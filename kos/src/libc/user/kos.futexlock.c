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
#include "kos.futexlock.h"
#include <kos/futex.h>
#include <kos/syscalls.h>
#include <hybrid/atomic.h>

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





/*[[[start:implementation]]]*/

/*[[[head:lfutexlock,hash:0xdf1120e4]]]*/
/* >> lfutexlock(2)
 * High-level wrapper around the lfutexlockat system call
 * This function behaves identical to the lfutex() system call, except that it takes
 * two futex addresses, where `ulockaddr' is used as a flag specifying that threads may
 * be waiting to be awoken once `LFUTEX_WAKE' is invoked on that memory location, whilst
 * the other futex address is used for the wait-while-condition checking, the same way
 * those checks would also be performed by the `lfutex() system call'
 * @param: command: One of:
 *    - LFUTEX_WAKE:              (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAKE, size_t count)
 *    - LFUTEX_NOP:               (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_NOP, size_t ignored)
 *    - LFUTEX_WAIT:              (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT, lfutexlock ignored, struct timespec const *timeout)
 *    - LFUTEX_WAIT_LOCK:         (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_LOCK, lfutex_t lock_value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE:        (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE, lfutex_t value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_UNTIL:        (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_UNTIL, lfutex_t value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_ABOVE:  (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE_ABOVE, lfutex_t value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_BELOW:  (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE_BELOW, lfutex_t value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_CMPXCH: (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE_CMPXCH, lfutex_t oldval, struct timespec const *timeout, lfutex_t newval)
 *    - LFUTEX_WAIT_UNTIL_CMPXCH: (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_UNTIL_CMPXCH, lfutex_t oldval, struct timespec const *timeout, lfutex_t newval)
 * @param: timeout: Timeout for wait operations (s.a. `LFUTEX_WAIT_FLAG_TIMEOUT_*')
 * @return: * : Depending on `command'
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINVAL:    The given `command' is invalid
 * @return: -1:EINTR:     A blocking futex-wait operation was interrupted
 * @return: -1:ETIMEDOUT: A blocking futex-wait operation has timed out */
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.lfutexlock") ssize_t
NOTHROW_RPC(LIBCCALL libc_lfutexlock)(lfutex_t *ulockaddr,
                                      lfutex_t *uaddr,
                                      syscall_ulong_t command,
                                      lfutex_t val,
                                      /*struct timespec const *timeout, lfutex_t val2*/...)
/*[[[body:lfutexlock]]]*/
{
	va_list args;
	struct __timespec32 *timeout;
	struct timespec64 tms64;
	lfutex_t val2;
	if (!LFUTEX_USES_TIMEOUT(command))
		return lfutexlock64(ulockaddr, uaddr, command, val);
	va_start(args, val);
	timeout = va_arg(args, struct __timespec32 *);
	val2    = va_arg(args, lfutex_t);
	va_end(args);
	if (!timeout) {
		return lfutexlock64(ulockaddr,
		                    uaddr,
		                    command,
		                    val,
		                    (struct timespec64 *)NULL,
		                    val2);
	}
	tms64.tv_sec  = (time64_t)timeout->tv_sec;
	tms64.tv_nsec = timeout->tv_nsec;
	return lfutexlock64(ulockaddr,
	                    uaddr,
	                    command,
	                    val,
	                    &tms64,
	                    val2);
}
/*[[[end:lfutexlock]]]*/

/*[[[head:lfutexlock64,hash:0xdb8ed0bd]]]*/
/* >> lfutexlock(2)
 * High-level wrapper around the lfutexlockat system call
 * This function behaves identical to the lfutex() system call, except that it takes
 * two futex addresses, where `ulockaddr' is used as a flag specifying that threads may
 * be waiting to be awoken once `LFUTEX_WAKE' is invoked on that memory location, whilst
 * the other futex address is used for the wait-while-condition checking, the same way
 * those checks would also be performed by the `lfutex() system call'
 * @param: command: One of:
 *    - LFUTEX_WAKE:              (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAKE, size_t count)
 *    - LFUTEX_NOP:               (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_NOP, size_t ignored)
 *    - LFUTEX_WAIT:              (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT, lfutexlock ignored, struct timespec const *timeout)
 *    - LFUTEX_WAIT_LOCK:         (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_LOCK, lfutex_t lock_value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE:        (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE, lfutex_t value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_UNTIL:        (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_UNTIL, lfutex_t value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_ABOVE:  (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE_ABOVE, lfutex_t value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_BELOW:  (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE_BELOW, lfutex_t value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_CMPXCH: (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE_CMPXCH, lfutex_t oldval, struct timespec const *timeout, lfutex_t newval)
 *    - LFUTEX_WAIT_UNTIL_CMPXCH: (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_UNTIL_CMPXCH, lfutex_t oldval, struct timespec const *timeout, lfutex_t newval)
 * @param: timeout: Timeout for wait operations (s.a. `LFUTEX_WAIT_FLAG_TIMEOUT_*')
 * @return: * : Depending on `command'
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINVAL:    The given `command' is invalid
 * @return: -1:EINTR:     A blocking futex-wait operation was interrupted
 * @return: -1:ETIMEDOUT: A blocking futex-wait operation has timed out */
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_lfutexlock64, libc_lfutexlock);
#else
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.lfutexlock64") ssize_t
NOTHROW_RPC(LIBCCALL libc_lfutexlock64)(lfutex_t *ulockaddr,
                                        lfutex_t *uaddr,
                                        syscall_ulong_t command,
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
	result = sys_lfutexlock(ulockaddr,
	                        uaddr,
	                        command,
	                        val,
	                        timeout,
	                        val2);
	return libc_seterrno_syserr(result);
}
#endif /* MAGIC:alias */
/*[[[end:lfutexlock64]]]*/

