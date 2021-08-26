/* HASH CRC-32:0x16e66b64 */
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
#ifndef __local_sigabbrev_np_defined
#define __local_sigabbrev_np_defined 1
#include <__crt.h>
#include <bits/types.h>
#include <asm/os/signal.h>
#ifndef ___local_sys_siglist_defined
#define ___local_sys_siglist_defined 1
#if defined(__CRT_HAVE___p_sys_siglist)
#ifndef ____p_sys_siglist_defined
#define ____p_sys_siglist_defined 1
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED __ATTR_RETNONNULL,char const *const *,__NOTHROW_NCX,__p_sys_siglist,(void),())
#endif /* !____p_sys_siglist_defined */
#ifndef _sys_siglist
#define _sys_siglist __p_sys_siglist()
#endif /* !_sys_siglist */
#ifndef sys_siglist
#define sys_siglist  __p_sys_siglist()
#endif /* !sys_siglist */
#elif defined(__CRT_HAVE_sys_siglist)
#if defined(__CRT_HAVE__sys_siglist) || !defined(__NO_ASMNAME)
__LIBC char const *const _sys_siglist[__NSIG] __ASMNAME("sys_siglist");
#else /* __CRT_HAVE__sys_siglist || !__NO_ASMNAME */
#ifndef _sys_siglist
#define _sys_siglist sys_siglist
#endif /* !_sys_siglist */
#endif /* !__CRT_HAVE__sys_siglist && __NO_ASMNAME */
#ifndef sys_siglist
__LIBC char const *const sys_siglist[__NSIG];
#endif /* !sys_siglist */
#elif defined(__CRT_HAVE__sys_siglist)
#ifndef sys_siglist
#ifndef __NO_ASMNAME
__LIBC char const *const sys_siglist[__NSIG] __ASMNAME("_sys_siglist");
#else /* !__NO_ASMNAME */
#define sys_siglist _sys_siglist
#endif /* __NO_ASMNAME */
#endif /* !sys_siglist */
#ifndef _sys_siglist
__LIBC char const *const _sys_siglist[__NSIG];
#endif /* !_sys_siglist */
#endif /* sys_siglist... */
#endif /* !___local_sys_siglist_defined */
__NAMESPACE_LOCAL_BEGIN
/* >> sigabbrev_np(3)
 * Return the name of a given signal, without the leading `SIG*' prefix.
 * If the given `signum' isn't recognized, return `NULL' instead. */
