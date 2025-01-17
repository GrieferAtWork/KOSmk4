/* HASH CRC-32:0x5bec042e */
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
#ifndef __local_pthread_num_processors_np_defined
#define __local_pthread_num_processors_np_defined
#include <__crt.h>
#ifdef __CRT_HAVE_sched_getaffinity
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_sched_getaffinity_defined
#define __local___localdep_sched_getaffinity_defined
__NAMESPACE_LOCAL_END
#include <bits/types.h>
#include <bits/os/cpu_set.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_OUT_OPT(3),int,__NOTHROW_NCX,__localdep_sched_getaffinity,(__pid_t __pid, __SIZE_TYPE__ __cpusetsize, struct __cpu_set_struct *__cpuset),sched_getaffinity,(__pid,__cpusetsize,__cpuset))
#endif /* !__local___localdep_sched_getaffinity_defined */
__NAMESPACE_LOCAL_END
#include <bits/os/cpu_set.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(pthread_num_processors_np) __ATTR_WUNUSED __STDC_INT_AS_SIZE_T
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(pthread_num_processors_np))(void) {
	struct __cpu_set_struct __cset;
	if __unlikely((__NAMESPACE_LOCAL_SYM __localdep_sched_getaffinity)(0, sizeof(__cset), &__cset) != 0)
		return 1;
	return (__STDC_INT_AS_SIZE_T)__CPU_COUNT_S(sizeof(__cset), &__cset);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_pthread_num_processors_np_defined
#define __local___localdep_pthread_num_processors_np_defined
#define __localdep_pthread_num_processors_np __LIBC_LOCAL_NAME(pthread_num_processors_np)
#endif /* !__local___localdep_pthread_num_processors_np_defined */
#else /* __CRT_HAVE_sched_getaffinity */
#undef __local_pthread_num_processors_np_defined
#endif /* !__CRT_HAVE_sched_getaffinity */
#endif /* !__local_pthread_num_processors_np_defined */
