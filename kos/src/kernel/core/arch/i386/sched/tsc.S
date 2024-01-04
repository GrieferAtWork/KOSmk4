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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_SCHED_TSC_S
#define GUARD_KERNEL_CORE_ARCH_I386_SCHED_TSC_S 1
#define __ASSEMBLER__ 1

#include <kernel/compiler.h>

#include <debugger/config.h>
#include <kernel/fpu.h>
#include <kernel/paging.h>
#include <kernel/x86/alternatives.h>
#include <kernel/x86/apic.h>
#include <kernel/x86/breakpoint.h> /* reload_x86_debug_registers */
#include <kernel/x86/pic.h>
#include <kernel/x86/pit.h>

#include <hybrid/host.h>

#include <cfi.h>
#include <asm/cpu-flags.h>
#include <asm/cpu-msr.h>
#include <asm/instr/compat.h>
#include <asm/instr/interrupt.h>
#include <asm/instr/jccN.h>
#include <asm/instr/movzxq.h>
#include <kos/kernel/cpu-state-asm.h>
#include <kos/kernel/cpu-state-compat.h>
#include <kos/kernel/cpu-state.h>
#include <kos/kernel/x86/gdt.h>
#include <kos/kernel/x86/tss-compat.h>
#include <kos/kernel/x86/tss.h>

#ifdef __x86_64__
#define x86_load_thread_Pax_cpu_Pbx x86_load_thread_rax_cpu_rbx
#define x86_unwind_scpustate_Psp    x86_unwind_scpustate_rsp
#else /* __x86_64__ */
#define x86_load_thread_Pax_cpu_Pbx x86_load_thread_eax_cpu_ebx
#define x86_unwind_scpustate_Psp    x86_unwind_scpustate_esp
#endif /* !__x86_64__ */


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
#define SIMPLE_C_INTERRUPT_ENTER \
	intr_enter INTR;             \
	FOREACH_CLOBBER_pushP_cfi_r
#define SIMPLE_C_INTERRUPT_LEAVE \
	FOREACH_CLOBBER_popP_cfi_r;  \
	intr_exit intr_enabled=0
#else /* __x86_64__ */
#define SIMPLE_C_INTERRUPT_ENTER          \
	pushl_cfi %ds;                        \
	.cfi_restore_iret_ds_or_offset -4;    \
	pushl_cfi %es;                        \
	.cfi_restore_iret_es_or_offset -8;    \
	pushl_cfi %fs;                        \
	.cfi_restore_iret_fs_or_offset -12;   \
	                                      \
	FOREACH_CLOBBER_pushP_cfi_r;          \
	                                      \
	/* Load kernel-space segments. */     \
	movw   $(SEGMENT_USER_DATA_RPL), %ax; \
	movw   %ax, %ds;                      \
	movw   %ax, %es;                      \
	movw   $(SEGMENT_KERNEL_FSBASE), %ax; \
	movw   %ax, %fs
#define SIMPLE_C_INTERRUPT_LEAVE \
	FOREACH_CLOBBER_popP_cfi_r;  \
	popl_cfi %fs;                \
	.cfi_restore_iret_fs;        \
	popl_cfi %es;                \
	.cfi_restore_iret_es;        \
	popl_cfi %ds;                \
	.cfi_restore_iret_ds;        \
	iret
#endif /* !__x86_64__ */


.section .text.free
INTERN_FUNCTION(x86_native_tsc_get)
	/* Implementation override for `tsc_get()' in APIC+TSC mode */
#ifdef __x86_64__
	xorq   %rax, %rax
#endif /* __x86_64__ */
	rdtsc
#ifdef __x86_64__
	shlq   $(32), %rdx
	orq    %rdx, %rax
#endif /* __x86_64__ */
	ret
INTERN_CONST(x86_native_tsc_get_size, . - x86_native_tsc_get)
END(x86_native_tsc_get)


.section .text.free
INTERN_FUNCTION(x86_native_tsc_nodeadline)
	/* Implementation override for `tsc_nodeadline()' in APIC+TSC mode */
	movl   $(0xffffffff), %eax
	movl   %eax, %edx
	movl   $(IA32_TSC_DEADLINE), %ecx
	wrmsr
	ret
INTERN_CONST(x86_native_tsc_nodeadline_size, . - x86_native_tsc_nodeadline)
END(x86_native_tsc_nodeadline)


.section .text.free
INTERN_FUNCTION(x86_native_tsc_deadline)
	/* Implementation override for `tsc_deadline()' in APIC+TSC mode */
#ifdef __x86_64__
	movl   %edi, %eax
	movq   %rdi, %rdx
	shlq   $(32), %rdx
	movl   $(IA32_TSC_DEADLINE), %ecx
	wrmsr
	/* Load the current timestamp. */
	xorq   %rax, %rax
	rdtsc
	shlq   $(32), %rdx
	orq    %rdx, %rax
	cmpq   %rax, %rdi
	jbe    .Lclear_deadline /* if (deadline <= current) goto .Lclear_deadline; */
	ret
