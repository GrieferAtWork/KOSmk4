/* HASH CRC-32:0x9e60cd69 */
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
#ifndef GUARD_LIBC_USER_FTS_H
#define GUARD_LIBC_USER_FTS_H 1

#include "../api.h"
#include "../auto/fts.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <fts.h>

DECL_BEGIN

#ifndef __KERNEL__
/* >> fts_children(3), fts_children64(3)
 * @param: instr: One of `FTS_AGAIN', `FTS_FOLLOW', `FTS_NOINSTR' or `FTS_SKIP' */
INTDEF WUNUSED ATTR_INOUT(1) FTSENT *NOTHROW_RPC(LIBCCALL libc_fts_children)(FTS *ftsp, __STDC_INT_AS_UINT_T instr);
/* >> fts_close(3), fts_close64(3) */
INTDEF ATTR_INOUT(1) int NOTHROW_NCX(LIBCCALL libc_fts_close)(FTS *ftsp);
/* >> fts_open(3), fts_open64(3)
 * @param: options: Set of `FTS_COMFOLLOW | FTS_LOGICAL | ... | FTS_STOP' */
INTDEF WUNUSED ATTR_IN(1) FTS *NOTHROW_RPC(LIBCCALL libc_fts_open)(char *const *path_argv, __STDC_INT_AS_UINT_T options, int (LIBKCALL *compar)(FTSENT const **lhs, FTSENT const **rhs));
/* >> fts_read(3), fts_read64(3) */
INTDEF WUNUSED ATTR_INOUT(1) FTSENT *NOTHROW_RPC(LIBCCALL libc_fts_read)(FTS *ftsp);
/* >> fts_set(3), fts_set64(3)
 * @param: instr: One of `FTS_AGAIN', `FTS_FOLLOW', `FTS_NOINSTR' or `FTS_SKIP' */
INTDEF ATTR_INOUT(1) ATTR_INOUT(2) int NOTHROW_NCX(LIBCCALL libc_fts_set)(FTS *ftsp, FTSENT *f, __STDC_INT_AS_UINT_T instr);
/* >> fts_children(3), fts_children64(3)
 * @param: instr: One of `FTS_AGAIN', `FTS_FOLLOW', `FTS_NOINSTR' or `FTS_SKIP' */
INTDEF WUNUSED ATTR_INOUT(1) FTSENT64 *NOTHROW_RPC(LIBCCALL libc_fts64_children)(FTS64 *ftsp, __STDC_INT_AS_UINT_T instr);
/* >> fts_close(3), fts_close64(3) */
INTDEF WUNUSED ATTR_INOUT(1) int NOTHROW_RPC(LIBCCALL libc_fts64_close)(FTS64 *ftsp);
/* >> fts_open(3), fts_open64(3)
 * @param: options: Set of `FTS_COMFOLLOW | FTS_LOGICAL | ... | FTS_STOP' */
INTDEF WUNUSED ATTR_IN(1) FTS64 *NOTHROW_RPC(LIBCCALL libc_fts64_open)(char *const *path_argv, __STDC_INT_AS_UINT_T options, int (LIBKCALL *compar)(FTSENT64 const **lhs, FTSENT64 const **rhs));
/* >> fts_read(3), fts_read64(3) */
INTDEF WUNUSED ATTR_INOUT(1) FTSENT64 *NOTHROW_RPC(LIBCCALL libc_fts64_read)(FTS64 *ftsp);
/* >> fts_set(3), fts_set64(3)
 * @param: instr: One of `FTS_AGAIN', `FTS_FOLLOW', `FTS_NOINSTR' or `FTS_SKIP' */
INTDEF ATTR_INOUT(1) ATTR_INOUT(2) int NOTHROW_NCX(LIBCCALL libc_fts64_set)(FTS64 *ftsp, FTSENT64 *f, __STDC_INT_AS_UINT_T instr);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_USER_FTS_H */
