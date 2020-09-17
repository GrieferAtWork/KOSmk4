/* HASH CRC-32:0xc4f52313 */
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
#ifndef _SIGNAL_H
#define _SIGNAL_H 1

#ifdef _CXX_STDONLY_CSIGNAL
#ifdef __CXX_SYSTEM_HEADER
#undef _SIGNAL_H /* Allow the C-header to be re-included to import all std::-symbols into the global namespace. */
#else /* __CXX_SYSTEM_HEADER */
/* Import all symbols into the global namespace when re-including "signal.h" after "csignal" */
#ifndef __sig_atomic_t_defined
#define __sig_atomic_t_defined 1
__NAMESPACE_STD_USING(sig_atomic_t)
#endif /* !__sig_atomic_t_defined */
#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_XOPEN2K8)
#ifndef __size_t_defined
#define __size_t_defined 1
__NAMESPACE_STD_USING(size_t)
#endif /* !__size_t_defined */
#endif /* __USE_XOPEN_EXTENDED || __USE_XOPEN2K8 */
#ifdef __CRT_HAVE_raise
__NAMESPACE_STD_USING(raise)
#endif /* __CRT_HAVE_raise */
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
#include <bits/sigset.h>
#include <bits/types.h>

#ifdef __USE_POSIX199309
#include <bits/timespec.h>
#endif /* __USE_POSIX199309 */

#ifdef __USE_MISC
#include <bits/sigcontext.h>
#endif /* __USE_MISC */

#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_XOPEN2K8)
#include <asm/sigstack.h>
#include <bits/sigstack.h> /* `struct sigstack', `struct sigaltstack' */
#if defined(__USE_XOPEN) || defined(__USE_XOPEN2K8)
#include <sys/ucontext.h>
#endif /* __USE_XOPEN || __USE_XOPEN2K8 */
#endif /* __USE_XOPEN_EXTENDED || __USE_XOPEN2K8 */

#if defined(__USE_POSIX199506) || defined(__USE_UNIX98)
#include <bits/crt/pthreadtypes.h>
#include <bits/sigval.h> /* union sigval */
#endif /* __USE_POSIX199506 || __USE_UNIX98 */

#ifdef __USE_POSIX
#include <bits/sigaction-struct.h>
#endif /* __USE_POSIX */

#if (defined(__USE_POSIX199309) || defined(__USE_XOPEN_EXTENDED) || defined(__USE_KOS))
#include <asm/sigevent.h>
#include <asm/siginfo.h>
#include <bits/sigevent.h>       /* struct sigevent */
#include <bits/siginfo-struct.h> /* struct __siginfo_struct */
#include <bits/sigval.h>         /* union sigval */
#endif /* __USE_POSIX199309 || __USE_XOPEN_EXTENDED || __USE_KOS */

__SYSDECL_BEGIN

/* Fake signal functions. */
#ifdef __SIG_ERR
#define SIG_ERR (__CCAST(__sighandler_t)__SIG_ERR) /* Error return. */
#endif /* __SIG_ERR */
#ifdef __SIG_DFL
#define SIG_DFL (__CCAST(__sighandler_t)__SIG_DFL) /* Default action. */
#endif /* __SIG_DFL */
#ifdef __SIG_IGN
#define SIG_IGN (__CCAST(__sighandler_t)__SIG_IGN) /* Ignore signal. */
#endif /* __SIG_IGN */

#ifdef __USE_DOS
#ifdef __SIG_GET
#define SIG_GET (__CCAST(__sighandler_t)__SIG_GET) /* Only get the current handler (accepted by `signal(2)') */
#endif /* __SIG_GET */
#ifdef __SIG_SGE
#define SIG_SGE (__CCAST(__sighandler_t)__SIG_SGE) /* Signal gets error. */
#endif /* __SIG_SGE */
#ifdef __SIG_ACK
#define SIG_ACK (__CCAST(__sighandler_t)__SIG_ACK) /* Acknowledge. */
#endif /* __SIG_ACK */
#endif /* __USE_DOS */

#ifdef __USE_UNIX98
#ifdef __SIG_HOLD
#define SIG_HOLD (__CCAST(__sighandler_t)__SIG_HOLD) /* Add signal to hold mask. */
#endif /* __SIG_HOLD */
#endif /* __USE_UNIX98 */

#ifdef __USE_KOS
#ifdef __SIG_TERM
#define SIG_TERM  (__CCAST(__sighandler_t)__SIG_TERM) /* Terminate the receiving process. */
#endif /* __SIG_TERM */
#ifdef __SIG_EXIT
#define SIG_EXIT  (__CCAST(__sighandler_t)__SIG_EXIT) /* Terminate the receiving thread. */
#endif /* __SIG_EXIT */
#ifdef __SIG_CONT
#define SIG_CONT  (__CCAST(__sighandler_t)__SIG_CONT) /* Continue execution. */
#endif /* __SIG_CONT */
#ifdef __SIG_STOP
#define SIG_STOP  (__CCAST(__sighandler_t)__SIG_STOP) /* Suspend execution. */
#endif /* __SIG_STOP */
#ifdef __SIG_CORE
#define SIG_CORE  (__CCAST(__sighandler_t)__SIG_CORE) /* Create a coredump and terminate. */
#endif /* __SIG_CORE */
#endif /* __USE_KOS */


