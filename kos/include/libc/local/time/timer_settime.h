/* HASH CRC-32:0xe69467ef */
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
#ifndef __local_timer_settime_defined
#define __local_timer_settime_defined
#include <__crt.h>
#include <bits/types.h>
#if defined(__CRT_HAVE_timer_settime64) || defined(__CRT_HAVE_timer_settime)
#include <features.h>
#include <bits/os/itimerspec.h>
__NAMESPACE_LOCAL_BEGIN
#if !defined(__local___localdep_timer_settime32_defined) && defined(__CRT_HAVE_timer_settime)
#define __local___localdep_timer_settime32_defined
__CREDIRECT(__ATTR_NONNULL((3)),int,__NOTHROW_NCX,__localdep_timer_settime32,(__timer_t __timerid, __STDC_INT_AS_UINT_T __flags, struct __itimerspec32 const *__restrict ___value, struct __itimerspec32 *__ovalue),timer_settime,(__timerid,__flags,___value,__ovalue))
#endif /* !__local___localdep_timer_settime32_defined && __CRT_HAVE_timer_settime */
#ifndef __local___localdep_timer_settime64_defined
#define __local___localdep_timer_settime64_defined
#if defined(__CRT_HAVE_timer_settime) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
__CREDIRECT(__ATTR_NONNULL((3)),int,__NOTHROW_NCX,__localdep_timer_settime64,(__timer_t __timerid, __STDC_INT_AS_UINT_T __flags, struct __itimerspec64 const *__restrict ___value, struct __itimerspec64 *__restrict __ovalue),timer_settime,(__timerid,__flags,___value,__ovalue))
#elif defined(__CRT_HAVE_timer_settime64)
__CREDIRECT(__ATTR_NONNULL((3)),int,__NOTHROW_NCX,__localdep_timer_settime64,(__timer_t __timerid, __STDC_INT_AS_UINT_T __flags, struct __itimerspec64 const *__restrict ___value, struct __itimerspec64 *__restrict __ovalue),timer_settime64,(__timerid,__flags,___value,__ovalue))
#elif defined(__CRT_HAVE_timer_settime)
__NAMESPACE_LOCAL_END
#include <libc/local/time/timer_settime64.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_timer_settime64 __LIBC_LOCAL_NAME(timer_settime64)
#else /* ... */
#undef __local___localdep_timer_settime64_defined
#endif /* !... */
#endif /* !__local___localdep_timer_settime64_defined */
__LOCAL_LIBC(timer_settime) __ATTR_NONNULL((3)) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(timer_settime))(__timer_t __timerid, __STDC_INT_AS_UINT_T __flags, struct itimerspec const *__restrict ___value, struct itimerspec *__restrict __ovalue) {
#ifdef __CRT_HAVE_timer_settime
	int __result;
	struct __itimerspec32 __value32, __ovalue32;
	__value32.__it_interval.tv_sec  = (__time32_t)___value->__it_interval.tv_sec;
	__value32.__it_interval.tv_nsec = ___value->__it_interval.tv_nsec;
	__value32.__it_value.tv_sec     = (__time32_t)___value->__it_value.tv_sec;
	__value32.__it_value.tv_nsec    = ___value->__it_value.tv_nsec;
	__result = (__NAMESPACE_LOCAL_SYM __localdep_timer_settime32)(__timerid, __flags, &__value32, __ovalue ? &__ovalue32 : __NULLPTR);
	if (!__result && __ovalue) {
		__ovalue->__it_interval.tv_sec  = (__time64_t)__ovalue32.__it_interval.tv_sec;
		__ovalue->__it_interval.tv_nsec = __ovalue32.__it_interval.tv_nsec;
		__ovalue->__it_value.tv_sec     = (__time64_t)__ovalue32.__it_value.tv_sec;
		__ovalue->__it_value.tv_nsec    = __ovalue32.__it_value.tv_nsec;
	}
	return __result;
#else /* __CRT_HAVE_timer_settime */
	int __result;
	struct __itimerspec64 __value64, __ovalue64;
	__value64.__it_interval.tv_sec  = (__time64_t)___value->__it_interval.tv_sec;
	__value64.__it_interval.tv_nsec = ___value->__it_interval.tv_nsec;
	__value64.__it_value.tv_sec     = (__time64_t)___value->__it_value.tv_sec;
	__value64.__it_value.tv_nsec    = ___value->__it_value.tv_nsec;
	__result = (__NAMESPACE_LOCAL_SYM __localdep_timer_settime64)(__timerid, __flags, &__value64, __ovalue ? &__ovalue64 : __NULLPTR);
	if (!__result && __ovalue) {
		__ovalue->__it_interval.tv_sec  = (__time32_t)__ovalue64.__it_interval.tv_sec;
		__ovalue->__it_interval.tv_nsec = __ovalue64.__it_interval.tv_nsec;
		__ovalue->__it_value.tv_sec     = (__time32_t)__ovalue64.__it_value.tv_sec;
		__ovalue->__it_value.tv_nsec    = __ovalue64.__it_value.tv_nsec;
	}
	return __result;
#endif /* !__CRT_HAVE_timer_settime */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_timer_settime_defined
#define __local___localdep_timer_settime_defined
#define __localdep_timer_settime __LIBC_LOCAL_NAME(timer_settime)
#endif /* !__local___localdep_timer_settime_defined */
#else /* __CRT_HAVE_timer_settime64 || __CRT_HAVE_timer_settime */
#undef __local_timer_settime_defined
#endif /* !__CRT_HAVE_timer_settime64 && !__CRT_HAVE_timer_settime */
#endif /* !__local_timer_settime_defined */
