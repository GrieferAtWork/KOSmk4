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
#ifndef _I386_KOS_ASM_INSTR_KGSBASE_H
#define _I386_KOS_ASM_INSTR_KGSBASE_H 1

#include <__stdinc.h>

#include <hybrid/__asm.h>
#include <hybrid/host.h>

#include <asm/instr/movzxq.h>

/* Helper  macros   to  push/pop   the  `IA32_KERNEL_GS_BASE'   MSR.
 * Note that while _in_ kernel-space, `IA32_KERNEL_GS_BASE' actually
 * refers to the user-space %gs.base  value, so these macros can  be
 * used to push/pop that register instead, meaning that they're very
 * useful  when  it  comes to  constructing  `scpustate' structures. */

#ifndef __COMPILER_NO_GCC_ASM_MACROS
#ifdef __x86_64__
__ASM_BEGIN

/* Read the kernel-gs-base register into \dst
 * CLOBBER: %rax, %rcx, %rdx and %rflags */
__ASM_L(.macro rdkgsbaseq dst:req)
__ASM_L(	movl   $(0xc0000102), %ecx) /* 0xc0000102 = IA32_KERNEL_GS_BASE */
__ASM_L(	rdmsr)
__ASM_L(.ifc \dst,'%rax')
__ASM_L(	shlq   $(32), %rdx)
__ASM_L(	orq    %rdx, %rax)
__ASM_L(.else;.ifc \dst,'%rcx')
__ASM_L(	shlq   $(32), %rdx)
__ASM_L(	movzlq %eax, %rcx)
__ASM_L(	orq    %rdx, %rcx)
__ASM_L(.else;.ifc \dst,'%rdx')
__ASM_L(	shlq   $(32), %rdx)
__ASM_L(	movzlq %eax, %rax)
__ASM_L(	orq    %rax, %rdx)
__ASM_L(.else;.ifc \dst,'%rbx')
__ASM_L(	shlq   $(32), %rdx)
__ASM_L(	movzlq %eax, %rbx)
__ASM_L(	orq    %rdx, %rbx)
__ASM_L(.else;.ifc \dst,'%rdi')
__ASM_L(	shlq   $(32), %rdx)
__ASM_L(	movzlq %eax, %rdi)
__ASM_L(	orq    %rdx, %rdi)
__ASM_L(.else;.ifc \dst,'%rsi')
__ASM_L(	shlq   $(32), %rdx)
__ASM_L(	movzlq %eax, %rsi)
__ASM_L(	orq    %rdx, %rsi)
__ASM_L(.else;.ifc \dst,'%rbp')
__ASM_L(	shlq   $(32), %rdx)
__ASM_L(	movzlq %eax, %rbp)
__ASM_L(	orq    %rdx, %rbp)
__ASM_L(.else;.ifc \dst,'%rsp')
__ASM_L(	shlq   $(32), %rdx)
__ASM_L(	movzlq %eax, %rsp)
__ASM_L(	orq    %rdx, %rsp)
__ASM_L(.else;.ifc \dst,'%r8')
__ASM_L(	shlq   $(32), %rdx)
__ASM_L(	movzlq %eax, %r8)
__ASM_L(	orq    %rdx, %r8)
__ASM_L(.else;.ifc \dst,'%r9')
__ASM_L(	shlq   $(32), %rdx)
__ASM_L(	movzlq %eax, %r8)
__ASM_L(	orq    %rdx, %r9)
__ASM_L(.else;.ifc \dst,'%r10')
__ASM_L(	shlq   $(32), %rdx)
__ASM_L(	movzlq %eax, %r10)
__ASM_L(	orq    %rdx, %r10)
__ASM_L(.else;.ifc \dst,'%r11')
__ASM_L(	shlq   $(32), %rdx)
__ASM_L(	movzlq %eax, %r11)
__ASM_L(	orq    %rdx, %r11)
__ASM_L(.else;.ifc \dst,'%r12')
__ASM_L(	shlq   $(32), %rdx)
__ASM_L(	movzlq %eax, %r12)
__ASM_L(	orq    %rdx, %r12)
__ASM_L(.else;.ifc \dst,'%r13')
__ASM_L(	shlq   $(32), %rdx)
__ASM_L(	movzlq %eax, %r13)
__ASM_L(	orq    %rdx, %r13)
__ASM_L(.else;.ifc \dst,'%r14')
__ASM_L(	shlq   $(32), %rdx)
__ASM_L(	movzlq %eax, %r14)
__ASM_L(	orq    %rdx, %r14)
__ASM_L(.else;.ifc \dst,'%r15')
__ASM_L(	shlq   $(32), %rdx)
__ASM_L(	movzlq %eax, %r15)
__ASM_L(	orq    %rdx, %r15)
__ASM_L(.else)
__ASM_L(	movl   %eax, 0+\dst)
__ASM_L(	movl   %edx, 4+\dst)
__ASM_L(.endif;.endif;.endif;.endif;.endif;.endif;.endif;.endif)
__ASM_L(.endif;.endif;.endif;.endif;.endif;.endif;.endif;.endif)
__ASM_L(.endm)

/* Write \src into the kernel-gs-base register
 * CLOBBER: %rax, %rcx, %rdx and %rflags */
