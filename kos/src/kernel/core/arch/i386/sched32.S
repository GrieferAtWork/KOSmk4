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

#include <kernel/compiler.h>
#include <kernel/pic.h>
#include <kernel/pit.h>
#include <kernel/gdt.h>
#include <kernel/apic.h>
#include <kernel/fpu.h>
#include <kernel/breakpoint.h>
#include <kernel/tss.h>
#include <kernel/except.h>
#include <sched/task.h>
#include <kos/kernel/cpu-state.h>

#include <kernel/syscall.h>

#include <asm/cfi.h>
#include <asm/cpu-flags.h>
#include <asm/param.h>

.section .text
INTERN_FUNCTION(x86_defidt_apic_spurious)
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

	/* Load kernel-space segments. */
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs

	call   x86_apic_spur
	movl   x86_lapic_base_address, %eax
	movl   $(APIC_EOI_FSIGNAL), APIC_EOI(%eax)

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
	.cfi_endproc
END(x86_defidt_apic_spurious)


INTERN(cpu_scheduler_interrupt)

/* The PIT interrupt handler -- Used for scheduling.
 * NOTE: If available, this interrupt will actually be fired by the LAPIC */
.section .text
INTERN_FUNCTION(x86_defidt_preemption)
	.cfi_startproc simple
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0

	/* Construct a full `struct scpustate' structure */
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	pushl_cfi %gs /* Note that this one also saves `%gs'! */
	.cfi_restore_iret_gs_or_offset -16

	pushal_cfi_r

	/* Load kernel-space segments. */
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs

	/* Acknowledge the interrupt. */
INTERN_FUNCTION(x86_pic_acknowledge)
	.byte  0x90, 0x90, 0x90, 0x90, 0x90
	.byte  0x90, 0x90, 0x90, 0x90, 0x90
	.byte  0x90, 0x90, 0x90, 0x90, 0x90
END(x86_pic_acknowledge)

	movl   %fs:0, %edx           /* cpu_scheduler_interrupt::struct task *__restrict thread */
	movl   %esp, _this_sched_state(%edx)
	movl   _this_cpu(%edx), %ebx /* THIS_CPU */
	movl   %ebx, %ecx            /* cpu_scheduler_interrupt::struct cpu *__restrict caller */

	/* Invoke the C-level interrupt implementation. */
	call   cpu_scheduler_interrupt

	/* Set the task returned by `cpu_scheduler_interrupt()'
	 * as the new current one. */
	movl   %eax, _this_cpu_current(%ebx)
INTERN_FUNCTION(x86_load_thread_eax_cpu_ebx)
	movl   _this_sched_state(%eax), %esp

	/* Load other scheduler-related register values. */
	movl   x86_this_kernel_sp0(%eax), %ecx
	movl   %ecx, x86_cputss + OFFSET_TSS_ESP0(%ebx)

#define GDT(x) x + x86_cpugdt(%ebx)
	/* SEGMENT_KERNEL_FSBASE */
	movl   %eax, %ecx
	movl   %eax, %edx
	shrl   $24,  %ecx
	andl   $0x00ffffff, %edx
	andl   $0xff000000, OFFSET_SEGMENT_DESCRIPTOR_BASE0 + GDT(SEGMENT_KERNEL_FSBASE) /* Clear out base_low */
	orl    %edx,        OFFSET_SEGMENT_DESCRIPTOR_BASE0 + GDT(SEGMENT_KERNEL_FSBASE) /* Set base_low */
	movb   %cl,         OFFSET_SEGMENT_DESCRIPTOR_BASE2 + GDT(SEGMENT_KERNEL_FSBASE) /* Set base_hi */

	/* SEGMENT_USER_FSBASE */
	movl   x86_this_user_fsbase(%eax), %ecx
	movl   %ecx, %edx
	shrl   $24,  %ecx
	andl   $0x00ffffff, %edx
	andl   $0xff000000, OFFSET_SEGMENT_DESCRIPTOR_BASE0 + GDT(SEGMENT_USER_FSBASE) /* Clear out base_low */
	orl    %edx,        OFFSET_SEGMENT_DESCRIPTOR_BASE0 + GDT(SEGMENT_USER_FSBASE) /* Set base_low */
	movb   %cl,         OFFSET_SEGMENT_DESCRIPTOR_BASE2 + GDT(SEGMENT_USER_FSBASE) /* Set base_hi */

	/* SEGMENT_USER_GSBASE */
	movl   x86_this_user_gsbase(%eax), %ecx
	movl   %ecx, %edx
	shrl   $24,  %ecx
	andl   $0x00ffffff, %edx
	andl   $0xff000000, OFFSET_SEGMENT_DESCRIPTOR_BASE0 + GDT(SEGMENT_USER_GSBASE) /* Clear out base_low */
	orl    %edx,        OFFSET_SEGMENT_DESCRIPTOR_BASE0 + GDT(SEGMENT_USER_GSBASE) /* Set base_low */
	movb   %cl,         OFFSET_SEGMENT_DESCRIPTOR_BASE2 + GDT(SEGMENT_USER_GSBASE) /* Set base_hi */
