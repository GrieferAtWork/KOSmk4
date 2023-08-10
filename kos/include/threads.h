/* HASH CRC-32:0x2ad7e8a */
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
/* (>) Standard: ISO C11 (ISO/IEC 9899:2011) */
/* (#) Portability: Cygwin        (/newlib/libc/include/threads.h) */
/* (#) Portability: FreeBSD       (/lib/libstdthreads/threads.h) */
/* (#) Portability: GNU C Library (/sysdeps/[...]/threads.h) */
/* (#) Portability: GNU Hurd      (/usr/include/threads.h) */
/* (#) Portability: Newlib        (/newlib/libc/include/threads.h) */
/* (#) Portability: diet libc     (/include/threads.h) */
/* (#) Portability: libc6         (/include/threads.h) */
/* (#) Portability: musl libc     (/include/threads.h) */
#ifndef _THREADS_H
#define _THREADS_H 1

#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>

#include <hybrid/typecore.h>

#include <asm/crt/threads.h>
#include <bits/crt/threads.h>
#include <bits/os/timespec.h>
#include <kos/anno.h>

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

#ifdef __CRT_HAVE_thrd_create
/* >> thrd_create(3)
 * Create and start a new thread (s.a. `pthread_create(3)')
 * @return: thrd_success: Success
 * @return: thrd_nomem:   Not enough memory
 * @return: thrd_error:   Error */
__CDECLARE(__ATTR_OUT(1) __ATTR_NONNULL((2)),int,__NOTHROW_NCX,thrd_create,(thrd_t *__thr, int (__LIBCCALL *__func)(void *__arg), void *__arg),(__thr,__func,__arg))
#elif defined(__CRT_HAVE_pthread_create)
#include <libc/local/threads/thrd_create.h>
/* >> thrd_create(3)
 * Create and start a new thread (s.a. `pthread_create(3)')
 * @return: thrd_success: Success
 * @return: thrd_nomem:   Not enough memory
 * @return: thrd_error:   Error */
__NAMESPACE_LOCAL_USING_OR_IMPL(thrd_create, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_OUT(1) __ATTR_NONNULL((2)) int __NOTHROW_NCX(__LIBCCALL thrd_create)(thrd_t *__thr, int (__LIBCCALL *__func)(void *__arg), void *__arg) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(thrd_create))(__thr, __func, __arg); })
#endif /* ... */
#ifdef __CRT_HAVE_pthread_equal
/* >> thrd_equal(3)
 * Return non-zero if `thr1' and `thr2' reference the same thread (s.a. `pthread_equal(3)')
 * @return: == 0: Threads are not equal
 * @return: != 0: Threads are qual */
__CEIREDIRECT(__ATTR_WUNUSED,int,__NOTHROW_NCX,thrd_equal,(thrd_t __thr1, thrd_t __thr2),pthread_equal,{ return __thr1 == __thr2; })
#elif defined(__CRT_HAVE_thrd_equal)
/* >> thrd_equal(3)
 * Return non-zero if `thr1' and `thr2' reference the same thread (s.a. `pthread_equal(3)')
 * @return: == 0: Threads are not equal
 * @return: != 0: Threads are qual */
__CEIDECLARE(__ATTR_WUNUSED,int,__NOTHROW_NCX,thrd_equal,(thrd_t __thr1, thrd_t __thr2),{ return __thr1 == __thr2; })
#else /* ... */
/* >> thrd_equal(3)
 * Return non-zero if `thr1' and `thr2' reference the same thread (s.a. `pthread_equal(3)')
 * @return: == 0: Threads are not equal
 * @return: != 0: Threads are qual */
__LOCAL __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL thrd_equal)(thrd_t __thr1, thrd_t __thr2) { return __thr1 == __thr2; }
#endif /* !... */
#ifdef __CRT_HAVE_pthread_self
/* >> thrd_current(3)
 * Return the descriptor for the calling thread (s.a. `pthread_self(3)') */
__CREDIRECT(__ATTR_WUNUSED,thrd_t,__NOTHROW_NCX,thrd_current,(void),pthread_self,())
#elif defined(__CRT_HAVE_thrd_current)
/* >> thrd_current(3)
 * Return the descriptor for the calling thread (s.a. `pthread_self(3)') */
__CDECLARE(__ATTR_WUNUSED,thrd_t,__NOTHROW_NCX,thrd_current,(void),())
#elif defined(__CRT_HAVE_thr_self)
/* >> thrd_current(3)
 * Return the descriptor for the calling thread (s.a. `pthread_self(3)') */
__CREDIRECT(__ATTR_WUNUSED,thrd_t,__NOTHROW_NCX,thrd_current,(void),thr_self,())
#elif defined(__CRT_HAVE_cthread_self)
/* >> thrd_current(3)
 * Return the descriptor for the calling thread (s.a. `pthread_self(3)') */
__CREDIRECT(__ATTR_WUNUSED,thrd_t,__NOTHROW_NCX,thrd_current,(void),cthread_self,())
#endif /* ... */
#include <bits/types.h>
#if defined(__CRT_HAVE_thrd_sleep) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> thrd_sleep(3), thrd_sleep64(3)
 * Sleep until a signal is received, or `time_point' has elapsed (s.a. `nanosleep(2)')
 * @return:     0: The (relative) time specified by `time_point' has elapsed
 * @return:    -1: A signal was received while waiting, and `remaining' was filled in (if given)
 * @return: <= -2: Some other error occurred */
