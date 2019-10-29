/* HASH CRC-32:0x76e5e735 */
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
#ifndef GUARD_LIBC_AUTO_CTYPE_C
#define GUARD_LIBC_AUTO_CTYPE_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "ctype.h"

DECL_BEGIN

#ifndef __KERNEL__
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.unicode.static.ctype.iscntrl") int
NOTHROW(LIBCCALL libc_iscntrl)(int ch) {
#line 69 "kos/src/libc/magic/ctype.c"
	return (u8)ch <= 0x1f || (u8)ch == 0x7f;
}

INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.unicode.static.ctype.isspace") int
NOTHROW(LIBCCALL libc_isspace)(int ch) {
#line 89 "kos/src/libc/magic/ctype.c"
	return ((u8)ch >= 0x09 && (u8)ch <= 0x0d) || (u8)ch == 0x20;
}

INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.unicode.static.ctype.isupper") int
NOTHROW(LIBCCALL libc_isupper)(int ch) {
#line 108 "kos/src/libc/magic/ctype.c"
	return (u8)ch >= 0x41 && (u8)ch <= 0x5a;
}

INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.unicode.static.ctype.islower") int
NOTHROW(LIBCCALL libc_islower)(int ch) {
#line 128 "kos/src/libc/magic/ctype.c"
	return (u8)ch >= 0x61 && (u8)ch <= 0x7a;
}

INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.unicode.static.ctype.isalpha") int
NOTHROW(LIBCCALL libc_isalpha)(int ch) {
#line 147 "kos/src/libc/magic/ctype.c"
	return libc_isupper(ch) || libc_islower(ch);
}

INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.unicode.static.ctype.isdigit") int
NOTHROW(LIBCCALL libc_isdigit)(int ch) {
#line 166 "kos/src/libc/magic/ctype.c"
	return (u8)ch >= 0x30 && (u8)ch <= 0x39;
}

INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.unicode.static.ctype.isxdigit") int
NOTHROW(LIBCCALL libc_isxdigit)(int ch) {
#line 187 "kos/src/libc/magic/ctype.c"
	return libc_isdigit(ch) ||
	       ((u8)ch >= 0x41 && (u8)ch <= 0x46) ||
	       ((u8)ch >= 0x61 && (u8)ch <= 0x66);
}

INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.unicode.static.ctype.isalnum") int
NOTHROW(LIBCCALL libc_isalnum)(int ch) {
#line 208 "kos/src/libc/magic/ctype.c"
	return libc_isupper(ch) || libc_islower(ch) || libc_isdigit(ch);
}

INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.unicode.static.ctype.ispunct") int
NOTHROW(LIBCCALL libc_ispunct)(int ch) {
#line 230 "kos/src/libc/magic/ctype.c"
	return ((u8)ch >= 0x21 && (u8)ch <= 0x2f) ||
	       ((u8)ch >= 0x3a && (u8)ch <= 0x40) ||
	       ((u8)ch >= 0x5b && (u8)ch <= 0x60) ||
	       ((u8)ch >= 0x7b && (u8)ch <= 0x7e);
}

INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.unicode.static.ctype.isgraph") int
NOTHROW(LIBCCALL libc_isgraph)(int ch) {
#line 252 "kos/src/libc/magic/ctype.c"
	return (u8)ch >= 0x21 && (u8)ch <= 0x7e;
}

INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.unicode.static.ctype.isprint") int
NOTHROW(LIBCCALL libc_isprint)(int ch) {
#line 271 "kos/src/libc/magic/ctype.c"
	return (u8)ch >= 0x20 && (u8)ch <= 0x7e;
}

INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.unicode.static.ctype.tolower") int
NOTHROW(LIBCCALL libc_tolower)(int ch) {
#line 290 "kos/src/libc/magic/ctype.c"
	return libc_isupper(ch) ? ((u8)ch+0x20) : ch;
}

INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.unicode.static.ctype.toupper") int
NOTHROW(LIBCCALL libc_toupper)(int ch) {
#line 299 "kos/src/libc/magic/ctype.c"
	return libc_islower(ch) ? ((u8)ch-0x20) : ch;
}

INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.unicode.static.ctype.isblank") int
NOTHROW(LIBCCALL libc_isblank)(int ch) {
#line 311 "kos/src/libc/magic/ctype.c"
	return (u8)ch == 0x09 || (u8)ch == 0x20;
}

