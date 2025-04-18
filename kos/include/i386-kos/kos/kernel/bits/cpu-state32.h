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
/*!replace_with_include <kos/kernel/cpu-state.h>*/
#ifndef _I386_KOS_KOS_KERNEL_BITS_CPU_STATE32_H
#define _I386_KOS_KOS_KERNEL_BITS_CPU_STATE32_H 1

#include <__crt.h>
#include <__stdinc.h>

#include <bits/types.h>
#include <hybrid/host.h>
#include <hybrid/__pointer.h>

#include "../x86/gdt.h"

__SYSDECL_BEGIN

#ifndef __x86_64__

#define gpregs32                    gpregs
#define OFFSET_GPREGS_EDI           OFFSET_GPREGS32_EDI
#define OFFSET_GPREGS_ESI           OFFSET_GPREGS32_ESI
#define OFFSET_GPREGS_EBP           OFFSET_GPREGS32_EBP
#define OFFSET_GPREGS_ESP           OFFSET_GPREGS32_ESP
#define OFFSET_GPREGS_EBX           OFFSET_GPREGS32_EBX
#define OFFSET_GPREGS_EDX           OFFSET_GPREGS32_EDX
#define OFFSET_GPREGS_ECX           OFFSET_GPREGS32_ECX
#define OFFSET_GPREGS_EAX           OFFSET_GPREGS32_EAX
#define SIZEOF_GPREGS               SIZEOF_GPREGS32

#define sgregs32                    sgregs
#define OFFSET_SGREGS_GS            OFFSET_SGREGS32_GS
#define OFFSET_SGREGS_FS            OFFSET_SGREGS32_FS
#define OFFSET_SGREGS_ES            OFFSET_SGREGS32_ES
#define OFFSET_SGREGS_DS            OFFSET_SGREGS32_DS
#define SIZEOF_SGREGS               SIZEOF_SGREGS32

#define coregs32                    coregs
#define OFFSET_COREGS_CR0           OFFSET_COREGS32_CR0
#define OFFSET_COREGS_CR2           OFFSET_COREGS32_CR2
#define OFFSET_COREGS_CR3           OFFSET_COREGS32_CR3
#define OFFSET_COREGS_CR4           OFFSET_COREGS32_CR4
#define SIZEOF_COREGS               SIZEOF_COREGS32

#define drregs32                    drregs
#define OFFSET_DRREGS_DR0           OFFSET_DRREGS32_DR0
#define OFFSET_DRREGS_DR1           OFFSET_DRREGS32_DR1
#define OFFSET_DRREGS_DR2           OFFSET_DRREGS32_DR2
#define OFFSET_DRREGS_DR3           OFFSET_DRREGS32_DR3
#define OFFSET_DRREGS_DR6           OFFSET_DRREGS32_DR6
#define OFFSET_DRREGS_DR7           OFFSET_DRREGS32_DR7
#define SIZEOF_DRREGS               SIZEOF_DRREGS32