/*[[[head:futexlock_wake,hash:0xd716e961]]]*/
/* A more efficient variant of `futex_wake()' that can be used to wake up threads waiting
 * on some given futex-lock. - This method of waking is faster, since it doesn't invoke a
 * system call when no thread is waiting on the given lock */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.futexlock_wake") ssize_t
NOTHROW_NCX(LIBCCALL libc_futexlock_wake)(lfutex_t *ulockaddr,
                                          size_t max_wake)
/*[[[body:futexlock_wake]]]*/
{
	ssize_t result;
	if (ATOMIC_XCH(*ulockaddr, 0) == 0)
		return 0; /* Nothing to do here. */
	result = sys_lfutex(ulockaddr, LFUTEX_WAKE, (uintptr_t)max_wake, NULL, 0);
	return libc_seterrno_syserr(result);
}
/*[[[end:futexlock_wake]]]*/

/*[[[head:futexlock_wakeall,hash:0x729b1c5a]]]*/
/* A more efficient variant of `futex_wake()' that can be used to wake up threads waiting
 * on some given futex-lock. - This method of waking is faster, since it doesn't invoke a
 * system call when no thread is waiting on the given lock */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.futexlock_wakeall") ssize_t
NOTHROW_NCX(LIBCCALL libc_futexlock_wakeall)(lfutex_t *ulockaddr)
/*[[[body:futexlock_wakeall]]]*/
{
	ssize_t result;
	if (ATOMIC_XCH(*ulockaddr, 0) == 0)
		return 0; /* Nothing to do here. */
	result = sys_lfutex(ulockaddr, LFUTEX_WAKE, (uintptr_t)-1, NULL, 0);
	return libc_seterrno_syserr(result);
}
/*[[[end:futexlock_wakeall]]]*/

/*[[[head:futexlock_waitwhile,hash:0x5ce4d2c4]]]*/
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.futexlock_waitwhile") int
NOTHROW_RPC(LIBCCALL libc_futexlock_waitwhile)(lfutex_t *ulockaddr,
                                               lfutex_t *uaddr,
                                               lfutex_t equal_to_value)
/*[[[body:futexlock_waitwhile]]]*/
{
	errno_t result;
	SPIN_WHILE(ATOMIC_READ(*uaddr) == equal_to_value);
	result = (errno_t)sys_lfutexlock(ulockaddr,
	                                 uaddr,
	                                 LFUTEX_WAIT_WHILE,
	                                 (uintptr_t)equal_to_value,
	                                 NULL,
	                                 0);
	return libc_seterrno_syserr(result);
}
/*[[[end:futexlock_waitwhile]]]*/

/*[[[head:futexlock_waituntil,hash:0x40fdfb2a]]]*/
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.futexlock_waituntil") int
NOTHROW_RPC(LIBCCALL libc_futexlock_waituntil)(lfutex_t *ulockaddr,
                                               lfutex_t *uaddr,
                                               lfutex_t not_equal_to_value)
/*[[[body:futexlock_waituntil]]]*/
{
	errno_t result;
	SPIN_WHILE(ATOMIC_READ(*uaddr) != not_equal_to_value);
	result = (errno_t)sys_lfutexlock(ulockaddr,
	                                 uaddr,
	                                 LFUTEX_WAIT_UNTIL,
	                                 (uintptr_t)not_equal_to_value,
	                                 NULL,
	                                 0);
	return libc_seterrno_syserr(result);
}
/*[[[end:futexlock_waituntil]]]*/

/*[[[head:futexlock_waitwhile_above,hash:0x55e487a2]]]*/
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.futexlock_waitwhile_above") int
NOTHROW_RPC(LIBCCALL libc_futexlock_waitwhile_above)(lfutex_t *ulockaddr,
                                                     lfutex_t *uaddr,
                                                     lfutex_t above_value)
/*[[[body:futexlock_waitwhile_above]]]*/
{
	errno_t result;
	SPIN_WHILE(ATOMIC_READ(*uaddr) > above_value);
	result = (errno_t)sys_lfutexlock(ulockaddr,
	                                 uaddr,
	                                 LFUTEX_WAIT_WHILE_ABOVE,
	                                 (uintptr_t)above_value,
	                                 NULL,
	                                 0);
	return libc_seterrno_syserr(result);
}
/*[[[end:futexlock_waitwhile_above]]]*/

/*[[[head:futexlock_waitwhile_below,hash:0xb41031a0]]]*/
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.futexlock_waitwhile_below") int
NOTHROW_RPC(LIBCCALL libc_futexlock_waitwhile_below)(lfutex_t *ulockaddr,
                                                     lfutex_t *uaddr,
                                                     lfutex_t below_value)
