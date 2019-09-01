/* HASH 0xc905ffe8 */
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
#ifndef GUARD_LIBC_AUTO_CTYPE_H
#define GUARD_LIBC_AUTO_CTYPE_H 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include <ctype.h>

DECL_BEGIN

#ifndef __KERNEL__
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBCCALL libc_iscntrl)(int ch);
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBCCALL libc_isspace)(int ch);
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBCCALL libc_isupper)(int ch);
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBCCALL libc_islower)(int ch);
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBCCALL libc_isalpha)(int ch);
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBCCALL libc_isdigit)(int ch);
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBCCALL libc_isxdigit)(int ch);
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBCCALL libc_isalnum)(int ch);
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBCCALL libc_ispunct)(int ch);
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBCCALL libc_isgraph)(int ch);
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBCCALL libc_isprint)(int ch);
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBCCALL libc_tolower)(int ch);
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBCCALL libc_toupper)(int ch);
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBCCALL libc_isblank)(int ch);
INTDEF ATTR_CONST WUNUSED int NOTHROW_NCX(LIBCCALL libc_iscntrl_l)(int ch, __locale_t locale);
INTDEF ATTR_CONST WUNUSED int NOTHROW_NCX(LIBCCALL libc_isspace_l)(int ch, __locale_t locale);
INTDEF ATTR_CONST WUNUSED int NOTHROW_NCX(LIBCCALL libc_isupper_l)(int ch, __locale_t locale);
INTDEF ATTR_CONST WUNUSED int NOTHROW_NCX(LIBCCALL libc_islower_l)(int ch, __locale_t locale);
INTDEF ATTR_CONST WUNUSED int NOTHROW_NCX(LIBCCALL libc_isalpha_l)(int ch, __locale_t locale);
INTDEF ATTR_CONST WUNUSED int NOTHROW_NCX(LIBCCALL libc_isdigit_l)(int ch, __locale_t locale);
INTDEF ATTR_CONST WUNUSED int NOTHROW_NCX(LIBCCALL libc_isxdigit_l)(int ch, __locale_t locale);
INTDEF ATTR_CONST WUNUSED int NOTHROW_NCX(LIBCCALL libc_isalnum_l)(int ch, __locale_t locale);
INTDEF ATTR_CONST WUNUSED int NOTHROW_NCX(LIBCCALL libc_ispunct_l)(int ch, __locale_t locale);
INTDEF ATTR_CONST WUNUSED int NOTHROW_NCX(LIBCCALL libc_isgraph_l)(int ch, __locale_t locale);
INTDEF ATTR_CONST WUNUSED int NOTHROW_NCX(LIBCCALL libc_isprint_l)(int ch, __locale_t locale);
INTDEF ATTR_CONST WUNUSED int NOTHROW_NCX(LIBCCALL libc_isblank_l)(int ch, __locale_t locale);
INTDEF ATTR_CONST WUNUSED int NOTHROW_NCX(LIBCCALL libc_tolower_l)(int ch, __locale_t locale);
INTDEF ATTR_CONST WUNUSED int NOTHROW_NCX(LIBCCALL libc_toupper_l)(int ch, __locale_t locale);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_CTYPE_H */
