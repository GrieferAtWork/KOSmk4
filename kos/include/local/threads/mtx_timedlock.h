/* HASH CRC-32:0x4a49d24c */
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
#ifndef __local_mtx_timedlock_defined
#define __local_mtx_timedlock_defined 1
#include <__crt.h>
#if defined(__CRT_HAVE_pthread_mutex_timedlock64) || defined(__CRT_HAVE_pthread_mutex_timedlock)
#include <bits/crt/threads.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: pthread_mutex_timedlock from pthread */
#ifndef __local___localdep_pthread_mutex_timedlock_defined
#define __local___localdep_pthread_mutex_timedlock_defined 1
#if defined(__CRT_HAVE_pthread_mutex_timedlock64) && defined(__USE_TIME_BITS64)
__NAMESPACE_LOCAL_END
#include <bits/crt/pthreadtypes.h>
#include <bits/timespec.h>
__NAMESPACE_LOCAL_BEGIN
/* Wait until lock becomes available, or specified time passes */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,__localdep_pthread_mutex_timedlock,(__pthread_mutex_t *__restrict __mutex, struct timespec const *__restrict __abstime),pthread_mutex_timedlock64,(__mutex,__abstime))
#elif defined(__CRT_HAVE_pthread_mutex_timedlock) && !defined(__USE_TIME_BITS64)
__NAMESPACE_LOCAL_END
#include <bits/crt/pthreadtypes.h>
#include <bits/timespec.h>
__NAMESPACE_LOCAL_BEGIN
/* Wait until lock becomes available, or specified time passes */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,__localdep_pthread_mutex_timedlock,(__pthread_mutex_t *__restrict __mutex, struct timespec const *__restrict __abstime),pthread_mutex_timedlock,(__mutex,__abstime))
#elif defined(__CRT_HAVE_pthread_mutex_timedlock64) || defined(__CRT_HAVE_pthread_mutex_timedlock)
__NAMESPACE_LOCAL_END
#include <local/pthread/pthread_mutex_timedlock.h>
__NAMESPACE_LOCAL_BEGIN
/* Wait until lock becomes available, or specified time passes */
#define __localdep_pthread_mutex_timedlock __LIBC_LOCAL_NAME(pthread_mutex_timedlock)
#else /* ... */
#undef __local___localdep_pthread_mutex_timedlock_defined
#endif /* !... */
#endif /* !__local___localdep_pthread_mutex_timedlock_defined */
__NAMESPACE_LOCAL_END
#include <asm/crt/threads.h>
#include <bits/crt/pthreadtypes.h>
__NAMESPACE_LOCAL_BEGIN
/* Block the current thread until the mutex pointed by MUTEX
 * is unlocked or time pointed by TIME_POINT is reached.
 * In case the mutex is unlock, the current thread will not be blocked
 * s.a. `pthread_mutex_timedlock()' */
__LOCAL_LIBC(mtx_timedlock) __ATTR_NONNULL((1, 2)) int
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(mtx_timedlock))(__mtx_t *__restrict __mutex, struct timespec const *__restrict __time_point) {
	int __error;
	__error = __localdep_pthread_mutex_timedlock((__pthread_mutex_t *)__mutex, __time_point);
	if __likely(!__error)
		return __thrd_success;
	return __thrd_error;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_mtx_timedlock_defined
#define __local___localdep_mtx_timedlock_defined 1
#define __localdep_mtx_timedlock __LIBC_LOCAL_NAME(mtx_timedlock)
#endif /* !__local___localdep_mtx_timedlock_defined */
#else /* __CRT_HAVE_pthread_mutex_timedlock64 || __CRT_HAVE_pthread_mutex_timedlock */
#undef __local_mtx_timedlock_defined
#endif /* !__CRT_HAVE_pthread_mutex_timedlock64 && !__CRT_HAVE_pthread_mutex_timedlock */
#endif /* !__local_mtx_timedlock_defined */
