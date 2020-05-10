/* HASH CRC-32:0x2264715 */
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
#ifndef __local_pread64_defined
#if defined(__CRT_HAVE_pread) || ((defined(__CRT_HAVE_read) || defined(__CRT_HAVE__read)) && (defined(__CRT_HAVE_lseek) || defined(__CRT_HAVE_lseek64) || defined(__CRT_HAVE__lseek) || defined(__CRT_HAVE___lseek) || defined(__CRT_HAVE__lseeki64)))
#define __local_pread64_defined 1
#include <__crt.h>
/* Dependency: "pread32" from "unistd" */
#ifndef ____localdep_pread32_defined
#define ____localdep_pread32_defined 1
#ifdef __CRT_HAVE_pread
__CREDIRECT(__ATTR_NONNULL((2)),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_pread32,(__fd_t __fd, void *__buf, __SIZE_TYPE__ __bufsize, __pos32_t __offset),pread,(__fd,__buf,__bufsize,__offset))
#else /* LIBC: pread */
#undef ____localdep_pread32_defined
#endif /* pread32... */
#endif /* !____localdep_pread32_defined */

/* Dependency: "lseek64" from "unistd" */
#ifndef ____localdep_lseek64_defined
#define ____localdep_lseek64_defined 1
#ifdef __CRT_HAVE_lseek64
/* >> lseek64(2)
 * Change the position of the file read/write pointer within a file referred to by `FD' */
__CREDIRECT(,__off64_t,__NOTHROW_NCX,__localdep_lseek64,(__fd_t __fd, __off64_t __offset, int __whence),lseek64,(__fd,__offset,__whence))
#elif defined(__CRT_HAVE_lseek) && (__SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> lseek64(2)
 * Change the position of the file read/write pointer within a file referred to by `FD' */
__CREDIRECT(,__off64_t,__NOTHROW_NCX,__localdep_lseek64,(__fd_t __fd, __off64_t __offset, int __whence),lseek,(__fd,__offset,__whence))
#elif defined(__CRT_HAVE__lseeki64)
/* >> lseek64(2)
 * Change the position of the file read/write pointer within a file referred to by `FD' */
__CREDIRECT(,__off64_t,__NOTHROW_NCX,__localdep_lseek64,(__fd_t __fd, __off64_t __offset, int __whence),_lseeki64,(__fd,__offset,__whence))
#elif defined(__CRT_HAVE_lseek) || defined(__CRT_HAVE__lseek) || defined(__CRT_HAVE___lseek)
#include <local/unistd/lseek64.h>
/* >> lseek64(2)
 * Change the position of the file read/write pointer within a file referred to by `FD' */
#define __localdep_lseek64 (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(lseek64))
#else /* CUSTOM: lseek64 */
#undef ____localdep_lseek64_defined
#endif /* lseek64... */
#endif /* !____localdep_lseek64_defined */

/* Dependency: "read" */
#ifndef ____localdep_read_defined
#define ____localdep_read_defined 1
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
#else /* LIBC: read */
#undef ____localdep_read_defined
#endif /* read... */
#endif /* !____localdep_read_defined */

/* Dependency: "lseek32" from "unistd" */
#ifndef ____localdep_lseek32_defined
#define ____localdep_lseek32_defined 1
#ifdef __CRT_HAVE_lseek
/* >> lseek32(2)
 * Change the position of the file read/write pointer within a file referred to by `FD' */
__CREDIRECT(,__off32_t,__NOTHROW_NCX,__localdep_lseek32,(__fd_t __fd, __off32_t __offset, int __whence),lseek,(__fd,__offset,__whence))
#elif defined(__CRT_HAVE__lseek)
/* >> lseek32(2)
 * Change the position of the file read/write pointer within a file referred to by `FD' */
__CREDIRECT(,__off32_t,__NOTHROW_NCX,__localdep_lseek32,(__fd_t __fd, __off32_t __offset, int __whence),_lseek,(__fd,__offset,__whence))
#elif defined(__CRT_HAVE___lseek)
/* >> lseek32(2)
 * Change the position of the file read/write pointer within a file referred to by `FD' */
__CREDIRECT(,__off32_t,__NOTHROW_NCX,__localdep_lseek32,(__fd_t __fd, __off32_t __offset, int __whence),__lseek,(__fd,__offset,__whence))
#else /* LIBC: lseek */
#undef ____localdep_lseek32_defined
#endif /* lseek32... */
#endif /* !____localdep_lseek32_defined */

__NAMESPACE_LOCAL_BEGIN
/* >> pread64(2)
 * Read data from a file at a specific offset */
__LOCAL_LIBC(pread64) __ATTR_NONNULL((2)) __SSIZE_TYPE__
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(pread64))(__fd_t __fd,
                                                     void *__buf,
                                                     __SIZE_TYPE__ __bufsize,
                                                     __PIO_OFFSET64 __offset) {
#line 975 "kos/src/libc/magic/unistd.c"
#if defined(__CRT_HAVE_pread) && ((!defined(__CRT_HAVE__lseeki64) && !defined(__CRT_HAVE_lseek64)) || (!defined(__CRT_HAVE_read) && !defined(__CRT_HAVE__read)))
	return __localdep_pread32(__fd, __buf, __bufsize, (__pos32_t)__offset);
#elif defined(__CRT_HAVE__lseeki64) || defined(__CRT_HAVE_lseek64)
	/* It may not be quick, and it may not be SMP-safe, but it'll still do the job! */
	__off64_t __oldpos;
	__SSIZE_TYPE__ __result;
	__oldpos = __localdep_lseek64(__fd, 0, __SEEK_CUR);
	if __unlikely(__oldpos < 0)
		return -1;
	if __unlikely(__localdep_lseek64(__fd, (__off64_t)__offset, __SEEK_SET) < 0)
		return -1;
	__result = __localdep_read(__fd, __buf, __bufsize);
	__localdep_lseek64(__fd, __oldpos, __SEEK_SET);
	return __result;
#else
	/* It may not be quick, and it may not be SMP-safe, but it'll still do the job! */
	__off32_t __oldpos;
	__SSIZE_TYPE__ __result;
	__oldpos = __localdep_lseek32(__fd, 0, __SEEK_CUR);
	if __unlikely(__oldpos < 0)
		return -1;
	if __unlikely(__localdep_lseek32(__fd, (__off32_t)__offset, __SEEK_SET) < 0)
		return -1;
	__result = __localdep_read(__fd, __buf, __bufsize);
	__localdep_lseek32(__fd, __oldpos, __SEEK_SET);
	return __result;
#endif
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE_pread || ((__CRT_HAVE_read || __CRT_HAVE__read) && (__CRT_HAVE_lseek || __CRT_HAVE_lseek64 || __CRT_HAVE__lseek || __CRT_HAVE___lseek || __CRT_HAVE__lseeki64)) */
#endif /* !__local_pread64_defined */
