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
#ifndef _I386_KOS_KOS_KERNEL_BITS_CPU_STATE64_H
#define _I386_KOS_KOS_KERNEL_BITS_CPU_STATE64_H 1

#include <__crt.h>
#include <__stdinc.h>

#include <hybrid/__pointer.h>
#include <hybrid/host.h>

#include <bits/types.h>

__SYSDECL_BEGIN

#ifdef __x86_64__

#define gpregs64                   gpregs
#define OFFSET_GPREGS_R15          OFFSET_GPREGS64_R15
#define OFFSET_GPREGS_R14          OFFSET_GPREGS64_R14
#define OFFSET_GPREGS_R13          OFFSET_GPREGS64_R13
#define OFFSET_GPREGS_R12          OFFSET_GPREGS64_R12
#define OFFSET_GPREGS_R11          OFFSET_GPREGS64_R11
#define OFFSET_GPREGS_R10          OFFSET_GPREGS64_R10
#define OFFSET_GPREGS_R9           OFFSET_GPREGS64_R9
#define OFFSET_GPREGS_R8           OFFSET_GPREGS64_R8
#define OFFSET_GPREGS_RDI          OFFSET_GPREGS64_RDI
#define OFFSET_GPREGS_RSI          OFFSET_GPREGS64_RSI
#define OFFSET_GPREGS_RBP          OFFSET_GPREGS64_RBP
#define OFFSET_GPREGS_RSP          OFFSET_GPREGS64_RSP
#define OFFSET_GPREGS_RBX          OFFSET_GPREGS64_RBX
#define OFFSET_GPREGS_RDX          OFFSET_GPREGS64_RDX
#define OFFSET_GPREGS_RCX          OFFSET_GPREGS64_RCX
#define OFFSET_GPREGS_RAX          OFFSET_GPREGS64_RAX
#define SIZEOF_GPREGS              SIZEOF_GPREGS64

#define gpregsnsp64                gpregsnsp
#define OFFSET_GPREGSNSP_R15       OFFSET_GPREGSNSP64_R15
#define OFFSET_GPREGSNSP_R14       OFFSET_GPREGSNSP64_R14
#define OFFSET_GPREGSNSP_R13       OFFSET_GPREGSNSP64_R13
#define OFFSET_GPREGSNSP_R12       OFFSET_GPREGSNSP64_R12
#define OFFSET_GPREGSNSP_R11       OFFSET_GPREGSNSP64_R11
#define OFFSET_GPREGSNSP_R10       OFFSET_GPREGSNSP64_R10
#define OFFSET_GPREGSNSP_R9        OFFSET_GPREGSNSP64_R9
#define OFFSET_GPREGSNSP_R8        OFFSET_GPREGSNSP64_R8
#define OFFSET_GPREGSNSP_RDI       OFFSET_GPREGSNSP64_RDI
#define OFFSET_GPREGSNSP_RSI       OFFSET_GPREGSNSP64_RSI
#define OFFSET_GPREGSNSP_RBP       OFFSET_GPREGSNSP64_RBP
/*      OFFSET_GPREGSNSP_RSP       OFFSET_GPREGSNSP64_RSP */
#define OFFSET_GPREGSNSP_RBX       OFFSET_GPREGSNSP64_RBX
#define OFFSET_GPREGSNSP_RDX       OFFSET_GPREGSNSP64_RDX
#define OFFSET_GPREGSNSP_RCX       OFFSET_GPREGSNSP64_RCX
#define OFFSET_GPREGSNSP_RAX       OFFSET_GPREGSNSP64_RAX
#define SIZEOF_GPREGSNSP           SIZEOF_GPREGSNSP64

#define sgregs64                   sgregs
#define OFFSET_SGREGS_GS           OFFSET_SGREGS64_GS
#define OFFSET_SGREGS_FS           OFFSET_SGREGS64_FS
#define OFFSET_SGREGS_ES           OFFSET_SGREGS64_ES
#define OFFSET_SGREGS_DS           OFFSET_SGREGS64_DS
#define SIZEOF_SGREGS              SIZEOF_SGREGS64

#define sgbase64                   sgbase
#define OFFSET_SGBASE_GSBASE       OFFSET_SGBASE64_GSBASE
#define OFFSET_SGBASE_FSBASE       OFFSET_SGBASE64_FSBASE
#define SIZEOF_SGBASE              SIZEOF_SGBASE64

