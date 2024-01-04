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
#ifdef __INTELLISENSE__
#include "idt64.S"
#define IDT_VECTOR 08
#endif /* __INTELLISENSE__ */

#if IDT_CONFIG_GETDPL(IDT_VECTOR_ID) == 3
IDT_HANDLER_SETDPL(3)
#endif /* IDT_CONFIG_GETDPL(IDT_VECTOR_ID) == 3 */

#if IDT_VECTOR_ID == 0x8
IDT_HANDLER_SETIST(1)
#endif /* IDT_VECTOR_ID == 0x8 */

IDT_HANDLER_BEGIN
	.cfi_startproc simple
	.cfi_iret_signal_frame
#if IDT_CONFIG_PUSHESERRORS(IDT_VECTOR_ID)
	.cfi_def_cfa %rsp, 8 /* Adjust for the error code. */
	popq_cfi -(SIZEOF_GPREGSNSP + 8)(%rsp) /* ECODE */
#else /* IDT_CONFIG_PUSHESERRORS(IDT_VECTOR_ID) */
	.cfi_def_cfa %rsp, 0
#endif /* !IDT_CONFIG_PUSHESERRORS(IDT_VECTOR_ID) */
	intr_enter INTR
#if IDT_VECTOR_ID == 0x1
INTERN_LABEL(_x86_idt_debugtrap_after_enter):
#elif IDT_VECTOR_ID == 0x3
INTERN_LABEL(_x86_idt_breakpoint_after_enter):
#endif /* ... */
	ASM_PUSH_ICPUSTATE_AFTER_IRET_CFI_R

#if IDT_CONFIG_PUSHESERRORS(IDT_VECTOR_ID)
	movq   -8(%rsp), %rbx /* uintptr_t ecode (register alias needed for unwinding) */
#endif /* IDT_CONFIG_PUSHESERRORS(IDT_VECTOR_ID) */

	/* Re-enable interrupts for certain exceptions. */
#if IDT_CONFIG_ISTRAP(IDT_VECTOR_ID)
	ttest  mask=EFLAGS_IF, loc=(OFFSET_ICPUSTATE64_IRREGS + OFFSET_IRREGS64_RFLAGS)(%rsp)
	jz     1f
	sti    /* Re-enable interrupts. */
1:
#endif /* TRAP... */

#if IDT_VECTOR_ID == 0x0e
	movq   %cr2, %rbp /* void *addr (register alias needed for unwinding) */
#endif /* IDT_VECTOR_ID == 0x0e */

#if IDT_VECTOR_ID == 0x0e
	.cfi_personality 0, x86_xintr3_userexcept_personality /* preserves: %rsp, %rbx, %rbp */
#elif IDT_CONFIG_PUSHESERRORS(IDT_VECTOR_ID)
	.cfi_personality 0, x86_xintr2_userexcept_personality /* preserves: %rsp, %rbx */
#else /* ... */
	.cfi_personality 0, x86_xintr1_userexcept_personality /* preserves: %rsp */
#endif /* !... */
	.cfi_lsda        0, 1f

1:	movq   %rsp, %rdi  /* struct icpustate *state */
#if IDT_VECTOR_ID == 0x0e
	movq   %rbp, %rdx  /* void *addr */
#endif /* IDT_VECTOR_ID == 0x0e */
#if IDT_CONFIG_PUSHESERRORS(IDT_VECTOR_ID)
	movq   %rbx, %rsi  /* uintptr_t ecode */
#endif /* IDT_CONFIG_PUSHESERRORS(IDT_VECTOR_ID) */

	EXTERN(PP_CAT2(x86_handle_, IDT_VECTOR_NAME))
	call   PP_CAT2(x86_handle_, IDT_VECTOR_NAME)

	ASM_POP_ICPUSTATE_BEFORE_IRET_CFI_R
	intr_exit
	.cfi_endproc
IDT_HANDLER_END


_idt_set_impl_section cirq, IDT_VECTOR_NAME
.weak PP_CAT2(x86_handle_, IDT_VECTOR_NAME)
INTERN_FUNCTION(PP_CAT2(x86_handle_, IDT_VECTOR_NAME))
	.cfi_startproc
#if !IDT_CONFIG_PUSHESERRORS(IDT_VECTOR_ID)
	xorq   %rsi, %rsi /* uintptr_t ecode */
#endif /* IDT_CONFIG_PUSHESERRORS(IDT_VECTOR_ID) */
	movq   $(IDT_VECTOR_ID), %rdx /* uintptr_t vecno */
	EXTERN(x86_handle_unhandled_idt)
	call   x86_handle_unhandled_idt
	ret
	.cfi_endproc
END(PP_CAT2(x86_handle_, IDT_VECTOR_NAME))

#undef IDT_VECTOR
