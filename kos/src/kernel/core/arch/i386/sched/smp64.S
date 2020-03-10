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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_SCHED_SMP64_S
#define GUARD_KERNEL_CORE_ARCH_I386_SCHED_SMP64_S 1
#define _KOS_KERNEL_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/apic.h>
#include <kernel/breakpoint.h>
#include <kernel/cpuid.h>
#include <kernel/gdt.h>
#include <kernel/paging.h>
#include <kernel/pic.h>
#include <sched/cpu.h>
#include <sched/smp.h>
#include <sched/task.h>
#include <sched/tss.h>

#include <asm/cfi.h>
#include <asm/cpu-cpuid.h>
#include <asm/cpu-flags.h>
#include <asm/cpu-msr.h>
#include <asm/instr/interrupt.h>
#include <asm/instr/movzxq.h>
#include <kos/kernel/cpu-state-asm.h>
#include <kos/kernel/cpu-state.h>


#ifndef CONFIG_NO_SMP

/* Push `IA32_KERNEL_GS_BASE' onto the stack
 * This macro clobbers %rax, %rcx and %rdx */
.macro pushq_cfi_kernel_gs_base
	subq   $(8), %rsp
	.cfi_adjust_cfa_offset 8
	movl   $(IA32_KERNEL_GS_BASE), %ecx
	rdmsr
	movl   %eax, 0(%rsp)
	movl   %edx, 4(%rsp)
.endm


/* Pop `IA32_KERNEL_GS_BASE' from the stack
 * This macro clobbers %rax, %rcx and %rdx */
.macro popq_cfi_kernel_gs_base
	movl   $(IA32_KERNEL_GS_BASE), %ecx
	movl   0(%rsp), %eax
	movl   4(%rsp), %edx
	wrmsr
	addq   $(8), %rsp
	.cfi_adjust_cfa_offset -8
.endm



.section .text
PUBLIC_FUNCTION(cpu_ipi_service_nopr)
	.cfi_startproc
	/* Simple wrapper around the IPI interrupt handler. */
	popq_cfi %rax
	.cfi_register %rip, %rax
	movq   %rsp, %rcx
	pushq_cfi $(SEGMENT_KERNEL_DATA0) /* %ss */
	.cfi_rel_offset %ss, 0
	pushq_cfi %rcx
	pushfq_cfi_r
	pushq_cfi $(SEGMENT_KERNEL_CODE)  /* %cs */
	.cfi_rel_offset %cs, 0
	pushq_cfi %rax
/*	.cfi_rel_offset %rip, 0 */
	.cfi_endproc
INTERN_FUNCTION(x86_idt_apic_ipi)
	.cfi_startproc
	.cfi_iret_signal_frame
	.cfi_def_cfa %rsp, 0
	intr_enter INTR

	ASM_PUSH_ICPUSTATE_AFTER_IRET_CFI_R

	/* Achnowledge the IPI beforehand, thus allowing another
	 * to be delivered while we're still handling the old one.
	 * The new one will not start executing until the iret below
	 * re-enabled interrupts (if it does so), but our LAPIC will
	 * have already been able to acknowledge the IPI, preventing
	 * the LAPIC of another CPU to be starved by never unsetting
	 * the `APIC_ICR0_FPENDING' bit. */
	EXTERN(x86_lapicbase)
	movq   x86_lapicbase, %rax
	movl   $(APIC_EOI_FSIGNAL), APIC_EOI(%rax)

	/* Reset the used action mode. */
	xorq   %rbp, %rbp

1:	/* Serve pending IPIs */
	movq   %rsp, %rdi
	call   x86_serve_ipi
	cmpq   %rax, %rsp
	je     2f
	/* Check for special IPI commands. */
	cmpq   $(CPU_IPI_MODE_SPECIAL_MIN), %rax
	jnae   3f

	/* Remember the greatest action that should be performed. */
	negq   %rax
	cmpq   %rbp, %rax
	jbe    1b         /* if (new_action <= action) goto 1b; */
	movq   %rax, %rbp /* action = new_action; */
	jmp    1b

	/* Load the new stack and continue serving IPIs */
3:	movq   %rax, %rsp
	jmp    1b

	/* Load all tasks that are pending execution by this CPU.
	 * This must be done _after_ IPIs are served, as the presence
	 * of pending IPIs also prevents more IPIs from being delivered.
	 * XXX: Add some way to have high-priority tasks be switched
	 *      to immediately, rather than having the previous task
	 *      complete its quantum. */
