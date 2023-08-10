/* HASH CRC-32:0xd00b0845 */
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
/* (#) Portability: GNU C Library (/sysdeps/unix/sysv/linux/sys/inotify.h) */
/* (#) Portability: diet libc     (/include/sys/inotify.h) */
/* (#) Portability: musl libc     (/include/sys/inotify.h) */
#ifndef _SYS_INOTIFY_H
#define _SYS_INOTIFY_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>

#include <linux/inotify.h>
#include <bits/types.h>   /* fd_t */

#ifdef __USE_GLIBC_BLOAT
#include <stdint.h>
#endif /* __USE_GLIBC_BLOAT */

#ifdef __CC__
__SYSDECL_BEGIN

#define __watchfd_t int
#ifdef __USE_KOS
typedef __watchfd_t watchfd_t;
#endif /* __USE_KOS */

#ifdef __CRT_HAVE_inotify_init
/* >> inotify_init(2) */
__CDECLARE(,__fd_t,__NOTHROW_NCX,inotify_init,(void),())
#elif defined(__CRT_HAVE_inotify_init1)
#include <libc/local/sys.inotify/inotify_init.h>
/* >> inotify_init(2) */
__NAMESPACE_LOCAL_USING_OR_IMPL(inotify_init, __FORCELOCAL __ATTR_ARTIFICIAL __fd_t __NOTHROW_NCX(__LIBCCALL inotify_init)(void) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(inotify_init))(); })
#endif /* ... */
/* >> inotify_init1(2)
 * @param: flags: Set of `IN_NONBLOCK | IN_CLOEXEC | IN_CLOFORK' */
__CDECLARE_OPT(,__fd_t,__NOTHROW_NCX,inotify_init1,(__STDC_INT_AS_UINT_T __flags),(__flags))
#ifdef __CRT_HAVE_inotify_add_watch
/* >> inotify_add_watch(2)
 * @param: mask: Set of `IN_ALL_EVENTS | ...' */
__CDECLARE(__ATTR_FDARG(1) __ATTR_IN(2),__watchfd_t,__NOTHROW_NCX,inotify_add_watch,(__fd_t __notify_fd, char const *__pathname, __UINT32_TYPE__ __mask),(__notify_fd,__pathname,__mask))
#else /* __CRT_HAVE_inotify_add_watch */
#include <asm/os/fcntl.h>
#if defined(__AT_FDCWD) && defined(__CRT_HAVE_inotify_add_watch_at)
#include <libc/local/sys.inotify/inotify_add_watch.h>
/* >> inotify_add_watch(2)
 * @param: mask: Set of `IN_ALL_EVENTS | ...' */
__NAMESPACE_LOCAL_USING_OR_IMPL(inotify_add_watch, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_FDARG(1) __ATTR_IN(2) __watchfd_t __NOTHROW_NCX(__LIBCCALL inotify_add_watch)(__fd_t __notify_fd, char const *__pathname, __UINT32_TYPE__ __mask) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(inotify_add_watch))(__notify_fd, __pathname, __mask); })
#endif /* __AT_FDCWD && __CRT_HAVE_inotify_add_watch_at */
#endif /* !__CRT_HAVE_inotify_add_watch */
/* >> inotify_rm_watch(2)
 * @param: wd: Watch fd (as returned by `inotify_add_watch{_at}') */
__CDECLARE_OPT(__ATTR_FDARG(1),int,__NOTHROW_NCX,inotify_rm_watch,(__fd_t __notify_fd, __watchfd_t __wd),(__notify_fd,__wd))

#ifdef __USE_KOS
/* >> inotify_add_watch_at(2)
 * @param: atflags: Set of `AT_SYMLINK_NOFOLLOW | AT_DOSPATH | AT_EMPTY_PATH'
 * @param: mask:    Set of `IN_ALL_EVENTS | ...' */
__CDECLARE_OPT(__ATTR_FDARG(1) __ATTR_IN(3),__watchfd_t,__NOTHROW_NCX,inotify_add_watch_at,(__fd_t __notify_fd, __fd_t __dirfd, char const *__pathname, __atflag_t __atflags, __UINT32_TYPE__ __mask),(__notify_fd,__dirfd,__pathname,__atflags,__mask))
#endif /* __USE_KOS */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_SYS_INOTIFY_H */
