/* HASH CRC-32:0x45bbc323 */
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
#ifndef GUARD_LIBC_AUTO_THREADS_H
#define GUARD_LIBC_AUTO_THREADS_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <threads.h>

DECL_BEGIN

#if !defined(__KERNEL__) && !defined(__LIBCCALL_IS_LIBDCALL)
/* >> thrd_create(3)
 * Create and start a new thread (s.a. `pthread_create(3)')
 * @return: thrd_success: Success
 * @return: thrd_nomem:   Not enough memory
 * @return: thrd_error:   Error */
INTDEF ATTR_OUT(1) NONNULL((2)) int NOTHROW_NCX(LIBDCALL libd_thrd_create)(thrd_t *thr, int (LIBDCALL *func)(void *arg), void *arg);
#endif /* !__KERNEL__ && !__LIBCCALL_IS_LIBDCALL */
#ifndef __KERNEL__
/* >> thrd_create(3)
 * Create and start a new thread (s.a. `pthread_create(3)')
 * @return: thrd_success: Success
 * @return: thrd_nomem:   Not enough memory
 * @return: thrd_error:   Error */
INTDEF ATTR_OUT(1) NONNULL((2)) int NOTHROW_NCX(LIBCCALL libc_thrd_create)(thrd_t *thr, int (LIBCCALL *func)(void *arg), void *arg);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> thrd_sleep(3), thrd_sleep64(3)
 * Sleep until a signal is received, or `time_point' has elapsed (s.a. `nanosleep(2)')
 * @return:     0: The (relative) time specified by `time_point' has elapsed
 * @return:    -1: A signal was received while waiting, and `remaining' was filled in (if given)
 * @return: <= -2: Some other error occurred */
INTDEF ATTR_IN(1) ATTR_OUT_OPT(2) int NOTHROW_RPC(LIBDCALL libd_thrd_sleep)(struct timespec const *time_point, struct timespec *remaining);
/* >> thrd_sleep(3), thrd_sleep64(3)
 * Sleep until a signal is received, or `time_point' has elapsed (s.a. `nanosleep(2)')
 * @return:     0: The (relative) time specified by `time_point' has elapsed
 * @return:    -1: A signal was received while waiting, and `remaining' was filled in (if given)
 * @return: <= -2: Some other error occurred */
INTDEF ATTR_IN(1) ATTR_OUT_OPT(2) int NOTHROW_RPC(LIBDCALL libd_thrd_sleep64)(struct timespec64 const *time_point, struct timespec64 *remaining);
/* >> thrd_exit(3)
 * Terminate the calling thread (s.a. `pthread_exit(3)') */
