/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_USER_KOS_FUTEXLOCK_C
#define GUARD_LIBC_USER_KOS_FUTEXLOCK_C 1

#include "../api.h"
/**/

#include <hybrid/atomic.h>

#include <kos/futex.h>
#include <kos/futexexpr.h>
#include <kos/futexlock.h>
#include <kos/syscalls.h>

#include "kos.futexlock.h"

DECL_BEGIN

/* Disable futex spin support when optimizing for size */
#ifdef __OPTIMIZE_SIZE__
#define NO_FUTEX_SPIN 1
#define SPIN_WHILE(should_wait_if_this_expression_is_true) \
	do {       \
	} __WHILE0
#else /* __OPTIMIZE_SIZE__ */
#undef NO_FUTEX_SPIN
INTDEF ATTR_READMOSTLY unsigned int futex_spin_counter;
#define SPIN_WHILE(should_wait_if_this_expression_is_true) \
	do {                                                   \
		unsigned int _count;                               \
		_count = ATOMIC_READ(futex_spin_counter);          \
		for (;;) {                                         \
			if (!(should_wait_if_this_expression_is_true)) \
				return 1; /* Didn't wait... */             \
			if (!_count)                                   \
				break;                                     \
			if (sys_sched_yield() != -EOK)                 \
				break;                                     \
			--_count;                                      \
		}                                                  \
	} __WHILE0
#endif /* !__OPTIMIZE_SIZE__ */



LOCAL NONNULL((1, 2))
ATTR_SECTION(".text.crt.sched.futexlock.libc_lfutexlock_impl") ssize_t
NOTHROW_RPC(LIBCCALL libc_lfutexlock_impl)(lfutex_t *ulockaddr,
                                           lfutex_t *uaddr,
                                           syscall_ulong_t futex_op,
                                           lfutex_t val,
                                           struct timespec64 const *timeout,
                                           lfutex_t val2) {
	ssize_t result;
	/* Special handling for futex operation that wouldn't be understood
	 * when they appear in the `fe_condition' of a futex expression.
	 * These are essentially all operations that don't take a timeout,
	 * since only wait-like operations can be used, any only wait-like
	 * operations that the ones that actually make use of a timeout. */
	if (!LFUTEX_USES_TIMEOUT(futex_op & LFUTEX_CMDMASK)) {
		result = sys_lfutex(ulockaddr, futex_op,
		                    val, timeout, val2);
	} else {
		struct lfutexexpr expr;
		expr.fe_offset    = 0;
		expr.fe_condition = futex_op & LFUTEX_CMDMASK;
		expr.fe_val       = val;
		expr.fe_val2      = val2;
		result = sys_lfutexlockexpr(ulockaddr, uaddr,
		                            1, &expr, timeout,
		                            futex_op & LFUTEX_FLAGMASK);
	}
	return libc_seterrno_syserr(result);
}


/*[[[start:implementation]]]*/

/*[[[head:lfutexlock,hash:CRC-32=0xa65f928b]]]*/
/* >> lfutexlock(3)
 * Helper function to implement the behavior of `lfutexlockexpr()' for only a single futex.
 * This function behaves identical to the lfutex() system call, except that it takes
 * two futex addresses, where `ulockaddr' is used with `LFUTEX_WAIT_LOCK_WAITERS' to cache if
 * there are threads that may be waiting to be awoken once `LFUTEX_WAKE' is invoked on that
 * memory location (aka. `futexlock_wakeall(ulockaddr)'), whilst the other futex address
 * (i.e. `uaddr') is used for the wait-while-condition checking, the same way those checks
 * would also be performed by the `lfutex() system call'
 * @param: futex_op: One of:
 *    - LFUTEX_NOP:                (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_NOP, size_t val = ignored)
 *    - LFUTEX_WAIT:               (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT, lfutex_t val = ignored, struct timespec const *timeout)
 *    - LFUTEX_WAIT_LOCK:          (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_LOCK, lfutex_t val = lock_value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE:         (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE, lfutex_t val = value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_UNTIL:         (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_UNTIL, lfutex_t val = value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_ABOVE:   (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE_ABOVE, lfutex_t val = value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_BELOW:   (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE_BELOW, lfutex_t val = value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_BITMASK: (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE_BITMASK, lfutex_t val = bitmask, struct timespec const *timeout, lfutex_t setmask)
 *    - LFUTEX_WAIT_UNTIL_BITMASK: (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_UNTIL_BITMASK, lfutex_t val = bitmask, struct timespec const *timeout, lfutex_t setmask)
 *    - LFUTEX_WAIT_WHILE_CMPXCH:  (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE_CMPXCH, lfutex_t val = oldval, struct timespec const *timeout, lfutex_t newval)
 *    - LFUTEX_WAIT_UNTIL_CMPXCH:  (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_UNTIL_CMPXCH, lfutex_t val = oldval, struct timespec const *timeout, lfutex_t newval)
 * @param: timeout: Timeout for wait operations (s.a. `LFUTEX_WAIT_FLAG_TIMEOUT_*')
 * @return: * : Depending on `futex_op'
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINVAL:    The given `futex_op' is invalid
 * @return: -1:EINTR:     A blocking futex-wait operation was interrupted
 * @return: -1:ETIMEDOUT: A blocking futex-wait operation has timed out */
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.futexlock.lfutexlock") ssize_t
NOTHROW_RPC(LIBCCALL libc_lfutexlock)(lfutex_t *ulockaddr,
                                      lfutex_t *uaddr,
                                      syscall_ulong_t futex_op,
                                      lfutex_t val,
                                      /*struct timespec const *timeout, lfutex_t val2*/...)
/*[[[body:lfutexlock]]]*/
{
	va_list args;
	struct __timespec32 *timeout;
	lfutex_t val2;
	va_start(args, val);
	timeout = va_arg(args, struct __timespec32 *);
	val2    = va_arg(args, lfutex_t);
	va_end(args);
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
	return libc_lfutexlock_impl(ulockaddr,
	                            uaddr,
	                            futex_op,
	                            val,
	                            (struct timespec64 *)timeout,
	                            val2);
#else /* __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */
	if (!timeout || !LFUTEX_USES_TIMEOUT(futex_op)) {
		return libc_lfutexlock_impl(ulockaddr,
		                            uaddr,
		                            futex_op,
		                            val,
		                            (struct timespec64 *)NULL,
		                            val2);
	} else {
		struct timespec64 tms64;
		tms64.tv_sec  = (time64_t)timeout->tv_sec;
		tms64.tv_nsec = timeout->tv_nsec;
		return libc_lfutexlock_impl(ulockaddr,
		                            uaddr,
		                            futex_op,
		                            val,
		                            &tms64,
		                            val2);
	}
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
}
/*[[[end:lfutexlock]]]*/

