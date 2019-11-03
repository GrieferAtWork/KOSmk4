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
#ifndef GUARD_LIBC_USER_KOS_FUTEX_C
#define GUARD_LIBC_USER_KOS_FUTEX_C 1
#define _KOS_SOURCE 1

#include "../api.h"
#include "kos.futex.h"
#include <kos/syscalls.h>
#include <kos/types.h>
#include <kos/futex.h>
#include <hybrid/atomic.h>
#include <unistd.h>

DECL_BEGIN


/* Disable futex spin support when optimizing for size */
#ifdef __OPTIMIZE_SIZE__
#define NO_FUTEX_SPIN 1
#define SPIN_WHILE(should_wait_if_this_expression_is_true) \
	do {       \
	} __WHILE0
#else /* __OPTIMIZE_SIZE__ */
#undef NO_FUTEX_SPIN
INTERN ATTR_READMOSTLY unsigned int futex_spin_counter = 4;
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

/*[[[head:lfutex,hash:CRC-32=0x4a09b756]]]*/
/* >> lfutex(2)
 * Provide the bottom-most API for implementing user-space synchronization on KOS
 * @param: futex_op: One of:
 *    - LFUTEX_WAKE:               (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAKE, size_t count)
 *    - LFUTEX_NOP:                (lfutex_t *uaddr, syscall_ulong_t LFUTEX_NOP, size_t ignored)
 *    - LFUTEX_WAIT:               (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT, lfutex ignored, struct timespec const *timeout)
 *    - LFUTEX_WAIT_LOCK:          (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_LOCK, lfutex_t lock_value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE:         (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE, lfutex_t value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_UNTIL:         (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_UNTIL, lfutex_t value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_ABOVE:   (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE_ABOVE, lfutex_t value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_BELOW:   (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE_BELOW, lfutex_t value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_BITMASK: (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE_BITMASK, lfutex_t bitmask, struct timespec const *timeout, lfutex_t setmask)
 *    - LFUTEX_WAIT_UNTIL_BITMASK: (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_UNTIL_BITMASK, lfutex_t bitmask, struct timespec const *timeout, lfutex_t setmask)
 *    - LFUTEX_WAIT_WHILE_CMPXCH:  (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE_CMPXCH, lfutex_t oldval, struct timespec const *timeout, lfutex_t newval)
 *    - LFUTEX_WAIT_UNTIL_CMPXCH:  (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_UNTIL_CMPXCH, lfutex_t oldval, struct timespec const *timeout, lfutex_t newval)
 * @param: timeout: Timeout for wait operations (s.a. `LFUTEX_WAIT_FLAG_TIMEOUT_*')
 * @return: * : Depending on `futex_op'
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINVAL:    The given `futex_op' is invalid
 * @return: -1:EINTR:     A blocking futex-wait operation was interrupted
 * @return: -1:ETIMEDOUT: A blocking futex-wait operation has timed out */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.futex.lfutex") ssize_t
NOTHROW_RPC(LIBCCALL libc_lfutex)(lfutex_t *uaddr,
                                  syscall_ulong_t futex_op,
                                  lfutex_t val,
                                  /*struct timespec const *timeout, lfutex_t val2*/...)
/*[[[body:lfutex]]]*/
{
	ssize_t result;
	va_list args;
	struct __timespec32 *timeout;
	lfutex_t val2;
	va_start(args, val);
	timeout = va_arg(args, struct __timespec32 *);
	val2    = va_arg(args, lfutex_t);
	va_end(args);
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
	result = sys_lfutex(uaddr,
	                    futex_op,
	                    val,
	                    (struct timespec64 *)timeout,
	                    val2);
	return libc_seterrno_syserr(result);
#else /* __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */
	if (!timeout || !LFUTEX_USES_TIMEOUT(futex_op)) {
		result = lfutex64(uaddr, futex_op, val,
		                  (struct timespec64 *)NULL, val2);
	} else {
		struct timespec64 tms64;
		tms64.tv_sec  = (time64_t)timeout->tv_sec;
		tms64.tv_nsec = timeout->tv_nsec;
		result = lfutex64(uaddr, futex_op, val, &tms64, val2);
	}
	return result;
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
}
/*[[[end:lfutex]]]*/

/*[[[head:lfutex64,hash:CRC-32=0x6d42f34a]]]*/
/* >> lfutex(2)
 * Provide the bottom-most API for implementing user-space synchronization on KOS
 * @param: futex_op: One of:
 *    - LFUTEX_WAKE:               (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAKE, size_t count)
 *    - LFUTEX_NOP:                (lfutex_t *uaddr, syscall_ulong_t LFUTEX_NOP, size_t ignored)
 *    - LFUTEX_WAIT:               (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT, lfutex ignored, struct timespec const *timeout)
 *    - LFUTEX_WAIT_LOCK:          (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_LOCK, lfutex_t lock_value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE:         (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE, lfutex_t value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_UNTIL:         (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_UNTIL, lfutex_t value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_ABOVE:   (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE_ABOVE, lfutex_t value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_BELOW:   (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE_BELOW, lfutex_t value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_BITMASK: (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE_BITMASK, lfutex_t bitmask, struct timespec const *timeout, lfutex_t setmask)
 *    - LFUTEX_WAIT_UNTIL_BITMASK: (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_UNTIL_BITMASK, lfutex_t bitmask, struct timespec const *timeout, lfutex_t setmask)
 *    - LFUTEX_WAIT_WHILE_CMPXCH:  (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE_CMPXCH, lfutex_t oldval, struct timespec const *timeout, lfutex_t newval)
 *    - LFUTEX_WAIT_UNTIL_CMPXCH:  (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_UNTIL_CMPXCH, lfutex_t oldval, struct timespec const *timeout, lfutex_t newval)
 * @param: timeout: Timeout for wait operations (s.a. `LFUTEX_WAIT_FLAG_TIMEOUT_*')
 * @return: * : Depending on `futex_op'
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINVAL:    The given `futex_op' is invalid
 * @return: -1:EINTR:     A blocking futex-wait operation was interrupted
 * @return: -1:ETIMEDOUT: A blocking futex-wait operation has timed out */
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_lfutex64, libc_lfutex);
#else
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.futex.lfutex64") ssize_t
NOTHROW_RPC(LIBCCALL libc_lfutex64)(lfutex_t *uaddr,
                                    syscall_ulong_t futex_op,
                                    lfutex_t val,
                                    /*struct timespec64 const *timeout, lfutex_t val2*/...)
/*[[[body:lfutex64]]]*/
{
	va_list args;
	struct timespec64 *timeout;
	lfutex_t val2;
	ssize_t result;
	va_start(args, val);
	timeout = va_arg(args, struct timespec64 *);
	val2    = va_arg(args, lfutex_t);
	va_end(args);
	result = sys_lfutex(uaddr,
	                    futex_op,
	                    val,
	                    timeout,
	                    val2);
	return libc_seterrno_syserr(result);
}
#endif /* MAGIC:alias */
/*[[[end:lfutex64]]]*/

/*[[[head:futex_wake,hash:CRC-32=0x9ec6c034]]]*/
/* Wake up to `MAX_WAKE' threads waiting for `*UADDR'
 * @return: * : The number of woken threads
 * @return: -1:EFAULT: A faulty pointer was given */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.futex.futex_wake") ssize_t
