/* HASH CRC-32:0xbe742eeb */
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
#ifndef __local_sched_rr_get_interval64_defined
#define __local_sched_rr_get_interval64_defined 1
#include <__crt.h>
#ifdef __CRT_HAVE_sched_rr_get_interval
#include <bits/types.h>
#include <bits/os/timespec.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: sched_rr_get_interval32 from sched */
#ifndef __local___localdep_sched_rr_get_interval32_defined
#define __local___localdep_sched_rr_get_interval32_defined 1
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_sched_rr_get_interval32,(__pid_t __pid, struct __timespec32 *__tms),sched_rr_get_interval,(__pid,__tms))
#endif /* !__local___localdep_sched_rr_get_interval32_defined */
__LOCAL_LIBC(sched_rr_get_interval64) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(sched_rr_get_interval64))(__pid_t __pid, struct __timespec64 *__tms) {
	struct __timespec32 __tms32;
	if (!__tms)
		return __localdep_sched_rr_get_interval32(__pid, __NULLPTR);
	__tms32.tv_sec  = (__time32_t)__tms->tv_sec;
	__tms32.tv_nsec = __tms->tv_nsec;
	return __localdep_sched_rr_get_interval32(__pid, &__tms32);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_sched_rr_get_interval64_defined
#define __local___localdep_sched_rr_get_interval64_defined 1
#define __localdep_sched_rr_get_interval64 __LIBC_LOCAL_NAME(sched_rr_get_interval64)
#endif /* !__local___localdep_sched_rr_get_interval64_defined */
#else /* __CRT_HAVE_sched_rr_get_interval */
#undef __local_sched_rr_get_interval64_defined
#endif /* !__CRT_HAVE_sched_rr_get_interval */
#endif /* !__local_sched_rr_get_interval64_defined */