#define coregs64                   coregs
#define OFFSET_COREGS_CR0          OFFSET_COREGS64_CR0
#define OFFSET_COREGS_CR2          OFFSET_COREGS64_CR2
#define OFFSET_COREGS_CR3          OFFSET_COREGS64_CR3
#define OFFSET_COREGS_CR4          OFFSET_COREGS64_CR4
#define SIZEOF_COREGS              SIZEOF_COREGS64

#define drregs64                   drregs
#define OFFSET_DRREGS_DR0          OFFSET_DRREGS64_DR0
#define OFFSET_DRREGS_DR1          OFFSET_DRREGS64_DR1
#define OFFSET_DRREGS_DR2          OFFSET_DRREGS64_DR2
#define OFFSET_DRREGS_DR3          OFFSET_DRREGS64_DR3
#define OFFSET_DRREGS_DR6          OFFSET_DRREGS64_DR6
#define OFFSET_DRREGS_DR7          OFFSET_DRREGS64_DR7
#define SIZEOF_DRREGS              SIZEOF_DRREGS64

#define irregs64                   irregs
#define irregs64_kernel            irregs
#define irregs64_user              irregs
#define irregs_kernel              irregs
#define irregs_user                irregs
#define OFFSET_IRREGS_RIP          OFFSET_IRREGS64_RIP
#define OFFSET_IRREGS_CS           OFFSET_IRREGS64_CS
#define OFFSET_IRREGS_RFLAGS       OFFSET_IRREGS64_RFLAGS
#define OFFSET_IRREGS_RSP          OFFSET_IRREGS64_RSP
#define OFFSET_IRREGS_SS           OFFSET_IRREGS64_SS
#define SIZEOF_IRREGS              SIZEOF_IRREGS64
#define SIZEOF_IRREGS_KERNEL       SIZEOF_IRREGS64
#define SIZEOF_IRREGS_USER         SIZEOF_IRREGS64

#define ucpustate64                ucpustate
#define OFFSET_UCPUSTATE_SGREGS    OFFSET_UCPUSTATE64_SGREGS
#define OFFSET_UCPUSTATE_SGBASE    OFFSET_UCPUSTATE64_SGBASE
#define OFFSET_UCPUSTATE_CS        OFFSET_UCPUSTATE64_CS
#define OFFSET_UCPUSTATE_SS        OFFSET_UCPUSTATE64_SS
#define OFFSET_UCPUSTATE_GPREGS    OFFSET_UCPUSTATE64_GPREGS
#define OFFSET_UCPUSTATE_RFLAGS    OFFSET_UCPUSTATE64_RFLAGS
#define OFFSET_UCPUSTATE_RIP       OFFSET_UCPUSTATE64_RIP
#define SIZEOF_UCPUSTATE           SIZEOF_UCPUSTATE64

#define lcpustate64                lcpustate
#define OFFSET_LCPUSTATE_R15       OFFSET_LCPUSTATE64_R15
#define OFFSET_LCPUSTATE_R14       OFFSET_LCPUSTATE64_R14
#define OFFSET_LCPUSTATE_R13       OFFSET_LCPUSTATE64_R13
#define OFFSET_LCPUSTATE_R12       OFFSET_LCPUSTATE64_R12
#define OFFSET_LCPUSTATE_RBP       OFFSET_LCPUSTATE64_RBP
#define OFFSET_LCPUSTATE_RSP       OFFSET_LCPUSTATE64_RSP
#define OFFSET_LCPUSTATE_RBX       OFFSET_LCPUSTATE64_RBX
#define OFFSET_LCPUSTATE_RIP       OFFSET_LCPUSTATE64_RIP
#define SIZEOF_LCPUSTATE           SIZEOF_LCPUSTATE64

#define kcpustate64                kcpustate
#define OFFSET_KCPUSTATE_GPREGS    OFFSET_KCPUSTATE64_GPREGS
#define OFFSET_KCPUSTATE_RFLAGS    OFFSET_KCPUSTATE64_RFLAGS
#define OFFSET_KCPUSTATE_RIP       OFFSET_KCPUSTATE64_RIP
#define SIZEOF_KCPUSTATE           SIZEOF_KCPUSTATE64

