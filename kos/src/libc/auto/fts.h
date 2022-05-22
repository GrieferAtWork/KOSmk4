/* HASH CRC-32:0xd618e18b */
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
#ifndef GUARD_LIBC_AUTO_FTS_H
#define GUARD_LIBC_AUTO_FTS_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <fts.h>

DECL_BEGIN

#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> fts_children(3), fts_children64(3)
 * @param: instr: One of `FTS_AGAIN', `FTS_FOLLOW', `FTS_NOINSTR' or `FTS_SKIP' */
INTDEF WUNUSED ATTR_INOUT(1) FTSENT *NOTHROW_RPC(LIBDCALL libd_fts_children)(FTS *ftsp, __STDC_INT_AS_UINT_T instr);
/* >> fts_close(3), fts_close64(3) */
INTDEF ATTR_INOUT(1) int NOTHROW_NCX(LIBDCALL libd_fts_close)(FTS *ftsp);
/* >> fts_read(3), fts_read64(3) */
INTDEF WUNUSED ATTR_INOUT(1) FTSENT *NOTHROW_RPC(LIBDCALL libd_fts_read)(FTS *ftsp);
/* >> fts_set(3), fts_set64(3)
 * @param: instr: One of `FTS_AGAIN', `FTS_FOLLOW', `FTS_NOINSTR' or `FTS_SKIP' */
INTDEF ATTR_INOUT(1) ATTR_INOUT(2) int NOTHROW_NCX(LIBDCALL libd_fts_set)(FTS *ftsp, FTSENT *f, __STDC_INT_AS_UINT_T instr);
/* >> fts_children(3), fts_children64(3)
 * @param: instr: One of `FTS_AGAIN', `FTS_FOLLOW', `FTS_NOINSTR' or `FTS_SKIP' */
INTDEF WUNUSED ATTR_INOUT(1) FTSENT64 *NOTHROW_RPC(LIBDCALL libd_fts64_children)(FTS64 *ftsp, __STDC_INT_AS_UINT_T instr);
/* >> fts_close(3), fts_close64(3) */
INTDEF WUNUSED ATTR_INOUT(1) int NOTHROW_RPC(LIBDCALL libd_fts64_close)(FTS64 *ftsp);
/* >> fts_read(3), fts_read64(3) */
INTDEF WUNUSED ATTR_INOUT(1) FTSENT64 *NOTHROW_RPC(LIBDCALL libd_fts64_read)(FTS64 *ftsp);
/* >> fts_set(3), fts_set64(3)
 * @param: instr: One of `FTS_AGAIN', `FTS_FOLLOW', `FTS_NOINSTR' or `FTS_SKIP' */
INTDEF ATTR_INOUT(1) ATTR_INOUT(2) int NOTHROW_NCX(LIBDCALL libd_fts64_set)(FTS64 *ftsp, FTSENT64 *f, __STDC_INT_AS_UINT_T instr);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_FTS_H */
