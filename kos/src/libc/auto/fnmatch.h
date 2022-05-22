/* HASH CRC-32:0xd0624a9a */
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
#ifndef GUARD_LIBC_AUTO_FNMATCH_H
#define GUARD_LIBC_AUTO_FNMATCH_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <fnmatch.h>

DECL_BEGIN

#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> fnmatch(3)
 * Match the given `name' against `pattern', returning
 * `0'  if  they match,  and  `FNM_NOMATCH' otherwise.
 * @param: match_flags:   Set of `FNM_*'
 * @return: 0           : `name' is matched by `pattern'
 * @return: FNM_NOMATCH : `name' is not matched by `pattern' */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int NOTHROW_NCX(LIBDCALL libd_fnmatch)(char const *pattern, char const *name, __STDC_INT_AS_UINT_T match_flags);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> fnmatch(3)
 * Match the given `name' against `pattern', returning
 * `0'  if  they match,  and  `FNM_NOMATCH' otherwise.
 * @param: match_flags:   Set of `FNM_*'
 * @return: 0           : `name' is matched by `pattern'
 * @return: FNM_NOMATCH : `name' is not matched by `pattern' */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int NOTHROW_NCX(LIBCCALL libc_fnmatch)(char const *pattern, char const *name, __STDC_INT_AS_UINT_T match_flags);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_FNMATCH_H */