2:	EXTERN(cpu_loadpending_nopr)
	call   cpu_loadpending_nopr

	/* Check for more pending IPIs by looking at the first word
	 * of the IPI in-use bitset. - The same check is also done by
	 * code used to trigger this interrupt from other cores, with
	 * the expectation that the presence of any IPIs allows for the
	 * assumption that no interrupt has to be fired on the target
	 * core, in which case it is expected that we handle that IPI. */
	EXTERN(this_cpu)
	movq   %gs:this_cpu, %rax
	EXTERN(thiscpu_x86_ipi_inuse)
	cmpq   $(0), thiscpu_x86_ipi_inuse(%rax)
	jne    1b

	/* Resume execution, as requested */
	PRIVATE(ipi_action_table)
	jmpq   *ipi_action_table(,%rbp,8)

.Lipi_resume:
	.cfi_remember_state
	ASM_POP_ICPUSTATE_BEFORE_IRET_CFI_R

	intr_exit
	.cfi_restore_state
.Lipi_switch_tasks:
	/* Complete the full scpustate structure. */
	ASM_PUSH_SGBASE_CFI_R
	ASM_PUSH_SGREGS_CFI_R(%rax)

	EXTERN(this_cpu)
	movq   %gs:this_cpu, %rbx
	EXTERN(this_sched_state)
	movq   %rsp, this_sched_state(%rsi)

	/* Prematurely end the current quantum */
	EXTERN(cpu_quantum_end_nopr)
	call   cpu_quantum_end_nopr

	/* Load the new CPU state */
	EXTERN(thiscpu_current)
	movq   thiscpu_current(%rbx), %rax
	EXTERN(x86_load_thread_rax_cpu_rbx)
	jmp    x86_load_thread_rax_cpu_rbx
	.cfi_endproc
END(x86_idt_apic_ipi)
END(cpu_ipi_service_nopr)

.section .rodata
PRIVATE_OBJECT(ipi_action_table)
	.quad  .Lipi_resume       /* 0 (default action) */
	.quad  .Lipi_switch_tasks /* CPU_IPI_MODE_SWITCH_TASKS */
END(ipi_action_table)


.section .text
INTERN_FUNCTION(x86_execute_direct_ipi_nopr)
	/* RDI: <cpu_ipi_t func> */
	/* RSI: <cpu_ipi_t args> */
	.cfi_startproc
	.cfi_signal_frame
	popq_cfi %rax
	.cfi_register %rip, %rax
	movq   %rsp, %rcx
	pushq_cfi $(SEGMENT_KERNEL_DATA0) /* %ss */
	.cfi_rel_offset %ss, 0
	pushq_cfi %rcx
	pushfq_cfi_r
	pushq_cfi $(SEGMENT_KERNEL_CODE)  /* %cs */
	.cfi_rel_offset %cs, 0
	pushq_cfi %rax
	.cfi_def_cfa %rsp, 0
	ASM_PUSH_ICPUSTATE_AFTER_IRET_CFI_R

	/* Invoke the IPI function */
	movq   %rdi, %rax
	movq   %rsp, %rdi
	callq  *%rax

	/* Check for special IPI commands, but ignore them. */
	cmpq   $(CPU_IPI_MODE_SPECIAL_MIN), %rax
	jae    .Lipi_resume
	movq   %rax, %rsp
	jmp    .Lipi_resume
	.cfi_endproc
END(x86_execute_direct_ipi_nopr)


.section .text
INTERN_FUNCTION(x86_execute_direct_ipi)
	/* RDI: <cpu_ipi_t func> */
	/* RSI: <cpu_ipi_t args> */
	.cfi_startproc
	.cfi_signal_frame
	popq_cfi %rax
	.cfi_register %rip, %rax
	movq   %rsp, %rcx
	pushq_cfi $(SEGMENT_KERNEL_DATA0) /* %ss */
	.cfi_rel_offset %ss, 0
	pushq_cfi %rcx
	pushfq_cfi_r
	pushq_cfi $(SEGMENT_KERNEL_CODE)  /* %cs */
	.cfi_rel_offset %cs, 0
	pushq_cfi %rax
	.cfi_def_cfa %rsp, 0
	ASM_PUSH_ICPUSTATE_AFTER_IRET_CFI_R

	/* Reset the used action mode. */
	xorq   %rbp, %rbp

	/* Invoke the IPI function */
	movq   %rdi, %rax
	movq   %rsp, %rdi
	callq  *%rax

	cmpq   %rsp, %rax
	je     1f
	/* Check for special IPI commands. */
	cmpq   $(CPU_IPI_MODE_SPECIAL_MIN), %rax
	jnae   .Lipi_resume
	negq   %rax
	jmpq   *ipi_action_table(,%rax,8)
	/* Load the new stack and continue serving IPIs */
1:	movq   %rax, %rsp
	jmp    .Lipi_resume
	.cfi_endproc
END(x86_execute_direct_ipi)



#define SYM(x) ((x) - KERNEL_CORE_BASE)