__CDECLARE(__ATTR_IN(1) __ATTR_OUT_OPT(2),int,__NOTHROW_RPC,thrd_sleep,(struct timespec const *__time_point, struct timespec *__remaining),(__time_point,__remaining))
#elif defined(__CRT_HAVE_thrd_sleep64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> thrd_sleep(3), thrd_sleep64(3)
 * Sleep until a signal is received, or `time_point' has elapsed (s.a. `nanosleep(2)')
 * @return:     0: The (relative) time specified by `time_point' has elapsed
 * @return:    -1: A signal was received while waiting, and `remaining' was filled in (if given)
 * @return: <= -2: Some other error occurred */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),int,__NOTHROW_RPC,thrd_sleep,(struct timespec const *__time_point, struct timespec *__remaining),thrd_sleep64,(__time_point,__remaining))
#elif defined(__CRT_HAVE_thrd_sleep) || defined(__CRT_HAVE_thrd_sleep64) || defined(__CRT_HAVE_nanosleep64) || defined(__CRT_HAVE_nanosleep) || defined(__CRT_HAVE___nanosleep) || defined(__CRT_HAVE___libc_nanosleep)
#include <libc/local/threads/thrd_sleep.h>
/* >> thrd_sleep(3), thrd_sleep64(3)
 * Sleep until a signal is received, or `time_point' has elapsed (s.a. `nanosleep(2)')
 * @return:     0: The (relative) time specified by `time_point' has elapsed
 * @return:    -1: A signal was received while waiting, and `remaining' was filled in (if given)
 * @return: <= -2: Some other error occurred */
__NAMESPACE_LOCAL_USING_OR_IMPL(thrd_sleep, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_OUT_OPT(2) int __NOTHROW_RPC(__LIBCCALL thrd_sleep)(struct timespec const *__time_point, struct timespec *__remaining) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(thrd_sleep))(__time_point, __remaining); })
#endif /* ... */
#ifdef __USE_TIME64
#if defined(__CRT_HAVE_thrd_sleep) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> thrd_sleep(3), thrd_sleep64(3)
 * Sleep until a signal is received, or `time_point' has elapsed (s.a. `nanosleep(2)')
 * @return:     0: The (relative) time specified by `time_point' has elapsed
 * @return:    -1: A signal was received while waiting, and `remaining' was filled in (if given)
 * @return: <= -2: Some other error occurred */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),int,__NOTHROW_RPC,thrd_sleep64,(struct timespec64 const *__time_point, struct timespec64 *__remaining),thrd_sleep,(__time_point,__remaining))
#elif defined(__CRT_HAVE_thrd_sleep64)
/* >> thrd_sleep(3), thrd_sleep64(3)
 * Sleep until a signal is received, or `time_point' has elapsed (s.a. `nanosleep(2)')
 * @return:     0: The (relative) time specified by `time_point' has elapsed
 * @return:    -1: A signal was received while waiting, and `remaining' was filled in (if given)
 * @return: <= -2: Some other error occurred */
__CDECLARE(__ATTR_IN(1) __ATTR_OUT_OPT(2),int,__NOTHROW_RPC,thrd_sleep64,(struct timespec64 const *__time_point, struct timespec64 *__remaining),(__time_point,__remaining))
#elif defined(__CRT_HAVE_thrd_sleep) || defined(__CRT_HAVE_nanosleep64) || defined(__CRT_HAVE_nanosleep) || defined(__CRT_HAVE___nanosleep) || defined(__CRT_HAVE___libc_nanosleep)
#include <libc/local/threads/thrd_sleep64.h>
/* >> thrd_sleep(3), thrd_sleep64(3)
 * Sleep until a signal is received, or `time_point' has elapsed (s.a. `nanosleep(2)')
 * @return:     0: The (relative) time specified by `time_point' has elapsed
 * @return:    -1: A signal was received while waiting, and `remaining' was filled in (if given)
 * @return: <= -2: Some other error occurred */
__NAMESPACE_LOCAL_USING_OR_IMPL(thrd_sleep64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_OUT_OPT(2) int __NOTHROW_RPC(__LIBCCALL thrd_sleep64)(struct timespec64 const *__time_point, struct timespec64 *__remaining) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(thrd_sleep64))(__time_point, __remaining); })
#endif /* ... */
#endif /* __USE_TIME64 */
#ifdef __CRT_HAVE_thrd_exit
/* >> thrd_exit(3)
 * Terminate the calling thread (s.a. `pthread_exit(3)') */
__CDECLARE_VOID(__ATTR_NORETURN,,thrd_exit,(int __res),(__res))
#elif defined(__CRT_HAVE_pthread_exit) || defined(__CRT_HAVE_thr_exit) || defined(__CRT_HAVE_cthread_exit)
#include <libc/local/threads/thrd_exit.h>
/* >> thrd_exit(3)
 * Terminate the calling thread (s.a. `pthread_exit(3)') */
__NAMESPACE_LOCAL_USING_OR_IMPL(thrd_exit, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NORETURN void (__LIBCCALL thrd_exit)(int __res) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(thrd_exit))(__res); })
#endif /* ... */
#ifdef __CRT_HAVE_thrd_detach
/* >> thrd_detach(3)
 * Detach the given thread (s.a. `pthread_detach(3)')
 * @return: thrd_success: Success
 * @return: thrd_error:   Error */
