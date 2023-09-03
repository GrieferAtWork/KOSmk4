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
#ifndef GUARD_LIBC_USER_KOS_FUTEXEXPR_C
#define GUARD_LIBC_USER_KOS_FUTEXEXPR_C 1

#include "../api.h"
/**/

#include <kos/futexexpr.h>
#include <kos/syscalls.h>

#include "kos.futexexpr.h"

DECL_BEGIN

/*[[[head:libc_lfutexexpr,hash:CRC-32=0x91eb703e]]]*/
/* >> lfutexexpr(2), lfutexexpr64(2)
 * The lfutexexpr(2) system call can be used to specify arbitrarily complex
 * expressions that must atomically (in relation to other futex operations)
 * hold true before the scheduler will suspend the calling thread.
 * @param: ulockaddr:     The futex on which to wait
 * @param: base:          Base pointer added to the `fe_offset' fields of given expressions
 * @param: expr:          Vector of expressions for which to check, terminated by `LFUTEX_EXPREND'
 * @param: timeout:       Timeout for wait operations (s.a. `LFUTEX_WAIT_FLAG_TIMEOUT_*')
 * @param: timeout_flags: Set of `LFUTEX_WAIT_FLAG_TIMEOUT_*'
 * @return: * : The first  non-zero  return value  from  executing  all of  the  given  `expr'
 *              in order (s.a. the documentations of the individual `LFUTEX_WAIT_*'  functions
 *              to see their  possible return  values, which are  always `0'  when they  would
 *              perform a wait  operation, and usually  `1' otherwise) or  `0' if the  calling
 *              thread had to perform a wait operation, at which point this function returning
 *              that value means that you've once again been re-awoken.
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINVAL:    One of the given commands is invalid, or `expr[0].fe_condition == LFUTEX_EXPREND'
 * @return: -1:EINTR:     A blocking futex-wait operation was interrupted
 * @return: -1:ETIMEDOUT: A blocking futex-wait operation has timed out */
INTERN ATTR_SECTION(".text.crt.sched.futexlockexpr") ATTR_IN(3) ATTR_IN_OPT(4) NONNULL((1)) int
NOTHROW_RPC(LIBCCALL libc_lfutexexpr)(lfutex_t *ulockaddr,
                                      void *base,
                                      struct lfutexexpr const *expr,
                                      struct timespec const *timeout,
                                      unsigned int timeout_flags)
/*[[[body:libc_lfutexexpr]]]*/
{
	errno_t error;
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
	error = sys_lfutexexpr(ulockaddr, base, expr, timeout, timeout_flags);
#else /* __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */
	struct timespec64 tm64;
	if (timeout) {
		tm64.tv_sec  = (time64_t)timeout->tv_sec;
		tm64.tv_nsec = timeout->tv_nsec;
		timeout = (struct timespec const *)&tm64;
	}
	error = sys_lfutexexpr(ulockaddr, base, expr,
	                       (struct timespec64 const *)timeout,
	                       timeout_flags);
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
	return libc_seterrno_syserr(error);
}
/*[[[end:libc_lfutexexpr]]]*/

/*[[[head:libc_lfutexexpr64,hash:CRC-32=0x970c5d2d]]]*/
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_lfutexexpr64, libc_lfutexexpr);
#else /* MAGIC:alias */
/* >> lfutexexpr(2), lfutexexpr64(2)
 * The lfutexexpr(2) system call can be used to specify arbitrarily complex
 * expressions that must atomically (in relation to other futex operations)
 * hold true before the scheduler will suspend the calling thread.
 * @param: ulockaddr:     The futex on which to wait
 * @param: base:          Base pointer added to the `fe_offset' fields of given expressions
 * @param: expr:          Vector of expressions for which to check, terminated by `LFUTEX_EXPREND'
 * @param: timeout:       Timeout for wait operations (s.a. `LFUTEX_WAIT_FLAG_TIMEOUT_*')
 * @param: timeout_flags: Set of `LFUTEX_WAIT_FLAG_TIMEOUT_*'
 * @return: * : The first  non-zero  return value  from  executing  all of  the  given  `expr'
 *              in order (s.a. the documentations of the individual `LFUTEX_WAIT_*'  functions
 *              to see their  possible return  values, which are  always `0'  when they  would
 *              perform a wait  operation, and usually  `1' otherwise) or  `0' if the  calling
 *              thread had to perform a wait operation, at which point this function returning
 *              that value means that you've once again been re-awoken.
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINVAL:    One of the given commands is invalid, or `expr[0].fe_condition == LFUTEX_EXPREND'
 * @return: -1:EINTR:     A blocking futex-wait operation was interrupted
 * @return: -1:ETIMEDOUT: A blocking futex-wait operation has timed out */
INTERN ATTR_SECTION(".text.crt.sched.futexlockexpr") ATTR_IN(3) ATTR_IN_OPT(4) NONNULL((1)) int
NOTHROW_RPC(LIBCCALL libc_lfutexexpr64)(lfutex_t *ulockaddr,
                                        void *base,
                                        struct lfutexexpr const *expr,
                                        struct timespec64 const *timeout,
                                        unsigned int timeout_flags)
/*[[[body:libc_lfutexexpr64]]]*/
{
	errno_t error;
	error = sys_lfutexexpr(ulockaddr, base, expr, timeout, timeout_flags);
	return libc_seterrno_syserr(error);
}
#endif /* MAGIC:alias */
/*[[[end:libc_lfutexexpr64]]]*/


/*[[[skip:libc_LFutexExpr]]]*/
/*[[[skip:libc_LFutexExpr64]]]*/

#if __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__
DEFINE_PUBLIC_ALIAS(LFutexExpr, libc_LFutexExpr);
INTERN ATTR_SECTION(".text.crt.sched.futexlockexpr") NONNULL((1, 4)) int LIBCCALL
libc_LFutexExpr(lfutex_t *ulockaddr, void *base, struct lfutexexpr const *expr,
                struct timespec const *timeout, unsigned int timeout_flags) THROWS(...) {
	struct timespec64 tm64;
	if (timeout) {
		tm64.tv_sec  = (time64_t)timeout->tv_sec;
		tm64.tv_nsec = timeout->tv_nsec;
		timeout = (struct timespec const *)&tm64;
	}
	return sys_Xlfutexexpr(ulockaddr, base, expr,
	                       (struct timespec64 const *)timeout,
	                       timeout_flags);
}
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */


/*[[[start:exports,hash:CRC-32=0x7134ca14]]]*/
DEFINE_PUBLIC_ALIAS(lfutexexpr, libc_lfutexexpr);
#include <bits/types.h>
#if __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__
DEFINE_PUBLIC_ALIAS(lfutexexpr64, libc_lfutexexpr64);
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_KOS_FUTEXEXPR_C */
