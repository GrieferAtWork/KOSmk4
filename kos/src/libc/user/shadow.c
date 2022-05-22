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
#ifndef GUARD_LIBC_USER_SHADOW_C
#define GUARD_LIBC_USER_SHADOW_C 1

#include "../api.h"
#include "shadow.h"

DECL_BEGIN

/*[[[head:libc_setspent,hash:CRC-32=0x8a151368]]]*/
INTERN ATTR_SECTION(".text.crt.database.shadow") void
NOTHROW_RPC(LIBCCALL libc_setspent)(void)
/*[[[body:libc_setspent]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("setspent"); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:libc_setspent]]]*/

/*[[[head:libc_endspent,hash:CRC-32=0x49326e3a]]]*/
INTERN ATTR_SECTION(".text.crt.database.shadow") void
NOTHROW_RPC_NOKOS(LIBCCALL libc_endspent)(void)
/*[[[body:libc_endspent]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("endspent"); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:libc_endspent]]]*/

/*[[[head:libc_getspent,hash:CRC-32=0x32f1ea92]]]*/
INTERN ATTR_SECTION(".text.crt.database.shadow") struct spwd *
NOTHROW_RPC(LIBCCALL libc_getspent)(void)
/*[[[body:libc_getspent]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("getspent"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_getspent]]]*/

/*[[[head:libc_getspnam,hash:CRC-32=0x956bc9da]]]*/
INTERN ATTR_SECTION(".text.crt.database.shadow") ATTR_IN(1) struct spwd *
NOTHROW_RPC(LIBCCALL libc_getspnam)(char const *__restrict name)
/*[[[body:libc_getspnam]]]*/
/*AUTO*/{
	(void)name;
	CRT_UNIMPLEMENTEDF("getspnam(%q)", name); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_getspnam]]]*/

/*[[[head:libc_sgetspent,hash:CRC-32=0x9438b9fc]]]*/
INTERN ATTR_SECTION(".text.crt.database.shadow") ATTR_IN(1) struct spwd *
NOTHROW_RPC(LIBCCALL libc_sgetspent)(char const *__restrict string)
/*[[[body:libc_sgetspent]]]*/
/*AUTO*/{
	(void)string;
	CRT_UNIMPLEMENTEDF("sgetspent(%q)", string); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_sgetspent]]]*/

/*[[[head:libc_fgetspent,hash:CRC-32=0x6b3d6456]]]*/
INTERN ATTR_SECTION(".text.crt.database.shadow") ATTR_INOUT(1) struct spwd *
NOTHROW_RPC(LIBCCALL libc_fgetspent)(FILE *__restrict stream)
/*[[[body:libc_fgetspent]]]*/
/*AUTO*/{
	(void)stream;
	CRT_UNIMPLEMENTEDF("fgetspent(%p)", stream); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_fgetspent]]]*/

/*[[[head:libc_putspent,hash:CRC-32=0x4a86c51a]]]*/
INTERN ATTR_SECTION(".text.crt.database.shadow") ATTR_IN(1) ATTR_INOUT(2) int
NOTHROW_RPC(LIBCCALL libc_putspent)(struct spwd const *__restrict p,
                                    FILE *__restrict stream)
/*[[[body:libc_putspent]]]*/
/*AUTO*/{
	(void)p;
	(void)stream;
	CRT_UNIMPLEMENTEDF("putspent(%p, %p)", p, stream); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_putspent]]]*/

/*[[[head:libc_getspent_r,hash:CRC-32=0x9a3e31a4]]]*/
INTERN ATTR_SECTION(".text.crt.database.shadow") ATTR_OUT(1) ATTR_OUT(4) ATTR_OUTS(2, 3) int
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
	CRT_UNIMPLEMENTEDF("getspent_r(%p, %q, %Ix, %p)", result_buf, buffer, buflen, result); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_getspent_r]]]*/

