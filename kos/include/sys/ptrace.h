/* HASH CRC-32:0xfd88b376 */
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
#ifndef _SYS_PTRACE_H
#define _SYS_PTRACE_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>

#include <asm/ptrace.h>
#include <bits/types.h>
#include <bits/ptrace.h> /* `struct __ptrace_peeksiginfo_args' */

__SYSDECL_BEGIN

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


#if (defined(__PTRACE_TRACEME) || defined(__PTRACE_PEEKTEXT) ||       \
     defined(__PTRACE_PEEKDATA) || defined(__PTRACE_PEEKUSER) ||      \
     defined(__PTRACE_POKETEXT) || defined(__PTRACE_POKEDATA) ||      \
     defined(__PTRACE_POKEUSER) || defined(__PTRACE_CONT) ||          \
     defined(__PTRACE_KILL) || defined(__PTRACE_SINGLESTEP) ||        \
     defined(__PTRACE_GETREGS) || defined(__PTRACE_SETREGS) ||        \
     defined(__PTRACE_GETFPREGS) || defined(__PTRACE_SETFPREGS) ||    \
     defined(__PTRACE_ATTACH) || defined(__PTRACE_DETACH) ||          \
     defined(__PTRACE_GETFPXREGS) || defined(__PTRACE_SETFPXREGS) ||  \
     defined(__PTRACE_SYSCALL) || defined(__PTRACE_SETOPTIONS) ||     \
     defined(__PTRACE_GETEVENTMSG) || defined(__PTRACE_GETSIGINFO) || \
     defined(__PTRACE_SETSIGINFO) || defined(__PTRACE_GETREGSET) ||   \
     defined(__PTRACE_SETREGSET) || defined(__PTRACE_SEIZE) ||        \
     defined(__PTRACE_INTERRUPT) || defined(__PTRACE_LISTEN) ||       \
     defined(__PTRACE_PEEKSIGINFO) || defined(__PTRACE_GETSIGMASK) || \
     defined(__PTRACE_SETSIGMASK) || defined(__PTRACE_SECCOMP_GET_FILTER))
