/* HASH CRC-32:0xba77e67b */
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
#ifndef __local_thrd_exit_defined
#define __local_thrd_exit_defined
#include <__crt.h>
#if defined(__CRT_HAVE_pthread_exit) || defined(__CRT_HAVE_thr_exit) || defined(__CRT_HAVE_cthread_exit)
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_pthread_exit_defined
#define __local___localdep_pthread_exit_defined
#ifdef __CRT_HAVE_pthread_exit
__CREDIRECT_VOID(__ATTR_NORETURN __ATTR_ACCESS_NONE(1),__THROWING,__localdep_pthread_exit,(void *__retval),pthread_exit,(__retval))
#elif defined(__CRT_HAVE_thr_exit)
__CREDIRECT_VOID(__ATTR_NORETURN __ATTR_ACCESS_NONE(1),__THROWING,__localdep_pthread_exit,(void *__retval),thr_exit,(__retval))
#elif defined(__CRT_HAVE_cthread_exit)
__CREDIRECT_VOID(__ATTR_NORETURN __ATTR_ACCESS_NONE(1),__THROWING,__localdep_pthread_exit,(void *__retval),cthread_exit,(__retval))
#else /* ... */
#undef __local___localdep_pthread_exit_defined
#endif /* !... */
#endif /* !__local___localdep_pthread_exit_defined */
__LOCAL_LIBC(thrd_exit) __ATTR_NORETURN void
(__LIBCCALL __LIBC_LOCAL_NAME(thrd_exit))(int __res) __THROWS(...) {
	(__NAMESPACE_LOCAL_SYM __localdep_pthread_exit)((void *)(__UINTPTR_TYPE__)(unsigned int)__res);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_thrd_exit_defined
#define __local___localdep_thrd_exit_defined
#define __localdep_thrd_exit __LIBC_LOCAL_NAME(thrd_exit)
#endif /* !__local___localdep_thrd_exit_defined */
#else /* __CRT_HAVE_pthread_exit || __CRT_HAVE_thr_exit || __CRT_HAVE_cthread_exit */
#undef __local_thrd_exit_defined
#endif /* !__CRT_HAVE_pthread_exit && !__CRT_HAVE_thr_exit && !__CRT_HAVE_cthread_exit */
#endif /* !__local_thrd_exit_defined */