__ASM_L(.macro wrkgsbaseq src:req)
__ASM_L(.ifc \src,'%rax')
__ASM_L(	movq   %rax, %rdx)
__ASM_L(	shrq   $(32), %rdx)
__ASM_L(.else;.ifc \src,'%rcx')
__ASM_L(	movl   %ecx, %eax)
__ASM_L(	movq   %rcx, %rdx)
__ASM_L(	shrq   $(32), %rdx)
__ASM_L(.else;.ifc \src,'%rdx')
__ASM_L(	movl   %edx, %eax)
__ASM_L(	shrq   $(32), %rdx)
__ASM_L(.else;.ifc \src,'%rbx')
__ASM_L(	movl   %ebx, %eax)
__ASM_L(	movq   %rbx, %rdx)
__ASM_L(	shrq   $(32), %rdx)
__ASM_L(.else;.ifc \src,'%rdi')
__ASM_L(	movl   %edi, %eax)
__ASM_L(	movq   %rdi, %rdx)
__ASM_L(	shrq   $(32), %rdx)
__ASM_L(.else;.ifc \src,'%rsi')
__ASM_L(	movl   %esi, %eax)
__ASM_L(	movq   %rsi, %rdx)
__ASM_L(	shrq   $(32), %rdx)
__ASM_L(.else;.ifc \src,'%rbp')
__ASM_L(	movl   %ebp, %eax)
__ASM_L(	movq   %rbp, %rdx)
__ASM_L(	shrq   $(32), %rdx)
__ASM_L(.else;.ifc \src,'%rsp')
__ASM_L(	movl   %esp, %eax)
__ASM_L(	movq   %rsp, %rdx)
__ASM_L(	shrq   $(32), %rdx)
__ASM_L(.else;.ifc \src,'%r8')
__ASM_L(	movl   %r8d, %eax)
__ASM_L(	movq   %r8, %rdx)
__ASM_L(	shrq   $(32), %rdx)
__ASM_L(.else;.ifc \src,'%r9')
__ASM_L(	movl   %r9d, %eax)
__ASM_L(	movq   %r9, %rdx)
__ASM_L(	shrq   $(32), %rdx)
__ASM_L(.else;.ifc \src,'%r10')
__ASM_L(	movl   %r10d, %eax)
__ASM_L(	movq   %r10, %rdx)
__ASM_L(	shrq   $(32), %rdx)
__ASM_L(.else;.ifc \src,'%r11')
__ASM_L(	movl   %r11d, %eax)
__ASM_L(	movq   %r11, %rdx)
__ASM_L(	shrq   $(32), %rdx)
__ASM_L(.else;.ifc \src,'%r12')
__ASM_L(	movl   %r12d, %eax)
__ASM_L(	movq   %r12, %rdx)
__ASM_L(	shrq   $(32), %rdx)
__ASM_L(.else;.ifc \src,'%r13')
__ASM_L(	movl   %r13d, %eax)
__ASM_L(	movq   %r13, %rdx)
__ASM_L(	shrq   $(32), %rdx)
__ASM_L(.else;.ifc \src,'%r14')
__ASM_L(	movl   %r14d, %eax)
__ASM_L(	movq   %r14, %rdx)
__ASM_L(	shrq   $(32), %rdx)
__ASM_L(.else;.ifc \src,'%r15')
__ASM_L(	movl   %r15d, %eax)
__ASM_L(	movq   %r15, %rdx)
__ASM_L(	shrq   $(32), %rdx)
__ASM_L(.else)
__ASM_L(	movl   0+\src, %eax)
__ASM_L(	movl   4+\src, %edx)
__ASM_L(.endif;.endif;.endif;.endif;.endif;.endif;.endif;.endif)
__ASM_L(.endif;.endif;.endif;.endif;.endif;.endif;.endif;.endif)
__ASM_L(	movl   $(0xc0000102), %ecx) /* 0xc0000102 = IA32_KERNEL_GS_BASE */
__ASM_L(	wrmsr)
__ASM_L(.endm)


/* Push `IA32_KERNEL_GS_BASE' onto the stack.
 * CLOBBER: %rax, %rcx, %rdx and %rflags */
__ASM_L(.macro pushq_cfi_kgsbase)
__ASM_L(	subq   $(8), %rsp)
__ASM_L(	.cfi_adjust_cfa_offset 8)
__ASM_L(	movl   $(0xc0000102), %ecx) /* 0xc0000102 = IA32_KERNEL_GS_BASE */
__ASM_L(	rdmsr)
__ASM_L(	movl   %eax, 0(%rsp))
__ASM_L(	movl   %edx, 4(%rsp))
__ASM_L(.endm)

/* Pop `IA32_KERNEL_GS_BASE' from the stack.
 * CLOBBER: %rax, %rcx, %rdx and %rflags */
__ASM_L(.macro popq_cfi_kgsbase)
__ASM_L(	movl   $(0xc0000102), %ecx) /* 0xc0000102 = IA32_KERNEL_GS_BASE */
__ASM_L(	movl   0(%rsp), %eax)
__ASM_L(	movl   4(%rsp), %edx)
__ASM_L(	wrmsr)
__ASM_L(	addq   $(8), %rsp)
__ASM_L(	.cfi_adjust_cfa_offset -8)
__ASM_L(.endm)

__ASM_END
#endif /* __x86_64__ */
#endif /* !__COMPILER_NO_GCC_ASM_MACROS */

#endif /* !_I386_KOS_ASM_INSTR_KGSBASE_H */
