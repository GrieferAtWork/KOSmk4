/* Copyright (c) 2019-2022 Griefer@Work                                       *
 *                                                                            *
 * This software is provided 'as-is', without any express or implied          *
 * warranty. In no event will the authors be held liable for any damages      *
 * arising from the use of this software.                                     *
 *                                                                            *
 * Permission is granted to anyone to use this software for any purpose,      *
 * including commercial applications, and to alter it and redistribute it     *
 * freely, subject to the following restrictions:                             *
 *                                                                            *
 * 1. The origin of this software must not be misrepresented; you must not    *
 *    claim that you wrote the original software. If you use this software    *
 *    in a product, an acknowledgement (see the following) in the product     *
 *    documentation is required:                                              *
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_SRC_FD_HANDMAN_C
#define GUARD_KERNEL_SRC_FD_HANDMAN_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/handle.h>
#include <kernel/handman.h>
#include <kernel/malloc.h>
#include <kernel/mman/cc.h>
#include <kernel/user.h>
#include <sched/task.h> /* get_stack_avail() */

#include <hybrid/atomic.h>
#include <hybrid/overflow.h>
#include <hybrid/sched/preemption.h>
#include <hybrid/sequence/list.h>
#include <hybrid/sched/atomic-lock.h>
#include <hybrid/sched/atomic-rwlock.h>

#include <kos/except.h>
#include <kos/except/reason/inval.h>
#include <kos/lockop.h>

#include <alloca.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>


/************************************************************************/
/* INTERNAL HANDRANGE ACCESS                                            */
/************************************************************************/

#undef RBTREE_LEFT_LEANING
#ifdef CONFIG_HANDMAN_USES_LLRBTREE
#define RBTREE_LEFT_LEANING
#endif /* CONFIG_HANDMAN_USES_LLRBTREE */
#define RBTREE_WANT_MINMAXLOCATE
#define RBTREE_WANT_PREV_NEXT_NODE
#define RBTREE_WANT_RLOCATE
#define RBTREE_OMIT_REMOVE
#define RBTREE_MINMAX_T_DEFINED
#define handrange_tree_minmax_t struct handrange_tree_minmax
#define RBTREE(name)            handrange_tree_##name
#define RBTREE_T                struct handrange
#define RBTREE_Tkey             unsigned int
#define RBTREE_GETNODE(self)    (self)->hr_node
#define RBTREE_GETMINKEY(self)  (self)->hr_minfd
#define RBTREE_GETMAXKEY(self)  (self)->hr_maxfd
#define RBTREE_REDFIELD         hr_flags
#define RBTREE_REDBIT           HANDRANGE_F_RED
#define RBTREE_CC               FCALL
#define RBTREE_NOTHROW          NOTHROW
#define RBTREE_DECL             FUNDEF
#define RBTREE_IMPL             PUBLIC
#include <hybrid/sequence/rbtree-abi.h>

DECL_BEGIN

static_assert(HANDRANGE_FREESLOTS_TRUNC_THRESHOLD > 1, "A trunc threshold of 0 doesn't make sense");
static_assert(HANDRANGE_FREESLOTS_SPLIT_THRESHOLD > HANDRANGE_FREESLOTS_TRUNC_THRESHOLD);
static_assert(sizeof(union handslot) == sizeof(struct handle));


/* Check if 2 given ranges overlap (that is: share at least 1 common address) */
#define RANGE_OVERLAPS(a_min, a_max, b_min, b_max) \
	((a_max) >= (b_min) && (a_min) <= (b_max))

#if !defined(NDEBUG) && !defined(NDEBUG_FINI)
#define DBG_memset memset
#else /* !NDEBUG && !NDEBUG_FINI */
#define DBG_memset(...) (void)0
#endif /* NDEBUG || NDEBUG_FINI */

#ifndef FD_MAX
#define FD_MAX INT_MAX
#endif /* !FD_MAX */

/* Ensure that `FD_MAX' is signed-positive, and doesn't overflow */
static_assert((int)FD_MAX == (unsigned int)FD_MAX);
static_assert((int)FD_MAX >= 0);

/* Find an overly large sequence of free slots and return the sequence's
 * starting index. When  no such range  exists, return `count'  instead. */
PRIVATE NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) unsigned int
NOTHROW(FCALL find_overlarge_free_range)(union handslot const *__restrict base,
                                         unsigned int count) {
	unsigned int i, max_overlarge_range_base;
	if (OVERFLOW_USUB(count, HANDRANGE_FREESLOTS_SPLIT_THRESHOLD, &max_overlarge_range_base))
		return count;
	for (i = 0; i < max_overlarge_range_base;) {
		unsigned int j;
		if (!handslot_isfree(&base[i])) {
			++i;
			continue;
		}
		/* Found a free slot */
		for (j = i + 1;; ++j) {
			if (j >= i + HANDRANGE_FREESLOTS_SPLIT_THRESHOLD)
				return i; /* Jup: it's an overlarge free sequence */
			if (!handslot_isfree(&base[j]))
				break; /* Nope -- this one's allocated! */
		}
		i = j + 1; /* Keep searching after the non-free slot. */
	}
	return count;
}

/* Same as `find_overlarge_free_range()', but find the last overlarge free range. */
PRIVATE NOBLOCK ATTR_PURE WUNUSED NONNULL((1, 3)) unsigned int
NOTHROW(FCALL rfind_overlarge_free_range)(union handslot const *__restrict base,
                                          unsigned int count,
                                          unsigned int *__restrict p_freemax) {
	unsigned int i = count;
	while (i >= HANDRANGE_FREESLOTS_SPLIT_THRESHOLD) {
		unsigned int j, free_count;
		--i;
		if (!handslot_isfree(&base[i]))
			continue;
		free_count = 1;
		for (;;) {
			j = i - free_count;
			if (free_count >= HANDRANGE_FREESLOTS_SPLIT_THRESHOLD) {
				*p_freemax = i;
				++j; /* `base[j]' wasn't checked, yet */
				while (j > 0 && handslot_isfree(&base[j - 1]))
					--j;
				return j;
			}
			if (!handslot_isfree(&base[j]))
				break;
			++free_count;
		}
		i = j;
	}
	return count;
}


/* Truncate `self'. -- The caller is holding a write-lock to `man'
 * @param: check_self__hr_joinlop: When `false', ignore restrictions by `self->_hr_joinlop'
 * @return: * :   The (possibly reallocated) `self'
 * @return: NULL: `self' was deleted. */
PRIVATE NOBLOCK NONNULL((1, 2)) struct handrange *
NOTHROW(FCALL handrange_truncate_locked)(struct handrange *__restrict self,
                                         struct handman *__restrict man,
                                         bool check_self__hr_joinlop) {
	/* Truncate trailing unused slots of `self' */
	unsigned int count;
	unsigned int rel_freemin;
	unsigned int rel_freemax;
again:
	count = handrange_count(self);
	assert(count > 0);
	if (handrange_slotisfree(self, count - 1)) {
		unsigned int trailing_free = 1;
		while (trailing_free < count &&
		       handrange_slotisfree(self, count - (trailing_free + 1)))
			++trailing_free;
		if (trailing_free >= count) {
			/* Range became fully empty --> Get rid of it. */
			handman_ranges_removenode(man, self);
			assert(ATOMIC_READ(self->hr_nlops) == 0);
			assert(ATOMIC_READ(self->hr_cexec) == 0);
			assert(ATOMIC_READ(self->hr_cfork) == 0);
			_handrange_free(self);
			return NULL;
		}
		if (trailing_free > HANDRANGE_FREESLOTS_TRUNC_THRESHOLD) {
			size_t reqsize;
			handman_ranges_removenode(man, self);
			count -= trailing_free;

			/* Update accounting. */
			self->hr_maxfd = self->hr_minfd + count - 1;

			/* Realloc to save on some space. */
			reqsize = _handrange_sizeof(count);
			if ((ATOMIC_READ(self->hr_nlops) != 0) ||
			    (check_self__hr_joinlop && ATOMIC_READ(self->_hr_joinlop.olo_func) != NULL)) {
				krealloc_in_place_nx(self, reqsize, GFP_ATOMIC);
			} else {
				struct handrange *newrange;
				newrange = (struct handrange *)krealloc_nx(self, reqsize, GFP_ATOMIC);
				if likely(newrange)
					self = newrange;
			}

			/* Re-insert into the range-tree */
			handman_ranges_insert(man, self);
		}
	}

	/* Find the last overlarge free range of `self'. If it isn't followed
	 * by  LOP handles, then  split `self' at  that overlarge free range.
	 * Afterwards,  realloc `self' (inplace-only if `hr_nlops != 0'), and
	 * search for more overlarge free range. */
	rel_freemin = rfind_overlarge_free_range(self->hr_hand, count, &rel_freemax);
	if (rel_freemin > 0 && rel_freemin < count) {
		struct handrange *newrange;
		unsigned int locount, hicount;
		size_t reqsize;
		assertf(rel_freemin < count - HANDRANGE_FREESLOTS_SPLIT_THRESHOLD,
		        "The case `freemin == count - HANDRANGE_FREESLOTS_SPLIT_THRESHOLD' "
		        "would mean that the free-range extends to the end, but we've already "
		        "handled the case of trailing free slots above!");
		locount = rel_freemin;
		hicount = count - (rel_freemax + 1);
		assert(locount > 0);
		assert(hicount > 0);

		/* Can only do the split if `self' doesn't contain LOP handles
		 * above the free range. */
		if (ATOMIC_READ(self->hr_nlops) != 0) {
			unsigned int i;
			for (i = rel_freemax + 1; i < count; ++i) {
				if (_handslot_islop(&self->hr_hand[i]))
					return self; /* Sorry. -- Can't do this split :( */
			}
		}

		/* Allocate a range for above the split.
		 * Note  that there is no way for us to safely do this while blocking, since
		 * we are called from a non-blocking context, meaning we have to rely on the
		 * allocation system being able to acquire all necessary locks on the  first
		 * try. -- If that fails, then we won't be able to release unused memory. */
		newrange = _handrange_alloc_nx(hicount, GFP_ATOMIC);
		if (!newrange)
			goto try_trim_leading_slots;

		/* All right! -- Let's fill in this new range. */
		handman_ranges_removenode(man, self);
		newrange->hr_flags = HANDRANGE_F_NORMAL;
		newrange->hr_minfd = self->hr_minfd + rel_freemax + 1;
		newrange->hr_maxfd = self->hr_maxfd;
		newrange->hr_nhint = 0;
		newrange->hr_nlops = 0;
		newrange->hr_cexec = 0;
		newrange->hr_cfork = 0;
		DBG_memset(&newrange->_hr_joinlop, 0xcc, sizeof(newrange->_hr_joinlop));
		newrange->_hr_joinlop.olo_func = NULL; /* Mark as "inactive" */
		assert(newrange->hr_minfd <= newrange->hr_maxfd);
		assert(handrange_count(newrange) == hicount);
		self->hr_maxfd = self->hr_minfd + rel_freemin - 1;
		assert(handrange_count(self) == locount);

		/* Transfer handle data. */
		memcpy(&newrange->hr_hand[0],
		       &self->hr_hand[rel_freemax + 1],
		       hicount, sizeof(union handslot));

		/* Update accounting for cexec/cfork handles. */
		if ((ATOMIC_READ(self->hr_cexec) != 0) ||
		    (ATOMIC_READ(self->hr_cfork) != 0)) {
			unsigned int i;
			for (i = 0; i < hicount; ++i) {
				iomode_t mode;
				if (!handrange_slotisused(newrange, i))
					continue;
				assertf(handrange_slotishand(newrange, i),
				        "There shouldn't be any LOP handles in here!");
				mode = newrange->hr_hand[i].mh_hand.h_mode;
				if (mode & IO_CLOEXEC) {
					ATOMIC_DEC(self->hr_cexec);
					++newrange->hr_cexec;
				}
				if (mode & IO_CLOFORK) {
					ATOMIC_DEC(self->hr_cfork);
					++newrange->hr_cfork;
				}
			}
		}

		/* Release unused memory from `self'. */
		reqsize = _handrange_sizeof(locount);
		if ((ATOMIC_READ(self->hr_nlops) != 0) ||
		    (check_self__hr_joinlop && ATOMIC_READ(self->_hr_joinlop.olo_func) != NULL)) {
			/* Must  use  inplace-realloc if  there  are LOP
			 * handles before the free-self we just removed. */
			krealloc_in_place_nx(self, reqsize, GFP_NORMAL);
		} else {
			struct handrange *temp;
			temp = (struct handrange *)krealloc_nx(self, reqsize, GFP_NORMAL);
			if likely(temp)
				self = temp;
		}

		/* Insert the new ranges. */
		handman_ranges_insert(man, newrange);
		handman_ranges_insert(man, self);
		goto again;
	}

try_trim_leading_slots:
	/* If `self->hr_nlops == 0', trim leading free slots from `self' */
	if (handrange_slotisfree(self, 0) && ATOMIC_READ(self->hr_nlops) == 0 &&
	    (!check_self__hr_joinlop || ATOMIC_READ(self->_hr_joinlop.olo_func) == NULL)) {
		struct handrange *temp;
		unsigned int count, free_count = 1;
		size_t reqsize;
		for (;;) {
			assertf(free_count < handrange_count(self),
			        "The case of everything being free was already handled "
			        "above, so we shouldn't be able to see it again here!");
			if (!handrange_slotisfree(self, free_count))
				break;
			++free_count;
		}
		if (free_count > HANDRANGE_FREESLOTS_TRUNC_THRESHOLD) {
			/* Trim leading unused slots. */
			handman_ranges_removenode(man, self);
			self->hr_minfd += free_count;
			count = handrange_count(self);
			memmovedown(&self->hr_hand[0],
			            &self->hr_hand[free_count],
			            count, sizeof(union handslot));

			/* Reallocate to release unused memory. */
			reqsize = _handrange_sizeof(count);
			temp = (struct handrange *)krealloc_nx(self, reqsize, GFP_ATOMIC);
			if likely(temp)
				self = temp;

			/* Re-insert the (now-truncated) range. */
			handman_ranges_insert(man, self);
		}
	}
	return self;
}


/* Join the given 2 ranges (or return `NULL' if this can't be done,
 * either due to lockop restrictions,  or because memory could  not
 * be allocated)
 * @param: ignore_my__hr_joinlop: When either `lorange' or `hirange', ignore restrictions
 *                                caused  by this range's  `_hr_joinlop' field. Should be
 *                                set to the origin range if called from a lock-op.
 * @return: * :   The joined handle-range.
 * @return: NULL: Was unable to join ranges. */
