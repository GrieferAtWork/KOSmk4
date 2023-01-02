/* HASH CRC-32:0x6c921591 */
/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_cnd_timedwait64_defined
#define __local_cnd_timedwait64_defined
#include <__crt.h>
#include <bits/types.h>
#if defined(__CRT_HAVE_pthread_cond_timedwait64) || defined(__CRT_HAVE_pthread_cond_timedwait)
#include <bits/crt/threads.h>
#include <bits/os/timespec.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_pthread_cond_timedwait64_defined
#define __local___localdep_pthread_cond_timedwait64_defined
#if defined(__CRT_HAVE_pthread_cond_timedwait) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
__NAMESPACE_LOCAL_END
#include <bits/crt/pthreadtypes.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(3) __ATTR_INOUT(1) __ATTR_INOUT(2),__errno_t,__NOTHROW_RPC,__localdep_pthread_cond_timedwait64,(__pthread_cond_t *__restrict __cond, __pthread_mutex_t *__restrict __mutex, struct __timespec64 const *__restrict __abstime),pthread_cond_timedwait,(__cond,__mutex,__abstime))
#elif defined(__CRT_HAVE_pthread_cond_timedwait64)
__NAMESPACE_LOCAL_END
#include <bits/crt/pthreadtypes.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(3) __ATTR_INOUT(1) __ATTR_INOUT(2),__errno_t,__NOTHROW_RPC,__localdep_pthread_cond_timedwait64,(__pthread_cond_t *__restrict __cond, __pthread_mutex_t *__restrict __mutex, struct __timespec64 const *__restrict __abstime),pthread_cond_timedwait64,(__cond,__mutex,__abstime))
#elif defined(__CRT_HAVE_pthread_cond_timedwait)
__NAMESPACE_LOCAL_END
#include <libc/local/pthread/pthread_cond_timedwait64.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_pthread_cond_timedwait64 __LIBC_LOCAL_NAME(pthread_cond_timedwait64)
#else /* ... */
#undef __local___localdep_pthread_cond_timedwait64_defined
#endif /* !... */
#endif /* !__local___localdep_pthread_cond_timedwait64_defined */
__NAMESPACE_LOCAL_END
#include <asm/crt/threads.h>
#include <bits/crt/pthreadtypes.h>
#include <asm/os/errno.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(cnd_timedwait64) __ATTR_IN(3) __ATTR_INOUT(1) __ATTR_INOUT(2) int
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(cnd_timedwait64))(__cnd_t *__restrict __cond, __mtx_t *__restrict __mutex, struct __timespec64 const *__restrict __time_point) {
	__errno_t __error;
	__error = (__NAMESPACE_LOCAL_SYM __localdep_pthread_cond_timedwait64)((__pthread_cond_t *)__cond,
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
#ifndef __local___localdep_cnd_timedwait64_defined
#define __local___localdep_cnd_timedwait64_defined
#define __localdep_cnd_timedwait64 __LIBC_LOCAL_NAME(cnd_timedwait64)
#endif /* !__local___localdep_cnd_timedwait64_defined */
#else /* __CRT_HAVE_pthread_cond_timedwait64 || __CRT_HAVE_pthread_cond_timedwait */
#undef __local_cnd_timedwait64_defined
#endif /* !__CRT_HAVE_pthread_cond_timedwait64 && !__CRT_HAVE_pthread_cond_timedwait */
#endif /* !__local_cnd_timedwait64_defined */
