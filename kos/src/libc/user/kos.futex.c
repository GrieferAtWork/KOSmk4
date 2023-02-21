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
#ifndef GUARD_LIBC_USER_KOS_FUTEX_C
#define GUARD_LIBC_USER_KOS_FUTEX_C 1
#define _KOS_SOURCE 1

#include "../api.h"
/**/

#include <kos/futex.h>
#include <kos/syscalls.h>
#include <kos/types.h>

#include <assert.h>
#include <atomic.h>
#include <unistd.h>

#include "kos.futex.h"

DECL_BEGIN


/* Disable futex spin support when optimizing for size */
#ifdef __OPTIMIZE_SIZE__
#define NO_FUTEX_SPIN 1
#define SPIN_WHILE(should_wait_if_this_expression_is_true) \
	(void)0
#else /* __OPTIMIZE_SIZE__ */
#undef NO_FUTEX_SPIN
INTERN ATTR_READMOSTLY unsigned int futex_spin_counter = 4;
#define SPIN_WHILE(should_wait_if_this_expression_is_true) \
	do {                                                   \
		unsigned int _count;                               \
		_count = atomic_read(&futex_spin_counter);          \
		for (;;) {                                         \
			if (!(should_wait_if_this_expression_is_true)) \
				return 1; /* Didn't wait... */             \
			if (!_count)                                   \
				break;                                     \
			if (sys_sched_yield() != -EOK)                 \
				break;                                     \
			--_count;                                      \
		}                                                  \
	}	__WHILE0
#endif /* !__OPTIMIZE_SIZE__ */






/*[[[head:libc_lfutex,hash:CRC-32=0xc38ce4d6]]]*/
/* >> lfutex(2)
 * Provide the bottom-most API for implementing user-space synchronization on KOS
 * @param: futex_op: One of:
 *    - LFUTEX_WAKE:                (lfutex_t *uaddr, LFUTEX_WAKE, size_t count)
 *    - LFUTEX_WAKEMASK:            (lfutex_t *uaddr, LFUTEX_WAKEMASK, size_t count, lfutex_t mask_and, lfutex_t mask_or)
 *    - LFUTEX_WAIT_WHILE:          (lfutex_t *uaddr, LFUTEX_WAIT_WHILE, lfutex_t value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_UNTIL:          (lfutex_t *uaddr, LFUTEX_WAIT_UNTIL, lfutex_t value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_ABOVE:    (lfutex_t *uaddr, LFUTEX_WAIT_WHILE_ABOVE, lfutex_t value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_BELOW:    (lfutex_t *uaddr, LFUTEX_WAIT_WHILE_BELOW, lfutex_t value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_BITMASK:  (lfutex_t *uaddr, LFUTEX_WAIT_WHILE_BITMASK, lfutex_t bitmask, struct timespec const *timeout, lfutex_t setmask)
 *    - LFUTEX_WAIT_UNTIL_BITMASK:  (lfutex_t *uaddr, LFUTEX_WAIT_UNTIL_BITMASK, lfutex_t bitmask, struct timespec const *timeout, lfutex_t setmask)
 *    - LFUTEX_WAIT_WHILE_EX:       (lfutex_t *uaddr, LFUTEX_WAIT_WHILE_EX, void const *rhs, struct timespec const *timeout, size_t num_bytes)
 *    - LFUTEX_WAIT_UNTIL_EX:       (lfutex_t *uaddr, LFUTEX_WAIT_UNTIL_EX, void const *rhs, struct timespec const *timeout, size_t num_bytes)
 *    - LFUTEX_WAIT_WHILE_ABOVE_EX: (lfutex_t *uaddr, LFUTEX_WAIT_WHILE_ABOVE_EX, void const *rhs, struct timespec const *timeout, size_t num_bytes)
 *    - LFUTEX_WAIT_WHILE_BELOW_EX: (lfutex_t *uaddr, LFUTEX_WAIT_WHILE_BELOW_EX, void const *rhs, struct timespec const *timeout, size_t num_bytes)
 * @param: timeout: Timeout for wait operations (s.a. `LFUTEX_WAIT_FLAG_TIMEOUT_*')
 * @return: * : Depending on `futex_op'
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINVAL:    The given `futex_op' is invalid
 * @return: -1:EINTR:     A blocking futex-wait operation was interrupted
 * @return: -1:ETIMEDOUT: A blocking futex-wait operation has timed out */
INTERN ATTR_SECTION(".text.crt.sched.futex") NONNULL((1)) ssize_t
NOTHROW_RPC(VLIBCCALL libc_lfutex)(lfutex_t *uaddr,
                                   syscall_ulong_t futex_op,
                                   lfutex_t val,
                                   ...)
/*[[[body:libc_lfutex]]]*/
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
/*[[[end:libc_lfutex]]]*/


/*[[[head:libc_lfutex64,hash:CRC-32=0x41fe89b]]]*/
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_lfutex64, libc_lfutex);
#else /* MAGIC:alias */
/* >> lfutex(2)
 * Provide the bottom-most API for implementing user-space synchronization on KOS
 * @param: futex_op: One of:
 *    - LFUTEX_WAKE:                (lfutex_t *uaddr, LFUTEX_WAKE, size_t count)
 *    - LFUTEX_WAKEMASK:            (lfutex_t *uaddr, LFUTEX_WAKEMASK, size_t count, lfutex_t mask_and, lfutex_t mask_or)
 *    - LFUTEX_WAIT_WHILE:          (lfutex_t *uaddr, LFUTEX_WAIT_WHILE, lfutex_t value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_UNTIL:          (lfutex_t *uaddr, LFUTEX_WAIT_UNTIL, lfutex_t value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_ABOVE:    (lfutex_t *uaddr, LFUTEX_WAIT_WHILE_ABOVE, lfutex_t value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_BELOW:    (lfutex_t *uaddr, LFUTEX_WAIT_WHILE_BELOW, lfutex_t value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_BITMASK:  (lfutex_t *uaddr, LFUTEX_WAIT_WHILE_BITMASK, lfutex_t bitmask, struct timespec const *timeout, lfutex_t setmask)
 *    - LFUTEX_WAIT_UNTIL_BITMASK:  (lfutex_t *uaddr, LFUTEX_WAIT_UNTIL_BITMASK, lfutex_t bitmask, struct timespec const *timeout, lfutex_t setmask)
 *    - LFUTEX_WAIT_WHILE_EX:       (lfutex_t *uaddr, LFUTEX_WAIT_WHILE_EX, void const *rhs, struct timespec const *timeout, size_t num_bytes)
 *    - LFUTEX_WAIT_UNTIL_EX:       (lfutex_t *uaddr, LFUTEX_WAIT_UNTIL_EX, void const *rhs, struct timespec const *timeout, size_t num_bytes)
 *    - LFUTEX_WAIT_WHILE_ABOVE_EX: (lfutex_t *uaddr, LFUTEX_WAIT_WHILE_ABOVE_EX, void const *rhs, struct timespec const *timeout, size_t num_bytes)
 *    - LFUTEX_WAIT_WHILE_BELOW_EX: (lfutex_t *uaddr, LFUTEX_WAIT_WHILE_BELOW_EX, void const *rhs, struct timespec const *timeout, size_t num_bytes)
 * @param: timeout: Timeout for wait operations (s.a. `LFUTEX_WAIT_FLAG_TIMEOUT_*')
 * @return: * : Depending on `futex_op'
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINVAL:    The given `futex_op' is invalid
 * @return: -1:EINTR:     A blocking futex-wait operation was interrupted
 * @return: -1:ETIMEDOUT: A blocking futex-wait operation has timed out */
