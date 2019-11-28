/* HASH CRC-32:0x535fb096 */
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
#ifndef __local_ReadAll_defined
#if defined(__CRT_HAVE_Read) && (defined(__CRT_HAVE_lseek) || defined(__CRT_HAVE_lseek64) || defined(__CRT_HAVE__lseek) || defined(__CRT_HAVE___lseek) || defined(__CRT_HAVE__lseeki64))
#define __local_ReadAll_defined 1
#include <kos/anno.h>
#include <parts/errno.h>

#include <kos/except.h>
/* Dependency: "Read" */
#ifndef ____localdep_Read_defined
#define ____localdep_Read_defined 1
#ifdef __CRT_HAVE_Read
/* >> read(2)
 * Read data from a given file descriptor `FD' and return the number of bytes read.
 * A return value of ZERO(0) is indicative of EOF */
__CREDIRECT(__ATTR_NONNULL((2)),__SIZE_TYPE__,,__localdep_Read,(__fd_t __fd, void *__buf, __SIZE_TYPE__ __bufsize),Read,(__fd,__buf,__bufsize)) __THROWS(...)
#else /* LIBC: Read */
#undef ____localdep_Read_defined
#endif /* Read... */
#endif /* !____localdep_Read_defined */

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
#elif defined(__CRT_HAVE_lseek) && (!defined(__USE_FILE_OFFSET64))
/* >> lseek(2)
 * Change the position of the file read/write pointer within a file referred to by `FD' */
__CREDIRECT(,__off32_t,__NOTHROW_NCX,__localdep_lseek,(__fd_t __fd, __off32_t __offset, int __whence),lseek,(__fd,__offset,__whence))
#elif defined(__CRT_HAVE__lseek) && (!defined(__USE_FILE_OFFSET64))
/* >> lseek(2)
 * Change the position of the file read/write pointer within a file referred to by `FD' */
__CREDIRECT(,__off32_t,__NOTHROW_NCX,__localdep_lseek,(__fd_t __fd, __off32_t __offset, int __whence),_lseek,(__fd,__offset,__whence))
#elif defined(__CRT_HAVE___lseek) && (!defined(__USE_FILE_OFFSET64))
/* >> lseek(2)
 * Change the position of the file read/write pointer within a file referred to by `FD' */
__CREDIRECT(,__off32_t,__NOTHROW_NCX,__localdep_lseek,(__fd_t __fd, __off32_t __offset, int __whence),__lseek,(__fd,__offset,__whence))
#elif defined(__CRT_HAVE_lseek64) || defined(__CRT_HAVE__lseeki64) || defined(__CRT_HAVE_lseek) || defined(__CRT_HAVE__lseek) || defined(__CRT_HAVE___lseek)
#include <local/unistd/lseek.h>
/* >> lseek(2)
 * Change the position of the file read/write pointer within a file referred to by `FD' */
#define __localdep_lseek(fd, offset, whence) (__FS_TYPE(off))(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(lseek))(fd, (__FS_TYPE(off))(offset), whence)
#else /* CUSTOM: lseek */
#undef ____localdep_lseek_defined
#endif /* lseek... */
#endif /* !____localdep_lseek_defined */

__NAMESPACE_LOCAL_BEGIN
/* >> readall(3)
 * Same as `read(2)', however keep on reading until `read()' indicates EOF (causing
 * `readall()' to immediately return `0') or the entirety of the given buffer has been
 * filled (in which case `bufsize' is returned).
 * If an error occurrs before all data could be read, try to use SEEK_CUR to rewind
 * the file descriptor by the amount of data that had already been loaded. - Errors
 * during this phase are silently ignored and don't cause `errno' to change */
__LOCAL_LIBC(ReadAll) __ATTR_NONNULL((2)) __SIZE_TYPE__
(__LIBCCALL __LIBC_LOCAL_NAME(ReadAll))(__fd_t __fd,
                                        void *__buf,
                                        __SIZE_TYPE__ __bufsize) __THROWS(...) {
#line 161 "kos/src/libc/magic/kos.unistd.c"
	__SIZE_TYPE__ __result, __temp;
	__result = __localdep_Read(__fd, __buf, __bufsize);
	if (__result != 0 && __result < __bufsize) {
		/* Keep on reading */
		for (;;) {
			TRY {
				__temp = __localdep_Read(__fd,
				           (__BYTE_TYPE__ *)__buf + (__SIZE_TYPE__)__result,
				            __bufsize - (__SIZE_TYPE__)__result);
			} EXCEPT {
#ifdef __errno
				int __old_error = __errno;
#endif
				/* Try to un-read data that had already been loaded. */
				__localdep_lseek(__fd, -(__FS_TYPE(off))(__FS_TYPE(pos))__result, 1);
#ifdef __errno
				__errno = __old_error;
#endif
				RETHROW();
			}
			if (!__temp) {
				__result = 0;
				break;
			}
			__result += __temp;
			if (__result >= __bufsize)
				break;
		}
	}
	return __result;
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE_Read && (__CRT_HAVE_lseek || __CRT_HAVE_lseek64 || __CRT_HAVE__lseek || __CRT_HAVE___lseek || __CRT_HAVE__lseeki64) */
#endif /* !__local_ReadAll_defined */
