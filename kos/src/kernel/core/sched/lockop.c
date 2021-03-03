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
#ifndef GUARD_KERNEL_SRC_SCHED_LOCKOP_C
#define GUARD_KERNEL_SRC_SCHED_LOCKOP_C 1

#include <kernel/compiler.h>
#include <sched/lockop.h>

#ifndef __INTELLISENSE__
#define LOCAL_oblockop     1
#define LOCAL_name         oblockop_reap_atomic_lock
#define LOCAL_attr         NONNULL((1, 2, 3))
#define LOCAL_args         struct atomic_lock *__restrict lock
#define LOCAL_trylock()    atomic_lock_tryacquire(lock)
#define LOCAL_unlock()     atomic_lock_release(lock)
#include "lockop-reap.c.inl"

#define LOCAL_oblockop     1
#define LOCAL_name         oblockop_reap_atomic_rwlock
#define LOCAL_attr         NONNULL((1, 2, 3))
#define LOCAL_args         struct atomic_rwlock *__restrict lock
#define LOCAL_trylock()    atomic_rwlock_trywrite(lock)
#define LOCAL_unlock()     atomic_rwlock_endwrite(lock)
#include "lockop-reap.c.inl"

#define LOCAL_oblockop     1
#define LOCAL_name         oblockop_reap_ex
#define LOCAL_attr         NONNULL((1, 2, 3, 4))
#define LOCAL_args         __BOOL (FCALL *trylock)(void *cookie), void (FCALL *unlock)(void *cookie), void *cookie
#define LOCAL_trylock()    (*trylock)(cookie)
#define LOCAL_unlock()     (*unlock)(cookie)
#include "lockop-reap.c.inl"

/* Arch-specific optimizations... */
#if defined(__OPTIMIZE_SIZE__) && defined(__x86_64__)
DEFINE_PUBLIC_ALIAS(lockop_reap_ex, oblockop_reap_ex);
DEFINE_PUBLIC_ALIAS(lockop_reap_atomic_lock, oblockop_reap_atomic_lock);
DEFINE_PUBLIC_ALIAS(lockop_reap_atomic_rwlock, oblockop_reap_atomic_rwlock);
#else /* ... */

#define LOCAL_oblockop     0
#define LOCAL_name         lockop_reap_atomic_lock
#define LOCAL_attr         NONNULL((1, 2))
#define LOCAL_args         struct atomic_lock *__restrict lock
#define LOCAL_trylock()    atomic_lock_tryacquire(lock)
#define LOCAL_unlock()     atomic_lock_release(lock)
#include "lockop-reap.c.inl"

#define LOCAL_oblockop     0
#define LOCAL_name         lockop_reap_atomic_rwlock
#define LOCAL_attr         NONNULL((1, 2))
#define LOCAL_args         struct atomic_rwlock *__restrict lock
#define LOCAL_trylock()    atomic_rwlock_trywrite(lock)
#define LOCAL_unlock()     atomic_rwlock_endwrite(lock)
#include "lockop-reap.c.inl"

#define LOCAL_oblockop     0
#define LOCAL_name         lockop_reap_ex
#define LOCAL_attr         NONNULL((1, 2, 3))
#define LOCAL_args         __BOOL (FCALL *trylock)(void *cookie), void (FCALL *unlock)(void *cookie), void *cookie
#define LOCAL_trylock()    (*trylock)(cookie)
#define LOCAL_unlock()     (*unlock)(cookie)
#include "lockop-reap.c.inl"

#endif /* !... */

#endif /* !__INTELLISENSE__ */

#endif /* !GUARD_KERNEL_SRC_SCHED_LOCKOP_C */
