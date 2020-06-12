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
#ifndef GUARD_LIBC_USER_PWD_C
#define GUARD_LIBC_USER_PWD_C 1

#include "../api.h"
#include "pwd.h"

DECL_BEGIN





/*[[[start:implementation]]]*/

/*[[[head:libc_getpwuid,hash:CRC-32=0x10df5116]]]*/
/* Search for an entry with a matching user ID */
INTERN ATTR_SECTION(".text.crt.database.pwd") struct passwd *
NOTHROW_RPC(LIBCCALL libc_getpwuid)(uid_t uid)
/*[[[body:libc_getpwuid]]]*/
/*AUTO*/{
	(void)uid;
	CRT_UNIMPLEMENTED("getpwuid"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_getpwuid]]]*/

/*[[[head:libc_getpwnam,hash:CRC-32=0xb70caa93]]]*/
/* Search for an entry with a matching username */
INTERN ATTR_SECTION(".text.crt.database.pwd") NONNULL((1)) struct passwd *
NOTHROW_RPC(LIBCCALL libc_getpwnam)(const char *name)
/*[[[body:libc_getpwnam]]]*/
/*AUTO*/{
	(void)name;
	CRT_UNIMPLEMENTED("getpwnam"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_getpwnam]]]*/

/*[[[head:libc_setpwent,hash:CRC-32=0x48c06094]]]*/
/* Rewind the password-file stream */
INTERN ATTR_SECTION(".text.crt.database.pwd") void
NOTHROW_RPC(LIBCCALL libc_setpwent)(void)
/*[[[body:libc_setpwent]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("setpwent"); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:libc_setpwent]]]*/

/*[[[head:libc_endpwent,hash:CRC-32=0xe5d5a03]]]*/
/* Close the password-file stream */
INTERN ATTR_SECTION(".text.crt.database.pwd") void
NOTHROW_RPC_NOKOS(LIBCCALL libc_endpwent)(void)
/*[[[body:libc_endpwent]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("endpwent"); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:libc_endpwent]]]*/

/*[[[head:libc_getpwent,hash:CRC-32=0x33cc71c4]]]*/
/* Read an entry from the password-file stream, opening it if necessary */
INTERN ATTR_SECTION(".text.crt.database.pwd") struct passwd *
NOTHROW_RPC(LIBCCALL libc_getpwent)(void)
/*[[[body:libc_getpwent]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("getpwent"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_getpwent]]]*/

/*[[[head:libc_fgetpwent,hash:CRC-32=0xe7a3bc8a]]]*/
/* Read an entry from STREAM */
INTERN ATTR_SECTION(".text.crt.database.pwd") NONNULL((1)) struct passwd *
NOTHROW_RPC(LIBCCALL libc_fgetpwent)(FILE *__restrict stream)
/*[[[body:libc_fgetpwent]]]*/
/*AUTO*/{
	(void)stream;
	CRT_UNIMPLEMENTED("fgetpwent"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_fgetpwent]]]*/

/*[[[head:libc_putpwent,hash:CRC-32=0x1348ea31]]]*/
/* Write the given entry onto the given stream */
INTERN ATTR_SECTION(".text.crt.database.pwd") NONNULL((1, 2)) int
NOTHROW_RPC(LIBCCALL libc_putpwent)(struct passwd const *__restrict p,
                                    FILE *__restrict f)
/*[[[body:libc_putpwent]]]*/
/*AUTO*/{
	(void)p;
	(void)f;
	CRT_UNIMPLEMENTED("putpwent"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_putpwent]]]*/

/*[[[head:libc_getpwuid_r,hash:CRC-32=0xa1720d03]]]*/
/* Search for an entry with a matching user ID */
INTERN ATTR_SECTION(".text.crt.database.pwd") NONNULL((2, 3, 5)) int
NOTHROW_RPC(LIBCCALL libc_getpwuid_r)(__uid_t __uid,
                                      struct passwd *__restrict resultbuf,
                                      char *__restrict buffer,
                                      size_t buflen,
                                      struct passwd **__restrict result)
/*[[[body:libc_getpwuid_r]]]*/
/*AUTO*/{
	(void)__uid;
	(void)resultbuf;
	(void)buffer;
	(void)buflen;
	(void)result;
	CRT_UNIMPLEMENTED("getpwuid_r"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_getpwuid_r]]]*/

