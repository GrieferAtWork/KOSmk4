/* HASH CRC-32:0xc0e33b3d */
/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_lfutex_defined
#define __local_lfutex_defined 1
#include <__crt.h>
#if defined(__CRT_HAVE_lfutex) || defined(__CRT_HAVE_lfutex64)
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: lfutex64 from kos.futex */
#ifndef __local___localdep_lfutex64_defined
#define __local___localdep_lfutex64_defined 1
#ifdef __CRT_HAVE_lfutex64
/* >> lfutex(2)
 * Provide the bottom-most API for implementing user-space synchronization on KOS
 * @param: futex_op: One of:
 *    - LFUTEX_WAKE:               (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAKE, size_t val = count)
 *    - LFUTEX_WAKEMASK:           (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAKEMASK, size_t val = count, lfutex_t mask_and, lfutex_t mask_or)
 *    - LFUTEX_NOP:                (lfutex_t *uaddr, syscall_ulong_t LFUTEX_NOP, size_t val = ignored)
 *    - LFUTEX_WAIT:               (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT, lfutex_t val = ignored, struct timespec const *timeout)
 *    - LFUTEX_WAIT_LOCK:          (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_LOCK, lfutex_t val = lock_value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE:         (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE, lfutex_t val = value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_UNTIL:         (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_UNTIL, lfutex_t val = value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_ABOVE:   (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE_ABOVE, lfutex_t val = value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_BELOW:   (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE_BELOW, lfutex_t val = value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_BITMASK: (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE_BITMASK, lfutex_t val = bitmask, struct timespec const *timeout, lfutex_t setmask)
 *    - LFUTEX_WAIT_UNTIL_BITMASK: (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_UNTIL_BITMASK, lfutex_t val = bitmask, struct timespec const *timeout, lfutex_t setmask)
 *    - LFUTEX_WAIT_WHILE_CMPXCH:  (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE_CMPXCH, lfutex_t val = oldval, struct timespec const *timeout, lfutex_t newval)
 *    - LFUTEX_WAIT_UNTIL_CMPXCH:  (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_UNTIL_CMPXCH, lfutex_t val = oldval, struct timespec const *timeout, lfutex_t newval)
 * @param: timeout: Timeout for wait operations (s.a. `LFUTEX_WAIT_FLAG_TIMEOUT_*')
 * @return: * : Depending on `futex_op'
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINVAL:    The given `futex_op' is invalid
 * @return: -1:EINTR:     A blocking futex-wait operation was interrupted
 * @return: -1:ETIMEDOUT: A blocking futex-wait operation has timed out */