/*[[[head:libc_getspnam_r,hash:CRC-32=0x48cd8769]]]*/
INTERN ATTR_SECTION(".text.crt.database.shadow") ATTR_IN(1) ATTR_OUT(2) ATTR_OUT(5) ATTR_OUTS(3, 4) int
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
	CRT_UNIMPLEMENTEDF("getspnam_r(%q, %p, %q, %Ix, %p)", name, result_buf, buffer, buflen, result); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_getspnam_r]]]*/

/*[[[head:libc_sgetspent_r,hash:CRC-32=0x8ec5e6cf]]]*/
INTERN ATTR_SECTION(".text.crt.database.shadow") ATTR_IN(1) ATTR_OUT(2) ATTR_OUT(5) ATTR_OUTS(3, 4) int
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
	CRT_UNIMPLEMENTEDF("sgetspent_r(%q, %p, %q, %Ix, %p)", string, result_buf, buffer, buflen, result); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_sgetspent_r]]]*/

/*[[[head:libc_fgetspent_r,hash:CRC-32=0xcba37a43]]]*/
INTERN ATTR_SECTION(".text.crt.database.shadow") ATTR_INOUT(1) ATTR_OUT(2) ATTR_OUT(5) ATTR_OUTS(3, 4) int
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
	CRT_UNIMPLEMENTEDF("fgetspent_r(%p, %p, %q, %Ix, %p)", stream, result_buf, buffer, buflen, result); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_fgetspent_r]]]*/

/*[[[head:libc_lckpwdf,hash:CRC-32=0xa0976341]]]*/
INTERN ATTR_SECTION(".text.crt.database.shadow") int
NOTHROW_RPC_KOS(LIBCCALL libc_lckpwdf)(void)
/*[[[body:libc_lckpwdf]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("lckpwdf"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_lckpwdf]]]*/

/*[[[head:libc_ulckpwdf,hash:CRC-32=0x80daa9be]]]*/
INTERN ATTR_SECTION(".text.crt.database.shadow") int
NOTHROW_NCX(LIBCCALL libc_ulckpwdf)(void)
/*[[[body:libc_ulckpwdf]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("ulckpwdf"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_ulckpwdf]]]*/





/*[[[start:exports,hash:CRC-32=0x9488edd3]]]*/
DEFINE_PUBLIC_ALIAS(__setspent, libc_setspent);
DEFINE_PUBLIC_ALIAS(setspent, libc_setspent);
DEFINE_PUBLIC_ALIAS(__endspent, libc_endspent);
DEFINE_PUBLIC_ALIAS(endspent, libc_endspent);
DEFINE_PUBLIC_ALIAS(__getspent, libc_getspent);
DEFINE_PUBLIC_ALIAS(getspent, libc_getspent);
DEFINE_PUBLIC_ALIAS(__getspnam, libc_getspnam);
DEFINE_PUBLIC_ALIAS(getspnam, libc_getspnam);
DEFINE_PUBLIC_ALIAS(sgetspent, libc_sgetspent);
DEFINE_PUBLIC_ALIAS(fgetspent, libc_fgetspent);
DEFINE_PUBLIC_ALIAS(putspent, libc_putspent);
DEFINE_PUBLIC_ALIAS(getspent_r, libc_getspent_r);
DEFINE_PUBLIC_ALIAS(getspnam_r, libc_getspnam_r);
DEFINE_PUBLIC_ALIAS(sgetspent_r, libc_sgetspent_r);
DEFINE_PUBLIC_ALIAS(fgetspent_r, libc_fgetspent_r);
DEFINE_PUBLIC_ALIAS(__lckpwdf, libc_lckpwdf);
DEFINE_PUBLIC_ALIAS(lckpwdf, libc_lckpwdf);
DEFINE_PUBLIC_ALIAS(__ulckpwdf, libc_ulckpwdf);
DEFINE_PUBLIC_ALIAS(ulckpwdf, libc_ulckpwdf);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_SHADOW_C */
