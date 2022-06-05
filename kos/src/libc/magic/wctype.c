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
%(c_prefix){
/* (>) Standard: ISO C95 (ISO/IEC 9899:1990/AMD1:1995) */
/* (>) Standard: POSIX.1-2001 (Issue 5, IEEE Std 1003.1-2001) */
/* (#) Portability: Cygwin        (/newlib/libc/include/wctype.h) */
/* (#) Portability: DJGPP         (/include/wctype.h) */
/* (#) Portability: EMX kLIBC     (/libc/include/wctype.h) */
/* (#) Portability: FreeBSD       (/include/wctype.h) */
/* (#) Portability: GNU C Library (/wctype/wctype.h) */
/* (#) Portability: MSVC          (/include/wctype.h) */
/* (#) Portability: MinGW         (/mingw-w64-headers/crt/wctype.h) */
/* (#) Portability: NetBSD        (/include/wctype.h) */
/* (#) Portability: Newlib        (/newlib/libc/include/wctype.h) */
/* (#) Portability: OpenBSD       (/include/wctype.h) */
/* (#) Portability: OpenSolaris   (/usr/src/head/wctype.h) */
/* (#) Portability: PDCLib        (/include/wctype.h) */
/* (#) Portability: Windows Kits  (/ucrt/wctype.h) */
/* (#) Portability: diet libc     (/include/wctype.h) */
/* (#) Portability: libc6         (/include/wctype.h) */
/* (#) Portability: mintlib       (/include/wctype.h) */
/* (#) Portability: musl libc     (/include/wctype.h) */
/* (#) Portability: uClibc        (/include/wctype.h) */
}

%[define_ccompat_header("cwctype")]

%[define_replacement(locale_t = __locale_t)]
%[define_replacement(wint_t = __WINT_TYPE__)]
%[define_replacement(wctype_t = __wctype_t)]
%[define_replacement(wctrans_t = __wctrans_t)]
%[define_replacement(offsetof = __builtin_offsetof)]

%[define_str2wcs_replacement(iscntrl = iswcntrl)]
%[define_str2wcs_replacement(isspace = iswspace)]
%[define_str2wcs_replacement(isupper = iswupper)]
%[define_str2wcs_replacement(islower = iswlower)]
%[define_str2wcs_replacement(isalpha = iswalpha)]
%[define_str2wcs_replacement(isdigit = iswdigit)]
%[define_str2wcs_replacement(isxdigit = iswxdigit)]
%[define_str2wcs_replacement(isalnum = iswalnum)]
%[define_str2wcs_replacement(ispunct = iswpunct)]
%[define_str2wcs_replacement(isgraph = iswgraph)]
%[define_str2wcs_replacement(isprint = iswprint)]
%[define_str2wcs_replacement(tolower = towlower)]
%[define_str2wcs_replacement(toupper = towupper)]
%[define_str2wcs_replacement(isblank = iswblank)]
%[define_str2wcs_replacement(iscntrl_l = iswcntrl_l)]
%[define_str2wcs_replacement(isspace_l = iswspace_l)]
%[define_str2wcs_replacement(isupper_l = iswupper_l)]
%[define_str2wcs_replacement(islower_l = iswlower_l)]
%[define_str2wcs_replacement(isalpha_l = iswalpha_l)]
%[define_str2wcs_replacement(isdigit_l = iswdigit_l)]
%[define_str2wcs_replacement(isxdigit_l = iswxdigit_l)]
%[define_str2wcs_replacement(isalnum_l = iswalnum_l)]
%[define_str2wcs_replacement(ispunct_l = iswpunct_l)]
%[define_str2wcs_replacement(isgraph_l = iswgraph_l)]
%[define_str2wcs_replacement(isprint_l = iswprint_l)]
%[define_str2wcs_replacement(isblank_l = iswblank_l)]
%[define_str2wcs_replacement(tolower_l = towlower_l)]
%[define_str2wcs_replacement(toupper_l = towupper_l)]
%[define_str2wcs_replacement(isascii = iswascii)]
//%[define_str2wcs_replacement(toascii = "(wchar_t)towascii")]

%[define_wchar_replacement(wchar_t = char16_t, char32_t)]
%[define_wchar_replacement(wint_t = wint16_t, wint32_t)]
%[define_wchar_replacement(__WINT_TYPE__ = __WINT16_TYPE__, __WINT32_TYPE__)]
%[define_wchar_replacement(__WCHAR_TYPE__ = __CHAR16_TYPE__, __CHAR32_TYPE__)]
%[define_wchar_replacement(__SIZEOF_WINT_T__ = "2", "4")]
%[define_wchar_replacement(__SIZEOF_WCHAR_T__ = "2", "4")]
%[define_wchar_replacement(WEOF = __WEOF16, __WEOF32)]
%[define_wchar_replacement(__WEOF = __WEOF16, __WEOF32)]

%[assume_defined_in_kos_userspace(__crt_iswcntrl)]
%[assume_defined_in_kos_userspace(__crt_iswspace)]
%[assume_defined_in_kos_userspace(__crt_iswlower)]
%[assume_defined_in_kos_userspace(__crt_iswupper)]
%[assume_defined_in_kos_userspace(__crt_iswalpha)]
%[assume_defined_in_kos_userspace(__crt_iswdigit)]
%[assume_defined_in_kos_userspace(__crt_iswxdigit)]
%[assume_defined_in_kos_userspace(__crt_iswalnum)]
%[assume_defined_in_kos_userspace(__crt_iswpunct)]
%[assume_defined_in_kos_userspace(__crt_iswgraph)]
%[assume_defined_in_kos_userspace(__crt_iswprint)]
%[assume_defined_in_kos_userspace(__crt_iswblank)]
%[assume_defined_in_kos_userspace(__crt_towlower)]
%[assume_defined_in_kos_userspace(__crt_towupper)]


%(auto_header){
/* For the sake of optimization, allow libc auto
 * functions to make direct use of unicode data. */
#ifndef __KERNEL__
#define libc_iswcntrl(ch)  __crt_iswcntrl(ch)
#define libd_iswcntrl(ch)  ((wint16_t)__crt_iswcntrl(ch))
#define libc_iswspace(ch)  __crt_iswspace(ch)
#define libd_iswspace(ch)  ((wint16_t)__crt_iswspace(ch))
#define libc_iswupper(ch)  __crt_iswupper(ch)
#define libd_iswupper(ch)  ((wint16_t)__crt_iswupper(ch))
#define libc_iswlower(ch)  __crt_iswlower(ch)
#define libd_iswlower(ch)  ((wint16_t)__crt_iswlower(ch))
#define libc_iswalpha(ch)  __crt_iswalpha(ch)
#define libd_iswalpha(ch)  ((wint16_t)__crt_iswalpha(ch))
#define libc_iswdigit(ch)  __crt_iswdigit(ch)
#define libd_iswdigit(ch)  ((wint16_t)__crt_iswdigit(ch))
#define libc_iswxdigit(ch) __crt_iswxdigit(ch)
#define libd_iswxdigit(ch) ((wint16_t)__crt_iswxdigit(ch))
#define libc_iswalnum(ch)  __crt_iswalnum(ch)
#define libd_iswalnum(ch)  ((wint16_t)__crt_iswalnum(ch))
#define libc_iswpunct(ch)  __crt_iswpunct(ch)
#define libd_iswpunct(ch)  ((wint16_t)__crt_iswpunct(ch))
#define libc_iswgraph(ch)  __crt_iswgraph(ch)
#define libd_iswgraph(ch)  ((wint16_t)__crt_iswgraph(ch))
#define libc_iswprint(ch)  __crt_iswprint(ch)
#define libd_iswprint(ch)  ((wint16_t)__crt_iswprint(ch))
#define libc_iswblank(ch)  __crt_iswblank(ch)
#define libd_iswblank(ch)  ((wint16_t)__crt_iswblank(ch))
#define libc_towlower(ch)  __crt_towlower(ch)
#define libd_towlower(ch)  ((wint16_t)__crt_towlower(ch))
#define libc_towupper(ch)  __crt_towupper(ch)
#define libd_towupper(ch)  ((wint16_t)__crt_towupper(ch))
#endif /* !__KERNEL__ */
}


