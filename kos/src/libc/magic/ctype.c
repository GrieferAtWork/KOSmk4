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
/* (>) Standard: ISO C89 (ANSI X3.159-1989) */
/* (>) Standard: POSIX.1 (Issue 1, IEEE Std 1003.1-1988) */
/* (#) Portability: Cygwin        (/newlib/libc/include/ctype.h) */
/* (#) Portability: DJGPP         (/include/ctype.h) */
/* (#) Portability: DragonFly BSD (/include/ctype.h) */
/* (#) Portability: EMX kLIBC     (/libc/include/ctype.h) */
/* (#) Portability: FreeBSD       (/include/ctype.h) */
/* (#) Portability: GNU C Library (/ctype/ctype.h) */
/* (#) Portability: MSVC          (/include/ctype.h) */
/* (#) Portability: MinGW         (/mingw-w64-headers/crt/ctype.h) */
/* (#) Portability: NetBSD        (/include/ctype.h) */
/* (#) Portability: Newlib        (/newlib/libc/include/ctype.h) */
/* (#) Portability: OpenBSD       (/include/ctype.h) */
/* (#) Portability: OpenSolaris   (/usr/src/head/ctype.h) */
/* (#) Portability: PDCLib        (/include/ctype.h) */
/* (#) Portability: Windows Kits  (/ucrt/ctype.h) */
/* (#) Portability: avr-libc      (/include/ctype.h) */
/* (#) Portability: diet libc     (/include/ctype.h) */
/* (#) Portability: libc4/5       (/include/ctype.h) */
/* (#) Portability: libc6         (/include/ctype.h) */
/* (#) Portability: libcmini      (/include/ctype.h) */
/* (#) Portability: mintlib       (/include/ctype.h) */
/* (#) Portability: musl libc     (/include/ctype.h) */
/* (#) Portability: uClibc        (/include/ctype.h) */
}

%[define_ccompat_header("cctype")]
%[define_replacement(locale_t = __locale_t)]

%[define_str2wcs_replacement(tolower   = towlower)]
%[define_str2wcs_replacement(toupper   = towupper)]
%[define_str2wcs_replacement(isalnum   = iswalnum)]
%[define_str2wcs_replacement(isalpha   = iswalpha)]
%[define_str2wcs_replacement(isupper   = iswupper)]
%[define_str2wcs_replacement(islower   = iswlower)]
%[define_str2wcs_replacement(isdigit   = iswdigit)]
%[define_str2wcs_replacement(isxdigit  = iswxdigit)]
%[define_str2wcs_replacement(isspace   = iswspace)]
%[define_str2wcs_replacement(ispunct   = iswpunct)]
%[define_str2wcs_replacement(isprint   = iswprint)]
%[define_str2wcs_replacement(isgraph   = iswgraph)]
%[define_str2wcs_replacement(iscntrl   = iswcntrl)]
%[define_str2wcs_replacement(isblank   = iswblank)]
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
%[define_str2wcs_replacement(isascii   = iswascii)]

%[declare_kernel_export("__ctype_C_flags")]
%[declare_kernel_export("__ctype_C_tolower")]
%[declare_kernel_export("__ctype_C_toupper")]

%[assume_defined_in_kos_userspace(__crt_iscntrl)]
%[assume_defined_in_kos_userspace(__crt_isspace)]
%[assume_defined_in_kos_userspace(__crt_islower)]
%[assume_defined_in_kos_userspace(__crt_isupper)]
%[assume_defined_in_kos_userspace(__crt_isalpha)]
%[assume_defined_in_kos_userspace(__crt_isdigit)]
%[assume_defined_in_kos_userspace(__crt_isxdigit)]
%[assume_defined_in_kos_userspace(__crt_isalnum)]
%[assume_defined_in_kos_userspace(__crt_ispunct)]
%[assume_defined_in_kos_userspace(__crt_isgraph)]
%[assume_defined_in_kos_userspace(__crt_isprint)]
%[assume_defined_in_kos_userspace(__crt_isblank)]
%[assume_defined_in_kos_userspace(__crt_tolower)]
%[assume_defined_in_kos_userspace(__crt_toupper)]

%(auto_source){
#include "../libc/globals.h"
}


/* Because KOS uses UTF-8 through, functions from <ctype.h> must
 * operate on only those characters which can be represented  in
 * single-byte mode (iow: ASCII)
 *
 * To improve performance, we make use of a lookup table define
 * flags   and   implement   the   tolower/toupper   functions.
 *
 * CTYPE flags are defined as follows:
 *     0x01: iscntrl   00-1F, 7F
 *     0x02: isspace   09-0D, 20
 *     0x04: islower   61-7A
 *     0x08: isupper   41-5A
 *     0x10: isdigit   30-39
 *     0x20: ishex     41-46, 61-66
 *     0x40: ispunct   21-2F, 3A-40, 5B-60, 7B-7E
 *     0x80: -         20 */
