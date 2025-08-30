/* HASH CRC-32:0x8538ccf9 */
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
/* (#) Portability: DragonFly BSD (/include/pthread_np.h) */
/* (#) Portability: FreeBSD       (/include/pthread_np.h) */
/* (#) Portability: OpenBSD       (/include/pthread_np.h) */
/*!always_includes <pthread.h>*/
#ifndef _PTHREAD_NP_H
#define _PTHREAD_NP_H 1

#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <bits/os/sigstack.h>
#include <bits/os/cpu_set.h>
#include <bits/types.h>
#include <pthread.h>


#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __cpu_set_t_defined
#define __cpu_set_t_defined
typedef struct __cpu_set_struct cpu_set_t;
#endif /* !__cpu_set_t_defined */

#ifndef __stack_t_defined
#define __stack_t_defined
typedef struct sigaltstack stack_t;
#endif /* !__stack_t_defined */

#ifndef __pthread_id_np_t_defined
#define __pthread_id_np_t_defined
typedef __pid_t pthread_id_np_t;
#endif /* !__pthread_id_np_t_defined */

#ifndef __pthread_switch_routine_t_defined
#define __pthread_switch_routine_t_defined
typedef __pthread_switch_routine_t pthread_switch_routine_t;
#endif /* !__pthread_switch_routine_t_defined */

#ifdef __CRT_HAVE_pthread_mutexattr_gettype
/* >> pthread_mutexattr_gettype(3)
 * Return in `*kind' the mutex kind attribute in `*self'
 * @return: EOK: Success */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),__errno_t,__NOTHROW_NCX,pthread_mutexattr_getkind_np,(pthread_mutexattr_t const *__restrict __self, int *__restrict __kind),pthread_mutexattr_gettype,(__self,__kind))
#elif defined(__CRT_HAVE_pthread_mutexattr_getkind_np)
/* >> pthread_mutexattr_gettype(3)
 * Return in `*kind' the mutex kind attribute in `*self'
 * @return: EOK: Success */
__CDECLARE(__ATTR_IN(1) __ATTR_OUT(2),__errno_t,__NOTHROW_NCX,pthread_mutexattr_getkind_np,(pthread_mutexattr_t const *__restrict __self, int *__restrict __kind),(__self,__kind))
#endif /* ... */
#ifdef __CRT_HAVE_pthread_mutexattr_settype
/* >> pthread_mutexattr_settype(3)
 * Set  the mutex kind attribute in `*self' to `kind' (either `PTHREAD_MUTEX_NORMAL',
 * `PTHREAD_MUTEX_RECURSIVE', `PTHREAD_MUTEX_ERRORCHECK', or `PTHREAD_MUTEX_DEFAULT')
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `kind' */
__CREDIRECT(__ATTR_INOUT(1),__errno_t,__NOTHROW_NCX,pthread_mutexattr_setkind_np,(pthread_mutexattr_t *__self, int __kind),pthread_mutexattr_settype,(__self,__kind))
#elif defined(__CRT_HAVE_pthread_mutexattr_setkind_np)
/* >> pthread_mutexattr_settype(3)
 * Set  the mutex kind attribute in `*self' to `kind' (either `PTHREAD_MUTEX_NORMAL',
 * `PTHREAD_MUTEX_RECURSIVE', `PTHREAD_MUTEX_ERRORCHECK', or `PTHREAD_MUTEX_DEFAULT')
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `kind' */
__CDECLARE(__ATTR_INOUT(1),__errno_t,__NOTHROW_NCX,pthread_mutexattr_setkind_np,(pthread_mutexattr_t *__self, int __kind),(__self,__kind))
#elif defined(__CRT_HAVE___pthread_mutexattr_settype)
/* >> pthread_mutexattr_settype(3)
 * Set  the mutex kind attribute in `*self' to `kind' (either `PTHREAD_MUTEX_NORMAL',
 * `PTHREAD_MUTEX_RECURSIVE', `PTHREAD_MUTEX_ERRORCHECK', or `PTHREAD_MUTEX_DEFAULT')
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `kind' */
__CREDIRECT(__ATTR_INOUT(1),__errno_t,__NOTHROW_NCX,pthread_mutexattr_setkind_np,(pthread_mutexattr_t *__self, int __kind),__pthread_mutexattr_settype,(__self,__kind))
#endif /* ... */
#ifdef __CRT_HAVE_pthread_getname_np
/* >> pthread_getname_np(3)
 * Get thread name visible in the kernel and its interfaces
 * @return: EOK:    Success
 * @return: ERANGE: The given `buflen' is too small */
__CREDIRECT(__ATTR_OUTS(2, 3),__errno_t,__NOTHROW_NCX,pthread_get_name_np,(pthread_t __self, char *__buf, size_t __buflen),pthread_getname_np,(__self,__buf,__buflen))
#elif defined(__CRT_HAVE_pthread_get_name_np)
/* >> pthread_getname_np(3)
 * Get thread name visible in the kernel and its interfaces
 * @return: EOK:    Success
 * @return: ERANGE: The given `buflen' is too small */
__CDECLARE(__ATTR_OUTS(2, 3),__errno_t,__NOTHROW_NCX,pthread_get_name_np,(pthread_t __self, char *__buf, size_t __buflen),(__self,__buf,__buflen))
#endif /* ... */
#ifndef __pthread_getname_np_defined
#define __pthread_getname_np_defined
#ifdef __CRT_HAVE_pthread_getname_np
/* >> pthread_getname_np(3)
 * Get thread name visible in the kernel and its interfaces
 * @return: EOK:    Success
 * @return: ERANGE: The given `buflen' is too small */
__CDECLARE(__ATTR_OUTS(2, 3),__errno_t,__NOTHROW_NCX,pthread_getname_np,(pthread_t __self, char *__buf, size_t __buflen),(__self,__buf,__buflen))
#elif defined(__CRT_HAVE_pthread_get_name_np)
/* >> pthread_getname_np(3)
 * Get thread name visible in the kernel and its interfaces
 * @return: EOK:    Success
 * @return: ERANGE: The given `buflen' is too small */
