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
#ifndef _I386_KOS_ASM_SIGNUM_VALUES_H
#define _I386_KOS_ASM_SIGNUM_VALUES_H 1

#include <__stdinc.h>

#if defined(__KOS__) || defined(__linux__)
#include "signum-values-kos.h"

/* Fake signal functions. */
#define __SIG_ERR  __KOS_SIG_ERR  /* Error return. */
#define __SIG_DFL  __KOS_SIG_DFL  /* Default action. */
#define __SIG_IGN  __KOS_SIG_IGN  /* Ignore signal. */
#define __SIG_HOLD __KOS_SIG_HOLD /* Add signal to hold mask. */
#define __SIG_TERM __KOS_SIG_TERM /* Terminate the receiving process. */
#define __SIG_EXIT __KOS_SIG_EXIT /* Terminate the receiving thread. */
#define __SIG_CONT __KOS_SIG_CONT /* Continue execution. */
#define __SIG_STOP __KOS_SIG_STOP /* Suspend execution. */
#define __SIG_CORE __KOS_SIG_CORE /* Create a coredump and terminate. */
#define __SIG_GET  __KOS_SIG_GET  /* Only get the current handler (accepted by `signal(2)') */

/* Signals. */
#define __SIGHUP    __KOS_SIGHUP    /* Hangup (POSIX). */
#define __SIGINT    __KOS_SIGINT    /* Interrupt (ANSI). */
#define __SIGQUIT   __KOS_SIGQUIT   /* Quit (POSIX). */
#define __SIGILL    __KOS_SIGILL    /* Illegal instruction (ANSI). */
#define __SIGTRAP   __KOS_SIGTRAP   /* Trace trap (POSIX). */
#define __SIGABRT   __KOS_SIGABRT   /* Abort (ANSI). */
#define __SIGIOT    __KOS_SIGIOT    /* IOT trap (4.2 BSD). */
#define __SIGBUS    __KOS_SIGBUS    /* BUS error (4.2 BSD). */
#define __SIGFPE    __KOS_SIGFPE    /* Floating-point exception (ANSI). */
#define __SIGKILL   __KOS_SIGKILL   /* Kill, unblockable (POSIX). */
#define __SIGUSR1   __KOS_SIGUSR1   /* User-defined signal 1 (POSIX). */
#define __SIGSEGV   __KOS_SIGSEGV   /* Segmentation violation (ANSI). */
#define __SIGUSR2   __KOS_SIGUSR2   /* User-defined signal 2 (POSIX). */
#define __SIGPIPE   __KOS_SIGPIPE   /* Broken pipe (POSIX). */
#define __SIGALRM   __KOS_SIGALRM   /* Alarm clock (POSIX). */
#define __SIGTERM   __KOS_SIGTERM   /* Termination (ANSI). */
#define __SIGSTKFLT __KOS_SIGSTKFLT /* Stack fault. */
#define __SIGCHLD   __KOS_SIGCHLD   /* Child status has changed (POSIX). */
#define __SIGCLD    __KOS_SIGCLD    /* Same as SIGCHLD (System V). */
#define __SIGCONT   __KOS_SIGCONT   /* Continue (POSIX). */
#define __SIGSTOP   __KOS_SIGSTOP   /* Stop, unblockable (POSIX). */
#define __SIGTSTP   __KOS_SIGTSTP   /* Keyboard stop (POSIX). */
#define __SIGTTIN   __KOS_SIGTTIN   /* Background read from tty (POSIX). */
#define __SIGTTOU   __KOS_SIGTTOU   /* Background write to tty (POSIX). */
#define __SIGURG    __KOS_SIGURG    /* Urgent condition on socket (4.2 BSD). */
#define __SIGXCPU   __KOS_SIGXCPU   /* CPU limit exceeded (4.2 BSD). */
#define __SIGXFSZ   __KOS_SIGXFSZ   /* File size limit exceeded (4.2 BSD). */
#define __SIGVTALRM __KOS_SIGVTALRM /* Virtual alarm clock (4.2 BSD). */
#define __SIGPROF   __KOS_SIGPROF   /* Profiling alarm clock (4.2 BSD). */
#define __SIGWINCH  __KOS_SIGWINCH  /* Window size change (4.3 BSD, Sun). */
#define __SIGIO     __KOS_SIGIO     /* I/O now possible (4.2 BSD). */
#define __SIGPOLL   __KOS_SIGPOLL   /* Pollable event occurred (System V). */
#define __SIGPWR    __KOS_SIGPWR    /* Power failure restart (System V). */
#define __SIGSYS    __KOS_SIGSYS    /* Bad system call. */
#define __NSIG      __KOS_NSIG      /* Biggest signal number + 1 (including real-time signals). */

/* These are the hard limits of the kernel.
 * These values should not be used directly at user level. */
#define __SIGRTMIN  __KOS_SIGRTMIN
#define __SIGRTMAX  __KOS_SIGRTMAX

#else /* __KOS__ || __linux__ */
#include <__crt.h>
#ifdef __CRT_DOS_PRIMARY
#include "signum-values-dos.h"

/* Fake signal functions. */
#define __SIG_ERR  __DOS_SIG_ERR /* Error return. */
#define __SIG_DFL  __DOS_SIG_DFL /* Default action. */
#define __SIG_IGN  __DOS_SIG_IGN /* Ignore signal. */
#define __SIG_GET  __DOS_SIG_GET /* Return current value. */
#define __SIG_SGE  __DOS_SIG_SGE /* Signal gets error. */
#define __SIG_ACK  __DOS_SIG_ACK /* Acknowledge. */

