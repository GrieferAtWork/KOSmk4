/* HASH CRC-32:0xf5d2d7e0 */
/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_AUTO_THREADS_C
#define GUARD_LIBC_AUTO_THREADS_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../user/threads.h"
#include "../user/pthread.h"
#include "../user/unistd.h"

DECL_BEGIN

STATIC_ASSERT(sizeof(int) <= sizeof(void *));
#if !defined(__KERNEL__) && !defined(__LIBCCALL_IS_LIBDCALL)
/* >> thrd_create(3)
 * Create and start a new thread (s.a. `pthread_create(3)')
 * @return: thrd_success: Success
 * @return: thrd_nomem:   Not enough memory
 * @return: thrd_error:   Error */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.sched.threads") ATTR_OUT(1) NONNULL((2)) int
NOTHROW_NCX(LIBDCALL libd_thrd_create)(thrd_t *thr,
                                       int (LIBDCALL *func)(void *arg),
                                       void *arg) {
	errno_t error;
	STATIC_ASSERT(sizeof(int) <= sizeof(void *));
	error = libd_pthread_create((pthread_t *)thr, NULL,
	                            (void *(LIBDCALL *)(void *))(void *)func,
	                            arg);
	if likely(!error)
		return thrd_success;
	if (error == ENOMEM)
		return thrd_nomem;
	return thrd_error;
}
#endif /* !__KERNEL__ && !__LIBCCALL_IS_LIBDCALL */
#ifndef __KERNEL__
#include <asm/crt/threads.h>
#include <libc/errno.h>
/* >> thrd_create(3)
 * Create and start a new thread (s.a. `pthread_create(3)')
 * @return: thrd_success: Success
 * @return: thrd_nomem:   Not enough memory
 * @return: thrd_error:   Error */
INTERN ATTR_SECTION(".text.crt.sched.threads") ATTR_OUT(1) NONNULL((2)) int
NOTHROW_NCX(LIBCCALL libc_thrd_create)(thrd_t *thr,
                                       int (LIBCCALL *func)(void *arg),
                                       void *arg) {
	errno_t error;
	STATIC_ASSERT(sizeof(int) <= sizeof(void *));
	error = libc_pthread_create((pthread_t *)thr, NULL,
	                       (void *(LIBCCALL *)(void *))(void *)func,
	                       arg);
	if likely(!error)
		return thrd_success;
#ifdef thrd_nomem
	if (error == ENOMEM)
		return thrd_nomem;
#endif /* thrd_nomem */
	return thrd_error;
}
/* >> thrd_exit(3)
 * Terminate the calling thread (s.a. `pthread_exit(3)') */
INTERN ATTR_SECTION(".text.crt.sched.threads") ATTR_NORETURN void
(LIBCCALL libc_thrd_exit)(int res) THROWS(...) {
	libc_pthread_exit((void *)(uintptr_t)(unsigned int)res);
}
#include <asm/crt/threads.h>
/* >> thrd_detach(3)
 * Detach the given thread (s.a. `pthread_detach(3)')
 * @return: thrd_success: Success
 * @return: thrd_error:   Error */
INTERN ATTR_SECTION(".text.crt.sched.threads") int
NOTHROW_NCX(LIBCCALL libc_thrd_detach)(thrd_t thr) {
	errno_t error;
	error = libc_pthread_detach((pthread_t)thr);
	if likely(!error)
		return thrd_success;
	return thrd_error;
}
#include <asm/crt/threads.h>
/* >> thrd_join(3)
 * Wait for the given thread to finish (s.a. `pthread_join(3)')
 * @return: thrd_success: Success
 * @return: thrd_error:   Error */
