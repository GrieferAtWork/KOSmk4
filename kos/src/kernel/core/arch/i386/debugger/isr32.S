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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_DEBUGGER_ISR32_S
#define GUARD_KERNEL_CORE_ARCH_I386_DEBUGGER_ISR32_S 1

#include <debugger/config.h>

#ifdef CONFIG_HAVE_DEBUGGER
#include <kernel/compiler.h>
#include <kernel/pic.h>
#include <kernel/apic.h>
#include <asm/cpu-flags.h>
#include <asm/cfi.h>
#include <kos/kernel/gdt.h>
#include <kos/kernel/cpu-state.h>



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


/* TODO: Override all of the generic ISR handlers
 *        - `x86_dbgidt_generic_00h'
 *        - `x86_dbgidt_generic_01h'
 *        - `x86_dbgidt_generic_??h'
 *        - `x86_dbgidt_generic_6ch'
 *       and queue them being serviced until
 *       the debugger is eventually exited. */



#endif /* CONFIG_HAVE_DEBUGGER */

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_DEBUGGER_ISR32_S */