/* Type of the REQUEST argument to `ptrace.' */
/*[[[enum]]]*/
#ifdef __CC__
typedef enum __ptrace_request {
#ifdef __PTRACE_TRACEME
	PTRACE_TRACEME = __PTRACE_TRACEME, /* Indicate that the process making this request should be traced.
	                                    * All signals received by this process can be intercepted by its
	                                    * parent, and its parent can use the other `ptrace' requests. */
#endif /* __PTRACE_TRACEME */
#ifdef __PTRACE_PEEKTEXT
	PTRACE_PEEKTEXT = __PTRACE_PEEKTEXT, /* Return the word in the process's text space at address ADDR.  */
#endif /* __PTRACE_PEEKTEXT */
#ifdef __PTRACE_PEEKDATA
	PTRACE_PEEKDATA = __PTRACE_PEEKDATA, /* Return the word in the process's data space at address ADDR.  */
#endif /* __PTRACE_PEEKDATA */
#ifdef __PTRACE_PEEKUSER
	PTRACE_PEEKUSER = __PTRACE_PEEKUSER, /* Return the word in the process's user area at offset ADDR.  */
#endif /* __PTRACE_PEEKUSER */
#ifdef __PTRACE_POKETEXT
	PTRACE_POKETEXT = __PTRACE_POKETEXT, /* Write the word DATA into the process's text space at address ADDR.  */
#endif /* __PTRACE_POKETEXT */
#ifdef __PTRACE_POKEDATA
	PTRACE_POKEDATA = __PTRACE_POKEDATA, /* Write the word DATA into the process's data space at address ADDR.  */
#endif /* __PTRACE_POKEDATA */
#ifdef __PTRACE_POKEUSER
	PTRACE_POKEUSER = __PTRACE_POKEUSER, /* Write the word DATA into the process's user area at offset ADDR.  */
#endif /* __PTRACE_POKEUSER */
#ifdef __PTRACE_CONT
	PTRACE_CONT = __PTRACE_CONT, /* Continue the process.  */
#endif /* __PTRACE_CONT */
#ifdef __PTRACE_KILL
	PTRACE_KILL = __PTRACE_KILL, /* Kill the process.  */
#endif /* __PTRACE_KILL */
#ifdef __PTRACE_SINGLESTEP
	PTRACE_SINGLESTEP = __PTRACE_SINGLESTEP, /* Single step the process. This is not supported on all machines.  */
#endif /* __PTRACE_SINGLESTEP */
#ifdef __PTRACE_GETREGS
	PTRACE_GETREGS = __PTRACE_GETREGS, /* Get all general purpose registers used by a processes. This is not supported on all machines.  */
#endif /* __PTRACE_GETREGS */
#ifdef __PTRACE_SETREGS
	PTRACE_SETREGS = __PTRACE_SETREGS, /* Set all general purpose registers used by a processes. This is not supported on all machines.  */
#endif /* __PTRACE_SETREGS */
#ifdef __PTRACE_GETFPREGS
	PTRACE_GETFPREGS = __PTRACE_GETFPREGS, /* Get all floating point registers used by a processes. This is not supported on all machines.  */
#endif /* __PTRACE_GETFPREGS */
#ifdef __PTRACE_SETFPREGS
	PTRACE_SETFPREGS = __PTRACE_SETFPREGS, /* Set all floating point registers used by a processes. This is not supported on all machines.  */
#endif /* __PTRACE_SETFPREGS */
#ifdef __PTRACE_ATTACH
	PTRACE_ATTACH = __PTRACE_ATTACH, /* Attach to a process that is already running. */
#endif /* __PTRACE_ATTACH */
#ifdef __PTRACE_DETACH
	PTRACE_DETACH = __PTRACE_DETACH, /* Detach from a process attached to with PTRACE_ATTACH.  */
#endif /* __PTRACE_DETACH */
#ifdef __PTRACE_GETFPXREGS
	PTRACE_GETFPXREGS = __PTRACE_GETFPXREGS, /* Get all extended floating point registers used by a processes. This is not supported on all machines.  */
#endif /* __PTRACE_GETFPXREGS */
#ifdef __PTRACE_SETFPXREGS
	PTRACE_SETFPXREGS = __PTRACE_SETFPXREGS, /* Set all extended floating point registers used by a processes. This is not supported on all machines.  */
#endif /* __PTRACE_SETFPXREGS */
#ifdef __PTRACE_SYSCALL
	PTRACE_SYSCALL = __PTRACE_SYSCALL, /* Continue and stop at the next (return from) syscall.  */
#endif /* __PTRACE_SYSCALL */
#ifdef __PTRACE_SETOPTIONS
	PTRACE_SETOPTIONS = __PTRACE_SETOPTIONS, /* Set ptrace filter options.  */
#endif /* __PTRACE_SETOPTIONS */
#ifdef __PTRACE_GETEVENTMSG
	PTRACE_GETEVENTMSG = __PTRACE_GETEVENTMSG, /* Get last ptrace message.  */
#endif /* __PTRACE_GETEVENTMSG */
#ifdef __PTRACE_GETSIGINFO
	PTRACE_GETSIGINFO = __PTRACE_GETSIGINFO, /* Get siginfo for process.  */
#endif /* __PTRACE_GETSIGINFO */
#ifdef __PTRACE_SETSIGINFO
	PTRACE_SETSIGINFO = __PTRACE_SETSIGINFO, /* Set new siginfo for process.  */
#endif /* __PTRACE_SETSIGINFO */
#ifdef __PTRACE_GETREGSET
	PTRACE_GETREGSET = __PTRACE_GETREGSET, /* Get register content.  */
#endif /* __PTRACE_GETREGSET */
#ifdef __PTRACE_SETREGSET
	PTRACE_SETREGSET = __PTRACE_SETREGSET, /* Set register content.  */
#endif /* __PTRACE_SETREGSET */
#ifdef __PTRACE_SEIZE
	PTRACE_SEIZE = __PTRACE_SEIZE, /* Like PTRACE_ATTACH, but do not force tracee to trap and do not affect signal or group stop state.  */
#endif /* __PTRACE_SEIZE */
#ifdef __PTRACE_INTERRUPT
	PTRACE_INTERRUPT = __PTRACE_INTERRUPT, /* Trap seized tracee.  */
#endif /* __PTRACE_INTERRUPT */
#ifdef __PTRACE_LISTEN
	PTRACE_LISTEN = __PTRACE_LISTEN, /* Wait for next group event.  */
#endif /* __PTRACE_LISTEN */
#ifdef __PTRACE_PEEKSIGINFO
	PTRACE_PEEKSIGINFO = __PTRACE_PEEKSIGINFO,
#endif /* __PTRACE_PEEKSIGINFO */
#ifdef __PTRACE_GETSIGMASK
	PTRACE_GETSIGMASK = __PTRACE_GETSIGMASK,
#endif /* __PTRACE_GETSIGMASK */
#ifdef __PTRACE_SETSIGMASK
	PTRACE_SETSIGMASK = __PTRACE_SETSIGMASK,
#endif /* __PTRACE_SETSIGMASK */
#ifdef __PTRACE_SECCOMP_GET_FILTER
	PTRACE_SECCOMP_GET_FILTER = __PTRACE_SECCOMP_GET_FILTER,
#endif /* __PTRACE_SECCOMP_GET_FILTER */

#ifdef __PTRACE_TRACEME
	PT_TRACE_ME = __PTRACE_TRACEME, /* Indicate that the process making this request should be traced.
	                                 * All signals received by this process can be intercepted by its
	                                 * parent, and its parent can use the other `ptrace' requests. */
#endif /* __PTRACE_TRACEME */
#ifdef __PTRACE_PEEKTEXT
	PT_READ_I = __PTRACE_PEEKTEXT, /* Return the word in the process's text space at address ADDR.  */
#endif /* __PTRACE_PEEKTEXT */
#ifdef __PTRACE_PEEKDATA
	PT_READ_D = __PTRACE_PEEKDATA, /* Return the word in the process's data space at address ADDR.  */
#endif /* __PTRACE_PEEKDATA */
#ifdef __PTRACE_PEEKUSER
	PT_READ_U = __PTRACE_PEEKUSER, /* Return the word in the process's user area at offset ADDR.  */
#endif /* __PTRACE_PEEKUSER */
#ifdef __PTRACE_POKETEXT
	PT_WRITE_I = __PTRACE_POKETEXT, /* Write the word DATA into the process's text space at address ADDR.  */
#endif /* __PTRACE_POKETEXT */
#ifdef __PTRACE_POKEDATA
	PT_WRITE_D = __PTRACE_POKEDATA, /* Write the word DATA into the process's data space at address ADDR.  */
#endif /* __PTRACE_POKEDATA */
#ifdef __PTRACE_POKEUSER
	PT_WRITE_U = __PTRACE_POKEUSER, /* Write the word DATA into the process's user area at offset ADDR.  */
#endif /* __PTRACE_POKEUSER */
#ifdef __PTRACE_CONT
	PT_CONTINUE = __PTRACE_CONT, /* Continue the process.  */
#endif /* __PTRACE_CONT */
#ifdef __PTRACE_KILL
	PT_KILL = __PTRACE_KILL, /* Kill the process.  */
#endif /* __PTRACE_KILL */
#ifdef __PTRACE_SINGLESTEP
	PT_STEP = __PTRACE_SINGLESTEP, /* Single step the process. This is not supported on all machines.  */
#endif /* __PTRACE_SINGLESTEP */
#ifdef __PTRACE_GETREGS
	PT_GETREGS = __PTRACE_GETREGS, /* Get all general purpose registers used by a processes. This is not supported on all machines.  */
#endif /* __PTRACE_GETREGS */
#ifdef __PTRACE_SETREGS
	PT_SETREGS = __PTRACE_SETREGS, /* Set all general purpose registers used by a processes. This is not supported on all machines.  */
#endif /* __PTRACE_SETREGS */
#ifdef __PTRACE_GETFPREGS
	PT_GETFPREGS = __PTRACE_GETFPREGS, /* Get all floating point registers used by a processes. This is not supported on all machines.  */
#endif /* __PTRACE_GETFPREGS */
#ifdef __PTRACE_SETFPREGS
	PT_SETFPREGS = __PTRACE_SETFPREGS, /* Set all floating point registers used by a processes. This is not supported on all machines.  */
#endif /* __PTRACE_SETFPREGS */
#ifdef __PTRACE_ATTACH
	PT_ATTACH = __PTRACE_ATTACH, /* Attach to a process that is already running. */
#endif /* __PTRACE_ATTACH */
#ifdef __PTRACE_DETACH
	PT_DETACH = __PTRACE_DETACH, /* Detach from a process attached to with PTRACE_ATTACH.  */
#endif /* __PTRACE_DETACH */
#ifdef __PTRACE_GETFPXREGS
	PT_GETFPXREGS = __PTRACE_GETFPXREGS, /* Get all extended floating point registers used by a processes. This is not supported on all machines.  */
#endif /* __PTRACE_GETFPXREGS */
#ifdef __PTRACE_SETFPXREGS
	PT_SETFPXREGS = __PTRACE_SETFPXREGS, /* Set all extended floating point registers used by a processes. This is not supported on all machines.  */
#endif /* __PTRACE_SETFPXREGS */
#ifdef __PTRACE_SYSCALL
	PT_SYSCALL = __PTRACE_SYSCALL, /* Continue and stop at the next (return from) syscall.  */
#endif /* __PTRACE_SYSCALL */
#ifdef __PTRACE_SETOPTIONS
	PT_SETOPTIONS = __PTRACE_SETOPTIONS, /* Set ptrace filter options.  */
#endif /* __PTRACE_SETOPTIONS */
#ifdef __PTRACE_GETEVENTMSG
	PT_GETEVENTMSG = __PTRACE_GETEVENTMSG, /* Get last ptrace message.  */
#endif /* __PTRACE_GETEVENTMSG */
#ifdef __PTRACE_GETSIGINFO
	PT_GETSIGINFO = __PTRACE_GETSIGINFO, /* Get siginfo for process.  */
#endif /* __PTRACE_GETSIGINFO */
#ifdef __PTRACE_SETSIGINFO
	PT_SETSIGINFO = __PTRACE_SETSIGINFO, /* Set new siginfo for process.  */
#endif /* __PTRACE_SETSIGINFO */
} __ptrace_request_t;
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#ifdef __PTRACE_TRACEME
#define PTRACE_TRACEME            PTRACE_TRACEME            /* Indicate that the process making this request should be traced.
                                                             * All signals received by this process can be intercepted by its
                                                             * parent, and its parent can use the other `ptrace' requests. */
#endif /* __PTRACE_TRACEME */
#ifdef __PTRACE_PEEKTEXT
#define PTRACE_PEEKTEXT           PTRACE_PEEKTEXT           /* Return the word in the process's text space at address ADDR.  */
#endif /* __PTRACE_PEEKTEXT */
#ifdef __PTRACE_PEEKDATA
#define PTRACE_PEEKDATA           PTRACE_PEEKDATA           /* Return the word in the process's data space at address ADDR.  */
#endif /* __PTRACE_PEEKDATA */
#ifdef __PTRACE_PEEKUSER
#define PTRACE_PEEKUSER           PTRACE_PEEKUSER           /* Return the word in the process's user area at offset ADDR.  */
#endif /* __PTRACE_PEEKUSER */
#ifdef __PTRACE_POKETEXT
#define PTRACE_POKETEXT           PTRACE_POKETEXT           /* Write the word DATA into the process's text space at address ADDR.  */
#endif /* __PTRACE_POKETEXT */
#ifdef __PTRACE_POKEDATA
#define PTRACE_POKEDATA           PTRACE_POKEDATA           /* Write the word DATA into the process's data space at address ADDR.  */
#endif /* __PTRACE_POKEDATA */
#ifdef __PTRACE_POKEUSER
#define PTRACE_POKEUSER           PTRACE_POKEUSER           /* Write the word DATA into the process's user area at offset ADDR.  */
#endif /* __PTRACE_POKEUSER */
#ifdef __PTRACE_CONT
#define PTRACE_CONT               PTRACE_CONT               /* Continue the process.  */
#endif /* __PTRACE_CONT */
#ifdef __PTRACE_KILL
#define PTRACE_KILL               PTRACE_KILL               /* Kill the process.  */
#endif /* __PTRACE_KILL */
#ifdef __PTRACE_SINGLESTEP
#define PTRACE_SINGLESTEP         PTRACE_SINGLESTEP         /* Single step the process. This is not supported on all machines.  */
#endif /* __PTRACE_SINGLESTEP */
#ifdef __PTRACE_GETREGS
#define PTRACE_GETREGS            PTRACE_GETREGS            /* Get all general purpose registers used by a processes. This is not supported on all machines.  */
#endif /* __PTRACE_GETREGS */
#ifdef __PTRACE_SETREGS
#define PTRACE_SETREGS            PTRACE_SETREGS            /* Set all general purpose registers used by a processes. This is not supported on all machines.  */
#endif /* __PTRACE_SETREGS */
#ifdef __PTRACE_GETFPREGS
#define PTRACE_GETFPREGS          PTRACE_GETFPREGS          /* Get all floating point registers used by a processes. This is not supported on all machines.  */
#endif /* __PTRACE_GETFPREGS */
#ifdef __PTRACE_SETFPREGS
#define PTRACE_SETFPREGS          PTRACE_SETFPREGS          /* Set all floating point registers used by a processes. This is not supported on all machines.  */
#endif /* __PTRACE_SETFPREGS */
#ifdef __PTRACE_ATTACH
#define PTRACE_ATTACH             PTRACE_ATTACH             /* Attach to a process that is already running. */
#endif /* __PTRACE_ATTACH */
#ifdef __PTRACE_DETACH
#define PTRACE_DETACH             PTRACE_DETACH             /* Detach from a process attached to with PTRACE_ATTACH.  */
#endif /* __PTRACE_DETACH */
#ifdef __PTRACE_GETFPXREGS
#define PTRACE_GETFPXREGS         PTRACE_GETFPXREGS         /* Get all extended floating point registers used by a processes. This is not supported on all machines.  */
#endif /* __PTRACE_GETFPXREGS */
#ifdef __PTRACE_SETFPXREGS
#define PTRACE_SETFPXREGS         PTRACE_SETFPXREGS         /* Set all extended floating point registers used by a processes. This is not supported on all machines.  */
#endif /* __PTRACE_SETFPXREGS */
#ifdef __PTRACE_SYSCALL
#define PTRACE_SYSCALL            PTRACE_SYSCALL            /* Continue and stop at the next (return from) syscall.  */
#endif /* __PTRACE_SYSCALL */
#ifdef __PTRACE_SETOPTIONS
#define PTRACE_SETOPTIONS         PTRACE_SETOPTIONS         /* Set ptrace filter options.  */
#endif /* __PTRACE_SETOPTIONS */
#ifdef __PTRACE_GETEVENTMSG
#define PTRACE_GETEVENTMSG        PTRACE_GETEVENTMSG        /* Get last ptrace message.  */
#endif /* __PTRACE_GETEVENTMSG */
#ifdef __PTRACE_GETSIGINFO
#define PTRACE_GETSIGINFO         PTRACE_GETSIGINFO         /* Get siginfo for process.  */
#endif /* __PTRACE_GETSIGINFO */
#ifdef __PTRACE_SETSIGINFO
#define PTRACE_SETSIGINFO         PTRACE_SETSIGINFO         /* Set new siginfo for process.  */
#endif /* __PTRACE_SETSIGINFO */
#ifdef __PTRACE_GETREGSET
#define PTRACE_GETREGSET          PTRACE_GETREGSET          /* Get register content.  */
#endif /* __PTRACE_GETREGSET */
#ifdef __PTRACE_SETREGSET
#define PTRACE_SETREGSET          PTRACE_SETREGSET          /* Set register content.  */
#endif /* __PTRACE_SETREGSET */
#ifdef __PTRACE_SEIZE
#define PTRACE_SEIZE              PTRACE_SEIZE              /* Like PTRACE_ATTACH, but do not force tracee to trap and do not affect signal or group stop state.  */
#endif /* __PTRACE_SEIZE */
#ifdef __PTRACE_INTERRUPT
#define PTRACE_INTERRUPT          PTRACE_INTERRUPT          /* Trap seized tracee.  */
#endif /* __PTRACE_INTERRUPT */
#ifdef __PTRACE_LISTEN
#define PTRACE_LISTEN             PTRACE_LISTEN             /* Wait for next group event.  */
#endif /* __PTRACE_LISTEN */
#ifdef __PTRACE_PEEKSIGINFO
#define PTRACE_PEEKSIGINFO        PTRACE_PEEKSIGINFO
#endif /* __PTRACE_PEEKSIGINFO */
#ifdef __PTRACE_GETSIGMASK
#define PTRACE_GETSIGMASK         PTRACE_GETSIGMASK
#endif /* __PTRACE_GETSIGMASK */
#ifdef __PTRACE_SETSIGMASK
#define PTRACE_SETSIGMASK         PTRACE_SETSIGMASK
#endif /* __PTRACE_SETSIGMASK */
#ifdef __PTRACE_SECCOMP_GET_FILTER
#define PTRACE_SECCOMP_GET_FILTER PTRACE_SECCOMP_GET_FILTER
#endif /* __PTRACE_SECCOMP_GET_FILTER */

#ifdef __PTRACE_TRACEME
#define PT_TRACE_ME               PT_TRACE_ME               /* Indicate that the process making this request should be traced.
                                                             * All signals received by this process can be intercepted by its
                                                             * parent, and its parent can use the other `ptrace' requests. */
