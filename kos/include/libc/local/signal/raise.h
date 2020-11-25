/* HASH CRC-32:0xbebc9b95 */
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
#ifndef __local_raise_defined
#define __local_raise_defined 1
#include <__crt.h>
#if (defined(__CRT_HAVE_pthread_kill) && (defined(__CRT_HAVE_pthread_self) || defined(__CRT_HAVE_thrd_current))) || (defined(__CRT_HAVE_kill) && (defined(__CRT_HAVE_getpid) || defined(__CRT_HAVE__getpid) || defined(__CRT_HAVE___getpid)))
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: getpid from unistd */
#ifndef __local___localdep_getpid_defined
#define __local___localdep_getpid_defined 1
#ifdef __CRT_HAVE_getpid
/* >> getpid(2)
 * Return the PID of the calling process (that is the TID of the calling thread group's leader)
 * THIS_THREAD->LEADER->PID */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__pid_t,__NOTHROW,__localdep_getpid,(void),getpid,())
#elif defined(__CRT_HAVE__getpid)
/* >> getpid(2)
 * Return the PID of the calling process (that is the TID of the calling thread group's leader)
 * THIS_THREAD->LEADER->PID */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__pid_t,__NOTHROW,__localdep_getpid,(void),_getpid,())
#elif defined(__CRT_HAVE___getpid)
/* >> getpid(2)
 * Return the PID of the calling process (that is the TID of the calling thread group's leader)
 * THIS_THREAD->LEADER->PID */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__pid_t,__NOTHROW,__localdep_getpid,(void),__getpid,())
#else /* ... */
#undef __local___localdep_getpid_defined
#endif /* !... */
#endif /* !__local___localdep_getpid_defined */
/* Dependency: kill from signal */
#if !defined(__local___localdep_kill_defined) && defined(__CRT_HAVE_kill)
#define __local___localdep_kill_defined 1
/* >> kill(2)
 * Raise a signal `signo' within the process(es) specified by `pid':
 *   - pid > 0:   Deliver `signo' to a process who's PID matches `pid'.
 *   - pid == 0:  Deliver `signo' to every process within the caller's process group.
 *   - pid == -1: Deliver `signo' to every process the caller has permission to send
 *                signals to, with the exception of a process with pid=1 (i.e. `/bin/init')
 *   - pid < -1:  Deliver `signo' to every process within the process group `-pid'
 * @param: signo: The signal number to deliver. When set to `0', no signal is delivered,
 *                and this function can be used to test if the caller would be allowed to
 *                send signals to the process(es) specified by `pid'
 * @return: 0:    Success
 * @return: -1:   [errno=EINVAL] The given `signo' is invalid
 * @return: -1:   [errno=EPERM]  The caller does not have permission to send signals to `pid'
 * @return: -1:   [errno=ESRCH]  No process is identified by `pid' */
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_kill,(__pid_t __pid, __signo_t __signo),kill,(__pid,__signo))
#endif /* !__local___localdep_kill_defined && __CRT_HAVE_kill */
/* Dependency: pthread_kill from signal */
#if !defined(__local___localdep_pthread_kill_defined) && defined(__CRT_HAVE_pthread_kill)
#define __local___localdep_pthread_kill_defined 1
__NAMESPACE_LOCAL_END
#include <bits/crt/pthreadtypes.h>
__NAMESPACE_LOCAL_BEGIN
/* >> pthread_kill(3)
 * Portable function for sending a signal to a specific `pthread' within one's own process.
 * @return: EOK:    Success
 * @return: EINVAL: The given `signo' is invalid */
__CREDIRECT(,__errno_t,__NOTHROW_NCX,__localdep_pthread_kill,(__pthread_t __pthread, __signo_t __signo),pthread_kill,(__pthread,__signo))
#endif /* !__local___localdep_pthread_kill_defined && __CRT_HAVE_pthread_kill */
/* Dependency: pthread_self from pthread */
#ifndef __local___localdep_pthread_self_defined
#define __local___localdep_pthread_self_defined 1
#ifdef __CRT_HAVE_pthread_self
/* >> pthread_self(3)
 * Obtain the identifier of the current thread
 * @return: * : Handle for the calling thread */
__CREDIRECT(__ATTR_CONST,__pthread_t,__NOTHROW,__localdep_pthread_self,(void),pthread_self,())
#elif defined(__CRT_HAVE_thrd_current)
/* >> pthread_self(3)
 * Obtain the identifier of the current thread
 * @return: * : Handle for the calling thread */
__CREDIRECT(__ATTR_CONST,__pthread_t,__NOTHROW,__localdep_pthread_self,(void),thrd_current,())
#else /* ... */
#undef __local___localdep_pthread_self_defined
#endif /* !... */
#endif /* !__local___localdep_pthread_self_defined */
__NAMESPACE_LOCAL_END
#include <libc/errno.h>
__NAMESPACE_LOCAL_BEGIN
/* >> raise(3)
 * Raise a signal within the current thread.
 * In a *-theaded process this is same as:
 *   *=multi:  `pthread_kill(pthread_self(), signo)'
 *   *=single: `kill(getpid(), signo)'
 * @return: 0:  Success
 * @return: -1: [errno=EINVAL] The given `signo' is invalid */
__LOCAL_LIBC(raise) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(raise))(__signo_t __signo) {
#if defined(__CRT_HAVE_pthread_kill) && (defined(__CRT_HAVE_pthread_self) || defined(__CRT_HAVE_thrd_current))
	__errno_t __error;
	__error = __localdep_pthread_kill(__localdep_pthread_self(), __signo);
	if __unlikely(__error != __EOK)
		__error = (__errno_t)__libc_seterrno(__error);
	return (int)__error;
#else /* __CRT_HAVE_pthread_kill && (__CRT_HAVE_pthread_self || __CRT_HAVE_thrd_current) */
	return __localdep_kill(__localdep_getpid(), __signo);
#endif /* !__CRT_HAVE_pthread_kill || (!__CRT_HAVE_pthread_self && !__CRT_HAVE_thrd_current) */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_raise_defined
#define __local___localdep_raise_defined 1
#define __localdep_raise __LIBC_LOCAL_NAME(raise)
#endif /* !__local___localdep_raise_defined */
#else /* (__CRT_HAVE_pthread_kill && (__CRT_HAVE_pthread_self || __CRT_HAVE_thrd_current)) || (__CRT_HAVE_kill && (__CRT_HAVE_getpid || __CRT_HAVE__getpid || __CRT_HAVE___getpid)) */
#undef __local_raise_defined
#endif /* (!__CRT_HAVE_pthread_kill || (!__CRT_HAVE_pthread_self && !__CRT_HAVE_thrd_current)) && (!__CRT_HAVE_kill || (!__CRT_HAVE_getpid && !__CRT_HAVE__getpid && !__CRT_HAVE___getpid)) */
#endif /* !__local_raise_defined */
