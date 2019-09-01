/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _I386_KOS_KOS_KERNEL_CPU_STATE32_H
#define _I386_KOS_KOS_KERNEL_CPU_STATE32_H 1

#include <__crt.h>
#include <__stdinc.h>

#include <bits/types.h>
#include <hybrid/host.h>

#include "gdt.h"

__SYSDECL_BEGIN

#ifndef __x86_64__

#define gpregs32          gpregs
#define OFFSET_GPREGS_EDI OFFSET_GPREGS32_EDI
#define OFFSET_GPREGS_ESI OFFSET_GPREGS32_ESI
#define OFFSET_GPREGS_EBP OFFSET_GPREGS32_EBP
#define OFFSET_GPREGS_ESP OFFSET_GPREGS32_ESP
#define OFFSET_GPREGS_EBX OFFSET_GPREGS32_EBX
#define OFFSET_GPREGS_EDX OFFSET_GPREGS32_EDX
#define OFFSET_GPREGS_ECX OFFSET_GPREGS32_ECX
#define OFFSET_GPREGS_EAX OFFSET_GPREGS32_EAX
#define SIZEOF_GPREGS     SIZEOF_GPREGS32

#define sgregs32          sgregs
#define OFFSET_SGREGS_GS  OFFSET_SGREGS32_GS
#define OFFSET_SGREGS_FS  OFFSET_SGREGS32_FS
#define OFFSET_SGREGS_ES  OFFSET_SGREGS32_ES
#define OFFSET_SGREGS_DS  OFFSET_SGREGS32_DS
#define SIZEOF_SGREGS     SIZEOF_SGREGS32

#define coregs32          coregs
#define OFFSET_COREGS_CR0 OFFSET_COREGS32_CR0
#define OFFSET_COREGS_CR2 OFFSET_COREGS32_CR2
#define OFFSET_COREGS_CR3 OFFSET_COREGS32_CR3
#define OFFSET_COREGS_CR4 OFFSET_COREGS32_CR4
#define SIZEOF_COREGS     SIZEOF_COREGS32

#define drregs32          drregs
#define OFFSET_DRREGS_DR0 OFFSET_DRREGS32_DR0
#define OFFSET_DRREGS_DR1 OFFSET_DRREGS32_DR1
#define OFFSET_DRREGS_DR2 OFFSET_DRREGS32_DR2
#define OFFSET_DRREGS_DR3 OFFSET_DRREGS32_DR3
#define OFFSET_DRREGS_DR6 OFFSET_DRREGS32_DR6
#define OFFSET_DRREGS_DR7 OFFSET_DRREGS32_DR7
#define SIZEOF_DRREGS     SIZEOF_DRREGS32

#define irregs32_kernel         irregs_kernel
#define irregs32_user           irregs_user
#define irregs32_vm86           irregs_vm86
#define OFFSET_IRREGS_EIP       OFFSET_IRREGS32_EIP
#define OFFSET_IRREGS_CS        OFFSET_IRREGS32_CS
#define OFFSET_IRREGS_EFLAGS    OFFSET_IRREGS32_EFLAGS
#define SIZEOF_IRREGS_KERNEL    SIZEOF_IRREGS32_KERNEL
#define OFFSET_IRREGS_ESP       OFFSET_IRREGS32_ESP
#define OFFSET_IRREGS_SS        OFFSET_IRREGS32_SS
#define SIZEOF_IRREGS_USER      SIZEOF_IRREGS32_USER
#define OFFSET_IRREGS_ES        OFFSET_IRREGS32_ES
#define OFFSET_IRREGS_DS        OFFSET_IRREGS32_DS
#define OFFSET_IRREGS_FS        OFFSET_IRREGS32_FS
#define OFFSET_IRREGS_GS        OFFSET_IRREGS32_GS
#define SIZEOF_IRREGS_VM86      SIZEOF_IRREGS32_VM86
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
#define IRREGS_SP                   IRREGS32_SP
#define IRREGS_PC                   IRREGS32_PC

#define IRREGS32_ISVM86         IRREGS32_ISVM86
#define IRREGS32_ISKERNEL       IRREGS32_ISKERNEL
#define IRREGS32_ISUSER         IRREGS32_ISUSER
#define IRREGS32_ISUSER_OR_VM86 IRREGS32_ISUSER_OR_VM86
#define IRREGS32_USER_ESP       IRREGS32_USER_ESP
#define IRREGS32_USER_SS        IRREGS32_USER_SS
#define IRREGS32_KERNEL_ESP     IRREGS32_KERNEL_ESP
#define IRREGS32_KERNEL_SS      IRREGS32_KERNEL_SS
#define IRREGS32_PC             IRREGS32_PC
#define IRREGS32_SP             IRREGS32_SP
#define IRREGS32_SS             IRREGS32_SS
#define IRREGS32_WRSP           IRREGS32_WRSP
#define IRREGS32_WRSS           IRREGS32_WRSS
#define IRREGS32_SIZEOF         IRREGS32_SIZEOF

#define ucpustate32             ucpustate
#define OFFSET_UCPUSTATE_GPREGS OFFSET_UCPUSTATE32_GPREGS
#define OFFSET_UCPUSTATE_SGREGS OFFSET_UCPUSTATE32_SGREGS
#define OFFSET_UCPUSTATE_CS     OFFSET_UCPUSTATE32_CS
#define OFFSET_UCPUSTATE_SS     OFFSET_UCPUSTATE32_SS
#define OFFSET_UCPUSTATE_EFLAGS OFFSET_UCPUSTATE32_EFLAGS
#define OFFSET_UCPUSTATE_EIP    OFFSET_UCPUSTATE32_EIP
#define SIZEOF_UCPUSTATE        SIZEOF_UCPUSTATE32
#define UCPUSTATE_PC            UCPUSTATE32_PC
#define UCPUSTATE_SP            UCPUSTATE32_SP

