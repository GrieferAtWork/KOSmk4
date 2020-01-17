/* HASH CRC-32:0x43b73a29 */
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
#ifndef GUARD_LIBC_AUTO_STDIO_H
#define GUARD_LIBC_AUTO_STDIO_H 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include <stdio.h>
#include <kos/anno.h>

DECL_BEGIN

/* Print a formatted string to a given in-member string buffer `BUF'
 * Return the number of written characters, excluding a trailing NUL-character */
INTDEF NONNULL((1, 2)) ATTR_LIBC_PRINTF(2, 0) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBCCALL libc_vsprintf)(char *__restrict dest, char const *__restrict format, va_list args);
/* Print a formatted string to a given in-member string buffer `BUF'
 * Return the number of written characters, excluding a trailing NUL-character */
INTDEF NONNULL((1, 2)) ATTR_LIBC_PRINTF(2, 3) __STDC_INT_AS_SIZE_T NOTHROW_NCX(VLIBCCALL libc_sprintf)(char *__restrict buf, char const *__restrict format, ...);
/* Print a formatted string to a given in-member string buffer `BUF'
 * Always return the REQUIRED buffer size (excluding a trailing NUL-character), and never write more than `BUFLEN' characters to `BUF' */
INTDEF NONNULL((3)) ATTR_LIBC_PRINTF(3, 0) __STDC_INT_AS_SIZE_T NOTHROW_NCX(LIBCCALL libc_vsnprintf)(char *__restrict buf, size_t buflen, char const *__restrict format, va_list args);
/* Print a formatted string to a given in-member string buffer `BUF'
 * Always return the REQUIRED buffer size (excluding a trailing NUL-character), and never write more than `BUFLEN' characters to `BUF' */
INTDEF NONNULL((3)) ATTR_LIBC_PRINTF(3, 4) __STDC_INT_AS_SIZE_T NOTHROW_NCX(VLIBCCALL libc_snprintf)(char *__restrict buf, size_t buflen, char const *__restrict format, ...);
#ifndef __KERNEL__
/* Scan data from a given `INPUT' string, following `FORMAT'
 * Return the number of successfully scanned data items */
INTDEF WUNUSED NONNULL((1, 2)) ATTR_LIBC_SCANF(2, 0) __STDC_INT_AS_SIZE_T NOTHROW_NCX(LIBCCALL libc_vsscanf)(char const *__restrict input, char const *__restrict format, va_list args);
/* Scan data from a given `INPUT' string, following `FORMAT'
 * Return the number of successfully scanned data items */
INTDEF NONNULL((1, 2)) ATTR_LIBC_SCANF(2, 3) __STDC_INT_AS_SIZE_T NOTHROW_NCX(VLIBCCALL libc_sscanf)(char const *__restrict input, char const *__restrict format, ...);
/* Scan data from a given `INPUT' string, following `FORMAT'
 * Return the number of successfully scanned data items */
#define libc__vsscanf libc_vsscanf
/* Scan data from a given `INPUT' string, following `FORMAT'
 * Return the number of successfully scanned data items */
