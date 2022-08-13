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
#ifndef GUARD_LIBCPUSTATE_ARCH_I386_APPLY64_S
#define GUARD_LIBCPUSTATE_ARCH_I386_APPLY64_S 1

#include "../../api.h"
/**/

#include <hybrid/compiler.h>

#include <cfi.h>
#include <asm/cpu-flags.h>
#include <asm/instr/fsgsbase.h>
#include <asm/instr/interrupt.h>
#include <kos/kernel/cpu-state-asm.h>
#include <kos/kernel/cpu-state.h>

#include <libcpustate/apply.h>

#ifdef __KERNEL__
#include <asm/instr/kgsbase.h>
#endif /* __KERNEL__ */

#ifdef __KERNEL__
#define TEXT_SECTION     .xdata
#define BEGIN_TRAP(name) PUBLIC_FUNCTION(name); .byte 0xe9; .long 0x00000000
#define END_TRAP(name)   END(name)
#else /* __KERNEL__ */
#define TEXT_SECTION     .text
#define BEGIN_TRAP(name) /* nothing */
#define END_TRAP(name)   /* nothing */
#endif /* !__KERNEL__ */


#ifdef __KERNEL__
.section TEXT_SECTION
	.cfi_startproc simple
	.cfi_signal_frame
	.cfi_def_cfa %rdi, 0
	ASM_CFI_OFFSET_RESTORE_ICPUSTATE(0)
BEGIN_TRAP(kernel_debugtrap_icpustate)
INTERN_FUNCTION(libcpu_apply_icpustate)
	movq  %rdi, %rsp
	.cfi_def_cfa_register %rsp
INTERN_FUNCTION(libcpu_apply_icpustate_rsp)
	ASM_POP_ICPUSTATE_BEFORE_IRET_CFI_R
	intr_exit
	.cfi_endproc
END(libcpu_apply_icpustate_rsp)
END(libcpu_apply_icpustate)
END_TRAP(kernel_debugtrap_icpustate)
DEFINE_PUBLIC_ALIAS(cpu_apply_icpustate, libcpu_apply_icpustate)
DEFINE_PUBLIC_ALIAS(cpu_apply_icpustate_rsp, libcpu_apply_icpustate_rsp)



.section TEXT_SECTION
	.cfi_startproc simple
	.cfi_signal_frame
	.cfi_def_cfa %rdi, OFFSET_SCPUSTATE_IRREGS
	ASM_CFI_REL_OFFSET_RESTORE_SCPUSTATE(0)
BEGIN_TRAP(kernel_debugtrap_scpustate)
INTERN_FUNCTION(libcpu_apply_scpustate)
	movq  %rdi, %rsp
	.cfi_def_cfa_register %rsp
INTERN_FUNCTION(libcpu_apply_scpustate_rsp)
	cli
	movq   %gs:0, %rcx /* Must preserve %gs.base! */
	ASM_POP_SGREGS_CFI_R(%rax)
	wrgsbaseq %rcx
	ASM_POP_SGBASE_CFI_R
	ASM_POP_GPREGSNSP_CFI_R
	intr_exit  intr_enabled=0
	.cfi_endproc
END(libcpu_apply_scpustate_rsp)
END(libcpu_apply_scpustate)
END_TRAP(kernel_debugtrap_scpustate)
DEFINE_PUBLIC_ALIAS(cpu_apply_scpustate, libcpu_apply_scpustate)
DEFINE_PUBLIC_ALIAS(cpu_apply_scpustate_rsp, libcpu_apply_scpustate_rsp)

#endif /* __KERNEL__ */


.macro wrgs_keepbase reg:req, clobber=%rcx
#ifdef __KERNEL__
	/* Special handling  required: Must  set  the new  %gs  value
	 * without trashing `%gs.base'. - Same as `__wrgs_keepbase()' */
	pushfq
	cli
	movq   %gs:0, \clobber /* rdgsbaseq \clobber */
	movw   \reg, %gs
	wrgsbaseq \clobber
	popfq
#else /* __KERNEL__ */
	movw   \reg, %gs
#endif /* !__KERNEL__ */
.endm



