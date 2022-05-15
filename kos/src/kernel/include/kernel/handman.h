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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_HANDMAN_H
#define GUARD_KERNEL_INCLUDE_KERNEL_HANDMAN_H 1

#include <kernel/compiler.h>

#include <kernel/handle.h>
#include <kernel/types.h>
#include <sched/sig.h>

#include <hybrid/sequence/rbtree.h>
#include <hybrid/sync/atomic-rwlock.h>

#include <kos/kernel/paging.h>
#include <kos/lockop.h>

#ifndef __INTELLISENSE__
#include <hybrid/pp/__va_nargs.h>
#endif /* !__INTELLISENSE__ */

#ifdef CONFIG_HANDMAN_USES_LLRBTREE
#undef CONFIG_HANDMAN_USES_RBTREE
#elif defined(CONFIG_HANDMAN_USES_RBTREE)
#undef CONFIG_HANDMAN_USES_LLRBTREE
#elif 1 /* Default: use RB-trees (slightly faster `ls /proc/pid/fd') */
#define CONFIG_HANDMAN_USES_RBTREE
#else /* ... */
#define CONFIG_HANDMAN_USES_LLRBTREE
#endif /* !... */

#ifdef __CC__
DECL_BEGIN

union handslot;
struct handrange;
struct handman;
struct openfd;
struct fnode;
struct fsuper;
struct task;
struct mfile;
struct fdirent;
struct path;
struct taskpid;
struct pipe;
struct driver;
struct socket;
struct epoll_controller;
struct filehandle;
struct dirhandle;
struct pipe_reader;
struct pipe_writer;
struct driver_state;
struct signalfd;
struct mfutexfd;
struct refcountable;


/* >> int __handleidof(T *expr)
 * Returns the HANDLE_TYPE_* code for the kernel object type  "T".
 * Causes a compiler error if "T" doesn't have a handle type code.
 * NOTE: Sub-classes of types with codes are handled correctly. */
#ifdef __cplusplus
extern "C++" {
struct __PRIVATE_handleidof_tag { };
template<class T> struct __PRIVATE_handleidof { };
#define __FOREACH_DEFINE_HANDLEIDOF(id, T)            \
	T operator,(T const &, __PRIVATE_handleidof_tag); \
	template<> struct __PRIVATE_handleidof<T> {       \
		enum { value = id };                          \
	};
HANDLE_FOREACH_TYPE(__FOREACH_DEFINE_HANDLEIDOF)
#undef __FOREACH_DEFINE_HANDLEIDOF
#define __handleidof(expr) (::__PRIVATE_handleidof<decltype((*(expr), ::__PRIVATE_handleidof_tag()))>::value)
} /* extern "C++" */
#endif /* __cplusplus */



/* Check if a  given `struct handle *self' is  actually
 * a handle, or  is simply a  `struct lockop'. This  is
 * used  for async-closing handles (as must be possible
 * in cases where open(2) fails after a handle has been
 * pre-allocated, but before  an object was  committed)
 *
 * Note that `_handle_islop()' can only ever be true for
 * handles within the  handle manager itself.  Functions
 * that  return handles automatically check for LOP IDs,
 * and return indicative of that ID not being  assigned,
 * with the  exception of  install-functions, which  act
 * as though the ID was actually assigned.
 *
 * In turn, this sort of  thing might lead to data  races
 * where a seemingly free handle ID cannot be re-assigned
 * when such should already be possible, but I don't  see
 * anything wrong with that, and the standards might even
 * allow it (though I don't care to find an actual answer
 * to this question)
 *
 * NOTE: With the exception of `_MANHANDLE_LOADMARKER', we
 *       don't  actually make use  of the lockop mechanism
 *       yet.  Especially since in  its current design, it
 *       would only work under KERNELSPACE_HIGHMEM! */
#ifdef KERNELSPACE_HIGHMEM
#define _HANDSLOT_LOP_MINTYPE (__CCAST(uintptr_half_t)(KERNELSPACE_BASE >> (__SIZEOF_POINTER__ * 4)))
#else /* KERNELSPACE_HIGHMEM */
#define _HANDSLOT_LOP_MINTYPE HANDLE_TYPE_COUNT
#endif /* !KERNELSPACE_HIGHMEM */


#define _handslot_islop(self)  ((self)->mh_hand.h_type >= _HANDSLOT_LOP_MINTYPE)
#define _handslot_ishand(self) (!_handslot_islop(self))

/* Special value for `mh_hand.h_type' that indicates a handle that has
 * been allocated, but not yet committed. It is possible to change the
 * type  of a handle from this to  the desired type without needing to
 * acquire a lock to the handle manager.
 * However, `hr_nlops' must be used to track how many such handles are
 * in some `struct handrange'. */
#define _MANHANDLE_LOADMARKER ((uintptr_half_t)-1)

#if HANDLE_TYPE_UNDEFINED == 0
#define __handletype_ishand(h_type) ((uintptr_half_t)((h_type)-1) < (_HANDSLOT_LOP_MINTYPE - 1))
#endif /* HANDLE_TYPE_UNDEFINED == 0 */
#define __handletype_isused(h_type) ((h_type) != HANDLE_TYPE_UNDEFINED)
#define __handletype_isfree(h_type) ((h_type) == HANDLE_TYPE_UNDEFINED)

union handslot {
	struct handle           mh_hand;     /* Handle data */
	Toblockop(handman)     _mh_lop;      /* Lock operator (currently unused) */
	Tobpostlockop(handman) _mh_plop;     /* Post-lock operator (currently unused) */
	void                  *_mh_words[2]; /* Raw data words. */
};

#define __handslot_makeword2(h_mode, h_type)          \
	((void *)(((uintptr_t)(uintptr_half_t)(h_mode)) | \
	          ((uintptr_t)(uintptr_half_t)(h_type) << (__SIZEOF_POINTER__ * 4))))

/* Determine the status of a given handle slot:
 *  - handslot_ishand: h_type != HANDLE_TYPE_UNDEFINED && _handslot_ishand
 *  - handslot_isused: h_type != HANDLE_TYPE_UNDEFINED
 *  - handslot_isfree: h_type == HANDLE_TYPE_UNDEFINED
 *  - handslot_forked: handslot_ishand && !IO_CLOFORK  (should the slot be retained during fork()?) */
#ifdef __handletype_ishand
#define handslot_ishand(self) __handletype_ishand((self)->mh_hand.h_type)
#else /* __handletype_ishand */
#define handslot_ishand(self) \
	(handslot_isused(self) && _handslot_ishand((self)->mh_hand.h_type))
#endif /* !__handletype_ishand */
#define handslot_isused(self) __handletype_isused((self)->mh_hand.h_type)
#define handslot_isfree(self) __handletype_isfree((self)->mh_hand.h_type)
#define handslot_forked(self) (handslot_ishand(self) && !((self)->mh_hand.h_mode & IO_CLOFORK))


/* When a `struct handrange' with this many consecutive `handslot_isfree()' slots
 * exists, that range should be split into  2 smaller ranges, the first of  which
 * ends at the free range, and the second of which starts after the free range.
 *
 * We  calculate this threshold quite intuitively as  the ceil'd # of the handles
 * that fit into the space needed for headers preceding the actual handle vector,
 * meaning that more than this # of consecutive free slots would be wasted space.
 *
 * Finally,  we add +2 just for good measure, and since we also want to optimize
 * for speed in regards to how many different ranges are pointed-to by the range
 * table of a `struct handman' */
#ifndef HANDRANGE_FREESLOTS_SPLIT_THRESHOLD
#define HANDRANGE_FREESLOTS_SPLIT_THRESHOLD            \
	(((__builtin_offsetof(struct handrange, hr_hand) + \
	   sizeof(struct handle) - 1) /                    \
	  sizeof(struct handle)) +                         \
	 2)
#endif /* !HANDRANGE_FREESLOTS_SPLIT_THRESHOLD */

/* Number of leading/trailing free slots before hand-ranges are truncated.
 * Note that once this threshold  is reached, _all_ leading/trailing  free
 * slots are freed, meaning that none will remain afterwards. -- This does
 * not specify how  many should  be left behind  during truncation,  which
 * always removes _all_ free slots.
 *
 * -> Truncation happens when `NUM_SLOTS > HANDRANGE_FREESLOTS_TRUNC_THRESHOLD',
 *    where  `NUM_SLOTS' is the # of leading  or trailing free-slots if a range.
 * -> This also doesn't affect ranges that became fully empty. For such a range
 *    it doesn't matter if it has less than HANDRANGE_FREESLOTS_TRUNC_THRESHOLD
 *    leading/trailing free slots. -- It is always deleted.
 * -> This limit is also ignored by `system_cc()', which (if it can) always
 *    trims _all_ leading/trailing free slots.
 */
