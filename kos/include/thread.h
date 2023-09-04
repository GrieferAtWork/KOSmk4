/* HASH CRC-32:0x5e2e5940 */
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
/* (#) Portability: OpenSolaris (/usr/src/head/thread.h) */
#ifndef _THREAD_H
#define _THREAD_H 1

#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <asm/crt/pthreadvalues.h>
#include <bits/crt/pthreadtypes.h>
#include <bits/types.h>
#include <kos/anno.h>

#ifdef __USE_SOLARIS
#include <bits/os/sigset.h>
#include <bits/os/sigstack.h>
#endif /* __USE_SOLARIS */

#if 1 /* ??? */
#include <sys/signal.h>
#include <sys/time.h>
/*#include <synch.h>*/ /* TODO: Solaris-style synchronization primitives */
#endif

#define THR_MIN_STACK thr_min_stack()

/* Flags for `thr_create(3)' */
#define THR_BOUND     0x00000001 /* s.a. PTHREAD_SCOPE_SYSTEM */
#define THR_NEW_LWP   0x00000002 /* ??? */
#define THR_DETACHED  0x00000040 /* s.a. PTHREAD_CREATE_DETACHED */
#define THR_SUSPENDED 0x00000080 /* TODO: pthread_attr_setcreatesuspend_np */
#define THR_DAEMON    0x00000100 /* ??? */

/* Static initializer for `thr_keycreate_once(3)' */
#ifdef __PTHREAD_ONCE_KEY_NP
#define THR_ONCE_KEY __PTHREAD_ONCE_KEY_NP
#else /* __PTHREAD_ONCE_KEY_NP */
#define THR_ONCE_KEY ((thread_key_t)-1)
#endif /* !__PTHREAD_ONCE_KEY_NP */

#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __size_t_defined
#define __size_t_defined
typedef __SIZE_TYPE__ size_t;
#endif /* !__size_t_defined */

typedef __pthread_t thread_t;
typedef __pthread_key_t thread_key_t;

#ifdef __CRT_HAVE_thr_create
__CDECLARE(__ATTR_OUT(6) __ATTR_NONNULL((3)),__errno_t,__NOTHROW_NCX,thr_create,(void *__stack_base, size_t __stack_size, void *(__LIBCCALL *__start_routine)(void *__arg), void *__arg, long __flags, thread_t *__newthread),(__stack_base,__stack_size,__start_routine,__arg,__flags,__newthread))
#elif defined(__CRT_HAVE_pthread_create)
#include <libc/local/thread/thr_create.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(thr_create, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_OUT(6) __ATTR_NONNULL((3)) __errno_t __NOTHROW_NCX(__LIBCCALL thr_create)(void *__stack_base, size_t __stack_size, void *(__LIBCCALL *__start_routine)(void *__arg), void *__arg, long __flags, thread_t *__newthread) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(thr_create))(__stack_base, __stack_size, __start_routine, __arg, __flags, __newthread); })
#endif /* ... */
#ifdef __CRT_HAVE_thr_join
__CDECLARE(__ATTR_OUT(2) __ATTR_OUT_OPT(3),__errno_t,__NOTHROW_RPC,thr_join,(thread_t __thr, thread_t *__p_departed, void **__thread_return),(__thr,__p_departed,__thread_return))
#elif defined(__CRT_HAVE_pthread_join)
#include <libc/local/thread/thr_join.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(thr_join, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_OUT(2) __ATTR_OUT_OPT(3) __errno_t __NOTHROW_RPC(__LIBCCALL thr_join)(thread_t __thr, thread_t *__p_departed, void **__thread_return) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(thr_join))(__thr, __p_departed, __thread_return); })
#endif /* ... */
#ifdef __CRT_HAVE_pthread_exit
/* >> pthread_exit(3)
 * Terminate calling thread.
 * The registered cleanup handlers are called via exception handling */
__CREDIRECT_VOID(__ATTR_NORETURN __ATTR_ACCESS_NONE(1),,thr_exit,(void *__retval),pthread_exit,(__retval))
#elif defined(__CRT_HAVE_thr_exit)
/* >> pthread_exit(3)
 * Terminate calling thread.
 * The registered cleanup handlers are called via exception handling */
