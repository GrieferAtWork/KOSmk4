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

%[define_ccompat_header("cctype")]
%[define_replacement(locale_t = __locale_t)]

%[define_str2wcs_replacement(tolower  = "(wchar_t)towlower")]
%[define_str2wcs_replacement(toupper  = "(wchar_t)towupper")]
%[define_str2wcs_replacement(isalnum  = iswalnum)]
%[define_str2wcs_replacement(isalpha  = iswalpha)]
%[define_str2wcs_replacement(isupper  = iswupper)]
%[define_str2wcs_replacement(islower  = iswlower)]
%[define_str2wcs_replacement(isdigit  = iswdigit)]
%[define_str2wcs_replacement(isxdigit = iswxdigit)]
%[define_str2wcs_replacement(isspace  = iswspace)]
%[define_str2wcs_replacement(ispunct  = iswpunct)]
%[define_str2wcs_replacement(isprint  = iswprint)]
%[define_str2wcs_replacement(isgraph  = iswgraph)]
%[define_str2wcs_replacement(iscntrl  = iswcntrl)]
%[define_str2wcs_replacement(isblank  = iswblank)]


%{
#include <features.h>

#ifdef __USE_XOPEN2K8
#include <xlocale.h>
#endif /* __USE_XOPEN2K8 */

#ifdef __USE_GLIBC
#include <endian.h>
#endif /* __USE_GLIBC */

#ifdef __CC__
__SYSDECL_BEGIN

}

%[default:section(".text.crt{|.dos}.unicode.static.ctype")];

[[ignore, ATTR_CONST, wunused, nothrow]]
char const *__locale_ctype_ptr();

[[ignore, wunused, ATTR_PURE]]
[[section(".text.crt{|.dos}.unicode.locale.ctype")]]
char const *__locale_ctype_ptr_l($locale_t locale);

[[ignore, wunused, ATTR_PURE, nothrow]]
[[decl_include("<hybrid/typecore.h>")]]
$uint16_t const **__ctype_b_loc();

[[ignore, wunused, ATTR_PURE, nothrow]]
[[decl_include("<hybrid/typecore.h>")]]
$int32_t const **__ctype_tolower_loc();

[[ignore, wunused, ATTR_PURE, nothrow]]
[[decl_include("<hybrid/typecore.h>")]]
$int32_t const **__ctype_toupper_loc();

[[ignore, ATTR_CONST, wunused, nothrow]]
int _isctype(int ch, int mask);

[[ignore, wunused, ATTR_PURE]]
[[section(".text.crt{|.dos}.unicode.locale.ctype")]]
int _isctype_l(int ch, int mask, $locale_t locale);


%[insert:std]


[[std, crtbuiltin, kernel]]
[[ATTR_CONST, wunused, libc, nothrow]]
int iscntrl(int ch) {
@@pp_ifdef __BUILDING_LIBC@@
	return (u8)ch <= 0x1f || (u8)ch == 0x7f;
@@pp_else@@
@@pp_if defined(__CRT_HAVE___ctype_b_loc) && defined(__CRT_GLC)@@
#include <hybrid/byteorder.h>
@@pp_if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__@@
	return (*__ctype_b_loc())[ch] & (1 << 9);
@@pp_else@@
	return (*__ctype_b_loc())[ch] & (1 << 1);
@@pp_endif@@
@@pp_elif defined(__CRT_HAVE___locale_ctype_ptr) && defined(__CRT_CYG)@@
	return ((__locale_ctype_ptr() + 1)[ch & 0xff] & 040) != 0;
@@pp_elif defined(__CRT_HAVE__isctype) && defined(__CRT_DOS)@@
	return _isctype(ch, 0x0020);
@@pp_else@@
	return (u8)ch <= 0x1f || (u8)ch == 0x7f;
@@pp_endif@@
@@pp_endif@@
}


[[ATTR_CONST, wunused, libc, nothrow]]
[[std, crtbuiltin, kernel]]
int isspace(int ch) {
@@pp_ifdef __BUILDING_LIBC@@
	return ((u8)ch >= 0x09 && (u8)ch <= 0x0d) || (u8)ch == 0x20;
@@pp_else@@
@@pp_if defined(__CRT_HAVE___ctype_b_loc) && defined(__CRT_GLC)@@
#include <hybrid/byteorder.h>
@@pp_if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__@@
	return (*__ctype_b_loc())[ch] & (1 << 5);
@@pp_else@@
	return (*__ctype_b_loc())[ch] & (1 << 13);
@@pp_endif@@
@@pp_elif defined(__CRT_HAVE___locale_ctype_ptr) && defined(__CRT_CYG)@@
	return ((__locale_ctype_ptr() + 1)[ch & 0xff] & 010) != 0;
@@pp_elif defined(__CRT_HAVE__isctype) && defined(__CRT_DOS)@@
	return _isctype(ch, 0x0008);
@@pp_else@@
	return ((u8)ch >= 0x09 && (u8)ch <= 0x0d) || (u8)ch == 0x20;
@@pp_endif@@
@@pp_endif@@
}

[[ATTR_CONST, wunused, libc, nothrow]]
[[std, crtbuiltin, kernel]] 
int isupper(int ch) {
@@pp_ifdef __BUILDING_LIBC@@
	return (u8)ch >= 0x41 && (u8)ch <= 0x5a;
@@pp_else@@
@@pp_if defined(__CRT_HAVE___ctype_b_loc) && defined(__CRT_GLC)@@
#include <hybrid/byteorder.h>
@@pp_if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__@@
	return (*__ctype_b_loc())[ch] & (1 << 0);
@@pp_else@@
	return (*__ctype_b_loc())[ch] & (1 << 8);
@@pp_endif@@
@@pp_elif defined(__CRT_HAVE___locale_ctype_ptr) && defined(__CRT_CYG)@@
	return ((__locale_ctype_ptr() + 1)[ch & 0xff] & 3) == 1;
@@pp_elif defined(__CRT_HAVE__isctype) && defined(__CRT_DOS)@@
	return _isctype(ch, 0x0001);
@@pp_else@@
	return (u8)ch >= 0x41 && (u8)ch <= 0x5a;
@@pp_endif@@
@@pp_endif@@
}


[[ATTR_CONST, wunused, libc, nothrow]]
[[std, crtbuiltin, kernel]] 
int islower(int ch) {
@@pp_ifdef __BUILDING_LIBC@@
	return (u8)ch >= 0x61 && (u8)ch <= 0x7a;
@@pp_else@@
@@pp_if defined(__CRT_HAVE___ctype_b_loc) && defined(__CRT_GLC)@@
#include <hybrid/byteorder.h>
@@pp_if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__@@
	return (*__ctype_b_loc())[ch] & (1 << 1);
@@pp_else@@
	return (*__ctype_b_loc())[ch] & (1 << 9);
@@pp_endif@@
@@pp_elif defined(__CRT_HAVE___locale_ctype_ptr) && defined(__CRT_CYG)@@
	return ((__locale_ctype_ptr() + 1)[ch & 0xff] & 3) == 2;
@@pp_elif defined(__CRT_HAVE__isctype) && defined(__CRT_DOS)@@
	return _isctype(ch, 0x0002);
@@pp_else@@
	return (u8)ch >= 0x61 && (u8)ch <= 0x7a;
@@pp_endif@@
@@pp_endif@@
}

[[ATTR_CONST, wunused, libc, nothrow]]
[[std, crtbuiltin, kernel]] 
int isalpha(int ch) {
@@pp_ifdef __BUILDING_LIBC@@
	return libc_isupper(ch) || libc_islower(ch);
@@pp_else@@
@@pp_if defined(__CRT_HAVE___ctype_b_loc) && defined(__CRT_GLC)@@
#include <hybrid/byteorder.h>
@@pp_if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__@@
	return (*__ctype_b_loc())[ch] & (1 << 2);
@@pp_else@@
	return (*__ctype_b_loc())[ch] & (1 << 10);
@@pp_endif@@
@@pp_elif defined(__CRT_HAVE___locale_ctype_ptr) && defined(__CRT_CYG)@@
	return ((__locale_ctype_ptr() + 1)[ch & 0xff] & 3) != 0;
@@pp_elif defined(__CRT_HAVE__isctype) && defined(__CRT_DOS)@@
	return _isctype(ch, 0x0103);
@@pp_else@@
	return isupper(ch) || islower(ch);
@@pp_endif@@
@@pp_endif@@
}