.Lclear_deadline:
	movq   %rax, %rdi
	xorl   %eax, %eax
	decl   %eax
	movl   %eax, %edx
	movl   $(IA32_TSC_DEADLINE), %ecx
	wrmsr
	movq   %rdi, %rax
	ret
#else /* __x86_64__ */
	/* NOTE: A FASTCALL function taking a 64-bit argument behaves identical to STDCALL! */
	movl   4(%esp), %eax
	movl   8(%esp), %edx
	movl   $(IA32_TSC_DEADLINE), %ecx
	wrmsr
	/* Check if the deadline has already expired. */
	rdtsc
	cmpl   8(%esp), %edx
	jb     .Lclear_deadline /* if (%edx < 8(%esp)) return false; */
	ja     .Lret_true       /* if (%edx > 8(%esp)) return true; */
	cmpl   4(%esp), %eax
	jbe    .Lclear_deadline /* if (%edi <= %eax) return false; */
.Lret_true:
	ret    $(8) /* Success */
.Lclear_deadline:
	/* When returning  false,  we  must write  UINT64_MAX  to  IA32_TSC_DEADLINE
	 * in order to prevent the APIC  timer interrupt from indicating a  deadline
	 * event after we've indicated to our caller that their deadline had already
	 * expired.
	 * -> API users should be allowed to assume that us returning `false' means that
	 *    The  high-level  `tsc_deadline_passed()'   function  won't  get   invoked! */
	movl   %eax, 4(%esp)
	movl   %edx, 8(%esp)
	xorl   %eax, %eax
	decl   %eax
	movl   %eax, %edx
	movl   $(IA32_TSC_DEADLINE), %ecx
	wrmsr
	movl   4(%esp), %eax
	movl   8(%esp), %edx
	ret    $(8)
#endif /* !__x86_64__ */
INTERN_CONST(x86_native_tsc_deadline_size, . - x86_native_tsc_deadline)
END(x86_native_tsc_deadline)


.section .text.free
INTERN_FUNCTION(x86_native_tsc_getdeadline)
	/* Implementation override for `tsc_deadline()' in APIC+TSC mode */
#ifdef __x86_64__
	xorq   %rax, %rax
#endif /* __x86_64__ */
	movl   $(IA32_TSC_DEADLINE), %ecx
	rdmsr
#ifdef __x86_64__
	shlq   $(32), %rdx
	orq    %rdx, %rax
#endif /* __x86_64__ */
	ret
INTERN_CONST(x86_native_tsc_getdeadline_size, . - x86_native_tsc_getdeadline)
END(x86_native_tsc_getdeadline)






.section .text
/* Return the currently set deadline. */
PUBLIC_FUNCTION(tsc_getdeadline)
	.cfi_startproc
#ifdef __x86_64__
	EXTERN(thiscpu_x86_apic_emutsc_deadline)
	movq   thiscpu_x86_apic_emutsc_deadline(%R_fcall0P), %rax
#else /* __x86_64__ */
	EXTERN(thiscpu_x86_apic_emutsc_deadline)
	movl   thiscpu_x86_apic_emutsc_deadline+0(%R_fcall0P), %eax
	movl   thiscpu_x86_apic_emutsc_deadline+4(%R_fcall0P), %edx
#endif /* !__x86_64__ */
	ret
	/* Ensure sufficient padding. */
.if x86_native_tsc_getdeadline_size > (. - tsc_getdeadline)
.skip x86_native_tsc_getdeadline_size - (. - tsc_getdeadline)
.endif
	.cfi_endproc
END(tsc_getdeadline)






/************************************************************************/
/* Spurious interrupt handler                                           */
/************************************************************************/
.section .text
INTERN_FUNCTION(x86_idt_apic_spurious)
	.cfi_startproc simple
	.cfi_iret_signal_frame
	.cfi_def_cfa %Psp, 0
	SIMPLE_C_INTERRUPT_ENTER

	/* Remember that a spurious interrupt happened. */
	EXTERN(x86_apic_spur)
	call   x86_apic_spur

	/* Signal EOI for the interrupt. */
	EXTERN(x86_lapicbase)
	movP   x86_lapicbase, %Pax
	movl   $(APIC_EOI_FSIGNAL), APIC_EOI(%Pax)

	SIMPLE_C_INTERRUPT_LEAVE
	.cfi_endproc
END(x86_idt_apic_spurious)