#define icpustate64                icpustate
#define OFFSET_ICPUSTATE_GPREGSNSP OFFSET_ICPUSTATE64_GPREGSNSP
#define OFFSET_ICPUSTATE_IRREGS    OFFSET_ICPUSTATE64_IRREGS
#define SIZEOF_ICPUSTATE           SIZEOF_ICPUSTATE64

#define scpustate64                scpustate
#define OFFSET_SCPUSTATE_SGREGS    OFFSET_SCPUSTATE64_SGREGS
#define OFFSET_SCPUSTATE_SGBASE    OFFSET_SCPUSTATE64_SGBASE
#define OFFSET_SCPUSTATE_GPREGSNSP OFFSET_SCPUSTATE64_GPREGSNSP
#define OFFSET_SCPUSTATE_IRREGS    OFFSET_SCPUSTATE64_IRREGS
#define SIZEOF_SCPUSTATE           SIZEOF_SCPUSTATE64

#define desctab64                  desctab
#define OFFSET_DESCTAB_LIMIT       OFFSET_DESCTAB64_LIMIT
#define OFFSET_DESCTAB_BASE        OFFSET_DESCTAB64_BASE
#define SIZEOF_DESCTAB             SIZEOF_DESCTAB64

#define fcpustate64                fcpustate
#define OFFSET_FCPUSTATE_GPREGS    OFFSET_FCPUSTATE64_GPREGS
#define OFFSET_FCPUSTATE_RFLAGS    OFFSET_FCPUSTATE64_RFLAGS
#define OFFSET_FCPUSTATE_RIP       OFFSET_FCPUSTATE64_RIP
#define OFFSET_FCPUSTATE_ES        OFFSET_FCPUSTATE64_ES
#define OFFSET_FCPUSTATE_CS        OFFSET_FCPUSTATE64_CS
#define OFFSET_FCPUSTATE_SS        OFFSET_FCPUSTATE64_SS
#define OFFSET_FCPUSTATE_DS        OFFSET_FCPUSTATE64_DS
#define OFFSET_FCPUSTATE_FS        OFFSET_FCPUSTATE64_FS
#define OFFSET_FCPUSTATE_GS        OFFSET_FCPUSTATE64_GS
#define OFFSET_FCPUSTATE_TR        OFFSET_FCPUSTATE64_TR
#define OFFSET_FCPUSTATE_LDT       OFFSET_FCPUSTATE64_LDT
#define OFFSET_FCPUSTATE_SGBASE    OFFSET_FCPUSTATE64_SGBASE
#define OFFSET_FCPUSTATE_SGREGS    OFFSET_FCPUSTATE64_SGREGS
#define OFFSET_FCPUSTATE_COREGS    OFFSET_FCPUSTATE64_COREGS
#define OFFSET_FCPUSTATE_DRREGS    OFFSET_FCPUSTATE64_DRREGS
#define OFFSET_FCPUSTATE_GDT       OFFSET_FCPUSTATE64_GDT
#define OFFSET_FCPUSTATE_IDT       OFFSET_FCPUSTATE64_IDT
#define SIZEOF_FCPUSTATE           SIZEOF_FCPUSTATE64

#endif /* __x86_64__ */


#define OFFSET_GPREGS64_R15 0
#define OFFSET_GPREGS64_R14 8
#define OFFSET_GPREGS64_R13 16
#define OFFSET_GPREGS64_R12 24
#define OFFSET_GPREGS64_R11 32
#define OFFSET_GPREGS64_R10 40
#define OFFSET_GPREGS64_R9  48
#define OFFSET_GPREGS64_R8  56
#define OFFSET_GPREGS64_RDI 64
#define OFFSET_GPREGS64_RSI 72
#define OFFSET_GPREGS64_RBP 80
#define OFFSET_GPREGS64_RSP 88
#define OFFSET_GPREGS64_RBX 96
#define OFFSET_GPREGS64_RDX 104
#define OFFSET_GPREGS64_RCX 112
#define OFFSET_GPREGS64_RAX 120
#define SIZEOF_GPREGS64     128
#ifdef __CC__
struct gpregs64 {
	__u64   gp_r15;    /* [P] General purpose register #15 */
	__u64   gp_r14;    /* [P] General purpose register #14 */
	__u64   gp_r13;    /* [P] General purpose register #13 */
	__u64   gp_r12;    /* [P] General purpose register #12 */
	__u64   gp_r11;    /* [C] General purpose register #11 */
	__u64   gp_r10;    /* [C] General purpose register #10 */
	__u64   gp_r9;     /* [C] General purpose register #9 */
	__u64   gp_r8;     /* [C] General purpose register #8 */
	__u64   gp_rdi;    /* [C] Destination pointer */
	__u64   gp_rsi;    /* [C] Source pointer */
	__u64   gp_rbp;    /* [P] Frame base pointer */
	__u64   gp_rsp;    /* [P] Stack pointer */
	__u64   gp_rbx;    /* [P] Base register */
	__u64   gp_rdx;    /* [C] Data register */
	__u64   gp_rcx;    /* [C] Count register */
	__u64   gp_rax;    /* [C] Accumulator register */
};
#endif /* __CC__ */