__CREDIRECT(__ATTR_OUTS(2, 3),__errno_t,__NOTHROW_NCX,pthread_getname_np,(pthread_t __self, char *__buf, size_t __buflen),pthread_get_name_np,(__self,__buf,__buflen))
#else /* ... */
#undef __pthread_getname_np_defined
#endif /* !... */
#endif /* !__pthread_getname_np_defined */
#ifdef __CRT_HAVE_pthread_setname_np
/* >> pthread_setname_np(3)
 * Set thread name visible in the kernel and its interfaces
 * @return: EOK:    Success
 * @return: ERANGE: The given `name' is too long */
__CREDIRECT(__ATTR_IN(2),__errno_t,__NOTHROW_NCX,pthread_set_name_np,(pthread_t __self, char const *__name),pthread_setname_np,(__self,__name))
#elif defined(__CRT_HAVE_pthread_set_name_np)
/* >> pthread_setname_np(3)
 * Set thread name visible in the kernel and its interfaces
 * @return: EOK:    Success
 * @return: ERANGE: The given `name' is too long */
__CDECLARE(__ATTR_IN(2),__errno_t,__NOTHROW_NCX,pthread_set_name_np,(pthread_t __self, char const *__name),(__self,__name))
#elif defined(__CRT_HAVE_cthread_set_name)
/* >> pthread_setname_np(3)
 * Set thread name visible in the kernel and its interfaces
 * @return: EOK:    Success
 * @return: ERANGE: The given `name' is too long */
__CREDIRECT(__ATTR_IN(2),__errno_t,__NOTHROW_NCX,pthread_set_name_np,(pthread_t __self, char const *__name),cthread_set_name,(__self,__name))
#endif /* ... */
#ifndef __pthread_setname_np_defined
#define __pthread_setname_np_defined
#ifdef __CRT_HAVE_pthread_setname_np
/* >> pthread_setname_np(3)
 * Set thread name visible in the kernel and its interfaces
 * @return: EOK:    Success
 * @return: ERANGE: The given `name' is too long */
__CDECLARE(__ATTR_IN(2),__errno_t,__NOTHROW_NCX,pthread_setname_np,(pthread_t __self, char const *__name),(__self,__name))
#elif defined(__CRT_HAVE_pthread_set_name_np)
/* >> pthread_setname_np(3)
 * Set thread name visible in the kernel and its interfaces
 * @return: EOK:    Success
 * @return: ERANGE: The given `name' is too long */
__CREDIRECT(__ATTR_IN(2),__errno_t,__NOTHROW_NCX,pthread_setname_np,(pthread_t __self, char const *__name),pthread_set_name_np,(__self,__name))
#elif defined(__CRT_HAVE_cthread_set_name)
/* >> pthread_setname_np(3)
 * Set thread name visible in the kernel and its interfaces
 * @return: EOK:    Success
 * @return: ERANGE: The given `name' is too long */
__CREDIRECT(__ATTR_IN(2),__errno_t,__NOTHROW_NCX,pthread_setname_np,(pthread_t __self, char const *__name),cthread_set_name,(__self,__name))
#else /* ... */
#undef __pthread_setname_np_defined
#endif /* !... */
#endif /* !__pthread_setname_np_defined */
#ifdef __CRT_HAVE_pthread_getattr_np
/* >> pthread_getattr_np(3)
 * Initialize thread attribute `*attr' with attributes corresponding to  the
 * already running thread `self'. It shall be called on uninitialized `attr'
 * and destroyed with `pthread_attr_destroy(3)' when no longer needed
 * @return: EOK:    Success
 * @return: ENOMEM: Insufficient memory */
__CREDIRECT(__ATTR_OUT(2),__errno_t,__NOTHROW_NCX,pthread_attr_get_np,(pthread_t __self, pthread_attr_t *__attr),pthread_getattr_np,(__self,__attr))
#elif defined(__CRT_HAVE_pthread_attr_get_np)
/* >> pthread_getattr_np(3)
 * Initialize thread attribute `*attr' with attributes corresponding to  the
 * already running thread `self'. It shall be called on uninitialized `attr'
 * and destroyed with `pthread_attr_destroy(3)' when no longer needed
 * @return: EOK:    Success
 * @return: ENOMEM: Insufficient memory */
__CDECLARE(__ATTR_OUT(2),__errno_t,__NOTHROW_NCX,pthread_attr_get_np,(pthread_t __self, pthread_attr_t *__attr),(__self,__attr))
#endif /* ... */
#ifndef __pthread_main_np_defined
#define __pthread_main_np_defined
#ifdef __CRT_HAVE_pthread_main_np
/* >> pthread_main_np(3)
 * Returns  1 if the  calling thread is the  main() thread (i.e. the
 * thread  that was  started by the  kernel in order  to execute the
 * calling program), and 0  otherwise. Additionally, -1 is  returned
 * if the  calling  thread  "hasn't been initialized",  though  this
 * isn't a case that can actually happen under KOS's implementation. */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,pthread_main_np,(void),())
#elif defined(__CRT_HAVE_thr_main)
/* >> pthread_main_np(3)
 * Returns  1 if the  calling thread is the  main() thread (i.e. the
 * thread  that was  started by the  kernel in order  to execute the
 * calling program), and 0  otherwise. Additionally, -1 is  returned
 * if the  calling  thread  "hasn't been initialized",  though  this
 * isn't a case that can actually happen under KOS's implementation. */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,pthread_main_np,(void),thr_main,())
#elif (defined(__CRT_HAVE_pthread_mainthread_np) && (defined(__CRT_HAVE_pthread_self) || defined(__CRT_HAVE_thrd_current) || defined(__CRT_HAVE_thr_self) || defined(__CRT_HAVE_cthread_self))) || ((defined(__CRT_HAVE_gettid) || defined(__CRT_HAVE___threadid) || defined(__CRT_HAVE_$QGetCurrentThreadId$Aplatform$Adetails$AConcurrency$A$AYAJXZ) || defined(__CRT_HAVE_pthread_getthreadid_np)) && (defined(__CRT_HAVE_getpid) || defined(__CRT_HAVE__getpid) || defined(__CRT_HAVE___getpid) || defined(__CRT_HAVE___libc_getpid)))
#include <libc/local/pthread/pthread_main_np.h>
/* >> pthread_main_np(3)
 * Returns  1 if the  calling thread is the  main() thread (i.e. the
 * thread  that was  started by the  kernel in order  to execute the
 * calling program), and 0  otherwise. Additionally, -1 is  returned
 * if the  calling  thread  "hasn't been initialized",  though  this
 * isn't a case that can actually happen under KOS's implementation. */
