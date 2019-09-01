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
#include <kos/kernel/cpu-state.h>
#include <asm/cfi.h>
#include <kernel/gdt.h>

.section .text
INTERN_FUNCTION(GDBX86RemoteInterrupt_AsmHandler)
	.cfi_startproc simple
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0

	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12

	pushal_cfi_r

	/* Load kernel-space segments. */
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs

	movl   %esp, %ecx
	INTERN(GDBX86RemoteInterrupt_CHandler)
	call   *GDBX86RemoteInterrupt_CHandler

	/* Check if `(*GDBX86RemoteInterrupt_CHandler)()' returned NULL,
	 * which is used to indicate that the interrupt was not meant
	 * for the communications handler */
	testl  %eax, %eax
	.cfi_remember_state
	jz     .Lcall_orig_handler

	popal_cfi_r

	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds

	iret

	.cfi_restore_state
.Lcall_orig_handler:
	/* Invoke the original interrupt handler. */
	INTERN(GDBX86RemoteInterrupt_GetOriginalHandler)
	call   GDBX86RemoteInterrupt_GetOriginalHandler
	movw   OFFSET_ICPUSTATE_DS(%esp), %cx /* %ds */
	movw   %cx, %ds
	.cfi_restore_iret_ds
	movl   %eax, %ss:OFFSET_ICPUSTATE_DS(%esp) /* Return address */

	popal_cfi_r

	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es

	ret    /* This used to be %ds, but we overwrote it with the return value
	        * of `GDBX86RemoteInterrupt_GetOriginalHandler()', so that we jump
	        * to the original interrupt handler with the IRET tail still in-tact,
	        * and all other registers restored to their old values. */
	.cfi_endproc
END(GDBX86RemoteInterrupt_AsmHandler)



.section .text
INTERN_FUNCTION(GDBX86Interrupt_AsmInt1Handler)
	/* INTERN void ASMCALL GDBX86Interrupt_AsmInt1Handler(void); */
	.cfi_startproc simple
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	pushal_cfi_r

	/* Load kernel-space segments. */
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs

	movl   %esp, %ecx
	INTERN(GDBX86Interrupt_Int1Handler)
	call   GDBX86Interrupt_Int1Handler
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
END(GDBX86Interrupt_AsmInt1Handler)


.section .text
INTERN_FUNCTION(GDBX86Interrupt_AsmInt3Handler)
	/* INTERN void ASMCALL GDBX86Interrupt_AsmInt3Handler(void); */
	.cfi_startproc simple
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	pushal_cfi_r

	/* Load kernel-space segments. */
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs

	movl   %esp, %ecx
	INTERN(GDBX86Interrupt_Int3Handler)
	call   GDBX86Interrupt_Int3Handler
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
END(GDBX86Interrupt_AsmInt3Handler)


