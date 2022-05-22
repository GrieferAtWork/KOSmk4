/* HASH CRC-32:0x678527ff */
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
#ifndef GUARD_LIBC_AUTO_SYS_TIMEX_H
#define GUARD_LIBC_AUTO_SYS_TIMEX_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <sys/timex.h>

DECL_BEGIN

#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> adjtimex(2), adjtimex64(2) */
INTDEF ATTR_INOUT(1) int NOTHROW_NCX(LIBDCALL libd_adjtimex)(struct timex *__restrict ntx);
/* >> ntp_gettime(3), ntp_gettime64(3) */
INTDEF ATTR_OUT(1) int NOTHROW_NCX(LIBDCALL libd_ntp_gettimex)(struct ntptimeval *__restrict ntv);
/* >> ntp_adjtime(3), ntp_adjtime64(3) */
INTDEF ATTR_INOUT(1) int NOTHROW_NCX(LIBDCALL libd_ntp_adjtime)(struct timex *__restrict tntx);
/* >> adjtimex(2), adjtimex64(2) */
INTDEF ATTR_INOUT(1) int NOTHROW_NCX(LIBDCALL libd_adjtimex64)(struct timex64 *__restrict ntx);
/* >> ntp_adjtime(3), ntp_adjtime64(3) */
INTDEF ATTR_INOUT(1) int NOTHROW_NCX(LIBDCALL libd_ntp_adjtime64)(struct timex64 *__restrict tntx);
/* >> ntp_gettime(3), ntp_gettime64(3) */
INTDEF ATTR_OUT(1) int NOTHROW_NCX(LIBDCALL libd_ntp_gettimex64)(struct ntptimeval64 *__restrict ntv);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_SYS_TIMEX_H */
