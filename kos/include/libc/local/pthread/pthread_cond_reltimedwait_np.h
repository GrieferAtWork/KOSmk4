/* HASH CRC-32:0xbae48147 */
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
#ifndef __local_pthread_cond_reltimedwait_np_defined
#define __local_pthread_cond_reltimedwait_np_defined
#include <__crt.h>
#include <bits/types.h>
#if defined(__CRT_HAVE_pthread_cond_reltimedwait64_np) || defined(__CRT_HAVE_pthread_cond_timedwait_relative64_np) || defined(__CRT_HAVE_pthread_cond_reltimedwait_np) || defined(__CRT_HAVE_pthread_cond_timedwait_relative_np)
#include <bits/crt/pthreadtypes.h>
#include <bits/os/timespec.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_crt_pthread_cond_reltimedwait32_np_defined
#define __local___localdep_crt_pthread_cond_reltimedwait32_np_defined
#ifdef __CRT_HAVE_pthread_cond_reltimedwait_np
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(3) __ATTR_INOUT(1) __ATTR_INOUT(2),__errno_t,__NOTHROW_RPC,__localdep_crt_pthread_cond_reltimedwait32_np,(__pthread_cond_t *__restrict __self, __pthread_mutex_t *__restrict __mutex, struct __timespec32 const *__restrict __reltime),pthread_cond_reltimedwait_np,(__self,__mutex,__reltime))
#elif defined(__CRT_HAVE_pthread_cond_timedwait_relative_np)
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(3) __ATTR_INOUT(1) __ATTR_INOUT(2),__errno_t,__NOTHROW_RPC,__localdep_crt_pthread_cond_reltimedwait32_np,(__pthread_cond_t *__restrict __self, __pthread_mutex_t *__restrict __mutex, struct __timespec32 const *__restrict __reltime),pthread_cond_timedwait_relative_np,(__self,__mutex,__reltime))
#else /* ... */
#undef __local___localdep_crt_pthread_cond_reltimedwait32_np_defined
#endif /* !... */
#endif /* !__local___localdep_crt_pthread_cond_reltimedwait32_np_defined */
#ifndef __local___localdep_pthread_cond_reltimedwait64_np_defined
#define __local___localdep_pthread_cond_reltimedwait64_np_defined
#if defined(__CRT_HAVE_pthread_cond_reltimedwait_np) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(3) __ATTR_INOUT(1) __ATTR_INOUT(2),__errno_t,__NOTHROW_RPC,__localdep_pthread_cond_reltimedwait64_np,(__pthread_cond_t *__restrict __self, __pthread_mutex_t *__restrict __mutex, struct __timespec64 const *__restrict __reltime),pthread_cond_reltimedwait_np,(__self,__mutex,__reltime))
#elif defined(__CRT_HAVE_pthread_cond_reltimedwait64_np)
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(3) __ATTR_INOUT(1) __ATTR_INOUT(2),__errno_t,__NOTHROW_RPC,__localdep_pthread_cond_reltimedwait64_np,(__pthread_cond_t *__restrict __self, __pthread_mutex_t *__restrict __mutex, struct __timespec64 const *__restrict __reltime),pthread_cond_reltimedwait64_np,(__self,__mutex,__reltime))
#elif defined(__CRT_HAVE_pthread_cond_timedwait_relative64_np)
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(3) __ATTR_INOUT(1) __ATTR_INOUT(2),__errno_t,__NOTHROW_RPC,__localdep_pthread_cond_reltimedwait64_np,(__pthread_cond_t *__restrict __self, __pthread_mutex_t *__restrict __mutex, struct __timespec64 const *__restrict __reltime),pthread_cond_timedwait_relative64_np,(__self,__mutex,__reltime))
#elif defined(__CRT_HAVE_pthread_cond_reltimedwait_np) || defined(__CRT_HAVE_pthread_cond_timedwait_relative_np)
__NAMESPACE_LOCAL_END
#include <libc/local/pthread/pthread_cond_reltimedwait64_np.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_pthread_cond_reltimedwait64_np __LIBC_LOCAL_NAME(pthread_cond_reltimedwait64_np)
#else /* ... */
#undef __local___localdep_pthread_cond_reltimedwait64_np_defined
#endif /* !... */
#endif /* !__local___localdep_pthread_cond_reltimedwait64_np_defined */
__LOCAL_LIBC(pthread_cond_reltimedwait_np) __ATTR_WUNUSED __ATTR_IN(3) __ATTR_INOUT(1) __ATTR_INOUT(2) __errno_t
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(pthread_cond_reltimedwait_np))(__pthread_cond_t *__restrict __self, __pthread_mutex_t *__restrict __mutex, struct timespec const *__restrict __reltime) {
#if defined(__CRT_HAVE_pthread_cond_reltimedwait_np) || defined(__CRT_HAVE_pthread_cond_timedwait_relative_np)
	__errno_t __result;
	struct __timespec32 __reltime32;
	__reltime32.tv_sec  = (__time32_t)__reltime->tv_sec;
	__reltime32.tv_nsec = __reltime->tv_nsec;
	__result = (__NAMESPACE_LOCAL_SYM __localdep_crt_pthread_cond_reltimedwait32_np)(__self, __mutex, &__reltime32);
	return __result;
#else /* __CRT_HAVE_pthread_cond_reltimedwait_np || __CRT_HAVE_pthread_cond_timedwait_relative_np */
	__errno_t __result;
	struct __timespec64 __reltime64;
	__reltime64.tv_sec  = (__time64_t)__reltime->tv_sec;
	__reltime64.tv_nsec = __reltime->tv_nsec;
	__result = (__NAMESPACE_LOCAL_SYM __localdep_pthread_cond_reltimedwait64_np)(__self, __mutex, &__reltime64);
	return __result;
#endif /* !__CRT_HAVE_pthread_cond_reltimedwait_np && !__CRT_HAVE_pthread_cond_timedwait_relative_np */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_pthread_cond_reltimedwait_np_defined
#define __local___localdep_pthread_cond_reltimedwait_np_defined
#define __localdep_pthread_cond_reltimedwait_np __LIBC_LOCAL_NAME(pthread_cond_reltimedwait_np)
#endif /* !__local___localdep_pthread_cond_reltimedwait_np_defined */
#else /* __CRT_HAVE_pthread_cond_reltimedwait64_np || __CRT_HAVE_pthread_cond_timedwait_relative64_np || __CRT_HAVE_pthread_cond_reltimedwait_np || __CRT_HAVE_pthread_cond_timedwait_relative_np */
#undef __local_pthread_cond_reltimedwait_np_defined
#endif /* !__CRT_HAVE_pthread_cond_reltimedwait64_np && !__CRT_HAVE_pthread_cond_timedwait_relative64_np && !__CRT_HAVE_pthread_cond_reltimedwait_np && !__CRT_HAVE_pthread_cond_timedwait_relative_np */
#endif /* !__local_pthread_cond_reltimedwait_np_defined */
