/* HASH CRC-32:0x5e9b2485 */
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
#ifndef GUARD_LIBC_AUTO_CTYPE_H
#define GUARD_LIBC_AUTO_CTYPE_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <ctype.h>

DECL_BEGIN

#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED char const *NOTHROW_NCX(LIBDCALL libd___locale_ctype_ptr_l)(locale_t locale);
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBDCALL libd__isctype)(int ch, int mask);
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBDCALL libd__isctype_l)(int ch, int mask, locale_t locale);
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBDCALL libd_iscntrl)(int ch);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBCCALL libc_iscntrl)(int ch);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBDCALL libd_isspace)(int ch);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBCCALL libc_isspace)(int ch);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBDCALL libd_isupper)(int ch);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBCCALL libc_isupper)(int ch);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBDCALL libd_islower)(int ch);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBCCALL libc_islower)(int ch);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBDCALL libd_isalpha)(int ch);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBCCALL libc_isalpha)(int ch);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBDCALL libd_isdigit)(int ch);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBCCALL libc_isdigit)(int ch);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBDCALL libd_isxdigit)(int ch);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBCCALL libc_isxdigit)(int ch);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBDCALL libd_isalnum)(int ch);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBCCALL libc_isalnum)(int ch);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBDCALL libd_ispunct)(int ch);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBCCALL libc_ispunct)(int ch);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBDCALL libd_isgraph)(int ch);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBCCALL libc_isgraph)(int ch);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBDCALL libd_isprint)(int ch);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBCCALL libc_isprint)(int ch);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBDCALL libd_tolower)(int ch);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBCCALL libc_tolower)(int ch);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBDCALL libd_toupper)(int ch);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBCCALL libc_toupper)(int ch);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBDCALL libd_isblank)(int ch);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBCCALL libc_isblank)(int ch);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBDCALL libd_iscntrl_l)(int ch, __locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBCCALL libc_iscntrl_l)(int ch, __locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBDCALL libd_isspace_l)(int ch, __locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBCCALL libc_isspace_l)(int ch, __locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBDCALL libd_isupper_l)(int ch, __locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBCCALL libc_isupper_l)(int ch, __locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBDCALL libd_islower_l)(int ch, __locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBCCALL libc_islower_l)(int ch, __locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBDCALL libd_isalpha_l)(int ch, __locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBCCALL libc_isalpha_l)(int ch, __locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBDCALL libd_isdigit_l)(int ch, __locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBCCALL libc_isdigit_l)(int ch, __locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBDCALL libd_isxdigit_l)(int ch, __locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBCCALL libc_isxdigit_l)(int ch, __locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBDCALL libd_isalnum_l)(int ch, __locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBCCALL libc_isalnum_l)(int ch, __locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBDCALL libd_ispunct_l)(int ch, __locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBCCALL libc_ispunct_l)(int ch, __locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBDCALL libd_isgraph_l)(int ch, __locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBCCALL libc_isgraph_l)(int ch, __locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBDCALL libd_isprint_l)(int ch, __locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBCCALL libc_isprint_l)(int ch, __locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBDCALL libd_isblank_l)(int ch, __locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBCCALL libc_isblank_l)(int ch, __locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBDCALL libd_tolower_l)(int ch, __locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBCCALL libc_tolower_l)(int ch, __locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBDCALL libd_toupper_l)(int ch, __locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBCCALL libc_toupper_l)(int ch, __locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Returns non-zero if `(C & ~0x7f) == 0' */
INTDEF ATTR_CONST int NOTHROW(LIBDCALL libd_isascii)(int c);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Returns non-zero if `(C & ~0x7f) == 0' */
INTDEF ATTR_CONST int NOTHROW(LIBCCALL libc_isascii)(int c);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Re-returns `C & 0x7f' */
INTDEF ATTR_CONST int NOTHROW(LIBDCALL libd_toascii)(int c);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Re-returns `C & 0x7f' */
INTDEF ATTR_CONST int NOTHROW(LIBCCALL libc_toascii)(int c);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_CTYPE_H */