#undef GDT

#ifndef CONFIG_NO_FPU
	/* Disable the FPU, preparing it to be loaded lazily. */
	movl   %cr0, %ecx
	andl   $~CR0_TS, %ecx
	movl   x86_fpu_current(%ebx), %edx
	cmpl   %edx, %eax
	je     1f
	/* Only disable if the target thread isn't holding the active FPU-context */
	orl    $CR0_TS, %ecx
1:	movl   %ecx, %cr0
#endif /* !CONFIG_NO_FPU */

	/* Update the used page directory pointer. */
	movl   _this_vm(%eax), %ecx
	movl   _this_vm_pdir_phys_ptr(%ecx), %eax
	movl   %cr3, %edx
	cmpl   %edx, %eax
	je     1f
	movl   %eax, %cr3
	/* Reload debug registers */
	reload_x86_debug_registers %ecx, %eax, %edx, 1
1:

.Lload_scpustate_esp:
	/* Load the underlying CPU state */
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
	.cfi_endproc
END(x86_load_thread_eax_cpu_ebx)
END(x86_defidt_preemption)


.section .text
.cfi_startproc
PUBLIC_FUNCTION(task_pause)
#ifndef CONFIG_NO_SMP
	pause
#endif /* !CONFIG_NO_SMP */
	ret
END(task_pause)

PUBLIC_FUNCTION(task_yield)
	popl_cfi %eax
	.cfi_register %eip, %eax
	pushfl_cfi_r
	testl  $(EFLAGS_IF), (%esp)
	.cfi_remember_state
	jz     .Lillegal_task_yield
	pushl_cfi_r %cs
	pushl_cfi %eax
	.cfi_rel_offset %eip, 0
	pushl_cfi_r %ds
	pushl_cfi_r %es
	pushl_cfi_r %fs
	pushl_cfi_r %gs
	pushal_cfi_r

.Ltask_yield_with_saved_cpu_state:
	/* Remember the current scheduler state. */
	movl   %fs:0, %esi
	cli
	movl   _this_sched_runnxt(%esi), %edi
	cmpl   %esi, %edi
	je     .Lyield_same_target
.Ldo_task_yield_esi_to_edi:
	movl   _this_cpu(%esi), %ebx

	/* Check for a scheduling override. */
	cmpl   $0, _this_cpu_override(%ebx)
	jne    .Lyield_same_target_with_override

	/* CURR: %esi */
	/* NEXT: %edi */
	movl   %esp, _this_sched_state(%esi)

	/* Prematurely end the current quantum */
	call   cpu_quantum_end

	/* Load the new CPU state */
	movl   %edi, _this_cpu_current(%ebx)
	movl   %edi, %eax
	jmp    x86_load_thread_eax_cpu_ebx
.Lyield_same_target_with_override:
#ifndef NDEBUG
	cmpl   %esi, _this_cpu_override(%ebx)
	je     .Lyield_same_target
	int3   /* Assertion failed: CPU override does not match calling thread.
	        * >> struct task *caller = %esi;
	        * >> struct cpu  *mycpu = %ebx; */
#endif /* !NDEBUG */
.Lyield_same_target:
	sti
#ifndef CONFIG_NO_SMP
	pause
#endif /* !CONFIG_NO_SMP */
	jmp    .Lload_scpustate_esp
	.cfi_restore_state
.Lillegal_task_yield:
	movl   $(ERROR_CODEOF(E_WOULDBLOCK_PREEMPTED)), %ecx
	call   error_throw
END(task_yield)
.cfi_endproc
DEFINE_PUBLIC_ALIAS(sys_sched_yield,task_yield)


.section .text
INTERN_FUNCTION(X86_ASMSYSCALL32_INT80(sched_yield))
	.cfi_startproc simple
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0

	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	pushl_cfi %gs
	.cfi_restore_iret_gs_or_offset -16

	xorl   %eax, %eax /* sched_yield() should return 0 to user-space. */

	pushal_cfi_r

	movl   $(SEGMENT_USER_DATA_RPL), %eax
	movl   %eax, %ds
	movl   %eax, %es
	movl   $(SEGMENT_KERNEL_FSBASE), %eax
	movl   %eax, %fs

	jmp    .Ltask_yield_with_saved_cpu_state
	.cfi_endproc
