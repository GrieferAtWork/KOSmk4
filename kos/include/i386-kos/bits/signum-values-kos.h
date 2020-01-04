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
#ifndef _I386_KOS_BITS_SIGNUM_VALUES_KOS_H
#define _I386_KOS_BITS_SIGNUM_VALUES_KOS_H 1

#include <__stdinc.h>

/* Fake signal functions. */
#define __KOS_SIG_ERR  (__CCAST(__sighandler_t)-1) /* Error return. */
#define __KOS_SIG_DFL  (__CCAST(__sighandler_t)0)  /* Default action. */
#define __KOS_SIG_IGN  (__CCAST(__sighandler_t)1)  /* Ignore signal. */
#define __KOS_SIG_HOLD (__CCAST(__sighandler_t)2)  /* Add signal to hold mask. */
#define __KOS_SIG_TERM (__CCAST(__sighandler_t)3)  /* Terminate the receiving process. */
#define __KOS_SIG_EXIT (__CCAST(__sighandler_t)4)  /* Terminate the receiving thread. */
#define __KOS_SIG_CONT (__CCAST(__sighandler_t)8)  /* Continue execution. */
#define __KOS_SIG_STOP (__CCAST(__sighandler_t)9)  /* Suspend execution. */
#define __KOS_SIG_CORE (__CCAST(__sighandler_t)10) /* Create a coredump and terminate. */
#define __KOS_SIG_GET  (__CCAST(__sighandler_t)11) /* Only get the current handler (accepted by `signal(2)') */

/* Signals. */
#define __KOS_SIGHUP    1             /* Hangup (POSIX). */
#define __KOS_SIGINT    2             /* Interrupt (ANSI). */
#define __KOS_SIGQUIT   3             /* Quit (POSIX). */
#define __KOS_SIGILL    4             /* Illegal instruction (ANSI). */
#define __KOS_SIGTRAP   5             /* Trace trap (POSIX). */
#define __KOS_SIGABRT   6             /* Abort (ANSI). */
#define __KOS_SIGIOT    __KOS_SIGABRT /* IOT trap (4.2 BSD). */
#define __KOS_SIGBUS    7             /* BUS error (4.2 BSD). */
#define __KOS_SIGFPE    8             /* Floating-point exception (ANSI). */
#define __KOS_SIGKILL   9             /* Kill, unblockable (POSIX). */
#define __KOS_SIGUSR1   10            /* User-defined signal 1 (POSIX). */
#define __KOS_SIGSEGV   11            /* Segmentation violation (ANSI). */
#define __KOS_SIGUSR2   12            /* User-defined signal 2 (POSIX). */
#define __KOS_SIGPIPE   13            /* Broken pipe (POSIX). */
#define __KOS_SIGALRM   14            /* Alarm clock (POSIX). */
#define __KOS_SIGTERM   15            /* Termination (ANSI). */
#define __KOS_SIGSTKFLT 16            /* Stack fault. */
#define __KOS_SIGCHLD   17            /* Child status has changed (POSIX). */
#define __KOS_SIGCLD    __KOS_SIGCHLD /* Same as SIGCHLD (System V). */
#define __KOS_SIGCONT   18            /* Continue (POSIX). */
#define __KOS_SIGSTOP   19            /* Stop, unblockable (POSIX). */
#define __KOS_SIGTSTP   20            /* Keyboard stop (POSIX). */
#define __KOS_SIGTTIN   21            /* Background read from tty (POSIX). */
#define __KOS_SIGTTOU   22            /* Background write to tty (POSIX). */
#define __KOS_SIGURG    23            /* Urgent condition on socket (4.2 BSD). */
#define __KOS_SIGXCPU   24            /* CPU limit exceeded (4.2 BSD). */
#define __KOS_SIGXFSZ   25            /* File size limit exceeded (4.2 BSD). */
#define __KOS_SIGVTALRM 26            /* Virtual alarm clock (4.2 BSD). */
#define __KOS_SIGPROF   27            /* Profiling alarm clock (4.2 BSD). */
#define __KOS_SIGWINCH  28            /* Window size change (4.3 BSD, Sun). */
#define __KOS_SIGIO     29            /* I/O now possible (4.2 BSD). */
#define __KOS_SIGPOLL   __KOS_SIGIO   /* Pollable event occurred (System V). */
#define __KOS_SIGPWR    30            /* Power failure restart (System V). */
#define __KOS_SIGSYS    31            /* Bad system call. */
#define __KOS_NSIG      65            /* Biggest signal number + 1 (including real-time signals). */

/* These are the hard limits of the kernel.
 * These values should not be used directly at user level. */
#define __KOS_SIGRTMIN  32
#define __KOS_SIGRTMAX  64


#endif /* !_I386_KOS_BITS_SIGNUM_VALUES_KOS_H */