#define irregs32_kernel             irregs_kernel
#define irregs32_user               irregs_user
#define irregs32_vm86               irregs_vm86
#define OFFSET_IRREGS_EIP           OFFSET_IRREGS32_EIP
#define OFFSET_IRREGS_CS            OFFSET_IRREGS32_CS
#define OFFSET_IRREGS_EFLAGS        OFFSET_IRREGS32_EFLAGS
#define SIZEOF_IRREGS_KERNEL        SIZEOF_IRREGS32_KERNEL
#define OFFSET_IRREGS_ESP           OFFSET_IRREGS32_ESP
#define OFFSET_IRREGS_SS            OFFSET_IRREGS32_SS
#define SIZEOF_IRREGS_USER          SIZEOF_IRREGS32_USER
#define OFFSET_IRREGS_ES            OFFSET_IRREGS32_ES
#define OFFSET_IRREGS_DS            OFFSET_IRREGS32_DS
#define OFFSET_IRREGS_FS            OFFSET_IRREGS32_FS
#define OFFSET_IRREGS_GS            OFFSET_IRREGS32_GS
#define SIZEOF_IRREGS_VM86          SIZEOF_IRREGS32_VM86
#define OFFSET_IRREGS_KERNEL_EIP    OFFSET_IRREGS32_KERNEL_EIP
#define OFFSET_IRREGS_KERNEL_CS     OFFSET_IRREGS32_KERNEL_CS
#define OFFSET_IRREGS_KERNEL_EFLAGS OFFSET_IRREGS32_KERNEL_EFLAGS
#define OFFSET_IRREGS_USER_EIP      OFFSET_IRREGS32_USER_EIP
#define OFFSET_IRREGS_USER_CS       OFFSET_IRREGS32_USER_CS
#define OFFSET_IRREGS_USER_EFLAGS   OFFSET_IRREGS32_USER_EFLAGS
#define OFFSET_IRREGS_USER_ESP      OFFSET_IRREGS32_USER_ESP
#define OFFSET_IRREGS_USER_SS       OFFSET_IRREGS32_USER_SS
#define OFFSET_IRREGS_VM86_EIP      OFFSET_IRREGS32_VM86_EIP
#define OFFSET_IRREGS_VM86_CS       OFFSET_IRREGS32_VM86_CS
#define OFFSET_IRREGS_VM86_EFLAGS   OFFSET_IRREGS32_VM86_EFLAGS
#define OFFSET_IRREGS_VM86_ESP      OFFSET_IRREGS32_VM86_ESP
#define OFFSET_IRREGS_VM86_SS       OFFSET_IRREGS32_VM86_SS
#define OFFSET_IRREGS_VM86_ES       OFFSET_IRREGS32_VM86_ES
#define OFFSET_IRREGS_VM86_DS       OFFSET_IRREGS32_VM86_DS
#define OFFSET_IRREGS_VM86_FS       OFFSET_IRREGS32_VM86_FS
#define OFFSET_IRREGS_VM86_GS       OFFSET_IRREGS32_VM86_GS

#define ucpustate32                 ucpustate
#define OFFSET_UCPUSTATE_GPREGS     OFFSET_UCPUSTATE32_GPREGS
#define OFFSET_UCPUSTATE_SGREGS     OFFSET_UCPUSTATE32_SGREGS
#define OFFSET_UCPUSTATE_CS         OFFSET_UCPUSTATE32_CS
#define OFFSET_UCPUSTATE_SS         OFFSET_UCPUSTATE32_SS
#define OFFSET_UCPUSTATE_EFLAGS     OFFSET_UCPUSTATE32_EFLAGS
#define OFFSET_UCPUSTATE_EIP        OFFSET_UCPUSTATE32_EIP
#define SIZEOF_UCPUSTATE            SIZEOF_UCPUSTATE32

#define lcpustate32                 lcpustate
#define OFFSET_LCPUSTATE_EDI        OFFSET_LCPUSTATE32_EDI
#define OFFSET_LCPUSTATE_ESI        OFFSET_LCPUSTATE32_ESI
#define OFFSET_LCPUSTATE_EBP        OFFSET_LCPUSTATE32_EBP
#define OFFSET_LCPUSTATE_ESP        OFFSET_LCPUSTATE32_ESP
#define OFFSET_LCPUSTATE_EBX        OFFSET_LCPUSTATE32_EBX
#define OFFSET_LCPUSTATE_EIP        OFFSET_LCPUSTATE32_EIP
#define SIZEOF_LCPUSTATE            SIZEOF_LCPUSTATE32

#define kcpustate32                 kcpustate
#define OFFSET_KCPUSTATE_GPREGS     OFFSET_KCPUSTATE32_GPREGS
#define OFFSET_KCPUSTATE_EFLAGS     OFFSET_KCPUSTATE32_EFLAGS
#define OFFSET_KCPUSTATE_EIP        OFFSET_KCPUSTATE32_EIP
#define SIZEOF_KCPUSTATE            SIZEOF_KCPUSTATE32

#define icpustate32                 icpustate
#define OFFSET_ICPUSTATE_GPREGS     OFFSET_ICPUSTATE32_GPREGS
#define OFFSET_ICPUSTATE_FS         OFFSET_ICPUSTATE32_FS
#define OFFSET_ICPUSTATE_ES         OFFSET_ICPUSTATE32_ES
#define OFFSET_ICPUSTATE_DS         OFFSET_ICPUSTATE32_DS
#define OFFSET_ICPUSTATE_IRREGS     OFFSET_ICPUSTATE32_IRREGS

