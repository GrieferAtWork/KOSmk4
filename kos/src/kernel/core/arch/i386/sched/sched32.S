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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_SCHED_SCHED32_S
#define GUARD_KERNEL_CORE_ARCH_I386_SCHED_SCHED32_S 1
#define __ASSEMBLER__ 1

#include <kernel/compiler.h>

#include <debugger/config.h>
#include <kernel/except.h>
#include <kernel/fpu.h> /* CONFIG_FPU */
#include <kernel/syscall.h>
#include <kernel/x86/apic.h>
#include <kernel/x86/breakpoint.h>
#include <kernel/x86/gdt.h>
#include <kernel/x86/pic.h>
#include <kernel/x86/pit.h>
#include <kernel/x86/syscall-tables.h>
#include <sched/task.h>
#include <sched/x86/tss.h>

#include <asm/cfi.h>
#include <asm/cpu-flags.h>
#include <asm/instr/jccN.h>
#include <asm/instr/ttest.h>
#include <kos/kernel/cpu-state.h>



.section .text
INTERN_FUNCTION(x86_idt_apic_spurious)
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

	EXTERN(x86_apic_spur)
	call   x86_apic_spur
	EXTERN(x86_lapicbase)
	movl   x86_lapicbase, %eax
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
END(x86_idt_apic_spurious)


.section .rodata.free
INTERN_FUNCTION(x86_ack_apic)
	EXTERN(x86_lapicbase)
	movl   x86_lapicbase, %eax
	movl   $(APIC_EOI_FSIGNAL), APIC_EOI(%eax)
INTERN_CONST(x86_ack_apic_size, . - x86_ack_apic)
END(x86_ack_apic)

.section .rodata.free
INTERN_FUNCTION(x86_ack_pic)
	movb   $(X86_PIC_CMD_EOI), %al
	outb   %al, $(X86_PIC1_CMD)
	.skip  x86_ack_apic_size - (. - x86_ack_pic), 0x90
END(x86_ack_pic)


/* The PIT interrupt handler -- Used for scheduling.
 * NOTE: If available, this interrupt will actually be fired by the LAPIC */
.section .text
INTERN_FUNCTION(x86_idt_preemption)
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
	.rept  x86_ack_apic_size
	.byte  0x90
	.endr
END(x86_pic_acknowledge)

	movl   %fs:0, %edx           /* cpu_scheduler_interrupt::struct task *__restrict thread */
	EXTERN(this_sched_state)
	movl   %esp, this_sched_state(%edx)
	EXTERN(this_cpu)
	movl   this_cpu(%edx), %ebx /* THIS_CPU */
	movl   %ebx, %ecx            /* cpu_scheduler_interrupt::struct cpu *__restrict caller */

	/* Invoke the C-level interrupt implementation. */
	EXTERN(cpu_scheduler_interrupt)
	call   cpu_scheduler_interrupt

	/* Set the task returned by `cpu_scheduler_interrupt()'
	 * as the new current one. */
	EXTERN(thiscpu_current)
	movl   %eax, thiscpu_current(%ebx)
INTERN_FUNCTION(x86_load_thread_eax_cpu_ebx)
	EXTERN(this_sched_state)
	movl   this_sched_state(%eax), %esp

	/* Load other scheduler-related register values. */
	EXTERN(this_x86_kernel_psp0)
	movl   this_x86_kernel_psp0(%eax), %ecx
	EXTERN(thiscpu_x86_tss)
	movl   %ecx, thiscpu_x86_tss + OFFSET_TSS_ESP0(%ebx)

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
	movl   this_x86_user_fsbase(%eax), %ecx
	movl   %ecx, %edx
	shrl   $(24), %ecx
	andl   $(0x00ffffff), %edx
	andl   $(0xff000000), OFFSET_SEGMENT_DESCRIPTOR_BASE0 + GDT(SEGMENT_USER_FSBASE) /* Clear out base_low */
	orl    %edx,          OFFSET_SEGMENT_DESCRIPTOR_BASE0 + GDT(SEGMENT_USER_FSBASE) /* Set base_low */
	movb   %cl,           OFFSET_SEGMENT_DESCRIPTOR_BASE2 + GDT(SEGMENT_USER_FSBASE) /* Set base_hi */

	/* SEGMENT_USER_GSBASE */
	movl   this_x86_user_gsbase(%eax), %ecx
	movl   %ecx, %edx
	shrl   $(24), %ecx
	andl   $(0x00ffffff), %edx
	andl   $(0xff000000), OFFSET_SEGMENT_DESCRIPTOR_BASE0 + GDT(SEGMENT_USER_GSBASE) /* Clear out base_low */
	orl    %edx,          OFFSET_SEGMENT_DESCRIPTOR_BASE0 + GDT(SEGMENT_USER_GSBASE) /* Set base_low */
	movb   %cl,           OFFSET_SEGMENT_DESCRIPTOR_BASE2 + GDT(SEGMENT_USER_GSBASE) /* Set base_hi */
