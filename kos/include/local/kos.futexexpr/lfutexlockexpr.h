/* HASH 0x1f2d60f7 */
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
#ifndef __local_lfutexlockexpr_defined
#if (defined(__CRT_HAVE_lfutexlockexpr) || defined(__CRT_HAVE_lfutexlockexpr64))
#define __local_lfutexlockexpr_defined 1
/* Dependency: "lfutexlockexpr32" from "kos.futexexpr" */
#ifndef ____localdep_lfutexlockexpr32_defined
#define ____localdep_lfutexlockexpr32_defined 1
#if defined(__CRT_HAVE_lfutexlockexpr)
/* >> lfutexlockexpr(2)
 * Same as `lfutexlock()' is for `lfutex()', but instead implemented for `lfutexexpr()'
 * @param: ulockaddr:     Address of the futex lock to-be used / The futex on which to wait
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
__CREDIRECT(__ATTR_NONNULL((1, 3)),int,__NOTHROW_RPC,__localdep_lfutexlockexpr32,(__uintptr_t *__ulockaddr, void *__base, struct lfutexexpr const *__exprv, __SIZE_TYPE__ __exprc, struct __timespec64 const *__timeout, unsigned int __timeout_flags),lfutexlockexpr,(__ulockaddr,__base,__exprv,__exprc,__timeout,__timeout_flags))
#else /* LIBC: lfutexlockexpr */
#undef ____localdep_lfutexlockexpr32_defined
#endif /* lfutexlockexpr32... */
#endif /* !____localdep_lfutexlockexpr32_defined */

/* Dependency: "lfutexlockexpr64" from "kos.futexexpr" */
#ifndef ____localdep_lfutexlockexpr64_defined
#define ____localdep_lfutexlockexpr64_defined 1
#if defined(__CRT_HAVE_lfutexlockexpr64)
/* >> lfutexlockexpr(2)
 * Same as `lfutexlock()' is for `lfutex()', but instead implemented for `lfutexexpr()'
 * @param: ulockaddr:     Address of the futex lock to-be used / The futex on which to wait
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
__CREDIRECT(__ATTR_NONNULL((1, 3)),int,__NOTHROW_RPC,__localdep_lfutexlockexpr64,(__uintptr_t *__ulockaddr, void *__base, struct lfutexexpr const *__exprv, __SIZE_TYPE__ __exprc, struct __timespec64 const *__timeout, unsigned int __timeout_flags),lfutexlockexpr64,(__ulockaddr,__base,__exprv,__exprc,__timeout,__timeout_flags))
#elif defined(__CRT_HAVE_lfutexlockexpr) && (__SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> lfutexlockexpr(2)
 * Same as `lfutexlock()' is for `lfutex()', but instead implemented for `lfutexexpr()'
 * @param: ulockaddr:     Address of the futex lock to-be used / The futex on which to wait
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
__CREDIRECT(__ATTR_NONNULL((1, 3)),int,__NOTHROW_RPC,__localdep_lfutexlockexpr64,(__uintptr_t *__ulockaddr, void *__base, struct lfutexexpr const *__exprv, __SIZE_TYPE__ __exprc, struct __timespec64 const *__timeout, unsigned int __timeout_flags),lfutexlockexpr,(__ulockaddr,__base,__exprv,__exprc,__timeout,__timeout_flags))
#elif defined(__CRT_HAVE_lfutexlockexpr)
#include <local/kos.futexexpr/lfutexlockexpr64.h>
/* >> lfutexlockexpr(2)
 * Same as `lfutexlock()' is for `lfutex()', but instead implemented for `lfutexexpr()'
 * @param: ulockaddr:     Address of the futex lock to-be used / The futex on which to wait
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
#define __localdep_lfutexlockexpr64 (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(lfutexlockexpr64))
#else /* CUSTOM: lfutexlockexpr64 */
#undef ____localdep_lfutexlockexpr64_defined
#endif /* lfutexlockexpr64... */
#endif /* !____localdep_lfutexlockexpr64_defined */

__NAMESPACE_LOCAL_BEGIN
/* >> lfutexlockexpr(2)
 * Same as `lfutexlock()' is for `lfutex()', but instead implemented for `lfutexexpr()'
 * @param: ulockaddr:     Address of the futex lock to-be used / The futex on which to wait
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
__LOCAL_LIBC(lfutexlockexpr) __ATTR_NONNULL((1, 3)) int
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(lfutexlockexpr))(__uintptr_t *__ulockaddr,
                                                            void *__base,
                                                            struct lfutexexpr const *__exprv,
                                                            __SIZE_TYPE__ __exprc,
                                                            struct __TM_TYPE(timespec) const *__timeout,
                                                            unsigned int __timeout_flags) {
#line 232 "kos/src/libc/magic/kos.futexexpr.c"
#ifdef __CRT_HAVE_lfutexlockexpr
	struct __timespec32 __tms32;
	if (!__timeout)
		return __localdep_lfutexlockexpr32(__ulockaddr, __base, __exprv, __exprc, __NULLPTR, 0);
	__tms32.tv_sec  = (__time32_t)__timeout->tv_sec;
	__tms32.tv_nsec = __timeout->tv_nsec;
	return __localdep_lfutexlockexpr32(__ulockaddr, __base, __exprv, __exprc, &__tms32, __timeout_flags);
#else /* __CRT_HAVE_lfutexlockexpr */
	struct __timespec64 __tms64;
	if (!__timeout)
		return __localdep_lfutexlockexpr64(__ulockaddr, __base, __exprv, __exprc, __NULLPTR, 0);
	__tms64.tv_sec  = (__time64_t)__timeout->tv_sec;
	__tms64.tv_nsec = __timeout->tv_nsec;
	return __localdep_lfutexlockexpr64(__ulockaddr, __base, __exprv, __exprc, &__tms64, __timeout_flags);
#endif /* !__CRT_HAVE_lfutexlockexpr */
}
__NAMESPACE_LOCAL_END
#endif /* (defined(__CRT_HAVE_lfutexlockexpr) || defined(__CRT_HAVE_lfutexlockexpr64)) */
#endif /* !__local_lfutexlockexpr_defined */
