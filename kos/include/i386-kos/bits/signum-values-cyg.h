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
#ifndef _I386_KOS_BITS_SIGNUM_VALUES_CYG_H
#define _I386_KOS_BITS_SIGNUM_VALUES_CYG_H 1

#include <__stdinc.h>
#include <hybrid/typecore.h>

/* Fake signal functions. */
#define __CYG_SIG_ERR  (__CCAST(__sighandler_t)-1) /* Error return. */
#define __CYG_SIG_DFL  (__CCAST(__sighandler_t)0)  /* Default action. */
#define __CYG_SIG_IGN  (__CCAST(__sighandler_t)1)  /* Ignore signal. */
#define __CYG_SIG_HOLD (__CCAST(__sighandler_t)2)  /* Add signal to hold mask. */

/* Signals. */
#define __CYG_SIGHUP    1             /* Hangup (POSIX). */
#define __CYG_SIGINT    2             /* Interrupt (ANSI). */
#define __CYG_SIGQUIT   3             /* Quit (POSIX). */
#define __CYG_SIGILL    4             /* Illegal instruction (ANSI). */
#define __CYG_SIGTRAP   5             /* Trace trap (POSIX). */
#define __CYG_SIGABRT   6             /* Abort (ANSI). */
#define __CYG_SIGIOT    __CYG_SIGABRT /* IOT trap (4.2 BSD). */
#define __CYG_SIGEMT    7             /* EMT instruction. */
#define __CYG_SIGFPE    8             /* Floating-point exception (ANSI). */
#define __CYG_SIGKILL   9             /* Kill, unblockable (POSIX). */
#define __CYG_SIGBUS    10            /* BUS error (4.2 BSD). */
#define __CYG_SIGSEGV   11            /* Segmentation violation (ANSI). */
#define __CYG_SIGSYS    12            /* Bad system call. */
#define __CYG_SIGPIPE   13            /* Broken pipe (POSIX). */
#define __CYG_SIGALRM   14            /* Alarm clock (POSIX). */
#define __CYG_SIGTERM   15            /* Termination (ANSI). */
#define __CYG_SIGURG    16            /* Urgent condition on socket (4.2 BSD). */
#define __CYG_SIGSTOP   17            /* Stop, unblockable (POSIX). */
#define __CYG_SIGTSTP   18            /* Keyboard stop (POSIX). */
#define __CYG_SIGCONT   19            /* Continue (POSIX). */
#define __CYG_SIGCHLD   20            /* Child status has changed (POSIX). */
#define __CYG_SIGCLD    __CYG_SIGCHLD /* Same as SIGCHLD (System V). */
#define __CYG_SIGTTIN   21            /* Background read from tty (POSIX). */
#define __CYG_SIGTTOU   22            /* Background write to tty (POSIX). */
#define __CYG_SIGIO     23            /* I/O now possible (4.2 BSD). */
#define __CYG_SIGPOLL   __CYG_SIGIO   /* Pollable event occurred (System V). */
#define __CYG_SIGXCPU   24            /* CPU limit exceeded (4.2 BSD). */
#define __CYG_SIGXFSZ   25            /* File size limit exceeded (4.2 BSD). */
#define __CYG_SIGVTALRM 26            /* Virtual alarm clock (4.2 BSD). */
#define __CYG_SIGPROF   27            /* Profiling alarm clock (4.2 BSD). */
#define __CYG_SIGWINCH  28            /* Window size change (4.3 BSD, Sun). */
#define __CYG_SIGLOST   29            /* Resource lost. */
#define __CYG_SIGPWR    __CYG_SIGLOST /* Power failure restart (System V). */
#define __CYG_SIGUSR1   30            /* User-defined signal 1 (POSIX). */
#define __CYG_SIGUSR2   31            /* User-defined signal 2 (POSIX). */
#define __CYG_SIGRTMIN  32
#if __SIZEOF_POINTER__ > 4
#define __CYG_SIGRTMAX  64
#define __CYG_NSIG      65      /* signal 0 implied */
#else
#define __CYG_SIGRTMAX  32
#define __CYG_NSIG      33      /* signal 0 implied */
#endif

#endif /* !_I386_KOS_BITS_SIGNUM_VALUES_CYG_H */
