/* HASH CRC-32:0x4da3628d */
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
#ifndef GUARD_LIBC_AUTO_WCTYPE_C
#define GUARD_LIBC_AUTO_WCTYPE_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "wctype.h"
#include "ctype.h"

DECL_BEGIN

#ifndef __KERNEL__
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.static.ctype.iswalnum") int
NOTHROW(LIBCCALL libc_iswalnum)(wint_t wc) {
#line 119 "kos/src/libc/magic/wctype.c"
	return libc_isalnum((int)wc);
}

INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.static.ctype.iswalpha") int
NOTHROW(LIBCCALL libc_iswalpha)(wint_t wc) {
#line 123 "kos/src/libc/magic/wctype.c"
	return libc_isalpha((int)wc);
}

INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.static.ctype.iswcntrl") int
NOTHROW(LIBCCALL libc_iswcntrl)(wint_t wc) {
#line 127 "kos/src/libc/magic/wctype.c"
	return libc_iscntrl((int)wc);
}

INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.static.ctype.iswdigit") int
NOTHROW(LIBCCALL libc_iswdigit)(wint_t wc) {
#line 131 "kos/src/libc/magic/wctype.c"
	return libc_isdigit((int)wc);
}

INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.static.ctype.iswgraph") int
NOTHROW(LIBCCALL libc_iswgraph)(wint_t wc) {
#line 135 "kos/src/libc/magic/wctype.c"
	return libc_isgraph((int)wc);
}

INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.static.ctype.iswlower") int
NOTHROW(LIBCCALL libc_iswlower)(wint_t wc) {
#line 139 "kos/src/libc/magic/wctype.c"
	return libc_islower((int)wc);
}

INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.static.ctype.iswprint") int
NOTHROW(LIBCCALL libc_iswprint)(wint_t wc) {
#line 143 "kos/src/libc/magic/wctype.c"
	return libc_isprint((int)wc);
}

INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.static.ctype.iswpunct") int
NOTHROW(LIBCCALL libc_iswpunct)(wint_t wc) {
#line 147 "kos/src/libc/magic/wctype.c"
	return libc_ispunct((int)wc);
}

INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.static.ctype.iswspace") int
NOTHROW(LIBCCALL libc_iswspace)(wint_t wc) {
#line 151 "kos/src/libc/magic/wctype.c"
	return libc_isspace((int)wc);
}

INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.static.ctype.iswupper") int
NOTHROW(LIBCCALL libc_iswupper)(wint_t wc) {
#line 155 "kos/src/libc/magic/wctype.c"
	return libc_isupper((int)wc);
}

INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.static.ctype.iswxdigit") int
NOTHROW(LIBCCALL libc_iswxdigit)(wint_t wc) {
#line 159 "kos/src/libc/magic/wctype.c"
	return libc_isdigit((int)wc);
}

INTERN WUNUSED NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.static.mbs.wctrans") wctrans_t
NOTHROW_NCX(LIBCCALL libc_wctrans)(char const *prop) {
#line 166 "kos/src/libc/magic/wctype.c"
	/* TODO */
	return 0;
}

INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.static.mbs.towctrans") wint_t
NOTHROW_NCX(LIBCCALL libc_towctrans)(wint_t wc,
                                     wctrans_t desc) {
#line 171 "kos/src/libc/magic/wctype.c"
	/* TODO */
	return 0;
}

INTERN WUNUSED NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.static.mbs.wctype") wctype_t
NOTHROW_NCX(LIBCCALL libc_wctype)(char const *prop) {
#line 178 "kos/src/libc/magic/wctype.c"
	/* TODO */
	return 0;
}

INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.static.mbs.iswctype") int
NOTHROW_NCX(LIBCCALL libc_iswctype)(wint_t wc,
                                    wctype_t desc) {
#line 183 "kos/src/libc/magic/wctype.c"
	/* TODO */
	return 0;
}

INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.static.ctype.iswblank") int
NOTHROW(LIBCCALL libc_iswblank)(wint_t wc) {
#line 191 "kos/src/libc/magic/wctype.c"
	return libc_isblank((int)wc);
}

INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.static.ctype.towlower") wint_t
NOTHROW(LIBCCALL libc_towlower)(wint_t wc) {
#line 197 "kos/src/libc/magic/wctype.c"
	return (wint_t)libc_tolower((int)wc);
}

INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.static.ctype.towupper") wint_t
NOTHROW(LIBCCALL libc_towupper)(wint_t wc) {
#line 201 "kos/src/libc/magic/wctype.c"
	return (wint_t)libc_toupper((int)wc);
}

INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.static.ctype.iswascii") int
NOTHROW(LIBCCALL libc_iswascii)(wint_t wc) {
#line 209 "kos/src/libc/magic/wctype.c"
	return (unsigned int)wc <= 0x7f;
}

INTERN ATTR_PURE WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.locale.ctype.iswalnum_l") int
NOTHROW_NCX(LIBCCALL libc_iswalnum_l)(wint_t wc,
                                      locale_t locale) {
#line 220 "kos/src/libc/magic/wctype.c"
	(void)locale;
	return libc_iswalnum(wc);
}

INTERN ATTR_PURE WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.locale.ctype.iswalpha_l") int
NOTHROW_NCX(LIBCCALL libc_iswalpha_l)(wint_t wc,
                                      locale_t locale) {
#line 226 "kos/src/libc/magic/wctype.c"
	(void)locale;
	return libc_iswalpha(wc);
}

INTERN ATTR_PURE WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.locale.ctype.iswcntrl_l") int
NOTHROW_NCX(LIBCCALL libc_iswcntrl_l)(wint_t wc,
                                      locale_t locale) {
#line 232 "kos/src/libc/magic/wctype.c"
	(void)locale;
	return libc_iswcntrl(wc);
}

INTERN ATTR_PURE WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.locale.ctype.iswdigit_l") int
NOTHROW_NCX(LIBCCALL libc_iswdigit_l)(wint_t wc,
                                      locale_t locale) {
#line 238 "kos/src/libc/magic/wctype.c"
	(void)locale;
	return libc_iswdigit(wc);
}

INTERN ATTR_PURE WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.locale.ctype.iswgraph_l") int
NOTHROW_NCX(LIBCCALL libc_iswgraph_l)(wint_t wc,
                                      locale_t locale) {
#line 244 "kos/src/libc/magic/wctype.c"
	(void)locale;
	return libc_iswgraph(wc);
}

INTERN ATTR_PURE WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.locale.ctype.iswlower_l") int
NOTHROW_NCX(LIBCCALL libc_iswlower_l)(wint_t wc,
                                      locale_t locale) {
#line 250 "kos/src/libc/magic/wctype.c"
	(void)locale;
	return libc_iswlower(wc);
}

INTERN ATTR_PURE WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.locale.ctype.iswprint_l") int
NOTHROW_NCX(LIBCCALL libc_iswprint_l)(wint_t wc,
                                      locale_t locale) {
#line 256 "kos/src/libc/magic/wctype.c"
	(void)locale;
	return libc_iswprint(wc);
}

INTERN ATTR_PURE WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.locale.ctype.iswpunct_l") int
NOTHROW_NCX(LIBCCALL libc_iswpunct_l)(wint_t wc,
                                      locale_t locale) {
#line 262 "kos/src/libc/magic/wctype.c"
	(void)locale;
	return libc_iswpunct(wc);
}

INTERN ATTR_PURE WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.locale.ctype.iswspace_l") int
NOTHROW_NCX(LIBCCALL libc_iswspace_l)(wint_t wc,
                                      locale_t locale) {
#line 268 "kos/src/libc/magic/wctype.c"
	(void)locale;
	return libc_iswspace(wc);
}

INTERN ATTR_PURE WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.locale.ctype.iswupper_l") int
NOTHROW_NCX(LIBCCALL libc_iswupper_l)(wint_t wc,
                                      locale_t locale) {
#line 274 "kos/src/libc/magic/wctype.c"
	(void)locale;
	return libc_iswupper(wc);
}

INTERN ATTR_PURE WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.locale.ctype.iswxdigit_l") int
NOTHROW_NCX(LIBCCALL libc_iswxdigit_l)(wint_t wc,
                                       locale_t locale) {
#line 280 "kos/src/libc/magic/wctype.c"
	(void)locale;
	return libc_iswxdigit(wc);
}