INTERN ATTR_SECTION(".text.crt.sched.threads") ATTR_OUT_OPT(2) int
NOTHROW_RPC(LIBCCALL libc_thrd_join)(thrd_t thr,
                                     int *res) {
	errno_t error;
#if __SIZEOF_POINTER__ != __SIZEOF_INT__
	void *resptr;
	error = libc_pthread_join((pthread_t)thr, res ? &resptr : NULL);
	if likely(!error) {
		if (res)
			*res = (int)(unsigned int)(uintptr_t)resptr;
		return thrd_success;
	}
#else /* __SIZEOF_POINTER__ != __SIZEOF_INT__ */
	error = libc_pthread_join((pthread_t)thr, (void **)res);
	if likely(!error)
		return thrd_success;
#endif /* __SIZEOF_POINTER__ == __SIZEOF_INT__ */
	return thrd_error;
}
#include <asm/crt/threads.h>
#include <asm/crt/pthreadvalues.h>
#include <bits/crt/pthreadtypes.h>
/* >> mtx_init(3)
 * Initialize a mutex object (s.a. `pthread_mutex_init(3)')
 * @return: thrd_success: Success
 * @return: thrd_error:   Error */
INTERN ATTR_SECTION(".text.crt.sched.threads") ATTR_OUT(1) int
NOTHROW_NCX(LIBCCALL libc_mtx_init)(mtx_t *__restrict mutex,
                                    __STDC_INT_AS_UINT_T type) {
	errno_t error;
	if (type == mtx_plain) {
		error = libc_pthread_mutex_init((pthread_mutex_t *)mutex, NULL);
	} else {
		pthread_mutexattr_t attr;
		error = libc_pthread_mutexattr_init(&attr);
		if (error == 0) {
			error = libc_pthread_mutexattr_settype(&attr,
			                                  type == mtx_recursive
			                                  ? __PTHREAD_MUTEX_RECURSIVE
			                                  : __PTHREAD_MUTEX_TIMED);
			if (error == 0)
				error = libc_pthread_mutex_init((pthread_mutex_t *)mutex, &attr);
			libc_pthread_mutexattr_destroy(&attr);
		}
	}
	if likely(!error)
		return thrd_success;
	return thrd_error;
}
#include <asm/crt/threads.h>
#include <bits/crt/pthreadtypes.h>
/* >> mtx_lock(3)
 * Acquire a lock to a given mutex (s.a. `pthread_mutex_lock(3)')
 * @return: thrd_success: Success
 * @return: thrd_error:   Error */
INTERN ATTR_SECTION(".text.crt.sched.threads") ATTR_INOUT(1) int
NOTHROW_RPC(LIBCCALL libc_mtx_lock)(mtx_t *__restrict mutex) {
	errno_t error;
	error = libc_pthread_mutex_lock((pthread_mutex_t *)mutex);
	if likely(!error)
		return thrd_success;
	return thrd_error;
}
#include <asm/crt/threads.h>
#include <bits/crt/pthreadtypes.h>
#include <asm/os/errno.h>
/* >> mtx_timedlock(3), mtx_timedlock64(3)
 * Acquire a lock to a given mutex (s.a. `pthread_mutex_timedlock(3)')
 * @return: thrd_success:  Success
 * @return: thrd_timedout: Timeout
 * @return: thrd_error:    Error */
INTERN ATTR_SECTION(".text.crt.sched.threads") ATTR_IN(2) ATTR_INOUT(1) int
NOTHROW_RPC(LIBCCALL libc_mtx_timedlock)(mtx_t *__restrict mutex,
                                         struct timespec const *__restrict time_point) {
	errno_t error;
	error = libc_pthread_mutex_timedlock((pthread_mutex_t *)mutex, time_point);
	if likely(!error)
		return thrd_success;

	if (error == ETIMEDOUT)
		return thrd_timedout;

	return thrd_error;
}
#include <bits/types.h>
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_mtx_timedlock64, libc_mtx_timedlock);
#else /* __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */
#include <asm/crt/threads.h>
#include <bits/crt/pthreadtypes.h>
#include <asm/os/errno.h>
/* >> mtx_timedlock(3), mtx_timedlock64(3)
 * Acquire a lock to a given mutex (s.a. `pthread_mutex_timedlock(3)')
 * @return: thrd_success:  Success
 * @return: thrd_timedout: Timeout
 * @return: thrd_error:    Error */