/*[[[head:lfutexlock64,hash:CRC-32=0x75813698]]]*/
/* >> lfutexlock(3)
 * Helper function to implement the behavior of `lfutexlockexpr()' for only a single futex.
 * This function behaves identical to the lfutex() system call, except that it takes
 * two futex addresses, where `ulockaddr' is used with `LFUTEX_WAIT_LOCK_WAITERS' to cache if
 * there are threads that may be waiting to be awoken once `LFUTEX_WAKE' is invoked on that
 * memory location (aka. `futexlock_wakeall(ulockaddr)'), whilst the other futex address
 * (i.e. `uaddr') is used for the wait-while-condition checking, the same way those checks
 * would also be performed by the `lfutex() system call'
 * @param: futex_op: One of:
 *    - LFUTEX_NOP:                (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_NOP, size_t val = ignored)
 *    - LFUTEX_WAIT:               (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT, lfutex_t val = ignored, struct timespec const *timeout)
 *    - LFUTEX_WAIT_LOCK:          (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_LOCK, lfutex_t val = lock_value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE:         (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE, lfutex_t val = value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_UNTIL:         (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_UNTIL, lfutex_t val = value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_ABOVE:   (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE_ABOVE, lfutex_t val = value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_BELOW:   (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE_BELOW, lfutex_t val = value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_BITMASK: (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE_BITMASK, lfutex_t val = bitmask, struct timespec const *timeout, lfutex_t setmask)
 *    - LFUTEX_WAIT_UNTIL_BITMASK: (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_UNTIL_BITMASK, lfutex_t val = bitmask, struct timespec const *timeout, lfutex_t setmask)
 *    - LFUTEX_WAIT_WHILE_CMPXCH:  (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE_CMPXCH, lfutex_t val = oldval, struct timespec const *timeout, lfutex_t newval)
 *    - LFUTEX_WAIT_UNTIL_CMPXCH:  (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_UNTIL_CMPXCH, lfutex_t val = oldval, struct timespec const *timeout, lfutex_t newval)
 * @param: timeout: Timeout for wait operations (s.a. `LFUTEX_WAIT_FLAG_TIMEOUT_*')
 * @return: * : Depending on `futex_op'
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINVAL:    The given `futex_op' is invalid
 * @return: -1:EINTR:     A blocking futex-wait operation was interrupted
 * @return: -1:ETIMEDOUT: A blocking futex-wait operation has timed out */
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_lfutexlock64, libc_lfutexlock);
#else
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.futexlock.lfutexlock64") ssize_t
NOTHROW_RPC(LIBCCALL libc_lfutexlock64)(lfutex_t *ulockaddr,
                                        lfutex_t *uaddr,
                                        syscall_ulong_t futex_op,
                                        lfutex_t val,
                                        /*struct timespec64 const *timeout, lfutex_t val2*/...)
/*[[[body:lfutexlock64]]]*/
{
	va_list args;
	struct timespec64 *timeout;
	lfutex_t val2;
	ssize_t result;
	va_start(args, val);
	timeout = va_arg(args, struct timespec64 *);
	val2    = va_arg(args, lfutex_t);
	va_end(args);
	result = libc_lfutexlock_impl(ulockaddr,
	                              uaddr,
	                              futex_op,
	                              val,
	                              timeout,
	                              val2);
	return result;
}
#endif /* MAGIC:alias */
/*[[[end:lfutexlock64]]]*/

/*[[[head:futexlock_wake,hash:CRC-32=0xa6d25819]]]*/
/* A more efficient variant of `futex_wake()' that can be used to wake up threads waiting
 * on some given futex-lock. - This method of waking is faster, since it doesn't invoke a
 * system call when no thread is waiting on the given lock */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.futexlock.futexlock_wake") ssize_t
NOTHROW_NCX(LIBCCALL libc_futexlock_wake)(lfutex_t *ulockaddr,
                                          size_t max_wake)
/*[[[body:futexlock_wake]]]*/
{
	ssize_t result;
	if (!(ATOMIC_READ(*ulockaddr) & LFUTEX_WAIT_LOCK_WAITERS))
		return 0; /* No waiting threads. */
	result = sys_lfutex(ulockaddr, LFUTEX_WAKEMASK, 1,
	                    (struct timespec64 const *)(uintptr_t)~LFUTEX_WAIT_LOCK_WAITERS,
	                    (uintptr_t)0);
	return libc_seterrno_syserr(result);
}
/*[[[end:futexlock_wake]]]*/

/*[[[head:futexlock_wakeall,hash:CRC-32=0xf28ae01f]]]*/
/* A more efficient variant of `futex_wake()' that can be used to wake up threads waiting
 * on some given futex-lock. - This method of waking is faster, since it doesn't invoke a
 * system call when no thread is waiting on the given lock */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.futexlock.futexlock_wakeall") ssize_t
NOTHROW_NCX(LIBCCALL libc_futexlock_wakeall)(lfutex_t *ulockaddr)
/*[[[body:futexlock_wakeall]]]*/
{
	ssize_t result;
	if (!(__hybrid_atomic_load(*ulockaddr, __ATOMIC_ACQUIRE) & LFUTEX_WAIT_LOCK_WAITERS))
		return 0; /* No waiting threads. */
	if (!(__hybrid_atomic_fetchand(*ulockaddr, ~LFUTEX_WAIT_LOCK_WAITERS, __ATOMIC_SEQ_CST) & LFUTEX_WAIT_LOCK_WAITERS))
		return 0; /* No waiting threads. */
	result = sys_lfutex(ulockaddr, LFUTEX_WAKE, (uintptr_t)-1, NULL, 0);
	return libc_seterrno_syserr(result);
}
/*[[[end:futexlock_wakeall]]]*/

/*[[[head:futexlock_waitwhile,hash:CRC-32=0xeddc295c]]]*/
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.futexlock.futexlock_waitwhile") int
NOTHROW_RPC(LIBCCALL libc_futexlock_waitwhile)(lfutex_t *ulockaddr,
                                               lfutex_t *uaddr,
                                               lfutex_t equal_to_value)
/*[[[body:futexlock_waitwhile]]]*/
{
	int result;
	SPIN_WHILE(ATOMIC_READ(*uaddr) == equal_to_value);
	result = (int)libc_lfutexlock_impl(ulockaddr,
	                                   uaddr,
	                                   LFUTEX_WAIT_WHILE,
	                                   (uintptr_t)equal_to_value,
	                                   NULL,
	                                   0);
	return result;
}
/*[[[end:futexlock_waitwhile]]]*/

/*[[[head:futexlock_waituntil,hash:CRC-32=0xa4ef3cb4]]]*/
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.futexlock.futexlock_waituntil") int
NOTHROW_RPC(LIBCCALL libc_futexlock_waituntil)(lfutex_t *ulockaddr,
                                               lfutex_t *uaddr,
                                               lfutex_t not_equal_to_value)
/*[[[body:futexlock_waituntil]]]*/
{
	int result;
	SPIN_WHILE(ATOMIC_READ(*uaddr) != not_equal_to_value);
	result = (int)libc_lfutexlock_impl(ulockaddr,
	                                   uaddr,
	                                   LFUTEX_WAIT_UNTIL,
	                                   (uintptr_t)not_equal_to_value,
	                                   NULL,
	                                   0);
	return result;
}
/*[[[end:futexlock_waituntil]]]*/

/*[[[head:futexlock_waitwhile_above,hash:CRC-32=0x455d4119]]]*/
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.futexlock.futexlock_waitwhile_above") int
NOTHROW_RPC(LIBCCALL libc_futexlock_waitwhile_above)(lfutex_t *ulockaddr,
                                                     lfutex_t *uaddr,
                                                     lfutex_t above_value)
/*[[[body:futexlock_waitwhile_above]]]*/
{
	int result;
	SPIN_WHILE(ATOMIC_READ(*uaddr) > above_value);
	result = (int)libc_lfutexlock_impl(ulockaddr,
	                                   uaddr,
	                                   LFUTEX_WAIT_WHILE_ABOVE,
	                                   (uintptr_t)above_value,
	                                   NULL,
	                                   0);
	return result;
}
/*[[[end:futexlock_waitwhile_above]]]*/

/*[[[head:futexlock_waitwhile_below,hash:CRC-32=0x59d9a689]]]*/
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.futexlock.futexlock_waitwhile_below") int
NOTHROW_RPC(LIBCCALL libc_futexlock_waitwhile_below)(lfutex_t *ulockaddr,
                                                     lfutex_t *uaddr,
                                                     lfutex_t below_value)
/*[[[body:futexlock_waitwhile_below]]]*/
{
	int result;
	SPIN_WHILE(ATOMIC_READ(*uaddr) < below_value);
	result = (int)libc_lfutexlock_impl(ulockaddr,
	                                   uaddr,
	                                   LFUTEX_WAIT_WHILE_BELOW,
	                                   (uintptr_t)below_value,
	                                   NULL,
	                                   0);
	return result;
}
/*[[[end:futexlock_waitwhile_below]]]*/

