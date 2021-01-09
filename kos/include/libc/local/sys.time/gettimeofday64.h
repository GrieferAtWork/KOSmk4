/* HASH CRC-32:0xf7d7ee68 */
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
#ifndef __local_gettimeofday64_defined
#define __local_gettimeofday64_defined 1
#include <__crt.h>
#if defined(__CRT_HAVE_gettimeofday) || defined(__CRT_HAVE___gettimeofday)
#include <bits/os/timeval.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: gettimeofday32 from sys.time */
#ifndef __local___localdep_gettimeofday32_defined
#define __local___localdep_gettimeofday32_defined 1
#ifdef __CRT_HAVE_gettimeofday
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,__localdep_gettimeofday32,(struct __timeval32 *__restrict __tv, void * __tz),gettimeofday,(__tv,__tz))
#elif defined(__CRT_HAVE___gettimeofday)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,__localdep_gettimeofday32,(struct __timeval32 *__restrict __tv, void * __tz),__gettimeofday,(__tv,__tz))
#else /* ... */
#undef __local___localdep_gettimeofday32_defined
#endif /* !... */
#endif /* !__local___localdep_gettimeofday32_defined */
__LOCAL_LIBC(gettimeofday64) __ATTR_NONNULL((1)) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(gettimeofday64))(struct __timeval64 *__restrict __tv, void * __tz) {
	int __result;
	struct __timeval32 __tv32;
	if (!__tv)
		return __localdep_gettimeofday32(__NULLPTR, __tz);
	__result = __localdep_gettimeofday32(&__tv32, __tz);
	if __likely(!__result) {
		__tv->tv_sec  = (__time64_t)__tv32.tv_sec;
		__tv->tv_usec = __tv32.tv_usec;
	}
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_gettimeofday64_defined
#define __local___localdep_gettimeofday64_defined 1
#define __localdep_gettimeofday64 __LIBC_LOCAL_NAME(gettimeofday64)
#endif /* !__local___localdep_gettimeofday64_defined */
#else /* __CRT_HAVE_gettimeofday || __CRT_HAVE___gettimeofday */
#undef __local_gettimeofday64_defined
#endif /* !__CRT_HAVE_gettimeofday && !__CRT_HAVE___gettimeofday */
#endif /* !__local_gettimeofday64_defined */
