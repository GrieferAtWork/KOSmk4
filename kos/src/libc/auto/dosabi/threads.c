/* HASH CRC-32:0xb999d61e */
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
#ifndef GUARD_LIBC_AUTO_DOSABI_THREADS_C
#define GUARD_LIBC_AUTO_DOSABI_THREADS_C 1

#include "../../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../../user/threads.h"

DECL_BEGIN

/* Create a new thread executing the function FUNC.  Arguments for FUNC
 * are passed through ARG. If successful, THR is set to new thread identifier */
INTERN ATTR_SECTION(".text.crt.dos.sched.threads") int
NOTHROW_NCX(LIBDCALL libd_thrd_create)(thrd_t *thr,
                                       thrd_start_t func,
                                       void *arg) {
	return libc_thrd_create(thr, func, arg);
}
/* Block current thread execution for at least the (relative) time pointed by TIME_POINT.
 * The current thread may resume if receives a signal. In that case, if REMAINING
 * is not NULL, the remaining time is stored in the object pointed by it
 * @return:     0: The (relative) time specified by `time_point' has elapsed
 * @return:    -1: A signal was received while waiting, and `remaining' was filled in (if given)
 * @return: <= -2: Some other error occurred */
INTERN ATTR_SECTION(".text.crt.dos.sched.threads") NONNULL((1)) int
NOTHROW_RPC(LIBDCALL libd_thrd_sleep)(struct timespec const *time_point,
                                      struct timespec *remaining) {
	return libc_thrd_sleep(time_point, remaining);
}
/* Block current thread execution for at least the (relative) time pointed by TIME_POINT.
 * The current thread may resume if receives a signal. In that case, if REMAINING
 * is not NULL, the remaining time is stored in the object pointed by it
 * @return:     0: The (relative) time specified by `time_point' has elapsed
 * @return:    -1: A signal was received while waiting, and `remaining' was filled in (if given)
 * @return: <= -2: Some other error occurred */
INTERN ATTR_SECTION(".text.crt.dos.sched.threads") NONNULL((1)) int
NOTHROW_RPC(LIBDCALL libd_thrd_sleep64)(struct timespec64 const *time_point,
                                        struct timespec64 *remaining) {
	return libc_thrd_sleep64(time_point, remaining);
}
/* Terminate current thread execution, cleaning up any thread local
 * storage and freeing resources. Returns the value specified in RES
 * s.a. `pthread_exit()' */
INTERN ATTR_SECTION(".text.crt.dos.sched.threads") ATTR_NORETURN void
(LIBDCALL libd_thrd_exit)(int res) THROWS(...) {
	libc_thrd_exit(res);
}
/* Detach the thread identified by THR from the current
 * environment (it does not allow join or wait for it)
 * s.a. `pthread_detach()' */
INTERN ATTR_SECTION(".text.crt.dos.sched.threads") int
NOTHROW_NCX(LIBDCALL libd_thrd_detach)(thrd_t thr) {
	return libc_thrd_detach(thr);
}
/* Block current thread until execution of THR is complete.
 * In case that RES is not NULL, will store the return value of THR when exiting
 * s.a. `pthread_join()' */
INTERN ATTR_SECTION(".text.crt.dos.sched.threads") int
NOTHROW_RPC(LIBDCALL libd_thrd_join)(thrd_t thr,
                                     int *res) {
	return libc_thrd_join(thr, res);
}
/* Creates a new mutex object with type TYPE.
 * If successful the new object is pointed by MUTEX
 * s.a. `pthread_mutex_init()' */
INTERN ATTR_SECTION(".text.crt.dos.sched.threads") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_mtx_init)(mtx_t *__restrict mutex,
                                    __STDC_INT_AS_UINT_T type) {
	return libc_mtx_init(mutex, type);
}
/* Block the current thread until the mutex pointed to by MUTEX is
 * unlocked.  In that case current thread will not be blocked
 * s.a. `pthread_mutex_lock()' */
