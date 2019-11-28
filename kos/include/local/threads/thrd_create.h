/* HASH CRC-32:0x3c0a074a */
/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_thrd_create_defined
#ifdef __CRT_HAVE_pthread_create
#define __local_thrd_create_defined 1
#include <bits/pthreadtypes.h>
#ifndef ____pthread_start_routine_t_defined
#define ____pthread_start_routine_t_defined 1
typedef void *(*__pthread_start_routine_t)(void *);
#endif /* !____pthread_start_routine_t_defined */
#include <bits/threads.h>

#include <parts/errno.h>
/* Dependency: "pthread_create" */
#ifndef ____localdep_pthread_create_defined
#define ____localdep_pthread_create_defined 1
#ifdef __CRT_HAVE_pthread_create
/* Create a new thread, starting with execution of START-ROUTINE
 * getting passed ARG. Creation attributed come from ATTR. The new
 * handle is stored in *NEWTHREAD */
__CREDIRECT(__ATTR_NONNULL((1, 3)),int,__NOTHROW_NCX,__localdep_pthread_create,(__pthread_t *__restrict __newthread, __pthread_attr_t const *__restrict __attr, __pthread_start_routine_t __start_routine, void *__restrict __arg),pthread_create,(__newthread,__attr,__start_routine,__arg))
#else /* LIBC: pthread_create */
#undef ____localdep_pthread_create_defined
#endif /* pthread_create... */
#endif /* !____localdep_pthread_create_defined */

__NAMESPACE_LOCAL_BEGIN
/* Create a new thread executing the function FUNC.  Arguments for FUNC
 * are passed through ARG. If successful, THR is set to new thread identifier */
__LOCAL_LIBC(thrd_create) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(thrd_create))(__thrd_t *__thr,
                                                         __thrd_start_t __func,
                                                         void *__arg) {
#line 100 "kos/src/libc/magic/threads.c"
	int __error;
	__STATIC_ASSERT(sizeof(int) <= sizeof(void *));
	__error = __localdep_pthread_create((__pthread_t *)__thr, __NULLPTR,
	                       (__pthread_start_routine_t)(void *)__func,
	                       __arg);
	if __likely(!__error)
		return 0; /* thrd_success */
#ifdef __ENOMEM
	if (__error == __ENOMEM)
		return 3; /* thrd_nomem */
#endif /* __ENOMEM */
	return 2; /* thrd_error */
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE_pthread_create */
#endif /* !__local_thrd_create_defined */
