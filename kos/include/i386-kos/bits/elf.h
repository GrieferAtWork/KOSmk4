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
#ifndef _I386_KOS_BITS_ELF_H
#define _I386_KOS_BITS_ELF_H 1

#include <__stdinc.h>
#include <features.h>
#include <bits/elf-types.h>
#include <hybrid/host.h>
#include <hybrid/typecore.h>

/* NOTE: Data structures in this header follow ELF naming and syntax contentions,
 *       but their names are non-standardized and should not be expected to be
 *       available on platforms other than KOS. */

__SYSDECL_BEGIN

/* Data structures for core file note segments. */
#define NT_PRSTATUS     1               /* Contains copy of prstatus struct */
#define NT_FPREGSET     2               /* Contains copy of fpregset struct */
#define NT_PRPSINFO     3               /* Contains copy of prpsinfo struct */
#define NT_PRXREG       4               /* Contains copy of prxregset struct */
#define NT_TASKSTRUCT   4               /* Contains copy of task structure */
#define NT_PLATFORM     5               /* String from sysinfo(SI_PLATFORM) */
#define NT_AUXV         6               /* Contains copy of auxv array */
#define NT_GWINDOWS     7               /* Contains copy of gwindows struct */
#define NT_ASRS         8               /* Contains copy of asrset struct */
#define NT_PSTATUS      10              /* Contains copy of pstatus struct */
#define NT_PSINFO       13              /* Contains copy of psinfo struct */
#define NT_PRCRED       14              /* Contains copy of prcred struct */
#define NT_UTSNAME      15              /* Contains copy of utsname struct */
#define NT_LWPSTATUS    16              /* Contains copy of lwpstatus struct */
#define NT_LWPSINFO     17              /* Contains copy of lwpinfo struct */
#define NT_PRFPXREG     20              /* Contains copy of fprxregset struct*/


#ifdef __CC__
typedef Elf32_Sword Elf32_pid_t;
typedef Elf64_Sword Elf64_pid_t;
typedef Elf32_Word  Elf32_greg_t;
typedef Elf64_Xword Elf64_greg_t;

typedef struct {
	Elf32_Sword si_signo; /* signal number. */
	Elf32_Sword si_code;  /* extra code. */
	Elf32_Sword si_errno; /* errno. */
} Elf32_Siginfo;

typedef struct {
	Elf64_Sword si_signo; /* signal number. */
	Elf64_Sword si_code;  /* extra code. */
	Elf64_Sword si_errno; /* errno. */
} Elf64_Siginfo;

typedef struct {
	Elf32_greg_t ebx;
	Elf32_greg_t ecx;
	Elf32_greg_t edx;
	Elf32_greg_t esi;
	Elf32_greg_t edi;
	Elf32_greg_t ebp;
	Elf32_greg_t eax;
	Elf32_greg_t ds;
	Elf32_greg_t es;
	Elf32_greg_t fs;
	Elf32_greg_t gs;
	Elf32_greg_t orig_eax;
	Elf32_greg_t eip;
	Elf32_greg_t cs;
	Elf32_greg_t eflags;
	Elf32_greg_t esp;
	Elf32_greg_t ss;
} Elf32_Userregs;

typedef struct {
	Elf64_greg_t r15;
	Elf64_greg_t r14;
	Elf64_greg_t r13;
	Elf64_greg_t r12;
	Elf64_greg_t rbp;
	Elf64_greg_t rbx;
	Elf64_greg_t r11;
	Elf64_greg_t r10;
	Elf64_greg_t r9;
	Elf64_greg_t r8;
	Elf64_greg_t rax;
	Elf64_greg_t rcx;
	Elf64_greg_t rdx;
	Elf64_greg_t rsi;
	Elf64_greg_t rdi;
	Elf64_greg_t orig_rax;
	Elf64_greg_t rip;
	Elf64_greg_t cs;
	Elf64_greg_t eflags;
	Elf64_greg_t rsp;
	Elf64_greg_t ss;
	Elf64_greg_t fs_base;
	Elf64_greg_t gs_base;
	Elf64_greg_t ds;
	Elf64_greg_t es;
	Elf64_greg_t fs;
	Elf64_greg_t gs;
} Elf64_Userregs;


