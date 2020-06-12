/* HASH CRC-32:0xfcef26ce */
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
#ifndef GUARD_LIBC_AUTO_CTYPE_C
#define GUARD_LIBC_AUTO_CTYPE_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../user/ctype.h"

DECL_BEGIN

INTERN ATTR_SECTION(".text.crt.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBCCALL libc_iscntrl)(int ch) {
#ifdef __BUILDING_LIBC
	return (u8)ch <= 0x1f || (u8)ch == 0x7f;
#else /* __BUILDING_LIBC */
#if defined(__CRT_HAVE___ctype_b_loc) && defined(__CRT_GLC)
#include <hybrid/byteorder.h>
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	return (*__ctype_b_loc())[ch] & (1 << 9);
#else /* __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__ */
	return (*__ctype_b_loc())[ch] & (1 << 1);
#endif /* __BYTE_ORDER__ != __ORDER_BIG_ENDIAN__ */
#elif defined(__CRT_HAVE___locale_ctype_ptr) && defined(__CRT_CYG)
	return ((__locale_ctype_ptr() + 1)[ch & 0xff] & 040) != 0;
#elif defined(__CRT_HAVE__isctype) && defined(__CRT_DOS)
	return _isctype(ch, 0x0020);
#else
	return (u8)ch <= 0x1f || (u8)ch == 0x7f;
#endif
#endif /* !__BUILDING_LIBC */
}
INTERN ATTR_SECTION(".text.crt.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBCCALL libc_isspace)(int ch) {
#ifdef __BUILDING_LIBC
	return ((u8)ch >= 0x09 && (u8)ch <= 0x0d) || (u8)ch == 0x20;
#else /* __BUILDING_LIBC */
#if defined(__CRT_HAVE___ctype_b_loc) && defined(__CRT_GLC)
#include <hybrid/byteorder.h>
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	return (*__ctype_b_loc())[ch] & (1 << 5);
#else /* __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__ */
	return (*__ctype_b_loc())[ch] & (1 << 13);
#endif /* __BYTE_ORDER__ != __ORDER_BIG_ENDIAN__ */
#elif defined(__CRT_HAVE___locale_ctype_ptr) && defined(__CRT_CYG)
	return ((__locale_ctype_ptr() + 1)[ch & 0xff] & 010) != 0;
#elif defined(__CRT_HAVE__isctype) && defined(__CRT_DOS)
	return _isctype(ch, 0x0008);
#else
	return ((u8)ch >= 0x09 && (u8)ch <= 0x0d) || (u8)ch == 0x20;
#endif
#endif /* !__BUILDING_LIBC */
}
INTERN ATTR_SECTION(".text.crt.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBCCALL libc_isupper)(int ch) {
#ifdef __BUILDING_LIBC
	return (u8)ch >= 0x41 && (u8)ch <= 0x5a;
#else /* __BUILDING_LIBC */
#if defined(__CRT_HAVE___ctype_b_loc) && defined(__CRT_GLC)
#include <hybrid/byteorder.h>
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	return (*__ctype_b_loc())[ch] & (1 << 0);
#else /* __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__ */
	return (*__ctype_b_loc())[ch] & (1 << 8);
#endif /* __BYTE_ORDER__ != __ORDER_BIG_ENDIAN__ */
#elif defined(__CRT_HAVE___locale_ctype_ptr) && defined(__CRT_CYG)
	return ((__locale_ctype_ptr() + 1)[ch & 0xff] & 3) == 1;
#elif defined(__CRT_HAVE__isctype) && defined(__CRT_DOS)
	return _isctype(ch, 0x0001);
#else
	return (u8)ch >= 0x41 && (u8)ch <= 0x5a;
#endif
#endif /* !__BUILDING_LIBC */
}
INTERN ATTR_SECTION(".text.crt.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBCCALL libc_islower)(int ch) {
#ifdef __BUILDING_LIBC
	return (u8)ch >= 0x61 && (u8)ch <= 0x7a;
#else /* __BUILDING_LIBC */
#if defined(__CRT_HAVE___ctype_b_loc) && defined(__CRT_GLC)
#include <hybrid/byteorder.h>
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	return (*__ctype_b_loc())[ch] & (1 << 1);
#else /* __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__ */
	return (*__ctype_b_loc())[ch] & (1 << 9);
#endif /* __BYTE_ORDER__ != __ORDER_BIG_ENDIAN__ */
#elif defined(__CRT_HAVE___locale_ctype_ptr) && defined(__CRT_CYG)
	return ((__locale_ctype_ptr() + 1)[ch & 0xff] & 3) == 2;
#elif defined(__CRT_HAVE__isctype) && defined(__CRT_DOS)
	return _isctype(ch, 0x0002);
#else
	return (u8)ch >= 0x61 && (u8)ch <= 0x7a;
#endif
#endif /* !__BUILDING_LIBC */
}
INTERN ATTR_SECTION(".text.crt.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBCCALL libc_isalpha)(int ch) {
#ifdef __BUILDING_LIBC
	return libc_isupper(ch) || libc_islower(ch);
#else /* __BUILDING_LIBC */
#if defined(__CRT_HAVE___ctype_b_loc) && defined(__CRT_GLC)
#include <hybrid/byteorder.h>
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	return (*__ctype_b_loc())[ch] & (1 << 2);
#else /* __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__ */
	return (*__ctype_b_loc())[ch] & (1 << 10);
#endif /* __BYTE_ORDER__ != __ORDER_BIG_ENDIAN__ */
#elif defined(__CRT_HAVE___locale_ctype_ptr) && defined(__CRT_CYG)
	return ((__locale_ctype_ptr() + 1)[ch & 0xff] & 3) != 0;
#elif defined(__CRT_HAVE__isctype) && defined(__CRT_DOS)
	return _isctype(ch, 0x0103);
#else
	return isupper(ch) || islower(ch);
#endif
#endif /* !__BUILDING_LIBC */
}
INTERN ATTR_SECTION(".text.crt.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBCCALL libc_isdigit)(int ch) {
#ifdef __BUILDING_LIBC
	return (u8)ch >= 0x30 && (u8)ch <= 0x39;
#else /* __BUILDING_LIBC */
#if defined(__CRT_HAVE___ctype_b_loc) && defined(__CRT_GLC)
#include <hybrid/byteorder.h>
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	return (*__ctype_b_loc())[ch] & (1 << 3);
#else /* __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__ */
	return (*__ctype_b_loc())[ch] & (1 << 11);
#endif /* __BYTE_ORDER__ != __ORDER_BIG_ENDIAN__ */
#elif defined(__CRT_HAVE___locale_ctype_ptr) && defined(__CRT_CYG)
	return ((__locale_ctype_ptr() + 1)[ch & 0xff] & 4) != 0;
#elif defined(__CRT_HAVE__isctype) && defined(__CRT_DOS)
	return _isctype(ch, 0x0004);
#else
	return (u8)ch >= 0x30 && (u8)ch <= 0x39;
#endif
#endif /* !__BUILDING_LIBC */
}
INTERN ATTR_SECTION(".text.crt.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBCCALL libc_isxdigit)(int ch) {
#ifdef __BUILDING_LIBC
	return isdigit(ch) ||
	       ((u8)ch >= 0x41 && (u8)ch <= 0x46) ||
	       ((u8)ch >= 0x61 && (u8)ch <= 0x66);
#else /* __BUILDING_LIBC */
#if defined(__CRT_HAVE___ctype_b_loc) && defined(__CRT_GLC)
#include <hybrid/byteorder.h>
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	return (*__ctype_b_loc())[ch] & (1 << 4);
#else /* __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__ */
	return (*__ctype_b_loc())[ch] & (1 << 12);
#endif /* __BYTE_ORDER__ != __ORDER_BIG_ENDIAN__ */
#elif defined(__CRT_HAVE___locale_ctype_ptr) && defined(__CRT_CYG)
	return ((__locale_ctype_ptr() + 1)[ch & 0xff] & 0104) != 0;
#elif defined(__CRT_HAVE__isctype) && defined(__CRT_DOS)
	return _isctype(ch, 0x0080);
#else
	return isdigit(ch) ||
	       ((u8)ch >= 0x41 && (u8)ch <= 0x46) ||
	       ((u8)ch >= 0x61 && (u8)ch <= 0x66);
#endif
#endif /* !__BUILDING_LIBC */
}
INTERN ATTR_SECTION(".text.crt.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBCCALL libc_isalnum)(int ch) {
#ifdef __BUILDING_LIBC
	return isupper(ch) || islower(ch) || isdigit(ch);
#else /* __BUILDING_LIBC */
#if defined(__CRT_HAVE___ctype_b_loc) && defined(__CRT_GLC)
#include <hybrid/byteorder.h>
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	return (*__ctype_b_loc())[ch] & (1 << 11);
#else /* __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__ */
	return (*__ctype_b_loc())[ch] & (1 << 3);
#endif /* __BYTE_ORDER__ != __ORDER_BIG_ENDIAN__ */
#elif defined(__CRT_HAVE___locale_ctype_ptr) && defined(__CRT_CYG)
	return ((__locale_ctype_ptr() + 1)[ch & 0xff] & 7) != 0;
#elif defined(__CRT_HAVE__isctype) && defined(__CRT_DOS)
	return _isctype(ch, 0x0107);
#else
	return isupper(ch) || islower(ch) || isdigit(ch);
#endif
#endif /* !__BUILDING_LIBC */
}
INTERN ATTR_SECTION(".text.crt.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBCCALL libc_ispunct)(int ch) {
#ifdef __BUILDING_LIBC
	return ((u8)ch >= 0x21 && (u8)ch <= 0x2f) ||
	       ((u8)ch >= 0x3a && (u8)ch <= 0x40) ||
	       ((u8)ch >= 0x5b && (u8)ch <= 0x60) ||
	       ((u8)ch >= 0x7b && (u8)ch <= 0x7e);
#else /* __BUILDING_LIBC */
#if defined(__CRT_HAVE___ctype_b_loc) && defined(__CRT_GLC)
#include <hybrid/byteorder.h>
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	return (*__ctype_b_loc())[ch] & (1 << 10);
#else /* __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__ */
	return (*__ctype_b_loc())[ch] & (1 << 2);
#endif /* __BYTE_ORDER__ != __ORDER_BIG_ENDIAN__ */
#elif defined(__CRT_HAVE___locale_ctype_ptr) && defined(__CRT_CYG)
	return ((__locale_ctype_ptr() + 1)[ch & 0xff] & 020) != 0;
#elif defined(__CRT_HAVE__isctype) && defined(__CRT_DOS)
	return _isctype(ch, 0x0010);
#else
	return ((u8)ch >= 0x21 && (u8)ch <= 0x2f) ||
	       ((u8)ch >= 0x3a && (u8)ch <= 0x40) ||
	       ((u8)ch >= 0x5b && (u8)ch <= 0x60) ||
	       ((u8)ch >= 0x7b && (u8)ch <= 0x7e);
#endif
#endif /* !__BUILDING_LIBC */
}
INTERN ATTR_SECTION(".text.crt.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBCCALL libc_isgraph)(int ch) {
#ifdef __BUILDING_LIBC
	return (u8)ch >= 0x21 && (u8)ch <= 0x7e;
#else /* __BUILDING_LIBC */
#if defined(__CRT_HAVE___ctype_b_loc) && defined(__CRT_GLC)
#include <hybrid/byteorder.h>
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	return (*__ctype_b_loc())[ch] & (1 << 7);
#else /* __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__ */
	return (*__ctype_b_loc())[ch] & (1 << 15);
#endif /* __BYTE_ORDER__ != __ORDER_BIG_ENDIAN__ */
#elif defined(__CRT_HAVE___locale_ctype_ptr) && defined(__CRT_CYG)
	return ((__locale_ctype_ptr() + 1)[ch & 0xff] & 027) != 0;
#elif defined(__CRT_HAVE__isctype) && defined(__CRT_DOS)
	return _isctype(ch, 0x0117);
#else
	return (u8)ch >= 0x21 && (u8)ch <= 0x7e;
#endif
#endif /* !__BUILDING_LIBC */
}
INTERN ATTR_SECTION(".text.crt.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBCCALL libc_isprint)(int ch) {
#ifdef __BUILDING_LIBC
	return (u8)ch >= 0x20 && (u8)ch <= 0x7e;
#else /* __BUILDING_LIBC */
#if defined(__CRT_HAVE___ctype_b_loc) && defined(__CRT_GLC)
#include <hybrid/byteorder.h>
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	return (*__ctype_b_loc())[ch] & (1 << 6);
#else /* __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__ */
	return (*__ctype_b_loc())[ch] & (1 << 14);
#endif /* __BYTE_ORDER__ != __ORDER_BIG_ENDIAN__ */
#elif defined(__CRT_HAVE___locale_ctype_ptr) && defined(__CRT_CYG)
	return ((__locale_ctype_ptr() + 1)[ch & 0xff] & 0227) != 0;
#elif defined(__CRT_HAVE__isctype) && defined(__CRT_DOS)
	return _isctype(ch, 0x0157);
#else
	return (u8)ch >= 0x20 && (u8)ch <= 0x7e;
#endif
#endif /* !__BUILDING_LIBC */
}
INTERN ATTR_SECTION(".text.crt.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBCCALL libc_tolower)(int ch) {
#ifdef __BUILDING_LIBC
	return isupper(ch) ? ((u8)ch+0x20) : ch;
#else /* __BUILDING_LIBC */
#if defined(__CRT_HAVE___ctype_tolower_loc) && defined(__CRT_CYG)
	return ch >= -128 && ch < 256 ? (*__ctype_tolower_loc())[ch] : ch;
#else /* __CRT_HAVE___ctype_tolower_loc && __CRT_CYG */
	return isupper(ch) ? ((u8)ch+0x20) : ch;
#endif /* !__CRT_HAVE___ctype_tolower_loc || !__CRT_CYG */
#endif /* !__BUILDING_LIBC */
}
INTERN ATTR_SECTION(".text.crt.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBCCALL libc_toupper)(int ch) {
#ifdef __BUILDING_LIBC
	return islower(ch) ? ((u8)ch-0x20) : ch;
#else /* __BUILDING_LIBC */
#if defined(__CRT_HAVE___ctype_toupper_loc) && defined(__CRT_CYG)
	return ch >= -128 && ch < 256 ? (*__ctype_toupper_loc())[ch] : ch;
#else /* __CRT_HAVE___ctype_toupper_loc && __CRT_CYG */
	return islower(ch) ? ((u8)ch-0x20) : ch;
#endif /* !__CRT_HAVE___ctype_toupper_loc || !__CRT_CYG */
#endif /* !__BUILDING_LIBC */
}
INTERN ATTR_SECTION(".text.crt.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBCCALL libc_isblank)(int ch) {
#ifdef __BUILDING_LIBC
	return (u8)ch == 0x09 || (u8)ch == 0x20;
#else /* __BUILDING_LIBC */
#if defined(__CRT_HAVE___ctype_b_loc) && defined(__CRT_GLC)
#include <hybrid/byteorder.h>
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	return (*__ctype_b_loc())[ch] & (1 << 8);
#else /* __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__ */
	return (*__ctype_b_loc())[ch] & (1 << 0);
#endif /* __BYTE_ORDER__ != __ORDER_BIG_ENDIAN__ */
#elif defined(__CRT_HAVE___locale_ctype_ptr) && defined(__CRT_CYG)
	return ((__locale_ctype_ptr() + 1)[ch & 0xff] & 0200) != 0 || ch == '\t';
#else
	return (u8)ch == 0x09 || (u8)ch == 0x20;
#endif
#endif /* !__BUILDING_LIBC */
}
#ifndef __KERNEL__
INTERN ATTR_SECTION(".text.crt.unicode.locale.ctype") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBCCALL libc_iscntrl_l)(int ch,
                                     __locale_t locale) {
#ifdef __BUILDING_LIBC
	(void)locale;
	COMPILER_IMPURE();
	return iscntrl(ch);
#else /* __BUILDING_LIBC */
#if defined(__CRT_HAVE___ctype_b_loc) && defined(__CRT_GLC)
#include <hybrid/byteorder.h>
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	return locale->__ctype_b[ch] & (1 << 9);
#else /* __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__ */
	return locale->__ctype_b[ch] & (1 << 1);
#endif /* __BYTE_ORDER__ != __ORDER_BIG_ENDIAN__ */
#elif defined(__CRT_HAVE___locale_ctype_ptr_l) && defined(__CRT_CYG)
	return ((__locale_ctype_ptr_l(locale) + 1)[ch & 0xff] & 040) != 0;
#elif defined(__CRT_HAVE__isctype_l) && defined(__CRT_DOS)
	return _isctype_l(ch, 0x0020, locale);
#else
	(void)locale;
	COMPILER_IMPURE();
	return iscntrl(ch);
#endif
#endif /* !__BUILDING_LIBC */
}
INTERN ATTR_SECTION(".text.crt.unicode.locale.ctype") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBCCALL libc_isspace_l)(int ch,
                                     __locale_t locale) {
#ifdef __BUILDING_LIBC
	(void)locale;
	COMPILER_IMPURE();
	return isspace(ch);
#else /* __BUILDING_LIBC */
#if defined(__CRT_HAVE___ctype_b_loc) && defined(__CRT_GLC)
#include <hybrid/byteorder.h>
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	return locale->__ctype_b[ch] & (1 << 5);
#else /* __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__ */
	return locale->__ctype_b[ch] & (1 << 13);
#endif /* __BYTE_ORDER__ != __ORDER_BIG_ENDIAN__ */
#elif defined(__CRT_HAVE___locale_ctype_ptr_l) && defined(__CRT_CYG)
	return ((__locale_ctype_ptr_l(locale) + 1)[ch & 0xff] & 010) != 0;
#elif defined(__CRT_HAVE__isctype_l) && defined(__CRT_DOS)
	return _isctype_l(ch, 0x0008, locale);
#else
	(void)locale;
	COMPILER_IMPURE();
	return isspace(ch);
#endif
#endif /* !__BUILDING_LIBC */
}
INTERN ATTR_SECTION(".text.crt.unicode.locale.ctype") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBCCALL libc_isupper_l)(int ch,
                                     __locale_t locale) {
#ifdef __BUILDING_LIBC
	(void)locale;
	COMPILER_IMPURE();
	return isupper(ch);
#else /* __BUILDING_LIBC */
#if defined(__CRT_HAVE___ctype_b_loc) && defined(__CRT_GLC)
#include <hybrid/byteorder.h>
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	return locale->__ctype_b[ch] & (1 << 0);
#else /* __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__ */
	return locale->__ctype_b[ch] & (1 << 8);
#endif /* __BYTE_ORDER__ != __ORDER_BIG_ENDIAN__ */
#elif defined(__CRT_HAVE___locale_ctype_ptr_l) && defined(__CRT_CYG)
	return ((__locale_ctype_ptr_l(locale) + 1)[ch & 0xff] & 3) == 1;
#elif defined(__CRT_HAVE__isctype_l) && defined(__CRT_DOS)
	return _isctype_l(ch, 0x0001, locale);
#else
	(void)locale;
	COMPILER_IMPURE();
	return isupper(ch);
#endif
#endif /* !__BUILDING_LIBC */
}
INTERN ATTR_SECTION(".text.crt.unicode.locale.ctype") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBCCALL libc_islower_l)(int ch,
                                     __locale_t locale) {
#ifdef __BUILDING_LIBC
	(void)locale;
	COMPILER_IMPURE();
	return islower(ch);
#else /* __BUILDING_LIBC */
#if defined(__CRT_HAVE___ctype_b_loc) && defined(__CRT_GLC)
#include <hybrid/byteorder.h>
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	return locale->__ctype_b[ch] & (1 << 1);
#else /* __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__ */
	return locale->__ctype_b[ch] & (1 << 9);
#endif /* __BYTE_ORDER__ != __ORDER_BIG_ENDIAN__ */
#elif defined(__CRT_HAVE___locale_ctype_ptr_l) && defined(__CRT_CYG)
	return ((__locale_ctype_ptr_l(locale) + 1)[ch & 0xff] & 3) == 2;
#elif defined(__CRT_HAVE__isctype_l) && defined(__CRT_DOS)
	return _isctype_l(ch, 0x0002, locale);
#else
	(void)locale;
	COMPILER_IMPURE();
	return islower(ch);
#endif
#endif /* !__BUILDING_LIBC */
}
INTERN ATTR_SECTION(".text.crt.unicode.locale.ctype") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBCCALL libc_isalpha_l)(int ch,
                                     __locale_t locale) {
#ifdef __BUILDING_LIBC
	(void)locale;
	COMPILER_IMPURE();
	return isalpha(ch);
#else /* __BUILDING_LIBC */
#if defined(__CRT_HAVE___ctype_b_loc) && defined(__CRT_GLC)
#include <hybrid/byteorder.h>
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	return locale->__ctype_b[ch] & (1 << 2);
#else /* __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__ */
	return locale->__ctype_b[ch] & (1 << 10);
#endif /* __BYTE_ORDER__ != __ORDER_BIG_ENDIAN__ */
#elif defined(__CRT_HAVE___locale_ctype_ptr_l) && defined(__CRT_CYG)
	return ((__locale_ctype_ptr_l(locale) + 1)[ch & 0xff] & 3) != 0;
#elif defined(__CRT_HAVE__isctype_l) && defined(__CRT_DOS)
	return _isctype_l(ch, 0x0103, locale);
#else
	(void)locale;
	COMPILER_IMPURE();
	return isalpha(ch);
#endif
#endif /* !__BUILDING_LIBC */
}
INTERN ATTR_SECTION(".text.crt.unicode.locale.ctype") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBCCALL libc_isdigit_l)(int ch,
                                     __locale_t locale) {
#ifdef __BUILDING_LIBC
	(void)locale;
	COMPILER_IMPURE();
	return isdigit(ch);
#else /* __BUILDING_LIBC */
#if defined(__CRT_HAVE___ctype_b_loc) && defined(__CRT_GLC)
#include <hybrid/byteorder.h>
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	return locale->__ctype_b[ch] & (1 << 3);
#else /* __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__ */
	return locale->__ctype_b[ch] & (1 << 11);
#endif /* __BYTE_ORDER__ != __ORDER_BIG_ENDIAN__ */
#elif defined(__CRT_HAVE___locale_ctype_ptr_l) && defined(__CRT_CYG)
	return ((__locale_ctype_ptr_l(locale) + 1)[ch & 0xff] & 4) != 0;
#elif defined(__CRT_HAVE__isctype_l) && defined(__CRT_DOS)
	return _isctype_l(ch, 0x0004, locale);
#else
	(void)locale;
	COMPILER_IMPURE();
	return isdigit(ch);
#endif
#endif /* !__BUILDING_LIBC */
}
INTERN ATTR_SECTION(".text.crt.unicode.locale.ctype") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBCCALL libc_isxdigit_l)(int ch,
                                      __locale_t locale) {
#ifdef __BUILDING_LIBC
	(void)locale;
	COMPILER_IMPURE();
	return isxdigit(ch);
#else /* __BUILDING_LIBC */
#if defined(__CRT_HAVE___ctype_b_loc) && defined(__CRT_GLC)
#include <hybrid/byteorder.h>
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	return locale->__ctype_b[ch] & (1 << 4);
#else /* __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__ */
	return locale->__ctype_b[ch] & (1 << 12);
#endif /* __BYTE_ORDER__ != __ORDER_BIG_ENDIAN__ */
#elif defined(__CRT_HAVE___locale_ctype_ptr_l) && defined(__CRT_CYG)
	return ((__locale_ctype_ptr_l(locale) + 1)[ch & 0xff] & 0104) != 0;
#elif defined(__CRT_HAVE__isctype_l) && defined(__CRT_DOS)
	return _isctype_l(ch, 0x0080, locale);
#else
	(void)locale;
	COMPILER_IMPURE();
	return isxdigit(ch);
#endif
#endif /* !__BUILDING_LIBC */
}
INTERN ATTR_SECTION(".text.crt.unicode.locale.ctype") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBCCALL libc_isalnum_l)(int ch,
                                     __locale_t locale) {
#ifdef __BUILDING_LIBC
	(void)locale;
	COMPILER_IMPURE();
	return isalnum(ch);
#else /* __BUILDING_LIBC */
#if defined(__CRT_HAVE___ctype_b_loc) && defined(__CRT_GLC)
#include <hybrid/byteorder.h>
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	return locale->__ctype_b[ch] & (1 << 11);
#else /* __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__ */
	return locale->__ctype_b[ch] & (1 << 3);
#endif /* __BYTE_ORDER__ != __ORDER_BIG_ENDIAN__ */
#elif defined(__CRT_HAVE___locale_ctype_ptr_l) && defined(__CRT_CYG)
	return ((__locale_ctype_ptr_l(locale) + 1)[ch & 0xff] & 7) != 0;
#elif defined(__CRT_HAVE__isctype_l) && defined(__CRT_DOS)
	return _isctype_l(ch, 0x0107, locale);
#else
	(void)locale;
	COMPILER_IMPURE();
	return isalnum(ch);
#endif
#endif /* !__BUILDING_LIBC */
}
INTERN ATTR_SECTION(".text.crt.unicode.locale.ctype") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBCCALL libc_ispunct_l)(int ch,
                                     __locale_t locale) {
#ifdef __BUILDING_LIBC
	(void)locale;
	COMPILER_IMPURE();
	return ispunct(ch);
#else /* __BUILDING_LIBC */
#if defined(__CRT_HAVE___ctype_b_loc) && defined(__CRT_GLC)
#include <hybrid/byteorder.h>
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	return locale->__ctype_b[ch] & (1 << 10);
#else /* __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__ */
	return locale->__ctype_b[ch] & (1 << 2);
#endif /* __BYTE_ORDER__ != __ORDER_BIG_ENDIAN__ */
#elif defined(__CRT_HAVE___locale_ctype_ptr_l) && defined(__CRT_CYG)
	return ((__locale_ctype_ptr_l(locale) + 1)[ch & 0xff] & 020) != 0;
#elif defined(__CRT_HAVE__isctype_l) && defined(__CRT_DOS)
	return _isctype_l(ch, 0x0010, locale);
#else
	(void)locale;
	COMPILER_IMPURE();
	return ispunct(ch);
#endif
#endif /* !__BUILDING_LIBC */
}
INTERN ATTR_SECTION(".text.crt.unicode.locale.ctype") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBCCALL libc_isgraph_l)(int ch,
                                     __locale_t locale) {
#ifdef __BUILDING_LIBC
	(void)locale;
	COMPILER_IMPURE();
	return isgraph(ch);
#else /* __BUILDING_LIBC */
#if defined(__CRT_HAVE___ctype_b_loc) && defined(__CRT_GLC)
#include <hybrid/byteorder.h>
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	return locale->__ctype_b[ch] & (1 << 7);
#else /* __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__ */
	return locale->__ctype_b[ch] & (1 << 15);
#endif /* __BYTE_ORDER__ != __ORDER_BIG_ENDIAN__ */
#elif defined(__CRT_HAVE___locale_ctype_ptr_l) && defined(__CRT_CYG)
	return ((__locale_ctype_ptr_l(locale) + 1)[ch & 0xff] & 027) != 0;
#elif defined(__CRT_HAVE__isctype_l) && defined(__CRT_DOS)
	return _isctype_l(ch, 0x0117, locale);
#else
	(void)locale;
	COMPILER_IMPURE();
	return isgraph(ch);
#endif
#endif /* !__BUILDING_LIBC */
}
INTERN ATTR_SECTION(".text.crt.unicode.locale.ctype") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBCCALL libc_isprint_l)(int ch,
                                     __locale_t locale) {
#ifdef __BUILDING_LIBC
	(void)locale;
	COMPILER_IMPURE();
	return isprint(ch);
#else /* __BUILDING_LIBC */
#if defined(__CRT_HAVE___ctype_b_loc) && defined(__CRT_GLC)
#include <hybrid/byteorder.h>
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	return locale->__ctype_b[ch] & (1 << 6);
#else /* __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__ */
	return locale->__ctype_b[ch] & (1 << 14);
#endif /* __BYTE_ORDER__ != __ORDER_BIG_ENDIAN__ */
#elif defined(__CRT_HAVE___locale_ctype_ptr_l) && defined(__CRT_CYG)
	return ((__locale_ctype_ptr_l(locale) + 1)[ch & 0xff] & 0227) != 0;
#elif defined(__CRT_HAVE__isctype_l) && defined(__CRT_DOS)
	return _isctype_l(ch, 0x0157, locale);
#else
	(void)locale;
	COMPILER_IMPURE();
	return isprint(ch);
#endif
#endif /* !__BUILDING_LIBC */
}
INTERN ATTR_SECTION(".text.crt.unicode.locale.ctype") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBCCALL libc_isblank_l)(int ch,
                                     __locale_t locale) {
#ifdef __BUILDING_LIBC
	(void)locale;
	COMPILER_IMPURE();
	return isblank(ch);
#else /* __BUILDING_LIBC */
#if defined(__CRT_HAVE___ctype_b_loc) && defined(__CRT_GLC)
#include <hybrid/byteorder.h>
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	return locale->__ctype_b[ch] & (1 << 8);
#else /* __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__ */
	return locale->__ctype_b[ch] & (1 << 0);
#endif /* __BYTE_ORDER__ != __ORDER_BIG_ENDIAN__ */
#elif defined(__CRT_HAVE___locale_ctype_ptr_l) && defined(__CRT_CYG)
	return ((__locale_ctype_ptr_l(locale) + 1)[ch & 0xff] & 0200) != 0 || ch == '\t';
#else
	(void)locale;
	COMPILER_IMPURE();
	return isblank(ch);
#endif
#endif /* !__BUILDING_LIBC */
}
INTERN ATTR_SECTION(".text.crt.unicode.locale.ctype") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBCCALL libc_tolower_l)(int ch,
                                     __locale_t locale) {
	/* TODO: GLC has a variant for this! */
	(void)locale;
	COMPILER_IMPURE();
	return tolower(ch);
}
INTERN ATTR_SECTION(".text.crt.unicode.locale.ctype") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBCCALL libc_toupper_l)(int ch,
                                     __locale_t locale) {
	/* TODO: GLC has a variant for this! */
	(void)locale;
	COMPILER_IMPURE();
	return toupper(ch);
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