%[insert:prefix(
#include <features.h>
)]%[insert:prefix(
#include <hybrid/byteorder.h>
)]%[insert:prefix(
#include <hybrid/typecore.h>
)]%[insert:prefix(
#include <asm/crt/stdio.h>
)]%[insert:prefix(
#include <bits/crt/wctype.h>
)]%[insert:prefix(
#include <bits/types.h>
)]%{

#if defined(__USE_XOPEN2K8) || defined(__USE_DOS)
#include <xlocale.h>
#endif /* __USE_XOPEN2K8 || __USE_DOS */

#ifdef __USE_GLIBC
#include <endian.h>
#endif /* __USE_GLIBC */


#if !defined(WEOF) && defined(__WEOF)
#define WEOF __WEOF
#endif /* !WEOF && __WEOF */

#ifdef __CC__
__SYSDECL_BEGIN

__NAMESPACE_STD_BEGIN
#ifndef __std_wint_t_defined
#define __std_wint_t_defined
typedef __WINT_TYPE__ wint_t;
#endif /* !__std_wint_t_defined */
#ifndef __std_wctype_t_defined
#define __std_wctype_t_defined
typedef __wctype_t wctype_t;
#endif /* !__std_wctype_t_defined */
__NAMESPACE_STD_END

#ifndef __CXX_SYSTEM_HEADER
}%(c, ccompat){
#ifndef __wint_t_defined
#define __wint_t_defined
__NAMESPACE_STD_USING(wint_t)
#endif /* !__wint_t_defined */
#ifndef __wctype_t_defined
#define __wctype_t_defined
__NAMESPACE_STD_USING(wctype_t)
#endif /* !__wctype_t_defined */
}%{
#endif /* !__CXX_SYSTEM_HEADER */

#ifndef __wchar_t_defined
#define __wchar_t_defined
typedef __WCHAR_TYPE__ wchar_t;
#endif /* !__wchar_t_defined */

}
%[define_replacement(wctrans_t = __wctrans_t)]
%(c, ccompat){
#if defined(__USE_ISOC99) || defined(__USE_XOPEN2K8)
}%{
#ifndef __std_wctrans_t_defined
#define __std_wctrans_t_defined
__NAMESPACE_STD_BEGIN
typedef __wctrans_t wctrans_t;
__NAMESPACE_STD_END
#endif /* !__std_wctrans_t_defined */

#ifndef __CXX_SYSTEM_HEADER
}%(c, ccompat){
#ifndef __wctrans_t_defined
#define __wctrans_t_defined
__NAMESPACE_STD_USING(wctrans_t)
#endif /* !__wctrans_t_defined */
}%{
#endif /* !__CXX_SYSTEM_HEADER */
}%(c, ccompat){
#endif /* __USE_ISOC99 || __USE_XOPEN2K8 */
}%{


}

%[insert:std]
%[default:section(".text.crt{|.dos}.wchar.unicode.static.ctype")];

/*[[[deemon
local TRAITS = {
	"iswcntrl", "iswspace", "iswupper", "iswlower", "iswalpha",
	"iswdigit", "iswxdigit", "iswalnum", "iswpunct", "iswgraph",
	"iswprint", "towlower", "towupper"
};
function printTrait(name) {
	local isto = name.startswith("to");
	print("@@>> ", name, "(3)");
	print("[[if($extended_include_prefix(\"<bits/crt/wctype.h>\")defined(__crt_", name, ")), preferred_extern_inline(\"", name, "\", { return __crt_", name, "(wc); })]]");
	print("[[if($extended_include_prefix(\"<bits/crt/wctype.h>\")defined(__crt_", name, ")), preferred_inline({ return __crt_", name, "(wc); })]]");
	print("[[wchar, std, crtbuiltin, const, wunused, nothrow, impl_include(\"<bits/crt/wctype.h>\"), decl_include(\"<hybrid/typecore.h>\")]]");
	print(isto ? "wint_t " : "int ", name, "(wint_t wc) {");
	print("@@pp_ifdef __crt_", name, "@@");
	print("	return __crt_", name, "(wc);");
	print("@@pp_else@@");
	if (isto) {
		print("	return btowc(to", name[3:], "(wctob(wc)));");
	} else {
		print("	return is", name[3:], "(wctob(wc));");
	}
	print("@@pp_endif@@");
	print("}");
	print;
}
for (local name: TRAITS)
	printTrait(name);
print("%(c,std)#ifdef __USE_ISOC99");
printTrait("iswblank");
print("%(c,std)#endif /" "* __USE_ISOC99 *" "/");
]]]*/
@@>> iswcntrl(3)
[[if($extended_include_prefix("<bits/crt/wctype.h>")defined(__crt_iswcntrl)), preferred_extern_inline("iswcntrl", { return __crt_iswcntrl(wc); })]]
[[if($extended_include_prefix("<bits/crt/wctype.h>")defined(__crt_iswcntrl)), preferred_inline({ return __crt_iswcntrl(wc); })]]
[[wchar, std, crtbuiltin, const, wunused, nothrow, impl_include("<bits/crt/wctype.h>"), decl_include("<hybrid/typecore.h>")]]
int iswcntrl(wint_t wc) {
@@pp_ifdef __crt_iswcntrl@@
	return __crt_iswcntrl(wc);
@@pp_else@@
	return iscntrl(wctob(wc));
@@pp_endif@@
}

@@>> iswspace(3)
[[if($extended_include_prefix("<bits/crt/wctype.h>")defined(__crt_iswspace)), preferred_extern_inline("iswspace", { return __crt_iswspace(wc); })]]
[[if($extended_include_prefix("<bits/crt/wctype.h>")defined(__crt_iswspace)), preferred_inline({ return __crt_iswspace(wc); })]]
[[wchar, std, crtbuiltin, const, wunused, nothrow, impl_include("<bits/crt/wctype.h>"), decl_include("<hybrid/typecore.h>")]]
int iswspace(wint_t wc) {
@@pp_ifdef __crt_iswspace@@
	return __crt_iswspace(wc);
@@pp_else@@
	return isspace(wctob(wc));
@@pp_endif@@
}

@@>> iswupper(3)
[[if($extended_include_prefix("<bits/crt/wctype.h>")defined(__crt_iswupper)), preferred_extern_inline("iswupper", { return __crt_iswupper(wc); })]]
[[if($extended_include_prefix("<bits/crt/wctype.h>")defined(__crt_iswupper)), preferred_inline({ return __crt_iswupper(wc); })]]
[[wchar, std, crtbuiltin, const, wunused, nothrow, impl_include("<bits/crt/wctype.h>"), decl_include("<hybrid/typecore.h>")]]
int iswupper(wint_t wc) {
@@pp_ifdef __crt_iswupper@@
	return __crt_iswupper(wc);
@@pp_else@@
	return isupper(wctob(wc));
@@pp_endif@@
}

@@>> iswlower(3)
[[if($extended_include_prefix("<bits/crt/wctype.h>")defined(__crt_iswlower)), preferred_extern_inline("iswlower", { return __crt_iswlower(wc); })]]
[[if($extended_include_prefix("<bits/crt/wctype.h>")defined(__crt_iswlower)), preferred_inline({ return __crt_iswlower(wc); })]]
[[wchar, std, crtbuiltin, const, wunused, nothrow, impl_include("<bits/crt/wctype.h>"), decl_include("<hybrid/typecore.h>")]]
int iswlower(wint_t wc) {
@@pp_ifdef __crt_iswlower@@
	return __crt_iswlower(wc);
@@pp_else@@
	return islower(wctob(wc));
@@pp_endif@@
}

