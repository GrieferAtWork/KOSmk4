/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_CORE_ARCH_I386_SCHED_APIC_S
#define GUARD_KERNEL_CORE_ARCH_I386_SCHED_APIC_S 1
#define __ASSEMBLER__ 1

#include <kernel/compiler.h>

#include <kernel/arch/apic.h>
#include <kernel/arch/pic.h>
#include <kernel/arch/pit.h>

#include <hybrid/host.h>

#include <asm/instr/compat.h>
#include <asm/instr/jccN.h>
#include <asm/param.h>

#ifdef __x86_64__
#include <asm/instr/movzxq.h>
#endif /* __x86_64__ */

#define SKIPFOR(mystart, minsize)        \
	.if minsize > (. - mystart);         \
	.skip minsize - (. - mystart), 0x90; \
	.endif;




/************************************************************************/
/* APIC IMPLEMENTATION                                                  */
/************************************************************************/

.section .text.free
#define BEGIN_APIC(name) INTERN_FUNCTION(name)
#define END_APIC(name)   INTERN_CONST(name##_size, . - name); END(name)

/* >> FUNDEF NOBLOCK NOPREEMPT WUNUSED NONNULL((1)) quantum_diff_t
 * >> NOTHROW(FCALL arch_cpu_quantum_elapsed_nopr)(struct cpu *__restrict me);
 * Same as the function above, however don't
 * account for lazy/delayed interrupt handling.*/
BEGIN_APIC(apic86_arch_cpu_quantum_elapsed_nopr)
	cmpb   $(0), arch_cpu_preemptive_interrupts_disabled(%R_fcall0P)
	jne8   1f /* Preemptive interrupts are disabled! */
	EXTERN(thiscpu_quantum_length)
	movzlP thiscpu_quantum_length(%R_fcall0P), %Pax
	EXTERN(x86_lapicbase)
	movP   x86_lapicbase, %Pcx
	movl   APIC_TIMER_CURRENT(%Pcx), %ecx /* Read the current timer value */
	subl   %ecx, %eax
	jb8    1f /* Shouldn't happen, but has been seen to happen */
	ret
1:	xorl   %eax, %eax
	ret
END_APIC(apic86_arch_cpu_quantum_elapsed_nopr)



/* >> FUNDEF NOBLOCK NOPREEMPT NONNULL((1)) void
 * >> NOTHROW(FCALL arch_cpu_disable_preemptive_interrupts_nopr)(struct cpu *__restrict me);
 * >> FUNDEF NOBLOCK NOPREEMPT NONNULL((1)) void
 * >> NOTHROW(FCALL arch_cpu_enable_preemptive_interrupts_nopr)(struct cpu *__restrict me);
 * Same as the functions above, but don't adjust the CPU time afterwards.
 * WARNING: Keeping preemptive interrupts disabled without time loss accounting
 *          for longer periods of time will cause `thiscpu_quantum_length' to
 *          go nuts once they actually get turned back on.
 * NOTE:    As long as preemptive interrupts are disabled, `arch_cpu_quantum_elapsed_nopr()'
 *          and `arch_cpu_quantum_elapsed_and_reset_nopr()' always return 0.
 * NOTE:    When `arch_cpu_enable_preemptive_interrupts_nopr()' always also
 *          does the same as `arch_cpu_update_quantum_length_nopr()'. */
