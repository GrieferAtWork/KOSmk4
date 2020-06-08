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
%[define_ccompat_header("cwctype")]

%[define_replacement(locale_t = __locale_t)]
%[define_replacement(wint_t = __WINT_TYPE__)]
%[define_replacement(wctype_t = __WCTYPE_TYPE__)]
%[define_replacement(wctrans_t = __wctrans_t)]

%{
#include <features.h>

#include <hybrid/byteorder.h>
#include <hybrid/typecore.h>

#include <asm/stdio.h> /* __WEOF */
#include <bits/types.h>

#if defined(__USE_XOPEN2K8) || defined(__USE_DOS)
#include <xlocale.h>
#endif /* __USE_XOPEN2K8 || __USE_DOS */

__SYSDECL_BEGIN

#ifndef WEOF
#define WEOF __WEOF
#endif /* !WEOF */

#ifdef __CC__

__NAMESPACE_STD_BEGIN
#ifndef __std_wint_t_defined
#define __std_wint_t_defined 1
typedef __WINT_TYPE__ wint_t;
#endif /* !__std_wint_t_defined */
#ifndef __std_wctype_t_defined
#define __std_wctype_t_defined 1
typedef __WCTYPE_TYPE__ wctype_t;
#endif /* !__std_wctype_t_defined */
__NAMESPACE_STD_END

#ifndef __CXX_SYSTEM_HEADER
}%(c, ccompat){
#ifndef __wint_t_defined
#define __wint_t_defined 1
__NAMESPACE_STD_USING(wint_t)
#endif /* !__wint_t_defined */
#ifndef __wctype_t_defined
#define __wctype_t_defined 1
__NAMESPACE_STD_USING(wctype_t)
#endif /* !__wctype_t_defined */
}%{
#endif /* !__CXX_SYSTEM_HEADER */

#ifndef __wchar_t_defined
#define __wchar_t_defined 1
typedef __WCHAR_TYPE__ wchar_t;
#endif /* !__wchar_t_defined */

#ifndef ____wctrans_t_defined
#define ____wctrans_t_defined 1
#ifdef __DOS_COMPAT__
typedef wchar_t __wctrans_t;
#else /* __DOS_COMPAT__ */
typedef __int32_t const *__wctrans_t;
#endif /* !__DOS_COMPAT__ */
#endif /* !____wctrans_t_defined */

}
%[define_replacement(wctrans_t = __wctrans_t)]
%(c, ccompat){
#if defined(__USE_ISOC99) || defined(__USE_XOPEN2K8)
}%{
#ifndef __std_wctrans_t_defined
#define __std_wctrans_t_defined 1
__NAMESPACE_STD_BEGIN
typedef __wctrans_t wctrans_t;
__NAMESPACE_STD_END
#endif /* !__std_wctrans_t_defined */

#ifndef __CXX_SYSTEM_HEADER
}%(c, ccompat){
#ifndef __wctrans_t_defined
#define __wctrans_t_defined 1
__NAMESPACE_STD_USING(wctrans_t)
#endif /* !__wctrans_t_defined */
}%{
#endif /* !__CXX_SYSTEM_HEADER */
}%(c, ccompat){
#endif /* __USE_ISOC99 || __USE_XOPEN2K8 */
}%{


}

%[insert:std]
%[default_impl_section("{.text.crt.wchar.unicode.static.ctype|.text.crt.dos.wchar.unicode.static.ctype}")];

[[std, crtbuiltin, ATTR_WUNUSED, ATTR_CONST, nothrow]]
int iswalnum(wint_t wc) {
	return isalnum((int)wc);
}

[[std, crtbuiltin, ATTR_WUNUSED, ATTR_CONST, nothrow]]
int iswalpha(wint_t wc) {
	return isalpha((int)wc);
}

[[std, crtbuiltin, ATTR_WUNUSED, ATTR_CONST, nothrow]]
int iswcntrl(wint_t wc) {
	return iscntrl((int)wc);
}

