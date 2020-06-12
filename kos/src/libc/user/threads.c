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
#ifndef GUARD_LIBC_USER_THREADS_C
#define GUARD_LIBC_USER_THREADS_C 1

#include "../api.h"
/**/

#include <kos/syscalls.h>
#include <parts/errno.h>

#include <pthread.h>

#include "pthread.h"
#include "threads.h"

DECL_BEGIN

STATIC_ASSERT(sizeof(int) <= sizeof(void *));

/*[[[start:implementation]]]*/

/*[[[head:libc_thrd_create,hash:CRC-32=0x4963fb47]]]*/
/* Create a new thread executing the function FUNC.  Arguments for FUNC
 * are passed through ARG. If successful, THR is set to new thread identifier */
INTERN ATTR_SECTION(".text.crt.sched.threads") int
NOTHROW_NCX(LIBCCALL libc_thrd_create)(thrd_t *thr,
                                       thrd_start_t func,
                                       void *arg)
/*[[[body:libc_thrd_create]]]*/
/*AUTO*/{
	int error;
	STATIC_ASSERT(sizeof(int) <= sizeof(void *));
	error = pthread_create((pthread_t *)thr, NULL,
	                       (__pthread_start_routine_t)(void *)func,
	                       arg);
	if likely(!error)
		return thrd_success;
#ifdef ENOMEM
	if (error == ENOMEM)
		return thrd_nomem;
#endif /* ENOMEM */
	return thrd_error;
}
/*[[[end:libc_thrd_create]]]*/

/*[[[head:libc_thrd_sleep,hash:CRC-32=0x9652694]]]*/
/* Block current thread execution for at least the (relative) time pointed by TIME_POINT.
 * The current thread may resume if receives a signal. In that case, if REMAINING
 * is not NULL, the remaining time is stored in the object pointed by it
 * @return:     0: The (relative) time specified by `time_point' has elapsed
 * @return:    -1: A signal was received while waiting, and `remaining' was filled in (if given)
 * @return: <= -2: Some other error occurred */
INTERN ATTR_SECTION(".text.crt.sched.threads") NONNULL((1)) int
NOTHROW_RPC(LIBCCALL libc_thrd_sleep)(struct timespec const *time_point,
                                      struct timespec *remaining)
/*[[[body:libc_thrd_sleep]]]*/
{
	errno_t error;
	error = sys_nanosleep(time_point, remaining);
	if likely(E_ISOK(error))
		return 0;
	if (error == -EINTR)
		return -1;
	return -2;
}
/*[[[end:libc_thrd_sleep]]]*/

/*[[[head:libc_thrd_sleep64,hash:CRC-32=0x5b3a3ab6]]]*/
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_thrd_sleep64, libc_thrd_sleep);
#else /* MAGIC:alias */
/* Block current thread execution for at least the (relative) time pointed by TIME_POINT.
 * The current thread may resume if receives a signal. In that case, if REMAINING
 * is not NULL, the remaining time is stored in the object pointed by it
 * @return:     0: The (relative) time specified by `time_point' has elapsed
 * @return:    -1: A signal was received while waiting, and `remaining' was filled in (if given)
 * @return: <= -2: Some other error occurred */
INTERN ATTR_SECTION(".text.crt.sched.threads") NONNULL((1)) int
NOTHROW_RPC(LIBCCALL libc_thrd_sleep64)(struct timespec64 const *time_point,
                                        struct timespec64 *remaining)
/*[[[body:libc_thrd_sleep64]]]*/
{
#ifdef __NR_nanosleep64
	errno_t error;
	error = sys_nanosleep64(time_point, remaining);
	if likely(E_ISOK(error))
		return 0;
	if (error == -EINTR)
		return -1;
	return -2;
#else /* __NR_nanosleep64 */
	int result;
	struct timespec32 tp32, rm32;
	tp32.tv_sec  = (time32_t)time_point->tv_sec;
	tp32.tv_nsec = time_point->tv_nsec;
	result = thrd_sleep(&tp32, remaining ? &rm32 : NULL);
	if ((result != 0) && remaining) {
		remaining->tv_sec  = (time64_t)rm32.tv_sec;
		remaining->tv_nsec = rm32.tv_nsec;
	}
	return result;
#endif /* !__NR_nanosleep64 */
}
#endif /* MAGIC:alias */
/*[[[end:libc_thrd_sleep64]]]*/

/*[[[head:libc_thrd_exit,hash:CRC-32=0xcb96d623]]]*/
/* Terminate current thread execution, cleaning up any thread local
 * storage and freeing resources. Returns the value specified in RES
 * s.a. `pthread_exit()' */
