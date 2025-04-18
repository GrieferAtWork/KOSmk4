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
/* (#) Portability: Linux (/usr/include/[...]/asm/siginfo.h) */
/*!always_includes <asm/os/sigevent.h>*/
/*!always_includes <asm/os/siginfo.h>*/
/*!always_includes <bits/os/sigevent.h>*/
/*!always_includes <bits/os/siginfo.h>*/
/*!always_includes <bits/os/sigval.h>*/
#ifndef _ASM_SIGINFO_H
#define _ASM_SIGINFO_H 1

#include <__stdinc.h>

#include <asm/os/sigevent.h>
#include <asm/os/siginfo.h>
#include <bits/os/sigevent.h>
#include <bits/os/siginfo.h>
#include <bits/os/sigval.h>
#include <linux/types.h>

#if !defined(SI_MAX_SIZE) && defined(__SI_MAX_SIZE)
#define SI_MAX_SIZE __SI_MAX_SIZE /* ... */
#endif /* !SI_MAX_SIZE && __SI_MAX_SIZE */

/* Values for `si_code'. Positive values are reserved for kernel-generated signals. */
#if !defined(SI_ASYNCNL) && defined(__SI_ASYNCNL)
#define SI_ASYNCNL __SI_ASYNCNL /* Sent by asynch name lookup completion. */
#endif /* !SI_ASYNCNL && __SI_ASYNCNL */
#if !defined(SI_DETHREAD) && defined(__SI_DETHREAD)
#define SI_DETHREAD __SI_DETHREAD /* Sent by `execve(2)' killing secondary threads. */
#endif /* !SI_DETHREAD && __SI_DETHREAD */
#if !defined(SI_TKILL) && defined(__SI_TKILL)
#define SI_TKILL   __SI_TKILL   /* Sent by tkill. */
#endif /* !SI_TKILL && __SI_TKILL */
#if !defined(SI_SIGIO) && defined(__SI_SIGIO)
#define SI_SIGIO   __SI_SIGIO   /* Sent by queued SIGIO. */
#endif /* !SI_SIGIO && __SI_SIGIO */
#if !defined(SI_ASYNCIO) && defined(__SI_ASYNCIO)
#define SI_ASYNCIO __SI_ASYNCIO /* Sent by AIO completion. */
#endif /* !SI_ASYNCIO && __SI_ASYNCIO */
#if !defined(SI_MESGQ) && defined(__SI_MESGQ)
#define SI_MESGQ   __SI_MESGQ   /* Sent by real time mesq state change. */
#endif /* !SI_MESGQ && __SI_MESGQ */
#if !defined(SI_TIMER) && defined(__SI_TIMER)
#define SI_TIMER   __SI_TIMER   /* Sent by timer expiration. */
#endif /* !SI_TIMER && __SI_TIMER */
#if !defined(SI_QUEUE) && defined(__SI_QUEUE)
#define SI_QUEUE   __SI_QUEUE   /* Sent by sigqueue. */
#endif /* !SI_QUEUE && __SI_QUEUE */
#if !defined(SI_USER) && defined(__SI_USER)
#define SI_USER    __SI_USER    /* Sent by kill, sigsend. */
#endif /* !SI_USER && __SI_USER */
#if !defined(SI_KERNEL) && defined(__SI_KERNEL)
#define SI_KERNEL  __SI_KERNEL  /* Send by kernel. */
#endif /* !SI_KERNEL && __SI_KERNEL */
#ifndef SI_FROMUSER
#define SI_FROMUSER(siptr)   ((siptr)->si_code <= 0)
#endif /* !SI_FROMUSER */
#ifndef SI_FROMKERNEL
#define SI_FROMKERNEL(siptr) ((siptr)->si_code > 0)
#endif /* !SI_FROMKERNEL */

