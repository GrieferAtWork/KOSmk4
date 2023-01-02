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

/*[[[head:libc_FUtimens,hash:CRC-32=0xbe2235c0]]]*/
/* >> futimens(2), futimens64(2) */
INTERN ATTR_SECTION(".text.crt.except.fs.modify_time") ATTR_IN_OPT(2) void
(LIBCCALL libc_FUtimens)(fd_t fd,
                         struct timespec const times[2 /*or:3*/]) THROWS(...)
/*[[[body:libc_FUtimens]]]*/
{
	sys_Xutimensat(fd, NULL, times, 0);
}
/*[[[end:libc_FUtimens]]]*/

/*[[[head:libc_FUtimens64,hash:CRC-32=0x6b11111e]]]*/
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_FUtimens64, libc_FUtimens);
#else /* MAGIC:alias */
/* >> futimens(2), futimens64(2) */
INTERN ATTR_SECTION(".text.crt.except.fs.modify_time") ATTR_IN_OPT(2) void
(LIBCCALL libc_FUtimens64)(fd_t fd,
                           struct timespec64 const times[2 /*or:3*/]) THROWS(...)
/*[[[body:libc_FUtimens64]]]*/
{
#ifdef SYS_utimensat64
	sys_Xutimensat64(fd, NULL, times, 0);
#elif defined(SYS_utimensat_time64)
	sys_Xutimensat_time64(fd, NULL, times, 0);
#else /* ... */
#error "No way to implement `FUtimens64()'"
#endif /* !... */
}
#endif /* MAGIC:alias */
/*[[[end:libc_FUtimens64]]]*/

/*[[[head:libc_Mknod,hash:CRC-32=0x46adf61]]]*/
/* >> mknod(2) */
INTERN ATTR_SECTION(".text.crt.except.fs.modify") ATTR_IN(1) void
(LIBCCALL libc_Mknod)(char const *nodename,
                      mode_t mode,
                      dev_t dev) THROWS(...)
/*[[[body:libc_Mknod]]]*/
{
	sys_Xmknodat(AT_FDCWD,
	             nodename,
	             mode,
	             dev);
}
/*[[[end:libc_Mknod]]]*/

/*[[[head:libc_Mkfifo,hash:CRC-32=0x91e44183]]]*/
/* >> mkfifo(2) */
INTERN ATTR_SECTION(".text.crt.except.fs.modify") ATTR_IN(1) void
(LIBCCALL libc_Mkfifo)(char const *fifoname,
                       mode_t mode) THROWS(...)
/*[[[body:libc_Mkfifo]]]*/
{
	return Mknod(fifoname, S_IFIFO | mode, 0);
}
/*[[[end:libc_Mkfifo]]]*/

/*[[[head:libc_MkfifoAt,hash:CRC-32=0xfcf64f8]]]*/
/* >> mkfifoat(2) */
INTERN ATTR_SECTION(".text.crt.except.fs.modify") ATTR_IN(2) void
(LIBCCALL libc_MkfifoAt)(fd_t dirfd,
                         char const *fifoname,
                         mode_t mode) THROWS(...)
/*[[[body:libc_MkfifoAt]]]*/
{
	return MknodAt(dirfd, fifoname, S_IFIFO | mode, 0);
}
/*[[[end:libc_MkfifoAt]]]*/

/*[[[head:libc_LChmod,hash:CRC-32=0xcfd51b1b]]]*/
/* >> lchmod(2) */
INTERN ATTR_SECTION(".text.crt.except.fs.modify") ATTR_IN(1) void
(LIBCCALL libc_LChmod)(char const *filename,
                       mode_t mode) THROWS(...)
/*[[[body:libc_LChmod]]]*/
{
	sys_Xfchmodat(AT_FDCWD, filename, mode, AT_SYMLINK_NOFOLLOW);
}
/*[[[end:libc_LChmod]]]*/

/*[[[skip:libc_Chmod]]]*/
/*[[[skip:libc_FChmodAt]]]*/
/*[[[skip:libc_FChmod]]]*/
/*[[[skip:libc_UTimensAt]]]*/
/*[[[skip:libc_UTimensAt64]]]*/
/*[[[skip:libc_Mkdir]]]*/
/*[[[skip:libc_FMkdirAt]]]*/
/*[[[skip:libc_FMknodAt]]]*/
/*[[[skip:libc_MkdirAt]]]*/
/*[[[skip:libc_MknodAt]]]*/



/*[[[start:exports,hash:CRC-32=0x42790cdf]]]*/
DEFINE_PUBLIC_ALIAS(LChmod, libc_LChmod);
DEFINE_PUBLIC_ALIAS(Mkfifo, libc_Mkfifo);
DEFINE_PUBLIC_ALIAS(MkfifoAt, libc_MkfifoAt);
DEFINE_PUBLIC_ALIAS(Mknod, libc_Mknod);
DEFINE_PUBLIC_ALIAS(FUtimens, libc_FUtimens);
DEFINE_PUBLIC_ALIAS(FUtimens64, libc_FUtimens64);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_KOS_SYS_STAT_C */