/*[[[deemon
local CTYPE = [0] * 256;
local TOLOWER = [0] * 256;
local TOUPPER = [0] * 256;
for (local i: [:256]) {
	local flags = 0;
	if ((i >= 0x00 && i <= 0x1F) || i == 0x7F)
		flags |= 0x01;
	if ((i >= 0x09 && i <= 0x0D) || i == 0x20)
		flags |= 0x02;
	if (i >= 0x61 && i <= 0x7A)
		flags |= 0x04;
	if (i >= 0x41 && i <= 0x5A)
		flags |= 0x08;
	if (i >= 0x30 && i <= 0x39)
		flags |= 0x10;
	if ((i >= 0x41 && i <= 0x46) || (i >= 0x61 && i <= 0x66))
		flags |= 0x20;
	if ((i >= 0x21 && i <= 0x2F) || (i >= 0x3A && i <= 0x40) ||
	    (i >= 0x5B && i <= 0x60) || (i >= 0x7B && i <= 0x7E))
		flags |= 0x40;
	if (i == 0x20)
		flags |= 0x80;
	CTYPE[i] = flags;
	local tolower = i;
	local toupper = i;
	if (i >= 0x41 && i <= 0x5a)
		tolower = i + 0x20;
	if (i >= 0x61 && i <= 0x7a)
		toupper = i - 0x20;
	TOLOWER[i] = tolower;
	TOUPPER[i] = toupper;
}
function printTable(name, tab, signed) {
	print("INTDEF __", signed ? "" : "U", "INT8_TYPE__ const ", name, "[256];");
	print("INTERN_CONST ATTR_SECTION(\".rodata.crt.unicode.static.ctype\") "),;
	print("__", signed ? "" : "U", "INT8_TYPE__ const ", name, "[256] = {");
	for (local line: tab.segments(16))
		print("	", ",".join(for (local x: line) (signed ? x.signed8 : x).hex()), ",");
	print("};");
}
print("%(auto_source){");
print("DEFINE_PUBLIC_ALIAS(__ctype_C_flags, libc___ctype_C_flags);");
print("DEFINE_PUBLIC_ALIAS(__ctype_C_tolower, libc___ctype_C_tolower);");
print("DEFINE_PUBLIC_ALIAS(__ctype_C_toupper, libc___ctype_C_toupper);");
printTable("libc___ctype_C_flags", CTYPE, false);
printTable("libc___ctype_C_tolower", TOLOWER, true);
printTable("libc___ctype_C_toupper", TOUPPER, true);
print("}");
]]]*/
%(auto_source){
DEFINE_PUBLIC_ALIAS(__ctype_C_flags, libc___ctype_C_flags);
DEFINE_PUBLIC_ALIAS(__ctype_C_tolower, libc___ctype_C_tolower);
DEFINE_PUBLIC_ALIAS(__ctype_C_toupper, libc___ctype_C_toupper);
INTDEF __UINT8_TYPE__ const libc___ctype_C_flags[256];
INTERN_CONST ATTR_SECTION(".rodata.crt.unicode.static.ctype") __UINT8_TYPE__ const libc___ctype_C_flags[256] = {
	0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x3,0x3,0x3,0x3,0x3,0x1,0x1,
	0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,
	0x82,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,
	0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x40,0x40,0x40,0x40,0x40,0x40,
	0x40,0x28,0x28,0x28,0x28,0x28,0x28,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,
	0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x40,0x40,0x40,0x40,0x40,
	0x40,0x24,0x24,0x24,0x24,0x24,0x24,0x4,0x4,0x4,0x4,0x4,0x4,0x4,0x4,0x4,
	0x4,0x4,0x4,0x4,0x4,0x4,0x4,0x4,0x4,0x4,0x4,0x40,0x40,0x40,0x40,0x1,
	0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
	0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
	0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
	0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
	0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
	0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
	0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
	0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
};
INTDEF __INT8_TYPE__ const libc___ctype_C_tolower[256];
INTERN_CONST ATTR_SECTION(".rodata.crt.unicode.static.ctype") __INT8_TYPE__ const libc___ctype_C_tolower[256] = {
	0x0,0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x8,0x9,0xa,0xb,0xc,0xd,0xe,0xf,
	0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1a,0x1b,0x1c,0x1d,0x1e,0x1f,
	0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,0x29,0x2a,0x2b,0x2c,0x2d,0x2e,0x2f,
	0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x3a,0x3b,0x3c,0x3d,0x3e,0x3f,
	0x40,0x61,0x62,0x63,0x64,0x65,0x66,0x67,0x68,0x69,0x6a,0x6b,0x6c,0x6d,0x6e,0x6f,
	0x70,0x71,0x72,0x73,0x74,0x75,0x76,0x77,0x78,0x79,0x7a,0x5b,0x5c,0x5d,0x5e,0x5f,
	0x60,0x61,0x62,0x63,0x64,0x65,0x66,0x67,0x68,0x69,0x6a,0x6b,0x6c,0x6d,0x6e,0x6f,
	0x70,0x71,0x72,0x73,0x74,0x75,0x76,0x77,0x78,0x79,0x7a,0x7b,0x7c,0x7d,0x7e,0x7f,
	-0x80,-0x7f,-0x7e,-0x7d,-0x7c,-0x7b,-0x7a,-0x79,-0x78,-0x77,-0x76,-0x75,-0x74,-0x73,-0x72,-0x71,
	-0x70,-0x6f,-0x6e,-0x6d,-0x6c,-0x6b,-0x6a,-0x69,-0x68,-0x67,-0x66,-0x65,-0x64,-0x63,-0x62,-0x61,
	-0x60,-0x5f,-0x5e,-0x5d,-0x5c,-0x5b,-0x5a,-0x59,-0x58,-0x57,-0x56,-0x55,-0x54,-0x53,-0x52,-0x51,
	-0x50,-0x4f,-0x4e,-0x4d,-0x4c,-0x4b,-0x4a,-0x49,-0x48,-0x47,-0x46,-0x45,-0x44,-0x43,-0x42,-0x41,
	-0x40,-0x3f,-0x3e,-0x3d,-0x3c,-0x3b,-0x3a,-0x39,-0x38,-0x37,-0x36,-0x35,-0x34,-0x33,-0x32,-0x31,
	-0x30,-0x2f,-0x2e,-0x2d,-0x2c,-0x2b,-0x2a,-0x29,-0x28,-0x27,-0x26,-0x25,-0x24,-0x23,-0x22,-0x21,
	-0x20,-0x1f,-0x1e,-0x1d,-0x1c,-0x1b,-0x1a,-0x19,-0x18,-0x17,-0x16,-0x15,-0x14,-0x13,-0x12,-0x11,
	-0x10,-0xf,-0xe,-0xd,-0xc,-0xb,-0xa,-0x9,-0x8,-0x7,-0x6,-0x5,-0x4,-0x3,-0x2,-0x1,
};
INTDEF __INT8_TYPE__ const libc___ctype_C_toupper[256];
INTERN_CONST ATTR_SECTION(".rodata.crt.unicode.static.ctype") __INT8_TYPE__ const libc___ctype_C_toupper[256] = {
	0x0,0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x8,0x9,0xa,0xb,0xc,0xd,0xe,0xf,
	0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1a,0x1b,0x1c,0x1d,0x1e,0x1f,
	0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,0x29,0x2a,0x2b,0x2c,0x2d,0x2e,0x2f,
	0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x3a,0x3b,0x3c,0x3d,0x3e,0x3f,
	0x40,0x41,0x42,0x43,0x44,0x45,0x46,0x47,0x48,0x49,0x4a,0x4b,0x4c,0x4d,0x4e,0x4f,
	0x50,0x51,0x52,0x53,0x54,0x55,0x56,0x57,0x58,0x59,0x5a,0x5b,0x5c,0x5d,0x5e,0x5f,
	0x60,0x41,0x42,0x43,0x44,0x45,0x46,0x47,0x48,0x49,0x4a,0x4b,0x4c,0x4d,0x4e,0x4f,
	0x50,0x51,0x52,0x53,0x54,0x55,0x56,0x57,0x58,0x59,0x5a,0x7b,0x7c,0x7d,0x7e,0x7f,
	-0x80,-0x7f,-0x7e,-0x7d,-0x7c,-0x7b,-0x7a,-0x79,-0x78,-0x77,-0x76,-0x75,-0x74,-0x73,-0x72,-0x71,
	-0x70,-0x6f,-0x6e,-0x6d,-0x6c,-0x6b,-0x6a,-0x69,-0x68,-0x67,-0x66,-0x65,-0x64,-0x63,-0x62,-0x61,
	-0x60,-0x5f,-0x5e,-0x5d,-0x5c,-0x5b,-0x5a,-0x59,-0x58,-0x57,-0x56,-0x55,-0x54,-0x53,-0x52,-0x51,
	-0x50,-0x4f,-0x4e,-0x4d,-0x4c,-0x4b,-0x4a,-0x49,-0x48,-0x47,-0x46,-0x45,-0x44,-0x43,-0x42,-0x41,
	-0x40,-0x3f,-0x3e,-0x3d,-0x3c,-0x3b,-0x3a,-0x39,-0x38,-0x37,-0x36,-0x35,-0x34,-0x33,-0x32,-0x31,
	-0x30,-0x2f,-0x2e,-0x2d,-0x2c,-0x2b,-0x2a,-0x29,-0x28,-0x27,-0x26,-0x25,-0x24,-0x23,-0x22,-0x21,
	-0x20,-0x1f,-0x1e,-0x1d,-0x1c,-0x1b,-0x1a,-0x19,-0x18,-0x17,-0x16,-0x15,-0x14,-0x13,-0x12,-0x11,
	-0x10,-0xf,-0xe,-0xd,-0xc,-0xb,-0xa,-0x9,-0x8,-0x7,-0x6,-0x5,-0x4,-0x3,-0x2,-0x1,
};
}
/*[[[end]]]*/


%(auto_header){
/* For  the  sake  of optimization,  allow  libc auto
 * functions to make direct use of `__ctype_C_flags'. */
#define libc_iscntrl(ch)  __crt_iscntrl(ch)
#define libc_isspace(ch)  __crt_isspace(ch)
#define libc_isupper(ch)  __crt_isupper(ch)
#define libc_islower(ch)  __crt_islower(ch)
#define libc_isalpha(ch)  __crt_isalpha(ch)
#define libc_isdigit(ch)  __crt_isdigit(ch)
#define libc_isxdigit(ch) __crt_isxdigit(ch)
#define libc_isalnum(ch)  __crt_isalnum(ch)
#define libc_ispunct(ch)  __crt_ispunct(ch)
#define libc_isgraph(ch)  __crt_isgraph(ch)
#define libc_isprint(ch)  __crt_isprint(ch)
#define libc_isblank(ch)  __crt_isblank(ch)
#define libc_tolower(ch)  __crt_tolower(ch)
#define libc_toupper(ch)  __crt_toupper(ch)
}


%[insert:prefix(
#include <features.h>
)]%[insert:prefix(
#include <bits/crt/ctype.h>
)]%[insert:prefix(
#ifdef __USE_XOPEN2K8
#include <xlocale.h>
#endif /* __USE_XOPEN2K8 */
)]%[insert:prefix(
#ifdef __USE_GLIBC_BLOAT
#include <endian.h>
#endif /* __USE_GLIBC_BLOAT */
)]%{

#ifdef __USE_DOS
#include <corecrt.h>
#ifndef __USE_DOS_CLEAN
#include <corecrt_wctype.h> /* Include <wchar.h> instead */
#endif /* !__USE_DOS_CLEAN */
#endif /* __USE_DOS */

#ifdef __CC__
__SYSDECL_BEGIN

}

%[default:section(".text.crt{|.dos}.unicode.static.ctype")];

[[ignore, const, wunused, nothrow]]
char const *__locale_ctype_ptr();

[[ignore, pure, wunused]]
[[section(".text.crt{|.dos}.unicode.locale.ctype")]]
char const *__locale_ctype_ptr_l($locale_t locale);

[[ignore, pure, wunused, nothrow]]
[[decl_include("<hybrid/typecore.h>")]]
$uint16_t const **__ctype_b_loc();

[[ignore, pure, wunused, nothrow]]
[[decl_include("<hybrid/typecore.h>")]]
$int32_t const **__ctype_tolower_loc();

[[ignore, pure, wunused, nothrow]]
[[decl_include("<hybrid/typecore.h>")]]
$int32_t const **__ctype_toupper_loc();


%[insert:std]


