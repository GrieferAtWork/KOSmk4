/* HASH CRC-32:0x509277ec */
/* Copyright (c) 2019 Griefer@Work                                            *
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
#ifndef __local_pthread_rwlock_timedwrlock_defined
#if defined(__CRT_HAVE_pthread_rwlock_timedwrlock) || defined(__CRT_HAVE_pthread_rwlock_timedwrlock64)
#define __local_pthread_rwlock_timedwrlock_defined 1
#include <bits/pthreadtypes.h>
#include <bits/timespec.h>
#include <bits/pthreadtypes.h>

#include <bits/timespec.h>
/* Dependency: "pthread_rwlock_timedwrlock32" from "pthread" */
#ifndef ____localdep_pthread_rwlock_timedwrlock32_defined
#define ____localdep_pthread_rwlock_timedwrlock32_defined 1
#ifdef __CRT_HAVE_pthread_rwlock_timedwrlock
/* Try to acquire write lock for RWLOCK or return after specfied time */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,__localdep_pthread_rwlock_timedwrlock32,(__pthread_rwlock_t *__restrict __rwlock, struct __timespec32 const *__restrict __abstime),pthread_rwlock_timedwrlock,(__rwlock,__abstime))
#else /* LIBC: pthread_rwlock_timedwrlock */
#undef ____localdep_pthread_rwlock_timedwrlock32_defined
#endif /* pthread_rwlock_timedwrlock32... */
#endif /* !____localdep_pthread_rwlock_timedwrlock32_defined */

/* Dependency: "pthread_rwlock_timedwrlock64" from "pthread" */
#ifndef ____localdep_pthread_rwlock_timedwrlock64_defined
#define ____localdep_pthread_rwlock_timedwrlock64_defined 1
#ifdef __CRT_HAVE_pthread_rwlock_timedwrlock64
/* Try to acquire write lock for RWLOCK or return after specfied time */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,__localdep_pthread_rwlock_timedwrlock64,(__pthread_rwlock_t *__restrict __rwlock, struct __timespec64 const *__restrict __abstime),pthread_rwlock_timedwrlock64,(__rwlock,__abstime))
#elif defined(__CRT_HAVE_pthread_rwlock_timedwrlock) && (__SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* Try to acquire write lock for RWLOCK or return after specfied time */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,__localdep_pthread_rwlock_timedwrlock64,(__pthread_rwlock_t *__restrict __rwlock, struct __timespec64 const *__restrict __abstime),pthread_rwlock_timedwrlock,(__rwlock,__abstime))
#elif defined(__CRT_HAVE_pthread_rwlock_timedwrlock)
#include <local/pthread/pthread_rwlock_timedwrlock64.h>
/* Try to acquire write lock for RWLOCK or return after specfied time */
#define __localdep_pthread_rwlock_timedwrlock64 (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pthread_rwlock_timedwrlock64))
#else /* CUSTOM: pthread_rwlock_timedwrlock64 */
#undef ____localdep_pthread_rwlock_timedwrlock64_defined
#endif /* pthread_rwlock_timedwrlock64... */
#endif /* !____localdep_pthread_rwlock_timedwrlock64_defined */

__NAMESPACE_LOCAL_BEGIN
/* Try to acquire write lock for RWLOCK or return after specfied time */
__LOCAL_LIBC(pthread_rwlock_timedwrlock) __ATTR_NONNULL((1, 2)) int
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(pthread_rwlock_timedwrlock))(__pthread_rwlock_t *__restrict __rwlock,
                                                                        struct __TM_TYPE(timespec) const *__restrict __abstime) {
#line 1048 "kos/src/libc/magic/pthread.c"
#ifdef __CRT_HAVE_pthread_rwlock_timedwrlock
	int __result;
	struct __timespec32 __abstime32;
	__abstime32.tv_sec  = (__time32_t)__abstime->tv_sec;
	__abstime32.tv_nsec = __abstime->tv_nsec;
	__result = __localdep_pthread_rwlock_timedwrlock32(__rwlock, &__abstime32);
	return __result;
#else /* __CRT_HAVE_pthread_rwlock_timedwrlock */
	int __result;
	struct __timespec64 __abstime64;
	__abstime64.tv_sec  = (__time64_t)__abstime->tv_sec;
	__abstime64.tv_nsec = __abstime->tv_nsec;
	__result = __localdep_pthread_rwlock_timedwrlock64(__rwlock, &__abstime32);
	return __result;
#endif /* !__CRT_HAVE_pthread_rwlock_timedwrlock */
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE_pthread_rwlock_timedwrlock || __CRT_HAVE_pthread_rwlock_timedwrlock64 */
#endif /* !__local_pthread_rwlock_timedwrlock_defined */