BEGIN_APIC(apic86_arch_cpu_enable_preemptive_interrupts_nopr)
	EXTERN(arch_cpu_preemptive_interrupts_disabled)
	movb   $(0), arch_cpu_preemptive_interrupts_disabled(%R_fcall0P)
	EXTERN(thiscpu_quantum_length)
	movl   thiscpu_quantum_length(%R_fcall0P), %ecx
	EXTERN(x86_lapicbase)
	movP   x86_lapicbase, %Pax
	/* >> lapic_write(APIC_TIMER_DIVIDE, APIC_TIMER_DIVIDE_F16); */
	movl   $(APIC_TIMER_DIVIDE_F16), APIC_TIMER_DIVIDE(%Pax)
	/* >> // Set the PIT interrupt to the APIC timer. 
	 * >> lapic_write(APIC_TIMER, X86_INTNO_PIC1_PIT | APIC_TIMER_MODE_FPERIODIC); */
	movl   $(X86_INTNO_PIC1_PIT | APIC_TIMER_MODE_FPERIODIC), APIC_TIMER(%Pax)
	/* >> lapic_write(APIC_TIMER_INITIAL, PERCPU(thiscpu_quantum_length)); */
	movl   %ecx, APIC_TIMER_INITIAL(%Pax)
	ret
END_APIC(apic86_arch_cpu_enable_preemptive_interrupts_nopr)


BEGIN_APIC(apic86_arch_cpu_disable_preemptive_interrupts_nopr)
	EXTERN(arch_cpu_preemptive_interrupts_disabled)
	movb   $(1), arch_cpu_preemptive_interrupts_disabled(%R_fcall0P)
	EXTERN(x86_lapicbase)
	movP   x86_lapicbase, %Pax
	/* lapic_write(APIC_TIMER, APIC_TIMER_FDISABLED); */
	movl   $(APIC_TIMER_FDISABLED), APIC_TIMER(%Pax)
	ret
END_APIC(apic86_arch_cpu_disable_preemptive_interrupts_nopr)



/* >> FUNDEF NOBLOCK NOPREEMPT NONNULL((1)) quantum_diff_t
 * >> NOTHROW(FCALL arch_cpu_quantum_elapsed_and_reset_nopr)(struct cpu *__restrict me);
 * Return the # of elapsed quantum units from the current CPU tick,
 * before resetting the # of elapsed units (as well as the # of units
 * left before a scheduler interrupt is fired) to their max values. */
BEGIN_APIC(apic86_arch_cpu_quantum_elapsed_and_reset_nopr)
	EXTERN(arch_cpu_preemptive_interrupts_disabled)
	cmpb   $(0), arch_cpu_preemptive_interrupts_disabled(%R_fcall0P)
	jne8   1f
	EXTERN(x86_lapicbase)
	movP   x86_lapicbase, %Pdx
	EXTERN(thiscpu_quantum_length)
	movzlP thiscpu_quantum_length(%R_fcall0P), %Pax
	/* >> lapic_read(APIC_TIMER_CURRENT); */
	movzlP APIC_TIMER_CURRENT(%Pdx), %Pcx
	/* >> lapic_write(APIC_TIMER_INITIAL, PERCPU(thiscpu_quantum_length)); */
	movl   %eax, APIC_TIMER_INITIAL(%Pdx) /* This will reset the timer */
	subP   %Pcx, %Pax
	jb8    1f /* Shouldn't happen */
	ret
1:	xorP   %Pax, %Pax
	ret
END_APIC(apic86_arch_cpu_quantum_elapsed_and_reset_nopr)



/* >> FUNDEF NOBLOCK NOPREEMPT NONNULL((1)) quantum_diff_t
 * >> NOTHROW(FCALL arch_cpu_update_quantum_length_nopr)(struct cpu *__restrict me);
 * Update hardware following a change made to `thiscpu_quantum_length'
 * NOTE: If `thiscpu_quantum_length' is greater than the implementation limit,
 *       it will be clamped to the max possible value. Note however that the
 *       implementation limit is always defined such that properly functioning
 *       hardware is always able to provide a quantum length suitable to
 *       perfectly match `HZ' ticks per second (even when the perfect quantum
 *       length needed to reach this goal changes over time) */
#if 0
BEGIN_APIC(apic86_arch_cpu_update_quantum_length_nopr)
	... /* Same as `apic86_arch_cpu_quantum_elapsed_and_reset_nopr()' */