/*[[[head:futexlock_waitwhile_aboveequal,hash:CRC-32=0xf1b5fc3d]]]*/
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.futexlock.futexlock_waitwhile_aboveequal") int
NOTHROW_RPC(LIBCCALL libc_futexlock_waitwhile_aboveequal)(lfutex_t *ulockaddr,
                                                          lfutex_t *uaddr,
                                                          lfutex_t above_equal_value)
/*[[[body:futexlock_waitwhile_aboveequal]]]*/
{
	int result;
	SPIN_WHILE(ATOMIC_READ(*uaddr) >= above_equal_value);
	result = (int)libc_lfutexlock_impl(ulockaddr,
	                                   uaddr,
	                                   likely(above_equal_value != 0)
	                                   ? LFUTEX_WAIT_WHILE_ABOVE
	                                   : LFUTEX_WAIT,
	                                   (uintptr_t)above_equal_value - 1,
	                                   NULL,
	                                   0);
	return result;
}
/*[[[end:futexlock_waitwhile_aboveequal]]]*/

/*[[[head:futexlock_waitwhile_belowequal,hash:CRC-32=0x2b3acecf]]]*/
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.futexlock.futexlock_waitwhile_belowequal") int
NOTHROW_RPC(LIBCCALL libc_futexlock_waitwhile_belowequal)(lfutex_t *ulockaddr,
                                                          lfutex_t *uaddr,
                                                          lfutex_t below_equal_value)
/*[[[body:futexlock_waitwhile_belowequal]]]*/
{
	int result;
	SPIN_WHILE(ATOMIC_READ(*uaddr) <= below_equal_value);
	result = (int)libc_lfutexlock_impl(ulockaddr,
	                                   uaddr,
	                                   likely(below_equal_value != (lfutex_t)-1)
	                                   ? LFUTEX_WAIT_WHILE_BELOW
	                                   : LFUTEX_WAIT,
	                                   (uintptr_t)below_equal_value + 1,
	                                   NULL,
	                                   0);
	return result;
}
/*[[[end:futexlock_waitwhile_belowequal]]]*/

/*[[[head:futexlock_waitwhile_cmpxch,hash:CRC-32=0x9a019cff]]]*/
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.futexlock.futexlock_waitwhile_cmpxch") int
NOTHROW_RPC(LIBCCALL libc_futexlock_waitwhile_cmpxch)(lfutex_t *ulockaddr,
                                                      lfutex_t *uaddr,
                                                      lfutex_t old_value,
                                                      lfutex_t new_value)
/*[[[body:futexlock_waitwhile_cmpxch]]]*/
{
	int result;
	SPIN_WHILE(ATOMIC_READ(*uaddr) == old_value);
	result = (int)libc_lfutexlock_impl(ulockaddr,
	                                   uaddr,
	                                   LFUTEX_WAIT_WHILE_CMPXCH,
	                                   (uintptr_t)old_value,
	                                   NULL,
	                                   (uintptr_t)new_value);
	return result;
}
/*[[[end:futexlock_waitwhile_cmpxch]]]*/

/*[[[head:futexlock_waituntil_cmpxch,hash:CRC-32=0x78ec6ab2]]]*/
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.futexlock.futexlock_waituntil_cmpxch") int
NOTHROW_RPC(LIBCCALL libc_futexlock_waituntil_cmpxch)(lfutex_t *ulockaddr,
                                                      lfutex_t *uaddr,
                                                      lfutex_t old_value,
                                                      lfutex_t new_value)
/*[[[body:futexlock_waituntil_cmpxch]]]*/
{
	int result;
	SPIN_WHILE(futex_trywaituntil_cmpxch(uaddr, old_value, new_value) == 0);
	result = (int)libc_lfutexlock_impl(ulockaddr,
	                                   uaddr,
	                                   LFUTEX_WAIT_UNTIL_CMPXCH,
	                                   (uintptr_t)old_value,
	                                   NULL,
	                                   (uintptr_t)new_value);
	return result;
}
/*[[[end:futexlock_waituntil_cmpxch]]]*/

/*[[[head:futexlock_waitlock,hash:CRC-32=0x7a511298]]]*/
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.futexlock.futexlock_waitlock") int
NOTHROW_RPC(LIBCCALL libc_futexlock_waitlock)(lfutex_t *ulockaddr,
                                              lfutex_t *uaddr)
/*[[[body:futexlock_waitlock]]]*/
{
	int result;
	SPIN_WHILE(futex_trywaitlock(uaddr) == 0);
	result = (int)libc_lfutexlock_impl(ulockaddr,
	                                   uaddr,
	                                   LFUTEX_WAIT_LOCK,
	                                   0,
	                                   NULL,
	                                   0);
	return result;
}
/*[[[end:futexlock_waitlock]]]*/

/*[[[head:futexlock_waitwhile_exactbits,hash:CRC-32=0x627bff9d]]]*/
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.futexlock.futexlock_waitwhile_exactbits") int
NOTHROW_RPC(LIBCCALL libc_futexlock_waitwhile_exactbits)(lfutex_t *ulockaddr,
                                                         lfutex_t *uaddr,
                                                         lfutex_t bitmask,
                                                         lfutex_t setmask)
/*[[[body:futexlock_waitwhile_exactbits]]]*/
{
	int result;
	SPIN_WHILE((ATOMIC_READ(*uaddr) & bitmask) == setmask);
	result = (int)libc_lfutexlock_impl(ulockaddr,
	                                   uaddr,
	                                   LFUTEX_WAIT_WHILE_BITMASK,
	                                   (uintptr_t)bitmask,
	                                   NULL,
	                                   (uintptr_t)setmask);
	return result;
}
/*[[[end:futexlock_waitwhile_exactbits]]]*/

/*[[[head:futexlock_waituntil_exactbits,hash:CRC-32=0x41f1399e]]]*/
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.futexlock.futexlock_waituntil_exactbits") int
NOTHROW_RPC(LIBCCALL libc_futexlock_waituntil_exactbits)(lfutex_t *ulockaddr,
                                                         lfutex_t *uaddr,
                                                         lfutex_t bitmask,
                                                         lfutex_t setmask)
/*[[[body:futexlock_waituntil_exactbits]]]*/
{
	int result;
	SPIN_WHILE((ATOMIC_READ(*uaddr) & bitmask) != setmask);
	result = (int)libc_lfutexlock_impl(ulockaddr,
	                                   uaddr,
	                                   LFUTEX_WAIT_UNTIL_BITMASK,
	                                   (uintptr_t)bitmask,
	                                   NULL,
	                                   (uintptr_t)setmask);
	return result;
}
/*[[[end:futexlock_waituntil_exactbits]]]*/

/*[[[head:futexlock_waitwhile_anybit,hash:CRC-32=0x9d62162e]]]*/
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.futexlock.futexlock_waitwhile_anybit") int
NOTHROW_RPC(LIBCCALL libc_futexlock_waitwhile_anybit)(lfutex_t *ulockaddr,
                                                      lfutex_t *uaddr,
                                                      lfutex_t bitmask)
/*[[[body:futexlock_waitwhile_anybit]]]*/
{
	int result;
	SPIN_WHILE((ATOMIC_READ(*uaddr) & bitmask) != 0);
	result = (int)libc_lfutexlock_impl(ulockaddr,
	                                   uaddr,
	                                   LFUTEX_WAIT_UNTIL_BITMASK,
	                                   (uintptr_t)bitmask,
	                                   NULL,
	                                   (uintptr_t)0);
	return result;
}
/*[[[end:futexlock_waitwhile_anybit]]]*/

