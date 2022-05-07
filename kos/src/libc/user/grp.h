/* HASH CRC-32:0xd435207e */
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
#ifndef GUARD_LIBC_USER_GRP_H
#define GUARD_LIBC_USER_GRP_H 1

#include "../api.h"
#include "../auto/grp.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <grp.h>

DECL_BEGIN

#ifndef __KERNEL__
/* >> getgrgid(3), getgrgid_r(3) */
INTDEF WUNUSED struct group *NOTHROW_RPC(LIBCCALL libc_getgrgid)(gid_t gid);
/* >> getgrnam(3), getgrnam_r(3) */
INTDEF WUNUSED NONNULL((1)) struct group *NOTHROW_RPC(LIBCCALL libc_getgrnam)(char const *__restrict name);
/* >> setgrent(3) */
INTDEF void NOTHROW_RPC(LIBCCALL libc_setgrent)(void);
/* >> endgrent(3) */
INTDEF void NOTHROW_RPC_NOKOS(LIBCCALL libc_endgrent)(void);
/* >> getgrent(3), getgrent_r(3) */
INTDEF WUNUSED struct group *NOTHROW_RPC(LIBCCALL libc_getgrent)(void);
/* >> getgrgid(3), getgrgid_r(3) */
INTDEF NONNULL((2, 3, 5)) int NOTHROW_RPC(LIBCCALL libc_getgrgid_r)(gid_t gid, struct group *__restrict resultbuf, char *__restrict buffer, size_t buflen, struct group **__restrict result);
/* >> getgrnam(3), getgrnam_r(3) */
INTDEF NONNULL((1, 2, 3, 5)) int NOTHROW_RPC(LIBCCALL libc_getgrnam_r)(char const *__restrict name, struct group *__restrict resultbuf, char *__restrict buffer, size_t buflen, struct group **__restrict result);
/* >> getgrent(3), getgrent_r(3) */
INTDEF NONNULL((1, 2, 4)) int NOTHROW_RPC(LIBCCALL libc_getgrent_r)(struct group *__restrict resultbuf, char *__restrict buffer, size_t buflen, struct group **__restrict result);
/* >> fgetgrent(3), fgetgrent_r(3) */
INTDEF NONNULL((1)) struct group *NOTHROW_RPC(LIBCCALL libc_fgetgrent)(FILE *__restrict stream);
/* >> setgroups(2) */
INTDEF int NOTHROW_RPC(LIBCCALL libc_setgroups)(size_t count, gid_t const *groups);
/* >> getgrouplist(3) */
INTDEF NONNULL((1, 3, 4)) int NOTHROW_RPC(LIBCCALL libc_getgrouplist)(char const *user, gid_t group, gid_t *groups, int *ngroups);
/* >> initgroups(3) */
INTDEF NONNULL((1)) int NOTHROW_RPC(LIBCCALL libc_initgroups)(char const *user, gid_t group);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_USER_GRP_H */
