/* HASH CRC-32:0xafc0385f */
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
#ifndef GUARD_LIBC_AUTO_LANGINFO_H
#define GUARD_LIBC_AUTO_LANGINFO_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <langinfo.h>

DECL_BEGIN

#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> nl_langinfo(3), nl_langinfo_l(3)
 * Return the name of the given `item' (one of the macros above)
 * to be returned for  the current locale (s.a.  `setlocale(3)')
 * This function never returns `NULL',  but may return an  empty
 * string when `item' is invalid.
 * @param: item: One of the macros from <langinfo.h>, or one of `_NL_*' */
INTDEF ATTR_RETNONNULL char __KOS_FIXED_CONST *NOTHROW_NCX(LIBDCALL libd_nl_langinfo)(nl_item item);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> nl_langinfo(3), nl_langinfo_l(3)
 * Return the name of the given `item' (one of the macros above)
 * to be returned for  the current locale (s.a.  `setlocale(3)')
 * This function never returns `NULL',  but may return an  empty
 * string when `item' is invalid.
 * @param: item: One of the macros from <langinfo.h>, or one of `_NL_*' */
INTDEF ATTR_RETNONNULL char __KOS_FIXED_CONST *NOTHROW_NCX(LIBCCALL libc_nl_langinfo)(nl_item item);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> nl_langinfo(3), nl_langinfo_l(3)
 * Return the name of the given `item' (one of the macros above)
 * to be returned for  the current locale (s.a.  `setlocale(3)')
 * This function never returns `NULL',  but may return an  empty
 * string when `item' is invalid.
 * @param: item: One of the macros from <langinfo.h>, or one of `_NL_*' */
INTDEF ATTR_RETNONNULL char __KOS_FIXED_CONST *NOTHROW_NCX(LIBDCALL libd_nl_langinfo_l)(nl_item item, locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> nl_langinfo(3), nl_langinfo_l(3)
 * Return the name of the given `item' (one of the macros above)
 * to be returned for  the current locale (s.a.  `setlocale(3)')
 * This function never returns `NULL',  but may return an  empty
 * string when `item' is invalid.
 * @param: item: One of the macros from <langinfo.h>, or one of `_NL_*' */
INTDEF ATTR_RETNONNULL char __KOS_FIXED_CONST *NOTHROW_NCX(LIBCCALL libc_nl_langinfo_l)(nl_item item, locale_t locale);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_LANGINFO_H */