INTERN ATTR_PURE WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.unicode.locale.ctype.iscntrl_l") int
NOTHROW_NCX(LIBCCALL libc_iscntrl_l)(int ch,
                                     __locale_t locale) {
#line 337 "kos/src/libc/magic/ctype.c"
	(void)locale;
	return libc_iscntrl(ch);
}

INTERN ATTR_PURE WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.unicode.locale.ctype.isspace_l") int
NOTHROW_NCX(LIBCCALL libc_isspace_l)(int ch,
                                     __locale_t locale) {
#line 360 "kos/src/libc/magic/ctype.c"
	(void)locale;
	return libc_isspace(ch);
}

INTERN ATTR_PURE WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.unicode.locale.ctype.isupper_l") int
NOTHROW_NCX(LIBCCALL libc_isupper_l)(int ch,
                                     __locale_t locale) {
#line 382 "kos/src/libc/magic/ctype.c"
	(void)locale;
	return libc_isupper(ch);
}

INTERN ATTR_PURE WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.unicode.locale.ctype.islower_l") int
NOTHROW_NCX(LIBCCALL libc_islower_l)(int ch,
                                     __locale_t locale) {
#line 404 "kos/src/libc/magic/ctype.c"
	(void)locale;
	return libc_islower(ch);
}

INTERN ATTR_PURE WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.unicode.locale.ctype.isalpha_l") int
NOTHROW_NCX(LIBCCALL libc_isalpha_l)(int ch,
                                     __locale_t locale) {
#line 426 "kos/src/libc/magic/ctype.c"
	(void)locale;
	return libc_isalpha(ch);
}

INTERN ATTR_PURE WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.unicode.locale.ctype.isdigit_l") int
NOTHROW_NCX(LIBCCALL libc_isdigit_l)(int ch,
                                     __locale_t locale) {
#line 448 "kos/src/libc/magic/ctype.c"
	(void)locale;
	return libc_isdigit(ch);
}

INTERN ATTR_PURE WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.unicode.locale.ctype.isxdigit_l") int
NOTHROW_NCX(LIBCCALL libc_isxdigit_l)(int ch,
                                      __locale_t locale) {
#line 470 "kos/src/libc/magic/ctype.c"
	(void)locale;
	return libc_isxdigit(ch);
}

INTERN ATTR_PURE WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.unicode.locale.ctype.isalnum_l") int
NOTHROW_NCX(LIBCCALL libc_isalnum_l)(int ch,
                                     __locale_t locale) {
#line 492 "kos/src/libc/magic/ctype.c"
	(void)locale;
	return libc_isalnum(ch);
}

INTERN ATTR_PURE WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.unicode.locale.ctype.ispunct_l") int
NOTHROW_NCX(LIBCCALL libc_ispunct_l)(int ch,
                                     __locale_t locale) {
#line 514 "kos/src/libc/magic/ctype.c"
	(void)locale;
	return libc_ispunct(ch);
}

INTERN ATTR_PURE WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.unicode.locale.ctype.isgraph_l") int
NOTHROW_NCX(LIBCCALL libc_isgraph_l)(int ch,
                                     __locale_t locale) {
#line 536 "kos/src/libc/magic/ctype.c"
	(void)locale;
	return libc_isgraph(ch);
}

INTERN ATTR_PURE WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.unicode.locale.ctype.isprint_l") int
NOTHROW_NCX(LIBCCALL libc_isprint_l)(int ch,
                                     __locale_t locale) {
#line 558 "kos/src/libc/magic/ctype.c"
	(void)locale;
	return libc_isprint(ch);
}

INTERN ATTR_PURE WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.unicode.locale.ctype.isblank_l") int
NOTHROW_NCX(LIBCCALL libc_isblank_l)(int ch,
                                     __locale_t locale) {
#line 580 "kos/src/libc/magic/ctype.c"
	(void)locale;
	return libc_isblank(ch);
}

INTERN ATTR_PURE WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.unicode.locale.ctype.tolower_l") int
NOTHROW_NCX(LIBCCALL libc_tolower_l)(int ch,
                                     __locale_t locale) {
#line 598 "kos/src/libc/magic/ctype.c"
	/* TODO: GLC has a variant for this! */
	(void)locale;
	return libc_tolower(ch);
}

INTERN ATTR_PURE WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.unicode.locale.ctype.toupper_l") int
NOTHROW_NCX(LIBCCALL libc_toupper_l)(int ch,
                                     __locale_t locale) {
#line 605 "kos/src/libc/magic/ctype.c"
	/* TODO: GLC has a variant for this! */
	(void)locale;
	return libc_toupper(ch);
}