END_APIC(apic86_arch_cpu_update_quantum_length_nopr)
#else
DEFINE_INTERN_ALIAS(apic86_arch_cpu_update_quantum_length_nopr,
                    apic86_arch_cpu_quantum_elapsed_and_reset_nopr);
INTERN_CONST(apic86_arch_cpu_update_quantum_length_nopr_size,
             apic86_arch_cpu_quantum_elapsed_and_reset_nopr_size);
#endif



/* >> FUNDEF NOBLOCK WUNUSED NOPREEMPT NONNULL((1)) bool
 * >> NOTHROW(FCALL arch_cpu_hwipi_pending_nopr)(struct cpu *__restrict me);
 * Check if IPIs are pending to be executed by the calling CPU,
 * returning `true' if this is the case, or `false' it not.
 * In order to serve any pending IPIs, preemption must be enabled. */
BEGIN_APIC(apic86_arch_cpu_hwipi_pending_nopr)
	/* >> u32 mask = lapic_read(APIC_ISR(APIC_ISR_INDEX(X86_INTERRUPT_APIC_IPI)));
	 * >> return (mask & APIC_ISR_MASK(X86_INTERRUPT_APIC_IPI)) != 0; */
	xorP   %Pax, %Pax
	EXTERN(x86_lapicbase)
	movP   x86_lapicbase, %Pcx
	movl   APIC_ISR(APIC_ISR_INDEX(X86_INTERRUPT_APIC_IPI))(%Pcx), %ecx
	testl  $(APIC_ISR_MASK(X86_INTERRUPT_APIC_IPI)), %ecx
	setnz  %al
	ret
END_APIC(apic86_arch_cpu_hwipi_pending_nopr)





















/************************************************************************/
/* PIT IMPLEMENTATION                                                   */
/************************************************************************/

.section .text
.cfi_startproc
#define BEGIN_PIT(name) PUBLIC_FUNCTION(name)
#define END_PIT(name)   SKIPFOR(name, apic86_##name##_size)

/* >> FUNDEF NOBLOCK NOPREEMPT WUNUSED NONNULL((1)) quantum_diff_t
 * >> NOTHROW(FCALL arch_cpu_quantum_elapsed_nopr)(struct cpu *__restrict me);
 * Same as the function above, however don't
 * account for lazy/delayed interrupt handling.*/
BEGIN_PIT(arch_cpu_quantum_elapsed_nopr)
	EXTERN(arch_cpu_preemptive_interrupts_disabled)
	cmpb   $(0), arch_cpu_preemptive_interrupts_disabled(%R_fcall0P)
	jne8   1f /* Preemptive interrupts are disabled! */
	/* Read the current PIT counter position. */
	movb   $(PIT_COMMAND_SELECT_F0 |     \
	         PIT_COMMAND_ACCESS_FLATCH | \
	         PIT_COMMAND_FBINARY), %al
	outb   %al,  $(PIT_COMMAND)
	inb    $(PIT_DATA0), %al
	movb   %al, %dl
	inb    $(PIT_DATA0), %al
	movb   %al, %dh
	EXTERN(thiscpu_quantum_length)
	movzlP thiscpu_quantum_length(%R_fcall0P), %Pax
	subw   %dx, %ax
	jb8    1f /* Shouldn't happen */
	ret
1:	xorP   %Pax, %Pax
	ret
END_PIT(arch_cpu_quantum_elapsed_nopr)



/* >> FUNDEF NOBLOCK NOPREEMPT NONNULL((1)) void
 * >> NOTHROW(FCALL arch_cpu_disable_preemptive_interrupts_nopr)(struct cpu *__restrict me);
 * >> FUNDEF NOBLOCK NOPREEMPT NONNULL((1)) void
 * >> NOTHROW(FCALL arch_cpu_enable_preemptive_interrupts_nopr)(struct cpu *__restrict me);
 * Same as the functions above, but don't adjust the CPU time afterwards.
 * WARNING: Keeping preemptive interrupts disabled without time loss accounting
 *          for longer periods of time will cause `thiscpu_quantum_length' to
 *          go nuts once they actually get turned back on.
 * NOTE:    As long as preemptive interrupts are disabled, `arch_cpu_quantum_elapsed_nopr()'
 *          and `arch_cpu_quantum_elapsed_and_reset_nopr()' always return 0.
 * NOTE:    When `arch_cpu_enable_preemptive_interrupts_nopr()' always also
 *          does the same as `arch_cpu_update_quantum_length_nopr()'. */
