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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_DEBUGGER_ISR_S
#define GUARD_KERNEL_CORE_ARCH_I386_DEBUGGER_ISR_S 1
#define __ASSEMBLER__ 1

#include <debugger/config.h>

#ifdef CONFIG_HAVE_KERNEL_DEBUGGER
#include <kernel/compiler.h>

#include <kernel/x86/apic.h>
#include <kernel/x86/idt-names.h>
#include <kernel/x86/pic.h>

#include <hybrid/host.h>
#include <hybrid/typecore.h>

#include <asm/cfi.h>
#include <asm/cpu-flags.h>
#include <asm/instr/compat.h>
#include <asm/instr/interrupt.h>
#include <asm/instr/movzxq.h>
#include <kos/kernel/cpu-state-asm.h>
#include <kos/kernel/cpu-state.h>
#include <kos/kernel/x86/gdt.h>

.section .text.x86.asmirq.x86_dbgaltcoreidt

.cfi_startproc simple
.cfi_iret_signal_frame
.cfi_def_cfa %Psp, 0

#define DEFINE_DBGALTCORE_IDT_OVERRIDE(id)                      \
	INTERN_FUNCTION(PP_CAT2(x86_dbgaltcoreidt_, IDT_X86_##id)); \
		movb   $(0x##id), %al;                                  \
		jmp    x86_dbgaltcore_interrupt;                        \
	END(PP_CAT2(x86_dbgaltcoreidt_, IDT_X86_##id));

/* NT service interrupts. */
DEFINE_DBGALTCORE_IDT_OVERRIDE(20)
DEFINE_DBGALTCORE_IDT_OVERRIDE(21)
DEFINE_DBGALTCORE_IDT_OVERRIDE(22)
DEFINE_DBGALTCORE_IDT_OVERRIDE(23)
DEFINE_DBGALTCORE_IDT_OVERRIDE(24)
DEFINE_DBGALTCORE_IDT_OVERRIDE(25)
DEFINE_DBGALTCORE_IDT_OVERRIDE(26)
DEFINE_DBGALTCORE_IDT_OVERRIDE(27)
DEFINE_DBGALTCORE_IDT_OVERRIDE(28)
DEFINE_DBGALTCORE_IDT_OVERRIDE(29)
DEFINE_DBGALTCORE_IDT_OVERRIDE(2a)
DEFINE_DBGALTCORE_IDT_OVERRIDE(2b)
DEFINE_DBGALTCORE_IDT_OVERRIDE(2c)
DEFINE_DBGALTCORE_IDT_OVERRIDE(2d)
DEFINE_DBGALTCORE_IDT_OVERRIDE(2e)
DEFINE_DBGALTCORE_IDT_OVERRIDE(2f)

/* Unused interrupts. */
DEFINE_DBGALTCORE_IDT_OVERRIDE(30)
DEFINE_DBGALTCORE_IDT_OVERRIDE(31)
DEFINE_DBGALTCORE_IDT_OVERRIDE(32)
DEFINE_DBGALTCORE_IDT_OVERRIDE(33)
DEFINE_DBGALTCORE_IDT_OVERRIDE(34)
DEFINE_DBGALTCORE_IDT_OVERRIDE(35)
DEFINE_DBGALTCORE_IDT_OVERRIDE(36)
DEFINE_DBGALTCORE_IDT_OVERRIDE(37)
DEFINE_DBGALTCORE_IDT_OVERRIDE(38)
DEFINE_DBGALTCORE_IDT_OVERRIDE(39)
DEFINE_DBGALTCORE_IDT_OVERRIDE(3a)
DEFINE_DBGALTCORE_IDT_OVERRIDE(3b)
DEFINE_DBGALTCORE_IDT_OVERRIDE(3c)
DEFINE_DBGALTCORE_IDT_OVERRIDE(3d)
DEFINE_DBGALTCORE_IDT_OVERRIDE(3e)
DEFINE_DBGALTCORE_IDT_OVERRIDE(3f)
DEFINE_DBGALTCORE_IDT_OVERRIDE(40)
DEFINE_DBGALTCORE_IDT_OVERRIDE(41)
DEFINE_DBGALTCORE_IDT_OVERRIDE(42)
DEFINE_DBGALTCORE_IDT_OVERRIDE(43)
DEFINE_DBGALTCORE_IDT_OVERRIDE(44)
DEFINE_DBGALTCORE_IDT_OVERRIDE(45)
DEFINE_DBGALTCORE_IDT_OVERRIDE(46)
DEFINE_DBGALTCORE_IDT_OVERRIDE(47)
DEFINE_DBGALTCORE_IDT_OVERRIDE(48)
DEFINE_DBGALTCORE_IDT_OVERRIDE(49)
DEFINE_DBGALTCORE_IDT_OVERRIDE(4a)
DEFINE_DBGALTCORE_IDT_OVERRIDE(4b)
DEFINE_DBGALTCORE_IDT_OVERRIDE(4c)
DEFINE_DBGALTCORE_IDT_OVERRIDE(4d)
DEFINE_DBGALTCORE_IDT_OVERRIDE(4e)
DEFINE_DBGALTCORE_IDT_OVERRIDE(4f)
DEFINE_DBGALTCORE_IDT_OVERRIDE(50)
DEFINE_DBGALTCORE_IDT_OVERRIDE(51)
DEFINE_DBGALTCORE_IDT_OVERRIDE(52)
DEFINE_DBGALTCORE_IDT_OVERRIDE(53)
DEFINE_DBGALTCORE_IDT_OVERRIDE(54)
DEFINE_DBGALTCORE_IDT_OVERRIDE(55)
DEFINE_DBGALTCORE_IDT_OVERRIDE(56)
DEFINE_DBGALTCORE_IDT_OVERRIDE(57)
DEFINE_DBGALTCORE_IDT_OVERRIDE(58)
DEFINE_DBGALTCORE_IDT_OVERRIDE(59)
DEFINE_DBGALTCORE_IDT_OVERRIDE(5a)
DEFINE_DBGALTCORE_IDT_OVERRIDE(5b)
DEFINE_DBGALTCORE_IDT_OVERRIDE(5c)
DEFINE_DBGALTCORE_IDT_OVERRIDE(5d)
DEFINE_DBGALTCORE_IDT_OVERRIDE(5e)
DEFINE_DBGALTCORE_IDT_OVERRIDE(5f)
DEFINE_DBGALTCORE_IDT_OVERRIDE(60)
DEFINE_DBGALTCORE_IDT_OVERRIDE(61)
DEFINE_DBGALTCORE_IDT_OVERRIDE(62)
DEFINE_DBGALTCORE_IDT_OVERRIDE(63)
DEFINE_DBGALTCORE_IDT_OVERRIDE(64)
DEFINE_DBGALTCORE_IDT_OVERRIDE(65)
DEFINE_DBGALTCORE_IDT_OVERRIDE(66)
DEFINE_DBGALTCORE_IDT_OVERRIDE(67)
DEFINE_DBGALTCORE_IDT_OVERRIDE(68)
DEFINE_DBGALTCORE_IDT_OVERRIDE(69)
DEFINE_DBGALTCORE_IDT_OVERRIDE(6a)
DEFINE_DBGALTCORE_IDT_OVERRIDE(6b)
DEFINE_DBGALTCORE_IDT_OVERRIDE(6c)
DEFINE_DBGALTCORE_IDT_OVERRIDE(6d)
DEFINE_DBGALTCORE_IDT_OVERRIDE(6e)
DEFINE_DBGALTCORE_IDT_OVERRIDE(6f)
DEFINE_DBGALTCORE_IDT_OVERRIDE(70)
DEFINE_DBGALTCORE_IDT_OVERRIDE(71)
DEFINE_DBGALTCORE_IDT_OVERRIDE(72)
DEFINE_DBGALTCORE_IDT_OVERRIDE(73)
DEFINE_DBGALTCORE_IDT_OVERRIDE(74)
DEFINE_DBGALTCORE_IDT_OVERRIDE(75)
DEFINE_DBGALTCORE_IDT_OVERRIDE(76)
DEFINE_DBGALTCORE_IDT_OVERRIDE(77)
DEFINE_DBGALTCORE_IDT_OVERRIDE(78)
DEFINE_DBGALTCORE_IDT_OVERRIDE(79)
DEFINE_DBGALTCORE_IDT_OVERRIDE(7a)
DEFINE_DBGALTCORE_IDT_OVERRIDE(7b)
DEFINE_DBGALTCORE_IDT_OVERRIDE(7c)
DEFINE_DBGALTCORE_IDT_OVERRIDE(7d)
DEFINE_DBGALTCORE_IDT_OVERRIDE(7e)
DEFINE_DBGALTCORE_IDT_OVERRIDE(7f)

/* The system call interrupt. */
DEFINE_DBGALTCORE_IDT_OVERRIDE(80)

/* Generic I/O interrupts. */
DEFINE_DBGALTCORE_IDT_OVERRIDE(81)
DEFINE_DBGALTCORE_IDT_OVERRIDE(82)
DEFINE_DBGALTCORE_IDT_OVERRIDE(83)
DEFINE_DBGALTCORE_IDT_OVERRIDE(84)
DEFINE_DBGALTCORE_IDT_OVERRIDE(85)
DEFINE_DBGALTCORE_IDT_OVERRIDE(86)
DEFINE_DBGALTCORE_IDT_OVERRIDE(87)
DEFINE_DBGALTCORE_IDT_OVERRIDE(88)
DEFINE_DBGALTCORE_IDT_OVERRIDE(89)
DEFINE_DBGALTCORE_IDT_OVERRIDE(8a)
DEFINE_DBGALTCORE_IDT_OVERRIDE(8b)
DEFINE_DBGALTCORE_IDT_OVERRIDE(8c)
DEFINE_DBGALTCORE_IDT_OVERRIDE(8d)
DEFINE_DBGALTCORE_IDT_OVERRIDE(8e)
DEFINE_DBGALTCORE_IDT_OVERRIDE(8f)
DEFINE_DBGALTCORE_IDT_OVERRIDE(90)
DEFINE_DBGALTCORE_IDT_OVERRIDE(91)
DEFINE_DBGALTCORE_IDT_OVERRIDE(92)
DEFINE_DBGALTCORE_IDT_OVERRIDE(93)
DEFINE_DBGALTCORE_IDT_OVERRIDE(94)
DEFINE_DBGALTCORE_IDT_OVERRIDE(95)
DEFINE_DBGALTCORE_IDT_OVERRIDE(96)
DEFINE_DBGALTCORE_IDT_OVERRIDE(97)
DEFINE_DBGALTCORE_IDT_OVERRIDE(98)
DEFINE_DBGALTCORE_IDT_OVERRIDE(99)
DEFINE_DBGALTCORE_IDT_OVERRIDE(9a)
DEFINE_DBGALTCORE_IDT_OVERRIDE(9b)
DEFINE_DBGALTCORE_IDT_OVERRIDE(9c)
DEFINE_DBGALTCORE_IDT_OVERRIDE(9d)
DEFINE_DBGALTCORE_IDT_OVERRIDE(9e)
DEFINE_DBGALTCORE_IDT_OVERRIDE(9f)
DEFINE_DBGALTCORE_IDT_OVERRIDE(a0)
DEFINE_DBGALTCORE_IDT_OVERRIDE(a1)
DEFINE_DBGALTCORE_IDT_OVERRIDE(a2)
DEFINE_DBGALTCORE_IDT_OVERRIDE(a3)
DEFINE_DBGALTCORE_IDT_OVERRIDE(a4)
DEFINE_DBGALTCORE_IDT_OVERRIDE(a5)
DEFINE_DBGALTCORE_IDT_OVERRIDE(a6)
DEFINE_DBGALTCORE_IDT_OVERRIDE(a7)
DEFINE_DBGALTCORE_IDT_OVERRIDE(a8)
DEFINE_DBGALTCORE_IDT_OVERRIDE(a9)
DEFINE_DBGALTCORE_IDT_OVERRIDE(aa)
DEFINE_DBGALTCORE_IDT_OVERRIDE(ab)
DEFINE_DBGALTCORE_IDT_OVERRIDE(ac)
DEFINE_DBGALTCORE_IDT_OVERRIDE(ad)
DEFINE_DBGALTCORE_IDT_OVERRIDE(ae)
DEFINE_DBGALTCORE_IDT_OVERRIDE(af)
DEFINE_DBGALTCORE_IDT_OVERRIDE(b0)
DEFINE_DBGALTCORE_IDT_OVERRIDE(b1)
DEFINE_DBGALTCORE_IDT_OVERRIDE(b2)
DEFINE_DBGALTCORE_IDT_OVERRIDE(b3)
DEFINE_DBGALTCORE_IDT_OVERRIDE(b4)
DEFINE_DBGALTCORE_IDT_OVERRIDE(b5)
DEFINE_DBGALTCORE_IDT_OVERRIDE(b6)
DEFINE_DBGALTCORE_IDT_OVERRIDE(b7)
DEFINE_DBGALTCORE_IDT_OVERRIDE(b8)
DEFINE_DBGALTCORE_IDT_OVERRIDE(b9)
DEFINE_DBGALTCORE_IDT_OVERRIDE(ba)
DEFINE_DBGALTCORE_IDT_OVERRIDE(bb)
DEFINE_DBGALTCORE_IDT_OVERRIDE(bc)
DEFINE_DBGALTCORE_IDT_OVERRIDE(bd)
DEFINE_DBGALTCORE_IDT_OVERRIDE(be)
DEFINE_DBGALTCORE_IDT_OVERRIDE(bf)
DEFINE_DBGALTCORE_IDT_OVERRIDE(c0)
DEFINE_DBGALTCORE_IDT_OVERRIDE(c1)
DEFINE_DBGALTCORE_IDT_OVERRIDE(c2)
DEFINE_DBGALTCORE_IDT_OVERRIDE(c3)
DEFINE_DBGALTCORE_IDT_OVERRIDE(c4)
DEFINE_DBGALTCORE_IDT_OVERRIDE(c5)
DEFINE_DBGALTCORE_IDT_OVERRIDE(c6)
DEFINE_DBGALTCORE_IDT_OVERRIDE(c7)
DEFINE_DBGALTCORE_IDT_OVERRIDE(c8)
DEFINE_DBGALTCORE_IDT_OVERRIDE(c9)
DEFINE_DBGALTCORE_IDT_OVERRIDE(ca)
DEFINE_DBGALTCORE_IDT_OVERRIDE(cb)
DEFINE_DBGALTCORE_IDT_OVERRIDE(cc)
DEFINE_DBGALTCORE_IDT_OVERRIDE(cd)
DEFINE_DBGALTCORE_IDT_OVERRIDE(ce)
DEFINE_DBGALTCORE_IDT_OVERRIDE(cf)
DEFINE_DBGALTCORE_IDT_OVERRIDE(d0)
DEFINE_DBGALTCORE_IDT_OVERRIDE(d1)
DEFINE_DBGALTCORE_IDT_OVERRIDE(d2)
DEFINE_DBGALTCORE_IDT_OVERRIDE(d3)
DEFINE_DBGALTCORE_IDT_OVERRIDE(d4)
DEFINE_DBGALTCORE_IDT_OVERRIDE(d5)
DEFINE_DBGALTCORE_IDT_OVERRIDE(d6)
DEFINE_DBGALTCORE_IDT_OVERRIDE(d7)
DEFINE_DBGALTCORE_IDT_OVERRIDE(d8)
DEFINE_DBGALTCORE_IDT_OVERRIDE(d9)
DEFINE_DBGALTCORE_IDT_OVERRIDE(da)
DEFINE_DBGALTCORE_IDT_OVERRIDE(db)
DEFINE_DBGALTCORE_IDT_OVERRIDE(dc)
DEFINE_DBGALTCORE_IDT_OVERRIDE(dd)
DEFINE_DBGALTCORE_IDT_OVERRIDE(de)
DEFINE_DBGALTCORE_IDT_OVERRIDE(df)
DEFINE_DBGALTCORE_IDT_OVERRIDE(e0)
DEFINE_DBGALTCORE_IDT_OVERRIDE(e1)
DEFINE_DBGALTCORE_IDT_OVERRIDE(e2)
DEFINE_DBGALTCORE_IDT_OVERRIDE(e3)
DEFINE_DBGALTCORE_IDT_OVERRIDE(e4)
DEFINE_DBGALTCORE_IDT_OVERRIDE(e5)
DEFINE_DBGALTCORE_IDT_OVERRIDE(e6)
DEFINE_DBGALTCORE_IDT_OVERRIDE(e7)
DEFINE_DBGALTCORE_IDT_OVERRIDE(e8)
DEFINE_DBGALTCORE_IDT_OVERRIDE(e9)
DEFINE_DBGALTCORE_IDT_OVERRIDE(ea)
DEFINE_DBGALTCORE_IDT_OVERRIDE(eb)
DEFINE_DBGALTCORE_IDT_OVERRIDE(ec)
DEFINE_DBGALTCORE_IDT_OVERRIDE(ed)

/* PIC interrupts (NOTE: `IDT_X86_f0' is also a PIC interrupt). */
DEFINE_DBGALTCORE_IDT_OVERRIDE(f1)
DEFINE_DBGALTCORE_IDT_OVERRIDE(f2)
DEFINE_DBGALTCORE_IDT_OVERRIDE(f3)
DEFINE_DBGALTCORE_IDT_OVERRIDE(f4)
DEFINE_DBGALTCORE_IDT_OVERRIDE(f5)
DEFINE_DBGALTCORE_IDT_OVERRIDE(f6)
DEFINE_DBGALTCORE_IDT_OVERRIDE(f7)
//DEFINE_DBGALTCORE_IDT_OVERRIDE(f8) /* FIXME: Work-around so the clock keeps on working */
DEFINE_DBGALTCORE_IDT_OVERRIDE(f9)
DEFINE_DBGALTCORE_IDT_OVERRIDE(fa)
DEFINE_DBGALTCORE_IDT_OVERRIDE(fb)
DEFINE_DBGALTCORE_IDT_OVERRIDE(fc)
DEFINE_DBGALTCORE_IDT_OVERRIDE(fd)
//DEFINE_DBGALTCORE_IDT_OVERRIDE(fe) /* FIXME: Work-around so disk-io keep on working */
//DEFINE_DBGALTCORE_IDT_OVERRIDE(ff) /* FIXME: Work-around so disk-io keep on working */


INTERN_FUNCTION(x86_dbgaltcore_interrupt)
	cli /* Ensure that all overwritten vectors are handled without interrupts enabled! */
	/* NOTE: %al = VECTOR_NUMBER.
	 *  -> All other registers must be preserved. */
#ifdef __x86_64__
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11

	/* Handle the interrupt */
	movzbq %al, %rdi
	EXTERN(x86_dbg_altcore_interrupt)
	call   x86_dbg_altcore_interrupt

	popq_cfi_r %r11
	popq_cfi_r %r10
	popq_cfi_r %r9
	popq_cfi_r %r8
	popq_cfi_r %rsi
	popq_cfi_r %rdi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
#else /* __x86_64__ */
	pushl_cfi_r %ecx
	pushl_cfi_r %edx

	/* Handle the interrupt */
	movzbl %al, %ecx
	EXTERN(x86_dbg_altcore_interrupt)
	call   x86_dbg_altcore_interrupt

	popl_cfi_r %edx
	popl_cfi_r %ecx
#endif /* !__x86_64__ */
	iretP
END(x86_dbgaltcore_interrupt)
.cfi_endproc



#ifdef __x86_64__
#define FOREACH_CLOBBER_pushP_cfi_r                            \
	pushq_cfi_r %rax;   /* [C] Accumulator register */         \
	pushq_cfi_r %rcx;   /* [C] Count register */               \
	pushq_cfi_r %rdx;   /* [C] Data register */                \
	pushq_cfi_r %rsi;   /* [C] Source pointer */               \
	pushq_cfi_r %rdi;   /* [C] Destination pointer */          \
	pushq_cfi_r %r8;    /* [C] General purpose register #8 */  \
	pushq_cfi_r %r9;    /* [C] General purpose register #9 */  \
	pushq_cfi_r %r10;   /* [C] General purpose register #10 */ \
	pushq_cfi_r %r11;   /* [C] General purpose register #11 */
#define FOREACH_CLOBBER_popP_cfi_r                             \
	popq_cfi_r %r11;    /* [C] General purpose register #11 */ \
	popq_cfi_r %r10;    /* [C] General purpose register #10 */ \
	popq_cfi_r %r9;     /* [C] General purpose register #9 */  \
	popq_cfi_r %r8;     /* [C] General purpose register #8 */  \
	popq_cfi_r %rdi;    /* [C] Destination pointer */          \
	popq_cfi_r %rsi;    /* [C] Source pointer */               \
	popq_cfi_r %rdx;    /* [C] Data register */                \
	popq_cfi_r %rcx;    /* [C] Count register */               \
	popq_cfi_r %rax     /* [C] Accumulator register */
#else /* __x86_64__ */
#define FOREACH_CLOBBER_pushP_cfi_r \
	pushl_cfi_r %eax;               \
	pushl_cfi_r %ecx;               \
	pushl_cfi_r %edx
#define FOREACH_CLOBBER_popP_cfi_r \
	popl_cfi_r %edx;               \
	popl_cfi_r %ecx;               \
	popl_cfi_r %eax
#endif /* !__x86_64__ */


#ifdef __x86_64__
#define x86_idt_apic_ipi_icpustate_Psp x86_idt_apic_ipi_icpustate_rsp
#else /* __x86_64__ */
#define x86_idt_apic_ipi_icpustate_Psp x86_idt_apic_ipi_icpustate_esp
#endif /* !__x86_64__ */




.section .text.x86.asmirq.x86_dbgidt_apic_ipi
INTERN_FUNCTION(x86_dbgidt_apic_ipi)
	.cfi_startproc
	.cfi_iret_signal_frame
	.cfi_def_cfa %Psp, 0
#ifdef __x86_64__
	cli
	ASM_PUSH_ICPUSTATE_AFTER_IRET_CFI_R
#else /* __x86_64__ */
	ASM_PUSH_ICPUSTATE_AFTER_HW_IRET_CFI_R
	/* Load kernel-space segments. */
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
#endif /* !__x86_64__ */

	/* Achnowledge the IPI. */
	EXTERN(x86_lapicbase)
	movP   x86_lapicbase, %Pax
	movl   $(APIC_EOI_FSIGNAL), APIC_EOI(%Pax)

	/* Deal with the interrupt */
	EXTERN(x86_dbg_handle_altcore_interrupt)
	call   x86_dbg_handle_altcore_interrupt

	/* Do normal APIC-IPI handling (ala. cpu_sendipi())
	 * This  is still required,  because other CPUs  will only send HW-ipis
	 * to us if we keep on handling SW-based IPIs, meaning that we'll  only
	 * get IPI-related interrupts if we're nice and handling SW-based ones!
	 *
	 * Also: Since we're  in debug-mode,  and the  specific CPU  that's
	 *       responsible for controlling the system at the moment,  any
	 *       IPI that gets back to us should really be as the result of
	 *       us requesting some sort of data (such as disk I/O, or  the
	 *       like...) */
	EXTERN(x86_idt_apic_ipi_icpustate_Psp)
	jmp    x86_idt_apic_ipi_icpustate_Psp
	.cfi_endproc
END(x86_dbgidt_apic_ipi)



.section .text.x86.asmirq.x86_dbgidt_specific_00h
INTERN_FUNCTION(x86_dbgidt_specific_00h) /* ISR_X86_f1 */
	.cfi_startproc simple
	.cfi_iret_signal_frame
	.cfi_def_cfa %Psp, 0
#ifdef __x86_64__
	cli
#else /* __x86_64__ */
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
#endif /* !__x86_64__ */

	FOREACH_CLOBBER_pushP_cfi_r

#ifndef __x86_64__
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
#endif /* !__x86_64__ */

	EXTERN(x86_handle_dbg_ps2_interrupt)
	call   x86_handle_dbg_ps2_interrupt

	/* outb(X86_PIC1_CMD, X86_PIC_CMD_EOI); */
	movb   $(X86_PIC_CMD_EOI), %al
	outb   %al, $(X86_PIC1_CMD)

	FOREACH_CLOBBER_popP_cfi_r
#ifndef __x86_64__
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
#endif /* !__x86_64__ */
	iretP
	.cfi_endproc
END(x86_dbgidt_specific_00h)



#endif /* CONFIG_HAVE_KERNEL_DEBUGGER */

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_DEBUGGER_ISR_S */
