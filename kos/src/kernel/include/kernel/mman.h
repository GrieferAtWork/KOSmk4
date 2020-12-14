/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_MMAN_H
#define GUARD_KERNEL_INCLUDE_KERNEL_MMAN_H 1

#include <kernel/compiler.h>

#include <kernel/mman/mnode.h>
#include <kernel/paging.h>
#include <kernel/types.h>

#include <hybrid/sequence/list.h>
#include <hybrid/sequence/rbtree.h>
#include <hybrid/sync/atomic-lock.h>

#ifdef __CC__
DECL_BEGIN

struct mpart; /* Memory file part. */
struct mfile; /* Memory storage owner/descriptor. */
struct mnode; /* Memory range descriptor. */
struct mman;  /* Memory manager. */

#ifndef __mnode_list_defined
#define __mnode_list_defined 1
LIST_HEAD(mnode_list, mnode);
#endif /* !__mnode_list_defined */

#ifndef __task_list_defined
#define __task_list_defined 1
LIST_HEAD(task_list, WEAK task);
#endif /* !__task_list_defined */

#ifndef __mnode_slist_defined
#define __mnode_slist_defined 1
SLIST_HEAD(mnode_slist, mnode);
#endif /* !__mnode_slist_defined */

struct mdeadram {
	SLIST_ENTRY(PAGEDIR_PAGEALIGNED mdeadram) mdr_link; /* [lock(ATOMIC)] Next dead-ram area. */
	PAGEDIR_PAGEALIGNED size_t                mdr_size; /* Total size (in bytes) of the dead-ram area.
	                                                     * This counts from the start of this structure. */
};
SLIST_HEAD(mdeadram_slist, mdeadram);

struct mman {
#ifndef __MMAN_INTERNAL_EXCLUDE_PAGEDIR
	pagedir_t                      mm_pagedir;     /* [lock(mm_lock)] The page directory associated with the mman. */
#endif /* !__MMAN_INTERNAL_EXCLUDE_PAGEDIR */
	PHYS pagedir_phys_t            mm_pdir_phys;   /* [1..1][const] Physical pointer of the page directory */
	WEAK refcnt_t                  mm_refcnt;      /* Reference counter. */
	WEAK refcnt_t                  mm_weakrefcnt;  /* Weak reference counter */
	struct atomic_lock             mm_lock;        /* Lock for this mman. */
	RBTREE_ROOT(struct mnode)      mm_mappings;    /* [owned][0..n][lock(mm_lock)] Known file mappings. */
	struct mnode_list              mm_writable;    /* [0..n][lock(mm_lock)] List of nodes that contain writable mappings. */
	size_t                         mm_heapsize;    /* [const] Size of the heap pointer used to allocated this mman. */
	struct task_list               mm_threads;     /* [0..n][lock(!PREEMPTION && SMP_LOCK(mm_threadslock))] */
#ifndef CONFIG_NO_SMP
	struct atomic_lock             mm_threadslock; /* SMP-lock for `mm_threads' */
#endif /* !CONFIG_NO_SMP */
	struct mnode_slist            _mm_unmapped;    /* [0..n][lock(ATOMIC)] List of nodes that have been unmapped,
	                                                * but yet to be removed from the `mm_mappings' tree. (or destroyed
	                                                * in any other form for that matter) */
	union {
		struct mnode               mm_kernreserve; /* A special RESERVED-like node that is used by user-space mmans
		                                            * to cover the entire kernel-space, preventing user-space from
		                                            * accidentally overwriting it, without the need of adding too
		                                            * many special-case exceptions to various mman-related functions.
		                                            * NOTE: For the kernel-mman itself, this node is unused. */
		struct {
			byte_t _mm_pad[__builtin_offsetof(struct mnode, mn_fspath)];
			struct mdeadram_slist  mm_deadram;     /* Only used by the kernel mman: Linked chain of dead-ram sections
			                                        * for which an attempt at unmapping should be made whenever the
			                                        * lock for this mman is released.
			                                        * This list is situated such that for user-space mmans, it always
			                                        * appears as an empty list, meaning that the clear-dead-ram check
			                                        * can simply be performed for every mman, and will simply be a
			                                        * no-op when done for anything but the kernel mman. */
		};
	};
};

