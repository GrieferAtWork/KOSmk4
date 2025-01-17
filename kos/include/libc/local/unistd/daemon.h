/* HASH CRC-32:0x3ba6c970 */
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
#ifndef __local_daemon_defined
#define __local_daemon_defined
#include <__crt.h>
#include <asm/os/fcntl.h>
#include <features.h>
#include <asm/os/oflags.h>
#if (defined(__CRT_HAVE_fork) || defined(__CRT_HAVE___fork) || defined(__CRT_HAVE___libc_fork)) && (defined(__CRT_HAVE__Exit) || defined(__CRT_HAVE__exit) || defined(__CRT_HAVE_quick_exit) || defined(__CRT_HAVE_exit)) && (defined(__CRT_HAVE_setsid) || defined(__CRT_HAVE___setsid) || defined(__CRT_HAVE___libc_setsid)) && (defined(__CRT_HAVE_chdir) || defined(__CRT_HAVE__chdir) || defined(__CRT_HAVE___chdir) || defined(__CRT_HAVE___libc_chdir) || (defined(__AT_FDCWD) && defined(__CRT_HAVE_fchdirat))) && (defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)))) && (defined(__CRT_HAVE_dup2) || defined(__CRT_HAVE__dup2) || defined(__CRT_HAVE___dup2) || defined(__CRT_HAVE___libc_dup2))
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_chdir_defined
#define __local___localdep_chdir_defined
#ifdef __CRT_HAVE_chdir
__CREDIRECT(__ATTR_IN(1),int,__NOTHROW_RPC,__localdep_chdir,(char const *__path),chdir,(__path))
#elif defined(__CRT_HAVE__chdir)
__CREDIRECT(__ATTR_IN(1),int,__NOTHROW_RPC,__localdep_chdir,(char const *__path),_chdir,(__path))
#elif defined(__CRT_HAVE___chdir)
__CREDIRECT(__ATTR_IN(1),int,__NOTHROW_RPC,__localdep_chdir,(char const *__path),__chdir,(__path))
#elif defined(__CRT_HAVE___libc_chdir)
__CREDIRECT(__ATTR_IN(1),int,__NOTHROW_RPC,__localdep_chdir,(char const *__path),__libc_chdir,(__path))
#elif defined(__AT_FDCWD) && defined(__CRT_HAVE_fchdirat)
__NAMESPACE_LOCAL_END
#include <libc/local/unistd/chdir.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_chdir __LIBC_LOCAL_NAME(chdir)
#else /* ... */
#undef __local___localdep_chdir_defined
#endif /* !... */
#endif /* !__local___localdep_chdir_defined */
#ifndef __local___localdep_close_defined
#define __local___localdep_close_defined
#ifdef __CRT_HAVE_close
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_FDARG(1),int,__NOTHROW_NCX,__localdep_close,(__fd_t __fd),close,(__fd))
#elif defined(__CRT_HAVE__close)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_FDARG(1),int,__NOTHROW_NCX,__localdep_close,(__fd_t __fd),_close,(__fd))
#elif defined(__CRT_HAVE___close)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_FDARG(1),int,__NOTHROW_NCX,__localdep_close,(__fd_t __fd),__close,(__fd))
#elif defined(__CRT_HAVE___libc_close)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_FDARG(1),int,__NOTHROW_NCX,__localdep_close,(__fd_t __fd),__libc_close,(__fd))
#else /* ... */
#undef __local___localdep_close_defined
#endif /* !... */
#endif /* !__local___localdep_close_defined */
#ifndef __local___localdep_daemon_setup_defined
#define __local___localdep_daemon_setup_defined
__NAMESPACE_LOCAL_END
#include <libc/local/unistd/daemon_setup.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_daemon_setup __LIBC_LOCAL_NAME(daemon_setup)
#endif /* !__local___localdep_daemon_setup_defined */
#ifndef __local___localdep_dup2_defined
#define __local___localdep_dup2_defined
#ifdef __CRT_HAVE_dup2
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_FDARG(1),__fd_t,__NOTHROW_NCX,__localdep_dup2,(__fd_t __oldfd, __fd_t __newfd),dup2,(__oldfd,__newfd))
#elif defined(__CRT_HAVE__dup2)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_FDARG(1),__fd_t,__NOTHROW_NCX,__localdep_dup2,(__fd_t __oldfd, __fd_t __newfd),_dup2,(__oldfd,__newfd))
#elif defined(__CRT_HAVE___dup2)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_FDARG(1),__fd_t,__NOTHROW_NCX,__localdep_dup2,(__fd_t __oldfd, __fd_t __newfd),__dup2,(__oldfd,__newfd))
#elif defined(__CRT_HAVE___libc_dup2)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_FDARG(1),__fd_t,__NOTHROW_NCX,__localdep_dup2,(__fd_t __oldfd, __fd_t __newfd),__libc_dup2,(__oldfd,__newfd))
#else /* ... */
#undef __local___localdep_dup2_defined
#endif /* !... */
#endif /* !__local___localdep_dup2_defined */
#ifndef __local___localdep_open_defined
#define __local___localdep_open_defined
#if defined(__CRT_HAVE_open) && (!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CVREDIRECT(__ATTR_WUNUSED __ATTR_IN(1),__fd_t,__NOTHROW_RPC,__localdep_open,(char const *__filename, __oflag_t __oflags),open,(__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE__open) && (!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CVREDIRECT(__ATTR_WUNUSED __ATTR_IN(1),__fd_t,__NOTHROW_RPC,__localdep_open,(char const *__filename, __oflag_t __oflags),_open,(__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE___open) && (!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CVREDIRECT(__ATTR_WUNUSED __ATTR_IN(1),__fd_t,__NOTHROW_RPC,__localdep_open,(char const *__filename, __oflag_t __oflags),__open,(__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE___libc_open) && (!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CVREDIRECT(__ATTR_WUNUSED __ATTR_IN(1),__fd_t,__NOTHROW_RPC,__localdep_open,(char const *__filename, __oflag_t __oflags),__libc_open,(__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE_open64)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CVREDIRECT(__ATTR_WUNUSED __ATTR_IN(1),__fd_t,__NOTHROW_RPC,__localdep_open,(char const *__filename, __oflag_t __oflags),open64,(__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE___open64)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CVREDIRECT(__ATTR_WUNUSED __ATTR_IN(1),__fd_t,__NOTHROW_RPC,__localdep_open,(char const *__filename, __oflag_t __oflags),__open64,(__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)))
__NAMESPACE_LOCAL_END
#include <libc/local/fcntl/open.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_open __LIBC_LOCAL_NAME(open)
#else /* ... */
#undef __local___localdep_open_defined
#endif /* !... */
#endif /* !__local___localdep_open_defined */
__NAMESPACE_LOCAL_END
#include <paths.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(daemon) int
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(daemon))(int __nochdir, int __noclose) {
	int __error = (__NAMESPACE_LOCAL_SYM __localdep_daemon_setup)();
	if __likely(__error == 0) {
		if (!__nochdir)
			(void)(__NAMESPACE_LOCAL_SYM __localdep_chdir)("/");
		if (!__noclose) {
			__fd_t __i, __nul = (__NAMESPACE_LOCAL_SYM __localdep_open)(_PATH_DEVNULL, __O_RDWR | __PRIVATE_O_CLOEXEC | __PRIVATE_O_CLOFORK);
			if __unlikely(__nul < 0)
				return __nul;
			/* NOTE: Glibc does an additional check to ensure that `nul'  really
			 *       is a character-device with the  correct dev_t. We could  do
			 *       that as well, however I'd consider a system where /dev/null
			 *       isn't actually /dev/null to  already be broken... (and  the
			 *       check only adds unnecessary overhead if you ask me) */
			for (__i = 0; __i < 3; ++__i) {
				if (__nul != __i)
					(void)(__NAMESPACE_LOCAL_SYM __localdep_dup2)(__nul, __i);
			}
#if defined(__CRT_HAVE_close) || defined(__CRT_HAVE__close) || defined(__CRT_HAVE___close) || defined(__CRT_HAVE___libc_close)
			if (__nul >= 3)
				(void)(__NAMESPACE_LOCAL_SYM __localdep_close)(__nul);
#endif /* __CRT_HAVE_close || __CRT_HAVE__close || __CRT_HAVE___close || __CRT_HAVE___libc_close */
		}
	}
	return __error;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_daemon_defined
#define __local___localdep_daemon_defined
#define __localdep_daemon __LIBC_LOCAL_NAME(daemon)
#endif /* !__local___localdep_daemon_defined */
#else /* (__CRT_HAVE_fork || __CRT_HAVE___fork || __CRT_HAVE___libc_fork) && (__CRT_HAVE__Exit || __CRT_HAVE__exit || __CRT_HAVE_quick_exit || __CRT_HAVE_exit) && (__CRT_HAVE_setsid || __CRT_HAVE___setsid || __CRT_HAVE___libc_setsid) && (__CRT_HAVE_chdir || __CRT_HAVE__chdir || __CRT_HAVE___chdir || __CRT_HAVE___libc_chdir || (__AT_FDCWD && __CRT_HAVE_fchdirat)) && (__CRT_HAVE_open64 || __CRT_HAVE___open64 || __CRT_HAVE_open || __CRT_HAVE__open || __CRT_HAVE___open || __CRT_HAVE___libc_open || (__AT_FDCWD && (__CRT_HAVE_openat64 || __CRT_HAVE_openat))) && (__CRT_HAVE_dup2 || __CRT_HAVE__dup2 || __CRT_HAVE___dup2 || __CRT_HAVE___libc_dup2) */
#undef __local_daemon_defined
#endif /* (!__CRT_HAVE_fork && !__CRT_HAVE___fork && !__CRT_HAVE___libc_fork) || (!__CRT_HAVE__Exit && !__CRT_HAVE__exit && !__CRT_HAVE_quick_exit && !__CRT_HAVE_exit) || (!__CRT_HAVE_setsid && !__CRT_HAVE___setsid && !__CRT_HAVE___libc_setsid) || (!__CRT_HAVE_chdir && !__CRT_HAVE__chdir && !__CRT_HAVE___chdir && !__CRT_HAVE___libc_chdir && (!__AT_FDCWD || !__CRT_HAVE_fchdirat)) || (!__CRT_HAVE_open64 && !__CRT_HAVE___open64 && !__CRT_HAVE_open && !__CRT_HAVE__open && !__CRT_HAVE___open && !__CRT_HAVE___libc_open && (!__AT_FDCWD || (!__CRT_HAVE_openat64 && !__CRT_HAVE_openat))) || (!__CRT_HAVE_dup2 && !__CRT_HAVE__dup2 && !__CRT_HAVE___dup2 && !__CRT_HAVE___libc_dup2) */
#endif /* !__local_daemon_defined */
