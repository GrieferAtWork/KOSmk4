/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_USER_SYS_STATFS_C
#define GUARD_LIBC_USER_SYS_STATFS_C 1

#include "../api.h"
/**/

#include <kos/syscalls.h>

#include "sys.statfs.h"

DECL_BEGIN

/*[[[head:libc_statfs,hash:CRC-32=0xe097c931]]]*/
INTERN ATTR_SECTION(".text.crt.fs.statfs.statfs") ATTR_IN(1) ATTR_OUT(2) int
NOTHROW_NCX(LIBCCALL libc_statfs)(char const *file,
                                  struct statfs *buf)
/*[[[body:libc_statfs]]]*/
{
	errno_t result;
	result = sys_statfs(file, (struct __statfs32 *)buf);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_statfs]]]*/

/*[[[head:libc_fstatfs,hash:CRC-32=0xe202da36]]]*/
INTERN ATTR_SECTION(".text.crt.fs.statfs.statfs") ATTR_OUT(2) int
NOTHROW_NCX(LIBCCALL libc_fstatfs)(fd_t filedes,
                                   struct statfs *buf)
/*[[[body:libc_fstatfs]]]*/
{
	errno_t result;
	result = sys_fstatfs(filedes, (struct __statfs32 *)buf);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_fstatfs]]]*/


/*[[[head:libc_statfs64,hash:CRC-32=0xa979a712]]]*/
#ifdef _STATFS_MATCHES_STATFS64
DEFINE_INTERN_ALIAS(libc_statfs64, libc_statfs);
#else /* MAGIC:alias */
INTERN ATTR_SECTION(".text.crt.fs.statfs.statfs") ATTR_IN(1) ATTR_OUT(2) int
NOTHROW_NCX(LIBCCALL libc_statfs64)(const char *file,
                                    struct statfs64 *buf)
/*[[[body:libc_statfs64]]]*/
{
	errno_t result;
	result = sys_statfs64(file, buf);
	return libc_seterrno_syserr(result);
}
#endif /* MAGIC:alias */
/*[[[end:libc_statfs64]]]*/

/*[[[head:libc_fstatfs64,hash:CRC-32=0x3342c231]]]*/
#ifdef _STATFS_MATCHES_STATFS64
DEFINE_INTERN_ALIAS(libc_fstatfs64, libc_fstatfs);
#else /* MAGIC:alias */
INTERN ATTR_SECTION(".text.crt.fs.statfs.statfs") ATTR_OUT(2) int
NOTHROW_NCX(LIBCCALL libc_fstatfs64)(fd_t filedes,
                                     struct statfs64 *buf)
/*[[[body:libc_fstatfs64]]]*/
{
	errno_t result;
	result = sys_fstatfs64(filedes, buf);
	return libc_seterrno_syserr(result);
}
#endif /* MAGIC:alias */
/*[[[end:libc_fstatfs64]]]*/





#undef statfs
#undef statfs64

/*[[[start:exports,hash:CRC-32=0xcbd1e8da]]]*/
DEFINE_PUBLIC_ALIAS(__statfs, libc_statfs);
DEFINE_PUBLIC_ALIAS(__libc_statfs, libc_statfs);
DEFINE_PUBLIC_ALIAS(statfs, libc_statfs);
DEFINE_PUBLIC_ALIAS(__fstatfs, libc_fstatfs);
DEFINE_PUBLIC_ALIAS(__libc_fstatfs, libc_fstatfs);
DEFINE_PUBLIC_ALIAS(fstatfs, libc_fstatfs);
DEFINE_PUBLIC_ALIAS(statfs64, libc_statfs64);
DEFINE_PUBLIC_ALIAS(fstatfs64, libc_fstatfs64);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_SYS_STATFS_C */
