/* HASH CRC-32:0x3ffe5b4d */
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
#ifndef __local_inotify_add_watch_defined
#define __local_inotify_add_watch_defined
#include <__crt.h>
#include <asm/os/fcntl.h>
#if defined(__AT_FDCWD) && defined(__CRT_HAVE_inotify_add_watch_at)
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_inotify_add_watch_at_defined
#define __local___localdep_inotify_add_watch_at_defined
__CREDIRECT(__ATTR_ACCESS_RO(3),int,__NOTHROW_NCX,__localdep_inotify_add_watch_at,(__fd_t __notify_fd, __fd_t __dirfd, char const *__pathname, __atflag_t __atflags, __UINT32_TYPE__ __mask),inotify_add_watch_at,(__notify_fd,__dirfd,__pathname,__atflags,__mask))
#endif /* !__local___localdep_inotify_add_watch_at_defined */
__NAMESPACE_LOCAL_END
#include <linux/inotify.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(inotify_add_watch) __ATTR_ACCESS_RO(2) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(inotify_add_watch))(__fd_t __notify_fd, char const *__pathname, __UINT32_TYPE__ __mask) {
	__atflag_t __atflags = 0;
#if defined(IN_DONT_FOLLOW) && defined(__AT_SYMLINK_NOFOLLOW)
	if (__mask & IN_DONT_FOLLOW) {
		__atflags |= __AT_SYMLINK_NOFOLLOW;
		__mask &= ~IN_DONT_FOLLOW;
	}
#endif /* IN_DONT_FOLLOW && __AT_SYMLINK_NOFOLLOW */
	return (__NAMESPACE_LOCAL_SYM __localdep_inotify_add_watch_at)(__notify_fd, __AT_FDCWD, __pathname, __atflags, __mask);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_inotify_add_watch_defined
#define __local___localdep_inotify_add_watch_defined
#define __localdep_inotify_add_watch __LIBC_LOCAL_NAME(inotify_add_watch)
#endif /* !__local___localdep_inotify_add_watch_defined */
#else /* __AT_FDCWD && __CRT_HAVE_inotify_add_watch_at */
#undef __local_inotify_add_watch_defined
#endif /* !__AT_FDCWD || !__CRT_HAVE_inotify_add_watch_at */
#endif /* !__local_inotify_add_watch_defined */