__CDECLARE(,int,__NOTHROW_NCX,thrd_detach,(thrd_t __thr),(__thr))
#elif defined(__CRT_HAVE_pthread_detach) || defined(__CRT_HAVE_cthread_detach)
#include <libc/local/threads/thrd_detach.h>
/* >> thrd_detach(3)
 * Detach the given thread (s.a. `pthread_detach(3)')
 * @return: thrd_success: Success
 * @return: thrd_error:   Error */
__NAMESPACE_LOCAL_USING_OR_IMPL(thrd_detach, __FORCELOCAL __ATTR_ARTIFICIAL int __NOTHROW_NCX(__LIBCCALL thrd_detach)(thrd_t __thr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(thrd_detach))(__thr); })
#endif /* ... */
#ifdef __CRT_HAVE_thrd_join
/* >> thrd_join(3)
 * Wait for the given thread to finish (s.a. `pthread_join(3)')
 * @return: thrd_success: Success
 * @return: thrd_error:   Error */
__CDECLARE(__ATTR_OUT_OPT(2),int,__NOTHROW_RPC,thrd_join,(thrd_t __thr, int *__res),(__thr,__res))
#elif defined(__CRT_HAVE_pthread_join)
#include <libc/local/threads/thrd_join.h>
/* >> thrd_join(3)
 * Wait for the given thread to finish (s.a. `pthread_join(3)')
 * @return: thrd_success: Success
 * @return: thrd_error:   Error */
__NAMESPACE_LOCAL_USING_OR_IMPL(thrd_join, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_OUT_OPT(2) int __NOTHROW_RPC(__LIBCCALL thrd_join)(thrd_t __thr, int *__res) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(thrd_join))(__thr, __res); })
#endif /* ... */
#ifdef __CRT_HAVE_sched_yield
/* >> thrd_yield(3)
 * Yield execution to another thread (s.a. `pthread_yield(3)') */
__CREDIRECT_VOID(,__NOTHROW,thrd_yield,(void),sched_yield,())
#elif defined(__CRT_HAVE_thrd_yield)
/* >> thrd_yield(3)
 * Yield execution to another thread (s.a. `pthread_yield(3)') */
__CDECLARE_VOID(,__NOTHROW,thrd_yield,(void),())
#elif defined(__CRT_HAVE_pthread_yield)
/* >> thrd_yield(3)
 * Yield execution to another thread (s.a. `pthread_yield(3)') */
__CREDIRECT_VOID(,__NOTHROW,thrd_yield,(void),pthread_yield,())
#elif defined(__CRT_HAVE___sched_yield)
/* >> thrd_yield(3)
 * Yield execution to another thread (s.a. `pthread_yield(3)') */
__CREDIRECT_VOID(,__NOTHROW,thrd_yield,(void),__sched_yield,())
#elif defined(__CRT_HAVE___libc_sched_yield)
/* >> thrd_yield(3)
 * Yield execution to another thread (s.a. `pthread_yield(3)') */
__CREDIRECT_VOID(,__NOTHROW,thrd_yield,(void),__libc_sched_yield,())
#elif defined(__CRT_HAVE_yield)
/* >> thrd_yield(3)
 * Yield execution to another thread (s.a. `pthread_yield(3)') */
__CREDIRECT_VOID(,__NOTHROW,thrd_yield,(void),yield,())
#elif defined(__CRT_HAVE_thr_yield)
/* >> thrd_yield(3)
 * Yield execution to another thread (s.a. `pthread_yield(3)') */
__CREDIRECT_VOID(,__NOTHROW,thrd_yield,(void),thr_yield,())
#elif defined(__CRT_HAVE_cthread_yield)
/* >> thrd_yield(3)
 * Yield execution to another thread (s.a. `pthread_yield(3)') */
__CREDIRECT_VOID(,__NOTHROW,thrd_yield,(void),cthread_yield,())
#endif /* ... */


/* Mutex functions.  */

#ifdef __CRT_HAVE_mtx_init
/* >> mtx_init(3)
 * Initialize a mutex object (s.a. `pthread_mutex_init(3)')
 * @return: thrd_success: Success
 * @return: thrd_error:   Error */
__CDECLARE(__ATTR_OUT(1),int,__NOTHROW_NCX,mtx_init,(mtx_t *__restrict __mutex, __STDC_INT_AS_UINT_T __type),(__mutex,__type))
#elif defined(__CRT_HAVE_pthread_mutex_init)
#include <libc/local/threads/mtx_init.h>
/* >> mtx_init(3)
 * Initialize a mutex object (s.a. `pthread_mutex_init(3)')
 * @return: thrd_success: Success
 * @return: thrd_error:   Error */
__NAMESPACE_LOCAL_USING_OR_IMPL(mtx_init, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_OUT(1) int __NOTHROW_NCX(__LIBCCALL mtx_init)(mtx_t *__restrict __mutex, __STDC_INT_AS_UINT_T __type) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mtx_init))(__mutex, __type); })
#endif /* ... */
#ifdef __CRT_HAVE_mtx_lock
/* >> mtx_lock(3)
 * Acquire a lock to a given mutex (s.a. `pthread_mutex_lock(3)')
 * @return: thrd_success: Success
 * @return: thrd_error:   Error */
