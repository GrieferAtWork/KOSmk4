/* HASH CRC-32:0x3c29f496 */
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
#ifndef __local_sigabbrev_np_defined
#define __local_sigabbrev_np_defined
#include <__crt.h>
#include <bits/types.h>
#include <asm/os/signal.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(sigabbrev_np) __ATTR_CONST __ATTR_WUNUSED char const *
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(sigabbrev_np))(__signo_t __signum) {
	char const *__result;
	switch (__signum) {

#ifdef __SIGABRT_COMPAT
	case __SIGABRT_COMPAT:
		__result = "ABRT_COMPAT";
		break;
#endif /* __SIGABRT_COMPAT */

#ifdef __SIGBREAK
	case __SIGBREAK:
		__result = "BREAK";
		break;
#endif /* __SIGBREAK */

#ifdef __SIGHUP
	case __SIGHUP:
		__result = "HUP";
		break;
#endif /* __SIGHUP */

#ifdef __SIGINT
	case __SIGINT:
		__result = "INT";
		break;
#endif /* __SIGINT */

#ifdef __SIGQUIT
	case __SIGQUIT:
		__result = "QUIT";
		break;
#endif /* __SIGQUIT */

#ifdef __SIGILL
	case __SIGILL:
		__result = "ILL";
		break;
#endif /* __SIGILL */

#ifdef __SIGTRAP
	case __SIGTRAP:
		__result = "TRAP";
		break;
#endif /* __SIGTRAP */

#ifdef __SIGABRT
	case __SIGABRT:
		__result = "ABRT";
		break;
#endif /* __SIGABRT */

#ifdef __SIGBUS
	case __SIGBUS:
		__result = "BUS";
		break;
#endif /* __SIGBUS */

#ifdef __SIGFPE
	case __SIGFPE:
		__result = "FPE";
		break;
#endif /* __SIGFPE */

#ifdef __SIGKILL
	case __SIGKILL:
		__result = "KILL";
		break;
#endif /* __SIGKILL */

#ifdef __SIGUSR1
	case __SIGUSR1:
		__result = "USR1";
		break;
#endif /* __SIGUSR1 */

#ifdef __SIGSEGV
	case __SIGSEGV:
		__result = "SEGV";
		break;
#endif /* __SIGSEGV */

#ifdef __SIGUSR2
	case __SIGUSR2:
		__result = "USR2";
		break;
#endif /* __SIGUSR2 */

#ifdef __SIGPIPE
	case __SIGPIPE:
		__result = "PIPE";
		break;
#endif /* __SIGPIPE */

#ifdef __SIGALRM
	case __SIGALRM:
		__result = "ALRM";
		break;
#endif /* __SIGALRM */

#ifdef __SIGTERM
	case __SIGTERM:
		__result = "TERM";
		break;
#endif /* __SIGTERM */

#ifdef __SIGSTKFLT
	case __SIGSTKFLT:
		__result = "STKFLT";
		break;
#endif /* __SIGSTKFLT */

#ifdef __SIGCHLD
	case __SIGCHLD:
		__result = "CHLD";
		break;
#endif /* __SIGCHLD */

#ifdef __SIGCONT
	case __SIGCONT:
		__result = "CONT";
		break;
#endif /* __SIGCONT */

#ifdef __SIGSTOP
	case __SIGSTOP:
		__result = "STOP";
		break;
#endif /* __SIGSTOP */

#ifdef __SIGTSTP
	case __SIGTSTP:
		__result = "TSTP";
		break;
#endif /* __SIGTSTP */

#ifdef __SIGTTOU
	case __SIGTTOU:
		__result = "TTOU";
		break;
#endif /* __SIGTTOU */

#ifdef __SIGURG
	case __SIGURG:
		__result = "URG";
		break;
#endif /* __SIGURG */

#ifdef __SIGXCPU
	case __SIGXCPU:
		__result = "XCPU";
		break;
#endif /* __SIGXCPU */

#ifdef __SIGXFSZ
	case __SIGXFSZ:
		__result = "XFSZ";
		break;
#endif /* __SIGXFSZ */

#ifdef __SIGVTALRM
	case __SIGVTALRM:
		__result = "VTALRM";
		break;
#endif /* __SIGVTALRM */

#ifdef __SIGPROF
	case __SIGPROF:
		__result = "PROF";
		break;
#endif /* __SIGPROF */

#ifdef __SIGWINCH
	case __SIGWINCH:
		__result = "WINCH";
		break;
#endif /* __SIGWINCH */

#ifdef __SIGIO
	case __SIGIO:
		__result = "IO";
		break;
#endif /* __SIGIO */

#ifdef __SIGSYS
	case __SIGSYS:
		__result = "SYS";
		break;
#endif /* __SIGSYS */

#ifdef __SIGEMT
	case __SIGEMT:
		__result = "EMT";
		break;
#endif /* __SIGEMT */

#ifdef __SIGLOST
	case __SIGLOST:
		__result = "LOST";
		break;
#endif /* __SIGLOST */

#if defined(__SIGTTIN) && (!defined(__SIGBREAK) || __SIGBREAK != __SIGTTIN)
	case __SIGTTIN:
		__result = "TTIN";
		break;
#endif /* __SIGTTIN && (!__SIGBREAK || __SIGBREAK != __SIGTTIN) */

#if defined(__SIGCLD) && (!defined(__SIGCHLD) || __SIGCLD != __SIGCHLD)
	case __SIGCLD:
		__result = "CLD";
		break;
#endif /* __SIGCLD && (!__SIGCHLD || __SIGCLD != __SIGCHLD) */

#if defined(__SIGIOT) && (!defined(__SIGABRT) || __SIGIOT != __SIGABRT)
	case __SIGIOT:
		__result = "IOT";
		break;
#endif /* __SIGIOT && (!__SIGABRT || __SIGIOT != __SIGABRT) */

#if defined(__SIGPOLL) && (!defined(__SIGIO) || __SIGPOLL != __SIGIO)
	case __SIGPOLL:
		__result = "POLL";
		break;
#endif /* __SIGPOLL && (!__SIGIO || __SIGPOLL != __SIGIO) */

#if defined(__SIGPWR) && (!defined(__SIGLOST) || __SIGPWR != __SIGLOST)
	case __SIGPWR:
		__result = "PWR";
		break;
#endif /* __SIGPWR && (!__SIGLOST || __SIGPWR != __SIGLOST) */

	default:
		__result = __NULLPTR;
		break;
	}
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_sigabbrev_np_defined
#define __local___localdep_sigabbrev_np_defined
#define __localdep_sigabbrev_np __LIBC_LOCAL_NAME(sigabbrev_np)
#endif /* !__local___localdep_sigabbrev_np_defined */
#endif /* !__local_sigabbrev_np_defined */