END(X86_ASMSYSCALL32_INT80(sched_yield))
DEFINE_INTERN_ALIAS(X86_ASMSYSCALL32_SYSENTER(sched_yield),
                    X86_ASMSYSCALL32_INT80(sched_yield))



.section .text
PUBLIC_FUNCTION(task_yield_nx)
	.cfi_startproc
	popl_cfi  %eax
	.cfi_register %eip, %eax
	pushfl_cfi_r
	testl  $(EFLAGS_IF), (%esp)
	.cfi_remember_state
	jz     .Lillegal_task_yield_nx
	pushl_cfi_r %cs
	pushl_cfi %eax
	.cfi_rel_offset %eip, 0
	pushl_cfi_r %ds
	pushl_cfi_r %es
	pushl_cfi_r %fs
	pushl_cfi_r %gs
	movl   $1, %eax /* Eventually, we want to return true. */
	pushal_cfi_r

	/* Remember the current scheduler state. */
	movl   %fs:0, %esi
	cli
	movl   _this_sched_runnxt(%esi), %edi
	cmpl   %esi, %edi
	je     .Lyield_same_target
	jmp    .Ldo_task_yield_esi_to_edi
	.cfi_restore_state
.Lillegal_task_yield_nx:
	addl   $4, %esp
	.cfi_adjust_cfa_offset -4
	movl   %eax, %ecx
	.cfi_register %eip, %ecx
	movl   $0, %eax
	jmpl   *%ecx
	.cfi_endproc
END(task_yield_nx)


.section .text
PUBLIC_FUNCTION(task_tryyield_or_pause)
	.cfi_startproc
	popl_cfi  %ecx
	.cfi_register %eip, %ecx
	pushfl_cfi_r
	testl  $(EFLAGS_IF), (%esp)
	jnz    1f
	addl   $4, %esp
	.cfi_adjust_cfa_offset -4
	.cfi_same_value %eflags
	movl   $(TASK_TRYYIELD_PREEMPTION_DISABLED), %eax
#ifndef CONFIG_NO_SMP
	pause
#endif /* !CONFIG_NO_SMP */
	jmpl   *%ecx
END(task_tryyield_or_pause)
	.cfi_adjust_cfa_offset 4
	.cfi_restore %eip
PUBLIC_FUNCTION(task_tryyield)
	popl_cfi %ecx
	.cfi_register %eip, %ecx
	pushfl_cfi_r
	testl  $(EFLAGS_IF), (%esp)
	jnz    1f
	addl   $4, %esp
	.cfi_adjust_cfa_offset -4
	.cfi_same_value %eflags
	movl   $(TASK_TRYYIELD_PREEMPTION_DISABLED), %eax
	jmpl   *%ecx
1:	.cfi_adjust_cfa_offset 4
	.cfi_rel_offset %eflags, 0
	movl   $(TASK_TRYYIELD_SUCCESS), %eax
	pushl_cfi_r %cs
	pushl_cfi %ecx
	.cfi_rel_offset %eip, 0
	pushl_cfi_r %ds
	pushl_cfi_r %es
	pushl_cfi_r %fs
	pushl_cfi_r %gs
	pushal_cfi_r

	/* Remember the current scheduler state. */
	movl   %fs:0, %esi
	cli
	movl   _this_sched_runnxt(%esi), %edi
	cmpl   %esi, %edi
	jne    .Ldo_task_yield_esi_to_edi
	sti

	/* Same target... */
	movl   $(TASK_TRYYIELD_NO_SUCCESSOR), OFFSET_SCPUSTATE_GPREGS + OFFSET_GPREGS_EAX(%esp)
#ifndef CONFIG_NO_SMP
	pause
#endif /* !CONFIG_NO_SMP */
	jmp    .Lload_scpustate_esp
	.cfi_endproc
END(task_tryyield)



.section .text
PUBLIC_FUNCTION(cpu_run_current_and_remember)
	.cfi_startproc
	popl_cfi  %eax
	.cfi_register %eip, %eax
	pushfl_cfi_r
	orl    $(EFLAGS_IF), (%esp)
	pushl_cfi_r %cs
	pushl_cfi %eax
	.cfi_rel_offset %eip, 0
	pushl_cfi_r %ds
	pushl_cfi_r %es
	pushl_cfi_r %fs
	pushl_cfi_r %gs
	pushal_cfi_r

	/* Remember the current scheduler state. */
	movl   %esp, _this_sched_state(%ecx)
	movl   _this_cpu(%ecx), %ebx

	/* Load the new CPU state */
	movl   _this_cpu_current(%ebx), %eax
	jmp    x86_load_thread_eax_cpu_ebx
	.cfi_endproc
