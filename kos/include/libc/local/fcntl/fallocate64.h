/* HASH CRC-32:0x1f2a62fc */
/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_fallocate64_defined
#define __local_fallocate64_defined
#include <__crt.h>
#include <features.h>
#include <bits/types.h>
#ifndef __PIO_OFFSET
#ifdef __USE_KOS_ALTERATIONS
#define __PIO_OFFSET   __pos_t
#define __PIO_OFFSET64 __pos64_t
#else /* __USE_KOS_ALTERATIONS */
#define __PIO_OFFSET   __off_t
#define __PIO_OFFSET64 __off64_t
#endif /* !__USE_KOS_ALTERATIONS */
#endif /* !__PIO_OFFSET */
__NAMESPACE_LOCAL_BEGIN
#if !defined(__local___localdep_fallocate32_defined) && defined(__CRT_HAVE_fallocate)
#define __local___localdep_fallocate32_defined
__CREDIRECT(__ATTR_FDARG(1),int,__NOTHROW_NCX,__localdep_fallocate32,(__fd_t __fd, __STDC_INT_AS_UINT_T __mode, __pos32_t __offset, __pos32_t __length),fallocate,(__fd,__mode,__offset,__length))
#endif /* !__local___localdep_fallocate32_defined && __CRT_HAVE_fallocate */
__LOCAL_LIBC(fallocate64) __ATTR_FDWRITE(1) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(fallocate64))(__fd_t __fd, __STDC_INT_AS_UINT_T __mode, __PIO_OFFSET64 __offset, __PIO_OFFSET64 __length) {
#ifdef __CRT_HAVE_fallocate
	return (__NAMESPACE_LOCAL_SYM __localdep_fallocate32)(__fd, __mode, (__pos32_t)__offset, (__pos32_t)__length);
#else /* __CRT_HAVE_fallocate */
	(void)__fd;
	(void)__mode;
	(void)__offset;
	(void)__length;
	return 0;
#endif /* !__CRT_HAVE_fallocate */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_fallocate64_defined
#define __local___localdep_fallocate64_defined
#define __localdep_fallocate64 __LIBC_LOCAL_NAME(fallocate64)
#endif /* !__local___localdep_fallocate64_defined */
#endif /* !__local_fallocate64_defined */