/*[[[deemon
local TRAITS = {
	"iscntrl", "isspace", "isupper", "islower", "isalpha",
	"isdigit", "isxdigit", "isalnum", "ispunct", "isgraph",
	"isprint", "tolower", "toupper"
};
function printTrait(name) {
	print("@@>> ", name, "(3)");
	print("[[std, libc]]");
	print("[[if($extended_include_prefix(\"<bits/crt/ctype.h>\")defined(__crt_", name, ")), preferred_extern_inline(", repr name, ", { return __crt_", name, "(ch); })]]");
	print("[[if($extended_include_prefix(\"<bits/crt/ctype.h>\")defined(__crt_", name, ")), preferred_inline({ return __crt_", name, "(ch); })]]");
	print("[[crtbuiltin, const, wunused, nothrow, impl_include(\"<bits/crt/ctype.h>\")]]");
	print("int ", name, "(int ch) {");
	print("@@pp_ifdef __crt_", name, "@@");
	print("	return __crt_", name, "(ch);");
	print("@@pp_else@@");
	print("	return __ascii_", name, "(ch);");
	print("@@pp_endif@@");
	print("}");
	print;
}
for (local name: TRAITS)
	printTrait(name);
print("%(c,std)#ifdef __USE_ISOC99");
printTrait("isblank");
print("%(c,std)#endif /" "* __USE_ISOC99 *" "/");
]]]*/
@@>> iscntrl(3)
[[std, libc]]
[[if($extended_include_prefix("<bits/crt/ctype.h>")defined(__crt_iscntrl)), preferred_extern_inline("iscntrl", { return __crt_iscntrl(ch); })]]
[[if($extended_include_prefix("<bits/crt/ctype.h>")defined(__crt_iscntrl)), preferred_inline({ return __crt_iscntrl(ch); })]]
[[crtbuiltin, const, wunused, nothrow, impl_include("<bits/crt/ctype.h>")]]
int iscntrl(int ch) {
@@pp_ifdef __crt_iscntrl@@
	return __crt_iscntrl(ch);
@@pp_else@@
	return __ascii_iscntrl(ch);
@@pp_endif@@
}

@@>> isspace(3)
[[std, libc]]
[[if($extended_include_prefix("<bits/crt/ctype.h>")defined(__crt_isspace)), preferred_extern_inline("isspace", { return __crt_isspace(ch); })]]
[[if($extended_include_prefix("<bits/crt/ctype.h>")defined(__crt_isspace)), preferred_inline({ return __crt_isspace(ch); })]]
[[crtbuiltin, const, wunused, nothrow, impl_include("<bits/crt/ctype.h>")]]
int isspace(int ch) {
@@pp_ifdef __crt_isspace@@
	return __crt_isspace(ch);
@@pp_else@@
	return __ascii_isspace(ch);
@@pp_endif@@
}

@@>> isupper(3)
[[std, libc]]
[[if($extended_include_prefix("<bits/crt/ctype.h>")defined(__crt_isupper)), preferred_extern_inline("isupper", { return __crt_isupper(ch); })]]
[[if($extended_include_prefix("<bits/crt/ctype.h>")defined(__crt_isupper)), preferred_inline({ return __crt_isupper(ch); })]]
[[crtbuiltin, const, wunused, nothrow, impl_include("<bits/crt/ctype.h>")]]
int isupper(int ch) {
@@pp_ifdef __crt_isupper@@
	return __crt_isupper(ch);
@@pp_else@@
	return __ascii_isupper(ch);
@@pp_endif@@
}

@@>> islower(3)
[[std, libc]]
[[if($extended_include_prefix("<bits/crt/ctype.h>")defined(__crt_islower)), preferred_extern_inline("islower", { return __crt_islower(ch); })]]
[[if($extended_include_prefix("<bits/crt/ctype.h>")defined(__crt_islower)), preferred_inline({ return __crt_islower(ch); })]]
[[crtbuiltin, const, wunused, nothrow, impl_include("<bits/crt/ctype.h>")]]
int islower(int ch) {
@@pp_ifdef __crt_islower@@
	return __crt_islower(ch);
@@pp_else@@
	return __ascii_islower(ch);
@@pp_endif@@
}

@@>> isalpha(3)
[[std, libc]]
[[if($extended_include_prefix("<bits/crt/ctype.h>")defined(__crt_isalpha)), preferred_extern_inline("isalpha", { return __crt_isalpha(ch); })]]
[[if($extended_include_prefix("<bits/crt/ctype.h>")defined(__crt_isalpha)), preferred_inline({ return __crt_isalpha(ch); })]]
[[crtbuiltin, const, wunused, nothrow, impl_include("<bits/crt/ctype.h>")]]
int isalpha(int ch) {
@@pp_ifdef __crt_isalpha@@
	return __crt_isalpha(ch);
@@pp_else@@
	return __ascii_isalpha(ch);
@@pp_endif@@
}

@@>> isdigit(3)
[[std, libc]]
[[if($extended_include_prefix("<bits/crt/ctype.h>")defined(__crt_isdigit)), preferred_extern_inline("isdigit", { return __crt_isdigit(ch); })]]
[[if($extended_include_prefix("<bits/crt/ctype.h>")defined(__crt_isdigit)), preferred_inline({ return __crt_isdigit(ch); })]]
[[crtbuiltin, const, wunused, nothrow, impl_include("<bits/crt/ctype.h>")]]
int isdigit(int ch) {
@@pp_ifdef __crt_isdigit@@
	return __crt_isdigit(ch);
@@pp_else@@
	return __ascii_isdigit(ch);
@@pp_endif@@
}

@@>> isxdigit(3)
[[std, libc]]
[[if($extended_include_prefix("<bits/crt/ctype.h>")defined(__crt_isxdigit)), preferred_extern_inline("isxdigit", { return __crt_isxdigit(ch); })]]
[[if($extended_include_prefix("<bits/crt/ctype.h>")defined(__crt_isxdigit)), preferred_inline({ return __crt_isxdigit(ch); })]]
[[crtbuiltin, const, wunused, nothrow, impl_include("<bits/crt/ctype.h>")]]
int isxdigit(int ch) {
@@pp_ifdef __crt_isxdigit@@
	return __crt_isxdigit(ch);
@@pp_else@@
	return __ascii_isxdigit(ch);
@@pp_endif@@
}

@@>> isalnum(3)
[[std, libc]]
[[if($extended_include_prefix("<bits/crt/ctype.h>")defined(__crt_isalnum)), preferred_extern_inline("isalnum", { return __crt_isalnum(ch); })]]
[[if($extended_include_prefix("<bits/crt/ctype.h>")defined(__crt_isalnum)), preferred_inline({ return __crt_isalnum(ch); })]]
[[crtbuiltin, const, wunused, nothrow, impl_include("<bits/crt/ctype.h>")]]
int isalnum(int ch) {
@@pp_ifdef __crt_isalnum@@
	return __crt_isalnum(ch);
@@pp_else@@
	return __ascii_isalnum(ch);
@@pp_endif@@
}

@@>> ispunct(3)
[[std, libc]]
[[if($extended_include_prefix("<bits/crt/ctype.h>")defined(__crt_ispunct)), preferred_extern_inline("ispunct", { return __crt_ispunct(ch); })]]
[[if($extended_include_prefix("<bits/crt/ctype.h>")defined(__crt_ispunct)), preferred_inline({ return __crt_ispunct(ch); })]]
[[crtbuiltin, const, wunused, nothrow, impl_include("<bits/crt/ctype.h>")]]
int ispunct(int ch) {
@@pp_ifdef __crt_ispunct@@
	return __crt_ispunct(ch);
@@pp_else@@
	return __ascii_ispunct(ch);
@@pp_endif@@
}

@@>> isgraph(3)
[[std, libc]]
[[if($extended_include_prefix("<bits/crt/ctype.h>")defined(__crt_isgraph)), preferred_extern_inline("isgraph", { return __crt_isgraph(ch); })]]
[[if($extended_include_prefix("<bits/crt/ctype.h>")defined(__crt_isgraph)), preferred_inline({ return __crt_isgraph(ch); })]]
[[crtbuiltin, const, wunused, nothrow, impl_include("<bits/crt/ctype.h>")]]
int isgraph(int ch) {
@@pp_ifdef __crt_isgraph@@
	return __crt_isgraph(ch);
@@pp_else@@
	return __ascii_isgraph(ch);
@@pp_endif@@
}

@@>> isprint(3)
[[std, libc]]
[[if($extended_include_prefix("<bits/crt/ctype.h>")defined(__crt_isprint)), preferred_extern_inline("isprint", { return __crt_isprint(ch); })]]
[[if($extended_include_prefix("<bits/crt/ctype.h>")defined(__crt_isprint)), preferred_inline({ return __crt_isprint(ch); })]]
[[crtbuiltin, const, wunused, nothrow, impl_include("<bits/crt/ctype.h>")]]
int isprint(int ch) {
@@pp_ifdef __crt_isprint@@
	return __crt_isprint(ch);
@@pp_else@@
	return __ascii_isprint(ch);
@@pp_endif@@
}

