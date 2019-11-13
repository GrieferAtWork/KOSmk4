/* HASH CRC-32:0x81761174 */
/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_USER_CTYPE_H
#define GUARD_LIBC_USER_CTYPE_H 1

#include "../api.h"
#include "../auto/ctype.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include <ctype.h>

DECL_BEGIN

INTDEF ATTR_CONST WUNUSED char const *NOTHROW(LIBCCALL libc___locale_ctype_ptr)(void);
INTDEF ATTR_PURE WUNUSED char const *NOTHROW_NCX(LIBCCALL libc___locale_ctype_ptr_l)(locale_t locale);
INTDEF ATTR_PURE WUNUSED uint16_t const **NOTHROW(LIBCCALL libc___ctype_b_loc)(void);
INTDEF ATTR_PURE WUNUSED int32_t const **NOTHROW(LIBCCALL libc___ctype_tolower_loc)(void);
INTDEF ATTR_PURE WUNUSED int32_t const **NOTHROW(LIBCCALL libc___ctype_toupper_loc)(void);
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBCCALL libc__isctype)(int ch, int mask);
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBCCALL libc__isctype_l)(int ch, int mask, locale_t locale);

DECL_END

#endif /* !GUARD_LIBC_USER_CTYPE_H */
