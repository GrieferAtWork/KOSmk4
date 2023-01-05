/* HASH CRC-32:0xbd56df10 */
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
#ifndef __local_thrd_create_defined
#define __local_thrd_create_defined
#include <__crt.h>
#ifdef __CRT_HAVE_pthread_create
#include <bits/crt/threads.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_pthread_create_defined
#define __local___localdep_pthread_create_defined
__NAMESPACE_LOCAL_END
#include <bits/types.h>
#include <bits/crt/pthreadtypes.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN_OPT(2) __ATTR_OUT(1) __ATTR_NONNULL((3)),__errno_t,__NOTHROW_NCX,__localdep_pthread_create,(__pthread_t *__restrict __p_newthread, __pthread_attr_t const *__restrict __attr, void *(__LIBCCALL *__start_routine)(void *__arg), void *__arg),pthread_create,(__p_newthread,__attr,__start_routine,__arg))
#endif /* !__local___localdep_pthread_create_defined */
__NAMESPACE_LOCAL_END
#include <asm/crt/threads.h>
#include <libc/errno.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(thrd_create) __ATTR_OUT(1) __ATTR_NONNULL((2)) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(thrd_create))(__thrd_t *__thr, int (__LIBCCALL *__func)(void *__arg), void *__arg) {
	__errno_t __error;
	__STATIC_ASSERT(sizeof(int) <= sizeof(void *));
	__error = (__NAMESPACE_LOCAL_SYM __localdep_pthread_create)((__pthread_t *)__thr, __NULLPTR,
	                       (void *(__LIBCCALL *)(void *))(void *)__func,
	                       __arg);
	if __likely(!__error)
		return __thrd_success;
#if defined(__thrd_nomem) && defined(__ENOMEM)
	if (__error == __ENOMEM)
		return __thrd_nomem;
#endif /* __thrd_nomem && __ENOMEM */
	return __thrd_error;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_thrd_create_defined
#define __local___localdep_thrd_create_defined
#define __localdep_thrd_create __LIBC_LOCAL_NAME(thrd_create)
#endif /* !__local___localdep_thrd_create_defined */
#else /* __CRT_HAVE_pthread_create */
#undef __local_thrd_create_defined
#endif /* !__CRT_HAVE_pthread_create */
#endif /* !__local_thrd_create_defined */
