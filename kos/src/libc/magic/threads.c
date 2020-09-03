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

%[default:section(".text.crt{|.dos}.sched.threads")]

%[define_replacement(tss_t = __tss_t)]
%[define_replacement(thrd_t = __thrd_t)]
%[define_replacement(tss_dtor_t = __tss_dtor_t)]
%[define_replacement(thrd_start_t = __thrd_start_t)]
%[define_replacement(once_flag = __once_flag)]
%[define_replacement(ONCE_FLAG_INIT = __ONCE_FLAG_INIT)]
%[define_replacement(mtx_t = __mtx_t)]
%[define_replacement(cnd_t = __cnd_t)]
%[define_replacement(STATIC_ASSERT = __STATIC_ASSERT)]

%[define_type_class(tss_t = "TIn(__SIZEOF_PTHREAD_KEY_T)")]
%[define_type_class(thrd_t = "TIn(__SIZEOF_PTHREAD_T)")]
%[define_type_class(thrd_start_t = "TP")]
%[define_type_class(tss_dtor_t = "TP")]

%[define_replacement(thrd_success  = __thrd_success)]
%[define_replacement(thrd_busy     = __thrd_busy)]
%[define_replacement(thrd_error    = __thrd_error)]
%[define_replacement(thrd_nomem    = __thrd_nomem)]
%[define_replacement(thrd_timedout = __thrd_timedout)]

%[define_replacement(mtx_plain     = __mtx_plain)]
%[define_replacement(mtx_recursive = __mtx_recursive)]
%[define_replacement(mtx_timed     = __mtx_timed)]

%(auto_source){
STATIC_ASSERT(sizeof(int) <= sizeof(void *));
}

%{
#include <features.h>

#include <hybrid/typecore.h>

#include <asm/crt/threads.h>
#include <bits/crt/threads.h>
#include <bits/timespec.h>
#include <kos/anno.h>

__SYSDECL_BEGIN

/* Documentation taken from Glibc /usr/include/threads.h, but have since been modified */
/* ISO C11 Standard: 7.26 - Thread support library  <threads.h>.
   Copyright (C) 2018-2019 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */


#ifndef TSS_DTOR_ITERATIONS
#define TSS_DTOR_ITERATIONS 4
#endif /* !TSS_DTOR_ITERATIONS */


#if (defined(__thrd_success) || defined(__thrd_busy) || \
     defined(__thrd_error) || defined(__thrd_nomem) ||  \
     defined(__thrd_timedout))
/* Exit and error codes.  */
/*[[[enum]]]*/
#ifdef __CC__
enum {
#ifdef __thrd_success
	thrd_success  = __thrd_success,
#endif /* __thrd_success */
#ifdef __thrd_busy
	thrd_busy     = __thrd_busy,
#endif /* __thrd_busy */
#ifdef __thrd_error
	thrd_error    = __thrd_error,
#endif /* __thrd_error */
#ifdef __thrd_nomem
	thrd_nomem    = __thrd_nomem,
#endif /* __thrd_nomem */
#ifdef __thrd_timedout
	thrd_timedout = __thrd_timedout
#endif /* __thrd_timedout */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#ifdef __thrd_success
#define thrd_success  thrd_success
#endif /* __thrd_success */
#ifdef __thrd_busy
#define thrd_busy     thrd_busy
#endif /* __thrd_busy */
#ifdef __thrd_error
#define thrd_error    thrd_error
#endif /* __thrd_error */
#ifdef __thrd_nomem
#define thrd_nomem    thrd_nomem
#endif /* __thrd_nomem */
#ifdef __thrd_timedout
#define thrd_timedout thrd_timedout
#endif /* __thrd_timedout */
#else /* __COMPILER_PREFERR_ENUMS */
#ifdef __thrd_success
#define thrd_success  __thrd_success
#endif /* __thrd_success */
#ifdef __thrd_busy
#define thrd_busy     __thrd_busy
#endif /* __thrd_busy */
#ifdef __thrd_error
#define thrd_error    __thrd_error
#endif /* __thrd_error */
#ifdef __thrd_nomem
#define thrd_nomem    __thrd_nomem
#endif /* __thrd_nomem */
#ifdef __thrd_timedout
#define thrd_timedout __thrd_timedout
#endif /* __thrd_timedout */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/
#endif /* ... */

#if (defined(__mtx_plain) || defined(__mtx_recursive) || \
     defined(__mtx_timed))
