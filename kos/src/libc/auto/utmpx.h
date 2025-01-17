/* HASH CRC-32:0xb6613f4 */
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
#ifndef GUARD_LIBC_AUTO_UTMPX_H
#define GUARD_LIBC_AUTO_UTMPX_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <utmpx.h>

DECL_BEGIN

#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> getutxid(3) */
INTDEF struct utmpx *NOTHROW_RPC(LIBDCALL libd_getutxid)(struct utmpx const *id);
/* >> getutxline(3) */
INTDEF struct utmpx *NOTHROW_RPC(LIBDCALL libd_getutxline)(struct utmpx const *line);
/* >> pututxline(3) */
INTDEF struct utmpx *NOTHROW_RPC(LIBDCALL libd_pututxline)(struct utmpx const *utmpx);
/* >> utmpxname(3) */
INTDEF int NOTHROW_RPC(LIBDCALL libd_utmpxname)(char const *file);
/* >> updwtmpx(3) */
INTDEF void NOTHROW_RPC(LIBDCALL libd_updwtmpx)(char const *wtmpx_file, struct utmpx const *utmpx);
/* >> getutmp(3) */
INTDEF void NOTHROW_RPC(LIBDCALL libd_getutmp)(struct utmpx const *utmpx, struct utmp *utmp);
/* >> getutmpx(3) */
INTDEF void NOTHROW_RPC(LIBDCALL libd_getutmpx)(struct utmp const *utmp, struct utmpx *utmpx);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_UTMPX_H */
