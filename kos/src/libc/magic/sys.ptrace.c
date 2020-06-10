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
%[define_replacement(longptr_t = __LONGPTR_TYPE__)]
%[default_impl_section(".text.crt.system.ptrace")]

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
/*[[[enum]]]*/
#ifdef __CC__
typedef enum __ptrace_request {
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
	PTRACE_SECCOMP_GET_FILTER = 0x420c,
	PT_TRACE_ME               = PTRACE_TRACEME,     /* Indicate that the process making this request should be traced.
	                                                 * All signals received by this process can be intercepted by its
	                                                 * parent, and its parent can use the other `ptrace' requests. */
	PT_READ_I                 = PTRACE_PEEKTEXT,    /* Return the word in the process's text space at address ADDR.  */
	PT_READ_D                 = PTRACE_PEEKDATA,    /* Return the word in the process's data space at address ADDR.  */
	PT_READ_U                 = PTRACE_PEEKUSER,    /* Return the word in the process's user area at offset ADDR.  */
	PT_WRITE_I                = PTRACE_POKETEXT,    /* Write the word DATA into the process's text space at address ADDR.  */
	PT_WRITE_D                = PTRACE_POKEDATA,    /* Write the word DATA into the process's data space at address ADDR.  */
	PT_WRITE_U                = PTRACE_POKEUSER,    /* Write the word DATA into the process's user area at offset ADDR.  */
	PT_CONTINUE               = PTRACE_CONT,        /* Continue the process.  */
	PT_KILL                   = PTRACE_KILL,        /* Kill the process.  */
	PT_STEP                   = PTRACE_SINGLESTEP,  /* Single step the process. This is not supported on all machines.  */
	PT_GETREGS                = PTRACE_GETREGS,     /* Get all general purpose registers used by a processes. This is not supported on all machines.  */
	PT_SETREGS                = PTRACE_SETREGS,     /* Set all general purpose registers used by a processes. This is not supported on all machines.  */
	PT_GETFPREGS              = PTRACE_GETFPREGS,   /* Get all floating point registers used by a processes. This is not supported on all machines.  */
	PT_SETFPREGS              = PTRACE_SETFPREGS,   /* Set all floating point registers used by a processes. This is not supported on all machines.  */
	PT_ATTACH                 = PTRACE_ATTACH,      /* Attach to a process that is already running. */
	PT_DETACH                 = PTRACE_DETACH,      /* Detach from a process attached to with PTRACE_ATTACH.  */
	PT_GETFPXREGS             = PTRACE_GETFPXREGS,  /* Get all extended floating point registers used by a processes. This is not supported on all machines.  */
	PT_SETFPXREGS             = PTRACE_SETFPXREGS,  /* Set all extended floating point registers used by a processes. This is not supported on all machines.  */
	PT_SYSCALL                = PTRACE_SYSCALL,     /* Continue and stop at the next (return from) syscall.  */
	PT_SETOPTIONS             = PTRACE_SETOPTIONS,  /* Set ptrace filter options.  */
	PT_GETEVENTMSG            = PTRACE_GETEVENTMSG, /* Get last ptrace message.  */
	PT_GETSIGINFO             = PTRACE_GETSIGINFO,  /* Get siginfo for process.  */
	PT_SETSIGINFO             = PTRACE_SETSIGINFO,  /* Set new siginfo for process.  */
} __ptrace_request_t;
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#define PTRACE_TRACEME            PTRACE_TRACEME            /* Indicate that the process making this request should be traced.
                                                             * All signals received by this process can be intercepted by its
                                                             * parent, and its parent can use the other `ptrace' requests. */
#define PTRACE_PEEKTEXT           PTRACE_PEEKTEXT           /* Return the word in the process's text space at address ADDR.  */
#define PTRACE_PEEKDATA           PTRACE_PEEKDATA           /* Return the word in the process's data space at address ADDR.  */
#define PTRACE_PEEKUSER           PTRACE_PEEKUSER           /* Return the word in the process's user area at offset ADDR.  */
#define PTRACE_POKETEXT           PTRACE_POKETEXT           /* Write the word DATA into the process's text space at address ADDR.  */
#define PTRACE_POKEDATA           PTRACE_POKEDATA           /* Write the word DATA into the process's data space at address ADDR.  */
#define PTRACE_POKEUSER           PTRACE_POKEUSER           /* Write the word DATA into the process's user area at offset ADDR.  */
#define PTRACE_CONT               PTRACE_CONT               /* Continue the process.  */
#define PTRACE_KILL               PTRACE_KILL               /* Kill the process.  */
#define PTRACE_SINGLESTEP         PTRACE_SINGLESTEP         /* Single step the process. This is not supported on all machines.  */
#define PTRACE_GETREGS            PTRACE_GETREGS            /* Get all general purpose registers used by a processes. This is not supported on all machines.  */
#define PTRACE_SETREGS            PTRACE_SETREGS            /* Set all general purpose registers used by a processes. This is not supported on all machines.  */
#define PTRACE_GETFPREGS          PTRACE_GETFPREGS          /* Get all floating point registers used by a processes. This is not supported on all machines.  */
#define PTRACE_SETFPREGS          PTRACE_SETFPREGS          /* Set all floating point registers used by a processes. This is not supported on all machines.  */
#define PTRACE_ATTACH             PTRACE_ATTACH             /* Attach to a process that is already running. */
#define PTRACE_DETACH             PTRACE_DETACH             /* Detach from a process attached to with PTRACE_ATTACH.  */
#define PTRACE_GETFPXREGS         PTRACE_GETFPXREGS         /* Get all extended floating point registers used by a processes. This is not supported on all machines.  */
#define PTRACE_SETFPXREGS         PTRACE_SETFPXREGS         /* Set all extended floating point registers used by a processes. This is not supported on all machines.  */
#define PTRACE_SYSCALL            PTRACE_SYSCALL            /* Continue and stop at the next (return from) syscall.  */
#define PTRACE_SETOPTIONS         PTRACE_SETOPTIONS         /* Set ptrace filter options.  */
#define PTRACE_GETEVENTMSG        PTRACE_GETEVENTMSG        /* Get last ptrace message.  */
#define PTRACE_GETSIGINFO         PTRACE_GETSIGINFO         /* Get siginfo for process.  */
#define PTRACE_SETSIGINFO         PTRACE_SETSIGINFO         /* Set new siginfo for process.  */
#define PTRACE_GETREGSET          PTRACE_GETREGSET          /* Get register content.  */
#define PTRACE_SETREGSET          PTRACE_SETREGSET          /* Set register content.  */
#define PTRACE_SEIZE              PTRACE_SEIZE              /* Like PTRACE_ATTACH, but do not force tracee to trap and do not affect signal or group stop state.  */
#define PTRACE_INTERRUPT          PTRACE_INTERRUPT          /* Trap seized tracee.  */
#define PTRACE_LISTEN             PTRACE_LISTEN             /* Wait for next group event.  */
#define PTRACE_PEEKSIGINFO        PTRACE_PEEKSIGINFO
#define PTRACE_GETSIGMASK         PTRACE_GETSIGMASK
#define PTRACE_SETSIGMASK         PTRACE_SETSIGMASK
#define PTRACE_SECCOMP_GET_FILTER PTRACE_SECCOMP_GET_FILTER
#define PT_TRACE_ME               PT_TRACE_ME               /* Indicate that the process making this request should be traced.
                                                             * All signals received by this process can be intercepted by its
                                                             * parent, and its parent can use the other `ptrace' requests. */
