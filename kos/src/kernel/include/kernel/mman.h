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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_MMAN_H
#define GUARD_KERNEL_INCLUDE_KERNEL_MMAN_H 1

#include <kernel/compiler.h>

#include <kernel/paging.h>
#include <kernel/types.h>

#include <hybrid/__assert.h>
#include <hybrid/sequence/list.h>   /* LIST_HEAD, SLIST_HEAD, ... */
#include <hybrid/sequence/rbtree.h> /* RBTREE_ROOT */
#include <hybrid/sync/atomic-lock.h>

#include <kos/lockop.h>

/* Configuration option: Use a read/write lock for `struct mman::mm_lock' */
#ifdef CONFIG_NO_USE_RWLOCK_FOR_MMAN
#undef CONFIG_USE_RWLOCK_FOR_MMAN
#elif defined(CONFIG_USE_RWLOCK_FOR_MMAN)
#if (CONFIG_USE_RWLOCK_FOR_MMAN + 0) == 0
#undef CONFIG_USE_RWLOCK_FOR_MMAN
#define CONFIG_NO_USE_RWLOCK_FOR_MMAN 1
#else /* CONFIG_USE_RWLOCK_FOR_MMAN == 0 */
#undef CONFIG_USE_RWLOCK_FOR_MMAN
#define CONFIG_USE_RWLOCK_FOR_MMAN 1
#endif /* CONFIG_USE_RWLOCK_FOR_MMAN != 0 */
#else /* ... */
/*#define CONFIG_USE_RWLOCK_FOR_MMAN 1*/
#endif /* !... */

#ifdef CONFIG_USE_RWLOCK_FOR_MMAN
#include <hybrid/sync/atomic-rwlock.h>
#endif /* CONFIG_USE_RWLOCK_FOR_MMAN */

/* Trace program counters of write-locks to mfile objects. */
#undef CONFIG_MMAN_TRACE_LOCKPC
#if 1
#define CONFIG_MMAN_TRACE_LOCKPC
#endif


#ifdef __CC__
DECL_BEGIN

struct mpart; /* Memory file part. */
struct mfile; /* Memory storage owner/descriptor. */
struct mnode; /* Memory range descriptor. */
struct mman;  /* Memory manager. */

#ifndef __mnode_list_defined
#define __mnode_list_defined
LIST_HEAD(mnode_list, mnode);
#endif /* !__mnode_list_defined */

#ifndef __task_list_defined
#define __task_list_defined
LIST_HEAD(task_list, WEAK task);
#endif /* !__task_list_defined */


struct mman {
#ifndef __WANT_MMAN_EXCLUDE_PAGEDIR
	pagedir_t            mm_pagedir;     /* [lock(mm_lock)] The page directory associated with the mman. */
#endif /* !__WANT_MMAN_EXCLUDE_PAGEDIR */
	WEAK refcnt_t        mm_refcnt;      /* Reference counter. */
	WEAK refcnt_t        mm_weakrefcnt;  /* Weak reference counter */
#ifdef CONFIG_USE_RWLOCK_FOR_MMAN
	struct atomic_rwlock mm_lock;        /* Lock for this mman. */
#else /* CONFIG_USE_RWLOCK_FOR_MMAN */
	struct atomic_lock   mm_lock;        /* Lock for this mman. */
#endif /* !CONFIG_USE_RWLOCK_FOR_MMAN */
#ifdef CONFIG_MMAN_TRACE_LOCKPC
	void const         *_mm_wrlockpc;    /* [lock(mm_lock)] Write-lock program counter. */
#endif /* CONFIG_MMAN_TRACE_LOCKPC */
	RBTREE_ROOT(mnode)   mm_mappings;    /* [owned][0..n][lock(mm_lock)] Known file mappings. */
	PHYS pagedir_phys_t  mm_pagedir_p;   /* [1..1][const] Physical pointer of the page directory */
	struct mnode_list    mm_writable;    /* [0..n][lock(mm_lock)] List of nodes that contain writable mappings. */
	struct task_list     mm_threads;     /* [0..n][lock(!PREEMPTION && SMP_LOCK(mm_threadslock))] */
#ifndef CONFIG_NO_SMP
	struct atomic_lock   mm_threadslock; /* SMP-lock for `mm_threads' */
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


/* The kernel's own memory manager. */
DATDEF struct mman mman_kernel;

/* The mman that is currently active within the calling thread */
DATDEF ATTR_PERTASK REF struct mman *this_mman;
#define THIS_MMAN  PERTASK_GET(this_mman)
#define PERMMAN(x) FORMMAN(THIS_MMAN, x)

/* Memory manager reference counting control. */
FUNDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL mman_free)(struct mman *__restrict self);
FUNDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL mman_destroy)(struct mman *__restrict self);
DEFINE_REFCNT_FUNCTIONS(struct mman, mm_refcnt, mman_destroy)
DEFINE_WEAKREFCNT_FUNCTIONS(struct mman, mm_weakrefcnt, mman_free)

