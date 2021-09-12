/* HASH CRC-32:0x29da2088 */
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
#ifndef __local_posix_fallocate_defined
#define __local_posix_fallocate_defined 1
#include <__crt.h>
#include <features.h>
#include <bits/types.h>
#ifndef __PIO_OFFSET
#ifdef __USE_KOS_ALTERATIONS
#define __PIO_OFFSET   __FS_TYPE(pos)
#define __PIO_OFFSET64 __pos64_t
#else /* __USE_KOS_ALTERATIONS */
#define __PIO_OFFSET   __FS_TYPE(off)
#define __PIO_OFFSET64 __off64_t
#endif /* !__USE_KOS_ALTERATIONS */
#endif /* !__PIO_OFFSET */
__NAMESPACE_LOCAL_BEGIN
#if !defined(__local___localdep_posix_fallocate32_defined) && defined(__CRT_HAVE_posix_fallocate)
#define __local___localdep_posix_fallocate32_defined 1
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_posix_fallocate32,(__fd_t __fd, __pos32_t __offset, __pos32_t __length),posix_fallocate,(__fd,__offset,__length))
#endif /* !__local___localdep_posix_fallocate32_defined && __CRT_HAVE_posix_fallocate */
#ifndef __local___localdep_posix_fallocate64_defined
#define __local___localdep_posix_fallocate64_defined 1
#ifdef __CRT_HAVE_posix_fallocate64
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_posix_fallocate64,(__fd_t __fd, __PIO_OFFSET64 __offset, __PIO_OFFSET64 __length),posix_fallocate64,(__fd,__offset,__length))
#elif defined(__CRT_HAVE_posix_fallocate) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_posix_fallocate64,(__fd_t __fd, __PIO_OFFSET64 __offset, __PIO_OFFSET64 __length),posix_fallocate,(__fd,__offset,__length))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/fcntl/posix_fallocate64.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_posix_fallocate64 __LIBC_LOCAL_NAME(posix_fallocate64)
#endif /* !... */
#endif /* !__local___localdep_posix_fallocate64_defined */
__LOCAL_LIBC(posix_fallocate) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(posix_fallocate))(__fd_t __fd, __PIO_OFFSET __offset, __PIO_OFFSET __length) {

	return __NAMESPACE_LOCAL_SYM __localdep_posix_fallocate64(__fd, (__PIO_OFFSET64)__offset, (__PIO_OFFSET64)__length);








}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_posix_fallocate_defined
#define __local___localdep_posix_fallocate_defined 1
#define __localdep_posix_fallocate __LIBC_LOCAL_NAME(posix_fallocate)
#endif /* !__local___localdep_posix_fallocate_defined */
#endif /* !__local_posix_fallocate_defined */
