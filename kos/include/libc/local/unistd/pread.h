/* HASH CRC-32:0xe319f629 */
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
#ifndef __local_pread_defined
#define __local_pread_defined 1
#include <__crt.h>
#include <asm/stdio.h>
#if defined(__CRT_HAVE_pread64) || defined(__CRT_HAVE___pread64) || defined(__CRT_HAVE_pread) || ((defined(__CRT_HAVE_lseek64) || defined(__CRT_HAVE__lseeki64) || defined(__CRT_HAVE_lseek) || defined(__CRT_HAVE__lseek) || defined(__CRT_HAVE___lseek)) && (defined(__CRT_HAVE_read) || defined(__CRT_HAVE__read) || defined(__CRT_HAVE___read)) && defined(__SEEK_CUR) && defined(__SEEK_SET))
#ifndef __PIO_OFFSET
#ifdef __USE_KOS_ALTERATIONS
#define __PIO_OFFSET   __FS_TYPE(__pos)
#define __PIO_OFFSET64 __pos64_t
#else /* __USE_KOS_ALTERATIONS */
#define __PIO_OFFSET   __FS_TYPE(__off)
#define __PIO_OFFSET64 __off64_t
#endif /* !__USE_KOS_ALTERATIONS */
#endif /* !__PIO_OFFSET */
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: lseek from unistd */
#ifndef __local___localdep_lseek_defined
#define __local___localdep_lseek_defined 1
#if defined(__CRT_HAVE_lseek64) && defined(__USE_FILE_OFFSET64)
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
/* >> lseek(2)
 * Change the position of the file read/write pointer within a file referred to by `FD' */
__CREDIRECT(,__FS_TYPE(off),__NOTHROW_NCX,__localdep_lseek,(__fd_t __fd, __FS_TYPE(off) __offset, __STDC_INT_AS_UINT_T __whence),lseek64,(__fd,__offset,__whence))
#elif defined(__CRT_HAVE__lseeki64) && defined(__USE_FILE_OFFSET64)
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
/* >> lseek(2)
 * Change the position of the file read/write pointer within a file referred to by `FD' */
__CREDIRECT(,__FS_TYPE(off),__NOTHROW_NCX,__localdep_lseek,(__fd_t __fd, __FS_TYPE(off) __offset, __STDC_INT_AS_UINT_T __whence),_lseeki64,(__fd,__offset,__whence))
#elif defined(__CRT_HAVE_lseek) && !defined(__USE_FILE_OFFSET64)
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
/* >> lseek(2)
 * Change the position of the file read/write pointer within a file referred to by `FD' */
__CREDIRECT(,__FS_TYPE(off),__NOTHROW_NCX,__localdep_lseek,(__fd_t __fd, __FS_TYPE(off) __offset, __STDC_INT_AS_UINT_T __whence),lseek,(__fd,__offset,__whence))
#elif defined(__CRT_HAVE__lseek) && !defined(__USE_FILE_OFFSET64)
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
/* >> lseek(2)
 * Change the position of the file read/write pointer within a file referred to by `FD' */
__CREDIRECT(,__FS_TYPE(off),__NOTHROW_NCX,__localdep_lseek,(__fd_t __fd, __FS_TYPE(off) __offset, __STDC_INT_AS_UINT_T __whence),_lseek,(__fd,__offset,__whence))
#elif defined(__CRT_HAVE___lseek) && !defined(__USE_FILE_OFFSET64)
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
/* >> lseek(2)
 * Change the position of the file read/write pointer within a file referred to by `FD' */
__CREDIRECT(,__FS_TYPE(off),__NOTHROW_NCX,__localdep_lseek,(__fd_t __fd, __FS_TYPE(off) __offset, __STDC_INT_AS_UINT_T __whence),__lseek,(__fd,__offset,__whence))
#elif defined(__CRT_HAVE_lseek64) || defined(__CRT_HAVE__lseeki64) || defined(__CRT_HAVE_lseek) || defined(__CRT_HAVE__lseek) || defined(__CRT_HAVE___lseek)
__NAMESPACE_LOCAL_END
#include <libc/local/unistd/lseek.h>
__NAMESPACE_LOCAL_BEGIN
/* >> lseek(2)
 * Change the position of the file read/write pointer within a file referred to by `FD' */
#define __localdep_lseek __LIBC_LOCAL_NAME(lseek)
#else /* ... */
#undef __local___localdep_lseek_defined
#endif /* !... */
#endif /* !__local___localdep_lseek_defined */
/* Dependency: pread64 from unistd */
#ifndef __local___localdep_pread64_defined
#define __local___localdep_pread64_defined 1
#ifdef __CRT_HAVE_pread64
/* >> pread64(2)
 * Read data from a file at a specific offset */
