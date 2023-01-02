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

/* Register arguments for SysVAbi */
#define R_sysvabi0b dil
#define R_sysvabi0w di
#define R_sysvabi0l edi
#define R_sysvabi0q rdi
#define R_sysvabi0P rdi
#define R_sysvabi1b sil
#define R_sysvabi1w si
#define R_sysvabi1l esi
#define R_sysvabi1q rsi
#define R_sysvabi1P rsi
#define R_sysvabi2b dl
#define R_sysvabi2w dx
#define R_sysvabi2l edx
#define R_sysvabi2q rdx
#define R_sysvabi2P rdx
#define R_sysvabi3b cl
#define R_sysvabi3w cx
#define R_sysvabi3l ecx
#define R_sysvabi3q rcx
#define R_sysvabi3P rcx
#define R_sysvabi4b r8l
#define R_sysvabi4w r8w
#define R_sysvabi4l r8d
#define R_sysvabi4q r8
#define R_sysvabi4P r8
#define R_sysvabi5b r9l
#define R_sysvabi5w r9w
#define R_sysvabi5l r9d
#define R_sysvabi5q r9
#define R_sysvabi5P r9

/* Register arguments for system calls */
#define R_syscall0b dil
#define R_syscall0w di
#define R_syscall0l edi
#define R_syscall0q rdi
#define R_syscall0P rdi
#define R_syscall1b sil
#define R_syscall1w si
#define R_syscall1l esi
#define R_syscall1q rsi
#define R_syscall1P rsi
#define R_syscall2b dl
#define R_syscall2w dx
#define R_syscall2l edx
#define R_syscall2q rdx
#define R_syscall2P rdx
#define R_syscall3b r10l
#define R_syscall3w r10w
#define R_syscall3l r10d
#define R_syscall3q r10
#define R_syscall3P r10
#define R_syscall4b r8l
#define R_syscall4w r8w
#define R_syscall4l r8d
#define R_syscall4q r8
#define R_syscall4P r8
#define R_syscall5b r9l
#define R_syscall5w r9w
#define R_syscall5l r9d
#define R_syscall5q r9
#define R_syscall5P r9

/* Register arguments for MsAbi */
#define R_msabi0b cl
#define R_msabi0w cx
#define R_msabi0l ecx
#define R_msabi0q rcx
#define R_msabi0P rcx
#define R_msabi1b dl
#define R_msabi1w dx
#define R_msabi1l edx
#define R_msabi1q rdx
#define R_msabi1P rdx
#define R_msabi2b r8l
#define R_msabi2w r8w
#define R_msabi2l r8d
#define R_msabi2q r8
#define R_msabi2P r8
#define R_msabi3b r9l
#define R_msabi3w r9w
#define R_msabi3l r9d
#define R_msabi3q r9
#define R_msabi3P r9

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
#define andP         andq
#define subP         subq
#define subP_imm_cfi subq_imm_cfi
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
#define cmovaP       cmovaq
#define cmovaeP      cmovaeq
#define cmovbP       cmovbq
#define cmovbeP      cmovbeq
#define cmovcP       cmovcq
#define cmoveP       cmoveq
#define cmovgP       cmovgq
#define cmovgeP      cmovgeq
#define cmovlP       cmovlq
#define cmovleP      cmovleq
#define cmovnaP      cmovnaq
#define cmovnaeP     cmovnaeq
#define cmovnbP      cmovnbq
#define cmovnbeP     cmovnbeq
#define cmovncP      cmovncq
#define cmovneP      cmovneq
#define cmovngP      cmovngq
#define cmovngeP     cmovngeq
#define cmovnlP      cmovnlq
#define cmovnleP     cmovnleq
#define cmovnoP      cmovnoq
#define cmovnpP      cmovnpq
#define cmovnsP      cmovnsq
#define cmovnzP      cmovnzq
#define cmovoP       cmovoq
#define cmovpP       cmovpq
#define cmovpeP      cmovpeq
#define cmovpoP      cmovpoq
#define cmovsP       cmovsq
#define cmovzP       cmovzq
#define shlP         shlq
#define shrP         shrq
#define salP         salq
#define sarP         sarq
#define rolP         rolq
#define rorP         rorq
#define rclP         rclq
#define rcrP         rcrq
#define jPcxz        jrcxz
#define rdfsbaseP    rdfsbaseq
#define rdgsbaseP    rdgsbaseq
#define wrfsbaseP    wrfsbaseq
#define wrgsbaseP    wrgsbaseq
#define iretP        iretq
#define lretP        lretq

