/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
%(c_prefix){
/* (>) Standard: ISO C11 (ISO/IEC 9899:2011) */
/* (#) Portability: Cygwin        (/newlib/libc/include/threads.h) */
/* (#) Portability: FreeBSD       (/lib/libstdthreads/threads.h) */
/* (#) Portability: GNU C Library (/sysdeps/[...]/threads.h) */
/* (#) Portability: GNU Hurd      (/usr/include/threads.h) */
/* (#) Portability: Newlib        (/newlib/libc/include/threads.h) */
/* (#) Portability: diet libc     (/include/threads.h) */
/* (#) Portability: libc6         (/include/threads.h) */
/* (#) Portability: musl libc     (/include/threads.h) */
}

%[default:section(".text.crt{|.dos}.sched.threads")]

%[define_replacement(tss_t = __tss_t)]
%[define_replacement(thrd_t = __thrd_t)]
%[define_replacement(tss_dtor_t = __tss_dtor_t)]
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

%[insert:prefix(
#include <features.h>
)]%{

}%[insert:prefix(
#include <hybrid/typecore.h>
)]%{

}%[insert:prefix(
#include <asm/crt/threads.h>
)]%[insert:prefix(
#include <bits/crt/threads.h>
)]%[insert:prefix(
#include <bits/os/timespec.h>
)]%[insert:prefix(
#include <kos/anno.h>
)]%{

__SYSDECL_BEGIN


#ifndef TSS_DTOR_ITERATIONS
#ifdef __TSS_DTOR_ITERATIONS
#define TSS_DTOR_ITERATIONS __TSS_DTOR_ITERATIONS
#else /* __TSS_DTOR_ITERATIONS */
#define TSS_DTOR_ITERATIONS 4
#endif /* !__TSS_DTOR_ITERATIONS */
#endif /* !TSS_DTOR_ITERATIONS */


#if ((!defined(thrd_success) && defined(__thrd_success)) || \
     (!defined(thrd_busy) && defined(__thrd_busy)) ||       \
     (!defined(thrd_error) && defined(__thrd_error)) ||     \
     (!defined(thrd_nomem) && defined(__thrd_nomem)) ||     \
     (!defined(thrd_timedout) && defined(__thrd_timedout)))
/* Exit and error codes.  */
/*[[[enum]]]*/
#ifdef __CC__
enum {
#if !defined(thrd_success) && defined(__thrd_success)
	thrd_success  = __thrd_success,
#endif /* !thrd_success && __thrd_success */
#if !defined(thrd_busy) && defined(__thrd_busy)
	thrd_busy     = __thrd_busy,
#endif /* !thrd_busy && __thrd_busy */
#if !defined(thrd_error) && defined(__thrd_error)
	thrd_error    = __thrd_error,
#endif /* !thrd_error && __thrd_error */
#if !defined(thrd_nomem) && defined(__thrd_nomem)
	thrd_nomem    = __thrd_nomem,
#endif /* !thrd_nomem && __thrd_nomem */
#if !defined(thrd_timedout) && defined(__thrd_timedout)
	thrd_timedout = __thrd_timedout
#endif /* !thrd_timedout && __thrd_timedout */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#if !defined(thrd_success) && defined(__thrd_success)
#define thrd_success  thrd_success
#endif /* !thrd_success && __thrd_success */
#if !defined(thrd_busy) && defined(__thrd_busy)
#define thrd_busy     thrd_busy
#endif /* !thrd_busy && __thrd_busy */
#if !defined(thrd_error) && defined(__thrd_error)
#define thrd_error    thrd_error
#endif /* !thrd_error && __thrd_error */
#if !defined(thrd_nomem) && defined(__thrd_nomem)
#define thrd_nomem    thrd_nomem
#endif /* !thrd_nomem && __thrd_nomem */
#if !defined(thrd_timedout) && defined(__thrd_timedout)
#define thrd_timedout thrd_timedout
#endif /* !thrd_timedout && __thrd_timedout */
#else /* __COMPILER_PREFERR_ENUMS */
#if !defined(thrd_success) && defined(__thrd_success)
#define thrd_success  __thrd_success
#endif /* !thrd_success && __thrd_success */
#if !defined(thrd_busy) && defined(__thrd_busy)
#define thrd_busy     __thrd_busy
#endif /* !thrd_busy && __thrd_busy */
#if !defined(thrd_error) && defined(__thrd_error)
#define thrd_error    __thrd_error
#endif /* !thrd_error && __thrd_error */
#if !defined(thrd_nomem) && defined(__thrd_nomem)
#define thrd_nomem    __thrd_nomem
#endif /* !thrd_nomem && __thrd_nomem */
#if !defined(thrd_timedout) && defined(__thrd_timedout)
#define thrd_timedout __thrd_timedout
#endif /* !thrd_timedout && __thrd_timedout */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/
#endif /* ... */

#if ((!defined(mtx_plain) && defined(__mtx_plain)) ||         \
     (!defined(mtx_recursive) && defined(__mtx_recursive)) || \
     (!defined(mtx_timed) && defined(__mtx_timed)))
