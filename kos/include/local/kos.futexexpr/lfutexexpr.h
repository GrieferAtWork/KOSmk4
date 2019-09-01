/* HASH 0x74786393 */
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
#ifndef __local_lfutexexpr_defined
#if (defined(__CRT_HAVE_lfutexexpr) || defined(__CRT_HAVE_lfutexexpr64))
#define __local_lfutexexpr_defined 1
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

/* Dependency: "lfutexexpr64" from "kos.futexexpr" */
#ifndef ____localdep_lfutexexpr64_defined
#define ____localdep_lfutexexpr64_defined 1
#if defined(__CRT_HAVE_lfutexexpr64)
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
__CREDIRECT(__ATTR_NONNULL((1, 3)),int,__NOTHROW_RPC,__localdep_lfutexexpr64,(__uintptr_t *__uaddr, void *__base, struct lfutexexpr const *__exprv, __SIZE_TYPE__ __exprc, struct __timespec64 const *__timeout, unsigned int __timeout_flags),lfutexexpr64,(__uaddr,__base,__exprv,__exprc,__timeout,__timeout_flags))
#elif defined(__CRT_HAVE_lfutexexpr) && (__SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
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
__CREDIRECT(__ATTR_NONNULL((1, 3)),int,__NOTHROW_RPC,__localdep_lfutexexpr64,(__uintptr_t *__uaddr, void *__base, struct lfutexexpr const *__exprv, __SIZE_TYPE__ __exprc, struct __timespec64 const *__timeout, unsigned int __timeout_flags),lfutexexpr,(__uaddr,__base,__exprv,__exprc,__timeout,__timeout_flags))
#elif defined(__CRT_HAVE_lfutexexpr)
#include <local/kos.futexexpr/lfutexexpr64.h>
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
#define __localdep_lfutexexpr64 (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(lfutexexpr64))
#else /* CUSTOM: lfutexexpr64 */
#undef ____localdep_lfutexexpr64_defined
#endif /* lfutexexpr64... */
#endif /* !____localdep_lfutexexpr64_defined */

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
__LOCAL_LIBC(lfutexexpr) __ATTR_NONNULL((1, 3)) int
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(lfutexexpr))(__uintptr_t *__uaddr,
                                                        void *__base,
                                                        struct lfutexexpr const *__exprv,
                                                        __SIZE_TYPE__ __exprc,
                                                        struct __TM_TYPE(timespec) const *__timeout,
                                                        unsigned int __timeout_flags) {
#line 196 "kos/src/libc/magic/kos.futexexpr.c"
#ifdef __CRT_HAVE_lfutexexpr
	struct __timespec32 __tms32;
	if (!__timeout)
		return __localdep_lfutexexpr32(__uaddr, __base, __exprv, __exprc, __NULLPTR, 0);
	__tms32.tv_sec  = (__time32_t)__timeout->tv_sec;
	__tms32.tv_nsec = __timeout->tv_nsec;
	return __localdep_lfutexexpr32(__uaddr, __base, __exprv, __exprc, &__tms32, __timeout_flags);
#else /* __CRT_HAVE_lfutexexpr */
	struct __timespec64 __tms64;
	if (!__timeout)
		return __localdep_lfutexexpr64(__uaddr, __base, __exprv, __exprc, __NULLPTR, 0);
	__tms64.tv_sec  = (__time64_t)__timeout->tv_sec;
	__tms64.tv_nsec = __timeout->tv_nsec;
	return __localdep_lfutexexpr64(__uaddr, __base, __exprv, __exprc, &__tms64, __timeout_flags);
#endif /* !__CRT_HAVE_lfutexexpr */
}
__NAMESPACE_LOCAL_END
#endif /* (defined(__CRT_HAVE_lfutexexpr) || defined(__CRT_HAVE_lfutexexpr64)) */
#endif /* !__local_lfutexexpr_defined */