PRIVATE NOBLOCK NONNULL((1, 2, 4)) struct handrange *
NOTHROW(FCALL handrange_rejoin2)(struct handrange *lorange,
                                 struct handrange *hirange,
                                 struct handrange *ignore_my__hr_joinlop,
                                 struct handman *__restrict man) {
	unsigned int locount, hicount;
	size_t reqsize, avlsize;
	assert(lorange->hr_maxfd + 1 == hirange->hr_minfd);

	/* Joining is never possible when `hirange' contains LOP handles. */
	if (ATOMIC_READ(hirange->hr_nlops) != 0)
		return NULL;
	if (hirange != ignore_my__hr_joinlop &&
	    ATOMIC_READ(hirange->_hr_joinlop.olo_func) != NULL)
		return NULL;

	/* Figure out buffer requirements. */
	locount = handrange_count(lorange);
	hicount = handrange_count(hirange);
	reqsize = _handrange_sizeof(locount + hicount);
	handman_ranges_removenode(man, lorange);
	krealloc_in_place_nx(lorange, reqsize, GFP_ATOMIC);
	avlsize = kmalloc_usable_size(lorange);
	if (avlsize < reqsize) {
		struct handrange *newrange;
		/* Try to do a proper realloc of `lorange' (if allowed) */
		if ((ATOMIC_READ(lorange->hr_nlops) != 0) ||
		    (lorange != ignore_my__hr_joinlop &&
		     ATOMIC_READ(lorange->_hr_joinlop.olo_func) != NULL)) {
			reqsize = _handrange_sizeof(locount);
			krealloc_in_place_nx(lorange, reqsize, GFP_ATOMIC);
			handman_ranges_insert(man, lorange);
			return NULL;
		}

		/* Do a full realloc of `lorange' */
		newrange = (struct handrange *)krealloc_nx(lorange, reqsize, GFP_ATOMIC);
		if (!newrange) {
			/* Unable to rejoin due to lack of available memory/locks :( */
			reqsize = _handrange_sizeof(locount);
			krealloc_in_place_nx(lorange, reqsize, GFP_ATOMIC);
			handman_ranges_insert(man, lorange);
			return NULL;
		}
		lorange = newrange;
		assert(kmalloc_usable_size(lorange) >= reqsize);
	}

	/* All right! `lorange' is large enough to do the join! */
	handman_ranges_removenode(man, hirange);
	lorange->hr_maxfd = hirange->hr_maxfd;
	if (ATOMIC_READ(lorange->hr_nhint) > locount + hirange->hr_nhint)
		ATOMIC_WRITE(lorange->hr_nhint, locount + hirange->hr_nhint);
	ATOMIC_ADD(lorange->hr_cexec, hirange->hr_cexec); /* non-atomic in `hirange' OK because no LOPs */
	ATOMIC_ADD(lorange->hr_cfork, hirange->hr_cfork); /* non-atomic in `hirange' OK because no LOPs */
	lorange->hr_maxfd = hirange->hr_maxfd;
	memcpy(&lorange->hr_hand[locount],
	       &hirange->hr_hand[0],
	       hicount, sizeof(union handslot));

	/* Re-insert the (now-joined) `lorange' */
	handman_ranges_insert(man, lorange);

	/* Free the (now-unused) `hirange' */
	_handrange_free(hirange);

	/* Tell our caller the updated address of `lorange' */
	return lorange;
}

/* @return: * : The updated (and possibly realloc'd) `self' */
PRIVATE NOBLOCK ATTR_RETNONNULL NONNULL((1, 2)) struct handrange *
NOTHROW(FCALL handrange_rejoin_locked)(struct handrange *__restrict self,
                                       struct handman *__restrict man) {
	/* Try to join `self' with its neighbors, but never release
	 * our lock from `man', and  never do anything blocking  or
	 * something that might THROW.
	 *
	 * NOTE: Must respect  all  lop  restrictions!  (except  for
	 *       `self->_hr_joinlop', which we're allowed to ignore) */
	struct handrange *neighbor, *joined;
	neighbor = handman_ranges_prev(man, self);
	if (neighbor && neighbor->hr_maxfd + 1 == self->hr_minfd) {
		joined = handrange_rejoin2(neighbor, self, self, man);
		if (joined)
			self = joined;
	}
	neighbor = handman_ranges_next(man, self);
	if (neighbor && self->hr_maxfd + 1 == neighbor->hr_minfd) {
		joined = handrange_rejoin2(self, neighbor, self, man);
		if (joined)
			self = joined;
	}
	return self;
}


PRIVATE NOBLOCK NONNULL((1, 2)) Tobpostlockop(handman) *
NOTHROW(LOCKOP_CC handrange_rejoin_lop)(Toblockop(handman) *__restrict self,
                                        struct handman *__restrict obj);
PRIVATE NOBLOCK NONNULL((1, 2)) Tobpostlockop(handman) *
NOTHROW(LOCKOP_CC handrange_rejoin_restart_lop)(Toblockop(handman) *__restrict self,
                                                struct handman *__restrict obj) {
	struct handrange *me;
	uintptr_t old_flags;
	me = container_of(self, struct handrange, _hr_joinlop);

	/* Do the actual work. */
	old_flags = ATOMIC_FETCHAND(me->hr_flags, ~_HANDRANGE_F_TRUNC);
	if (old_flags & _HANDRANGE_F_TRUNC) {
		/* NOTE: Ignore `_hr_joinlop' restrictions because we're that lockop! */
		me = handrange_truncate_locked(me, obj, false);
		if (!me)
			return NULL; /* Range was deleted. */
	}
	me = handrange_rejoin_locked(me, obj);

	/* Restart support. */
	ATOMIC_WRITE(me->_hr_joinlop.olo_func, &handrange_rejoin_lop);
	oblockop_enqueue(&obj->hm_lops, &me->_hr_joinlop); /* Caller will notice this */
	return NULL;
}

PRIVATE NOBLOCK NONNULL((1, 2)) Tobpostlockop(handman) *
NOTHROW(LOCKOP_CC handrange_rejoin_lop)(Toblockop(handman) *__restrict self,
                                        struct handman *__restrict obj) {
	struct handrange *me;
	uintptr_t old_flags;
	me = container_of(self, struct handrange, _hr_joinlop);

	/* Do the actual work. */
	old_flags = ATOMIC_FETCHAND(me->hr_flags, ~_HANDRANGE_F_TRUNC);
	if (old_flags & _HANDRANGE_F_TRUNC) {
		/* NOTE: Ignore `_hr_joinlop' restrictions because we're that lockop! */
		me = handrange_truncate_locked(me, obj, false);
		if (!me)
			return NULL; /* Range was deleted. */
	}
	me = handrange_rejoin_locked(me, obj);

	/* Restart support. */
	if (!ATOMIC_CMPXCH(me->_hr_joinlop.olo_func, &handrange_rejoin_lop, NULL)) {
		/* We get here if `_hr_joinlop' was changed to the restart function.
		 * In that case, we must enqueue the lockop once again to have it be
		 * handled a second time. */
		oblockop_enqueue(&obj->hm_lops, &me->_hr_joinlop); /* Caller will notice this */
	}
	return NULL;
}


/* Asynchronously try to rejoin `self' with its neighboring ranges.
 * This function uses `_hr_joinlop' in  case doing so would  block. */
PUBLIC NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL handrange_dec_nlops_and_maybe_rejoin)(struct handrange *__restrict self,
                                                    struct handman *__restrict man,
                                                    bool try_truncate_self) {
	/* Rejoin and all that stuff can only work if the _last_ LOP handle goes away.
	 * For  any recursive LOP handle, we don't even have to try and acquire a lock
	 * to the handle manager. */
	for (;;) {
		unsigned int nlops;
		nlops = ATOMIC_READ(self->hr_nlops);
		assertf(nlops >= 1, "Only call this if _you_ are holding a LOP handle.");
		if (nlops < 2)
			break;
		/* Set rejoin flags. */
		if (try_truncate_self)
			ATOMIC_OR(self->hr_flags, _HANDRANGE_F_TRUNC);
		if (ATOMIC_CMPXCH_WEAK(self->hr_nlops, nlops, nlops - 1))
			return;
	}
	if (handman_trywrite(man)) {
		ATOMIC_DEC(self->hr_nlops);
		if ((ATOMIC_FETCHAND(self->hr_flags, ~_HANDRANGE_F_TRUNC) & _HANDRANGE_F_TRUNC) ||
		    (try_truncate_self)) {
			if (!handrange_truncate_locked(self, man, true))
				goto unlock_and_done;
		}
		handrange_rejoin_locked(self, man);
unlock_and_done:
		handman_endwrite(man);
		return;
	}

	/* Set rejoin flags. */
	if (try_truncate_self)
		ATOMIC_OR(self->hr_flags, _HANDRANGE_F_TRUNC);
	for (;;) {
		Toblockop_callback_t(handman) func;
		func = ATOMIC_READ(self->_hr_joinlop.olo_func);
		assert(func == NULL ||
		       func == &handrange_rejoin_lop ||
		       func == &handrange_rejoin_restart_lop);
		if (func == NULL) {
			/* Initial lockop request. */
			if (!ATOMIC_CMPXCH(self->_hr_joinlop.olo_func, NULL, &handrange_rejoin_lop))
				continue;
			break;
		}
		if (func == &handrange_rejoin_lop) {
			/* Force another rejoin after the current one is done. */
			if (!ATOMIC_CMPXCH(self->_hr_joinlop.olo_func,
			                   &handrange_rejoin_lop,
			                   &handrange_rejoin_restart_lop))
				continue;
			ATOMIC_DEC(self->hr_nlops);
			return;
		}
		/* At least 1 additional rejoin will happen after the current
		 * one, meaning the  caller request will  be served in  full! */
		ATOMIC_DEC(self->hr_nlops);
		return;
	}

	/* Decrement the NLOPs counter _AFTER_ we set `_hr_joinlop' to non-NULL.
	 * This is important so that at no point in time will there be an intent
	 * of a lock-op without some indicator. */
	ATOMIC_DEC(self->hr_nlops);

	/* Enqueue the lockop */
	oblockop_enqueue(&man->hm_lops, &self->_hr_joinlop);
	_handman_reap(man);
}




/* Destroy the given handle range. */
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL handrange_destroy)(struct handrange *__restrict self) {
	unsigned int i, count;

	/* Drop references from still-opened handles.
	 * Note that at this point there mustn't be any LOP handles remaining! */
	assertf(self->hr_nlops == 0,
	        "Destroying handle-range which still contains LOP handles\n"
	        "In this case, those LOP handles should have kept us alive!");
	count = handrange_count(self);
	for (i = 0; i < count; ++i) {
		assertf(handrange_slotishand(self, i) || handrange_slotisfree(self, i),
		        "Invalid slot %u: marked as used, but isn't a handle", i);
		if (handrange_slotisfree(self, i))
			continue;
		handle_decref(self->hr_hand[i].mh_hand);
	}

	/* Free the actual handle-range structure. */
	_handrange_free(self);
}


PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL handrange_destroy_tree)(struct handrange *__restrict root) {
	struct handrange *lhs, *rhs;
again:
	lhs = root->hr_node.rb_lhs;
	rhs = root->hr_node.rb_rhs;
	handrange_destroy(root);
	if (lhs) {
		if (rhs)
			handrange_destroy_tree(rhs);
		root = lhs;
		goto again;
	}
	if (rhs) {
		root = rhs;
		goto again;
	}
}

/* Destroy the given handle manager. */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL handman_destroy)(struct handman *__restrict self) {
	handman_reap(self);
	sig_broadcast_for_fini(&self->hm_changed);
	if likely(self->hm_ranges != NULL)
		handrange_destroy_tree(self->hm_ranges);
	kfree(self);
}



struct handman_fork_data {
	struct handrange *hfd_range;    /* [0..1] Preallocated handle range. */
	unsigned int      hfd_nextfd;   /* Lowest FD number that must still be cloned */
	unsigned int      hfd_closemin; /* Lowest FD that must be close'd */
	unsigned int      hfd_closemax; /* Greatest FD that must be close'd */
};



/* Find the first range containing an FD >= minfd */
PRIVATE ATTR_PURE WUNUSED NONNULL((1)) struct handrange *
NOTHROW(FCALL handman_firstrangeafter)(struct handman *__restrict self,
                                       unsigned int minfd) {
	struct handrange *result;
	result = handman_ranges_rlocate(self, minfd, UINT_MAX);
	if (result) {
		/* Ensure that no other range also matches requirements */
		struct handrange *prev;
		for (;;) {
			prev = handman_ranges_prev(self, result);
			if (!prev)
				break;
			if (minfd > prev->hr_maxfd)
				break; /* This range doesn't match requirements */
			result = prev;
		}
	}
	return result;
}


/* NOTE: This function assumes that `dst' is freshly allocated and mustn't be locked/unlocked
 * NOTE: Upon error, this function releases a read-lock from `src'. */