@@>> tolower(3)
[[std, libc]]
[[if($extended_include_prefix("<bits/crt/ctype.h>")defined(__crt_tolower)), preferred_extern_inline("tolower", { return __crt_tolower(ch); })]]
[[if($extended_include_prefix("<bits/crt/ctype.h>")defined(__crt_tolower)), preferred_inline({ return __crt_tolower(ch); })]]
[[crtbuiltin, const, wunused, nothrow, impl_include("<bits/crt/ctype.h>")]]
int tolower(int ch) {
@@pp_ifdef __crt_tolower@@
	return __crt_tolower(ch);
@@pp_else@@
	return __ascii_tolower(ch);
@@pp_endif@@
}

@@>> toupper(3)
[[std, libc]]
[[if($extended_include_prefix("<bits/crt/ctype.h>")defined(__crt_toupper)), preferred_extern_inline("toupper", { return __crt_toupper(ch); })]]
[[if($extended_include_prefix("<bits/crt/ctype.h>")defined(__crt_toupper)), preferred_inline({ return __crt_toupper(ch); })]]
[[crtbuiltin, const, wunused, nothrow, impl_include("<bits/crt/ctype.h>")]]
int toupper(int ch) {
@@pp_ifdef __crt_toupper@@
	return __crt_toupper(ch);
@@pp_else@@
	return __ascii_toupper(ch);
@@pp_endif@@
}

%(c,std)#ifdef __USE_ISOC99
@@>> isblank(3)
[[std, libc]]
[[if($extended_include_prefix("<bits/crt/ctype.h>")defined(__crt_isblank)), preferred_extern_inline("isblank", { return __crt_isblank(ch); })]]
[[if($extended_include_prefix("<bits/crt/ctype.h>")defined(__crt_isblank)), preferred_inline({ return __crt_isblank(ch); })]]
[[crtbuiltin, const, wunused, nothrow, impl_include("<bits/crt/ctype.h>")]]
int isblank(int ch) {
@@pp_ifdef __crt_isblank@@
	return __crt_isblank(ch);
@@pp_else@@
	return __ascii_isblank(ch);
@@pp_endif@@
}

%(c,std)#endif /* __USE_ISOC99 */
/*[[[end]]]*/



%
%#ifdef __USE_XOPEN2K8

%[default:section(".text.crt{|.dos}.unicode.locale.ctype")]