INTERN ATTR_SECTION(".text.crt.sched.threads") ATTR_IN(2) ATTR_INOUT(1) int
NOTHROW_RPC(LIBCCALL libc_mtx_timedlock64)(mtx_t *__restrict mutex,
                                           struct timespec64 const *__restrict time_point) {
	errno_t error;
	error = libc_pthread_mutex_timedlock64((pthread_mutex_t *)mutex, time_point);
	if likely(!error)
		return thrd_success;

	if (error == ETIMEDOUT)
		return thrd_timedout;

	return thrd_error;
}
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
#include <asm/crt/threads.h>
#include <bits/crt/pthreadtypes.h>
#include <libc/errno.h>
/* >> mtx_trylock(3)
 * Try to acquire a lock to a given mutex (s.a. `pthread_mutex_trylock(3)')
 * @return: thrd_success: Success
 * @return: thrd_busy:    Cannot lock without blocking right now
 * @return: thrd_error:   Error */
INTERN ATTR_SECTION(".text.crt.sched.threads") ATTR_INOUT(1) int
NOTHROW_NCX(LIBCCALL libc_mtx_trylock)(mtx_t *__restrict mutex) {
	errno_t error;
	error = libc_pthread_mutex_trylock((pthread_mutex_t *)mutex);
	if likely(!error)
		return thrd_success;
#ifdef thrd_busy
	if likely(error == EBUSY)
		return thrd_busy;
#endif /* thrd_busy */
	return thrd_error;
}
#include <asm/crt/threads.h>
#include <bits/crt/pthreadtypes.h>
/* >> mtx_unlock(3)
 * Release a lock from a given mutex (s.a. `pthread_mutex_unlock(3)')
 * @return: thrd_success: Success
 * @return: thrd_error:   Error */
INTERN ATTR_SECTION(".text.crt.sched.threads") ATTR_INOUT(1) int
NOTHROW_NCX(LIBCCALL libc_mtx_unlock)(mtx_t *__restrict mutex) {
	errno_t error;
	error = libc_pthread_mutex_unlock((pthread_mutex_t *)mutex);
	if likely(!error)
		return thrd_success;
	return thrd_error;
}
#include <asm/crt/threads.h>
#include <bits/crt/pthreadtypes.h>
/* >> cnd_init(3)
 * Initialize the given condition variable (s.a. `pthread_cond_init(3)')
 * @return: thrd_success: Success
 * @return: thrd_error:   Error */
INTERN ATTR_SECTION(".text.crt.sched.threads") ATTR_OUT(1) int
NOTHROW_NCX(LIBCCALL libc_cnd_init)(cnd_t *__restrict cond) {
	errno_t error;
	error = libc_pthread_cond_init((pthread_cond_t *)cond, NULL);
	if likely(!error)
		return thrd_success;
	return thrd_error;
}
#include <asm/crt/threads.h>
#include <bits/crt/pthreadtypes.h>
/* >> cnd_signal(3)
 * Wakeup  one thread currently  waiting on the given
 * condition variable (s.a. `pthread_cond_signal(3)')
 * @return: thrd_success: Success
 * @return: thrd_error:   Error */
INTERN ATTR_SECTION(".text.crt.sched.threads") ATTR_INOUT(1) int
NOTHROW_NCX(LIBCCALL libc_cnd_signal)(cnd_t *__restrict cond) {
	errno_t error;
	error = libc_pthread_cond_signal((pthread_cond_t *)cond);
	if likely(!error)
		return thrd_success;
	return thrd_error;
}
#include <asm/crt/threads.h>
#include <bits/crt/pthreadtypes.h>
/* >> cnd_broadcast(3)
 * Wakeup  all  threads currently  waiting on  the given
 * condition variable (s.a. `pthread_cond_broadcast(3)')
 * @return: thrd_success: Success
 * @return: thrd_error:   Error */