/*[[[body:futexlock_waitwhile_below]]]*/
{
	errno_t result;
	SPIN_WHILE(ATOMIC_READ(*uaddr) < below_value);
	result = (errno_t)sys_lfutexlock(ulockaddr,
	                                 uaddr,
	                                 LFUTEX_WAIT_WHILE_BELOW,
	                                 (uintptr_t)below_value,
	                                 NULL,
	                                 0);
	return libc_seterrno_syserr(result);
}
/*[[[end:futexlock_waitwhile_below]]]*/

/*[[[head:futexlock_waitwhile_aboveequal,hash:0xb709c613]]]*/
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.futexlock_waitwhile_aboveequal") int
NOTHROW_RPC(LIBCCALL libc_futexlock_waitwhile_aboveequal)(lfutex_t *ulockaddr,
                                                          lfutex_t *uaddr,
                                                          lfutex_t above_equal_value)
/*[[[body:futexlock_waitwhile_aboveequal]]]*/
{
	errno_t result;
	SPIN_WHILE(ATOMIC_READ(*uaddr) >= above_equal_value);
	result = (errno_t)sys_lfutexlock(ulockaddr,
	                                 uaddr,
	                                 likely(above_equal_value != 0)
	                                 ? LFUTEX_WAIT_WHILE_ABOVE
	                                 : LFUTEX_WAIT,
	                                 (uintptr_t)above_equal_value - 1,
	                                 NULL,
	                                 0);
	return libc_seterrno_syserr(result);
}
/*[[[end:futexlock_waitwhile_aboveequal]]]*/

/*[[[head:futexlock_waitwhile_belowequal,hash:0xd7579db7]]]*/
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.futexlock_waitwhile_belowequal") int
NOTHROW_RPC(LIBCCALL libc_futexlock_waitwhile_belowequal)(lfutex_t *ulockaddr,
                                                          lfutex_t *uaddr,
                                                          lfutex_t below_equal_value)
/*[[[body:futexlock_waitwhile_belowequal]]]*/
{
	errno_t result;
	SPIN_WHILE(ATOMIC_READ(*uaddr) <= below_equal_value);
	result = (errno_t)sys_lfutexlock(ulockaddr,
	                                 uaddr,
	                                 likely(below_equal_value != (lfutex_t)-1)
	                                 ? LFUTEX_WAIT_WHILE_BELOW
	                                 : LFUTEX_WAIT,
	                                 (uintptr_t)below_equal_value + 1,
	                                 NULL,
	                                 0);
	return libc_seterrno_syserr(result);
}
/*[[[end:futexlock_waitwhile_belowequal]]]*/

/*[[[head:futexlock_waitwhile_cmpxch,hash:0x143ce42a]]]*/
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.futexlock_waitwhile_cmpxch") int
NOTHROW_RPC(LIBCCALL libc_futexlock_waitwhile_cmpxch)(lfutex_t *ulockaddr,
                                                      lfutex_t *uaddr,
                                                      lfutex_t old_value,
                                                      lfutex_t new_value)
/*[[[body:futexlock_waitwhile_cmpxch]]]*/
{
	errno_t result;
	SPIN_WHILE(ATOMIC_READ(*uaddr) == old_value);
	result = (errno_t)sys_lfutexlock(ulockaddr,
	                                 uaddr,
	                                 LFUTEX_WAIT_WHILE_CMPXCH,
	                                 (uintptr_t)old_value,
	                                 NULL,
	                                 (uintptr_t)new_value);
	return libc_seterrno_syserr(result);
}
/*[[[end:futexlock_waitwhile_cmpxch]]]*/

/*[[[head:futexlock_waituntil_cmpxch,hash:0xd8d91324]]]*/
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.futexlock_waituntil_cmpxch") int
NOTHROW_RPC(LIBCCALL libc_futexlock_waituntil_cmpxch)(lfutex_t *ulockaddr,
                                                      lfutex_t *uaddr,
                                                      lfutex_t old_value,
                                                      lfutex_t new_value)
/*[[[body:futexlock_waituntil_cmpxch]]]*/
{
	errno_t result;
	SPIN_WHILE(futex_trywaituntil_cmpxch(uaddr, old_value, new_value) == 0);
	result = (errno_t)sys_lfutexlock(ulockaddr,
	                                 uaddr,
	                                 LFUTEX_WAIT_UNTIL_CMPXCH,
	                                 (uintptr_t)old_value,
	                                 NULL,
	                                 (uintptr_t)new_value);
	return libc_seterrno_syserr(result);
}
/*[[[end:futexlock_waituntil_cmpxch]]]*/

/*[[[head:futexlock_waitlock,hash:0x978a3358]]]*/
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.futexlock_waitlock") int
NOTHROW_RPC(LIBCCALL libc_futexlock_waitlock)(lfutex_t *ulockaddr,
                                              lfutex_t *uaddr)
/*[[[body:futexlock_waitlock]]]*/
{
	errno_t result;
	SPIN_WHILE(futex_trywaitlock(uaddr) == 0);
	result = (errno_t)sys_lfutexlock(ulockaddr,
	                                 uaddr,
	                                 LFUTEX_WAIT_LOCK,
	                                 0,
	                                 NULL,
	                                 0);
	return libc_seterrno_syserr(result);
}
/*[[[end:futexlock_waitlock]]]*/

