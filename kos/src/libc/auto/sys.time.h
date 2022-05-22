/* HASH CRC-32:0x134cc5ef */
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
#ifndef GUARD_LIBC_AUTO_SYS_TIME_H
#define GUARD_LIBC_AUTO_SYS_TIME_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <sys/time.h>

DECL_BEGIN

#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> gettimeofday(2), gettimeofday64(2) */
INTDEF ATTR_ACCESS_WR_OPT(1) ATTR_ACCESS_WR_OPT(2) int NOTHROW_NCX(LIBDCALL libd_gettimeofday)(struct timeval *__restrict tv, __timezone_ptr_t tz);
/* >> getitimer(2), getitimer64(2) */
INTDEF ATTR_ACCESS_WR(2) int NOTHROW_NCX(LIBDCALL libd_getitimer)(__itimer_which_t which, struct itimerval *curr_value);
/* >> setitimer(2), setitimer64(2) */
INTDEF ATTR_ACCESS_RO(2) ATTR_ACCESS_WR_OPT(3) int NOTHROW_NCX(LIBDCALL libd_setitimer)(__itimer_which_t which, struct itimerval const *newval, struct itimerval *oldval);
/* >> utimes(2), utimes64(2) */
INTDEF ATTR_ACCESS_RO(1) ATTR_ACCESS_RO_OPT(2) int NOTHROW_NCX(LIBDCALL libd_utimes)(char const *file, struct timeval const tvp[2]);
/* >> futimesat(2), futimesat64(2) */
INTDEF ATTR_ACCESS_RO(2) ATTR_ACCESS_RO_OPT(3) int NOTHROW_NCX(LIBDCALL libd_futimesat)(fd_t fd, char const *file, struct timeval const tvp[2]);
/* >> settimeofday(2), settimeofday64(2) */
INTDEF ATTR_ACCESS_RO_OPT(1) ATTR_ACCESS_RO_OPT(2) int NOTHROW_NCX(LIBDCALL libd_settimeofday)(struct timeval const *tv, struct timezone const *tz);
/* >> adjtime(3), adjtime64(3) */
INTDEF ATTR_ACCESS_RO_OPT(1) ATTR_ACCESS_WR_OPT(2) int NOTHROW_NCX(LIBDCALL libd_adjtime)(struct timeval const *delta, struct timeval *olddelta);
/* >> lutimes(2), lutimes64(2) */
INTDEF ATTR_ACCESS_RO(1) ATTR_ACCESS_RO_OPT(2) int NOTHROW_NCX(LIBDCALL libd_lutimes)(char const *file, struct timeval const tvp[2]);
/* >> futimes(2), futimes64(2) */
INTDEF ATTR_ACCESS_RO_OPT(2) int NOTHROW_NCX(LIBDCALL libd_futimes)(fd_t fd, struct timeval const tvp[2]);
/* >> gettimeofday(2), gettimeofday64(2) */
INTDEF ATTR_ACCESS_WR_OPT(1) ATTR_ACCESS_WR_OPT(2) int NOTHROW_NCX(LIBDCALL libd_gettimeofday64)(struct timeval64 *__restrict tv, __timezone_ptr_t tz);
/* >> getitimer(2), getitimer64(2) */
INTDEF ATTR_ACCESS_WR(2) int NOTHROW_NCX(LIBDCALL libd_getitimer64)(__itimer_which_t which, struct itimerval64 *curr_value);
/* >> setitimer(2), setitimer64(2) */
INTDEF ATTR_ACCESS_RO(2) ATTR_ACCESS_WR_OPT(3) int NOTHROW_NCX(LIBDCALL libd_setitimer64)(__itimer_which_t which, struct itimerval64 const *newval, struct itimerval64 *oldval);
/* >> utimes(2), utimes64(2) */
INTDEF ATTR_ACCESS_RO(1) ATTR_ACCESS_RO_OPT(2) int NOTHROW_NCX(LIBDCALL libd_utimes64)(char const *file, struct timeval64 const tvp[2]);
/* >> settimeofday(2), settimeofday64(2) */
INTDEF ATTR_ACCESS_RO_OPT(1) ATTR_ACCESS_RO_OPT(2) int NOTHROW_NCX(LIBDCALL libd_settimeofday64)(struct timeval64 const *tv, struct timezone const *tz);
/* >> adjtime(3), adjtime64(3) */
INTDEF ATTR_ACCESS_RO_OPT(1) ATTR_ACCESS_WR_OPT(2) int NOTHROW_NCX(LIBDCALL libd_adjtime64)(struct timeval64 const *delta, struct timeval64 *olddelta);
/* >> lutimes(2), lutimes64(2) */
INTDEF ATTR_ACCESS_RO(1) ATTR_ACCESS_RO_OPT(2) int NOTHROW_NCX(LIBDCALL libd_lutimes64)(char const *file, struct timeval64 const tvp[2]);
/* >> lutimes(2), lutimes64(2) */
INTDEF ATTR_ACCESS_RO_OPT(2) int NOTHROW_NCX(LIBDCALL libd_futimes64)(fd_t fd, struct timeval64 const tvp[2]);
/* >> futimesat(2), futimesat64(2) */
INTDEF ATTR_ACCESS_RO(2) ATTR_ACCESS_RO_OPT(3) int NOTHROW_NCX(LIBDCALL libd_futimesat64)(fd_t fd, char const *file, struct timeval64 const tvp[2]);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_SYS_TIME_H */