/************************************************************************/
/* RTC resync interrupt handler                                         */
/************************************************************************/
.section .text
INTERN_FUNCTION(x86_idt_specific_07h) /* IDT_X86_f8, X86_INTNO_PIC2_CMOS */
	.cfi_startproc simple
	.cfi_iret_signal_frame
	.cfi_def_cfa %Psp, 0
	SIMPLE_C_INTERRUPT_ENTER

	/* Call the C-level CMOS interrupt handler. */
	EXTERN(x86_cmos_interrupt)
	call   x86_cmos_interrupt

	/* Signal EOI for the interrupt.
	 * Note that this one's a PIC interrupt! */
	movb   $(X86_PIC_CMD_EOI), %al
	outb   %al, $(X86_PIC2_CMD) /* outb(X86_PIC2_CMD, X86_PIC_CMD_EOI); */
	outb   %al, $(X86_PIC1_CMD) /* outb(X86_PIC1_CMD, X86_PIC_CMD_EOI); */

	SIMPLE_C_INTERRUPT_LEAVE
	.cfi_endproc
END(x86_idt_specific_07h)





/************************************************************************/
/* Preemptive interrupt handler                                         */
/************************************************************************/
.section .text
PRIVATE_FUNCTION(call_tsc_deadline)
	.cfi_startproc
#ifndef __x86_64__
	pushl_cfi %edi /* tsc_deadline:deadline (high 32 bits) */
	pushl_cfi %esi /* tsc_deadline:deadline (low 32 bits) */
	EXTERN(tsc_deadline)
	call   tsc_deadline
	.cfi_adjust_cfa_offset -8
	ret
#else /* !__x86_64__ */
	EXTERN(tsc_deadline)
	jmp    tsc_deadline
#endif /* __x86_64__ */
	.cfi_endproc
END(call_tsc_deadline)

.section .text
INTERN_FUNCTION(x86_idt_preemption)
	.cfi_startproc simple
	.cfi_iret_signal_frame
	.cfi_def_cfa %Psp, 0
#ifdef __x86_64__
	intr_enter INTR
#endif /* __x86_64__ */

	/* Construct a full `struct scpustate' structure */
	ASM_PUSH_SCPUSTATE_AFTER_HW_IRET_CFI_R

	/* Load kernel-space segments. */
#ifndef __x86_64__
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
#endif /* !__x86_64__ */

	/* Acknowledge the interrupt. */
.alt_if X86_FEAT_APIC
	EXTERN(x86_lapicbase)
	movP   x86_lapicbase, %Pdi
	movl   $(APIC_EOI_FSIGNAL), APIC_EOI(%Pdi)
.alt_else
	movb   $(X86_PIC_CMD_EOI), %al
	outb   %al, $(X86_PIC1_CMD)
.alt_endif

	EXTERN(this_task)
	movP   %segtls:this_task, %Pbp
	EXTERN(this_cpu)
	movP   this_cpu(%Pbp), %Pbx /* THIS_CPU */

.alt_if X86_FEAT_TSC_DEADLINE
	/* Check if there really was an interrupt. */
	movl   $(IA32_TSC_DEADLINE), %ecx
	rdmsr
#ifdef __x86_64__
	shlq   $(32), %rdx
	movzlq %eax, %rsi
	orq    %rdx, %rsi
	/* %rsi == CURRENT_DEADLINE */
	xorq   %rax, %rax
#else /* __x86_64__ */
	movl   %eax, %esi
	movl   %edx, %edi
	/* %edi:%esi == CURRENT_DEADLINE */
#endif /* __x86_64__ */
	/* Get the current timestamp value. */
	rdtsc
#ifdef __x86_64__
	shlq   $(32), %rdx
	orq    %rdx, %rax
	/* %rax == NOW */
#else /* __x86_64__ */
	/* %edx:%eax == NOW */
#endif /* !__x86_64__ */
.alt_elseif X86_FEAT_APIC
	xorb   %al, %al
	EXTERN(thiscpu_x86_apic_emutsc_early_interrupt)
	xchgb  thiscpu_x86_apic_emutsc_early_interrupt(%Pbx), %al
	testb  %al, %al
	jnz8   1f
	/* Advance the timer. */
	EXTERN(thiscpu_x86_apic_emutsc_tscbase)
	EXTERN(thiscpu_x86_apic_emutsc_initial_shifted)
#ifdef __x86_64__
	movq   thiscpu_x86_apic_emutsc_initial_shifted(%Pbx), %rax
	addq   %rax, thiscpu_x86_apic_emutsc_tscbase(%Pbx)
#else /* __x86_64__ */
	movl   thiscpu_x86_apic_emutsc_initial_shifted+0(%Pbx), %eax
	addl   %eax, thiscpu_x86_apic_emutsc_tscbase+0(%Pbx)
	movl   thiscpu_x86_apic_emutsc_initial_shifted+4(%Pbx), %eax
	adcl   %eax, thiscpu_x86_apic_emutsc_tscbase+4(%Pbx)