#endif /* __PTRACE_TRACEME */
#ifdef __PTRACE_PEEKTEXT
#define PT_READ_I                 PT_READ_I                 /* Return the word in the process's text space at address ADDR.  */
#endif /* __PTRACE_PEEKTEXT */
#ifdef __PTRACE_PEEKDATA
#define PT_READ_D                 PT_READ_D                 /* Return the word in the process's data space at address ADDR.  */
#endif /* __PTRACE_PEEKDATA */
#ifdef __PTRACE_PEEKUSER
#define PT_READ_U                 PT_READ_U                 /* Return the word in the process's user area at offset ADDR.  */
#endif /* __PTRACE_PEEKUSER */
#ifdef __PTRACE_POKETEXT
#define PT_WRITE_I                PT_WRITE_I                /* Write the word DATA into the process's text space at address ADDR.  */
#endif /* __PTRACE_POKETEXT */
#ifdef __PTRACE_POKEDATA
#define PT_WRITE_D                PT_WRITE_D                /* Write the word DATA into the process's data space at address ADDR.  */
#endif /* __PTRACE_POKEDATA */
#ifdef __PTRACE_POKEUSER
#define PT_WRITE_U                PT_WRITE_U                /* Write the word DATA into the process's user area at offset ADDR.  */
#endif /* __PTRACE_POKEUSER */
#ifdef __PTRACE_CONT
#define PT_CONTINUE               PT_CONTINUE               /* Continue the process.  */
#endif /* __PTRACE_CONT */
#ifdef __PTRACE_KILL
#define PT_KILL                   PT_KILL                   /* Kill the process.  */
#endif /* __PTRACE_KILL */
#ifdef __PTRACE_SINGLESTEP
#define PT_STEP                   PT_STEP                   /* Single step the process. This is not supported on all machines.  */
#endif /* __PTRACE_SINGLESTEP */
#ifdef __PTRACE_GETREGS
#define PT_GETREGS                PT_GETREGS                /* Get all general purpose registers used by a processes. This is not supported on all machines.  */
#endif /* __PTRACE_GETREGS */
#ifdef __PTRACE_SETREGS
#define PT_SETREGS                PT_SETREGS                /* Set all general purpose registers used by a processes. This is not supported on all machines.  */
#endif /* __PTRACE_SETREGS */
#ifdef __PTRACE_GETFPREGS
#define PT_GETFPREGS              PT_GETFPREGS              /* Get all floating point registers used by a processes. This is not supported on all machines.  */
#endif /* __PTRACE_GETFPREGS */
#ifdef __PTRACE_SETFPREGS
#define PT_SETFPREGS              PT_SETFPREGS              /* Set all floating point registers used by a processes. This is not supported on all machines.  */
#endif /* __PTRACE_SETFPREGS */
#ifdef __PTRACE_ATTACH
#define PT_ATTACH                 PT_ATTACH                 /* Attach to a process that is already running. */
#endif /* __PTRACE_ATTACH */
#ifdef __PTRACE_DETACH
#define PT_DETACH                 PT_DETACH                 /* Detach from a process attached to with PTRACE_ATTACH.  */
#endif /* __PTRACE_DETACH */
#ifdef __PTRACE_GETFPXREGS
#define PT_GETFPXREGS             PT_GETFPXREGS             /* Get all extended floating point registers used by a processes. This is not supported on all machines.  */
#endif /* __PTRACE_GETFPXREGS */
#ifdef __PTRACE_SETFPXREGS
#define PT_SETFPXREGS             PT_SETFPXREGS             /* Set all extended floating point registers used by a processes. This is not supported on all machines.  */
#endif /* __PTRACE_SETFPXREGS */
#ifdef __PTRACE_SYSCALL
#define PT_SYSCALL                PT_SYSCALL                /* Continue and stop at the next (return from) syscall.  */
#endif /* __PTRACE_SYSCALL */
#ifdef __PTRACE_SETOPTIONS
#define PT_SETOPTIONS             PT_SETOPTIONS             /* Set ptrace filter options.  */
#endif /* __PTRACE_SETOPTIONS */
#ifdef __PTRACE_GETEVENTMSG
#define PT_GETEVENTMSG            PT_GETEVENTMSG            /* Get last ptrace message.  */
#endif /* __PTRACE_GETEVENTMSG */
#ifdef __PTRACE_GETSIGINFO
#define PT_GETSIGINFO             PT_GETSIGINFO             /* Get siginfo for process.  */
#endif /* __PTRACE_GETSIGINFO */
#ifdef __PTRACE_SETSIGINFO
#define PT_SETSIGINFO             PT_SETSIGINFO             /* Set new siginfo for process.  */
#endif /* __PTRACE_SETSIGINFO */
#else /* __COMPILER_PREFERR_ENUMS */
#ifdef __PTRACE_TRACEME
#define PTRACE_TRACEME            __PTRACE_TRACEME            /* Indicate that the process making this request should be traced.
                                                               * All signals received by this process can be intercepted by its
                                                               * parent, and its parent can use the other `ptrace' requests. */
#endif /* __PTRACE_TRACEME */
#ifdef __PTRACE_PEEKTEXT
#define PTRACE_PEEKTEXT           __PTRACE_PEEKTEXT           /* Return the word in the process's text space at address ADDR.  */
#endif /* __PTRACE_PEEKTEXT */
#ifdef __PTRACE_PEEKDATA
#define PTRACE_PEEKDATA           __PTRACE_PEEKDATA           /* Return the word in the process's data space at address ADDR.  */
#endif /* __PTRACE_PEEKDATA */
#ifdef __PTRACE_PEEKUSER
#define PTRACE_PEEKUSER           __PTRACE_PEEKUSER           /* Return the word in the process's user area at offset ADDR.  */
#endif /* __PTRACE_PEEKUSER */
#ifdef __PTRACE_POKETEXT
#define PTRACE_POKETEXT           __PTRACE_POKETEXT           /* Write the word DATA into the process's text space at address ADDR.  */
#endif /* __PTRACE_POKETEXT */
#ifdef __PTRACE_POKEDATA
#define PTRACE_POKEDATA           __PTRACE_POKEDATA           /* Write the word DATA into the process's data space at address ADDR.  */
#endif /* __PTRACE_POKEDATA */
#ifdef __PTRACE_POKEUSER
#define PTRACE_POKEUSER           __PTRACE_POKEUSER           /* Write the word DATA into the process's user area at offset ADDR.  */
#endif /* __PTRACE_POKEUSER */
#ifdef __PTRACE_CONT
#define PTRACE_CONT               __PTRACE_CONT               /* Continue the process.  */
#endif /* __PTRACE_CONT */
#ifdef __PTRACE_KILL
#define PTRACE_KILL               __PTRACE_KILL               /* Kill the process.  */
#endif /* __PTRACE_KILL */
#ifdef __PTRACE_SINGLESTEP
#define PTRACE_SINGLESTEP         __PTRACE_SINGLESTEP         /* Single step the process. This is not supported on all machines.  */
#endif /* __PTRACE_SINGLESTEP */
#ifdef __PTRACE_GETREGS
#define PTRACE_GETREGS            __PTRACE_GETREGS            /* Get all general purpose registers used by a processes. This is not supported on all machines.  */
#endif /* __PTRACE_GETREGS */
#ifdef __PTRACE_SETREGS
#define PTRACE_SETREGS            __PTRACE_SETREGS            /* Set all general purpose registers used by a processes. This is not supported on all machines.  */
#endif /* __PTRACE_SETREGS */
#ifdef __PTRACE_GETFPREGS
#define PTRACE_GETFPREGS          __PTRACE_GETFPREGS          /* Get all floating point registers used by a processes. This is not supported on all machines.  */
#endif /* __PTRACE_GETFPREGS */
#ifdef __PTRACE_SETFPREGS
#define PTRACE_SETFPREGS          __PTRACE_SETFPREGS          /* Set all floating point registers used by a processes. This is not supported on all machines.  */
#endif /* __PTRACE_SETFPREGS */
#ifdef __PTRACE_ATTACH
#define PTRACE_ATTACH             __PTRACE_ATTACH             /* Attach to a process that is already running. */
#endif /* __PTRACE_ATTACH */
#ifdef __PTRACE_DETACH
#define PTRACE_DETACH             __PTRACE_DETACH             /* Detach from a process attached to with PTRACE_ATTACH.  */
#endif /* __PTRACE_DETACH */
#ifdef __PTRACE_GETFPXREGS
#define PTRACE_GETFPXREGS         __PTRACE_GETFPXREGS         /* Get all extended floating point registers used by a processes. This is not supported on all machines.  */
#endif /* __PTRACE_GETFPXREGS */
#ifdef __PTRACE_SETFPXREGS
#define PTRACE_SETFPXREGS         __PTRACE_SETFPXREGS         /* Set all extended floating point registers used by a processes. This is not supported on all machines.  */
#endif /* __PTRACE_SETFPXREGS */
#ifdef __PTRACE_SYSCALL
#define PTRACE_SYSCALL            __PTRACE_SYSCALL            /* Continue and stop at the next (return from) syscall.  */
#endif /* __PTRACE_SYSCALL */
#ifdef __PTRACE_SETOPTIONS
#define PTRACE_SETOPTIONS         __PTRACE_SETOPTIONS         /* Set ptrace filter options.  */
#endif /* __PTRACE_SETOPTIONS */
#ifdef __PTRACE_GETEVENTMSG
#define PTRACE_GETEVENTMSG        __PTRACE_GETEVENTMSG        /* Get last ptrace message.  */
#endif /* __PTRACE_GETEVENTMSG */
#ifdef __PTRACE_GETSIGINFO
#define PTRACE_GETSIGINFO         __PTRACE_GETSIGINFO         /* Get siginfo for process.  */
#endif /* __PTRACE_GETSIGINFO */
#ifdef __PTRACE_SETSIGINFO
#define PTRACE_SETSIGINFO         __PTRACE_SETSIGINFO         /* Set new siginfo for process.  */
#endif /* __PTRACE_SETSIGINFO */
#ifdef __PTRACE_GETREGSET
#define PTRACE_GETREGSET          __PTRACE_GETREGSET          /* Get register content.  */
#endif /* __PTRACE_GETREGSET */
#ifdef __PTRACE_SETREGSET
#define PTRACE_SETREGSET          __PTRACE_SETREGSET          /* Set register content.  */
#endif /* __PTRACE_SETREGSET */
#ifdef __PTRACE_SEIZE
#define PTRACE_SEIZE              __PTRACE_SEIZE              /* Like PTRACE_ATTACH, but do not force tracee to trap and do not affect signal or group stop state.  */
#endif /* __PTRACE_SEIZE */
#ifdef __PTRACE_INTERRUPT
#define PTRACE_INTERRUPT          __PTRACE_INTERRUPT          /* Trap seized tracee.  */
#endif /* __PTRACE_INTERRUPT */
#ifdef __PTRACE_LISTEN
#define PTRACE_LISTEN             __PTRACE_LISTEN             /* Wait for next group event.  */
#endif /* __PTRACE_LISTEN */
#ifdef __PTRACE_PEEKSIGINFO
#define PTRACE_PEEKSIGINFO        __PTRACE_PEEKSIGINFO
#endif /* __PTRACE_PEEKSIGINFO */
#ifdef __PTRACE_GETSIGMASK
#define PTRACE_GETSIGMASK         __PTRACE_GETSIGMASK
#endif /* __PTRACE_GETSIGMASK */
#ifdef __PTRACE_SETSIGMASK
#define PTRACE_SETSIGMASK         __PTRACE_SETSIGMASK
#endif /* __PTRACE_SETSIGMASK */
#ifdef __PTRACE_SECCOMP_GET_FILTER
#define PTRACE_SECCOMP_GET_FILTER __PTRACE_SECCOMP_GET_FILTER
#endif /* __PTRACE_SECCOMP_GET_FILTER */

#ifdef __PTRACE_TRACEME
#define PT_TRACE_ME               __PTRACE_TRACEME            /* Indicate that the process making this request should be traced.
                                                               * All signals received by this process can be intercepted by its
                                                               * parent, and its parent can use the other `ptrace' requests. */
