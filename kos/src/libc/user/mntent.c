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
#ifndef GUARD_LIBC_USER_MNTENT_C
#define GUARD_LIBC_USER_MNTENT_C 1

#include "../api.h"
#include "mntent.h"

DECL_BEGIN





/*[[[start:implementation]]]*/

/*[[[head:setmntent,hash:CRC-32=0x8be63af0]]]*/
/* Prepare to begin reading and/or writing mount table
 * entries from the beginning of FILE.  MODE is as for `fopen' */
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.database.mntent.setmntent") FILE *
NOTHROW_RPC(LIBCCALL libc_setmntent)(char const *file,
                                     char const *mode)
/*[[[body:setmntent]]]*/
{
	(void)file;
	(void)mode;
	CRT_UNIMPLEMENTED("setmntent"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:setmntent]]]*/

/*[[[head:getmntent,hash:CRC-32=0x3e073f87]]]*/
/* Read one mount table entry from STREAM.  Returns a pointer to storage
 * reused on the next call, or null for EOF or error (use feof/ferror to check) */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.database.mntent.getmntent") struct mntent *
NOTHROW_RPC(LIBCCALL libc_getmntent)(FILE *stream)
/*[[[body:getmntent]]]*/
{
	(void)stream;
	CRT_UNIMPLEMENTED("getmntent"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:getmntent]]]*/

/*[[[head:getmntent_r,hash:CRC-32=0x955948c3]]]*/
/* Reentrant version of the above function */
INTERN NONNULL((1, 2, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.database.mntent.getmntent_r") struct mntent *
NOTHROW_RPC(LIBCCALL libc_getmntent_r)(FILE *__restrict stream,
                                       struct mntent *__restrict result,
                                       char *__restrict buffer,
                                       __STDC_INT_AS_SIZE_T bufsize)
/*[[[body:getmntent_r]]]*/
{
	(void)stream;
	(void)result;
	(void)buffer;
	(void)bufsize;
	CRT_UNIMPLEMENTED("getmntent_r"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:getmntent_r]]]*/

/*[[[head:addmntent,hash:CRC-32=0x303ff22e]]]*/
/* Write the mount table entry described by MNT to STREAM.
 * Return zero on success, nonzero on failure */
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.database.mntent.addmntent") int
NOTHROW_RPC(LIBCCALL libc_addmntent)(FILE *__restrict stream,
                                     struct mntent const *__restrict mnt)
/*[[[body:addmntent]]]*/
{
	(void)stream;
	(void)mnt;
	CRT_UNIMPLEMENTED("addmntent"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:addmntent]]]*/

/*[[[head:endmntent,hash:CRC-32=0x670faef7]]]*/
/* Close a stream opened with `setmntent' */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.database.mntent.endmntent") int
NOTHROW_RPC_NOKOS(LIBCCALL libc_endmntent)(FILE *stream)
/*[[[body:endmntent]]]*/
{
	(void)stream;
	CRT_UNIMPLEMENTED("endmntent"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:endmntent]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:CRC-32=0x7f9d24d1]]]*/
DEFINE_PUBLIC_WEAK_ALIAS(setmntent, libc_setmntent);
DEFINE_PUBLIC_WEAK_ALIAS(__setmntent, libc_setmntent);
DEFINE_PUBLIC_WEAK_ALIAS(getmntent, libc_getmntent);
DEFINE_PUBLIC_WEAK_ALIAS(getmntent_r, libc_getmntent_r);
DEFINE_PUBLIC_WEAK_ALIAS(__getmntent_r, libc_getmntent_r);
DEFINE_PUBLIC_WEAK_ALIAS(addmntent, libc_addmntent);
DEFINE_PUBLIC_WEAK_ALIAS(endmntent, libc_endmntent);
DEFINE_PUBLIC_WEAK_ALIAS(__endmntent, libc_endmntent);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_MNTENT_C */