/* Signals. */
#define __SIGINT         __DOS_SIGINT          /* Interrupt (ANSI). */
#define __SIGILL         __DOS_SIGILL          /* Illegal instruction (ANSI). */
#define __SIGABRT_COMPAT __DOS_SIGABRT_COMPAT  /* Abort (ANSI). */
#define __SIGFPE         __DOS_SIGFPE          /* Floating-point exception (ANSI). */
#define __SIGSEGV        __DOS_SIGSEGV         /* Segmentation violation (ANSI). */
#define __SIGTERM        __DOS_SIGTERM         /* Termination (ANSI). */
#define __SIGBREAK       __DOS_SIGBREAK        /* Background read from tty (POSIX). */
#define __SIGABRT        __DOS_SIGABRT         /* Abort (ANSI). */
#define __NSIG           __DOS_NSIG            /* Biggest signal number + 1 (including real-time signals). */

#elif defined(__CRT_CYG_PRIMARY)
#include "signum-values-cyg.h"

/* Fake signal functions. */
#define __SIG_ERR  __CYG_SIG_ERR  /* Error return. */
#define __SIG_DFL  __CYG_SIG_DFL  /* Default action. */
#define __SIG_IGN  __CYG_SIG_IGN  /* Ignore signal. */
#define __SIG_HOLD __CYG_SIG_HOLD /* Add signal to hold mask. */

/* Signals. */
#define __SIGHUP    __CYG_SIGHUP    /* Hangup (POSIX). */
#define __SIGINT    __CYG_SIGINT    /* Interrupt (ANSI). */
#define __SIGQUIT   __CYG_SIGQUIT   /* Quit (POSIX). */
#define __SIGILL    __CYG_SIGILL    /* Illegal instruction (ANSI). */
#define __SIGTRAP   __CYG_SIGTRAP   /* Trace trap (POSIX). */
#define __SIGABRT   __CYG_SIGABRT   /* Abort (ANSI). */
#define __SIGIOT    __CYG_SIGIOT    /* IOT trap (4.2 BSD). */
#define __SIGEMT    __CYG_SIGEMT    /* EMT instruction. */
#define __SIGFPE    __CYG_SIGFPE    /* Floating-point exception (ANSI). */
#define __SIGKILL   __CYG_SIGKILL   /* Kill, unblockable (POSIX). */
#define __SIGBUS    __CYG_SIGBUS    /* BUS error (4.2 BSD). */
#define __SIGSEGV   __CYG_SIGSEGV   /* Segmentation violation (ANSI). */
#define __SIGSYS    __CYG_SIGSYS    /* Bad system call. */
#define __SIGPIPE   __CYG_SIGPIPE   /* Broken pipe (POSIX). */
#define __SIGALRM   __CYG_SIGALRM   /* Alarm clock (POSIX). */
#define __SIGTERM   __CYG_SIGTERM   /* Termination (ANSI). */
#define __SIGURG    __CYG_SIGURG    /* Urgent condition on socket (4.2 BSD). */
#define __SIGSTOP   __CYG_SIGSTOP   /* Stop, unblockable (POSIX). */
#define __SIGTSTP   __CYG_SIGTSTP   /* Keyboard stop (POSIX). */
#define __SIGCONT   __CYG_SIGCONT   /* Continue (POSIX). */
#define __SIGCHLD   __CYG_SIGCHLD   /* Child status has changed (POSIX). */
#define __SIGCLD    __CYG_SIGCLD    /* Same as SIGCHLD (System V). */
#define __SIGTTIN   __CYG_SIGTTIN   /* Background read from tty (POSIX). */
#define __SIGTTOU   __CYG_SIGTTOU   /* Background write to tty (POSIX). */
#define __SIGIO     __CYG_SIGIO     /* I/O now possible (4.2 BSD). */
#define __SIGPOLL   __CYG_SIGPOLL   /* Pollable event occurred (System V). */
#define __SIGXCPU   __CYG_SIGXCPU   /* CPU limit exceeded (4.2 BSD). */
#define __SIGXFSZ   __CYG_SIGXFSZ   /* File size limit exceeded (4.2 BSD). */
#define __SIGVTALRM __CYG_SIGVTALRM /* Virtual alarm clock (4.2 BSD). */
#define __SIGPROF   __CYG_SIGPROF   /* Profiling alarm clock (4.2 BSD). */
#define __SIGWINCH  __CYG_SIGWINCH  /* Window size change (4.3 BSD, Sun). */
#define __SIGLOST   __CYG_SIGLOST   /* Resource lost. */
#define __SIGPWR    __CYG_SIGPWR    /* Power failure restart (System V). */
#define __SIGUSR1   __CYG_SIGUSR1   /* User-defined signal 1 (POSIX). */
#define __SIGUSR2   __CYG_SIGUSR2   /* User-defined signal 2 (POSIX). */
#define __SIGRTMIN  __CYG_SIGRTMIN
#define __SIGRTMAX  __CYG_SIGRTMAX
#define __NSIG      __CYG_NSIG      /* signal 0 implied */

#else /* __CRT_..._PRIMARY */
#include "../../asm/signum-values.h"
#endif /* !__CRT_..._PRIMARY */
#endif /* !__KOS__ && !__linux__ */

#endif /* !_I386_KOS_ASM_SIGNUM_VALUES_H */
