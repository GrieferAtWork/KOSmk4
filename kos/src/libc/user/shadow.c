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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_USER_SHADOW_C
#define GUARD_LIBC_USER_SHADOW_C 1

#include "../api.h"
#include "shadow.h"

DECL_BEGIN





/*[[[start:implementation]]]*/

/*[[[head:setspent,hash:CRC-32=0x6dfa6052]]]*/
/* Open database for reading.
 * This function is not part of POSIX and therefore no official cancellation point */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.database.shadow.setspent") void
NOTHROW_RPC(LIBCCALL libc_setspent)(void)
/*[[[body:setspent]]]*/
{
	CRT_UNIMPLEMENTED("setspent"); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:setspent]]]*/

/*[[[head:endspent,hash:CRC-32=0xfff1c73f]]]*/
/* Close database. */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.database.shadow.endspent") void
NOTHROW_RPC_NOKOS(LIBCCALL libc_endspent)(void)
/*[[[body:endspent]]]*/
{
	CRT_UNIMPLEMENTED("endspent"); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:endspent]]]*/

/*[[[head:getspent,hash:CRC-32=0xf659bab2]]]*/
/* Get next entry from database, perhaps after opening the file.
 * This function is not part of POSIX and therefore no official cancellation point */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.database.shadow.getspent") struct spwd *
NOTHROW_RPC(LIBCCALL libc_getspent)(void)
/*[[[body:getspent]]]*/
{
	CRT_UNIMPLEMENTED("getspent"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:getspent]]]*/

/*[[[head:getspnam,hash:CRC-32=0xc935ac36]]]*/
/* Get shadow entry matching NAME.
 * This function is not part of POSIX and therefore no official cancellation point */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.database.shadow.getspnam") struct spwd *
NOTHROW_RPC(LIBCCALL libc_getspnam)(char const *__restrict name)
/*[[[body:getspnam]]]*/
{
	(void)name;
	CRT_UNIMPLEMENTED("getspnam"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:getspnam]]]*/

/*[[[head:sgetspent,hash:CRC-32=0x4064e4e9]]]*/
/* Read shadow entry from STRING.
 * This function is not part of POSIX and therefore no official cancellation point */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.database.shadow.sgetspent") struct spwd *
NOTHROW_RPC(LIBCCALL libc_sgetspent)(char const *__restrict string)
/*[[[body:sgetspent]]]*/
{
	(void)string;
	CRT_UNIMPLEMENTED("sgetspent"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:sgetspent]]]*/

/*[[[head:fgetspent,hash:CRC-32=0xd70c1a72]]]*/
/* Read next shadow entry from STREAM.
 * This function is not part of POSIX and therefore no official cancellation point */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.database.shadow.fgetspent") struct spwd *
NOTHROW_RPC(LIBCCALL libc_fgetspent)(FILE *__restrict stream)
/*[[[body:fgetspent]]]*/
{
	(void)stream;
	CRT_UNIMPLEMENTED("fgetspent"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:fgetspent]]]*/

/*[[[head:putspent,hash:CRC-32=0x40464108]]]*/
/* Write line containing shadow password entry to stream.
 * This function is not part of POSIX and therefore no official cancellation point */
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.database.shadow.putspent") int
NOTHROW_RPC(LIBCCALL libc_putspent)(struct spwd const *__restrict p,
                                    FILE *__restrict stream)
/*[[[body:putspent]]]*/
{
	(void)p;
	(void)stream;
	CRT_UNIMPLEMENTED("putspent"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:putspent]]]*/

/*[[[head:getspent_r,hash:CRC-32=0xbd8ea05f]]]*/
/* Reentrant versions of some of the functions above.
 * These functions are not part of POSIX and therefore no official cancellation point */
INTERN NONNULL((1, 2, 4))
ATTR_WEAK ATTR_SECTION(".text.crt.database.shadow.getspent_r") int
NOTHROW_RPC(LIBCCALL libc_getspent_r)(struct spwd *__restrict result_buf,
                                      char *__restrict buffer,
                                      size_t buflen,
                                      struct spwd **__restrict result)
/*[[[body:getspent_r]]]*/
{
	(void)result_buf;
	(void)buffer;
	(void)buflen;
	(void)result;
	CRT_UNIMPLEMENTED("getspent_r"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:getspent_r]]]*/

/*[[[head:getspnam_r,hash:CRC-32=0x2d32830b]]]*/
/* Reentrant versions of some of the functions above.
 * These functions are not part of POSIX and therefore no official cancellation point */
