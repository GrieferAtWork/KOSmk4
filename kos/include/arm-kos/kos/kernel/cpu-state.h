/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _ARM_KOS_KOS_KERNEL_CPU_STATE_H
#define _ARM_KOS_KOS_KERNEL_CPU_STATE_H 1

#include <__stdinc.h>

#include <bits/types.h>


#define OFFSET_UCPUSTATE_R0   0  /* r0 */
#define OFFSET_UCPUSTATE_R1   4  /* r1 */
#define OFFSET_UCPUSTATE_R2   8  /* r2 */
#define OFFSET_UCPUSTATE_R3   12 /* r3 */
#define OFFSET_UCPUSTATE_R4   16 /* r4 */
#define OFFSET_UCPUSTATE_R5   20 /* r5 */
#define OFFSET_UCPUSTATE_R6   24 /* r6 */
#define OFFSET_UCPUSTATE_R7   28 /* r7 */
#define OFFSET_UCPUSTATE_R8   32 /* r8 */
#define OFFSET_UCPUSTATE_R9   36 /* r9 */
#define OFFSET_UCPUSTATE_R10  40 /* r10 */
#define OFFSET_UCPUSTATE_R11  44 /* r11 */
#define OFFSET_UCPUSTATE_R12  48 /* r12 */
#define OFFSET_UCPUSTATE_SP   52 /* r13 */
#define OFFSET_UCPUSTATE_LR   56 /* r14 */
#define OFFSET_UCPUSTATE_PC   60 /* r15 */
#define OFFSET_UCPUSTATE_CPSR 64 /* CurrentProgramStatusRegister */
#define SIZEOF_UCPUSTATE      68
#define ALIGNOF_UCPUSTATE     4

#define OFFSET_LCPUSTATE_R4  0  /* r4 */
#define OFFSET_LCPUSTATE_R5  4  /* r5 */
#define OFFSET_LCPUSTATE_R6  8  /* r6 */
#define OFFSET_LCPUSTATE_R7  12 /* r7 */
#define OFFSET_LCPUSTATE_R8  16 /* r8 */
#define OFFSET_LCPUSTATE_R9  20 /* r9 */
#define OFFSET_LCPUSTATE_R10 24 /* r10 */
#define OFFSET_LCPUSTATE_R11 28 /* r11 */
#define OFFSET_LCPUSTATE_SP  32 /* r13 */
#define OFFSET_LCPUSTATE_LR  36 /* r14 */
#define OFFSET_LCPUSTATE_PC  40 /* r15 */
#define SIZEOF_LCPUSTATE     44
#define ALIGNOF_LCPUSTATE    4

#define OFFSET_KCPUSTATE_R0   OFFSET_UCPUSTATE_R0   /* r0 */
#define OFFSET_KCPUSTATE_R1   OFFSET_UCPUSTATE_R1   /* r1 */
#define OFFSET_KCPUSTATE_R2   OFFSET_UCPUSTATE_R2   /* r2 */
#define OFFSET_KCPUSTATE_R3   OFFSET_UCPUSTATE_R3   /* r3 */
#define OFFSET_KCPUSTATE_R4   OFFSET_UCPUSTATE_R4   /* r4 */
#define OFFSET_KCPUSTATE_R5   OFFSET_UCPUSTATE_R5   /* r5 */
#define OFFSET_KCPUSTATE_R6   OFFSET_UCPUSTATE_R6   /* r6 */
#define OFFSET_KCPUSTATE_R7   OFFSET_UCPUSTATE_R7   /* r7 */
#define OFFSET_KCPUSTATE_R8   OFFSET_UCPUSTATE_R8   /* r8 */
#define OFFSET_KCPUSTATE_R9   OFFSET_UCPUSTATE_R9   /* r9 */
#define OFFSET_KCPUSTATE_R10  OFFSET_UCPUSTATE_R10  /* r10 */
#define OFFSET_KCPUSTATE_R11  OFFSET_UCPUSTATE_R11  /* r11 */
#define OFFSET_KCPUSTATE_R12  OFFSET_UCPUSTATE_R12  /* r12 */
#define OFFSET_KCPUSTATE_SP   OFFSET_UCPUSTATE_SP   /* r13 */
#define OFFSET_KCPUSTATE_LR   OFFSET_UCPUSTATE_LR   /* r14 */
#define OFFSET_KCPUSTATE_PC   OFFSET_UCPUSTATE_PC   /* r15 */
#define OFFSET_KCPUSTATE_CPSR OFFSET_UCPUSTATE_CPSR /* CurrentProgramStatusRegister */
#define SIZEOF_KCPUSTATE      SIZEOF_UCPUSTATE
#define ALIGNOF_KCPUSTATE     ALIGNOF_UCPUSTATE

