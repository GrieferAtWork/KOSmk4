/* HASH CRC-32:0x21f42278 */
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
/* (>) Standard: ISO C89 (ANSI X3.159-1989) */
/* (>) Standard: POSIX.1 (Issue 1, IEEE Std 1003.1-1988) */
/* (#) Portability: Cygwin        (/newlib/libc/include/signal.h) */
/* (#) Portability: DJGPP         (/include/signal.h) */
/* (#) Portability: FreeBSD       (/include/signal.h) */
/* (#) Portability: GNU C Library (/signal/signal.h) */
/* (#) Portability: MSVC          (/include/signal.h) */
/* (#) Portability: MinGW         (/mingw-w64-headers/crt/signal.h) */
/* (#) Portability: NetBSD        (/include/signal.h) */
/* (#) Portability: Newlib        (/newlib/libc/include/signal.h) */
/* (#) Portability: OpenBSD       (/include/signal.h) */
/* (#) Portability: OpenSolaris   (/usr/src/head/signal.h) */
/* (#) Portability: Windows Kits  (/ucrt/signal.h) */
/* (#) Portability: diet libc     (/include/signal.h) */
/* (#) Portability: libc4/5       (/include/signal.h) */
/* (#) Portability: libc6         (/include/signal.h) */
/* (#) Portability: musl libc     (/include/signal.h) */
/* (#) Portability: uClibc        (/include/signal.h) */
#ifndef _SIGNAL_H
#define _SIGNAL_H 1

#ifdef _CXX_STDONLY_CSIGNAL
#ifdef __CXX_SYSTEM_HEADER
#undef _SIGNAL_H /* Allow the C-header to be re-included to import all std::-symbols into the global namespace. */
#else /* __CXX_SYSTEM_HEADER */
/* Import all symbols into the global namespace when re-including "signal.h" after "csignal" */
#ifndef __sig_atomic_t_defined
#define __sig_atomic_t_defined
__NAMESPACE_STD_USING(sig_atomic_t)
#endif /* !__sig_atomic_t_defined */
#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_XOPEN2K8)
#ifndef __size_t_defined
#define __size_t_defined
__NAMESPACE_STD_USING(size_t)
#endif /* !__size_t_defined */
#endif /* __USE_XOPEN_EXTENDED || __USE_XOPEN2K8 */
#if defined(__CRT_HAVE_raise) || ((defined(__CRT_HAVE_pthread_kill) || defined(__CRT_HAVE_thr_kill)) && (defined(__CRT_HAVE_pthread_self) || defined(__CRT_HAVE_thrd_current) || defined(__CRT_HAVE_thr_self))) || ((defined(__CRT_HAVE_kill) || defined(__CRT_HAVE___kill) || defined(__CRT_HAVE___libc_kill)) && (defined(__CRT_HAVE_getpid) || defined(__CRT_HAVE__getpid) || defined(__CRT_HAVE___getpid) || defined(__CRT_HAVE___libc_getpid)))
__NAMESPACE_STD_USING(raise)
#endif /* __CRT_HAVE_raise || ((__CRT_HAVE_pthread_kill || __CRT_HAVE_thr_kill) && (__CRT_HAVE_pthread_self || __CRT_HAVE_thrd_current || __CRT_HAVE_thr_self)) || ((__CRT_HAVE_kill || __CRT_HAVE___kill || __CRT_HAVE___libc_kill) && (__CRT_HAVE_getpid || __CRT_HAVE__getpid || __CRT_HAVE___getpid || __CRT_HAVE___libc_getpid)) */
#include <features.h>
#if (defined(__CRT_HAVE_signal) && defined(__USE_MISC)) || (defined(__CRT_HAVE__signal) && defined(__USE_MISC)) || defined(__CRT_HAVE_sysv_signal)
__NAMESPACE_STD_USING(signal)
#endif /* (__CRT_HAVE_signal && __USE_MISC) || (__CRT_HAVE__signal && __USE_MISC) || __CRT_HAVE_sysv_signal */
#undef _CXX_STDONLY_CSIGNAL
#endif /* !__CXX_SYSTEM_HEADER */
#else /* _CXX_STDONLY_CSIGNAL */
#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>

#include <asm/os/signal.h>
#include <bits/os/sigset.h>
#include <hybrid/typecore.h>
#include <bits/types.h>
#include <libc/errno.h>

#ifdef __USE_POSIX199309
#include <bits/os/timespec.h>
#endif /* __USE_POSIX199309 */

#ifdef __USE_MISC
#include <bits/os/sigcontext.h>
#endif /* __USE_MISC */

#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_XOPEN2K8)
#include <asm/os/sigstack.h>
#include <bits/os/sigstack.h> /* `struct sigstack', `struct sigaltstack' */
#if defined(__USE_XOPEN) || defined(__USE_XOPEN2K8)
#include <sys/ucontext.h>
#endif /* __USE_XOPEN || __USE_XOPEN2K8 */
#endif /* __USE_XOPEN_EXTENDED || __USE_XOPEN2K8 */

#if defined(__USE_POSIX199506) || defined(__USE_UNIX98)
#include <bits/crt/pthreadtypes.h>
#include <bits/os/sigval.h> /* union sigval */
#endif /* __USE_POSIX199506 || __USE_UNIX98 */

#ifdef __USE_POSIX
#include <bits/os/sigaction.h>
#endif /* __USE_POSIX */

#if defined(__USE_KOS) && defined(__KOS__)
#include <kos/bits/userprocmask.h>
#endif /* __USE_KOS && __KOS__ */

#if (defined(__USE_POSIX199309) || defined(__USE_XOPEN_EXTENDED) || defined(__USE_KOS))
#include <asm/os/sigevent.h>
#include <asm/os/siginfo.h>
#include <bits/os/sigevent.h> /* struct sigevent */
#include <bits/os/siginfo.h>  /* struct __siginfo_struct */
#include <bits/os/sigval.h>   /* union sigval */
#endif /* __USE_POSIX199309 || __USE_XOPEN_EXTENDED || __USE_KOS */

__SYSDECL_BEGIN

/* Fake signal functions. */
#if !defined(SIG_ERR) && defined(__SIG_ERR)
#define SIG_ERR (__CCAST(__sighandler_t)__SIG_ERR) /* Error return. */
#endif /* !SIG_ERR && __SIG_ERR */
#if !defined(SIG_DFL) && defined(__SIG_DFL)
#define SIG_DFL (__CCAST(__sighandler_t)__SIG_DFL) /* Default action. */
#endif /* !SIG_DFL && __SIG_DFL */
#if !defined(SIG_IGN) && defined(__SIG_IGN)
#define SIG_IGN (__CCAST(__sighandler_t)__SIG_IGN) /* Ignore signal. */
#endif /* !SIG_IGN && __SIG_IGN */

#ifdef __USE_DOS
#if !defined(SIG_GET) && defined(__SIG_GET)
#define SIG_GET (__CCAST(__sighandler_t)__SIG_GET) /* Only get the current handler (accepted by `signal(2)') */
#endif /* !SIG_GET && __SIG_GET */
#if !defined(SIG_SGE) && defined(__SIG_SGE)
#define SIG_SGE (__CCAST(__sighandler_t)__SIG_SGE) /* Signal gets error. */
#endif /* !SIG_SGE && __SIG_SGE */
#if !defined(SIG_ACK) && defined(__SIG_ACK)
#define SIG_ACK (__CCAST(__sighandler_t)__SIG_ACK) /* Acknowledge. */
#endif /* !SIG_ACK && __SIG_ACK */
#endif /* __USE_DOS */

#ifdef __USE_UNIX98
#if !defined(SIG_HOLD) && defined(__SIG_HOLD)
#define SIG_HOLD (__CCAST(__sighandler_t)__SIG_HOLD) /* Add signal to hold mask. */
#endif /* !SIG_HOLD && __SIG_HOLD */
#endif /* __USE_UNIX98 */

#ifdef __USE_KOS
#if !defined(SIG_TERM) && defined(__SIG_TERM)
#define SIG_TERM (__CCAST(__sighandler_t)__SIG_TERM) /* Terminate the receiving process. */
#endif /* !SIG_TERM && __SIG_TERM */
#if !defined(SIG_EXIT) && defined(__SIG_EXIT)
#define SIG_EXIT (__CCAST(__sighandler_t)__SIG_EXIT) /* Terminate the receiving thread. */
#endif /* !SIG_EXIT && __SIG_EXIT */
#if !defined(SIG_CONT) && defined(__SIG_CONT)
#define SIG_CONT (__CCAST(__sighandler_t)__SIG_CONT) /* Continue execution. */
#endif /* !SIG_CONT && __SIG_CONT */
#if !defined(SIG_STOP) && defined(__SIG_STOP)
#define SIG_STOP (__CCAST(__sighandler_t)__SIG_STOP) /* Suspend execution. */
#endif /* !SIG_STOP && __SIG_STOP */
#if !defined(SIG_CORE) && defined(__SIG_CORE)
#define SIG_CORE (__CCAST(__sighandler_t)__SIG_CORE) /* Create a coredump and terminate. */
#endif /* !SIG_CORE && __SIG_CORE */
#if !defined(SIG_GET) && defined(__SIG_GET)
#define SIG_GET  (__CCAST(__sighandler_t)__SIG_GET)  /* Only get the current handler (accepted by `signal(2)') */
#endif /* !SIG_GET && __SIG_GET */
#endif /* __USE_KOS */


/* Signals numbers. */
#if !defined(SIGHUP) && defined(__SIGHUP)
#define SIGHUP    __SIGHUP     /* Hangup (POSIX). */
#endif /* !SIGHUP && __SIGHUP */
#if !defined(SIGINT) && defined(__SIGINT)
#define SIGINT    __SIGINT     /* Interrupt (ANSI). */
#endif /* !SIGINT && __SIGINT */
#if !defined(SIGQUIT) && defined(__SIGQUIT)
#define SIGQUIT   __SIGQUIT    /* Quit (POSIX). */
#endif /* !SIGQUIT && __SIGQUIT */
#if !defined(SIGILL) && defined(__SIGILL)
#define SIGILL    __SIGILL     /* Illegal instruction (ANSI). */
#endif /* !SIGILL && __SIGILL */
#if !defined(SIGTRAP) && defined(__SIGTRAP)
#define SIGTRAP   __SIGTRAP    /* Trace trap (POSIX). */
#endif /* !SIGTRAP && __SIGTRAP */
#if !defined(SIGABRT) && defined(__SIGABRT)
#define SIGABRT   __SIGABRT    /* Abort (ANSI). */
#endif /* !SIGABRT && __SIGABRT */
#if !defined(SIGIOT) && defined(__SIGIOT)
#define SIGIOT    __SIGIOT     /* IOT trap (4.2 BSD). */
#endif /* !SIGIOT && __SIGIOT */
#if !defined(SIGBUS) && defined(__SIGBUS)
#define SIGBUS    __SIGBUS     /* BUS error (4.2 BSD). */
#endif /* !SIGBUS && __SIGBUS */
#if !defined(SIGFPE) && defined(__SIGFPE)
#define SIGFPE    __SIGFPE     /* Floating-point exception (ANSI). */
#endif /* !SIGFPE && __SIGFPE */
#if !defined(SIGKILL) && defined(__SIGKILL)
#define SIGKILL   __SIGKILL    /* Kill, unblockable (POSIX). */
#endif /* !SIGKILL && __SIGKILL */
#if !defined(SIGUSR1) && defined(__SIGUSR1)
#define SIGUSR1   __SIGUSR1    /* User-defined signal 1 (POSIX). */
#endif /* !SIGUSR1 && __SIGUSR1 */
#if !defined(SIGSEGV) && defined(__SIGSEGV)
#define SIGSEGV   __SIGSEGV    /* Segmentation violation (ANSI). */
#endif /* !SIGSEGV && __SIGSEGV */
#if !defined(SIGUSR2) && defined(__SIGUSR2)
#define SIGUSR2   __SIGUSR2    /* User-defined signal 2 (POSIX). */
#endif /* !SIGUSR2 && __SIGUSR2 */
#if !defined(SIGPIPE) && defined(__SIGPIPE)
#define SIGPIPE   __SIGPIPE    /* Broken pipe (POSIX). */
#endif /* !SIGPIPE && __SIGPIPE */
#if !defined(SIGALRM) && defined(__SIGALRM)
#define SIGALRM   __SIGALRM    /* Alarm clock (POSIX). */
#endif /* !SIGALRM && __SIGALRM */
#if !defined(SIGTERM) && defined(__SIGTERM)
#define SIGTERM   __SIGTERM    /* Termination (ANSI). */
#endif /* !SIGTERM && __SIGTERM */
#if !defined(SIGSTKFLT) && defined(__SIGSTKFLT)
#define SIGSTKFLT __SIGSTKFLT  /* Stack fault. */
#endif /* !SIGSTKFLT && __SIGSTKFLT */
#if !defined(SIGCHLD) && defined(__SIGCHLD)
#define SIGCHLD   __SIGCHLD    /* Child status has changed (POSIX). */
#endif /* !SIGCHLD && __SIGCHLD */
#if !defined(SIGCONT) && defined(__SIGCONT)
#define SIGCONT   __SIGCONT    /* Continue (POSIX). */
#endif /* !SIGCONT && __SIGCONT */
#if !defined(SIGSTOP) && defined(__SIGSTOP)
#define SIGSTOP   __SIGSTOP    /* Stop, unblockable (POSIX). */
#endif /* !SIGSTOP && __SIGSTOP */
#if !defined(SIGTSTP) && defined(__SIGTSTP)
#define SIGTSTP   __SIGTSTP    /* Keyboard stop (POSIX). */
#endif /* !SIGTSTP && __SIGTSTP */
#if !defined(SIGTTIN) && defined(__SIGTTIN)
#define SIGTTIN   __SIGTTIN    /* Background read from tty (POSIX). */
#endif /* !SIGTTIN && __SIGTTIN */
#if !defined(SIGTTOU) && defined(__SIGTTOU)
#define SIGTTOU   __SIGTTOU    /* Background write to tty (POSIX). */
#endif /* !SIGTTOU && __SIGTTOU */
#if !defined(SIGURG) && defined(__SIGURG)
#define SIGURG    __SIGURG     /* Urgent condition on socket (4.2 BSD). */
#endif /* !SIGURG && __SIGURG */
#if !defined(SIGXCPU) && defined(__SIGXCPU)
#define SIGXCPU   __SIGXCPU    /* CPU limit exceeded (4.2 BSD). */
#endif /* !SIGXCPU && __SIGXCPU */
#if !defined(SIGXFSZ) && defined(__SIGXFSZ)
#define SIGXFSZ   __SIGXFSZ    /* File size limit exceeded (4.2 BSD). */
#endif /* !SIGXFSZ && __SIGXFSZ */
#if !defined(SIGVTALRM) && defined(__SIGVTALRM)
#define SIGVTALRM __SIGVTALRM  /* Virtual alarm clock (4.2 BSD). */
#endif /* !SIGVTALRM && __SIGVTALRM */
#if !defined(SIGPROF) && defined(__SIGPROF)
#define SIGPROF   __SIGPROF    /* Profiling alarm clock (4.2 BSD). */
#endif /* !SIGPROF && __SIGPROF */
#if !defined(SIGWINCH) && defined(__SIGWINCH)
#define SIGWINCH  __SIGWINCH   /* Window size change (4.3 BSD, Sun). */
#endif /* !SIGWINCH && __SIGWINCH */
#if !defined(SIGIO) && defined(__SIGIO)
#define SIGIO     __SIGIO      /* I/O now possible (4.2 BSD). */
#endif /* !SIGIO && __SIGIO */
#if !defined(SIGPOLL) && defined(__SIGPOLL)
#define SIGPOLL   __SIGPOLL    /* Pollable event occurred (System V). */
#endif /* !SIGPOLL && __SIGPOLL */
#if !defined(SIGPWR) && defined(__SIGPWR)
#define SIGPWR    __SIGPWR     /* Power failure restart (System V). */
#endif /* !SIGPWR && __SIGPWR */
#if !defined(SIGSYS) && defined(__SIGSYS)
#define SIGSYS    __SIGSYS     /* Bad system call. */
#endif /* !SIGSYS && __SIGSYS */
#if !defined(SIGCLD) && defined(__SIGCHLD)
#define SIGCLD    __SIGCHLD    /* Same as SIGCHLD (System V). */
#endif /* !SIGCLD && __SIGCHLD */
#if defined(__USE_KOS) && !defined(SIGRPC) && defined(__SIGRPC)
#define SIGRPC    __SIGRPC     /* Default signal number used for <kos/rpc.h> */
#endif /* __USE_KOS && !SIGRPC && __SIGRPC */
#ifndef SIGUNUSED
#ifdef __SIGUNUSED
#define SIGUNUSED __SIGUNUSED
#elif defined(__SIGSYS)
#define SIGUNUSED __SIGSYS
#endif /* ... */
#endif /* !SIGUNUSED */

#if !defined(_NSIG) && defined(__NSIG)
#define _NSIG __NSIG /* Biggest signal number + 1 (including real-time signals). */
#endif /* !_NSIG && __NSIG */

/* These are the hard limits of the kernel.
 * These values should not be used directly at user level. */
#ifndef SIGRTMIN
#if defined(__SIGRTMIN) && (!defined(__CRT_HAVE___libc_current_sigrtmin) || !defined(__CC__))
#define SIGRTMIN __SIGRTMIN
#else /* __SIGRTMIN && (!__CRT_HAVE___libc_current_sigrtmin || !__CC__) */
#define SIGRTMIN __libc_current_sigrtmin()
#endif /* !__SIGRTMIN || (__CRT_HAVE___libc_current_sigrtmin && __CC__) */
#endif /* !SIGRTMIN */
#ifndef SIGRTMAX
#if defined(__SIGRTMAX) && (!defined(__CRT_HAVE___libc_current_sigrtmax) || !defined(__CC__))
#define SIGRTMAX __SIGRTMAX
#else /* __SIGRTMAX && (!__CRT_HAVE___libc_current_sigrtmax || !__CC__) */
#define SIGRTMAX __libc_current_sigrtmax()
#endif /* !__SIGRTMAX || (__CRT_HAVE___libc_current_sigrtmax && __CC__) */
#endif /* !SIGRTMAX */

#ifdef __USE_DOS
/* Define DOS's signal name aliases. */
#if !defined(SIGBREAK) && defined(__SIGBREAK)
#define SIGBREAK __SIGBREAK /* Background read from tty (POSIX). */
#endif /* !SIGBREAK && __SIGBREAK */
#ifndef SIGABRT_COMPAT
#ifdef __SIGABRT_COMPAT
#define SIGABRT_COMPAT __SIGABRT_COMPAT /* Abort (ANSI). */
#elif defined(__SIGABRT)
#define SIGABRT_COMPAT __SIGABRT        /* Abort (ANSI). */
#endif /* ... */
#endif /* !SIGABRT_COMPAT */
#endif /* __USE_DOS */




#ifdef __USE_POSIX
/* Bits in `sa_flags'. */
#if !defined(SA_NOCLDSTOP) && defined(__SA_NOCLDSTOP)
#define SA_NOCLDSTOP __SA_NOCLDSTOP /* Don't send SIGCHLD when children stop (Ignored for anything other than SIGCLD). */
#endif /* !SA_NOCLDSTOP && __SA_NOCLDSTOP */
#if !defined(SA_NOCLDWAIT) && defined(__SA_NOCLDWAIT)
#define SA_NOCLDWAIT __SA_NOCLDWAIT /* Don't create zombie on child death (Ignored for anything other than SIGCLD). */
#endif /* !SA_NOCLDWAIT && __SA_NOCLDWAIT */
#if !defined(SA_SIGINFO) && defined(__SA_SIGINFO)
#define SA_SIGINFO __SA_SIGINFO /* Invoke signal-catching function with three arguments instead of one. */
#endif /* !SA_SIGINFO && __SA_SIGINFO */

#ifdef __USE_KOS_KERNEL
#if !defined(SA_RESTORER) && defined(__SA_RESTORER)
#define SA_RESTORER __SA_RESTORER /* A custom  signal restore  function (`sa_restorer')  was given.  This
                                   * flag is set by libc, after having filled in the `sa_restorer' field. */
#endif /* !SA_RESTORER && __SA_RESTORER */
#endif /* __USE_KOS_KERNEL */

#if defined(__USE_UNIX98) || defined(__USE_MISC)
#if !defined(SA_ONSTACK) && defined(__SA_ONSTACK)
#define SA_ONSTACK __SA_ONSTACK /* Execute the handler on sigaltstack. */
#endif /* !SA_ONSTACK && __SA_ONSTACK */
#endif /* __USE_UNIX98 || __USE_MISC */

#if defined(__USE_UNIX98) || defined(__USE_XOPEN2K8)
#if !defined(SA_RESTART) && defined(__SA_RESTART)
#define SA_RESTART __SA_RESTART /* Restart restartable syscall on signal return. */
#endif /* !SA_RESTART && __SA_RESTART */
#if !defined(SA_NODEFER) && defined(__SA_NODEFER)
#define SA_NODEFER __SA_NODEFER /* Don't automatically block the signal when its handler is being executed. */
#endif /* !SA_NODEFER && __SA_NODEFER */
#if !defined(SA_RESETHAND) && defined(__SA_RESETHAND)
#define SA_RESETHAND __SA_RESETHAND /* Reset to SIG_DFL on entry to handler. */
#endif /* !SA_RESETHAND && __SA_RESETHAND */
#endif /* __USE_UNIX98 || __USE_XOPEN2K8 */

#ifdef __USE_MISC
#if !defined(SA_INTERRUPT) && defined(__SA_INTERRUPT)
#define SA_INTERRUPT __SA_INTERRUPT /* Historical no-op. */
#endif /* !SA_INTERRUPT && __SA_INTERRUPT */
/* Some aliases for the SA_ constants. */
#if !defined(SA_NOMASK) && defined(__SA_NODEFER)
#define SA_NOMASK __SA_NODEFER
#endif /* !SA_NOMASK && __SA_NODEFER */
#if !defined(SA_ONESHOT) && defined(__SA_RESETHAND)
#define SA_ONESHOT __SA_RESETHAND
#endif /* !SA_ONESHOT && __SA_RESETHAND */
#if !defined(SA_STACK) && defined(__SA_ONSTACK)
#define SA_STACK __SA_ONSTACK
#endif /* !SA_STACK && __SA_ONSTACK */
#endif /* __USE_MISC */

/* Values for the HOW argument to `sigprocmask'. */
#if !defined(SIG_BLOCK) && defined(__SIG_BLOCK)
#define SIG_BLOCK __SIG_BLOCK /* Block signals. */
#endif /* !SIG_BLOCK && __SIG_BLOCK */
#if !defined(SIG_UNBLOCK) && defined(__SIG_UNBLOCK)
#define SIG_UNBLOCK __SIG_UNBLOCK /* Unblock signals. */
#endif /* !SIG_UNBLOCK && __SIG_UNBLOCK */
#if !defined(SIG_SETMASK) && defined(__SIG_SETMASK)
#define SIG_SETMASK __SIG_SETMASK /* Set the set of blocked signals. */
#endif /* !SIG_SETMASK && __SIG_SETMASK */
#endif /* __USE_POSIX */