/* Mutex types.  */
/*[[[enum]]]*/
#ifdef __CC__
enum {
#ifdef __mtx_plain
	mtx_plain     = __mtx_plain,
#endif /* __mtx_plain */
#ifdef __mtx_recursive
	mtx_recursive = __mtx_recursive,
#endif /* __mtx_recursive */
#ifdef __mtx_timed
	mtx_timed     = __mtx_timed
#endif /* __mtx_timed */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#ifdef __mtx_plain
#define mtx_plain     mtx_plain
#endif /* __mtx_plain */
#ifdef __mtx_recursive
#define mtx_recursive mtx_recursive
#endif /* __mtx_recursive */
#ifdef __mtx_timed
#define mtx_timed     mtx_timed
#endif /* __mtx_timed */
#else /* __COMPILER_PREFERR_ENUMS */
#ifdef __mtx_plain
#define mtx_plain     __mtx_plain
#endif /* __mtx_plain */
#ifdef __mtx_recursive
#define mtx_recursive __mtx_recursive
#endif /* __mtx_recursive */
#ifdef __mtx_timed
#define mtx_timed     __mtx_timed
#endif /* __mtx_timed */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/
#endif /* ... */


#ifdef __CC__

typedef __tss_t tss_t;
typedef __thrd_t thrd_t;
typedef __tss_dtor_t tss_dtor_t;
typedef __thrd_start_t thrd_start_t;
typedef __once_flag once_flag;
#define ONCE_FLAG_INIT __ONCE_FLAG_INIT
typedef __mtx_t mtx_t;
typedef __cnd_t cnd_t;

}


@@Create a new thread executing the function FUNC.  Arguments for FUNC
@@are passed through ARG. If successful, THR is set to new thread identifier
[[decl_include("<bits/crt/threads.h>")]]
[[impl_include("<asm/crt/threads.h>", "<libc/errno.h>")]]
[[requires_function(pthread_create)]]
int thrd_create(thrd_t *thr, thrd_start_t func, void *arg) {
	$errno_t error;
	STATIC_ASSERT(sizeof(int) <= sizeof(void *));
	error = pthread_create((pthread_t *)thr, NULL,
	                       (__pthread_start_routine_t)(void *)func,
	                       arg);
	if likely(!error)
		return thrd_success;
@@pp_if defined(thrd_nomem) && defined(ENOMEM)@@
	if (error == ENOMEM)
		return thrd_nomem;
@@pp_endif@@
	return thrd_error;
}

[[decl_include("<bits/crt/threads.h>")]]
int thrd_equal(thrd_t thr1, thrd_t thr2) = pthread_equal;