INTDEF ATTR_NORETURN void (LIBDCALL libd_thrd_exit)(int res);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> thrd_exit(3)
 * Terminate the calling thread (s.a. `pthread_exit(3)') */
INTDEF ATTR_NORETURN void (LIBCCALL libc_thrd_exit)(int res);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> thrd_detach(3)
 * Detach the given thread (s.a. `pthread_detach(3)')
 * @return: thrd_success: Success
 * @return: thrd_error:   Error */
INTDEF int NOTHROW_NCX(LIBDCALL libd_thrd_detach)(thrd_t thr);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> thrd_detach(3)
 * Detach the given thread (s.a. `pthread_detach(3)')
 * @return: thrd_success: Success
 * @return: thrd_error:   Error */
INTDEF int NOTHROW_NCX(LIBCCALL libc_thrd_detach)(thrd_t thr);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> thrd_join(3)
 * Wait for the given thread to finish (s.a. `pthread_join(3)')
 * @return: thrd_success: Success
 * @return: thrd_error:   Error */
INTDEF ATTR_OUT_OPT(2) int NOTHROW_RPC(LIBDCALL libd_thrd_join)(thrd_t thr, int *res);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> thrd_join(3)
 * Wait for the given thread to finish (s.a. `pthread_join(3)')
 * @return: thrd_success: Success
 * @return: thrd_error:   Error */
INTDEF ATTR_OUT_OPT(2) int NOTHROW_RPC(LIBCCALL libc_thrd_join)(thrd_t thr, int *res);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> mtx_init(3)
 * Initialize a mutex object (s.a. `pthread_mutex_init(3)')
 * @return: thrd_success: Success
 * @return: thrd_error:   Error */
INTDEF ATTR_OUT(1) int NOTHROW_NCX(LIBDCALL libd_mtx_init)(mtx_t *__restrict mutex, __STDC_INT_AS_UINT_T type);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> mtx_init(3)
 * Initialize a mutex object (s.a. `pthread_mutex_init(3)')
 * @return: thrd_success: Success
 * @return: thrd_error:   Error */
INTDEF ATTR_OUT(1) int NOTHROW_NCX(LIBCCALL libc_mtx_init)(mtx_t *__restrict mutex, __STDC_INT_AS_UINT_T type);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> mtx_lock(3)
 * Acquire a lock to a given mutex (s.a. `pthread_mutex_lock(3)')
 * @return: thrd_success: Success
 * @return: thrd_error:   Error */
INTDEF ATTR_INOUT(1) int NOTHROW_RPC(LIBDCALL libd_mtx_lock)(mtx_t *__restrict mutex);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> mtx_lock(3)
 * Acquire a lock to a given mutex (s.a. `pthread_mutex_lock(3)')
 * @return: thrd_success: Success
 * @return: thrd_error:   Error */
INTDEF ATTR_INOUT(1) int NOTHROW_RPC(LIBCCALL libc_mtx_lock)(mtx_t *__restrict mutex);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> mtx_timedlock(3), mtx_timedlock64(3)
 * Acquire a lock to a given mutex (s.a. `pthread_mutex_timedlock(3)')
 * @return: thrd_success:  Success
 * @return: thrd_timedout: Timeout
 * @return: thrd_error:    Error */
INTDEF ATTR_IN(2) ATTR_INOUT(1) int NOTHROW_RPC(LIBDCALL libd_mtx_timedlock)(mtx_t *__restrict mutex, struct timespec const *__restrict time_point);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> mtx_timedlock(3), mtx_timedlock64(3)
 * Acquire a lock to a given mutex (s.a. `pthread_mutex_timedlock(3)')
 * @return: thrd_success:  Success
 * @return: thrd_timedout: Timeout
 * @return: thrd_error:    Error */
INTDEF ATTR_IN(2) ATTR_INOUT(1) int NOTHROW_RPC(LIBCCALL libc_mtx_timedlock)(mtx_t *__restrict mutex, struct timespec const *__restrict time_point);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> mtx_timedlock(3), mtx_timedlock64(3)
 * Acquire a lock to a given mutex (s.a. `pthread_mutex_timedlock(3)')
 * @return: thrd_success:  Success
 * @return: thrd_timedout: Timeout
 * @return: thrd_error:    Error */
INTDEF ATTR_IN(2) ATTR_INOUT(1) int NOTHROW_RPC(LIBDCALL libd_mtx_timedlock64)(mtx_t *__restrict mutex, struct timespec64 const *__restrict time_point);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> mtx_timedlock(3), mtx_timedlock64(3)
 * Acquire a lock to a given mutex (s.a. `pthread_mutex_timedlock(3)')
 * @return: thrd_success:  Success
 * @return: thrd_timedout: Timeout
 * @return: thrd_error:    Error */
INTDEF ATTR_IN(2) ATTR_INOUT(1) int NOTHROW_RPC(LIBCCALL libc_mtx_timedlock64)(mtx_t *__restrict mutex, struct timespec64 const *__restrict time_point);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> mtx_trylock(3)
 * Try to acquire a lock to a given mutex (s.a. `pthread_mutex_trylock(3)')
 * @return: thrd_success: Success
 * @return: thrd_busy:    Cannot lock without blocking right now
 * @return: thrd_error:   Error */
INTDEF ATTR_INOUT(1) int NOTHROW_NCX(LIBDCALL libd_mtx_trylock)(mtx_t *__restrict mutex);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> mtx_trylock(3)
 * Try to acquire a lock to a given mutex (s.a. `pthread_mutex_trylock(3)')
 * @return: thrd_success: Success
 * @return: thrd_busy:    Cannot lock without blocking right now
 * @return: thrd_error:   Error */
INTDEF ATTR_INOUT(1) int NOTHROW_NCX(LIBCCALL libc_mtx_trylock)(mtx_t *__restrict mutex);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> mtx_unlock(3)
 * Release a lock from a given mutex (s.a. `pthread_mutex_unlock(3)')
 * @return: thrd_success: Success
 * @return: thrd_error:   Error */
INTDEF ATTR_INOUT(1) int NOTHROW_NCX(LIBDCALL libd_mtx_unlock)(mtx_t *__restrict mutex);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> mtx_unlock(3)
 * Release a lock from a given mutex (s.a. `pthread_mutex_unlock(3)')
 * @return: thrd_success: Success
 * @return: thrd_error:   Error */
INTDEF ATTR_INOUT(1) int NOTHROW_NCX(LIBCCALL libc_mtx_unlock)(mtx_t *__restrict mutex);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> cnd_init(3)
 * Initialize the given condition variable (s.a. `pthread_cond_init(3)')
 * @return: thrd_success: Success
 * @return: thrd_error:   Error */
INTDEF ATTR_OUT(1) int NOTHROW_NCX(LIBDCALL libd_cnd_init)(cnd_t *__restrict cond);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> cnd_init(3)
 * Initialize the given condition variable (s.a. `pthread_cond_init(3)')
 * @return: thrd_success: Success
 * @return: thrd_error:   Error */
INTDEF ATTR_OUT(1) int NOTHROW_NCX(LIBCCALL libc_cnd_init)(cnd_t *__restrict cond);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> cnd_signal(3)
 * Wakeup  one thread currently  waiting on the given
 * condition variable (s.a. `pthread_cond_signal(3)')
 * @return: thrd_success: Success
 * @return: thrd_error:   Error */
INTDEF ATTR_INOUT(1) int NOTHROW_NCX(LIBDCALL libd_cnd_signal)(cnd_t *__restrict cond);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> cnd_signal(3)
 * Wakeup  one thread currently  waiting on the given
 * condition variable (s.a. `pthread_cond_signal(3)')
 * @return: thrd_success: Success
 * @return: thrd_error:   Error */
INTDEF ATTR_INOUT(1) int NOTHROW_NCX(LIBCCALL libc_cnd_signal)(cnd_t *__restrict cond);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> cnd_broadcast(3)
 * Wakeup  all  threads currently  waiting on  the given
 * condition variable (s.a. `pthread_cond_broadcast(3)')
 * @return: thrd_success: Success
 * @return: thrd_error:   Error */
INTDEF ATTR_INOUT(1) int NOTHROW_NCX(LIBDCALL libd_cnd_broadcast)(cnd_t *__restrict cond);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> cnd_broadcast(3)
 * Wakeup  all  threads currently  waiting on  the given
 * condition variable (s.a. `pthread_cond_broadcast(3)')
 * @return: thrd_success: Success
 * @return: thrd_error:   Error */
INTDEF ATTR_INOUT(1) int NOTHROW_NCX(LIBCCALL libc_cnd_broadcast)(cnd_t *__restrict cond);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> cnd_wait(3)
 * Wait on the given condition variable (s.a. `pthread_cond_wait(3)')
 * @return: thrd_success: Success
 * @return: thrd_error:   Error */
INTDEF ATTR_INOUT(1) ATTR_INOUT(2) int NOTHROW_RPC(LIBDCALL libd_cnd_wait)(cnd_t *__restrict cond, mtx_t *__restrict mutex);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> cnd_wait(3)
 * Wait on the given condition variable (s.a. `pthread_cond_wait(3)')
 * @return: thrd_success: Success
 * @return: thrd_error:   Error */
INTDEF ATTR_INOUT(1) ATTR_INOUT(2) int NOTHROW_RPC(LIBCCALL libc_cnd_wait)(cnd_t *__restrict cond, mtx_t *__restrict mutex);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> cnd_timedwait(3), cnd_timedwait64(3)
 * Wait on the given condition variable (s.a. `pthread_cond_timedwait(3)')
 * @return: thrd_success:  Success
 * @return: thrd_timedout: Timeout
 * @return: thrd_error:    Error */
INTDEF ATTR_IN(3) ATTR_INOUT(1) ATTR_INOUT(2) int NOTHROW_RPC(LIBDCALL libd_cnd_timedwait)(cnd_t *__restrict cond, mtx_t *__restrict mutex, struct timespec const *__restrict time_point);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> cnd_timedwait(3), cnd_timedwait64(3)
 * Wait on the given condition variable (s.a. `pthread_cond_timedwait(3)')
 * @return: thrd_success:  Success
 * @return: thrd_timedout: Timeout
 * @return: thrd_error:    Error */
INTDEF ATTR_IN(3) ATTR_INOUT(1) ATTR_INOUT(2) int NOTHROW_RPC(LIBCCALL libc_cnd_timedwait)(cnd_t *__restrict cond, mtx_t *__restrict mutex, struct timespec const *__restrict time_point);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> cnd_timedwait(3), cnd_timedwait64(3)
 * Wait on the given condition variable (s.a. `pthread_cond_timedwait(3)')
 * @return: thrd_success:  Success
 * @return: thrd_timedout: Timeout
 * @return: thrd_error:    Error */
INTDEF ATTR_IN(3) ATTR_INOUT(1) ATTR_INOUT(2) int NOTHROW_RPC(LIBDCALL libd_cnd_timedwait64)(cnd_t *__restrict cond, mtx_t *__restrict mutex, struct timespec64 const *__restrict time_point);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> cnd_timedwait(3), cnd_timedwait64(3)
 * Wait on the given condition variable (s.a. `pthread_cond_timedwait(3)')
 * @return: thrd_success:  Success
 * @return: thrd_timedout: Timeout
 * @return: thrd_error:    Error */
INTDEF ATTR_IN(3) ATTR_INOUT(1) ATTR_INOUT(2) int NOTHROW_RPC(LIBCCALL libc_cnd_timedwait64)(cnd_t *__restrict cond, mtx_t *__restrict mutex, struct timespec64 const *__restrict time_point);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> tss_create(3)
 * Create a new TLS key (s.a. `pthread_key_create(3)')
 * @return: thrd_success: Success
 * @return: thrd_error:   Error */
INTDEF ATTR_OUT(1) int NOTHROW_NCX(LIBDCALL libd_tss_create)(tss_t *tss_id, void (LIBKCALL *destructor)(void *arg));
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> tss_create(3)
 * Create a new TLS key (s.a. `pthread_key_create(3)')
 * @return: thrd_success: Success
 * @return: thrd_error:   Error */
INTDEF ATTR_OUT(1) int NOTHROW_NCX(LIBCCALL libc_tss_create)(tss_t *tss_id, void (LIBKCALL *destructor)(void *arg));
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> tss_set(3)
 * Set the calling thread's value for the given TLS key (s.a. `pthread_setspecific(3)')
 * @return: thrd_success: Success
 * @return: thrd_error:   Error */
INTDEF ATTR_ACCESS_NONE(2) int NOTHROW_NCX(LIBDCALL libd_tss_set)(tss_t tss_id, void *val);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> tss_set(3)
 * Set the calling thread's value for the given TLS key (s.a. `pthread_setspecific(3)')
 * @return: thrd_success: Success
 * @return: thrd_error:   Error */
INTDEF ATTR_ACCESS_NONE(2) int NOTHROW_NCX(LIBCCALL libc_tss_set)(tss_t tss_id, void *val);
/* >> thr_min_stack(3) */
INTDEF ATTR_CONST WUNUSED size_t NOTHROW(LIBCCALL libc_thr_min_stack)(void);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_THREADS_H */