INTERN ATTR_SECTION(".text.crt.sched.futex") NONNULL((1)) ssize_t
NOTHROW_RPC(VLIBCCALL libc_lfutex64)(lfutex_t *uaddr,
                                     syscall_ulong_t futex_op,
                                     lfutex_t val,
                                     ...)
/*[[[body:libc_lfutex64]]]*/
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
/*[[[end:libc_lfutex64]]]*/

/*[[[head:libc_futex_wake,hash:CRC-32=0x1b7562d9]]]*/
/* Wake up to `MAX_WAKE' threads waiting for `*UADDR'
 * @return: * : The number of woken threads
 * @return: -1:EFAULT: A faulty pointer was given */
INTERN ATTR_SECTION(".text.crt.sched.futex") NONNULL((1)) ssize_t
NOTHROW_NCX(LIBCCALL libc_futex_wake)(lfutex_t *uaddr,
                                      size_t max_wake)
/*[[[body:libc_futex_wake]]]*/
{
	ssize_t result;
	result = sys_lfutex(uaddr, LFUTEX_WAKE, (uintptr_t)max_wake, NULL, 0);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_futex_wake]]]*/

/*[[[head:libc_futex_wakemask,hash:CRC-32=0xeaaa51f4]]]*/
/* Similar to `futex_wake()', however once there are no more threads that
 * can be awoken, perform the following operation: `*uaddr = (*uaddr & mask_and) | mask_or'
 * @return: * : The number of woken threads
 * @return: -1:EFAULT: A faulty pointer was given */
INTERN ATTR_SECTION(".text.crt.sched.futex") NONNULL((1)) ssize_t
NOTHROW_NCX(LIBCCALL libc_futex_wakemask)(lfutex_t *uaddr,
                                          size_t max_wake,
                                          lfutex_t mask_and,
                                          lfutex_t mask_or)
/*[[[body:libc_futex_wakemask]]]*/
{
	ssize_t result;
	result = sys_lfutex(uaddr, LFUTEX_WAKEMASK,
	                    (uintptr_t)max_wake,
	                    (struct timespec64 const *)(uintptr_t)mask_and,
	                    (uintptr_t)mask_or);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_futex_wakemask]]]*/



/*[[[head:libc_futex_wakeall,hash:CRC-32=0xedbeda1a]]]*/
/* Wake all threads waiting for `*UADDR' (same as `futex_wake(uaddr, (size_t)-1)')
 * @return: * : The number of woken threads
 * @return: -1:EFAULT: A faulty pointer was given */
INTERN ATTR_SECTION(".text.crt.sched.futex") NONNULL((1)) ssize_t
NOTHROW_NCX(LIBCCALL libc_futex_wakeall)(lfutex_t *uaddr)
/*[[[body:libc_futex_wakeall]]]*/
{
	ssize_t result;
	result = sys_lfutex(uaddr,
	                    LFUTEX_WAKE,
	                    (uintptr_t)(size_t)-1,
	                    NULL,
	                    0);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_futex_wakeall]]]*/

/*[[[head:libc_futex_waitwhile,hash:CRC-32=0x50cc5c0a]]]*/
/* Wait if `*uaddr == equal_to_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
INTERN ATTR_SECTION(".text.crt.sched.futex") ATTR_IN(1) int
NOTHROW_RPC(LIBCCALL libc_futex_waitwhile)(lfutex_t *uaddr,
                                           lfutex_t equal_to_value)
/*[[[body:libc_futex_waitwhile]]]*/
{
	errno_t result;
	SPIN_WHILE(atomic_read(uaddr) == equal_to_value);
	result = (errno_t)sys_lfutex(uaddr,
	                             LFUTEX_WAIT_WHILE,
	                             (uintptr_t)equal_to_value,
	                             NULL,
	                             0);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_futex_waitwhile]]]*/

/*[[[head:libc_futex_waituntil,hash:CRC-32=0xae6ad533]]]*/
/* Wait if `*uaddr != not_equal_to_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
INTERN ATTR_SECTION(".text.crt.sched.futex") ATTR_IN(1) int
NOTHROW_RPC(LIBCCALL libc_futex_waituntil)(lfutex_t *uaddr,
                                           lfutex_t not_equal_to_value)
/*[[[body:libc_futex_waituntil]]]*/
{
	errno_t result;
	SPIN_WHILE(atomic_read(uaddr) != not_equal_to_value);
	result = (errno_t)sys_lfutex(uaddr,
	                             LFUTEX_WAIT_UNTIL,
	                             (uintptr_t)not_equal_to_value,
	                             NULL,
	                             0);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_futex_waituntil]]]*/

/*[[[head:libc_futex_waitwhile_above,hash:CRC-32=0x24426d06]]]*/
/* Wait if `*uaddr > above_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
INTERN ATTR_SECTION(".text.crt.sched.futex") ATTR_IN(1) int
NOTHROW_RPC(LIBCCALL libc_futex_waitwhile_above)(lfutex_t *uaddr,
                                                 lfutex_t above_value)
/*[[[body:libc_futex_waitwhile_above]]]*/
{
	errno_t result;
	SPIN_WHILE(atomic_read(uaddr) > above_value);
	result = (errno_t)sys_lfutex(uaddr,
	                             LFUTEX_WAIT_WHILE_ABOVE,
	                             (uintptr_t)above_value,
	                             NULL,
	                             0);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_futex_waitwhile_above]]]*/

