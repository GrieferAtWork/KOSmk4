/* HASH CRC-32:0xf1b7c3d7 */
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
#ifndef GUARD_LIBC_AUTO_DOSABI_GRP_C
#define GUARD_LIBC_AUTO_DOSABI_GRP_C 1

#include "../../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../../user/grp.h"

DECL_BEGIN

/* Search for an entry with a matching group ID */
INTERN ATTR_SECTION(".text.crt.dos.database.group") struct group *
NOTHROW_RPC(LIBDCALL libd_getgrgid)(gid_t gid) {
	return libc_getgrgid(gid);
}
/* Search for an entry with a matching group name */
INTERN ATTR_SECTION(".text.crt.dos.database.group") NONNULL((1)) struct group *
NOTHROW_RPC(LIBDCALL libd_getgrnam)(char const *__restrict name) {
	return libc_getgrnam(name);
}
/* Write the given entry onto the given stream */
INTERN ATTR_SECTION(".text.crt.dos.database.group") NONNULL((1, 2)) int
NOTHROW_RPC(LIBDCALL libd_putgrent)(struct group const *__restrict entry,
                                    FILE *__restrict stream) {
	return libc_putgrent(entry, stream);
}
/* Search for an entry with a matching group ID */
INTERN ATTR_SECTION(".text.crt.dos.database.group") NONNULL((2, 3, 5)) int
NOTHROW_RPC(LIBDCALL libd_getgrgid_r)(gid_t gid,
                                      struct group *__restrict resultbuf,
                                      char *__restrict buffer,
                                      size_t buflen,
                                      struct group **__restrict result) {
	return libc_getgrgid_r(gid, resultbuf, buffer, buflen, result);
}
/* Search for an entry with a matching group name */
INTERN ATTR_SECTION(".text.crt.dos.database.group") NONNULL((1, 2, 3, 5)) int
NOTHROW_RPC(LIBDCALL libd_getgrnam_r)(char const *__restrict name,
                                      struct group *__restrict resultbuf,
                                      char *__restrict buffer,
                                      size_t buflen,
                                      struct group **__restrict result) {
	return libc_getgrnam_r(name, resultbuf, buffer, buflen, result);
}
/* Read an entry from the group-file stream, opening it if necessary */
INTERN ATTR_SECTION(".text.crt.dos.database.group") NONNULL((1, 2, 4)) int
NOTHROW_RPC(LIBDCALL libd_getgrent_r)(struct group *__restrict resultbuf,
                                      char *__restrict buffer,
                                      size_t buflen,
                                      struct group **__restrict result) {
	return libc_getgrent_r(resultbuf, buffer, buflen, result);
}
/* Read a group entry from STREAM */
INTERN ATTR_SECTION(".text.crt.dos.database.group") NONNULL((1, 2, 3, 5)) int
NOTHROW_RPC(LIBDCALL libd_fgetgrent_r)(FILE *__restrict stream,
                                       struct group *__restrict resultbuf,
                                       char *__restrict buffer,
                                       size_t buflen,
                                       struct group **__restrict result) {
	return libc_fgetgrent_r(stream, resultbuf, buffer, buflen, result);
}
/* Read a group entry from STREAM */
INTERN ATTR_SECTION(".text.crt.dos.database.group") NONNULL((1)) struct group *
NOTHROW_RPC(LIBDCALL libd_fgetgrent)(FILE *__restrict stream) {
	return libc_fgetgrent(stream);
}
/* Set the group set for the current user to GROUPS (N of them) */
INTERN ATTR_SECTION(".text.crt.dos.database.group") int
NOTHROW_RPC(LIBDCALL libd_setgroups)(size_t count,
                                     gid_t const *groups) {
	return libc_setgroups(count, groups);
}
/* Store at most *NGROUPS members of the group set for USER into
 * *GROUPS. Also include GROUP. The actual number of groups found is
 * returned in *NGROUPS.  Return -1 if the if *NGROUPS is too small */
INTERN ATTR_SECTION(".text.crt.dos.database.group") NONNULL((1, 3, 4)) int
NOTHROW_RPC(LIBDCALL libd_getgrouplist)(char const *user,
                                        gid_t group,
                                        gid_t *groups,
                                        int *ngroups) {
	return libc_getgrouplist(user, group, groups, ngroups);
}
/* Initialize the group set for the current user
 * by reading the group database and using all groups
 * of which USER is a member. Also include GROUP. */
INTERN ATTR_SECTION(".text.crt.dos.database.group") NONNULL((1)) int
NOTHROW_RPC(LIBDCALL libd_initgroups)(char const *user,
                                      gid_t group) {
	return libc_initgroups(user, group);
}

DECL_END

DEFINE_PUBLIC_ALIAS(DOS$getgrgid, libd_getgrgid);
DEFINE_PUBLIC_ALIAS(DOS$getgrnam, libd_getgrnam);
DEFINE_PUBLIC_ALIAS(DOS$putgrent, libd_putgrent);
DEFINE_PUBLIC_ALIAS(DOS$getgrgid_r, libd_getgrgid_r);
DEFINE_PUBLIC_ALIAS(DOS$getgrnam_r, libd_getgrnam_r);
DEFINE_PUBLIC_ALIAS(DOS$getgrent_r, libd_getgrent_r);
DEFINE_PUBLIC_ALIAS(DOS$fgetgrent_r, libd_fgetgrent_r);
DEFINE_PUBLIC_ALIAS(DOS$fgetgrent, libd_fgetgrent);
DEFINE_PUBLIC_ALIAS(DOS$setgroups, libd_setgroups);
DEFINE_PUBLIC_ALIAS(DOS$getgrouplist, libd_getgrouplist);
DEFINE_PUBLIC_ALIAS(DOS$initgroups, libd_initgroups);

#endif /* !GUARD_LIBC_AUTO_DOSABI_GRP_C */