PRIVATE NONNULL((1, 2, 3)) bool FCALL
handrange_clone_or_unlock(struct handman *__restrict dst,
                          struct handman *__restrict src,
                          struct handman_fork_data *__restrict data) {
#define UNLOCKALL() handman_endread(src)
	struct handrange *dstrange;
	struct handrange *srcrange;
	unsigned int clone_minfd, clone_maxfd;
	unsigned int i, clone_count;
	unsigned int skip;
	size_t got_rangesize;
	size_t req_rangesize;
	bool has_lop_handles;
	bool has_fork_handles;
	if (data->hfd_nextfd == 0) {
		srcrange = handman_ranges_first(src);
	} else {
again:
		srcrange = handman_firstrangeafter(src, data->hfd_nextfd);
	}
	if (!srcrange)
		return true; /*  Everything was cloned! */

	/* Figure out which FDs to clone */
	clone_minfd = data->hfd_nextfd;
	if (clone_minfd < srcrange->hr_minfd)
		clone_minfd = srcrange->hr_minfd;
	clone_maxfd = srcrange->hr_maxfd;
	assert(clone_minfd <= clone_maxfd);

	/* Check if clone_minfd...clone_maxfd overlaps with the caller's clone-on-fork range. */
	if (RANGE_OVERLAPS(clone_minfd,
	                   clone_maxfd,
	                   data->hfd_closemin,
	                   data->hfd_closemax)) {
		if (clone_minfd < data->hfd_closemin) {
			/* Clone range _BEFORE_ force-close area */
			clone_maxfd = data->hfd_closemin - 1;
		} else {
			/* Clone range _AFTER_ force-close area */
			clone_minfd = data->hfd_closemax + 1;
		}
		if (clone_minfd > clone_maxfd) {
			/* No part of `srcrange' should be cloned, so next up:
			 * clone the first range beyond the force-close range. */
			data->hfd_nextfd = data->hfd_closemax + 1;
			goto again;
		}
	}

	dstrange      = data->hfd_range;
	clone_count   = (clone_maxfd - clone_minfd) + 1;
	got_rangesize = kmalloc_usable_size(dstrange);
	req_rangesize = offsetof(struct handrange, hr_hand) +
	                clone_count * sizeof(struct handle);
	if (req_rangesize > got_rangesize) {
		/* Try to allocate a larger range. */
		dstrange = (struct handrange *)krealloc_nx(dstrange, req_rangesize, GFP_ATOMIC);
		if (!dstrange) {
			/* Re-attempt while blocking. */
			UNLOCKALL();
			dstrange = (struct handrange *)krealloc(dstrange, req_rangesize, GFP_NORMAL);
			data->hfd_range = dstrange;
			/* Tell the caller that we lost the lock. */
			return false;
		}
		got_rangesize = kmalloc_usable_size(dstrange);
	}
	assert(req_rangesize <= got_rangesize);

	/* Figure out how many leading file are being skipped from `srcrange' (usually `0') */
	skip = __builtin_expect(clone_minfd - srcrange->hr_minfd, 0);

	/* Fill in `dstrange' */
	if (OVERFLOW_USUB(ATOMIC_READ(srcrange->hr_nhint),
	                  skip, &dstrange->hr_nhint))
		dstrange->hr_nhint = 0;
	dstrange->hr_nlops = 0;
	dstrange->hr_cexec = srcrange->hr_cexec;
	dstrange->hr_cfork = 0;
	DBG_memset(&dstrange->_hr_joinlop, 0xcc, sizeof(dstrange->_hr_joinlop));
	dstrange->_hr_joinlop.olo_func = NULL; /* Mark as "inactive" */

	/* Check if `srcrange' contains LOP handles (must be done _BEFORE_ we copy
	 * its  handle vector, since a zero value  after the copy could still mean
	 * that it was non-zero before, and thus had us copying LOP handles) */
	has_lop_handles = ATOMIC_READ(srcrange->hr_nlops) != 0;

	/* Copy the actual handle vector. */
	memcpy(&dstrange->hr_hand[0],
	       &srcrange->hr_hand[skip],
	       clone_count,
	       sizeof(struct handle));

	/* Explicitly delete LOP handles. */
	if (has_lop_handles) {
		for (i = 0; i < clone_count; ++i) {
			if likely(!_handslot_islop(&dstrange->hr_hand[i]))
				continue;
			DBG_memset(&dstrange->hr_hand[i], 0xcc, sizeof(dstrange->hr_hand[i]));
			dstrange->hr_hand[i].mh_hand.h_type = HANDLE_TYPE_UNDEFINED;
			dstrange->hr_hand[i].mh_hand.h_mode = 0;
			if (dstrange->hr_nhint > i)
				dstrange->hr_nhint = i; /* Fix hint */
		}
	}

	/* Explicitly delete CLOFORK handles. */
	has_fork_handles = srcrange->hr_cfork != 0;
	if (has_fork_handles) {
		for (i = 0; i < clone_count; ++i) {
			if (!(dstrange->hr_hand[i].mh_hand.h_mode & IO_CLOFORK))
				continue;
			DBG_memset(&dstrange->hr_hand[i], 0xcc, sizeof(dstrange->hr_hand[i]));
			dstrange->hr_hand[i].mh_hand.h_type = HANDLE_TYPE_UNDEFINED;
			dstrange->hr_hand[i].mh_hand.h_mode = 0;
			if (dstrange->hr_nhint > i)
				dstrange->hr_nhint = i; /* Fix hint */
		}
	}

	/* Fill in from where the next range should be cloned */
	data->hfd_nextfd = clone_maxfd + 1;

	/* Check for over-large gaps in `dstrange' */
	if (has_lop_handles || has_fork_handles) {
		/* `dstrange' may contain overly large gaps, or possibly even no handles at all.
		 * As such, we must trim unused slots and maybe even split the entire range into
		 * multiple smaller ones. */
		unsigned int trailing_free = 0;
		unsigned int leading_free = 0;
		unsigned int new_clone_count;
		while (leading_free < clone_count &&
		       handrange_slotisfree(dstrange, leading_free))
			++leading_free;
		if unlikely(leading_free >= clone_count) {
			/* The range is entirely empty. --> Just move on to the next one! */
			data->hfd_range = dstrange;
			goto again;
		}
		if (leading_free > HANDRANGE_FREESLOTS_TRUNC_THRESHOLD) {
			clone_minfd += leading_free;
			clone_count -= leading_free;
			req_rangesize -= leading_free * sizeof(struct handle);
			memmovedown(&dstrange->hr_hand[0],
			            &dstrange->hr_hand[leading_free],
			            clone_count, sizeof(struct handle));
		}

		/* Trim trailing free slots */
		trailing_free = 0;
		while ((assert(clone_count),
		        handrange_slotisfree(dstrange, clone_count - (trailing_free + 1))))
			++trailing_free;
		if (trailing_free > HANDRANGE_FREESLOTS_TRUNC_THRESHOLD) {
			clone_count -= trailing_free;
			req_rangesize -= trailing_free * sizeof(struct handle);
		}

		/* Check for over-large gaps in the middle */
		new_clone_count = find_overlarge_free_range(dstrange->hr_hand, clone_count);
		assert(new_clone_count <= clone_count);
		if (new_clone_count < clone_count) {
			assertf(new_clone_count != 0, "the fully-empty case was already checked above");
			clone_maxfd   = clone_minfd + new_clone_count - 1;
			clone_count   = new_clone_count;
			req_rangesize = offsetof(struct handrange, hr_hand) +
			                new_clone_count * sizeof(struct handle);
			/* We know that handles `clone_minfd+new_clone_count...+=HANDRANGE_FREESLOTS_SPLIT_THRESHOLD'
			 * are all marked as free. -  As such, the next range to-be  cloned once we're done with  the
			 * current one starts at the end of said free range. */
			data->hfd_nextfd = clone_minfd;
			data->hfd_nextfd += new_clone_count;
			data->hfd_nextfd += HANDRANGE_FREESLOTS_SPLIT_THRESHOLD;
		}

		/* Delete next-free hint */
		dstrange->hr_nhint = 0;
	}

	/* Fill in remaining fields. */
	dstrange->hr_flags = HANDRANGE_F_NORMAL;
	dstrange->hr_minfd = clone_minfd;
	dstrange->hr_maxfd = clone_maxfd;

	/* Acquire new references to cloned handles. */
	for (i = 0; i < clone_count; ++i) {
		if (dstrange->hr_hand[i].mh_hand.h_type == HANDLE_TYPE_UNDEFINED)
			continue;
		handle_incref(dstrange->hr_hand[i].mh_hand);
		++dst->hm_handles;
	}

	/* Free unused memory. */
	if (req_rangesize < got_rangesize) {
		struct handrange *smaller;
		smaller = (struct handrange *)krealloc_nx(dstrange, req_rangesize, GFP_ATOMIC);
		if likely(smaller)
			dstrange = smaller;
	}

	/* Insert the cloned range into `dst' */
	handman_ranges_insert(dst, dstrange);

	/* Consume the preallocated range (which has now been inserted into `dst') */
	data->hfd_range = NULL;

	/* Keep on cloning additional ranges. */
	goto again;
#undef UNLOCKALL
}



/* For a given handle manager, creating a copy that no longer
 * contains any handles that had been marked as `IO_CLOFORK'.
 *
 * Additionally, handles that are currently being installed,
 * as per `handman_install_begin()' will _NOT_ be copied. Or
 * to be precise: any `_handslot_islop' handle is skipped. */
PUBLIC ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct handman *FCALL
handman_fork(struct handman *__restrict self)
		THROWS(E_BADALLOC, E_WOULDBLOCK) {
	REF struct handman *result;
	/* Allocate the new handle manager */
	result = (REF struct handman *)kmalloc(sizeof(struct handman), GFP_NORMAL);
	result->hm_ranges  = NULL;
	result->hm_handles = 0;
	TRY {
		struct handman_fork_data fdat;

		/* Set-up fork meta-data */
		fdat.hfd_range    = NULL;
		fdat.hfd_nextfd   = 0;
		fdat.hfd_closemin = (unsigned int)-1; /* Don't close any extra handles */
		fdat.hfd_closemax = 0;

		/* If a range ends up unused in the end, force-free it. */
		RAII_FINALLY { _handrange_free_unlikely(fdat.hfd_range); };

		/* Actually clone handle ranges. */
		do {
			handman_read(self);
		} while (!handrange_clone_or_unlock(result, self, &fdat));
		handman_endread(self);
	} EXCEPT {
		if (result->hm_ranges)
			handrange_destroy_tree(result->hm_ranges);
		kfree(result);
		RETHROW();
	}

	/* Fill in remaining fields. */
	result->hm_refcnt = 1;
	atomic_rwlock_init(&result->hm_lock);
	SLIST_INIT(&result->hm_lops);
	sig_init(&result->hm_changed);
	result->hm_maxhand = ATOMIC_READ(self->hm_maxhand);
	result->hm_maxfd   = ATOMIC_READ(self->hm_maxfd);
	return result;
}

/* The combination of `handman_fork()' and `handman_closerange()'
 * @throw: E_INVALID_ARGUMENT_BAD_VALUE:E_INVALID_ARGUMENT_CONTEXT_CLOSE_RANGE_BADRANGE: [...] */
PUBLIC ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct handman *FCALL
handman_fork_and_closerange(struct handman *__restrict self,
                            unsigned int minfd, unsigned int maxfd)
		THROWS(E_BADALLOC_INSUFFICIENT_HEAP_MEMORY,
		       E_WOULDBLOCK, E_INVALID_ARGUMENT_BAD_VALUE) {
	REF struct handman *result;
	if unlikely(minfd > maxfd) {
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_CLOSE_RANGE_BADRANGE,
		      minfd, maxfd);
	}
	/* Enforce min/max bounds */
	if unlikely(minfd > (unsigned int)FD_MAX)
		return handman_fork(self);
	if unlikely(maxfd > (unsigned int)FD_MAX)
		maxfd = (unsigned int)FD_MAX;
	assert(minfd <= maxfd);

	/* Allocate the new handle manager */
	result = (REF struct handman *)kmalloc(sizeof(struct handman), GFP_NORMAL);
	result->hm_ranges  = NULL;
	result->hm_handles = 0;
	TRY {
		struct handman_fork_data fdat;

		/* Set-up fork meta-data */
		fdat.hfd_range    = NULL;
		fdat.hfd_nextfd   = 0;
		fdat.hfd_closemin = (unsigned int)minfd; /* Force-clone range. */
		fdat.hfd_closemax = (unsigned int)maxfd;

		/* If a range ends up unused in the end, force-free it. */
		RAII_FINALLY { _handrange_free_unlikely(fdat.hfd_range); };

		/* Actually clone handle ranges. */
		do {
			handman_read(self);
		} while (!handrange_clone_or_unlock(result, self, &fdat));
		handman_endread(self);
	} EXCEPT {
		if (result->hm_ranges)
			handrange_destroy_tree(result->hm_ranges);
		kfree(result);
		RETHROW();
	}

	/* Fill in remaining fields. */
	result->hm_refcnt = 1;
	atomic_rwlock_init(&result->hm_lock);
	SLIST_INIT(&result->hm_lops);
	sig_init(&result->hm_changed);
	result->hm_maxhand = ATOMIC_READ(self->hm_maxhand);
	result->hm_maxfd   = ATOMIC_READ(self->hm_maxfd);
	return result;
}



/* Close all CLOEXEC handles in `self'
 * @return: * : The # of closed handles. */
PRIVATE NOBLOCK NONNULL((1)) unsigned int
NOTHROW(FCALL handrange_cloexec)(struct handrange *__restrict self) {
	unsigned int result = 0;
	unsigned int i, count;
	if (self->hr_cexec == 0)
		goto done;
	count = handrange_count(self);
	for (i = 0; i < count; ++i) {
		if (!handrange_slotishand(self, i))
			continue;
		if (!(self->hr_hand[i].mh_hand.h_mode & IO_CLOEXEC))
			continue;

		/* Close this handle. */
		handle_decref(self->hr_hand[i].mh_hand);
		if (self->hr_hand[i].mh_hand.h_mode & IO_CLOFORK)
			ATOMIC_DEC(self->hr_cfork);
		DBG_memset(&self->hr_hand[i].mh_hand, 0xcc, sizeof(self->hr_hand[i].mh_hand));
		self->hr_hand[i].mh_hand.h_type = HANDLE_TYPE_UNDEFINED;
		ATOMIC_DEC(self->hr_cexec);
		if (ATOMIC_READ(self->hr_nhint) > i)
			ATOMIC_WRITE(self->hr_nhint, i);
		++result;
	}
done:
	return result;
}


/* Close all handles marked as `IO_CLOEXEC'
 *
 * WARNING: If another thread  is currently using  `handman_install_begin()'
 *          to create a handle that will later be installed with IO_CLOEXEC,
 *          said handle will _NOT_ be closed. This is normally not a problem
 *          since `handman_cloexec()' is only called during exec(), and at a
 *          point where the calling thread *should* be alone with its files,
 *          but  this scenario can be constructed by use of CLONE_FILES, and
 *          there is no way to prevent this race from happening (other  than
 *          by simply going with the  flow and accepting that every  process
 *          should  have its own file descriptor table). This is OK however,
 *          since  one could argue that said other thread opened the CLOEXEC
 *          file _after_ we closed all CLOEXEC files that were there before. */
PUBLIC NONNULL((1)) void FCALL
handman_cloexec(struct handman *__restrict self)
		THROWS(E_WOULDBLOCK) {
	bool changed = false;
	unsigned int minfd = 0;
	unsigned int total = 0;
	struct handrange *range;
	handman_write(self);
	while ((range = handman_firstrangeafter(self, minfd)) != NULL) {
		unsigned int part;
		minfd = range->hr_maxfd + 1;
		/* Close all CLOEXEC handles from this range. */
		part = handrange_cloexec(range);
		total += part;
		if (part) {
			/* If something was closed, truncate unused slots. */
			handrange_truncate_locked(range, self, true);
			changed = true;
		}
	}
	assert(self->hm_handles >= total);
	ATOMIC_SUB(self->hm_handles, total);
	handman_endwrite(self);
	if (changed)
		sig_broadcast(&self->hm_changed);
}

/* The handle manager of the kernel itself. */
PUBLIC struct handman handman_kernel = {
	.hm_refcnt  = 4, /* handman_kernel, boottask, asyncwork, bootidle */
	.hm_lock    = ATOMIC_RWLOCK_INIT,
	.hm_lops    = SLIST_HEAD_INITIALIZER(handman_kernel.hm_lops),
	.hm_ranges  = NULL,
	.hm_changed = SIG_INIT,
	.hm_handles = 0,
	.hm_maxhand = (unsigned int)FD_MAX + 1,
	.hm_maxfd   = (unsigned int)FD_MAX,
};

/* [1..1][lock(read(THIS_TASK || INTERN(lock)),
 *             write(THIS_TASK && INTERN(lock)))]
 * Handle manager of the calling thread. */
PUBLIC ATTR_PERTASK ATTR_ALIGN(struct handman *)
this_handman = &handman_kernel;

DEFINE_PERTASK_FINI(fini_this_handman);
PRIVATE ATTR_USED NOBLOCK NONNULL((1)) void
NOTHROW(KCALL fini_this_handman)(struct task *__restrict self) {
	decref(FORTASK(self, this_handman));
}


#ifndef CONFIG_NO_SMP
/* Lock for accessing any remote thread's this_handman field */
PRIVATE struct atomic_lock handman_change_lock = ATOMIC_RWLOCK_INIT;
#endif /* !CONFIG_NO_SMP */
#define handman_change_lock_acquire() atomic_lock_acquire_smp(&handman_change_lock)
#define handman_change_lock_release() atomic_lock_release_smp(&handman_change_lock)



