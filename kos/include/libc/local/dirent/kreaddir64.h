/* HASH CRC-32:0xf76fadea */
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
#ifndef __local_kreaddir64_defined
#define __local_kreaddir64_defined
#include <__crt.h>
#include <bits/os/dirent.h>
#if (defined(__CRT_HAVE_kreaddirf) && defined(__DIRENT32_MATCHES_DIRENT64)) || defined(__CRT_HAVE_kreaddirf64)
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_kreaddirf64_defined
#define __local___localdep_kreaddirf64_defined
#if defined(__CRT_HAVE_kreaddirf) && defined(__DIRENT32_MATCHES_DIRENT64)
__CREDIRECT(__ATTR_WUNUSED __ATTR_FDREAD(1),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_kreaddirf64,(__fd_t __fd, struct __dirent64 *__buf, __SIZE_TYPE__ __bufsize, unsigned int __mode, __oflag_t __flags),kreaddirf,(__fd,__buf,__bufsize,__mode,__flags))
#elif defined(__CRT_HAVE_kreaddirf64)
__CREDIRECT(__ATTR_WUNUSED __ATTR_FDREAD(1),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_kreaddirf64,(__fd_t __fd, struct __dirent64 *__buf, __SIZE_TYPE__ __bufsize, unsigned int __mode, __oflag_t __flags),kreaddirf64,(__fd,__buf,__bufsize,__mode,__flags))
#else /* ... */
#undef __local___localdep_kreaddirf64_defined
#endif /* !... */
#endif /* !__local___localdep_kreaddirf64_defined */
__LOCAL_LIBC(kreaddir64) __ATTR_WUNUSED __ATTR_FDREAD(1) __SSIZE_TYPE__
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(kreaddir64))(__fd_t __fd, struct __dirent64 *__buf, __SIZE_TYPE__ __bufsize, unsigned int __mode) {
	return (__NAMESPACE_LOCAL_SYM __localdep_kreaddirf64)(__fd, __buf, __bufsize, __mode, 0);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_kreaddir64_defined
#define __local___localdep_kreaddir64_defined
#define __localdep_kreaddir64 __LIBC_LOCAL_NAME(kreaddir64)
#endif /* !__local___localdep_kreaddir64_defined */
#else /* (__CRT_HAVE_kreaddirf && __DIRENT32_MATCHES_DIRENT64) || __CRT_HAVE_kreaddirf64 */
#undef __local_kreaddir64_defined
#endif /* (!__CRT_HAVE_kreaddirf || !__DIRENT32_MATCHES_DIRENT64) && !__CRT_HAVE_kreaddirf64 */
#endif /* !__local_kreaddir64_defined */