__NAMESPACE_LOCAL_USING_OR_IMPL(pthread_main_np, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL pthread_main_np)(void) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pthread_main_np))(); })
#else /* ... */
#undef __pthread_main_np_defined
#endif /* !... */
#endif /* !__pthread_main_np_defined */
#if !defined(__pthread_attr_getaffinity_np_defined) && defined(__CRT_HAVE_pthread_attr_getaffinity_np)
#define __pthread_attr_getaffinity_np_defined
/* >> pthread_attr_getaffinity_np(3)
 * Get cpuset on which the thread will be allowed to run
 * @return: EOK:    Success
 * @return: EINVAL: `cpusetsize' is too small */
__CDECLARE(__ATTR_IN(1) __ATTR_OUT_OPT(3),__errno_t,__NOTHROW_NCX,pthread_attr_getaffinity_np,(pthread_attr_t const *__self, size_t __cpusetsize, cpu_set_t *__cpuset),(__self,__cpusetsize,__cpuset))
#endif /* !__pthread_attr_getaffinity_np_defined && __CRT_HAVE_pthread_attr_getaffinity_np */
#ifndef __pthread_attr_setaffinity_np_defined
#define __pthread_attr_setaffinity_np_defined
#ifdef __CRT_HAVE_pthread_attr_setaffinity_np
/* >> pthread_attr_setaffinity_np(3)
 * Set cpuset on which the thread will be allowed to run
 * @return: EOK:    Success
 * @return: EINVAL: The given set contains a non-existent CPU
 * @return: ENOMEM: Insufficient memory */
__CDECLARE(__ATTR_INOUT(1) __ATTR_IN_OPT(3),__errno_t,__NOTHROW_NCX,pthread_attr_setaffinity_np,(pthread_attr_t *__self, size_t __cpusetsize, cpu_set_t const *__cpuset),(__self,__cpusetsize,__cpuset))
#elif defined(__CRT_HAVE___pthread_attr_setaffinity_np)
/* >> pthread_attr_setaffinity_np(3)
 * Set cpuset on which the thread will be allowed to run
 * @return: EOK:    Success
 * @return: EINVAL: The given set contains a non-existent CPU
 * @return: ENOMEM: Insufficient memory */
__CREDIRECT(__ATTR_INOUT(1) __ATTR_IN_OPT(3),__errno_t,__NOTHROW_NCX,pthread_attr_setaffinity_np,(pthread_attr_t *__self, size_t __cpusetsize, cpu_set_t const *__cpuset),__pthread_attr_setaffinity_np,(__self,__cpusetsize,__cpuset))
#else /* ... */
#undef __pthread_attr_setaffinity_np_defined
#endif /* !... */
#endif /* !__pthread_attr_setaffinity_np_defined */
#if !defined(__pthread_getaffinity_np_defined) && defined(__CRT_HAVE_pthread_getaffinity_np)
#define __pthread_getaffinity_np_defined
/* >> pthread_getaffinity_np(3)
 * Get bit set in `cpuset' representing the processors `self' can run on
 * @return: EOK:   Success
 * @return: ESRCH: `self' has already exited */
__CDECLARE(__ATTR_OUT_OPT(3),__errno_t,__NOTHROW_NCX,pthread_getaffinity_np,(pthread_t __self, size_t __cpusetsize, cpu_set_t *__cpuset),(__self,__cpusetsize,__cpuset))
#endif /* !__pthread_getaffinity_np_defined && __CRT_HAVE_pthread_getaffinity_np */
#ifdef __CRT_HAVE_pthread_resume_all_np
/* >> pthread_resume_all_np(3)
 * Calls `pthread_continue_np(3)' once for every running thread but the calling one.
 * This  function  essentially reverses  the effects  of `pthread_suspend_all_np(3)' */
__CREDIRECT(,__errno_t,__NOTHROW_NCX,pthread_multi_np,(void),pthread_resume_all_np,())
#elif defined(__CRT_HAVE_pthread_multi_np)
/* >> pthread_resume_all_np(3)
 * Calls `pthread_continue_np(3)' once for every running thread but the calling one.
 * This  function  essentially reverses  the effects  of `pthread_suspend_all_np(3)' */
__CDECLARE(,__errno_t,__NOTHROW_NCX,pthread_multi_np,(void),())
#endif /* ... */
#ifdef __CRT_HAVE_pthread_suspend_all_np
/* >> pthread_suspend_all_np(3)
 * Calls  `pthread_suspend_np(3)' once for every running thread but the calling one
 * After a call to this function, the calling thread is the only one running within
 * the current process (at least of those created by `pthread_create(3)')
 *
 * Signals directed at suspended thread will not be handled until that thread has
 * been resumed (s.a. `pthread_resume_all_np(3)')
 *
 * @return: EOK:       Success
 * @return: ENOMEM:    Insufficient memory
 * @return: EOVERFLOW: The suspension counter of some thread can't go any higher */
__CREDIRECT(,__errno_t,__NOTHROW_NCX,pthread_single_np,(void),pthread_suspend_all_np,())
#elif defined(__CRT_HAVE_pthread_single_np)
/* >> pthread_suspend_all_np(3)
 * Calls  `pthread_suspend_np(3)' once for every running thread but the calling one
 * After a call to this function, the calling thread is the only one running within
 * the current process (at least of those created by `pthread_create(3)')
 *
 * Signals directed at suspended thread will not be handled until that thread has
 * been resumed (s.a. `pthread_resume_all_np(3)')
 *
 * @return: EOK:       Success
 * @return: ENOMEM:    Insufficient memory
 * @return: EOVERFLOW: The suspension counter of some thread can't go any higher */
