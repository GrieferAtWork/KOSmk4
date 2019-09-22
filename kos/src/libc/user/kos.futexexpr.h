/* HASH CRC-32:0x9a157b03 */
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
#ifndef GUARD_LIBC_USER_KOS_FUTEXEXPR_H
#define GUARD_LIBC_USER_KOS_FUTEXEXPR_H 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include <kos/futexexpr.h>

DECL_BEGIN

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
INTDEF NONNULL((1, 3)) int NOTHROW_RPC(LIBCCALL libc_lfutexexpr)(lfutex_t *uaddr, void *base, struct lfutexexpr const *exprv, size_t exprc, struct timespec const *timeout, unsigned int timeout_flags);
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
INTDEF NONNULL((1, 3)) int NOTHROW_RPC(LIBCCALL libc_lfutexlockexpr)(lfutex_t *ulockaddr, void *base, struct lfutexexpr const *exprv, size_t exprc, struct timespec const *timeout, unsigned int timeout_flags);
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
INTDEF NONNULL((1, 3)) int NOTHROW_RPC(LIBCCALL libc_lfutexexpr64)(lfutex_t *uaddr, void *base, struct lfutexexpr const *exprv, size_t exprc, struct timespec64 const *timeout, unsigned int timeout_flags);
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
INTDEF NONNULL((1, 3)) int NOTHROW_RPC(LIBCCALL libc_lfutexlockexpr64)(lfutex_t *ulockaddr, void *base, struct lfutexexpr const *exprv, size_t exprc, struct timespec64 const *timeout, unsigned int timeout_flags);

DECL_END

#endif /* !GUARD_LIBC_USER_KOS_FUTEXEXPR_H */
