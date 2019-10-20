/* HASH CRC-32:0xf86105a1 */
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
#ifndef __local_lseek_defined
#if (defined(__CRT_HAVE_lseek64) || defined(__CRT_HAVE__lseeki64) || defined(__CRT_HAVE_lseek) || defined(__CRT_HAVE__lseek))
#define __local_lseek_defined 1
/* Dependency: "lseek32" from "unistd" */
#ifndef ____localdep_lseek32_defined
#define ____localdep_lseek32_defined 1
#if defined(__CRT_HAVE_lseek)
/* >> lseek32(2)
 * Change the position of the file read/write pointer within a file referred to by `FD' */
__CREDIRECT(,__off32_t,__NOTHROW_NCX,__localdep_lseek32,(__fd_t __fd, __off32_t __offset, int __whence),lseek,(__fd,__offset,__whence))
#elif defined(__CRT_HAVE__lseek)
/* >> lseek32(2)
 * Change the position of the file read/write pointer within a file referred to by `FD' */
__CREDIRECT(,__off32_t,__NOTHROW_NCX,__localdep_lseek32,(__fd_t __fd, __off32_t __offset, int __whence),_lseek,(__fd,__offset,__whence))
#else /* LIBC: lseek */
#undef ____localdep_lseek32_defined
#endif /* lseek32... */
#endif /* !____localdep_lseek32_defined */

/* Dependency: "lseek64" from "unistd" */
#ifndef ____localdep_lseek64_defined
#define ____localdep_lseek64_defined 1
#if defined(__CRT_HAVE_lseek64)
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
#elif defined(__CRT_HAVE_lseek) || defined(__CRT_HAVE__lseek)
#include <local/unistd/lseek64.h>
/* >> lseek64(2)
 * Change the position of the file read/write pointer within a file referred to by `FD' */
#define __localdep_lseek64 (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(lseek64))
#else /* CUSTOM: lseek64 */
#undef ____localdep_lseek64_defined
#endif /* lseek64... */
#endif /* !____localdep_lseek64_defined */

__NAMESPACE_LOCAL_BEGIN
/* >> lseek(2)
 * Change the position of the file read/write pointer within a file referred to by `FD' */
__LOCAL_LIBC(lseek) __FS_TYPE(off)
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(lseek))(__fd_t __fd,
                                                   __FS_TYPE(off) __offset,
                                                   int __whence) {
#line 637 "kos/src/libc/magic/unistd.c"
#if defined(__CRT_HAVE_lseek) || defined(__CRT_HAVE__lseek)
	return __localdep_lseek32(__fd, (__off32_t)__offset, __whence);
#else
	return __localdep_lseek64(__fd, (__off64_t)__offset, __whence);
#endif
}
__NAMESPACE_LOCAL_END
#endif /* (defined(__CRT_HAVE_lseek64) || defined(__CRT_HAVE__lseeki64) || defined(__CRT_HAVE_lseek) || defined(__CRT_HAVE__lseek)) */
#endif /* !__local_lseek_defined */
