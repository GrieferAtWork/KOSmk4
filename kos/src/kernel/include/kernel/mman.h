/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_MMAN_H
#define GUARD_KERNEL_INCLUDE_KERNEL_MMAN_H 1

#include <kernel/compiler.h>

#include <kernel/paging.h>
#include <kernel/types.h>

#include <hybrid/sequence/list.h>   /* LIST_HEAD, SLIST_HEAD, ... */
#include <hybrid/sequence/rbtree.h> /* RBTREE_ROOT */
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

struct mman {
#ifndef __MMAN_INTERNAL_EXCLUDE_PAGEDIR
	pagedir_t                      mm_pagedir;     /* [lock(mm_lock)] The page directory associated with the mman. */
#endif /* !__MMAN_INTERNAL_EXCLUDE_PAGEDIR */
	WEAK refcnt_t                  mm_refcnt;      /* Reference counter. */
	WEAK refcnt_t                  mm_weakrefcnt;  /* Weak reference counter */
	struct atomic_lock             mm_lock;        /* Lock for this mman. */
	RBTREE_ROOT(struct mnode)      mm_mappings;    /* [owned][0..n][lock(mm_lock)] Known file mappings. */
	PHYS pagedir_phys_t            mm_pdir_phys;   /* [1..1][const] Physical pointer of the page directory */
	struct mnode_list              mm_writable;    /* [0..n][lock(mm_lock)] List of nodes that contain writable mappings. */
	size_t                         mm_heapsize;    /* [const] Size of the heap pointer used to allocated this mman. */
	struct task_list               mm_threads;     /* [0..n][lock(!PREEMPTION && SMP_LOCK(mm_threadslock))] */
#ifndef CONFIG_NO_SMP
	struct atomic_lock             mm_threadslock; /* SMP-lock for `mm_threads' */
#endif /* !CONFIG_NO_SMP */
};

#ifndef FORMMAN
#if defined(__INTELLISENSE__) && defined(__cplusplus)
extern "C++" {
#define FORMMAN FORMMAN
template<class __T> __T &(FORMMAN)(struct mman *__restrict self, __T &symbol);
template<class __T> __T const &(FORMMAN)(struct mman const *__restrict self, __T const &symbol);
} /* extern "C++" */
#else /* __INTELLISENSE__ && __cplusplus */
#define FORMMAN(self, symbol) (*(__typeof__(&(symbol)))((__UINTPTR_TYPE__)(self) + (__UINTPTR_TYPE__)&(symbol)))
#endif /* !__INTELLISENSE__ || !__cplusplus */
#endif /* !FORMMAN */


/* TODO: fork() should not have to truely create a new page directory.
 *              Instead, try to make it so that dynamic elements of the
 *              page directory can be shared between multiple mmans! */
/* TODO: exec() should use `mman_new()' to create an actual, new memory
 *              manager from scratch. */


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

/* Memory manager construction functions.
 * NOTE: mman_fork() will fork the current mman. */
FUNDEF ATTR_RETNONNULL WUNUSED REF struct mman *FCALL mman_new(void) THROWS(E_BADALLOC, ...);
FUNDEF ATTR_RETNONNULL WUNUSED REF struct mman *FCALL mman_fork(void) THROWS(E_BADALLOC, ...);

/* Set the mman active within the calling thread, as well as
 * change page directories to make use of the new mman before
 * returning. */
FUNDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL task_setmman)(struct mman *__restrict newmman);

/* Return the active mman of the given `thread' */
FUNDEF NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct mman *
NOTHROW(FCALL task_getmman)(struct task *__restrict thread);


/*
 * Idea on how to implement an O(1) fork(2) system call:
 *
 * >> struct mman *mman_fork() {
 * >>     struct mman *result = malloc(...);
 * >>     pagedir_fork(result->mn_pdir);
 * >>     ...
 * >> }
 *
 * pagedir_fork:
 *    Use the `v_unused*_ign' bits of the entries of all of the
 *    dynamically allocated vectors within the page directory
 *    as a data-stream to encode a reference counter for the
 *    surrounding page-vector. (s.a. `p32_pagedir_refe2_incref')
 *
 * NOTE: The pagedir_fork() idea may be possible to implement,
 *       but the whole copy-on-write memory-mappings-tree idea
 *       would be _way_ too complicated, and wouldn't actually
 *       given us that great of a performance boost, since the
 *       first time either process does a write, half of their
 *       shared tree would have to be unshared.
 *       This is because only unsharing a single node wouldn't
 *       do, since we always have to unshare all nodes along the
 *       way to the actual node that we want to modify.
 *       And then there's the problem of syncing memory access
 *       to all of the nodes: With shared trees, simply locking
 *       the memory manager isn't good enough, since there would
 *       be more than 1 mman involved!
 */



struct mlockop;
#ifndef __mlockop_slist_defined
#define __mlockop_slist_defined 1
SLIST_HEAD(mlockop_slist, mlockop);
#endif /* !__mlockop_slist_defined */


/* Only used by the kernel mman: Linked chain of pending operations
 * that should be executed (via a reap-mechanism) whenever the lock
 * for this mman is released.
 * This list is situated such that for user-space mmans, it always
 * appears as an empty list, meaning that the must-reap-check can
 * simply be performed for every mman, and will simply be a no-op
 * when done for anything but the kernel mman.
 * However, you still mustn't add anything into it for a user-space
 * memory manager! */
DATDEF ATTR_PERMMAN struct mlockop_slist thismman_lockops;

/* Aliasing symbol: `== FORMMAN(&mman_kernel, thismman_lockops)' */
#ifndef __mman_kernel_lockops_defined
#define __mman_kernel_lockops_defined 1
DATDEF struct mlockop_slist mman_kernel_lockops;
#endif /* !__mman_kernel_lockops_defined */



/* Reap lock operations of `self' */
FUNDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL _mman_lockops_reap)(struct mman *__restrict self);
#define mman_lockops_mustreap(self) \
	(__hybrid_atomic_load(FORMMAN(self, thismman_lockops.slh_first), __ATOMIC_ACQUIRE) != __NULLPTR)
#ifdef __OPTIMIZE_SIZE__
#define mman_lockops_reap(self) _mman_lockops_reap(self)
#else /* __OPTIMIZE_SIZE__ */
#define mman_lockops_reap(self) (void)(!mman_lockops_mustreap(self) || (_mman_lockops_reap(self), 0))
#endif /* !__OPTIMIZE_SIZE__ */


/* Lock accessor helpers for `struct mman' */
#define mman_lock_tryacquire(self) atomic_lock_tryacquire(&(self)->mm_lock)
#define mman_lock_acquire(self)    atomic_lock_acquire(&(self)->mm_lock)
#define mman_lock_acquire_nx(self) atomic_lock_acquire_nx(&(self)->mm_lock)
#define mman_lock_release(self)    (atomic_lock_release(&(self)->mm_lock), mman_lockops_reap(self))
#define mman_lock_acquired(self)   atomic_lock_acquired(&(self)->mm_lock)
#define mman_lock_available(self)  atomic_lock_available(&(self)->mm_lock)
__DEFINE_SYNC_MUTEX(struct mman,
                    mman_lock_tryacquire,
                    mman_lock_acquire,
                    mman_lock_acquire_nx,
                    mman_lock_release,
                    mman_lock_acquired,
                    mman_lock_available)


DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_MMAN_H */