END(cpu_run_current_and_remember)

.section .text
PUBLIC_FUNCTION(cpu_run_current)
	.cfi_startproc
	/* Load the CPU state of the task set as current. */
	movl   %fs:0, %eax
	movl   _this_cpu(%eax), %ebx
	movl   _this_cpu_current(%ebx), %eax
	jmp    x86_load_thread_eax_cpu_ebx
	.cfi_endproc
END(cpu_run_current)



.section .text.free
INTERN_FUNCTION(x86_apic_cpu_quantum_elapsed)
	pushfl
	movl   x86_lapic_base_address, %ecx
	movl   %fs:_this_cpu, %eax
	cli
	movl   APIC_TIMER_CURRENT(%ecx), %ecx
	movl   cpu_quantum_length(%eax), %eax
	popfl
	subl   %ecx, %eax
	ret
INTERN(x86_apic_cpu_quantum_elapsed_size)
	x86_apic_cpu_quantum_elapsed_size = . - x86_apic_cpu_quantum_elapsed
END(x86_apic_cpu_quantum_elapsed)

INTERN_FUNCTION(x86_apic_cpu_quantum_elapsed_nopr)
	movl   x86_lapic_base_address, %ecx
	movl   %fs:_this_cpu, %eax
	movl   APIC_TIMER_CURRENT(%ecx), %ecx
	movl   cpu_quantum_length(%eax), %eax
	subl   %ecx, %eax
	ret
INTERN(x86_apic_cpu_quantum_elapsed_size_nopr)
	x86_apic_cpu_quantum_elapsed_size_nopr = . - x86_apic_cpu_quantum_elapsed_nopr
END(x86_apic_cpu_quantum_elapsed_nopr)

INTERN_FUNCTION(x86_apic_cpu_quantum_remaining)
	pushfl
	movl   x86_lapic_base_address, %eax
	cli
	movl   APIC_TIMER_CURRENT(%eax), %eax
	popfl
	ret
INTERN(x86_apic_cpu_quantum_remaining_size)
	x86_apic_cpu_quantum_remaining_size = . - x86_apic_cpu_quantum_remaining
END(x86_apic_cpu_quantum_remaining)

INTERN_FUNCTION(x86_apic_cpu_quantum_remaining_nopr)
	movl   x86_lapic_base_address, %eax
	movl   APIC_TIMER_CURRENT(%eax), %eax
	ret
INTERN(x86_apic_cpu_quantum_remaining_size_nopr)
	x86_apic_cpu_quantum_remaining_size_nopr = . - x86_apic_cpu_quantum_remaining_nopr
END(x86_apic_cpu_quantum_remaining_nopr)

INTERN_FUNCTION(x86_apic_cpu_disable_preemptive_interrupts)
	pushfl
	movl   x86_lapic_base_address, %ecx
	cli
	/* lapic_write(APIC_TIMER, APIC_TIMER_FDISABLED); */
	movl   $(APIC_TIMER_FDISABLED), APIC_TIMER(%ecx)
	popfl
	ret
INTERN(x86_apic_cpu_disable_preemptive_interrupts_size)
	x86_apic_cpu_disable_preemptive_interrupts_size = . - x86_apic_cpu_disable_preemptive_interrupts
END(x86_apic_cpu_disable_preemptive_interrupts)

INTERN_FUNCTION(x86_apic_cpu_disable_preemptive_interrupts_nopr)
	movl   x86_lapic_base_address, %ecx
	/* lapic_write(APIC_TIMER, APIC_TIMER_FDISABLED); */
	movl   $(APIC_TIMER_FDISABLED), APIC_TIMER(%ecx)
	ret
INTERN(x86_apic_cpu_disable_preemptive_interrupts_size_nopr)
	x86_apic_cpu_disable_preemptive_interrupts_size_nopr = . - x86_apic_cpu_disable_preemptive_interrupts_nopr
END(x86_apic_cpu_disable_preemptive_interrupts_nopr)

INTERN_FUNCTION(x86_apic_cpu_enable_preemptive_interrupts)
	pushfl
	movl   %fs:_this_cpu, %eax
	movl   x86_lapic_base_address, %ecx
	cli
	movl   cpu_quantum_length(%eax), %eax
	/* lapic_write(APIC_TIMER_DIVIDE, APIC_TIMER_DIVIDE_F16); */
	movl   $(APIC_TIMER_DIVIDE_F16), APIC_TIMER_DIVIDE(%ecx)
	/* lapic_write(APIC_TIMER,
	 *             // Set the PIT interrupt to the APIC timer.
	 *             X86_INTNO_PIC1_PIT |
	 *             APIC_TIMER_MODE_FPERIODIC |
	 *             APIC_TIMER_SOURCE_FDIV); */
	movl   $(X86_INTNO_PIC1_PIT | APIC_TIMER_MODE_FPERIODIC | APIC_TIMER_SOURCE_FDIV), \
	       APIC_TIMER(%ecx)
	/* lapic_write(APIC_TIMER_INITIAL,PERCPU(cpu_quantum_length)); */
	movl   %eax, APIC_TIMER_INITIAL(%ecx)
	popfl
	ret
