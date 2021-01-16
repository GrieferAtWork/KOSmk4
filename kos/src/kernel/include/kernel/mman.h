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
 *              Instead, try to make it so that both the page directory,
 *              as well as `struct mnode' can be shared between multiple
 *              memory managers! */
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
 * >>     result->mm_mappings = incref(THIS_VM->mm_mappings);
 * >> }
 *
 * pagedir_fork:
 *    Use the `v_unused*_ign' bits of the entries of all of the
 *    dynamically allocated vectors within the page directory
 *    as a data-stream to encode a reference counter for the
 *    surrounding page-vector. (s.a. `p32_pagedir_refe2_incref')
 *
 * copy_on_write_btree:
 *    A binary tree, where upon every write to one of the mnode fields,
 *    we first check a reference counter stored within the mnode itself
 *    as to whether of not that node is being shared.
 *    If it is being shared, then we must create a copy of it, and the
 *    entire path-chain leading up to the node. (because we'll also need
 *    to write the lhs/rhs fields of the to-be modified node's parent,
 *    and it's parent, and so on...)
 *
 *
 * !!!PROBLEM!!! The parent pointer of the R/B-tree used for mem-nodes
 *               would have to be altered whenever one of the nodes has
 *               to be changed, which would result in the entire tree
 *               being unshared.
 * Solution:     Boils down to: When nodes are shared by different parents,
 *               then every node also needs 1 parent-pointer for every one
 *               of its parents.
 *               In other words: just extending the R/B-tree ABI isn't enough.
 *               And furthermore: we can't get rid of parent pointers: they're
 *               more important than ever (see the next (solved) problem)
 *
 * !!!PROBLEM!!! In order for `mpart_split()' and `mpart--unsharecow' to
 *               to their things, they'd need to be able to enumerate _all_
 *               of the memory managers associated with a given mem-node!
 * Solution:     This can be solved by forming a backwards tree of all of
 *               the different, recursive parent pointers of reachable from
 *               the current node. On every path where we reach an end, that
 *               last node with 0 parent pointers will reference a different
 *               memory manager, which in turn contains a mapping for the
 *               associated mpart!
 *
 *
 * Changes necessary:
 *  - mnode.mn_mman:     Must become a vector, who's length can then be
 *                       interpreted as the node's reference counter.
 *                       This vector must facilitate both atomic add
 *                       and remove operations (with the remove also
 *                       needing to be NOBLOCK+NOTHROW)
 *  - RBTREE:            Add an extension that allows for copy-on-write
 *                       reference counting functionality.
 *                       Do this by adding a function `RBTREE_PREPARE_WRITE(node, proot)'
 *                       that can be overwritten to do `node = copy_if_shared(node, proot)'
 *  - pagedir:           Implement reference counting on all levels, and
 *                       check the reference counters before making any
 *                       changes to a vector. It may be useful to have a
 *                       dedicated REFCNT_MAYBE_GREATER_ONE bit that can
 *                       be checked by isshared(), and, if set, causes a
 *                       search for other references to be performed, and
 *                       if none are found, have that bit get cleared.
 *                       -> Only vectors not currently shared can be modified.
 *  - pagedir:           Then act of splitting/merging Ei-level page-vectors
 *                       must account for references, such that newly created
 *                       vectors have refcnt=1, and vectors that go away have
 *                       their refcnt decremented.
 *  - mnode.mn_writable: Get rid of this.
 *                       The idea was to have a list of all of the places
 *                       where writable memory mappings exist, however in
 *                       this new design, the pagedir API is responsible
 *                       to clear all of the WRITABLE-bits as part of the
 *                       call to `pagedir_fork()'. Internally, this search
 *                       can be combined with the incref procedure.
 *  - mpart_split:       Must account for copy-on-write, such that all altered
 *                       nodes will be unshared such that the current behavior
 *                       can be made use of normally.
 *  - exec:              Instead of going through all of the troubles of wanting to
 *                       re-use the old mman by clearing it and its page directory,
 *                       make it so that a new mman is created, which is then
 *                       assigned to main thread of the process that called exec.
 *                       The old mman can then simply be decref'd.
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
