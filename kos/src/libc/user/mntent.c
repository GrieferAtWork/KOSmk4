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
#ifndef GUARD_LIBC_USER_MNTENT_C
#define GUARD_LIBC_USER_MNTENT_C 1

#include "../api.h"
#include "mntent.h"

DECL_BEGIN





/*[[[start:implementation]]]*/

/*[[[head:libc_setmntent,hash:CRC-32=0x3147db9f]]]*/
/* >> setmntent(3) */
INTERN ATTR_SECTION(".text.crt.database.mntent") NONNULL((1, 2)) FILE *
NOTHROW_RPC(LIBCCALL libc_setmntent)(char const *file,
                                     char const *mode)
/*[[[body:libc_setmntent]]]*/
/*AUTO*/{
	(void)file;
	(void)mode;
	CRT_UNIMPLEMENTEDF("setmntent(%q, %q)", file, mode); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_setmntent]]]*/

/*[[[head:libc_getmntent,hash:CRC-32=0x22c04d99]]]*/
/* >> getmntent(3), getmntent_r(3) */
INTERN ATTR_SECTION(".text.crt.database.mntent") NONNULL((1)) struct mntent *
NOTHROW_RPC(LIBCCALL libc_getmntent)(FILE *stream)
/*[[[body:libc_getmntent]]]*/
/*AUTO*/{
	(void)stream;
	CRT_UNIMPLEMENTEDF("getmntent(%p)", stream); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_getmntent]]]*/

/*[[[head:libc_getmntent_r,hash:CRC-32=0x45a07216]]]*/
/* >> getmntent(3), getmntent_r(3) */
INTERN ATTR_SECTION(".text.crt.database.mntent") NONNULL((1, 2, 3)) struct mntent *
NOTHROW_RPC(LIBCCALL libc_getmntent_r)(FILE *__restrict stream,
                                       struct mntent *__restrict result,
                                       char *__restrict buffer,
                                       __STDC_INT_AS_SIZE_T bufsize)
/*[[[body:libc_getmntent_r]]]*/
/*AUTO*/{
	(void)stream;
	(void)result;
	(void)buffer;
	(void)bufsize;
	CRT_UNIMPLEMENTEDF("getmntent_r(%p, %p, %q, %x)", stream, result, buffer, bufsize); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_getmntent_r]]]*/

/*[[[head:libc_addmntent,hash:CRC-32=0x66abfa93]]]*/
/* >> addmntent(3) */
INTERN ATTR_SECTION(".text.crt.database.mntent") NONNULL((1, 2)) int
NOTHROW_RPC(LIBCCALL libc_addmntent)(FILE *__restrict stream,
                                     struct mntent const *__restrict mnt)
/*[[[body:libc_addmntent]]]*/
/*AUTO*/{
	(void)stream;
	(void)mnt;
	CRT_UNIMPLEMENTEDF("addmntent(%p, %p)", stream, mnt); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_addmntent]]]*/

/*[[[head:libc_endmntent,hash:CRC-32=0x16157864]]]*/
/* >> endmntent(3) */
INTERN ATTR_SECTION(".text.crt.database.mntent") NONNULL((1)) int
NOTHROW_RPC_NOKOS(LIBCCALL libc_endmntent)(FILE *stream)
/*[[[body:libc_endmntent]]]*/
/*AUTO*/{
	(void)stream;
	CRT_UNIMPLEMENTEDF("endmntent(%p)", stream); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_endmntent]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:CRC-32=0x1975f556]]]*/
DEFINE_PUBLIC_ALIAS(__setmntent, libc_setmntent);
DEFINE_PUBLIC_ALIAS(setmntent, libc_setmntent);
DEFINE_PUBLIC_ALIAS(getmntent, libc_getmntent);
DEFINE_PUBLIC_ALIAS(__getmntent_r, libc_getmntent_r);
DEFINE_PUBLIC_ALIAS(getmntent_r, libc_getmntent_r);
DEFINE_PUBLIC_ALIAS(addmntent, libc_addmntent);
DEFINE_PUBLIC_ALIAS(__endmntent, libc_endmntent);
DEFINE_PUBLIC_ALIAS(endmntent, libc_endmntent);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_MNTENT_C */