#ifndef HANDRANGE_FREESLOTS_TRUNC_THRESHOLD
#define HANDRANGE_FREESLOTS_TRUNC_THRESHOLD 2
#endif /* !HANDRANGE_FREESLOTS_TRUNC_THRESHOLD */


/* Bits for `struct handrange::hr_flags' */
#define HANDRANGE_F_NORMAL 0x00000000 /* Normal flags. */
#define HANDRANGE_F_RED    0x00000001 /* FLAG: This range is a red node. */
#define _HANDRANGE_F_TRUNC 0x00000002 /* FLAG: The range will be truncated (used internally) */

struct handrange {
#ifdef CONFIG_HANDMAN_USES_RBTREE
	RBTREE_NODE(handrange)   hr_node;  /* [lock(:hm_lock)][0..1] Node in tree of handle ranges. */
#else /* CONFIG_HANDMAN_USES_RBTREE */
	LLRBTREE_NODE(handrange) hr_node;  /* [lock(:hm_lock)][0..1] Node in tree of handle ranges. */
#endif /* !CONFIG_HANDMAN_USES_RBTREE */
	uintptr_t                hr_flags; /* [lock(:hm_lock)] Set of `HANDRANGE_F_*' */
	unsigned int             hr_minfd; /* [lock(:hm_lock)] Min file descriptor contained by this range. */
	unsigned int             hr_maxfd; /* [lock(:hm_lock)] Max file descriptor contained by this range. */
	unsigned int             hr_nhint; /* [lock(INC(:hm_lock), DEC(ATOMIC))]
	                                    * Lowest FD (relative to `hr_minfd') which *may* be `HANDLE_TYPE_UNDEFINED'.
	                                    * When searching for free slots, we only consider slots above this  relative
	                                    * value, though due to race conditions, some may also exist below.
	                                    * NOTE: Must be considered invalid as `>= handrange_count()' */
	unsigned int             hr_nlops; /* [lock(INC(:hm_lock), DEC(ATOMIC))] Max # of lop-handles.
	                                    * When non-zero, the  range may not  be reallocated  (only
	                                    * inplace-realloc  is  allowed),  as  direct  pointers  to
	                                    * locations within this structure may exist.
	                                    * When  decremented to `0', you must try to join the range
	                                    * with its neighbors. For this, you may use `_hr_joinlop'. */
	/* NOTE: For the following two: less handles with  the relevant flag might exist, but  never
	 *       more. In other words: when either of these is `0', it is guarantied that no handles
	 *       with the relevant flag exist in `hr_hand'. Furthermore, these counters can only  be
	 *       incremented if `hr_nlops != 0' (or when  holding :hm_lock), meaning that if  you're
	 *       holding said lock and ensure `hr_nlops == 0', then these 2 values are [const] until
	 *       you release your lock. */
	unsigned int             hr_cexec; /* [lock(INC(:hm_lock || (hr_nlops != 0 && ATOMIC)), DEC(:hm_lock))]
	                                    * Upper bound for # of handles with IO_CLOEXEC */
	unsigned int             hr_cfork; /* [lock(INC(:hm_lock || (hr_nlops != 0 && ATOMIC)), DEC(:hm_lock))]
	                                    * Upper bound for # of handles with IO_CLOFORK */
	union { /* Lock operator (used by `hr_nlops') */
		Toblockop(handman)     _hr_joinlop;  /* [lock(ATOMIC && (WAS(.olo_func == NULL || CALLER_SET) && hr_nlops != 0))] */
		Tobpostlockop(handman) _hr_joinplop; /* [lock(ATOMIC && (WAS(.olo_func == NULL || CALLER_SET) && hr_nlops != 0))] */
	};
	/* [lock(:hm_lock || ATOMIC(TRANSITION([*].mh_hand.h_type, _MANHANDLE_LOADMARKER, HANDLE_TYPE_*)))]
	 * Vector handles defined by this range. */
	COMPILER_FLEXIBLE_ARRAY(union handslot, hr_hand);
};

#define _handrange_sizeof(num_handles)               (__builtin_offsetof(struct handrange, hr_hand) + (num_handles) * sizeof(union handslot))
#define _handrange_alloc_nx(num_handles, gfp)        ((struct handrange *)kmalloc_nx(_handrange_sizeof(num_handles), gfp))
#define _handrange_alloc(num_handles, gfp)           ((struct handrange *)kmalloc(_handrange_sizeof(num_handles), gfp))
#define _handrange_realloc_nx(ptr, num_handles, gfp) ((struct handrange *)krealloc_nx(ptr, _handrange_sizeof(num_handles), gfp))
#define _handrange_realloc(ptr, num_handles, gfp)    ((struct handrange *)krealloc(ptr, _handrange_sizeof(num_handles), gfp))
#define _handrange_free(ptr)                         kfree(ptr)
#define _handrange_free_unlikely(ptr)                kfree_unlikely(ptr)


/* Check if reallocation of `self' is currently allowed.
 * The caller  must be  holding  a lock  to  `:hm_lock'! */
#define handrange_canrealloc(self) \
	(__hybrid_atomic_load((self)->hr_nlops, __ATOMIC_ACQUIRE) == 0)

/* Return the # of handles contained in this handle-range's range. */
#define handrange_count(self) \
	(((self)->hr_maxfd - (self)->hr_minfd) + 1)

/* Determine the status of a given handle slot:
 *  - handrange_slotishand: h_type != HANDLE_TYPE_UNDEFINED && _handslot_ishand
 *  - handrange_slotisused: h_type != HANDLE_TYPE_UNDEFINED
 *  - handrange_slotisfree: h_type == HANDLE_TYPE_UNDEFINED
 *  - handrange_slotforked: handrange_slotishand && !IO_CLOFORK  (should the slot be retained during fork()?) */
#define handrange_slotishand(self, relative_fd) handslot_ishand(&(self)->hr_hand[relative_fd])
#define handrange_slotisused(self, relative_fd) handslot_isused(&(self)->hr_hand[relative_fd])
#define handrange_slotisfree(self, relative_fd) handslot_isfree(&(self)->hr_hand[relative_fd])
#define handrange_slotforked(self, relative_fd) handslot_forked(&(self)->hr_hand[relative_fd])

/* Set/clear flags in `self->hr_hand[relative_fd]' (caller must be holding `:hm_lock')
 * NOTE: The caller must still broadcast `:hm_changed' after using these functions! */
#define handrange_st_cloexec(self, relative_fd)                          \
	(((self)->hr_hand[relative_fd].mh_hand.h_mode & IO_CLOEXEC)          \
	 ? (void)0                                                           \
	 : (void)((self)->hr_hand[relative_fd].mh_hand.h_mode |= IO_CLOEXEC, \
	          __hybrid_atomic_inc((self)->hr_cexec, __ATOMIC_SEQ_CST)))
#define handrange_cl_cloexec(self, relative_fd)                           \
	(((self)->hr_hand[relative_fd].mh_hand.h_mode & IO_CLOEXEC)           \
	 ? (void)((self)->hr_hand[relative_fd].mh_hand.h_mode &= ~IO_CLOEXEC, \
	          __hybrid_atomic_dec((self)->hr_cexec, __ATOMIC_SEQ_CST))    \
	 : (void)0)
#define handrange_xl_cloexec(self, relative_fd)                 \
	((self)->hr_hand[relative_fd].mh_hand.h_mode ^= IO_CLOEXEC, \
	 ((self)->hr_hand[relative_fd].mh_hand.h_mode & IO_CLOEXEC) \
	 ? __hybrid_atomic_inc((self)->hr_cexec, __ATOMIC_SEQ_CST)  \
	 : __hybrid_atomic_dec((self)->hr_cexec, __ATOMIC_SEQ_CST))
