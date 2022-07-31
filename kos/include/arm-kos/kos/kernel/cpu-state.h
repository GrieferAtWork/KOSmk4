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

struct fcpustate { /* f -- Full */
	struct ucpustate scs_ustate;
	/* TODO: Other registers? */
};

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_ARM_KOS_KOS_KERNEL_CPU_STATE_H */
