/* HASH CRC-32:0x205551cf */
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
#ifndef __local_pthread_attr_setstack_defined
#define __local_pthread_attr_setstack_defined 1
#include <__crt.h>
#if defined(__CRT_HAVE_pthread_attr_setstackaddr) && defined(__CRT_HAVE_pthread_attr_setstacksize)
#include <bits/types.h>
#include <bits/crt/pthreadtypes.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: crt_pthread_attr_setstackaddr from pthread */
#ifndef __local___localdep_crt_pthread_attr_setstackaddr_defined
#define __local___localdep_crt_pthread_attr_setstackaddr_defined 1
/* >> pthread_attr_setstackaddr(3)
 * Set the starting address of the stack of the thread to be created.
 * Depending on whether the stack grows up or down the value must either
 * be higher or lower than all the address in the memory block. The
 * minimal size of the block must be `PTHREAD_STACK_MIN'
 * @return: EOK:    Success
 * @return: EINVAL: The stack isn't suitably aligned */
__CREDIRECT(__ATTR_NONNULL((1)),__errno_t,__NOTHROW_NCX,__localdep_crt_pthread_attr_setstackaddr,(__pthread_attr_t *__attr, void *__stackaddr),pthread_attr_setstackaddr,(__attr,__stackaddr))
#endif /* !__local___localdep_crt_pthread_attr_setstackaddr_defined */
/* Dependency: crt_pthread_attr_setstacksize from pthread */
#ifndef __local___localdep_crt_pthread_attr_setstacksize_defined
#define __local___localdep_crt_pthread_attr_setstacksize_defined 1
/* >> pthread_attr_setstacksize(3)
 * Add information about the minimum stack size needed for the thread
 * to be started. This size must never be less than `PTHREAD_STACK_MIN'
 * and must also not exceed the system limits
 * @return: EOK:    Success
 * @return: EINVAL: `stacksize' is too small */
__CREDIRECT(__ATTR_NONNULL((1)),__errno_t,__NOTHROW_NCX,__localdep_crt_pthread_attr_setstacksize,(__pthread_attr_t *__attr, __SIZE_TYPE__ __stacksize),pthread_attr_setstacksize,(__attr,__stacksize))
#endif /* !__local___localdep_crt_pthread_attr_setstacksize_defined */
/* >> pthread_attr_setstack(3)
 * The following two interfaces are intended to replace the last two. They
 * require setting the address as well as the size since only setting the
 * address will make the implementation on some architectures impossible
 * @return: EOK:    Success
 * @return: EINVAL: `stacksize' is too small, or the stack isn't suitably aligned */
__LOCAL_LIBC(pthread_attr_setstack) __ATTR_NONNULL((1)) __errno_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(pthread_attr_setstack))(__pthread_attr_t *__attr, void *__stackaddr, __SIZE_TYPE__ __stacksize) {
	__errno_t __result;
	__result = __localdep_crt_pthread_attr_setstackaddr(__attr, __stackaddr);
	if __likely(__result == 0)
		__result = __localdep_crt_pthread_attr_setstacksize(__attr, __stacksize);
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_pthread_attr_setstack_defined
#define __local___localdep_pthread_attr_setstack_defined 1
#define __localdep_pthread_attr_setstack __LIBC_LOCAL_NAME(pthread_attr_setstack)
#endif /* !__local___localdep_pthread_attr_setstack_defined */
#else /* __CRT_HAVE_pthread_attr_setstackaddr && __CRT_HAVE_pthread_attr_setstacksize */
#undef __local_pthread_attr_setstack_defined
#endif /* !__CRT_HAVE_pthread_attr_setstackaddr || !__CRT_HAVE_pthread_attr_setstacksize */
#endif /* !__local_pthread_attr_setstack_defined */