/* 16-bit (real-mode) bootstrap code executed by secondary cores.
 * All this code does is load a GDT and use it to jump
 * into 32-bit mode at `x86_smp_entry32' */
.section .text.free
.code16
INTERN_FUNCTION(x86_smp_entry)
	/* Entry address for secondary APs */
	cli
	/* Load the GDT below. */
	/* movw $(*x86_smp_entry_gdt_segment), %sp */
	.byte  0xbc
INTERN_LABEL(x86_smp_entry_gdt_segment):
	.word  0x1234
	movw   %sp, %ds
/*	lgdtl  %ds:(*x86_smp_entry_gdt_offset) */
	.byte  0x0f, 0x01, 0x16
INTERN_LABEL(x86_smp_entry_gdt_offset):
	.word  0x5678
	movl   %cr0, %esp
	orw    $(CR0_PE), %sp
	movl   %esp, %cr0
	/* Jump to protected mode. */
	ljmpl  $(0x08), $(SYM(x86_smp_entry32))
INTERN_OBJECT(x86_smp_gdt)
	.word  (3 * SIZEOF_SEGMENT_DESCRIPTOR) - 1
INTERN_LABEL(x86_smp_gdt_pointer_base):
	.int   1f - x86_smp_entry
#define DEFINE_SEGMENT_DESCRIPTOR(TYPE, args) \
	.int   SEGMENT_##TYPE##_INIT_UL args;     \
	.int   SEGMENT_##TYPE##_INIT_UH args;
1:	DEFINE_SEGMENT_DESCRIPTOR(DESCRIPTOR, (0, 0, 0, 0, 0, 0, 0, 0, 0, 0))
	DEFINE_SEGMENT_DESCRIPTOR(DESCRIPTOR, (0, 0xfffff, SEGMENT_DESCRIPTOR_TYPE_CODE_EXRD, 1, 0, 1, 0, 0, 1, 1))
	DEFINE_SEGMENT_DESCRIPTOR(DESCRIPTOR, (0, 0xfffff, SEGMENT_DESCRIPTOR_TYPE_DATA_RDWR, 1, 0, 1, 0, 0, 1, 1))
#undef DEFINE_SEGMENT_DESCRIPTOR
END(x86_smp_gdt)

INTERN_CONST(x86_smp_entry_size, . - x86_smp_entry)
END(x86_smp_entry)


	/* 32-bit entry point */
.section .pdata


.code32
PRIVATE_OBJECT(x86_smp_entry32_ministack)
	.skip 8 /* We only need 8 bytes of stack memory! */
END(x86_smp_entry32_ministack)
PRIVATE_OBJECT(x86_smp_entry32_ministack_lock)
	.byte 0 /* Non-zero if locked */
END(x86_smp_entry32_ministack_lock)

INTERN_FUNCTION(x86_smp_entry32_spin)
	pause
INTERN_FUNCTION(x86_smp_entry32)
	movw   $(0x10), %sp /* x86_smp_gdt_pointer_base[2] */
	movw   %sp, %ds
/*	movw   %sp, %es */ /* Not needed */
	movw   %sp, %ss

	/* Check if CPUID is supported.
	 * NOTE: For this, we need 8 bytes of stack memory... */
	movb   $(1), %al
	lock;  xchgb %al, SYM(x86_smp_entry32_ministack_lock)
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
	testl  $(CPUID_80000001D_LM), %edx
	jz     x86_smp_boot_failure_no_longmode

	/* Test the PAE bit. */
//	testl  $(CPUID_80000001D_PAE), %edx
//	jz     x86_smp_boot_failure_no_pae

	/* Test the PSE bit. */
//	testl  $(CPUID_80000001D_PSE), %edx
//	jz     x86_smp_boot_failure_no_pse

	movl   $(1), %eax
	cpuid

	/* Test the MSR bit. */
	testl  $(CPUID_1D_MSR), %edx
	jz     x86_smp_boot_failure_no_msr

	/* Prepare to enable paging. */
	movl   $(pagedir_kernel_phys), %esp
	movl   %esp, %cr3

	/* Configure the %CR4 register. */
	movl   %cr4, %esp
	/* Enable PageSizeExtension (required for 2Mib pages & long-mode),
	 * as well as PhysicalAddressExtension (required for the 48-bit
	 * physical address space needed in long-mode) */
	orl    $(CR4_PSE | CR4_PAE), %esp
	movl   $(1), %eax
	cpuid
	testl  $(CPUID_1D_PGE), %edx /* Enable PGE if supported by the host (optional feature) */
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
	testl  $(CPUID_7B_SMEP), %ebx /* Enable SMAP if supported by the host (optional feature) */
	jz     1f
	orl    $(CR4_SMEP), %esp