__CDECLARE_VOID(__ATTR_NORETURN __ATTR_ACCESS_NONE(1),,thr_exit,(void *__retval),(__retval))
#elif defined(__CRT_HAVE_cthread_exit)
/* >> pthread_exit(3)
 * Terminate calling thread.
 * The registered cleanup handlers are called via exception handling */
__CREDIRECT_VOID(__ATTR_NORETURN __ATTR_ACCESS_NONE(1),,thr_exit,(void *__retval),cthread_exit,(__retval))
#endif /* ... */
#ifdef __CRT_HAVE_pthread_self
/* >> pthread_self(3)
 * Obtain the identifier of the current thread
 * @return: * : Handle for the calling thread */
__CREDIRECT(__ATTR_CONST,thread_t,__NOTHROW,thr_self,(void),pthread_self,())
#elif defined(__CRT_HAVE_thrd_current)
/* >> pthread_self(3)
 * Obtain the identifier of the current thread
 * @return: * : Handle for the calling thread */
__CREDIRECT(__ATTR_CONST,thread_t,__NOTHROW,thr_self,(void),thrd_current,())
#elif defined(__CRT_HAVE_thr_self)
/* >> pthread_self(3)
 * Obtain the identifier of the current thread
 * @return: * : Handle for the calling thread */
__CDECLARE(__ATTR_CONST,thread_t,__NOTHROW,thr_self,(void),())
#elif defined(__CRT_HAVE_cthread_self)
/* >> pthread_self(3)
 * Obtain the identifier of the current thread
 * @return: * : Handle for the calling thread */
__CREDIRECT(__ATTR_CONST,thread_t,__NOTHROW,thr_self,(void),cthread_self,())
#endif /* ... */
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
#ifdef __CRT_HAVE_pthread_kill
/* >> pthread_kill(3)
 * Portable function for sending a signal to a specific `pthread' within one's own process.
 * @return: EOK:    Success
 * @return: EINVAL: The given `signo' is invalid */
__CREDIRECT(,__errno_t,__NOTHROW_NCX,thr_kill,(thread_t __thr, __signo_t __signo),pthread_kill,(__thr,__signo))
#elif defined(__CRT_HAVE_thr_kill)
/* >> pthread_kill(3)
 * Portable function for sending a signal to a specific `pthread' within one's own process.
 * @return: EOK:    Success
 * @return: EINVAL: The given `signo' is invalid */
__CDECLARE(,__errno_t,__NOTHROW_NCX,thr_kill,(thread_t __thr, __signo_t __signo),(__thr,__signo))
#endif /* ... */
#ifdef __CRT_HAVE_thr_setprio
__CDECLARE(,__errno_t,__NOTHROW_NCX,thr_setprio,(thread_t __thr, int __priority),(__thr,__priority))
#elif defined(__CRT_HAVE_pthread_setschedparam) && defined(__CRT_HAVE_pthread_getschedparam)
#include <libc/local/thread/thr_setprio.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(thr_setprio, __FORCELOCAL __ATTR_ARTIFICIAL __errno_t __NOTHROW_NCX(__LIBCCALL thr_setprio)(thread_t __thr, int __priority) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(thr_setprio))(__thr, __priority); })
#endif /* ... */
#ifdef __CRT_HAVE_thr_getprio
__CDECLARE(__ATTR_OUT(2),__errno_t,__NOTHROW_NCX,thr_getprio,(thread_t __thr, int *__p_priority),(__thr,__p_priority))
#elif defined(__CRT_HAVE_pthread_getschedparam)
#include <libc/local/thread/thr_getprio.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(thr_getprio, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_OUT(2) __errno_t __NOTHROW_NCX(__LIBCCALL thr_getprio)(thread_t __thr, int *__p_priority) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(thr_getprio))(__thr, __p_priority); })
#endif /* ... */
#ifdef __CRT_HAVE_pthread_key_create
/* >> pthread_key_create(3)
 * Create a key value identifying a location in the thread-specific
 * data area. Each thread maintains a distinct thread-specific data
 * area. `destr_function', if non-`NULL', is called with the  value
 * associated to that key when the key is destroyed.
 * `destr_function' is not called if the value associated is `NULL'
 * when the key is destroyed
 * @return: EOK:    Success
 * @return: ENOMEM: Insufficient memory to create the key */
