/* HASH CRC-32:0x22263b69 */
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
#ifndef __local_thrd_detach_defined
#ifdef __CRT_HAVE_pthread_detach
#define __local_thrd_detach_defined 1
#include <__crt.h>
#include <bits/threads.h>
/* Dependency: "pthread_detach" */
#ifndef ____localdep_pthread_detach_defined
#define ____localdep_pthread_detach_defined 1
#ifdef __CRT_HAVE_pthread_detach
/* Indicate that the thread THREAD is never to be joined with PTHREAD_JOIN.
 * The resources of THREAD will therefore be freed immediately when it
 * terminates, instead of waiting for another thread to perform PTHREAD_JOIN on it */
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_pthread_detach,(__pthread_t __pthread),pthread_detach,(__pthread))
#else /* LIBC: pthread_detach */
#undef ____localdep_pthread_detach_defined
#endif /* pthread_detach... */
#endif /* !____localdep_pthread_detach_defined */

__NAMESPACE_LOCAL_BEGIN
/* Detach the thread identified by THR from the current
 * environment (it does not allow join or wait for it)
 * s.a. `pthread_detach()' */
__LOCAL_LIBC(thrd_detach) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(thrd_detach))(__thrd_t __thr) {
#line 230 "kos/src/libc/magic/threads.c"
	int __error;
	__error = __localdep_pthread_detach((__pthread_t)__thr);
	if __likely(!__error)
		return 0; /* thrd_success */
	return 2; /* thrd_error */
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE_pthread_detach */
#endif /* !__local_thrd_detach_defined */