#define handrange_st_clofork(self, relative_fd)                          \
	(((self)->hr_hand[relative_fd].mh_hand.h_mode & IO_CLOFORK)          \
	 ? (void)0                                                           \
	 : (void)((self)->hr_hand[relative_fd].mh_hand.h_mode |= IO_CLOFORK, \
	          __hybrid_atomic_inc((self)->hr_cfork, __ATOMIC_SEQ_CST)))
#define handrange_cl_clofork(self, relative_fd)                           \
	(((self)->hr_hand[relative_fd].mh_hand.h_mode & IO_CLOFORK)           \
	 ? (void)((self)->hr_hand[relative_fd].mh_hand.h_mode &= ~IO_CLOFORK, \
	          __hybrid_atomic_dec((self)->hr_cfork, __ATOMIC_SEQ_CST))    \
	 : (void)0)
#define handrange_xl_clofork(self, relative_fd)                 \
	((self)->hr_hand[relative_fd].mh_hand.h_mode ^= IO_CLOFORK, \
	 ((self)->hr_hand[relative_fd].mh_hand.h_mode & IO_CLOFORK) \
	 ? __hybrid_atomic_inc((self)->hr_cfork, __ATOMIC_SEQ_CST)  \
	 : __hybrid_atomic_dec((self)->hr_cfork, __ATOMIC_SEQ_CST))
#define handrange_setcloexec(self, relative_fd, new_cloexec_flag)                     \
	(((self)->hr_hand[relative_fd].mh_hand.h_mode & IO_CLOEXEC) == (new_cloexec_flag) \
	 ? (void)0                                                                        \
	 : (void)handrange_xl_cloexec(self, relative_fd))
#define handrange_setclofork(self, relative_fd, new_clofork_flag)                     \
	(((self)->hr_hand[relative_fd].mh_hand.h_mode & IO_CLOFORK) == (new_clofork_flag) \
	 ? (void)0                                                                        \
	 : (void)handrange_xl_clofork(self, relative_fd))
/* @param: new_clo_flags: Set of `IO_CLOEXEC | IO_CLOFORK' */
#define handrange_setcloflags(self, relative_fd, new_clo_flags)           \
	(handrange_setcloexec(self, relative_fd, (new_clo_flags)&IO_CLOEXEC), \
	 handrange_setclofork(self, relative_fd, (new_clo_flags)&IO_CLOFORK))


/* Safely install data into a given `union handslot *self', without ever  blocking.
 * This is the sequence of events that must happen in order to commit a handle that
 * had previously been reserved/allocated by a call to `handman_install_begin()'.
 *
 * Note that the order in which we update stuff here is extremely important:
 *  - First, we fill in the handle's data field. This could actually happen at any
 *    point  before the commit, as this field  doesn't have any meaning in regards
 *    to data ordering. However, if it needs to hold some sort of value, this must
 *    happen _before_ we fill in the second data word.
 *  - Then,  we must  update the cexec/cfork  fields, thus ensuring  that at no
 *    point in time will they be `0' when there is a non-zero amount of handles
 *    with the relevant flag.
 *  - The second data word contains the handle's type/mode. -- Only the type  is
 *    truly important here,  as it encodes  the fact that  the handle was  still
 *    marked  as `_MANHANDLE_LOADMARKER'. Once we write to this word, the handle
 *    will no longer be marked as such, meaning that once we write this word, we
 *    have no way of undoing this operation without blocking. And even then, the
 *    moment we do that write, the handle will become visible in /proc/pid/fd or
 *    other places that can access process handles.
 *  - Finally, we do some cleanup by  decrementing `hr_nlops'. This is a  counter
 *    for how many  handles are so-called  LOP-handles (s.a.  `_handslot_islop'),
 *    and  is used to prevent the range from being realloc'd. This is also a very
 *    special operation, as the moment we do the decrement, `range' may be free'd
 *    or realloc'd by another thread. However,  for the sake of cache  reduction,
 *    we also have to try and re-join a handle region with its neighbors whenever
 *    doing so becomes  allowed. (s.a.  `handrange_dec_nlops_and_maybe_rejoin()')
 *  - And lastly, we signify that handles changed.  -- This may be used for  any
 *    purpose what-so-ever, but the primary  consumer is `dup2()', which  blocks
 *    if the target handle is used by a LOP handle (which we just stopped being) */
#define _handslot_commit_inherit(man, range, self, data, mode, type)      \
	(__hybrid_atomic_store((self)->_mh_words[0], data, __ATOMIC_RELEASE), \
	 __handslot_commit_inherit(man, range, self, mode, type))
#define __handslot_commit_inherit(man, range, self, mode, type)                                       \
	(__hybrid_assert((self)->mh_hand.h_type == _MANHANDLE_LOADMARKER),                                \
	 ((mode)&IO_CLOEXEC) ? (void)__hybrid_atomic_inc((range)->hr_cexec, __ATOMIC_RELEASE) : (void)0,  \
	 ((mode)&IO_CLOFORK) ? (void)__hybrid_atomic_inc((range)->hr_cfork, __ATOMIC_RELEASE) : (void)0,  \
	 __hybrid_atomic_store((self)->_mh_words[1], __handslot_makeword2(mode, type), __ATOMIC_SEQ_CST), \
	 handrange_dec_nlops_and_maybe_rejoin(range, man, 0),                                             \
	 sig_broadcast(&(man)->hm_changed))

/* Similar to `_handslot_commit()', but rather than commit handles,
 * this  one is used to mark pre-allocated handles as unused. (such
 * as due to a failure  at installing/allocating the actual  handle
 * object) */
#define _handslot_abort(man, range, self)                                                                              \
	do {                                                                                                               \
		unsigned int _mha_ohint, _mha_nhint;                                                                           \
		__hybrid_assert((self)->mh_hand.h_type == _MANHANDLE_LOADMARKER);                                              \
		/*__hybrid_atomic_store((self)->_mh_words[0], INVALID_POINTER, __ATOMIC_RELEASE);*/                            \
		__hybrid_atomic_store((self)->_mh_words[1], __handslot_makeword2(0, HANDLE_TYPE_UNDEFINED), __ATOMIC_SEQ_CST); \
		_mha_nhint = (unsigned int)(size_t)((self) - (range)->hr_hand);                                                \
		/* Update `hr_nhint' to reflect our slot having become free. */                                                \
		do {                                                                                                           \
			_mha_ohint = __hybrid_atomic_load((range)->hr_nhint, __ATOMIC_ACQUIRE);                                    \
			if (_mha_ohint <= _mha_nhint)                                                                              \
				break; /* Only ever lower the hint; never raise it! */                                                 \
		} while (!__hybrid_atomic_cmpxch_weak((range)->hr_nhint, _mha_ohint, _mha_nhint,                               \
		                                      __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST));                                    \
		__hybrid_atomic_dec((man)->hm_handles, __ATOMIC_SEQ_CST);                                                      \
		handrange_dec_nlops_and_maybe_rejoin(range, man, 1);                                                           \
		sig_broadcast(&(man)->hm_changed);                                                                             \
	}	__WHILE0

/* Asynchronously try to rejoin `self' with its neighboring ranges.
 * This function uses `_hr_joinlop' in  case doing so would  block. */
FUNDEF NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL handrange_dec_nlops_and_maybe_rejoin)(struct handrange *__restrict self,
                                                    struct handman *__restrict man,
                                                    __BOOL try_truncate_self);


struct handman {
	WEAK refcnt_t            hm_refcnt;  /* Reference counter. */
	struct atomic_rwlock     hm_lock;    /* Lock for this handle manager. */
	Toblockop_slist(handman) hm_lops;    /* Lock operators for `hm_lock' */
#ifdef CONFIG_HANDMAN_USES_RBTREE
	RBTREE_ROOT(handrange)   hm_ranges;  /* [lock(hm_lock)][0..n] Root for the handle-range tree. */
#else /* CONFIG_HANDMAN_USES_RBTREE */
	LLRBTREE_ROOT(handrange) hm_ranges;  /* [lock(hm_lock)][0..n] Root for the handle-range tree. */
#endif /* !CONFIG_HANDMAN_USES_RBTREE */
	struct sig               hm_changed; /* Broadcast whenever:
	                                      *  - a handle is installed (both commit+abort)
	                                      *  - a handle is closed
	                                      *  - a handle is replaced
	                                      *  - a handle's h_mode is changed. */
	unsigned int             hm_handles; /* [lock(INC(hm_lock), DEC(ATOMIC))]
	                                      * Total # of non-HANDLE_TYPE_UNDEFINED handles. Due
	                                      * to race conditions, this may be greater than  the
	                                      * actual number of handles, but never less than it. */
	unsigned int             hm_maxhand; /* [lock(ATOMIC)] The max # of handles might may be
	                                      * allocated. When allocating new slots, the system
	                                      * checks that `(hm_handles + 1) <= hm_maxhand'. If
	                                      * not: E_BADALLOC_INSUFFICIENT_HANDLE_NUMBERS. */
	/*fd_t*/ unsigned int    hm_maxfd;   /* [lock(ATOMIC)] The max file descriptor number which
	                                      * may be assigned (in future operations). Usually set
	                                      * to  `INT_MAX'. Handles greater  than this (or those
	                                      * with negative numbers)  cannot be assigned,  though
	                                      * some have symbolic meaning (e.g. AT_FDCWD)
	                                      *
	                                      * This field must not be greater than INT_MAX! */
};

