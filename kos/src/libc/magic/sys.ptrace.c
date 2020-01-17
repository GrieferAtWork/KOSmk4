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

%[define_replacement(fd_t = __fd_t)]
%[default_impl_section(.text.crt.system.ptrace)]

%{
#include <features.h>
#include <bits/types.h>

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



/* Type of the REQUEST argument to `ptrace.' */
}%[enum @undef @macro @guard @typedef(__ptrace_request_t) __ptrace_request {
	PTRACE_TRACEME            = 0,      /* Indicate that the process making this request should be traced.
	                                     * All signals received by this process can be intercepted by its
	                                     * parent, and its parent can use the other `ptrace' requests. */
	PTRACE_PEEKTEXT           = 1,      /* Return the word in the process's text space at address ADDR.  */
	PTRACE_PEEKDATA           = 2,      /* Return the word in the process's data space at address ADDR.  */
	PTRACE_PEEKUSER           = 3,      /* Return the word in the process's user area at offset ADDR.  */
	PTRACE_POKETEXT           = 4,      /* Write the word DATA into the process's text space at address ADDR.  */
	PTRACE_POKEDATA           = 5,      /* Write the word DATA into the process's data space at address ADDR.  */
	PTRACE_POKEUSER           = 6,      /* Write the word DATA into the process's user area at offset ADDR.  */
	PTRACE_CONT               = 7,      /* Continue the process.  */
	PTRACE_KILL               = 8,      /* Kill the process.  */
	PTRACE_SINGLESTEP         = 9,      /* Single step the process. This is not supported on all machines.  */
	PTRACE_GETREGS            = 12,     /* Get all general purpose registers used by a processes. This is not supported on all machines.  */
	PTRACE_SETREGS            = 13,     /* Set all general purpose registers used by a processes. This is not supported on all machines.  */
	PTRACE_GETFPREGS          = 14,     /* Get all floating point registers used by a processes. This is not supported on all machines.  */
	PTRACE_SETFPREGS          = 15,     /* Set all floating point registers used by a processes. This is not supported on all machines.  */
	PTRACE_ATTACH             = 16,     /* Attach to a process that is already running. */
	PTRACE_DETACH             = 17,     /* Detach from a process attached to with PTRACE_ATTACH.  */
	PTRACE_GETFPXREGS         = 18,     /* Get all extended floating point registers used by a processes. This is not supported on all machines.  */
	PTRACE_SETFPXREGS         = 19,     /* Set all extended floating point registers used by a processes. This is not supported on all machines.  */
	PTRACE_SYSCALL            = 24,     /* Continue and stop at the next (return from) syscall.  */
	PTRACE_SETOPTIONS         = 0x4200, /* Set ptrace filter options.  */
	PTRACE_GETEVENTMSG        = 0x4201, /* Get last ptrace message.  */
	PTRACE_GETSIGINFO         = 0x4202, /* Get siginfo for process.  */
	PTRACE_SETSIGINFO         = 0x4203, /* Set new siginfo for process.  */
	PTRACE_GETREGSET          = 0x4204, /* Get register content.  */
	PTRACE_SETREGSET          = 0x4205, /* Set register content.  */
	PTRACE_SEIZE              = 0x4206, /* Like PTRACE_ATTACH, but do not force tracee to trap and do not affect signal or group stop state.  */
	PTRACE_INTERRUPT          = 0x4207, /* Trap seized tracee.  */
	PTRACE_LISTEN             = 0x4208, /* Wait for next group event.  */
	PTRACE_PEEKSIGINFO        = 0x4209,
	PTRACE_GETSIGMASK         = 0x420a,
	PTRACE_SETSIGMASK         = 0x420b,
	PTRACE_SECCOMP_GET_FILTER = 0x420c
	PT_TRACE_ME               = PTRACE_TRACEME     /* Indicate that the process making this request should be traced.
	                                                * All signals received by this process can be intercepted by its
	                                                * parent, and its parent can use the other `ptrace' requests. */
	PT_READ_I                 = PTRACE_PEEKTEXT    /* Return the word in the process's text space at address ADDR.  */
	PT_READ_D                 = PTRACE_PEEKDATA    /* Return the word in the process's data space at address ADDR.  */
	PT_READ_U                 = PTRACE_PEEKUSER    /* Return the word in the process's user area at offset ADDR.  */
	PT_WRITE_I                = PTRACE_POKETEXT    /* Write the word DATA into the process's text space at address ADDR.  */
	PT_WRITE_D                = PTRACE_POKEDATA    /* Write the word DATA into the process's data space at address ADDR.  */
	PT_WRITE_U                = PTRACE_POKEUSER    /* Write the word DATA into the process's user area at offset ADDR.  */
	PT_CONTINUE               = PTRACE_CONT        /* Continue the process.  */
	PT_KILL                   = PTRACE_KILL        /* Kill the process.  */
	PT_STEP                   = PTRACE_SINGLESTEP  /* Single step the process. This is not supported on all machines.  */
	PT_GETREGS                = PTRACE_GETREGS     /* Get all general purpose registers used by a processes. This is not supported on all machines.  */
	PT_SETREGS                = PTRACE_SETREGS     /* Set all general purpose registers used by a processes. This is not supported on all machines.  */
	PT_GETFPREGS              = PTRACE_GETFPREGS   /* Get all floating point registers used by a processes. This is not supported on all machines.  */
	PT_SETFPREGS              = PTRACE_SETFPREGS   /* Set all floating point registers used by a processes. This is not supported on all machines.  */
	PT_ATTACH                 = PTRACE_ATTACH      /* Attach to a process that is already running. */
	PT_DETACH                 = PTRACE_DETACH      /* Detach from a process attached to with PTRACE_ATTACH.  */
	PT_GETFPXREGS             = PTRACE_GETFPXREGS  /* Get all extended floating point registers used by a processes. This is not supported on all machines.  */
	PT_SETFPXREGS             = PTRACE_SETFPXREGS  /* Set all extended floating point registers used by a processes. This is not supported on all machines.  */
	PT_SYSCALL                = PTRACE_SYSCALL     /* Continue and stop at the next (return from) syscall.  */
	PT_SETOPTIONS             = PTRACE_SETOPTIONS  /* Set ptrace filter options.  */
	PT_GETEVENTMSG            = PTRACE_GETEVENTMSG /* Get last ptrace message.  */
	PT_GETSIGINFO             = PTRACE_GETSIGINFO  /* Get siginfo for process.  */
	PT_SETSIGINFO             = PTRACE_SETSIGINFO  /* Set new siginfo for process.  */
}]%{


/* Flag for PTRACE_LISTEN. */
}%[enum @undef @macro __ptrace_flags {
	PTRACE_SEIZE_DEVEL = 0x80000000
}]%{

/* Options set using PTRACE_SETOPTIONS. */
}%[enum @undef @macro __ptrace_setoptions {
	PTRACE_O_TRACESYSGOOD    = 0x00000001,
	PTRACE_O_TRACEFORK       = 0x00000002,
	PTRACE_O_TRACEVFORK      = 0x00000004,
	PTRACE_O_TRACECLONE      = 0x00000008,
	PTRACE_O_TRACEEXEC       = 0x00000010,
	PTRACE_O_TRACEVFORKDONE  = 0x00000020,
	PTRACE_O_TRACEEXIT       = 0x00000040,
	PTRACE_O_TRACESECCOMP    = 0x00000080,
	PTRACE_O_EXITKILL        = 0x00100000,
	PTRACE_O_SUSPEND_SECCOMP = 0x00200000,
	PTRACE_O_MASK            = 0x003000ff
}]%{


/* Wait extended result codes for the above trace options. */
}%[enum @undef @macro __ptrace_eventcodes {
	PTRACE_EVENT_FORK       = 1,
	PTRACE_EVENT_VFORK      = 2,
	PTRACE_EVENT_CLONE      = 3,
	PTRACE_EVENT_EXEC       = 4,
	PTRACE_EVENT_VFORK_DONE = 5,
	PTRACE_EVENT_EXIT       = 6,
	PTRACE_EVENT_SECCOMP    = 7
}]%{


}%[enum @undef @macro __ptrace_peeksiginfo_flags {
	PTRACE_PEEKSIGINFO_SHARED = (1 << 0) /* Read signals from a shared (process wide) queue. */
}]%{


#ifdef __CC__
}%[push_macro @undef { off flags nr }]%{
/* Arguments for PTRACE_PEEKSIGINFO. */
struct __ptrace_peeksiginfo_args {
	__uint64_t off;   /* From which siginfo to start. */
	__uint32_t flags; /* Flags for peeksiginfo. */
	__int32_t  nr;    /* How many siginfos to take. */
};
}%[pop_macro]%{

}

@@Perform process tracing functions. REQUEST is one of
@@the values above, and determines the action to be taken.
@@For all requests except PTRACE_TRACEME, PID specifies the process to be traced.
@@
@@PID and the other arguments described above for the various requests should
@@appear (those that are used for the particular request) as:
@@    pid_t PID, void *ADDR, int DATA, void *ADDR2
@@after REQUEST
ptrace:(__ptrace_request_t request, ...) -> long int;

%{
#endif /* __CC__ */

__SYSDECL_END

}