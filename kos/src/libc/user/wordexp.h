/* HASH CRC-32:0xbc86aed8 */
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
#ifndef GUARD_LIBC_USER_WORDEXP_H
#define GUARD_LIBC_USER_WORDEXP_H 1

#include "../api.h"
#include "../auto/wordexp.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <wordexp.h>

DECL_BEGIN

#ifndef __KERNEL__
/* >> wordexp(3)
 * Do shell-like expansion of `string'
 * @param: string: The string to expand
 * @param: self:   The word-expansion controller (and result container)
 * @param: flags:  Expansion flags (set of `WRDE_*' from <wordexp.h>)
 * @return: 0 : Success
 * @return: * : Error (return value is one of `WRDE_*' from <wordexp.h>) */
INTDEF ATTR_IN(1) NONNULL((2)) int NOTHROW_NCX(LIBCCALL libc_wordexp)(char const *__restrict string, wordexp_t *__restrict self, __STDC_INT_AS_UINT_T flags);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_USER_WORDEXP_H */
