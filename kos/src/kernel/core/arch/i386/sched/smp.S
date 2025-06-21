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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_SCHED_SMP_S
#define GUARD_KERNEL_CORE_ARCH_I386_SCHED_SMP_S 1
#define __ASSEMBLER__ 1
#define _KOS_KERNEL_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/fpu.h> /* CONFIG_HAVE_FPU */
#include <kernel/x86/alternatives.h>
#include <kernel/x86/apic.h>
#include <kernel/x86/breakpoint.h> /* reload_x86_debug_registers */
#include <kernel/x86/cpuid.h>
#include <kernel/x86/idt.h> /* X86_INTERRUPT_APIC_SPURIOUS */
#include <kernel/x86/pic.h> /* X86_INTNO_PIC1_PIT */
#include <sched/cpu.h>

#include <hybrid/host.h>

#include <asm/asmword.h>
#include <cfi.h>
#include <asm/cpu-flags.h>
#include <asm/cpu-msr.h>
#include <asm/instr/compat.h>
#include <asm/instr/ttest.h>
#include <kos/kernel/cpu-state-asm.h>
#include <kos/kernel/cpu-state-compat.h>
#include <kos/kernel/cpu-state.h>
#include <kos/kernel/x86/gdt.h>
#include <kos/kernel/x86/segment.h>
#include <kos/kernel/x86/tss-compat.h>
#include <kos/kernel/x86/tss.h>

#include <stddef.h>
#include <stdint.h>
#ifdef __x86_64__
#include <asm/instr/fsgsbase.h>
#include <asm/instr/interrupt.h>
#include <asm/instr/movzxq.h>
#endif /* __x86_64__ */

/**/
#include "tsc.h" /* CONFIG_HAVE_KERNEL_X86_TSC_ASSERT_FORWARD */

#define PS __SIZEOF_POINTER__

#ifndef CONFIG_NO_SMP

.macro pushP_cfi_r_ss
#ifdef __x86_64__
	pushq_cfi $(SEGMENT_KERNEL_DATA0) /* %ss */
	.cfi_rel_offset %ss, 0
#else /* __x86_64__ */
	pushl_cfi_r %ss
#endif /* !__x86_64__ */
.endm /* pushP_cfi_r_ss */

.macro pushP_cfi_r_cs
#ifdef __x86_64__
	pushq_cfi $(SEGMENT_KERNEL_CODE) /* %cs */
	.cfi_rel_offset %cs, 0
#else /* __x86_64__ */
	pushl_cfi_r %cs
#endif /* !__x86_64__ */
.endm /* pushP_cfi_r_cs */

#ifdef __x86_64__
#define x86_load_thread_Pax_cpu_Pbx    x86_load_thread_rax_cpu_rbx
#define x86_idt_apic_ipi_icpustate_Psp x86_idt_apic_ipi_icpustate_rsp
#else /* __x86_64__ */
#define x86_load_thread_Pax_cpu_Pbx    x86_load_thread_eax_cpu_ebx
#define x86_idt_apic_ipi_icpustate_Psp x86_idt_apic_ipi_icpustate_esp
#endif /* !__x86_64__ */

#ifdef __x86_64__
#define RETURN_FROM_INTERRUPT intr_exit
#else /* __x86_64__ */
#define RETURN_FROM_INTERRUPT iret
#endif /* !__x86_64__ */



.section .text
PUBLIC_FUNCTION(cpu_ipi_service_nopr)
	.cfi_startproc
	/* Simple wrapper around the IPI interrupt handler. */
	popP_cfi %Pax
	.cfi_register %Pip, %Pax
#ifdef __x86_64__
	movq   %rsp, %rcx
	pushP_cfi_r_ss    /* irregs::ir_ss */
	pushq_cfi %rcx    /* irregs::ir_rsp */
#endif /* __x86_64__ */
	pushfP_cfi_r      /* irregs::ir_Pflags */
	pushP_cfi_r_cs    /* irregs::ir_cs */
	pushP_cfi %Pax    /* irregs::ir_Pip */
/*	.cfi_rel_offset %Pip, 0 */
	.cfi_endproc
INTERN_FUNCTION(x86_idt_apic_ipi)
	.cfi_startproc
	.cfi_signal_frame__io
	.cfi_restore_iret
	.cfi_def_cfa %Psp, 0
#ifdef __x86_64__
	intr_enter INTR
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
INTERN_FUNCTION(x86_idt_apic_ipi_icpustate_Psp)

	/* Achnowledge  the  IPI beforehand,  thus  allowing another
	 * to be delivered while we're  still handling the old  one.
	 * The new one will not start executing until the iret below
	 * re-enabled interrupts (if it does so), but our LAPIC will
	 * have already been able to acknowledge the IPI, preventing
	 * the LAPIC of another CPU to be starved by never unsetting
	 * the `APIC_ICR0_FPENDING' bit. */
	EXTERN(x86_lapicbase)
	movP   x86_lapicbase, %Pax
	movl   $(APIC_EOI_FSIGNAL), APIC_EOI(%Pax)

	/* Reset the used action mode. */
	xorP   %Pbp, %Pbp
	EXTERN(this_cpu)
	movP   %segtls:this_cpu, %Pbx

1:	/* Serve pending IPIs */
	movP   %Pbx, %R_fcall0P
	movP   %Psp, %R_fcall1P
	EXTERN(x86_serve_ipi)
	call   x86_serve_ipi
	cmpP   %Pax, %Psp
	je     2f
	/* Check for special IPI commands. */
	cmpP   $(CPU_IPI_MODE_SPECIAL_MIN), %Pax
	jnae   3f

	/* Remember the greatest action that should be performed. */
	negP   %Pax
	cmpP   %Pbp, %Pax
	jbe    1b         /* if (new_action <= action) goto 1b; */
	movP   %Pax, %Pbp /* action = new_action; */
	jmp    1b

	/* Load the new stack and continue serving IPIs */
3:	movP   %Pax, %Psp
	jmp    1b

2:	/* Load all tasks that are pending execution by this CPU.
	 * This must be done _after_ IPIs are served, as the presence
	 * of pending IPIs also prevents more IPIs from being delivered.
	 * XXX: Add some way to have high-priority tasks be switched
	 *      to immediately, rather than having the previous task
	 *      complete its quantum. */
	xorP   %Pdx, %Pdx
	EXTERN(thiscpu_sched_pending)
	/*lock*/ xchgP %Pdx, thiscpu_sched_pending(%Pbx) /* NOTE: `lock' is implicit for `xchg' */
	testP  %Pdx, %Pdx
	jz     .Lapic_ipi_no_pending
#ifndef __x86_64__
	pushl_cfi %edx /* chain */
#endif /* __x86_64__ */
	movP   %Pbx, %R_fcall0P
	EXTERN(this_task)
	movP   %segtls:this_task, %R_fcall1P
	EXTERN(sched_intern_loadpending)
	call   sched_intern_loadpending
#ifndef __x86_64__
	.cfi_adjust_cfa_offset -4
#endif /* __x86_64__ */
	cmpP   %Pax, %segtls:this_task
	je     .Lapic_ipi_no_pending
	/* Remember the thread that the scheduler wants us to switch to. */
	EXTERN(thiscpu_sched_current)
	movP   %Pax, thiscpu_sched_current(%Pbx)
	/* Check if there are more IPIs */
	EXTERN(thiscpu_x86_ipi_inuse)
	cmpP   $(0), thiscpu_x86_ipi_inuse(%Pbx)
	je     .Lipi_switch_tasks
	/* Modify the target thread's CPU state to have it service the remaining IPIs. */
	movP   %Pax, %R_fcall0P
	EXTERN(x86_task_push_serve_ipi)
	call   x86_task_push_serve_ipi
	jmp    .Lipi_switch_tasks
.Lapic_ipi_no_pending:


	/* Check for more  pending IPIs  by looking at  the first  word
	 * of  the IPI in-use bitset. - The  same check is also done by
	 * code used to trigger this  interrupt from other cores,  with
	 * the expectation that the presence of any IPIs allows for the
	 * assumption that no interrupt has  to be fired on the  target
	 * core, in which case it is expected that we handle that  IPI. */
	EXTERN(thiscpu_x86_ipi_inuse)
	cmpP   $(0), thiscpu_x86_ipi_inuse(%Pbx)
	jne    1b

	/* Resume execution, as requested */
	PRIVATE(ipi_action_table)
	jmpP   *ipi_action_table(,%Pbp,PS)

.Lipi_resume:
	.cfi_remember_state
	ASM_POP_ICPUSTATE_BEFORE_HW_IRET_CFI_R
	RETURN_FROM_INTERRUPT
	.cfi_restore_state
.Lipi_switch_tasks:
	/* Complete the full scpustate structure. */
