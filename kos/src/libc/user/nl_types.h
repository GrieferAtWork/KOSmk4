/* HASH CRC-32:0x9118dea5 */
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
#ifndef GUARD_LIBC_USER_NL_TYPES_H
#define GUARD_LIBC_USER_NL_TYPES_H 1

#include "../api.h"
#include "../auto/nl_types.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <nl_types.h>

DECL_BEGIN

#ifndef __KERNEL__
INTDEF ATTR_IN(1) nl_catd NOTHROW_RPC(LIBCCALL libc_catopen)(char const *cat_name, int flag);
INTDEF char *NOTHROW_NCX(LIBCCALL libc_catgets)(nl_catd catalog, int set, int number, char const *string);
INTDEF int NOTHROW_NCX(LIBCCALL libc_catclose)(nl_catd catalog);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_USER_NL_TYPES_H */