/* Signals numbers. */
#ifdef __SIGHUP
#define SIGHUP    __SIGHUP     /* Hangup (POSIX). */
#endif /* __SIGHUP */
#ifdef __SIGINT
#define SIGINT    __SIGINT     /* Interrupt (ANSI). */
#endif /* __SIGINT */
#ifdef __SIGQUIT
#define SIGQUIT   __SIGQUIT    /* Quit (POSIX). */
#endif /* __SIGQUIT */
#ifdef __SIGILL
#define SIGILL    __SIGILL     /* Illegal instruction (ANSI). */
#endif /* __SIGILL */
#ifdef __SIGTRAP
#define SIGTRAP   __SIGTRAP    /* Trace trap (POSIX). */
#endif /* __SIGTRAP */
#ifdef __SIGABRT
#define SIGABRT   __SIGABRT    /* Abort (ANSI). */
#endif /* __SIGABRT */
#ifdef __SIGIOT
#define SIGIOT    __SIGIOT     /* IOT trap (4.2 BSD). */
#endif /* __SIGIOT */
#ifdef __SIGBUS
#define SIGBUS    __SIGBUS     /* BUS error (4.2 BSD). */
#endif /* __SIGBUS */
#ifdef __SIGFPE
#define SIGFPE    __SIGFPE     /* Floating-point exception (ANSI). */
#endif /* __SIGFPE */
#ifdef __SIGKILL
#define SIGKILL   __SIGKILL    /* Kill, unblockable (POSIX). */
#endif /* __SIGKILL */
#ifdef __SIGUSR1
#define SIGUSR1   __SIGUSR1    /* User-defined signal 1 (POSIX). */
#endif /* __SIGUSR1 */
#ifdef __SIGSEGV
#define SIGSEGV   __SIGSEGV    /* Segmentation violation (ANSI). */
#endif /* __SIGSEGV */
#ifdef __SIGUSR2
#define SIGUSR2   __SIGUSR2    /* User-defined signal 2 (POSIX). */
#endif /* __SIGUSR2 */
#ifdef __SIGPIPE
#define SIGPIPE   __SIGPIPE    /* Broken pipe (POSIX). */
#endif /* __SIGPIPE */
#ifdef __SIGALRM
#define SIGALRM   __SIGALRM    /* Alarm clock (POSIX). */
#endif /* __SIGALRM */
#ifdef __SIGTERM
#define SIGTERM   __SIGTERM    /* Termination (ANSI). */
#endif /* __SIGTERM */
#ifdef __SIGSTKFLT
#define SIGSTKFLT __SIGSTKFLT  /* Stack fault. */
#endif /* __SIGSTKFLT */
#ifdef __SIGCHLD
#define SIGCHLD   __SIGCHLD    /* Child status has changed (POSIX). */
#endif /* __SIGCHLD */
#ifdef __SIGCONT
#define SIGCONT   __SIGCONT    /* Continue (POSIX). */
#endif /* __SIGCONT */
#ifdef __SIGSTOP
#define SIGSTOP   __SIGSTOP    /* Stop, unblockable (POSIX). */
#endif /* __SIGSTOP */
#ifdef __SIGTSTP
#define SIGTSTP   __SIGTSTP    /* Keyboard stop (POSIX). */
#endif /* __SIGTSTP */
#ifdef __SIGTTIN
#define SIGTTIN   __SIGTTIN    /* Background read from tty (POSIX). */
#endif /* __SIGTTIN */
#ifdef __SIGTTOU
#define SIGTTOU   __SIGTTOU    /* Background write to tty (POSIX). */
#endif /* __SIGTTOU */
#ifdef __SIGURG
#define SIGURG    __SIGURG     /* Urgent condition on socket (4.2 BSD). */
#endif /* __SIGURG */
#ifdef __SIGXCPU
#define SIGXCPU   __SIGXCPU    /* CPU limit exceeded (4.2 BSD). */
#endif /* __SIGXCPU */
#ifdef __SIGXFSZ
#define SIGXFSZ   __SIGXFSZ    /* File size limit exceeded (4.2 BSD). */
#endif /* __SIGXFSZ */
#ifdef __SIGVTALRM
#define SIGVTALRM __SIGVTALRM  /* Virtual alarm clock (4.2 BSD). */
#endif /* __SIGVTALRM */
#ifdef __SIGPROF
#define SIGPROF   __SIGPROF    /* Profiling alarm clock (4.2 BSD). */
#endif /* __SIGPROF */
#ifdef __SIGWINCH
#define SIGWINCH  __SIGWINCH   /* Window size change (4.3 BSD, Sun). */
#endif /* __SIGWINCH */
#ifdef __SIGIO
#define SIGIO     __SIGIO      /* I/O now possible (4.2 BSD). */
#endif /* __SIGIO */
#ifdef __SIGPOLL
#define SIGPOLL   __SIGPOLL    /* Pollable event occurred (System V). */
#endif /* __SIGPOLL */
#ifdef __SIGPWR
#define SIGPWR    __SIGPWR     /* Power failure restart (System V). */
#endif /* __SIGPWR */
#ifdef __SIGSYS
#define SIGSYS    __SIGSYS     /* Bad system call. */
#endif /* __SIGSYS */
#ifdef __SIGCHLD
#define SIGCLD    __SIGCHLD    /* Same as SIGCHLD (System V). */
#endif /* __SIGCHLD */
#ifdef __SIGUNUSED
#define SIGUNUSED __SIGUNUSED
#elif defined(__SIGSYS)
#define SIGUNUSED __SIGSYS
#endif /* ... */

#ifdef __NSIG
#define _NSIG __NSIG /* Biggest signal number + 1 (including real-time signals). */
#endif /* __NSIG */

/* These are the hard limits of the kernel.
 * These values should not be used directly at user level. */
#if defined(__SIGRTMIN) && (!defined(__CRT_HAVE___libc_current_sigrtmin) || !defined(__CC__))
#define SIGRTMIN __SIGRTMIN
#else /* __SIGRTMIN && (!__CRT_HAVE___libc_current_sigrtmin || !__CC__) */
#define SIGRTMIN __libc_current_sigrtmin()
#endif /* !__SIGRTMIN || (__CRT_HAVE___libc_current_sigrtmin && __CC__) */
#if defined(__SIGRTMAX) && (!defined(__CRT_HAVE___libc_current_sigrtmax) || !defined(__CC__))
#define SIGRTMAX __SIGRTMAX
#else /* __SIGRTMAX && (!__CRT_HAVE___libc_current_sigrtmax || !__CC__) */
#define SIGRTMAX __libc_current_sigrtmax()
#endif /* !__SIGRTMAX || (__CRT_HAVE___libc_current_sigrtmax && __CC__) */

