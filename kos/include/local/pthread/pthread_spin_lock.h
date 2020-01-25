/* HASH CRC-32:0x2b5df110 */
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
#ifndef __local_pthread_spin_lock_defined
#define __local_pthread_spin_lock_defined 1
#include <hybrid/__atomic.h>

#include <hybrid/sched/__yield.h>
/* Dependency: "pthread_spin_trylock" from "pthread" */
#ifndef ____localdep_pthread_spin_trylock_defined
#define ____localdep_pthread_spin_trylock_defined 1
#ifdef __CRT_HAVE_pthread_spin_trylock
/* Try to lock spinlock LOCK */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,__localdep_pthread_spin_trylock,(__pthread_spinlock_t *__lock),pthread_spin_trylock,(__lock))
#else /* LIBC: pthread_spin_trylock */
#include <local/pthread/pthread_spin_trylock.h>
/* Try to lock spinlock LOCK */
#define __localdep_pthread_spin_trylock (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pthread_spin_trylock))
#endif /* pthread_spin_trylock... */
#endif /* !____localdep_pthread_spin_trylock_defined */

__NAMESPACE_LOCAL_BEGIN
/* Wait until spinlock LOCK is retrieved */
__LOCAL_LIBC(pthread_spin_lock) __ATTR_NONNULL((1)) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(pthread_spin_lock))(__pthread_spinlock_t *__lock) {
#line 1270 "kos/src/libc/magic/pthread.c"
	while (__localdep_pthread_spin_trylock(__lock) != 0)
		__hybrid_yield();
	return 0;
}
__NAMESPACE_LOCAL_END
#endif /* !__local_pthread_spin_lock_defined */