INTERN ATTR_PURE WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.locale.ctype.iswblank_l") int
NOTHROW_NCX(LIBCCALL libc_iswblank_l)(wint_t wc,
                                      locale_t locale) {
#line 286 "kos/src/libc/magic/wctype.c"
	(void)locale;
	return libc_iswblank(wc);
}

INTERN ATTR_PURE WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.locale.ctype.iswctype_l") int
NOTHROW_NCX(LIBCCALL libc_iswctype_l)(wint_t wc,
                                      wctype_t type,
                                      locale_t locale) {
#line 292 "kos/src/libc/magic/wctype.c"
	(void)locale;
	return libc_iswctype(wc, type);
}

INTERN ATTR_PURE WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.locale.ctype.towupper_l") wint_t
NOTHROW_NCX(LIBCCALL libc_towupper_l)(wint_t wc,
                                      locale_t locale) {
#line 298 "kos/src/libc/magic/wctype.c"
	(void)locale;
	return libc_towupper(wc);
}

INTERN ATTR_PURE WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.locale.ctype.towlower_l") wint_t
NOTHROW_NCX(LIBCCALL libc_towlower_l)(wint_t wc,
                                      locale_t locale) {
#line 304 "kos/src/libc/magic/wctype.c"
	(void)locale;
	return libc_towlower(wc);
}

INTERN WUNUSED NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.locale.mbs.wctype_l") wctype_t
NOTHROW_NCX(LIBCCALL libc_wctype_l)(char const *prop,
                                    locale_t locale) {
#line 311 "kos/src/libc/magic/wctype.c"
	(void)locale;
	return libc_wctype(prop);
}

INTERN WUNUSED NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.locale.mbs.wctrans_l") wctrans_t
NOTHROW_NCX(LIBCCALL libc_wctrans_l)(char const *prop,
                                     locale_t locale) {
#line 317 "kos/src/libc/magic/wctype.c"
	(void)locale;
	return libc_wctrans(prop);
}

INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.locale.mbs.towctrans_l") wint_t
NOTHROW_NCX(LIBCCALL libc_towctrans_l)(wint_t wc,
                                       wctrans_t desc,
                                       locale_t locale) {
#line 323 "kos/src/libc/magic/wctype.c"
	(void)locale;
	return libc_towctrans(wc, desc);
}

INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.static.mbs.isleadbyte") int
NOTHROW_NCX(LIBCCALL libc_isleadbyte)(int wc) {
#line 361 "kos/src/libc/magic/wctype.c"
	return wc >= 192 && wc <= 255;
}

INTERN ATTR_PURE WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.locale.mbs._isleadbyte_l") int
NOTHROW_NCX(LIBCCALL libc__isleadbyte_l)(int wc,
                                         locale_t locale) {
#line 366 "kos/src/libc/magic/wctype.c"
	(void)locale;
	return libc_isleadbyte(wc);
}

INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.static.mbs.__iswcsymf") int
NOTHROW_NCX(LIBCCALL libc___iswcsymf)(wint_t wc) {
#line 372 "kos/src/libc/magic/wctype.c"
	return libc_iswalpha(wc) || wc == '_' || wc == '$';
}

INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.static.mbs.__iswcsym") int
NOTHROW_NCX(LIBCCALL libc___iswcsym)(wint_t wc) {
#line 376 "kos/src/libc/magic/wctype.c"
	return libc_iswalnum(wc) || wc == '_' || wc == '$';
}

INTERN ATTR_PURE WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.locale.mbs._iswcsymf_l") int
NOTHROW_NCX(LIBCCALL libc__iswcsymf_l)(wint_t wc,
                                       locale_t locale) {
#line 383 "kos/src/libc/magic/wctype.c"
	return libc_iswalpha_l(wc, locale) || wc == '_' || wc == '$';
}

INTERN ATTR_PURE WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.locale.mbs._iswcsym_l") int
NOTHROW_NCX(LIBCCALL libc__iswcsym_l)(wint_t wc,
                                      locale_t locale) {
#line 387 "kos/src/libc/magic/wctype.c"
	return libc_iswalnum_l(wc, locale) || wc == '_' || wc == '$';
}

