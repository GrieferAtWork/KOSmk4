/* HASH CRC-32:0x7e0d583 */
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
#ifndef __local_pthread_get_stackaddr_np_defined
#define __local_pthread_get_stackaddr_np_defined
#include <__crt.h>
#if (defined(__CRT_HAVE_pthread_getattr_np) || defined(__CRT_HAVE_pthread_attr_get_np)) && (defined(__CRT_HAVE_pthread_attr_getstackaddr) || defined(__CRT_HAVE_pthread_attr_getstack))
#include <bits/crt/pthreadtypes.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_pthread_attr_destroy_defined
#define __local___localdep_pthread_attr_destroy_defined
#ifdef __CRT_HAVE_pthread_attr_destroy
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_INOUT(1),__errno_t,__NOTHROW_NCX,__localdep_pthread_attr_destroy,(__pthread_attr_t *__self),pthread_attr_destroy,(__self))
#elif defined(__CRT_HAVE___pthread_attr_destroy)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_INOUT(1),__errno_t,__NOTHROW_NCX,__localdep_pthread_attr_destroy,(__pthread_attr_t *__self),__pthread_attr_destroy,(__self))
#else /* ... */
#undef __local___localdep_pthread_attr_destroy_defined
#endif /* !... */
#endif /* !__local___localdep_pthread_attr_destroy_defined */
#ifndef __local___localdep_pthread_attr_getstackaddr_defined
#define __local___localdep_pthread_attr_getstackaddr_defined
#ifdef __CRT_HAVE_pthread_attr_getstackaddr
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),__errno_t,__NOTHROW_NCX,__localdep_pthread_attr_getstackaddr,(__pthread_attr_t const *__restrict __self, void **__restrict __stackaddr),pthread_attr_getstackaddr,(__self,__stackaddr))
#elif defined(__CRT_HAVE_pthread_attr_getstack)
__NAMESPACE_LOCAL_END
#include <libc/local/pthread/pthread_attr_getstackaddr.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_pthread_attr_getstackaddr __LIBC_LOCAL_NAME(pthread_attr_getstackaddr)
#else /* ... */
#undef __local___localdep_pthread_attr_getstackaddr_defined
#endif /* !... */
#endif /* !__local___localdep_pthread_attr_getstackaddr_defined */
#ifndef __local___localdep_pthread_getattr_np_defined
#define __local___localdep_pthread_getattr_np_defined
#ifdef __CRT_HAVE_pthread_getattr_np
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_OUT(2),__errno_t,__NOTHROW_NCX,__localdep_pthread_getattr_np,(__pthread_t __self, __pthread_attr_t *__attr),pthread_getattr_np,(__self,__attr))
#elif defined(__CRT_HAVE_pthread_attr_get_np)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_OUT(2),__errno_t,__NOTHROW_NCX,__localdep_pthread_getattr_np,(__pthread_t __self, __pthread_attr_t *__attr),pthread_attr_get_np,(__self,__attr))
#else /* ... */
#undef __local___localdep_pthread_getattr_np_defined
#endif /* !... */
#endif /* !__local___localdep_pthread_getattr_np_defined */
__LOCAL_LIBC(pthread_get_stackaddr_np) void *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(pthread_get_stackaddr_np))(__pthread_t __self) {
	void *__result = __NULLPTR;
	__pthread_attr_t __attr;
	if ((__NAMESPACE_LOCAL_SYM __localdep_pthread_getattr_np)(__self, &__attr) == 0) {
		if ((__NAMESPACE_LOCAL_SYM __localdep_pthread_attr_getstackaddr)(&__attr, &__result) != 0)
			__result = __NULLPTR;
#if defined(__CRT_HAVE_pthread_attr_destroy) || defined(__CRT_HAVE___pthread_attr_destroy)
		(__NAMESPACE_LOCAL_SYM __localdep_pthread_attr_destroy)(&__attr);
#endif /* __CRT_HAVE_pthread_attr_destroy || __CRT_HAVE___pthread_attr_destroy */
	}
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_pthread_get_stackaddr_np_defined
#define __local___localdep_pthread_get_stackaddr_np_defined
#define __localdep_pthread_get_stackaddr_np __LIBC_LOCAL_NAME(pthread_get_stackaddr_np)
#endif /* !__local___localdep_pthread_get_stackaddr_np_defined */
#else /* (__CRT_HAVE_pthread_getattr_np || __CRT_HAVE_pthread_attr_get_np) && (__CRT_HAVE_pthread_attr_getstackaddr || __CRT_HAVE_pthread_attr_getstack) */
#undef __local_pthread_get_stackaddr_np_defined
#endif /* (!__CRT_HAVE_pthread_getattr_np && !__CRT_HAVE_pthread_attr_get_np) || (!__CRT_HAVE_pthread_attr_getstackaddr && !__CRT_HAVE_pthread_attr_getstack) */
#endif /* !__local_pthread_get_stackaddr_np_defined */