[[ATTR_CONST, wunused, libc, nothrow]]
[[std, crtbuiltin, kernel]] 
int isdigit(int ch) {
@@pp_ifdef __BUILDING_LIBC@@
	return (u8)ch >= 0x30 && (u8)ch <= 0x39;
@@pp_else@@
@@pp_if defined(__CRT_HAVE___ctype_b_loc) && defined(__CRT_GLC)@@
#include <hybrid/byteorder.h>
@@pp_if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__@@
	return (*__ctype_b_loc())[ch] & (1 << 3);
@@pp_else@@
	return (*__ctype_b_loc())[ch] & (1 << 11);
@@pp_endif@@
@@pp_elif defined(__CRT_HAVE___locale_ctype_ptr) && defined(__CRT_CYG)@@
	return ((__locale_ctype_ptr() + 1)[ch & 0xff] & 4) != 0;
@@pp_elif defined(__CRT_HAVE__isctype) && defined(__CRT_DOS)@@
	return _isctype(ch, 0x0004);
@@pp_else@@
	return (u8)ch >= 0x30 && (u8)ch <= 0x39;
@@pp_endif@@
@@pp_endif@@
}

[[ATTR_CONST, wunused, libc, nothrow]]
[[std, crtbuiltin, kernel]] 
int isxdigit(int ch) {
@@pp_ifdef __BUILDING_LIBC@@
	return isdigit(ch) ||
	       ((u8)ch >= 0x41 && (u8)ch <= 0x46) ||
	       ((u8)ch >= 0x61 && (u8)ch <= 0x66);
@@pp_else@@
@@pp_if defined(__CRT_HAVE___ctype_b_loc) && defined(__CRT_GLC)@@
#include <hybrid/byteorder.h>
@@pp_if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__@@
	return (*__ctype_b_loc())[ch] & (1 << 4);
@@pp_else@@
	return (*__ctype_b_loc())[ch] & (1 << 12);
@@pp_endif@@
@@pp_elif defined(__CRT_HAVE___locale_ctype_ptr) && defined(__CRT_CYG)@@
	return ((__locale_ctype_ptr() + 1)[ch & 0xff] & 0104) != 0;
@@pp_elif defined(__CRT_HAVE__isctype) && defined(__CRT_DOS)@@
	return _isctype(ch, 0x0080);
@@pp_else@@
	return isdigit(ch) ||
	       ((u8)ch >= 0x41 && (u8)ch <= 0x46) ||
	       ((u8)ch >= 0x61 && (u8)ch <= 0x66);
@@pp_endif@@
@@pp_endif@@
}

[[ATTR_CONST, wunused, libc, nothrow]]
[[std, crtbuiltin, kernel]] 
int isalnum(int ch) {
@@pp_ifdef __BUILDING_LIBC@@
	return isupper(ch) || islower(ch) || isdigit(ch);
@@pp_else@@
@@pp_if defined(__CRT_HAVE___ctype_b_loc) && defined(__CRT_GLC)@@
#include <hybrid/byteorder.h>
@@pp_if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__@@
	return (*__ctype_b_loc())[ch] & (1 << 11);
@@pp_else@@
	return (*__ctype_b_loc())[ch] & (1 << 3);
@@pp_endif@@
@@pp_elif defined(__CRT_HAVE___locale_ctype_ptr) && defined(__CRT_CYG)@@
	return ((__locale_ctype_ptr() + 1)[ch & 0xff] & 7) != 0;
@@pp_elif defined(__CRT_HAVE__isctype) && defined(__CRT_DOS)@@
	return _isctype(ch, 0x0107);
@@pp_else@@
	return isupper(ch) || islower(ch) || isdigit(ch);
@@pp_endif@@
@@pp_endif@@
}

[[ATTR_CONST, wunused, libc, nothrow]]
[[std, crtbuiltin, kernel]] 
int ispunct(int ch)  {
@@pp_ifdef __BUILDING_LIBC@@
	return ((u8)ch >= 0x21 && (u8)ch <= 0x2f) ||
	       ((u8)ch >= 0x3a && (u8)ch <= 0x40) ||
	       ((u8)ch >= 0x5b && (u8)ch <= 0x60) ||
	       ((u8)ch >= 0x7b && (u8)ch <= 0x7e);
@@pp_else@@
@@pp_if defined(__CRT_HAVE___ctype_b_loc) && defined(__CRT_GLC)@@
#include <hybrid/byteorder.h>
@@pp_if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__@@
	return (*__ctype_b_loc())[ch] & (1 << 10);
@@pp_else@@
	return (*__ctype_b_loc())[ch] & (1 << 2);
@@pp_endif@@
@@pp_elif defined(__CRT_HAVE___locale_ctype_ptr) && defined(__CRT_CYG)@@
	return ((__locale_ctype_ptr() + 1)[ch & 0xff] & 020) != 0;
@@pp_elif defined(__CRT_HAVE__isctype) && defined(__CRT_DOS)@@
	return _isctype(ch, 0x0010);
@@pp_else@@
	return ((u8)ch >= 0x21 && (u8)ch <= 0x2f) ||
	       ((u8)ch >= 0x3a && (u8)ch <= 0x40) ||
	       ((u8)ch >= 0x5b && (u8)ch <= 0x60) ||
	       ((u8)ch >= 0x7b && (u8)ch <= 0x7e);
@@pp_endif@@
@@pp_endif@@
}

[[ATTR_CONST, wunused, libc, nothrow]]
[[std, crtbuiltin, kernel]] 
int isgraph(int ch) {
@@pp_ifdef __BUILDING_LIBC@@
	return (u8)ch >= 0x21 && (u8)ch <= 0x7e;
@@pp_else@@
@@pp_if defined(__CRT_HAVE___ctype_b_loc) && defined(__CRT_GLC)@@
#include <hybrid/byteorder.h>
@@pp_if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__@@
	return (*__ctype_b_loc())[ch] & (1 << 7);
@@pp_else@@
	return (*__ctype_b_loc())[ch] & (1 << 15);
@@pp_endif@@
@@pp_elif defined(__CRT_HAVE___locale_ctype_ptr) && defined(__CRT_CYG)@@
	return ((__locale_ctype_ptr() + 1)[ch & 0xff] & 027) != 0;
@@pp_elif defined(__CRT_HAVE__isctype) && defined(__CRT_DOS)@@
	return _isctype(ch, 0x0117);
@@pp_else@@
	return (u8)ch >= 0x21 && (u8)ch <= 0x7e;
@@pp_endif@@
@@pp_endif@@
}

[[ATTR_CONST, wunused, libc, nothrow]]
[[std, crtbuiltin, kernel]] 
int isprint(int ch) {
@@pp_ifdef __BUILDING_LIBC@@
	return (u8)ch >= 0x20 && (u8)ch <= 0x7e;
@@pp_else@@
@@pp_if defined(__CRT_HAVE___ctype_b_loc) && defined(__CRT_GLC)@@
#include <hybrid/byteorder.h>
@@pp_if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__@@
	return (*__ctype_b_loc())[ch] & (1 << 6);
@@pp_else@@
	return (*__ctype_b_loc())[ch] & (1 << 14);
@@pp_endif@@
@@pp_elif defined(__CRT_HAVE___locale_ctype_ptr) && defined(__CRT_CYG)@@
	return ((__locale_ctype_ptr() + 1)[ch & 0xff] & 0227) != 0;
@@pp_elif defined(__CRT_HAVE__isctype) && defined(__CRT_DOS)@@
	return _isctype(ch, 0x0157);
@@pp_else@@
	return (u8)ch >= 0x20 && (u8)ch <= 0x7e;
@@pp_endif@@
@@pp_endif@@
}

[[ATTR_CONST, wunused, nothrow, crtbuiltin]]
[[libc, std, kernel, alias("_tolower")]]
[[if(!defined(__KERNEL__)), export_as("_tolower")]]
int tolower(int ch) {
@@pp_ifdef __BUILDING_LIBC@@
	return isupper(ch) ? ((u8)ch+0x20) : ch;
@@pp_else@@
@@pp_if $has_function(__ctype_tolower_loc) && defined(__CRT_CYG)@@
	return ch >= -128 && ch < 256 ? (*__ctype_tolower_loc())[ch] : ch;
@@pp_else@@
	return isupper(ch) ? ((u8)ch+0x20) : ch;
@@pp_endif@@
@@pp_endif@@
}

[[ATTR_CONST, wunused, nothrow, crtbuiltin]]
[[libc, std, kernel, alias("_toupper")]]
[[if(!defined(__KERNEL__)), export_as("_toupper")]]
int toupper(int ch) {
@@pp_ifdef __BUILDING_LIBC@@
	return islower(ch) ? ((u8)ch-0x20) : ch;
@@pp_else@@
@@pp_if $has_function(__ctype_toupper_loc) && defined(__CRT_CYG)@@
	return ch >= -128 && ch < 256 ? (*__ctype_toupper_loc())[ch] : ch;
@@pp_else@@
	return islower(ch) ? ((u8)ch-0x20) : ch;
@@pp_endif@@
@@pp_endif@@
}