#if (defined(__USE_POSIX199309) || defined(__USE_XOPEN_EXTENDED) || defined(__USE_KOS))

/* `sigev_notify' values. */
#if (defined(__SIGEV_SIGNAL) || defined(__SIGEV_NONE) ||      \
     defined(__SIGEV_THREAD) || defined(__SIGEV_THREAD_ID) || \
     defined(__SIGEV_INLINE_THREAD))
/*[[[enum]]]*/
#ifdef __CC__
enum {
#ifdef __SIGEV_SIGNAL
	SIGEV_SIGNAL    = __SIGEV_SIGNAL, /* Notify via signal. */
#endif /* __SIGEV_SIGNAL */
#ifdef __SIGEV_NONE
	SIGEV_NONE      = __SIGEV_NONE, /* Other notification: meaningless. */
#endif /* __SIGEV_NONE */
#ifdef __SIGEV_THREAD
	SIGEV_THREAD    = __SIGEV_THREAD, /* Deliver via thread creation. */
#endif /* __SIGEV_THREAD */
#ifdef __SIGEV_THREAD_ID
	SIGEV_THREAD_ID = __SIGEV_THREAD_ID, /* Send signal to specific thread. */
#endif /* __SIGEV_THREAD_ID */
#ifdef __SIGEV_INLINE_THREAD
	SIGEV_INLINE_THREAD = __SIGEV_INLINE_THREAD, /* KOS-only: Same as `SIGEV_THREAD', but try not to actually spawn a thread, though
	                                              * this event kind  is allowed to  be implemented as  an alias for  `SIGEV_THREAD'.
	                                              * Semantically, the following rules have to be followed by  `SIGEV_INLINE_THREAD':
	                                              *   - You mustn't call `pthread_exit(3)'
	                                              * In the context of AIO completion events (s.a. <aio.h>), the following applies:
	                                              *   - If triggered as a result of `aio_cancel(3)', the call to `aio_cancel()' may
	                                              *     not return until your callback has also returned (because your callback may
	                                              *     have hi-jacked that thread)
	                                              * NOTE: You are allowed to make modifications to `errno', so don't worry about it.
	                                              * NOTE: Depending on context, this may be identical to `SIGEV_THREAD'!
	                                              *
	                                              * Generally speaking,  you should  act like  your callback  is invoked  as though  it
	                                              * were a signal handler (note that it may actually be invoked from a signal handler),
	                                              * meaning that you should only call NOBLOCK and re-entrance-safe functions. */
#endif /* __SIGEV_INLINE_THREAD */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#ifdef __SIGEV_SIGNAL
#define SIGEV_SIGNAL        SIGEV_SIGNAL        /* Notify via signal. */
#endif /* __SIGEV_SIGNAL */
#ifdef __SIGEV_NONE
#define SIGEV_NONE          SIGEV_NONE          /* Other notification: meaningless. */
#endif /* __SIGEV_NONE */
#ifdef __SIGEV_THREAD
#define SIGEV_THREAD        SIGEV_THREAD        /* Deliver via thread creation. */
#endif /* __SIGEV_THREAD */
#ifdef __SIGEV_THREAD_ID
#define SIGEV_THREAD_ID     SIGEV_THREAD_ID     /* Send signal to specific thread. */
#endif /* __SIGEV_THREAD_ID */
#ifdef __SIGEV_INLINE_THREAD
#define SIGEV_INLINE_THREAD SIGEV_INLINE_THREAD /* KOS-only: Same as `SIGEV_THREAD', but try not to actually spawn a thread, though
                                                 * this event kind  is allowed to  be implemented as  an alias for  `SIGEV_THREAD'.
                                                 * Semantically, the following rules have to be followed by  `SIGEV_INLINE_THREAD':
                                                 *   - You mustn't call `pthread_exit(3)'
                                                 * In the context of AIO completion events (s.a. <aio.h>), the following applies:
                                                 *   - If triggered as a result of `aio_cancel(3)', the call to `aio_cancel()' may
                                                 *     not return until your callback has also returned (because your callback may
                                                 *     have hi-jacked that thread)
                                                 * NOTE: You are allowed to make modifications to `errno', so don't worry about it.
                                                 * NOTE: Depending on context, this may be identical to `SIGEV_THREAD'!
                                                 *
                                                 * Generally speaking,  you should  act like  your callback  is invoked  as though  it
                                                 * were a signal handler (note that it may actually be invoked from a signal handler),
                                                 * meaning that you should only call NOBLOCK and re-entrance-safe functions. */
#endif /* __SIGEV_INLINE_THREAD */
#else /* __COMPILER_PREFERR_ENUMS */
#ifdef __SIGEV_SIGNAL
#define SIGEV_SIGNAL        __SIGEV_SIGNAL        /* Notify via signal. */
#endif /* __SIGEV_SIGNAL */
#ifdef __SIGEV_NONE
#define SIGEV_NONE          __SIGEV_NONE          /* Other notification: meaningless. */
#endif /* __SIGEV_NONE */
#ifdef __SIGEV_THREAD
#define SIGEV_THREAD        __SIGEV_THREAD        /* Deliver via thread creation. */
#endif /* __SIGEV_THREAD */
#ifdef __SIGEV_THREAD_ID
#define SIGEV_THREAD_ID     __SIGEV_THREAD_ID     /* Send signal to specific thread. */
#endif /* __SIGEV_THREAD_ID */
#ifdef __SIGEV_INLINE_THREAD
#define SIGEV_INLINE_THREAD __SIGEV_INLINE_THREAD /* KOS-only: Same as `SIGEV_THREAD', but try not to actually spawn a thread, though
                                                   * this event kind  is allowed to  be implemented as  an alias for  `SIGEV_THREAD'.
                                                   * Semantically, the following rules have to be followed by  `SIGEV_INLINE_THREAD':
                                                   *   - You mustn't call `pthread_exit(3)'
                                                   * In the context of AIO completion events (s.a. <aio.h>), the following applies:
                                                   *   - If triggered as a result of `aio_cancel(3)', the call to `aio_cancel()' may
                                                   *     not return until your callback has also returned (because your callback may
                                                   *     have hi-jacked that thread)
                                                   * NOTE: You are allowed to make modifications to `errno', so don't worry about it.
                                                   * NOTE: Depending on context, this may be identical to `SIGEV_THREAD'!
                                                   *
                                                   * Generally speaking,  you should  act like  your callback  is invoked  as though  it
                                                   * were a signal handler (note that it may actually be invoked from a signal handler),
                                                   * meaning that you should only call NOBLOCK and re-entrance-safe functions. */
#endif /* __SIGEV_INLINE_THREAD */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/
#endif /* __SIGEV_SIGNAL || __SIGEV_NONE || __SIGEV_THREAD || __SIGEV_THREAD_ID */


/* Values for `si_code'. Positive values are reserved for kernel-generated signals. */
#if (defined(__SI_ASYNCNL) || defined(__SI_TKILL) || defined(__SI_SIGIO) || \
     defined(__SI_ASYNCIO) || defined(__SI_MESGQ) || defined(__SI_TIMER) || \
     defined(__SI_QUEUE) || defined(__SI_USER) || defined(__SI_KERNEL))
/*[[[enum]]]*/
#ifdef __CC__
enum {
#ifdef __SI_ASYNCNL
	SI_ASYNCNL = __SI_ASYNCNL, /* Sent by asynch name lookup completion. */
#endif /* __SI_ASYNCNL */
#ifdef __SI_TKILL
	SI_TKILL = __SI_TKILL,     /* Sent by tkill. */
#endif /* __SI_TKILL */
#ifdef __SI_SIGIO
	SI_SIGIO = __SI_SIGIO,     /* Sent by queued SIGIO. */
#endif /* __SI_SIGIO */
#ifdef __SI_ASYNCIO
	SI_ASYNCIO = __SI_ASYNCIO, /* Sent by AIO completion. */
#endif /* __SI_ASYNCIO */
#ifdef __SI_MESGQ
	SI_MESGQ = __SI_MESGQ,     /* Sent by real time mesq state change. */
#endif /* __SI_MESGQ */
#ifdef __SI_TIMER
	SI_TIMER = __SI_TIMER,     /* Sent by timer expiration. */
#endif /* __SI_TIMER */
#ifdef __SI_QUEUE
	SI_QUEUE = __SI_QUEUE,     /* Sent by sigqueue. */
#endif /* __SI_QUEUE */
#ifdef __SI_USER
	SI_USER = __SI_USER,       /* Sent by kill, sigsend. */
#endif /* __SI_USER */
#ifdef __SI_KERNEL
	SI_KERNEL = __SI_KERNEL,   /* Send by kernel. */
#endif /* __SI_KERNEL */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#ifdef __SI_ASYNCNL
#define SI_ASYNCNL SI_ASYNCNL /* Sent by asynch name lookup completion. */
#endif /* __SI_ASYNCNL */
#ifdef __SI_TKILL
#define SI_TKILL   SI_TKILL   /* Sent by tkill. */
#endif /* __SI_TKILL */
#ifdef __SI_SIGIO
#define SI_SIGIO   SI_SIGIO   /* Sent by queued SIGIO. */
#endif /* __SI_SIGIO */
#ifdef __SI_ASYNCIO
#define SI_ASYNCIO SI_ASYNCIO /* Sent by AIO completion. */
#endif /* __SI_ASYNCIO */
#ifdef __SI_MESGQ
#define SI_MESGQ   SI_MESGQ   /* Sent by real time mesq state change. */
#endif /* __SI_MESGQ */
#ifdef __SI_TIMER
#define SI_TIMER   SI_TIMER   /* Sent by timer expiration. */
#endif /* __SI_TIMER */
#ifdef __SI_QUEUE
#define SI_QUEUE   SI_QUEUE   /* Sent by sigqueue. */
#endif /* __SI_QUEUE */
#ifdef __SI_USER
#define SI_USER    SI_USER    /* Sent by kill, sigsend. */
#endif /* __SI_USER */
#ifdef __SI_KERNEL
#define SI_KERNEL  SI_KERNEL  /* Send by kernel. */
#endif /* __SI_KERNEL */
#else /* __COMPILER_PREFERR_ENUMS */
#ifdef __SI_ASYNCNL
#define SI_ASYNCNL __SI_ASYNCNL /* Sent by asynch name lookup completion. */
#endif /* __SI_ASYNCNL */
#ifdef __SI_TKILL
#define SI_TKILL   __SI_TKILL   /* Sent by tkill. */
#endif /* __SI_TKILL */
#ifdef __SI_SIGIO
#define SI_SIGIO   __SI_SIGIO   /* Sent by queued SIGIO. */
#endif /* __SI_SIGIO */
#ifdef __SI_ASYNCIO
#define SI_ASYNCIO __SI_ASYNCIO /* Sent by AIO completion. */
#endif /* __SI_ASYNCIO */
#ifdef __SI_MESGQ
#define SI_MESGQ   __SI_MESGQ   /* Sent by real time mesq state change. */
#endif /* __SI_MESGQ */
#ifdef __SI_TIMER
#define SI_TIMER   __SI_TIMER   /* Sent by timer expiration. */
#endif /* __SI_TIMER */
#ifdef __SI_QUEUE
#define SI_QUEUE   __SI_QUEUE   /* Sent by sigqueue. */
#endif /* __SI_QUEUE */
#ifdef __SI_USER
#define SI_USER    __SI_USER    /* Sent by kill, sigsend. */
#endif /* __SI_USER */
#ifdef __SI_KERNEL
#define SI_KERNEL  __SI_KERNEL  /* Send by kernel. */
#endif /* __SI_KERNEL */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/
#endif /* __SI_... */



#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_XOPEN2K8)

/* `si_code' values for SIGILL signal. */
#if (defined(__ILL_ILLOPC) || defined(__ILL_ILLOPN) || defined(__ILL_ILLADR) || \
     defined(__ILL_ILLTRP) || defined(__ILL_PRVOPC) || defined(__ILL_PRVREG) || \
     defined(__ILL_COPROC) || defined(__ILL_BADSTK))
/*[[[enum]]]*/
#ifdef __CC__
enum {
#ifdef __ILL_ILLOPC
	ILL_ILLOPC = __ILL_ILLOPC, /* Illegal opcode. */
#endif /* __ILL_ILLOPC */
#ifdef __ILL_ILLOPN
	ILL_ILLOPN = __ILL_ILLOPN, /* Illegal operand. */
#endif /* __ILL_ILLOPN */
#ifdef __ILL_ILLADR
	ILL_ILLADR = __ILL_ILLADR, /* Illegal addressing mode. */
#endif /* __ILL_ILLADR */
#ifdef __ILL_ILLTRP
	ILL_ILLTRP = __ILL_ILLTRP, /* Illegal trap. */
#endif /* __ILL_ILLTRP */
#ifdef __ILL_PRVOPC
	ILL_PRVOPC = __ILL_PRVOPC, /* Privileged opcode. */
#endif /* __ILL_PRVOPC */
#ifdef __ILL_PRVREG
	ILL_PRVREG = __ILL_PRVREG, /* Privileged register. */
#endif /* __ILL_PRVREG */
#ifdef __ILL_COPROC
	ILL_COPROC = __ILL_COPROC, /* Coprocessor error. */
#endif /* __ILL_COPROC */
#ifdef __ILL_BADSTK
	ILL_BADSTK = __ILL_BADSTK  /* Internal stack error. */
#endif /* __ILL_BADSTK */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#ifdef __ILL_ILLOPC
#define ILL_ILLOPC ILL_ILLOPC /* Illegal opcode. */
#endif /* __ILL_ILLOPC */
#ifdef __ILL_ILLOPN
#define ILL_ILLOPN ILL_ILLOPN /* Illegal operand. */
#endif /* __ILL_ILLOPN */
#ifdef __ILL_ILLADR
#define ILL_ILLADR ILL_ILLADR /* Illegal addressing mode. */
#endif /* __ILL_ILLADR */
#ifdef __ILL_ILLTRP
#define ILL_ILLTRP ILL_ILLTRP /* Illegal trap. */
#endif /* __ILL_ILLTRP */
#ifdef __ILL_PRVOPC
#define ILL_PRVOPC ILL_PRVOPC /* Privileged opcode. */
#endif /* __ILL_PRVOPC */
#ifdef __ILL_PRVREG
#define ILL_PRVREG ILL_PRVREG /* Privileged register. */
#endif /* __ILL_PRVREG */
#ifdef __ILL_COPROC
#define ILL_COPROC ILL_COPROC /* Coprocessor error. */
#endif /* __ILL_COPROC */
#ifdef __ILL_BADSTK
#define ILL_BADSTK ILL_BADSTK /* Internal stack error. */
#endif /* __ILL_BADSTK */
#else /* __COMPILER_PREFERR_ENUMS */
#ifdef __ILL_ILLOPC
#define ILL_ILLOPC __ILL_ILLOPC /* Illegal opcode. */
#endif /* __ILL_ILLOPC */
#ifdef __ILL_ILLOPN
#define ILL_ILLOPN __ILL_ILLOPN /* Illegal operand. */
#endif /* __ILL_ILLOPN */
#ifdef __ILL_ILLADR
#define ILL_ILLADR __ILL_ILLADR /* Illegal addressing mode. */
#endif /* __ILL_ILLADR */
#ifdef __ILL_ILLTRP
#define ILL_ILLTRP __ILL_ILLTRP /* Illegal trap. */
#endif /* __ILL_ILLTRP */
#ifdef __ILL_PRVOPC
#define ILL_PRVOPC __ILL_PRVOPC /* Privileged opcode. */
#endif /* __ILL_PRVOPC */
#ifdef __ILL_PRVREG
#define ILL_PRVREG __ILL_PRVREG /* Privileged register. */
#endif /* __ILL_PRVREG */
#ifdef __ILL_COPROC
#define ILL_COPROC __ILL_COPROC /* Coprocessor error. */
#endif /* __ILL_COPROC */
#ifdef __ILL_BADSTK
#define ILL_BADSTK __ILL_BADSTK /* Internal stack error. */
#endif /* __ILL_BADSTK */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/
#endif /* __ILL_... */



/* `si_code' values for SIGFPE signal. */
#if (defined(__FPE_INTDIV) || defined(__FPE_INTOVF) || defined(__FPE_FLTDIV) || \
     defined(__FPE_FLTOVF) || defined(__FPE_FLTUND) || defined(__FPE_FLTRES) || \
     defined(__FPE_FLTINV) || defined(__FPE_FLTSUB))