/* Mutex types.  */
/*[[[enum]]]*/
#ifdef __CC__
enum {
#if !defined(mtx_plain) && defined(__mtx_plain)
	mtx_plain     = __mtx_plain,
#endif /* !mtx_plain && __mtx_plain */
#if !defined(mtx_recursive) && defined(__mtx_recursive)
	mtx_recursive = __mtx_recursive,
#endif /* !mtx_recursive && __mtx_recursive */
#if !defined(mtx_timed) && defined(__mtx_timed)
	mtx_timed     = __mtx_timed
#endif /* !mtx_timed && __mtx_timed */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#if !defined(mtx_plain) && defined(__mtx_plain)
#define mtx_plain     mtx_plain
#endif /* !mtx_plain && __mtx_plain */
#if !defined(mtx_recursive) && defined(__mtx_recursive)
#define mtx_recursive mtx_recursive
#endif /* !mtx_recursive && __mtx_recursive */
#if !defined(mtx_timed) && defined(__mtx_timed)
#define mtx_timed     mtx_timed
#endif /* !mtx_timed && __mtx_timed */
#else /* __COMPILER_PREFERR_ENUMS */
#if !defined(mtx_plain) && defined(__mtx_plain)
#define mtx_plain     __mtx_plain
#endif /* !mtx_plain && __mtx_plain */
#if !defined(mtx_recursive) && defined(__mtx_recursive)
#define mtx_recursive __mtx_recursive
#endif /* !mtx_recursive && __mtx_recursive */
#if !defined(mtx_timed) && defined(__mtx_timed)
#define mtx_timed     __mtx_timed
#endif /* !mtx_timed && __mtx_timed */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/
#endif /* ... */


#ifdef __CC__

typedef __tss_t tss_t;
typedef __thrd_t thrd_t;
typedef void (__LIBKCALL *tss_dtor_t)(void *__arg); /* TODO: Dos support! */
typedef int (__LIBCCALL *thrd_start_t)(void *__arg);
typedef __once_flag once_flag;
#define ONCE_FLAG_INIT __ONCE_FLAG_INIT
typedef __mtx_t mtx_t;
typedef __cnd_t cnd_t;

}


