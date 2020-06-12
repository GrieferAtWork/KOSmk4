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
#ifndef GUARD_LIBC_USER_SHADOW_C
#define GUARD_LIBC_USER_SHADOW_C 1

#include "../api.h"
#include "shadow.h"

DECL_BEGIN





/*[[[start:implementation]]]*/

/*[[[head:libc_setspent,hash:CRC-32=0x381becd4]]]*/
/* Open database for reading.
 * This function is not part of POSIX and therefore no official cancellation point */
INTERN ATTR_SECTION(".text.crt.database.shadow") void
NOTHROW_RPC(LIBCCALL libc_setspent)(void)
/*[[[body:libc_setspent]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("setspent"); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:libc_setspent]]]*/

/*[[[head:libc_endspent,hash:CRC-32=0x35b44d37]]]*/
/* Close database. */
INTERN ATTR_SECTION(".text.crt.database.shadow") void
NOTHROW_RPC_NOKOS(LIBCCALL libc_endspent)(void)
/*[[[body:libc_endspent]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("endspent"); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:libc_endspent]]]*/

/*[[[head:libc_getspent,hash:CRC-32=0x895461bd]]]*/
/* Get next entry from database, perhaps after opening the file.
 * This function is not part of POSIX and therefore no official cancellation point */
INTERN ATTR_SECTION(".text.crt.database.shadow") struct spwd *
NOTHROW_RPC(LIBCCALL libc_getspent)(void)
/*[[[body:libc_getspent]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("getspent"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_getspent]]]*/

/*[[[head:libc_getspnam,hash:CRC-32=0xe006374e]]]*/
/* Get shadow entry matching NAME.
 * This function is not part of POSIX and therefore no official cancellation point */
INTERN ATTR_SECTION(".text.crt.database.shadow") NONNULL((1)) struct spwd *
NOTHROW_RPC(LIBCCALL libc_getspnam)(char const *__restrict name)
/*[[[body:libc_getspnam]]]*/
/*AUTO*/{
	(void)name;
	CRT_UNIMPLEMENTED("getspnam"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_getspnam]]]*/

/*[[[head:libc_sgetspent,hash:CRC-32=0x4165ee3c]]]*/
/* Read shadow entry from STRING.
 * This function is not part of POSIX and therefore no official cancellation point */
INTERN ATTR_SECTION(".text.crt.database.shadow") NONNULL((1)) struct spwd *
NOTHROW_RPC(LIBCCALL libc_sgetspent)(char const *__restrict string)
/*[[[body:libc_sgetspent]]]*/
/*AUTO*/{
	(void)string;
	CRT_UNIMPLEMENTED("sgetspent"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_sgetspent]]]*/

/*[[[head:libc_fgetspent,hash:CRC-32=0xb3eb2a3e]]]*/
/* Read next shadow entry from STREAM.
 * This function is not part of POSIX and therefore no official cancellation point */
INTERN ATTR_SECTION(".text.crt.database.shadow") NONNULL((1)) struct spwd *
NOTHROW_RPC(LIBCCALL libc_fgetspent)(FILE *__restrict stream)
/*[[[body:libc_fgetspent]]]*/
/*AUTO*/{
	(void)stream;
	CRT_UNIMPLEMENTED("fgetspent"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_fgetspent]]]*/

/*[[[head:libc_putspent,hash:CRC-32=0x6a8112a4]]]*/
/* Write line containing shadow password entry to stream.
 * This function is not part of POSIX and therefore no official cancellation point */
INTERN ATTR_SECTION(".text.crt.database.shadow") NONNULL((1, 2)) int
NOTHROW_RPC(LIBCCALL libc_putspent)(struct spwd const *__restrict p,
                                    FILE *__restrict stream)
/*[[[body:libc_putspent]]]*/
/*AUTO*/{
	(void)p;
	(void)stream;
	CRT_UNIMPLEMENTED("putspent"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_putspent]]]*/

/*[[[head:libc_getspent_r,hash:CRC-32=0xfab378af]]]*/
/* Reentrant versions of some of the functions above.
 * These functions are not part of POSIX and therefore no official cancellation point */
INTERN ATTR_SECTION(".text.crt.database.shadow") NONNULL((1, 2, 4)) int
NOTHROW_RPC(LIBCCALL libc_getspent_r)(struct spwd *__restrict result_buf,
                                      char *__restrict buffer,
                                      size_t buflen,
                                      struct spwd **__restrict result)
/*[[[body:libc_getspent_r]]]*/
/*AUTO*/{
	(void)result_buf;
	(void)buffer;
	(void)buflen;
	(void)result;
	CRT_UNIMPLEMENTED("getspent_r"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_getspent_r]]]*/