__LOCAL_LIBC(sigabbrev_np) __ATTR_CONST __ATTR_WUNUSED char const *
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(sigabbrev_np))(__signo_t __signum) {
#if defined(__CRT_HAVE___p_sys_siglist) || defined(__CRT_HAVE_sys_siglist) || defined(__CRT_HAVE__sys_siglist)
	return (unsigned int)__signum < __NSIG ? _sys_siglist[__signum] : __NULLPTR;
#else /* __CRT_HAVE___p_sys_siglist || __CRT_HAVE_sys_siglist || __CRT_HAVE__sys_siglist */
	char const *__result;
	switch (__signum) {

#ifdef __SIGABRT_COMPAT
	case __SIGABRT_COMPAT : __result = "SIGABRT_COMPAT"; break;
#endif /* __SIGABRT_COMPAT */
#ifdef __SIGBREAK
	case __SIGBREAK : __result = "SIGBREAK"; break;
#endif /* __SIGBREAK */
#ifdef __SIGHUP
	case __SIGHUP   : __result = "SIGHUP"; break;
#endif /* __SIGHUP */
#ifdef __SIGINT
	case __SIGINT   : __result = "SIGINT"; break;
#endif /* __SIGINT */
#ifdef __SIGQUIT
	case __SIGQUIT  : __result = "SIGQUIT"; break;
#endif /* __SIGQUIT */
#ifdef __SIGILL
	case __SIGILL   : __result = "SIGILL"; break;
#endif /* __SIGILL */
#ifdef __SIGTRAP
	case __SIGTRAP  : __result = "SIGTRAP"; break;
#endif /* __SIGTRAP */
#ifdef __SIGABRT
	case __SIGABRT  : __result = "SIGABRT"; break;
#endif /* __SIGABRT */
#ifdef __SIGBUS
	case __SIGBUS   : __result = "SIGBUS"; break;
#endif /* __SIGBUS */
#ifdef __SIGFPE
	case __SIGFPE   : __result = "SIGFPE"; break;
#endif /* __SIGFPE */
#ifdef __SIGKILL
	case __SIGKILL  : __result = "SIGKILL"; break;
#endif /* __SIGKILL */
#ifdef __SIGUSR1
	case __SIGUSR1  : __result = "SIGUSR1"; break;
#endif /* __SIGUSR1 */
#ifdef __SIGSEGV
	case __SIGSEGV  : __result = "SIGSEGV"; break;
#endif /* __SIGSEGV */
#ifdef __SIGUSR2
	case __SIGUSR2  : __result = "SIGUSR2"; break;
#endif /* __SIGUSR2 */
#ifdef __SIGPIPE
	case __SIGPIPE  : __result = "SIGPIPE"; break;
#endif /* __SIGPIPE */
#ifdef __SIGALRM
	case __SIGALRM  : __result = "SIGALRM"; break;
#endif /* __SIGALRM */
#ifdef __SIGTERM
	case __SIGTERM  : __result = "SIGTERM"; break;
#endif /* __SIGTERM */
#ifdef __SIGSTKFLT
	case __SIGSTKFLT: __result = "SIGSTKFLT"; break;
#endif /* __SIGSTKFLT */
#ifdef __SIGCHLD
	case __SIGCHLD  : __result = "SIGCHLD"; break;
#endif /* __SIGCHLD */
#ifdef __SIGCONT
	case __SIGCONT  : __result = "SIGCONT"; break;
#endif /* __SIGCONT */
#ifdef __SIGSTOP
	case __SIGSTOP  : __result = "SIGSTOP"; break;
#endif /* __SIGSTOP */
#ifdef __SIGTSTP
	case __SIGTSTP  : __result = "SIGTSTP"; break;
#endif /* __SIGTSTP */
#ifdef __SIGTTIN
	case __SIGTTIN  : __result = "SIGTTIN"; break;
#endif /* __SIGTTIN */
#ifdef __SIGTTOU
	case __SIGTTOU  : __result = "SIGTTOU"; break;
#endif /* __SIGTTOU */
#ifdef __SIGURG
	case __SIGURG   : __result = "SIGURG"; break;
#endif /* __SIGURG */
#ifdef __SIGXCPU
	case __SIGXCPU  : __result = "SIGXCPU"; break;
#endif /* __SIGXCPU */
#ifdef __SIGXFSZ
	case __SIGXFSZ  : __result = "SIGXFSZ"; break;
#endif /* __SIGXFSZ */
#ifdef __SIGVTALRM
	case __SIGVTALRM: __result = "SIGVTALRM"; break;
#endif /* __SIGVTALRM */
#ifdef __SIGPROF
	case __SIGPROF  : __result = "SIGPROF"; break;
#endif /* __SIGPROF */
#ifdef __SIGWINCH
	case __SIGWINCH : __result = "SIGWINCH"; break;
#endif /* __SIGWINCH */
#ifdef __SIGIO
	case __SIGIO    : __result = "SIGIO"; break;
#endif /* __SIGIO */
#ifdef __SIGSYS
	case __SIGSYS   : __result = "SIGSYS"; break;
#endif /* __SIGSYS */
#ifdef __SIGEMT
	case __SIGEMT   : __result = "SIGEMT"; break;
#endif /* __SIGEMT */
#ifdef __SIGLOST
	case __SIGLOST  : __result = "SIGLOST"; break;
#endif /* __SIGLOST */
#if defined(__SIGCLD) && (!defined(__SIGCHLD) || __SIGCLD != __SIGCHLD)
	case __SIGCLD   : __result = "SIGCLD"; break;
#endif /* __SIGCLD && (!__SIGCHLD || __SIGCLD != __SIGCHLD) */
#if defined(__SIGIOT) && (!defined(__SIGABRT) || __SIGIOT != __SIGABRT)
	case __SIGIOT   : __result = "SIGIOT"; break;
#endif /* __SIGIOT && (!__SIGABRT || __SIGIOT != __SIGABRT) */
#if defined(__SIGPOLL) && (!defined(__SIGIO) || __SIGPOLL != __SIGIO)
	case __SIGPOLL   : __result = "SIGPOLL"; break;
#endif /* __SIGPOLL && (!__SIGIO || __SIGPOLL != __SIGIO) */
#if defined(__SIGPWR) && (!defined(__SIGLOST) || __SIGPWR != __SIGLOST)
	case __SIGPWR   : __result = "SIGPWR"; break;
#endif /* __SIGPWR && (!__SIGLOST || __SIGPWR != __SIGLOST) */

	default:
		__result = __NULLPTR;
		break;
	}
	return __result;
#endif /* !__CRT_HAVE___p_sys_siglist && !__CRT_HAVE_sys_siglist && !__CRT_HAVE__sys_siglist */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_sigabbrev_np_defined
#define __local___localdep_sigabbrev_np_defined 1
#define __localdep_sigabbrev_np __LIBC_LOCAL_NAME(sigabbrev_np)
#endif /* !__local___localdep_sigabbrev_np_defined */
#endif /* !__local_sigabbrev_np_defined */
