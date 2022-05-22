/* HASH CRC-32:0x7e721d38 */
/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
/* (#) Portability: FreeBSD (/include/pthread_np.h) */
/* (#) Portability: OpenBSD (/include/pthread_np.h) */
#ifndef _PTHREAD_NP_H
#define _PTHREAD_NP_H 1

#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <bits/os/sigstack.h>
#include <pthread.h>


#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __pthread_switch_routine_t_defined
#define __pthread_switch_routine_t_defined
typedef void (__LIBKCALL *pthread_switch_routine_t)(pthread_t, pthread_t);
#endif /* !__pthread_switch_routine_t_defined */

#ifndef __stack_t_defined
#define __stack_t_defined
typedef struct sigaltstack stack_t;
#endif /* !__stack_t_defined */

#ifdef __CRT_HAVE_pthread_mutexattr_gettype
/* >> pthread_mutexattr_gettype(3)
 * Return in `*kind' the mutex kind attribute in `*attr'
 * @return: EOK: Success */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),__errno_t,__NOTHROW_NCX,pthread_mutexattr_getkind_np,(pthread_mutexattr_t const *__restrict __attr, int *__restrict __kind),pthread_mutexattr_gettype,(__attr,__kind))
#elif defined(__CRT_HAVE_pthread_mutexattr_getkind_np)
/* >> pthread_mutexattr_gettype(3)
 * Return in `*kind' the mutex kind attribute in `*attr'
 * @return: EOK: Success */
__CDECLARE(__ATTR_IN(1) __ATTR_OUT(2),__errno_t,__NOTHROW_NCX,pthread_mutexattr_getkind_np,(pthread_mutexattr_t const *__restrict __attr, int *__restrict __kind),(__attr,__kind))
#endif /* ... */
#ifdef __CRT_HAVE_pthread_mutexattr_settype
/* >> pthread_mutexattr_settype(3)
 * Set  the mutex kind attribute in `*attr' to `kind' (either `PTHREAD_MUTEX_NORMAL',
 * `PTHREAD_MUTEX_RECURSIVE', `PTHREAD_MUTEX_ERRORCHECK', or `PTHREAD_MUTEX_DEFAULT')
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `kind' */
__CREDIRECT(__ATTR_INOUT(1),__errno_t,__NOTHROW_NCX,pthread_mutexattr_setkind_np,(pthread_mutexattr_t *__attr, int __kind),pthread_mutexattr_settype,(__attr,__kind))
#elif defined(__CRT_HAVE_pthread_mutexattr_setkind_np)
/* >> pthread_mutexattr_settype(3)
 * Set  the mutex kind attribute in `*attr' to `kind' (either `PTHREAD_MUTEX_NORMAL',
 * `PTHREAD_MUTEX_RECURSIVE', `PTHREAD_MUTEX_ERRORCHECK', or `PTHREAD_MUTEX_DEFAULT')
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `kind' */
__CDECLARE(__ATTR_INOUT(1),__errno_t,__NOTHROW_NCX,pthread_mutexattr_setkind_np,(pthread_mutexattr_t *__attr, int __kind),(__attr,__kind))
#endif /* ... */
#ifdef __CRT_HAVE_pthread_getname_np
/* >> pthread_getname_np(3)
 * Get thread name visible in the kernel and its interfaces
 * @return: EOK:    Success
 * @return: ERANGE: The given `buflen' is too small */
__CREDIRECT(__ATTR_OUTS(2, 3),__errno_t,__NOTHROW_NCX,pthread_get_name_np,(pthread_t __target_thread, char *__buf, size_t __buflen),pthread_getname_np,(__target_thread,__buf,__buflen))
#elif defined(__CRT_HAVE_pthread_get_name_np)
/* >> pthread_getname_np(3)
 * Get thread name visible in the kernel and its interfaces
 * @return: EOK:    Success
 * @return: ERANGE: The given `buflen' is too small */
__CDECLARE(__ATTR_OUTS(2, 3),__errno_t,__NOTHROW_NCX,pthread_get_name_np,(pthread_t __target_thread, char *__buf, size_t __buflen),(__target_thread,__buf,__buflen))
#endif /* ... */
#ifdef __CRT_HAVE_pthread_setname_np
/* >> pthread_setname_np(3)
 * Set thread name visible in the kernel and its interfaces
 * @return: EOK:    Success
 * @return: ERANGE: The given `name' is too long */
__CREDIRECT(__ATTR_IN(2),__errno_t,__NOTHROW_NCX,pthread_set_name_np,(pthread_t __target_thread, const char *__name),pthread_setname_np,(__target_thread,__name))
#elif defined(__CRT_HAVE_pthread_set_name_np)
/* >> pthread_setname_np(3)
 * Set thread name visible in the kernel and its interfaces
 * @return: EOK:    Success
 * @return: ERANGE: The given `name' is too long */
__CDECLARE(__ATTR_IN(2),__errno_t,__NOTHROW_NCX,pthread_set_name_np,(pthread_t __target_thread, const char *__name),(__target_thread,__name))
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
#elif (defined(__CRT_HAVE_pthread_mainthread_np) && (defined(__CRT_HAVE_pthread_self) || defined(__CRT_HAVE_thrd_current) || defined(__CRT_HAVE_thr_self))) || ((defined(__CRT_HAVE_gettid) || defined(__CRT_HAVE___threadid) || defined(__CRT_HAVE_$QGetCurrentThreadId$Aplatform$Adetails$AConcurrency$A$AYAJXZ)) && (defined(__CRT_HAVE_getpid) || defined(__CRT_HAVE__getpid) || defined(__CRT_HAVE___getpid) || defined(__CRT_HAVE___libc_getpid)))
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
#ifdef __CRT_HAVE_pthread_stackseg_np
/* >> pthread_stackseg_np(3)
 * Convenience wrapper for `pthread_getattr_np(3)' + `pthread_attr_getstack()' */
__CDECLARE(__ATTR_OUT(2),__errno_t,__NOTHROW_NCX,pthread_stackseg_np,(pthread_t __pthread, stack_t *__sinfo),(__pthread,__sinfo))
#elif defined(__CRT_HAVE_pthread_getattr_np) && (defined(__CRT_HAVE_pthread_attr_getstack) || (defined(__CRT_HAVE_pthread_attr_getstackaddr) && defined(__CRT_HAVE_pthread_attr_getstacksize)))
#include <libc/local/pthread_np/pthread_stackseg_np.h>
/* >> pthread_stackseg_np(3)
 * Convenience wrapper for `pthread_getattr_np(3)' + `pthread_attr_getstack()' */
__NAMESPACE_LOCAL_USING_OR_IMPL(pthread_stackseg_np, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_OUT(2) __errno_t __NOTHROW_NCX(__LIBCCALL pthread_stackseg_np)(pthread_t __pthread, stack_t *__sinfo) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pthread_stackseg_np))(__pthread, __sinfo); })
#endif /* ... */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_PTHREAD_NP_H */
