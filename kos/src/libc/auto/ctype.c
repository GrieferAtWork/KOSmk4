/* HASH CRC-32:0x42ddf899 */
/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_AUTO_CTYPE_C
#define GUARD_LIBC_AUTO_CTYPE_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../user/ctype.h"

DECL_BEGIN

#ifdef __KERNEL__
DEFINE_PUBLIC_ALIAS(__ctype_flags, libc___ctype_flags);
DEFINE_PUBLIC_ALIAS(__ctype_tolower, libc___ctype_tolower);
DEFINE_PUBLIC_ALIAS(__ctype_toupper, libc___ctype_toupper);
INTDEF __UINT8_TYPE__ const libc___ctype_flags[256];
INTERN_CONST ATTR_SECTION(".rodata.crt.unicode.static.ctype") __UINT8_TYPE__ const libc___ctype_flags[256] = {
	0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x03,0x03,0x03,0x03,0x03,0x01,0x01,
	0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,
	0x82,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,
	0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x40,0x40,0x40,0x40,0x40,0x40,
	0x40,0x28,0x28,0x28,0x28,0x28,0x28,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,
	0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x40,0x40,0x40,0x40,0x40,
	0x40,0x24,0x24,0x24,0x24,0x24,0x24,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,
	0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x40,0x40,0x40,0x40,0x01,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
};
INTDEF __UINT8_TYPE__ const libc___ctype_tolower[256];
INTERN_CONST ATTR_SECTION(".rodata.crt.unicode.static.ctype") __UINT8_TYPE__ const libc___ctype_tolower[256] = {
	0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f,
	0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1a,0x1b,0x1c,0x1d,0x1e,0x1f,
	0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,0x29,0x2a,0x2b,0x2c,0x2d,0x2e,0x2f,
	0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x3a,0x3b,0x3c,0x3d,0x3e,0x3f,
	0x40,0x61,0x62,0x63,0x64,0x65,0x66,0x67,0x68,0x69,0x6a,0x6b,0x6c,0x6d,0x6e,0x6f,
	0x70,0x71,0x72,0x73,0x74,0x75,0x76,0x77,0x78,0x79,0x7a,0x5b,0x5c,0x5d,0x5e,0x5f,
	0x60,0x61,0x62,0x63,0x64,0x65,0x66,0x67,0x68,0x69,0x6a,0x6b,0x6c,0x6d,0x6e,0x6f,
	0x70,0x71,0x72,0x73,0x74,0x75,0x76,0x77,0x78,0x79,0x7a,0x7b,0x7c,0x7d,0x7e,0x7f,
	0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,
	0x90,0x91,0x92,0x93,0x94,0x95,0x96,0x97,0x98,0x99,0x9a,0x9b,0x9c,0x9d,0x9e,0x9f,
	0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,
	0xb0,0xb1,0xb2,0xb3,0xb4,0xb5,0xb6,0xb7,0xb8,0xb9,0xba,0xbb,0xbc,0xbd,0xbe,0xbf,
	0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,
	0xd0,0xd1,0xd2,0xd3,0xd4,0xd5,0xd6,0xd7,0xd8,0xd9,0xda,0xdb,0xdc,0xdd,0xde,0xdf,
	0xe0,0xe1,0xe2,0xe3,0xe4,0xe5,0xe6,0xe7,0xe8,0xe9,0xea,0xeb,0xec,0xed,0xee,0xef,
	0xf0,0xf1,0xf2,0xf3,0xf4,0xf5,0xf6,0xf7,0xf8,0xf9,0xfa,0xfb,0xfc,0xfd,0xfe,0xff,
};
INTDEF __UINT8_TYPE__ const libc___ctype_toupper[256];
INTERN_CONST ATTR_SECTION(".rodata.crt.unicode.static.ctype") __UINT8_TYPE__ const libc___ctype_toupper[256] = {
	0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f,
	0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1a,0x1b,0x1c,0x1d,0x1e,0x1f,
	0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,0x29,0x2a,0x2b,0x2c,0x2d,0x2e,0x2f,
	0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x3a,0x3b,0x3c,0x3d,0x3e,0x3f,
	0x40,0x41,0x42,0x43,0x44,0x45,0x46,0x47,0x48,0x49,0x4a,0x4b,0x4c,0x4d,0x4e,0x4f,
	0x50,0x51,0x52,0x53,0x54,0x55,0x56,0x57,0x58,0x59,0x5a,0x5b,0x5c,0x5d,0x5e,0x5f,
	0x60,0x41,0x42,0x43,0x44,0x45,0x46,0x47,0x48,0x49,0x4a,0x4b,0x4c,0x4d,0x4e,0x4f,
	0x50,0x51,0x52,0x53,0x54,0x55,0x56,0x57,0x58,0x59,0x5a,0x7b,0x7c,0x7d,0x7e,0x7f,
	0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,
	0x90,0x91,0x92,0x93,0x94,0x95,0x96,0x97,0x98,0x99,0x9a,0x9b,0x9c,0x9d,0x9e,0x9f,
	0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,
	0xb0,0xb1,0xb2,0xb3,0xb4,0xb5,0xb6,0xb7,0xb8,0xb9,0xba,0xbb,0xbc,0xbd,0xbe,0xbf,
	0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,
	0xd0,0xd1,0xd2,0xd3,0xd4,0xd5,0xd6,0xd7,0xd8,0xd9,0xda,0xdb,0xdc,0xdd,0xde,0xdf,
	0xe0,0xe1,0xe2,0xe3,0xe4,0xe5,0xe6,0xe7,0xe8,0xe9,0xea,0xeb,0xec,0xed,0xee,0xef,
	0xf0,0xf1,0xf2,0xf3,0xf4,0xf5,0xf6,0xf7,0xf8,0xf9,0xfa,0xfb,0xfc,0xfd,0xfe,0xff,
};
#endif /* __KERNEL__ */
#ifndef __KERNEL__
#include <bits/crt/ctype.h>
/* >> iscntrl(3) */
INTERN ATTR_SECTION(".text.crt.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBCCALL libc_iscntrl)(int ch) {
#ifdef __crt_iscntrl
	return __crt_iscntrl(ch);
#else /* __crt_iscntrl */
	return __ascii_iscntrl(ch);
#endif /* !__crt_iscntrl */
}
#include <bits/crt/ctype.h>
/* >> isspace(3) */
INTERN ATTR_SECTION(".text.crt.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBCCALL libc_isspace)(int ch) {
#ifdef __crt_isspace
	return __crt_isspace(ch);
#else /* __crt_isspace */
	return __ascii_isspace(ch);
#endif /* !__crt_isspace */
}
#include <bits/crt/ctype.h>
/* >> isupper(3) */
INTERN ATTR_SECTION(".text.crt.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBCCALL libc_isupper)(int ch) {
#ifdef __crt_isupper
	return __crt_isupper(ch);
#else /* __crt_isupper */
	return __ascii_isupper(ch);
#endif /* !__crt_isupper */
}
#include <bits/crt/ctype.h>
/* >> islower(3) */
INTERN ATTR_SECTION(".text.crt.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBCCALL libc_islower)(int ch) {
#ifdef __crt_islower
	return __crt_islower(ch);
#else /* __crt_islower */
	return __ascii_islower(ch);
#endif /* !__crt_islower */
}
#include <bits/crt/ctype.h>
/* >> isalpha(3) */
INTERN ATTR_SECTION(".text.crt.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBCCALL libc_isalpha)(int ch) {
#ifdef __crt_isalpha
	return __crt_isalpha(ch);
#else /* __crt_isalpha */
	return __ascii_isalpha(ch);
#endif /* !__crt_isalpha */
}
#include <bits/crt/ctype.h>
/* >> isdigit(3) */
INTERN ATTR_SECTION(".text.crt.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBCCALL libc_isdigit)(int ch) {
#ifdef __crt_isdigit
	return __crt_isdigit(ch);
#else /* __crt_isdigit */
	return __ascii_isdigit(ch);
#endif /* !__crt_isdigit */
}
#include <bits/crt/ctype.h>
/* >> isxdigit(3) */
INTERN ATTR_SECTION(".text.crt.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBCCALL libc_isxdigit)(int ch) {
#ifdef __crt_isxdigit
	return __crt_isxdigit(ch);
#else /* __crt_isxdigit */
	return __ascii_isxdigit(ch);
#endif /* !__crt_isxdigit */
}
#include <bits/crt/ctype.h>
/* >> isalnum(3) */
INTERN ATTR_SECTION(".text.crt.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBCCALL libc_isalnum)(int ch) {
#ifdef __crt_isalnum
	return __crt_isalnum(ch);
#else /* __crt_isalnum */
	return __ascii_isalnum(ch);
#endif /* !__crt_isalnum */
}
#include <bits/crt/ctype.h>
/* >> ispunct(3) */
INTERN ATTR_SECTION(".text.crt.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBCCALL libc_ispunct)(int ch) {
#ifdef __crt_ispunct
	return __crt_ispunct(ch);
#else /* __crt_ispunct */
	return __ascii_ispunct(ch);
#endif /* !__crt_ispunct */
}
#include <bits/crt/ctype.h>
/* >> isgraph(3) */
INTERN ATTR_SECTION(".text.crt.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBCCALL libc_isgraph)(int ch) {
#ifdef __crt_isgraph
	return __crt_isgraph(ch);
#else /* __crt_isgraph */
	return __ascii_isgraph(ch);
#endif /* !__crt_isgraph */
}
#include <bits/crt/ctype.h>
/* >> isprint(3) */
INTERN ATTR_SECTION(".text.crt.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBCCALL libc_isprint)(int ch) {
#ifdef __crt_isprint
	return __crt_isprint(ch);
#else /* __crt_isprint */
	return __ascii_isprint(ch);
#endif /* !__crt_isprint */
}
#include <bits/crt/ctype.h>
/* >> tolower(3) */
INTERN ATTR_SECTION(".text.crt.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBCCALL libc_tolower)(int ch) {
#ifdef __crt_tolower
	return __crt_tolower(ch);
#else /* __crt_tolower */
	return __ascii_tolower(ch);
#endif /* !__crt_tolower */
}
#include <bits/crt/ctype.h>
/* >> toupper(3) */
INTERN ATTR_SECTION(".text.crt.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBCCALL libc_toupper)(int ch) {
#ifdef __crt_toupper
	return __crt_toupper(ch);
#else /* __crt_toupper */
	return __ascii_toupper(ch);
#endif /* !__crt_toupper */
}
#include <bits/crt/ctype.h>
/* >> isblank(3) */
INTERN ATTR_SECTION(".text.crt.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBCCALL libc_isblank)(int ch) {
#ifdef __crt_isblank
	return __crt_isblank(ch);
#else /* __crt_isblank */
	return __ascii_isblank(ch);
#endif /* !__crt_isblank */
}
/* >> iscntrl_l(3) */
INTERN ATTR_SECTION(".text.crt.unicode.locale.ctype") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBCCALL libc_iscntrl_l)(int ch,
                                     locale_t locale) {
	COMPILER_IMPURE();
	(void)locale;
	return libc_iscntrl(ch);
}
/* >> isspace_l(3) */
INTERN ATTR_SECTION(".text.crt.unicode.locale.ctype") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBCCALL libc_isspace_l)(int ch,
                                     locale_t locale) {
	COMPILER_IMPURE();
	(void)locale;
	return libc_isspace(ch);
}
/* >> isupper_l(3) */
INTERN ATTR_SECTION(".text.crt.unicode.locale.ctype") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBCCALL libc_isupper_l)(int ch,
                                     locale_t locale) {
	COMPILER_IMPURE();
	(void)locale;
	return libc_isupper(ch);
}
/* >> islower_l(3) */
INTERN ATTR_SECTION(".text.crt.unicode.locale.ctype") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBCCALL libc_islower_l)(int ch,
                                     locale_t locale) {
	COMPILER_IMPURE();
	(void)locale;
	return libc_islower(ch);
}
/* >> isalpha_l(3) */
INTERN ATTR_SECTION(".text.crt.unicode.locale.ctype") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBCCALL libc_isalpha_l)(int ch,
                                     locale_t locale) {
	COMPILER_IMPURE();
	(void)locale;
	return libc_isalpha(ch);
}
/* >> isdigit_l(3) */
INTERN ATTR_SECTION(".text.crt.unicode.locale.ctype") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBCCALL libc_isdigit_l)(int ch,
                                     locale_t locale) {
	COMPILER_IMPURE();
	(void)locale;
	return libc_isdigit(ch);
}
/* >> isxdigit_l(3) */
INTERN ATTR_SECTION(".text.crt.unicode.locale.ctype") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBCCALL libc_isxdigit_l)(int ch,
                                      locale_t locale) {
	COMPILER_IMPURE();
	(void)locale;
	return libc_isxdigit(ch);
}
/* >> isalnum_l(3) */
INTERN ATTR_SECTION(".text.crt.unicode.locale.ctype") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBCCALL libc_isalnum_l)(int ch,
                                     locale_t locale) {
	COMPILER_IMPURE();
	(void)locale;
	return libc_isalnum(ch);
}
/* >> ispunct_l(3) */
INTERN ATTR_SECTION(".text.crt.unicode.locale.ctype") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBCCALL libc_ispunct_l)(int ch,
                                     locale_t locale) {
	COMPILER_IMPURE();
	(void)locale;
	return libc_ispunct(ch);
}
/* >> isgraph_l(3) */
INTERN ATTR_SECTION(".text.crt.unicode.locale.ctype") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBCCALL libc_isgraph_l)(int ch,
                                     locale_t locale) {
	COMPILER_IMPURE();
	(void)locale;
	return libc_isgraph(ch);
}
/* >> isprint_l(3) */
INTERN ATTR_SECTION(".text.crt.unicode.locale.ctype") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBCCALL libc_isprint_l)(int ch,
                                     locale_t locale) {
	COMPILER_IMPURE();
	(void)locale;
	return libc_isprint(ch);
}
/* >> isblank_l(3) */
INTERN ATTR_SECTION(".text.crt.unicode.locale.ctype") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBCCALL libc_isblank_l)(int ch,
                                     locale_t locale) {
	COMPILER_IMPURE();
	(void)locale;
	return libc_isblank(ch);
}
/* >> tolower_l(3) */
INTERN ATTR_SECTION(".text.crt.unicode.locale.ctype") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBCCALL libc_tolower_l)(int ch,
                                     locale_t locale) {
	COMPILER_IMPURE();
	(void)locale;
	return libc_tolower(ch);
}
/* >> toupper_l(3) */
INTERN ATTR_SECTION(".text.crt.unicode.locale.ctype") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBCCALL libc_toupper_l)(int ch,
                                     locale_t locale) {
	COMPILER_IMPURE();
	(void)locale;
	return libc_toupper(ch);
}
/* Returns non-zero if `(C & ~0x7f) == 0' */
INTERN ATTR_SECTION(".text.crt.unicode.static.ctype") ATTR_CONST int
NOTHROW(LIBCCALL libc_isascii)(int c) {
	return (c & ~0x7f) == 0;
}
/* Re-returns `C & 0x7f' */
INTERN ATTR_SECTION(".text.crt.unicode.static.ctype") ATTR_CONST int
NOTHROW(LIBCCALL libc_toascii)(int c) {
	return c & 0x7f;
}
#endif /* !__KERNEL__ */

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(iscntrl, libc_iscntrl);
DEFINE_PUBLIC_ALIAS(isspace, libc_isspace);
DEFINE_PUBLIC_ALIAS(isupper, libc_isupper);
DEFINE_PUBLIC_ALIAS(islower, libc_islower);
DEFINE_PUBLIC_ALIAS(isalpha, libc_isalpha);
DEFINE_PUBLIC_ALIAS(isdigit, libc_isdigit);
DEFINE_PUBLIC_ALIAS(isxdigit, libc_isxdigit);
DEFINE_PUBLIC_ALIAS(isalnum, libc_isalnum);
DEFINE_PUBLIC_ALIAS(ispunct, libc_ispunct);
DEFINE_PUBLIC_ALIAS(isgraph, libc_isgraph);
DEFINE_PUBLIC_ALIAS(isprint, libc_isprint);
DEFINE_PUBLIC_ALIAS(tolower, libc_tolower);
DEFINE_PUBLIC_ALIAS(toupper, libc_toupper);
DEFINE_PUBLIC_ALIAS(isblank, libc_isblank);
DEFINE_PUBLIC_ALIAS(__iscntrl_l, libc_iscntrl_l);
DEFINE_PUBLIC_ALIAS(iscntrl_l, libc_iscntrl_l);
DEFINE_PUBLIC_ALIAS(__isspace_l, libc_isspace_l);
DEFINE_PUBLIC_ALIAS(isspace_l, libc_isspace_l);
DEFINE_PUBLIC_ALIAS(__isupper_l, libc_isupper_l);
DEFINE_PUBLIC_ALIAS(isupper_l, libc_isupper_l);
DEFINE_PUBLIC_ALIAS(__islower_l, libc_islower_l);
DEFINE_PUBLIC_ALIAS(islower_l, libc_islower_l);
DEFINE_PUBLIC_ALIAS(__isalpha_l, libc_isalpha_l);
DEFINE_PUBLIC_ALIAS(isalpha_l, libc_isalpha_l);
DEFINE_PUBLIC_ALIAS(__isdigit_l, libc_isdigit_l);
DEFINE_PUBLIC_ALIAS(isdigit_l, libc_isdigit_l);
DEFINE_PUBLIC_ALIAS(__isxdigit_l, libc_isxdigit_l);
DEFINE_PUBLIC_ALIAS(isxdigit_l, libc_isxdigit_l);
DEFINE_PUBLIC_ALIAS(__isalnum_l, libc_isalnum_l);
DEFINE_PUBLIC_ALIAS(isalnum_l, libc_isalnum_l);
DEFINE_PUBLIC_ALIAS(__ispunct_l, libc_ispunct_l);
DEFINE_PUBLIC_ALIAS(ispunct_l, libc_ispunct_l);
DEFINE_PUBLIC_ALIAS(__isgraph_l, libc_isgraph_l);
DEFINE_PUBLIC_ALIAS(isgraph_l, libc_isgraph_l);
DEFINE_PUBLIC_ALIAS(__isprint_l, libc_isprint_l);
DEFINE_PUBLIC_ALIAS(isprint_l, libc_isprint_l);
DEFINE_PUBLIC_ALIAS(__isblank_l, libc_isblank_l);
DEFINE_PUBLIC_ALIAS(isblank_l, libc_isblank_l);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_tolower_l, libc_tolower_l);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(__tolower_l, libc_tolower_l);
DEFINE_PUBLIC_ALIAS(tolower_l, libc_tolower_l);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_toupper_l, libc_toupper_l);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(__toupper_l, libc_toupper_l);
DEFINE_PUBLIC_ALIAS(toupper_l, libc_toupper_l);
DEFINE_PUBLIC_ALIAS(isascii, libc_isascii);
DEFINE_PUBLIC_ALIAS(toascii, libc_toascii);
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_CTYPE_C */
