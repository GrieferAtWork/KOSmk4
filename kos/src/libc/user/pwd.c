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
#ifndef GUARD_LIBC_USER_PWD_C
#define GUARD_LIBC_USER_PWD_C 1

#include "../api.h"
#include "pwd.h"

DECL_BEGIN





/*[[[start:implementation]]]*/

/*[[[head:getpwuid,hash:0xc325a731]]]*/
/* Search for an entry with a matching user ID */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.database.pwd.getpwuid") struct passwd *
NOTHROW_RPC(LIBCCALL libc_getpwuid)(uid_t uid)
/*[[[body:getpwuid]]]*/
{
	CRT_UNIMPLEMENTED("getpwuid"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:getpwuid]]]*/

/*[[[head:getpwnam,hash:0x32e4e474]]]*/
/* Search for an entry with a matching username */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.database.pwd.getpwnam") struct passwd *
NOTHROW_RPC(LIBCCALL libc_getpwnam)(const char *name)
/*[[[body:getpwnam]]]*/
{
	CRT_UNIMPLEMENTED("getpwnam"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:getpwnam]]]*/

/*[[[head:setpwent,hash:0x7d679ba7]]]*/
/* Rewind the password-file stream */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.database.pwd.setpwent") void
NOTHROW_RPC(LIBCCALL libc_setpwent)(void)
/*[[[body:setpwent]]]*/
{
	CRT_UNIMPLEMENTED("setpwent"); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:setpwent]]]*/

/*[[[head:endpwent,hash:0xa7b0144f]]]*/
/* Close the password-file stream */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.database.pwd.endpwent") void
NOTHROW_RPC_NOKOS(LIBCCALL libc_endpwent)(void)
/*[[[body:endpwent]]]*/
{
	CRT_UNIMPLEMENTED("endpwent"); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:endpwent]]]*/

/*[[[head:getpwent,hash:0x1f18db96]]]*/
/* Read an entry from the password-file stream, opening it if necessary */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.database.pwd.getpwent") struct passwd *
NOTHROW_RPC(LIBCCALL libc_getpwent)(void)
/*[[[body:getpwent]]]*/
{
	CRT_UNIMPLEMENTED("getpwent"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:getpwent]]]*/

/*[[[head:fgetpwent,hash:0x19027b20]]]*/
/* Read an entry from STREAM */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.database.pwd.fgetpwent") struct passwd *
NOTHROW_RPC(LIBCCALL libc_fgetpwent)(FILE *__restrict stream)
/*[[[body:fgetpwent]]]*/
{
	CRT_UNIMPLEMENTED("fgetpwent"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:fgetpwent]]]*/

/*[[[head:putpwent,hash:0x515a663f]]]*/
/* Write the given entry onto the given stream */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.database.pwd.putpwent") int
NOTHROW_RPC(LIBCCALL libc_putpwent)(struct passwd const *__restrict p,
                                    FILE *__restrict f)
/*[[[body:putpwent]]]*/
{
	CRT_UNIMPLEMENTED("putpwent"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:putpwent]]]*/

/*[[[head:getpwuid_r,hash:0xc6108571]]]*/
/* Search for an entry with a matching user ID */
INTERN NONNULL((2, 3, 5))
ATTR_WEAK ATTR_SECTION(".text.crt.database.pwd.getpwuid_r") int
NOTHROW_RPC(LIBCCALL libc_getpwuid_r)(__uid_t __uid,
                                      struct passwd *__restrict resultbuf,
                                      char *__restrict buffer,
                                      size_t buflen,
                                      struct passwd **__restrict result)
/*[[[body:getpwuid_r]]]*/
{
	CRT_UNIMPLEMENTED("getpwuid_r"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:getpwuid_r]]]*/

/*[[[head:getpwnam_r,hash:0x6ccf8663]]]*/
/* Search for an entry with a matching username */
INTERN NONNULL((1, 2, 3, 5))
ATTR_WEAK ATTR_SECTION(".text.crt.database.pwd.getpwnam_r") int
NOTHROW_RPC(LIBCCALL libc_getpwnam_r)(const char *__restrict name,
                                      struct passwd *__restrict resultbuf,
                                      char *__restrict buffer,
                                      size_t buflen,
                                      struct passwd **__restrict result)
/*[[[body:getpwnam_r]]]*/
{
	CRT_UNIMPLEMENTED("getpwnam_r"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:getpwnam_r]]]*/

/*[[[head:getpwent_r,hash:0x5dbe6d50]]]*/
/* Read an entry from the password-file stream, opening it if necessary */
INTERN NONNULL((1, 2, 4))
ATTR_WEAK ATTR_SECTION(".text.crt.database.pwd.getpwent_r") int
NOTHROW_RPC(LIBCCALL libc_getpwent_r)(struct passwd *__restrict resultbuf,
                                      char *__restrict buffer,
                                      size_t buflen,
                                      struct passwd **__restrict result)
/*[[[body:getpwent_r]]]*/
{
	CRT_UNIMPLEMENTED("getpwent_r"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:getpwent_r]]]*/

/*[[[head:fgetpwent_r,hash:0x797ab55c]]]*/
/* Read an entry from STREAM */
INTERN NONNULL((1, 2, 3, 5))
ATTR_WEAK ATTR_SECTION(".text.crt.database.pwd.fgetpwent_r") int
NOTHROW_RPC(LIBCCALL libc_fgetpwent_r)(FILE *__restrict stream,
                                       struct passwd *__restrict resultbuf,
                                       char *__restrict buffer,
                                       size_t buflen,
                                       struct passwd **__restrict result)
/*[[[body:fgetpwent_r]]]*/
{
	CRT_UNIMPLEMENTED("fgetpwent_r"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:fgetpwent_r]]]*/

/*[[[head:getpw,hash:0x22b9c1f7]]]*/
/* Re-construct the password-file line for the given uid in the
 * given buffer. This knows the format that the caller will
 * expect, but this need not be the format of the password file */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.database.pwd.getpw") int
NOTHROW_RPC(LIBCCALL libc_getpw)(__uid_t uid,
                                 char *buffer)
/*[[[body:getpw]]]*/
{
	CRT_UNIMPLEMENTED("getpw"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:getpw]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:0xe299da17]]]*/
DEFINE_PUBLIC_WEAK_ALIAS(getpwuid, libc_getpwuid);
DEFINE_PUBLIC_WEAK_ALIAS(getpwnam, libc_getpwnam);
DEFINE_PUBLIC_WEAK_ALIAS(setpwent, libc_setpwent);
DEFINE_PUBLIC_WEAK_ALIAS(endpwent, libc_endpwent);
DEFINE_PUBLIC_WEAK_ALIAS(getpwent, libc_getpwent);
DEFINE_PUBLIC_WEAK_ALIAS(getpwuid, libc_getpwuid);
DEFINE_PUBLIC_WEAK_ALIAS(getpwnam, libc_getpwnam);
DEFINE_PUBLIC_WEAK_ALIAS(fgetpwent, libc_fgetpwent);
DEFINE_PUBLIC_WEAK_ALIAS(putpwent, libc_putpwent);
DEFINE_PUBLIC_WEAK_ALIAS(getpwuid_r, libc_getpwuid_r);
DEFINE_PUBLIC_WEAK_ALIAS(getpwnam_r, libc_getpwnam_r);
DEFINE_PUBLIC_WEAK_ALIAS(getpwent_r, libc_getpwent_r);
DEFINE_PUBLIC_WEAK_ALIAS(fgetpwent_r, libc_fgetpwent_r);
DEFINE_PUBLIC_WEAK_ALIAS(getpw, libc_getpw);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_PWD_C */