INTERN(x86_apic_cpu_enable_preemptive_interrupts_size)
	x86_apic_cpu_enable_preemptive_interrupts_size = . - x86_apic_cpu_enable_preemptive_interrupts
END(x86_apic_cpu_enable_preemptive_interrupts)

INTERN_FUNCTION(x86_apic_cpu_enable_preemptive_interrupts_nopr)
	movl   %fs:_this_cpu, %eax
	movl   x86_lapic_base_address, %ecx
	movl   cpu_quantum_length(%eax), %eax
	/* lapic_write(APIC_TIMER_DIVIDE, APIC_TIMER_DIVIDE_F16); */
	movl   $(APIC_TIMER_DIVIDE_F16), APIC_TIMER_DIVIDE(%ecx)
	/* lapic_write(APIC_TIMER,
	 *             // Set the PIT interrupt to the APIC timer.
	 *             X86_INTNO_PIC1_PIT |
	 *             APIC_TIMER_MODE_FPERIODIC |
	 *             APIC_TIMER_SOURCE_FDIV); */
	movl   $(X86_INTNO_PIC1_PIT | APIC_TIMER_MODE_FPERIODIC | APIC_TIMER_SOURCE_FDIV), \
	       APIC_TIMER(%ecx)
	/* lapic_write(APIC_TIMER_INITIAL, PERCPU(cpu_quantum_length)); */
	movl   %eax, APIC_TIMER_INITIAL(%ecx)
	ret
INTERN(x86_apic_cpu_enable_preemptive_interrupts_size_nopr)
	x86_apic_cpu_enable_preemptive_interrupts_size_nopr = . - x86_apic_cpu_enable_preemptive_interrupts_nopr
END(x86_apic_cpu_enable_preemptive_interrupts_nopr)

INTERN_FUNCTION(x86_apic_cpu_quantum_reset)
	pushfl
	movl   %fs:_this_cpu, %eax
	movl   x86_lapic_base_address, %ecx
	cli
	movl   cpu_quantum_length(%eax), %eax
	/* lapic_write(APIC_TIMER_CURRENT, PERCPU(cpu_quantum_length)); */
	movl   %eax, APIC_TIMER_CURRENT(%ecx)
	popfl
	ret
INTERN(x86_apic_cpu_quantum_reset_size)
	x86_apic_cpu_quantum_reset_size = . - x86_apic_cpu_quantum_reset
END(x86_apic_cpu_quantum_reset)

INTERN_FUNCTION(x86_apic_cpu_quantum_reset_nopr)
	movl   %fs:_this_cpu, %eax
	movl   x86_lapic_base_address, %ecx
	movl   cpu_quantum_length(%eax), %eax
	/* lapic_write(APIC_TIMER_CURRENT, PERCPU(cpu_quantum_length)); */
	movl   %eax, APIC_TIMER_CURRENT(%ecx)
	ret
INTERN(x86_apic_cpu_quantum_reset_size_nopr)
	x86_apic_cpu_quantum_reset_size_nopr = . - x86_apic_cpu_quantum_reset_nopr
END(x86_apic_cpu_quantum_reset_nopr)

INTERN_FUNCTION(x86_apic_cpu_ipi_pending)
	/* u32 mask = lapic_read(APIC_ISR(APIC_ISR_INDEX(X86_INTERRUPT_APIC_IPI))); */
	/* return (mask & APIC_ISR_MASK(X86_INTERRUPT_APIC_IPI)) != 0; */
	xorl   %eax, %eax
	movl   x86_lapic_base_address, %ecx
	movl   APIC_ISR(APIC_ISR_INDEX(X86_INTERRUPT_APIC_IPI))(%ecx), %ecx
	testl  $(APIC_ISR_MASK(X86_INTERRUPT_APIC_IPI)), %ecx
	setnz  %al
	ret
INTERN(x86_apic_cpu_ipi_pending_size)
	x86_apic_cpu_ipi_pending_size = . - x86_apic_cpu_ipi_pending
END(x86_apic_cpu_ipi_pending)