/* Return the handle manager of the given thread. */
PUBLIC NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct handman *
NOTHROW(FCALL task_gethandman)(struct task *__restrict thread) {
	REF struct handman *result;
	handman_change_lock_acquire();
	result = incref(FORTASK(thread, this_handman));
	handman_change_lock_release();
	return result;
}

/* Exchange the handle manager of the calling thread (and return the old one). */
PUBLIC ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct handman *
NOTHROW(FCALL task_sethandman_inherit)(/*inherit(always)*/ REF struct handman *__restrict newman) {
	REF struct handman *result;
	handman_change_lock_acquire();
	result = PERTASK_GET(this_handman);
	PERTASK_SET(this_handman, newman);
	handman_change_lock_release();
	return result;
}



/************************************************************************/
/* HIGH-LEVEL HANDLE OPERATIONS (SPECIFIC TO SOME HANDMAN)              */
/************************************************************************/

/* Returns the max used FD +1, or `0' if no FDs are in use */
PUBLIC NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) unsigned int
NOTHROW(FCALL handman_usefdend)(struct handman const *__restrict self) {
	unsigned int result;
	struct handrange *range;
	range = handman_ranges_last(self);
	if unlikely(!range)
		return 0;
	result = handrange_count(range);
	while (result && !handrange_slotishand(range, result - 1))
		--result;
	result += range->hr_minfd;
	return result;
}

PRIVATE ATTR_COLD ATTR_NORETURN NONNULL((1)) void FCALL
handman_unlock_and_throw_invalid_handle(struct handman *__restrict self,
                                        fd_t fd, bool is_write_lock)
		THROWS(E_INVALID_HANDLE_FILE) {
	unsigned int reason, maxfd, useend;
	useend = handman_usefdend(self);
	maxfd  = self->hm_maxfd;
	if (is_write_lock) {
		handman_endwrite(self);
	} else {
		handman_endread(self);
	}
	reason = E_INVALID_HANDLE_FILE_UNBOUND;
	if ((unsigned int)fd > maxfd)
		reason = E_INVALID_HANDLE_FILE_ILLEGAL;
	if (fd < 0)
		reason = E_INVALID_HANDLE_FILE_NEGATIVE;
	THROW(E_INVALID_HANDLE_FILE, (syscall_slong_t)fd, reason, useend, maxfd);
}


/* Change the iomode_t bits of  the handle specified by `fd'.  This
 * function is used to implement various fcntl() and ioctl() codes.
 * >> omode = hand->h_mode;
 * >> hand->h_mode = (omode & mask) | value;
 * >> return omode;
 * Throws `E_INVALID_HANDLE_FILE_UNBOUND' for non-committed handles.
 * @param: mask:  Mask of mode bits to retain (unmasked bits are cleared)
 * @param: value: Mask of mode bits to add
 * @return: * :   The old handle mode
 * @throw: E_INVALID_HANDLE_FILE:E_INVALID_HANDLE_FILE_NEGATIVE:fd: `fd < 0'
 * @throw: E_INVALID_HANDLE_FILE:E_INVALID_HANDLE_FILE_ILLEGAL:fd:  `fd > self->hm_maxfd'
 * @throw: E_INVALID_HANDLE_FILE:E_INVALID_HANDLE_FILE_UNBOUND:fd:  [...] */
PUBLIC NONNULL((1)) iomode_t FCALL
handman_sethandflags(struct handman *__restrict self,
                     fd_t fd, iomode_t mask, iomode_t value)
		THROWS(E_WOULDBLOCK, E_INVALID_HANDLE_FILE) {
	iomode_t omode, nmode;
	unsigned int relfd;
	struct handrange *range;
	union handslot *slot;
	handman_write(self);

	/* Lookup handle. */
	range = handman_ranges_locate(self, (unsigned int)fd);
	if unlikely(!range)
		goto err_badfd;
	relfd = (unsigned int)fd - range->hr_minfd;
	if unlikely(!handrange_slotishand(range, relfd))
		goto err_badfd;
	slot  = &range->hr_hand[relfd];

	/* Change handle flags. */
	omode = slot->mh_hand.h_mode;
	nmode = (omode & mask) | value;
	slot->mh_hand.h_mode = nmode;
	if ((omode & IO_CLOEXEC) != (nmode & IO_CLOEXEC)) {
		if (nmode & IO_CLOEXEC) {
			ATOMIC_INC(range->hr_cexec);
		} else {
			ATOMIC_DEC(range->hr_cexec);
		}
	}
	if ((omode & IO_CLOFORK) != (nmode & IO_CLOFORK)) {
		if (nmode & IO_CLOFORK) {
			ATOMIC_INC(range->hr_cfork);
		} else {
			ATOMIC_DEC(range->hr_cfork);
		}
	}

	/* Cleanup... */
	handman_endwrite(self);
	if (omode != nmode)
		sig_broadcast(&self->hm_changed);
	return omode;
err_badfd:
	handman_unlock_and_throw_invalid_handle(self, fd, true);
}
PUBLIC NONNULL((1)) iomode_t FCALL
handman_gethandflags(struct handman *__restrict self, fd_t fd)
		THROWS(E_WOULDBLOCK, E_INVALID_HANDLE_FILE) {
	iomode_t result;
	unsigned int relfd;
	struct handrange *range;
	handman_read(self);

	/* Lookup handle. */
	range = handman_ranges_locate(self, (unsigned int)fd);
	if unlikely(!range)
		goto err_badfd;
	relfd = (unsigned int)fd - range->hr_minfd;
	if unlikely(!handrange_slotishand(range, relfd))
		goto err_badfd;
	result = range->hr_hand[relfd].mh_hand.h_mode;
	handman_endread(self);
	return result;
err_badfd:
	handman_unlock_and_throw_invalid_handle(self, fd, false);
}


/* Lookup the handle `fd' within `self', and store a reference in `*hand'
 * NOTE: A non-committed handle results in `E_INVALID_HANDLE_FILE_UNBOUND'
 * @return: hand: Always re-returns `hand'
 * @throw: E_INVALID_HANDLE_FILE:E_INVALID_HANDLE_FILE_NEGATIVE:fd: `fd < 0'
 * @throw: E_INVALID_HANDLE_FILE:E_INVALID_HANDLE_FILE_ILLEGAL:fd:  `fd > self->hm_maxfd'
 * @throw: E_INVALID_HANDLE_FILE:E_INVALID_HANDLE_FILE_UNBOUND:fd:  [...] */
PUBLIC ATTR_RETNONNULL NONNULL((1, 3)) REF struct handle *FCALL
handman_lookup(struct handman *__restrict self, fd_t fd,
               /*out*/ REF struct handle *__restrict hand)
		THROWS(E_WOULDBLOCK, E_INVALID_HANDLE_FILE) {
	unsigned int relfd;
	struct handrange *range;
	handman_read(self);
	range = handman_ranges_locate(self, (unsigned int)fd);
	if unlikely(!range)
		goto err_badfd;
	relfd = (unsigned int)fd - range->hr_minfd;
	if unlikely(!handrange_slotishand(range, relfd))
		goto err_badfd;
	hand = (REF struct handle *)memcpy(hand, &range->hr_hand[relfd].mh_hand,
	                                   sizeof(struct handle));
	handle_incref(*hand);
	handman_endread(self);
	return hand;
err_badfd:
	handman_unlock_and_throw_invalid_handle(self, fd, false);
}

/* Same as `handman_lookup()', but write `HANDLE_TYPE_UNDEFINED' in
 * case the given `fd' is negative or not bound to a kernel object,
 * or hasn't been committed. */
PUBLIC ATTR_RETNONNULL NONNULL((1, 3)) REF struct handle *FCALL
handman_trylookup(struct handman *__restrict self, fd_t fd,
                  /*out*/ REF struct handle *__restrict hand)
		THROWS(E_WOULDBLOCK) {
	unsigned int relfd;
	struct handrange *range;
	handman_read(self);
	range = handman_ranges_locate(self, (unsigned int)fd);
	if unlikely(!range)
		goto err_badfd;
	relfd = (unsigned int)fd - range->hr_minfd;
	if unlikely(!handrange_slotishand(range, relfd))
		goto err_badfd;
	hand = (REF struct handle *)memcpy(hand, &range->hr_hand[relfd].mh_hand,
	                                   sizeof(struct handle));
	handle_incref(*hand);
	handman_endread(self);
	return hand;
err_badfd:
	handman_endread(self);
	DBG_memset(hand, 0xcc, sizeof(*hand));
	hand->h_mode = 0;
	hand->h_type = HANDLE_TYPE_UNDEFINED;
	return hand;
}



/* Try to lookup the slot associated with `fd', or return `NULL'.
 * The caller must be holding a lock to `self' (either rd or  wr) */
PUBLIC WUNUSED NONNULL((1)) union handslot *
NOTHROW(FCALL handman_trylookup_slot)(struct handman *__restrict self, fd_t fd) {
	unsigned int relfd;
	struct handrange *range;
	assert(handman_reading(self));
	range = handman_ranges_locate(self, (unsigned int)fd);
	if unlikely(!range)
		goto err_badfd;
	relfd = (unsigned int)fd - range->hr_minfd;
	if unlikely(!handrange_slotishand(range, relfd))
		goto err_badfd;
	return &range->hr_hand[relfd];
err_badfd:
	return NULL;
}

PUBLIC ATTR_RETNONNULL WUNUSED NONNULL((1)) union handslot *FCALL
handman_lookup_slot_or_unlock_and_throw(struct handman *__restrict self, fd_t fd)
		THROWS(E_INVALID_HANDLE_FILE) {
	union handslot *result;
	result = handman_trylookup_slot(self, fd);
	if unlikely(!result)
		handman_unlock_and_throw_invalid_handle(self, fd, handman_writing(self));
	return result;
}





/* Close the handle `fd' within `self', and store its old contents in `*hand'
 * @return: ohand: Always re-returns `ohand'
 * @throw: E_INVALID_HANDLE_FILE:E_INVALID_HANDLE_FILE_NEGATIVE:fd: `fd < 0'
 * @throw: E_INVALID_HANDLE_FILE:E_INVALID_HANDLE_FILE_ILLEGAL:fd:  `fd > self->hm_maxfd'
 * @throw: E_INVALID_HANDLE_FILE:E_INVALID_HANDLE_FILE_UNBOUND:fd:  [...] */
