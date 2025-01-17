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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_DEBUG_PANIC64_S
#define GUARD_KERNEL_CORE_ARCH_I386_DEBUG_PANIC64_S 1
#define __ASSEMBLER__ 1

#include <kernel/compiler.h>

#include <kernel/panic.h>

#include <cfi.h>
#include <asm/instr/fsgsbase.h>
#include <bits/va_list-struct.h>
#include <kos/kernel/cpu-state-asm.h>
#include <kos/kernel/cpu-state.h>

/* ATTR_NORETURN void kernel_panic_here(void) */
.section .text.cold
PUBLIC_FUNCTION(kernel_panic_here)
	.cfi_startproc
	.cfi_signal_frame
	pushfq_cfi_r
	pushq_cfi_r %rax
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rbx
	pushq_cfi %rsp
	addq   $(56), 0(%rsp)
	.cfi_rel_offset %rsp, 0
	pushq_cfi_r %rbp
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	pushq_cfi_r %r12
	pushq_cfi_r %r13
	pushq_cfi_r %r14
	pushq_cfi_r %r15
	pushq_cfi_seg_r %ss, %rax
	pushq_cfi_seg_r %cs, %rax
	ASM_PUSH_SGBASE_CFI_R
	ASM_PUSH_SGREGS_CFI_R(%rax)

	xorq   %rdx, %rdx /* __builtin_va_list args */
	xorq   %rsi, %rsi /* char const *format */
	movq   %rsp, %rdi /* struct ucpustate *__restrict state */
	PUBLIC(kernel_vpanic_ucpustate)
	call   kernel_vpanic_ucpustate
	nop /* For tracebacks... */
	.cfi_endproc
END(kernel_panic_here)


/* ATTR_NORETURN void kernel_panic_here_n(unsigned int n_skip) */
.section .text.cold
PUBLIC_FUNCTION(kernel_panic_here_n)
	.cfi_startproc
	.cfi_signal_frame
	pushfq_cfi_r
	pushq_cfi_r %rax
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rbx
	pushq_cfi %rsp
	addq   $(56), 0(%rsp)
	.cfi_rel_offset %rsp, 0
	pushq_cfi_r %rbp
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	pushq_cfi_r %r12
	pushq_cfi_r %r13
	pushq_cfi_r %r14
	pushq_cfi_r %r15
	pushq_cfi_seg_r %ss, %rax
	pushq_cfi_seg_r %cs, %rax
	ASM_PUSH_SGBASE_CFI_R
	ASM_PUSH_SGREGS_CFI_R(%rax)

	xorq   %rcx, %rcx /* __builtin_va_list args */
	xorq   %rdx, %rdx /* char const *format */
	movq   %rsp, %rsi /* struct ucpustate *__restrict state */
//	movq   %rdi, %rdi /* unsigned int n_skip */
	PUBLIC(kernel_vpanic_ucpustate_n)
	call   kernel_vpanic_ucpustate_n
	nop /* For tracebacks... */
	.cfi_endproc
END(kernel_panic_here_n)


/* ATTR_NORETURN void kernel_vpanic(char const *format, va_list args) */
.section .text.cold
PUBLIC_FUNCTION(kernel_vpanic)
	.cfi_startproc
	.cfi_signal_frame
	pushfq_cfi_r
	pushq_cfi_r %rax
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rbx
	pushq_cfi %rsp
	addq   $(56), 0(%rsp)
	.cfi_rel_offset %rsp, 0
	pushq_cfi_r %rbp
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	pushq_cfi_r %r12
	pushq_cfi_r %r13
	pushq_cfi_r %r14
	pushq_cfi_r %r15
	pushq_cfi_seg_r %ss, %rax
	pushq_cfi_seg_r %cs, %rax
	ASM_PUSH_SGBASE_CFI_R
	ASM_PUSH_SGREGS_CFI_R(%rax)

	movq   %rsi, %rdx /* __builtin_va_list args */
	movq   %rdi, %rsi /* char const *format */
	movq   %rsp, %rdi /* struct ucpustate *__restrict state */
	PUBLIC(kernel_vpanic_ucpustate)
	call   kernel_vpanic_ucpustate
	nop /* For tracebacks... */
	.cfi_endproc
END(kernel_vpanic)


/* ATTR_NORETURN void kernel_vpanic_n(unsigned int n_skip, char const *format, va_list args) */
.section .text.cold
PUBLIC_FUNCTION(kernel_vpanic_n)
	.cfi_startproc
	.cfi_signal_frame
	pushfq_cfi_r
	pushq_cfi_r %rax
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rbx
	pushq_cfi %rsp
	addq   $(56), 0(%rsp)
	.cfi_rel_offset %rsp, 0
	pushq_cfi_r %rbp
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	pushq_cfi_r %r12
	pushq_cfi_r %r13
	pushq_cfi_r %r14
	pushq_cfi_r %r15
	pushq_cfi_seg_r %ss, %rax
	pushq_cfi_seg_r %cs, %rax
	ASM_PUSH_SGBASE_CFI_R
	ASM_PUSH_SGREGS_CFI_R(%rax)

	movq   %rdx, %rcx /* __builtin_va_list args */
	movq   %rsi, %rdx /* char const *format */
	movq   %rsp, %rsi /* struct ucpustate *__restrict state */