INTERN ATTR_SECTION(".text.crt.sched.threads") ATTR_NORETURN void
(LIBCCALL libc_thrd_exit)(int res) THROWS(...)
/*[[[body:libc_thrd_exit]]]*/
/*AUTO*/{
	pthread_exit((void *)(uintptr_t)(unsigned int)res);
}
/*[[[end:libc_thrd_exit]]]*/

/*[[[head:libc_thrd_detach,hash:CRC-32=0xb2233f04]]]*/
/* Detach the thread identified by THR from the current
 * environment (it does not allow join or wait for it)
 * s.a. `pthread_detach()' */
INTERN ATTR_SECTION(".text.crt.sched.threads") int
NOTHROW_NCX(LIBCCALL libc_thrd_detach)(thrd_t thr)
/*[[[body:libc_thrd_detach]]]*/
/*AUTO*/{
	int error;
	error = pthread_detach((pthread_t)thr);
	if likely(!error)
		return thrd_success;
	return thrd_error;
}
/*[[[end:libc_thrd_detach]]]*/

/*[[[head:libc_thrd_join,hash:CRC-32=0xe3f7563a]]]*/
/* Block current thread until execution of THR is complete.
 * In case that RES is not NULL, will store the return value of THR when exiting
 * s.a. `pthread_join()' */
INTERN ATTR_SECTION(".text.crt.sched.threads") int
NOTHROW_RPC(LIBCCALL libc_thrd_join)(thrd_t thr,
                                     int *res)
/*[[[body:libc_thrd_join]]]*/
/*AUTO*/{
	int error;
#if __SIZEOF_POINTER__ != __SIZEOF_INT__
	void *resptr;
	error = pthread_join((pthread_t)thr, res ? &resptr : NULL);
	if likely(!error) {
		if (res)
			*res = (int)(unsigned int)(uintptr_t)resptr;
		return thrd_success;
	}
#else /* __SIZEOF_POINTER__ != __SIZEOF_INT__ */
	error = pthread_join((pthread_t)thr, (void **)res);
	if likely(!error)
		return thrd_success;
#endif /* !(__SIZEOF_POINTER__ != __SIZEOF_INT__) */
	return thrd_error;
}
/*[[[end:libc_thrd_join]]]*/

/*[[[head:libc_mtx_init,hash:CRC-32=0x2325b925]]]*/
/* Creates a new mutex object with type TYPE.
 * If successful the new object is pointed by MUTEX
 * s.a. `pthread_mutex_init()' */
INTERN ATTR_SECTION(".text.crt.sched.threads") NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_mtx_init)(mtx_t *__restrict mutex,
                                    __STDC_INT_AS_UINT_T type)
/*[[[body:libc_mtx_init]]]*/
/*AUTO*/{
	int error;
	if (type == mtx_plain) {
		error = pthread_mutex_init((pthread_mutex_t *)mutex, NULL);
	} else {
		pthread_mutexattr_t attr;
		error = pthread_mutexattr_init(&attr);
		if (error == 0) {
			error = pthread_mutexattr_settype(&attr,
			                                  (type & 1) ? __PTHREAD_MUTEX_RECURSIVE
			                                             : __PTHREAD_MUTEX_TIMED);
			if (error == 0)
				error = pthread_mutex_init((pthread_mutex_t *)mutex, &attr);
			pthread_mutexattr_destroy(&attr);
		}
	}
	if likely(!error)
		return thrd_success;
	return thrd_error;
}
/*[[[end:libc_mtx_init]]]*/

/*[[[head:libc_mtx_lock,hash:CRC-32=0x634a5462]]]*/
/* Block the current thread until the mutex pointed to by MUTEX is
 * unlocked.  In that case current thread will not be blocked
 * s.a. `pthread_mutex_lock()' */
INTERN ATTR_SECTION(".text.crt.sched.threads") NONNULL((1)) int
NOTHROW_RPC(LIBCCALL libc_mtx_lock)(mtx_t *__restrict mutex)
/*[[[body:libc_mtx_lock]]]*/
/*AUTO*/{
	int error;
	error = pthread_mutex_lock((pthread_mutex_t *)mutex);
	if likely(!error)
		return thrd_success;
	return thrd_error;
}
/*[[[end:libc_mtx_lock]]]*/

/*[[[head:libc_mtx_timedlock,hash:CRC-32=0xb3c95990]]]*/
/* Block the current thread until the mutex pointed by MUTEX
 * is unlocked or time pointed by TIME_POINT is reached.
 * In case the mutex is unlock, the current thread will not be blocked
 * s.a. `pthread_mutex_timedlock()' */
INTERN ATTR_SECTION(".text.crt.sched.threads") NONNULL((1, 2)) int
NOTHROW_RPC(LIBCCALL libc_mtx_timedlock)(mtx_t *__restrict mutex,
                                         struct timespec const *__restrict time_point)
