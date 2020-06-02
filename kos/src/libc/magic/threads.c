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

%[default_impl_section(.text.crt.sched.threads)]

%[define_replacement(tss_t = __tss_t)]
%[define_replacement(thrd_t = __thrd_t)]
%[define_replacement(tss_dtor_t = __tss_dtor_t)]
%[define_replacement(thrd_start_t = __thrd_start_t)]
%[define_replacement(once_flag = __once_flag)]
%[define_replacement(ONCE_FLAG_INIT = __ONCE_FLAG_INIT)]
%[define_replacement(mtx_t = __mtx_t)]
%[define_replacement(cnd_t = __cnd_t)]
%[define_replacement(STATIC_ASSERT = __STATIC_ASSERT)]

%[define_replacement(thrd_success  = __thrd_success)]
%[define_replacement(thrd_busy     = __thrd_busy)]
%[define_replacement(thrd_error    = __thrd_error)]
%[define_replacement(thrd_nomem    = __thrd_nomem)]
%[define_replacement(thrd_timedout = __thrd_timedout)]

%[define_replacement(mtx_plain     = __mtx_plain)]
%[define_replacement(mtx_recursive = __mtx_recursive)]
%[define_replacement(mtx_timed     = __mtx_timed)]


%{
#include <features.h>

#include <hybrid/typecore.h>

#include <asm/threads.h>
#include <bits/threads.h>
#include <bits/timespec.h>

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

/* Exit and error codes.  */
/*[[[enum]]]*/
#ifdef __CC__
enum {
	thrd_success  = __thrd_success,
	thrd_busy     = __thrd_busy,
	thrd_error    = __thrd_error,
	thrd_nomem    = __thrd_nomem,
	thrd_timedout = __thrd_timedout
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#define thrd_success  thrd_success
#define thrd_busy     thrd_busy
#define thrd_error    thrd_error
#define thrd_nomem    thrd_nomem
#define thrd_timedout thrd_timedout
#else /* __COMPILER_PREFERR_ENUMS */
#define thrd_success  __thrd_success
#define thrd_busy     __thrd_busy
#define thrd_error    __thrd_error
#define thrd_nomem    __thrd_nomem
#define thrd_timedout __thrd_timedout
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/

/* Mutex types.  */
/*[[[enum]]]*/
#ifdef __CC__
enum {
	mtx_plain     = __mtx_plain,
	mtx_recursive = __mtx_recursive,
	mtx_timed     = __mtx_timed
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#define mtx_plain     mtx_plain
#define mtx_recursive mtx_recursive
#define mtx_timed     mtx_timed
#else /* __COMPILER_PREFERR_ENUMS */
#define mtx_plain     __mtx_plain
#define mtx_recursive __mtx_recursive
#define mtx_timed     __mtx_timed
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/


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
[same_impl][requires($has_function(pthread_create))]
[dependency_include(<asm/threads.h>)]
[dependency_include(<parts/errno.h>)]
[decl_include(<bits/threads.h>)]
thrd_create:(thrd_t *thr, thrd_start_t func, void *arg) -> int {
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

@@Check if __LHS and __RHS point to the same thread
@@s.a. `pthread_equal()'
[decl_include(<bits/threads.h>)]
thrd_equal:(thrd_t lhs, thrd_t rhs) -> int = pthread_equal;

@@Return current thread identifier
@@s.a. `pthread_self()'
[decl_include(<bits/threads.h>)]
thrd_current:() -> thrd_t = pthread_self;

@@Block current thread execution for at least the (relative) time pointed by TIME_POINT.
@@The current thread may resume if receives a signal. In that case, if REMAINING
@@is not NULL, the remaining time is stored in the object pointed by it
@@@return:     0: The (relative) time specified by `time_point' has elapsed
@@@return:    -1: A signal was received while waiting, and `remaining' was filled in (if given)
@@@return: <= -2: Some other error occurred
[if(defined(__USE_TIME_BITS64)), preferred_alias(thrd_sleep64)]
[if(!defined(__USE_TIME_BITS64)), preferred_alias(thrd_sleep)]
[requires($has_function(thrd_sleep32) || $has_function(crt_thrd_sleep64) || $has_function(nanosleep))]
[dependency_include(<asm/threads.h>)]
[dependency_include(<parts/errno.h>)]
[decl_include(<bits/timespec.h>)][cp]
thrd_sleep:([nonnull] struct timespec const *time_point,
            [nullable] struct timespec *remaining) -> int {
@@if_has_function(thrd_sleep32)@@
	int result;
	struct timespec32 tp32, rem32;
	tp32.@tv_sec@  = (time32_t)time_point->@tv_sec@;
	tp32.@tv_nsec@ = time_point->@tv_nsec@;
	result = thrd_sleep32(&tp32, remaining ? &rem32 : NULL);
	if (result == -1 && remaining) {
		remaining->@tv_sec@ = (time64_t)rem32.@tv_sec@;
		remaining->@tv_nsec@ = rem32.@tv_nsec@;
	}
	return result;
@@elif_has_function(crt_thrd_sleep64)@@
	int result;
	struct timespec64 tp64, rem64;
	tp64.@tv_sec@  = (time64_t)time_point->@tv_sec@;
	tp64.@tv_nsec@ = time_point->@tv_nsec@;
	result = crt_thrd_sleep64(&tp64, remaining ? &rem64 : NULL);
	if (result == -1 && remaining) {
		remaining->@tv_sec@ = (time32_t)rem64.@tv_sec@;
		remaining->@tv_nsec@ = rem64.@tv_nsec@;
	}
	return result;
@@else_has_function(crt_thrd_sleep64)@@
	int error;
	error = nanosleep(time_point, remaining);
	if likely(error == 0)
		return 0;
#if defined(__libc_geterrno) && defined(EINTR)
	if (__libc_geterrno() == EINTR)
		return -1;
#endif /* __libc_geterrno && EINTR */
	return -2;
@@endif_has_function(crt_thrd_sleep64)@@
}

%#ifdef __USE_TIME64
[ignore][doc_alias(thrd_sleep)]
[decl_include(<bits/timespec.h>)][cp]
thrd_sleep32:([nonnull] struct $timespec32 const *time_point,
              [nullable] struct $timespec32 *remaining) -> int = thrd_sleep?;
[ignore][doc_alias(thrd_sleep)]
[decl_include(<bits/timespec.h>)][cp]
crt_thrd_sleep64:([nonnull] struct timespec64 const *time_point,
                  [nullable] struct timespec64 *remaining) -> int = thrd_sleep64?;

[doc_alias(thrd_sleep)]
[requires($has_function(thrd_sleep32) || $has_function(nanosleep64))]
[decl_include(<bits/timespec.h>)][cp][time64_variant_of(thrd_sleep)]
thrd_sleep64:([nonnull] struct timespec64 const *time_point,
              [nullable] struct timespec64 *remaining) -> int {
@@if_has_function(nanosleep64)@@
	int error;
	error = nanosleep64(time_point, remaining);
	if likely(error == 0)
		return 0;
#if defined(__libc_geterrno) && defined(EINTR)
	if (__libc_geterrno() == EINTR)
		return -1;
#endif /* __libc_geterrno && EINTR */
	return -2;
@@else_has_function(nanosleep64)@@
	int result;
	struct timespec32 tp32;
	struct timespec32 rem32;
	tp32.@tv_sec@  = (time32_t)time_point->@tv_sec@;
	tp32.@tv_nsec@ = time_point->@tv_nsec@;
	result = thrd_sleep32(&tp32, remaining ? &rem32 : NULL);
	if (result == -1 && remaining) {
		remaining->@tv_sec@ = (time64_t)rem32.@tv_sec@;
		remaining->@tv_nsec@ = rem32.@tv_nsec@;
	}
	return result;
@@endif_has_function(nanosleep64)@@
}
%#endif /* __USE_TIME64 */

@@Terminate current thread execution, cleaning up any thread local
@@storage and freeing resources. Returns the value specified in RES
@@s.a. `pthread_exit()'
[throws()][ATTR_NORETURN][same_impl][requires($has_function(pthread_exit))]
thrd_exit:(int res) {
	pthread_exit((void *)(uintptr_t)(unsigned int)res);
}

@@Detach the thread identified by THR from the current
@@environment (it does not allow join or wait for it)
@@s.a. `pthread_detach()'
[dependency_include(<asm/threads.h>)]
[decl_include(<bits/threads.h>)]
[same_impl][requires($has_function(pthread_detach))]
thrd_detach:(thrd_t thr) -> int {
	int error;
	error = pthread_detach((pthread_t)thr);
	if likely(!error)
		return thrd_success;
	return thrd_error;
}

@@Block current thread until execution of THR is complete.
@@In case that RES is not NULL, will store the return value of THR when exiting
@@s.a. `pthread_join()'
[dependency_include(<asm/threads.h>)]
[decl_include(<hybrid/typecore.h>)]
[decl_include(<bits/threads.h>)][cp]
[same_impl][requires($has_function(pthread_join))]
thrd_join:(thrd_t thr, int *res) -> int {
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
#endif /* __SIZEOF_POINTER__ == __SIZEOF_INT__ */
	return thrd_error;
}

@@Stop current thread execution and call the scheduler to decide which
@@thread should execute next. The current thread may be selected by the
@@scheduler to keep running
@@s.a. `pthread_yield()'
[alias(sched_yield)] thrd_yield:() = pthread_yield;



%
%
%/* Mutex functions.  */
%

@@Creates a new mutex object with type TYPE.
@@If successful the new object is pointed by MUTEX
@@s.a. `pthread_mutex_init()'
[dependency_include(<asm/threads.h>)]
[decl_include(<bits/threads.h>)]
[decl_include(<bits/pthreadvalues.h>)]
[decl_include(<bits/pthreadtypes.h>)]
[same_impl][requires($has_function(pthread_mutex_init))]
mtx_init:([nonnull] mtx_t *__restrict mutex, int type) -> int {
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

@@Block the current thread until the mutex pointed to by MUTEX is
@@unlocked.  In that case current thread will not be blocked
@@s.a. `pthread_mutex_lock()'
[dependency_include(<asm/threads.h>)]
[decl_include(<bits/threads.h>)][cp]
[decl_include(<bits/pthreadtypes.h>)]
[same_impl][requires($has_function(pthread_mutex_lock))]
mtx_lock:([nonnull] mtx_t *__restrict mutex) -> int {
	int error;
	error = pthread_mutex_lock((pthread_mutex_t *)mutex);
	if likely(!error)
		return thrd_success;
	return thrd_error;
}

@@Block the current thread until the mutex pointed by MUTEX
@@is unlocked or time pointed by TIME_POINT is reached.
@@In case the mutex is unlock, the current thread will not be blocked
@@s.a. `pthread_mutex_timedlock()'
[if(defined(__USE_TIME_BITS64)), preferred_alias(mtx_timedlock64)]
[if(!defined(__USE_TIME_BITS64)), preferred_alias(mtx_timedlock)]
[dependency_include(<asm/threads.h>)]
[decl_include(<bits/threads.h>)][cp]
[decl_include(<bits/pthreadtypes.h>)]
[same_impl][requires($has_function(pthread_mutex_timedlock))]
mtx_timedlock:([nonnull] mtx_t *__restrict mutex,
               [nonnull] struct timespec const *__restrict time_point) -> int {
	int error;
	error = pthread_mutex_timedlock((pthread_mutex_t *)mutex, time_point);
	if likely(!error)
		return thrd_success;
	return thrd_error;
}

%#ifdef __USE_TIME64
[time64_variant_of(mtx_timedlock)]
[dependency_include(<asm/threads.h>)]
[decl_include(<bits/threads.h>)][cp]
[decl_include(<bits/pthreadtypes.h>)]
[same_impl][requires($has_function(pthread_mutex_timedlock64))]
mtx_timedlock64:([nonnull] mtx_t *__restrict mutex,
                 [nonnull] struct timespec64 const *__restrict time_point) -> int {
	int error;
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
[dependency_include(<asm/threads.h>)]
[decl_include(<bits/threads.h>)]
[decl_include(<bits/pthreadtypes.h>)]
[same_impl][requires($has_function(pthread_mutex_trylock))]
mtx_trylock:([nonnull] mtx_t *__restrict mutex) -> int {
	int error;
	error = pthread_mutex_trylock((pthread_mutex_t *)mutex);
	if likely(!error)
		return thrd_success;
	return thrd_error;
}

@@Unlock the mutex pointed by MUTEX.
@@It may potentially awake other threads waiting on this mutex
@@s.a. `pthread_mutex_unlock()'
[dependency_include(<asm/threads.h>)]
[decl_include(<bits/threads.h>)]
[decl_include(<bits/pthreadtypes.h>)]
[same_impl][requires($has_function(pthread_mutex_unlock))]
mtx_unlock:([nonnull] mtx_t *__restrict mutex) -> int {
	int error;
	error = pthread_mutex_unlock((pthread_mutex_t *)mutex);
	if likely(!error)
		return thrd_success;
	return thrd_error;
}

@@Destroy the mutex object pointed by MUTEX
@@s.a. `pthread_mutex_destroy()'
[decl_include(<bits/threads.h>)]
mtx_destroy:([nonnull] mtx_t *__restrict mutex) = pthread_mutex_destroy;



@@Call function FUNC exactly once, even if invoked from several threads.
@@All calls must be made with the same FLAG object
@@s.a. `pthread_once()'
[decl_include(<bits/threads.h>)][throws]
call_once:([nonnull] once_flag *__restrict flag,
           [nonnull] __once_func_t func) = pthread_once;

%
%
%/* Condition variable functions.  */
%

@@Initialize new condition variable pointed by COND
@@s.a. `pthread_cond_init()'
[dependency_include(<asm/threads.h>)]
[decl_include(<bits/threads.h>)]
[decl_include(<bits/pthreadtypes.h>)]
[same_impl][requires($has_function(pthread_cond_init))]
cnd_init:([nonnull] cnd_t *__restrict cond) -> int {
	int error;
	error = pthread_cond_init((pthread_cond_t *)cond, NULL);
	if likely(!error)
		return thrd_success;
	return thrd_error;
}

@@Unblock one thread that currently waits on condition variable pointed by COND
@@s.a. `pthread_cond_signal()'
[dependency_include(<asm/threads.h>)]
[decl_include(<bits/threads.h>)]
[decl_include(<bits/pthreadtypes.h>)]
[same_impl][requires($has_function(pthread_cond_signal))]
cnd_signal:([nonnull] cnd_t *__restrict cond) -> int {
	int error;
	error = pthread_cond_signal((pthread_cond_t *)cond);
	if likely(!error)
		return thrd_success;
	return thrd_error;
}

@@Unblock all threads currently waiting on condition variable pointed by COND
@@s.a. `pthread_cond_broadcast()'
[dependency_include(<asm/threads.h>)]
[decl_include(<bits/threads.h>)]
[decl_include(<bits/pthreadtypes.h>)]
[same_impl][requires($has_function(pthread_cond_broadcast))]
cnd_broadcast:([nonnull] cnd_t *__restrict cond) -> int {
	int error;
	error = pthread_cond_broadcast((pthread_cond_t *)cond);
	if likely(!error)
		return thrd_success;
	return thrd_error;
}

@@Block current thread on the condition variable pointed by COND
@@s.a. `pthread_cond_wait()'
[dependency_include(<asm/threads.h>)]
[decl_include(<bits/threads.h>)]
[decl_include(<bits/pthreadtypes.h>)]
[same_impl][requires($has_function(pthread_cond_wait))][cp]
cnd_wait:([nonnull] cnd_t *__restrict cond,
          [nonnull] mtx_t *__restrict mutex) -> int {
	int error;
	error = pthread_cond_wait((pthread_cond_t *)cond,
	                          (pthread_mutex_t *)mutex);
	if likely(!error)
		return thrd_success;
	return thrd_error;
}

@@Block current thread on the condition variable until condition variable
@@pointed by COND is signaled or time pointed by TIME_POINT is reached
@@s.a. `pthread_cond_timedwait()'
[if(defined(__USE_TIME_BITS64)), preferred_alias(cnd_timedwait64)]
[if(!defined(__USE_TIME_BITS64)), preferred_alias(cnd_timedwait)]
[dependency_include(<asm/threads.h>)]
[decl_include(<bits/threads.h>)][cp]
[decl_include(<bits/pthreadtypes.h>)]
[decl_include(<bits/timespec.h>)]
[same_impl][requires($has_function(pthread_cond_timedwait))]
cnd_timedwait:([nonnull] cnd_t *__restrict cond,
               [nonnull] mtx_t *__restrict mutex,
               [nonnull] struct timespec const *__restrict time_point) -> int {
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

%#ifdef __USE_TIME64
[time64_variant_of(cnd_timedwait)]
[dependency_include(<asm/threads.h>)]
[decl_include(<bits/threads.h>)][cp]
[decl_include(<bits/pthreadtypes.h>)]
[decl_include(<bits/timespec.h>)]
[same_impl][requires($has_function(pthread_cond_timedwait))]
cnd_timedwait64:([nonnull] cnd_t *__restrict cond,
                 [nonnull] mtx_t *__restrict mutex,
                 [nonnull] struct timespec64 const *__restrict time_point) -> int {
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
%#endif /* __USE_TIME64 */

@@Destroy condition variable pointed by cond and free all of its resources
@@s.a. `pthread_cond_destroy()'
cnd_destroy:(cnd_t *COND) = pthread_cond_destroy;

%
%
%/* Thread specific storage functions.  */
%

@@Create new thread-specific storage key and stores it in the object pointed by TSS_ID.
@@If DESTRUCTOR is not NULL, the function will be called when the thread terminates
@@s.a. `pthread_key_create()'
[dependency_include(<asm/threads.h>)]
[decl_include(<bits/threads.h>)]
[decl_include(<bits/pthreadtypes.h>)]
[same_impl][requires($has_function(pthread_key_create))]
tss_create:(tss_t *tss_id, tss_dtor_t destructor) -> int {
	int error;
	error = pthread_key_create((pthread_key_t *)tss_id, destructor);
	if likely(!error)
		return thrd_success;
	return thrd_error;
}

@@Return the value held in thread-specific storage
@@for the current thread identified by TSS_ID
@@s.a. `pthread_getspecific()'
[decl_include(<bits/threads.h>)]
tss_get:(tss_t tss_id) -> void * = pthread_getspecific;

@@Sets the value of the thread-specific storage
@@identified by TSS_ID for the current thread to VAL
@@s.a. `pthread_setspecific()'
[dependency_include(<asm/threads.h>)]
[decl_include(<bits/threads.h>)]
[decl_include(<bits/pthreadtypes.h>)]
[same_impl][requires($has_function(pthread_setspecific))]
tss_set:(tss_t tss_id, void *val) -> int {
	int error;
	error = pthread_setspecific((pthread_key_t)tss_id, val);
	if likely(!error)
		return thrd_success;
	return thrd_error;
}

@@Destroys the thread-specific storage identified by TSS_ID.
@@The destructor of the TSS will not be called upon thread exit
@@s.a. `pthread_key_delete()'
[decl_include(<bits/threads.h>)]
tss_delete:(tss_t tss_id) = pthread_key_delete;


%{

#endif /* __CC__ */

__SYSDECL_END

}