#define PT_READ_I                 PT_READ_I                 /* Return the word in the process's text space at address ADDR.  */
#define PT_READ_D                 PT_READ_D                 /* Return the word in the process's data space at address ADDR.  */
#define PT_READ_U                 PT_READ_U                 /* Return the word in the process's user area at offset ADDR.  */
#define PT_WRITE_I                PT_WRITE_I                /* Write the word DATA into the process's text space at address ADDR.  */
#define PT_WRITE_D                PT_WRITE_D                /* Write the word DATA into the process's data space at address ADDR.  */
#define PT_WRITE_U                PT_WRITE_U                /* Write the word DATA into the process's user area at offset ADDR.  */
#define PT_CONTINUE               PT_CONTINUE               /* Continue the process.  */
#define PT_KILL                   PT_KILL                   /* Kill the process.  */
#define PT_STEP                   PT_STEP                   /* Single step the process. This is not supported on all machines.  */
#define PT_GETREGS                PT_GETREGS                /* Get all general purpose registers used by a processes. This is not supported on all machines.  */
#define PT_SETREGS                PT_SETREGS                /* Set all general purpose registers used by a processes. This is not supported on all machines.  */
#define PT_GETFPREGS              PT_GETFPREGS              /* Get all floating point registers used by a processes. This is not supported on all machines.  */
#define PT_SETFPREGS              PT_SETFPREGS              /* Set all floating point registers used by a processes. This is not supported on all machines.  */
#define PT_ATTACH                 PT_ATTACH                 /* Attach to a process that is already running. */
#define PT_DETACH                 PT_DETACH                 /* Detach from a process attached to with PTRACE_ATTACH.  */
#define PT_GETFPXREGS             PT_GETFPXREGS             /* Get all extended floating point registers used by a processes. This is not supported on all machines.  */
#define PT_SETFPXREGS             PT_SETFPXREGS             /* Set all extended floating point registers used by a processes. This is not supported on all machines.  */
#define PT_SYSCALL                PT_SYSCALL                /* Continue and stop at the next (return from) syscall.  */
#define PT_SETOPTIONS             PT_SETOPTIONS             /* Set ptrace filter options.  */
#define PT_GETEVENTMSG            PT_GETEVENTMSG            /* Get last ptrace message.  */
#define PT_GETSIGINFO             PT_GETSIGINFO             /* Get siginfo for process.  */
#define PT_SETSIGINFO             PT_SETSIGINFO             /* Set new siginfo for process.  */
#else /* __COMPILER_PREFERR_ENUMS */
#define PTRACE_TRACEME            0      /* Indicate that the process making this request should be traced.
                                          * All signals received by this process can be intercepted by its
                                          * parent, and its parent can use the other `ptrace' requests. */
#define PTRACE_PEEKTEXT           1      /* Return the word in the process's text space at address ADDR.  */
#define PTRACE_PEEKDATA           2      /* Return the word in the process's data space at address ADDR.  */
#define PTRACE_PEEKUSER           3      /* Return the word in the process's user area at offset ADDR.  */
#define PTRACE_POKETEXT           4      /* Write the word DATA into the process's text space at address ADDR.  */
#define PTRACE_POKEDATA           5      /* Write the word DATA into the process's data space at address ADDR.  */
#define PTRACE_POKEUSER           6      /* Write the word DATA into the process's user area at offset ADDR.  */
#define PTRACE_CONT               7      /* Continue the process.  */
#define PTRACE_KILL               8      /* Kill the process.  */
#define PTRACE_SINGLESTEP         9      /* Single step the process. This is not supported on all machines.  */
#define PTRACE_GETREGS            12     /* Get all general purpose registers used by a processes. This is not supported on all machines.  */
#define PTRACE_SETREGS            13     /* Set all general purpose registers used by a processes. This is not supported on all machines.  */
#define PTRACE_GETFPREGS          14     /* Get all floating point registers used by a processes. This is not supported on all machines.  */
#define PTRACE_SETFPREGS          15     /* Set all floating point registers used by a processes. This is not supported on all machines.  */
#define PTRACE_ATTACH             16     /* Attach to a process that is already running. */
#define PTRACE_DETACH             17     /* Detach from a process attached to with PTRACE_ATTACH.  */
#define PTRACE_GETFPXREGS         18     /* Get all extended floating point registers used by a processes. This is not supported on all machines.  */
#define PTRACE_SETFPXREGS         19     /* Set all extended floating point registers used by a processes. This is not supported on all machines.  */
#define PTRACE_SYSCALL            24     /* Continue and stop at the next (return from) syscall.  */
#define PTRACE_SETOPTIONS         0x4200 /* Set ptrace filter options.  */
#define PTRACE_GETEVENTMSG        0x4201 /* Get last ptrace message.  */
#define PTRACE_GETSIGINFO         0x4202 /* Get siginfo for process.  */
#define PTRACE_SETSIGINFO         0x4203 /* Set new siginfo for process.  */
#define PTRACE_GETREGSET          0x4204 /* Get register content.  */
#define PTRACE_SETREGSET          0x4205 /* Set register content.  */
#define PTRACE_SEIZE              0x4206 /* Like PTRACE_ATTACH, but do not force tracee to trap and do not affect signal or group stop state.  */
#define PTRACE_INTERRUPT          0x4207 /* Trap seized tracee.  */
#define PTRACE_LISTEN             0x4208 /* Wait for next group event.  */
#define PTRACE_PEEKSIGINFO        0x4209
#define PTRACE_GETSIGMASK         0x420a
#define PTRACE_SETSIGMASK         0x420b
#define PTRACE_SECCOMP_GET_FILTER 0x420c
#define PT_TRACE_ME               0      /* Indicate that the process making this request should be traced.
                                          * All signals received by this process can be intercepted by its
                                          * parent, and its parent can use the other `ptrace' requests. */
