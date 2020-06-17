/* HASH CRC-32:0xdbced6c0 */
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
#ifndef GUARD_LIBC_AUTO_DOSABI_SYS_SYSLOG_C
#define GUARD_LIBC_AUTO_DOSABI_SYS_SYSLOG_C 1

#include "../../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../../user/sys.syslog.h"

DECL_BEGIN

INTERN ATTR_SECTION(".text.crt.dos.system.syslog") void
NOTHROW_RPC(LIBDCALL libd_openlog)(char const *ident,
                                   __STDC_INT_AS_UINT_T option,
                                   __STDC_INT_AS_UINT_T facility) {
	libc_openlog(ident, option, facility);
}
INTERN ATTR_SECTION(".text.crt.dos.system.syslog") int
NOTHROW_NCX(LIBDCALL libd_setlogmask)(__STDC_INT_AS_UINT_T mask) {
	return libc_setlogmask(mask);
}
INTERN ATTR_SECTION(".text.crt.dos.system.syslog") ATTR_LIBC_PRINTF(2, 0) NONNULL((2)) void
NOTHROW_RPC(LIBDCALL libd_vsyslog)(__STDC_INT_AS_UINT_T level,
                                   char const *format,
                                   va_list args) {
	libc_vsyslog(level, format, args);
}
/* Helper functions for printing to the system log */
INTERN ATTR_SECTION(".text.crt.dos.system.syslog") NONNULL((2)) ssize_t
NOTHROW_RPC(LIBDCALL libd_syslog_printer)(void *arg,
                                          char const *__restrict data,
                                          size_t datalen) {
	return libc_syslog_printer(arg, data, datalen);
}

DECL_END

DEFINE_PUBLIC_ALIAS(DOS$openlog, libd_openlog);
DEFINE_PUBLIC_ALIAS(DOS$setlogmask, libd_setlogmask);
DEFINE_PUBLIC_ALIAS(DOS$vsyslog, libd_vsyslog);
DEFINE_PUBLIC_ALIAS(DOS$syslog_printer, libd_syslog_printer);

#endif /* !GUARD_LIBC_AUTO_DOSABI_SYS_SYSLOG_C */