@@Return current thread identifier
@@s.a. `pthread_self()'
[[decl_include("<bits/crt/threads.h>")]]
thrd_t thrd_current() = pthread_self;

@@Block current thread execution for at least the (relative) time pointed by TIME_POINT.
@@The current thread may resume if receives a signal. In that case, if REMAINING
@@is not NULL, the remaining time is stored in the object pointed by it
@@@return:     0: The (relative) time specified by `time_point' has elapsed
@@@return:    -1: A signal was received while waiting, and `remaining' was filled in (if given)
@@@return: <= -2: Some other error occurred
[[cp, no_crt_self_import, decl_include("<bits/timespec.h>")]]
[[if(defined(__USE_TIME_BITS64)), preferred_alias("thrd_sleep64")]]
[[if(!defined(__USE_TIME_BITS64)), preferred_alias("thrd_sleep")]]
[[impl_include("<asm/crt/threads.h>", "<libc/errno.h>")]]
[[userimpl, requires($has_function(thrd_sleep32) || $has_function(crt_thrd_sleep64) || $has_function(nanosleep))]]
int thrd_sleep([[nonnull]] struct timespec const *time_point,
               [[nullable]] struct timespec *remaining) {
@@pp_if $has_function(thrd_sleep32)@@
	int result;
	struct timespec32 tp32, rem32;
	tp32.tv_sec  = (time32_t)time_point->tv_sec;
	tp32.tv_nsec = time_point->tv_nsec;
	result = thrd_sleep32(&tp32, remaining ? &rem32 : NULL);
	if (result == -1 && remaining) {
		remaining->tv_sec = (time64_t)rem32.tv_sec;
		remaining->tv_nsec = rem32.tv_nsec;
	}
	return result;
@@pp_elif $has_function(crt_thrd_sleep64)@@
	int result;
	struct timespec64 tp64, rem64;
	tp64.tv_sec  = (time64_t)time_point->tv_sec;
	tp64.tv_nsec = time_point->tv_nsec;
	result = crt_thrd_sleep64(&tp64, remaining ? &rem64 : NULL);
	if (result == -1 && remaining) {
		remaining->tv_sec = (time32_t)rem64.tv_sec;
		remaining->tv_nsec = rem64.tv_nsec;
	}
	return result;
@@pp_else@@
	int result;
	result = nanosleep(time_point, remaining);
	if likely(result == 0)
		return 0;
@@pp_if defined(__libc_geterrno) && defined(EINTR)@@
	if (__libc_geterrno() == EINTR)
		return -1;
@@pp_endif@@
	return -2;
@@pp_endif@@
}

%#ifdef __USE_TIME64
[[cp, doc_alias("thrd_sleep"), ignore, nocrt, alias("thrd_sleep")]]
[[decl_include("<bits/timespec.h>")]]
int thrd_sleep32([[nonnull]] struct $timespec32 const *time_point,
                 [[nullable]] struct $timespec32 *remaining);

[[cp, doc_alias("thrd_sleep"), ignore, nocrt, alias("thrd_sleep64")]]
[[decl_include("<bits/timespec.h>")]]
int crt_thrd_sleep64([[nonnull]] struct timespec64 const *time_point,
                     [[nullable]] struct timespec64 *remaining);

[[cp, doc_alias("thrd_sleep")]]
[[decl_include("<bits/timespec.h>"), time64_variant_of(thrd_sleep)]]
[[userimpl, requires($has_function(thrd_sleep32) || $has_function(nanosleep64))]]
int thrd_sleep64([[nonnull]] struct timespec64 const *time_point,
                 [[nullable]] struct timespec64 *remaining) {
@@pp_if $has_function(nanosleep64)@@
	int result;
	result = nanosleep64(time_point, remaining);
	if likely(result == 0)
		return 0;
@@pp_if defined(__libc_geterrno) && defined(EINTR)@@
	if (__libc_geterrno() == EINTR)
		return -1;
@@pp_endif@@
	return -2;
@@pp_else@@
	int result;
	struct timespec32 tp32;
	struct timespec32 rem32;
	tp32.tv_sec  = (time32_t)time_point->tv_sec;
	tp32.tv_nsec = time_point->tv_nsec;
	result = thrd_sleep32(&tp32, remaining ? &rem32 : NULL);
	if (result == -1 && remaining) {
		remaining->tv_sec = (time64_t)rem32.tv_sec;
		remaining->tv_nsec = rem32.tv_nsec;
	}
	return result;
@@pp_endif@@
}
%#endif /* __USE_TIME64 */

@@Terminate current thread execution, cleaning up any thread local
@@storage and freeing resources. Returns the value specified in RES
@@s.a. `pthread_exit()'
[[ATTR_NORETURN, throws]]
[[requires_function(pthread_exit)]]
void thrd_exit(int res) {
	pthread_exit((void *)(uintptr_t)(unsigned int)res);
}

