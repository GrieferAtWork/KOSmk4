/* HASH CRC-32:0xe23eb94f */
/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
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
INTDEF char16_t *NOTHROW_NCX(LIBDCALL libd__wcserror)(errno_t errno_value);
INTDEF char32_t *NOTHROW_NCX(LIBKCALL libc__wcserror)(errno_t errno_value);
INTDEF ATTR_OUTS(1, 2) errno_t NOTHROW_NCX(LIBDCALL libd__wcserror_s)(char16_t *buf, size_t buflen, errno_t errno_value);
INTDEF ATTR_OUTS(1, 2) errno_t NOTHROW_NCX(LIBKCALL libc__wcserror_s)(char32_t *buf, size_t buflen, errno_t errno_value);
INTDEF ATTR_IN_OPT(1) char16_t *NOTHROW_NCX(LIBDCALL libd___wcserror)(char16_t const *message);
INTDEF ATTR_IN_OPT(1) char32_t *NOTHROW_NCX(LIBKCALL libc___wcserror)(char32_t const *message);
INTDEF ATTR_IN_OPT(3) ATTR_OUTS(1, 2) errno_t NOTHROW_NCX(LIBDCALL libd___wcserror_s)(char16_t *buf, size_t buflen, char16_t const *message);
INTDEF ATTR_IN_OPT(3) ATTR_OUTS(1, 2) errno_t NOTHROW_NCX(LIBKCALL libc___wcserror_s)(char32_t *buf, size_t buflen, char32_t const *message);
INTDEF ATTR_INOUTS(1, 4) errno_t NOTHROW_NCX(LIBDCALL libd__wcsnset_s)(char16_t *__restrict buf, size_t buflen, char16_t ch, size_t maxlen);
INTDEF ATTR_INOUTS(1, 4) errno_t NOTHROW_NCX(LIBKCALL libc__wcsnset_s)(char32_t *__restrict buf, size_t buflen, char32_t ch, size_t maxlen);
INTDEF ATTR_INOUTS(1, 2) errno_t NOTHROW_NCX(LIBDCALL libd__wcsset_s)(char16_t *dst, size_t dstsize, char16_t ch);
INTDEF ATTR_INOUTS(1, 2) errno_t NOTHROW_NCX(LIBKCALL libc__wcsset_s)(char32_t *dst, size_t dstsize, char32_t ch);
INTDEF ATTR_INOUT_OPT(1) errno_t NOTHROW_NCX(LIBDCALL libd__wcslwr_s)(char16_t *buf, size_t buflen);
INTDEF ATTR_INOUT_OPT(1) errno_t NOTHROW_NCX(LIBKCALL libc__wcslwr_s)(char32_t *buf, size_t buflen);
INTDEF ATTR_INOUT_OPT(1) errno_t NOTHROW_NCX(LIBDCALL libd__wcsupr_s)(char16_t *buf, size_t buflen);
INTDEF ATTR_INOUT_OPT(1) errno_t NOTHROW_NCX(LIBKCALL libc__wcsupr_s)(char32_t *buf, size_t buflen);
INTDEF ATTR_INOUT_OPT(1) errno_t NOTHROW_NCX(LIBDCALL libd__wcslwr_s_l)(char16_t *buf, size_t buflen, locale_t locale);
INTDEF ATTR_INOUT_OPT(1) errno_t NOTHROW_NCX(LIBKCALL libc__wcslwr_s_l)(char32_t *buf, size_t buflen, locale_t locale);
INTDEF ATTR_INOUT_OPT(1) errno_t NOTHROW_NCX(LIBDCALL libd__wcsupr_s_l)(char16_t *buf, size_t buflen, locale_t locale);
INTDEF ATTR_INOUT_OPT(1) errno_t NOTHROW_NCX(LIBKCALL libc__wcsupr_s_l)(char32_t *buf, size_t buflen, locale_t locale);
INTDEF ATTR_INS(3, 4) ATTR_OUTS(1, 2) errno_t NOTHROW_NCX(LIBDCALL libd_wmemcpy_s)(char16_t *dst, rsize_t dstlength, char16_t const *src, rsize_t srclength);
INTDEF ATTR_INS(3, 4) ATTR_OUTS(1, 2) errno_t NOTHROW_NCX(LIBKCALL libc_wmemcpy_s)(char32_t *dst, rsize_t dstlength, char32_t const *src, rsize_t srclength);
INTDEF ATTR_INS(3, 4) ATTR_OUTS(1, 2) errno_t NOTHROW_NCX(LIBDCALL libd_wmemmove_s)(char16_t *dst, rsize_t dstlength, char16_t const *src, rsize_t srclength);
INTDEF ATTR_INS(3, 4) ATTR_OUTS(1, 2) errno_t NOTHROW_NCX(LIBKCALL libc_wmemmove_s)(char32_t *dst, rsize_t dstlength, char32_t const *src, rsize_t srclength);
/* >> wcscat_s(3) */
INTDEF ATTR_INOUT_OPT(1) ATTR_IN_OPT(3) errno_t NOTHROW_NCX(LIBDCALL libd_wcscat_s)(char16_t *dst, size_t dstsize, char16_t const *src);
/* >> wcscat_s(3) */
INTDEF ATTR_INOUT_OPT(1) ATTR_IN_OPT(3) errno_t NOTHROW_NCX(LIBKCALL libc_wcscat_s)(char32_t *dst, size_t dstsize, char32_t const *src);
/* >> wcscpy_s(3) */
INTDEF ATTR_IN_OPT(3) ATTR_OUTS(1, 2) errno_t NOTHROW_NCX(LIBDCALL libd_wcscpy_s)(char16_t *dst, size_t dstsize, char16_t const *src);
/* >> wcscpy_s(3) */
INTDEF ATTR_IN_OPT(3) ATTR_OUTS(1, 2) errno_t NOTHROW_NCX(LIBKCALL libc_wcscpy_s)(char32_t *dst, size_t dstsize, char32_t const *src);
/* >> wcsncat_s(3) */
INTDEF ATTR_INOUT_OPT(1) ATTR_IN_OPT(3) errno_t NOTHROW_NCX(LIBDCALL libd_wcsncat_s)(char16_t *dst, rsize_t dstsize, char16_t const *src, rsize_t maxlen);
/* >> wcsncat_s(3) */
INTDEF ATTR_INOUT_OPT(1) ATTR_IN_OPT(3) errno_t NOTHROW_NCX(LIBKCALL libc_wcsncat_s)(char32_t *dst, rsize_t dstsize, char32_t const *src, rsize_t maxlen);
/* >> wcsncpy_s(3) */
INTDEF ATTR_IN_OPT(3) ATTR_OUTS(1, 2) errno_t NOTHROW_NCX(LIBDCALL libd_wcsncpy_s)(char16_t *dst, size_t dstsize, char16_t const *src, size_t maxlen);
/* >> wcsncpy_s(3) */
INTDEF ATTR_IN_OPT(3) ATTR_OUTS(1, 2) errno_t NOTHROW_NCX(LIBKCALL libc_wcsncpy_s)(char32_t *dst, size_t dstsize, char32_t const *src, size_t maxlen);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_CORECRT_WSTRING_H */
