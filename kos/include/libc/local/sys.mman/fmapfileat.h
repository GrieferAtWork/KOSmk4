/* HASH CRC-32:0x2001de85 */
/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_fmapfileat_defined
#define __local_fmapfileat_defined
#include <__crt.h>
#include <asm/os/oflags.h>
#include <features.h>
#if defined(__O_RDONLY) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)) && (defined(__CRT_HAVE_fmapfile) || ((defined(__CRT_HAVE_read) || defined(__CRT_HAVE__read) || defined(__CRT_HAVE___read) || defined(__CRT_HAVE___libc_read)) && (defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)) && (defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))))
#include <bits/types.h>
#include <bits/crt/mapfile.h>
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
#ifndef __local___localdep_fmapfile_defined
#define __local___localdep_fmapfile_defined
#ifdef __CRT_HAVE_fmapfile
__CREDIRECT(__ATTR_WUNUSED __ATTR_FDARG(2) __ATTR_OUT(1),int,__NOTHROW_NCX,__localdep_fmapfile,(struct mapfile *__restrict __mapping, __fd_t __fd, __pos64_t __offset, __SIZE_TYPE__ __min_bytes, __SIZE_TYPE__ __max_bytes, __SIZE_TYPE__ __num_trailing_nulbytes, unsigned int __flags),fmapfile,(__mapping,__fd,__offset,__min_bytes,__max_bytes,__num_trailing_nulbytes,__flags))
#elif (defined(__CRT_HAVE_read) || defined(__CRT_HAVE__read) || defined(__CRT_HAVE___read) || defined(__CRT_HAVE___libc_read)) && (defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)) && (defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))
__NAMESPACE_LOCAL_END
#include <libc/local/sys.mman/fmapfile.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_fmapfile __LIBC_LOCAL_NAME(fmapfile)
#else /* ... */
#undef __local___localdep_fmapfile_defined
#endif /* !... */
#endif /* !__local___localdep_fmapfile_defined */
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
__NAMESPACE_LOCAL_END
#include <asm/os/fcntl.h>
#include <libc/errno.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(fmapfileat) __ATTR_WUNUSED __ATTR_IN(3) __ATTR_OUT(1) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(fmapfileat))(struct mapfile *__restrict __mapping, __fd_t __dirfd, char const *__filename, __pos64_t __offset, __SIZE_TYPE__ __min_bytes, __SIZE_TYPE__ __max_bytes, __SIZE_TYPE__ __num_trailing_nulbytes, unsigned int __flags, __atflag_t __atflags) {
	__fd_t __fd;
	int __result;
	__oflag_t __oflags = __O_RDONLY | __PRIVATE_O_CLOEXEC | __PRIVATE_O_CLOFORK;
#if defined(__AT_DOSPATH) && defined(__O_DOSPATH)
	if (__atflags & __AT_DOSPATH) {
		__oflags |= __O_DOSPATH;
		__atflags &= ~__AT_DOSPATH;
	}
#endif /* __AT_DOSPATH && __O_DOSPATH */
#ifdef __AT_EMPTY_PATH
	if (__atflags & __AT_EMPTY_PATH) {
		if (!*__filename) {
			return (__NAMESPACE_LOCAL_SYM __localdep_fmapfile)(__mapping, __dirfd,
			                __offset, __min_bytes, __max_bytes,
			                __num_trailing_nulbytes, __flags);
		}
		__atflags &= ~__AT_EMPTY_PATH;
	}
#endif /* __AT_EMPTY_PATH */
	if __unlikely(__atflags != 0) {
#ifdef __EINVAL
		return __libc_seterrno(__EINVAL);
#else /* __EINVAL */
		return __libc_seterrno(1);
#endif /* !__EINVAL */
	}
	__fd = (__NAMESPACE_LOCAL_SYM __localdep_openat)(__dirfd, __filename, __oflags);
	if __unlikely(__fd < 0)
		return -1;
	__result = (__NAMESPACE_LOCAL_SYM __localdep_fmapfile)(__mapping, __fd,
	                  __offset, __min_bytes, __max_bytes,
	                  __num_trailing_nulbytes,
	                  __flags | __FMAPFILE_ATSTART);
#if defined(__CRT_HAVE_close) || defined(__CRT_HAVE__close) || defined(__CRT_HAVE___close) || defined(__CRT_HAVE___libc_close)
	(__NAMESPACE_LOCAL_SYM __localdep_close)(__fd);
#endif /* __CRT_HAVE_close || __CRT_HAVE__close || __CRT_HAVE___close || __CRT_HAVE___libc_close */
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_fmapfileat_defined
#define __local___localdep_fmapfileat_defined
#define __localdep_fmapfileat __LIBC_LOCAL_NAME(fmapfileat)
#endif /* !__local___localdep_fmapfileat_defined */
#else /* __O_RDONLY && (__CRT_HAVE_openat64 || __CRT_HAVE_openat) && (__CRT_HAVE_fmapfile || ((__CRT_HAVE_read || __CRT_HAVE__read || __CRT_HAVE___read || __CRT_HAVE___libc_read) && (__CRT_HAVE_malloc || __CRT_HAVE___libc_malloc || __CRT_HAVE_calloc || __CRT_HAVE___libc_calloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc || __CRT_HAVE_memalign || __CRT_HAVE_aligned_alloc || __CRT_HAVE___libc_memalign || __CRT_HAVE_posix_memalign) && (__CRT_HAVE_realloc || __CRT_HAVE___libc_realloc))) */
#undef __local_fmapfileat_defined
#endif /* !__O_RDONLY || (!__CRT_HAVE_openat64 && !__CRT_HAVE_openat) || (!__CRT_HAVE_fmapfile && ((!__CRT_HAVE_read && !__CRT_HAVE__read && !__CRT_HAVE___read && !__CRT_HAVE___libc_read) || (!__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc))) */
#endif /* !__local_fmapfileat_defined */
