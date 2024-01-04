/* HASH CRC-32:0xb61e75e8 */
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
#ifndef GUARD_LIBC_AUTO_NL_TYPES_H
#define GUARD_LIBC_AUTO_NL_TYPES_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <nl_types.h>

DECL_BEGIN

#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_IN(1) nl_catd NOTHROW_RPC(LIBDCALL libd_catopen)(char const *cat_name, int flag);
INTDEF ATTR_INOUT(1) char *NOTHROW_NCX(LIBDCALL libd_catgets)(nl_catd catalog, int set, int number, char const *string);
INTDEF ATTR_INOUT(1) int NOTHROW_NCX(LIBDCALL libd_catclose)(nl_catd catalog);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_NL_TYPES_H */