NOTHROW_NCX(LIBCCALL libc_futex_wake)(lfutex_t *uaddr,
                                      size_t max_wake)
/*[[[body:futex_wake]]]*/
{
	ssize_t result;
	result = sys_lfutex(uaddr, LFUTEX_WAKE, (uintptr_t)max_wake, NULL, 0);
	return libc_seterrno_syserr(result);
}
/*[[[end:futex_wake]]]*/

/*[[[head:futex_wakeall,hash:CRC-32=0x94371019]]]*/
/* Wake all threads waiting for `*UADDR' (same as `futex_wake(uaddr, (size_t)-1)')
 * @return: * : The number of woken threads
 * @return: -1:EFAULT: A faulty pointer was given */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.futex.futex_wakeall") ssize_t
NOTHROW_NCX(LIBCCALL libc_futex_wakeall)(lfutex_t *uaddr)
/*[[[body:futex_wakeall]]]*/
{
	ssize_t result;
	result = sys_lfutex(uaddr,
	                    LFUTEX_WAKE,
	                    (uintptr_t)(size_t)-1,
	                    NULL,
	                    0);
	return libc_seterrno_syserr(result);
}
/*[[[end:futex_wakeall]]]*/

/*[[[head:futex_waitwhile,hash:CRC-32=0x2dcee111]]]*/
/* Wait if `*uaddr == equal_to_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.futex.futex_waitwhile") int
NOTHROW_RPC(LIBCCALL libc_futex_waitwhile)(lfutex_t *uaddr,
                                           lfutex_t equal_to_value)
/*[[[body:futex_waitwhile]]]*/
{
	errno_t result;
	SPIN_WHILE(ATOMIC_READ(*uaddr) == equal_to_value);
	result = (errno_t)sys_lfutex(uaddr,
	                             LFUTEX_WAIT_WHILE,
	                             (uintptr_t)equal_to_value,
	                             NULL,
	                             0);
	return libc_seterrno_syserr(result);
}
/*[[[end:futex_waitwhile]]]*/

/*[[[head:futex_waituntil,hash:CRC-32=0x8e078cd9]]]*/
/* Wait if `*uaddr != not_equal_to_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.futex.futex_waituntil") int
NOTHROW_RPC(LIBCCALL libc_futex_waituntil)(lfutex_t *uaddr,
                                           lfutex_t not_equal_to_value)
/*[[[body:futex_waituntil]]]*/
{
	errno_t result;
	SPIN_WHILE(ATOMIC_READ(*uaddr) != not_equal_to_value);
	result = (errno_t)sys_lfutex(uaddr,
	                             LFUTEX_WAIT_UNTIL,
	                             (uintptr_t)not_equal_to_value,
	                             NULL,
	                             0);
	return libc_seterrno_syserr(result);
}
/*[[[end:futex_waituntil]]]*/

/*[[[head:futex_waitwhile_above,hash:CRC-32=0x4fcd3ed]]]*/
/* Wait if `*uaddr > above_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.futex.futex_waitwhile_above") int
NOTHROW_RPC(LIBCCALL libc_futex_waitwhile_above)(lfutex_t *uaddr,
                                                 lfutex_t above_value)
/*[[[body:futex_waitwhile_above]]]*/
{
	errno_t result;
	SPIN_WHILE(ATOMIC_READ(*uaddr) > above_value);
	result = (errno_t)sys_lfutex(uaddr,
	                             LFUTEX_WAIT_WHILE_ABOVE,
	                             (uintptr_t)above_value,
	                             NULL,
	                             0);
	return libc_seterrno_syserr(result);
}
/*[[[end:futex_waitwhile_above]]]*/

/*[[[head:futex_waitwhile_below,hash:CRC-32=0x762e48c]]]*/
/* Wait if `*uaddr < below_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.futex.futex_waitwhile_below") int
NOTHROW_RPC(LIBCCALL libc_futex_waitwhile_below)(lfutex_t *uaddr,
                                                 lfutex_t below_value)
/*[[[body:futex_waitwhile_below]]]*/
{
	errno_t result;
	SPIN_WHILE(ATOMIC_READ(*uaddr) < below_value);
	result = (errno_t)sys_lfutex(uaddr,
	                             LFUTEX_WAIT_WHILE_BELOW,
	                             (uintptr_t)below_value,
	                             NULL,
	                             0);
	return libc_seterrno_syserr(result);
}
/*[[[end:futex_waitwhile_below]]]*/

/*[[[head:futex_waitwhile_aboveequal,hash:CRC-32=0xbc8266c4]]]*/
/* Wait if `*uaddr >= above_equal_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.futex.futex_waitwhile_aboveequal") int
NOTHROW_RPC(LIBCCALL libc_futex_waitwhile_aboveequal)(lfutex_t *uaddr,
                                                      lfutex_t above_equal_value)
/*[[[body:futex_waitwhile_aboveequal]]]*/
{
	errno_t result;
	SPIN_WHILE(ATOMIC_READ(*uaddr) >= above_equal_value);
	result = (errno_t)sys_lfutex(uaddr,
	                             likely(above_equal_value != 0)
	                             ? LFUTEX_WAIT_WHILE_ABOVE
	                             : LFUTEX_WAIT,
	                             (uintptr_t)above_equal_value - 1,
	                             NULL,
	                             0);
	return libc_seterrno_syserr(result);
}
/*[[[end:futex_waitwhile_aboveequal]]]*/

/*[[[head:futex_waitwhile_belowequal,hash:CRC-32=0xacbadfa9]]]*/
/* Wait if `*uaddr <= below_equal_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.futex.futex_waitwhile_belowequal") int
NOTHROW_RPC(LIBCCALL libc_futex_waitwhile_belowequal)(lfutex_t *uaddr,
                                                      lfutex_t below_equal_value)
/*[[[body:futex_waitwhile_belowequal]]]*/
{
	errno_t result;
	SPIN_WHILE(ATOMIC_READ(*uaddr) <= below_equal_value);
	result = (errno_t)sys_lfutex(uaddr,
	                             likely(below_equal_value != (lfutex_t)-1)
	                             ? LFUTEX_WAIT_WHILE_BELOW
	                             : LFUTEX_WAIT,
	                             (uintptr_t)below_equal_value + 1,
	                             NULL,
	                             0);
	return libc_seterrno_syserr(result);
}
/*[[[end:futex_waitwhile_belowequal]]]*/

/*[[[head:futex_waitwhile_cmpxch,hash:CRC-32=0x5237a91a]]]*/
/* Wait if `*uaddr == old_value', and set `*uaddr = new_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted (*uaddr was still set to new_value) */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.futex.futex_waitwhile_cmpxch") int
NOTHROW_RPC(LIBCCALL libc_futex_waitwhile_cmpxch)(lfutex_t *uaddr,
                                                  lfutex_t old_value,
                                                  lfutex_t new_value)
/*[[[body:futex_waitwhile_cmpxch]]]*/
{
	errno_t result;
	SPIN_WHILE(ATOMIC_READ(*uaddr) == old_value);
	result = (errno_t)sys_lfutex(uaddr,
	                             LFUTEX_WAIT_WHILE_CMPXCH,
	                             (uintptr_t)old_value,
	                             NULL,
	                             (uintptr_t)new_value);
	return libc_seterrno_syserr(result);
}
/*[[[end:futex_waitwhile_cmpxch]]]*/

