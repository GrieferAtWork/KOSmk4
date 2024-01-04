/* HASH CRC-32:0x44ce4a9f */
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
#ifndef __local_cthread_fork_defined
#define __local_cthread_fork_defined
#include <__crt.h>
#ifdef __CRT_HAVE_pthread_create
struct cthread;
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
#include <libc/errno.h>
#include <bits/types.h>
#include <bits/crt/pthreadtypes.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(cthread_fork) __ATTR_NONNULL((1)) struct cthread *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(cthread_fork))(void * (__LIBCCALL *__start_routine)(void * __arg), void * __arg) {
	__pthread_t __result;
	__errno_t __error;
	__error = (__NAMESPACE_LOCAL_SYM __localdep_pthread_create)(&__result, __NULLPTR, __start_routine, __arg);
	if __unlikely(__error != 0) {
		__libc_seterrno(__error);
		__result = (__pthread_t)__NULLPTR;
	}
	return (struct cthread *)__result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_cthread_fork_defined
#define __local___localdep_cthread_fork_defined
#define __localdep_cthread_fork __LIBC_LOCAL_NAME(cthread_fork)
#endif /* !__local___localdep_cthread_fork_defined */
#else /* __CRT_HAVE_pthread_create */
#undef __local_cthread_fork_defined
#endif /* !__CRT_HAVE_pthread_create */
#endif /* !__local_cthread_fork_defined */