.section TEXT_SECTION
	.cfi_startproc simple
	.cfi_signal_frame
	.cfi_def_cfa %rdi, 0
	ASM_CFI_REL_OFFSET_RESTORE_UCPUSTATE(0)
BEGIN_TRAP(kernel_debugtrap_ucpustate)
INTERN_FUNCTION(libcpu_apply_ucpustate)

	/* Construct an IRET tail that we can use to load the context. */
	pushq  (OFFSET_UCPUSTATE_SS)(%rdi)
	pushq  (OFFSET_UCPUSTATE_GPREGS + OFFSET_GPREGS_RSP)(%rdi)
	pushq  (OFFSET_UCPUSTATE_RFLAGS)(%rdi)
	pushq  (OFFSET_UCPUSTATE_CS)(%rdi)
	pushq  (OFFSET_UCPUSTATE_RIP)(%rdi)

	/* Load segment registers. */
	movw   (OFFSET_UCPUSTATE_SGREGS + OFFSET_SGREGS_DS)(%rdi), %ax
	movw   %ax, %ds
	.cfi_same_value %ds
	movw   (OFFSET_UCPUSTATE_SGREGS + OFFSET_SGREGS_ES)(%rdi), %ax
	movw   %ax, %es
	.cfi_same_value %es
	movw   (OFFSET_UCPUSTATE_SGREGS + OFFSET_SGREGS_FS)(%rdi), %ax
	movw   %ax, %fs
	.cfi_same_value %fs
	movw   (OFFSET_UCPUSTATE_SGREGS + OFFSET_SGREGS_GS)(%rdi), %ax
	wrgs_keepbase %ax, %rcx
	.cfi_same_value %gs

	/* Load segment base registers. */
#ifdef __KERNEL__
	wrkgsbaseq (OFFSET_UCPUSTATE_SGBASE + OFFSET_SGBASE_GSBASE)(%rdi)
#else /* __KERNEL__ */
	movq   (OFFSET_UCPUSTATE_SGBASE + OFFSET_SGBASE_GSBASE)(%rdi), %rax
	wrgsbaseq %rax
	.cfi_same_value %gs.base
#endif /* !__KERNEL__ */
	movq   (OFFSET_UCPUSTATE_SGBASE + OFFSET_SGBASE_FSBASE)(%rdi), %rax
	wrfsbaseq %rax
	.cfi_same_value %fs.base

	/* Restore IRREGS registers from the stack. */
	.cfi_reg_offset %rip, OFFSET_IRREGS_RIP, %rsp
	.cfi_reg_offset %cs, OFFSET_IRREGS_CS, %rsp
	.cfi_reg_offset %rflags, OFFSET_IRREGS_RFLAGS, %rsp
	.cfi_reg_offset %rsp, OFFSET_IRREGS_RSP, %rsp
	.cfi_reg_offset %ss, OFFSET_IRREGS_SS, %rsp

	/* Load GP registers. */
	movq   (OFFSET_UCPUSTATE_GPREGS + OFFSET_GPREGS_RAX)(%rdi), %rax
	.cfi_same_value %rax
	movq   (OFFSET_UCPUSTATE_GPREGS + OFFSET_GPREGS_RCX)(%rdi), %rcx
	.cfi_same_value %rcx
	movq   (OFFSET_UCPUSTATE_GPREGS + OFFSET_GPREGS_RDX)(%rdi), %rdx
	.cfi_same_value %rdx
	movq   (OFFSET_UCPUSTATE_GPREGS + OFFSET_GPREGS_RBX)(%rdi), %rbx
	.cfi_same_value %rbx
	movq   (OFFSET_UCPUSTATE_GPREGS + OFFSET_GPREGS_RBP)(%rdi), %rbp
	.cfi_same_value %rbp
	movq   (OFFSET_UCPUSTATE_GPREGS + OFFSET_GPREGS_RSI)(%rdi), %rsi
	.cfi_same_value %rsi
	movq   (OFFSET_UCPUSTATE_GPREGS + OFFSET_GPREGS_R8)(%rdi), %r8
	.cfi_same_value %r8
	movq   (OFFSET_UCPUSTATE_GPREGS + OFFSET_GPREGS_R9)(%rdi), %r9
	.cfi_same_value %r9
	movq   (OFFSET_UCPUSTATE_GPREGS + OFFSET_GPREGS_R10)(%rdi), %r10
	.cfi_same_value %r10
	movq   (OFFSET_UCPUSTATE_GPREGS + OFFSET_GPREGS_R11)(%rdi), %r11
	.cfi_same_value %r11
	movq   (OFFSET_UCPUSTATE_GPREGS + OFFSET_GPREGS_R12)(%rdi), %r12
	.cfi_same_value %r12
	movq   (OFFSET_UCPUSTATE_GPREGS + OFFSET_GPREGS_R13)(%rdi), %r13
	.cfi_same_value %r13
	movq   (OFFSET_UCPUSTATE_GPREGS + OFFSET_GPREGS_R14)(%rdi), %r14
	.cfi_same_value %r14
	movq   (OFFSET_UCPUSTATE_GPREGS + OFFSET_GPREGS_R15)(%rdi), %r15
	.cfi_same_value %r15
	movq   (OFFSET_UCPUSTATE_GPREGS + OFFSET_GPREGS_RDI)(%rdi), %rdi
	.cfi_same_value %rdi

	/* Load the IRET tail. */
	intr_exit
	.cfi_endproc