BEGIN_PIT(arch_cpu_enable_preemptive_interrupts_nopr)
	/* Mark preemptive interrupts as being enabled. */
	EXTERN(arch_cpu_preemptive_interrupts_disabled)
	movb   $(0), arch_cpu_preemptive_interrupts_disabled(%R_fcall0P)
	EXTERN(thiscpu_quantum_length)
	movw   thiscpu_quantum_length(%R_fcall0P), %dx
	movb   $(PIT_COMMAND_SELECT_F0 |     \
	         PIT_COMMAND_ACCESS_FLOHI |  \
	         PIT_COMMAND_MODE_FRATEGEN | \
	         PIT_COMMAND_FBINARY), %al
	outb   %al, $(PIT_COMMAND)
	/* outb_p(PIT_DATA0, thiscpu_quantum_length & 0xff) */
	movb   %dl, %al
	outb   %al, $(PIT_DATA0)
	outb   %al, $(0x80)  /* io_pause() */
	/* outb(PIT_DATA0, (thiscpu_quantum_length >> 8) & 0xff); */
	movb   %dh, %al
	outb   %al, $(PIT_DATA0)
	ret
END_PIT(arch_cpu_enable_preemptive_interrupts_nopr)


BEGIN_PIT(arch_cpu_disable_preemptive_interrupts_nopr)
	/* Mark preemptive interrupts as being disabled. */
	EXTERN(arch_cpu_preemptive_interrupts_disabled)
	movb   $(1), arch_cpu_preemptive_interrupts_disabled(%R_fcall0P)
	/* Disable the PIT interrupt within the PIC */
	inb    $(X86_PIC1_DATA), %al
	orb    $(1 << (X86_INTNO_PIC1_PIT-X86_INTERRUPT_PIC1_BASE)), %al
	outb   %al, $(X86_PIC1_DATA)
	/* Set the PIT to one-shot mode to keep it from running
	 * -> https://forum.osdev.org/viewtopic.php?t=11689&p=80318 */
	movb   $(PIT_COMMAND_SELECT_F0 |    \
	         PIT_COMMAND_ACCESS_FLOHI | \
	         PIT_COMMAND_MODE_FONESHOT), %al
	outb   %al, $(PIT_COMMAND)
	/* Normally at this point, the PIT would want us to specify the delay,
	 * however by not telling it anything, we essentially leave it hanging
	 * in this semi-disabled mode until we reset it at a later point in time. */
	ret
END_PIT(arch_cpu_disable_preemptive_interrupts_nopr)



/* >> FUNDEF NOBLOCK NOPREEMPT NONNULL((1)) quantum_diff_t
 * >> NOTHROW(FCALL arch_cpu_quantum_elapsed_and_reset_nopr)(struct cpu *__restrict me);
 * Return the # of elapsed quantum units from the current CPU tick,
 * before resetting the # of elapsed units (as well as the # of units
 * left before a scheduler interrupt is fired) to their max values. */
BEGIN_PIT(arch_cpu_quantum_elapsed_and_reset_nopr)
	/* Re-initialize to reset the latch counter. */
	EXTERN(thiscpu_quantum_length)
	movl   thiscpu_quantum_length(%R_fcall0P), %edx
