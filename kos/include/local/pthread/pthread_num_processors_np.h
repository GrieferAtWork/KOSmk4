/* HASH CRC-32:0x4d7d1141 */
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
#ifndef __local_pthread_num_processors_np_defined
#ifdef __CRT_HAVE_sched_getaffinity
#define __local_pthread_num_processors_np_defined 1
#include <bits/sched.h>
/* Dependency: "sched_getaffinity" */
#ifndef ____localdep_sched_getaffinity_defined
#define ____localdep_sched_getaffinity_defined 1
#ifdef __CRT_HAVE_sched_getaffinity
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_sched_getaffinity,(__pid_t __pid, __SIZE_TYPE__ __cpusetsize, __cpu_set_t *__cpuset),sched_getaffinity,(__pid,__cpusetsize,__cpuset))
#else /* LIBC: sched_getaffinity */
#undef ____localdep_sched_getaffinity_defined
#endif /* sched_getaffinity... */
#endif /* !____localdep_sched_getaffinity_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(pthread_num_processors_np) __STDC_INT_AS_SIZE_T
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(pthread_num_processors_np))(void) {
#line 1413 "kos/src/libc/magic/pthread.c"
	__cpu_set_t __cset;
	if __unlikely(__localdep_sched_getaffinity(0, sizeof(__cset), &__cset) != 0)
		return 1;
	return (__STDC_INT_AS_SIZE_T)__CPU_COUNT_S(sizeof(__cset), &__cset);
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE_sched_getaffinity */
#endif /* !__local_pthread_num_processors_np_defined */