/* Memory manager construction functions.
 * - mman_fork() will fork the current mman; guess what system call uses it (:P)
 * - mman_new() is used by exec(2) after vfork(2). */
FUNDEF ATTR_RETNONNULL WUNUSED REF struct mman *FCALL mman_new(void) THROWS(E_BADALLOC);
FUNDEF ATTR_RETNONNULL WUNUSED REF struct mman *FCALL mman_fork(void) THROWS(E_BADALLOC, E_WOULDBLOCK);

/* Set  the mman active within the calling thread, as well as
 * change page directories to make use of the new mman before
 * returning. */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL task_setmman)(struct mman *__restrict newmman);
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL task_setmman_inherit)(/*inherit(always)*/ REF struct mman *__restrict newmman);

/* Same as `task_setmman()', but return a reference to the old mman. */
FUNDEF NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct mman *
NOTHROW(FCALL task_xchmman)(struct mman *__restrict newmman);
FUNDEF NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct mman *
NOTHROW(FCALL task_xchmman_inherit)(/*inherit(always)*/ REF struct mman *__restrict newmman);

/* Return the active mman of the given `thread' */
FUNDEF NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct mman *
NOTHROW(FCALL task_getmman)(struct task *__restrict thread);


/* [0..n] Linked chain of pending  operations that should be  executed
 * (via a reap-mechanism) whenever the lock for this mman is released. */
DATDEF ATTR_PERMMAN Toblockop_slist(mman) thismman_lockops;

/* Aliasing symbol: `== FORMMAN(&mman_kernel, thismman_lockops)' */
DATDEF Toblockop_slist(mman) mman_kernel_lockops;

/* Reap lock operations of the given mman. */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL _mman_lockops_reap)(struct mman *__restrict self);
#ifdef __NO_builtin_constant_p
#define mman_lockops_mustreap(self) \
	(__hybrid_atomic_load(FORMMAN(self, thismman_lockops.slh_first), __ATOMIC_ACQUIRE) != __NULLPTR)
#else /* __NO_builtin_constant_p */
/* By directly accessing `mman_kernel_lockops' if known at compile-time, generated
 * assembly doesn't have to do the otherwise necessary addition between two known-
 * link-time-constant values. */
#define mman_lockops_mustreap(self)                                                       \
	((__builtin_constant_p((self) == &mman_kernel) && (self) == &mman_kernel)             \
	 ? __hybrid_atomic_load(mman_kernel_lockops.slh_first, __ATOMIC_ACQUIRE) != __NULLPTR \
	 : __hybrid_atomic_load(FORMMAN(self, thismman_lockops.slh_first), __ATOMIC_ACQUIRE) != __NULLPTR)
#endif /* !__NO_builtin_constant_p */
#ifdef __OPTIMIZE_SIZE__
#define mman_lockops_reap(self) _mman_lockops_reap(self)
#else /* __OPTIMIZE_SIZE__ */
#define mman_lockops_reap(self)            \
	(void)(!mman_lockops_mustreap(self) || \
	       (_mman_lockops_reap(self), 0))
#endif /* !__OPTIMIZE_SIZE__ */

#ifndef CONFIG_NO_SMP
#define mman_threadslock_tryacquire_nopr(self) atomic_lock_tryacquire(&(self)->mm_threadslock)
#define mman_threadslock_acquire_nopr(self)    atomic_lock_acquire_nopr(&(self)->mm_threadslock)
#define mman_threadslock_release_nopr(self)    atomic_lock_release(&(self)->mm_threadslock)
#define mman_threadslock_acquired(self)        atomic_lock_acquired(&(self)->mm_threadslock)
#define mman_threadslock_available(self)       atomic_lock_available(&(self)->mm_threadslock)
#else /* !CONFIG_NO_SMP */
#define mman_threadslock_tryacquire_nopr(self) 1
#define mman_threadslock_acquire_nopr(self)    (void)0
#define mman_threadslock_release_nopr(self)    (void)0
#define mman_threadslock_acquired(self)        (!__hybrid_preemption_ison())
#define mman_threadslock_available(self)       1
#endif /* CONFIG_NO_SMP */
#define mman_threadslock_acquire(self)   atomic_lock_acquire_smp(&(self)->mm_threadslock)
#define mman_threadslock_release(self)   atomic_lock_release_smp(&(self)->mm_threadslock)
#define mman_threadslock_acquire_b(self) atomic_lock_acquire_smp_b(&(self)->mm_threadslock)
#define mman_threadslock_release_b(self) atomic_lock_release_smp_b(&(self)->mm_threadslock)