PUBLIC ATTR_RETNONNULL NONNULL((1, 3)) REF struct handle *FCALL
handman_close(struct handman *__restrict self, fd_t fd,
              /*out*/ REF struct handle *__restrict ohand)
		THROWS(E_WOULDBLOCK, E_INVALID_HANDLE_FILE) {
	struct handrange *range;
	unsigned int relfd;
	handman_write(self);
	range = handman_ranges_locate(self, (unsigned int)fd);
	if unlikely(!range)
		goto err_badfd;
	relfd = (unsigned int)fd - range->hr_minfd;
	if unlikely(!handrange_slotishand(range, relfd))
		goto err_badfd;

	/* Copy information about the original handle. */
	memcpy(ohand, &range->hr_hand[relfd].mh_hand, sizeof(struct handle));
	DBG_memset(&range->hr_hand[relfd], 0xcc, sizeof(range->hr_hand[relfd]));
	range->hr_hand[relfd].mh_hand.h_type = HANDLE_TYPE_UNDEFINED;
	ATOMIC_DEC(self->hm_handles);
	if (ohand->h_mode & IO_CLOEXEC)
		ATOMIC_DEC(range->hr_cexec);
	if (ohand->h_mode & IO_CLOFORK)
		ATOMIC_DEC(range->hr_cfork);
	if (ATOMIC_READ(range->hr_nhint) > relfd)
		ATOMIC_WRITE(range->hr_nhint, relfd);

	/* If the close'd slot was the last one, trim trailing free slots. */
	if ((unsigned int)fd == range->hr_maxfd) {
		unsigned int count, trailing_free;
do_trim_trailing_slots:
		/* Count how many trailing free slots are in this range. */
		count = handrange_count(range);
		trailing_free = 1;
		while (trailing_free < count &&
		       handrange_slotisfree(range, count - (trailing_free + 1)))
			++trailing_free;
		if (trailing_free >= count) {
			/* Range became empty. --> Don't re-insert, but free */
free_empty_range:
			handman_ranges_removenode(self, range);
			assert(ATOMIC_READ(range->hr_nlops) == 0);
			assert(ATOMIC_READ(range->_hr_joinlop.olo_func) == NULL);
			assert(range->hr_cexec == 0);
			assert(range->hr_cfork == 0);
			handman_endwrite(self);
			_handrange_free(range);
			return ohand;
		}
		if (trailing_free > HANDRANGE_FREESLOTS_TRUNC_THRESHOLD) {
			size_t reqsize;
			handman_ranges_removenode(self, range);
			range->hr_maxfd -= trailing_free;
			count -= trailing_free;
			assert(count > 0);

			/* Reallocate to release unused memory. */
			reqsize = _handrange_sizeof(count);
			if (ATOMIC_READ(range->hr_nlops) != 0 ||
			    ATOMIC_READ(range->_hr_joinlop.olo_func) != NULL) {
				/* Can only do inplace-realloc */
				krealloc_in_place_nx(range, reqsize, GFP_ATOMIC);
			} else {
				struct handrange *temp;
				temp = (struct handrange *)krealloc_nx(range, reqsize, GFP_ATOMIC);
				if likely(temp)
					range = temp;
			}

			/* Re-insert the (now smaller) range. */
			handman_ranges_insert(self, range);
		}
	} else if ((unsigned int)fd == range->hr_minfd) {
do_trim_leading_slots:
		/* Trim unused leading slots (only possible when there are no LOP handles) */
		if (ATOMIC_READ(range->hr_nlops) == 0) {
			struct handrange *temp;
			size_t reqsize;
			unsigned int count;
			unsigned int leading_free;
			count = handrange_count(range);
			leading_free = 1;
			while (leading_free < count &&
			       handrange_slotisfree(range, leading_free))
				++leading_free;
			if unlikely(leading_free >= count)
				goto free_empty_range;
			if (leading_free > HANDRANGE_FREESLOTS_TRUNC_THRESHOLD) {
				handman_ranges_removenode(self, range);
				range->hr_minfd += leading_free;
				count -= leading_free;

				/* Move vector to reflect stripped entries. */
				memmovedown(&range->hr_hand[0], &range->hr_hand[leading_free],
				            count, sizeof(union handslot));

				/* Reallocate to release unused memory. */
				reqsize  = _handrange_sizeof(count);
				temp = (struct handrange *)krealloc_nx(range, reqsize, GFP_ATOMIC);
				if likely(temp)
					range = temp;

				/* Re-insert the (now smaller) range. */
				handman_ranges_insert(self, range);
			}
		}
	} else {
		/* The  close'd handle is somewhere in the middle of the range.
		 * Check if due to the handle's closure, a free-range  appeared
		 * consisting of at least `HANDRANGE_FREESLOTS_SPLIT_THRESHOLD'
		 * consecutive free slots. */
		unsigned int rel_freemin;
		unsigned int rel_freemax;
		unsigned int rel_maxslot;
		unsigned int freecount;
		rel_freemin = relfd;
		rel_freemax = relfd;
		rel_maxslot = range->hr_maxfd - range->hr_minfd;
		while (rel_freemin > 0 && handrange_slotisfree(range, rel_freemin - 1))
			--rel_freemin;
		while (rel_freemax < rel_maxslot && handrange_slotisfree(range, rel_freemax + 1))
			++rel_freemax;
		freecount = (rel_freemax - rel_freemin) + 1;
		/* Deal with special cases where someone left behind pre-allocated slots. */
		if unlikely(rel_freemax == rel_maxslot)
			goto do_trim_trailing_slots; /* Trim trailing slots. */
		if unlikely(rel_freemin == 0)
			goto do_trim_leading_slots; /* Trim leading slots. */
		if (freecount >= HANDRANGE_FREESLOTS_SPLIT_THRESHOLD) {
			struct handrange *temp;
			struct handrange *newrange = NULL;
			unsigned int hicount;
			size_t reqsize, avlsize;
again_handle_large_freecount:

			/* Yes: the free range _did_ become large enough to warren a range split!
			 * However, we mustn't do the  split if any of  the slots above the  free
			 * range are marked as  LOP handles! (though if  any below the split  are
			 * marked as lop handles, that  simply means we have to  realloc_in_place
			 * when truncating the buffer for what will become the lower bound of the
			 * free range) */
			if (ATOMIC_READ(range->hr_nlops) != 0 ||
			    ATOMIC_READ(range->_hr_joinlop.olo_func) != NULL) {
				/* There may be LOP slots above the free range. */
				unsigned int i;
				for (i = rel_freemax + 1; i <= rel_freemax; ++i) {
					if (_handslot_islop(&range->hr_hand[i])) {
						handman_endwrite(self);
						_handrange_free_unlikely(newrange);
						return ohand;
					}
				}
			}

			/* All right! -- Let's do this! */
			hicount = rel_maxslot - rel_freemax;
			reqsize = _handrange_sizeof(hicount);
			temp    = (struct handrange *)krealloc_nx(newrange, reqsize, GFP_ATOMIC);
			if (temp)
				newrange = temp;
			avlsize = kmalloc_usable_size(newrange);
			if (reqsize > avlsize) {
				handman_endwrite(self);
				temp = (struct handrange *)krealloc_nx(newrange, reqsize, GFP_NORMAL);
				if (temp)
					newrange = temp;
				avlsize = kmalloc_usable_size(newrange);
				if (reqsize > avlsize) {
free_newrange_and_done:
					_handrange_free(newrange);
					return ohand;
				}
				if (!handman_write_nx(self))
					goto free_newrange_and_done;
				/* Check if something changed. */
				range = handman_ranges_locate(self, (unsigned int)fd);
				if unlikely(!range) {
endwrite_and_free_newrange_and_done:
					handman_endwrite(self);
					goto free_newrange_and_done;
				}
				relfd = (unsigned int)fd - range->hr_minfd;
				if unlikely(!handrange_slotisfree(range, relfd))
					goto endwrite_and_free_newrange_and_done;
				rel_freemin = relfd;
				rel_freemax = relfd;
				rel_maxslot = range->hr_maxfd - range->hr_minfd;
				while (rel_freemin > 0 && handrange_slotisfree(range, rel_freemin - 1))
					--rel_freemin;
				while (rel_freemax < rel_maxslot && handrange_slotisfree(range, rel_freemax + 1))
					++rel_freemax;
				freecount = (rel_freemax - rel_freemin) + 1;
				/* Deal with special cases where someone left behind pre-allocated slots. */
				if unlikely(rel_freemax == rel_maxslot) {
					_handrange_free(newrange);
					goto do_trim_trailing_slots; /* Trim trailing slots. */
				}
				if unlikely(rel_freemin == 0) {
					_handrange_free(newrange);
					goto do_trim_leading_slots; /* Trim leading slots. */
				}
				if (freecount < HANDRANGE_FREESLOTS_SPLIT_THRESHOLD)
					goto endwrite_and_free_newrange_and_done;
				goto again_handle_large_freecount;
			}

			/* At this point we've got a buffer for the new high-range.
			 * -> Time to fill it in! */
			handman_ranges_removenode(self, range);
			newrange->hr_flags = HANDRANGE_F_NORMAL;
			newrange->hr_minfd = range->hr_minfd + rel_freemax + 1;
			newrange->hr_maxfd = range->hr_maxfd;
			newrange->hr_nhint = 0;
			newrange->hr_nlops = 0;
			newrange->hr_cexec = 0;
			newrange->hr_cfork = 0;
			assert(newrange->hr_minfd <= newrange->hr_maxfd);
			assert(handrange_count(newrange) == hicount);
			range->hr_maxfd = range->hr_minfd + rel_freemin - 1;
			assert(handrange_count(range) == rel_freemin);

			/* Transfer handle data. */
			memcpy(&newrange->hr_hand[0],
			       &range->hr_hand[rel_freemax + 1],
			       hicount, sizeof(union handslot));

			/* Update accounting for cexec/cfork handles. */
			if ((ATOMIC_READ(range->hr_cexec) != 0) ||
			    (ATOMIC_READ(range->hr_cfork) != 0)) {
				unsigned int i;
				for (i = 0; i < hicount; ++i) {
					iomode_t mode;
					if (!handrange_slotisused(newrange, i))
						continue;
					assertf(handrange_slotishand(newrange, i),
					        "There shouldn't be any LOP handles in here!");
					mode = newrange->hr_hand[i].mh_hand.h_mode;
					if (mode & IO_CLOEXEC) {
						ATOMIC_DEC(range->hr_cexec);
						++newrange->hr_cexec;
					}
					if (mode & IO_CLOFORK) {
						ATOMIC_DEC(range->hr_cfork);
						++newrange->hr_cfork;
					}
				}
			}

			/* Release unused memory from `range'. */
			reqsize = _handrange_sizeof(rel_freemin);
			if (ATOMIC_READ(range->hr_nlops) != 0 ||
			    ATOMIC_READ(range->_hr_joinlop.olo_func) != NULL) {
				/* Must use  inplace-realloc  if  there  are  LOP
				 * handles before the free-range we just removed. */
				krealloc_in_place_nx(range, reqsize, GFP_NORMAL);
			} else {
				temp = (struct handrange *)krealloc_nx(range, reqsize, GFP_NORMAL);
				if likely(temp)
					range = temp;
			}

			/* Insert the new ranges. */
			handman_ranges_insert(self, newrange);
			handman_ranges_insert(self, range);
		}
	}
	handman_endwrite(self);
	return ohand;
err_badfd:
	handman_unlock_and_throw_invalid_handle(self, fd, true);
}



/* Close all handles within the given range. */
PRIVATE NOBLOCK NONNULL((1, 2, 4, 6)) unsigned int
NOTHROW(FCALL handrange_clorange)(struct handrange *__restrict self,
                                  unsigned int *__restrict p_minfd, unsigned int maxfd,
                                  struct handle *__restrict decref_buf, size_t decref_siz,
                                  size_t *__restrict p_decref_len) {
	unsigned int result = 0;
	unsigned int minfd  = *p_minfd;
	assert(minfd >= self->hr_minfd && minfd <= self->hr_maxfd);
	minfd -= self->hr_minfd;
	maxfd -= self->hr_minfd;
	if (maxfd > self->hr_maxfd)
		maxfd = self->hr_maxfd;
	for (; minfd <= maxfd; ++minfd) {
		if (!handrange_slotishand(self, minfd))
			continue;
		if (*p_decref_len >= decref_siz)
			break; /* Need more buffer space. */
		/* Close this handle. */
		memcpy(&decref_buf[*p_decref_len], &self->hr_hand[minfd].mh_hand, sizeof(struct handle));
		if (self->hr_hand[minfd].mh_hand.h_mode & IO_CLOFORK)
			ATOMIC_DEC(self->hr_cfork);
		if (self->hr_hand[minfd].mh_hand.h_mode & IO_CLOEXEC)
			ATOMIC_DEC(self->hr_cexec);
		DBG_memset(&self->hr_hand[minfd].mh_hand, 0xcc, sizeof(self->hr_hand[minfd].mh_hand));
		self->hr_hand[minfd].mh_hand.h_type = HANDLE_TYPE_UNDEFINED;
		if (ATOMIC_READ(self->hr_nhint) > minfd)
			ATOMIC_WRITE(self->hr_nhint, minfd);
		++*p_decref_len;
		++result;
	}
	minfd += self->hr_minfd;
	*p_minfd = minfd;
	return result;
}

/* Close all open file descriptors within the given range.
 * @return: * : The number of closed files
 * @throw: E_INVALID_ARGUMENT_BAD_VALUE:E_INVALID_ARGUMENT_CONTEXT_CLOSE_RANGE_BADRANGE: [...] */
PUBLIC NONNULL((1)) unsigned int FCALL
handman_closerange(struct handman *__restrict self,
                   unsigned int minfd, unsigned int maxfd)
		THROWS(E_WOULDBLOCK, E_INVALID_ARGUMENT_BAD_VALUE) {
	unsigned int result = 0;
	struct handle *decref_buf;
	size_t decref_siz, decref_len;
	struct handrange *range;
	int has_preemption = -1;
	if unlikely(minfd > maxfd) {
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_CLOSE_RANGE_BADRANGE,
		      minfd, maxfd);
	}

	/* Enforce min/max bounds */
	if unlikely(minfd > (unsigned int)FD_MAX)
		return 0;
	if unlikely(maxfd > (unsigned int)FD_MAX)
		maxfd = (unsigned int)FD_MAX;
	assert(minfd <= maxfd);
	decref_siz = (maxfd - minfd) + 1;
	decref_len = get_stack_avail() / (2 * sizeof(struct handle));
	if (decref_siz > decref_len)
		decref_siz = decref_len;
	if (decref_siz > 1024)
		decref_siz = 1024;
	if (decref_siz < 16)
		decref_siz = 16;
	decref_buf = (struct handle *)alloca(decref_siz * sizeof(struct handle));
	decref_len = 0;
again_lock_and_findrange:
	handman_write(self);
again_findrange:
	while ((range = handman_firstrangeafter(self, minfd)) != NULL) {
		unsigned int part;
		part = handrange_clorange(range, &minfd, maxfd,
		                          decref_buf, decref_siz,
		                          &decref_len);
		if (part != 0) {
			assert(self->hm_handles >= part);
			ATOMIC_SUB(self->hm_handles, part);
			handrange_truncate_locked(range, self, true);
		}
		result += part;
		if (minfd > maxfd)
			break; /* We're done! */
		if (decref_len >= decref_siz)
			break; /*  */
	}
	if (has_preemption < 0)
		has_preemption = preemption_ison();

	/* If `handman_write(self)' might throw, don't release the lock. */
	if (has_preemption)
		handman_endwrite(self);

	/* Drop handle references. */
	while (decref_len) {
		--decref_len;
		handle_decref(decref_buf[decref_len]);
	}
	if (minfd <= maxfd) {
		/* We're got more work to do. */
		if (has_preemption)
			goto again_lock_and_findrange;
		goto again_findrange;
	} else if (!has_preemption) {
		handman_endwrite(self);
	}
	if (result != 0)
		sig_broadcast(&self->hm_changed);
	return result;
}



/* Set the IO_CLOEXEC flag for all open files within the given range.
 * @throw: E_INVALID_ARGUMENT_BAD_VALUE:E_INVALID_ARGUMENT_CONTEXT_CLOSE_RANGE_BADRANGE: [...] */
PUBLIC NONNULL((1)) void FCALL
handman_setcloexec_range(struct handman *__restrict self,
                         unsigned int minfd, unsigned int maxfd)
		THROWS(E_WOULDBLOCK, E_INVALID_ARGUMENT_BAD_VALUE) {
	bool changed;
	struct handrange *range;
	if unlikely(minfd > maxfd) {
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_CLOSE_RANGE_BADRANGE,
		      minfd, maxfd);
	}

	/* Enforce min/max bounds */
	if unlikely(minfd > (unsigned int)FD_MAX)
		return;
	if unlikely(maxfd > (unsigned int)FD_MAX)
		maxfd = (unsigned int)FD_MAX;
	assert(minfd <= maxfd);

	changed = false;
	handman_write(self);
	while ((range = handman_firstrangeafter(self, minfd)) != NULL) {
		unsigned int i, range_minfd, range_maxfd;
		range_minfd = range->hr_minfd;
		range_maxfd = range->hr_maxfd;
		if (range_minfd < minfd)
			range_minfd = minfd;
		if (range_maxfd > maxfd)
			range_minfd = maxfd;
		range_minfd -= range->hr_minfd;
		range_maxfd -= range->hr_minfd;
		assert(range_minfd <= range_maxfd);
		for (i = range_minfd; i <= range_maxfd; ++i) {
			if (!handrange_slotishand(range, i))
				continue; /* Unused/LOP slot */
			if (!(range->hr_hand[i].mh_hand.h_mode & IO_CLOEXEC)) {
				/* Mark as CLOEXEC */
				range->hr_hand[i].mh_hand.h_mode |= IO_CLOEXEC;
				ATOMIC_INC(range->hr_cexec);
				changed = true;
			}
		}
		minfd = range->hr_maxfd + 1;
		if (minfd > maxfd)
			break;
	}
	handman_endwrite(self);
	if (changed)
		sig_broadcast(&self->hm_changed);
}



/* Find the next handrange_slotishand handle in a slot >= fd
 * @param: p_data: When non-NULL, filled with the `h_data' field of the returned file.
 *                 This is used by procfs to generate INO numbers for `/proc/[pid]/fd'
 * @throw: E_INVALID_HANDLE_FILE:E_INVALID_HANDLE_FILE_UNBOUND:  No handle `>= fd' exists
 * @throw: E_INVALID_HANDLE_FILE:E_INVALID_HANDLE_FILE_ILLEGAL:  `fd > self->hm_maxfd'
 * @throw: E_INVALID_HANDLE_FILE:E_INVALID_HANDLE_FILE_NEGATIVE: `fd < 0' */
PUBLIC WUNUSED NONNULL((1)) fd_t FCALL
handman_findnext(struct handman *__restrict self, fd_t fd, void **p_data)
		THROWS(E_WOULDBLOCK, E_INVALID_HANDLE_FILE) {
	struct handrange *range;
	handman_read(self);

	/* Find the range which contains, or comes after `fd' */
nextrange:
	range = handman_firstrangeafter(self, (unsigned int)fd);
	if unlikely(!range)
		goto err_badfd;

	/* If `range' comes after `fd', set `fd' to point to the range's start. */
	if ((unsigned int)fd < range->hr_minfd)
		fd = (fd_t)range->hr_minfd;

	/* Scan ahead until the next valid FD. */
	for (;; ++fd) {
		if ((unsigned int)fd > range->hr_maxfd)
			goto nextrange;
		if (handrange_slotishand(range, (unsigned int)fd - range->hr_minfd))
			break;
	}

	/* Write-back the handle data pointer (if requested) */
	if (p_data != NULL)
		*p_data = range->hr_hand[(unsigned int)fd - range->hr_minfd].mh_hand.h_data;

	handman_endread(self);
	return fd;
err_badfd:
	handman_unlock_and_throw_invalid_handle(self, fd, false);
}