#define PT_READ_I                 1      /* Return the word in the process's text space at address ADDR.  */
#define PT_READ_D                 2      /* Return the word in the process's data space at address ADDR.  */
#define PT_READ_U                 3      /* Return the word in the process's user area at offset ADDR.  */
#define PT_WRITE_I                4      /* Write the word DATA into the process's text space at address ADDR.  */
#define PT_WRITE_D                5      /* Write the word DATA into the process's data space at address ADDR.  */
#define PT_WRITE_U                6      /* Write the word DATA into the process's user area at offset ADDR.  */
#define PT_CONTINUE               7      /* Continue the process.  */
#define PT_KILL                   8      /* Kill the process.  */
#define PT_STEP                   9      /* Single step the process. This is not supported on all machines.  */
#define PT_GETREGS                12     /* Get all general purpose registers used by a processes. This is not supported on all machines.  */
#define PT_SETREGS                13     /* Set all general purpose registers used by a processes. This is not supported on all machines.  */
#define PT_GETFPREGS              14     /* Get all floating point registers used by a processes. This is not supported on all machines.  */
#define PT_SETFPREGS              15     /* Set all floating point registers used by a processes. This is not supported on all machines.  */
#define PT_ATTACH                 16     /* Attach to a process that is already running. */
#define PT_DETACH                 17     /* Detach from a process attached to with PTRACE_ATTACH.  */
#define PT_GETFPXREGS             18     /* Get all extended floating point registers used by a processes. This is not supported on all machines.  */
#define PT_SETFPXREGS             19     /* Set all extended floating point registers used by a processes. This is not supported on all machines.  */
#define PT_SYSCALL                24     /* Continue and stop at the next (return from) syscall.  */
#define PT_SETOPTIONS             0x4200 /* Set ptrace filter options.  */
#define PT_GETEVENTMSG            0x4201 /* Get last ptrace message.  */
#define PT_GETSIGINFO             0x4202 /* Get siginfo for process.  */
#define PT_SETSIGINFO             0x4203 /* Set new siginfo for process.  */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/


