/* HASH CRC-32:0xee15dbe6 */
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
#ifndef __local_pthread_cond_timedwait_defined
#if defined(__CRT_HAVE_pthread_cond_timedwait) || defined(__CRT_HAVE_pthread_cond_timedwait64)
#define __local_pthread_cond_timedwait_defined 1
#include <bits/pthreadtypes.h>
#include <bits/timespec.h>
#include <bits/pthreadtypes.h>

#include <bits/timespec.h>
/* Dependency: "pthread_cond_timedwait32" from "pthread" */
#ifndef ____localdep_pthread_cond_timedwait32_defined
#define ____localdep_pthread_cond_timedwait32_defined 1
#ifdef __CRT_HAVE_pthread_cond_timedwait
__CREDIRECT(__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,__localdep_pthread_cond_timedwait32,(__pthread_cond_t *__restrict __cond, __pthread_mutex_t *__restrict __mutex, struct __timespec32 const *__restrict __abstime),pthread_cond_timedwait,(__cond,__mutex,__abstime))
#else /* LIBC: pthread_cond_timedwait */
#undef ____localdep_pthread_cond_timedwait32_defined
#endif /* pthread_cond_timedwait32... */
#endif /* !____localdep_pthread_cond_timedwait32_defined */

/* Dependency: "pthread_cond_timedwait64" from "pthread" */
#ifndef ____localdep_pthread_cond_timedwait64_defined
#define ____localdep_pthread_cond_timedwait64_defined 1
#ifdef __CRT_HAVE_pthread_cond_timedwait64
/* Wait for condition variable COND to be signaled or broadcast until
 * ABSTIME. MUTEX is assumed to be locked before. ABSTIME is an
 * absolute time specification; zero is the beginning of the epoch
 * (00:00:00 GMT, January 1, 1970). */
__CREDIRECT(__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,__localdep_pthread_cond_timedwait64,(__pthread_cond_t *__restrict __cond, __pthread_mutex_t *__restrict __mutex, struct __timespec64 const *__restrict __abstime),pthread_cond_timedwait64,(__cond,__mutex,__abstime))
#elif defined(__CRT_HAVE_pthread_cond_timedwait) && (__SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* Wait for condition variable COND to be signaled or broadcast until
 * ABSTIME. MUTEX is assumed to be locked before. ABSTIME is an
 * absolute time specification; zero is the beginning of the epoch
 * (00:00:00 GMT, January 1, 1970). */
__CREDIRECT(__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,__localdep_pthread_cond_timedwait64,(__pthread_cond_t *__restrict __cond, __pthread_mutex_t *__restrict __mutex, struct __timespec64 const *__restrict __abstime),pthread_cond_timedwait,(__cond,__mutex,__abstime))
#elif defined(__CRT_HAVE_pthread_cond_timedwait)
#include <local/pthread/pthread_cond_timedwait64.h>
/* Wait for condition variable COND to be signaled or broadcast until
 * ABSTIME. MUTEX is assumed to be locked before. ABSTIME is an
 * absolute time specification; zero is the beginning of the epoch
 * (00:00:00 GMT, January 1, 1970). */
#define __localdep_pthread_cond_timedwait64 (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pthread_cond_timedwait64))
#else /* CUSTOM: pthread_cond_timedwait64 */
#undef ____localdep_pthread_cond_timedwait64_defined
#endif /* pthread_cond_timedwait64... */
#endif /* !____localdep_pthread_cond_timedwait64_defined */

__NAMESPACE_LOCAL_BEGIN
/* Wait for condition variable COND to be signaled or broadcast until
 * ABSTIME. MUTEX is assumed to be locked before. ABSTIME is an
 * absolute time specification; zero is the beginning of the epoch
 * (00:00:00 GMT, January 1, 1970). */
__LOCAL_LIBC(pthread_cond_timedwait) __ATTR_NONNULL((1, 2, 3)) int
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(pthread_cond_timedwait))(__pthread_cond_t *__restrict __cond,
                                                                    __pthread_mutex_t *__restrict __mutex,
                                                                    struct timespec const *__restrict __abstime) {
#line 1167 "kos/src/libc/magic/pthread.c"
#ifdef __CRT_HAVE_pthread_cond_timedwait
	int __result;
	struct __timespec32 __abstime32;
	__abstime32.tv_sec  = (__time32_t)__abstime->tv_sec;
	__abstime32.tv_nsec = __abstime->tv_nsec;
	__result = __localdep_pthread_cond_timedwait32(__cond, __mutex, &__abstime32);
	return __result;
#else /* __CRT_HAVE_pthread_cond_timedwait */
	int __result;
	struct __timespec64 __abstime64;
	__abstime64.tv_sec  = (__time64_t)__abstime->tv_sec;
	__abstime64.tv_nsec = __abstime->tv_nsec;
	__result = __localdep_pthread_cond_timedwait64(__cond, __mutex, &__abstime64);
	return __result;
#endif /* !__CRT_HAVE_pthread_cond_timedwait */
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE_pthread_cond_timedwait || __CRT_HAVE_pthread_cond_timedwait64 */
#endif /* !__local_pthread_cond_timedwait_defined */