END(libcpu_apply_ucpustate)
END_TRAP(kernel_debugtrap_ucpustate)
DEFINE_PUBLIC_ALIAS(cpu_apply_ucpustate, libcpu_apply_ucpustate)


.section TEXT_SECTION
	.cfi_startproc simple
	.cfi_signal_frame
	.cfi_def_cfa %rdi, 0
	ASM_CFI_REL_OFFSET_RESTORE_KCPUSTATE(0)
BEGIN_TRAP(kernel_debugtrap_kcpustate)
INTERN_FUNCTION(libcpu_apply_kcpustate)

	/* Load the target stack. */
	movq   (OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_RSP)(%rdi), %rsp
	.cfi_same_value %rsp

	/* Load the target RFLAGS register. */
	pushq  (OFFSET_KCPUSTATE_RFLAGS)(%rdi)
	popfq
	.cfi_same_value %rflags

	/* Push the return address onto the stack. */
	pushq  (OFFSET_KCPUSTATE_RIP)(%rdi)
	.cfi_reg_offset %rip, 0, %rsp

	/* Load GP registers. */
	movq   (OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_RAX)(%rdi), %rax
	.cfi_same_value %rax
	movq   (OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_RCX)(%rdi), %rcx
	.cfi_same_value %rcx
	movq   (OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_RDX)(%rdi), %rdx
	.cfi_same_value %rdx
	movq   (OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_RBX)(%rdi), %rbx
	.cfi_same_value %rbx
	movq   (OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_RBP)(%rdi), %rbp
	.cfi_same_value %rbp
	movq   (OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_RSI)(%rdi), %rsi
	.cfi_same_value %rsi
	movq   (OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_R8)(%rdi), %r8
	.cfi_same_value %r8
	movq   (OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_R9)(%rdi), %r9
	.cfi_same_value %r9
	movq   (OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_R10)(%rdi), %r10
	.cfi_same_value %r10
	movq   (OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_R11)(%rdi), %r11
	.cfi_same_value %r11
	movq   (OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_R12)(%rdi), %r12
	.cfi_same_value %r12
	movq   (OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_R13)(%rdi), %r13
	.cfi_same_value %r13
	movq   (OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_R14)(%rdi), %r14
	.cfi_same_value %r14
	movq   (OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_R15)(%rdi), %r15
	.cfi_same_value %r15
	movq   (OFFSET_KCPUSTATE_GPREGS + OFFSET_GPREGS_RDI)(%rdi), %rdi
	.cfi_same_value %rdi

	ret
	.cfi_endproc
END(libcpu_apply_kcpustate)
END_TRAP(kernel_debugtrap_kcpustate)
DEFINE_PUBLIC_ALIAS(cpu_apply_kcpustate, libcpu_apply_kcpustate)