/* `si_code' values for SIGILL signal. */
#if !defined(ILL_ILLOPC) && defined(__ILL_ILLOPC)
#define ILL_ILLOPC __ILL_ILLOPC /* Illegal opcode. */
#endif /* !ILL_ILLOPC && __ILL_ILLOPC */
#if !defined(ILL_ILLOPN) && defined(__ILL_ILLOPN)
#define ILL_ILLOPN __ILL_ILLOPN /* Illegal operand. */
#endif /* !ILL_ILLOPN && __ILL_ILLOPN */
#if !defined(ILL_ILLADR) && defined(__ILL_ILLADR)
#define ILL_ILLADR __ILL_ILLADR /* Illegal addressing mode. */
#endif /* !ILL_ILLADR && __ILL_ILLADR */
#if !defined(ILL_ILLTRP) && defined(__ILL_ILLTRP)
#define ILL_ILLTRP __ILL_ILLTRP /* Illegal trap. */
#endif /* !ILL_ILLTRP && __ILL_ILLTRP */
#if !defined(ILL_PRVOPC) && defined(__ILL_PRVOPC)
#define ILL_PRVOPC __ILL_PRVOPC /* Privileged opcode. */
#endif /* !ILL_PRVOPC && __ILL_PRVOPC */
#if !defined(ILL_PRVREG) && defined(__ILL_PRVREG)
#define ILL_PRVREG __ILL_PRVREG /* Privileged register. */
#endif /* !ILL_PRVREG && __ILL_PRVREG */
#if !defined(ILL_COPROC) && defined(__ILL_COPROC)
#define ILL_COPROC __ILL_COPROC /* Coprocessor error. */
#endif /* !ILL_COPROC && __ILL_COPROC */
#if !defined(ILL_BADSTK) && defined(__ILL_BADSTK)
#define ILL_BADSTK __ILL_BADSTK /* Internal stack error. */
#endif /* !ILL_BADSTK && __ILL_BADSTK */
#if !defined(ILL_BADIADDR) && defined(__ILL_BADIADDR)
#define ILL_BADIADDR __ILL_BADIADDR /* ??? */
#endif /* !ILL_BADIADDR && __ILL_BADIADDR */
#if !defined(ILL_BADIADDR) && defined(__ILL_BADIADDR)
#define ILL_BADIADDR __ILL_BADIADDR /* ??? */
#endif /* !ILL_BADIADDR && __ILL_BADIADDR */
#if !defined(NSIGILL) && defined(__NSIGILL)
#define NSIGILL __NSIGILL /* Number of `ILL_*' codes. */
#endif /* !NSIGILL && __NSIGILL */

/* `si_code' values for SIGFPE signal. */
#if !defined(FPE_INTDIV) && defined(__FPE_INTDIV)
#define FPE_INTDIV __FPE_INTDIV /* Integer divide by zero. */
#endif /* !FPE_INTDIV && __FPE_INTDIV */
#if !defined(FPE_INTOVF) && defined(__FPE_INTOVF)
#define FPE_INTOVF __FPE_INTOVF /* Integer overflow. */
#endif /* !FPE_INTOVF && __FPE_INTOVF */
#if !defined(FPE_FLTDIV) && defined(__FPE_FLTDIV)
#define FPE_FLTDIV __FPE_FLTDIV /* Floating point divide by zero. */
#endif /* !FPE_FLTDIV && __FPE_FLTDIV */
#if !defined(FPE_FLTOVF) && defined(__FPE_FLTOVF)
#define FPE_FLTOVF __FPE_FLTOVF /* Floating point overflow. */
#endif /* !FPE_FLTOVF && __FPE_FLTOVF */
#if !defined(FPE_FLTUND) && defined(__FPE_FLTUND)
#define FPE_FLTUND __FPE_FLTUND /* Floating point underflow. */
#endif /* !FPE_FLTUND && __FPE_FLTUND */
#if !defined(FPE_FLTRES) && defined(__FPE_FLTRES)
#define FPE_FLTRES __FPE_FLTRES /* Floating point inexact result. */
#endif /* !FPE_FLTRES && __FPE_FLTRES */
#if !defined(FPE_FLTINV) && defined(__FPE_FLTINV)
#define FPE_FLTINV __FPE_FLTINV /* Floating point invalid operation. */
#endif /* !FPE_FLTINV && __FPE_FLTINV */
#if !defined(FPE_FLTSUB) && defined(__FPE_FLTSUB)
#define FPE_FLTSUB __FPE_FLTSUB /* Subscript out of range. */
#endif /* !FPE_FLTSUB && __FPE_FLTSUB */
#if !defined(FPE_FLTUNK) && defined(__FPE_FLTUNK)
#define FPE_FLTUNK __FPE_FLTUNK /* ??? */
#endif /* !FPE_FLTUNK && __FPE_FLTUNK */
#if !defined(FPE_CONDTRAP) && defined(__FPE_CONDTRAP)
#define FPE_CONDTRAP __FPE_CONDTRAP /* ??? */
#endif /* !FPE_CONDTRAP && __FPE_CONDTRAP */
#if !defined(NSIGFPE) && defined(__NSIGFPE)
#define NSIGFPE __NSIGFPE /* Number of `FPE_*' codes. */
#endif /* !NSIGFPE && __NSIGFPE */