#endif /* __PTRACE_TRACEME */
#ifdef __PTRACE_PEEKTEXT
#define PT_READ_I                 __PTRACE_PEEKTEXT           /* Return the word in the process's text space at address ADDR.  */
#endif /* __PTRACE_PEEKTEXT */
#ifdef __PTRACE_PEEKDATA
#define PT_READ_D                 __PTRACE_PEEKDATA           /* Return the word in the process's data space at address ADDR.  */
#endif /* __PTRACE_PEEKDATA */
#ifdef __PTRACE_PEEKUSER
#define PT_READ_U                 __PTRACE_PEEKUSER           /* Return the word in the process's user area at offset ADDR.  */
#endif /* __PTRACE_PEEKUSER */
#ifdef __PTRACE_POKETEXT
#define PT_WRITE_I                __PTRACE_POKETEXT           /* Write the word DATA into the process's text space at address ADDR.  */
#endif /* __PTRACE_POKETEXT */
#ifdef __PTRACE_POKEDATA
#define PT_WRITE_D                __PTRACE_POKEDATA           /* Write the word DATA into the process's data space at address ADDR.  */
#endif /* __PTRACE_POKEDATA */
#ifdef __PTRACE_POKEUSER
#define PT_WRITE_U                __PTRACE_POKEUSER           /* Write the word DATA into the process's user area at offset ADDR.  */
#endif /* __PTRACE_POKEUSER */
#ifdef __PTRACE_CONT
#define PT_CONTINUE               __PTRACE_CONT               /* Continue the process.  */
#endif /* __PTRACE_CONT */
#ifdef __PTRACE_KILL
#define PT_KILL                   __PTRACE_KILL               /* Kill the process.  */
#endif /* __PTRACE_KILL */
#ifdef __PTRACE_SINGLESTEP
#define PT_STEP                   __PTRACE_SINGLESTEP         /* Single step the process. This is not supported on all machines.  */
#endif /* __PTRACE_SINGLESTEP */
#ifdef __PTRACE_GETREGS
#define PT_GETREGS                __PTRACE_GETREGS            /* Get all general purpose registers used by a processes. This is not supported on all machines.  */
#endif /* __PTRACE_GETREGS */
#ifdef __PTRACE_SETREGS
#define PT_SETREGS                __PTRACE_SETREGS            /* Set all general purpose registers used by a processes. This is not supported on all machines.  */
#endif /* __PTRACE_SETREGS */
#ifdef __PTRACE_GETFPREGS
#define PT_GETFPREGS              __PTRACE_GETFPREGS          /* Get all floating point registers used by a processes. This is not supported on all machines.  */
#endif /* __PTRACE_GETFPREGS */
#ifdef __PTRACE_SETFPREGS
#define PT_SETFPREGS              __PTRACE_SETFPREGS          /* Set all floating point registers used by a processes. This is not supported on all machines.  */
#endif /* __PTRACE_SETFPREGS */
#ifdef __PTRACE_ATTACH
#define PT_ATTACH                 __PTRACE_ATTACH             /* Attach to a process that is already running. */
#endif /* __PTRACE_ATTACH */
#ifdef __PTRACE_DETACH
#define PT_DETACH                 __PTRACE_DETACH             /* Detach from a process attached to with PTRACE_ATTACH.  */
#endif /* __PTRACE_DETACH */
#ifdef __PTRACE_GETFPXREGS
#define PT_GETFPXREGS             __PTRACE_GETFPXREGS         /* Get all extended floating point registers used by a processes. This is not supported on all machines.  */
#endif /* __PTRACE_GETFPXREGS */
#ifdef __PTRACE_SETFPXREGS
#define PT_SETFPXREGS             __PTRACE_SETFPXREGS         /* Set all extended floating point registers used by a processes. This is not supported on all machines.  */
#endif /* __PTRACE_SETFPXREGS */
#ifdef __PTRACE_SYSCALL
#define PT_SYSCALL                __PTRACE_SYSCALL            /* Continue and stop at the next (return from) syscall.  */
#endif /* __PTRACE_SYSCALL */
#ifdef __PTRACE_SETOPTIONS
#define PT_SETOPTIONS             __PTRACE_SETOPTIONS         /* Set ptrace filter options.  */
#endif /* __PTRACE_SETOPTIONS */
#ifdef __PTRACE_GETEVENTMSG
#define PT_GETEVENTMSG            __PTRACE_GETEVENTMSG        /* Get last ptrace message.  */
#endif /* __PTRACE_GETEVENTMSG */
#ifdef __PTRACE_GETSIGINFO
#define PT_GETSIGINFO             __PTRACE_GETSIGINFO         /* Get siginfo for process.  */
#endif /* __PTRACE_GETSIGINFO */
#ifdef __PTRACE_SETSIGINFO
#define PT_SETSIGINFO             __PTRACE_SETSIGINFO         /* Set new siginfo for process.  */
#endif /* __PTRACE_SETSIGINFO */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/
#elif defined(__CC__)
typedef int __ptrace_request_t;
#endif /* ... */


