/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _ASM_OS_CYGWIN_SIGNAL_H
#define _ASM_OS_CYGWIN_SIGNAL_H 1

#include <__stdinc.h>

#include <hybrid/typecore.h>


/************************************************************************/
/* CYGWIN                                                               */
/************************************************************************/

/* Bits in `sa_flags'. */
#define __SA_NOCLDSTOP __UINT32_C(0x00000001) /* Don't send SIGCHLD when children stop (Ignored for anything other than SIGCLD). */
#define __SA_NOCLDWAIT __UINT32_C(0x00000002) /* Don't create zombie on child death (Ignored for anything other than SIGCLD). */
#define __SA_SIGINFO   __UINT32_C(0x00000004) /* Invoke signal-catching function with three arguments instead of one. */
#define __SA_RESTORER  __UINT32_C(0x04000000) /* A custom  signal restore  function (`sa_restorer')  was given.  This
                                               * flag is set by libc, after having filled in the `sa_restorer' field. */
#define __SA_ONSTACK   __UINT32_C(0x20000000) /* Execute the handler on sigaltstack. */
#define __SA_RESTART   __UINT32_C(0x10000000) /* Restart restartable syscall on signal return. */
#define __SA_NODEFER   __UINT32_C(0x40000000) /* Don't automatically block the signal when its handler is being executed. */
#define __SA_RESETHAND __UINT32_C(0x80000000) /* Reset to SIG_DFL on entry to handler. */
#define __SA_INTERRUPT __UINT32_C(0x20000000) /* Historical no-op. */

/* Values for the HOW argument to `sigprocmask'. */
#define __SIG_BLOCK   0 /* Block signals. */
#define __SIG_UNBLOCK 1 /* Unblock signals. */
#define __SIG_SETMASK 2 /* Set the set of blocked signals. */


/* Fake signal functions. */
#define __SIG_ERR  (-1) /* Error return. */
#define __SIG_DFL  0    /* Default action. */
#define __SIG_IGN  1    /* Ignore signal. */
#define __SIG_HOLD 2    /* Add signal to hold mask. */

/* Signals. */
#define __SIGHUP    1         /* Hangup (POSIX). */
#define __SIGINT    2         /* Interrupt (ANSI). */
#define __SIGQUIT   3         /* Quit (POSIX). */
#define __SIGILL    4         /* Illegal instruction (ANSI). */
#define __SIGTRAP   5         /* Trace trap (POSIX). */
#define __SIGABRT   6         /* Abort (ANSI). */
#define __SIGIOT    __SIGABRT /* IOT trap (4.2 BSD). */
#define __SIGEMT    7         /* EMT instruction. */
#define __SIGFPE    8         /* Floating-point exception (ANSI). */
#define __SIGKILL   9         /* Kill, unblockable (POSIX). */
#define __SIGBUS    10        /* BUS error (4.2 BSD). */
#define __SIGSEGV   11        /* Segmentation violation (ANSI). */
#define __SIGSYS    12        /* Bad system call. */
#define __SIGPIPE   13        /* Broken pipe (POSIX). */
#define __SIGALRM   14        /* Alarm clock (POSIX). */
#define __SIGTERM   15        /* Termination (ANSI). */
#define __SIGURG    16        /* Urgent condition on socket (4.2 BSD). */
#define __SIGSTOP   17        /* Stop, unblockable (POSIX). */
#define __SIGTSTP   18        /* Keyboard stop (POSIX). */
#define __SIGCONT   19        /* Continue (POSIX). */
#define __SIGCHLD   20        /* Child status has changed (POSIX). */
#define __SIGCLD    __SIGCHLD /* Same as SIGCHLD (System V). */
#define __SIGTTIN   21        /* Background read from tty (POSIX). */
#define __SIGTTOU   22        /* Background write to tty (POSIX). */
#define __SIGIO     23        /* I/O now possible (4.2 BSD). */
#define __SIGPOLL   __SIGIO   /* Pollable event occurred (System V). */
#define __SIGXCPU   24        /* CPU limit exceeded (4.2 BSD). */
#define __SIGXFSZ   25        /* File size limit exceeded (4.2 BSD). */
#define __SIGVTALRM 26        /* Virtual alarm clock (4.2 BSD). */
#define __SIGPROF   27        /* Profiling alarm clock (4.2 BSD). */
#define __SIGWINCH  28        /* Window size change (4.3 BSD, Sun). */
#define __SIGLOST   29        /* Resource lost. */
#define __SIGPWR    __SIGLOST /* Power failure restart (System V). */
#define __SIGUSR1   30        /* User-defined signal 1 (POSIX). */
#define __SIGUSR2   31        /* User-defined signal 2 (POSIX). */
#define __SIGRTMIN  32
#if __SIZEOF_POINTER__ > 4
#define __SIGRTMAX  64
#define __NSIG      65
#else /* __SIZEOF_POINTER__ > 4 */
#define __SIGRTMAX  32
#define __NSIG      33
#endif /* __SIZEOF_POINTER__ <= 4 */

#endif /* !_ASM_OS_CYGWIN_SIGNAL_H */