#endif /* !__x86_64__ */
	/* Store the current counter.
	 * NOTE: Must only do this if the interrupt wasn't already handled,
	 *       else  this might  result in  an APIC  interval being lost:
	 * >> READ(CURRENT) = 0x123;
	 * >> HW:SCHEDULE_INTERRUPT;
	 * >> CURRENT = 0x100000;
	 * >> READ(CURRENT) = 0xf0000;  -> thiscpu_x86_apic_emutsc_early_interrupt=true;
	 * >> READ(CURRENT) = 0x8000;
	 * >> SW:HANDLE_INTERRUPT;
	 * >> thiscpu_x86_apic_emutsc_prev_current = READ(CURRENT) = 0xf0000;
	 * If the last line was executed, it would cause the secondary interrupt
	 * to become lost! */
/*	movP   x86_lapicbase, %Pdi */ /* Had already been loaded */
	movl   APIC_TIMER_CURRENT(%Pdi), %eax
	EXTERN(thiscpu_x86_apic_emutsc_prev_current)
	movl   %eax, thiscpu_x86_apic_emutsc_prev_current(%Pbx)
1:

	/* Check if a deadline has even been set. */
#ifdef __x86_64__
	movq   thiscpu_x86_apic_emutsc_deadline(%Pbx), %rsi /* tsc_deadline:deadline */
	cmpq   $(-1), %rsi
	alt_je32 x86_unwind_scpustate_Psp
#else /* __x86_64__ */
	movl   thiscpu_x86_apic_emutsc_deadline+0(%Pbx), %esi
	movl   thiscpu_x86_apic_emutsc_deadline+4(%Pbx), %edi
	cmpl   $(-1), %edi
	jne8   1f
	cmpl   $(-1), %esi
	alt_je32 x86_unwind_scpustate_Psp
1:
#endif /* !__x86_64__ */

	/* Re-calculate the deadline and check if it has already expired. */
	movP   %Pbx, %R_fcall0P
	alt_call call_tsc_deadline
#ifdef __x86_64__
	movq   thiscpu_x86_apic_emutsc_deadline(%Pbx), %rsi
#endif /* __x86_64__ */
.alt_else
	xorb   %al, %al
	EXTERN(thiscpu_x86_apic_emutsc_early_interrupt)
	xchgb  thiscpu_x86_apic_emutsc_early_interrupt(%Pbx), %al
	testb  %al, %al
	jnz8   1f
	/* Advance the timer. */
	EXTERN(thiscpu_x86_apic_emutsc_tscbase)
	EXTERN(thiscpu_x86_apic_emutsc_initial_shifted)
#ifdef __x86_64__
	movq   thiscpu_x86_apic_emutsc_initial_shifted(%Pbx), %rax
	addq   %rax, thiscpu_x86_apic_emutsc_tscbase(%Pbx)
#else /* __x86_64__ */
	movl   thiscpu_x86_apic_emutsc_initial_shifted+0(%Pbx), %eax
	addl   %eax, thiscpu_x86_apic_emutsc_tscbase+0(%Pbx)
	movl   thiscpu_x86_apic_emutsc_initial_shifted+4(%Pbx), %eax
	adcl   %eax, thiscpu_x86_apic_emutsc_tscbase+4(%Pbx)
#endif /* !__x86_64__ */
	/* Read the current counter. */
	movb   $(PIT_COMMAND_SELECT_F0 | PIT_COMMAND_ACCESS_FLATCH | PIT_COMMAND_FBINARY), %al
	outb   %al, $(PIT_COMMAND)
	inb    $(PIT_DATA0), %al
	movb   %al, %cl
	inb    $(PIT_DATA0), %al
	movb   %al, %ch
	movzwl %cx, %ecx

	/* Store the current counter.
	 * NOTE: Must only do this if the interrupt wasn't already handled,
	 *       else  this might  result in  an APIC  interval being lost:
	 * >> READ(CURRENT) = 0x123;
	 * >> HW:SCHEDULE_INTERRUPT;
	 * >> CURRENT = 0x100000;
	 * >> READ(CURRENT) = 0xf0000;  -> thiscpu_x86_apic_emutsc_early_interrupt=true;
	 * >> READ(CURRENT) = 0x8000;
	 * >> SW:HANDLE_INTERRUPT;
	 * >> thiscpu_x86_apic_emutsc_prev_current = READ(CURRENT) = 0xf0000;
	 * If the last line was executed, it would cause the secondary interrupt
	 * to become lost! */
	EXTERN(thiscpu_x86_apic_emutsc_prev_current)
	movl   %ecx, thiscpu_x86_apic_emutsc_prev_current(%Pbx)

1:	/* Check if a deadline has even been set. */
#ifdef __x86_64__
	movq   thiscpu_x86_apic_emutsc_deadline(%Pbx), %rsi /* tsc_deadline:deadline */
	cmpq   $(-1), %rsi
	alt_je32 x86_unwind_scpustate_Psp