/*[[[head:futex_waituntil_cmpxch,hash:CRC-32=0xef61194c]]]*/
/* Wait if `*uaddr != old_value', and set `*uaddr = new_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted (*uaddr was still set to new_value) */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.futex.futex_waituntil_cmpxch") int
NOTHROW_RPC(LIBCCALL libc_futex_waituntil_cmpxch)(lfutex_t *uaddr,
                                                  lfutex_t old_value,
                                                  lfutex_t new_value)
/*[[[body:futex_waituntil_cmpxch]]]*/
{
	errno_t result;
	SPIN_WHILE(futex_trywaituntil_cmpxch(uaddr, old_value, new_value) == 0);
	result = (errno_t)sys_lfutex(uaddr,
	                             LFUTEX_WAIT_UNTIL_CMPXCH,
	                             (uintptr_t)old_value,
	                             NULL,
	                             (uintptr_t)new_value);
	return libc_seterrno_syserr(result);
}
/*[[[end:futex_waituntil_cmpxch]]]*/

/*[[[head:futex_waitlock,hash:CRC-32=0xc4fa7f8d]]]*/
/* Acquire a managed futex lock (s.a. `LFUTEX_WAIT_LOCK')
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted (*uaddr was still set to new_value) */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.futex.futex_waitlock") int
NOTHROW_RPC(LIBCCALL libc_futex_waitlock)(lfutex_t *uaddr)
/*[[[body:futex_waitlock]]]*/
{
	errno_t result;
	SPIN_WHILE(futex_trywaitlock(uaddr) == 0);
	result = (errno_t)sys_lfutex(uaddr,
	                             LFUTEX_WAIT_LOCK,
	                             0,
	                             NULL,
	                             0);
	return libc_seterrno_syserr(result);
}
/*[[[end:futex_waitlock]]]*/

/*[[[head:futex_waitwhile_exactbits,hash:CRC-32=0x5d5d120e]]]*/
/* Wait if `(*uaddr & bitmask) == setmask'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.futex.futex_waitwhile_exactbits") int
NOTHROW_RPC(LIBCCALL libc_futex_waitwhile_exactbits)(lfutex_t *uaddr,
                                                     lfutex_t bitmask,
                                                     lfutex_t setmask)
/*[[[body:futex_waitwhile_exactbits]]]*/
{
	errno_t result;
	SPIN_WHILE((ATOMIC_READ(*uaddr) & bitmask) == setmask);
	result = (errno_t)sys_lfutex(uaddr,
	                             LFUTEX_WAIT_WHILE_BITMASK,
	                             (uintptr_t)bitmask,
	                             NULL,
	                             (uintptr_t)setmask);
	return libc_seterrno_syserr(result);
}
/*[[[end:futex_waitwhile_exactbits]]]*/

/*[[[head:futex_waituntil_exactbits,hash:CRC-32=0x38f04d]]]*/
/* Wait if `(*uaddr & bitmask) != setmask'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.futex.futex_waituntil_exactbits") int
NOTHROW_RPC(LIBCCALL libc_futex_waituntil_exactbits)(lfutex_t *uaddr,
                                                     lfutex_t bitmask,
                                                     lfutex_t setmask)
/*[[[body:futex_waituntil_exactbits]]]*/
{
	errno_t result;
	SPIN_WHILE((ATOMIC_READ(*uaddr) & bitmask) != setmask);
	result = (errno_t)sys_lfutex(uaddr,
	                             LFUTEX_WAIT_UNTIL_BITMASK,
	                             (uintptr_t)bitmask,
	                             NULL,
	                             (uintptr_t)setmask);
	return libc_seterrno_syserr(result);
}
/*[[[end:futex_waituntil_exactbits]]]*/

/*[[[head:futex_waitwhile_anybit,hash:CRC-32=0x17283928]]]*/
/* Wait if `(*uaddr & bitmask) != 0'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.futex.futex_waitwhile_anybit") int
NOTHROW_RPC(LIBCCALL libc_futex_waitwhile_anybit)(lfutex_t *uaddr,
                                                  lfutex_t bitmask)
/*[[[body:futex_waitwhile_anybit]]]*/
{
	errno_t result;
	SPIN_WHILE((ATOMIC_READ(*uaddr) & bitmask) != 0);
	result = (errno_t)sys_lfutex(uaddr,
	                             LFUTEX_WAIT_UNTIL_BITMASK,
	                             (uintptr_t)bitmask,
	                             NULL,
	                             (uintptr_t)0);
	return libc_seterrno_syserr(result);
}
/*[[[end:futex_waitwhile_anybit]]]*/

/*[[[head:futex_waitwhile_allbits,hash:CRC-32=0x211d9e8e]]]*/
/* Wait if `(*uaddr & bitmask) == bitmask'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.futex.futex_waitwhile_allbits") int
NOTHROW_RPC(LIBCCALL libc_futex_waitwhile_allbits)(lfutex_t *uaddr,
                                                   lfutex_t bitmask)
/*[[[body:futex_waitwhile_allbits]]]*/
{
	errno_t result;
	SPIN_WHILE((ATOMIC_READ(*uaddr) & bitmask) == bitmask);
	result = (errno_t)sys_lfutex(uaddr,
	                             LFUTEX_WAIT_WHILE_BITMASK,
	                             (uintptr_t)bitmask,
	                             NULL,
	                             (uintptr_t)bitmask);
	return libc_seterrno_syserr(result);
}
/*[[[end:futex_waitwhile_allbits]]]*/

/*[[[head:futex_timedwaitwhile,hash:CRC-32=0x8d6d9cfe]]]*/
/* Wait if `*uaddr == equal_to_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.futex.futex_timedwaitwhile") int
NOTHROW_RPC(LIBCCALL libc_futex_timedwaitwhile)(lfutex_t *uaddr,
                                                lfutex_t equal_to_value,
                                                struct timespec const *rel_timeout)
/*[[[body:futex_timedwaitwhile]]]*/
{
	struct timespec64 tms64;
	if (!rel_timeout)
		return futex_timedwaitwhile64(uaddr, equal_to_value, NULL);
	tms64.tv_sec  = (time64_t)rel_timeout->tv_sec;
	tms64.tv_nsec = rel_timeout->tv_nsec;
	return futex_timedwaitwhile64(uaddr, equal_to_value, &tms64);
}
/*[[[end:futex_timedwaitwhile]]]*/

/*[[[head:futex_timedwaituntil,hash:CRC-32=0xf2a6a192]]]*/
/* Wait if `*uaddr != not_equal_to_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.futex.futex_timedwaituntil") int
NOTHROW_RPC(LIBCCALL libc_futex_timedwaituntil)(lfutex_t *uaddr,
                                                lfutex_t not_equal_to_value,
                                                struct timespec const *rel_timeout)
/*[[[body:futex_timedwaituntil]]]*/
{
	struct timespec64 tms64;
	if (!rel_timeout)
		return futex_timedwaituntil64(uaddr, not_equal_to_value, NULL);
	tms64.tv_sec  = (time64_t)rel_timeout->tv_sec;
	tms64.tv_nsec = rel_timeout->tv_nsec;
	return futex_timedwaituntil64(uaddr, not_equal_to_value, &tms64);
}
/*[[[end:futex_timedwaituntil]]]*/

