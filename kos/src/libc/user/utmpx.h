/* HASH 0x71878a7d */
/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_USER_UTMPX_H
#define GUARD_LIBC_USER_UTMPX_H 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include <utmpx.h>

DECL_BEGIN

/* Open user accounting database */
INTDEF void NOTHROW_RPC(LIBCCALL libc_setutxent)(void);
/* Close user accounting database */
INTDEF void NOTHROW_RPC_NOKOS(LIBCCALL libc_endutxent)(void);
/* Get the next entry from the user accounting database */
INTDEF struct utmpx *NOTHROW_RPC(LIBCCALL libc_getutxent)(void);
/* Get the user accounting database entry corresponding to ID */
INTDEF struct utmpx *NOTHROW_RPC(LIBCCALL libc_getutxid)(struct utmpx const *id);
/* Get the user accounting database entry corresponding to LINE */
INTDEF struct utmpx *NOTHROW_RPC(LIBCCALL libc_getutxline)(struct utmpx const *line);
/* Write the entry UTMPX into the user accounting database */
INTDEF struct utmpx *NOTHROW_RPC(LIBCCALL libc_pututxline)(struct utmpx const *utmpx);
/* Change name of the utmpx file to be examined.
 * This function is not part of POSIX and therefore no official cancellation point */
INTDEF int NOTHROW_RPC(LIBCCALL libc_utmpxname)(char const *file);
/* Append entry UTMP to the wtmpx-like file WTMPX_FILE.
 * This function is not part of POSIX and therefore no official cancellation point */
INTDEF void NOTHROW_RPC(LIBCCALL libc_updwtmpx)(char const *wtmpx_file, struct utmpx const *utmpx);
/* Copy the information in UTMPX to UTMP.
 * This function is not part of POSIX and therefore no official cancellation point */
INTDEF void NOTHROW_RPC(LIBCCALL libc_getutmp)(struct utmpx const *utmpx, struct utmp *utmp);
/* Copy the information in UTMP to UTMPX.
 * This function is not part of POSIX and therefore no official cancellation point */
INTDEF void NOTHROW_RPC(LIBCCALL libc_getutmpx)(struct utmp const *utmp, struct utmpx *utmpx);

DECL_END

#endif /* !GUARD_LIBC_USER_UTMPX_H */
