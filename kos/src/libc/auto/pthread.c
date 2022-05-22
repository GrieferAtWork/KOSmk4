/* HASH CRC-32:0xa5e1a994 */
/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
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
#include "../user/kos.except.h"
#include "../user/kos.futex.h"
#include "../user/sched.h"
#include "../user/unistd.h"

DECL_BEGIN

#ifndef __KERNEL__
/* >> pthread_equal(3)
 * Compare two thread identifiers
 * @return: 0 : Given threads are non-equal
 * @return: * : Given threads are equal */
INTERN ATTR_SECTION(".text.crt.sched.pthread") ATTR_CONST WUNUSED int
NOTHROW(LIBCCALL libc_pthread_equal)(pthread_t thr1,
                                     pthread_t thr2) {
	return thr1 == thr2;
}
#include <asm/crt/pthreadvalues.h>
#include <hybrid/__atomic.h>
#include <hybrid/sched/__yield.h>
#include <asm/os/errno.h>
#include <kos/asm/futex.h>
/* >> pthread_once(3)
 * Guarantee that the initialization function `init_routine' will be called
 * only  once,  even if  pthread_once is  executed  several times  with the
 * same `once_control' argument. `once_control' must  point to a static  or
 * extern variable initialized to `PTHREAD_ONCE_INIT'.
 * @return: EOK: Success */
INTERN ATTR_SECTION(".text.crt.sched.pthread") ATTR_INOUT(1) NONNULL((2)) errno_t
(LIBCCALL libc_pthread_once)(pthread_once_t *once_control,
                             void (LIBCCALL *init_routine)(void)) THROWS(...) {
#undef __PRIVATE_PTHREAD_ONCE_USES_FUTEX

#if __SIZEOF_PTHREAD_ONCE_T == __SIZEOF_POINTER__
#define __PRIVATE_PTHREAD_ONCE_USES_FUTEX
#elif defined(LFUTEX_WAIT_WHILE_EX)
#define __PRIVATE_PTHREAD_ONCE_USES_FUTEX
#endif /* ... */


	/*
	 * Internal state values for pthread_once():
	 *  - __PTHREAD_ONCE_INIT + 0: Not yet called
	 *  - __PTHREAD_ONCE_INIT + 1: Currently being called
	 *  - __PTHREAD_ONCE_INIT + 2: Was called
	 * #ifdef __PRIVATE_PTHREAD_ONCE_USES_FUTEX
	 *  - __PTHREAD_ONCE_INIT + 3: Currently being called, and other threads are waiting
	 * #endif
	 *
	 */
	pthread_once_t status;
again:
	status = __hybrid_atomic_cmpxch_val(*once_control,
	                                    __PTHREAD_ONCE_INIT,
	                                    __PTHREAD_ONCE_INIT + 1,
	                                    __ATOMIC_SEQ_CST,
	                                    __ATOMIC_SEQ_CST);
	if (status == __PTHREAD_ONCE_INIT) {
		/* To comply with POSIX, we  must be able to roll-back  our
		 * initialization when `init_routine' "cancels" our thread. */
#ifdef __cplusplus
		try {
			(*init_routine)();
		} catch (...) {
			/* roll-back... */
#ifdef __PRIVATE_PTHREAD_ONCE_USES_FUTEX
			if (__hybrid_atomic_xch(*once_control, __PTHREAD_ONCE_INIT,
			                        __ATOMIC_RELEASE) == __PTHREAD_ONCE_INIT + 3)
				libc_futex_wakeall((lfutex_t *)once_control);
#else /* __PRIVATE_PTHREAD_ONCE_USES_FUTEX */
			__hybrid_atomic_store(*once_control,
			                      __PTHREAD_ONCE_INIT,
			                      __ATOMIC_RELEASE);
#endif /* !__PRIVATE_PTHREAD_ONCE_USES_FUTEX */

			libc_except_rethrow();



		}
#else /* __cplusplus */
		(*init_routine)();
#endif /* !__cplusplus */

		/* Remember that the function was called. */
#ifdef __PRIVATE_PTHREAD_ONCE_USES_FUTEX
		if (__hybrid_atomic_xch(*once_control, __PTHREAD_ONCE_INIT + 2,
		                        __ATOMIC_RELEASE) == __PTHREAD_ONCE_INIT + 3)
			libc_futex_wakeall((lfutex_t *)once_control);
#else /* __PRIVATE_PTHREAD_ONCE_USES_FUTEX */
		__hybrid_atomic_store(*once_control,
		                      __PTHREAD_ONCE_INIT + 2,
		                      __ATOMIC_RELEASE);
#endif /* !__PRIVATE_PTHREAD_ONCE_USES_FUTEX */
	} else if (status != __PTHREAD_ONCE_INIT + 2) {
#ifdef __PRIVATE_PTHREAD_ONCE_USES_FUTEX
		if unlikely(status != __PTHREAD_ONCE_INIT + 1 &&
		            status != __PTHREAD_ONCE_INIT + 3)
#else /* __PRIVATE_PTHREAD_ONCE_USES_FUTEX */
		if unlikely(status != __PTHREAD_ONCE_INIT + 1)
#endif /* !__PRIVATE_PTHREAD_ONCE_USES_FUTEX */
		{
			/* Quote(https://man7.org/linux/man-pages/man3/pthread_once.3p.html):
			 * """
			 * If  an implementation  detects that  the value  specified by the
			 * once_control argument  to pthread_once()  does  not refer  to  a
			 * pthread_once_t object  initialized by  PTHREAD_ONCE_INIT, it  is
			 * recommended that the function should fail and report an [EINVAL]
			 * error.
			 * """
			 */

			return EINVAL;



		}

		/* Wait for some other thread to finish init_routine() */
#ifdef __PRIVATE_PTHREAD_ONCE_USES_FUTEX
		if (status == __PTHREAD_ONCE_INIT + 1) {
			/* Request a futex-wake call once initialization
			 * completes  in  whatever thread  is  doing it. */
			if (!__hybrid_atomic_cmpxch(*once_control,
			                            __PTHREAD_ONCE_INIT + 1,
			                            __PTHREAD_ONCE_INIT + 3,
			                            __ATOMIC_SEQ_CST,
			                            __ATOMIC_SEQ_CST))
				goto again;
		}
#if __SIZEOF_PTHREAD_ONCE_T == __SIZEOF_POINTER__
		libc_futex_waitwhile((lfutex_t *)once_control, __PTHREAD_ONCE_INIT + 3);
#else /* __SIZEOF_PTHREAD_ONCE_T == __SIZEOF_POINTER__ */
		{
			static pthread_once_t const _init_marker = __PTHREAD_ONCE_INIT + 3;
			libc_lfutex64((lfutex_t *)once_control, LFUTEX_WAIT_WHILE_EX,
			         (lfutex_t)&_init_marker, (struct timespec64 const *)NULL,
			         sizeof(pthread_once_t));
		}
#endif /* __SIZEOF_PTHREAD_ONCE_T != __SIZEOF_POINTER__ */
#else /* __PRIVATE_PTHREAD_ONCE_USES_FUTEX */
		do {
			__hybrid_yield();
		} while (__hybrid_atomic_load(*once_control, __ATOMIC_ACQUIRE) ==
		         __PTHREAD_ONCE_INIT + 1);
#endif /* !__PRIVATE_PTHREAD_ONCE_USES_FUTEX */

		/* Must re-check the once-status, since another thread may have
		 * rolled back completion  in case its  call to  `init_routine'
		 * resulted in an exception being called. (or to speak in terms
		 * of POSIX, caused its thread to be "canceled") */
		goto again;
	}
	return 0;
#undef __PRIVATE_PTHREAD_ONCE_USES_FUTEX
}
/* Function called to call the cleanup handler. As an extern inline
 * function the compiler is free to decide inlining the change when
 * needed or fall back on the copy which must exist somewhere else */