%#ifdef __USE_ISOC99
[[ATTR_CONST, wunused, nothrow]]
[[crtbuiltin, libc, std, kernel]]
int isblank(int ch) {
@@pp_ifdef __BUILDING_LIBC@@
	return (u8)ch == 0x09 || (u8)ch == 0x20;
@@pp_else@@
@@pp_if defined(__CRT_HAVE___ctype_b_loc) && defined(__CRT_GLC)@@
#include <hybrid/byteorder.h>
@@pp_if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__@@
	return (*__ctype_b_loc())[ch] & (1 << 8);
@@pp_else@@
	return (*__ctype_b_loc())[ch] & (1 << 0);
@@pp_endif@@
@@pp_elif defined(__CRT_HAVE___locale_ctype_ptr) && defined(__CRT_CYG)@@
	return ((__locale_ctype_ptr() + 1)[ch & 0xff] & 0200) != 0 || ch == '\t';
@@pp_else@@
	return (u8)ch == 0x09 || (u8)ch == 0x20;
@@pp_endif@@
@@pp_endif@@
}
%{
#endif /* __USE_ISOC99 */

#ifdef __USE_XOPEN2K8
}

%[default:section(".text.crt{|.dos}.unicode.locale.ctype")]

[[wunused, ATTR_PURE, export_alias("__iscntrl_l")]]
int iscntrl_l(int ch, __locale_t locale) {
@@pp_ifdef __BUILDING_LIBC@@
	(void)locale;
	COMPILER_IMPURE();
	return iscntrl(ch);
@@pp_else@@
@@pp_if defined(__CRT_HAVE___ctype_b_loc) && defined(__CRT_GLC)@@
#include <hybrid/byteorder.h>
@@pp_if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__@@
	return locale->__ctype_b[ch] & (1 << 9);
@@pp_else@@
	return locale->__ctype_b[ch] & (1 << 1);
@@pp_endif@@
@@pp_elif defined(@__CRT_HAVE___locale_ctype_ptr_l@) && defined(__CRT_CYG)@@
	return ((__locale_ctype_ptr_l(locale) + 1)[ch & 0xff] & 040) != 0;
@@pp_elif defined(@__CRT_HAVE__isctype_l@) && defined(__CRT_DOS)@@
	return _isctype_l(ch, 0x0020, locale);
@@pp_else@@
	(void)locale;
	COMPILER_IMPURE();
	return iscntrl(ch);
@@pp_endif@@
@@pp_endif@@
}


[[wunused, ATTR_PURE, export_alias("__isspace_l")]]
int isspace_l(int ch, __locale_t locale) {
@@pp_ifdef __BUILDING_LIBC@@
	(void)locale;
	COMPILER_IMPURE();
	return isspace(ch);
@@pp_else@@
@@pp_if defined(__CRT_HAVE___ctype_b_loc) && defined(__CRT_GLC)@@
#include <hybrid/byteorder.h>
@@pp_if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__@@
	return locale->__ctype_b[ch] & (1 << 5);
@@pp_else@@
	return locale->__ctype_b[ch] & (1 << 13);
@@pp_endif@@
@@pp_elif defined(@__CRT_HAVE___locale_ctype_ptr_l@) && defined(__CRT_CYG)@@
	return ((__locale_ctype_ptr_l(locale) + 1)[ch & 0xff] & 010) != 0;
@@pp_elif defined(@__CRT_HAVE__isctype_l@) && defined(__CRT_DOS)@@
	return _isctype_l(ch, 0x0008, locale);
@@pp_else@@
	(void)locale;
	COMPILER_IMPURE();
	return isspace(ch);
@@pp_endif@@
@@pp_endif@@
}

[[wunused, ATTR_PURE, export_alias("__isupper_l")]]
int isupper_l(int ch, __locale_t locale) {
@@pp_ifdef __BUILDING_LIBC@@
	(void)locale;
	COMPILER_IMPURE();
	return isupper(ch);
@@pp_else@@
@@pp_if defined(__CRT_HAVE___ctype_b_loc) && defined(__CRT_GLC)@@
#include <hybrid/byteorder.h>
@@pp_if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__@@
	return locale->__ctype_b[ch] & (1 << 0);
@@pp_else@@
	return locale->__ctype_b[ch] & (1 << 8);
@@pp_endif@@
@@pp_elif defined(@__CRT_HAVE___locale_ctype_ptr_l@) && defined(__CRT_CYG)@@
	return ((__locale_ctype_ptr_l(locale) + 1)[ch & 0xff] & 3) == 1;
@@pp_elif defined(@__CRT_HAVE__isctype_l@) && defined(__CRT_DOS)@@
	return _isctype_l(ch, 0x0001, locale);
@@pp_else@@
	(void)locale;
	COMPILER_IMPURE();
	return isupper(ch);
@@pp_endif@@
@@pp_endif@@
}

[[wunused, ATTR_PURE, export_alias("__islower_l")]]
int islower_l(int ch, __locale_t locale) {
@@pp_ifdef __BUILDING_LIBC@@
	(void)locale;
	COMPILER_IMPURE();
	return islower(ch);
@@pp_else@@
@@pp_if defined(__CRT_HAVE___ctype_b_loc) && defined(__CRT_GLC)@@
#include <hybrid/byteorder.h>
@@pp_if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__@@
	return locale->__ctype_b[ch] & (1 << 1);
@@pp_else@@
	return locale->__ctype_b[ch] & (1 << 9);
@@pp_endif@@
@@pp_elif defined(@__CRT_HAVE___locale_ctype_ptr_l@) && defined(__CRT_CYG)@@
	return ((__locale_ctype_ptr_l(locale) + 1)[ch & 0xff] & 3) == 2;
@@pp_elif defined(@__CRT_HAVE__isctype_l@) && defined(__CRT_DOS)@@
	return _isctype_l(ch, 0x0002, locale);
@@pp_else@@
	(void)locale;
	COMPILER_IMPURE();
	return islower(ch);
@@pp_endif@@
@@pp_endif@@
}

[[wunused, ATTR_PURE, export_alias("__isalpha_l")]]
int isalpha_l(int ch, __locale_t locale) {
@@pp_ifdef __BUILDING_LIBC@@
	(void)locale;
	COMPILER_IMPURE();
	return isalpha(ch);
@@pp_else@@
@@pp_if defined(__CRT_HAVE___ctype_b_loc) && defined(__CRT_GLC)@@
#include <hybrid/byteorder.h>
@@pp_if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__@@
	return locale->__ctype_b[ch] & (1 << 2);
@@pp_else@@
	return locale->__ctype_b[ch] & (1 << 10);
@@pp_endif@@
@@pp_elif defined(@__CRT_HAVE___locale_ctype_ptr_l@) && defined(__CRT_CYG)@@
	return ((__locale_ctype_ptr_l(locale) + 1)[ch & 0xff] & 3) != 0;
@@pp_elif defined(@__CRT_HAVE__isctype_l@) && defined(__CRT_DOS)@@
	return _isctype_l(ch, 0x0103, locale);
@@pp_else@@
	(void)locale;
	COMPILER_IMPURE();
	return isalpha(ch);
@@pp_endif@@
@@pp_endif@@
}

[[wunused, ATTR_PURE, export_alias("__isdigit_l")]]
int isdigit_l(int ch, __locale_t locale) {
@@pp_ifdef __BUILDING_LIBC@@
	(void)locale;
	COMPILER_IMPURE();
	return isdigit(ch);
@@pp_else@@
@@pp_if defined(__CRT_HAVE___ctype_b_loc) && defined(__CRT_GLC)@@
#include <hybrid/byteorder.h>
@@pp_if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__@@
	return locale->__ctype_b[ch] & (1 << 3);
@@pp_else@@
	return locale->__ctype_b[ch] & (1 << 11);
@@pp_endif@@
@@pp_elif defined(@__CRT_HAVE___locale_ctype_ptr_l@) && defined(__CRT_CYG)@@
	return ((__locale_ctype_ptr_l(locale) + 1)[ch & 0xff] & 4) != 0;
@@pp_elif defined(@__CRT_HAVE__isctype_l@) && defined(__CRT_DOS)@@
	return _isctype_l(ch, 0x0004, locale);
@@pp_else@@
	(void)locale;
	COMPILER_IMPURE();
	return isdigit(ch);
@@pp_endif@@
@@pp_endif@@
}

