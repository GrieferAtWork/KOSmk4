/* HASH CRC-32:0xf76398e0 */
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
#ifndef __local_mapfile_defined
#define __local_mapfile_defined
#include <__crt.h>
#include <asm/os/fcntl.h>
#include <asm/os/oflags.h>
#include <features.h>
#if (defined(__AT_FDCWD) && (defined(__CRT_HAVE_fmapfileat) || (defined(__O_RDONLY) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)) && (defined(__CRT_HAVE_fmapfile) || ((defined(__CRT_HAVE_read) || defined(__CRT_HAVE__read) || defined(__CRT_HAVE___read) || defined(__CRT_HAVE___libc_read)) && (defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)) && (defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))))))) || (defined(__O_RDONLY) && (defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)))) && (defined(__CRT_HAVE_fmapfile) || ((defined(__CRT_HAVE_read) || defined(__CRT_HAVE__read) || defined(__CRT_HAVE___read) || defined(__CRT_HAVE___libc_read)) && (defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)) && (defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))))
#include <bits/types.h>
#include <bits/crt/mapfile.h>
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
#ifndef __local___localdep_fmapfile_defined
#define __local___localdep_fmapfile_defined
#ifdef __CRT_HAVE_fmapfile
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,__localdep_fmapfile,(struct mapfile *__restrict __mapping, __fd_t __fd, __pos64_t __offset, __SIZE_TYPE__ __max_bytes, __SIZE_TYPE__ __num_trailing_nulbytes),fmapfile,(__mapping,__fd,__offset,__max_bytes,__num_trailing_nulbytes))
#elif (defined(__CRT_HAVE_read) || defined(__CRT_HAVE__read) || defined(__CRT_HAVE___read) || defined(__CRT_HAVE___libc_read)) && (defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)) && (defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))
__NAMESPACE_LOCAL_END
#include <libc/local/sys.mman/fmapfile.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_fmapfile __LIBC_LOCAL_NAME(fmapfile)
#else /* ... */
#undef __local___localdep_fmapfile_defined
#endif /* !... */
#endif /* !__local___localdep_fmapfile_defined */
#ifndef __local___localdep_fmapfileat_defined
#define __local___localdep_fmapfileat_defined
#ifdef __CRT_HAVE_fmapfileat
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 3)),int,__NOTHROW_NCX,__localdep_fmapfileat,(struct mapfile *__restrict __mapping, __fd_t __dirfd, char const *__filename, __pos64_t __offset, __SIZE_TYPE__ __max_bytes, __SIZE_TYPE__ __num_trailing_nulbytes, __atflag_t __atflags),fmapfileat,(__mapping,__dirfd,__filename,__offset,__max_bytes,__num_trailing_nulbytes,__atflags))
#elif defined(__O_RDONLY) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)) && (defined(__CRT_HAVE_fmapfile) || ((defined(__CRT_HAVE_read) || defined(__CRT_HAVE__read) || defined(__CRT_HAVE___read) || defined(__CRT_HAVE___libc_read)) && (defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)) && (defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))))
__NAMESPACE_LOCAL_END
#include <libc/local/sys.mman/fmapfileat.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_fmapfileat __LIBC_LOCAL_NAME(fmapfileat)
#else /* ... */
#undef __local___localdep_fmapfileat_defined
#endif /* !... */
#endif /* !__local___localdep_fmapfileat_defined */
#ifndef __local___localdep_open_defined
#define __local___localdep_open_defined
#if defined(__CRT_HAVE_open) && (!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)
__CVREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_RPC,__localdep_open,(char const *__filename, __oflag_t __oflags),open,(__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE__open) && (!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)
__CVREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_RPC,__localdep_open,(char const *__filename, __oflag_t __oflags),_open,(__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE___open) && (!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)
__CVREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_RPC,__localdep_open,(char const *__filename, __oflag_t __oflags),__open,(__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE___libc_open) && (!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)
__CVREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_RPC,__localdep_open,(char const *__filename, __oflag_t __oflags),__libc_open,(__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE_open64)
__CVREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_RPC,__localdep_open,(char const *__filename, __oflag_t __oflags),open64,(__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE___open64)
__CVREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_RPC,__localdep_open,(char const *__filename, __oflag_t __oflags),__open64,(__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)))
__NAMESPACE_LOCAL_END
#include <libc/local/fcntl/open.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_open __LIBC_LOCAL_NAME(open)
#else /* ... */
#undef __local___localdep_open_defined
#endif /* !... */
#endif /* !__local___localdep_open_defined */
__LOCAL_LIBC(mapfile) __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(mapfile))(struct mapfile *__restrict __mapping, char const *__filename, __pos64_t __offset, __SIZE_TYPE__ __max_bytes, __SIZE_TYPE__ __num_trailing_nulbytes) {
#if defined(__AT_FDCWD) && (defined(__CRT_HAVE_fmapfileat) || (defined(__O_RDONLY) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)) && (defined(__CRT_HAVE_fmapfile) || ((defined(__CRT_HAVE_read) || defined(__CRT_HAVE__read) || defined(__CRT_HAVE___read) || defined(__CRT_HAVE___libc_read)) && (defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)) && (defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))))))
	return (__NAMESPACE_LOCAL_SYM __localdep_fmapfileat)(__mapping, __AT_FDCWD, __filename, __offset, __max_bytes, __num_trailing_nulbytes, 0);
#else /* __AT_FDCWD && (__CRT_HAVE_fmapfileat || (__O_RDONLY && (__CRT_HAVE_openat64 || __CRT_HAVE_openat) && (__CRT_HAVE_fmapfile || ((__CRT_HAVE_read || __CRT_HAVE__read || __CRT_HAVE___read || __CRT_HAVE___libc_read) && (__CRT_HAVE_malloc || __CRT_HAVE___libc_malloc || __CRT_HAVE_calloc || __CRT_HAVE___libc_calloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc || __CRT_HAVE_memalign || __CRT_HAVE_aligned_alloc || __CRT_HAVE___libc_memalign || __CRT_HAVE_posix_memalign) && (__CRT_HAVE_realloc || __CRT_HAVE___libc_realloc))))) */
#if defined(__O_CLOEXEC) && defined(__O_CLOFORK)
	__fd_t __fd = (__NAMESPACE_LOCAL_SYM __localdep_open)(__filename, __O_RDONLY | __O_CLOEXEC | __O_CLOFORK);
#elif defined(__O_CLOEXEC)
	__fd_t __fd = (__NAMESPACE_LOCAL_SYM __localdep_open)(__filename, __O_RDONLY | __O_CLOEXEC);
#elif defined(__O_CLOFORK)
	__fd_t __fd = (__NAMESPACE_LOCAL_SYM __localdep_open)(__filename, __O_RDONLY | __O_CLOFORK);
#else /* ... */
	__fd_t __fd = (__NAMESPACE_LOCAL_SYM __localdep_open)(__filename, __O_RDONLY);
#endif /* !... */
	if __unlikely(__fd < 0)
		return -1;
	__result = (__NAMESPACE_LOCAL_SYM __localdep_fmapfile)(__mapping, __fd, __offset, __max_bytes, __num_trailing_nulbytes);
#if defined(__CRT_HAVE_close) || defined(__CRT_HAVE__close) || defined(__CRT_HAVE___close) || defined(__CRT_HAVE___libc_close)
	(__NAMESPACE_LOCAL_SYM __localdep_close)(__fd);
#endif /* __CRT_HAVE_close || __CRT_HAVE__close || __CRT_HAVE___close || __CRT_HAVE___libc_close */
	return __result;
#endif /* !__AT_FDCWD || (!__CRT_HAVE_fmapfileat && (!__O_RDONLY || (!__CRT_HAVE_openat64 && !__CRT_HAVE_openat) || (!__CRT_HAVE_fmapfile && ((!__CRT_HAVE_read && !__CRT_HAVE__read && !__CRT_HAVE___read && !__CRT_HAVE___libc_read) || (!__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc))))) */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_mapfile_defined
#define __local___localdep_mapfile_defined
#define __localdep_mapfile __LIBC_LOCAL_NAME(mapfile)
#endif /* !__local___localdep_mapfile_defined */
#else /* (__AT_FDCWD && (__CRT_HAVE_fmapfileat || (__O_RDONLY && (__CRT_HAVE_openat64 || __CRT_HAVE_openat) && (__CRT_HAVE_fmapfile || ((__CRT_HAVE_read || __CRT_HAVE__read || __CRT_HAVE___read || __CRT_HAVE___libc_read) && (__CRT_HAVE_malloc || __CRT_HAVE___libc_malloc || __CRT_HAVE_calloc || __CRT_HAVE___libc_calloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc || __CRT_HAVE_memalign || __CRT_HAVE_aligned_alloc || __CRT_HAVE___libc_memalign || __CRT_HAVE_posix_memalign) && (__CRT_HAVE_realloc || __CRT_HAVE___libc_realloc)))))) || (__O_RDONLY && (__CRT_HAVE_open64 || __CRT_HAVE___open64 || __CRT_HAVE_open || __CRT_HAVE__open || __CRT_HAVE___open || __CRT_HAVE___libc_open || (__AT_FDCWD && (__CRT_HAVE_openat64 || __CRT_HAVE_openat))) && (__CRT_HAVE_fmapfile || ((__CRT_HAVE_read || __CRT_HAVE__read || __CRT_HAVE___read || __CRT_HAVE___libc_read) && (__CRT_HAVE_malloc || __CRT_HAVE___libc_malloc || __CRT_HAVE_calloc || __CRT_HAVE___libc_calloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc || __CRT_HAVE_memalign || __CRT_HAVE_aligned_alloc || __CRT_HAVE___libc_memalign || __CRT_HAVE_posix_memalign) && (__CRT_HAVE_realloc || __CRT_HAVE___libc_realloc)))) */
#undef __local_mapfile_defined
#endif /* (!__AT_FDCWD || (!__CRT_HAVE_fmapfileat && (!__O_RDONLY || (!__CRT_HAVE_openat64 && !__CRT_HAVE_openat) || (!__CRT_HAVE_fmapfile && ((!__CRT_HAVE_read && !__CRT_HAVE__read && !__CRT_HAVE___read && !__CRT_HAVE___libc_read) || (!__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc)))))) && (!__O_RDONLY || (!__CRT_HAVE_open64 && !__CRT_HAVE___open64 && !__CRT_HAVE_open && !__CRT_HAVE__open && !__CRT_HAVE___open && !__CRT_HAVE___libc_open && (!__AT_FDCWD || (!__CRT_HAVE_openat64 && !__CRT_HAVE_openat))) || (!__CRT_HAVE_fmapfile && ((!__CRT_HAVE_read && !__CRT_HAVE__read && !__CRT_HAVE___read && !__CRT_HAVE___libc_read) || (!__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc)))) */
#endif /* !__local_mapfile_defined */
