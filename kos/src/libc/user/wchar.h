/* HASH CRC-32:0xc5a2d124 */
/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
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
/* >> fgetwc(3), getwc(3), fgetwc_unlocked(3), getwc_unlocked(3) */
INTDEF ATTR_INOUT(1) wint16_t NOTHROW_CB_NCX(LIBDCALL libd_fgetwc)(FILE *__restrict stream);
/* >> fgetwc(3), getwc(3), fgetwc_unlocked(3), getwc_unlocked(3) */
INTDEF ATTR_INOUT(1) wint32_t NOTHROW_CB_NCX(LIBKCALL libc_fgetwc)(FILE *__restrict stream);
/* >> fputwc(3), putwc(3), fputwc_unlocked(3), putwc_unlocked(3) */
INTDEF ATTR_INOUT(2) wint16_t NOTHROW_CB_NCX(LIBDCALL libd_fputwc)(char16_t wc, FILE *stream);
/* >> fputwc(3), putwc(3), fputwc_unlocked(3), putwc_unlocked(3) */
INTDEF ATTR_INOUT(2) wint32_t NOTHROW_CB_NCX(LIBKCALL libc_fputwc)(char32_t wc, FILE *stream);
/* >> ungetwc(3), ungetwc_unlocked(3) */
INTDEF ATTR_INOUT(2) wint16_t NOTHROW_NCX(LIBDCALL libd_ungetwc)(wint16_t wc, FILE *stream);
/* >> ungetwc(3), ungetwc_unlocked(3) */
INTDEF ATTR_INOUT(2) wint32_t NOTHROW_NCX(LIBKCALL libc_ungetwc)(wint32_t wc, FILE *stream);
/* >> open_wmemstream(3) */
INTDEF FILE *NOTHROW_NCX(LIBDCALL libd_open_wmemstream)(char16_t **bufloc, size_t *sizeloc);
/* >> open_wmemstream(3) */
INTDEF FILE *NOTHROW_NCX(LIBKCALL libc_open_wmemstream)(char32_t **bufloc, size_t *sizeloc);
/* >> fgetwc(3), getwc(3), fgetwc_unlocked(3), getwc_unlocked(3) */
INTDEF ATTR_INOUT(1) wint16_t NOTHROW_CB_NCX(LIBDCALL libd_fgetwc_unlocked)(FILE *__restrict stream);
/* >> fgetwc(3), getwc(3), fgetwc_unlocked(3), getwc_unlocked(3) */
INTDEF ATTR_INOUT(1) wint32_t NOTHROW_CB_NCX(LIBKCALL libc_fgetwc_unlocked)(FILE *__restrict stream);
/* >> fputwc(3), putwc(3), fputwc_unlocked(3), putwc_unlocked(3) */
INTDEF ATTR_INOUT(2) wint16_t NOTHROW_CB_NCX(LIBDCALL libd_fputwc_unlocked)(char16_t wc, FILE *__restrict stream);
/* >> fputwc(3), putwc(3), fputwc_unlocked(3), putwc_unlocked(3) */
INTDEF ATTR_INOUT(2) wint32_t NOTHROW_CB_NCX(LIBKCALL libc_fputwc_unlocked)(char32_t wc, FILE *__restrict stream);
/* >> file_wprinter(3), file_wprinter_unlocked(3)
 * For use with `format_wprintf()' and friends: Prints to a `FILE *' closure argument */
INTDEF ATTR_INS(2, 3) NONNULL((1)) ssize_t NOTHROW_CB_NCX(LIBDCALL libd_file_wprinter)(void *arg, char16_t const *__restrict data, size_t datalen);
/* >> file_wprinter(3), file_wprinter_unlocked(3)
 * For use with `format_wprintf()' and friends: Prints to a `FILE *' closure argument */
INTDEF ATTR_INS(2, 3) NONNULL((1)) ssize_t NOTHROW_CB_NCX(LIBKCALL libc_file_wprinter)(void *arg, char32_t const *__restrict data, size_t datalen);
/* >> file_wprinter(3), file_wprinter_unlocked(3)
 * For use with `format_wprintf()' and friends: Prints to a `FILE *' closure argument */
INTDEF ATTR_INS(2, 3) NONNULL((1)) ssize_t NOTHROW_CB_NCX(LIBDCALL libd_file_wprinter_unlocked)(void *arg, char16_t const *__restrict data, size_t datalen);
/* >> file_wprinter(3), file_wprinter_unlocked(3)
 * For use with `format_wprintf()' and friends: Prints to a `FILE *' closure argument */
INTDEF ATTR_INS(2, 3) NONNULL((1)) ssize_t NOTHROW_CB_NCX(LIBKCALL libc_file_wprinter_unlocked)(void *arg, char32_t const *__restrict data, size_t datalen);
/* >> ungetwc(3), ungetwc_unlocked(3) */
INTDEF ATTR_INOUT(2) wint16_t NOTHROW_NCX(LIBDCALL libd_ungetwc_unlocked)(wint16_t ch, FILE *__restrict stream);
/* >> ungetwc(3), ungetwc_unlocked(3) */
INTDEF ATTR_INOUT(2) wint32_t NOTHROW_NCX(LIBKCALL libc_ungetwc_unlocked)(wint32_t ch, FILE *__restrict stream);
/* >> fgetwln(3) */
INTDEF WUNUSED ATTR_INOUT(1) ATTR_OUT_OPT(2) char16_t *NOTHROW_NCX(LIBDCALL libd_fgetwln)(FILE *__restrict stream, size_t *__restrict lenp);
/* >> fgetwln(3) */
INTDEF WUNUSED ATTR_INOUT(1) ATTR_OUT_OPT(2) char32_t *NOTHROW_NCX(LIBKCALL libc_fgetwln)(FILE *__restrict stream, size_t *__restrict lenp);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_USER_WCHAR_H */