#ifdef __USE_DOS
/* Define DOS's signal name aliases. */
#ifdef __SIGBREAK
#define SIGBREAK __SIGBREAK /* Background read from tty (POSIX). */
#endif /* __SIGBREAK */
#ifdef __SIGABRT_COMPAT
#define SIGABRT_COMPAT __SIGABRT_COMPAT /* Abort (ANSI). */
#elif defined(__SIGABRT)
#define SIGABRT_COMPAT __SIGABRT /* Abort (ANSI). */
#endif /* ... */
#endif /* __USE_DOS */




#ifdef __USE_POSIX
/* Bits in `sa_flags'. */
#ifdef __SA_NOCLDSTOP
#define SA_NOCLDSTOP __SA_NOCLDSTOP /* Don't send SIGCHLD when children stop. */
#endif /* __SA_NOCLDSTOP */
#ifdef __SA_NOCLDWAIT
#define SA_NOCLDWAIT __SA_NOCLDWAIT /* Don't create zombie on child death. */
#endif /* __SA_NOCLDWAIT */
#ifdef __SA_SIGINFO
#define SA_SIGINFO __SA_SIGINFO /* Invoke signal-catching function with three arguments instead of one. */
#endif /* __SA_SIGINFO */

#ifdef __USE_KOS_KERNEL
#ifdef __SA_RESTORER
#define SA_RESTORER __SA_RESTORER /* A custom signal restore function (`sa_restorer') was given.
                                   * This flag is set by libc, after having filled in the `sa_restorer' field.
                                   * NOTE: On x86, the kernel assumes that this points to a function:
                                   * >> sa_restorer:
                                   * >>     movl   $SYS_sigreturn, %eax
                                   * >>     int    $0x80 */
#endif /* __SA_RESTORER */
#endif /* __USE_KOS_KERNEL */

#if defined(__USE_UNIX98) || defined(__USE_MISC)
#ifdef __SA_ONSTACK
#define SA_ONSTACK __SA_ONSTACK /* Execute the handler on sigaltstack. */
#endif /* __SA_ONSTACK */
#endif /* __USE_UNIX98 || __USE_MISC */

#if defined(__USE_UNIX98) || defined(__USE_XOPEN2K8)
#ifdef __SA_RESTART
#define SA_RESTART __SA_RESTART /* Restart restartable syscall on signal return. */
#endif /* __SA_RESTART */
#ifdef __SA_NODEFER
#define SA_NODEFER __SA_NODEFER /* Don't automatically block the signal when its handler is being executed. */
#endif /* __SA_NODEFER */
#ifdef __SA_RESETHAND
#define SA_RESETHAND __SA_RESETHAND /* Reset to SIG_DFL on entry to handler. */
#endif /* __SA_RESETHAND */
#endif /* __USE_UNIX98 || __USE_XOPEN2K8 */

#ifdef __USE_MISC
#ifdef __SA_INTERRUPT
#define SA_INTERRUPT __SA_INTERRUPT /* Historical no-op. */
#endif /* __SA_INTERRUPT */
/* Some aliases for the SA_ constants. */
#ifdef __SA_NODEFER
#define SA_NOMASK __SA_NODEFER
#endif /* __SA_NODEFER */
#ifdef __SA_RESETHAND
#define SA_ONESHOT __SA_RESETHAND
#endif /* __SA_RESETHAND */
#ifdef __SA_ONSTACK
#define SA_STACK __SA_ONSTACK
#endif /* __SA_ONSTACK */
#endif /* __USE_MISC */

/* Values for the HOW argument to `sigprocmask'. */
#ifdef __SIG_BLOCK
#define SIG_BLOCK __SIG_BLOCK /* Block signals. */
#endif /* __SIG_BLOCK */
#ifdef __SIG_UNBLOCK
#define SIG_UNBLOCK __SIG_UNBLOCK /* Unblock signals. */
#endif /* __SIG_UNBLOCK */
#ifdef __SIG_SETMASK
#define SIG_SETMASK __SIG_SETMASK /* Set the set of blocked signals. */
#endif /* __SIG_SETMASK */
#endif /* __USE_POSIX */

#if (defined(__USE_POSIX199309) || defined(__USE_XOPEN_EXTENDED) || defined(__USE_KOS))

/* `sigev_notify' values. */
#if (defined(__SIGEV_SIGNAL) || defined(__SIGEV_NONE) || \
     defined(__SIGEV_THREAD) || defined(__SIGEV_THREAD_ID))
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
	SIGEV_THREAD_ID = __SIGEV_THREAD_ID  /* Send signal to specific thread. */
#endif /* __SIGEV_THREAD_ID */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#ifdef __SIGEV_SIGNAL
#define SIGEV_SIGNAL    SIGEV_SIGNAL    /* Notify via signal. */
#endif /* __SIGEV_SIGNAL */
#ifdef __SIGEV_NONE
#define SIGEV_NONE      SIGEV_NONE      /* Other notification: meaningless. */
#endif /* __SIGEV_NONE */
#ifdef __SIGEV_THREAD
#define SIGEV_THREAD    SIGEV_THREAD    /* Deliver via thread creation. */
#endif /* __SIGEV_THREAD */
#ifdef __SIGEV_THREAD_ID
#define SIGEV_THREAD_ID SIGEV_THREAD_ID /* Send signal to specific thread. */
#endif /* __SIGEV_THREAD_ID */
#else /* __COMPILER_PREFERR_ENUMS */
#ifdef __SIGEV_SIGNAL
#define SIGEV_SIGNAL    __SIGEV_SIGNAL    /* Notify via signal. */
#endif /* __SIGEV_SIGNAL */
#ifdef __SIGEV_NONE
#define SIGEV_NONE      __SIGEV_NONE      /* Other notification: meaningless. */
#endif /* __SIGEV_NONE */
#ifdef __SIGEV_THREAD
#define SIGEV_THREAD    __SIGEV_THREAD    /* Deliver via thread creation. */
#endif /* __SIGEV_THREAD */
#ifdef __SIGEV_THREAD_ID
#define SIGEV_THREAD_ID __SIGEV_THREAD_ID /* Send signal to specific thread. */
#endif /* __SIGEV_THREAD_ID */
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
	SI_QUEUE = __SI_QUEUE,     /* Sent by sigqueue_entry. */
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
#define SI_QUEUE   SI_QUEUE   /* Sent by sigqueue_entry. */
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
#define SI_QUEUE   __SI_QUEUE   /* Sent by sigqueue_entry. */
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
#define POLL_MSG POLL_MSG /* Input message available.   */
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
#define POLL_MSG __POLL_MSG /* Input message available.   */
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

