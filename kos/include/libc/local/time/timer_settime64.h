/* HASH CRC-32:0xeba0e14b */
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
#ifndef __local_timer_settime64_defined
#define __local_timer_settime64_defined
#include <__crt.h>
#ifdef __CRT_HAVE_timer_settime
#include <features.h>
#include <bits/os/itimerspec.h>
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_timer_settime32_defined
#define __local___localdep_timer_settime32_defined
__CREDIRECT(__ATTR_IN(3) __ATTR_OUT_OPT(4),int,__NOTHROW_NCX,__localdep_timer_settime32,(__timer_t __timerid, __STDC_INT_AS_UINT_T __flags, struct __itimerspec32 const *__restrict ___value, struct __itimerspec32 *__ovalue),timer_settime,(__timerid,__flags,___value,__ovalue))
#endif /* !__local___localdep_timer_settime32_defined */
__LOCAL_LIBC(timer_settime64) __ATTR_IN(3) __ATTR_OUT_OPT(4) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(timer_settime64))(__timer_t __timerid, __STDC_INT_AS_UINT_T __flags, struct __itimerspec64 const *__restrict ___value, struct __itimerspec64 *__restrict __ovalue) {
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
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_timer_settime64_defined
#define __local___localdep_timer_settime64_defined
#define __localdep_timer_settime64 __LIBC_LOCAL_NAME(timer_settime64)
#endif /* !__local___localdep_timer_settime64_defined */
#else /* __CRT_HAVE_timer_settime */
#undef __local_timer_settime64_defined
#endif /* !__CRT_HAVE_timer_settime */
#endif /* !__local_timer_settime64_defined */