__CDECLARE(,__errno_t,__NOTHROW_NCX,pthread_single_np,(void),())
#endif /* ... */
#ifdef __CRT_HAVE_pthread_tryjoin_np
/* >> pthread_tryjoin_np(3)
 * Check whether thread  `self' has terminated.  If so return  the
 * status of the thread in `*thread_return', if `thread_return' is
 * not `NULL'.
 * @return: EOK:   Success
 * @return: EBUSY: The thread has yet to terminate */
__CREDIRECT(__ATTR_OUT_OPT(2),__errno_t,__NOTHROW_NCX,pthread_peekjoin_np,(pthread_t __self, void **__thread_return),pthread_tryjoin_np,(__self,__thread_return))
#elif defined(__CRT_HAVE_pthread_peekjoin_np)
/* >> pthread_tryjoin_np(3)
 * Check whether thread  `self' has terminated.  If so return  the
 * status of the thread in `*thread_return', if `thread_return' is
 * not `NULL'.
 * @return: EOK:   Success
 * @return: EBUSY: The thread has yet to terminate */
__CDECLARE(__ATTR_OUT_OPT(2),__errno_t,__NOTHROW_NCX,pthread_peekjoin_np,(pthread_t __self, void **__thread_return),(__self,__thread_return))
#endif /* ... */
#if !defined(__pthread_setaffinity_np_defined) && defined(__CRT_HAVE_pthread_setaffinity_np)
#define __pthread_setaffinity_np_defined
/* >> pthread_setaffinity_np(3)
 * Limit specified thread `self' to run only on the processors represented in `cpuset'
 * @return: EOK:   Success
 * @return: ESRCH: `self' has already exited */
__CDECLARE(__ATTR_IN_OPT(3),__errno_t,__NOTHROW_NCX,pthread_setaffinity_np,(pthread_t __self, size_t __cpusetsize, cpu_set_t const *__cpuset),(__self,__cpusetsize,__cpuset))
#endif /* !__pthread_setaffinity_np_defined && __CRT_HAVE_pthread_setaffinity_np */
#ifndef __pthread_timedjoin_np_defined
#define __pthread_timedjoin_np_defined
#include <features.h>
#if defined(__CRT_HAVE_pthread_timedjoin_np) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> pthread_timedjoin_np(3), pthread_timedjoin64_np(3)
 * Make calling thread  wait for termination  of the thread  `self',
 * but only until `timeout'. The exit status of the thread is stored
 * in  `*thread_return',   if   `thread_return'   is   not   `NULL'.
 * @return: EOK:       Success
 * @return: EINVAL:    The given `abstime' is invalid
 * @return: ETIMEDOUT: The given `abstime' has expired */
__CDECLARE(__ATTR_IN_OPT(3) __ATTR_OUT_OPT(2),__errno_t,__NOTHROW_RPC,pthread_timedjoin_np,(pthread_t __self, void **__thread_return, struct timespec const *__abstime),(__self,__thread_return,__abstime))
#elif defined(__CRT_HAVE_pthread_timedjoin64_np) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> pthread_timedjoin_np(3), pthread_timedjoin64_np(3)
 * Make calling thread  wait for termination  of the thread  `self',
 * but only until `timeout'. The exit status of the thread is stored
 * in  `*thread_return',   if   `thread_return'   is   not   `NULL'.
 * @return: EOK:       Success
 * @return: EINVAL:    The given `abstime' is invalid
 * @return: ETIMEDOUT: The given `abstime' has expired */
__CREDIRECT(__ATTR_IN_OPT(3) __ATTR_OUT_OPT(2),__errno_t,__NOTHROW_RPC,pthread_timedjoin_np,(pthread_t __self, void **__thread_return, struct timespec const *__abstime),pthread_timedjoin64_np,(__self,__thread_return,__abstime))
#elif defined(__CRT_HAVE___pthread_timedjoin_np64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> pthread_timedjoin_np(3), pthread_timedjoin64_np(3)
 * Make calling thread  wait for termination  of the thread  `self',
 * but only until `timeout'. The exit status of the thread is stored
 * in  `*thread_return',   if   `thread_return'   is   not   `NULL'.
 * @return: EOK:       Success
 * @return: EINVAL:    The given `abstime' is invalid
 * @return: ETIMEDOUT: The given `abstime' has expired */
__CREDIRECT(__ATTR_IN_OPT(3) __ATTR_OUT_OPT(2),__errno_t,__NOTHROW_RPC,pthread_timedjoin_np,(pthread_t __self, void **__thread_return, struct timespec const *__abstime),__pthread_timedjoin_np64,(__self,__thread_return,__abstime))
#elif defined(__CRT_HAVE_pthread_timedjoin64_np) || defined(__CRT_HAVE___pthread_timedjoin_np64) || defined(__CRT_HAVE_pthread_timedjoin_np)
#include <libc/local/pthread/pthread_timedjoin_np.h>
/* >> pthread_timedjoin_np(3), pthread_timedjoin64_np(3)
 * Make calling thread  wait for termination  of the thread  `self',
 * but only until `timeout'. The exit status of the thread is stored
 * in  `*thread_return',   if   `thread_return'   is   not   `NULL'.
 * @return: EOK:       Success
 * @return: EINVAL:    The given `abstime' is invalid
 * @return: ETIMEDOUT: The given `abstime' has expired */
__NAMESPACE_LOCAL_USING_OR_IMPL(pthread_timedjoin_np, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN_OPT(3) __ATTR_OUT_OPT(2) __errno_t __NOTHROW_RPC(__LIBCCALL pthread_timedjoin_np)(pthread_t __self, void **__thread_return, struct timespec const *__abstime) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pthread_timedjoin_np))(__self, __thread_return, __abstime); })
#else /* ... */
#undef __pthread_timedjoin_np_defined
#endif /* !... */
#endif /* !__pthread_timedjoin_np_defined */
#ifndef __pthread_timedjoin64_np_defined
#define __pthread_timedjoin64_np_defined
#if defined(__CRT_HAVE_pthread_timedjoin_np) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> pthread_timedjoin_np(3), pthread_timedjoin64_np(3)
 * Make calling thread  wait for termination  of the thread  `self',
 * but only until `timeout'. The exit status of the thread is stored
 * in  `*thread_return',   if   `thread_return'   is   not   `NULL'.
 * @return: EOK:       Success
 * @return: EINVAL:    The given `abstime' is invalid
 * @return: ETIMEDOUT: The given `abstime' has expired */
