/* HASH CRC-32:0x5192b775 */
/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_AUTO_MBCTYPE_C
#define GUARD_LIBC_AUTO_MBCTYPE_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../user/mbctype.h"
#include "../user/ctype.h"

DECL_BEGIN

#include "../libc/globals.h"
#ifndef __KERNEL__
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBCCALL libc__getmbcp_l)(locale_t locale) {
	if (locale == NULL)
		return libc__getmbcp();
	return 65001; /* ??? */
}
/* @param: ch: Should actually be `unsigned char ch' */
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBCCALL libc__ismbbkalnum)(unsigned int ch) {
	return libc__ismbbkalnum_l(ch, NULL);
}
/* @param: ch: Should actually be `unsigned char ch' */
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBCCALL libc__ismbbkana)(unsigned int ch) {
	return libc__ismbbkana_l(ch, NULL);
}
/* @param: ch: Should actually be `unsigned char ch' */
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBCCALL libc__ismbbkpunct)(unsigned int ch) {
	return libc__ismbbkpunct_l(ch, NULL);
}
/* @param: ch: Should actually be `unsigned char ch' */
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBCCALL libc__ismbbalpha)(unsigned int ch) {
	return libc__ismbbalpha_l(ch, NULL);
}
/* @param: ch: Should actually be `unsigned char ch' */
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBCCALL libc__ismbbpunct)(unsigned int ch) {
	return libc__ismbbpunct_l(ch, NULL);
}
/* @param: ch: Should actually be `unsigned char ch' */
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBCCALL libc__ismbbblank)(unsigned int ch) {
	return libc__ismbbblank_l(ch, NULL);
}
/* @param: ch: Should actually be `unsigned char ch' */
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBCCALL libc__ismbbalnum)(unsigned int ch) {
	return libc__ismbbalnum_l(ch, NULL);
}
/* @param: ch: Should actually be `unsigned char ch' */
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBCCALL libc__ismbbprint)(unsigned int ch) {
	return libc__ismbbprint_l(ch, NULL);
}
/* @param: ch: Should actually be `unsigned char ch' */
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBCCALL libc__ismbbgraph)(unsigned int ch) {
	return libc__ismbbgraph_l(ch, NULL);
}
/* @param: ch: Should actually be `unsigned char ch' */
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBCCALL libc__ismbblead)(unsigned int ch) {
	return libc__ismbblead_l(ch, NULL);
}
/* @param: ch: Should actually be `unsigned char ch' */
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBCCALL libc__ismbbtrail)(unsigned int ch) {
	return libc__ismbbtrail_l(ch, NULL);
}
#include <libc/template/mbctype.h>
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED unsigned char
NOTHROW_NCX(LIBCCALL libc__get_mbbtype_l)(unsigned char ch,
                                          locale_t locale) {
	if (locale == NULL)
		return (__LOCAL__mbctype + 1)[ch];
	return 0; /* XXX: locale support */
}
/* @param: ch: Should actually be `unsigned char ch' */
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBCCALL libc__ismbblead_l)(unsigned int ch,
                                        locale_t locale) {
	return libc__get_mbbtype_l((unsigned char)ch, locale) & 0x04;
}
/* @param: ch: Should actually be `unsigned char ch' */
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBCCALL libc__ismbbtrail_l)(unsigned int ch,
                                         locale_t locale) {
	return libc__get_mbbtype_l((unsigned char)ch, locale) & 0x08;
}
/* @param: ch: Should actually be `unsigned char ch' */
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBCCALL libc__ismbbkalnum_l)(unsigned int ch,
                                          locale_t locale) {
	return libc__get_mbbtype_l((unsigned char)ch, locale) & 0x01;
}
/* @param: ch: Should actually be `unsigned char ch' */
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBCCALL libc__ismbbkana_l)(unsigned int ch,
                                        locale_t locale) {
	return libc__get_mbbtype_l((unsigned char)ch, locale) & (0x01 | 0x02);
}
/* @param: ch: Should actually be `unsigned char ch' */
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBCCALL libc__ismbbkpunct_l)(unsigned int ch,
                                          locale_t locale) {
	return libc__get_mbbtype_l((unsigned char)ch, locale) & 0x02;
}
/* @param: ch: Should actually be `unsigned char ch' */
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBCCALL libc__ismbbalpha_l)(unsigned int ch,
                                         locale_t locale) {
	return libc_isalpha_l(ch, locale) || libc__ismbbkalnum_l(ch, locale);
}
/* @param: ch: Should actually be `unsigned char ch' */
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBCCALL libc__ismbbpunct_l)(unsigned int ch,
                                         locale_t locale) {
	return libc_ispunct_l(ch, locale) || libc__ismbbkpunct_l(ch, locale);
}
/* @param: ch: Should actually be `unsigned char ch' */
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBCCALL libc__ismbbblank_l)(unsigned int ch,
                                         locale_t locale) {
	return libc_isblank_l(ch, locale) || ch == '\t';
}
/* @param: ch: Should actually be `unsigned char ch' */
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBCCALL libc__ismbbalnum_l)(unsigned int ch,
                                         locale_t locale) {
	return libc_isalnum_l(ch, locale) || libc__ismbbkalnum_l(ch, locale);
}
/* @param: ch: Should actually be `unsigned char ch' */
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBCCALL libc__ismbbprint_l)(unsigned int ch,
                                         locale_t locale) {
	return libc_isprint_l(ch, locale) || libc__ismbbkana_l(ch, locale);
}
/* @param: ch: Should actually be `unsigned char ch' */
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBCCALL libc__ismbbgraph_l)(unsigned int ch,
                                         locale_t locale) {
	return libc_isgraph_l(ch, locale) || libc__ismbbkana_l(ch, locale);
}
#endif /* !__KERNEL__ */

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(_ismbbkalnum, libc__ismbbkalnum);
DEFINE_PUBLIC_ALIAS(_ismbbkprint, libc__ismbbkana);
DEFINE_PUBLIC_ALIAS(_ismbbkana, libc__ismbbkana);
DEFINE_PUBLIC_ALIAS(_ismbbkpunct, libc__ismbbkpunct);
DEFINE_PUBLIC_ALIAS(_ismbbalpha, libc__ismbbalpha);
DEFINE_PUBLIC_ALIAS(_ismbbpunct, libc__ismbbpunct);
DEFINE_PUBLIC_ALIAS(_ismbbblank, libc__ismbbblank);
DEFINE_PUBLIC_ALIAS(_ismbbalnum, libc__ismbbalnum);
DEFINE_PUBLIC_ALIAS(_ismbbprint, libc__ismbbprint);
DEFINE_PUBLIC_ALIAS(_ismbbgraph, libc__ismbbgraph);
DEFINE_PUBLIC_ALIAS(_ismbblead, libc__ismbblead);
DEFINE_PUBLIC_ALIAS(_ismbbtrail, libc__ismbbtrail);
DEFINE_PUBLIC_ALIAS(_ismbblead_l, libc__ismbblead_l);
DEFINE_PUBLIC_ALIAS(_ismbbtrail_l, libc__ismbbtrail_l);
DEFINE_PUBLIC_ALIAS(_ismbbkalnum_l, libc__ismbbkalnum_l);
DEFINE_PUBLIC_ALIAS(_ismbbkprint_l, libc__ismbbkana_l);
DEFINE_PUBLIC_ALIAS(_ismbbkana_l, libc__ismbbkana_l);
DEFINE_PUBLIC_ALIAS(_ismbbkpunct_l, libc__ismbbkpunct_l);
DEFINE_PUBLIC_ALIAS(_ismbbalpha_l, libc__ismbbalpha_l);
DEFINE_PUBLIC_ALIAS(_ismbbpunct_l, libc__ismbbpunct_l);
DEFINE_PUBLIC_ALIAS(_ismbbblank_l, libc__ismbbblank_l);
DEFINE_PUBLIC_ALIAS(_ismbbalnum_l, libc__ismbbalnum_l);
DEFINE_PUBLIC_ALIAS(_ismbbprint_l, libc__ismbbprint_l);
DEFINE_PUBLIC_ALIAS(_ismbbgraph_l, libc__ismbbgraph_l);
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_MBCTYPE_C */
