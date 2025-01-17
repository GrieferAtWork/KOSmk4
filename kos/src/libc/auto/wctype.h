/* HASH CRC-32:0x18eb0c6 */
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
#ifndef GUARD_LIBC_AUTO_WCTYPE_H
#define GUARD_LIBC_AUTO_WCTYPE_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <wctype.h>

DECL_BEGIN

/* For the sake of optimization, allow libc auto
 * functions to make direct use of unicode data. */
#ifndef __KERNEL__
#define libc_iswcntrl(ch)  __crt_iswcntrl(ch)
#define libd_iswcntrl(ch)  ((wint16_t)__crt_iswcntrl(ch))
#define libc_iswspace(ch)  __crt_iswspace(ch)
#define libd_iswspace(ch)  ((wint16_t)__crt_iswspace(ch))
#define libc_iswupper(ch)  __crt_iswupper(ch)
#define libd_iswupper(ch)  ((wint16_t)__crt_iswupper(ch))
#define libc_iswlower(ch)  __crt_iswlower(ch)
#define libd_iswlower(ch)  ((wint16_t)__crt_iswlower(ch))
#define libc_iswalpha(ch)  __crt_iswalpha(ch)
#define libd_iswalpha(ch)  ((wint16_t)__crt_iswalpha(ch))
#define libc_iswdigit(ch)  __crt_iswdigit(ch)
#define libd_iswdigit(ch)  ((wint16_t)__crt_iswdigit(ch))
#define libc_iswxdigit(ch) __crt_iswxdigit(ch)
#define libd_iswxdigit(ch) ((wint16_t)__crt_iswxdigit(ch))
#define libc_iswalnum(ch)  __crt_iswalnum(ch)
#define libd_iswalnum(ch)  ((wint16_t)__crt_iswalnum(ch))
#define libc_iswpunct(ch)  __crt_iswpunct(ch)
#define libd_iswpunct(ch)  ((wint16_t)__crt_iswpunct(ch))
#define libc_iswgraph(ch)  __crt_iswgraph(ch)
#define libd_iswgraph(ch)  ((wint16_t)__crt_iswgraph(ch))
#define libc_iswprint(ch)  __crt_iswprint(ch)
#define libd_iswprint(ch)  ((wint16_t)__crt_iswprint(ch))
#define libc_iswblank(ch)  __crt_iswblank(ch)
#define libd_iswblank(ch)  ((wint16_t)__crt_iswblank(ch))
#define libc_towlower(ch)  __crt_towlower(ch)
#define libd_towlower(ch)  ((wint16_t)__crt_towlower(ch))
#define libc_towupper(ch)  __crt_towupper(ch)
#define libd_towupper(ch)  ((wint16_t)__crt_towupper(ch))
#endif /* !__KERNEL__ */
#ifndef __KERNEL__
/* >> iswcntrl(3) */
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBDCALL libd_iswcntrl)(wint16_t wc);
/* >> iswcntrl(3) */
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBKCALL libc_iswcntrl)(wint32_t wc);
/* >> iswspace(3) */
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBDCALL libd_iswspace)(wint16_t wc);
/* >> iswspace(3) */
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBKCALL libc_iswspace)(wint32_t wc);
/* >> iswupper(3) */
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBDCALL libd_iswupper)(wint16_t wc);
/* >> iswupper(3) */
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBKCALL libc_iswupper)(wint32_t wc);
/* >> iswlower(3) */
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBDCALL libd_iswlower)(wint16_t wc);
/* >> iswlower(3) */
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBKCALL libc_iswlower)(wint32_t wc);
/* >> iswalpha(3) */
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBDCALL libd_iswalpha)(wint16_t wc);
/* >> iswalpha(3) */
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBKCALL libc_iswalpha)(wint32_t wc);
/* >> iswdigit(3) */
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBDCALL libd_iswdigit)(wint16_t wc);
/* >> iswdigit(3) */
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBKCALL libc_iswdigit)(wint32_t wc);
/* >> iswxdigit(3) */
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBDCALL libd_iswxdigit)(wint16_t wc);
/* >> iswxdigit(3) */
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBKCALL libc_iswxdigit)(wint32_t wc);
/* >> iswalnum(3) */
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBDCALL libd_iswalnum)(wint16_t wc);
/* >> iswalnum(3) */
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBKCALL libc_iswalnum)(wint32_t wc);
/* >> iswpunct(3) */
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBDCALL libd_iswpunct)(wint16_t wc);
/* >> iswpunct(3) */
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBKCALL libc_iswpunct)(wint32_t wc);
/* >> iswgraph(3) */
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBDCALL libd_iswgraph)(wint16_t wc);
/* >> iswgraph(3) */
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBKCALL libc_iswgraph)(wint32_t wc);
/* >> iswprint(3) */
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBDCALL libd_iswprint)(wint16_t wc);
/* >> iswprint(3) */
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBKCALL libc_iswprint)(wint32_t wc);
/* >> towlower(3) */
INTDEF ATTR_CONST WUNUSED wint16_t NOTHROW(LIBDCALL libd_towlower)(wint16_t wc);
/* >> towlower(3) */
INTDEF ATTR_CONST WUNUSED wint32_t NOTHROW(LIBKCALL libc_towlower)(wint32_t wc);
/* >> towupper(3) */
INTDEF ATTR_CONST WUNUSED wint16_t NOTHROW(LIBDCALL libd_towupper)(wint16_t wc);
/* >> towupper(3) */
INTDEF ATTR_CONST WUNUSED wint32_t NOTHROW(LIBKCALL libc_towupper)(wint32_t wc);
/* >> iswblank(3) */
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBDCALL libd_iswblank)(wint16_t wc);
/* >> iswblank(3) */
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBKCALL libc_iswblank)(wint32_t wc);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) wctrans_t NOTHROW_NCX(LIBDCALL libd_wctrans)(char const *prop);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) wctrans_t NOTHROW_NCX(LIBCCALL libc_wctrans)(char const *prop);
INTDEF ATTR_CONST WUNUSED wint16_t NOTHROW(LIBDCALL libd_towctrans)(wint16_t wc, wctrans_t desc);
INTDEF ATTR_CONST WUNUSED wint32_t NOTHROW(LIBKCALL libc_towctrans)(wint32_t wc, wctrans_t desc);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) wctype_t NOTHROW_NCX(LIBDCALL libd_wctype)(char const *prop);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) wctype_t NOTHROW_NCX(LIBCCALL libc_wctype)(char const *prop);
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBDCALL libd_iswctype)(wint16_t wc, wctype_t desc);
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBKCALL libc_iswctype)(wint32_t wc, wctype_t desc);
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBDCALL libd_iswascii)(wint16_t wc);
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBKCALL libc_iswascii)(wint32_t wc);
/* >> iswcntrl_l(3) */
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBDCALL libd_iswcntrl_l)(wint16_t ch, locale_t locale);
/* >> iswcntrl_l(3) */
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBKCALL libc_iswcntrl_l)(wint32_t ch, locale_t locale);
/* >> iswspace_l(3) */
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBDCALL libd_iswspace_l)(wint16_t ch, locale_t locale);
/* >> iswspace_l(3) */
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBKCALL libc_iswspace_l)(wint32_t ch, locale_t locale);
/* >> iswupper_l(3) */
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBDCALL libd_iswupper_l)(wint16_t ch, locale_t locale);
/* >> iswupper_l(3) */
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBKCALL libc_iswupper_l)(wint32_t ch, locale_t locale);
/* >> iswlower_l(3) */
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBDCALL libd_iswlower_l)(wint16_t ch, locale_t locale);
/* >> iswlower_l(3) */
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBKCALL libc_iswlower_l)(wint32_t ch, locale_t locale);
/* >> iswalpha_l(3) */
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBDCALL libd_iswalpha_l)(wint16_t ch, locale_t locale);
/* >> iswalpha_l(3) */
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBKCALL libc_iswalpha_l)(wint32_t ch, locale_t locale);
/* >> iswdigit_l(3) */
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBDCALL libd_iswdigit_l)(wint16_t ch, locale_t locale);
/* >> iswdigit_l(3) */
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBKCALL libc_iswdigit_l)(wint32_t ch, locale_t locale);
/* >> iswxdigit_l(3) */
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBDCALL libd_iswxdigit_l)(wint16_t ch, locale_t locale);
/* >> iswxdigit_l(3) */
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBKCALL libc_iswxdigit_l)(wint32_t ch, locale_t locale);
/* >> iswalnum_l(3) */
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBDCALL libd_iswalnum_l)(wint16_t ch, locale_t locale);
/* >> iswalnum_l(3) */
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBKCALL libc_iswalnum_l)(wint32_t ch, locale_t locale);
/* >> iswpunct_l(3) */
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBDCALL libd_iswpunct_l)(wint16_t ch, locale_t locale);
/* >> iswpunct_l(3) */
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBKCALL libc_iswpunct_l)(wint32_t ch, locale_t locale);
/* >> iswgraph_l(3) */
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBDCALL libd_iswgraph_l)(wint16_t ch, locale_t locale);
/* >> iswgraph_l(3) */
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBKCALL libc_iswgraph_l)(wint32_t ch, locale_t locale);
/* >> iswprint_l(3) */
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBDCALL libd_iswprint_l)(wint16_t ch, locale_t locale);
/* >> iswprint_l(3) */
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBKCALL libc_iswprint_l)(wint32_t ch, locale_t locale);
/* >> iswblank_l(3) */
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBDCALL libd_iswblank_l)(wint16_t ch, locale_t locale);
/* >> iswblank_l(3) */
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBKCALL libc_iswblank_l)(wint32_t ch, locale_t locale);
/* >> towlower_l(3) */
INTDEF ATTR_PURE WUNUSED wint16_t NOTHROW_NCX(LIBDCALL libd_towlower_l)(wint16_t ch, locale_t locale);
/* >> towlower_l(3) */
INTDEF ATTR_PURE WUNUSED wint32_t NOTHROW_NCX(LIBKCALL libc_towlower_l)(wint32_t ch, locale_t locale);
/* >> towupper_l(3) */
INTDEF ATTR_PURE WUNUSED wint16_t NOTHROW_NCX(LIBDCALL libd_towupper_l)(wint16_t ch, locale_t locale);
/* >> towupper_l(3) */
INTDEF ATTR_PURE WUNUSED wint32_t NOTHROW_NCX(LIBKCALL libc_towupper_l)(wint32_t ch, locale_t locale);
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBDCALL libd_iswctype_l)(wint16_t wc, wctype_t type, locale_t locale);
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBKCALL libc_iswctype_l)(wint32_t wc, wctype_t type, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED ATTR_IN(1) wctype_t NOTHROW_NCX(LIBDCALL libd_wctype_l)(char const *prop, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED ATTR_IN(1) wctype_t NOTHROW_NCX(LIBCCALL libc_wctype_l)(char const *prop, locale_t locale);
INTDEF WUNUSED wint16_t NOTHROW_NCX(LIBDCALL libd_towctrans_l)(wint16_t wc, wctrans_t desc, locale_t locale);
INTDEF WUNUSED wint32_t NOTHROW_NCX(LIBKCALL libc_towctrans_l)(wint32_t wc, wctrans_t desc, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED ATTR_IN(1) wctrans_t NOTHROW_NCX(LIBDCALL libd_wctrans_l)(char const *prop, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED ATTR_IN(1) wctrans_t NOTHROW_NCX(LIBCCALL libc_wctrans_l)(char const *prop, locale_t locale);
/* >> iswsymstrt(3), iswsymstrt_l(3)
 * Check if `wc' may appear at the start of a symbol/keyword/identifier */
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBDCALL libd___iswcsymf)(wint16_t wc);
/* >> iswsymstrt(3), iswsymstrt_l(3)
 * Check if `wc' may appear at the start of a symbol/keyword/identifier */
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBKCALL libc___iswcsymf)(wint32_t wc);
/* >> iswsymcont(3), iswsymcont_l(3)
 * Check if `wc' may appear in the middle of a symbol/keyword/identifier */
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBDCALL libd___iswcsym)(wint16_t wc);
/* >> iswsymcont(3), iswsymcont_l(3)
 * Check if `wc' may appear in the middle of a symbol/keyword/identifier */
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBKCALL libc___iswcsym)(wint32_t wc);
/* >> iswsymstrt(3), iswsymstrt_l(3)
 * Check if `wc' may appear at the start of a symbol/keyword/identifier */
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBDCALL libd__iswcsymf_l)(wint16_t wc, locale_t locale);
/* >> iswsymstrt(3), iswsymstrt_l(3)
 * Check if `wc' may appear at the start of a symbol/keyword/identifier */
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBKCALL libc__iswcsymf_l)(wint32_t wc, locale_t locale);
/* >> iswsymcont(3), iswsymcont_l(3)
 * Check if `wc' may appear in the middle of a symbol/keyword/identifier */
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBDCALL libd__iswcsym_l)(wint16_t wc, locale_t locale);
/* >> iswsymcont(3), iswsymcont_l(3)
 * Check if `wc' may appear in the middle of a symbol/keyword/identifier */
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBKCALL libc__iswcsym_l)(wint32_t wc, locale_t locale);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> isleadbyte(3) */
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBDCALL libd_isleadbyte)(int wc);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> isleadbyte(3) */
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBCCALL libc_isleadbyte)(int wc);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBDCALL libd__isleadbyte_l)(int wc, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBCCALL libc__isleadbyte_l)(int wc, locale_t locale);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_WCTYPE_H */