INTERN NONNULL((1, 2, 3, 5))
ATTR_WEAK ATTR_SECTION(".text.crt.database.shadow.getspnam_r") int
NOTHROW_RPC(LIBCCALL libc_getspnam_r)(char const *__restrict name,
                                      struct spwd *__restrict result_buf,
                                      char *__restrict buffer,
                                      size_t buflen,
                                      struct spwd **__restrict result)
/*[[[body:getspnam_r]]]*/
{
	(void)name;
	(void)result_buf;
	(void)buffer;
	(void)buflen;
	(void)result;
	CRT_UNIMPLEMENTED("getspnam_r"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:getspnam_r]]]*/

/*[[[head:sgetspent_r,hash:CRC-32=0x1761f05]]]*/
/* Reentrant versions of some of the functions above.
 * These functions are not part of POSIX and therefore no official cancellation point */
INTERN NONNULL((1, 2, 3, 5))
ATTR_WEAK ATTR_SECTION(".text.crt.database.shadow.sgetspent_r") int
NOTHROW_RPC(LIBCCALL libc_sgetspent_r)(char const *__restrict string,
                                       struct spwd *__restrict result_buf,
                                       char *__restrict buffer,
                                       size_t buflen,
                                       struct spwd **__restrict result)
/*[[[body:sgetspent_r]]]*/
{
	(void)string;
	(void)result_buf;
	(void)buffer;
	(void)buflen;
	(void)result;
	CRT_UNIMPLEMENTED("sgetspent_r"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:sgetspent_r]]]*/

/*[[[head:fgetspent_r,hash:CRC-32=0xf54bf1bf]]]*/
/* Reentrant versions of some of the functions above.
 * These functions are not part of POSIX and therefore no official cancellation point */
INTERN NONNULL((1, 2, 3, 5))
ATTR_WEAK ATTR_SECTION(".text.crt.database.shadow.fgetspent_r") int
NOTHROW_RPC(LIBCCALL libc_fgetspent_r)(FILE *__restrict stream,
                                       struct spwd *__restrict result_buf,
                                       char *__restrict buffer,
                                       size_t buflen,
                                       struct spwd **__restrict result)
/*[[[body:fgetspent_r]]]*/
{
	(void)stream;
	(void)result_buf;
	(void)buffer;
	(void)buflen;
	(void)result;
	CRT_UNIMPLEMENTED("fgetspent_r"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:fgetspent_r]]]*/

/*[[[head:lckpwdf,hash:CRC-32=0xcb3c07b7]]]*/
/* Protect password file against multi writers */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.database.shadow.lckpwdf") int
NOTHROW_RPC_KOS(LIBCCALL libc_lckpwdf)(void)
/*[[[body:lckpwdf]]]*/
{
	CRT_UNIMPLEMENTED("lckpwdf"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:lckpwdf]]]*/

/*[[[head:ulckpwdf,hash:CRC-32=0x9ba809e4]]]*/
/* Unlock password file */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.database.shadow.ulckpwdf") int
NOTHROW_NCX(LIBCCALL libc_ulckpwdf)(void)
/*[[[body:ulckpwdf]]]*/
{
	CRT_UNIMPLEMENTED("ulckpwdf"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:ulckpwdf]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:CRC-32=0x13b46cd0]]]*/
DEFINE_PUBLIC_WEAK_ALIAS(setspent, libc_setspent);
DEFINE_PUBLIC_WEAK_ALIAS(endspent, libc_endspent);
DEFINE_PUBLIC_WEAK_ALIAS(getspent, libc_getspent);
DEFINE_PUBLIC_WEAK_ALIAS(getspnam, libc_getspnam);
DEFINE_PUBLIC_WEAK_ALIAS(sgetspent, libc_sgetspent);
DEFINE_PUBLIC_WEAK_ALIAS(fgetspent, libc_fgetspent);
DEFINE_PUBLIC_WEAK_ALIAS(putspent, libc_putspent);
DEFINE_PUBLIC_WEAK_ALIAS(getspent_r, libc_getspent_r);
DEFINE_PUBLIC_WEAK_ALIAS(getspnam_r, libc_getspnam_r);
DEFINE_PUBLIC_WEAK_ALIAS(sgetspent_r, libc_sgetspent_r);
DEFINE_PUBLIC_WEAK_ALIAS(fgetspent_r, libc_fgetspent_r);
DEFINE_PUBLIC_WEAK_ALIAS(lckpwdf, libc_lckpwdf);
DEFINE_PUBLIC_WEAK_ALIAS(ulckpwdf, libc_ulckpwdf);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_SHADOW_C */
