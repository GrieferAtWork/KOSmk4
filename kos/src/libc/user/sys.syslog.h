/* HASH CRC-32:0x16ae8afb */
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_USER_SYS_SYSLOG_H
#define GUARD_LIBC_USER_SYS_SYSLOG_H 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include <sys/syslog.h>

DECL_BEGIN

INTDEF void NOTHROW_NCX(LIBCCALL libc_closelog)(void);
INTDEF void NOTHROW_RPC(LIBCCALL libc_openlog)(char const *ident, int option, int facility);
INTDEF int NOTHROW_NCX(LIBCCALL libc_setlogmask)(int mask);
INTDEF NONNULL((2)) ATTR_LIBC_PRINTF(2,3) void NOTHROW_RPC(VLIBCCALL libc_syslog)(int level, char const *format, ...);
INTDEF NONNULL((2)) ATTR_LIBC_PRINTF(2,0) void NOTHROW_RPC(LIBCCALL libc_vsyslog)(int level, char const *format, va_list args);
/* Helper functions for printing to the system log */
INTDEF NONNULL((2)) ssize_t NOTHROW_RPC(LIBCCALL libc_syslog_printer)(void *arg, char const *__restrict data, size_t datalen);

DECL_END

#endif /* !GUARD_LIBC_USER_SYS_SYSLOG_H */
