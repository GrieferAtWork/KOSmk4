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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_SCHED_SMP32_S
#define GUARD_KERNEL_CORE_ARCH_I386_SCHED_SMP32_S 1
#define _KOS_KERNEL_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/apic.h>
#include <kernel/breakpoint.h>
#include <kernel/arch/cpuid.h>
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
#include <kos/kernel/cpu-state.h>


#ifndef CONFIG_NO_SMP

.section .text
PUBLIC_FUNCTION(cpu_ipi_service_nopr)
	.cfi_startproc
	/* Simple wrapper around the IPI interrupt handler. */
	popl_cfi %eax
	.cfi_register %eip, %eax
	pushfl_cfi_r
	pushl_cfi_r %cs
	pushl_cfi %eax
/*	.cfi_rel_offset %eip, 0 */
	.cfi_endproc
INTERN_FUNCTION(x86_idt_apic_ipi)
	.cfi_startproc
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0

	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12

	pushal_cfi_r

	/* Load kernel-space segments. */
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs

	/* Achnowledge the IPI beforehand, thus allowing another
	 * to be delivered while we're still handling the old one.
	 * The new one will not start executing until the iret below
	 * re-enabled interrupts (if it does so), but our LAPIC will
	 * have already been able to acknowledge the IPI, preventing
	 * the LAPIC of another CPU to be starved by never unsetting
	 * the `APIC_ICR0_FPENDING' bit. */
	EXTERN(x86_lapicbase)
	movl   x86_lapicbase, %eax
	movl   $(APIC_EOI_FSIGNAL), APIC_EOI(%eax)

	/* Reset the used action mode. */
	xorl   %ebp, %ebp

1:	/* Serve pending IPIs */
	movl   %esp, %ecx
	call   x86_serve_ipi
	cmpl   %eax, %esp
	je     2f
	/* Check for special IPI commands. */
	cmpl   $(CPU_IPI_MODE_SPECIAL_MIN), %eax
	jnae   3f

	/* Remember the greatest action that should be performed. */
	negl   %eax
	cmpl   %ebp, %eax
	jbe    1b         /* if (new_action <= action) goto 1b; */
	movl   %eax, %ebp /* action = new_action; */
	jmp    1b

	/* Load the new stack and continue serving IPIs */
3:	movl   %eax, %esp
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
	movl   %fs:this_cpu, %eax
	EXTERN(thiscpu_x86_ipi_inuse)
	cmpl   $(0), thiscpu_x86_ipi_inuse(%eax)
	jne    1b

	/* Resume execution, as requested */
	PRIVATE(ipi_action_table)
	jmpl   *ipi_action_table(,%ebp,4)

.Lipi_resume:
	.cfi_remember_state
	popal_cfi_r

	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds

	iret
	.cfi_restore_state
.Lipi_switch_tasks:
	/* Complete the full scpustate structure. */
	popal_cfi_r

	pushl_cfi %gs
	.cfi_restore_iret_gs_or_offset -16

	pushal_cfi_r

	movl   %fs:0, %esi
	EXTERN(this_cpu)
	movl   this_cpu(%esi), %ebx
	EXTERN(this_sched_state)
	movl   %esp, this_sched_state(%esi)

	/* Prematurely end the current quantum */
	EXTERN(cpu_quantum_end_nopr)
	call   cpu_quantum_end_nopr

	/* Load the new CPU state */
	EXTERN(thiscpu_current)
	movl   thiscpu_current(%ebx), %eax
	EXTERN(x86_load_thread_eax_cpu_ebx)
	jmp    x86_load_thread_eax_cpu_ebx
	.cfi_endproc
END(x86_idt_apic_ipi)
END(cpu_ipi_service_nopr)

.section .rodata
PRIVATE_OBJECT(ipi_action_table)
	.long  .Lipi_resume       /* 0 (default action) */
	.long  .Lipi_switch_tasks /* CPU_IPI_MODE_SWITCH_TASKS */
END(ipi_action_table)


