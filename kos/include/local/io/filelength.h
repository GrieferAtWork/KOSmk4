/* HASH CRC-32:0x600f0e6 */
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
#ifndef __local_filelength_defined
#define __local_filelength_defined 1
#include <__crt.h>
#if defined(__CRT_HAVE_lseek) || defined(__CRT_HAVE__lseek) || defined(__CRT_HAVE___lseek) || defined(__CRT_HAVE_lseek64) || defined(__CRT_HAVE__lseeki64)
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: lseek from unistd */
#ifndef __local___localdep_lseek_defined
#define __local___localdep_lseek_defined 1
#ifdef __lseek_defined
/* >> lseek(2)
 * Change the position of the file read/write pointer within a file referred to by `FD' */
__NAMESPACE_GLB_USING(lseek)
#define __localdep_lseek lseek
#elif defined(__CRT_HAVE_lseek64) && defined(__USE_FILE_OFFSET64)
/* >> lseek(2)
 * Change the position of the file read/write pointer within a file referred to by `FD' */
__CREDIRECT(,__FS_TYPE(off),__NOTHROW_NCX,__localdep_lseek,(__fd_t __fd, __FS_TYPE(off) __offset, int __whence),lseek64,(__fd,__offset,__whence))
#elif defined(__CRT_HAVE__lseeki64) && defined(__USE_FILE_OFFSET64)
/* >> lseek(2)
 * Change the position of the file read/write pointer within a file referred to by `FD' */
__CREDIRECT(,__FS_TYPE(off),__NOTHROW_NCX,__localdep_lseek,(__fd_t __fd, __FS_TYPE(off) __offset, int __whence),_lseeki64,(__fd,__offset,__whence))
#elif defined(__CRT_HAVE_lseek) && !defined(__USE_FILE_OFFSET64)
/* >> lseek(2)
 * Change the position of the file read/write pointer within a file referred to by `FD' */
__CREDIRECT(,__FS_TYPE(off),__NOTHROW_NCX,__localdep_lseek,(__fd_t __fd, __FS_TYPE(off) __offset, int __whence),lseek,(__fd,__offset,__whence))
#elif defined(__CRT_HAVE__lseek) && !defined(__USE_FILE_OFFSET64)
/* >> lseek(2)
 * Change the position of the file read/write pointer within a file referred to by `FD' */
__CREDIRECT(,__FS_TYPE(off),__NOTHROW_NCX,__localdep_lseek,(__fd_t __fd, __FS_TYPE(off) __offset, int __whence),_lseek,(__fd,__offset,__whence))
#elif defined(__CRT_HAVE___lseek) && !defined(__USE_FILE_OFFSET64)
/* >> lseek(2)
 * Change the position of the file read/write pointer within a file referred to by `FD' */
__CREDIRECT(,__FS_TYPE(off),__NOTHROW_NCX,__localdep_lseek,(__fd_t __fd, __FS_TYPE(off) __offset, int __whence),__lseek,(__fd,__offset,__whence))
#elif defined(__CRT_HAVE_lseek) || defined(__CRT_HAVE__lseek) || defined(__CRT_HAVE___lseek) || defined(__CRT_HAVE_lseek64) || defined(__CRT_HAVE__lseeki64)
__NAMESPACE_LOCAL_END
#include <local/unistd/lseek.h>
__NAMESPACE_LOCAL_BEGIN
/* >> lseek(2)
 * Change the position of the file read/write pointer within a file referred to by `FD' */
#define __localdep_lseek __LIBC_LOCAL_NAME(lseek)
#else /* ... */
#undef __local___localdep_lseek_defined
#endif /* !... */
#endif /* !__local___localdep_lseek_defined */
__LOCAL_LIBC(filelength) __ATTR_WUNUSED __LONG32_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(filelength))(__fd_t __fd) {
	__LONG32_TYPE__ __oldpos, __result;
	__oldpos = __localdep_lseek(__fd, 0, __SEEK_CUR);
	if __unlikely(__oldpos < 0)
		return -1;
	__result = __localdep_lseek(__fd, 0, __SEEK_END);
	if __likely(__result >= 0)
		__localdep_lseek(__fd, __oldpos, __SEEK_SET);
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_filelength_defined
#define __local___localdep_filelength_defined 1
#define __localdep_filelength __LIBC_LOCAL_NAME(filelength)
#endif /* !__local___localdep_filelength_defined */
#else /* __CRT_HAVE_lseek || __CRT_HAVE__lseek || __CRT_HAVE___lseek || __CRT_HAVE_lseek64 || __CRT_HAVE__lseeki64 */
#undef __local_filelength_defined
#endif /* !__CRT_HAVE_lseek && !__CRT_HAVE__lseek && !__CRT_HAVE___lseek && !__CRT_HAVE_lseek64 && !__CRT_HAVE__lseeki64 */
#endif /* !__local_filelength_defined */