/* The kernel's own memory manager. */
DATDEF struct mman mman_kernel;

/* The mman that is currently active within the calling thread */
DATDEF ATTR_PERTASK REF struct mman *this_mman;
#define THIS_MMAN  PERTASK_GET(this_mman)
#define PERMMAN(x) (*(__typeof__(&(x)))((uintptr_t)THIS_MMAN + (uintptr_t)&(x)))

/* Memory manager reference counting control. */
FUNDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL mman_free)(struct mman *__restrict self);
FUNDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL mman_destroy)(struct mman *__restrict self);
DEFINE_REFCOUNT_FUNCTIONS(struct mman, mm_refcnt, mman_destroy)
DEFINE_WEAKREFCOUNT_FUNCTIONS(struct mman, mm_weakrefcnt, mman_free)

/* Memory manager construction functions. */
FUNDEF ATTR_RETNONNULL WUNUSED REF struct mman *FCALL mman_new(void) THROWS(E_BADALLOC, ...);
FUNDEF ATTR_RETNONNULL WUNUSED REF struct mman *FCALL mman_fork(struct mman *__restrict self) THROWS(E_BADALLOC, ...);

/* Set the mman active within the calling thread, as well as
 * change page directories to make use of the new mman before
 * returning. */
FUNDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL task_setmman)(struct mman *__restrict newmman);

/* Return the active mman of the given `thread' */
FUNDEF NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct mman *
NOTHROW(FCALL task_getmman)(struct task *__restrict thread);


/* Reap dead ram regions of `self' */
FUNDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL _mman_reap)(struct mman *__restrict self);
#define mman_mustreap(self)                                                               \
	(__hybrid_atomic_load((self)->mm_deadram.slh_first, __ATOMIC_ACQUIRE) != __NULLPTR || \
	 __hybrid_atomic_load((self)->_mm_unmapped.slh_first, __ATOMIC_ACQUIRE) != __NULLPTR)
#ifdef __OPTIMIZE_SIZE__
#define mman_reap(self) _mman_reap(self)
#else /* __OPTIMIZE_SIZE__ */
#define mman_reap(self) (void)(!mman_mustreap(self) || (_mman_reap(self), 0))
#endif /* !__OPTIMIZE_SIZE__ */

/* Lock accessor helpers for `struct mman' */
#define mman_lock_tryacquire(self) atomic_lock_tryacquire(&(self)->mm_lock)
#define mman_lock_acquire(self)    atomic_lock_acquire(&(self)->mm_lock)
#define mman_lock_acquire_nx(self) atomic_lock_acquire_nx(&(self)->mm_lock)
#define mman_lock_release(self)    (atomic_lock_release(&(self)->mm_lock), mman_reap(self))
#define mman_lock_acquired(self)   atomic_lock_acquired(&(self)->mm_lock)
#define mman_lock_available(self)  atomic_lock_available(&(self)->mm_lock)
__DEFINE_SYNC_MUTEX(struct mman,
                    mman_lock_tryacquire,
                    mman_lock_acquire,
                    mman_lock_acquire_nx,
                    mman_lock_release,
                    mman_lock_acquired,
                    mman_lock_available)