.section .text
INTERN_FUNCTION(x86_execute_direct_ipi_nopr)
	/* ECX: <cpu_ipi_t func> */
	/* EDX: <cpu_ipi_t args> */
	.cfi_startproc
	popl_cfi %eax
	.cfi_register %eip, %eax
	pushfl_cfi_r  /* EFLAGS */
	pushl_cfi %cs
	pushl_cfi %eax
	pushl_cfi_r %ds
	pushl_cfi_r %es
	pushl_cfi_r %fs
	pushal_cfi_r

	/* Invoke the IPI function */
	movl   %ecx, %eax
	movl   %esp, %ecx
	calll  *%eax

	/* Check for special IPI commands, but ignore them. */
	cmpl   $(CPU_IPI_MODE_SPECIAL_MIN), %eax
	jae    .Lipi_resume
	movl   %eax, %esp
	jmp    .Lipi_resume
	.cfi_endproc
END(x86_execute_direct_ipi_nopr)


.section .text
INTERN_FUNCTION(x86_execute_direct_ipi)
	/* ECX: <cpu_ipi_t func> */
	/* EDX: <cpu_ipi_t args> */
	.cfi_startproc
	popl_cfi %eax
	.cfi_register %eip, %eax
	pushfl_cfi_r  /* EFLAGS */
	orl    $(EFLAGS_IF), 0(%esp)
	pushl_cfi %cs
	pushl_cfi %eax
	pushl_cfi_r %ds
	pushl_cfi_r %es
	pushl_cfi_r %fs
	pushal_cfi_r

	/* Reset the used action mode. */
	xorl   %ebp, %ebp

	/* Invoke the IPI function */
	movl   %ecx, %eax
	movl   %esp, %ecx
	calll  *%eax

	cmpl   %esp, %eax
	je     1f
	/* Check for special IPI commands. */
	cmpl   $(CPU_IPI_MODE_SPECIAL_MIN), %eax
	jnae   .Lipi_resume
	negl   %eax
	jmpl   *ipi_action_table(,%eax,4)
	/* Load the new stack and continue serving IPIs */
1:	movl   %eax, %esp
	jmp    .Lipi_resume
	.cfi_endproc
END(x86_execute_direct_ipi)




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
	ljmpl  $(8), $(x86_smp_entry32 - KERNEL_CORE_BASE)
INTERN_OBJECT(x86_smp_gdt)
	.word  (3 * SIZEOF_SEGMENT_DESCRIPTOR) - 1
INTERN_LABEL(x86_smp_gdt_pointer_base):
	.long  1f - x86_smp_entry
#define DEFINE_SEGMENT_DESCRIPTOR(TYPE, args) \
	.long  SEGMENT_##TYPE##_INIT_UL args; \
	.long  SEGMENT_##TYPE##_INIT_UH args;
1:	DEFINE_SEGMENT_DESCRIPTOR(DESCRIPTOR, (0, 0, 0, 0, 0, 0, 0, 0, 0, 0))
	DEFINE_SEGMENT_DESCRIPTOR(DESCRIPTOR, (0, 0xfffff, SEGMENT_DESCRIPTOR_TYPE_CODE_EXRD, 1, 0, 1, 0, 0, 1, 1))
	DEFINE_SEGMENT_DESCRIPTOR(DESCRIPTOR, (0, 0xfffff, SEGMENT_DESCRIPTOR_TYPE_DATA_RDWR, 1, 0, 1, 0, 0, 1, 1))
#undef DEFINE_SEGMENT_DESCRIPTOR
END(x86_smp_gdt)

INTERN_CONST(x86_smp_entry_size, . - x86_smp_entry)
END(x86_smp_entry)
.code32



#define R_CPU   %ebp
#define R_TASK  %edi


.section .pdata

/* Initialize the cpuid feature table of the calling CPU
 * IN:
 *     R_CPU: THIS_CPU
 * OUT:
 *     %rip:  set to `.Ldone_init_cpuid'
 * CLOBBER:
 *     %eax
 *     %ecx
 *     %edx
 *     %ebx
 */
PRIVATE_FUNCTION(x86_smp_init_cpuid)
	movw   $(CPU_FEATURE_FDIDINIT), thiscpu_x86_cpufeatures(R_CPU)
	/* Clear out our CPUID features table. */
	pushl  %edi
	leal   thiscpu_x86_cpuid(R_CPU), %edi
	xorl   %eax, %eax