/*[[[head:futexlock_waitwhile_allbits,hash:CRC-32=0x373886df]]]*/
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.futexlock.futexlock_waitwhile_allbits") int
NOTHROW_RPC(LIBCCALL libc_futexlock_waitwhile_allbits)(lfutex_t *ulockaddr,
                                                       lfutex_t *uaddr,
                                                       lfutex_t bitmask)
/*[[[body:futexlock_waitwhile_allbits]]]*/
{
	int result;
	SPIN_WHILE((ATOMIC_READ(*uaddr) & bitmask) == bitmask);
	result = (int)libc_lfutexlock_impl(ulockaddr,
	                                   uaddr,
	                                   LFUTEX_WAIT_WHILE_BITMASK,
	                                   (uintptr_t)bitmask,
	                                   NULL,
	                                   (uintptr_t)bitmask);
	return result;
}
/*[[[end:futexlock_waitwhile_allbits]]]*/

/*[[[head:futexlock_timedwaitwhile,hash:CRC-32=0x376d086e]]]*/
/* Wait if `*uaddr == equal_to_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.futexlock.futexlock_timedwaitwhile") int
NOTHROW_RPC(LIBCCALL libc_futexlock_timedwaitwhile)(lfutex_t *ulockaddr,
                                                    lfutex_t *uaddr,
                                                    lfutex_t equal_to_value,
                                                    struct timespec const *rel_timeout)
/*[[[body:futexlock_timedwaitwhile]]]*/
{
	struct timespec64 tms64;
	if (!rel_timeout)
		return futexlock_timedwaitwhile64(ulockaddr, uaddr, equal_to_value, NULL);
	tms64.tv_sec  = (time64_t)rel_timeout->tv_sec;
	tms64.tv_nsec = rel_timeout->tv_nsec;
	return futexlock_timedwaitwhile64(ulockaddr, uaddr, equal_to_value, &tms64);
}
/*[[[end:futexlock_timedwaitwhile]]]*/

/*[[[head:futexlock_timedwaituntil,hash:CRC-32=0xb2f41d7d]]]*/
/* Wait if `*uaddr != not_equal_to_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.futexlock.futexlock_timedwaituntil") int
NOTHROW_RPC(LIBCCALL libc_futexlock_timedwaituntil)(lfutex_t *ulockaddr,
                                                    lfutex_t *uaddr,
                                                    lfutex_t not_equal_to_value,
                                                    struct timespec const *rel_timeout)
/*[[[body:futexlock_timedwaituntil]]]*/
{
	struct timespec64 tms64;
	if (!rel_timeout)
		return futexlock_timedwaituntil64(ulockaddr, uaddr, not_equal_to_value, NULL);
	tms64.tv_sec  = (time64_t)rel_timeout->tv_sec;
	tms64.tv_nsec = rel_timeout->tv_nsec;
	return futexlock_timedwaituntil64(ulockaddr, uaddr, not_equal_to_value, &tms64);
}
/*[[[end:futexlock_timedwaituntil]]]*/

/*[[[head:futexlock_timedwaitwhile_above,hash:CRC-32=0x891b48db]]]*/
/* Wait if `*uaddr > above_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.futexlock.futexlock_timedwaitwhile_above") int
NOTHROW_RPC(LIBCCALL libc_futexlock_timedwaitwhile_above)(lfutex_t *ulockaddr,
                                                          lfutex_t *uaddr,
                                                          lfutex_t above_value,
                                                          struct timespec const *rel_timeout)
/*[[[body:futexlock_timedwaitwhile_above]]]*/
{
	struct timespec64 tms64;
	if (!rel_timeout)
		return futexlock_timedwaitwhile_above64(ulockaddr, uaddr, above_value, NULL);
	tms64.tv_sec  = (time64_t)rel_timeout->tv_sec;
	tms64.tv_nsec = rel_timeout->tv_nsec;
	return futexlock_timedwaitwhile_above64(ulockaddr, uaddr, above_value, &tms64);
}
/*[[[end:futexlock_timedwaitwhile_above]]]*/

/*[[[head:futexlock_timedwaitwhile_below,hash:CRC-32=0x46dc77d6]]]*/
/* Wait if `*uaddr < below_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.futexlock.futexlock_timedwaitwhile_below") int
NOTHROW_RPC(LIBCCALL libc_futexlock_timedwaitwhile_below)(lfutex_t *ulockaddr,
                                                          lfutex_t *uaddr,
                                                          lfutex_t below_value,
                                                          struct timespec const *rel_timeout)
/*[[[body:futexlock_timedwaitwhile_below]]]*/
{
	struct timespec64 tms64;
	if (!rel_timeout)
		return futexlock_timedwaitwhile_below64(ulockaddr, uaddr, below_value, NULL);
	tms64.tv_sec  = (time64_t)rel_timeout->tv_sec;
	tms64.tv_nsec = rel_timeout->tv_nsec;
	return futexlock_timedwaitwhile_below64(ulockaddr, uaddr, below_value, &tms64);
}
/*[[[end:futexlock_timedwaitwhile_below]]]*/

/*[[[head:futexlock_timedwaitwhile_aboveequal,hash:CRC-32=0x5d662ee6]]]*/
/* Wait if `*uaddr >= above_equal_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.futexlock.futexlock_timedwaitwhile_aboveequal") int
NOTHROW_RPC(LIBCCALL libc_futexlock_timedwaitwhile_aboveequal)(lfutex_t *ulockaddr,
                                                               lfutex_t *uaddr,
                                                               lfutex_t above_equal_value,
                                                               struct timespec const *rel_timeout)
/*[[[body:futexlock_timedwaitwhile_aboveequal]]]*/
{
	struct timespec64 tms64;
	if (!rel_timeout)
		return futexlock_timedwaitwhile_aboveequal64(ulockaddr, uaddr, above_equal_value, NULL);
	tms64.tv_sec  = (time64_t)rel_timeout->tv_sec;
	tms64.tv_nsec = rel_timeout->tv_nsec;
	return futexlock_timedwaitwhile_aboveequal64(ulockaddr, uaddr, above_equal_value, &tms64);
}
/*[[[end:futexlock_timedwaitwhile_aboveequal]]]*/

/*[[[head:futexlock_timedwaitwhile_belowequal,hash:CRC-32=0x90198a5a]]]*/
/* Wait if `*uaddr <= below_equal_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.futexlock.futexlock_timedwaitwhile_belowequal") int
NOTHROW_RPC(LIBCCALL libc_futexlock_timedwaitwhile_belowequal)(lfutex_t *ulockaddr,
                                                               lfutex_t *uaddr,
                                                               lfutex_t below_equal_value,
                                                               struct timespec const *rel_timeout)
/*[[[body:futexlock_timedwaitwhile_belowequal]]]*/
{
	struct timespec64 tms64;
	if (!rel_timeout)
		return futexlock_timedwaitwhile_belowequal64(ulockaddr, uaddr, below_equal_value, NULL);
	tms64.tv_sec  = (time64_t)rel_timeout->tv_sec;
	tms64.tv_nsec = rel_timeout->tv_nsec;
	return futexlock_timedwaitwhile_belowequal64(ulockaddr, uaddr, below_equal_value, &tms64);
}
/*[[[end:futexlock_timedwaitwhile_belowequal]]]*/

/*[[[head:futexlock_timedwaitwhile_cmpxch,hash:CRC-32=0x7e46eb48]]]*/
/* Wait if `*uaddr == old_value', and set `*uaddr = new_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted (*uaddr was still set to new_value)
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.futexlock.futexlock_timedwaitwhile_cmpxch") int
NOTHROW_RPC(LIBCCALL libc_futexlock_timedwaitwhile_cmpxch)(lfutex_t *ulockaddr,
                                                           lfutex_t *uaddr,
                                                           lfutex_t old_value,
                                                           lfutex_t new_value,
                                                           struct timespec const *rel_timeout)
/*[[[body:futexlock_timedwaitwhile_cmpxch]]]*/
{
	struct timespec64 tms64;
	if (!rel_timeout)
		return futexlock_timedwaitwhile_cmpxch64(ulockaddr, uaddr, old_value, new_value, NULL);
	tms64.tv_sec  = (time64_t)rel_timeout->tv_sec;
	tms64.tv_nsec = rel_timeout->tv_nsec;
	return futexlock_timedwaitwhile_cmpxch64(ulockaddr, uaddr, old_value, new_value, &tms64);
}
/*[[[end:futexlock_timedwaitwhile_cmpxch]]]*/