/* Find the next handrange_slotishand handle in a slot >= fd
 * @return: -1: One of the cases where `handman_findnext()' throws `E_INVALID_HANDLE_FILE' */
PUBLIC WUNUSED NONNULL((1)) fd_t FCALL
handman_tryfindnext(struct handman *__restrict self, fd_t fd, void **p_data)
		THROWS(E_WOULDBLOCK) {
	struct handrange *range;
	handman_read(self);

	/* Find the range which contains, or comes after `fd' */
nextrange:
	range = handman_firstrangeafter(self, (unsigned int)fd);
	if unlikely(!range)
		goto err_badfd;

	/* If `range' comes after `fd', set `fd' to point to the range's start. */
	if ((unsigned int)fd < range->hr_minfd)
		fd = (fd_t)range->hr_minfd;

	/* Scan ahead until the next valid FD. */
	for (;; ++fd) {
		if ((unsigned int)fd > range->hr_maxfd)
			goto nextrange;
		if (handrange_slotishand(range, (unsigned int)fd - range->hr_minfd))
			break;
	}

	/* Write-back the handle data pointer (if requested) */
	if (p_data != NULL)
		*p_data = range->hr_hand[(unsigned int)fd - range->hr_minfd].mh_hand.h_data;

	handman_endread(self);
	return fd;
err_badfd:
	handman_endread(self);
	return -1;
}


/* Install a handle into the given handle-range.
 * The caller must ensure that the associated slot isn't already in use,
 * as well as  to be holding  a lock to  the associated handle  manager. */
PRIVATE NOBLOCK NONNULL((1, 3)) void
NOTHROW(FCALL handrange_install_handle)(struct handrange *__restrict self, unsigned int relfd,
                                        struct handle const *__restrict nhand) {
	memcpy(&self->hr_hand[relfd].mh_hand, nhand, sizeof(struct handle));
	if (nhand->h_mode & IO_CLOFORK)
		ATOMIC_INC(self->hr_cfork);
	if (nhand->h_mode & IO_CLOEXEC)
		ATOMIC_INC(self->hr_cexec);
	handle_incref(*nhand);
}



/* Special return values for `handman_extendrange_or_unlock' */
#define HANDMAN_EXTENDRANGE_OR_UNLOCK_NORANGE  ((struct handrange *)0)
#define HANDMAN_EXTENDRANGE_OR_UNLOCK_UNLOCKED ((struct handrange *)-1)

/* Extend a neighboring range of `fd' to include `fd'.
 * @return: * : The range which now includes `fd'
 * @return: HANDMAN_EXTENDRANGE_OR_UNLOCK_NORANGE:  No range to extend was found.
 * @return: HANDMAN_EXTENDRANGE_OR_UNLOCK_UNLOCKED: Write-lock to `self' was released. -- Try again. */
PRIVATE NONNULL((1, 3)) struct handrange *FCALL
handman_extendrange_or_unlock(struct handman *__restrict self, unsigned int fd,
                              /*in|out*/ struct handrange **__restrict p_newrange) {
	struct handrange *range, *neighbor;
	unsigned int extend_minfd;
	unsigned int extend_maxfd;
	assert(!handman_ranges_locate(self, fd));

	/* Check +/- HANDRANGE_FREESLOTS_SPLIT_THRESHOLD around `fd' for pre-existing ranges
	 * If one is found, try to extend it (but only realloc if `hr_nlops == 0', though do
	 * try realloc_inplace() if the range is preceding). */
	if (OVERFLOW_USUB(fd, HANDRANGE_FREESLOTS_SPLIT_THRESHOLD, &extend_minfd))
		extend_minfd = 0;
	extend_maxfd = fd + HANDRANGE_FREESLOTS_SPLIT_THRESHOLD;

	/* Find some handrange that overlaps with the range
	 * in  which  we  want to  extend  existing ranges. */
	range = handman_ranges_rlocate(self, extend_minfd, extend_maxfd);
	if (!range)
		return HANDMAN_EXTENDRANGE_OR_UNLOCK_NORANGE;

	/* We always want the range directly before the gap. */
again_check_for_neighbor:
	if (fd < range->hr_minfd) {
		neighbor = handman_ranges_prev(self, range);
		if (neighbor && extend_minfd <= neighbor->hr_maxfd) {
			range = neighbor;
			goto again_check_for_neighbor;
		}
	} else {
		neighbor = handman_ranges_next(self, range);
		if (neighbor && extend_minfd >= neighbor->hr_maxfd) {
			range = neighbor;
			goto again_check_for_neighbor;
		}
	}

	if (range->hr_maxfd < fd) {
		size_t reqsize, avlsize;
		struct handrange *newrange;

		/* Extend preceding range  upwards. Try realloc_inplace,  or normal  realloc
		 * based on `hr_nlops'. Also check kmalloc_usable_size() to see if the range
		 * may already be large enough. */

		/* First up: check if we should join 2 ranges */
		neighbor = handman_ranges_next(self, range);
		assert(!neighbor || fd < neighbor->hr_minfd);
		if (neighbor && extend_maxfd >= neighbor->hr_minfd &&
		    /* NOTE: The read order of the following 2 is important! */
		    ATOMIC_READ(neighbor->hr_nlops) == 0 &&
		    ATOMIC_READ(neighbor->_hr_joinlop.olo_func) == NULL) {
			unsigned int i, dst, gap;
			/* Yes: try to merge `range' with `neighbor' */
			reqsize = _handrange_sizeof((neighbor->hr_maxfd - range->hr_minfd) + 1);
			krealloc_in_place_nx(range, reqsize, GFP_ATOMIC);
			avlsize = kmalloc_usable_size(range);
			if (avlsize < reqsize) {
				if (ATOMIC_READ(range->hr_nlops) != 0 ||
				    ATOMIC_READ(range->_hr_joinlop.olo_func) != NULL) {
					/* Not allowed to expand predecessor upwards, but
					 * maybe we can expand the successor downwards... */
try_expand_neighbor_downwards:
					if (!neighbor)
						return HANDMAN_EXTENDRANGE_OR_UNLOCK_NORANGE;
					range = neighbor;
					goto try_expand_downwards;
				}
				handman_ranges_removenode(self, range);
				newrange = (struct handrange *)krealloc_nx(range, reqsize, GFP_ATOMIC);
				if (newrange) {
					range   = newrange;
					avlsize = kmalloc_usable_size(range);
				}
				if (avlsize < reqsize) {
					size_t oldsize;
					/* Try to use the caller's in/out buffer range. */
					newrange = (struct handrange *)krealloc_nx(*p_newrange, reqsize, GFP_ATOMIC);
					if (!newrange)
						newrange = *p_newrange;
					*p_newrange = newrange;
					avlsize = kmalloc_usable_size(newrange);
					if (avlsize < reqsize) {
						handman_ranges_insert(self, range);
						handman_endwrite(self);
						*p_newrange = (struct handrange *)krealloc(newrange, reqsize, GFP_NORMAL);
						return HANDMAN_EXTENDRANGE_OR_UNLOCK_UNLOCKED;
					}
					*p_newrange = range; /* Gift the caller the original range */
					oldsize = _handrange_sizeof(handrange_count(range));
					range = (struct handrange *)memcpy(newrange, range, oldsize);
				}
			} else {
				handman_ranges_removenode(self, range);
			}

			/* Extend `range' to include a gap, as well as `neighbor' */
			handman_ranges_removenode(self, neighbor);
			dst = handrange_count(range);
			gap = neighbor->hr_minfd - (range->hr_maxfd + 1);
			if (ATOMIC_READ(range->hr_nhint) > dst)
				ATOMIC_WRITE(range->hr_nhint, dst);
			for (i = 0; i < gap; ++i, ++dst) {
				DBG_memset(&range->hr_hand[dst], 0xcc, sizeof(range->hr_hand[dst]));
				range->hr_hand[dst].mh_hand.h_type = HANDLE_TYPE_UNDEFINED;
			}
			memcpy(&range->hr_hand[dst], &neighbor->hr_hand[0],
			       handrange_count(neighbor), sizeof(union handslot));
			/* Update accounting of `range' */
			range->hr_maxfd = neighbor->hr_maxfd;
			ATOMIC_ADD(range->hr_cexec, neighbor->hr_cexec);
			ATOMIC_ADD(range->hr_cfork, neighbor->hr_cfork);
			handman_ranges_insert(self, range);
			_handrange_free_unlikely(*p_newrange); /* Free any buffer previously allocated */
			*p_newrange = neighbor;                /* Gift the caller the old neighbor */
			return range;
		} else {
			unsigned int i, more, dst;

			/* Only try to extend `range' itself. */
			reqsize = _handrange_sizeof((fd + 1) - range->hr_minfd);
			krealloc_in_place_nx(range, reqsize, GFP_ATOMIC);
			avlsize = kmalloc_usable_size(range);
			if (reqsize > avlsize) {
				/* Non-inplace expand only works if there are no LOP handles. */
				if (ATOMIC_READ(range->hr_nlops) != 0 ||
				    ATOMIC_READ(range->_hr_joinlop.olo_func) != NULL)
					goto try_expand_neighbor_downwards;
				handman_ranges_removenode(self, range);
				newrange = (struct handrange *)krealloc_nx(range, reqsize, GFP_ATOMIC);
				if (newrange) {
					range   = newrange;
					avlsize = kmalloc_usable_size(range);
				}
				if (reqsize > avlsize) {
					size_t oldsize;
					/* Try to use the caller's in/out buffer range. */
					newrange = (struct handrange *)krealloc_nx(*p_newrange, reqsize, GFP_ATOMIC);
					if (!newrange)
						newrange = *p_newrange;
					*p_newrange = newrange;
					avlsize = kmalloc_usable_size(newrange);
					if (avlsize < reqsize) {
						handman_ranges_insert(self, range);
						handman_endwrite(self);
						*p_newrange = (struct handrange *)krealloc(newrange, reqsize, GFP_NORMAL);
						return HANDMAN_EXTENDRANGE_OR_UNLOCK_UNLOCKED;
					}
					*p_newrange = range; /* Gift the caller the original range */
					oldsize = _handrange_sizeof(handrange_count(range));
					range = (struct handrange *)memcpy(newrange, range, oldsize);
				}
			} else {
				handman_ranges_removenode(self, range);
			}

			/* All right! -- We're allowed to do the insert. */
			dst  = handrange_count(range);
			more = fd - range->hr_maxfd;
			if (ATOMIC_READ(range->hr_nhint) > dst)
				ATOMIC_WRITE(range->hr_nhint, dst);
			for (i = 0; i < more; ++i, ++dst) {
				DBG_memset(&range->hr_hand[dst], 0xcc, sizeof(range->hr_hand[dst]));
				range->hr_hand[dst].mh_hand.h_type = HANDLE_TYPE_UNDEFINED;
			}

			/* Update range accounting. */
			range->hr_maxfd = fd;
			handman_ranges_insert(self, range);
			return range;
		}
		__builtin_unreachable();
	} else {
		size_t reqsize, avlsize;
		struct handrange *newrange;
		unsigned int i, oldcount, newcount, insert;
try_expand_downwards:
		assert(fd < range->hr_minfd);

		/* Extend succeeding range downwards. This only works if `hr_nlops == 0' */
		if (ATOMIC_READ(range->hr_nlops) != 0 ||
		    ATOMIC_READ(range->_hr_joinlop.olo_func) != NULL)
			return HANDMAN_EXTENDRANGE_OR_UNLOCK_NORANGE;

		handman_ranges_removenode(self, range);
		insert   = (range->hr_minfd - fd);
		oldcount = handrange_count(range);
		newcount = (range->hr_maxfd - fd) + 1;
		reqsize  = _handrange_sizeof(newcount);
		newrange = (struct handrange *)_handrange_realloc_nx(range, reqsize, GFP_ATOMIC);
		if (newrange)
			range = newrange;
		avlsize = kmalloc_usable_size(range);
		if (reqsize > avlsize) {
			/* Must allocate a larger range. */
			newrange = *p_newrange;
			avlsize  = kmalloc_usable_size(newrange);
			if (avlsize >= reqsize) {
				/* Copy everything into the new buffer, and give the caller the old range. */
				*p_newrange = range;
				range = (struct handrange *)memcpy(newrange, range, _handrange_sizeof(oldcount));
			} else {
				/* Must allocate a larger buffer while blocking. */
				handman_endwrite(self);
				*p_newrange = (struct handrange *)krealloc(newrange, reqsize, GFP_NORMAL);
				return HANDMAN_EXTENDRANGE_OR_UNLOCK_UNLOCKED;
			}
		}

		/* Update the range to include `fd' */
		memmoveup(&range->hr_hand[insert],
		          &range->hr_hand[0],
		          oldcount,
		          sizeof(union handslot));
		for (i = 0; i < insert; ++i) {
			DBG_memset(&range->hr_hand[i], 0xcc, sizeof(range->hr_hand[i]));
			range->hr_hand[i].mh_hand.h_type = HANDLE_TYPE_UNDEFINED;
		}
		ATOMIC_WRITE(range->hr_nhint, 0);
		range->hr_minfd = fd;
		handman_ranges_insert(self, range);
		return range;
	}
	__builtin_unreachable();
}


/* Install a given handle  under a specific handle  number.
 * Note that this function doesn't accept symbolic handles.
 * NOTE: When `fd' is a non-committed  handle, this function will block  until
 *       the associated handle slot is either committed, or rolled back before
 *       re-attempting to override it (hence the `BLOCKING').
 * @param: self: The handle manager in which to install `hand'
 * @param: fd:   The FD to override. (Symbolic handles not allowed)
 * @param: hand: The handle to install under `fd'
 * @return: fd:  Always re-returns `fd'
 * @throw: E_BADALLOC_INSUFFICIENT_HEAP_MEMORY:    Failed to allocate memory
 * @throw: E_BADALLOC_INSUFFICIENT_HANDLE_NUMBERS: `self->hm_handles >= self->hm_maxhand', and `fd' isn't allocated.
 * @throw: E_INVALID_HANDLE_FILE:E_INVALID_HANDLE_FILE_ILLEGAL:  `fd > self->hm_maxfd'
 * @throw: E_INVALID_HANDLE_FILE:E_INVALID_HANDLE_FILE_NEGATIVE: `fd < 0' */
