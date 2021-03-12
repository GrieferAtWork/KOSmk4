/* HASH CRC-32:0xe51c05ed */
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
#ifndef __local_timer_gettime_defined
#define __local_timer_gettime_defined 1
#include <__crt.h>
#if defined(__CRT_HAVE_timer_gettime64) || defined(__CRT_HAVE_timer_gettime)
#include <bits/os/itimerspec.h>
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: timer_gettime32 from time */
#if !defined(__local___localdep_timer_gettime32_defined) && defined(__CRT_HAVE_timer_gettime)
#define __local___localdep_timer_gettime32_defined 1
/* Get current value of timer `timerid' and store it in `value' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,__localdep_timer_gettime32,(__timer_t __timerid, struct itimerspec *__value),timer_gettime,(__timerid,__value))
#endif /* !__local___localdep_timer_gettime32_defined && __CRT_HAVE_timer_gettime */
/* Dependency: timer_gettime64 from time */
#ifndef __local___localdep_timer_gettime64_defined
#define __local___localdep_timer_gettime64_defined 1
#ifdef __CRT_HAVE_timer_gettime64
/* Get current value of timer `timerid' and store it in `value' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,__localdep_timer_gettime64,(__timer_t __timerid, struct __itimerspec64 *__value),timer_gettime64,(__timerid,__value))
#elif defined(__CRT_HAVE_timer_gettime) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* Get current value of timer `timerid' and store it in `value' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,__localdep_timer_gettime64,(__timer_t __timerid, struct __itimerspec64 *__value),timer_gettime,(__timerid,__value))
#elif defined(__CRT_HAVE_timer_gettime)
__NAMESPACE_LOCAL_END
#include <libc/local/time/timer_gettime64.h>
__NAMESPACE_LOCAL_BEGIN
/* Get current value of timer `timerid' and store it in `value' */
#define __localdep_timer_gettime64 __LIBC_LOCAL_NAME(timer_gettime64)
#else /* ... */
#undef __local___localdep_timer_gettime64_defined
#endif /* !... */
#endif /* !__local___localdep_timer_gettime64_defined */
/* Get current value of timer `timerid' and store it in `value' */
__LOCAL_LIBC(timer_gettime) __ATTR_NONNULL((2)) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(timer_gettime))(__timer_t __timerid, struct itimerspec *__value) {
#ifdef __CRT_HAVE_timer_gettime
	int __result;
	struct __itimerspec32 __value32;
	__result = __localdep_timer_gettime32(__timerid, &__value32);
	if (!__result) {
		__value->__it_interval.tv_sec  = (__time64_t)__value32.__it_interval.tv_sec;
		__value->__it_interval.tv_nsec = __value32.__it_interval.tv_nsec;
		__value->__it_value.tv_sec     = (__time64_t)__value32.__it_value.tv_sec;
		__value->__it_value.tv_nsec    = __value32.__it_value.tv_nsec;
	}
	return __result;
#else /* __CRT_HAVE_timer_gettime */
	int __result;
	struct __itimerspec64 __value64;
	__result = __localdep_timer_gettime64(__timerid, &__value64);
	if (!__result) {
		__value->__it_interval.tv_sec  = (__time32_t)__value64.__it_interval.tv_sec;
		__value->__it_interval.tv_nsec = __value64.__it_interval.tv_nsec;
		__value->__it_value.tv_sec     = (__time32_t)__value64.__it_value.tv_sec;
		__value->__it_value.tv_nsec    = __value64.__it_value.tv_nsec;
	}
	return __result;
#endif /* !__CRT_HAVE_timer_gettime */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_timer_gettime_defined
#define __local___localdep_timer_gettime_defined 1
#define __localdep_timer_gettime __LIBC_LOCAL_NAME(timer_gettime)
#endif /* !__local___localdep_timer_gettime_defined */
#else /* __CRT_HAVE_timer_gettime64 || __CRT_HAVE_timer_gettime */
#undef __local_timer_gettime_defined
#endif /* !__CRT_HAVE_timer_gettime64 && !__CRT_HAVE_timer_gettime */
#endif /* !__local_timer_gettime_defined */
