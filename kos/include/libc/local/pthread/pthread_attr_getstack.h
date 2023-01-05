/* HASH CRC-32:0xd5706a09 */
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
#ifndef __local_pthread_attr_getstack_defined
#define __local_pthread_attr_getstack_defined
#include <__crt.h>
#if defined(__CRT_HAVE_pthread_attr_getstackaddr) && defined(__CRT_HAVE_pthread_attr_getstacksize)
#include <bits/types.h>
#include <bits/crt/pthreadtypes.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_crt_pthread_attr_getstackaddr_defined
#define __local___localdep_crt_pthread_attr_getstackaddr_defined
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),__errno_t,__NOTHROW_NCX,__localdep_crt_pthread_attr_getstackaddr,(__pthread_attr_t const *__restrict __self, void **__restrict __stackaddr),pthread_attr_getstackaddr,(__self,__stackaddr))
#endif /* !__local___localdep_crt_pthread_attr_getstackaddr_defined */
#ifndef __local___localdep_crt_pthread_attr_getstacksize_defined
#define __local___localdep_crt_pthread_attr_getstacksize_defined
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),__errno_t,__NOTHROW_NCX,__localdep_crt_pthread_attr_getstacksize,(__pthread_attr_t const *__restrict __self, __SIZE_TYPE__ *__restrict __stacksize),pthread_attr_getstacksize,(__self,__stacksize))
#endif /* !__local___localdep_crt_pthread_attr_getstacksize_defined */
__LOCAL_LIBC(pthread_attr_getstack) __ATTR_IN(1) __ATTR_OUT(2) __ATTR_OUT(3) __errno_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(pthread_attr_getstack))(__pthread_attr_t const *__restrict __self, void **__restrict __stackaddr, __SIZE_TYPE__ *__restrict __stacksize) {
	__errno_t __result;
	__result = (__NAMESPACE_LOCAL_SYM __localdep_crt_pthread_attr_getstackaddr)(__self, __stackaddr);
	if __likely(__result == 0)
		__result = (__NAMESPACE_LOCAL_SYM __localdep_crt_pthread_attr_getstacksize)(__self, __stacksize);
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_pthread_attr_getstack_defined
#define __local___localdep_pthread_attr_getstack_defined
#define __localdep_pthread_attr_getstack __LIBC_LOCAL_NAME(pthread_attr_getstack)
#endif /* !__local___localdep_pthread_attr_getstack_defined */
#else /* __CRT_HAVE_pthread_attr_getstackaddr && __CRT_HAVE_pthread_attr_getstacksize */
#undef __local_pthread_attr_getstack_defined
#endif /* !__CRT_HAVE_pthread_attr_getstackaddr || !__CRT_HAVE_pthread_attr_getstacksize */
#endif /* !__local_pthread_attr_getstack_defined */
