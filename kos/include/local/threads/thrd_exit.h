/* HASH CRC-32:0x71e9e0d0 */
/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_thrd_exit_defined
#define __local_thrd_exit_defined 1
#include <__crt.h>
#ifdef __CRT_HAVE_pthread_exit
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: pthread_exit from pthread */
#if !defined(__local___localdep_pthread_exit_defined) && defined(__CRT_HAVE_pthread_exit)
#define __local___localdep_pthread_exit_defined 1
/* Terminate calling thread.
 * The registered cleanup handlers are called via exception handling */
__CREDIRECT_VOID(__ATTR_NORETURN,__THROWING,__localdep_pthread_exit,(void *__retval),pthread_exit,(__retval))
#endif /* !__local___localdep_pthread_exit_defined && __CRT_HAVE_pthread_exit */
/* Terminate current thread execution, cleaning up any thread local
 * storage and freeing resources. Returns the value specified in RES
 * s.a. `pthread_exit()' */
__LOCAL_LIBC(thrd_exit) __ATTR_NORETURN void
(__LIBCCALL __LIBC_LOCAL_NAME(thrd_exit))(int __res) __THROWS(...) {
	__localdep_pthread_exit((void *)(__UINTPTR_TYPE__)(unsigned int)__res);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_thrd_exit_defined
#define __local___localdep_thrd_exit_defined 1
#define __localdep_thrd_exit __LIBC_LOCAL_NAME(thrd_exit)
#endif /* !__local___localdep_thrd_exit_defined */
#else /* __CRT_HAVE_pthread_exit */
#undef __local_thrd_exit_defined
#endif /* !__CRT_HAVE_pthread_exit */
#endif /* !__local_thrd_exit_defined */
