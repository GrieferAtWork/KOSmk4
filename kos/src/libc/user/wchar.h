/* HASH CRC-32:0xb3decc72 */
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
#ifndef GUARD_LIBC_USER_WCHAR_H
#define GUARD_LIBC_USER_WCHAR_H 1

#include "../api.h"
#include "../auto/wchar.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <wchar.h>

DECL_BEGIN

#ifndef __KERNEL__
/* >> fgetwc(3) */
INTDEF NONNULL((1)) wint16_t (LIBDCALL libd_fgetwc)(FILE *__restrict stream) THROWS(...);
/* >> fgetwc(3) */
INTDEF NONNULL((1)) wint32_t (LIBKCALL libc_fgetwc)(FILE *__restrict stream) THROWS(...);
/* >> fputwc(3) */
INTDEF NONNULL((2)) wint16_t (LIBDCALL libd_fputwc)(char16_t wc, FILE *stream) THROWS(...);
/* >> fputwc(3) */
INTDEF NONNULL((2)) wint32_t (LIBKCALL libc_fputwc)(char32_t wc, FILE *stream) THROWS(...);
/* >> ungetwc(3) */
INTDEF NONNULL((2)) wint16_t NOTHROW_NCX(LIBDCALL libd_ungetwc)(wint16_t wc, FILE *stream);
/* >> ungetwc(3) */
INTDEF NONNULL((2)) wint32_t NOTHROW_NCX(LIBKCALL libc_ungetwc)(wint32_t wc, FILE *stream);
/* >> open_wmemstream(3) */
INTDEF FILE *NOTHROW_NCX(LIBDCALL libd_open_wmemstream)(char16_t **bufloc, size_t *sizeloc);
/* >> open_wmemstream(3) */
INTDEF FILE *NOTHROW_NCX(LIBKCALL libc_open_wmemstream)(char32_t **bufloc, size_t *sizeloc);
/* >> getwc_unlocked(3), fgetwc_unlocked(3) */
INTDEF NONNULL((1)) wint16_t (LIBDCALL libd_fgetwc_unlocked)(FILE *__restrict stream) THROWS(...);
/* >> getwc_unlocked(3), fgetwc_unlocked(3) */
INTDEF NONNULL((1)) wint32_t (LIBKCALL libc_fgetwc_unlocked)(FILE *__restrict stream) THROWS(...);
/* >> putwc_unlocked(3), fputwc_unlocked(3) */
INTDEF NONNULL((2)) wint16_t (LIBDCALL libd_fputwc_unlocked)(char16_t wc, FILE *__restrict stream) THROWS(...);
/* >> putwc_unlocked(3), fputwc_unlocked(3) */
INTDEF NONNULL((2)) wint32_t (LIBKCALL libc_fputwc_unlocked)(char32_t wc, FILE *__restrict stream) THROWS(...);
/* >> file_wprinter(3)
 * For use with `format_wprintf()' and friends: Prints to a `FILE *' closure argument */
INTDEF NONNULL((1, 2)) ssize_t (LIBDCALL libd_file_wprinter)(void *arg, char16_t const *__restrict data, size_t datalen) THROWS(...);
/* >> file_wprinter(3)
 * For use with `format_wprintf()' and friends: Prints to a `FILE *' closure argument */
INTDEF NONNULL((1, 2)) ssize_t (LIBKCALL libc_file_wprinter)(void *arg, char32_t const *__restrict data, size_t datalen) THROWS(...);
/* >> file_wprinter_unlocked(3)
 * Same as `file_wprinter()', but performs I/O without acquiring a lock to `(FILE *)arg' */
INTDEF NONNULL((1, 2)) ssize_t (LIBDCALL libd_file_wprinter_unlocked)(void *arg, char16_t const *__restrict data, size_t datalen) THROWS(...);
/* >> file_wprinter_unlocked(3)
 * Same as `file_wprinter()', but performs I/O without acquiring a lock to `(FILE *)arg' */
INTDEF NONNULL((1, 2)) ssize_t (LIBKCALL libc_file_wprinter_unlocked)(void *arg, char32_t const *__restrict data, size_t datalen) THROWS(...);
/* >> ungetwc_unlocked(3) */
INTDEF NONNULL((2)) wint16_t NOTHROW_NCX(LIBDCALL libd_ungetwc_unlocked)(wint16_t ch, FILE *__restrict stream);
/* >> ungetwc_unlocked(3) */
INTDEF NONNULL((2)) wint32_t NOTHROW_NCX(LIBKCALL libc_ungetwc_unlocked)(wint32_t ch, FILE *__restrict stream);
/* >> vfwscanf_unlocked(3) */
INTDEF WUNUSED ATTR_LIBC_C16SCANF(2, 0) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (LIBDCALL libd_vfwscanf_unlocked)(FILE *__restrict stream, char16_t const *__restrict format, va_list args) THROWS(...);
/* >> vfwscanf_unlocked(3) */
INTDEF WUNUSED ATTR_LIBC_C32SCANF(2, 0) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (LIBKCALL libc_vfwscanf_unlocked)(FILE *__restrict stream, char32_t const *__restrict format, va_list args) THROWS(...);
/* >> fgetwln(3) */
INTDEF WUNUSED NONNULL((1, 2)) char16_t *NOTHROW_NCX(LIBDCALL libd_fgetwln)(FILE *__restrict fp, size_t *__restrict lenp);
/* >> fgetwln(3) */
INTDEF WUNUSED NONNULL((1, 2)) char32_t *NOTHROW_NCX(LIBKCALL libc_fgetwln)(FILE *__restrict fp, size_t *__restrict lenp);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_USER_WCHAR_H */
