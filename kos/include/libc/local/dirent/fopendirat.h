/* HASH CRC-32:0xdb363fa4 */
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
#ifndef __local_fopendirat_defined
#define __local_fopendirat_defined
#include <__crt.h>
#include <features.h>
#include <asm/os/oflags.h>
#if defined(__CRT_HAVE_fdopendir) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat))
struct __dirstream;
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_close_defined
#define __local___localdep_close_defined
#ifdef __CRT_HAVE_close
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_close,(__fd_t __fd),close,(__fd))
#elif defined(__CRT_HAVE__close)
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_close,(__fd_t __fd),_close,(__fd))
#elif defined(__CRT_HAVE___close)
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_close,(__fd_t __fd),__close,(__fd))
#elif defined(__CRT_HAVE___libc_close)
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_close,(__fd_t __fd),__libc_close,(__fd))
#else /* ... */
#undef __local___localdep_close_defined
#endif /* !... */
#endif /* !__local___localdep_close_defined */
#ifndef __local___localdep_fdopendir_defined
#define __local___localdep_fdopendir_defined
__CREDIRECT(__ATTR_WUNUSED,struct __dirstream *,__NOTHROW_NCX,__localdep_fdopendir,(__fd_t __fd),fdopendir,(__fd))
#endif /* !__local___localdep_fdopendir_defined */
#ifndef __local___localdep_openat_defined
#define __local___localdep_openat_defined
#if defined(__CRT_HAVE_openat) && (!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)
__CVREDIRECT(__ATTR_WUNUSED __ATTR_IN(2),__fd_t,__NOTHROW_RPC,__localdep_openat,(__fd_t __dirfd, char const *__filename, __oflag_t __oflags),openat,(__dirfd,__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE_openat64)
__CVREDIRECT(__ATTR_WUNUSED __ATTR_IN(2),__fd_t,__NOTHROW_RPC,__localdep_openat,(__fd_t __dirfd, char const *__filename, __oflag_t __oflags),openat64,(__dirfd,__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE_openat)
__NAMESPACE_LOCAL_END
#include <libc/local/fcntl/openat.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_openat __LIBC_LOCAL_NAME(openat)
#else /* ... */
#undef __local___localdep_openat_defined
#endif /* !... */
#endif /* !__local___localdep_openat_defined */
__LOCAL_LIBC(fopendirat) __ATTR_WUNUSED __ATTR_IN(2) struct __dirstream *
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(fopendirat))(__fd_t __dirfd, char const *__name, __oflag_t __oflags) {
	struct __dirstream *__result;
#ifdef __O_RDONLY
	__oflags |= __O_RDONLY;
#endif /* __O_RDONLY */
#ifdef __O_DIRECTORY
	__oflags |= __O_DIRECTORY;
#endif /* __O_DIRECTORY */
	__fd_t __fd = (__NAMESPACE_LOCAL_SYM __localdep_openat)(__dirfd, __name, __oflags);
	if __unlikely(__fd < 0)
		return __NULLPTR;
	__result = (__NAMESPACE_LOCAL_SYM __localdep_fdopendir)(__fd);
#if defined(__CRT_HAVE_close) || defined(__CRT_HAVE__close) || defined(__CRT_HAVE___close) || defined(__CRT_HAVE___libc_close)
	if __unlikely(!__result)
		(__NAMESPACE_LOCAL_SYM __localdep_close)(__fd);
#endif /* __CRT_HAVE_close || __CRT_HAVE__close || __CRT_HAVE___close || __CRT_HAVE___libc_close */
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_fopendirat_defined
#define __local___localdep_fopendirat_defined
#define __localdep_fopendirat __LIBC_LOCAL_NAME(fopendirat)
#endif /* !__local___localdep_fopendirat_defined */
#else /* __CRT_HAVE_fdopendir && (__CRT_HAVE_openat64 || __CRT_HAVE_openat) */
#undef __local_fopendirat_defined
#endif /* !__CRT_HAVE_fdopendir || (!__CRT_HAVE_openat64 && !__CRT_HAVE_openat) */
#endif /* !__local_fopendirat_defined */
