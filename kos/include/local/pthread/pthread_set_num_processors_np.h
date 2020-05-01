/* HASH CRC-32:0x17fa5494 */
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
#ifndef __local_pthread_set_num_processors_np_defined
#ifdef __CRT_HAVE_sched_setaffinity
#define __local_pthread_set_num_processors_np_defined 1
#include <__crt.h>
#include <bits/sched.h>

#include <parts/errno.h>
/* Dependency: "sched_setaffinity" */
#ifndef ____localdep_sched_setaffinity_defined
#define ____localdep_sched_setaffinity_defined 1
#ifdef __CRT_HAVE_sched_setaffinity
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_sched_setaffinity,(__pid_t __pid, __SIZE_TYPE__ __cpusetsize, __cpu_set_t const *__cpuset),sched_setaffinity,(__pid,__cpusetsize,__cpuset))
#else /* LIBC: sched_setaffinity */
#undef ____localdep_sched_setaffinity_defined
#endif /* sched_setaffinity... */
#endif /* !____localdep_sched_setaffinity_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(pthread_set_num_processors_np) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(pthread_set_num_processors_np))(int __n) {
#line 1423 "kos/src/libc/magic/pthread.c"
	int __i, __result;
	__cpu_set_t __cset;
	if (__n < 1) {
#ifdef __EINVAL
		return __EINVAL;
#else /* __EINVAL */
		return 1;
#endif /* !__EINVAL */
	}
	__CPU_ZERO_S(sizeof(__cset), &__cset);
	for (__i = 0; __i < __n; ++__i) {
		if (!__CPU_SET_S(__i, sizeof(__cset), &__cset))
			break;
	}
	__result = __localdep_sched_setaffinity(0, sizeof(__cset), &__cset);
	if __unlikely(__result != 0)
		__result = __libc_geterrno_or(1);
	return __result;
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE_sched_setaffinity */
#endif /* !__local_pthread_set_num_processors_np_defined */