[[wunused, ATTR_PURE, export_alias("__isxdigit_l")]]
int isxdigit_l(int ch, __locale_t locale) {
@@pp_ifdef __BUILDING_LIBC@@
	(void)locale;
	COMPILER_IMPURE();
	return isxdigit(ch);
@@pp_else@@
@@pp_if defined(__CRT_HAVE___ctype_b_loc) && defined(__CRT_GLC)@@
#include <hybrid/byteorder.h>
@@pp_if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__@@
	return locale->__ctype_b[ch] & (1 << 4);
@@pp_else@@
	return locale->__ctype_b[ch] & (1 << 12);
@@pp_endif@@
@@pp_elif defined(@__CRT_HAVE___locale_ctype_ptr_l@) && defined(__CRT_CYG)@@
	return ((__locale_ctype_ptr_l(locale) + 1)[ch & 0xff] & 0104) != 0;
@@pp_elif defined(@__CRT_HAVE__isctype_l@) && defined(__CRT_DOS)@@
	return _isctype_l(ch, 0x0080, locale);
@@pp_else@@
	(void)locale;
	COMPILER_IMPURE();
	return isxdigit(ch);
@@pp_endif@@
@@pp_endif@@
}

[[wunused, ATTR_PURE, export_alias("__isalnum_l")]]
int isalnum_l(int ch, __locale_t locale) {
@@pp_ifdef __BUILDING_LIBC@@
	(void)locale;
	COMPILER_IMPURE();
	return isalnum(ch);
@@pp_else@@
@@pp_if defined(__CRT_HAVE___ctype_b_loc) && defined(__CRT_GLC)@@
#include <hybrid/byteorder.h>
@@pp_if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__@@
	return locale->__ctype_b[ch] & (1 << 11);
@@pp_else@@
	return locale->__ctype_b[ch] & (1 << 3);
@@pp_endif@@
@@pp_elif defined(@__CRT_HAVE___locale_ctype_ptr_l@) && defined(__CRT_CYG)@@
	return ((__locale_ctype_ptr_l(locale) + 1)[ch & 0xff] & 7) != 0;
@@pp_elif defined(@__CRT_HAVE__isctype_l@) && defined(__CRT_DOS)@@
	return _isctype_l(ch, 0x0107, locale);
@@pp_else@@
	(void)locale;
	COMPILER_IMPURE();
	return isalnum(ch);
@@pp_endif@@
@@pp_endif@@
}

[[wunused, ATTR_PURE, export_alias("__ispunct_l")]]
int ispunct_l(int ch, __locale_t locale) {
@@pp_ifdef __BUILDING_LIBC@@
	(void)locale;
	COMPILER_IMPURE();
	return ispunct(ch);
@@pp_else@@
@@pp_if defined(__CRT_HAVE___ctype_b_loc) && defined(__CRT_GLC)@@
#include <hybrid/byteorder.h>
@@pp_if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__@@
	return locale->__ctype_b[ch] & (1 << 10);
@@pp_else@@
	return locale->__ctype_b[ch] & (1 << 2);
@@pp_endif@@
@@pp_elif defined(@__CRT_HAVE___locale_ctype_ptr_l@) && defined(__CRT_CYG)@@
	return ((__locale_ctype_ptr_l(locale) + 1)[ch & 0xff] & 020) != 0;
@@pp_elif defined(@__CRT_HAVE__isctype_l@) && defined(__CRT_DOS)@@
	return _isctype_l(ch, 0x0010, locale);
@@pp_else@@
	(void)locale;
	COMPILER_IMPURE();
	return ispunct(ch);
@@pp_endif@@
@@pp_endif@@
}

[[wunused, ATTR_PURE, export_alias("__isgraph_l")]]
int isgraph_l(int ch, __locale_t locale) {
@@pp_ifdef __BUILDING_LIBC@@
	(void)locale;
	COMPILER_IMPURE();
	return isgraph(ch);
@@pp_else@@
@@pp_if defined(__CRT_HAVE___ctype_b_loc) && defined(__CRT_GLC)@@
#include <hybrid/byteorder.h>
@@pp_if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__@@
	return locale->__ctype_b[ch] & (1 << 7);
@@pp_else@@
	return locale->__ctype_b[ch] & (1 << 15);
@@pp_endif@@
@@pp_elif defined(@__CRT_HAVE___locale_ctype_ptr_l@) && defined(__CRT_CYG)@@
	return ((__locale_ctype_ptr_l(locale) + 1)[ch & 0xff] & 027) != 0;
@@pp_elif defined(@__CRT_HAVE__isctype_l@) && defined(__CRT_DOS)@@
	return _isctype_l(ch, 0x0117, locale);
@@pp_else@@
	(void)locale;
	COMPILER_IMPURE();
	return isgraph(ch);
@@pp_endif@@
@@pp_endif@@
}

[[wunused, ATTR_PURE, export_alias("__isprint_l")]]
int isprint_l(int ch, __locale_t locale) {
@@pp_ifdef __BUILDING_LIBC@@
	(void)locale;
	COMPILER_IMPURE();
	return isprint(ch);
@@pp_else@@
@@pp_if defined(__CRT_HAVE___ctype_b_loc) && defined(__CRT_GLC)@@
#include <hybrid/byteorder.h>
@@pp_if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__@@
	return locale->__ctype_b[ch] & (1 << 6);
@@pp_else@@
	return locale->__ctype_b[ch] & (1 << 14);
@@pp_endif@@
@@pp_elif defined(@__CRT_HAVE___locale_ctype_ptr_l@) && defined(__CRT_CYG)@@
	return ((__locale_ctype_ptr_l(locale) + 1)[ch & 0xff] & 0227) != 0;
@@pp_elif defined(@__CRT_HAVE__isctype_l@) && defined(__CRT_DOS)@@
	return _isctype_l(ch, 0x0157, locale);
@@pp_else@@
	(void)locale;
	COMPILER_IMPURE();
	return isprint(ch);
@@pp_endif@@
@@pp_endif@@
}

[[wunused, ATTR_PURE, export_alias("__isblank_l")]]
int isblank_l(int ch, __locale_t locale) {
@@pp_ifdef __BUILDING_LIBC@@
	(void)locale;
	COMPILER_IMPURE();
	return isblank(ch);
@@pp_else@@
@@pp_if defined(__CRT_HAVE___ctype_b_loc) && defined(__CRT_GLC)@@
#include <hybrid/byteorder.h>
@@pp_if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__@@
	return locale->__ctype_b[ch] & (1 << 8);
@@pp_else@@
	return locale->__ctype_b[ch] & (1 << 0);
@@pp_endif@@
@@pp_elif defined(@__CRT_HAVE___locale_ctype_ptr_l@) && defined(__CRT_CYG)@@
	return ((__locale_ctype_ptr_l(locale) + 1)[ch & 0xff] & 0200) != 0 || ch == '\t';
@@pp_else@@
	(void)locale;
	COMPILER_IMPURE();
	return isblank(ch);
@@pp_endif@@
@@pp_endif@@
}


[[wunused, ATTR_PURE, export_alias("_tolower_l", "__tolower_l")]]
int tolower_l(int ch, __locale_t locale) {
	/* TODO: GLC has a variant for this! */
	(void)locale;
	COMPILER_IMPURE();
	return tolower(ch);
}

[[wunused, ATTR_PURE, export_alias("_toupper_l", "__toupper_l")]]
int toupper_l(int ch, __locale_t locale) {
	/* TODO: GLC has a variant for this! */
	(void)locale;
	COMPILER_IMPURE();
	return toupper(ch);
}


