/* HASH CRC-32:0x9750b6e7 */
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
#ifndef __local_sigdescr_np_defined
#define __local_sigdescr_np_defined
#include <__crt.h>
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_sigabbrev_np_defined
#define __local___localdep_sigabbrev_np_defined
#ifdef __CRT_HAVE_sigabbrev_np
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,char const *,__NOTHROW,__localdep_sigabbrev_np,(__signo_t __signo),sigabbrev_np,(__signo))
#elif defined(__CRT_HAVE_signalname)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,char const *,__NOTHROW,__localdep_sigabbrev_np,(__signo_t __signo),signalname,(__signo))
#elif defined(__CRT_HAVE_strsigno)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,char const *,__NOTHROW,__localdep_sigabbrev_np,(__signo_t __signo),strsigno,(__signo))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/string/sigabbrev_np.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_sigabbrev_np __LIBC_LOCAL_NAME(sigabbrev_np)
#endif /* !... */
#endif /* !__local___localdep_sigabbrev_np_defined */
#ifndef __local___localdep_strend_defined
#define __local___localdep_strend_defined
#ifdef __CRT_HAVE_strend
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,__localdep_strend,(char const *__restrict __str),strend,(__str))
#else /* __CRT_HAVE_strend */
__NAMESPACE_LOCAL_END
#include <libc/local/string/strend.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strend __LIBC_LOCAL_NAME(strend)
#endif /* !__CRT_HAVE_strend */
#endif /* !__local___localdep_strend_defined */
__NAMESPACE_LOCAL_END
#include <asm/os/signal.h>
#ifndef __BUILDING_LIBC
#ifdef __CRT_HAVE__sys_siglist
#ifndef _sys_siglist
#ifdef __NSIG
__CSDECLARE2(,char const *const _sys_siglist[__NSIG],_sys_siglist)
#else /* __NSIG */
__CSDECLARE2(,char const *const _sys_siglist[],_sys_siglist)
#endif /* !__NSIG */
#define _sys_siglist _sys_siglist
#endif /* !_sys_siglist */
#if !defined(_sys_nsig) && defined(__CRT_HAVE__sys_nsig)
__CSDECLARE(,int,_sys_nsig)
#define _sys_nsig _sys_nsig
#endif /* !_sys_nsig && __CRT_HAVE__sys_nsig */
#endif /* __CRT_HAVE__sys_siglist */
#endif /* !__BUILDING_LIBC */
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(sigdescr_np) __ATTR_CONST __ATTR_WUNUSED char const *
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(sigdescr_np))(__signo_t __signo) {
#if defined(__CRT_HAVE__sys_siglist) && (defined(_sys_nsig) || defined(__NSIG))
#ifdef _sys_nsig
	return (unsigned int)__signo < (unsigned int)_sys_nsig ? _sys_siglist[__signo] : __NULLPTR;
#else /* _sys_nsig */
	return (unsigned int)__signo < (unsigned int)__NSIG ? _sys_siglist[__signo] : __NULLPTR;
#endif /* !_sys_nsig */
#elif (!defined(__CRT_HAVE_sigabbrev_np) && !defined(__CRT_HAVE_signalname) && !defined(__CRT_HAVE_strsigno)) || defined(__CRT_KOS)



	char const *__result;
	__result = (__NAMESPACE_LOCAL_SYM __localdep_sigabbrev_np)(__signo);
	if (__result)
		__result = (__NAMESPACE_LOCAL_SYM __localdep_strend)(__result) + 1;
	return __result;
#else /* ... */
	char const *__result;
	switch (__signo) {

#ifdef __SIGABRT_COMPAT
	case __SIGABRT_COMPAT: __result = "Aborted"; break;
#endif /* __SIGABRT_COMPAT */
#ifdef __SIGBREAK
	case __SIGBREAK:       __result = "Stopped (tty input)"; break;
#endif /* __SIGBREAK */
#ifdef __SIGHUP
	case __SIGHUP:         __result = "Hangup"; break;
#endif /* __SIGHUP */
#ifdef __SIGINT
	case __SIGINT:         __result = "Interrupt"; break;
#endif /* __SIGINT */
#ifdef __SIGQUIT
	case __SIGQUIT:        __result = "Quit"; break;
#endif /* __SIGQUIT */
#ifdef __SIGILL
	case __SIGILL:         __result = "Illegal instruction"; break;
#endif /* __SIGILL */
#ifdef __SIGTRAP
	case __SIGTRAP:        __result = "Trace/breakpoint trap"; break;
#endif /* __SIGTRAP */
#ifdef __SIGABRT
	case __SIGABRT:        __result = "Aborted"; break;
#endif /* __SIGABRT */
#ifdef __SIGBUS
	case __SIGBUS:         __result = "Bus error"; break;
#endif /* __SIGBUS */
#ifdef __SIGFPE
	case __SIGFPE:         __result = "Floating point exception"; break;
#endif /* __SIGFPE */
#ifdef __SIGKILL
	case __SIGKILL:        __result = "Killed"; break;
#endif /* __SIGKILL */
#ifdef __SIGUSR1
	case __SIGUSR1:        __result = "User defined signal 1"; break;
#endif /* __SIGUSR1 */
#ifdef __SIGSEGV
	case __SIGSEGV:        __result = "Segmentation violation"; break;
#endif /* __SIGSEGV */
#ifdef __SIGUSR2
	case __SIGUSR2:        __result = "User defined signal 2"; break;
#endif /* __SIGUSR2 */
#ifdef __SIGPIPE
	case __SIGPIPE:        __result = "Broken pipe"; break;
#endif /* __SIGPIPE */
#ifdef __SIGALRM
	case __SIGALRM:        __result = "Alarm clock"; break;
#endif /* __SIGALRM */
#ifdef __SIGTERM
	case __SIGTERM:        __result = "Terminated"; break;
#endif /* __SIGTERM */
#ifdef __SIGSTKFLT
	case __SIGSTKFLT:      __result = "Stack fault"; break;
#endif /* __SIGSTKFLT */
#ifdef __SIGCHLD
	case __SIGCHLD:        __result = "Child exited"; break;
#endif /* __SIGCHLD */
#ifdef __SIGCONT
	case __SIGCONT:        __result = "Continued"; break;
#endif /* __SIGCONT */
#ifdef __SIGSTOP
	case __SIGSTOP:        __result = "Stopped (signal)"; break;
#endif /* __SIGSTOP */
#ifdef __SIGTSTP
	case __SIGTSTP:        __result = "Stopped"; break;
#endif /* __SIGTSTP */
#ifdef __SIGTTOU
	case __SIGTTOU:        __result = "Stopped (tty output)"; break;
#endif /* __SIGTTOU */
#ifdef __SIGURG
	case __SIGURG:         __result = "Urgent I/O condition"; break;
#endif /* __SIGURG */
#ifdef __SIGXCPU
	case __SIGXCPU:        __result = "CPU time limit exceeded"; break;
#endif /* __SIGXCPU */
#ifdef __SIGXFSZ
	case __SIGXFSZ:        __result = "File size limit exceeded"; break;
#endif /* __SIGXFSZ */
#ifdef __SIGVTALRM
	case __SIGVTALRM:      __result = "Virtual timer expired"; break;
#endif /* __SIGVTALRM */
#ifdef __SIGPROF
	case __SIGPROF:        __result = "Profiling timer expired"; break;
#endif /* __SIGPROF */
#ifdef __SIGWINCH
	case __SIGWINCH:       __result = "Window changed"; break;
#endif /* __SIGWINCH */
#ifdef __SIGIO
	case __SIGIO:          __result = "I/O possible"; break;
#endif /* __SIGIO */
#ifdef __SIGSYS
	case __SIGSYS:         __result = "Bad system call"; break;
#endif /* __SIGSYS */
#ifdef __SIGEMT
	case __SIGEMT:         __result = "EMT instruction"; break;
#endif /* __SIGEMT */
#ifdef __SIGLOST
	case __SIGLOST:        __result = "Resource lost"; break;
#endif /* __SIGLOST */
#if defined(__SIGTTIN) && (!defined(__SIGBREAK) || __SIGBREAK != __SIGTTIN)
	case __SIGTTIN:        __result = "Stopped (tty input)"; break;
#endif /* __SIGTTIN && (!__SIGBREAK || __SIGBREAK != __SIGTTIN) */
#if defined(__SIGCLD) && (!defined(__SIGCHLD) || __SIGCLD != __SIGCHLD)
	case __SIGCLD:         __result = "Child exited"; break;
#endif /* __SIGCLD && (!__SIGCHLD || __SIGCLD != __SIGCHLD) */
#if defined(__SIGIOT) && (!defined(__SIGABRT) || __SIGIOT != __SIGABRT)
	case __SIGIOT:         __result = "IOT trap"; break;
#endif /* __SIGIOT && (!__SIGABRT || __SIGIOT != __SIGABRT) */
#if defined(__SIGPOLL) && (!defined(__SIGIO) || __SIGPOLL != __SIGIO)
	case __SIGPOLL:        __result = "Pollable event occurred"; break;
#endif /* __SIGPOLL && (!__SIGIO || __SIGPOLL != __SIGIO) */
#if defined(__SIGPWR) && (!defined(__SIGLOST) || __SIGPWR != __SIGLOST)
	case __SIGPWR:         __result = "Power failure"; break;
#endif /* __SIGPWR && (!__SIGLOST || __SIGPWR != __SIGLOST) */

	default:
		__result = __NULLPTR;
		break;
	}
	return __result;
#endif /* !... */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_sigdescr_np_defined
#define __local___localdep_sigdescr_np_defined
#define __localdep_sigdescr_np __LIBC_LOCAL_NAME(sigdescr_np)
#endif /* !__local___localdep_sigdescr_np_defined */
#endif /* !__local_sigdescr_np_defined */
