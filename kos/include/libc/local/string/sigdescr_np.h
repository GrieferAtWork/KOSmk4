/* HASH CRC-32:0xd2d1cbb4 */
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
#ifndef __local_sigdescr_np_defined
#define __local_sigdescr_np_defined
#include <__crt.h>
#include <bits/types.h>
#include <asm/os/signal.h>
#ifndef ___local_sys_siglist_defined
#define ___local_sys_siglist_defined
#if defined(__CRT_HAVE___p_sys_siglist)
#ifndef ____p_sys_siglist_defined
#define ____p_sys_siglist_defined
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED __ATTR_RETNONNULL,char const *const *,__NOTHROW_NCX,__p_sys_siglist,(void),())
#endif /* !____p_sys_siglist_defined */
#ifndef _sys_siglist
#define _sys_siglist __p_sys_siglist()
#endif /* !_sys_siglist */
#ifndef sys_siglist
#define sys_siglist  __p_sys_siglist()
#endif /* !sys_siglist */
#elif defined(__CRT_HAVE_sys_siglist)
#if defined(__CRT_HAVE__sys_siglist) || !defined(__NO_COMPILER_SREDIRECT)
__CSREDIRECT2(,char const *const _sys_siglist[__NSIG],_sys_siglist,__sys_siglist)
#else /* __CRT_HAVE__sys_siglist || !__NO_COMPILER_SREDIRECT */
#ifndef _sys_siglist
#define _sys_siglist sys_siglist
#endif /* !_sys_siglist */
#endif /* !__CRT_HAVE__sys_siglist && __NO_COMPILER_SREDIRECT */
#ifndef sys_siglist
__CSDECLARE2(,char const *const sys_siglist[__NSIG],sys_siglist)
#endif /* !sys_siglist */
#elif defined(__CRT_HAVE__sys_siglist)
#ifndef sys_siglist
#ifndef __NO_COMPILER_SREDIRECT
__CSREDIRECT2(,char const *const sys_siglist[__NSIG],sys_siglist,___sys_siglist)
#else /* !__NO_COMPILER_SREDIRECT */
#define sys_siglist _sys_siglist
#endif /* __NO_COMPILER_SREDIRECT */
#endif /* !sys_siglist */
#ifndef _sys_siglist
__CSDECLARE2(,char const *const _sys_siglist[__NSIG],_sys_siglist)
#endif /* !_sys_siglist */
#endif /* sys_siglist... */
#endif /* !___local_sys_siglist_defined */
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(sigdescr_np) __ATTR_CONST __ATTR_WUNUSED char const *
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(sigdescr_np))(__signo_t __signum) {
#ifdef _sys_siglist
	if __unlikely((unsigned int)__signum < __NSIG)
		return __NULLPTR;
	return _sys_siglist[__signum];
#else /* _sys_siglist */
	char const *__result;
	switch (__signum) {

#ifdef __SIGHUP
	case __SIGHUP:
		__result = "Hangup";
		break;
#endif /* __SIGHUP */

#ifdef __SIGINT
	case __SIGINT:
		__result = "Interrupt";
		break;
#endif /* __SIGINT */

#ifdef __SIGQUIT
	case __SIGQUIT:
		__result = "Quit";
		break;
#endif /* __SIGQUIT */

#ifdef __SIGILL
	case __SIGILL:
		__result = "Illegal instruction";
		break;
#endif /* __SIGILL */

#ifdef __SIGTRAP
	case __SIGTRAP:
		__result = "Trace/breakpoint trap";
		break;
#endif /* __SIGTRAP */

#if defined(__SIGABRT) || defined(__SIGABRT_COMPAT)
#ifdef __SIGABRT
	case __SIGABRT:
#endif /* __SIGABRT */
#if defined(__SIGABRT_COMPAT) && (!defined(__SIGABRT) || __SIGABRT_COMPAT != __SIGABRT)
	case __SIGABRT_COMPAT:
#endif /* __SIGABRT_COMPAT && (!__SIGABRT || __SIGABRT_COMPAT != __SIGABRT) */
		__result = "Aborted";
		break;
#endif /* __SIGABRT || __SIGABRT_COMPAT */

#ifdef __SIGBUS
	case __SIGBUS:
		__result = "Bus error";
		break;
#endif /* __SIGBUS */

#ifdef __SIGFPE
	case __SIGFPE:
		__result = "Floating point exception";
		break;
#endif /* __SIGFPE */

#ifdef __SIGKILL
	case __SIGKILL:
		__result = "Killed";
		break;
#endif /* __SIGKILL */

#ifdef __SIGUSR1
	case __SIGUSR1:
		__result = "User defined signal 1";
		break;
#endif /* __SIGUSR1 */

#ifdef __SIGSEGV
	case __SIGSEGV:
		__result = "Segmentation violation";
		break;
#endif /* __SIGSEGV */

#ifdef __SIGUSR2
	case __SIGUSR2:
		__result = "User defined signal 2";
		break;
#endif /* __SIGUSR2 */

#ifdef __SIGPIPE
	case __SIGPIPE:
		__result = "Broken pipe";
		break;
#endif /* __SIGPIPE */

#ifdef __SIGALRM
	case __SIGALRM:
		__result = "Alarm clock";
		break;
#endif /* __SIGALRM */

#ifdef __SIGTERM
	case __SIGTERM:
		__result = "Terminated";
		break;
#endif /* __SIGTERM */

#ifdef __SIGSTKFLT
	case __SIGSTKFLT:
		__result = "Stack fault";
		break;
#endif /* __SIGSTKFLT */

#if defined(__SIGCHLD) || defined(__SIGCLD)
#ifdef __SIGCHLD
	case __SIGCHLD:
#endif /* __SIGCHLD */
#if defined(__SIGCLD) && (!defined(__SIGCHLD) || __SIGCLD != __SIGCHLD)
	case __SIGCLD:
#endif /* __SIGCLD && (!__SIGCHLD || __SIGCLD != __SIGCHLD) */
		__result = "Child exited";
		break;
#endif /* __SIGCHLD || __SIGCLD */

#ifdef __SIGCONT
	case __SIGCONT:
		__result = "Continued";
		break;
#endif /* __SIGCONT */

#ifdef __SIGSTOP
	case __SIGSTOP:
		__result = "Stopped (signal)";
		break;
#endif /* __SIGSTOP */

#ifdef __SIGTSTP
	case __SIGTSTP:
		__result = "Stopped";
		break;
#endif /* __SIGTSTP */

#if defined(__SIGTTIN) || defined(__SIGBREAK)
#ifdef __SIGTTIN
	case __SIGTTIN:
#endif /* __SIGTTIN */
#if defined(__SIGBREAK) && (!defined(__SIGTTIN) || __SIGBREAK != __SIGTTIN)
	case __SIGBREAK:
#endif /* __SIGBREAK && (!__SIGTTIN || __SIGBREAK != __SIGTTIN) */
		__result = "Stopped (tty input)";
		break;
#endif /* __SIGTTIN || __SIGBREAK */

#ifdef __SIGTTOU
	case __SIGTTOU:
		__result = "Stopped (tty output)";
		break;
#endif /* __SIGTTOU */

#ifdef __SIGURG
	case __SIGURG:
		__result = "Urgent I/O condition";
		break;
#endif /* __SIGURG */

#ifdef __SIGXCPU
	case __SIGXCPU:
		__result = "CPU time limit exceeded";
		break;
#endif /* __SIGXCPU */

#ifdef __SIGXFSZ
	case __SIGXFSZ:
		__result = "File size limit exceeded";
		break;
#endif /* __SIGXFSZ */

#ifdef __SIGVTALRM
	case __SIGVTALRM:
		__result = "Virtual timer expired";
		break;
#endif /* __SIGVTALRM */

#ifdef __SIGPROF
	case __SIGPROF:
		__result = "Profiling timer expired";
		break;
#endif /* __SIGPROF */

#ifdef __SIGWINCH
	case __SIGWINCH:
		__result = "Window changed";
		break;
#endif /* __SIGWINCH */

#ifdef __SIGIO
	case __SIGIO:
		__result = "I/O possible";
		break;
#endif /* __SIGIO */

#ifdef __SIGSYS
	case __SIGSYS:
		__result = "Bad system call";
		break;
#endif /* __SIGSYS */

#ifdef __SIGEMT
	case __SIGEMT:
		__result = "EMT instruction";
		break;
#endif /* __SIGEMT */

#ifdef __SIGLOST
	case __SIGLOST:
		__result = "Resource lost";
		break;
#endif /* __SIGLOST */

#if defined(__SIGIOT) && (!defined(__SIGABRT) || __SIGIOT != __SIGABRT)
	case __SIGIOT:
		__result = "IOT trap";
		break;
#endif /* __SIGIOT && (!__SIGABRT || __SIGIOT != __SIGABRT) */

#if defined(__SIGPOLL) && (!defined(__SIGIO) || __SIGPOLL != __SIGIO)
	case __SIGPOLL:
		__result = "Pollable event occurred";
		break;
#endif /* __SIGPOLL && (!__SIGIO || __SIGPOLL != __SIGIO) */

#if defined(__SIGPWR) && (!defined(__SIGLOST) || __SIGPWR != __SIGLOST)
	case __SIGPWR:
		__result = "Power failure";
		break;
#endif /* __SIGPWR && (!__SIGLOST || __SIGPWR != __SIGLOST) */


	default:
		__result = __NULLPTR;
		break;
	}
	return __result;
#endif /* !_sys_siglist */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_sigdescr_np_defined
#define __local___localdep_sigdescr_np_defined
#define __localdep_sigdescr_np __LIBC_LOCAL_NAME(sigdescr_np)
#endif /* !__local___localdep_sigdescr_np_defined */
#endif /* !__local_sigdescr_np_defined */
