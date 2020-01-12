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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_USER_THREADS_C
#define GUARD_LIBC_USER_THREADS_C 1

#include "../api.h"
/**/

#include <parts/errno.h>

#include <pthread.h>
#include <syslog.h>

#include "pthread.h"
#include "threads.h"

DECL_BEGIN

STATIC_ASSERT(sizeof(int) <= sizeof(void *));

/*[[[start:implementation]]]*/

/*[[[head:thrd_create,hash:CRC-32=0x70db4d38]]]*/
/* Create a new thread executing the function FUNC.  Arguments for FUNC
 * are passed through ARG. If successful, THR is set to new thread identifier */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.sched.threads.thrd_create") int
NOTHROW_NCX(LIBCCALL libc_thrd_create)(thrd_t *thr,
                                       thrd_start_t func,
                                       void *arg)
/*[[[body:thrd_create]]]*/
/*AUTO*/{
	int error;
	STATIC_ASSERT(sizeof(int) <= sizeof(void *));
	error = libc_pthread_create((pthread_t *)thr, NULL,
	                       (__pthread_start_routine_t)(void *)func,
	                       arg);
	if likely(!error)
		return 0; /* thrd_success */
#ifdef __ENOMEM
	if (error == __ENOMEM)
		return 3; /* thrd_nomem */
#endif /* __ENOMEM */
	return 2; /* thrd_error */
}
/*[[[end:thrd_create]]]*/

/*[[[head:thrd_sleep,hash:CRC-32=0x6d830c89]]]*/
/* Block current thread execution for at least the time pointed by TIME_POINT.
 * The current thread may resume if receives a signal. In that case, if REMAINING
 * is not NULL, the remaining time is stored in the object pointed by it
 * @return:     0: The given `time_point' has passed
 * @return:    -1: A signal was received while waiting, and `remaining' was filled in (if given)
 * @return: <= -2: Some other error occurred */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.threads.thrd_sleep") int
NOTHROW_RPC(LIBCCALL libc_thrd_sleep)(struct timespec const *time_point,
                                      struct timespec *remaining)
/*[[[body:thrd_sleep]]]*/
{
	(void)time_point;
	(void)remaining;
	CRT_UNIMPLEMENTED("thrd_sleep"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:thrd_sleep]]]*/

/*[[[head:thrd_sleep64,hash:CRC-32=0xfcb95dea]]]*/
/* Block current thread execution for at least the time pointed by TIME_POINT.
 * The current thread may resume if receives a signal. In that case, if REMAINING
 * is not NULL, the remaining time is stored in the object pointed by it
 * @return:     0: The given `time_point' has passed
 * @return:    -1: A signal was received while waiting, and `remaining' was filled in (if given)
 * @return: <= -2: Some other error occurred */
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_thrd_sleep64, libc_thrd_sleep);
#else
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.threads.thrd_sleep64") int
NOTHROW_RPC(LIBCCALL libc_thrd_sleep64)(struct timespec64 const *time_point,
                                        struct timespec64 *remaining)