@@>> iswalpha(3)
[[if($extended_include_prefix("<bits/crt/wctype.h>")defined(__crt_iswalpha)), preferred_extern_inline("iswalpha", { return __crt_iswalpha(wc); })]]
[[if($extended_include_prefix("<bits/crt/wctype.h>")defined(__crt_iswalpha)), preferred_inline({ return __crt_iswalpha(wc); })]]
[[wchar, std, crtbuiltin, const, wunused, nothrow, impl_include("<bits/crt/wctype.h>"), decl_include("<hybrid/typecore.h>")]]
int iswalpha(wint_t wc) {
@@pp_ifdef __crt_iswalpha@@
	return __crt_iswalpha(wc);
@@pp_else@@
	return isalpha(wctob(wc));
@@pp_endif@@
}

@@>> iswdigit(3)
[[if($extended_include_prefix("<bits/crt/wctype.h>")defined(__crt_iswdigit)), preferred_extern_inline("iswdigit", { return __crt_iswdigit(wc); })]]
[[if($extended_include_prefix("<bits/crt/wctype.h>")defined(__crt_iswdigit)), preferred_inline({ return __crt_iswdigit(wc); })]]
[[wchar, std, crtbuiltin, const, wunused, nothrow, impl_include("<bits/crt/wctype.h>"), decl_include("<hybrid/typecore.h>")]]
int iswdigit(wint_t wc) {
@@pp_ifdef __crt_iswdigit@@
	return __crt_iswdigit(wc);
@@pp_else@@
	return isdigit(wctob(wc));
@@pp_endif@@
}

@@>> iswxdigit(3)
[[if($extended_include_prefix("<bits/crt/wctype.h>")defined(__crt_iswxdigit)), preferred_extern_inline("iswxdigit", { return __crt_iswxdigit(wc); })]]
[[if($extended_include_prefix("<bits/crt/wctype.h>")defined(__crt_iswxdigit)), preferred_inline({ return __crt_iswxdigit(wc); })]]
[[wchar, std, crtbuiltin, const, wunused, nothrow, impl_include("<bits/crt/wctype.h>"), decl_include("<hybrid/typecore.h>")]]
int iswxdigit(wint_t wc) {
@@pp_ifdef __crt_iswxdigit@@
	return __crt_iswxdigit(wc);
@@pp_else@@
	return isxdigit(wctob(wc));
@@pp_endif@@
}

@@>> iswalnum(3)
[[if($extended_include_prefix("<bits/crt/wctype.h>")defined(__crt_iswalnum)), preferred_extern_inline("iswalnum", { return __crt_iswalnum(wc); })]]
[[if($extended_include_prefix("<bits/crt/wctype.h>")defined(__crt_iswalnum)), preferred_inline({ return __crt_iswalnum(wc); })]]
[[wchar, std, crtbuiltin, const, wunused, nothrow, impl_include("<bits/crt/wctype.h>"), decl_include("<hybrid/typecore.h>")]]
int iswalnum(wint_t wc) {
@@pp_ifdef __crt_iswalnum@@
	return __crt_iswalnum(wc);
@@pp_else@@
	return isalnum(wctob(wc));
@@pp_endif@@
}

@@>> iswpunct(3)
[[if($extended_include_prefix("<bits/crt/wctype.h>")defined(__crt_iswpunct)), preferred_extern_inline("iswpunct", { return __crt_iswpunct(wc); })]]
[[if($extended_include_prefix("<bits/crt/wctype.h>")defined(__crt_iswpunct)), preferred_inline({ return __crt_iswpunct(wc); })]]
[[wchar, std, crtbuiltin, const, wunused, nothrow, impl_include("<bits/crt/wctype.h>"), decl_include("<hybrid/typecore.h>")]]
int iswpunct(wint_t wc) {
@@pp_ifdef __crt_iswpunct@@
	return __crt_iswpunct(wc);
@@pp_else@@
	return ispunct(wctob(wc));
@@pp_endif@@
}

@@>> iswgraph(3)
[[if($extended_include_prefix("<bits/crt/wctype.h>")defined(__crt_iswgraph)), preferred_extern_inline("iswgraph", { return __crt_iswgraph(wc); })]]
[[if($extended_include_prefix("<bits/crt/wctype.h>")defined(__crt_iswgraph)), preferred_inline({ return __crt_iswgraph(wc); })]]
[[wchar, std, crtbuiltin, const, wunused, nothrow, impl_include("<bits/crt/wctype.h>"), decl_include("<hybrid/typecore.h>")]]
int iswgraph(wint_t wc) {
@@pp_ifdef __crt_iswgraph@@
	return __crt_iswgraph(wc);
@@pp_else@@
	return isgraph(wctob(wc));
@@pp_endif@@
}

@@>> iswprint(3)
[[if($extended_include_prefix("<bits/crt/wctype.h>")defined(__crt_iswprint)), preferred_extern_inline("iswprint", { return __crt_iswprint(wc); })]]
[[if($extended_include_prefix("<bits/crt/wctype.h>")defined(__crt_iswprint)), preferred_inline({ return __crt_iswprint(wc); })]]
[[wchar, std, crtbuiltin, const, wunused, nothrow, impl_include("<bits/crt/wctype.h>"), decl_include("<hybrid/typecore.h>")]]
int iswprint(wint_t wc) {
@@pp_ifdef __crt_iswprint@@
	return __crt_iswprint(wc);
@@pp_else@@
	return isprint(wctob(wc));
@@pp_endif@@
}

@@>> towlower(3)
[[if($extended_include_prefix("<bits/crt/wctype.h>")defined(__crt_towlower)), preferred_extern_inline("towlower", { return __crt_towlower(wc); })]]
[[if($extended_include_prefix("<bits/crt/wctype.h>")defined(__crt_towlower)), preferred_inline({ return __crt_towlower(wc); })]]
[[wchar, std, crtbuiltin, const, wunused, nothrow, impl_include("<bits/crt/wctype.h>"), decl_include("<hybrid/typecore.h>")]]
wint_t towlower(wint_t wc) {
@@pp_ifdef __crt_towlower@@
	return __crt_towlower(wc);
@@pp_else@@
	return btowc(tolower(wctob(wc)));
@@pp_endif@@
}

@@>> towupper(3)
[[if($extended_include_prefix("<bits/crt/wctype.h>")defined(__crt_towupper)), preferred_extern_inline("towupper", { return __crt_towupper(wc); })]]
[[if($extended_include_prefix("<bits/crt/wctype.h>")defined(__crt_towupper)), preferred_inline({ return __crt_towupper(wc); })]]
[[wchar, std, crtbuiltin, const, wunused, nothrow, impl_include("<bits/crt/wctype.h>"), decl_include("<hybrid/typecore.h>")]]
wint_t towupper(wint_t wc) {
@@pp_ifdef __crt_towupper@@
	return __crt_towupper(wc);
@@pp_else@@
	return btowc(toupper(wctob(wc)));
@@pp_endif@@
}

%(c,std)#ifdef __USE_ISOC99
@@>> iswblank(3)
[[if($extended_include_prefix("<bits/crt/wctype.h>")defined(__crt_iswblank)), preferred_extern_inline("iswblank", { return __crt_iswblank(wc); })]]
[[if($extended_include_prefix("<bits/crt/wctype.h>")defined(__crt_iswblank)), preferred_inline({ return __crt_iswblank(wc); })]]
[[wchar, std, crtbuiltin, const, wunused, nothrow, impl_include("<bits/crt/wctype.h>"), decl_include("<hybrid/typecore.h>")]]
int iswblank(wint_t wc) {
@@pp_ifdef __crt_iswblank@@
	return __crt_iswblank(wc);
@@pp_else@@
	return isblank(wctob(wc));
@@pp_endif@@
}