/*[[[head:futexlock_timedwaituntil_cmpxch,hash:CRC-32=0xe083fc1a]]]*/
/* Wait if `*uaddr != old_value', and set `*uaddr = new_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted (*uaddr was still set to new_value)
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.futexlock.futexlock_timedwaituntil_cmpxch") int
NOTHROW_RPC(LIBCCALL libc_futexlock_timedwaituntil_cmpxch)(lfutex_t *ulockaddr,
                                                           lfutex_t *uaddr,
                                                           lfutex_t old_value,
                                                           lfutex_t new_value,
                                                           struct timespec const *rel_timeout)
/*[[[body:futexlock_timedwaituntil_cmpxch]]]*/
{
	struct timespec64 tms64;
	if (!rel_timeout)
		return futexlock_timedwaituntil_cmpxch64(ulockaddr, uaddr, old_value, new_value, NULL);
	tms64.tv_sec  = (time64_t)rel_timeout->tv_sec;
	tms64.tv_nsec = rel_timeout->tv_nsec;
	return futexlock_timedwaituntil_cmpxch64(ulockaddr, uaddr, old_value, new_value, &tms64);
}
/*[[[end:futexlock_timedwaituntil_cmpxch]]]*/

/*[[[head:futexlock_timedwaitlock,hash:CRC-32=0x25225336]]]*/
/* Acquire a managed futex lock (s.a. `LFUTEX_WAIT_LOCK')
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted (*uaddr was still set to new_value)
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.futexlock.futexlock_timedwaitlock") int
NOTHROW_RPC(LIBCCALL libc_futexlock_timedwaitlock)(lfutex_t *ulockaddr,
                                                   lfutex_t *uaddr,
                                                   struct timespec const *rel_timeout)
/*[[[body:futexlock_timedwaitlock]]]*/
{
	struct timespec64 tms64;
	if (!rel_timeout)
		return futexlock_timedwaitlock64(ulockaddr, uaddr, NULL);
	tms64.tv_sec  = (time64_t)rel_timeout->tv_sec;
	tms64.tv_nsec = rel_timeout->tv_nsec;
	return futexlock_timedwaitlock64(ulockaddr, uaddr, &tms64);
}
/*[[[end:futexlock_timedwaitlock]]]*/

/*[[[head:futexlock_timedwaitwhile_exactbits,hash:CRC-32=0x17caf402]]]*/
/* Wait if `(*uaddr & bitmask) == setmask'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.futexlock.futexlock_timedwaitwhile_exactbits") int
NOTHROW_RPC(LIBCCALL libc_futexlock_timedwaitwhile_exactbits)(lfutex_t *ulockaddr,
                                                              lfutex_t *uaddr,
                                                              lfutex_t bitmask,
                                                              lfutex_t setmask,
                                                              struct timespec const *rel_timeout)
/*[[[body:futexlock_timedwaitwhile_exactbits]]]*/
{
	struct timespec64 tms64;
	if (!rel_timeout)
		return futexlock_timedwaitwhile_exactbits64(ulockaddr, uaddr, bitmask, setmask, NULL);
	tms64.tv_sec  = (time64_t)rel_timeout->tv_sec;
	tms64.tv_nsec = rel_timeout->tv_nsec;
	return futexlock_timedwaitwhile_exactbits64(ulockaddr, uaddr, bitmask, setmask, &tms64);
}
/*[[[end:futexlock_timedwaitwhile_exactbits]]]*/

/*[[[head:futexlock_timedwaituntil_exactbits,hash:CRC-32=0xa345d1a8]]]*/
/* Wait if `(*uaddr & bitmask) != setmask'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.futexlock.futexlock_timedwaituntil_exactbits") int
NOTHROW_RPC(LIBCCALL libc_futexlock_timedwaituntil_exactbits)(lfutex_t *ulockaddr,
                                                              lfutex_t *uaddr,
                                                              lfutex_t bitmask,
                                                              lfutex_t setmask,
                                                              struct timespec const *rel_timeout)
/*[[[body:futexlock_timedwaituntil_exactbits]]]*/
{
	struct timespec64 tms64;
	if (!rel_timeout)
		return futexlock_timedwaituntil_exactbits64(ulockaddr, uaddr, bitmask, setmask, NULL);
	tms64.tv_sec  = (time64_t)rel_timeout->tv_sec;
	tms64.tv_nsec = rel_timeout->tv_nsec;
	return futexlock_timedwaituntil_exactbits64(ulockaddr, uaddr, bitmask, setmask, &tms64);
}
/*[[[end:futexlock_timedwaituntil_exactbits]]]*/

/*[[[head:futexlock_timedwaitwhile_anybit,hash:CRC-32=0x62326bfa]]]*/
/* Wait if `(*uaddr & bitmask) != 0'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.futexlock.futexlock_timedwaitwhile_anybit") int
NOTHROW_RPC(LIBCCALL libc_futexlock_timedwaitwhile_anybit)(lfutex_t *ulockaddr,
                                                           lfutex_t *uaddr,
                                                           lfutex_t bitmask,
                                                           struct timespec const *rel_timeout)
/*[[[body:futexlock_timedwaitwhile_anybit]]]*/
{
	struct timespec64 tms64;
	if (!rel_timeout)
		return futexlock_timedwaitwhile_anybit64(ulockaddr, uaddr, bitmask, NULL);
	tms64.tv_sec  = (time64_t)rel_timeout->tv_sec;
	tms64.tv_nsec = rel_timeout->tv_nsec;
	return futexlock_timedwaitwhile_anybit64(ulockaddr, uaddr, bitmask, &tms64);
}
/*[[[end:futexlock_timedwaitwhile_anybit]]]*/

/*[[[head:futexlock_timedwaitwhile_allbits,hash:CRC-32=0x2180f95d]]]*/
/* Wait if `(*uaddr & bitmask) == bitmask'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.futexlock.futexlock_timedwaitwhile_allbits") int
NOTHROW_RPC(LIBCCALL libc_futexlock_timedwaitwhile_allbits)(lfutex_t *ulockaddr,
                                                            lfutex_t *uaddr,
                                                            lfutex_t bitmask,
                                                            struct timespec const *rel_timeout)
/*[[[body:futexlock_timedwaitwhile_allbits]]]*/
{
	struct timespec64 tms64;
	if (!rel_timeout)
		return futexlock_timedwaitwhile_allbits64(ulockaddr, uaddr, bitmask, NULL);
	tms64.tv_sec  = (time64_t)rel_timeout->tv_sec;
	tms64.tv_nsec = rel_timeout->tv_nsec;
	return futexlock_timedwaitwhile_allbits64(ulockaddr, uaddr, bitmask, &tms64);
}
/*[[[end:futexlock_timedwaitwhile_allbits]]]*/

