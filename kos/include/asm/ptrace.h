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
#ifndef _ASM_PTRACE_H
#define _ASM_PTRACE_H 1

#include <__crt.h>
#include <__stdinc.h>

/* Some documentation comments are taken from /usr/include/i386-linux-gnu/sys/ptrace.h on a linux machine.
 * The following copyright notice can be found at the top of that file: */
/* `ptrace' debugger support interface.  Linux version.
   Copyright (C) 1996-2016 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */


#if defined(__KOS__) || defined(__linux__) || defined(__CRT_KOS) || defined(__CRT_KOS_KERNEL) || defined(__CRT_GLC)
#define __PTRACE_TRACEME            0      /* Indicate that the process making this request should be traced. \
                                            * All signals received by this process can be intercepted by its  \
                                            * parent, and its parent can use the other `ptrace' requests. */
#define __PTRACE_PEEKTEXT           1      /* Return the word in the process's text space at address ADDR. */
#define __PTRACE_PEEKDATA           2      /* Return the word in the process's data space at address ADDR. */
#define __PTRACE_PEEKUSER           3      /* Return the word in the process's user area at offset ADDR. */
#define __PTRACE_POKETEXT           4      /* Write the word DATA into the process's text space at address ADDR. */
#define __PTRACE_POKEDATA           5      /* Write the word DATA into the process's data space at address ADDR. */
#define __PTRACE_POKEUSER           6      /* Write the word DATA into the process's user area at offset ADDR. */
#define __PTRACE_CONT               7      /* Continue the process. */
#define __PTRACE_KILL               8      /* Kill the process. */
#define __PTRACE_SINGLESTEP         9      /* Single step the process. This is not supported on all machines. */
#define __PTRACE_GETREGS            12     /* Get all general purpose registers used by a processes. This is not supported on all machines. */
#define __PTRACE_SETREGS            13     /* Set all general purpose registers used by a processes. This is not supported on all machines. */
#define __PTRACE_GETFPREGS          14     /* Get all floating point registers used by a processes. This is not supported on all machines. */
#define __PTRACE_SETFPREGS          15     /* Set all floating point registers used by a processes. This is not supported on all machines. */
#define __PTRACE_ATTACH             16     /* Attach to a process that is already running. */
#define __PTRACE_DETACH             17     /* Detach from a process attached to with PTRACE_ATTACH. */
#define __PTRACE_GETFPXREGS         18     /* Get all extended floating point registers used by a processes. This is not supported on all machines. */
#define __PTRACE_SETFPXREGS         19     /* Set all extended floating point registers used by a processes. This is not supported on all machines. */
#define __PTRACE_SYSCALL            24     /* Continue and stop at the next (return from) syscall. */
#define __PTRACE_SETOPTIONS         0x4200 /* Set ptrace filter options. */
#define __PTRACE_GETEVENTMSG        0x4201 /* Get last ptrace message. */
#define __PTRACE_GETSIGINFO         0x4202 /* Get siginfo for process. */
#define __PTRACE_SETSIGINFO         0x4203 /* Set new siginfo for process. */
#define __PTRACE_GETREGSET          0x4204 /* Get register content. */
#define __PTRACE_SETREGSET          0x4205 /* Set register content. */
#define __PTRACE_SEIZE              0x4206 /* Like PTRACE_ATTACH, but do not force tracee to trap and do not affect signal or group stop state. */
#define __PTRACE_INTERRUPT          0x4207 /* Trap seized tracee. */
#define __PTRACE_LISTEN             0x4208 /* Wait for next group event. */
#define __PTRACE_PEEKSIGINFO        0x4209 /* ... */
#define __PTRACE_GETSIGMASK         0x420a /* ... */
#define __PTRACE_SETSIGMASK         0x420b /* ... */
#define __PTRACE_SECCOMP_GET_FILTER 0x420c /* ... */

/* Flag for PTRACE_LISTEN. */
#define __PTRACE_SEIZE_DEVEL 0x80000000 /* ... */

/* Options set using PTRACE_SETOPTIONS. */
#define __PTRACE_O_TRACESYSGOOD    0x00000001 /* ... */
#define __PTRACE_O_TRACEFORK       0x00000002 /* ... */
#define __PTRACE_O_TRACEVFORK      0x00000004 /* ... */
#define __PTRACE_O_TRACECLONE      0x00000008 /* ... */
#define __PTRACE_O_TRACEEXEC       0x00000010 /* ... */
#define __PTRACE_O_TRACEVFORKDONE  0x00000020 /* ... */
#define __PTRACE_O_TRACEEXIT       0x00000040 /* ... */
#define __PTRACE_O_TRACESECCOMP    0x00000080 /* ... */
#define __PTRACE_O_EXITKILL        0x00100000 /* ... */
#define __PTRACE_O_SUSPEND_SECCOMP 0x00200000 /* ... */
#define __PTRACE_O_MASK            0x003000ff /* ... */

/* Wait extended result codes for the above trace options. */
#define __PTRACE_EVENT_FORK       1 /* ... */
#define __PTRACE_EVENT_VFORK      2 /* ... */
#define __PTRACE_EVENT_CLONE      3 /* ... */
#define __PTRACE_EVENT_EXEC       4 /* ... */
#define __PTRACE_EVENT_VFORK_DONE 5 /* ... */
#define __PTRACE_EVENT_EXIT       6 /* ... */
#define __PTRACE_EVENT_SECCOMP    7 /* ... */

#define __PTRACE_PEEKSIGINFO_SHARED 0x0001 /* Read signals from a shared (process wide) queue. */

#endif /* __KOS__ || __linux__ || __CRT_KOS || __CRT_KOS_KERNEL || __CRT_GLC */

#endif /* !_ASM_PTRACE_H */