__CREDIRECT(__ATTR_OUT(1),__errno_t,__NOTHROW_NCX,thr_keycreate,(thread_key_t *__key, void (__LIBKCALL *__destr_function)(void *)),pthread_key_create,(__key,__destr_function))
#elif defined(__CRT_HAVE_thr_keycreate)
/* >> pthread_key_create(3)
 * Create a key value identifying a location in the thread-specific
 * data area. Each thread maintains a distinct thread-specific data
 * area. `destr_function', if non-`NULL', is called with the  value
 * associated to that key when the key is destroyed.
 * `destr_function' is not called if the value associated is `NULL'
 * when the key is destroyed
 * @return: EOK:    Success
 * @return: ENOMEM: Insufficient memory to create the key */
__CDECLARE(__ATTR_OUT(1),__errno_t,__NOTHROW_NCX,thr_keycreate,(thread_key_t *__key, void (__LIBKCALL *__destr_function)(void *)),(__key,__destr_function))
#elif defined(__CRT_HAVE___pthread_key_create)
/* >> pthread_key_create(3)
 * Create a key value identifying a location in the thread-specific
 * data area. Each thread maintains a distinct thread-specific data
 * area. `destr_function', if non-`NULL', is called with the  value
 * associated to that key when the key is destroyed.
 * `destr_function' is not called if the value associated is `NULL'
 * when the key is destroyed
 * @return: EOK:    Success
 * @return: ENOMEM: Insufficient memory to create the key */
__CREDIRECT(__ATTR_OUT(1),__errno_t,__NOTHROW_NCX,thr_keycreate,(thread_key_t *__key, void (__LIBKCALL *__destr_function)(void *)),__pthread_key_create,(__key,__destr_function))
#endif /* ... */
#ifdef __CRT_HAVE_pthread_key_create_once_np
/* >> pthread_key_create_once_np(3)
 * Same as `pthread_key_create()', but the  given `key' must be  pre-initialized
 * using the static initializer `PTHREAD_ONCE_KEY_NP', whilst this function will
 * make  sure that  even in the  event of multiple  simultaneous threads calling
 * this function, only one will create the  key, and all others will wait  until
 * the key has been  created. Once the  key was created,  further calls to  this
 * function will no longer block, but simply return immediately.
 * @return: EOK:    Success
 * @return: ENOMEM: Insufficient memory to create the key */
__CREDIRECT(__ATTR_OUT(1),__errno_t,__NOTHROW_NCX,thr_keycreate_once,(thread_key_t *__key, void (__LIBKCALL *__destr_function)(void *)),pthread_key_create_once_np,(__key,__destr_function))
#elif defined(__CRT_HAVE_thr_keycreate_once)
/* >> pthread_key_create_once_np(3)
 * Same as `pthread_key_create()', but the  given `key' must be  pre-initialized
 * using the static initializer `PTHREAD_ONCE_KEY_NP', whilst this function will
 * make  sure that  even in the  event of multiple  simultaneous threads calling
 * this function, only one will create the  key, and all others will wait  until
 * the key has been  created. Once the  key was created,  further calls to  this
 * function will no longer block, but simply return immediately.
 * @return: EOK:    Success
 * @return: ENOMEM: Insufficient memory to create the key */