/*[[[head:futexlock_timedwaitwhile64,hash:CRC-32=0xfa856e22]]]*/
/* Wait if `*uaddr == equal_to_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_futexlock_timedwaitwhile64, libc_futexlock_timedwaitwhile);
#else
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.futexlock.futexlock_timedwaitwhile64") int
NOTHROW_RPC(LIBCCALL libc_futexlock_timedwaitwhile64)(lfutex_t *ulockaddr,
                                                      lfutex_t *uaddr,
                                                      lfutex_t equal_to_value,
                                                      struct timespec64 const *rel_timeout)
/*[[[body:futexlock_timedwaitwhile64]]]*/
{
	errno_t result;
	SPIN_WHILE(ATOMIC_READ(*uaddr) == equal_to_value);
	result = (errno_t)libc_lfutexlock_impl(ulockaddr,
	                                       uaddr,
	                                       LFUTEX_WAIT_WHILE |
	                                       LFUTEX_WAIT_FLAG_TIMEOUT_RELATIVE,
	                                       (uintptr_t)equal_to_value,
	                                       rel_timeout,
	                                       (uintptr_t)0);
	return libc_seterrno_syserr(result);
}
#endif /* MAGIC:alias */
/*[[[end:futexlock_timedwaitwhile64]]]*/

/*[[[head:futexlock_timedwaituntil64,hash:CRC-32=0x410b3dcf]]]*/
/* Wait if `*uaddr != not_equal_to_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_futexlock_timedwaituntil64, libc_futexlock_timedwaituntil);
#else
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.futexlock.futexlock_timedwaituntil64") int
NOTHROW_RPC(LIBCCALL libc_futexlock_timedwaituntil64)(lfutex_t *ulockaddr,
                                                      lfutex_t *uaddr,
                                                      lfutex_t not_equal_to_value,
                                                      struct timespec64 const *rel_timeout)
/*[[[body:futexlock_timedwaituntil64]]]*/
{
	int result;
	SPIN_WHILE(ATOMIC_READ(*uaddr) != not_equal_to_value);
	result = (int)libc_lfutexlock_impl(ulockaddr,
	                                   uaddr,
	                                   LFUTEX_WAIT_UNTIL |
	                                   LFUTEX_WAIT_FLAG_TIMEOUT_RELATIVE,
	                                   (uintptr_t)not_equal_to_value,
	                                   rel_timeout,
	                                   (uintptr_t)0);
	return result;
}
#endif /* MAGIC:alias */
/*[[[end:futexlock_timedwaituntil64]]]*/

/*[[[head:futexlock_timedwaitwhile_above64,hash:CRC-32=0x32984226]]]*/
/* Wait if `*uaddr > above_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_futexlock_timedwaitwhile_above64, libc_futexlock_timedwaitwhile_above);
#else
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.futexlock.futexlock_timedwaitwhile_above64") int
NOTHROW_RPC(LIBCCALL libc_futexlock_timedwaitwhile_above64)(lfutex_t *ulockaddr,
                                                            lfutex_t *uaddr,
                                                            lfutex_t above_value,
                                                            struct timespec64 const *rel_timeout)
/*[[[body:futexlock_timedwaitwhile_above64]]]*/
{
	int result;
	SPIN_WHILE(ATOMIC_READ(*uaddr) > above_value);
	result = (int)libc_lfutexlock_impl(ulockaddr,
	                                   uaddr,
	                                   LFUTEX_WAIT_WHILE_ABOVE |
	                                   LFUTEX_WAIT_FLAG_TIMEOUT_RELATIVE,
	                                   (uintptr_t)above_value,
	                                   rel_timeout,
	                                   (uintptr_t)0);
	return result;
}
#endif /* MAGIC:alias */
/*[[[end:futexlock_timedwaitwhile_above64]]]*/

/*[[[head:futexlock_timedwaitwhile_below64,hash:CRC-32=0x8432b585]]]*/
/* Wait if `*uaddr < below_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_futexlock_timedwaitwhile_below64, libc_futexlock_timedwaitwhile_below);
#else
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.futexlock.futexlock_timedwaitwhile_below64") int
NOTHROW_RPC(LIBCCALL libc_futexlock_timedwaitwhile_below64)(lfutex_t *ulockaddr,
                                                            lfutex_t *uaddr,
                                                            lfutex_t below_value,
                                                            struct timespec64 const *rel_timeout)
/*[[[body:futexlock_timedwaitwhile_below64]]]*/
{
	int result;
	SPIN_WHILE(ATOMIC_READ(*uaddr) < below_value);
	result = (int)libc_lfutexlock_impl(ulockaddr,
	                                   uaddr,
	                                   LFUTEX_WAIT_WHILE_BELOW |
	                                   LFUTEX_WAIT_FLAG_TIMEOUT_RELATIVE,
	                                   (uintptr_t)below_value,
	                                   rel_timeout,
	                                   (uintptr_t)0);
	return result;
}
#endif /* MAGIC:alias */
/*[[[end:futexlock_timedwaitwhile_below64]]]*/

/*[[[head:futexlock_timedwaitwhile_aboveequal64,hash:CRC-32=0x674333da]]]*/
/* Wait if `*uaddr >= above_equal_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_futexlock_timedwaitwhile_aboveequal64, libc_futexlock_timedwaitwhile_aboveequal);
#else
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.futexlock.futexlock_timedwaitwhile_aboveequal64") int
NOTHROW_RPC(LIBCCALL libc_futexlock_timedwaitwhile_aboveequal64)(lfutex_t *ulockaddr,
                                                                 lfutex_t *uaddr,
                                                                 lfutex_t above_equal_value,
                                                                 struct timespec64 const *rel_timeout)
/*[[[body:futexlock_timedwaitwhile_aboveequal64]]]*/
{
	int result;
	SPIN_WHILE(ATOMIC_READ(*uaddr) >= above_equal_value);
	result = (int)libc_lfutexlock_impl(ulockaddr,
	                                   uaddr,
	                                   likely(above_equal_value != 0)
	                                   ? LFUTEX_WAIT_WHILE_ABOVE | LFUTEX_WAIT_FLAG_TIMEOUT_RELATIVE
	                                   : LFUTEX_WAIT | LFUTEX_WAIT_FLAG_TIMEOUT_RELATIVE,
	                                   (uintptr_t)above_equal_value - 1,
	                                   rel_timeout,
	                                   (uintptr_t)0);
	return result;
}
#endif /* MAGIC:alias */
/*[[[end:futexlock_timedwaitwhile_aboveequal64]]]*/

/*[[[head:futexlock_timedwaitwhile_belowequal64,hash:CRC-32=0x3d875bc5]]]*/
/* Wait if `*uaddr <= below_equal_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_futexlock_timedwaitwhile_belowequal64, libc_futexlock_timedwaitwhile_belowequal);
#else
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.futexlock.futexlock_timedwaitwhile_belowequal64") int
NOTHROW_RPC(LIBCCALL libc_futexlock_timedwaitwhile_belowequal64)(lfutex_t *ulockaddr,
                                                                 lfutex_t *uaddr,
                                                                 lfutex_t below_equal_value,
                                                                 struct timespec64 const *rel_timeout)
/*[[[body:futexlock_timedwaitwhile_belowequal64]]]*/
{
	int result;
	SPIN_WHILE(ATOMIC_READ(*uaddr) <= below_equal_value);
	result = (int)libc_lfutexlock_impl(ulockaddr,
	                                   uaddr,
	                                   likely(below_equal_value != (lfutex_t)-1)
	                                   ? LFUTEX_WAIT_WHILE_BELOW | LFUTEX_WAIT_FLAG_TIMEOUT_RELATIVE
	                                   : LFUTEX_WAIT | LFUTEX_WAIT_FLAG_TIMEOUT_RELATIVE,
	                                   (uintptr_t)below_equal_value + 1,
	                                   rel_timeout,
	                                   (uintptr_t)0);
	return result;
}
#endif /* MAGIC:alias */
/*[[[end:futexlock_timedwaitwhile_belowequal64]]]*/