%(c,std)#endif /* __USE_ISOC99 */
/*[[[end]]]*/




%(c,std)#ifdef __USE_ISOC99

[[std, guard, pure, wunused, requires(defined(__CRT_KOS))]]
[[decl_include("<bits/crt/wctype.h>")]]
[[impl_include("<bits/crt/unicode.h>")]]
wctrans_t wctrans([[in]] char const *prop) {
	struct wctrans_entry {
		char     we_name[8]; /* Name (including the leading "to") */
		uint16_t we_offset;  /* Offset to `int32_t' field in `struct __unitraits' */
	};
	static struct wctrans_entry const entries[] = {
		{ "tolower", offsetof(struct @__unitraits@, @__ut_lower@) },
		{ "toupper", offsetof(struct @__unitraits@, @__ut_upper@) },
		{ "totitle", offsetof(struct @__unitraits@, @__ut_title@) }, /* Kos extension! */
	};
	unsigned int i;
	for (i = 0; i < COMPILER_LENOF(entries); ++i) {
		if (strcmp(prop, entries[i].we_name) == 0)
			return (wctrans_t)(uintptr_t)entries[i].we_offset;
	}
	return (wctrans_t)0;
}

[[decl_include("<hybrid/typecore.h>", "<bits/crt/wctype.h>")]]
[[std, wchar, guard, const, wunused, export_alias("__towctrans")]]
[[requires(defined(__CRT_KOS) && $has_function(__unicode_descriptor))]]
[[impl_include("<bits/crt/unicode.h>")]]
wint_t towctrans(wint_t wc, wctrans_t desc) {
	struct @__unitraits@ const *traits = __unicode_descriptor(wc);
	return wc + *((s32 const *)traits + (uintptr_t)desc);
}
%(c,std)#endif /* __USE_ISOC99 */

[[std, pure, wunused]]
[[decl_include("<bits/crt/wctype.h>")]]
[[requires(defined(__CRT_KOS) && $has_function(__unicode_descriptor))]]
[[impl_include("<bits/crt/unicode.h>")]]
wctype_t wctype([[in]] char const *prop) {
	struct wctype_entry {
		char     we_name[8]; /* Name (with leading "is" stripped) */
		uint16_t we_flags;   /* Flags that must be set. */
	};
	static struct wctype_entry const entries[] = {
		{ "cntrl",   __UNICODE_ISCNTRL },
		{ "space",   __UNICODE_ISSPACE },
		{ "lower",   __UNICODE_ISLOWER },
		{ "upper",   __UNICODE_ISUPPER },
		{ "alpha",   __UNICODE_ISALPHA },
		{ "digit",   __UNICODE_ISDIGIT },
		{ "xdigit",  __UNICODE_ISXDIGIT },
		{ "alnum",   __UNICODE_ISALNUM },
		{ "punct",   __UNICODE_ISPUNCT },
		{ "graph",   __UNICODE_ISGRAPH },
		{ "print",   __UNICODE_ISPRINT },
		{ "blank",   __UNICODE_ISBLANK },
		/* All of the following are KOS extensions! */
		{ "tab",     __UNICODE_ISTAB },
		{ "white",   __UNICODE_ISWHITE },
		{ "empty",   __UNICODE_ISEMPTY },
		{ "lf",      __UNICODE_ISLF },
		{ "hex",     __UNICODE_ISHEX },
		{ "title",   __UNICODE_ISTITLE },
		{ "numeric", __UNICODE_ISNUMERIC },
		{ "symstrt", __UNICODE_ISSYMSTRT },
		{ "symcont", __UNICODE_ISSYMCONT },
	};
	unsigned int i;
	for (i = 0; i < COMPILER_LENOF(entries); ++i) {
		if (strcmp(prop, entries[i].we_name) == 0)
			return entries[i].we_flags;
	}
	return 0;
}

[[decl_include("<hybrid/typecore.h>", "<bits/crt/wctype.h>")]]
[[std, wchar, const, wunused, export_alias("is_wctype", "__iswctype")]]
[[requires(defined(__CRT_KOS) && $has_function(__unicode_descriptor))]]
[[impl_include("<bits/crt/unicode.h>")]]
int iswctype($wint_t wc, $wctype_t desc) {
	struct @__unitraits@ const *traits = __unicode_descriptor(wc);
	return (int)(traits->@__ut_flags@ & (uint16_t)desc);
}


%
%#if defined(__USE_KOS) || defined(__USE_DOS)
[[decl_include("<hybrid/typecore.h>")]]
[[wchar, const, wunused, nothrow]]
int iswascii($wint_t wc) {
	return wc >= 0 && wc <= 0x7f;
}
%#endif /* __USE_KOS || __USE_DOS */


%
%#ifdef __USE_XOPEN2K8

%[default:section(".text.crt{|.dos}.wchar.unicode.locale.ctype")]

/*[[[deemon
local TRAITS = {
	"iswcntrl", "iswspace", "iswupper", "iswlower", "iswalpha",
	"iswdigit", "iswxdigit", "iswalnum", "iswpunct", "iswgraph",
	"iswprint", "iswblank", "towlower", "towupper"
};
function printTrait(name) {
	print("@@>> ", name, "_l(3)");
	print("[[wchar, pure, wunused, decl_include(\"<hybrid/typecore.h>\")]]");
	print("[[if($extended_include_prefix(\"<bits/crt/wctype.h>\")defined(__crt_", name, "_l)), preferred_extern_inline(\"", name, "_l\", { return __crt_", name, "_l(ch, locale); })]]");
	print("[[if($extended_include_prefix(\"<bits/crt/wctype.h>\")defined(__crt_", name, "_l)), preferred_extern_inline(\"_", name, "_l\", { return __crt_", name, "_l(ch, locale); })]]");
	print("[[if($extended_include_prefix(\"<bits/crt/wctype.h>\")defined(__crt_", name, "_l)), preferred_extern_inline(\"__", name, "_l\", { return __crt_", name, "_l(ch, locale); })]]");
	print("[[if($extended_include_prefix(\"<bits/crt/wctype.h>\")defined(__crt_", name, "_l)), preferred_inline({ return __crt_", name, "_l(ch, locale); })]]");
	print("[[dos_export_alias(\"_", name, "_l\"), export_alias(\"__", name, "_l\")]]");
	print("[[if($extended_include_prefix(\"<bits/crt/wctype.h>\")defined(__crt_", name, ")), inline({ COMPILER_IMPURE(); (void)locale; return __crt_", name, "(ch); })]]");
	print("[[if(defined(__LIBKCALL_CALLER_CLEANUP)), crt_intern_kos_alias(\"libc_", name, "\")]]");
	print("[[if(defined(__LIBDCALL_CALLER_CLEANUP)), crt_intern_dos_alias(\"libd_", name, "\")]]");
	print(name.startswith("to") ? "$wint_t " : "int ", name, "_l($wint_t ch, $locale_t locale) {");
	print("	COMPILER_IMPURE();");
	print("	(void)locale;");
	print("	return ", name, "(ch);");
	print("}");
	print;
}
for (local name: TRAITS)
	printTrait(name);
]]]*/
@@>> iswcntrl_l(3)
[[wchar, pure, wunused, decl_include("<hybrid/typecore.h>")]]
[[if($extended_include_prefix("<bits/crt/wctype.h>")defined(__crt_iswcntrl_l)), preferred_extern_inline("iswcntrl_l", { return __crt_iswcntrl_l(ch, locale); })]]
[[if($extended_include_prefix("<bits/crt/wctype.h>")defined(__crt_iswcntrl_l)), preferred_extern_inline("_iswcntrl_l", { return __crt_iswcntrl_l(ch, locale); })]]
[[if($extended_include_prefix("<bits/crt/wctype.h>")defined(__crt_iswcntrl_l)), preferred_extern_inline("__iswcntrl_l", { return __crt_iswcntrl_l(ch, locale); })]]
[[if($extended_include_prefix("<bits/crt/wctype.h>")defined(__crt_iswcntrl_l)), preferred_inline({ return __crt_iswcntrl_l(ch, locale); })]]
[[dos_export_alias("_iswcntrl_l"), export_alias("__iswcntrl_l")]]
[[if($extended_include_prefix("<bits/crt/wctype.h>")defined(__crt_iswcntrl)), inline({ COMPILER_IMPURE(); (void)locale; return __crt_iswcntrl(ch); })]]
[[if(defined(__LIBKCALL_CALLER_CLEANUP)), crt_intern_kos_alias("libc_iswcntrl")]]
[[if(defined(__LIBDCALL_CALLER_CLEANUP)), crt_intern_dos_alias("libd_iswcntrl")]]
int iswcntrl_l($wint_t ch, $locale_t locale) {
	COMPILER_IMPURE();
	(void)locale;
	return iswcntrl(ch);
}