/* Destroy the given handle manager. */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL handman_destroy)(struct handman *__restrict self);
DEFINE_REFCNT_FUNCTIONS(struct handman, hm_refcnt, handman_destroy)

/* Helpers for accessing `hm_lock' */
#define _handman_reap(self)        _oblockop_reap_atomic_rwlock(&(self)->hm_lops, &(self)->hm_lock, self)
#define handman_reap(self)         oblockop_reap_atomic_rwlock(&(self)->hm_lops, &(self)->hm_lock, self)
#define handman_mustreap(self)     oblockop_mustreap(&(self)->hm_lops)
#define handman_write(self)        atomic_rwlock_write(&(self)->hm_lock)
#define handman_write_nx(self)     atomic_rwlock_write_nx(&(self)->hm_lock)
#define handman_trywrite(self)     atomic_rwlock_trywrite(&(self)->hm_lock)
#define handman_endwrite(self)     (atomic_rwlock_endwrite(&(self)->hm_lock), handman_reap(self))
#define _handman_endwrite(self)    atomic_rwlock_endwrite(&(self)->hm_lock)
#define handman_read(self)         atomic_rwlock_read(&(self)->hm_lock)
#define handman_read_nx(self)      atomic_rwlock_read_nx(&(self)->hm_lock)
#define handman_tryread(self)      atomic_rwlock_tryread(&(self)->hm_lock)
#define _handman_endread(self)     atomic_rwlock_endread(&(self)->hm_lock)
#define handman_endread(self)      (void)(atomic_rwlock_endread(&(self)->hm_lock) && (handman_reap(self), 0))
#define _handman_end(self)         atomic_rwlock_end(&(self)->hm_lock)
#define handman_end(self)          (void)(atomic_rwlock_end(&(self)->hm_lock) && (handman_reap(self), 0))
#define handman_upgrade(self)      atomic_rwlock_upgrade(&(self)->hm_lock)
#define handman_upgrade_nx(self)   atomic_rwlock_upgrade_nx(&(self)->hm_lock)
#define handman_tryupgrade(self)   atomic_rwlock_tryupgrade(&(self)->hm_lock)
#define handman_downgrade(self)    atomic_rwlock_downgrade(&(self)->hm_lock)
#define handman_reading(self)      atomic_rwlock_reading(&(self)->hm_lock)
#define handman_writing(self)      atomic_rwlock_writing(&(self)->hm_lock)
#define handman_canread(self)      atomic_rwlock_canread(&(self)->hm_lock)
#define handman_canwrite(self)     atomic_rwlock_canwrite(&(self)->hm_lock)
#define handman_waitread(self)     atomic_rwlock_waitread(&(self)->hm_lock)
#define handman_waitwrite(self)    atomic_rwlock_waitwrite(&(self)->hm_lock)
#define handman_waitread_nx(self)  atomic_rwlock_waitread_nx(&(self)->hm_lock)
#define handman_waitwrite_nx(self) atomic_rwlock_waitwrite_nx(&(self)->hm_lock)

/* For a given handle manager, creating a copy that no longer
 * contains any handles that had been marked as `IO_CLOFORK'.
 *
 * Additionally, handles that are currently being installed,
 * as per `handman_install_begin()' will _NOT_ be copied. Or
 * to be precise: any `_handslot_islop' handle is skipped. */
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct handman *FCALL
handman_fork(struct handman *__restrict self)
		THROWS(E_BADALLOC, E_WOULDBLOCK);

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
FUNDEF NONNULL((1)) void FCALL
handman_cloexec(struct handman *__restrict self)
		THROWS(E_WOULDBLOCK);

/* The handle manager of the kernel itself. */
DATDEF struct handman handman_kernel;

/* [1..1][lock(read(THIS_TASK || INTERN(lock)),
 *             write(THIS_TASK && INTERN(lock)))]
 * Handle manager of the calling thread. */
DATDEF ATTR_PERTASK struct handman *this_handman;
#define THIS_HANDMAN    PERTASK_GET(this_handman)

/* Return the handle manager of the given thread. */
FUNDEF NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct handman *
NOTHROW(FCALL task_gethandman)(struct task *__restrict thread);

/* Exchange the handle manager of the calling thread (and return the old one). */
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct handman *
NOTHROW(FCALL task_sethandman_inherit)(/*inherit(always)*/ REF struct handman *__restrict newman);
#define task_sethandman(newman) task_sethandman_inherit(incref(newman))


/* Returns the max used FD +1, or `0' if no FDs are in use
 * NOTE: The caller must be holding a lock to `self' */
FUNDEF NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) unsigned int
NOTHROW(FCALL handman_usefdend)(struct handman const *__restrict self);

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
FUNDEF NONNULL((1)) iomode_t FCALL
handman_sethandflags(struct handman *__restrict self,
                     fd_t fd, iomode_t mask, iomode_t value)
		THROWS(E_WOULDBLOCK, E_INVALID_HANDLE_FILE);
FUNDEF NONNULL((1)) iomode_t FCALL
handman_gethandflags(struct handman *__restrict self, fd_t fd)
		THROWS(E_WOULDBLOCK, E_INVALID_HANDLE_FILE);



/************************************************************************/
/* INTERNAL HANDRANGE ACCESS                                            */
/************************************************************************/
struct handrange_tree_minmax {
	struct handrange *mm_min; /* [0..1] Lowest branch. */
	struct handrange *mm_max; /* [0..1] Greatest branch. */
};

FUNDEF NOBLOCK ATTR_PURE WUNUSED struct handrange *NOTHROW(FCALL handrange_tree_locate)(/*nullable*/ struct handrange *root, unsigned int key);
FUNDEF NOBLOCK ATTR_PURE WUNUSED struct handrange *NOTHROW(FCALL handrange_tree_rlocate)(/*nullable*/ struct handrange *root, unsigned int minkey, unsigned int maxkey);
FUNDEF NOBLOCK NONNULL((1, 2)) void NOTHROW(FCALL handrange_tree_insert)(struct handrange **__restrict proot, struct handrange *__restrict node);
FUNDEF NOBLOCK NONNULL((1, 2)) void NOTHROW(FCALL handrange_tree_removenode)(struct handrange **__restrict proot, struct handrange *__restrict node);
#ifdef CONFIG_HANDMAN_USES_RBTREE
FUNDEF NOBLOCK WUNUSED NONNULL((1)) struct handrange *NOTHROW(FCALL handrange_tree_prevnode)(struct handrange const *__restrict self);
FUNDEF NOBLOCK WUNUSED NONNULL((1)) struct handrange *NOTHROW(FCALL handrange_tree_nextnode)(struct handrange const *__restrict self);
#else /* CONFIG_HANDMAN_USES_RBTREE */
FUNDEF NOBLOCK WUNUSED NONNULL((1, 2)) struct handrange *NOTHROW(FCALL handrange_tree_prevnode)(struct handrange *root, struct handrange const *self);
FUNDEF NOBLOCK WUNUSED NONNULL((1, 2)) struct handrange *NOTHROW(FCALL handrange_tree_nextnode)(struct handrange *root, struct handrange const *self);
#endif /* !CONFIG_HANDMAN_USES_RBTREE */
FUNDEF NOBLOCK NONNULL((4)) void NOTHROW(FCALL handrange_tree_minmaxlocate)(struct handrange *root, unsigned int minkey, unsigned int maxkey, struct handrange_tree_minmax *__restrict result);

