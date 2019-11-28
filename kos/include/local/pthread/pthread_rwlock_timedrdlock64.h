/* HASH CRC-32:0xe1123510 */
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
#ifndef __local_pthread_rwlock_timedrdlock64_defined
#ifdef __CRT_HAVE_pthread_rwlock_timedrdlock
#define __local_pthread_rwlock_timedrdlock64_defined 1
#include <bits/pthreadtypes.h>
#include <bits/timespec.h>
#include <bits/pthreadtypes.h>

#include <bits/timespec.h>
/* Dependency: "pthread_rwlock_timedrdlock32" from "pthread" */
#ifndef ____localdep_pthread_rwlock_timedrdlock32_defined
#define ____localdep_pthread_rwlock_timedrdlock32_defined 1
#ifdef __CRT_HAVE_pthread_rwlock_timedrdlock
/* Try to acquire read lock for RWLOCK or return after specfied time */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,__localdep_pthread_rwlock_timedrdlock32,(__pthread_rwlock_t *__restrict __rwlock, struct __timespec32 const *__restrict __abstime),pthread_rwlock_timedrdlock,(__rwlock,__abstime))
#else /* LIBC: pthread_rwlock_timedrdlock */
#undef ____localdep_pthread_rwlock_timedrdlock32_defined
#endif /* pthread_rwlock_timedrdlock32... */
#endif /* !____localdep_pthread_rwlock_timedrdlock32_defined */

__NAMESPACE_LOCAL_BEGIN
/* Try to acquire read lock for RWLOCK or return after specfied time */
__LOCAL_LIBC(pthread_rwlock_timedrdlock64) __ATTR_NONNULL((1, 2)) int
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(pthread_rwlock_timedrdlock64))(__pthread_rwlock_t *__restrict __rwlock,
                                                                          struct __timespec64 const *__restrict __abstime) {
#line 1017 "kos/src/libc/magic/pthread.c"
	int __result;
	struct __timespec32 __abstime32;
	__abstime32.tv_sec  = (__time32_t)__abstime->tv_sec;
	__abstime32.tv_nsec = __abstime->tv_nsec;
	__result = __localdep_pthread_rwlock_timedrdlock32(__rwlock, &__abstime32);
	return __result;
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE_pthread_rwlock_timedrdlock */
#endif /* !__local_pthread_rwlock_timedrdlock64_defined */