.section .xdata
	.cfi_startproc simple
	.cfi_signal_frame
	.cfi_def_cfa %rdi, 0
	ASM_CFI_REL_OFFSET_RESTORE_LCPUSTATE(0)
BEGIN_TRAP(kernel_debugtrap_lcpustate)
INTERN_FUNCTION(libcpu_apply_lcpustate)
	movq   OFFSET_LCPUSTATE_R15(%rdi), %r15
	.cfi_same_value %r15
	movq   OFFSET_LCPUSTATE_R14(%rdi), %r14
	.cfi_same_value %r14
	movq   OFFSET_LCPUSTATE_R13(%rdi), %r13
	.cfi_same_value %r13
	movq   OFFSET_LCPUSTATE_R12(%rdi), %r12
	.cfi_same_value %r12
	movq   OFFSET_LCPUSTATE_RBP(%rdi), %rbp
	.cfi_same_value %rbp
	movq   OFFSET_LCPUSTATE_RSP(%rdi), %rsp
	.cfi_same_value %rsp
	movq   OFFSET_LCPUSTATE_RBX(%rdi), %rbx
	.cfi_same_value %rbx
	pushq  OFFSET_LCPUSTATE_RIP(%rdi)
	ret
	.cfi_endproc
END(libcpu_apply_lcpustate)
END_TRAP(kernel_debugtrap_lcpustate)
DEFINE_PUBLIC_ALIAS(cpu_apply_lcpustate, libcpu_apply_lcpustate)


.section TEXT_SECTION
	.cfi_startproc simple
	.cfi_signal_frame
	.cfi_def_cfa %rdi, 0
	ASM_CFI_REL_OFFSET_RESTORE_FCPUSTATE(0)
BEGIN_TRAP(kernel_debugtrap_fcpustate)
INTERN_FUNCTION(libcpu_apply_fcpustate)

	/* Load the %tr register */
	movw   OFFSET_FCPUSTATE_TR(%rdi), %ax
	ltrw   %ax
	.cfi_same_value %tr

	/* Load the %ldt register */
	movw   OFFSET_FCPUSTATE_LDT(%rdi), %ax
	lldtw  %ax
	.cfi_same_value %ldtr

	/* Load segment registers. */
	movw   OFFSET_FCPUSTATE_GS(%rdi), %ax
	wrgs_keepbase %ax, %rcx
	.cfi_same_value %gs
	movw   OFFSET_FCPUSTATE_FS(%rdi), %ax
	movw   %ax, %fs
	.cfi_same_value %fs
	movw   OFFSET_FCPUSTATE_ES(%rdi), %ax
	movw   %ax, %es
	.cfi_same_value %es
	movw   OFFSET_FCPUSTATE_DS(%rdi), %ax
	movw   %ax, %ds
	.cfi_same_value %ds

	/* Load control registers. */
	movq   (OFFSET_FCPUSTATE_COREGS + OFFSET_COREGS_CR0)(%rdi), %rax
	movq   %rax, %cr0
	movq   (OFFSET_FCPUSTATE_COREGS + OFFSET_COREGS_CR2)(%rdi), %rax
	movq   %rax, %cr2
	movq   (OFFSET_FCPUSTATE_COREGS + OFFSET_COREGS_CR3)(%rdi), %rax
	movq   %rax, %cr3
	movq   (OFFSET_FCPUSTATE_COREGS + OFFSET_COREGS_CR4)(%rdi), %rax
	movq   %rax, %cr4

	/* Load debug registers. */
	movq   (OFFSET_FCPUSTATE_DRREGS + OFFSET_DRREGS_DR0)(%rdi), %rax
	movq   %rax, %dr0
	movq   (OFFSET_FCPUSTATE_DRREGS + OFFSET_DRREGS_DR1)(%rdi), %rax
	movq   %rax, %dr1
	movq   (OFFSET_FCPUSTATE_DRREGS + OFFSET_DRREGS_DR2)(%rdi), %rax
	movq   %rax, %dr2
	movq   (OFFSET_FCPUSTATE_DRREGS + OFFSET_DRREGS_DR3)(%rdi), %rax
	movq   %rax, %dr3
	movq   (OFFSET_FCPUSTATE_DRREGS + OFFSET_DRREGS_DR6)(%rdi), %rax
	movq   %rax, %dr6
	movq   (OFFSET_FCPUSTATE_DRREGS + OFFSET_DRREGS_DR7)(%rdi), %rax
	movq   %rax, %dr7

	/* Load the GDT and IDT. */
	lgdtq  OFFSET_FCPUSTATE_GDT(%rdi)
	lidtq  OFFSET_FCPUSTATE_IDT(%rdi)

	/* Construct an IRET tail that we can use to load the context. */
	pushq  (OFFSET_FCPUSTATE_SS)(%rdi)
	pushq  (OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_RSP)(%rdi)
	pushq  (OFFSET_FCPUSTATE_RFLAGS)(%rdi)
	pushq  (OFFSET_FCPUSTATE_CS)(%rdi)
	pushq  (OFFSET_FCPUSTATE_RIP)(%rdi)

	/* Restore IRREGS registers from the stack. */
	.cfi_reg_offset %rip, OFFSET_IRREGS_RIP, %rsp
	.cfi_reg_offset %cs, OFFSET_IRREGS_CS, %rsp
	.cfi_reg_offset %rflags, OFFSET_IRREGS_RFLAGS, %rsp
	.cfi_reg_offset %rsp, OFFSET_IRREGS_RSP, %rsp
	.cfi_reg_offset %ss, OFFSET_IRREGS_SS, %rsp

	/* Load segment base registers. */
