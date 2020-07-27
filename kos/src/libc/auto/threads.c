/* HASH CRC-32:0xd84e2bc6 */
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
#ifndef __KERNEL__
#include <asm/crt/threads.h>
#include <parts/errno.h>
/* Create a new thread executing the function FUNC.  Arguments for FUNC
 * are passed through ARG. If successful, THR is set to new thread identifier */
INTERN ATTR_SECTION(".text.crt.sched.threads") int
NOTHROW_NCX(LIBCCALL libc_thrd_create)(thrd_t *thr,
                                       thrd_start_t func,
                                       void *arg) {
	errno_t error;
	STATIC_ASSERT(sizeof(int) <= sizeof(void *));
	error = libc_pthread_create((pthread_t *)thr, NULL,
	                       (__pthread_start_routine_t)(void *)func,
	                       arg);
	if likely(!error)
		return thrd_success;
#if defined(thrd_nomem) && defined(ENOMEM)
	if (error == ENOMEM)
		return thrd_nomem;
#endif /* thrd_nomem && ENOMEM */
	return thrd_error;
}
/* Terminate current thread execution, cleaning up any thread local
 * storage and freeing resources. Returns the value specified in RES
 * s.a. `pthread_exit()' */
INTERN ATTR_SECTION(".text.crt.sched.threads") ATTR_NORETURN void
(LIBCCALL libc_thrd_exit)(int res) THROWS(...) {
	libc_pthread_exit((void *)(uintptr_t)(unsigned int)res);
}
#include <asm/crt/threads.h>
/* Detach the thread identified by THR from the current
 * environment (it does not allow join or wait for it)
 * s.a. `pthread_detach()' */
INTERN ATTR_SECTION(".text.crt.sched.threads") int
NOTHROW_NCX(LIBCCALL libc_thrd_detach)(thrd_t thr) {
	errno_t error;
	error = libc_pthread_detach((pthread_t)thr);
	if likely(!error)
		return thrd_success;
	return thrd_error;
}
#include <asm/crt/threads.h>
/* Block current thread until execution of THR is complete.
 * In case that RES is not NULL, will store the return value of THR when exiting
 * s.a. `pthread_join()' */
INTERN ATTR_SECTION(".text.crt.sched.threads") int
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
/* Creates a new mutex object with type TYPE.
 * If successful the new object is pointed by MUTEX
 * s.a. `pthread_mutex_init()' */
INTERN ATTR_SECTION(".text.crt.sched.threads") NONNULL((1)) int
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
/* Block the current thread until the mutex pointed to by MUTEX is
 * unlocked.  In that case current thread will not be blocked
 * s.a. `pthread_mutex_lock()' */
INTERN ATTR_SECTION(".text.crt.sched.threads") NONNULL((1)) int
NOTHROW_RPC(LIBCCALL libc_mtx_lock)(mtx_t *__restrict mutex) {
	errno_t error;
	error = libc_pthread_mutex_lock((pthread_mutex_t *)mutex);
	if likely(!error)
		return thrd_success;
	return thrd_error;
}
#include <asm/crt/threads.h>
#include <bits/crt/pthreadtypes.h>
/* Block the current thread until the mutex pointed by MUTEX
 * is unlocked or time pointed by TIME_POINT is reached.
 * In case the mutex is unlock, the current thread will not be blocked
 * s.a. `pthread_mutex_timedlock()' */
INTERN ATTR_SECTION(".text.crt.sched.threads") NONNULL((1, 2)) int
NOTHROW_RPC(LIBCCALL libc_mtx_timedlock)(mtx_t *__restrict mutex,
                                         struct timespec const *__restrict time_point) {
	errno_t error;
	error = libc_pthread_mutex_timedlock((pthread_mutex_t *)mutex, time_point);
	if likely(!error)
		return thrd_success;
	return thrd_error;
}
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_mtx_timedlock64, libc_mtx_timedlock);
#else /* __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */
#include <asm/crt/threads.h>
#include <bits/crt/pthreadtypes.h>
/* Block the current thread until the mutex pointed by MUTEX
 * is unlocked or time pointed by TIME_POINT is reached.
 * In case the mutex is unlock, the current thread will not be blocked
 * s.a. `pthread_mutex_timedlock()' */
INTERN ATTR_SECTION(".text.crt.sched.threads") NONNULL((1, 2)) int
NOTHROW_RPC(LIBCCALL libc_mtx_timedlock64)(mtx_t *__restrict mutex,
                                           struct timespec64 const *__restrict time_point) {
	errno_t error;
	error = libc_pthread_mutex_timedlock64((pthread_mutex_t *)mutex, time_point);
	if likely(!error)
		return thrd_success;
	return thrd_error;
}
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
#include <asm/crt/threads.h>
#include <bits/crt/pthreadtypes.h>
#include <parts/errno.h>
/* Try to lock the mutex pointed by MUTEX without blocking.
 * If the mutex is free the current threads takes control of
 * it, otherwise it returns immediately
 * s.a. `pthread_mutex_trylock()' */
