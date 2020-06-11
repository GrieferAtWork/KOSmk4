/* HASH CRC-32:0x3154b0c5 */
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
#ifndef GUARD_LIBC_USER_WCHAR_H
#define GUARD_LIBC_USER_WCHAR_H 1

#include "../api.h"
#include "../auto/wchar.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <wchar.h>

DECL_BEGIN

#ifndef __KERNEL__
INTDEF NONNULL((1)) wint_t (LIBDCALL libd_fgetwc)(FILE *__restrict stream) THROWS(...);
INTDEF NONNULL((1)) wint_t (LIBKCALL libc_fgetwc)(FILE *__restrict stream) THROWS(...);
INTDEF NONNULL((2)) wint_t (LIBDCALL libd_fputwc)(char16_t wc, FILE *stream) THROWS(...);
INTDEF NONNULL((2)) wint_t (LIBKCALL libc_fputwc)(char32_t wc, FILE *stream) THROWS(...);
INTDEF NONNULL((2)) wint_t NOTHROW_NCX(LIBDCALL libd_ungetwc)(wint_t wc, FILE *stream);
INTDEF NONNULL((2)) wint_t NOTHROW_NCX(LIBKCALL libc_ungetwc)(wint_t wc, FILE *stream);
INTDEF WUNUSED ATTR_LIBC_WSCANF(2, 0) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (LIBDCALL libd_vfwscanf)(FILE *__restrict stream, char16_t const *__restrict format, va_list args) THROWS(...);
INTDEF WUNUSED ATTR_LIBC_WSCANF(2, 0) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (LIBKCALL libc_vfwscanf)(FILE *__restrict stream, char32_t const *__restrict format, va_list args) THROWS(...);
INTDEF NONNULL((2)) size_t NOTHROW_NCX(LIBDCALL libd_mbsnrtowcs)(char16_t *dst, char const **__restrict psrc, size_t nmc, size_t len, mbstate_t *mbs);
INTDEF NONNULL((2)) size_t NOTHROW_NCX(LIBKCALL libc_mbsnrtowcs)(char32_t *dst, char const **__restrict psrc, size_t nmc, size_t len, mbstate_t *mbs);
INTDEF NONNULL((2)) size_t NOTHROW_NCX(LIBDCALL libd_wcsnrtombs)(char *dst, char16_t const **__restrict psrc, size_t nwc, size_t len, mbstate_t *mbs);
INTDEF NONNULL((2)) size_t NOTHROW_NCX(LIBKCALL libc_wcsnrtombs)(char *dst, char32_t const **__restrict psrc, size_t nwc, size_t len, mbstate_t *mbs);
INTDEF FILE *NOTHROW_NCX(LIBDCALL libd_open_wmemstream)(char16_t **bufloc, size_t *sizeloc);
INTDEF FILE *NOTHROW_NCX(LIBKCALL libc_open_wmemstream)(char32_t **bufloc, size_t *sizeloc);
INTDEF NONNULL((1)) wint_t (LIBDCALL libd__fgetwc_nolock)(FILE *__restrict stream) THROWS(...);
INTDEF NONNULL((1)) wint_t (LIBKCALL libc_fgetwc_unlocked)(FILE *__restrict stream) THROWS(...);
INTDEF NONNULL((2)) wint_t (LIBDCALL libd__fputwc_nolock)(char16_t wc, FILE *__restrict stream) THROWS(...);
INTDEF NONNULL((2)) wint_t (LIBKCALL libc_fputwc_unlocked)(char32_t wc, FILE *__restrict stream) THROWS(...);
/* For use with `format_printf()' and friends: Prints to a `FILE *' closure argument */
INTDEF NONNULL((1, 2)) ssize_t (LIBDCALL libd_file_wprinter)(void *arg, char16_t const *__restrict data, size_t datalen) THROWS(...);
/* For use with `format_printf()' and friends: Prints to a `FILE *' closure argument */
INTDEF NONNULL((1, 2)) ssize_t (LIBKCALL libc_file_wprinter)(void *arg, char32_t const *__restrict data, size_t datalen) THROWS(...);
/* Same as `file_wprinter()', but performs I/O without acquiring a lock to `($FILE *)ARG' */
INTDEF NONNULL((1, 2)) ssize_t (LIBDCALL libd_file_wprinter_unlocked)(void *arg, char16_t const *__restrict data, size_t datalen) THROWS(...);
/* Same as `file_wprinter()', but performs I/O without acquiring a lock to `($FILE *)ARG' */
INTDEF NONNULL((1, 2)) ssize_t (LIBKCALL libc_file_wprinter_unlocked)(void *arg, char32_t const *__restrict data, size_t datalen) THROWS(...);
INTDEF NONNULL((2)) wint_t NOTHROW_NCX(LIBDCALL libd__ungetwc_nolock)(wint_t ch, FILE *__restrict stream);
INTDEF NONNULL((2)) wint_t NOTHROW_NCX(LIBKCALL libc_ungetwc_unlocked)(wint_t ch, FILE *__restrict stream);
INTDEF WUNUSED ATTR_LIBC_WSCANF(2, 0) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (LIBDCALL libd_vfwscanf_unlocked)(FILE *__restrict stream, char16_t const *__restrict format, va_list args) THROWS(...);
INTDEF WUNUSED ATTR_LIBC_WSCANF(2, 0) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (LIBKCALL libc_vfwscanf_unlocked)(FILE *__restrict stream, char32_t const *__restrict format, va_list args) THROWS(...);
INTDEF char16_t *NOTHROW_NCX(LIBDCALL libd__wcserror)(int errno_value);
INTDEF char32_t *NOTHROW_NCX(LIBKCALL libc__wcserror)(int errno_value);
INTDEF errno_t NOTHROW_NCX(LIBDCALL libd__wcserror_s)(char16_t *buf, size_t bufsize, int errno_value);
INTDEF errno_t NOTHROW_NCX(LIBKCALL libc__wcserror_s)(char32_t *buf, size_t bufsize, int errno_value);
INTDEF char16_t *NOTHROW_NCX(LIBDCALL libd___wcserror)(char16_t const *message);
INTDEF char32_t *NOTHROW_NCX(LIBKCALL libc___wcserror)(char32_t const *message);
INTDEF errno_t NOTHROW_NCX(LIBDCALL libd___wcserror_s)(char16_t *buf, size_t bufsize, char16_t const *message);
INTDEF errno_t NOTHROW_NCX(LIBKCALL libc___wcserror_s)(char32_t *buf, size_t bufsize, char32_t const *message);
INTDEF WUNUSED NONNULL((1, 2)) FILE *NOTHROW_NCX(LIBDCALL libd__wfsopen)(char16_t const *filename, char16_t const *mode, __STDC_INT_AS_UINT_T sh_flag);
INTDEF WUNUSED NONNULL((1, 2)) FILE *NOTHROW_NCX(LIBKCALL libc__wfsopen)(char32_t const *filename, char32_t const *mode, __STDC_INT_AS_UINT_T sh_flag);
INTDEF WUNUSED NONNULL((2)) FILE *NOTHROW_NCX(LIBDCALL libd__wfdopen)(fd_t fd, char16_t const *mode);
INTDEF WUNUSED NONNULL((2)) FILE *NOTHROW_NCX(LIBKCALL libc__wfdopen)(fd_t fd, char32_t const *mode);
INTDEF NONNULL((1, 2, 3)) errno_t NOTHROW_NCX(LIBDCALL libd__wfopen_s)(FILE **pstream, char16_t const *filename, char16_t const *mode);
INTDEF NONNULL((1, 2, 3)) errno_t NOTHROW_NCX(LIBKCALL libc__wfopen_s)(FILE **pstream, char32_t const *filename, char32_t const *mode);
INTDEF NONNULL((1, 2, 3)) errno_t NOTHROW_NCX(LIBDCALL libd__wfreopen_s)(FILE **pstream, char16_t const *filename, char16_t const *mode, FILE *stream);
INTDEF NONNULL((1, 2, 3)) errno_t NOTHROW_NCX(LIBKCALL libc__wfreopen_s)(FILE **pstream, char32_t const *filename, char32_t const *mode, FILE *stream);
INTDEF WUNUSED char16_t *NOTHROW_NCX(LIBDCALL libd__wtempnam)(char16_t const *directory, char16_t const *file_prefix);
INTDEF WUNUSED char32_t *NOTHROW_NCX(LIBKCALL libc__wtempnam)(char32_t const *directory, char32_t const *file_prefix);
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBDCALL libd__wtmpnam_s)(char16_t *dst, size_t wchar_count);
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBKCALL libc__wtmpnam_s)(char32_t *dst, size_t wchar_count);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_USER_WCHAR_H */
