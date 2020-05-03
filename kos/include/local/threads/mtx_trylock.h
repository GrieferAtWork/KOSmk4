/* HASH CRC-32:0xedb2c8c1 */
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
#ifndef __local_mtx_trylock_defined
#ifdef __CRT_HAVE_pthread_mutex_trylock
#define __local_mtx_trylock_defined 1
#include <__crt.h>
#include <bits/threads.h>

#include <bits/pthreadtypes.h>
#include <asm/threads.h>
/* Dependency: "pthread_mutex_trylock" */
#ifndef ____localdep_pthread_mutex_trylock_defined
#define ____localdep_pthread_mutex_trylock_defined 1
#ifdef __CRT_HAVE_pthread_mutex_trylock
/* Try locking a mutex */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,__localdep_pthread_mutex_trylock,(__pthread_mutex_t *__mutex),pthread_mutex_trylock,(__mutex))
#else /* LIBC: pthread_mutex_trylock */
#undef ____localdep_pthread_mutex_trylock_defined
#endif /* pthread_mutex_trylock... */
#endif /* !____localdep_pthread_mutex_trylock_defined */

__NAMESPACE_LOCAL_BEGIN
/* Try to lock the mutex pointed by MUTEX without blocking.
 * If the mutex is free the current threads takes control of
 * it, otherwise it returns immediately
 * s.a. `pthread_mutex_trylock()' */
__LOCAL_LIBC(mtx_trylock) __ATTR_NONNULL((1)) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(mtx_trylock))(__mtx_t *__restrict __mutex) {
#line 380 "kos/src/libc/magic/threads.c"
	int __error;
	__error = __localdep_pthread_mutex_trylock((__pthread_mutex_t *)__mutex);
	if __likely(!__error)
		return __thrd_success;
	return __thrd_error;
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE_pthread_mutex_trylock */
#endif /* !__local_mtx_trylock_defined */
