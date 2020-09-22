/* HASH CRC-32:0x829dd1f */
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
#ifndef __local_lfutexlockexpr_defined
#define __local_lfutexlockexpr_defined 1
#include <__crt.h>
#if defined(__CRT_HAVE_lfutexlockexpr64) || defined(__CRT_HAVE_lfutexlockexpr)
#include <bits/types.h>
#include <bits/os/timespec.h>
#include <kos/bits/futex-expr.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: lfutexlockexpr32 from kos.futexexpr */
#if !defined(__local___localdep_lfutexlockexpr32_defined) && defined(__CRT_HAVE_lfutexlockexpr)
#define __local___localdep_lfutexlockexpr32_defined 1
/* >> lfutexlockexpr(2)
 * A function that is similar to `lfutexexpr()', but allows for the use of one central
 * locking futex that is used for waiting and may be distinct from any other given futex
 * object pointer.
 * Notes:
 *   - This function only has the calling thread wait on a single futex `ulockaddr',
 *     rather than having it wait on an arbitrary number of futexes, as would be the case when
 *     the `lfutexexpr()' function is used.
 *   - For more precise control over waiting on futex objects, as well as waiting on futexes
 *     in conjunction with waiting on other things such as files, see the documentation on
 *     this topic (lfutex() and select()) at the top of <kos/futex.h>
 * @param: ulockaddr:     Address of the futex lock to-be used / The futex on which to wait
 * @param: base:          Base pointer added to the `fe_offset' fields of given expressions
 * @param: exprv:         Vector of expressions for which to check
 * @param: exprc:         Number of expressions given in `exprv'
 * @param: timeout:       Timeout for wait operations (s.a. `LFUTEX_WAIT_FLAG_TIMEOUT_*')
 * @param: timeout_flags: Set of `LFUTEX_WAIT_FLAG_TIMEOUT_*'
 * @return: * : The first non-zero return value from executing all of the given `exprv'
 *              in order (s.a. the documentations of the individual `LFUTEX_WAIT_*' functions
 *              to see their possible return values, which are always `0' when they would
 *              perform a wait operation, and usually `1' otherwise) or `0' if the calling
 *              thread had to perform a wait operation, at which point this function returning
 *              that value means that you've once again been re-awoken.
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINVAL:    One of the given commands is invalid, or `exprc' was `0'
 * @return: -1:EINTR:     A blocking futex-wait operation was interrupted
 * @return: -1:ETIMEDOUT: A blocking futex-wait operation has timed out */
__CREDIRECT(__ATTR_NONNULL((1, 4)),int,__NOTHROW_RPC,__localdep_lfutexlockexpr32,(__uintptr_t *__ulockaddr, void *__base, __SIZE_TYPE__ __exprc, struct lfutexexpr const *__exprv, struct __timespec64 const *__timeout, unsigned int __timeout_flags),lfutexlockexpr,(__ulockaddr,__base,__exprc,__exprv,__timeout,__timeout_flags))
#endif /* !__local___localdep_lfutexlockexpr32_defined && __CRT_HAVE_lfutexlockexpr */
/* Dependency: lfutexlockexpr64 from kos.futexexpr */
#ifndef __local___localdep_lfutexlockexpr64_defined
#define __local___localdep_lfutexlockexpr64_defined 1
#ifdef __CRT_HAVE_lfutexlockexpr64
/* >> lfutexlockexpr(2)
 * A function that is similar to `lfutexexpr()', but allows for the use of one central
 * locking futex that is used for waiting and may be distinct from any other given futex
 * object pointer.
 * Notes:
 *   - This function only has the calling thread wait on a single futex `ulockaddr',
 *     rather than having it wait on an arbitrary number of futexes, as would be the case when
 *     the `lfutexexpr()' function is used.
 *   - For more precise control over waiting on futex objects, as well as waiting on futexes
 *     in conjunction with waiting on other things such as files, see the documentation on
 *     this topic (lfutex() and select()) at the top of <kos/futex.h>
 * @param: ulockaddr:     Address of the futex lock to-be used / The futex on which to wait
 * @param: base:          Base pointer added to the `fe_offset' fields of given expressions
 * @param: exprv:         Vector of expressions for which to check
 * @param: exprc:         Number of expressions given in `exprv'
 * @param: timeout:       Timeout for wait operations (s.a. `LFUTEX_WAIT_FLAG_TIMEOUT_*')
 * @param: timeout_flags: Set of `LFUTEX_WAIT_FLAG_TIMEOUT_*'
 * @return: * : The first non-zero return value from executing all of the given `exprv'
 *              in order (s.a. the documentations of the individual `LFUTEX_WAIT_*' functions
 *              to see their possible return values, which are always `0' when they would
 *              perform a wait operation, and usually `1' otherwise) or `0' if the calling
 *              thread had to perform a wait operation, at which point this function returning
 *              that value means that you've once again been re-awoken.
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINVAL:    One of the given commands is invalid, or `exprc' was `0'
 * @return: -1:EINTR:     A blocking futex-wait operation was interrupted
 * @return: -1:ETIMEDOUT: A blocking futex-wait operation has timed out */
