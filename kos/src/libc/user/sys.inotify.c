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
#ifndef GUARD_LIBC_USER_SYS_INOTIFY_C
#define GUARD_LIBC_USER_SYS_INOTIFY_C 1

#include "../api.h"
/**/

#include <kos/syscalls.h>

#include <syscall.h>

#include "sys.inotify.h"

#ifndef SYS_inotify_init
#define sys_inotify_init() sys_inotify_init1(0)
#endif /* !SYS_inotify_init */

DECL_BEGIN

/*[[[head:libc_inotify_init,hash:CRC-32=0xfd63ef52]]]*/
/* >> inotify_init(2) */
INTERN ATTR_SECTION(".text.crt.unsorted") fd_t
NOTHROW_NCX(LIBCCALL libc_inotify_init)(void)
/*[[[body:libc_inotify_init]]]*/
{
	fd_t result = sys_inotify_init();
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_inotify_init]]]*/

/*[[[head:libc_inotify_init1,hash:CRC-32=0x227ac8a3]]]*/
/* >> inotify_init1(2)
 * @param: flags: Set of `IN_NONBLOCK | IN_CLOEXEC | IN_CLOFORK' */
INTERN ATTR_SECTION(".text.crt.unsorted") fd_t
NOTHROW_NCX(LIBCCALL libc_inotify_init1)(__STDC_INT_AS_UINT_T flags)
/*[[[body:libc_inotify_init1]]]*/
{
	fd_t result = sys_inotify_init1((syscall_ulong_t)(unsigned int)flags);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_inotify_init1]]]*/

/*[[[head:libd_inotify_add_watch,hash:CRC-32=0x12216e3b]]]*/
/* >> inotify_add_watch(2)
 * @param: mask: Set of `IN_ALL_EVENTS | ...' */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.unsorted") ATTR_FDARG(1) ATTR_IN(2) __watchfd_t
NOTHROW_NCX(LIBDCALL libd_inotify_add_watch)(fd_t notify_fd,
                                             char const *pathname,
                                             uint32_t mask)
/*[[[body:libd_inotify_add_watch]]]*/
{
	atflag_t atflags = 0;
	if (mask & IN_DONT_FOLLOW) {
		atflags |= AT_SYMLINK_NOFOLLOW;
		mask &= ~IN_DONT_FOLLOW;
	}
	return libd_inotify_add_watch_at(notify_fd, AT_FDCWD, pathname, atflags, mask);
}
/*[[[end:libd_inotify_add_watch]]]*/

/*[[[head:libc_inotify_add_watch,hash:CRC-32=0x947b04a]]]*/
/* >> inotify_add_watch(2)
 * @param: mask: Set of `IN_ALL_EVENTS | ...' */
INTERN ATTR_SECTION(".text.crt.unsorted") ATTR_FDARG(1) ATTR_IN(2) __watchfd_t
NOTHROW_NCX(LIBCCALL libc_inotify_add_watch)(fd_t notify_fd,
                                             char const *pathname,
                                             uint32_t mask)
/*[[[body:libc_inotify_add_watch]]]*/
{
#ifdef SYS_inotify_add_watch
	watchfd_t result;
	result = sys_inotify_add_watch(notify_fd, pathname, mask);
	return libc_seterrno_syserr(result);
#else /* SYS_inotify_add_watch */
	atflag_t atflags = 0;
	if (mask & IN_DONT_FOLLOW) {
		atflags |= __AT_SYMLINK_NOFOLLOW;
		mask &= ~IN_DONT_FOLLOW;
	}
	return libc_inotify_add_watch_at(notify_fd, __AT_FDCWD, pathname, atflags, mask);
#endif /* !SYS_inotify_add_watch */
}
/*[[[end:libc_inotify_add_watch]]]*/

/*[[[head:libc_inotify_rm_watch,hash:CRC-32=0xf66b1000]]]*/
/* >> inotify_rm_watch(2)
 * @param: wd: Watch fd (as returned by `inotify_add_watch{_at}') */
INTERN ATTR_SECTION(".text.crt.unsorted") ATTR_FDARG(1) int
NOTHROW_NCX(LIBCCALL libc_inotify_rm_watch)(fd_t notify_fd,
                                            __watchfd_t wd)
/*[[[body:libc_inotify_rm_watch]]]*/
{
	errno_t result;
	result = sys_inotify_rm_watch(notify_fd, wd);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_inotify_rm_watch]]]*/

