/* HASH CRC-32:0xd58a56b */
/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_AUTO_SYS_SYSLOG_C
#define GUARD_LIBC_AUTO_SYS_SYSLOG_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../user/sys.syslog.h"
#include "format-printer.h"

DECL_BEGIN

#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.system.syslog") ATTR_IN(2) ATTR_LIBC_PRINTF(2, 3) void
NOTHROW_RPC(VLIBDCALL libd_syslog)(__STDC_INT_AS_UINT_T level,
                                   char const *format,
                                   ...) {
	va_list args;
	va_start(args, format);
	libc_vsyslog(level, format, args);
	va_end(args);
}
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTERN ATTR_SECTION(".text.crt.system.syslog") ATTR_IN(2) ATTR_LIBC_PRINTF(2, 3) void
NOTHROW_RPC(VLIBCCALL libc_syslog)(__STDC_INT_AS_UINT_T level,
                                   char const *format,
                                   ...) {
	va_list args;
	va_start(args, format);
	libc_vsyslog(level, format, args);
	va_end(args);
}
INTERN ATTR_SECTION(".text.crt.system.syslog") ATTR_IN(2) ATTR_LIBC_PRINTF(2, 0) void
NOTHROW_RPC(LIBCCALL libc_vsyslog)(__STDC_INT_AS_UINT_T level,
                                   char const *format,
                                   va_list args) {
	libc_format_vprintf(&libc_syslog_printer,
	               (void *)(uintptr_t)(unsigned int)level,
	               format,
	               args);
}
#endif /* !__KERNEL__ */

DECL_END

#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS_P_VOID(DOS$syslog,libd_syslog,ATTR_IN(2) ATTR_LIBC_PRINTF(2, 3),NOTHROW_RPC,VLIBDCALL,(__STDC_INT_AS_UINT_T level, char const *format, ...),(level,format,));
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS_P_VOID(syslog,libc_syslog,ATTR_IN(2) ATTR_LIBC_PRINTF(2, 3),NOTHROW_RPC,VLIBCCALL,(__STDC_INT_AS_UINT_T level, char const *format, ...),(level,format,));
DEFINE_PUBLIC_ALIAS_P_VOID(vsyslog,libc_vsyslog,ATTR_IN(2) ATTR_LIBC_PRINTF(2, 0),NOTHROW_RPC,LIBCCALL,(__STDC_INT_AS_UINT_T level, char const *format, va_list args),(level,format,args));
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_SYS_SYSLOG_C */
