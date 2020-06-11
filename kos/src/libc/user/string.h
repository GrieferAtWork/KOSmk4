/* HASH CRC-32:0x7cd12e3d */
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
#ifndef GUARD_LIBC_USER_STRING_H
#define GUARD_LIBC_USER_STRING_H 1

#include "../api.h"
#include "../auto/string.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <string.h>

DECL_BEGIN

#ifndef __KERNEL__
INTDEF WUNUSED char *NOTHROW_NCX(LIBCCALL libc_strsignal)(int signo);
INTDEF ATTR_COLD ATTR_RETNONNULL NONNULL((2)) char *NOTHROW_NCX(LIBCCALL libc_strerror_r)(int errnum, char *buf, size_t buflen);
INTDEF ATTR_COLD NONNULL((2)) errno_t NOTHROW_NCX(LIBCCALL libc___xpg_strerror_r)(int errnum, char *buf, size_t buflen);
INTDEF ATTR_CONST WUNUSED char const *NOTHROW(LIBCCALL libc_strerror_s)(int errnum);
INTDEF ATTR_CONST WUNUSED char const *NOTHROW(LIBCCALL libc_strerrorname_s)(int errnum);
INTDEF ATTR_CONST WUNUSED char const *NOTHROW(LIBCCALL libc_strsignal_s)(int signum);
INTDEF WUNUSED char *NOTHROW_RPC(LIBCCALL libc__strerror)(char const *message);
INTDEF NONNULL((1)) errno_t NOTHROW_RPC(LIBDCALL libd__strerror_s)(char *__restrict buf, size_t buflen, char const *message);
INTDEF NONNULL((1)) errno_t NOTHROW_RPC(LIBKCALL libc__strerror_s)(char *__restrict buf, size_t buflen, char const *message);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_USER_STRING_H */
