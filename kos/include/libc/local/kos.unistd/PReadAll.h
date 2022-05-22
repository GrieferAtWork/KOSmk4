/* HASH CRC-32:0xe9d076be */
/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_PReadAll_defined
#define __local_PReadAll_defined
#include <__crt.h>
#include <bits/types.h>
#if defined(__CRT_HAVE_PReadAll) || defined(__CRT_HAVE_PReadAll64) || defined(__CRT_HAVE_PRead64) || defined(__CRT_HAVE_PRead)
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
#if !defined(__local___localdep_PReadAll32_defined) && defined(__CRT_HAVE_PReadAll)
#define __local___localdep_PReadAll32_defined
__CREDIRECT(__ATTR_ACCESS_WRS(2, 3),__SIZE_TYPE__,__THROWING,__localdep_PReadAll32,(__fd_t __fd, void *__buf, __SIZE_TYPE__ __bufsize, __pos32_t __offset),PReadAll,(__fd,__buf,__bufsize,__offset))
#endif /* !__local___localdep_PReadAll32_defined && __CRT_HAVE_PReadAll */
#ifndef __local___localdep_PReadAll64_defined
#define __local___localdep_PReadAll64_defined
#if defined(__CRT_HAVE_PReadAll) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_ACCESS_WRS(2, 3),__SIZE_TYPE__,__THROWING,__localdep_PReadAll64,(__fd_t __fd, void *__buf, __SIZE_TYPE__ __bufsize, __pos64_t __offset),PReadAll,(__fd,__buf,__bufsize,__offset))
#elif defined(__CRT_HAVE_PReadAll64)
__CREDIRECT(__ATTR_ACCESS_WRS(2, 3),__SIZE_TYPE__,__THROWING,__localdep_PReadAll64,(__fd_t __fd, void *__buf, __SIZE_TYPE__ __bufsize, __pos64_t __offset),PReadAll64,(__fd,__buf,__bufsize,__offset))
#elif defined(__CRT_HAVE_PRead64) || defined(__CRT_HAVE_PRead)
__NAMESPACE_LOCAL_END
#include <libc/local/kos.unistd/PReadAll64.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_PReadAll64 __LIBC_LOCAL_NAME(PReadAll64)
#else /* ... */
#undef __local___localdep_PReadAll64_defined
#endif /* !... */
#endif /* !__local___localdep_PReadAll64_defined */
__LOCAL_LIBC(PReadAll) __ATTR_ACCESS_WRS(2, 3) __SIZE_TYPE__
(__LIBCCALL __LIBC_LOCAL_NAME(PReadAll))(__fd_t __fd, void *__buf, __SIZE_TYPE__ __bufsize, __FS_TYPE(pos) __offset) __THROWS(...) {
#ifdef __CRT_HAVE_PReadAll
	return (__NAMESPACE_LOCAL_SYM __localdep_PReadAll32)(__fd, __buf, __bufsize, (__pos32_t)__offset);
#else /* __CRT_HAVE_PReadAll */
	return (__NAMESPACE_LOCAL_SYM __localdep_PReadAll64)(__fd, __buf, __bufsize, (__pos64_t)__offset);
#endif /* !__CRT_HAVE_PReadAll */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_PReadAll_defined
#define __local___localdep_PReadAll_defined
#define __localdep_PReadAll __LIBC_LOCAL_NAME(PReadAll)
#endif /* !__local___localdep_PReadAll_defined */
#else /* __CRT_HAVE_PReadAll || __CRT_HAVE_PReadAll64 || __CRT_HAVE_PRead64 || __CRT_HAVE_PRead */
#undef __local_PReadAll_defined
#endif /* !__CRT_HAVE_PReadAll && !__CRT_HAVE_PReadAll64 && !__CRT_HAVE_PRead64 && !__CRT_HAVE_PRead */
#endif /* !__local_PReadAll_defined */
