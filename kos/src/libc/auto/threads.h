/* HASH CRC-32:0x8011ee21 */
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
#ifndef GUARD_LIBC_AUTO_THREADS_H
#define GUARD_LIBC_AUTO_THREADS_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <threads.h>

DECL_BEGIN

#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Create a new thread executing the function FUNC.  Arguments for FUNC
 * are passed through ARG. If successful, THR is set to new thread identifier */
INTDEF int NOTHROW_NCX(LIBDCALL libd_thrd_create)(thrd_t *thr, thrd_start_t func, void *arg);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Create a new thread executing the function FUNC.  Arguments for FUNC
 * are passed through ARG. If successful, THR is set to new thread identifier */
INTDEF int NOTHROW_NCX(LIBCCALL libc_thrd_create)(thrd_t *thr, thrd_start_t func, void *arg);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Block current thread execution for at least the (relative) time pointed by TIME_POINT.
 * The current thread may resume if receives a signal. In that case, if REMAINING
 * is not NULL, the remaining time is stored in the object pointed by it
 * @return:     0: The (relative) time specified by `time_point' has elapsed
 * @return:    -1: A signal was received while waiting, and `remaining' was filled in (if given)
 * @return: <= -2: Some other error occurred */
INTDEF NONNULL((1)) int NOTHROW_RPC(LIBDCALL libd_thrd_sleep)(struct timespec const *time_point, struct timespec *remaining);
/* Block current thread execution for at least the (relative) time pointed by TIME_POINT.
 * The current thread may resume if receives a signal. In that case, if REMAINING
 * is not NULL, the remaining time is stored in the object pointed by it
 * @return:     0: The (relative) time specified by `time_point' has elapsed
 * @return:    -1: A signal was received while waiting, and `remaining' was filled in (if given)
 * @return: <= -2: Some other error occurred */
INTDEF NONNULL((1)) int NOTHROW_RPC(LIBDCALL libd_thrd_sleep64)(struct timespec64 const *time_point, struct timespec64 *remaining);
/* Terminate current thread execution, cleaning up any thread local
 * storage and freeing resources. Returns the value specified in RES
 * s.a. `pthread_exit()' */