/*[[[head:futex_timedwaitwhile_above,hash:CRC-32=0x8bfff3cd]]]*/
/* Wait if `*uaddr > above_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.futex.futex_timedwaitwhile_above") int
NOTHROW_RPC(LIBCCALL libc_futex_timedwaitwhile_above)(lfutex_t *uaddr,
                                                      lfutex_t above_value,
                                                      struct timespec const *rel_timeout)
/*[[[body:futex_timedwaitwhile_above]]]*/
{
	struct timespec64 tms64;
	if (!rel_timeout)
		return futex_timedwaitwhile_above64(uaddr, above_value, NULL);
	tms64.tv_sec  = (time64_t)rel_timeout->tv_sec;
	tms64.tv_nsec = rel_timeout->tv_nsec;
	return futex_timedwaitwhile_above64(uaddr, above_value, &tms64);
}
/*[[[end:futex_timedwaitwhile_above]]]*/

/*[[[head:futex_timedwaitwhile_below,hash:CRC-32=0x3c1e99b2]]]*/
/* Wait if `*uaddr < below_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.futex.futex_timedwaitwhile_below") int
NOTHROW_RPC(LIBCCALL libc_futex_timedwaitwhile_below)(lfutex_t *uaddr,
                                                      lfutex_t below_value,
                                                      struct timespec const *rel_timeout)
/*[[[body:futex_timedwaitwhile_below]]]*/
{
	struct timespec64 tms64;
	if (!rel_timeout)
		return futex_timedwaitwhile_below64(uaddr, below_value, NULL);
	tms64.tv_sec  = (time64_t)rel_timeout->tv_sec;
	tms64.tv_nsec = rel_timeout->tv_nsec;
	return futex_timedwaitwhile_below64(uaddr, below_value, &tms64);
}
/*[[[end:futex_timedwaitwhile_below]]]*/

/*[[[head:futex_timedwaitwhile_aboveequal,hash:CRC-32=0xb29060a4]]]*/
/* Wait if `*uaddr >= above_equal_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.futex.futex_timedwaitwhile_aboveequal") int
NOTHROW_RPC(LIBCCALL libc_futex_timedwaitwhile_aboveequal)(lfutex_t *uaddr,
                                                           lfutex_t above_equal_value,
                                                           struct timespec const *rel_timeout)
/*[[[body:futex_timedwaitwhile_aboveequal]]]*/
{
	struct timespec64 tms64;
	if (!rel_timeout)
		return futex_timedwaitwhile_aboveequal64(uaddr, above_equal_value, NULL);
	tms64.tv_sec  = (time64_t)rel_timeout->tv_sec;
	tms64.tv_nsec = rel_timeout->tv_nsec;
	return futex_timedwaitwhile_aboveequal64(uaddr, above_equal_value, &tms64);
}
/*[[[end:futex_timedwaitwhile_aboveequal]]]*/

/*[[[head:futex_timedwaitwhile_belowequal,hash:CRC-32=0xbf605cb]]]*/
/* Wait if `*uaddr <= below_equal_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.futex.futex_timedwaitwhile_belowequal") int
NOTHROW_RPC(LIBCCALL libc_futex_timedwaitwhile_belowequal)(lfutex_t *uaddr,
                                                           lfutex_t below_equal_value,
                                                           struct timespec const *rel_timeout)
/*[[[body:futex_timedwaitwhile_belowequal]]]*/
{
	struct timespec64 tms64;
	if (!rel_timeout)
		return futex_timedwaitwhile_belowequal64(uaddr, below_equal_value, NULL);
	tms64.tv_sec  = (time64_t)rel_timeout->tv_sec;
	tms64.tv_nsec = rel_timeout->tv_nsec;
	return futex_timedwaitwhile_belowequal64(uaddr, below_equal_value, &tms64);
}
/*[[[end:futex_timedwaitwhile_belowequal]]]*/

/*[[[head:futex_timedwaitwhile_cmpxch,hash:CRC-32=0x638289d7]]]*/
/* Wait if `*uaddr == old_value', and set `*uaddr = new_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted (*uaddr was still set to new_value)
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.futex.futex_timedwaitwhile_cmpxch") int
NOTHROW_RPC(LIBCCALL libc_futex_timedwaitwhile_cmpxch)(lfutex_t *uaddr,
                                                       lfutex_t old_value,
                                                       lfutex_t new_value,
                                                       struct timespec const *rel_timeout)
/*[[[body:futex_timedwaitwhile_cmpxch]]]*/
{
	struct timespec64 tms64;
	if (!rel_timeout)
		return futex_timedwaitwhile_cmpxch64(uaddr, old_value, new_value, NULL);
	tms64.tv_sec  = (time64_t)rel_timeout->tv_sec;
	tms64.tv_nsec = rel_timeout->tv_nsec;
	return futex_timedwaitwhile_cmpxch64(uaddr, old_value, new_value, &tms64);
}
/*[[[end:futex_timedwaitwhile_cmpxch]]]*/

/*[[[head:futex_timedwaituntil_cmpxch,hash:CRC-32=0xe30c6068]]]*/
/* Wait if `*uaddr != old_value', and set `*uaddr = new_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted (*uaddr was still set to new_value)
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.futex.futex_timedwaituntil_cmpxch") int
NOTHROW_RPC(LIBCCALL libc_futex_timedwaituntil_cmpxch)(lfutex_t *uaddr,
                                                       lfutex_t old_value,
                                                       lfutex_t new_value,
                                                       struct timespec const *rel_timeout)
/*[[[body:futex_timedwaituntil_cmpxch]]]*/
{
	struct timespec64 tms64;
	if (!rel_timeout)
		return futex_timedwaituntil_cmpxch64(uaddr, old_value, new_value, NULL);
	tms64.tv_sec  = (time64_t)rel_timeout->tv_sec;
	tms64.tv_nsec = rel_timeout->tv_nsec;
	return futex_timedwaituntil_cmpxch64(uaddr, old_value, new_value, &tms64);
}
/*[[[end:futex_timedwaituntil_cmpxch]]]*/

/*[[[head:futex_timedwaitlock,hash:CRC-32=0x235fc1ee]]]*/
/* Acquire a managed futex lock (s.a. `LFUTEX_WAIT_LOCK')
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted (*uaddr was still set to new_value)
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.futex.futex_timedwaitlock") int
NOTHROW_RPC(LIBCCALL libc_futex_timedwaitlock)(lfutex_t *uaddr,
                                               struct timespec const *rel_timeout)
/*[[[body:futex_timedwaitlock]]]*/
{
	struct timespec64 tms64;
	if (!rel_timeout)
		return futex_timedwaitlock64(uaddr, NULL);
	tms64.tv_sec  = (time64_t)rel_timeout->tv_sec;
	tms64.tv_nsec = rel_timeout->tv_nsec;
	return futex_timedwaitlock64(uaddr, &tms64);
}
/*[[[end:futex_timedwaitlock]]]*/

