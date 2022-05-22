/* HASH CRC-32:0xd442407 */
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
#ifndef GUARD_LIBC_USER_SYS_SYSLOG_H
#define GUARD_LIBC_USER_SYS_SYSLOG_H 1

#include "../api.h"
#include "../auto/sys.syslog.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <sys/syslog.h>

DECL_BEGIN

#ifndef __KERNEL__
INTDEF void NOTHROW_NCX(LIBCCALL libc_closelog)(void);
INTDEF void NOTHROW_RPC(LIBCCALL libc_openlog)(char const *ident, __STDC_INT_AS_UINT_T option, __STDC_INT_AS_UINT_T facility);
INTDEF int NOTHROW_NCX(LIBCCALL libc_setlogmask)(__STDC_INT_AS_UINT_T mask);
/* Helper functions for printing to the system log */
INTDEF ATTR_INS(2, 3) ssize_t NOTHROW_RPC(__FORMATPRINTER_CC libc_syslog_printer)(void *arg, char const *__restrict data, size_t datalen);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_USER_SYS_SYSLOG_H */
