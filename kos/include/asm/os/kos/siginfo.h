/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _ASM_OS_KOS_SIGINFO_H
#define _ASM_OS_KOS_SIGINFO_H 1

/* NOTE: After changing the IDs/comments in this file, you must re-run:
 * $ deemon -F kos/src/libc/magic/signal.c */

#include <__stdinc.h>

#include <hybrid/host.h>

/************************************************************************/
/* KOS/LINUX                                                            */
/************************************************************************/

/* Values for `si_code'. Positive values are reserved for kernel-generated signals. */
#define __SI_ASYNCNL  (-60) /* Sent by asynch name lookup completion. */
#define __SI_DETHREAD (-7)  /* Sent by `execve(2)' killing secondary threads. */
#define __SI_TKILL    (-6)  /* Sent by tkill. */
#define __SI_SIGIO    (-5)  /* Sent by queued SIGIO. */
#define __SI_ASYNCIO  (-4)  /* Sent by AIO completion. */
#define __SI_MESGQ    (-3)  /* Sent by real time mesq state change. */
#define __SI_TIMER    (-2)  /* Sent by timer expiration. */
#define __SI_QUEUE    (-1)  /* Sent by sigqueue. */
#define __SI_USER     0     /* Sent by kill, sigsend. */
#define __SI_KERNEL   0x80  /* Send by kernel. */

/* `si_code' values for SIGILL signal. */
#define __ILL_ILLOPC   1  /* Illegal opcode. */
#define __ILL_ILLOPN   2  /* Illegal operand. */
#define __ILL_ILLADR   3  /* Illegal addressing mode. */
#define __ILL_ILLTRP   4  /* Illegal trap. */
#define __ILL_PRVOPC   5  /* Privileged opcode. */
#define __ILL_PRVREG   6  /* Privileged register. */
#define __ILL_COPROC   7  /* Coprocessor error. */
#define __ILL_BADSTK   8  /* Internal stack error. */
#define __ILL_BADIADDR 9  /* ??? */
#define __ILL_BREAK    10 /* ??? */
#define __ILL_BNDMOD   11 /* ??? */
#define __NSIGILL      11 /* Number of `ILL_*' codes. */

/* `si_code' values for SIGFPE signal. */
#define __FPE_INTDIV   1  /* Integer divide by zero. */
#define __FPE_INTOVF   2  /* Integer overflow. */
#define __FPE_FLTDIV   3  /* Floating point divide by zero. */
#define __FPE_FLTOVF   4  /* Floating point overflow. */
#define __FPE_FLTUND   5  /* Floating point underflow. */
#define __FPE_FLTRES   6  /* Floating point inexact result. */
#define __FPE_FLTINV   7  /* Floating point invalid operation. */
#define __FPE_FLTSUB   8  /* Subscript out of range. */
#define __FPE_DECOVF   9  /* ??? */
#define __FPE_DECDIV   10 /* ??? */
#define __FPE_DECERR   11 /* ??? */
#define __FPE_INVASC   12 /* ??? */
#define __FPE_INVDEC   13 /* ??? */
#define __FPE_FLTUNK   14 /* ??? */
#define __FPE_CONDTRAP 15 /* ??? */
#define __NSIGFPE      15 /* Number of `FPE_*' codes. */

/* `si_code' values for SIGSEGV signal. */
#define __SEGV_MAPERR 1 /* Address not mapped to object. */
#define __SEGV_ACCERR 2 /* Invalid permissions for mapped object. */
#define __SEGV_BNDERR 3 /* ??? */
#ifdef __ia64__
#define __SEGV_PSTKOVF 4 /* ??? */
#else /* __ia64__ */
#define __SEGV_PKUERR 4 /* ??? */
#endif /* !__ia64__ */
#define __SEGV_ACCADI  5 /* ??? */
#define __SEGV_ADIDERR 6 /* ??? */
#define __SEGV_ADIPERR 7 /* ??? */
#define __SEGV_MTEAERR 8 /* ??? */
#define __SEGV_MTESERR 9 /* ??? */
#define __NSIGSEGV     9 /* Number of `SEGV_*' codes. */


/* `si_code' values for SIGBUS signal. */
#define __BUS_ADRALN    1 /* Invalid address alignment. */
#define __BUS_ADRERR    2 /* Non-existent physical address. */
#define __BUS_OBJERR    3 /* Object specific hardware error. */
#define __BUS_MCEERR_AR 4 /* Hardware memory error: action required. */
#define __BUS_MCEERR_AO 5 /* Hardware memory error: action optional. */
#define __NSIGBUS       5 /* Number of `BUS_*' codes. */

/* `si_code' values for SIGTRAP signal. */
#define __TRAP_BRKPT  1 /* Process breakpoint. */
#define __TRAP_TRACE  2 /* Process trace trap. */
#define __TRAP_BRANCH 3 /* ??? */
#define __TRAP_HWBKPT 4 /* ??? */
#define __TRAP_UNK    5 /* ??? */
#define __TRAP_PERF   6 /* ??? */
#define __NSIGTRAP    6 /* Number of `TRAP_*' codes. */

/* `si_code' values for SIGCHLD signal. */
#define __CLD_EXITED    1 /* Child has exited. */
#define __CLD_KILLED    2 /* Child was killed. */
#define __CLD_DUMPED    3 /* Child terminated abnormally. */
#define __CLD_TRAPPED   4 /* Traced child has trapped. */
#define __CLD_STOPPED   5 /* Child has stopped. */
#define __CLD_CONTINUED 6 /* Stopped child has continued. */
#define __NSIGCHLD      6 /* Number of `CLD_*' codes. */

/* `si_code' values for SIGPOLL signal. */
#define __POLL_IN  1 /* Data input available. */
#define __POLL_OUT 2 /* Output buffers available. */
#define __POLL_MSG 3 /* Input message available.   */
#define __POLL_ERR 4 /* I/O error. */
#define __POLL_PRI 5 /* High priority input available. */
#define __POLL_HUP 6 /* Device disconnected. */
#define __NSIGPOLL 6 /* Number of `POLL_*' codes. */

/* `si_code' values for SIGSYS signal. */
#define __SYS_SECCOMP       1 /* ???*/
#define __SYS_USER_DISPATCH 2 /* ???*/
#define __NSIGSYS           2 /* Number of `SYS_*' codes. */

/* `si_code' values for SIGEMT signal. */
#define __EMT_TAGOVF 1 /* ??? */
#define __NSIGEMT    1 /* Number of `EMT_*' codes. */

#endif /* !_ASM_OS_KOS_SIGINFO_H */
