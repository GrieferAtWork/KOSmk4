/* HASH CRC-32:0x65f71ed */
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
#ifndef GUARD_LIBC_AUTO_DOSABI_WCTYPE_C
#define GUARD_LIBC_AUTO_DOSABI_WCTYPE_C 1

#include "../../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../wctype.h"

DECL_BEGIN

INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBDCALL libd_iswalnum)(wint_t wc) {
	return libc_iswalnum(wc);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBDCALL libd_iswalpha)(wint_t wc) {
	return libc_iswalpha(wc);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBDCALL libd_iswcntrl)(wint_t wc) {
	return libc_iswcntrl(wc);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBDCALL libd_iswdigit)(wint_t wc) {
	return libc_iswdigit(wc);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBDCALL libd_iswgraph)(wint_t wc) {
	return libc_iswgraph(wc);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBDCALL libd_iswlower)(wint_t wc) {
	return libc_iswlower(wc);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBDCALL libd_iswprint)(wint_t wc) {
	return libc_iswprint(wc);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBDCALL libd_iswpunct)(wint_t wc) {
	return libc_iswpunct(wc);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBDCALL libd_iswspace)(wint_t wc) {
	return libc_iswspace(wc);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBDCALL libd_iswupper)(wint_t wc) {
	return libc_iswupper(wc);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBDCALL libd_iswxdigit)(wint_t wc) {
	return libc_iswxdigit(wc);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs") ATTR_PURE WUNUSED NONNULL((1)) wctrans_t
NOTHROW_NCX(LIBDCALL libd_wctrans)(char const *prop) {
	return libc_wctrans(prop);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs") ATTR_CONST WUNUSED wint_t
NOTHROW_NCX(LIBDCALL libd_towctrans)(wint_t wc,
                                     wctrans_t desc) {
	return libc_towctrans(wc, desc);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs") ATTR_PURE WUNUSED NONNULL((1)) wctype_t
NOTHROW_NCX(LIBDCALL libd_wctype)(char const *prop) {
	return libc_wctype(prop);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs") ATTR_CONST WUNUSED int
NOTHROW_NCX(LIBDCALL libd_iswctype)(wint_t wc,
                                    wctype_t desc) {
	return libc_iswctype(wc, desc);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBDCALL libd_iswblank)(wint_t wc) {
	return libc_iswblank(wc);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.ctype") ATTR_CONST WUNUSED wint_t
NOTHROW(LIBDCALL libd_towlower)(wint_t wc) {
	return libc_towlower(wc);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.ctype") ATTR_CONST WUNUSED wint_t
NOTHROW(LIBDCALL libd_towupper)(wint_t wc) {
	return libc_towupper(wc);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBDCALL libd_iswascii)(wint_t wc) {
	return libc_iswascii(wc);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.ctype") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBDCALL libd_iswalnum_l)(wint_t wc,
                                      locale_t locale) {
	return libc_iswalnum_l(wc, locale);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.ctype") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBDCALL libd_iswalpha_l)(wint_t wc,
                                      locale_t locale) {
	return libc_iswalpha_l(wc, locale);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.ctype") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBDCALL libd_iswcntrl_l)(wint_t wc,
                                      locale_t locale) {
	return libc_iswcntrl_l(wc, locale);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.ctype") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBDCALL libd_iswdigit_l)(wint_t wc,
                                      locale_t locale) {
	return libc_iswdigit_l(wc, locale);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.ctype") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBDCALL libd_iswgraph_l)(wint_t wc,
                                      locale_t locale) {
	return libc_iswgraph_l(wc, locale);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.ctype") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBDCALL libd_iswlower_l)(wint_t wc,
                                      locale_t locale) {
	return libc_iswlower_l(wc, locale);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.ctype") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBDCALL libd_iswprint_l)(wint_t wc,
                                      locale_t locale) {
	return libc_iswprint_l(wc, locale);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.ctype") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBDCALL libd_iswpunct_l)(wint_t wc,
                                      locale_t locale) {
	return libc_iswpunct_l(wc, locale);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.ctype") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBDCALL libd_iswspace_l)(wint_t wc,
                                      locale_t locale) {
	return libc_iswspace_l(wc, locale);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.ctype") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBDCALL libd_iswupper_l)(wint_t wc,
                                      locale_t locale) {
	return libc_iswupper_l(wc, locale);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.ctype") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBDCALL libd_iswxdigit_l)(wint_t wc,
                                       locale_t locale) {
	return libc_iswxdigit_l(wc, locale);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.ctype") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBDCALL libd_iswblank_l)(wint_t wc,
                                      locale_t locale) {
	return libc_iswblank_l(wc, locale);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.ctype") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBDCALL libd_iswctype_l)(wint_t wc,
                                      wctype_t type,
                                      locale_t locale) {
	return libc_iswctype_l(wc, type, locale);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.ctype") ATTR_PURE WUNUSED wint_t
NOTHROW_NCX(LIBDCALL libd_towupper_l)(wint_t wc,
                                      locale_t locale) {
	return libc_towupper_l(wc, locale);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.ctype") ATTR_PURE WUNUSED wint_t
NOTHROW_NCX(LIBDCALL libd_towlower_l)(wint_t wc,
                                      locale_t locale) {
	return libc_towlower_l(wc, locale);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.mbs") WUNUSED NONNULL((1)) wctype_t
NOTHROW_NCX(LIBDCALL libd_wctype_l)(char const *prop,
                                    locale_t locale) {
	return libc_wctype_l(prop, locale);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.mbs") WUNUSED NONNULL((1)) wctrans_t
NOTHROW_NCX(LIBDCALL libd_wctrans_l)(char const *prop,
                                     locale_t locale) {
	return libc_wctrans_l(prop, locale);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.mbs") WUNUSED wint_t
NOTHROW_NCX(LIBDCALL libd_towctrans_l)(wint_t wc,
                                       wctrans_t desc,
                                       locale_t locale) {
	return libc_towctrans_l(wc, desc, locale);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs") ATTR_CONST WUNUSED int
NOTHROW_NCX(LIBDCALL libd_isleadbyte)(int wc) {
	return libc_isleadbyte(wc);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.mbs") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBDCALL libd__isleadbyte_l)(int wc,
                                         locale_t locale) {
	return libc__isleadbyte_l(wc, locale);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs") ATTR_CONST WUNUSED int
NOTHROW_NCX(LIBDCALL libd___iswcsymf)(wint_t wc) {
	return libc___iswcsymf(wc);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs") ATTR_CONST WUNUSED int
NOTHROW_NCX(LIBDCALL libd___iswcsym)(wint_t wc) {
	return libc___iswcsym(wc);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.mbs") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBDCALL libd__iswcsymf_l)(wint_t wc,
                                       locale_t locale) {
	return libc__iswcsymf_l(wc, locale);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.mbs") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBDCALL libd__iswcsym_l)(wint_t wc,
                                      locale_t locale) {
	return libc__iswcsym_l(wc, locale);
}

DECL_END

DEFINE_PUBLIC_ALIAS(DOS$iswalnum, libd_iswalnum);
DEFINE_PUBLIC_ALIAS(DOS$iswalpha, libd_iswalpha);
DEFINE_PUBLIC_ALIAS(DOS$iswcntrl, libd_iswcntrl);
DEFINE_PUBLIC_ALIAS(DOS$iswdigit, libd_iswdigit);
DEFINE_PUBLIC_ALIAS(DOS$iswgraph, libd_iswgraph);
DEFINE_PUBLIC_ALIAS(DOS$iswlower, libd_iswlower);
DEFINE_PUBLIC_ALIAS(DOS$iswprint, libd_iswprint);
DEFINE_PUBLIC_ALIAS(DOS$iswpunct, libd_iswpunct);
DEFINE_PUBLIC_ALIAS(DOS$iswspace, libd_iswspace);
DEFINE_PUBLIC_ALIAS(DOS$iswupper, libd_iswupper);
DEFINE_PUBLIC_ALIAS(DOS$iswxdigit, libd_iswxdigit);
DEFINE_PUBLIC_ALIAS(DOS$wctrans, libd_wctrans);
DEFINE_PUBLIC_ALIAS(DOS$__towctrans, libd_towctrans);
DEFINE_PUBLIC_ALIAS(DOS$towctrans, libd_towctrans);
DEFINE_PUBLIC_ALIAS(DOS$wctype, libd_wctype);
DEFINE_PUBLIC_ALIAS(DOS$is_wctype, libd_iswctype);
DEFINE_PUBLIC_ALIAS(DOS$__iswctype, libd_iswctype);
DEFINE_PUBLIC_ALIAS(DOS$iswctype, libd_iswctype);
DEFINE_PUBLIC_ALIAS(DOS$iswblank, libd_iswblank);
DEFINE_PUBLIC_ALIAS(DOS$towlower, libd_towlower);
DEFINE_PUBLIC_ALIAS(DOS$towupper, libd_towupper);
DEFINE_PUBLIC_ALIAS(DOS$iswascii, libd_iswascii);
DEFINE_PUBLIC_ALIAS(DOS$_iswalnum_l, libd_iswalnum_l);
DEFINE_PUBLIC_ALIAS(DOS$__iswalnum_l, libd_iswalnum_l);
DEFINE_PUBLIC_ALIAS(DOS$iswalnum_l, libd_iswalnum_l);
DEFINE_PUBLIC_ALIAS(DOS$_iswalpha_l, libd_iswalpha_l);
DEFINE_PUBLIC_ALIAS(DOS$__iswalpha_l, libd_iswalpha_l);
DEFINE_PUBLIC_ALIAS(DOS$iswalpha_l, libd_iswalpha_l);
DEFINE_PUBLIC_ALIAS(DOS$_iswcntrl_l, libd_iswcntrl_l);
DEFINE_PUBLIC_ALIAS(DOS$__iswcntrl_l, libd_iswcntrl_l);
DEFINE_PUBLIC_ALIAS(DOS$iswcntrl_l, libd_iswcntrl_l);
DEFINE_PUBLIC_ALIAS(DOS$_iswdigit_l, libd_iswdigit_l);
DEFINE_PUBLIC_ALIAS(DOS$__iswdigit_l, libd_iswdigit_l);
DEFINE_PUBLIC_ALIAS(DOS$iswdigit_l, libd_iswdigit_l);
DEFINE_PUBLIC_ALIAS(DOS$_iswgraph_l, libd_iswgraph_l);
DEFINE_PUBLIC_ALIAS(DOS$__iswgraph_l, libd_iswgraph_l);
DEFINE_PUBLIC_ALIAS(DOS$iswgraph_l, libd_iswgraph_l);
DEFINE_PUBLIC_ALIAS(DOS$_iswlower_l, libd_iswlower_l);
DEFINE_PUBLIC_ALIAS(DOS$__iswlower_l, libd_iswlower_l);
DEFINE_PUBLIC_ALIAS(DOS$iswlower_l, libd_iswlower_l);
DEFINE_PUBLIC_ALIAS(DOS$_iswprint_l, libd_iswprint_l);
DEFINE_PUBLIC_ALIAS(DOS$__iswprint_l, libd_iswprint_l);
DEFINE_PUBLIC_ALIAS(DOS$iswprint_l, libd_iswprint_l);
DEFINE_PUBLIC_ALIAS(DOS$_iswpunct_l, libd_iswpunct_l);
DEFINE_PUBLIC_ALIAS(DOS$__iswpunct_l, libd_iswpunct_l);
DEFINE_PUBLIC_ALIAS(DOS$iswpunct_l, libd_iswpunct_l);
DEFINE_PUBLIC_ALIAS(DOS$_iswspace_l, libd_iswspace_l);
DEFINE_PUBLIC_ALIAS(DOS$__iswspace_l, libd_iswspace_l);
DEFINE_PUBLIC_ALIAS(DOS$iswspace_l, libd_iswspace_l);
DEFINE_PUBLIC_ALIAS(DOS$_iswupper_l, libd_iswupper_l);
DEFINE_PUBLIC_ALIAS(DOS$__iswupper_l, libd_iswupper_l);
DEFINE_PUBLIC_ALIAS(DOS$iswupper_l, libd_iswupper_l);
DEFINE_PUBLIC_ALIAS(DOS$_iswxdigit_l, libd_iswxdigit_l);
DEFINE_PUBLIC_ALIAS(DOS$__iswxdigit_l, libd_iswxdigit_l);
DEFINE_PUBLIC_ALIAS(DOS$iswxdigit_l, libd_iswxdigit_l);
DEFINE_PUBLIC_ALIAS(DOS$_iswblank_l, libd_iswblank_l);
DEFINE_PUBLIC_ALIAS(DOS$__iswblank_l, libd_iswblank_l);
DEFINE_PUBLIC_ALIAS(DOS$iswblank_l, libd_iswblank_l);
DEFINE_PUBLIC_ALIAS(DOS$_iswctype_l, libd_iswctype_l);
DEFINE_PUBLIC_ALIAS(DOS$__iswctype_l, libd_iswctype_l);
DEFINE_PUBLIC_ALIAS(DOS$iswctype_l, libd_iswctype_l);
DEFINE_PUBLIC_ALIAS(DOS$_towupper_l, libd_towupper_l);
DEFINE_PUBLIC_ALIAS(DOS$__towupper_l, libd_towupper_l);
DEFINE_PUBLIC_ALIAS(DOS$towupper_l, libd_towupper_l);
DEFINE_PUBLIC_ALIAS(DOS$_towlower_l, libd_towlower_l);
DEFINE_PUBLIC_ALIAS(DOS$__towlower_l, libd_towlower_l);
DEFINE_PUBLIC_ALIAS(DOS$towlower_l, libd_towlower_l);
DEFINE_PUBLIC_ALIAS(DOS$__wctype_l, libd_wctype_l);
DEFINE_PUBLIC_ALIAS(DOS$wctype_l, libd_wctype_l);
DEFINE_PUBLIC_ALIAS(DOS$__wctrans_l, libd_wctrans_l);
DEFINE_PUBLIC_ALIAS(DOS$wctrans_l, libd_wctrans_l);
DEFINE_PUBLIC_ALIAS(DOS$__towctrans_l, libd_towctrans_l);
DEFINE_PUBLIC_ALIAS(DOS$towctrans_l, libd_towctrans_l);
DEFINE_PUBLIC_ALIAS(DOS$isleadbyte, libd_isleadbyte);
DEFINE_PUBLIC_ALIAS(DOS$_isleadbyte_l, libd__isleadbyte_l);
DEFINE_PUBLIC_ALIAS(DOS$__iswcsymf, libd___iswcsymf);
DEFINE_PUBLIC_ALIAS(DOS$__iswcsym, libd___iswcsym);
DEFINE_PUBLIC_ALIAS(DOS$_iswcsymf_l, libd__iswcsymf_l);
DEFINE_PUBLIC_ALIAS(DOS$_iswcsym_l, libd__iswcsym_l);

#endif /* !GUARD_LIBC_AUTO_DOSABI_WCTYPE_C */