[[std, crtbuiltin, ATTR_WUNUSED, ATTR_CONST, nothrow]]
int iswdigit(wint_t wc) {
	return isdigit((int)wc);
}

[[std, crtbuiltin, ATTR_WUNUSED, ATTR_CONST, nothrow]]
int iswgraph(wint_t wc) {
	return isgraph((int)wc);
}

[[std, crtbuiltin, ATTR_WUNUSED, ATTR_CONST, nothrow]]
int iswlower(wint_t wc) {
	return islower((int)wc);
}

[[std, crtbuiltin, ATTR_WUNUSED, ATTR_CONST, nothrow]]
int iswprint(wint_t wc) {
	return isprint((int)wc);
}

[[std, crtbuiltin, ATTR_WUNUSED, ATTR_CONST, nothrow]]
int iswpunct(wint_t wc) {
	return ispunct((int)wc);
}

[[std, crtbuiltin, ATTR_WUNUSED, ATTR_CONST, nothrow]]
int iswspace(wint_t wc) {
	return isspace((int)wc);
}

[[std, crtbuiltin, ATTR_WUNUSED, ATTR_CONST, nothrow]]
int iswupper(wint_t wc) {
	return isupper((int)wc);
}

[[std, crtbuiltin, ATTR_WUNUSED, ATTR_CONST, nothrow]]
int iswxdigit(wint_t wc) {
	return isdigit((int)wc);
}

%(std)#ifdef __USE_ISOC99
%[default_impl_section("{.text.crt.wchar.unicode.static.mbs|.text.crt.dos.wchar.unicode.static.mbs}")];

[[std, guard, ATTR_WUNUSED, ATTR_PURE]]
wctrans_t wctrans([[nonnull]] char const *prop) {
	/* TODO */
	(void)prop;
	COMPILER_IMPURE();
	return 0;
}

[[std, guard, ATTR_WUNUSED, export_alias("__towctrans"), ATTR_CONST]]
wint_t towctrans(wint_t wc, wctrans_t desc) {
	/* TODO */
	(void)wc;
	(void)desc;
	return 0;
}
%(std)#endif /* __USE_ISOC99 */

[[std, ATTR_WUNUSED, ATTR_PURE]]
wctype_t wctype([[nonnull]] char const *prop) {
	/* TODO */
	(void)prop;
	COMPILER_IMPURE();
	return 0;
}

[[std, ATTR_WUNUSED, ATTR_CONST, export_alias("is_wctype", "__iswctype")]]
int iswctype(wint_t wc, wctype_t desc) {
	/* TODO */
	(void)wc;
	(void)desc;
	return 0;
}

%[default_impl_section("{.text.crt.wchar.unicode.static.ctype|.text.crt.dos.wchar.unicode.static.ctype}")]
%(std)#ifdef __USE_ISOC99
[[std, guard, ATTR_WUNUSED, ATTR_CONST, nothrow, crtbuiltin]]
int iswblank(wint_t wc) {
	return isblank((int)wc);
}
%(std)#endif /* __USE_ISOC99 */

[[std, ATTR_WUNUSED, ATTR_CONST, nothrow, crtbuiltin]]
wint_t towlower(wint_t wc) {
	return (wint_t)tolower((int)wc);
}
[[std, ATTR_WUNUSED, ATTR_CONST, nothrow, crtbuiltin]]
wint_t towupper(wint_t wc) {
	return (wint_t)toupper((int)wc);
}


%
%#if defined(__USE_KOS) || defined(__USE_DOS)
[[ATTR_WUNUSED, ATTR_CONST, nothrow]]
int iswascii($wint_t wc) {
	return (unsigned int)wc <= 0x7f;
}
%#endif /* __USE_KOS || __USE_DOS */


%
%#ifdef __USE_XOPEN2K8

%[default_impl_section("{.text.crt.wchar.unicode.locale.ctype|.text.crt.dos.wchar.unicode.locale.ctype}")];
[[ATTR_WUNUSED, ATTR_PURE, export_alias("_iswalnum_l", "__iswalnum_l")]]
int iswalnum_l($wint_t wc, $locale_t locale) {
	(void)locale;
	COMPILER_IMPURE();
	return iswalnum(wc);
}

