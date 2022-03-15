/* HASH CRC-32:0x8852a964 */
/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_USER_CORECRT_WCONIO_H
#define GUARD_LIBC_USER_CORECRT_WCONIO_H 1

#include "../api.h"
#include "../auto/corecrt_wconio.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <corecrt_wconio.h>

DECL_BEGIN

#ifndef __KERNEL__
INTDEF WUNUSED wint16_t NOTHROW_NCX(LIBDCALL libd__getwch)(void);
INTDEF WUNUSED wint32_t NOTHROW_NCX(LIBKCALL libc__getwch)(void);
INTDEF WUNUSED wint16_t NOTHROW_NCX(LIBDCALL libd__getwch_nolock)(void);
INTDEF WUNUSED wint32_t NOTHROW_NCX(LIBKCALL libc__getwch_nolock)(void);
INTDEF WUNUSED wint16_t NOTHROW_NCX(LIBDCALL libd__getwche)(void);
INTDEF WUNUSED wint32_t NOTHROW_NCX(LIBKCALL libc__getwche)(void);
INTDEF WUNUSED wint16_t NOTHROW_NCX(LIBDCALL libd__getwche_nolock)(void);
INTDEF WUNUSED wint32_t NOTHROW_NCX(LIBKCALL libc__getwche_nolock)(void);
INTDEF WUNUSED ATTR_LIBC_C16SCANF(2, 0) NONNULL((2)) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBDCALL libd___conio_common_vcwscanf)(uint64_t options, char16_t const *format, locale_t locale, va_list args);
INTDEF WUNUSED ATTR_LIBC_C32SCANF(2, 0) NONNULL((2)) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBKCALL libc___conio_common_vcwscanf)(uint64_t options, char32_t const *format, locale_t locale, va_list args);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_USER_CORECRT_WCONIO_H */
