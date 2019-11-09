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

#ifndef VECTOR
#error "Must #define VECTOR ... before #include-ing this file"
#endif

#ifndef FUNC
#define FUNC3(x, y) x ## y
#define FUNC2(x, y) FUNC3(x, y)
#define FUNC(x)     FUNC2(x, VECTOR)
#define VECTOR_ID   FUNC(0x)
#endif /* !FUNC */

#ifndef SECTION_MACRO_DEFINED
#define SECTION_MACRO_DEFINED 1
.macro SET_ASMIRQ_SECTION vector:req
.section .text.x86.asmisr.\vector
.endm
#endif


SET_ASMIRQ_SECTION VECTOR
INTERN_FUNCTION(FUNC(x86_asmirq_))
	.cfi_startproc simple
	.cfi_iret_signal_frame
	.cfi_def_cfa %rsp, 0
	intr_enter  INTR

	pushq_cfi_r %rax    /* [C] Accumulator register */
	pushq_cfi_r %rcx    /* [C] Count register */
	pushq_cfi_r %rdx    /* [C] Data register */
	pushq_cfi_r %rsi    /* [C] Source pointer */
	pushq_cfi_r %rdi    /* [C] Destination pointer */
	pushq_cfi_r %r8     /* [C] General purpose register #8 */
	pushq_cfi_r %r9     /* [C] General purpose register #9 */
	pushq_cfi_r %r10    /* [C] General purpose register #10 */
	pushq_cfi_r %r11    /* [C] General purpose register #11 */

#if VECTOR_ID == 0xf7
	/* SPUR#1 */
#define HAVE_SPURIOUS_FAULT 1
	.cfi_remember_state
	movb   $(X86_PIC_READ_ISR), %al
	outb   %al,      $(X86_PIC1_CMD) /* outb(X86_PIC1_CMD, X86_PIC_READ_ISR); */
	inb    $(X86_PIC2_CMD),     %al
	testb  $0x80,               %al
	jnz    99f /* if (!(inb(X86_PIC2_CMD) & 0x80)) goto 99f; */
#elif VECTOR_ID == 0xff
	/* SPUR#2 */
#define HAVE_SPURIOUS_FAULT 1
	.cfi_remember_state
	movb   $(X86_PIC_READ_ISR), %al
	outb   %al,      $(X86_PIC2_CMD) /* outb(X86_PIC2_CMD, X86_PIC_READ_ISR); */
	inb    $(X86_PIC2_CMD),     %al
	testb  $0x80,               %al
	jz     99f /* if (!(inb(X86_PIC2_CMD) & 0x80)) goto 99f; */
#endif

	/* Signal EOI */
#if VECTOR_ID >= X86_INTERRUPT_PIC1_BASE
	movb   $(X86_PIC_CMD_EOI), %al
#if VECTOR_ID >= X86_INTERRUPT_PIC2_BASE
	outb   %al,      $(X86_PIC2_CMD) /* outb(X86_PIC2_CMD, X86_PIC_CMD_EOI); */
#endif /* VECTOR_ID >= X86_INTERRUPT_PIC2_BASE */
	outb   %al,      $(X86_PIC1_CMD) /* outb(X86_PIC1_CMD, X86_PIC_CMD_EOI); */
#endif /* VECTOR_ID >= X86_INTERRUPT_PIC1_BASE */

	/* Invoke the C-level ISR callback */
	INTERN(FUNC(kernel_isr))
	call   FUNC(kernel_isr)

#ifdef HAVE_SPURIOUS_FAULT
98:
#endif /* HAVE_SPURIOUS_FAULT */
	popq_cfi_r %rax    /* [C] Accumulator register */
	popq_cfi_r %rcx    /* [C] Count register */
	popq_cfi_r %rdx    /* [C] Data register */
	popq_cfi_r %rsi    /* [C] Source pointer */
	popq_cfi_r %rdi    /* [C] Destination pointer */
	popq_cfi_r %r8     /* [C] General purpose register #8 */
	popq_cfi_r %r9     /* [C] General purpose register #9 */
	popq_cfi_r %r10    /* [C] General purpose register #10 */
	popq_cfi_r %r11    /* [C] General purpose register #11 */

	intr_exit

#ifdef HAVE_SPURIOUS_FAULT
#undef HAVE_SPURIOUS_FAULT
	.cfi_restore_state
99:	pushq_cfi $98b
#if VECTOR_ID == 0xf7
	INTERN(x86_pic1_spur)
	jmp    x86_pic1_spur
#else /* VECTOR_ID == 0xf7 */
	INTERN(x86_pic2_spur)
	jmp    x86_pic2_spur
#endif /* VECTOR_ID != 0xf7 */
#endif /* HAVE_SPURIOUS_FAULT */
	.cfi_endproc
END(FUNC(x86_asmirq_))

#undef VECTOR