#define scpustate32                 scpustate
#define OFFSET_SCPUSTATE_GPREGS     OFFSET_SCPUSTATE32_GPREGS
#define OFFSET_SCPUSTATE_SGREGS     OFFSET_SCPUSTATE32_SGREGS
#define OFFSET_SCPUSTATE_IRREGS     OFFSET_SCPUSTATE32_IRREGS

#define desctab32                   desctab
#define OFFSET_DESCTAB_LIMIT        OFFSET_DESCTAB32_LIMIT
#define OFFSET_DESCTAB_BASE         OFFSET_DESCTAB32_BASE
#define SIZEOF_DESCTAB              SIZEOF_DESCTAB32

#define fcpustate32                 fcpustate
#define OFFSET_FCPUSTATE_GPREGS     OFFSET_FCPUSTATE32_GPREGS
#define OFFSET_FCPUSTATE_EFLAGS     OFFSET_FCPUSTATE32_EFLAGS
#define OFFSET_FCPUSTATE_EIP        OFFSET_FCPUSTATE32_EIP
#define OFFSET_FCPUSTATE_ES         OFFSET_FCPUSTATE32_ES
#define OFFSET_FCPUSTATE_CS         OFFSET_FCPUSTATE32_CS
#define OFFSET_FCPUSTATE_SS         OFFSET_FCPUSTATE32_SS
#define OFFSET_FCPUSTATE_DS         OFFSET_FCPUSTATE32_DS
#define OFFSET_FCPUSTATE_FS         OFFSET_FCPUSTATE32_FS
#define OFFSET_FCPUSTATE_GS         OFFSET_FCPUSTATE32_GS
#define OFFSET_FCPUSTATE_TR         OFFSET_FCPUSTATE32_TR
#define OFFSET_FCPUSTATE_LDT        OFFSET_FCPUSTATE32_LDT
#define OFFSET_FCPUSTATE_COREGS     OFFSET_FCPUSTATE32_COREGS
#define OFFSET_FCPUSTATE_DRREGS     OFFSET_FCPUSTATE32_DRREGS
#define OFFSET_FCPUSTATE_GDT        OFFSET_FCPUSTATE32_GDT
#define OFFSET_FCPUSTATE_IDT        OFFSET_FCPUSTATE32_IDT
#define SIZEOF_FCPUSTATE            SIZEOF_FCPUSTATE32

#endif /* !__x86_64__ */



#define OFFSET_GPREGS32_EDI 0
#define OFFSET_GPREGS32_ESI 4
#define OFFSET_GPREGS32_EBP 8
#define OFFSET_GPREGS32_ESP 12
#define OFFSET_GPREGS32_EBX 16
#define OFFSET_GPREGS32_EDX 20
#define OFFSET_GPREGS32_ECX 24
#define OFFSET_GPREGS32_EAX 28
#define SIZEOF_GPREGS32     32
#ifdef __CC__
struct gpregs32 {
	__u32   gp_edi;    /* [P] Destination pointer */
	__u32   gp_esi;    /* [P] Source pointer */
	__u32   gp_ebp;    /* [P] Frame base pointer */
	__u32   gp_esp;    /* [P] Stack pointer */
	__u32   gp_ebx;    /* [P] Base register */
	__u32   gp_edx;    /* [C] Data register */
	__u32   gp_ecx;    /* [C] Count register */
	__u32   gp_eax;    /* [C] Accumulator register */
};
#endif /* __CC__ */