INTERN ATTR_SECTION(".text.crt.sched.pthread") void
NOTHROW_NCX(LIBCCALL libc___pthread_cleanup_routine)(struct __pthread_cleanup_frame *frame) {
	if (frame->__do_it)
		(*frame->__cancel_routine)(frame->__cancel_arg);
}
#include <hybrid/__atomic.h>
/* >> pthread_spin_init(3)
 * Initialize the spinlock `lock'. If `pshared' is nonzero
 * the  spinlock can be shared between different processes
 * @return: EOK: Success */
INTERN ATTR_SECTION(".text.crt.sched.pthread") ATTR_OUT(1) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_spin_init)(pthread_spinlock_t *lock,
                                             int pshared) {
	(void)pshared;
	__hybrid_atomic_store(*lock, 0, __ATOMIC_RELAXED);
	return 0;
}
/* >> pthread_spin_destroy(3)
 * Destroy the spinlock `lock'
 * @return: EOK: Success */
INTERN ATTR_SECTION(".text.crt.sched.pthread") ATTR_INOUT(1) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_spin_destroy)(pthread_spinlock_t *lock) {
	COMPILER_IMPURE();
	(void)lock; /* no-op */
	return 0;
}
#include <hybrid/__atomic.h>
#include <hybrid/sched/__yield.h>
/* >> pthread_spin_lock(3)
 * Wait until spinlock `lock' is retrieved
 * @return: EOK: Success */
INTERN ATTR_SECTION(".text.crt.sched.pthread") ATTR_INOUT(1) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_spin_lock)(pthread_spinlock_t *lock) {
	while (libc_pthread_spin_trylock(lock) != 0)
		__hybrid_yield();
	return 0;
}
#include <hybrid/__atomic.h>
#include <libc/errno.h>
/* >> pthread_spin_trylock(3)
 * Try to lock spinlock `lock'
 * @return: EOK:   Success
 * @return: EBUSY: Lock has already been acquired */
