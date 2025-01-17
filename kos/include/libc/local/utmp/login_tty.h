/* HASH CRC-32:0xd3aa80a0 */
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
#ifndef __local_login_tty_defined
#define __local_login_tty_defined
#include <__crt.h>
#include <asm/os/tty.h>
#include <features.h>
#include <bits/types.h>
#if defined(__TIOCSCTTY) && (defined(__CRT_HAVE_ioctl) || defined(__CRT_HAVE___ioctl) || defined(__CRT_HAVE___libc_ioctl) || defined(__CRT_HAVE___ioctl_time64)) && (defined(__CRT_HAVE_setsid) || defined(__CRT_HAVE___setsid) || defined(__CRT_HAVE___libc_setsid)) && (defined(__CRT_HAVE_dup2) || defined(__CRT_HAVE__dup2) || defined(__CRT_HAVE___dup2) || defined(__CRT_HAVE___libc_dup2)) && (defined(__CRT_HAVE_close) || defined(__CRT_HAVE__close) || defined(__CRT_HAVE___close) || defined(__CRT_HAVE___libc_close))
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_close_defined
#define __local___localdep_close_defined
#ifdef __CRT_HAVE_close
__CREDIRECT(__ATTR_FDARG(1),int,__NOTHROW_NCX,__localdep_close,(__fd_t __fd),close,(__fd))
#elif defined(__CRT_HAVE__close)
__CREDIRECT(__ATTR_FDARG(1),int,__NOTHROW_NCX,__localdep_close,(__fd_t __fd),_close,(__fd))
#elif defined(__CRT_HAVE___close)
__CREDIRECT(__ATTR_FDARG(1),int,__NOTHROW_NCX,__localdep_close,(__fd_t __fd),__close,(__fd))
#elif defined(__CRT_HAVE___libc_close)
__CREDIRECT(__ATTR_FDARG(1),int,__NOTHROW_NCX,__localdep_close,(__fd_t __fd),__libc_close,(__fd))
#else /* ... */
#undef __local___localdep_close_defined
#endif /* !... */
#endif /* !__local___localdep_close_defined */
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
#ifndef __local___localdep_ioctl_defined
#define __local___localdep_ioctl_defined
#if defined(__CRT_HAVE_ioctl) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
__CVREDIRECT(__ATTR_FDARG(1),__STDC_INT_AS_SSIZE_T,__NOTHROW_RPC,__localdep_ioctl,(__fd_t __fd, __ioctl_t __request),ioctl,(__fd,__request),__request,1,(void *))
#elif defined(__CRT_HAVE___ioctl) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
__CVREDIRECT(__ATTR_FDARG(1),__STDC_INT_AS_SSIZE_T,__NOTHROW_RPC,__localdep_ioctl,(__fd_t __fd, __ioctl_t __request),__ioctl,(__fd,__request),__request,1,(void *))
#elif defined(__CRT_HAVE___libc_ioctl) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
__CVREDIRECT(__ATTR_FDARG(1),__STDC_INT_AS_SSIZE_T,__NOTHROW_RPC,__localdep_ioctl,(__fd_t __fd, __ioctl_t __request),__libc_ioctl,(__fd,__request),__request,1,(void *))
#elif defined(__CRT_HAVE___ioctl_time64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
__CVREDIRECT(__ATTR_FDARG(1),__STDC_INT_AS_SSIZE_T,__NOTHROW_RPC,__localdep_ioctl,(__fd_t __fd, __ioctl_t __request),__ioctl_time64,(__fd,__request),__request,1,(void *))
#elif defined(__CRT_HAVE_ioctl)
__CVREDIRECT(__ATTR_FDARG(1),__STDC_INT_AS_SSIZE_T,__NOTHROW_RPC,__localdep_ioctl,(__fd_t __fd, __ioctl_t __request),ioctl,(__fd,__request),__request,1,(void *))
#elif defined(__CRT_HAVE___ioctl)
__CVREDIRECT(__ATTR_FDARG(1),__STDC_INT_AS_SSIZE_T,__NOTHROW_RPC,__localdep_ioctl,(__fd_t __fd, __ioctl_t __request),__ioctl,(__fd,__request),__request,1,(void *))
#elif defined(__CRT_HAVE___libc_ioctl)
__CVREDIRECT(__ATTR_FDARG(1),__STDC_INT_AS_SSIZE_T,__NOTHROW_RPC,__localdep_ioctl,(__fd_t __fd, __ioctl_t __request),__libc_ioctl,(__fd,__request),__request,1,(void *))
#elif defined(__CRT_HAVE___ioctl_time64)
__CVREDIRECT(__ATTR_FDARG(1),__STDC_INT_AS_SSIZE_T,__NOTHROW_RPC,__localdep_ioctl,(__fd_t __fd, __ioctl_t __request),__ioctl_time64,(__fd,__request),__request,1,(void *))
#else /* ... */
#undef __local___localdep_ioctl_defined
#endif /* !... */
#endif /* !__local___localdep_ioctl_defined */
#ifndef __local___localdep_setsid_defined
#define __local___localdep_setsid_defined
#ifdef __CRT_HAVE_setsid
__CREDIRECT(,__pid_t,__NOTHROW_NCX,__localdep_setsid,(void),setsid,())
#elif defined(__CRT_HAVE___setsid)
__CREDIRECT(,__pid_t,__NOTHROW_NCX,__localdep_setsid,(void),__setsid,())
#elif defined(__CRT_HAVE___libc_setsid)
__CREDIRECT(,__pid_t,__NOTHROW_NCX,__localdep_setsid,(void),__libc_setsid,())
#else /* ... */
#undef __local___localdep_setsid_defined
#endif /* !... */
#endif /* !__local___localdep_setsid_defined */
__NAMESPACE_LOCAL_END
#include <asm/os/stdio.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(login_tty) __ATTR_FDARG(1) int
__NOTHROW_RPC_KOS(__LIBCCALL __LIBC_LOCAL_NAME(login_tty))(__fd_t __fd) {
	if __unlikely((__NAMESPACE_LOCAL_SYM __localdep_setsid)() < 0)
		goto __err;
	if __unlikely((__NAMESPACE_LOCAL_SYM __localdep_ioctl)(__fd, __TIOCSCTTY, 1) < 0)
		goto __err;
#if __STDIN_FILENO <= 2 && __STDOUT_FILENO <= 2 && __STDERR_FILENO <= 2
	{
		__fd_t __i;
		for (__i = 0; __i <= 2; ++__i) {
			if __likely(__fd != __i) {
				if __unlikely((__NAMESPACE_LOCAL_SYM __localdep_dup2)(__fd, __i))
					goto __err;
			}
		}
	}
	if __likely(__fd >= 3)
		(__NAMESPACE_LOCAL_SYM __localdep_close)(__fd);
#else /* __STDIN_FILENO <= 2 && __STDOUT_FILENO <= 2 && __STDERR_FILENO <= 2 */
	if (__likely(__fd != __STDIN_FILENO) && __unlikely((__NAMESPACE_LOCAL_SYM __localdep_dup2)(__fd, __STDIN_FILENO)))
		goto __err;
	if (__likely(__fd != __STDOUT_FILENO) && __unlikely((__NAMESPACE_LOCAL_SYM __localdep_dup2)(__fd, __STDOUT_FILENO)))
		goto __err;
	if (__likely(__fd != __STDERR_FILENO) && __unlikely((__NAMESPACE_LOCAL_SYM __localdep_dup2)(__fd, __STDERR_FILENO)))
		goto __err;
	if __likely(__fd != __STDIN_FILENO && __fd != __STDOUT_FILENO && __fd != __STDERR_FILENO)
		(__NAMESPACE_LOCAL_SYM __localdep_close)(__fd);
#endif /* __STDIN_FILENO > 2 || __STDOUT_FILENO > 2 || __STDERR_FILENO > 2 */
	return 0;
__err:
	return -1;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_login_tty_defined
#define __local___localdep_login_tty_defined
#define __localdep_login_tty __LIBC_LOCAL_NAME(login_tty)
#endif /* !__local___localdep_login_tty_defined */
#else /* __TIOCSCTTY && (__CRT_HAVE_ioctl || __CRT_HAVE___ioctl || __CRT_HAVE___libc_ioctl || __CRT_HAVE___ioctl_time64) && (__CRT_HAVE_setsid || __CRT_HAVE___setsid || __CRT_HAVE___libc_setsid) && (__CRT_HAVE_dup2 || __CRT_HAVE__dup2 || __CRT_HAVE___dup2 || __CRT_HAVE___libc_dup2) && (__CRT_HAVE_close || __CRT_HAVE__close || __CRT_HAVE___close || __CRT_HAVE___libc_close) */
#undef __local_login_tty_defined
#endif /* !__TIOCSCTTY || (!__CRT_HAVE_ioctl && !__CRT_HAVE___ioctl && !__CRT_HAVE___libc_ioctl && !__CRT_HAVE___ioctl_time64) || (!__CRT_HAVE_setsid && !__CRT_HAVE___setsid && !__CRT_HAVE___libc_setsid) || (!__CRT_HAVE_dup2 && !__CRT_HAVE__dup2 && !__CRT_HAVE___dup2 && !__CRT_HAVE___libc_dup2) || (!__CRT_HAVE_close && !__CRT_HAVE__close && !__CRT_HAVE___close && !__CRT_HAVE___libc_close) */
#endif /* !__local_login_tty_defined */
