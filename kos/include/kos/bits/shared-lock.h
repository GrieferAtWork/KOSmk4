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
#if __SIZEOF_INT__ == 4
#define __SHARED_LOCK_UNLOCKED_WAITING 0x80000000u
#elif __SIZEOF_INT__ == 8
#define __SHARED_LOCK_UNLOCKED_WAITING 0x8000000000000000u
#elif __SIZEOF_INT__ == 2
#define __SHARED_LOCK_UNLOCKED_WAITING 0x8000u
#elif __SIZEOF_INT__ == 1
#define __SHARED_LOCK_UNLOCKED_WAITING 0x80u
#else /* __SIZEOF_INT__ == ... */
#error "Unsupported sizeof(int)"
#endif /* __SIZEOF_INT__ != ... */
	/*
	 * 0:                                            Lock is available
	 * 1:                                            Lock is held (no-one is waiting)
	 * [2, __SHARED_LOCK_UNLOCKED_WAITING-1]:        Lock is held (someone may be waiting)
	 * __SHARED_LOCK_UNLOCKED_WAITING:               Lock is available (someone may be waiting)
	 * [__SHARED_LOCK_UNLOCKED_WAITING+1, UINT_MAX]: Lock is held (someone may be waiting;
	 *                                               only set briefly during lock acquire) */
	unsigned int sl_lock; /* Lock word */
#endif /* !__KERNEL__ */
};

/* Try to acquire a lock to a given `struct shared_lock *self' */
#ifdef __KERNEL__
#ifdef __COMPILER_WORKAROUND_GCC_105689_MAC
#define __shared_lock_tryacquire(self) \
	__COMPILER_WORKAROUND_GCC_105689_MAC(self, __hybrid_atomic_xch(&__cw_105689_self->sl_lock, 1, __ATOMIC_ACQUIRE) == 0)
#else /* __COMPILER_WORKAROUND_GCC_105689_MAC */
#define __shared_lock_tryacquire(self) \
	(__hybrid_atomic_xch(&(self)->sl_lock, 1, __ATOMIC_ACQUIRE) == 0)
#endif /* !__COMPILER_WORKAROUND_GCC_105689_MAC */
#define __shared_lock_available(self) \
	(__hybrid_atomic_load(&(self)->sl_lock, __ATOMIC_ACQUIRE) == 0)
#define __shared_lock_release_ex(self)                             \
	(__hybrid_atomic_store(&(self)->sl_lock, 0, __ATOMIC_RELEASE), \
	 __shared_lock_sendone(self))
#define __shared_lock_sendone(self) sig_send(&(self)->sl_sig)
#else /* __KERNEL__ */
#define __shared_lock_available(self) \
	((__hybrid_atomic_load(&(self)->sl_lock, __ATOMIC_ACQUIRE) & ~__SHARED_LOCK_UNLOCKED_WAITING) == 0)
#ifdef __CRT_HAVE_XSC
#if __CRT_HAVE_XSC(futex)
/* NOTE: we use `sys_Xfutex()', because the only possible exception is E_SEGFAULT */
#define __shared_lock_wait_impl(self) \
	(void)sys_Xfutex(&(self)->sl_lock, /*FUTEX_WAIT*/ 0, 2, __NULLPTR, __NULLPTR, 0)
#define __shared_lock_wait_impl_timeout32(self, abs_timeout) \
	(sys_Xfutex(&(self)->sl_lock, /*FUTEX_WAIT_BITSET*/ 9, 2, abs_timeout, __NULLPTR, (__UINT32_TYPE__)-1) >= 0)
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
#define __shared_lock_wait_impl_timeout64(self, abs_timeout) \
	__shared_lock_wait_impl_timeout32(self, (struct __timespec32 *)(abs_timeout))
#elif __CRT_HAVE_XSC(futex_time64)
#define __shared_lock_wait_impl_timeout64(self, abs_timeout) \
	(sys_Xfutex_time64(&(self)->sl_lock, /*FUTEX_WAIT_BITSET*/ 9, 2, abs_timeout, __NULLPTR, (__UINT32_TYPE__)-1) >= 0)
