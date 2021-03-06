/* HASH CRC-32:0xc9d664b1 */
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
#ifndef __local_pthread_attr_getstackaddr_defined
#define __local_pthread_attr_getstackaddr_defined 1
#include <__crt.h>
#ifdef __CRT_HAVE_pthread_attr_getstack
#include <bits/types.h>
#include <bits/crt/pthreadtypes.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: crt_pthread_attr_getstack from pthread */
#ifndef __local___localdep_crt_pthread_attr_getstack_defined
#define __local___localdep_crt_pthread_attr_getstack_defined 1
/* >> pthread_attr_getstack(3)
 * Return the previously set address for the stack
 * @return: EOK: Success */
__CREDIRECT(__ATTR_NONNULL((1, 2, 3)),__errno_t,__NOTHROW_NCX,__localdep_crt_pthread_attr_getstack,(__pthread_attr_t const *__restrict __attr, void **__restrict __stackaddr, __SIZE_TYPE__ *__restrict __stacksize),pthread_attr_getstack,(__attr,__stackaddr,__stacksize))
#endif /* !__local___localdep_crt_pthread_attr_getstack_defined */
/* >> pthread_attr_getstackaddr(3)
 * Return the previously set address for the stack
 * @return: EOK: Success */
__LOCAL_LIBC(pthread_attr_getstackaddr) __ATTR_DEPRECATED("Use pthread_attr_getstack()") __ATTR_NONNULL((1, 2)) __errno_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(pthread_attr_getstackaddr))(__pthread_attr_t const *__restrict __attr, void **__restrict __stackaddr) {
	__SIZE_TYPE__ __stacksize;
	return __localdep_crt_pthread_attr_getstack(__attr, __stackaddr, &__stacksize);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_pthread_attr_getstackaddr_defined
#define __local___localdep_pthread_attr_getstackaddr_defined 1
#define __localdep_pthread_attr_getstackaddr __LIBC_LOCAL_NAME(pthread_attr_getstackaddr)
#endif /* !__local___localdep_pthread_attr_getstackaddr_defined */
#else /* __CRT_HAVE_pthread_attr_getstack */
#undef __local_pthread_attr_getstackaddr_defined
#endif /* !__CRT_HAVE_pthread_attr_getstack */
#endif /* !__local_pthread_attr_getstackaddr_defined */
