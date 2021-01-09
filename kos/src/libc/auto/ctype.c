/* HASH CRC-32:0xc2b71b8f */
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

INTERN ATTR_SECTION(".text.crt.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBCCALL libc_iscntrl)(int ch) {

	return (u8)ch <= 0x1f || (u8)ch == 0x7f;
















}
INTERN ATTR_SECTION(".text.crt.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBCCALL libc_isspace)(int ch) {

	return ((u8)ch >= 0x09 && (u8)ch <= 0x0d) || (u8)ch == 0x20;
















}
INTERN ATTR_SECTION(".text.crt.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBCCALL libc_isupper)(int ch) {

	return (u8)ch >= 0x41 && (u8)ch <= 0x5a;
















}
INTERN ATTR_SECTION(".text.crt.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBCCALL libc_islower)(int ch) {

	return (u8)ch >= 0x61 && (u8)ch <= 0x7a;
















}
INTERN ATTR_SECTION(".text.crt.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBCCALL libc_isalpha)(int ch) {

	return libc_isupper(ch) || libc_islower(ch);
















}
INTERN ATTR_SECTION(".text.crt.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBCCALL libc_isdigit)(int ch) {

	return (u8)ch >= 0x30 && (u8)ch <= 0x39;
















}
INTERN ATTR_SECTION(".text.crt.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBCCALL libc_isxdigit)(int ch) {

	return libc_isdigit(ch) ||
	       ((u8)ch >= 0x41 && (u8)ch <= 0x46) ||
	       ((u8)ch >= 0x61 && (u8)ch <= 0x66);


















}
INTERN ATTR_SECTION(".text.crt.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBCCALL libc_isalnum)(int ch) {

	return libc_isupper(ch) || libc_islower(ch) || libc_isdigit(ch);
















}
INTERN ATTR_SECTION(".text.crt.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBCCALL libc_ispunct)(int ch) {

	return ((u8)ch >= 0x21 && (u8)ch <= 0x2f) ||
	       ((u8)ch >= 0x3a && (u8)ch <= 0x40) ||
	       ((u8)ch >= 0x5b && (u8)ch <= 0x60) ||
	       ((u8)ch >= 0x7b && (u8)ch <= 0x7e);



















}
INTERN ATTR_SECTION(".text.crt.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBCCALL libc_isgraph)(int ch) {

	return (u8)ch >= 0x21 && (u8)ch <= 0x7e;
















}
INTERN ATTR_SECTION(".text.crt.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBCCALL libc_isprint)(int ch) {

	return (u8)ch >= 0x20 && (u8)ch <= 0x7e;
















}
INTERN ATTR_SECTION(".text.crt.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBCCALL libc_tolower)(int ch) {

	return libc_isupper(ch) ? ((u8)ch+0x20) : ch;







}
INTERN ATTR_SECTION(".text.crt.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBCCALL libc_toupper)(int ch) {

	return libc_islower(ch) ? ((u8)ch-0x20) : ch;







}
INTERN ATTR_SECTION(".text.crt.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBCCALL libc_isblank)(int ch) {

	return (u8)ch == 0x09 || (u8)ch == 0x20;














}
#ifndef __KERNEL__
INTERN ATTR_SECTION(".text.crt.unicode.locale.ctype") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBCCALL libc_iscntrl_l)(int ch,
                                     __locale_t locale) {

	(void)locale;
	COMPILER_IMPURE();
	return libc_iscntrl(ch);


















}
INTERN ATTR_SECTION(".text.crt.unicode.locale.ctype") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBCCALL libc_isspace_l)(int ch,
                                     __locale_t locale) {

	(void)locale;
	COMPILER_IMPURE();
	return libc_isspace(ch);


















}
INTERN ATTR_SECTION(".text.crt.unicode.locale.ctype") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBCCALL libc_isupper_l)(int ch,
                                     __locale_t locale) {

	(void)locale;
	COMPILER_IMPURE();
	return libc_isupper(ch);


















}
INTERN ATTR_SECTION(".text.crt.unicode.locale.ctype") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBCCALL libc_islower_l)(int ch,
                                     __locale_t locale) {

	(void)locale;
	COMPILER_IMPURE();
	return libc_islower(ch);


















}
INTERN ATTR_SECTION(".text.crt.unicode.locale.ctype") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBCCALL libc_isalpha_l)(int ch,
                                     __locale_t locale) {

	(void)locale;
	COMPILER_IMPURE();
	return libc_isalpha(ch);


















}
INTERN ATTR_SECTION(".text.crt.unicode.locale.ctype") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBCCALL libc_isdigit_l)(int ch,
                                     __locale_t locale) {

	(void)locale;
	COMPILER_IMPURE();
	return libc_isdigit(ch);


















}
INTERN ATTR_SECTION(".text.crt.unicode.locale.ctype") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBCCALL libc_isxdigit_l)(int ch,
                                      __locale_t locale) {

	(void)locale;
	COMPILER_IMPURE();
	return libc_isxdigit(ch);


















}
INTERN ATTR_SECTION(".text.crt.unicode.locale.ctype") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBCCALL libc_isalnum_l)(int ch,
                                     __locale_t locale) {

	(void)locale;
	COMPILER_IMPURE();
	return libc_isalnum(ch);


















}
INTERN ATTR_SECTION(".text.crt.unicode.locale.ctype") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBCCALL libc_ispunct_l)(int ch,
                                     __locale_t locale) {

	(void)locale;
	COMPILER_IMPURE();
	return libc_ispunct(ch);


















}
INTERN ATTR_SECTION(".text.crt.unicode.locale.ctype") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBCCALL libc_isgraph_l)(int ch,
                                     __locale_t locale) {

	(void)locale;
	COMPILER_IMPURE();
	return libc_isgraph(ch);


















}
INTERN ATTR_SECTION(".text.crt.unicode.locale.ctype") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBCCALL libc_isprint_l)(int ch,
                                     __locale_t locale) {

	(void)locale;
	COMPILER_IMPURE();
	return libc_isprint(ch);


















}
INTERN ATTR_SECTION(".text.crt.unicode.locale.ctype") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBCCALL libc_isblank_l)(int ch,
                                     __locale_t locale) {

	(void)locale;
	COMPILER_IMPURE();
	return libc_isblank(ch);
















}
INTERN ATTR_SECTION(".text.crt.unicode.locale.ctype") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBCCALL libc_tolower_l)(int ch,
                                     __locale_t locale) {
	/* TODO: GLC has a variant for this! */
	(void)locale;
	COMPILER_IMPURE();
	return libc_tolower(ch);
}
INTERN ATTR_SECTION(".text.crt.unicode.locale.ctype") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBCCALL libc_toupper_l)(int ch,
                                     __locale_t locale) {
	/* TODO: GLC has a variant for this! */
	(void)locale;
	COMPILER_IMPURE();
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
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(_tolower, libc_tolower);
#endif /* !__KERNEL__ */
DEFINE_PUBLIC_ALIAS(tolower, libc_tolower);
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(_toupper, libc_toupper);
#endif /* !__KERNEL__ */
DEFINE_PUBLIC_ALIAS(toupper, libc_toupper);
DEFINE_PUBLIC_ALIAS(isblank, libc_isblank);
#ifndef __KERNEL__
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
DEFINE_PUBLIC_ALIAS(_tolower_l, libc_tolower_l);
DEFINE_PUBLIC_ALIAS(__tolower_l, libc_tolower_l);
DEFINE_PUBLIC_ALIAS(tolower_l, libc_tolower_l);
DEFINE_PUBLIC_ALIAS(_toupper_l, libc_toupper_l);
DEFINE_PUBLIC_ALIAS(__toupper_l, libc_toupper_l);
DEFINE_PUBLIC_ALIAS(toupper_l, libc_toupper_l);
DEFINE_PUBLIC_ALIAS(isascii, libc_isascii);
DEFINE_PUBLIC_ALIAS(toascii, libc_toascii);
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_CTYPE_C */