/*[[[body:libc_mtx_timedlock]]]*/
/*AUTO*/{
	int error;
	error = pthread_mutex_timedlock((pthread_mutex_t *)mutex, time_point);
	if likely(!error)
		return thrd_success;
	return thrd_error;
}
/*[[[end:libc_mtx_timedlock]]]*/

/*[[[head:libc_mtx_trylock,hash:CRC-32=0xbe84c0ff]]]*/
/* Try to lock the mutex pointed by MUTEX without blocking.
 * If the mutex is free the current threads takes control of
 * it, otherwise it returns immediately
 * s.a. `pthread_mutex_trylock()' */
INTERN ATTR_SECTION(".text.crt.sched.threads") NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_mtx_trylock)(mtx_t *__restrict mutex)
/*[[[body:libc_mtx_trylock]]]*/
/*AUTO*/{
	int error;
	error = pthread_mutex_trylock((pthread_mutex_t *)mutex);
	if likely(!error)
		return thrd_success;
	return thrd_error;
}
/*[[[end:libc_mtx_trylock]]]*/

/*[[[head:libc_mtx_unlock,hash:CRC-32=0xc8558bd1]]]*/
/* Unlock the mutex pointed by MUTEX.
 * It may potentially awake other threads waiting on this mutex
 * s.a. `pthread_mutex_unlock()' */
INTERN ATTR_SECTION(".text.crt.sched.threads") NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_mtx_unlock)(mtx_t *__restrict mutex)
/*[[[body:libc_mtx_unlock]]]*/
/*AUTO*/{
	int error;
	error = pthread_mutex_unlock((pthread_mutex_t *)mutex);
	if likely(!error)
		return thrd_success;
	return thrd_error;
}
/*[[[end:libc_mtx_unlock]]]*/



/*[[[head:libc_cnd_init,hash:CRC-32=0x54d46090]]]*/
/* Initialize new condition variable pointed by COND
 * s.a. `pthread_cond_init()' */
INTERN ATTR_SECTION(".text.crt.sched.threads") NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_cnd_init)(cnd_t *__restrict cond)
/*[[[body:libc_cnd_init]]]*/
/*AUTO*/{
	int error;
	error = pthread_cond_init((pthread_cond_t *)cond, NULL);
	if likely(!error)
		return thrd_success;
	return thrd_error;
}
/*[[[end:libc_cnd_init]]]*/

/*[[[head:libc_cnd_signal,hash:CRC-32=0xc5a06121]]]*/
/* Unblock one thread that currently waits on condition variable pointed by COND
 * s.a. `pthread_cond_signal()' */
INTERN ATTR_SECTION(".text.crt.sched.threads") NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_cnd_signal)(cnd_t *__restrict cond)
/*[[[body:libc_cnd_signal]]]*/
/*AUTO*/{
	int error;
	error = pthread_cond_signal((pthread_cond_t *)cond);
	if likely(!error)
		return thrd_success;
	return thrd_error;
}
/*[[[end:libc_cnd_signal]]]*/

/*[[[head:libc_cnd_broadcast,hash:CRC-32=0xef615182]]]*/
/* Unblock all threads currently waiting on condition variable pointed by COND
 * s.a. `pthread_cond_broadcast()' */
INTERN ATTR_SECTION(".text.crt.sched.threads") NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_cnd_broadcast)(cnd_t *__restrict cond)
/*[[[body:libc_cnd_broadcast]]]*/
/*AUTO*/{
	int error;
	error = pthread_cond_broadcast((pthread_cond_t *)cond);
	if likely(!error)
		return thrd_success;
	return thrd_error;
}
/*[[[end:libc_cnd_broadcast]]]*/

/*[[[head:libc_cnd_wait,hash:CRC-32=0x84fb4503]]]*/
/* Block current thread on the condition variable pointed by COND
 * s.a. `pthread_cond_wait()' */
INTERN ATTR_SECTION(".text.crt.sched.threads") NONNULL((1, 2)) int
NOTHROW_RPC(LIBCCALL libc_cnd_wait)(cnd_t *__restrict cond,
                                    mtx_t *__restrict mutex)
/*[[[body:libc_cnd_wait]]]*/
/*AUTO*/{
	int error;
	error = pthread_cond_wait((pthread_cond_t *)cond,
	                          (pthread_mutex_t *)mutex);
	if likely(!error)
		return thrd_success;
	return thrd_error;
}
/*[[[end:libc_cnd_wait]]]*/

/*[[[head:libc_cnd_timedwait,hash:CRC-32=0xbfe6bc32]]]*/
/* Block current thread on the condition variable until condition variable
 * pointed by COND is signaled or time pointed by TIME_POINT is reached
 * s.a. `pthread_cond_timedwait()' */
