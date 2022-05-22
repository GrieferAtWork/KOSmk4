/* HASH CRC-32:0xe3b3d9ec */
/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_pthread_stackseg_np_defined
#define __local_pthread_stackseg_np_defined
#include <__crt.h>
#if defined(__CRT_HAVE_pthread_getattr_np) && (defined(__CRT_HAVE_pthread_attr_getstack) || (defined(__CRT_HAVE_pthread_attr_getstackaddr) && defined(__CRT_HAVE_pthread_attr_getstacksize)))
#include <bits/os/sigstack.h>
#include <bits/types.h>
#include <bits/crt/pthreadtypes.h>
__NAMESPACE_LOCAL_BEGIN
#if !defined(__local___localdep_pthread_attr_destroy_defined) && defined(__CRT_HAVE_pthread_attr_destroy)
#define __local___localdep_pthread_attr_destroy_defined
__CREDIRECT(__ATTR_ACCESS_RW(1),__errno_t,__NOTHROW_NCX,__localdep_pthread_attr_destroy,(__pthread_attr_t *__attr),pthread_attr_destroy,(__attr))
#endif /* !__local___localdep_pthread_attr_destroy_defined && __CRT_HAVE_pthread_attr_destroy */
#ifndef __local___localdep_pthread_attr_getstack_defined
#define __local___localdep_pthread_attr_getstack_defined
#ifdef __CRT_HAVE_pthread_attr_getstack
__CREDIRECT(__ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR(2) __ATTR_ACCESS_WR(3),__errno_t,__NOTHROW_NCX,__localdep_pthread_attr_getstack,(__pthread_attr_t const *__restrict __attr, void **__restrict __stackaddr, __SIZE_TYPE__ *__restrict __stacksize),pthread_attr_getstack,(__attr,__stackaddr,__stacksize))
#elif defined(__CRT_HAVE_pthread_attr_getstackaddr) && defined(__CRT_HAVE_pthread_attr_getstacksize)
__NAMESPACE_LOCAL_END
#include <libc/local/pthread/pthread_attr_getstack.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_pthread_attr_getstack __LIBC_LOCAL_NAME(pthread_attr_getstack)
#else /* ... */
#undef __local___localdep_pthread_attr_getstack_defined
#endif /* !... */
#endif /* !__local___localdep_pthread_attr_getstack_defined */
#ifndef __local___localdep_pthread_getattr_np_defined
#define __local___localdep_pthread_getattr_np_defined
__CREDIRECT(__ATTR_ACCESS_WR(2),__errno_t,__NOTHROW_NCX,__localdep_pthread_getattr_np,(__pthread_t __pthread, __pthread_attr_t *__attr),pthread_getattr_np,(__pthread,__attr))
#endif /* !__local___localdep_pthread_getattr_np_defined */
__LOCAL_LIBC(pthread_stackseg_np) __ATTR_ACCESS_WR(2) __errno_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(pthread_stackseg_np))(__pthread_t __pthread, struct sigaltstack *__sinfo) {
	__errno_t __result;
	__pthread_attr_t __attr;
	__result = (__NAMESPACE_LOCAL_SYM __localdep_pthread_getattr_np)(__pthread, &__attr);
	if __likely(__result == 0) {
		void *__stackaddr;
		__SIZE_TYPE__ __stacksize;
		__result = (__NAMESPACE_LOCAL_SYM __localdep_pthread_attr_getstack)(&__attr, &__stackaddr, &__stacksize);
		if __likely(__result == 0) {
			__sinfo->ss_sp    = __stackaddr;
			__sinfo->ss_size  = __stacksize;
			__sinfo->ss_flags = 0;
		}
#ifdef __CRT_HAVE_pthread_attr_destroy
		(__NAMESPACE_LOCAL_SYM __localdep_pthread_attr_destroy)(&__attr);
#endif /* __CRT_HAVE_pthread_attr_destroy */
	}
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_pthread_stackseg_np_defined
#define __local___localdep_pthread_stackseg_np_defined
#define __localdep_pthread_stackseg_np __LIBC_LOCAL_NAME(pthread_stackseg_np)
#endif /* !__local___localdep_pthread_stackseg_np_defined */
#else /* __CRT_HAVE_pthread_getattr_np && (__CRT_HAVE_pthread_attr_getstack || (__CRT_HAVE_pthread_attr_getstackaddr && __CRT_HAVE_pthread_attr_getstacksize)) */
#undef __local_pthread_stackseg_np_defined
#endif /* !__CRT_HAVE_pthread_getattr_np || (!__CRT_HAVE_pthread_attr_getstack && (!__CRT_HAVE_pthread_attr_getstackaddr || !__CRT_HAVE_pthread_attr_getstacksize)) */
#endif /* !__local_pthread_stackseg_np_defined */