#ifdef __PTRACE_SEIZE_DEVEL
/* Flag for PTRACE_LISTEN. */
/*[[[enum]]]*/
#ifdef __CC__
enum __ptrace_flags {
#ifdef __PTRACE_SEIZE_DEVEL
	PTRACE_SEIZE_DEVEL = __PTRACE_SEIZE_DEVEL
#endif /* __PTRACE_SEIZE_DEVEL */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#ifdef __PTRACE_SEIZE_DEVEL
#define PTRACE_SEIZE_DEVEL PTRACE_SEIZE_DEVEL
#endif /* __PTRACE_SEIZE_DEVEL */
#else /* __COMPILER_PREFERR_ENUMS */
#ifdef __PTRACE_SEIZE_DEVEL
#define PTRACE_SEIZE_DEVEL __PTRACE_SEIZE_DEVEL
#endif /* __PTRACE_SEIZE_DEVEL */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/
#endif /* ... */


#if (defined(__PTRACE_O_TRACESYSGOOD) || defined(__PTRACE_O_TRACEFORK) ||   \
     defined(__PTRACE_O_TRACEVFORK) || defined(__PTRACE_O_TRACECLONE) ||    \
     defined(__PTRACE_O_TRACEEXEC) || defined(__PTRACE_O_TRACEVFORKDONE) || \
     defined(__PTRACE_O_TRACEEXIT) || defined(__PTRACE_O_TRACESECCOMP) ||   \
     defined(__PTRACE_O_EXITKILL) || defined(__PTRACE_O_SUSPEND_SECCOMP) || \
     defined(__PTRACE_O_MASK))
