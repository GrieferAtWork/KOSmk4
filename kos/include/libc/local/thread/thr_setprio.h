/* HASH CRC-32:0xf4af77b */
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
#ifndef __local_thr_setprio_defined
#define __local_thr_setprio_defined
#include <__crt.h>
#if defined(__CRT_HAVE_pthread_setschedparam) && defined(__CRT_HAVE_pthread_getschedparam)
#include <bits/types.h>
#include <bits/crt/pthreadtypes.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_pthread_getschedparam_defined
#define __local___localdep_pthread_getschedparam_defined
__NAMESPACE_LOCAL_END
#include <bits/os/sched.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_OUT(2) __ATTR_OUT(3),__errno_t,__NOTHROW_NCX,__localdep_pthread_getschedparam,(__pthread_t __self, int *__restrict __policy, struct sched_param *__restrict __param),pthread_getschedparam,(__self,__policy,__param))
#endif /* !__local___localdep_pthread_getschedparam_defined */
#ifndef __local___localdep_pthread_setschedparam_defined
#define __local___localdep_pthread_setschedparam_defined
__NAMESPACE_LOCAL_END
#include <bits/os/sched.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN(3),__errno_t,__NOTHROW_NCX,__localdep_pthread_setschedparam,(__pthread_t __self, int __policy, struct sched_param const *__param),pthread_setschedparam,(__self,__policy,__param))
#endif /* !__local___localdep_pthread_setschedparam_defined */
__NAMESPACE_LOCAL_END
#include <bits/os/sched.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(thr_setprio) __errno_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(thr_setprio))(__pthread_t __thr, int __priority) {
	__errno_t __result;
	struct sched_param __param;
	int __policy;
	__result = (__NAMESPACE_LOCAL_SYM __localdep_pthread_getschedparam)(__thr, &__policy, &__param);
	if (__result == 0 && __param.sched_priority != __priority) {
		__param.sched_priority = __priority;
		__result = (__NAMESPACE_LOCAL_SYM __localdep_pthread_setschedparam)(__thr, __policy, &__param);
	}
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_thr_setprio_defined
#define __local___localdep_thr_setprio_defined
#define __localdep_thr_setprio __LIBC_LOCAL_NAME(thr_setprio)
#endif /* !__local___localdep_thr_setprio_defined */
#else /* __CRT_HAVE_pthread_setschedparam && __CRT_HAVE_pthread_getschedparam */
#undef __local_thr_setprio_defined
#endif /* !__CRT_HAVE_pthread_setschedparam || !__CRT_HAVE_pthread_getschedparam */
#endif /* !__local_thr_setprio_defined */
