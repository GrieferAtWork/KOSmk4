/* HASH CRC-32:0xd4d60e27 */
/* Copyright (c) 2019 Griefer@Work                                            *
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
#ifndef GUARD_LIBC_USER_STRING_H
#define GUARD_LIBC_USER_STRING_H 1

#include "../api.h"
#include "../auto/string.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include <string.h>

DECL_BEGIN

INTDEF ATTR_COLD ATTR_RETNONNULL WUNUSED char *NOTHROW_NCX(LIBCCALL libc_strerror)(int errnum);
INTDEF ATTR_COLD WUNUSED char *NOTHROW_NCX(LIBCCALL libc_strerror_l)(int errnum, locale_t locale);
INTDEF WUNUSED char *NOTHROW_NCX(LIBCCALL libc_strsignal)(int signo);
INTDEF ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED NONNULL((1)) char *NOTHROW_NCX(LIBCCALL libc_strndup)(char const *__restrict string, size_t max_chars);
INTDEF ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED NONNULL((1)) char *NOTHROW_NCX(LIBCCALL libc_strdup)(char const *__restrict string);
INTDEF ATTR_COLD ATTR_RETNONNULL NONNULL((2)) char *NOTHROW_NCX(LIBCCALL libc_strerror_r)(int errnum, char *buf, size_t buflen);
INTDEF ATTR_CONST ATTR_PURE WUNUSED char const *NOTHROW(LIBCCALL libc_strerror_s)(int errnum);
INTDEF ATTR_CONST WUNUSED char const *NOTHROW(LIBCCALL libc_strerrorname_s)(int errnum);
INTDEF ATTR_CONST WUNUSED char const *NOTHROW(LIBCCALL libc_strsignal_s)(int signum);
/* Print the given `FORMAT' into a newly allocated, heap-allocated string */
INTDEF ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED ATTR_LIBC_PRINTF(1, 0) char *NOTHROW_NCX(LIBCCALL libc_vstrdupf)(char const *__restrict format, va_list args);
/* Print the given `FORMAT' into a newly allocated, heap-allocated string */
INTDEF ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED ATTR_LIBC_PRINTF(1, 0) char *NOTHROW_NCX(VLIBCCALL libc_strdupf)(char const *__restrict format, ...);
INTDEF WUNUSED char *NOTHROW_RPC(LIBCCALL libc__strerror)(char const *message);
INTDEF NONNULL((1)) errno_t NOTHROW_RPC(LIBCCALL libc__strerror_s)(char *__restrict buf, size_t buflen, char const *message);
INTDEF NONNULL((1)) errno_t NOTHROW_RPC(LIBDCALL libd__strerror_s)(char *__restrict buf, size_t buflen, char const *message);

DECL_END

#endif /* !GUARD_LIBC_USER_STRING_H */
