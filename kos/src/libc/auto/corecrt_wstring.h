/* HASH CRC-32:0xc910df5a */
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
#ifndef GUARD_LIBC_AUTO_CORECRT_WSTRING_H
#define GUARD_LIBC_AUTO_CORECRT_WSTRING_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <corecrt_wstring.h>

DECL_BEGIN

#ifndef __KERNEL__
INTDEF errno_t NOTHROW_NCX(LIBDCALL libd__wcsnset_s)(char16_t *__restrict buf, size_t buflen, char16_t ch, size_t maxlen);
INTDEF errno_t NOTHROW_NCX(LIBKCALL libc__wcsnset_s)(char32_t *__restrict buf, size_t buflen, char32_t ch, size_t maxlen);
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBDCALL libd__wcsset_s)(char16_t *dst, size_t dstsize, char16_t ch);
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBKCALL libc__wcsset_s)(char32_t *dst, size_t dstsize, char32_t ch);
INTDEF errno_t NOTHROW_NCX(LIBDCALL libd__wcslwr_s)(char16_t *buf, size_t buflen);
INTDEF errno_t NOTHROW_NCX(LIBKCALL libc__wcslwr_s)(char32_t *buf, size_t buflen);
INTDEF errno_t NOTHROW_NCX(LIBDCALL libd__wcsupr_s)(char16_t *buf, size_t buflen);
INTDEF errno_t NOTHROW_NCX(LIBKCALL libc__wcsupr_s)(char32_t *buf, size_t buflen);
INTDEF errno_t NOTHROW_NCX(LIBDCALL libd__wcslwr_s_l)(char16_t *buf, size_t buflen, locale_t locale);
INTDEF errno_t NOTHROW_NCX(LIBKCALL libc__wcslwr_s_l)(char32_t *buf, size_t buflen, locale_t locale);
INTDEF errno_t NOTHROW_NCX(LIBDCALL libd__wcsupr_s_l)(char16_t *buf, size_t buflen, locale_t locale);
INTDEF errno_t NOTHROW_NCX(LIBKCALL libc__wcsupr_s_l)(char32_t *buf, size_t buflen, locale_t locale);
INTDEF NONNULL((1, 3)) errno_t NOTHROW_NCX(LIBDCALL libd_wmemcpy_s)(char16_t *dst, rsize_t dstlength, char16_t const *src, rsize_t srclength);
INTDEF NONNULL((1, 3)) errno_t NOTHROW_NCX(LIBKCALL libc_wmemcpy_s)(char32_t *dst, rsize_t dstlength, char32_t const *src, rsize_t srclength);
INTDEF NONNULL((1, 3)) errno_t NOTHROW_NCX(LIBDCALL libd_wmemmove_s)(char16_t *dst, rsize_t dstlength, char16_t const *src, rsize_t srclength);
INTDEF NONNULL((1, 3)) errno_t NOTHROW_NCX(LIBKCALL libc_wmemmove_s)(char32_t *dst, rsize_t dstlength, char32_t const *src, rsize_t srclength);
/* >> wcscat_s(3) */
INTDEF errno_t NOTHROW_NCX(LIBDCALL libd_wcscat_s)(char16_t *dst, size_t dstsize, char16_t const *src);
/* >> wcscat_s(3) */
INTDEF errno_t NOTHROW_NCX(LIBKCALL libc_wcscat_s)(char32_t *dst, size_t dstsize, char32_t const *src);
/* >> wcscpy_s(3) */
INTDEF errno_t NOTHROW_NCX(LIBDCALL libd_wcscpy_s)(char16_t *dst, size_t dstsize, char16_t const *src);
/* >> wcscpy_s(3) */
INTDEF errno_t NOTHROW_NCX(LIBKCALL libc_wcscpy_s)(char32_t *dst, size_t dstsize, char32_t const *src);
/* >> wcsncat_s(3) */
INTDEF errno_t NOTHROW_NCX(LIBDCALL libd_wcsncat_s)(char16_t *dst, rsize_t dstsize, const char16_t *src, rsize_t maxlen);
/* >> wcsncat_s(3) */
INTDEF errno_t NOTHROW_NCX(LIBKCALL libc_wcsncat_s)(char32_t *dst, rsize_t dstsize, const char32_t *src, rsize_t maxlen);
/* >> wcsncpy_s(3) */
INTDEF errno_t NOTHROW_NCX(LIBDCALL libd_wcsncpy_s)(char16_t *dst, size_t dstsize, char16_t const *src, size_t maxlen);
/* >> wcsncpy_s(3) */
INTDEF errno_t NOTHROW_NCX(LIBKCALL libc_wcsncpy_s)(char32_t *dst, size_t dstsize, char32_t const *src, size_t maxlen);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_CORECRT_WSTRING_H */
