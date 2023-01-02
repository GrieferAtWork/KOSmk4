/* HASH CRC-32:0x91deeb6f */
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
#ifndef GUARD_LIBC_AUTO_SYS_SYSLOG_H
#define GUARD_LIBC_AUTO_SYS_SYSLOG_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <sys/syslog.h>

DECL_BEGIN

#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF void NOTHROW_RPC(LIBDCALL libd_openlog)(char const *ident, __STDC_INT_AS_UINT_T option, __STDC_INT_AS_UINT_T facility);
INTDEF int NOTHROW_NCX(LIBDCALL libd_setlogmask)(__STDC_INT_AS_UINT_T mask);
INTDEF ATTR_IN(2) ATTR_LIBC_PRINTF(2, 3) void NOTHROW_RPC(VLIBDCALL libd_syslog)(__STDC_INT_AS_UINT_T level, char const *format, ...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_IN(2) ATTR_LIBC_PRINTF(2, 3) void NOTHROW_RPC(VLIBCCALL libc_syslog)(__STDC_INT_AS_UINT_T level, char const *format, ...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_IN(2) ATTR_LIBC_PRINTF(2, 0) void NOTHROW_RPC(LIBDCALL libd_vsyslog)(__STDC_INT_AS_UINT_T level, char const *format, va_list args);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_IN(2) ATTR_LIBC_PRINTF(2, 0) void NOTHROW_RPC(LIBCCALL libc_vsyslog)(__STDC_INT_AS_UINT_T level, char const *format, va_list args);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_SYS_SYSLOG_H */