/*[[[enum]]]*/
#ifdef __CC__
enum {
#ifdef __FPE_INTDIV
	FPE_INTDIV = __FPE_INTDIV, /* Integer divide by zero. */
#endif /* __FPE_INTDIV */
#ifdef __FPE_INTOVF
	FPE_INTOVF = __FPE_INTOVF, /* Integer overflow. */
#endif /* __FPE_INTOVF */
#ifdef __FPE_FLTDIV
	FPE_FLTDIV = __FPE_FLTDIV, /* Floating point divide by zero. */
#endif /* __FPE_FLTDIV */
#ifdef __FPE_FLTOVF
	FPE_FLTOVF = __FPE_FLTOVF, /* Floating point overflow. */
#endif /* __FPE_FLTOVF */
#ifdef __FPE_FLTUND
	FPE_FLTUND = __FPE_FLTUND, /* Floating point underflow. */
#endif /* __FPE_FLTUND */
#ifdef __FPE_FLTRES
	FPE_FLTRES = __FPE_FLTRES, /* Floating point inexact result. */
#endif /* __FPE_FLTRES */
#ifdef __FPE_FLTINV
	FPE_FLTINV = __FPE_FLTINV, /* Floating point invalid operation. */
#endif /* __FPE_FLTINV */
#ifdef __FPE_FLTSUB
	FPE_FLTSUB = __FPE_FLTSUB  /* Subscript out of range. */
#endif /* __FPE_FLTSUB */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#ifdef __FPE_INTDIV
#define FPE_INTDIV FPE_INTDIV /* Integer divide by zero. */
#endif /* __FPE_INTDIV */
#ifdef __FPE_INTOVF
#define FPE_INTOVF FPE_INTOVF /* Integer overflow. */
#endif /* __FPE_INTOVF */
#ifdef __FPE_FLTDIV
#define FPE_FLTDIV FPE_FLTDIV /* Floating point divide by zero. */
#endif /* __FPE_FLTDIV */
#ifdef __FPE_FLTOVF
#define FPE_FLTOVF FPE_FLTOVF /* Floating point overflow. */
#endif /* __FPE_FLTOVF */
#ifdef __FPE_FLTUND
#define FPE_FLTUND FPE_FLTUND /* Floating point underflow. */
#endif /* __FPE_FLTUND */
#ifdef __FPE_FLTRES
#define FPE_FLTRES FPE_FLTRES /* Floating point inexact result. */
#endif /* __FPE_FLTRES */
#ifdef __FPE_FLTINV
#define FPE_FLTINV FPE_FLTINV /* Floating point invalid operation. */
#endif /* __FPE_FLTINV */
#ifdef __FPE_FLTSUB
#define FPE_FLTSUB FPE_FLTSUB /* Subscript out of range. */
#endif /* __FPE_FLTSUB */
#else /* __COMPILER_PREFERR_ENUMS */
#ifdef __FPE_INTDIV
#define FPE_INTDIV __FPE_INTDIV /* Integer divide by zero. */
#endif /* __FPE_INTDIV */
#ifdef __FPE_INTOVF
#define FPE_INTOVF __FPE_INTOVF /* Integer overflow. */
#endif /* __FPE_INTOVF */
#ifdef __FPE_FLTDIV
#define FPE_FLTDIV __FPE_FLTDIV /* Floating point divide by zero. */
#endif /* __FPE_FLTDIV */
#ifdef __FPE_FLTOVF
#define FPE_FLTOVF __FPE_FLTOVF /* Floating point overflow. */
#endif /* __FPE_FLTOVF */
#ifdef __FPE_FLTUND
#define FPE_FLTUND __FPE_FLTUND /* Floating point underflow. */
#endif /* __FPE_FLTUND */
#ifdef __FPE_FLTRES
#define FPE_FLTRES __FPE_FLTRES /* Floating point inexact result. */
#endif /* __FPE_FLTRES */
#ifdef __FPE_FLTINV
#define FPE_FLTINV __FPE_FLTINV /* Floating point invalid operation. */
#endif /* __FPE_FLTINV */
#ifdef __FPE_FLTSUB
#define FPE_FLTSUB __FPE_FLTSUB /* Subscript out of range. */
#endif /* __FPE_FLTSUB */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/
#endif /* __FPE_... */



/* `si_code' values for SIGSEGV signal. */
#if defined(__SEGV_MAPERR) || defined(__SEGV_ACCERR)
/*[[[enum]]]*/
#ifdef __CC__
enum {
#ifdef __SEGV_MAPERR
	SEGV_MAPERR = __SEGV_MAPERR, /* Address not mapped to object. */
#endif /* __SEGV_MAPERR */
#ifdef __SEGV_ACCERR
	SEGV_ACCERR = __SEGV_ACCERR  /* Invalid permissions for mapped object. */
#endif /* __SEGV_ACCERR */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#ifdef __SEGV_MAPERR
#define SEGV_MAPERR SEGV_MAPERR /* Address not mapped to object. */
#endif /* __SEGV_MAPERR */
#ifdef __SEGV_ACCERR
#define SEGV_ACCERR SEGV_ACCERR /* Invalid permissions for mapped object. */
#endif /* __SEGV_ACCERR */
#else /* __COMPILER_PREFERR_ENUMS */
#ifdef __SEGV_MAPERR
#define SEGV_MAPERR __SEGV_MAPERR /* Address not mapped to object. */
#endif /* __SEGV_MAPERR */
#ifdef __SEGV_ACCERR
#define SEGV_ACCERR __SEGV_ACCERR /* Invalid permissions for mapped object. */
#endif /* __SEGV_ACCERR */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/
#endif /* __SEGV_... */



/* `si_code' values for SIGBUS signal. */
#if (defined(__BUS_ADRALN) || defined(__BUS_ADRERR) ||    \
     defined(__BUS_OBJERR) || defined(__BUS_MCEERR_AR) || \
     defined(__BUS_MCEERR_AO))
/*[[[enum]]]*/
#ifdef __CC__
enum {
#ifdef __BUS_ADRALN
	BUS_ADRALN    = __BUS_ADRALN,    /* Invalid address alignment. */
#endif /* __BUS_ADRALN */
#ifdef __BUS_ADRERR
	BUS_ADRERR    = __BUS_ADRERR,    /* Non-existent physical address. */
#endif /* __BUS_ADRERR */
#ifdef __BUS_OBJERR
	BUS_OBJERR    = __BUS_OBJERR,    /* Object specific hardware error. */
#endif /* __BUS_OBJERR */
#ifdef __BUS_MCEERR_AR
	BUS_MCEERR_AR = __BUS_MCEERR_AR, /* Hardware memory error: action required. */
#endif /* __BUS_MCEERR_AR */
#ifdef __BUS_MCEERR_AO
	BUS_MCEERR_AO = __BUS_MCEERR_AO  /* Hardware memory error: action optional. */
#endif /* __BUS_MCEERR_AO */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#ifdef __BUS_ADRALN
#define BUS_ADRALN    BUS_ADRALN    /* Invalid address alignment. */
#endif /* __BUS_ADRALN */
#ifdef __BUS_ADRERR
#define BUS_ADRERR    BUS_ADRERR    /* Non-existent physical address. */
#endif /* __BUS_ADRERR */
#ifdef __BUS_OBJERR
#define BUS_OBJERR    BUS_OBJERR    /* Object specific hardware error. */
#endif /* __BUS_OBJERR */
#ifdef __BUS_MCEERR_AR
#define BUS_MCEERR_AR BUS_MCEERR_AR /* Hardware memory error: action required. */
#endif /* __BUS_MCEERR_AR */
#ifdef __BUS_MCEERR_AO
#define BUS_MCEERR_AO BUS_MCEERR_AO /* Hardware memory error: action optional. */
#endif /* __BUS_MCEERR_AO */
#else /* __COMPILER_PREFERR_ENUMS */
#ifdef __BUS_ADRALN
#define BUS_ADRALN    __BUS_ADRALN    /* Invalid address alignment. */
#endif /* __BUS_ADRALN */
#ifdef __BUS_ADRERR
#define BUS_ADRERR    __BUS_ADRERR    /* Non-existent physical address. */
#endif /* __BUS_ADRERR */
#ifdef __BUS_OBJERR
#define BUS_OBJERR    __BUS_OBJERR    /* Object specific hardware error. */
#endif /* __BUS_OBJERR */
#ifdef __BUS_MCEERR_AR
#define BUS_MCEERR_AR __BUS_MCEERR_AR /* Hardware memory error: action required. */
#endif /* __BUS_MCEERR_AR */
#ifdef __BUS_MCEERR_AO
#define BUS_MCEERR_AO __BUS_MCEERR_AO /* Hardware memory error: action optional. */
#endif /* __BUS_MCEERR_AO */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/
#endif /* __BUS_... */
#endif /* __USE_XOPEN_EXTENDED || __USE_XOPEN2K8 */



#ifdef __USE_XOPEN_EXTENDED
/* `si_code' values for SIGTRAP signal. */
#if defined(__TRAP_BRKPT) || defined(__TRAP_TRACE)
/*[[[enum]]]*/
#ifdef __CC__
enum {
#ifdef __TRAP_BRKPT
	TRAP_BRKPT = __TRAP_BRKPT, /* Process breakpoint. */
#endif /* __TRAP_BRKPT */
#ifdef __TRAP_TRACE
	TRAP_TRACE = __TRAP_TRACE  /* Process trace trap. */
#endif /* __TRAP_TRACE */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#ifdef __TRAP_BRKPT
#define TRAP_BRKPT TRAP_BRKPT /* Process breakpoint. */
#endif /* __TRAP_BRKPT */
#ifdef __TRAP_TRACE
#define TRAP_TRACE TRAP_TRACE /* Process trace trap. */
#endif /* __TRAP_TRACE */
#else /* __COMPILER_PREFERR_ENUMS */
#ifdef __TRAP_BRKPT
#define TRAP_BRKPT __TRAP_BRKPT /* Process breakpoint. */
#endif /* __TRAP_BRKPT */
#ifdef __TRAP_TRACE
#define TRAP_TRACE __TRAP_TRACE /* Process trace trap. */
#endif /* __TRAP_TRACE */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/
#endif /* __TRAP_... */
#endif /* __USE_XOPEN_EXTENDED */



#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_XOPEN2K8)
/* `si_code' values for SIGCHLD signal. */
#if (defined(__CLD_EXITED) || defined(__CLD_KILLED) ||  \
     defined(__CLD_DUMPED) || defined(__CLD_TRAPPED) || \
     defined(__CLD_STOPPED) || defined(__CLD_CONTINUED))
/*[[[enum]]]*/
#ifdef __CC__
enum {
#ifdef __CLD_EXITED
	CLD_EXITED    = __CLD_EXITED,    /* Child has exited. */
#endif /* __CLD_EXITED */
#ifdef __CLD_KILLED
	CLD_KILLED    = __CLD_KILLED,    /* Child was killed. */
#endif /* __CLD_KILLED */
#ifdef __CLD_DUMPED
	CLD_DUMPED    = __CLD_DUMPED,    /* Child terminated abnormally. */
#endif /* __CLD_DUMPED */
#ifdef __CLD_TRAPPED
	CLD_TRAPPED   = __CLD_TRAPPED,   /* Traced child has trapped. */
#endif /* __CLD_TRAPPED */
#ifdef __CLD_STOPPED
	CLD_STOPPED   = __CLD_STOPPED,   /* Child has stopped. */
#endif /* __CLD_STOPPED */
#ifdef __CLD_CONTINUED
	CLD_CONTINUED = __CLD_CONTINUED  /* Stopped child has continued. */
#endif /* __CLD_CONTINUED */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#ifdef __CLD_EXITED
#define CLD_EXITED    CLD_EXITED    /* Child has exited. */
#endif /* __CLD_EXITED */
#ifdef __CLD_KILLED
#define CLD_KILLED    CLD_KILLED    /* Child was killed. */
#endif /* __CLD_KILLED */
#ifdef __CLD_DUMPED
#define CLD_DUMPED    CLD_DUMPED    /* Child terminated abnormally. */
#endif /* __CLD_DUMPED */
#ifdef __CLD_TRAPPED
#define CLD_TRAPPED   CLD_TRAPPED   /* Traced child has trapped. */
#endif /* __CLD_TRAPPED */
#ifdef __CLD_STOPPED
#define CLD_STOPPED   CLD_STOPPED   /* Child has stopped. */
#endif /* __CLD_STOPPED */
#ifdef __CLD_CONTINUED
#define CLD_CONTINUED CLD_CONTINUED /* Stopped child has continued. */
#endif /* __CLD_CONTINUED */
#else /* __COMPILER_PREFERR_ENUMS */
#ifdef __CLD_EXITED
#define CLD_EXITED    __CLD_EXITED    /* Child has exited. */
#endif /* __CLD_EXITED */
#ifdef __CLD_KILLED
#define CLD_KILLED    __CLD_KILLED    /* Child was killed. */
#endif /* __CLD_KILLED */
#ifdef __CLD_DUMPED
#define CLD_DUMPED    __CLD_DUMPED    /* Child terminated abnormally. */
#endif /* __CLD_DUMPED */
#ifdef __CLD_TRAPPED
#define CLD_TRAPPED   __CLD_TRAPPED   /* Traced child has trapped. */
#endif /* __CLD_TRAPPED */
#ifdef __CLD_STOPPED
#define CLD_STOPPED   __CLD_STOPPED   /* Child has stopped. */
#endif /* __CLD_STOPPED */
#ifdef __CLD_CONTINUED
#define CLD_CONTINUED __CLD_CONTINUED /* Stopped child has continued. */
#endif /* __CLD_CONTINUED */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/
#endif /* __CLD_... */



/* `si_code' values for SIGPOLL signal. */
#if (defined(__POLL_IN) || defined(__POLL_OUT) || defined(__POLL_MSG) || \
     defined(__POLL_ERR) || defined(__POLL_PRI) || defined(__POLL_HUP))
/*[[[enum]]]*/
#ifdef __CC__
enum {
#ifdef __POLL_IN
	POLL_IN  = __POLL_IN,  /* Data input available. */
#endif /* __POLL_IN */
#ifdef __POLL_OUT
	POLL_OUT = __POLL_OUT, /* Output buffers available. */
#endif /* __POLL_OUT */
#ifdef __POLL_MSG
	POLL_MSG = __POLL_MSG, /* Input message available.   */
#endif /* __POLL_MSG */
#ifdef __POLL_ERR
	POLL_ERR = __POLL_ERR, /* I/O error. */
#endif /* __POLL_ERR */
#ifdef __POLL_PRI
	POLL_PRI = __POLL_PRI, /* High priority input available. */
#endif /* __POLL_PRI */
#ifdef __POLL_HUP
	POLL_HUP = __POLL_HUP  /* Device disconnected. */
#endif /* __POLL_HUP */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#ifdef __POLL_IN
#define POLL_IN  POLL_IN  /* Data input available. */
#endif /* __POLL_IN */
#ifdef __POLL_OUT
#define POLL_OUT POLL_OUT /* Output buffers available. */
#endif /* __POLL_OUT */
#ifdef __POLL_MSG
#define POLL_MSG POLL_MSG /* Input message available. */
#endif /* __POLL_MSG */
#ifdef __POLL_ERR
#define POLL_ERR POLL_ERR /* I/O error. */
#endif /* __POLL_ERR */
#ifdef __POLL_PRI
#define POLL_PRI POLL_PRI /* High priority input available. */
#endif /* __POLL_PRI */
#ifdef __POLL_HUP
#define POLL_HUP POLL_HUP /* Device disconnected. */
#endif /* __POLL_HUP */
#else /* __COMPILER_PREFERR_ENUMS */
#ifdef __POLL_IN
#define POLL_IN  __POLL_IN  /* Data input available. */
#endif /* __POLL_IN */
#ifdef __POLL_OUT
#define POLL_OUT __POLL_OUT /* Output buffers available. */
#endif /* __POLL_OUT */
#ifdef __POLL_MSG
#define POLL_MSG __POLL_MSG /* Input message available. */
#endif /* __POLL_MSG */
#ifdef __POLL_ERR
#define POLL_ERR __POLL_ERR /* I/O error. */
#endif /* __POLL_ERR */
#ifdef __POLL_PRI
#define POLL_PRI __POLL_PRI /* High priority input available. */
#endif /* __POLL_PRI */
#ifdef __POLL_HUP
#define POLL_HUP __POLL_HUP /* Device disconnected. */
#endif /* __POLL_HUP */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/
#endif /* __POLL_... */
#endif /* __USE_XOPEN_EXTENDED || __USE_XOPEN2K8 */
#endif /* __USE_POSIX199309 || __USE_XOPEN_EXTENDED || __USE_KOS */


#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_XOPEN2K8)

/* Possible values for `struct sigaltstack::ss_flags.'. */
#if defined(__SS_ONSTACK) || defined(__SS_DISABLE) || defined(__SS_AUTODISARM)
/*[[[enum]]]*/
#ifdef __CC__
enum {
#ifdef __SS_ONSTACK
	SS_ONSTACK    = __SS_ONSTACK,   /* out.flag: Currently executing from the alternate signal stack. */
#endif /* __SS_ONSTACK */
#ifdef __SS_DISABLE
	SS_DISABLE    = __SS_DISABLE,   /* in.flag: Disable the alternate signal stack. (all other flags are ignored when set)
	                                 * out.flag: The alternate signal stack is currently disabled. */
#endif /* __SS_DISABLE */
#ifdef __SS_AUTODISARM
	SS_AUTODISARM = __SS_AUTODISARM /* flag:     Disable  the  alternate signal  stack upon  signal handler
	                                 *           entry by  saving its  old configuration  and disabling  it
	                                 *           by  means  of  `SS_DISABLE',  before  restoring  its prior
	                                 *           setting  once the signal  handler returns, thus preventing
	                                 *           other signal handlers from recursing onto an in-use stack. */
#endif /* __SS_AUTODISARM */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#ifdef __SS_ONSTACK
#define SS_ONSTACK    SS_ONSTACK    /* out.flag: Currently executing from the alternate signal stack. */
#endif /* __SS_ONSTACK */
#ifdef __SS_DISABLE
#define SS_DISABLE    SS_DISABLE    /* in.flag: Disable the alternate signal stack. (all other flags are ignored when set)
                                     * out.flag: The alternate signal stack is currently disabled. */
#endif /* __SS_DISABLE */
#ifdef __SS_AUTODISARM
#define SS_AUTODISARM SS_AUTODISARM /* flag:     Disable  the  alternate signal  stack upon  signal handler
                                     *           entry by  saving its  old configuration  and disabling  it
                                     *           by  means  of  `SS_DISABLE',  before  restoring  its prior
                                     *           setting  once the signal  handler returns, thus preventing
                                     *           other signal handlers from recursing onto an in-use stack. */
#endif /* __SS_AUTODISARM */
#else /* __COMPILER_PREFERR_ENUMS */
#ifdef __SS_ONSTACK
#define SS_ONSTACK    __SS_ONSTACK    /* out.flag: Currently executing from the alternate signal stack. */
#endif /* __SS_ONSTACK */
#ifdef __SS_DISABLE
#define SS_DISABLE    __SS_DISABLE    /* in.flag: Disable the alternate signal stack. (all other flags are ignored when set)
                                       * out.flag: The alternate signal stack is currently disabled. */
#endif /* __SS_DISABLE */
#ifdef __SS_AUTODISARM
#define SS_AUTODISARM __SS_AUTODISARM /* flag:     Disable  the  alternate signal  stack upon  signal handler
                                       *           entry by  saving its  old configuration  and disabling  it
                                       *           by  means  of  `SS_DISABLE',  before  restoring  its prior
                                       *           setting  once the signal  handler returns, thus preventing
                                       *           other signal handlers from recursing onto an in-use stack. */
#endif /* __SS_AUTODISARM */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/
#endif /* __SS_ONSTACK || __SS_DISABLE */

#ifdef __MINSIGSTKSZ
#define MINSIGSTKSZ __MINSIGSTKSZ /* Minimum stack size for a signal handler. */
#endif /* __MINSIGSTKSZ */

#ifdef __SIGSTKSZ
#define SIGSTKSZ __SIGSTKSZ /* System default stack size. */
#endif /* __SIGSTKSZ */

#endif /* __USE_XOPEN_EXTENDED || __USE_XOPEN2K8 */



#ifdef __CC__

#if (defined(__USE_POSIX199309) || defined(__USE_XOPEN_EXTENDED) || defined(__USE_KOS))
#ifndef __sigevent_t_defined
#define __sigevent_t_defined
typedef struct sigevent sigevent_t;
#endif /* !__sigevent_t_defined */
#ifndef __siginfo_t_defined
#define __siginfo_t_defined
typedef struct __siginfo_struct siginfo_t;
#endif /* !__siginfo_t_defined */
#ifndef __sigval_t_defined
#define __sigval_t_defined
typedef union sigval sigval_t;
#endif /* !__sigval_t_defined */
#endif /* __USE_POSIX199309 || __USE_XOPEN_EXTENDED || __USE_KOS */

#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_XOPEN2K8)
#ifndef __stack_t_defined
#define __stack_t_defined
typedef struct sigaltstack stack_t;
#endif /* !__stack_t_defined */
#endif /* __USE_XOPEN_EXTENDED || __USE_XOPEN2K8 */

#ifndef __std_sig_atomic_t_defined
#define __std_sig_atomic_t_defined
__NAMESPACE_STD_BEGIN
/* An integral type  that can be  modified atomically, without  the
 * possibility of a signal arriving in the middle of the operation. */
typedef __SIG_ATOMIC_TYPE__ sig_atomic_t;
__NAMESPACE_STD_END
#endif /* !__std_sig_atomic_t_defined */
#ifndef __CXX_SYSTEM_HEADER
#ifndef __sig_atomic_t_defined
#define __sig_atomic_t_defined
__NAMESPACE_STD_USING(sig_atomic_t)
#endif /* !__sig_atomic_t_defined */
#endif /* !__CXX_SYSTEM_HEADER */

#ifdef __USE_POSIX
#ifndef __sigset_t_defined
#define __sigset_t_defined
typedef struct __sigset_struct sigset_t;
#endif /* !__sigset_t_defined */
#endif /* __USE_POSIX */

#if defined(__USE_XOPEN) || defined(__USE_XOPEN2K)
#ifndef __pid_t_defined
#define __pid_t_defined
typedef __pid_t pid_t;
#endif /* !__pid_t_defined */
#ifndef __uid_t_defined
#define __uid_t_defined
typedef __uid_t uid_t;
#endif /* !__uid_t_defined */
#endif /* __USE_XOPEN || __USE_XOPEN2K */

#ifndef ____sighandler_t_defined
#define ____sighandler_t_defined
typedef void (__LIBKCALL *__sighandler_t)(int __signo);
#endif /* !____sighandler_t_defined */

#ifdef __USE_GNU
#ifndef __sighandler_t_defined
#define __sighandler_t_defined
typedef __sighandler_t sighandler_t;
#endif /* !__sighandler_t_defined */
#endif /* __USE_GNU */

#ifdef __USE_MISC
#ifndef NSIG
#define NSIG _NSIG
#endif /* !NSIG */
#ifndef __sig_t_defined
#define __sig_t_defined
typedef __sighandler_t sig_t;
#endif /* !__sig_t_defined */
#endif /* __USE_MISC */

#ifndef __PRIVATE_SIGSET_VALIDATE_SIGNO
#if defined(__KERNEL__) && __SIZEOF_INT__ >= __SIZEOF_POINTER__
#define __PRIVATE_SIGSET_ISMEMBER_EXT /* nothing */
#else /* __KERNEL__ && __SIZEOF_INT__ >= __SIZEOF_POINTER__ */
#define __PRIVATE_SIGSET_ISMEMBER_EXT != 0
#endif /* !__KERNEL__ && __SIZEOF_INT__ < __SIZEOF_POINTER__ */
#if defined(__KERNEL__) && defined(__KOS__)
#define __PRIVATE_SIGSET_VALIDATE_SIGNO(signo) /* nothing */
#elif defined(__NSIG) && defined(__EINVAL)
#define __PRIVATE_SIGSET_VALIDATE_SIGNO(signo)     \
	if __unlikely(signo <= 0 || signo >= __NSIG) { \
		return __libc_seterrno(__EINVAL);          \
	}
#elif defined(__NSIG)
#define __PRIVATE_SIGSET_VALIDATE_SIGNO(signo)     \
	if __unlikely(signo <= 0 || signo >= __NSIG) { \
		return __libc_seterrno(1);                 \
	}
#elif defined(__EINVAL)
#define __PRIVATE_SIGSET_VALIDATE_SIGNO(signo) \
	if __unlikely(signo <= 0) {                \
		return __libc_seterrno(__EINVAL);      \
	}
#else /* ... */
#define __PRIVATE_SIGSET_VALIDATE_SIGNO(signo) \
	if __unlikely(signo <= 0) {                \
		return __libc_seterrno(1);             \
	}
#endif /* !... */
#endif /* !__PRIVATE_SIGSET_VALIDATE_SIGNO */
#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_XOPEN2K8)
#ifndef __std_size_t_defined
#define __std_size_t_defined
__NAMESPACE_STD_BEGIN
typedef __SIZE_TYPE__ size_t;
__NAMESPACE_STD_END
#endif /* !__std_size_t_defined */

#ifndef __CXX_SYSTEM_HEADER
#ifndef __size_t_defined
#define __size_t_defined
__NAMESPACE_STD_USING(size_t)
#endif /* !__size_t_defined */
#endif /* !__CXX_SYSTEM_HEADER */
#endif /* __USE_XOPEN_EXTENDED || __USE_XOPEN2K8 */

__NAMESPACE_STD_BEGIN
#ifdef __CRT_HAVE_raise
/* >> raise(3)
 * Raise a signal within the current thread.
 * In  a *-threaded process this is same as:
 *   *=multi:  `pthread_kill(pthread_self(), signo)'
 *   *=single: `kill(getpid(), signo)'
 * @return: 0:  Success
 * @return: -1: [errno=EINVAL] The given `signo' is invalid */
__CDECLARE(,int,__NOTHROW_NCX,raise,(__signo_t __signo),(__signo))
#elif ((defined(__CRT_HAVE_pthread_kill) || defined(__CRT_HAVE_thr_kill)) && (defined(__CRT_HAVE_pthread_self) || defined(__CRT_HAVE_thrd_current) || defined(__CRT_HAVE_thr_self))) || ((defined(__CRT_HAVE_kill) || defined(__CRT_HAVE___kill) || defined(__CRT_HAVE___libc_kill)) && (defined(__CRT_HAVE_getpid) || defined(__CRT_HAVE__getpid) || defined(__CRT_HAVE___getpid) || defined(__CRT_HAVE___libc_getpid)))
__NAMESPACE_STD_END
#include <libc/local/signal/raise.h>
__NAMESPACE_STD_BEGIN
/* >> raise(3)
 * Raise a signal within the current thread.
 * In  a *-threaded process this is same as:
 *   *=multi:  `pthread_kill(pthread_self(), signo)'
 *   *=single: `kill(getpid(), signo)'
 * @return: 0:  Success
 * @return: -1: [errno=EINVAL] The given `signo' is invalid */
__NAMESPACE_LOCAL_USING_OR_IMPL(raise, __FORCELOCAL __ATTR_ARTIFICIAL int __NOTHROW_NCX(__LIBCCALL raise)(__signo_t __signo) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(raise))(__signo); })
#endif /* ... */
#if defined(__CRT_HAVE_signal) && defined(__USE_MISC)
/* >> signal(2/3)
 * Non-portable  signal  handler  establishment  function  that  behaves
 * either like `sysv_signal()', `bsd_signal()', or has its own behavior.
 * On KOS, this function behaves identical to `bsd_signal()'
 * @return: * :      The previous signal handler function.
 * @return: SIG_ERR: Error (s.a. `errno') */
__CDECLARE(,__sighandler_t,__NOTHROW_NCX,signal,(__signo_t __signo, __sighandler_t __handler),(__signo,__handler))
#elif defined(__CRT_HAVE__signal) && defined(__USE_MISC)
/* >> signal(2/3)
 * Non-portable  signal  handler  establishment  function  that  behaves
 * either like `sysv_signal()', `bsd_signal()', or has its own behavior.
 * On KOS, this function behaves identical to `bsd_signal()'
 * @return: * :      The previous signal handler function.
 * @return: SIG_ERR: Error (s.a. `errno') */
__CREDIRECT(,__sighandler_t,__NOTHROW_NCX,signal,(__signo_t __signo, __sighandler_t __handler),_signal,(__signo,__handler))
#elif defined(__CRT_HAVE_sysv_signal)
/* >> signal(2/3)
 * Non-portable  signal  handler  establishment  function  that  behaves
 * either like `sysv_signal()', `bsd_signal()', or has its own behavior.
 * On KOS, this function behaves identical to `bsd_signal()'
 * @return: * :      The previous signal handler function.
 * @return: SIG_ERR: Error (s.a. `errno') */
__CREDIRECT(,__sighandler_t,__NOTHROW_NCX,signal,(__signo_t __signo, __sighandler_t __handler),sysv_signal,(__signo,__handler))
#endif /* ... */
__NAMESPACE_STD_END
#ifndef __CXX_SYSTEM_HEADER
#if defined(__CRT_HAVE_raise) || ((defined(__CRT_HAVE_pthread_kill) || defined(__CRT_HAVE_thr_kill)) && (defined(__CRT_HAVE_pthread_self) || defined(__CRT_HAVE_thrd_current) || defined(__CRT_HAVE_thr_self))) || ((defined(__CRT_HAVE_kill) || defined(__CRT_HAVE___kill) || defined(__CRT_HAVE___libc_kill)) && (defined(__CRT_HAVE_getpid) || defined(__CRT_HAVE__getpid) || defined(__CRT_HAVE___getpid) || defined(__CRT_HAVE___libc_getpid)))
__NAMESPACE_STD_USING(raise)
#endif /* __CRT_HAVE_raise || ((__CRT_HAVE_pthread_kill || __CRT_HAVE_thr_kill) && (__CRT_HAVE_pthread_self || __CRT_HAVE_thrd_current || __CRT_HAVE_thr_self)) || ((__CRT_HAVE_kill || __CRT_HAVE___kill || __CRT_HAVE___libc_kill) && (__CRT_HAVE_getpid || __CRT_HAVE__getpid || __CRT_HAVE___getpid || __CRT_HAVE___libc_getpid)) */
#endif /* !__CXX_SYSTEM_HEADER */
#ifdef __CRT_HAVE_sysv_signal
/* >> sysv_signal(3)
 * Wrapper for `sigaction(2)' to establish a signal handler as:
 *     >> struct sigaction act, oact
 *     >> act.sa_handler = handler;
 *     >> act.sa_flags   = (SA_RESETHAND | SA_NODEFER) & ~SA_RESTART;
 *     >> sigemptyset(&act.sa_mask);
 *     >> if (sigaction(signo, &act, &oact) != 0)
 *     >>     oact.sa_handler = SIG_ERR;
 *     >> return oact.sa_handler;
 * @return: * :      The previous signal handler function.
 * @return: SIG_ERR: Error (s.a. `errno') */
__CREDIRECT(,__sighandler_t,__NOTHROW_NCX,__sysv_signal,(__signo_t __signo, __sighandler_t __handler),sysv_signal,(__signo,__handler))
#elif defined(__CRT_HAVE___sysv_signal)
/* >> sysv_signal(3)
 * Wrapper for `sigaction(2)' to establish a signal handler as:
 *     >> struct sigaction act, oact
 *     >> act.sa_handler = handler;
 *     >> act.sa_flags   = (SA_RESETHAND | SA_NODEFER) & ~SA_RESTART;
 *     >> sigemptyset(&act.sa_mask);
 *     >> if (sigaction(signo, &act, &oact) != 0)
 *     >>     oact.sa_handler = SIG_ERR;
 *     >> return oact.sa_handler;
 * @return: * :      The previous signal handler function.
 * @return: SIG_ERR: Error (s.a. `errno') */
__CDECLARE(,__sighandler_t,__NOTHROW_NCX,__sysv_signal,(__signo_t __signo, __sighandler_t __handler),(__signo,__handler))
#elif defined(__SA_RESETHAND) && defined(__SA_NODEFER) && defined(__SIG_ERR) && (defined(__CRT_HAVE_sigaction) || defined(__CRT_HAVE___sigaction))
#include <libc/local/signal/sysv_signal.h>
/* >> sysv_signal(3)
 * Wrapper for `sigaction(2)' to establish a signal handler as:
 *     >> struct sigaction act, oact
 *     >> act.sa_handler = handler;
 *     >> act.sa_flags   = (SA_RESETHAND | SA_NODEFER) & ~SA_RESTART;
 *     >> sigemptyset(&act.sa_mask);
 *     >> if (sigaction(signo, &act, &oact) != 0)
 *     >>     oact.sa_handler = SIG_ERR;
 *     >> return oact.sa_handler;
 * @return: * :      The previous signal handler function.
 * @return: SIG_ERR: Error (s.a. `errno') */
__FORCELOCAL __ATTR_ARTIFICIAL __sighandler_t __NOTHROW_NCX(__LIBCCALL __sysv_signal)(__signo_t __signo, __sighandler_t __handler) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sysv_signal))(__signo, __handler); }
#endif /* ... */
#ifdef __USE_GNU
#ifdef __CRT_HAVE_sysv_signal
/* >> sysv_signal(3)
 * Wrapper for `sigaction(2)' to establish a signal handler as:
 *     >> struct sigaction act, oact
 *     >> act.sa_handler = handler;
 *     >> act.sa_flags   = (SA_RESETHAND | SA_NODEFER) & ~SA_RESTART;
 *     >> sigemptyset(&act.sa_mask);
 *     >> if (sigaction(signo, &act, &oact) != 0)
 *     >>     oact.sa_handler = SIG_ERR;
 *     >> return oact.sa_handler;
 * @return: * :      The previous signal handler function.
 * @return: SIG_ERR: Error (s.a. `errno') */
