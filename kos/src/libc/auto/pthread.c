/* HASH CRC-32:0x632d1fd */
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
#include "../user/pthread.h"
#include "../user/unistd.h"

DECL_BEGIN

#ifndef __KERNEL__
/* Compare two thread identifiers */
INTERN ATTR_SECTION(".text.crt.sched.pthread") ATTR_CONST int
NOTHROW_NCX(LIBCCALL libc_pthread_equal)(pthread_t thr1,
                                         pthread_t thr2) {
	return thr1 == thr2;
}
/* Function called to call the cleanup handler. As an extern inline
 * function the compiler is free to decide inlining the change when
 * needed or fall back on the copy which must exist somewhere else */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1)) void
NOTHROW_NCX(LIBCCALL libc___pthread_cleanup_routine)(struct __pthread_cleanup_frame *frame) {
	if (frame->__do_it)
		(*frame->__cancel_routine)(frame->__cancel_arg);
}
#include <hybrid/__atomic.h>
/* Initialize the spinlock LOCK. If PSHARED is nonzero the
 * spinlock can be shared between different processes */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_pthread_spin_init)(pthread_spinlock_t *lock,
                                             int pshared) {
	(void)pshared;
	__hybrid_atomic_store(*lock, 0, __ATOMIC_RELAXED);
	return 0;
}
/* Destroy the spinlock LOCK */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_pthread_spin_destroy)(pthread_spinlock_t *lock) {
	COMPILER_IMPURE();
	(void)lock; /* no-op */
	return 0;
}
#include <hybrid/__atomic.h>
#include <hybrid/sched/__yield.h>
/* Wait until spinlock LOCK is retrieved */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_pthread_spin_lock)(pthread_spinlock_t *lock) {
	while (libc_pthread_spin_trylock(lock) != 0)
		__hybrid_yield();
	return 0;
}
#include <hybrid/__atomic.h>
#include <parts/errno.h>
/* Try to lock spinlock LOCK */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_pthread_spin_trylock)(pthread_spinlock_t *lock) {
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
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_pthread_spin_unlock)(pthread_spinlock_t *lock) {
	__hybrid_atomic_store(*lock, 0, __ATOMIC_RELEASE);
	return 0;
}
/* Returns 1 if the calling thread is the main() thread (i.e. the
 * thread that was started by the kernel in order to execute the
 * calling program), and 0 otherwise. Additionally, -1 is returned
 * if the calling thread "hasn't been initialized", though this
 * isn't a case that can actually happen under KOS's implementation. */
INTERN ATTR_SECTION(".text.crt.sched.pthread_ext") ATTR_CONST int
NOTHROW_NCX(LIBCCALL libc_pthread_main_np)(void) {
	return libc_gettid() == libc_getpid();
}
#endif /* !__KERNEL__ */

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(thrd_equal, libc_pthread_equal);
DEFINE_PUBLIC_ALIAS(pthread_equal, libc_pthread_equal);
DEFINE_PUBLIC_ALIAS(__pthread_cleanup_routine, libc___pthread_cleanup_routine);
DEFINE_PUBLIC_ALIAS(pthread_spin_init, libc_pthread_spin_init);
DEFINE_PUBLIC_ALIAS(pthread_spin_destroy, libc_pthread_spin_destroy);
DEFINE_PUBLIC_ALIAS(pthread_spin_lock, libc_pthread_spin_lock);
DEFINE_PUBLIC_ALIAS(pthread_spin_trylock, libc_pthread_spin_trylock);
DEFINE_PUBLIC_ALIAS(pthread_spin_unlock, libc_pthread_spin_unlock);
DEFINE_PUBLIC_ALIAS(thr_main, libc_pthread_main_np);
DEFINE_PUBLIC_ALIAS(pthread_main_np, libc_pthread_main_np);
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_PTHREAD_C */