INTERN ATTR_SECTION(".text.crt.sched.threads") ATTR_INOUT(1) int
NOTHROW_NCX(LIBCCALL libc_cnd_broadcast)(cnd_t *__restrict cond) {
	errno_t error;
	error = libc_pthread_cond_broadcast((pthread_cond_t *)cond);
	if likely(!error)
		return thrd_success;
	return thrd_error;
}
#include <asm/crt/threads.h>
#include <bits/crt/pthreadtypes.h>
/* >> cnd_wait(3)
 * Wait on the given condition variable (s.a. `pthread_cond_wait(3)')
 * @return: thrd_success: Success
 * @return: thrd_error:   Error */
INTERN ATTR_SECTION(".text.crt.sched.threads") ATTR_INOUT(1) ATTR_INOUT(2) int
NOTHROW_RPC(LIBCCALL libc_cnd_wait)(cnd_t *__restrict cond,
                                    mtx_t *__restrict mutex) {
	errno_t error;
	error = libc_pthread_cond_wait((pthread_cond_t *)cond,
	                          (pthread_mutex_t *)mutex);
	if likely(!error)
		return thrd_success;
	return thrd_error;
}
#include <asm/crt/threads.h>
#include <bits/crt/pthreadtypes.h>
#include <asm/os/errno.h>
/* >> cnd_timedwait(3), cnd_timedwait64(3)
 * Wait on the given condition variable (s.a. `pthread_cond_timedwait(3)')
 * @return: thrd_success:  Success
 * @return: thrd_timedout: Timeout
 * @return: thrd_error:    Error */
INTERN ATTR_SECTION(".text.crt.sched.threads") ATTR_IN(3) ATTR_INOUT(1) ATTR_INOUT(2) int
NOTHROW_RPC(LIBCCALL libc_cnd_timedwait)(cnd_t *__restrict cond,
                                         mtx_t *__restrict mutex,
                                         struct timespec const *__restrict time_point) {
	errno_t error;
	error = libc_pthread_cond_timedwait((pthread_cond_t *)cond,
	                               (pthread_mutex_t *)mutex,
	                               time_point);
	if likely(!error)
		return thrd_success;

	if (error == ETIMEDOUT)
		return thrd_timedout;

	return thrd_error;
}
#include <bits/types.h>
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_cnd_timedwait64, libc_cnd_timedwait);
#else /* __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */
#include <asm/crt/threads.h>
#include <bits/crt/pthreadtypes.h>
#include <asm/os/errno.h>
/* >> cnd_timedwait(3), cnd_timedwait64(3)
 * Wait on the given condition variable (s.a. `pthread_cond_timedwait(3)')
 * @return: thrd_success:  Success
 * @return: thrd_timedout: Timeout
 * @return: thrd_error:    Error */
INTERN ATTR_SECTION(".text.crt.sched.threads") ATTR_IN(3) ATTR_INOUT(1) ATTR_INOUT(2) int
NOTHROW_RPC(LIBCCALL libc_cnd_timedwait64)(cnd_t *__restrict cond,
                                           mtx_t *__restrict mutex,
                                           struct timespec64 const *__restrict time_point) {
	errno_t error;
	error = libc_pthread_cond_timedwait64((pthread_cond_t *)cond,
	                                 (pthread_mutex_t *)mutex,
	                                 time_point);
	if likely(!error)
		return thrd_success;

	if (error == ETIMEDOUT)
		return thrd_timedout;

	return thrd_error;
}
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
#include <asm/crt/threads.h>
#include <bits/crt/pthreadtypes.h>
/* >> tss_create(3)
 * Create a new TLS key (s.a. `pthread_key_create(3)')
 * @return: thrd_success: Success
 * @return: thrd_error:   Error */
