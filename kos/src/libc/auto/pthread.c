/* HASH CRC-32:0x25563ff5 */
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
#include "../user/sched.h"
#include "../user/unistd.h"

DECL_BEGIN

#ifndef __KERNEL__
/* Compare two thread identifiers */
INTERN ATTR_SECTION(".text.crt.sched.pthread") ATTR_CONST int
NOTHROW_NCX(LIBCCALL libc_pthread_equal)(pthread_t thr1,
                                         pthread_t thr2) {
	return thr1 == thr2;
}
#include <asm/crt/pthreadvalues.h>
#include <hybrid/__atomic.h>
/* Guarantee that the initialization function INIT_ROUTINE will be called
 * only once, even if pthread_once is executed several times with the
 * same ONCE_CONTROL argument. ONCE_CONTROL must point to a static or
 * extern variable initialized to PTHREAD_ONCE_INIT. */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1, 2)) errno_t
(LIBCCALL libc_pthread_once)(pthread_once_t *once_control,
                             __pthread_once_routine_t init_routine) THROWS(...) {
	if (__hybrid_atomic_xch(*once_control, __PTHREAD_ONCE_INIT + 1,
	                        __ATOMIC_SEQ_CST) == __PTHREAD_ONCE_INIT) {
		/* Since init_routine() can't indicate failure, we only need a bi-state
		 * control word, as we don't need any sort of is-executing state, and
		 * can directly go from not-executed to was-executed. */
		(*init_routine)();
	}
	return 0;
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
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_spin_init)(pthread_spinlock_t *lock,
                                             int pshared) {
	(void)pshared;
	__hybrid_atomic_store(*lock, 0, __ATOMIC_RELAXED);
	return 0;
}
/* Destroy the spinlock LOCK */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_spin_destroy)(pthread_spinlock_t *lock) {
	COMPILER_IMPURE();
	(void)lock; /* no-op */
	return 0;
}
#include <hybrid/__atomic.h>
#include <hybrid/sched/__yield.h>
/* Wait until spinlock LOCK is retrieved */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_spin_lock)(pthread_spinlock_t *lock) {
	while (libc_pthread_spin_trylock(lock) != 0)
		__hybrid_yield();
	return 0;
}
#include <hybrid/__atomic.h>
#include <parts/errno.h>
/* Try to lock spinlock LOCK */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1)) errno_t
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
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_spin_unlock)(pthread_spinlock_t *lock) {
	__hybrid_atomic_store(*lock, 0, __ATOMIC_RELEASE);
	return 0;
}
#include <bits/sched.h>
INTERN ATTR_SECTION(".text.crt.sched.pthread_ext") __STDC_INT_AS_SIZE_T
NOTHROW_NCX(LIBCCALL libc_pthread_num_processors_np)(void) {
	cpu_set_t cset;
	if unlikely(libc_sched_getaffinity(0, sizeof(cset), &cset) != 0)
		return 1;
	return (__STDC_INT_AS_SIZE_T)__CPU_COUNT_S(sizeof(cset), &cset);
}
#include <bits/sched.h>
#include <parts/errno.h>
INTERN ATTR_SECTION(".text.crt.sched.pthread_ext") errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_set_num_processors_np)(int n) {
	int i, result;
	cpu_set_t cset;
	if (n < 1) {
#ifdef EINVAL
		return EINVAL;
#else /* EINVAL */
		return 1;
#endif /* !EINVAL */
	}
	__CPU_ZERO_S(sizeof(cset), &cset);
	for (i = 0; i < n; ++i) {
		if (!__CPU_SET_S(i, sizeof(cset), &cset))
			break;
	}
	result = libc_sched_setaffinity(0, sizeof(cset), &cset);
	if unlikely(result != 0)
		result = __libc_geterrno_or(1);
	return result;
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
DEFINE_PUBLIC_ALIAS(call_once, libc_pthread_once);
DEFINE_PUBLIC_ALIAS(pthread_once, libc_pthread_once);
DEFINE_PUBLIC_ALIAS(__pthread_cleanup_routine, libc___pthread_cleanup_routine);
DEFINE_PUBLIC_ALIAS(pthread_spin_init, libc_pthread_spin_init);
DEFINE_PUBLIC_ALIAS(pthread_spin_destroy, libc_pthread_spin_destroy);
DEFINE_PUBLIC_ALIAS(pthread_spin_lock, libc_pthread_spin_lock);
DEFINE_PUBLIC_ALIAS(pthread_spin_trylock, libc_pthread_spin_trylock);
DEFINE_PUBLIC_ALIAS(pthread_spin_unlock, libc_pthread_spin_unlock);
DEFINE_PUBLIC_ALIAS(pthread_num_processors_np, libc_pthread_num_processors_np);
DEFINE_PUBLIC_ALIAS(pthread_set_num_processors_np, libc_pthread_set_num_processors_np);
DEFINE_PUBLIC_ALIAS(thr_main, libc_pthread_main_np);
DEFINE_PUBLIC_ALIAS(pthread_main_np, libc_pthread_main_np);
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_PTHREAD_C */
