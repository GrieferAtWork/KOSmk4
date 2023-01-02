/* HASH CRC-32:0xd725a58d */
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
#ifndef GUARD_LIBC_AUTO_SYS_TIMERFD_H
#define GUARD_LIBC_AUTO_SYS_TIMERFD_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <sys/timerfd.h>

DECL_BEGIN

#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> timerfd_create(2)
 * @param: flags: Set of `0 | TFD_NONBLOCK | TFD_CLOEXEC | TFD_CLOFORK' */
INTDEF fd_t NOTHROW(LIBDCALL libd_timerfd_create)(clockid_t clock_id, __STDC_INT_AS_UINT_T flags);
/* >> timerfd_settime(2), timerfd_settime64(2)
 * @param: flags: Set of `0 | TFD_TIMER_ABSTIME' */
INTDEF ATTR_IN(3) ATTR_OUT_OPT(4) int NOTHROW_NCX(LIBDCALL libd_timerfd_settime)(fd_t ufd, __STDC_INT_AS_UINT_T flags, struct itimerspec const *utmr, struct itimerspec *otmr);
/* >> timerfd_gettime(2), timerfd_gettime64(2) */
INTDEF ATTR_OUT(2) int NOTHROW_NCX(LIBDCALL libd_timerfd_gettime)(fd_t ufd, struct itimerspec *__restrict otmr);
/* >> timerfd_settime(2), timerfd_settime64(2)
 * @param: flags: Set of `0 | TFD_TIMER_ABSTIME' */
INTDEF ATTR_IN(3) ATTR_OUT_OPT(4) int NOTHROW_NCX(LIBDCALL libd_timerfd_settime64)(fd_t ufd, __STDC_INT_AS_UINT_T flags, struct itimerspec64 const *utmr, struct itimerspec64 *otmr);
/* >> timerfd_gettime(2), timerfd_gettime64(2) */
INTDEF ATTR_OUT(2) int NOTHROW_NCX(LIBDCALL libd_timerfd_gettime64)(fd_t ufd, struct itimerspec64 *__restrict otmr);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_SYS_TIMERFD_H */
