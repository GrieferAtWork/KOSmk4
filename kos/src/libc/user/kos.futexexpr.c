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
#ifndef GUARD_LIBC_USER_KOS_FUTEXEXPR_C
#define GUARD_LIBC_USER_KOS_FUTEXEXPR_C 1

#include "../api.h"
#include "kos.futexexpr.h"
#include <kos/futexexpr.h>
#include <kos/syscalls.h>

DECL_BEGIN





/*[[[start:implementation]]]*/

/*[[[head:lfutexexpr,hash:CRC-32=0x3dc7a605]]]*/
/* >> lfutexexpr(2)
 * The lfutexexpr() system call can be used to specify arbitrarily complex
 * expressions that must atomically (in relation to other futex operations)
 * hold true before the scheduler will suspend the calling thread, as well as
 * have the calling thread wait for any number of futex objects associated with
 * any address that is checked as part of the expression. (s.a. `lfutex()')
 * Notes:
 *   - This is the only futex function that can be used to wait on multiple futex
 *     objects (i.e. resume execution when `LFUTEX_WAKE' is called on _any_ of them)
 *   - For more precise control over waiting on futex objects, as well as waiting on
 *     futexes in conjunction with waiting on other things such as files, see the
 *     documentation on this topic (lfutex() and select()) at the top of <kos/futex.h>
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
INTERN NONNULL((3))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.futexexpr.lfutexexpr") int
NOTHROW_RPC(LIBCCALL libc_lfutexexpr)(void *base,
                                      size_t exprc,
                                      struct lfutexexpr const *exprv,
                                      struct timespec const *timeout,
                                      unsigned int timeout_flags)
/*[[[body:lfutexexpr]]]*/
{
	struct timespec64 tm64;
	if (!timeout) {
		return lfutexexpr64(base,
		                    exprc,
		                    exprv,
		                    NULL,
		                    timeout_flags);
	}
	tm64.tv_sec  = (time64_t)timeout->tv_sec;
	tm64.tv_nsec = timeout->tv_nsec;
	return lfutexexpr64(base,
	                    exprc,
	                    exprv,
	                    &tm64,
	                    timeout_flags);
}
/*[[[end:lfutexexpr]]]*/

/*[[[head:lfutexlockexpr,hash:CRC-32=0xae634c1e]]]*/
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
INTERN NONNULL((1, 4))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.futexlockexpr.lfutexlockexpr") int
NOTHROW_RPC(LIBCCALL libc_lfutexlockexpr)(lfutex_t *ulockaddr,
                                          void *base,
                                          size_t exprc,
                                          struct lfutexexpr const *exprv,
                                          struct timespec const *timeout,
                                          unsigned int timeout_flags)
/*[[[body:lfutexlockexpr]]]*/
{
	struct timespec64 tm64;
	if (!timeout) {
		return lfutexlockexpr64(ulockaddr,
		                        base,
		                        exprc,
		                        exprv,
		                        NULL,
		                        timeout_flags);
	}
	tm64.tv_sec  = (time64_t)timeout->tv_sec;
	tm64.tv_nsec = timeout->tv_nsec;
	return lfutexlockexpr64(ulockaddr,
	                        base,
	                        exprc,
	                        exprv,
	                        &tm64,
	                        timeout_flags);
}
/*[[[end:lfutexlockexpr]]]*/

/*[[[head:lfutexexpr64,hash:CRC-32=0xb7c4fc5b]]]*/
/* >> lfutexexpr(2)
 * The lfutexexpr() system call can be used to specify arbitrarily complex
 * expressions that must atomically (in relation to other futex operations)
 * hold true before the scheduler will suspend the calling thread, as well as
 * have the calling thread wait for any number of futex objects associated with
 * any address that is checked as part of the expression. (s.a. `lfutex()')
 * Notes:
 *   - This is the only futex function that can be used to wait on multiple futex
 *     objects (i.e. resume execution when `LFUTEX_WAKE' is called on _any_ of them)
 *   - For more precise control over waiting on futex objects, as well as waiting on
 *     futexes in conjunction with waiting on other things such as files, see the
 *     documentation on this topic (lfutex() and select()) at the top of <kos/futex.h>
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
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_lfutexexpr64, libc_lfutexexpr);
#else
INTERN NONNULL((3))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.futexexpr.lfutexexpr64") int
NOTHROW_RPC(LIBCCALL libc_lfutexexpr64)(void *base,
                                        size_t exprc,
                                        struct lfutexexpr const *exprv,
                                        struct timespec64 const *timeout,
                                        unsigned int timeout_flags)
/*[[[body:lfutexexpr64]]]*/
{
	errno_t error;
	error = sys_lfutexexpr(base,
	                       exprc,
	                       exprv,
	                       timeout,
	                       (syscall_ulong_t)timeout_flags);
	return libc_seterrno_syserr(error);
}
#endif /* MAGIC:alias */
/*[[[end:lfutexexpr64]]]*/

/*[[[head:lfutexlockexpr64,hash:CRC-32=0x2359daf0]]]*/
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
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_lfutexlockexpr64, libc_lfutexlockexpr);
#else
INTERN NONNULL((1, 4))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.futexlockexpr.lfutexlockexpr64") int
NOTHROW_RPC(LIBCCALL libc_lfutexlockexpr64)(lfutex_t *ulockaddr,
                                            void *base,
                                            size_t exprc,
                                            struct lfutexexpr const *exprv,
                                            struct timespec64 const *timeout,
                                            unsigned int timeout_flags)
/*[[[body:lfutexlockexpr64]]]*/
{
	errno_t error;
	error = sys_lfutexlockexpr(ulockaddr,
	                           base,
	                           exprc,
	                           exprv,
	                           timeout,
	                           (syscall_ulong_t)timeout_flags);
	return libc_seterrno_syserr(error);
}
#endif /* MAGIC:alias */
/*[[[end:lfutexlockexpr64]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:CRC-32=0xaca9cef5]]]*/
DEFINE_PUBLIC_WEAK_ALIAS(lfutexexpr, libc_lfutexexpr);
DEFINE_PUBLIC_WEAK_ALIAS(lfutexlockexpr, libc_lfutexlockexpr);
DEFINE_PUBLIC_WEAK_ALIAS(lfutexexpr64, libc_lfutexexpr64);
DEFINE_PUBLIC_WEAK_ALIAS(lfutexlockexpr64, libc_lfutexlockexpr64);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_KOS_FUTEXEXPR_C */