#define lcpustate32            lcpustate
#define OFFSET_LCPUSTATE_EDI   OFFSET_LCPUSTATE32_EDI
#define OFFSET_LCPUSTATE_ESI   OFFSET_LCPUSTATE32_ESI
#define OFFSET_LCPUSTATE_EBP   OFFSET_LCPUSTATE32_EBP
#define OFFSET_LCPUSTATE_ESP   OFFSET_LCPUSTATE32_ESP
#define OFFSET_LCPUSTATE_EBX   OFFSET_LCPUSTATE32_EBX
#define OFFSET_LCPUSTATE_EIP   OFFSET_LCPUSTATE32_EIP
#define SIZEOF_LCPUSTATE       SIZEOF_LCPUSTATE32
#define LCPUSTATE_TO_GPREGS    LCPUSTATE32_TO_GPREGS32
#define LCPUSTATE_TO_UCPUSTATE LCPUSTATE32_TO_UCPUSTATE32
#define LCPUSTATE_TO_KCPUSTATE LCPUSTATE32_TO_KCPUSTATE32
#define LCPUSTATE_PC           LCPUSTATE32_PC
#define LCPUSTATE_SP           LCPUSTATE32_SP

#define kcpustate32             kcpustate
#define OFFSET_KCPUSTATE_GPREGS OFFSET_KCPUSTATE32_GPREGS
#define OFFSET_KCPUSTATE_EFLAGS OFFSET_KCPUSTATE32_EFLAGS
#define OFFSET_KCPUSTATE_EIP    OFFSET_KCPUSTATE32_EIP
#define SIZEOF_KCPUSTATE        SIZEOF_KCPUSTATE32
#define KCPUSTATE_TO_UCPUSTATE  KCPUSTATE32_TO_UCPUSTATE32
#define KCPUSTATE_TO_LCPUSTATE  KCPUSTATE32_TO_LCPUSTATE32
#define KCPUSTATE_PC            KCPUSTATE32_PC
#define KCPUSTATE_SP            KCPUSTATE32_SP


#define icpustate32              icpustate
#define OFFSET_ICPUSTATE_GPREGS  OFFSET_ICPUSTATE32_GPREGS
#define OFFSET_ICPUSTATE_FS      OFFSET_ICPUSTATE32_FS
#define OFFSET_ICPUSTATE_ES      OFFSET_ICPUSTATE32_ES
#define OFFSET_ICPUSTATE_DS      OFFSET_ICPUSTATE32_DS
#define OFFSET_ICPUSTATE_IRREGS  OFFSET_ICPUSTATE32_IRREGS
#define ICPUSTATE_TO_UCPUSTATE   ICPUSTATE32_TO_UCPUSTATE32
#define ICPUSTATE_ISVM86         ICPUSTATE32_ISVM86
#define ICPUSTATE_ISKERNEL       ICPUSTATE32_ISKERNEL
#define ICPUSTATE_ISUSER         ICPUSTATE32_ISUSER
#define ICPUSTATE_ISUSER_OR_VM86 ICPUSTATE32_ISUSER_OR_VM86
#define ICPUSTATE_USER_ESP       ICPUSTATE32_USER_ESP
#define ICPUSTATE_KERNEL_ESP     ICPUSTATE32_KERNEL_ESP
#define ICPUSTATE_USER_SS        ICPUSTATE32_USER_SS
#define ICPUSTATE_KERNEL_SS      ICPUSTATE32_KERNEL_SS
#define ICPUSTATE_PC             ICPUSTATE32_PC
#define ICPUSTATE_DS             ICPUSTATE32_DS
#define ICPUSTATE_ES             ICPUSTATE32_ES
#define ICPUSTATE_FS             ICPUSTATE32_FS
#define ICPUSTATE_GS             ICPUSTATE32_GS
#define ICPUSTATE_WRDS           ICPUSTATE32_WRDS
#define ICPUSTATE_WRES           ICPUSTATE32_WRES
#define ICPUSTATE_WRFS           ICPUSTATE32_WRFS
#define ICPUSTATE_WRGS           ICPUSTATE32_WRGS
#define ICPUSTATE_SP             ICPUSTATE32_SP
#define ICPUSTATE_SS             ICPUSTATE32_SS
#define ICPUSTATE_WRSP           ICPUSTATE32_WRSP
#define ICPUSTATE_WRSS           ICPUSTATE32_WRSS
#define ICPUSTATE_SIZEOF         ICPUSTATE32_SIZEOF

#define scpustate32              scpustate
#define OFFSET_SCPUSTATE_GPREGS  OFFSET_SCPUSTATE32_GPREGS
#define OFFSET_SCPUSTATE_SGREGS  OFFSET_SCPUSTATE32_SGREGS
#define OFFSET_SCPUSTATE_IRREGS  OFFSET_SCPUSTATE32_IRREGS
#define SCPUSTATE_TO_UCPUSTATE   SCPUSTATE32_TO_UCPUSTATE32
#define SCPUSTATE_ISVM86         SCPUSTATE32_ISVM86
#define SCPUSTATE_ISKERNEL       SCPUSTATE32_ISKERNEL
#define SCPUSTATE_ISUSER         SCPUSTATE32_ISUSER
#define SCPUSTATE_ISUSER_OR_VM86 SCPUSTATE32_ISUSER_OR_VM86
#define SCPUSTATE_USER_ESP       SCPUSTATE32_USER_ESP
#define SCPUSTATE_KERNEL_ESP     SCPUSTATE32_KERNEL_ESP
#define SCPUSTATE_USER_SS        SCPUSTATE32_USER_SS
#define SCPUSTATE_KERNEL_SS      SCPUSTATE32_KERNEL_SS
#define SCPUSTATE_PC             SCPUSTATE32_PC
#define SCPUSTATE_DS             SCPUSTATE32_DS
#define SCPUSTATE_ES             SCPUSTATE32_ES
#define SCPUSTATE_FS             SCPUSTATE32_FS
#define SCPUSTATE_GS             SCPUSTATE32_GS
#define SCPUSTATE_WRDS           SCPUSTATE32_WRDS
#define SCPUSTATE_WRES           SCPUSTATE32_WRES
#define SCPUSTATE_WRFS           SCPUSTATE32_WRFS
#define SCPUSTATE_WRGS           SCPUSTATE32_WRGS
#define SCPUSTATE_SP             SCPUSTATE32_SP
#define SCPUSTATE_SS             SCPUSTATE32_SS
#define SCPUSTATE_WRSP           SCPUSTATE32_WRSP
#define SCPUSTATE_WRSS           SCPUSTATE32_WRSS
#define SCPUSTATE_SIZEOF         SCPUSTATE32_SIZEOF

