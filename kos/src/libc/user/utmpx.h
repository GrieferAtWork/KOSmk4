/* HASH CRC-32:0x4eeef93f */
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
#ifndef GUARD_LIBC_USER_UTMPX_H
#define GUARD_LIBC_USER_UTMPX_H 1

#include "../api.h"
#include "../auto/utmpx.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <utmpx.h>

DECL_BEGIN

#ifndef __KERNEL__
/* >> setutxent(3) */
INTDEF void NOTHROW_RPC(LIBCCALL libc_setutxent)(void);
/* >> endutxent(3) */
INTDEF void NOTHROW_RPC_NOKOS(LIBCCALL libc_endutxent)(void);
/* >> getutxent(3) */
INTDEF struct utmpx *NOTHROW_RPC(LIBCCALL libc_getutxent)(void);
/* >> getutxid(3) */
INTDEF struct utmpx *NOTHROW_RPC(LIBCCALL libc_getutxid)(struct utmpx const *id);
/* >> getutxline(3) */
INTDEF struct utmpx *NOTHROW_RPC(LIBCCALL libc_getutxline)(struct utmpx const *line);
/* >> pututxline(3) */
INTDEF struct utmpx *NOTHROW_RPC(LIBCCALL libc_pututxline)(struct utmpx const *utmpx);
/* >> utmpxname(3) */
INTDEF int NOTHROW_RPC(LIBCCALL libc_utmpxname)(char const *file);
/* >> updwtmpx(3) */
INTDEF void NOTHROW_RPC(LIBCCALL libc_updwtmpx)(char const *wtmpx_file, struct utmpx const *utmpx);
/* >> getutmp(3) */
INTDEF void NOTHROW_RPC(LIBCCALL libc_getutmp)(struct utmpx const *utmpx, struct utmp *utmp);
/* >> getutmpx(3) */
INTDEF void NOTHROW_RPC(LIBCCALL libc_getutmpx)(struct utmp const *utmp, struct utmpx *utmpx);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_USER_UTMPX_H */
