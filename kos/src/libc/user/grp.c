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
#ifndef GUARD_LIBC_USER_GRP_C
#define GUARD_LIBC_USER_GRP_C 1

#include "../api.h"
/**/

#include <kos/syscalls.h>

#include <syscall.h>

#include "grp.h"

DECL_BEGIN





/*[[[start:implementation]]]*/

/*[[[head:libc_getgrgid,hash:CRC-32=0xb6ef74b6]]]*/
/* >> getgrgid(3), getgrgid_r(3) */
INTERN ATTR_SECTION(".text.crt.database.group") struct group *
NOTHROW_RPC(LIBCCALL libc_getgrgid)(gid_t gid)
/*[[[body:libc_getgrgid]]]*/
/*AUTO*/{
	(void)gid;
	CRT_UNIMPLEMENTEDF("getgrgid(%" PRIxN(__SIZEOF_GID_T__) ")", gid); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_getgrgid]]]*/

/*[[[head:libc_getgrnam,hash:CRC-32=0xdf2e267e]]]*/
/* >> getgrnam(3), getgrnam_r(3) */
INTERN ATTR_SECTION(".text.crt.database.group") NONNULL((1)) struct group *
NOTHROW_RPC(LIBCCALL libc_getgrnam)(char const *__restrict name)
/*[[[body:libc_getgrnam]]]*/
/*AUTO*/{
	(void)name;
	CRT_UNIMPLEMENTEDF("getgrnam(%q)", name); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_getgrnam]]]*/

/*[[[head:libc_setgrent,hash:CRC-32=0x3b216a03]]]*/
/* >> setgrent(3) */
INTERN ATTR_SECTION(".text.crt.database.group") void
NOTHROW_RPC(LIBCCALL libc_setgrent)(void)
/*[[[body:libc_setgrent]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("setgrent"); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:libc_setgrent]]]*/

/*[[[head:libc_endgrent,hash:CRC-32=0x22183a08]]]*/
/* >> endgrent(3) */
INTERN ATTR_SECTION(".text.crt.database.group") void
NOTHROW_RPC_NOKOS(LIBCCALL libc_endgrent)(void)
/*[[[body:libc_endgrent]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("endgrent"); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:libc_endgrent]]]*/

/*[[[head:libc_getgrent,hash:CRC-32=0x943e44f3]]]*/
/* >> getgrent(3), getgrent_r(3) */
INTERN ATTR_SECTION(".text.crt.database.group") struct group *
NOTHROW_RPC(LIBCCALL libc_getgrent)(void)
/*[[[body:libc_getgrent]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("getgrent"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_getgrent]]]*/

/*[[[head:libc_putgrent,hash:CRC-32=0xc0f4a7c4]]]*/
/* >> putgrent(3) */
INTERN ATTR_SECTION(".text.crt.database.group") NONNULL((1, 2)) int
NOTHROW_RPC(LIBCCALL libc_putgrent)(struct group const *__restrict entry,
                                    FILE *__restrict stream)
/*[[[body:libc_putgrent]]]*/
/*AUTO*/{
	(void)entry;
	(void)stream;
	CRT_UNIMPLEMENTEDF("putgrent(%p, %p)", entry, stream); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_putgrent]]]*/

/*[[[head:libc_getgrgid_r,hash:CRC-32=0x693b1077]]]*/
/* >> getgrgid(3), getgrgid_r(3) */
INTERN ATTR_SECTION(".text.crt.database.group") NONNULL((2, 3, 5)) int
NOTHROW_RPC(LIBCCALL libc_getgrgid_r)(gid_t gid,
                                      struct group *__restrict resultbuf,
                                      char *__restrict buffer,
                                      size_t buflen,
                                      struct group **__restrict result)
/*[[[body:libc_getgrgid_r]]]*/
/*AUTO*/{
	(void)gid;
	(void)resultbuf;
	(void)buffer;
	(void)buflen;
	(void)result;
	CRT_UNIMPLEMENTEDF("getgrgid_r(%" PRIxN(__SIZEOF_GID_T__) ", %p, %q, %Ix, %p)", gid, resultbuf, buffer, buflen, result); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_getgrgid_r]]]*/

/*[[[head:libc_getgrnam_r,hash:CRC-32=0x31f0eb7]]]*/
/* >> getgrnam(3), getgrnam_r(3) */
INTERN ATTR_SECTION(".text.crt.database.group") NONNULL((1, 2, 3, 5)) int
NOTHROW_RPC(LIBCCALL libc_getgrnam_r)(char const *__restrict name,
                                      struct group *__restrict resultbuf,
                                      char *__restrict buffer,
                                      size_t buflen,
                                      struct group **__restrict result)
/*[[[body:libc_getgrnam_r]]]*/
/*AUTO*/{
	(void)name;
	(void)resultbuf;
	(void)buffer;
	(void)buflen;
	(void)result;
	CRT_UNIMPLEMENTEDF("getgrnam_r(%q, %p, %q, %Ix, %p)", name, resultbuf, buffer, buflen, result); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_getgrnam_r]]]*/

/*[[[head:libc_getgrent_r,hash:CRC-32=0x60227ef8]]]*/
/* >> getgrent(3), getgrent_r(3) */
INTERN ATTR_SECTION(".text.crt.database.group") NONNULL((1, 2, 4)) int
NOTHROW_RPC(LIBCCALL libc_getgrent_r)(struct group *__restrict resultbuf,
                                      char *__restrict buffer,
                                      size_t buflen,
                                      struct group **__restrict result)