1:	testl  $(CPUID_7B_FSGSBASE), %ebx /* Enable FSGSBASE if supported by the host (emulated if unsupported) */
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
	 * such as the NXE bit, as well as SCE (SysCallExtensions) */
	movl   $(0x80000001), %eax
	cpuid
	testl  $(CPUID_80000001D_NX), %edx
	jz     1f
	orl    $(IA32_EFER_NXE), %esp
1:	testl  $(CPUID_80000001D_SYSCALL), %edx
	jz     1f
	orl    $(IA32_EFER_SCE), %esp
1:	/* Save the new configuration. */
	movl   $(IA32_EFER), %ecx
	movl   %esp, %eax
	movl   %ebp, %edx
	wrmsr

	/* Now to actually enable paging! */
	movl  %cr0, %eax
	orl   $(CR0_PG | CR0_WP), %eax
	movl  %eax, %cr0

	/* Load a GDT that can be used for entering long mode. */
	lgdtl  SYM(smp64_enterlong_gdt_pointer)

	/* Load 64-bit segment registers. */
	movw   $(0x10), %sp /* DATA */
	movw   %sp, %ds
/*	movw   %sp, %es * Not needed */
/*	movw   %sp, %fs * Not needed */
/*	movw   %sp, %gs * Not needed */
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
	.int   SEGMENT_##TYPE##_INIT_UL args;     \
	.int   SEGMENT_##TYPE##_INIT_UH args;
	DEFINE_SEGMENT_DESCRIPTOR(DESCRIPTOR, (0, 0, 0, 0, 0, 0, 0, 0, 0, 0))
	DEFINE_SEGMENT_DESCRIPTOR(DESCRIPTOR, (0, 0xfffff, SEGMENT_DESCRIPTOR_TYPE_CODE_EXRD, 1, 0, 1, 0, /*L*/ 1, 0, 1))
	DEFINE_SEGMENT_DESCRIPTOR(DESCRIPTOR, (0, 0xfffff, SEGMENT_DESCRIPTOR_TYPE_DATA_RDWR, 1, 0, 1, 0, /*L*/ 1, 0, 1))
#undef DEFINE_SEGMENT_DESCRIPTOR
.Lsmp64_enterlong_gdt_end = .
END(smp64_enterlong_gdt)
.align 2
PRIVATE_OBJECT(smp64_enterlong_gdt_pointer)
	.word  (.Lsmp64_enterlong_gdt_end - smp64_enterlong_gdt) - 1
	.int   SYM(smp64_enterlong_gdt)
END(smp64_enterlong_gdt_pointer)



#define R_CPU   %rbp
#define R_TASK  %rbx


.code64

/* Initialize the cpuid feature table of the calling CPU
 * IN:
 *     R_CPU: THIS_CPU
 * OUT:
 *     %rip:  set to `.Ldone_init_cpuid'
 * CLOBBER:
 *     %rax
 *     %rcx
 *     %rdx
 *     %rdi
 */
PRIVATE_FUNCTION(x86_smp_init_cpuid)
	movw   $(CPU_FEATURE_FDIDINIT), thiscpu_x86_cpufeatures(R_CPU)
	/* Clear out our CPUID features table. */
	leaq   thiscpu_x86_cpuid(R_CPU), %rdi
	xorq   %rax, %rax
#if (SIZEOF_CPUID_CPUINFO % 8) == 0
	movq   $(SIZEOF_CPUID_CPUINFO / 8), %rcx
	rep;   stosq
#elif (SIZEOF_CPUID_CPUINFO % 8) == 4
	movq   $(SIZEOF_CPUID_CPUINFO / 4), %rcx
	rep;   stosl
#else
	movl   $(SIZEOF_CPUID_CPUINFO), %rcx
	rep;   stosb
#endif

	/* The `cpuid' instruction is available. */
	orw    $(CPU_FEATURE_FCPUID), thiscpu_x86_cpufeatures(R_CPU)

	movq   %rbx, %rdi
	movl   $(1), %eax
	cpuid
	movl   %eax, thiscpu_x86_cpuid + OFFSET_CPUID_1A(R_CPU)
	movl   %ebx, thiscpu_x86_cpuid + OFFSET_CPUID_1B(R_CPU)
	movl   %edx, thiscpu_x86_cpuid + OFFSET_CPUID_1D(R_CPU)
	movl   %ecx, thiscpu_x86_cpuid + OFFSET_CPUID_1C(R_CPU)

	/* if (Family == 6 && Model < 3 && Stepping < 3)
	 *     OFFSET_CPUID_1D &= ~CPUID_1D_SEP; */
	testl  $(CPUID_1D_SEP), %edx
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
	andl   $(~CPUID_1D_SEP), thiscpu_x86_cpuid + OFFSET_CPUID_1D(R_CPU)
