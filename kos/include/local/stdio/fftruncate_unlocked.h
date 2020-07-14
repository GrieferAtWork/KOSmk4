/* HASH CRC-32:0x8c6ef943 */
/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_fftruncate_unlocked_defined
#define __local_fftruncate_unlocked_defined 1
#include <__crt.h>
#if ((defined(__CRT_HAVE__chsize) && !defined(__USE_FILE_OFFSET64)) || (defined(__CRT_HAVE_chsize) && !defined(__USE_FILE_OFFSET64)) || defined(__CRT_HAVE_ftruncate64) || defined(__CRT_HAVE__chsize_s) || defined(__CRT_HAVE_ftruncate)) && (defined(__CRT_HAVE_fileno) || defined(__CRT_HAVE__fileno) || defined(__CRT_HAVE_fileno_unlocked))
#ifndef __PIO_OFFSET
#ifdef __USE_KOS
#define __PIO_OFFSET   __FS_TYPE(__pos)
#define __PIO_OFFSET64 __pos64_t
#else /* __USE_KOS */
#define __PIO_OFFSET   __FS_TYPE(__off)
#define __PIO_OFFSET64 __off64_t
#endif /* !__USE_KOS */
#endif /* !__PIO_OFFSET */
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: fileno_unlocked from stdio */
#ifndef __local___localdep_fileno_unlocked_defined
#define __local___localdep_fileno_unlocked_defined 1
#if defined(__CRT_HAVE_fileno_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* Same as `fileno()', but performs I/O without acquiring a lock to `STREAM' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_NCX,__localdep_fileno_unlocked,(__FILE *__restrict __stream),fileno_unlocked,(__stream))
#elif defined(__CRT_HAVE_fileno)
/* Same as `fileno()', but performs I/O without acquiring a lock to `STREAM' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_NCX,__localdep_fileno_unlocked,(__FILE *__restrict __stream),fileno,(__stream))
#elif defined(__CRT_HAVE__fileno)
/* Same as `fileno()', but performs I/O without acquiring a lock to `STREAM' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_NCX,__localdep_fileno_unlocked,(__FILE *__restrict __stream),_fileno,(__stream))
#elif defined(__CRT_HAVE_fileno_unlocked)
/* Same as `fileno()', but performs I/O without acquiring a lock to `STREAM' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_NCX,__localdep_fileno_unlocked,(__FILE *__restrict __stream),fileno_unlocked,(__stream))
#else /* ... */
#undef __local___localdep_fileno_unlocked_defined
#endif /* !... */
#endif /* !__local___localdep_fileno_unlocked_defined */
/* Dependency: ftruncate from unistd */
#ifndef __local___localdep_ftruncate_defined
#define __local___localdep_ftruncate_defined 1
#if defined(__CRT_HAVE_ftruncate64) && defined(__USE_FILE_OFFSET64)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
/* >> ftruncate(2)
 * Truncate the given file `FD' to a length of `LENGTH' */
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_ftruncate,(__fd_t __fd, __PIO_OFFSET __length),ftruncate64,(__fd,__length))
#elif defined(__CRT_HAVE__chsize_s) && defined(__USE_FILE_OFFSET64)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
/* >> ftruncate(2)
 * Truncate the given file `FD' to a length of `LENGTH' */
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_ftruncate,(__fd_t __fd, __PIO_OFFSET __length),_chsize_s,(__fd,__length))
#elif defined(__CRT_HAVE_ftruncate) && !defined(__USE_FILE_OFFSET64)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
/* >> ftruncate(2)
 * Truncate the given file `FD' to a length of `LENGTH' */
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_ftruncate,(__fd_t __fd, __PIO_OFFSET __length),ftruncate,(__fd,__length))
#elif defined(__CRT_HAVE__chsize) && !defined(__USE_FILE_OFFSET64)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
/* >> ftruncate(2)
 * Truncate the given file `FD' to a length of `LENGTH' */
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_ftruncate,(__fd_t __fd, __PIO_OFFSET __length),_chsize,(__fd,__length))
#elif defined(__CRT_HAVE_chsize) && !defined(__USE_FILE_OFFSET64)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
/* >> ftruncate(2)
 * Truncate the given file `FD' to a length of `LENGTH' */
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_ftruncate,(__fd_t __fd, __PIO_OFFSET __length),chsize,(__fd,__length))
#elif defined(__CRT_HAVE_ftruncate64) || defined(__CRT_HAVE__chsize_s) || defined(__CRT_HAVE_ftruncate)
__NAMESPACE_LOCAL_END
#include <local/unistd/ftruncate.h>
__NAMESPACE_LOCAL_BEGIN
/* >> ftruncate(2)
 * Truncate the given file `FD' to a length of `LENGTH' */
#define __localdep_ftruncate __LIBC_LOCAL_NAME(ftruncate)
#else /* ... */
#undef __local___localdep_ftruncate_defined
#endif /* !... */
#endif /* !__local___localdep_ftruncate_defined */
/* >> fftruncate_unlocked(3)
 * Same as `fftruncate()', but don't acquire a lock to the file */
__LOCAL_LIBC(fftruncate_unlocked) __ATTR_NONNULL((1)) int
(__LIBCCALL __LIBC_LOCAL_NAME(fftruncate_unlocked))(__FILE *__restrict __stream, __PIO_OFFSET __length) __THROWS(...) {
	int __result = -1;
	__fd_t __fd = __localdep_fileno_unlocked(__stream);
	if __likely(__fd >= 0)
		__result = __localdep_ftruncate(__fd, __length);
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_fftruncate_unlocked_defined
#define __local___localdep_fftruncate_unlocked_defined 1
#define __localdep_fftruncate_unlocked __LIBC_LOCAL_NAME(fftruncate_unlocked)
#endif /* !__local___localdep_fftruncate_unlocked_defined */
#else /* ((__CRT_HAVE__chsize && !__USE_FILE_OFFSET64) || (__CRT_HAVE_chsize && !__USE_FILE_OFFSET64) || __CRT_HAVE_ftruncate64 || __CRT_HAVE__chsize_s || __CRT_HAVE_ftruncate) && (__CRT_HAVE_fileno || __CRT_HAVE__fileno || __CRT_HAVE_fileno_unlocked) */
#undef __local_fftruncate_unlocked_defined
#endif /* ((!__CRT_HAVE__chsize || __USE_FILE_OFFSET64) && (!__CRT_HAVE_chsize || __USE_FILE_OFFSET64) && !__CRT_HAVE_ftruncate64 && !__CRT_HAVE__chsize_s && !__CRT_HAVE_ftruncate) || (!__CRT_HAVE_fileno && !__CRT_HAVE__fileno && !__CRT_HAVE_fileno_unlocked) */
#endif /* !__local_fftruncate_unlocked_defined */