__CDECLARE(,__sighandler_t,__NOTHROW_NCX,sysv_signal,(__signo_t __signo, __sighandler_t __handler),(__signo,__handler))
#elif defined(__CRT_HAVE___sysv_signal)
/* >> sysv_signal(3)
 * Wrapper for `sigaction(2)' to establish a signal handler as:
 *     >> struct sigaction act, oact
 *     >> act.sa_handler = handler;
 *     >> act.sa_flags   = (SA_RESETHAND | SA_NODEFER) & ~SA_RESTART;
 *     >> sigemptyset(&act.sa_mask);
 *     >> if (sigaction(signo, &act, &oact) != 0)
 *     >>     oact.sa_handler = SIG_ERR;
 *     >> return oact.sa_handler;
 * @return: * :      The previous signal handler function.
 * @return: SIG_ERR: Error (s.a. `errno') */
__CREDIRECT(,__sighandler_t,__NOTHROW_NCX,sysv_signal,(__signo_t __signo, __sighandler_t __handler),__sysv_signal,(__signo,__handler))
#elif defined(__SA_RESETHAND) && defined(__SA_NODEFER) && defined(__SIG_ERR) && (defined(__CRT_HAVE_sigaction) || defined(__CRT_HAVE___sigaction))
#include <libc/local/signal/sysv_signal.h>
/* >> sysv_signal(3)
 * Wrapper for `sigaction(2)' to establish a signal handler as:
 *     >> struct sigaction act, oact
 *     >> act.sa_handler = handler;
 *     >> act.sa_flags   = (SA_RESETHAND | SA_NODEFER) & ~SA_RESTART;
 *     >> sigemptyset(&act.sa_mask);
 *     >> if (sigaction(signo, &act, &oact) != 0)
 *     >>     oact.sa_handler = SIG_ERR;
 *     >> return oact.sa_handler;
 * @return: * :      The previous signal handler function.
 * @return: SIG_ERR: Error (s.a. `errno') */
__NAMESPACE_LOCAL_USING_OR_IMPL(sysv_signal, __FORCELOCAL __ATTR_ARTIFICIAL __sighandler_t __NOTHROW_NCX(__LIBCCALL sysv_signal)(__signo_t __signo, __sighandler_t __handler) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sysv_signal))(__signo, __handler); })
#endif /* ... */
#endif /* __USE_GNU */
#ifndef __CXX_SYSTEM_HEADER
#if (defined(__CRT_HAVE_signal) && defined(__USE_MISC)) || (defined(__CRT_HAVE__signal) && defined(__USE_MISC)) || defined(__CRT_HAVE_sysv_signal)
__NAMESPACE_STD_USING(signal)
#endif /* (__CRT_HAVE_signal && __USE_MISC) || (__CRT_HAVE__signal && __USE_MISC) || __CRT_HAVE_sysv_signal */
#endif /* !__CXX_SYSTEM_HEADER */
#ifdef __USE_MISC
#define sigmask(signo) __sigset_mask(signo)
#ifdef __CRT_HAVE_ssignal
/* >> ssignal(3)
 * Establish a software-signal-handler. This handler may or may not
 * be distinct from normal signal handlers, and should be triggered
 * by `gsignal(3)', rather than `raise(3)'.
 * On KOS, this function behaves identical to `bsd_signal()'
 * @return: * :      The previous signal handler function.
 * @return: SIG_ERR: Error (s.a. `errno') */
__CDECLARE(,__sighandler_t,__NOTHROW_NCX,ssignal,(__signo_t __signo, __sighandler_t __handler),(__signo,__handler))
#elif defined(__CRT_HAVE_bsd_signal) || defined(__CRT_HAVE___bsd_signal)
#include <libc/local/signal/ssignal.h>
/* >> ssignal(3)
 * Establish a software-signal-handler. This handler may or may not
 * be distinct from normal signal handlers, and should be triggered
 * by `gsignal(3)', rather than `raise(3)'.
 * On KOS, this function behaves identical to `bsd_signal()'
 * @return: * :      The previous signal handler function.
 * @return: SIG_ERR: Error (s.a. `errno') */
__NAMESPACE_LOCAL_USING_OR_IMPL(ssignal, __FORCELOCAL __ATTR_ARTIFICIAL __sighandler_t __NOTHROW_NCX(__LIBCCALL ssignal)(__signo_t __signo, __sighandler_t __handler) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ssignal))(__signo, __handler); })
#endif /* ... */
#ifdef __CRT_HAVE_gsignal
/* >> gsignal(3)
 * Raise a software-signal  by invoking  a previously  established
 * software-signal-handler,  as   set  by   `ssignal(signo, ...)'.
 * This method by which a software signal is raised may or may not
 * be distinct from normal signal handlers.
 * On KOS, this function behaves identical to `raise()'
 * @return: 0:  Success
 * @return: -1: [errno=EINVAL] The given `signo' is invalid */
__CDECLARE(,int,__NOTHROW_NCX,gsignal,(__signo_t __signo),(__signo))
#elif defined(__CRT_HAVE_raise) || ((defined(__CRT_HAVE_pthread_kill) || defined(__CRT_HAVE_thr_kill)) && (defined(__CRT_HAVE_pthread_self) || defined(__CRT_HAVE_thrd_current) || defined(__CRT_HAVE_thr_self))) || ((defined(__CRT_HAVE_kill) || defined(__CRT_HAVE___kill) || defined(__CRT_HAVE___libc_kill)) && (defined(__CRT_HAVE_getpid) || defined(__CRT_HAVE__getpid) || defined(__CRT_HAVE___getpid) || defined(__CRT_HAVE___libc_getpid)))
#include <libc/local/signal/gsignal.h>
/* >> gsignal(3)
 * Raise a software-signal  by invoking  a previously  established
 * software-signal-handler,  as   set  by   `ssignal(signo, ...)'.
 * This method by which a software signal is raised may or may not
 * be distinct from normal signal handlers.
 * On KOS, this function behaves identical to `raise()'
 * @return: 0:  Success
 * @return: -1: [errno=EINVAL] The given `signo' is invalid */
__NAMESPACE_LOCAL_USING_OR_IMPL(gsignal, __FORCELOCAL __ATTR_ARTIFICIAL int __NOTHROW_NCX(__LIBCCALL gsignal)(__signo_t __signo) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(gsignal))(__signo); })
#endif /* ... */
#ifdef __CRT_HAVE_sigblock
/* >> sigblock(3)
 * Deprecated  method  of  SIG_BLOCK-ing  a  given  set  of
 * signals. Modern code should use `sigprocmask()' instead.
 * @return: * : First 32 bits of previous signal mask (or however many fit in `int') */
__CDECLARE(__ATTR_DEPRECATED("Using `sigprocmask(SIG_BLOCK)\' instead"),int,__NOTHROW_NCX,sigblock,(int __mask),(__mask))
#elif defined(__CRT_HAVE___sigblock)
/* >> sigblock(3)
 * Deprecated  method  of  SIG_BLOCK-ing  a  given  set  of
 * signals. Modern code should use `sigprocmask()' instead.
 * @return: * : First 32 bits of previous signal mask (or however many fit in `int') */
__CREDIRECT(__ATTR_DEPRECATED("Using `sigprocmask(SIG_BLOCK)\' instead"),int,__NOTHROW_NCX,sigblock,(int __mask),__sigblock,(__mask))
#elif defined(__SIG_BLOCK) && (defined(__CRT_HAVE_sigprocmask) || defined(__CRT_HAVE___sigprocmask) || defined(__CRT_HAVE___libc_sigprocmask) || defined(__CRT_HAVE_pthread_sigmask) || defined(__CRT_HAVE_thr_sigsetmask))
#include <libc/local/signal/sigblock.h>
/* >> sigblock(3)
 * Deprecated  method  of  SIG_BLOCK-ing  a  given  set  of
 * signals. Modern code should use `sigprocmask()' instead.
 * @return: * : First 32 bits of previous signal mask (or however many fit in `int') */
__NAMESPACE_LOCAL_USING_OR_IMPL(sigblock, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_DEPRECATED("Using `sigprocmask(SIG_BLOCK)\' instead") int __NOTHROW_NCX(__LIBCCALL sigblock)(int __mask) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sigblock))(__mask); })
#endif /* ... */
#ifdef __CRT_HAVE_sigsetmask
/* >> sigsetmask(3)
 * Deprecated method of SIG_SETMASK-ing a given set of signals.
 * Modern code should  use `sigprocmask(SIG_SETMASK)'  instead.
 * @return: * : First 32 bits of previous signal mask (or however many fit in `int') */
__CDECLARE(__ATTR_DEPRECATED("Using `sigprocmask()\' instead"),int,__NOTHROW_NCX,sigsetmask,(int __mask),(__mask))
#elif defined(__CRT_HAVE___sigsetmask)
/* >> sigsetmask(3)
 * Deprecated method of SIG_SETMASK-ing a given set of signals.
 * Modern code should  use `sigprocmask(SIG_SETMASK)'  instead.
 * @return: * : First 32 bits of previous signal mask (or however many fit in `int') */
__CREDIRECT(__ATTR_DEPRECATED("Using `sigprocmask()\' instead"),int,__NOTHROW_NCX,sigsetmask,(int __mask),__sigsetmask,(__mask))
#elif defined(__SIG_SETMASK) && (defined(__CRT_HAVE_sigprocmask) || defined(__CRT_HAVE___sigprocmask) || defined(__CRT_HAVE___libc_sigprocmask) || defined(__CRT_HAVE_pthread_sigmask) || defined(__CRT_HAVE_thr_sigsetmask))
#include <libc/local/signal/sigsetmask.h>
/* >> sigsetmask(3)
 * Deprecated method of SIG_SETMASK-ing a given set of signals.
 * Modern code should  use `sigprocmask(SIG_SETMASK)'  instead.
 * @return: * : First 32 bits of previous signal mask (or however many fit in `int') */
__NAMESPACE_LOCAL_USING_OR_IMPL(sigsetmask, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_DEPRECATED("Using `sigprocmask()\' instead") int __NOTHROW_NCX(__LIBCCALL sigsetmask)(int __mask) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sigsetmask))(__mask); })
#endif /* ... */
#ifdef __CRT_HAVE_siggetmask
/* >> sigsetmask(3)
 * Deprecated method of  retrieving the masking-state  of
 * the lowest-numberred `sizeof(int) * NBBY - 1' signals.
 * @return: * : First 32 bits of signal mask (or however many fit in `int') */
__CDECLARE(__ATTR_DEPRECATED("Using `sigprocmask()\' instead"),int,__NOTHROW_NCX,siggetmask,(void),())
#elif defined(__CRT_HAVE___siggetmask)
/* >> sigsetmask(3)
 * Deprecated method of  retrieving the masking-state  of
 * the lowest-numberred `sizeof(int) * NBBY - 1' signals.
 * @return: * : First 32 bits of signal mask (or however many fit in `int') */
__CREDIRECT(__ATTR_DEPRECATED("Using `sigprocmask()\' instead"),int,__NOTHROW_NCX,siggetmask,(void),__siggetmask,())
#elif defined(__CRT_HAVE_sigprocmask) || defined(__CRT_HAVE___sigprocmask) || defined(__CRT_HAVE___libc_sigprocmask) || defined(__CRT_HAVE_pthread_sigmask) || defined(__CRT_HAVE_thr_sigsetmask)
#include <libc/local/signal/siggetmask.h>
/* >> sigsetmask(3)
 * Deprecated method of  retrieving the masking-state  of
 * the lowest-numberred `sizeof(int) * NBBY - 1' signals.
 * @return: * : First 32 bits of signal mask (or however many fit in `int') */
__NAMESPACE_LOCAL_USING_OR_IMPL(siggetmask, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_DEPRECATED("Using `sigprocmask()\' instead") int __NOTHROW_NCX(__LIBCCALL siggetmask)(void) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(siggetmask))(); })
#endif /* ... */

#ifndef sys_siglist
#ifdef _sys_siglist
#define sys_siglist _sys_siglist
#else /* _sys_siglist */
#if !defined(____p_sys_siglist_defined) && defined(__CRT_HAVE___p_sys_siglist)
#define ____p_sys_siglist_defined
__CDECLARE(__ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED,char const *const *,__NOTHROW,__p_sys_siglist,(void),())
#endif /* !____p_sys_siglist_defined && __CRT_HAVE___p_sys_siglist */
#ifdef ____p_sys_siglist_defined
#define sys_siglist  __p_sys_siglist()
#define _sys_siglist __p_sys_siglist()
#endif /* ____p_sys_siglist_defined */
#ifndef _sys_siglist
#ifdef __CRT_HAVE_sys_siglist
#ifdef _NSIG
__LIBC char const *const sys_siglist[_NSIG];
#else /* _NSIG */
__LIBC char const *const sys_siglist[];
#endif /* !_NSIG */
#define sys_siglist  sys_siglist
#define _sys_siglist sys_siglist
#elif defined(__CRT_HAVE__sys_siglist)
#ifdef _NSIG
__LIBC char const *const _sys_siglist[_NSIG];
#else /* _NSIG */
__LIBC char const *const _sys_siglist[];
#endif /* !_NSIG */
#define sys_siglist  _sys_siglist
#define _sys_siglist _sys_siglist
#endif /* sys_siglist... */
#endif /* !_sys_siglist */
#endif /* !_sys_siglist */
#endif /* !sys_siglist */

