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
#ifndef GUARD_KERNEL_INCLUDE_SCHED_RWLOCK_INTERN_H
#define GUARD_KERNEL_INCLUDE_SCHED_RWLOCK_INTERN_H 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/malloc-defs.h>
#include <kernel/types.h>
#include <sched/rwlock.h>

DECL_BEGIN

#ifdef __CC__
/* A dummy R/W lock pointer. */
#define READLOCK_DUMMYLOCK  ((struct rwlock *)-1)

struct rwlock;
struct task;

struct read_lock {
	uintptr_t      rl_recursion; /* [valid_if(rl_rwlock != NULL && rl_rwlock != READLOCK_DUMMYLOCK)]
	                              * Amount of recursive read-locks held. */
	struct rwlock *rl_rwlock;    /* [valid_if(!= NULL && != READLOCK_DUMMYLOCK)] Associated R/W-lock. */
};


#define RWLOCK_HASH(x) ((uintptr_t)(x) / HEAP_ALIGNMENT)
struct read_locks {
	struct read_lock  rls_sbuf[CONFIG_TASK_STATIC_READLOCKS];
	size_t            rls_use; /* Amount of read-locks in use. */
	size_t            rls_cnt; /* Amount of non-NULL R/W locks. */
	size_t            rls_msk; /* Allocated hash-mask of the read-hash-vector. */
	struct read_lock *rls_vec; /* [1..rls_msk+1][owned_if(!= rls_sbuf)]
	                            * Hash-vector of thread-locally held read-locks.
	                            * As hash-index, use `RWLOCK_HASH()' */
};

DATDEF ATTR_PERTASK struct read_locks this_read_locks;

#ifdef CONFIG_BUILDING_KERNEL_CORE
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(KCALL pertask_readlocks_init)(struct task *__restrict thread);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(KCALL pertask_readlocks_fini)(struct task *__restrict thread);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(KCALL pertask_readlocks_reinit)(struct task *__restrict thread);
#endif /* CONFIG_BUILDING_KERNEL_CORE */

#endif /* __CC__ */

DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_SCHED_RWLOCK_INTERN_H */
