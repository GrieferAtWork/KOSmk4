/* HASH CRC-32:0xbbdf046a */
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
#ifndef __local_PWrite_defined
#define __local_PWrite_defined 1
#include <__crt.h>
#if defined(__CRT_HAVE_PWrite64) || defined(__CRT_HAVE_PWrite)
#include <kos/anno.h>
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: PWrite32 from kos.unistd */
#if !defined(__local___localdep_PWrite32_defined) && defined(__CRT_HAVE_PWrite)
#define __local___localdep_PWrite32_defined 1
__CREDIRECT(__ATTR_NONNULL((2)),__SIZE_TYPE__,__THROWING,__localdep_PWrite32,(__fd_t __fd, void const *__buf, __SIZE_TYPE__ __bufsize, __pos32_t __offset),PWrite,(__fd,__buf,__bufsize,__offset))
#endif /* !__local___localdep_PWrite32_defined && __CRT_HAVE_PWrite */
/* Dependency: PWrite64 from kos.unistd */
#ifndef __local___localdep_PWrite64_defined
#define __local___localdep_PWrite64_defined 1
#ifdef __CRT_HAVE_PWrite64
/* >> pwrite64(2)
 * Write data to a file at a specific offset */
__CREDIRECT(__ATTR_NONNULL((2)),__SIZE_TYPE__,__THROWING,__localdep_PWrite64,(__fd_t __fd, void *__buf, __SIZE_TYPE__ __bufsize, __pos64_t __offset),PWrite64,(__fd,__buf,__bufsize,__offset))
#elif defined(__CRT_HAVE_PWrite) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
/* >> pwrite64(2)
 * Write data to a file at a specific offset */
__CREDIRECT(__ATTR_NONNULL((2)),__SIZE_TYPE__,__THROWING,__localdep_PWrite64,(__fd_t __fd, void *__buf, __SIZE_TYPE__ __bufsize, __pos64_t __offset),PWrite,(__fd,__buf,__bufsize,__offset))
#elif defined(__CRT_HAVE_PWrite)
__NAMESPACE_LOCAL_END
#include <libc/local/kos.unistd/PWrite64.h>
__NAMESPACE_LOCAL_BEGIN
/* >> pwrite64(2)
 * Write data to a file at a specific offset */
#define __localdep_PWrite64 __LIBC_LOCAL_NAME(PWrite64)
#else /* ... */
#undef __local___localdep_PWrite64_defined
#endif /* !... */
#endif /* !__local___localdep_PWrite64_defined */
/* >> pwrite(2)
 * Write data to a file at a specific offset */
__LOCAL_LIBC(PWrite) __ATTR_NONNULL((2)) __SIZE_TYPE__
(__LIBCCALL __LIBC_LOCAL_NAME(PWrite))(__fd_t __fd, void const *__buf, __SIZE_TYPE__ __bufsize, __FS_TYPE(pos) __offset) __THROWS(...) {
#ifdef __CRT_HAVE_PWrite
	return __localdep_PWrite32(__fd, __buf, __bufsize, (__pos32_t)__offset);
#else /* __CRT_HAVE_PWrite */
	return __localdep_PWrite64(__fd, __buf, __bufsize, (__pos64_t)__offset);
#endif /* !__CRT_HAVE_PWrite */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_PWrite_defined
#define __local___localdep_PWrite_defined 1
#define __localdep_PWrite __LIBC_LOCAL_NAME(PWrite)
#endif /* !__local___localdep_PWrite_defined */
#else /* __CRT_HAVE_PWrite64 || __CRT_HAVE_PWrite */
#undef __local_PWrite_defined
#endif /* !__CRT_HAVE_PWrite64 && !__CRT_HAVE_PWrite */
#endif /* !__local_PWrite_defined */