#define libc__vsscanf_s libc_vsscanf
INTDEF WUNUSED NONNULL((1, 2)) ATTR_LIBC_SCANF(2, 4) __STDC_INT_AS_SIZE_T NOTHROW_NCX(LIBCCALL libc__vsscanf_l)(char const *__restrict input, char const *__restrict format, locale_t locale, va_list args);
#define libc__vsscanf_s_l libc__vsscanf_l
INTDEF WUNUSED NONNULL((1, 3)) ATTR_LIBC_SCANF(3, 4) __STDC_INT_AS_SIZE_T NOTHROW_NCX(LIBCCALL libc__vsnscanf)(char const *__restrict input, size_t inputlen, char const *__restrict format, va_list args);
#define libc__vsnscanf_s libc__vsnscanf
INTDEF NONNULL((1, 3)) ATTR_LIBC_SCANF(3, 5) __STDC_INT_AS_SIZE_T NOTHROW_NCX(LIBCCALL libc__vsnscanf_l)(char const *__restrict input, size_t inputlen, char const *__restrict format, locale_t locale, va_list args);
#define libc__vsnscanf_s_l libc__vsnscanf_l
INTDEF NONNULL((1, 3)) ATTR_LIBC_SCANF(3, 4) __STDC_INT_AS_SIZE_T NOTHROW_NCX(VLIBCCALL libc__snscanf)(char const *__restrict input, size_t inputlen, char const *__restrict format, ...);
INTDEF NONNULL((1, 3)) ATTR_LIBC_SCANF(3, 5) __STDC_INT_AS_SIZE_T NOTHROW_NCX(VLIBCCALL libc__snscanf_l)(char const *__restrict input, size_t inputlen, char const *__restrict format, locale_t locale, ...);
INTDEF NONNULL((1, 2)) ATTR_LIBC_SCANF(2, 4) __STDC_INT_AS_SIZE_T (VLIBCCALL libc__sscanf_s_l)(char const *__restrict input, char const *__restrict format, locale_t locale, ...) __THROWS(...);
INTDEF NONNULL((1, 3)) ATTR_LIBC_SCANF(3, 4) __STDC_INT_AS_SIZE_T NOTHROW_NCX(VLIBCCALL libc__snscanf_s)(char const *__restrict input, size_t inputlen, char const *__restrict format, ...);
INTDEF NONNULL((1, 3)) ATTR_LIBC_SCANF(3, 5) __STDC_INT_AS_SIZE_T NOTHROW_NCX(VLIBCCALL libc__snscanf_s_l)(char const *__restrict input, size_t inputlen, char const *__restrict format, locale_t locale, ...);
INTDEF NONNULL((1, 2)) ATTR_LIBC_PRINTF(2, 0) __STDC_INT_AS_SIZE_T NOTHROW_NCX(LIBCCALL libc__vsprintf_l)(char *__restrict buf, char const *__restrict format, locale_t locale, va_list args);
#define libc__vsprintf_s_l libc__vsnprintf_l
INTDEF NONNULL((3)) ATTR_LIBC_PRINTF_P(3, 0) __STDC_INT_AS_SIZE_T NOTHROW_NCX(LIBCCALL libc__vsprintf_p)(char *__restrict buf, size_t bufsize, char const *__restrict format, va_list args);
INTDEF NONNULL((3)) ATTR_LIBC_PRINTF_P(3, 0) __STDC_INT_AS_SIZE_T NOTHROW_NCX(LIBCCALL libc__vsprintf_p_l)(char *__restrict buf, size_t bufsize, char const *__restrict format, locale_t locale, va_list args);
INTDEF NONNULL((1, 2)) ATTR_LIBC_PRINTF(2, 4) __STDC_INT_AS_SIZE_T NOTHROW_NCX(VLIBCCALL libc__sprintf_l)(char *__restrict buf, char const *__restrict format, locale_t locale, ...);
INTDEF NONNULL((3)) ATTR_LIBC_PRINTF(3, 5) __STDC_INT_AS_SIZE_T NOTHROW_NCX(VLIBCCALL libc__sprintf_s_l)(char *__restrict buf, size_t bufsize, char const *__restrict format, locale_t locale, ...);
INTDEF NONNULL((3)) ATTR_LIBC_PRINTF_P(3, 4) __STDC_INT_AS_SIZE_T NOTHROW_NCX(VLIBCCALL libc__sprintf_p)(char *__restrict buf, size_t bufsize, char const *__restrict format, ...);
INTDEF NONNULL((3)) ATTR_LIBC_PRINTF_P(3, 5) __STDC_INT_AS_SIZE_T NOTHROW_NCX(VLIBCCALL libc__sprintf_p_l)(char *__restrict buf, size_t bufsize, char const *__restrict format, locale_t locale, ...);
INTDEF WUNUSED NONNULL((1)) ATTR_LIBC_PRINTF(1, 0) __STDC_INT_AS_SIZE_T NOTHROW_NCX(LIBCCALL libc__vscprintf)(char const *__restrict format, va_list args);
INTDEF WUNUSED NONNULL((1)) ATTR_LIBC_PRINTF(1, 2) __STDC_INT_AS_SIZE_T NOTHROW_NCX(VLIBCCALL libc__scprintf)(char const *__restrict format, ...);
INTDEF WUNUSED NONNULL((1)) ATTR_LIBC_PRINTF(1, 0) __STDC_INT_AS_SIZE_T NOTHROW_NCX(LIBCCALL libc__vscprintf_l)(char const *__restrict format, locale_t locale, va_list args);
INTDEF WUNUSED NONNULL((1)) ATTR_LIBC_PRINTF_P(1, 0) __STDC_INT_AS_SIZE_T NOTHROW_NCX(LIBCCALL libc__vscprintf_p)(char const *__restrict format, va_list args);
INTDEF WUNUSED NONNULL((1)) ATTR_LIBC_PRINTF_P(1, 0) __STDC_INT_AS_SIZE_T NOTHROW_NCX(LIBCCALL libc__vscprintf_p_l)(char const *__restrict format, locale_t locale, va_list args);
INTDEF WUNUSED NONNULL((1)) ATTR_LIBC_PRINTF(1, 3) __STDC_INT_AS_SIZE_T NOTHROW_NCX(VLIBCCALL libc__scprintf_l)(char const *__restrict format, locale_t locale, ...);
INTDEF WUNUSED NONNULL((1)) ATTR_LIBC_PRINTF_P(1, 2) __STDC_INT_AS_SIZE_T NOTHROW_NCX(VLIBCCALL libc__scprintf_p)(char const *__restrict format, ...);
INTDEF WUNUSED NONNULL((1)) ATTR_LIBC_PRINTF_P(1, 3) __STDC_INT_AS_SIZE_T NOTHROW_NCX(VLIBCCALL libc__scprintf_p_l)(char const *__restrict format, locale_t locale, ...);
/* WARNING: This function returns the number of written character. - Not the required buffer size! */
INTDEF NONNULL((3)) ATTR_LIBC_PRINTF(3, 0) __STDC_INT_AS_SIZE_T NOTHROW_NCX(LIBCCALL libc__vsnprintf)(char *__restrict buf, size_t bufsize, char const *__restrict format, va_list args);
INTDEF NONNULL((3)) ATTR_LIBC_PRINTF(3, 0) __STDC_INT_AS_SIZE_T NOTHROW_NCX(LIBCCALL libc__vsnprintf_l)(char *__restrict buf, size_t bufsize, char const *__restrict format, locale_t locale, va_list args);
/* WARNING: This function returns the number of written character. - Not the required buffer size! */
#define libc__vsnprintf_c libc__vsnprintf
#define libc__vsnprintf_c_l libc__vsnprintf_l
INTDEF NONNULL((4)) ATTR_LIBC_PRINTF(4, 0) __STDC_INT_AS_SIZE_T NOTHROW_NCX(LIBCCALL libc__vsnprintf_s)(char *__restrict buf, size_t bufsize, size_t buflen, char const *__restrict format, va_list args);
INTDEF NONNULL((4)) ATTR_LIBC_PRINTF(4, 0) __STDC_INT_AS_SIZE_T NOTHROW_NCX(LIBCCALL libc__vsnprintf_s_l)(char *__restrict buf, size_t bufsize, size_t buflen, char const *__restrict format, locale_t locale, va_list args);
INTDEF NONNULL((3)) ATTR_LIBC_PRINTF(3, 4) __STDC_INT_AS_SIZE_T NOTHROW_NCX(VLIBCCALL libc__snprintf)(char *__restrict buf, size_t bufsize, char const *__restrict format, ...);
INTDEF NONNULL((3)) ATTR_LIBC_PRINTF(3, 5) __STDC_INT_AS_SIZE_T NOTHROW_NCX(VLIBCCALL libc__snprintf_l)(char *__restrict buf, size_t bufsize, char const *__restrict format, locale_t locale, ...);
INTDEF NONNULL((3)) ATTR_LIBC_PRINTF(3, 4) __STDC_INT_AS_SIZE_T NOTHROW_NCX(VLIBCCALL libc__snprintf_c)(char *__restrict buf, size_t bufsize, char const *__restrict format, ...);
INTDEF NONNULL((3)) ATTR_LIBC_PRINTF(3, 5) __STDC_INT_AS_SIZE_T NOTHROW_NCX(VLIBCCALL libc__snprintf_c_l)(char *__restrict buf, size_t bufsize, char const *__restrict format, locale_t locale, ...);
INTDEF NONNULL((4)) ATTR_LIBC_PRINTF(4, 5) __STDC_INT_AS_SIZE_T NOTHROW_NCX(VLIBCCALL libc__snprintf_s)(char *__restrict buf, size_t bufsize, size_t buflen, char const *__restrict format, ...);
INTDEF NONNULL((4)) ATTR_LIBC_PRINTF(4, 6) __STDC_INT_AS_SIZE_T NOTHROW_NCX(VLIBCCALL libc__snprintf_s_l)(char *__restrict buf, size_t bufsize, size_t buflen, char const *__restrict format, locale_t locale, ...);
/* Print a formatted string to a given in-member string buffer `BUF'
 * Always return the REQUIRED buffer size (excluding a trailing NUL-character), and never write more than `BUFLEN' characters to `BUF' */
#define libc_sprintf_s libc_snprintf
/* Print a formatted string to a given in-member string buffer `BUF'
 * Always return the REQUIRED buffer size (excluding a trailing NUL-character), and never write more than `BUFLEN' characters to `BUF' */
#define libc_vsprintf_s libc_vsnprintf
/* Scan data from a given `INPUT' string, following `FORMAT'
 * Return the number of successfully scanned data items */
#define libc_sscanf_s libc_sscanf
/* Scan data from a given `INPUT' string, following `FORMAT'
 * Return the number of successfully scanned data items */
#define libc_vsscanf_s libc_vsscanf
INTDEF NONNULL((4)) ATTR_LIBC_PRINTF(4, 0) __STDC_INT_AS_SIZE_T NOTHROW_NCX(LIBCCALL libc_vsnprintf_s)(char *__restrict buf, size_t bufsize, size_t buflen, char const *__restrict format, va_list args);
/* Same as `fflush()', but performs I/O without acquiring a lock to `STREAM' */
#define libc__fflush_nolock libc_fflush_unlocked
#define libc_flushall libc__flushall
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_STDIO_H */
