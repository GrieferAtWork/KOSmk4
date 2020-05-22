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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_DEBUGGER_ISR32_S
#define GUARD_KERNEL_CORE_ARCH_I386_DEBUGGER_ISR32_S 1

#include <debugger/config.h>

#ifdef CONFIG_HAVE_DEBUGGER
#include <kernel/compiler.h>

#include <kernel/x86/apic.h>
#include <kernel/x86/pic.h>

#include <asm/cfi.h>
#include <asm/cpu-flags.h>
#include <kos/kernel/cpu-state.h>
#include <kos/kernel/gdt.h>



.section .text.cold
INTERN_FUNCTION(x86_dbgidt_pagefault)
	.cfi_startproc simple
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 4 /* Adjust for the error code. */
	popl_cfi %ss:-(12 + SIZEOF_GPREGS + 4)(%esp) /* ECODE */
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	pushal_cfi_r
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	movl   -4(%esp), %edx /* ECODE */
	movl   %esp, %ecx
	EXTERN(x86_handle_dbg_pagefault)
	call   x86_handle_dbg_pagefault
	movl   %eax, %esp
	popal_cfi_r
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(x86_dbgidt_pagefault)



.section .text.cold
INTERN_FUNCTION(x86_dbgidt_apic_ipi)
	.cfi_startproc simple
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0

	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12

	pushl_cfi_r %eax
	pushl_cfi_r %ecx
	pushl_cfi_r %edx

	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs

	/* Achnowledge the IPI. */
	EXTERN(x86_lapicbase)
	movl   x86_lapicbase, %eax
	movl   $(APIC_EOI_FSIGNAL), APIC_EOI(%eax)

	/* Deal with the interrupt */
	EXTERN(x86_dbg_handle_altcore_interrupt)
	call   x86_dbg_handle_altcore_interrupt

	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi_r %eax

	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds

	iret
	.cfi_endproc
END(x86_dbgidt_apic_ipi)


.section .text.cold
INTERN_FUNCTION(x86_dbgidt_specific_00h) /* ISR_X86_f1 */
	.cfi_startproc simple
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0

	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12

	pushl_cfi_r %eax
	pushl_cfi_r %ecx
	pushl_cfi_r %edx

	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs

	EXTERN(x86_handle_dbg_ps2_interrupt)
	call   x86_handle_dbg_ps2_interrupt

	/* outb(X86_PIC1_CMD, X86_PIC_CMD_EOI); */
	movb   $(X86_PIC_CMD_EOI), %al
	outb   %al, $(X86_PIC1_CMD)

	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi_r %eax

	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds

	iret
	.cfi_endproc
END(x86_dbgidt_specific_00h)

#ifndef __INTELLISENSE__
#include "isr.S"
#endif /* !__INTELLISENSE__ */

#endif /* CONFIG_HAVE_DEBUGGER */

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_DEBUGGER_ISR32_S */