#define desctab32            desctab
#define OFFSET_DESCTAB_LIMIT OFFSET_DESCTAB32_LIMIT
#define OFFSET_DESCTAB_BASE  OFFSET_DESCTAB32_BASE
#define SIZEOF_DESCTAB       SIZEOF_DESCTAB32

#define fcpustate32             fcpustate
#define OFFSET_FCPUSTATE_GPREGS OFFSET_FCPUSTATE32_GPREGS
#define OFFSET_FCPUSTATE_EFLAGS OFFSET_FCPUSTATE32_EFLAGS
#define OFFSET_FCPUSTATE_EIP    OFFSET_FCPUSTATE32_EIP
#define OFFSET_FCPUSTATE_ES     OFFSET_FCPUSTATE32_ES
#define OFFSET_FCPUSTATE_CS     OFFSET_FCPUSTATE32_CS
#define OFFSET_FCPUSTATE_SS     OFFSET_FCPUSTATE32_SS
#define OFFSET_FCPUSTATE_DS     OFFSET_FCPUSTATE32_DS
#define OFFSET_FCPUSTATE_FS     OFFSET_FCPUSTATE32_FS
#define OFFSET_FCPUSTATE_GS     OFFSET_FCPUSTATE32_GS
#define OFFSET_FCPUSTATE_TR     OFFSET_FCPUSTATE32_TR
#define OFFSET_FCPUSTATE_LDT    OFFSET_FCPUSTATE32_LDT
#define OFFSET_FCPUSTATE_COREGS OFFSET_FCPUSTATE32_COREGS
#define OFFSET_FCPUSTATE_DRREGS OFFSET_FCPUSTATE32_DRREGS
#define OFFSET_FCPUSTATE_GDT    OFFSET_FCPUSTATE32_GDT
#define OFFSET_FCPUSTATE_IDT    OFFSET_FCPUSTATE32_IDT
#define SIZEOF_FCPUSTATE        SIZEOF_FCPUSTATE32
#define FCPUSTATE_TO_UCPUSTATE  FCPUSTATE32_TO_UCPUSTATE32
#define FCPUSTATE_TO_LCPUSTATE  FCPUSTATE32_TO_LCPUSTATE32
#define FCPUSTATE_PC            FCPUSTATE32_PC
#define FCPUSTATE_SP            FCPUSTATE32_SP

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
struct __ATTR_PACKED gpregs32 {
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
struct __ATTR_PACKED sgregs32 {
	__u32   sg_gs;     /* G segment register (Usually `SEGMENT_USER_GSBASE_RPL') */
	__u32   sg_fs;     /* F segment register (Usually `SEGMENT_USER_FSBASE_RPL' / `SEGMENT_KERNEL_FSBASE') */
	__u32   sg_es;     /* E (source) segment register (Usually `SEGMENT_USER_DATA_RPL') */
	__u32   sg_ds;     /* D (destination) segment register (Usually `SEGMENT_USER_DATA_RPL') */
};
#endif /* __CC__ */


#define OFFSET_COREGS32_CR0 0
#define OFFSET_COREGS32_CR2 4
#define OFFSET_COREGS32_CR3 8
#define OFFSET_COREGS32_CR4 12
#define SIZEOF_COREGS32     16
#ifdef __CC__
struct __ATTR_PACKED coregs32 {
	__u32   co_cr0;    /* %cr0 (Set of `CR0_*' from `/include/i386-kos/asm/cpu-flags.h') */
	__u32   co_cr2;    /* %cr2 (Page Fault Linear Address (PFLA) (when a #PF occurs, contains that fault's address)) */
	__u32   co_cr3;    /* %cr3 (Page Directory Linear Address) */
	__u32   co_cr4;    /* %cr4 (Set of `CR4_*' from `/include/i386-kos/asm/cpu-flags.h') */
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
struct __ATTR_PACKED drregs32 {
	__u32   dr_dr0;    /* %dr0 (Linear address of first breakpoint) */
	__u32   dr_dr1;    /* %dr1 (Linear address of second breakpoint) */
	__u32   dr_dr2;    /* %dr2 (Linear address of third breakpoint) */
	__u32   dr_dr3;    /* %dr3 (Linear address of fourth breakpoint) */
	__u32   dr_dr6;    /* %dr6 (Debug status) */
	__u32   dr_dr7;    /* %dr7 (Debug control (set of `DR7_*' from `/include/i386-kos/asm/cpu-flags.h')) */
};
#endif /* __CC__ */



#define OFFSET_IRREGS32_EIP    0
#define OFFSET_IRREGS32_CS     4
#define OFFSET_IRREGS32_EFLAGS 8
#define SIZEOF_IRREGS32_KERNEL 12
#define OFFSET_IRREGS32_ESP    12
#define OFFSET_IRREGS32_SS     16
#define SIZEOF_IRREGS32_USER   20
#define OFFSET_IRREGS32_ES     20
#define OFFSET_IRREGS32_DS     24
#define OFFSET_IRREGS32_FS     28
#define OFFSET_IRREGS32_GS     32
#define SIZEOF_IRREGS32_VM86   36
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
struct __ATTR_PACKED irregs32_kernel {
	__u32   ir_eip;    /* Instruction pointer */
	__u32   ir_cs;     /* Code segment (Ring #0, usually `SEGMENT_KERNEL_CODE') */
	__u32   ir_eflags; /* Flags register */
};
#if defined(__cplusplus) && 0 /* offsetof() in non-POD is undefined... */
struct __ATTR_PACKED irregs32_user: irregs_kernel {
	/* The following fields are popped when `(ir_cs & 3) != CURRENT_RING' */
	__u32   ir_esp;    /* Stack pointer */
	__u32   ir_ss;     /* Stack segment (Ring #3, usually `SEGMENT_USER_DATA_RPL') */
};
struct __ATTR_PACKED irregs32_vm86: irregs_user {
	/* `ir_eflags' has the `EFLAGS_VM' flag set. */
	__u32   ir_es;
	__u32   ir_ds;
	__u32   ir_fs;
	__u32   ir_gs;
};
#else
struct __ATTR_PACKED irregs32_user {
	__u32   ir_eip;    /* Instruction pointer */
	__u32   ir_cs;     /* Code segment (Ring #3, usually `SEGMENT_USER_CODE_RPL') */
	__u32   ir_eflags; /* Flags register */
	/* The following fields are popped when `(ir_cs & 3) != CURRENT_RING' */
	__u32   ir_esp;    /* Stack pointer */
	__u32   ir_ss;     /* Stack segment (Ring #3, usually `SEGMENT_USER_DATA_RPL') */
};
struct __ATTR_PACKED irregs32_vm86 {
	__u32   ir_eip;
	__u32   ir_cs;
	__u32   ir_eflags; /* Has the `EFLAGS_VM' flag set. */
	__u32   ir_esp;
	__u32   ir_ss;
	__u32   ir_es;
	__u32   ir_ds;
	__u32   ir_fs;
	__u32   ir_gs;
};
#endif

#define IRREGS32_ISVM86(x)          ((x).ir_eflags & 0x20000)
#define IRREGS32_ISKERNEL(x)        (!((x).ir_cs & 3) && !IRREGS32_ISVM86(x))
#define IRREGS32_ISUSER(x)          (((x).ir_cs & 3) && !IRREGS32_ISVM86(x))
#define IRREGS32_ISUSER_OR_VM86(x)  (((x).ir_cs & 3) || IRREGS32_ISVM86(x))

#define IRREGS32_USER_ESP(x)        (((struct irregs32_user *)&(x))->ir_esp)
#define IRREGS32_USER_SS(x)         (((struct irregs32_user *)&(x))->ir_ss)
#define IRREGS32_KERNEL_ESP(x)      ((__uintptr_t)((__byte_t *)&(x) + SIZEOF_IRREGS32_KERNEL))
#define IRREGS32_KERNEL_SS(x)         SEGMENT_KERNEL_DATA

#define IRREGS32_PC(x)          ((x).ir_eip)
#define IRREGS32_SP(x)          (IRREGS32_ISUSER_OR_VM86(x) ? IRREGS32_USER_ESP(x) : IRREGS32_KERNEL_ESP(x))
#define IRREGS32_SS(x)          (IRREGS32_ISUSER_OR_VM86(x) ? IRREGS32_USER_SS(x) : IRREGS32_KERNEL_SS(x))
#define IRREGS32_WRSP(x, value) (IRREGS32_ISUSER_OR_VM86(x) ? (IRREGS32_USER_ESP(x) = (value), 1) : (IRREGS32_KERNEL_ESP(x) == (value)))
#define IRREGS32_WRSS(x, value) (IRREGS32_ISUSER_OR_VM86(x) ? (IRREGS32_USER_SS(x) = (value), 1) : (IRREGS32_KERNEL_SS(x) == (value)))

/* Returns the total size of the given CPU state. */
#define IRREGS32_SIZEOF(x)                     \
	(IRREGS32_ISVM86(x) ? SIZEOF_IRREGS32_VM86 \
	 ((x).ir_cs & 3)    ? SIZEOF_IRREGS32_USER \
	                    : SIZEOF_IRREGS32_KERNEL)

#endif /* __CC__ */


#define OFFSET_UCPUSTATE32_GPREGS  0
#define OFFSET_UCPUSTATE32_SGREGS  32
#define OFFSET_UCPUSTATE32_CS      48
#define OFFSET_UCPUSTATE32_SS      52
#define OFFSET_UCPUSTATE32_EFLAGS  56
#define OFFSET_UCPUSTATE32_EIP     60
#define SIZEOF_UCPUSTATE32         64
#ifdef __CC__
struct __ATTR_PACKED ucpustate32 { /* u -- User */
	/* Full CPU state, as used by system calls.
	 * NOTE: Also represents the state saved when an exception occurs,
	 *       both inside kernel-, as well as user-space. */
	struct gpregs32 ucs_gpregs; /* General purpose registers. */
	struct sgregs32 ucs_sgregs; /* Segment registers. */
	__u32           ucs_cs;     /* Code segment (Ring #3, usually `SEGMENT_USER_CODE_RPL') */
	__u32           ucs_ss;     /* Stack segment (Ring #3, usually `SEGMENT_USER_DATA_RPL') */
	__u32           ucs_eflags; /* Flags register */
	__u32           ucs_eip;    /* Instruction pointer */
};

#define UCPUSTATE32_PC(x) ((x).ucs_eip)
#define UCPUSTATE32_SP(x) ((x).ucs_gpregs.gp_esp)

#endif /* __CC__ */

#define OFFSET_LCPUSTATE32_EDI  0
#define OFFSET_LCPUSTATE32_ESI  4
#define OFFSET_LCPUSTATE32_EBP  8
#define OFFSET_LCPUSTATE32_ESP  12
#define OFFSET_LCPUSTATE32_EBX  16
#define OFFSET_LCPUSTATE32_EIP  20
#define SIZEOF_LCPUSTATE32      24
#ifdef __CC__
struct __ATTR_PACKED lcpustate32 { /* l -- Little */
	/* A minimal CPU state containing only registers that are callee-preserved.
	 * This kind of CPU state is most useful for generating tracebacks. */
	__u32         lcs_edi;    /* [P] Destination pointer */
	__u32         lcs_esi;    /* [P] Source pointer */
	__u32         lcs_ebp;    /* [P] Frame base pointer */
	__u32         lcs_esp;    /* [P] Stack pointer */
	__u32         lcs_ebx;    /* [P] Base register */
	__u32         lcs_eip;    /* Instruction pointer */
};

#ifndef __x86_64__
__FORCELOCAL void __FCALL lcpustate_cur(struct lcpustate32 *__restrict __st) {
	__asm__("movl %%edi, %0\n\t"
			"movl %%esi, %1\n\t"
			"movl %%ebp, %2\n\t"
			"movl %%esp, %3\n\t"
			"movl %%ebx, %4\n\t"
#if (defined(__pic__) || defined(__PIC__) || \
     defined(__pie__) || defined(__PIE__)) && 0
			"call 991f\n\t"
			"991: .cfi_adjust_cfa_offset 4\n\t"
			"popl %5\n\t"
			".cfi_adjust_cfa_offset -4"
#else
			"movl $991f, %5\n\t"
			"991:"
#endif
			: "=m" (__st->lcs_edi)
			, "=m" (__st->lcs_esi)
			, "=m" (__st->lcs_ebp)
			, "=m" (__st->lcs_esp)
			, "=m" (__st->lcs_ebx)
			, "=m" (__st->lcs_eip));
}
#endif /* !__x86_64__ */

#define LCPUSTATE32_TO_GPREGS32(dst, src) \
	((dst).gp_edi = (src).lcs_edi,        \
	 (dst).gp_esi = (src).lcs_esi,        \
	 (dst).gp_ebp = (src).lcs_ebp,        \
	 (dst).gp_esp = (src).lcs_esp,        \
	 (dst).gp_ebx = (src).lcs_ebx,        \
	 (dst).gp_edx = 0,                    \
	 (dst).gp_ecx = 0,                    \
	 (dst).gp_eax = 0)
#define LCPUSTATE32_TO_UCPUSTATE32(dst, src)                          \
	(LCPUSTATE32_TO_GPREGS32((dst).ucs_gpregs, src),                  \
	 (dst).ucs_sgregs.sg_gs  = __rdgs(),                              \
	 (dst).ucs_sgregs.sg_fs  = __rdfs(),                              \
	 (dst).ucs_sgregs.sg_es  = __rdes(),                              \
	 (dst).ucs_sgregs.sg_ds  = __rdds(),                              \
	 (dst).ucs_cs            = SEGMENT_CURRENT_CODE_RPL /*__rdcs()*/, \
	 (dst).ucs_ss            = SEGMENT_CURRENT_DATA_RPL /*__rdss()*/, \
	 (dst).ucs_eflags        = (__u32)__rdflags(),                    \
	 (dst).ucs_eip           = (src).lcs_eip)
#define LCPUSTATE32_TO_KCPUSTATE32(dst, src)         \
	(LCPUSTATE32_TO_GPREGS32((dst).kcs_gpregs, src), \
	 (dst).kcs_eflags = (__u32)__rdflags(),          \
	 (dst).kcs_eip    = (src).lcs_eip)

#define LCPUSTATE32_PC(x) ((x).lcs_eip)
#define LCPUSTATE32_SP(x) ((x).lcs_esp)
#endif /* __CC__ */


#define OFFSET_KCPUSTATE32_GPREGS  0
#define OFFSET_KCPUSTATE32_EFLAGS  32
#define OFFSET_KCPUSTATE32_EIP     36
#define SIZEOF_KCPUSTATE32         40
#ifdef __CC__
struct __ATTR_PACKED kcpustate32 {
	/* A CPU state used to describe a known, valid register state in kernel-space.
	 * This kind of state is also used by exception handling, and the associated
	 * stack unwinding. */
	struct gpregs32 kcs_gpregs; /* General purpose registers. */
	__u32           kcs_eflags; /* Flags register */
	__u32           kcs_eip;    /* Instruction pointer */
};

#define KCPUSTATE32_TO_UCPUSTATE32(dst, src)                         \
	((dst).ucs_gpregs       = (src).kcs_gpregs,                      \
	 (dst).ucs_sgregs.sg_gs = __rdgs(),                              \
	 (dst).ucs_sgregs.sg_fs = __rdfs(),                              \
	 (dst).ucs_sgregs.sg_es = __rdes(),                              \
	 (dst).ucs_sgregs.sg_ds = __rdds(),                              \
	 (dst).ucs_cs           = SEGMENT_CURRENT_CODE_RPL /*__rdcs()*/, \
	 (dst).ucs_ss           = SEGMENT_CURRENT_DATA_RPL /*__rdss()*/, \
	 (dst).ucs_eflags       = (src).kcs_eflags,                      \
	 (dst).ucs_eip          = (src).kcs_eip)
#define KCPUSTATE32_TO_LCPUSTATE32(dst, src)  \
	((dst).lcs_edi = (src).kcs_gpregs.gp_edi, \
	 (dst).lcs_esi = (src).kcs_gpregs.gp_esi, \
	 (dst).lcs_ebp = (src).kcs_gpregs.gp_ebp, \
	 (dst).lcs_esp = (src).kcs_gpregs.gp_esp, \
	 (dst).lcs_ebx = (src).kcs_gpregs.gp_ebx, \
	 (dst).lcs_eip = (src).kcs_eip)

#define KCPUSTATE32_PC(x) ((x).kcs_eip)
#define KCPUSTATE32_SP(x) ((x).kcs_gpregs.gp_esp)

#endif /* __CC__ */


#define OFFSET_ICPUSTATE32_GPREGS  0
#define OFFSET_ICPUSTATE32_FS      32
#define OFFSET_ICPUSTATE32_ES      36
#define OFFSET_ICPUSTATE32_DS      40
#define OFFSET_ICPUSTATE32_IRREGS  44
#ifdef __CC__
struct __ATTR_PACKED icpustate32 { /* i -- Interrupts */
	/* A CPU state that is used by hardware interrupts (other than those used
	 * by scheduling, which generate `scpustate' instead), in order to describe
	 * the interrupted text location.
	 * Also the primary CPU state used by RPC handlers.
	 * Because interrupts always lead into kernel-space, and because the kernel
	 * doesn't make use of the %gs register, that register is not saved by this
	 * kind of state, and when required should always be assumed to equal
	 * `SEGMENT_USER_GSBASE_RPL', as is the default expectation for user-space.
	 * Note however that because %gs is not saved, its exact value can therefor
	 * be read using `__rdgs()' (though only in the thread that generated the
	 * `struct icpustate'), as well as the fact that modifications to the %gs
	 * segment selector will not be undone when an `struct icpustate' is loaded. */
	struct gpregs32    ics_gpregs; /* General purpose registers. */
	__u32              ics_fs;     /* F segment register (Usually `SEGMENT_USER_FSBASE_RPL' / `SEGMENT_KERNEL_FSBASE') */
	__u32              ics_es;     /* E (source) segment register (Usually `SEGMENT_USER_DATA_RPL') */
	__u32              ics_ds;     /* D (destination) segment register (Usually `SEGMENT_USER_DATA_RPL') */
	union __ATTR_PACKED {
		/* Interrupt return registers.
		 * NOTE: When returning to user-space, the ESP inside
		 *       of this structure is the user-space EPS.
		 *       Otherwise, the return-ESP is equal to the
		 *       address of `ir_esp' (Use `ICPUSTATE_SP')
		 * NOTE: Since the size of this structure depends on one
		 *       of its fields, use `ICPUSTATE_SIZEOF()'
		 *       to determine it. */
		struct irregs32_kernel ics_irregs;
		struct irregs32_kernel ics_irregs_k;
		struct irregs32_user   ics_irregs_u;
		struct irregs32_vm86   ics_irregs_v;
	};
};

/* Convert the given `struct icpustate32 &src' to a `struct ucpustate32 &dst' */
#define ICPUSTATE32_TO_UCPUSTATE32(dst, src)                        \
	((dst).ucs_gpregs = (src).ics_gpregs,                           \
	 (dst).ucs_eip    = (src).ics_irregs_k.ir_eip,                  \
	 (dst).ucs_eflags = (src).ics_irregs_k.ir_eflags,               \
	 (dst).ucs_cs     = (src).ics_irregs_k.ir_cs,                   \
	 ICPUSTATE32_ISVM86(src)                                        \
	 ? ((dst).ucs_gpregs.gp_esp = (src).ics_irregs_v.ir_esp,        \
	    (dst).ucs_ss            = (src).ics_irregs_v.ir_ss,         \
	    (dst).ucs_sgregs.sg_ds  = (src).ics_irregs_v.ir_ds,         \
	    (dst).ucs_sgregs.sg_es  = (src).ics_irregs_v.ir_es,         \
	    (dst).ucs_sgregs.sg_fs  = (src).ics_irregs_v.ir_fs,         \
	    (dst).ucs_sgregs.sg_gs  = (src).ics_irregs_v.ir_gs)         \
	 : ((dst).ucs_sgregs.sg_ds = (src).ics_ds,                      \
	    (dst).ucs_sgregs.sg_es = (src).ics_es,                      \
	    (dst).ucs_sgregs.sg_fs = (src).ics_fs,                      \
	    (dst).ucs_sgregs.sg_gs = __rdgs(),                          \
	    ((src).ics_irregs_k.ir_cs & 3)                              \
	    ? ((dst).ucs_ss            = ICPUSTATE32_USER_SS(src),      \
	       (dst).ucs_gpregs.gp_esp = ICPUSTATE32_USER_ESP(src))     \
	    : ((dst).ucs_ss            = ICPUSTATE32_KERNEL_SS(src),    \
	       (dst).ucs_gpregs.gp_esp = ICPUSTATE32_KERNEL_ESP(src))), \
	 (void)0)

#define ICPUSTATE32_ISVM86(x)          ((x).ics_irregs_k.ir_eflags & 0x20000)
#define ICPUSTATE32_ISKERNEL(x)        (!((x).ics_irregs_k.ir_cs & 3) && !ICPUSTATE32_ISVM86(x))
#define ICPUSTATE32_ISUSER(x)          (((x).ics_irregs_k.ir_cs & 3) && !ICPUSTATE32_ISVM86(x))
#define ICPUSTATE32_ISUSER_OR_VM86(x)  (((x).ics_irregs_k.ir_cs & 3) || ICPUSTATE32_ISVM86(x))

#define ICPUSTATE32_USER_ESP(x)   ((x).ics_irregs_u.ir_esp)
#define ICPUSTATE32_KERNEL_ESP(x) ((__uintptr_t)(&(x).ics_irregs_k + 1))
#define ICPUSTATE32_USER_SS(x)    ((x).ics_irregs_u.ir_ss)
#define ICPUSTATE32_KERNEL_SS(x)    SEGMENT_KERNEL_DATA

#define ICPUSTATE32_PC(x)         ((x).ics_irregs_k.ir_eip)

/* Get/set the values of segment registers (these setters won't fail)
 * Macros are required for these, because of special handling required for vm86 support */
#define ICPUSTATE32_DS(x)          (ICPUSTATE32_ISVM86(x) ? (x).ics_irregs_v.ir_ds : (x).ics_ds)
#define ICPUSTATE32_ES(x)          (ICPUSTATE32_ISVM86(x) ? (x).ics_irregs_v.ir_es : (x).ics_es)
#define ICPUSTATE32_FS(x)          (ICPUSTATE32_ISVM86(x) ? (x).ics_irregs_v.ir_fs : (x).ics_fs)
#define ICPUSTATE32_GS(x)          (ICPUSTATE32_ISVM86(x) ? (x).ics_irregs_v.ir_gs : __rdgs())
#define ICPUSTATE32_WRDS(x, value) (ICPUSTATE32_ISVM86(x) ? (void)((x).ics_irregs_v.ir_ds = (value)) : (void)((x).ics_ds = (value)))
#define ICPUSTATE32_WRES(x, value) (ICPUSTATE32_ISVM86(x) ? (void)((x).ics_irregs_v.ir_es = (value)) : (void)((x).ics_es = (value)))
#define ICPUSTATE32_WRFS(x, value) (ICPUSTATE32_ISVM86(x) ? (void)((x).ics_irregs_v.ir_fs = (value)) : (void)((x).ics_fs = (value)))
#define ICPUSTATE32_WRGS(x, value) (ICPUSTATE32_ISVM86(x) ? (void)((x).ics_irregs_v.ir_gs = (value)) : __wrgs(value))

/* Return the values of conditionally restored registers, as
 * they will appear when the cpu state is restored. */
#define ICPUSTATE32_SP(x)         (ICPUSTATE32_ISUSER_OR_VM86(x) ? ICPUSTATE32_USER_ESP(x) : ICPUSTATE32_KERNEL_ESP(x))
#define ICPUSTATE32_SS(x)         (ICPUSTATE32_ISUSER_OR_VM86(x) ? ICPUSTATE32_USER_SS(x) : ICPUSTATE32_KERNEL_SS(x))

/* Set values of conditionally restored registers.
 * @return: 1: The given `value' will be stored.
 * @return: 0: Failed to modify the state such that `value' will be restored. */
#define ICPUSTATE32_WRSP(x, value) (ICPUSTATE32_ISUSER_OR_VM86(x) ? ((x).ics_irregs_u.ir_esp = (value),1) : (ICPUSTATE32_KERNEL_ESP(x) == (value)))
#define ICPUSTATE32_WRSS(x, value) (ICPUSTATE32_ISUSER_OR_VM86(x) ? ((x).ics_irregs_u.ir_ss = (value),1) : (ICPUSTATE32_KERNEL_SS(x) == (value)))

/* Returns the total size of the given CPU state. */
#define ICPUSTATE32_SIZEOF(x) \
	(((x).ics_irregs_k.ir_eflags & 0x20000) ? (SIZEOF_GPREGS32+12+SIZEOF_IRREGS32_VM86) \
	 ((x).ics_irregs_k.ir_cs & 3)           ? (SIZEOF_GPREGS32+12+SIZEOF_IRREGS32_USER) \
	                                        : (SIZEOF_GPREGS32+12+SIZEOF_IRREGS32_KERNEL))
#endif /* __CC__ */


#define OFFSET_SCPUSTATE32_GPREGS  0
#define OFFSET_SCPUSTATE32_SGREGS  32
#define OFFSET_SCPUSTATE32_IRREGS  48
#ifdef __CC__
struct __ATTR_PACKED scpustate32 { /* s -- Scheduling */
	/* CPU state, as used to store the state of a thread that isn't currently running. */
	struct gpregs32    scs_gpregs; /* General purpose registers. */
	struct sgregs32    scs_sgregs; /* Segment registers. */
	union __ATTR_PACKED {
		/* Interrupt return registers.
		 * NOTE: When returning to user-space, the ESP inside
		 *       of this structure is the user-space EPS.
		 *       Otherwise, the return-ESP is equal to the
		 *       address of `ir_esp' (Use `SCPUSTATE_SP')
		 * NOTE: Since the size of this structure depends on one
		 *       of its fields, use `SCPUSTATE_SIZEOF()'
		 *       to determine it. */
		struct irregs32_kernel scs_irregs;
		struct irregs32_kernel scs_irregs_k;
		struct irregs32_user   scs_irregs_u;
		struct irregs32_vm86   scs_irregs_v;
	};
};

/* Convert the given `struct scpustate32 &src' to a `struct ucpustate32 &dst' */
#define SCPUSTATE32_TO_UCPUSTATE32(dst, src)                        \
	((dst).ucs_gpregs = (src).scs_gpregs,                           \
	 (dst).ucs_eip    = (src).scs_irregs_k.ir_eip,                  \
	 (dst).ucs_eflags = (src).scs_irregs_k.ir_eflags,               \
	 (dst).ucs_cs     = (src).scs_irregs_k.ir_cs,                   \
	 SCPUSTATE32_ISVM86(src)                                        \
	 ? ((dst).ucs_gpregs.gp_esp = (src).scs_irregs_v.ir_esp,        \
	    (dst).ucs_ss            = (src).scs_irregs_v.ir_ss,         \
	    (dst).ucs_sgregs.sg_ds  = (src).scs_irregs_v.ir_ds,         \
	    (dst).ucs_sgregs.sg_es  = (src).scs_irregs_v.ir_es,         \
	    (dst).ucs_sgregs.sg_fs  = (src).scs_irregs_v.ir_fs,         \
	    (dst).ucs_sgregs.sg_gs  = (src).scs_irregs_v.ir_gs)         \
	 : ((dst).ucs_sgregs = (src).scs_sgregs,                        \
	    ((src).scs_irregs_k.ir_cs & 3)                              \
	    ? ((dst).ucs_ss            = SCPUSTATE32_USER_SS(src),      \
	       (dst).ucs_gpregs.gp_esp = SCPUSTATE32_USER_ESP(src))     \
	    : ((dst).ucs_ss            = SCPUSTATE32_KERNEL_SS(src),    \
	       (dst).ucs_gpregs.gp_esp = SCPUSTATE32_KERNEL_ESP(src))), \
	 (void)0)
//	struct coregs32  fcs_coregs; /* Control registers. */
//	struct drregs32  fcs_drregs; /* Debug registers. */
//	__u16          __fcs_pad0;   /* ... */
//	struct desctab32 fcs_gdt;    /* Global descriptor table. */
//	__u16          __fcs_pad1;   /* ... */
//	struct desctab32 fcs_idt;    /* Interrupt descriptor table. */

#define SCPUSTATE32_ISVM86(x)          ((x).scs_irregs_k.ir_eflags & 0x20000)
#define SCPUSTATE32_ISKERNEL(x)        (!((x).scs_irregs_k.ir_cs & 3) && !SCPUSTATE32_ISVM86(x))
#define SCPUSTATE32_ISUSER(x)          (((x).scs_irregs_k.ir_cs & 3) && !SCPUSTATE32_ISVM86(x))
#define SCPUSTATE32_ISUSER_OR_VM86(x)  (((x).scs_irregs_k.ir_cs & 3) || SCPUSTATE32_ISVM86(x))

#define SCPUSTATE32_USER_ESP(x)   ((x).scs_irregs_u.ir_esp)
#define SCPUSTATE32_KERNEL_ESP(x) ((__uintptr_t)(&(x).scs_irregs_k + 1))
#define SCPUSTATE32_USER_SS(x)    ((x).scs_irregs_u.ir_ss)
#define SCPUSTATE32_KERNEL_SS(x)    SEGMENT_KERNEL_DATA

#define SCPUSTATE32_PC(x)         ((x).scs_irregs_k.ir_eip)

/* Get/set the values of segment registers (these setters won't fail)
 * Macros are required for these, because of special handling required for vm86 support */
#define SCPUSTATE32_DS(x)         (SCPUSTATE32_ISVM86(x) ? (x).scs_irregs_v.ir_ds : (x).scs_sgregs.sg_ds)
#define SCPUSTATE32_ES(x)         (SCPUSTATE32_ISVM86(x) ? (x).scs_irregs_v.ir_es : (x).scs_sgregs.sg_es)
#define SCPUSTATE32_FS(x)         (SCPUSTATE32_ISVM86(x) ? (x).scs_irregs_v.ir_fs : (x).scs_sgregs.sg_fs)
#define SCPUSTATE32_GS(x)         (SCPUSTATE32_ISVM86(x) ? (x).scs_irregs_v.ir_gs : (x).scs_sgregs.sg_gs)
#define SCPUSTATE32_WRDS(x,value) (SCPUSTATE32_ISVM86(x) ? (void)((x).scs_irregs_v.ir_ds = (value)) : (void)((x).scs_sgregs.sg_ds = (value)))
#define SCPUSTATE32_WRES(x,value) (SCPUSTATE32_ISVM86(x) ? (void)((x).scs_irregs_v.ir_es = (value)) : (void)((x).scs_sgregs.sg_es = (value)))
#define SCPUSTATE32_WRFS(x,value) (SCPUSTATE32_ISVM86(x) ? (void)((x).scs_irregs_v.ir_fs = (value)) : (void)((x).scs_sgregs.sg_fs = (value)))
#define SCPUSTATE32_WRGS(x,value) (SCPUSTATE32_ISVM86(x) ? (void)((x).scs_irregs_v.ir_gs = (value)) : (void)((x).scs_sgregs.sg_gs = (value)))

/* Return the values of conditionally restored registers, as
 * they will appear when the cpu state is restored. */
#define SCPUSTATE32_SP(x)         (SCPUSTATE32_ISUSER_OR_VM86(x) ? SCPUSTATE32_USER_ESP(x) : SCPUSTATE32_KERNEL_ESP(x))
#define SCPUSTATE32_SS(x)         (SCPUSTATE32_ISUSER_OR_VM86(x) ? SCPUSTATE32_USER_SS(x) : SCPUSTATE32_KERNEL_SS(x))

/* Set values of conditionally restored registers.
 * @return: 1: The given `value' will be stored.
 * @return: 0: Failed to modify the state such that `value' will be restored. */
#define SCPUSTATE32_WRSP(x, value) (SCPUSTATE32_ISUSER_OR_VM86(x) ? ((x).scs_irregs_u.ir_esp = (value), 1) : (SCPUSTATE32_KERNEL_ESP(x) == (value)))
#define SCPUSTATE32_WRSS(x, value) (SCPUSTATE32_ISUSER_OR_VM86(x) ? ((x).scs_irregs_u.ir_ss = (value), 1) : (SCPUSTATE32_KERNEL_SS(x) == (value)))

/* Returns the total size of the given CPU state. */
#define SCPUSTATE32_SIZEOF(x) \
	(((x).scs_irregs_k.ir_eflags & 0x20000) ? (SIZEOF_GPREGS32+SIZEOF_SGREGS32+SIZEOF_IRREGS32_VM86) : \
	 ((x).scs_irregs_k.ir_cs & 3)           ? (SIZEOF_GPREGS32+SIZEOF_SGREGS32+SIZEOF_IRREGS32_USER) : \
	                                          (SIZEOF_GPREGS32+SIZEOF_SGREGS32+SIZEOF_IRREGS32_KERNEL))
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
struct __ATTR_PACKED fcpustate32 { /* f -- Full */
	/* Full CPU state (including _all_ registers that exist). */
	struct gpregs32  fcs_gpregs; /* General purpose registers. */
	__u32            fcs_eflags; /* Flags register */
	__u32            fcs_eip;    /* Flags register */
	struct {
		__u32        sg_es;      /* E (source) segment register. */
		__u32        sg_cs;      /* Code segment register. */
		__u32        sg_ss;      /* Stack segment register. */
		__u32        sg_ds;      /* D (destination) segment register. */
		__u32        sg_fs;      /* F segment register. */
		__u32        sg_gs;      /* G segment register. */
		__u32        sg_tr;      /* Task register. */
		__u32        sg_ldt;     /* Load descriptor table. */
	}                fcs_sgregs; /* Segment registers. */
	struct coregs32  fcs_coregs; /* Control registers. */
	struct drregs32  fcs_drregs; /* Debug registers. */
	__u16          __fcs_pad0;   /* ... */
	struct desctab32 fcs_gdt;    /* Global descriptor table. */
	__u16          __fcs_pad1;   /* ... */
	struct desctab32 fcs_idt;    /* Interrupt descriptor table. */
};

#define FCPUSTATE32_TO_UCPUSTATE32(dst, src)          \
	((dst).ucs_gpregs       = (src).fcs_gpregs,       \
	 (dst).ucs_sgregs.sg_gs = (src).fcs_sgregs.sg_gs, \
	 (dst).ucs_sgregs.sg_fs = (src).fcs_sgregs.sg_fs, \
	 (dst).ucs_sgregs.sg_es = (src).fcs_sgregs.sg_es, \
	 (dst).ucs_sgregs.sg_ds = (src).fcs_sgregs.sg_ds, \
	 (dst).ucs_cs           = (src).fcs_sgregs.sg_cs, \
	 (dst).ucs_ss           = (src).fcs_sgregs.sg_ss, \
	 (dst).ucs_eflags       = (src).fcs_eflags,       \
	 (dst).ucs_eip          = (src).fcs_eip)
#define FCPUSTATE32_TO_LCPUSTATE32(dst, src)  \
	((dst).lcs_edi = (src).fcs_gpregs.gp_edi, \
	 (dst).lcs_esi = (src).fcs_gpregs.gp_esi, \
	 (dst).lcs_ebp = (src).fcs_gpregs.gp_ebp, \
	 (dst).lcs_esp = (src).fcs_gpregs.gp_esp, \
	 (dst).lcs_ebx = (src).fcs_gpregs.gp_ebx, \
	 (dst).lcs_eip = (src).fcs_eip)
#define FCPUSTATE32_PC(x) ((x).fcs_eip)
#define FCPUSTATE32_SP(x) ((x).fcs_gpregs.gp_esp)

#endif /* __CC__ */

__SYSDECL_END

#endif /* !_I386_KOS_KOS_KERNEL_CPU_STATE32_H */