.section .text
PUBLIC_FUNCTION(cpu_quantum_remaining_nopr)
	/* Read the current PIT counter position. */
	movb   $(PIT_COMMAND_SELECT_F0 | \
	         PIT_COMMAND_ACCESS_FLATCH | \
	         PIT_COMMAND_FBINARY), %al
	outb   %al,  $(PIT_COMMAND)
	inb    $(PIT_DATA0),     %al
	movb   %al, %cl
	inb    $(PIT_DATA0),     %al
	movb   %al, %ch
	movzwl %cx, %eax
	ret
.if x86_apic_cpu_quantum_remaining_size_nopr > (. - cpu_quantum_remaining_nopr)
.skip x86_apic_cpu_quantum_remaining_size_nopr - (. - cpu_quantum_remaining_nopr)
.endif
END(cpu_quantum_remaining_nopr)


PUBLIC_FUNCTION(cpu_quantum_remaining)
	pushfl
	cli
	/* Read the current PIT counter position. */
	movb   $(PIT_COMMAND_SELECT_F0 | \
	         PIT_COMMAND_ACCESS_FLATCH | \
	         PIT_COMMAND_FBINARY), %al
	outb   %al,  $(PIT_COMMAND)
	inb    $(PIT_DATA0),     %al
	movb   %al, %cl
	inb    $(PIT_DATA0),     %al
	popfl
	movb   %al, %ch
	movzwl %cx, %eax
	ret
.if x86_apic_cpu_quantum_remaining_size > (. - cpu_quantum_remaining)
.skip x86_apic_cpu_quantum_remaining_size - (. - cpu_quantum_remaining)
.endif
END(cpu_quantum_remaining)

PUBLIC_FUNCTION(cpu_quantum_elapsed_nopr)
	/* Read the current PIT counter position. */
	movb   $(PIT_COMMAND_SELECT_F0 | \
	         PIT_COMMAND_ACCESS_FLATCH | \
	         PIT_COMMAND_FBINARY), %al
	outb   %al,  $(PIT_COMMAND)
	inb    $(PIT_DATA0),     %al
	movb   %al, %cl
	inb    $(PIT_DATA0),     %al
	movb   %al, %ch
	movl   $PIT_HZ_DIV(HZ), %eax
	subw   %cx, %ax
	ret
.if x86_apic_cpu_quantum_elapsed_size_nopr > (. - cpu_quantum_elapsed_nopr)
.skip x86_apic_cpu_quantum_elapsed_size_nopr - (. - cpu_quantum_elapsed_nopr)
.endif
END(cpu_quantum_elapsed_nopr)

PUBLIC_FUNCTION(cpu_quantum_elapsed)
	pushfl
	movb   $(PIT_COMMAND_SELECT_F0 | \
	         PIT_COMMAND_ACCESS_FLATCH | \
	         PIT_COMMAND_FBINARY), %al
	cli
	/* Read the current PIT counter position. */
	outb   %al,  $(PIT_COMMAND)
	inb    $(PIT_DATA0),     %al
	movb   %al, %cl
	inb    $(PIT_DATA0),     %al
	popfl
	movb   %al, %ch
	movl   $PIT_HZ_DIV(HZ), %eax
	subw   %cx, %ax
	ret
.if x86_apic_cpu_quantum_elapsed_size > (. - cpu_quantum_elapsed)
.skip x86_apic_cpu_quantum_elapsed_size - (. - cpu_quantum_elapsed)
.endif
END(cpu_quantum_elapsed)


INTERN_FUNCTION(x86_cpu_disable_preemptive_interrupts)
	pushfl
	cli
	/* Disable the PIT interrupt within the PIC */
	inb    $(X86_PIC1_DATA), %al
	orb    $(1 << (X86_INTNO_PIC1_PIT-X86_INTERRUPT_PIC1_BASE)), %al
	outb   %al, $(X86_PIC1_DATA)
	/* Set the PIT to one-shot mode to keep it from running
	 * -> https://forum.osdev.org/viewtopic.php?t=11689&p=80318 */
	/* outb(PIT_COMMAND,
	 *      PIT_COMMAND_SELECT_F0 |
	 *      PIT_COMMAND_ACCESS_FLOHI |
	 *      PIT_COMMAND_MODE_FONESHOT); */
	movb   $(PIT_COMMAND_SELECT_F0 | \
	         PIT_COMMAND_ACCESS_FLOHI | \
	         PIT_COMMAND_MODE_FONESHOT), %al
	outb   %al, $(PIT_COMMAND)
	/* Normally at this point, the PIT would want us to specify the delay,
	 * however by not telling it anything, we essentially leave it hanging
	 * in this semi-disabled mode until we reset it at a later point in time. */
	popfl
	ret
.if x86_apic_cpu_disable_preemptive_interrupts_size > (. - x86_cpu_disable_preemptive_interrupts)
.skip x86_apic_cpu_disable_preemptive_interrupts_size - (. - x86_cpu_disable_preemptive_interrupts)
.endif
END(x86_cpu_disable_preemptive_interrupts)