/* Try to pre-fault access to the given addres range, such that `memcpy_nopf()'
 * may succeed when re-attempted.
 * @return: * : The # of leading bytes that this function managed to fault. For
 *              this purpose, any non-zero value means that `*(byte_t *)addr'
 *              was made accessible for at least one moment before this function
 *              returns. Note though that memory may have already been unloaded
 *              by the time this function returns (unlikely), so the caller must
 *              still be ready to deal with the possibility that another attempt
 *              at doing nopf access at `*(byte_t *)addr' might immediatly fail
 *              again.
 *              Also note that for any memory that had already been faulted within
 *              the given address range, this function acts as though it had been
 *              the one to fault that range, meaning that the return value doesn't
 *              actually represent how much memory had just been faulted, but rather
 *              how much continuous memory (starting at `addr' and limited by at
 *              most `num_bytes') was faulted simultaneously at some point before
 *              this function returns.
 * @return: 0 : Nothing could be faulted. This might be because `addr' doesn't
 *              point into mapped memory, or the memory that is pointed-to by it
 *              is backed by VIO storage.
 *              The caller should handle this case by attempting direct memory
 *              access to the affected region (i.e. using `memcpy' rather than 
 *              `memcpy_nopf'), and dealing with any potential E_SEGFAULT error. */
FUNDEF size_t FCALL
mman_prefault(USER CHECKED void const *addr,
              size_t num_bytes, bool for_writing)
		THROWS(E_WOULDBLOCK, E_BADALLOC);

/* Enumerate segments from `buffer', and prefault up to `num_bytes' of pointed-to
 * memory, after skipping the first `offset' bytes. The return value is the sum
 * of successfully faulted segments, however faulting also stops on the first
 * segment that cannot be fully faulted. */
FUNDEF size_t FCALL
mman_prefaultv(struct aio_buffer const *__restrict buffer,
               size_t offset, size_t num_bytes, bool for_writing)
		THROWS(E_WOULDBLOCK, E_BADALLOC);


/* High-level page directory syncing functions. */
FUNDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL mman_sync_p)(struct mman *__restrict self, PAGEDIR_PAGEALIGNED UNCHECKED void *addr, PAGEDIR_PAGEALIGNED size_t num_bytes);
FUNDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL mman_syncone_p)(struct mman *__restrict self, PAGEDIR_PAGEALIGNED UNCHECKED void *addr);
FUNDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL mman_syncall_p)(struct mman *__restrict self);

#ifndef CONFIG_NO_SMP
/* Same as `mman_sync_p(THIS_MMAN, ...)' (The sync is done on every CPU that uses the caller's VM) */
FUNDEF NOBLOCK void NOTHROW(FCALL mman_sync)(PAGEDIR_PAGEALIGNED UNCHECKED void *addr, PAGEDIR_PAGEALIGNED size_t num_bytes);
FUNDEF NOBLOCK void NOTHROW(FCALL mman_syncone)(PAGEDIR_PAGEALIGNED UNCHECKED void *addr);
FUNDEF NOBLOCK void NOTHROW(FCALL mman_syncall)(void);

/* Same as `mman_sync_p(&mman_kernel, ...)' (The sync is performed on every CPU, for any VM) */
FUNDEF NOBLOCK void NOTHROW(FCALL mman_supersync)(PAGEDIR_PAGEALIGNED UNCHECKED void *addr, PAGEDIR_PAGEALIGNED size_t num_bytes);
FUNDEF NOBLOCK void NOTHROW(FCALL mman_supersyncone)(PAGEDIR_PAGEALIGNED UNCHECKED void *addr);
FUNDEF NOBLOCK void NOTHROW(FCALL mman_supersyncall)(void);
#else /* !CONFIG_NO_SMP */
#define mman_sync(addr, num_bytes) pagedir_sync(addr, num_bytes)
#define mman_syncone(addr)         pagedir_syncone(addr)
FUNDEF NOBLOCK void NOTHROW(FCALL mman_syncall)(void);
#define mman_supersync(addr, num_bytes) pagedir_sync(addr, num_bytes)
#define mman_supersyncone(addr)         pagedir_syncone(addr)
#define mman_supersyncall()             pagedir_syncall()
#endif /* CONFIG_NO_SMP */




DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_MMAN_H */
