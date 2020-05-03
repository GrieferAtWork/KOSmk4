/* HASH CRC-32:0x2938bdea */
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
#ifndef GUARD_LIBC_AUTO_PTHREAD_C
#define GUARD_LIBC_AUTO_PTHREAD_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "pthread.h"

DECL_BEGIN

#ifndef __KERNEL__
/* Compare two thread identifiers */
INTERN ATTR_CONST
ATTR_WEAK ATTR_SECTION(".text.crt.sched.pthread.pthread_equal") int
NOTHROW_NCX(LIBCCALL libc_pthread_equal)(pthread_t pthread1,
                                         pthread_t pthread2) {
#line 318 "kos/src/libc/magic/pthread.c"
	return pthread1 == pthread2;
}

/* Function called to call the cleanup handler. As an extern inline
 * function the compiler is free to decide inlining the change when
 * needed or fall back on the copy which must exist somewhere else */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.pthread.__pthread_cleanup_routine") void
NOTHROW_NCX(LIBCCALL libc___pthread_cleanup_routine)(struct __pthread_cleanup_frame *frame) {
#line 643 "kos/src/libc/magic/pthread.c"
	if (frame->__do_it)
		(*frame->__cancel_routine)(frame->__cancel_arg);
}

#include <hybrid/__atomic.h>
/* Initialize the spinlock LOCK. If PSHARED is nonzero the
 * spinlock can be shared between different processes */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.pthread.pthread_spin_init") int
NOTHROW_NCX(LIBCCALL libc_pthread_spin_init)(pthread_spinlock_t *lock,
                                             int pshared) {
#line 1253 "kos/src/libc/magic/pthread.c"
	(void)pshared;
	__hybrid_atomic_store(*lock, 0, __ATOMIC_RELAXED);
	return 0;
}

/* Destroy the spinlock LOCK */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.pthread.pthread_spin_destroy") int
NOTHROW_NCX(LIBCCALL libc_pthread_spin_destroy)(pthread_spinlock_t *lock) {
#line 1261 "kos/src/libc/magic/pthread.c"
	COMPILER_IMPURE();
	(void)lock; /* no-op */
	return 0;
}

#include <hybrid/__atomic.h>

#include <hybrid/sched/__yield.h>
/* Wait until spinlock LOCK is retrieved */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.pthread.pthread_spin_lock") int
NOTHROW_NCX(LIBCCALL libc_pthread_spin_lock)(pthread_spinlock_t *lock) {
#line 1271 "kos/src/libc/magic/pthread.c"
	while (libc_pthread_spin_trylock(lock) != 0)
		__hybrid_yield();
	return 0;
}

#include <hybrid/__atomic.h>

#include <parts/errno.h>
/* Try to lock spinlock LOCK */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.pthread.pthread_spin_trylock") int
NOTHROW_NCX(LIBCCALL libc_pthread_spin_trylock)(pthread_spinlock_t *lock) {
#line 1281 "kos/src/libc/magic/pthread.c"
	if (__hybrid_atomic_xch(*lock, 1, __ATOMIC_ACQUIRE) == 0)
		return 0;
#ifdef EBUSY
	return EBUSY;
#elif defined(EWOULDBLOCK)
	return EWOULDBLOCK;
#elif defined(EAGAIN)
	return EAGAIN;
#else /* ... */
	return 1;
#endif /* !... */
}

#include <hybrid/__atomic.h>
/* Release spinlock LOCK */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.pthread.pthread_spin_unlock") int
NOTHROW_NCX(LIBCCALL libc_pthread_spin_unlock)(pthread_spinlock_t *lock) {
#line 1298 "kos/src/libc/magic/pthread.c"
	__hybrid_atomic_store(*lock, 0, __ATOMIC_RELEASE);
	return 0;
}

#endif /* !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_WEAK_ALIAS(pthread_equal, libc_pthread_equal);
DEFINE_PUBLIC_WEAK_ALIAS(thrd_equal, libc_pthread_equal);
DEFINE_PUBLIC_WEAK_ALIAS(__pthread_cleanup_routine, libc___pthread_cleanup_routine);
DEFINE_PUBLIC_WEAK_ALIAS(pthread_spin_init, libc_pthread_spin_init);
DEFINE_PUBLIC_WEAK_ALIAS(pthread_spin_destroy, libc_pthread_spin_destroy);
DEFINE_PUBLIC_WEAK_ALIAS(pthread_spin_lock, libc_pthread_spin_lock);
DEFINE_PUBLIC_WEAK_ALIAS(pthread_spin_trylock, libc_pthread_spin_trylock);
DEFINE_PUBLIC_WEAK_ALIAS(pthread_spin_unlock, libc_pthread_spin_unlock);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_PTHREAD_C */