%{
#endif /* __USE_XOPEN2K8 */


/* ASCII-only, inline variants. */
#ifndef __NO_ATTR_INLINE
__LOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(__LIBCCALL __ascii_iscntrl)(int __ch) { return (__UINT8_TYPE__)__ch <= 0x1f || (__UINT8_TYPE__)__ch == 0x7f; }
__LOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(__LIBCCALL __ascii_isspace)(int __ch) { return ((__UINT8_TYPE__)__ch >= 0x09 && (__UINT8_TYPE__)__ch <= 0x0d) || (__UINT8_TYPE__)__ch == 0x20; }
__LOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(__LIBCCALL __ascii_isupper)(int __ch) { return (__UINT8_TYPE__)__ch >= 0x41 && (__UINT8_TYPE__)__ch <= 0x5a; }
__LOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(__LIBCCALL __ascii_islower)(int __ch) { return (__UINT8_TYPE__)__ch >= 0x61 && (__UINT8_TYPE__)__ch <= 0x7a; }
__LOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(__LIBCCALL __ascii_isalpha)(int __ch) { return __ascii_isupper(__ch) || __ascii_islower(__ch); }
__LOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(__LIBCCALL __ascii_isdigit)(int __ch) { return (__UINT8_TYPE__)__ch >= 0x30 && (__UINT8_TYPE__)__ch <= 0x39; }
__LOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(__LIBCCALL __ascii_isxdigit)(int __ch) { return __ascii_isdigit(__ch) || ((__UINT8_TYPE__)__ch >= 0x41 && (__UINT8_TYPE__)__ch <= 0x46) || ((__UINT8_TYPE__)__ch >= 0x61 && (__UINT8_TYPE__)__ch <= 0x66); }
__LOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(__LIBCCALL __ascii_isalnum)(int __ch) { return __ascii_isupper(__ch) || __ascii_islower(__ch) || __ascii_isdigit(__ch); }
__LOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(__LIBCCALL __ascii_ispunct)(int __ch) { return ((__UINT8_TYPE__)__ch >= 0x21 && (__UINT8_TYPE__)__ch <= 0x2f) || ((__UINT8_TYPE__)__ch >= 0x3a && (__UINT8_TYPE__)__ch <= 0x40) || ((__UINT8_TYPE__)__ch >= 0x5b && (__UINT8_TYPE__)__ch <= 0x60) || ((__UINT8_TYPE__)__ch >= 0x7b && (__UINT8_TYPE__)__ch <= 0x7e); }
__LOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(__LIBCCALL __ascii_isgraph)(int __ch) { return (__UINT8_TYPE__)__ch >= 0x21 && (__UINT8_TYPE__)__ch <= 0x7e; }
__LOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(__LIBCCALL __ascii_isprint)(int __ch) { return (__UINT8_TYPE__)__ch >= 0x20 && (__UINT8_TYPE__)__ch <= 0x7e; }
__LOCAL __ATTR_WUNUSED __ATTR_CONST int __NOTHROW(__LIBCCALL __ascii_tolower)(int __ch) { return __ascii_isupper(__ch) ? ((__UINT8_TYPE__)__ch+0x20) : __ch; }
__LOCAL __ATTR_WUNUSED __ATTR_CONST int __NOTHROW(__LIBCCALL __ascii_toupper)(int __ch) { return __ascii_islower(__ch) ? ((__UINT8_TYPE__)__ch-0x20) : __ch; }
#ifdef __USE_ISOC99
__LOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(__LIBCCALL __ascii_isblank)(int __ch) { return (__UINT8_TYPE__)__ch == 0x09 || (__UINT8_TYPE__)__ch == 0x20; }
#endif /* __USE_ISOC99 */
#elif !defined(__NO_XBLOCK)
#define __ascii_iscntrl(ch)  __XBLOCK({ __UINT8_TYPE__ const __ac_ch = (__UINT8_TYPE__)(ch); __XRETURN __ac_ch <= 0x1f || __ac_ch == 0x7f; })
#define __ascii_isspace(ch)  __XBLOCK({ __UINT8_TYPE__ const __ac_ch = (__UINT8_TYPE__)(ch); __XRETURN (__ac_ch >= 0x09 && __ac_ch <= 0x0d) || __ac_ch == 0x20; })
#define __ascii_isupper(ch)  __XBLOCK({ __UINT8_TYPE__ const __ac_ch = (__UINT8_TYPE__)(ch); __XRETURN __ac_ch >= 0x41 && __ac_ch <= 0x5a; })
#define __ascii_islower(ch)  __XBLOCK({ __UINT8_TYPE__ const __ac_ch = (__UINT8_TYPE__)(ch); __XRETURN __ac_ch >= 0x61 && __ac_ch <= 0x7a; })
#define __ascii_isalpha(ch)  __XBLOCK({ __UINT8_TYPE__ const __ac_ch = (__UINT8_TYPE__)(ch); __XRETURN __ascii_isupper(__ac_ch) || __ascii_islower(__ac_ch); })
#define __ascii_isdigit(ch)  __XBLOCK({ __UINT8_TYPE__ const __ac_ch = (__UINT8_TYPE__)(ch); __XRETURN __ac_ch >= 0x30 && __ac_ch <= 0x39; })
#define __ascii_isxdigit(ch) __XBLOCK({ __UINT8_TYPE__ const __ac_ch = (__UINT8_TYPE__)(ch); __XRETURN __ascii_isdigit(__ac_ch) || (__ac_ch >= 0x41 && __ac_ch <= 0x46) || (__ac_ch >= 0x61 && __ac_ch <= 0x66); })
#define __ascii_isalnum(ch)  __XBLOCK({ __UINT8_TYPE__ const __ac_ch = (__UINT8_TYPE__)(ch); __XRETURN __ascii_isupper(__ac_ch) || __ascii_islower(__ac_ch) || __ascii_isdigit(__ac_ch); })
#define __ascii_ispunct(ch)  __XBLOCK({ __UINT8_TYPE__ const __ac_ch = (__UINT8_TYPE__)(ch); __XRETURN (__ac_ch >= 0x21 && __ac_ch <= 0x2f) || (__ac_ch >= 0x3a && __ac_ch <= 0x40) || (__ac_ch >= 0x5b && __ac_ch <= 0x60) || (__ac_ch >= 0x7b && __ac_ch <= 0x7e); })
#define __ascii_isgraph(ch)  __XBLOCK({ __UINT8_TYPE__ const __ac_ch = (__UINT8_TYPE__)(ch); __XRETURN __ac_ch >= 0x21 && __ac_ch <= 0x7e; })
#define __ascii_isprint(ch)  __XBLOCK({ __UINT8_TYPE__ const __ac_ch = (__UINT8_TYPE__)(ch); __XRETURN __ac_ch >= 0x20 && __ac_ch <= 0x7e; })
#define __ascii_tolower(ch)  __XBLOCK({ __UINT8_TYPE__ const __ac_ch = (__UINT8_TYPE__)(ch); __XRETURN (int)(__ascii_isupper(ch) ? (__ac_ch+0x20) : __ac_ch); })
#define __ascii_toupper(ch)  __XBLOCK({ __UINT8_TYPE__ const __ac_ch = (__UINT8_TYPE__)(ch); __XRETURN (int)(__ascii_islower(ch) ? (__ac_ch-0x20) : __ac_ch); })
#ifdef __USE_ISOC99
#define __ascii_isblank(ch)  __XBLOCK({ __UINT8_TYPE__ const __ac_ch = (__UINT8_TYPE__)(ch); __XRETURN __ac_ch == 0x09 || __ac_ch == 0x20; })
#endif /* __USE_ISOC99 */
#else /* ... */
#define __ascii_iscntrl(ch)  ((__UINT8_TYPE__)(ch) <= 0x1f || (__UINT8_TYPE__)(ch) == 0x7f)
#define __ascii_isspace(ch) (((__UINT8_TYPE__)(ch) >= 0x09 && (__UINT8_TYPE__)(ch) <= 0x0d) || \
                              (__UINT8_TYPE__)(ch) == 0x20)
#define __ascii_isupper(ch)  ((__UINT8_TYPE__)(ch) >= 0x41 && (__UINT8_TYPE__)(ch) <= 0x5a)
#define __ascii_islower(ch)  ((__UINT8_TYPE__)(ch) >= 0x61 && (__UINT8_TYPE__)(ch) <= 0x7a)
#define __ascii_isalpha(ch)  (__ascii_isupper(ch) || __ascii_islower(ch))
#define __ascii_isdigit(ch)  ((__UINT8_TYPE__)(ch) >= 0x30 && (__UINT8_TYPE__)(ch) <= 0x39)
#define __ascii_isxdigit(ch)  (__ascii_isdigit(ch) || \
                             ((__UINT8_TYPE__)(ch) >= 0x41 && (__UINT8_TYPE__)(ch) <= 0x46) || \
                             ((__UINT8_TYPE__)(ch) >= 0x61 && (__UINT8_TYPE__)(ch) <= 0x66))
#define __ascii_isalnum(ch)   (__ascii_isupper(ch) || __ascii_islower(ch) || __ascii_isdigit(ch))
#define __ascii_ispunct(ch) (((__UINT8_TYPE__)(ch) >= 0x21 && (__UINT8_TYPE__)(ch) <= 0x2f) || \
                             ((__UINT8_TYPE__)(ch) >= 0x3a && (__UINT8_TYPE__)(ch) <= 0x40) || \
                             ((__UINT8_TYPE__)(ch) >= 0x5b && (__UINT8_TYPE__)(ch) <= 0x60) || \
                             ((__UINT8_TYPE__)(ch) >= 0x7b && (__UINT8_TYPE__)(ch) <= 0x7e))
