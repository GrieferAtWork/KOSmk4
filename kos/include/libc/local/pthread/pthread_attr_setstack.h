/* HASH CRC-32:0x9791ae7b */
/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_pthread_attr_setstack_defined
#define __local_pthread_attr_setstack_defined
#include <__crt.h>
#if defined(__CRT_HAVE_pthread_attr_setstackaddr) && defined(__CRT_HAVE_pthread_attr_setstacksize)
#include <bits/types.h>
#include <bits/crt/pthreadtypes.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_crt_pthread_attr_setstackaddr_defined
#define __local___localdep_crt_pthread_attr_setstackaddr_defined
__CREDIRECT(__ATTR_INOUT(1),__errno_t,__NOTHROW_NCX,__localdep_crt_pthread_attr_setstackaddr,(__pthread_attr_t *__self, void *__stackaddr),pthread_attr_setstackaddr,(__self,__stackaddr))
#endif /* !__local___localdep_crt_pthread_attr_setstackaddr_defined */
#ifndef __local___localdep_crt_pthread_attr_setstacksize_defined
#define __local___localdep_crt_pthread_attr_setstacksize_defined
__CREDIRECT(__ATTR_INOUT(1),__errno_t,__NOTHROW_NCX,__localdep_crt_pthread_attr_setstacksize,(__pthread_attr_t *__self, __SIZE_TYPE__ __stacksize),pthread_attr_setstacksize,(__self,__stacksize))
#endif /* !__local___localdep_crt_pthread_attr_setstacksize_defined */
__LOCAL_LIBC(pthread_attr_setstack) __ATTR_INOUT(1) __errno_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(pthread_attr_setstack))(__pthread_attr_t *__self, void *__stackaddr, __SIZE_TYPE__ __stacksize) {
	__errno_t __result;
	__result = (__NAMESPACE_LOCAL_SYM __localdep_crt_pthread_attr_setstackaddr)(__self, __stackaddr);
	if __likely(__result == 0)
		__result = (__NAMESPACE_LOCAL_SYM __localdep_crt_pthread_attr_setstacksize)(__self, __stacksize);
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_pthread_attr_setstack_defined
#define __local___localdep_pthread_attr_setstack_defined
#define __localdep_pthread_attr_setstack __LIBC_LOCAL_NAME(pthread_attr_setstack)
#endif /* !__local___localdep_pthread_attr_setstack_defined */
#else /* __CRT_HAVE_pthread_attr_setstackaddr && __CRT_HAVE_pthread_attr_setstacksize */
#undef __local_pthread_attr_setstack_defined
#endif /* !__CRT_HAVE_pthread_attr_setstackaddr || !__CRT_HAVE_pthread_attr_setstacksize */
#endif /* !__local_pthread_attr_setstack_defined */
