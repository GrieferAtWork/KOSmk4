/* HASH CRC-32:0xa9291bde */
/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local__filelengthi64_defined
#define __local__filelengthi64_defined 1
#include <__crt.h>
#include <asm/os/stdio.h>
#if (defined(__CRT_HAVE_lseek64) || defined(__CRT_HAVE__lseeki64) || defined(__CRT_HAVE_lseek) || defined(__CRT_HAVE__lseek) || defined(__CRT_HAVE___lseek)) && defined(__SEEK_CUR) && defined(__SEEK_END) && defined(__SEEK_SET)
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: lseek64 from unistd */
#ifndef __local___localdep_lseek64_defined
#define __local___localdep_lseek64_defined 1
#ifdef __CRT_HAVE_lseek64
/* >> lseek64(2)
 * Change the position of the file read/write pointer within a file referred to by `fd' */
__CREDIRECT(,__off64_t,__NOTHROW_NCX,__localdep_lseek64,(__fd_t __fd, __off64_t __offset, __STDC_INT_AS_UINT_T __whence),lseek64,(__fd,__offset,__whence))
#elif defined(__CRT_HAVE_lseek) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
/* >> lseek64(2)
 * Change the position of the file read/write pointer within a file referred to by `fd' */
__CREDIRECT(,__off64_t,__NOTHROW_NCX,__localdep_lseek64,(__fd_t __fd, __off64_t __offset, __STDC_INT_AS_UINT_T __whence),lseek,(__fd,__offset,__whence))
#elif defined(__CRT_HAVE__lseeki64)
/* >> lseek64(2)
 * Change the position of the file read/write pointer within a file referred to by `fd' */
__CREDIRECT(,__off64_t,__NOTHROW_NCX,__localdep_lseek64,(__fd_t __fd, __off64_t __offset, __STDC_INT_AS_UINT_T __whence),_lseeki64,(__fd,__offset,__whence))
#elif defined(__CRT_HAVE_lseek) || defined(__CRT_HAVE__lseek) || defined(__CRT_HAVE___lseek)
__NAMESPACE_LOCAL_END
#include <libc/local/unistd/lseek64.h>
__NAMESPACE_LOCAL_BEGIN
/* >> lseek64(2)
 * Change the position of the file read/write pointer within a file referred to by `fd' */
#define __localdep_lseek64 __LIBC_LOCAL_NAME(lseek64)
#else /* ... */
#undef __local___localdep_lseek64_defined
#endif /* !... */
#endif /* !__local___localdep_lseek64_defined */
__LOCAL_LIBC(_filelengthi64) __ATTR_WUNUSED __INT64_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_filelengthi64))(__fd_t __fd) {
	__INT64_TYPE__ __oldpos, __result;
	__oldpos = __localdep_lseek64(__fd, 0, __SEEK_CUR);
	if __unlikely(__oldpos < 0)
		return -1;
	__result = __localdep_lseek64(__fd, 0, __SEEK_END);
	if __likely(__result >= 0)
		__localdep_lseek64(__fd, __oldpos, __SEEK_SET);
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__filelengthi64_defined
#define __local___localdep__filelengthi64_defined 1
#define __localdep__filelengthi64 __LIBC_LOCAL_NAME(_filelengthi64)
#endif /* !__local___localdep__filelengthi64_defined */
#else /* (__CRT_HAVE_lseek64 || __CRT_HAVE__lseeki64 || __CRT_HAVE_lseek || __CRT_HAVE__lseek || __CRT_HAVE___lseek) && __SEEK_CUR && __SEEK_END && __SEEK_SET */
#undef __local__filelengthi64_defined
#endif /* (!__CRT_HAVE_lseek64 && !__CRT_HAVE__lseeki64 && !__CRT_HAVE_lseek && !__CRT_HAVE__lseek && !__CRT_HAVE___lseek) || !__SEEK_CUR || !__SEEK_END || !__SEEK_SET */
#endif /* !__local__filelengthi64_defined */
