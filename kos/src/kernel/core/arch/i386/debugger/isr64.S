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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_DEBUGGER_ISR64_S
#define GUARD_KERNEL_CORE_ARCH_I386_DEBUGGER_ISR64_S 1

#include <debugger/config.h>

#ifdef CONFIG_HAVE_DEBUGGER
#include <kernel/compiler.h>

#include <kernel/arch/apic.h>
#include <kernel/arch/pic.h>

#include <asm/cfi.h>
#include <asm/cpu-flags.h>
#include <asm/instr/interrupt.h>
#include <kos/kernel/cpu-state-asm.h>
#include <kos/kernel/cpu-state.h>
#include <kos/kernel/gdt.h>


.section .text.cold
INTERN_FUNCTION(x86_dbgidt_pagefault)
	.cfi_startproc simple
	.cfi_iret_signal_frame
	.cfi_def_cfa %rsp, 8 /* Adjust for the error code. */
	popq_cfi -(SIZEOF_GPREGSNSP + 8)(%rsp) /* ECODE */
	intr_enter INTR
	ASM_PUSH_ICPUSTATE_AFTER_IRET_CFI_R
	movq   -8(%rsp), %rsi /* ECODE */
	movq   %rsp, %rdi
	EXTERN(x86_handle_dbg_pagefault)
	call   x86_handle_dbg_pagefault
	movq   %rax, %rsp
	ASM_POP_ICPUSTATE_BEFORE_IRET_CFI_R
	intr_exit
	.cfi_endproc
END(x86_dbgidt_pagefault)



.section .text.cold
INTERN_FUNCTION(x86_dbgidt_apic_ipi)
	.cfi_startproc simple
	.cfi_iret_signal_frame
	.cfi_def_cfa %rsp, 0
	intr_enter INTR

	/* Save scratch registers */
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %rax

	/* Achnowledge the IPI. */
	EXTERN(x86_lapicbase)
	movq   x86_lapicbase, %rax
	movl   $(APIC_EOI_FSIGNAL), APIC_EOI(%rax)

	/* Deal with the interrupt */
	EXTERN(x86_dbg_handle_altcore_interrupt)
	call   x86_dbg_handle_altcore_interrupt

	/* Restore scratch registers */
	popq_cfi_r %rax
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	popq_cfi_r %r8
	popq_cfi_r %r9
	popq_cfi_r %r10
	popq_cfi_r %r11

	intr_exit
	.cfi_endproc
END(x86_dbgidt_apic_ipi)


.section .text.cold
INTERN_FUNCTION(x86_dbgidt_specific_00h) /* ISR_X86_f1 */
	.cfi_startproc simple
	.cfi_iret_signal_frame
	.cfi_def_cfa %rsp, 0
	intr_enter INTR

	/* Save scratch registers */
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %rax

	EXTERN(x86_handle_dbg_ps2_interrupt)
	call   x86_handle_dbg_ps2_interrupt

	/* outb(X86_PIC1_CMD,X86_PIC_CMD_EOI); */
	movb   $(X86_PIC_CMD_EOI), %al
	outb   %al, $(X86_PIC1_CMD)

	/* Restore scratch registers */
	popq_cfi_r %rax
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	popq_cfi_r %r8
	popq_cfi_r %r9
	popq_cfi_r %r10
	popq_cfi_r %r11

	intr_exit
	.cfi_endproc
END(x86_dbgidt_specific_00h)

#ifndef __INTELLISENSE__
#include "isr.S"
#endif /* !__INTELLISENSE__ */

#endif /* CONFIG_HAVE_DEBUGGER */

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_DEBUGGER_ISR64_S */