/*[[[deemon
local TRAITS = {
	"iscntrl", "isspace", "isupper", "islower", "isalpha",
	"isdigit", "isxdigit", "isalnum", "ispunct", "isgraph",
	"isprint", "isblank", "tolower", "toupper"
};
function printTrait(name) {
	print("@@>> ", name, "_l(3)");
	print("[[if($extended_include_prefix(\"<bits/crt/ctype.h>\")defined(__crt_", name, "_l)), preferred_extern_inline(\"", name, "_l\", { return __crt_", name, "_l(ch, locale); })]]");
	print("[[if($extended_include_prefix(\"<bits/crt/ctype.h>\")defined(__crt_", name, "_l)), preferred_extern_inline(\"_", name, "_l\", { return __crt_", name, "_l(ch, locale); })]]");
	print("[[if($extended_include_prefix(\"<bits/crt/ctype.h>\")defined(__crt_", name, "_l)), preferred_extern_inline(\"__", name, "_l\", { return __crt_", name, "_l(ch, locale); })]]");
	print("[[if($extended_include_prefix(\"<bits/crt/ctype.h>\")defined(__crt_", name, "_l)), preferred_inline({ return __crt_", name, "_l(ch, locale); })]]");
	print("[[pure, wunused, dos_only_export_alias(\"_", name, "_l\"), export_alias(\"__", name, "_l\")]]");
	print("[[if(defined(__LIBKCALL_CALLER_CLEANUP)), crt_intern_kos_alias(\"libc_", name, "\")]]");
	print("[[if(defined(__LIBDCALL_CALLER_CLEANUP)), crt_intern_dos_alias(\"libd_", name, "\")]]");
	print("int ", name, "_l(int ch, $locale_t locale) {");
	print("	COMPILER_IMPURE();");
	print("	(void)locale;");
	print("	return ", name, "(ch);");
	print("}");
}
for (local name: TRAITS)
	printTrait(name);
]]]*/
@@>> iscntrl_l(3)
[[if($extended_include_prefix("<bits/crt/ctype.h>")defined(__crt_iscntrl_l)), preferred_extern_inline("iscntrl_l", { return __crt_iscntrl_l(ch, locale); })]]
[[if($extended_include_prefix("<bits/crt/ctype.h>")defined(__crt_iscntrl_l)), preferred_extern_inline("_iscntrl_l", { return __crt_iscntrl_l(ch, locale); })]]
[[if($extended_include_prefix("<bits/crt/ctype.h>")defined(__crt_iscntrl_l)), preferred_extern_inline("__iscntrl_l", { return __crt_iscntrl_l(ch, locale); })]]
[[if($extended_include_prefix("<bits/crt/ctype.h>")defined(__crt_iscntrl_l)), preferred_inline({ return __crt_iscntrl_l(ch, locale); })]]
[[pure, wunused, dos_only_export_alias("_iscntrl_l"), export_alias("__iscntrl_l")]]
[[if(defined(__LIBKCALL_CALLER_CLEANUP)), crt_intern_kos_alias("libc_iscntrl")]]
[[if(defined(__LIBDCALL_CALLER_CLEANUP)), crt_intern_dos_alias("libd_iscntrl")]]
int iscntrl_l(int ch, $locale_t locale) {
	COMPILER_IMPURE();
	(void)locale;
	return iscntrl(ch);
}
@@>> isspace_l(3)
[[if($extended_include_prefix("<bits/crt/ctype.h>")defined(__crt_isspace_l)), preferred_extern_inline("isspace_l", { return __crt_isspace_l(ch, locale); })]]
[[if($extended_include_prefix("<bits/crt/ctype.h>")defined(__crt_isspace_l)), preferred_extern_inline("_isspace_l", { return __crt_isspace_l(ch, locale); })]]
[[if($extended_include_prefix("<bits/crt/ctype.h>")defined(__crt_isspace_l)), preferred_extern_inline("__isspace_l", { return __crt_isspace_l(ch, locale); })]]
[[if($extended_include_prefix("<bits/crt/ctype.h>")defined(__crt_isspace_l)), preferred_inline({ return __crt_isspace_l(ch, locale); })]]
[[pure, wunused, dos_only_export_alias("_isspace_l"), export_alias("__isspace_l")]]
[[if(defined(__LIBKCALL_CALLER_CLEANUP)), crt_intern_kos_alias("libc_isspace")]]
[[if(defined(__LIBDCALL_CALLER_CLEANUP)), crt_intern_dos_alias("libd_isspace")]]
int isspace_l(int ch, $locale_t locale) {
	COMPILER_IMPURE();
	(void)locale;
	return isspace(ch);
}
@@>> isupper_l(3)
[[if($extended_include_prefix("<bits/crt/ctype.h>")defined(__crt_isupper_l)), preferred_extern_inline("isupper_l", { return __crt_isupper_l(ch, locale); })]]
[[if($extended_include_prefix("<bits/crt/ctype.h>")defined(__crt_isupper_l)), preferred_extern_inline("_isupper_l", { return __crt_isupper_l(ch, locale); })]]
[[if($extended_include_prefix("<bits/crt/ctype.h>")defined(__crt_isupper_l)), preferred_extern_inline("__isupper_l", { return __crt_isupper_l(ch, locale); })]]
[[if($extended_include_prefix("<bits/crt/ctype.h>")defined(__crt_isupper_l)), preferred_inline({ return __crt_isupper_l(ch, locale); })]]
[[pure, wunused, dos_only_export_alias("_isupper_l"), export_alias("__isupper_l")]]
[[if(defined(__LIBKCALL_CALLER_CLEANUP)), crt_intern_kos_alias("libc_isupper")]]
[[if(defined(__LIBDCALL_CALLER_CLEANUP)), crt_intern_dos_alias("libd_isupper")]]
int isupper_l(int ch, $locale_t locale) {
	COMPILER_IMPURE();
	(void)locale;
	return isupper(ch);
}
@@>> islower_l(3)
[[if($extended_include_prefix("<bits/crt/ctype.h>")defined(__crt_islower_l)), preferred_extern_inline("islower_l", { return __crt_islower_l(ch, locale); })]]
[[if($extended_include_prefix("<bits/crt/ctype.h>")defined(__crt_islower_l)), preferred_extern_inline("_islower_l", { return __crt_islower_l(ch, locale); })]]
[[if($extended_include_prefix("<bits/crt/ctype.h>")defined(__crt_islower_l)), preferred_extern_inline("__islower_l", { return __crt_islower_l(ch, locale); })]]
[[if($extended_include_prefix("<bits/crt/ctype.h>")defined(__crt_islower_l)), preferred_inline({ return __crt_islower_l(ch, locale); })]]
[[pure, wunused, dos_only_export_alias("_islower_l"), export_alias("__islower_l")]]
[[if(defined(__LIBKCALL_CALLER_CLEANUP)), crt_intern_kos_alias("libc_islower")]]
[[if(defined(__LIBDCALL_CALLER_CLEANUP)), crt_intern_dos_alias("libd_islower")]]
int islower_l(int ch, $locale_t locale) {
	COMPILER_IMPURE();
	(void)locale;
	return islower(ch);
}
@@>> isalpha_l(3)
[[if($extended_include_prefix("<bits/crt/ctype.h>")defined(__crt_isalpha_l)), preferred_extern_inline("isalpha_l", { return __crt_isalpha_l(ch, locale); })]]
[[if($extended_include_prefix("<bits/crt/ctype.h>")defined(__crt_isalpha_l)), preferred_extern_inline("_isalpha_l", { return __crt_isalpha_l(ch, locale); })]]
[[if($extended_include_prefix("<bits/crt/ctype.h>")defined(__crt_isalpha_l)), preferred_extern_inline("__isalpha_l", { return __crt_isalpha_l(ch, locale); })]]
[[if($extended_include_prefix("<bits/crt/ctype.h>")defined(__crt_isalpha_l)), preferred_inline({ return __crt_isalpha_l(ch, locale); })]]
[[pure, wunused, dos_only_export_alias("_isalpha_l"), export_alias("__isalpha_l")]]
[[if(defined(__LIBKCALL_CALLER_CLEANUP)), crt_intern_kos_alias("libc_isalpha")]]
[[if(defined(__LIBDCALL_CALLER_CLEANUP)), crt_intern_dos_alias("libd_isalpha")]]
int isalpha_l(int ch, $locale_t locale) {
	COMPILER_IMPURE();
	(void)locale;
	return isalpha(ch);
}
@@>> isdigit_l(3)
[[if($extended_include_prefix("<bits/crt/ctype.h>")defined(__crt_isdigit_l)), preferred_extern_inline("isdigit_l", { return __crt_isdigit_l(ch, locale); })]]
[[if($extended_include_prefix("<bits/crt/ctype.h>")defined(__crt_isdigit_l)), preferred_extern_inline("_isdigit_l", { return __crt_isdigit_l(ch, locale); })]]
[[if($extended_include_prefix("<bits/crt/ctype.h>")defined(__crt_isdigit_l)), preferred_extern_inline("__isdigit_l", { return __crt_isdigit_l(ch, locale); })]]
[[if($extended_include_prefix("<bits/crt/ctype.h>")defined(__crt_isdigit_l)), preferred_inline({ return __crt_isdigit_l(ch, locale); })]]
[[pure, wunused, dos_only_export_alias("_isdigit_l"), export_alias("__isdigit_l")]]
[[if(defined(__LIBKCALL_CALLER_CLEANUP)), crt_intern_kos_alias("libc_isdigit")]]
[[if(defined(__LIBDCALL_CALLER_CLEANUP)), crt_intern_dos_alias("libd_isdigit")]]
int isdigit_l(int ch, $locale_t locale) {
	COMPILER_IMPURE();
	(void)locale;
	return isdigit(ch);
}
@@>> isxdigit_l(3)
[[if($extended_include_prefix("<bits/crt/ctype.h>")defined(__crt_isxdigit_l)), preferred_extern_inline("isxdigit_l", { return __crt_isxdigit_l(ch, locale); })]]
[[if($extended_include_prefix("<bits/crt/ctype.h>")defined(__crt_isxdigit_l)), preferred_extern_inline("_isxdigit_l", { return __crt_isxdigit_l(ch, locale); })]]
[[if($extended_include_prefix("<bits/crt/ctype.h>")defined(__crt_isxdigit_l)), preferred_extern_inline("__isxdigit_l", { return __crt_isxdigit_l(ch, locale); })]]
[[if($extended_include_prefix("<bits/crt/ctype.h>")defined(__crt_isxdigit_l)), preferred_inline({ return __crt_isxdigit_l(ch, locale); })]]
[[pure, wunused, dos_only_export_alias("_isxdigit_l"), export_alias("__isxdigit_l")]]
[[if(defined(__LIBKCALL_CALLER_CLEANUP)), crt_intern_kos_alias("libc_isxdigit")]]
[[if(defined(__LIBDCALL_CALLER_CLEANUP)), crt_intern_dos_alias("libd_isxdigit")]]
int isxdigit_l(int ch, $locale_t locale) {
	COMPILER_IMPURE();
	(void)locale;
	return isxdigit(ch);
}
@@>> isalnum_l(3)
[[if($extended_include_prefix("<bits/crt/ctype.h>")defined(__crt_isalnum_l)), preferred_extern_inline("isalnum_l", { return __crt_isalnum_l(ch, locale); })]]
[[if($extended_include_prefix("<bits/crt/ctype.h>")defined(__crt_isalnum_l)), preferred_extern_inline("_isalnum_l", { return __crt_isalnum_l(ch, locale); })]]
[[if($extended_include_prefix("<bits/crt/ctype.h>")defined(__crt_isalnum_l)), preferred_extern_inline("__isalnum_l", { return __crt_isalnum_l(ch, locale); })]]
[[if($extended_include_prefix("<bits/crt/ctype.h>")defined(__crt_isalnum_l)), preferred_inline({ return __crt_isalnum_l(ch, locale); })]]
[[pure, wunused, dos_only_export_alias("_isalnum_l"), export_alias("__isalnum_l")]]
[[if(defined(__LIBKCALL_CALLER_CLEANUP)), crt_intern_kos_alias("libc_isalnum")]]
[[if(defined(__LIBDCALL_CALLER_CLEANUP)), crt_intern_dos_alias("libd_isalnum")]]
int isalnum_l(int ch, $locale_t locale) {
	COMPILER_IMPURE();
	(void)locale;
	return isalnum(ch);
}
@@>> ispunct_l(3)
[[if($extended_include_prefix("<bits/crt/ctype.h>")defined(__crt_ispunct_l)), preferred_extern_inline("ispunct_l", { return __crt_ispunct_l(ch, locale); })]]
[[if($extended_include_prefix("<bits/crt/ctype.h>")defined(__crt_ispunct_l)), preferred_extern_inline("_ispunct_l", { return __crt_ispunct_l(ch, locale); })]]
[[if($extended_include_prefix("<bits/crt/ctype.h>")defined(__crt_ispunct_l)), preferred_extern_inline("__ispunct_l", { return __crt_ispunct_l(ch, locale); })]]
[[if($extended_include_prefix("<bits/crt/ctype.h>")defined(__crt_ispunct_l)), preferred_inline({ return __crt_ispunct_l(ch, locale); })]]
[[pure, wunused, dos_only_export_alias("_ispunct_l"), export_alias("__ispunct_l")]]
[[if(defined(__LIBKCALL_CALLER_CLEANUP)), crt_intern_kos_alias("libc_ispunct")]]
[[if(defined(__LIBDCALL_CALLER_CLEANUP)), crt_intern_dos_alias("libd_ispunct")]]
int ispunct_l(int ch, $locale_t locale) {
	COMPILER_IMPURE();
	(void)locale;
	return ispunct(ch);
}
@@>> isgraph_l(3)
[[if($extended_include_prefix("<bits/crt/ctype.h>")defined(__crt_isgraph_l)), preferred_extern_inline("isgraph_l", { return __crt_isgraph_l(ch, locale); })]]
[[if($extended_include_prefix("<bits/crt/ctype.h>")defined(__crt_isgraph_l)), preferred_extern_inline("_isgraph_l", { return __crt_isgraph_l(ch, locale); })]]
[[if($extended_include_prefix("<bits/crt/ctype.h>")defined(__crt_isgraph_l)), preferred_extern_inline("__isgraph_l", { return __crt_isgraph_l(ch, locale); })]]
[[if($extended_include_prefix("<bits/crt/ctype.h>")defined(__crt_isgraph_l)), preferred_inline({ return __crt_isgraph_l(ch, locale); })]]
[[pure, wunused, dos_only_export_alias("_isgraph_l"), export_alias("__isgraph_l")]]
[[if(defined(__LIBKCALL_CALLER_CLEANUP)), crt_intern_kos_alias("libc_isgraph")]]
[[if(defined(__LIBDCALL_CALLER_CLEANUP)), crt_intern_dos_alias("libd_isgraph")]]
int isgraph_l(int ch, $locale_t locale) {
	COMPILER_IMPURE();
	(void)locale;
	return isgraph(ch);
}
@@>> isprint_l(3)
[[if($extended_include_prefix("<bits/crt/ctype.h>")defined(__crt_isprint_l)), preferred_extern_inline("isprint_l", { return __crt_isprint_l(ch, locale); })]]
[[if($extended_include_prefix("<bits/crt/ctype.h>")defined(__crt_isprint_l)), preferred_extern_inline("_isprint_l", { return __crt_isprint_l(ch, locale); })]]
[[if($extended_include_prefix("<bits/crt/ctype.h>")defined(__crt_isprint_l)), preferred_extern_inline("__isprint_l", { return __crt_isprint_l(ch, locale); })]]
[[if($extended_include_prefix("<bits/crt/ctype.h>")defined(__crt_isprint_l)), preferred_inline({ return __crt_isprint_l(ch, locale); })]]
[[pure, wunused, dos_only_export_alias("_isprint_l"), export_alias("__isprint_l")]]
[[if(defined(__LIBKCALL_CALLER_CLEANUP)), crt_intern_kos_alias("libc_isprint")]]
[[if(defined(__LIBDCALL_CALLER_CLEANUP)), crt_intern_dos_alias("libd_isprint")]]
int isprint_l(int ch, $locale_t locale) {
	COMPILER_IMPURE();
	(void)locale;
	return isprint(ch);
}
@@>> isblank_l(3)
[[if($extended_include_prefix("<bits/crt/ctype.h>")defined(__crt_isblank_l)), preferred_extern_inline("isblank_l", { return __crt_isblank_l(ch, locale); })]]
[[if($extended_include_prefix("<bits/crt/ctype.h>")defined(__crt_isblank_l)), preferred_extern_inline("_isblank_l", { return __crt_isblank_l(ch, locale); })]]
[[if($extended_include_prefix("<bits/crt/ctype.h>")defined(__crt_isblank_l)), preferred_extern_inline("__isblank_l", { return __crt_isblank_l(ch, locale); })]]
[[if($extended_include_prefix("<bits/crt/ctype.h>")defined(__crt_isblank_l)), preferred_inline({ return __crt_isblank_l(ch, locale); })]]
[[pure, wunused, dos_only_export_alias("_isblank_l"), export_alias("__isblank_l")]]
[[if(defined(__LIBKCALL_CALLER_CLEANUP)), crt_intern_kos_alias("libc_isblank")]]
[[if(defined(__LIBDCALL_CALLER_CLEANUP)), crt_intern_dos_alias("libd_isblank")]]
int isblank_l(int ch, $locale_t locale) {
	COMPILER_IMPURE();
	(void)locale;
	return isblank(ch);
}
@@>> tolower_l(3)
[[if($extended_include_prefix("<bits/crt/ctype.h>")defined(__crt_tolower_l)), preferred_extern_inline("tolower_l", { return __crt_tolower_l(ch, locale); })]]
[[if($extended_include_prefix("<bits/crt/ctype.h>")defined(__crt_tolower_l)), preferred_extern_inline("_tolower_l", { return __crt_tolower_l(ch, locale); })]]
[[if($extended_include_prefix("<bits/crt/ctype.h>")defined(__crt_tolower_l)), preferred_extern_inline("__tolower_l", { return __crt_tolower_l(ch, locale); })]]
[[if($extended_include_prefix("<bits/crt/ctype.h>")defined(__crt_tolower_l)), preferred_inline({ return __crt_tolower_l(ch, locale); })]]
[[pure, wunused, dos_only_export_alias("_tolower_l"), export_alias("__tolower_l")]]
[[if(defined(__LIBKCALL_CALLER_CLEANUP)), crt_intern_kos_alias("libc_tolower")]]
[[if(defined(__LIBDCALL_CALLER_CLEANUP)), crt_intern_dos_alias("libd_tolower")]]
int tolower_l(int ch, $locale_t locale) {
	COMPILER_IMPURE();
	(void)locale;
	return tolower(ch);
}
@@>> toupper_l(3)
[[if($extended_include_prefix("<bits/crt/ctype.h>")defined(__crt_toupper_l)), preferred_extern_inline("toupper_l", { return __crt_toupper_l(ch, locale); })]]
[[if($extended_include_prefix("<bits/crt/ctype.h>")defined(__crt_toupper_l)), preferred_extern_inline("_toupper_l", { return __crt_toupper_l(ch, locale); })]]
[[if($extended_include_prefix("<bits/crt/ctype.h>")defined(__crt_toupper_l)), preferred_extern_inline("__toupper_l", { return __crt_toupper_l(ch, locale); })]]
[[if($extended_include_prefix("<bits/crt/ctype.h>")defined(__crt_toupper_l)), preferred_inline({ return __crt_toupper_l(ch, locale); })]]
[[pure, wunused, dos_only_export_alias("_toupper_l"), export_alias("__toupper_l")]]
[[if(defined(__LIBKCALL_CALLER_CLEANUP)), crt_intern_kos_alias("libc_toupper")]]
[[if(defined(__LIBDCALL_CALLER_CLEANUP)), crt_intern_dos_alias("libd_toupper")]]
int toupper_l(int ch, $locale_t locale) {
	COMPILER_IMPURE();
	(void)locale;
	return toupper(ch);
}
/*[[[end]]]*/


