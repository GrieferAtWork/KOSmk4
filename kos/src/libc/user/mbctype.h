/* HASH CRC-32:0xc039712b */
/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_USER_MBCTYPE_H
#define GUARD_LIBC_USER_MBCTYPE_H 1

#include "../api.h"
#include "../auto/mbctype.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <mbctype.h>

DECL_BEGIN

#ifndef __KERNEL__
INTDEF ATTR_CONST ATTR_RETNONNULL WUNUSED unsigned char *NOTHROW(LIBCCALL libc___p__mbctype)(void);
INTDEF ATTR_CONST ATTR_RETNONNULL WUNUSED unsigned char *NOTHROW(LIBCCALL libc___p__mbcasemap)(void);
INTDEF int NOTHROW_NCX(LIBCCALL libc__setmbcp)(int cp);
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBCCALL libc__getmbcp)(void);
INTDEF ATTR_PURE WUNUSED char32_t NOTHROW_NCX(LIBCCALL libc__mbctouni_l)(unsigned int ch, locale_t locale);
INTDEF ATTR_PURE WUNUSED unsigned int NOTHROW_NCX(LIBCCALL libc__unitombc_l)(char32_t ch, locale_t locale);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_USER_MBCTYPE_H */