#define OFFSET_SGREGS32_GS  0
#define OFFSET_SGREGS32_FS  4
#define OFFSET_SGREGS32_ES  8
#define OFFSET_SGREGS32_DS  12
#define SIZEOF_SGREGS32     16
#ifdef __CC__
struct sgregs32 {
	union {
		__u32 sg_gs;     /* G  segment   register   (Usually   `SEGMENT_USER_GSBASE_RPL')
		                  * (upper 16 bits are undefined, but should be written as zeros) */
		__u16 sg_gs16;   /* G segment register (Usually `SEGMENT_USER_GSBASE_RPL') */
	};
	union {
		__u32 sg_fs;     /* F segment register (Usually `SEGMENT_USER_FSBASE_RPL' / `SEGMENT_KERNEL_FSBASE')
		                  * (upper   16   bits   are   undefined,   but   should   be   written   as  zeros) */
		__u16 sg_fs16;   /* F segment register (Usually `SEGMENT_USER_FSBASE_RPL' / `SEGMENT_KERNEL_FSBASE') */
	};
	union {
		__u32 sg_es;     /* E (source) segment register (Usually `SEGMENT_USER_DATA_RPL')
		                  * (upper 16 bits are undefined, but should be written as zeros) */
		__u16 sg_es16;   /* E (source) segment register (Usually `SEGMENT_USER_DATA_RPL') */
	};
	union {
		__u32 sg_ds;     /* D (destination) segment register (Usually `SEGMENT_USER_DATA_RPL')
		                  * (upper 16  bits are  undefined, but  should be  written as  zeros) */
		__u16 sg_ds16;   /* D (destination) segment register (Usually `SEGMENT_USER_DATA_RPL') */
	};
};
#endif /* __CC__ */



#define OFFSET_COREGS32_CR0 0
#define OFFSET_COREGS32_CR2 4
#define OFFSET_COREGS32_CR3 8
#define OFFSET_COREGS32_CR4 12
#define SIZEOF_COREGS32     16
#ifdef __CC__
struct coregs32 {
	__u32                co_cr0; /* %cr0 (Set of `CR0_*' from `/include/i386-kos/asm/cpu-flags.h') */
	__HYBRID_PTR32(void) co_cr2; /* %cr2 (Page Fault Linear Address (PFLA) (when a #PF occurs, contains that fault's address)) */
	__u32                co_cr3; /* %cr3 (Page Directory Linear Address) */
	__u32                co_cr4; /* %cr4 (Set of `CR4_*' from `/include/i386-kos/asm/cpu-flags.h') */
};
#endif /* __CC__ */



#define OFFSET_DRREGS32_DR0  0
#define OFFSET_DRREGS32_DR1  4
#define OFFSET_DRREGS32_DR2  8
#define OFFSET_DRREGS32_DR3  12
#define OFFSET_DRREGS32_DR6  16
#define OFFSET_DRREGS32_DR7  20
#define SIZEOF_DRREGS32      24
#ifdef __CC__
struct drregs32 {
	__HYBRID_PTR32(void) dr_dr0; /* %dr0 (Linear address of first breakpoint) */
	__HYBRID_PTR32(void) dr_dr1; /* %dr1 (Linear address of second breakpoint) */
	__HYBRID_PTR32(void) dr_dr2; /* %dr2 (Linear address of third breakpoint) */
	__HYBRID_PTR32(void) dr_dr3; /* %dr3 (Linear address of fourth breakpoint) */
	__u32                dr_dr6; /* %dr6 (Debug status) */
	__u32                dr_dr7; /* %dr7 (Debug control (set of `DR7_*' from `/include/i386-kos/asm/cpu-flags.h')) */
};
#endif /* __CC__ */