//	movq   %rdi, %rdi /* unsigned int n_skip */
	PUBLIC(kernel_vpanic_ucpustate_n)
	call   kernel_vpanic_ucpustate_n
	nop /* For tracebacks... */
	.cfi_endproc
END(kernel_vpanic_n)


/* ATTR_NORETURN void kernel_panic(char const *format, ...) */
.section .text.cold
PUBLIC_FUNCTION(kernel_panic)
	.cfi_startproc
	.cfi_signal_frame
	pushfq_cfi_r
	pushq_cfi_r %rax
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rbx
	leaq   48(%rsp), %rax
	pushq_cfi %rax
	.cfi_rel_offset %rsp, 0
	pushq_cfi_r %rbp
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	pushq_cfi_r %r12
	pushq_cfi_r %r13
	pushq_cfi_r %r14
	pushq_cfi_r %r15
	pushq_cfi_seg_r %ss, %rax
	pushq_cfi_seg_r %cs, %rax
	ASM_PUSH_SGBASE_CFI_R
	ASM_PUSH_SGREGS_CFI_R(%rax)

	/* Reload RCX and RDX, as they have been clobbered by `ASM_PUSH_SGBASE_CFI_R' */
	movq   (OFFSET_UCPUSTATE_GPREGS + OFFSET_GPREGS_RCX)(%rsp), %rcx
	movq   (OFFSET_UCPUSTATE_GPREGS + OFFSET_GPREGS_RDX)(%rsp), %rdx

	/* struct x86_64_va_list_reg_save_area */
	pushq_cfi %r9
	pushq_cfi %r8
	pushq_cfi %rcx
	pushq_cfi %rdx
	pushq_cfi %rsi

	movq   %rdi, %rsi          /* char const *format */
	leaq   (8 * 5)(%rsp), %rdi /* struct ucpustate *__restrict state */

	/* `rsa_rdi' is already consumed by `char const *format' */
	/* x86_64_va_list_struct */
	leaq   -8(%rsp), %rax
	pushq_cfi %rax   /* vl_reg_save_area */
	leaq   (8 + (8 * 5) + SIZEOF_UCPUSTATE)(%rsp), %rax
	pushq_cfi %rax   /* vl_overflow_arg_area */
	pushq_cfi $(1*8) /* vl_gp_offset */
	movl   $(SIZEOF_X86_64_VA_LIST_REG_SAVE_AREA), OFFSET_X86_64_VA_LIST_STRUCT_FP_OFFSET(%rsp)
	movq   %rsp, %rdx /* __builtin_va_list args */

	PUBLIC(kernel_vpanic_ucpustate)
	call   kernel_vpanic_ucpustate
	nop /* For tracebacks... */
	.cfi_endproc
END(kernel_panic)


/* ATTR_NORETURN void kernel_panic_n(unsigned int n_skip, char const *format, ...) */
.section .text.cold
PUBLIC_FUNCTION(kernel_panic_n)
	.cfi_startproc
	.cfi_signal_frame
	pushfq_cfi_r
	pushq_cfi_r %rax
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rbx
	leaq   48(%rsp), %rax
	pushq_cfi %rax
	.cfi_rel_offset %rsp, 0
	pushq_cfi_r %rbp
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	pushq_cfi_r %r12
	pushq_cfi_r %r13
	pushq_cfi_r %r14
	pushq_cfi_r %r15
	pushq_cfi_seg_r %ss, %rax
	pushq_cfi_seg_r %cs, %rax
	ASM_PUSH_SGBASE_CFI_R
	ASM_PUSH_SGREGS_CFI_R(%rax)

	/* Reload RCX and RDX, as they have been clobbered by `ASM_PUSH_SGBASE_CFI_R' */
	movq   (OFFSET_UCPUSTATE_GPREGS + OFFSET_GPREGS_RCX)(%rsp), %rcx
	movq   (OFFSET_UCPUSTATE_GPREGS + OFFSET_GPREGS_RDX)(%rsp), %rdx

	/* struct x86_64_va_list_reg_save_area */
	pushq_cfi %r9
	pushq_cfi %r8
	pushq_cfi %rcx
	pushq_cfi %rdx

	movq   %rsi, %rdx          /* char const *format */
	leaq   (8 * 4)(%rsp), %rsi /* struct ucpustate *__restrict state */
//	movq   %rdi, %rdi          /* unsigned int n_skip */

	/* `rsa_rdi' is already consumed by `unsigned int n_skip' */
	/* `rsa_rsi' is already consumed by `char const *format' */
	/* x86_64_va_list_struct */
	leaq   -16(%rsp), %rax
	pushq_cfi %rax   /* vl_reg_save_area */
	leaq   (8 + (8 * 4) + SIZEOF_UCPUSTATE)(%rsp), %rax
	pushq_cfi %rax   /* vl_overflow_arg_area */
	pushq_cfi $(2*8) /* vl_gp_offset */
	movl   $(SIZEOF_X86_64_VA_LIST_REG_SAVE_AREA), OFFSET_X86_64_VA_LIST_STRUCT_FP_OFFSET(%rsp)
	movq   %rsp, %rcx /* __builtin_va_list args */

	PUBLIC(kernel_vpanic_ucpustate_n)
	call   kernel_vpanic_ucpustate_n
	nop /* For tracebacks... */
	.cfi_endproc
END(kernel_panic_n)

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_DEBUG_PANIC64_S */
