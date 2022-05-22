/* HASH CRC-32:0x9990203 */
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
#ifndef GUARD_LIBC_USER_UTMP_H
#define GUARD_LIBC_USER_UTMP_H 1

#include "../api.h"
#include "../auto/utmp.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <utmp.h>

DECL_BEGIN

#ifndef __KERNEL__
/* >> login(3) */
INTDEF ATTR_IN(1) void NOTHROW_RPC_KOS(LIBCCALL libc_login)(struct utmp const *entry);
/* >> logout(3) */
INTDEF ATTR_IN(1) int NOTHROW_RPC_KOS(LIBCCALL libc_logout)(char const *ut_line);
/* >> logwtmp(3) */
INTDEF ATTR_IN(1) ATTR_IN(2) ATTR_IN(3) void NOTHROW_RPC_KOS(LIBCCALL libc_logwtmp)(char const *ut_line, char const *ut_name, char const *ut_host);
/* >> updwtmp(3) */
INTDEF ATTR_IN(1) ATTR_IN(2) void NOTHROW_RPC_KOS(LIBCCALL libc_updwtmp)(char const *wtmp_file, struct utmp const *utmp);
/* >> utmpname(3) */
INTDEF ATTR_IN(1) int NOTHROW_RPC_KOS(LIBCCALL libc_utmpname)(char const *file);
/* >> getutent(3), getutent_r(3) */
INTDEF struct utmp *NOTHROW_RPC_KOS(LIBCCALL libc_getutent)(void);
/* >> setutent(3) */
INTDEF void NOTHROW_RPC_KOS(LIBCCALL libc_setutent)(void);
/* >> endutent(3) */
INTDEF void NOTHROW_NCX(LIBCCALL libc_endutent)(void);
/* >> getutid(3), getutid_r(3) */
INTDEF ATTR_IN(1) struct utmp *NOTHROW_RPC_KOS(LIBCCALL libc_getutid)(struct utmp const *id);
/* >> getutline(3), getutline_r(3) */
INTDEF ATTR_IN(1) struct utmp *NOTHROW_RPC_KOS(LIBCCALL libc_getutline)(struct utmp const *line);
/* >> pututline(3) */
INTDEF ATTR_IN(1) struct utmp *NOTHROW_RPC_KOS(LIBCCALL libc_pututline)(struct utmp const *utmp_ptr);
/* >> getutent(3), getutent_r(3) */
INTDEF ATTR_OUT(1) ATTR_OUT(2) int NOTHROW_RPC_KOS(LIBCCALL libc_getutent_r)(struct utmp *buffer, struct utmp **result);
/* >> getutid(3), getutid_r(3) */
INTDEF ATTR_IN(1) ATTR_OUT(2) ATTR_OUT(3) int NOTHROW_RPC_KOS(LIBCCALL libc_getutid_r)(struct utmp const *id, struct utmp *buffer, struct utmp **result);
/* >> getutline(3), getutline_r(3) */
INTDEF ATTR_IN(1) ATTR_OUT(2) ATTR_OUT(3) int NOTHROW_RPC_KOS(LIBCCALL libc_getutline_r)(struct utmp const *line, struct utmp *buffer, struct utmp **result);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_USER_UTMP_H */