#define __ascii_isgraph(ch)  ((__UINT8_TYPE__)(ch) >= 0x21 && (__UINT8_TYPE__)(ch) <= 0x7e)
#define __ascii_isprint(ch)  ((__UINT8_TYPE__)(ch) >= 0x20 && (__UINT8_TYPE__)(ch) <= 0x7e)
#define __ascii_tolower(ch)  ((int)(__ascii_isupper(ch) ? ((ch)+0x20) : (ch)))
#define __ascii_toupper(ch)  ((int)(__ascii_islower(ch) ? ((ch)-0x20) : (ch)))
#ifdef __USE_ISOC99
#define __ascii_isblank(ch)  ((__UINT8_TYPE__)(ch) == 0x09 || (__UINT8_TYPE__)(ch) == 0x20)
#endif /* __USE_ISOC99 */
#endif /* !... */


#if (!defined(__cplusplus) || defined(__USE_CTYPE_MACROS)) && !defined(__CXX_SYSTEM_HEADER)

#if defined(__CRT_GLC) && defined(__CRT_HAVE___ctype_b_loc)  /* ---- GLIBC */
#include <hybrid/byteorder.h>
__NAMESPACE_INT_BEGIN
__CDECLARE(__ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED,__UINT16_TYPE__ const **,__NOTHROW,__ctype_b_loc,(void),())
#ifndef __NO_XBLOCK
#ifdef __CRT_HAVE___ctype_tolower_loc
__CDECLARE(__ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED,__INT32_TYPE__ const **,__NOTHROW,__ctype_tolower_loc,(void),())
#endif /* __CRT_HAVE___ctype_tolower_loc */
#ifdef __CRT_HAVE___ctype_toupper_loc
__CDECLARE(__ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED,__INT32_TYPE__ const **,__NOTHROW,__ctype_toupper_loc,(void),())
#endif /* __CRT_HAVE___ctype_toupper_loc */
#endif /* !__NO_XBLOCK */
__NAMESPACE_INT_END
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#define __inline_isupper(ch)  ((*__NAMESPACE_INT_SYM __ctype_b_loc())[ch] & (1 << 0))
#define __inline_islower(ch)  ((*__NAMESPACE_INT_SYM __ctype_b_loc())[ch] & (1 << 1))
#define __inline_isalpha(ch)  ((*__NAMESPACE_INT_SYM __ctype_b_loc())[ch] & (1 << 2))
#define __inline_isdigit(ch)  ((*__NAMESPACE_INT_SYM __ctype_b_loc())[ch] & (1 << 3))
#define __inline_isxdigit(ch) ((*__NAMESPACE_INT_SYM __ctype_b_loc())[ch] & (1 << 4))
#define __inline_isspace(ch)  ((*__NAMESPACE_INT_SYM __ctype_b_loc())[ch] & (1 << 5))
#define __inline_isprint(ch)  ((*__NAMESPACE_INT_SYM __ctype_b_loc())[ch] & (1 << 6))
#define __inline_isgraph(ch)  ((*__NAMESPACE_INT_SYM __ctype_b_loc())[ch] & (1 << 7))
#define __inline_iscntrl(ch)  ((*__NAMESPACE_INT_SYM __ctype_b_loc())[ch] & (1 << 9))
#define __inline_ispunct(ch)  ((*__NAMESPACE_INT_SYM __ctype_b_loc())[ch] & (1 << 10))
#define __inline_isalnum(ch)  ((*__NAMESPACE_INT_SYM __ctype_b_loc())[ch] & (1 << 11))
#ifdef __USE_ISOC99
#define __inline_isblank(ch)  ((*__NAMESPACE_INT_SYM __ctype_b_loc())[ch] & (1 << 8))
#endif /* __USE_ISOC99 */
#ifndef __USE_XOPEN2K8
#define __inline_isupper_l(ch, locale)  ((locale)->__ctype_b[ch] & (1 << 0))
#define __inline_islower_l(ch, locale)  ((locale)->__ctype_b[ch] & (1 << 1))
#define __inline_isalpha_l(ch, locale)  ((locale)->__ctype_b[ch] & (1 << 2))
#define __inline_isdigit_l(ch, locale)  ((locale)->__ctype_b[ch] & (1 << 3))
#define __inline_isxdigit_l(ch, locale) ((locale)->__ctype_b[ch] & (1 << 4))
#define __inline_isspace_l(ch, locale)  ((locale)->__ctype_b[ch] & (1 << 5))
#define __inline_isprint_l(ch, locale)  ((locale)->__ctype_b[ch] & (1 << 6))
#define __inline_isgraph_l(ch, locale)  ((locale)->__ctype_b[ch] & (1 << 7))
#define __inline_iscntrl_l(ch, locale)  ((locale)->__ctype_b[ch] & (1 << 9))
#define __inline_ispunct_l(ch, locale)  ((locale)->__ctype_b[ch] & (1 << 10))
#define __inline_isalnum_l(ch, locale)  ((locale)->__ctype_b[ch] & (1 << 11))
#define __inline_isblank_l(ch, locale)  ((locale)->__ctype_b[ch] & (1 << 8))
#endif /* !__USE_XOPEN2K8 */
#else /* __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__ */
#define __inline_isupper(ch)  ((*__NAMESPACE_INT_SYM __ctype_b_loc())[(int)(ch)] & (1 << 8))
#define __inline_islower(ch)  ((*__NAMESPACE_INT_SYM __ctype_b_loc())[(int)(ch)] & (1 << 9))
#define __inline_isalpha(ch)  ((*__NAMESPACE_INT_SYM __ctype_b_loc())[(int)(ch)] & (1 << 10))
#define __inline_isdigit(ch)  ((*__NAMESPACE_INT_SYM __ctype_b_loc())[(int)(ch)] & (1 << 11))
#define __inline_isxdigit(ch) ((*__NAMESPACE_INT_SYM __ctype_b_loc())[(int)(ch)] & (1 << 12))
#define __inline_isspace(ch)  ((*__NAMESPACE_INT_SYM __ctype_b_loc())[(int)(ch)] & (1 << 13))
#define __inline_isprint(ch)  ((*__NAMESPACE_INT_SYM __ctype_b_loc())[(int)(ch)] & (1 << 14))
#define __inline_isgraph(ch)  ((*__NAMESPACE_INT_SYM __ctype_b_loc())[(int)(ch)] & (1 << 15))
#define __inline_iscntrl(ch)  ((*__NAMESPACE_INT_SYM __ctype_b_loc())[(int)(ch)] & (1 << 1))
#define __inline_ispunct(ch)  ((*__NAMESPACE_INT_SYM __ctype_b_loc())[(int)(ch)] & (1 << 2))
#define __inline_isalnum(ch)  ((*__NAMESPACE_INT_SYM __ctype_b_loc())[(int)(ch)] & (1 << 3))
#ifdef __USE_ISOC99
#define __inline_isblank(ch)  ((*__NAMESPACE_INT_SYM __ctype_b_loc())[(int)(ch)] & (1 << 0))
#endif /* __USE_ISOC99 */
#ifdef __USE_XOPEN2K8
#define __inline_isupper_l(ch, locale)  ((locale)->__ctype_b[(int)(ch)] & (1 << 8))
#define __inline_islower_l(ch, locale)  ((locale)->__ctype_b[(int)(ch)] & (1 << 9))
#define __inline_isalpha_l(ch, locale)  ((locale)->__ctype_b[(int)(ch)] & (1 << 10))
#define __inline_isdigit_l(ch, locale)  ((locale)->__ctype_b[(int)(ch)] & (1 << 11))
#define __inline_isxdigit_l(ch, locale) ((locale)->__ctype_b[(int)(ch)] & (1 << 12))
#define __inline_isspace_l(ch, locale)  ((locale)->__ctype_b[(int)(ch)] & (1 << 13))
#define __inline_isprint_l(ch, locale)  ((locale)->__ctype_b[(int)(ch)] & (1 << 14))
#define __inline_isgraph_l(ch, locale)  ((locale)->__ctype_b[(int)(ch)] & (1 << 15))
#define __inline_iscntrl_l(ch, locale)  ((locale)->__ctype_b[(int)(ch)] & (1 << 1))
#define __inline_ispunct_l(ch, locale)  ((locale)->__ctype_b[(int)(ch)] & (1 << 2))
#define __inline_isalnum_l(ch, locale)  ((locale)->__ctype_b[(int)(ch)] & (1 << 3))
#define __inline_isblank_l(ch, locale)  ((locale)->__ctype_b[(int)(ch)] & (1 << 0))
#endif /* !__USE_XOPEN2K8 */
#endif /* __BYTE_ORDER__ != __ORDER_BIG_ENDIAN__ */
#ifndef __NO_XBLOCK
#ifdef __CRT_HAVE___ctype_tolower_loc
#define __inline_tolower(ch)  __XBLOCK({ int __tol_ch = (int)(ch); __XRETURN __tol_ch >= -128 && __tol_ch < 256 ? (*__ctype_tolower_loc())[__tol_ch] : __tol_ch; })
#endif /* __CRT_HAVE___ctype_tolower_loc */
#ifdef __CRT_HAVE___ctype_toupper_loc
#define __inline_toupper(ch)  __XBLOCK({ int __tol_ch = (int)(ch); __XRETURN __tol_ch >= -128 && __tol_ch < 256 ? (*__ctype_toupper_loc())[__tol_ch] : __tol_ch; })
#endif /* __CRT_HAVE___ctype_toupper_loc */
#endif /* !__NO_XBLOCK */
#elif defined(__CRT_CYG) && defined(__CRT_HAVE___locale_ctype_ptr)  /* ---- CYGWIN */
__NAMESPACE_INT_BEGIN
__CDECLARE(__ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED,char const *,__NOTHROW,__locale_ctype_ptr,(void),())
#ifdef __CRT_HAVE___locale_ctype_ptr_l
__CDECLARE(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED,char const *,__NOTHROW_NCX,__locale_ctype_ptr_l,(__locale_t __locale),(__locale))
#endif /* __CRT_HAVE___locale_ctype_ptr_l */
__NAMESPACE_INT_END
#define __chtype_lookup(ch)           ((__NAMESPACE_INT_SYM __locale_ctype_ptr()+1)[(int)(ch)])
#ifdef __CRT_HAVE___locale_ctype_ptr_l
#define __chtype_lookup_l(ch, locale) ((__NAMESPACE_INT_SYM __locale_ctype_ptr_l(locale)+1)[(int)(ch)])
#else /* __CRT_HAVE___locale_ctype_ptr_l */
#define __chtype_lookup_l(ch, locale) ((__NAMESPACE_INT_SYM __locale_ctype_ptr(locale)+1)[(int)(ch)])
#endif /* !__CRT_HAVE___locale_ctype_ptr_l */
#define __inline_isalpha(ch)           (__chtype_lookup(ch)&3)
#define __inline_isupper(ch)          ((__chtype_lookup(ch)&3)==1)
#define __inline_islower(ch)          ((__chtype_lookup(ch)&3)==2)
#define __inline_isdigit(ch)           (__chtype_lookup(ch)&4)
#define __inline_isxdigit(ch)          (__chtype_lookup(ch)&014)
#define __inline_isspace(ch)           (__chtype_lookup(ch)&010)
#define __inline_ispunct(ch)           (__chtype_lookup(ch)&020)
#define __inline_isalnum(ch)           (__chtype_lookup(ch)&7)
#define __inline_isprint(ch)           (__chtype_lookup(ch)&0227)
#define __inline_isgraph(ch)           (__chtype_lookup(ch)&027)
#define __inline_iscntrl(ch)           (__chtype_lookup(ch)&040)
#ifdef __USE_XOPEN2K8
#define __inline_isalpha_l(ch, locale)  (__chtype_lookup_l(ch, locale)&3)
#define __inline_isupper_l(ch, locale) ((__chtype_lookup_l(ch, locale)&3)==1)
#define __inline_islower_l(ch, locale) ((__chtype_lookup_l(ch, locale)&3)==2)
#define __inline_isdigit_l(ch, locale)  (__chtype_lookup_l(ch, locale)&4)
#define __inline_isxdigit_l(ch, locale) (__chtype_lookup_l(ch, locale)&014)
#define __inline_isspace_l(ch, locale)  (__chtype_lookup_l(ch, locale)&010)
#define __inline_ispunct_l(ch, locale)  (__chtype_lookup_l(ch, locale)&020)
#define __inline_isalnum_l(ch, locale)  (__chtype_lookup_l(ch, locale)&7)
#define __inline_isprint_l(ch, locale)  (__chtype_lookup_l(ch, locale)&0227)
#define __inline_isgraph_l(ch, locale)  (__chtype_lookup_l(ch, locale)&027)
#define __inline_iscntrl_l(ch, locale)  (__chtype_lookup_l(ch, locale)&040)
#endif /* __USE_XOPEN2K8 */
#ifdef __USE_ISOC99
#ifndef __NO_XBLOCK
#define __inline_isblank(ch)           __XBLOCK({ int __x = (ch); __XRETURN (__chtype_lookup(__x) & 0200) || (__x) == '\t'; })
#define __inline_isblank_l(ch, locale) __XBLOCK({ int __x = (ch); __XRETURN (__chtype_lookup_l(__x, locale) & 0200) || (__x) == '\t'; })
#endif /* !__NO_XBLOCK */
#endif /* __USE_ISOC99 */
#elif defined(__CRT_DOS) && defined(__CRT_HAVE__isctype) /* ---- DOS (MSVC) */
__NAMESPACE_INT_BEGIN
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,_isctype,(int __ch, int __mask),(__ch,__mask))
#ifdef __CRT_HAVE__isctype_l
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_isctype_l,(int __ch, int __mask, __locale_t __locale),(__ch,__mask,__locale))
#endif /* __CRT_HAVE__isctype_l */
__NAMESPACE_INT_END
#define __dos_isctype(ch, mask)      (__NAMESPACE_INT_SYM _isctype)(ch, mask)
#ifdef __CRT_HAVE__isctype_l
#define _isctype_l(ch, mask, locale) (__NAMESPACE_INT_SYM _isctype_l)(ch, mask, locale)
#else /* __CRT_HAVE__isctype_l */
#define _isctype_l(ch, mask, locale) (__NAMESPACE_INT_SYM _isctype)(ch, mask)
#endif /* !__CRT_HAVE__isctype_l */
#define __inline_isalnum(ch)            __dos_isctype((ch), 0x0107)
#define __inline_isalpha(ch)            __dos_isctype((ch), 0x0103)
#define __inline_isupper(ch)            __dos_isctype((ch), 0x0001)
#define __inline_islower(ch)            __dos_isctype((ch), 0x0002)
#define __inline_isdigit(ch)            __dos_isctype((ch), 0x0004)
#define __inline_isxdigit(ch)           __dos_isctype((ch), 0x0080)
#define __inline_isspace(ch)            __dos_isctype((ch), 0x0008)
#define __inline_ispunct(ch)            __dos_isctype((ch), 0x0010)
#define __inline_isprint(ch)            __dos_isctype((ch), 0x0157)
#define __inline_isgraph(ch)            __dos_isctype((ch), 0x0117)
#define __inline_iscntrl(ch)            __dos_isctype((ch), 0x0020)
#ifdef __USE_XOPEN2K8
#define __inline_isalnum_l(ch, locale)   _isctype_l((ch), 0x0107, (locale))
#define __inline_isalpha_l(ch, locale)   _isctype_l((ch), 0x0103, (locale))
#define __inline_isupper_l(ch, locale)   _isctype_l((ch), 0x0001, (locale))
#define __inline_islower_l(ch, locale)   _isctype_l((ch), 0x0002, (locale))
#define __inline_isdigit_l(ch, locale)   _isctype_l((ch), 0x0004, (locale))
#define __inline_isxdigit_l(ch, locale)  _isctype_l((ch), 0x0080, (locale))
#define __inline_isspace_l(ch, locale)   _isctype_l((ch), 0x0008, (locale))
#define __inline_ispunct_l(ch, locale)   _isctype_l((ch), 0x0010, (locale))
#define __inline_isprint_l(ch, locale)   _isctype_l((ch), 0x0157, (locale))
#define __inline_isgraph_l(ch, locale)   _isctype_l((ch), 0x0117, (locale))
#define __inline_iscntrl_l(ch, locale)   _isctype_l((ch), 0x0020, (locale))
#endif /* __USE_XOPEN2K8 */
#endif /* CRT... */