#if !defined(_sys_siglist) && defined(sys_siglist)
#define _sys_siglist sys_siglist
#endif /* !_sys_siglist && sys_siglist */
struct sigcontext;
/* Don't  call directly. Used internally to resume
 * execution when returning from a signal handler. */
__CDECLARE_VOID_OPT(__ATTR_NORETURN,__NOTHROW_NCX,sigreturn,(struct sigcontext const *__scp),(__scp))
#endif /* __USE_MISC */

#ifdef __USE_BSD
#ifndef sys_signame
#ifdef sys_sigabbrev
#define sys_signame sys_sigabbrev
#elif defined(__CRT_HAVE_sys_signame)
#ifdef _NSIG
__LIBC char const *const sys_signame[_NSIG];
#else /* _NSIG */
__LIBC char const *const sys_signame[];
#endif /* !_NSIG */
#define sys_signame sys_signame
#elif defined(__CRT_HAVE_sys_sigabbrev)
#ifdef __NO_ASMNAME
#ifdef _NSIG
__LIBC char const *const sys_signame[_NSIG] __CASMNAME("sys_sigabbrev");
#else /* _NSIG */
__LIBC char const *const sys_signame[] __CASMNAME("sys_sigabbrev");
#endif /* !_NSIG */
#define sys_signame sys_signame
#else /* __NO_ASMNAME */
#ifdef _NSIG
__LIBC char const *const sys_sigabbrev[_NSIG];
#else /* _NSIG */
__LIBC char const *const sys_sigabbrev[];
#endif /* !_NSIG */
#define sys_sigabbrev sys_sigabbrev
#define sys_signame   sys_sigabbrev
#endif /* !__NO_ASMNAME */
#endif /* ... */
#endif /* !sys_signame */

#ifndef sys_nsig
#ifdef __CRT_HAVE_sys_nsig
__LIBC int const sys_nsig;
#define sys_nsig sys_nsig
#endif /* __CRT_HAVE_sys_nsig */
#endif /* !sys_nsig */
#endif /* __USE_BSD */

#ifdef __USE_XOPEN
#ifdef __CRT_HAVE_bsd_signal
/* >> bsd_signal(3)
 * Wrapper for `sigaction(2)' to establish a signal handler as:
 *     >> struct sigaction act, oact
 *     >> act.sa_handler = handler;
 *     >> sigemptyset(&act.sa_mask);
 *     >> sigaddset(&act.sa_mask, signo);
 *     >> act.sa_flags = sigismember(&[SIGNALS_WITH_SIGINTERRUPT], signo) ? 0 : SA_RESTART;
 *     >> SET_SIGRESTORE(act);
 *     >> if (sigaction(signo, &act, &oact) != 0)
 *     >>     oact.sa_handler = SIG_ERR;
 *     >> return oact.sa_handler;
 *     Where `SIGNALS_WITH_SIGINTERRUPT' is the set of signals for  which
 *     `siginterrupt(3)' had last been called with a non-zero `interrupt'
 *     argument
 * @return: * :      The previous signal handler function.
 * @return: SIG_ERR: Error (s.a. `errno') */
__CDECLARE(,__sighandler_t,__NOTHROW_NCX,bsd_signal,(__signo_t __signo, __sighandler_t __handler),(__signo,__handler))
#elif defined(__CRT_HAVE___bsd_signal)
/* >> bsd_signal(3)
 * Wrapper for `sigaction(2)' to establish a signal handler as:
 *     >> struct sigaction act, oact
 *     >> act.sa_handler = handler;
 *     >> sigemptyset(&act.sa_mask);
 *     >> sigaddset(&act.sa_mask, signo);
 *     >> act.sa_flags = sigismember(&[SIGNALS_WITH_SIGINTERRUPT], signo) ? 0 : SA_RESTART;
 *     >> SET_SIGRESTORE(act);
 *     >> if (sigaction(signo, &act, &oact) != 0)
 *     >>     oact.sa_handler = SIG_ERR;
 *     >> return oact.sa_handler;
 *     Where `SIGNALS_WITH_SIGINTERRUPT' is the set of signals for  which
 *     `siginterrupt(3)' had last been called with a non-zero `interrupt'
 *     argument
 * @return: * :      The previous signal handler function.
 * @return: SIG_ERR: Error (s.a. `errno') */
__CREDIRECT(,__sighandler_t,__NOTHROW_NCX,bsd_signal,(__signo_t __signo, __sighandler_t __handler),__bsd_signal,(__signo,__handler))
#endif /* ... */
#ifdef __CRT_HAVE___xpg_sigpause
/* >> sigpause(3)
 * Atomically save and set the caller's signal mask to consist solely
 * of the signal signal `signo', then wait for that signal to  arrive
 * before restoring the old signal mask.
 * @return: -1: [errno=EINTR] The signal handler for `signo' was executed. */
__CREDIRECT(,int,__NOTHROW_NCX,sigpause,(__signo_t __signo),__xpg_sigpause,(__signo))
#elif defined(__CRT_HAVE_sigsuspend) || defined(__CRT_HAVE___sigsuspend)
#include <libc/local/signal/sigpause.h>
/* >> sigpause(3)
 * Atomically save and set the caller's signal mask to consist solely
 * of the signal signal `signo', then wait for that signal to  arrive
 * before restoring the old signal mask.
 * @return: -1: [errno=EINTR] The signal handler for `signo' was executed. */
__NAMESPACE_LOCAL_USING_OR_IMPL(sigpause, __FORCELOCAL __ATTR_ARTIFICIAL int __NOTHROW_NCX(__LIBCCALL sigpause)(__signo_t __signo) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sigpause))(__signo); })
#endif /* ... */
#endif /* __USE_XOPEN */

#ifdef __USE_POSIX
#ifdef __CRT_HAVE_kill
/* >> kill(2)
 * Raise a signal `signo' within the process(es) specified by `pid':
 *   - pid > 0:   Deliver `signo' to a process who's PID matches `pid'.
 *   - pid == 0:  Deliver `signo' to every process within the caller's process group.
 *   - pid == -1: Deliver  `signo'  to  every process  the  caller has  permission  to send
 *                signals to, with the exception of a process with pid=1 (i.e. `/bin/init')
 *   - pid < -1:  Deliver `signo' to every process within the process group `-pid'
 * @param: signo: The signal number to deliver. When set to `0', no signal is  delivered,
 *                and this function can be used to test if the caller would be allowed to
 *                send signals to the process(es) specified by `pid'
 * @return: 0:    Success
 * @return: -1:   [errno=EINVAL] The given `signo' is invalid
 * @return: -1:   [errno=EPERM]  The caller does not have permission to send signals to `pid'
 * @return: -1:   [errno=ESRCH]  No process is identified by `pid' */
__CDECLARE(,int,__NOTHROW_NCX,kill,(__pid_t __pid, __signo_t __signo),(__pid,__signo))
#elif defined(__CRT_HAVE___kill)
/* >> kill(2)
 * Raise a signal `signo' within the process(es) specified by `pid':
 *   - pid > 0:   Deliver `signo' to a process who's PID matches `pid'.
 *   - pid == 0:  Deliver `signo' to every process within the caller's process group.
 *   - pid == -1: Deliver  `signo'  to  every process  the  caller has  permission  to send
 *                signals to, with the exception of a process with pid=1 (i.e. `/bin/init')
 *   - pid < -1:  Deliver `signo' to every process within the process group `-pid'
 * @param: signo: The signal number to deliver. When set to `0', no signal is  delivered,
 *                and this function can be used to test if the caller would be allowed to
 *                send signals to the process(es) specified by `pid'
 * @return: 0:    Success
 * @return: -1:   [errno=EINVAL] The given `signo' is invalid
 * @return: -1:   [errno=EPERM]  The caller does not have permission to send signals to `pid'
 * @return: -1:   [errno=ESRCH]  No process is identified by `pid' */
__CREDIRECT(,int,__NOTHROW_NCX,kill,(__pid_t __pid, __signo_t __signo),__kill,(__pid,__signo))
#elif defined(__CRT_HAVE___libc_kill)
/* >> kill(2)
 * Raise a signal `signo' within the process(es) specified by `pid':
 *   - pid > 0:   Deliver `signo' to a process who's PID matches `pid'.
 *   - pid == 0:  Deliver `signo' to every process within the caller's process group.
 *   - pid == -1: Deliver  `signo'  to  every process  the  caller has  permission  to send
 *                signals to, with the exception of a process with pid=1 (i.e. `/bin/init')
 *   - pid < -1:  Deliver `signo' to every process within the process group `-pid'
 * @param: signo: The signal number to deliver. When set to `0', no signal is  delivered,
 *                and this function can be used to test if the caller would be allowed to
 *                send signals to the process(es) specified by `pid'
 * @return: 0:    Success
 * @return: -1:   [errno=EINVAL] The given `signo' is invalid
 * @return: -1:   [errno=EPERM]  The caller does not have permission to send signals to `pid'
 * @return: -1:   [errno=ESRCH]  No process is identified by `pid' */
__CREDIRECT(,int,__NOTHROW_NCX,kill,(__pid_t __pid, __signo_t __signo),__libc_kill,(__pid,__signo))
#endif /* ... */
#ifdef __CRT_HAVE_sigemptyset
/* >> sigemptyset(3)
 * Clear the given signal set of all contained signals
 * @return: 0: Always returns `0' */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,sigemptyset,(struct __sigset_struct *__set),(__set))
#else /* __CRT_HAVE_sigemptyset */
#include <libc/local/signal/sigemptyset.h>
/* >> sigemptyset(3)
 * Clear the given signal set of all contained signals
 * @return: 0: Always returns `0' */
__NAMESPACE_LOCAL_USING_OR_IMPL(sigemptyset, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL sigemptyset)(struct __sigset_struct *__set) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sigemptyset))(__set); })
#endif /* !__CRT_HAVE_sigemptyset */
#ifdef __CRT_HAVE_sigfillset
/* >> sigfillset(3)
 * Add all possible signals (possibly even including undefined signals,
 * though these would be ignored by the kernel) to the given signal set
 * @return: 0: Always returns `0' */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,sigfillset,(struct __sigset_struct *__set),(__set))
#else /* __CRT_HAVE_sigfillset */
#include <libc/local/signal/sigfillset.h>
/* >> sigfillset(3)
 * Add all possible signals (possibly even including undefined signals,
 * though these would be ignored by the kernel) to the given signal set
 * @return: 0: Always returns `0' */
__NAMESPACE_LOCAL_USING_OR_IMPL(sigfillset, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL sigfillset)(struct __sigset_struct *__set) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sigfillset))(__set); })
#endif /* !__CRT_HAVE_sigfillset */
#ifdef __CRT_HAVE_sigaddset
/* >> sigaddset(3)
 * Add only the given `signo' to the given signal set
 * @return: 0:  Success (Always returned by the kernel-version)
 * @return: -1: [errno=EINVAL] invalid `signo'.
 *              Not returned by the kernel-version of this function! */
__CEIDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,sigaddset,(struct __sigset_struct *__set, __signo_t __signo),{ __ULONGPTR_TYPE__ __mask, __word; __PRIVATE_SIGSET_VALIDATE_SIGNO(__signo) __mask = __sigset_mask(__signo); __word = __sigset_word(__signo); __set->__val[__word] |= __mask; return 0; })
#elif defined(__CRT_HAVE___sigaddset)
/* >> sigaddset(3)
 * Add only the given `signo' to the given signal set
 * @return: 0:  Success (Always returned by the kernel-version)
 * @return: -1: [errno=EINVAL] invalid `signo'.
 *              Not returned by the kernel-version of this function! */
__CEIREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,sigaddset,(struct __sigset_struct *__set, __signo_t __signo),__sigaddset,{ __ULONGPTR_TYPE__ __mask, __word; __PRIVATE_SIGSET_VALIDATE_SIGNO(__signo) __mask = __sigset_mask(__signo); __word = __sigset_word(__signo); __set->__val[__word] |= __mask; return 0; })
#else /* ... */
/* >> sigaddset(3)
 * Add only the given `signo' to the given signal set
 * @return: 0:  Success (Always returned by the kernel-version)
 * @return: -1: [errno=EINVAL] invalid `signo'.
 *              Not returned by the kernel-version of this function! */
__LOCAL __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL sigaddset)(struct __sigset_struct *__set, __signo_t __signo) { __ULONGPTR_TYPE__ __mask, __word; __PRIVATE_SIGSET_VALIDATE_SIGNO(__signo) __mask = __sigset_mask(__signo); __word = __sigset_word(__signo); __set->__val[__word] |= __mask; return 0; }
#endif /* !... */
#ifdef __CRT_HAVE_sigdelset
/* >> sigdelset(3)
 * Remove only the given `signo' from the given signal set
 * @return: 0:  Success (Always returned by the kernel-version)
 * @return: -1: [errno=EINVAL] invalid `signo'.
 *              Not returned by the kernel-version of this function! */
__CEIDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,sigdelset,(struct __sigset_struct *__set, __signo_t __signo),{ __ULONGPTR_TYPE__ __mask, __word; __PRIVATE_SIGSET_VALIDATE_SIGNO(__signo) __mask = __sigset_mask(__signo); __word = __sigset_word(__signo); __set->__val[__word] &= ~__mask; return 0; })
#elif defined(__CRT_HAVE___sigdelset)
/* >> sigdelset(3)
 * Remove only the given `signo' from the given signal set
 * @return: 0:  Success (Always returned by the kernel-version)
 * @return: -1: [errno=EINVAL] invalid `signo'.
 *              Not returned by the kernel-version of this function! */
__CEIREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,sigdelset,(struct __sigset_struct *__set, __signo_t __signo),__sigdelset,{ __ULONGPTR_TYPE__ __mask, __word; __PRIVATE_SIGSET_VALIDATE_SIGNO(__signo) __mask = __sigset_mask(__signo); __word = __sigset_word(__signo); __set->__val[__word] &= ~__mask; return 0; })
#else /* ... */
/* >> sigdelset(3)
 * Remove only the given `signo' from the given signal set
 * @return: 0:  Success (Always returned by the kernel-version)
 * @return: -1: [errno=EINVAL] invalid `signo'.
 *              Not returned by the kernel-version of this function! */
__LOCAL __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL sigdelset)(struct __sigset_struct *__set, __signo_t __signo) { __ULONGPTR_TYPE__ __mask, __word; __PRIVATE_SIGSET_VALIDATE_SIGNO(__signo) __mask = __sigset_mask(__signo); __word = __sigset_word(__signo); __set->__val[__word] &= ~__mask; return 0; }
#endif /* !... */
#ifdef __CRT_HAVE_sigismember
/* >> sigismember(3)
 * Check if a given `signo' is apart of the a given signal set
 * @return: >1: The given `signo' is apart of `set' (may be returned by the kernel-version of this function)
 * @return:  1: The given `signo' is apart of `set'
 * @return:  0: The given `signo' isn't apart of `set'
 * @return: -1: [errno=EINVAL] invalid `signo'.
 *              Not returned by the kernel-version of this function! */
__CEIDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,sigismember,(struct __sigset_struct const *__set, __signo_t __signo),{ __ULONGPTR_TYPE__ __mask, __word; __PRIVATE_SIGSET_VALIDATE_SIGNO(__signo) __mask = __sigset_mask(__signo); __word = __sigset_word(__signo); return (__set->__val[__word] & __mask) __PRIVATE_SIGSET_ISMEMBER_EXT; })
#elif defined(__CRT_HAVE___sigismember)
/* >> sigismember(3)
 * Check if a given `signo' is apart of the a given signal set
 * @return: >1: The given `signo' is apart of `set' (may be returned by the kernel-version of this function)
 * @return:  1: The given `signo' is apart of `set'
 * @return:  0: The given `signo' isn't apart of `set'
 * @return: -1: [errno=EINVAL] invalid `signo'.
 *              Not returned by the kernel-version of this function! */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,sigismember,(struct __sigset_struct const *__set, __signo_t __signo),__sigismember,{ __ULONGPTR_TYPE__ __mask, __word; __PRIVATE_SIGSET_VALIDATE_SIGNO(__signo) __mask = __sigset_mask(__signo); __word = __sigset_word(__signo); return (__set->__val[__word] & __mask) __PRIVATE_SIGSET_ISMEMBER_EXT; })
#else /* ... */
/* >> sigismember(3)
 * Check if a given `signo' is apart of the a given signal set
 * @return: >1: The given `signo' is apart of `set' (may be returned by the kernel-version of this function)
 * @return:  1: The given `signo' is apart of `set'
 * @return:  0: The given `signo' isn't apart of `set'
 * @return: -1: [errno=EINVAL] invalid `signo'.
 *              Not returned by the kernel-version of this function! */
__LOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL sigismember)(struct __sigset_struct const *__set, __signo_t __signo) { __ULONGPTR_TYPE__ __mask, __word; __PRIVATE_SIGSET_VALIDATE_SIGNO(__signo) __mask = __sigset_mask(__signo); __word = __sigset_word(__signo); return (__set->__val[__word] & __mask) __PRIVATE_SIGSET_ISMEMBER_EXT; }
#endif /* !... */
#ifdef __CRT_HAVE_sigprocmask
/* Change  the signal mask for the calling thread. Note that portable
 * programs that also make use of multithreading must instead use the
 * pthread-specific  `pthread_sigmask()'  function instead,  as POSIX
 * states that  this function  behaves undefined  in such  scenarios.
 * However, on KOS, `pthread_sigmask()' is  simply an alias for  this
 * function,  and  `sigprocmask()'   always  operates   thread-local.
 * Note also  that on  KOS 2  additional functions  `getsigmaskptr()'
 * and `setsigmaskptr()'  exist, which  can be  used to  get/set  the
 * address of the signal mask used by the kernel.
 * @param how: One of `SIG_BLOCK', `SIG_UNBLOCK' or `SIG_SETMASK'
 * @return: 0:  Success
 * @return: -1: [errno=EINVAL] Invalid `how' */
__CDECLARE(,int,__NOTHROW_NCX,sigprocmask,(__STDC_INT_AS_UINT_T __how, sigset_t const *__set, sigset_t *__oset),(__how,__set,__oset))
#elif defined(__CRT_HAVE___sigprocmask)
/* Change  the signal mask for the calling thread. Note that portable
 * programs that also make use of multithreading must instead use the
 * pthread-specific  `pthread_sigmask()'  function instead,  as POSIX
 * states that  this function  behaves undefined  in such  scenarios.
 * However, on KOS, `pthread_sigmask()' is  simply an alias for  this
 * function,  and  `sigprocmask()'   always  operates   thread-local.
 * Note also  that on  KOS 2  additional functions  `getsigmaskptr()'
 * and `setsigmaskptr()'  exist, which  can be  used to  get/set  the
 * address of the signal mask used by the kernel.
 * @param how: One of `SIG_BLOCK', `SIG_UNBLOCK' or `SIG_SETMASK'
 * @return: 0:  Success
 * @return: -1: [errno=EINVAL] Invalid `how' */
__CREDIRECT(,int,__NOTHROW_NCX,sigprocmask,(__STDC_INT_AS_UINT_T __how, sigset_t const *__set, sigset_t *__oset),__sigprocmask,(__how,__set,__oset))
#elif defined(__CRT_HAVE___libc_sigprocmask)
/* Change  the signal mask for the calling thread. Note that portable
 * programs that also make use of multithreading must instead use the
 * pthread-specific  `pthread_sigmask()'  function instead,  as POSIX
 * states that  this function  behaves undefined  in such  scenarios.
 * However, on KOS, `pthread_sigmask()' is  simply an alias for  this
 * function,  and  `sigprocmask()'   always  operates   thread-local.
 * Note also  that on  KOS 2  additional functions  `getsigmaskptr()'
 * and `setsigmaskptr()'  exist, which  can be  used to  get/set  the
 * address of the signal mask used by the kernel.
 * @param how: One of `SIG_BLOCK', `SIG_UNBLOCK' or `SIG_SETMASK'
 * @return: 0:  Success
 * @return: -1: [errno=EINVAL] Invalid `how' */
__CREDIRECT(,int,__NOTHROW_NCX,sigprocmask,(__STDC_INT_AS_UINT_T __how, sigset_t const *__set, sigset_t *__oset),__libc_sigprocmask,(__how,__set,__oset))
#elif defined(__CRT_HAVE_pthread_sigmask)
/* Change  the signal mask for the calling thread. Note that portable
 * programs that also make use of multithreading must instead use the
 * pthread-specific  `pthread_sigmask()'  function instead,  as POSIX
 * states that  this function  behaves undefined  in such  scenarios.
 * However, on KOS, `pthread_sigmask()' is  simply an alias for  this
 * function,  and  `sigprocmask()'   always  operates   thread-local.
 * Note also  that on  KOS 2  additional functions  `getsigmaskptr()'
 * and `setsigmaskptr()'  exist, which  can be  used to  get/set  the
 * address of the signal mask used by the kernel.
 * @param how: One of `SIG_BLOCK', `SIG_UNBLOCK' or `SIG_SETMASK'
 * @return: 0:  Success
 * @return: -1: [errno=EINVAL] Invalid `how' */