INTERN_FUNCTION(x86_cpu_disable_preemptive_interrupts_nopr)
	/* Disable the PIT interrupt within the PIC */
	inb    $(X86_PIC1_DATA), %al
	orb    $(1 << (X86_INTNO_PIC1_PIT-X86_INTERRUPT_PIC1_BASE)), %al
	outb   %al, $(X86_PIC1_DATA)
	/* Set the PIT to one-shot mode to keep it from running
	 * -> https://forum.osdev.org/viewtopic.php?t=11689&p=80318 */
	/* outb(PIT_COMMAND,
	 *      PIT_COMMAND_SELECT_F0 |
	 *      PIT_COMMAND_ACCESS_FLOHI |
	 *      PIT_COMMAND_MODE_FONESHOT); */
	movb   $(PIT_COMMAND_SELECT_F0 | \
	         PIT_COMMAND_ACCESS_FLOHI | \
	         PIT_COMMAND_MODE_FONESHOT), %al
	outb   %al, $(PIT_COMMAND)
	/* Normally at this point, the PIT would want us to specify the delay,
	 * however by not telling it anything, we essentially leave it hanging
	 * in this semi-disabled mode until we reset it at a later point in time. */
	ret
.if x86_apic_cpu_disable_preemptive_interrupts_size_nopr > (. - x86_cpu_disable_preemptive_interrupts_nopr)
.skip x86_apic_cpu_disable_preemptive_interrupts_size_nopr - (. - x86_cpu_disable_preemptive_interrupts_nopr)
.endif
END(x86_cpu_disable_preemptive_interrupts_nopr)

INTERN_FUNCTION(x86_cpu_enable_preemptive_interrupts)
	pushfl
	movb   $(PIT_COMMAND_SELECT_F0 | \
	         PIT_COMMAND_ACCESS_FLOHI | \
	         PIT_COMMAND_MODE_FSQRWAVE | \
	         PIT_COMMAND_FBINARY), %al
	cli
	/* outb(PIT_COMMAND,
	 *      PIT_COMMAND_SELECT_F0 |
	 *      PIT_COMMAND_ACCESS_FLOHI |
	 *      PIT_COMMAND_MODE_FSQRWAVE |
	 *      PIT_COMMAND_FBINARY) */
	outb   %al, $(PIT_COMMAND)
	/* outb_p(PIT_DATA0, PIT_HZ_DIV(HZ) & 0xff) */
	movb   $(PIT_HZ_DIV(HZ) & 0xff), %al
	outb   %al, $(PIT_DATA0)
	outb   %al, $(0x80)  /* io_pause() */
	/* outb(PIT_DATA0, PIT_HZ_DIV(HZ) >> 8); */
	movb   $(PIT_HZ_DIV(HZ) >> 8), %al
	outb   %al, $(PIT_DATA0)
	/* Now to enable to the PIC */
	inb    $(X86_PIC1_DATA), %al
	andb   $~(1 << (X86_INTNO_PIC1_PIT-X86_INTERRUPT_PIC1_BASE)), %al
	outb   %al, $(X86_PIC1_DATA)
	popfl
	ret
.if x86_apic_cpu_enable_preemptive_interrupts_size > (. - x86_cpu_enable_preemptive_interrupts)
.skip x86_apic_cpu_enable_preemptive_interrupts_size - (. - x86_cpu_enable_preemptive_interrupts)
.endif
END(x86_cpu_enable_preemptive_interrupts)

INTERN_FUNCTION(x86_cpu_enable_preemptive_interrupts_nopr)
	/* outb(PIT_COMMAND,
	 *      PIT_COMMAND_SELECT_F0 |
	 *      PIT_COMMAND_ACCESS_FLOHI |
	 *      PIT_COMMAND_MODE_FSQRWAVE |
	 *      PIT_COMMAND_FBINARY) */
	movb   $(PIT_COMMAND_SELECT_F0 | \
	         PIT_COMMAND_ACCESS_FLOHI | \
	         PIT_COMMAND_MODE_FSQRWAVE | \
	         PIT_COMMAND_FBINARY), %al
	outb   %al, $(PIT_COMMAND)
	/* outb_p(PIT_DATA0, PIT_HZ_DIV(HZ) & 0xff) */
	movb    $(PIT_HZ_DIV(HZ) & 0xff), %al
	outb   %al, $(PIT_DATA0)
	outb   %al, $(0x80)  /* io_pause() */
	/* outb(PIT_DATA0, PIT_HZ_DIV(HZ) >> 8); */
	movb   $(PIT_HZ_DIV(HZ) >> 8), %al
	outb   %al, $(PIT_DATA0)
	/* Now to enable to the PIC */
	inb    $(X86_PIC1_DATA), %al
	andb   $~(1 << (X86_INTNO_PIC1_PIT-X86_INTERRUPT_PIC1_BASE)), %al
	outb   %al, $(X86_PIC1_DATA)
	ret