/*[[[head:libc_futex_waitwhile_below,hash:CRC-32=0x142f22e3]]]*/
/* Wait if `*uaddr < below_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
INTERN ATTR_SECTION(".text.crt.sched.futex") ATTR_IN(1) int
NOTHROW_RPC(LIBCCALL libc_futex_waitwhile_below)(lfutex_t *uaddr,
                                                 lfutex_t below_value)
/*[[[body:libc_futex_waitwhile_below]]]*/
{
	errno_t result;
	SPIN_WHILE(atomic_read(uaddr) < below_value);
	result = (errno_t)sys_lfutex(uaddr,
	                             LFUTEX_WAIT_WHILE_BELOW,
	                             (uintptr_t)below_value,
	                             NULL,
	                             0);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_futex_waitwhile_below]]]*/

/*[[[head:libc_futex_waitwhile_aboveequal,hash:CRC-32=0xbfefb77d]]]*/
/* Wait if `*uaddr >= above_or_equal_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
INTERN ATTR_SECTION(".text.crt.sched.futex") ATTR_IN(1) int
NOTHROW_RPC(LIBCCALL libc_futex_waitwhile_aboveequal)(lfutex_t *uaddr,
                                                      lfutex_t above_or_equal_value)
/*[[[body:libc_futex_waitwhile_aboveequal]]]*/
{
	errno_t result;
	assert(above_or_equal_value != 0);
	SPIN_WHILE(atomic_read(uaddr) >= above_or_equal_value);
	result = (errno_t)sys_lfutex(uaddr, LFUTEX_WAIT_WHILE_ABOVE,
	                             (uintptr_t)above_or_equal_value - 1,
	                             NULL, 0);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_futex_waitwhile_aboveequal]]]*/

/*[[[head:libc_futex_waitwhile_belowequal,hash:CRC-32=0x67806fc4]]]*/
/* Wait if `*uaddr <= below_or_equal_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
INTERN ATTR_SECTION(".text.crt.sched.futex") ATTR_IN(1) int
NOTHROW_RPC(LIBCCALL libc_futex_waitwhile_belowequal)(lfutex_t *uaddr,
                                                      lfutex_t below_or_equal_value)
/*[[[body:libc_futex_waitwhile_belowequal]]]*/
{
	errno_t result;
	assert(below_or_equal_value != (lfutex_t)-1);
	SPIN_WHILE(atomic_read(uaddr) <= below_or_equal_value);
	result = (errno_t)sys_lfutex(uaddr, LFUTEX_WAIT_WHILE_BELOW,
	                             (uintptr_t)below_or_equal_value + 1,
	                             NULL, 0);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_futex_waitwhile_belowequal]]]*/

/*[[[head:libc_futex_waitwhile_exactbits,hash:CRC-32=0xa9a8f048]]]*/
/* Wait if `(*uaddr & bitmask) == setmask'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
INTERN ATTR_SECTION(".text.crt.sched.futex") ATTR_IN(1) int
NOTHROW_RPC(LIBCCALL libc_futex_waitwhile_exactbits)(lfutex_t *uaddr,
                                                     lfutex_t bitmask,
                                                     lfutex_t setmask)
/*[[[body:libc_futex_waitwhile_exactbits]]]*/
{
	errno_t result;
	SPIN_WHILE((atomic_read(uaddr) & bitmask) == setmask);
	result = (errno_t)sys_lfutex(uaddr,
	                             LFUTEX_WAIT_WHILE_BITMASK,
	                             (uintptr_t)bitmask,
	                             NULL,
	                             (uintptr_t)setmask);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_futex_waitwhile_exactbits]]]*/

/*[[[head:libc_futex_waituntil_exactbits,hash:CRC-32=0xa7ac06d1]]]*/
/* Wait if `(*uaddr & bitmask) != setmask'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
INTERN ATTR_SECTION(".text.crt.sched.futex") ATTR_IN(1) int
NOTHROW_RPC(LIBCCALL libc_futex_waituntil_exactbits)(lfutex_t *uaddr,
                                                     lfutex_t bitmask,
                                                     lfutex_t setmask)
/*[[[body:libc_futex_waituntil_exactbits]]]*/
{
	errno_t result;
	SPIN_WHILE((atomic_read(uaddr) & bitmask) != setmask);
	result = (errno_t)sys_lfutex(uaddr,
	                             LFUTEX_WAIT_UNTIL_BITMASK,
	                             (uintptr_t)bitmask,
	                             NULL,
	                             (uintptr_t)setmask);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_futex_waituntil_exactbits]]]*/

/*[[[head:libc_futex_waitwhile_anybit,hash:CRC-32=0xebb9f64a]]]*/
/* Wait if `(*uaddr & bitmask) != 0'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
INTERN ATTR_SECTION(".text.crt.sched.futex") ATTR_IN(1) int
NOTHROW_RPC(LIBCCALL libc_futex_waitwhile_anybit)(lfutex_t *uaddr,
                                                  lfutex_t bitmask)
/*[[[body:libc_futex_waitwhile_anybit]]]*/
{
	errno_t result;
	SPIN_WHILE((atomic_read(uaddr) & bitmask) != 0);
	result = (errno_t)sys_lfutex(uaddr,
	                             LFUTEX_WAIT_UNTIL_BITMASK,
	                             (uintptr_t)bitmask,
	                             NULL,
	                             (uintptr_t)0);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_futex_waitwhile_anybit]]]*/

/*[[[head:libc_futex_waitwhile_allbits,hash:CRC-32=0xe31459ef]]]*/
/* Wait if `(*uaddr & bitmask) == bitmask'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
INTERN ATTR_SECTION(".text.crt.sched.futex") ATTR_IN(1) int
NOTHROW_RPC(LIBCCALL libc_futex_waitwhile_allbits)(lfutex_t *uaddr,
                                                   lfutex_t bitmask)
/*[[[body:libc_futex_waitwhile_allbits]]]*/
{
	errno_t result;
	SPIN_WHILE((atomic_read(uaddr) & bitmask) == bitmask);
	result = (errno_t)sys_lfutex(uaddr,
	                             LFUTEX_WAIT_WHILE_BITMASK,
	                             (uintptr_t)bitmask,
	                             NULL,
	                             (uintptr_t)bitmask);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_futex_waitwhile_allbits]]]*/

