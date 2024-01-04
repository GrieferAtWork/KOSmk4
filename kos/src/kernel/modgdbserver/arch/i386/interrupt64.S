/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_MODGDBSERVER_ARCH_I386_INTERRUPT64_S
#define GUARD_MODGDBSERVER_ARCH_I386_INTERRUPT64_S 1
#define __ASSEMBLER__ 1

#include <kernel/compiler.h>

#include <kernel/x86/gdt.h>

#include <cfi.h>
#include <asm/instr/interrupt.h>
#include <kos/kernel/cpu-state-asm.h>
#include <kos/kernel/cpu-state.h>

.section .text
INTERN_FUNCTION(GDBX86Interrupt_AsmInt1Handler)
	/* INTERN void ASMCALL GDBX86Interrupt_AsmInt1Handler(void); */
	.cfi_startproc simple
	.cfi_iret_signal_frame
	.cfi_def_cfa %rsp, 0
	intr_enter TRAP
	ASM_PUSH_ICPUSTATE_AFTER_IRET_CFI_R

	movq   %rsp, %rdi
	EXTERN(GDBX86Interrupt_Int1Handler)
	call   GDBX86Interrupt_Int1Handler
	movq   %rax, %rsp

	ASM_POP_ICPUSTATE_BEFORE_IRET_CFI_R
	intr_exit
	.cfi_endproc
END(GDBX86Interrupt_AsmInt1Handler)


.section .text
INTERN_FUNCTION(GDBX86Interrupt_AsmInt3Handler)
	/* INTERN void ASMCALL GDBX86Interrupt_AsmInt3Handler(void); */
	.cfi_startproc simple
	.cfi_iret_signal_frame
	.cfi_def_cfa %rsp, 0
	intr_enter TRAP
	ASM_PUSH_ICPUSTATE_AFTER_IRET_CFI_R

	movq   %rsp, %rdi
	EXTERN(GDBX86Interrupt_Int3Handler)
	call   GDBX86Interrupt_Int3Handler
	movq   %rax, %rsp

	ASM_POP_ICPUSTATE_BEFORE_IRET_CFI_R
	intr_exit
	.cfi_endproc
END(GDBX86Interrupt_AsmInt3Handler)

#endif /* !GUARD_MODGDBSERVER_ARCH_I386_INTERRUPT64_S */