/*[[[head:libd_inotify_add_watch_at,hash:CRC-32=0x25ccab5a]]]*/
/* >> inotify_add_watch_at(2)
 * @param: atflags: Set of `AT_SYMLINK_NOFOLLOW | AT_DOSPATH | AT_EMPTY_PATH'
 * @param: mask:    Set of `IN_ALL_EVENTS | ...' */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.unsorted") ATTR_FDARG(1) ATTR_IN(3) __watchfd_t
NOTHROW_NCX(LIBDCALL libd_inotify_add_watch_at)(fd_t notify_fd,
                                                fd_t dirfd,
                                                char const *pathname,
                                                atflag_t atflags,
                                                uint32_t mask)
/*[[[body:libd_inotify_add_watch_at]]]*/
{
	return libc_inotify_add_watch_at(notify_fd, dirfd, pathname,
	                                 atflags | libd_AT_DOSPATH,
	                                 mask);
}
/*[[[end:libd_inotify_add_watch_at]]]*/

/*[[[head:libc_inotify_add_watch_at,hash:CRC-32=0x741ad018]]]*/
/* >> inotify_add_watch_at(2)
 * @param: atflags: Set of `AT_SYMLINK_NOFOLLOW | AT_DOSPATH | AT_EMPTY_PATH'
 * @param: mask:    Set of `IN_ALL_EVENTS | ...' */
INTERN ATTR_SECTION(".text.crt.unsorted") ATTR_FDARG(1) ATTR_IN(3) __watchfd_t
NOTHROW_NCX(LIBCCALL libc_inotify_add_watch_at)(fd_t notify_fd,
                                                fd_t dirfd,
                                                char const *pathname,
                                                atflag_t atflags,
                                                uint32_t mask)
/*[[[body:libc_inotify_add_watch_at]]]*/
{
	watchfd_t result;
	result = sys_inotify_add_watch_at(notify_fd, dirfd, pathname, atflags, mask);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_inotify_add_watch_at]]]*/

/*[[[start:exports,hash:CRC-32=0xd0292b02]]]*/
DEFINE_PUBLIC_ALIAS_P(inotify_init,libc_inotify_init,,fd_t,NOTHROW_NCX,LIBCCALL,(void),());
DEFINE_PUBLIC_ALIAS_P(inotify_init1,libc_inotify_init1,,fd_t,NOTHROW_NCX,LIBCCALL,(__STDC_INT_AS_UINT_T flags),(flags));
DEFINE_PUBLIC_ALIAS_P(DOS$inotify_add_watch,libd_inotify_add_watch,ATTR_FDARG(1) ATTR_IN(2),__watchfd_t,NOTHROW_NCX,LIBDCALL,(fd_t notify_fd, char const *pathname, uint32_t mask),(notify_fd,pathname,mask));
DEFINE_PUBLIC_ALIAS_P(inotify_add_watch,libc_inotify_add_watch,ATTR_FDARG(1) ATTR_IN(2),__watchfd_t,NOTHROW_NCX,LIBCCALL,(fd_t notify_fd, char const *pathname, uint32_t mask),(notify_fd,pathname,mask));
DEFINE_PUBLIC_ALIAS_P(inotify_rm_watch,libc_inotify_rm_watch,ATTR_FDARG(1),int,NOTHROW_NCX,LIBCCALL,(fd_t notify_fd, __watchfd_t wd),(notify_fd,wd));
DEFINE_PUBLIC_ALIAS_P(DOS$inotify_add_watch_at,libd_inotify_add_watch_at,ATTR_FDARG(1) ATTR_IN(3),__watchfd_t,NOTHROW_NCX,LIBDCALL,(fd_t notify_fd, fd_t dirfd, char const *pathname, atflag_t atflags, uint32_t mask),(notify_fd,dirfd,pathname,atflags,mask));
DEFINE_PUBLIC_ALIAS_P(inotify_add_watch_at,libc_inotify_add_watch_at,ATTR_FDARG(1) ATTR_IN(3),__watchfd_t,NOTHROW_NCX,LIBCCALL,(fd_t notify_fd, fd_t dirfd, char const *pathname, atflag_t atflags, uint32_t mask),(notify_fd,dirfd,pathname,atflags,mask));
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_SYS_INOTIFY_C */
