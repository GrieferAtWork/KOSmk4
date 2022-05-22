/* HASH CRC-32:0xc2043082 */
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
#ifndef __local_pthread_set_num_processors_np_defined
#define __local_pthread_set_num_processors_np_defined
#include <__crt.h>
#ifdef __CRT_HAVE_sched_setaffinity
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_sched_setaffinity_defined
#define __local___localdep_sched_setaffinity_defined
__NAMESPACE_LOCAL_END
#include <bits/os/cpu_set.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_ACCESS_RO_OPT(3),int,__NOTHROW_NCX,__localdep_sched_setaffinity,(__pid_t __pid, __SIZE_TYPE__ __cpusetsize, struct __cpu_set_struct const *__cpuset),sched_setaffinity,(__pid,__cpusetsize,__cpuset))
#endif /* !__local___localdep_sched_setaffinity_defined */
__NAMESPACE_LOCAL_END
#include <bits/os/cpu_set.h>
#include <libc/errno.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(pthread_set_num_processors_np) __errno_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(pthread_set_num_processors_np))(int __n) {
	int __i, __result;
	struct __cpu_set_struct __cset;
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
	__result = (__NAMESPACE_LOCAL_SYM __localdep_sched_setaffinity)(0, sizeof(__cset), &__cset);
	if __unlikely(__result != 0)
		__result = __libc_geterrno_or(1);
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_pthread_set_num_processors_np_defined
#define __local___localdep_pthread_set_num_processors_np_defined
#define __localdep_pthread_set_num_processors_np __LIBC_LOCAL_NAME(pthread_set_num_processors_np)
#endif /* !__local___localdep_pthread_set_num_processors_np_defined */
#else /* __CRT_HAVE_sched_setaffinity */
#undef __local_pthread_set_num_processors_np_defined
#endif /* !__CRT_HAVE_sched_setaffinity */
#endif /* !__local_pthread_set_num_processors_np_defined */