/*[[[head:libc_futex_timedwaitwhile,hash:CRC-32=0x6745a4f9]]]*/
/* Wait if `*uaddr == equal_to_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
INTERN ATTR_SECTION(".text.crt.sched.futex") ATTR_IN(1) ATTR_IN_OPT(3) int
NOTHROW_RPC(LIBCCALL libc_futex_timedwaitwhile)(lfutex_t *uaddr,
                                                lfutex_t equal_to_value,
                                                struct timespec const *rel_timeout)
/*[[[body:libc_futex_timedwaitwhile]]]*/
{
	struct timespec64 tms64;
	if (!rel_timeout)
		return futex_timedwaitwhile64(uaddr, equal_to_value, NULL);
	tms64.tv_sec  = (time64_t)rel_timeout->tv_sec;
	tms64.tv_nsec = rel_timeout->tv_nsec;
	return futex_timedwaitwhile64(uaddr, equal_to_value, &tms64);
}
/*[[[end:libc_futex_timedwaitwhile]]]*/

/*[[[head:libc_futex_timedwaituntil,hash:CRC-32=0x950872df]]]*/
/* Wait if `*uaddr != not_equal_to_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
INTERN ATTR_SECTION(".text.crt.sched.futex") ATTR_IN(1) ATTR_IN_OPT(3) int
NOTHROW_RPC(LIBCCALL libc_futex_timedwaituntil)(lfutex_t *uaddr,
                                                lfutex_t not_equal_to_value,
                                                struct timespec const *rel_timeout)
/*[[[body:libc_futex_timedwaituntil]]]*/
{
	struct timespec64 tms64;
	if (!rel_timeout)
		return futex_timedwaituntil64(uaddr, not_equal_to_value, NULL);
	tms64.tv_sec  = (time64_t)rel_timeout->tv_sec;
	tms64.tv_nsec = rel_timeout->tv_nsec;
	return futex_timedwaituntil64(uaddr, not_equal_to_value, &tms64);
}
/*[[[end:libc_futex_timedwaituntil]]]*/

/*[[[head:libc_futex_timedwaitwhile_above,hash:CRC-32=0xa7e040d4]]]*/
/* Wait if `*uaddr > above_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
INTERN ATTR_SECTION(".text.crt.sched.futex") ATTR_IN(1) ATTR_IN_OPT(3) int
NOTHROW_RPC(LIBCCALL libc_futex_timedwaitwhile_above)(lfutex_t *uaddr,
                                                      lfutex_t above_value,
                                                      struct timespec const *rel_timeout)
/*[[[body:libc_futex_timedwaitwhile_above]]]*/
{
	struct timespec64 tms64;
	if (!rel_timeout)
		return futex_timedwaitwhile_above64(uaddr, above_value, NULL);
	tms64.tv_sec  = (time64_t)rel_timeout->tv_sec;
	tms64.tv_nsec = rel_timeout->tv_nsec;
	return futex_timedwaitwhile_above64(uaddr, above_value, &tms64);
}
/*[[[end:libc_futex_timedwaitwhile_above]]]*/

/*[[[head:libc_futex_timedwaitwhile_below,hash:CRC-32=0x6c986881]]]*/
/* Wait if `*uaddr < below_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
INTERN ATTR_SECTION(".text.crt.sched.futex") ATTR_IN(1) ATTR_IN_OPT(3) int
NOTHROW_RPC(LIBCCALL libc_futex_timedwaitwhile_below)(lfutex_t *uaddr,
                                                      lfutex_t below_value,
                                                      struct timespec const *rel_timeout)
/*[[[body:libc_futex_timedwaitwhile_below]]]*/
{
	struct timespec64 tms64;
	if (!rel_timeout)
		return futex_timedwaitwhile_below64(uaddr, below_value, NULL);
	tms64.tv_sec  = (time64_t)rel_timeout->tv_sec;
	tms64.tv_nsec = rel_timeout->tv_nsec;
	return futex_timedwaitwhile_below64(uaddr, below_value, &tms64);
}
/*[[[end:libc_futex_timedwaitwhile_below]]]*/

/*[[[head:libc_futex_timedwaitwhile_aboveequal,hash:CRC-32=0x6d709b58]]]*/
/* Wait if `*uaddr >= above_or_equal_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
INTERN ATTR_SECTION(".text.crt.sched.futex") ATTR_IN(1) ATTR_IN_OPT(3) int
NOTHROW_RPC(LIBCCALL libc_futex_timedwaitwhile_aboveequal)(lfutex_t *uaddr,
                                                           lfutex_t above_or_equal_value,
                                                           struct timespec const *rel_timeout)
/*[[[body:libc_futex_timedwaitwhile_aboveequal]]]*/
{
	struct timespec64 tms64;
	if (!rel_timeout)
		return futex_timedwaitwhile_aboveequal64(uaddr, above_or_equal_value, NULL);
	tms64.tv_sec  = (time64_t)rel_timeout->tv_sec;
	tms64.tv_nsec = rel_timeout->tv_nsec;
	return futex_timedwaitwhile_aboveequal64(uaddr, above_or_equal_value, &tms64);
}
/*[[[end:libc_futex_timedwaitwhile_aboveequal]]]*/

/*[[[head:libc_futex_timedwaitwhile_belowequal,hash:CRC-32=0xb574acb7]]]*/
/* Wait if `*uaddr <= below_or_equal_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
INTERN ATTR_SECTION(".text.crt.sched.futex") ATTR_IN(1) ATTR_IN_OPT(3) int
NOTHROW_RPC(LIBCCALL libc_futex_timedwaitwhile_belowequal)(lfutex_t *uaddr,
                                                           lfutex_t below_or_equal_value,
                                                           struct timespec const *rel_timeout)
/*[[[body:libc_futex_timedwaitwhile_belowequal]]]*/
{
	struct timespec64 tms64;
	if (!rel_timeout)
		return futex_timedwaitwhile_belowequal64(uaddr, below_or_equal_value, NULL);
	tms64.tv_sec  = (time64_t)rel_timeout->tv_sec;
	tms64.tv_nsec = rel_timeout->tv_nsec;
	return futex_timedwaitwhile_belowequal64(uaddr, below_or_equal_value, &tms64);
}
/*[[[end:libc_futex_timedwaitwhile_belowequal]]]*/

