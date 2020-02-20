/* HASH CRC-32:0xb503fc04 */
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
#ifndef __local_pwrite_defined
#if defined(__CRT_HAVE_pwrite64) || ((defined(__CRT_HAVE_write) || defined(__CRT_HAVE__write)) && (defined(__CRT_HAVE_lseek) || defined(__CRT_HAVE_lseek64) || defined(__CRT_HAVE__lseek) || defined(__CRT_HAVE___lseek) || defined(__CRT_HAVE__lseeki64)))
#define __local_pwrite_defined 1
/* Dependency: "pwrite64" from "unistd" */
#ifndef ____localdep_pwrite64_defined
#define ____localdep_pwrite64_defined 1
#ifdef __CRT_HAVE_pwrite64
/* >> pwrite64(2)
 * Write data to a file at a specific offset */
__CREDIRECT(__ATTR_NONNULL((2)),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_pwrite64,(__fd_t __fd, void const *__buf, __SIZE_TYPE__ __bufsize, __PIO_OFFSET64 __offset),pwrite64,(__fd,__buf,__bufsize,__offset))
#elif defined(__CRT_HAVE_pwrite) && (__SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> pwrite64(2)
 * Write data to a file at a specific offset */
__CREDIRECT(__ATTR_NONNULL((2)),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_pwrite64,(__fd_t __fd, void const *__buf, __SIZE_TYPE__ __bufsize, __PIO_OFFSET64 __offset),pwrite,(__fd,__buf,__bufsize,__offset))
#elif defined(__CRT_HAVE___pwrite64)
/* >> pwrite64(2)
 * Write data to a file at a specific offset */
__CREDIRECT(__ATTR_NONNULL((2)),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_pwrite64,(__fd_t __fd, void const *__buf, __SIZE_TYPE__ __bufsize, __PIO_OFFSET64 __offset),__pwrite64,(__fd,__buf,__bufsize,__offset))
#elif defined(__CRT_HAVE_pread) || ((defined(__CRT_HAVE_write) || defined(__CRT_HAVE__write)) && (defined(__CRT_HAVE_lseek) || defined(__CRT_HAVE_lseek64) || defined(__CRT_HAVE__lseek) || defined(__CRT_HAVE___lseek) || defined(__CRT_HAVE__lseeki64)))
#include <local/unistd/pwrite64.h>
/* >> pwrite64(2)
 * Write data to a file at a specific offset */
#define __localdep_pwrite64 (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pwrite64))
#else /* CUSTOM: pwrite64 */
#undef ____localdep_pwrite64_defined
#endif /* pwrite64... */
#endif /* !____localdep_pwrite64_defined */

/* Dependency: "lseek" from "unistd" */
#ifndef ____localdep_lseek_defined
#define ____localdep_lseek_defined 1
#if defined(__CRT_HAVE_lseek64) && defined(__USE_FILE_OFFSET64)
/* >> lseek(2)
 * Change the position of the file read/write pointer within a file referred to by `FD' */
__CREDIRECT(,__off64_t,__NOTHROW_NCX,__localdep_lseek,(__fd_t __fd, __off64_t __offset, int __whence),lseek64,(__fd,__offset,__whence))
#elif defined(__CRT_HAVE__lseeki64) && defined(__USE_FILE_OFFSET64)
/* >> lseek(2)
 * Change the position of the file read/write pointer within a file referred to by `FD' */
__CREDIRECT(,__off64_t,__NOTHROW_NCX,__localdep_lseek,(__fd_t __fd, __off64_t __offset, int __whence),_lseeki64,(__fd,__offset,__whence))
#elif defined(__CRT_HAVE_lseek) && !defined(__USE_FILE_OFFSET64)
/* >> lseek(2)
 * Change the position of the file read/write pointer within a file referred to by `FD' */
__CREDIRECT(,__off32_t,__NOTHROW_NCX,__localdep_lseek,(__fd_t __fd, __off32_t __offset, int __whence),lseek,(__fd,__offset,__whence))
#elif defined(__CRT_HAVE__lseek) && !defined(__USE_FILE_OFFSET64)
/* >> lseek(2)
 * Change the position of the file read/write pointer within a file referred to by `FD' */
__CREDIRECT(,__off32_t,__NOTHROW_NCX,__localdep_lseek,(__fd_t __fd, __off32_t __offset, int __whence),_lseek,(__fd,__offset,__whence))
#elif defined(__CRT_HAVE___lseek) && !defined(__USE_FILE_OFFSET64)
/* >> lseek(2)
 * Change the position of the file read/write pointer within a file referred to by `FD' */