[[ATTR_WUNUSED, ATTR_PURE, export_alias("_iswalpha_l", "__iswalpha_l")]]
int iswalpha_l($wint_t wc, $locale_t locale) {
	(void)locale;
	COMPILER_IMPURE();
	return iswalpha(wc);
}

[[ATTR_WUNUSED, ATTR_PURE, export_alias("_iswcntrl_l", "__iswcntrl_l")]]
int iswcntrl_l($wint_t wc, $locale_t locale) {
	(void)locale;
	COMPILER_IMPURE();
	return iswcntrl(wc);
}

[[ATTR_WUNUSED, ATTR_PURE, export_alias("_iswdigit_l", "__iswdigit_l")]]
int iswdigit_l($wint_t wc, $locale_t locale) {
	(void)locale;
	COMPILER_IMPURE();
	return iswdigit(wc);
}

[[ATTR_WUNUSED, ATTR_PURE, export_alias("_iswgraph_l", "__iswgraph_l")]]
int iswgraph_l($wint_t wc, $locale_t locale) {
	(void)locale;
	COMPILER_IMPURE();
	return iswgraph(wc);
}

[[ATTR_WUNUSED, ATTR_PURE, export_alias("_iswlower_l", "__iswlower_l")]]
int iswlower_l($wint_t wc, $locale_t locale) {
	(void)locale;
	COMPILER_IMPURE();
	return iswlower(wc);
}

[[ATTR_WUNUSED, ATTR_PURE, export_alias("_iswprint_l", "__iswprint_l")]]
int iswprint_l($wint_t wc, $locale_t locale) {
	(void)locale;
	COMPILER_IMPURE();
	return iswprint(wc);
}

[[ATTR_WUNUSED, ATTR_PURE, export_alias("_iswpunct_l", "__iswpunct_l")]]
int iswpunct_l($wint_t wc, $locale_t locale) {
	(void)locale;
	COMPILER_IMPURE();
	return iswpunct(wc);
}

[[ATTR_WUNUSED, ATTR_PURE, export_alias("_iswspace_l", "__iswspace_l")]]
int iswspace_l($wint_t wc, $locale_t locale) {
	(void)locale;
	COMPILER_IMPURE();
	return iswspace(wc);
}

[[ATTR_WUNUSED, ATTR_PURE, export_alias("_iswupper_l", "__iswupper_l")]]
int iswupper_l($wint_t wc, $locale_t locale) {
	(void)locale;
	COMPILER_IMPURE();
	return iswupper(wc);
}

[[ATTR_WUNUSED, ATTR_PURE, export_alias("_iswxdigit_l", "__iswxdigit_l")]]
int iswxdigit_l($wint_t wc, $locale_t locale) {
	(void)locale;
	COMPILER_IMPURE();
	return iswxdigit(wc);
}

[[ATTR_WUNUSED, ATTR_PURE, export_alias("_iswblank_l", "__iswblank_l")]]
int iswblank_l($wint_t wc, $locale_t locale) {
	(void)locale;
	COMPILER_IMPURE();
	return iswblank(wc);
}

[[ATTR_WUNUSED, ATTR_PURE, export_alias("_iswctype_l", "__iswctype_l")]]
int iswctype_l($wint_t wc, $wctype_t type, $locale_t locale) {
	(void)locale;
	COMPILER_IMPURE();
	return iswctype(wc, type);
}

[[ATTR_WUNUSED, ATTR_PURE, export_alias("_towupper_l", "__towupper_l")]]
$wint_t towupper_l($wint_t wc, $locale_t locale) {
	(void)locale;
	COMPILER_IMPURE();
	return towupper(wc);
}

[[ATTR_WUNUSED, ATTR_PURE, export_alias("_towlower_l", "__towlower_l")]]
$wint_t towlower_l($wint_t wc, $locale_t locale) {
	(void)locale;
	COMPILER_IMPURE();
	return towlower(wc);
}