#ifndef __inline_isalnum
#define __inline_isalnum(ch) (isalnum)(ch)
#endif /* !__inline_isalnum */
#ifndef __inline_isalpha
#define __inline_isalpha(ch) (isalpha)(ch)
#endif /* !__inline_isalpha */
#ifndef __inline_isupper
#define __inline_isupper(ch) (isupper)(ch)
#endif /* !__inline_isupper */
#ifndef __inline_islower
#define __inline_islower(ch) (islower)(ch)
#endif /* !__inline_islower */
#ifndef __inline_isdigit
#define __inline_isdigit(ch) (isdigit)(ch)
#endif /* !__inline_isdigit */
#ifndef __inline_isxdigit
#define __inline_isxdigit(ch) (isxdigit)(ch)
#endif /* !__inline_isxdigit */
#ifndef __inline_isspace
#define __inline_isspace(ch) (isspace)(ch)
#endif /* !__inline_isspace */
#ifndef __inline_ispunct
#define __inline_ispunct(ch) (ispunct)(ch)
#endif /* !__inline_ispunct */
#ifndef __inline_isprint
#define __inline_isprint(ch) (isprint)(ch)
#endif /* !__inline_isprint */
#ifndef __inline_isgraph
#define __inline_isgraph(ch) (isgraph)(ch)
#endif /* !__inline_isgraph */
#ifndef __inline_iscntrl
#define __inline_iscntrl(ch) (iscntrl)(ch)
#endif /* !__inline_iscntrl */
#ifdef __USE_ISOC99
#ifndef __inline_isblank
#define __inline_isblank(ch) (isblank)(ch)
#endif /* !__inline_isblank */
#endif /* __USE_ISOC99 */