__CREDIRECT(__ATTR_IN_OPT(3) __ATTR_OUT_OPT(2),__errno_t,__NOTHROW_RPC,pthread_timedjoin64_np,(pthread_t __self, void **__thread_return, struct timespec64 const *__abstime),pthread_timedjoin_np,(__self,__thread_return,__abstime))
#elif defined(__CRT_HAVE_pthread_timedjoin64_np)
/* >> pthread_timedjoin_np(3), pthread_timedjoin64_np(3)
 * Make calling thread  wait for termination  of the thread  `self',
 * but only until `timeout'. The exit status of the thread is stored
 * in  `*thread_return',   if   `thread_return'   is   not   `NULL'.
 * @return: EOK:       Success
 * @return: EINVAL:    The given `abstime' is invalid
 * @return: ETIMEDOUT: The given `abstime' has expired */
__CDECLARE(__ATTR_IN_OPT(3) __ATTR_OUT_OPT(2),__errno_t,__NOTHROW_RPC,pthread_timedjoin64_np,(pthread_t __self, void **__thread_return, struct timespec64 const *__abstime),(__self,__thread_return,__abstime))
#elif defined(__CRT_HAVE___pthread_timedjoin_np64)
/* >> pthread_timedjoin_np(3), pthread_timedjoin64_np(3)
 * Make calling thread  wait for termination  of the thread  `self',
 * but only until `timeout'. The exit status of the thread is stored
 * in  `*thread_return',   if   `thread_return'   is   not   `NULL'.
 * @return: EOK:       Success
 * @return: EINVAL:    The given `abstime' is invalid
 * @return: ETIMEDOUT: The given `abstime' has expired */
__CREDIRECT(__ATTR_IN_OPT(3) __ATTR_OUT_OPT(2),__errno_t,__NOTHROW_RPC,pthread_timedjoin64_np,(pthread_t __self, void **__thread_return, struct timespec64 const *__abstime),__pthread_timedjoin_np64,(__self,__thread_return,__abstime))
#elif defined(__CRT_HAVE_pthread_timedjoin_np)
#include <libc/local/pthread/pthread_timedjoin64_np.h>
/* >> pthread_timedjoin_np(3), pthread_timedjoin64_np(3)
 * Make calling thread  wait for termination  of the thread  `self',
 * but only until `timeout'. The exit status of the thread is stored
 * in  `*thread_return',   if   `thread_return'   is   not   `NULL'.
 * @return: EOK:       Success
 * @return: EINVAL:    The given `abstime' is invalid
 * @return: ETIMEDOUT: The given `abstime' has expired */
__NAMESPACE_LOCAL_USING_OR_IMPL(pthread_timedjoin64_np, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN_OPT(3) __ATTR_OUT_OPT(2) __errno_t __NOTHROW_RPC(__LIBCCALL pthread_timedjoin64_np)(pthread_t __self, void **__thread_return, struct timespec64 const *__abstime) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pthread_timedjoin64_np))(__self, __thread_return, __abstime); })
#else /* ... */
#undef __pthread_timedjoin64_np_defined
#endif /* !... */
#endif /* !__pthread_timedjoin64_np_defined */
#ifdef __CRT_HAVE_gettid
/* >> gettid(2)
 * Return the TID of the calling thread
 * THIS_THREAD->PID */
__CREDIRECT(,pthread_id_np_t,__NOTHROW_NCX,pthread_getthreadid_np,(void),gettid,())
#elif defined(__CRT_HAVE___threadid)
/* >> gettid(2)
 * Return the TID of the calling thread
 * THIS_THREAD->PID */
__CREDIRECT(,pthread_id_np_t,__NOTHROW_NCX,pthread_getthreadid_np,(void),__threadid,())
#elif defined(__CRT_HAVE_$QGetCurrentThreadId$Aplatform$Adetails$AConcurrency$A$AYAJXZ)
/* >> gettid(2)
 * Return the TID of the calling thread
 * THIS_THREAD->PID */
__CREDIRECT(,pthread_id_np_t,__NOTHROW_NCX,pthread_getthreadid_np,(void),?GetCurrentThreadId@platform@details@Concurrency@@YAJXZ,())
#elif defined(__CRT_HAVE_pthread_getthreadid_np)
/* >> gettid(2)
 * Return the TID of the calling thread
 * THIS_THREAD->PID */
__CDECLARE(,pthread_id_np_t,__NOTHROW_NCX,pthread_getthreadid_np,(void),())
#endif /* ... */
#ifdef __CRT_HAVE_pthread_stackseg_np
/* >> pthread_stackseg_np(3)
 * Convenience wrapper for `pthread_getattr_np(3)' + `pthread_attr_getstack()' */
__CDECLARE(__ATTR_OUT(2),__errno_t,__NOTHROW_NCX,pthread_stackseg_np,(pthread_t __self, stack_t *__sinfo),(__self,__sinfo))
#elif (defined(__CRT_HAVE_pthread_getattr_np) || defined(__CRT_HAVE_pthread_attr_get_np)) && (defined(__CRT_HAVE_pthread_attr_getstack) || (defined(__CRT_HAVE_pthread_attr_getstackaddr) && defined(__CRT_HAVE_pthread_attr_getstacksize)))
#include <libc/local/pthread_np/pthread_stackseg_np.h>
/* >> pthread_stackseg_np(3)
 * Convenience wrapper for `pthread_getattr_np(3)' + `pthread_attr_getstack()' */
