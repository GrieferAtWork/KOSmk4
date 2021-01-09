/* HASH CRC-32:0x729ff0a5 */
/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
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
/* >> pthread_equal(3)
 * Compare two thread identifiers
 * @return: 0 : Given threads are non-equal
 * @return: * : Given threads are equal */
INTERN ATTR_SECTION(".text.crt.sched.pthread") ATTR_CONST int
NOTHROW(LIBCCALL libc_pthread_equal)(pthread_t thr1,
                                     pthread_t thr2) {
	return thr1 == thr2;
}
#include <asm/crt/pthreadvalues.h>
#include <hybrid/__atomic.h>
#include <hybrid/sched/__yield.h>
/* >> pthread_once(3)
 * Guarantee that the initialization function INIT_ROUTINE will be called
 * only once, even if pthread_once is executed several times with the
 * same ONCE_CONTROL argument. ONCE_CONTROL must point to a static or
 * extern variable initialized to PTHREAD_ONCE_INIT.
 * @return: EOK: Success */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1, 2)) errno_t
(LIBCCALL libc_pthread_once)(pthread_once_t *once_control,
                             __pthread_once_routine_t init_routine) THROWS(...) {
	pthread_once_t status;
	status = __hybrid_atomic_cmpxch_val(*once_control,
	                                    __PTHREAD_ONCE_INIT,
	                                    __PTHREAD_ONCE_INIT + 1,
	                                    __ATOMIC_SEQ_CST,
	                                    __ATOMIC_SEQ_CST);
	if (status == __PTHREAD_ONCE_INIT) {
		(*init_routine)();
		__hybrid_atomic_store(*once_control,
		                      __PTHREAD_ONCE_INIT + 2,
		                      __ATOMIC_RELEASE);
	} else if (status != __PTHREAD_ONCE_INIT + 2) {
		/* Wait for some other thread to finish init_routine() */
		do {
			__hybrid_yield();
		} while (__hybrid_atomic_load(*once_control, __ATOMIC_ACQUIRE) !=
		         __PTHREAD_ONCE_INIT + 2);
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
/* >> pthread_spin_init(3)
 * Initialize the spinlock LOCK. If PSHARED is nonzero the
 * spinlock can be shared between different processes
 * @return: EOK: Success */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_spin_init)(pthread_spinlock_t *lock,
                                             int pshared) {
	(void)pshared;
	__hybrid_atomic_store(*lock, 0, __ATOMIC_RELAXED);
	return 0;
}
/* >> pthread_spin_destroy(3)
 * Destroy the spinlock LOCK
 * @return: EOK: Success */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_spin_destroy)(pthread_spinlock_t *lock) {
	COMPILER_IMPURE();
	(void)lock; /* no-op */
	return 0;
}
#include <hybrid/__atomic.h>
#include <hybrid/sched/__yield.h>
/* >> pthread_spin_lock(3)
 * Wait until spinlock LOCK is retrieved
 * @return: EOK: Success */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_spin_lock)(pthread_spinlock_t *lock) {
	while (libc_pthread_spin_trylock(lock) != 0)
		__hybrid_yield();
	return 0;
}
#include <hybrid/__atomic.h>
#include <libc/errno.h>
/* >> pthread_spin_trylock(3)
 * Try to lock spinlock LOCK
 * @return: EOK:   Success
 * @return: EBUSY: Lock has already been acquired */
INTERN ATTR_SECTION(".text.crt.sched.pthread") WUNUSED NONNULL((1)) errno_t
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
/* >> pthread_spin_unlock(3)
 * Release spinlock LOCK
 * @return: EOK: Success */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_spin_unlock)(pthread_spinlock_t *lock) {
	__hybrid_atomic_store(*lock, 0, __ATOMIC_RELEASE);
	return 0;
}
#include <bits/os/cpu_set.h>
/* >> pthread_num_processors_np(3)
 * @return: * : The number of cpus that the calling thread is able to run on */
INTERN ATTR_SECTION(".text.crt.sched.pthread_ext") __STDC_INT_AS_SIZE_T
NOTHROW_NCX(LIBCCALL libc_pthread_num_processors_np)(void) {
	cpu_set_t cset;
	if unlikely(libc_sched_getaffinity(0, sizeof(cset), &cset) != 0)
		return 1;
	return (__STDC_INT_AS_SIZE_T)__CPU_COUNT_S(sizeof(cset), &cset);
}
#include <bits/os/cpu_set.h>
#include <libc/errno.h>
/* >> pthread_set_num_processors_np(3)
 * Restrict the calling thread to only run on the first `n' cpus
 * @return: EOK:    Success
 * @return: EINVAL: `n' was specified as less than `1'
 * @return: * :     Same as `errno' after a call to `sched_setaffinity(2)' */
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
/* >> pthread_main_np(3)
 * Returns 1 if the calling thread is the main() thread (i.e. the
 * thread that was started by the kernel in order to execute the
 * calling program), and 0 otherwise. Additionally, -1 is returned
 * if the calling thread "hasn't been initialized", though this
 * isn't a case that can actually happen under KOS's implementation. */
INTERN ATTR_SECTION(".text.crt.sched.pthread_ext") ATTR_CONST int
NOTHROW(LIBCCALL libc_pthread_main_np)(void) {
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
