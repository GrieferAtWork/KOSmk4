/* HASH CRC-32:0xb677402 */
/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_sched_rr_get_interval_defined
#if (defined(__CRT_HAVE_sched_rr_get_interval) || defined(__CRT_HAVE_sched_rr_get_interval64))
#define __local_sched_rr_get_interval_defined 1
/* Dependency: "sched_rr_get_interval32" from "sched" */
#ifndef ____localdep_sched_rr_get_interval32_defined
#define ____localdep_sched_rr_get_interval32_defined 1
#if defined(__CRT_HAVE_sched_rr_get_interval)
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_sched_rr_get_interval32,(__pid_t __pid, struct __timespec32 *__tms),sched_rr_get_interval,(__pid,__tms))
#else /* LIBC: sched_rr_get_interval */
#undef ____localdep_sched_rr_get_interval32_defined
#endif /* sched_rr_get_interval32... */
#endif /* !____localdep_sched_rr_get_interval32_defined */

/* Dependency: "sched_rr_get_interval64" from "sched" */
#ifndef ____localdep_sched_rr_get_interval64_defined
#define ____localdep_sched_rr_get_interval64_defined 1
#if defined(__CRT_HAVE_sched_rr_get_interval64)
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_sched_rr_get_interval64,(__pid_t __pid, struct __timespec64 *__tms),sched_rr_get_interval64,(__pid,__tms))
#elif defined(__CRT_HAVE_sched_rr_get_interval) && (__SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_sched_rr_get_interval64,(__pid_t __pid, struct __timespec64 *__tms),sched_rr_get_interval,(__pid,__tms))
#elif defined(__CRT_HAVE_sched_rr_get_interval)
#include <local/sched/sched_rr_get_interval64.h>
#define __localdep_sched_rr_get_interval64 (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sched_rr_get_interval64))
#else /* CUSTOM: sched_rr_get_interval64 */
#undef ____localdep_sched_rr_get_interval64_defined
#endif /* sched_rr_get_interval64... */
#endif /* !____localdep_sched_rr_get_interval64_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(sched_rr_get_interval) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(sched_rr_get_interval))(__pid_t __pid,
                                                                   struct __TM_TYPE(timespec) *__tms) {
#line 110 "kos/src/libc/magic/sched.c"
#ifdef __CRT_HAVE_sched_rr_get_interval
	struct __timespec32 __tms32;
	if (!__tms)
		return __localdep_sched_rr_get_interval32(__pid, __NULLPTR);
	__tms32.tv_sec  = (__time32_t)__tms->tv_sec;
	__tms32.tv_bsec = __tms->tv_bsec;
	return __localdep_sched_rr_get_interval32(__pid, &__tms32);
#else /* __CRT_HAVE_sched_rr_get_interval */
	struct __timespec64 __tms64;
	if (!__tms)
		return __localdep_sched_rr_get_interval64(__pid, __NULLPTR);
	__tms64.tv_sec  = (__time64_t)__tms->tv_sec;
	__tms64.tv_bsec = __tms->tv_bsec;
	return __localdep_sched_rr_get_interval64(__pid, &__tms64);
#endif /* !__CRT_HAVE_sched_rr_get_interval */
}
__NAMESPACE_LOCAL_END
#endif /* (defined(__CRT_HAVE_sched_rr_get_interval) || defined(__CRT_HAVE_sched_rr_get_interval64)) */
#endif /* !__local_sched_rr_get_interval_defined */