__CDECLARE(__ATTR_INOUT(1),int,__NOTHROW_RPC,mtx_lock,(mtx_t *__restrict __mutex),(__mutex))
#elif defined(__CRT_HAVE_pthread_mutex_lock)
#include <libc/local/threads/mtx_lock.h>
/* >> mtx_lock(3)
 * Acquire a lock to a given mutex (s.a. `pthread_mutex_lock(3)')
 * @return: thrd_success: Success
 * @return: thrd_error:   Error */
__NAMESPACE_LOCAL_USING_OR_IMPL(mtx_lock, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT(1) int __NOTHROW_RPC(__LIBCCALL mtx_lock)(mtx_t *__restrict __mutex) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mtx_lock))(__mutex); })
#endif /* ... */
#if defined(__CRT_HAVE_mtx_timedlock) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> mtx_timedlock(3), mtx_timedlock64(3)
 * Acquire a lock to a given mutex (s.a. `pthread_mutex_timedlock(3)')
 * @return: thrd_success:  Success
 * @return: thrd_timedout: Timeout
 * @return: thrd_error:    Error */
__CDECLARE(__ATTR_IN(2) __ATTR_INOUT(1),int,__NOTHROW_RPC,mtx_timedlock,(mtx_t *__restrict __mutex, struct timespec const *__restrict __time_point),(__mutex,__time_point))
#elif defined(__CRT_HAVE_mtx_timedlock64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> mtx_timedlock(3), mtx_timedlock64(3)
 * Acquire a lock to a given mutex (s.a. `pthread_mutex_timedlock(3)')
 * @return: thrd_success:  Success
 * @return: thrd_timedout: Timeout
 * @return: thrd_error:    Error */
__CREDIRECT(__ATTR_IN(2) __ATTR_INOUT(1),int,__NOTHROW_RPC,mtx_timedlock,(mtx_t *__restrict __mutex, struct timespec const *__restrict __time_point),mtx_timedlock64,(__mutex,__time_point))
#elif defined(__CRT_HAVE_pthread_mutex_timedlock64) || defined(__CRT_HAVE_pthread_mutex_timedlock)
#include <libc/local/threads/mtx_timedlock.h>
/* >> mtx_timedlock(3), mtx_timedlock64(3)
 * Acquire a lock to a given mutex (s.a. `pthread_mutex_timedlock(3)')
 * @return: thrd_success:  Success
 * @return: thrd_timedout: Timeout
 * @return: thrd_error:    Error */
__NAMESPACE_LOCAL_USING_OR_IMPL(mtx_timedlock, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(2) __ATTR_INOUT(1) int __NOTHROW_RPC(__LIBCCALL mtx_timedlock)(mtx_t *__restrict __mutex, struct timespec const *__restrict __time_point) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mtx_timedlock))(__mutex, __time_point); })
#endif /* ... */
#ifdef __USE_TIME64
#if defined(__CRT_HAVE_mtx_timedlock) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> mtx_timedlock(3), mtx_timedlock64(3)
 * Acquire a lock to a given mutex (s.a. `pthread_mutex_timedlock(3)')
 * @return: thrd_success:  Success
 * @return: thrd_timedout: Timeout
 * @return: thrd_error:    Error */
__CREDIRECT(__ATTR_IN(2) __ATTR_INOUT(1),int,__NOTHROW_RPC,mtx_timedlock64,(mtx_t *__restrict __mutex, struct timespec64 const *__restrict __time_point),mtx_timedlock,(__mutex,__time_point))
#elif defined(__CRT_HAVE_mtx_timedlock64)
/* >> mtx_timedlock(3), mtx_timedlock64(3)
 * Acquire a lock to a given mutex (s.a. `pthread_mutex_timedlock(3)')
 * @return: thrd_success:  Success
 * @return: thrd_timedout: Timeout
 * @return: thrd_error:    Error */
__CDECLARE(__ATTR_IN(2) __ATTR_INOUT(1),int,__NOTHROW_RPC,mtx_timedlock64,(mtx_t *__restrict __mutex, struct timespec64 const *__restrict __time_point),(__mutex,__time_point))
#elif defined(__CRT_HAVE_pthread_mutex_timedlock64) || defined(__CRT_HAVE_pthread_mutex_timedlock)
#include <libc/local/threads/mtx_timedlock64.h>
/* >> mtx_timedlock(3), mtx_timedlock64(3)
 * Acquire a lock to a given mutex (s.a. `pthread_mutex_timedlock(3)')
 * @return: thrd_success:  Success
 * @return: thrd_timedout: Timeout
 * @return: thrd_error:    Error */
__NAMESPACE_LOCAL_USING_OR_IMPL(mtx_timedlock64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(2) __ATTR_INOUT(1) int __NOTHROW_RPC(__LIBCCALL mtx_timedlock64)(mtx_t *__restrict __mutex, struct timespec64 const *__restrict __time_point) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mtx_timedlock64))(__mutex, __time_point); })
#endif /* ... */
#endif /* __USE_TIME64 */
#ifdef __CRT_HAVE_mtx_trylock
/* >> mtx_trylock(3)
 * Try to acquire a lock to a given mutex (s.a. `pthread_mutex_trylock(3)')
 * @return: thrd_success: Success
 * @return: thrd_busy:    Cannot lock without blocking right now
 * @return: thrd_error:   Error */