1:

	movl   $(0), %eax
	cpuid
	movl   %eax, thiscpu_x86_cpuid + OFFSET_CPUID_0A(R_CPU)
	movl   %ebx, thiscpu_x86_cpuid + OFFSET_CPUID_0B(R_CPU)
	movl   %edx, thiscpu_x86_cpuid + OFFSET_CPUID_0D(R_CPU)
	movl   %ecx, thiscpu_x86_cpuid + OFFSET_CPUID_0C(R_CPU)

	cmpl   $(7), %eax
	jnae   1f
	movl   $(7), %eax
	movl   $(0), %ecx /* Sub-leaf:0 */
	cpuid
	movl   %edx, thiscpu_x86_cpuid + OFFSET_CPUID_7D(R_CPU)
	movl   %ecx, thiscpu_x86_cpuid + OFFSET_CPUID_7C(R_CPU)
	movl   %ebx, thiscpu_x86_cpuid + OFFSET_CPUID_7B(R_CPU)
1:	movl   $(0x80000000), %eax
	cpuid
	movl   %eax, thiscpu_x86_cpuid + OFFSET_CPUID_80000000A(R_CPU)
	cmpl   $(0x80000001), %eax
	jnae   2f
	movl   $(0x80000001), %eax
	cpuid
	movl   %ecx, thiscpu_x86_cpuid + OFFSET_CPUID_80000001C(R_CPU)
	movl   %edx, thiscpu_x86_cpuid + OFFSET_CPUID_80000001D(R_CPU)
	movl   thiscpu_x86_cpuid + OFFSET_CPUID_80000000A(R_CPU), %eax
	cmpl   $(0x80000004), %eax
	jnae   3f
	movl   $(0x80000004), %eax
	cpuid
	movl   %eax, thiscpu_x86_cpuid + OFFSET_CPUID_80000004A(R_CPU)
	movl   %ebx, thiscpu_x86_cpuid + OFFSET_CPUID_80000004B(R_CPU)
	movl   %ecx, thiscpu_x86_cpuid + OFFSET_CPUID_80000004C(R_CPU)
	movl   %edx, thiscpu_x86_cpuid + OFFSET_CPUID_80000004D(R_CPU)
	movl   $(0x80000003), %eax
	cpuid
	movl   %eax, thiscpu_x86_cpuid + OFFSET_CPUID_80000003A(R_CPU)
	movl   %ebx, thiscpu_x86_cpuid + OFFSET_CPUID_80000003B(R_CPU)
	movl   %ecx, thiscpu_x86_cpuid + OFFSET_CPUID_80000003C(R_CPU)
	movl   %edx, thiscpu_x86_cpuid + OFFSET_CPUID_80000003D(R_CPU)
	movl   $(0x80000002), %eax
	cpuid
	movl   %eax, thiscpu_x86_cpuid + OFFSET_CPUID_80000002A(R_CPU)
	movl   %ebx, thiscpu_x86_cpuid + OFFSET_CPUID_80000002B(R_CPU)
	movl   %ecx, thiscpu_x86_cpuid + OFFSET_CPUID_80000002C(R_CPU)
	movl   %edx, thiscpu_x86_cpuid + OFFSET_CPUID_80000002D(R_CPU)
3:  /* ci_80000000a < 0x80000004 */
2:  /* ci_80000000a < 0x80000001 */
	movq   %rdi, %rbx
	jmp    .Ldone_init_cpuid
END(x86_smp_init_cpuid)



	/* 64-bit entry point */
INTERN_FUNCTION(x86_smp_entry64)

	/* Figure out who we actually are by looking at our LAPIC id. */
	EXTERN(x86_lapicbase)
	movq   x86_lapicbase, %rsp
	movl   APIC_ID(%rsp), %esp
	shrl   $(APIC_ID_FSHIFT), %esp

	/* Find the CPU how's APIC_ID matches `%sp' (and that'll be us then) */
	EXTERN(cpu_count)
	movq   cpu_count, %rcx
	decq   %rcx
	EXTERN(cpu_vector)
1:	movq   cpu_vector(,%rcx,8), R_CPU
	EXTERN(thiscpu_x86_lapicid)
	movzbw thiscpu_x86_lapicid(R_CPU), %dx
	cmpw   %dx, %sp
	je     1f
	loop   1b
	jmp    .Lx86_smp_kill