/*[[[head:futexlock_timedwaitwhile_cmpxch64,hash:CRC-32=0xeeeaf7f7]]]*/
/* Wait if `*uaddr == old_value', and set `*uaddr = new_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted (*uaddr was still set to new_value)
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_futexlock_timedwaitwhile_cmpxch64, libc_futexlock_timedwaitwhile_cmpxch);
#else
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.futexlock.futexlock_timedwaitwhile_cmpxch64") int
NOTHROW_RPC(LIBCCALL libc_futexlock_timedwaitwhile_cmpxch64)(lfutex_t *ulockaddr,
                                                             lfutex_t *uaddr,
                                                             lfutex_t old_value,
                                                             lfutex_t new_value,
                                                             struct timespec64 const *rel_timeout)
/*[[[body:futexlock_timedwaitwhile_cmpxch64]]]*/
{
	int result;
	SPIN_WHILE(ATOMIC_READ(*uaddr) != old_value);
	result = (int)libc_lfutexlock_impl(ulockaddr,
	                                   uaddr,
	                                   LFUTEX_WAIT_WHILE_CMPXCH |
	                                   LFUTEX_WAIT_FLAG_TIMEOUT_RELATIVE,
	                                   (uintptr_t)old_value,
	                                   rel_timeout,
	                                   (uintptr_t)new_value);
	return result;
}
#endif /* MAGIC:alias */
/*[[[end:futexlock_timedwaitwhile_cmpxch64]]]*/

/*[[[head:futexlock_timedwaituntil_cmpxch64,hash:CRC-32=0xd8305c87]]]*/
/* Wait if `*uaddr != old_value', and set `*uaddr = new_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted (*uaddr was still set to new_value)
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_futexlock_timedwaituntil_cmpxch64, libc_futexlock_timedwaituntil_cmpxch);
#else
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.futexlock.futexlock_timedwaituntil_cmpxch64") int
NOTHROW_RPC(LIBCCALL libc_futexlock_timedwaituntil_cmpxch64)(lfutex_t *ulockaddr,
                                                             lfutex_t *uaddr,
                                                             lfutex_t old_value,
                                                             lfutex_t new_value,
                                                             struct timespec64 const *rel_timeout)
/*[[[body:futexlock_timedwaituntil_cmpxch64]]]*/
{
	int result;
	SPIN_WHILE(futex_trywaituntil_cmpxch(uaddr, old_value, new_value) == 0);
	result = (int)libc_lfutexlock_impl(ulockaddr,
	                                   uaddr,
	                                   LFUTEX_WAIT_UNTIL_CMPXCH |
	                                   LFUTEX_WAIT_FLAG_TIMEOUT_RELATIVE,
	                                   (uintptr_t)old_value,
	                                   rel_timeout,
	                                   (uintptr_t)new_value);
	return result;
}
#endif /* MAGIC:alias */
/*[[[end:futexlock_timedwaituntil_cmpxch64]]]*/

/*[[[head:futexlock_timedwaitlock64,hash:CRC-32=0xba095e73]]]*/
/* Acquire a managed futex lock (s.a. `LFUTEX_WAIT_LOCK')
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted (*uaddr was still set to new_value)
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_futexlock_timedwaitlock64, libc_futexlock_timedwaitlock);
#else
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.futexlock.futexlock_timedwaitlock64") int
NOTHROW_RPC(LIBCCALL libc_futexlock_timedwaitlock64)(lfutex_t *ulockaddr,
                                                     lfutex_t *uaddr,
                                                     struct timespec64 const *rel_timeout)
/*[[[body:futexlock_timedwaitlock64]]]*/
{
	int result;
	SPIN_WHILE(futex_trywaitlock(uaddr) == 0);
	result = (int)libc_lfutexlock_impl(ulockaddr,
	                                   uaddr,
	                                   LFUTEX_WAIT_LOCK |
	                                   LFUTEX_WAIT_FLAG_TIMEOUT_RELATIVE,
	                                   (uintptr_t)0,
	                                   rel_timeout,
	                                   (uintptr_t)0);
	return result;
}
#endif /* MAGIC:alias */
/*[[[end:futexlock_timedwaitlock64]]]*/

/*[[[head:futexlock_timedwaitwhile_exactbits64,hash:CRC-32=0xceb2fec2]]]*/
/* Wait if `(*uaddr & bitmask) == setmask'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_futexlock_timedwaitwhile_exactbits64, libc_futexlock_timedwaitwhile_exactbits);
#else
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.futexlock.futexlock_timedwaitwhile_exactbits64") int
NOTHROW_RPC(LIBCCALL libc_futexlock_timedwaitwhile_exactbits64)(lfutex_t *ulockaddr,
                                                                lfutex_t *uaddr,
                                                                lfutex_t bitmask,
                                                                lfutex_t setmask,
                                                                struct timespec64 const *rel_timeout)
/*[[[body:futexlock_timedwaitwhile_exactbits64]]]*/
{
	int result;
	SPIN_WHILE((ATOMIC_READ(*uaddr) & bitmask) == setmask);
	result = (int)libc_lfutexlock_impl(ulockaddr,
	                                   uaddr,
	                                   LFUTEX_WAIT_WHILE_BITMASK |
	                                   LFUTEX_WAIT_FLAG_TIMEOUT_RELATIVE,
	                                   (uintptr_t)bitmask,
	                                   rel_timeout,
	                                   (uintptr_t)setmask);
	return result;
}
#endif /* MAGIC:alias */
/*[[[end:futexlock_timedwaitwhile_exactbits64]]]*/

/*[[[head:futexlock_timedwaituntil_exactbits64,hash:CRC-32=0xba381693]]]*/
/* Wait if `(*uaddr & bitmask) != setmask'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_futexlock_timedwaituntil_exactbits64, libc_futexlock_timedwaituntil_exactbits);
#else
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.futexlock.futexlock_timedwaituntil_exactbits64") int
NOTHROW_RPC(LIBCCALL libc_futexlock_timedwaituntil_exactbits64)(lfutex_t *ulockaddr,
                                                                lfutex_t *uaddr,
                                                                lfutex_t bitmask,
                                                                lfutex_t setmask,
                                                                struct timespec64 const *rel_timeout)
/*[[[body:futexlock_timedwaituntil_exactbits64]]]*/
{
	int result;
	SPIN_WHILE((ATOMIC_READ(*uaddr) & bitmask) != setmask);
	result = (int)libc_lfutexlock_impl(ulockaddr,
	                                   uaddr,
	                                   LFUTEX_WAIT_UNTIL_BITMASK |
	                                   LFUTEX_WAIT_FLAG_TIMEOUT_RELATIVE,
	                                   (uintptr_t)bitmask,
	                                   rel_timeout,
	                                   (uintptr_t)setmask);
	return result;
}
#endif /* MAGIC:alias */
/*[[[end:futexlock_timedwaituntil_exactbits64]]]*/

/*[[[head:futexlock_timedwaitwhile_anybit64,hash:CRC-32=0x29ec81ed]]]*/
/* Wait if `(*uaddr & bitmask) != 0'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_futexlock_timedwaitwhile_anybit64, libc_futexlock_timedwaitwhile_anybit);
#else
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.futexlock.futexlock_timedwaitwhile_anybit64") int
NOTHROW_RPC(LIBCCALL libc_futexlock_timedwaitwhile_anybit64)(lfutex_t *ulockaddr,
                                                             lfutex_t *uaddr,
                                                             lfutex_t bitmask,
                                                             struct timespec64 const *rel_timeout)
/*[[[body:futexlock_timedwaitwhile_anybit64]]]*/
{
	int result;
	SPIN_WHILE((ATOMIC_READ(*uaddr) & bitmask) != 0);
	result = (int)libc_lfutexlock_impl(ulockaddr,
	                                   uaddr,
	                                   LFUTEX_WAIT_UNTIL_BITMASK |
	                                   LFUTEX_WAIT_FLAG_TIMEOUT_RELATIVE,
	                                   (uintptr_t)bitmask,
	                                   rel_timeout,
	                                   (uintptr_t)0);
	return result;
}
#endif /* MAGIC:alias */
/*[[[end:futexlock_timedwaitwhile_anybit64]]]*/