@@Detach the thread identified by THR from the current
@@environment (it does not allow join or wait for it)
@@s.a. `pthread_detach()'
[[impl_include("<asm/crt/threads.h>")]]
[[decl_include("<bits/crt/threads.h>")]]
[[requires_function(pthread_detach)]]
int thrd_detach(thrd_t thr) {
	$errno_t error;
	error = pthread_detach((pthread_t)thr);
	if likely(!error)
		return thrd_success;
	return thrd_error;
}

@@Block current thread until execution of THR is complete.
@@In case that RES is not NULL, will store the return value of THR when exiting
@@s.a. `pthread_join()'
[[cp, decl_include("<bits/crt/threads.h>")]]
[[impl_include("<asm/crt/threads.h>")]]
[[requires_function(pthread_join)]]
int thrd_join(thrd_t thr, int *res) {
	$errno_t error;
@@pp_if __SIZEOF_POINTER__ != __SIZEOF_INT__@@
	void *resptr;
	error = pthread_join((pthread_t)thr, res ? &resptr : NULL);
	if likely(!error) {
		if (res)
			*res = (int)(unsigned int)(uintptr_t)resptr;
		return thrd_success;
	}
@@pp_else@@
	error = pthread_join((pthread_t)thr, (void **)res);
	if likely(!error)
		return thrd_success;
@@pp_endif@@
	return thrd_error;
}

