/* HASH CRC-32:0x5eafda27 */
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
#ifndef __local_fallocate_defined
#define __local_fallocate_defined 1
#include <__crt.h>
#include <features.h>
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: fallocate32 from fcntl */
#if !defined(__local___localdep_fallocate32_defined) && defined(__CRT_HAVE_fallocate)
#define __local___localdep_fallocate32_defined 1
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_fallocate32,(__fd_t __fd, int __mode, __off64_t __offset, __off64_t __length),fallocate,(__fd,__mode,__offset,__length))
#endif /* !__local___localdep_fallocate32_defined && __CRT_HAVE_fallocate */
/* Dependency: fallocate64 from fcntl */
#ifndef __local___localdep_fallocate64_defined
#define __local___localdep_fallocate64_defined 1
#ifdef __CRT_HAVE_fallocate64
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_fallocate64,(__fd_t __fd, int __mode, __off64_t __offset, __off64_t __length),fallocate64,(__fd,__mode,__offset,__length))
#elif defined(__CRT_HAVE_fallocate) && (__SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_fallocate64,(__fd_t __fd, int __mode, __off64_t __offset, __off64_t __length),fallocate,(__fd,__mode,__offset,__length))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <local/fcntl/fallocate64.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_fallocate64 __LIBC_LOCAL_NAME(fallocate64)
#endif /* !... */
#endif /* !__local___localdep_fallocate64_defined */
__LOCAL_LIBC(fallocate) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(fallocate))(__fd_t __fd, int __mode, __FS_TYPE(off) __offset, __FS_TYPE(off) __length) {

	return __localdep_fallocate64(__fd, __mode, (__off64_t)__offset, (__off64_t)__length);









}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_fallocate_defined
#define __local___localdep_fallocate_defined 1
#define __localdep_fallocate __LIBC_LOCAL_NAME(fallocate)
#endif /* !__local___localdep_fallocate_defined */
#endif /* !__local_fallocate_defined */