#define OFFSET_IRREGS32_EIP           0
#define OFFSET_IRREGS32_CS            4
#define OFFSET_IRREGS32_EFLAGS        8
#define SIZEOF_IRREGS32_KERNEL        12
#define OFFSET_IRREGS32_ESP           12
#define OFFSET_IRREGS32_SS            16
#define SIZEOF_IRREGS32_USER          20
#define OFFSET_IRREGS32_ES            20
#define OFFSET_IRREGS32_DS            24
#define OFFSET_IRREGS32_FS            28
#define OFFSET_IRREGS32_GS            32
#define SIZEOF_IRREGS32_VM86          36
#define OFFSET_IRREGS32_KERNEL_EIP    OFFSET_IRREGS32_EIP
#define OFFSET_IRREGS32_KERNEL_CS     OFFSET_IRREGS32_CS
#define OFFSET_IRREGS32_KERNEL_EFLAGS OFFSET_IRREGS32_EFLAGS
#define OFFSET_IRREGS32_USER_EIP      OFFSET_IRREGS32_EIP
#define OFFSET_IRREGS32_USER_CS       OFFSET_IRREGS32_CS
#define OFFSET_IRREGS32_USER_EFLAGS   OFFSET_IRREGS32_EFLAGS
#define OFFSET_IRREGS32_USER_ESP      OFFSET_IRREGS32_ESP
#define OFFSET_IRREGS32_USER_SS       OFFSET_IRREGS32_SS
#define OFFSET_IRREGS32_VM86_EIP      OFFSET_IRREGS32_EIP
#define OFFSET_IRREGS32_VM86_CS       OFFSET_IRREGS32_CS
#define OFFSET_IRREGS32_VM86_EFLAGS   OFFSET_IRREGS32_EFLAGS
#define OFFSET_IRREGS32_VM86_ESP      OFFSET_IRREGS32_ESP
#define OFFSET_IRREGS32_VM86_SS       OFFSET_IRREGS32_SS
#define OFFSET_IRREGS32_VM86_ES       OFFSET_IRREGS32_ES
#define OFFSET_IRREGS32_VM86_DS       OFFSET_IRREGS32_DS
#define OFFSET_IRREGS32_VM86_FS       OFFSET_IRREGS32_FS
#define OFFSET_IRREGS32_VM86_GS       OFFSET_IRREGS32_GS
#ifdef __CC__
struct irregs32_kernel {
	__u32     ir_eip;    /* Instruction pointer */
	union {
		__u32 ir_cs;     /* Code   segment   (Ring  #0,   usually  `SEGMENT_KERNEL_CODE')
		                  * (upper 16 bits are undefined, but should be written as zeros) */
		__u16 ir_cs16;   /* Code segment (Ring #0, usually `SEGMENT_KERNEL_CODE') */
	};
	__u32     ir_eflags; /* Flags register */
};
#if defined(__cplusplus) && 0 /* offsetof() in non-POD is undefined... */
struct irregs32_user: irregs_kernel {
	/* The following fields are popped when `(ir_cs & 3) != CURRENT_RING' */
	__u32     ir_esp;    /* Stack pointer */
	union {
		__u32 ir_ss;     /* Stack  segment  (Ring  #3,  usually  `SEGMENT_USER_DATA_RPL')
		                  * (upper 16 bits are undefined, but should be written as zeros) */
		__u16 ir_ss16;   /* Stack segment (Ring #3, usually `SEGMENT_USER_DATA_RPL') */
	};
};
struct irregs32_vm86: irregs_user {
	/* `ir_eflags' has the `EFLAGS_VM' flag set.
	 * NOTE: For each of these, the upper 16 bits are undefined, but should be written as zeros */
	union {
		__u32 ir_es;
		__u16 ir_es16;
	};
	union {
		__u32 ir_ds;
		__u16 ir_ds16;
	};
	union {
		__u32 ir_fs;
		__u16 ir_fs16;
	};
	union {
		__u32 ir_gs;
		__u16 ir_gs16;
	};
};
#else
struct irregs32_user {
	__u32     ir_eip;    /* Instruction pointer */
	union {
		__u32 ir_cs;     /* Code  segment  (Ring  #3,  usually   `SEGMENT_USER_CODE_RPL')
		                  * (upper 16 bits are undefined, but should be written as zeros) */
		__u16 ir_cs16;   /* Code segment (Ring #3, usually `SEGMENT_USER_CODE_RPL') */
	};
	__u32     ir_eflags; /* Flags register */
	/* The following fields are popped when `(ir_cs & 3) != CURRENT_RING' */
	__u32     ir_esp;    /* Stack pointer */
	union {
		__u32 ir_ss;     /* Stack  segment  (Ring  #3,  usually  `SEGMENT_USER_DATA_RPL')
		                  * (upper 16 bits are undefined, but should be written as zeros) */
		__u16 ir_ss16;   /* Stack segment (Ring #3, usually `SEGMENT_USER_DATA_RPL') */
	};
};
struct irregs32_vm86 {
	__u32     ir_eip;
	union {
		__u32 ir_cs;
		__u16 ir_cs16;
	};
	__u32     ir_eflags; /* Has the `EFLAGS_VM' flag set. */
	__u32     ir_esp;
	/* NOTE: For each of these, the upper 16 bits are undefined, but should be written as zeros */
	union {
		__u32 ir_ss;
		__u16 ir_ss16;
	};
	union {
		__u32 ir_es;
		__u16 ir_es16;
	};
	union {
		__u32 ir_ds;
		__u16 ir_ds16;
	};
	union {
		__u32 ir_fs;
		__u16 ir_fs16;
	};
	union {
		__u32 ir_gs;
		__u16 ir_gs16;
	};
};
#endif
#endif /* __CC__ */



