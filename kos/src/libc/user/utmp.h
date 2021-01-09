/* HASH CRC-32:0xa7ba478d */
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
#ifndef GUARD_LIBC_USER_UTMP_H
#define GUARD_LIBC_USER_UTMP_H 1

#include "../api.h"
#include "../auto/utmp.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <utmp.h>

DECL_BEGIN

#ifndef __KERNEL__
/* Write the given entry into utmp and wtmp */
INTDEF NONNULL((1)) void NOTHROW_RPC_KOS(LIBCCALL libc_login)(struct utmp const *entry);
/* Write the utmp entry to say the user on UT_LINE has logged out */
INTDEF NONNULL((1)) int NOTHROW_RPC_KOS(LIBCCALL libc_logout)(char const *ut_line);
/* Append to wtmp an entry for the current time and the given info */
INTDEF NONNULL((1, 2, 3)) void NOTHROW_RPC_KOS(LIBCCALL libc_logwtmp)(char const *ut_line, char const *ut_name, char const *ut_host);
/* Append entry UTMP to the wtmp-like file WTMP_FILE */
INTDEF NONNULL((1, 2)) void NOTHROW_RPC_KOS(LIBCCALL libc_updwtmp)(char const *wtmp_file, struct utmp const *utmp);
/* Change name of the utmp file to be examined */
INTDEF NONNULL((1)) int NOTHROW_RPC_KOS(LIBCCALL libc_utmpname)(char const *file);
/* Read next entry from a utmp-like file */
INTDEF struct utmp *NOTHROW_RPC_KOS(LIBCCALL libc_getutent)(void);
/* Reset the input stream to the beginning of the file */
INTDEF void NOTHROW_RPC_KOS(LIBCCALL libc_setutent)(void);
/* Close the current open file */
INTDEF void NOTHROW_NCX(LIBCCALL libc_endutent)(void);
/* Search forward from the current point in the utmp file
 * until the next entry with a ut_type matching ID->ut_type */
INTDEF NONNULL((1)) struct utmp *NOTHROW_RPC_KOS(LIBCCALL libc_getutid)(struct utmp const *id);
/* Search forward from the current point in the utmp file
 * until the next entry with a ut_line matching LINE->ut_line */
INTDEF NONNULL((1)) struct utmp *NOTHROW_RPC_KOS(LIBCCALL libc_getutline)(struct utmp const *line);
/* Write out entry pointed to by UTMP_PTR into the utmp file */
INTDEF NONNULL((1)) struct utmp *NOTHROW_RPC_KOS(LIBCCALL libc_pututline)(struct utmp const *utmp_ptr);
/* Reentrant versions of the file for handling utmp files */
INTDEF NONNULL((1, 2)) int NOTHROW_RPC_KOS(LIBCCALL libc_getutent_r)(struct utmp *buffer, struct utmp **result);
/* Reentrant versions of the file for handling utmp files */
INTDEF NONNULL((1, 2, 3)) int NOTHROW_RPC_KOS(LIBCCALL libc_getutid_r)(struct utmp const *id, struct utmp *buffer, struct utmp **result);
/* Reentrant versions of the file for handling utmp files */
INTDEF NONNULL((1, 2, 3)) int NOTHROW_RPC_KOS(LIBCCALL libc_getutline_r)(struct utmp const *line, struct utmp *buffer, struct utmp **result);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_USER_UTMP_H */
