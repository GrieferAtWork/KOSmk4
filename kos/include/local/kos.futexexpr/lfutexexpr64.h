/* HASH 0x880e12b4 */
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
#ifndef __local_lfutexexpr64_defined
#if defined(__CRT_HAVE_lfutexexpr)
#define __local_lfutexexpr64_defined 1
/* Dependency: "lfutexexpr32" from "kos.futexexpr" */
#ifndef ____localdep_lfutexexpr32_defined
#define ____localdep_lfutexexpr32_defined 1
#if defined(__CRT_HAVE_lfutexexpr)
/* >> lfutexexpr(2)
 * High-level wrapper around the lfutexexpr system call
 * The lfutexexpr() system call can be used to specify arbitrarily complex
 * expressions that must atomically (in relation to other futex operations)
 * hold true before the scheduler will suspend the calling thread.
 * @param: uaddr:         The futex on which to wait
 * @param: base:          Base pointer added to the `fe_offset' fields of given expressions
 * @param: exprv:         Vector of expressions for which to check
 * @param: exprc:         Number of expressions given in `exprv'
 * @param: timeout:       Timeout for wait operations (s.a. `LFUTEX_WAIT_FLAG_TIMEOUT_*')
 * @param: timeout_flags: Set of `LFUTEX_WAIT_FLAG_TIMEOUT_*'
 * @return: * : Depending on `command'
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINVAL:    One of the given commands is invalid
 * @return: -1:EINTR:     A blocking futex-wait operation was interrupted
 * @return: -1:ETIMEDOUT: A blocking futex-wait operation has timed out */
__CREDIRECT(__ATTR_NONNULL((1, 3)),int,__NOTHROW_RPC,__localdep_lfutexexpr32,(__uintptr_t *__uaddr, void *__base, struct lfutexexpr const *__exprv, __SIZE_TYPE__ __exprc, struct __timespec64 const *__timeout, unsigned int __timeout_flags),lfutexexpr,(__uaddr,__base,__exprv,__exprc,__timeout,__timeout_flags))
#else /* LIBC: lfutexexpr */
#undef ____localdep_lfutexexpr32_defined
#endif /* lfutexexpr32... */
#endif /* !____localdep_lfutexexpr32_defined */

__NAMESPACE_LOCAL_BEGIN
/* >> lfutexexpr(2)
 * High-level wrapper around the lfutexexpr system call
 * The lfutexexpr() system call can be used to specify arbitrarily complex
 * expressions that must atomically (in relation to other futex operations)
 * hold true before the scheduler will suspend the calling thread.
 * @param: uaddr:         The futex on which to wait
 * @param: base:          Base pointer added to the `fe_offset' fields of given expressions
 * @param: exprv:         Vector of expressions for which to check
 * @param: exprc:         Number of expressions given in `exprv'
 * @param: timeout:       Timeout for wait operations (s.a. `LFUTEX_WAIT_FLAG_TIMEOUT_*')
 * @param: timeout_flags: Set of `LFUTEX_WAIT_FLAG_TIMEOUT_*'
 * @return: * : Depending on `command'
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINVAL:    One of the given commands is invalid
 * @return: -1:EINTR:     A blocking futex-wait operation was interrupted
 * @return: -1:ETIMEDOUT: A blocking futex-wait operation has timed out */
__LOCAL_LIBC(lfutexexpr64) __ATTR_NONNULL((1, 3)) int
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(lfutexexpr64))(__uintptr_t *__uaddr,
                                                          void *__base,
                                                          struct lfutexexpr const *__exprv,
                                                          __SIZE_TYPE__ __exprc,
                                                          struct __timespec64 const *__timeout,
                                                          unsigned int __timeout_flags) {
#line 255 "kos/src/libc/magic/kos.futexexpr.c"
	struct __timespec32 __tms32;
	if (!__timeout)
		return __localdep_lfutexexpr32(__uaddr, __base, __exprv, __exprc, __NULLPTR, 0);
	__tms32.tv_sec  = (__time32_t)__timeout->tv_sec;
	__tms32.tv_nsec = __timeout->tv_nsec;
	return __localdep_lfutexexpr32(__uaddr, __base, __exprv, __exprc, &__tms32, __timeout_flags);
}
__NAMESPACE_LOCAL_END
#endif /* defined(__CRT_HAVE_lfutexexpr) */
#endif /* !__local_lfutexexpr64_defined */
