/* HASH CRC-32:0x639003c7 */
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
#ifndef __local_daemonfd_defined
#define __local_daemonfd_defined
#include <__crt.h>
#if (defined(__CRT_HAVE_fork) || defined(__CRT_HAVE___fork) || defined(__CRT_HAVE___libc_fork)) && (defined(__CRT_HAVE__Exit) || defined(__CRT_HAVE__exit) || defined(__CRT_HAVE_quick_exit) || defined(__CRT_HAVE_exit)) && (defined(__CRT_HAVE_setsid) || defined(__CRT_HAVE___setsid) || defined(__CRT_HAVE___libc_setsid)) && (defined(__CRT_HAVE_fchdir) || defined(__CRT_HAVE___fchdir) || defined(__CRT_HAVE___libc_fchdir)) && (defined(__CRT_HAVE_dup2) || defined(__CRT_HAVE__dup2) || defined(__CRT_HAVE___dup2) || defined(__CRT_HAVE___libc_dup2))
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
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
__CREDIRECT(__ATTR_FDARG(1),__fd_t,__NOTHROW_NCX,__localdep_dup2,(__fd_t __oldfd, __fd_t __newfd),dup2,(__oldfd,__newfd))
#elif defined(__CRT_HAVE__dup2)
__CREDIRECT(__ATTR_FDARG(1),__fd_t,__NOTHROW_NCX,__localdep_dup2,(__fd_t __oldfd, __fd_t __newfd),_dup2,(__oldfd,__newfd))
#elif defined(__CRT_HAVE___dup2)
__CREDIRECT(__ATTR_FDARG(1),__fd_t,__NOTHROW_NCX,__localdep_dup2,(__fd_t __oldfd, __fd_t __newfd),__dup2,(__oldfd,__newfd))
#elif defined(__CRT_HAVE___libc_dup2)
__CREDIRECT(__ATTR_FDARG(1),__fd_t,__NOTHROW_NCX,__localdep_dup2,(__fd_t __oldfd, __fd_t __newfd),__libc_dup2,(__oldfd,__newfd))
#else /* ... */
#undef __local___localdep_dup2_defined
#endif /* !... */
#endif /* !__local___localdep_dup2_defined */
#ifndef __local___localdep_fchdir_defined
#define __local___localdep_fchdir_defined
#ifdef __CRT_HAVE_fchdir
__CREDIRECT(__ATTR_FDARG(1),int,__NOTHROW_RPC,__localdep_fchdir,(__fd_t __fd),fchdir,(__fd))
#elif defined(__CRT_HAVE___fchdir)
__CREDIRECT(__ATTR_FDARG(1),int,__NOTHROW_RPC,__localdep_fchdir,(__fd_t __fd),__fchdir,(__fd))
#elif defined(__CRT_HAVE___libc_fchdir)
__CREDIRECT(__ATTR_FDARG(1),int,__NOTHROW_RPC,__localdep_fchdir,(__fd_t __fd),__libc_fchdir,(__fd))
#else /* ... */
#undef __local___localdep_fchdir_defined
#endif /* !... */
#endif /* !__local___localdep_fchdir_defined */
__LOCAL_LIBC(daemonfd) int
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(daemonfd))(__fd_t __chdirfd, __fd_t __nullfd) {
	int __error = (__NAMESPACE_LOCAL_SYM __localdep_daemon_setup)();
	if __likely(__error == 0) {
		if (__chdirfd != -1)
			(void)(__NAMESPACE_LOCAL_SYM __localdep_fchdir)(__chdirfd);
		if (__nullfd != -1) {
			__fd_t __i;
			for (__i = 0; __i < 3; ++__i) {
				if (__nullfd != __i)
					(void)(__NAMESPACE_LOCAL_SYM __localdep_dup2)(__nullfd, __i);
			}
		}
	}
	return __error;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_daemonfd_defined
#define __local___localdep_daemonfd_defined
#define __localdep_daemonfd __LIBC_LOCAL_NAME(daemonfd)
#endif /* !__local___localdep_daemonfd_defined */
#else /* (__CRT_HAVE_fork || __CRT_HAVE___fork || __CRT_HAVE___libc_fork) && (__CRT_HAVE__Exit || __CRT_HAVE__exit || __CRT_HAVE_quick_exit || __CRT_HAVE_exit) && (__CRT_HAVE_setsid || __CRT_HAVE___setsid || __CRT_HAVE___libc_setsid) && (__CRT_HAVE_fchdir || __CRT_HAVE___fchdir || __CRT_HAVE___libc_fchdir) && (__CRT_HAVE_dup2 || __CRT_HAVE__dup2 || __CRT_HAVE___dup2 || __CRT_HAVE___libc_dup2) */
#undef __local_daemonfd_defined
#endif /* (!__CRT_HAVE_fork && !__CRT_HAVE___fork && !__CRT_HAVE___libc_fork) || (!__CRT_HAVE__Exit && !__CRT_HAVE__exit && !__CRT_HAVE_quick_exit && !__CRT_HAVE_exit) || (!__CRT_HAVE_setsid && !__CRT_HAVE___setsid && !__CRT_HAVE___libc_setsid) || (!__CRT_HAVE_fchdir && !__CRT_HAVE___fchdir && !__CRT_HAVE___libc_fchdir) || (!__CRT_HAVE_dup2 && !__CRT_HAVE__dup2 && !__CRT_HAVE___dup2 && !__CRT_HAVE___libc_dup2) */
#endif /* !__local_daemonfd_defined */