/* Possible values for `ss_flags.'. */
#if defined(__SS_ONSTACK) || defined(__SS_DISABLE)
/*[[[enum]]]*/
#ifdef __CC__
enum {
#ifdef __SS_ONSTACK
	SS_ONSTACK = __SS_ONSTACK,
#endif /* __SS_ONSTACK */
#ifdef __SS_DISABLE
	SS_DISABLE = __SS_DISABLE
#endif /* __SS_DISABLE */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#ifdef __SS_ONSTACK
#define SS_ONSTACK SS_ONSTACK
#endif /* __SS_ONSTACK */
#ifdef __SS_DISABLE
#define SS_DISABLE SS_DISABLE
#endif /* __SS_DISABLE */
#else /* __COMPILER_PREFERR_ENUMS */
#ifdef __SS_ONSTACK
#define SS_ONSTACK __SS_ONSTACK
#endif /* __SS_ONSTACK */
#ifdef __SS_DISABLE
#define SS_DISABLE __SS_DISABLE
#endif /* __SS_DISABLE */
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
#define __sigevent_t_defined 1
typedef struct sigevent sigevent_t;
#endif /* !__sigevent_t_defined */
#ifndef __siginfo_t_defined
#define __siginfo_t_defined 1
typedef struct __siginfo_struct siginfo_t;
#endif /* !__siginfo_t_defined */
#ifndef __sigval_t_defined
#define __sigval_t_defined 1
typedef union sigval sigval_t;
#endif /* !__sigval_t_defined */
#endif /* __USE_POSIX199309 || __USE_XOPEN_EXTENDED || __USE_KOS */

#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_XOPEN2K8)
#ifndef __stack_t_defined
#define __stack_t_defined 1
#ifdef __CC__
typedef struct sigaltstack stack_t;
#endif /* __CC__ */
#endif /* !__stack_t_defined */
#endif /* __USE_XOPEN_EXTENDED || __USE_XOPEN2K8 */

#ifndef __std_sig_atomic_t_defined
#define __std_sig_atomic_t_defined 1
__NAMESPACE_STD_BEGIN
/* An integral type that can be modified atomically, without the
 * possibility of a signal arriving in the middle of the operation.  */
typedef __SIG_ATOMIC_TYPE__ sig_atomic_t;
__NAMESPACE_STD_END
#endif /* !__std_sig_atomic_t_defined */
#ifndef __CXX_SYSTEM_HEADER
#ifndef __sig_atomic_t_defined
#define __sig_atomic_t_defined 1
__NAMESPACE_STD_USING(sig_atomic_t)
#endif /* !__sig_atomic_t_defined */
#endif /* !__CXX_SYSTEM_HEADER */

#ifdef __USE_POSIX
#ifndef __sigset_t_defined
#define __sigset_t_defined 1
typedef struct __sigset_struct sigset_t;
#endif /* !__sigset_t_defined */
#endif /* __USE_POSIX */

#if defined(__USE_XOPEN) || defined(__USE_XOPEN2K)
#ifndef __pid_t_defined
#define __pid_t_defined 1
typedef __pid_t pid_t;
#endif /* !__pid_t_defined */
#ifndef __uid_t_defined
#define __uid_t_defined 1
typedef __uid_t uid_t;
#endif /* !__uid_t_defined */
#endif /* __USE_XOPEN || __USE_XOPEN2K */

#ifndef ____sighandler_t_defined
#define ____sighandler_t_defined 1
typedef void (__LIBKCALL *__sighandler_t)(int __signo);
#endif /* !____sighandler_t_defined */

#ifdef __USE_GNU
#ifndef __sighandler_t_defined
#define __sighandler_t_defined 1
typedef __sighandler_t sighandler_t;
#endif /* !__sighandler_t_defined */
#endif /* __USE_GNU */

#ifdef __USE_MISC
#ifndef NSIG
#define NSIG _NSIG
#endif /* !NSIG */
typedef __sighandler_t sig_t;
#endif /* __USE_MISC */

#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_XOPEN2K8)
#ifndef __std_size_t_defined
#define __std_size_t_defined 1
__NAMESPACE_STD_BEGIN
typedef __SIZE_TYPE__ size_t;
__NAMESPACE_STD_END
#endif /* !__std_size_t_defined */

#ifndef __CXX_SYSTEM_HEADER
#ifndef __size_t_defined
#define __size_t_defined 1
__NAMESPACE_STD_USING(size_t)
#endif /* !__size_t_defined */
#endif /* !__CXX_SYSTEM_HEADER */
#endif /* __USE_XOPEN_EXTENDED || __USE_XOPEN2K8 */

__NAMESPACE_STD_BEGIN
__CDECLARE_OPT(,int,__NOTHROW_NCX,raise,(__signo_t __signo),(__signo))
#if defined(__CRT_HAVE_signal) && defined(__USE_MISC)
__CDECLARE(,__sighandler_t,__NOTHROW_NCX,signal,(__signo_t __signo, __sighandler_t __handler),(__signo,__handler))
#elif defined(__CRT_HAVE__signal) && defined(__USE_MISC)
__CREDIRECT(,__sighandler_t,__NOTHROW_NCX,signal,(__signo_t __signo, __sighandler_t __handler),_signal,(__signo,__handler))
#elif defined(__CRT_HAVE_sysv_signal)
__CREDIRECT(,__sighandler_t,__NOTHROW_NCX,signal,(__signo_t __signo, __sighandler_t __handler),sysv_signal,(__signo,__handler))
#endif /* ... */
__NAMESPACE_STD_END
#ifndef __CXX_SYSTEM_HEADER
#ifdef __CRT_HAVE_raise
__NAMESPACE_STD_USING(raise)
#endif /* __CRT_HAVE_raise */
#endif /* !__CXX_SYSTEM_HEADER */
#ifdef __CRT_HAVE_sysv_signal
__CREDIRECT(,__sighandler_t,__NOTHROW_NCX,__sysv_signal,(__signo_t __signo, __sighandler_t __handler),sysv_signal,(__signo,__handler))
#elif defined(__CRT_HAVE___sysv_signal)
__CDECLARE(,__sighandler_t,__NOTHROW_NCX,__sysv_signal,(__signo_t __signo, __sighandler_t __handler),(__signo,__handler))
#endif /* ... */
#ifdef __USE_GNU
#ifdef __CRT_HAVE_sysv_signal
__CDECLARE(,__sighandler_t,__NOTHROW_NCX,sysv_signal,(__signo_t __signo, __sighandler_t __handler),(__signo,__handler))
#elif defined(__CRT_HAVE___sysv_signal)
__CREDIRECT(,__sighandler_t,__NOTHROW_NCX,sysv_signal,(__signo_t __signo, __sighandler_t __handler),__sysv_signal,(__signo,__handler))
#endif /* ... */
#endif /* __USE_GNU */
#ifndef __CXX_SYSTEM_HEADER
#if (defined(__CRT_HAVE_signal) && defined(__USE_MISC)) || (defined(__CRT_HAVE__signal) && defined(__USE_MISC)) || defined(__CRT_HAVE_sysv_signal)
__NAMESPACE_STD_USING(signal)
#endif /* (__CRT_HAVE_signal && __USE_MISC) || (__CRT_HAVE__signal && __USE_MISC) || __CRT_HAVE_sysv_signal */
#endif /* !__CXX_SYSTEM_HEADER */
#ifdef __USE_MISC
#define sigmask(signo) __sigset_mask(signo)
__CDECLARE_OPT(,__sighandler_t,__NOTHROW_NCX,ssignal,(__signo_t __signo, __sighandler_t __handler),(__signo,__handler))
__CDECLARE_OPT(,int,__NOTHROW_NCX,gsignal,(__signo_t __signo),(__signo))
__CDECLARE_OPT(,int,__NOTHROW_NCX,sigblock,(int __mask),(__mask))
__CDECLARE_OPT(,int,__NOTHROW_NCX,sigsetmask,(int __mask),(__mask))
__CDECLARE_OPT(,int,__NOTHROW_NCX,siggetmask,(void),())

#ifndef sys_siglist
#ifdef _sys_siglist
#define sys_siglist _sys_siglist
#else /* _sys_siglist */
#ifndef ____p_sys_siglist_defined
#define ____p_sys_siglist_defined 1
#ifdef __CRT_HAVE___p_sys_siglist
__CDECLARE(__ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED,char const *const *,__NOTHROW,__p_sys_siglist,(void),())
#else /* __CRT_HAVE___p_sys_siglist */
#undef ____p_sys_siglist_defined
#endif /* !__CRT_HAVE___p_sys_siglist */
#endif /* !____p_sys_siglist_defined */
#ifdef ____p_sys_siglist_defined
#define sys_siglist  __p_sys_siglist()
#define _sys_siglist __p_sys_siglist()
#endif /* ____p_sys_siglist_defined */
#ifndef _sys_siglist
#ifdef __CRT_HAVE_sys_siglist
__LIBC char const *const sys_siglist[_NSIG];
#define sys_siglist  sys_siglist
#define _sys_siglist sys_siglist
#elif defined(__CRT_HAVE__sys_siglist)
__LIBC char const *const _sys_siglist[_NSIG];
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
__CDECLARE_VOID_OPT(__ATTR_NORETURN,__NOTHROW_NCX,sigreturn,(struct sigcontext const *__scp),(__scp))
#endif /* __USE_MISC */

#ifdef __USE_XOPEN
__CDECLARE_OPT(,__sighandler_t,__NOTHROW_NCX,bsd_signal,(__signo_t __signo, __sighandler_t __handler),(__signo,__handler))
#ifdef __CRT_HAVE___xpg_sigpause
__CREDIRECT(,int,__NOTHROW_NCX,sigpause,(__signo_t __signo),__xpg_sigpause,(__signo))
#endif /* __CRT_HAVE___xpg_sigpause */
#endif /* __USE_XOPEN */

#ifdef __USE_POSIX
__CDECLARE_OPT(,int,__NOTHROW_NCX,kill,(__pid_t __pid, __signo_t __signo),(__pid,__signo))
#ifdef __CRT_HAVE_sigemptyset
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,sigemptyset,(struct __sigset_struct *__set),(__set))
#else /* __CRT_HAVE_sigemptyset */
#include <libc/local/signal/sigemptyset.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(sigemptyset, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL sigemptyset)(struct __sigset_struct *__set) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sigemptyset))(__set); })
#endif /* !__CRT_HAVE_sigemptyset */
#ifdef __CRT_HAVE_sigfillset
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,sigfillset,(struct __sigset_struct *__set),(__set))
#else /* __CRT_HAVE_sigfillset */
#include <libc/local/signal/sigfillset.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(sigfillset, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL sigfillset)(struct __sigset_struct *__set) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sigfillset))(__set); })
#endif /* !__CRT_HAVE_sigfillset */
#ifdef __CRT_HAVE_sigaddset
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,sigaddset,(struct __sigset_struct *__set, __signo_t __signo),(__set,__signo))
#elif defined(__CRT_HAVE___sigaddset)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,sigaddset,(struct __sigset_struct *__set, __signo_t __signo),__sigaddset,(__set,__signo))
#else /* ... */
#include <libc/local/signal/sigaddset.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(sigaddset, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL sigaddset)(struct __sigset_struct *__set, __signo_t __signo) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sigaddset))(__set, __signo); })
#endif /* !... */
#ifdef __CRT_HAVE_sigdelset
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,sigdelset,(struct __sigset_struct *__set, __signo_t __signo),(__set,__signo))
#elif defined(__CRT_HAVE___sigdelset)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,sigdelset,(struct __sigset_struct *__set, __signo_t __signo),__sigdelset,(__set,__signo))
#else /* ... */
#include <libc/local/signal/sigdelset.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(sigdelset, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL sigdelset)(struct __sigset_struct *__set, __signo_t __signo) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sigdelset))(__set, __signo); })
#endif /* !... */
#ifdef __CRT_HAVE_sigismember
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,sigismember,(struct __sigset_struct const *__set, __signo_t __signo),(__set,__signo))
#elif defined(__CRT_HAVE___sigismember)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,sigismember,(struct __sigset_struct const *__set, __signo_t __signo),__sigismember,(__set,__signo))
#else /* ... */
#include <libc/local/signal/sigismember.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(sigismember, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL sigismember)(struct __sigset_struct const *__set, __signo_t __signo) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sigismember))(__set, __signo); })
#endif /* !... */
/* @param how: One of `SIG_BLOCK', `SIG_UNBLOCK' or `SIG_SETMASK' */
__CDECLARE_OPT(,int,__NOTHROW_NCX,sigprocmask,(__STDC_INT_AS_UINT_T __how, sigset_t const *__set, sigset_t *__oset),(__how,__set,__oset))
#ifdef __CRT_HAVE_sigsuspend
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,sigsuspend,(sigset_t const *__set),(__set))
#elif defined(__CRT_HAVE___sigsuspend)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,sigsuspend,(sigset_t const *__set),__sigsuspend,(__set))
#endif /* ... */
#ifdef __CRT_HAVE_sigaction
__CDECLARE(,int,__NOTHROW_NCX,sigaction,(__signo_t __signo, struct sigaction const *__act, struct sigaction *__oact),(__signo,__act,__oact))
#elif defined(__CRT_HAVE___sigaction)
__CREDIRECT(,int,__NOTHROW_NCX,sigaction,(__signo_t __signo, struct sigaction const *__act, struct sigaction *__oact),__sigaction,(__signo,__act,__oact))
#endif /* ... */
__CDECLARE_OPT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,sigpending,(sigset_t *__restrict __set),(__set))
__CDECLARE_OPT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,sigwait,(sigset_t const *__restrict __set, __signo_t *__restrict __signo),(__set,__signo))
#ifdef __USE_GNU
#ifdef __CRT_HAVE_sigisemptyset
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,sigisemptyset,(struct __sigset_struct const *__restrict __set),(__set))
#else /* __CRT_HAVE_sigisemptyset */
#include <libc/local/signal/sigisemptyset.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(sigisemptyset, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL sigisemptyset)(struct __sigset_struct const *__restrict __set) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sigisemptyset))(__set); })
#endif /* !__CRT_HAVE_sigisemptyset */
#ifdef __CRT_HAVE_sigandset
__CDECLARE(__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_NCX,sigandset,(struct __sigset_struct *__set, struct __sigset_struct const *__left, struct __sigset_struct const *__right),(__set,__left,__right))
#else /* __CRT_HAVE_sigandset */
#include <libc/local/signal/sigandset.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(sigandset, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2, 3)) int __NOTHROW_NCX(__LIBCCALL sigandset)(struct __sigset_struct *__set, struct __sigset_struct const *__left, struct __sigset_struct const *__right) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sigandset))(__set, __left, __right); })
#endif /* !__CRT_HAVE_sigandset */
#ifdef __CRT_HAVE_sigorset
__CDECLARE(__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_NCX,sigorset,(struct __sigset_struct *__set, struct __sigset_struct const *__left, struct __sigset_struct const *__right),(__set,__left,__right))
#else /* __CRT_HAVE_sigorset */
#include <libc/local/signal/sigorset.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(sigorset, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2, 3)) int __NOTHROW_NCX(__LIBCCALL sigorset)(struct __sigset_struct *__set, struct __sigset_struct const *__left, struct __sigset_struct const *__right) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sigorset))(__set, __left, __right); })
#endif /* !__CRT_HAVE_sigorset */
#endif /* __USE_GNU */
#ifdef __USE_POSIX199309
__CDECLARE_OPT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,sigwaitinfo,(struct __sigset_struct const *__restrict __set, siginfo_t *__restrict __info),(__set,__info))
#if defined(__CRT_HAVE_sigtimedwait64) && defined(__USE_TIME_BITS64)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,sigtimedwait,(struct __sigset_struct const *__restrict __set, siginfo_t *__restrict __info, struct timespec const *__timeout),sigtimedwait64,(__set,__info,__timeout))
#elif defined(__CRT_HAVE_sigtimedwait) && !defined(__USE_TIME_BITS64)
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,sigtimedwait,(struct __sigset_struct const *__restrict __set, siginfo_t *__restrict __info, struct timespec const *__timeout),(__set,__info,__timeout))
#elif defined(__CRT_HAVE_sigtimedwait64) || defined(__CRT_HAVE_sigtimedwait)
#include <libc/local/signal/sigtimedwait.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(sigtimedwait, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL sigtimedwait)(struct __sigset_struct const *__restrict __set, siginfo_t *__restrict __info, struct timespec const *__timeout) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sigtimedwait))(__set, __info, __timeout); })
#endif /* ... */
__CDECLARE_OPT(,int,__NOTHROW_NCX,sigqueue,(__pid_t __pid, __signo_t __signo, union sigval const __val),(__pid,__signo,__val))
#ifdef __USE_TIME64
#ifdef __CRT_HAVE_sigtimedwait64
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,sigtimedwait64,(struct __sigset_struct const *__restrict __set, siginfo_t *__restrict __info, struct __timespec64 const *__timeout),(__set,__info,__timeout))
#elif defined(__CRT_HAVE_sigtimedwait) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,sigtimedwait64,(struct __sigset_struct const *__restrict __set, siginfo_t *__restrict __info, struct __timespec64 const *__timeout),sigtimedwait,(__set,__info,__timeout))
#elif defined(__CRT_HAVE_sigtimedwait)
#include <libc/local/signal/sigtimedwait64.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(sigtimedwait64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL sigtimedwait64)(struct __sigset_struct const *__restrict __set, siginfo_t *__restrict __info, struct __timespec64 const *__timeout) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sigtimedwait64))(__set, __info, __timeout); })
#endif /* ... */
#endif /* __USE_TIME64 */
#endif /* __USE_POSIX199309 */
#endif /* __USE_POSIX */