__NAMESPACE_LOCAL_USING_OR_IMPL(pthread_stackseg_np, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_OUT(2) __errno_t __NOTHROW_NCX(__LIBCCALL pthread_stackseg_np)(pthread_t __self, stack_t *__sinfo) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pthread_stackseg_np))(__self, __sinfo); })
#endif /* ... */
#ifndef __pthread_attr_setcreatesuspend_np_defined
#define __pthread_attr_setcreatesuspend_np_defined
#ifdef __CRT_HAVE_pthread_attr_setcreatesuspend_np
/* >> pthread_attr_setcreatesuspend_np(3)
 * Setup `self' such that created threads start in a "suspended" state,
 * requiring a call to one of the following function to actually start:
 *  - `pthread_continue_np(3)' (or `pthread_unsuspend_np(3)')
 *  - `pthread_resume_np(3)'
 *  - `pthread_resume_all_np(3)'
 * Alias for `pthread_attr_setstartsuspended_np(self, 1)'
 * @return: EOK: Always returned */
__CDECLARE(__ATTR_INOUT(1),__errno_t,__NOTHROW_NCX,pthread_attr_setcreatesuspend_np,(pthread_attr_t *__restrict __self),(__self))
#elif defined(__CRT_HAVE_pthread_attr_setstartsuspended_np)
#include <libc/local/pthread/pthread_attr_setcreatesuspend_np.h>
/* >> pthread_attr_setcreatesuspend_np(3)
 * Setup `self' such that created threads start in a "suspended" state,
 * requiring a call to one of the following function to actually start:
 *  - `pthread_continue_np(3)' (or `pthread_unsuspend_np(3)')
 *  - `pthread_resume_np(3)'
 *  - `pthread_resume_all_np(3)'
 * Alias for `pthread_attr_setstartsuspended_np(self, 1)'
 * @return: EOK: Always returned */
__NAMESPACE_LOCAL_USING_OR_IMPL(pthread_attr_setcreatesuspend_np, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT(1) __errno_t __NOTHROW_NCX(__LIBCCALL pthread_attr_setcreatesuspend_np)(pthread_attr_t *__restrict __self) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pthread_attr_setcreatesuspend_np))(__self); })
#else /* ... */
#undef __pthread_attr_setcreatesuspend_np_defined
#endif /* !... */
#endif /* !__pthread_attr_setcreatesuspend_np_defined */
#ifndef __pthread_suspend_np_defined
#define __pthread_suspend_np_defined
#ifdef __CRT_HAVE_pthread_suspend_np
/* >> pthread_suspend_np(3)
 * Increment the given thread's suspend-counter. If the counter was `0' before,
 * then the thread is suspended and this function only returns once the  thread
 * has stopped executing code.
 *
 * Signals directed at suspended thread will not be handled until that thread has
 * been  resumed  (s.a.  `pthread_resume_np(3)'  and   `pthread_unsuspend_np(3)')
 *
 * @see pthread_suspend2_np
 * @return: EOK:       Success
 * @return: ESRCH:     The thread has already been terminated
 * @return: ENOMEM:    Insufficient memory
 * @return: EOVERFLOW: The suspension counter can't go any higher */
__CDECLARE(,__errno_t,__NOTHROW_NCX,pthread_suspend_np,(pthread_t __self),(__self))
#elif defined(__CRT_HAVE_thr_suspend)
/* >> pthread_suspend_np(3)
 * Increment the given thread's suspend-counter. If the counter was `0' before,
 * then the thread is suspended and this function only returns once the  thread
 * has stopped executing code.
 *
 * Signals directed at suspended thread will not be handled until that thread has
 * been  resumed  (s.a.  `pthread_resume_np(3)'  and   `pthread_unsuspend_np(3)')
 *
 * @see pthread_suspend2_np
 * @return: EOK:       Success
 * @return: ESRCH:     The thread has already been terminated
 * @return: ENOMEM:    Insufficient memory
 * @return: EOVERFLOW: The suspension counter can't go any higher */
__CREDIRECT(,__errno_t,__NOTHROW_NCX,pthread_suspend_np,(pthread_t __self),thr_suspend,(__self))
#elif defined(__CRT_HAVE_pthread_suspend2_np)
#include <libc/local/pthread/pthread_suspend_np.h>
/* >> pthread_suspend_np(3)
 * Increment the given thread's suspend-counter. If the counter was `0' before,
 * then the thread is suspended and this function only returns once the  thread
 * has stopped executing code.
 *
 * Signals directed at suspended thread will not be handled until that thread has
 * been  resumed  (s.a.  `pthread_resume_np(3)'  and   `pthread_unsuspend_np(3)')
 *
 * @see pthread_suspend2_np
 * @return: EOK:       Success
 * @return: ESRCH:     The thread has already been terminated
 * @return: ENOMEM:    Insufficient memory
 * @return: EOVERFLOW: The suspension counter can't go any higher */
__NAMESPACE_LOCAL_USING_OR_IMPL(pthread_suspend_np, __FORCELOCAL __ATTR_ARTIFICIAL __errno_t __NOTHROW_NCX(__LIBCCALL pthread_suspend_np)(pthread_t __self) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pthread_suspend_np))(__self); })
#else /* ... */
#undef __pthread_suspend_np_defined
#endif /* !... */
#endif /* !__pthread_suspend_np_defined */
#ifndef __pthread_resume_np_defined
#define __pthread_resume_np_defined
#ifdef __CRT_HAVE_pthread_resume_np
/* >> pthread_suspend_np(3)
 * Decrement the given thread's suspend-counter. If the counter was already `0',
 * then  the calls is a no-op (and `EOK').  If the counter was `1', execution of
 * the thread is allowed to  continue (or start for the  first time in case  the
 * thread was created with `pthread_attr_setstartsuspended_np(3)' set to 1).
 *
 * @see pthread_suspend_np, pthread_suspend2_np, pthread_resume2_np, pthread_continue_np
 * @return: EOK:   Success
 * @return: ESRCH: The thread has already been terminated */