#define OFFSET_GPREGSNSP64_R15 0
#define OFFSET_GPREGSNSP64_R14 8
#define OFFSET_GPREGSNSP64_R13 16
#define OFFSET_GPREGSNSP64_R12 24
#define OFFSET_GPREGSNSP64_R11 32
#define OFFSET_GPREGSNSP64_R10 40
#define OFFSET_GPREGSNSP64_R9  48
#define OFFSET_GPREGSNSP64_R8  56
#define OFFSET_GPREGSNSP64_RDI 64
#define OFFSET_GPREGSNSP64_RSI 72
#define OFFSET_GPREGSNSP64_RBP 80
/*      OFFSET_GPREGSNSP64_RSP ... */
#define OFFSET_GPREGSNSP64_RBX 88
#define OFFSET_GPREGSNSP64_RDX 96
#define OFFSET_GPREGSNSP64_RCX 104
#define OFFSET_GPREGSNSP64_RAX 112
#define SIZEOF_GPREGSNSP64     120
#ifdef __CC__
struct gpregsnsp64 /*[PREFIX(gp_)]*/ {
	__u64   gp_r15;    /* [P] General purpose register #15 */
	__u64   gp_r14;    /* [P] General purpose register #14 */
	__u64   gp_r13;    /* [P] General purpose register #13 */
	__u64   gp_r12;    /* [P] General purpose register #12 */
	__u64   gp_r11;    /* [C] General purpose register #11 */
	__u64   gp_r10;    /* [C] General purpose register #10 */
	__u64   gp_r9;     /* [C] General purpose register #9 */
	__u64   gp_r8;     /* [C] General purpose register #8 */
	__u64   gp_rdi;    /* [C] Destination pointer */
	__u64   gp_rsi;    /* [C] Source pointer */
	__u64   gp_rbp;    /* [P] Frame base pointer */
	__u64   gp_rbx;    /* [P] Base register */
	__u64   gp_rdx;    /* [C] Data register */
	__u64   gp_rcx;    /* [C] Count register */
	__u64   gp_rax;    /* [C] Accumulator register */
};
#endif /* __CC__ */



#define OFFSET_SGREGS64_GS  0
#define OFFSET_SGREGS64_FS  8
#define OFFSET_SGREGS64_ES  16
#define OFFSET_SGREGS64_DS  24
#define SIZEOF_SGREGS64     32
#ifdef __CC__
struct sgregs64 {
	union {
		__u64 sg_gs;     /* G  segment   register   (Usually   `SEGMENT_USER_GSBASE_RPL')
		                  * (upper 48 bits are undefined, but should be written as zeros) */
		__u16 sg_gs16;   /* G segment register (Usually `SEGMENT_USER_GSBASE_RPL') */
	};
	union {
		__u64 sg_fs;     /* F segment register (Usually `SEGMENT_USER_FSBASE_RPL' / `SEGMENT_KERNEL_FSBASE')
		                  * (upper   48   bits   are   undefined,   but   should   be   written   as  zeros) */
		__u16 sg_fs16;   /* F segment register (Usually `SEGMENT_USER_FSBASE_RPL' / `SEGMENT_KERNEL_FSBASE') */
	};
	union {
		__u64 sg_es;     /* E (source) segment register (Usually `SEGMENT_USER_DATA_RPL')
		                  * (upper 48 bits are undefined, but should be written as zeros) */
		__u16 sg_es16;   /* E (source) segment register (Usually `SEGMENT_USER_DATA_RPL') */
	};
	union {
		__u64 sg_ds;     /* D (destination) segment register (Usually `SEGMENT_USER_DATA_RPL')
		                  * (upper 48  bits are  undefined, but  should be  written as  zeros) */
		__u16 sg_ds16;   /* D (destination) segment register (Usually `SEGMENT_USER_DATA_RPL') */
	};
};
#endif /* __CC__ */