@@>> iswspace_l(3)
[[wchar, pure, wunused, decl_include("<hybrid/typecore.h>")]]
[[if($extended_include_prefix("<bits/crt/wctype.h>")defined(__crt_iswspace_l)), preferred_extern_inline("iswspace_l", { return __crt_iswspace_l(ch, locale); })]]
[[if($extended_include_prefix("<bits/crt/wctype.h>")defined(__crt_iswspace_l)), preferred_extern_inline("_iswspace_l", { return __crt_iswspace_l(ch, locale); })]]
[[if($extended_include_prefix("<bits/crt/wctype.h>")defined(__crt_iswspace_l)), preferred_extern_inline("__iswspace_l", { return __crt_iswspace_l(ch, locale); })]]
[[if($extended_include_prefix("<bits/crt/wctype.h>")defined(__crt_iswspace_l)), preferred_inline({ return __crt_iswspace_l(ch, locale); })]]
[[dos_export_alias("_iswspace_l"), export_alias("__iswspace_l")]]
[[if($extended_include_prefix("<bits/crt/wctype.h>")defined(__crt_iswspace)), inline({ COMPILER_IMPURE(); (void)locale; return __crt_iswspace(ch); })]]
[[if(defined(__LIBKCALL_CALLER_CLEANUP)), crt_intern_kos_alias("libc_iswspace")]]
[[if(defined(__LIBDCALL_CALLER_CLEANUP)), crt_intern_dos_alias("libd_iswspace")]]
int iswspace_l($wint_t ch, $locale_t locale) {
	COMPILER_IMPURE();
	(void)locale;
	return iswspace(ch);
}

@@>> iswupper_l(3)
[[wchar, pure, wunused, decl_include("<hybrid/typecore.h>")]]
[[if($extended_include_prefix("<bits/crt/wctype.h>")defined(__crt_iswupper_l)), preferred_extern_inline("iswupper_l", { return __crt_iswupper_l(ch, locale); })]]
[[if($extended_include_prefix("<bits/crt/wctype.h>")defined(__crt_iswupper_l)), preferred_extern_inline("_iswupper_l", { return __crt_iswupper_l(ch, locale); })]]
[[if($extended_include_prefix("<bits/crt/wctype.h>")defined(__crt_iswupper_l)), preferred_extern_inline("__iswupper_l", { return __crt_iswupper_l(ch, locale); })]]
[[if($extended_include_prefix("<bits/crt/wctype.h>")defined(__crt_iswupper_l)), preferred_inline({ return __crt_iswupper_l(ch, locale); })]]
[[dos_export_alias("_iswupper_l"), export_alias("__iswupper_l")]]
[[if($extended_include_prefix("<bits/crt/wctype.h>")defined(__crt_iswupper)), inline({ COMPILER_IMPURE(); (void)locale; return __crt_iswupper(ch); })]]
[[if(defined(__LIBKCALL_CALLER_CLEANUP)), crt_intern_kos_alias("libc_iswupper")]]
[[if(defined(__LIBDCALL_CALLER_CLEANUP)), crt_intern_dos_alias("libd_iswupper")]]
int iswupper_l($wint_t ch, $locale_t locale) {
	COMPILER_IMPURE();
	(void)locale;
	return iswupper(ch);
}

@@>> iswlower_l(3)
[[wchar, pure, wunused, decl_include("<hybrid/typecore.h>")]]
[[if($extended_include_prefix("<bits/crt/wctype.h>")defined(__crt_iswlower_l)), preferred_extern_inline("iswlower_l", { return __crt_iswlower_l(ch, locale); })]]
[[if($extended_include_prefix("<bits/crt/wctype.h>")defined(__crt_iswlower_l)), preferred_extern_inline("_iswlower_l", { return __crt_iswlower_l(ch, locale); })]]
[[if($extended_include_prefix("<bits/crt/wctype.h>")defined(__crt_iswlower_l)), preferred_extern_inline("__iswlower_l", { return __crt_iswlower_l(ch, locale); })]]
[[if($extended_include_prefix("<bits/crt/wctype.h>")defined(__crt_iswlower_l)), preferred_inline({ return __crt_iswlower_l(ch, locale); })]]
[[dos_export_alias("_iswlower_l"), export_alias("__iswlower_l")]]
[[if($extended_include_prefix("<bits/crt/wctype.h>")defined(__crt_iswlower)), inline({ COMPILER_IMPURE(); (void)locale; return __crt_iswlower(ch); })]]
[[if(defined(__LIBKCALL_CALLER_CLEANUP)), crt_intern_kos_alias("libc_iswlower")]]
[[if(defined(__LIBDCALL_CALLER_CLEANUP)), crt_intern_dos_alias("libd_iswlower")]]
int iswlower_l($wint_t ch, $locale_t locale) {
	COMPILER_IMPURE();
	(void)locale;
	return iswlower(ch);
}

@@>> iswalpha_l(3)
[[wchar, pure, wunused, decl_include("<hybrid/typecore.h>")]]
[[if($extended_include_prefix("<bits/crt/wctype.h>")defined(__crt_iswalpha_l)), preferred_extern_inline("iswalpha_l", { return __crt_iswalpha_l(ch, locale); })]]
[[if($extended_include_prefix("<bits/crt/wctype.h>")defined(__crt_iswalpha_l)), preferred_extern_inline("_iswalpha_l", { return __crt_iswalpha_l(ch, locale); })]]
[[if($extended_include_prefix("<bits/crt/wctype.h>")defined(__crt_iswalpha_l)), preferred_extern_inline("__iswalpha_l", { return __crt_iswalpha_l(ch, locale); })]]
[[if($extended_include_prefix("<bits/crt/wctype.h>")defined(__crt_iswalpha_l)), preferred_inline({ return __crt_iswalpha_l(ch, locale); })]]
[[dos_export_alias("_iswalpha_l"), export_alias("__iswalpha_l")]]
[[if($extended_include_prefix("<bits/crt/wctype.h>")defined(__crt_iswalpha)), inline({ COMPILER_IMPURE(); (void)locale; return __crt_iswalpha(ch); })]]
[[if(defined(__LIBKCALL_CALLER_CLEANUP)), crt_intern_kos_alias("libc_iswalpha")]]
[[if(defined(__LIBDCALL_CALLER_CLEANUP)), crt_intern_dos_alias("libd_iswalpha")]]
int iswalpha_l($wint_t ch, $locale_t locale) {
	COMPILER_IMPURE();
	(void)locale;
	return iswalpha(ch);
}

