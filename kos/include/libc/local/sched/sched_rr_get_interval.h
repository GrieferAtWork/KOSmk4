/* HASH CRC-32:0xc580bd46 */
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
#ifndef __local_sched_rr_get_interval_defined
#define __local_sched_rr_get_interval_defined
#include <__crt.h>
#include <bits/types.h>
#if defined(__CRT_HAVE_sched_rr_get_interval64) || defined(__CRT_HAVE_sched_rr_get_interval) || defined(__CRT_HAVE___sched_rr_get_interval) || defined(__CRT_HAVE___libc_sched_rr_get_interval)
#include <bits/os/timespec.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_sched_rr_get_interval32_defined
#define __local___localdep_sched_rr_get_interval32_defined
#ifdef __CRT_HAVE_sched_rr_get_interval
__CREDIRECT(__ATTR_ACCESS_WR_OPT(2),int,__NOTHROW_NCX,__localdep_sched_rr_get_interval32,(__pid_t __pid, struct __timespec32 *__tms),sched_rr_get_interval,(__pid,__tms))
#elif defined(__CRT_HAVE___sched_rr_get_interval)
__CREDIRECT(__ATTR_ACCESS_WR_OPT(2),int,__NOTHROW_NCX,__localdep_sched_rr_get_interval32,(__pid_t __pid, struct __timespec32 *__tms),__sched_rr_get_interval,(__pid,__tms))
#elif defined(__CRT_HAVE___libc_sched_rr_get_interval)
__CREDIRECT(__ATTR_ACCESS_WR_OPT(2),int,__NOTHROW_NCX,__localdep_sched_rr_get_interval32,(__pid_t __pid, struct __timespec32 *__tms),__libc_sched_rr_get_interval,(__pid,__tms))
#else /* ... */
#undef __local___localdep_sched_rr_get_interval32_defined
#endif /* !... */
#endif /* !__local___localdep_sched_rr_get_interval32_defined */
#ifndef __local___localdep_sched_rr_get_interval64_defined
#define __local___localdep_sched_rr_get_interval64_defined
#if defined(__CRT_HAVE_sched_rr_get_interval) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
__CREDIRECT(__ATTR_ACCESS_WR_OPT(2),int,__NOTHROW_NCX,__localdep_sched_rr_get_interval64,(__pid_t __pid, struct __timespec64 *__tms),sched_rr_get_interval,(__pid,__tms))
#elif defined(__CRT_HAVE___sched_rr_get_interval) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
__CREDIRECT(__ATTR_ACCESS_WR_OPT(2),int,__NOTHROW_NCX,__localdep_sched_rr_get_interval64,(__pid_t __pid, struct __timespec64 *__tms),__sched_rr_get_interval,(__pid,__tms))
#elif defined(__CRT_HAVE___libc_sched_rr_get_interval) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
__CREDIRECT(__ATTR_ACCESS_WR_OPT(2),int,__NOTHROW_NCX,__localdep_sched_rr_get_interval64,(__pid_t __pid, struct __timespec64 *__tms),__libc_sched_rr_get_interval,(__pid,__tms))
#elif defined(__CRT_HAVE_sched_rr_get_interval64)
__CREDIRECT(__ATTR_ACCESS_WR_OPT(2),int,__NOTHROW_NCX,__localdep_sched_rr_get_interval64,(__pid_t __pid, struct __timespec64 *__tms),sched_rr_get_interval64,(__pid,__tms))
#elif defined(__CRT_HAVE_sched_rr_get_interval) || defined(__CRT_HAVE___sched_rr_get_interval) || defined(__CRT_HAVE___libc_sched_rr_get_interval)
__NAMESPACE_LOCAL_END
#include <libc/local/sched/sched_rr_get_interval64.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_sched_rr_get_interval64 __LIBC_LOCAL_NAME(sched_rr_get_interval64)
#else /* ... */
#undef __local___localdep_sched_rr_get_interval64_defined
#endif /* !... */
#endif /* !__local___localdep_sched_rr_get_interval64_defined */
__LOCAL_LIBC(sched_rr_get_interval) __ATTR_ACCESS_WR_OPT(2) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(sched_rr_get_interval))(__pid_t __pid, struct timespec *__tms) {
#if defined(__CRT_HAVE_sched_rr_get_interval) || defined(__CRT_HAVE___sched_rr_get_interval) || defined(__CRT_HAVE___libc_sched_rr_get_interval)
	struct __timespec32 __tms32;
	if (!__tms)
		return (__NAMESPACE_LOCAL_SYM __localdep_sched_rr_get_interval32)(__pid, __NULLPTR);
	__tms32.tv_sec  = (__time32_t)__tms->tv_sec;
	__tms32.tv_nsec = __tms->tv_nsec;
	return (__NAMESPACE_LOCAL_SYM __localdep_sched_rr_get_interval32)(__pid, &__tms32);
#else /* __CRT_HAVE_sched_rr_get_interval || __CRT_HAVE___sched_rr_get_interval || __CRT_HAVE___libc_sched_rr_get_interval */
	struct __timespec64 __tms64;
	if (!__tms)
		return (__NAMESPACE_LOCAL_SYM __localdep_sched_rr_get_interval64)(__pid, __NULLPTR);
	__tms64.tv_sec  = (__time64_t)__tms->tv_sec;
	__tms64.tv_nsec = __tms->tv_nsec;
	return (__NAMESPACE_LOCAL_SYM __localdep_sched_rr_get_interval64)(__pid, &__tms64);
#endif /* !__CRT_HAVE_sched_rr_get_interval && !__CRT_HAVE___sched_rr_get_interval && !__CRT_HAVE___libc_sched_rr_get_interval */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_sched_rr_get_interval_defined
#define __local___localdep_sched_rr_get_interval_defined
#define __localdep_sched_rr_get_interval __LIBC_LOCAL_NAME(sched_rr_get_interval)
#endif /* !__local___localdep_sched_rr_get_interval_defined */
#else /* __CRT_HAVE_sched_rr_get_interval64 || __CRT_HAVE_sched_rr_get_interval || __CRT_HAVE___sched_rr_get_interval || __CRT_HAVE___libc_sched_rr_get_interval */
#undef __local_sched_rr_get_interval_defined
#endif /* !__CRT_HAVE_sched_rr_get_interval64 && !__CRT_HAVE_sched_rr_get_interval && !__CRT_HAVE___sched_rr_get_interval && !__CRT_HAVE___libc_sched_rr_get_interval */
#endif /* !__local_sched_rr_get_interval_defined */