__CDECLARE(__ATTR_OUT(1),__errno_t,__NOTHROW_NCX,thr_keycreate_once,(thread_key_t *__key, void (__LIBKCALL *__destr_function)(void *)),(__key,__destr_function))
#elif defined(__CRT_HAVE_pthread_key_create) || defined(__CRT_HAVE_thr_keycreate) || defined(__CRT_HAVE___pthread_key_create)
#include <libc/local/pthread/pthread_key_create_once_np.h>
/* >> pthread_key_create_once_np(3)
 * Same as `pthread_key_create()', but the  given `key' must be  pre-initialized
 * using the static initializer `PTHREAD_ONCE_KEY_NP', whilst this function will
 * make  sure that  even in the  event of multiple  simultaneous threads calling
 * this function, only one will create the  key, and all others will wait  until
 * the key has been  created. Once the  key was created,  further calls to  this
 * function will no longer block, but simply return immediately.
 * @return: EOK:    Success
 * @return: ENOMEM: Insufficient memory to create the key */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_OUT(1) __errno_t __NOTHROW_NCX(__LIBCCALL thr_keycreate_once)(thread_key_t *__key, void (__LIBKCALL *__destr_function)(void *)) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pthread_key_create_once_np))((__pthread_key_t *)__key, __destr_function); }
#endif /* ... */
#ifdef __CRT_HAVE_pthread_setspecific
/* >> pthread_setspecific(3)
 * Store POINTER in the thread-specific data slot identified by `key'
 * @return: EOK:    Success
 * @return: EINVAL: Invalid `key'
 * @return: ENOMEM: `pointer' is non-`NULL', `key' had yet to be allocated for the
 *                  calling  thread, and an attempt to allocate it just now failed */
__CREDIRECT(__ATTR_ACCESS_NONE(2),__errno_t,__NOTHROW_NCX,thr_setspecific,(thread_key_t __key, void *__val),pthread_setspecific,(__key,__val))
#elif defined(__CRT_HAVE_thr_setspecific)
/* >> pthread_setspecific(3)
 * Store POINTER in the thread-specific data slot identified by `key'
 * @return: EOK:    Success
 * @return: EINVAL: Invalid `key'
 * @return: ENOMEM: `pointer' is non-`NULL', `key' had yet to be allocated for the
 *                  calling  thread, and an attempt to allocate it just now failed */
__CDECLARE(__ATTR_ACCESS_NONE(2),__errno_t,__NOTHROW_NCX,thr_setspecific,(thread_key_t __key, void *__val),(__key,__val))
#elif defined(__CRT_HAVE___pthread_setspecific)
/* >> pthread_setspecific(3)
 * Store POINTER in the thread-specific data slot identified by `key'
 * @return: EOK:    Success
 * @return: EINVAL: Invalid `key'
 * @return: ENOMEM: `pointer' is non-`NULL', `key' had yet to be allocated for the
 *                  calling  thread, and an attempt to allocate it just now failed */
__CREDIRECT(__ATTR_ACCESS_NONE(2),__errno_t,__NOTHROW_NCX,thr_setspecific,(thread_key_t __key, void *__val),__pthread_setspecific,(__key,__val))
#endif /* ... */
#ifdef __CRT_HAVE_thr_getspecific
__CDECLARE(__ATTR_OUT(2),__errno_t,__NOTHROW_NCX,thr_getspecific,(thread_key_t __key, void **__p_val),(__key,__p_val))
#elif (defined(__CRT_HAVE_pthread_getspecific) || defined(__CRT_HAVE_tss_get) || defined(__CRT_HAVE___pthread_getspecific) || defined(__CRT_HAVE_pthread_getspecificptr_np)) && (defined(__CRT_HAVE_pthread_setspecific) || defined(__CRT_HAVE_thr_setspecific) || defined(__CRT_HAVE___pthread_setspecific))
#include <libc/local/thread/thr_getspecific.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(thr_getspecific, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_OUT(2) __errno_t __NOTHROW_NCX(__LIBCCALL thr_getspecific)(thread_key_t __key, void **__p_val) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(thr_getspecific))(__key, __p_val); })
#endif /* ... */
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
#ifdef __CRT_HAVE_pthread_getconcurrency
/* >> pthread_getconcurrency(3)
 * Determine level of concurrency
 * @return: * : The current concurrency level */
__CREDIRECT(__ATTR_PURE,int,__NOTHROW_NCX,thr_getconcurrency,(void),pthread_getconcurrency,())
#elif defined(__CRT_HAVE_thr_getconcurrency)
/* >> pthread_getconcurrency(3)
 * Determine level of concurrency
 * @return: * : The current concurrency level */