/*[[[head:futexlock_timedwaitwhile_allbits64,hash:CRC-32=0x84fc7876]]]*/
/* Wait if `(*uaddr & bitmask) == bitmask'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_futexlock_timedwaitwhile_allbits64, libc_futexlock_timedwaitwhile_allbits);
#else
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.futexlock.futexlock_timedwaitwhile_allbits64") int
NOTHROW_RPC(LIBCCALL libc_futexlock_timedwaitwhile_allbits64)(lfutex_t *ulockaddr,
                                                              lfutex_t *uaddr,
                                                              lfutex_t bitmask,
                                                              struct timespec64 const *rel_timeout)
/*[[[body:futexlock_timedwaitwhile_allbits64]]]*/
{
	int result;
	SPIN_WHILE((ATOMIC_READ(*uaddr) & bitmask) == bitmask);
	result = (int)libc_lfutexlock_impl(ulockaddr,
	                                   uaddr,
	                                   LFUTEX_WAIT_WHILE_BITMASK |
	                                   LFUTEX_WAIT_FLAG_TIMEOUT_RELATIVE,
	                                   (uintptr_t)bitmask,
	                                   rel_timeout,
	                                   (uintptr_t)bitmask);
	return result;
}
#endif /* MAGIC:alias */
/*[[[end:futexlock_timedwaitwhile_allbits64]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:CRC-32=0xec38ab8c]]]*/
DEFINE_PUBLIC_WEAK_ALIAS(lfutexlock, libc_lfutexlock);
DEFINE_PUBLIC_WEAK_ALIAS(lfutexlock64, libc_lfutexlock64);
DEFINE_PUBLIC_WEAK_ALIAS(futexlock_wake, libc_futexlock_wake);
DEFINE_PUBLIC_WEAK_ALIAS(futexlock_wakeall, libc_futexlock_wakeall);
DEFINE_PUBLIC_WEAK_ALIAS(futexlock_waitwhile, libc_futexlock_waitwhile);
DEFINE_PUBLIC_WEAK_ALIAS(futexlock_waituntil, libc_futexlock_waituntil);
DEFINE_PUBLIC_WEAK_ALIAS(futexlock_waitwhile_above, libc_futexlock_waitwhile_above);
DEFINE_PUBLIC_WEAK_ALIAS(futexlock_waitwhile_below, libc_futexlock_waitwhile_below);
DEFINE_PUBLIC_WEAK_ALIAS(futexlock_waitwhile_aboveequal, libc_futexlock_waitwhile_aboveequal);
DEFINE_PUBLIC_WEAK_ALIAS(futexlock_waitwhile_belowequal, libc_futexlock_waitwhile_belowequal);
DEFINE_PUBLIC_WEAK_ALIAS(futexlock_waitwhile_cmpxch, libc_futexlock_waitwhile_cmpxch);
DEFINE_PUBLIC_WEAK_ALIAS(futexlock_waituntil_cmpxch, libc_futexlock_waituntil_cmpxch);
DEFINE_PUBLIC_WEAK_ALIAS(futexlock_waitlock, libc_futexlock_waitlock);
DEFINE_PUBLIC_WEAK_ALIAS(futexlock_waitwhile_exactbits, libc_futexlock_waitwhile_exactbits);
DEFINE_PUBLIC_WEAK_ALIAS(futexlock_waituntil_exactbits, libc_futexlock_waituntil_exactbits);
DEFINE_PUBLIC_WEAK_ALIAS(futexlock_waitwhile_anybit, libc_futexlock_waitwhile_anybit);
DEFINE_PUBLIC_WEAK_ALIAS(futexlock_waitwhile_allbits, libc_futexlock_waitwhile_allbits);
DEFINE_PUBLIC_WEAK_ALIAS(futexlock_timedwaitwhile, libc_futexlock_timedwaitwhile);
DEFINE_PUBLIC_WEAK_ALIAS(futexlock_timedwaituntil, libc_futexlock_timedwaituntil);
DEFINE_PUBLIC_WEAK_ALIAS(futexlock_timedwaitwhile_above, libc_futexlock_timedwaitwhile_above);
DEFINE_PUBLIC_WEAK_ALIAS(futexlock_timedwaitwhile_below, libc_futexlock_timedwaitwhile_below);
DEFINE_PUBLIC_WEAK_ALIAS(futexlock_timedwaitwhile_aboveequal, libc_futexlock_timedwaitwhile_aboveequal);
DEFINE_PUBLIC_WEAK_ALIAS(futexlock_timedwaitwhile_belowequal, libc_futexlock_timedwaitwhile_belowequal);
DEFINE_PUBLIC_WEAK_ALIAS(futexlock_timedwaitwhile_cmpxch, libc_futexlock_timedwaitwhile_cmpxch);
DEFINE_PUBLIC_WEAK_ALIAS(futexlock_timedwaituntil_cmpxch, libc_futexlock_timedwaituntil_cmpxch);
DEFINE_PUBLIC_WEAK_ALIAS(futexlock_timedwaitlock, libc_futexlock_timedwaitlock);
DEFINE_PUBLIC_WEAK_ALIAS(futexlock_timedwaitwhile_exactbits, libc_futexlock_timedwaitwhile_exactbits);
DEFINE_PUBLIC_WEAK_ALIAS(futexlock_timedwaituntil_exactbits, libc_futexlock_timedwaituntil_exactbits);
DEFINE_PUBLIC_WEAK_ALIAS(futexlock_timedwaitwhile_anybit, libc_futexlock_timedwaitwhile_anybit);
DEFINE_PUBLIC_WEAK_ALIAS(futexlock_timedwaitwhile_allbits, libc_futexlock_timedwaitwhile_allbits);
DEFINE_PUBLIC_WEAK_ALIAS(futexlock_timedwaitwhile64, libc_futexlock_timedwaitwhile64);
DEFINE_PUBLIC_WEAK_ALIAS(futexlock_timedwaituntil64, libc_futexlock_timedwaituntil64);
DEFINE_PUBLIC_WEAK_ALIAS(futexlock_timedwaitwhile_above64, libc_futexlock_timedwaitwhile_above64);
DEFINE_PUBLIC_WEAK_ALIAS(futexlock_timedwaitwhile_below64, libc_futexlock_timedwaitwhile_below64);
DEFINE_PUBLIC_WEAK_ALIAS(futexlock_timedwaitwhile_aboveequal64, libc_futexlock_timedwaitwhile_aboveequal64);
DEFINE_PUBLIC_WEAK_ALIAS(futexlock_timedwaitwhile_belowequal64, libc_futexlock_timedwaitwhile_belowequal64);
DEFINE_PUBLIC_WEAK_ALIAS(futexlock_timedwaitwhile_cmpxch64, libc_futexlock_timedwaitwhile_cmpxch64);
DEFINE_PUBLIC_WEAK_ALIAS(futexlock_timedwaituntil_cmpxch64, libc_futexlock_timedwaituntil_cmpxch64);
DEFINE_PUBLIC_WEAK_ALIAS(futexlock_timedwaitlock64, libc_futexlock_timedwaitlock64);
DEFINE_PUBLIC_WEAK_ALIAS(futexlock_timedwaitwhile_exactbits64, libc_futexlock_timedwaitwhile_exactbits64);
DEFINE_PUBLIC_WEAK_ALIAS(futexlock_timedwaituntil_exactbits64, libc_futexlock_timedwaituntil_exactbits64);
DEFINE_PUBLIC_WEAK_ALIAS(futexlock_timedwaitwhile_anybit64, libc_futexlock_timedwaitwhile_anybit64);
DEFINE_PUBLIC_WEAK_ALIAS(futexlock_timedwaitwhile_allbits64, libc_futexlock_timedwaitwhile_allbits64);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_KOS_FUTEXLOCK_C */