#define OFFSET_ICPUSTATE_R0   OFFSET_UCPUSTATE_R0   /* r0 */
#define OFFSET_ICPUSTATE_R1   OFFSET_UCPUSTATE_R1   /* r1 */
#define OFFSET_ICPUSTATE_R2   OFFSET_UCPUSTATE_R2   /* r2 */
#define OFFSET_ICPUSTATE_R3   OFFSET_UCPUSTATE_R3   /* r3 */
#define OFFSET_ICPUSTATE_R4   OFFSET_UCPUSTATE_R4   /* r4 */
#define OFFSET_ICPUSTATE_R5   OFFSET_UCPUSTATE_R5   /* r5 */
#define OFFSET_ICPUSTATE_R6   OFFSET_UCPUSTATE_R6   /* r6 */
#define OFFSET_ICPUSTATE_R7   OFFSET_UCPUSTATE_R7   /* r7 */
#define OFFSET_ICPUSTATE_R8   OFFSET_UCPUSTATE_R8   /* r8 */
#define OFFSET_ICPUSTATE_R9   OFFSET_UCPUSTATE_R9   /* r9 */
#define OFFSET_ICPUSTATE_R10  OFFSET_UCPUSTATE_R10  /* r10 */
#define OFFSET_ICPUSTATE_R11  OFFSET_UCPUSTATE_R11  /* r11 */
#define OFFSET_ICPUSTATE_R12  OFFSET_UCPUSTATE_R12  /* r12 */
#define OFFSET_ICPUSTATE_SP   OFFSET_UCPUSTATE_SP   /* r13 */
#define OFFSET_ICPUSTATE_LR   OFFSET_UCPUSTATE_LR   /* r14 */
#define OFFSET_ICPUSTATE_PC   OFFSET_UCPUSTATE_PC   /* r15 */
#define OFFSET_ICPUSTATE_CPSR OFFSET_UCPUSTATE_CPSR /* CurrentProgramStatusRegister */
#define SIZEOF_ICPUSTATE      SIZEOF_UCPUSTATE
#define ALIGNOF_ICPUSTATE     ALIGNOF_UCPUSTATE

#define OFFSET_SCPUSTATE_R0   OFFSET_UCPUSTATE_R0   /* r0 */
#define OFFSET_SCPUSTATE_R1   OFFSET_UCPUSTATE_R1   /* r1 */
#define OFFSET_SCPUSTATE_R2   OFFSET_UCPUSTATE_R2   /* r2 */
#define OFFSET_SCPUSTATE_R3   OFFSET_UCPUSTATE_R3   /* r3 */
#define OFFSET_SCPUSTATE_R4   OFFSET_UCPUSTATE_R4   /* r4 */
#define OFFSET_SCPUSTATE_R5   OFFSET_UCPUSTATE_R5   /* r5 */
#define OFFSET_SCPUSTATE_R6   OFFSET_UCPUSTATE_R6   /* r6 */
#define OFFSET_SCPUSTATE_R7   OFFSET_UCPUSTATE_R7   /* r7 */
#define OFFSET_SCPUSTATE_R8   OFFSET_UCPUSTATE_R8   /* r8 */
#define OFFSET_SCPUSTATE_R9   OFFSET_UCPUSTATE_R9   /* r9 */
#define OFFSET_SCPUSTATE_R10  OFFSET_UCPUSTATE_R10  /* r10 */
#define OFFSET_SCPUSTATE_R11  OFFSET_UCPUSTATE_R11  /* r11 */
#define OFFSET_SCPUSTATE_R12  OFFSET_UCPUSTATE_R12  /* r12 */
#define OFFSET_SCPUSTATE_SP   OFFSET_UCPUSTATE_SP   /* r13 */
#define OFFSET_SCPUSTATE_LR   OFFSET_UCPUSTATE_LR   /* r14 */
#define OFFSET_SCPUSTATE_PC   OFFSET_UCPUSTATE_PC   /* r15 */
#define OFFSET_SCPUSTATE_CPSR OFFSET_UCPUSTATE_CPSR /* CurrentProgramStatusRegister */
#define SIZEOF_SCPUSTATE      SIZEOF_UCPUSTATE
#define ALIGNOF_SCPUSTATE     ALIGNOF_UCPUSTATE

/* Define struct aliases */
#define KCPUSTATE_IS_UCPUSTATE
#define ICPUSTATE_IS_UCPUSTATE
#define SCPUSTATE_IS_UCPUSTATE

#ifdef __CC__
__SYSDECL_BEGIN

struct ucpustate { /* u -- User */
	__uint32_t ucs_r0;   /* r0 */
	__uint32_t ucs_r1;   /* r1 */
	__uint32_t ucs_r2;   /* r2 */
	__uint32_t ucs_r3;   /* r3 */
	__uint32_t ucs_r4;   /* r4 */
	__uint32_t ucs_r5;   /* r5 */
	__uint32_t ucs_r6;   /* r6 */
	__uint32_t ucs_r7;   /* r7 */
	__uint32_t ucs_r8;   /* r8 */
	__uint32_t ucs_r9;   /* r9 */
	__uint32_t ucs_r10;  /* r10 */
	__uint32_t ucs_r11;  /* r11 */
	__uint32_t ucs_r12;  /* r12 */
	__uint32_t ucs_sp;   /* r13 */
	__uint32_t ucs_lr;   /* r14 */
	__uint32_t ucs_pc;   /* r15 */
	__uint32_t ucs_cpsr; /* CurrentProgramStatusRegister */
};