__CDECLARE(__ATTR_PURE,int,__NOTHROW_NCX,thr_getconcurrency,(void),())
#endif /* ... */
#ifdef __CRT_HAVE_pthread_setconcurrency
/* >> pthread_setconcurrency(3)
 * Set new concurrency level to `level'
 * @return: EOK:    Success
 * @return: EINVAL: The given `level' is negative */
__CREDIRECT(,__errno_t,__NOTHROW_NCX,thr_setconcurrency,(int __level),pthread_setconcurrency,(__level))
#elif defined(__CRT_HAVE_thr_setconcurrency)
/* >> pthread_setconcurrency(3)
 * Set new concurrency level to `level'
 * @return: EOK:    Success
 * @return: EINVAL: The given `level' is negative */
__CDECLARE(,__errno_t,__NOTHROW_NCX,thr_setconcurrency,(int __level),(__level))
#endif /* ... */
#ifdef __CRT_HAVE_sched_yield
/* >> sched_yield(2)
 * @return: 1: Another thread was  executed prior to  the function  returning
 *             The thread may not necessarily be apart of the calling process
 * @return: 0: The function returned immediately when no other thread was executed */
__CREDIRECT_VOID(,__NOTHROW_NCX,thr_yield,(void),sched_yield,())
#elif defined(__CRT_HAVE_thrd_yield)
/* >> sched_yield(2)
 * @return: 1: Another thread was  executed prior to  the function  returning
 *             The thread may not necessarily be apart of the calling process
 * @return: 0: The function returned immediately when no other thread was executed */
__CREDIRECT_VOID(,__NOTHROW_NCX,thr_yield,(void),thrd_yield,())
#elif defined(__CRT_HAVE_pthread_yield)
/* >> sched_yield(2)
 * @return: 1: Another thread was  executed prior to  the function  returning
 *             The thread may not necessarily be apart of the calling process
 * @return: 0: The function returned immediately when no other thread was executed */
__CREDIRECT_VOID(,__NOTHROW_NCX,thr_yield,(void),pthread_yield,())
#elif defined(__CRT_HAVE___sched_yield)
/* >> sched_yield(2)
 * @return: 1: Another thread was  executed prior to  the function  returning
 *             The thread may not necessarily be apart of the calling process
 * @return: 0: The function returned immediately when no other thread was executed */
__CREDIRECT_VOID(,__NOTHROW_NCX,thr_yield,(void),__sched_yield,())
#elif defined(__CRT_HAVE___libc_sched_yield)
/* >> sched_yield(2)
 * @return: 1: Another thread was  executed prior to  the function  returning
 *             The thread may not necessarily be apart of the calling process
 * @return: 0: The function returned immediately when no other thread was executed */
__CREDIRECT_VOID(,__NOTHROW_NCX,thr_yield,(void),__libc_sched_yield,())
#elif defined(__CRT_HAVE_yield)
/* >> sched_yield(2)
 * @return: 1: Another thread was  executed prior to  the function  returning
 *             The thread may not necessarily be apart of the calling process
 * @return: 0: The function returned immediately when no other thread was executed */
__CREDIRECT_VOID(,__NOTHROW_NCX,thr_yield,(void),yield,())
#elif defined(__CRT_HAVE_thr_yield)
/* >> sched_yield(2)
 * @return: 1: Another thread was  executed prior to  the function  returning
 *             The thread may not necessarily be apart of the calling process
 * @return: 0: The function returned immediately when no other thread was executed */
__CDECLARE_VOID(,__NOTHROW_NCX,thr_yield,(void),())
#elif defined(__CRT_HAVE_cthread_yield)
/* >> sched_yield(2)
 * @return: 1: Another thread was  executed prior to  the function  returning
 *             The thread may not necessarily be apart of the calling process
 * @return: 0: The function returned immediately when no other thread was executed */
__CREDIRECT_VOID(,__NOTHROW_NCX,thr_yield,(void),cthread_yield,())
#endif /* ... */

