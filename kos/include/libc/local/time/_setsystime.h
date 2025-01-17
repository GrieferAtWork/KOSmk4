/* HASH CRC-32:0xb67a834b */
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
#ifndef __local__setsystime_defined
#define __local__setsystime_defined
#include <__crt.h>
#include <bits/types.h>
#if defined(__CRT_HAVE_settimeofday64) || defined(__CRT_HAVE___settimeofday64) || defined(__CRT_HAVE_settimeofday) || defined(__CRT_HAVE___settimeofday) || defined(__CRT_HAVE___libc_settimeofday)
#include <features.h>
#include <bits/crt/tm.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_mktime64_defined
#define __local___localdep_mktime64_defined
#if defined(__CRT_HAVE_mktime) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INOUT(1),__time64_t,__NOTHROW_NCX,__localdep_mktime64,(struct __NAMESPACE_STD_SYM tm *__tp),mktime,(__tp))
#elif defined(__CRT_HAVE_mktime64)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INOUT(1),__time64_t,__NOTHROW_NCX,__localdep_mktime64,(struct __NAMESPACE_STD_SYM tm *__tp),mktime64,(__tp))
#elif defined(__CRT_HAVE_timelocal64)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INOUT(1),__time64_t,__NOTHROW_NCX,__localdep_mktime64,(struct __NAMESPACE_STD_SYM tm *__tp),timelocal64,(__tp))
#elif defined(__CRT_HAVE___mktime64)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INOUT(1),__time64_t,__NOTHROW_NCX,__localdep_mktime64,(struct __NAMESPACE_STD_SYM tm *__tp),__mktime64,(__tp))
#elif defined(__CRT_HAVE__mktime64)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INOUT(1),__time64_t,__NOTHROW_NCX,__localdep_mktime64,(struct __NAMESPACE_STD_SYM tm *__tp),_mktime64,(__tp))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/time/mktime64.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_mktime64 __LIBC_LOCAL_NAME(mktime64)
#endif /* !... */
#endif /* !__local___localdep_mktime64_defined */
#ifndef __local___localdep_settimeofday64_defined
#define __local___localdep_settimeofday64_defined
#if defined(__CRT_HAVE_settimeofday) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
__NAMESPACE_LOCAL_END
#include <bits/os/timeval.h>
struct timezone;
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN_OPT(1) __ATTR_IN_OPT(2),int,__NOTHROW_NCX,__localdep_settimeofday64,(struct __timeval64 const *__tv, struct timezone const *__tz),settimeofday,(__tv,__tz))
#elif defined(__CRT_HAVE___settimeofday) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
__NAMESPACE_LOCAL_END
#include <bits/os/timeval.h>
struct timezone;
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN_OPT(1) __ATTR_IN_OPT(2),int,__NOTHROW_NCX,__localdep_settimeofday64,(struct __timeval64 const *__tv, struct timezone const *__tz),__settimeofday,(__tv,__tz))
#elif defined(__CRT_HAVE___libc_settimeofday) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
__NAMESPACE_LOCAL_END
#include <bits/os/timeval.h>
struct timezone;
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN_OPT(1) __ATTR_IN_OPT(2),int,__NOTHROW_NCX,__localdep_settimeofday64,(struct __timeval64 const *__tv, struct timezone const *__tz),__libc_settimeofday,(__tv,__tz))
#elif defined(__CRT_HAVE_settimeofday64)
__NAMESPACE_LOCAL_END
#include <bits/os/timeval.h>
struct timezone;
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN_OPT(1) __ATTR_IN_OPT(2),int,__NOTHROW_NCX,__localdep_settimeofday64,(struct __timeval64 const *__tv, struct timezone const *__tz),settimeofday64,(__tv,__tz))
#elif defined(__CRT_HAVE___settimeofday64)
__NAMESPACE_LOCAL_END
#include <bits/os/timeval.h>
struct timezone;
__NAMESPACE_LOCAL_BEGIN
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
__NAMESPACE_LOCAL_END
#include <bits/os/timeval.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_setsystime) __ATTR_INOUT(1) unsigned int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_setsystime))(struct __NAMESPACE_STD_SYM tm *__tp, unsigned int __milliseconds) {
	struct __timeval64 __tv;
	__tv.tv_sec  = (__NAMESPACE_LOCAL_SYM __localdep_mktime64)(__tp);
	__tv.tv_usec = __milliseconds * 1000;
	return (unsigned int)(__NAMESPACE_LOCAL_SYM __localdep_settimeofday64)(&__tv, __NULLPTR);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__setsystime_defined
#define __local___localdep__setsystime_defined
#define __localdep__setsystime __LIBC_LOCAL_NAME(_setsystime)
#endif /* !__local___localdep__setsystime_defined */
#else /* __CRT_HAVE_settimeofday64 || __CRT_HAVE___settimeofday64 || __CRT_HAVE_settimeofday || __CRT_HAVE___settimeofday || __CRT_HAVE___libc_settimeofday */
#undef __local__setsystime_defined
#endif /* !__CRT_HAVE_settimeofday64 && !__CRT_HAVE___settimeofday64 && !__CRT_HAVE_settimeofday && !__CRT_HAVE___settimeofday && !__CRT_HAVE___libc_settimeofday */
#endif /* !__local__setsystime_defined */
