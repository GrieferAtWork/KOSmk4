/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _KOS_BITS_SHARED_RWLOCK_H
#define _KOS_BITS_SHARED_RWLOCK_H 1

#include <__stdinc.h>

#include <hybrid/__assert.h>
#include <hybrid/__atomic.h>

#include <bits/types.h>

#ifdef __KERNEL__
#include <kernel/types.h> /* ktime_t */
#include <sched/sig.h>
#define __shared_rwlock_timespec ktime_t
#else /* __KERNEL__ */
#include <bits/os/timespec.h>
#include <kos/syscalls.h>
#define __shared_rwlock_timespec struct timespec const *
#endif /* !__KERNEL__ */

#ifdef __CC__
__DECL_BEGIN

struct shared_rwlock {
	__uintptr_t sl_lock;   /* # of read-locks, or (uintptr_t)-1 if a write-lock is active. */
#ifdef __KERNEL__
	struct sig  sl_rdwait; /* Signal broadcast to wake-up readers. */
	struct sig  sl_wrwait; /* Signal broadcast to wake-up writers. */
#else /* __KERNEL__ */
	__uintptr_t sl_rdwait; /* Futex for read-lock waiters (non-zero if threads may be waiting) */
	__uintptr_t sl_wrwait; /* Futex for write-lock waiters (non-zero if threads may be waiting) */
#endif /* !__KERNEL__ */
};

#ifdef __KERNEL__
#define __shared_rwlock_wrwait_send(self)      sig_send(&(self)->sl_wrwait)
#define __shared_rwlock_rdwait_broadcast(self) sig_broadcast(&(self)->sl_rdwait)
#elif defined(__CRT_HAVE_XSC)
#if __CRT_HAVE_XSC(lfutex)
#define __shared_rwlock_wrwait_send(self)                                       \
	((self)->sl_wrwait                                                          \
	 ? (__hybrid_atomic_store(&(self)->sl_wrwait, 0, __ATOMIC_RELEASE),         \
	    sys_Xlfutex(&(self)->sl_wrwait, LFUTEX_WAKEMASK, 1, __NULLPTR, 0) != 0) \
	 : 0)
#define __shared_rwlock_rdwait_broadcast(self)                                           \
	((self)->sl_rdwait                                                                   \
	 ? (__hybrid_atomic_store(&(self)->sl_rdwait, 0, __ATOMIC_RELEASE),                  \
	    sys_Xlfutex(&(self)->sl_rdwait, LFUTEX_WAKEMASK, (__uintptr_t)-1, __NULLPTR, 0)) \
	 : 0)
#endif /* __CRT_HAVE_XSC(lfutex) */
#endif /* ... */

__DECL_END
#endif /* __CC__ */

#endif /* !_KOS_BITS_SHARED_RWLOCK_H */
