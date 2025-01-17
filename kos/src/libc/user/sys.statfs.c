/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
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

/*[[[head:libc_fstatfs,hash:CRC-32=0x8f2070ba]]]*/
INTERN ATTR_SECTION(".text.crt.fs.statfs.statfs") ATTR_FDARG(1) ATTR_OUT(2) int
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

/*[[[head:libc_fstatfs64,hash:CRC-32=0x1ffab477]]]*/
#ifdef _STATFS_MATCHES_STATFS64
DEFINE_INTERN_ALIAS(libc_fstatfs64, libc_fstatfs);
#else /* MAGIC:alias */
INTERN ATTR_SECTION(".text.crt.fs.statfs.statfs") ATTR_FDARG(1) ATTR_OUT(2) int
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

/*[[[start:exports,hash:CRC-32=0x66db0d94]]]*/
DEFINE_PUBLIC_ALIAS_P(__statfs,libc_statfs,ATTR_IN(1) ATTR_OUT(2),int,NOTHROW_NCX,LIBCCALL,(char const *file, struct statfs *buf),(file,buf));
DEFINE_PUBLIC_ALIAS_P(__libc_statfs,libc_statfs,ATTR_IN(1) ATTR_OUT(2),int,NOTHROW_NCX,LIBCCALL,(char const *file, struct statfs *buf),(file,buf));
DEFINE_PUBLIC_ALIAS_P(statfs,libc_statfs,ATTR_IN(1) ATTR_OUT(2),int,NOTHROW_NCX,LIBCCALL,(char const *file, struct statfs *buf),(file,buf));
DEFINE_PUBLIC_ALIAS_P(__fstatfs,libc_fstatfs,ATTR_FDARG(1) ATTR_OUT(2),int,NOTHROW_NCX,LIBCCALL,(fd_t filedes, struct statfs *buf),(filedes,buf));
DEFINE_PUBLIC_ALIAS_P(__libc_fstatfs,libc_fstatfs,ATTR_FDARG(1) ATTR_OUT(2),int,NOTHROW_NCX,LIBCCALL,(fd_t filedes, struct statfs *buf),(filedes,buf));
DEFINE_PUBLIC_ALIAS_P(fstatfs,libc_fstatfs,ATTR_FDARG(1) ATTR_OUT(2),int,NOTHROW_NCX,LIBCCALL,(fd_t filedes, struct statfs *buf),(filedes,buf));
DEFINE_PUBLIC_ALIAS_P(statfs64,libc_statfs64,ATTR_IN(1) ATTR_OUT(2),int,NOTHROW_NCX,LIBCCALL,(const char *file, struct statfs64 *buf),(file,buf));
DEFINE_PUBLIC_ALIAS_P(fstatfs64,libc_fstatfs64,ATTR_FDARG(1) ATTR_OUT(2),int,NOTHROW_NCX,LIBCCALL,(fd_t filedes, struct statfs64 *buf),(filedes,buf));
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_SYS_STATFS_C */
