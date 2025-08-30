/* HASH CRC-32:0xd80ddb8f */
/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_pthread_mutex_clocklock64_defined
#define __local_pthread_mutex_clocklock64_defined
#include <__crt.h>
#ifdef __CRT_HAVE_pthread_mutex_clocklock
#include <bits/types.h>
#include <bits/crt/pthreadtypes.h>
#include <bits/os/timespec.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_crt_pthread_mutex_clocklock32_defined
#define __local___localdep_crt_pthread_mutex_clocklock32_defined
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(3) __ATTR_INOUT(1),__errno_t,__NOTHROW_RPC,__localdep_crt_pthread_mutex_clocklock32,(__pthread_mutex_t *__restrict __self, __clockid_t __clock_id, struct timespec const *__restrict __abstime),pthread_mutex_clocklock,(__self,__clock_id,__abstime))
#endif /* !__local___localdep_crt_pthread_mutex_clocklock32_defined */
__LOCAL_LIBC(pthread_mutex_clocklock64) __ATTR_WUNUSED __ATTR_IN(3) __ATTR_INOUT(1) __errno_t
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(pthread_mutex_clocklock64))(__pthread_mutex_t *__restrict __self, __clockid_t __clock_id, struct __timespec64 const *__restrict __abstime) {
	__errno_t __result;
	struct __timespec32 __abstime32;
	__abstime32.tv_sec  = (__time32_t)__abstime->tv_sec;
	__abstime32.tv_nsec = __abstime->tv_nsec;
	__result = (__NAMESPACE_LOCAL_SYM __localdep_crt_pthread_mutex_clocklock32)(__self, __clock_id, &__abstime32);
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_pthread_mutex_clocklock64_defined
#define __local___localdep_pthread_mutex_clocklock64_defined
#define __localdep_pthread_mutex_clocklock64 __LIBC_LOCAL_NAME(pthread_mutex_clocklock64)
#endif /* !__local___localdep_pthread_mutex_clocklock64_defined */
#else /* __CRT_HAVE_pthread_mutex_clocklock */
#undef __local_pthread_mutex_clocklock64_defined
#endif /* !__CRT_HAVE_pthread_mutex_clocklock */
#endif /* !__local_pthread_mutex_clocklock64_defined */