#ifdef __USE_XOPEN2K8
#ifdef __inline_isalnum_l
#define isalnum_l(ch, locale)  __inline_isalnum_l(ch, locale)
#endif /* __inline_isalnum_l */
#ifdef __inline_isalpha_l
#define isalpha_l(ch, locale)  __inline_isalpha_l(ch, locale)
#endif /* __inline_isalpha_l */
#ifdef __inline_isupper_l
#define isupper_l(ch, locale)  __inline_isupper_l(ch, locale)
#endif /* __inline_isupper_l */
#ifdef __inline_islower_l
#define islower_l(ch, locale)  __inline_islower_l(ch, locale)
#endif /* __inline_islower_l */
#ifdef __inline_isdigit_l
#define isdigit_l(ch, locale)  __inline_isdigit_l(ch, locale)
#endif /* __inline_isdigit_l */
#ifdef __inline_isxdigit_l
#define isxdigit_l(ch, locale) __inline_isxdigit_l(ch, locale)
#endif /* __inline_isxdigit_l */
#ifdef __inline_isspace_l
#define isspace_l(ch, locale)  __inline_isspace_l(ch, locale)
#endif /* __inline_isspace_l */
#ifdef __inline_ispunct_l
#define ispunct_l(ch, locale)  __inline_ispunct_l(ch, locale)
#endif /* __inline_ispunct_l */
#ifdef __inline_isprint_l
#define isprint_l(ch, locale)  __inline_isprint_l(ch, locale)
#endif /* __inline_isprint_l */
#ifdef __inline_isgraph_l
#define isgraph_l(ch, locale)  __inline_isgraph_l(ch, locale)
#endif /* __inline_isgraph_l */
#ifdef __inline_iscntrl_l
#define iscntrl_l(ch, locale)  __inline_iscntrl_l(ch, locale)
#endif /* __inline_iscntrl_l */
#endif /* __USE_XOPEN2K8 */

#ifndef __NO_builtin_constant_p
#ifndef __NO_builtin_choose_expr
#define isalnum(ch)  __builtin_choose_expr(__builtin_constant_p(ch), __ascii_isalnum(ch), __inline_isalnum(ch))
#define isalpha(ch)  __builtin_choose_expr(__builtin_constant_p(ch), __ascii_isalpha(ch), __inline_isalpha(ch))
#define isupper(ch)  __builtin_choose_expr(__builtin_constant_p(ch), __ascii_isupper(ch), __inline_isupper(ch))
#define islower(ch)  __builtin_choose_expr(__builtin_constant_p(ch), __ascii_islower(ch), __inline_islower(ch))
#define isdigit(ch)  __builtin_choose_expr(__builtin_constant_p(ch), __ascii_isdigit(ch), __inline_isdigit(ch))
#define isxdigit(ch) __builtin_choose_expr(__builtin_constant_p(ch), __ascii_isxdigit(ch), __inline_isxdigit(ch))
#define isspace(ch)  __builtin_choose_expr(__builtin_constant_p(ch), __ascii_isspace(ch), __inline_isspace(ch))
#define ispunct(ch)  __builtin_choose_expr(__builtin_constant_p(ch), __ascii_ispunct(ch), __inline_ispunct(ch))
#define isprint(ch)  __builtin_choose_expr(__builtin_constant_p(ch), __ascii_isprint(ch), __inline_isprint(ch))
#define isgraph(ch)  __builtin_choose_expr(__builtin_constant_p(ch), __ascii_isgraph(ch), __inline_isgraph(ch))
#define iscntrl(ch)  __builtin_choose_expr(__builtin_constant_p(ch), __ascii_iscntrl(ch), __inline_iscntrl(ch))
#ifdef __USE_ISOC99
#define isblank(ch)  __builtin_choose_expr(__builtin_constant_p(ch), __ascii_isblank(ch), __inline_isblank(ch))
#endif /* __USE_ISOC99 */
#else /* !__NO_builtin_choose_expr */
#define isalnum(ch)  (__builtin_constant_p(ch) ? __ascii_isalnum(ch) : __inline_isalnum(ch))
#define isalpha(ch)  (__builtin_constant_p(ch) ? __ascii_isalpha(ch) : __inline_isalpha(ch))
#define isupper(ch)  (__builtin_constant_p(ch) ? __ascii_isupper(ch) : __inline_isupper(ch))
#define islower(ch)  (__builtin_constant_p(ch) ? __ascii_islower(ch) : __inline_islower(ch))
#define isdigit(ch)  (__builtin_constant_p(ch) ? __ascii_isdigit(ch) : __inline_isdigit(ch))
#define isxdigit(ch) (__builtin_constant_p(ch) ? __ascii_isxdigit(ch) : __inline_isxdigit(ch))
#define isspace(ch)  (__builtin_constant_p(ch) ? __ascii_isspace(ch) : __inline_isspace(ch))
#define ispunct(ch)  (__builtin_constant_p(ch) ? __ascii_ispunct(ch) : __inline_ispunct(ch))
#define isprint(ch)  (__builtin_constant_p(ch) ? __ascii_isprint(ch) : __inline_isprint(ch))
#define isgraph(ch)  (__builtin_constant_p(ch) ? __ascii_isgraph(ch) : __inline_isgraph(ch))
#define iscntrl(ch)  (__builtin_constant_p(ch) ? __ascii_iscntrl(ch) : __inline_iscntrl(ch))
#ifdef __USE_ISOC99
#define isblank(ch)  (__builtin_constant_p(ch) ? __ascii_isblank(ch) : __inline_isblank(ch))
#endif /* __USE_ISOC99 */
#endif /* __NO_builtin_choose_expr */
#else /* !__NO_builtin_constant_p */
#define isalnum(ch)  __inline_isalnum(ch)
#define isalpha(ch)  __inline_isalpha(ch)
#define isupper(ch)  __inline_isupper(ch)
#define islower(ch)  __inline_islower(ch)
#define isdigit(ch)  __inline_isdigit(ch)
#define isxdigit(ch) __inline_isxdigit(ch)
#define isspace(ch)  __inline_isspace(ch)
#define ispunct(ch)  __inline_ispunct(ch)
#define isprint(ch)  __inline_isprint(ch)
#define isgraph(ch)  __inline_isgraph(ch)
#define iscntrl(ch)  __inline_iscntrl(ch)
#ifdef __USE_ISOC99
#define isblank(ch)  __inline_isblank(ch)
#endif /* __USE_ISOC99 */
#endif /* __NO_builtin_constant_p */

#endif /* (!__cplusplus || __USE_CTYPE_MACROS) && !__CXX_SYSTEM_HEADER */


#if defined(__USE_MISC) || defined(__USE_XOPEN)
}
%[default:section(".text.crt{|.dos}.unicode.static.ctype")];

@@Returns non-zero if `(C & ~0x7f) == 0'
[[nothrow, ATTR_CONST]]
int isascii(int c) {
	return (c & ~0x7f) == 0;
}

@@Re-returns `C & 0x7f'
[[nothrow, ATTR_CONST]]
int toascii(int c) {
	return c & 0x7f;
}

%{
#if (!defined(__cplusplus) || defined(__USE_CTYPE_MACROS)) && !defined(__CXX_SYSTEM_HEADER)
#define isascii(c) (((c) & ~0x7f) == 0)
#define toascii(c) ((c) & 0x7f)
#endif /* (!__cplusplus || __USE_CTYPE_MACROS) && !__CXX_SYSTEM_HEADER */

#endif /* __USE_MISC || __USE_XOPEN */

__SYSDECL_END
#endif /* __CC__ */

}

