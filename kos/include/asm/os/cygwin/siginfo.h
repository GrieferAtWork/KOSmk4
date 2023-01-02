/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _ASM_OS_CYGWIN_SIGINFO_H
#define _ASM_OS_CYGWIN_SIGINFO_H 1

#include <__stdinc.h>

/************************************************************************/
/* CYGWIN                                                               */
/************************************************************************/

/* Values for `si_code'. */
#define __SI_USER    0  /* Sent by kill, sigsend. */
#define __SI_ASYNCIO 2  /* Sent by AIO completion. */
#define __SI_MESGQ   3  /* Sent by real time mesq state change. */
#define __SI_TIMER   4  /* Sent by timer expiration. */
#define __SI_QUEUE   5  /* Sent by sigqueue. */
#define __SI_KERNEL  6  /* Send by kernel. */

/* `si_code' values for SIGILL signal. */
#define __ILL_ILLOPC 7  /* Illegal opcode. */
#define __ILL_ILLOPN 8  /* Illegal operand. */
#define __ILL_ILLADR 9  /* Illegal addressing mode. */
#define __ILL_ILLTRP 10 /* Illegal trap. */
#define __ILL_PRVOPC 11 /* Privileged opcode. */
#define __ILL_PRVREG 12 /* Privileged register. */
#define __ILL_COPROC 13 /* Coprocessor error. */
#define __ILL_BADSTK 14 /* Internal stack error. */

/* `si_code' values for SIGFPE signal. */
#define __FPE_INTDIV 15 /* Integer divide by zero. */
#define __FPE_INTOVF 16 /* Integer overflow. */
#define __FPE_FLTDIV 17 /* Floating point divide by zero. */
#define __FPE_FLTOVF 18 /* Floating point overflow. */
#define __FPE_FLTUND 19 /* Floating point underflow. */
#define __FPE_FLTRES 20 /* Floating point inexact result. */
#define __FPE_FLTINV 21 /* Floating point invalid operation. */
#define __FPE_FLTSUB 22 /* Subscript out of range. */

/* `si_code' values for SIGSEGV signal. */
#define __SEGV_MAPERR 23 /* Address not mapped to object. */
#define __SEGV_ACCERR 24 /* Invalid permissions for mapped object. */

/* `si_code' values for SIGBUS signal. */
#define __BUS_ADRALN 25 /* Invalid address alignment. */
#define __BUS_ADRERR 26 /* Non-existent physical address. */
#define __BUS_OBJERR 27 /* Object specific hardware error. */

/* `si_code' values for SIGCHLD signal. */
#define __CLD_EXITED    28 /* Child has exited. */
#define __CLD_KILLED    29 /* Child was killed. */
#define __CLD_DUMPED    30 /* Child terminated abnormally. */
#define __CLD_TRAPPED   31 /* Traced child has trapped. */
#define __CLD_STOPPED   32 /* Child has stopped. */
#define __CLD_CONTINUED 33 /* Stopped child has continued. */

#endif /* !_ASM_OS_CYGWIN_SIGINFO_H */