__CDECLARE(__ATTR_INOUT(1),int,__NOTHROW_NCX,mtx_trylock,(mtx_t *__restrict __mutex),(__mutex))
#elif defined(__CRT_HAVE_pthread_mutex_trylock)
#include <libc/local/threads/mtx_trylock.h>
/* >> mtx_trylock(3)
 * Try to acquire a lock to a given mutex (s.a. `pthread_mutex_trylock(3)')
 * @return: thrd_success: Success
 * @return: thrd_busy:    Cannot lock without blocking right now
 * @return: thrd_error:   Error */
__NAMESPACE_LOCAL_USING_OR_IMPL(mtx_trylock, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT(1) int __NOTHROW_NCX(__LIBCCALL mtx_trylock)(mtx_t *__restrict __mutex) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mtx_trylock))(__mutex); })
#endif /* ... */
#ifdef __CRT_HAVE_mtx_unlock
/* >> mtx_unlock(3)
 * Release a lock from a given mutex (s.a. `pthread_mutex_unlock(3)')
 * @return: thrd_success: Success
 * @return: thrd_error:   Error */
__CDECLARE(__ATTR_INOUT(1),int,__NOTHROW_NCX,mtx_unlock,(mtx_t *__restrict __mutex),(__mutex))
#elif defined(__CRT_HAVE_pthread_mutex_unlock)
#include <libc/local/threads/mtx_unlock.h>
/* >> mtx_unlock(3)
 * Release a lock from a given mutex (s.a. `pthread_mutex_unlock(3)')
 * @return: thrd_success: Success
 * @return: thrd_error:   Error */
__NAMESPACE_LOCAL_USING_OR_IMPL(mtx_unlock, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT(1) int __NOTHROW_NCX(__LIBCCALL mtx_unlock)(mtx_t *__restrict __mutex) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mtx_unlock))(__mutex); })
#endif /* ... */
#ifdef __CRT_HAVE_pthread_mutex_destroy
/* >> mtx_destroy(3)
 * Destroy the given mutex (s.a. `pthread_mutex_destroy(3)') */
__CREDIRECT_VOID(__ATTR_INOUT(1),__NOTHROW_NCX,mtx_destroy,(mtx_t *__restrict __mutex),pthread_mutex_destroy,(__mutex))
#elif defined(__CRT_HAVE_mtx_destroy)
/* >> mtx_destroy(3)
 * Destroy the given mutex (s.a. `pthread_mutex_destroy(3)') */
__CDECLARE_VOID(__ATTR_INOUT(1),__NOTHROW_NCX,mtx_destroy,(mtx_t *__restrict __mutex),(__mutex))
#endif /* ... */
#ifdef __CRT_HAVE_pthread_once
/* >> call_once(3)
 * Invoke `func', but make sure this only happens once (s.a. `pthread_once()') */
__CREDIRECT_VOID(__ATTR_INOUT(1) __ATTR_NONNULL((2)),__NOTHROW_CB,call_once,(once_flag *__restrict __flag, void (__LIBCCALL *__func)(void)),pthread_once,(__flag,__func))
#elif defined(__CRT_HAVE_call_once)
/* >> call_once(3)
 * Invoke `func', but make sure this only happens once (s.a. `pthread_once()') */
__CDECLARE_VOID(__ATTR_INOUT(1) __ATTR_NONNULL((2)),__NOTHROW_CB,call_once,(once_flag *__restrict __flag, void (__LIBCCALL *__func)(void)),(__flag,__func))
#else /* ... */
#include <libc/local/pthread/pthread_once.h>
/* >> call_once(3)
 * Invoke `func', but make sure this only happens once (s.a. `pthread_once()') */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT(1) __ATTR_NONNULL((2)) void __NOTHROW_CB(__LIBCCALL call_once)(once_flag *__restrict __flag, void (__LIBCCALL *__func)(void)) { (void)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pthread_once))((__pthread_once_t *)__flag, __func); }
#endif /* !... */


/* Condition variable functions.  */

#ifdef __CRT_HAVE_cnd_init
/* >> cnd_init(3)
 * Initialize the given condition variable (s.a. `pthread_cond_init(3)')
 * @return: thrd_success: Success
 * @return: thrd_error:   Error */
__CDECLARE(__ATTR_OUT(1),int,__NOTHROW_NCX,cnd_init,(cnd_t *__restrict __cond),(__cond))
#elif defined(__CRT_HAVE_pthread_cond_init)
#include <libc/local/threads/cnd_init.h>
/* >> cnd_init(3)
 * Initialize the given condition variable (s.a. `pthread_cond_init(3)')
 * @return: thrd_success: Success
 * @return: thrd_error:   Error */
__NAMESPACE_LOCAL_USING_OR_IMPL(cnd_init, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_OUT(1) int __NOTHROW_NCX(__LIBCCALL cnd_init)(cnd_t *__restrict __cond) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(cnd_init))(__cond); })
#endif /* ... */
#ifdef __CRT_HAVE_cnd_signal
/* >> cnd_signal(3)
 * Wakeup  one thread currently  waiting on the given
 * condition variable (s.a. `pthread_cond_signal(3)')
 * @return: thrd_success: Success
 * @return: thrd_error:   Error */
__CDECLARE(__ATTR_INOUT(1),int,__NOTHROW_NCX,cnd_signal,(cnd_t *__restrict __cond),(__cond))
#elif defined(__CRT_HAVE_pthread_cond_signal)
#include <libc/local/threads/cnd_signal.h>
/* >> cnd_signal(3)
 * Wakeup  one thread currently  waiting on the given
 * condition variable (s.a. `pthread_cond_signal(3)')
 * @return: thrd_success: Success
 * @return: thrd_error:   Error */
