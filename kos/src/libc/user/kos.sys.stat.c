/* Copyright (c) 2019 Griefer@Work                                            *
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
#ifndef GUARD_LIBC_USER_KOS_SYS_STAT_C
#define GUARD_LIBC_USER_KOS_SYS_STAT_C 1

#include "../api.h"
#include "kos.sys.stat.h"
#include <fcntl.h>
#include <kos/syscalls.h>

DECL_BEGIN





/*[[[start:implementation]]]*/

/*[[[head:FUtimens,hash:0x6a4c81ab]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.except.fs.modify_time.FUtimens") void
(LIBCCALL libc_FUtimens)(fd_t fd,
                         struct timespec const times[2/*or:3*/])
		__THROWS(...)
/*[[[body:FUtimens]]]*/
{
	sys_Xutimensat(fd, NULL, times, 0);
}
/*[[[end:FUtimens]]]*/

/*[[[head:FUtimens64,hash:0x800e85b7]]]*/
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_FUtimens64, libc_FUtimens);
#else
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.except.fs.modify_time.FUtimens64") void
(LIBCCALL libc_FUtimens64)(fd_t fd,
                           struct timespec64 const times[2/*or:3*/])
		__THROWS(...)
/*[[[body:FUtimens64]]]*/
{
	sys_Xutimensat64(fd, NULL, times, 0);
}
#endif /* MAGIC:alias */
/*[[[end:FUtimens64]]]*/

/*[[[head:Mknod,hash:0xfdca60fb]]]*/
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.except.fs.modify.Mknod") void
(LIBCCALL libc_Mknod)(char const *nodename,
                      mode_t mode,
                      dev_t dev)
		__THROWS(...)
/*[[[body:Mknod]]]*/
{
	sys_Xmknodat(AT_FDCWD,
	             nodename,
	             mode,
	             dev);
}
/*[[[end:Mknod]]]*/

/*[[[head:Mkfifo,hash:0x6f153bc3]]]*/
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.except.fs.modify.Mkfifo") void
(LIBCCALL libc_Mkfifo)(char const *fifoname,
                       mode_t mode)
		__THROWS(...)
/*[[[body:Mkfifo]]]*/
{
	return Mknod(fifoname, S_IFIFO | mode, 0);
}
/*[[[end:Mkfifo]]]*/

/*[[[head:MkfifoAt,hash:0xb4dd04b7]]]*/
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.except.fs.modify.MkfifoAt") void
(LIBCCALL libc_MkfifoAt)(fd_t dirfd,
                         char const *fifoname,
                         mode_t mode)
		__THROWS(...)
/*[[[body:MkfifoAt]]]*/
{
	return MknodAt(dirfd, fifoname, S_IFIFO | mode, 0);
}
/*[[[end:MkfifoAt]]]*/

/*[[[skip:Stat]]]*/
/*[[[skip:FStat]]]*/
/*[[[skip:LStat]]]*/
/*[[[skip:FStatAt]]]*/
/*[[[skip:Stat64]]]*/
/*[[[skip:FStat64]]]*/
/*[[[skip:LStat64]]]*/
/*[[[skip:FStatAt64]]]*/
/*[[[skip:Chmod]]]*/
/*[[[skip:LChmod]]]*/
/*[[[skip:FChmodAt]]]*/
/*[[[skip:FChmod]]]*/
/*[[[skip:UTimensAt]]]*/
/*[[[skip:UTimensAt64]]]*/
/*[[[skip:Mkdir]]]*/
/*[[[skip:FMkdirAt]]]*/
/*[[[skip:FMknodAt]]]*/
/*[[[skip:MkdirAt]]]*/
/*[[[skip:MknodAt]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:0x6a2d6f9a]]]*/
DEFINE_PUBLIC_WEAK_ALIAS(Mkfifo, libc_Mkfifo);
DEFINE_PUBLIC_WEAK_ALIAS(MkfifoAt, libc_MkfifoAt);
DEFINE_PUBLIC_WEAK_ALIAS(Mknod, libc_Mknod);
DEFINE_PUBLIC_WEAK_ALIAS(FUtimens, libc_FUtimens);
DEFINE_PUBLIC_WEAK_ALIAS(FUtimens64, libc_FUtimens64);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_KOS_SYS_STAT_C */
