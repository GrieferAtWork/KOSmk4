/* HASH CRC-32:0x8cbff94d */
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
#ifndef __local_settimeofday_defined
#define __local_settimeofday_defined
#include <__crt.h>
#include <bits/types.h>
#if defined(__CRT_HAVE_settimeofday64) || defined(__CRT_HAVE___settimeofday64) || defined(__CRT_HAVE_settimeofday) || defined(__CRT_HAVE___settimeofday) || defined(__CRT_HAVE___libc_settimeofday)
#include <bits/os/timeval.h>
struct timezone;
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_settimeofday32_defined
#define __local___localdep_settimeofday32_defined
#ifdef __CRT_HAVE_settimeofday
__CREDIRECT(__ATTR_IN_OPT(1) __ATTR_IN_OPT(2),int,__NOTHROW_NCX,__localdep_settimeofday32,(struct __timeval32 const *__tv, struct timezone const *__tz),settimeofday,(__tv,__tz))
#elif defined(__CRT_HAVE___settimeofday)
__CREDIRECT(__ATTR_IN_OPT(1) __ATTR_IN_OPT(2),int,__NOTHROW_NCX,__localdep_settimeofday32,(struct __timeval32 const *__tv, struct timezone const *__tz),__settimeofday,(__tv,__tz))
#elif defined(__CRT_HAVE___libc_settimeofday)
__CREDIRECT(__ATTR_IN_OPT(1) __ATTR_IN_OPT(2),int,__NOTHROW_NCX,__localdep_settimeofday32,(struct __timeval32 const *__tv, struct timezone const *__tz),__libc_settimeofday,(__tv,__tz))
#else /* ... */
#undef __local___localdep_settimeofday32_defined
#endif /* !... */
#endif /* !__local___localdep_settimeofday32_defined */
#ifndef __local___localdep_settimeofday64_defined
#define __local___localdep_settimeofday64_defined
#if defined(__CRT_HAVE_settimeofday) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
__CREDIRECT(__ATTR_IN_OPT(1) __ATTR_IN_OPT(2),int,__NOTHROW_NCX,__localdep_settimeofday64,(struct __timeval64 const *__tv, struct timezone const *__tz),settimeofday,(__tv,__tz))
#elif defined(__CRT_HAVE___settimeofday) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
__CREDIRECT(__ATTR_IN_OPT(1) __ATTR_IN_OPT(2),int,__NOTHROW_NCX,__localdep_settimeofday64,(struct __timeval64 const *__tv, struct timezone const *__tz),__settimeofday,(__tv,__tz))
#elif defined(__CRT_HAVE___libc_settimeofday) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
__CREDIRECT(__ATTR_IN_OPT(1) __ATTR_IN_OPT(2),int,__NOTHROW_NCX,__localdep_settimeofday64,(struct __timeval64 const *__tv, struct timezone const *__tz),__libc_settimeofday,(__tv,__tz))
#elif defined(__CRT_HAVE_settimeofday64)
__CREDIRECT(__ATTR_IN_OPT(1) __ATTR_IN_OPT(2),int,__NOTHROW_NCX,__localdep_settimeofday64,(struct __timeval64 const *__tv, struct timezone const *__tz),settimeofday64,(__tv,__tz))
#elif defined(__CRT_HAVE___settimeofday64)
__CREDIRECT(__ATTR_IN_OPT(1) __ATTR_IN_OPT(2),int,__NOTHROW_NCX,__localdep_settimeofday64,(struct __timeval64 const *__tv, struct timezone const *__tz),__settimeofday64,(__tv,__tz))
#elif defined(__CRT_HAVE_settimeofday) || defined(__CRT_HAVE___settimeofday) || defined(__CRT_HAVE___libc_settimeofday)
__NAMESPACE_LOCAL_END
#include <libc/local/sys.time/settimeofday64.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_settimeofday64 __LIBC_LOCAL_NAME(settimeofday64)
#else /* ... */
#undef __local___localdep_settimeofday64_defined
#endif /* !... */
#endif /* !__local___localdep_settimeofday64_defined */
__LOCAL_LIBC(settimeofday) __ATTR_IN_OPT(1) __ATTR_IN_OPT(2) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(settimeofday))(struct timeval const *__tv, struct timezone const *__tz) {
#if defined(__CRT_HAVE_settimeofday) || defined(__CRT_HAVE___settimeofday) || defined(__CRT_HAVE___libc_settimeofday)
	struct __timeval32 __tv32;
	if (!__tv)
		return (__NAMESPACE_LOCAL_SYM __localdep_settimeofday32)(__NULLPTR, __tz);
	__tv32.tv_sec  = (__time32_t)__tv->tv_sec;
	__tv32.tv_usec = __tv->tv_usec;
	return (__NAMESPACE_LOCAL_SYM __localdep_settimeofday32)(&__tv32, __tz);
#else /* __CRT_HAVE_settimeofday || __CRT_HAVE___settimeofday || __CRT_HAVE___libc_settimeofday */
	struct __timeval64 __tv64;
	if (!__tv)
		return (__NAMESPACE_LOCAL_SYM __localdep_settimeofday64)(__NULLPTR, __tz);
	__tv64.tv_sec  = (__time64_t)__tv->tv_sec;
	__tv64.tv_usec = __tv->tv_usec;
	return (__NAMESPACE_LOCAL_SYM __localdep_settimeofday64)(&__tv64, __tz);
#endif /* !__CRT_HAVE_settimeofday && !__CRT_HAVE___settimeofday && !__CRT_HAVE___libc_settimeofday */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_settimeofday_defined
#define __local___localdep_settimeofday_defined
#define __localdep_settimeofday __LIBC_LOCAL_NAME(settimeofday)
#endif /* !__local___localdep_settimeofday_defined */
#else /* __CRT_HAVE_settimeofday64 || __CRT_HAVE___settimeofday64 || __CRT_HAVE_settimeofday || __CRT_HAVE___settimeofday || __CRT_HAVE___libc_settimeofday */
#undef __local_settimeofday_defined
#endif /* !__CRT_HAVE_settimeofday64 && !__CRT_HAVE___settimeofday64 && !__CRT_HAVE_settimeofday && !__CRT_HAVE___settimeofday && !__CRT_HAVE___libc_settimeofday */
#endif /* !__local_settimeofday_defined */
