/* HASH CRC-32:0xe05328cd */
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
#ifndef __local_timer_gettime64_defined
#define __local_timer_gettime64_defined
#include <__crt.h>
#ifdef __CRT_HAVE_timer_gettime
#include <bits/os/itimerspec.h>
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_timer_gettime32_defined
#define __local___localdep_timer_gettime32_defined
__CREDIRECT(__ATTR_OUT_OPT(2),int,__NOTHROW_NCX,__localdep_timer_gettime32,(__timer_t __timerid, struct itimerspec *___value),timer_gettime,(__timerid,___value))
#endif /* !__local___localdep_timer_gettime32_defined */
__LOCAL_LIBC(timer_gettime64) __ATTR_OUT(2) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(timer_gettime64))(__timer_t __timerid, struct __itimerspec64 *___value) {
	int __result;
	struct __itimerspec32 __value32;
	__result = (__NAMESPACE_LOCAL_SYM __localdep_timer_gettime32)(__timerid, &__value32);
	if (__result == 0) {
		___value->__it_interval.tv_sec  = (__time64_t)__value32.__it_interval.tv_sec;
		___value->__it_interval.tv_nsec = __value32.__it_interval.tv_nsec;
		___value->__it_value.tv_sec     = (__time64_t)__value32.__it_value.tv_sec;
		___value->__it_value.tv_nsec    = __value32.__it_value.tv_nsec;
	}
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_timer_gettime64_defined
#define __local___localdep_timer_gettime64_defined
#define __localdep_timer_gettime64 __LIBC_LOCAL_NAME(timer_gettime64)
#endif /* !__local___localdep_timer_gettime64_defined */
#else /* __CRT_HAVE_timer_gettime */
#undef __local_timer_gettime64_defined
#endif /* !__CRT_HAVE_timer_gettime */
#endif /* !__local_timer_gettime64_defined */