#define OFFSET_SGBASE64_GSBASE  0
#define OFFSET_SGBASE64_FSBASE  8
#define SIZEOF_SGBASE64         16
#ifdef __CC__
struct sgbase64 /*[PREFIX(sg_)]*/ {
	__u64   sg_gsbase;  /* G segment register base (for user-space) */
	__u64   sg_fsbase;  /* F segment register base */
};
#endif /* __CC__ */



#define OFFSET_COREGS64_CR0 0
#define OFFSET_COREGS64_CR2 8
#define OFFSET_COREGS64_CR3 16
#define OFFSET_COREGS64_CR4 24
#define SIZEOF_COREGS64     32
#ifdef __CC__
struct coregs64 {
	__u64                co_cr0; /* %cr0 (Set of `CR0_*' from `/include/i386-kos/asm/cpu-flags.h') */
	__HYBRID_PTR64(void) co_cr2; /* %cr2 (Page Fault Linear Address (PFLA) (when a #PF occurs, contains that fault's address)) */
	__u64                co_cr3; /* %cr3 (Page Directory Linear Address) */
	__u64                co_cr4; /* %cr4 (Set of `CR4_*' from `/include/i386-kos/asm/cpu-flags.h') */
};
#endif /* __CC__ */



#define OFFSET_DRREGS64_DR0  0
#define OFFSET_DRREGS64_DR1  8
#define OFFSET_DRREGS64_DR2  16
#define OFFSET_DRREGS64_DR3  24
#define OFFSET_DRREGS64_DR6  32
#define OFFSET_DRREGS64_DR7  40
#define SIZEOF_DRREGS64      48
#ifdef __CC__
struct drregs64 {
	__HYBRID_PTR64(void) dr_dr0; /* %dr0 (Linear address of first breakpoint) */
	__HYBRID_PTR64(void) dr_dr1; /* %dr1 (Linear address of second breakpoint) */
	__HYBRID_PTR64(void) dr_dr2; /* %dr2 (Linear address of third breakpoint) */
	__HYBRID_PTR64(void) dr_dr3; /* %dr3 (Linear address of fourth breakpoint) */
	__u64                dr_dr6; /* %dr6 (Debug status) */
	__u64                dr_dr7; /* %dr7 (Debug control (set of `DR7_*' from `/include/i386-kos/asm/cpu-flags.h')) */
};
#endif /* __CC__ */



#define OFFSET_IRREGS64_RIP    0
#define OFFSET_IRREGS64_CS     8
#define OFFSET_IRREGS64_RFLAGS 16
#define OFFSET_IRREGS64_RSP    24
#define OFFSET_IRREGS64_SS     32
#define SIZEOF_IRREGS64        40
#ifdef __CC__
struct irregs64 {
	/* On x86_64, the interrupt return tail always looks the same. */
	__u64     ir_rip;    /* Instruction pointer */
	union {
		__u64 ir_cs;     /* Code   segment   (Ring  #0,   usually  `SEGMENT_KERNEL_CODE')
		                  * (upper 48 bits are undefined, but should be written as zeros) */
		__u16 ir_cs16;   /* Code segment (Ring #0, usually `SEGMENT_KERNEL_CODE') */
	};
	__u64     ir_rflags; /* Flags register */
	__u64     ir_rsp;    /* Return stack pointer */
	union {
		__u64 ir_ss;     /* Return stack segment (Ring #0, usually `SEGMENT_KERNEL_DATA' or `0')
		                  * (upper  48  bits  are undefined,  but  should be  written  as zeros) */
		__u16 ir_ss16;   /* Return stack segment (Ring #0, usually `SEGMENT_KERNEL_DATA' or `0') */
	};
};
#endif /* __CC__ */



