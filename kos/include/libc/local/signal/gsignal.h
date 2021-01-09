/* HASH CRC-32:0xc3e70cb2 */
/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_gsignal_defined
#define __local_gsignal_defined 1
#include <__crt.h>
#if defined(__CRT_HAVE_raise) || (defined(__CRT_HAVE_pthread_kill) && (defined(__CRT_HAVE_pthread_self) || defined(__CRT_HAVE_thrd_current))) || (defined(__CRT_HAVE_kill) && (defined(__CRT_HAVE_getpid) || defined(__CRT_HAVE__getpid) || defined(__CRT_HAVE___getpid)))
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: raise from signal */
#ifndef __local___localdep_raise_defined
#define __local___localdep_raise_defined 1
#ifdef __CRT_HAVE_raise
/* >> raise(3)
 * Raise a signal within the current thread.
 * In a *-theaded process this is same as:
 *   *=multi:  `pthread_kill(pthread_self(), signo)'
 *   *=single: `kill(getpid(), signo)'
 * @return: 0:  Success
 * @return: -1: [errno=EINVAL] The given `signo' is invalid */
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_raise,(__signo_t __signo),raise,(__signo))
#elif (defined(__CRT_HAVE_pthread_kill) && (defined(__CRT_HAVE_pthread_self) || defined(__CRT_HAVE_thrd_current))) || (defined(__CRT_HAVE_kill) && (defined(__CRT_HAVE_getpid) || defined(__CRT_HAVE__getpid) || defined(__CRT_HAVE___getpid)))
__NAMESPACE_LOCAL_END
#include <libc/local/signal/raise.h>
__NAMESPACE_LOCAL_BEGIN
/* >> raise(3)
 * Raise a signal within the current thread.
 * In a *-theaded process this is same as:
 *   *=multi:  `pthread_kill(pthread_self(), signo)'
 *   *=single: `kill(getpid(), signo)'
 * @return: 0:  Success
 * @return: -1: [errno=EINVAL] The given `signo' is invalid */
#define __localdep_raise __LIBC_LOCAL_NAME(raise)
#else /* ... */
#undef __local___localdep_raise_defined
#endif /* !... */
#endif /* !__local___localdep_raise_defined */
/* >> gsignal(3)
 * Raise a software-signal by invocing a previously established
 * software-signal-handler, as set by `ssignal(signo, ...)'.
 * This method by which a software signal is raised may or may not
 * be distinct from normal signal handlers.
 * On KOS, this function behaves identical to `raise()'
 * @return: 0:  Success
 * @return: -1: [errno=EINVAL] The given `signo' is invalid */
__LOCAL_LIBC(gsignal) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(gsignal))(__signo_t __signo) {
	return __localdep_raise(__signo);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_gsignal_defined
#define __local___localdep_gsignal_defined 1
#define __localdep_gsignal __LIBC_LOCAL_NAME(gsignal)
#endif /* !__local___localdep_gsignal_defined */
#else /* __CRT_HAVE_raise || (__CRT_HAVE_pthread_kill && (__CRT_HAVE_pthread_self || __CRT_HAVE_thrd_current)) || (__CRT_HAVE_kill && (__CRT_HAVE_getpid || __CRT_HAVE__getpid || __CRT_HAVE___getpid)) */
#undef __local_gsignal_defined
#endif /* !__CRT_HAVE_raise && (!__CRT_HAVE_pthread_kill || (!__CRT_HAVE_pthread_self && !__CRT_HAVE_thrd_current)) && (!__CRT_HAVE_kill || (!__CRT_HAVE_getpid && !__CRT_HAVE__getpid && !__CRT_HAVE___getpid)) */
#endif /* !__local_gsignal_defined */