%#endif /* __USE_XOPEN2K8 */


%{

#if (!defined(__cplusplus) || defined(__USE_CTYPE_MACROS)) && !defined(__CXX_SYSTEM_HEADER)

#ifdef __USE_XOPEN2K8
#ifdef __crt_isalnum_l
#define isalnum_l(ch, locale) __crt_isalnum_l(ch, locale)
#endif /* __crt_isalnum_l */
#ifdef __crt_isalpha_l
#define isalpha_l(ch, locale) __crt_isalpha_l(ch, locale)
#endif /* __crt_isalpha_l */
#ifdef __crt_isupper_l
#define isupper_l(ch, locale) __crt_isupper_l(ch, locale)
#endif /* __crt_isupper_l */
#ifdef __crt_islower_l
#define islower_l(ch, locale) __crt_islower_l(ch, locale)
#endif /* __crt_islower_l */
#ifdef __crt_isdigit_l
#define isdigit_l(ch, locale) __crt_isdigit_l(ch, locale)
#endif /* __crt_isdigit_l */
#ifdef __crt_isxdigit_l
#define isxdigit_l(ch, locale) __crt_isxdigit_l(ch, locale)
#endif /* __crt_isxdigit_l */
#ifdef __crt_isspace_l
#define isspace_l(ch, locale) __crt_isspace_l(ch, locale)
#endif /* __crt_isspace_l */
#ifdef __crt_ispunct_l
#define ispunct_l(ch, locale) __crt_ispunct_l(ch, locale)
#endif /* __crt_ispunct_l */
#ifdef __crt_isprint_l
#define isprint_l(ch, locale) __crt_isprint_l(ch, locale)
#endif /* __crt_isprint_l */
#ifdef __crt_isgraph_l
#define isgraph_l(ch, locale) __crt_isgraph_l(ch, locale)
#endif /* __crt_isgraph_l */
#ifdef __crt_iscntrl_l
#define iscntrl_l(ch, locale) __crt_iscntrl_l(ch, locale)
#endif /* __crt_iscntrl_l */
#ifdef __crt_isblank_l
#define isblank_l(ch, locale) __crt_isblank_l(ch, locale)
#endif /* __crt_isblank_l */
#ifdef __crt_tolower_l
#define tolower_l(ch, locale) __crt_tolower_l(ch, locale)
#endif /* __crt_tolower_l */
#ifdef __crt_toupper_l
#define toupper_l(ch, locale) __crt_toupper_l(ch, locale)
#endif /* __crt_toupper_l */
#endif /* __USE_XOPEN2K8 */

#ifndef __NO_builtin_constant_p
#ifndef __NO_builtin_choose_expr
#ifdef __crt_isalnum
#define isalnum(ch) __builtin_choose_expr(__builtin_constant_p(ch), __ascii_isalnum(ch), __crt_isalnum(ch))
#endif /* __crt_isalnum */
#ifdef __crt_isalpha
#define isalpha(ch) __builtin_choose_expr(__builtin_constant_p(ch), __ascii_isalpha(ch), __crt_isalpha(ch))
#endif /* __crt_isalpha */
#ifdef __crt_isupper
#define isupper(ch) __builtin_choose_expr(__builtin_constant_p(ch), __ascii_isupper(ch), __crt_isupper(ch))
#endif /* __crt_isupper */
#ifdef __crt_islower
#define islower(ch) __builtin_choose_expr(__builtin_constant_p(ch), __ascii_islower(ch), __crt_islower(ch))
#endif /* __crt_islower */
#ifdef __crt_isdigit
#define isdigit(ch) __builtin_choose_expr(__builtin_constant_p(ch), __ascii_isdigit(ch), __crt_isdigit(ch))
#endif /* __crt_isdigit */
#ifdef __crt_isxdigit
#define isxdigit(ch) __builtin_choose_expr(__builtin_constant_p(ch), __ascii_isxdigit(ch), __crt_isxdigit(ch))
#endif /* __crt_isxdigit */
#ifdef __crt_isspace
#define isspace(ch) __builtin_choose_expr(__builtin_constant_p(ch), __ascii_isspace(ch), __crt_isspace(ch))
#endif /* __crt_isspace */
#ifdef __crt_ispunct
#define ispunct(ch) __builtin_choose_expr(__builtin_constant_p(ch), __ascii_ispunct(ch), __crt_ispunct(ch))
#endif /* __crt_ispunct */
#ifdef __crt_isprint
#define isprint(ch) __builtin_choose_expr(__builtin_constant_p(ch), __ascii_isprint(ch), __crt_isprint(ch))
#endif /* __crt_isprint */
#ifdef __crt_isgraph
#define isgraph(ch) __builtin_choose_expr(__builtin_constant_p(ch), __ascii_isgraph(ch), __crt_isgraph(ch))
#endif /* __crt_isgraph */
#ifdef __crt_iscntrl
#define iscntrl(ch) __builtin_choose_expr(__builtin_constant_p(ch), __ascii_iscntrl(ch), __crt_iscntrl(ch))
#endif /* __crt_iscntrl */
#if defined(__USE_ISOC99) && defined(__crt_isblank)
#define isblank(ch) __builtin_choose_expr(__builtin_constant_p(ch), __ascii_isblank(ch), __crt_isblank(ch))
#endif /* __USE_ISOC99 && __crt_isblank */
#ifdef __crt_tolower
#define tolower(ch) __builtin_choose_expr(__builtin_constant_p(ch), __ascii_tolower(ch), __crt_tolower(ch))
#endif /* __crt_tolower */
#ifdef __crt_toupper
#define toupper(ch) __builtin_choose_expr(__builtin_constant_p(ch), __ascii_toupper(ch), __crt_toupper(ch))
#endif /* __crt_toupper */
#else /* !__NO_builtin_choose_expr */
#ifdef __crt_isalnum
#define isalnum(ch) (__builtin_constant_p(ch) ? __ascii_isalnum(ch) : __crt_isalnum(ch))
#endif /* __crt_isalnum */
#ifdef __crt_isalpha
#define isalpha(ch) (__builtin_constant_p(ch) ? __ascii_isalpha(ch) : __crt_isalpha(ch))
#endif /* __crt_isalpha */
#ifdef __crt_isupper
#define isupper(ch) (__builtin_constant_p(ch) ? __ascii_isupper(ch) : __crt_isupper(ch))
#endif /* __crt_isupper */
#ifdef __crt_islower
#define islower(ch) (__builtin_constant_p(ch) ? __ascii_islower(ch) : __crt_islower(ch))
#endif /* __crt_islower */
#ifdef __crt_isdigit
#define isdigit(ch) (__builtin_constant_p(ch) ? __ascii_isdigit(ch) : __crt_isdigit(ch))
#endif /* __crt_isdigit */
#ifdef __crt_isxdigit
#define isxdigit(ch) (__builtin_constant_p(ch) ? __ascii_isxdigit(ch) : __crt_isxdigit(ch))
#endif /* __crt_isxdigit */
#ifdef __crt_isspace
#define isspace(ch) (__builtin_constant_p(ch) ? __ascii_isspace(ch) : __crt_isspace(ch))
#endif /* __crt_isspace */
#ifdef __crt_ispunct
#define ispunct(ch) (__builtin_constant_p(ch) ? __ascii_ispunct(ch) : __crt_ispunct(ch))
#endif /* __crt_ispunct */
#ifdef __crt_isprint
#define isprint(ch) (__builtin_constant_p(ch) ? __ascii_isprint(ch) : __crt_isprint(ch))
#endif /* __crt_isprint */
#ifdef __crt_isgraph
#define isgraph(ch) (__builtin_constant_p(ch) ? __ascii_isgraph(ch) : __crt_isgraph(ch))
#endif /* __crt_isgraph */
#ifdef __crt_iscntrl
#define iscntrl(ch) (__builtin_constant_p(ch) ? __ascii_iscntrl(ch) : __crt_iscntrl(ch))
#endif /* __crt_iscntrl */
#if defined(__USE_ISOC99) && defined(__crt_isblank)
#define isblank(ch) (__builtin_constant_p(ch) ? __ascii_isblank(ch) : __crt_isblank(ch))
#endif /* __USE_ISOC99 && __crt_isblank */
#ifdef __crt_tolower
#define tolower(ch) (__builtin_constant_p(ch) ? __ascii_tolower(ch) : __crt_tolower(ch))
#endif /* __crt_tolower */
#ifdef __crt_toupper
#define toupper(ch) (__builtin_constant_p(ch) ? __ascii_toupper(ch) : __crt_toupper(ch))
#endif /* __crt_toupper */
#endif /* __NO_builtin_choose_expr */
#else /* !__NO_builtin_constant_p */
#ifdef __crt_isalnum
#define isalnum(ch) __crt_isalnum(ch)
#endif /* __crt_isalnum */
#ifdef __crt_isalpha
#define isalpha(ch) __crt_isalpha(ch)
#endif /* __crt_isalpha */
#ifdef __crt_isupper
#define isupper(ch) __crt_isupper(ch)
#endif /* __crt_isupper */
#ifdef __crt_islower
#define islower(ch) __crt_islower(ch)
#endif /* __crt_islower */
#ifdef __crt_isdigit
#define isdigit(ch) __crt_isdigit(ch)
#endif /* __crt_isdigit */
#ifdef __crt_isxdigit
#define isxdigit(ch) __crt_isxdigit(ch)
#endif /* __crt_isxdigit */
#ifdef __crt_isspace
#define isspace(ch) __crt_isspace(ch)
#endif /* __crt_isspace */
#ifdef __crt_ispunct
#define ispunct(ch) __crt_ispunct(ch)
#endif /* __crt_ispunct */
#ifdef __crt_isprint
#define isprint(ch) __crt_isprint(ch)
#endif /* __crt_isprint */
#ifdef __crt_isgraph
#define isgraph(ch) __crt_isgraph(ch)
#endif /* __crt_isgraph */
#ifdef __crt_iscntrl
#define iscntrl(ch) __crt_iscntrl(ch)
#endif /* __crt_iscntrl */
#if defined(__USE_ISOC99) && defined(__crt_isblank)
#define isblank(ch) __crt_isblank(ch)
#endif /* __USE_ISOC99 && __crt_isblank */
#ifdef __crt_tolower
#define tolower(ch) __crt_tolower(ch)
#endif /* __crt_tolower */
#ifdef __crt_toupper
#define toupper(ch) __crt_toupper(ch)
#endif /* __crt_toupper */
#endif /* __NO_builtin_constant_p */

#endif /* (!__cplusplus || __USE_CTYPE_MACROS) && !__CXX_SYSTEM_HEADER */
}

