/* HASH CRC-32:0x818be54c */
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
#ifndef __local_gai_suspend_defined
#define __local_gai_suspend_defined 1
#include <__crt.h>
#if defined(__CRT_HAVE_gai_suspend64) || defined(__CRT_HAVE_gai_suspend)
__NAMESPACE_LOCAL_BEGIN
/* Dependency: gai_suspend32 from netdb */
#if !defined(__local___localdep_gai_suspend32_defined) && defined(__CRT_HAVE_gai_suspend)
#define __local___localdep_gai_suspend32_defined 1
/* Suspend execution of the thread until at least one of the `ent' requests
 * in `list' is handled. If `timeout' is not a null pointer it specifies the
 * longest time the function keeps waiting before returning with an error.
 * This function is not part of POSIX and therefore no official
 * cancellation point */
__CREDIRECT(,int,__NOTHROW_RPC,__localdep_gai_suspend32,(struct gaicb const *const __list[], int __ent, struct __timespec32 const *__timeout),gai_suspend,(__list,__ent,__timeout))
#endif /* !__local___localdep_gai_suspend32_defined && __CRT_HAVE_gai_suspend */
/* Dependency: gai_suspend64 from netdb */
#ifndef __local___localdep_gai_suspend64_defined
#define __local___localdep_gai_suspend64_defined 1
#ifdef __CRT_HAVE_gai_suspend64
/* Suspend execution of the thread until at least one of the `ent' requests
 * in `list' is handled. If `timeout' is not a null pointer it specifies the
 * longest time the function keeps waiting before returning with an error.
 * This function is not part of POSIX and therefore no official
 * cancellation point */
__CREDIRECT(,int,__NOTHROW_RPC,__localdep_gai_suspend64,(struct gaicb const *const __list[], int __ent, struct __timespec64 const *__timeout),gai_suspend64,(__list,__ent,__timeout))
#elif defined(__CRT_HAVE_gai_suspend) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* Suspend execution of the thread until at least one of the `ent' requests
 * in `list' is handled. If `timeout' is not a null pointer it specifies the
 * longest time the function keeps waiting before returning with an error.
 * This function is not part of POSIX and therefore no official
 * cancellation point */
__CREDIRECT(,int,__NOTHROW_RPC,__localdep_gai_suspend64,(struct gaicb const *const __list[], int __ent, struct __timespec64 const *__timeout),gai_suspend,(__list,__ent,__timeout))
#elif defined(__CRT_HAVE_gai_suspend)
__NAMESPACE_LOCAL_END
#include <libc/local/netdb/gai_suspend64.h>
__NAMESPACE_LOCAL_BEGIN
/* Suspend execution of the thread until at least one of the `ent' requests
 * in `list' is handled. If `timeout' is not a null pointer it specifies the
 * longest time the function keeps waiting before returning with an error.
 * This function is not part of POSIX and therefore no official
 * cancellation point */
#define __localdep_gai_suspend64 __LIBC_LOCAL_NAME(gai_suspend64)
#else /* ... */
#undef __local___localdep_gai_suspend64_defined
#endif /* !... */
#endif /* !__local___localdep_gai_suspend64_defined */
/* Suspend execution of the thread until at least one of the `ent' requests
 * in `list' is handled. If `timeout' is not a null pointer it specifies the
 * longest time the function keeps waiting before returning with an error.
 * This function is not part of POSIX and therefore no official
 * cancellation point */
__LOCAL_LIBC(gai_suspend) int
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(gai_suspend))(struct gaicb const *const __list[], int __ent, struct timespec const *__timeout) {
#ifdef __CRT_HAVE_gai_suspend
	struct __timespec32 __tmo32;
	if (!__timeout)
		return __localdep_gai_suspend32(__list, __ent, __NULLPTR);
	__tmo32.tv_sec  = (__time32_t)__timeout->tv_sec;
	__tmo32.tv_nsec = __timeout->tv_nsec;
	return __localdep_gai_suspend32(__list, __ent, &__tmo32);
#else /* __CRT_HAVE_gai_suspend */
	struct __timespec64 __tmo64;
	if (!__timeout)
		return __localdep_gai_suspend64(__list, __ent, __NULLPTR);
	__tmo64.tv_sec  = (__time64_t)__timeout->tv_sec;
	__tmo64.tv_nsec = __timeout->tv_nsec;
	return __localdep_gai_suspend64(__list, __ent, &__tmo64);
#endif /* !__CRT_HAVE_gai_suspend */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_gai_suspend_defined
#define __local___localdep_gai_suspend_defined 1
#define __localdep_gai_suspend __LIBC_LOCAL_NAME(gai_suspend)
#endif /* !__local___localdep_gai_suspend_defined */
#else /* __CRT_HAVE_gai_suspend64 || __CRT_HAVE_gai_suspend */
#undef __local_gai_suspend_defined
#endif /* !__CRT_HAVE_gai_suspend64 && !__CRT_HAVE_gai_suspend */
#endif /* !__local_gai_suspend_defined */