#define OFFSET_UCPUSTATE64_SGREGS 0
#define OFFSET_UCPUSTATE64_SGBASE 32
#define OFFSET_UCPUSTATE64_CS     48
#define OFFSET_UCPUSTATE64_SS     56
#define OFFSET_UCPUSTATE64_GPREGS 64
#define OFFSET_UCPUSTATE64_RFLAGS 192
#define OFFSET_UCPUSTATE64_RIP    200
#define SIZEOF_UCPUSTATE64        208
#ifdef __CC__
struct ucpustate64 { /* u -- User */
	/* Full CPU state, as used by system calls.
	 * NOTE: Also represents the state saved when an exception occurs,
	 *       both   inside   kernel-,    as   well   as    user-space. */
	struct sgregs64 ucs_sgregs; /* Segment registers. */
	struct sgbase64 ucs_sgbase; /* Segment base registers. */
	union {
		__u64       ucs_cs;     /* Code  segment  (Ring  #3,  usually   `SEGMENT_USER_CODE_RPL')
		                         * (upper 48 bits are undefined, but should be written as zeros) */
		__u16       ucs_cs16;   /* Code segment (Ring #3, usually `SEGMENT_USER_CODE_RPL') */
	};
	union {
		__u64       ucs_ss;     /* Stack  segment  (Ring  #3,  usually  `SEGMENT_USER_DATA_RPL')
		                         * (upper 48 bits are undefined, but should be written as zeros) */
		__u16       ucs_ss16;   /* Stack segment (Ring #3, usually `SEGMENT_USER_DATA_RPL') */
	};
	struct gpregs64 ucs_gpregs; /* General purpose registers. */
	__u64           ucs_rflags; /* Flags register */
	__u64           ucs_rip;    /* Instruction pointer */
};
#endif /* __CC__ */



#define OFFSET_LCPUSTATE64_R15  0
#define OFFSET_LCPUSTATE64_R14  8
#define OFFSET_LCPUSTATE64_R13  16
#define OFFSET_LCPUSTATE64_R12  24
#define OFFSET_LCPUSTATE64_RBP  32
#define OFFSET_LCPUSTATE64_RSP  40
#define OFFSET_LCPUSTATE64_RBX  48
#define OFFSET_LCPUSTATE64_RIP  56
#define SIZEOF_LCPUSTATE64      64
#ifdef __CC__
struct lcpustate64 { /* l -- Little */
	/* A minimal CPU state containing only registers that are callee-preserved.
	 * This kind  of  CPU  state  is most  useful  for  generating  tracebacks. */
	__u64         lcs_r15;    /* [P] General purpose register #15 */
	__u64         lcs_r14;    /* [P] General purpose register #14 */
	__u64         lcs_r13;    /* [P] General purpose register #13 */
	__u64         lcs_r12;    /* [P] General purpose register #12 */
	__u64         lcs_rbp;    /* [P] Frame base pointer */
	__u64         lcs_rsp;    /* [P] Stack pointer */
	__u64         lcs_rbx;    /* [P] Base register */
	__u64         lcs_rip;    /* Instruction pointer */
};
#endif /* __CC__ */



#define OFFSET_KCPUSTATE64_GPREGS  0
#define OFFSET_KCPUSTATE64_RFLAGS  128
#define OFFSET_KCPUSTATE64_RIP     136
#define SIZEOF_KCPUSTATE64         144
#ifdef __CC__
struct kcpustate64 {
	/* A CPU state used to describe a known, valid register state in kernel-space.
	 * This  kind of state is also used  by exception handling, and the associated
	 * stack unwinding. */
	struct gpregs64 kcs_gpregs; /* General purpose registers. */
	__u64           kcs_rflags; /* Flags register */
	__u64           kcs_rip;    /* Instruction pointer */
};
#endif /* __CC__ */