#ifdef __x86_64__
	ASM_PUSH_SGBASE_CFI_R
	ASM_PUSH_SGREGS_CFI_R(%rax)
#else /* __x86_64__ */
	popal_cfi_r
	pushl_cfi %gs
	.cfi_restore_iret_gs_or_offset -16
	pushal_cfi_r
	/* We've clobbered %Pbx with the `popal_cfi_r' above, so re-load it here. */
	EXTERN(this_cpu)
	movP   %segtls:this_cpu, %Pbx
#endif /* !__x86_64__ */

	EXTERN(thiscpu_sched_current)
	movP   thiscpu_sched_current(%Pbx), %Pax

	/* Load the new CPU state */
#ifndef NDEBUG /* TODO: REMOVE ME (>> tsc.S: FIXME: This int3 got hit randomly one time) */
	EXTERN(this_sstate)
	movP   this_sstate(%Pax), %Pcx
	cmpP   $(0x10000000), (OFFSET_SCPUSTATE_IRREGS + OFFSET_IRREGS_PFLAGS)(%Pcx)
	jna    771f /* if (!(STATE.EFLAGS > 0x10000000)) goto 771f; */
	int3
771:
#endif
	EXTERN(x86_load_thread_Pax_cpu_Pbx)
	jmp    x86_load_thread_Pax_cpu_Pbx
	.cfi_endproc
END(x86_idt_apic_ipi_icpustate_Psp)
END(x86_idt_apic_ipi)
END(cpu_ipi_service_nopr)

.section .rodata
PRIVATE_OBJECT(ipi_action_table)
	.wordptr  .Lipi_resume       /* 0 (default action) */
	.wordptr  .Lipi_switch_tasks /* CPU_IPI_MODE_SWITCH_TASKS */
END(ipi_action_table)


.section .text
/* >> INTDEF NOBLOCK NONNULL((1, 2)) void
 * >> NOTHROW(FCALL x86_execute_direct_ipi_nopr)(cpu_ipi_t func,
 * >>                                            void *args[CPU_IPI_ARGCOUNT]); */
INTERN_FUNCTION(x86_execute_direct_ipi_nopr)
	/* ECX: <cpu_ipi_t func> */
	/* EDX: <cpu_ipi_t args> */
	.cfi_startproc
	/* Construct an IRET tail. */
	popP_cfi %Pax
	.cfi_register %Pip, %Pax
#ifdef __x86_64__
	movq   %rsp, %rcx
	pushP_cfi_r_ss    /* irregs::ir_ss */
	pushq_cfi %rcx    /* irregs::ir_rsp */
	.cfi_rel_offset %rsp, 0
#endif /* __x86_64__ */
	pushfP_cfi_r      /* irregs::ir_Pflags */
	pushP_cfi_r_cs    /* irregs::ir_cs */
	pushP_cfi %Pax    /* irregs::ir_Pip */
	.cfi_rel_offset %Pip, 0

	/* Construct a full `struct icpustate' */
	ASM_PUSH_ICPUSTATE_AFTER_IRET_CFI_R

	/* Invoke the IPI function */
	movP   %R_fcall0P, %Pax
	movP   %Psp, %R_fcall0P
	callP  *%Pax

	/* Check for special IPI commands, but ignore them. */
	cmpP   $(CPU_IPI_MODE_SPECIAL_MIN), %Pax
	jae    .Lipi_resume
	movP   %Pax, %Psp
	jmp    .Lipi_resume
	.cfi_endproc
END(x86_execute_direct_ipi_nopr)


.section .text
/* >> INTDEF NOBLOCK NONNULL((1, 2)) void
 * >> NOTHROW(FCALL x86_execute_direct_ipi)(cpu_ipi_t func,
 * >>                                       void *args[CPU_IPI_ARGCOUNT]); */
INTERN_FUNCTION(x86_execute_direct_ipi)
	/* ECX: <cpu_ipi_t func> */
	/* EDX: <cpu_ipi_t args> */
	.cfi_startproc
	/* Construct an IRET tail. */
	popP_cfi %Pax
	.cfi_register %Pip, %Pax
#ifdef __x86_64__
	movq   %rsp, %rcx
	pushP_cfi_r_ss    /* irregs::ir_ss */
	pushq_cfi %rcx    /* irregs::ir_rsp */
	.cfi_rel_offset %rsp, 0
#endif /* __x86_64__ */
	pushfP_cfi_r      /* irregs::ir_Pflags */
	orP    $(EFLAGS_IF), 0(%Psp) /* Make sure that #IF is set in the IRET tail. */
	pushP_cfi_r_cs    /* irregs::ir_cs */
	pushP_cfi %Pax    /* irregs::ir_Pip */
	.cfi_rel_offset %Pip, 0

	/* Construct a full `struct icpustate' */
	ASM_PUSH_ICPUSTATE_AFTER_IRET_CFI_R

	/* Reset the used action mode. */
	xorP   %Pbp, %Pbp

	/* Invoke the IPI function */
	movP   %R_fcall0P, %Pax
	movP   %Psp, %R_fcall0P
	callP  *%Pax

	cmpP   %Psp, %Pax
	je     1f
	/* Check for special IPI commands. */
	cmpP   $(CPU_IPI_MODE_SPECIAL_MIN), %Pax
	jnae   .Lipi_resume
	negP   %Pax
	jmpP   *ipi_action_table(,%Pax,PS)
	/* Load the new stack and continue serving IPIs */
1:	movP   %Pax, %Psp
	jmp    .Lipi_resume
	.cfi_endproc
END(x86_execute_direct_ipi)




/* 16-bit (real-mode) bootstrap code executed by secondary cores.
 * All  this  code  does  is  load  a  GDT  and  use  it  to jump
 * into 32-bit mode at `x86_smp_entry32' */
#define SYM(x) ((x) - KERNEL_CORE_BASE)
.section .text.free
.code16
INTERN_FUNCTION(x86_smp_entry)
	/* Entry address for secondary APs */
	cli
	/* Load the GDT below. */
	/* movw $(*x86_smp_entry_gdt_segment), %sp */
	.byte  0xbc
INTERN_LABEL(x86_smp_entry_gdt_segment):
	.word16 0x1234
	movw   %sp, %ds
/*	lgdtl  %ds:(*x86_smp_entry_gdt_offset) */
	.byte  0x0f, 0x01, 0x16
INTERN_LABEL(x86_smp_entry_gdt_offset):
	.word16 0x5678
	movl   %cr0, %esp
	orw    $(CR0_PE), %sp
	movl   %esp, %cr0
	/* Jump to protected mode. */
	ljmpl  $(0x08), $(SYM(x86_smp_entry32))
INTERN_OBJECT(x86_smp_gdt)
	.word16 ((3 * SIZEOF_SEGMENT_DESCRIPTOR) - 1)
INTERN_LABEL(x86_smp_gdt_pointer_base):
	.word32 (1f - x86_smp_entry)
