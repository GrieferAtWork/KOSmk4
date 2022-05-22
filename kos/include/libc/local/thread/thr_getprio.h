/* HASH CRC-32:0xe5966a02 */
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
#ifndef __local_thr_getprio_defined
#define __local_thr_getprio_defined
#include <__crt.h>
#ifdef __CRT_HAVE_pthread_getschedparam
#include <bits/types.h>
#include <bits/crt/pthreadtypes.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_pthread_getschedparam_defined
#define __local___localdep_pthread_getschedparam_defined
__NAMESPACE_LOCAL_END
#include <bits/os/sched.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_ACCESS_WR(2) __ATTR_ACCESS_WR(3),__errno_t,__NOTHROW_NCX,__localdep_pthread_getschedparam,(__pthread_t __target_thread, int *__restrict __policy, struct sched_param *__restrict __param),pthread_getschedparam,(__target_thread,__policy,__param))
#endif /* !__local___localdep_pthread_getschedparam_defined */
__NAMESPACE_LOCAL_END
#include <bits/os/sched.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(thr_getprio) __ATTR_NONNULL((2)) __errno_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(thr_getprio))(__pthread_t __thr, int *__p_priority) {
	__errno_t __result;
	struct sched_param __param;
	int __policy;
	__result = (__NAMESPACE_LOCAL_SYM __localdep_pthread_getschedparam)(__thr, &__policy, &__param);
	if (__result == 0)
		*__p_priority = __param.sched_priority;
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_thr_getprio_defined
#define __local___localdep_thr_getprio_defined
#define __localdep_thr_getprio __LIBC_LOCAL_NAME(thr_getprio)
#endif /* !__local___localdep_thr_getprio_defined */
#else /* __CRT_HAVE_pthread_getschedparam */
#undef __local_thr_getprio_defined
#endif /* !__CRT_HAVE_pthread_getschedparam */
#endif /* !__local_thr_getprio_defined */
