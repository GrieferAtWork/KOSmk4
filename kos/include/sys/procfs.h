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
/* (#) Portability: Cygwin        (/winsup/cygwin/include/sys/procfs.h) */
/* (#) Portability: DragonFly BSD (/sys/sys/procfs.h) */
/* (#) Portability: FreeBSD       (/sys/sys/procfs.h) */
/* (#) Portability: GNU C Library (/sysdeps/unix/sysv/linux/sys/procfs.h) */
/* (#) Portability: OpenSolaris   (/usr/src/uts/common/sys/procfs.h) */
/* (#) Portability: musl libc     (/include/sys/procfs.h) */
#ifndef _SYS_PROCFS_H
#define _SYS_PROCFS_H 1

#include <__stdinc.h>
#include <features.h>

#include <bits/os/timeval.h>
#include <sys/types.h>
#include <sys/user.h>


/* This file is derived from Glibc /usr/include/i386-linux-gnu/sys/procfs.h */
/* Copyright (C) 2001-2016 Free Software Foundation, Inc.
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
   <http://www.gnu.org/licenses/>. */

#ifdef __CC__
__SYSDECL_BEGIN

/* Type for a general-purpose register. */
typedef __ULONGPTR_TYPE__ elf_greg_t;

/* And   the  whole  bunch  of  them.  We  could  have  used  `struct
 * user_regs_struct' directly in the typedef, but tradition says that
 * the  register  set  is an  array,  which does  have  some peculiar
 * semantics, so leave it that way. */
#define ELF_NGREG (sizeof(struct user_regs_struct) / sizeof(elf_greg_t))
typedef elf_greg_t elf_gregset_t[ELF_NGREG];

#ifndef __x86_64__
/* Register set for the floating-point registers. */
typedef struct user_fpregs_struct elf_fpregset_t;

/* Register set for the extended floating-point registers. Includes
   the Pentium III SSE registers in addition to the classic
   floating-point stuff. */
typedef struct user_fpxregs_struct elf_fpxregset_t;
#else /* __x86_64__ */
/* Register set for the extended floating-point registers. Includes
   the Pentium III SSE registers in addition to the classic
   floating-point stuff. */
typedef struct user_fpregs_struct elf_fpregset_t;
#endif /* !__x86_64__ */

/* Signal info. */
struct elf_siginfo {
	int si_signo; /* Signal number. */
	int si_code;  /* Extra code. */
	int si_errno; /* Errno. */
};


/* Definitions to generate Intel  SVR4-like core files. These  mostly
 * have the same names  as the SVR4 types  with "elf_" tacked on  the
 * front to prevent clashes with  Linux definitions, and the  typedef
 * forms have been avoided. This  is mostly like the SVR4  structure,
 * but more Linuxy, with things that Linux does not support and which
 * GDB doesn't really use excluded. */

struct elf_prstatus {
	struct elf_siginfo pr_info;    /* Info associated with signal. */
	__UINT16_TYPE__    pr_cursig;  /* Current signal. */
	__ULONGPTR_TYPE__  pr_sigpend; /* Set of pending signals. */
	__ULONGPTR_TYPE__  pr_sighold; /* Set of held signals. */
	__pid_t            pr_pid;     /* ... */
	__pid_t            pr_ppid;    /* ... */
	__pid_t            pr_pgrp;    /* ... */
	__pid_t            pr_sid;     /* ... */
	struct timeval     pr_utime;   /* User time. */
	struct timeval     pr_stime;   /* System time. */
	struct timeval     pr_cutime;  /* Cumulative user time. */
	struct timeval     pr_cstime;  /* Cumulative system time. */
	elf_gregset_t      pr_reg;     /* GP registers. */
	__INT32_TYPE__     pr_fpvalid; /* True if math coprocessor is being used. */
};


#define ELF_PRARGSZ 80 /* Number of chars for args. */

struct elf_prpsinfo {
	char                  pr_state; /* Numeric process state. */
	char                  pr_sname; /* Char for pr_state. */
	char                  pr_zomb;  /* Zombie. */
	char                  pr_nice;  /* Nice val. */
	__ULONGPTR_TYPE__     pr_flag;  /* Flags. */
	__UINTPTR_HALF_TYPE__ pr_uid;
	__UINTPTR_HALF_TYPE__ pr_gid;
	__INT32_TYPE__        pr_pid;
	__INT32_TYPE__        pr_ppid;
	__INT32_TYPE__        pr_pgrp;
	__INT32_TYPE__        pr_sid;
	/* Lots missing */
	char                  pr_fname[16];           /* Filename of executable. */
	char                  pr_psargs[ELF_PRARGSZ]; /* Initial part of arg list. */
};


/* The  rest of  this file provides  the types for  emulation of the
 * Solaris <proc_service.h> interfaces that should be implemented by
 * users of libthread_db. */

/* Addresses. */
typedef void *psaddr_t;

/* Register sets. Linux has different names. */
typedef elf_gregset_t prgregset_t;
typedef elf_fpregset_t prfpregset_t;

/* We don't have any differences between processes and threads,
 * therefore have only one PID type. */
typedef __pid_t lwpid_t;

/* Process status and info. In the end we do provide typedefs for them. */
typedef struct elf_prstatus prstatus_t;
typedef struct elf_prpsinfo prpsinfo_t;


__SYSDECL_END
#endif /* __CC__ */

#endif /* !_SYS_PROCFS_H */
