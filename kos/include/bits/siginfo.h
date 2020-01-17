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
#ifndef _BITS_SIGINFO_H
#define _BITS_SIGINFO_H 1

#include <__stdinc.h>
#include <features.h>

#include <bits/siginfo-struct.h>
#include <bits/siginfo-values.h>

__SYSDECL_BEGIN

/* Values for `si_code'. Positive values are reserved for kernel-generated signals. */
/*[[[enum]]]*/
#ifdef __CC__
enum {
#ifdef __SI_ASYNCNL
	SI_ASYNCNL = __SI_ASYNCNL, /* Sent by asynch name lookup completion. */
#endif /* __SI_ASYNCNL */
#ifdef __SI_TKILL
	SI_TKILL = __SI_TKILL,     /* Sent by tkill. */
#endif /* __SI_TKILL */
#ifdef __SI_SIGIO
	SI_SIGIO = __SI_SIGIO,     /* Sent by queued SIGIO. */
#endif /* __SI_SIGIO */
#ifdef __SI_ASYNCIO
	SI_ASYNCIO = __SI_ASYNCIO, /* Sent by AIO completion. */
#endif /* __SI_ASYNCIO */
#ifdef __SI_MESGQ
	SI_MESGQ = __SI_MESGQ,     /* Sent by real time mesq state change. */
#endif /* __SI_MESGQ */
#ifdef __SI_TIMER
	SI_TIMER = __SI_TIMER,     /* Sent by timer expiration. */
#endif /* __SI_TIMER */
#ifdef __SI_QUEUE
	SI_QUEUE = __SI_QUEUE,     /* Sent by sigqueue_entry. */
#endif /* __SI_QUEUE */
#ifdef __SI_USER
	SI_USER = __SI_USER,       /* Sent by kill, sigsend. */
#endif /* __SI_USER */
#ifdef __SI_KERNEL
	SI_KERNEL = __SI_KERNEL,   /* Send by kernel. */
#endif /* __SI_KERNEL */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#ifdef __SI_ASYNCNL
#define SI_ASYNCNL SI_ASYNCNL /* Sent by asynch name lookup completion. */
#endif /* __SI_ASYNCNL */
#ifdef __SI_TKILL
#define SI_TKILL   SI_TKILL   /* Sent by tkill. */
#endif /* __SI_TKILL */
#ifdef __SI_SIGIO
#define SI_SIGIO   SI_SIGIO   /* Sent by queued SIGIO. */
#endif /* __SI_SIGIO */
#ifdef __SI_ASYNCIO
#define SI_ASYNCIO SI_ASYNCIO /* Sent by AIO completion. */
#endif /* __SI_ASYNCIO */
#ifdef __SI_MESGQ
#define SI_MESGQ   SI_MESGQ   /* Sent by real time mesq state change. */
#endif /* __SI_MESGQ */
#ifdef __SI_TIMER
#define SI_TIMER   SI_TIMER   /* Sent by timer expiration. */
#endif /* __SI_TIMER */
#ifdef __SI_QUEUE
#define SI_QUEUE   SI_QUEUE   /* Sent by sigqueue_entry. */
#endif /* __SI_QUEUE */
#ifdef __SI_USER
#define SI_USER    SI_USER    /* Sent by kill, sigsend. */
#endif /* __SI_USER */
#ifdef __SI_KERNEL
#define SI_KERNEL  SI_KERNEL  /* Send by kernel. */
#endif /* __SI_KERNEL */
#else /* __COMPILER_PREFERR_ENUMS */
#ifdef __SI_ASYNCNL
#define SI_ASYNCNL __SI_ASYNCNL /* Sent by asynch name lookup completion. */
#endif /* __SI_ASYNCNL */
#ifdef __SI_TKILL
#define SI_TKILL   __SI_TKILL   /* Sent by tkill. */
#endif /* __SI_TKILL */
#ifdef __SI_SIGIO
#define SI_SIGIO   __SI_SIGIO   /* Sent by queued SIGIO. */
#endif /* __SI_SIGIO */
#ifdef __SI_ASYNCIO
#define SI_ASYNCIO __SI_ASYNCIO /* Sent by AIO completion. */
#endif /* __SI_ASYNCIO */
#ifdef __SI_MESGQ
#define SI_MESGQ   __SI_MESGQ   /* Sent by real time mesq state change. */
#endif /* __SI_MESGQ */
#ifdef __SI_TIMER
#define SI_TIMER   __SI_TIMER   /* Sent by timer expiration. */
#endif /* __SI_TIMER */
#ifdef __SI_QUEUE
#define SI_QUEUE   __SI_QUEUE   /* Sent by sigqueue_entry. */
#endif /* __SI_QUEUE */
#ifdef __SI_USER
#define SI_USER    __SI_USER    /* Sent by kill, sigsend. */
#endif /* __SI_USER */
#ifdef __SI_KERNEL
#define SI_KERNEL  __SI_KERNEL  /* Send by kernel. */
#endif /* __SI_KERNEL */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/



#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_XOPEN2K8)
/* `si_code' values for SIGILL signal. */
/*[[[enum]]]*/
#ifdef __CC__
enum {
#ifdef __ILL_ILLOPC
	ILL_ILLOPC = __ILL_ILLOPC, /* Illegal opcode. */
#endif /* __ILL_ILLOPC */
#ifdef __ILL_ILLOPN
	ILL_ILLOPN = __ILL_ILLOPN, /* Illegal operand. */
#endif /* __ILL_ILLOPN */
#ifdef __ILL_ILLADR
	ILL_ILLADR = __ILL_ILLADR, /* Illegal addressing mode. */
#endif /* __ILL_ILLADR */
#ifdef __ILL_ILLTRP
	ILL_ILLTRP = __ILL_ILLTRP, /* Illegal trap. */
#endif /* __ILL_ILLTRP */
#ifdef __ILL_PRVOPC
	ILL_PRVOPC = __ILL_PRVOPC, /* Privileged opcode. */
#endif /* __ILL_PRVOPC */
#ifdef __ILL_PRVREG
	ILL_PRVREG = __ILL_PRVREG, /* Privileged register. */
#endif /* __ILL_PRVREG */
#ifdef __ILL_COPROC
	ILL_COPROC = __ILL_COPROC, /* Coprocessor error. */
#endif /* __ILL_COPROC */
#ifdef __ILL_BADSTK
	ILL_BADSTK = __ILL_BADSTK  /* Internal stack error. */
#endif /* __ILL_BADSTK */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#ifdef __ILL_ILLOPC
#define ILL_ILLOPC ILL_ILLOPC /* Illegal opcode. */
#endif /* __ILL_ILLOPC */
#ifdef __ILL_ILLOPN
#define ILL_ILLOPN ILL_ILLOPN /* Illegal operand. */
#endif /* __ILL_ILLOPN */
#ifdef __ILL_ILLADR
#define ILL_ILLADR ILL_ILLADR /* Illegal addressing mode. */
#endif /* __ILL_ILLADR */
#ifdef __ILL_ILLTRP
#define ILL_ILLTRP ILL_ILLTRP /* Illegal trap. */
#endif /* __ILL_ILLTRP */
#ifdef __ILL_PRVOPC
#define ILL_PRVOPC ILL_PRVOPC /* Privileged opcode. */
#endif /* __ILL_PRVOPC */
#ifdef __ILL_PRVREG
#define ILL_PRVREG ILL_PRVREG /* Privileged register. */
#endif /* __ILL_PRVREG */
#ifdef __ILL_COPROC
#define ILL_COPROC ILL_COPROC /* Coprocessor error. */
#endif /* __ILL_COPROC */
#ifdef __ILL_BADSTK
#define ILL_BADSTK ILL_BADSTK /* Internal stack error. */
#endif /* __ILL_BADSTK */
#else /* __COMPILER_PREFERR_ENUMS */
#ifdef __ILL_ILLOPC
#define ILL_ILLOPC __ILL_ILLOPC /* Illegal opcode. */
#endif /* __ILL_ILLOPC */
#ifdef __ILL_ILLOPN
#define ILL_ILLOPN __ILL_ILLOPN /* Illegal operand. */
#endif /* __ILL_ILLOPN */
#ifdef __ILL_ILLADR
#define ILL_ILLADR __ILL_ILLADR /* Illegal addressing mode. */
#endif /* __ILL_ILLADR */
#ifdef __ILL_ILLTRP
#define ILL_ILLTRP __ILL_ILLTRP /* Illegal trap. */
#endif /* __ILL_ILLTRP */
#ifdef __ILL_PRVOPC
#define ILL_PRVOPC __ILL_PRVOPC /* Privileged opcode. */
#endif /* __ILL_PRVOPC */
#ifdef __ILL_PRVREG
#define ILL_PRVREG __ILL_PRVREG /* Privileged register. */
#endif /* __ILL_PRVREG */
#ifdef __ILL_COPROC
#define ILL_COPROC __ILL_COPROC /* Coprocessor error. */
#endif /* __ILL_COPROC */
#ifdef __ILL_BADSTK
#define ILL_BADSTK __ILL_BADSTK /* Internal stack error. */
#endif /* __ILL_BADSTK */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/



/* `si_code' values for SIGFPE signal. */
/*[[[enum]]]*/
#ifdef __CC__
enum {
#ifdef __FPE_INTDIV
	FPE_INTDIV = __FPE_INTDIV, /* Integer divide by zero. */
#endif /* __FPE_INTDIV */
#ifdef __FPE_INTOVF
	FPE_INTOVF = __FPE_INTOVF, /* Integer overflow. */
#endif /* __FPE_INTOVF */
#ifdef __FPE_FLTDIV
	FPE_FLTDIV = __FPE_FLTDIV, /* Floating point divide by zero. */
#endif /* __FPE_FLTDIV */
#ifdef __FPE_FLTOVF
	FPE_FLTOVF = __FPE_FLTOVF, /* Floating point overflow. */
#endif /* __FPE_FLTOVF */
#ifdef __FPE_FLTUND
	FPE_FLTUND = __FPE_FLTUND, /* Floating point underflow. */
#endif /* __FPE_FLTUND */
#ifdef __FPE_FLTRES
	FPE_FLTRES = __FPE_FLTRES, /* Floating point inexact result. */
#endif /* __FPE_FLTRES */
#ifdef __FPE_FLTINV
	FPE_FLTINV = __FPE_FLTINV, /* Floating point invalid operation. */
#endif /* __FPE_FLTINV */
#ifdef __FPE_FLTSUB
	FPE_FLTSUB = __FPE_FLTSUB  /* Subscript out of range. */
#endif /* __FPE_FLTSUB */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#ifdef __FPE_INTDIV
#define FPE_INTDIV FPE_INTDIV /* Integer divide by zero. */
#endif /* __FPE_INTDIV */
#ifdef __FPE_INTOVF
#define FPE_INTOVF FPE_INTOVF /* Integer overflow. */
#endif /* __FPE_INTOVF */
#ifdef __FPE_FLTDIV
#define FPE_FLTDIV FPE_FLTDIV /* Floating point divide by zero. */
#endif /* __FPE_FLTDIV */
#ifdef __FPE_FLTOVF
#define FPE_FLTOVF FPE_FLTOVF /* Floating point overflow. */
#endif /* __FPE_FLTOVF */
#ifdef __FPE_FLTUND
#define FPE_FLTUND FPE_FLTUND /* Floating point underflow. */
#endif /* __FPE_FLTUND */
#ifdef __FPE_FLTRES
#define FPE_FLTRES FPE_FLTRES /* Floating point inexact result. */
#endif /* __FPE_FLTRES */
#ifdef __FPE_FLTINV
#define FPE_FLTINV FPE_FLTINV /* Floating point invalid operation. */
#endif /* __FPE_FLTINV */
#ifdef __FPE_FLTSUB
#define FPE_FLTSUB FPE_FLTSUB /* Subscript out of range. */
#endif /* __FPE_FLTSUB */
#else /* __COMPILER_PREFERR_ENUMS */
#ifdef __FPE_INTDIV
#define FPE_INTDIV __FPE_INTDIV /* Integer divide by zero. */
#endif /* __FPE_INTDIV */
#ifdef __FPE_INTOVF
#define FPE_INTOVF __FPE_INTOVF /* Integer overflow. */
#endif /* __FPE_INTOVF */
#ifdef __FPE_FLTDIV
#define FPE_FLTDIV __FPE_FLTDIV /* Floating point divide by zero. */
#endif /* __FPE_FLTDIV */
#ifdef __FPE_FLTOVF
#define FPE_FLTOVF __FPE_FLTOVF /* Floating point overflow. */
#endif /* __FPE_FLTOVF */
#ifdef __FPE_FLTUND
#define FPE_FLTUND __FPE_FLTUND /* Floating point underflow. */
#endif /* __FPE_FLTUND */
#ifdef __FPE_FLTRES
#define FPE_FLTRES __FPE_FLTRES /* Floating point inexact result. */
#endif /* __FPE_FLTRES */
#ifdef __FPE_FLTINV
#define FPE_FLTINV __FPE_FLTINV /* Floating point invalid operation. */
#endif /* __FPE_FLTINV */
#ifdef __FPE_FLTSUB
#define FPE_FLTSUB __FPE_FLTSUB /* Subscript out of range. */
#endif /* __FPE_FLTSUB */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/



/* `si_code' values for SIGSEGV signal. */
/*[[[enum]]]*/
#ifdef __CC__
enum {
#ifdef __SEGV_MAPERR
	SEGV_MAPERR = __SEGV_MAPERR, /* Address not mapped to object. */
#endif /* __SEGV_MAPERR */
#ifdef __SEGV_ACCERR
	SEGV_ACCERR = __SEGV_ACCERR  /* Invalid permissions for mapped object. */
#endif /* __SEGV_ACCERR */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#ifdef __SEGV_MAPERR
#define SEGV_MAPERR SEGV_MAPERR /* Address not mapped to object. */
#endif /* __SEGV_MAPERR */
#ifdef __SEGV_ACCERR
#define SEGV_ACCERR SEGV_ACCERR /* Invalid permissions for mapped object. */
#endif /* __SEGV_ACCERR */
#else /* __COMPILER_PREFERR_ENUMS */
#ifdef __SEGV_MAPERR
#define SEGV_MAPERR __SEGV_MAPERR /* Address not mapped to object. */
#endif /* __SEGV_MAPERR */
#ifdef __SEGV_ACCERR
#define SEGV_ACCERR __SEGV_ACCERR /* Invalid permissions for mapped object. */
#endif /* __SEGV_ACCERR */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/



/* `si_code' values for SIGBUS signal. */
/*[[[enum]]]*/
#ifdef __CC__
enum {
#ifdef __BUS_ADRALN
	BUS_ADRALN    = __BUS_ADRALN,    /* Invalid address alignment. */
#endif /* __BUS_ADRALN */
#ifdef __BUS_ADRERR
	BUS_ADRERR    = __BUS_ADRERR,    /* Non-existant physical address. */
#endif /* __BUS_ADRERR */
#ifdef __BUS_OBJERR
	BUS_OBJERR    = __BUS_OBJERR,    /* Object specific hardware error. */
#endif /* __BUS_OBJERR */
#ifdef __BUS_MCEERR_AR
	BUS_MCEERR_AR = __BUS_MCEERR_AR, /* Hardware memory error: action required. */
#endif /* __BUS_MCEERR_AR */
#ifdef __BUS_MCEERR_AO
	BUS_MCEERR_AO = __BUS_MCEERR_AO  /* Hardware memory error: action optional. */
#endif /* __BUS_MCEERR_AO */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#ifdef __BUS_ADRALN
#define BUS_ADRALN    BUS_ADRALN    /* Invalid address alignment. */
#endif /* __BUS_ADRALN */
#ifdef __BUS_ADRERR
#define BUS_ADRERR    BUS_ADRERR    /* Non-existant physical address. */
#endif /* __BUS_ADRERR */
#ifdef __BUS_OBJERR
#define BUS_OBJERR    BUS_OBJERR    /* Object specific hardware error. */
#endif /* __BUS_OBJERR */
#ifdef __BUS_MCEERR_AR
#define BUS_MCEERR_AR BUS_MCEERR_AR /* Hardware memory error: action required. */
#endif /* __BUS_MCEERR_AR */
#ifdef __BUS_MCEERR_AO
#define BUS_MCEERR_AO BUS_MCEERR_AO /* Hardware memory error: action optional. */
#endif /* __BUS_MCEERR_AO */
#else /* __COMPILER_PREFERR_ENUMS */
#ifdef __BUS_ADRALN
#define BUS_ADRALN    __BUS_ADRALN    /* Invalid address alignment. */
#endif /* __BUS_ADRALN */
#ifdef __BUS_ADRERR
#define BUS_ADRERR    __BUS_ADRERR    /* Non-existant physical address. */
#endif /* __BUS_ADRERR */
#ifdef __BUS_OBJERR
#define BUS_OBJERR    __BUS_OBJERR    /* Object specific hardware error. */
#endif /* __BUS_OBJERR */
#ifdef __BUS_MCEERR_AR
#define BUS_MCEERR_AR __BUS_MCEERR_AR /* Hardware memory error: action required. */
#endif /* __BUS_MCEERR_AR */
#ifdef __BUS_MCEERR_AO
#define BUS_MCEERR_AO __BUS_MCEERR_AO /* Hardware memory error: action optional. */
#endif /* __BUS_MCEERR_AO */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/
#endif /* __USE_XOPEN_EXTENDED || __USE_XOPEN2K8 */



#ifdef __USE_XOPEN_EXTENDED
/* `si_code' values for SIGTRAP signal. */
/*[[[enum]]]*/
#ifdef __CC__
enum {
#ifdef __TRAP_BRKPT
	TRAP_BRKPT = __TRAP_BRKPT, /* Process breakpoint. */
#endif /* __TRAP_BRKPT */
#ifdef __TRAP_TRACE
	TRAP_TRACE = __TRAP_TRACE  /* Process trace trap. */
#endif /* __TRAP_TRACE */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#ifdef __TRAP_BRKPT
#define TRAP_BRKPT TRAP_BRKPT /* Process breakpoint. */
#endif /* __TRAP_BRKPT */
#ifdef __TRAP_TRACE
#define TRAP_TRACE TRAP_TRACE /* Process trace trap. */
#endif /* __TRAP_TRACE */
#else /* __COMPILER_PREFERR_ENUMS */
#ifdef __TRAP_BRKPT
#define TRAP_BRKPT __TRAP_BRKPT /* Process breakpoint. */
#endif /* __TRAP_BRKPT */
#ifdef __TRAP_TRACE
#define TRAP_TRACE __TRAP_TRACE /* Process trace trap. */
#endif /* __TRAP_TRACE */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/
#endif /* __USE_XOPEN_EXTENDED */



#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_XOPEN2K8)

/* `si_code' values for SIGCHLD signal. */
#ifndef CLD_EXITED
/*[[[enum]]]*/
#ifdef __CC__
enum {
#ifdef __CLD_EXITED
	CLD_EXITED    = __CLD_EXITED,    /* Child has exited. */
#endif /* __CLD_EXITED */
#ifdef __CLD_KILLED
	CLD_KILLED    = __CLD_KILLED,    /* Child was killed. */
#endif /* __CLD_KILLED */
#ifdef __CLD_DUMPED
	CLD_DUMPED    = __CLD_DUMPED,    /* Child terminated abnormally. */
#endif /* __CLD_DUMPED */
#ifdef __CLD_TRAPPED
	CLD_TRAPPED   = __CLD_TRAPPED,   /* Traced child has trapped. */
#endif /* __CLD_TRAPPED */
#ifdef __CLD_STOPPED
	CLD_STOPPED   = __CLD_STOPPED,   /* Child has stopped. */
#endif /* __CLD_STOPPED */
#ifdef __CLD_CONTINUED
	CLD_CONTINUED = __CLD_CONTINUED  /* Stopped child has continued. */
#endif /* __CLD_CONTINUED */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#ifdef __CLD_EXITED
#define CLD_EXITED    CLD_EXITED    /* Child has exited. */
#endif /* __CLD_EXITED */
#ifdef __CLD_KILLED
#define CLD_KILLED    CLD_KILLED    /* Child was killed. */
#endif /* __CLD_KILLED */
#ifdef __CLD_DUMPED
#define CLD_DUMPED    CLD_DUMPED    /* Child terminated abnormally. */
#endif /* __CLD_DUMPED */
#ifdef __CLD_TRAPPED
#define CLD_TRAPPED   CLD_TRAPPED   /* Traced child has trapped. */
#endif /* __CLD_TRAPPED */
#ifdef __CLD_STOPPED
#define CLD_STOPPED   CLD_STOPPED   /* Child has stopped. */
#endif /* __CLD_STOPPED */
#ifdef __CLD_CONTINUED
#define CLD_CONTINUED CLD_CONTINUED /* Stopped child has continued. */
#endif /* __CLD_CONTINUED */
#else /* __COMPILER_PREFERR_ENUMS */
#ifdef __CLD_EXITED
#define CLD_EXITED    __CLD_EXITED    /* Child has exited. */
#endif /* __CLD_EXITED */
#ifdef __CLD_KILLED
#define CLD_KILLED    __CLD_KILLED    /* Child was killed. */
#endif /* __CLD_KILLED */
#ifdef __CLD_DUMPED
#define CLD_DUMPED    __CLD_DUMPED    /* Child terminated abnormally. */
#endif /* __CLD_DUMPED */
#ifdef __CLD_TRAPPED
#define CLD_TRAPPED   __CLD_TRAPPED   /* Traced child has trapped. */
#endif /* __CLD_TRAPPED */
#ifdef __CLD_STOPPED
#define CLD_STOPPED   __CLD_STOPPED   /* Child has stopped. */
#endif /* __CLD_STOPPED */
#ifdef __CLD_CONTINUED
#define CLD_CONTINUED __CLD_CONTINUED /* Stopped child has continued. */
#endif /* __CLD_CONTINUED */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/
#endif /* !CLD_EXITED */



/* `si_code' values for SIGPOLL signal. */
#ifndef POLL_IN
/*[[[enum]]]*/
#ifdef __CC__
enum {
#ifdef __POLL_IN
	POLL_IN  = __POLL_IN,  /* Data input available. */
#endif /* __POLL_IN */
#ifdef __POLL_OUT
	POLL_OUT = __POLL_OUT, /* Output buffers available. */
#endif /* __POLL_OUT */
#ifdef __POLL_MSG
	POLL_MSG = __POLL_MSG, /* Input message available.   */
#endif /* __POLL_MSG */
#ifdef __POLL_ERR
	POLL_ERR = __POLL_ERR, /* I/O error. */
#endif /* __POLL_ERR */
#ifdef __POLL_PRI
	POLL_PRI = __POLL_PRI, /* High priority input available. */
#endif /* __POLL_PRI */
#ifdef __POLL_HUP
	POLL_HUP = __POLL_HUP  /* Device disconnected. */
#endif /* __POLL_HUP */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#ifdef __POLL_IN
#define POLL_IN  POLL_IN  /* Data input available. */
#endif /* __POLL_IN */
#ifdef __POLL_OUT
#define POLL_OUT POLL_OUT /* Output buffers available. */
#endif /* __POLL_OUT */
#ifdef __POLL_MSG
#define POLL_MSG POLL_MSG /* Input message available.   */
#endif /* __POLL_MSG */
#ifdef __POLL_ERR
#define POLL_ERR POLL_ERR /* I/O error. */
#endif /* __POLL_ERR */
#ifdef __POLL_PRI
#define POLL_PRI POLL_PRI /* High priority input available. */
#endif /* __POLL_PRI */
#ifdef __POLL_HUP
#define POLL_HUP POLL_HUP /* Device disconnected. */
#endif /* __POLL_HUP */
#else /* __COMPILER_PREFERR_ENUMS */
#ifdef __POLL_IN
#define POLL_IN  __POLL_IN  /* Data input available. */
#endif /* __POLL_IN */
#ifdef __POLL_OUT
#define POLL_OUT __POLL_OUT /* Output buffers available. */
#endif /* __POLL_OUT */
#ifdef __POLL_MSG
#define POLL_MSG __POLL_MSG /* Input message available.   */
#endif /* __POLL_MSG */
#ifdef __POLL_ERR
#define POLL_ERR __POLL_ERR /* I/O error. */
#endif /* __POLL_ERR */
#ifdef __POLL_PRI
#define POLL_PRI __POLL_PRI /* High priority input available. */
#endif /* __POLL_PRI */
#ifdef __POLL_HUP
#define POLL_HUP __POLL_HUP /* Device disconnected. */
#endif /* __POLL_HUP */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/
#endif /* !POLL_IN */

#endif /* __USE_XOPEN_EXTENDED || __USE_XOPEN2K8 */

__SYSDECL_END

#endif /* !_BITS_SIGINFO_H */