/*[[[head:futex_timedwaitwhile_exactbits,hash:CRC-32=0xde3a5db5]]]*/
/* Wait if `(*uaddr & bitmask) == setmask'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.futex.futex_timedwaitwhile_exactbits") int
NOTHROW_RPC(LIBCCALL libc_futex_timedwaitwhile_exactbits)(lfutex_t *uaddr,
                                                          lfutex_t bitmask,
                                                          lfutex_t setmask,
                                                          struct timespec const *rel_timeout)
/*[[[body:futex_timedwaitwhile_exactbits]]]*/
{
	struct timespec64 tms64;
	if (!rel_timeout)
		return futex_timedwaitwhile_exactbits64(uaddr, bitmask, setmask, NULL);
	tms64.tv_sec  = (time64_t)rel_timeout->tv_sec;
	tms64.tv_nsec = rel_timeout->tv_nsec;
	return futex_timedwaitwhile_exactbits64(uaddr, bitmask, setmask, &tms64);
}
/*[[[end:futex_timedwaitwhile_exactbits]]]*/

/*[[[head:futex_timedwaituntil_exactbits,hash:CRC-32=0x5f77a749]]]*/
/* Wait if `(*uaddr & bitmask) != setmask'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.futex.futex_timedwaituntil_exactbits") int
NOTHROW_RPC(LIBCCALL libc_futex_timedwaituntil_exactbits)(lfutex_t *uaddr,
                                                          lfutex_t bitmask,
                                                          lfutex_t setmask,
                                                          struct timespec const *rel_timeout)
/*[[[body:futex_timedwaituntil_exactbits]]]*/
{
	struct timespec64 tms64;
	if (!rel_timeout)
		return futex_timedwaituntil_exactbits64(uaddr, bitmask, setmask, NULL);
	tms64.tv_sec  = (time64_t)rel_timeout->tv_sec;
	tms64.tv_nsec = rel_timeout->tv_nsec;
	return futex_timedwaituntil_exactbits64(uaddr, bitmask, setmask, &tms64);
}
/*[[[end:futex_timedwaituntil_exactbits]]]*/

/*[[[head:futex_timedwaitwhile_anybit,hash:CRC-32=0x9a072a7e]]]*/
/* Wait if `(*uaddr & bitmask) != 0'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.futex.futex_timedwaitwhile_anybit") int
NOTHROW_RPC(LIBCCALL libc_futex_timedwaitwhile_anybit)(lfutex_t *uaddr,
                                                       lfutex_t bitmask,
                                                       struct timespec const *rel_timeout)
/*[[[body:futex_timedwaitwhile_anybit]]]*/
{
	struct timespec64 tms64;
	if (!rel_timeout)
		return futex_timedwaitwhile_anybit64(uaddr, bitmask, NULL);
	tms64.tv_sec  = (time64_t)rel_timeout->tv_sec;
	tms64.tv_nsec = rel_timeout->tv_nsec;
	return futex_timedwaitwhile_anybit64(uaddr, bitmask, &tms64);
}
/*[[[end:futex_timedwaitwhile_anybit]]]*/

/*[[[head:futex_timedwaitwhile_allbits,hash:CRC-32=0x2be43701]]]*/
/* Wait if `(*uaddr & bitmask) == bitmask'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.futex.futex_timedwaitwhile_allbits") int
NOTHROW_RPC(LIBCCALL libc_futex_timedwaitwhile_allbits)(lfutex_t *uaddr,
                                                        lfutex_t bitmask,
                                                        struct timespec const *rel_timeout)
/*[[[body:futex_timedwaitwhile_allbits]]]*/
{
	struct timespec64 tms64;
	if (!rel_timeout)
		return futex_timedwaitwhile_allbits64(uaddr, bitmask, NULL);
	tms64.tv_sec  = (time64_t)rel_timeout->tv_sec;
	tms64.tv_nsec = rel_timeout->tv_nsec;
	return futex_timedwaitwhile_allbits64(uaddr, bitmask, &tms64);
}
/*[[[end:futex_timedwaitwhile_allbits]]]*/

/*[[[head:futex_timedwaitwhile64,hash:CRC-32=0x2840a225]]]*/
/* Wait if `*uaddr == equal_to_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_futex_timedwaitwhile64, libc_futex_timedwaitwhile);
#else
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.futex.futex_timedwaitwhile64") int
NOTHROW_RPC(LIBCCALL libc_futex_timedwaitwhile64)(lfutex_t *uaddr,
                                                  lfutex_t equal_to_value,
                                                  struct timespec64 const *rel_timeout)
/*[[[body:futex_timedwaitwhile64]]]*/
{
	errno_t result;
	SPIN_WHILE(ATOMIC_READ(*uaddr) == equal_to_value);
	result = (errno_t)sys_lfutex(uaddr,
	                             LFUTEX_WAIT_WHILE |
	                             LFUTEX_WAIT_FLAG_TIMEOUT_RELATIVE,
	                             (uintptr_t)equal_to_value,
	                             rel_timeout,
	                             (uintptr_t)0);
	return libc_seterrno_syserr(result);
}
#endif /* MAGIC:alias */
/*[[[end:futex_timedwaitwhile64]]]*/

/*[[[head:futex_timedwaituntil64,hash:CRC-32=0xc3e5aa93]]]*/
/* Wait if `*uaddr != not_equal_to_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_futex_timedwaituntil64, libc_futex_timedwaituntil);
#else
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.futex.futex_timedwaituntil64") int
NOTHROW_RPC(LIBCCALL libc_futex_timedwaituntil64)(lfutex_t *uaddr,
                                                  lfutex_t not_equal_to_value,
                                                  struct timespec64 const *rel_timeout)
/*[[[body:futex_timedwaituntil64]]]*/
{
	errno_t result;
	SPIN_WHILE(ATOMIC_READ(*uaddr) != not_equal_to_value);
	result = (errno_t)sys_lfutex(uaddr,
	                             LFUTEX_WAIT_UNTIL |
	                             LFUTEX_WAIT_FLAG_TIMEOUT_RELATIVE,
	                             (uintptr_t)not_equal_to_value,
	                             rel_timeout,
	                             (uintptr_t)0);
	return libc_seterrno_syserr(result);
}
#endif /* MAGIC:alias */
/*[[[end:futex_timedwaituntil64]]]*/

/*[[[head:futex_timedwaitwhile_above64,hash:CRC-32=0x1ad3f376]]]*/
/* Wait if `*uaddr > above_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_futex_timedwaitwhile_above64, libc_futex_timedwaitwhile_above);
#else
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.futex.futex_timedwaitwhile_above64") int
NOTHROW_RPC(LIBCCALL libc_futex_timedwaitwhile_above64)(lfutex_t *uaddr,
                                                        lfutex_t above_value,
                                                        struct timespec64 const *rel_timeout)
/*[[[body:futex_timedwaitwhile_above64]]]*/
{
	errno_t result;
	SPIN_WHILE(ATOMIC_READ(*uaddr) > above_value);
	result = (errno_t)sys_lfutex(uaddr,
	                             LFUTEX_WAIT_WHILE_ABOVE |
	                             LFUTEX_WAIT_FLAG_TIMEOUT_RELATIVE,
	                             (uintptr_t)above_value,
	                             rel_timeout,
	                             (uintptr_t)0);
	return libc_seterrno_syserr(result);
}
#endif /* MAGIC:alias */
/*[[[end:futex_timedwaitwhile_above64]]]*/