#ifdef CONFIG_MMAN_TRACE_LOCKPC
#define __MMAN_INIT_WRLOCKPC        __NULLPTR,
#define __mman_init_wrlockpc(self)  (self)->_mm_wrlockpc = __NULLPTR,
#define __mman_cinit_wrlockpc(self) __hybrid_assert((self)->_mm_wrlockpc == __NULLPTR),
#else /* CONFIG_MMAN_TRACE_LOCKPC */
#define __MMAN_INIT_WRLOCKPC        /* nothing */
#define __mman_init_wrlockpc(self)  /* nothing */
#define __mman_cinit_wrlockpc(self) /* nothing */
#endif /* !CONFIG_MMAN_TRACE_LOCKPC */

#ifdef CONFIG_MMAN_TRACE_LOCKPC
#include <asm/intrin.h>
#define __mman_trace_wrlock_setpc(self) (self)->_mm_wrlockpc = __rdip()
#define __mman_trace_wrlock_clrpc(self) (self)->_mm_wrlockpc = __NULLPTR
#endif /* CONFIG_MMAN_TRACE_LOCKPC */


/* Lock accessor helpers for `struct mman' */
#ifdef CONFIG_USE_RWLOCK_FOR_MMAN
#ifdef CONFIG_MMAN_TRACE_LOCKPC
#define mman_lock_trywrite(self)   (atomic_rwlock_trywrite(&(self)->mm_lock) && (__mman_trace_wrlock_setpc(self), 1))
#define mman_lock_write(self)      (atomic_rwlock_write(&(self)->mm_lock), __mman_trace_wrlock_setpc(self))
#define mman_lock_write_nx(self)   (atomic_rwlock_write_nx(&(self)->mm_lock) && (__mman_trace_wrlock_setpc(self), 1))
#define _mman_lock_endwrite(self)  (__mman_trace_wrlock_clrpc(self), atomic_rwlock_endwrite(&(self)->mm_lock))
#define _mman_lock_end(self)       (mman_lock_writing(self) && (__mman_trace_wrlock_clrpc(self), 1), atomic_rwlock_end(&(self)->mm_lock))
#define mman_lock_tryupgrade(self) (atomic_rwlock_tryupgrade(&(self)->mm_lock) && (__mman_trace_wrlock_setpc(self), 1))
#define mman_lock_upgrade(self)    (atomic_rwlock_upgrade(&(self)->mm_lock), __mman_trace_wrlock_setpc(self))
#define mman_lock_downgrade(self)  (__mman_trace_wrlock_clrpc(self), atomic_rwlock_downgrade(&(self)->mm_lock))
#else /* CONFIG_MMAN_TRACE_LOCKPC */
#define mman_lock_trywrite(self)   atomic_rwlock_trywrite(&(self)->mm_lock)
#define mman_lock_write(self)      atomic_rwlock_write(&(self)->mm_lock)
#define mman_lock_write_nx(self)   atomic_rwlock_write_nx(&(self)->mm_lock)
#define _mman_lock_endwrite(self)  atomic_rwlock_endwrite(&(self)->mm_lock)
#define _mman_lock_end(self)       atomic_rwlock_end(&(self)->mm_lock)
#define mman_lock_tryupgrade(self) atomic_rwlock_tryupgrade(&(self)->mm_lock)
#define mman_lock_upgrade(self)    atomic_rwlock_upgrade(&(self)->mm_lock)
#define mman_lock_downgrade(self)  atomic_rwlock_downgrade(&(self)->mm_lock)
#endif /* !CONFIG_MMAN_TRACE_LOCKPC */
#define mman_lock_tryread(self)      atomic_rwlock_tryread(&(self)->mm_lock)
#define mman_lock_read(self)         atomic_rwlock_read(&(self)->mm_lock)
#define mman_lock_read_nx(self)      atomic_rwlock_read_nx(&(self)->mm_lock)
#define mman_lock_endread(self)      (atomic_rwlock_endread(&(self)->mm_lock) ? mman_lockops_reap(self) : (void)0)
#define _mman_lock_endread(self)     atomic_rwlock_endread(&(self)->mm_lock)
#define mman_lock_endwrite(self)     (_mman_lock_endwrite(self), mman_lockops_reap(self))
#define mman_lock_end(self)          (_mman_lock_end(self) ? mman_lockops_reap(self) : (void)0)
#define mman_lock_reading(self)      atomic_rwlock_reading(&(self)->mm_lock)
#define mman_lock_writing(self)      atomic_rwlock_writing(&(self)->mm_lock)
#define mman_lock_canread(self)      atomic_rwlock_canread(&(self)->mm_lock)
#define mman_lock_canwrite(self)     atomic_rwlock_canwrite(&(self)->mm_lock)
#define mman_lock_waitread(self)     atomic_rwlock_waitread(&(self)->mm_lock)
#define mman_lock_waitwrite(self)    atomic_rwlock_waitwrite(&(self)->mm_lock)
#define mman_lock_waitread_nx(self)  atomic_rwlock_waitread_nx(&(self)->mm_lock)
#define mman_lock_waitwrite_nx(self) atomic_rwlock_waitwrite_nx(&(self)->mm_lock)