/* Flag for PTRACE_LISTEN. */
/*[[[enum]]]*/
#ifdef __CC__
enum __ptrace_flags {
	PTRACE_SEIZE_DEVEL = 0x80000000
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#define PTRACE_SEIZE_DEVEL PTRACE_SEIZE_DEVEL
#else /* __COMPILER_PREFERR_ENUMS */
#define PTRACE_SEIZE_DEVEL 0x80000000
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/

/* Options set using PTRACE_SETOPTIONS. */
/*[[[enum]]]*/
#ifdef __CC__
enum __ptrace_setoptions {
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
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#define PTRACE_O_TRACESYSGOOD    PTRACE_O_TRACESYSGOOD
#define PTRACE_O_TRACEFORK       PTRACE_O_TRACEFORK
#define PTRACE_O_TRACEVFORK      PTRACE_O_TRACEVFORK
#define PTRACE_O_TRACECLONE      PTRACE_O_TRACECLONE
#define PTRACE_O_TRACEEXEC       PTRACE_O_TRACEEXEC
#define PTRACE_O_TRACEVFORKDONE  PTRACE_O_TRACEVFORKDONE
#define PTRACE_O_TRACEEXIT       PTRACE_O_TRACEEXIT
#define PTRACE_O_TRACESECCOMP    PTRACE_O_TRACESECCOMP
#define PTRACE_O_EXITKILL        PTRACE_O_EXITKILL
#define PTRACE_O_SUSPEND_SECCOMP PTRACE_O_SUSPEND_SECCOMP
#define PTRACE_O_MASK            PTRACE_O_MASK
#else /* __COMPILER_PREFERR_ENUMS */
#define PTRACE_O_TRACESYSGOOD    0x00000001
#define PTRACE_O_TRACEFORK       0x00000002
#define PTRACE_O_TRACEVFORK      0x00000004
#define PTRACE_O_TRACECLONE      0x00000008
#define PTRACE_O_TRACEEXEC       0x00000010
#define PTRACE_O_TRACEVFORKDONE  0x00000020
#define PTRACE_O_TRACEEXIT       0x00000040
#define PTRACE_O_TRACESECCOMP    0x00000080
#define PTRACE_O_EXITKILL        0x00100000
#define PTRACE_O_SUSPEND_SECCOMP 0x00200000
#define PTRACE_O_MASK            0x003000ff
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/


/* Wait extended result codes for the above trace options. */
/*[[[enum]]]*/
#ifdef __CC__
enum __ptrace_eventcodes {
	PTRACE_EVENT_FORK       = 1,
	PTRACE_EVENT_VFORK      = 2,
	PTRACE_EVENT_CLONE      = 3,
	PTRACE_EVENT_EXEC       = 4,
	PTRACE_EVENT_VFORK_DONE = 5,
	PTRACE_EVENT_EXIT       = 6,
	PTRACE_EVENT_SECCOMP    = 7
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#define PTRACE_EVENT_FORK       PTRACE_EVENT_FORK
#define PTRACE_EVENT_VFORK      PTRACE_EVENT_VFORK
#define PTRACE_EVENT_CLONE      PTRACE_EVENT_CLONE
#define PTRACE_EVENT_EXEC       PTRACE_EVENT_EXEC
#define PTRACE_EVENT_VFORK_DONE PTRACE_EVENT_VFORK_DONE
#define PTRACE_EVENT_EXIT       PTRACE_EVENT_EXIT
#define PTRACE_EVENT_SECCOMP    PTRACE_EVENT_SECCOMP
#else /* __COMPILER_PREFERR_ENUMS */
#define PTRACE_EVENT_FORK       1
#define PTRACE_EVENT_VFORK      2
#define PTRACE_EVENT_CLONE      3
#define PTRACE_EVENT_EXEC       4
#define PTRACE_EVENT_VFORK_DONE 5
#define PTRACE_EVENT_EXIT       6
#define PTRACE_EVENT_SECCOMP    7
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/


/*[[[enum]]]*/
#ifdef __CC__
enum __ptrace_peeksiginfo_flags {
	PTRACE_PEEKSIGINFO_SHARED = 0x0001 /* Read signals from a shared (process wide) queue. */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#define PTRACE_PEEKSIGINFO_SHARED PTRACE_PEEKSIGINFO_SHARED /* Read signals from a shared (process wide) queue. */
#else /* __COMPILER_PREFERR_ENUMS */
#define PTRACE_PEEKSIGINFO_SHARED 0x0001 /* Read signals from a shared (process wide) queue. */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/


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
$longptr_t ptrace(__ptrace_request_t request, ...);

%{
#endif /* __CC__ */

__SYSDECL_END

}