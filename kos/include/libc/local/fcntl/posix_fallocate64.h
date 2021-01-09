/* HASH CRC-32:0xfb570294 */
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
#ifndef __local_posix_fallocate64_defined
#define __local_posix_fallocate64_defined 1
#include <__crt.h>
#include <bits/types.h>
#include <features.h>
#ifndef __PIO_OFFSET
#ifdef __USE_KOS_ALTERATIONS
#define __PIO_OFFSET   __FS_TYPE(__pos)
#define __PIO_OFFSET64 __pos64_t
#else /* __USE_KOS_ALTERATIONS */
#define __PIO_OFFSET   __FS_TYPE(__off)
#define __PIO_OFFSET64 __off64_t
#endif /* !__USE_KOS_ALTERATIONS */
#endif /* !__PIO_OFFSET */
__NAMESPACE_LOCAL_BEGIN
/* Dependency: posix_fallocate32 from fcntl */
#if !defined(__local___localdep_posix_fallocate32_defined) && defined(__CRT_HAVE_posix_fallocate)
#define __local___localdep_posix_fallocate32_defined 1
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_posix_fallocate32,(__fd_t __fd, __pos32_t __offset, __pos32_t __length),posix_fallocate,(__fd,__offset,__length))
#endif /* !__local___localdep_posix_fallocate32_defined && __CRT_HAVE_posix_fallocate */
__LOCAL_LIBC(posix_fallocate64) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(posix_fallocate64))(__fd_t __fd, __PIO_OFFSET64 __offset, __PIO_OFFSET64 __length) {
#ifdef __CRT_HAVE_posix_fallocate
	return __localdep_posix_fallocate32(__fd, (__pos32_t)__offset, (__pos32_t)__length);
#else /* __CRT_HAVE_posix_fallocate */
	(void)__fd;
	(void)__offset;
	(void)__length;
	return 0;
#endif /* !__CRT_HAVE_posix_fallocate */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_posix_fallocate64_defined
#define __local___localdep_posix_fallocate64_defined 1
#define __localdep_posix_fallocate64 __LIBC_LOCAL_NAME(posix_fallocate64)
#endif /* !__local___localdep_posix_fallocate64_defined */
#endif /* !__local_posix_fallocate64_defined */