#if (SIZEOF_CPUID_CPUINFO % 4) == 0
	movl   $(SIZEOF_CPUID_CPUINFO / 4), %ecx
	rep;   stosl
#else /* (SIZEOF_CPUID_CPUINFO % 4) == 0 */
	movl   $(SIZEOF_CPUID_CPUINFO), %ecx
	rep;   stosb
#endif /* (SIZEOF_CPUID_CPUINFO % 4) != 0 */
	popl   %edi

	/* Check if CPUID is supported. */
	pushfl
	pushfl
	xorl   $(EFLAGS_ID), 0(%esp)
	popfl
	pushfl
	popl   %eax
	xorl   0(%esp), %eax
	popfl
	andl   $(EFLAGS_ID), %eax
	jz     .Ldone_init_cpuid

	/* The `cpuid' instruction is available. */
	orw    $(CPU_FEATURE_FCPUID), thiscpu_x86_cpufeatures(R_CPU)

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
	jmp    .Ldone_init_cpuid
END(x86_smp_init_cpuid)


INTERN_FUNCTION(x86_smp_entry32)
	/* 32-bit entry point */
	movw   $(0x10), %sp /* x86_smp_gdt_pointer_base[2] */
	movw   %sp, %ds
	movw   %sp, %es
	movw   %sp, %ss

	/* Configure extended paging features.
	 * This has to be done before we can load `pagedir_kernel', as features such
	 * as PAE, or even just use of the GLOBAL bit would otherwise cause #PFs because
	 * the CPU would claim that reserved bits were set, or who-know-what in the case
	 * of the PAE page table really just being a completely different structure than
	 * the P32 page table.
	 * XXX: This assumes that all CPUs have the same feature-set as the boot cpu... */
	movl   %cr4, %esp
#ifndef CONFIG_NO_PAGING_PAE
	/* Enable PAE support (if necessary for setting the page directory) */
#ifndef CONFIG_NO_PAGING_P32
	EXTERN(x86_bootcpu_cpuid)
	testl  $(CPUID_1D_PAE), ((x86_bootcpu_cpuid - KERNEL_CORE_BASE) + OFFSET_CPUID_1D)
	jz     1f
#endif /* !CONFIG_NO_PAGING_P32 */
	orl    $(CR4_PAE), %esp
	/* Enable NX support (if necessary for setting the page directory) */
	EXTERN(x86_bootcpu_cpuid)
	testl  $(CPUID_80000001D_NX), ((x86_bootcpu_cpuid - KERNEL_CORE_BASE) + OFFSET_CPUID_80000001D)
	jz     1f
	movl   $(IA32_EFER), %ecx
	rdmsr
	orl    $(IA32_EFER_NXE), %eax
	wrmsr
	/* With PAE + NX, try to enable its effects while
	 * in kernel-space (if supported by the CPU) */
	testl  $(CPUID_7B_SMEP), (x86_bootcpu_cpuid + OFFSET_CPUID_7B)
	jz     1f
	orl    $(CR4_SMEP), %esp
1:
#endif /* !CONFIG_NO_PAGING_PAE */
	/* Enable PGE support (if necessary for setting the page directory) */
	testl  $(CPUID_1D_PGE), ((x86_bootcpu_cpuid - KERNEL_CORE_BASE) + OFFSET_CPUID_1D)
	jz     1f
	orl    $(CR4_PGE), %esp
1:	movl   %esp, %cr4


	/* Enable paging.
	 * NOTE: This is why this part must appear in the .pdata section.
	 *       Because we still are in physical memory, we must enable
	 *       paging in a context where the page directory we're enabling
	 *       has our current location mapped to ourself.
	 *       Later then, we'll jump into true virtual memory, but for
	 *       now, our actual PC is offset by `KERNEL_CORE_BASE' */
	movl   $(pagedir_kernel_phys), %esp
	movl   %esp, %cr3
	movl   %cr0, %esp
	orl    $(CR0_PG), %esp
	movl   %esp, %cr0

	/* Figure out who we actually are by looking at our LAPIC id. */
	EXTERN(x86_lapicbase)
	movl   x86_lapicbase, %esp
	movl   APIC_ID(%esp), %esp
	shrl   $(APIC_ID_FSHIFT), %esp

	/* Find the CPU how's APIC_ID matches `%sp' (and that'll be us then) */
	EXTERN(cpu_count)
	movl   cpu_count, %ecx
	decl   %ecx
	EXTERN(cpu_vector)