#endif /* !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_WEAK_ALIAS(iscntrl, libc_iscntrl);
DEFINE_PUBLIC_WEAK_ALIAS(isspace, libc_isspace);
DEFINE_PUBLIC_WEAK_ALIAS(isupper, libc_isupper);
DEFINE_PUBLIC_WEAK_ALIAS(islower, libc_islower);
DEFINE_PUBLIC_WEAK_ALIAS(isalpha, libc_isalpha);
DEFINE_PUBLIC_WEAK_ALIAS(isdigit, libc_isdigit);
DEFINE_PUBLIC_WEAK_ALIAS(isxdigit, libc_isxdigit);
DEFINE_PUBLIC_WEAK_ALIAS(isalnum, libc_isalnum);
DEFINE_PUBLIC_WEAK_ALIAS(ispunct, libc_ispunct);
DEFINE_PUBLIC_WEAK_ALIAS(isgraph, libc_isgraph);
DEFINE_PUBLIC_WEAK_ALIAS(isprint, libc_isprint);
DEFINE_PUBLIC_WEAK_ALIAS(tolower, libc_tolower);
DEFINE_PUBLIC_WEAK_ALIAS(_tolower, libc_tolower);
DEFINE_PUBLIC_WEAK_ALIAS(toupper, libc_toupper);
DEFINE_PUBLIC_WEAK_ALIAS(_toupper, libc_toupper);
DEFINE_PUBLIC_WEAK_ALIAS(isblank, libc_isblank);
DEFINE_PUBLIC_WEAK_ALIAS(iscntrl_l, libc_iscntrl_l);
DEFINE_PUBLIC_WEAK_ALIAS(__iscntrl_l, libc_iscntrl_l);
DEFINE_PUBLIC_WEAK_ALIAS(isspace_l, libc_isspace_l);
DEFINE_PUBLIC_WEAK_ALIAS(__isspace_l, libc_isspace_l);
DEFINE_PUBLIC_WEAK_ALIAS(isupper_l, libc_isupper_l);
DEFINE_PUBLIC_WEAK_ALIAS(__isupper_l, libc_isupper_l);
DEFINE_PUBLIC_WEAK_ALIAS(islower_l, libc_islower_l);
DEFINE_PUBLIC_WEAK_ALIAS(__islower_l, libc_islower_l);
DEFINE_PUBLIC_WEAK_ALIAS(isalpha_l, libc_isalpha_l);
DEFINE_PUBLIC_WEAK_ALIAS(__isalpha_l, libc_isalpha_l);
DEFINE_PUBLIC_WEAK_ALIAS(isdigit_l, libc_isdigit_l);
DEFINE_PUBLIC_WEAK_ALIAS(__isdigit_l, libc_isdigit_l);
DEFINE_PUBLIC_WEAK_ALIAS(isxdigit_l, libc_isxdigit_l);
DEFINE_PUBLIC_WEAK_ALIAS(__isxdigit_l, libc_isxdigit_l);
DEFINE_PUBLIC_WEAK_ALIAS(isalnum_l, libc_isalnum_l);
DEFINE_PUBLIC_WEAK_ALIAS(__isalnum_l, libc_isalnum_l);
DEFINE_PUBLIC_WEAK_ALIAS(ispunct_l, libc_ispunct_l);
DEFINE_PUBLIC_WEAK_ALIAS(__ispunct_l, libc_ispunct_l);
DEFINE_PUBLIC_WEAK_ALIAS(isgraph_l, libc_isgraph_l);
DEFINE_PUBLIC_WEAK_ALIAS(__isgraph_l, libc_isgraph_l);
DEFINE_PUBLIC_WEAK_ALIAS(isprint_l, libc_isprint_l);
DEFINE_PUBLIC_WEAK_ALIAS(__isprint_l, libc_isprint_l);
DEFINE_PUBLIC_WEAK_ALIAS(isblank_l, libc_isblank_l);
DEFINE_PUBLIC_WEAK_ALIAS(__isblank_l, libc_isblank_l);
DEFINE_PUBLIC_WEAK_ALIAS(tolower_l, libc_tolower_l);
DEFINE_PUBLIC_WEAK_ALIAS(_tolower_l, libc_tolower_l);
DEFINE_PUBLIC_WEAK_ALIAS(__tolower_l, libc_tolower_l);
DEFINE_PUBLIC_WEAK_ALIAS(toupper_l, libc_toupper_l);
DEFINE_PUBLIC_WEAK_ALIAS(_toupper_l, libc_toupper_l);
DEFINE_PUBLIC_WEAK_ALIAS(__toupper_l, libc_toupper_l);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_CTYPE_C */