INTERN ATTR_SECTION(".text.crt.sched.pthread") WUNUSED ATTR_INOUT(1) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_spin_trylock)(pthread_spinlock_t *lock) {
	if (__hybrid_atomic_xch(*lock, 1, __ATOMIC_ACQUIRE) == 0)
		return 0;

	return EBUSY;







}
#include <hybrid/__atomic.h>
/* >> pthread_spin_unlock(3)
 * Release  spinlock  `lock'
 * @return: EOK: Success */
INTERN ATTR_SECTION(".text.crt.sched.pthread") ATTR_INOUT(1) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_spin_unlock)(pthread_spinlock_t *lock) {
	__hybrid_atomic_store(*lock, 0, __ATOMIC_RELEASE);
	return 0;
}
#include <hybrid/__atomic.h>
/* >> pthread_key_create_once_np(3)
 * Same as `pthread_key_create()', but the  given `key' must be  pre-initialized
 * using the static initializer `PTHREAD_ONCE_KEY_NP', whilst this function will
 * make  sure that  even in the  event of multiple  simultaneous threads calling
 * this function, only one will create the  key, and all others will wait  until
 * the key has been  created. Once the  key was created,  further calls to  this
 * function will no longer block, but simply return immediately.
 * @return: EOK:    Success
 * @return: ENOMEM: Insufficient memory to create the key */
INTERN ATTR_SECTION(".text.crt.sched.pthread") ATTR_OUT(1) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_key_create_once_np)(pthread_key_t *key,
                                                      void (LIBKCALL *destr_function)(void *)) {
	pthread_key_t kv;
	errno_t error;
again:
	kv = __hybrid_atomic_load(*key, __ATOMIC_ACQUIRE);
#ifdef __PTHREAD_ONCE_KEY_NP
	if (kv != __PTHREAD_ONCE_KEY_NP)
#else /* __PTHREAD_ONCE_KEY_NP */
	if (kv != (pthread_key_t)-1)
#endif /* !__PTHREAD_ONCE_KEY_NP */
	{
		return 0; /* Already initialized. */
	}

	/* Try to do the init ourselves. */
	error = libc_pthread_key_create(&kv, destr_function);
	if unlikely(error != 0)
		return error; /* Error... */

	/* Try to save the results. */
#ifdef __PTHREAD_ONCE_KEY_NP
	if unlikely(!__hybrid_atomic_cmpxch(*key, __PTHREAD_ONCE_KEY_NP, kv,
	                                    __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST))
#else /* __PTHREAD_ONCE_KEY_NP */
	if unlikely(!__hybrid_atomic_cmpxch(*key, (pthread_key_t)-1, kv,
	                                    __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST))
#endif /* !__PTHREAD_ONCE_KEY_NP */
	{
		/* Someone else was faster. - Destroy our version of the key,  and
		 * try again in order to use the other key that was created in the
		 * mean time. */

		libc_pthread_key_delete(kv);

		goto again;
	}

	/* Success: key has been created */
	return 0;
}
#include <bits/os/cpu_set.h>
/* >> pthread_num_processors_np(3)
 * @return: * : The number of cpus that the calling thread is able to run on */
INTERN ATTR_SECTION(".text.crt.sched.pthread_ext") WUNUSED __STDC_INT_AS_SIZE_T
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

		return EINVAL;



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
 * Returns  1 if the  calling thread is the  main() thread (i.e. the
 * thread  that was  started by the  kernel in order  to execute the
 * calling program), and 0  otherwise. Additionally, -1 is  returned
 * if the  calling  thread  "hasn't been initialized",  though  this
 * isn't a case that can actually happen under KOS's implementation. */
INTERN ATTR_SECTION(".text.crt.sched.pthread_ext") ATTR_CONST WUNUSED int
NOTHROW(LIBCCALL libc_pthread_main_np)(void) {

	return libc_pthread_equal(libc_pthread_mainthread_np(), libc_pthread_self());



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
DEFINE_PUBLIC_ALIAS(thr_keycreate_once, libc_pthread_key_create_once_np);
DEFINE_PUBLIC_ALIAS(pthread_key_create_once_np, libc_pthread_key_create_once_np);
DEFINE_PUBLIC_ALIAS(pthread_num_processors_np, libc_pthread_num_processors_np);
DEFINE_PUBLIC_ALIAS(pthread_set_num_processors_np, libc_pthread_set_num_processors_np);
DEFINE_PUBLIC_ALIAS(thr_main, libc_pthread_main_np);
DEFINE_PUBLIC_ALIAS(pthread_main_np, libc_pthread_main_np);
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_PTHREAD_C */