1:	movl   cpu_vector(,%ecx,4), R_CPU
	EXTERN(thiscpu_x86_lapicid)
	movzbw thiscpu_x86_lapicid(R_CPU), %dx
	cmpw   %dx, %sp
	je     1f
	loop   1b
	jmp    .Lx86_smp_kill
1:
	/* Change CPU state to indicate that we're going to initialize! */
	EXTERN(thiscpu_state)
	movl   $(CPU_STATE_RUNNING), thiscpu_state(R_CPU)
	EXTERN(cpu_online_count)
	lock;  incl cpu_online_count

	/* Found our CPU (now stored in R_CPU) */
	EXTERN(thiscpu_current)
	movl   thiscpu_current(R_CPU),  R_TASK /* TARGET task. */
	EXTERN(this_sched_state)
	movl   this_sched_state(R_TASK), %esp   /* stack */

	/* Load the GDT of our new CPU */
	EXTERN(thiscpu_x86_gdt)
	leal   thiscpu_x86_gdt(R_CPU), %ecx
	pushl  %ecx
	pushw  $((SEGMENT_COUNT * SIZEOF_SEGMENT_DESCRIPTOR) - 1)
	lgdt   (%esp)
	addl   $(6), %esp

	/* Load the Task register. */
	/* SEGMENTS[SEGMENT_CPU_TSS].busy = 0;  // Required for `ltr' */
	andb   $(0b11111101), thiscpu_x86_gdt + SEGMENT_CPU_TSS + 5(R_CPU)
	movw   $(SEGMENT_CPU_TSS), %cx
	ltrw   %cx

	/* Load the local descriptor table. */
	movw   $(SEGMENT_CPU_LDT), %cx
	lldtw  %cx

	/* Load basic segments. */
	movw   $(SEGMENT_USER_DATA), %cx
	movw   %cx, %ds
	movw   %cx, %es
	movw   $(SEGMENT_KERNEL_DATA), %cx
	movw   %cx, %ss
	/* NOTE: This also does the jump from physical into virtual memory! */
	ljmp   $(SEGMENT_KERNEL_CODE), $(1f)
1:

	/* Load the interrupt descriptor table. */
	EXTERN(x86_idt_ptr)
	lidtl  x86_idt_ptr

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
	xorl   %edx, %edx
	movl   $(SEGMENT_KERNEL_CODE), %eax
	movl   $(IA32_SYSENTER_CS), %ecx
	wrmsr

	/* __wrmsr(IA32_SYSENTER_ESP, (uintptr_t)&PERCPU(thiscpu_x86_tss).t_esp0); */
	xorl   %edx, %edx
	leal   (thiscpu_x86_tss + OFFSET_TSS_ESP0)(R_CPU), %eax
	movl   $(IA32_SYSENTER_ESP), %ecx
	wrmsr

	/* __wrmsr(IA32_SYSENTER_EIP, (uintptr_t)x86_syscall32_sysenter[_traced]); */
	xorl   %edx, %edx
	EXTERN(x86_syscall32_sysenter)
	movl   $(x86_syscall32_sysenter), %eax
#ifndef CONFIG_NO_SYSCALL_TRACING
	EXTERN(syscall_tracing_enabled)
	cmpb   $(0), syscall_tracing_enabled
	je     1f
	EXTERN(x86_syscall32_sysenter_traced)
	movl   $(x86_syscall32_sysenter_traced), %eax
1:
#endif /* !CONFIG_NO_SYSCALL_TRACING */
	movl   $(IA32_SYSENTER_EIP), %ecx
	wrmsr
.Ldone_sysenter:


	/* Load the VM of the target task. */
	movl   this_vm(R_TASK), %ecx
	EXTERN(vm_kernel)
	cmpl   $(vm_kernel), %ecx
	je     1f
	EXTERN(thisvm_pdir_phys_ptr)
	movl   thisvm_pdir_phys_ptr(%ecx), %ecx
	movl   %ecx, %cr3
