/* HASH CRC-32:0xaad6e476 */
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
#ifndef GUARD_LIBC_AUTO_REGEXP_H
#define GUARD_LIBC_AUTO_REGEXP_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <regexp.h>

DECL_BEGIN

#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> step(3)
 * Find the next matching position in `string', given `expbuf' as previously passed to `compile(3)'
 * @return: 0: No match
 * @return: 1: Match was found in range `[loc1,loc2)' (yes: these are global variables) */
INTDEF int NOTHROW_NCX(LIBDCALL libd_step)(char const *string, char const *expbuf);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> step(3)
 * Find the next matching position in `string', given `expbuf' as previously passed to `compile(3)'
 * @return: 0: No match
 * @return: 1: Match was found in range `[loc1,loc2)' (yes: these are global variables) */
INTDEF int NOTHROW_NCX(LIBCCALL libc_step)(char const *string, char const *expbuf);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> advance(3)
 * Match the beginning of `string' against `expbuf' as previously passed to `compile(3)'
 * @return: 0: No match (or just not at the beginning of `string')
 * @return: 1: Match was found in range `[string,loc2)' (`string' being the first
 *             argument  to this  function, and  `loc2' being  a global variable) */
INTDEF int NOTHROW_NCX(LIBDCALL libd_advance)(char const *string, char const *expbuf);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> advance(3)
 * Match the beginning of `string' against `expbuf' as previously passed to `compile(3)'
 * @return: 0: No match (or just not at the beginning of `string')
 * @return: 1: Match was found in range `[string,loc2)' (`string' being the first
 *             argument  to this  function, and  `loc2' being  a global variable) */
INTDEF int NOTHROW_NCX(LIBCCALL libc_advance)(char const *string, char const *expbuf);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_REGEXP_H */