/* Options set using PTRACE_SETOPTIONS. */
/*[[[enum]]]*/
#ifdef __CC__
enum __ptrace_setoptions {
#ifdef __PTRACE_O_TRACESYSGOOD
	PTRACE_O_TRACESYSGOOD = __PTRACE_O_TRACESYSGOOD, /* ... */
#endif /* __PTRACE_O_TRACESYSGOOD */
#ifdef __PTRACE_O_TRACEFORK
	PTRACE_O_TRACEFORK = __PTRACE_O_TRACEFORK, /* ... */
#endif /* __PTRACE_O_TRACEFORK */
#ifdef __PTRACE_O_TRACEVFORK
	PTRACE_O_TRACEVFORK = __PTRACE_O_TRACEVFORK, /* ... */
#endif /* __PTRACE_O_TRACEVFORK */
#ifdef __PTRACE_O_TRACECLONE
	PTRACE_O_TRACECLONE = __PTRACE_O_TRACECLONE, /* ... */
#endif /* __PTRACE_O_TRACECLONE */
#ifdef __PTRACE_O_TRACEEXEC
	PTRACE_O_TRACEEXEC = __PTRACE_O_TRACEEXEC, /* ... */
#endif /* __PTRACE_O_TRACEEXEC */
#ifdef __PTRACE_O_TRACEVFORKDONE
	PTRACE_O_TRACEVFORKDONE = __PTRACE_O_TRACEVFORKDONE, /* ... */
#endif /* __PTRACE_O_TRACEVFORKDONE */
#ifdef __PTRACE_O_TRACEEXIT
	PTRACE_O_TRACEEXIT = __PTRACE_O_TRACEEXIT, /* ... */
#endif /* __PTRACE_O_TRACEEXIT */
#ifdef __PTRACE_O_TRACESECCOMP
	PTRACE_O_TRACESECCOMP = __PTRACE_O_TRACESECCOMP, /* ... */
#endif /* __PTRACE_O_TRACESECCOMP */
#ifdef __PTRACE_O_EXITKILL
	PTRACE_O_EXITKILL = __PTRACE_O_EXITKILL, /* ... */
#endif /* __PTRACE_O_EXITKILL */
#ifdef __PTRACE_O_SUSPEND_SECCOMP
	PTRACE_O_SUSPEND_SECCOMP = __PTRACE_O_SUSPEND_SECCOMP, /* ... */
#endif /* __PTRACE_O_SUSPEND_SECCOMP */
#ifdef __PTRACE_O_MASK
	PTRACE_O_MASK = __PTRACE_O_MASK /* ... */
#endif /* __PTRACE_O_MASK */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#ifdef __PTRACE_O_TRACESYSGOOD
#define PTRACE_O_TRACESYSGOOD    PTRACE_O_TRACESYSGOOD    /* ... */
#endif /* __PTRACE_O_TRACESYSGOOD */
#ifdef __PTRACE_O_TRACEFORK
#define PTRACE_O_TRACEFORK       PTRACE_O_TRACEFORK       /* ... */
#endif /* __PTRACE_O_TRACEFORK */
#ifdef __PTRACE_O_TRACEVFORK
#define PTRACE_O_TRACEVFORK      PTRACE_O_TRACEVFORK      /* ... */
#endif /* __PTRACE_O_TRACEVFORK */
#ifdef __PTRACE_O_TRACECLONE
#define PTRACE_O_TRACECLONE      PTRACE_O_TRACECLONE      /* ... */
#endif /* __PTRACE_O_TRACECLONE */
#ifdef __PTRACE_O_TRACEEXEC
#define PTRACE_O_TRACEEXEC       PTRACE_O_TRACEEXEC       /* ... */
#endif /* __PTRACE_O_TRACEEXEC */
#ifdef __PTRACE_O_TRACEVFORKDONE
#define PTRACE_O_TRACEVFORKDONE  PTRACE_O_TRACEVFORKDONE  /* ... */
#endif /* __PTRACE_O_TRACEVFORKDONE */
#ifdef __PTRACE_O_TRACEEXIT
#define PTRACE_O_TRACEEXIT       PTRACE_O_TRACEEXIT       /* ... */
#endif /* __PTRACE_O_TRACEEXIT */
#ifdef __PTRACE_O_TRACESECCOMP
#define PTRACE_O_TRACESECCOMP    PTRACE_O_TRACESECCOMP    /* ... */
#endif /* __PTRACE_O_TRACESECCOMP */
#ifdef __PTRACE_O_EXITKILL
#define PTRACE_O_EXITKILL        PTRACE_O_EXITKILL        /* ... */
#endif /* __PTRACE_O_EXITKILL */
#ifdef __PTRACE_O_SUSPEND_SECCOMP
#define PTRACE_O_SUSPEND_SECCOMP PTRACE_O_SUSPEND_SECCOMP /* ... */
#endif /* __PTRACE_O_SUSPEND_SECCOMP */
#ifdef __PTRACE_O_MASK
#define PTRACE_O_MASK            PTRACE_O_MASK            /* ... */
#endif /* __PTRACE_O_MASK */
#else /* __COMPILER_PREFERR_ENUMS */
#ifdef __PTRACE_O_TRACESYSGOOD
#define PTRACE_O_TRACESYSGOOD    __PTRACE_O_TRACESYSGOOD    /* ... */
#endif /* __PTRACE_O_TRACESYSGOOD */
#ifdef __PTRACE_O_TRACEFORK
#define PTRACE_O_TRACEFORK       __PTRACE_O_TRACEFORK       /* ... */
#endif /* __PTRACE_O_TRACEFORK */
#ifdef __PTRACE_O_TRACEVFORK
#define PTRACE_O_TRACEVFORK      __PTRACE_O_TRACEVFORK      /* ... */
#endif /* __PTRACE_O_TRACEVFORK */
#ifdef __PTRACE_O_TRACECLONE
#define PTRACE_O_TRACECLONE      __PTRACE_O_TRACECLONE      /* ... */
#endif /* __PTRACE_O_TRACECLONE */
#ifdef __PTRACE_O_TRACEEXEC
#define PTRACE_O_TRACEEXEC       __PTRACE_O_TRACEEXEC       /* ... */
#endif /* __PTRACE_O_TRACEEXEC */
#ifdef __PTRACE_O_TRACEVFORKDONE
#define PTRACE_O_TRACEVFORKDONE  __PTRACE_O_TRACEVFORKDONE  /* ... */
#endif /* __PTRACE_O_TRACEVFORKDONE */
#ifdef __PTRACE_O_TRACEEXIT
#define PTRACE_O_TRACEEXIT       __PTRACE_O_TRACEEXIT       /* ... */
#endif /* __PTRACE_O_TRACEEXIT */
#ifdef __PTRACE_O_TRACESECCOMP
#define PTRACE_O_TRACESECCOMP    __PTRACE_O_TRACESECCOMP    /* ... */
#endif /* __PTRACE_O_TRACESECCOMP */
#ifdef __PTRACE_O_EXITKILL
#define PTRACE_O_EXITKILL        __PTRACE_O_EXITKILL        /* ... */
#endif /* __PTRACE_O_EXITKILL */
#ifdef __PTRACE_O_SUSPEND_SECCOMP
#define PTRACE_O_SUSPEND_SECCOMP __PTRACE_O_SUSPEND_SECCOMP /* ... */
#endif /* __PTRACE_O_SUSPEND_SECCOMP */
#ifdef __PTRACE_O_MASK
#define PTRACE_O_MASK            __PTRACE_O_MASK            /* ... */
#endif /* __PTRACE_O_MASK */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/
#endif /* .. */


#if (defined(__PTRACE_EVENT_FORK) || defined(__PTRACE_EVENT_VFORK) ||      \
     defined(__PTRACE_EVENT_CLONE) || defined(__PTRACE_EVENT_EXEC) ||      \
     defined(__PTRACE_EVENT_VFORK_DONE) || defined(__PTRACE_EVENT_EXIT) || \
     defined(__PTRACE_EVENT_SECCOMP))