/* `si_code' values for SIGSEGV signal. */
#if !defined(SEGV_MAPERR) && defined(__SEGV_MAPERR)
#define SEGV_MAPERR __SEGV_MAPERR /* Address not mapped to object. */
#endif /* !SEGV_MAPERR && __SEGV_MAPERR */
#if !defined(SEGV_ACCERR) && defined(__SEGV_ACCERR)
#define SEGV_ACCERR __SEGV_ACCERR /* Invalid permissions for mapped object. */
#endif /* !SEGV_ACCERR && __SEGV_ACCERR */
#if !defined(SEGV_BNDERR) && defined(__SEGV_BNDERR)
#define SEGV_BNDERR __SEGV_BNDERR /* ??? */
#endif /* !SEGV_BNDERR && __SEGV_BNDERR */
#if !defined(SEGV_PKUERR) && defined(__SEGV_PKUERR)
#define SEGV_PKUERR __SEGV_PKUERR /* ??? */
#endif /* !SEGV_PKUERR && __SEGV_PKUERR */
#if !defined(SEGV_ACCADI) && defined(__SEGV_ACCADI)
#define SEGV_ACCADI __SEGV_ACCADI /* ??? */
#endif /* !SEGV_ACCADI && __SEGV_ACCADI */
#if !defined(SEGV_ADIDERR) && defined(__SEGV_ADIDERR)
#define SEGV_ADIDERR __SEGV_ADIDERR /* ??? */
#endif /* !SEGV_ADIDERR && __SEGV_ADIDERR */
#if !defined(SEGV_ADIPERR) && defined(__SEGV_ADIPERR)
#define SEGV_ADIPERR __SEGV_ADIPERR /* ??? */
#endif /* !SEGV_ADIPERR && __SEGV_ADIPERR */
#if !defined(SEGV_MTEAERR) && defined(__SEGV_MTEAERR)
#define SEGV_MTEAERR __SEGV_MTEAERR /* ??? */
#endif /* !SEGV_MTEAERR && __SEGV_MTEAERR */
#if !defined(SEGV_MTESERR) && defined(__SEGV_MTESERR)
#define SEGV_MTESERR __SEGV_MTESERR /* ??? */
#endif /* !SEGV_MTESERR && __SEGV_MTESERR */
#if !defined(NSIGSEGV) && defined(__NSIGSEGV)
#define NSIGSEGV __NSIGSEGV /* Number of `SEGV_*' codes. */
#endif /* !NSIGSEGV && __NSIGSEGV */

/* `si_code' values for SIGBUS signal. */
#if !defined(BUS_ADRALN) && defined(__BUS_ADRALN)
#define BUS_ADRALN    __BUS_ADRALN    /* Invalid address alignment. */
#endif /* !BUS_ADRALN && __BUS_ADRALN */
#if !defined(BUS_ADRERR) && defined(__BUS_ADRERR)
#define BUS_ADRERR    __BUS_ADRERR    /* Non-existent physical address. */
#endif /* !BUS_ADRERR && __BUS_ADRERR */
#if !defined(BUS_OBJERR) && defined(__BUS_OBJERR)
#define BUS_OBJERR    __BUS_OBJERR    /* Object specific hardware error. */
#endif /* !BUS_OBJERR && __BUS_OBJERR */
#if !defined(BUS_MCEERR_AR) && defined(__BUS_MCEERR_AR)
#define BUS_MCEERR_AR __BUS_MCEERR_AR /* Hardware memory error: action required. */
#endif /* !BUS_MCEERR_AR && __BUS_MCEERR_AR */
#if !defined(BUS_MCEERR_AO) && defined(__BUS_MCEERR_AO)
#define BUS_MCEERR_AO __BUS_MCEERR_AO /* Hardware memory error: action optional. */
#endif /* !BUS_MCEERR_AO && __BUS_MCEERR_AO */
#if !defined(NSIGBUS) && defined(__NSIGBUS)
#define NSIGBUS __NSIGBUS /* Number of `BUS_*' codes. */
#endif /* !NSIGBUS && __NSIGBUS */