__CREDIRECT(,__off32_t,__NOTHROW_NCX,__localdep_lseek,(__fd_t __fd, __off32_t __offset, int __whence),__lseek,(__fd,__offset,__whence))
#elif defined(__CRT_HAVE_lseek64) || defined(__CRT_HAVE__lseeki64) || defined(__CRT_HAVE_lseek) || defined(__CRT_HAVE__lseek) || defined(__CRT_HAVE___lseek)
#include <local/unistd/lseek.h>
/* >> lseek(2)
 * Change the position of the file read/write pointer within a file referred to by `FD' */
#define __localdep_lseek (*(__FS_TYPE(off)(__LIBCCALL*)(__fd_t, __off32_t, int))&(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(lseek)))
#else /* CUSTOM: lseek */
#undef ____localdep_lseek_defined
#endif /* lseek... */
#endif /* !____localdep_lseek_defined */

/* Dependency: "write" */
#ifndef ____localdep_write_defined
#define ____localdep_write_defined 1
#ifdef __CRT_HAVE_write
/* >> write(2)
 * Write data to a given file descriptor `FD' and return the number of bytes written */
__CREDIRECT(__ATTR_NONNULL((2)),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_write,(__fd_t __fd, void const *__buf, __SIZE_TYPE__ __bufsize),write,(__fd,__buf,__bufsize))
#elif defined(__CRT_HAVE__write)
/* >> write(2)
 * Write data to a given file descriptor `FD' and return the number of bytes written */
__CREDIRECT(__ATTR_NONNULL((2)),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_write,(__fd_t __fd, void const *__buf, __SIZE_TYPE__ __bufsize),_write,(__fd,__buf,__bufsize))
#elif defined(__CRT_HAVE___write)
/* >> write(2)
 * Write data to a given file descriptor `FD' and return the number of bytes written */
__CREDIRECT(__ATTR_NONNULL((2)),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_write,(__fd_t __fd, void const *__buf, __SIZE_TYPE__ __bufsize),__write,(__fd,__buf,__bufsize))
#else /* LIBC: write */
#undef ____localdep_write_defined
#endif /* write... */
#endif /* !____localdep_write_defined */

__NAMESPACE_LOCAL_BEGIN
#ifndef __PIO_OFFSET
#ifdef __USE_KOS
#define __PIO_OFFSET     __FS_TYPE(pos)
#define __PIO_OFFSET64   __pos64_t
#else
#define __PIO_OFFSET     __FS_TYPE(off)
#define __PIO_OFFSET64   __off64_t
#endif
#endif /* !__PIO_OFFSET */

#ifndef 0
#   define 0  0 /* Seek from beginning of file.  */
#   define 1  1 /* Seek from current position.  */
#   define 2  2 /* Seek from end of file.  */
#if defined(__USE_GNU) && (defined(__CRT_KOS) || defined(__CRT_GLC))
#   define SEEK_DATA 3 /* Seek to next data.  */
#   define SEEK_HOLE 4 /* Seek to next hole.  */
#endif /* __USE_GNU && (__CRT_KOS || __CRT_GLC) */
#endif
/* >> pwrite(2)
 * Write data to a file at a specific offset */
__LOCAL_LIBC(pwrite) __ATTR_NONNULL((2)) __SSIZE_TYPE__
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(pwrite))(__fd_t __fd,
                                                    void const *__buf,
                                                    __SIZE_TYPE__ __bufsize,
                                                    __PIO_OFFSET __offset) {
#line 902 "kos/src/libc/magic/unistd.c"
#ifdef __CRT_HAVE_pwrite64
	return __localdep_pwrite64(__fd, __buf, __bufsize, (__PIO_OFFSET64)__offset);
#else
	/* It may not be quick, and it may not be SMP-safe, but it'll still do the job! */
	__FS_TYPE(off) __oldpos;
	__SSIZE_TYPE__ __result;
	__oldpos = __localdep_lseek(__fd, 0, 1);
	if __unlikely(__oldpos < 0)
		return -1;
	if __unlikely(__localdep_lseek(__fd, (__FS_TYPE(off))__offset, 0) < 0)
		return -1;
	__result = __localdep_write(__fd, __buf, __bufsize);
	__localdep_lseek(__fd, __oldpos, 0);
	return __result;
#endif
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE_pwrite64 || ((__CRT_HAVE_write || __CRT_HAVE__write) && (__CRT_HAVE_lseek || __CRT_HAVE_lseek64 || __CRT_HAVE__lseek || __CRT_HAVE___lseek || __CRT_HAVE__lseeki64)) */
#endif /* !__local_pwrite_defined */