#ifdef __USE_KOS
__CDECLARE_OPT(__ATTR_NONNULL((3)),int,__NOTHROW_NCX,sigqueueinfo,(__pid_t __tgid, __signo_t __signo, siginfo_t const *__uinfo),(__tgid,__signo,__uinfo))
__CDECLARE_OPT(__ATTR_NONNULL((4)),int,__NOTHROW_NCX,tgsigqueueinfo,(__pid_t __tgid, __pid_t __tid, __signo_t __signo, siginfo_t const *__uinfo),(__tgid,__tid,__signo,__uinfo))
#endif /* __USE_KOS */

#if defined(__USE_MISC) || defined(__USE_XOPEN_EXTENDED)
__CDECLARE_OPT(,int,__NOTHROW_NCX,killpg,(__pid_t __pgrp, __signo_t __signo),(__pgrp,__signo))
#endif /* __USE_MISC || __USE_XOPEN_EXTENDED */

#ifdef __USE_XOPEN2K8
__CDECLARE_VOID_OPT(,__NOTHROW_NCX,psignal,(__signo_t __signo, char const *__s),(__signo,__s))
__CDECLARE_VOID_OPT(__ATTR_NONNULL((1)),__NOTHROW_NCX,psiginfo,(siginfo_t const *__pinfo, char const *__s),(__pinfo,__s))
#endif /* __USE_XOPEN2K8 */

