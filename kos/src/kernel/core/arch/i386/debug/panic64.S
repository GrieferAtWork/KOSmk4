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

#include <kernel/compiler.h>
#include <kernel/panic.h>
#include <kernel/fsgsbase.h>
#include <kos/kernel/cpu-state.h>
#include <asm/cfi.h>

.section .text.cold
/* ATTR_NORETURN void kernel_panic_here(void) */
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
	pushq_seg_cfi_r %ss, %rax
	pushq_seg_cfi_r %cs, %rax
	pushq_seg_cfi_r %fs.base, %rax
	pushq_seg_cfi_r %gs.base, %rax
	pushq_seg_cfi_r %ds, %rax
	pushq_seg_cfi_r %es, %rax
	pushq_cfi_r %fs
	pushq_cfi_r %gs

	xorq   %rdx, %rdx /* __builtin_va_list args */
	xorq   %rsi, %rsi /* char const *format */
	movq   %rsp, %rdi /* struct ucpustate *__restrict state */
	PUBLIC(kernel_vpanic_ucpustate)
	call   kernel_vpanic_ucpustate
	.cfi_endproc
END(kernel_panic_here)

.section .text.cold
/* ATTR_NORETURN void kernel_vpanic(char const *format, va_list args) */
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
	pushq_seg_cfi_r %ss, %rax
	pushq_seg_cfi_r %cs, %rax
	pushq_seg_cfi_r %fs.base, %rax
	pushq_seg_cfi_r %gs.base, %rax
	pushq_seg_cfi_r %ds, %rax
	pushq_seg_cfi_r %es, %rax
	pushq_cfi_r %fs
	pushq_cfi_r %gs

	movq   %rsi, %rdx /* __builtin_va_list args */
	movq   %rdi, %rsi /* char const *format */
	movq   %rsp, %rdi /* struct ucpustate *__restrict state */
	PUBLIC(kernel_vpanic_ucpustate)
	call   kernel_vpanic_ucpustate
	.cfi_endproc
END(kernel_vpanic)

.section .text.cold
/* ATTR_NORETURN void kernel_panic(char const *format, ...) */
PUBLIC_FUNCTION(kernel_panic)
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
	pushq_seg_cfi_r %ss, %rax
	pushq_seg_cfi_r %cs, %rax
	pushq_seg_cfi_r %fs.base, %rax
	pushq_seg_cfi_r %gs.base, %rax
	pushq_seg_cfi_r %ds, %rax
	pushq_seg_cfi_r %es, %rax
	pushq_cfi_r %fs
	pushq_cfi_r %gs

	/* struct x86_64_va_list_reg_save_area */
	pushq_cfi %r9
	pushq_cfi %r8
	pushq_cfi %rcx
	pushq_cfi %rdx
	pushq_cfi %rsi

	/* `rsa_rdi' is already consumed by `char const *format' */
	/* x86_64_va_list_struct */
	leaq   -8(%rsp), %rax
	pushq_cfi %rax   /* vl_reg_save_area */
	leaq   (8+(8*5)+SIZEOF_UCPUSTATE+8)(%rsp), %rax
	pushq_cfi %rax   /* vl_overflow_arg_area */
	pushq_cfi $(304) /* No FP-registers */
	pushq_cfi $(1*8) /* 1 GP registers already in use */
	movq   %rsp, %rdx                  /* __builtin_va_list args */
	movq   %rdi, %rsi                  /* char const *format */
	leaq   ((8*3)+8+(8*5))(%rsp), %rdi /* struct ucpustate *__restrict state */

	PUBLIC(kernel_vpanic_ucpustate)
	call   kernel_vpanic_ucpustate
	.cfi_endproc
END(kernel_panic)