__CREDIRECT(,int,__NOTHROW_NCX,sigprocmask,(__STDC_INT_AS_UINT_T __how, sigset_t const *__set, sigset_t *__oset),pthread_sigmask,(__how,__set,__oset))
#elif defined(__CRT_HAVE_thr_sigsetmask)
/* Change  the signal mask for the calling thread. Note that portable
 * programs that also make use of multithreading must instead use the
 * pthread-specific  `pthread_sigmask()'  function instead,  as POSIX
 * states that  this function  behaves undefined  in such  scenarios.
 * However, on KOS, `pthread_sigmask()' is  simply an alias for  this
 * function,  and  `sigprocmask()'   always  operates   thread-local.
 * Note also  that on  KOS 2  additional functions  `getsigmaskptr()'
 * and `setsigmaskptr()'  exist, which  can be  used to  get/set  the
 * address of the signal mask used by the kernel.
 * @param how: One of `SIG_BLOCK', `SIG_UNBLOCK' or `SIG_SETMASK'
 * @return: 0:  Success
 * @return: -1: [errno=EINVAL] Invalid `how' */
__CREDIRECT(,int,__NOTHROW_NCX,sigprocmask,(__STDC_INT_AS_UINT_T __how, sigset_t const *__set, sigset_t *__oset),thr_sigsetmask,(__how,__set,__oset))
#endif /* ... */
#ifdef __USE_KOS

#ifdef __NSIG
/* >> sigvalid(3)
 * Verify that `signo' is a valid signal number. */
#define sigvalid(signo) ((signo) > 0 && (signo) < __NSIG)
#endif /* __NSIG */

/* >> getsigmaskptr(3)
 * Return   the   current  signal   mask  pointer.
 * See the documentation of `setsigmaskptr(3)' for
 * what this function is all about.
 * @return: * : A pointer to the calling thread's current signal mask */
__CDECLARE_OPT(__ATTR_RETNONNULL __ATTR_WUNUSED,sigset_t *,__NOTHROW_NCX,getsigmaskptr,(void),())
/* >> setsigmaskptr(3)
 * Set  the  current  signal  mask  pointer  to `sigmaskptr'
 * This  is  a kos-specific  function  that can  be  used to
 * speed up/replace  calls  to  `sigprocmask()'.  But  using
 * this function safely requires knowledge of its underlying
 * semantics. If you're unsure on those, you should  instead
 * just use the portable `sigprocmask()' and forget you ever
 * read this comment :)
 * Example usage:
 * >> static sigset_t const fullset = SIGSET_INIT_FULL;
 * >> sigset_t *oldset = setsigmaskptr((sigset_t *)&fullset);
 * >> // Code in here executes with all maskable signals masked
 * >> // Note however that code in here also mustn't call sigprocmask()
 * >> setsigmaskptr(oldset);
 * Equivalent code using sigprocmask (which has way more overhead):
 * >> static sigset_t const fullset = SIGSET_INIT_FULL;
 * >> sigset_t oldset;
 * >> sigprocmask(SIG_SETMASK, &fullset, &oldset);
 * >> // Code in here executes with all maskable signals masked
 * >> sigprocmask(SIG_SETMASK, &oldset, NULL);
 * @param: sigmaskptr: Address of the signal mask to use from now on.
 * @return: * : Address of the previously used signal mask. */
__CDECLARE_OPT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),sigset_t *,__NOTHROW_NCX,setsigmaskptr,(sigset_t *__sigmaskptr),(__sigmaskptr))
#ifdef __CRT_HAVE_setsigmaskfullptr
/* >> setsigmaskfullptr(3)
 * Same as  `setsigmaskptr()',  but  set a  statically  allocated,  fully
 * filled signal  mask  as  the calling  thread's  current  signal  mask.
 * This essentially means that this  function can be used to  temporarily
 * disable the reception of all  signals within the calling thread,  thus
 * allowing the thread to run  without being interrupted (by another  but
 * SIGKILL and SIGSTOP, which can't be masked), until the returned signal
 * mask is restored.
 * >> sigset_t *os;
 * >> os = setsigmaskfullptr();
 * >> ...
 * >> setsigmaskptr(os); */
__CDECLARE(__ATTR_RETNONNULL,sigset_t *,__NOTHROW_NCX,setsigmaskfullptr,(void),())
#elif defined(__CRT_HAVE_setsigmaskptr)
#include <libc/local/signal/setsigmaskfullptr.h>
/* >> setsigmaskfullptr(3)
 * Same as  `setsigmaskptr()',  but  set a  statically  allocated,  fully
 * filled signal  mask  as  the calling  thread's  current  signal  mask.
 * This essentially means that this  function can be used to  temporarily
 * disable the reception of all  signals within the calling thread,  thus
 * allowing the thread to run  without being interrupted (by another  but
 * SIGKILL and SIGSTOP, which can't be masked), until the returned signal
 * mask is restored.
 * >> sigset_t *os;
 * >> os = setsigmaskfullptr();
 * >> ...
 * >> setsigmaskptr(os); */
__NAMESPACE_LOCAL_USING_OR_IMPL(setsigmaskfullptr, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL sigset_t *__NOTHROW_NCX(__LIBCCALL setsigmaskfullptr)(void) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(setsigmaskfullptr))(); })
#endif /* ... */
struct userprocmask;
#if !defined(__getuserprocmask_defined) && defined(__CRT_HAVE_getuserprocmask)
#define __getuserprocmask_defined
/* >> getuserprocmask(3)
 * Return a pointer to the calling thread's userprocmask
 * This function is only  declared if supported by  libc */
__CDECLARE(__ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED,struct userprocmask *,__NOTHROW,getuserprocmask,(void),())
#endif /* !__getuserprocmask_defined && __CRT_HAVE_getuserprocmask */
#if !defined(__chkuserprocmask_defined) && defined(__CRT_HAVE_chkuserprocmask)
#define __chkuserprocmask_defined
/* >> chkuserprocmask(3)
 * Following the calling thread's userprocmask becoming less
 * restrictive, check for pending signals and handle them if
 * necessary
 * This function is only declared if supported by libc */
__CDECLARE_VOID(,__NOTHROW,chkuserprocmask,(void),())
#endif /* !__chkuserprocmask_defined && __CRT_HAVE_chkuserprocmask */
#endif /* __USE_KOS */
#ifdef __CRT_HAVE_sigsuspend
/* >> sigsuspend(2)
 * Atomically save and  set the caller's  signal mask to  `set', then wait  for
 * one of the unmasked (iow: `!sigismember')-signals to arrive before restoring
 * the old signal mask.
 * @param: set: The set of signals on which to wait
 * @return: -1: [errno=EINTR] The signal handler for `signo' was executed. */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,sigsuspend,(sigset_t const *__set),(__set))
#elif defined(__CRT_HAVE___sigsuspend)
/* >> sigsuspend(2)
 * Atomically save and  set the caller's  signal mask to  `set', then wait  for
 * one of the unmasked (iow: `!sigismember')-signals to arrive before restoring
 * the old signal mask.
 * @param: set: The set of signals on which to wait
 * @return: -1: [errno=EINTR] The signal handler for `signo' was executed. */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,sigsuspend,(sigset_t const *__set),__sigsuspend,(__set))
#endif /* ... */
#ifdef __CRT_HAVE_sigaction
/* >> sigaction(2)
 * Get/Set the  action that  shall  be performed  when  a
 * signal `signo' must be handled by the calling process.
 * This function will modify the caller's kernel-space signal handler  descriptor,
 * who's shared/unshared behavior between threads is controlled by `CLONE_SIGHAND'
 * @return: 0:  Success
 * @return: -1: [errno=EINVAL] The given `signo' is invalid */
__CDECLARE(,int,__NOTHROW_NCX,sigaction,(__signo_t __signo, struct sigaction const *__act, struct sigaction *__oact),(__signo,__act,__oact))
#elif defined(__CRT_HAVE___sigaction)
/* >> sigaction(2)
 * Get/Set the  action that  shall  be performed  when  a
 * signal `signo' must be handled by the calling process.
 * This function will modify the caller's kernel-space signal handler  descriptor,
 * who's shared/unshared behavior between threads is controlled by `CLONE_SIGHAND'
 * @return: 0:  Success
 * @return: -1: [errno=EINVAL] The given `signo' is invalid */
__CREDIRECT(,int,__NOTHROW_NCX,sigaction,(__signo_t __signo, struct sigaction const *__act, struct sigaction *__oact),__sigaction,(__signo,__act,__oact))
#endif /* ... */
#ifdef __CRT_HAVE_sigpending
/* >> sigpending(2)
 * Retrieve the set of signals that are pending
 * in  either  the calling  thread  and process
 * @return: 0: Success */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,sigpending,(sigset_t *__restrict __set),(__set))
#elif defined(__CRT_HAVE___sigpending)
/* >> sigpending(2)
 * Retrieve the set of signals that are pending
 * in  either  the calling  thread  and process
 * @return: 0: Success */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,sigpending,(sigset_t *__restrict __set),__sigpending,(__set))
#elif defined(__CRT_HAVE___libc_sigpending)
/* >> sigpending(2)
 * Retrieve the set of signals that are pending
 * in  either  the calling  thread  and process
 * @return: 0: Success */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,sigpending,(sigset_t *__restrict __set),__libc_sigpending,(__set))
#endif /* ... */
/* >> sigwait(3)
 * Same as `sigsuspend(2)', but write-back the actual signal that was raised to `*signo'
 * @return: -1: [errno=EINTR] The signal handler for `signo' was executed. */
__CDECLARE_OPT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,sigwait,(sigset_t const *__restrict __set, __signo_t *__restrict __signo),(__set,__signo))
#ifdef __USE_GNU
#ifdef __CRT_HAVE_sigisemptyset
/* >> sigisemptyset(3)
 * Check if the given signal set is empty
 * @return: != 0: Yes, it is empty
 * @return: == 0: No, at least 1 signal is contained */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,sigisemptyset,(struct __sigset_struct const *__restrict __set),(__set))
#else /* __CRT_HAVE_sigisemptyset */
#include <libc/local/signal/sigisemptyset.h>
/* >> sigisemptyset(3)
 * Check if the given signal set is empty
 * @return: != 0: Yes, it is empty
 * @return: == 0: No, at least 1 signal is contained */
__NAMESPACE_LOCAL_USING_OR_IMPL(sigisemptyset, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL sigisemptyset)(struct __sigset_struct const *__restrict __set) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sigisemptyset))(__set); })
#endif /* !__CRT_HAVE_sigisemptyset */
#ifdef __CRT_HAVE_sigandset
/* >> sigandset(3)
 * Set-up every signal `S' from `set' as the result of `set[S] = left[S] & right[S]'
 * @return: 0: Always returns `0' */
__CDECLARE(__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_NCX,sigandset,(struct __sigset_struct *__set, struct __sigset_struct const *__left, struct __sigset_struct const *__right),(__set,__left,__right))
#else /* __CRT_HAVE_sigandset */
#include <libc/local/signal/sigandset.h>
/* >> sigandset(3)
 * Set-up every signal `S' from `set' as the result of `set[S] = left[S] & right[S]'
 * @return: 0: Always returns `0' */
__NAMESPACE_LOCAL_USING_OR_IMPL(sigandset, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2, 3)) int __NOTHROW_NCX(__LIBCCALL sigandset)(struct __sigset_struct *__set, struct __sigset_struct const *__left, struct __sigset_struct const *__right) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sigandset))(__set, __left, __right); })
#endif /* !__CRT_HAVE_sigandset */
#ifdef __CRT_HAVE_sigorset
/* >> sigorset(3)
 * Set-up every signal `S' from `set' as the result of `set[S] = left[S] | right[S]'
 * @return: 0: Always returns `0' */
__CDECLARE(__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_NCX,sigorset,(struct __sigset_struct *__set, struct __sigset_struct const *__left, struct __sigset_struct const *__right),(__set,__left,__right))
#else /* __CRT_HAVE_sigorset */
#include <libc/local/signal/sigorset.h>
/* >> sigorset(3)
 * Set-up every signal `S' from `set' as the result of `set[S] = left[S] | right[S]'
 * @return: 0: Always returns `0' */
__NAMESPACE_LOCAL_USING_OR_IMPL(sigorset, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2, 3)) int __NOTHROW_NCX(__LIBCCALL sigorset)(struct __sigset_struct *__set, struct __sigset_struct const *__left, struct __sigset_struct const *__right) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sigorset))(__set, __left, __right); })
#endif /* !__CRT_HAVE_sigorset */
#endif /* __USE_GNU */
#ifdef __USE_KOS
#ifdef __CRT_HAVE_signandset
/* >> signandset(3)
 * Set-up every signal `S' from `set' as the result of `set[S] = left[S] & ~right[S]'
 * @return: 0: Always returns `0' */
__CDECLARE(__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_NCX,signandset,(struct __sigset_struct *__set, struct __sigset_struct const *__left, struct __sigset_struct const *__right),(__set,__left,__right))
#else /* __CRT_HAVE_signandset */
#include <libc/local/signal/signandset.h>
/* >> signandset(3)
 * Set-up every signal `S' from `set' as the result of `set[S] = left[S] & ~right[S]'
 * @return: 0: Always returns `0' */
__NAMESPACE_LOCAL_USING_OR_IMPL(signandset, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2, 3)) int __NOTHROW_NCX(__LIBCCALL signandset)(struct __sigset_struct *__set, struct __sigset_struct const *__left, struct __sigset_struct const *__right) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(signandset))(__set, __left, __right); })
#endif /* !__CRT_HAVE_signandset */
#endif /* __USE_KOS */
#ifdef __USE_POSIX199309
/* >> sigwaitinfo(2)
 * Same as `sigsuspend(2)',  but write-back extended  information in the  signal,
 * as it would/has also been passed to a signal handler's second (info) argument.
 * @param: set:  The set of signals on which to wait
 * @param: info: Information about the signal on which to wait.
 * @return: -1: [errno=EINTR] The signal handler for `signo' was executed. */