/* Wait extended result codes for the above trace options. */
/*[[[enum]]]*/
#ifdef __CC__
enum __ptrace_eventcodes {
#ifdef __PTRACE_EVENT_FORK
	PTRACE_EVENT_FORK = __PTRACE_EVENT_FORK, /* ... */
#endif /* __PTRACE_EVENT_FORK */
#ifdef __PTRACE_EVENT_VFORK
	PTRACE_EVENT_VFORK = __PTRACE_EVENT_VFORK, /* ... */
#endif /* __PTRACE_EVENT_VFORK */
#ifdef __PTRACE_EVENT_CLONE
	PTRACE_EVENT_CLONE = __PTRACE_EVENT_CLONE, /* ... */
#endif /* __PTRACE_EVENT_CLONE */
#ifdef __PTRACE_EVENT_EXEC
	PTRACE_EVENT_EXEC = __PTRACE_EVENT_EXEC, /* ... */
#endif /* __PTRACE_EVENT_EXEC */
#ifdef __PTRACE_EVENT_VFORK_DONE
	PTRACE_EVENT_VFORK_DONE = __PTRACE_EVENT_VFORK_DONE, /* ... */
#endif /* __PTRACE_EVENT_VFORK_DONE */
#ifdef __PTRACE_EVENT_EXIT
	PTRACE_EVENT_EXIT = __PTRACE_EVENT_EXIT, /* ... */
#endif /* __PTRACE_EVENT_EXIT */
#ifdef __PTRACE_EVENT_SECCOMP
	PTRACE_EVENT_SECCOMP = __PTRACE_EVENT_SECCOMP /* ... */
#endif /* __PTRACE_EVENT_SECCOMP */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#ifdef __PTRACE_EVENT_FORK
#define PTRACE_EVENT_FORK       PTRACE_EVENT_FORK       /* ... */
#endif /* __PTRACE_EVENT_FORK */
#ifdef __PTRACE_EVENT_VFORK
#define PTRACE_EVENT_VFORK      PTRACE_EVENT_VFORK      /* ... */
#endif /* __PTRACE_EVENT_VFORK */
#ifdef __PTRACE_EVENT_CLONE
#define PTRACE_EVENT_CLONE      PTRACE_EVENT_CLONE      /* ... */
#endif /* __PTRACE_EVENT_CLONE */
#ifdef __PTRACE_EVENT_EXEC
#define PTRACE_EVENT_EXEC       PTRACE_EVENT_EXEC       /* ... */
#endif /* __PTRACE_EVENT_EXEC */
#ifdef __PTRACE_EVENT_VFORK_DONE
#define PTRACE_EVENT_VFORK_DONE PTRACE_EVENT_VFORK_DONE /* ... */
#endif /* __PTRACE_EVENT_VFORK_DONE */
#ifdef __PTRACE_EVENT_EXIT
#define PTRACE_EVENT_EXIT       PTRACE_EVENT_EXIT       /* ... */
#endif /* __PTRACE_EVENT_EXIT */
#ifdef __PTRACE_EVENT_SECCOMP
#define PTRACE_EVENT_SECCOMP    PTRACE_EVENT_SECCOMP    /* ... */
#endif /* __PTRACE_EVENT_SECCOMP */
#else /* __COMPILER_PREFERR_ENUMS */
#ifdef __PTRACE_EVENT_FORK
#define PTRACE_EVENT_FORK       __PTRACE_EVENT_FORK       /* ... */
#endif /* __PTRACE_EVENT_FORK */
#ifdef __PTRACE_EVENT_VFORK
#define PTRACE_EVENT_VFORK      __PTRACE_EVENT_VFORK      /* ... */
#endif /* __PTRACE_EVENT_VFORK */
#ifdef __PTRACE_EVENT_CLONE
#define PTRACE_EVENT_CLONE      __PTRACE_EVENT_CLONE      /* ... */
#endif /* __PTRACE_EVENT_CLONE */
#ifdef __PTRACE_EVENT_EXEC
#define PTRACE_EVENT_EXEC       __PTRACE_EVENT_EXEC       /* ... */
#endif /* __PTRACE_EVENT_EXEC */
#ifdef __PTRACE_EVENT_VFORK_DONE
#define PTRACE_EVENT_VFORK_DONE __PTRACE_EVENT_VFORK_DONE /* ... */
#endif /* __PTRACE_EVENT_VFORK_DONE */
#ifdef __PTRACE_EVENT_EXIT
#define PTRACE_EVENT_EXIT       __PTRACE_EVENT_EXIT       /* ... */
#endif /* __PTRACE_EVENT_EXIT */
#ifdef __PTRACE_EVENT_SECCOMP
#define PTRACE_EVENT_SECCOMP    __PTRACE_EVENT_SECCOMP    /* ... */
#endif /* __PTRACE_EVENT_SECCOMP */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/
#endif /* ... */


#ifdef __PTRACE_PEEKSIGINFO_SHARED
/*[[[enum]]]*/
#ifdef __CC__
enum __ptrace_peeksiginfo_flags {
#ifdef __PTRACE_PEEKSIGINFO_SHARED
	PTRACE_PEEKSIGINFO_SHARED = __PTRACE_PEEKSIGINFO_SHARED /* Read signals from a shared (process wide) queue. */
#endif /* __PTRACE_PEEKSIGINFO_SHARED */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#ifdef __PTRACE_PEEKSIGINFO_SHARED
#define PTRACE_PEEKSIGINFO_SHARED PTRACE_PEEKSIGINFO_SHARED /* Read signals from a shared (process wide) queue. */
#endif /* __PTRACE_PEEKSIGINFO_SHARED */
#else /* __COMPILER_PREFERR_ENUMS */
#ifdef __PTRACE_PEEKSIGINFO_SHARED
#define PTRACE_PEEKSIGINFO_SHARED __PTRACE_PEEKSIGINFO_SHARED /* Read signals from a shared (process wide) queue. */
#endif /* __PTRACE_PEEKSIGINFO_SHARED */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/
#endif /* ... */


#ifdef __CC__

#ifdef __CRT_HAVE_ptrace
/* Perform process tracing functions. REQUEST is one of
 * the values above, and determines the action to be taken.
 * For all requests except PTRACE_TRACEME, PID specifies the process to be traced.
 *
 * PID and the other arguments described above for the various requests should
 * appear (those that are used for the particular request) as:
 *     pid_t PID, void *ADDR, int DATA, void *ADDR2
 * after REQUEST */
__LIBC __LONGPTR_TYPE__ __NOTHROW_NCX(__VLIBCCALL ptrace)(__ptrace_request_t __request, ...) __CASMNAME_SAME("ptrace");
#endif /* __CRT_HAVE_ptrace */

#endif /* __CC__ */

__SYSDECL_END

#endif /* !_SYS_PTRACE_H */