@@>> thrd_create(3)
@@Create and start a new thread (s.a. `pthread_create(3)')
@@@return: thrd_success: Success
@@@return: thrd_nomem:   Not enough memory
@@@return: thrd_error:   Error
[[decl_include("<bits/crt/threads.h>")]]
[[impl_include("<asm/crt/threads.h>", "<libc/errno.h>")]]
[[requires_function(pthread_create)]]
[[crt_dos_impl_if(!defined(__KERNEL__) && !defined(__LIBCCALL_IS_LIBDCALL))]]
[[crt_dos_variant({
impl: {
	$errno_t error;
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
})]]
int thrd_create([[out]] thrd_t *thr,
                [[nonnull]] int (LIBCCALL *func)(void *arg),
                void *arg) {
	$errno_t error;
	STATIC_ASSERT(sizeof(int) <= sizeof(void *));
	error = pthread_create((pthread_t *)thr, NULL,
	                       (void *(LIBCCALL *)(void *))(void *)func,
	                       arg);
	if likely(!error)
		return thrd_success;
@@pp_if defined(thrd_nomem) && defined(ENOMEM)@@
	if (error == ENOMEM)
		return thrd_nomem;
@@pp_endif@@
	return thrd_error;
}

@@>> thrd_equal(3)
@@Return non-zero if `thr1' and `thr2' reference the same thread (s.a. `pthread_equal(3)')
@@@return: == 0: Threads are not equal
@@@return: != 0: Threads are qual
[[wunused, decl_include("<bits/crt/threads.h>")]]
int thrd_equal(thrd_t thr1, thrd_t thr2) = pthread_equal;

@@>> thrd_current(3)
@@Return the descriptor for the calling thread (s.a. `pthread_self(3)')
[[wunused, decl_include("<bits/crt/threads.h>")]]
thrd_t thrd_current() = pthread_self;

@@>> thrd_sleep(3), thrd_sleep64(3)
@@Sleep until a signal is received, or `time_point' has elapsed (s.a. `nanosleep(2)')
@@@return:     0: The (relative) time specified by `time_point' has elapsed
@@@return:    -1: A signal was received while waiting, and `remaining' was filled in (if given)
@@@return: <= -2: Some other error occurred
[[cp, decl_include("<bits/os/timespec.h>"), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("thrd_sleep")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("thrd_sleep64", "__thrd_sleep64")]]
[[impl_include("<asm/crt/threads.h>", "<libc/errno.h>")]]
[[userimpl, requires($has_function(thrd_sleep32) || $has_function(crt_thrd_sleep64) || $has_function(nanosleep))]]
int thrd_sleep([[in]] struct timespec const *time_point,
               [[out_opt]] struct timespec *remaining) {
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
[[decl_include("<bits/os/timespec.h>")]]
int thrd_sleep32([[in]] struct $timespec32 const *time_point,
                 [[out_opt]] struct $timespec32 *remaining);

[[cp, doc_alias("thrd_sleep"), ignore, nocrt, alias("thrd_sleep64", "__thrd_sleep64")]]
[[decl_include("<bits/os/timespec.h>")]]
int crt_thrd_sleep64([[in]] struct timespec64 const *time_point,
                     [[out_opt]] struct timespec64 *remaining);

[[cp, decl_include("<bits/os/timespec.h>")]]
[[preferred_time64_variant_of(thrd_sleep), doc_alias("thrd_sleep")]]
[[time64_export_alias("__thrd_sleep64")]]
[[userimpl, requires($has_function(thrd_sleep32) || $has_function(nanosleep64))]]
int thrd_sleep64([[in]] struct timespec64 const *time_point,
                 [[out_opt]] struct timespec64 *remaining) {
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

@@>> thrd_exit(3)
@@Terminate the calling thread (s.a. `pthread_exit(3)')
[[noreturn, no_nothrow, requires_function(pthread_exit)]]
void thrd_exit(int res) {
	pthread_exit((void *)(uintptr_t)(unsigned int)res);
}

@@>> thrd_detach(3)
@@Detach the given thread (s.a. `pthread_detach(3)')
@@@return: thrd_success: Success
@@@return: thrd_error:   Error
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

@@>> thrd_join(3)
@@Wait for the given thread to finish (s.a. `pthread_join(3)')
@@@return: thrd_success: Success
@@@return: thrd_error:   Error
[[cp, decl_include("<bits/crt/threads.h>")]]
[[impl_include("<asm/crt/threads.h>")]]
[[requires_function(pthread_join)]]
int thrd_join(thrd_t thr, [[out_opt]] int *res) {
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

@@>> thrd_yield(3)
@@Yield execution to another thread (s.a. `pthread_yield(3)')
[[nothrow]]
void thrd_yield() = pthread_yield;



%
%
%/* Mutex functions.  */
%

@@>> mtx_init(3)
@@Initialize a mutex object (s.a. `pthread_mutex_init(3)')
@@@return: thrd_success: Success
@@@return: thrd_error:   Error
[[decl_include("<features.h>", "<bits/crt/threads.h>")]]
[[impl_include("<asm/crt/threads.h>", "<asm/crt/pthreadvalues.h>", "<bits/crt/pthreadtypes.h>")]]
[[requires_function(pthread_mutex_init)]]
int mtx_init([[out]] mtx_t *__restrict mutex, __STDC_INT_AS_UINT_T type) {
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

@@>> mtx_lock(3)
@@Acquire a lock to a given mutex (s.a. `pthread_mutex_lock(3)')
@@@return: thrd_success: Success
@@@return: thrd_error:   Error
[[cp, decl_include("<bits/crt/threads.h>")]]
[[impl_include("<asm/crt/threads.h>", "<bits/crt/pthreadtypes.h>")]]
[[requires_function(pthread_mutex_lock)]]
int mtx_lock([[inout]] mtx_t *__restrict mutex) {
	$errno_t error;
	error = pthread_mutex_lock((pthread_mutex_t *)mutex);
	if likely(!error)
		return thrd_success;
	return thrd_error;
}

@@>> mtx_timedlock(3), mtx_timedlock64(3)
@@Acquire a lock to a given mutex (s.a. `pthread_mutex_timedlock(3)')
@@@return: thrd_success:  Success
@@@return: thrd_timedout: Timeout
@@@return: thrd_error:    Error
[[cp, no_crt_self_import, decl_include("<bits/crt/threads.h>", "<bits/os/timespec.h>")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("mtx_timedlock")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("mtx_timedlock64", "__mtx_timedlock64")]]
[[impl_include("<asm/crt/threads.h>", "<bits/crt/pthreadtypes.h>", "<asm/os/errno.h>")]]
[[requires_function(pthread_mutex_timedlock)]]
int mtx_timedlock([[inout]] mtx_t *__restrict mutex,
                  [[in]] struct timespec const *__restrict time_point) {
	$errno_t error;
	error = pthread_mutex_timedlock((pthread_mutex_t *)mutex, time_point);
	if likely(!error)
		return thrd_success;
@@pp_ifdef ETIMEDOUT@@
	if (error == ETIMEDOUT)
		return thrd_timedout;
@@pp_endif@@
	return thrd_error;
}

%#ifdef __USE_TIME64
[[cp, decl_include("<bits/crt/threads.h>", "<bits/os/timespec.h>")]]
[[preferred_time64_variant_of(mtx_timedlock), doc_alias("mtx_timedlock")]]
[[time64_export_alias("__mtx_timedlock64")]]
[[impl_include("<asm/crt/threads.h>", "<bits/crt/pthreadtypes.h>", "<asm/os/errno.h>")]]
[[requires_function(pthread_mutex_timedlock64)]]
int mtx_timedlock64([[inout]] mtx_t *__restrict mutex,
                    [[in]] struct timespec64 const *__restrict time_point) {
	$errno_t error;
	error = pthread_mutex_timedlock64((pthread_mutex_t *)mutex, time_point);
	if likely(!error)
		return thrd_success;
@@pp_ifdef ETIMEDOUT@@
	if (error == ETIMEDOUT)
		return thrd_timedout;
@@pp_endif@@
	return thrd_error;
}
%#endif /* __USE_TIME64 */


@@>> mtx_trylock(3)
@@Try to acquire a lock to a given mutex (s.a. `pthread_mutex_trylock(3)')
@@@return: thrd_success: Success
@@@return: thrd_busy:    Cannot lock without blocking right now
@@@return: thrd_error:   Error
[[decl_include("<bits/crt/threads.h>")]]
[[impl_include("<asm/crt/threads.h>", "<bits/crt/pthreadtypes.h>", "<libc/errno.h>")]]
[[requires_function(pthread_mutex_trylock)]]
int mtx_trylock([[inout]] mtx_t *__restrict mutex) {
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

@@>> mtx_unlock(3)
@@Release a lock from a given mutex (s.a. `pthread_mutex_unlock(3)')
@@@return: thrd_success: Success
@@@return: thrd_error:   Error
[[decl_include("<bits/crt/threads.h>")]]
[[impl_include("<asm/crt/threads.h>", "<bits/crt/pthreadtypes.h>")]]
[[requires_function(pthread_mutex_unlock)]]
int mtx_unlock([[inout]] mtx_t *__restrict mutex) {
	$errno_t error;
	error = pthread_mutex_unlock((pthread_mutex_t *)mutex);
	if likely(!error)
		return thrd_success;
	return thrd_error;
}

@@>> mtx_destroy(3)
@@Destroy the given mutex (s.a. `pthread_mutex_destroy(3)')
[[decl_include("<bits/crt/threads.h>")]]
void mtx_destroy([[inout]] mtx_t *__restrict mutex) = pthread_mutex_destroy;



@@>> call_once(3)
@@Invoke `func', but make sure this only happens once (s.a. `pthread_once()')
[[decl_include("<bits/crt/threads.h>"), nothrow_cb]]
void call_once([[inout]] once_flag *__restrict flag,
               [[nonnull]] void (LIBCCALL *func)(void)) = pthread_once;

%
%
%/* Condition variable functions.  */
%

@@>> cnd_init(3)
@@Initialize the given condition variable (s.a. `pthread_cond_init(3)')
@@@return: thrd_success: Success
@@@return: thrd_error:   Error
[[decl_include("<bits/crt/threads.h>")]]
[[impl_include("<asm/crt/threads.h>", "<bits/crt/pthreadtypes.h>")]]
[[requires_function(pthread_cond_init)]]
int cnd_init([[out]] cnd_t *__restrict cond) {
	$errno_t error;
	error = pthread_cond_init((pthread_cond_t *)cond, NULL);
	if likely(!error)
		return thrd_success;
	return thrd_error;
}

@@>> cnd_signal(3)
@@Wakeup  one thread currently  waiting on the given
@@condition variable (s.a. `pthread_cond_signal(3)')
@@@return: thrd_success: Success
@@@return: thrd_error:   Error
[[decl_include("<bits/crt/threads.h>")]]
[[impl_include("<asm/crt/threads.h>", "<bits/crt/pthreadtypes.h>")]]
[[requires_function(pthread_cond_signal)]]
int cnd_signal([[inout]] cnd_t *__restrict cond) {
	$errno_t error;
	error = pthread_cond_signal((pthread_cond_t *)cond);
	if likely(!error)
		return thrd_success;
	return thrd_error;
}

@@>> cnd_broadcast(3)
@@Wakeup  all  threads currently  waiting on  the given
@@condition variable (s.a. `pthread_cond_broadcast(3)')
@@@return: thrd_success: Success
@@@return: thrd_error:   Error
[[decl_include("<bits/crt/threads.h>")]]
[[impl_include("<asm/crt/threads.h>", "<bits/crt/pthreadtypes.h>")]]
[[requires($has_function(pthread_cond_broadcast))]]
int cnd_broadcast([[inout]] cnd_t *__restrict cond) {
	$errno_t error;
	error = pthread_cond_broadcast((pthread_cond_t *)cond);
	if likely(!error)
		return thrd_success;
	return thrd_error;
}

@@>> cnd_wait(3)
@@Wait on the given condition variable (s.a. `pthread_cond_wait(3)')
@@@return: thrd_success: Success
@@@return: thrd_error:   Error
[[cp, decl_include("<bits/crt/threads.h>")]]
[[impl_include("<asm/crt/threads.h>", "<bits/crt/pthreadtypes.h>")]]
[[requires_function(pthread_cond_wait)]]
int cnd_wait([[inout]] cnd_t *__restrict cond,
             [[inout]] mtx_t *__restrict mutex) {
	$errno_t error;
	error = pthread_cond_wait((pthread_cond_t *)cond,
	                          (pthread_mutex_t *)mutex);
	if likely(!error)
		return thrd_success;
	return thrd_error;
}

@@>> cnd_timedwait(3), cnd_timedwait64(3)
@@Wait on the given condition variable (s.a. `pthread_cond_timedwait(3)')
@@@return: thrd_success:  Success
@@@return: thrd_timedout: Timeout
@@@return: thrd_error:    Error
[[cp, decl_include("<bits/crt/threads.h>", "<bits/os/timespec.h>"), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("cnd_timedwait")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("cnd_timedwait64", "__cnd_timedwait64")]]
[[impl_include("<asm/crt/threads.h>", "<bits/crt/pthreadtypes.h>", "<asm/os/errno.h>")]]
[[requires_function(pthread_cond_timedwait)]]
int cnd_timedwait([[inout]] cnd_t *__restrict cond,
                  [[inout]] mtx_t *__restrict mutex,
                  [[in]] struct timespec const *__restrict time_point) {
	$errno_t error;
	error = pthread_cond_timedwait((pthread_cond_t *)cond,
	                               (pthread_mutex_t *)mutex,
	                               time_point);
	if likely(!error)
		return thrd_success;
@@pp_ifdef ETIMEDOUT@@
	if (error == ETIMEDOUT)
		return thrd_timedout;
@@pp_endif@@
	return thrd_error;
}

%#ifdef __USE_TIME64
[[cp, decl_include("<bits/crt/threads.h>", "<bits/os/timespec.h>")]]
[[time64_export_alias("__cnd_timedwait64")]]
[[preferred_time64_variant_of(cnd_timedwait), doc_alias("cnd_timedwait")]]
[[impl_include("<asm/crt/threads.h>", "<bits/crt/pthreadtypes.h>", "<asm/os/errno.h>")]]
[[requires_function(pthread_cond_timedwait64)]]
int cnd_timedwait64([[inout]] cnd_t *__restrict cond,
                    [[inout]] mtx_t *__restrict mutex,
                    [[in]] struct timespec64 const *__restrict time_point) {
	$errno_t error;
	error = pthread_cond_timedwait64((pthread_cond_t *)cond,
	                                 (pthread_mutex_t *)mutex,
	                                 time_point);
	if likely(!error)
		return thrd_success;
@@pp_ifdef ETIMEDOUT@@
	if (error == ETIMEDOUT)
		return thrd_timedout;
@@pp_endif@@
	return thrd_error;
}
%#endif /* __USE_TIME64 */

@@Destroy condition variable pointed by cond and free all of its resources
@@s.a. `pthread_cond_destroy()'
void cnd_destroy([[inout]] cnd_t *cond) = pthread_cond_destroy;

%
%
%/* Thread specific storage functions.  */
%

@@>> tss_create(3)
@@Create a new TLS key (s.a. `pthread_key_create(3)')
@@@return: thrd_success: Success
@@@return: thrd_error:   Error
[[decl_include("<bits/crt/threads.h>")]]
[[impl_include("<asm/crt/threads.h>", "<bits/crt/pthreadtypes.h>")]]
[[requires_function(pthread_key_create)]] /* TODO: Dos support! */
int tss_create([[out]] tss_t *tss_id,
               [[nullable]] void (LIBKCALL *destructor)(void *arg)) {
	$errno_t error;
	error = pthread_key_create((pthread_key_t *)tss_id, destructor);
	if likely(!error)
		return thrd_success;
	return thrd_error;
}

@@>> tss_get(3)
@@Return the calling thread's value for the given TLS key (s.a. `pthread_getspecific(3)')
@@@return: * : The calling thread's value of the given TLS variable
[[decl_include("<bits/crt/threads.h>")]]
void *tss_get(tss_t tss_id) = pthread_getspecific;

@@>> tss_set(3)
@@Set the calling thread's value for the given TLS key (s.a. `pthread_setspecific(3)')
@@@return: thrd_success: Success
@@@return: thrd_error:   Error
[[decl_include("<bits/crt/threads.h>")]]
[[impl_include("<asm/crt/threads.h>", "<bits/crt/pthreadtypes.h>")]]
[[requires_function(pthread_setspecific)]]
int tss_set(tss_t tss_id, [[access(none)]] void *val) {
	$errno_t error;
	error = pthread_setspecific((pthread_key_t)tss_id, val);
	if likely(!error)
		return thrd_success;
	return thrd_error;
}

@@>> tss_delete(3)
@@Destroys the given TLS key (s.a. `pthread_key_delete(3)')
[[decl_include("<bits/crt/threads.h>")]]
void tss_delete(tss_t tss_id) = pthread_key_delete;


%
%{
/* NOTE: On true Solaris, this function isn't actually restricted to `__EXTENSIONS__'
 *       as it is here, however this entire header is fully standardized by STD-C, so
 *       in the interest of enforcing a clean namespace, and the fact that I have yet
 *       to see this function anywhere other than Solaris, restrict it to its feature
 *       namespace. */
}
%#ifdef __USE_SOLARIS
@@>> thr_min_stack(3)
[[guard, wunused, const, nothrow, decl_include("<hybrid/typecore.h>")]]
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

@@>> thr_main(3)
@@Another  one of these non-restricted, but solaris-specific functions:
@@This  one returns 1 if the calling  thread is the main() thread (i.e.
@@the thread that  was started by  the kernel in  order to execute  the
@@calling program), and  0 otherwise. Additionally,  -1 is returned  if
@@the calling thread "hasn't been initialized", or if the caller wasn't
@@created  by one  of the  pthread- or  threads-related init functions.
@@Internally,  this is  the return value  if the caller  doesn't have a
@@proper pthread-controller attached.
[[guard]]
thr_main(*) = pthread_main_np;
%#endif /* __USE_SOLARIS */


%{

#endif /* __CC__ */

__SYSDECL_END

}
