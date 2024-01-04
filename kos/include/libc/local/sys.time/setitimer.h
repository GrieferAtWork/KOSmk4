/* HASH CRC-32:0x6ed46f54 */
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
#ifndef __local_setitimer_defined
#define __local_setitimer_defined
#include <__crt.h>
#include <bits/types.h>
#if defined(__CRT_HAVE_setitimer64) || defined(__CRT_HAVE___setitimer64) || defined(__CRT_HAVE_setitimer) || defined(__CRT_HAVE___setitimer) || defined(__CRT_HAVE___libc_setitimer)
#include <bits/os/itimerval.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_setitimer32_defined
#define __local___localdep_setitimer32_defined
#ifdef __CRT_HAVE_setitimer
__CREDIRECT(__ATTR_IN_OPT(2) __ATTR_OUT_OPT(3),int,__NOTHROW_NCX,__localdep_setitimer32,(int __which, struct __itimerval32 const *__restrict __newval, struct __itimerval32 *__restrict __oldval),setitimer,(__which,__newval,__oldval))
#elif defined(__CRT_HAVE___setitimer)
__CREDIRECT(__ATTR_IN_OPT(2) __ATTR_OUT_OPT(3),int,__NOTHROW_NCX,__localdep_setitimer32,(int __which, struct __itimerval32 const *__restrict __newval, struct __itimerval32 *__restrict __oldval),__setitimer,(__which,__newval,__oldval))
#elif defined(__CRT_HAVE___libc_setitimer)
__CREDIRECT(__ATTR_IN_OPT(2) __ATTR_OUT_OPT(3),int,__NOTHROW_NCX,__localdep_setitimer32,(int __which, struct __itimerval32 const *__restrict __newval, struct __itimerval32 *__restrict __oldval),__libc_setitimer,(__which,__newval,__oldval))
#else /* ... */
#undef __local___localdep_setitimer32_defined
#endif /* !... */
#endif /* !__local___localdep_setitimer32_defined */
#ifndef __local___localdep_setitimer64_defined
#define __local___localdep_setitimer64_defined
#if defined(__CRT_HAVE_setitimer) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
__CREDIRECT(__ATTR_IN_OPT(2) __ATTR_OUT_OPT(3),int,__NOTHROW_NCX,__localdep_setitimer64,(int __which, struct __itimerval64 const *__newval, struct __itimerval64 *__oldval),setitimer,(__which,__newval,__oldval))
#elif defined(__CRT_HAVE___setitimer) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
__CREDIRECT(__ATTR_IN_OPT(2) __ATTR_OUT_OPT(3),int,__NOTHROW_NCX,__localdep_setitimer64,(int __which, struct __itimerval64 const *__newval, struct __itimerval64 *__oldval),__setitimer,(__which,__newval,__oldval))
#elif defined(__CRT_HAVE___libc_setitimer) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
__CREDIRECT(__ATTR_IN_OPT(2) __ATTR_OUT_OPT(3),int,__NOTHROW_NCX,__localdep_setitimer64,(int __which, struct __itimerval64 const *__newval, struct __itimerval64 *__oldval),__libc_setitimer,(__which,__newval,__oldval))
#elif defined(__CRT_HAVE_setitimer64)
__CREDIRECT(__ATTR_IN_OPT(2) __ATTR_OUT_OPT(3),int,__NOTHROW_NCX,__localdep_setitimer64,(int __which, struct __itimerval64 const *__newval, struct __itimerval64 *__oldval),setitimer64,(__which,__newval,__oldval))
#elif defined(__CRT_HAVE___setitimer64)
__CREDIRECT(__ATTR_IN_OPT(2) __ATTR_OUT_OPT(3),int,__NOTHROW_NCX,__localdep_setitimer64,(int __which, struct __itimerval64 const *__newval, struct __itimerval64 *__oldval),__setitimer64,(__which,__newval,__oldval))
#elif defined(__CRT_HAVE_setitimer) || defined(__CRT_HAVE___setitimer) || defined(__CRT_HAVE___libc_setitimer)
__NAMESPACE_LOCAL_END
#include <libc/local/sys.time/setitimer64.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_setitimer64 __LIBC_LOCAL_NAME(setitimer64)
#else /* ... */
#undef __local___localdep_setitimer64_defined
#endif /* !... */
#endif /* !__local___localdep_setitimer64_defined */
__LOCAL_LIBC(setitimer) __ATTR_IN_OPT(2) __ATTR_OUT_OPT(3) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(setitimer))(int __which, struct itimerval const *__newval, struct itimerval *__oldval) {
#if defined(__CRT_HAVE_setitimer) || defined(__CRT_HAVE___setitimer) || defined(__CRT_HAVE___libc_setitimer)
	int __result;
	struct __itimerval32 __old32;
	if (__newval) {
		struct __itimerval32 __new32;
		__new32.it_interval.tv_sec  = (__time32_t)__newval->it_interval.tv_sec;
		__new32.it_interval.tv_usec = __newval->it_interval.tv_usec;
		__new32.it_value.tv_sec     = (__time32_t)__newval->it_value.tv_sec;
		__new32.it_value.tv_usec    = __newval->it_value.tv_usec;
		__result = (__NAMESPACE_LOCAL_SYM __localdep_setitimer32)(__which, &__new32, __oldval ? &__old32 : __NULLPTR);
	} else {
		__result = (__NAMESPACE_LOCAL_SYM __localdep_setitimer32)(__which, __NULLPTR, __oldval ? &__old32 : __NULLPTR);
	}
	if (__likely(!__result) && __oldval) {
		__oldval->it_interval.tv_sec  = (__time64_t)__old32.it_interval.tv_sec;
		__oldval->it_interval.tv_usec = __old32.it_interval.tv_usec;
		__oldval->it_value.tv_sec     = (__time64_t)__old32.it_value.tv_sec;
		__oldval->it_value.tv_usec    = __old32.it_value.tv_usec;
	}
	return __result;
#else /* __CRT_HAVE_setitimer || __CRT_HAVE___setitimer || __CRT_HAVE___libc_setitimer */
	int __result;
	struct __itimerval64 __old64;
	if (__newval) {
		struct __itimerval64 __new64;
		__new64.it_interval.tv_sec  = (__time64_t)__newval->it_interval.tv_sec;
		__new64.it_interval.tv_usec = __newval->it_interval.tv_usec;
		__new64.it_value.tv_sec     = (__time64_t)__newval->it_value.tv_sec;
		__new64.it_value.tv_usec    = __newval->it_value.tv_usec;
		__result = (__NAMESPACE_LOCAL_SYM __localdep_setitimer64)(__which, &__new64, __oldval ? &__old64 : __NULLPTR);
	} else {
		__result = (__NAMESPACE_LOCAL_SYM __localdep_setitimer64)(__which, __NULLPTR, __oldval ? &__old64 : __NULLPTR);
	}
	if (__likely(!__result) && __oldval) {
		__oldval->it_interval.tv_sec  = (__time32_t)__old64.it_interval.tv_sec;
		__oldval->it_interval.tv_usec = __old64.it_interval.tv_usec;
		__oldval->it_value.tv_sec     = (__time32_t)__old64.it_value.tv_sec;
		__oldval->it_value.tv_usec    = __old64.it_value.tv_usec;
	}
	return __result;
#endif /* !__CRT_HAVE_setitimer && !__CRT_HAVE___setitimer && !__CRT_HAVE___libc_setitimer */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_setitimer_defined
#define __local___localdep_setitimer_defined
#define __localdep_setitimer __LIBC_LOCAL_NAME(setitimer)
#endif /* !__local___localdep_setitimer_defined */
#else /* __CRT_HAVE_setitimer64 || __CRT_HAVE___setitimer64 || __CRT_HAVE_setitimer || __CRT_HAVE___setitimer || __CRT_HAVE___libc_setitimer */
#undef __local_setitimer_defined
#endif /* !__CRT_HAVE_setitimer64 && !__CRT_HAVE___setitimer64 && !__CRT_HAVE_setitimer && !__CRT_HAVE___setitimer && !__CRT_HAVE___libc_setitimer */
#endif /* !__local_setitimer_defined */