/* `si_code' values for SIGTRAP signal. */
#if !defined(TRAP_BRKPT) && defined(__TRAP_BRKPT)
#define TRAP_BRKPT __TRAP_BRKPT /* Process breakpoint. */
#endif /* !TRAP_BRKPT && __TRAP_BRKPT */
#if !defined(TRAP_TRACE) && defined(__TRAP_TRACE)
#define TRAP_TRACE __TRAP_TRACE /* Process trace trap. */
#endif /* !TRAP_TRACE && __TRAP_TRACE */
#if !defined(TRAP_BRANCH) && defined(__TRAP_BRANCH)
#define TRAP_BRANCH __TRAP_BRANCH /* ??? */
#endif /* !TRAP_BRANCH && __TRAP_BRANCH */
#if !defined(TRAP_HWBKPT) && defined(__TRAP_HWBKPT)
#define TRAP_HWBKPT __TRAP_HWBKPT /* ??? */
#endif /* !TRAP_HWBKPT && __TRAP_HWBKPT */
#if !defined(TRAP_UNK) && defined(__TRAP_UNK)
#define TRAP_UNK __TRAP_UNK /* ??? */
#endif /* !TRAP_UNK && __TRAP_UNK */
#if !defined(TRAP_PERF) && defined(__TRAP_PERF)
#define TRAP_PERF __TRAP_PERF /* ??? */
#endif /* !TRAP_PERF && __TRAP_PERF */
#if !defined(NSIGTRAP) && defined(__NSIGTRAP)
#define NSIGTRAP __NSIGTRAP /* Number of `TRAP_*' codes. */
#endif /* !NSIGTRAP && __NSIGTRAP */

/* `si_code' values for SIGCHLD signal. */
#if !defined(CLD_EXITED) && defined(__CLD_EXITED)
#define CLD_EXITED    __CLD_EXITED    /* Child has exited. */
#endif /* !CLD_EXITED && __CLD_EXITED */
#if !defined(CLD_KILLED) && defined(__CLD_KILLED)
#define CLD_KILLED    __CLD_KILLED    /* Child was killed. */
#endif /* !CLD_KILLED && __CLD_KILLED */
#if !defined(CLD_DUMPED) && defined(__CLD_DUMPED)
#define CLD_DUMPED    __CLD_DUMPED    /* Child terminated abnormally. */
#endif /* !CLD_DUMPED && __CLD_DUMPED */
#if !defined(CLD_TRAPPED) && defined(__CLD_TRAPPED)
#define CLD_TRAPPED   __CLD_TRAPPED   /* Traced child has trapped. */
#endif /* !CLD_TRAPPED && __CLD_TRAPPED */
#if !defined(CLD_STOPPED) && defined(__CLD_STOPPED)
#define CLD_STOPPED   __CLD_STOPPED   /* Child has stopped. */
#endif /* !CLD_STOPPED && __CLD_STOPPED */
#if !defined(CLD_CONTINUED) && defined(__CLD_CONTINUED)
#define CLD_CONTINUED __CLD_CONTINUED /* Stopped child has continued. */
#endif /* !CLD_CONTINUED && __CLD_CONTINUED */
#if !defined(NSIGCHLD) && defined(__NSIGCHLD)
#define NSIGCHLD __NSIGCHLD /* Number of `CLD_*' codes. */
#endif /* !NSIGCHLD && __NSIGCHLD */

/* `si_code' values for SIGPOLL signal. */
#if !defined(POLL_IN) && defined(__POLL_IN)
#define POLL_IN  __POLL_IN  /* Data input available. */
#endif /* !POLL_IN && __POLL_IN */
#if !defined(POLL_OUT) && defined(__POLL_OUT)
#define POLL_OUT __POLL_OUT /* Output buffers available. */
#endif /* !POLL_OUT && __POLL_OUT */
#if !defined(POLL_MSG) && defined(__POLL_MSG)
#define POLL_MSG __POLL_MSG /* Input message available. */
#endif /* !POLL_MSG && __POLL_MSG */
#if !defined(POLL_ERR) && defined(__POLL_ERR)
#define POLL_ERR __POLL_ERR /* I/O error. */
#endif /* !POLL_ERR && __POLL_ERR */
#if !defined(POLL_PRI) && defined(__POLL_PRI)
#define POLL_PRI __POLL_PRI /* High priority input available. */
#endif /* !POLL_PRI && __POLL_PRI */
#if !defined(POLL_HUP) && defined(__POLL_HUP)
#define POLL_HUP __POLL_HUP /* Device disconnected. */
#endif /* !POLL_HUP && __POLL_HUP */
#if !defined(NSIGPOLL) && defined(__NSIGPOLL)
#define NSIGPOLL __NSIGPOLL /* Number of `POLL_*' codes. */
#endif /* !NSIGPOLL && __NSIGPOLL */