@@>> iswdigit_l(3)
[[wchar, pure, wunused, decl_include("<hybrid/typecore.h>")]]
[[if($extended_include_prefix("<bits/crt/wctype.h>")defined(__crt_iswdigit_l)), preferred_extern_inline("iswdigit_l", { return __crt_iswdigit_l(ch, locale); })]]
[[if($extended_include_prefix("<bits/crt/wctype.h>")defined(__crt_iswdigit_l)), preferred_extern_inline("_iswdigit_l", { return __crt_iswdigit_l(ch, locale); })]]
[[if($extended_include_prefix("<bits/crt/wctype.h>")defined(__crt_iswdigit_l)), preferred_extern_inline("__iswdigit_l", { return __crt_iswdigit_l(ch, locale); })]]
[[if($extended_include_prefix("<bits/crt/wctype.h>")defined(__crt_iswdigit_l)), preferred_inline({ return __crt_iswdigit_l(ch, locale); })]]
[[dos_export_alias("_iswdigit_l"), export_alias("__iswdigit_l")]]
[[if($extended_include_prefix("<bits/crt/wctype.h>")defined(__crt_iswdigit)), inline({ COMPILER_IMPURE(); (void)locale; return __crt_iswdigit(ch); })]]
[[if(defined(__LIBKCALL_CALLER_CLEANUP)), crt_intern_kos_alias("libc_iswdigit")]]
[[if(defined(__LIBDCALL_CALLER_CLEANUP)), crt_intern_dos_alias("libd_iswdigit")]]
int iswdigit_l($wint_t ch, $locale_t locale) {
	COMPILER_IMPURE();
	(void)locale;
	return iswdigit(ch);
}

@@>> iswxdigit_l(3)
[[wchar, pure, wunused, decl_include("<hybrid/typecore.h>")]]
[[if($extended_include_prefix("<bits/crt/wctype.h>")defined(__crt_iswxdigit_l)), preferred_extern_inline("iswxdigit_l", { return __crt_iswxdigit_l(ch, locale); })]]
[[if($extended_include_prefix("<bits/crt/wctype.h>")defined(__crt_iswxdigit_l)), preferred_extern_inline("_iswxdigit_l", { return __crt_iswxdigit_l(ch, locale); })]]
[[if($extended_include_prefix("<bits/crt/wctype.h>")defined(__crt_iswxdigit_l)), preferred_extern_inline("__iswxdigit_l", { return __crt_iswxdigit_l(ch, locale); })]]
[[if($extended_include_prefix("<bits/crt/wctype.h>")defined(__crt_iswxdigit_l)), preferred_inline({ return __crt_iswxdigit_l(ch, locale); })]]
[[dos_export_alias("_iswxdigit_l"), export_alias("__iswxdigit_l")]]
[[if($extended_include_prefix("<bits/crt/wctype.h>")defined(__crt_iswxdigit)), inline({ COMPILER_IMPURE(); (void)locale; return __crt_iswxdigit(ch); })]]
[[if(defined(__LIBKCALL_CALLER_CLEANUP)), crt_intern_kos_alias("libc_iswxdigit")]]
[[if(defined(__LIBDCALL_CALLER_CLEANUP)), crt_intern_dos_alias("libd_iswxdigit")]]
int iswxdigit_l($wint_t ch, $locale_t locale) {
	COMPILER_IMPURE();
	(void)locale;
	return iswxdigit(ch);
}

@@>> iswalnum_l(3)
[[wchar, pure, wunused, decl_include("<hybrid/typecore.h>")]]
[[if($extended_include_prefix("<bits/crt/wctype.h>")defined(__crt_iswalnum_l)), preferred_extern_inline("iswalnum_l", { return __crt_iswalnum_l(ch, locale); })]]
[[if($extended_include_prefix("<bits/crt/wctype.h>")defined(__crt_iswalnum_l)), preferred_extern_inline("_iswalnum_l", { return __crt_iswalnum_l(ch, locale); })]]
[[if($extended_include_prefix("<bits/crt/wctype.h>")defined(__crt_iswalnum_l)), preferred_extern_inline("__iswalnum_l", { return __crt_iswalnum_l(ch, locale); })]]
[[if($extended_include_prefix("<bits/crt/wctype.h>")defined(__crt_iswalnum_l)), preferred_inline({ return __crt_iswalnum_l(ch, locale); })]]
[[dos_export_alias("_iswalnum_l"), export_alias("__iswalnum_l")]]
[[if($extended_include_prefix("<bits/crt/wctype.h>")defined(__crt_iswalnum)), inline({ COMPILER_IMPURE(); (void)locale; return __crt_iswalnum(ch); })]]
[[if(defined(__LIBKCALL_CALLER_CLEANUP)), crt_intern_kos_alias("libc_iswalnum")]]
[[if(defined(__LIBDCALL_CALLER_CLEANUP)), crt_intern_dos_alias("libd_iswalnum")]]
int iswalnum_l($wint_t ch, $locale_t locale) {
	COMPILER_IMPURE();
	(void)locale;
	return iswalnum(ch);
}

@@>> iswpunct_l(3)
[[wchar, pure, wunused, decl_include("<hybrid/typecore.h>")]]
[[if($extended_include_prefix("<bits/crt/wctype.h>")defined(__crt_iswpunct_l)), preferred_extern_inline("iswpunct_l", { return __crt_iswpunct_l(ch, locale); })]]
[[if($extended_include_prefix("<bits/crt/wctype.h>")defined(__crt_iswpunct_l)), preferred_extern_inline("_iswpunct_l", { return __crt_iswpunct_l(ch, locale); })]]
[[if($extended_include_prefix("<bits/crt/wctype.h>")defined(__crt_iswpunct_l)), preferred_extern_inline("__iswpunct_l", { return __crt_iswpunct_l(ch, locale); })]]
[[if($extended_include_prefix("<bits/crt/wctype.h>")defined(__crt_iswpunct_l)), preferred_inline({ return __crt_iswpunct_l(ch, locale); })]]
[[dos_export_alias("_iswpunct_l"), export_alias("__iswpunct_l")]]
[[if($extended_include_prefix("<bits/crt/wctype.h>")defined(__crt_iswpunct)), inline({ COMPILER_IMPURE(); (void)locale; return __crt_iswpunct(ch); })]]
[[if(defined(__LIBKCALL_CALLER_CLEANUP)), crt_intern_kos_alias("libc_iswpunct")]]
[[if(defined(__LIBDCALL_CALLER_CLEANUP)), crt_intern_dos_alias("libd_iswpunct")]]
int iswpunct_l($wint_t ch, $locale_t locale) {
	COMPILER_IMPURE();
	(void)locale;
	return iswpunct(ch);
}

@@>> iswgraph_l(3)
[[wchar, pure, wunused, decl_include("<hybrid/typecore.h>")]]
[[if($extended_include_prefix("<bits/crt/wctype.h>")defined(__crt_iswgraph_l)), preferred_extern_inline("iswgraph_l", { return __crt_iswgraph_l(ch, locale); })]]
[[if($extended_include_prefix("<bits/crt/wctype.h>")defined(__crt_iswgraph_l)), preferred_extern_inline("_iswgraph_l", { return __crt_iswgraph_l(ch, locale); })]]
[[if($extended_include_prefix("<bits/crt/wctype.h>")defined(__crt_iswgraph_l)), preferred_extern_inline("__iswgraph_l", { return __crt_iswgraph_l(ch, locale); })]]
[[if($extended_include_prefix("<bits/crt/wctype.h>")defined(__crt_iswgraph_l)), preferred_inline({ return __crt_iswgraph_l(ch, locale); })]]
[[dos_export_alias("_iswgraph_l"), export_alias("__iswgraph_l")]]
[[if($extended_include_prefix("<bits/crt/wctype.h>")defined(__crt_iswgraph)), inline({ COMPILER_IMPURE(); (void)locale; return __crt_iswgraph(ch); })]]
[[if(defined(__LIBKCALL_CALLER_CLEANUP)), crt_intern_kos_alias("libc_iswgraph")]]
[[if(defined(__LIBDCALL_CALLER_CLEANUP)), crt_intern_dos_alias("libd_iswgraph")]]
int iswgraph_l($wint_t ch, $locale_t locale) {
	COMPILER_IMPURE();
	(void)locale;
	return iswgraph(ch);
}