__CDECLARE_OPT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,sigwaitinfo,(struct __sigset_struct const *__restrict __set, siginfo_t *__restrict __info),(__set,__info))
#if defined(__CRT_HAVE_sigtimedwait) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> sigtimedwait(2), sigtimedwait64(2)
 * Same as `sigwaitinfo(2)', but stop waiting after a total of `rel_timeout' has passed
 * @param: set:         The set of signals on which to wait
 * @param: info:        Information about the signal on which to wait.
 * @param: rel_timeout: The timeout specifying for how long to wait (or `NULL' to wait indefinitely)
 * @return: -1: [errno=EINTR]  The signal handler for `signo' was executed.
 * @return: -1: [errno=EAGAIN] A total of `rel_timeout' has passed. */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,sigtimedwait,(struct __sigset_struct const *__restrict __set, siginfo_t *__restrict __info, struct timespec const *__rel_timeout),(__set,__info,__rel_timeout))
#elif defined(__CRT_HAVE_sigtimedwait64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> sigtimedwait(2), sigtimedwait64(2)
 * Same as `sigwaitinfo(2)', but stop waiting after a total of `rel_timeout' has passed
 * @param: set:         The set of signals on which to wait
 * @param: info:        Information about the signal on which to wait.
 * @param: rel_timeout: The timeout specifying for how long to wait (or `NULL' to wait indefinitely)
 * @return: -1: [errno=EINTR]  The signal handler for `signo' was executed.
 * @return: -1: [errno=EAGAIN] A total of `rel_timeout' has passed. */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,sigtimedwait,(struct __sigset_struct const *__restrict __set, siginfo_t *__restrict __info, struct timespec const *__rel_timeout),sigtimedwait64,(__set,__info,__rel_timeout))
#elif defined(__CRT_HAVE_sigtimedwait64) || defined(__CRT_HAVE_sigtimedwait)
#include <libc/local/signal/sigtimedwait.h>
/* >> sigtimedwait(2), sigtimedwait64(2)
 * Same as `sigwaitinfo(2)', but stop waiting after a total of `rel_timeout' has passed
 * @param: set:         The set of signals on which to wait
 * @param: info:        Information about the signal on which to wait.
 * @param: rel_timeout: The timeout specifying for how long to wait (or `NULL' to wait indefinitely)
 * @return: -1: [errno=EINTR]  The signal handler for `signo' was executed.
 * @return: -1: [errno=EAGAIN] A total of `rel_timeout' has passed. */
__NAMESPACE_LOCAL_USING_OR_IMPL(sigtimedwait, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL sigtimedwait)(struct __sigset_struct const *__restrict __set, siginfo_t *__restrict __info, struct timespec const *__rel_timeout) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sigtimedwait))(__set, __info, __rel_timeout); })
#endif /* ... */
/* >> sigqueue(2)
 * Similar to  `kill(2)',  but  `pid'  must  be positive  and  reference  a  process's  PID,
 * meaning that this function can only be used to send a signal to single, specific process.
 * @param: pid:   The PID of the process that shall receive the signal.
 * @param: signo: The signal number to deliver. When set to `0', no signal is  delivered,
 *                and this function can be used to test if the caller would be allowed to
 *                send signals to the process(es) specified by `pid'
 * @param: val:   An additional value to pass alongside the signal itself. This value can
 *                read as `info->si_value' from within a 3-arg signal handler established
 *                by `pid', or  may also be  returned by a  call to `sigwaitinfo(2)'  and
 *                friends made by `pid'.
 * @return: 0:    Success
 * @return: -1:   [errno=EINVAL] The given `signo' is invalid
 * @return: -1:   [errno=EPERM]  The caller does not have permission to send signals to `pid'
 * @return: -1:   [errno=ESRCH]  No process is identified by `pid' */
__CDECLARE_OPT(,int,__NOTHROW_NCX,sigqueue,(__pid_t __pid, __signo_t __signo, union sigval const __val),(__pid,__signo,__val))
#ifdef __USE_TIME64
#if defined(__CRT_HAVE_sigtimedwait) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> sigtimedwait(2), sigtimedwait64(2)
 * Same as `sigwaitinfo(2)', but stop waiting after a total of `rel_timeout' has passed
 * @param: set:         The set of signals on which to wait
 * @param: info:        Information about the signal on which to wait.
 * @param: rel_timeout: The timeout specifying for how long to wait (or `NULL' to wait indefinitely)
 * @return: -1: [errno=EINTR]  The signal handler for `signo' was executed.
 * @return: -1: [errno=EAGAIN] A total of `rel_timeout' has passed. */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,sigtimedwait64,(struct __sigset_struct const *__restrict __set, siginfo_t *__restrict __info, struct timespec64 const *__rel_timeout),sigtimedwait,(__set,__info,__rel_timeout))
#elif defined(__CRT_HAVE_sigtimedwait64)
/* >> sigtimedwait(2), sigtimedwait64(2)
 * Same as `sigwaitinfo(2)', but stop waiting after a total of `rel_timeout' has passed
 * @param: set:         The set of signals on which to wait
 * @param: info:        Information about the signal on which to wait.
 * @param: rel_timeout: The timeout specifying for how long to wait (or `NULL' to wait indefinitely)
 * @return: -1: [errno=EINTR]  The signal handler for `signo' was executed.
 * @return: -1: [errno=EAGAIN] A total of `rel_timeout' has passed. */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,sigtimedwait64,(struct __sigset_struct const *__restrict __set, siginfo_t *__restrict __info, struct timespec64 const *__rel_timeout),(__set,__info,__rel_timeout))
#elif defined(__CRT_HAVE_sigtimedwait)
#include <libc/local/signal/sigtimedwait64.h>
/* >> sigtimedwait(2), sigtimedwait64(2)
 * Same as `sigwaitinfo(2)', but stop waiting after a total of `rel_timeout' has passed
 * @param: set:         The set of signals on which to wait
 * @param: info:        Information about the signal on which to wait.
 * @param: rel_timeout: The timeout specifying for how long to wait (or `NULL' to wait indefinitely)
 * @return: -1: [errno=EINTR]  The signal handler for `signo' was executed.
 * @return: -1: [errno=EAGAIN] A total of `rel_timeout' has passed. */
__NAMESPACE_LOCAL_USING_OR_IMPL(sigtimedwait64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL sigtimedwait64)(struct __sigset_struct const *__restrict __set, siginfo_t *__restrict __info, struct timespec64 const *__rel_timeout) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sigtimedwait64))(__set, __info, __rel_timeout); })
#endif /* ... */
#endif /* __USE_TIME64 */
#endif /* __USE_POSIX199309 */
#endif /* __USE_POSIX */

#ifdef __USE_KOS
/* >> sigqueueinfo(2)
 * Similar to  `sigqueue(2)',  but  instead  of  only being  able  to  specify  a  custom
 * signal  value, everything  about signal meta-data  can be specified  by this function.
 * Note however  that  various privileges  are  required  to provide  custom  values  for
 * different values of `uinfo' that don't match what the equivalent call to `sigqueue(2)'
 * would have used.
 * @param: pid:   The PID of the process that shall receive the signal.
 * @param: signo: The signal number to deliver. When set to `0', no signal is  delivered,
 *                and this function can be used to test if the caller would be allowed to
 *                send signals to the process(es) specified by `pid'
 * @param: uinfo: Signal information to pass alongside the signal itself.
 * @return: 0:    Success
 * @return: -1:   [errno=EINVAL] The given `signo' is invalid
 * @return: -1:   [errno=EINVAL] The given `signo' doesn't match `uinfo->si_signo'
 * @return: -1:   [errno=EPERM]  The caller does not have permission to send signals to `pid'
 * @return: -1:   [errno=EPERM]  `info->si_code' is invalid, and `pid' is a different process
 * @return: -1:   [errno=ESRCH]  No process is identified by `pid' */
__CDECLARE_OPT(__ATTR_NONNULL((3)),int,__NOTHROW_NCX,sigqueueinfo,(__pid_t __pid, __signo_t __signo, siginfo_t const *__uinfo),(__pid,__signo,__uinfo))
/* >> tgsigqueueinfo(2)
 * Similar  to `sigqueueinfo(2)', rather than sending a signal to a process
 * as a whole, only send the signal to a single thread within that process.
 * @param: pid:   The PID of the process that shall receive the signal.
 * @param: signo: The signal number to deliver. When set to `0', no signal is  delivered,
 *                and this function can be used to test if the caller would be allowed to
 *                send signals to the process(es) specified by `pid'
 * @param: uinfo: Signal information to pass alongside the signal itself.
 * @return: 0:    Success
 * @return: -1:   [errno=EINVAL] The given `signo' is invalid
 * @return: -1:   [errno=EINVAL] The given `signo' doesn't match `uinfo->si_signo'
 * @return: -1:   [errno=EPERM]  The caller does not have permission to send signals to `pid'
 * @return: -1:   [errno=EPERM]  `info->si_code' is invalid, and `pid' is a different process
 * @return: -1:   [errno=ESRCH]  No process is identified by `pid' */
__CDECLARE_OPT(__ATTR_NONNULL((4)),int,__NOTHROW_NCX,tgsigqueueinfo,(__pid_t __pid, __pid_t __tid, __signo_t __signo, siginfo_t const *__uinfo),(__pid,__tid,__signo,__uinfo))
#endif /* __USE_KOS */

#if defined(__USE_MISC) || defined(__USE_XOPEN_EXTENDED)
#ifdef __CRT_HAVE_killpg
/* >> killpg(3)
 * Alias for `kill(-pgrp, signo)'
 * @param: signo: The signal number to deliver. When set to `0', no signal is  delivered,
 *                and this function can be used to test if the caller would be allowed to
 *                send signals to the process(es) specified by `pid'
 * @return: 0:    Success
 * @return: -1:   [errno=EINVAL] The given `signo' is invalid
 * @return: -1:   [errno=EPERM]  The caller does not have permission to send signals to `pgrp'
 * @return: -1:   [errno=ESRCH]  No process group is identified by `pgrp' */
__CDECLARE(,int,__NOTHROW_NCX,killpg,(__pid_t __pgrp, __signo_t __signo),(__pgrp,__signo))
#elif defined(__CRT_HAVE_kill) || defined(__CRT_HAVE___kill) || defined(__CRT_HAVE___libc_kill)
#include <libc/local/signal/killpg.h>
/* >> killpg(3)
 * Alias for `kill(-pgrp, signo)'
 * @param: signo: The signal number to deliver. When set to `0', no signal is  delivered,
 *                and this function can be used to test if the caller would be allowed to
 *                send signals to the process(es) specified by `pid'
 * @return: 0:    Success
 * @return: -1:   [errno=EINVAL] The given `signo' is invalid
 * @return: -1:   [errno=EPERM]  The caller does not have permission to send signals to `pgrp'
 * @return: -1:   [errno=ESRCH]  No process group is identified by `pgrp' */
__NAMESPACE_LOCAL_USING_OR_IMPL(killpg, __FORCELOCAL __ATTR_ARTIFICIAL int __NOTHROW_NCX(__LIBCCALL killpg)(__pid_t __pgrp, __signo_t __signo) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(killpg))(__pgrp, __signo); })
#endif /* ... */
#endif /* __USE_MISC || __USE_XOPEN_EXTENDED */

#ifdef __USE_XOPEN2K8
#ifndef __psignal_defined
#define __psignal_defined
#ifdef __CRT_HAVE_psignal
/* >> psignal(3)
 * Same as `fprintf(stderr, "%s: %s\n", s, sigabbrev_np(signo) ? "SIG"+. : strdupf("Unknown signal %d", signo))'
 * When `s' is `NULL' or an empty string, omit the leading "%s: " from the format. */
__CDECLARE_VOID(,__NOTHROW_NCX,psignal,(__signo_t __signo, char const *__s),(__signo,__s))
#else /* __CRT_HAVE_psignal */
#include <libc/template/stdstreams.h>
#if defined(__LOCAL_stderr) && (defined(__CRT_HAVE_fprintf) || defined(__CRT_HAVE__IO_fprintf) || defined(__CRT_HAVE_fprintf_s) || defined(__CRT_HAVE_fprintf_unlocked) || defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock))
#include <libc/local/signal/psignal.h>
/* >> psignal(3)
 * Same as `fprintf(stderr, "%s: %s\n", s, sigabbrev_np(signo) ? "SIG"+. : strdupf("Unknown signal %d", signo))'
 * When `s' is `NULL' or an empty string, omit the leading "%s: " from the format. */
__NAMESPACE_LOCAL_USING_OR_IMPL(psignal, __FORCELOCAL __ATTR_ARTIFICIAL void __NOTHROW_NCX(__LIBCCALL psignal)(__signo_t __signo, char const *__s) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(psignal))(__signo, __s); })
#else /* __LOCAL_stderr && (__CRT_HAVE_fprintf || __CRT_HAVE__IO_fprintf || __CRT_HAVE_fprintf_s || __CRT_HAVE_fprintf_unlocked || __CRT_HAVE_vfprintf || __CRT_HAVE_vfprintf_s || __CRT_HAVE__IO_vfprintf || __CRT_HAVE_vfprintf_unlocked || __CRT_HAVE_file_printer || __CRT_HAVE_file_printer_unlocked || __CRT_HAVE_putc || __CRT_HAVE_fputc || __CRT_HAVE__IO_putc || __CRT_HAVE_putc_unlocked || __CRT_HAVE_fputc_unlocked || __CRT_HAVE__putc_nolock || __CRT_HAVE__fputc_nolock || (__CRT_DOS && (__CRT_HAVE__flsbuf || __CRT_HAVE___swbuf)) || __CRT_HAVE_fwrite || __CRT_HAVE__IO_fwrite || __CRT_HAVE_fwrite_s || __CRT_HAVE_fwrite_unlocked || __CRT_HAVE__fwrite_nolock) */
#undef __psignal_defined
#endif /* !__LOCAL_stderr || (!__CRT_HAVE_fprintf && !__CRT_HAVE__IO_fprintf && !__CRT_HAVE_fprintf_s && !__CRT_HAVE_fprintf_unlocked && !__CRT_HAVE_vfprintf && !__CRT_HAVE_vfprintf_s && !__CRT_HAVE__IO_vfprintf && !__CRT_HAVE_vfprintf_unlocked && !__CRT_HAVE_file_printer && !__CRT_HAVE_file_printer_unlocked && !__CRT_HAVE_putc && !__CRT_HAVE_fputc && !__CRT_HAVE__IO_putc && !__CRT_HAVE_putc_unlocked && !__CRT_HAVE_fputc_unlocked && !__CRT_HAVE__putc_nolock && !__CRT_HAVE__fputc_nolock && (!__CRT_DOS || (!__CRT_HAVE__flsbuf && !__CRT_HAVE___swbuf)) && !__CRT_HAVE_fwrite && !__CRT_HAVE__IO_fwrite && !__CRT_HAVE_fwrite_s && !__CRT_HAVE_fwrite_unlocked && !__CRT_HAVE__fwrite_nolock) */
#endif /* !__CRT_HAVE_psignal */
#endif /* !__psignal_defined */
#ifndef __psiginfo_defined
#define __psiginfo_defined
#ifdef __CRT_HAVE_psiginfo
/* >> psiginfo(3)
 * Similar to `psignal(3)', but instead print extended signal information from `*pinfo' */
__CDECLARE_VOID(__ATTR_NONNULL((1)),__NOTHROW_NCX,psiginfo,(siginfo_t const *__pinfo, char const *__s),(__pinfo,__s))
#else /* __CRT_HAVE_psiginfo */
#include <libc/template/stdstreams.h>
#if defined(__LOCAL_stderr) && (defined(__CRT_HAVE_fprintf) || defined(__CRT_HAVE__IO_fprintf) || defined(__CRT_HAVE_fprintf_s) || defined(__CRT_HAVE_fprintf_unlocked) || defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock))
#include <libc/local/signal/psiginfo.h>
/* >> psiginfo(3)
 * Similar to `psignal(3)', but instead print extended signal information from `*pinfo' */
__NAMESPACE_LOCAL_USING_OR_IMPL(psiginfo, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) void __NOTHROW_NCX(__LIBCCALL psiginfo)(siginfo_t const *__pinfo, char const *__s) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(psiginfo))(__pinfo, __s); })
#else /* __LOCAL_stderr && (__CRT_HAVE_fprintf || __CRT_HAVE__IO_fprintf || __CRT_HAVE_fprintf_s || __CRT_HAVE_fprintf_unlocked || __CRT_HAVE_vfprintf || __CRT_HAVE_vfprintf_s || __CRT_HAVE__IO_vfprintf || __CRT_HAVE_vfprintf_unlocked || __CRT_HAVE_file_printer || __CRT_HAVE_file_printer_unlocked || __CRT_HAVE_putc || __CRT_HAVE_fputc || __CRT_HAVE__IO_putc || __CRT_HAVE_putc_unlocked || __CRT_HAVE_fputc_unlocked || __CRT_HAVE__putc_nolock || __CRT_HAVE__fputc_nolock || (__CRT_DOS && (__CRT_HAVE__flsbuf || __CRT_HAVE___swbuf)) || __CRT_HAVE_fwrite || __CRT_HAVE__IO_fwrite || __CRT_HAVE_fwrite_s || __CRT_HAVE_fwrite_unlocked || __CRT_HAVE__fwrite_nolock) */
#undef __psiginfo_defined
#endif /* !__LOCAL_stderr || (!__CRT_HAVE_fprintf && !__CRT_HAVE__IO_fprintf && !__CRT_HAVE_fprintf_s && !__CRT_HAVE_fprintf_unlocked && !__CRT_HAVE_vfprintf && !__CRT_HAVE_vfprintf_s && !__CRT_HAVE__IO_vfprintf && !__CRT_HAVE_vfprintf_unlocked && !__CRT_HAVE_file_printer && !__CRT_HAVE_file_printer_unlocked && !__CRT_HAVE_putc && !__CRT_HAVE_fputc && !__CRT_HAVE__IO_putc && !__CRT_HAVE_putc_unlocked && !__CRT_HAVE_fputc_unlocked && !__CRT_HAVE__putc_nolock && !__CRT_HAVE__fputc_nolock && (!__CRT_DOS || (!__CRT_HAVE__flsbuf && !__CRT_HAVE___swbuf)) && !__CRT_HAVE_fwrite && !__CRT_HAVE__IO_fwrite && !__CRT_HAVE_fwrite_s && !__CRT_HAVE_fwrite_unlocked && !__CRT_HAVE__fwrite_nolock) */
#endif /* !__CRT_HAVE_psiginfo */
#endif /* !__psiginfo_defined */
#ifdef __USE_KOS
#ifdef __CRT_HAVE_strsigcode_s
/* >> strsigcode_s(3)
 * Return a textual description of `code', as read from `siginfo_t::si_code',
 * and used in conjunction with a given signal `signo'. This function is used
 * for the implementation of `psiginfo(3)' */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,char const *,__NOTHROW_NCX,strsigcode_s,(__signo_t __signo, int __code),(__signo,__code))
#else /* __CRT_HAVE_strsigcode_s */
#include <libc/local/signal/strsigcode_s.h>
/* >> strsigcode_s(3)
 * Return a textual description of `code', as read from `siginfo_t::si_code',
 * and used in conjunction with a given signal `signo'. This function is used
 * for the implementation of `psiginfo(3)' */
__NAMESPACE_LOCAL_USING_OR_IMPL(strsigcode_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED char const *__NOTHROW_NCX(__LIBCCALL strsigcode_s)(__signo_t __signo, int __code) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strsigcode_s))(__signo, __code); })
#endif /* !__CRT_HAVE_strsigcode_s */
#endif /* __USE_KOS */
#endif /* __USE_XOPEN2K8 */

#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_XOPEN2K8)
/* >> siginterrupt(3)
 * Set the `SA_RESTART' of the already-established signal handler for `signo',
 * as well as cause any future handler established by `bsd_signal()' or one of
 * its aliases to immediately be established with `SA_RESTART' set/cleared
 * @param: interrupt: When == 0: clear `SA_RESTART' for the signal handler of `signo'
 *                    When != 0: set `SA_RESTART'  for the signal handler of  `signo'
 * @return: 0:  Success
 * @return: -1: [errno=EINVAL] The given `signo' is invalid */
__CDECLARE_OPT(,int,__NOTHROW_NCX,siginterrupt,(__signo_t __signo, __STDC_INT_AS_UINT_T __interrupt),(__signo,__interrupt))
#ifdef __CRT_HAVE_sigstack
/* >> sigstack(2)
 * Deprecated, and slightly different version of `sigaltstack(2)'
 * @return: 0:  Success
 * @return: -1: Error (s.a. `errno') */
__CDECLARE(,int,__NOTHROW_NCX,sigstack,(struct sigstack *__ss, struct sigstack *__oss),(__ss,__oss))
#elif defined(__SS_ONSTACK) && defined(__SS_DISABLE) && defined(__CRT_HAVE_sigaltstack)
#include <libc/local/signal/sigstack.h>
/* >> sigstack(2)
 * Deprecated, and slightly different version of `sigaltstack(2)'
 * @return: 0:  Success
 * @return: -1: Error (s.a. `errno') */
__NAMESPACE_LOCAL_USING_OR_IMPL(sigstack, __FORCELOCAL __ATTR_ARTIFICIAL int __NOTHROW_NCX(__LIBCCALL sigstack)(struct sigstack *__ss, struct sigstack *__oss) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sigstack))(__ss, __oss); })
#endif /* ... */
/* >> sigaltstack(2)
 * Get/Set the alternate signal stack for the calling thread. When set,
 * the alternate signal stack can be used to host signal handlers  that
 * have been established with the `SA_ONSTACK' flag in `sa_flags'.
 * @return: 0:  Success
 * @return: -1: Error (s.a. `errno') */
__CDECLARE_OPT(,int,__NOTHROW_NCX,sigaltstack,(struct sigaltstack const *__ss, struct sigaltstack *__oss),(__ss,__oss))
#endif /* __USE_XOPEN_EXTENDED || __USE_XOPEN2K8 */

#ifdef __USE_XOPEN_EXTENDED
#ifdef __CRT_HAVE_sighold
/* >> sighold(3)
 * Mask a single signal  `signo', which is the  same
 * as `sigprocmask(SIG_BLOCK, MASKFOR(signo), NULL)'
 * @return: 0:  Success
 * @return: -1: Error (s.a. `errno') */
__CDECLARE(,int,__NOTHROW_NCX,sighold,(__signo_t __signo),(__signo))
#elif defined(__SIG_BLOCK) && (defined(__CRT_HAVE_sigprocmask) || defined(__CRT_HAVE___sigprocmask) || defined(__CRT_HAVE___libc_sigprocmask) || defined(__CRT_HAVE_pthread_sigmask) || defined(__CRT_HAVE_thr_sigsetmask))
#include <libc/local/signal/sighold.h>
/* >> sighold(3)
 * Mask a single signal  `signo', which is the  same
 * as `sigprocmask(SIG_BLOCK, MASKFOR(signo), NULL)'
 * @return: 0:  Success
 * @return: -1: Error (s.a. `errno') */
__NAMESPACE_LOCAL_USING_OR_IMPL(sighold, __FORCELOCAL __ATTR_ARTIFICIAL int __NOTHROW_NCX(__LIBCCALL sighold)(__signo_t __signo) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sighold))(__signo); })
#endif /* ... */
#ifdef __CRT_HAVE_sigrelse
/* >> sighold(3)
 * Unmask a single signal  `signo', which is the  same
 * as `sigprocmask(SIG_UNBLOCK, MASKFOR(signo), NULL)'
 * @return: 0:  Success
 * @return: -1: Error (s.a. `errno') */
__CDECLARE(,int,__NOTHROW_NCX,sigrelse,(__signo_t __signo),(__signo))
#elif defined(__SIG_UNBLOCK) && (defined(__CRT_HAVE_sigprocmask) || defined(__CRT_HAVE___sigprocmask) || defined(__CRT_HAVE___libc_sigprocmask) || defined(__CRT_HAVE_pthread_sigmask) || defined(__CRT_HAVE_thr_sigsetmask))
#include <libc/local/signal/sigrelse.h>
/* >> sighold(3)
 * Unmask a single signal  `signo', which is the  same
 * as `sigprocmask(SIG_UNBLOCK, MASKFOR(signo), NULL)'
 * @return: 0:  Success
 * @return: -1: Error (s.a. `errno') */
__NAMESPACE_LOCAL_USING_OR_IMPL(sigrelse, __FORCELOCAL __ATTR_ARTIFICIAL int __NOTHROW_NCX(__LIBCCALL sigrelse)(__signo_t __signo) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sigrelse))(__signo); })
#endif /* ... */
#ifdef __CRT_HAVE_sigignore
/* >> sigignore(3)
 * Change the disposition of `signo' to `SIG_IGN' using `bsd_signal(3)'
 * @return: 0:  Success
 * @return: -1: Error (s.a. `errno') */
__CDECLARE(,int,__NOTHROW_NCX,sigignore,(__signo_t __signo),(__signo))
#elif defined(__SIG_IGN) && defined(__SIG_ERR) && (defined(__CRT_HAVE_bsd_signal) || defined(__CRT_HAVE___bsd_signal))
#include <libc/local/signal/sigignore.h>
/* >> sigignore(3)
 * Change the disposition of `signo' to `SIG_IGN' using `bsd_signal(3)'
 * @return: 0:  Success
 * @return: -1: Error (s.a. `errno') */
__NAMESPACE_LOCAL_USING_OR_IMPL(sigignore, __FORCELOCAL __ATTR_ARTIFICIAL int __NOTHROW_NCX(__LIBCCALL sigignore)(__signo_t __signo) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sigignore))(__signo); })
#endif /* ... */
#ifdef __CRT_HAVE_sigset
/* >> sigset(3)
 * Set the handler of `signo'  to `disp', or add `signo'  to
 * the calling threads's signal mask when `disp == SIG_HOLD'
 * @return: 0:  Success
 * @return: -1: Error (s.a. `errno') */
__CDECLARE(,__sighandler_t,__NOTHROW_NCX,sigset,(__signo_t __signo, __sighandler_t __disp),(__signo,__disp))
#elif defined(__SIG_ERR) && defined(__SIG_HOLD) && defined(__SIG_BLOCK) && (defined(__CRT_HAVE_sigprocmask) || defined(__CRT_HAVE___sigprocmask) || defined(__CRT_HAVE___libc_sigprocmask) || defined(__CRT_HAVE_pthread_sigmask) || defined(__CRT_HAVE_thr_sigsetmask)) && (defined(__CRT_HAVE_sigaction) || defined(__CRT_HAVE___sigaction))
#include <libc/local/signal/sigset.h>
/* >> sigset(3)
 * Set the handler of `signo'  to `disp', or add `signo'  to
 * the calling threads's signal mask when `disp == SIG_HOLD'
 * @return: 0:  Success
 * @return: -1: Error (s.a. `errno') */
__NAMESPACE_LOCAL_USING_OR_IMPL(sigset, __FORCELOCAL __ATTR_ARTIFICIAL __sighandler_t __NOTHROW_NCX(__LIBCCALL sigset)(__signo_t __signo, __sighandler_t __disp) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sigset))(__signo, __disp); })
#endif /* ... */
#endif /* __USE_XOPEN_EXTENDED */

#ifdef __CRT_HAVE___libc_current_sigrtmin
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__signo_t,__NOTHROW_NCX,__libc_current_sigrtmin,(void),())
#elif defined(__CRT_HAVE___libc_current_sigrtmin_private)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__signo_t,__NOTHROW_NCX,__libc_current_sigrtmin,(void),__libc_current_sigrtmin_private,())
#elif defined(__SIGRTMIN)
#include <libc/local/signal/__libc_current_sigrtmin.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(__libc_current_sigrtmin, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __signo_t __NOTHROW_NCX(__LIBCCALL __libc_current_sigrtmin)(void) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__libc_current_sigrtmin))(); })
#endif /* ... */
#ifdef __CRT_HAVE___libc_current_sigrtmax
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__signo_t,__NOTHROW_NCX,__libc_current_sigrtmax,(void),())
#elif defined(__CRT_HAVE___libc_current_sigrtmax_private)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__signo_t,__NOTHROW_NCX,__libc_current_sigrtmax,(void),__libc_current_sigrtmax_private,())
#elif defined(__SIGRTMAX)
#include <libc/local/signal/__libc_current_sigrtmax.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(__libc_current_sigrtmax, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __signo_t __NOTHROW_NCX(__LIBCCALL __libc_current_sigrtmax)(void) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__libc_current_sigrtmax))(); })
#endif /* ... */

#if defined(__USE_POSIX199506) || defined(__USE_UNIX98)
#ifndef __pthread_sigmask_defined
#define __pthread_sigmask_defined
#ifdef __CRT_HAVE_pthread_sigmask
/* >> pthread_sigmask(3)
 * Thread-safe version of `sigprocmask(2)'. Note though, that on
 * many systems (including KOS), this function behaves identical
 * to `sigprocmask()', though portable programs should still use
 * this function if they intend to use multiple threads.
 * @return: EOK:    Success
 * @return: EINVAL: Invalid `how' */