#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_XOPEN2K8)
__CDECLARE_OPT(,int,__NOTHROW_NCX,siginterrupt,(__signo_t __signo, __STDC_INT_AS_UINT_T __interrupt),(__signo,__interrupt))
__CDECLARE_OPT(,int,__NOTHROW_NCX,sigstack,(struct sigstack *__ss, struct sigstack *__oss),(__ss,__oss))
__CDECLARE_OPT(,int,__NOTHROW_NCX,sigaltstack,(struct sigaltstack const *__ss, struct sigaltstack *__oss),(__ss,__oss))
#endif /* __USE_XOPEN_EXTENDED || __USE_XOPEN2K8 */

#ifdef __USE_XOPEN_EXTENDED
__CDECLARE_OPT(,int,__NOTHROW_NCX,sighold,(__signo_t __signo),(__signo))
__CDECLARE_OPT(,int,__NOTHROW_NCX,sigrelse,(__signo_t __signo),(__signo))
__CDECLARE_OPT(,int,__NOTHROW_NCX,sigignore,(__signo_t __signo),(__signo))
__CDECLARE_OPT(,__sighandler_t,__NOTHROW_NCX,sigset,(__signo_t __signo, __sighandler_t __disp),(__signo,__disp))
#endif /* __USE_XOPEN_EXTENDED */

