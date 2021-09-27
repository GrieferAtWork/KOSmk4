/* HASH CRC-32:0x289d7b24 */
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
#ifndef __local_sem_timedwait_defined
#define __local_sem_timedwait_defined
#include <__crt.h>
#include <bits/types.h>
#if defined(__CRT_HAVE_sem_timedwait64) || defined(__CRT_HAVE_sem_timedwait)
#include <bits/crt/semaphore.h>
#include <bits/os/timespec.h>
__NAMESPACE_LOCAL_BEGIN
#if !defined(__local___localdep_sem_timedwait32_defined) && defined(__CRT_HAVE_sem_timedwait)
#define __local___localdep_sem_timedwait32_defined
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,__localdep_sem_timedwait32,(__sem_t *__restrict __sem, struct __timespec32 const *__restrict __abstime),sem_timedwait,(__sem,__abstime))
#endif /* !__local___localdep_sem_timedwait32_defined && __CRT_HAVE_sem_timedwait */
#ifndef __local___localdep_sem_timedwait64_defined
#define __local___localdep_sem_timedwait64_defined
#if defined(__CRT_HAVE_sem_timedwait) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,__localdep_sem_timedwait64,(__sem_t *__restrict __sem, struct __timespec64 const *__restrict __abstime),sem_timedwait,(__sem,__abstime))
#elif defined(__CRT_HAVE_sem_timedwait64)
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,__localdep_sem_timedwait64,(__sem_t *__restrict __sem, struct __timespec64 const *__restrict __abstime),sem_timedwait64,(__sem,__abstime))
#elif defined(__CRT_HAVE_sem_timedwait)
__NAMESPACE_LOCAL_END
#include <libc/local/semaphore/sem_timedwait64.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_sem_timedwait64 __LIBC_LOCAL_NAME(sem_timedwait64)
#else /* ... */
#undef __local___localdep_sem_timedwait64_defined
#endif /* !... */
#endif /* !__local___localdep_sem_timedwait64_defined */
__LOCAL_LIBC(sem_timedwait) __ATTR_NONNULL((1, 2)) int
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(sem_timedwait))(__sem_t *__restrict __sem, struct timespec const *__restrict __abstime) {
#ifdef __CRT_HAVE_sem_timedwait
	struct __timespec32 __ts32;
	__ts32.tv_sec = (__time32_t)__abstime->tv_sec;
	__ts32.tv_nsec = __abstime->tv_nsec;
	return (__NAMESPACE_LOCAL_SYM __localdep_sem_timedwait32)(__sem, &__ts32);
#else /* __CRT_HAVE_sem_timedwait */
	struct __timespec64 __ts64;
	__ts64.tv_sec = (__time64_t)__abstime->tv_sec;
	__ts64.tv_nsec = __abstime->tv_nsec;
	return (__NAMESPACE_LOCAL_SYM __localdep_sem_timedwait64)(__sem, &__ts64);
#endif /* !__CRT_HAVE_sem_timedwait */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_sem_timedwait_defined
#define __local___localdep_sem_timedwait_defined
#define __localdep_sem_timedwait __LIBC_LOCAL_NAME(sem_timedwait)
#endif /* !__local___localdep_sem_timedwait_defined */
#else /* __CRT_HAVE_sem_timedwait64 || __CRT_HAVE_sem_timedwait */
#undef __local_sem_timedwait_defined
#endif /* !__CRT_HAVE_sem_timedwait64 && !__CRT_HAVE_sem_timedwait */
#endif /* !__local_sem_timedwait_defined */