__CDECLARE(,__errno_t,__NOTHROW_NCX,pthread_sigmask,(__STDC_INT_AS_UINT_T __how, struct __sigset_struct const *__newmask, struct __sigset_struct *__oldmask),(__how,__newmask,__oldmask))
#elif defined(__CRT_HAVE_thr_sigsetmask)
/* >> pthread_sigmask(3)
 * Thread-safe version of `sigprocmask(2)'. Note though, that on
 * many systems (including KOS), this function behaves identical
 * to `sigprocmask()', though portable programs should still use
 * this function if they intend to use multiple threads.
 * @return: EOK:    Success
 * @return: EINVAL: Invalid `how' */
__CREDIRECT(,__errno_t,__NOTHROW_NCX,pthread_sigmask,(__STDC_INT_AS_UINT_T __how, struct __sigset_struct const *__newmask, struct __sigset_struct *__oldmask),thr_sigsetmask,(__how,__newmask,__oldmask))
#elif defined(__CRT_HAVE_sigprocmask)
/* >> pthread_sigmask(3)
 * Thread-safe version of `sigprocmask(2)'. Note though, that on
 * many systems (including KOS), this function behaves identical
 * to `sigprocmask()', though portable programs should still use
 * this function if they intend to use multiple threads.
 * @return: EOK:    Success
 * @return: EINVAL: Invalid `how' */
__CREDIRECT(,__errno_t,__NOTHROW_NCX,pthread_sigmask,(__STDC_INT_AS_UINT_T __how, struct __sigset_struct const *__newmask, struct __sigset_struct *__oldmask),sigprocmask,(__how,__newmask,__oldmask))
#else /* ... */
#undef __pthread_sigmask_defined
#endif /* !... */
#endif /* !__pthread_sigmask_defined */
#ifndef __pthread_kill_defined
#define __pthread_kill_defined
#ifdef __CRT_HAVE_pthread_kill
/* >> pthread_kill(3)
 * Portable function for sending a signal to a specific `pthread' within one's own process.
 * @return: EOK:    Success
 * @return: EINVAL: The given `signo' is invalid */
__CDECLARE(,__errno_t,__NOTHROW_NCX,pthread_kill,(__pthread_t __pthread, __signo_t __signo),(__pthread,__signo))
#elif defined(__CRT_HAVE_thr_kill)
/* >> pthread_kill(3)
 * Portable function for sending a signal to a specific `pthread' within one's own process.
 * @return: EOK:    Success
 * @return: EINVAL: The given `signo' is invalid */
__CREDIRECT(,__errno_t,__NOTHROW_NCX,pthread_kill,(__pthread_t __pthread, __signo_t __signo),thr_kill,(__pthread,__signo))
#else /* ... */
#undef __pthread_kill_defined
#endif /* !... */
#endif /* !__pthread_kill_defined */
#ifdef __USE_GNU
#if !defined(__pthread_sigqueue_defined) && defined(__CRT_HAVE_pthread_sigqueue)
#define __pthread_sigqueue_defined
/* >> pthread_sigqueue(3)
 * This function is for `pthread_kill(3)', what `sigqueue(2)' is for  `kill(2)',
 * in that it sends a signal to `pthread', alongside a custom signal value `val'
 * @param: signo: The signal number to deliver. When set to `0', no signal is  delivered,
 *                and this function can be used to test if the caller would be allowed to
 *                send signals to the process(es) specified by `pid'
 * @param: val:   An additional value to pass alongside the signal itself. This value can
 *                read as `info->si_value' from within a 3-arg signal handler established
 *                by `pid', or  may also be  returned by a  call to `sigwaitinfo(2)'  and
 *                friends made by `pid'.
 * @return: EOK:    Success
 * @return: EINVAL: The given `signo' is invalid
 * @return: ESRCH:  The given `pthread' has already terminated, and could no longer handle the signal */
__CDECLARE(,__errno_t,__NOTHROW_NCX,pthread_sigqueue,(__pthread_t __pthread, __signo_t __signo, union sigval const __val),(__pthread,__signo,__val))
#endif /* !__pthread_sigqueue_defined && __CRT_HAVE_pthread_sigqueue */
#endif /* __USE_GNU */
#endif /* __USE_POSIX199506 || __USE_UNIX98 */
#ifdef __USE_KOS
/* Initialize a `sigset_t' as empty:
 * >> static sigset_t myset = SIGSET_INIT_EMPTY; */
#define SIGSET_INIT_EMPTY __SIGSET_INIT(0)

/* Initialize a `sigset_t' as filled:
 * >> static sigset_t myset = SIGSET_INIT_FULL; */
#define SIGSET_INIT_FULL __SIGSET_INIT((__ULONGPTR_TYPE__)-1)
#endif /* __USE_KOS */

/* GLibc function aliases originally found in <bits/sigset.h>
 * Because these don't violate namespacing rules, and because
 * <bits/sigset.h> is included unconditionally, we also define
 * these unconditionally! */

#ifdef __CRT_HAVE_sigemptyset
/* >> sigemptyset(3)
 * Clear the given signal set of all contained signals
 * @return: 0: Always returns `0' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,__sigemptyset,(struct __sigset_struct *__set),sigemptyset,(__set))
#else /* __CRT_HAVE_sigemptyset */
#include <libc/local/signal/sigemptyset.h>
/* >> sigemptyset(3)
 * Clear the given signal set of all contained signals
 * @return: 0: Always returns `0' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL __sigemptyset)(struct __sigset_struct *__set) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sigemptyset))(__set); }
#endif /* !__CRT_HAVE_sigemptyset */
#ifdef __CRT_HAVE_sigfillset
/* >> sigfillset(3)
 * Add all possible signals (possibly even including undefined signals,
 * though these would be ignored by the kernel) to the given signal set
 * @return: 0: Always returns `0' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,__sigfillset,(struct __sigset_struct *__set),sigfillset,(__set))
#else /* __CRT_HAVE_sigfillset */
#include <libc/local/signal/sigfillset.h>
/* >> sigfillset(3)
 * Add all possible signals (possibly even including undefined signals,
 * though these would be ignored by the kernel) to the given signal set
 * @return: 0: Always returns `0' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL __sigfillset)(struct __sigset_struct *__set) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sigfillset))(__set); }
#endif /* !__CRT_HAVE_sigfillset */
#ifdef __USE_GNU
#ifdef __CRT_HAVE_sigisemptyset
/* >> sigisemptyset(3)
 * Check if the given signal set is empty
 * @return: != 0: Yes, it is empty
 * @return: == 0: No, at least 1 signal is contained */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,__sigisemptyset,(struct __sigset_struct const *__restrict __set),sigisemptyset,(__set))
#else /* __CRT_HAVE_sigisemptyset */
#include <libc/local/signal/sigisemptyset.h>
/* >> sigisemptyset(3)
 * Check if the given signal set is empty
 * @return: != 0: Yes, it is empty
 * @return: == 0: No, at least 1 signal is contained */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL __sigisemptyset)(struct __sigset_struct const *__restrict __set) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sigisemptyset))(__set); }
#endif /* !__CRT_HAVE_sigisemptyset */
#ifdef __CRT_HAVE_sigandset
/* >> sigandset(3)
 * Set-up every signal `S' from `set' as the result of `set[S] = left[S] & right[S]'
 * @return: 0: Always returns `0' */
__CREDIRECT(__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_NCX,__sigandset,(struct __sigset_struct *__set, struct __sigset_struct const *__left, struct __sigset_struct const *__right),sigandset,(__set,__left,__right))
#else /* __CRT_HAVE_sigandset */
#include <libc/local/signal/sigandset.h>
/* >> sigandset(3)
 * Set-up every signal `S' from `set' as the result of `set[S] = left[S] & right[S]'
 * @return: 0: Always returns `0' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2, 3)) int __NOTHROW_NCX(__LIBCCALL __sigandset)(struct __sigset_struct *__set, struct __sigset_struct const *__left, struct __sigset_struct const *__right) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sigandset))(__set, __left, __right); }
#endif /* !__CRT_HAVE_sigandset */
#ifdef __CRT_HAVE_sigorset
/* >> sigorset(3)
 * Set-up every signal `S' from `set' as the result of `set[S] = left[S] | right[S]'
 * @return: 0: Always returns `0' */
__CREDIRECT(__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_NCX,__sigorset,(struct __sigset_struct *__set, struct __sigset_struct const *__left, struct __sigset_struct const *__right),sigorset,(__set,__left,__right))
#else /* __CRT_HAVE_sigorset */
#include <libc/local/signal/sigorset.h>
/* >> sigorset(3)
 * Set-up every signal `S' from `set' as the result of `set[S] = left[S] | right[S]'
 * @return: 0: Always returns `0' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2, 3)) int __NOTHROW_NCX(__LIBCCALL __sigorset)(struct __sigset_struct *__set, struct __sigset_struct const *__left, struct __sigset_struct const *__right) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sigorset))(__set, __left, __right); }
#endif /* !__CRT_HAVE_sigorset */
#endif /* __USE_GNU */
#ifdef __CRT_HAVE_sigismember
/* >> sigismember(3)
 * Check if a given `signo' is apart of the a given signal set
 * @return: >1: The given `signo' is apart of `set' (may be returned by the kernel-version of this function)
 * @return:  1: The given `signo' is apart of `set'
 * @return:  0: The given `signo' isn't apart of `set'
 * @return: -1: [errno=EINVAL] invalid `signo'.
 *              Not returned by the kernel-version of this function! */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,__sigismember,(struct __sigset_struct const *__set, __signo_t __signo),sigismember,{ __ULONGPTR_TYPE__ __mask, __word; __PRIVATE_SIGSET_VALIDATE_SIGNO(__signo) __mask = __sigset_mask(__signo); __word = __sigset_word(__signo); return (__set->__val[__word] & __mask) __PRIVATE_SIGSET_ISMEMBER_EXT; })
#elif defined(__CRT_HAVE___sigismember)
/* >> sigismember(3)
 * Check if a given `signo' is apart of the a given signal set
 * @return: >1: The given `signo' is apart of `set' (may be returned by the kernel-version of this function)
 * @return:  1: The given `signo' is apart of `set'
 * @return:  0: The given `signo' isn't apart of `set'
 * @return: -1: [errno=EINVAL] invalid `signo'.
 *              Not returned by the kernel-version of this function! */
__CEIDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,__sigismember,(struct __sigset_struct const *__set, __signo_t __signo),{ __ULONGPTR_TYPE__ __mask, __word; __PRIVATE_SIGSET_VALIDATE_SIGNO(__signo) __mask = __sigset_mask(__signo); __word = __sigset_word(__signo); return (__set->__val[__word] & __mask) __PRIVATE_SIGSET_ISMEMBER_EXT; })
#else /* ... */
/* >> sigismember(3)
 * Check if a given `signo' is apart of the a given signal set
 * @return: >1: The given `signo' is apart of `set' (may be returned by the kernel-version of this function)
 * @return:  1: The given `signo' is apart of `set'
 * @return:  0: The given `signo' isn't apart of `set'
 * @return: -1: [errno=EINVAL] invalid `signo'.
 *              Not returned by the kernel-version of this function! */
__LOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL __sigismember)(struct __sigset_struct const *__set, __signo_t __signo) { __ULONGPTR_TYPE__ __mask, __word; __PRIVATE_SIGSET_VALIDATE_SIGNO(__signo) __mask = __sigset_mask(__signo); __word = __sigset_word(__signo); return (__set->__val[__word] & __mask) __PRIVATE_SIGSET_ISMEMBER_EXT; }
#endif /* !... */
#ifdef __CRT_HAVE_sigaddset
/* >> sigaddset(3)
 * Add only the given `signo' to the given signal set
 * @return: 0:  Success (Always returned by the kernel-version)
 * @return: -1: [errno=EINVAL] invalid `signo'.
 *              Not returned by the kernel-version of this function! */
__CEIREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,__sigaddset,(struct __sigset_struct *__set, __signo_t __signo),sigaddset,{ __ULONGPTR_TYPE__ __mask, __word; __PRIVATE_SIGSET_VALIDATE_SIGNO(__signo) __mask = __sigset_mask(__signo); __word = __sigset_word(__signo); __set->__val[__word] |= __mask; return 0; })
#elif defined(__CRT_HAVE___sigaddset)
/* >> sigaddset(3)
 * Add only the given `signo' to the given signal set
 * @return: 0:  Success (Always returned by the kernel-version)
 * @return: -1: [errno=EINVAL] invalid `signo'.
 *              Not returned by the kernel-version of this function! */
__CEIDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,__sigaddset,(struct __sigset_struct *__set, __signo_t __signo),{ __ULONGPTR_TYPE__ __mask, __word; __PRIVATE_SIGSET_VALIDATE_SIGNO(__signo) __mask = __sigset_mask(__signo); __word = __sigset_word(__signo); __set->__val[__word] |= __mask; return 0; })
#else /* ... */
/* >> sigaddset(3)
 * Add only the given `signo' to the given signal set
 * @return: 0:  Success (Always returned by the kernel-version)
 * @return: -1: [errno=EINVAL] invalid `signo'.
 *              Not returned by the kernel-version of this function! */
__LOCAL __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL __sigaddset)(struct __sigset_struct *__set, __signo_t __signo) { __ULONGPTR_TYPE__ __mask, __word; __PRIVATE_SIGSET_VALIDATE_SIGNO(__signo) __mask = __sigset_mask(__signo); __word = __sigset_word(__signo); __set->__val[__word] |= __mask; return 0; }
#endif /* !... */
#ifdef __CRT_HAVE_sigdelset
/* >> sigdelset(3)
 * Remove only the given `signo' from the given signal set
 * @return: 0:  Success (Always returned by the kernel-version)
 * @return: -1: [errno=EINVAL] invalid `signo'.
 *              Not returned by the kernel-version of this function! */
__CEIREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,__sigdelset,(struct __sigset_struct *__set, __signo_t __signo),sigdelset,{ __ULONGPTR_TYPE__ __mask, __word; __PRIVATE_SIGSET_VALIDATE_SIGNO(__signo) __mask = __sigset_mask(__signo); __word = __sigset_word(__signo); __set->__val[__word] &= ~__mask; return 0; })
#elif defined(__CRT_HAVE___sigdelset)
/* >> sigdelset(3)
 * Remove only the given `signo' from the given signal set
 * @return: 0:  Success (Always returned by the kernel-version)
 * @return: -1: [errno=EINVAL] invalid `signo'.
 *              Not returned by the kernel-version of this function! */
__CEIDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,__sigdelset,(struct __sigset_struct *__set, __signo_t __signo),{ __ULONGPTR_TYPE__ __mask, __word; __PRIVATE_SIGSET_VALIDATE_SIGNO(__signo) __mask = __sigset_mask(__signo); __word = __sigset_word(__signo); __set->__val[__word] &= ~__mask; return 0; })
#else /* ... */
/* >> sigdelset(3)
 * Remove only the given `signo' from the given signal set
 * @return: 0:  Success (Always returned by the kernel-version)
 * @return: -1: [errno=EINVAL] invalid `signo'.
 *              Not returned by the kernel-version of this function! */
__LOCAL __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL __sigdelset)(struct __sigset_struct *__set, __signo_t __signo) { __ULONGPTR_TYPE__ __mask, __word; __PRIVATE_SIGSET_VALIDATE_SIGNO(__signo) __mask = __sigset_mask(__signo); __word = __sigset_word(__signo); __set->__val[__word] &= ~__mask; return 0; }
#endif /* !... */
/* These appear in glibc under these  names, however these names collide  with
 * some escapes in a couple of places, so only define them when we're supposed
 * to emulate glibc as closely as possible. */
#ifdef __USE_GLIBC
#undef __sigmask
#undef __sigword
/* Return the mask or index for a specific signal `sig' within some sigset. */
#define __sigmask(sig) __sigset_mask(sig)
#define __sigword(sig) __sigset_word(sig)
#endif /* __USE_GLIBC */

#ifdef __USE_NETBSD
#ifdef __CRT_HAVE_sigabbrev_np
/* >> sigabbrev_np(3)
 * Return the name of a given signal, _without_ the leading `SIG*' prefix.
 * When the given `signum' isn't  recognized, `NULL' is returned  instead. */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,char const *,__NOTHROW,signalname,(__signo_t __signum),sigabbrev_np,(__signum))
#elif defined(__CRT_HAVE_signalname)
/* >> sigabbrev_np(3)
 * Return the name of a given signal, _without_ the leading `SIG*' prefix.
 * When the given `signum' isn't  recognized, `NULL' is returned  instead. */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,char const *,__NOTHROW,signalname,(__signo_t __signum),(__signum))
#else /* ... */
#include <libc/local/string/sigabbrev_np.h>
/* >> sigabbrev_np(3)
 * Return the name of a given signal, _without_ the leading `SIG*' prefix.
 * When the given `signum' isn't  recognized, `NULL' is returned  instead. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED char const *__NOTHROW(__LIBCCALL signalname)(__signo_t __signum) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sigabbrev_np))(__signum); }
#endif /* !... */
#ifdef __CRT_HAVE_signalnumber
/* >> signalnumber(3)
 * Similar to `strtosigno(3)', however ignore any leading `SIG*'
 * prefix of `name', and  do a case-insensitive compare  between
 * the given `name', and the  signal's actual name. When  `name'
 * isn't recognized, return `0' instead.
 * This function also handles stuff like "SIGRTMIN+1" or "9" */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__signo_t,__NOTHROW_NCX,signalnumber,(const char *__name),(__name))
#else /* __CRT_HAVE_signalnumber */
#include <libc/local/signal/signalnumber.h>
/* >> signalnumber(3)
 * Similar to `strtosigno(3)', however ignore any leading `SIG*'
 * prefix of `name', and  do a case-insensitive compare  between
 * the given `name', and the  signal's actual name. When  `name'
 * isn't recognized, return `0' instead.
 * This function also handles stuff like "SIGRTMIN+1" or "9" */
__NAMESPACE_LOCAL_USING_OR_IMPL(signalnumber, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __signo_t __NOTHROW_NCX(__LIBCCALL signalnumber)(const char *__name) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(signalnumber))(__name); })
#endif /* !__CRT_HAVE_signalnumber */
#ifdef __CRT_HAVE_signalnext
/* >> signalnext(3)
 * Return the next-greater signal number that comes after `signo'
 * When  no such signal number exists, return `0'. When the given
 * `signo' is `0', return the lowest valid signal number. */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__signo_t,__NOTHROW_NCX,signalnext,(__signo_t __signo),(__signo))
#else /* __CRT_HAVE_signalnext */
#include <libc/local/signal/signalnext.h>
/* >> signalnext(3)
 * Return the next-greater signal number that comes after `signo'
 * When  no such signal number exists, return `0'. When the given
 * `signo' is `0', return the lowest valid signal number. */
__NAMESPACE_LOCAL_USING_OR_IMPL(signalnext, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __signo_t __NOTHROW_NCX(__LIBCCALL signalnext)(__signo_t __signo) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(signalnext))(__signo); })
#endif /* !__CRT_HAVE_signalnext */
#endif /* __USE_NETBSD */

#ifdef __USE_SOLARIS
#define SIG2STR_MAX 32
#ifdef __CRT_HAVE_sig2str
/* >> sig2str(3)
 * Wrapper around  `sigabbrev_np(3)', that  also adds  additional
 * handling for `SIGRTMIN...`SIGRTMAX' signals, which are encoded
 * in a way that is compatible with `str2sig(3)'. */
__CDECLARE(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,sig2str,(__signo_t __signo, char __buf[32]),(__signo,__buf))
#else /* __CRT_HAVE_sig2str */
#include <libc/local/signal/sig2str.h>
/* >> sig2str(3)
 * Wrapper around  `sigabbrev_np(3)', that  also adds  additional
 * handling for `SIGRTMIN...`SIGRTMAX' signals, which are encoded
 * in a way that is compatible with `str2sig(3)'. */
__NAMESPACE_LOCAL_USING_OR_IMPL(sig2str, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2)) int __NOTHROW_NCX(__LIBCCALL sig2str)(__signo_t __signo, char __buf[32]) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sig2str))(__signo, __buf); })
#endif /* !__CRT_HAVE_sig2str */
#ifdef __CRT_HAVE_str2sig
/* >> str2sig(3)
 * More restrictive version of `signalnumber(3)':
 *  - Requires all name-characters to be upper-case
 *  - Doesn't automatically remove any "SIG" prefix.
 * @return: 0 : Success; `*p_signo' was filled
 * @return: -1: Unrecognized `name' (`errno(3)' was _NOT_ modified) */
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,str2sig,(const char *__name, __signo_t *__p_signo),(__name,__p_signo))
#else /* __CRT_HAVE_str2sig */
#include <libc/local/signal/str2sig.h>
/* >> str2sig(3)
 * More restrictive version of `signalnumber(3)':
 *  - Requires all name-characters to be upper-case
 *  - Doesn't automatically remove any "SIG" prefix.
 * @return: 0 : Success; `*p_signo' was filled
 * @return: -1: Unrecognized `name' (`errno(3)' was _NOT_ modified) */
__NAMESPACE_LOCAL_USING_OR_IMPL(str2sig, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL str2sig)(const char *__name, __signo_t *__p_signo) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(str2sig))(__name, __p_signo); })
#endif /* !__CRT_HAVE_str2sig */
#endif /* __USE_SOLARIS */

#endif /* __CC__ */

__SYSDECL_END

#ifdef __CXX_SYSTEM_HEADER
#define _CXX_STDONLY_CSIGNAL
#undef _SIGNAL_H
#endif /* __CXX_SYSTEM_HEADER */
#endif /* !_CXX_STDONLY_CSIGNAL */
#endif /* !_SIGNAL_H */