__NAMESPACE_LOCAL_USING_OR_IMPL(cnd_signal, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT(1) int __NOTHROW_NCX(__LIBCCALL cnd_signal)(cnd_t *__restrict __cond) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(cnd_signal))(__cond); })
#endif /* ... */
#ifdef __CRT_HAVE_cnd_broadcast
/* >> cnd_broadcast(3)
 * Wakeup  all  threads currently  waiting on  the given
 * condition variable (s.a. `pthread_cond_broadcast(3)')
 * @return: thrd_success: Success
 * @return: thrd_error:   Error */
__CDECLARE(__ATTR_INOUT(1),int,__NOTHROW_NCX,cnd_broadcast,(cnd_t *__restrict __cond),(__cond))
#elif defined(__CRT_HAVE_pthread_cond_broadcast)
#include <libc/local/threads/cnd_broadcast.h>
/* >> cnd_broadcast(3)
 * Wakeup  all  threads currently  waiting on  the given
 * condition variable (s.a. `pthread_cond_broadcast(3)')
 * @return: thrd_success: Success
 * @return: thrd_error:   Error */
__NAMESPACE_LOCAL_USING_OR_IMPL(cnd_broadcast, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT(1) int __NOTHROW_NCX(__LIBCCALL cnd_broadcast)(cnd_t *__restrict __cond) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(cnd_broadcast))(__cond); })
#endif /* ... */
#ifdef __CRT_HAVE_cnd_wait
/* >> cnd_wait(3)
 * Wait on the given condition variable (s.a. `pthread_cond_wait(3)')
 * @return: thrd_success: Success
 * @return: thrd_error:   Error */
__CDECLARE(__ATTR_INOUT(1) __ATTR_INOUT(2),int,__NOTHROW_RPC,cnd_wait,(cnd_t *__restrict __cond, mtx_t *__restrict __mutex),(__cond,__mutex))
#elif defined(__CRT_HAVE_pthread_cond_wait)
#include <libc/local/threads/cnd_wait.h>
/* >> cnd_wait(3)
 * Wait on the given condition variable (s.a. `pthread_cond_wait(3)')
 * @return: thrd_success: Success
 * @return: thrd_error:   Error */
__NAMESPACE_LOCAL_USING_OR_IMPL(cnd_wait, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT(1) __ATTR_INOUT(2) int __NOTHROW_RPC(__LIBCCALL cnd_wait)(cnd_t *__restrict __cond, mtx_t *__restrict __mutex) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(cnd_wait))(__cond, __mutex); })
#endif /* ... */
#if defined(__CRT_HAVE_cnd_timedwait) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> cnd_timedwait(3), cnd_timedwait64(3)
 * Wait on the given condition variable (s.a. `pthread_cond_timedwait(3)')
 * @return: thrd_success:  Success
 * @return: thrd_timedout: Timeout
 * @return: thrd_error:    Error */
__CDECLARE(__ATTR_IN(3) __ATTR_INOUT(1) __ATTR_INOUT(2),int,__NOTHROW_RPC,cnd_timedwait,(cnd_t *__restrict __cond, mtx_t *__restrict __mutex, struct timespec const *__restrict __time_point),(__cond,__mutex,__time_point))
#elif defined(__CRT_HAVE_cnd_timedwait64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> cnd_timedwait(3), cnd_timedwait64(3)
 * Wait on the given condition variable (s.a. `pthread_cond_timedwait(3)')
 * @return: thrd_success:  Success
 * @return: thrd_timedout: Timeout
 * @return: thrd_error:    Error */
__CREDIRECT(__ATTR_IN(3) __ATTR_INOUT(1) __ATTR_INOUT(2),int,__NOTHROW_RPC,cnd_timedwait,(cnd_t *__restrict __cond, mtx_t *__restrict __mutex, struct timespec const *__restrict __time_point),cnd_timedwait64,(__cond,__mutex,__time_point))
#elif defined(__CRT_HAVE_pthread_cond_timedwait64) || defined(__CRT_HAVE_pthread_cond_timedwait)
#include <libc/local/threads/cnd_timedwait.h>
/* >> cnd_timedwait(3), cnd_timedwait64(3)
 * Wait on the given condition variable (s.a. `pthread_cond_timedwait(3)')
 * @return: thrd_success:  Success
 * @return: thrd_timedout: Timeout
 * @return: thrd_error:    Error */
__NAMESPACE_LOCAL_USING_OR_IMPL(cnd_timedwait, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(3) __ATTR_INOUT(1) __ATTR_INOUT(2) int __NOTHROW_RPC(__LIBCCALL cnd_timedwait)(cnd_t *__restrict __cond, mtx_t *__restrict __mutex, struct timespec const *__restrict __time_point) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(cnd_timedwait))(__cond, __mutex, __time_point); })
#endif /* ... */
#ifdef __USE_TIME64
#if defined(__CRT_HAVE_cnd_timedwait) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> cnd_timedwait(3), cnd_timedwait64(3)
 * Wait on the given condition variable (s.a. `pthread_cond_timedwait(3)')
 * @return: thrd_success:  Success
 * @return: thrd_timedout: Timeout
 * @return: thrd_error:    Error */
__CREDIRECT(__ATTR_IN(3) __ATTR_INOUT(1) __ATTR_INOUT(2),int,__NOTHROW_RPC,cnd_timedwait64,(cnd_t *__restrict __cond, mtx_t *__restrict __mutex, struct timespec64 const *__restrict __time_point),cnd_timedwait,(__cond,__mutex,__time_point))
#elif defined(__CRT_HAVE_cnd_timedwait64)
/* >> cnd_timedwait(3), cnd_timedwait64(3)
 * Wait on the given condition variable (s.a. `pthread_cond_timedwait(3)')
 * @return: thrd_success:  Success
 * @return: thrd_timedout: Timeout
 * @return: thrd_error:    Error */
__CDECLARE(__ATTR_IN(3) __ATTR_INOUT(1) __ATTR_INOUT(2),int,__NOTHROW_RPC,cnd_timedwait64,(cnd_t *__restrict __cond, mtx_t *__restrict __mutex, struct timespec64 const *__restrict __time_point),(__cond,__mutex,__time_point))
#elif defined(__CRT_HAVE_pthread_cond_timedwait64) || defined(__CRT_HAVE_pthread_cond_timedwait)
#include <libc/local/threads/cnd_timedwait64.h>
/* >> cnd_timedwait(3), cnd_timedwait64(3)
 * Wait on the given condition variable (s.a. `pthread_cond_timedwait(3)')
 * @return: thrd_success:  Success
 * @return: thrd_timedout: Timeout
 * @return: thrd_error:    Error */
__NAMESPACE_LOCAL_USING_OR_IMPL(cnd_timedwait64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(3) __ATTR_INOUT(1) __ATTR_INOUT(2) int __NOTHROW_RPC(__LIBCCALL cnd_timedwait64)(cnd_t *__restrict __cond, mtx_t *__restrict __mutex, struct timespec64 const *__restrict __time_point) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(cnd_timedwait64))(__cond, __mutex, __time_point); })
#endif /* ... */
#endif /* __USE_TIME64 */
#ifdef __CRT_HAVE_pthread_cond_destroy
/* Destroy condition variable pointed by cond and free all of its resources
 * s.a. `pthread_cond_destroy()' */