#undef GDT

#ifdef CONFIG_FPU
	/* Disable the FPU, preparing it to be loaded lazily. */
	movl   %cr0, %ecx
	andl   $(~CR0_TS), %ecx
	EXTERN(thiscpu_x86_fputhread)
	movl   thiscpu_x86_fputhread(%ebx), %edx
	cmpl   %edx, %eax
	je     1f
	/* Only disable if the target thread isn't holding the active FPU-context */
	orl    $(CR0_TS), %ecx
1:	movl   %ecx, %cr0
#endif /* CONFIG_FPU */

	/* Check if the old thread had its I/O permissions bitmap loaded. */
	EXTERN(thiscpu_x86_ioperm_bitmap)
	cmpl   $(0), thiscpu_x86_ioperm_bitmap(%ebx)
	jne    .Llazy_disable_ioperm_bitmap
INTERN_LABEL(__x86_lazy_disable_ioperm_bitmap_return):

	.cfi_remember_state

	/* Update the used page directory pointer. */
	EXTERN(this_vm)
	movl   this_vm(%eax), %ecx
	EXTERN(thisvm_pdir_phys_ptr)
	movl   thisvm_pdir_phys_ptr(%ecx), %eax
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
	.cfi_restore_state

	/* Disable the I/O permissions bitmap. */
.Llazy_disable_ioperm_bitmap:
	/* Check if the loaded I/O permissions bitmap is the calling thread's */
	EXTERN(this_x86_ioperm_bitmap)
	movl   this_x86_ioperm_bitmap(%eax), %edx
	EXTERN(thiscpu_x86_ioperm_bitmap)
	cmpl   %edx, thiscpu_x86_ioperm_bitmap(%ebx)
	je     __x86_lazy_disable_ioperm_bitmap_return
	/* Must actually unmap the I/O permissions bitmap! */
	EXTERN(thiscpu_x86_iobnode_pagedir_identity)
	movl   thiscpu_x86_iobnode_pagedir_identity(%ebx), %edx
	xorl   %ecx, %ecx  /* P32_PAGE_ABSENT / PAE_PAGE_ABSENT */
	movl   %ecx, thiscpu_x86_ioperm_bitmap(%ebx)
	movl   %ecx, 0x0(%edx)
	movl   %ecx, 0x4(%edx)
#ifndef CONFIG_NO_PAGING_PAE
INTERN_FUNCTION(__x86_lazy_disable_ioperm_bitmap_pae)
	/* When PAE paging is disabled, paging initialization overrides this
	 * instruction location with a `jmp __x86_lazy_disable_ioperm_bitmap_return' */
	movl   %ecx, 0x8(%edx)
	movl   %ecx, 0xc(%edx)
END(__x86_lazy_disable_ioperm_bitmap_pae)
#endif /* !CONFIG_NO_PAGING_PAE */
	/* XXX: invlpg */
	jmp    __x86_lazy_disable_ioperm_bitmap_return
	.cfi_endproc
END(x86_load_thread_eax_cpu_ebx)
END(x86_idt_preemption)


#ifdef CONFIG_HAVE_DEBUGGER
.section .text.cold
INTERN_FUNCTION(x86_dbgidt_preemption) /* ISR_X86_f0 */
	.cfi_startproc simple
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi_r %eax
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	/* Acknowledge the interrupt. */
INTERN_FUNCTION(x86_debug_pic_acknowledge)
	.rept  x86_ack_apic_size
	.byte  0x90
	.endr