#else /* ... */
#define __shared_lock_wait_impl_timeout64 __shared_lock_wait_impl_timeout64
__FORCELOCAL __ATTR_NONNULL((1)) __BOOL
(__shared_lock_wait_impl_timeout64)(struct shared_lock *__restrict __self,
                                    unsigned int __lockword,
                                    struct __timespec64 const *abs_timeout) {
	struct __timespec32 __ts32;
	if (!abs_timeout)
		return __shared_lock_wait_impl_timeout32(__self, __lockword, __NULLPTR);
	__ts32.tv_sec  = (__time32_t)abs_timeout->tv_sec;
	__ts32.tv_nsec = abs_timeout->tv_nsec;
	return __shared_lock_wait_impl_timeout32(__self, __lockword, &__ts32);
}
#endif /* !... */
#ifdef __USE_TIME_BITS64
#define __shared_lock_wait_impl_timeout __shared_lock_wait_impl_timeout64
#else /* __USE_TIME_BITS64 */
#define __shared_lock_wait_impl_timeout __shared_lock_wait_impl_timeout32
#endif /* !__USE_TIME_BITS64 */

#define __shared_lock_sendone(self) \
	(sys_Xfutex(&(self)->sl_lock, /*FUTEX_WAKE*/ 1, 1, __NULLPTR, __NULLPTR, 0) != 0)
#define __shared_lock_sendall(self) \
	(sys_Xfutex(&(self)->sl_lock, /*FUTEX_WAKE*/ 1, (__UINT32_TYPE__)-1, __NULLPTR, __NULLPTR, 0) != 0)
#define __shared_lock_acquire_or_wait_impl(self, ...)                                     \
	for (;;) {                                                                            \
		unsigned int _sl_lockword;                                                        \
		/* Try to acquire the lock, or enter the waiting-state */                         \
		_sl_lockword = __hybrid_atomic_incfetch(&(self)->sl_lock, __ATOMIC_ACQUIRE);      \
		if (_sl_lockword < 2)                                                             \
			break; /* Initial acquire! */                                                 \
		/* Lock is already being held by some other thread (but need to make sure that    \
		 * the  lock-word is re-set back to `2' if we just accidentally set it to 3 or    \
		 * something higher */                                                            \
		if (_sl_lockword != 2) {                                                          \
			/* Normalize lock-word into its canonical locked+waiting state */             \
			unsigned int _sl_nlockword = _sl_lockword;                                    \
			while (!__hybrid_atomic_cmpxch_weak(&(self)->sl_lock, _sl_nlockword, 2,       \
			                                    __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST)) {    \
				_sl_nlockword = __hybrid_atomic_load(&(self)->sl_lock, __ATOMIC_ACQUIRE); \
				if (_sl_nlockword <= 2)                                                   \
					break;                                                                \
			}                                                                             \
			if (_sl_lockword == (__SHARED_LOCK_UNLOCKED_WAITING + 1))                     \
				break; /* Initial acquire (with other potential waiting threads) */       \
		}                                                                                 \
		/* Wait implementation... */                                                      \
		__VA_ARGS__                                                                       \
	}

#define __shared_lock_waitfor_or_wait_impl(self, ...)                             \
	for (;;) {                                                                    \
		unsigned int _sl_lockword;                                                \
		_sl_lockword = __hybrid_atomic_load(&(self)->sl_lock, __ATOMIC_ACQUIRE);  \
		if ((_sl_lockword & ~__SHARED_LOCK_UNLOCKED_WAITING) == 0)                \
			break; /* Lock is available */                                        \
		/* Ensure a canonical wait-state */                                       \
		if (_sl_lockword != 2) {                                                  \
			if (!__hybrid_atomic_cmpxch_weak(&(self)->sl_lock, _sl_lockword, 2,   \
			                                 __ATOMIC_ACQUIRE, __ATOMIC_ACQUIRE)) \
				continue;                                                         \
		}                                                                         \
		/* Wait implementation... */                                              \
		__VA_ARGS__                                                               \
	}

#endif /* __CRT_HAVE_XSC(futex) */
#endif /* ... */
#endif /* __KERNEL__ */

__DECL_END
#endif /* __CC__ */

#endif /* !_KOS_BITS_SHARED_LOCK_H */