struct lcpustate { /* l -- Little */
	__uint32_t lcs_r4;  /* r4 */
	__uint32_t lcs_r5;  /* r5 */
	__uint32_t lcs_r6;  /* r6 */
	__uint32_t lcs_r7;  /* r7 */
	__uint32_t lcs_r8;  /* r8 */
	__uint32_t lcs_r9;  /* r9 */
	__uint32_t lcs_r10; /* r10 */
	__uint32_t lcs_r11; /* r11 */
	__uint32_t lcs_sp;  /* r13 */
	__uint32_t lcs_lr;  /* r14 */
	__uint32_t lcs_pc;  /* r15 */
};

#define kcpustate ucpustate /* k -- kernel */
#define icpustate ucpustate /* i -- Interrupts */
#define scpustate ucpustate /* s -- Scheduling */


/* NOTE: Banked registers described here are based on the description from:
 *
 * file:    "DDI0406B_arm_architecture_reference_manual.pdf"
 * section: "B1.3.2    ARM core registers"
 * title:   "Figure B1-1 Organization of general-purpose registers and Program Status Registers"
 */
struct fcpustate { /* f -- Full */
	struct ucpustate fcs_usr;      /* User-mode register state (r{0-15}_usr + CPSR)
	                                * NOTE: _ONLY_ the described register state when
	                                * `(fcs_usr.ucs_cpsr & CPSR_M) == CPSR_M_USR' */

	/* Banked registers: FIQ */
	__uint32_t       fcs_R8_fiq;   /* banked R8-register used instead of `fcs_usr.ucs_r8' in FIQ-mode */
	__uint32_t       fcs_R9_fiq;   /* banked R9-register used instead of `fcs_usr.ucs_r9' in FIQ-mode */
	__uint32_t       fcs_R10_fiq;  /* banked R10-register used instead of `fcs_usr.ucs_r10' in FIQ-mode */
	__uint32_t       fcs_R11_fiq;  /* banked R11-register used instead of `fcs_usr.ucs_r11' in FIQ-mode */
	__uint32_t       fcs_R12_fiq;  /* banked R12-register used instead of `fcs_usr.ucs_r12' in FIQ-mode */
	__uint32_t       fcs_SP_fiq;   /* banked SP-register used instead of `fcs_usr.ucs_sp' in FIQ-mode */
	__uint32_t       fcs_LR_fiq;   /* banked LR-register used instead of `fcs_usr.ucs_lr' in FIQ-mode */
	__uint32_t       fcs_SPSR_fiq; /* SPSR for FIQ-mode (old CPSR upon mode-entry) */

	/* Banked registers: IRQ */
	__uint32_t       fcs_SP_irq;   /* banked SP-register used instead of `fcs_usr.ucs_sp' in IRQ-mode */
	__uint32_t       fcs_LR_irq;   /* banked LR-register used instead of `fcs_usr.ucs_lr' in IRQ-mode */
	__uint32_t       fcs_SPSR_irq; /* SPSR for IRQ-mode (old CPSR upon mode-entry) */

	/* Banked registers: SVC */
	__uint32_t       fcs_SP_svc;   /* banked SP-register used instead of `fcs_usr.ucs_sp' in SVC-mode */
	__uint32_t       fcs_LR_svc;   /* banked LR-register used instead of `fcs_usr.ucs_lr' in SVC-mode */
	__uint32_t       fcs_SPSR_svc; /* SPSR for SVC-mode (old CPSR upon mode-entry) */

	/* Banked registers: ABT */
	__uint32_t       fcs_SP_abt;   /* banked SP-register used instead of `fcs_usr.ucs_sp' in ABT-mode */
	__uint32_t       fcs_LR_abt;   /* banked LR-register used instead of `fcs_usr.ucs_lr' in ABT-mode */
	__uint32_t       fcs_SPSR_abt; /* SPSR for ABT-mode (old CPSR upon mode-entry) */

	/* Banked registers: UND */
	__uint32_t       fcs_SP_und;   /* banked SP-register used instead of `fcs_usr.ucs_sp' in UND-mode */
	__uint32_t       fcs_LR_und;   /* banked LR-register used instead of `fcs_usr.ucs_lr' in UND-mode */
	__uint32_t       fcs_SPSR_und; /* SPSR for UND-mode (old CPSR upon mode-entry) */
};

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_ARM_KOS_KOS_KERNEL_CPU_STATE_H */
