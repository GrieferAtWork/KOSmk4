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
/*!replace_with_include <asm/os/ptrace.h>*/
#ifndef _ASM_OS_KOS_PTRACE_H
#define _ASM_OS_KOS_PTRACE_H 1

#include <__stdinc.h>

/************************************************************************/
/* KOS/LINUX                                                            */
/************************************************************************/

/* ptrace(2) request codes. */
#define __PTRACE_TRACEME            0      /* ??? */
#define __PTRACE_PEEKTEXT           1      /* ??? */
#define __PTRACE_PEEKDATA           2      /* ??? */
#define __PTRACE_PEEKUSER           3      /* ??? */
#define __PTRACE_POKETEXT           4      /* ??? */
#define __PTRACE_POKEDATA           5      /* ??? */
#define __PTRACE_POKEUSER           6      /* ??? */
#define __PTRACE_CONT               7      /* ??? */
#define __PTRACE_KILL               8      /* ??? */
#define __PTRACE_SINGLESTEP         9      /* ??? */
#define __PTRACE_GETREGS            12     /* ??? */
#define __PTRACE_SETREGS            13     /* ??? */
#define __PTRACE_GETFPREGS          14     /* ??? */
#define __PTRACE_SETFPREGS          15     /* ??? */
#define __PTRACE_ATTACH             16     /* ??? */
#define __PTRACE_DETACH             17     /* ??? */
#define __PTRACE_GETFPXREGS         18     /* ??? */
#define __PTRACE_SETFPXREGS         19     /* ??? */
#define __PTRACE_SYSCALL            24     /* ??? */
#define __PTRACE_SETOPTIONS         0x4200 /* ??? */
#define __PTRACE_GETEVENTMSG        0x4201 /* ??? */
#define __PTRACE_GETSIGINFO         0x4202 /* ??? */
#define __PTRACE_SETSIGINFO         0x4203 /* ??? */
#define __PTRACE_GETREGSET          0x4204 /* ??? */
#define __PTRACE_SETREGSET          0x4205 /* ??? */
#define __PTRACE_SEIZE              0x4206 /* ??? */
#define __PTRACE_INTERRUPT          0x4207 /* ??? */
#define __PTRACE_LISTEN             0x4208 /* ??? */
#define __PTRACE_PEEKSIGINFO        0x4209 /* ??? */
#define __PTRACE_GETSIGMASK         0x420a /* ??? */
#define __PTRACE_SETSIGMASK         0x420b /* ??? */
#define __PTRACE_SECCOMP_GET_FILTER 0x420c /* ??? */

/* Flag accepted by `__PTRACE_LISTEN' */
#define __PTRACE_SEIZE_DEVEL 0x80000000 /* ??? */

/* Flag accepted by `__PTRACE_SETOPTIONS'. */
#define __PTRACE_O_TRACESYSGOOD    0x00000001 /* ??? */
#define __PTRACE_O_TRACEFORK       0x00000002 /* ??? */
#define __PTRACE_O_TRACEVFORK      0x00000004 /* ??? */
#define __PTRACE_O_TRACECLONE      0x00000008 /* ??? */
#define __PTRACE_O_TRACEEXEC       0x00000010 /* ??? */
#define __PTRACE_O_TRACEVFORKDONE  0x00000020 /* ??? */
#define __PTRACE_O_TRACEEXIT       0x00000040 /* ??? */
#define __PTRACE_O_TRACESECCOMP    0x00000080 /* ??? */
#define __PTRACE_O_EXITKILL        0x00100000 /* ??? */
#define __PTRACE_O_SUSPEND_SECCOMP 0x00200000 /* ??? */
#define __PTRACE_O_MASK            0x003000ff /* ??? */

/* Extended wait-result-codes for trace options. */
#define __PTRACE_EVENT_FORK       1 /* ??? */
#define __PTRACE_EVENT_VFORK      2 /* ??? */
#define __PTRACE_EVENT_CLONE      3 /* ??? */
#define __PTRACE_EVENT_EXEC       4 /* ??? */
#define __PTRACE_EVENT_VFORK_DONE 5 /* ??? */
#define __PTRACE_EVENT_EXIT       6 /* ??? */
#define __PTRACE_EVENT_SECCOMP    7 /* ??? */

#define __PTRACE_PEEKSIGINFO_SHARED 0x0001 /* ??? */

#endif /* !_ASM_OS_KOS_PTRACE_H */
