/* HASH CRC-32:0x4a60434a */
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
#ifndef __local__getsystime_defined
#define __local__getsystime_defined
#include <__crt.h>
#include <bits/types.h>
#if defined(__CRT_HAVE_gettimeofday64) || defined(__CRT_HAVE___gettimeofday64) || defined(__CRT_HAVE_gettimeofday) || defined(__CRT_HAVE___gettimeofday) || defined(__CRT_HAVE___libc_gettimeofday)
#include <bits/crt/tm.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_gettimeofday64_defined
#define __local___localdep_gettimeofday64_defined
#if defined(__CRT_HAVE_gettimeofday) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
__NAMESPACE_LOCAL_END
#include <bits/os/timeval.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_OUT_OPT(1) __ATTR_OUT_OPT(2),int,__NOTHROW_NCX,__localdep_gettimeofday64,(struct __timeval64 *__restrict __tv, void * __tz),gettimeofday,(__tv,__tz))
#elif defined(__CRT_HAVE_gettimeofday64)
__NAMESPACE_LOCAL_END
#include <bits/os/timeval.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_OUT_OPT(1) __ATTR_OUT_OPT(2),int,__NOTHROW_NCX,__localdep_gettimeofday64,(struct __timeval64 *__restrict __tv, void * __tz),gettimeofday64,(__tv,__tz))
#elif defined(__CRT_HAVE___gettimeofday64)
__NAMESPACE_LOCAL_END
#include <bits/os/timeval.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_OUT_OPT(1) __ATTR_OUT_OPT(2),int,__NOTHROW_NCX,__localdep_gettimeofday64,(struct __timeval64 *__restrict __tv, void * __tz),__gettimeofday64,(__tv,__tz))
#elif defined(__CRT_HAVE___gettimeofday) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
__NAMESPACE_LOCAL_END
#include <bits/os/timeval.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_OUT_OPT(1) __ATTR_OUT_OPT(2),int,__NOTHROW_NCX,__localdep_gettimeofday64,(struct __timeval64 *__restrict __tv, void * __tz),__gettimeofday,(__tv,__tz))
#elif defined(__CRT_HAVE___libc_gettimeofday) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
__NAMESPACE_LOCAL_END
#include <bits/os/timeval.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_OUT_OPT(1) __ATTR_OUT_OPT(2),int,__NOTHROW_NCX,__localdep_gettimeofday64,(struct __timeval64 *__restrict __tv, void * __tz),__libc_gettimeofday,(__tv,__tz))
#elif defined(__CRT_HAVE_gettimeofday) || defined(__CRT_HAVE___gettimeofday) || defined(__CRT_HAVE___libc_gettimeofday)
__NAMESPACE_LOCAL_END
#include <libc/local/sys.time/gettimeofday64.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_gettimeofday64 __LIBC_LOCAL_NAME(gettimeofday64)
#else /* ... */
#undef __local___localdep_gettimeofday64_defined
#endif /* !... */
#endif /* !__local___localdep_gettimeofday64_defined */
#ifndef __local___localdep_localtime64_r_defined
#define __local___localdep_localtime64_r_defined
#if defined(__CRT_HAVE_localtime_r) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),struct __NAMESPACE_STD_SYM tm *,__NOTHROW_NCX,__localdep_localtime64_r,(__time64_t const *__restrict __timer, struct __NAMESPACE_STD_SYM tm *__restrict __tp),localtime_r,(__timer,__tp))
#elif defined(__CRT_HAVE_localtime64_r)
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),struct __NAMESPACE_STD_SYM tm *,__NOTHROW_NCX,__localdep_localtime64_r,(__time64_t const *__restrict __timer, struct __NAMESPACE_STD_SYM tm *__restrict __tp),localtime64_r,(__timer,__tp))
#elif defined(__CRT_HAVE___localtime64_r)
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),struct __NAMESPACE_STD_SYM tm *,__NOTHROW_NCX,__localdep_localtime64_r,(__time64_t const *__restrict __timer, struct __NAMESPACE_STD_SYM tm *__restrict __tp),__localtime64_r,(__timer,__tp))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/time/localtime64_r.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_localtime64_r __LIBC_LOCAL_NAME(localtime64_r)
#endif /* !... */
#endif /* !__local___localdep_localtime64_r_defined */
__NAMESPACE_LOCAL_END
#include <bits/os/timeval.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_getsystime) __ATTR_OUT(1) unsigned int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_getsystime))(struct __NAMESPACE_STD_SYM tm *__tp) {
	struct __timeval64 __tv;
	if __unlikely((__NAMESPACE_LOCAL_SYM __localdep_gettimeofday64)(&__tv, __NULLPTR) != 0) {
		__tv.tv_sec  = 0;
		__tv.tv_usec = 0;
	}
	(__NAMESPACE_LOCAL_SYM __localdep_localtime64_r)(&__tv.tv_sec, __tp);
	return __tv.tv_usec / 1000;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__getsystime_defined
#define __local___localdep__getsystime_defined
#define __localdep__getsystime __LIBC_LOCAL_NAME(_getsystime)
#endif /* !__local___localdep__getsystime_defined */
#else /* __CRT_HAVE_gettimeofday64 || __CRT_HAVE___gettimeofday64 || __CRT_HAVE_gettimeofday || __CRT_HAVE___gettimeofday || __CRT_HAVE___libc_gettimeofday */
#undef __local__getsystime_defined
#endif /* !__CRT_HAVE_gettimeofday64 && !__CRT_HAVE___gettimeofday64 && !__CRT_HAVE_gettimeofday && !__CRT_HAVE___gettimeofday && !__CRT_HAVE___libc_gettimeofday */
#endif /* !__local__getsystime_defined */
