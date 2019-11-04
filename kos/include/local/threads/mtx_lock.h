/* HASH CRC-32:0xb09689d7 */
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
#ifndef __local_mtx_lock_defined
#ifdef __CRT_HAVE_pthread_mutex_lock
#define __local_mtx_lock_defined 1
#include <bits/threads.h>

#include <bits/pthreadtypes.h>
/* Dependency: "pthread_mutex_lock" */
#ifndef ____localdep_pthread_mutex_lock_defined
#define ____localdep_pthread_mutex_lock_defined 1
#ifdef __CRT_HAVE_pthread_mutex_lock
/* Lock a mutex */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,__localdep_pthread_mutex_lock,(__pthread_mutex_t *__mutex),pthread_mutex_lock,(__mutex))
#else /* LIBC: pthread_mutex_lock */
#undef ____localdep_pthread_mutex_lock_defined
#endif /* pthread_mutex_lock... */
#endif /* !____localdep_pthread_mutex_lock_defined */

__NAMESPACE_LOCAL_BEGIN
/* Block the current thread until the mutex pointed to by MUTEX is
 * unlocked.  In that case current thread will not be blocked
 * s.a. `pthread_mutex_lock()' */
__LOCAL_LIBC(mtx_lock) __ATTR_NONNULL((1)) int
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(mtx_lock))(__mtx_t *__restrict __mutex) {
#line 277 "kos/src/libc/magic/threads.c"
	int __error;
	__error = __localdep_pthread_mutex_lock((__pthread_mutex_t *)__mutex);
	if __likely(!__error)
		return 0; /* thrd_success */
	return 2; /* thrd_error */
}
__NAMESPACE_LOCAL_END
#endif /* defined(__CRT_HAVE_pthread_mutex_lock) */
#endif /* !__local_mtx_lock_defined */
