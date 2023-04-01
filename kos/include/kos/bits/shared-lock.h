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
#ifndef _KOS_BITS_SHARED_LOCK_H
#define _KOS_BITS_SHARED_LOCK_H 1

#include <__stdinc.h>

#include <hybrid/__assert.h>
#include <hybrid/__atomic.h>

#include <bits/types.h>

#ifdef __KERNEL__
#include <kernel/types.h> /* ktime_t */
#include <sched/sig.h>
#define __shared_lock_timespec ktime_t
#else /* __KERNEL__ */
#include <bits/os/timespec.h>
#include <kos/syscalls.h>
#define __shared_lock_timespec struct timespec const *
#endif /* !__KERNEL__ */

#ifdef __CC__
__DECL_BEGIN

struct shared_lock {
#ifdef __KERNEL__
	unsigned int sl_lock; /* Lock word (== 0: available, != 0: held) */
#if __SIZEOF_INT__ < __SIZEOF_POINTER__
	__byte_t   __sl_pad[__SIZEOF_POINTER__ - __SIZEOF_INT__];
#endif /* __SIZEOF_INT__ < __SIZEOF_POINTER__ */
	struct sig   sl_sig;  /* Signal send when the shared_lock is unlocked. */
#else /* __KERNEL__ */
	unsigned int sl_lock;    /* Lock word (== 0: available, != 0: held) */
	unsigned int sl_waiting; /* # of waiting threads */
#endif /* !__KERNEL__ */
};

#ifdef __KERNEL__
#define __shared_lock_send(self) sig_send(&(self)->sl_sig)
#else /* __KERNEL__ */
#define __shared_lock_beginwait(self) __hybrid_atomic_inc(&(self)->sl_waiting, __ATOMIC_SEQ_CST)
#define __shared_lock_endwait(self)   __hybrid_atomic_dec(&(self)->sl_waiting, __ATOMIC_SEQ_CST)
#ifdef __CRT_HAVE_XSC
#if __CRT_HAVE_XSC(futex)
/* NOTE: we use `sys_Xfutex()', because the only possible exception is E_SEGFAULT */
#define __shared_lock_send(self) \
	(sys_Xfutex(&(self)->sl_lock, /*FUTEX_WAKE*/ 1, 1, __NULLPTR, __NULLPTR, 0) != 0)
#define __shared_lock_wait(self, lockword) \
	(void)sys_Xfutex(&(self)->sl_lock, /*FUTEX_WAIT*/ 0, lockword, __NULLPTR, __NULLPTR, 0)
#define __shared_lock_wait_timeout32(self, lockword, abs_timeout) \
	(sys_Xfutex(&(self)->sl_lock, /*FUTEX_WAIT_BITSET*/ 9, lockword, abs_timeout, __NULLPTR, (__UINT32_TYPE__)-1) >= 0)
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
#define __shared_lock_wait_timeout64(self, lockword, abs_timeout) \
	__shared_lock_wait_timeout32(self, lockword, (struct __timespec32 *)(abs_timeout))
#elif __CRT_HAVE_XSC(futex_time64)
#define __shared_lock_wait_timeout64(self, lockword, abs_timeout) \
	(sys_Xfutex_time64(&(self)->sl_lock, /*FUTEX_WAIT_BITSET*/ 9, lockword, abs_timeout, __NULLPTR, (__UINT32_TYPE__)-1) >= 0)
#else /* ... */
#define __shared_lock_wait_timeout64 __shared_lock_wait_timeout64
__FORCELOCAL __ATTR_NONNULL((1)) __BOOL
(__shared_lock_wait_timeout64)(struct shared_lock *__restrict __self,
                               unsigned int __lockword,
                               struct __timespec64 const *abs_timeout) {
	struct __timespec32 __ts32;
	if (!abs_timeout)
		return __shared_lock_wait_timeout32(__self, __lockword, __NULLPTR);
	__ts32.tv_sec  = (__time32_t)abs_timeout->tv_sec;
	__ts32.tv_nsec = abs_timeout->tv_nsec;
	return __shared_lock_wait_timeout32(__self, __lockword, &__ts32);
}
#endif /* !... */
#ifdef __USE_TIME_BITS64
#define __shared_lock_wait_timeout __shared_lock_wait_timeout64
#else /* __USE_TIME_BITS64 */
#define __shared_lock_wait_timeout __shared_lock_wait_timeout32
#endif /* !__USE_TIME_BITS64 */
#endif /* __CRT_HAVE_XSC(futex) */
#endif /* ... */
#endif /* __KERNEL__ */

__DECL_END
#endif /* __CC__ */

#endif /* !_KOS_BITS_SHARED_LOCK_H */