PUBLIC BLOCKING NONNULL((1, 3, 4)) fd_t FCALL
handman_install_into(struct handman *__restrict self, fd_t fd,
                     struct handle const *__restrict nhand,
                     /*out*/ REF struct handle *__restrict ohand)
		THROWS(E_BADALLOC_INSUFFICIENT_HEAP_MEMORY,
		       E_BADALLOC_INSUFFICIENT_HANDLE_NUMBERS,
		       E_INVALID_HANDLE_FILE, E_WOULDBLOCK,
		       E_INTERRUPT) {
	struct handrange *range;
	assert(!task_wasconnected());
	assert(nhand->h_type != HANDLE_TYPE_UNDEFINED);
again_lock:
	handman_write(self);

	/* First up: check for a range that contains `fd' */
	range = handman_ranges_locate(self, (unsigned int)fd);
	if (range != NULL) {
		/* All right: so storage has already been allocated! */
		unsigned int relfd;
insert_into_range:
		relfd = (unsigned int)fd - range->hr_minfd;
again_check_slot:
		if (handrange_slotisfree(range, relfd)) {
			/* Slot wasn't in use already */
			if unlikely(self->hm_handles >= self->hm_maxhand) {
				handman_endwrite(self);
				THROW(E_BADALLOC_INSUFFICIENT_HANDLE_NUMBERS);
			}
			handrange_install_handle(range, relfd, nhand);
			ATOMIC_INC(self->hm_handles);
			handman_endwrite(self);
			sig_broadcast(&self->hm_changed);
			DBG_memset(ohand, 0xcc, sizeof(*ohand));
			ohand->h_mode = 0;
			ohand->h_type = HANDLE_TYPE_UNDEFINED;
			return fd;
		} else if (_handslot_islop(&range->hr_hand[relfd])) {
			/* Slot is a LOP -- wait for it to stop being one */
			task_connect(&self->hm_changed); /* NOTHROW, because first connection */
			COMPILER_READ_BARRIER();
			if unlikely(!_handslot_islop(&range->hr_hand[relfd])) {
				task_disconnectall();
				goto again_check_slot;
			}
			handman_endwrite(self);

			/* Wait for the handle to be committed (or rolled back) */
			task_waitfor();
			goto again_lock;
		} else {
			/* Slot is already in use. -- Override */
			memcpy(ohand, &range->hr_hand[relfd].mh_hand, sizeof(struct handle));
			memcpy(&range->hr_hand[relfd].mh_hand, nhand, sizeof(struct handle));

			/* Account for close-on-xxx flag changes. */
			if ((ohand->h_mode & O_CLOEXEC) != (nhand->h_mode & O_CLOEXEC)) {
				if (nhand->h_mode & O_CLOEXEC) {
					ATOMIC_INC(range->hr_cexec);
				} else {
					ATOMIC_DEC(range->hr_cexec);
				}
			}
			if ((ohand->h_mode & O_CLOFORK) != (nhand->h_mode & O_CLOFORK)) {
				if (nhand->h_mode & O_CLOFORK) {
					ATOMIC_INC(range->hr_cfork);
				} else {
					ATOMIC_DEC(range->hr_cfork);
				}
			}
			handle_incref(*nhand);
			handman_endwrite(self);
			sig_broadcast(&self->hm_changed);
			return fd;
		}
		__builtin_unreachable();
	}

	/* Validate that `fd' is allowed. */
	if unlikely((unsigned int)fd > self->hm_maxfd) {
		unsigned int reason, maxfd, useend;
		useend = handman_usefdend(self);
		maxfd  = self->hm_maxfd;
		handman_endwrite(self);
		reason = E_INVALID_HANDLE_FILE_ILLEGAL;
		if (fd < 0)
			reason = E_INVALID_HANDLE_FILE_NEGATIVE;
		THROW(E_INVALID_HANDLE_FILE, (syscall_slong_t)fd,
		      reason, useend, maxfd);
	}
	assertf(fd >= 0,
	        "This can only happen when hm_maxfd=%#x is greater "
	        "than INT_MAX, which it is not allowed to be set to.",
	        self->hm_maxfd);

	/* Slot hasn't been allocated, meaning we'll have to create it,
	 * meaning that the total handle  count will have to  increase. */
	if unlikely(self->hm_handles >= self->hm_maxhand) {
		handman_endwrite(self);
		THROW(E_BADALLOC_INSUFFICIENT_HANDLE_NUMBERS);
	}

	/* Look for another range in this widened search area. */
	{
		struct handrange *newrange;
		newrange = NULL;
again_extendrange:
		range = handman_extendrange_or_unlock(self, (unsigned int)fd, &newrange);
		if (range == HANDMAN_EXTENDRANGE_OR_UNLOCK_NORANGE) {
			_handrange_free_unlikely(newrange);
		} else if (range == HANDMAN_EXTENDRANGE_OR_UNLOCK_UNLOCKED) {
			TRY {
				handman_write(self);
			} EXCEPT {
				_handrange_free(newrange);
				RETHROW();
			}
			range = handman_ranges_locate(self, (unsigned int)fd);
			if unlikely(range != NULL)
				goto free_newrange_and_insert_into_range;
			goto again_extendrange;
		} else {
			assert((unsigned int)fd >= range->hr_minfd &&
			       (unsigned int)fd <= range->hr_maxfd);
free_newrange_and_insert_into_range:
			_handrange_free_unlikely(newrange);
			goto insert_into_range;
		}
	}

	/* Must create a totally new range consisting of a single element `fd'. */
	range = _handrange_alloc_nx(1, GFP_ATOMIC);
	if (range == NULL) {
		struct handrange *xrange;
		struct handrange *nrange;
		handman_endwrite(self);
		nrange = NULL;
		range  = _handrange_alloc(1, GFP_NORMAL);
again_lock_for_newrange:
		TRY {
			handman_write(self);
		} EXCEPT {
			_handrange_free_unlikely(nrange);
			_handrange_free(range);
			RETHROW();
		}

		/* Re-check that there are no pre-existing ranges for the other cases above. */
		xrange = handman_ranges_locate(self, (unsigned int)fd);
		if unlikely(xrange != NULL) {
			_handrange_free_unlikely(nrange);
			_handrange_free(range);
			range = xrange;
			goto insert_into_range;
		}

		/* Re-check extension of an existing range. */
		xrange = handman_extendrange_or_unlock(self, (unsigned int)fd, &nrange);
		if unlikely(xrange != HANDMAN_EXTENDRANGE_OR_UNLOCK_NORANGE) {
			if (xrange == HANDMAN_EXTENDRANGE_OR_UNLOCK_UNLOCKED)
				goto again_lock_for_newrange;
			assert((unsigned int)fd >= range->hr_minfd &&
			       (unsigned int)fd <= range->hr_maxfd);
			_handrange_free(nrange);
			_handrange_free(range);
			range = xrange;
			goto insert_into_range;
		}
		_handrange_free_unlikely(nrange);
	}

	/* Fill in the new, singular-element range. */
	range->hr_flags = HANDRANGE_F_NORMAL;
	range->hr_minfd = (unsigned int)fd;
	range->hr_maxfd = (unsigned int)fd;
	range->hr_nhint = 1;
	range->hr_nlops = 0;
	range->hr_cexec = nhand->h_mode & IO_CLOEXEC ? 1 : 0;
	range->hr_cfork = nhand->h_mode & IO_CLOFORK ? 1 : 0;
	DBG_memset(&range->_hr_joinlop, 0xcc, sizeof(range->_hr_joinlop));
	range->_hr_joinlop.olo_func = NULL; /* Mark as "inactive" */

	/* Install the initial handle. */
	memcpy(&range->hr_hand[0].mh_hand, nhand, sizeof(struct handle));
	handle_incref(*nhand);

	/* Insert the new range into the manager's range-tree. */
	handman_ranges_insert(self, range);

	/* Do accounting */
	ATOMIC_INC(self->hm_handles);
	handman_endwrite(self);
	sig_broadcast(&self->hm_changed);
	DBG_memset(ohand, 0xcc, sizeof(*ohand));
	ohand->h_mode = 0;
	ohand->h_type = HANDLE_TYPE_UNDEFINED;
	return fd;
}

PUBLIC BLOCKING NONNULL((1, 3)) fd_t FCALL
handman_install_into_simple(struct handman *__restrict self, fd_t fd,
                            struct handle const *__restrict nhand)
		THROWS(E_BADALLOC_INSUFFICIENT_HEAP_MEMORY,
		       E_BADALLOC_INSUFFICIENT_HANDLE_NUMBERS,
		       E_INVALID_HANDLE_FILE, E_WOULDBLOCK,
		       E_INTERRUPT) {
	fd_t result;
	struct handle ohand;
	result = handman_install_into(self, fd, nhand, &ohand);
	handle_decref(ohand); /* No-op if `HANDLE_TYPE_UNDEFINED' */
	return result;
}



PRIVATE ATTR_COLD ATTR_NORETURN NONNULL((1)) void FCALL
handman_endwrite_and_throw_invalid_handle_for_dupfd(struct handman *__restrict self,
                                                    fd_t fd)
		THROWS(E_INVALID_HANDLE_FILE) {
	unsigned int reason, maxfd, useend;
	useend = handman_usefdend(self);
	maxfd  = self->hm_maxfd;
	handman_endwrite(self);
	reason = E_INVALID_HANDLE_FILE_UNBOUND;
	if ((unsigned int)fd > maxfd)
		reason = E_INVALID_HANDLE_FILE_ILLEGAL_F_DUPFD;
	if (fd < 0)
		reason = E_INVALID_HANDLE_FILE_NEGATIVE;
	THROW(E_INVALID_HANDLE_FILE, (syscall_slong_t)fd, reason, useend, maxfd);
}




/* Special return values for `handman_joinranges_or_unlock' */
#define HANDMAN_JOINRANGES_OR_UNLOCK_UNABLE   HANDMAN_EXTENDRANGE_OR_UNLOCK_NORANGE
#define HANDMAN_JOINRANGES_OR_UNLOCK_UNLOCKED HANDMAN_EXTENDRANGE_OR_UNLOCK_UNLOCKED

/* Join adjacent ranges, or unlock `self'.
 * @return: * : The joined combination of `lorange' and `hirange'
 * @return: HANDMAN_JOINRANGES_OR_UNLOCK_UNABLE:   Unable to join ranges because of LOP handles
 * @return: HANDMAN_JOINRANGES_OR_UNLOCK_UNLOCKED: Lock to `self' was lost. (try again) */
PRIVATE WUNUSED NONNULL((1, 2, 3, 4)) struct handrange *FCALL
handman_joinranges_or_unlock(struct handman *__restrict self,
                             struct handrange *__restrict lorange,
                             struct handrange *__restrict hirange,
                             /*in|out*/ struct handrange **__restrict p_newrange) {
	unsigned int locount, hicount;
	size_t reqsize, avlsize;
	assert(lorange->hr_maxfd + 1 == hirange->hr_minfd);

	/* If the high range contains LOP handles, then merging is impossible. */
	if (ATOMIC_READ(hirange->hr_nlops) != 0 ||
	    ATOMIC_READ(hirange->_hr_joinlop.olo_func) != NULL)
		return HANDMAN_JOINRANGES_OR_UNLOCK_UNABLE;

	/* Figure our buffer requirements. */
	locount = handrange_count(lorange);
	hicount = handrange_count(hirange);
	reqsize = _handrange_sizeof(locount + hicount);
	avlsize = kmalloc_usable_size(lorange);
	if (kmalloc_usable_size(hirange) > avlsize &&
	    ATOMIC_READ(lorange->hr_nlops) == 0 &&
	    ATOMIC_READ(lorange->_hr_joinlop.olo_func) == NULL) {
		/* Rather than expand `lorange' upwards, expand `hirange' downwards. */
		struct handrange *newrange;
		handman_ranges_removenode(self, hirange);
		newrange = (struct handrange *)krealloc_nx(hirange, reqsize, GFP_ATOMIC);
		if (newrange)
			hirange = newrange;
		avlsize = kmalloc_usable_size(hirange);
		if (reqsize > avlsize) {
			/* Try to use `*p_newrange' */
			newrange = (struct handrange *)krealloc_nx(*p_newrange, reqsize, GFP_ATOMIC);
			if (!newrange)
				newrange = *p_newrange;
			*p_newrange = newrange;
			avlsize     = kmalloc_usable_size(newrange);
			if (reqsize > avlsize) {
				handman_ranges_insert(self, hirange);
				handman_endwrite(self);
				*p_newrange = (struct handrange *)krealloc(newrange, reqsize, GFP_NORMAL);
				return HANDMAN_JOINRANGES_OR_UNLOCK_UNLOCKED;
			}
			/* Replace `hirange' with the (large enough) `newrange' buffer */
			*p_newrange = hirange; /* Gift to the caller */
			hirange = (struct handrange *)memcpy(newrange, hirange, _handrange_sizeof(hicount));
		}

		/* Refactor `hirange' to make space for `lorange' */
		handman_ranges_removenode(self, hirange);
		memmoveup(&hirange->hr_hand[locount],
		          &hirange->hr_hand[0],
		          hicount, sizeof(union handslot));
		memcpy(&hirange->hr_hand[0],
		       &lorange->hr_hand[0],
		       locount, sizeof(union handslot));

		/* Update accounting. */
		hirange->hr_nhint += locount;
		if (hirange->hr_nhint > lorange->hr_nhint && lorange->hr_nhint < locount)
			hirange->hr_nhint = lorange->hr_nhint;
		hirange->hr_minfd = lorange->hr_minfd;
		hirange->hr_cexec += lorange->hr_cexec; /* non-atomic is OK because `hr_nlops == 0' */
		hirange->hr_cfork += lorange->hr_cfork; /* non-atomic is OK because `hr_nlops == 0' */

		/* Re-insert the (now-larger) `hirange' into the tree. */
		handman_ranges_insert(self, hirange);

		/* Cleanup. */
		_handrange_free(*p_newrange);
		*p_newrange = lorange;
		return hirange;
	}

	/* Try to inplace-realloc `lorange' for sufficient space. */
	handman_ranges_removenode(self, lorange);
	krealloc_in_place_nx(lorange, reqsize, GFP_ATOMIC);
	avlsize = kmalloc_usable_size(lorange);
	if (reqsize > avlsize) {
		struct handrange *newrange;
		if (ATOMIC_READ(lorange->hr_nlops) != 0 ||
		    ATOMIC_READ(lorange->_hr_joinlop.olo_func) != NULL) {
			/* Cannot join because of LOPs */
			handman_ranges_insert(self, lorange);
			reqsize = _handrange_sizeof(locount);
			krealloc_in_place_nx(lorange, reqsize, GFP_ATOMIC);
			return HANDMAN_JOINRANGES_OR_UNLOCK_UNABLE;
		}
		/* Try to realloc (non-inplace) `lorange' to become large enough. */
		newrange = (struct handrange *)krealloc_nx(lorange, reqsize, GFP_ATOMIC);
		if (newrange)
			lorange = newrange;
		avlsize = kmalloc_usable_size(lorange);
		if (reqsize > avlsize) {
			newrange = *p_newrange;
			newrange = (struct handrange *)krealloc_nx(newrange, reqsize, GFP_ATOMIC);
			if (!newrange)
				newrange = *p_newrange;
			*p_newrange = newrange;
			avlsize = kmalloc_usable_size(newrange);
			if (reqsize > avlsize) {
				struct handrange *temp;
				temp = (struct handrange *)krealloc_nx(lorange, _handrange_sizeof(locount), GFP_ATOMIC);
				if (temp)
					lorange = temp;
				handman_ranges_insert(self, lorange);
				handman_endwrite(self);
				*p_newrange = (struct handrange *)krealloc(newrange, reqsize, GFP_NORMAL);
				return HANDMAN_JOINRANGES_OR_UNLOCK_UNLOCKED;
			}
			/* Use `newrange' for everything. */
			*p_newrange = lorange; /* Gift to the caller. */
			lorange = (struct handrange *)memcpy(newrange, lorange, _handrange_sizeof(locount));
		}
	}

	/* Update accounting. */
	handman_ranges_removenode(self, lorange);
	handman_ranges_removenode(self, hirange);
	if (ATOMIC_READ(lorange->hr_nhint) > locount + hirange->hr_nhint)
		ATOMIC_WRITE(lorange->hr_nhint, locount + hirange->hr_nhint);
	ATOMIC_ADD(lorange->hr_cexec, hirange->hr_cexec); /* non-atomic in `hirange' OK because no LOPs */
	ATOMIC_ADD(lorange->hr_cfork, hirange->hr_cfork); /* non-atomic in `hirange' OK because no LOPs */
	lorange->hr_maxfd = hirange->hr_maxfd;
	memcpy(&lorange->hr_hand[locount],
	       &hirange->hr_hand[0],
	       hicount, sizeof(union handslot));

	/* Cleanup. */
	_handrange_free(*p_newrange);
	*p_newrange = hirange; /* Gift to the caller */
	return lorange;
}



