/* HASH CRC-32:0xb4c96d7e */
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
#ifndef GUARD_LIBC_AUTO_DOSABI_CTYPE_C
#define GUARD_LIBC_AUTO_DOSABI_CTYPE_C 1

#include "../../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../../user/ctype.h"

DECL_BEGIN

INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.ctype") ATTR_PURE WUNUSED char const *
NOTHROW_NCX(LIBDCALL libd___locale_ctype_ptr_l)(locale_t locale) {
	return libc___locale_ctype_ptr_l(locale);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBDCALL libd__isctype)(int ch,
                                int mask) {
	return libc__isctype(ch, mask);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.ctype") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBDCALL libd__isctype_l)(int ch,
                                      int mask,
                                      locale_t locale) {
	return libc__isctype_l(ch, mask, locale);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBDCALL libd_iscntrl)(int ch) {
	return libc_iscntrl(ch);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBDCALL libd_isspace)(int ch) {
	return libc_isspace(ch);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBDCALL libd_isupper)(int ch) {
	return libc_isupper(ch);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBDCALL libd_islower)(int ch) {
	return libc_islower(ch);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBDCALL libd_isalpha)(int ch) {
	return libc_isalpha(ch);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBDCALL libd_isdigit)(int ch) {
	return libc_isdigit(ch);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBDCALL libd_isxdigit)(int ch) {
	return libc_isxdigit(ch);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBDCALL libd_isalnum)(int ch) {
	return libc_isalnum(ch);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBDCALL libd_ispunct)(int ch) {
	return libc_ispunct(ch);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBDCALL libd_isgraph)(int ch) {
	return libc_isgraph(ch);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBDCALL libd_isprint)(int ch) {
	return libc_isprint(ch);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBDCALL libd_tolower)(int ch) {
	return libc_tolower(ch);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBDCALL libd_toupper)(int ch) {
	return libc_toupper(ch);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBDCALL libd_isblank)(int ch) {
	return libc_isblank(ch);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.ctype") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBDCALL libd_iscntrl_l)(int ch,
                                     __locale_t locale) {
	return libc_iscntrl_l(ch, locale);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.ctype") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBDCALL libd_isspace_l)(int ch,
                                     __locale_t locale) {
	return libc_isspace_l(ch, locale);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.ctype") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBDCALL libd_isupper_l)(int ch,
                                     __locale_t locale) {
	return libc_isupper_l(ch, locale);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.ctype") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBDCALL libd_islower_l)(int ch,
                                     __locale_t locale) {
	return libc_islower_l(ch, locale);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.ctype") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBDCALL libd_isalpha_l)(int ch,
                                     __locale_t locale) {
	return libc_isalpha_l(ch, locale);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.ctype") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBDCALL libd_isdigit_l)(int ch,
                                     __locale_t locale) {
	return libc_isdigit_l(ch, locale);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.ctype") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBDCALL libd_isxdigit_l)(int ch,
                                      __locale_t locale) {
	return libc_isxdigit_l(ch, locale);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.ctype") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBDCALL libd_isalnum_l)(int ch,
                                     __locale_t locale) {
	return libc_isalnum_l(ch, locale);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.ctype") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBDCALL libd_ispunct_l)(int ch,
                                     __locale_t locale) {
	return libc_ispunct_l(ch, locale);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.ctype") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBDCALL libd_isgraph_l)(int ch,
                                     __locale_t locale) {
	return libc_isgraph_l(ch, locale);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.ctype") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBDCALL libd_isprint_l)(int ch,
                                     __locale_t locale) {
	return libc_isprint_l(ch, locale);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.ctype") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBDCALL libd_isblank_l)(int ch,
                                     __locale_t locale) {
	return libc_isblank_l(ch, locale);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.ctype") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBDCALL libd_tolower_l)(int ch,
                                     __locale_t locale) {
	return libc_tolower_l(ch, locale);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.ctype") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBDCALL libd_toupper_l)(int ch,
                                     __locale_t locale) {
	return libc_toupper_l(ch, locale);
}
/* Returns non-zero if `(C & ~0x7f) == 0' */
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.ctype") ATTR_CONST int
NOTHROW(LIBDCALL libd_isascii)(int c) {
	return libc_isascii(c);
}
/* Re-returns `C & 0x7f' */
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.ctype") ATTR_CONST int
NOTHROW(LIBDCALL libd_toascii)(int c) {
	return libc_toascii(c);
}

DECL_END