/*[[[body:thrd_sleep64]]]*/
{
	(void)time_point;
	(void)remaining;
	CRT_UNIMPLEMENTED("thrd_sleep64"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
#endif /* MAGIC:alias */
/*[[[end:thrd_sleep64]]]*/

/*[[[head:thrd_exit,hash:CRC-32=0x52db12ca]]]*/
/* Terminate current thread execution, cleaning up any thread local
 * storage and freeing resources. Returns the value specified in RES
 * s.a. `pthread_exit()' */
INTERN ATTR_NORETURN
ATTR_WEAK ATTR_SECTION(".text.crt.sched.threads.thrd_exit") void
(LIBCCALL libc_thrd_exit)(int res)
/*[[[body:thrd_exit]]]*/
/*AUTO*/{
	libc_pthread_exit((void *)(uintptr_t)(unsigned int)res);
}
/*[[[end:thrd_exit]]]*/

/*[[[head:thrd_detach,hash:CRC-32=0x7e0ab0d8]]]*/
/* Detach the thread identified by THR from the current
 * environment (it does not allow join or wait for it)
 * s.a. `pthread_detach()' */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.sched.threads.thrd_detach") int
NOTHROW_NCX(LIBCCALL libc_thrd_detach)(thrd_t thr)
/*[[[body:thrd_detach]]]*/
/*AUTO*/{
	int error;
	error = libc_pthread_detach((pthread_t)thr);
	if likely(!error)
		return 0; /* thrd_success */
	return 2; /* thrd_error */
}
/*[[[end:thrd_detach]]]*/

/*[[[head:thrd_join,hash:CRC-32=0x4d176179]]]*/
/* Block current thread until execution of THR is complete.
 * In case that RES is not NULL, will store the return value of THR when exiting
 * s.a. `pthread_join()' */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.sched.threads.thrd_join") int
NOTHROW_RPC(LIBCCALL libc_thrd_join)(thrd_t thr,
                                     int *res)
/*[[[body:thrd_join]]]*/
/*AUTO*/{
	int error;
#if __SIZEOF_POINTER__ != __SIZEOF_INT__
	void *resptr;
	error = libc_pthread_join((pthread_t)thr, res ? &resptr : NULL);
	if likely(!error) {
		if (res)
			*res = (int)(unsigned int)(uintptr_t)resptr;
		return 0; /* thrd_success */
	}
#else /* __SIZEOF_POINTER__ != __SIZEOF_INT__ */
	error = libc_pthread_join((pthread_t)thr, (void **)res);
	if likely(!error)
		return 0; /* thrd_success */
#endif /* __SIZEOF_POINTER__ == __SIZEOF_INT__ */
	return 2; /* thrd_error */
}
/*[[[end:thrd_join]]]*/

/*[[[head:mtx_init,hash:CRC-32=0x30046be0]]]*/
/* Creates a new mutex object with type TYPE.
 * If successful the new object is pointed by MUTEX
 * s.a. `pthread_mutex_init()' */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.threads.mtx_init") int
NOTHROW_NCX(LIBCCALL libc_mtx_init)(mtx_t *__restrict mutex,
                                    int type)
/*[[[body:mtx_init]]]*/
/*AUTO*/{
	int error;
	if (type == 0 /*mtx_plain*/) {
		error = libc_pthread_mutex_init((pthread_mutex_t *)mutex, NULL);
	} else {
		pthread_mutexattr_t attr;
		error = libc_pthread_mutexattr_init(&attr);
		if (error == 0) {
			error = libc_pthread_mutexattr_settype(&attr,
			                                  (type & 1) ? __PTHREAD_MUTEX_RECURSIVE
			                                             : __PTHREAD_MUTEX_TIMED);
			if (error == 0)
				error = libc_pthread_mutex_init((pthread_mutex_t *)mutex, &attr);
			libc_pthread_mutexattr_destroy(&attr);
		}
	}
	if likely(!error)
		return 0; /* thrd_success */
	return 2; /* thrd_error */
}
/*[[[end:mtx_init]]]*/

/*[[[head:mtx_lock,hash:CRC-32=0x462c9cd7]]]*/
/* Block the current thread until the mutex pointed to by MUTEX is
 * unlocked.  In that case current thread will not be blocked
 * s.a. `pthread_mutex_lock()' */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.threads.mtx_lock") int
NOTHROW_RPC(LIBCCALL libc_mtx_lock)(mtx_t *__restrict mutex)
/*[[[body:mtx_lock]]]*/
/*AUTO*/{
	int error;
	error = libc_pthread_mutex_lock((pthread_mutex_t *)mutex);
	if likely(!error)
		return 0; /* thrd_success */
	return 2; /* thrd_error */
}
/*[[[end:mtx_lock]]]*/

/*[[[head:mtx_timedlock,hash:CRC-32=0x4d0f5349]]]*/
/* Block the current thread until the mutex pointed by MUTEX
 * is unlocked or time pointed by TIME_POINT is reached.
 * In case the mutex is unlock, the current thread will not be blocked
 * s.a. `pthread_mutex_timedlock()' */
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.threads.mtx_timedlock") int
NOTHROW_RPC(LIBCCALL libc_mtx_timedlock)(mtx_t *__restrict mutex,
                                         struct timespec const *__restrict time_point)
/*[[[body:mtx_timedlock]]]*/
/*AUTO*/{
	int error;
	error = libc_pthread_mutex_timedlock((pthread_mutex_t *)mutex, time_point);
	if likely(!error)
		return 0; /* thrd_success */
	return 2; /* thrd_error */
}
/*[[[end:mtx_timedlock]]]*/

/*[[[head:mtx_trylock,hash:CRC-32=0x7e795193]]]*/
/* Try to lock the mutex pointed by MUTEX without blocking.
 * If the mutex is free the current threads takes control of
 * it, otherwise it returns immediately
 * s.a. `pthread_mutex_trylock()' */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.threads.mtx_trylock") int
NOTHROW_NCX(LIBCCALL libc_mtx_trylock)(mtx_t *__restrict mutex)
/*[[[body:mtx_trylock]]]*/
/*AUTO*/{
	int error;
	error = libc_pthread_mutex_trylock((pthread_mutex_t *)mutex);
	if likely(!error)
		return 0; /* thrd_success */
	return 2; /* thrd_error */
}
/*[[[end:mtx_trylock]]]*/

/*[[[head:mtx_unlock,hash:CRC-32=0xe32fab2d]]]*/
/* Unlock the mutex pointed by MUTEX.
 * It may potentially awake other threads waiting on this mutex
 * s.a. `pthread_mutex_unlock()' */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.threads.mtx_unlock") int
NOTHROW_NCX(LIBCCALL libc_mtx_unlock)(mtx_t *__restrict mutex)
/*[[[body:mtx_unlock]]]*/
/*AUTO*/{
	int error;
	error = libc_pthread_mutex_unlock((pthread_mutex_t *)mutex);
	if likely(!error)
		return 0; /* thrd_success */
	return 2; /* thrd_error */
}
/*[[[end:mtx_unlock]]]*/



/*[[[head:cnd_init,hash:CRC-32=0xa9f30a2e]]]*/
/* Initialize new condition variable pointed by COND
 * s.a. `pthread_cond_init()' */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.threads.cnd_init") int
NOTHROW_NCX(LIBCCALL libc_cnd_init)(cnd_t *__restrict cond)
/*[[[body:cnd_init]]]*/
/*AUTO*/{
	int error;
	error = libc_pthread_cond_init((pthread_cond_t *)cond, NULL);
	if likely(!error)
		return 0; /* thrd_success */
	return 2; /* thrd_error */
}
/*[[[end:cnd_init]]]*/

/*[[[head:cnd_signal,hash:CRC-32=0x28db28fe]]]*/
/* Unblock one thread that currently waits on condition variable pointed by COND
 * s.a. `pthread_cond_signal()' */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.threads.cnd_signal") int
NOTHROW_NCX(LIBCCALL libc_cnd_signal)(cnd_t *__restrict cond)
/*[[[body:cnd_signal]]]*/
/*AUTO*/{
	int error;
	error = libc_pthread_cond_signal((pthread_cond_t *)cond);
	if likely(!error)
		return 0; /* thrd_success */
	return 2; /* thrd_error */
}
/*[[[end:cnd_signal]]]*/

/*[[[head:cnd_broadcast,hash:CRC-32=0xe717665b]]]*/
/* Unblock all threads currently waiting on condition variable pointed by COND
 * s.a. `pthread_cond_broadcast()' */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.threads.cnd_broadcast") int
NOTHROW_NCX(LIBCCALL libc_cnd_broadcast)(cnd_t *__restrict cond)
/*[[[body:cnd_broadcast]]]*/
/*AUTO*/{
	int error;
	error = libc_pthread_cond_broadcast((pthread_cond_t *)cond);
	if likely(!error)
		return 0; /* thrd_success */
	return 2; /* thrd_error */
}
/*[[[end:cnd_broadcast]]]*/

/*[[[head:cnd_wait,hash:CRC-32=0x87c17d99]]]*/
/* Block current thread on the condition variable pointed by COND
 * s.a. `pthread_cond_wait()' */
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.threads.cnd_wait") int
NOTHROW_RPC(LIBCCALL libc_cnd_wait)(cnd_t *__restrict cond,
                                    mtx_t *__restrict mutex)
/*[[[body:cnd_wait]]]*/
/*AUTO*/{
	int error;
	error = libc_pthread_cond_wait((pthread_cond_t *)cond,
	                          (pthread_mutex_t *)mutex);
	if likely(!error)
		return 0; /* thrd_success */
	return 2; /* thrd_error */
}
/*[[[end:cnd_wait]]]*/

/*[[[head:cnd_timedwait,hash:CRC-32=0xb12eb15d]]]*/
/* Block current thread on the condition variable until condition variable
 * pointed by COND is signaled or time pointed by TIME_POINT is reached
 * s.a. `pthread_cond_timedwait()' */
INTERN NONNULL((1, 2, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.threads.cnd_timedwait") int
NOTHROW_RPC(LIBCCALL libc_cnd_timedwait)(cnd_t *__restrict cond,
                                         mtx_t *__restrict mutex,
                                         struct timespec const *__restrict time_point)
/*[[[body:cnd_timedwait]]]*/
/*AUTO*/{
	int error;
	error = libc_pthread_cond_timedwait((pthread_cond_t *)cond,
	                               (pthread_mutex_t *)mutex,
	                               time_point);
	if likely(!error)
		return 0; /* thrd_success */
	if (error == ETIMEDOUT)
		return 4; /* thrd_timedout */
	return 2; /* thrd_error */
}
/*[[[end:cnd_timedwait]]]*/


/*[[[head:tss_create,hash:CRC-32=0xd5ca36d8]]]*/
/* Create new thread-specific storage key and stores it in the object pointed by TSS_ID.
 * If DESTRUCTOR is not NULL, the function will be called when the thread terminates
 * s.a. `pthread_key_create()' */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.sched.threads.tss_create") int
NOTHROW_NCX(LIBCCALL libc_tss_create)(tss_t *tss_id,
                                      tss_dtor_t destructor)
/*[[[body:tss_create]]]*/
/*AUTO*/{
	int error;
	error = libc_pthread_key_create((pthread_key_t *)tss_id, destructor);
	if likely(!error)
		return 0; /* thrd_success */
	return 2; /* thrd_error */
}
/*[[[end:tss_create]]]*/


/*[[[head:tss_set,hash:CRC-32=0xf104f6ef]]]*/
/* Sets the value of the thread-specific storage
 * identified by TSS_ID for the current thread to VAL
 * s.a. `pthread_setspecific()' */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.sched.threads.tss_set") int
NOTHROW_NCX(LIBCCALL libc_tss_set)(tss_t tss_id,
                                   void *val)
/*[[[body:tss_set]]]*/
/*AUTO*/{
	int error;
	error = libc_pthread_setspecific((pthread_key_t)tss_id, val);
	if likely(!error)
		return 0; /* thrd_success */
	return 2; /* thrd_error */
}
/*[[[end:tss_set]]]*/


/*[[[head:mtx_timedlock64,hash:CRC-32=0x96af6595]]]*/
/* Block the current thread until the mutex pointed by MUTEX
 * is unlocked or time pointed by TIME_POINT is reached.
 * In case the mutex is unlock, the current thread will not be blocked
 * s.a. `pthread_mutex_timedlock()' */
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_mtx_timedlock64, libc_mtx_timedlock);
#else
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.threads.mtx_timedlock64") int
NOTHROW_RPC(LIBCCALL libc_mtx_timedlock64)(mtx_t *__restrict mutex,
                                           struct timespec64 const *__restrict time_point)
/*[[[body:mtx_timedlock64]]]*/
/*AUTO*/{
	int error;
	error = libc_pthread_mutex_timedlock64((pthread_mutex_t *)mutex, time_point);
	if likely(!error)
		return 0; /* thrd_success */
	return 2; /* thrd_error */
}
#endif /* MAGIC:alias */
/*[[[end:mtx_timedlock64]]]*/

/*[[[head:cnd_timedwait64,hash:CRC-32=0x807e3edb]]]*/
/* Block current thread on the condition variable until condition variable
 * pointed by COND is signaled or time pointed by TIME_POINT is reached
 * s.a. `pthread_cond_timedwait()' */
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_cnd_timedwait64, libc_cnd_timedwait);
#else
INTERN NONNULL((1, 2, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.threads.cnd_timedwait64") int
NOTHROW_RPC(LIBCCALL libc_cnd_timedwait64)(cnd_t *__restrict cond,
                                           mtx_t *__restrict mutex,
                                           struct timespec64 const *__restrict time_point)
/*[[[body:cnd_timedwait64]]]*/
/*AUTO*/{
	int error;
	error = libc_pthread_cond_timedwait64((pthread_cond_t *)cond,
	                                 (pthread_mutex_t *)mutex,
	                                 time_point);
	if likely(!error)
		return 0; /* thrd_success */
	if (error == ETIMEDOUT)
		return 4; /* thrd_timedout */
	return 2; /* thrd_error */
}
#endif /* MAGIC:alias */
/*[[[end:cnd_timedwait64]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:CRC-32=0x816d775c]]]*/
DEFINE_PUBLIC_WEAK_ALIAS(thrd_create, libc_thrd_create);
DEFINE_PUBLIC_WEAK_ALIAS(thrd_sleep, libc_thrd_sleep);
DEFINE_PUBLIC_WEAK_ALIAS(thrd_sleep64, libc_thrd_sleep64);
DEFINE_PUBLIC_WEAK_ALIAS(thrd_exit, libc_thrd_exit);
DEFINE_PUBLIC_WEAK_ALIAS(thrd_detach, libc_thrd_detach);
DEFINE_PUBLIC_WEAK_ALIAS(thrd_join, libc_thrd_join);
DEFINE_PUBLIC_WEAK_ALIAS(mtx_init, libc_mtx_init);
DEFINE_PUBLIC_WEAK_ALIAS(mtx_lock, libc_mtx_lock);
DEFINE_PUBLIC_WEAK_ALIAS(mtx_timedlock, libc_mtx_timedlock);
DEFINE_PUBLIC_WEAK_ALIAS(mtx_timedlock64, libc_mtx_timedlock64);
DEFINE_PUBLIC_WEAK_ALIAS(mtx_trylock, libc_mtx_trylock);
DEFINE_PUBLIC_WEAK_ALIAS(mtx_unlock, libc_mtx_unlock);
DEFINE_PUBLIC_WEAK_ALIAS(cnd_init, libc_cnd_init);
DEFINE_PUBLIC_WEAK_ALIAS(cnd_signal, libc_cnd_signal);
DEFINE_PUBLIC_WEAK_ALIAS(cnd_broadcast, libc_cnd_broadcast);
DEFINE_PUBLIC_WEAK_ALIAS(cnd_wait, libc_cnd_wait);
DEFINE_PUBLIC_WEAK_ALIAS(cnd_timedwait, libc_cnd_timedwait);
DEFINE_PUBLIC_WEAK_ALIAS(cnd_timedwait64, libc_cnd_timedwait64);
DEFINE_PUBLIC_WEAK_ALIAS(tss_create, libc_tss_create);
DEFINE_PUBLIC_WEAK_ALIAS(tss_set, libc_tss_set);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_THREADS_C */