/* Acquire locks and ensure that  `return->hr_hand[*p_relfd]'
 * is a free slot with an effective index that is `>= minfd'.
 * NOTE: This function already increments `hm_handles'! */
PRIVATE ATTR_RETNONNULL WUNUSED NONNULL((1, 3)) struct handrange *FCALL
handman_lock_and_alloc_for_install(struct handman *__restrict self, fd_t minfd,
                                   unsigned int *__restrict p_relfd)
		THROWS(E_BADALLOC_INSUFFICIENT_HEAP_MEMORY,
		       E_BADALLOC_INSUFFICIENT_HANDLE_NUMBERS,
		       E_INVALID_HANDLE_FILE, E_WOULDBLOCK) {
	unsigned int relfd, count;
	struct handrange *result, *next;
	struct handrange *newrange = NULL;
	RAII_FINALLY { _handrange_free_unlikely(newrange); };

again:
	handman_write(self);
	/* Check if we're allowed to create new handles, or we're already at/above the limit. */
	if unlikely(self->hm_handles >= self->hm_maxhand) {
		handman_endwrite(self);
		THROW(E_BADALLOC_INSUFFICIENT_HANDLE_NUMBERS);
	}

	/* Find the first range above `minfd' */
	if likely(minfd == 0) {
		result = handman_ranges_first(self);
	} else {
		result = handman_firstrangeafter(self, (unsigned int)minfd);
	}
	if (!result || (unsigned int)minfd < result->hr_minfd) {
		/* No range exists above  `minfd', or there is  an
		 * unmapped gap between `minfd' and its successor.
		 *
		 * -> Since we get here for invalid `minfd' values,
		 *    only check if  `minfd' is once  we get  here. */
		if unlikely((unsigned int)minfd > self->hm_maxfd)
			handman_endwrite_and_throw_invalid_handle_for_dupfd(self, minfd);
		assertf(minfd >= 0,
		        "This can only happen when hm_maxfd=%#x is greater "
		        "than INT_MAX, which it is not allowed to be set to.",
		        self->hm_maxfd);

		/* Try to expand another, existing range. */
		result = handman_extendrange_or_unlock(self, (unsigned int)minfd, &newrange);
		if (result == HANDMAN_EXTENDRANGE_OR_UNLOCK_UNLOCKED)
			goto again; /* Lock was lost --> try again */
		if (result != HANDMAN_EXTENDRANGE_OR_UNLOCK_NORANGE)
			goto handle_existing_range; /* Insert into newly expanded range! */

		relfd = (unsigned int)minfd;
create_new_range_for_relfd:
		/* Allocate a new range. */
		result = _handrange_alloc_nx(1, GFP_ATOMIC);
		if (!result) {
			struct handrange *existing_range;
			handman_endwrite(self);
			result = _handrange_alloc(1, GFP_NORMAL);
			TRY {
				handman_write(self);
			} EXCEPT {
				_handrange_free(result);
				RETHROW();
			}
			if unlikely(self->hm_handles >= self->hm_maxhand) {
				handman_endwrite(self);
				_handrange_free(result);
				THROW(E_BADALLOC_INSUFFICIENT_HANDLE_NUMBERS);
			}
			if (minfd == 0) {
				existing_range = handman_ranges_first(self);
			} else {
				existing_range = handman_firstrangeafter(self, (unsigned int)minfd);
			}
			if unlikely(existing_range != NULL) {
				_handrange_free(result);
				result = existing_range;
				goto handle_existing_range;
			}
		}

		/* Fill in the new range. */
		result->hr_flags = HANDRANGE_F_NORMAL;
		result->hr_minfd = relfd;
		result->hr_maxfd = relfd;
		result->hr_nhint = 1; /* First slot will be used */
		result->hr_nlops = 0;
		result->hr_cexec = 0;
		result->hr_cfork = 0;
		DBG_memset(&result->_hr_joinlop, 0xcc, sizeof(result->_hr_joinlop));
		result->_hr_joinlop.olo_func = NULL;
		DBG_memset(&result->hr_hand[0], 0xcc, sizeof(result->hr_hand[0]));
		result->hr_hand[0].mh_hand.h_type = HANDLE_TYPE_UNDEFINED;
		*p_relfd = 0;

		/* Insert the new range into the tree. */
		handman_ranges_insert(self, result);
		ATOMIC_INC(self->hm_handles);
		return result;
	}
handle_existing_range:

	/* Search for unused slots within this range. */
insert_into_result:
	relfd = ATOMIC_READ(result->hr_nhint);
	if unlikely((unsigned int)minfd > result->hr_minfd) {
		/* We must only consider free slots above the caller-given `minfd' */
		unsigned int temp;
		temp = (unsigned int)minfd - result->hr_minfd;
		if (relfd < temp)
			relfd = temp;
	}
	count = handrange_count(result);
	if (relfd < count) {
		while (relfd < count) {
			if (handrange_slotisfree(result, relfd)) {
				/* Found a free slot! */
				ATOMIC_WRITE(result->hr_nhint, relfd + 1);
				*p_relfd = relfd;
				ATOMIC_INC(self->hm_handles);
				return result;
			}
			++relfd;
		}
		/* Remember that all slots are in use */
		ATOMIC_WRITE(result->hr_nhint, relfd);
	}

	/* This range is fully allocated. -- Check the next one */
	next = handman_ranges_next(self, result);
	if (next) {
		assert(next->hr_minfd >= result->hr_maxfd + 1);
		if (next->hr_minfd <= result->hr_maxfd + 1) {
			/* Next range is adjacent (try merge the two of them) */
			result = handman_joinranges_or_unlock(self, result, next, &newrange);
			if (result == HANDMAN_JOINRANGES_OR_UNLOCK_UNLOCKED)
				goto again; /* Lock was lost --> try again */
			if (result == HANDMAN_JOINRANGES_OR_UNLOCK_UNABLE)
				result = next; /* Unable to merge. --> Just insert into `next' */
			goto insert_into_result;
		}
	}

	/* Extend `result' (and possibly join it with `next') */
	relfd  = result->hr_maxfd + 1;
	result = handman_extendrange_or_unlock(self, relfd, &newrange);
	if (result == HANDMAN_EXTENDRANGE_OR_UNLOCK_UNLOCKED)
		goto again; /* Lock was lost --> try again */
	if (result == HANDMAN_EXTENDRANGE_OR_UNLOCK_NORANGE)
		goto create_new_range_for_relfd; /* Cannot extend existing ranges --> create a new one */

	/* Was able to extend ranges, so now `result' should contain free slots.
	 * -> Find those slots and use them. */
	goto insert_into_result;
}


/* A simplified version  of `handman_install_begin()' +  `handman_install_commit()',
 * that skips the allocated+not-assigned handle step by installing the actual handle
 * from the get-go (in such a way that at no point is there a handle that cannot  be
 * close(2)'d, but still cannot be dup2(2)'d into without blocking).
 * @param: minfd: Lowest FD which may be returned (s.a. `fcntl(F_DUPFD)')
 * @return: * :   The file descriptor number that was allocated.
 * @throw: E_BADALLOC_INSUFFICIENT_HEAP_MEMORY:    Failed to allocate memory
 * @throw: E_BADALLOC_INSUFFICIENT_HANDLE_NUMBERS: `self->hm_handles >= self->hm_maxhand'
 * @throw: E_INVALID_HANDLE_FILE:E_INVALID_HANDLE_FILE_ILLEGAL_F_DUPFD: `minfd > self->hm_maxfd'
 * @throw: E_INVALID_HANDLE_FILE:E_INVALID_HANDLE_FILE_NEGATIVE:        `minfd < 0'
 * @throw: E_WOULDBLOCK: [...] */
PUBLIC WUNUSED NONNULL((1, 2)) fd_t FCALL
handman_install(struct handman *__restrict self,
                struct handle const *__restrict hand,
                fd_t minfd)
		THROWS(E_BADALLOC_INSUFFICIENT_HEAP_MEMORY,
		       E_BADALLOC_INSUFFICIENT_HANDLE_NUMBERS,
		       E_INVALID_HANDLE_FILE, E_WOULDBLOCK) {
	fd_t result;
	struct handle *dest;
	struct handrange *range;
	unsigned int relfd;

	/* Allocate a slot. */
	range  = handman_lock_and_alloc_for_install(self, minfd, &relfd);
	result = range->hr_minfd + relfd;
	dest   = &range->hr_hand[relfd].mh_hand;

	/* Install the handle. */
	memcpy(dest, hand, sizeof(struct handle));
	handle_incref(*dest);
	if (dest->h_mode & IO_CLOEXEC)
		ATOMIC_INC(range->hr_cexec);
	if (dest->h_mode & IO_CLOFORK)
		ATOMIC_INC(range->hr_cfork);

	/* Release locks. */
	handman_endwrite(self);
	return result;
}



/* Preserve a file descriptor slot to which the caller may either
 * commit  a kernel object, or roll back its installation in case
 * of an error during the object's creation.
 *
 * This 2-step process (including the ability of knowing what  will
 * eventually  become the object's  initial file descriptor number)
 * makes it possible to prevent race conditions relating to objects
 * being created before needing to  be destroyed when it turns  out
 * that installing them isn't possible.
 *
 * @param: self:  The handle manager to which to install
 * @param: data:  Handle installation data. (filled in)
 *                This data _must_ be finalized via a call to one of:
 *                 - handman_install_commit()
 *                 - handman_install_rollback()
 *                ... both of which are NOBLOCK+NOTHROW and may therefor
 *                be called after any other object-specific point-of-no-
 *                return control-flow position.
 * @param: minfd: Lowest FD which may be returned (s.a. `fcntl(F_DUPFD)')
 * @return: * :   The file descriptor number that was allocated.
 * @throw: E_BADALLOC_INSUFFICIENT_HEAP_MEMORY:    Failed to allocate memory
 * @throw: E_BADALLOC_INSUFFICIENT_HANDLE_NUMBERS: `self->hm_handles >= self->hm_maxhand'
 * @throw: E_INVALID_HANDLE_FILE:E_INVALID_HANDLE_FILE_ILLEGAL_F_DUPFD: `minfd > self->hm_maxfd'
 * @throw: E_INVALID_HANDLE_FILE:E_INVALID_HANDLE_FILE_NEGATIVE:        `minfd < 0'
 * @throw: E_WOULDBLOCK: [...] */
PUBLIC WUNUSED NONNULL((1)) fd_t FCALL
_handman_install_begin(struct handle_install_data *__restrict data, fd_t minfd)
		THROWS(E_BADALLOC_INSUFFICIENT_HEAP_MEMORY,
		       E_BADALLOC_INSUFFICIENT_HANDLE_NUMBERS,
		       E_INVALID_HANDLE_FILE, E_WOULDBLOCK) {
	fd_t result;
	struct handrange *range;
	unsigned int relfd;

	/* Allocate a slot. */
	range = handman_lock_and_alloc_for_install(data->hid_man, minfd, &relfd);

	/* Set-up the slot as `_MANHANDLE_LOADMARKER'. */
	result          = range->hr_minfd + relfd;
	data->hid_range = range;
	data->hid_slot  = &range->hr_hand[relfd];
	DBG_memset(data->hid_slot, 0xcc, sizeof(*data->hid_slot));
	data->hid_slot->mh_hand.h_type = _MANHANDLE_LOADMARKER;
	ATOMIC_INC(range->hr_nlops); /* Because we're a LOP handle. */

	/* Release locks. */
	handman_endwrite(data->hid_man);
	return result;
}


/* Commit installation of a handle (s.a. `_handslot_commit()') */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL _handman_install_commit_inherit)(struct handle_install_data *__restrict self,
                                               iomode_t h_mode, uintptr_half_t h_type) {
	_handslot_commit_inherit_with_preset_data(self->hid_man,
	                                          self->hid_range,
	                                          self->hid_slot,
	                                          h_mode, h_type);
}

/* Abort installation of a handle (s.a. `_handslot_rollback()') */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL handman_install_rollback)(struct handle_install_data *__restrict self) {
	_handslot_rollback(self->hid_man,
	                   self->hid_range,
	                   self->hid_slot);
}



/* Cache clearing hook for handle managers. */
INTERN NOBLOCK_IF(ccinfo_noblock(info)) NONNULL((1, 2)) void
NOTHROW(KCALL system_cc_perhman)(struct handman *__restrict self,
                                 struct ccinfo *__restrict info) {
	unsigned int minfd = 0;
	for (;;) {
		REF struct handle hand;
		struct handrange *range;
		if (!handman_tryread(self)) {
			if (ccinfo_noblock(info))
				return;
			if (!handman_read_nx(self))
				return;
		}

		/* Find the first handle with an index >= fdno */
		range = handman_firstrangeafter(self, minfd);
		if (!range) {
unlock_and_done:
			handman_endread(self);
			break;
		}
		/* TODO: Free unused slots from `range', as per:
		 *  - handrange_truncate_locked
		 *  - handrange_rejoin_locked
		 */
		for (;;) {
			if (handrange_slotishand(range, minfd - range->hr_minfd))
				break;
			++minfd;
			if (minfd > range->hr_maxfd) {
				range = handman_ranges_next(self, range);
				if (!range)
					goto unlock_and_done;
				assert(range->hr_minfd >= minfd);
				minfd = range->hr_minfd;
			}
		}

		/* Load the handle object. */
		memcpy(&hand,
		       &range->hr_hand[minfd - range->hr_minfd].mh_hand,
		       sizeof(struct handle));
		handle_incref(hand);
		handman_endread(self);

		/* Clear caches associated with the pointed-to object. */
		system_cc_handle(hand.h_type, hand.h_data, info);
		handle_decref(hand);
		if (ccinfo_isdone(info))
			break;
		++minfd;
	}
}

DECL_END

#endif /* !GUARD_KERNEL_SRC_FD_HANDMAN_C */
