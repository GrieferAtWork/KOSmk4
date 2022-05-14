/* HASH CRC-32:0x624d635a */
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
#ifndef __local_pthread_cond_timedwait_defined
#define __local_pthread_cond_timedwait_defined
#include <__crt.h>
#include <bits/types.h>
#if defined(__CRT_HAVE_pthread_cond_timedwait64) || defined(__CRT_HAVE_pthread_cond_timedwait)
#include <bits/crt/pthreadtypes.h>
#include <bits/os/timespec.h>
__NAMESPACE_LOCAL_BEGIN
#if !defined(__local___localdep_crt_pthread_cond_timedwait32_defined) && defined(__CRT_HAVE_pthread_cond_timedwait)
#define __local___localdep_crt_pthread_cond_timedwait32_defined
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2, 3)),__errno_t,__NOTHROW_RPC,__localdep_crt_pthread_cond_timedwait32,(__pthread_cond_t *__restrict __cond, __pthread_mutex_t *__restrict __mutex, struct __timespec32 const *__restrict __abstime),pthread_cond_timedwait,(__cond,__mutex,__abstime))
#endif /* !__local___localdep_crt_pthread_cond_timedwait32_defined && __CRT_HAVE_pthread_cond_timedwait */
#ifndef __local___localdep_pthread_cond_timedwait64_defined
#define __local___localdep_pthread_cond_timedwait64_defined
#if defined(__CRT_HAVE_pthread_cond_timedwait) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2, 3)),__errno_t,__NOTHROW_RPC,__localdep_pthread_cond_timedwait64,(__pthread_cond_t *__restrict __cond, __pthread_mutex_t *__restrict __mutex, struct __timespec64 const *__restrict __abstime),pthread_cond_timedwait,(__cond,__mutex,__abstime))
#elif defined(__CRT_HAVE_pthread_cond_timedwait64)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2, 3)),__errno_t,__NOTHROW_RPC,__localdep_pthread_cond_timedwait64,(__pthread_cond_t *__restrict __cond, __pthread_mutex_t *__restrict __mutex, struct __timespec64 const *__restrict __abstime),pthread_cond_timedwait64,(__cond,__mutex,__abstime))
#elif defined(__CRT_HAVE_pthread_cond_timedwait)
__NAMESPACE_LOCAL_END
#include <libc/local/pthread/pthread_cond_timedwait64.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_pthread_cond_timedwait64 __LIBC_LOCAL_NAME(pthread_cond_timedwait64)
#else /* ... */
#undef __local___localdep_pthread_cond_timedwait64_defined
#endif /* !... */
#endif /* !__local___localdep_pthread_cond_timedwait64_defined */
__LOCAL_LIBC(pthread_cond_timedwait) __ATTR_WUNUSED __ATTR_NONNULL((1, 2, 3)) __errno_t
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(pthread_cond_timedwait))(__pthread_cond_t *__restrict __cond, __pthread_mutex_t *__restrict __mutex, struct timespec const *__restrict __abstime) {
#ifdef __CRT_HAVE_pthread_cond_timedwait
	__errno_t __result;
	struct __timespec32 __abstime32;
	__abstime32.tv_sec  = (__time32_t)__abstime->tv_sec;
	__abstime32.tv_nsec = __abstime->tv_nsec;
	__result = (__NAMESPACE_LOCAL_SYM __localdep_crt_pthread_cond_timedwait32)(__cond, __mutex, &__abstime32);
	return __result;
#else /* __CRT_HAVE_pthread_cond_timedwait */
	__errno_t __result;
	struct __timespec64 __abstime64;
	__abstime64.tv_sec  = (__time64_t)__abstime->tv_sec;
	__abstime64.tv_nsec = __abstime->tv_nsec;
	__result = (__NAMESPACE_LOCAL_SYM __localdep_pthread_cond_timedwait64)(__cond, __mutex, &__abstime64);
	return __result;
#endif /* !__CRT_HAVE_pthread_cond_timedwait */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_pthread_cond_timedwait_defined
#define __local___localdep_pthread_cond_timedwait_defined
#define __localdep_pthread_cond_timedwait __LIBC_LOCAL_NAME(pthread_cond_timedwait)
#endif /* !__local___localdep_pthread_cond_timedwait_defined */
#else /* __CRT_HAVE_pthread_cond_timedwait64 || __CRT_HAVE_pthread_cond_timedwait */
#undef __local_pthread_cond_timedwait_defined
#endif /* !__CRT_HAVE_pthread_cond_timedwait64 && !__CRT_HAVE_pthread_cond_timedwait */
#endif /* !__local_pthread_cond_timedwait_defined */
