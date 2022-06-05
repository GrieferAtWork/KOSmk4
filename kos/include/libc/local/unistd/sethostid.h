/* HASH CRC-32:0xca98257e */
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
#ifndef __local_sethostid_defined
#define __local_sethostid_defined
#include <__crt.h>
#include <asm/os/oflags.h>
#include <paths.h>
#include <features.h>
#include <asm/os/fcntl.h>
#include <hybrid/typecore.h>
#include <bits/crt/format-printer.h>
#if (defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)))) && (defined(__CRT_HAVE_writeall) || (defined(__CRT_HAVE_write_printer) && defined(__LIBCCALL_IS_FORMATPRINTER_CC) && __SIZEOF_INT__ == __SIZEOF_POINTER__) || defined(__CRT_HAVE_write) || defined(__CRT_HAVE__write) || defined(__CRT_HAVE___write) || defined(__CRT_HAVE___libc_write)) && defined(__O_WRONLY) && defined(__O_CREAT) && defined(__O_TRUNC) && defined(_PATH_HOSTID)
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_close_defined
#define __local___localdep_close_defined
#ifdef __CRT_HAVE_close
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_close,(__fd_t __fd),close,(__fd))
#elif defined(__CRT_HAVE__close)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_close,(__fd_t __fd),_close,(__fd))
#elif defined(__CRT_HAVE___close)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_close,(__fd_t __fd),__close,(__fd))
#elif defined(__CRT_HAVE___libc_close)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_close,(__fd_t __fd),__libc_close,(__fd))
#else /* ... */
#undef __local___localdep_close_defined
#endif /* !... */
#endif /* !__local___localdep_close_defined */
#ifndef __local___localdep_mkdir_defined
#define __local___localdep_mkdir_defined
#ifdef __CRT_HAVE_mkdir
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN(1),int,__NOTHROW_RPC,__localdep_mkdir,(char const *__pathname, __mode_t __mode),mkdir,(__pathname,__mode))
#elif defined(__CRT_HAVE___mkdir)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN(1),int,__NOTHROW_RPC,__localdep_mkdir,(char const *__pathname, __mode_t __mode),__mkdir,(__pathname,__mode))
#elif defined(__CRT_HAVE___libc_mkdir)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN(1),int,__NOTHROW_RPC,__localdep_mkdir,(char const *__pathname, __mode_t __mode),__libc_mkdir,(__pathname,__mode))
#elif (defined(__CRT_DOS_PRIMARY) && defined(__CRT_HAVE__mkdir)) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_mkdirat) || defined(__CRT_HAVE_fmkdirat)))
__NAMESPACE_LOCAL_END
#include <libc/local/sys.stat/mkdir.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_mkdir __LIBC_LOCAL_NAME(mkdir)
#else /* ... */
#undef __local___localdep_mkdir_defined
#endif /* !... */
#endif /* !__local___localdep_mkdir_defined */
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
#ifndef __local___localdep_writeall_defined
#define __local___localdep_writeall_defined
#ifdef __CRT_HAVE_writeall
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_INS(2, 3),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_writeall,(__fd_t __fd, void const *__buf, __SIZE_TYPE__ __bufsize),writeall,(__fd,__buf,__bufsize))
#elif defined(__CRT_HAVE_write_printer) && defined(__LIBCCALL_IS_FORMATPRINTER_CC) && __SIZEOF_INT__ == __SIZEOF_POINTER__
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_INS(2, 3),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_writeall,(__fd_t __fd, void const *__buf, __SIZE_TYPE__ __bufsize),write_printer,(__fd,__buf,__bufsize))
#elif defined(__CRT_HAVE_write) || defined(__CRT_HAVE__write) || defined(__CRT_HAVE___write) || defined(__CRT_HAVE___libc_write)
__NAMESPACE_LOCAL_END
#include <libc/local/unistd/writeall.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_writeall __LIBC_LOCAL_NAME(writeall)
#else /* ... */
#undef __local___localdep_writeall_defined
#endif /* !... */
#endif /* !__local___localdep_writeall_defined */
__NAMESPACE_LOCAL_END
#include <libc/errno.h>
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(sethostid) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(sethostid))(__LONGPTR_TYPE__ __id) {
	__fd_t __fd;
	__SSIZE_TYPE__ __count;
	__UINT32_TYPE__ __id32;

	/* Ensure that `id' fits into 4 bytes */
#if __SIZEOF_POINTER__ > 4
	if (__id & ~__UINT32_C(0xffffffff)) {
#ifdef __EOVERFLOW
		return __libc_seterrno(__EOVERFLOW);
#else /* __EOVERFLOW */
		return __libc_seterrno(1);
#endif /* !__EOVERFLOW */
	}
#endif /* __SIZEOF_POINTER__ > 4 */

	/* Try to open the hostid file for writing */
	__fd = (__NAMESPACE_LOCAL_SYM __localdep_open)(_PATH_HOSTID, __O_WRONLY | __O_CREAT | __O_TRUNC | __PRIVATE_O_CLOEXEC | __PRIVATE_O_CLOFORK, 0644);
	if (__fd < 0) {
		/* Try to lazily create the containing directory if it's missing. */
#if (defined(__CRT_HAVE_mkdir) || defined(__CRT_HAVE___mkdir) || defined(__CRT_HAVE___libc_mkdir) || (defined(__CRT_DOS_PRIMARY) && defined(__CRT_HAVE__mkdir)) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_mkdirat) || defined(__CRT_HAVE_fmkdirat)))) && defined(__libc_geterrno_or) && defined(__ENOTDIR)
		if (__libc_geterrno() == __ENOTDIR) {
			/* Check if /etc was already created. */
#ifndef __EEXIST
			(__NAMESPACE_LOCAL_SYM __localdep_mkdir)(_PATH_HOSTID_CONTAINING_DIRECTORY, 0755);
#else /* !__EEXIST */
			if ((__NAMESPACE_LOCAL_SYM __localdep_mkdir)(_PATH_HOSTID_CONTAINING_DIRECTORY, 0755) == 0 ||
			    __libc_geterrno() == __EEXIST)
#endif /* __EEXIST */
			{
				__fd = (__NAMESPACE_LOCAL_SYM __localdep_open)(_PATH_HOSTID, __O_WRONLY | __O_CREAT | __O_TRUNC | __PRIVATE_O_CLOEXEC | __PRIVATE_O_CLOFORK, 0644);
				if (__fd >= 0)
					goto __got_fd;
#define __WANT_got_fd
			}
		}
#endif /* (__CRT_HAVE_mkdir || __CRT_HAVE___mkdir || __CRT_HAVE___libc_mkdir || (__CRT_DOS_PRIMARY && __CRT_HAVE__mkdir) || (__AT_FDCWD && (__CRT_HAVE_mkdirat || __CRT_HAVE_fmkdirat))) && __libc_geterrno_or && __ENOTDIR */
		return __fd;
	}
#ifdef __WANT_got_fd
#undef __WANT_got_fd
__got_fd:
#endif /* WANT_got_fd */
	__id32  = (__UINT32_TYPE__)(__ULONGPTR_TYPE__)__id;
	__count = (__NAMESPACE_LOCAL_SYM __localdep_writeall)(__fd, &__id32, 4);
#if defined(__CRT_HAVE_close) || defined(__CRT_HAVE__close) || defined(__CRT_HAVE___close) || defined(__CRT_HAVE___libc_close)
	(__NAMESPACE_LOCAL_SYM __localdep_close)(__fd);
#endif /* __CRT_HAVE_close || __CRT_HAVE__close || __CRT_HAVE___close || __CRT_HAVE___libc_close */
	if (__count != 4) {
#ifdef __ENOSPC
		if (__count >= 0)
			__libc_seterrno(__ENOSPC); /* ??? */
#endif /* __ENOSPC */
		return -1;
	}
	return 0;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_sethostid_defined
#define __local___localdep_sethostid_defined
#define __localdep_sethostid __LIBC_LOCAL_NAME(sethostid)
#endif /* !__local___localdep_sethostid_defined */
#else /* (__CRT_HAVE_open64 || __CRT_HAVE___open64 || __CRT_HAVE_open || __CRT_HAVE__open || __CRT_HAVE___open || __CRT_HAVE___libc_open || (__AT_FDCWD && (__CRT_HAVE_openat64 || __CRT_HAVE_openat))) && (__CRT_HAVE_writeall || (__CRT_HAVE_write_printer && __LIBCCALL_IS_FORMATPRINTER_CC && __SIZEOF_INT__ == __SIZEOF_POINTER__) || __CRT_HAVE_write || __CRT_HAVE__write || __CRT_HAVE___write || __CRT_HAVE___libc_write) && __O_WRONLY && __O_CREAT && __O_TRUNC && _PATH_HOSTID */
#undef __local_sethostid_defined
#endif /* (!__CRT_HAVE_open64 && !__CRT_HAVE___open64 && !__CRT_HAVE_open && !__CRT_HAVE__open && !__CRT_HAVE___open && !__CRT_HAVE___libc_open && (!__AT_FDCWD || (!__CRT_HAVE_openat64 && !__CRT_HAVE_openat))) || (!__CRT_HAVE_writeall && (!__CRT_HAVE_write_printer || !__LIBCCALL_IS_FORMATPRINTER_CC || __SIZEOF_INT__ != __SIZEOF_POINTER__) && !__CRT_HAVE_write && !__CRT_HAVE__write && !__CRT_HAVE___write && !__CRT_HAVE___libc_write) || !__O_WRONLY || !__O_CREAT || !__O_TRUNC || !_PATH_HOSTID */
#endif /* !__local_sethostid_defined */
