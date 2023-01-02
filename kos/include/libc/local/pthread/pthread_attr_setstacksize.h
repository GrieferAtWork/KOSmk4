/* HASH CRC-32:0xb01a2f03 */
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
#ifndef __local_pthread_attr_setstacksize_defined
#define __local_pthread_attr_setstacksize_defined
#include <__crt.h>
#if (defined(__CRT_HAVE_pthread_attr_getstack) || (defined(__CRT_HAVE_pthread_attr_getstackaddr) && defined(__CRT_HAVE_pthread_attr_getstacksize))) && defined(__CRT_HAVE_pthread_attr_setstack)
#include <bits/types.h>
#include <bits/crt/pthreadtypes.h>
__NAMESPACE_LOCAL_BEGIN
#if !defined(__local___localdep_crt_pthread_attr_getstackaddr_defined) && defined(__CRT_HAVE_pthread_attr_getstackaddr)
#define __local___localdep_crt_pthread_attr_getstackaddr_defined
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),__errno_t,__NOTHROW_NCX,__localdep_crt_pthread_attr_getstackaddr,(__pthread_attr_t const *__restrict __attr, void **__restrict __stackaddr),pthread_attr_getstackaddr,(__attr,__stackaddr))
#endif /* !__local___localdep_crt_pthread_attr_getstackaddr_defined && __CRT_HAVE_pthread_attr_getstackaddr */
#ifndef __local___localdep_crt_pthread_attr_setstack_defined
#define __local___localdep_crt_pthread_attr_setstack_defined
__CREDIRECT(__ATTR_INOUT(1),__errno_t,__NOTHROW_NCX,__localdep_crt_pthread_attr_setstack,(__pthread_attr_t *__attr, void *__stackaddr, __SIZE_TYPE__ __stacksize),pthread_attr_setstack,(__attr,__stackaddr,__stacksize))
#endif /* !__local___localdep_crt_pthread_attr_setstack_defined */
#ifndef __local___localdep_pthread_attr_getstack_defined
#define __local___localdep_pthread_attr_getstack_defined
#ifdef __CRT_HAVE_pthread_attr_getstack
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2) __ATTR_OUT(3),__errno_t,__NOTHROW_NCX,__localdep_pthread_attr_getstack,(__pthread_attr_t const *__restrict __attr, void **__restrict __stackaddr, __SIZE_TYPE__ *__restrict __stacksize),pthread_attr_getstack,(__attr,__stackaddr,__stacksize))
#elif defined(__CRT_HAVE_pthread_attr_getstackaddr) && defined(__CRT_HAVE_pthread_attr_getstacksize)
__NAMESPACE_LOCAL_END
#include <libc/local/pthread/pthread_attr_getstack.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_pthread_attr_getstack __LIBC_LOCAL_NAME(pthread_attr_getstack)
#else /* ... */
#undef __local___localdep_pthread_attr_getstack_defined
#endif /* !... */
#endif /* !__local___localdep_pthread_attr_getstack_defined */
__LOCAL_LIBC(pthread_attr_setstacksize) __ATTR_INOUT(1) __errno_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(pthread_attr_setstacksize))(__pthread_attr_t *__attr, __SIZE_TYPE__ __stacksize) {
	__errno_t __result;
	void *__stackaddr;
#ifdef __CRT_HAVE_pthread_attr_getstackaddr
	__result = (__NAMESPACE_LOCAL_SYM __localdep_crt_pthread_attr_getstackaddr)(__attr, &__stackaddr);
#else /* __CRT_HAVE_pthread_attr_getstackaddr */
	__SIZE_TYPE__ ___old_stacksize;
	__result = (__NAMESPACE_LOCAL_SYM __localdep_pthread_attr_getstack)(__attr, &__stackaddr, &___old_stacksize);
#endif /* !__CRT_HAVE_pthread_attr_getstackaddr */
	if __likely(__result == 0)
		__result = (__NAMESPACE_LOCAL_SYM __localdep_crt_pthread_attr_setstack)(__attr, __stackaddr, __stacksize);
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_pthread_attr_setstacksize_defined
#define __local___localdep_pthread_attr_setstacksize_defined
#define __localdep_pthread_attr_setstacksize __LIBC_LOCAL_NAME(pthread_attr_setstacksize)
#endif /* !__local___localdep_pthread_attr_setstacksize_defined */
#else /* (__CRT_HAVE_pthread_attr_getstack || (__CRT_HAVE_pthread_attr_getstackaddr && __CRT_HAVE_pthread_attr_getstacksize)) && __CRT_HAVE_pthread_attr_setstack */
#undef __local_pthread_attr_setstacksize_defined
#endif /* (!__CRT_HAVE_pthread_attr_getstack && (!__CRT_HAVE_pthread_attr_getstackaddr || !__CRT_HAVE_pthread_attr_getstacksize)) || !__CRT_HAVE_pthread_attr_setstack */
#endif /* !__local_pthread_attr_setstacksize_defined */