%
%#ifdef __USE_KOS
%[default:section(".text.crt.dos.unicode.static.ctype")];

@@>> issymstrt(3)
@@Test if `ch' can appear at the start of a symbol/keyword/identifier
[[const, wunused, decl_include("<hybrid/typecore.h>"), crt_name("__iscsymf")]]
int issymstrt(int ch) {
	return isalpha(ch) || ch == '_' || ch == '$';
}

@@>> issymcont(3)
@@Test if `ch' can appear in the middle of a symbol/keyword/identifier
[[const, wunused, decl_include("<hybrid/typecore.h>"), crt_name("__iscsym")]]
int issymcont(int ch) {
	return isalnum(ch) || ch == '_' || ch == '$';
}
%#endif /* __USE_KOS */

%
%#if defined(__USE_MISC) || defined(__USE_XOPEN)
%[default:section(".text.crt{|.dos}.unicode.static.ctype")];

@@Returns non-zero if `(C & ~0x7f) == 0'
[[const, nothrow, inline, dos_only_export_alias("__isascii")]]
int isascii(int c) {
	return (c & ~0x7f) == 0;
}

@@Re-returns `C & 0x7f'
[[const, nothrow, inline, dos_only_export_alias("__toascii")]]
int toascii(int c) {
	return c & 0x7f;
}

%{
#if (!defined(__cplusplus) || defined(__USE_CTYPE_MACROS)) && !defined(__CXX_SYSTEM_HEADER)
#define isascii(c) (((c) & ~0x7f) == 0)
#define toascii(c) ((c) & 0x7f)
#endif /* (!__cplusplus || __USE_CTYPE_MACROS) && !__CXX_SYSTEM_HEADER */
}
%#endif /* __USE_MISC || __USE_XOPEN */


%
%#if defined(__USE_MISC) || defined(__USE_XOPEN) || defined(__USE_DOS)
@@>> _tolower(3)
@@Same as `tolower(3)', but the caller must ensure that `isupper(ch)'
[[const, wunused, nothrow, inline]]
int _tolower(int ch) {
	return ch + 0x20;
}

@@>> _toupper(3)
@@Same as `toupper(3)', but the caller must ensure that `islower(ch)'
[[const, wunused, nothrow, inline]]
int _toupper(int ch) {
	return ch - 0x20;
}
%#endif /* __USE_MISC || __USE_XOPEN || __USE_DOS */


%
%#ifdef __USE_DOS
%[default:section(".text.crt.dos.unicode.static.ctype")];