#define OFFSET_ICPUSTATE64_GPREGSNSP 0   /* [FIELD(ics_gpregs)] */
#define OFFSET_ICPUSTATE64_IRREGS    120
#define SIZEOF_ICPUSTATE64           160
#ifdef __CC__
struct icpustate64 { /* i -- Interrupts */
	/* A  CPU state that is used by  hardware interrupts (other than those used
	 * by scheduling, which generate `scpustate' instead), in order to describe
	 * the interrupted text location.
	 * Also the primary CPU state used by RPC handlers.
	 * Note that while inside of an interrupt, the %gs_base value that's going
	 * to be restored depends on `ics_irregs.ir_cs & 3'.
	 * If user-space is indicated, `swapgs' is executed and `%gs_base' is filled
	 * with `IA32_KERNEL_GS_BASE', with  the original  `%gs_base' value  written
	 * back into `IA32_KERNEL_GS_BASE'
	 * As such, while  inside of kernel-space,  the user-space-return  value
	 * for `%gs_base' is stored within `IA32_KERNEL_GS_BASE' (don't let  the
	 * name of that MSR fool you. - While in kernel-space, this is the user-
	 * space %gs_base value!)
	 * NOTES:
	 *   - Wherever an icpustate is used, that state is applicable in the context
	 *     of the current thread (You will  never find an icpustate belonging  to
	 *     another thread, and if you do, something has probably gone wrong)
	 *   - With this in mind, registers not apart of this structure retain their
	 *     effective  values, meaning that %ds, %es, %fs, %gs, %fs.base, %tr and
	 *     %ldtr continue to hold their values from wherever the interrupt
	 *     originated from.
	 *   - %gs.base is a bit more complicated, since it is made up of 2 different
	 *     registers %gs.base and %gs.kernel_base that  can be exchanged for  each
	 *     other (don't let the name %gs.kernel_base fool you; the implied meaning
	 *     only holds true while in user-space;  a better name would be  something
	 *     like %gs.inactive_base)
	 *
	 * When an icpustate is created/exited:
	 *     >> entry:
	 *     >>     testb  $3, OFFSET_IRREGS_CS(%rsp)
	 *     >>     jz     1f
	 *     >>     swapgs
	 *     >> 1:  pushq_cfi_r <EACH_GP_REG>
	 *     >>
	 *     >> ...
	 *     >>
	 *     >> exit:
	 *     >>     popq_cfi_r <EACH_GP_REG>
	 *     >>     testb  $3, OFFSET_IRREGS_CS(%rsp)
	 *     >>     jz     1f
	 *     >>     cli      // Prevent interrupts after swapgs (when %gs.base already has its user-space value)
	 *     >>     swapgs
	 *     >> 1:  iretq
	 * To read/write the %gs.base that's restored when an icpustate returns:
	 *     >> gs_base = ics_irregs.ir_cs & 3 ? __rdmsr(IA32_KERNEL_GS_BASE) : __rdgsbase();
	 * To read/write the %gs.base that's to-be used for user-space:
	 *     >> gs_base = __rdmsr(IA32_KERNEL_GS_BASE);
	 */
	struct gpregsnsp64 ics_gpregs; /* General purpose registers. */
	struct irregs64    ics_irregs; /* Interrupt return registers. */
};
#endif /* __CC__ */



#define OFFSET_SCPUSTATE64_SGREGS        0
#define OFFSET_SCPUSTATE64_SGBASE        32
#define OFFSET_SCPUSTATE64_GPREGSNSP     48 /* [FIELD(scs_gpregs)] */
#define OFFSET_SCPUSTATE64_IRREGS        168
#define SIZEOF_SCPUSTATE64               208
#ifdef __CC__
struct scpustate64 { /* s -- Scheduling */
	/* CPU state, as used to store the state of a thread that isn't currently running. */
	struct sgregs64    scs_sgregs;        /* Segment registers. */
	struct sgbase64    scs_sgbase;        /* Segment base registers.
	                                       * NOTE: These are _always_ the user-space values!
	                                       * In other words: `sg_gsbase' mirrors `IA32_KERNEL_GS_BASE';
	                                       * s.a. <asm/instr/kernel-gs-base.h>
	                                       * The kernel-space `%gs.base' is always the address of the
	                                       * associated `struct task *', and thus isn't considered to
	                                       * be a register that is saved/restored. */
	struct gpregsnsp64 scs_gpregs;        /* General purpose registers. */
	struct irregs64    scs_irregs;        /* Interrupt return registers. */
};
#endif /* __CC__ */



#define OFFSET_DESCTAB64_LIMIT 0
#define OFFSET_DESCTAB64_BASE  2
#define SIZEOF_DESCTAB64       10
#ifdef __CC__
struct __ATTR_PACKED desctab64 /*[PREFIX(dt_)]*/ {
	__u16   dt_limit;  /* Descriptor table limit */
	__u64   dt_base;   /* Descriptor table base */
};
#endif /* __CC__ */



