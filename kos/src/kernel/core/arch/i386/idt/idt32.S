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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_IDT_IDT32_S
#define GUARD_KERNEL_CORE_ARCH_I386_IDT_IDT32_S 1
#define __ASSEMBLER__ 1

#include <hybrid/compiler.h>

#include <kernel/x86/fault.h>
#include <kernel/x86/idt-names.h>
#include <kernel/x86/idt.h>
#include <kernel/x86/pic.h>

#include <asm/cfi.h>
#include <asm/cpu-flags.h>
#include <kos/kernel/bits/cpu-state-asm32.h>
#include <kos/kernel/bits/cpu-state32.h>
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
#define IDT_HANDLER_BEGIN                          \
	_idt_set_impl_section asmirq, IDT_VECTOR_NAME; \
	INTERN_FUNCTION(PP_CAT2(x86_idt_, IDT_VECTOR_NAME))
#define IDT_HANDLER_END \
	END(PP_CAT2(x86_idt_, IDT_VECTOR_NAME))


#ifndef __INTELLISENSE__
#define IDT_EXCEPT_IMPL   "idt32-exception.S"
#define IDT_WINSPEC_IMPL  "idt32-exception.S"
#define IDT_GENERIC_IMPL  "idt32-dynamic.S"
#define IDT_SPECIFIC_IMPL "idt32-dynamic.S"
#include "foreach.h"
#endif /* !__INTELLISENSE__ */

.section .text.cold
.cfi_startproc
.cfi_iret_signal_frame
PRIVATE_FUNCTION(x86_idt_unused_common)
	.cfi_def_cfa %esp, 4
	popl_cfi %ss:-(12 + SIZEOF_GPREGS + 4)(%esp) /* VECNO */
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	pushal_cfi_r
	movl   %esp, %ecx /* struct icpustate *state */
	xorl   %edx, %edx /* uintptr_t ecode */
	subl   $(4), %esp /* VECNO */
	.cfi_adjust_cfa_offset 4

	EXTERN(x86_handle_unhandled_idt)
	call   x86_handle_unhandled_idt
	movl   %eax, %esp

	popal_cfi_r
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
END(x86_idt_unused_common)

#ifndef __INTELLISENSE__
#define IDT_UNUSED_IMPL   "idt32-unused.S"
#include "foreach.h"
#endif /* !__INTELLISENSE__ */
.cfi_endproc

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_IDT_IDT32_S */