#ifdef __CRT_HAVE___libc_current_sigrtmin
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__signo_t,__NOTHROW_NCX,__libc_current_sigrtmin,(void),())
#else /* __CRT_HAVE___libc_current_sigrtmin */
#include <asm/os/signal.h>
#ifdef __SIGRTMIN
#include <libc/local/signal/__libc_current_sigrtmin.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(__libc_current_sigrtmin, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __signo_t __NOTHROW_NCX(__LIBCCALL __libc_current_sigrtmin)(void) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__libc_current_sigrtmin))(); })
#endif /* __SIGRTMIN */
#endif /* !__CRT_HAVE___libc_current_sigrtmin */
#ifdef __CRT_HAVE___libc_current_sigrtmax
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__signo_t,__NOTHROW_NCX,__libc_current_sigrtmax,(void),())
#else /* __CRT_HAVE___libc_current_sigrtmax */
#include <asm/os/signal.h>
#ifdef __SIGRTMAX
#include <libc/local/signal/__libc_current_sigrtmax.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(__libc_current_sigrtmax, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __signo_t __NOTHROW_NCX(__LIBCCALL __libc_current_sigrtmax)(void) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__libc_current_sigrtmax))(); })
#endif /* __SIGRTMAX */
#endif /* !__CRT_HAVE___libc_current_sigrtmax */