INTERN ATTR_SECTION(".text.crt.sched.threads") NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_mtx_trylock)(mtx_t *__restrict mutex) {
	errno_t error;
	error = libc_pthread_mutex_trylock((pthread_mutex_t *)mutex);
	if likely(!error)
		return thrd_success;
#if defined(thrd_busy) && defined(EBUSY)
	if likely(error == EBUSY)
		return thrd_busy;
#endif /* thrd_busy && EBUSY */
	return thrd_error;
}
#include <asm/crt/threads.h>
#include <bits/crt/pthreadtypes.h>
/* Unlock the mutex pointed by MUTEX.
 * It may potentially awake other threads waiting on this mutex
 * s.a. `pthread_mutex_unlock()' */
INTERN ATTR_SECTION(".text.crt.sched.threads") NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_mtx_unlock)(mtx_t *__restrict mutex) {
	errno_t error;
	error = libc_pthread_mutex_unlock((pthread_mutex_t *)mutex);
	if likely(!error)
		return thrd_success;
	return thrd_error;
}
#include <asm/crt/threads.h>
#include <bits/crt/pthreadtypes.h>
/* Initialize new condition variable pointed by COND
 * s.a. `pthread_cond_init()' */
INTERN ATTR_SECTION(".text.crt.sched.threads") NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_cnd_init)(cnd_t *__restrict cond) {
	errno_t error;
	error = libc_pthread_cond_init((pthread_cond_t *)cond, NULL);
	if likely(!error)
		return thrd_success;
	return thrd_error;
}
#include <asm/crt/threads.h>
#include <bits/crt/pthreadtypes.h>
/* Unblock one thread that currently waits on condition variable pointed by COND
 * s.a. `pthread_cond_signal()' */
INTERN ATTR_SECTION(".text.crt.sched.threads") NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_cnd_signal)(cnd_t *__restrict cond) {
	errno_t error;
	error = libc_pthread_cond_signal((pthread_cond_t *)cond);
	if likely(!error)
		return thrd_success;
	return thrd_error;
}
#include <asm/crt/threads.h>
#include <bits/crt/pthreadtypes.h>
/* Unblock all threads currently waiting on condition variable pointed by COND
 * s.a. `pthread_cond_broadcast()' */
INTERN ATTR_SECTION(".text.crt.sched.threads") NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_cnd_broadcast)(cnd_t *__restrict cond) {
	errno_t error;
	error = libc_pthread_cond_broadcast((pthread_cond_t *)cond);
	if likely(!error)
		return thrd_success;
	return thrd_error;
}
#include <asm/crt/threads.h>
#include <bits/crt/pthreadtypes.h>
/* Block current thread on the condition variable pointed by COND
 * s.a. `pthread_cond_wait()' */
INTERN ATTR_SECTION(".text.crt.sched.threads") NONNULL((1, 2)) int
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
/* Block current thread on the condition variable until condition variable
 * pointed by COND is signaled or time pointed by TIME_POINT is reached
 * s.a. `pthread_cond_timedwait()' */
INTERN ATTR_SECTION(".text.crt.sched.threads") NONNULL((1, 2, 3)) int
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
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_cnd_timedwait64, libc_cnd_timedwait);
#else /* __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */
#include <asm/crt/threads.h>
#include <bits/crt/pthreadtypes.h>
/* Block current thread on the condition variable until condition variable
 * pointed by COND is signaled or time pointed by TIME_POINT is reached
 * s.a. `pthread_cond_timedwait()' */
INTERN ATTR_SECTION(".text.crt.sched.threads") NONNULL((1, 2, 3)) int
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
/* Create new thread-specific storage key and stores it in the object pointed by TSS_ID.
 * If DESTRUCTOR is not NULL, the function will be called when the thread terminates
 * s.a. `pthread_key_create()' */
INTERN ATTR_SECTION(".text.crt.sched.threads") int
NOTHROW_NCX(LIBCCALL libc_tss_create)(tss_t *tss_id,
                                      tss_dtor_t destructor) {
	errno_t error;
	error = libc_pthread_key_create((pthread_key_t *)tss_id, destructor);
	if likely(!error)
		return thrd_success;
	return thrd_error;
}
#include <asm/crt/threads.h>
#include <bits/crt/pthreadtypes.h>
/* Sets the value of the thread-specific storage
 * identified by TSS_ID for the current thread to VAL
 * s.a. `pthread_setspecific()' */
INTERN ATTR_SECTION(".text.crt.sched.threads") int
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
INTERN ATTR_SECTION(".text.crt.sched.threads") ATTR_CONST size_t
NOTHROW_NCX(LIBCCALL libc_thr_min_stack)(void) {






#ifdef __PTHREAD_STACK_MIN
	return __PTHREAD_STACK_MIN;
#else /* __PTHREAD_STACK_MIN */
	return 8192;
#endif /* !__PTHREAD_STACK_MIN */
}
#endif /* !__KERNEL__ */

DECL_END

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
