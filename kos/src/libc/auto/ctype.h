/* HASH CRC-32:0xdf13c6a9 */
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
#ifndef GUARD_LIBC_AUTO_CTYPE_H
#define GUARD_LIBC_AUTO_CTYPE_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <ctype.h>

DECL_BEGIN

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
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED char const *NOTHROW_NCX(LIBDCALL libd___locale_ctype_ptr_l)(locale_t locale);
/* >> iscntrl(3) */
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBDCALL libd_iscntrl)(int ch);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> iscntrl(3) */
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBCCALL libc_iscntrl)(int ch);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> isspace(3) */
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBDCALL libd_isspace)(int ch);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> isspace(3) */
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBCCALL libc_isspace)(int ch);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> isupper(3) */
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBDCALL libd_isupper)(int ch);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> isupper(3) */
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBCCALL libc_isupper)(int ch);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> islower(3) */
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBDCALL libd_islower)(int ch);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> islower(3) */
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBCCALL libc_islower)(int ch);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> isalpha(3) */
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBDCALL libd_isalpha)(int ch);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> isalpha(3) */
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBCCALL libc_isalpha)(int ch);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> isdigit(3) */
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBDCALL libd_isdigit)(int ch);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> isdigit(3) */
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBCCALL libc_isdigit)(int ch);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> isxdigit(3) */
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBDCALL libd_isxdigit)(int ch);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> isxdigit(3) */
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBCCALL libc_isxdigit)(int ch);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> isalnum(3) */
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBDCALL libd_isalnum)(int ch);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> isalnum(3) */
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBCCALL libc_isalnum)(int ch);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> ispunct(3) */
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBDCALL libd_ispunct)(int ch);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> ispunct(3) */
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBCCALL libc_ispunct)(int ch);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> isgraph(3) */
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBDCALL libd_isgraph)(int ch);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> isgraph(3) */
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBCCALL libc_isgraph)(int ch);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> isprint(3) */
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBDCALL libd_isprint)(int ch);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> isprint(3) */
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBCCALL libc_isprint)(int ch);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> tolower(3) */
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBDCALL libd_tolower)(int ch);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> tolower(3) */
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBCCALL libc_tolower)(int ch);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> toupper(3) */
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBDCALL libd_toupper)(int ch);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> toupper(3) */
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBCCALL libc_toupper)(int ch);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> isblank(3) */
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBDCALL libd_isblank)(int ch);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> isblank(3) */
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBCCALL libc_isblank)(int ch);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> iscntrl_l(3) */
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBDCALL libd_iscntrl_l)(int ch, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> iscntrl_l(3) */
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBCCALL libc_iscntrl_l)(int ch, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> isspace_l(3) */
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBDCALL libd_isspace_l)(int ch, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> isspace_l(3) */
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBCCALL libc_isspace_l)(int ch, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> isupper_l(3) */
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBDCALL libd_isupper_l)(int ch, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> isupper_l(3) */
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBCCALL libc_isupper_l)(int ch, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> islower_l(3) */
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBDCALL libd_islower_l)(int ch, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> islower_l(3) */
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBCCALL libc_islower_l)(int ch, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> isalpha_l(3) */
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBDCALL libd_isalpha_l)(int ch, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> isalpha_l(3) */
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBCCALL libc_isalpha_l)(int ch, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> isdigit_l(3) */
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBDCALL libd_isdigit_l)(int ch, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> isdigit_l(3) */
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBCCALL libc_isdigit_l)(int ch, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> isxdigit_l(3) */
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBDCALL libd_isxdigit_l)(int ch, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> isxdigit_l(3) */
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBCCALL libc_isxdigit_l)(int ch, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> isalnum_l(3) */
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBDCALL libd_isalnum_l)(int ch, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> isalnum_l(3) */
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBCCALL libc_isalnum_l)(int ch, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> ispunct_l(3) */
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBDCALL libd_ispunct_l)(int ch, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> ispunct_l(3) */
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBCCALL libc_ispunct_l)(int ch, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> isgraph_l(3) */
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBDCALL libd_isgraph_l)(int ch, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> isgraph_l(3) */
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBCCALL libc_isgraph_l)(int ch, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> isprint_l(3) */
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBDCALL libd_isprint_l)(int ch, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> isprint_l(3) */
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBCCALL libc_isprint_l)(int ch, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> isblank_l(3) */
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBDCALL libd_isblank_l)(int ch, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> isblank_l(3) */
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBCCALL libc_isblank_l)(int ch, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> tolower_l(3) */
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBDCALL libd_tolower_l)(int ch, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> tolower_l(3) */
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBCCALL libc_tolower_l)(int ch, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> toupper_l(3) */
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBDCALL libd_toupper_l)(int ch, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> toupper_l(3) */
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBCCALL libc_toupper_l)(int ch, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> issymstrt(3)
 * Test if `ch' can appear at the start of a symbol/keyword/identifier */
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBDCALL libd___iscsymf)(int ch);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> issymstrt(3)
 * Test if `ch' can appear at the start of a symbol/keyword/identifier */
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBCCALL libc___iscsymf)(int ch);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> issymcont(3)
 * Test if `ch' can appear in the middle of a symbol/keyword/identifier */
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBDCALL libd___iscsym)(int ch);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> issymcont(3)
 * Test if `ch' can appear in the middle of a symbol/keyword/identifier */
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBCCALL libc___iscsym)(int ch);
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
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> _tolower(3)
 * Same as `tolower(3)', but the caller must ensure that `isupper(ch)' */
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBDCALL libd__tolower)(int ch);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> _tolower(3)
 * Same as `tolower(3)', but the caller must ensure that `isupper(ch)' */
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBCCALL libc__tolower)(int ch);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> _toupper(3)
 * Same as `toupper(3)', but the caller must ensure that `islower(ch)' */
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBDCALL libd__toupper)(int ch);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> _toupper(3)
 * Same as `toupper(3)', but the caller must ensure that `islower(ch)' */
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBCCALL libc__toupper)(int ch);
INTDEF ATTR_CONST WUNUSED size_t NOTHROW(LIBCCALL libc___ctype_get_mb_cur_max)(void);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF int NOTHROW_NCX(LIBDCALL libd____mb_cur_max_l_func)(locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF int NOTHROW_NCX(LIBCCALL libc____mb_cur_max_l_func)(locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBDCALL libd__chvalidator_l)(locale_t locale, int ch, int mask);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBCCALL libc__chvalidator_l)(locale_t locale, int ch, int mask);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBDCALL libd__isctype)(int ch, int mask);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBCCALL libc__isctype)(int ch, int mask);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBDCALL libd__isctype_l)(int ch, int mask, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBCCALL libc__isctype_l)(int ch, int mask, locale_t locale);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_CTYPE_H */