/*[[[head:futex_timedwaitwhile_below64,hash:CRC-32=0xa909603]]]*/
/* Wait if `*uaddr < below_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_futex_timedwaitwhile_below64, libc_futex_timedwaitwhile_below);
#else
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.futex.futex_timedwaitwhile_below64") int
NOTHROW_RPC(LIBCCALL libc_futex_timedwaitwhile_below64)(lfutex_t *uaddr,
                                                        lfutex_t below_value,
                                                        struct timespec64 const *rel_timeout)
/*[[[body:futex_timedwaitwhile_below64]]]*/
{
	errno_t result;
	SPIN_WHILE(ATOMIC_READ(*uaddr) < below_value);
	result = (errno_t)sys_lfutex(uaddr,
	                             LFUTEX_WAIT_WHILE_BELOW |
	                             LFUTEX_WAIT_FLAG_TIMEOUT_RELATIVE,
	                             (uintptr_t)below_value,
	                             rel_timeout,
	                             (uintptr_t)0);
	return libc_seterrno_syserr(result);
}
#endif /* MAGIC:alias */
/*[[[end:futex_timedwaitwhile_below64]]]*/

/*[[[head:futex_timedwaitwhile_aboveequal64,hash:CRC-32=0x548e14da]]]*/
/* Wait if `*uaddr >= above_equal_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_futex_timedwaitwhile_aboveequal64, libc_futex_timedwaitwhile_aboveequal);
#else
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.futex.futex_timedwaitwhile_aboveequal64") int
NOTHROW_RPC(LIBCCALL libc_futex_timedwaitwhile_aboveequal64)(lfutex_t *uaddr,
                                                             lfutex_t above_equal_value,
                                                             struct timespec64 const *rel_timeout)
/*[[[body:futex_timedwaitwhile_aboveequal64]]]*/
{
	errno_t result;
	SPIN_WHILE(ATOMIC_READ(*uaddr) >= above_equal_value);
	result = (errno_t)sys_lfutex(uaddr,
	                             likely(above_equal_value != 0)
	                             ? LFUTEX_WAIT_WHILE_ABOVE | LFUTEX_WAIT_FLAG_TIMEOUT_RELATIVE
	                             : LFUTEX_WAIT | LFUTEX_WAIT_FLAG_TIMEOUT_RELATIVE,
	                             (uintptr_t)above_equal_value - 1,
	                             rel_timeout,
	                             (uintptr_t)0);
	return libc_seterrno_syserr(result);
}
#endif /* MAGIC:alias */
/*[[[end:futex_timedwaitwhile_aboveequal64]]]*/

/*[[[head:futex_timedwaitwhile_belowequal64,hash:CRC-32=0xe1e373cc]]]*/
/* Wait if `*uaddr <= below_equal_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_futex_timedwaitwhile_belowequal64, libc_futex_timedwaitwhile_belowequal);
#else
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.futex.futex_timedwaitwhile_belowequal64") int
NOTHROW_RPC(LIBCCALL libc_futex_timedwaitwhile_belowequal64)(lfutex_t *uaddr,
                                                             lfutex_t below_equal_value,
                                                             struct timespec64 const *rel_timeout)
/*[[[body:futex_timedwaitwhile_belowequal64]]]*/
{
	errno_t result;
	SPIN_WHILE(ATOMIC_READ(*uaddr) <= below_equal_value);
	result = (errno_t)sys_lfutex(uaddr,
	                             likely(below_equal_value != (lfutex_t)-1)
	                             ? LFUTEX_WAIT_WHILE_BELOW | LFUTEX_WAIT_FLAG_TIMEOUT_RELATIVE
	                             : LFUTEX_WAIT | LFUTEX_WAIT_FLAG_TIMEOUT_RELATIVE,
	                             (uintptr_t)below_equal_value + 1,
	                             rel_timeout,
	                             (uintptr_t)0);
	return libc_seterrno_syserr(result);
}
#endif /* MAGIC:alias */
/*[[[end:futex_timedwaitwhile_belowequal64]]]*/

/*[[[head:futex_timedwaitwhile_cmpxch64,hash:CRC-32=0x7f3ff5fb]]]*/
/* Wait if `*uaddr == old_value', and set `*uaddr = new_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted (*uaddr was still set to new_value)
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_futex_timedwaitwhile_cmpxch64, libc_futex_timedwaitwhile_cmpxch);
#else
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.futex.futex_timedwaitwhile_cmpxch64") int
NOTHROW_RPC(LIBCCALL libc_futex_timedwaitwhile_cmpxch64)(lfutex_t *uaddr,
                                                         lfutex_t old_value,
                                                         lfutex_t new_value,
                                                         struct timespec64 const *rel_timeout)
/*[[[body:futex_timedwaitwhile_cmpxch64]]]*/
{
	errno_t result;
	SPIN_WHILE(ATOMIC_READ(*uaddr) != old_value);
	result = (errno_t)sys_lfutex(uaddr,
	                             LFUTEX_WAIT_WHILE_CMPXCH |
	                             LFUTEX_WAIT_FLAG_TIMEOUT_RELATIVE,
	                             (uintptr_t)old_value,
	                             rel_timeout,
	                             (uintptr_t)new_value);
	return libc_seterrno_syserr(result);
}
#endif /* MAGIC:alias */
/*[[[end:futex_timedwaitwhile_cmpxch64]]]*/

/*[[[head:futex_timedwaituntil_cmpxch64,hash:CRC-32=0xfbe42e9f]]]*/
/* Wait if `*uaddr != old_value', and set `*uaddr = new_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted (*uaddr was still set to new_value)
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_futex_timedwaituntil_cmpxch64, libc_futex_timedwaituntil_cmpxch);
#else
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.futex.futex_timedwaituntil_cmpxch64") int
NOTHROW_RPC(LIBCCALL libc_futex_timedwaituntil_cmpxch64)(lfutex_t *uaddr,
                                                         lfutex_t old_value,
                                                         lfutex_t new_value,
                                                         struct timespec64 const *rel_timeout)
/*[[[body:futex_timedwaituntil_cmpxch64]]]*/
{
	errno_t result;
	SPIN_WHILE(futex_trywaituntil_cmpxch(uaddr, old_value, new_value) == 0);
	result = (errno_t)sys_lfutex(uaddr,
	                             LFUTEX_WAIT_UNTIL_CMPXCH |
	                             LFUTEX_WAIT_FLAG_TIMEOUT_RELATIVE,
	                             (uintptr_t)old_value,
	                             rel_timeout,
	                             (uintptr_t)new_value);
	return libc_seterrno_syserr(result);
}
#endif /* MAGIC:alias */
/*[[[end:futex_timedwaituntil_cmpxch64]]]*/

/*[[[head:futex_timedwaitlock64,hash:CRC-32=0x8dab44cc]]]*/
/* Acquire a managed futex lock (s.a. `LFUTEX_WAIT_LOCK')
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted (*uaddr was still set to new_value)
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_futex_timedwaitlock64, libc_futex_timedwaitlock);
#else
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.futex.futex_timedwaitlock64") int
NOTHROW_RPC(LIBCCALL libc_futex_timedwaitlock64)(lfutex_t *uaddr,
                                                 struct timespec64 const *rel_timeout)
/*[[[body:futex_timedwaitlock64]]]*/
{
	errno_t result;
	SPIN_WHILE(futex_trywaitlock(uaddr) == 0);
	result = (errno_t)sys_lfutex(uaddr,
	                             LFUTEX_WAIT_LOCK |
	                             LFUTEX_WAIT_FLAG_TIMEOUT_RELATIVE,
	                             (uintptr_t)0,
	                             rel_timeout,
	                             (uintptr_t)0);
	return libc_seterrno_syserr(result);
}
#endif /* MAGIC:alias */
/*[[[end:futex_timedwaitlock64]]]*/