/*[[[head:libc_futex_timedwaitwhile_exactbits,hash:CRC-32=0xef74a598]]]*/
/* Wait if `(*uaddr & bitmask) == setmask'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
INTERN ATTR_SECTION(".text.crt.sched.futex") ATTR_IN(1) ATTR_IN_OPT(4) int
NOTHROW_RPC(LIBCCALL libc_futex_timedwaitwhile_exactbits)(lfutex_t *uaddr,
                                                          lfutex_t bitmask,
                                                          lfutex_t setmask,
                                                          struct timespec const *rel_timeout)
/*[[[body:libc_futex_timedwaitwhile_exactbits]]]*/
{
	struct timespec64 tms64;
	if (!rel_timeout)
		return futex_timedwaitwhile_exactbits64(uaddr, bitmask, setmask, NULL);
	tms64.tv_sec  = (time64_t)rel_timeout->tv_sec;
	tms64.tv_nsec = rel_timeout->tv_nsec;
	return futex_timedwaitwhile_exactbits64(uaddr, bitmask, setmask, &tms64);
}
/*[[[end:libc_futex_timedwaitwhile_exactbits]]]*/

/*[[[head:libc_futex_timedwaituntil_exactbits,hash:CRC-32=0x940768fd]]]*/
/* Wait if `(*uaddr & bitmask) != setmask'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
INTERN ATTR_SECTION(".text.crt.sched.futex") ATTR_IN(1) ATTR_IN_OPT(4) int
NOTHROW_RPC(LIBCCALL libc_futex_timedwaituntil_exactbits)(lfutex_t *uaddr,
                                                          lfutex_t bitmask,
                                                          lfutex_t setmask,
                                                          struct timespec const *rel_timeout)
/*[[[body:libc_futex_timedwaituntil_exactbits]]]*/
{
	struct timespec64 tms64;
	if (!rel_timeout)
		return futex_timedwaituntil_exactbits64(uaddr, bitmask, setmask, NULL);
	tms64.tv_sec  = (time64_t)rel_timeout->tv_sec;
	tms64.tv_nsec = rel_timeout->tv_nsec;
	return futex_timedwaituntil_exactbits64(uaddr, bitmask, setmask, &tms64);
}
/*[[[end:libc_futex_timedwaituntil_exactbits]]]*/

/*[[[head:libc_futex_timedwaitwhile_anybit,hash:CRC-32=0x6d3c5cf1]]]*/
/* Wait if `(*uaddr & bitmask) != 0'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
INTERN ATTR_SECTION(".text.crt.sched.futex") ATTR_IN(1) ATTR_IN_OPT(3) int
NOTHROW_RPC(LIBCCALL libc_futex_timedwaitwhile_anybit)(lfutex_t *uaddr,
                                                       lfutex_t bitmask,
                                                       struct timespec const *rel_timeout)
/*[[[body:libc_futex_timedwaitwhile_anybit]]]*/
{
	struct timespec64 tms64;
	if (!rel_timeout)
		return futex_timedwaitwhile_anybit64(uaddr, bitmask, NULL);
	tms64.tv_sec  = (time64_t)rel_timeout->tv_sec;
	tms64.tv_nsec = rel_timeout->tv_nsec;
	return futex_timedwaitwhile_anybit64(uaddr, bitmask, &tms64);
}
/*[[[end:libc_futex_timedwaitwhile_anybit]]]*/

/*[[[head:libc_futex_timedwaitwhile_allbits,hash:CRC-32=0xe52c07a4]]]*/
/* Wait if `(*uaddr & bitmask) == bitmask'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
INTERN ATTR_SECTION(".text.crt.sched.futex") ATTR_IN(1) ATTR_IN_OPT(3) int
NOTHROW_RPC(LIBCCALL libc_futex_timedwaitwhile_allbits)(lfutex_t *uaddr,
                                                        lfutex_t bitmask,
                                                        struct timespec const *rel_timeout)
/*[[[body:libc_futex_timedwaitwhile_allbits]]]*/
{
	struct timespec64 tms64;
	if (!rel_timeout)
		return futex_timedwaitwhile_allbits64(uaddr, bitmask, NULL);
	tms64.tv_sec  = (time64_t)rel_timeout->tv_sec;
	tms64.tv_nsec = rel_timeout->tv_nsec;
	return futex_timedwaitwhile_allbits64(uaddr, bitmask, &tms64);
}
/*[[[end:libc_futex_timedwaitwhile_allbits]]]*/

/*[[[head:libc_futex_timedwaitwhile64,hash:CRC-32=0xc726bd7b]]]*/
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_futex_timedwaitwhile64, libc_futex_timedwaitwhile);
#else /* MAGIC:alias */
/* Wait if `*uaddr == equal_to_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
INTERN ATTR_SECTION(".text.crt.sched.futex") ATTR_IN(1) ATTR_IN_OPT(3) int
NOTHROW_RPC(LIBCCALL libc_futex_timedwaitwhile64)(lfutex_t *uaddr,
                                                  lfutex_t equal_to_value,
                                                  struct timespec64 const *rel_timeout)
/*[[[body:libc_futex_timedwaitwhile64]]]*/
{
	errno_t result;
	SPIN_WHILE(atomic_read(uaddr) == equal_to_value);
	result = (errno_t)sys_lfutex(uaddr,
	                             LFUTEX_WAIT_WHILE |
	                             LFUTEX_WAIT_FLAG_TIMEOUT_RELATIVE,
	                             (uintptr_t)equal_to_value,
	                             rel_timeout,
	                             (uintptr_t)0);
	return libc_seterrno_syserr(result);
}
#endif /* MAGIC:alias */
/*[[[end:libc_futex_timedwaitwhile64]]]*/

