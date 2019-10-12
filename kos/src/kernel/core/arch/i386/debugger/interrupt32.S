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

#include <kernel/debugger.h>

#ifndef CONFIG_NO_DEBUGGER
#include <kernel/compiler.h>
#include <kernel/pic.h>
#include <kernel/apic.h>
#include <asm/cpu-flags.h>
#include <asm/cfi.h>
#include <kos/kernel/gdt.h>
#include <kos/kernel/cpu-state.h>


.section .text.cold
INTERN_FUNCTION(x86_debug_asmirq_f1)
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

	INTERN(x86_debug_ps2_interrupt)
	call   x86_debug_ps2_interrupt

	/* outb(X86_PIC1_CMD,X86_PIC_CMD_EOI); */
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
END(x86_debug_asmirq_f1)


.section .text.cold
INTERN_FUNCTION(x86_debug_asmirq_f0)
	.cfi_startproc simple
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0

	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4

	pushl_cfi_r %eax
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	/* Acknowledge the interrupt. */
INTERN_FUNCTION(x86_debug_pic_acknowledge)
	.byte  0x90, 0x90, 0x90, 0x90, 0x90
	.byte  0x90, 0x90, 0x90, 0x90, 0x90
	.byte  0x90, 0x90, 0x90, 0x90, 0x90
END(x86_debug_pic_acknowledge)
	popl_cfi_r %eax

	popl_cfi %ds
	.cfi_restore_iret_ds

	iret
	.cfi_endproc
END(x86_debug_asmirq_f0)





#define INTERRUPT_TYPE_NORMAL 0 /* Normal interrupt */
#define INTERRUPT_TYPE_ERROR  1 /* This interrupt pushes an error code onto the stack. */
#define INTERRUPT_TYPE_SPUR1  2 /* This interrupt may happen spuriously (PIC#1). */
#define INTERRUPT_TYPE_SPUR2  3 /* This interrupt may happen spuriously (PIC#2). */

.macro define_interrupt id, dpl=0, type=INTERRUPT_TYPE_NORMAL
	.hidden x86_debug_asmirq_\id
	.global x86_debug_asmirq_\id
	.type   x86_debug_asmirq_\id, @function
	.hidden x86_debug_irqdpl_\id
	.global x86_debug_irqdpl_\id
x86_debug_irqdpl_\id = \dpl
	.section .text.x86.asmirq.debug.\id
x86_debug_asmirq_\id:
	.cfi_startproc simple
	.cfi_iret_signal_frame
.if \type == INTERRUPT_TYPE_ERROR
	.cfi_def_cfa %esp, 4 /* Adjust for the error code. */
	popl_cfi %ss:-(12 + SIZEOF_GPREGS + 4)(%esp) /* ECODE */
.else
	.cfi_def_cfa %esp, 0
.endif
	/* Check for spurios interrupts */
.if \type == INTERRUPT_TYPE_SPUR1
	call    x86_check_spurious_interrupt_PIC1
.elseif \type == INTERRUPT_TYPE_SPUR2
	call    x86_check_spurious_interrupt_PIC2
.endif

	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12

	pushal_cfi_r
	/* Load segment registers, as expected in kernel-space */
	movw    $(SEGMENT_USER_DATA_RPL), %ax
	movw    %ax, %ds
	movw    %ax, %es
	movw    $(SEGMENT_KERNEL_FSBASE), %ax
	movw    %ax, %fs
.if \type == INTERRUPT_TYPE_ERROR
	movl    -4(%esp), %edx /* ECODE */
.endif
	movl    %esp, %ecx
	/* Invoke the high-level C-function */
	call    x86_debug_cirq_\id
	movl    %eax, %esp
	/* Start restoring registers. */
	popal_cfi_r

	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds

	iret
	.cfi_endproc
.size x86_debug_asmirq_\id, . - x86_debug_asmirq_\id
.endm


define_interrupt 0e, 0, INTERRUPT_TYPE_ERROR /* #PF  Page Fault. */








#endif /* !CONFIG_NO_DEBUGGER */