__CVREDIRECT(__ATTR_NONNULL((1)),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_lfutex64,(__uintptr_t *__uaddr, __syscall_ulong_t __futex_op, __uintptr_t __val),lfutex64,(__uaddr,__futex_op,__val),__val,2,(void *,__UINTPTR_TYPE__))
#elif defined(__CRT_HAVE_lfutex) && (__SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> lfutex(2)
 * Provide the bottom-most API for implementing user-space synchronization on KOS
 * @param: futex_op: One of:
 *    - LFUTEX_WAKE:               (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAKE, size_t val = count)
 *    - LFUTEX_WAKEMASK:           (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAKEMASK, size_t val = count, lfutex_t mask_and, lfutex_t mask_or)
 *    - LFUTEX_NOP:                (lfutex_t *uaddr, syscall_ulong_t LFUTEX_NOP, size_t val = ignored)
 *    - LFUTEX_WAIT:               (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT, lfutex_t val = ignored, struct timespec const *timeout)
 *    - LFUTEX_WAIT_LOCK:          (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_LOCK, lfutex_t val = lock_value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE:         (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE, lfutex_t val = value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_UNTIL:         (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_UNTIL, lfutex_t val = value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_ABOVE:   (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE_ABOVE, lfutex_t val = value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_BELOW:   (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE_BELOW, lfutex_t val = value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_BITMASK: (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE_BITMASK, lfutex_t val = bitmask, struct timespec const *timeout, lfutex_t setmask)
 *    - LFUTEX_WAIT_UNTIL_BITMASK: (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_UNTIL_BITMASK, lfutex_t val = bitmask, struct timespec const *timeout, lfutex_t setmask)
 *    - LFUTEX_WAIT_WHILE_CMPXCH:  (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE_CMPXCH, lfutex_t val = oldval, struct timespec const *timeout, lfutex_t newval)
 *    - LFUTEX_WAIT_UNTIL_CMPXCH:  (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_UNTIL_CMPXCH, lfutex_t val = oldval, struct timespec const *timeout, lfutex_t newval)
 * @param: timeout: Timeout for wait operations (s.a. `LFUTEX_WAIT_FLAG_TIMEOUT_*')
 * @return: * : Depending on `futex_op'
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINVAL:    The given `futex_op' is invalid
 * @return: -1:EINTR:     A blocking futex-wait operation was interrupted
 * @return: -1:ETIMEDOUT: A blocking futex-wait operation has timed out */
__CVREDIRECT(__ATTR_NONNULL((1)),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_lfutex64,(__uintptr_t *__uaddr, __syscall_ulong_t __futex_op, __uintptr_t __val),lfutex,(__uaddr,__futex_op,__val),__val,2,(void *,__UINTPTR_TYPE__))
#elif defined(__CRT_HAVE_lfutex)
__NAMESPACE_LOCAL_END
#include <local/kos.futex/lfutex64.h>
__NAMESPACE_LOCAL_BEGIN
/* >> lfutex(2)
 * Provide the bottom-most API for implementing user-space synchronization on KOS
 * @param: futex_op: One of:
 *    - LFUTEX_WAKE:               (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAKE, size_t val = count)
 *    - LFUTEX_WAKEMASK:           (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAKEMASK, size_t val = count, lfutex_t mask_and, lfutex_t mask_or)
 *    - LFUTEX_NOP:                (lfutex_t *uaddr, syscall_ulong_t LFUTEX_NOP, size_t val = ignored)
 *    - LFUTEX_WAIT:               (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT, lfutex_t val = ignored, struct timespec const *timeout)
 *    - LFUTEX_WAIT_LOCK:          (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_LOCK, lfutex_t val = lock_value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE:         (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE, lfutex_t val = value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_UNTIL:         (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_UNTIL, lfutex_t val = value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_ABOVE:   (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE_ABOVE, lfutex_t val = value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_BELOW:   (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE_BELOW, lfutex_t val = value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_BITMASK: (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE_BITMASK, lfutex_t val = bitmask, struct timespec const *timeout, lfutex_t setmask)
 *    - LFUTEX_WAIT_UNTIL_BITMASK: (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_UNTIL_BITMASK, lfutex_t val = bitmask, struct timespec const *timeout, lfutex_t setmask)
 *    - LFUTEX_WAIT_WHILE_CMPXCH:  (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE_CMPXCH, lfutex_t val = oldval, struct timespec const *timeout, lfutex_t newval)
 *    - LFUTEX_WAIT_UNTIL_CMPXCH:  (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_UNTIL_CMPXCH, lfutex_t val = oldval, struct timespec const *timeout, lfutex_t newval)
 * @param: timeout: Timeout for wait operations (s.a. `LFUTEX_WAIT_FLAG_TIMEOUT_*')
 * @return: * : Depending on `futex_op'
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINVAL:    The given `futex_op' is invalid
 * @return: -1:EINTR:     A blocking futex-wait operation was interrupted
 * @return: -1:ETIMEDOUT: A blocking futex-wait operation has timed out */
#define __localdep_lfutex64 __LIBC_LOCAL_NAME(lfutex64)
#else /* ... */
#undef __local___localdep_lfutex64_defined
#endif /* !... */
#endif /* !__local___localdep_lfutex64_defined */
/* Dependency: lfutex32 from kos.futex */
#if !defined(__local___localdep_lfutex32_defined) && defined(__CRT_HAVE_lfutex)
#define __local___localdep_lfutex32_defined 1
/* >> lfutex(2)
 * Provide the bottom-most API for implementing user-space synchronization on KOS
 * @param: futex_op: One of:
 *    - LFUTEX_WAKE:               (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAKE, size_t val = count)
 *    - LFUTEX_WAKEMASK:           (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAKEMASK, size_t val = count, lfutex_t mask_and, lfutex_t mask_or)
 *    - LFUTEX_NOP:                (lfutex_t *uaddr, syscall_ulong_t LFUTEX_NOP, size_t val = ignored)
 *    - LFUTEX_WAIT:               (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT, lfutex_t val = ignored, struct timespec const *timeout)
 *    - LFUTEX_WAIT_LOCK:          (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_LOCK, lfutex_t val = lock_value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE:         (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE, lfutex_t val = value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_UNTIL:         (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_UNTIL, lfutex_t val = value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_ABOVE:   (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE_ABOVE, lfutex_t val = value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_BELOW:   (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE_BELOW, lfutex_t val = value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_BITMASK: (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE_BITMASK, lfutex_t val = bitmask, struct timespec const *timeout, lfutex_t setmask)
 *    - LFUTEX_WAIT_UNTIL_BITMASK: (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_UNTIL_BITMASK, lfutex_t val = bitmask, struct timespec const *timeout, lfutex_t setmask)
 *    - LFUTEX_WAIT_WHILE_CMPXCH:  (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE_CMPXCH, lfutex_t val = oldval, struct timespec const *timeout, lfutex_t newval)
 *    - LFUTEX_WAIT_UNTIL_CMPXCH:  (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_UNTIL_CMPXCH, lfutex_t val = oldval, struct timespec const *timeout, lfutex_t newval)
 * @param: timeout: Timeout for wait operations (s.a. `LFUTEX_WAIT_FLAG_TIMEOUT_*')
 * @return: * : Depending on `futex_op'
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINVAL:    The given `futex_op' is invalid
 * @return: -1:EINTR:     A blocking futex-wait operation was interrupted
 * @return: -1:ETIMEDOUT: A blocking futex-wait operation has timed out */
__CVREDIRECT(__ATTR_NONNULL((1)),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_lfutex32,(__uintptr_t *__uaddr, __syscall_ulong_t __futex_op, __uintptr_t __val),lfutex,(__uaddr,__futex_op,__val),__val,2,(__UINTPTR_TYPE__,__UINTPTR_TYPE__))
#endif /* !__local___localdep_lfutex32_defined && __CRT_HAVE_lfutex */
__NAMESPACE_LOCAL_END
#include <bits/timespec.h>
__NAMESPACE_LOCAL_BEGIN
/* >> lfutex(2)
 * Provide the bottom-most API for implementing user-space synchronization on KOS
 * @param: futex_op: One of:
 *    - LFUTEX_WAKE:               (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAKE, size_t val = count)
 *    - LFUTEX_WAKEMASK:           (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAKEMASK, size_t val = count, lfutex_t mask_and, lfutex_t mask_or)
 *    - LFUTEX_NOP:                (lfutex_t *uaddr, syscall_ulong_t LFUTEX_NOP, size_t val = ignored)
 *    - LFUTEX_WAIT:               (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT, lfutex_t val = ignored, struct timespec const *timeout)
 *    - LFUTEX_WAIT_LOCK:          (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_LOCK, lfutex_t val = lock_value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE:         (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE, lfutex_t val = value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_UNTIL:         (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_UNTIL, lfutex_t val = value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_ABOVE:   (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE_ABOVE, lfutex_t val = value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_BELOW:   (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE_BELOW, lfutex_t val = value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_BITMASK: (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE_BITMASK, lfutex_t val = bitmask, struct timespec const *timeout, lfutex_t setmask)
 *    - LFUTEX_WAIT_UNTIL_BITMASK: (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_UNTIL_BITMASK, lfutex_t val = bitmask, struct timespec const *timeout, lfutex_t setmask)
 *    - LFUTEX_WAIT_WHILE_CMPXCH:  (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE_CMPXCH, lfutex_t val = oldval, struct timespec const *timeout, lfutex_t newval)
 *    - LFUTEX_WAIT_UNTIL_CMPXCH:  (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_UNTIL_CMPXCH, lfutex_t val = oldval, struct timespec const *timeout, lfutex_t newval)
 * @param: timeout: Timeout for wait operations (s.a. `LFUTEX_WAIT_FLAG_TIMEOUT_*')
 * @return: * : Depending on `futex_op'
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINVAL:    The given `futex_op' is invalid
 * @return: -1:EINTR:     A blocking futex-wait operation was interrupted
 * @return: -1:ETIMEDOUT: A blocking futex-wait operation has timed out */
__LOCAL_LIBC(lfutex) __ATTR_NONNULL((1)) __SSIZE_TYPE__
__NOTHROW_RPC(__VLIBCCALL __LIBC_LOCAL_NAME(lfutex))(__uintptr_t *__uaddr, __syscall_ulong_t __futex_op, __uintptr_t __val, ...) {
#ifdef __CRT_HAVE_lfutex
	__builtin_va_list __args;
	__uintptr_t __val2;
	struct __timespec32 __tms32;
	struct __timespec64 const *__timeout;
	__builtin_va_start(__args, __val);
	__timeout = __builtin_va_arg(__args, struct __timespec64 const *);
	__val2 = __builtin_va_arg(__args, __uintptr_t);
	__builtin_va_end(__args);
	if (!__timeout || !LFUTEX_USES_TIMEOUT(__futex_op))
		return __localdep_lfutex32(__uaddr, __futex_op, __val, (struct __timespec32 *)__NULLPTR, __val2);
	__tms32.tv_sec  = (__time32_t)__timeout->tv_sec;
	__tms32.tv_nsec = __timeout->tv_nsec;
	return __localdep_lfutex32(__uaddr, __futex_op, __val, &__tms32, __val2);
#else /* __CRT_HAVE_lfutex */
	__builtin_va_list __args;
	__uintptr_t __val2;
	struct __timespec64 __tms64;
	struct __timespec32 *__timeout;
	__builtin_va_start(__args, __val);
	__timeout = __builtin_va_arg(__args, struct __timespec32 *);
	__val2 = __builtin_va_arg(__args, __uintptr_t);
	__builtin_va_end(__args);
	if (!__timeout || !LFUTEX_USES_TIMEOUT(__futex_op))
		return __localdep_lfutex64(__uaddr, __futex_op, __val, (struct __timespec64 const *)__NULLPTR, __val2);
	__tms64.tv_sec  = (__time64_t)__timeout->tv_sec;
	__tms64.tv_nsec = __timeout->tv_nsec;
	return __localdep_lfutex64(__uaddr, __futex_op, __val, &__tms64, __val2);
#endif /* !__CRT_HAVE_lfutex */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_lfutex_defined
#define __local___localdep_lfutex_defined 1
#define __localdep_lfutex __LIBC_LOCAL_NAME(lfutex)
#endif /* !__local___localdep_lfutex_defined */
#else /* __CRT_HAVE_lfutex || __CRT_HAVE_lfutex64 */
#undef __local_lfutex_defined
#endif /* !__CRT_HAVE_lfutex && !__CRT_HAVE_lfutex64 */
#endif /* !__local_lfutex_defined */
