/* HASH CRC-32:0x2c5620d9 */
/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_wtruncate64_defined
#if defined(__CRT_HAVE_wtruncate) || ((defined(__CRT_HAVE_open) || defined(__CRT_HAVE_open64) || defined(__CRT_HAVE__open)) && (defined(__CRT_HAVE__chsize_s) || defined(__CRT_HAVE__chsize) || defined(__CRT_HAVE_ftruncate) || defined(__CRT_HAVE_ftruncate64)))
#define __local_wtruncate64_defined 1
#include <bits/types.h>
/* Dependency: "wtruncate32" from "parts.wchar.unistd" */
#ifndef ____localdep_wtruncate32_defined
#define ____localdep_wtruncate32_defined 1
#ifdef __CRT_HAVE_wtruncate
/* >> truncate(2)
 * Truncate the given file `FILE' to a length of `LENGTH' */
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_wtruncate32,(__WCHAR_TYPE__ const *__file, __pos32_t __length),wtruncate,(__file,__length))
#else /* LIBC: wtruncate */
#undef ____localdep_wtruncate32_defined
#endif /* wtruncate32... */
#endif /* !____localdep_wtruncate32_defined */

/* Dependency: "open64" from "fcntl" */
#ifndef ____localdep_open64_defined
#define ____localdep_open64_defined 1
#ifdef __CRT_HAVE_open64
__CVREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_RPC,__localdep_open64,(char const *__filename, __oflag_t __oflags),open64,(__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE___open64)
__CVREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_RPC,__localdep_open64,(char const *__filename, __oflag_t __oflags),__open64,(__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE_open) && (!defined(__O_LARGEFILE) || (__O_LARGEFILE+0) == 0)
__CVREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_RPC,__localdep_open64,(char const *__filename, __oflag_t __oflags),open,(__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE__open) && (!defined(__O_LARGEFILE) || (__O_LARGEFILE+0) == 0)
__CVREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_RPC,__localdep_open64,(char const *__filename, __oflag_t __oflags),_open,(__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open)
#include <local/fcntl/open64.h>
#define __localdep_open64 (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(open64))
#else /* CUSTOM: open64 */
#undef ____localdep_open64_defined
#endif /* open64... */
#endif /* !____localdep_open64_defined */

/* Dependency: "open" from "fcntl" */
#ifndef ____localdep_open_defined
#define ____localdep_open_defined 1
#if defined(__CRT_HAVE_open64) && (defined(__USE_FILE_OFFSET64))
__CVREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_RPC,__localdep_open,(char const *__filename, __oflag_t __oflags),open64,(__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE_open) && (!defined(__USE_FILE_OFFSET64))
__CVREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_RPC,__localdep_open,(char const *__filename, __oflag_t __oflags),open,(__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE___open)
__CVREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_RPC,__localdep_open,(char const *__filename, __oflag_t __oflags),__open,(__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE__open)
__CVREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_RPC,__localdep_open,(char const *__filename, __oflag_t __oflags),_open,(__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || (defined(__CRT_AT_FDCWD) && (defined(__CRT_HAVE_openat) || defined(__CRT_HAVE_openat64)))
#include <local/fcntl/open.h>
#define __localdep_open (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(open))
#else /* CUSTOM: open */
#undef ____localdep_open_defined
#endif /* open... */
#endif /* !____localdep_open_defined */

/* Dependency: "ftruncate64" from "unistd" */
#ifndef ____localdep_ftruncate64_defined
#define ____localdep_ftruncate64_defined 1
#ifdef __CRT_HAVE_ftruncate64
/* >> ftruncate64(2)
 * Truncate the given file `FD' to a length of `LENGTH' */
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_ftruncate64,(__fd_t __fd, __PIO_OFFSET64 __length),ftruncate64,(__fd,__length))
#elif defined(__CRT_HAVE_ftruncate) && (__SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> ftruncate64(2)
 * Truncate the given file `FD' to a length of `LENGTH' */
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_ftruncate64,(__fd_t __fd, __PIO_OFFSET64 __length),ftruncate,(__fd,__length))
#elif defined(__CRT_HAVE__chsize_s)
/* >> ftruncate64(2)
 * Truncate the given file `FD' to a length of `LENGTH' */
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_ftruncate64,(__fd_t __fd, __PIO_OFFSET64 __length),_chsize_s,(__fd,__length))
#elif defined(__CRT_HAVE_ftruncate) || defined(__CRT_HAVE__chsize)
#include <local/unistd/ftruncate64.h>
/* >> ftruncate64(2)
 * Truncate the given file `FD' to a length of `LENGTH' */