#ifdef __USE_SOLARIS

#ifndef __sigset_t_defined
#define __sigset_t_defined
typedef struct __sigset_struct sigset_t;
#endif /* !__sigset_t_defined */

#ifndef __stack_t_defined
#define __stack_t_defined
typedef struct sigaltstack stack_t;
#endif /* !__stack_t_defined */

#ifdef __CRT_HAVE_pthread_sigmask
/* >> pthread_sigmask(3)
 * Thread-safe version of `sigprocmask(2)'. Note though, that on
 * many systems (including KOS), this function behaves identical
 * to `sigprocmask()', though portable programs should still use
 * this function if they intend to use multiple threads.
 * @return: EOK:    Success
 * @return: EINVAL: Invalid `how' */
__CREDIRECT(__ATTR_IN_OPT(2) __ATTR_OUT_OPT(3),__errno_t,__NOTHROW_NCX,thr_sigsetmask,(__STDC_INT_AS_UINT_T __how, struct __sigset_struct const *__newmask, struct __sigset_struct *__oldmask),pthread_sigmask,(__how,__newmask,__oldmask))
#elif defined(__CRT_HAVE_thr_sigsetmask)
/* >> pthread_sigmask(3)
 * Thread-safe version of `sigprocmask(2)'. Note though, that on
 * many systems (including KOS), this function behaves identical
 * to `sigprocmask()', though portable programs should still use
 * this function if they intend to use multiple threads.
 * @return: EOK:    Success
 * @return: EINVAL: Invalid `how' */
__CDECLARE(__ATTR_IN_OPT(2) __ATTR_OUT_OPT(3),__errno_t,__NOTHROW_NCX,thr_sigsetmask,(__STDC_INT_AS_UINT_T __how, struct __sigset_struct const *__newmask, struct __sigset_struct *__oldmask),(__how,__newmask,__oldmask))
#elif defined(__CRT_HAVE_sigprocmask)
/* >> pthread_sigmask(3)
 * Thread-safe version of `sigprocmask(2)'. Note though, that on
 * many systems (including KOS), this function behaves identical
 * to `sigprocmask()', though portable programs should still use
 * this function if they intend to use multiple threads.
 * @return: EOK:    Success
 * @return: EINVAL: Invalid `how' */
__CREDIRECT(__ATTR_IN_OPT(2) __ATTR_OUT_OPT(3),__errno_t,__NOTHROW_NCX,thr_sigsetmask,(__STDC_INT_AS_UINT_T __how, struct __sigset_struct const *__newmask, struct __sigset_struct *__oldmask),sigprocmask,(__how,__newmask,__oldmask))
#endif /* ... */
#ifdef __CRT_HAVE_thr_stksegment
/* >> thr_stksegment(3)
 * Wrapper for `pthread_stackseg_np(pthread_self(), sinfo)' */
__CDECLARE(,__errno_t,__NOTHROW_NCX,thr_stksegment,(stack_t *__sinfo),(__sinfo))
#elif (defined(__CRT_HAVE_pthread_stackseg_np) || (defined(__CRT_HAVE_pthread_getattr_np) && (defined(__CRT_HAVE_pthread_attr_getstack) || (defined(__CRT_HAVE_pthread_attr_getstackaddr) && defined(__CRT_HAVE_pthread_attr_getstacksize))))) && (defined(__CRT_HAVE_pthread_self) || defined(__CRT_HAVE_thrd_current) || defined(__CRT_HAVE_thr_self) || defined(__CRT_HAVE_cthread_self))
#include <libc/local/thread/thr_stksegment.h>
/* >> thr_stksegment(3)
 * Wrapper for `pthread_stackseg_np(pthread_self(), sinfo)' */
__NAMESPACE_LOCAL_USING_OR_IMPL(thr_stksegment, __FORCELOCAL __ATTR_ARTIFICIAL __errno_t __NOTHROW_NCX(__LIBCCALL thr_stksegment)(stack_t *__sinfo) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(thr_stksegment))(__sinfo); })
#endif /* ... */
#endif /* __USE_SOLARIS */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_THREAD_H */