#define DEFINE_SEGMENT_DESCRIPTOR(TYPE, args) \
	.word32 (SEGMENT_##TYPE##_INIT_UL args); \
	.word32 (SEGMENT_##TYPE##_INIT_UH args);
1:	DEFINE_SEGMENT_DESCRIPTOR(DESCRIPTOR, (0, 0, 0, 0, 0, 0, 0, 0, 0, 0))
	DEFINE_SEGMENT_DESCRIPTOR(DESCRIPTOR, (0, 0xfffff, SEGMENT_DESCRIPTOR_TYPE_CODE_EXRD, 1, 0, 1, 0, 0, 1, 1))
	DEFINE_SEGMENT_DESCRIPTOR(DESCRIPTOR, (0, 0xfffff, SEGMENT_DESCRIPTOR_TYPE_DATA_RDWR, 1, 0, 1, 0, 0, 1, 1))
#undef DEFINE_SEGMENT_DESCRIPTOR
END(x86_smp_gdt)

INTERN_CONST(x86_smp_entry_size, . - x86_smp_entry)
END(x86_smp_entry)


.section .text.free
#ifdef __x86_64__
.code64
#else /* __x86_64__ */
.code32
#endif /* !__x86_64__ */

#undef R_CPU
#undef R_TASK
#ifdef __x86_64__
#define R_CPU   %rbp
#define R_TASK  %rbx
#else /* __x86_64__ */
#define R_CPU   %ebp
#define R_TASK  %ebx
#endif /* !__x86_64__ */

/* Initialize the cpuid feature table of the calling CPU
 * IN:
 *     R_CPU: THIS_CPU
 * OUT:
 *     %Pip:  set to `.Ldone_init_cpuid'
 * CLOBBER:
 *     %Pax
 *     %Pcx
 *     %Pdx
 *     %Pdi
 */
PRIVATE_FUNCTION(x86_smp_init_cpuid)
	EXTERN(thiscpu_x86_cpufeatures)
	movw   $(CPU_FEATURE_FDIDINIT), thiscpu_x86_cpufeatures(R_CPU)

	/* Clear out our CPUID features table. */
	EXTERN(thiscpu_x86_cpuid)
	leaP   thiscpu_x86_cpuid(R_CPU), %Pdi
	xorP   %Pax, %Pax
	cld
#if defined(__x86_64__) && (SIZEOF_CPUID_CPUINFO % 8) == 0
	movq   $(SIZEOF_CPUID_CPUINFO / 8), %rcx
	rep    stosq
#elif (SIZEOF_CPUID_CPUINFO % 4) == 0
	movl   $(SIZEOF_CPUID_CPUINFO / 4), %ecx
	rep    stosl
#else /* ... */
	movl   $(SIZEOF_CPUID_CPUINFO), %ecx
	rep    stosb
#endif /* !... */

	/* Check if CPUID is supported.
	 * On x86_64, the caller will have already performed this check! */
#ifndef __x86_64__
	pushfl
	pushfl
	xorl   $(EFLAGS_ID), 0(%esp)
	popfl
	pushfl
	popl   %eax
	xorl   0(%esp), %eax
	popfl
	andl   $(EFLAGS_ID), %eax
	jz     .Lsmp_init_crN

	/* The `cpuid' instruction is available. */
	EXTERN(thiscpu_x86_cpufeatures)
	orw    $(CPU_FEATURE_FCPUID), thiscpu_x86_cpufeatures(R_CPU)
#endif /* !__x86_64__ */

	movP   %Pbx, %Pdi
	movl   $(1), %eax
	cpuid
	movl   %eax, (thiscpu_x86_cpuid + OFFSET_CPUID_1A)(R_CPU)
	movl   %ebx, (thiscpu_x86_cpuid + OFFSET_CPUID_1B)(R_CPU)
	movl   %edx, (thiscpu_x86_cpuid + OFFSET_CPUID_1D)(R_CPU)
	movl   %ecx, (thiscpu_x86_cpuid + OFFSET_CPUID_1C)(R_CPU)

	/* if (Family == 6 && Model < 3 && Stepping < 3)
	 *     OFFSET_CPUID_1D &= ~CPUID_1D_SEP; */
	ttest  mask=CPUID_1D_SEP, loc=%edx
	jz     1f
	movl   %eax, %ecx
	andl   $(CPUID_1A_FAMILY_M), %ecx
	cmpl   $(6 << CPUID_1A_FAMILY_S), %ecx
	jne    1f  /* if (Family != 6) goto 1f; */
	movl   %eax, %ecx
	andl   $(CPUID_1A_MODEL_M), %ecx
#if CPUID_1A_MODEL_S != 0
	shrl   $(CPUID_1A_MODEL_S), %ecx
#endif /* CPUID_1A_MODEL_S != 0 */
	cmpl   $(3), %ecx
	jae    1f  /* if (Model >= 3) goto 1f; */
	movl   %eax, %ecx
	andl   $(CPUID_1A_STEPPING_M), %ecx
#if CPUID_1A_STEPPING_S != 0
	shrl   $(CPUID_1A_STEPPING_S), %ecx
#endif /* CPUID_1A_STEPPING_S != 0 */
	cmpl   $(3), %ecx
	/* if (Stepping >= 3) goto 1f; */
	jae    1f
	andl   $(~CPUID_1D_SEP), (thiscpu_x86_cpuid + OFFSET_CPUID_1D)(R_CPU)
1:

	movl   $(0), %eax
	cpuid
	movl   %eax, (thiscpu_x86_cpuid + OFFSET_CPUID_0A)(R_CPU)
	movl   %ebx, (thiscpu_x86_cpuid + OFFSET_CPUID_0B)(R_CPU)
	movl   %edx, (thiscpu_x86_cpuid + OFFSET_CPUID_0D)(R_CPU)
	movl   %ecx, (thiscpu_x86_cpuid + OFFSET_CPUID_0C)(R_CPU)

	cmpl   $(7), %eax
	jnae   1f
	movl   $(7), %eax
	movl   $(0), %ecx /* Sub-leaf:0 */
	cpuid
	movl   %edx, (thiscpu_x86_cpuid + OFFSET_CPUID_7D)(R_CPU)
	movl   %ecx, (thiscpu_x86_cpuid + OFFSET_CPUID_7C)(R_CPU)
	movl   %ebx, (thiscpu_x86_cpuid + OFFSET_CPUID_7B)(R_CPU)
1:	movl   $(0x80000000), %eax
	cpuid
	movl   %eax, (thiscpu_x86_cpuid + OFFSET_CPUID_80000000A)(R_CPU)
	cmpl   $(0x80000001), %eax
	jnae   2f
	movl   $(0x80000001), %eax
	cpuid
	movl   %ecx, (thiscpu_x86_cpuid + OFFSET_CPUID_80000001C)(R_CPU)
	movl   %edx, (thiscpu_x86_cpuid + OFFSET_CPUID_80000001D)(R_CPU)
	movl   (thiscpu_x86_cpuid + OFFSET_CPUID_80000000A)(R_CPU), %eax

	cmpl   $(0x80000007), %eax
	jnae   4f
	movl   $(0x80000007), %eax
	cpuid
	movl   %edx, (thiscpu_x86_cpuid + OFFSET_CPUID_80000007D)(R_CPU)
	jmp    5f
4:	cmpl   $(0x80000004), %eax
	jnae   3f
5:

	movl   $(0x80000004), %eax
	cpuid
	movl   %eax, (thiscpu_x86_cpuid + OFFSET_CPUID_80000004A)(R_CPU)
	movl   %ebx, (thiscpu_x86_cpuid + OFFSET_CPUID_80000004B)(R_CPU)
	movl   %ecx, (thiscpu_x86_cpuid + OFFSET_CPUID_80000004C)(R_CPU)
	movl   %edx, (thiscpu_x86_cpuid + OFFSET_CPUID_80000004D)(R_CPU)

	movl   $(0x80000003), %eax
	cpuid
	movl   %eax, (thiscpu_x86_cpuid + OFFSET_CPUID_80000003A)(R_CPU)
	movl   %ebx, (thiscpu_x86_cpuid + OFFSET_CPUID_80000003B)(R_CPU)
	movl   %ecx, (thiscpu_x86_cpuid + OFFSET_CPUID_80000003C)(R_CPU)
	movl   %edx, (thiscpu_x86_cpuid + OFFSET_CPUID_80000003D)(R_CPU)

	movl   $(0x80000002), %eax
	cpuid
	movl   %eax, (thiscpu_x86_cpuid + OFFSET_CPUID_80000002A)(R_CPU)
	movl   %ebx, (thiscpu_x86_cpuid + OFFSET_CPUID_80000002B)(R_CPU)
	movl   %ecx, (thiscpu_x86_cpuid + OFFSET_CPUID_80000002C)(R_CPU)
	movl   %edx, (thiscpu_x86_cpuid + OFFSET_CPUID_80000002D)(R_CPU)
3:  /* ci_80000000a < 0x80000004 */
2:  /* ci_80000000a < 0x80000001 */
	movP   %Pdi, %Pbx

.Lsmp_init_crN:

	movP   %cr0, %Pax
	movP   %cr4, %Pcx

#ifdef CONFIG_HAVE_FPU
	/* Check if KOS was booted with `nofpu' */
	EXTERN(x86_config_nofpu)
	cmpb   $(0), x86_config_nofpu
	jnz    .Lsmp_ini_crN_nofpu
	andP   $(~(CR0_EM | CR0_TS)), %Pax
	/* Check if we're connected to a FPU */
	ttest  mask=CPUID_1D_FPU, loc=(thiscpu_x86_cpuid + OFFSET_CPUID_1D)(R_CPU)
	jnz    .Lsmp_ini_crN_havefpu
	/* No? Ok then.
	 * Check if that's actually true. */
#ifdef __x86_64__
	pushq  $(0x00000000000055aa)
#else /* __x86_64__ */
	pushl  $(0x000055aa)
#endif /* !__x86_64__ */
	movP   %Pax, %cr0
	fninit
	fnstsw 0(%Psp)
	popP   %Pdx
	cmpw   $(0), %dx
	je     .Lsmp_ini_crN_havefpu_override /* We _do_ actually have an FPU */
	/* Nope! Really no FPU here... */
.Lsmp_ini_crN_nofpu:
	/* Force FPU emulation */
	andP   $(~CR0_MP),         %Pax /* Disable for emulated FPU */
	orP    $(CR0_EM | CR0_TS), %Pax
	jmp    .Lsmp_ini_crN_donefpu
.Lsmp_ini_crN_havefpu_override:
	/* Override saved cpuid feature flags, because we know better than they do! */
	orl    $(CPUID_1D_FPU), (thiscpu_x86_cpuid + OFFSET_CPUID_1D)(R_CPU)
	orl    $(CPUID_80000001D_FPU), (thiscpu_x86_cpuid + OFFSET_CPUID_80000001D)(R_CPU)
.Lsmp_ini_crN_havefpu:
	/* TODO: Only set `CR0_ET' if we're connected to a 387 (as opposed to a 287) */
	orP    $(CR0_TS | CR0_ET | CR0_MP), %Pax

	/* Enable native FPU exceptions, if supported. */
#ifndef __x86_64__
	ttest  mask=CPU_FEATURE_FI486, loc=thiscpu_x86_cpufeatures(R_CPU)
	jz     1f
#endif /* !__x86_64__ */
	orP    $(CR0_NE), %Pax /* Native exceptions enable */
#ifndef __x86_64__
1:
#endif /* !__x86_64__ */
	/* Enable SSE, if supported. */
	ttest  mask=CPUID_1D_SSE, loc=(thiscpu_x86_cpuid + OFFSET_CPUID_1D)(R_CPU)
	jz     1f
	orP    $(CR4_OSFXSR/* | CR4_OSXMMEXCPT*/), %Pcx /* TODO: CR4_OSXMMEXCPT */
1:
.Lsmp_ini_crN_donefpu:
#endif /* CONFIG_HAVE_FPU */

	/* Store results */
	EXTERN(thiscpu_x86_saved_cr0)
	movP   %Pax, thiscpu_x86_saved_cr0(R_CPU)
	EXTERN(thiscpu_x86_saved_cr4)
	movP   %Pcx, thiscpu_x86_saved_cr4(R_CPU)
	jmp    .Ldone_init_cpuid
END(x86_smp_init_cpuid)



.section .pdata
.code32
#ifdef __x86_64__
PRIVATE_OBJECT(x86_smp_entry32_ministack)
	.skip 8 /* We only need 8 bytes of stack memory! */
END(x86_smp_entry32_ministack)
PRIVATE_OBJECT(x86_smp_entry32_ministack_lock)
	.byte 0 /* Non-zero if locked */
END(x86_smp_entry32_ministack_lock)

INTERN_FUNCTION(x86_smp_entry32_spin)
	pause
#endif /* __x86_64__ */
INTERN_FUNCTION(x86_smp_entry32)
	/* 32-bit entry point */
	movw   $(0x10), %sp /* x86_smp_gdt_pointer_base[2] */
	movw   %sp, %ds
/*	movw   %sp, %es */ /* Not needed */
	movw   %sp, %ss


#ifdef __x86_64__
	/* Check if CPUID is supported.
	 * NOTE: For this, we need 8 bytes of stack memory... */
	movb   $(1), %al
	lock   xchgb %al, SYM(x86_smp_entry32_ministack_lock)
	testb  %al, %al
	jnz    x86_smp_entry32_spin

	movl   $(SYM(x86_smp_entry32_ministack) + 8), %esp
	pushfl
	pushfl
	xorl   $(EFLAGS_ID), 0(%esp)
	popfl
	pushfl
	popl   %eax
	xorl   0(%esp), %eax
	popfl
	movb   $(0), SYM(x86_smp_entry32_ministack_lock) /* Unlock the temporary stack. */
	andl   $(EFLAGS_ID), %eax
	jz     x86_smp_boot_failure_no_cpuid


	xorl   %eax, %eax
	cpuid
	cmpl   $(1), %eax
	jb     x86_smp_boot_failure_no_cpuid_0x1

	movl   $(0x80000000), %eax
	cpuid
	cmpl   $(0x80000001), %eax
	jnae   x86_smp_boot_failure_no_cpuid_0x80000001

	movl   $(0x80000001), %eax
	cpuid

	/* Test the LM bit. */
	ttest  mask=CPUID_80000001D_LM, loc=%edx
	jz     x86_smp_boot_failure_no_longmode

	/* Test the PAE bit. */
//	ttest mask=CPUID_80000001D_PAE, loc=%edx
//	jz x86_smp_boot_failure_no_pae

	/* Test the PSE bit. */
//	ttest mask=CPUID_80000001D_PSE, loc=%edx
//	jz x86_smp_boot_failure_no_pse

	movl   $(1), %eax
	cpuid

	/* Test the MSR bit. */
	ttest  mask=CPUID_1D_MSR, loc=%edx
	jz     x86_smp_boot_failure_no_msr

	/* Configure the %CR4 register. */
	movl   %cr4, %esp
	/* Enable PageSizeExtension (required for 2Mib pages & long-mode),
	 * as well as  PhysicalAddressExtension (required  for the  48-bit
	 * physical address space needed in long-mode) */
	orl    $(CR4_PSE | CR4_PAE), %esp
	movl   $(1), %eax
	cpuid
	ttest  mask=CPUID_1D_PGE, loc=%edx /* Enable PGE if supported by the host (optional feature) */
	jz     1f
	orl    $(CR4_PGE), %esp
1:

	/* Make sure that leaf #7 is actually supported */
	xorl   %eax, %eax
	cpuid
	cmpl   $(7), %eax
	jnae   2f
	movl   $(7), %eax
	cpuid
	ttest  mask=CPUID_7B_SMEP, loc=%ebx /* Enable SMAP if supported by the host (optional feature) */
	jz     1f
	orl    $(CR4_SMEP), %esp
1:	ttest  mask=CPUID_7B_FSGSBASE, loc=%ebx /* Enable FSGSBASE if supported by the host (emulated if unsupported) */
	jz     1f
	orl    $(CR4_FSGSBASE), %esp
1:
	/* Save the fully configured CR4 register. */
2:	movl   %esp, %cr4


	/* Set the LME bit in the EFER MSR register. */
	movl   $(IA32_EFER), %ecx
	rdmsr
	orl    $(IA32_EFER_LME), %eax /* LongModeEnabled */
	movl   %eax, %esp
	movl   %edx, %ebp

	/* Since we're already here, try to enable some other long-mode extensions,
	 * such   as   the   NXE   bit,   as   well   as   SCE  (SysCallExtensions) */
	movl   $(0x80000001), %eax
	cpuid
	ttest  mask=CPUID_80000001D_NX, loc=%edx
	jz     1f
	orl    $(IA32_EFER_NXE), %esp
1:	ttest  mask=CPUID_80000001D_SYSCALL, loc=%edx
	jz     1f
	orl    $(IA32_EFER_SCE), %esp
1:	/* Save the new configuration. */
	movl   $(IA32_EFER), %ecx
	movl   %esp, %eax
	movl   %ebp, %edx
	wrmsr
#else /* __x86_64__ */
	/* Configure extended paging features.
	 * This has to  be done before  we can load  `pagedir_kernel', as features  such
	 * as PAE, or even just use of the GLOBAL bit would otherwise cause #PFs because
	 * the CPU would claim that reserved bits were set, or who-know-what in the case
	 * of the PAE page table really just being a completely different structure than
	 * the P32 page table.
	 * XXX: This assumes that all CPUs have the same feature-set as the boot cpu... */
	movl   %cr4, %esp
#ifndef CONFIG_NO_KERNEL_X86_PAGING_PAE
	/* Enable PAE support (if necessary for setting the page directory) */
#ifndef CONFIG_NO_KERNEL_X86_PAGING_P32
	EXTERN(bootcpu_x86_cpuid)
	ttest  mask=CPUID_1D_PAE, loc=((bootcpu_x86_cpuid - KERNEL_CORE_BASE) + OFFSET_CPUID_1D)
	jz     1f
#endif /* !CONFIG_NO_KERNEL_X86_PAGING_P32 */
	orl    $(CR4_PAE), %esp
	/* Enable NX support (if necessary for setting the page directory) */
	EXTERN(bootcpu_x86_cpuid)
	ttest  mask=CPUID_80000001D_NX, loc=((bootcpu_x86_cpuid - KERNEL_CORE_BASE) + OFFSET_CPUID_80000001D)
	jz     1f
	movl   $(IA32_EFER), %ecx
	rdmsr
	orl    $(IA32_EFER_NXE), %eax
	wrmsr
	/* With PAE + NX, try to enable its effects while
	 * in kernel-space  (if  supported  by  the  CPU) */
	ttest  mask=CPUID_7B_SMEP, loc=(bootcpu_x86_cpuid + OFFSET_CPUID_7B)
	jz     1f
	orl    $(CR4_SMEP), %esp
1:
#endif /* !CONFIG_NO_KERNEL_X86_PAGING_PAE */
	/* Enable PGE support (if necessary for setting the page directory) */
	ttest  mask=CPUID_1D_PGE, loc=((bootcpu_x86_cpuid - KERNEL_CORE_BASE) + OFFSET_CPUID_1D)
	jz     1f
	orl    $(CR4_PGE), %esp
1:	movl   %esp, %cr4
#endif /* !__x86_64__ */

	/* Enable paging.
	 * NOTE: This  is why this  part must appear  in the .pdata section.
	 *       Because  we still  are in  physical memory,  we must enable
	 *       paging in a context where the page directory we're enabling
	 *       has our current location mapped to ourselves.
	 *       Later then, we'll jump into true virtual memory, but for
	 *       now,  our  actual  PC  is  offset  by `KERNEL_CORE_BASE' */
	movl   $(pagedir_kernel_phys), %esp
	movl   %esp, %cr3

	/* Now to actually enable paging! */
	movl   %cr0, %esp
	orl    $(CR0_PG | CR0_WP), %esp
	movl   %esp, %cr0

#ifdef __x86_64__
	/* Load a GDT that can be used for entering long mode. */
	lgdtl  SYM(smp64_enterlong_gdt_pointer)

	/* Load 64-bit segment registers. */
	movw   $(0x10), %sp /* DATA */
	movw   %sp, %ds
/*	movw   %sp, %es */ /* Not needed */
/*	movw   %sp, %fs */ /* Not needed */
/*	movw   %sp, %gs */ /* Not needed */
	movw   %sp, %ss

	/* And finally, jump into 64-bit mode! */
	ljmpl  $(0x08), $(SYM(x86_smp_entry64))
END(x86_smp_entry32)
END(x86_smp_entry32_spin)

DEFINE_PRIVATE_ALIAS(x86_smp_boot_failure_no_cpuid, x86_smp_boot_failure)
DEFINE_PRIVATE_ALIAS(x86_smp_boot_failure_no_cpuid_0x1, x86_smp_boot_failure)
DEFINE_PRIVATE_ALIAS(x86_smp_boot_failure_no_cpuid_0x80000001, x86_smp_boot_failure)
DEFINE_PRIVATE_ALIAS(x86_smp_boot_failure_no_longmode, x86_smp_boot_failure)
DEFINE_PRIVATE_ALIAS(x86_smp_boot_failure_no_msr, x86_smp_boot_failure)
PRIVATE_FUNCTION(x86_smp_boot_failure)
	cli
	hlt
	jmp    x86_smp_boot_failure
END(x86_smp_boot_failure)


.align 8
PRIVATE_OBJECT(smp64_enterlong_gdt)
#define DEFINE_SEGMENT_DESCRIPTOR(TYPE, args) \
	.word32(SEGMENT_##TYPE##_INIT_UL args);   \
	.word32(SEGMENT_##TYPE##_INIT_UH args);
	DEFINE_SEGMENT_DESCRIPTOR(DESCRIPTOR, (0, 0, 0, 0, 0, 0, 0, 0, 0, 0))
	DEFINE_SEGMENT_DESCRIPTOR(DESCRIPTOR, (0, 0xfffff, SEGMENT_DESCRIPTOR_TYPE_CODE_EXRD, 1, 0, 1, 0, /*L*/ 1, 0, 1))
	DEFINE_SEGMENT_DESCRIPTOR(DESCRIPTOR, (0, 0xfffff, SEGMENT_DESCRIPTOR_TYPE_DATA_RDWR, 1, 0, 1, 0, /*L*/ 1, 0, 1))
#undef DEFINE_SEGMENT_DESCRIPTOR
.Lsmp64_enterlong_gdt_end = .
END(smp64_enterlong_gdt)
.align 2
PRIVATE_OBJECT(smp64_enterlong_gdt_pointer)
	.word16 ((.Lsmp64_enterlong_gdt_end - smp64_enterlong_gdt) - 1)
	.word32 (SYM(smp64_enterlong_gdt))
END(smp64_enterlong_gdt_pointer)

.code64
INTERN_FUNCTION(x86_smp_entry64)
	/* 64-bit entry point */
#endif /* __x86_64__ */

	/* Figure out who we actually are by looking at our LAPIC id. */
	EXTERN(x86_lapicbase)
	movP   x86_lapicbase, %Psp
	movl   APIC_ID(%Psp), %esp
	shrl   $(APIC_ID_FSHIFT), %esp

	/* Find the CPU how's APIC_ID matches `%sp' (and that'll be us then) */
	EXTERN(cpu_count)
	movzlP cpu_count, %Pcx
	decP   %Pcx
	EXTERN(cpu_vector)
1:	movP   cpu_vector(,%Pcx,PS), R_CPU
	EXTERN(thiscpu_x86_lapicid)
	movzbw thiscpu_x86_lapicid(R_CPU), %dx
	cmpw   %dx, %sp
	je     1f
	loop   1b
	jmp    .Lx86_smp_kill
1:
	/* Change CPU state to indicate that we're going to initialize! */
	EXTERN(thiscpu_state)
	movP   $(CPU_STATE_RUNNING), thiscpu_state(R_CPU)
	EXTERN(cpu_online_count)
	lock   incl cpu_online_count

	/* Found our CPU (now stored in R_CPU) */
	EXTERN(thiscpu_sched_current)
	movP   thiscpu_sched_current(R_CPU), R_TASK /* TARGET task. */
	EXTERN(this_sstate)
	movP   this_sstate(R_TASK), %Psp            /* stack */
#ifndef NDEBUG /* TODO: REMOVE ME (>> tsc.S: FIXME: This int3 got hit randomly one time) */
	cmpP   $(0x10000000), (OFFSET_SCPUSTATE_IRREGS + OFFSET_IRREGS_PFLAGS)(%Psp)
	jna    771f /* if (!(STATE.EFLAGS > 0x10000000)) goto 771f; */
	int3
771:
#endif

	/* Load the GDT of our new CPU */
	EXTERN(thiscpu_x86_saved_gdtr)
	lgdtP  thiscpu_x86_saved_gdtr(R_CPU)

	/* Load basic segments. */
	movw   $(SEGMENT_USER_DATA_RPL), %cx
	movw   %cx, %ds
	movw   %cx, %es
#ifdef __x86_64__
	movw   %cx, %fs
	movw   %cx, %gs
#endif /* __x86_64__ */

	/* Load the Task register. */
	/* SEGMENTS[SEGMENT_CPU_TSS].busy = 0;  // Required for `ltr' */
	EXTERN(thiscpu_x86_saved_tr)
	movzwP thiscpu_x86_saved_tr(R_CPU), %Pcx
	EXTERN(thiscpu_x86_gdt)
	andb   $(0b11111101), (thiscpu_x86_gdt + 5)(R_CPU, %Pcx, 1)
	ltrw   %cx

	/* Load the local descriptor table. */
	EXTERN(thiscpu_x86_saved_ldtr)
	movw   thiscpu_x86_saved_ldtr(R_CPU), %cx
	lldtw  %cx

	/* Load remaining segments and jump to virtual memory. */
#ifdef __x86_64__
	movq   %rsp, %rax
	pushq  $(SEGMENT_KERNEL_DATA0) /* %ss */
	pushq  %rax                    /* %rsp */
	pushfq                         /* %rflags */
	pushq  $(SEGMENT_KERNEL_CODE)  /* %cs */
	pushq  $(1f)                   /* %rip */
	iretq  /* Jump to our per-cpu 64-bit code segment. */
#else /* __x86_64__ */
	movw   $(SEGMENT_KERNEL_DATA), %cx
	movw   %cx, %ss
	ljmpl  $(SEGMENT_KERNEL_CODE), $(1f)
#endif /* !__x86_64__ */
1:

	/* Load the interrupt descriptor table. */
	EXTERN(thiscpu_x86_saved_idtr)
	lidtP  thiscpu_x86_saved_idtr(R_CPU)

	/* ============== Configure cpuid features ============== */
	/* R_CPU:  THIS_CPU
	 * R_TASK: THIS_TASK */

	/* Check if we've already filled in our CPUID features table. */
	EXTERN(thiscpu_x86_cpufeatures)
	ttest  mask=CPU_FEATURE_FDIDINIT, loc=thiscpu_x86_cpufeatures(R_CPU)
	jz     x86_smp_init_cpuid
.Ldone_init_cpuid:

	/* Load saved %cr0 and %cr4 registers. */
	movP   thiscpu_x86_saved_cr0(R_CPU), %Pax
#ifdef CONFIG_HAVE_FPU
	orP    $(CR0_TS), %Pax /* Force a lazy FPU context switch */
#endif /* CONFIG_HAVE_FPU */
	movP   %Pax, %cr0
	movP   thiscpu_x86_saved_cr4(R_CPU), %Pax
	movP   %Pax, %cr4

	/* If supported, initialize the `sysenter' instruction */
	ttest  mask=CPUID_1D_SEP, loc=(thiscpu_x86_cpuid + OFFSET_CPUID_1D)(R_CPU)
	jz     .Ldone_sysenter

	/* __wrmsr(IA32_SYSENTER_CS, SEGMENT_KERNEL_CODE); */
	xorP   %Pdx, %Pdx
	movl   $(SEGMENT_KERNEL_CODE), %eax
	movl   $(IA32_SYSENTER_CS), %ecx
	wrmsr

	/* __wrmsr(IA32_SYSENTER_ESP, (uintptr_t)&PERCPU(thiscpu_x86_tss).t_psp0); */
#ifdef __x86_64__
	leaq   (thiscpu_x86_tss + OFFSET_TSS_RSP0)(R_CPU), %rax
	movq   %rax, %rdx
	shrq   $(32), %rdx
	movzlq %eax, %rax
#else /* __x86_64__ */
	leal   (thiscpu_x86_tss + OFFSET_TSS_ESP0)(R_CPU), %eax
	xorl   %edx, %edx
#endif /* !__x86_64__ */
	movl   $(IA32_SYSENTER_ESP), %ecx
	wrmsr

	/* __wrmsr(IA32_SYSENTER_EIP, (uintptr_t)x86_syscall32_sysenter[_traced]); */
	EXTERN(x86_syscall32_sysenter)
	movP   $(x86_syscall32_sysenter), %Pax
#ifndef CONFIG_NO_KERNEL_SYSCALL_TRACING
	EXTERN(syscall_tracing_enabled)
	cmpb   $(0), syscall_tracing_enabled
	je     1f
	EXTERN(x86_syscall32_sysenter_traced)
	movP   $(x86_syscall32_sysenter_traced), %Pax
1:
#endif /* !CONFIG_NO_KERNEL_SYSCALL_TRACING */
#ifdef __x86_64__
	movq   %rax, %rdx
	shrq   $(32), %rdx
	movzlq %eax, %rax
#else /* __x86_64__ */
	xorl   %edx, %edx
#endif /* !__x86_64__ */
	movl   $(IA32_SYSENTER_EIP), %ecx
	wrmsr
.Ldone_sysenter:


	/* If supported, initialize the `syscall' instruction */
#ifdef __x86_64__
	ttest  mask=CPUID_80000001D_SYSCALL, loc=(thiscpu_x86_cpuid + OFFSET_CPUID_80000001D)(R_CPU)
	jz     .Ldone_syscall

	/* __wrmsr(IA32_STAR, (u64)SEGMENT_KERNEL_CODE  <<  32   |
	 *                    (u64)SEGMENT_USER_CODE32_RPL << 48); */
	movl   $(IA32_STAR), %ecx
	rdmsr  /* Preserve the lower 32 bits! (in %eax)
	        * Intel defines these bits as RESERVED, so they mustn't be altered. */
	movl   $(SEGMENT_KERNEL_CODE | SEGMENT_USER_CODE32_RPL << 16), %edx
	wrmsr

	/* __wrmsr(IA32_FMASK, EFLAGS_IF); */
	xorl   %edx, %edx
	movl   $(EFLAGS_IF), %eax
	movl   $(IA32_FMASK), %ecx
	wrmsr

	/* __wrmsr(IA32_LSTAR, (u64)&x86_syscall64_syscall[_traced]); */
	EXTERN(x86_syscall64_syscall)
	movq   $(x86_syscall64_syscall), %rax
#ifndef CONFIG_NO_KERNEL_SYSCALL_TRACING
	EXTERN(syscall_tracing_enabled)
	cmpb   $(0), syscall_tracing_enabled
	je     1f
	EXTERN(x86_syscall64_syscall_traced)
	movq   $(x86_syscall64_syscall_traced), %rax
1:
#endif /* !CONFIG_NO_KERNEL_SYSCALL_TRACING */
	movq   %rax, %rdx
	shrq   $(32), %rdx
	movzlq %eax, %rax
	movl   $(IA32_LSTAR), %ecx
	wrmsr

	/* TODO: `IA32_CSTAR' must be set to some kernel-space PC location
	 *       that is used  to handle user-space  using `syscall'  from
	 *       32-bit mode!
	 *       On  Intel CPUs, this MSR isn't used, and the CPU natively
	 *       causes a #UD to  be thrown, but AMD  CPUs do make use  of
	 *       this MSR, so we must still program it, else the CPU might
	 *       end up jumping  to some user-space  text location when  a
	 *       32-bit program makes use of `syscall'! */

.Ldone_syscall:
#endif /* __x86_64__ */

.Ldo_init_with_task_and_stack:

	/* Load the VM of the target task. */
	EXTERN(this_mman)
	movP   this_mman(R_TASK), %Pcx
	EXTERN(thismman_pagedir_p)
	movP   thismman_pagedir_p(%Pcx), %Pax
	EXTERN(thiscpu_pdir)
	movP   %Pax, thiscpu_pdir(R_CPU) /* Update the per-cpu current-pdir field. */
	movP   %Pax, %cr3

	/* Set up tracing to appear as though we're nothing but an interrupt originating
	 * from  whereever  we're  supposed  to  start  executing  the  provided thread. */
	.cfi_startproc simple
	.cfi_signal_frame__entry
	.cfi_def_cfa %Psp, OFFSET_SCPUSTATE_IRREGS
#ifdef __x86_64__
	ASM_CFI_REL_OFFSET_RESTORE_SGBASE(OFFSET_SCPUSTATE_SGBASE)
	ASM_CFI_REL_OFFSET_RESTORE_SGREGS(OFFSET_SCPUSTATE_SGREGS)
	ASM_CFI_REL_OFFSET_RESTORE_GPREGSNSP(OFFSET_SCPUSTATE_GPREGSNSP)
	ASM_CFI_REL_OFFSET_RESTORE_IRREGS(OFFSET_SCPUSTATE_IRREGS)
#else /* __x86_64__ */
	.cfi_restore_iret_eip
	.cfi_restore_iret_cs
	.cfi_restore_iret_eflags
	.cfi_restore_iret_esp
	.cfi_restore_iret_ss
	.cfi_rel_offset %edi, OFFSET_SCPUSTATE_GPREGS + OFFSET_GPREGS_EDI
	.cfi_rel_offset %esi, OFFSET_SCPUSTATE_GPREGS + OFFSET_GPREGS_ESI
	.cfi_rel_offset %ebp, OFFSET_SCPUSTATE_GPREGS + OFFSET_GPREGS_EBP
/*	.cfi_rel_offset %esp, OFFSET_SCPUSTATE_GPREGS + OFFSET_GPREGS_ESP */
	.cfi_rel_offset %ebx, OFFSET_SCPUSTATE_GPREGS + OFFSET_GPREGS_EBX
	.cfi_rel_offset %edx, OFFSET_SCPUSTATE_GPREGS + OFFSET_GPREGS_EDX
	.cfi_rel_offset %ecx, OFFSET_SCPUSTATE_GPREGS + OFFSET_GPREGS_ECX
	.cfi_rel_offset %eax, OFFSET_SCPUSTATE_GPREGS + OFFSET_GPREGS_EAX
	.cfi_restore_iret_es_or_offset ((OFFSET_SCPUSTATE_SGREGS + OFFSET_SGREGS_ES) - OFFSET_SCPUSTATE_IRREGS)
	.cfi_restore_iret_ds_or_offset ((OFFSET_SCPUSTATE_SGREGS + OFFSET_SGREGS_DS) - OFFSET_SCPUSTATE_IRREGS)
	.cfi_restore_iret_fs_or_offset ((OFFSET_SCPUSTATE_SGREGS + OFFSET_SGREGS_FS) - OFFSET_SCPUSTATE_IRREGS)
	.cfi_restore_iret_gs_or_offset ((OFFSET_SCPUSTATE_SGREGS + OFFSET_SGREGS_GS) - OFFSET_SCPUSTATE_IRREGS)
#endif /* !__x86_64__ */

	/* Reload debug registers */
	reload_x86_debug_registers %Pcx, %Pax, %Pdx, 0

	/* R_CPU:   THIS_CPU   (%rbp)
	 * R_TASK:  THIS_TASK  (%rbx) */

	/* Load other scheduler-related register values. */
	EXTERN(this_x86_kernel_psp0)
	movP   this_x86_kernel_psp0(R_TASK), %Pcx
	EXTERN(thiscpu_x86_tss)
	movP   %Pcx, (thiscpu_x86_tss + OFFSET_TSS_PSP0)(R_CPU)

	/* Load segment register bases. */
#ifndef __x86_64__
	EXTERN(thiscpu_x86_gdt)
#define GDT(x) x + thiscpu_x86_gdt(R_CPU)
	/* SEGMENT_KERNEL_FSBASE */
	movl   R_TASK, %ecx
	movl   R_TASK, %edx
	shrl   $(24),  %ecx
	andl   $(0x00ffffff), %edx
	andl   $(0xff000000), OFFSET_SEGMENT_DESCRIPTOR_BASE0 + GDT(SEGMENT_KERNEL_FSBASE) /* Clear out base_low */
	orl    %edx,          OFFSET_SEGMENT_DESCRIPTOR_BASE0 + GDT(SEGMENT_KERNEL_FSBASE) /* Set base_low */
	movb   %cl,           OFFSET_SEGMENT_DESCRIPTOR_BASE2 + GDT(SEGMENT_KERNEL_FSBASE) /* Set base_hi */

	/* SEGMENT_USER_FSBASE */
	EXTERN(this_x86_user_fsbase)
	movl   this_x86_user_fsbase(R_TASK), %ecx
	movl   %ecx, %edx
	shrl   $(24),  %ecx
	andl   $(0x00ffffff), %edx
	andl   $(0xff000000), OFFSET_SEGMENT_DESCRIPTOR_BASE0 + GDT(SEGMENT_USER_FSBASE) /* Clear out base_low */
	orl    %edx,          OFFSET_SEGMENT_DESCRIPTOR_BASE0 + GDT(SEGMENT_USER_FSBASE) /* Set base_low */
	movb   %cl,           OFFSET_SEGMENT_DESCRIPTOR_BASE2 + GDT(SEGMENT_USER_FSBASE) /* Set base_hi */

	/* SEGMENT_USER_GSBASE */
	EXTERN(this_x86_user_gsbase)
	movl   this_x86_user_gsbase(R_TASK), %ecx
	movl   %ecx, %edx
	shrl   $(24),  %ecx
	andl   $(0x00ffffff), %edx
	andl   $(0xff000000), OFFSET_SEGMENT_DESCRIPTOR_BASE0 + GDT(SEGMENT_USER_GSBASE) /* Clear out base_low */
	orl    %edx,          OFFSET_SEGMENT_DESCRIPTOR_BASE0 + GDT(SEGMENT_USER_GSBASE) /* Set base_low */
	movb   %cl,           OFFSET_SEGMENT_DESCRIPTOR_BASE2 + GDT(SEGMENT_USER_GSBASE) /* Set base_hi */
#undef GDT
#endif /* !__x86_64__ */

#ifdef CONFIG_HAVE_FPU
	/* Indicate that no task is currently holding an FPU context.
	 * NOTE: Technically, we could also move this part into `cpu_enter_deepsleep()',
	 *       however it's safer  to unconditionally do  this during  initialization! */
	EXTERN(thiscpu_fputhread)
	movP   $(0), thiscpu_fputhread(R_CPU)
#endif /* CONFIG_HAVE_FPU */

	/* Enable the APIC/TSC of this CPU, thus also enabling preemptive interrupts. */
.alt_if X86_FEAT_TSC_DEADLINE
	/* Set the TSC deadline to its max value. */
	movP   $-1, %Pax
	movl   %eax, %edx
	movl   $(IA32_TSC_DEADLINE), %ecx
	wrmsr
#ifdef __x86_64__
	movq   %rax, thiscpu_x86_apic_emutsc_deadline(R_CPU)
#else /* __x86_64__ */
	movl   %eax, thiscpu_x86_apic_emutsc_deadline(R_CPU)
	movl   %eax, thiscpu_x86_apic_emutsc_deadline+4(R_CPU)
#endif /* !__x86_64__ */
	EXTERN(x86_lapicbase)
	movP   x86_lapicbase, %Pax
	/* Enable the APIC timer in TSC-deadline mode. */
#define lapic_write(offset, value) movl   $(value), (offset)(%Pax)
	lapic_write(APIC_SPURIOUS, APIC_SPURIOUS_FENABLED | X86_INTERRUPT_APIC_SPURIOUS)
	lapic_write(APIC_TIMER,    X86_INTNO_PIC1_PIT | APIC_TIMER_MODE_FTSCDEADLINE)
#undef lapic_write

.alt_else
	/* PURE APIC */
	EXTERN(x86_lapicbase)
	movP   x86_lapicbase, %Pax
#define lapic_write(offset, value) movl   $(value), (offset)(%Pax)
	lapic_write(APIC_SPURIOUS,      APIC_SPURIOUS_FENABLED | X86_INTERRUPT_APIC_SPURIOUS)
	lapic_write(APIC_TIMER,         X86_INTNO_PIC1_PIT | APIC_TIMER_MODE_FPERIODIC)
	lapic_write(APIC_TIMER_DIVIDE,  APIC_TIMER_DIVIDE_F128)
	lapic_write(APIC_TIMER_INITIAL, UINT32_MAX)
#undef lapic_write
	/* Initialize per-cpu variables related to emutsc */
	xorP   %Pax, %Pax
#ifdef __x86_64__
	movq   %rax, thiscpu_x86_apic_emutsc_tscbase(R_CPU)
#ifdef CONFIG_HAVE_KERNEL_X86_TSC_ASSERT_FORWARD
	movq   %rax, thiscpu_x86_last_tsc(R_CPU)
#endif /* CONFIG_HAVE_KERNEL_X86_TSC_ASSERT_FORWARD */
#else /* __x86_64__ */
	movl   %eax, thiscpu_x86_apic_emutsc_tscbase(R_CPU)
	movl   %eax, thiscpu_x86_apic_emutsc_tscbase+4(R_CPU)
#ifdef CONFIG_HAVE_KERNEL_X86_TSC_ASSERT_FORWARD
	movl   %eax, thiscpu_x86_last_tsc(R_CPU)
	movl   %eax, thiscpu_x86_last_tsc+4(R_CPU)
#endif /* CONFIG_HAVE_KERNEL_X86_TSC_ASSERT_FORWARD */
#endif /* !__x86_64__ */
	movb   %al, thiscpu_x86_apic_emutsc_early_interrupt(R_CPU)
	movb   $(7), thiscpu_x86_apic_emutsc_divide(R_CPU)
	decP   %Pax /* %Pax = UINT[32|64]_MAX */
	movl   %eax, thiscpu_x86_apic_emutsc_prev_current(R_CPU)
#ifdef __x86_64__
	movq   %rax, thiscpu_x86_apic_emutsc_deadline(R_CPU)
#else /* __x86_64__ */
	movl   %eax, thiscpu_x86_apic_emutsc_deadline(R_CPU)
	movl   %eax, thiscpu_x86_apic_emutsc_deadline+4(R_CPU)
#endif /* !__x86_64__ */
	movl   %eax, thiscpu_x86_apic_emutsc_initial(R_CPU)
	shll   $(7), %eax /* %eax = (u32)(UINT32_MAX << 7) */
	movl   %eax, thiscpu_x86_apic_emutsc_initial_shifted(R_CPU)
	movl   $(0x7f), thiscpu_x86_apic_emutsc_initial_shifted+4(R_CPU)
.alt_endif

	/* re-sync the realtime() clock and set-up the initial TSC deadline. */
	movP   R_CPU, %R_fcall0P
	EXTERN(tsc_resync_init)
	call   tsc_resync_init

	/* Check for, and load all threads that are pending execution by our CPU. */
	xorP   %Pdx, %Pdx
	EXTERN(thiscpu_sched_pending)
	/*lock*/ xchgP %Pdx, thiscpu_sched_pending(R_CPU)
	testP  %Pdx, %Pdx
	jz     1f
#ifndef __x86_64__
	pushl_cfi %edx /* chain */
#endif /* __x86_64__ */
	movP   R_CPU,  %R_fcall0P
	movP   R_TASK, %R_fcall1P
	/* Ensure that we're calling `sched_intern_loadpending' with a valid TLS context. */
#ifdef __x86_64__
	wrgsbaseq R_TASK
#else /* __x86_64__ */
	/* Load kernel-space segments. */
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
#endif /* !__x86_64__ */
	EXTERN(sched_intern_loadpending)
	call   sched_intern_loadpending
#ifndef __x86_64__
	.cfi_adjust_cfa_offset -4
#endif /* __x86_64__ */
	cmpP   %Pax, R_TASK
	je     1f
	/* Start execution with a different thread. */
	EXTERN(thiscpu_sched_current)
	movP   %Pax, thiscpu_sched_current(R_CPU)
	movP   %Pax, R_TASK
	movP   this_sstate(%Pax), %Psp /* stack */
#ifndef NDEBUG /* TODO: REMOVE ME (>> tsc.S: FIXME: This int3 got hit randomly one time) */
	cmpP   $(0x10000000), (OFFSET_SCPUSTATE_IRREGS + OFFSET_IRREGS_PFLAGS)(%Psp)
	jna    771f /* if (!(STATE.EFLAGS > 0x10000000)) goto 771f; */
	int3
771:
#endif
	jmp    .Ldo_init_with_task_and_stack
1:


	/* (Partially) load the underlying CPU state */
#ifdef __x86_64__
	ASM_POP_SGREGS_CFI_R(%rax)
	ASM_POP_SGBASE_CFI_R
	wrgsbaseq R_TASK
#else /* __x86_64__ */
	popal_cfi_r
	popl_cfi_r %gs
	pushal_cfi_r
	/* Load kernel-space segments. */
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
#endif /* !__x86_64__ */

	/* Service pending IPIs for the first time.
	 * -> Since we got here thanks to an INIT IPI, regular IPI callbacks
	 *    would not have generated their IPI interrupt, meaning we  have
	 *    to manually check for callbacks this one time.
	 * NOTE: Since `x86_serve_ipi()' expects an `icpustate' structure,
	 *       we were forced to partially unwind the CPU state so-as to
	 *       already pre-load the `%segtls' register. */
	EXTERN(this_cpu)
	movP   %segtls:this_cpu, %R_fcall0P
	movP   %Psp, %R_fcall1P
	EXTERN(x86_serve_ipi)
	call   x86_serve_ipi
	movP   %Pax, %Psp

	ASM_POP_ICPUSTATE_BEFORE_HW_IRET_CFI_R
	RETURN_FROM_INTERRUPT
	.cfi_endproc
#ifdef __x86_64__
END(x86_smp_entry64)
#else /* __x86_64__ */
END(x86_smp_entry32)
#endif /* !__x86_64__ */



.section .text.cold
/* FUNDEF void NOTHROW(FCALL cpu_enter_deepsleep)(struct cpu *__restrict caller); */
PUBLIC_FUNCTION(cpu_enter_deepsleep)
	.cfi_startproc
	/* Construct an IRET tail. */
	popP_cfi %Pax
	.cfi_register %Pip, %Pax
#ifdef __x86_64__
	movq   %rsp, %rcx
	pushP_cfi_r_ss    /* irregs::ir_ss */
	pushq_cfi %rcx    /* irregs::ir_rsp */
	.cfi_rel_offset %rsp, 0
#endif /* __x86_64__ */
	pushfP_cfi_r      /* irregs::ir_Pflags */
	orP    $(EFLAGS_IF), 0(%Psp) /* Re-enable interrupts upon return */
	pushP_cfi_r_cs    /* irregs::ir_cs */
	pushP_cfi %Pax    /* irregs::ir_Pip */
	.cfi_rel_offset %Pip, 0

	/* Construct a `struct scpustate' on-stack */
#ifdef __x86_64__
	ASM_PUSH_GPREGSNSP_CFI_R /* gpregs */
	ASM_PUSH_SGBASE_CFI_R
	ASM_PUSH_SGREGS_CFI_R(%rax)
#else /* __x86_64__ */
	ASM_PUSH_SCPUSTATE_AFTER_HW_IRET_CFI_R
#endif /* !__x86_64__ */

#ifdef CONFIG_HAVE_FPU
	/* With the CPU about to go OFFLINE, make sure to also save the current
	 * FPU state (if the FPU was used), so-as to not lose that  information
	 * and have it still be available when we come back online. */
	EXTERN(thiscpu_fputhread)
	movP   thiscpu_fputhread(%R_fcall0P), %Pax
	testP  %Pax, %Pax
	jz     1f
	clts   /* Make sure FPU access is allowed. */
	/* Save the current FPU context into `this_fpustate(%Pax)' */
	movP   %R_fcall0P, %Pbx /* Preserve THIS_CPU */
	EXTERN(this_fpustate)
	movP   this_fpustate(%Pax), %R_fcall0P
	EXTERN(x86_fpustate_save)
	call   x86_fpustate_save
	movP   %Pbx, %R_fcall0P /* Restore THIS_CPU */
1:
#endif /* CONFIG_HAVE_FPU */

	/* Save   the   current   RGDT/IDTR/LDTR/TR   in   some   PERCPU   field.
	 * There  are  system  functions   that  will  temporarily  alter   these
	 * registers for all CPUs on the system, (e.g. `x86_idt_modify_begin()'),
	 * so if these registers currently  contain non-standard values, then  we
	 * mustn't clobber them,  as would happen  as the result  of us going  to
	 * deep sleep, before  being re-awokened,  at which point  we'd load  the
	 * original  (standard)  values, rather  than  those that  were  set just
	 * prior to us going to deep-sleep. */
	EXTERN(thiscpu_x86_saved_gdtr)
	sgdtP  thiscpu_x86_saved_gdtr(%R_fcall0P)
	EXTERN(thiscpu_x86_saved_idtr)
	sidtP  thiscpu_x86_saved_idtr(%R_fcall0P)
	EXTERN(thiscpu_x86_saved_ldtr)
	sldtw  thiscpu_x86_saved_ldtr(%R_fcall0P)
	EXTERN(thiscpu_x86_saved_tr)
	strw   thiscpu_x86_saved_tr(%R_fcall0P)
	movP   %cr0, %Pax
	EXTERN(thiscpu_x86_saved_cr0)
	movP   %Pax, thiscpu_x86_saved_cr0(%R_fcall0P)
	movP   %cr4, %Pax
	EXTERN(thiscpu_x86_saved_cr4)
	movP   %Pax, thiscpu_x86_saved_cr4(%R_fcall0P)



	/* Decrement the cpu-online counter. */
	EXTERN(cpu_online_count)
	lock   decl cpu_online_count

#ifndef NDEBUG /* TODO: REMOVE ME (>> tsc.S: FIXME: This int3 got hit randomly one time) */
	cmpP   $(0x10000000), (OFFSET_SCPUSTATE_IRREGS + OFFSET_IRREGS_PFLAGS)(%Psp)
	jna    771f /* if (!(STATE.EFLAGS > 0x10000000)) goto 771f; */
	int3
771:
#endif
	EXTERN(thiscpu_idle_sstate)
	movP   %Psp, thiscpu_idle_sstate(%R_fcall0P)

	/* Flush all caches before actually commiting to beginning to dream */
	wbinvd /* TODO: Only available since 486. - Must be replaced with `nop' no 386 */
	EXTERN(thiscpu_state)
	movP   $(CPU_STATE_DREAMING), thiscpu_state(%R_fcall0P)

	/* We're  now dreaming, meaning that our core  may get reset at any moment,
	 * and there is nothing we can do to undo this ourselves, or prevent such a
	 * reset from happening.
	 * However, in the interest of ensuring that everyone got the memo, invalidate
	 * caches  one more time (although this time  it should only be caches related
	 * to us setting `thiscpu_state' to `CPU_STATE_DREAMING') */

	wbinvd /* TODO: Only available since 486. - Must be replaced with `nop' no 386 */

	/* Disable our LAPIC
	 * s.a.: Intel manual Volume #3: 10.4.7.2      Local APIC State After It Has Been Software Disabled
	 * "The local APIC will respond normally to INIT, NMI, SMI, and SIPI messages"
	 * -> In other words,  it will  still be  able to  respond to  the INIT  IPI
	 *    send by other  cores, however  we can  conserve power  by turning  off
	 *    a  majority of  its other functions.  -> After all:  we're routing all
	 *    hardware interrupts to CPU#0, so if we can still handle INIT normally,
	 *    there's no reason to stay alive in order to do all of the other stuff! */
	EXTERN(x86_lapicbase)
	movP   x86_lapicbase, %Pax
	movl   $(0), APIC_SPURIOUS(%Pax)


	/* This is the master `hlt' instruction that is executed by a CPU when it is
	 * currently OFFLINE. - A CPU with an execution EIP set here isn't  actually
	 * running.
	 * Also note that the BOOT CPU must never be allowed to get here!
	 * Reminder: A  CPU is able to get out of this by another CPU sending an INIT IPI,
	 *           at which point the SMP  bootstrap code (s.a. `x86_smp_entry32')  gets
	 *           executed again, at the end of which the CPU context we've saved above
	 *           will get loaded once again. */
1:	hlt


.Lx86_smp_kill:
	/* we really shouldn't get here, but just in case we somehow do, manually
	 * disable interrupts  once again,  and jump  back to  continue  halting. */
	cli
	jmp    1b
	.cfi_endproc
END(cpu_enter_deepsleep)

#endif /* !CONFIG_NO_SMP */

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_SCHED_SMP_S */
