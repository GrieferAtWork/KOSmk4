/* HASH CRC-32:0x2ca3d3ec */
/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_ftruncate64_defined
#define __local_ftruncate64_defined
#include <__crt.h>
#if defined(__CRT_HAVE_ftruncate) || defined(__CRT_HAVE___ftruncate) || defined(__CRT_HAVE___libc_ftruncate) || defined(__CRT_HAVE__chsize) || defined(__CRT_HAVE_chsize)
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
#ifndef __local___localdep_crt_ftruncate32_defined
#define __local___localdep_crt_ftruncate32_defined
#ifdef __CRT_HAVE_ftruncate
__CREDIRECT(__ATTR_FDWRITE(1),int,__NOTHROW_NCX,__localdep_crt_ftruncate32,(__fd_t __fd, __pos32_t __length),ftruncate,(__fd,__length))
#elif defined(__CRT_HAVE___ftruncate)
__CREDIRECT(__ATTR_FDWRITE(1),int,__NOTHROW_NCX,__localdep_crt_ftruncate32,(__fd_t __fd, __pos32_t __length),__ftruncate,(__fd,__length))
#elif defined(__CRT_HAVE___libc_ftruncate)
__CREDIRECT(__ATTR_FDWRITE(1),int,__NOTHROW_NCX,__localdep_crt_ftruncate32,(__fd_t __fd, __pos32_t __length),__libc_ftruncate,(__fd,__length))
#elif defined(__CRT_HAVE__chsize)
__CREDIRECT(__ATTR_FDWRITE(1),int,__NOTHROW_NCX,__localdep_crt_ftruncate32,(__fd_t __fd, __pos32_t __length),_chsize,(__fd,__length))
#elif defined(__CRT_HAVE_chsize)
__CREDIRECT(__ATTR_FDWRITE(1),int,__NOTHROW_NCX,__localdep_crt_ftruncate32,(__fd_t __fd, __pos32_t __length),chsize,(__fd,__length))
#else /* ... */
#undef __local___localdep_crt_ftruncate32_defined
#endif /* !... */
#endif /* !__local___localdep_crt_ftruncate32_defined */
__LOCAL_LIBC(ftruncate64) __ATTR_FDWRITE(1) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(ftruncate64))(__fd_t __fd, __PIO_OFFSET64 __length) {
	return (__NAMESPACE_LOCAL_SYM __localdep_crt_ftruncate32)(__fd, (__pos32_t)__length);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_ftruncate64_defined
#define __local___localdep_ftruncate64_defined
#define __localdep_ftruncate64 __LIBC_LOCAL_NAME(ftruncate64)
#endif /* !__local___localdep_ftruncate64_defined */
#else /* __CRT_HAVE_ftruncate || __CRT_HAVE___ftruncate || __CRT_HAVE___libc_ftruncate || __CRT_HAVE__chsize || __CRT_HAVE_chsize */
#undef __local_ftruncate64_defined
#endif /* !__CRT_HAVE_ftruncate && !__CRT_HAVE___ftruncate && !__CRT_HAVE___libc_ftruncate && !__CRT_HAVE__chsize && !__CRT_HAVE_chsize */
#endif /* !__local_ftruncate64_defined */