#else /* __x86_64__ */
	movl   thiscpu_x86_apic_emutsc_deadline+0(%Pbx), %esi
	movl   thiscpu_x86_apic_emutsc_deadline+4(%Pbx), %edi
	cmpl   $(-1), %edi
	jne8   1f
	cmpl   $(-1), %esi
	alt_je32 x86_unwind_scpustate_Psp
1:
#endif /* !__x86_64__ */

	/* Re-calculate the deadline and check if it has already expired. */
	movP   %Pbx, %R_fcall0P
	alt_call call_tsc_deadline
#ifdef __x86_64__
	movq   thiscpu_x86_apic_emutsc_deadline(%Pbx), %rsi
#endif /* __x86_64__ */
.alt_endif

#ifdef __x86_64__
	/* %rax -- Current time */
	/* %rsi -- Current deadline */
	cmpq   %rax, %rsi
	ja32   x86_unwind_scpustate_Psp /* if (deadline > now) goto x86_unwind_scpustate_Psp; */
#else /* __x86_64__ */
	/* %edx:%eax -- Current time */
	/* %edi:%esi -- Current deadline */
	cmpl   %edx, %edi
	ja32   x86_unwind_scpustate_Psp /* if (deadline[1] > now[1]) goto x86_unwind_scpustate_Psp; */
	jne8   1f                     /* if (deadline[1] != now[1]) goto 1f; */
	cmpl   %eax, %esi
	ja32   x86_unwind_scpustate_Psp /* if (deadline[0] > now[0]) goto x86_unwind_scpustate_Psp; */
1:
#endif /* !__x86_64__ */
	/* Deadline has expired (and the current time is now stored in %rax / %edx:%eax) */

	EXTERN(this_sstate)
	movP   %Psp, this_sstate(%Pbp)

	/* Trigger the deadline-passed interrupt handler. */
#ifdef __x86_64__
	movq   %rax, %rdx       /* tsc_deadline_passed:now */
#else /* __x86_64__ */
	pushl_cfi %edx          /* tsc_deadline_passed:now (high 32 bits) */
	pushl_cfi %eax          /* tsc_deadline_passed:now (low 32 bits) */
#endif /* !__x86_64__ */
	movP   %Pbx, %R_fcall0P /* tsc_deadline_passed:me */
	movP   %Pbp, %R_fcall1P /* tsc_deadline_passed:caller */
	EXTERN(tsc_deadline_passed)
	call   tsc_deadline_passed
#ifndef __x86_64__
	.cfi_adjust_cfa_offset -8
#endif /* !__x86_64__ */

	/* Check if we should actually switch threads */
	cmpP   %Pbp, %Pax
	je32   x86_unwind_scpustate_Psp

	/* Switch to the task returned by `tsc_deadline_passed()' */
	EXTERN(thiscpu_sched_current)
	movP   %Pax, thiscpu_sched_current(%Pbx)

INTERN_FUNCTION(x86_load_thread_Pax_cpu_Pbx)
	/* Primary entry point for loading a new thread-context for
	 * some thread `%Pax',  whilst running on  some cpu  `%Pbx' */
	EXTERN(this_sstate)
	movP   this_sstate(%Pax), %Psp

#ifndef NDEBUG
	cmpP   $(0x10000000), (OFFSET_SCPUSTATE_IRREGS + OFFSET_IRREGS_PFLAGS)(%Psp)
	jna    1f /* if (!(STATE.EFLAGS > 0x10000000)) goto 1f; */
	int3
1:
#endif /* !NDEBUG */

	/* Load other scheduler-related register values. */
	EXTERN(this_x86_kernel_psp0)
	movP   this_x86_kernel_psp0(%Pax), %Pcx
	EXTERN(thiscpu_x86_tss)
	movP   %Pcx, (thiscpu_x86_tss + OFFSET_TSS_PSP0)(%Pbx)

#ifndef __x86_64__
	/* Load segment base addresses */
	EXTERN(thiscpu_x86_gdt)
