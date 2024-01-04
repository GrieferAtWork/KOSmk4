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
#ifndef _ASM_OS_KOS_SIGNAL_H
#define _ASM_OS_KOS_SIGNAL_H 1

#include <__stdinc.h>
#include <hybrid/typecore.h> /* __UINT32_C */

/************************************************************************/
/* KOS/LINUX                                                            */
/************************************************************************/

/* Bits in `sa_flags'. */
#define __SA_NOCLDSTOP      __UINT32_C(0x00000001) /* Don't send SIGCHLD when children stop (Ignored for anything other than SIGCLD). */
#define __SA_NOCLDWAIT      __UINT32_C(0x00000002) /* Don't create zombie on child death (Ignored for anything other than SIGCLD). */
#define __SA_SIGINFO        __UINT32_C(0x00000004) /* Invoke signal-catching function with three arguments instead of one. */
#define __SA_UNSUPPORTED    __UINT32_C(0x00000400) /* ??? */
#define __SA_EXPOSE_TAGBITS __UINT32_C(0x00000800) /* ??? */
#define __SA_RESTORER       __UINT32_C(0x04000000) /* A custom  signal restore  function (`sa_restorer')  was given.  This
                                                    * flag is set by libc, after having filled in the `sa_restorer' field. */
#define __SA_ONSTACK        __UINT32_C(0x08000000) /* Execute the handler on sigaltstack. */
#define __SA_RESTART        __UINT32_C(0x10000000) /* Restart restartable syscall on signal return. */
#define __SA_INTERRUPT      __UINT32_C(0x20000000) /* Historical no-op. */
#define __SA_NODEFER        __UINT32_C(0x40000000) /* Don't automatically block the signal when its handler is being executed. */
#define __SA_RESETHAND      __UINT32_C(0x80000000) /* Reset to SIG_DFL on entry to handler. */


/* Values for the HOW argument to `sigprocmask'. */
#define __SIG_BLOCK   0 /* Block signals. */
#define __SIG_UNBLOCK 1 /* Unblock signals. */
#define __SIG_SETMASK 2 /* Set the set of blocked signals. */


/* Fake signal functions. */
#define __SIG_ERR  (-1) /* Error return. */
#define __SIG_DFL  0    /* Default action. */
#define __SIG_IGN  1    /* Ignore signal. */
#define __SIG_HOLD 2    /* Add signal to hold mask. */
#ifdef __KOS__
#define __SIG_TERM 3  /* Terminate the receiving process. */
#define __SIG_EXIT 4  /* Terminate the receiving thread. */
/*      __SIG_     5   */
/*      __SIG_     6   */
/*      __SIG_     7   */
#define __SIG_CONT 8  /* Continue execution. */
#define __SIG_STOP 9  /* Suspend execution. */
#define __SIG_CORE 10 /* Create a coredump and terminate. */
#define __SIG_GET  11 /* Only get the current handler (accepted by `signal(2)') */
#endif /* __KOS__ */

/* Signals. */
#define __SIGHUP    1         /* Hangup (POSIX). */
#define __SIGINT    2         /* Interrupt (ANSI). */
#define __SIGQUIT   3         /* Quit (POSIX). */
#define __SIGILL    4         /* Illegal instruction (ANSI). */
#define __SIGTRAP   5         /* Trace/breakpoint trap (POSIX). */
#define __SIGABRT   6         /* Aborted (ANSI). */
#define __SIGIOT    __SIGABRT /* IOT trap (4.2 BSD). */
#define __SIGBUS    7         /* Bus error (4.2 BSD). */
#define __SIGFPE    8         /* Floating point exception (ANSI). */
#define __SIGKILL   9         /* Killed -- Kill, unblockable (POSIX). */
#define __SIGUSR1   10        /* User defined signal 1 (POSIX). */
#define __SIGSEGV   11        /* Segmentation violation (ANSI). */
#define __SIGUSR2   12        /* User defined signal 2 (POSIX). */
#define __SIGPIPE   13        /* Broken pipe (POSIX). */
#define __SIGALRM   14        /* Alarm clock (POSIX). */
#define __SIGTERM   15        /* Terminated (ANSI). */
#define __SIGSTKFLT 16        /* Stack fault. */
#define __SIGCHLD   17        /* Child exited (POSIX). */
#define __SIGCLD    __SIGCHLD /* Child exited (System V). */
#define __SIGCONT   18        /* Continued (POSIX). */
#define __SIGSTOP   19        /* Stopped (signal) -- Stop, unblockable (POSIX). */
#define __SIGTSTP   20        /* Stopped -- Keyboard stop (POSIX). */
#define __SIGTTIN   21        /* Stopped (tty input) -- Background read from tty (POSIX). */
#define __SIGTTOU   22        /* Stopped (tty output) -- Background write to tty (POSIX). */
#define __SIGURG    23        /* Urgent I/O condition (4.2 BSD). */
#define __SIGXCPU   24        /* CPU time limit exceeded (4.2 BSD). */
#define __SIGXFSZ   25        /* File size limit exceeded (4.2 BSD). */
#define __SIGVTALRM 26        /* Virtual timer expired (4.2 BSD). */
#define __SIGPROF   27        /* Profiling timer expired (4.2 BSD). */
#define __SIGWINCH  28        /* Window changed (4.3 BSD, Sun). */
#define __SIGIO     29        /* I/O possible (4.2 BSD). */
#define __SIGPOLL   __SIGIO   /* Pollable event occurred (System V). */
#define __SIGPWR    30        /* Power failure (System V). */
#define __SIGSYS    31        /* Bad system call. */
#define __NSIG      65        /* Biggest signal number + 1 (including real-time signals). */
#ifdef __KOS__
/* NOTE: I  would have loved to assign a  dedicated signal number for SIGRPC, but
 *       sadly KOS RPCs are kos-specific (who would'a thunk?), and signal numbers
 *       must be kept such that binary linux compatibility is maintained, meaning
 *       I can't add any new ones :(
 * `SIGURG' was chosen as the aliased signal for the simple reason that this
 * signal  has a default  disposition of `SIG_IGN'  (not that signal actions
 * matter for RPC signals, but I  feel like a default `SIG_IGN'  disposition
 * is the best fit for RPCs) */
#define __SIGRPC    __SIGURG  /* Default signal number used for <kos/rpc.h> */
#endif /* __KOS__ */


/* These are the hard limits of the kernel.
 * These values should not be used directly at user level. */
#define __SIGRTMIN 32
#define __SIGRTMAX 64


#endif /* !_ASM_OS_KOS_SIGNAL_H */