__CREDIRECT(__ATTR_NONNULL((2)),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_pread64,(__fd_t __fd, void *__buf, __SIZE_TYPE__ __bufsize, __PIO_OFFSET64 __offset),pread64,(__fd,__buf,__bufsize,__offset))
#elif defined(__CRT_HAVE_pread) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
/* >> pread64(2)
 * Read data from a file at a specific offset */
__CREDIRECT(__ATTR_NONNULL((2)),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_pread64,(__fd_t __fd, void *__buf, __SIZE_TYPE__ __bufsize, __PIO_OFFSET64 __offset),pread,(__fd,__buf,__bufsize,__offset))
#elif defined(__CRT_HAVE___pread64)
/* >> pread64(2)
 * Read data from a file at a specific offset */
__CREDIRECT(__ATTR_NONNULL((2)),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_pread64,(__fd_t __fd, void *__buf, __SIZE_TYPE__ __bufsize, __PIO_OFFSET64 __offset),__pread64,(__fd,__buf,__bufsize,__offset))
#elif defined(__CRT_HAVE_pread) || ((defined(__CRT_HAVE_lseek64) || defined(__CRT_HAVE__lseeki64) || defined(__CRT_HAVE_lseek) || defined(__CRT_HAVE__lseek) || defined(__CRT_HAVE___lseek)) && (defined(__CRT_HAVE_read) || defined(__CRT_HAVE__read) || defined(__CRT_HAVE___read)) && defined(__SEEK_CUR) && defined(__SEEK_SET))
__NAMESPACE_LOCAL_END
#include <libc/local/unistd/pread64.h>
__NAMESPACE_LOCAL_BEGIN
/* >> pread64(2)
 * Read data from a file at a specific offset */
#define __localdep_pread64 __LIBC_LOCAL_NAME(pread64)
#else /* ... */
#undef __local___localdep_pread64_defined
#endif /* !... */
#endif /* !__local___localdep_pread64_defined */
/* Dependency: read from unistd */
#ifndef __local___localdep_read_defined
#define __local___localdep_read_defined 1
#ifdef __CRT_HAVE_read
/* >> read(2)
 * Read data from a given file descriptor `FD' and return the number of bytes read.
 * A return value of ZERO(0) is indicative of EOF */
__CREDIRECT(__ATTR_NONNULL((2)),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_read,(__fd_t __fd, void *__buf, __SIZE_TYPE__ __bufsize),read,(__fd,__buf,__bufsize))
#elif defined(__CRT_HAVE__read)
/* >> read(2)
 * Read data from a given file descriptor `FD' and return the number of bytes read.
 * A return value of ZERO(0) is indicative of EOF */
__CREDIRECT(__ATTR_NONNULL((2)),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_read,(__fd_t __fd, void *__buf, __SIZE_TYPE__ __bufsize),_read,(__fd,__buf,__bufsize))
#elif defined(__CRT_HAVE___read)
/* >> read(2)
 * Read data from a given file descriptor `FD' and return the number of bytes read.
 * A return value of ZERO(0) is indicative of EOF */
__CREDIRECT(__ATTR_NONNULL((2)),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_read,(__fd_t __fd, void *__buf, __SIZE_TYPE__ __bufsize),__read,(__fd,__buf,__bufsize))
#else /* ... */
#undef __local___localdep_read_defined
#endif /* !... */
#endif /* !__local___localdep_read_defined */
/* >> pread(2)
 * Read data from a file at a specific offset */
__LOCAL_LIBC(pread) __ATTR_NONNULL((2)) __SSIZE_TYPE__
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(pread))(__fd_t __fd, void *__buf, __SIZE_TYPE__ __bufsize, __PIO_OFFSET __offset) {

	return __localdep_pread64(__fd, __buf, __bufsize, (__PIO_OFFSET64)__offset);













}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_pread_defined
#define __local___localdep_pread_defined 1
#define __localdep_pread __LIBC_LOCAL_NAME(pread)
#endif /* !__local___localdep_pread_defined */
#else /* __CRT_HAVE_pread64 || __CRT_HAVE___pread64 || __CRT_HAVE_pread || ((__CRT_HAVE_lseek64 || __CRT_HAVE__lseeki64 || __CRT_HAVE_lseek || __CRT_HAVE__lseek || __CRT_HAVE___lseek) && (__CRT_HAVE_read || __CRT_HAVE__read || __CRT_HAVE___read) && __SEEK_CUR && __SEEK_SET) */
#undef __local_pread_defined
#endif /* !__CRT_HAVE_pread64 && !__CRT_HAVE___pread64 && !__CRT_HAVE_pread && ((!__CRT_HAVE_lseek64 && !__CRT_HAVE__lseeki64 && !__CRT_HAVE_lseek && !__CRT_HAVE__lseek && !__CRT_HAVE___lseek) || (!__CRT_HAVE_read && !__CRT_HAVE__read && !__CRT_HAVE___read) || !__SEEK_CUR || !__SEEK_SET) */
#endif /* !__local_pread_defined */
