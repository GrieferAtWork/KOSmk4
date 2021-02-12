/* HASH CRC-32:0x43d54efb */
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
#ifndef __local_pthread_rwlock_timedwrlock64_defined
#define __local_pthread_rwlock_timedwrlock64_defined 1
#include <__crt.h>
#ifdef __CRT_HAVE_pthread_rwlock_timedwrlock
#include <bits/types.h>
#include <bits/crt/pthreadtypes.h>
#include <bits/os/timespec.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: pthread_rwlock_timedwrlock32 from pthread */
#ifndef __local___localdep_pthread_rwlock_timedwrlock32_defined
#define __local___localdep_pthread_rwlock_timedwrlock32_defined 1
/* >> pthread_rwlock_timedwrlock(3), pthread_rwlock_timedwrlock64(3)
 * Try to acquire write lock for `rwlock' or return after the specified time
 * @return: EOK:       Success
 * @return: EINVAL:    The given `abstime' is invalid
 * @return: ETIMEDOUT: The given `abstime' has expired */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__errno_t,__NOTHROW_RPC,__localdep_pthread_rwlock_timedwrlock32,(__pthread_rwlock_t *__restrict __rwlock, struct __timespec32 const *__restrict __abstime),pthread_rwlock_timedwrlock,(__rwlock,__abstime))
#endif /* !__local___localdep_pthread_rwlock_timedwrlock32_defined */
/* >> pthread_rwlock_timedwrlock(3), pthread_rwlock_timedwrlock64(3)
 * Try to acquire write lock for `rwlock' or return after the specified time
 * @return: EOK:       Success
 * @return: EINVAL:    The given `abstime' is invalid
 * @return: ETIMEDOUT: The given `abstime' has expired */
__LOCAL_LIBC(pthread_rwlock_timedwrlock64) __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __errno_t
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(pthread_rwlock_timedwrlock64))(__pthread_rwlock_t *__restrict __rwlock, struct __timespec64 const *__restrict __abstime) {
	__errno_t __result;
	struct __timespec32 __abstime32;
	__abstime32.tv_sec  = (__time32_t)__abstime->tv_sec;
	__abstime32.tv_nsec = __abstime->tv_nsec;
	__result = __localdep_pthread_rwlock_timedwrlock32(__rwlock, &__abstime32);
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_pthread_rwlock_timedwrlock64_defined
#define __local___localdep_pthread_rwlock_timedwrlock64_defined 1
#define __localdep_pthread_rwlock_timedwrlock64 __LIBC_LOCAL_NAME(pthread_rwlock_timedwrlock64)
#endif /* !__local___localdep_pthread_rwlock_timedwrlock64_defined */
#else /* __CRT_HAVE_pthread_rwlock_timedwrlock */
#undef __local_pthread_rwlock_timedwrlock64_defined
#endif /* !__CRT_HAVE_pthread_rwlock_timedwrlock */
#endif /* !__local_pthread_rwlock_timedwrlock64_defined */