__CREDIRECT_VOID(__ATTR_INOUT(1),__NOTHROW_NCX,cnd_destroy,(cnd_t *__cond),pthread_cond_destroy,(__cond))
#elif defined(__CRT_HAVE_cnd_destroy)
/* Destroy condition variable pointed by cond and free all of its resources
 * s.a. `pthread_cond_destroy()' */
__CDECLARE_VOID(__ATTR_INOUT(1),__NOTHROW_NCX,cnd_destroy,(cnd_t *__cond),(__cond))
#endif /* ... */


/* Thread specific storage functions.  */

#ifdef __CRT_HAVE_tss_create
/* >> tss_create(3)
 * Create a new TLS key (s.a. `pthread_key_create(3)')
 * @return: thrd_success: Success
 * @return: thrd_error:   Error */
__CDECLARE(__ATTR_OUT(1),int,__NOTHROW_NCX,tss_create,(tss_t *__tss_id, void (__LIBKCALL *__destructor)(void *__arg)),(__tss_id,__destructor))
#elif defined(__CRT_HAVE_pthread_key_create) || defined(__CRT_HAVE_thr_keycreate)
#include <libc/local/threads/tss_create.h>
/* >> tss_create(3)
 * Create a new TLS key (s.a. `pthread_key_create(3)')
 * @return: thrd_success: Success
 * @return: thrd_error:   Error */
__NAMESPACE_LOCAL_USING_OR_IMPL(tss_create, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_OUT(1) int __NOTHROW_NCX(__LIBCCALL tss_create)(tss_t *__tss_id, void (__LIBKCALL *__destructor)(void *__arg)) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(tss_create))(__tss_id, __destructor); })
#endif /* ... */
#ifdef __CRT_HAVE_pthread_getspecific
/* >> tss_get(3)
 * Return the calling thread's value for the given TLS key (s.a. `pthread_getspecific(3)')
 * @return: * : The calling thread's value of the given TLS variable */
__CREDIRECT(,void *,__NOTHROW_NCX,tss_get,(tss_t __tss_id),pthread_getspecific,(__tss_id))
#elif defined(__CRT_HAVE_tss_get)
/* >> tss_get(3)
 * Return the calling thread's value for the given TLS key (s.a. `pthread_getspecific(3)')
 * @return: * : The calling thread's value of the given TLS variable */
__CDECLARE(,void *,__NOTHROW_NCX,tss_get,(tss_t __tss_id),(__tss_id))
#elif defined(__CRT_HAVE_pthread_getspecificptr_np)
#include <libc/local/pthread/pthread_getspecific.h>
/* >> tss_get(3)
 * Return the calling thread's value for the given TLS key (s.a. `pthread_getspecific(3)')
 * @return: * : The calling thread's value of the given TLS variable */
__FORCELOCAL __ATTR_ARTIFICIAL void *__NOTHROW_NCX(__LIBCCALL tss_get)(tss_t __tss_id) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pthread_getspecific))((__pthread_key_t)__tss_id); }
#endif /* ... */
#ifdef __CRT_HAVE_tss_set
/* >> tss_set(3)
 * Set the calling thread's value for the given TLS key (s.a. `pthread_setspecific(3)')
 * @return: thrd_success: Success
 * @return: thrd_error:   Error */