#define handman_ranges_first(self)                       \
	__XBLOCK({                                           \
		struct handrange *__hrf_res = (self)->hm_ranges; \
		if likely(__hrf_res != __NULLPTR) {              \
			while (__hrf_res->hr_node.rb_lhs)            \
				__hrf_res = __hrf_res->hr_node.rb_lhs;   \
		}                                                \
		__XRETURN __hrf_res;                             \
	})
#define handman_ranges_last(self)                        \
	__XBLOCK({                                           \
		struct handrange *__hrf_res = (self)->hm_ranges; \
		if likely(__hrf_res != __NULLPTR) {              \
			while (__hrf_res->hr_node.rb_rhs)            \
				__hrf_res = __hrf_res->hr_node.rb_rhs;   \
		}                                                \
		__XRETURN __hrf_res;                             \
	})
#define handman_ranges_locate(self, key)                          handrange_tree_locate((self)->hm_ranges, key)
#define handman_ranges_rlocate(self, minkey, maxkey)              handrange_tree_rlocate((self)->hm_ranges, minkey, maxkey)
#define handman_ranges_insert(self, range)                        handrange_tree_insert(&(self)->hm_ranges, range)
#define handman_ranges_removenode(self, range)                    handrange_tree_removenode(&(self)->hm_ranges, range)
#define handman_ranges_minmaxlocate(self, minkey, maxkey, result) handrange_tree_minmaxlocate((self)->hm_ranges, minkey, maxkey, result)
#ifdef CONFIG_HANDMAN_USES_RBTREE
#define handman_ranges_prev(self, range) handrange_tree_prevnode(range)
#define handman_ranges_next(self, range) handrange_tree_nextnode(range)
#else /* CONFIG_HANDMAN_USES_RBTREE */
#define handman_ranges_prev(self, range) handrange_tree_prevnode((self)->hm_ranges, range)
#define handman_ranges_next(self, range) handrange_tree_nextnode((self)->hm_ranges, range)
#endif /* !CONFIG_HANDMAN_USES_RBTREE */
/************************************************************************/





/************************************************************************/
/* HIGH-LEVEL HANDLE OPERATIONS (SPECIFIC TO SOME HANDMAN)              */
/************************************************************************/

/* Lookup the handle `fd' within `self', and store a reference in `*hand'
 * NOTE: A non-committed handle results in `E_INVALID_HANDLE_FILE_UNBOUND'
 * @return: hand: Always re-returns `hand'
 * @throw: E_INVALID_HANDLE_FILE:E_INVALID_HANDLE_FILE_NEGATIVE:fd: `fd < 0'
 * @throw: E_INVALID_HANDLE_FILE:E_INVALID_HANDLE_FILE_ILLEGAL:fd:  `fd > self->hm_maxfd'
 * @throw: E_INVALID_HANDLE_FILE:E_INVALID_HANDLE_FILE_UNBOUND:fd:  [...] */
FUNDEF ATTR_RETNONNULL NONNULL((1, 3)) REF struct handle *FCALL
handman_lookup(struct handman *__restrict self, fd_t fd,
               /*out*/ REF struct handle *__restrict hand)
		THROWS(E_WOULDBLOCK, E_INVALID_HANDLE_FILE);

/* Same as `handman_lookup()', but write `HANDLE_TYPE_UNDEFINED' in
 * case the given `fd' is negative or not bound to a kernel object,
 * or hasn't been committed. */
FUNDEF ATTR_RETNONNULL NONNULL((1, 3)) REF struct handle *FCALL
handman_trylookup(struct handman *__restrict self, fd_t fd,
                  /*out*/ REF struct handle *__restrict hand)
		THROWS(E_WOULDBLOCK);

/* Try to lookup the slot associated with `fd', or return `NULL'.
 * The caller must be holding a lock to `self' (either rd or  wr) */
FUNDEF WUNUSED NONNULL((1)) union handslot *
NOTHROW(FCALL handman_trylookup_slot)(struct handman *__restrict self, fd_t fd);
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((1)) union handslot *FCALL
handman_lookup_slot_or_unlock_and_throw(struct handman *__restrict self, fd_t fd)
		THROWS(E_INVALID_HANDLE_FILE);

#ifdef __cplusplus
extern "C++" {
FORCELOCAL ATTR_ARTIFICIAL WUNUSED NONNULL((1)) REF struct handle FCALL
handman_lookup(struct handman *__restrict self, fd_t fd)
		THROWS(E_WOULDBLOCK, E_INVALID_HANDLE_FILE) {
	REF struct handle hand, *hptr;
	hptr = handman_lookup(self, fd, &hand);
	__builtin_assume(hptr == &hand);
	(void)hptr;
	return hand;
}
FORCELOCAL ATTR_ARTIFICIAL WUNUSED NONNULL((1)) REF struct handle FCALL
handman_trylookup(struct handman *__restrict self, fd_t fd)
		THROWS(E_WOULDBLOCK) {
	REF struct handle hand, *hptr;
	hptr = handman_trylookup(self, fd, &hand);
	__builtin_assume(hptr == &hand);
	(void)hptr;
	return hand;
}
} /* extern "C++" */
#endif /* __cplusplus */

/* Close the handle `fd' within `self', and store its old contents in `*hand'
 * @return: ohand: Always re-returns `ohand'
 * @throw: E_INVALID_HANDLE_FILE:E_INVALID_HANDLE_FILE_NEGATIVE:fd: `fd < 0'
 * @throw: E_INVALID_HANDLE_FILE:E_INVALID_HANDLE_FILE_ILLEGAL:fd:  `fd > self->hm_maxfd'
 * @throw: E_INVALID_HANDLE_FILE:E_INVALID_HANDLE_FILE_UNBOUND:fd:  [...] */
FUNDEF ATTR_RETNONNULL NONNULL((1, 3)) REF struct handle *FCALL
handman_close(struct handman *__restrict self, fd_t fd,
              /*out*/ REF struct handle *__restrict ohand)
		THROWS(E_WOULDBLOCK, E_INVALID_HANDLE_FILE);

/* Close all open file descriptors within the given range.
 * @return: * : The number of closed files
 * @throw: E_INVALID_ARGUMENT_BAD_VALUE:E_INVALID_ARGUMENT_CONTEXT_CLOSE_RANGE_BADRANGE: [...] */
FUNDEF NONNULL((1)) unsigned int FCALL
handman_closerange(struct handman *__restrict self,
                   unsigned int minfd, unsigned int maxfd)
		THROWS(E_WOULDBLOCK, E_INVALID_ARGUMENT_BAD_VALUE);

/* The combination of `handman_fork()' and `handman_closerange()'
 * @throw: E_INVALID_ARGUMENT_BAD_VALUE:E_INVALID_ARGUMENT_CONTEXT_CLOSE_RANGE_BADRANGE: [...] */
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct handman *FCALL
handman_fork_and_closerange(struct handman *__restrict self,
                            unsigned int minfd, unsigned int maxfd)
		THROWS(E_BADALLOC_INSUFFICIENT_HEAP_MEMORY,
		       E_WOULDBLOCK, E_INVALID_ARGUMENT_BAD_VALUE);

/* Set the IO_CLOEXEC flag for all open files within the given range.
 * @throw: E_INVALID_ARGUMENT_BAD_VALUE:E_INVALID_ARGUMENT_CONTEXT_CLOSE_RANGE_BADRANGE: [...] */
FUNDEF NONNULL((1)) void FCALL
handman_setcloexec_range(struct handman *__restrict self,
                         unsigned int minfd, unsigned int maxfd)
		THROWS(E_WOULDBLOCK, E_INVALID_ARGUMENT_BAD_VALUE);

/* Find the next handrange_slotishand handle in a slot >= fd
 * @param: p_data: When non-NULL, filled with the `h_data' field of the returned file.
 *                 This is used by procfs to generate INO numbers for `/proc/[pid]/fd'
 * @throw: E_INVALID_HANDLE_FILE:E_INVALID_HANDLE_FILE_UNBOUND:  No handle `>= fd' exists
 * @throw: E_INVALID_HANDLE_FILE:E_INVALID_HANDLE_FILE_ILLEGAL:  `fd > self->hm_maxfd'
 * @throw: E_INVALID_HANDLE_FILE:E_INVALID_HANDLE_FILE_NEGATIVE: `fd < 0' */