DEFINE_PUBLIC_ALIAS(DOS$__locale_ctype_ptr_l, libd___locale_ctype_ptr_l);
DEFINE_PUBLIC_ALIAS(DOS$_isctype, libd__isctype);
DEFINE_PUBLIC_ALIAS(DOS$_isctype_l, libd__isctype_l);
DEFINE_PUBLIC_ALIAS(DOS$iscntrl, libd_iscntrl);
DEFINE_PUBLIC_ALIAS(DOS$isspace, libd_isspace);
DEFINE_PUBLIC_ALIAS(DOS$isupper, libd_isupper);
DEFINE_PUBLIC_ALIAS(DOS$islower, libd_islower);
DEFINE_PUBLIC_ALIAS(DOS$isalpha, libd_isalpha);
DEFINE_PUBLIC_ALIAS(DOS$isdigit, libd_isdigit);
DEFINE_PUBLIC_ALIAS(DOS$isxdigit, libd_isxdigit);
DEFINE_PUBLIC_ALIAS(DOS$isalnum, libd_isalnum);
DEFINE_PUBLIC_ALIAS(DOS$ispunct, libd_ispunct);
DEFINE_PUBLIC_ALIAS(DOS$isgraph, libd_isgraph);
DEFINE_PUBLIC_ALIAS(DOS$isprint, libd_isprint);
DEFINE_PUBLIC_ALIAS(DOS$_tolower, libd_tolower);
DEFINE_PUBLIC_ALIAS(DOS$tolower, libd_tolower);
DEFINE_PUBLIC_ALIAS(DOS$_toupper, libd_toupper);
DEFINE_PUBLIC_ALIAS(DOS$toupper, libd_toupper);
DEFINE_PUBLIC_ALIAS(DOS$isblank, libd_isblank);
DEFINE_PUBLIC_ALIAS(DOS$__iscntrl_l, libd_iscntrl_l);
DEFINE_PUBLIC_ALIAS(DOS$iscntrl_l, libd_iscntrl_l);
DEFINE_PUBLIC_ALIAS(DOS$__isspace_l, libd_isspace_l);
DEFINE_PUBLIC_ALIAS(DOS$isspace_l, libd_isspace_l);
DEFINE_PUBLIC_ALIAS(DOS$__isupper_l, libd_isupper_l);
DEFINE_PUBLIC_ALIAS(DOS$isupper_l, libd_isupper_l);
DEFINE_PUBLIC_ALIAS(DOS$__islower_l, libd_islower_l);
DEFINE_PUBLIC_ALIAS(DOS$islower_l, libd_islower_l);
DEFINE_PUBLIC_ALIAS(DOS$__isalpha_l, libd_isalpha_l);
DEFINE_PUBLIC_ALIAS(DOS$isalpha_l, libd_isalpha_l);
DEFINE_PUBLIC_ALIAS(DOS$__isdigit_l, libd_isdigit_l);
DEFINE_PUBLIC_ALIAS(DOS$isdigit_l, libd_isdigit_l);
DEFINE_PUBLIC_ALIAS(DOS$__isxdigit_l, libd_isxdigit_l);
DEFINE_PUBLIC_ALIAS(DOS$isxdigit_l, libd_isxdigit_l);
DEFINE_PUBLIC_ALIAS(DOS$__isalnum_l, libd_isalnum_l);
DEFINE_PUBLIC_ALIAS(DOS$isalnum_l, libd_isalnum_l);
DEFINE_PUBLIC_ALIAS(DOS$__ispunct_l, libd_ispunct_l);
DEFINE_PUBLIC_ALIAS(DOS$ispunct_l, libd_ispunct_l);
DEFINE_PUBLIC_ALIAS(DOS$__isgraph_l, libd_isgraph_l);
DEFINE_PUBLIC_ALIAS(DOS$isgraph_l, libd_isgraph_l);
DEFINE_PUBLIC_ALIAS(DOS$__isprint_l, libd_isprint_l);
DEFINE_PUBLIC_ALIAS(DOS$isprint_l, libd_isprint_l);
DEFINE_PUBLIC_ALIAS(DOS$__isblank_l, libd_isblank_l);
DEFINE_PUBLIC_ALIAS(DOS$isblank_l, libd_isblank_l);
DEFINE_PUBLIC_ALIAS(DOS$_tolower_l, libd_tolower_l);
DEFINE_PUBLIC_ALIAS(DOS$__tolower_l, libd_tolower_l);
DEFINE_PUBLIC_ALIAS(DOS$tolower_l, libd_tolower_l);
DEFINE_PUBLIC_ALIAS(DOS$_toupper_l, libd_toupper_l);
DEFINE_PUBLIC_ALIAS(DOS$__toupper_l, libd_toupper_l);
DEFINE_PUBLIC_ALIAS(DOS$toupper_l, libd_toupper_l);
DEFINE_PUBLIC_ALIAS(DOS$isascii, libd_isascii);
DEFINE_PUBLIC_ALIAS(DOS$toascii, libd_toascii);

#endif /* !GUARD_LIBC_AUTO_DOSABI_CTYPE_C */
