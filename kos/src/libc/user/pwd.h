/* HASH CRC-32:0xbca137ef */
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
#ifndef GUARD_LIBC_USER_PWD_H
#define GUARD_LIBC_USER_PWD_H 1

#include "../api.h"
#include "../auto/pwd.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <pwd.h>

DECL_BEGIN

#ifndef __KERNEL__
/* Rewind the password-file stream */
INTDEF void NOTHROW_RPC(LIBCCALL libc_setpwent)(void);
/* Close the password-file stream */
INTDEF void NOTHROW_RPC_NOKOS(LIBCCALL libc_endpwent)(void);
/* Read an entry from the password-file stream, opening it if necessary
 * return: * :                         A pointer to the read password entry
 * return: NULL: (errno = <unchanged>) The last entry has already been read
 *                                     (use `setpwent()' to rewind the database)
 * return: NULL: (errno = <changed>)   Error (s.a. `errno') */
INTDEF struct passwd *NOTHROW_RPC(LIBCCALL libc_getpwent)(void);
/* Search for an entry with a matching user ID
 * return: * :                         A pointer to the read password entry
 * return: NULL: (errno = <unchanged>) No entry for `uid' exists
 * return: NULL: (errno = <changed>)   Error (s.a. `errno') */
INTDEF struct passwd *NOTHROW_RPC(LIBCCALL libc_getpwuid)(uid_t uid);
/* Search for an entry with a matching username
 * return: * :                         A pointer to the read password entry
 * return: NULL: (errno = <unchanged>) No entry for `name' exists
 * return: NULL: (errno = <changed>)   Error (s.a. `errno') */
INTDEF NONNULL((1)) struct passwd *NOTHROW_RPC(LIBCCALL libc_getpwnam)(const char *name);
/* Read an entry from `stream'
 * return: * :                         A pointer to the read password entry
 * return: NULL: (errno = <unchanged>) The last entry has already been read
 *                                     (use `rewind(stream)' to rewind the database)
 * return: NULL: (errno = <changed>)   Error (s.a. `errno') */
INTDEF NONNULL((1)) struct passwd *NOTHROW_RPC(LIBCCALL libc_fgetpwent)(FILE *__restrict stream);
/* Search for an entry with a matching user ID
 * @return: 0 : (*result != NULL) Success
 * @return: 0 : (*result == NULL) No entry for `uid'
 * @return: * : Error (one of `E*' from `<errno.h>') */
INTDEF NONNULL((2, 3, 5)) errno_t NOTHROW_RPC(LIBCCALL libc_getpwuid_r)(uid_t uid, struct passwd *__restrict resultbuf, char *__restrict buffer, size_t buflen, struct passwd **__restrict result);
/* Search for an entry with a matching username
 * @return: 0 : (*result != NULL) Success
 * @return: 0 : (*result == NULL) No entry for `name'
 * @return: * : Error (one of `E*' from `<errno.h>') */
INTDEF NONNULL((1, 2, 3, 5)) errno_t NOTHROW_RPC(LIBCCALL libc_getpwnam_r)(const char *__restrict name, struct passwd *__restrict resultbuf, char *__restrict buffer, size_t buflen, struct passwd **__restrict result);
/* Read an entry from the password-file stream, opening it if necessary.
 * @return: 0 :     Success (`*result' is made to point at `resultbuf')
 * @return: ENOENT: The last entry has already been read (use `setpwent()' to rewind the database)
 * @return: ERANGE: The given `buflen' is too small (pass a larger value and try again)
 * @return: * :     Error (one of `E*' from `<errno.h>') */
INTDEF NONNULL((1, 2, 4)) errno_t NOTHROW_RPC(LIBCCALL libc_getpwent_r)(struct passwd *__restrict resultbuf, char *__restrict buffer, size_t buflen, struct passwd **__restrict result);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_USER_PWD_H */
