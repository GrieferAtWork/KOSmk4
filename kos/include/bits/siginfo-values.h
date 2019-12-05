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
#ifndef _BITS_SIGINFO_VALUES_H
#define _BITS_SIGINFO_VALUES_H 1

#include <__stdinc.h>

/* Values for `si_code'. Positive values are reserved for kernel-generated signals. */
#ifndef __SI_USER
#define __SI_ASYNCNL (-60) /* Sent by asynch name lookup completion. */
#define __SI_TKILL   (-6)  /* Sent by tkill. */
#define __SI_SIGIO   (-5)  /* Sent by queued SIGIO. */
#define __SI_ASYNCIO (-4)  /* Sent by AIO completion. */
#define __SI_MESGQ   (-3)  /* Sent by real time mesq state change. */
#define __SI_TIMER   (-2)  /* Sent by timer expiration. */
#define __SI_QUEUE   (-1)  /* Sent by sigqueue_entry. */
#define __SI_USER    0     /* Sent by kill, sigsend. */
#define __SI_KERNEL  0x80  /* Send by kernel. */
#endif /* !__SI_ASYNCNL */

/* `si_code' values for SIGILL signal. */
#ifndef __ILL_ILLOPC
#define __ILL_ILLOPC    1 /* Illegal opcode. */
#define __ILL_ILLOPN    2 /* Illegal operand. */
#define __ILL_ILLADR    3 /* Illegal addressing mode. */
#define __ILL_ILLTRP    4 /* Illegal trap. */
#define __ILL_PRVOPC    5 /* Privileged opcode. */
#define __ILL_PRVREG    6 /* Privileged register. */
#define __ILL_COPROC    7 /* Coprocessor error. */
#define __ILL_BADSTK    8 /* Internal stack error. */
#endif /* !__ILL_ILLOPC */

/* `si_code' values for SIGFPE signal. */
#ifndef __FPE_INTDIV
#define __FPE_INTDIV    1 /* Integer divide by zero. */
#define __FPE_INTOVF    2 /* Integer overflow. */
#define __FPE_FLTDIV    3 /* Floating point divide by zero. */
#define __FPE_FLTOVF    4 /* Floating point overflow. */
#define __FPE_FLTUND    5 /* Floating point underflow. */
#define __FPE_FLTRES    6 /* Floating point inexact result. */
#define __FPE_FLTINV    7 /* Floating point invalid operation. */
#define __FPE_FLTSUB    8 /* Subscript out of range. */
#endif /* !__FPE_INTDIV */

/* `si_code' values for SIGSEGV signal. */
#ifndef __SEGV_MAPERR
#define __SEGV_MAPERR 1 /* Address not mapped to object. */
#define __SEGV_ACCERR 2 /* Invalid permissions for mapped object. */
#endif /* !__SEGV_MAPERR */

/* `si_code' values for SIGBUS signal. */
#ifndef __BUS_ADRALN
#define __BUS_ADRALN    1 /* Invalid address alignment. */
#define __BUS_ADRERR    2 /* Non-existant physical address. */
#define __BUS_OBJERR    3 /* Object specific hardware error. */
#define __BUS_MCEERR_AR 4 /* Hardware memory error: action required. */
#define __BUS_MCEERR_AO 5 /* Hardware memory error: action optional. */
#endif /* !__BUS_ADRALN */

/* `si_code' values for SIGTRAP signal. */
#ifndef __TRAP_BRKPT
#define __TRAP_BRKPT 1 /* Process breakpoint. */
#define __TRAP_TRACE 2 /* Process trace trap. */
#endif /* !__TRAP_BRKPT */

/* `si_code' values for SIGCHLD signal. */
#ifndef __CLD_EXITED
#define __CLD_EXITED    1 /* Child has exited. */
#define __CLD_KILLED    2 /* Child was killed. */
#define __CLD_DUMPED    3 /* Child terminated abnormally. */
#define __CLD_TRAPPED   4 /* Traced child has trapped. */
#define __CLD_STOPPED   5 /* Child has stopped. */
#define __CLD_CONTINUED 6 /* Stopped child has continued. */
#endif /* !__CLD_EXITED */

/* `si_code' values for SIGPOLL signal. */
#ifndef __POLL_IN
#define __POLL_IN  1 /* Data input available. */
#define __POLL_OUT 2 /* Output buffers available. */
#define __POLL_MSG 3 /* Input message available.   */
#define __POLL_ERR 4 /* I/O error. */
#define __POLL_PRI 5 /* High priority input available. */
#define __POLL_HUP 6 /* Device disconnected. */
#endif /* !__POLL_IN */

#endif /* !_BITS_SIGINFO_VALUES_H */