#ifdef __KERNEL__
#define segtls       gs /* THIS_TASK */
#define rdtlsbasel   rdgsbasel
#define wrtlsbasel   wrgsbasel
#define rdtlsbaseq   rdgsbaseq
#define wrtlsbaseq   wrgsbaseq
#define rdtlsbaseP   rdgsbaseq
#define wrtlsbaseP   wrgsbaseq
#else /* __KERNEL__ */
#define segtls       fs /* user-space TLS (as set-up by libdl.so) */
#define rdtlsbasel   rdfsbasel
#define wrtlsbasel   wrfsbasel
#define rdtlsbaseq   rdfsbaseq
#define wrtlsbaseq   wrfsbaseq
#define rdtlsbaseP   rdfsbaseq
#define wrtlsbaseP   wrfsbaseq
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

/* Register arguments for system calls */
#define R_syscall0b bl
#define R_syscall0w bx
#define R_syscall0l ebx
#define R_syscall0P ebx
#define R_syscall1b cl
#define R_syscall1w cx
#define R_syscall1l ecx
#define R_syscall1P ecx
#define R_syscall2b dl
#define R_syscall2w dx
#define R_syscall2l edx
#define R_syscall2P rdx
#define R_syscall3w si
#define R_syscall3l esi
#define R_syscall3P esi
#define R_syscall4w di
#define R_syscall4l edi
#define R_syscall4P edi
#define R_syscall5w bp
#define R_syscall5l ebp
#define R_syscall5P ebp

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
#define andP         andl
#define subP         subl
#define subP_imm_cfi subl_imm_cfi
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
#define cmovaP       cmoval
#define cmovaeP      cmovael
#define cmovbP       cmovbl
#define cmovbeP      cmovbel
#define cmovcP       cmovcl
#define cmoveP       cmovel
#define cmovgP       cmovgl
#define cmovgeP      cmovgel
#define cmovlP       cmovll
#define cmovleP      cmovlel
#define cmovnaP      cmovnal
#define cmovnaeP     cmovnael
#define cmovnbP      cmovnbl
#define cmovnbeP     cmovnbel
#define cmovncP      cmovncl
#define cmovneP      cmovnel
#define cmovngP      cmovngl
#define cmovngeP     cmovngel
#define cmovnlP      cmovnll
#define cmovnleP     cmovnlel
#define cmovnoP      cmovnol
#define cmovnpP      cmovnpl
#define cmovnsP      cmovnsl
#define cmovnzP      cmovnzl
#define cmovoP       cmovol
#define cmovpP       cmovpl
#define cmovpeP      cmovpel
#define cmovpoP      cmovpol
#define cmovsP       cmovsl
#define cmovzP       cmovzl
#define shlP         shll
#define shrP         shrl
#define salP         sall
#define sarP         sarl
#define rolP         roll
#define rorP         rorl
#define rclP         rcll
#define rcrP         rcrl
#define jPcxz        jecxz
#define rdfsbaseP    rdfsbasel
#define rdgsbaseP    rdgsbasel
#define wrfsbaseP    wrfsbasel
#define wrgsbaseP    wrgsbasel
#define iretP        iret
#define lretP        lret

#ifdef __KERNEL__
#define segtls       fs /* THIS_TASK: SEGMENT_KERNEL_FSBASE */
#define rdtlsbasel   rdfsbasel
#define wrtlsbasel   wrfsbasel
#define rdtlsbaseP   rdfsbasel
#define wrtlsbaseP   wrfsbasel
#else /* __KERNEL__ */
#define segtls       gs /* user-space TLS (as set-up by libdl.so) (SEGMENT_USER_GSBASE_RPL) */
#define rdtlsbasel   rdgsbasel
#define wrtlsbasel   wrgsbasel
#define rdtlsbaseP   rdgsbasel
#define wrtlsbaseP   wrgsbasel
#endif /* !__KERNEL__ */

#endif /* !__x86_64__ */
#endif /* __ASSEMBLER__ */

#endif /* !_I386_KOS_ASM_INSTR_COMPAT_H */