INTERN ATTR_SECTION(".text.crt.sched.threads") NONNULL((1, 2, 3)) int
NOTHROW_RPC(LIBCCALL libc_cnd_timedwait)(cnd_t *__restrict cond,
                                         mtx_t *__restrict mutex,
                                         struct timespec const *__restrict time_point)
/*[[[body:libc_cnd_timedwait]]]*/
/*AUTO*/{
	int error;
	error = pthread_cond_timedwait((pthread_cond_t *)cond,
	                               (pthread_mutex_t *)mutex,
	                               time_point);
	if likely(!error)
		return thrd_success;
	if (error == ETIMEDOUT)
		return thrd_timedout;
	return thrd_error;
}
/*[[[end:libc_cnd_timedwait]]]*/


/*[[[head:libc_tss_create,hash:CRC-32=0x4cfaf566]]]*/
/* Create new thread-specific storage key and stores it in the object pointed by TSS_ID.
 * If DESTRUCTOR is not NULL, the function will be called when the thread terminates
 * s.a. `pthread_key_create()' */
INTERN ATTR_SECTION(".text.crt.sched.threads") int
NOTHROW_NCX(LIBCCALL libc_tss_create)(tss_t *tss_id,
                                      tss_dtor_t destructor)
/*[[[body:libc_tss_create]]]*/
/*AUTO*/{
	int error;
	error = pthread_key_create((pthread_key_t *)tss_id, destructor);
	if likely(!error)
		return thrd_success;
	return thrd_error;
}
/*[[[end:libc_tss_create]]]*/


/*[[[head:libc_tss_set,hash:CRC-32=0xa14dc97a]]]*/
/* Sets the value of the thread-specific storage
 * identified by TSS_ID for the current thread to VAL
 * s.a. `pthread_setspecific()' */
INTERN ATTR_SECTION(".text.crt.sched.threads") int
NOTHROW_NCX(LIBCCALL libc_tss_set)(tss_t tss_id,
                                   void *val)
/*[[[body:libc_tss_set]]]*/
/*AUTO*/{
	int error;
	error = pthread_setspecific((pthread_key_t)tss_id, val);
	if likely(!error)
		return thrd_success;
	return thrd_error;
}
/*[[[end:libc_tss_set]]]*/


/*[[[head:libc_mtx_timedlock64,hash:CRC-32=0x2cbf0464]]]*/
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_mtx_timedlock64, libc_mtx_timedlock);
#else /* MAGIC:alias */
/* Block the current thread until the mutex pointed by MUTEX
 * is unlocked or time pointed by TIME_POINT is reached.
 * In case the mutex is unlock, the current thread will not be blocked
 * s.a. `pthread_mutex_timedlock()' */
INTERN ATTR_SECTION(".text.crt.sched.threads") NONNULL((1, 2)) int
NOTHROW_RPC(LIBCCALL libc_mtx_timedlock64)(mtx_t *__restrict mutex,
                                           struct timespec64 const *__restrict time_point)
/*[[[body:libc_mtx_timedlock64]]]*/
/*AUTO*/{
	int error;
	error = pthread_mutex_timedlock64((pthread_mutex_t *)mutex, time_point);
	if likely(!error)
		return thrd_success;
	return thrd_error;
}
#endif /* MAGIC:alias */
/*[[[end:libc_mtx_timedlock64]]]*/

/*[[[head:libc_cnd_timedwait64,hash:CRC-32=0x8c0a7278]]]*/
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_cnd_timedwait64, libc_cnd_timedwait);
#else /* MAGIC:alias */
/* Block current thread on the condition variable until condition variable
 * pointed by COND is signaled or time pointed by TIME_POINT is reached
 * s.a. `pthread_cond_timedwait()' */
INTERN ATTR_SECTION(".text.crt.sched.threads") NONNULL((1, 2, 3)) int
NOTHROW_RPC(LIBCCALL libc_cnd_timedwait64)(cnd_t *__restrict cond,
                                           mtx_t *__restrict mutex,
                                           struct timespec64 const *__restrict time_point)
/*[[[body:libc_cnd_timedwait64]]]*/
/*AUTO*/{
	int error;
	error = pthread_cond_timedwait64((pthread_cond_t *)cond,
	                                 (pthread_mutex_t *)mutex,
	                                 time_point);
	if likely(!error)
		return thrd_success;
	if (error == ETIMEDOUT)
		return thrd_timedout;
	return thrd_error;
}
#endif /* MAGIC:alias */
/*[[[end:libc_cnd_timedwait64]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:CRC-32=0x590f7a1]]]*/
DEFINE_PUBLIC_ALIAS(thrd_create, libc_thrd_create);
DEFINE_PUBLIC_ALIAS(thrd_sleep, libc_thrd_sleep);
DEFINE_PUBLIC_ALIAS(thrd_sleep64, libc_thrd_sleep64);
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
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_THREADS_C */