FUNDEF WUNUSED NONNULL((1)) fd_t FCALL
handman_findnext(struct handman *__restrict self,
                 fd_t fd, void **p_data DFL(__NULLPTR))
		THROWS(E_WOULDBLOCK, E_INVALID_HANDLE_FILE);

/* Find the next handrange_slotishand handle in a slot >= fd
 * @return: -1: One of the cases where `handman_findnext()' throws `E_INVALID_HANDLE_FILE' */
FUNDEF WUNUSED NONNULL((1)) fd_t FCALL
handman_tryfindnext(struct handman *__restrict self,
                    fd_t fd, void **p_data DFL(__NULLPTR))
		THROWS(E_WOULDBLOCK);

/* Install a given handle  under a specific handle  number.
 * Note that this function doesn't accept symbolic handles.
 * NOTE: When `fd' is a non-committed handle, this function will block until
 *       the associated handle slot is  either committed, or aborted  before
 *       re-attempting to override it (hence the `BLOCKING').
 * @param: self: The handle manager in which to install `hand'
 * @param: fd:   The FD to override. (Symbolic handles not allowed)
 * @param: hand: The handle to install under `fd'
 * @return: fd:  Always re-returns `fd'
 * @throw: E_BADALLOC_INSUFFICIENT_HEAP_MEMORY:    Failed to allocate memory
 * @throw: E_BADALLOC_INSUFFICIENT_HANDLE_NUMBERS: `self->hm_handles >= self->hm_maxhand', and `fd' isn't allocated.
 * @throw: E_INVALID_HANDLE_FILE:E_INVALID_HANDLE_FILE_ILLEGAL:  `fd > self->hm_maxfd'
 * @throw: E_INVALID_HANDLE_FILE:E_INVALID_HANDLE_FILE_NEGATIVE: `fd < 0' */
FUNDEF BLOCKING NONNULL((1, 3, 4)) fd_t FCALL
handman_install_into(struct handman *__restrict self, fd_t fd,
                     struct handle const *__restrict nhand,
                     /*out*/ REF struct handle *__restrict ohand)
		THROWS(E_BADALLOC_INSUFFICIENT_HEAP_MEMORY,
		       E_BADALLOC_INSUFFICIENT_HANDLE_NUMBERS,
		       E_INVALID_HANDLE_FILE, E_WOULDBLOCK,
		       E_INTERRUPT);
FUNDEF BLOCKING NONNULL((1, 3)) fd_t FCALL
handman_install_into_simple(struct handman *__restrict self, fd_t fd,
                            struct handle const *__restrict nhand)
		THROWS(E_BADALLOC_INSUFFICIENT_HEAP_MEMORY,
		       E_BADALLOC_INSUFFICIENT_HANDLE_NUMBERS,
		       E_INVALID_HANDLE_FILE, E_WOULDBLOCK,
		       E_INTERRUPT);
#ifdef __cplusplus
extern "C++" {
FUNDEF BLOCKING NONNULL((1, 4)) fd_t FCALL
handman_install_into(struct handman *__restrict self, fd_t fd,
                     struct handle const &__restrict nhand,
                     /*out*/ REF struct handle *__restrict ohand)
		THROWS(E_BADALLOC_INSUFFICIENT_HEAP_MEMORY,
		       E_BADALLOC_INSUFFICIENT_HANDLE_NUMBERS,
		       E_INVALID_HANDLE_FILE, E_WOULDBLOCK,
		       E_INTERRUPT)
		ASMNAME("handman_install_into");
FUNDEF BLOCKING NONNULL((1, 3)) fd_t FCALL
handman_install_into(struct handman *__restrict self, fd_t fd,
                     struct handle const *__restrict nhand)
		THROWS(E_BADALLOC_INSUFFICIENT_HEAP_MEMORY,
		       E_BADALLOC_INSUFFICIENT_HANDLE_NUMBERS,
		       E_INVALID_HANDLE_FILE, E_WOULDBLOCK,
		       E_INTERRUPT)
		ASMNAME("handman_install_into_simple");
FUNDEF BLOCKING NONNULL((1)) fd_t FCALL
handman_install_into(struct handman *__restrict self, fd_t fd,
                     struct handle const &__restrict nhand)
		THROWS(E_BADALLOC_INSUFFICIENT_HEAP_MEMORY,
		       E_BADALLOC_INSUFFICIENT_HANDLE_NUMBERS,
		       E_INVALID_HANDLE_FILE, E_WOULDBLOCK,
		       E_INTERRUPT)
		ASMNAME("handman_install_into_simple");
FUNDEF BLOCKING NONNULL((1)) fd_t FCALL
handman_install_into_simple(struct handman *__restrict self, fd_t fd,
                            struct handle const &__restrict nhand)
		THROWS(E_BADALLOC_INSUFFICIENT_HEAP_MEMORY,
		       E_BADALLOC_INSUFFICIENT_HANDLE_NUMBERS,
		       E_INVALID_HANDLE_FILE, E_WOULDBLOCK,
		       E_INTERRUPT)
		ASMNAME("handman_install_into_simple");
} /* extern "C++" */
#endif /* __cplusplus */


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
FUNDEF WUNUSED NONNULL((1, 2)) fd_t FCALL
handman_install(struct handman *__restrict self,
                struct handle const *__restrict hand,
                fd_t minfd DFL(0))
		THROWS(E_BADALLOC_INSUFFICIENT_HEAP_MEMORY,
		       E_BADALLOC_INSUFFICIENT_HANDLE_NUMBERS,
		       E_INVALID_HANDLE_FILE, E_WOULDBLOCK);
#ifdef __cplusplus
extern "C++" {
FUNDEF WUNUSED NONNULL((1)) fd_t FCALL
handman_install(struct handman *__restrict self,
                struct handle const &__restrict hand,
                fd_t minfd DFL(0))
		THROWS(E_BADALLOC_INSUFFICIENT_HEAP_MEMORY,
		       E_BADALLOC_INSUFFICIENT_HANDLE_NUMBERS,
		       E_INVALID_HANDLE_FILE, E_WOULDBLOCK)
		ASMNAME("handman_install");
} /* extern "C++" */
#endif /* __cplusplus */
/************************************************************************/





/************************************************************************/
/* 2-STEP HANDLE INSTALLATION API                                       */
/************************************************************************/
struct handle_install_data {
	struct handman   *hid_man;   /* [1..1][const] Handle manager. */
	struct handrange *hid_range; /* [1..1][const] Target range. */
	union handslot   *hid_slot;  /* [1..1][const] Target slot. */
};


/* Preserve a file descriptor slot to which the caller may either
 * commit a kernel object, or  abort its installation in case  of
 * an error during the object's creation.
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
 *                 - handman_install_abort()
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
#ifdef __INTELLISENSE__
FUNDEF WUNUSED NONNULL((1, 2)) fd_t FCALL
handman_install_begin(struct handman *__restrict self,
                      struct handle_install_data *__restrict data,
                      fd_t minfd DFL(0))
		THROWS(E_BADALLOC_INSUFFICIENT_HEAP_MEMORY,
		       E_BADALLOC_INSUFFICIENT_HANDLE_NUMBERS,
		       E_INVALID_HANDLE_FILE, E_WOULDBLOCK);
#else /* __INTELLISENSE__ */
#define handman_install_begin(self, data, ...) \
	((data)->hid_man = (self),                 \
	 _handman_install_begin(data, ##__VA_ARGS__))
#endif /* !__INTELLISENSE__ */
FUNDEF WUNUSED NONNULL((1)) fd_t FCALL
_handman_install_begin(struct handle_install_data *__restrict data,
                       fd_t minfd DFL(0))
		THROWS(E_BADALLOC_INSUFFICIENT_HEAP_MEMORY,
		       E_BADALLOC_INSUFFICIENT_HANDLE_NUMBERS,
		       E_INVALID_HANDLE_FILE, E_WOULDBLOCK);

/* Commit installation of a handle (s.a. `_handslot_commit()') */
#ifdef __INTELLISENSE__
FUNDEF NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL handman_install_commit)(struct handle_install_data *__restrict self,
                                      void *h_data, iomode_t h_mode, uintptr_half_t h_type);
FUNDEF NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL handman_install_commit_inherit)(struct handle_install_data *__restrict self,
                                              /*inherit(always)*/ REF void *h_data,
                                              iomode_t h_mode, uintptr_half_t h_type);
