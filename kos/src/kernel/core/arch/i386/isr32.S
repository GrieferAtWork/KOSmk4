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
#define __ASSEMBLER__ 1
#include <hybrid/compiler.h>

#include <kernel/arch/isr-config.h>
#include <kernel/arch/isr-names.h>
#include <kernel/idt.h>
#include <kernel/pic.h>

#include <asm/cfi.h>
#include <asm/cpu-flags.h>
#include <kos/kernel/cpu-state32.h>
#include <kos/kernel/gdt.h>
#include <kos/kernel/tss.h>

#include <libunwind/cfi.h>


#define PRIVATE_ISR_VECTOR_ID2(id) 0x##id
#define PRIVATE_ISR_VECTOR_ID(id) PRIVATE_ISR_VECTOR_ID2(id)
#define ISR_VECTOR_ID PRIVATE_ISR_VECTOR_ID(ISR_VECTOR)

#define PRIVATE_ISR_VECTOR_NAME2(id) ISR_X86_##id
#define PRIVATE_ISR_VECTOR_NAME(id) PRIVATE_ISR_VECTOR_NAME2(id)
#define ISR_VECTOR_NAME PRIVATE_ISR_VECTOR_NAME(ISR_VECTOR)

.macro _isr_set_impl_section prefix:req, id:req
.section .text.x86.\prefix.\id
.endm

#define ISR_HANDLER_SETDPL(dpl)                      \
	INTERN(PP_CAT2(__x86_defdpl_, ISR_VECTOR_NAME)); \
	.set PP_CAT2(__x86_defdpl_, ISR_VECTOR_NAME), dpl;
#define ISR_HANDLER_BEGIN                          \
	_isr_set_impl_section asmirq, ISR_VECTOR_NAME; \
	INTERN_FUNCTION(PP_CAT2(__x86_defisr_, ISR_VECTOR_NAME))
#define ISR_HANDLER_END \
	END(PP_CAT2(__x86_defisr_, ISR_VECTOR_NAME))


#ifndef __INTELLISENSE__
#define ISR_EXCEPT_IMPL   "isr32-exception.S"
#define ISR_WINSPEC_IMPL  "isr32-exception.S"
#define ISR_GENERIC_IMPL  "isr32-dynamic.S"
#define ISR_SPECIFIC_IMPL "isr32-dynamic.S"
#include "isr-foreach.h"
#endif /* !__INTELLISENSE__ */

.section .text.cold
.cfi_startproc
.cfi_iret_signal_frame
PRIVATE_FUNCTION(__x86_isr_unused_common)
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
	subl   $4, %esp   /* VECNO */
	.cfi_adjust_cfa_offset 4

	INTERN(x86_handle_isr)
	call   x86_handle_isr
	movl   %eax, %esp

	popal_cfi_r
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
END(__x86_isr_unused_common)

#ifndef __INTELLISENSE__
#define ISR_UNUSED_IMPL   "isr32-unused.S"
#include "isr-foreach.h"
#endif /* !__INTELLISENSE__ */
.cfi_endproc