#define OFFSET_FCPUSTATE64_GPREGS 0
#define OFFSET_FCPUSTATE64_RFLAGS 128
#define OFFSET_FCPUSTATE64_RIP    136
#define OFFSET_FCPUSTATE64_ES     144 /* [FIELD(fcs_sgregs.sg_es)] */
#define OFFSET_FCPUSTATE64_CS     152 /* [FIELD(fcs_sgregs.sg_cs)] */
#define OFFSET_FCPUSTATE64_SS     160 /* [FIELD(fcs_sgregs.sg_ss)] */
#define OFFSET_FCPUSTATE64_DS     168 /* [FIELD(fcs_sgregs.sg_ds)] */
#define OFFSET_FCPUSTATE64_FS     176 /* [FIELD(fcs_sgregs.sg_fs)] */
#define OFFSET_FCPUSTATE64_GS     184 /* [FIELD(fcs_sgregs.sg_gs)] */
#define OFFSET_FCPUSTATE64_TR     192 /* [FIELD(fcs_sgregs.sg_tr)] */
#define OFFSET_FCPUSTATE64_LDT    200 /* [FIELD(fcs_sgregs.sg_ldt)] */
#define OFFSET_FCPUSTATE64_SGBASE 208
#define OFFSET_FCPUSTATE64_COREGS 224
#define OFFSET_FCPUSTATE64_DRREGS 256
#define OFFSET_FCPUSTATE64_GDT    310
#define OFFSET_FCPUSTATE64_IDT    326
#define SIZEOF_FCPUSTATE64        336
#ifdef __CC__
struct fcpustate64 { /* f -- Full */
	/* Full CPU state (including _all_ registers that exist). */
	struct gpregs64  fcs_gpregs; /* General purpose registers. */
	__u64            fcs_rflags; /* Flags register */
	__u64            fcs_rip;    /* Flags register */
	struct {
		union {
			__u64    sg_es;       /* E (source) segment register.
			                       * (upper 48 bits are undefined, but should be written as zeros) */
			__u16    sg_es16;     /* E (source) segment register. */
		};
		union {
			__u64    sg_cs;       /* Code segment register.
			                       * (upper 48 bits are undefined, but should be written as zeros) */
			__u16    sg_cs16;     /* Code segment register. */
		};
		union {
			__u64    sg_ss;       /* Stack segment register.
			                       * (upper 48 bits are undefined, but should be written as zeros) */
			__u16    sg_ss16;     /* Stack segment register. */
		};
		union {
			__u64    sg_ds;       /* D (destination) segment register.
			                       * (upper 48 bits are undefined, but should be written as zeros) */
			__u16    sg_ds16;     /* D (destination) segment register. */
		};
		union {
			__u64    sg_fs;       /* F segment register.
			                       * (upper 48 bits are undefined, but should be written as zeros) */
			__u16    sg_fs16;     /* F segment register. */
		};
		union {
			__u64    sg_gs;       /* G segment register.
			                       * (upper 48 bits are undefined, but should be written as zeros) */
			__u16    sg_gs16;     /* G segment register. */
		};
		union {
			__u64    sg_tr;       /* Task register.
			                       * (upper 48 bits are undefined, but should be written as zeros) */
			__u16    sg_tr16;     /* Task register. */
		};
		union {
			__u64    sg_ldt;      /* Load descriptor table.
			                       * (upper 48 bits are undefined, but should be written as zeros) */
			__u16    sg_ldt16;    /* Load descriptor table. */
		};
	}                fcs_sgregs;  /* Segment index registers. */
	struct sgbase64  fcs_sgbase;  /* Segment base registers. */
	struct coregs64  fcs_coregs;  /* Control registers. */
	struct drregs64  fcs_drregs;  /* Debug registers. */
	__u16          __fcs_pad0[3]; /* ... */
	struct desctab64 fcs_gdt;     /* Global descriptor table. */
	__u16          __fcs_pad1[3]; /* ... */
	struct desctab64 fcs_idt;     /* Interrupt descriptor table. */
};
#endif /* __CC__ */



__SYSDECL_END

#endif /* !_I386_KOS_KOS_KERNEL_BITS_CPU_STATE64_H */