#define OFFSET_UCPUSTATE32_GPREGS  0
#define OFFSET_UCPUSTATE32_SGREGS  32
#define OFFSET_UCPUSTATE32_CS      48
#define OFFSET_UCPUSTATE32_SS      52
#define OFFSET_UCPUSTATE32_EFLAGS  56
#define OFFSET_UCPUSTATE32_EIP     60
#define SIZEOF_UCPUSTATE32         64
#ifdef __CC__
struct ucpustate32 { /* u -- User */
	/* Full CPU state, as used by system calls.
	 * NOTE: Also represents the state saved when an exception occurs,
	 *       both   inside   kernel-,    as   well   as    user-space. */
	struct gpregs32 ucs_gpregs; /* General purpose registers. */
	struct sgregs32 ucs_sgregs; /* Segment registers. */
	union {
		__u32       ucs_cs;     /* Code  segment  (Ring  #3,  usually   `SEGMENT_USER_CODE_RPL')
		                         * (upper 16 bits are undefined, but should be written as zeros) */
		__u16       ucs_cs16;   /* Code segment (Ring #3, usually `SEGMENT_USER_CODE_RPL') */
	};
	union {
		__u32       ucs_ss;     /* Stack  segment  (Ring  #3,  usually  `SEGMENT_USER_DATA_RPL')
		                         * (upper 16 bits are undefined, but should be written as zeros) */
		__u16       ucs_ss16;   /* Stack segment (Ring #3, usually `SEGMENT_USER_DATA_RPL') */
	};
	__u32           ucs_eflags; /* Flags register */
	__u32           ucs_eip;    /* Instruction pointer */
};
#endif /* __CC__ */



#define OFFSET_LCPUSTATE32_EDI 0
#define OFFSET_LCPUSTATE32_ESI 4
#define OFFSET_LCPUSTATE32_EBP 8
#define OFFSET_LCPUSTATE32_ESP 12
#define OFFSET_LCPUSTATE32_EBX 16
#define OFFSET_LCPUSTATE32_EIP 20
#define SIZEOF_LCPUSTATE32     24
#ifdef __CC__
struct lcpustate32 { /* l -- Little */
	/* A minimal CPU state containing only registers that are callee-preserved.
	 * This kind  of  CPU  state  is most  useful  for  generating  tracebacks. */
	__u32         lcs_edi;    /* [P] Destination pointer */
	__u32         lcs_esi;    /* [P] Source pointer */
	__u32         lcs_ebp;    /* [P] Frame base pointer */
	__u32         lcs_esp;    /* [P] Stack pointer */
	__u32         lcs_ebx;    /* [P] Base register */
	__u32         lcs_eip;    /* Instruction pointer */
};
#endif /* __CC__ */



#define OFFSET_KCPUSTATE32_GPREGS 0
#define OFFSET_KCPUSTATE32_EFLAGS 32
#define OFFSET_KCPUSTATE32_EIP    36
#define SIZEOF_KCPUSTATE32        40
#ifdef __CC__
struct kcpustate32 {
	/* A CPU state used to describe a known, valid register state in kernel-space.
	 * This  kind of state is also used  by exception handling, and the associated
	 * stack unwinding. */
	struct gpregs32 kcs_gpregs; /* General purpose registers. */
	__u32           kcs_eflags; /* Flags register */
	__u32           kcs_eip;    /* Instruction pointer */
};
#endif /* __CC__ */