#if defined(__USE_POSIX199506) || defined(__USE_UNIX98)
#ifndef __pthread_sigmask_defined
#define __pthread_sigmask_defined 1
#ifdef __CRT_HAVE_pthread_sigmask
__CDECLARE(,int,__NOTHROW_NCX,pthread_sigmask,(__STDC_INT_AS_UINT_T __how, struct __sigset_struct const *__newmask, struct __sigset_struct *__oldmask),(__how,__newmask,__oldmask))
#else /* __CRT_HAVE_pthread_sigmask */
#undef __pthread_sigmask_defined
#endif /* !__CRT_HAVE_pthread_sigmask */
#endif /* !__pthread_sigmask_defined */
#ifndef __pthread_kill_defined
#define __pthread_kill_defined 1
#ifdef __CRT_HAVE_pthread_kill
__CDECLARE(,int,__NOTHROW_NCX,pthread_kill,(__pthread_t __threadid, __signo_t __signo),(__threadid,__signo))
#else /* __CRT_HAVE_pthread_kill */
#undef __pthread_kill_defined
#endif /* !__CRT_HAVE_pthread_kill */
#endif /* !__pthread_kill_defined */
#ifdef __USE_GNU
#ifndef __pthread_sigqueue_defined
#define __pthread_sigqueue_defined 1
#ifdef __CRT_HAVE_pthread_sigqueue
__CDECLARE(,int,__NOTHROW_NCX,pthread_sigqueue,(__pthread_t __threadid, __signo_t __signo, union sigval const __value),(__threadid,__signo,__value))
#else /* __CRT_HAVE_pthread_sigqueue */
#undef __pthread_sigqueue_defined
#endif /* !__CRT_HAVE_pthread_sigqueue */
#endif /* !__pthread_sigqueue_defined */
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
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,__sigemptyset,(struct __sigset_struct *__set),sigemptyset,(__set))
#else /* __CRT_HAVE_sigemptyset */
#include <libc/local/signal/sigemptyset.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL __sigemptyset)(struct __sigset_struct *__set) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sigemptyset))(__set); }
#endif /* !__CRT_HAVE_sigemptyset */
#ifdef __CRT_HAVE_sigfillset
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,__sigfillset,(struct __sigset_struct *__set),sigfillset,(__set))
#else /* __CRT_HAVE_sigfillset */
#include <libc/local/signal/sigfillset.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL __sigfillset)(struct __sigset_struct *__set) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sigfillset))(__set); }
#endif /* !__CRT_HAVE_sigfillset */
#ifdef __USE_GNU
#ifdef __CRT_HAVE_sigisemptyset
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,__sigisemptyset,(struct __sigset_struct const *__restrict __set),sigisemptyset,(__set))
#else /* __CRT_HAVE_sigisemptyset */
#include <libc/local/signal/sigisemptyset.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL __sigisemptyset)(struct __sigset_struct const *__restrict __set) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sigisemptyset))(__set); }
#endif /* !__CRT_HAVE_sigisemptyset */
#ifdef __CRT_HAVE_sigandset
__CREDIRECT(__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_NCX,__sigandset,(struct __sigset_struct *__set, struct __sigset_struct const *__left, struct __sigset_struct const *__right),sigandset,(__set,__left,__right))
#else /* __CRT_HAVE_sigandset */
#include <libc/local/signal/sigandset.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2, 3)) int __NOTHROW_NCX(__LIBCCALL __sigandset)(struct __sigset_struct *__set, struct __sigset_struct const *__left, struct __sigset_struct const *__right) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sigandset))(__set, __left, __right); }
#endif /* !__CRT_HAVE_sigandset */
#ifdef __CRT_HAVE_sigorset
__CREDIRECT(__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_NCX,__sigorset,(struct __sigset_struct *__set, struct __sigset_struct const *__left, struct __sigset_struct const *__right),sigorset,(__set,__left,__right))
#else /* __CRT_HAVE_sigorset */
#include <libc/local/signal/sigorset.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2, 3)) int __NOTHROW_NCX(__LIBCCALL __sigorset)(struct __sigset_struct *__set, struct __sigset_struct const *__left, struct __sigset_struct const *__right) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sigorset))(__set, __left, __right); }
#endif /* !__CRT_HAVE_sigorset */
#endif /* __USE_GNU */
#ifdef __CRT_HAVE_sigismember
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,__sigismember,(struct __sigset_struct const *__set, __signo_t __signo),sigismember,(__set,__signo))
#elif defined(__CRT_HAVE___sigismember)
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,__sigismember,(struct __sigset_struct const *__set, __signo_t __signo),(__set,__signo))
#else /* ... */
#include <libc/local/signal/sigismember.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL __sigismember)(struct __sigset_struct const *__set, __signo_t __signo) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sigismember))(__set, __signo); }
#endif /* !... */
#ifdef __CRT_HAVE_sigaddset
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,__sigaddset,(struct __sigset_struct *__set, __signo_t __signo),sigaddset,(__set,__signo))
#elif defined(__CRT_HAVE___sigaddset)
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,__sigaddset,(struct __sigset_struct *__set, __signo_t __signo),(__set,__signo))
#else /* ... */
#include <libc/local/signal/sigaddset.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL __sigaddset)(struct __sigset_struct *__set, __signo_t __signo) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sigaddset))(__set, __signo); }
#endif /* !... */
#ifdef __CRT_HAVE_sigdelset
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,__sigdelset,(struct __sigset_struct *__set, __signo_t __signo),sigdelset,(__set,__signo))
#elif defined(__CRT_HAVE___sigdelset)
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,__sigdelset,(struct __sigset_struct *__set, __signo_t __signo),(__set,__signo))
#else /* ... */
#include <libc/local/signal/sigdelset.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL __sigdelset)(struct __sigset_struct *__set, __signo_t __signo) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sigdelset))(__set, __signo); }
#endif /* !... */
/* These appear in glibc under these names, however these names collide with
 * some escapes in a couple of places, so only define them when we're supposed
 * to emulate glibc as closely as possible. */
#ifdef __USE_GLIBC
#undef __sigmask
#undef __sigword
/* Return the mask or index for a specific signal `sig' within some sigset. */
#define __sigmask(sig) __sigset_mask(sig)
#define __sigword(sig) __sigset_word(sig)
#endif /* __USE_GLIBC */

#endif /* __CC__ */

__SYSDECL_END

#ifdef __CXX_SYSTEM_HEADER
#define _CXX_STDONLY_CSIGNAL 1
#undef _SIGNAL_H
#endif /* __CXX_SYSTEM_HEADER */
#endif /* !_CXX_STDONLY_CSIGNAL */
#endif /* !_SIGNAL_H */