/*[[[head:libc_futex_timedwaituntil64,hash:CRC-32=0xdb032b8]]]*/
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_futex_timedwaituntil64, libc_futex_timedwaituntil);
#else /* MAGIC:alias */
/* Wait if `*uaddr != not_equal_to_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
INTERN ATTR_SECTION(".text.crt.sched.futex") ATTR_IN(1) ATTR_IN_OPT(3) int
NOTHROW_RPC(LIBCCALL libc_futex_timedwaituntil64)(lfutex_t *uaddr,
                                                  lfutex_t not_equal_to_value,
                                                  struct timespec64 const *rel_timeout)
/*[[[body:libc_futex_timedwaituntil64]]]*/
{
	errno_t result;
	SPIN_WHILE(atomic_read(uaddr) != not_equal_to_value);
	result = (errno_t)sys_lfutex(uaddr,
	                             LFUTEX_WAIT_UNTIL |
	                             LFUTEX_WAIT_FLAG_TIMEOUT_RELATIVE,
	                             (uintptr_t)not_equal_to_value,
	                             rel_timeout,
	                             (uintptr_t)0);
	return libc_seterrno_syserr(result);
}
#endif /* MAGIC:alias */
/*[[[end:libc_futex_timedwaituntil64]]]*/

/*[[[head:libc_futex_timedwaitwhile_above64,hash:CRC-32=0xe7f3ea4d]]]*/
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_futex_timedwaitwhile_above64, libc_futex_timedwaitwhile_above);
#else /* MAGIC:alias */
/* Wait if `*uaddr > above_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
INTERN ATTR_SECTION(".text.crt.sched.futex") ATTR_IN(1) ATTR_IN_OPT(3) int
NOTHROW_RPC(LIBCCALL libc_futex_timedwaitwhile_above64)(lfutex_t *uaddr,
                                                        lfutex_t above_value,
                                                        struct timespec64 const *rel_timeout)
/*[[[body:libc_futex_timedwaitwhile_above64]]]*/
{
	errno_t result;
	SPIN_WHILE(atomic_read(uaddr) > above_value);
	result = (errno_t)sys_lfutex(uaddr,
	                             LFUTEX_WAIT_WHILE_ABOVE |
	                             LFUTEX_WAIT_FLAG_TIMEOUT_RELATIVE,
	                             (uintptr_t)above_value,
	                             rel_timeout,
	                             (uintptr_t)0);
	return libc_seterrno_syserr(result);
}
#endif /* MAGIC:alias */
/*[[[end:libc_futex_timedwaitwhile_above64]]]*/

/*[[[head:libc_futex_timedwaitwhile_below64,hash:CRC-32=0x6c1cb7f6]]]*/
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_futex_timedwaitwhile_below64, libc_futex_timedwaitwhile_below);
#else /* MAGIC:alias */
/* Wait if `*uaddr < below_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
INTERN ATTR_SECTION(".text.crt.sched.futex") ATTR_IN(1) ATTR_IN_OPT(3) int
NOTHROW_RPC(LIBCCALL libc_futex_timedwaitwhile_below64)(lfutex_t *uaddr,
                                                        lfutex_t below_value,
                                                        struct timespec64 const *rel_timeout)
/*[[[body:libc_futex_timedwaitwhile_below64]]]*/
{
	errno_t result;
	SPIN_WHILE(atomic_read(uaddr) < below_value);
	result = (errno_t)sys_lfutex(uaddr,
	                             LFUTEX_WAIT_WHILE_BELOW |
	                             LFUTEX_WAIT_FLAG_TIMEOUT_RELATIVE,
	                             (uintptr_t)below_value,
	                             rel_timeout,
	                             (uintptr_t)0);
	return libc_seterrno_syserr(result);
}
#endif /* MAGIC:alias */
/*[[[end:libc_futex_timedwaitwhile_below64]]]*/

/*[[[head:libc_futex_timedwaitwhile_aboveequal64,hash:CRC-32=0xee25b49c]]]*/
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_futex_timedwaitwhile_aboveequal64, libc_futex_timedwaitwhile_aboveequal);
#else /* MAGIC:alias */
/* Wait if `*uaddr >= above_or_equal_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
INTERN ATTR_SECTION(".text.crt.sched.futex") ATTR_IN(1) ATTR_IN_OPT(3) int
NOTHROW_RPC(LIBCCALL libc_futex_timedwaitwhile_aboveequal64)(lfutex_t *uaddr,
                                                             lfutex_t above_or_equal_value,
                                                             struct timespec64 const *rel_timeout)
/*[[[body:libc_futex_timedwaitwhile_aboveequal64]]]*/
{
	errno_t result;
	assert(above_or_equal_value != 0);
	SPIN_WHILE(atomic_read(uaddr) >= above_or_equal_value);
	result = (errno_t)sys_lfutex(uaddr,
	                             LFUTEX_WAIT_WHILE_ABOVE | LFUTEX_WAIT_FLAG_TIMEOUT_RELATIVE,
	                             (uintptr_t)above_or_equal_value - 1,
	                             rel_timeout, (uintptr_t)0);
	return libc_seterrno_syserr(result);
}
#endif /* MAGIC:alias */
/*[[[end:libc_futex_timedwaitwhile_aboveequal64]]]*/

/*[[[head:libc_futex_timedwaitwhile_belowequal64,hash:CRC-32=0x862fc2c1]]]*/
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_futex_timedwaitwhile_belowequal64, libc_futex_timedwaitwhile_belowequal);
#else /* MAGIC:alias */
/* Wait if `*uaddr <= below_or_equal_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
INTERN ATTR_SECTION(".text.crt.sched.futex") ATTR_IN(1) ATTR_IN_OPT(3) int
NOTHROW_RPC(LIBCCALL libc_futex_timedwaitwhile_belowequal64)(lfutex_t *uaddr,
                                                             lfutex_t below_or_equal_value,
                                                             struct timespec64 const *rel_timeout)
/*[[[body:libc_futex_timedwaitwhile_belowequal64]]]*/
{
	errno_t result;
	assert(below_or_equal_value != (lfutex_t)-1);
	SPIN_WHILE(atomic_read(uaddr) <= below_or_equal_value);
	result = (errno_t)sys_lfutex(uaddr,
	                             LFUTEX_WAIT_WHILE_BELOW | LFUTEX_WAIT_FLAG_TIMEOUT_RELATIVE,
	                             (uintptr_t)below_or_equal_value + 1,
	                             rel_timeout, (uintptr_t)0);
	return libc_seterrno_syserr(result);
}
#endif /* MAGIC:alias */
/*[[[end:libc_futex_timedwaitwhile_belowequal64]]]*/