#define OFFSET_ICPUSTATE32_GPREGS 0
#define OFFSET_ICPUSTATE32_FS     32
#define OFFSET_ICPUSTATE32_ES     36
#define OFFSET_ICPUSTATE32_DS     40
#define OFFSET_ICPUSTATE32_IRREGS 44
#ifdef __CC__
struct icpustate32 { /* i -- Interrupts */
	/* A  CPU state that is used by  hardware interrupts (other than those used
	 * by scheduling, which generate `scpustate' instead), in order to describe
	 * the interrupted text location.
	 * Also the primary CPU state used by RPC handlers.
	 * Because interrupts always lead into kernel-space, and because the  kernel
	 * doesn't  make use of the %gs register, that register is not saved by this
	 * kind  of  state, and  when  required should  always  be assumed  to equal
	 * `SEGMENT_USER_GSBASE_RPL',  as is the default expectation for user-space.
	 * Note however that because %gs is not saved, its exact value can  therefor
	 * be  read using `__rdgs()'  (though only in the  thread that generated the
	 * `struct icpustate'),  as well as  the fact that  modifications to the %gs
	 * segment selector will not be undone when an `struct icpustate' is loaded. */
	struct gpregs32    ics_gpregs; /* General purpose registers. */
	union {
		__u32          ics_fs;     /* F segment register (Usually `SEGMENT_USER_FSBASE_RPL' / `SEGMENT_KERNEL_FSBASE')
		                            * (upper   16   bits   are   undefined,   but   should   be   written   as  zeros) */
		__u16          ics_fs16;   /* F segment register (Usually `SEGMENT_USER_FSBASE_RPL' / `SEGMENT_KERNEL_FSBASE')
		                            * (upper   16   bits   are   undefined,   but   should   be   written   as  zeros) */
	};
	union {
		__u32          ics_es;     /* E (source) segment register (Usually `SEGMENT_USER_DATA_RPL')
		                            * (upper 16 bits are undefined, but should be written as zeros) */
		__u16          ics_es16;   /* E (source) segment register (Usually `SEGMENT_USER_DATA_RPL') */
	};
	union {
		__u32          ics_ds;     /* D (destination) segment register (Usually `SEGMENT_USER_DATA_RPL')
		                            * (upper 16  bits are  undefined, but  should be  written as  zeros) */
		__u16          ics_ds16;   /* D (destination) segment register (Usually `SEGMENT_USER_DATA_RPL') */
	};
	union {
		/* Interrupt return registers.
		 * NOTE: When  returning to user-space, the ESP inside
		 *       of this  structure  is  the  user-space  EPS.
		 *       Otherwise,  the  return-ESP is  equal  to the
		 *       address of `ir_esp' (Use `icpustate_getsp()')
		 * NOTE: Since the size of this structure depends on one
		 *       of   its   fields,   use   `icpustate_sizeof()'
		 *       to determine it. */
		struct irregs32_kernel ics_irregs;
		struct irregs32_kernel ics_irregs_k;
		struct irregs32_user   ics_irregs_u;
#ifndef __I386_NO_VM86
		struct irregs32_vm86   ics_irregs_v;
#endif /* !__I386_NO_VM86 */
	};
};
#endif /* __CC__ */



#define OFFSET_SCPUSTATE32_GPREGS  0
#define OFFSET_SCPUSTATE32_SGREGS  32
#define OFFSET_SCPUSTATE32_IRREGS  48
#ifdef __CC__
struct scpustate32 { /* s -- Scheduling */
	/* CPU state, as used to store the state of a thread that isn't currently running. */
	struct gpregs32    scs_gpregs; /* General purpose registers. */
	struct sgregs32    scs_sgregs; /* Segment registers. */
	union {
		/* Interrupt return registers.
		 * NOTE: When  returning to user-space, the ESP inside
		 *       of this  structure  is  the  user-space  EPS.
		 *       Otherwise,  the  return-ESP is  equal  to the
		 *       address of `ir_esp' (Use `scpustate_getsp()')
		 * NOTE: Since the size of this structure depends on one
		 *       of   its   fields,   use   `scpustate_sizeof()'
		 *       to determine it. */
		struct irregs32_kernel scs_irregs;
		struct irregs32_kernel scs_irregs_k;
		struct irregs32_user   scs_irregs_u;
#ifndef __I386_NO_VM86
		struct irregs32_vm86   scs_irregs_v;
#endif /* !__I386_NO_VM86 */
	};
};
#endif /* __CC__ */



#define OFFSET_DESCTAB32_LIMIT 0
#define OFFSET_DESCTAB32_BASE  2
#define SIZEOF_DESCTAB32       6
#ifdef __CC__
struct __ATTR_PACKED desctab32 /*[PREFIX(dt_)]*/ {
	__u16   dt_limit; /* Descriptor table limit */
	__u32   dt_base;  /* Descriptor table base */
};
#endif /* __CC__ */



