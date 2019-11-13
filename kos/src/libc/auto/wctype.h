/* HASH CRC-32:0x3e59fb7f */
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
#ifndef GUARD_LIBC_AUTO_WCTYPE_H
#define GUARD_LIBC_AUTO_WCTYPE_H 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include <wctype.h>

DECL_BEGIN

#ifndef __KERNEL__
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBCCALL libc_iswalnum)(wint_t wc);
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBCCALL libc_iswalpha)(wint_t wc);
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBCCALL libc_iswcntrl)(wint_t wc);
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBCCALL libc_iswdigit)(wint_t wc);
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBCCALL libc_iswgraph)(wint_t wc);
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBCCALL libc_iswlower)(wint_t wc);
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBCCALL libc_iswprint)(wint_t wc);
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBCCALL libc_iswpunct)(wint_t wc);
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBCCALL libc_iswspace)(wint_t wc);
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBCCALL libc_iswupper)(wint_t wc);
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBCCALL libc_iswxdigit)(wint_t wc);
INTDEF ATTR_PURE WUNUSED NONNULL((1)) wctrans_t NOTHROW_NCX(LIBCCALL libc_wctrans)(char const *prop);
INTDEF ATTR_CONST WUNUSED wint_t NOTHROW_NCX(LIBCCALL libc_towctrans)(wint_t wc, wctrans_t desc);
INTDEF ATTR_PURE WUNUSED NONNULL((1)) wctype_t NOTHROW_NCX(LIBCCALL libc_wctype)(char const *prop);
INTDEF ATTR_CONST WUNUSED int NOTHROW_NCX(LIBCCALL libc_iswctype)(wint_t wc, wctype_t desc);
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBCCALL libc_iswblank)(wint_t wc);
INTDEF ATTR_CONST WUNUSED wint_t NOTHROW(LIBCCALL libc_towlower)(wint_t wc);
INTDEF ATTR_CONST WUNUSED wint_t NOTHROW(LIBCCALL libc_towupper)(wint_t wc);
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBCCALL libc_iswascii)(wint_t wc);
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBCCALL libc_iswalnum_l)(wint_t wc, locale_t locale);
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBCCALL libc_iswalpha_l)(wint_t wc, locale_t locale);
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBCCALL libc_iswcntrl_l)(wint_t wc, locale_t locale);
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBCCALL libc_iswdigit_l)(wint_t wc, locale_t locale);
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBCCALL libc_iswgraph_l)(wint_t wc, locale_t locale);
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBCCALL libc_iswlower_l)(wint_t wc, locale_t locale);
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBCCALL libc_iswprint_l)(wint_t wc, locale_t locale);
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBCCALL libc_iswpunct_l)(wint_t wc, locale_t locale);
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBCCALL libc_iswspace_l)(wint_t wc, locale_t locale);
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBCCALL libc_iswupper_l)(wint_t wc, locale_t locale);
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBCCALL libc_iswxdigit_l)(wint_t wc, locale_t locale);
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBCCALL libc_iswblank_l)(wint_t wc, locale_t locale);
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBCCALL libc_iswctype_l)(wint_t wc, wctype_t type, locale_t locale);
INTDEF ATTR_PURE WUNUSED wint_t NOTHROW_NCX(LIBCCALL libc_towupper_l)(wint_t wc, locale_t locale);
INTDEF ATTR_PURE WUNUSED wint_t NOTHROW_NCX(LIBCCALL libc_towlower_l)(wint_t wc, locale_t locale);
INTDEF WUNUSED NONNULL((1)) wctype_t NOTHROW_NCX(LIBCCALL libc_wctype_l)(char const *prop, locale_t locale);
INTDEF WUNUSED NONNULL((1)) wctrans_t NOTHROW_NCX(LIBCCALL libc_wctrans_l)(char const *prop, locale_t locale);
INTDEF WUNUSED wint_t NOTHROW_NCX(LIBCCALL libc_towctrans_l)(wint_t wc, wctrans_t desc, locale_t locale);
#define libc__iswalnum_l libc_iswalnum_l
#define libc__iswalpha_l libc_iswalpha_l
#define libc__iswcntrl_l libc_iswcntrl_l
#define libc__iswdigit_l libc_iswdigit_l
#define libc__iswgraph_l libc_iswgraph_l
#define libc__iswlower_l libc_iswlower_l
#define libc__iswprint_l libc_iswprint_l
#define libc__iswpunct_l libc_iswpunct_l
#define libc__iswspace_l libc_iswspace_l
#define libc__iswupper_l libc_iswupper_l
#define libc__iswxdigit_l libc_iswxdigit_l
#define libc__iswblank_l libc_iswblank_l
#define libc__towupper_l libc_towupper_l
#define libc__towlower_l libc_towlower_l
#define libc__iswctype_l libc_iswctype_l
#define libc_is_wctype libc_iswctype
INTDEF ATTR_CONST WUNUSED int NOTHROW_NCX(LIBCCALL libc_isleadbyte)(int wc);
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBCCALL libc__isleadbyte_l)(int wc, locale_t locale);
INTDEF ATTR_CONST WUNUSED int NOTHROW_NCX(LIBCCALL libc___iswcsymf)(wint_t wc);
INTDEF ATTR_CONST WUNUSED int NOTHROW_NCX(LIBCCALL libc___iswcsym)(wint_t wc);
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBCCALL libc__iswcsymf_l)(wint_t wc, locale_t locale);
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBCCALL libc__iswcsym_l)(wint_t wc, locale_t locale);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_WCTYPE_H */