/*[[[head:futexlock_waitwhile_exactbits,hash:0xac2c2d31]]]*/
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.futexlock_waitwhile_exactbits") int
NOTHROW_RPC(LIBCCALL libc_futexlock_waitwhile_exactbits)(lfutex_t *ulockaddr,
                                                         lfutex_t *uaddr,
                                                         lfutex_t bitmask,
                                                         lfutex_t setmask)
/*[[[body:futexlock_waitwhile_exactbits]]]*/
{
	errno_t result;
	SPIN_WHILE((ATOMIC_READ(*uaddr) & bitmask) == setmask);
	result = (errno_t)sys_lfutexlock(ulockaddr,
	                                 uaddr,
	                                 LFUTEX_WAIT_WHILE_BITMASK,
	                                 (uintptr_t)bitmask,
	                                 NULL,
	                                 (uintptr_t)setmask);
	return libc_seterrno_syserr(result);
}
/*[[[end:futexlock_waitwhile_exactbits]]]*/

/*[[[head:futexlock_waituntil_exactbits,hash:0xbac513c8]]]*/
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.futexlock_waituntil_exactbits") int
NOTHROW_RPC(LIBCCALL libc_futexlock_waituntil_exactbits)(lfutex_t *ulockaddr,
                                                         lfutex_t *uaddr,
                                                         lfutex_t bitmask,
                                                         lfutex_t setmask)
/*[[[body:futexlock_waituntil_exactbits]]]*/
{
	errno_t result;
	SPIN_WHILE((ATOMIC_READ(*uaddr) & bitmask) != setmask);
	result = (errno_t)sys_lfutexlock(ulockaddr,
	                                 uaddr,
	                                 LFUTEX_WAIT_UNTIL_BITMASK,
	                                 (uintptr_t)bitmask,
	                                 NULL,
	                                 (uintptr_t)setmask);
	return libc_seterrno_syserr(result);
}
/*[[[end:futexlock_waituntil_exactbits]]]*/

/*[[[head:futexlock_waitwhile_anybit,hash:0x6502c0ca]]]*/
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.futexlock_waitwhile_anybit") int
NOTHROW_RPC(LIBCCALL libc_futexlock_waitwhile_anybit)(lfutex_t *ulockaddr,
                                                      lfutex_t *uaddr,
                                                      lfutex_t bitmask)
/*[[[body:futexlock_waitwhile_anybit]]]*/
{
	errno_t result;
	SPIN_WHILE((ATOMIC_READ(*uaddr) & bitmask) != 0);
	result = (errno_t)sys_lfutexlock(ulockaddr,
	                                 uaddr,
	                                 LFUTEX_WAIT_UNTIL_BITMASK,
	                                 (uintptr_t)bitmask,
	                                 NULL,
	                                 (uintptr_t)0);
	return libc_seterrno_syserr(result);
}
/*[[[end:futexlock_waitwhile_anybit]]]*/

/*[[[head:futexlock_waitwhile_allbits,hash:0x19e69b9a]]]*/
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.futexlock_waitwhile_allbits") int
NOTHROW_RPC(LIBCCALL libc_futexlock_waitwhile_allbits)(lfutex_t *ulockaddr,
                                                       lfutex_t *uaddr,
                                                       lfutex_t bitmask)
/*[[[body:futexlock_waitwhile_allbits]]]*/
{
	errno_t result;
	SPIN_WHILE((ATOMIC_READ(*uaddr) & bitmask) == bitmask);
	result = (errno_t)sys_lfutexlock(ulockaddr,
	                                 uaddr,
	                                 LFUTEX_WAIT_WHILE_BITMASK,
	                                 (uintptr_t)bitmask,
	                                 NULL,
	                                 (uintptr_t)bitmask);
	return libc_seterrno_syserr(result);
}
/*[[[end:futexlock_waitwhile_allbits]]]*/