@@>> iswprint_l(3)
[[wchar, pure, wunused, decl_include("<hybrid/typecore.h>")]]
[[if($extended_include_prefix("<bits/crt/wctype.h>")defined(__crt_iswprint_l)), preferred_extern_inline("iswprint_l", { return __crt_iswprint_l(ch, locale); })]]
[[if($extended_include_prefix("<bits/crt/wctype.h>")defined(__crt_iswprint_l)), preferred_extern_inline("_iswprint_l", { return __crt_iswprint_l(ch, locale); })]]
[[if($extended_include_prefix("<bits/crt/wctype.h>")defined(__crt_iswprint_l)), preferred_extern_inline("__iswprint_l", { return __crt_iswprint_l(ch, locale); })]]
[[if($extended_include_prefix("<bits/crt/wctype.h>")defined(__crt_iswprint_l)), preferred_inline({ return __crt_iswprint_l(ch, locale); })]]
[[dos_export_alias("_iswprint_l"), export_alias("__iswprint_l")]]
[[if($extended_include_prefix("<bits/crt/wctype.h>")defined(__crt_iswprint)), inline({ COMPILER_IMPURE(); (void)locale; return __crt_iswprint(ch); })]]
[[if(defined(__LIBKCALL_CALLER_CLEANUP)), crt_intern_kos_alias("libc_iswprint")]]
[[if(defined(__LIBDCALL_CALLER_CLEANUP)), crt_intern_dos_alias("libd_iswprint")]]
int iswprint_l($wint_t ch, $locale_t locale) {
	COMPILER_IMPURE();
	(void)locale;
	return iswprint(ch);
}

@@>> iswblank_l(3)
[[wchar, pure, wunused, decl_include("<hybrid/typecore.h>")]]
[[if($extended_include_prefix("<bits/crt/wctype.h>")defined(__crt_iswblank_l)), preferred_extern_inline("iswblank_l", { return __crt_iswblank_l(ch, locale); })]]
[[if($extended_include_prefix("<bits/crt/wctype.h>")defined(__crt_iswblank_l)), preferred_extern_inline("_iswblank_l", { return __crt_iswblank_l(ch, locale); })]]
[[if($extended_include_prefix("<bits/crt/wctype.h>")defined(__crt_iswblank_l)), preferred_extern_inline("__iswblank_l", { return __crt_iswblank_l(ch, locale); })]]
[[if($extended_include_prefix("<bits/crt/wctype.h>")defined(__crt_iswblank_l)), preferred_inline({ return __crt_iswblank_l(ch, locale); })]]
[[dos_export_alias("_iswblank_l"), export_alias("__iswblank_l")]]
[[if($extended_include_prefix("<bits/crt/wctype.h>")defined(__crt_iswblank)), inline({ COMPILER_IMPURE(); (void)locale; return __crt_iswblank(ch); })]]
[[if(defined(__LIBKCALL_CALLER_CLEANUP)), crt_intern_kos_alias("libc_iswblank")]]
[[if(defined(__LIBDCALL_CALLER_CLEANUP)), crt_intern_dos_alias("libd_iswblank")]]
int iswblank_l($wint_t ch, $locale_t locale) {
	COMPILER_IMPURE();
	(void)locale;
	return iswblank(ch);
}

@@>> towlower_l(3)
[[wchar, pure, wunused, decl_include("<hybrid/typecore.h>")]]
[[if($extended_include_prefix("<bits/crt/wctype.h>")defined(__crt_towlower_l)), preferred_extern_inline("towlower_l", { return __crt_towlower_l(ch, locale); })]]
[[if($extended_include_prefix("<bits/crt/wctype.h>")defined(__crt_towlower_l)), preferred_extern_inline("_towlower_l", { return __crt_towlower_l(ch, locale); })]]
[[if($extended_include_prefix("<bits/crt/wctype.h>")defined(__crt_towlower_l)), preferred_extern_inline("__towlower_l", { return __crt_towlower_l(ch, locale); })]]
[[if($extended_include_prefix("<bits/crt/wctype.h>")defined(__crt_towlower_l)), preferred_inline({ return __crt_towlower_l(ch, locale); })]]
[[dos_export_alias("_towlower_l"), export_alias("__towlower_l")]]
[[if($extended_include_prefix("<bits/crt/wctype.h>")defined(__crt_towlower)), inline({ COMPILER_IMPURE(); (void)locale; return __crt_towlower(ch); })]]
[[if(defined(__LIBKCALL_CALLER_CLEANUP)), crt_intern_kos_alias("libc_towlower")]]
[[if(defined(__LIBDCALL_CALLER_CLEANUP)), crt_intern_dos_alias("libd_towlower")]]
$wint_t towlower_l($wint_t ch, $locale_t locale) {
	COMPILER_IMPURE();
	(void)locale;
	return towlower(ch);
}

@@>> towupper_l(3)
[[wchar, pure, wunused, decl_include("<hybrid/typecore.h>")]]
[[if($extended_include_prefix("<bits/crt/wctype.h>")defined(__crt_towupper_l)), preferred_extern_inline("towupper_l", { return __crt_towupper_l(ch, locale); })]]
[[if($extended_include_prefix("<bits/crt/wctype.h>")defined(__crt_towupper_l)), preferred_extern_inline("_towupper_l", { return __crt_towupper_l(ch, locale); })]]
[[if($extended_include_prefix("<bits/crt/wctype.h>")defined(__crt_towupper_l)), preferred_extern_inline("__towupper_l", { return __crt_towupper_l(ch, locale); })]]
[[if($extended_include_prefix("<bits/crt/wctype.h>")defined(__crt_towupper_l)), preferred_inline({ return __crt_towupper_l(ch, locale); })]]
[[dos_export_alias("_towupper_l"), export_alias("__towupper_l")]]
[[if($extended_include_prefix("<bits/crt/wctype.h>")defined(__crt_towupper)), inline({ COMPILER_IMPURE(); (void)locale; return __crt_towupper(ch); })]]
[[if(defined(__LIBKCALL_CALLER_CLEANUP)), crt_intern_kos_alias("libc_towupper")]]
[[if(defined(__LIBDCALL_CALLER_CLEANUP)), crt_intern_dos_alias("libd_towupper")]]
$wint_t towupper_l($wint_t ch, $locale_t locale) {
	COMPILER_IMPURE();
	(void)locale;
	return towupper(ch);
}
/*[[[end]]]*/


[[dos_only_export_alias("_iswctype_l"), export_alias("__iswctype_l")]]
[[wchar, pure, wunused, decl_include("<hybrid/typecore.h>", "<bits/crt/wctype.h>")]]
[[requires_function(iswctype)]]
[[if(defined(__LIBKCALL_CALLER_CLEANUP)), crt_intern_kos_alias("libc_iswctype")]]
[[if(defined(__LIBDCALL_CALLER_CLEANUP)), crt_intern_dos_alias("libd_iswctype")]]
int iswctype_l($wint_t wc, $wctype_t type, $locale_t locale) {
	COMPILER_IMPURE();
	(void)locale;
	return iswctype(wc, type);
}