#define GDT(x) x + thiscpu_x86_gdt(%ebx)
	/* SEGMENT_KERNEL_FSBASE */
	movl   %eax, %ecx
	movl   %eax, %edx
	shrl   $(24), %ecx
	andl   $(0x00ffffff), %edx
	andl   $(0xff000000), OFFSET_SEGMENT_DESCRIPTOR_BASE0 + GDT(SEGMENT_KERNEL_FSBASE) /* Clear out base_low */
	orl    %edx,          OFFSET_SEGMENT_DESCRIPTOR_BASE0 + GDT(SEGMENT_KERNEL_FSBASE) /* Set base_low */
	movb   %cl,           OFFSET_SEGMENT_DESCRIPTOR_BASE2 + GDT(SEGMENT_KERNEL_FSBASE) /* Set base_hi */

	/* SEGMENT_USER_FSBASE */
	EXTERN(this_x86_user_fsbase)
	movl   this_x86_user_fsbase(%eax), %ecx
	movl   %ecx, %edx
	shrl   $(24), %ecx
	andl   $(0x00ffffff), %edx
	andl   $(0xff000000), OFFSET_SEGMENT_DESCRIPTOR_BASE0 + GDT(SEGMENT_USER_FSBASE) /* Clear out base_low */
	orl    %edx,          OFFSET_SEGMENT_DESCRIPTOR_BASE0 + GDT(SEGMENT_USER_FSBASE) /* Set base_low */
	movb   %cl,           OFFSET_SEGMENT_DESCRIPTOR_BASE2 + GDT(SEGMENT_USER_FSBASE) /* Set base_hi */

	/* SEGMENT_USER_GSBASE */
	EXTERN(this_x86_user_gsbase)
	movl   this_x86_user_gsbase(%eax), %ecx
	movl   %ecx, %edx
	shrl   $(24), %ecx
	andl   $(0x00ffffff), %edx
	andl   $(0xff000000), OFFSET_SEGMENT_DESCRIPTOR_BASE0 + GDT(SEGMENT_USER_GSBASE) /* Clear out base_low */
	orl    %edx,          OFFSET_SEGMENT_DESCRIPTOR_BASE0 + GDT(SEGMENT_USER_GSBASE) /* Set base_low */
	movb   %cl,           OFFSET_SEGMENT_DESCRIPTOR_BASE2 + GDT(SEGMENT_USER_GSBASE) /* Set base_hi */
#undef GDT
#endif /* __x86_64__ */


#ifdef CONFIG_HAVE_FPU
	/* Disable the FPU, preparing it to be loaded lazily. */
	movP   %cr0, %Pcx
	andP   $(~CR0_TS), %Pcx
	EXTERN(thiscpu_fputhread)
	movP   thiscpu_fputhread(%Pbx), %Pdx
	cmpP   %Pdx, %Pax
	je8    1f
	/* Only disable if the target thread isn't holding the active FPU-context */
	orP    $(CR0_TS), %Pcx
1:	movP   %Pcx, %cr0
#endif /* CONFIG_HAVE_FPU */

	/* Check if the old thread had its I/O permissions bitmap loaded. */
	EXTERN(thiscpu_x86_ioperm_bitmap)
	cmpP   $(0), thiscpu_x86_ioperm_bitmap(%Pbx)
	jne32  .Llazy_disable_ioperm_bitmap
INTERN_LABEL(__x86_lazy_disable_ioperm_bitmap_return):

	.cfi_remember_state

	/* Update the used page directory pointer. */
	EXTERN(this_mman)
	movP   this_mman(%Pax), %Pcx
	EXTERN(thismman_pagedir_p)
	movP   thismman_pagedir_p(%Pcx), %Pdi
	EXTERN(thiscpu_pdir)
	movP   %Pdi, thiscpu_pdir(%Pbx) /* Update the per-cpu current-pdir field. */
	movP   %cr3, %Pdx
	cmpP   %Pdx, %Pdi
	je     1f
	movP   %Pdi, %cr3
	/* Reload debug registers */
	reload_x86_debug_registers %Pcx, %Pdi, %Psi, 1
1:

#ifdef __x86_64__
INTERN_FUNCTION(x86_load_scpustate_rsp_gsbase_rax_nopr)
#else /* __x86_64__ */
INTERN_FUNCTION(x86_load_scpustate_esp_nopr)
#endif /* !__x86_64__ */

#ifndef NDEBUG
	pushfP_cfi
	testP  $(EFLAGS_IF), 0(%Psp)
	jz     1f
	int3   /* ASSERTION FAILED: Interrupt should be off when you get here! */
1:	popfP_cfi
#endif /* !NDEBUG */

#ifdef __x86_64__
	.cfi_register %gs.base, %rax

	/* Load segment registers. */
	ASM_POP_SGREGS_CFI_R(%rcx)

	/* Update the kernel TLS pointer.
	 * NOTE: This must be done  _after_ segment registers were  loaded,
	 *       as the use of `ASM_POP_SGREGS_CFI_R()' clobbered %gs.base! */
	wrgsbaseq %rax
	.cfi_same_value %gs.base

	/* Load fsbase and kgsbase */
	ASM_POP_SGBASE_CFI_R

	/* Load GP registers. */
	ASM_POP_GPREGSNSP_CFI_R

	/* Resume execution */
	intr_exit intr_enabled=0
#else /* __x86_64__ */
	/* Load the underlying CPU state */
PRIVATE_FUNCTION(x86_unwind_scpustate_Psp)
	popal_cfi_r

	popl_cfi %gs
	.cfi_restore_iret_gs
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds

	iret
