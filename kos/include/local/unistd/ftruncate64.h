/* HASH CRC-32:0x741a54ae */
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
#ifndef __local_ftruncate64_defined
#define __local_ftruncate64_defined 1
#include <__crt.h>
#ifdef __CRT_HAVE_ftruncate
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
/* Dependency: ftruncate32 from unistd */
#ifndef __local___localdep_ftruncate32_defined
#define __local___localdep_ftruncate32_defined 1
/* >> ftruncate(2)
 * Truncate the given file `FD' to a length of `LENGTH' */
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_ftruncate32,(__fd_t __fd, __pos32_t __length),ftruncate,(__fd,__length))
#endif /* !__local___localdep_ftruncate32_defined */
/* >> ftruncate64(2)
 * Truncate the given file `FD' to a length of `LENGTH' */
__LOCAL_LIBC(ftruncate64) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(ftruncate64))(__fd_t __fd, __PIO_OFFSET64 __length) {
	return __localdep_ftruncate32(__fd, (__pos32_t)__length);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_ftruncate64_defined
#define __local___localdep_ftruncate64_defined 1
#define __localdep_ftruncate64 __LIBC_LOCAL_NAME(ftruncate64)
#endif /* !__local___localdep_ftruncate64_defined */
#else /* __CRT_HAVE_ftruncate */
#undef __local_ftruncate64_defined
#endif /* !__CRT_HAVE_ftruncate */
#endif /* !__local_ftruncate64_defined */
