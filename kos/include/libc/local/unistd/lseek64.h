/* HASH CRC-32:0xab8e9df2 */
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
#ifndef __local_lseek64_defined
#define __local_lseek64_defined 1
#include <__crt.h>
#if defined(__CRT_HAVE_lseek) || defined(__CRT_HAVE__lseek) || defined(__CRT_HAVE___lseek)
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_lseek32_defined
#define __local___localdep_lseek32_defined 1
#ifdef __CRT_HAVE_lseek
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(,__off32_t,__NOTHROW_NCX,__localdep_lseek32,(__fd_t __fd, __off32_t __offset, __STDC_INT_AS_UINT_T __whence),lseek,(__fd,__offset,__whence))
#elif defined(__CRT_HAVE__lseek)
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(,__off32_t,__NOTHROW_NCX,__localdep_lseek32,(__fd_t __fd, __off32_t __offset, __STDC_INT_AS_UINT_T __whence),_lseek,(__fd,__offset,__whence))
#elif defined(__CRT_HAVE___lseek)
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(,__off32_t,__NOTHROW_NCX,__localdep_lseek32,(__fd_t __fd, __off32_t __offset, __STDC_INT_AS_UINT_T __whence),__lseek,(__fd,__offset,__whence))
#else /* ... */
#undef __local___localdep_lseek32_defined
#endif /* !... */
#endif /* !__local___localdep_lseek32_defined */
__LOCAL_LIBC(lseek64) __off64_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(lseek64))(__fd_t __fd, __off64_t __offset, __STDC_INT_AS_UINT_T __whence) {
	return __NAMESPACE_LOCAL_SYM __localdep_lseek32(__fd, (__off32_t)__offset, __whence);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_lseek64_defined
#define __local___localdep_lseek64_defined 1
#define __localdep_lseek64 __LIBC_LOCAL_NAME(lseek64)
#endif /* !__local___localdep_lseek64_defined */
#else /* __CRT_HAVE_lseek || __CRT_HAVE__lseek || __CRT_HAVE___lseek */
#undef __local_lseek64_defined
#endif /* !__CRT_HAVE_lseek && !__CRT_HAVE__lseek && !__CRT_HAVE___lseek */
#endif /* !__local_lseek64_defined */
