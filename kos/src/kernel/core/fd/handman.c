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

#ifdef CONFIG_USE_NEW_HANDMAN
#include <kernel/handle.h>
#include <kernel/handman.h>
#include <kernel/malloc.h>
#include <kernel/user.h>

#include <hybrid/atomic.h>
#include <hybrid/overflow.h>
#include <hybrid/sequence/list.h>

#include <kos/except.h>
#include <kos/except/reason/inval.h>
#include <kos/lockop.h>

#include <assert.h>
#include <limits.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

DECL_BEGIN

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


/* Asynchronously try to rejoin `self' with its neighboring ranges.
 * This function uses `_hr_joinlop' in  case doing so would  block. */
PUBLIC NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL handrange_dec_nlops_and_maybe_rejoin)(struct handrange *__restrict self,
                                                    struct handman *__restrict man,
                                                    bool try_truncate_self) {
	/* TODO: Try to acquire a lock to `man' (on failure, use ATOMIC_CMPXCH on `_hr_joinlop' to create a lockop) */
	/* TODO: While holding the lock, do `ATOMIC_DECFECTCH(self->hr_nlops)', and remember if it dropped to `0' */
	/* TODO: When `try_truncate_self' is given, trim trailing `handrange_slotisfree()' slots. */
	/* TODO: When `try_truncate_self' is given and `hr_nlops == 0', trim leading `handrange_slotisfree()' slots (use memmove to shift downwards). */
	/* TODO: When `try_truncate_self' is given and slots were trimmed, update bounds of `self' and remove+re-insert into the tree.
	 *       Also do a realloc (inplace if `hr_nlops != 0') to free unused memory.
	 *       When the range before fully empty, simply remove from `man', free it, and return. */
	/* TODO: Check neighbors of `self' in `man' and try to merge with then.
	 *       Note that we must ensure that `self->hr_hand' isn't  realloc'd
	 *       when `hr_nlops != 0' */
	(void)man;
	(void)try_truncate_self;
	ATOMIC_DEC(self->hr_nlops);
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
	kfree(self);
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



/* Find an overly large sequence of free slots and return the sequence's
 * starting index. When  no such range  exists, return `count'  instead. */
PRIVATE NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) unsigned int
NOTHROW(FCALL find_overlarge_free_range)(union handslot const *__restrict base,
                                         unsigned int count) {
	unsigned int i, effective_count;
	if (OVERFLOW_USUB(count, HANDRANGE_FREESLOTS_SPLIT_THRESHOLD, &effective_count))
		return count;
	for (i = 0; i < effective_count;) {
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




struct handman_fork_data {
	struct handrange *hfd_range;    /* [0..1] Preallocated handle range. */
	unsigned int      hfd_nextfd;   /* Lowest FD number that must still be cloned */
	unsigned int      hfd_closemin; /* Lowest FD that must be close'd */
	unsigned int      hfd_closemax; /* Greatest FD that must be close'd */
};



/* NOTE: This function assumes that `dst' is freshly allocated and mustn't be locked/unlocked
 * NOTE: Upon error, this function releases a read-lock from `src'. */
PRIVATE NONNULL((1, 2, 3)) bool FCALL
handrange_clone_or_unlock(struct handman *__restrict dst,
                          struct handman *__restrict src,
                          struct handman_fork_data *__restrict data) {
#define UNLOCKALL() handman_endread(src)
	struct handrange *dstrange;
	struct handrange *srcrange;
	fd_t clone_minfd, clone_maxfd;
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
		srcrange = handman_ranges_rlocate(src, data->hfd_nextfd, (unsigned int)-1);
		if (srcrange) {
			/* Ensure that no other range must be cloned first! */
			struct handrange *prev;
			for (;;) {
				prev = handman_ranges_prev(src, srcrange);
				if (!prev)
					break;
				if (data->hfd_nextfd > (unsigned int)prev->hr_maxfd)
					break; /* This range was already cloned */
				srcrange = prev;
			}
		}
	}
	if (!srcrange)
		return true; /*  Everything was cloned! */

	/* Figure out which FDs to clone */
	clone_minfd = (fd_t)data->hfd_nextfd;
	if (clone_minfd < srcrange->hr_minfd)
		clone_minfd = srcrange->hr_minfd;
	clone_maxfd = srcrange->hr_maxfd;
	assert(clone_minfd <= clone_maxfd);

	/* Check if clone_minfd...clone_maxfd overlaps with the caller's clone-on-fork range. */
	if (RANGE_OVERLAPS((unsigned int)clone_minfd,
	                   (unsigned int)clone_maxfd,
	                   data->hfd_closemin,
	                   data->hfd_closemax)) {
		if ((unsigned int)clone_minfd < (unsigned int)data->hfd_closemin) {
			/* Clone range _BEFORE_ force-close area */
			clone_maxfd = (fd_t)data->hfd_closemin - 1;
		} else {
			/* Clone range _AFTER_ force-close area */
			clone_minfd = (fd_t)data->hfd_closemax + 1;
		}
		if ((unsigned int)clone_minfd > (unsigned int)clone_maxfd) {
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
	skip = (unsigned int)(clone_minfd - srcrange->hr_minfd);
	__builtin_expect(skip, 0);

	/* Fill in `dstrange' */
	dstrange->hr_nhint = srcrange->hr_nhint - skip;
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
	data->hfd_nextfd = (unsigned int)clone_maxfd + 1;

	/* Check for over-large gaps in `dstrange' */
	if (has_lop_handles || has_fork_handles) {
		/* `dstrange' may contain overly large gaps, or possibly even no handles at all.
		 * As such, we must trim unused slots and maybe even split the entire range into
		 * multiple smaller ones. */
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
#ifndef __OPTIMIZE_SIZE__
		if (leading_free)
#endif /* !__OPTIMIZE_SIZE__ */
		{
			clone_minfd += leading_free;
			clone_count -= leading_free;
			req_rangesize -= leading_free * sizeof(struct handle);
			memmovedown(&dstrange->hr_hand[0],
			            &dstrange->hr_hand[leading_free],
			            clone_count, sizeof(struct handle));
		}

		/* Trim trailing free slots */
		while ((assert(clone_count),
		        handrange_slotisfree(dstrange, clone_count - 1))) {
			--clone_count;
			req_rangesize -= sizeof(struct handle);
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
			data->hfd_nextfd = (unsigned int)clone_minfd;
			data->hfd_nextfd += new_clone_count;
			data->hfd_nextfd += HANDRANGE_FREESLOTS_SPLIT_THRESHOLD;
		}

		/* Delete next-free hint */
		dstrange->hr_nhint = 0;
	}

	/* Fill in remaining fields. */
	dstrange->hr_minfd = clone_minfd;
	dstrange->hr_maxfd = clone_maxfd;

	/* Acquire new references to cloned handles. */
	for (i = 0; i < clone_count; ++i) {
		/* HINT: `handle_incref()' is a no-op for HANDLE_TYPE_UNDEFINED! */
		handle_incref(dstrange->hr_hand[i].mh_hand);
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
		RAII_FINALLY { kfree(fdat.hfd_range); };

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
                            fd_t minfd, fd_t maxfd)
		THROWS(E_BADALLOC_INSUFFICIENT_HEAP_MEMORY,
		       E_WOULDBLOCK, E_INVALID_ARGUMENT_BAD_VALUE) {
	REF struct handman *result;

	/* Force min/max bounds (XXX: should we really do this?) */
	if unlikely(minfd < 0)
		minfd = 0;
	if unlikely(minfd > FD_MAX)
		minfd = FD_MAX;
	if unlikely(maxfd < 0)
		maxfd = 0;
	if unlikely(maxfd > FD_MAX)
		maxfd = FD_MAX;
	if unlikely(minfd > maxfd) {
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_CLOSE_RANGE_BADRANGE,
		      minfd, maxfd);
	}

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
		RAII_FINALLY { kfree(fdat.hfd_range); };

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
	/* TODO */
}

/* The handle manager of the kernel itself. */
PUBLIC struct handman handman_kernel = {
	/* TODO */
};

/* [1..1][lock(read(THIS_TASK || INTERN(lock)),
 *             write(THIS_TASK && INTERN(lock)))]
 * Handle manager of the calling thread. */
PUBLIC ATTR_PERTASK ATTR_ALIGN(struct handman *)
this_handman = &handman_kernel;


/* Return the handle manager of the given thread. */
PUBLIC NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct handman *
NOTHROW(FCALL task_gethandman)(struct task *__restrict thread) {
	/* TODO */
}

/* Exchange the handle manager of the calling thread (and return the old one). */
PUBLIC ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct handman *
NOTHROW(FCALL task_sethandman)(struct handman *__restrict newman) {
	/* TODO */
}





DECL_END
#endif /* CONFIG_USE_NEW_HANDMAN */

#endif /* !GUARD_KERNEL_SRC_FD_HANDMAN_C */
