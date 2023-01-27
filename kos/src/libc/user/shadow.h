/* HASH CRC-32:0xd897ddb3 */
/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_USER_SHADOW_H
#define GUARD_LIBC_USER_SHADOW_H 1

#include "../api.h"
#include "../auto/shadow.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <shadow.h>

DECL_BEGIN

#ifndef __KERNEL__
INTDEF void NOTHROW_RPC(LIBCCALL libc_setspent)(void);
INTDEF void NOTHROW_RPC_NOKOS(LIBCCALL libc_endspent)(void);
INTDEF WUNUSED struct spwd *NOTHROW_RPC(LIBCCALL libc_getspent)(void);
/* >> getspnam(3)
 * Search for an entry with a matching username
 * @return: * :                         A pointer to the read shadow entry
 * @return: NULL: (errno = <unchanged>) No entry for `name' exists
 * @return: NULL: (errno = <changed>)   Error (s.a. `errno') */
INTDEF WUNUSED ATTR_IN(1) struct spwd *NOTHROW_RPC(LIBCCALL libc_getspnam)(char const *__restrict name);
/* >> fgetpwent(3)
 * Read an entry from `stream'
 * @return: * :                         A pointer to the read password entry
 * @return: NULL: (errno = <unchanged>) The last entry has already been read
 *                                      (use `rewind(stream)' to rewind the database)
 * @return: NULL: (errno = <changed>)   Error (s.a. `errno') */
INTDEF WUNUSED ATTR_INOUT(1) struct spwd *NOTHROW_RPC(LIBCCALL libc_fgetspent)(FILE *__restrict stream);
INTDEF ATTR_OUT(1) ATTR_OUT(4) ATTR_OUTS(2, 3) errno_t NOTHROW_RPC(LIBCCALL libc_getspent_r)(struct spwd *__restrict resultbuf, char *__restrict buffer, size_t buflen, struct spwd **__restrict result);
INTDEF ATTR_IN(1) ATTR_OUT(2) ATTR_OUT(5) ATTR_OUTS(3, 4) errno_t NOTHROW_RPC(LIBCCALL libc_getspnam_r)(char const *__restrict name, struct spwd *__restrict resultbuf, char *__restrict buffer, size_t buflen, struct spwd **__restrict result);
INTDEF int NOTHROW_RPC_KOS(LIBCCALL libc_lckpwdf)(void);
INTDEF int NOTHROW_NCX(LIBCCALL libc_ulckpwdf)(void);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_USER_SHADOW_H */
