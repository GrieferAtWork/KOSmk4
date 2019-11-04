/* HASH CRC-32:0xf28a306a */
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
#ifndef __local_cnd_wait_defined
#ifdef __CRT_HAVE_pthread_cond_wait
#define __local_cnd_wait_defined 1
#include <bits/threads.h>

#include <bits/pthreadtypes.h>
/* Dependency: "pthread_cond_wait" */
#ifndef ____localdep_pthread_cond_wait_defined
#define ____localdep_pthread_cond_wait_defined 1
#ifdef __CRT_HAVE_pthread_cond_wait
/* Wait for condition variable COND to be signaled or broadcast.
 * MUTEX is assumed to be locked before. */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,__localdep_pthread_cond_wait,(__pthread_cond_t *__restrict __cond, __pthread_mutex_t *__restrict __mutex),pthread_cond_wait,(__cond,__mutex))
#else /* LIBC: pthread_cond_wait */
#undef ____localdep_pthread_cond_wait_defined
#endif /* pthread_cond_wait... */
#endif /* !____localdep_pthread_cond_wait_defined */

__NAMESPACE_LOCAL_BEGIN
/* Block current thread on the condition variable pointed by COND
 * s.a. `pthread_cond_wait()' */
__LOCAL_LIBC(cnd_wait) __ATTR_NONNULL((1, 2)) int
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(cnd_wait))(__cnd_t *__restrict __cond,
                                                      __mtx_t *__restrict __mutex) {
#line 412 "kos/src/libc/magic/threads.c"
	int __error;
	__error = __localdep_pthread_cond_wait((__pthread_cond_t *)__cond,
	                          (__pthread_mutex_t *)__mutex);
	if __likely(!__error)
		return 0; /* thrd_success */
	return 2; /* thrd_error */
}
__NAMESPACE_LOCAL_END
#endif /* defined(__CRT_HAVE_pthread_cond_wait) */
#endif /* !__local_cnd_wait_defined */
