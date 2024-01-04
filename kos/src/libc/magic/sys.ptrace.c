/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
%(c_prefix){
/* (#) Portability: DragonFly BSD (/sys/sys/ptrace.h) */
/* (#) Portability: EMX kLIBC     (/libc/include/sys/ptrace.h) */
/* (#) Portability: FreeBSD       (/sys/sys/ptrace.h) */
/* (#) Portability: GNU C Library (/sysdeps/unix/sysv/linux/sys/ptrace.h) */
/* (#) Portability: NetBSD        (/sys/sys/ptrace.h) */
/* (#) Portability: OpenBSD       (/sys/sys/ptrace.h) */
/* (#) Portability: diet libc     (/include/sys/ptrace.h) */
/* (#) Portability: libc4/5       (/include/sys/ptrace.h) */
/* (#) Portability: mintlib       (/include/sys/ptrace.h) */
/* (#) Portability: musl libc     (/include/sys/ptrace.h) */
}

%[define_replacement(fd_t = __fd_t)]
%[define_replacement(longptr_t = __LONGPTR_TYPE__)]
%[define_replacement(__ptrace_request_t = int)]
%[define_type_class(__ptrace_request_t = "TD")]
%[default:section(".text.crt{|.dos}.system.ptrace")]

%[insert:prefix(
#include <features.h>
)]%{

}%[insert:prefix(
#include <asm/os/ptrace.h>
)]%[insert:prefix(
#include <bits/types.h>
)]%[insert:prefix(
#include <bits/os/ptrace.h> /* `struct __ptrace_peeksiginfo_args' */
)]%{


__SYSDECL_BEGIN

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
/* ptrace(2) request codes. */
/*[[[enum]]]*/
#ifdef __CC__
typedef enum __ptrace_request {
#if !defined(PTRACE_TRACEME) && defined(__PTRACE_TRACEME)
	PTRACE_TRACEME = __PTRACE_TRACEME,   /* ??? */
#endif /* !PTRACE_TRACEME && __PTRACE_TRACEME */
#if !defined(PTRACE_PEEKTEXT) && defined(__PTRACE_PEEKTEXT)
	PTRACE_PEEKTEXT = __PTRACE_PEEKTEXT, /* ??? */
#endif /* !PTRACE_PEEKTEXT && __PTRACE_PEEKTEXT */
#if !defined(PTRACE_PEEKDATA) && defined(__PTRACE_PEEKDATA)
	PTRACE_PEEKDATA = __PTRACE_PEEKDATA, /* ??? */
#endif /* !PTRACE_PEEKDATA && __PTRACE_PEEKDATA */
#if !defined(PTRACE_PEEKUSER) && defined(__PTRACE_PEEKUSER)
	PTRACE_PEEKUSER = __PTRACE_PEEKUSER, /* ??? */
#endif /* !PTRACE_PEEKUSER && __PTRACE_PEEKUSER */
#if !defined(PTRACE_POKETEXT) && defined(__PTRACE_POKETEXT)
	PTRACE_POKETEXT = __PTRACE_POKETEXT, /* ??? */
#endif /* !PTRACE_POKETEXT && __PTRACE_POKETEXT */
#if !defined(PTRACE_POKEDATA) && defined(__PTRACE_POKEDATA)
	PTRACE_POKEDATA = __PTRACE_POKEDATA, /* ??? */
#endif /* !PTRACE_POKEDATA && __PTRACE_POKEDATA */
#if !defined(PTRACE_POKEUSER) && defined(__PTRACE_POKEUSER)
	PTRACE_POKEUSER = __PTRACE_POKEUSER, /* ??? */
#endif /* !PTRACE_POKEUSER && __PTRACE_POKEUSER */
#if !defined(PTRACE_CONT) && defined(__PTRACE_CONT)
	PTRACE_CONT = __PTRACE_CONT, /* ??? */
#endif /* !PTRACE_CONT && __PTRACE_CONT */
#if !defined(PTRACE_KILL) && defined(__PTRACE_KILL)
	PTRACE_KILL = __PTRACE_KILL, /* ??? */
#endif /* !PTRACE_KILL && __PTRACE_KILL */
#if !defined(PTRACE_SINGLESTEP) && defined(__PTRACE_SINGLESTEP)
	PTRACE_SINGLESTEP = __PTRACE_SINGLESTEP, /* ??? */
#endif /* !PTRACE_SINGLESTEP && __PTRACE_SINGLESTEP */
#if !defined(PTRACE_GETREGS) && defined(__PTRACE_GETREGS)
	PTRACE_GETREGS = __PTRACE_GETREGS, /* ??? */
#endif /* !PTRACE_GETREGS && __PTRACE_GETREGS */
#if !defined(PTRACE_SETREGS) && defined(__PTRACE_SETREGS)
	PTRACE_SETREGS = __PTRACE_SETREGS, /* ??? */
#endif /* !PTRACE_SETREGS && __PTRACE_SETREGS */
#if !defined(PTRACE_GETFPREGS) && defined(__PTRACE_GETFPREGS)
	PTRACE_GETFPREGS = __PTRACE_GETFPREGS, /* ??? */
#endif /* !PTRACE_GETFPREGS && __PTRACE_GETFPREGS */
#if !defined(PTRACE_SETFPREGS) && defined(__PTRACE_SETFPREGS)
	PTRACE_SETFPREGS = __PTRACE_SETFPREGS, /* ??? */
#endif /* !PTRACE_SETFPREGS && __PTRACE_SETFPREGS */
#if !defined(PTRACE_ATTACH) && defined(__PTRACE_ATTACH)
	PTRACE_ATTACH = __PTRACE_ATTACH, /* ??? */
#endif /* !PTRACE_ATTACH && __PTRACE_ATTACH */
#if !defined(PTRACE_DETACH) && defined(__PTRACE_DETACH)
	PTRACE_DETACH = __PTRACE_DETACH, /* ??? */
#endif /* !PTRACE_DETACH && __PTRACE_DETACH */
#if !defined(PTRACE_GETFPXREGS) && defined(__PTRACE_GETFPXREGS)
	PTRACE_GETFPXREGS = __PTRACE_GETFPXREGS, /* ??? */
#endif /* !PTRACE_GETFPXREGS && __PTRACE_GETFPXREGS */
#if !defined(PTRACE_SETFPXREGS) && defined(__PTRACE_SETFPXREGS)
	PTRACE_SETFPXREGS = __PTRACE_SETFPXREGS, /* ??? */
#endif /* !PTRACE_SETFPXREGS && __PTRACE_SETFPXREGS */
#if !defined(PTRACE_SYSCALL) && defined(__PTRACE_SYSCALL)
	PTRACE_SYSCALL = __PTRACE_SYSCALL, /* ??? */
#endif /* !PTRACE_SYSCALL && __PTRACE_SYSCALL */
#if !defined(PTRACE_SETOPTIONS) && defined(__PTRACE_SETOPTIONS)
	PTRACE_SETOPTIONS = __PTRACE_SETOPTIONS, /* ??? */
#endif /* !PTRACE_SETOPTIONS && __PTRACE_SETOPTIONS */
#if !defined(PTRACE_GETEVENTMSG) && defined(__PTRACE_GETEVENTMSG)
	PTRACE_GETEVENTMSG = __PTRACE_GETEVENTMSG, /* ??? */
#endif /* !PTRACE_GETEVENTMSG && __PTRACE_GETEVENTMSG */
#if !defined(PTRACE_GETSIGINFO) && defined(__PTRACE_GETSIGINFO)
	PTRACE_GETSIGINFO = __PTRACE_GETSIGINFO, /* ??? */
#endif /* !PTRACE_GETSIGINFO && __PTRACE_GETSIGINFO */
#if !defined(PTRACE_SETSIGINFO) && defined(__PTRACE_SETSIGINFO)
	PTRACE_SETSIGINFO = __PTRACE_SETSIGINFO, /* ??? */
#endif /* !PTRACE_SETSIGINFO && __PTRACE_SETSIGINFO */
#if !defined(PTRACE_GETREGSET) && defined(__PTRACE_GETREGSET)
	PTRACE_GETREGSET = __PTRACE_GETREGSET, /* ??? */
#endif /* !PTRACE_GETREGSET && __PTRACE_GETREGSET */
#if !defined(PTRACE_SETREGSET) && defined(__PTRACE_SETREGSET)
	PTRACE_SETREGSET = __PTRACE_SETREGSET, /* ??? */
#endif /* !PTRACE_SETREGSET && __PTRACE_SETREGSET */
#if !defined(PTRACE_SEIZE) && defined(__PTRACE_SEIZE)
	PTRACE_SEIZE = __PTRACE_SEIZE, /* ??? */
#endif /* !PTRACE_SEIZE && __PTRACE_SEIZE */
#if !defined(PTRACE_INTERRUPT) && defined(__PTRACE_INTERRUPT)
	PTRACE_INTERRUPT = __PTRACE_INTERRUPT, /* ??? */
#endif /* !PTRACE_INTERRUPT && __PTRACE_INTERRUPT */
#if !defined(PTRACE_LISTEN) && defined(__PTRACE_LISTEN)
	PTRACE_LISTEN = __PTRACE_LISTEN, /* ??? */
#endif /* !PTRACE_LISTEN && __PTRACE_LISTEN */
#if !defined(PTRACE_PEEKSIGINFO) && defined(__PTRACE_PEEKSIGINFO)
	PTRACE_PEEKSIGINFO = __PTRACE_PEEKSIGINFO, /* ??? */
#endif /* !PTRACE_PEEKSIGINFO && __PTRACE_PEEKSIGINFO */
#if !defined(PTRACE_GETSIGMASK) && defined(__PTRACE_GETSIGMASK)
	PTRACE_GETSIGMASK = __PTRACE_GETSIGMASK, /* ??? */
#endif /* !PTRACE_GETSIGMASK && __PTRACE_GETSIGMASK */
#if !defined(PTRACE_SETSIGMASK) && defined(__PTRACE_SETSIGMASK)
	PTRACE_SETSIGMASK = __PTRACE_SETSIGMASK, /* ??? */
#endif /* !PTRACE_SETSIGMASK && __PTRACE_SETSIGMASK */
#if !defined(PTRACE_SECCOMP_GET_FILTER) && defined(__PTRACE_SECCOMP_GET_FILTER)
	PTRACE_SECCOMP_GET_FILTER = __PTRACE_SECCOMP_GET_FILTER, /* ??? */
#endif /* !PTRACE_SECCOMP_GET_FILTER && __PTRACE_SECCOMP_GET_FILTER */

#if !defined(PT_TRACE_ME) && defined(__PTRACE_TRACEME)
	PT_TRACE_ME = __PTRACE_TRACEME, /* ??? */
#endif /* !PT_TRACE_ME && __PTRACE_TRACEME */
#if !defined(PT_READ_I) && defined(__PTRACE_PEEKTEXT)
	PT_READ_I = __PTRACE_PEEKTEXT, /* ??? */
#endif /* !PT_READ_I && __PTRACE_PEEKTEXT */
#if !defined(PT_READ_D) && defined(__PTRACE_PEEKDATA)
	PT_READ_D = __PTRACE_PEEKDATA, /* ??? */
#endif /* !PT_READ_D && __PTRACE_PEEKDATA */
#if !defined(PT_READ_U) && defined(__PTRACE_PEEKUSER)
	PT_READ_U = __PTRACE_PEEKUSER, /* ??? */
#endif /* !PT_READ_U && __PTRACE_PEEKUSER */
#if !defined(PT_WRITE_I) && defined(__PTRACE_POKETEXT)
	PT_WRITE_I = __PTRACE_POKETEXT, /* ??? */
#endif /* !PT_WRITE_I && __PTRACE_POKETEXT */
#if !defined(PT_WRITE_D) && defined(__PTRACE_POKEDATA)
	PT_WRITE_D = __PTRACE_POKEDATA, /* ??? */
#endif /* !PT_WRITE_D && __PTRACE_POKEDATA */
#if !defined(PT_WRITE_U) && defined(__PTRACE_POKEUSER)
	PT_WRITE_U = __PTRACE_POKEUSER, /* ??? */
#endif /* !PT_WRITE_U && __PTRACE_POKEUSER */
#if !defined(PT_CONTINUE) && defined(__PTRACE_CONT)
	PT_CONTINUE = __PTRACE_CONT, /* ??? */
#endif /* !PT_CONTINUE && __PTRACE_CONT */
#if !defined(PT_KILL) && defined(__PTRACE_KILL)
	PT_KILL = __PTRACE_KILL, /* ??? */
#endif /* !PT_KILL && __PTRACE_KILL */
#if !defined(PT_STEP) && defined(__PTRACE_SINGLESTEP)
	PT_STEP = __PTRACE_SINGLESTEP, /* ??? */
#endif /* !PT_STEP && __PTRACE_SINGLESTEP */
#if !defined(PT_GETREGS) && defined(__PTRACE_GETREGS)
	PT_GETREGS = __PTRACE_GETREGS, /* ??? */
#endif /* !PT_GETREGS && __PTRACE_GETREGS */
#if !defined(PT_SETREGS) && defined(__PTRACE_SETREGS)
	PT_SETREGS = __PTRACE_SETREGS, /* ??? */
#endif /* !PT_SETREGS && __PTRACE_SETREGS */
#if !defined(PT_GETFPREGS) && defined(__PTRACE_GETFPREGS)
	PT_GETFPREGS = __PTRACE_GETFPREGS, /* ??? */
#endif /* !PT_GETFPREGS && __PTRACE_GETFPREGS */
#if !defined(PT_SETFPREGS) && defined(__PTRACE_SETFPREGS)
	PT_SETFPREGS = __PTRACE_SETFPREGS, /* ??? */
#endif /* !PT_SETFPREGS && __PTRACE_SETFPREGS */
#if !defined(PT_ATTACH) && defined(__PTRACE_ATTACH)
	PT_ATTACH = __PTRACE_ATTACH, /* ??? */
#endif /* !PT_ATTACH && __PTRACE_ATTACH */
#if !defined(PT_DETACH) && defined(__PTRACE_DETACH)
	PT_DETACH = __PTRACE_DETACH, /* ??? */
#endif /* !PT_DETACH && __PTRACE_DETACH */
#if !defined(PT_GETFPXREGS) && defined(__PTRACE_GETFPXREGS)
	PT_GETFPXREGS = __PTRACE_GETFPXREGS, /* ??? */
#endif /* !PT_GETFPXREGS && __PTRACE_GETFPXREGS */
#if !defined(PT_SETFPXREGS) && defined(__PTRACE_SETFPXREGS)
	PT_SETFPXREGS = __PTRACE_SETFPXREGS, /* ??? */
#endif /* !PT_SETFPXREGS && __PTRACE_SETFPXREGS */
#if !defined(PT_SYSCALL) && defined(__PTRACE_SYSCALL)
	PT_SYSCALL = __PTRACE_SYSCALL, /* ??? */
#endif /* !PT_SYSCALL && __PTRACE_SYSCALL */
#if !defined(PT_SETOPTIONS) && defined(__PTRACE_SETOPTIONS)
	PT_SETOPTIONS = __PTRACE_SETOPTIONS, /* ??? */
#endif /* !PT_SETOPTIONS && __PTRACE_SETOPTIONS */
#if !defined(PT_GETEVENTMSG) && defined(__PTRACE_GETEVENTMSG)
	PT_GETEVENTMSG = __PTRACE_GETEVENTMSG, /* ??? */
#endif /* !PT_GETEVENTMSG && __PTRACE_GETEVENTMSG */
#if !defined(PT_GETSIGINFO) && defined(__PTRACE_GETSIGINFO)
	PT_GETSIGINFO = __PTRACE_GETSIGINFO, /* ??? */
#endif /* !PT_GETSIGINFO && __PTRACE_GETSIGINFO */
#if !defined(PT_SETSIGINFO) && defined(__PTRACE_SETSIGINFO)
	PT_SETSIGINFO = __PTRACE_SETSIGINFO, /* ??? */
#endif /* !PT_SETSIGINFO && __PTRACE_SETSIGINFO */
} __ptrace_request_t;
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#if !defined(PTRACE_TRACEME) && defined(__PTRACE_TRACEME)
#define PTRACE_TRACEME            PTRACE_TRACEME            /* ??? */
#endif /* !PTRACE_TRACEME && __PTRACE_TRACEME */
#if !defined(PTRACE_PEEKTEXT) && defined(__PTRACE_PEEKTEXT)
#define PTRACE_PEEKTEXT           PTRACE_PEEKTEXT           /* ??? */
#endif /* !PTRACE_PEEKTEXT && __PTRACE_PEEKTEXT */
#if !defined(PTRACE_PEEKDATA) && defined(__PTRACE_PEEKDATA)
#define PTRACE_PEEKDATA           PTRACE_PEEKDATA           /* ??? */
#endif /* !PTRACE_PEEKDATA && __PTRACE_PEEKDATA */
#if !defined(PTRACE_PEEKUSER) && defined(__PTRACE_PEEKUSER)
#define PTRACE_PEEKUSER           PTRACE_PEEKUSER           /* ??? */
#endif /* !PTRACE_PEEKUSER && __PTRACE_PEEKUSER */
#if !defined(PTRACE_POKETEXT) && defined(__PTRACE_POKETEXT)
#define PTRACE_POKETEXT           PTRACE_POKETEXT           /* ??? */
#endif /* !PTRACE_POKETEXT && __PTRACE_POKETEXT */
#if !defined(PTRACE_POKEDATA) && defined(__PTRACE_POKEDATA)
#define PTRACE_POKEDATA           PTRACE_POKEDATA           /* ??? */
#endif /* !PTRACE_POKEDATA && __PTRACE_POKEDATA */
#if !defined(PTRACE_POKEUSER) && defined(__PTRACE_POKEUSER)
#define PTRACE_POKEUSER           PTRACE_POKEUSER           /* ??? */
#endif /* !PTRACE_POKEUSER && __PTRACE_POKEUSER */
#if !defined(PTRACE_CONT) && defined(__PTRACE_CONT)
#define PTRACE_CONT               PTRACE_CONT               /* ??? */
#endif /* !PTRACE_CONT && __PTRACE_CONT */
#if !defined(PTRACE_KILL) && defined(__PTRACE_KILL)
#define PTRACE_KILL               PTRACE_KILL               /* ??? */
#endif /* !PTRACE_KILL && __PTRACE_KILL */
#if !defined(PTRACE_SINGLESTEP) && defined(__PTRACE_SINGLESTEP)
#define PTRACE_SINGLESTEP         PTRACE_SINGLESTEP         /* ??? */
#endif /* !PTRACE_SINGLESTEP && __PTRACE_SINGLESTEP */
#if !defined(PTRACE_GETREGS) && defined(__PTRACE_GETREGS)
#define PTRACE_GETREGS            PTRACE_GETREGS            /* ??? */
#endif /* !PTRACE_GETREGS && __PTRACE_GETREGS */
#if !defined(PTRACE_SETREGS) && defined(__PTRACE_SETREGS)
#define PTRACE_SETREGS            PTRACE_SETREGS            /* ??? */
#endif /* !PTRACE_SETREGS && __PTRACE_SETREGS */
#if !defined(PTRACE_GETFPREGS) && defined(__PTRACE_GETFPREGS)
#define PTRACE_GETFPREGS          PTRACE_GETFPREGS          /* ??? */
#endif /* !PTRACE_GETFPREGS && __PTRACE_GETFPREGS */
#if !defined(PTRACE_SETFPREGS) && defined(__PTRACE_SETFPREGS)
#define PTRACE_SETFPREGS          PTRACE_SETFPREGS          /* ??? */
#endif /* !PTRACE_SETFPREGS && __PTRACE_SETFPREGS */
#if !defined(PTRACE_ATTACH) && defined(__PTRACE_ATTACH)
#define PTRACE_ATTACH             PTRACE_ATTACH             /* ??? */
#endif /* !PTRACE_ATTACH && __PTRACE_ATTACH */
#if !defined(PTRACE_DETACH) && defined(__PTRACE_DETACH)
#define PTRACE_DETACH             PTRACE_DETACH             /* ??? */
#endif /* !PTRACE_DETACH && __PTRACE_DETACH */
#if !defined(PTRACE_GETFPXREGS) && defined(__PTRACE_GETFPXREGS)
#define PTRACE_GETFPXREGS         PTRACE_GETFPXREGS         /* ??? */
#endif /* !PTRACE_GETFPXREGS && __PTRACE_GETFPXREGS */
#if !defined(PTRACE_SETFPXREGS) && defined(__PTRACE_SETFPXREGS)
#define PTRACE_SETFPXREGS         PTRACE_SETFPXREGS         /* ??? */
#endif /* !PTRACE_SETFPXREGS && __PTRACE_SETFPXREGS */
#if !defined(PTRACE_SYSCALL) && defined(__PTRACE_SYSCALL)
#define PTRACE_SYSCALL            PTRACE_SYSCALL            /* ??? */
#endif /* !PTRACE_SYSCALL && __PTRACE_SYSCALL */
#if !defined(PTRACE_SETOPTIONS) && defined(__PTRACE_SETOPTIONS)
#define PTRACE_SETOPTIONS         PTRACE_SETOPTIONS         /* ??? */
#endif /* !PTRACE_SETOPTIONS && __PTRACE_SETOPTIONS */
#if !defined(PTRACE_GETEVENTMSG) && defined(__PTRACE_GETEVENTMSG)
#define PTRACE_GETEVENTMSG        PTRACE_GETEVENTMSG        /* ??? */
#endif /* !PTRACE_GETEVENTMSG && __PTRACE_GETEVENTMSG */
#if !defined(PTRACE_GETSIGINFO) && defined(__PTRACE_GETSIGINFO)
#define PTRACE_GETSIGINFO         PTRACE_GETSIGINFO         /* ??? */
#endif /* !PTRACE_GETSIGINFO && __PTRACE_GETSIGINFO */
#if !defined(PTRACE_SETSIGINFO) && defined(__PTRACE_SETSIGINFO)
#define PTRACE_SETSIGINFO         PTRACE_SETSIGINFO         /* ??? */
#endif /* !PTRACE_SETSIGINFO && __PTRACE_SETSIGINFO */
#if !defined(PTRACE_GETREGSET) && defined(__PTRACE_GETREGSET)
#define PTRACE_GETREGSET          PTRACE_GETREGSET          /* ??? */
#endif /* !PTRACE_GETREGSET && __PTRACE_GETREGSET */
#if !defined(PTRACE_SETREGSET) && defined(__PTRACE_SETREGSET)
#define PTRACE_SETREGSET          PTRACE_SETREGSET          /* ??? */
#endif /* !PTRACE_SETREGSET && __PTRACE_SETREGSET */
#if !defined(PTRACE_SEIZE) && defined(__PTRACE_SEIZE)
#define PTRACE_SEIZE              PTRACE_SEIZE              /* ??? */
#endif /* !PTRACE_SEIZE && __PTRACE_SEIZE */
#if !defined(PTRACE_INTERRUPT) && defined(__PTRACE_INTERRUPT)
#define PTRACE_INTERRUPT          PTRACE_INTERRUPT          /* ??? */
#endif /* !PTRACE_INTERRUPT && __PTRACE_INTERRUPT */
#if !defined(PTRACE_LISTEN) && defined(__PTRACE_LISTEN)
#define PTRACE_LISTEN             PTRACE_LISTEN             /* ??? */
#endif /* !PTRACE_LISTEN && __PTRACE_LISTEN */
#if !defined(PTRACE_PEEKSIGINFO) && defined(__PTRACE_PEEKSIGINFO)
#define PTRACE_PEEKSIGINFO        PTRACE_PEEKSIGINFO        /* ??? */
#endif /* !PTRACE_PEEKSIGINFO && __PTRACE_PEEKSIGINFO */
#if !defined(PTRACE_GETSIGMASK) && defined(__PTRACE_GETSIGMASK)
#define PTRACE_GETSIGMASK         PTRACE_GETSIGMASK         /* ??? */
#endif /* !PTRACE_GETSIGMASK && __PTRACE_GETSIGMASK */
#if !defined(PTRACE_SETSIGMASK) && defined(__PTRACE_SETSIGMASK)
#define PTRACE_SETSIGMASK         PTRACE_SETSIGMASK         /* ??? */
#endif /* !PTRACE_SETSIGMASK && __PTRACE_SETSIGMASK */
#if !defined(PTRACE_SECCOMP_GET_FILTER) && defined(__PTRACE_SECCOMP_GET_FILTER)
#define PTRACE_SECCOMP_GET_FILTER PTRACE_SECCOMP_GET_FILTER /* ??? */
#endif /* !PTRACE_SECCOMP_GET_FILTER && __PTRACE_SECCOMP_GET_FILTER */

#if !defined(PT_TRACE_ME) && defined(__PTRACE_TRACEME)
#define PT_TRACE_ME               PT_TRACE_ME               /* ??? */
#endif /* !PT_TRACE_ME && __PTRACE_TRACEME */
#if !defined(PT_READ_I) && defined(__PTRACE_PEEKTEXT)
#define PT_READ_I                 PT_READ_I                 /* ??? */
#endif /* !PT_READ_I && __PTRACE_PEEKTEXT */
#if !defined(PT_READ_D) && defined(__PTRACE_PEEKDATA)
#define PT_READ_D                 PT_READ_D                 /* ??? */
#endif /* !PT_READ_D && __PTRACE_PEEKDATA */
#if !defined(PT_READ_U) && defined(__PTRACE_PEEKUSER)
#define PT_READ_U                 PT_READ_U                 /* ??? */
#endif /* !PT_READ_U && __PTRACE_PEEKUSER */
#if !defined(PT_WRITE_I) && defined(__PTRACE_POKETEXT)
#define PT_WRITE_I                PT_WRITE_I                /* ??? */
#endif /* !PT_WRITE_I && __PTRACE_POKETEXT */
#if !defined(PT_WRITE_D) && defined(__PTRACE_POKEDATA)
#define PT_WRITE_D                PT_WRITE_D                /* ??? */
#endif /* !PT_WRITE_D && __PTRACE_POKEDATA */
#if !defined(PT_WRITE_U) && defined(__PTRACE_POKEUSER)
#define PT_WRITE_U                PT_WRITE_U                /* ??? */
#endif /* !PT_WRITE_U && __PTRACE_POKEUSER */
#if !defined(PT_CONTINUE) && defined(__PTRACE_CONT)
#define PT_CONTINUE               PT_CONTINUE               /* ??? */
#endif /* !PT_CONTINUE && __PTRACE_CONT */
#if !defined(PT_KILL) && defined(__PTRACE_KILL)
#define PT_KILL                   PT_KILL                   /* ??? */
#endif /* !PT_KILL && __PTRACE_KILL */
#if !defined(PT_STEP) && defined(__PTRACE_SINGLESTEP)
#define PT_STEP                   PT_STEP                   /* ??? */
#endif /* !PT_STEP && __PTRACE_SINGLESTEP */
#if !defined(PT_GETREGS) && defined(__PTRACE_GETREGS)
#define PT_GETREGS                PT_GETREGS                /* ??? */
#endif /* !PT_GETREGS && __PTRACE_GETREGS */
#if !defined(PT_SETREGS) && defined(__PTRACE_SETREGS)
#define PT_SETREGS                PT_SETREGS                /* ??? */
#endif /* !PT_SETREGS && __PTRACE_SETREGS */
#if !defined(PT_GETFPREGS) && defined(__PTRACE_GETFPREGS)
#define PT_GETFPREGS              PT_GETFPREGS              /* ??? */
#endif /* !PT_GETFPREGS && __PTRACE_GETFPREGS */
#if !defined(PT_SETFPREGS) && defined(__PTRACE_SETFPREGS)
#define PT_SETFPREGS              PT_SETFPREGS              /* ??? */
#endif /* !PT_SETFPREGS && __PTRACE_SETFPREGS */
#if !defined(PT_ATTACH) && defined(__PTRACE_ATTACH)
#define PT_ATTACH                 PT_ATTACH                 /* ??? */
#endif /* !PT_ATTACH && __PTRACE_ATTACH */
#if !defined(PT_DETACH) && defined(__PTRACE_DETACH)
#define PT_DETACH                 PT_DETACH                 /* ??? */
#endif /* !PT_DETACH && __PTRACE_DETACH */
#if !defined(PT_GETFPXREGS) && defined(__PTRACE_GETFPXREGS)
#define PT_GETFPXREGS             PT_GETFPXREGS             /* ??? */
#endif /* !PT_GETFPXREGS && __PTRACE_GETFPXREGS */
#if !defined(PT_SETFPXREGS) && defined(__PTRACE_SETFPXREGS)
#define PT_SETFPXREGS             PT_SETFPXREGS             /* ??? */
#endif /* !PT_SETFPXREGS && __PTRACE_SETFPXREGS */
#if !defined(PT_SYSCALL) && defined(__PTRACE_SYSCALL)
#define PT_SYSCALL                PT_SYSCALL                /* ??? */
#endif /* !PT_SYSCALL && __PTRACE_SYSCALL */
#if !defined(PT_SETOPTIONS) && defined(__PTRACE_SETOPTIONS)
#define PT_SETOPTIONS             PT_SETOPTIONS             /* ??? */
#endif /* !PT_SETOPTIONS && __PTRACE_SETOPTIONS */
#if !defined(PT_GETEVENTMSG) && defined(__PTRACE_GETEVENTMSG)
#define PT_GETEVENTMSG            PT_GETEVENTMSG            /* ??? */
#endif /* !PT_GETEVENTMSG && __PTRACE_GETEVENTMSG */
#if !defined(PT_GETSIGINFO) && defined(__PTRACE_GETSIGINFO)
#define PT_GETSIGINFO             PT_GETSIGINFO             /* ??? */
#endif /* !PT_GETSIGINFO && __PTRACE_GETSIGINFO */
#if !defined(PT_SETSIGINFO) && defined(__PTRACE_SETSIGINFO)
#define PT_SETSIGINFO             PT_SETSIGINFO             /* ??? */
#endif /* !PT_SETSIGINFO && __PTRACE_SETSIGINFO */
#else /* __COMPILER_PREFERR_ENUMS */
#if !defined(PTRACE_TRACEME) && defined(__PTRACE_TRACEME)
#define PTRACE_TRACEME            __PTRACE_TRACEME            /* ??? */
#endif /* !PTRACE_TRACEME && __PTRACE_TRACEME */
#if !defined(PTRACE_PEEKTEXT) && defined(__PTRACE_PEEKTEXT)
#define PTRACE_PEEKTEXT           __PTRACE_PEEKTEXT           /* ??? */
#endif /* !PTRACE_PEEKTEXT && __PTRACE_PEEKTEXT */
#if !defined(PTRACE_PEEKDATA) && defined(__PTRACE_PEEKDATA)
#define PTRACE_PEEKDATA           __PTRACE_PEEKDATA           /* ??? */
#endif /* !PTRACE_PEEKDATA && __PTRACE_PEEKDATA */
#if !defined(PTRACE_PEEKUSER) && defined(__PTRACE_PEEKUSER)
#define PTRACE_PEEKUSER           __PTRACE_PEEKUSER           /* ??? */
#endif /* !PTRACE_PEEKUSER && __PTRACE_PEEKUSER */
#if !defined(PTRACE_POKETEXT) && defined(__PTRACE_POKETEXT)
#define PTRACE_POKETEXT           __PTRACE_POKETEXT           /* ??? */
#endif /* !PTRACE_POKETEXT && __PTRACE_POKETEXT */
#if !defined(PTRACE_POKEDATA) && defined(__PTRACE_POKEDATA)
#define PTRACE_POKEDATA           __PTRACE_POKEDATA           /* ??? */
#endif /* !PTRACE_POKEDATA && __PTRACE_POKEDATA */
#if !defined(PTRACE_POKEUSER) && defined(__PTRACE_POKEUSER)
#define PTRACE_POKEUSER           __PTRACE_POKEUSER           /* ??? */
#endif /* !PTRACE_POKEUSER && __PTRACE_POKEUSER */
#if !defined(PTRACE_CONT) && defined(__PTRACE_CONT)
#define PTRACE_CONT               __PTRACE_CONT               /* ??? */
#endif /* !PTRACE_CONT && __PTRACE_CONT */
#if !defined(PTRACE_KILL) && defined(__PTRACE_KILL)
#define PTRACE_KILL               __PTRACE_KILL               /* ??? */
#endif /* !PTRACE_KILL && __PTRACE_KILL */
#if !defined(PTRACE_SINGLESTEP) && defined(__PTRACE_SINGLESTEP)
#define PTRACE_SINGLESTEP         __PTRACE_SINGLESTEP         /* ??? */
#endif /* !PTRACE_SINGLESTEP && __PTRACE_SINGLESTEP */
#if !defined(PTRACE_GETREGS) && defined(__PTRACE_GETREGS)
#define PTRACE_GETREGS            __PTRACE_GETREGS            /* ??? */
#endif /* !PTRACE_GETREGS && __PTRACE_GETREGS */
#if !defined(PTRACE_SETREGS) && defined(__PTRACE_SETREGS)
#define PTRACE_SETREGS            __PTRACE_SETREGS            /* ??? */
#endif /* !PTRACE_SETREGS && __PTRACE_SETREGS */
#if !defined(PTRACE_GETFPREGS) && defined(__PTRACE_GETFPREGS)
#define PTRACE_GETFPREGS          __PTRACE_GETFPREGS          /* ??? */
#endif /* !PTRACE_GETFPREGS && __PTRACE_GETFPREGS */
#if !defined(PTRACE_SETFPREGS) && defined(__PTRACE_SETFPREGS)
#define PTRACE_SETFPREGS          __PTRACE_SETFPREGS          /* ??? */
#endif /* !PTRACE_SETFPREGS && __PTRACE_SETFPREGS */
#if !defined(PTRACE_ATTACH) && defined(__PTRACE_ATTACH)
#define PTRACE_ATTACH             __PTRACE_ATTACH             /* ??? */
#endif /* !PTRACE_ATTACH && __PTRACE_ATTACH */
#if !defined(PTRACE_DETACH) && defined(__PTRACE_DETACH)
#define PTRACE_DETACH             __PTRACE_DETACH             /* ??? */
#endif /* !PTRACE_DETACH && __PTRACE_DETACH */
#if !defined(PTRACE_GETFPXREGS) && defined(__PTRACE_GETFPXREGS)
#define PTRACE_GETFPXREGS         __PTRACE_GETFPXREGS         /* ??? */
#endif /* !PTRACE_GETFPXREGS && __PTRACE_GETFPXREGS */
#if !defined(PTRACE_SETFPXREGS) && defined(__PTRACE_SETFPXREGS)
#define PTRACE_SETFPXREGS         __PTRACE_SETFPXREGS         /* ??? */
#endif /* !PTRACE_SETFPXREGS && __PTRACE_SETFPXREGS */
#if !defined(PTRACE_SYSCALL) && defined(__PTRACE_SYSCALL)
#define PTRACE_SYSCALL            __PTRACE_SYSCALL            /* ??? */
#endif /* !PTRACE_SYSCALL && __PTRACE_SYSCALL */
#if !defined(PTRACE_SETOPTIONS) && defined(__PTRACE_SETOPTIONS)
#define PTRACE_SETOPTIONS         __PTRACE_SETOPTIONS         /* ??? */
#endif /* !PTRACE_SETOPTIONS && __PTRACE_SETOPTIONS */
#if !defined(PTRACE_GETEVENTMSG) && defined(__PTRACE_GETEVENTMSG)
#define PTRACE_GETEVENTMSG        __PTRACE_GETEVENTMSG        /* ??? */
#endif /* !PTRACE_GETEVENTMSG && __PTRACE_GETEVENTMSG */
#if !defined(PTRACE_GETSIGINFO) && defined(__PTRACE_GETSIGINFO)
#define PTRACE_GETSIGINFO         __PTRACE_GETSIGINFO         /* ??? */
#endif /* !PTRACE_GETSIGINFO && __PTRACE_GETSIGINFO */
#if !defined(PTRACE_SETSIGINFO) && defined(__PTRACE_SETSIGINFO)
#define PTRACE_SETSIGINFO         __PTRACE_SETSIGINFO         /* ??? */
#endif /* !PTRACE_SETSIGINFO && __PTRACE_SETSIGINFO */
#if !defined(PTRACE_GETREGSET) && defined(__PTRACE_GETREGSET)
#define PTRACE_GETREGSET          __PTRACE_GETREGSET          /* ??? */
#endif /* !PTRACE_GETREGSET && __PTRACE_GETREGSET */
#if !defined(PTRACE_SETREGSET) && defined(__PTRACE_SETREGSET)
#define PTRACE_SETREGSET          __PTRACE_SETREGSET          /* ??? */
#endif /* !PTRACE_SETREGSET && __PTRACE_SETREGSET */
#if !defined(PTRACE_SEIZE) && defined(__PTRACE_SEIZE)
#define PTRACE_SEIZE              __PTRACE_SEIZE              /* ??? */
#endif /* !PTRACE_SEIZE && __PTRACE_SEIZE */
#if !defined(PTRACE_INTERRUPT) && defined(__PTRACE_INTERRUPT)
#define PTRACE_INTERRUPT          __PTRACE_INTERRUPT          /* ??? */
#endif /* !PTRACE_INTERRUPT && __PTRACE_INTERRUPT */
#if !defined(PTRACE_LISTEN) && defined(__PTRACE_LISTEN)
#define PTRACE_LISTEN             __PTRACE_LISTEN             /* ??? */
#endif /* !PTRACE_LISTEN && __PTRACE_LISTEN */
#if !defined(PTRACE_PEEKSIGINFO) && defined(__PTRACE_PEEKSIGINFO)
#define PTRACE_PEEKSIGINFO        __PTRACE_PEEKSIGINFO        /* ??? */
#endif /* !PTRACE_PEEKSIGINFO && __PTRACE_PEEKSIGINFO */
#if !defined(PTRACE_GETSIGMASK) && defined(__PTRACE_GETSIGMASK)
#define PTRACE_GETSIGMASK         __PTRACE_GETSIGMASK         /* ??? */
#endif /* !PTRACE_GETSIGMASK && __PTRACE_GETSIGMASK */
#if !defined(PTRACE_SETSIGMASK) && defined(__PTRACE_SETSIGMASK)
#define PTRACE_SETSIGMASK         __PTRACE_SETSIGMASK         /* ??? */
#endif /* !PTRACE_SETSIGMASK && __PTRACE_SETSIGMASK */
#if !defined(PTRACE_SECCOMP_GET_FILTER) && defined(__PTRACE_SECCOMP_GET_FILTER)
#define PTRACE_SECCOMP_GET_FILTER __PTRACE_SECCOMP_GET_FILTER /* ??? */
#endif /* !PTRACE_SECCOMP_GET_FILTER && __PTRACE_SECCOMP_GET_FILTER */

#if !defined(PT_TRACE_ME) && defined(__PTRACE_TRACEME)
#define PT_TRACE_ME               __PTRACE_TRACEME            /* ??? */
#endif /* !PT_TRACE_ME && __PTRACE_TRACEME */
#if !defined(PT_READ_I) && defined(__PTRACE_PEEKTEXT)
#define PT_READ_I                 __PTRACE_PEEKTEXT           /* ??? */
#endif /* !PT_READ_I && __PTRACE_PEEKTEXT */
#if !defined(PT_READ_D) && defined(__PTRACE_PEEKDATA)
#define PT_READ_D                 __PTRACE_PEEKDATA           /* ??? */
#endif /* !PT_READ_D && __PTRACE_PEEKDATA */
#if !defined(PT_READ_U) && defined(__PTRACE_PEEKUSER)
#define PT_READ_U                 __PTRACE_PEEKUSER           /* ??? */
#endif /* !PT_READ_U && __PTRACE_PEEKUSER */
#if !defined(PT_WRITE_I) && defined(__PTRACE_POKETEXT)
#define PT_WRITE_I                __PTRACE_POKETEXT           /* ??? */
#endif /* !PT_WRITE_I && __PTRACE_POKETEXT */
#if !defined(PT_WRITE_D) && defined(__PTRACE_POKEDATA)
#define PT_WRITE_D                __PTRACE_POKEDATA           /* ??? */
#endif /* !PT_WRITE_D && __PTRACE_POKEDATA */
#if !defined(PT_WRITE_U) && defined(__PTRACE_POKEUSER)
#define PT_WRITE_U                __PTRACE_POKEUSER           /* ??? */
#endif /* !PT_WRITE_U && __PTRACE_POKEUSER */
#if !defined(PT_CONTINUE) && defined(__PTRACE_CONT)
#define PT_CONTINUE               __PTRACE_CONT               /* ??? */
#endif /* !PT_CONTINUE && __PTRACE_CONT */
#if !defined(PT_KILL) && defined(__PTRACE_KILL)
#define PT_KILL                   __PTRACE_KILL               /* ??? */
#endif /* !PT_KILL && __PTRACE_KILL */
#if !defined(PT_STEP) && defined(__PTRACE_SINGLESTEP)
#define PT_STEP                   __PTRACE_SINGLESTEP         /* ??? */
#endif /* !PT_STEP && __PTRACE_SINGLESTEP */
#if !defined(PT_GETREGS) && defined(__PTRACE_GETREGS)
#define PT_GETREGS                __PTRACE_GETREGS            /* ??? */
#endif /* !PT_GETREGS && __PTRACE_GETREGS */
#if !defined(PT_SETREGS) && defined(__PTRACE_SETREGS)
#define PT_SETREGS                __PTRACE_SETREGS            /* ??? */
#endif /* !PT_SETREGS && __PTRACE_SETREGS */
#if !defined(PT_GETFPREGS) && defined(__PTRACE_GETFPREGS)
#define PT_GETFPREGS              __PTRACE_GETFPREGS          /* ??? */
#endif /* !PT_GETFPREGS && __PTRACE_GETFPREGS */
#if !defined(PT_SETFPREGS) && defined(__PTRACE_SETFPREGS)
#define PT_SETFPREGS              __PTRACE_SETFPREGS          /* ??? */
#endif /* !PT_SETFPREGS && __PTRACE_SETFPREGS */
#if !defined(PT_ATTACH) && defined(__PTRACE_ATTACH)
#define PT_ATTACH                 __PTRACE_ATTACH             /* ??? */
#endif /* !PT_ATTACH && __PTRACE_ATTACH */
#if !defined(PT_DETACH) && defined(__PTRACE_DETACH)
#define PT_DETACH                 __PTRACE_DETACH             /* ??? */
#endif /* !PT_DETACH && __PTRACE_DETACH */
#if !defined(PT_GETFPXREGS) && defined(__PTRACE_GETFPXREGS)
#define PT_GETFPXREGS             __PTRACE_GETFPXREGS         /* ??? */
#endif /* !PT_GETFPXREGS && __PTRACE_GETFPXREGS */
#if !defined(PT_SETFPXREGS) && defined(__PTRACE_SETFPXREGS)
#define PT_SETFPXREGS             __PTRACE_SETFPXREGS         /* ??? */
#endif /* !PT_SETFPXREGS && __PTRACE_SETFPXREGS */
#if !defined(PT_SYSCALL) && defined(__PTRACE_SYSCALL)
#define PT_SYSCALL                __PTRACE_SYSCALL            /* ??? */
#endif /* !PT_SYSCALL && __PTRACE_SYSCALL */
#if !defined(PT_SETOPTIONS) && defined(__PTRACE_SETOPTIONS)
#define PT_SETOPTIONS             __PTRACE_SETOPTIONS         /* ??? */
#endif /* !PT_SETOPTIONS && __PTRACE_SETOPTIONS */
#if !defined(PT_GETEVENTMSG) && defined(__PTRACE_GETEVENTMSG)
#define PT_GETEVENTMSG            __PTRACE_GETEVENTMSG        /* ??? */
#endif /* !PT_GETEVENTMSG && __PTRACE_GETEVENTMSG */
#if !defined(PT_GETSIGINFO) && defined(__PTRACE_GETSIGINFO)
#define PT_GETSIGINFO             __PTRACE_GETSIGINFO         /* ??? */
#endif /* !PT_GETSIGINFO && __PTRACE_GETSIGINFO */
#if !defined(PT_SETSIGINFO) && defined(__PTRACE_SETSIGINFO)
#define PT_SETSIGINFO             __PTRACE_SETSIGINFO         /* ??? */
#endif /* !PT_SETSIGINFO && __PTRACE_SETSIGINFO */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/
#elif defined(__CC__)
typedef int __ptrace_request_t;
#endif /* ... */


#if !defined(PTRACE_SEIZE_DEVEL) && defined(__PTRACE_SEIZE_DEVEL)
/* Flag accepted by `PTRACE_LISTEN' */
/*[[[enum]]]*/
#ifdef __CC__
enum __ptrace_flags {
	PTRACE_SEIZE_DEVEL = __PTRACE_SEIZE_DEVEL /* ??? */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#define PTRACE_SEIZE_DEVEL PTRACE_SEIZE_DEVEL /* ??? */
#else /* __COMPILER_PREFERR_ENUMS */
#define PTRACE_SEIZE_DEVEL __PTRACE_SEIZE_DEVEL /* ??? */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/
#endif /* !PTRACE_SEIZE_DEVEL && __PTRACE_SEIZE_DEVEL */


#if ((!defined(PTRACE_O_TRACESYSGOOD) && defined(__PTRACE_O_TRACESYSGOOD)) ||    \
     (!defined(PTRACE_O_TRACEFORK) && defined(__PTRACE_O_TRACEFORK)) ||       \
     (!defined(PTRACE_O_TRACEVFORK) && defined(__PTRACE_O_TRACEVFORK)) ||      \
     (!defined(PTRACE_O_TRACECLONE) && defined(__PTRACE_O_TRACECLONE)) ||      \
     (!defined(PTRACE_O_TRACEEXEC) && defined(__PTRACE_O_TRACEEXEC)) ||       \
     (!defined(PTRACE_O_TRACEVFORKDONE) && defined(__PTRACE_O_TRACEVFORKDONE)) ||  \
     (!defined(PTRACE_O_TRACEEXIT) && defined(__PTRACE_O_TRACEEXIT)) ||       \
     (!defined(PTRACE_O_TRACESECCOMP) && defined(__PTRACE_O_TRACESECCOMP)) ||    \
     (!defined(PTRACE_O_EXITKILL) && defined(__PTRACE_O_EXITKILL)) ||        \
     (!defined(PTRACE_O_SUSPEND_SECCOMP) && defined(__PTRACE_O_SUSPEND_SECCOMP)) || \
     (!defined(PTRACE_O_MASK) && defined(__PTRACE_O_MASK)))
/* Flag accepted by `PTRACE_SETOPTIONS'. */
/*[[[enum]]]*/
#ifdef __CC__
enum __ptrace_setoptions {
#if !defined(PTRACE_O_TRACESYSGOOD) && defined(__PTRACE_O_TRACESYSGOOD)
	PTRACE_O_TRACESYSGOOD = __PTRACE_O_TRACESYSGOOD, /* ??? */
#endif /* !PTRACE_O_TRACESYSGOOD && __PTRACE_O_TRACESYSGOOD */
#if !defined(PTRACE_O_TRACEFORK) && defined(__PTRACE_O_TRACEFORK)
	PTRACE_O_TRACEFORK = __PTRACE_O_TRACEFORK, /* ??? */
#endif /* !PTRACE_O_TRACEFORK && __PTRACE_O_TRACEFORK */
#if !defined(PTRACE_O_TRACEVFORK) && defined(__PTRACE_O_TRACEVFORK)
	PTRACE_O_TRACEVFORK = __PTRACE_O_TRACEVFORK, /* ??? */
#endif /* !PTRACE_O_TRACEVFORK && __PTRACE_O_TRACEVFORK */
#if !defined(PTRACE_O_TRACECLONE) && defined(__PTRACE_O_TRACECLONE)
	PTRACE_O_TRACECLONE = __PTRACE_O_TRACECLONE, /* ??? */
#endif /* !PTRACE_O_TRACECLONE && __PTRACE_O_TRACECLONE */
#if !defined(PTRACE_O_TRACEEXEC) && defined(__PTRACE_O_TRACEEXEC)
	PTRACE_O_TRACEEXEC = __PTRACE_O_TRACEEXEC, /* ??? */
#endif /* !PTRACE_O_TRACEEXEC && __PTRACE_O_TRACEEXEC */
#if !defined(PTRACE_O_TRACEVFORKDONE) && defined(__PTRACE_O_TRACEVFORKDONE)
	PTRACE_O_TRACEVFORKDONE = __PTRACE_O_TRACEVFORKDONE, /* ??? */
#endif /* !PTRACE_O_TRACEVFORKDONE && __PTRACE_O_TRACEVFORKDONE */
#if !defined(PTRACE_O_TRACEEXIT) && defined(__PTRACE_O_TRACEEXIT)
	PTRACE_O_TRACEEXIT = __PTRACE_O_TRACEEXIT, /* ??? */
#endif /* !PTRACE_O_TRACEEXIT && __PTRACE_O_TRACEEXIT */
#if !defined(PTRACE_O_TRACESECCOMP) && defined(__PTRACE_O_TRACESECCOMP)
	PTRACE_O_TRACESECCOMP = __PTRACE_O_TRACESECCOMP, /* ??? */
#endif /* !PTRACE_O_TRACESECCOMP && __PTRACE_O_TRACESECCOMP */
#if !defined(PTRACE_O_EXITKILL) && defined(__PTRACE_O_EXITKILL)
	PTRACE_O_EXITKILL = __PTRACE_O_EXITKILL, /* ??? */
#endif /* !PTRACE_O_EXITKILL && __PTRACE_O_EXITKILL */
#if !defined(PTRACE_O_SUSPEND_SECCOMP) && defined(__PTRACE_O_SUSPEND_SECCOMP)
	PTRACE_O_SUSPEND_SECCOMP = __PTRACE_O_SUSPEND_SECCOMP, /* ??? */
#endif /* !PTRACE_O_SUSPEND_SECCOMP && __PTRACE_O_SUSPEND_SECCOMP */
#if !defined(PTRACE_O_MASK) && defined(__PTRACE_O_MASK)
	PTRACE_O_MASK = __PTRACE_O_MASK /* ??? */
#endif /* !PTRACE_O_MASK && __PTRACE_O_MASK */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#if !defined(PTRACE_O_TRACESYSGOOD) && defined(__PTRACE_O_TRACESYSGOOD)
#define PTRACE_O_TRACESYSGOOD    PTRACE_O_TRACESYSGOOD    /* ??? */
#endif /* !PTRACE_O_TRACESYSGOOD && __PTRACE_O_TRACESYSGOOD */
#if !defined(PTRACE_O_TRACEFORK) && defined(__PTRACE_O_TRACEFORK)
#define PTRACE_O_TRACEFORK       PTRACE_O_TRACEFORK       /* ??? */
#endif /* !PTRACE_O_TRACEFORK && __PTRACE_O_TRACEFORK */
#if !defined(PTRACE_O_TRACEVFORK) && defined(__PTRACE_O_TRACEVFORK)
#define PTRACE_O_TRACEVFORK      PTRACE_O_TRACEVFORK      /* ??? */
#endif /* !PTRACE_O_TRACEVFORK && __PTRACE_O_TRACEVFORK */
#if !defined(PTRACE_O_TRACECLONE) && defined(__PTRACE_O_TRACECLONE)
#define PTRACE_O_TRACECLONE      PTRACE_O_TRACECLONE      /* ??? */
#endif /* !PTRACE_O_TRACECLONE && __PTRACE_O_TRACECLONE */
#if !defined(PTRACE_O_TRACEEXEC) && defined(__PTRACE_O_TRACEEXEC)
#define PTRACE_O_TRACEEXEC       PTRACE_O_TRACEEXEC       /* ??? */
#endif /* !PTRACE_O_TRACEEXEC && __PTRACE_O_TRACEEXEC */
#if !defined(PTRACE_O_TRACEVFORKDONE) && defined(__PTRACE_O_TRACEVFORKDONE)
#define PTRACE_O_TRACEVFORKDONE  PTRACE_O_TRACEVFORKDONE  /* ??? */
#endif /* !PTRACE_O_TRACEVFORKDONE && __PTRACE_O_TRACEVFORKDONE */
#if !defined(PTRACE_O_TRACEEXIT) && defined(__PTRACE_O_TRACEEXIT)
#define PTRACE_O_TRACEEXIT       PTRACE_O_TRACEEXIT       /* ??? */
#endif /* !PTRACE_O_TRACEEXIT && __PTRACE_O_TRACEEXIT */
#if !defined(PTRACE_O_TRACESECCOMP) && defined(__PTRACE_O_TRACESECCOMP)
#define PTRACE_O_TRACESECCOMP    PTRACE_O_TRACESECCOMP    /* ??? */
#endif /* !PTRACE_O_TRACESECCOMP && __PTRACE_O_TRACESECCOMP */
#if !defined(PTRACE_O_EXITKILL) && defined(__PTRACE_O_EXITKILL)
#define PTRACE_O_EXITKILL        PTRACE_O_EXITKILL        /* ??? */
#endif /* !PTRACE_O_EXITKILL && __PTRACE_O_EXITKILL */
#if !defined(PTRACE_O_SUSPEND_SECCOMP) && defined(__PTRACE_O_SUSPEND_SECCOMP)
#define PTRACE_O_SUSPEND_SECCOMP PTRACE_O_SUSPEND_SECCOMP /* ??? */
#endif /* !PTRACE_O_SUSPEND_SECCOMP && __PTRACE_O_SUSPEND_SECCOMP */
#if !defined(PTRACE_O_MASK) && defined(__PTRACE_O_MASK)
#define PTRACE_O_MASK            PTRACE_O_MASK            /* ??? */
#endif /* !PTRACE_O_MASK && __PTRACE_O_MASK */
#else /* __COMPILER_PREFERR_ENUMS */
#if !defined(PTRACE_O_TRACESYSGOOD) && defined(__PTRACE_O_TRACESYSGOOD)
#define PTRACE_O_TRACESYSGOOD    __PTRACE_O_TRACESYSGOOD    /* ??? */
#endif /* !PTRACE_O_TRACESYSGOOD && __PTRACE_O_TRACESYSGOOD */
#if !defined(PTRACE_O_TRACEFORK) && defined(__PTRACE_O_TRACEFORK)
#define PTRACE_O_TRACEFORK       __PTRACE_O_TRACEFORK       /* ??? */
#endif /* !PTRACE_O_TRACEFORK && __PTRACE_O_TRACEFORK */
#if !defined(PTRACE_O_TRACEVFORK) && defined(__PTRACE_O_TRACEVFORK)
#define PTRACE_O_TRACEVFORK      __PTRACE_O_TRACEVFORK      /* ??? */
#endif /* !PTRACE_O_TRACEVFORK && __PTRACE_O_TRACEVFORK */
#if !defined(PTRACE_O_TRACECLONE) && defined(__PTRACE_O_TRACECLONE)
#define PTRACE_O_TRACECLONE      __PTRACE_O_TRACECLONE      /* ??? */
#endif /* !PTRACE_O_TRACECLONE && __PTRACE_O_TRACECLONE */
#if !defined(PTRACE_O_TRACEEXEC) && defined(__PTRACE_O_TRACEEXEC)
#define PTRACE_O_TRACEEXEC       __PTRACE_O_TRACEEXEC       /* ??? */
#endif /* !PTRACE_O_TRACEEXEC && __PTRACE_O_TRACEEXEC */
#if !defined(PTRACE_O_TRACEVFORKDONE) && defined(__PTRACE_O_TRACEVFORKDONE)
#define PTRACE_O_TRACEVFORKDONE  __PTRACE_O_TRACEVFORKDONE  /* ??? */
#endif /* !PTRACE_O_TRACEVFORKDONE && __PTRACE_O_TRACEVFORKDONE */
#if !defined(PTRACE_O_TRACEEXIT) && defined(__PTRACE_O_TRACEEXIT)
#define PTRACE_O_TRACEEXIT       __PTRACE_O_TRACEEXIT       /* ??? */
#endif /* !PTRACE_O_TRACEEXIT && __PTRACE_O_TRACEEXIT */
#if !defined(PTRACE_O_TRACESECCOMP) && defined(__PTRACE_O_TRACESECCOMP)
#define PTRACE_O_TRACESECCOMP    __PTRACE_O_TRACESECCOMP    /* ??? */
#endif /* !PTRACE_O_TRACESECCOMP && __PTRACE_O_TRACESECCOMP */
#if !defined(PTRACE_O_EXITKILL) && defined(__PTRACE_O_EXITKILL)
#define PTRACE_O_EXITKILL        __PTRACE_O_EXITKILL        /* ??? */
#endif /* !PTRACE_O_EXITKILL && __PTRACE_O_EXITKILL */
#if !defined(PTRACE_O_SUSPEND_SECCOMP) && defined(__PTRACE_O_SUSPEND_SECCOMP)
#define PTRACE_O_SUSPEND_SECCOMP __PTRACE_O_SUSPEND_SECCOMP /* ??? */
#endif /* !PTRACE_O_SUSPEND_SECCOMP && __PTRACE_O_SUSPEND_SECCOMP */
#if !defined(PTRACE_O_MASK) && defined(__PTRACE_O_MASK)
#define PTRACE_O_MASK            __PTRACE_O_MASK            /* ??? */
#endif /* !PTRACE_O_MASK && __PTRACE_O_MASK */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/
#endif /* .. */


#if ((!defined(PTRACE_EVENT_FORK) && defined(__PTRACE_EVENT_FORK)) ||             \
     (!defined(PTRACE_EVENT_VFORK) && defined(__PTRACE_EVENT_VFORK)) ||           \
     (!defined(PTRACE_EVENT_CLONE) && defined(__PTRACE_EVENT_CLONE)) ||           \
     (!defined(PTRACE_EVENT_EXEC) && defined(__PTRACE_EVENT_EXEC)) ||             \
     (!defined(PTRACE_EVENT_VFORK_DONE) && defined(__PTRACE_EVENT_VFORK_DONE)) || \
     (!defined(PTRACE_EVENT_EXIT) && defined(__PTRACE_EVENT_EXIT)) ||             \
     (!defined(PTRACE_EVENT_SECCOMP) && defined(__PTRACE_EVENT_SECCOMP)))
/* Extended wait-result-codes for trace options. */
/*[[[enum]]]*/
#ifdef __CC__
enum __ptrace_eventcodes {
#if !defined(PTRACE_EVENT_FORK) && defined(__PTRACE_EVENT_FORK)
	PTRACE_EVENT_FORK = __PTRACE_EVENT_FORK, /* ??? */
#endif /* !PTRACE_EVENT_FORK && __PTRACE_EVENT_FORK */
#if !defined(PTRACE_EVENT_VFORK) && defined(__PTRACE_EVENT_VFORK)
	PTRACE_EVENT_VFORK = __PTRACE_EVENT_VFORK, /* ??? */
#endif /* !PTRACE_EVENT_VFORK && __PTRACE_EVENT_VFORK */
#if !defined(PTRACE_EVENT_CLONE) && defined(__PTRACE_EVENT_CLONE)
	PTRACE_EVENT_CLONE = __PTRACE_EVENT_CLONE, /* ??? */
#endif /* !PTRACE_EVENT_CLONE && __PTRACE_EVENT_CLONE */
#if !defined(PTRACE_EVENT_EXEC) && defined(__PTRACE_EVENT_EXEC)
	PTRACE_EVENT_EXEC = __PTRACE_EVENT_EXEC, /* ??? */
#endif /* !PTRACE_EVENT_EXEC && __PTRACE_EVENT_EXEC */
#if !defined(PTRACE_EVENT_VFORK_DONE) && defined(__PTRACE_EVENT_VFORK_DONE)
	PTRACE_EVENT_VFORK_DONE = __PTRACE_EVENT_VFORK_DONE, /* ??? */
#endif /* !PTRACE_EVENT_VFORK_DONE && __PTRACE_EVENT_VFORK_DONE */
#if !defined(PTRACE_EVENT_EXIT) && defined(__PTRACE_EVENT_EXIT)
	PTRACE_EVENT_EXIT = __PTRACE_EVENT_EXIT, /* ??? */
#endif /* !PTRACE_EVENT_EXIT && __PTRACE_EVENT_EXIT */
#if !defined(PTRACE_EVENT_SECCOMP) && defined(__PTRACE_EVENT_SECCOMP)
	PTRACE_EVENT_SECCOMP = __PTRACE_EVENT_SECCOMP /* ??? */
#endif /* !PTRACE_EVENT_SECCOMP && __PTRACE_EVENT_SECCOMP */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#if !defined(PTRACE_EVENT_FORK) && defined(__PTRACE_EVENT_FORK)
#define PTRACE_EVENT_FORK       PTRACE_EVENT_FORK       /* ??? */
#endif /* !PTRACE_EVENT_FORK && __PTRACE_EVENT_FORK */
#if !defined(PTRACE_EVENT_VFORK) && defined(__PTRACE_EVENT_VFORK)
#define PTRACE_EVENT_VFORK      PTRACE_EVENT_VFORK      /* ??? */
#endif /* !PTRACE_EVENT_VFORK && __PTRACE_EVENT_VFORK */
#if !defined(PTRACE_EVENT_CLONE) && defined(__PTRACE_EVENT_CLONE)
#define PTRACE_EVENT_CLONE      PTRACE_EVENT_CLONE      /* ??? */
#endif /* !PTRACE_EVENT_CLONE && __PTRACE_EVENT_CLONE */
#if !defined(PTRACE_EVENT_EXEC) && defined(__PTRACE_EVENT_EXEC)
#define PTRACE_EVENT_EXEC       PTRACE_EVENT_EXEC       /* ??? */
#endif /* !PTRACE_EVENT_EXEC && __PTRACE_EVENT_EXEC */
#if !defined(PTRACE_EVENT_VFORK_DONE) && defined(__PTRACE_EVENT_VFORK_DONE)
#define PTRACE_EVENT_VFORK_DONE PTRACE_EVENT_VFORK_DONE /* ??? */
#endif /* !PTRACE_EVENT_VFORK_DONE && __PTRACE_EVENT_VFORK_DONE */
#if !defined(PTRACE_EVENT_EXIT) && defined(__PTRACE_EVENT_EXIT)
#define PTRACE_EVENT_EXIT       PTRACE_EVENT_EXIT       /* ??? */
#endif /* !PTRACE_EVENT_EXIT && __PTRACE_EVENT_EXIT */
#if !defined(PTRACE_EVENT_SECCOMP) && defined(__PTRACE_EVENT_SECCOMP)
#define PTRACE_EVENT_SECCOMP    PTRACE_EVENT_SECCOMP    /* ??? */
#endif /* !PTRACE_EVENT_SECCOMP && __PTRACE_EVENT_SECCOMP */
#else /* __COMPILER_PREFERR_ENUMS */
#if !defined(PTRACE_EVENT_FORK) && defined(__PTRACE_EVENT_FORK)
#define PTRACE_EVENT_FORK       __PTRACE_EVENT_FORK       /* ??? */
#endif /* !PTRACE_EVENT_FORK && __PTRACE_EVENT_FORK */
#if !defined(PTRACE_EVENT_VFORK) && defined(__PTRACE_EVENT_VFORK)
#define PTRACE_EVENT_VFORK      __PTRACE_EVENT_VFORK      /* ??? */
#endif /* !PTRACE_EVENT_VFORK && __PTRACE_EVENT_VFORK */
#if !defined(PTRACE_EVENT_CLONE) && defined(__PTRACE_EVENT_CLONE)
#define PTRACE_EVENT_CLONE      __PTRACE_EVENT_CLONE      /* ??? */
#endif /* !PTRACE_EVENT_CLONE && __PTRACE_EVENT_CLONE */
#if !defined(PTRACE_EVENT_EXEC) && defined(__PTRACE_EVENT_EXEC)
#define PTRACE_EVENT_EXEC       __PTRACE_EVENT_EXEC       /* ??? */
#endif /* !PTRACE_EVENT_EXEC && __PTRACE_EVENT_EXEC */
#if !defined(PTRACE_EVENT_VFORK_DONE) && defined(__PTRACE_EVENT_VFORK_DONE)
#define PTRACE_EVENT_VFORK_DONE __PTRACE_EVENT_VFORK_DONE /* ??? */
#endif /* !PTRACE_EVENT_VFORK_DONE && __PTRACE_EVENT_VFORK_DONE */
#if !defined(PTRACE_EVENT_EXIT) && defined(__PTRACE_EVENT_EXIT)
#define PTRACE_EVENT_EXIT       __PTRACE_EVENT_EXIT       /* ??? */
#endif /* !PTRACE_EVENT_EXIT && __PTRACE_EVENT_EXIT */
#if !defined(PTRACE_EVENT_SECCOMP) && defined(__PTRACE_EVENT_SECCOMP)
#define PTRACE_EVENT_SECCOMP    __PTRACE_EVENT_SECCOMP    /* ??? */
#endif /* !PTRACE_EVENT_SECCOMP && __PTRACE_EVENT_SECCOMP */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/
#endif /* ... */


#if !defined(PTRACE_PEEKSIGINFO_SHARED) && defined(__PTRACE_PEEKSIGINFO_SHARED)
/*[[[enum]]]*/
#ifdef __CC__
enum __ptrace_peeksiginfo_flags {
	PTRACE_PEEKSIGINFO_SHARED = __PTRACE_PEEKSIGINFO_SHARED /* ??? */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#define PTRACE_PEEKSIGINFO_SHARED PTRACE_PEEKSIGINFO_SHARED /* ??? */
#else /* __COMPILER_PREFERR_ENUMS */
#define PTRACE_PEEKSIGINFO_SHARED __PTRACE_PEEKSIGINFO_SHARED /* ??? */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/
#endif /* !PTRACE_PEEKSIGINFO_SHARED && __PTRACE_PEEKSIGINFO_SHARED */


#ifdef __CC__

}

[[vartypes($pid_t, void *, void *), decl_include("<hybrid/typecore.h>")]]
$longptr_t ptrace(__ptrace_request_t request, ...
                  /* pid_t pid, void *addr, void *data */);

%{

#endif /* __CC__ */

__SYSDECL_END

}