/*[[[body:libc_getgrent_r]]]*/
/*AUTO*/{
	(void)resultbuf;
	(void)buffer;
	(void)buflen;
	(void)result;
	CRT_UNIMPLEMENTEDF("getgrent_r(%p, %q, %Ix, %p)", resultbuf, buffer, buflen, result); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_getgrent_r]]]*/

/*[[[head:libc_fgetgrent_r,hash:CRC-32=0x86119e41]]]*/
/* >> fgetgrent(3), fgetgrent_r(3) */
INTERN ATTR_SECTION(".text.crt.database.group") NONNULL((1, 2, 3, 5)) int
NOTHROW_RPC(LIBCCALL libc_fgetgrent_r)(FILE *__restrict stream,
                                       struct group *__restrict resultbuf,
                                       char *__restrict buffer,
                                       size_t buflen,
                                       struct group **__restrict result)
/*[[[body:libc_fgetgrent_r]]]*/
/*AUTO*/{
	(void)stream;
	(void)resultbuf;
	(void)buffer;
	(void)buflen;
	(void)result;
	CRT_UNIMPLEMENTEDF("fgetgrent_r(%p, %p, %q, %Ix, %p)", stream, resultbuf, buffer, buflen, result); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_fgetgrent_r]]]*/

/*[[[head:libc_fgetgrent,hash:CRC-32=0xd25bcde2]]]*/
/* >> fgetgrent(3), fgetgrent_r(3) */
INTERN ATTR_SECTION(".text.crt.database.group") NONNULL((1)) struct group *
NOTHROW_RPC(LIBCCALL libc_fgetgrent)(FILE *__restrict stream)
/*[[[body:libc_fgetgrent]]]*/
/*AUTO*/{
	(void)stream;
	CRT_UNIMPLEMENTEDF("fgetgrent(%p)", stream); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_fgetgrent]]]*/

/*[[[head:libc_setgroups,hash:CRC-32=0x1fc5c7b3]]]*/
/* >> setgroups(2) */
INTERN ATTR_SECTION(".text.crt.database.group") int
NOTHROW_RPC(LIBCCALL libc_setgroups)(size_t count,
                                     gid_t const *groups)
/*[[[body:libc_setgroups]]]*/
{
	errno_t error;
#if defined(SYS_setgroups32) && __SIZEOF_GID_T__ == 4
	error = sys_setgroups32(count, (u32 const *)groups);
#else /* SYS_setgroups32 && __SIZEOF_GID_T__ == 4 */
	error = sys_setgroups(count, groups);
#endif /* !SYS_setgroups32 || __SIZEOF_GID_T__ != 4 */
	return libc_seterrno_syserr(error);
}
/*[[[end:libc_setgroups]]]*/

/*[[[head:libc_getgrouplist,hash:CRC-32=0x75f93cf6]]]*/
/* >> getgrouplist(3) */
INTERN ATTR_SECTION(".text.crt.database.group") NONNULL((1, 3, 4)) int
NOTHROW_RPC(LIBCCALL libc_getgrouplist)(char const *user,
                                        gid_t group,
                                        gid_t *groups,
                                        int *ngroups)
/*[[[body:libc_getgrouplist]]]*/
/*AUTO*/{
	(void)user;
	(void)group;
	(void)groups;
	(void)ngroups;
	CRT_UNIMPLEMENTEDF("getgrouplist(%q, %" PRIxN(__SIZEOF_GID_T__) ", %p, %p)", user, group, groups, ngroups); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_getgrouplist]]]*/

/*[[[head:libc_initgroups,hash:CRC-32=0x78d27b62]]]*/
/* >> initgroups(3) */
INTERN ATTR_SECTION(".text.crt.database.group") NONNULL((1)) int
NOTHROW_RPC(LIBCCALL libc_initgroups)(char const *user,
                                      gid_t group)
/*[[[body:libc_initgroups]]]*/
/*AUTO*/{
	(void)user;
	(void)group;
	CRT_UNIMPLEMENTEDF("initgroups(%q, %" PRIxN(__SIZEOF_GID_T__) ")", user, group); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_initgroups]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:CRC-32=0x61a9e11e]]]*/
DEFINE_PUBLIC_ALIAS(getgrgid, libc_getgrgid);
DEFINE_PUBLIC_ALIAS(getgrnam, libc_getgrnam);
DEFINE_PUBLIC_ALIAS(setgrent, libc_setgrent);
DEFINE_PUBLIC_ALIAS(endgrent, libc_endgrent);
DEFINE_PUBLIC_ALIAS(getgrent, libc_getgrent);
DEFINE_PUBLIC_ALIAS(putgrent, libc_putgrent);
DEFINE_PUBLIC_ALIAS(getgrgid_r, libc_getgrgid_r);
DEFINE_PUBLIC_ALIAS(getgrnam_r, libc_getgrnam_r);
DEFINE_PUBLIC_ALIAS(getgrent_r, libc_getgrent_r);
DEFINE_PUBLIC_ALIAS(fgetgrent_r, libc_fgetgrent_r);
DEFINE_PUBLIC_ALIAS(fgetgrent, libc_fgetgrent);
DEFINE_PUBLIC_ALIAS(setgroups, libc_setgroups);
DEFINE_PUBLIC_ALIAS(getgrouplist, libc_getgrouplist);
DEFINE_PUBLIC_ALIAS(initgroups, libc_initgroups);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_GRP_C */