END(x86_unwind_scpustate_Psp)
#endif /* !__x86_64__ */
#ifdef __x86_64__
END(x86_load_scpustate_rsp_gsbase_rax_nopr)
#else /* __x86_64__ */
END(x86_load_scpustate_esp_nopr)
#endif /* !__x86_64__ */
	nop /* This fixes tracebacks when the IRET breaks */
	.cfi_restore_state
#ifdef __x86_64__
	.cfi_remember_state
PRIVATE_FUNCTION(x86_unwind_scpustate_Psp)
	/* Only restore GP registers! */
	addq   $(OFFSET_SCPUSTATE64_GPREGSNSP), %rsp
	ASM_POP_GPREGSNSP_CFI_R
	intr_exit intr_enabled=0
END(x86_unwind_scpustate_Psp)
	.cfi_restore_state
#endif /* __x86_64__ */

	/* Disable the I/O permissions bitmap. */
.Llazy_disable_ioperm_bitmap:
	/* Check if the loaded I/O permissions bitmap is the calling thread's */
	EXTERN(this_x86_ioperm_bitmap)
	movP   this_x86_ioperm_bitmap(%Pax), %Pdx
	EXTERN(thiscpu_x86_ioperm_bitmap)
	cmpP   %Pdx, thiscpu_x86_ioperm_bitmap(%Pbx)
	je     __x86_lazy_disable_ioperm_bitmap_return
	/* Must actually unmap the I/O permissions bitmap! */
	EXTERN(thiscpu_x86_iobnode_pagedir_identity)
	movP   thiscpu_x86_iobnode_pagedir_identity(%Pbx), %Pdx
#ifdef __x86_64__
	movzlq $(P64_PAGE_FPREPARED), %rcx
	movq   $(0), thiscpu_x86_ioperm_bitmap(%rbx)
	movq   %rcx, 0x0(%Pdx)
	movq   %rcx, 0x8(%Pdx)
	invlpg (thiscpu_x86_iob + 0 * PAGESIZE)(%Pbx)
	invlpg (thiscpu_x86_iob + 1 * PAGESIZE)(%Pbx)
#else /* __x86_64__ */
	xorl   %ecx, %ecx  /* P32_PAGE_ABSENT / PAE_PAGE_ABSENT */
	movl   %ecx, thiscpu_x86_ioperm_bitmap(%ebx)
	movl   %ecx, 0x0(%Pdx)
	movl   %ecx, 0x4(%Pdx)
#ifndef CONFIG_NO_KERNEL_X86_PAGING_PAE
INTERN_FUNCTION(__x86_lazy_disable_ioperm_bitmap_pae)
	/* When  PAE  paging  is  disabled,  paging  initialization  overrides  this
	 * instruction location with a `jmp __x86_lazy_disable_ioperm_bitmap_return' */
	movl   %ecx, 0x8(%Pdx)
	movl   %ecx, 0xc(%Pdx)
END(__x86_lazy_disable_ioperm_bitmap_pae)
#endif /* !CONFIG_NO_KERNEL_X86_PAGING_PAE */
.alt_if X86_FEAT_INVLPG
	invlpg (thiscpu_x86_iob + 0 * PAGESIZE)(%Pbx)
	invlpg (thiscpu_x86_iob + 1 * PAGESIZE)(%Pbx)
.alt_else
	/* ... */
.alt_endif
#endif /* !__x86_64__ */
	jmp    __x86_lazy_disable_ioperm_bitmap_return
	.cfi_endproc
END(x86_load_thread_Pax_cpu_Pbx)
END(x86_idt_preemption)



#ifdef CONFIG_HAVE_KERNEL_DEBUGGER
.section .text.cold
INTERN_FUNCTION(x86_dbgidt_preemption) /* ISR_X86_f0 */
	.cfi_startproc simple
	.cfi_iret_signal_frame
	.cfi_def_cfa %Psp, 0
#ifdef __x86_64__
	intr_enter INTR
	pushq_cfi_r %rax
#else /* __x86_64__ */
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi_r %eax
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
#endif /* !__x86_64__ */
	pushP_cfi_r %Pcx
	pushP_cfi_r %Pbx

	/* Acknowledge the interrupt. */
.alt_if X86_FEAT_APIC
	EXTERN(x86_lapicbase)
	movP   x86_lapicbase, %Pax
	movl   $(APIC_EOI_FSIGNAL), APIC_EOI(%Pax)
.alt_else
	movb   $(X86_PIC_CMD_EOI), %al
	outb   %al, $(X86_PIC1_CMD)
.alt_endif

.alt_if X86_FEAT_TSC_DEADLINE
	/* Nothing... */
