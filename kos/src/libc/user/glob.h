/* HASH CRC-32:0x19387dc1 */
/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_USER_GLOB_H
#define GUARD_LIBC_USER_GLOB_H 1

#include "../api.h"
#include "../auto/glob.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <glob.h>

DECL_BEGIN

#ifndef __KERNEL__
/* @param: flags: Set of `GLOB_ERR | GLOB_MARK | GLOB_NOSORT | GLOB_DOOFFS |
 *                        GLOB_NOCHECK | GLOB_APPEND  | GLOB_NOESCAPE  |
 *                        GLOB_PERIOD | GLOB_MAGCHAR | GLOB_ALTDIRFUNC |
 *                        GLOB_BRACE  |  GLOB_NOMAGIC  |  GLOB_TILDE   |
 *                        GLOB_ONLYDIR | GLOB_TILDE_CHECK'
 * @return: GLOB_NOSPACE : ...
 * @return: GLOB_ABORTED : ...
 * @return: GLOB_NOMATCH : ...
 * @return: GLOB_NOSYS   : ... */
INTDEF NONNULL((1, 4)) int NOTHROW_NCX(LIBCCALL libc_glob)(char const *__restrict pattern, __STDC_INT_AS_UINT_T flags, __glob_errfunc_t errfunc, glob_t *__restrict pglob);
INTDEF NONNULL((1)) void NOTHROW_NCX(LIBCCALL libc_globfree)(glob_t *pglob);
/* @param: flags: Set of `GLOB_ERR | GLOB_MARK | GLOB_NOSORT | GLOB_DOOFFS |
 *                        GLOB_NOCHECK | GLOB_APPEND  | GLOB_NOESCAPE  |
 *                        GLOB_PERIOD | GLOB_MAGCHAR | GLOB_ALTDIRFUNC |
 *                        GLOB_BRACE  |  GLOB_NOMAGIC  |  GLOB_TILDE   |
 *                        GLOB_ONLYDIR | GLOB_TILDE_CHECK'
 * @return: GLOB_NOSPACE : ...
 * @return: GLOB_ABORTED : ...
 * @return: GLOB_NOMATCH : ...
 * @return: GLOB_NOSYS   : ... */
INTDEF NONNULL((1, 4)) int NOTHROW_NCX(LIBCCALL libc_glob64)(const char *__restrict pattern, __STDC_INT_AS_UINT_T flags, __glob_errfunc_t errfunc, struct __glob64_struct *__restrict pglob);
INTDEF NONNULL((1)) void NOTHROW_NCX(LIBCCALL libc_globfree64)(struct __glob64_struct *pglob);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_USER_GLOB_H */