.if x86_apic_cpu_enable_preemptive_interrupts_size_nopr > (. - x86_cpu_enable_preemptive_interrupts_nopr)
.skip x86_apic_cpu_enable_preemptive_interrupts_size_nopr - (. - x86_cpu_enable_preemptive_interrupts_nopr)
.endif
END(x86_cpu_enable_preemptive_interrupts_nopr)


PUBLIC_FUNCTION(cpu_quantum_reset)
	pushfl
	movb   $(PIT_COMMAND_SELECT_F0 | \
	         PIT_COMMAND_ACCESS_FLOHI | \
	         PIT_COMMAND_MODE_FSQRWAVE | \
	         PIT_COMMAND_FBINARY), %al
	cli
	/* Re-initialize to reset the latch counter. */
	/* outb(PIT_COMMAND,
	 *      PIT_COMMAND_SELECT_F0 |
	 *      PIT_COMMAND_ACCESS_FLOHI |
	 *      PIT_COMMAND_MODE_FSQRWAVE |
	 *      PIT_COMMAND_FBINARY) */
	outb   %al, $(PIT_COMMAND)
	/* outb_p(PIT_DATA0, PIT_HZ_DIV(HZ) & 0xff) */
	movb   $(PIT_HZ_DIV(HZ) & 0xff), %al
	outb   %al, $(PIT_DATA0)
	outb   %al, $(0x80)  /* io_pause() */
	/* outb(PIT_DATA0, PIT_HZ_DIV(HZ) >> 8); */
	movb   $(PIT_HZ_DIV(HZ) >> 8), %al
	outb   %al, $(PIT_DATA0)
	popfl
	ret
.if x86_apic_cpu_quantum_reset_size > (. - cpu_quantum_reset)
.skip x86_apic_cpu_quantum_reset_size - (. - cpu_quantum_reset)
.endif
END(cpu_quantum_reset)

PUBLIC_FUNCTION(cpu_quantum_reset_nopr)
	/* Re-initialize to reset the latch counter. */
	/* outb(PIT_COMMAND,
	 *      PIT_COMMAND_SELECT_F0 |
	 *      PIT_COMMAND_ACCESS_FLOHI |
	 *      PIT_COMMAND_MODE_FSQRWAVE |
	 *      PIT_COMMAND_FBINARY) */
	movb   $(PIT_COMMAND_SELECT_F0 | \
	         PIT_COMMAND_ACCESS_FLOHI | \
	         PIT_COMMAND_MODE_FSQRWAVE | \
	         PIT_COMMAND_FBINARY), %al
	outb   %al, $(PIT_COMMAND)
	/* outb_p(PIT_DATA0, PIT_HZ_DIV(HZ) & 0xff) */
	movb   $(PIT_HZ_DIV(HZ) & 0xff), %al
	outb   %al, $(PIT_DATA0)
	outb   %al, $(0x80)  /* io_pause() */
	/* outb(PIT_DATA0, PIT_HZ_DIV(HZ) >> 8); */
	movb   $(PIT_HZ_DIV(HZ) >> 8), %al
	outb   %al, $(PIT_DATA0)
	ret
.if x86_apic_cpu_quantum_reset_size_nopr > (. - cpu_quantum_reset_nopr)
.skip x86_apic_cpu_quantum_reset_size_nopr - (. - cpu_quantum_reset_nopr)
.endif
END(cpu_quantum_reset_nopr)


PUBLIC_FUNCTION(cpu_hwipi_pending)
	/* outb(X86_PIC1_CMD, X86_PIC_READ_IRR) */
	pushfl
	movl   $(X86_PIC_READ_IRR), %eax /* NOTE: This also clears all of the upper bits! */
	cli
	outb   %al, $(X86_PIC1_CMD)
	/* AL = inb(X86_PIC1_CMD) */
	inb    $(X86_PIC2_CMD), %al
	popfl
	/* return PIT_BIT_IS_SET(AL); */
	testb  $(1 << (X86_INTNO_PIC1_PIT-X86_INTERRUPT_PIC1_BASE)), %al
	setnz  %al
	ret
.if x86_apic_cpu_ipi_pending_size > (. - cpu_hwipi_pending)
.skip x86_apic_cpu_ipi_pending_size - (. - cpu_hwipi_pending)
.endif
END(cpu_hwipi_pending)