%[define(_UPPER    = 0x0001)]
%[define(_LOWER    = 0x0002)]
%[define(_DIGIT    = 0x0004)]
%[define(_SPACE    = 0x0008)]
%[define(_PUNCT    = 0x0010)]
%[define(_CONTROL  = 0x0020)]
%[define(_BLANK    = 0x0040)]
%[define(_HEX      = 0x0080)]
%[define(_LEADBYTE = 0x8000)]
%[define(_ALPHA    = 0x0103)]


%{
/* Possible values for `mask' argument of `_isctype(3)' */
#ifndef _UPPER
#define _UPPER    0x0001 /* isupper() */
#define _LOWER    0x0002 /* islower() */
#define _DIGIT    0x0004 /* isdigit() */
#define _SPACE    0x0008 /* isspace() */
#define _PUNCT    0x0010 /* ispunct() */
#define _CONTROL  0x0020 /* iscntrl() */
#define _BLANK    0x0040 /* isblank() */
#define _HEX      0x0080 /* isxdigit() - isdigit() */
#define _LEADBYTE 0x8000 /* Leading byte of multi-byte sequence */
#define _ALPHA    0x0103 /* isalpha() -- (0x0100 | _UPPER | _LOWER) */
#endif /* !_UPPER */


#ifndef MB_CUR_MAX
#ifdef __LOCAL_MB_CUR_MAX
#define MB_CUR_MAX __LOCAL_MB_CUR_MAX
#elif defined(__mb_cur_max)
#define MB_CUR_MAX ((__SIZE_TYPE__)__mb_cur_max)
#elif defined(__ctype_get_mb_cur_max) || defined(____ctype_get_mb_cur_max_defined)
#define MB_CUR_MAX __ctype_get_mb_cur_max()
#elif defined(___mb_cur_max_func) || defined(_____mb_cur_max_func_defined)
#define MB_CUR_MAX ((__SIZE_TYPE__)___mb_cur_max_func())
#elif defined(__p___mb_cur_max) || defined(____p___mb_cur_max_defined)
#define MB_CUR_MAX ((__SIZE_TYPE__)*__p___mb_cur_max())
#elif defined(__CRT_HAVE___ctype_get_mb_cur_max)
#define ____ctype_get_mb_cur_max_defined
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__SIZE_TYPE__,__NOTHROW,__ctype_get_mb_cur_max,(void),())
#define MB_CUR_MAX __ctype_get_mb_cur_max()
#elif defined(__CRT_HAVE____mb_cur_max_func)
#define _____mb_cur_max_func_defined
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,___mb_cur_max_func,(void),())
#define MB_CUR_MAX ((__SIZE_TYPE__)___mb_cur_max_func())
#elif defined(__CRT_HAVE___p___mb_cur_max)
#define ____p___mb_cur_max_defined
__CDECLARE(__ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED,int *,__NOTHROW,__p___mb_cur_max,(void),())
#define MB_CUR_MAX ((__SIZE_TYPE__)*__p___mb_cur_max())
#elif defined(__CRT_HAVE___mb_cur_max)
__CSDECLARE(,int,__mb_cur_max)
#define __mb_cur_max __mb_cur_max
#define MB_CUR_MAX   ((__SIZE_TYPE__)__mb_cur_max)
#else /* __CRT_HAVE___ctype_get_mb_cur_max */
#define MB_CUR_MAX 7 /* == UNICODE_UTF8_CURLEN */
#endif /* !__CRT_HAVE___ctype_get_mb_cur_max */
#endif /* !MB_CUR_MAX */
}

[[hidden, const, wunused]]
[[decl_include("<hybrid/typecore.h>")]]
[[impl_include("<libc/template/MB_CUR_MAX.h>")]]
[[export_alias("___mb_cur_max_func")]]
[[section(".text.crt{|.dos}.unicode.static.ctype")]]
$size_t __ctype_get_mb_cur_max(void) {
	return __LOCAL_MB_CUR_MAX;
}

[[guard, const, wunused]]
int ___mb_cur_max_func(void) = __ctype_get_mb_cur_max;

[[impl_include("<libc/template/MB_CUR_MAX.h>")]]
[[if(defined(__LIBKCALL_CALLER_CLEANUP)), crt_intern_kos_alias("libc___ctype_get_mb_cur_max")]]
[[if(defined(__LIBDCALL_CALLER_CLEANUP)), crt_intern_dos_alias("libd___ctype_get_mb_cur_max")]]
int ___mb_cur_max_l_func($locale_t locale) {
	(void)locale;
	return __LOCAL_MB_CUR_MAX;
}

[[nocrt, const, wunused, nothrow]]
[[alias("_chvalidator", "_isctype")]]
int _chvalidator(int ch, int mask);

[[wunused, pure, requires_function(_isctype_l)]]
int _chvalidator_l($locale_t locale, int ch, int mask) {
	return _isctype_l(ch, mask, locale);
}

%[insert:pp_if(!defined(NDEBUG) && $has_function(_chvalidator))]
%#define __chvalidchk(ch, mask) _chvalidator(ch, mask)
%[insert:pp_else]
%{
__LOCAL __ATTR_WUNUSED __ATTR_NONNULL((1)) int
__NOTHROW_NCX(__LIBCCALL __acrt_locale_get_ctype_array_value)(__UINT16_TYPE__ const *__ct_array,
                                                              int __ch, int __mask) {
	if __likely(__ch >= -1 && __ch <= 255)
		return __ct_array[__ch] & __mask;
	return 0;
}
}
%#define __chvalidchk(ch, mask) __acrt_locale_get_ctype_array_value(__PCTYPE_FUNC, ch, mask)
%[insert:pp_endif]
%[insert:pp_if($has_function(_isctype_l))]
%#define _chvalidchk_l(ch, mask, locale) _isctype_l(ch, mask, locale)
%#define _ischartype_l(ch, mask, locale) _isctype_l(ch, mask, locale)
%[insert:pp_elif($has_function(_chvalidator_l))]
%#define _chvalidchk_l(ch, mask, locale) _chvalidator_l(locale, ch, mask)
%#define _ischartype_l(ch, mask, locale) _chvalidator_l(locale, ch, mask)
%[insert:pp_endif]


[[guard, const, wunused, nothrow]]
[[export_alias("_chvalidator")]]
int _isctype(int ch, int mask) {
	int result = 0;
	if ((mask & _UPPER) && isupper(ch))
		result |= _UPPER;
	if ((mask & _LOWER) && islower(ch))
		result |= _LOWER;
	if ((mask & _DIGIT) && isdigit(ch))
		result |= _DIGIT;
	if ((mask & _SPACE) && isspace(ch))
		result |= _SPACE;
	if ((mask & _PUNCT) && ispunct(ch))
		result |= _PUNCT;
	if ((mask & _CONTROL) && iscntrl(ch))
		result |= _CONTROL;
	if ((mask & _BLANK) && isblank(ch))
		result |= _BLANK;
	if ((mask & _HEX) && isxdigit(ch) && !isdigit(ch))
		result |= _HEX;
	if ((mask & _LEADBYTE) && ch >= 0xc0) /* NOTE: UTF-8 lead byte */
		result |= _LEADBYTE;
	/*if ((mask & 0x0100) && isalpha(ch) && islower(ch) && isupper(ch))
		result |= 0x0100;*/
	return result;
}

[[guard, pure, wunused, requires_function(_isctype)]]
[[section(".text.crt{|.dos}.unicode.locale.ctype")]]
[[if(defined(__LIBKCALL_CALLER_CLEANUP)), crt_intern_kos_alias("libc__isctype")]]
[[if(defined(__LIBDCALL_CALLER_CLEANUP)), crt_intern_dos_alias("libd__isctype")]]
int _isctype_l(int ch, int mask, $locale_t locale) {
	COMPILER_IMPURE();
	(void)locale;
	return _isctype(ch, mask);
}


%[insert:function(_isalpha_l = isalpha_l)]
%[insert:function(_isupper_l = isupper_l)]
%[insert:function(_islower_l = islower_l)]
%[insert:function(_isdigit_l = isdigit_l)]
%[insert:function(_isxdigit_l = isxdigit_l)]
%[insert:function(_isspace_l = isspace_l)]
%[insert:function(_ispunct_l = ispunct_l)]
%[insert:function(_isblank_l = isblank_l)]
%[insert:function(_isalnum_l = isalnum_l)]
%[insert:function(_isprint_l = isprint_l)]
%[insert:function(_isgraph_l = isgraph_l)]
%[insert:function(_iscntrl_l = iscntrl_l)]
%[insert:function(_tolower_l = tolower_l)]
%[insert:function(_toupper_l = toupper_l)]

%[insert:function(__isascii = isascii)]
%[insert:function(__toascii = toascii)]
%[insert:function(__iscsymf = issymstrt)]
%[insert:function(__iscsym = issymcont)]
%#endif /* __USE_DOS */


%{

__SYSDECL_END
#endif /* __CC__ */

}
