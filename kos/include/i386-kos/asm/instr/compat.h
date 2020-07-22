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
#ifndef _I386_KOS_ASM_INSTR_COMPAT_H
#define _I386_KOS_ASM_INSTR_COMPAT_H 1

#include <__stdinc.h>
#include <hybrid/host.h>

#ifdef __ASSEMBLER__

/* Pointer-sized instruction/register aliases */
#ifdef __x86_64__

/* Registers */
#define Pax    rax    /* [C] Accumulator register */
#define Pcx    rcx    /* [C] Count register */
#define Pdx    rdx    /* [C] Data register */
#define Pbx    rbx    /* [P] Base register */
#define Psp    rsp    /* [P] Stack pointer */
#define Pbp    rbp    /* [P] Frame base pointer */
#define Psi    rsi    /* [C] Source pointer */
#define Pdi    rdi    /* [C] Destination pointer */
#define Pip    rip    /* Instruction pointer */
#define Pflags rflags /* Flags register */

/* First argument for FCALL functions */
#define R_fcall0b dil
#define R_fcall0w di
#define R_fcall0l edi
#define R_fcall0q rdi
#define R_fcall0P rdi

/* Second argument for FCALL functions */
#define R_fcall1b sil
#define R_fcall1w si
#define R_fcall1l esi
#define R_fcall1q rsi
#define R_fcall1P rsi

/* Instructions */
#define movsbP       movsbq
#define movswP       movswq
#define movslP       movslq
#ifdef _I386_KOS_ASM_INSTR_MOVZXQ_H
#define movzbP       movzbq
#define movzwP       movzwq
#define movzlP       movzlq
#endif /* _I386_KOS_ASM_INSTR_MOVZXQ_H */
#define movP         movq
#define addP         addq
#define orP          orq
#define adcP         adcq
#define sbbP         sbbq
#define subP         subq
#define andP         andq
#define subP         subq
#define xorP         xorq
#define cmpP         cmpq
#define negP         negq
#define testP        testq
#define pushP        pushq
#define pushP_cfi    pushq_cfi
#define pushP_cfi_r  pushq_cfi_r
#define pushfP       pushfq
#define pushfP_cfi   pushfq_cfi
#define pushfP_cfi_r pushfq_cfi_r
#define popP         popq
#define popP_cfi     popq_cfi
#define popP_cfi_r   popq_cfi_r
#define popfP        popfq
#define popfP_cfi    popfq_cfi
#define popfP_cfi_r  popfq_cfi_r
#define jmpP         jmpq
#define callP        callq
#define leaP         leaq
#define incP         incq
#define decP         decq
#define lidtP        lidtq
#define sidtP        sidtq
#define lgdtP        lgdtq
#define sgdtP        sgdtq
#define xchgP        xchgq
#define stosP        stosq
#define lodsP        lodsq
#define cmpsP        cmpsq
#define movsP        movsq
#define scasP        scasq
#define notP         notq

#ifdef __KERNEL__
#define segtls gs /* THIS_TASK */
#else /* __KERNEL__ */
#define segtls fs /* user-space TLS (as set-up by libdl.so) */
#endif /* !__KERNEL__ */


#else /* __x86_64__ */

/* Registers */
#define Pax    eax    /* [C] Accumulator register */
#define Pcx    ecx    /* [C] Count register */
#define Pdx    edx    /* [C] Data register */
#define Pbx    ebx    /* [P] Base register */
#define Psp    esp    /* [P] Stack pointer */
#define Pbp    ebp    /* [P] Frame base pointer */
#define Psi    esi    /* [P] Source pointer */
#define Pdi    edi    /* [P] Destination pointer */
#define Pip    eip    /* Instruction pointer */
#define Pflags eflags /* Flags register */

/* First argument for FCALL functions */
#define R_fcall0b cl
#define R_fcall0w cx
#define R_fcall0l ecx
#define R_fcall0P ecx

/* Second argument for FCALL functions */
#define R_fcall1b dl
#define R_fcall1w dx
#define R_fcall1l edx
#define R_fcall1P edx

/* Instructions */
#define movzbP       movzbl
#define movzwP       movzwl
#define movzlP       movl
#define movsbP       movsbl
#define movswP       movswl
#define movslP       movl
#define movP         movl
#define addP         addl
#define orP          orl
#define adcP         adcl
#define sbbP         sbbl
#define subP         subl
#define andP         andl
#define subP         subl
#define xorP         xorl
#define cmpP         cmpl
#define negP         negl
#define testP        testl
#define pushP        pushl
#define pushP_cfi    pushl_cfi
#define pushP_cfi_r  pushl_cfi_r
#define pushfP       pushfl
#define pushfP_cfi   pushfl_cfi
#define pushfP_cfi_r pushfl_cfi_r
#define popP         popl
#define popP_cfi     popl_cfi
#define popP_cfi_r   popl_cfi_r
#define popfP        popfl
#define popfP_cfi    popfl_cfi
#define popfP_cfi_r  popfl_cfi_r
#define jmpP         jmpl
#define callP        calll
#define leaP         leal
#define incP         incl
#define decP         decl
#define lidtP        lidtl
#define sidtP        sidtl
#define lgdtP        lgdtl
#define sgdtP        sgdtl
#define xchgP        xchgl
#define stosP        stosl
#define lodsP        lodsl
#define cmpsP        cmpsl
#define movsP        movsl
#define scasP        scasl
#define notP         notl

#ifdef __KERNEL__
#define segtls fs /* THIS_TASK: SEGMENT_KERNEL_FSBASE */
#else /* __KERNEL__ */
#define segtls gs /* user-space TLS (as set-up by libdl.so) (SEGMENT_USER_GSBASE_RPL) */
#endif /* !__KERNEL__ */

#endif /* !__x86_64__ */
#endif /* __ASSEMBLER__ */

#endif /* !_I386_KOS_ASM_INSTR_COMPAT_H */