INTERN ATTR_SECTION(".text.crt.dos.sched.threads") NONNULL((1)) int
NOTHROW_RPC(LIBDCALL libd_mtx_lock)(mtx_t *__restrict mutex) {
	return libc_mtx_lock(mutex);
}
/* Block the current thread until the mutex pointed by MUTEX
 * is unlocked or time pointed by TIME_POINT is reached.
 * In case the mutex is unlock, the current thread will not be blocked
 * s.a. `pthread_mutex_timedlock()' */
INTERN ATTR_SECTION(".text.crt.dos.sched.threads") NONNULL((1, 2)) int
NOTHROW_RPC(LIBDCALL libd_mtx_timedlock)(mtx_t *__restrict mutex,
                                         struct timespec const *__restrict time_point) {
	return libc_mtx_timedlock(mutex, time_point);
}
/* Block the current thread until the mutex pointed by MUTEX
 * is unlocked or time pointed by TIME_POINT is reached.
 * In case the mutex is unlock, the current thread will not be blocked
 * s.a. `pthread_mutex_timedlock()' */
INTERN ATTR_SECTION(".text.crt.dos.sched.threads") NONNULL((1, 2)) int
NOTHROW_RPC(LIBDCALL libd_mtx_timedlock64)(mtx_t *__restrict mutex,
                                           struct timespec64 const *__restrict time_point) {
	return libc_mtx_timedlock64(mutex, time_point);
}
/* Try to lock the mutex pointed by MUTEX without blocking.
 * If the mutex is free the current threads takes control of
 * it, otherwise it returns immediately
 * s.a. `pthread_mutex_trylock()' */
INTERN ATTR_SECTION(".text.crt.dos.sched.threads") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_mtx_trylock)(mtx_t *__restrict mutex) {
	return libc_mtx_trylock(mutex);
}
/* Unlock the mutex pointed by MUTEX.
 * It may potentially awake other threads waiting on this mutex
 * s.a. `pthread_mutex_unlock()' */
INTERN ATTR_SECTION(".text.crt.dos.sched.threads") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_mtx_unlock)(mtx_t *__restrict mutex) {
	return libc_mtx_unlock(mutex);
}
/* Initialize new condition variable pointed by COND
 * s.a. `pthread_cond_init()' */
INTERN ATTR_SECTION(".text.crt.dos.sched.threads") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_cnd_init)(cnd_t *__restrict cond) {
	return libc_cnd_init(cond);
}
/* Unblock one thread that currently waits on condition variable pointed by COND
 * s.a. `pthread_cond_signal()' */
INTERN ATTR_SECTION(".text.crt.dos.sched.threads") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_cnd_signal)(cnd_t *__restrict cond) {
	return libc_cnd_signal(cond);
}
/* Unblock all threads currently waiting on condition variable pointed by COND
 * s.a. `pthread_cond_broadcast()' */
INTERN ATTR_SECTION(".text.crt.dos.sched.threads") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_cnd_broadcast)(cnd_t *__restrict cond) {
	return libc_cnd_broadcast(cond);
}
/* Block current thread on the condition variable pointed by COND
 * s.a. `pthread_cond_wait()' */
INTERN ATTR_SECTION(".text.crt.dos.sched.threads") NONNULL((1, 2)) int
NOTHROW_RPC(LIBDCALL libd_cnd_wait)(cnd_t *__restrict cond,
                                    mtx_t *__restrict mutex) {
	return libc_cnd_wait(cond, mutex);
}
/* Block current thread on the condition variable until condition variable
 * pointed by COND is signaled or time pointed by TIME_POINT is reached
 * s.a. `pthread_cond_timedwait()' */