#ifdef __cplusplus
extern "C++" {
FUNDEF NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL handman_install_commit)(struct handle_install_data *__restrict self,
                                      struct handle const *__restrict hand);
FUNDEF NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL handman_install_commit_inherit)(struct handle_install_data *__restrict self,
                                              struct handle const *__restrict hand);
#define __FOREACH_HANDLES_INSTALL_COMMIT(id, T)                                                \
	FUNDEF NOBLOCK NONNULL((1, 2)) void                                                        \
	NOTHROW(FCALL handman_install_commit)(struct handle_install_data *__restrict self,         \
	                                      T *h_data, iomode_t h_mode);                         \
	FUNDEF NOBLOCK NONNULL((1, 2)) void                                                        \
	NOTHROW(FCALL handman_install_commit_inherit)(struct handle_install_data *__restrict self, \
	                                              /*inherit(always)*/ REF T *h_data, iomode_t h_mode);
HANDLE_FOREACH_TYPE(__FOREACH_HANDLES_INSTALL_COMMIT)
#undef __FOREACH_HANDLES_INSTALL_COMMIT
} /* extern "C++" */
#endif /* __cplusplus */
#else /* __INTELLISENSE__ */
#define __PRIVATE_handman_install_commit_inherit4(self, h_data, h_mode, h_type)       \
	(__hybrid_atomic_store((self)->hid_slot->_mh_words[0], h_data, __ATOMIC_RELEASE), \
	 _handman_install_commit_inherit(self, h_mode, h_type))
#define __PRIVATE_handman_install_commit4(self, h_data, h_mode, h_type) \
	((*handle_type_db.h_incref[h_type])(h_data),                        \
	 __PRIVATE_handman_install_commit_inherit4(self, h_data, h_mode, h_type))
#define __PRIVATE_handman_install_commit_inherit2(self, hand) \
	__PRIVATE_handman_install_commit_inherit4(self, (hand)->h_data, (hand)->h_mode, (hand)->h_type)
#define __PRIVATE_handman_install_commit_inherit3(self, h_data, h_mode) \
	__PRIVATE_handman_install_commit_inherit4(self, h_data, h_mode, __handleidof(h_data))
#define __PRIVATE_handman_install_commit2(self, hand) \
	__PRIVATE_handman_install_commit4(self, (hand)->h_data, (hand)->h_mode, (hand)->h_type)
#define __PRIVATE_handman_install_commit3(self, h_data, h_mode) \
	__PRIVATE_handman_install_commit4(self, h_data, h_mode, __handleidof(h_data))
#define handman_install_commit_inherit(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_handman_install_commit_inherit, (__VA_ARGS__))(__VA_ARGS__)
#define handman_install_commit(...)         __HYBRID_PP_VA_OVERLOAD(__PRIVATE_handman_install_commit, (__VA_ARGS__))(__VA_ARGS__)
#endif /* !__INTELLISENSE__ */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL _handman_install_commit_inherit)(struct handle_install_data *__restrict self,
                                               iomode_t h_mode, uintptr_half_t h_type);

/* Abort installation of a handle (s.a. `_handslot_abort()') */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL handman_install_abort)(struct handle_install_data *__restrict self);
/************************************************************************/








/************************************************************************/
/* HIGH-LEVEL HANDLE OPERATIONS (FOR THE CALLING THREAD)                */
/************************************************************************/

/* Same as `handman_close()', but also accept symbolic
 * handles, and  use `THIS_HANDMAN'  for normal  ones. */
FUNDEF ATTR_RETNONNULL NONNULL((2)) REF struct handle *FCALL
handles_close(fd_t fd, /*out*/ REF struct handle *__restrict ohand)
		THROWS(E_WOULDBLOCK, E_INVALID_HANDLE_FILE);

/* Same as `handman_lookup()', but also accept symbolic
 * handles,  and  use `THIS_HANDMAN'  for  normal ones. */
FUNDEF ATTR_RETNONNULL NONNULL((2)) REF struct handle *FCALL
handles_lookup(fd_t fd, /*out*/ REF struct handle *__restrict hand)
		THROWS(E_WOULDBLOCK, E_INVALID_HANDLE_FILE);
#define handles_lookup_nosym(...) handman_lookup(THIS_HANDMAN, __VA_ARGS__)

/* Same as `handles_lookup()', but require a specific handle type,
 * and return a reference to  the handle's `h_data' field,  rather
 * than the handle itself (attempts to cast miss-matching  types). */
FUNDEF ATTR_RETNONNULL WUNUSED REF void *FCALL
handles_lookupobj(fd_t fd, uintptr_half_t wanted_type)
		THROWS(E_WOULDBLOCK, E_INVALID_HANDLE_FILE, E_INVALID_HANDLE_FILETYPE);

/* Special wrappers for retrieving specific objects from handles. */
FUNDEF ATTR_RETNONNULL WUNUSED REF struct fnode *FCALL
handles_lookupfnode(fd_t fd)
		THROWS(E_WOULDBLOCK, E_INVALID_HANDLE_FILE, E_INVALID_HANDLE_FILETYPE);
FUNDEF ATTR_RETNONNULL WUNUSED REF struct fsuper *FCALL
handles_lookupfsuper_relaxed(fd_t fd)
		THROWS(E_WOULDBLOCK, E_INVALID_HANDLE_FILE, E_INVALID_HANDLE_FILETYPE);
FUNDEF ATTR_RETNONNULL WUNUSED REF struct task *FCALL
handles_lookuptask(fd_t fd)
		THROWS(E_WOULDBLOCK, E_INVALID_HANDLE_FILE,
		       E_INVALID_HANDLE_FILETYPE, E_PROCESS_EXITED);

#define handles_lookupmfile(fd)    ((REF struct mfile *)handles_lookupobj(fd, HANDLE_TYPE_MFILE))
#define handles_lookupfdirent(fd)  ((REF struct fdirent *)handles_lookupobj(fd, HANDLE_TYPE_DIRENT))
#define handles_lookuppath(fd)     ((REF struct path *)handles_lookupobj(fd, HANDLE_TYPE_PATH))
#define handles_lookuppidfd(fd)    ((REF struct taskpid *)handles_lookupobj(fd, HANDLE_TYPE_PIDFD))
#define handles_lookuppipe(fd)     ((REF struct pipe *)handles_lookupobj(fd, HANDLE_TYPE_PIPE))
#define handles_lookupmodule(fd)   ((REF struct driver *)handles_lookupobj(fd, HANDLE_TYPE_MODULE))
#define handles_lookupsocket(fd)   ((REF struct socket *)handles_lookupobj(fd, HANDLE_TYPE_SOCKET))
#define handles_lookupepoll(fd)    ((REF struct epoll_controller *)handles_lookupobj(fd, HANDLE_TYPE_EPOLL))
#define handles_lookupsignalfd(fd) ((REF struct signalfd *)handles_lookupobj(fd, HANDLE_TYPE_SIGNALFD))
#define handles_lookupnotifyfd(fd) ((REF struct notifyfd *)handles_lookupobj(fd, HANDLE_TYPE_NOTIFYFD))

/* Same as `handman_install_into()',  but also  accept
 * symbolic handles, and use `THIS_HANDMAN' otherwise. */
FUNDEF BLOCKING NONNULL((2, 3)) fd_t FCALL
handles_install_into(fd_t fd, struct handle const *__restrict nhand,
                     /*out*/ REF struct handle *__restrict ohand)
		THROWS(E_BADALLOC_INSUFFICIENT_HEAP_MEMORY,
		       E_BADALLOC_INSUFFICIENT_HANDLE_NUMBERS,
		       E_INVALID_HANDLE_FILE, E_WOULDBLOCK);
FUNDEF BLOCKING NONNULL((2)) fd_t FCALL
handles_install_into_simple(fd_t fd, struct handle const *__restrict nhand)
		THROWS(E_BADALLOC_INSUFFICIENT_HEAP_MEMORY,
		       E_BADALLOC_INSUFFICIENT_HANDLE_NUMBERS,
		       E_INVALID_HANDLE_FILE, E_WOULDBLOCK);