.alt_elseif X86_FEAT_APIC
	/* Account for timings, but don't re-calculate the TSC deadline. */
	movP   %segtls:this_cpu, %Pbx
	EXTERN(thiscpu_x86_apic_emutsc_early_interrupt)
	/* if (FORCPU(me, thiscpu_x86_apic_emutsc_early_interrupt)) {
	 *     FORCPU(me, thiscpu_x86_apic_emutsc_early_interrupt) = false;
	 * } else {
	 *     ... */
	xorb   %cl, %cl
	xchgb  %cl, thiscpu_x86_apic_emutsc_early_interrupt(%Pbx)
	testb  %cl, %cl
	jnz8   1f
	/*     FORCPU(me, thiscpu_x86_apic_emutsc_tscbase) +=
	 *         FORCPU(me, thiscpu_x86_apic_emutsc_initial_shifted); */
	EXTERN(thiscpu_x86_apic_emutsc_tscbase)
	EXTERN(thiscpu_x86_apic_emutsc_initial_shifted)
#ifdef __x86_64__
	movq   thiscpu_x86_apic_emutsc_initial_shifted(%Pbx), %rcx
	addq   %rcx, thiscpu_x86_apic_emutsc_tscbase(%Pbx)
#else /* __x86_64__ */
	movl   thiscpu_x86_apic_emutsc_initial_shifted+0(%Pbx), %ecx
	addl   %ecx, thiscpu_x86_apic_emutsc_tscbase+0(%Pbx)
	movl   thiscpu_x86_apic_emutsc_initial_shifted+4(%Pbx), %ecx
	adcl   %ecx, thiscpu_x86_apic_emutsc_tscbase+4(%Pbx)
#endif /* !__x86_64__ */
	/*     ...
	 * } */
	/* FORCPU(me, thiscpu_x86_apic_emutsc_prev_current) = lapic_read(APIC_TIMER_CURRENT); */
	movl   APIC_TIMER_CURRENT(%Pax), %ecx /* NOTE: %Pax was loaded above! */
	EXTERN(thiscpu_x86_apic_emutsc_prev_current)
	movl   %ecx, thiscpu_x86_apic_emutsc_prev_current(%Pbx)
1:
.alt_else
	/* Account for timings, but don't re-calculate the TSC deadline. */
	movP   %segtls:this_cpu, %Pbx
	EXTERN(thiscpu_x86_apic_emutsc_early_interrupt)
	/* if (FORCPU(me, thiscpu_x86_apic_emutsc_early_interrupt)) {
	 *     FORCPU(me, thiscpu_x86_apic_emutsc_early_interrupt) = false;
	 * } else {
	 *     ... */
	xorb   %cl, %cl
	xchgb  %cl, thiscpu_x86_apic_emutsc_early_interrupt(%Pbx)
	testb  %cl, %cl
	jnz8   1f
	/*     FORCPU(me, thiscpu_x86_apic_emutsc_tscbase) +=
	 *         FORCPU(me, thiscpu_x86_apic_emutsc_initial_shifted); */
	EXTERN(thiscpu_x86_apic_emutsc_tscbase)
	EXTERN(thiscpu_x86_apic_emutsc_initial_shifted)
#ifdef __x86_64__
	movq   thiscpu_x86_apic_emutsc_initial_shifted(%Pbx), %rcx
	addq   %rcx, thiscpu_x86_apic_emutsc_tscbase(%Pbx)
#else /* __x86_64__ */
	movl   thiscpu_x86_apic_emutsc_initial_shifted+0(%Pbx), %ecx
	addl   %ecx, thiscpu_x86_apic_emutsc_tscbase+0(%Pbx)
	movl   thiscpu_x86_apic_emutsc_initial_shifted+4(%Pbx), %ecx
	adcl   %ecx, thiscpu_x86_apic_emutsc_tscbase+4(%Pbx)
#endif /* !__x86_64__ */
	/*     ...
	 * } */
	/* FORCPU(me, thiscpu_x86_apic_emutsc_prev_current) = lapic_read(APIC_TIMER_CURRENT); */

	/* Read the current PIT counter position. */
	movb   $(PIT_COMMAND_SELECT_F0 | PIT_COMMAND_ACCESS_FLATCH | PIT_COMMAND_FBINARY), %al
	outb   %al,  $(PIT_COMMAND)
	inb    $(PIT_DATA0), %al
	movb   %al, %cl
	inb    $(PIT_DATA0), %al
	movb   %al, %ch
	movzwl %cx, %ecx
	movl   %ecx, thiscpu_x86_apic_emutsc_prev_current(%Pbx)
1:
.alt_endif

	popP_cfi_r %Pbx
	popP_cfi_r %Pcx
	popP_cfi_r %Pax
#ifdef __x86_64__
	intr_exit intr_enabled=0
#else /* __x86_64__ */
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
#endif /* !__x86_64__ */
	.cfi_endproc
END(x86_dbgidt_preemption)
#endif /* CONFIG_HAVE_KERNEL_DEBUGGER */



#endif /* !GUARD_KERNEL_CORE_ARCH_I386_SCHED_TSC_S */