__CDECLARE(,__errno_t,__NOTHROW_NCX,pthread_resume_np,(pthread_t __self),(__self))
#elif defined(__CRT_HAVE_pthread_resume2_np)
#include <libc/local/pthread/pthread_resume_np.h>
/* >> pthread_suspend_np(3)
 * Decrement the given thread's suspend-counter. If the counter was already `0',
 * then  the calls is a no-op (and `EOK').  If the counter was `1', execution of
 * the thread is allowed to  continue (or start for the  first time in case  the
 * thread was created with `pthread_attr_setstartsuspended_np(3)' set to 1).
 *
 * @see pthread_suspend_np, pthread_suspend2_np, pthread_resume2_np, pthread_continue_np
 * @return: EOK:   Success
 * @return: ESRCH: The thread has already been terminated */
__NAMESPACE_LOCAL_USING_OR_IMPL(pthread_resume_np, __FORCELOCAL __ATTR_ARTIFICIAL __errno_t __NOTHROW_NCX(__LIBCCALL pthread_resume_np)(pthread_t __self) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pthread_resume_np))(__self); })
#else /* ... */
#undef __pthread_resume_np_defined
#endif /* !... */
#endif /* !__pthread_resume_np_defined */
#ifndef __pthread_continue_np_defined
#define __pthread_continue_np_defined
#ifdef __CRT_HAVE_pthread_continue_np
/* >> pthread_continue_np(3), pthread_unsuspend_np(3)
 * Set the given thread's suspend-counter to `0'. If the counter was already `0',
 * then the calls is a no-op (and  `EOK'). Otherwise, execution of the thread  is
 * allowed  to  continue (or  start for  the first  time in  case the  thread was
 * created with `pthread_attr_setstartsuspended_np(3)' set to 1).
 *
 * @see pthread_suspend_np, pthread_suspend2_np, pthread_resume2_np, pthread_resume_np
 * @return: EOK:   Success
 * @return: ESRCH: The thread has already been terminated */
__CDECLARE(,__errno_t,__NOTHROW_NCX,pthread_continue_np,(pthread_t __self),(__self))
#elif defined(__CRT_HAVE_thr_continue)
/* >> pthread_continue_np(3), pthread_unsuspend_np(3)
 * Set the given thread's suspend-counter to `0'. If the counter was already `0',
 * then the calls is a no-op (and  `EOK'). Otherwise, execution of the thread  is
 * allowed  to  continue (or  start for  the first  time in  case the  thread was
 * created with `pthread_attr_setstartsuspended_np(3)' set to 1).
 *
 * @see pthread_suspend_np, pthread_suspend2_np, pthread_resume2_np, pthread_resume_np
 * @return: EOK:   Success
 * @return: ESRCH: The thread has already been terminated */
__CREDIRECT(,__errno_t,__NOTHROW_NCX,pthread_continue_np,(pthread_t __self),thr_continue,(__self))
#elif defined(__CRT_HAVE_pthread_unsuspend_np)
/* >> pthread_continue_np(3), pthread_unsuspend_np(3)
 * Set the given thread's suspend-counter to `0'. If the counter was already `0',
 * then the calls is a no-op (and  `EOK'). Otherwise, execution of the thread  is
 * allowed  to  continue (or  start for  the first  time in  case the  thread was
 * created with `pthread_attr_setstartsuspended_np(3)' set to 1).
 *
 * @see pthread_suspend_np, pthread_suspend2_np, pthread_resume2_np, pthread_resume_np
 * @return: EOK:   Success
 * @return: ESRCH: The thread has already been terminated */
__CREDIRECT(,__errno_t,__NOTHROW_NCX,pthread_continue_np,(pthread_t __self),pthread_unsuspend_np,(__self))
#else /* ... */
#undef __pthread_continue_np_defined
#endif /* !... */
#endif /* !__pthread_continue_np_defined */
#ifndef __pthread_unsuspend_np_defined
#define __pthread_unsuspend_np_defined
#ifdef __CRT_HAVE_pthread_continue_np
/* >> pthread_continue_np(3), pthread_unsuspend_np(3)
 * Set the given thread's suspend-counter to `0'. If the counter was already `0',
 * then the calls is a no-op (and  `EOK'). Otherwise, execution of the thread  is
 * allowed  to  continue (or  start for  the first  time in  case the  thread was
 * created with `pthread_attr_setstartsuspended_np(3)' set to 1).
 *
 * @see pthread_suspend_np, pthread_suspend2_np, pthread_resume2_np, pthread_resume_np
 * @return: EOK:   Success
 * @return: ESRCH: The thread has already been terminated */
__CREDIRECT(,__errno_t,__NOTHROW_NCX,pthread_unsuspend_np,(pthread_t __self),pthread_continue_np,(__self))
#elif defined(__CRT_HAVE_thr_continue)
/* >> pthread_continue_np(3), pthread_unsuspend_np(3)
 * Set the given thread's suspend-counter to `0'. If the counter was already `0',
 * then the calls is a no-op (and  `EOK'). Otherwise, execution of the thread  is
 * allowed  to  continue (or  start for  the first  time in  case the  thread was
 * created with `pthread_attr_setstartsuspended_np(3)' set to 1).
 *
 * @see pthread_suspend_np, pthread_suspend2_np, pthread_resume2_np, pthread_resume_np
 * @return: EOK:   Success
 * @return: ESRCH: The thread has already been terminated */
__CREDIRECT(,__errno_t,__NOTHROW_NCX,pthread_unsuspend_np,(pthread_t __self),thr_continue,(__self))
#elif defined(__CRT_HAVE_pthread_unsuspend_np)
/* >> pthread_continue_np(3), pthread_unsuspend_np(3)
 * Set the given thread's suspend-counter to `0'. If the counter was already `0',
 * then the calls is a no-op (and  `EOK'). Otherwise, execution of the thread  is
 * allowed  to  continue (or  start for  the first  time in  case the  thread was
 * created with `pthread_attr_setstartsuspended_np(3)' set to 1).
 *
 * @see pthread_suspend_np, pthread_suspend2_np, pthread_resume2_np, pthread_resume_np
 * @return: EOK:   Success
 * @return: ESRCH: The thread has already been terminated */