.Lpit_reset_quantum_with_length_edx:
	EXTERN(arch_cpu_preemptive_interrupts_disabled)
	cmpb   $(0), arch_cpu_preemptive_interrupts_disabled(%R_fcall0P)
	jne8   1f

	/* %edx = thiscpu_quantum_length & 0xffff */
	movb   $(PIT_COMMAND_SELECT_F0 |     \
	         PIT_COMMAND_ACCESS_FLATCH | \
	         PIT_COMMAND_FBINARY), %al
	outb   %al,  $(PIT_COMMAND)
	inb    $(PIT_DATA0), %al
	movb   %al, %cl
	inb    $(PIT_DATA0), %al
	movb   %al, %ch
	/* %cx = REMAINING_QUANTUM_UNITS_FROM_PREVIOUS_QUANTUM */

	movb   $(PIT_COMMAND_SELECT_F0 |     \
	         PIT_COMMAND_ACCESS_FLOHI |  \
	         PIT_COMMAND_MODE_FRATEGEN | \
	         PIT_COMMAND_FBINARY), %al
	outb   %al, $(PIT_COMMAND)
	/* outb_p(PIT_DATA0, thiscpu_quantum_length & 0xff) */
	movb   %dl, %al
	outb   %al, $(PIT_DATA0)
	outb   %al, $(0x80)  /* io_pause() */
	/* outb(PIT_DATA0, (thiscpu_quantum_length >> 8) & 0xff); */
	movb   %dh, %al
	outb   %al, $(PIT_DATA0)
	/* Calculate the actual number of elapsed quantum units. */
	movzlP %edx, %Pax
	subw   %cx, %ax
	jb8    1f /* Shouldn't happen */
	ret
1:	xorP   %Pax, %Pax
	ret
END_PIT(arch_cpu_quantum_elapsed_and_reset_nopr)



/* >> FUNDEF NOBLOCK NOPREEMPT NONNULL((1)) quantum_diff_t
 * >> NOTHROW(FCALL arch_cpu_update_quantum_length_nopr)(struct cpu *__restrict me);
 * Update hardware following a change made to `thiscpu_quantum_length'
 * NOTE: If `thiscpu_quantum_length' is greater than the implementation limit,
 *       it will be clamped to the max possible value. Note however that the
 *       implementation limit is always defined such that properly functioning
 *       hardware is always able to provide a quantum length suitable to
 *       perfectly match `HZ' ticks per second (even when the perfect quantum
 *       length needed to reach this goal changes over time) */
BEGIN_PIT(arch_cpu_update_quantum_length_nopr)
	EXTERN(thiscpu_quantum_length)
	movl   thiscpu_quantum_length(%R_fcall0P), %edx
	/* Make sure that we don't exceed the max value. */
	cmpl   $(0xffff), %edx
	jbe8   .Lpit_reset_quantum_with_length_edx
	movl   $(0xffff), %edx
	movl   %edx, thiscpu_quantum_length(%R_fcall0P)
	jmp8   .Lpit_reset_quantum_with_length_edx
END_PIT(arch_cpu_update_quantum_length_nopr)



/* >> FUNDEF NOBLOCK WUNUSED NOPREEMPT NONNULL((1)) bool
 * >> NOTHROW(FCALL arch_cpu_hwipi_pending_nopr)(struct cpu *__restrict me);
 * Check if IPIs are pending to be executed by the calling CPU,
 * returning `true' if this is the case, or `false' it not.
 * In order to serve any pending IPIs, preemption must be enabled. */
BEGIN_PIT(arch_cpu_hwipi_pending_nopr)
	movP   $(X86_PIC_READ_IRR), %Pax /* NOTE: This also clears all of the upper bits! */
	outb   %al, $(X86_PIC1_CMD)
	inb    $(X86_PIC2_CMD), %al /* %al = inb(X86_PIC1_CMD) */
	/* return PIT_BIT_IS_SET(%al); */
	testb  $(1 << (X86_INTNO_PIC1_PIT - X86_INTERRUPT_PIC1_BASE)), %al
	setnz  %al
	ret
END_PIT(arch_cpu_hwipi_pending_nopr)


.cfi_endproc


#endif /* !GUARD_KERNEL_CORE_ARCH_I386_SCHED_APIC_S */
