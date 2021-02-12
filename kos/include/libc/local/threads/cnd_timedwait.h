/* HASH CRC-32:0xbfe490f4 */
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
#ifndef __local_cnd_timedwait_defined
#define __local_cnd_timedwait_defined 1
#include <__crt.h>
#if defined(__CRT_HAVE_pthread_cond_timedwait64) || defined(__CRT_HAVE_pthread_cond_timedwait)
#include <bits/crt/threads.h>
#include <bits/os/timespec.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: pthread_cond_timedwait from pthread */
#ifndef __local___localdep_pthread_cond_timedwait_defined
#define __local___localdep_pthread_cond_timedwait_defined 1
#if defined(__CRT_HAVE_pthread_cond_timedwait64) && defined(__USE_TIME_BITS64)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
#include <bits/crt/pthreadtypes.h>
__NAMESPACE_LOCAL_BEGIN
/* >> pthread_cond_timedwait(3), pthread_cond_timedwait64(3)
 * Wait for condition variable `cond' to be signaled or broadcast
 * until `abstime'. `mutex' is assumed to be locked before.
 * `abstime' is an absolute time specification; zero is the
 * beginning of the epoch (00:00:00 GMT, January 1, 1970).
 * @return: EOK:       Success
 * @return: EINVAL:    The given `abstime' is invalid
 * @return: ETIMEDOUT: The given `abstime' has expired */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2, 3)),__errno_t,__NOTHROW_RPC,__localdep_pthread_cond_timedwait,(__pthread_cond_t *__restrict __cond, __pthread_mutex_t *__restrict __mutex, struct timespec const *__restrict __abstime),pthread_cond_timedwait64,(__cond,__mutex,__abstime))
#elif defined(__CRT_HAVE_pthread_cond_timedwait) && !defined(__USE_TIME_BITS64)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
#include <bits/crt/pthreadtypes.h>
__NAMESPACE_LOCAL_BEGIN
/* >> pthread_cond_timedwait(3), pthread_cond_timedwait64(3)
 * Wait for condition variable `cond' to be signaled or broadcast
 * until `abstime'. `mutex' is assumed to be locked before.
 * `abstime' is an absolute time specification; zero is the
 * beginning of the epoch (00:00:00 GMT, January 1, 1970).
 * @return: EOK:       Success
 * @return: EINVAL:    The given `abstime' is invalid
 * @return: ETIMEDOUT: The given `abstime' has expired */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2, 3)),__errno_t,__NOTHROW_RPC,__localdep_pthread_cond_timedwait,(__pthread_cond_t *__restrict __cond, __pthread_mutex_t *__restrict __mutex, struct timespec const *__restrict __abstime),pthread_cond_timedwait,(__cond,__mutex,__abstime))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/pthread/pthread_cond_timedwait.h>
__NAMESPACE_LOCAL_BEGIN
/* >> pthread_cond_timedwait(3), pthread_cond_timedwait64(3)
 * Wait for condition variable `cond' to be signaled or broadcast
 * until `abstime'. `mutex' is assumed to be locked before.
 * `abstime' is an absolute time specification; zero is the
 * beginning of the epoch (00:00:00 GMT, January 1, 1970).
 * @return: EOK:       Success
 * @return: EINVAL:    The given `abstime' is invalid
 * @return: ETIMEDOUT: The given `abstime' has expired */
#define __localdep_pthread_cond_timedwait __LIBC_LOCAL_NAME(pthread_cond_timedwait)
#endif /* !... */
#endif /* !__local___localdep_pthread_cond_timedwait_defined */
__NAMESPACE_LOCAL_END
#include <asm/crt/threads.h>
#include <bits/crt/pthreadtypes.h>
#include <asm/os/errno.h>
__NAMESPACE_LOCAL_BEGIN
/* >> cnd_timedwait(3), cnd_timedwait64(3)
 * Wait on the given condition variable (s.a. `pthread_cond_timedwait(3)')
 * @return: thrd_success:  Success
 * @return: thrd_timedout: Timeout
 * @return: thrd_error:    Error */
__LOCAL_LIBC(cnd_timedwait) __ATTR_NONNULL((1, 2, 3)) int
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(cnd_timedwait))(__cnd_t *__restrict __cond, __mtx_t *__restrict __mutex, struct timespec const *__restrict __time_point) {
	__errno_t __error;
	__error = __localdep_pthread_cond_timedwait((__pthread_cond_t *)__cond,
	                               (__pthread_mutex_t *)__mutex,
	                               __time_point);
	if __likely(!__error)
		return __thrd_success;
#ifdef __ETIMEDOUT
	if (__error == __ETIMEDOUT)
		return __thrd_timedout;
#endif /* __ETIMEDOUT */
	return __thrd_error;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_cnd_timedwait_defined
#define __local___localdep_cnd_timedwait_defined 1
#define __localdep_cnd_timedwait __LIBC_LOCAL_NAME(cnd_timedwait)
#endif /* !__local___localdep_cnd_timedwait_defined */
#else /* __CRT_HAVE_pthread_cond_timedwait64 || __CRT_HAVE_pthread_cond_timedwait */
#undef __local_cnd_timedwait_defined
#endif /* !__CRT_HAVE_pthread_cond_timedwait64 && !__CRT_HAVE_pthread_cond_timedwait */
#endif /* !__local_cnd_timedwait_defined */