#define __localdep_ftruncate64 (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ftruncate64))
#else /* CUSTOM: ftruncate64 */
#undef ____localdep_ftruncate64_defined
#endif /* ftruncate64... */
#endif /* !____localdep_ftruncate64_defined */

/* Dependency: "close" */
#ifndef ____localdep_close_defined
#define ____localdep_close_defined 1
#ifdef __CRT_HAVE_close
/* >> close(2)
 * Close a file handle */
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_close,(__fd_t __fd),close,(__fd))
#elif defined(__CRT_HAVE__close)
/* >> close(2)
 * Close a file handle */
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_close,(__fd_t __fd),_close,(__fd))
#elif defined(__CRT_HAVE___close)
/* >> close(2)
 * Close a file handle */
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_close,(__fd_t __fd),__close,(__fd))
#else /* LIBC: close */
#undef ____localdep_close_defined
#endif /* close... */
#endif /* !____localdep_close_defined */

__NAMESPACE_LOCAL_BEGIN
#ifndef __PIO_OFFSET
#ifdef __USE_KOS
#define __PIO_OFFSET     __FS_TYPE(pos)
#define __PIO_OFFSET64   __pos64_t
#else /* __USE_KOS */
#define __PIO_OFFSET     __FS_TYPE(off)
#define __PIO_OFFSET64   __off64_t
#endif /* !__USE_KOS */
#endif /* !__PIO_OFFSET */
/* >> wtruncate(2)
 * Truncate the given file `FILE' to a length of `LENGTH' */
__LOCAL_LIBC(wtruncate64) __ATTR_NONNULL((1)) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(wtruncate64))(__WCHAR_TYPE__ const *__file,
                                                         __PIO_OFFSET64 __length) {
#line 1300 "kos/src/libc/magic/unistd.c"
#if defined(__CRT_HAVE_wtruncate) && (!defined(__CRT_HAVE_open) || !defined(__CRT_HAVE_open64) || !defined(__CRT_HAVE__open) || (!defined(__CRT_HAVE__chsize_s) && !defined(__CRT_HAVE_ftruncate64)))
	return __localdep_wtruncate32(__file, (__PIO_OFFSET)__length);
#else
	int __result;
	__fd_t __fd;
#if defined(__CRT_HAVE_open64)
	__fd = __localdep_open64(__file, 1); /* O_WRONLY */
#else
	__fd = __localdep_open(__file, 1); /* O_WRONLY */
#endif
	if __unlikely(__fd < 0)
		return -1;
	__result = __localdep_ftruncate64(__fd, __length);
#if defined(__CRT_HAVE_close) || defined(__CRT_HAVE__close)
	__localdep_close(__fd);
#endif
	return __result;
#endif
}
__NAMESPACE_LOCAL_END
#endif /* defined(__CRT_HAVE_wtruncate) || ((defined(__CRT_HAVE_open) || defined(__CRT_HAVE_open64) || defined(__CRT_HAVE__open)) && (defined(__CRT_HAVE__chsize_s) || defined(__CRT_HAVE__chsize) || defined(__CRT_HAVE_ftruncate) || defined(__CRT_HAVE_ftruncate64))) */
#endif /* !__local_wtruncate64_defined */