@@Stop current thread execution and call the scheduler to decide which
@@thread should execute next. The current thread may be selected by the
@@scheduler to keep running
@@s.a. `pthread_yield()'
[[nothrow]]
void thrd_yield() = pthread_yield;



%
%
%/* Mutex functions.  */
%

@@Creates a new mutex object with type TYPE.
@@If successful the new object is pointed by MUTEX
@@s.a. `pthread_mutex_init()'
[[decl_include("<features.h>", "<bits/crt/threads.h>")]]
[[impl_include("<asm/crt/threads.h>", "<asm/crt/pthreadvalues.h>", "<bits/crt/pthreadtypes.h>")]]
[[requires_function(pthread_mutex_init)]]
int mtx_init([[nonnull]] mtx_t *__restrict mutex, __STDC_INT_AS_UINT_T type) {
	$errno_t error;
	if (type == mtx_plain) {
		error = pthread_mutex_init((pthread_mutex_t *)mutex, NULL);
	} else {
		pthread_mutexattr_t attr;
		error = pthread_mutexattr_init(&attr);
		if (error == 0) {
			error = pthread_mutexattr_settype(&attr,
			                                  type == mtx_recursive
			                                  ? __PTHREAD_MUTEX_RECURSIVE
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

@@Block the current thread until the mutex pointed to by MUTEX is
@@unlocked.  In that case current thread will not be blocked
@@s.a. `pthread_mutex_lock()'
[[cp, decl_include("<bits/crt/threads.h>")]]
[[impl_include("<asm/crt/threads.h>", "<bits/crt/pthreadtypes.h>")]]
[[requires_function(pthread_mutex_lock)]]
int mtx_lock([[nonnull]] mtx_t *__restrict mutex) {
	$errno_t error;
	error = pthread_mutex_lock((pthread_mutex_t *)mutex);
	if likely(!error)
		return thrd_success;
	return thrd_error;
}

@@Block the current thread until the mutex pointed by MUTEX
@@is unlocked or time pointed by TIME_POINT is reached.
@@In case the mutex is unlock, the current thread will not be blocked
@@s.a. `pthread_mutex_timedlock()'
[[cp, no_crt_self_import]]
[[if(defined(__USE_TIME_BITS64)), preferred_alias("mtx_timedlock64")]]
[[if(!defined(__USE_TIME_BITS64)), preferred_alias("mtx_timedlock")]]
[[decl_include("<bits/crt/threads.h>")]]
[[impl_include("<asm/crt/threads.h>", "<bits/crt/pthreadtypes.h>")]]
[[requires_function(pthread_mutex_timedlock)]]
int mtx_timedlock([[nonnull]] mtx_t *__restrict mutex,
                  [[nonnull]] struct timespec const *__restrict time_point) {
	$errno_t error;
	error = pthread_mutex_timedlock((pthread_mutex_t *)mutex, time_point);
	if likely(!error)
		return thrd_success;
	return thrd_error;
}

%#ifdef __USE_TIME64
[[cp, doc_alias("mtx_timedlock"), time64_variant_of(mtx_timedlock)]]
[[decl_include("<bits/crt/threads.h>")]]
[[impl_include("<asm/crt/threads.h>", "<bits/crt/pthreadtypes.h>")]]
[[requires_function(pthread_mutex_timedlock64)]]
int mtx_timedlock64([[nonnull]] mtx_t *__restrict mutex,
                    [[nonnull]] struct timespec64 const *__restrict time_point) {
	$errno_t error;
	error = pthread_mutex_timedlock64((pthread_mutex_t *)mutex, time_point);
	if likely(!error)
		return thrd_success;
	return thrd_error;
}
%#endif /* __USE_TIME64 */


@@Try to lock the mutex pointed by MUTEX without blocking.
@@If the mutex is free the current threads takes control of
@@it, otherwise it returns immediately
@@s.a. `pthread_mutex_trylock()'
[[decl_include("<bits/crt/threads.h>")]]
[[impl_include("<asm/crt/threads.h>", "<bits/crt/pthreadtypes.h>", "<libc/errno.h>")]]
[[requires_function(pthread_mutex_trylock)]]
int mtx_trylock([[nonnull]] mtx_t *__restrict mutex) {
	$errno_t error;
	error = pthread_mutex_trylock((pthread_mutex_t *)mutex);
	if likely(!error)
		return thrd_success;
@@pp_if defined(thrd_busy) && defined(EBUSY)@@
	if likely(error == EBUSY)
		return thrd_busy;
@@pp_endif@@
	return thrd_error;
}

@@Unlock the mutex pointed by MUTEX.
@@It may potentially awake other threads waiting on this mutex
@@s.a. `pthread_mutex_unlock()'
[[decl_include("<bits/crt/threads.h>")]]
[[impl_include("<asm/crt/threads.h>", "<bits/crt/pthreadtypes.h>")]]
[[requires_function(pthread_mutex_unlock)]]
int mtx_unlock([[nonnull]] mtx_t *__restrict mutex) {
	$errno_t error;
	error = pthread_mutex_unlock((pthread_mutex_t *)mutex);
	if likely(!error)
		return thrd_success;
	return thrd_error;
}

@@Destroy the mutex object pointed by MUTEX
@@s.a. `pthread_mutex_destroy()'
[[decl_include("<bits/crt/threads.h>")]]
void mtx_destroy([[nonnull]] mtx_t *__restrict mutex) = pthread_mutex_destroy;



@@Call function FUNC exactly once, even if invoked from several threads.
@@All calls must be made with the same FLAG object
@@s.a. `pthread_once()'
[[decl_include("<bits/crt/threads.h>"), throws]]
void call_once([[nonnull]] once_flag *__restrict flag,
               [[nonnull]] __once_func_t func) = pthread_once;

%
%
%/* Condition variable functions.  */
%

@@Initialize new condition variable pointed by COND
@@s.a. `pthread_cond_init()'
[[decl_include("<bits/crt/threads.h>")]]
[[impl_include("<asm/crt/threads.h>", "<bits/crt/pthreadtypes.h>")]]
[[requires_function(pthread_cond_init)]]
int cnd_init([[nonnull]] cnd_t *__restrict cond) {
	$errno_t error;
	error = pthread_cond_init((pthread_cond_t *)cond, NULL);
	if likely(!error)
		return thrd_success;
	return thrd_error;
}

@@Unblock one thread that currently waits on condition variable pointed by COND
@@s.a. `pthread_cond_signal()'
[[decl_include("<bits/crt/threads.h>")]]
[[impl_include("<asm/crt/threads.h>", "<bits/crt/pthreadtypes.h>")]]
[[requires_function(pthread_cond_signal)]]
int cnd_signal([[nonnull]] cnd_t *__restrict cond) {
	$errno_t error;
	error = pthread_cond_signal((pthread_cond_t *)cond);
	if likely(!error)
		return thrd_success;
	return thrd_error;
}

@@Unblock all threads currently waiting on condition variable pointed by COND
@@s.a. `pthread_cond_broadcast()'
[[decl_include("<bits/crt/threads.h>")]]
[[impl_include("<asm/crt/threads.h>", "<bits/crt/pthreadtypes.h>")]]
[[requires($has_function(pthread_cond_broadcast))]]
int cnd_broadcast([[nonnull]] cnd_t *__restrict cond) {
	$errno_t error;
	error = pthread_cond_broadcast((pthread_cond_t *)cond);
	if likely(!error)
		return thrd_success;
	return thrd_error;
}

@@Block current thread on the condition variable pointed by COND
@@s.a. `pthread_cond_wait()'
[[cp, decl_include("<bits/crt/threads.h>")]]
[[impl_include("<asm/crt/threads.h>", "<bits/crt/pthreadtypes.h>")]]
[[requires_function(pthread_cond_wait)]]
int cnd_wait([[nonnull]] cnd_t *__restrict cond,
             [[nonnull]] mtx_t *__restrict mutex) {
	$errno_t error;
	error = pthread_cond_wait((pthread_cond_t *)cond,
	                          (pthread_mutex_t *)mutex);
	if likely(!error)
		return thrd_success;
	return thrd_error;
}

@@Block current thread on the condition variable until condition variable
@@pointed by COND is signaled or time pointed by TIME_POINT is reached
@@s.a. `pthread_cond_timedwait()'
[[cp, no_crt_self_import]]
[[if(defined(__USE_TIME_BITS64)), preferred_alias(cnd_timedwait64)]]
[[if(!defined(__USE_TIME_BITS64)), preferred_alias(cnd_timedwait)]]
[[decl_include("<bits/crt/threads.h>", "<bits/timespec.h>")]]
[[impl_include("<asm/crt/threads.h>", "<bits/crt/pthreadtypes.h>")]]
[[requires($has_function(pthread_cond_timedwait))]]
int cnd_timedwait([[nonnull]] cnd_t *__restrict cond,
                  [[nonnull]] mtx_t *__restrict mutex,
                  [[nonnull]] struct timespec const *__restrict time_point) {
	$errno_t error;
	error = pthread_cond_timedwait((pthread_cond_t *)cond,
	                               (pthread_mutex_t *)mutex,
	                               time_point);
	if likely(!error)
		return thrd_success;
	if (error == ETIMEDOUT)
		return thrd_timedout;
	return thrd_error;
}

%#ifdef __USE_TIME64
[[cp, doc_alias("cnd_timedwait"), time64_variant_of(cnd_timedwait)]]
[[decl_include("<bits/crt/threads.h>", "<bits/timespec.h>")]]
[[impl_include("<asm/crt/threads.h>", "<bits/crt/pthreadtypes.h>")]]
[[requires($has_function(pthread_cond_timedwait64))]]
int cnd_timedwait64([[nonnull]] cnd_t *__restrict cond,
                    [[nonnull]] mtx_t *__restrict mutex,
                    [[nonnull]] struct timespec64 const *__restrict time_point) {
	$errno_t error;
	error = pthread_cond_timedwait64((pthread_cond_t *)cond,
	                                 (pthread_mutex_t *)mutex,
	                                 time_point);
	if likely(!error)
		return thrd_success;
	if (error == ETIMEDOUT)
		return thrd_timedout;
	return thrd_error;
}
%#endif /* __USE_TIME64 */

@@Destroy condition variable pointed by cond and free all of its resources
@@s.a. `pthread_cond_destroy()'
void cnd_destroy(cnd_t *cond) = pthread_cond_destroy;

%
%
%/* Thread specific storage functions.  */
%

@@Create new thread-specific storage key and stores it in the object pointed by TSS_ID.
@@If DESTRUCTOR is not NULL, the function will be called when the thread terminates
@@s.a. `pthread_key_create()'
[[decl_include("<bits/crt/threads.h>")]]
[[impl_include("<asm/crt/threads.h>", "<bits/crt/pthreadtypes.h>")]]
[[requires_function(pthread_key_create)]]
int tss_create(tss_t *tss_id, tss_dtor_t destructor) {
	$errno_t error;
	error = pthread_key_create((pthread_key_t *)tss_id, destructor);
	if likely(!error)
		return thrd_success;
	return thrd_error;
}

@@Return the value held in thread-specific storage
@@for the current thread identified by TSS_ID
@@s.a. `pthread_getspecific()'
[[decl_include("<bits/crt/threads.h>")]]
void *tss_get(tss_t tss_id) = pthread_getspecific;

@@Sets the value of the thread-specific storage
@@identified by TSS_ID for the current thread to VAL
@@s.a. `pthread_setspecific()'
[[decl_include("<bits/crt/threads.h>")]]
[[impl_include("<asm/crt/threads.h>", "<bits/crt/pthreadtypes.h>")]]
[[requires_function(pthread_setspecific)]]
int tss_set(tss_t tss_id, void *val) {
	$errno_t error;
	error = pthread_setspecific((pthread_key_t)tss_id, val);
	if likely(!error)
		return thrd_success;
	return thrd_error;
}

@@Destroys the thread-specific storage identified by TSS_ID.
@@The destructor of the TSS will not be called upon thread exit
@@s.a. `pthread_key_delete()'
[[decl_include("<bits/crt/threads.h>")]]
void tss_delete(tss_t tss_id) = pthread_key_delete;


%
%/* NOTE: On true Solaris, this function isn't actually restricted to `__EXTENSIONS__'
% *       as it is here, however this entire header is fully standardized by STD-C, so
% *       in the interest of enforcing a clean namespace, and the fact that I have yet
% *       to see this function anywhere other than Solaris, restrict it to its feature
% *       namespace. */
%#ifdef __USE_SOLARIS
[[ATTR_CONST, decl_include("<hybrid/typecore.h>")]]
[[impl_include("<asm/crt/confname.h>", "<asm/crt/limits.h>")]]
$size_t thr_min_stack() {
@@pp_if !defined(__BUILDING_LIBC) && ($has_function(sysconf) && defined(_SC_THREAD_STACK_MIN))@@
	__LONGPTR_TYPE__ result;
	result = sysconf(_SC_THREAD_STACK_MIN);
	if (result != -1)
		return (size_t)result;
@@pp_endif@@
@@pp_ifdef __PTHREAD_STACK_MIN@@
	return __PTHREAD_STACK_MIN;
@@pp_else@@
	return 8192;
@@pp_endif@@
}

@@Another one of these non-restricted, but solaris-specific functions:
@@This one returns 1 if the calling thread is the main() thread (i.e.
@@the thread that was started by the kernel in order to execute the
@@calling program), and 0 otherwise. Additionally, -1 is returned if
@@the calling thread "hasn't been initialized", or if the caller wasn't
@@created by one of the pthread- or threads-related init functions.
@@Internally, this is the return value if the caller doesn't have a
@@proper pthread-controller attached.
thr_main(*) = pthread_main_np;
%#endif /* __USE_SOLARIS */


%{

#endif /* __CC__ */

__SYSDECL_END

}