/* HASH CRC-32:0x61e7a107 */
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
#ifndef __local_lfutex64_defined
#if defined(__CRT_HAVE_lfutex)
#define __local_lfutex64_defined 1
/* Dependency: "lfutex32" from "kos.futex" */
#ifndef ____localdep_lfutex32_defined
#define ____localdep_lfutex32_defined 1
#if defined(__CRT_HAVE_lfutex)
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
__CREDIRECT(__ATTR_NONNULL((1)),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_lfutex32,(__uintptr_t *__uaddr, __syscall_ulong_t __futex_op, __uintptr_t __val, /*struct timespec const *timeout, lfutex_t val2*/...),lfutex,(__uaddr,__futex_op,__val,))
#else /* LIBC: lfutex */
#undef ____localdep_lfutex32_defined
#endif /* lfutex32... */
#endif /* !____localdep_lfutex32_defined */

__NAMESPACE_LOCAL_BEGIN
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
__LOCAL_LIBC(lfutex64) __ATTR_NONNULL((1)) __SSIZE_TYPE__
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(lfutex64))(__uintptr_t *__uaddr,
                                                      __syscall_ulong_t __futex_op,
                                                      __uintptr_t __val,
                                                      /*struct timespec64 const *timeout, lfutex_t val2*/...) {
#line 309 "kos/src/libc/magic/kos.futex.c"
	__builtin_va_list __args;
	__uintptr_t __val2;
	struct __timespec32 __tms32;
	struct __timespec64 *__timeout;
	__builtin_va_start(__args, __val);
	__timeout = __builtin_va_arg(__args, struct __timespec64 *);
	__val2 = __builtin_va_arg(__args, __uintptr_t);
	__builtin_va_end(__args);
	if (!__timeout || !LFUTEX_USES_TIMEOUT(__futex_op))
		return __localdep_lfutex32(__uaddr, __futex_op, __val, (struct __timespec32 *)__NULLPTR, __val2);
	__tms32.tv_sec  = (__time32_t)__timeout->tv_sec;
	__tms32.tv_nsec = __timeout->tv_nsec;
	return __localdep_lfutex32(__uaddr, __futex_op, __val, &__tms32, __val2);
}
__NAMESPACE_LOCAL_END
#endif /* defined(__CRT_HAVE_lfutex) */
#endif /* !__local_lfutex64_defined */
