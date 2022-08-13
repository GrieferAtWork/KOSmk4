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
#ifndef GUARD_MODGDBSERVER_ARCH_I386_INTERRUPT32_S
#define GUARD_MODGDBSERVER_ARCH_I386_INTERRUPT32_S 1
#define __ASSEMBLER__ 1

#include <kernel/compiler.h>

#include <kernel/x86/gdt.h>

#include <cfi.h>
#include <kos/kernel/cpu-state.h>

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
	EXTERN(GDBX86Interrupt_Int1Handler)
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
	EXTERN(GDBX86Interrupt_Int3Handler)
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

#endif /* !GUARD_MODGDBSERVER_ARCH_I386_INTERRUPT32_S */
