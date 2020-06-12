/* HASH CRC-32:0x2ce15631 */
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
#ifndef GUARD_LIBC_AUTO_WCTYPE_C
#define GUARD_LIBC_AUTO_WCTYPE_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "wctype.h"
#include <ctype.h>

DECL_BEGIN

#ifndef __KERNEL__
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBCCALL libc_iswalnum)(wint_t wc) {
	return isalnum((int)wc);
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBCCALL libc_iswalpha)(wint_t wc) {
	return isalpha((int)wc);
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBCCALL libc_iswcntrl)(wint_t wc) {
	return iscntrl((int)wc);
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBCCALL libc_iswdigit)(wint_t wc) {
	return isdigit((int)wc);
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBCCALL libc_iswgraph)(wint_t wc) {
	return isgraph((int)wc);
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBCCALL libc_iswlower)(wint_t wc) {
	return islower((int)wc);
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBCCALL libc_iswprint)(wint_t wc) {
	return isprint((int)wc);
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBCCALL libc_iswpunct)(wint_t wc) {
	return ispunct((int)wc);
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBCCALL libc_iswspace)(wint_t wc) {
	return isspace((int)wc);
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBCCALL libc_iswupper)(wint_t wc) {
	return isupper((int)wc);
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBCCALL libc_iswxdigit)(wint_t wc) {
	return isdigit((int)wc);
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.mbs") ATTR_PURE WUNUSED NONNULL((1)) wctrans_t
NOTHROW_NCX(LIBCCALL libc_wctrans)(char const *prop) {
	/* TODO */
	(void)prop;
	COMPILER_IMPURE();
	return 0;
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.mbs") ATTR_CONST WUNUSED wint_t
NOTHROW_NCX(LIBCCALL libc_towctrans)(wint_t wc,
                                     wctrans_t desc) {
	/* TODO */
	(void)wc;
	(void)desc;
	return 0;
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.mbs") ATTR_PURE WUNUSED NONNULL((1)) wctype_t
NOTHROW_NCX(LIBCCALL libc_wctype)(char const *prop) {
	/* TODO */
	(void)prop;
	COMPILER_IMPURE();
	return 0;
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.mbs") ATTR_CONST WUNUSED int
NOTHROW_NCX(LIBCCALL libc_iswctype)(wint_t wc,
                                    wctype_t desc) {
	/* TODO */
	(void)wc;
	(void)desc;
	return 0;
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBCCALL libc_iswblank)(wint_t wc) {
	return isblank((int)wc);
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.ctype") ATTR_CONST WUNUSED wint_t
NOTHROW(LIBCCALL libc_towlower)(wint_t wc) {
	return (wint_t)tolower((int)wc);
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.ctype") ATTR_CONST WUNUSED wint_t
NOTHROW(LIBCCALL libc_towupper)(wint_t wc) {
	return (wint_t)toupper((int)wc);
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBCCALL libc_iswascii)(wint_t wc) {
	return (unsigned int)wc <= 0x7f;
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.locale.ctype") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBCCALL libc_iswalnum_l)(wint_t wc,
                                      locale_t locale) {
	(void)locale;
	COMPILER_IMPURE();
	return iswalnum(wc);
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.locale.ctype") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBCCALL libc_iswalpha_l)(wint_t wc,
                                      locale_t locale) {
	(void)locale;
	COMPILER_IMPURE();
	return iswalpha(wc);
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.locale.ctype") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBCCALL libc_iswcntrl_l)(wint_t wc,
                                      locale_t locale) {
	(void)locale;
	COMPILER_IMPURE();
	return iswcntrl(wc);
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.locale.ctype") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBCCALL libc_iswdigit_l)(wint_t wc,
                                      locale_t locale) {
	(void)locale;
	COMPILER_IMPURE();
	return iswdigit(wc);
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.locale.ctype") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBCCALL libc_iswgraph_l)(wint_t wc,
                                      locale_t locale) {
	(void)locale;
	COMPILER_IMPURE();
	return iswgraph(wc);
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.locale.ctype") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBCCALL libc_iswlower_l)(wint_t wc,
                                      locale_t locale) {
	(void)locale;
	COMPILER_IMPURE();
	return iswlower(wc);
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.locale.ctype") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBCCALL libc_iswprint_l)(wint_t wc,
                                      locale_t locale) {
	(void)locale;
	COMPILER_IMPURE();
	return iswprint(wc);
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.locale.ctype") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBCCALL libc_iswpunct_l)(wint_t wc,
                                      locale_t locale) {
	(void)locale;
	COMPILER_IMPURE();
	return iswpunct(wc);
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.locale.ctype") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBCCALL libc_iswspace_l)(wint_t wc,
                                      locale_t locale) {
	(void)locale;
	COMPILER_IMPURE();
	return iswspace(wc);
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.locale.ctype") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBCCALL libc_iswupper_l)(wint_t wc,
                                      locale_t locale) {
	(void)locale;
	COMPILER_IMPURE();
	return iswupper(wc);
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.locale.ctype") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBCCALL libc_iswxdigit_l)(wint_t wc,
                                       locale_t locale) {
	(void)locale;
	COMPILER_IMPURE();
	return iswxdigit(wc);
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.locale.ctype") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBCCALL libc_iswblank_l)(wint_t wc,
                                      locale_t locale) {
	(void)locale;
	COMPILER_IMPURE();
	return iswblank(wc);
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.locale.ctype") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBCCALL libc_iswctype_l)(wint_t wc,
                                      wctype_t type,
                                      locale_t locale) {
	(void)locale;
	COMPILER_IMPURE();
	return iswctype(wc, type);
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.locale.ctype") ATTR_PURE WUNUSED wint_t
NOTHROW_NCX(LIBCCALL libc_towupper_l)(wint_t wc,
                                      locale_t locale) {
	(void)locale;
	COMPILER_IMPURE();
	return towupper(wc);
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.locale.ctype") ATTR_PURE WUNUSED wint_t
NOTHROW_NCX(LIBCCALL libc_towlower_l)(wint_t wc,
                                      locale_t locale) {
	(void)locale;
	COMPILER_IMPURE();
	return towlower(wc);
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.locale.mbs") WUNUSED NONNULL((1)) wctype_t
NOTHROW_NCX(LIBCCALL libc_wctype_l)(char const *prop,
                                    locale_t locale) {
	(void)locale;
	COMPILER_IMPURE();
	return wctype(prop);
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.locale.mbs") WUNUSED NONNULL((1)) wctrans_t
NOTHROW_NCX(LIBCCALL libc_wctrans_l)(char const *prop,
                                     locale_t locale) {
	(void)locale;
	COMPILER_IMPURE();
	return wctrans(prop);
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.locale.mbs") WUNUSED wint_t
NOTHROW_NCX(LIBCCALL libc_towctrans_l)(wint_t wc,
                                       wctrans_t desc,
                                       locale_t locale) {
	(void)locale;
	COMPILER_IMPURE();
	return towctrans(wc, desc);
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.mbs") ATTR_CONST WUNUSED int
NOTHROW_NCX(LIBCCALL libc_isleadbyte)(int wc) {
	return wc >= 192 && wc <= 255;
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.locale.mbs") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBCCALL libc__isleadbyte_l)(int wc,
                                         locale_t locale) {
	(void)locale;
	COMPILER_IMPURE();
	return isleadbyte(wc);
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.mbs") ATTR_CONST WUNUSED int
NOTHROW_NCX(LIBCCALL libc___iswcsymf)(wint_t wc) {
	return iswalpha(wc) || wc == '_' || wc == '$';
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.mbs") ATTR_CONST WUNUSED int
NOTHROW_NCX(LIBCCALL libc___iswcsym)(wint_t wc) {
	return iswalnum(wc) || wc == '_' || wc == '$';
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.locale.mbs") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBCCALL libc__iswcsymf_l)(wint_t wc,
                                       locale_t locale) {
	return iswalpha_l(wc, locale) || wc == '_' || wc == '$';
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.locale.mbs") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBCCALL libc__iswcsym_l)(wint_t wc,
                                      locale_t locale) {
	return iswalnum_l(wc, locale) || wc == '_' || wc == '$';
}
#endif /* !__KERNEL__ */

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(iswalnum, libc_iswalnum);
DEFINE_PUBLIC_ALIAS(iswalpha, libc_iswalpha);
DEFINE_PUBLIC_ALIAS(iswcntrl, libc_iswcntrl);
DEFINE_PUBLIC_ALIAS(iswdigit, libc_iswdigit);
DEFINE_PUBLIC_ALIAS(iswgraph, libc_iswgraph);
DEFINE_PUBLIC_ALIAS(iswlower, libc_iswlower);
DEFINE_PUBLIC_ALIAS(iswprint, libc_iswprint);
DEFINE_PUBLIC_ALIAS(iswpunct, libc_iswpunct);
DEFINE_PUBLIC_ALIAS(iswspace, libc_iswspace);
DEFINE_PUBLIC_ALIAS(iswupper, libc_iswupper);
DEFINE_PUBLIC_ALIAS(iswxdigit, libc_iswxdigit);
DEFINE_PUBLIC_ALIAS(wctrans, libc_wctrans);
DEFINE_PUBLIC_ALIAS(__towctrans, libc_towctrans);
DEFINE_PUBLIC_ALIAS(towctrans, libc_towctrans);
DEFINE_PUBLIC_ALIAS(wctype, libc_wctype);
DEFINE_PUBLIC_ALIAS(is_wctype, libc_iswctype);
DEFINE_PUBLIC_ALIAS(__iswctype, libc_iswctype);
DEFINE_PUBLIC_ALIAS(iswctype, libc_iswctype);
DEFINE_PUBLIC_ALIAS(iswblank, libc_iswblank);
DEFINE_PUBLIC_ALIAS(towlower, libc_towlower);
DEFINE_PUBLIC_ALIAS(towupper, libc_towupper);
DEFINE_PUBLIC_ALIAS(iswascii, libc_iswascii);
DEFINE_PUBLIC_ALIAS(_iswalnum_l, libc_iswalnum_l);
DEFINE_PUBLIC_ALIAS(__iswalnum_l, libc_iswalnum_l);
DEFINE_PUBLIC_ALIAS(iswalnum_l, libc_iswalnum_l);
DEFINE_PUBLIC_ALIAS(_iswalpha_l, libc_iswalpha_l);
DEFINE_PUBLIC_ALIAS(__iswalpha_l, libc_iswalpha_l);
DEFINE_PUBLIC_ALIAS(iswalpha_l, libc_iswalpha_l);
DEFINE_PUBLIC_ALIAS(_iswcntrl_l, libc_iswcntrl_l);
DEFINE_PUBLIC_ALIAS(__iswcntrl_l, libc_iswcntrl_l);
DEFINE_PUBLIC_ALIAS(iswcntrl_l, libc_iswcntrl_l);
DEFINE_PUBLIC_ALIAS(_iswdigit_l, libc_iswdigit_l);
DEFINE_PUBLIC_ALIAS(__iswdigit_l, libc_iswdigit_l);
DEFINE_PUBLIC_ALIAS(iswdigit_l, libc_iswdigit_l);
DEFINE_PUBLIC_ALIAS(_iswgraph_l, libc_iswgraph_l);
DEFINE_PUBLIC_ALIAS(__iswgraph_l, libc_iswgraph_l);
DEFINE_PUBLIC_ALIAS(iswgraph_l, libc_iswgraph_l);
DEFINE_PUBLIC_ALIAS(_iswlower_l, libc_iswlower_l);
DEFINE_PUBLIC_ALIAS(__iswlower_l, libc_iswlower_l);
DEFINE_PUBLIC_ALIAS(iswlower_l, libc_iswlower_l);
DEFINE_PUBLIC_ALIAS(_iswprint_l, libc_iswprint_l);
DEFINE_PUBLIC_ALIAS(__iswprint_l, libc_iswprint_l);
DEFINE_PUBLIC_ALIAS(iswprint_l, libc_iswprint_l);
DEFINE_PUBLIC_ALIAS(_iswpunct_l, libc_iswpunct_l);
DEFINE_PUBLIC_ALIAS(__iswpunct_l, libc_iswpunct_l);
DEFINE_PUBLIC_ALIAS(iswpunct_l, libc_iswpunct_l);
DEFINE_PUBLIC_ALIAS(_iswspace_l, libc_iswspace_l);
DEFINE_PUBLIC_ALIAS(__iswspace_l, libc_iswspace_l);
DEFINE_PUBLIC_ALIAS(iswspace_l, libc_iswspace_l);
DEFINE_PUBLIC_ALIAS(_iswupper_l, libc_iswupper_l);
DEFINE_PUBLIC_ALIAS(__iswupper_l, libc_iswupper_l);
DEFINE_PUBLIC_ALIAS(iswupper_l, libc_iswupper_l);
DEFINE_PUBLIC_ALIAS(_iswxdigit_l, libc_iswxdigit_l);
DEFINE_PUBLIC_ALIAS(__iswxdigit_l, libc_iswxdigit_l);
DEFINE_PUBLIC_ALIAS(iswxdigit_l, libc_iswxdigit_l);
DEFINE_PUBLIC_ALIAS(_iswblank_l, libc_iswblank_l);
DEFINE_PUBLIC_ALIAS(__iswblank_l, libc_iswblank_l);
DEFINE_PUBLIC_ALIAS(iswblank_l, libc_iswblank_l);
DEFINE_PUBLIC_ALIAS(_iswctype_l, libc_iswctype_l);
DEFINE_PUBLIC_ALIAS(__iswctype_l, libc_iswctype_l);
DEFINE_PUBLIC_ALIAS(iswctype_l, libc_iswctype_l);
DEFINE_PUBLIC_ALIAS(_towupper_l, libc_towupper_l);
DEFINE_PUBLIC_ALIAS(__towupper_l, libc_towupper_l);
DEFINE_PUBLIC_ALIAS(towupper_l, libc_towupper_l);
DEFINE_PUBLIC_ALIAS(_towlower_l, libc_towlower_l);
DEFINE_PUBLIC_ALIAS(__towlower_l, libc_towlower_l);
DEFINE_PUBLIC_ALIAS(towlower_l, libc_towlower_l);
DEFINE_PUBLIC_ALIAS(__wctype_l, libc_wctype_l);
DEFINE_PUBLIC_ALIAS(wctype_l, libc_wctype_l);
DEFINE_PUBLIC_ALIAS(__wctrans_l, libc_wctrans_l);
DEFINE_PUBLIC_ALIAS(wctrans_l, libc_wctrans_l);
DEFINE_PUBLIC_ALIAS(__towctrans_l, libc_towctrans_l);
DEFINE_PUBLIC_ALIAS(towctrans_l, libc_towctrans_l);
DEFINE_PUBLIC_ALIAS(isleadbyte, libc_isleadbyte);
DEFINE_PUBLIC_ALIAS(_isleadbyte_l, libc__isleadbyte_l);
DEFINE_PUBLIC_ALIAS(__iswcsymf, libc___iswcsymf);
DEFINE_PUBLIC_ALIAS(__iswcsym, libc___iswcsym);
DEFINE_PUBLIC_ALIAS(_iswcsymf_l, libc__iswcsymf_l);
DEFINE_PUBLIC_ALIAS(_iswcsym_l, libc__iswcsym_l);
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_WCTYPE_C */