/* Aliases for !CONFIG_USE_RWLOCK_FOR_MMAN-mode
 * Use write-locks for all of these since those are exclusive */
#define mman_lock_tryacquire mman_lock_trywrite
#define mman_lock_acquire    mman_lock_write
#define mman_lock_acquire_nx mman_lock_write_nx
#define mman_lock_release    mman_lock_endwrite
#define _mman_lock_release  _mman_lock_endwrite
#define mman_lock_acquired   mman_lock_writing
#define mman_lock_available  mman_lock_canwrite
#define mman_lock_waitfor    mman_lock_waitwrite
#define mman_lock_waitfor_nx mman_lock_waitwrite_nx
#else /* CONFIG_USE_RWLOCK_FOR_MMAN */
#ifdef CONFIG_MMAN_TRACE_LOCKPC
#define mman_lock_tryacquire(self) (atomic_lock_tryacquire(&(self)->mm_lock) && (__mman_trace_wrlock_setpc(self), 1))
#define mman_lock_acquire(self)    (atomic_lock_acquire(&(self)->mm_lock), __mman_trace_wrlock_setpc(self))
#define mman_lock_acquire_nx(self) (atomic_lock_acquire_nx(&(self)->mm_lock) && (__mman_trace_wrlock_setpc(self), 1))
#define _mman_lock_release(self)   (__mman_trace_wrlock_clrpc(self), atomic_lock_release(&(self)->mm_lock))
#else /* CONFIG_MMAN_TRACE_LOCKPC */
#define mman_lock_tryacquire(self) atomic_lock_tryacquire(&(self)->mm_lock)
#define mman_lock_acquire(self)    atomic_lock_acquire(&(self)->mm_lock)
#define mman_lock_acquire_nx(self) atomic_lock_acquire_nx(&(self)->mm_lock)
#define _mman_lock_release(self)   atomic_lock_release(&(self)->mm_lock)
#endif /* !CONFIG_MMAN_TRACE_LOCKPC */
#define mman_lock_release(self)    (_mman_lock_release(self), mman_lockops_reap(self))
#define mman_lock_acquired(self)   atomic_lock_acquired(&(self)->mm_lock)
#define mman_lock_available(self)  atomic_lock_available(&(self)->mm_lock)
#define mman_lock_waitfor(self)    atomic_lock_waitfor(&(self)->mm_lock)
#define mman_lock_waitfor_nx(self) atomic_lock_waitfor_nx(&(self)->mm_lock)

/* Aliases for the R/W-lock configuration option. */
#define mman_lock_tryread          mman_lock_tryacquire
#define mman_lock_trywrite         mman_lock_tryacquire
#define mman_lock_read             mman_lock_acquire
#define mman_lock_read_nx          mman_lock_acquire_nx
#define mman_lock_write            mman_lock_acquire
#define mman_lock_write_nx         mman_lock_acquire_nx
#define mman_lock_endread          mman_lock_release
#define mman_lock_endwrite         mman_lock_release
#define mman_lock_end              mman_lock_release
#define _mman_lock_endread         _mman_lock_release
#define _mman_lock_endwrite        _mman_lock_release
#define _mman_lock_end             _mman_lock_release
#define mman_lock_reading          mman_lock_acquired
#define mman_lock_writing          mman_lock_acquired
#define mman_lock_canread          mman_lock_available
#define mman_lock_canwrite         mman_lock_available
#define mman_lock_waitread         mman_lock_waitfor
#define mman_lock_waitwrite        mman_lock_waitfor
#define mman_lock_waitread_nx      mman_lock_waitfor_nx
#define mman_lock_waitwrite_nx     mman_lock_waitfor_nx
#define mman_lock_tryupgrade(self) 1
#define mman_lock_upgrade(self)    1
#define mman_lock_downgrade(self)  (void)0
#endif /* !CONFIG_USE_RWLOCK_FOR_MMAN */

DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_MMAN_H */