typedef struct {
	Elf32_Sword  tv_sec;
	Elf32_Sword  tv_usec;
} Elf32_Prtimeval;

typedef struct {
	Elf64_Sxword tv_sec;
	Elf64_Sxword tv_usec;
} Elf64_Prtimeval;


typedef struct {
	Elf32_Siginfo          pr_info;    /* Info associated with signal. */
	Elf32_Half             pr_cursig;  /* Current signal. */
	Elf32_Word             pr_sigpend; /* Set of pending signals. */
	Elf32_Word             pr_sighold; /* Set of held signals. */
	Elf32_pid_t            pr_pid;
	Elf32_pid_t            pr_ppid;
	Elf32_pid_t            pr_pgrp;
	Elf32_pid_t            pr_sid;
	Elf32_Prtimeval        pr_utime;   /* User time. */
	Elf32_Prtimeval        pr_stime;   /* System time. */
	Elf32_Prtimeval        pr_cutime;  /* Total user time. */
	Elf32_Prtimeval        pr_cstime;  /* Total system time. */
	Elf32_Userregs         pr_reg;     /* General purpose registers. */
	Elf32_Word             pr_fpvalid; /* True if a math coprocessor being used. */
} Elf32_Prstatus;

typedef struct {
	Elf64_Siginfo          pr_info;    /* Info associated with signal. */
	Elf64_Half             pr_cursig;  /* Current signal. */
	Elf64_Word             pr_sigpend; /* Set of pending signals. */
	Elf64_Word             pr_sighold; /* Set of held signals. */
	Elf64_pid_t            pr_pid;
	Elf64_pid_t            pr_ppid;
	Elf64_pid_t            pr_pgrp;
	Elf64_pid_t            pr_sid;
	Elf64_Prtimeval        pr_utime;   /* User time. */
	Elf64_Prtimeval        pr_stime;   /* System time. */
	Elf64_Prtimeval        pr_cutime;  /* Total user time. */
	Elf64_Prtimeval        pr_cstime;  /* Total system time. */
	Elf64_Userregs         pr_reg;     /* General purpose registers. */
	Elf64_Word             pr_fpvalid; /* True if a math coprocessor being used. */
} Elf64_Prstatus;

typedef struct {
	Elf32_Siginfo          pr_info;    /* Info associated with signal. */
	Elf32_Half             pr_cursig;  /* Current signal. */
	Elf32_Word             pr_sigpend; /* Set of pending signals. */
	Elf32_Word             pr_sighold; /* Set of held signals. */
	Elf32_pid_t            pr_pid;
	Elf32_pid_t            pr_ppid;
	Elf32_pid_t            pr_pgrp;
	Elf32_pid_t            pr_sid;
	Elf32_Prtimeval        pr_utime;   /* User time. */
	Elf32_Prtimeval        pr_stime;   /* System time. */
	Elf32_Prtimeval        pr_cutime;  /* Total user time. */
	Elf32_Prtimeval        pr_cstime;  /* Total system time. */
	Elf64_Userregs         pr_reg;     /* General purpose registers. */
	Elf32_Word             pr_fpvalid; /* True if a math coprocessor being used. */
} Elfx32_Prstatus; /* 32-bit running on 64-bit host. */

#define ELF_PRARGSZ 80 /* Number of chars for args */
typedef struct {
	char        pr_state;        /* Numeric process state. */
	char        pr_sname;        /* Char for pr_state. */
	char        pr_zomb;         /* Zombie. */
	char        pr_nice;         /* Nice val. */
	Elf32_Word  pr_flag;         /* Flags. */
	Elf32_Half  pr_uid;
	Elf32_Half  pr_gid;
	Elf32_pid_t pr_pid;
	Elf32_pid_t pr_ppid;
	Elf32_pid_t pr_pgrp;
	Elf32_pid_t pr_sid;
	/* <stuff missing in linux> */
	char pr_fname[16];           /* Filename of executable. */
	char pr_psargs[ELF_PRARGSZ]; /* Initial part of arg list. */
} Elf32_Prpsinfo;

