/* HASH CRC-32:0x42de8ebc */
/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_timer_settime64_defined
#ifdef __CRT_HAVE_timer_settime
#define __local_timer_settime64_defined 1
#include <bits/itimerspec.h>
#include <bits/itimerspec.h>
/* Dependency: "timer_settime32" from "time" */
#ifndef ____localdep_timer_settime32_defined
#define ____localdep_timer_settime32_defined 1
#ifdef __CRT_HAVE_timer_settime
/* Set timer TIMERID to VALUE, returning old value in OVALUE */
__CREDIRECT(__ATTR_NONNULL((3)),int,__NOTHROW_NCX,__localdep_timer_settime32,(timer_t __timerid, int __flags, struct __itimerspec32 const *__restrict __value, struct __itimerspec32 *__ovalue),timer_settime,(__timerid,__flags,__value,__ovalue))
#else /* LIBC: timer_settime */
#undef ____localdep_timer_settime32_defined
#endif /* timer_settime32... */
#endif /* !____localdep_timer_settime32_defined */

__NAMESPACE_LOCAL_BEGIN
/* Set timer TIMERID to VALUE, returning old value in OVALUE */
__LOCAL_LIBC(timer_settime64) __ATTR_NONNULL((3)) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(timer_settime64))(timer_t __timerid,
                                                             int __flags,
                                                             struct itimerspec64 const *__restrict __value,
                                                             struct itimerspec64 *__restrict __ovalue) {
#line 1271 "kos/src/libc/magic/time.c"
	int __result;
	struct __itimerspec32 __value32, __ovalue32;
	__value32.__it_interval.tv_sec  = (__time32_t)__value->__it_interval.tv_sec;
	__value32.__it_interval.tv_nsec = __value->__it_interval.tv_nsec;
	__value32.__it_value.tv_sec     = (__time32_t)__value->__it_value.tv_sec;
	__value32.__it_value.tv_nsec    = __value->__it_value.tv_nsec;
	__result = __localdep_timer_settime32(__timerid, __flags, &__value32, __ovalue ? &__ovalue32 : __NULLPTR);
	if (!__result && __ovalue) {
		__ovalue->__it_interval.tv_sec  = (__time64_t)__ovalue32.__it_interval.tv_sec;
		__ovalue->__it_interval.tv_nsec = __ovalue32.__it_interval.tv_nsec;
		__ovalue->__it_value.tv_sec     = (__time64_t)__ovalue32.__it_value.tv_sec;
		__ovalue->__it_value.tv_nsec    = __ovalue32.__it_value.tv_nsec;
	}
	return __result;
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE_timer_settime */
#endif /* !__local_timer_settime64_defined */
