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
/* (#) Portability: Linux (/usr/include/[...]/asm/signal.h) */
#ifndef _ASM_SIGNAL_H
#define _ASM_SIGNAL_H 1

#include <__stdinc.h>

#include <asm-generic/signal-defs.h>
#include <asm/bitsperlong.h>
#include <asm/os/signal.h>
#include <asm/os/sigset.h>
#include <bits/os/sigaction.h>
#include <bits/os/sigstack.h>
#include <linux/types.h>

#if !defined(SA_RESTORER) && defined(__SA_RESTORER)
#define SA_RESTORER __SA_RESTORER /* A custom  signal restore  function (`sa_restorer')  was given.  This
                                   * flag is set by libc, after having filled in the `sa_restorer' field. */
#endif /* !SA_RESTORER && __SA_RESTORER */

#if !defined(MINSIGSTKSZ) && defined(__MINSIGSTKSZ)
#define MINSIGSTKSZ __MINSIGSTKSZ /* Minimum stack size for a signal handler. */
#endif /* !MINSIGSTKSZ && __MINSIGSTKSZ */

#if !defined(SIGSTKSZ) && defined(__SIGSTKSZ)
#define SIGSTKSZ __SIGSTKSZ /* System default stack size. */
#endif /* !SIGSTKSZ && __SIGSTKSZ */


#ifdef __NSIG
#ifndef _NSIG
#define _NSIG __NSIG
#endif /* !_NSIG */
#ifndef _NSIG_BPW
#define _NSIG_BPW __BITS_PER_LONG
#endif /* !_NSIG_BPW */
#ifndef _NSIG_WORDS
#define _NSIG_WORDS (_NSIG / _NSIG_BPW)
#endif /* !_NSIG_WORDS */
#endif /* __NSIG */

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
#ifndef SIGUNUSED
#ifdef __SIGUNUSED
#define SIGUNUSED __SIGUNUSED
#elif defined(__SIGSYS)
#define SIGUNUSED __SIGSYS
#endif /* ... */
#endif /* !SIGUNUSED */

/* These are the hard limits of the kernel.
 * These values should not be used directly at user level. */
#if !defined(SIGRTMIN) && defined(__SIGRTMIN)
#define SIGRTMIN __SIGRTMIN
#endif /* !SIGRTMIN && __SIGRTMIN */
#if !defined(SIGRTMAX) && defined(__SIGRTMAX)
#define SIGRTMAX __SIGRTMAX
#endif /* !SIGRTMAX && __SIGRTMAX */

#ifdef __CC__
__DECL_BEGIN

#ifndef __sigset_t_defined
#define __sigset_t_defined
typedef struct __sigset_struct sigset_t;
#endif /* !__sigset_t_defined */

#ifndef __old_sigset_t_defined
#define __old_sigset_t_defined
typedef __ULONGPTR_TYPE__ old_sigset_t;
#endif /* !__old_sigset_t_defined */

#ifndef __stack_t_defined
#define __stack_t_defined
typedef struct sigaltstack stack_t;
#endif /* !__stack_t_defined */

__DECL_END
#endif /* __CC__ */


#endif /* !_ASM_SIGNAL_H */