/*[[[head:futex_timedwaitwhile_exactbits64,hash:CRC-32=0xab513d67]]]*/
/* Wait if `(*uaddr & bitmask) == setmask'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_futex_timedwaitwhile_exactbits64, libc_futex_timedwaitwhile_exactbits);
#else
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.futex.futex_timedwaitwhile_exactbits64") int
NOTHROW_RPC(LIBCCALL libc_futex_timedwaitwhile_exactbits64)(lfutex_t *uaddr,
                                                            lfutex_t bitmask,
                                                            lfutex_t setmask,
                                                            struct timespec64 const *rel_timeout)
/*[[[body:futex_timedwaitwhile_exactbits64]]]*/
{
	errno_t result;
	SPIN_WHILE((ATOMIC_READ(*uaddr) & bitmask) == setmask);
	result = (errno_t)sys_lfutex(uaddr,
	                             LFUTEX_WAIT_WHILE_BITMASK |
	                             LFUTEX_WAIT_FLAG_TIMEOUT_RELATIVE,
	                             (uintptr_t)bitmask,
	                             rel_timeout,
	                             (uintptr_t)setmask);
	return libc_seterrno_syserr(result);
}
#endif /* MAGIC:alias */
/*[[[end:futex_timedwaitwhile_exactbits64]]]*/

/*[[[head:futex_timedwaituntil_exactbits64,hash:CRC-32=0xccea58f1]]]*/
/* Wait if `(*uaddr & bitmask) != setmask'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_futex_timedwaituntil_exactbits64, libc_futex_timedwaituntil_exactbits);
#else
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.futex.futex_timedwaituntil_exactbits64") int
NOTHROW_RPC(LIBCCALL libc_futex_timedwaituntil_exactbits64)(lfutex_t *uaddr,
                                                            lfutex_t bitmask,
                                                            lfutex_t setmask,
                                                            struct timespec64 const *rel_timeout)
/*[[[body:futex_timedwaituntil_exactbits64]]]*/
{
	errno_t result;
	SPIN_WHILE((ATOMIC_READ(*uaddr) & bitmask) != setmask);
	result = (errno_t)sys_lfutex(uaddr,
	                             LFUTEX_WAIT_UNTIL_BITMASK |
	                             LFUTEX_WAIT_FLAG_TIMEOUT_RELATIVE,
	                             (uintptr_t)bitmask,
	                             rel_timeout,
	                             (uintptr_t)setmask);
	return libc_seterrno_syserr(result);
}
#endif /* MAGIC:alias */
/*[[[end:futex_timedwaituntil_exactbits64]]]*/

/*[[[head:futex_timedwaitwhile_anybit64,hash:CRC-32=0x6db613d6]]]*/
/* Wait if `(*uaddr & bitmask) != 0'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_futex_timedwaitwhile_anybit64, libc_futex_timedwaitwhile_anybit);
#else
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.futex.futex_timedwaitwhile_anybit64") int
NOTHROW_RPC(LIBCCALL libc_futex_timedwaitwhile_anybit64)(lfutex_t *uaddr,
                                                         lfutex_t bitmask,
                                                         struct timespec64 const *rel_timeout)
/*[[[body:futex_timedwaitwhile_anybit64]]]*/
{
	errno_t result;
	SPIN_WHILE((ATOMIC_READ(*uaddr) & bitmask) != 0);
	result = (errno_t)sys_lfutex(uaddr,
	                             LFUTEX_WAIT_UNTIL_BITMASK |
	                             LFUTEX_WAIT_FLAG_TIMEOUT_RELATIVE,
	                             (uintptr_t)bitmask,
	                             rel_timeout,
	                             (uintptr_t)0);
	return libc_seterrno_syserr(result);
}
#endif /* MAGIC:alias */
/*[[[end:futex_timedwaitwhile_anybit64]]]*/

/*[[[head:futex_timedwaitwhile_allbits64,hash:CRC-32=0x638557f2]]]*/
/* Wait if `(*uaddr & bitmask) == bitmask'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_futex_timedwaitwhile_allbits64, libc_futex_timedwaitwhile_allbits);
#else
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.futex.futex_timedwaitwhile_allbits64") int
NOTHROW_RPC(LIBCCALL libc_futex_timedwaitwhile_allbits64)(lfutex_t *uaddr,
                                                          lfutex_t bitmask,
                                                          struct timespec64 const *rel_timeout)
/*[[[body:futex_timedwaitwhile_allbits64]]]*/
{
	errno_t result;
	SPIN_WHILE((ATOMIC_READ(*uaddr) & bitmask) == bitmask);
	result = (errno_t)sys_lfutex(uaddr,
	                             LFUTEX_WAIT_WHILE_BITMASK |
	                             LFUTEX_WAIT_FLAG_TIMEOUT_RELATIVE,
	                             (uintptr_t)bitmask,
	                             rel_timeout,
	                             (uintptr_t)bitmask);
	return libc_seterrno_syserr(result);
}
#endif /* MAGIC:alias */
/*[[[end:futex_timedwaitwhile_allbits64]]]*/

/*[[[head:futex_getspin,hash:CRC-32=0x1e14afb3]]]*/
/* Get/Set the number of times to spin the following futex operations without
 * entering kernel-space, setting waiter-bits, and entering sleep mode:
 *   - LFUTEX_WAIT_WHILE: SPIN({ if (*uaddr != val) DONE(); });
 *   - LFUTEX_WAIT_UNTIL: SPIN({ if (*uaddr == val) DONE(); });
 *   - ...
 * Futex spinning improves performance by bypassing expensive blocking operations
 * when associated locks are often only held for a couple of moments at a time.
 * Take for example `lfutex(LFUTEX_WAIT_WHILE)' (or preferrably `futex_waitwhile()'), which
 * is wrapped like this:
 * >> unsigned int spins;
 * >> spins = futex_getspin();
 * >> while (spins--) {
 * >> 	if (*uaddr != val)
 * >> 		return 0;
 * >> 	if (sched_yield())
 * >> 		break; // If there was nothing to switch to, sched_yield() returns non-zero
 * >> }
 * >> return lfutex(uaddr, LFUTEX_WAIT_WHILE, val, (struct timespec const *)NULL);
 * Upon startup, `futex_getspin()' is pre-initialized to `4'.
 * @return: * : The current (get) / old (set) spin value */
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.sched.futex.futex_getspin") unsigned int
NOTHROW(LIBCCALL libc_futex_getspin)(void)
/*[[[body:futex_getspin]]]*/
{
#ifdef NO_FUTEX_SPIN
	return 0;
#else
	return ATOMIC_READ(futex_spin_counter);
#endif
}
/*[[[end:futex_getspin]]]*/