INTDEF ATTR_NORETURN void (LIBDCALL libd_thrd_exit)(int res) THROWS(...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Terminate current thread execution, cleaning up any thread local
 * storage and freeing resources. Returns the value specified in RES
 * s.a. `pthread_exit()' */
INTDEF ATTR_NORETURN void (LIBCCALL libc_thrd_exit)(int res) THROWS(...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Detach the thread identified by THR from the current
 * environment (it does not allow join or wait for it)
 * s.a. `pthread_detach()' */
INTDEF int NOTHROW_NCX(LIBDCALL libd_thrd_detach)(thrd_t thr);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Detach the thread identified by THR from the current
 * environment (it does not allow join or wait for it)
 * s.a. `pthread_detach()' */
INTDEF int NOTHROW_NCX(LIBCCALL libc_thrd_detach)(thrd_t thr);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Block current thread until execution of THR is complete.
 * In case that RES is not NULL, will store the return value of THR when exiting
 * s.a. `pthread_join()' */
INTDEF int NOTHROW_RPC(LIBDCALL libd_thrd_join)(thrd_t thr, int *res);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Block current thread until execution of THR is complete.
 * In case that RES is not NULL, will store the return value of THR when exiting
 * s.a. `pthread_join()' */
INTDEF int NOTHROW_RPC(LIBCCALL libc_thrd_join)(thrd_t thr, int *res);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Creates a new mutex object with type TYPE.
 * If successful the new object is pointed by MUTEX
 * s.a. `pthread_mutex_init()' */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBDCALL libd_mtx_init)(mtx_t *__restrict mutex, __STDC_INT_AS_UINT_T type);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Creates a new mutex object with type TYPE.
 * If successful the new object is pointed by MUTEX
 * s.a. `pthread_mutex_init()' */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_mtx_init)(mtx_t *__restrict mutex, __STDC_INT_AS_UINT_T type);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Block the current thread until the mutex pointed to by MUTEX is
 * unlocked.  In that case current thread will not be blocked
 * s.a. `pthread_mutex_lock()' */
INTDEF NONNULL((1)) int NOTHROW_RPC(LIBDCALL libd_mtx_lock)(mtx_t *__restrict mutex);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Block the current thread until the mutex pointed to by MUTEX is
 * unlocked.  In that case current thread will not be blocked
 * s.a. `pthread_mutex_lock()' */
INTDEF NONNULL((1)) int NOTHROW_RPC(LIBCCALL libc_mtx_lock)(mtx_t *__restrict mutex);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Block the current thread until the mutex pointed by MUTEX
 * is unlocked or time pointed by TIME_POINT is reached.
 * In case the mutex is unlock, the current thread will not be blocked
 * s.a. `pthread_mutex_timedlock()' */
INTDEF NONNULL((1, 2)) int NOTHROW_RPC(LIBDCALL libd_mtx_timedlock)(mtx_t *__restrict mutex, struct timespec const *__restrict time_point);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Block the current thread until the mutex pointed by MUTEX
 * is unlocked or time pointed by TIME_POINT is reached.
 * In case the mutex is unlock, the current thread will not be blocked
 * s.a. `pthread_mutex_timedlock()' */
INTDEF NONNULL((1, 2)) int NOTHROW_RPC(LIBCCALL libc_mtx_timedlock)(mtx_t *__restrict mutex, struct timespec const *__restrict time_point);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Block the current thread until the mutex pointed by MUTEX
 * is unlocked or time pointed by TIME_POINT is reached.
 * In case the mutex is unlock, the current thread will not be blocked
 * s.a. `pthread_mutex_timedlock()' */
INTDEF NONNULL((1, 2)) int NOTHROW_RPC(LIBDCALL libd_mtx_timedlock64)(mtx_t *__restrict mutex, struct timespec64 const *__restrict time_point);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Block the current thread until the mutex pointed by MUTEX
 * is unlocked or time pointed by TIME_POINT is reached.
 * In case the mutex is unlock, the current thread will not be blocked
 * s.a. `pthread_mutex_timedlock()' */
INTDEF NONNULL((1, 2)) int NOTHROW_RPC(LIBCCALL libc_mtx_timedlock64)(mtx_t *__restrict mutex, struct timespec64 const *__restrict time_point);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Try to lock the mutex pointed by MUTEX without blocking.
 * If the mutex is free the current threads takes control of
 * it, otherwise it returns immediately
 * s.a. `pthread_mutex_trylock()' */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBDCALL libd_mtx_trylock)(mtx_t *__restrict mutex);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Try to lock the mutex pointed by MUTEX without blocking.
 * If the mutex is free the current threads takes control of
 * it, otherwise it returns immediately
 * s.a. `pthread_mutex_trylock()' */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_mtx_trylock)(mtx_t *__restrict mutex);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Unlock the mutex pointed by MUTEX.
 * It may potentially awake other threads waiting on this mutex
 * s.a. `pthread_mutex_unlock()' */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBDCALL libd_mtx_unlock)(mtx_t *__restrict mutex);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Unlock the mutex pointed by MUTEX.
 * It may potentially awake other threads waiting on this mutex
 * s.a. `pthread_mutex_unlock()' */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_mtx_unlock)(mtx_t *__restrict mutex);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Initialize new condition variable pointed by COND
 * s.a. `pthread_cond_init()' */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBDCALL libd_cnd_init)(cnd_t *__restrict cond);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Initialize new condition variable pointed by COND
 * s.a. `pthread_cond_init()' */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_cnd_init)(cnd_t *__restrict cond);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Unblock one thread that currently waits on condition variable pointed by COND
 * s.a. `pthread_cond_signal()' */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBDCALL libd_cnd_signal)(cnd_t *__restrict cond);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Unblock one thread that currently waits on condition variable pointed by COND
 * s.a. `pthread_cond_signal()' */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_cnd_signal)(cnd_t *__restrict cond);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Unblock all threads currently waiting on condition variable pointed by COND
 * s.a. `pthread_cond_broadcast()' */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBDCALL libd_cnd_broadcast)(cnd_t *__restrict cond);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Unblock all threads currently waiting on condition variable pointed by COND
 * s.a. `pthread_cond_broadcast()' */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_cnd_broadcast)(cnd_t *__restrict cond);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Block current thread on the condition variable pointed by COND
 * s.a. `pthread_cond_wait()' */
INTDEF NONNULL((1, 2)) int NOTHROW_RPC(LIBDCALL libd_cnd_wait)(cnd_t *__restrict cond, mtx_t *__restrict mutex);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Block current thread on the condition variable pointed by COND
 * s.a. `pthread_cond_wait()' */
INTDEF NONNULL((1, 2)) int NOTHROW_RPC(LIBCCALL libc_cnd_wait)(cnd_t *__restrict cond, mtx_t *__restrict mutex);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Block current thread on the condition variable until condition variable
 * pointed by COND is signaled or time pointed by TIME_POINT is reached
 * s.a. `pthread_cond_timedwait()' */
INTDEF NONNULL((1, 2, 3)) int NOTHROW_RPC(LIBDCALL libd_cnd_timedwait)(cnd_t *__restrict cond, mtx_t *__restrict mutex, struct timespec const *__restrict time_point);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Block current thread on the condition variable until condition variable
 * pointed by COND is signaled or time pointed by TIME_POINT is reached
 * s.a. `pthread_cond_timedwait()' */
INTDEF NONNULL((1, 2, 3)) int NOTHROW_RPC(LIBCCALL libc_cnd_timedwait)(cnd_t *__restrict cond, mtx_t *__restrict mutex, struct timespec const *__restrict time_point);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Block current thread on the condition variable until condition variable
 * pointed by COND is signaled or time pointed by TIME_POINT is reached
 * s.a. `pthread_cond_timedwait()' */
INTDEF NONNULL((1, 2, 3)) int NOTHROW_RPC(LIBDCALL libd_cnd_timedwait64)(cnd_t *__restrict cond, mtx_t *__restrict mutex, struct timespec64 const *__restrict time_point);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Block current thread on the condition variable until condition variable
 * pointed by COND is signaled or time pointed by TIME_POINT is reached
 * s.a. `pthread_cond_timedwait()' */
INTDEF NONNULL((1, 2, 3)) int NOTHROW_RPC(LIBCCALL libc_cnd_timedwait64)(cnd_t *__restrict cond, mtx_t *__restrict mutex, struct timespec64 const *__restrict time_point);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Create new thread-specific storage key and stores it in the object pointed by TSS_ID.
 * If DESTRUCTOR is not NULL, the function will be called when the thread terminates
 * s.a. `pthread_key_create()' */
INTDEF int NOTHROW_NCX(LIBDCALL libd_tss_create)(tss_t *tss_id, tss_dtor_t destructor);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Create new thread-specific storage key and stores it in the object pointed by TSS_ID.
 * If DESTRUCTOR is not NULL, the function will be called when the thread terminates
 * s.a. `pthread_key_create()' */
INTDEF int NOTHROW_NCX(LIBCCALL libc_tss_create)(tss_t *tss_id, tss_dtor_t destructor);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Sets the value of the thread-specific storage
 * identified by TSS_ID for the current thread to VAL
 * s.a. `pthread_setspecific()' */
INTDEF int NOTHROW_NCX(LIBDCALL libd_tss_set)(tss_t tss_id, void *val);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Sets the value of the thread-specific storage
 * identified by TSS_ID for the current thread to VAL
 * s.a. `pthread_setspecific()' */
INTDEF int NOTHROW_NCX(LIBCCALL libc_tss_set)(tss_t tss_id, void *val);
INTDEF ATTR_CONST size_t NOTHROW_NCX(LIBCCALL libc_thr_min_stack)(void);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_THREADS_H */