1:
	/* Set up tracing to appear as though we're nothing but an interrupt originating
	 * from whereever we're supposed to start executing the provided thread. */
	.cfi_startproc simple
	.cfi_signal_frame
	.cfi_def_cfa %esp, OFFSET_SCPUSTATE_IRREGS
	.cfi_restore_iret_eip
	.cfi_restore_iret_cs
	.cfi_restore_iret_eflags
	.cfi_restore_iret_esp
	.cfi_restore_iret_ss
	.cfi_rel_offset %edi, OFFSET_SCPUSTATE_GPREGS + OFFSET_GPREGS_EDI
	.cfi_rel_offset %esi, OFFSET_SCPUSTATE_GPREGS + OFFSET_GPREGS_ESI
	.cfi_rel_offset %ebp, OFFSET_SCPUSTATE_GPREGS + OFFSET_GPREGS_EBP
	.cfi_rel_offset %esp, OFFSET_SCPUSTATE_GPREGS + OFFSET_GPREGS_ESP
	.cfi_rel_offset %ebx, OFFSET_SCPUSTATE_GPREGS + OFFSET_GPREGS_EBX
	.cfi_rel_offset %edx, OFFSET_SCPUSTATE_GPREGS + OFFSET_GPREGS_EDX
	.cfi_rel_offset %ecx, OFFSET_SCPUSTATE_GPREGS + OFFSET_GPREGS_ECX
	.cfi_rel_offset %eax, OFFSET_SCPUSTATE_GPREGS + OFFSET_GPREGS_EAX
	.cfi_restore_iret_gs_or_offset ((OFFSET_SCPUSTATE_SGREGS + OFFSET_SGREGS_GS) - OFFSET_SCPUSTATE_IRREGS)
	.cfi_restore_iret_fs_or_offset ((OFFSET_SCPUSTATE_SGREGS + OFFSET_SGREGS_FS) - OFFSET_SCPUSTATE_IRREGS)
	.cfi_restore_iret_es_or_offset ((OFFSET_SCPUSTATE_SGREGS + OFFSET_SGREGS_ES) - OFFSET_SCPUSTATE_IRREGS)
	.cfi_restore_iret_ds_or_offset ((OFFSET_SCPUSTATE_SGREGS + OFFSET_SGREGS_DS) - OFFSET_SCPUSTATE_IRREGS)

	/* Reload debug registers */
	reload_x86_debug_registers %ecx, %eax, %edx, 0

	/* R_CPU:   THIS_CPU
	 * R_TASK:  THIS_TASK */

	/* Check for, and load all threads that are pending execution by our CPU. */
	movl   $(CPU_PENDING_ENDOFCHAIN), %edx
	EXTERN(thiscpu_pending)
	lock;  xchgl %edx, thiscpu_pending(R_CPU)
	cmpl   $(CPU_PENDING_ENDOFCHAIN), %edx
	jz     1f
	movl   R_CPU, %ecx
	EXTERN(cpu_loadpending_chain_nopr)
	call   cpu_loadpending_chain_nopr
1:

	/* Enable preemptive interrupts. */
	movl   R_CPU, %ecx
	EXTERN(x86_altcore_initapic)
	call   x86_altcore_initapic

//	EXTERN(this_sched_state)
//	movl   this_sched_state(R_TASK), %esp

	/* Load other scheduler-related register values. */
	EXTERN(this_x86_kernel_psp0)
	movl   this_x86_kernel_psp0(R_TASK), %ecx
	EXTERN(thiscpu_x86_tss)
	movl   %ecx, thiscpu_x86_tss + OFFSET_TSS_ESP0(R_CPU)

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

#ifndef CONFIG_NO_FPU
	/* Disable the FPU, preparing it to be loaded lazily. */
	movl   %cr0, %ecx
	orl    $(CR0_TS), %ecx
	movl   %ecx, %cr0
	/* Also: Indicate that no task is currently holding an FPU context.
	 * NOTE: Technically, we could also move this part into `cpu_enter_deepsleep()',
	 *       however it's safer to unconditionally do this during initialization! */
	EXTERN(thiscpu_x86_fputhread)
	movl   $(0), thiscpu_x86_fputhread(R_CPU)