/*[[[head:libc_getspnam_r,hash:CRC-32=0x5629111e]]]*/
/* Reentrant versions of some of the functions above.
 * These functions are not part of POSIX and therefore no official cancellation point */
INTERN ATTR_SECTION(".text.crt.database.shadow") NONNULL((1, 2, 3, 5)) int
NOTHROW_RPC(LIBCCALL libc_getspnam_r)(char const *__restrict name,
                                      struct spwd *__restrict result_buf,
                                      char *__restrict buffer,
                                      size_t buflen,
                                      struct spwd **__restrict result)
/*[[[body:libc_getspnam_r]]]*/
/*AUTO*/{
	(void)name;
	(void)result_buf;
	(void)buffer;
	(void)buflen;
	(void)result;
	CRT_UNIMPLEMENTED("getspnam_r"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_getspnam_r]]]*/

/*[[[head:libc_sgetspent_r,hash:CRC-32=0x1a7bc87]]]*/
/* Reentrant versions of some of the functions above.
 * These functions are not part of POSIX and therefore no official cancellation point */
INTERN ATTR_SECTION(".text.crt.database.shadow") NONNULL((1, 2, 3, 5)) int
NOTHROW_RPC(LIBCCALL libc_sgetspent_r)(char const *__restrict string,
                                       struct spwd *__restrict result_buf,
                                       char *__restrict buffer,
                                       size_t buflen,
                                       struct spwd **__restrict result)
/*[[[body:libc_sgetspent_r]]]*/
/*AUTO*/{
	(void)string;
	(void)result_buf;
	(void)buffer;
	(void)buflen;
	(void)result;
	CRT_UNIMPLEMENTED("sgetspent_r"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_sgetspent_r]]]*/

/*[[[head:libc_fgetspent_r,hash:CRC-32=0x799adf59]]]*/
/* Reentrant versions of some of the functions above.
 * These functions are not part of POSIX and therefore no official cancellation point */
INTERN ATTR_SECTION(".text.crt.database.shadow") NONNULL((1, 2, 3, 5)) int
NOTHROW_RPC(LIBCCALL libc_fgetspent_r)(FILE *__restrict stream,
                                       struct spwd *__restrict result_buf,
                                       char *__restrict buffer,
                                       size_t buflen,
                                       struct spwd **__restrict result)
/*[[[body:libc_fgetspent_r]]]*/
/*AUTO*/{
	(void)stream;
	(void)result_buf;
	(void)buffer;
	(void)buflen;
	(void)result;
	CRT_UNIMPLEMENTED("fgetspent_r"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_fgetspent_r]]]*/

/*[[[head:libc_lckpwdf,hash:CRC-32=0x52f047fc]]]*/
/* Protect password file against multi writers */
INTERN ATTR_SECTION(".text.crt.database.shadow") int
NOTHROW_RPC_KOS(LIBCCALL libc_lckpwdf)(void)
/*[[[body:libc_lckpwdf]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("lckpwdf"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_lckpwdf]]]*/

/*[[[head:libc_ulckpwdf,hash:CRC-32=0x9ca5bf33]]]*/
/* Unlock password file */
INTERN ATTR_SECTION(".text.crt.database.shadow") int
NOTHROW_NCX(LIBCCALL libc_ulckpwdf)(void)
/*[[[body:libc_ulckpwdf]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("ulckpwdf"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_ulckpwdf]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:CRC-32=0xc9cf3d45]]]*/
DEFINE_PUBLIC_ALIAS(setspent, libc_setspent);
DEFINE_PUBLIC_ALIAS(endspent, libc_endspent);
DEFINE_PUBLIC_ALIAS(getspent, libc_getspent);
DEFINE_PUBLIC_ALIAS(getspnam, libc_getspnam);
DEFINE_PUBLIC_ALIAS(sgetspent, libc_sgetspent);
DEFINE_PUBLIC_ALIAS(fgetspent, libc_fgetspent);
DEFINE_PUBLIC_ALIAS(putspent, libc_putspent);
DEFINE_PUBLIC_ALIAS(getspent_r, libc_getspent_r);
DEFINE_PUBLIC_ALIAS(getspnam_r, libc_getspnam_r);
DEFINE_PUBLIC_ALIAS(sgetspent_r, libc_sgetspent_r);
DEFINE_PUBLIC_ALIAS(fgetspent_r, libc_fgetspent_r);
DEFINE_PUBLIC_ALIAS(lckpwdf, libc_lckpwdf);
DEFINE_PUBLIC_ALIAS(ulckpwdf, libc_ulckpwdf);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_SHADOW_C */