/*[[[head:futexlock_timedwaitwhile,hash:0xb583f116]]]*/
/* Wait if `*uaddr == equal_to_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.futexlock_timedwaitwhile") int
NOTHROW_RPC(LIBCCALL libc_futexlock_timedwaitwhile)(lfutex_t *ulockaddr,
                                                    lfutex_t *uaddr,
                                                    lfutex_t equal_to_value,
                                                    struct timespec *rel_timeout)
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

/*[[[head:futexlock_timedwaituntil,hash:0xbfa542c8]]]*/
/* Wait if `*uaddr != not_equal_to_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.futexlock_timedwaituntil") int
NOTHROW_RPC(LIBCCALL libc_futexlock_timedwaituntil)(lfutex_t *ulockaddr,
                                                    lfutex_t *uaddr,
                                                    lfutex_t not_equal_to_value,
                                                    struct timespec *rel_timeout)
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

/*[[[head:futexlock_timedwaitwhile_above,hash:0x2fce9259]]]*/
/* Wait if `*uaddr > above_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.futexlock_timedwaitwhile_above") int
NOTHROW_RPC(LIBCCALL libc_futexlock_timedwaitwhile_above)(lfutex_t *ulockaddr,
                                                          lfutex_t *uaddr,
                                                          lfutex_t above_value,
                                                          struct timespec *rel_timeout)
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

/*[[[head:futexlock_timedwaitwhile_below,hash:0x525896ac]]]*/
/* Wait if `*uaddr < below_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.futexlock_timedwaitwhile_below") int
NOTHROW_RPC(LIBCCALL libc_futexlock_timedwaitwhile_below)(lfutex_t *ulockaddr,
                                                          lfutex_t *uaddr,
                                                          lfutex_t below_value,
                                                          struct timespec *rel_timeout)
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

/*[[[head:futexlock_timedwaitwhile_aboveequal,hash:0x9b0e72bc]]]*/
/* Wait if `*uaddr >= above_equal_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.futexlock_timedwaitwhile_aboveequal") int
NOTHROW_RPC(LIBCCALL libc_futexlock_timedwaitwhile_aboveequal)(lfutex_t *ulockaddr,
                                                               lfutex_t *uaddr,
                                                               lfutex_t above_equal_value,
                                                               struct timespec *rel_timeout)
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

/*[[[head:futexlock_timedwaitwhile_belowequal,hash:0xa3c061a7]]]*/
/* Wait if `*uaddr <= below_equal_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.futexlock_timedwaitwhile_belowequal") int
NOTHROW_RPC(LIBCCALL libc_futexlock_timedwaitwhile_belowequal)(lfutex_t *ulockaddr,
                                                               lfutex_t *uaddr,
                                                               lfutex_t below_equal_value,
                                                               struct timespec *rel_timeout)
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

/*[[[head:futexlock_timedwaitwhile_cmpxch,hash:0xb5030db8]]]*/
/* Wait if `*uaddr == old_value', and set `*uaddr = new_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted (*uaddr was still set to new_value)
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.futexlock_timedwaitwhile_cmpxch") int
NOTHROW_RPC(LIBCCALL libc_futexlock_timedwaitwhile_cmpxch)(lfutex_t *ulockaddr,
                                                           lfutex_t *uaddr,
                                                           lfutex_t old_value,
                                                           lfutex_t new_value,
                                                           struct timespec *rel_timeout)
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

/*[[[head:futexlock_timedwaituntil_cmpxch,hash:0x5ac6d62c]]]*/
/* Wait if `*uaddr != old_value', and set `*uaddr = new_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted (*uaddr was still set to new_value)
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.futexlock_timedwaituntil_cmpxch") int
NOTHROW_RPC(LIBCCALL libc_futexlock_timedwaituntil_cmpxch)(lfutex_t *ulockaddr,
                                                           lfutex_t *uaddr,
                                                           lfutex_t old_value,
                                                           lfutex_t new_value,
                                                           struct timespec *rel_timeout)
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

/*[[[head:futexlock_timedwaitlock,hash:0x367fa621]]]*/
/* Acquire a managed futex lock (s.a. `LFUTEX_WAIT_LOCK')
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted (*uaddr was still set to new_value)
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.futexlock_timedwaitlock") int
NOTHROW_RPC(LIBCCALL libc_futexlock_timedwaitlock)(lfutex_t *ulockaddr,
                                                   lfutex_t *uaddr,
                                                   struct timespec *rel_timeout)
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

/*[[[head:futexlock_timedwaitwhile_exactbits,hash:0xa1d9e8cf]]]*/
/* Wait if `(*uaddr & bitmask) == setmask'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.futexlock_timedwaitwhile_exactbits") int
NOTHROW_RPC(LIBCCALL libc_futexlock_timedwaitwhile_exactbits)(lfutex_t *ulockaddr,
                                                              lfutex_t *uaddr,
                                                              lfutex_t bitmask,
                                                              lfutex_t setmask,
                                                              struct timespec *rel_timeout)
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

/*[[[head:futexlock_timedwaituntil_exactbits,hash:0xdb6c97cf]]]*/
/* Wait if `(*uaddr & bitmask) != setmask'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.futexlock_timedwaituntil_exactbits") int
NOTHROW_RPC(LIBCCALL libc_futexlock_timedwaituntil_exactbits)(lfutex_t *ulockaddr,
                                                              lfutex_t *uaddr,
                                                              lfutex_t bitmask,
                                                              lfutex_t setmask,
                                                              struct timespec *rel_timeout)
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

/*[[[head:futexlock_timedwaitwhile_anybit,hash:0xa98cab8b]]]*/
/* Wait if `(*uaddr & bitmask) != 0'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.futexlock_timedwaitwhile_anybit") int
NOTHROW_RPC(LIBCCALL libc_futexlock_timedwaitwhile_anybit)(lfutex_t *ulockaddr,
                                                           lfutex_t *uaddr,
                                                           lfutex_t bitmask,
                                                           struct timespec *rel_timeout)
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

/*[[[head:futexlock_timedwaitwhile_allbits,hash:0xa6eb8acf]]]*/
/* Wait if `(*uaddr & bitmask) == bitmask'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.futexlock_timedwaitwhile_allbits") int
NOTHROW_RPC(LIBCCALL libc_futexlock_timedwaitwhile_allbits)(lfutex_t *ulockaddr,
                                                            lfutex_t *uaddr,
                                                            lfutex_t bitmask,
                                                            struct timespec *rel_timeout)
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

/*[[[head:futexlock_timedwaitwhile64,hash:0x3b7e3ea0]]]*/
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
ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.futexlock_timedwaitwhile64") int
NOTHROW_RPC(LIBCCALL libc_futexlock_timedwaitwhile64)(lfutex_t *ulockaddr,
                                                      lfutex_t *uaddr,
                                                      lfutex_t equal_to_value,
                                                      struct timespec64 *rel_timeout)
