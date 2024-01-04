/* HASH CRC-32:0xaa99d674 */
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
#ifndef __local_timerfd_settime64_defined
#define __local_timerfd_settime64_defined
#include <__crt.h>
#ifdef __CRT_HAVE_timerfd_settime
#include <features.h>
#include <bits/types.h>
#include <bits/os/itimerspec.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_timerfd_settime32_defined
#define __local___localdep_timerfd_settime32_defined
__CREDIRECT(__ATTR_FDARG(1) __ATTR_IN(3) __ATTR_OUT_OPT(4),int,__NOTHROW_NCX,__localdep_timerfd_settime32,(__fd_t __ufd, __STDC_INT_AS_UINT_T __flags, struct __itimerspec32 const *__utmr, struct __itimerspec32 *__otmr),timerfd_settime,(__ufd,__flags,__utmr,__otmr))
#endif /* !__local___localdep_timerfd_settime32_defined */
__LOCAL_LIBC(timerfd_settime64) __ATTR_FDARG(1) __ATTR_IN(3) __ATTR_OUT_OPT(4) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(timerfd_settime64))(__fd_t __ufd, __STDC_INT_AS_UINT_T __flags, struct __itimerspec64 const *__utmr, struct __itimerspec64 *__otmr) {
	int __result;
	struct __itimerspec32 __utmr32, __otmr32;
	__utmr32.__it_interval.tv_sec  = (__time32_t)__utmr->__it_interval.tv_sec;
	__utmr32.__it_interval.tv_nsec = __utmr->__it_interval.tv_nsec;
	__utmr32.__it_value.tv_sec     = (__time32_t)__utmr->__it_value.tv_sec;
	__utmr32.__it_value.tv_nsec    = __utmr->__it_value.tv_nsec;
	__result = (__NAMESPACE_LOCAL_SYM __localdep_timerfd_settime32)(__ufd, __flags, &__utmr32, __otmr ? &__otmr32 : __NULLPTR);
	if (__result == 0 && __otmr) {
		__otmr->__it_interval.tv_sec  = (__time64_t)__otmr32.__it_interval.tv_sec;
		__otmr->__it_interval.tv_nsec = __otmr32.__it_interval.tv_nsec;
		__otmr->__it_value.tv_sec     = (__time64_t)__otmr32.__it_value.tv_sec;
		__otmr->__it_value.tv_nsec    = __otmr32.__it_value.tv_nsec;
	}
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_timerfd_settime64_defined
#define __local___localdep_timerfd_settime64_defined
#define __localdep_timerfd_settime64 __LIBC_LOCAL_NAME(timerfd_settime64)
#endif /* !__local___localdep_timerfd_settime64_defined */
#else /* __CRT_HAVE_timerfd_settime */
#undef __local_timerfd_settime64_defined
#endif /* !__CRT_HAVE_timerfd_settime */
#endif /* !__local_timerfd_settime64_defined */
