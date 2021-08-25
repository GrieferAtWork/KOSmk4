/* HASH CRC-32:0xd30db7a1 */
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
#ifndef __local_sigdescr_np_defined
#define __local_sigdescr_np_defined 1
#include <__crt.h>
#include <bits/types.h>
#include <asm/os/signal.h>
__NAMESPACE_LOCAL_BEGIN
/* >> sigdescr_np(3)
 * Return a description for the given signal.
 * If the given `signum' isn't recognized, return `NULL' instead. */
__LOCAL_LIBC(sigdescr_np) __ATTR_CONST __ATTR_WUNUSED char const *
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(sigdescr_np))(__signo_t __signum) {
	char const *__result;
	switch (__signum) {

#ifdef __SIGABRT_COMPAT
	case __SIGABRT_COMPAT : __result = "Abort"; break;
#endif /* __SIGABRT_COMPAT */
#ifdef __SIGBREAK
	case __SIGBREAK : __result = "Background read from tty"; break;
#endif /* __SIGBREAK */
#ifdef __SIGHUP
	case __SIGHUP   : __result = "Hangup"; break;
#endif /* __SIGHUP */
#ifdef __SIGINT
	case __SIGINT   : __result = "Interrupt"; break;
#endif /* __SIGINT */
#ifdef __SIGQUIT
	case __SIGQUIT  : __result = "Quit"; break;
#endif /* __SIGQUIT */
#ifdef __SIGILL
	case __SIGILL   : __result = "Illegal instruction"; break;
#endif /* __SIGILL */
#ifdef __SIGTRAP
	case __SIGTRAP  : __result = "Trace trap"; break;
#endif /* __SIGTRAP */
#ifdef __SIGABRT
	case __SIGABRT  : __result = "Abort"; break;
#endif /* __SIGABRT */
#ifdef __SIGBUS
	case __SIGBUS   : __result = "BUS error"; break;
#endif /* __SIGBUS */
#ifdef __SIGFPE
	case __SIGFPE   : __result = "Floating-point exception"; break;
#endif /* __SIGFPE */
#ifdef __SIGKILL
	case __SIGKILL  : __result = "Kill"; break;
#endif /* __SIGKILL */
#ifdef __SIGUSR1
	case __SIGUSR1  : __result = "User-defined signal 1"; break;
#endif /* __SIGUSR1 */
#ifdef __SIGSEGV
	case __SIGSEGV  : __result = "Segmentation violation"; break;
#endif /* __SIGSEGV */
#ifdef __SIGUSR2
	case __SIGUSR2  : __result = "User-defined signal 2"; break;
#endif /* __SIGUSR2 */
#ifdef __SIGPIPE
	case __SIGPIPE  : __result = "Broken pipe"; break;
#endif /* __SIGPIPE */
#ifdef __SIGALRM
	case __SIGALRM  : __result = "Alarm clock"; break;
#endif /* __SIGALRM */
#ifdef __SIGTERM
	case __SIGTERM  : __result = "Termination"; break;
#endif /* __SIGTERM */
#ifdef __SIGSTKFLT
	case __SIGSTKFLT: __result = "Stack fault"; break;
#endif /* __SIGSTKFLT */
#if defined(__SIGCHLD) || defined(__SIGCLD)
#ifdef __SIGCHLD
	case __SIGCHLD:
#endif /* __SIGCHLD */
#if defined(__SIGCLD) && (!defined(__SIGCHLD) || __SIGCLD != __SIGCHLD)
	case __SIGCLD:
#endif /* __SIGCLD && (!__SIGCHLD || __SIGCLD != __SIGCHLD) */
		__result = "Child status has changed";
		break;
#endif /* __SIGCHLD || __SIGCLD */
#ifdef __SIGCONT
	case __SIGCONT  : __result = "Continue"; break;
#endif /* __SIGCONT */
#ifdef __SIGSTOP
	case __SIGSTOP  : __result = "Stop"; break;
#endif /* __SIGSTOP */
#ifdef __SIGTSTP
	case __SIGTSTP  : __result = "Keyboard stop"; break;
#endif /* __SIGTSTP */
#ifdef __SIGTTIN
	case __SIGTTIN  : __result = "Background read from tty"; break;
#endif /* __SIGTTIN */
#ifdef __SIGTTOU
	case __SIGTTOU  : __result = "Background write to tty"; break;
#endif /* __SIGTTOU */
#ifdef __SIGURG
	case __SIGURG   : __result = "Urgent condition on socket"; break;
#endif /* __SIGURG */
#ifdef __SIGXCPU
	case __SIGXCPU  : __result = "CPU limit exceeded"; break;
#endif /* __SIGXCPU */
#ifdef __SIGXFSZ
	case __SIGXFSZ  : __result = "File size limit exceeded"; break;
#endif /* __SIGXFSZ */
#ifdef __SIGVTALRM
	case __SIGVTALRM: __result = "Virtual alarm clock"; break;
#endif /* __SIGVTALRM */
#ifdef __SIGPROF
	case __SIGPROF  : __result = "Profiling alarm clock"; break;
#endif /* __SIGPROF */
#ifdef __SIGWINCH
	case __SIGWINCH : __result = "Window size change"; break;
#endif /* __SIGWINCH */
#ifdef __SIGIO
	case __SIGIO    : __result = "I/O now possible"; break;
#endif /* __SIGIO */
#ifdef __SIGSYS
	case __SIGSYS   : __result = "Bad system call"; break;
#endif /* __SIGSYS */
#ifdef __SIGEMT
	case __SIGEMT   : __result = "EMT instruction"; break;
#endif /* __SIGEMT */
#ifdef __SIGLOST
	case __SIGLOST  : __result = "Resource lost"; break;
#endif /* __SIGLOST */
#if defined(__SIGIOT) && (!defined(__SIGABRT) || __SIGIOT != __SIGABRT)
	case __SIGIOT   : __result = "IOT trap"; break;
#endif /* __SIGIOT && (!__SIGABRT || __SIGIOT != __SIGABRT) */
#if defined(__SIGPOLL) && (!defined(__SIGIO) || __SIGPOLL != __SIGIO)
	case __SIGPOLL  : __result = "Pollable event occurred"; break;
#endif /* __SIGPOLL && (!__SIGIO || __SIGPOLL != __SIGIO) */
#if defined(__SIGPWR) && (!defined(__SIGLOST) || __SIGPWR != __SIGLOST)
	case __SIGPWR   : __result = "Power failure restart"; break;
#endif /* __SIGPWR && (!__SIGLOST || __SIGPWR != __SIGLOST) */

	default:
		__result = __NULLPTR;
		break;
	}
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_sigdescr_np_defined
#define __local___localdep_sigdescr_np_defined 1
#define __localdep_sigdescr_np __LIBC_LOCAL_NAME(sigdescr_np)
#endif /* !__local___localdep_sigdescr_np_defined */
#endif /* !__local_sigdescr_np_defined */
