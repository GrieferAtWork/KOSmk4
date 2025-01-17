/* HASH CRC-32:0xcfdaf1ff */
/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_AUTO_MBCTYPE_H
#define GUARD_LIBC_AUTO_MBCTYPE_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <mbctype.h>

DECL_BEGIN

#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF int NOTHROW_NCX(LIBDCALL libd__setmbcp)(int cp);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBCCALL libc__getmbcp_l)(locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED char32_t NOTHROW_NCX(LIBDCALL libd__mbctouni_l)(unsigned int ch, locale_t locale);
INTDEF ATTR_PURE WUNUSED unsigned int NOTHROW_NCX(LIBDCALL libd__unitombc_l)(char32_t ch, locale_t locale);
/* @param: ch: Should actually be `unsigned char ch' */
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBDCALL libd__ismbbkalnum)(unsigned int ch);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* @param: ch: Should actually be `unsigned char ch' */
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBCCALL libc__ismbbkalnum)(unsigned int ch);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* @param: ch: Should actually be `unsigned char ch' */
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBDCALL libd__ismbbkana)(unsigned int ch);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* @param: ch: Should actually be `unsigned char ch' */
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBCCALL libc__ismbbkana)(unsigned int ch);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* @param: ch: Should actually be `unsigned char ch' */
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBDCALL libd__ismbbkpunct)(unsigned int ch);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* @param: ch: Should actually be `unsigned char ch' */
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBCCALL libc__ismbbkpunct)(unsigned int ch);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* @param: ch: Should actually be `unsigned char ch' */
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBDCALL libd__ismbbalpha)(unsigned int ch);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* @param: ch: Should actually be `unsigned char ch' */
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBCCALL libc__ismbbalpha)(unsigned int ch);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* @param: ch: Should actually be `unsigned char ch' */
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBDCALL libd__ismbbpunct)(unsigned int ch);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* @param: ch: Should actually be `unsigned char ch' */
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBCCALL libc__ismbbpunct)(unsigned int ch);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* @param: ch: Should actually be `unsigned char ch' */
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBDCALL libd__ismbbblank)(unsigned int ch);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* @param: ch: Should actually be `unsigned char ch' */
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBCCALL libc__ismbbblank)(unsigned int ch);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* @param: ch: Should actually be `unsigned char ch' */
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBDCALL libd__ismbbalnum)(unsigned int ch);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* @param: ch: Should actually be `unsigned char ch' */
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBCCALL libc__ismbbalnum)(unsigned int ch);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* @param: ch: Should actually be `unsigned char ch' */
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBDCALL libd__ismbbprint)(unsigned int ch);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* @param: ch: Should actually be `unsigned char ch' */
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBCCALL libc__ismbbprint)(unsigned int ch);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* @param: ch: Should actually be `unsigned char ch' */
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBDCALL libd__ismbbgraph)(unsigned int ch);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* @param: ch: Should actually be `unsigned char ch' */
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBCCALL libc__ismbbgraph)(unsigned int ch);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* @param: ch: Should actually be `unsigned char ch' */
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBDCALL libd__ismbblead)(unsigned int ch);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* @param: ch: Should actually be `unsigned char ch' */
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBCCALL libc__ismbblead)(unsigned int ch);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* @param: ch: Should actually be `unsigned char ch' */
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBDCALL libd__ismbbtrail)(unsigned int ch);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* @param: ch: Should actually be `unsigned char ch' */
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBCCALL libc__ismbbtrail)(unsigned int ch);
INTDEF ATTR_PURE WUNUSED unsigned char NOTHROW_NCX(LIBCCALL libc__get_mbbtype_l)(unsigned char ch, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* @param: ch: Should actually be `unsigned char ch' */
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBDCALL libd__ismbblead_l)(unsigned int ch, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* @param: ch: Should actually be `unsigned char ch' */
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBCCALL libc__ismbblead_l)(unsigned int ch, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* @param: ch: Should actually be `unsigned char ch' */
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBDCALL libd__ismbbtrail_l)(unsigned int ch, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* @param: ch: Should actually be `unsigned char ch' */
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBCCALL libc__ismbbtrail_l)(unsigned int ch, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* @param: ch: Should actually be `unsigned char ch' */
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBDCALL libd__ismbbkalnum_l)(unsigned int ch, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* @param: ch: Should actually be `unsigned char ch' */
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBCCALL libc__ismbbkalnum_l)(unsigned int ch, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* @param: ch: Should actually be `unsigned char ch' */
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBDCALL libd__ismbbkana_l)(unsigned int ch, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* @param: ch: Should actually be `unsigned char ch' */
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBCCALL libc__ismbbkana_l)(unsigned int ch, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* @param: ch: Should actually be `unsigned char ch' */
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBDCALL libd__ismbbkpunct_l)(unsigned int ch, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* @param: ch: Should actually be `unsigned char ch' */
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBCCALL libc__ismbbkpunct_l)(unsigned int ch, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* @param: ch: Should actually be `unsigned char ch' */
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBDCALL libd__ismbbalpha_l)(unsigned int ch, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* @param: ch: Should actually be `unsigned char ch' */
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBCCALL libc__ismbbalpha_l)(unsigned int ch, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* @param: ch: Should actually be `unsigned char ch' */
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBDCALL libd__ismbbpunct_l)(unsigned int ch, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* @param: ch: Should actually be `unsigned char ch' */
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBCCALL libc__ismbbpunct_l)(unsigned int ch, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* @param: ch: Should actually be `unsigned char ch' */
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBDCALL libd__ismbbblank_l)(unsigned int ch, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* @param: ch: Should actually be `unsigned char ch' */
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBCCALL libc__ismbbblank_l)(unsigned int ch, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* @param: ch: Should actually be `unsigned char ch' */
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBDCALL libd__ismbbalnum_l)(unsigned int ch, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* @param: ch: Should actually be `unsigned char ch' */
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBCCALL libc__ismbbalnum_l)(unsigned int ch, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* @param: ch: Should actually be `unsigned char ch' */
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBDCALL libd__ismbbprint_l)(unsigned int ch, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* @param: ch: Should actually be `unsigned char ch' */
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBCCALL libc__ismbbprint_l)(unsigned int ch, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* @param: ch: Should actually be `unsigned char ch' */
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBDCALL libd__ismbbgraph_l)(unsigned int ch, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* @param: ch: Should actually be `unsigned char ch' */
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBCCALL libc__ismbbgraph_l)(unsigned int ch, locale_t locale);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_MBCTYPE_H */
