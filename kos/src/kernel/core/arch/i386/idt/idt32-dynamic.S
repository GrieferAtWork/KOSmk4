/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifdef __INTELLISENSE__
#include "idt32.S"
#define IDT_VECTOR ff
#endif /* __INTELLISENSE__ */

IDT_HANDLER_BEGIN
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
#endif /* HAVE_SPURIOUS_FAULT */
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

#ifdef HAVE_SPURIOUS_FAULT
#undef HAVE_SPURIOUS_FAULT
	.cfi_def_cfa_offset 24
	.cfi_restore_iret_ds_or_offset -4
	.cfi_restore_iret_es_or_offset -8
	.cfi_restore_iret_fs_or_offset -12
	.cfi_rel_offset %eax, 8
	.cfi_rel_offset %ecx, 4
	.cfi_rel_offset %edx, 0
99:	pushl_cfi $(98b)
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