#endif /* !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_WEAK_ALIAS(iswalnum, libc_iswalnum);
DEFINE_PUBLIC_WEAK_ALIAS(iswalpha, libc_iswalpha);
DEFINE_PUBLIC_WEAK_ALIAS(iswcntrl, libc_iswcntrl);
DEFINE_PUBLIC_WEAK_ALIAS(iswdigit, libc_iswdigit);
DEFINE_PUBLIC_WEAK_ALIAS(iswgraph, libc_iswgraph);
DEFINE_PUBLIC_WEAK_ALIAS(iswlower, libc_iswlower);
DEFINE_PUBLIC_WEAK_ALIAS(iswprint, libc_iswprint);
DEFINE_PUBLIC_WEAK_ALIAS(iswpunct, libc_iswpunct);
DEFINE_PUBLIC_WEAK_ALIAS(iswspace, libc_iswspace);
DEFINE_PUBLIC_WEAK_ALIAS(iswupper, libc_iswupper);
DEFINE_PUBLIC_WEAK_ALIAS(iswxdigit, libc_iswxdigit);
DEFINE_PUBLIC_WEAK_ALIAS(wctrans, libc_wctrans);
DEFINE_PUBLIC_WEAK_ALIAS(towctrans, libc_towctrans);
DEFINE_PUBLIC_WEAK_ALIAS(__towctrans, libc_towctrans);
DEFINE_PUBLIC_WEAK_ALIAS(wctype, libc_wctype);
DEFINE_PUBLIC_WEAK_ALIAS(iswctype, libc_iswctype);
DEFINE_PUBLIC_WEAK_ALIAS(__iswctype, libc_iswctype);
DEFINE_PUBLIC_WEAK_ALIAS(is_wctype, libc_iswctype);
DEFINE_PUBLIC_WEAK_ALIAS(iswblank, libc_iswblank);
DEFINE_PUBLIC_WEAK_ALIAS(towlower, libc_towlower);
DEFINE_PUBLIC_WEAK_ALIAS(towupper, libc_towupper);
DEFINE_PUBLIC_WEAK_ALIAS(iswascii, libc_iswascii);
DEFINE_PUBLIC_WEAK_ALIAS(iswalnum_l, libc_iswalnum_l);
DEFINE_PUBLIC_WEAK_ALIAS(__iswalnum_l, libc_iswalnum_l);
DEFINE_PUBLIC_WEAK_ALIAS(_iswalnum_l, libc_iswalnum_l);
DEFINE_PUBLIC_WEAK_ALIAS(iswalpha_l, libc_iswalpha_l);
DEFINE_PUBLIC_WEAK_ALIAS(__iswalpha_l, libc_iswalpha_l);
DEFINE_PUBLIC_WEAK_ALIAS(_iswalpha_l, libc_iswalpha_l);
DEFINE_PUBLIC_WEAK_ALIAS(iswcntrl_l, libc_iswcntrl_l);
DEFINE_PUBLIC_WEAK_ALIAS(__iswcntrl_l, libc_iswcntrl_l);
DEFINE_PUBLIC_WEAK_ALIAS(_iswcntrl_l, libc_iswcntrl_l);
DEFINE_PUBLIC_WEAK_ALIAS(iswdigit_l, libc_iswdigit_l);
DEFINE_PUBLIC_WEAK_ALIAS(__iswdigit_l, libc_iswdigit_l);
DEFINE_PUBLIC_WEAK_ALIAS(_iswdigit_l, libc_iswdigit_l);
DEFINE_PUBLIC_WEAK_ALIAS(iswgraph_l, libc_iswgraph_l);
DEFINE_PUBLIC_WEAK_ALIAS(__iswgraph_l, libc_iswgraph_l);
DEFINE_PUBLIC_WEAK_ALIAS(_iswgraph_l, libc_iswgraph_l);
DEFINE_PUBLIC_WEAK_ALIAS(iswlower_l, libc_iswlower_l);
DEFINE_PUBLIC_WEAK_ALIAS(__iswlower_l, libc_iswlower_l);
DEFINE_PUBLIC_WEAK_ALIAS(_iswlower_l, libc_iswlower_l);
DEFINE_PUBLIC_WEAK_ALIAS(iswprint_l, libc_iswprint_l);
DEFINE_PUBLIC_WEAK_ALIAS(__iswprint_l, libc_iswprint_l);
DEFINE_PUBLIC_WEAK_ALIAS(_iswprint_l, libc_iswprint_l);
DEFINE_PUBLIC_WEAK_ALIAS(iswpunct_l, libc_iswpunct_l);
DEFINE_PUBLIC_WEAK_ALIAS(__iswpunct_l, libc_iswpunct_l);
DEFINE_PUBLIC_WEAK_ALIAS(_iswpunct_l, libc_iswpunct_l);
DEFINE_PUBLIC_WEAK_ALIAS(iswspace_l, libc_iswspace_l);
DEFINE_PUBLIC_WEAK_ALIAS(__iswspace_l, libc_iswspace_l);
DEFINE_PUBLIC_WEAK_ALIAS(_iswspace_l, libc_iswspace_l);
DEFINE_PUBLIC_WEAK_ALIAS(iswupper_l, libc_iswupper_l);
DEFINE_PUBLIC_WEAK_ALIAS(__iswupper_l, libc_iswupper_l);
DEFINE_PUBLIC_WEAK_ALIAS(_iswupper_l, libc_iswupper_l);
DEFINE_PUBLIC_WEAK_ALIAS(iswxdigit_l, libc_iswxdigit_l);
DEFINE_PUBLIC_WEAK_ALIAS(__iswxdigit_l, libc_iswxdigit_l);
DEFINE_PUBLIC_WEAK_ALIAS(_iswxdigit_l, libc_iswxdigit_l);
DEFINE_PUBLIC_WEAK_ALIAS(iswblank_l, libc_iswblank_l);
DEFINE_PUBLIC_WEAK_ALIAS(__iswblank_l, libc_iswblank_l);
DEFINE_PUBLIC_WEAK_ALIAS(_iswblank_l, libc_iswblank_l);
DEFINE_PUBLIC_WEAK_ALIAS(iswctype_l, libc_iswctype_l);
DEFINE_PUBLIC_WEAK_ALIAS(__iswctype_l, libc_iswctype_l);
DEFINE_PUBLIC_WEAK_ALIAS(_iswctype_l, libc_iswctype_l);
DEFINE_PUBLIC_WEAK_ALIAS(towupper_l, libc_towupper_l);
DEFINE_PUBLIC_WEAK_ALIAS(__towupper_l, libc_towupper_l);
DEFINE_PUBLIC_WEAK_ALIAS(_towupper_l, libc_towupper_l);
DEFINE_PUBLIC_WEAK_ALIAS(towlower_l, libc_towlower_l);
DEFINE_PUBLIC_WEAK_ALIAS(__towlower_l, libc_towlower_l);
DEFINE_PUBLIC_WEAK_ALIAS(_towlower_l, libc_towlower_l);
DEFINE_PUBLIC_WEAK_ALIAS(wctype_l, libc_wctype_l);
DEFINE_PUBLIC_WEAK_ALIAS(__wctype_l, libc_wctype_l);
DEFINE_PUBLIC_WEAK_ALIAS(wctrans_l, libc_wctrans_l);
DEFINE_PUBLIC_WEAK_ALIAS(__wctrans_l, libc_wctrans_l);
DEFINE_PUBLIC_WEAK_ALIAS(towctrans_l, libc_towctrans_l);
DEFINE_PUBLIC_WEAK_ALIAS(__towctrans_l, libc_towctrans_l);
DEFINE_PUBLIC_WEAK_ALIAS(isleadbyte, libc_isleadbyte);
DEFINE_PUBLIC_WEAK_ALIAS(_isleadbyte_l, libc__isleadbyte_l);
DEFINE_PUBLIC_WEAK_ALIAS(__iswcsymf, libc___iswcsymf);
DEFINE_PUBLIC_WEAK_ALIAS(__iswcsym, libc___iswcsym);
DEFINE_PUBLIC_WEAK_ALIAS(_iswcsymf_l, libc__iswcsymf_l);
DEFINE_PUBLIC_WEAK_ALIAS(_iswcsym_l, libc__iswcsym_l);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_WCTYPE_C */