INTERN ATTR_SECTION(".text.crt.sched.threads") ATTR_OUT(1) int
NOTHROW_NCX(LIBCCALL libc_tss_create)(tss_t *tss_id,
                                      void (LIBKCALL *destructor)(void *arg)) {
	errno_t error;
	error = libc_pthread_key_create((pthread_key_t *)tss_id, destructor);
	if likely(!error)
		return thrd_success;
	return thrd_error;
}
#include <asm/crt/threads.h>
#include <bits/crt/pthreadtypes.h>
/* >> tss_set(3)
 * Set the calling thread's value for the given TLS key (s.a. `pthread_setspecific(3)')
 * @return: thrd_success: Success
 * @return: thrd_error:   Error */
INTERN ATTR_SECTION(".text.crt.sched.threads") ATTR_ACCESS_NONE(2) int
NOTHROW_NCX(LIBCCALL libc_tss_set)(tss_t tss_id,
                                   void *val) {
	errno_t error;
	error = libc_pthread_setspecific((pthread_key_t)tss_id, val);
	if likely(!error)
		return thrd_success;
	return thrd_error;
}
#include <asm/crt/confname.h>
#include <asm/crt/limits.h>
/* >> thr_min_stack(3) */
INTERN ATTR_SECTION(".text.crt.sched.threads") ATTR_CONST WUNUSED size_t
NOTHROW_NCX(LIBCCALL libc_thr_min_stack)(void) {






#ifdef __PTHREAD_STACK_MIN
	return __PTHREAD_STACK_MIN;
#else /* __PTHREAD_STACK_MIN */
	return 8192;
#endif /* !__PTHREAD_STACK_MIN */
}
#endif /* !__KERNEL__ */

DECL_END

#if !defined(__KERNEL__) && !defined(__LIBCCALL_IS_LIBDCALL)
DEFINE_PUBLIC_ALIAS(DOS$thrd_create, libd_thrd_create);
#endif /* !__KERNEL__ && !__LIBCCALL_IS_LIBDCALL */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(thrd_create, libc_thrd_create);
DEFINE_PUBLIC_ALIAS(thrd_exit, libc_thrd_exit);
DEFINE_PUBLIC_ALIAS(thrd_detach, libc_thrd_detach);
DEFINE_PUBLIC_ALIAS(thrd_join, libc_thrd_join);
DEFINE_PUBLIC_ALIAS(mtx_init, libc_mtx_init);
DEFINE_PUBLIC_ALIAS(mtx_lock, libc_mtx_lock);
DEFINE_PUBLIC_ALIAS(mtx_timedlock, libc_mtx_timedlock);
DEFINE_PUBLIC_ALIAS(mtx_timedlock64, libc_mtx_timedlock64);
DEFINE_PUBLIC_ALIAS(mtx_trylock, libc_mtx_trylock);
DEFINE_PUBLIC_ALIAS(mtx_unlock, libc_mtx_unlock);
DEFINE_PUBLIC_ALIAS(cnd_init, libc_cnd_init);
DEFINE_PUBLIC_ALIAS(cnd_signal, libc_cnd_signal);
DEFINE_PUBLIC_ALIAS(cnd_broadcast, libc_cnd_broadcast);
DEFINE_PUBLIC_ALIAS(cnd_wait, libc_cnd_wait);
DEFINE_PUBLIC_ALIAS(cnd_timedwait, libc_cnd_timedwait);
DEFINE_PUBLIC_ALIAS(cnd_timedwait64, libc_cnd_timedwait64);
DEFINE_PUBLIC_ALIAS(tss_create, libc_tss_create);
DEFINE_PUBLIC_ALIAS(tss_set, libc_tss_set);
DEFINE_PUBLIC_ALIAS(thr_min_stack, libc_thr_min_stack);
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_THREADS_C */