typedef struct {
	char        pr_state;        /* Numeric process state. */
	char        pr_sname;        /* Char for pr_state. */
	char        pr_zomb;         /* Zombie. */
	char        pr_nice;         /* Nice val. */
	Elf64_Xword pr_flag;         /* Flags. */
	Elf64_Half  pr_uid;
	Elf64_Half  pr_gid;
	Elf64_pid_t pr_pid;
	Elf64_pid_t pr_ppid;
	Elf64_pid_t pr_pgrp;
	Elf64_pid_t pr_sid;
	/* <stuff missing in linux> */
	char pr_fname[16];           /* Filename of executable. */
	char pr_psargs[ELF_PRARGSZ]; /* Initial part of arg list. */
} Elf64_Prpsinfo;


typedef struct {
	Elf32_Addr  fe_begin; /* File mapping start address. */
	Elf32_Addr  fe_end;   /* File mapping end address. */
	Elf32_Off   fe_off;   /* File mapping offset (in pages). */
} Elf32_Ntfileent;

typedef struct {
	Elf64_Addr  fe_begin; /* File mapping start address. */
	Elf64_Addr  fe_end;   /* File mapping end address. */
	Elf64_Off   fe_off;   /* File mapping offset (in pages). */
} Elf64_Ntfileent;

typedef struct {
	Elf32_Word      nf_count;  /* Amount of stored file mappings. */
	Elf32_Word      nf_pagesz; /* == getpagesize(). */
/*	Elf32_Ntfileent nf_files[nf_count]; */    /* Vector of file entires. */
/*	char            nf_names[nf_count][?]; */ /* Inline vector of ZERO-terminated strings, matching 'nf_files' (Iterate with: `iter = strend(iter)+1') */
} Elf32_Ntfile; /* Note section header content for `NT_FILE'. */

typedef struct {
	Elf64_Xword     nf_count;  /* Amount of stored file mappings. */
	Elf64_Xword     nf_pagesz; /* == getpagesize(). */
/*	Elf64_Ntfileent nf_files[nf_count]; */    /* Vector of file entires. */
/*	char            nf_names[nf_count][?]; */ /* Inline vector of ZERO-terminated strings, matching 'nf_files' (Iterate with: `iter = strend(iter)+1') */
} Elf64_Ntfile; /* Note section header content for `NT_FILE'. */


typedef struct {
	Elf32_Sword cwd;
	Elf32_Sword swd;
	Elf32_Sword twd;
	Elf32_Sword fip;
	Elf32_Sword fcs;
	Elf32_Sword foo;
	Elf32_Sword fos;
	Elf32_Sword st_space[20]; /* 80 bytes */
} Elf32_Fpregset;

typedef struct {
	Elf64_Half  cwd;
	Elf64_Half  swd;
	Elf64_Half  twd; /* Not the same as the 32bit/x87/FSAVE twd */
	Elf64_Half  fop;
	Elf64_Xword rip;
	Elf64_Xword rdp;
	Elf64_Word  mxcsr;
	Elf64_Word  mxcsr_mask;
	Elf64_Word  st_space[32];  /* 128 bytes */
	Elf64_Word  xmm_space[64]; /* 256 bytes */
	Elf64_Word  padding[24];
} Elf64_Fpregset;

typedef struct {
	/* NOTE: Linux calls this one 'user32_fxsr_struct' */
	Elf32_Half  cwd;
	Elf32_Half  swd;
	Elf32_Half  twd;
	Elf32_Half  fop;
	Elf32_Sword fip;
	Elf32_Sword fcs;
	Elf32_Sword foo;
	Elf32_Sword fos;
	Elf32_Sword mxcsr;
	Elf32_Sword reserved;
	Elf32_Sword st_space[32];  /* 128 bytes */
	Elf32_Sword xmm_space[32]; /* 128 bytes */
	Elf32_Sword padding[56];
} Elf32_Prxfpreg;
/* XXX: There doesn't seem to be the equivalent of 'Elf64_Prxfpreg'... */
#endif /* __CC__ */


__SYSDECL_END

#endif /* !_I386_KOS_BITS_ELF_H */