/*[[[head:libc_futex_timedwaitwhile_exactbits64,hash:CRC-32=0x38dab1f0]]]*/
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_futex_timedwaitwhile_exactbits64, libc_futex_timedwaitwhile_exactbits);
#else /* MAGIC:alias */
/* Wait if `(*uaddr & bitmask) == setmask'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
INTERN ATTR_SECTION(".text.crt.sched.futex") ATTR_IN(1) ATTR_IN_OPT(4) int
NOTHROW_RPC(LIBCCALL libc_futex_timedwaitwhile_exactbits64)(lfutex_t *uaddr,
                                                            lfutex_t bitmask,
                                                            lfutex_t setmask,
                                                            struct timespec64 const *rel_timeout)
/*[[[body:libc_futex_timedwaitwhile_exactbits64]]]*/
{
	errno_t result;
	SPIN_WHILE((atomic_read(uaddr) & bitmask) == setmask);
	result = (errno_t)sys_lfutex(uaddr,
	                             LFUTEX_WAIT_WHILE_BITMASK |
	                             LFUTEX_WAIT_FLAG_TIMEOUT_RELATIVE,
	                             (uintptr_t)bitmask,
	                             rel_timeout,
	                             (uintptr_t)setmask);
	return libc_seterrno_syserr(result);
}
#endif /* MAGIC:alias */
/*[[[end:libc_futex_timedwaitwhile_exactbits64]]]*/

/*[[[head:libc_futex_timedwaituntil_exactbits64,hash:CRC-32=0xf12e90d1]]]*/
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_futex_timedwaituntil_exactbits64, libc_futex_timedwaituntil_exactbits);
#else /* MAGIC:alias */
/* Wait if `(*uaddr & bitmask) != setmask'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
INTERN ATTR_SECTION(".text.crt.sched.futex") ATTR_IN(1) ATTR_IN_OPT(4) int
NOTHROW_RPC(LIBCCALL libc_futex_timedwaituntil_exactbits64)(lfutex_t *uaddr,
                                                            lfutex_t bitmask,
                                                            lfutex_t setmask,
                                                            struct timespec64 const *rel_timeout)
/*[[[body:libc_futex_timedwaituntil_exactbits64]]]*/
{
	errno_t result;
	SPIN_WHILE((atomic_read(uaddr) & bitmask) != setmask);
	result = (errno_t)sys_lfutex(uaddr,
	                             LFUTEX_WAIT_UNTIL_BITMASK |
	                             LFUTEX_WAIT_FLAG_TIMEOUT_RELATIVE,
	                             (uintptr_t)bitmask,
	                             rel_timeout,
	                             (uintptr_t)setmask);
	return libc_seterrno_syserr(result);
}
#endif /* MAGIC:alias */
/*[[[end:libc_futex_timedwaituntil_exactbits64]]]*/

/*[[[head:libc_futex_timedwaitwhile_anybit64,hash:CRC-32=0x613456e0]]]*/
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_futex_timedwaitwhile_anybit64, libc_futex_timedwaitwhile_anybit);
#else /* MAGIC:alias */
/* Wait if `(*uaddr & bitmask) != 0'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
INTERN ATTR_SECTION(".text.crt.sched.futex") ATTR_IN(1) ATTR_IN_OPT(3) int
NOTHROW_RPC(LIBCCALL libc_futex_timedwaitwhile_anybit64)(lfutex_t *uaddr,
                                                         lfutex_t bitmask,
                                                         struct timespec64 const *rel_timeout)
/*[[[body:libc_futex_timedwaitwhile_anybit64]]]*/
{
	errno_t result;
	SPIN_WHILE((atomic_read(uaddr) & bitmask) != 0);
	result = (errno_t)sys_lfutex(uaddr,
	                             LFUTEX_WAIT_UNTIL_BITMASK |
	                             LFUTEX_WAIT_FLAG_TIMEOUT_RELATIVE,
	                             (uintptr_t)bitmask,
	                             rel_timeout,
	                             (uintptr_t)0);
	return libc_seterrno_syserr(result);
}
#endif /* MAGIC:alias */
/*[[[end:libc_futex_timedwaitwhile_anybit64]]]*/

/*[[[head:libc_futex_timedwaitwhile_allbits64,hash:CRC-32=0xb2ae4c00]]]*/
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_futex_timedwaitwhile_allbits64, libc_futex_timedwaitwhile_allbits);
#else /* MAGIC:alias */
/* Wait if `(*uaddr & bitmask) == bitmask'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
INTERN ATTR_SECTION(".text.crt.sched.futex") ATTR_IN(1) ATTR_IN_OPT(3) int
NOTHROW_RPC(LIBCCALL libc_futex_timedwaitwhile_allbits64)(lfutex_t *uaddr,
                                                          lfutex_t bitmask,
                                                          struct timespec64 const *rel_timeout)
/*[[[body:libc_futex_timedwaitwhile_allbits64]]]*/
{
	errno_t result;
	SPIN_WHILE((atomic_read(uaddr) & bitmask) == bitmask);
	result = (errno_t)sys_lfutex(uaddr,
	                             LFUTEX_WAIT_WHILE_BITMASK |
	                             LFUTEX_WAIT_FLAG_TIMEOUT_RELATIVE,
	                             (uintptr_t)bitmask,
	                             rel_timeout,
	                             (uintptr_t)bitmask);
	return libc_seterrno_syserr(result);
}
#endif /* MAGIC:alias */
/*[[[end:libc_futex_timedwaitwhile_allbits64]]]*/

/*[[[head:libc_futex_getspin,hash:CRC-32=0x4183c524]]]*/
/* Get/Set the number of times to spin the following futex operations without
 * entering  kernel-space,  setting  waiter-bits,  and  entering  sleep mode:
 *   - LFUTEX_WAIT_WHILE: SPIN({ if (*uaddr != val) DONE(); });
 *   - LFUTEX_WAIT_UNTIL: SPIN({ if (*uaddr == val) DONE(); });
 *   - ...
 * Futex spinning improves  performance by bypassing  expensive blocking  operations
 * when associated locks  are often only  held for a  couple of moments  at a  time.
 * Take for example `lfutex(LFUTEX_WAIT_WHILE)' (or preferably `futex_waitwhile()'),
 * which is wrapped like this:
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
INTERN ATTR_SECTION(".text.crt.sched.futex") WUNUSED unsigned int
NOTHROW(LIBCCALL libc_futex_getspin)(void)
/*[[[body:libc_futex_getspin]]]*/
{
#ifdef NO_FUTEX_SPIN
	return 0;
#else /* NO_FUTEX_SPIN */
	return atomic_read(&futex_spin_counter);
#endif /* !NO_FUTEX_SPIN */
}
/*[[[end:libc_futex_getspin]]]*/