#ifdef __KERNEL__
	wrkgsbaseq (OFFSET_FCPUSTATE_SGBASE + OFFSET_SGBASE_GSBASE)(%rdi)
#else /* __KERNEL__ */
	movq   (OFFSET_FCPUSTATE_SGBASE + OFFSET_SGBASE_GSBASE)(%rdi), %rax
	wrgsbaseq %rax
	.cfi_same_value %gs.base
#endif /* !__KERNEL__ */
	movq   (OFFSET_FCPUSTATE_SGBASE + OFFSET_SGBASE_FSBASE)(%rdi), %rax
	wrfsbaseq %rax
	.cfi_same_value %fs.base


	/* Load GP registers. */
	movq   (OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_RAX)(%rdi), %rax
	.cfi_same_value %rax
	movq   (OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_RCX)(%rdi), %rcx
	.cfi_same_value %rcx
	movq   (OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_RDX)(%rdi), %rdx
	.cfi_same_value %rdx
	movq   (OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_RBX)(%rdi), %rbx
	.cfi_same_value %rbx
	movq   (OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_RBP)(%rdi), %rbp
	.cfi_same_value %rbp
	movq   (OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_RSI)(%rdi), %rsi
	.cfi_same_value %rsi
	movq   (OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_R8)(%rdi), %r8
	.cfi_same_value %r8
	movq   (OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_R9)(%rdi), %r9
	.cfi_same_value %r9
	movq   (OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_R10)(%rdi), %r10
	.cfi_same_value %r10
	movq   (OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_R11)(%rdi), %r11
	.cfi_same_value %r11
	movq   (OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_R12)(%rdi), %r12
	.cfi_same_value %r12
	movq   (OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_R13)(%rdi), %r13
	.cfi_same_value %r13
	movq   (OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_R14)(%rdi), %r14
	.cfi_same_value %r14
	movq   (OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_R15)(%rdi), %r15
	.cfi_same_value %r15
	movq   (OFFSET_FCPUSTATE_GPREGS + OFFSET_GPREGS_RDI)(%rdi), %rdi
	.cfi_same_value %rdi

	intr_exit
	.cfi_endproc
END(libcpu_apply_fcpustate)
END_TRAP(kernel_debugtrap_fcpustate)
DEFINE_PUBLIC_ALIAS(cpu_apply_fcpustate, libcpu_apply_fcpustate)

#endif /* !GUARD_LIBCPUSTATE_ARCH_I386_APPLY64_S */