[[decl_include("<bits/crt/wctype.h>")]]
[[wunused, export_alias("__wctype_l")]]
[[requires_function(wctype)]]
[[if(defined(__LIBKCALL_CALLER_CLEANUP)), crt_intern_kos_alias("libc_wctype")]]
[[if(defined(__LIBDCALL_CALLER_CLEANUP)), crt_intern_dos_alias("libd_wctype")]]
$wctype_t wctype_l([[in]] char const *prop, $locale_t locale) {
	COMPILER_IMPURE();
	(void)locale;
	return wctype(prop);
}

[[decl_include("<hybrid/typecore.h>", "<bits/crt/wctype.h>")]]
[[wchar, wunused, export_alias("__towctrans_l")]]
[[requires_function(towctrans)]]
[[if(defined(__LIBKCALL_CALLER_CLEANUP)), crt_intern_kos_alias("libc_towctrans")]]
[[if(defined(__LIBDCALL_CALLER_CLEANUP)), crt_intern_dos_alias("libd_towctrans")]]
$wint_t towctrans_l($wint_t wc, $wctrans_t desc, $locale_t locale) {
	COMPILER_IMPURE();
	(void)locale;
	return towctrans(wc, desc);
}

[[decl_include("<bits/crt/wctype.h>")]]
[[wunused, export_alias("__wctrans_l")]]
[[requires_function(wctrans)]]
[[if(defined(__LIBKCALL_CALLER_CLEANUP)), crt_intern_kos_alias("libc_wctrans")]]
[[if(defined(__LIBDCALL_CALLER_CLEANUP)), crt_intern_dos_alias("libd_wctrans")]]
$wctrans_t wctrans_l([[in]] char const *prop, $locale_t locale) {
	COMPILER_IMPURE();
	(void)locale;
	return wctrans(prop);
}

%#endif /* __USE_XOPEN2K8 */



%#ifdef __USE_KOS
%[default:section(".text.crt.dos.wchar.unicode.static.mbs")]

@@>> iswsymstrt(3), iswsymstrt_l(3)
@@Check if `wc' may appear at the start of a symbol/keyword/identifier
[[wchar, const, wunused, decl_include("<hybrid/typecore.h>")]]
[[impl_include("<bits/crt/unicode.h>"), crt_name("__iswcsymf")]]
int iswsymstrt($wint_t wc) {
@@pp_if defined(__CRT_KOS) && $has_function(__unicode_descriptor)@@
	struct @__unitraits@ const *traits = __unicode_descriptor(wc);
	return (int)(traits->@__ut_flags@ & __UNICODE_ISSYMSTRT);
@@pp_else@@
	return iswalpha(wc) || wc == '_' || wc == '$';
@@pp_endif@@
}

@@>> iswsymcont(3), iswsymcont_l(3)
@@Check if `wc' may appear in the middle of a symbol/keyword/identifier
[[wchar, const, wunused, decl_include("<hybrid/typecore.h>")]]
[[impl_include("<bits/crt/unicode.h>"), crt_name("__iswcsym")]]
int iswsymcont($wint_t wc) {
@@pp_if defined(__CRT_KOS) && $has_function(__unicode_descriptor)@@
	struct @__unitraits@ const *traits = __unicode_descriptor(wc);
	return (int)(traits->@__ut_flags@ & __UNICODE_ISSYMCONT);
@@pp_else@@
	return iswalnum(wc) || wc == '_' || wc == '$';
@@pp_endif@@
}

%[default:section(".text.crt.dos.wchar.unicode.locale.mbs")]

[[wchar, pure, wunused, decl_include("<hybrid/typecore.h>")]]
[[crt_name("_iswcsymf_l"), doc_alias("iswsymstrt")]]
[[if(defined(__LIBKCALL_CALLER_CLEANUP)), crt_intern_kos_alias("libc___iswcsymf")]]
[[if(defined(__LIBDCALL_CALLER_CLEANUP)), crt_intern_dos_alias("libd___iswcsymf")]]
int iswsymstrt_l($wint_t wc, $locale_t locale) {
@@pp_if defined(__CRT_KOS) && $has_function(__unicode_descriptor)@@
	COMPILER_IMPURE();
	(void)locale;
	return iswsymstrt(wc);
@@pp_else@@
	return iswalpha_l(wc, locale) || wc == '_' || wc == '$';
@@pp_endif@@
}

[[wchar, pure, wunused, decl_include("<hybrid/typecore.h>")]]
[[crt_name("_iswcsym_l"), doc_alias("iswsymcont")]]
[[if(defined(__LIBKCALL_CALLER_CLEANUP)), crt_intern_kos_alias("libc___iswcsym")]]
[[if(defined(__LIBDCALL_CALLER_CLEANUP)), crt_intern_dos_alias("libd___iswcsym")]]
int iswsymcont_l($wint_t wc, $locale_t locale) {
@@pp_if defined(__CRT_KOS) && $has_function(__unicode_descriptor)@@
	COMPILER_IMPURE();
	(void)locale;
	return iswsymcont(wc);
@@pp_else@@
	return iswalnum_l(wc, locale) || wc == '_' || wc == '$';
@@pp_endif@@
}

%#endif /* __USE_KOS */



%[default:section(".text.crt.dos.wchar.unicode.locale.mbs")]

%
%#ifdef __USE_DOS
%#ifndef __wctype_t_defined
%#define __wctype_t_defined
%__NAMESPACE_STD_USING(wctype_t)
%#endif /* !__wctype_t_defined */
%#ifndef _WCTYPE_DEFINED
%#define _WCTYPE_DEFINED 1

%[insert:function(_iswalnum_l = iswalnum_l)]
%[insert:function(_iswalpha_l = iswalpha_l)]
%[insert:function(_iswcntrl_l = iswcntrl_l)]
%[insert:function(_iswdigit_l = iswdigit_l)]
%[insert:function(_iswgraph_l = iswgraph_l)]
%[insert:function(_iswlower_l = iswlower_l)]
%[insert:function(_iswprint_l = iswprint_l)]
%[insert:function(_iswpunct_l = iswpunct_l)]
%[insert:function(_iswspace_l = iswspace_l)]
%[insert:function(_iswupper_l = iswupper_l)]
%[insert:function(_iswxdigit_l = iswxdigit_l)]
%[insert:function(_iswblank_l = iswblank_l)]
%[insert:function(_towupper_l = towupper_l)]
%[insert:function(_towlower_l = towlower_l)]
%[insert:function(_iswctype_l = iswctype_l)]
%[insert:function(is_wctype = iswctype)]

%
@@>> isleadbyte(3)
[[const, wunused]]
[[section(".text.crt{|.dos}.wchar.unicode.static.mbs")]]
int isleadbyte(int wc) {
	return wc >= 192 && wc <= 255;
}

[[pure, wunused]]
[[section(".text.crt{|.dos}.wchar.unicode.locale.mbs")]]
[[if(defined(__LIBKCALL_CALLER_CLEANUP)), crt_intern_kos_alias("libc_isleadbyte")]]
[[if(defined(__LIBDCALL_CALLER_CLEANUP)), crt_intern_dos_alias("libd_isleadbyte")]]
int _isleadbyte_l(int wc, $locale_t locale) {
	COMPILER_IMPURE();
	(void)locale;
	return isleadbyte(wc);
}

%[insert:function(__iswcsymf = iswsymstrt)]
%[insert:function(__iswcsym = iswsymcont)]
%[insert:function(_iswcsymf_l = iswsymstrt_l)]
%[insert:function(_iswcsym_l = iswsymcont_l)]
%#endif /* !_WCTYPE_DEFINED */
%#endif /* __USE_DOS */



%{

__SYSDECL_END
#endif /* __CC__ */

#ifdef __USE_UTF
#if defined(_UCHAR_H) && !defined(_PARTS_UCHAR_WCTYPE_H)
#include <parts/uchar/wctype.h>
#endif /* _UCHAR_H && !_PARTS_UCHAR_WCTYPE_H */
#endif /* __USE_UTF */

}
