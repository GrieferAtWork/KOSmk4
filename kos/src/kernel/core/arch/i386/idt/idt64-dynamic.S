/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifdef __INTELLISENSE__
#include "idt64.S"
#define IDT_VECTOR ff
#endif /* __INTELLISENSE__ */

IDT_HANDLER_BEGIN
	.cfi_startproc simple
	.cfi_iret_signal_frame
	.cfi_def_cfa %rsp, 0
	intr_enter INTR

	/* Save scratch registers */
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %rax

#if IDT_VECTOR_ID == 0xf7
	/* SPUR#1 */
#define HAVE_SPURIOUS_FAULT 1
	movb   $(X86_PIC_READ_ISR), %al
	outb   %al, $(X86_PIC1_CMD) /* outb(X86_PIC1_CMD, X86_PIC_READ_ISR); */
	inb    $(X86_PIC2_CMD), %al
	testb  $(0x80), %al
	jnz    99f /* if (!(inb(X86_PIC2_CMD) & 0x80)) goto 99f; */
#elif IDT_VECTOR_ID == 0xff
	/* SPUR#2 */
#define HAVE_SPURIOUS_FAULT 1
	movb   $(X86_PIC_READ_ISR), %al
	outb   %al, $(X86_PIC2_CMD) /* outb(X86_PIC2_CMD, X86_PIC_READ_ISR); */
	inb    $(X86_PIC2_CMD), %al
	testb  $(0x80), %al
	jz     99f /* if (!(inb(X86_PIC2_CMD) & 0x80)) goto 99f; */
#endif

	/* Invoke the C-level ISR handler */
	EXTERN(PP_CAT2(kernel_isr_, IDT_VECTOR_NAME))
	call   PP_CAT2(kernel_isr_, IDT_VECTOR_NAME)

	/* Signal EOI */
#if IDT_VECTOR_ID >= X86_INTERRUPT_PIC1_BASE
	movb   $(X86_PIC_CMD_EOI), %al
#if IDT_VECTOR_ID >= X86_INTERRUPT_PIC2_BASE
	outb   %al, $(X86_PIC2_CMD) /* outb(X86_PIC2_CMD, X86_PIC_CMD_EOI); */
#endif /* IDT_VECTOR_ID >= X86_INTERRUPT_PIC2_BASE */
	outb   %al, $(X86_PIC1_CMD) /* outb(X86_PIC1_CMD, X86_PIC_CMD_EOI); */
#endif /* IDT_VECTOR_ID >= X86_INTERRUPT_PIC1_BASE */

#ifdef HAVE_SPURIOUS_FAULT
98:
	.cfi_remember_state
#endif /* HAVE_SPURIOUS_FAULT */

	/* Restore scratch registers */
	popq_cfi_r %rax
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	popq_cfi_r %r8
	popq_cfi_r %r9
	popq_cfi_r %r10
	popq_cfi_r %r11
	intr_exit

#ifdef HAVE_SPURIOUS_FAULT
#undef HAVE_SPURIOUS_FAULT
	.cfi_restore_state
99:	pushq_cfi $(98b)
#if IDT_VECTOR_ID == 0xf7
	EXTERN(x86_pic1_spur)
	jmp    x86_pic1_spur
#else /* IDT_VECTOR_ID == 0xf7 */
	EXTERN(x86_pic2_spur)
	jmp    x86_pic2_spur
#endif /* IDT_VECTOR_ID != 0xf7 */
#endif /* HAVE_SPURIOUS_FAULT */
	.cfi_endproc
IDT_HANDLER_END


#undef IDT_VECTOR