#define OFFSET_FCPUSTATE32_GPREGS 0
#define OFFSET_FCPUSTATE32_EFLAGS 32
#define OFFSET_FCPUSTATE32_EIP    36
#define OFFSET_FCPUSTATE32_ES     40 /* [FIELD(fcs_sgregs.sg_es)] */
#define OFFSET_FCPUSTATE32_CS     44 /* [FIELD(fcs_sgregs.sg_cs)] */
#define OFFSET_FCPUSTATE32_SS     48 /* [FIELD(fcs_sgregs.sg_ss)] */
#define OFFSET_FCPUSTATE32_DS     52 /* [FIELD(fcs_sgregs.sg_ds)] */
#define OFFSET_FCPUSTATE32_FS     56 /* [FIELD(fcs_sgregs.sg_fs)] */
#define OFFSET_FCPUSTATE32_GS     60 /* [FIELD(fcs_sgregs.sg_gs)] */
#define OFFSET_FCPUSTATE32_TR     64 /* [FIELD(fcs_sgregs.sg_tr)] */
#define OFFSET_FCPUSTATE32_LDT    68 /* [FIELD(fcs_sgregs.sg_ldt)] */
#define OFFSET_FCPUSTATE32_COREGS 72
#define OFFSET_FCPUSTATE32_DRREGS 88
#define OFFSET_FCPUSTATE32_GDT    114
#define OFFSET_FCPUSTATE32_IDT    122
#define SIZEOF_FCPUSTATE32        128
#ifdef __CC__
struct fcpustate32 { /* f -- Full */
	/* Full CPU state (including _all_ registers that exist). */
	struct gpregs32  fcs_gpregs; /* General purpose registers. */
	__u32            fcs_eflags; /* Flags register */
	__u32            fcs_eip;    /* Flags register */
	struct {
		union {
			__u32    sg_es;      /* E (source) segment register.
			                      * (upper 16 bits are undefined, but should be written as zeros) */
			__u16    sg_es16;    /* E (source) segment register. */
		};
		union {
			__u32    sg_cs;      /* Code segment register.
		                          * (upper 16 bits are undefined, but should be written as zeros) */
			__u16    sg_cs16;    /* Code segment register. */
		};
		union {
			__u32    sg_ss;      /* Stack segment register.
			                      * (upper 16 bits are undefined, but should be written as zeros) */
			__u16    sg_ss16;    /* Stack segment register. */
		};
		union {
			__u32    sg_ds;      /* D (destination) segment register.
			                      * (upper 16 bits are undefined, but should be written as zeros) */
			__u16    sg_ds16;    /* D (destination) segment register. */
		};
		union {
			__u32    sg_fs;      /* F segment register.
			                      * (upper 16 bits are undefined, but should be written as zeros) */
			__u16    sg_fs16;    /* F segment register. */
		};
		union {
			__u32    sg_gs;      /* G segment register.
			                      * (upper 16 bits are undefined, but should be written as zeros) */
			__u16    sg_gs16;    /* G segment register. */
		};
		union {
			__u32    sg_tr;      /* Task register.
			                      * (upper 16 bits are undefined, but should be written as zeros) */
			__u16    sg_tr16;    /* Task register. */
		};
		union {
			__u32    sg_ldt;     /* Load descriptor table.
			                      * (upper 16 bits are undefined, but should be written as zeros) */
			__u16    sg_ldt16;   /* Load descriptor table. */
		};
	}                fcs_sgregs; /* Segment registers. */
	struct coregs32  fcs_coregs; /* Control registers. */
	struct drregs32  fcs_drregs; /* Debug registers. */
	__u16          __fcs_pad0;   /* ... */
	struct desctab32 fcs_gdt;    /* Global descriptor table. */
	__u16          __fcs_pad1;   /* ... */
	struct desctab32 fcs_idt;    /* Interrupt descriptor table. */
};
#endif /* __CC__ */



__SYSDECL_END

#endif /* !_I386_KOS_KOS_KERNEL_BITS_CPU_STATE32_H */
