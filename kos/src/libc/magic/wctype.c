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
%[define_ccompat_header(cwctype)]

%[define_replacement(locale_t = __locale_t)]
%[define_replacement(wint_t = __WINT_TYPE__)]
%[define_replacement(wctype_t = __WCTYPE_TYPE__)]
%[define_replacement(wctrans_t = __wctrans_t)]

%{
#include <features.h>

#include <bits/types.h>
#include <hybrid/typecore.h>
#include <hybrid/byteorder.h>

#if defined(__USE_XOPEN2K8) || defined(__USE_DOS)
#include <xlocale.h>
#endif /* __USE_XOPEN2K8 || __USE_DOS */

__SYSDECL_BEGIN

#ifndef WEOF
#if __SIZEOF_WCHAR_T__ == 4
#define WEOF (__CCAST(__WINT_TYPE__)0xffffffffu)
#else /* __SIZEOF_WCHAR_T__ == 4 */
#define WEOF (__CCAST(__WINT_TYPE__)0xffff)
#endif /* __SIZEOF_WCHAR_T__ != 4 */
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
%[default_impl_section({.text.crt.wchar.unicode.static.ctype|.text.crt.dos.wchar.unicode.static.ctype})]

[std][ATTR_WUNUSED][ATTR_CONST][nothrow][crtbuiltin]
iswalnum:(wint_t wc) -> int {
	return isalnum((int)wc);
}
[std][ATTR_WUNUSED][ATTR_CONST][nothrow][crtbuiltin]
iswalpha:(wint_t wc) -> int {
	return isalpha((int)wc);
}
[std][ATTR_WUNUSED][ATTR_CONST][nothrow][crtbuiltin]
iswcntrl:(wint_t wc) -> int {
	return iscntrl((int)wc);
}
[std][ATTR_WUNUSED][ATTR_CONST][nothrow][crtbuiltin]
iswdigit:(wint_t wc) -> int {
	return isdigit((int)wc);
}
[std][ATTR_WUNUSED][ATTR_CONST][nothrow][crtbuiltin]
iswgraph:(wint_t wc) -> int {
	return isgraph((int)wc);
}
[std][ATTR_WUNUSED][ATTR_CONST][nothrow][crtbuiltin]
iswlower:(wint_t wc) -> int {
	return islower((int)wc);
}
[std][ATTR_WUNUSED][ATTR_CONST][nothrow][crtbuiltin]
iswprint:(wint_t wc) -> int {
	return isprint((int)wc);
}
[std][ATTR_WUNUSED][ATTR_CONST][nothrow][crtbuiltin]
iswpunct:(wint_t wc) -> int {
	return ispunct((int)wc);
}
[std][ATTR_WUNUSED][ATTR_CONST][nothrow][crtbuiltin]
iswspace:(wint_t wc) -> int {
	return isspace((int)wc);
}
[std][ATTR_WUNUSED][ATTR_CONST][nothrow][crtbuiltin]
iswupper:(wint_t wc) -> int {
	return isupper((int)wc);
}
[std][ATTR_WUNUSED][ATTR_CONST][nothrow][crtbuiltin]
iswxdigit:(wint_t wc) -> int {
	return isdigit((int)wc);
}

%(std)#ifdef __USE_ISOC99
%[default_impl_section({.text.crt.wchar.unicode.static.mbs|.text.crt.dos.wchar.unicode.static.mbs})]
[std][std_guard][ATTR_WUNUSED][ATTR_NONNULL((1))]
wctrans:(char const *prop) -> wctrans_t {
	/* TODO */
	return 0;
}
[std][std_guard][ATTR_WUNUSED][export_alias(__towctrans)]
towctrans:(wint_t wc, wctrans_t desc) -> wint_t {
	/* TODO */
	return 0;
}
%(std)#endif /* __USE_ISOC99 */

[std][ATTR_WUNUSED][ATTR_NONNULL((1))]
wctype:(char const *prop) -> wctype_t {
	/* TODO */
	return 0;
}
[std][ATTR_WUNUSED][alias(is_wctype)][export_alias(__iswctype)]
iswctype:(wint_t wc, wctype_t desc) -> int {
	/* TODO */
	return 0;
}

%[default_impl_section({.text.crt.wchar.unicode.static.ctype|.text.crt.dos.wchar.unicode.static.ctype})]
%(std)#ifdef __USE_ISOC99
[std][std_guard][ATTR_WUNUSED][ATTR_CONST][nothrow][crtbuiltin]
iswblank:(wint_t wc) -> int {
	return isblank((int)wc);
}
%(std)#endif /* __USE_ISOC99 */

[std][ATTR_WUNUSED][ATTR_CONST][nothrow][crtbuiltin]
towlower:(wint_t wc) -> wint_t {
	return (wint_t)tolower((int)wc);
}
[std][ATTR_WUNUSED][ATTR_CONST][nothrow][crtbuiltin]
towupper:(wint_t wc) -> wint_t {
	return (wint_t)toupper((int)wc);
}


%
%#if defined(__USE_KOS) || defined(__USE_DOS)
[ATTR_WUNUSED][ATTR_CONST][nothrow]
iswascii:($wint_t wc) -> int {
	return (unsigned int)wc <= 0x7f;
}
%#endif /* __USE_KOS || __USE_DOS */


%
%#ifdef __USE_XOPEN2K8

%[default_impl_section({.text.crt.wchar.unicode.locale.ctype|.text.crt.dos.wchar.unicode.locale.ctype})]
[ATTR_WUNUSED][ATTR_PURE][alias(_iswalnum_l)][export_alias(__iswalnum_l)]
iswalnum_l:($wint_t wc, $locale_t locale) -> int {
	(void)locale;
	return iswalnum(wc);
}

[ATTR_WUNUSED][ATTR_PURE][alias(_iswalpha_l)][export_alias(__iswalpha_l)]
iswalpha_l:($wint_t wc, $locale_t locale) -> int {
	(void)locale;
	return iswalpha(wc);
}

[ATTR_WUNUSED][ATTR_PURE][alias(_iswcntrl_l)][export_alias(__iswcntrl_l)]
iswcntrl_l:($wint_t wc, $locale_t locale) -> int {
	(void)locale;
	return iswcntrl(wc);
}

[ATTR_WUNUSED][ATTR_PURE][alias(_iswdigit_l)][export_alias(__iswdigit_l)]
iswdigit_l:($wint_t wc, $locale_t locale) -> int {
	(void)locale;
	return iswdigit(wc);
}

[ATTR_WUNUSED][ATTR_PURE][alias(_iswgraph_l)][export_alias(__iswgraph_l)]
iswgraph_l:($wint_t wc, $locale_t locale) -> int {
	(void)locale;
	return iswgraph(wc);
}

[ATTR_WUNUSED][ATTR_PURE][alias(_iswlower_l)][export_alias(__iswlower_l)]
iswlower_l:($wint_t wc, $locale_t locale) -> int {
	(void)locale;
	return iswlower(wc);
}

[ATTR_WUNUSED][ATTR_PURE][alias(_iswprint_l)][export_alias(__iswprint_l)]
iswprint_l:($wint_t wc, $locale_t locale) -> int {
	(void)locale;
	return iswprint(wc);
}

[ATTR_WUNUSED][ATTR_PURE][alias(_iswpunct_l)][export_alias(__iswpunct_l)]
iswpunct_l:($wint_t wc, $locale_t locale) -> int {
	(void)locale;
	return iswpunct(wc);
}

[ATTR_WUNUSED][ATTR_PURE][alias(_iswspace_l)][export_alias(__iswspace_l)]
iswspace_l:($wint_t wc, $locale_t locale) -> int {
	(void)locale;
	return iswspace(wc);
}

[ATTR_WUNUSED][ATTR_PURE][alias(_iswupper_l)][export_alias(__iswupper_l)]
iswupper_l:($wint_t wc, $locale_t locale) -> int {
	(void)locale;
	return iswupper(wc);
}

[ATTR_WUNUSED][ATTR_PURE][alias(_iswxdigit_l)][export_alias(__iswxdigit_l)]
iswxdigit_l:($wint_t wc, $locale_t locale) -> int {
	(void)locale;
	return iswxdigit(wc);
}

[ATTR_WUNUSED][ATTR_PURE][alias(_iswblank_l)][export_alias(__iswblank_l)]
iswblank_l:($wint_t wc, $locale_t locale) -> int {
	(void)locale;
	return iswblank(wc);
}

[ATTR_WUNUSED][ATTR_PURE][alias(_iswctype_l)][export_alias(__iswctype_l)]
iswctype_l:($wint_t wc, $wctype_t type, $locale_t locale) -> int {
	(void)locale;
	return iswctype(wc, type);
}

[ATTR_WUNUSED][ATTR_PURE][alias(_towupper_l)][export_alias(__towupper_l)]
towupper_l:($wint_t wc, $locale_t locale) -> $wint_t {
	(void)locale;
	return towupper(wc);
}

[ATTR_WUNUSED][ATTR_PURE][alias(_towlower_l)][export_alias(__towlower_l)]
towlower_l:($wint_t wc, $locale_t locale) -> $wint_t {
	(void)locale;
	return towlower(wc);
}

%[default_impl_section({.text.crt.wchar.unicode.locale.mbs|.text.crt.dos.wchar.unicode.locale.mbs})]
[ATTR_WUNUSED][ATTR_NONNULL((1))][export_alias(__wctype_l)]
wctype_l:(char const *prop, $locale_t locale) -> $wctype_t {
	(void)locale;
	return wctype(prop);
}

[ATTR_WUNUSED][ATTR_NONNULL((1))][export_alias(__wctrans_l)]
wctrans_l:(char const *prop, $locale_t locale) -> $wctrans_t {
	(void)locale;
	return wctrans(prop);
}

[ATTR_WUNUSED][export_alias(__towctrans_l)]
towctrans_l:($wint_t wc, $wctrans_t desc, $locale_t locale) -> $wint_t {
	(void)locale;
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

%[default_impl_section({.text.crt.wchar.unicode.locale.ctype|.text.crt.dos.wchar.unicode.locale.ctype})]
[attribute(*)][alias(*)] _iswalnum_l:(*) = iswalnum_l;
[attribute(*)][alias(*)] _iswalpha_l:(*) = iswalpha_l;
[attribute(*)][alias(*)] _iswcntrl_l:(*) = iswcntrl_l;
[attribute(*)][alias(*)] _iswdigit_l:(*) = iswdigit_l;
[attribute(*)][alias(*)] _iswgraph_l:(*) = iswgraph_l;
[attribute(*)][alias(*)] _iswlower_l:(*) = iswlower_l;
[attribute(*)][alias(*)] _iswprint_l:(*) = iswprint_l;
[attribute(*)][alias(*)] _iswpunct_l:(*) = iswpunct_l;
[attribute(*)][alias(*)] _iswspace_l:(*) = iswspace_l;
[attribute(*)][alias(*)] _iswupper_l:(*) = iswupper_l;
[attribute(*)][alias(*)] _iswxdigit_l:(*) = iswxdigit_l;
[attribute(*)][alias(*)] _iswblank_l:(*) = iswblank_l;
[attribute(*)][alias(*)] _towupper_l:(*) = towupper_l;
[attribute(*)][alias(*)] _towlower_l:(*) = towlower_l;
%[default_impl_section({.text.crt.wchar.unicode.locale.mbs|.text.crt.dos.wchar.unicode.locale.mbs})]
[attribute(*)][alias(*)] _iswctype_l:(*) = iswctype_l;
[ATTR_WUNUSED] is_wctype:($wint_t wc, $wctype_t desc) -> int = iswctype;

%[default_impl_section({.text.crt.wchar.unicode.static.mbs|.text.crt.dos.wchar.unicode.static.mbs})]
%
[ATTR_WUNUSED][ATTR_CONST]
isleadbyte:(int wc) -> int {
	return wc >= 192 && wc <= 255;
}
%[default_impl_section({.text.crt.wchar.unicode.locale.mbs|.text.crt.dos.wchar.unicode.locale.mbs})]
[ATTR_WUNUSED][ATTR_PURE]
_isleadbyte_l:(int wc, $locale_t locale) -> int {
	(void)locale;
	return isleadbyte(wc);
}
%[default_impl_section({.text.crt.wchar.unicode.static.mbs|.text.crt.dos.wchar.unicode.static.mbs})]
[ATTR_WUNUSED][ATTR_CONST]
__iswcsymf:($wint_t wc) -> int {
	return iswalpha(wc) || wc == '_' || wc == '$';
}
[ATTR_WUNUSED][ATTR_CONST]
__iswcsym:($wint_t wc) -> int {
	return iswalnum(wc) || wc == '_' || wc == '$';
}

%
%[default_impl_section({.text.crt.wchar.unicode.locale.mbs|.text.crt.dos.wchar.unicode.locale.mbs})]
[ATTR_WUNUSED][ATTR_PURE]
_iswcsymf_l:($wint_t wc, $locale_t locale) -> int {
	return iswalpha_l(wc, locale) || wc == '_' || wc == '$';
}
[ATTR_WUNUSED][ATTR_PURE]
_iswcsym_l:($wint_t wc, $locale_t locale) -> int {
	return iswalnum_l(wc, locale) || wc == '_' || wc == '$';
}

%#endif /* !_WCTYPE_DEFINED */
%#endif /* __USE_DOS */



%{

#endif /* __CC__ */

__SYSDECL_END

}