/*[[[head:libc_futex_setspin,hash:CRC-32=0xde86c264]]]*/
/* Get/Set the number of times to spin the following futex operations without
 * entering  kernel-space,  setting  waiter-bits,  and  entering  sleep mode:
 *   - LFUTEX_WAIT_WHILE: SPIN({ if (*uaddr != val) DONE(); });
 *   - LFUTEX_WAIT_UNTIL: SPIN({ if (*uaddr == val) DONE(); });
 *   - ...
 * Futex spinning improves  performance by bypassing  expensive blocking  operations
 * when associated locks  are often only  held for a  couple of moments  at a  time.
 * Take for example `lfutex(LFUTEX_WAIT_WHILE)' (or preferably `futex_waitwhile()'),
 * which is wrapped like this:
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
INTERN ATTR_SECTION(".text.crt.sched.futex") unsigned int
NOTHROW(LIBCCALL libc_futex_setspin)(unsigned int new_spin)
/*[[[body:libc_futex_setspin]]]*/
{
#ifdef NO_FUTEX_SPIN
	(void)new_spin;
	return 0;
#else /* NO_FUTEX_SPIN */
	return atomic_xch(&futex_spin_counter, new_spin);
#endif /* !NO_FUTEX_SPIN */
}
/*[[[end:libc_futex_setspin]]]*/





/*[[[start:exports,hash:CRC-32=0x579a238]]]*/
DEFINE_PUBLIC_ALIAS(lfutex, libc_lfutex);
DEFINE_PUBLIC_ALIAS(lfutex64, libc_lfutex64);
DEFINE_PUBLIC_ALIAS(futex_wake, libc_futex_wake);
DEFINE_PUBLIC_ALIAS(futex_wakeall, libc_futex_wakeall);
DEFINE_PUBLIC_ALIAS(futex_wakemask, libc_futex_wakemask);
DEFINE_PUBLIC_ALIAS(futex_waitwhile, libc_futex_waitwhile);
DEFINE_PUBLIC_ALIAS(futex_waituntil, libc_futex_waituntil);
DEFINE_PUBLIC_ALIAS(futex_waitwhile_above, libc_futex_waitwhile_above);
DEFINE_PUBLIC_ALIAS(futex_waitwhile_below, libc_futex_waitwhile_below);
DEFINE_PUBLIC_ALIAS(futex_waitwhile_aboveequal, libc_futex_waitwhile_aboveequal);
DEFINE_PUBLIC_ALIAS(futex_waitwhile_belowequal, libc_futex_waitwhile_belowequal);
DEFINE_PUBLIC_ALIAS(futex_waitwhile_exactbits, libc_futex_waitwhile_exactbits);
DEFINE_PUBLIC_ALIAS(futex_waituntil_exactbits, libc_futex_waituntil_exactbits);
DEFINE_PUBLIC_ALIAS(futex_waitwhile_anybit, libc_futex_waitwhile_anybit);
DEFINE_PUBLIC_ALIAS(futex_waitwhile_allbits, libc_futex_waitwhile_allbits);
DEFINE_PUBLIC_ALIAS(futex_timedwaitwhile, libc_futex_timedwaitwhile);
DEFINE_PUBLIC_ALIAS(futex_timedwaituntil, libc_futex_timedwaituntil);
DEFINE_PUBLIC_ALIAS(futex_timedwaitwhile_above, libc_futex_timedwaitwhile_above);
DEFINE_PUBLIC_ALIAS(futex_timedwaitwhile_below, libc_futex_timedwaitwhile_below);
DEFINE_PUBLIC_ALIAS(futex_timedwaitwhile_aboveequal, libc_futex_timedwaitwhile_aboveequal);
DEFINE_PUBLIC_ALIAS(futex_timedwaitwhile_belowequal, libc_futex_timedwaitwhile_belowequal);
DEFINE_PUBLIC_ALIAS(futex_timedwaitwhile_exactbits, libc_futex_timedwaitwhile_exactbits);
DEFINE_PUBLIC_ALIAS(futex_timedwaituntil_exactbits, libc_futex_timedwaituntil_exactbits);
DEFINE_PUBLIC_ALIAS(futex_timedwaitwhile_anybit, libc_futex_timedwaitwhile_anybit);
DEFINE_PUBLIC_ALIAS(futex_timedwaitwhile_allbits, libc_futex_timedwaitwhile_allbits);
DEFINE_PUBLIC_ALIAS(futex_timedwaitwhile64, libc_futex_timedwaitwhile64);
DEFINE_PUBLIC_ALIAS(futex_timedwaituntil64, libc_futex_timedwaituntil64);
DEFINE_PUBLIC_ALIAS(futex_timedwaitwhile_above64, libc_futex_timedwaitwhile_above64);
DEFINE_PUBLIC_ALIAS(futex_timedwaitwhile_below64, libc_futex_timedwaitwhile_below64);
DEFINE_PUBLIC_ALIAS(futex_timedwaitwhile_aboveequal64, libc_futex_timedwaitwhile_aboveequal64);
DEFINE_PUBLIC_ALIAS(futex_timedwaitwhile_belowequal64, libc_futex_timedwaitwhile_belowequal64);
DEFINE_PUBLIC_ALIAS(futex_timedwaitwhile_exactbits64, libc_futex_timedwaitwhile_exactbits64);
DEFINE_PUBLIC_ALIAS(futex_timedwaituntil_exactbits64, libc_futex_timedwaituntil_exactbits64);
DEFINE_PUBLIC_ALIAS(futex_timedwaitwhile_anybit64, libc_futex_timedwaitwhile_anybit64);
DEFINE_PUBLIC_ALIAS(futex_timedwaitwhile_allbits64, libc_futex_timedwaitwhile_allbits64);
DEFINE_PUBLIC_ALIAS(futex_getspin, libc_futex_getspin);
DEFINE_PUBLIC_ALIAS(futex_setspin, libc_futex_setspin);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_KOS_FUTEX_C */
