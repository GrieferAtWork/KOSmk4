/* HASH CRC-32:0xf29bd868 */
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
#ifndef GUARD_LIBC_USER_MBSTRING_H
#define GUARD_LIBC_USER_MBSTRING_H 1

#include "../api.h"
#include "../auto/mbstring.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <mbstring.h>

DECL_BEGIN

#ifndef __KERNEL__
INTDEF WUNUSED NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc__mbsbtype_l)(unsigned char const *str, size_t pos, locale_t locale);
INTDEF WUNUSED unsigned int NOTHROW_NCX(LIBCCALL libc__mbbtombc_l)(unsigned int ch, locale_t locale);
INTDEF WUNUSED unsigned int NOTHROW_NCX(LIBCCALL libc__mbctombb_l)(unsigned int ch, locale_t locale);
INTDEF WUNUSED int NOTHROW_NCX(LIBCCALL libc__mbbtype_l)(unsigned char ch, int ctype, locale_t locale);
INTDEF WUNUSED int NOTHROW_NCX(LIBCCALL libc__ismbcalnum_l)(unsigned int ch, locale_t locale);
INTDEF WUNUSED int NOTHROW_NCX(LIBCCALL libc__ismbcalpha_l)(unsigned int ch, locale_t locale);
INTDEF WUNUSED int NOTHROW_NCX(LIBCCALL libc__ismbcdigit_l)(unsigned int ch, locale_t locale);
INTDEF WUNUSED int NOTHROW_NCX(LIBCCALL libc__ismbcgraph_l)(unsigned int ch, locale_t locale);
INTDEF WUNUSED int NOTHROW_NCX(LIBCCALL libc__ismbclegal_l)(unsigned int ch, locale_t locale);
INTDEF WUNUSED int NOTHROW_NCX(LIBCCALL libc__ismbclower_l)(unsigned int ch, locale_t locale);
INTDEF WUNUSED int NOTHROW_NCX(LIBCCALL libc__ismbcprint_l)(unsigned int ch, locale_t locale);
INTDEF WUNUSED int NOTHROW_NCX(LIBCCALL libc__ismbcpunct_l)(unsigned int ch, locale_t locale);
INTDEF WUNUSED int NOTHROW_NCX(LIBCCALL libc__ismbcblank_l)(unsigned int ch, locale_t locale);
INTDEF WUNUSED int NOTHROW_NCX(LIBCCALL libc__ismbcspace_l)(unsigned int ch, locale_t locale);
INTDEF WUNUSED int NOTHROW_NCX(LIBCCALL libc__ismbcupper_l)(unsigned int ch, locale_t locale);
INTDEF WUNUSED unsigned int NOTHROW_NCX(LIBCCALL libc__mbctolower_l)(unsigned int ch, locale_t locale);
INTDEF WUNUSED unsigned int NOTHROW_NCX(LIBCCALL libc__mbctoupper_l)(unsigned int ch, locale_t locale);
INTDEF WUNUSED int NOTHROW_NCX(LIBCCALL libc__ismbchira_l)(unsigned int ch, locale_t locale);
INTDEF WUNUSED int NOTHROW_NCX(LIBCCALL libc__ismbckata_l)(unsigned int ch, locale_t locale);
INTDEF WUNUSED int NOTHROW_NCX(LIBCCALL libc__ismbcsymbol_l)(unsigned int ch, locale_t locale);
INTDEF WUNUSED int NOTHROW_NCX(LIBCCALL libc__ismbcl0_l)(unsigned int ch, locale_t locale);
INTDEF WUNUSED int NOTHROW_NCX(LIBCCALL libc__ismbcl1_l)(unsigned int ch, locale_t locale);
INTDEF WUNUSED int NOTHROW_NCX(LIBCCALL libc__ismbcl2_l)(unsigned int ch, locale_t locale);
INTDEF WUNUSED unsigned int NOTHROW_NCX(LIBCCALL libc__mbcjistojms_l)(unsigned int ch, locale_t locale);
INTDEF WUNUSED unsigned int NOTHROW_NCX(LIBCCALL libc__mbcjmstojis_l)(unsigned int ch, locale_t locale);
INTDEF WUNUSED unsigned int NOTHROW_NCX(LIBCCALL libc__mbctohira_l)(unsigned int ch, locale_t locale);
INTDEF WUNUSED unsigned int NOTHROW_NCX(LIBCCALL libc__mbctokata_l)(unsigned int ch, locale_t locale);
INTDEF WUNUSED int NOTHROW_NCX(LIBCCALL libc__ismbblead_l)(unsigned int ch, locale_t locale);
INTDEF WUNUSED int NOTHROW_NCX(LIBCCALL libc__ismbbtrail_l)(unsigned int ch, locale_t locale);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_USER_MBSTRING_H */
