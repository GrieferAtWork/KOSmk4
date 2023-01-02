/* HASH CRC-32:0x577a28fd */
/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_getitimer_defined
#define __local_getitimer_defined
#include <__crt.h>
#include <bits/types.h>
#if defined(__CRT_HAVE_getitimer64) || defined(__CRT_HAVE_getitimer) || defined(__CRT_HAVE___getitimer) || defined(__CRT_HAVE___libc_getitimer)
#include <bits/os/itimerval.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_getitimer32_defined
#define __local___localdep_getitimer32_defined
#ifdef __CRT_HAVE_getitimer
__CREDIRECT(__ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_getitimer32,(int __which, struct __itimerval32 *__curr_value),getitimer,(__which,__curr_value))
#elif defined(__CRT_HAVE___getitimer)
__CREDIRECT(__ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_getitimer32,(int __which, struct __itimerval32 *__curr_value),__getitimer,(__which,__curr_value))
#elif defined(__CRT_HAVE___libc_getitimer)
__CREDIRECT(__ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_getitimer32,(int __which, struct __itimerval32 *__curr_value),__libc_getitimer,(__which,__curr_value))
#else /* ... */
#undef __local___localdep_getitimer32_defined
#endif /* !... */
#endif /* !__local___localdep_getitimer32_defined */
#ifndef __local___localdep_getitimer64_defined
#define __local___localdep_getitimer64_defined
#if defined(__CRT_HAVE_getitimer) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
__CREDIRECT(__ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_getitimer64,(int __which, struct __itimerval64 *__curr_value),getitimer,(__which,__curr_value))
#elif defined(__CRT_HAVE___getitimer) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
__CREDIRECT(__ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_getitimer64,(int __which, struct __itimerval64 *__curr_value),__getitimer,(__which,__curr_value))
#elif defined(__CRT_HAVE___libc_getitimer) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
__CREDIRECT(__ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_getitimer64,(int __which, struct __itimerval64 *__curr_value),__libc_getitimer,(__which,__curr_value))
#elif defined(__CRT_HAVE_getitimer64)
__CREDIRECT(__ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_getitimer64,(int __which, struct __itimerval64 *__curr_value),getitimer64,(__which,__curr_value))
#elif defined(__CRT_HAVE_getitimer) || defined(__CRT_HAVE___getitimer) || defined(__CRT_HAVE___libc_getitimer)
__NAMESPACE_LOCAL_END
#include <libc/local/sys.time/getitimer64.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_getitimer64 __LIBC_LOCAL_NAME(getitimer64)
#else /* ... */
#undef __local___localdep_getitimer64_defined
#endif /* !... */
#endif /* !__local___localdep_getitimer64_defined */
__LOCAL_LIBC(getitimer) __ATTR_OUT(2) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(getitimer))(int __which, struct itimerval *__curr_value) {
#if defined(__CRT_HAVE_getitimer) || defined(__CRT_HAVE___getitimer) || defined(__CRT_HAVE___libc_getitimer)
	int __result;
	struct __itimerval32 __tv32;
	__result = (__NAMESPACE_LOCAL_SYM __localdep_getitimer32)(__which, &__tv32);
	if __likely(!__result) {
		__curr_value->it_interval.tv_sec  = (__time64_t)__tv32.it_interval.tv_sec;
		__curr_value->it_interval.tv_usec = __tv32.it_interval.tv_usec;
		__curr_value->it_value.tv_sec     = (__time64_t)__tv32.it_value.tv_sec;
		__curr_value->it_value.tv_usec    = __tv32.it_value.tv_usec;
	}
	return __result;
#else /* __CRT_HAVE_getitimer || __CRT_HAVE___getitimer || __CRT_HAVE___libc_getitimer */
	int __result;
	struct __timeval64 __tv64;
	__result = (__NAMESPACE_LOCAL_SYM __localdep_getitimer64)(__which, &__tv64);
	if __likely(!__result) {
		__curr_value->it_interval.tv_sec  = (__time32_t)__tv64.it_interval.tv_sec;
		__curr_value->it_interval.tv_usec = __tv64.it_interval.tv_usec;
		__curr_value->it_value.tv_sec     = (__time32_t)__tv64.it_value.tv_sec;
		__curr_value->it_value.tv_usec    = __tv64.it_value.tv_usec;
	}
	return __result;
#endif /* !__CRT_HAVE_getitimer && !__CRT_HAVE___getitimer && !__CRT_HAVE___libc_getitimer */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_getitimer_defined
#define __local___localdep_getitimer_defined
#define __localdep_getitimer __LIBC_LOCAL_NAME(getitimer)
#endif /* !__local___localdep_getitimer_defined */
#else /* __CRT_HAVE_getitimer64 || __CRT_HAVE_getitimer || __CRT_HAVE___getitimer || __CRT_HAVE___libc_getitimer */
#undef __local_getitimer_defined
#endif /* !__CRT_HAVE_getitimer64 && !__CRT_HAVE_getitimer && !__CRT_HAVE___getitimer && !__CRT_HAVE___libc_getitimer */
#endif /* !__local_getitimer_defined */
