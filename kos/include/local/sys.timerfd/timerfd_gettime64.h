/* HASH CRC-32:0x83832a1 */
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
#ifndef __local_timerfd_gettime64_defined
#define __local_timerfd_gettime64_defined 1
#include <__crt.h>
#ifdef __CRT_HAVE_timerfd_gettime
__NAMESPACE_LOCAL_BEGIN
/* Dependency: timerfd_gettime32 from sys.timerfd */
#ifndef __local___localdep_timerfd_gettime32_defined
#define __local___localdep_timerfd_gettime32_defined 1
/* Return the next expiration time of UFD */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,__localdep_timerfd_gettime32,(__fd_t __ufd, struct __itimerspec32 *__restrict __otmr),timerfd_gettime,(__ufd,__otmr))
#endif /* !__local___localdep_timerfd_gettime32_defined */
/* Return the next expiration time of UFD */
__LOCAL_LIBC(timerfd_gettime64) __ATTR_NONNULL((2)) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(timerfd_gettime64))(__fd_t __ufd, struct __itimerspec64 *__restrict __otmr) {
	int __result;
	struct __itimerspec32 __otmr32;
	__result = __localdep_timerfd_gettime32(__timerid, &__otmr32);
	if (!__result) {
		__otmr->__it_interval.tv_sec  = (__time64_t)__otmr32.__it_interval.tv_sec;
		__otmr->__it_interval.tv_nsec = __otmr32.__it_interval.tv_nsec;
		__otmr->__it_value.tv_sec     = (__time64_t)__otmr32.__it_value.tv_sec;
		__otmr->__it_value.tv_nsec    = __otmr32.__it_value.tv_nsec;
	}
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_timerfd_gettime64_defined
#define __local___localdep_timerfd_gettime64_defined 1
#define __localdep_timerfd_gettime64 __LIBC_LOCAL_NAME(timerfd_gettime64)
#endif /* !__local___localdep_timerfd_gettime64_defined */
#else /* __CRT_HAVE_timerfd_gettime */
#undef __local_timerfd_gettime64_defined
#endif /* !__CRT_HAVE_timerfd_gettime */
#endif /* !__local_timerfd_gettime64_defined */