#endif /* !CONFIG_NO_FPU */

	/* (Partially) load the underlying CPU state */
	popal_cfi_r
	popl_cfi_r %gs

	pushal_cfi_r
	/* Load kernel-space segments. */
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	/* Service pending IPIs for the first time.
	 * -> Since we got here thanks to an INIT IPI, regular IPI callbacks
	 *    would not have generated their IPI interrupt, meaning we have
	 *    to manually check for callbacks this one time.
	 * NOTE: Since `x86_serve_ipi()' expects an `icpustate' structure,
	 *       we were forced to partially unwind the CPU state so-as to
	 *       already pre-load the `%gs' register. */
	movl   %esp, %ecx
	EXTERN(x86_serve_ipi)
	call   x86_serve_ipi
	movl   %eax, %esp
	popal_cfi_r

	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds

	iret
	.cfi_endproc
END(x86_smp_entry32)



.section .text.cold
/* FUNDEF void NOTHROW(FCALL cpu_enter_deepsleep)(struct cpu *__restrict caller); */
PUBLIC_FUNCTION(cpu_enter_deepsleep)
	.cfi_startproc
	/* Construct an IRET tail which will later be used to return to the caller. */
	popl_cfi %eax
	.cfi_register %eip, %eax
	pushfl_cfi_r                     /* irregs_kernel::ir_eflags */
	orl    $(EFLAGS_IF), 0(%esp)     /* Re-enable interrupts upon return */
	pushl_cfi %cs                    /* irregs_kernel::ir_cs */
	pushl_cfi %eax                   /* irregs_kernel::ir_eip */
	.cfi_endproc

	/* With an IRET tail constructed, switch to using a signal-frame CFI descriptor */
	.cfi_startproc simple
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0

	pushl_cfi %ds   /* sgregs::sg_ds */
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es   /* sgregs::sg_es */
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs   /* sgregs::sg_fs */
	.cfi_restore_iret_fs_or_offset -12
	pushl_cfi %gs   /* sgregs::sg_gs */
	.cfi_restore_iret_gs_or_offset -16

	pushal_cfi_r                       /* gpregs */

#ifndef CONFIG_NO_FPU
	/* With the CPU about to go OFFLINE, make sure to also save the current
	 * FPU state (if the FPU was used), so-as to not lose that information
	 * and have it still be available when we come back online. */
	EXTERN(thiscpu_x86_fputhread)
	movl   thiscpu_x86_fputhread(%ecx), %eax
	testl  %eax, %eax
	jz     1f
	clts   /* Make sure FPU access is allowed. */
	/* Save the current FPU context into `this_x86_fpustate(%eax)' */
	movl   %ecx, %ebx /* Preserve THIS_CPU */
	EXTERN(this_x86_fpustate)
	movl   this_x86_fpustate(%eax), %ecx
	EXTERN(x86_fpustate_save)
	call   x86_fpustate_save
	movl   %ebx, %ecx /* Restore THIS_CPU */
1:
#endif /* !CONFIG_NO_FPU */

	/* Decrement the cpu-online counter. */
	EXTERN(cpu_online_count)
	lock;  decl cpu_online_count

	EXTERN(thiscpu_idle_sched_state)
	movl   %esp, thiscpu_idle_sched_state(%ecx)

	/* Flush all caches before actually commiting to beginning to dream */
	wbinvd /* TODO: Only available since 486. - Must be replaced with `nop' no 386 */
	EXTERN(thiscpu_state)
	movl   $(CPU_STATE_DREAMING), thiscpu_state(%ecx)

	/* We're now dreaming, meaning that our core may get reset at any moment,
	 * and there is nothing we can do to undo this ourself, or prevent such a
	 * reset from happening.
	 * However, in the interest of ensuring that everyone got the memo, invalidate
	 * caches one more time (although this time it should only be caches related
	 * to us setting `thiscpu_state' to `CPU_STATE_DREAMING') */

	wbinvd /* TODO: Only available since 486. - Must be replaced with `nop' no 386 */

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
	movl   x86_lapicbase, %eax
	movl   $(0), APIC_SPURIOUS(%eax)


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

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_SCHED_SMP32_S */