__CREDIRECT(__ATTR_NONNULL((1, 4)),int,__NOTHROW_RPC,__localdep_lfutexlockexpr64,(__uintptr_t *__ulockaddr, void *__base, __SIZE_TYPE__ __exprc, struct lfutexexpr const *__exprv, struct __timespec64 const *__timeout, unsigned int __timeout_flags),lfutexlockexpr64,(__ulockaddr,__base,__exprc,__exprv,__timeout,__timeout_flags))
#elif defined(__CRT_HAVE_lfutexlockexpr) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> lfutexlockexpr(2)
 * A function that is similar to `lfutexexpr()', but allows for the use of one central
 * locking futex that is used for waiting and may be distinct from any other given futex
 * object pointer.
 * Notes:
 *   - This function only has the calling thread wait on a single futex `ulockaddr',
 *     rather than having it wait on an arbitrary number of futexes, as would be the case when
 *     the `lfutexexpr()' function is used.
 *   - For more precise control over waiting on futex objects, as well as waiting on futexes
 *     in conjunction with waiting on other things such as files, see the documentation on
 *     this topic (lfutex() and select()) at the top of <kos/futex.h>
 * @param: ulockaddr:     Address of the futex lock to-be used / The futex on which to wait
 * @param: base:          Base pointer added to the `fe_offset' fields of given expressions
 * @param: exprv:         Vector of expressions for which to check
 * @param: exprc:         Number of expressions given in `exprv'
 * @param: timeout:       Timeout for wait operations (s.a. `LFUTEX_WAIT_FLAG_TIMEOUT_*')
 * @param: timeout_flags: Set of `LFUTEX_WAIT_FLAG_TIMEOUT_*'
 * @return: * : The first non-zero return value from executing all of the given `exprv'
 *              in order (s.a. the documentations of the individual `LFUTEX_WAIT_*' functions
 *              to see their possible return values, which are always `0' when they would
 *              perform a wait operation, and usually `1' otherwise) or `0' if the calling
 *              thread had to perform a wait operation, at which point this function returning
 *              that value means that you've once again been re-awoken.
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINVAL:    One of the given commands is invalid, or `exprc' was `0'
 * @return: -1:EINTR:     A blocking futex-wait operation was interrupted
 * @return: -1:ETIMEDOUT: A blocking futex-wait operation has timed out */
__CREDIRECT(__ATTR_NONNULL((1, 4)),int,__NOTHROW_RPC,__localdep_lfutexlockexpr64,(__uintptr_t *__ulockaddr, void *__base, __SIZE_TYPE__ __exprc, struct lfutexexpr const *__exprv, struct __timespec64 const *__timeout, unsigned int __timeout_flags),lfutexlockexpr,(__ulockaddr,__base,__exprc,__exprv,__timeout,__timeout_flags))
#elif defined(__CRT_HAVE_lfutexlockexpr)
__NAMESPACE_LOCAL_END
#include <libc/local/kos.futexexpr/lfutexlockexpr64.h>
__NAMESPACE_LOCAL_BEGIN
/* >> lfutexlockexpr(2)
 * A function that is similar to `lfutexexpr()', but allows for the use of one central
 * locking futex that is used for waiting and may be distinct from any other given futex
 * object pointer.
 * Notes:
 *   - This function only has the calling thread wait on a single futex `ulockaddr',
 *     rather than having it wait on an arbitrary number of futexes, as would be the case when
 *     the `lfutexexpr()' function is used.
 *   - For more precise control over waiting on futex objects, as well as waiting on futexes
 *     in conjunction with waiting on other things such as files, see the documentation on
 *     this topic (lfutex() and select()) at the top of <kos/futex.h>
 * @param: ulockaddr:     Address of the futex lock to-be used / The futex on which to wait
 * @param: base:          Base pointer added to the `fe_offset' fields of given expressions
 * @param: exprv:         Vector of expressions for which to check
 * @param: exprc:         Number of expressions given in `exprv'
 * @param: timeout:       Timeout for wait operations (s.a. `LFUTEX_WAIT_FLAG_TIMEOUT_*')
 * @param: timeout_flags: Set of `LFUTEX_WAIT_FLAG_TIMEOUT_*'
 * @return: * : The first non-zero return value from executing all of the given `exprv'
 *              in order (s.a. the documentations of the individual `LFUTEX_WAIT_*' functions
 *              to see their possible return values, which are always `0' when they would
 *              perform a wait operation, and usually `1' otherwise) or `0' if the calling
 *              thread had to perform a wait operation, at which point this function returning
 *              that value means that you've once again been re-awoken.
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINVAL:    One of the given commands is invalid, or `exprc' was `0'
 * @return: -1:EINTR:     A blocking futex-wait operation was interrupted
 * @return: -1:ETIMEDOUT: A blocking futex-wait operation has timed out */
#define __localdep_lfutexlockexpr64 __LIBC_LOCAL_NAME(lfutexlockexpr64)
#else /* ... */
#undef __local___localdep_lfutexlockexpr64_defined
#endif /* !... */
#endif /* !__local___localdep_lfutexlockexpr64_defined */
/* >> lfutexlockexpr(2)
 * A function that is similar to `lfutexexpr()', but allows for the use of one central
 * locking futex that is used for waiting and may be distinct from any other given futex
 * object pointer.
 * Notes:
 *   - This function only has the calling thread wait on a single futex `ulockaddr',
 *     rather than having it wait on an arbitrary number of futexes, as would be the case when
 *     the `lfutexexpr()' function is used.
 *   - For more precise control over waiting on futex objects, as well as waiting on futexes
 *     in conjunction with waiting on other things such as files, see the documentation on
 *     this topic (lfutex() and select()) at the top of <kos/futex.h>
 * @param: ulockaddr:     Address of the futex lock to-be used / The futex on which to wait
 * @param: base:          Base pointer added to the `fe_offset' fields of given expressions
 * @param: exprv:         Vector of expressions for which to check
 * @param: exprc:         Number of expressions given in `exprv'
 * @param: timeout:       Timeout for wait operations (s.a. `LFUTEX_WAIT_FLAG_TIMEOUT_*')
 * @param: timeout_flags: Set of `LFUTEX_WAIT_FLAG_TIMEOUT_*'
 * @return: * : The first non-zero return value from executing all of the given `exprv'
 *              in order (s.a. the documentations of the individual `LFUTEX_WAIT_*' functions
 *              to see their possible return values, which are always `0' when they would
 *              perform a wait operation, and usually `1' otherwise) or `0' if the calling
 *              thread had to perform a wait operation, at which point this function returning
 *              that value means that you've once again been re-awoken.
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINVAL:    One of the given commands is invalid, or `exprc' was `0'
 * @return: -1:EINTR:     A blocking futex-wait operation was interrupted
 * @return: -1:ETIMEDOUT: A blocking futex-wait operation has timed out */
__LOCAL_LIBC(lfutexlockexpr) __ATTR_NONNULL((1, 4)) int
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(lfutexlockexpr))(__uintptr_t *__ulockaddr, void *__base, __SIZE_TYPE__ __exprc, struct lfutexexpr const *__exprv, struct timespec const *__timeout, unsigned int __timeout_flags) {
#ifdef __CRT_HAVE_lfutexlockexpr
	struct __timespec32 __tms32;
	if (!__timeout)
		return __localdep_lfutexlockexpr32(__ulockaddr, __base, __exprc, __exprv, __NULLPTR, 0);
	__tms32.tv_sec  = (__time32_t)__timeout->tv_sec;
	__tms32.tv_nsec = __timeout->tv_nsec;
	return __localdep_lfutexlockexpr32(__ulockaddr, __base, __exprc, __exprv, &__tms32, __timeout_flags);
#else /* __CRT_HAVE_lfutexlockexpr */
	struct __timespec64 __tms64;
	if (!__timeout)
		return __localdep_lfutexlockexpr64(__ulockaddr, __base, __exprc, __exprv, __NULLPTR, 0);
	__tms64.tv_sec  = (__time64_t)__timeout->tv_sec;
	__tms64.tv_nsec = __timeout->tv_nsec;
	return __localdep_lfutexlockexpr64(__ulockaddr, __base, __exprc, __exprv, &__tms64, __timeout_flags);
#endif /* !__CRT_HAVE_lfutexlockexpr */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_lfutexlockexpr_defined
#define __local___localdep_lfutexlockexpr_defined 1
#define __localdep_lfutexlockexpr __LIBC_LOCAL_NAME(lfutexlockexpr)
#endif /* !__local___localdep_lfutexlockexpr_defined */
#else /* __CRT_HAVE_lfutexlockexpr64 || __CRT_HAVE_lfutexlockexpr */
#undef __local_lfutexlockexpr_defined
#endif /* !__CRT_HAVE_lfutexlockexpr64 && !__CRT_HAVE_lfutexlockexpr */
#endif /* !__local_lfutexlockexpr_defined */