/*[[[head:futex_setspin,hash:CRC-32=0xeaeda144]]]*/
/* Get/Set the number of times to spin the following futex operations without
 * entering kernel-space, setting waiter-bits, and entering sleep mode:
 *   - LFUTEX_WAIT_WHILE: SPIN({ if (*uaddr != val) DONE(); });
 *   - LFUTEX_WAIT_UNTIL: SPIN({ if (*uaddr == val) DONE(); });
 *   - ...
 * Futex spinning improves performance by bypassing expensive blocking operations
 * when associated locks are often only held for a couple of moments at a time.
 * Take for example `lfutex(LFUTEX_WAIT_WHILE)' (or preferrably `futex_waitwhile()'), which
 * is wrapped like this:
 * >> unsigned int spins;
 * >> spins = futex_getspin();
 * >> while (spins--) {
 * >> 	if (*uaddr != val)
 * >> 		return 0;
 * >> 	if (sched_yield())
 * >> 		break; // If there was nothing to switch to, sched_yield() returns non-zero
 * >> }
 * >> return lfutex(uaddr, LFUTEX_WAIT_WHILE, val, (struct timespec const *)NULL);
 * Upon startup, `futex_getspin()' is pre-initialized to `4'.
 * @return: * : The current (get) / old (set) spin value */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.sched.futex.futex_setspin") unsigned int
NOTHROW(LIBCCALL libc_futex_setspin)(unsigned int new_spin)
/*[[[body:futex_setspin]]]*/
{
#ifdef NO_FUTEX_SPIN
	(void)new_spin;
	return 0;
#else
	return ATOMIC_XCH(futex_spin_counter, new_spin);
#endif
}
/*[[[end:futex_setspin]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:CRC-32=0xcbb0bbf3]]]*/
DEFINE_PUBLIC_WEAK_ALIAS(lfutex, libc_lfutex);
DEFINE_PUBLIC_WEAK_ALIAS(lfutex64, libc_lfutex64);
DEFINE_PUBLIC_WEAK_ALIAS(futex_wake, libc_futex_wake);
DEFINE_PUBLIC_WEAK_ALIAS(futex_wakeall, libc_futex_wakeall);
DEFINE_PUBLIC_WEAK_ALIAS(futex_waitwhile, libc_futex_waitwhile);
DEFINE_PUBLIC_WEAK_ALIAS(futex_waituntil, libc_futex_waituntil);
DEFINE_PUBLIC_WEAK_ALIAS(futex_waitwhile_above, libc_futex_waitwhile_above);
DEFINE_PUBLIC_WEAK_ALIAS(futex_waitwhile_below, libc_futex_waitwhile_below);
DEFINE_PUBLIC_WEAK_ALIAS(futex_waitwhile_aboveequal, libc_futex_waitwhile_aboveequal);
DEFINE_PUBLIC_WEAK_ALIAS(futex_waitwhile_belowequal, libc_futex_waitwhile_belowequal);
DEFINE_PUBLIC_WEAK_ALIAS(futex_waitwhile_cmpxch, libc_futex_waitwhile_cmpxch);
DEFINE_PUBLIC_WEAK_ALIAS(futex_waituntil_cmpxch, libc_futex_waituntil_cmpxch);
DEFINE_PUBLIC_WEAK_ALIAS(futex_waitlock, libc_futex_waitlock);
DEFINE_PUBLIC_WEAK_ALIAS(futex_waitwhile_exactbits, libc_futex_waitwhile_exactbits);
DEFINE_PUBLIC_WEAK_ALIAS(futex_waituntil_exactbits, libc_futex_waituntil_exactbits);
DEFINE_PUBLIC_WEAK_ALIAS(futex_waitwhile_anybit, libc_futex_waitwhile_anybit);
DEFINE_PUBLIC_WEAK_ALIAS(futex_waitwhile_allbits, libc_futex_waitwhile_allbits);
DEFINE_PUBLIC_WEAK_ALIAS(futex_timedwaitwhile, libc_futex_timedwaitwhile);
DEFINE_PUBLIC_WEAK_ALIAS(futex_timedwaituntil, libc_futex_timedwaituntil);
DEFINE_PUBLIC_WEAK_ALIAS(futex_timedwaitwhile_above, libc_futex_timedwaitwhile_above);
DEFINE_PUBLIC_WEAK_ALIAS(futex_timedwaitwhile_below, libc_futex_timedwaitwhile_below);
DEFINE_PUBLIC_WEAK_ALIAS(futex_timedwaitwhile_aboveequal, libc_futex_timedwaitwhile_aboveequal);
DEFINE_PUBLIC_WEAK_ALIAS(futex_timedwaitwhile_belowequal, libc_futex_timedwaitwhile_belowequal);
DEFINE_PUBLIC_WEAK_ALIAS(futex_timedwaitwhile_cmpxch, libc_futex_timedwaitwhile_cmpxch);
DEFINE_PUBLIC_WEAK_ALIAS(futex_timedwaituntil_cmpxch, libc_futex_timedwaituntil_cmpxch);
DEFINE_PUBLIC_WEAK_ALIAS(futex_timedwaitlock, libc_futex_timedwaitlock);
DEFINE_PUBLIC_WEAK_ALIAS(futex_timedwaitwhile_exactbits, libc_futex_timedwaitwhile_exactbits);
DEFINE_PUBLIC_WEAK_ALIAS(futex_timedwaituntil_exactbits, libc_futex_timedwaituntil_exactbits);
DEFINE_PUBLIC_WEAK_ALIAS(futex_timedwaitwhile_anybit, libc_futex_timedwaitwhile_anybit);
DEFINE_PUBLIC_WEAK_ALIAS(futex_timedwaitwhile_allbits, libc_futex_timedwaitwhile_allbits);
DEFINE_PUBLIC_WEAK_ALIAS(futex_timedwaitwhile64, libc_futex_timedwaitwhile64);
DEFINE_PUBLIC_WEAK_ALIAS(futex_timedwaituntil64, libc_futex_timedwaituntil64);
DEFINE_PUBLIC_WEAK_ALIAS(futex_timedwaitwhile_above64, libc_futex_timedwaitwhile_above64);
DEFINE_PUBLIC_WEAK_ALIAS(futex_timedwaitwhile_below64, libc_futex_timedwaitwhile_below64);
DEFINE_PUBLIC_WEAK_ALIAS(futex_timedwaitwhile_aboveequal64, libc_futex_timedwaitwhile_aboveequal64);
DEFINE_PUBLIC_WEAK_ALIAS(futex_timedwaitwhile_belowequal64, libc_futex_timedwaitwhile_belowequal64);
DEFINE_PUBLIC_WEAK_ALIAS(futex_timedwaitwhile_cmpxch64, libc_futex_timedwaitwhile_cmpxch64);
DEFINE_PUBLIC_WEAK_ALIAS(futex_timedwaituntil_cmpxch64, libc_futex_timedwaituntil_cmpxch64);
DEFINE_PUBLIC_WEAK_ALIAS(futex_timedwaitlock64, libc_futex_timedwaitlock64);
DEFINE_PUBLIC_WEAK_ALIAS(futex_timedwaitwhile_exactbits64, libc_futex_timedwaitwhile_exactbits64);
DEFINE_PUBLIC_WEAK_ALIAS(futex_timedwaituntil_exactbits64, libc_futex_timedwaituntil_exactbits64);
DEFINE_PUBLIC_WEAK_ALIAS(futex_timedwaitwhile_anybit64, libc_futex_timedwaitwhile_anybit64);
DEFINE_PUBLIC_WEAK_ALIAS(futex_timedwaitwhile_allbits64, libc_futex_timedwaitwhile_allbits64);
DEFINE_PUBLIC_WEAK_ALIAS(futex_getspin, libc_futex_getspin);
DEFINE_PUBLIC_WEAK_ALIAS(futex_setspin, libc_futex_setspin);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_KOS_FUTEX_C */