1:
	/* Change CPU state to indicate that we're going to initialize! */
	EXTERN(thiscpu_state)
	movq   $(CPU_STATE_RUNNING), thiscpu_state(R_CPU)
	EXTERN(cpu_online_count)
	lock;  incq cpu_online_count

	/* Found our CPU (now stored in R_CPU) */
	EXTERN(thiscpu_current)
	movq   thiscpu_current(R_CPU),  R_TASK /* TARGET task. */
	EXTERN(this_sched_state)
	movq   this_sched_state(R_TASK), %rsp   /* stack */

	/* Load the GDT of our new CPU */
	EXTERN(thiscpu_x86_gdt)
	leaq   thiscpu_x86_gdt(R_CPU), %rcx
	pushq  %rcx
	pushw  $((SEGMENT_COUNT * SIZEOF_SEGMENT_DESCRIPTOR) - 1)
	lgdtq  (%rsp)
	addq   $(10), %rsp

	/* Load basic segments. */
	movw   $(SEGMENT_USER_DATA64_RPL), %cx
	movw   %cx, %ds
	movw   %cx, %es
	movw   %cx, %fs
	movw   %cx, %gs

	/* Load the Task register. */
	/* SEGMENTS[SEGMENT_CPU_TSS].busy = 0;  // Required for `ltr' */
	EXTERN(thiscpu_x86_gdt)
	andb   $(0b11111101), (thiscpu_x86_gdt + SEGMENT_CPU_TSS + 5)(R_CPU)
	movw   $(SEGMENT_CPU_TSS), %cx
	ltrw   %cx

	/* Load the local descriptor table. */
	movw   $(SEGMENT_CPU_LDT), %cx
	lldtw  %cx

	/* NOTE: This also does the jump from physical into virtual memory! */
	movq   %rsp, %rax
	pushq  $(SEGMENT_KERNEL_DATA0) /* %ss */
	pushq  %rax                    /* %rsp */
	pushfq                         /* %rflags */
	pushq  $(SEGMENT_KERNEL_CODE)  /* %cs */
	pushq  $(1f)                   /* %rip */
	iretq  /* Jump to our per-cpu 64-bit code segment. */
1:

	/* Load the interrupt descriptor table. */
	EXTERN(x86_idt_ptr)
	lidtq  x86_idt_ptr

	/* ============== Configure cpuid features ============== */
	/* R_CPU:  THIS_CPU
	 * R_TASK: THIS_TASK */

	/* Check if we've already filled in our CPUID features table. */
	EXTERN(thiscpu_x86_cpufeatures)
	testw  $(CPU_FEATURE_FDIDINIT), thiscpu_x86_cpufeatures(R_CPU)
	jz     x86_smp_init_cpuid
.Ldone_init_cpuid:


	/* If supported, initialize the `sysenter' instruction */
	testl  $(CPUID_1D_SEP), OFFSET_CPUID_1D(R_CPU)
	jz     .Ldone_sysenter

	/* __wrmsr(IA32_SYSENTER_CS, SEGMENT_KERNEL_CODE); */
	xorq   %rdx, %rdx
	movl   $(SEGMENT_KERNEL_CODE), %eax
	movl   $(IA32_SYSENTER_CS), %ecx
	wrmsr

	/* __wrmsr(IA32_SYSENTER_ESP, (uintptr_t)&PERCPU(thiscpu_x86_tss).t_esp0); */
	leaq   (thiscpu_x86_tss + OFFSET_TSS_RSP0)(R_CPU), %rax
	movq   %rax, %rdx
	shrq   $(32), %rdx
	movzlq %eax, %rax
	movl   $(IA32_SYSENTER_ESP), %ecx
	wrmsr

	/* __wrmsr(IA32_SYSENTER_EIP, (uintptr_t)&x86_syscall32_sysenter[_traced]); */
	EXTERN(x86_syscall32_sysenter)
	movq   $(x86_syscall32_sysenter), %rax
#ifndef CONFIG_NO_SYSCALL_TRACING
	EXTERN(syscall_tracing_enabled)
	cmpb   $(0), syscall_tracing_enabled
	je     1f
	EXTERN(x86_syscall32_sysenter_traced)
	movq   $(x86_syscall32_sysenter_traced), %rax
1:
#endif /* !CONFIG_NO_SYSCALL_TRACING */
	movq   %rax, %rdx
	shrq   $(32), %rdx
	movzlq %eax, %rax
	movl   $(IA32_SYSENTER_EIP), %ecx
	wrmsr
.Ldone_sysenter:


	/* If supported, initialize the `syscall' instruction */
	testl  $(CPUID_80000001D_SYSCALL), OFFSET_CPUID_80000001D(R_CPU)
	jz     .Ldone_syscall

	/* __wrmsr(IA32_STAR, (u64)SEGMENT_KERNEL_CODE << 32); */
	movl   $(SEGMENT_KERNEL_CODE), %edx
	xorq   %rax, %rax
	movl   $(IA32_STAR), %ecx
	wrmsr

	/* __wrmsr(IA32_FMASK, EFLAGS_IF); */
	xorq   %rdx, %rdx
	movl   $(EFLAGS_IF), %eax
	movl   $(IA32_FMASK), %ecx
	wrmsr

	/* __wrmsr(IA32_LSTAR, (u64)&x86_syscall64_syscall[_traced]); */
	EXTERN(x86_syscall64_syscall)
	movq   $(x86_syscall64_syscall), %rax