#ifdef __cplusplus
extern "C++" {
FUNDEF BLOCKING NONNULL((2)) fd_t FCALL
handles_install_into(fd_t fd, struct handle const *__restrict nhand,
                     /*out*/ REF struct handle &__restrict ohand)
		THROWS(E_BADALLOC_INSUFFICIENT_HEAP_MEMORY,
		       E_BADALLOC_INSUFFICIENT_HANDLE_NUMBERS,
		       E_INVALID_HANDLE_FILE, E_WOULDBLOCK)
		ASMNAME("handles_install_into");
FUNDEF BLOCKING NONNULL((2)) fd_t FCALL
handles_install_into(fd_t fd, struct handle const *__restrict nhand)
		THROWS(E_BADALLOC_INSUFFICIENT_HEAP_MEMORY,
		       E_BADALLOC_INSUFFICIENT_HANDLE_NUMBERS,
		       E_INVALID_HANDLE_FILE, E_WOULDBLOCK)
		ASMNAME("handles_install_into_simple");
FUNDEF BLOCKING fd_t FCALL
handles_install_into(fd_t fd, struct handle const &__restrict nhand)
		THROWS(E_BADALLOC_INSUFFICIENT_HEAP_MEMORY,
		       E_BADALLOC_INSUFFICIENT_HANDLE_NUMBERS,
		       E_INVALID_HANDLE_FILE, E_WOULDBLOCK)
		ASMNAME("handles_install_into_simple");
FUNDEF BLOCKING fd_t FCALL
handles_install_into_simple(fd_t fd, struct handle const &__restrict nhand)
		THROWS(E_BADALLOC_INSUFFICIENT_HEAP_MEMORY,
		       E_BADALLOC_INSUFFICIENT_HANDLE_NUMBERS,
		       E_INVALID_HANDLE_FILE, E_WOULDBLOCK)
		ASMNAME("handles_install_into_simple");
} /* extern "C++" */
#endif /* __cplusplus */

#ifdef __INTELLISENSE__
FUNDEF WUNUSED NONNULL((1)) fd_t FCALL
handles_install(struct handle const *__restrict hand, fd_t minfd DFL(0))
		THROWS(E_BADALLOC_INSUFFICIENT_HEAP_MEMORY,
		       E_BADALLOC_INSUFFICIENT_HANDLE_NUMBERS,
		       E_INVALID_HANDLE_FILE, E_WOULDBLOCK);
#ifdef __cplusplus
extern "C++" {
FUNDEF WUNUSED fd_t FCALL
handles_install(struct handle const &__restrict hand, fd_t minfd DFL(0))
		THROWS(E_BADALLOC_INSUFFICIENT_HEAP_MEMORY,
		       E_BADALLOC_INSUFFICIENT_HANDLE_NUMBERS,
		       E_INVALID_HANDLE_FILE, E_WOULDBLOCK)
		ASMNAME("handles_install");
} /* extern "C++" */
#endif /* __cplusplus */
#else /* __INTELLISENSE__ */
#define handles_install(...) handman_install(THIS_HANDMAN, __VA_ARGS__)
#endif /* !__INTELLISENSE__ */


/* Install a handle according to user-space openfd instructions.
 * @return: * : The file descriptor slot into which `hand' was installed. */
FUNDEF BLOCKING NONNULL((1)) fd_t FCALL
handles_install_openfd(struct handle const *__restrict hand,
                       USER UNCHECKED struct openfd *data)
		THROWS(E_BADALLOC_INSUFFICIENT_HEAP_MEMORY,
		       E_BADALLOC_INSUFFICIENT_HANDLE_NUMBERS,
		       E_INVALID_HANDLE_FILE, E_WOULDBLOCK,
		       E_SEGFAULT);
#ifdef __cplusplus
extern "C++" {
FUNDEF BLOCKING fd_t FCALL
handles_install_openfd(struct handle const &__restrict hand,
                       USER UNCHECKED struct openfd *data)
		THROWS(E_BADALLOC_INSUFFICIENT_HEAP_MEMORY,
		       E_BADALLOC_INSUFFICIENT_HANDLE_NUMBERS,
		       E_INVALID_HANDLE_FILE, E_WOULDBLOCK,
		       E_SEGFAULT)
		ASMNAME("handles_install_openfd");
} /* extern "C++" */
#endif /* __cplusplus */


/* 2-step handle installation:
 *
 * >> fd_t resfd;
 * >> REF struct kernel_object *kobj;
 * >> struct handle_install_data install;
 * >> resfd = handles_install_begin(&install);
 * >> TRY {
 * >>     kobj = CREATE_KERNEL_OBJECT();
 * >> } EXCEPT {
 * >>     handles_install_abort(&install);
 * >>     RETHROW();
 * >> }
 * >> handles_install_commit_inherit(&install, kobj, IO_RDWR);
 * >> return resfd;
 *
 * Because `handles_install_commit_inherit()' is NOBLOCK +  NOTHROW,
 * this mechanism can be used  to safely construct globally  visible
 * kernel objects,  without risking  scope  leakage in  those  cases
 * where it's impossible to allocate  another handle (since in  this
 * model, such an error happens _before_ the globally visible object
 * actually gets created) */
#ifdef __INTELLISENSE__
FUNDEF WUNUSED NONNULL((1)) fd_t FCALL
handles_install_begin(struct handle_install_data *__restrict data,
                      fd_t minfd DFL(0))
		THROWS(E_BADALLOC_INSUFFICIENT_HEAP_MEMORY,
		       E_BADALLOC_INSUFFICIENT_HANDLE_NUMBERS,
		       E_INVALID_HANDLE_FILE, E_WOULDBLOCK);
FUNDEF NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL handles_install_commit)(struct handle_install_data *__restrict self,
                                      void *h_data, iomode_t h_mode, uintptr_half_t h_type);
FUNDEF NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL handles_install_commit_inherit)(struct handle_install_data *__restrict self,
                                              /*inherit(always)*/ REF void *h_data,
                                              iomode_t h_mode, uintptr_half_t h_type);
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL handles_install_abort)(struct handle_install_data *__restrict self);
#ifdef __cplusplus
extern "C++" {
FUNDEF NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL handles_install_commit)(struct handle_install_data *__restrict self,
                                      struct handle const *__restrict hand);
FUNDEF NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL handles_install_commit_inherit)(struct handle_install_data *__restrict self,
                                              struct handle const *__restrict hand);
#define __FOREACH_HANDLES_INSTALL_COMMIT(id, T)                                                \
	FUNDEF NOBLOCK NONNULL((1, 2)) void                                                        \
	NOTHROW(FCALL handles_install_commit)(struct handle_install_data *__restrict self,         \
	                                      T *h_data, iomode_t h_mode);                         \
	FUNDEF NOBLOCK NONNULL((1, 2)) void                                                        \
	NOTHROW(FCALL handles_install_commit_inherit)(struct handle_install_data *__restrict self, \
	                                              /*inherit(always)*/ REF T *h_data, iomode_t h_mode);
HANDLE_FOREACH_TYPE(__FOREACH_HANDLES_INSTALL_COMMIT)
#undef __FOREACH_HANDLES_INSTALL_COMMIT
} /* extern "C++" */
#endif /* __cplusplus */
#else /* __INTELLISENSE__ */
#define handles_install_begin(data, ...) \
	((data)->hid_man = THIS_HANDMAN, _handman_install_begin(data, ##__VA_ARGS__))
#define handles_install_commit         handman_install_commit
#define handles_install_commit_inherit handman_install_commit_inherit
#define handles_install_abort          handman_install_abort
#endif /* !__INTELLISENSE__ */





/* Helper wrappers */
#ifdef __cplusplus
extern "C++" {
FORCELOCAL ATTR_ARTIFICIAL WUNUSED REF struct handle FCALL
handles_close(fd_t fd) THROWS(E_WOULDBLOCK, E_INVALID_HANDLE_FILE) {
	REF struct handle hand, *hptr;
	hptr = handles_close(fd, &hand);
	__builtin_assume(hptr == &hand);
	(void)hptr;
	return hand;
}
FORCELOCAL ATTR_ARTIFICIAL WUNUSED REF struct handle FCALL
handles_lookup(fd_t fd) THROWS(E_WOULDBLOCK, E_INVALID_HANDLE_FILE) {
	REF struct handle hand, *hptr;
	hptr = handles_lookup(fd, &hand);
	__builtin_assume(hptr == &hand);
	(void)hptr;
	return hand;
}
} /* extern "C++" */
#endif /* __cplusplus */

/************************************************************************/

DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_HANDMAN_H */