END(x86_debug_pic_acknowledge)
	popl_cfi_r %eax
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(x86_dbgidt_preemption)
#endif /* CONFIG_HAVE_DEBUGGER */


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
	ttest  mask=EFLAGS_IF, loc=(%esp)
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
	EXTERN(this_sched_runnxt)
	movl   this_sched_runnxt(%esi), %edi
	cmpl   %esi, %edi
	je     .Lyield_same_target
.Ldo_task_yield_esi_to_edi:
	movl   this_cpu(%esi), %ebx

	/* Check for a scheduling override. */
	EXTERN(thiscpu_override)
	cmpl   $(0), thiscpu_override(%ebx)
	jne    .Lyield_same_target_with_override

	/* CURR: %esi */
	/* NEXT: %edi */
	movl   %esp, this_sched_state(%esi)

	/* Prematurely end the current quantum */
	movl   %esi, %ecx /* current */
	movl   %edi, %edx /* next */
	EXTERN(cpu_quantum_end_nopr)
	call   cpu_quantum_end_nopr

	/* Load the new CPU state */
	EXTERN(thiscpu_current)
	movl   %edi, thiscpu_current(%ebx)
	movl   %edi, %eax
	EXTERN(x86_load_thread_eax_cpu_ebx)
	jmp    x86_load_thread_eax_cpu_ebx
.Lyield_same_target_with_override:
#ifndef NDEBUG
	EXTERN(thiscpu_override)
	cmpl   %esi, thiscpu_override(%ebx)
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
	EXTERN(error_throw)
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
	ttest  mask=EFLAGS_IF, loc=(%esp)
	.cfi_remember_state
	jz     .Lillegal_task_yield_nx
	pushl_cfi_r %cs
	pushl_cfi %eax
	.cfi_rel_offset %eip, 0
	pushl_cfi_r %ds
	pushl_cfi_r %es
	pushl_cfi_r %fs
	pushl_cfi_r %gs
	movl   $(1), %eax /* Eventually, we want to return true. */
	pushal_cfi_r

	/* Remember the current scheduler state. */
	movl   %fs:0, %esi
	cli
	EXTERN(this_sched_runnxt)
	movl   this_sched_runnxt(%esi), %edi
	cmpl   %esi, %edi
	je     .Lyield_same_target
	jmp    .Ldo_task_yield_esi_to_edi
	.cfi_restore_state
.Lillegal_task_yield_nx:
	addl   $(4), %esp
	.cfi_adjust_cfa_offset -4
	movl   %eax, %ecx
	.cfi_register %eip, %ecx
	movl   $(0), %eax
	jmpl   *%ecx
	.cfi_endproc
END(task_yield_nx)


.section .text
PUBLIC_FUNCTION(task_tryyield_or_pause)
	.cfi_startproc
	popl_cfi  %ecx
	.cfi_register %eip, %ecx
	pushfl_cfi_r
	ttest  mask=EFLAGS_IF, loc=(%esp)
	jnz    1f
	addl   $(4), %esp
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
	ttest  mask=EFLAGS_IF, loc=(%esp)
	jnz    1f
	addl   $(4), %esp
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
	EXTERN(this_sched_runnxt)
	movl   this_sched_runnxt(%esi), %edi
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
PUBLIC_FUNCTION(cpu_run_current_and_remember_nopr)
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
	EXTERN(this_sched_state)
	movl   %esp, this_sched_state(%ecx)
	EXTERN(this_cpu)
	movl   this_cpu(%ecx), %ebx

	/* Load the new CPU state */
	EXTERN(thiscpu_current)
	movl   thiscpu_current(%ebx), %eax
	jmp    x86_load_thread_eax_cpu_ebx
	.cfi_endproc
END(cpu_run_current_and_remember_nopr)

.section .text
PUBLIC_FUNCTION(cpu_run_current_nopr)
	.cfi_startproc
	/* Load the CPU state of the task set as current. */
	movl   %fs:0, %eax
	EXTERN(this_cpu)
	movl   this_cpu(%eax), %ebx
	EXTERN(thiscpu_current)
	movl   thiscpu_current(%ebx), %eax
	jmp    x86_load_thread_eax_cpu_ebx
	.cfi_endproc
END(cpu_run_current_nopr)

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_SCHED_SCHED32_S */
