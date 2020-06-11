/* HASH CRC-32:0x5296945c */
/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_USER_PWD_H
#define GUARD_LIBC_USER_PWD_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <pwd.h>

DECL_BEGIN

#ifndef __KERNEL__
/* Rewind the password-file stream */
INTDEF void NOTHROW_RPC(LIBCCALL libc_setpwent)(void);
/* Close the password-file stream */
INTDEF void NOTHROW_RPC_NOKOS(LIBCCALL libc_endpwent)(void);
/* Read an entry from the password-file stream, opening it if necessary */
INTDEF struct passwd *NOTHROW_RPC(LIBCCALL libc_getpwent)(void);
/* Search for an entry with a matching user ID */
INTDEF struct passwd *NOTHROW_RPC(LIBCCALL libc_getpwuid)(uid_t uid);
/* Search for an entry with a matching username */
INTDEF NONNULL((1)) struct passwd *NOTHROW_RPC(LIBCCALL libc_getpwnam)(const char *name);
/* Read an entry from STREAM */
INTDEF NONNULL((1)) struct passwd *NOTHROW_RPC(LIBCCALL libc_fgetpwent)(FILE *__restrict stream);
/* Write the given entry onto the given stream */
INTDEF NONNULL((1, 2)) int NOTHROW_RPC(LIBCCALL libc_putpwent)(struct passwd const *__restrict p, FILE *__restrict f);
/* Search for an entry with a matching user ID */
INTDEF NONNULL((2, 3, 5)) int NOTHROW_RPC(LIBCCALL libc_getpwuid_r)(__uid_t __uid, struct passwd *__restrict resultbuf, char *__restrict buffer, size_t buflen, struct passwd **__restrict result);
/* Search for an entry with a matching username */
INTDEF NONNULL((1, 2, 3, 5)) int NOTHROW_RPC(LIBCCALL libc_getpwnam_r)(const char *__restrict name, struct passwd *__restrict resultbuf, char *__restrict buffer, size_t buflen, struct passwd **__restrict result);
/* Read an entry from the password-file stream, opening it if necessary */
INTDEF NONNULL((1, 2, 4)) int NOTHROW_RPC(LIBCCALL libc_getpwent_r)(struct passwd *__restrict resultbuf, char *__restrict buffer, size_t buflen, struct passwd **__restrict result);
/* Read an entry from STREAM. This function is not standardized and probably never will */
INTDEF NONNULL((1, 2, 3, 5)) int NOTHROW_RPC(LIBCCALL libc_fgetpwent_r)(FILE *__restrict stream, struct passwd *__restrict resultbuf, char *__restrict buffer, size_t buflen, struct passwd **__restrict result);
/* Re-construct the password-file line for the given uid in the
 * given buffer. This knows the format that the caller will
 * expect, but this need not be the format of the password file */
INTDEF int NOTHROW_RPC(LIBCCALL libc_getpw)(__uid_t uid, char *buffer);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_USER_PWD_H */
