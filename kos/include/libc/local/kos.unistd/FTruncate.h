/* HASH CRC-32:0x5c301b50 */
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
#ifndef __local_FTruncate_defined
#define __local_FTruncate_defined 1
#include <__crt.h>
#if defined(__CRT_HAVE_FTruncate64) || defined(__CRT_HAVE_FTruncate)
#include <kos/anno.h>
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: FTruncate32 from kos.unistd */
#if !defined(__local___localdep_FTruncate32_defined) && defined(__CRT_HAVE_FTruncate)
#define __local___localdep_FTruncate32_defined 1
/* >> ftruncate(2), ftruncate64(2)
 * Truncate the given file `FD' to a length of `LENGTH' */
__CREDIRECT(,int,__THROWING,__localdep_FTruncate32,(__fd_t __fd, __pos32_t __length),FTruncate,(__fd,__length))
#endif /* !__local___localdep_FTruncate32_defined && __CRT_HAVE_FTruncate */
/* Dependency: FTruncate64 from kos.unistd */
#ifndef __local___localdep_FTruncate64_defined
#define __local___localdep_FTruncate64_defined 1
#ifdef __CRT_HAVE_FTruncate64
/* >> ftruncate(2), ftruncate64(2)
 * Truncate the given file `FD' to a length of `LENGTH' */
__CREDIRECT_VOID(,__THROWING,__localdep_FTruncate64,(__fd_t __fd, __pos64_t __length),FTruncate64,(__fd,__length))
#elif defined(__CRT_HAVE_FTruncate) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
/* >> ftruncate(2), ftruncate64(2)
 * Truncate the given file `FD' to a length of `LENGTH' */
__CREDIRECT_VOID(,__THROWING,__localdep_FTruncate64,(__fd_t __fd, __pos64_t __length),FTruncate,(__fd,__length))
#elif defined(__CRT_HAVE_FTruncate)
__NAMESPACE_LOCAL_END
#include <libc/local/kos.unistd/FTruncate64.h>
__NAMESPACE_LOCAL_BEGIN
/* >> ftruncate(2), ftruncate64(2)
 * Truncate the given file `FD' to a length of `LENGTH' */
#define __localdep_FTruncate64 __LIBC_LOCAL_NAME(FTruncate64)
#else /* ... */
#undef __local___localdep_FTruncate64_defined
#endif /* !... */
#endif /* !__local___localdep_FTruncate64_defined */
/* >> ftruncate(2), ftruncate64(2)
 * Truncate the given file `FD' to a length of `LENGTH' */
__LOCAL_LIBC(FTruncate) void
(__LIBCCALL __LIBC_LOCAL_NAME(FTruncate))(__fd_t __fd, __FS_TYPE(pos) __length) __THROWS(...) {
#ifdef __CRT_HAVE_FTruncate
	__localdep_FTruncate32(__fd, (__pos32_t)__length);
#else /* __CRT_HAVE_FTruncate */
	__localdep_FTruncate64(__fd, (__pos64_t)__length);
#endif /* !__CRT_HAVE_FTruncate */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_FTruncate_defined
#define __local___localdep_FTruncate_defined 1
#define __localdep_FTruncate __LIBC_LOCAL_NAME(FTruncate)
#endif /* !__local___localdep_FTruncate_defined */
#else /* __CRT_HAVE_FTruncate64 || __CRT_HAVE_FTruncate */
#undef __local_FTruncate_defined
#endif /* !__CRT_HAVE_FTruncate64 && !__CRT_HAVE_FTruncate */
#endif /* !__local_FTruncate_defined */
