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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_IDT_IDT64_S
#define GUARD_KERNEL_CORE_ARCH_I386_IDT_IDT64_S 1
#define __ASSEMBLER__ 1

#include <hybrid/compiler.h>

#include <kernel/x86/idt-names.h>
#include <kernel/x86/idt.h>
#include <kernel/x86/pic.h>

#include <asm/cfi.h>
#include <asm/cpu-flags.h>
#include <asm/instr/interrupt.h>
#include <asm/instr/ttest.h>
#include <kos/kernel/cpu-state-asm.h>
#include <kos/kernel/cpu-state.h>
#include <kos/kernel/x86/gdt.h>
#include <kos/kernel/x86/tss.h>

#include <libunwind/cfi.h>


#define PRIVATE_IDT_VECTOR_ID2(id) 0x##id
#define PRIVATE_IDT_VECTOR_ID(id) PRIVATE_IDT_VECTOR_ID2(id)
#define IDT_VECTOR_ID PRIVATE_IDT_VECTOR_ID(IDT_VECTOR)

#define PRIVATE_IDT_VECTOR_NAME2(id) IDT_X86_##id
#define PRIVATE_IDT_VECTOR_NAME(id) PRIVATE_IDT_VECTOR_NAME2(id)
#define IDT_VECTOR_NAME PRIVATE_IDT_VECTOR_NAME(IDT_VECTOR)

.macro _idt_set_impl_section prefix:req, id:req
.section .text.x86.\prefix\().\id
.endm

#define IDT_HANDLER_SETDPL(dpl)                    \
	INTERN(PP_CAT2(x86_idtdpl_, IDT_VECTOR_NAME)); \
	.set PP_CAT2(x86_idtdpl_, IDT_VECTOR_NAME), dpl;
#define IDT_HANDLER_SETIST(ist)                    \
	INTERN(PP_CAT2(x86_idtist_, IDT_VECTOR_NAME)); \
	.set PP_CAT2(x86_idtist_, IDT_VECTOR_NAME), ist;
#define IDT_HANDLER_BEGIN                          \
	_idt_set_impl_section asmirq, IDT_VECTOR_NAME; \
	INTERN_FUNCTION(PP_CAT2(x86_idt_, IDT_VECTOR_NAME))
#define IDT_HANDLER_END \
	END(PP_CAT2(x86_idt_, IDT_VECTOR_NAME))


#ifndef __INTELLISENSE__
#define IDT_EXCEPT_IMPL   "idt64-exception.S"
#define IDT_WINSPEC_IMPL  "idt64-exception.S"
#define IDT_GENERIC_IMPL  "idt64-dynamic.S"
#define IDT_SPECIFIC_IMPL "idt64-dynamic.S"
#include "foreach.h"
#endif /* !__INTELLISENSE__ */

.section .text.cold
.cfi_startproc
.cfi_iret_signal_frame
PRIVATE_FUNCTION(x86_idt_unused_common)
	.cfi_def_cfa %rsp, 8
	popq_cfi -(SIZEOF_GPREGS64 + 8)(%rsp) /* VECNO */
	intr_enter INTR
	ASM_PUSH_ICPUSTATE_AFTER_IRET_CFI_R
	movq   %rsp, %rdi     /* struct icpustate *state */
	xorq   %rsi, %rsi     /* uintptr_t ecode */
	movq   -8(%rsp), %rdx /* VECNO */

	EXTERN(x86_handle_unhandled_idt)
	call   x86_handle_unhandled_idt
	movq   %rax, %rsp

	ASM_POP_ICPUSTATE_BEFORE_IRET_CFI_R
	intr_exit
END(x86_idt_unused_common)

#ifndef __INTELLISENSE__
#define IDT_UNUSED_IMPL   "idt64-unused.S"
#include "foreach.h"
#endif /* !__INTELLISENSE__ */
.cfi_endproc

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_IDT_IDT64_S */