__CDECLARE(__ATTR_ACCESS_NONE(2),int,__NOTHROW_NCX,tss_set,(tss_t __tss_id, void *__val),(__tss_id,__val))
#elif defined(__CRT_HAVE_pthread_setspecific) || defined(__CRT_HAVE_thr_setspecific)
#include <libc/local/threads/tss_set.h>
/* >> tss_set(3)
 * Set the calling thread's value for the given TLS key (s.a. `pthread_setspecific(3)')
 * @return: thrd_success: Success
 * @return: thrd_error:   Error */
__NAMESPACE_LOCAL_USING_OR_IMPL(tss_set, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_ACCESS_NONE(2) int __NOTHROW_NCX(__LIBCCALL tss_set)(tss_t __tss_id, void *__val) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(tss_set))(__tss_id, __val); })
#endif /* ... */
#ifdef __CRT_HAVE_pthread_key_delete
/* >> tss_delete(3)
 * Destroys the given TLS key (s.a. `pthread_key_delete(3)') */
__CREDIRECT_VOID(,__NOTHROW_NCX,tss_delete,(tss_t __tss_id),pthread_key_delete,(__tss_id))
#elif defined(__CRT_HAVE_tss_delete)
/* >> tss_delete(3)
 * Destroys the given TLS key (s.a. `pthread_key_delete(3)') */
__CDECLARE_VOID(,__NOTHROW_NCX,tss_delete,(tss_t __tss_id),(__tss_id))
#endif /* ... */

/* NOTE: On true Solaris, this function isn't actually restricted to `__EXTENSIONS__'
 *       as it is here, however this entire header is fully standardized by STD-C, so
 *       in the interest of enforcing a clean namespace, and the fact that I have yet
 *       to see this function anywhere other than Solaris, restrict it to its feature
 *       namespace. */
#ifdef __USE_SOLARIS
#ifndef __thr_min_stack_defined
#define __thr_min_stack_defined
#ifdef __CRT_HAVE_thr_min_stack
/* >> thr_min_stack(3) */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__SIZE_TYPE__,__NOTHROW,thr_min_stack,(void),())
#else /* __CRT_HAVE_thr_min_stack */
#include <libc/local/threads/thr_min_stack.h>
/* >> thr_min_stack(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(thr_min_stack, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __SIZE_TYPE__ __NOTHROW(__LIBCCALL thr_min_stack)(void) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(thr_min_stack))(); })
#endif /* !__CRT_HAVE_thr_min_stack */
#endif /* !__thr_min_stack_defined */
#ifndef __thr_main_defined
#define __thr_main_defined
#ifdef __CRT_HAVE_pthread_main_np
/* >> thr_main(3)
 * Another  one of these non-restricted, but solaris-specific functions:
 * This  one returns 1 if the calling  thread is the main() thread (i.e.
 * the thread that  was started by  the kernel in  order to execute  the
 * calling program), and  0 otherwise. Additionally,  -1 is returned  if
 * the calling thread "hasn't been initialized", or if the caller wasn't
 * created  by one  of the  pthread- or  threads-related init functions.
 * Internally,  this is  the return value  if the caller  doesn't have a
 * proper pthread-controller attached. */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,thr_main,(void),pthread_main_np,())
#elif defined(__CRT_HAVE_thr_main)
/* >> thr_main(3)
 * Another  one of these non-restricted, but solaris-specific functions:
 * This  one returns 1 if the calling  thread is the main() thread (i.e.
 * the thread that  was started by  the kernel in  order to execute  the
 * calling program), and  0 otherwise. Additionally,  -1 is returned  if
 * the calling thread "hasn't been initialized", or if the caller wasn't
 * created  by one  of the  pthread- or  threads-related init functions.
 * Internally,  this is  the return value  if the caller  doesn't have a
 * proper pthread-controller attached. */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,thr_main,(void),())
#elif (defined(__CRT_HAVE_pthread_mainthread_np) && (defined(__CRT_HAVE_pthread_self) || defined(__CRT_HAVE_thrd_current) || defined(__CRT_HAVE_thr_self) || defined(__CRT_HAVE_cthread_self))) || ((defined(__CRT_HAVE_gettid) || defined(__CRT_HAVE___threadid) || defined(__CRT_HAVE_$QGetCurrentThreadId$Aplatform$Adetails$AConcurrency$A$AYAJXZ)) && (defined(__CRT_HAVE_getpid) || defined(__CRT_HAVE__getpid) || defined(__CRT_HAVE___getpid) || defined(__CRT_HAVE___libc_getpid)))
#include <libc/local/pthread/pthread_main_np.h>
/* >> thr_main(3)
 * Another  one of these non-restricted, but solaris-specific functions:
 * This  one returns 1 if the calling  thread is the main() thread (i.e.
 * the thread that  was started by  the kernel in  order to execute  the
 * calling program), and  0 otherwise. Additionally,  -1 is returned  if
 * the calling thread "hasn't been initialized", or if the caller wasn't
 * created  by one  of the  pthread- or  threads-related init functions.
 * Internally,  this is  the return value  if the caller  doesn't have a
 * proper pthread-controller attached. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL thr_main)(void) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pthread_main_np))(); }
#else /* ... */
#undef __thr_main_defined
#endif /* !... */
#endif /* !__thr_main_defined */
#endif /* __USE_SOLARIS */

#endif /* __CC__ */

__SYSDECL_END

#endif /* !_THREADS_H */