__CDECLARE(,__errno_t,__NOTHROW_NCX,pthread_unsuspend_np,(pthread_t __self),(__self))
#else /* ... */
#undef __pthread_unsuspend_np_defined
#endif /* !... */
#endif /* !__pthread_unsuspend_np_defined */
#ifndef __pthread_suspend_all_np_defined
#define __pthread_suspend_all_np_defined
#ifdef __CRT_HAVE_pthread_suspend_all_np
/* >> pthread_suspend_all_np(3)
 * Calls  `pthread_suspend_np(3)' once for every running thread but the calling one
 * After a call to this function, the calling thread is the only one running within
 * the current process (at least of those created by `pthread_create(3)')
 *
 * Signals directed at suspended thread will not be handled until that thread has
 * been resumed (s.a. `pthread_resume_all_np(3)')
 *
 * @return: EOK:       Success
 * @return: ENOMEM:    Insufficient memory
 * @return: EOVERFLOW: The suspension counter of some thread can't go any higher */
__CDECLARE(,__errno_t,__NOTHROW_NCX,pthread_suspend_all_np,(void),())
#elif defined(__CRT_HAVE_pthread_single_np)
/* >> pthread_suspend_all_np(3)
 * Calls  `pthread_suspend_np(3)' once for every running thread but the calling one
 * After a call to this function, the calling thread is the only one running within
 * the current process (at least of those created by `pthread_create(3)')
 *
 * Signals directed at suspended thread will not be handled until that thread has
 * been resumed (s.a. `pthread_resume_all_np(3)')
 *
 * @return: EOK:       Success
 * @return: ENOMEM:    Insufficient memory
 * @return: EOVERFLOW: The suspension counter of some thread can't go any higher */
__CREDIRECT(,__errno_t,__NOTHROW_NCX,pthread_suspend_all_np,(void),pthread_single_np,())
#else /* ... */
#undef __pthread_suspend_all_np_defined
#endif /* !... */
#endif /* !__pthread_suspend_all_np_defined */
#ifndef __pthread_resume_all_np_defined
#define __pthread_resume_all_np_defined
#ifdef __CRT_HAVE_pthread_resume_all_np
/* >> pthread_resume_all_np(3)
 * Calls `pthread_continue_np(3)' once for every running thread but the calling one.
 * This  function  essentially reverses  the effects  of `pthread_suspend_all_np(3)' */
__CDECLARE(,__errno_t,__NOTHROW_NCX,pthread_resume_all_np,(void),())
#elif defined(__CRT_HAVE_pthread_multi_np)
/* >> pthread_resume_all_np(3)
 * Calls `pthread_continue_np(3)' once for every running thread but the calling one.
 * This  function  essentially reverses  the effects  of `pthread_suspend_all_np(3)' */
__CREDIRECT(,__errno_t,__NOTHROW_NCX,pthread_resume_all_np,(void),pthread_multi_np,())
#else /* ... */
#undef __pthread_resume_all_np_defined
#endif /* !... */
#endif /* !__pthread_resume_all_np_defined */
#ifdef __CRT_HAVE_pthread_getunique_np
/* >> pthread_getunique_np(3)
 * Wrapper around `pthread_gettid_np(3)' that is also available on some other platforms. */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,__errno_t,__NOTHROW_NCX,pthread_getunique_np,(pthread_t __self, pthread_id_np_t *__ptid),(__self,__ptid))
#elif defined(__CRT_HAVE_pthread_threadid_np)
/* >> pthread_getunique_np(3)
 * Wrapper around `pthread_gettid_np(3)' that is also available on some other platforms. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,__errno_t,__NOTHROW_NCX,pthread_getunique_np,(pthread_t __self, pthread_id_np_t *__ptid),pthread_threadid_np,(__self,__ptid))
#elif defined(__CRT_HAVE_pthread_gettid_np)
#include <libc/local/pthread/pthread_getunique_np.h>
/* >> pthread_getunique_np(3)
 * Wrapper around `pthread_gettid_np(3)' that is also available on some other platforms. */
__NAMESPACE_LOCAL_USING_OR_IMPL(pthread_getunique_np, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __errno_t __NOTHROW_NCX(__LIBCCALL pthread_getunique_np)(pthread_t __self, pthread_id_np_t *__ptid) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pthread_getunique_np))(__self, __ptid); })
#endif /* ... */
/* >> pthread_mutex_isowned_np(3)
 * Check if the calling thread is holding a lock to `mutex' (for use by assertions)
 * @return: 1 : Yes, you are holding a lock to `mutex'
 * @return: 0 : Either `mutex' isn't locked, or it isn't you that's holding the lock */
__CDECLARE_OPT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),int,__NOTHROW_NCX,pthread_mutex_isowned_np,(pthread_mutex_t __KOS_FIXED_CONST *__mutex),(__mutex))
#ifdef __CRT_HAVE_pthread_switch_add_np
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1)),__errno_t,__NOTHROW_NCX,pthread_switch_add_np,(pthread_switch_routine_t __routine),(__routine))
#else /* __CRT_HAVE_pthread_switch_add_np */
#include <libc/local/pthread/pthread_switch_add_np.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(pthread_switch_add_np, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __errno_t __NOTHROW_NCX(__LIBCCALL pthread_switch_add_np)(pthread_switch_routine_t __routine) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pthread_switch_add_np))(__routine); })
#endif /* !__CRT_HAVE_pthread_switch_add_np */
#ifdef __CRT_HAVE_pthread_switch_delete_np
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1)),__errno_t,__NOTHROW_NCX,pthread_switch_delete_np,(pthread_switch_routine_t __routine),(__routine))
#else /* __CRT_HAVE_pthread_switch_delete_np */
#include <libc/local/pthread/pthread_switch_delete_np.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(pthread_switch_delete_np, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __errno_t __NOTHROW_NCX(__LIBCCALL pthread_switch_delete_np)(pthread_switch_routine_t __routine) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pthread_switch_delete_np))(__routine); })
#endif /* !__CRT_HAVE_pthread_switch_delete_np */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_PTHREAD_NP_H */