INTERN ATTR_SECTION(".text.crt.dos.sched.threads") NONNULL((1, 2, 3)) int
NOTHROW_RPC(LIBDCALL libd_cnd_timedwait)(cnd_t *__restrict cond,
                                         mtx_t *__restrict mutex,
                                         struct timespec const *__restrict time_point) {
	return libc_cnd_timedwait(cond, mutex, time_point);
}
/* Block current thread on the condition variable until condition variable
 * pointed by COND is signaled or time pointed by TIME_POINT is reached
 * s.a. `pthread_cond_timedwait()' */
INTERN ATTR_SECTION(".text.crt.dos.sched.threads") NONNULL((1, 2, 3)) int
NOTHROW_RPC(LIBDCALL libd_cnd_timedwait64)(cnd_t *__restrict cond,
                                           mtx_t *__restrict mutex,
                                           struct timespec64 const *__restrict time_point) {
	return libc_cnd_timedwait64(cond, mutex, time_point);
}
/* Create new thread-specific storage key and stores it in the object pointed by TSS_ID.
 * If DESTRUCTOR is not NULL, the function will be called when the thread terminates
 * s.a. `pthread_key_create()' */
INTERN ATTR_SECTION(".text.crt.dos.sched.threads") int
NOTHROW_NCX(LIBDCALL libd_tss_create)(tss_t *tss_id,
                                      tss_dtor_t destructor) {
	return libc_tss_create(tss_id, destructor);
}
/* Sets the value of the thread-specific storage
 * identified by TSS_ID for the current thread to VAL
 * s.a. `pthread_setspecific()' */
INTERN ATTR_SECTION(".text.crt.dos.sched.threads") int
NOTHROW_NCX(LIBDCALL libd_tss_set)(tss_t tss_id,
                                   void *val) {
	return libc_tss_set(tss_id, val);
}

DECL_END

DEFINE_PUBLIC_ALIAS(DOS$thrd_create, libd_thrd_create);
DEFINE_PUBLIC_ALIAS(DOS$thrd_sleep, libd_thrd_sleep);
DEFINE_PUBLIC_ALIAS(DOS$thrd_sleep64, libd_thrd_sleep64);
DEFINE_PUBLIC_ALIAS(DOS$thrd_exit, libd_thrd_exit);
DEFINE_PUBLIC_ALIAS(DOS$thrd_detach, libd_thrd_detach);
DEFINE_PUBLIC_ALIAS(DOS$thrd_join, libd_thrd_join);
DEFINE_PUBLIC_ALIAS(DOS$mtx_init, libd_mtx_init);
DEFINE_PUBLIC_ALIAS(DOS$mtx_lock, libd_mtx_lock);
DEFINE_PUBLIC_ALIAS(DOS$mtx_timedlock, libd_mtx_timedlock);
DEFINE_PUBLIC_ALIAS(DOS$mtx_timedlock64, libd_mtx_timedlock64);
DEFINE_PUBLIC_ALIAS(DOS$mtx_trylock, libd_mtx_trylock);
DEFINE_PUBLIC_ALIAS(DOS$mtx_unlock, libd_mtx_unlock);
DEFINE_PUBLIC_ALIAS(DOS$cnd_init, libd_cnd_init);
DEFINE_PUBLIC_ALIAS(DOS$cnd_signal, libd_cnd_signal);
DEFINE_PUBLIC_ALIAS(DOS$cnd_broadcast, libd_cnd_broadcast);
DEFINE_PUBLIC_ALIAS(DOS$cnd_wait, libd_cnd_wait);
DEFINE_PUBLIC_ALIAS(DOS$cnd_timedwait, libd_cnd_timedwait);
DEFINE_PUBLIC_ALIAS(DOS$cnd_timedwait64, libd_cnd_timedwait64);
DEFINE_PUBLIC_ALIAS(DOS$tss_create, libd_tss_create);
DEFINE_PUBLIC_ALIAS(DOS$tss_set, libd_tss_set);

#endif /* !GUARD_LIBC_AUTO_DOSABI_THREADS_C */
