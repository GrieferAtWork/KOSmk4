/* HASH CRC-32:0xe741b38c */
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_mtx_timedlock64_defined
#if defined(__CRT_HAVE_pthread_mutex_timedlock) || defined(__CRT_HAVE_pthread_mutex_timedlock64)
#define __local_mtx_timedlock64_defined 1
#include <bits/pthreadtypes.h>
#include <bits/timespec.h>
#include <bits/threads.h>

#include <bits/pthreadtypes.h>
/* Dependency: "pthread_mutex_timedlock64" from "pthread" */
#ifndef ____localdep_pthread_mutex_timedlock64_defined
#define ____localdep_pthread_mutex_timedlock64_defined 1
#ifdef __CRT_HAVE_pthread_mutex_timedlock64
/* Wait until lock becomes available, or specified time passes */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,__localdep_pthread_mutex_timedlock64,(__pthread_mutex_t *__restrict __mutex, struct __timespec64 const *__restrict __abstime),pthread_mutex_timedlock64,(__mutex,__abstime))
#elif defined(__CRT_HAVE_pthread_mutex_timedlock) && (__SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* Wait until lock becomes available, or specified time passes */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,__localdep_pthread_mutex_timedlock64,(__pthread_mutex_t *__restrict __mutex, struct __timespec64 const *__restrict __abstime),pthread_mutex_timedlock,(__mutex,__abstime))
#elif defined(__CRT_HAVE_pthread_mutex_timedlock)
#include <local/pthread/pthread_mutex_timedlock64.h>
/* Wait until lock becomes available, or specified time passes */
#define __localdep_pthread_mutex_timedlock64 (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pthread_mutex_timedlock64))
#else /* CUSTOM: pthread_mutex_timedlock64 */
#undef ____localdep_pthread_mutex_timedlock64_defined
#endif /* pthread_mutex_timedlock64... */
#endif /* !____localdep_pthread_mutex_timedlock64_defined */

__NAMESPACE_LOCAL_BEGIN
/* Block the current thread until the mutex pointed by MUTEX
 * is unlocked or time pointed by TIME_POINT is reached.
 * In case the mutex is unlock, the current thread will not be blocked
 * s.a. `pthread_mutex_timedlock()' */
__LOCAL_LIBC(mtx_timedlock64) __ATTR_NONNULL((1, 2)) int
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(mtx_timedlock64))(__mtx_t *__restrict __mutex,
                                                             struct __timespec64 const *__restrict __time_point) {
#line 309 "kos/src/libc/magic/threads.c"
	int __error;
	__error = __localdep_pthread_mutex_timedlock64((__pthread_mutex_t *)__mutex, __time_point);
	if __likely(!__error)
		return 0; /* thrd_success */
	return 2; /* thrd_error */
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE_pthread_mutex_timedlock || __CRT_HAVE_pthread_mutex_timedlock64 */
#endif /* !__local_mtx_timedlock64_defined */