#ifndef CONFIG_NO_SYSCALL_TRACING
	EXTERN(syscall_tracing_enabled)
	cmpb   $(0), syscall_tracing_enabled
	je     1f
	EXTERN(x86_syscall64_syscall_traced)
	movq   $(x86_syscall64_syscall_traced), %rax
1:
#endif /* !CONFIG_NO_SYSCALL_TRACING */
	movq   %rax, %rdx
	shrq   $(32), %rdx
	movzlq %eax, %rax
	movl   $(IA32_LSTAR), %ecx
	wrmsr
.Ldone_syscall:

	/* Load the VM of the target task. */
	movq   this_vm(R_TASK), %rcx
	EXTERN(vm_kernel)
	cmpq   $(vm_kernel), %rcx
	je     1f
	EXTERN(thisvm_pdir_phys_ptr)
	movq   thisvm_pdir_phys_ptr(%rcx), %rcx
	movq   %rcx, %cr3
1:
	/* Set up tracing to appear as though we're nothing but an interrupt originating
	 * from whereever we're supposed to start executing the provided thread. */
	.cfi_startproc simple
	.cfi_signal_frame
	.cfi_def_cfa %rsp, OFFSET_SCPUSTATE_IRREGS
	ASM_CFI_REL_OFFSET_RESTORE_SGBASE(OFFSET_SCPUSTATE_SGBASE)
	ASM_CFI_REL_OFFSET_RESTORE_SGREGS(OFFSET_SCPUSTATE_SGREGS)
	ASM_CFI_REL_OFFSET_RESTORE_GPREGSNSP(OFFSET_SCPUSTATE_GPREGSNSP)
	ASM_CFI_REL_OFFSET_RESTORE_IRREGS(OFFSET_SCPUSTATE_IRREGS)

	/* Reload debug registers */
	reload_x86_debug_registers %rcx, %rax, %rdx, 0

	/* R_CPU:   THIS_CPU
	 * R_TASK:  THIS_TASK */

	/* Check for, and load all threads that are pending execution by our CPU. */
	movq   $(CPU_PENDING_ENDOFCHAIN), %rdx
	EXTERN(thiscpu_pending)
	lock;  xchgq %rdx, thiscpu_pending(R_CPU)
	cmpq   $(CPU_PENDING_ENDOFCHAIN), %rdx
	jz     1f
	movq   R_CPU, %rcx
	EXTERN(cpu_loadpending_chain_nopr)
	call   cpu_loadpending_chain_nopr
1:

	/* Enable preemptive interrupts. */
	movq   R_CPU, %rdi
	EXTERN(x86_altcore_initapic)
	call   x86_altcore_initapic

//	EXTERN(this_sched_state)
//	movq   this_sched_state(R_TASK), %rsp

	/* Load other scheduler-related register values. */
	EXTERN(this_x86_kernel_psp0)
	movq   this_x86_kernel_psp0(R_TASK), %rcx
	EXTERN(thiscpu_x86_tss)
	movq   %rcx, thiscpu_x86_tss + OFFSET_TSS_RSP0(R_CPU)

#ifndef CONFIG_NO_FPU
	/* Disable the FPU, preparing it to be loaded lazily. */
	movq   %cr0, %rcx
	orq    $(CR0_TS), %rcx
	movq   %rcx, %cr0
	/* Also: Indicate that no task is currently holding an FPU context.
	 * NOTE: Technically, we could also move this part into `cpu_enter_deepsleep()',
	 *       however it's safer to unconditionally do this during initialization! */
	EXTERN(thiscpu_x86_fputhread)
	movl   $(0), thiscpu_x86_fputhread(R_CPU)
#endif /* !CONFIG_NO_FPU */

	/* (Partially) load the underlying CPU state */
	ASM_POP_SGREGS_CFI_R(%rax)
	ASM_POP_SGBASE_CFI_R
	wrgsbaseq R_TASK

	/* Service pending IPIs for the first time.
	 * -> Since we got here thanks to an INIT IPI, regular IPI callbacks
	 *    would not have generated their IPI interrupt, meaning we have
	 *    to manually check for callbacks this one time.
	 * NOTE: Since `x86_serve_ipi()' expects an `icpustate' structure,
	 *       we were forced to partially unwind the CPU state. */
	movq   %rsp, %rdi
	EXTERN(x86_serve_ipi)
	call   x86_serve_ipi
	movq   %rax, %rsp

	ASM_POP_ICPUSTATE_BEFORE_IRET_CFI_R
	intr_exit
	.cfi_endproc
END(x86_smp_entry64)



