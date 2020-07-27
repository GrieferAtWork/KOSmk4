/* HASH CRC-32:0x97dfe2e4 */
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
#ifndef GUARD_LIBC_USER_ALIASES_H
#define GUARD_LIBC_USER_ALIASES_H 1

#include "../api.h"
#include "../auto/aliases.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <aliases.h>

DECL_BEGIN

#ifndef __KERNEL__
/* Rewind/Open the internal mail alias database file (which is located in `/etc/aliases') */
INTDEF void NOTHROW_RPC_KOS(LIBCCALL libc_setaliasent)(void);
/* Close the internal mail alias database file (s.a. `setaliasent(3)') */
INTDEF void NOTHROW_NCX(LIBCCALL libc_endaliasent)(void);
/* Read the entry entry from the mail alias alias database.
 * If the database hadn't already been opened, this function will
 * open it the same way that a call to `setaliasent(3)' would.
 * @return: * :   A pointer to an internal, statically allocated structure
 * @return: NULL: [errno=<unchanged>] Database end has been reached
 * @return: NULL: [errno=ENOENT]      Database end has been reached
 * @return: NULL: [errno=*]           Error */
INTDEF WUNUSED struct aliasent *NOTHROW_RPC_KOS(LIBCCALL libc_getaliasent)(void);
/* Reentrant variant of `getaliasent(3)' (s.a. similar functions such as `getpwent_r(3)') */
INTDEF NONNULL((1, 2, 4)) errno_t NOTHROW_RPC_KOS(LIBCCALL libc_getaliasent_r)(struct aliasent *__restrict result_buf, char *__restrict buffer, size_t buflen, struct aliasent **__restrict result);
/* Find a database entry associated with the given `name'
 * @return: * :   A pointer to an internal, statically allocated structure
 * @return: NULL: [errno=ENOENT] No entry matching `name'
 * @return: NULL: [errno=*]      Error */
INTDEF WUNUSED NONNULL((1)) struct aliasent *NOTHROW_RPC_KOS(LIBCCALL libc_getaliasbyname)(char const *name);
/* Reentrant variant of `getaliasbyname(3)' (s.a. similar functions such as `getpwnam_r(3)') */
INTDEF NONNULL((1, 2, 3, 5)) errno_t NOTHROW_RPC_KOS(LIBCCALL libc_getaliasbyname_r)(char const *__restrict name, struct aliasent *__restrict result_buf, char *__restrict buffer, size_t buflen, struct aliasent **__restrict result);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_USER_ALIASES_H */