/*[[[head:libc_getpwnam_r,hash:CRC-32=0x349be2a1]]]*/
/* Search for an entry with a matching username */
INTERN ATTR_SECTION(".text.crt.database.pwd") NONNULL((1, 2, 3, 5)) int
NOTHROW_RPC(LIBCCALL libc_getpwnam_r)(const char *__restrict name,
                                      struct passwd *__restrict resultbuf,
                                      char *__restrict buffer,
                                      size_t buflen,
                                      struct passwd **__restrict result)
/*[[[body:libc_getpwnam_r]]]*/
/*AUTO*/{
	(void)name;
	(void)resultbuf;
	(void)buffer;
	(void)buflen;
	(void)result;
	CRT_UNIMPLEMENTED("getpwnam_r"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_getpwnam_r]]]*/

/*[[[head:libc_getpwent_r,hash:CRC-32=0xa8695877]]]*/
/* Read an entry from the password-file stream, opening it if necessary */
INTERN ATTR_SECTION(".text.crt.database.pwd") NONNULL((1, 2, 4)) int
NOTHROW_RPC(LIBCCALL libc_getpwent_r)(struct passwd *__restrict resultbuf,
                                      char *__restrict buffer,
                                      size_t buflen,
                                      struct passwd **__restrict result)
/*[[[body:libc_getpwent_r]]]*/
/*AUTO*/{
	(void)resultbuf;
	(void)buffer;
	(void)buflen;
	(void)result;
	CRT_UNIMPLEMENTED("getpwent_r"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_getpwent_r]]]*/

/*[[[head:libc_fgetpwent_r,hash:CRC-32=0x9740f0db]]]*/
/* Read an entry from STREAM. This function is not standardized and probably never will */
INTERN ATTR_SECTION(".text.crt.database.pwd") NONNULL((1, 2, 3, 5)) int
NOTHROW_RPC(LIBCCALL libc_fgetpwent_r)(FILE *__restrict stream,
                                       struct passwd *__restrict resultbuf,
                                       char *__restrict buffer,
                                       size_t buflen,
                                       struct passwd **__restrict result)
/*[[[body:libc_fgetpwent_r]]]*/
/*AUTO*/{
	(void)stream;
	(void)resultbuf;
	(void)buffer;
	(void)buflen;
	(void)result;
	CRT_UNIMPLEMENTED("fgetpwent_r"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_fgetpwent_r]]]*/

/*[[[head:libc_getpw,hash:CRC-32=0x23d394cf]]]*/
/* Re-construct the password-file line for the given uid in the
 * given buffer. This knows the format that the caller will
 * expect, but this need not be the format of the password file */
INTERN ATTR_SECTION(".text.crt.database.pwd") int
NOTHROW_RPC(LIBCCALL libc_getpw)(__uid_t uid,
                                 char *buffer)
/*[[[body:libc_getpw]]]*/
/*AUTO*/{
	(void)uid;
	(void)buffer;
	CRT_UNIMPLEMENTED("getpw"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_getpw]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:CRC-32=0x1ee579b4]]]*/
DEFINE_PUBLIC_ALIAS(setpwent, libc_setpwent);
DEFINE_PUBLIC_ALIAS(endpwent, libc_endpwent);
DEFINE_PUBLIC_ALIAS(getpwent, libc_getpwent);
DEFINE_PUBLIC_ALIAS(getpwuid, libc_getpwuid);
DEFINE_PUBLIC_ALIAS(getpwnam, libc_getpwnam);
DEFINE_PUBLIC_ALIAS(fgetpwent, libc_fgetpwent);
DEFINE_PUBLIC_ALIAS(putpwent, libc_putpwent);
DEFINE_PUBLIC_ALIAS(getpwuid_r, libc_getpwuid_r);
DEFINE_PUBLIC_ALIAS(getpwnam_r, libc_getpwnam_r);
DEFINE_PUBLIC_ALIAS(getpwent_r, libc_getpwent_r);
DEFINE_PUBLIC_ALIAS(fgetpwent_r, libc_fgetpwent_r);
DEFINE_PUBLIC_ALIAS(getpw, libc_getpw);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_PWD_C */