/*[[[body:futexlock_timedwaitwhile64]]]*/
{
	errno_t result;
	SPIN_WHILE(ATOMIC_READ(*uaddr) == equal_to_value);
	result = (errno_t)sys_lfutexlock(ulockaddr,
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

/*[[[head:futexlock_timedwaituntil64,hash:0xaab882e3]]]*/
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
ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.futexlock_timedwaituntil64") int
NOTHROW_RPC(LIBCCALL libc_futexlock_timedwaituntil64)(lfutex_t *ulockaddr,
                                                      lfutex_t *uaddr,
                                                      lfutex_t not_equal_to_value,
                                                      struct timespec64 *rel_timeout)
/*[[[body:futexlock_timedwaituntil64]]]*/
{
	errno_t result;
	SPIN_WHILE(ATOMIC_READ(*uaddr) != not_equal_to_value);
	result = (errno_t)sys_lfutexlock(ulockaddr,
	                                 uaddr,
	                                 LFUTEX_WAIT_UNTIL |
	                                 LFUTEX_WAIT_FLAG_TIMEOUT_RELATIVE,
	                                 (uintptr_t)not_equal_to_value,
	                                 rel_timeout,
	                                 (uintptr_t)0);
	return libc_seterrno_syserr(result);
}
#endif /* MAGIC:alias */
/*[[[end:futexlock_timedwaituntil64]]]*/

/*[[[head:futexlock_timedwaitwhile_above64,hash:0x54b8fa57]]]*/
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
ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.futexlock_timedwaitwhile_above64") int
NOTHROW_RPC(LIBCCALL libc_futexlock_timedwaitwhile_above64)(lfutex_t *ulockaddr,
                                                            lfutex_t *uaddr,
                                                            lfutex_t above_value,
                                                            struct timespec64 *rel_timeout)
/*[[[body:futexlock_timedwaitwhile_above64]]]*/
{
	errno_t result;
	SPIN_WHILE(ATOMIC_READ(*uaddr) > above_value);
	result = (errno_t)sys_lfutexlock(ulockaddr,
	                                 uaddr,
	                                 LFUTEX_WAIT_WHILE_ABOVE |
	                                 LFUTEX_WAIT_FLAG_TIMEOUT_RELATIVE,
	                                 (uintptr_t)above_value,
	                                 rel_timeout,
	                                 (uintptr_t)0);
	return libc_seterrno_syserr(result);
}
#endif /* MAGIC:alias */
/*[[[end:futexlock_timedwaitwhile_above64]]]*/

/*[[[head:futexlock_timedwaitwhile_below64,hash:0x1b9b1313]]]*/
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
ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.futexlock_timedwaitwhile_below64") int
NOTHROW_RPC(LIBCCALL libc_futexlock_timedwaitwhile_below64)(lfutex_t *ulockaddr,
                                                            lfutex_t *uaddr,
                                                            lfutex_t below_value,
                                                            struct timespec64 *rel_timeout)
/*[[[body:futexlock_timedwaitwhile_below64]]]*/
{
	errno_t result;
	SPIN_WHILE(ATOMIC_READ(*uaddr) < below_value);
	result = (errno_t)sys_lfutexlock(ulockaddr,
	                                 uaddr,
	                                 LFUTEX_WAIT_WHILE_BELOW |
	                                 LFUTEX_WAIT_FLAG_TIMEOUT_RELATIVE,
	                                 (uintptr_t)below_value,
	                                 rel_timeout,
	                                 (uintptr_t)0);
	return libc_seterrno_syserr(result);
}
#endif /* MAGIC:alias */
/*[[[end:futexlock_timedwaitwhile_below64]]]*/

/*[[[head:futexlock_timedwaitwhile_aboveequal64,hash:0x1d8336c6]]]*/
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
ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.futexlock_timedwaitwhile_aboveequal64") int
NOTHROW_RPC(LIBCCALL libc_futexlock_timedwaitwhile_aboveequal64)(lfutex_t *ulockaddr,
                                                                 lfutex_t *uaddr,
                                                                 lfutex_t above_equal_value,
                                                                 struct timespec64 *rel_timeout)
/*[[[body:futexlock_timedwaitwhile_aboveequal64]]]*/
{
	errno_t result;
	SPIN_WHILE(ATOMIC_READ(*uaddr) >= above_equal_value);
	result = (errno_t)sys_lfutexlock(ulockaddr,
	                                 uaddr,
	                                 likely(above_equal_value != 0)
	                                 ? LFUTEX_WAIT_WHILE_ABOVE | LFUTEX_WAIT_FLAG_TIMEOUT_RELATIVE
	                                 : LFUTEX_WAIT | LFUTEX_WAIT_FLAG_TIMEOUT_RELATIVE,
	                                 (uintptr_t)above_equal_value - 1,
	                                 rel_timeout,
	                                 (uintptr_t)0);
	return libc_seterrno_syserr(result);
}
#endif /* MAGIC:alias */
/*[[[end:futexlock_timedwaitwhile_aboveequal64]]]*/

/*[[[head:futexlock_timedwaitwhile_belowequal64,hash:0xffc9cb81]]]*/
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
ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.futexlock_timedwaitwhile_belowequal64") int
NOTHROW_RPC(LIBCCALL libc_futexlock_timedwaitwhile_belowequal64)(lfutex_t *ulockaddr,
                                                                 lfutex_t *uaddr,
                                                                 lfutex_t below_equal_value,
                                                                 struct timespec64 *rel_timeout)
/*[[[body:futexlock_timedwaitwhile_belowequal64]]]*/
{
	errno_t result;
	SPIN_WHILE(ATOMIC_READ(*uaddr) <= below_equal_value);
	result = (errno_t)sys_lfutexlock(ulockaddr,
	                                 uaddr,
	                                 likely(below_equal_value != (lfutex_t)-1)
	                                 ? LFUTEX_WAIT_WHILE_BELOW | LFUTEX_WAIT_FLAG_TIMEOUT_RELATIVE
	                                 : LFUTEX_WAIT | LFUTEX_WAIT_FLAG_TIMEOUT_RELATIVE,
	                                 (uintptr_t)below_equal_value + 1,
	                                 rel_timeout,
	                                 (uintptr_t)0);
	return libc_seterrno_syserr(result);
}
#endif /* MAGIC:alias */
/*[[[end:futexlock_timedwaitwhile_belowequal64]]]*/

/*[[[head:futexlock_timedwaitwhile_cmpxch64,hash:0xd21f728c]]]*/
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
ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.futexlock_timedwaitwhile_cmpxch64") int
NOTHROW_RPC(LIBCCALL libc_futexlock_timedwaitwhile_cmpxch64)(lfutex_t *ulockaddr,
                                                             lfutex_t *uaddr,
                                                             lfutex_t old_value,
                                                             lfutex_t new_value,
                                                             struct timespec64 *rel_timeout)
/*[[[body:futexlock_timedwaitwhile_cmpxch64]]]*/
{
	errno_t result;
	SPIN_WHILE(ATOMIC_READ(*uaddr) != old_value);
	result = (errno_t)sys_lfutexlock(ulockaddr,
	                                 uaddr,
	                                 LFUTEX_WAIT_WHILE_CMPXCH |
	                                 LFUTEX_WAIT_FLAG_TIMEOUT_RELATIVE,
	                                 (uintptr_t)old_value,
	                                 rel_timeout,
	                                 (uintptr_t)new_value);
	return libc_seterrno_syserr(result);
}
#endif /* MAGIC:alias */
/*[[[end:futexlock_timedwaitwhile_cmpxch64]]]*/

/*[[[head:futexlock_timedwaituntil_cmpxch64,hash:0xa7f13908]]]*/
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
ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.futexlock_timedwaituntil_cmpxch64") int
NOTHROW_RPC(LIBCCALL libc_futexlock_timedwaituntil_cmpxch64)(lfutex_t *ulockaddr,
                                                             lfutex_t *uaddr,
                                                             lfutex_t old_value,
                                                             lfutex_t new_value,
                                                             struct timespec64 *rel_timeout)
/*[[[body:futexlock_timedwaituntil_cmpxch64]]]*/
{
	errno_t result;
	SPIN_WHILE(futex_trywaituntil_cmpxch(uaddr, old_value, new_value) == 0);
	result = (errno_t)sys_lfutexlock(ulockaddr,
	                                 uaddr,
	                                 LFUTEX_WAIT_UNTIL_CMPXCH |
	                                 LFUTEX_WAIT_FLAG_TIMEOUT_RELATIVE,
	                                 (uintptr_t)old_value,
	                                 rel_timeout,
	                                 (uintptr_t)new_value);
	return libc_seterrno_syserr(result);
}
#endif /* MAGIC:alias */
/*[[[end:futexlock_timedwaituntil_cmpxch64]]]*/

/*[[[head:futexlock_timedwaitlock64,hash:0x1bd2a0c3]]]*/
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
ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.futexlock_timedwaitlock64") int
NOTHROW_RPC(LIBCCALL libc_futexlock_timedwaitlock64)(lfutex_t *ulockaddr,
                                                     lfutex_t *uaddr,
                                                     struct timespec64 *rel_timeout)
/*[[[body:futexlock_timedwaitlock64]]]*/
{
	errno_t result;
	SPIN_WHILE(futex_trywaitlock(uaddr) == 0);
	result = (errno_t)sys_lfutexlock(ulockaddr,
	                                 uaddr,
	                                 LFUTEX_WAIT_LOCK |
	                                 LFUTEX_WAIT_FLAG_TIMEOUT_RELATIVE,
	                                 (uintptr_t)0,
	                                 rel_timeout,
	                                 (uintptr_t)0);
	return libc_seterrno_syserr(result);
}
#endif /* MAGIC:alias */
/*[[[end:futexlock_timedwaitlock64]]]*/

/*[[[head:futexlock_timedwaitwhile_exactbits64,hash:0x44b6f372]]]*/
/* Wait if `(*uaddr & bitmask) == setmask'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_futexlock_timedwaitwhile_exactbits64, libc_futexlock_timedwaitwhile_exactbits);
#else
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.futexlock_timedwaitwhile_exactbits64") int
NOTHROW_RPC(LIBCCALL libc_futexlock_timedwaitwhile_exactbits64)(lfutex_t *ulockaddr,
                                                                lfutex_t *uaddr,
                                                                lfutex_t bitmask,
                                                                lfutex_t setmask,
                                                                struct timespec64 *rel_timeout)
/*[[[body:futexlock_timedwaitwhile_exactbits64]]]*/
{
	errno_t result;
	SPIN_WHILE((ATOMIC_READ(*uaddr) & bitmask) == setmask);
	result = (errno_t)sys_lfutexlock(ulockaddr,
	                                 uaddr,
	                                 LFUTEX_WAIT_WHILE_BITMASK |
	                                 LFUTEX_WAIT_FLAG_TIMEOUT_RELATIVE,
	                                 (uintptr_t)bitmask,
	                                 rel_timeout,
	                                 (uintptr_t)setmask);
	return libc_seterrno_syserr(result);
}
#endif /* MAGIC:alias */
/*[[[end:futexlock_timedwaitwhile_exactbits64]]]*/

/*[[[head:futexlock_timedwaituntil_exactbits64,hash:0x118145ff]]]*/
/* Wait if `(*uaddr & bitmask) != setmask'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_futexlock_timedwaituntil_exactbits64, libc_futexlock_timedwaituntil_exactbits);
#else
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.futexlock_timedwaituntil_exactbits64") int
NOTHROW_RPC(LIBCCALL libc_futexlock_timedwaituntil_exactbits64)(lfutex_t *ulockaddr,
                                                                lfutex_t *uaddr,
                                                                lfutex_t bitmask,
                                                                lfutex_t setmask,
                                                                struct timespec64 *rel_timeout)
/*[[[body:futexlock_timedwaituntil_exactbits64]]]*/
{
	errno_t result;
	SPIN_WHILE((ATOMIC_READ(*uaddr) & bitmask) != setmask);
	result = (errno_t)sys_lfutexlock(ulockaddr,
	                                 uaddr,
	                                 LFUTEX_WAIT_UNTIL_BITMASK |
	                                 LFUTEX_WAIT_FLAG_TIMEOUT_RELATIVE,
	                                 (uintptr_t)bitmask,
	                                 rel_timeout,
	                                 (uintptr_t)setmask);
	return libc_seterrno_syserr(result);
}
#endif /* MAGIC:alias */
/*[[[end:futexlock_timedwaituntil_exactbits64]]]*/

/*[[[head:futexlock_timedwaitwhile_anybit64,hash:0x86c5b2ec]]]*/
/* Wait if `(*uaddr & bitmask) != 0'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_futexlock_timedwaitwhile_anybit64, libc_futexlock_timedwaitwhile_anybit);
#else
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.futexlock_timedwaitwhile_anybit64") int
NOTHROW_RPC(LIBCCALL libc_futexlock_timedwaitwhile_anybit64)(lfutex_t *ulockaddr,
                                                             lfutex_t *uaddr,
                                                             lfutex_t bitmask,
                                                             struct timespec64 *rel_timeout)
/*[[[body:futexlock_timedwaitwhile_anybit64]]]*/
{
	errno_t result;
	SPIN_WHILE((ATOMIC_READ(*uaddr) & bitmask) != 0);
	result = (errno_t)sys_lfutexlock(ulockaddr,
	                                 uaddr,
	                                 LFUTEX_WAIT_UNTIL_BITMASK |
	                                 LFUTEX_WAIT_FLAG_TIMEOUT_RELATIVE,
	                                 (uintptr_t)bitmask,
	                                 rel_timeout,
	                                 (uintptr_t)0);
	return libc_seterrno_syserr(result);
}
#endif /* MAGIC:alias */
/*[[[end:futexlock_timedwaitwhile_anybit64]]]*/

/*[[[head:futexlock_timedwaitwhile_allbits64,hash:0x39e29c4f]]]*/
/* Wait if `(*uaddr & bitmask) == bitmask'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_futexlock_timedwaitwhile_allbits64, libc_futexlock_timedwaitwhile_allbits);
#else
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.futexlock_timedwaitwhile_allbits64") int
NOTHROW_RPC(LIBCCALL libc_futexlock_timedwaitwhile_allbits64)(lfutex_t *ulockaddr,
                                                              lfutex_t *uaddr,
                                                              lfutex_t bitmask,
                                                              struct timespec64 *rel_timeout)
/*[[[body:futexlock_timedwaitwhile_allbits64]]]*/
{
	errno_t result;
	SPIN_WHILE((ATOMIC_READ(*uaddr) & bitmask) == bitmask);
	result = (errno_t)sys_lfutexlock(ulockaddr,
	                                 uaddr,
	                                 LFUTEX_WAIT_WHILE_BITMASK |
	                                 LFUTEX_WAIT_FLAG_TIMEOUT_RELATIVE,
	                                 (uintptr_t)bitmask,
	                                 rel_timeout,
	                                 (uintptr_t)bitmask);
	return libc_seterrno_syserr(result);
}
#endif /* MAGIC:alias */
/*[[[end:futexlock_timedwaitwhile_allbits64]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:0xfaf78b50]]]*/
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