.section .text.cold
/* FUNDEF void NOTHROW(FCALL cpu_enter_deepsleep)(struct cpu *__restrict caller); */
PUBLIC_FUNCTION(cpu_enter_deepsleep)
	.cfi_startproc
	/* Construct an IRET tail which will later be used to return to the caller. */
	popq_cfi %rax
	.cfi_register %rip, %rax
	movq   %rsp, %rcx
	pushq_cfi $(SEGMENT_KERNEL_DATA0) /* ir_ss */
	.cfi_rel_offset %ss, 0
	pushq_cfi %rcx                    /* ir_rsp */
	.cfi_rel_offset %rsp, 0
	pushfq_cfi_r                      /* ir_rflags */
	orq    $(EFLAGS_IF), (%rsp)
	pushq_cfi $(SEGMENT_KERNEL_CODE)  /* ir_cs */
	.cfi_rel_offset %cs, 0
	pushq_cfi %rax                    /* ir_rip */
	.cfi_rel_offset %rip, 0
	.cfi_endproc

	/* With an IRET tail constructed, switch to using a signal-frame CFI descriptor */
	.cfi_startproc simple
	.cfi_iret_signal_frame
	.cfi_def_cfa %rsp, 0

	ASM_PUSH_GPREGSNSP_CFI_R         /* gpregs */
	ASM_PUSH_SGBASE_CFI_R
	ASM_PUSH_SGREGS_CFI_R(%rax)

#ifndef CONFIG_NO_FPU
	/* With the CPU about to go OFFLINE, make sure to also save the current
	 * FPU state (if the FPU was used), so-as to not lose that information
	 * and have it still be available when we come back online. */
	EXTERN(thiscpu_x86_fputhread)
	movq   thiscpu_x86_fputhread(%rdi), %rax
	testq  %rax, %rax
	jz     1f
	clts   /* Make sure FPU access is allowed. */
	/* Save the current FPU context into `this_x86_fpustate(%rax)' */
	movq   %rdi, %rbx /* Preserve THIS_CPU */
	EXTERN(this_x86_fpustate)
	movq   this_x86_fpustate(%rax), %rdi
	EXTERN(x86_fpustate_save)
	call   x86_fpustate_save
	movq   %rbx, %rdi /* Restore THIS_CPU */
1:
#endif /* !CONFIG_NO_FPU */

	/* Decrement the cpu-online counter. */
	EXTERN(cpu_online_count)
	lock;  decq cpu_online_count

	EXTERN(thiscpu_idle_sched_state)
	movq   %rsp, thiscpu_idle_sched_state(%rdi)

	/* Flush all caches before actually commiting to beginning to dream */
	wbinvd
	EXTERN(thiscpu_state)
	movq   $(CPU_STATE_DREAMING), thiscpu_state(%rdi)

	/* We're now dreaming, meaning that our core may get reset at any moment,
	 * and there is nothing we can do to undo this ourself, or prevent such a
	 * reset from happening.
	 * However, in the interest of ensuring that everyone got the memo, invalidate
	 * caches one more time (although this time it should only be caches related
	 * to us setting `thiscpu_state' to `CPU_STATE_DREAMING') */

	wbinvd

	/* Disable our LAPIC
	 * s.a.: Intel manual Volume #3: 10.4.7.2      Local APIC State After It Has Been Software Disabled
	 * "The local APIC will respond normally to INIT, NMI, SMI, and SIPI messages"
	 * -> In other words, it will still be able to respond to
	 *    the INIT IPI send by other cores, however we can
	 *    conserve power by turning off a majority of its
	 *    other functions. -> After all: we're routing all
	 *    hardware interrupts to CPU#0, so if we can still
	 *    handle INIT normally, there's no reason to stay
	 *    alive in order to do all of the other stuff! */
	EXTERN(x86_lapicbase)
	movq   x86_lapicbase, %rax
	movl   $(0), APIC_SPURIOUS(%rax)


	/* This is the master `hlt' instruction that is executed by a CPU when it is
	 * currently OFFLINE. - A CPU with an execution EIP set here isn't actually
	 * running.
	 * Also note that the BOOT CPU must never be allowed to get here!
	 * Reminder: A CPU is able to get out of this by another CPU sending an INIT IPI,
	 *           at which point the SMP bootstrap code (s.a. `x86_smp_entry32') gets
	 *           executed again, at the end of which the CPU context we've saved above
	 *           will get loaded once again. */
1:	hlt


.Lx86_smp_kill:
	/* we really shouldn't get here, but just in case we somehow do, manually
	 * disable interrupts once again, and jump back to continue halting. */
	cli
	jmp    1b
	.cfi_endproc
END(cpu_enter_deepsleep)


#endif /* !CONFIG_NO_SMP */

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_SCHED_SMP64_S */
