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
#ifndef GUARD_LIBC_USER_KOS_SYS_STAT_C
#define GUARD_LIBC_USER_KOS_SYS_STAT_C 1

#include "../api.h"
/**/

#include <kos/syscalls.h>

#include <fcntl.h>
#include <syscall.h>

#include "kos.sys.stat.h"

DECL_BEGIN

/*[[[head:libc_FUTimens,hash:CRC-32=0xc479388b]]]*/
/* >> futimens(2), futimens64(2) */
INTERN ATTR_SECTION(".text.crt.except.fs.modify_time") ATTR_IN_OPT(2) void
(LIBCCALL libc_FUTimens)(fd_t fd,
                         struct timespec const times[2 /*or:3*/]) THROWS(...)
/*[[[body:libc_FUTimens]]]*/
{
	sys_Xutimensat(fd, NULL, times, 0);
}
/*[[[end:libc_FUTimens]]]*/

/*[[[head:libc_FUTimens64,hash:CRC-32=0xed8b6c19]]]*/
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_FUTimens64, libc_FUTimens);
#else /* MAGIC:alias */
/* >> futimens(2), futimens64(2) */
INTERN ATTR_SECTION(".text.crt.except.fs.modify_time") ATTR_IN_OPT(2) void
(LIBCCALL libc_FUTimens64)(fd_t fd,
                           struct timespec64 const times[2 /*or:3*/]) THROWS(...)
/*[[[body:libc_FUTimens64]]]*/
{
#ifdef SYS_utimensat64
	sys_Xutimensat64(fd, NULL, times, 0);
#elif defined(SYS_utimensat_time64)
	sys_Xutimensat_time64(fd, NULL, times, 0);
#else /* ... */
#error "No way to implement `FUTimens64()'"
#endif /* !... */
}
#endif /* MAGIC:alias */
/*[[[end:libc_FUTimens64]]]*/

/*[[[head:libc_MkNod,hash:CRC-32=0xaa76b56c]]]*/
/* >> mknod(2) */
INTERN ATTR_SECTION(".text.crt.except.fs.modify") ATTR_IN(1) void
(LIBCCALL libc_MkNod)(char const *nodename,
                      mode_t mode,
                      dev_t dev) THROWS(...)
/*[[[body:libc_MkNod]]]*/
{
	sys_Xmknodat(AT_FDCWD,
	             nodename,
	             mode,
	             dev);
}
/*[[[end:libc_MkNod]]]*/

/*[[[head:libc_MkFiFo,hash:CRC-32=0xdd2473a9]]]*/
/* >> mkfifo(2) */
INTERN ATTR_SECTION(".text.crt.except.fs.modify") ATTR_IN(1) void
(LIBCCALL libc_MkFiFo)(char const *fifoname,
                       mode_t mode) THROWS(...)
/*[[[body:libc_MkFiFo]]]*/
{
	return MkNod(fifoname, S_IFIFO | mode, 0);
}
/*[[[end:libc_MkFiFo]]]*/

/*[[[head:libc_MkFiFoAt,hash:CRC-32=0x3c8d48]]]*/
/* >> mkfifoat(2) */
INTERN ATTR_SECTION(".text.crt.except.fs.modify") ATTR_IN(2) void
(LIBCCALL libc_MkFiFoAt)(fd_t dirfd,
                         char const *fifoname,
                         mode_t mode) THROWS(...)
/*[[[body:libc_MkFiFoAt]]]*/
{
	return MkNodAt(dirfd, fifoname, S_IFIFO | mode, 0);
}
/*[[[end:libc_MkFiFoAt]]]*/

/*[[[head:libc_LChMod,hash:CRC-32=0x9e8e8668]]]*/
/* >> lchmod(2) */
INTERN ATTR_SECTION(".text.crt.except.fs.modify") ATTR_IN(1) void
(LIBCCALL libc_LChMod)(char const *filename,
                       mode_t mode) THROWS(...)
/*[[[body:libc_LChMod]]]*/
{
	sys_Xfchmodat(AT_FDCWD, filename, mode, AT_SYMLINK_NOFOLLOW);
}
/*[[[end:libc_LChMod]]]*/

/*[[[skip:libc_ChMod]]]*/
/*[[[skip:libc_FChModAt]]]*/
/*[[[skip:libc_FChMod]]]*/
/*[[[skip:libc_UTimensAt]]]*/
/*[[[skip:libc_UTimensAt64]]]*/
/*[[[skip:libc_MkDir]]]*/
/*[[[skip:libc_FMkDirAt]]]*/
/*[[[skip:libc_FMkNodAt]]]*/
/*[[[skip:libc_MkDirAt]]]*/
/*[[[skip:libc_MkNodAt]]]*/



/*[[[start:exports,hash:CRC-32=0x4774b393]]]*/
DEFINE_PUBLIC_ALIAS(LChMod, libc_LChMod);
DEFINE_PUBLIC_ALIAS(MkFiFo, libc_MkFiFo);
DEFINE_PUBLIC_ALIAS(MkFiFoAt, libc_MkFiFoAt);
DEFINE_PUBLIC_ALIAS(MkNod, libc_MkNod);
DEFINE_PUBLIC_ALIAS(FUTimens, libc_FUTimens);
DEFINE_PUBLIC_ALIAS(FUTimens64, libc_FUTimens64);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_KOS_SYS_STAT_C */