%[default_impl_section("{.text.crt.wchar.unicode.locale.mbs|.text.crt.dos.wchar.unicode.locale.mbs}")];

[[ATTR_WUNUSED, export_alias("__wctype_l")]]
$wctype_t wctype_l([[nonnull]] char const *prop, $locale_t locale) {
	(void)locale;
	COMPILER_IMPURE();
	return wctype(prop);
}

[[ATTR_WUNUSED, export_alias("__wctrans_l")]]
$wctrans_t wctrans_l([[nonnull]] char const *prop, $locale_t locale) {
	(void)locale;
	COMPILER_IMPURE();
	return wctrans(prop);
}

[[ATTR_WUNUSED, export_alias("__towctrans_l")]]
$wint_t towctrans_l($wint_t wc, $wctrans_t desc, $locale_t locale) {
	(void)locale;
	COMPILER_IMPURE();
	return towctrans(wc, desc);
}

%#endif /* __USE_XOPEN2K8 */

%
%#ifdef __USE_DOS
%#ifndef __wctype_t_defined
%#define __wctype_t_defined 1
%__NAMESPACE_STD_USING(wctype_t)
%#endif /* !__wctype_t_defined */
%#ifndef _WCTYPE_DEFINED
%#define _WCTYPE_DEFINED 1

_iswalnum_l(*) = iswalnum_l;
_iswalpha_l(*) = iswalpha_l;
_iswcntrl_l(*) = iswcntrl_l;
_iswdigit_l(*) = iswdigit_l;
_iswgraph_l(*) = iswgraph_l;
_iswlower_l(*) = iswlower_l;
_iswprint_l(*) = iswprint_l;
_iswpunct_l(*) = iswpunct_l;
_iswspace_l(*) = iswspace_l;
_iswupper_l(*) = iswupper_l;
_iswxdigit_l(*) = iswxdigit_l;
_iswblank_l(*) = iswblank_l;
_towupper_l(*) = towupper_l;
_towlower_l(*) = towlower_l;
_iswctype_l(*) = iswctype_l;
is_wctype(*) = iswctype;

%
[[ATTR_WUNUSED, ATTR_CONST]]
[[section("{.text.crt.wchar.unicode.static.mbs|.text.crt.dos.wchar.unicode.static.mbs}")]]
int isleadbyte(int wc) {
	return wc >= 192 && wc <= 255;
}

[[ATTR_WUNUSED, ATTR_PURE]]
[[section("{.text.crt.wchar.unicode.locale.mbs|.text.crt.dos.wchar.unicode.locale.mbs}")]]
int _isleadbyte_l(int wc, $locale_t locale) {
	(void)locale;
	COMPILER_IMPURE();
	return isleadbyte(wc);
}

%[default_impl_section("{.text.crt.wchar.unicode.static.mbs|.text.crt.dos.wchar.unicode.static.mbs}")];
[[ATTR_WUNUSED, ATTR_CONST]]
int __iswcsymf($wint_t wc) {
	return iswalpha(wc) || wc == '_' || wc == '$';
}

[[ATTR_WUNUSED, ATTR_CONST]]
int __iswcsym($wint_t wc) {
	return iswalnum(wc) || wc == '_' || wc == '$';
}

%
%[default_impl_section("{.text.crt.wchar.unicode.locale.mbs|.text.crt.dos.wchar.unicode.locale.mbs}")];
[[ATTR_WUNUSED, ATTR_PURE]]
int _iswcsymf_l($wint_t wc, $locale_t locale) {
	return iswalpha_l(wc, locale) || wc == '_' || wc == '$';
}

[[ATTR_WUNUSED, ATTR_PURE]]
int _iswcsym_l($wint_t wc, $locale_t locale) {
	return iswalnum_l(wc, locale) || wc == '_' || wc == '$';
}

%#endif /* !_WCTYPE_DEFINED */
%#endif /* __USE_DOS */



%{

#endif /* __CC__ */

__SYSDECL_END

}

