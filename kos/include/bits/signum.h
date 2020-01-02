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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _BITS_SIGNUM_H
#define _BITS_SIGNUM_H 1

#include <__stdinc.h>
#include <features.h>

#include <bits/signum-values.h>

__SYSDECL_BEGIN

/* Fake signal functions. */
#ifdef __SIG_ERR
#define SIG_ERR   __SIG_ERR /* Error return. */
#endif /* __SIG_ERR */
#ifdef __SIG_DFL
#define SIG_DFL   __SIG_DFL /* Default action. */
#endif /* __SIG_DFL */
#ifdef __SIG_IGN
#define SIG_IGN   __SIG_IGN /* Ignore signal. */
#endif /* __SIG_IGN */

#ifdef __USE_DOS
#ifdef __SIG_GET
#define SIG_GET   __SIG_GET
#endif /* __SIG_GET */
#ifdef __SIG_SGE
#define SIG_SGE   __SIG_SGE
#endif /* __SIG_SGE */
#ifdef __SIG_ACK
#define SIG_ACK   __SIG_ACK
#endif /* __SIG_ACK */
#endif /* __USE_DOS */

#ifdef __USE_UNIX98
#ifdef __SIG_HOLD
#define SIG_HOLD  __SIG_HOLD
#endif /* __SIG_HOLD */
#endif /* __USE_UNIX98 */


#ifdef __USE_KOS
#ifdef __SIG_TERM
#define SIG_TERM  __SIG_TERM /* Terminate the receiving process. */
#endif /* __SIG_TERM */
#ifdef __SIG_EXIT
#define SIG_EXIT  __SIG_EXIT /* Terminate the receiving thread. */
#endif /* __SIG_EXIT */
#ifdef __SIG_CONT
#define SIG_CONT  __SIG_CONT /* Continue execution. */
#endif /* __SIG_CONT */
#ifdef __SIG_STOP
#define SIG_STOP  __SIG_STOP /* Suspend execution. */
#endif /* __SIG_STOP */
#ifdef __SIG_CORE
#define SIG_CORE  __SIG_CORE /* Create a coredump and terminate. */
#endif /* __SIG_CORE */
#endif /* __USE_KOS */


/* Signals. */
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
#ifdef __SIGCLD
#define SIGCLD    __SIGCLD     /* Same as SIGCHLD (System V). */
#endif /* __SIGCLD */
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
#ifdef __SIGUNUSED
#define SIGUNUSED __SIGUNUSED
#elif defined(__SIGSYS)
#define SIGUNUSED __SIGSYS
#endif
#ifdef __NSIG
#define _NSIG     __NSIG       /* Biggest signal number + 1 (including real-time signals). */
#endif /* __NSIG */

/* These are the hard limits of the kernel.
 * These values should not be used directly at user level. */
#if defined(__SIGRTMIN) && \
  (!defined(__CRT_HAVE___libc_current_sigrtmin) || !defined(__CC__))
#define SIGRTMIN    __SIGRTMIN
#else /* !... */
#define SIGRTMIN   (__libc_current_sigrtmin())
#endif /* ... */
#if defined(__SIGRTMAX) && \
  (!defined(__CRT_HAVE___libc_current_sigrtmax) || !defined(__CC__))
#define SIGRTMAX    __SIGRTMAX
#else /* !... */
#define SIGRTMAX   (__libc_current_sigrtmax())
#endif /* ... */

#ifdef __USE_DOS
/* Define DOS's signal name aliases. */
#ifdef __SIGBREAK
#define SIGBREAK        __SIGBREAK       /* Background read from tty (POSIX). */
#endif /* __SIGBREAK */
#ifdef __SIGABRT_COMPAT
#define SIGABRT_COMPAT  __SIGABRT_COMPAT /* Abort (ANSI). */
#elif defined(__SIGABRT)
#define SIGABRT_COMPAT  __SIGABRT        /* Abort (ANSI). */
#endif
#endif /* __USE_DOS */

__SYSDECL_END

#endif /* !_BITS_SIGNUM_H */
