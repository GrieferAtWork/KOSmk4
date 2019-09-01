/* Copyright (c) 2019 Griefer@Work                                            *
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
#ifndef _BITS_SIGNUM_VALUES_H
#define _BITS_SIGNUM_VALUES_H 1

#include <__stdinc.h>

/* Fake signal functions. */
#define __SIG_ERR  (__CCAST(__sighandler_t)-1) /* Error return. */
#define __SIG_DFL  (__CCAST(__sighandler_t)0)  /* Default action. */
#define __SIG_IGN  (__CCAST(__sighandler_t)1)  /* Ignore signal. */
#define __SIG_HOLD (__CCAST(__sighandler_t)2)  /* Add signal to hold mask. */

/* Signals. */
#define __SIGHUP    1         /* Hangup (POSIX). */
#define __SIGINT    2         /* Interrupt (ANSI). */
#define __SIGQUIT   3         /* Quit (POSIX). */
#define __SIGILL    4         /* Illegal instruction (ANSI). */
#define __SIGTRAP   5         /* Trace trap (POSIX). */
#define __SIGABRT   6         /* Abort (ANSI). */
#define __SIGIOT    6         /* IOT trap (4.2 BSD). */
#define __SIGBUS    7         /* BUS error (4.2 BSD). */
#define __SIGFPE    8         /* Floating-point exception (ANSI). */
#define __SIGKILL   9         /* Kill, unblockable (POSIX). */
#define __SIGUSR1   10        /* User-defined signal 1 (POSIX). */
#define __SIGSEGV   11        /* Segmentation violation (ANSI). */
#define __SIGUSR2   12        /* User-defined signal 2 (POSIX). */
#define __SIGPIPE   13        /* Broken pipe (POSIX). */
#define __SIGALRM   14        /* Alarm clock (POSIX). */
#define __SIGTERM   15        /* Termination (ANSI). */
#define __SIGSTKFLT 16        /* Stack fault. */
#define __SIGCHLD   17        /* Child status has changed (POSIX). */
#define __SIGCLD    __SIGCHLD /* Same as SIGCHLD (System V). */
#define __SIGCONT   18        /* Continue (POSIX). */
#define __SIGSTOP   19        /* Stop, unblockable (POSIX). */
#define __SIGTSTP   20        /* Keyboard stop (POSIX). */
#define __SIGTTIN   21        /* Background read from tty (POSIX). */
#define __SIGTTOU   22        /* Background write to tty (POSIX). */
#define __SIGURG    23        /* Urgent condition on socket (4.2 BSD). */
#define __SIGXCPU   24        /* CPU limit exceeded (4.2 BSD). */
#define __SIGXFSZ   25        /* File size limit exceeded (4.2 BSD). */
#define __SIGVTALRM 26        /* Virtual alarm clock (4.2 BSD). */
#define __SIGPROF   27        /* Profiling alarm clock (4.2 BSD). */
#define __SIGWINCH  28        /* Window size change (4.3 BSD, Sun). */
#define __SIGIO     29        /* I/O now possible (4.2 BSD). */
#define __SIGPOLL   __SIGIO   /* Pollable event occurred (System V). */
#define __SIGPWR    30        /* Power failure restart (System V). */
#define __SIGSYS    31        /* Bad system call. */
#define __NSIG      65        /* Biggest signal number + 1 (including real-time signals). */

/* These are the hard limits of the kernel.
 * These values should not be used directly at user level. */
#define __SIGRTMIN  32
#define __SIGRTMAX  64


#endif /* !_BITS_SIGNUM_VALUES_H */