/* `si_code' values for SIGSYS signal. */
#if !defined(SYS_SECCOMP) && defined(__SYS_SECCOMP)
#define SYS_SECCOMP __SYS_SECCOMP /* ???*/
#endif /* !SYS_SECCOMP && __SYS_SECCOMP */
#if !defined(SYS_USER_DISPATCH) && defined(__SYS_USER_DISPATCH)
#define SYS_USER_DISPATCH __SYS_USER_DISPATCH /* ???*/
#endif /* !SYS_USER_DISPATCH && __SYS_USER_DISPATCH */
#if !defined(NSIGSYS) && defined(__NSIGSYS)
#define NSIGSYS __NSIGSYS /* Number of `SYS_*' codes. */
#endif /* !NSIGSYS && __NSIGSYS */

/* `si_code' values for SIGEMT signal. */
#if !defined(EMT_TAGOVF) && defined(__EMT_TAGOVF)
#define EMT_TAGOVF __EMT_TAGOVF /* ??? */
#endif /* !EMT_TAGOVF && __EMT_TAGOVF */
#if !defined(NSIGEMT) && defined(__NSIGEMT)
#define NSIGEMT __NSIGEMT /* Number of `EMT_*' codes. */
#endif /* !NSIGEMT && __NSIGEMT */



/* `sigev_notify' values. */
#if !defined(SIGEV_SIGNAL) && defined(__SIGEV_SIGNAL)
#define SIGEV_SIGNAL        __SIGEV_SIGNAL        /* Notify via signal. */
#endif /* !SIGEV_SIGNAL && __SIGEV_SIGNAL */
#if !defined(SIGEV_NONE) && defined(__SIGEV_NONE)
#define SIGEV_NONE          __SIGEV_NONE          /* Other notification: meaningless. */
#endif /* !SIGEV_NONE && __SIGEV_NONE */
#if !defined(SIGEV_THREAD) && defined(__SIGEV_THREAD)
#define SIGEV_THREAD        __SIGEV_THREAD        /* Deliver via thread creation. */
#endif /* !SIGEV_THREAD && __SIGEV_THREAD */
#if !defined(SIGEV_THREAD_ID) && defined(__SIGEV_THREAD_ID)
#define SIGEV_THREAD_ID     __SIGEV_THREAD_ID     /* Send signal to specific thread. */
#endif /* !SIGEV_THREAD_ID && __SIGEV_THREAD_ID */



#if !defined(SIGEV_MAX_SIZE) && defined(__SIGEV_MAX_SIZE)
#define SIGEV_MAX_SIZE __SIGEV_MAX_SIZE /* ... */
#endif /* !SIGEV_MAX_SIZE && __SIGEV_MAX_SIZE */
#if !defined(SIGEV_PAD_SIZE) && defined(__SIGEV_PAD_SIZE)
#define SIGEV_PAD_SIZE __SIGEV_PAD_SIZE /* ... */
#endif /* !SIGEV_PAD_SIZE && __SIGEV_PAD_SIZE */

#ifdef __CC__
__DECL_BEGIN

#ifndef __sigval_t_defined
#define __sigval_t_defined
typedef union sigval sigval_t;
#endif /* !__sigval_t_defined */

#ifndef __ARCH_SI_BAND_T
#define __ARCH_SI_BAND_T __LONGPTR_TYPE__
#endif /* !__ARCH_SI_BAND_T */

#ifndef __ARCH_SI_CLOCK_T
#define __ARCH_SI_CLOCK_T __kernel_clock_t
#endif /* !__ARCH_SI_CLOCK_T */

#ifndef __ARCH_SI_ATTRIBUTES
#define __ARCH_SI_ATTRIBUTES
#endif /* !__ARCH_SI_ATTRIBUTES */

#ifndef __siginfo_t_defined
#define __siginfo_t_defined
typedef struct __siginfo_struct siginfo_t;
#endif /* !__siginfo_t_defined */

#ifndef __sigevent_t_defined
#define __sigevent_t_defined
typedef struct sigevent sigevent_t;
#endif /* !__sigevent_t_defined */

__DECL_END
#endif /* __CC__ */

#endif /* !_ASM_SIGINFO_H */
