/* HASH CRC-32:0x696b378 */
/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_AUTO_KOS_FUTEXEXPR_H
#define GUARD_LIBC_AUTO_KOS_FUTEXEXPR_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <kos/futexexpr.h>

DECL_BEGIN

#ifndef __KERNEL__
/* >> LFutexExprI(2), LFutexExprI64(2)
 * Same as `LFutexExpr()', but implicitly handle `E_INTERRUPT' exceptions by re-starting the system call.
 * @return: * :  The first  non-zero  return value  from  executing  all of  the  given  `expr'
 *               in order (s.a. the documentations of the individual `LFUTEX_WAIT_*'  functions
 *               to see their  possible return  values, which are  always `0'  when they  would
 *               perform a wait  operation, and usually  `1' otherwise) or  `0' if the  calling
 *               thread had to perform a wait operation, at which point this function returning
 *               that value means that you've once again been re-awoken.
 * @return: < 0: Timeout expired
 * @throws: E_SEGFAULT:         A faulty pointer was given
 * @throws: E_INVALID_ARGUMENT: One of the given commands is invalid, or `expr[0].fe_condition == LFUTEX_EXPREND' */
INTDEF ATTR_IN_OPT(4) NONNULL((1, 3)) int (LIBCCALL libc_LFutexExprI)(lfutex_t *ulockaddr, void *base, struct lfutexexpr const *expr, struct timespec const *timeout, unsigned int timeout_flags) THROWS(...);
/* >> LFutexExprI(2), LFutexExprI64(2)
 * Same as `LFutexExpr()', but implicitly handle `E_INTERRUPT' exceptions by re-starting the system call.
 * @return: * :  The first  non-zero  return value  from  executing  all of  the  given  `expr'
 *               in order (s.a. the documentations of the individual `LFUTEX_WAIT_*'  functions
 *               to see their  possible return  values, which are  always `0'  when they  would
 *               perform a wait  operation, and usually  `1' otherwise) or  `0' if the  calling
 *               thread had to perform a wait operation, at which point this function returning
 *               that value means that you've once again been re-awoken.
 * @return: < 0: Timeout expired
 * @throws: E_SEGFAULT:         A faulty pointer was given
 * @throws: E_INVALID_ARGUMENT: One of the given commands is invalid, or `expr[0].fe_condition == LFUTEX_EXPREND' */
INTDEF ATTR_IN_OPT(4) NONNULL((1, 3)) int (LIBCCALL libc_LFutexExprI64)(lfutex_t *ulockaddr, void *base, struct lfutexexpr const *expr, struct timespec64 const *timeout, unsigned int timeout_flags) THROWS(...);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_KOS_FUTEXEXPR_H */
