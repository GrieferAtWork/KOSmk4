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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_SCHED_SCHED64_S
#define GUARD_KERNEL_CORE_ARCH_I386_SCHED_SCHED64_S 1

#include <kernel/compiler.h>

#include <debugger/config.h>
#include <kernel/apic.h>
#include <kernel/arch/paging64.h>
#include <kernel/breakpoint.h>
#include <kernel/except.h>
#include <kernel/fpu.h>
#include <kernel/gdt.h>
#include <kernel/pic.h>
#include <kernel/pit.h>
#include <kernel/syscall-tables.h>
#include <kernel/syscall.h>
#include <sched/task.h>
#include <sched/tss.h>

#include <asm/cfi.h>
#include <asm/cpu-flags.h>
#include <asm/cpu-msr.h>
#include <asm/instr/fsgsbase.h>
#include <asm/instr/interrupt.h>
#include <asm/instr/kgsbase.h>
#include <asm/instr/movzxq.h>
#include <asm/param.h>
#include <kos/kernel/cpu-state-asm.h>
#include <kos/kernel/cpu-state.h>


.section .text
INTERN_FUNCTION(x86_idt_apic_spurious)
	.cfi_startproc simple
	.cfi_iret_signal_frame
	.cfi_def_cfa %rsp, 0
	intr_enter INTR

	pushq_cfi_r %rax    /* [C] Accumulator register */
	pushq_cfi_r %rcx    /* [C] Count register */
	pushq_cfi_r %rdx    /* [C] Data register */
	pushq_cfi_r %rsi    /* [C] Source pointer */
	pushq_cfi_r %rdi    /* [C] Destination pointer */
	pushq_cfi_r %r8     /* [C] General purpose register #8 */
	pushq_cfi_r %r9     /* [C] General purpose register #9 */
	pushq_cfi_r %r10    /* [C] General purpose register #10 */
	pushq_cfi_r %r11    /* [C] General purpose register #11 */

	EXTERN(x86_apic_spur)
	call   x86_apic_spur
	EXTERN(x86_lapicbase)
	movq   x86_lapicbase, %rax
	movl   $(APIC_EOI_FSIGNAL), APIC_EOI(%rax)

	popq_cfi_r %r11     /* [C] General purpose register #11 */
	popq_cfi_r %r10     /* [C] General purpose register #10 */
	popq_cfi_r %r9      /* [C] General purpose register #9 */
	popq_cfi_r %r8      /* [C] General purpose register #8 */
	popq_cfi_r %rdi     /* [C] Destination pointer */
	popq_cfi_r %rsi     /* [C] Source pointer */
	popq_cfi_r %rdx     /* [C] Data register */
	popq_cfi_r %rcx     /* [C] Count register */
	popq_cfi_r %rax     /* [C] Accumulator register */

	intr_exit intr_enabled=0
	.cfi_endproc
END(x86_idt_apic_spurious)


.section .rodata.free
INTERN_FUNCTION(x86_ack_apic)
	EXTERN(x86_lapicbase)
	movq   x86_lapicbase, %rax
	movl   $(APIC_EOI_FSIGNAL), APIC_EOI(%rax)
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
	.cfi_def_cfa %rsp, 0
	intr_enter INTR

	/* Construct a full `struct scpustate' structure */
	ASM_PUSH_SCPUSTATE_AFTER_IRET_CFI_R

	/* Acknowledge the interrupt. */
INTERN_FUNCTION(x86_pic_acknowledge)
	.rept  x86_ack_apic_size
	.byte  0x90
	.endr
END(x86_pic_acknowledge)

	movq   %gs:0, %rsi          /* cpu_scheduler_interrupt::struct task *__restrict thread */
	EXTERN(this_sched_state)
	movq   %rsp, this_sched_state(%rsi)
	EXTERN(this_cpu)
	movq   this_cpu(%rsi), %rbx /* THIS_CPU */
	movq   %rbx, %rdi           /* cpu_scheduler_interrupt::struct cpu *__restrict caller */

	/* Invoke the C-level interrupt implementation. */
	EXTERN(cpu_scheduler_interrupt)
	call   cpu_scheduler_interrupt

	/* Set the task returned by `cpu_scheduler_interrupt()'
	 * as the new current one. */
	EXTERN(thiscpu_current)
	movq   %rax, thiscpu_current(%rbx)

INTERN_FUNCTION(x86_load_thread_rax_cpu_rbx)
	EXTERN(this_sched_state)
	movq   this_sched_state(%rax), %rsp

	/* Load other scheduler-related register values. */
	EXTERN(this_x86_kernel_psp0)
	movq   this_x86_kernel_psp0(%rax), %rcx
	EXTERN(thiscpu_x86_tss)
	movq   %rcx, thiscpu_x86_tss + OFFSET_TSS_RSP0(%rbx)

#ifndef CONFIG_NO_FPU
	/* Disable the FPU, preparing it to be loaded lazily. */
	movq   %cr0, %rcx
	andq   $~CR0_TS, %rcx
	EXTERN(thiscpu_x86_fputhread)
	movq   thiscpu_x86_fputhread(%rbx), %rdx
	cmpq   %rdx, %rax
	je     1f
	/* Only disable if the target thread isn't holding the active FPU-context */
	orq    $(CR0_TS), %rcx
1:	movq   %rcx, %cr0
#endif /* !CONFIG_NO_FPU */

	/* Check if the old thread had its I/O permissions bitmap loaded. */
	EXTERN(thiscpu_x86_ioperm_bitmap)
	cmpq   $(0), thiscpu_x86_ioperm_bitmap(%rbx)
	jnz    .Llazy_disable_ioperm_bitmap
.Llazy_disable_ioperm_bitmap_return:

	.cfi_remember_state

	/* Update the used page directory pointer. */
	EXTERN(this_vm)
	movq   this_vm(%rax), %rcx
	EXTERN(thisvm_pdir_phys_ptr)
	movq   thisvm_pdir_phys_ptr(%rcx), %rdi
	movq   %cr3, %rdx
	cmpq   %rdx, %rdi
	je     1f
	movq   %rdi, %cr3
	/* Reload debug registers */
	reload_x86_debug_registers %rcx, %rdi, %rsi, 1
1:

.Lload_scpustate_rsp_gsbase_rax:
	/* Load segment registers. */
	ASM_POP_SGREGS_CFI_R(%rcx)

	/* Update the kernel TLS pointer.
	 * NOTE: This must be done _after_ segment registers were loaded,
	 *       as the use of `ASM_POP_SGREGS_CFI_R()' clobbered %gs.base! */
	wrgsbaseq %rax

	/* Load fsbase and kgsbase */
	ASM_POP_SGBASE_CFI_R

	/* Load GP registers. */
	ASM_POP_GPREGSNSP_CFI_R

	/* Resume execution */
	intr_exit intr_enabled=0
	.cfi_restore_state

	/* Disable the I/O permissions bitmap. */
.Llazy_disable_ioperm_bitmap:
	/* Check if the loaded I/O permissions bitmap is the calling thread's */
	EXTERN(this_x86_ioperm_bitmap)
	movq   this_x86_ioperm_bitmap(%rax), %rdx
	EXTERN(thiscpu_x86_ioperm_bitmap)
	cmpq   %rdx, thiscpu_x86_ioperm_bitmap(%rbx)
	je     .Llazy_disable_ioperm_bitmap_return
	/* Must actually unmap the I/O permissions bitmap! */
	EXTERN(thiscpu_x86_iobnode_pagedir_identity)
	movq   thiscpu_x86_iobnode_pagedir_identity(%rbx), %rdx
	movl   $(P64_PAGE_FPREPARED), %ecx
	movq   $(0), thiscpu_x86_ioperm_bitmap(%rbx)
	movq   %rcx, 0x0(%rdx)
	movq   %rcx, 0x8(%rdx)
	jmp    .Llazy_disable_ioperm_bitmap_return
	.cfi_endproc
END(x86_load_thread_rax_cpu_rbx)
END(x86_idt_preemption)



#ifdef CONFIG_HAVE_DEBUGGER
.section .text.cold
INTERN_FUNCTION(x86_dbgidt_preemption) /* ISR_X86_f0 */
	.cfi_startproc simple
	.cfi_iret_signal_frame
	.cfi_def_cfa %rsp, 0
	intr_enter INTR
	pushq_cfi_r %rax
	/* Acknowledge the interrupt. */
INTERN_FUNCTION(x86_debug_pic_acknowledge)
	.rept  x86_ack_apic_size
	.byte  0x90
	.endr
END(x86_debug_pic_acknowledge)
	popq_cfi_r %rax
	intr_exit intr_enabled=0
	.cfi_endproc
END(x86_dbgidt_preemption)
#endif /* CONFIG_HAVE_DEBUGGER */



.section .text
PUBLIC_FUNCTION(task_pause)
	.cfi_startproc
#ifndef CONFIG_NO_SMP
	pause
#endif /* !CONFIG_NO_SMP */
	ret
	.cfi_endproc
END(task_pause)

PUBLIC_FUNCTION(task_yield)
	.cfi_startproc
	.cfi_signal_frame
	popq_cfi %rax
	.cfi_register %rip, %rax
	movq   %rsp, %rcx
	pushq_cfi $(SEGMENT_KERNEL_DATA) /* ir_ss */
	.cfi_rel_offset %ss, 0
	pushq_cfi %rcx                   /* ir_rsp */
	.cfi_rel_offset %rsp, 0
	pushfq_cfi_r                     /* ir_rflags */
	testq  $(EFLAGS_IF), 0(%rsp)
	.cfi_remember_state
	jz     .Lillegal_task_yield
	pushq_cfi $(SEGMENT_KERNEL_CODE) /* ir_cs */
	.cfi_rel_offset %cs, 0
	pushq_cfi %rax                   /* ir_rip */
	.cfi_rel_offset %rip, 0

INTERN_FUNCTION(X86_ASMSYSCALL64(sched_yield))
	/* Construct a full `struct scpustate' structure */
	ASM_PUSH_SCPUSTATE_AFTER_IRET_CFI_R

	/* Remember the current scheduler state. */
	movq   %gs:0, %rbx
	cli
	EXTERN(this_sched_runnxt)
	movq   this_sched_runnxt(%rbx), %rbp
	cmpq   %rbx, %rbp
	je     .Lyield_same_target
.Ldo_task_yield_rbx_to_rbp:

	/* Check for a scheduling override. */
	EXTERN(this_cpu)
	movq   this_cpu(%rbx), %rcx
	EXTERN(thiscpu_override)
	cmpq   $(0), thiscpu_override(%rcx)
	jne    .Lyield_same_target_with_override

	/* CURR: %rbx */
	/* NEXT: %rbp*/
	EXTERN(this_sched_state)
	movq   %rsp, this_sched_state(%rbx)

	/* Prematurely end the current quantum */
	EXTERN(cpu_quantum_end)
	call   cpu_quantum_end

	/* Load the new CPU state */
	EXTERN(this_cpu)
	movq   this_cpu(%rbx), %rbx
	EXTERN(thiscpu_current)
	movq   %rbp, thiscpu_current(%rbx)
	movq   %rbp, %rax
	jmp    x86_load_thread_rax_cpu_rbx
.Lyield_same_target_with_override:
#ifndef NDEBUG
	EXTERN(thiscpu_override)
	cmpq   %rbx, thiscpu_override(%rcx)
	je     .Lyield_same_target
	int3   /* Assertion failed: CPU override does not match calling thread.
	        * >> struct task *caller = %rbx;
	        * >> struct cpu  *mycpu  = %rcx; */
#endif /* !NDEBUG */
.Lyield_same_target:
#ifndef CONFIG_NO_SMP
	sti
	movq   %rbx, %rax
	pause
	cli
#else /* !CONFIG_NO_SMP */
	movq   %rbx, %rax
#endif /* CONFIG_NO_SMP */
	jmp    .Lload_scpustate_rsp_gsbase_rax
	.cfi_restore_state
.Lillegal_task_yield:
	movq   $(ERROR_CODEOF(E_WOULDBLOCK_PREEMPTED)), %rdi
	EXTERN(error_throw)
	call   error_throw
END(X86_ASMSYSCALL64(sched_yield))
END(task_yield)
.cfi_endproc

DEFINE_PUBLIC_ALIAS(sys_sched_yield, task_yield)

/* sched_yield() is has an identical implementation in compatibility mode */
DEFINE_INTERN_ALIAS(X86_ASMSYSCALL32_SYSENTER(sched_yield), X86_ASMSYSCALL64(sched_yield))
DEFINE_INTERN_ALIAS(X86_ASMSYSCALL32_INT80(sched_yield), X86_ASMSYSCALL64(sched_yield))





.section .text
PUBLIC_FUNCTION(task_yield_nx)
	.cfi_startproc
	.cfi_signal_frame
	popq_cfi %rax
	.cfi_register %rip, %rax
	movq   %rsp, %rcx
	pushq_cfi $(SEGMENT_KERNEL_DATA) /* ir_ss */
	.cfi_rel_offset %ss, 0
	pushq_cfi %rcx                   /* ir_rsp */
	.cfi_rel_offset %rsp, 0
	pushfq_cfi_r                     /* ir_rflags */
	testq  $(EFLAGS_IF), 0(%rsp)
	.cfi_remember_state
	jz     .Lillegal_task_yield_nx
	pushq_cfi $(SEGMENT_KERNEL_CODE) /* ir_cs */
	.cfi_rel_offset %cs, 0
	pushq_cfi %rax                   /* ir_rip */
	.cfi_rel_offset %rip, 0

	/* Construct a full `struct scpustate' structure */
	pushq_cfi $(1)                   /* [C] Accumulator register */
	.cfi_rel_offset %rax, 0 /* Eventually, we want to return true. */
	ASM_PUSH_GPREGSNSP_NORAX_CFI_R
	ASM_PUSH_SGBASE_CFI_R
	ASM_PUSH_SGREGS_CFI_R(%rax)

	/* Remember the current scheduler state. */
	movq   %gs:0, %rbx
	cli
	EXTERN(this_sched_runnxt)
	movq   this_sched_runnxt(%rbx), %rbp
	cmpq   %rbx, %rbp
	je     .Lyield_same_target
	jmp    .Ldo_task_yield_rbx_to_rbp
	.cfi_restore_state
.Lillegal_task_yield_nx:
	addq   $(24), %rsp
	.cfi_adjust_cfa_offset -24
	movq   %rax, %rcx
	.cfi_register %rip, %rcx
	movq   $(0), %rax
	jmpq   *%rcx
	.cfi_endproc
END(task_yield_nx)



.section .text
PUBLIC_FUNCTION(task_tryyield_or_pause)
	.cfi_startproc
	.cfi_signal_frame
	popq_cfi %rcx
	.cfi_register %rip, %rcx
	movq   %rsp, %rdx
	pushq_cfi $(SEGMENT_KERNEL_DATA) /* ir_ss */
	.cfi_rel_offset %ss, 0
	pushq_cfi %rdx                   /* ir_rsp */
	.cfi_rel_offset %rsp, 0
	pushfq_cfi_r                     /* ir_rflags */
	testq  $(EFLAGS_IF), 0(%rsp)
	jnz    1f
	addq   $(24), %rsp
	.cfi_adjust_cfa_offset -24
	.cfi_same_value %rflags
	movq   $(TASK_TRYYIELD_PREEMPTION_DISABLED), %rax
#ifndef CONFIG_NO_SMP
	pause
#endif /* !CONFIG_NO_SMP */
	jmpq   *%rcx
END(task_tryyield_or_pause)
	.cfi_adjust_cfa_offset 8
	.cfi_restore %rip
PUBLIC_FUNCTION(task_tryyield)
	popq_cfi %rcx
	.cfi_register %rip, %rcx
	movq   %rsp, %rdx
	pushq_cfi $(SEGMENT_KERNEL_DATA) /* ir_ss */
	.cfi_rel_offset %ss, 0
	pushq_cfi %rdx                   /* ir_rsp */
	.cfi_rel_offset %rsp, 0
	pushfq_cfi_r                     /* ir_rflags */
	testq  $(EFLAGS_IF), 0(%rsp)
	jnz    1f
	addq   $(24), %rsp
	.cfi_adjust_cfa_offset -24
	.cfi_same_value %rflags
	movq   $(TASK_TRYYIELD_PREEMPTION_DISABLED), %rax
#ifndef CONFIG_NO_SMP
	pause
#endif /* !CONFIG_NO_SMP */
	jmpq   *%rcx
1:	.cfi_adjust_cfa_offset 24
	.cfi_rel_offset %eflags, 0
	pushq_cfi $(SEGMENT_KERNEL_CODE) /* ir_cs */
	.cfi_rel_offset %cs, 0
	pushq_cfi %rcx                   /* ir_rip */
	.cfi_rel_offset %rip, 0

	/* Construct a full `struct scpustate' structure */
	pushq_cfi $(TASK_TRYYIELD_SUCCESS) /* [C] Accumulator register */
	.cfi_rel_offset %rax, 0
	ASM_PUSH_GPREGSNSP_NORAX_CFI_R
	ASM_PUSH_SGBASE_CFI_R
	ASM_PUSH_SGREGS_CFI_R(%rax)

	/* Remember the current scheduler state. */
	movq   %gs:0, %rbx
	cli
	EXTERN(this_sched_runnxt)
	movq   this_sched_runnxt(%rbx), %rbp
	cmpq   %rbx, %rbp
	jne    .Ldo_task_yield_rbx_to_rbp
#ifndef CONFIG_NO_SMP
	sti
#endif /* !CONFIG_NO_SMP */

	/* Same target... */
	movq   $(TASK_TRYYIELD_NO_SUCCESSOR), (OFFSET_SCPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_RAX)(%rsp)
#ifndef CONFIG_NO_SMP
	pause
#endif /* !CONFIG_NO_SMP */
	movq   %rbx, %rax
#ifndef CONFIG_NO_SMP
	cli
#endif /* !CONFIG_NO_SMP */
	jmp    .Lload_scpustate_rsp_gsbase_rax
	.cfi_endproc
END(task_tryyield)



.section .text
PUBLIC_FUNCTION(cpu_run_current_and_remember)
	/* %rdi: <struct task *__restrict caller> */
	.cfi_startproc
	.cfi_signal_frame
	popq_cfi %rax
	.cfi_register %rip, %rax
	movq   %rsp, %rcx
	pushq_cfi $(SEGMENT_KERNEL_DATA) /* ir_ss */
	.cfi_rel_offset %ss, 0
	pushq_cfi %rcx                   /* ir_rsp */
	.cfi_rel_offset %rsp, 0
	pushfq_cfi_r                     /* ir_rflags */
	orq    $(EFLAGS_IF), (%rsp)
	pushq_cfi $(SEGMENT_KERNEL_CODE) /* ir_cs */
	.cfi_rel_offset %cs, 0
	pushq_cfi %rax                   /* ir_rip */
	.cfi_rel_offset %rip, 0

	/* Construct a full `struct scpustate' structure */
	ASM_PUSH_SCPUSTATE_AFTER_IRET_CFI_R

	/* Remember the current scheduler state. */
	EXTERN(this_sched_state)
	movq   %rsp, this_sched_state(%rdi)
	EXTERN(this_cpu)
	movq   this_cpu(%rdi), %rbx

	/* Load the new CPU state */
	EXTERN(thiscpu_current)
	movq   thiscpu_current(%rbx), %rax
	EXTERN(x86_load_thread_rax_cpu_rbx)
	jmp    x86_load_thread_rax_cpu_rbx
	.cfi_endproc
END(cpu_run_current_and_remember)

.section .text
PUBLIC_FUNCTION(cpu_run_current)
	.cfi_startproc
	/* Load the CPU state of the task set as current. */
	movq   %gs:0, %rax
	EXTERN(this_cpu)
	movq   this_cpu(%rax), %rbx
	EXTERN(thiscpu_current)
	movq   thiscpu_current(%rbx), %rax
	EXTERN(x86_load_thread_rax_cpu_rbx)
	jmp    x86_load_thread_rax_cpu_rbx
	.cfi_endproc
END(cpu_run_current)



.section .text.free
INTERN_FUNCTION(x86_apic_cpu_quantum_elapsed)
	pushfq
	EXTERN(x86_lapicbase)
	movq   x86_lapicbase, %rcx
	EXTERN(this_cpu)
	movq   %gs:this_cpu, %rax
	cli
	movzlq APIC_TIMER_CURRENT(%rcx), %rcx
	EXTERN(thiscpu_quantum_length)
	movzlq thiscpu_quantum_length(%rax), %rax
	popfq
	subq   %rcx, %rax
	ret
INTERN_CONST(x86_apic_cpu_quantum_elapsed_size, . - x86_apic_cpu_quantum_elapsed)
END(x86_apic_cpu_quantum_elapsed)

INTERN_FUNCTION(x86_apic_cpu_quantum_elapsed_nopr)
	EXTERN(x86_lapicbase)
	movq   x86_lapicbase, %rcx
	EXTERN(this_cpu)
	movq   %gs:this_cpu, %rax
	movzlq APIC_TIMER_CURRENT(%rcx), %rcx
	EXTERN(thiscpu_quantum_length)
	movzlq thiscpu_quantum_length(%rax), %rax
	subq   %rcx, %rax
	ret
INTERN_CONST(x86_apic_cpu_quantum_elapsed_size_nopr, . - x86_apic_cpu_quantum_elapsed_nopr)
END(x86_apic_cpu_quantum_elapsed_nopr)

INTERN_FUNCTION(x86_apic_cpu_quantum_remaining)
	pushfq
	EXTERN(x86_lapicbase)
	movq   x86_lapicbase, %rax
	cli
	movzlq APIC_TIMER_CURRENT(%rax), %rax
	popfq
	ret
INTERN_CONST(x86_apic_cpu_quantum_remaining_size, . - x86_apic_cpu_quantum_remaining)
END(x86_apic_cpu_quantum_remaining)

INTERN_FUNCTION(x86_apic_cpu_quantum_remaining_nopr)
	EXTERN(x86_lapicbase)
	movq   x86_lapicbase, %rax
	movzlq APIC_TIMER_CURRENT(%rax), %rax
	ret
INTERN_CONST(x86_apic_cpu_quantum_remaining_size_nopr, . - x86_apic_cpu_quantum_remaining_nopr)
END(x86_apic_cpu_quantum_remaining_nopr)

INTERN_FUNCTION(x86_apic_cpu_disable_preemptive_interrupts)
	pushfq
	EXTERN(x86_lapicbase)
	movq   x86_lapicbase, %rcx
	cli
	/* lapic_write(APIC_TIMER, APIC_TIMER_FDISABLED); */
	movl   $(APIC_TIMER_FDISABLED), APIC_TIMER(%rcx)
	popfq
	ret
INTERN_CONST(x86_apic_cpu_disable_preemptive_interrupts_size, . - x86_apic_cpu_disable_preemptive_interrupts)
END(x86_apic_cpu_disable_preemptive_interrupts)

INTERN_FUNCTION(x86_apic_cpu_disable_preemptive_interrupts_nopr)
	EXTERN(x86_lapicbase)
	movq   x86_lapicbase, %rcx
	/* lapic_write(APIC_TIMER, APIC_TIMER_FDISABLED); */
	movl   $(APIC_TIMER_FDISABLED), APIC_TIMER(%rcx)
	ret
INTERN_CONST(x86_apic_cpu_disable_preemptive_interrupts_size_nopr, . - x86_apic_cpu_disable_preemptive_interrupts_nopr)
END(x86_apic_cpu_disable_preemptive_interrupts_nopr)

INTERN_FUNCTION(x86_apic_cpu_enable_preemptive_interrupts)
	pushfq
	EXTERN(this_cpu)
	movq   %gs:this_cpu, %rax
	EXTERN(x86_lapicbase)
	movq   x86_lapicbase, %rcx
	cli
	EXTERN(thiscpu_quantum_length)
	movl   thiscpu_quantum_length(%rax), %eax
	/* lapic_write(APIC_TIMER_DIVIDE, APIC_TIMER_DIVIDE_F16); */
	movl   $(APIC_TIMER_DIVIDE_F16), APIC_TIMER_DIVIDE(%rcx)
	/* lapic_write(APIC_TIMER,
	 *             // Set the PIT interrupt to the APIC timer.
	 *             X86_INTNO_PIC1_PIT |
	 *             APIC_TIMER_MODE_FPERIODIC |
	 *             APIC_TIMER_SOURCE_FDIV); */
	movl   $(X86_INTNO_PIC1_PIT | APIC_TIMER_MODE_FPERIODIC | APIC_TIMER_SOURCE_FDIV), \
	       APIC_TIMER(%rcx)
	/* lapic_write(APIC_TIMER_INITIAL,PERCPU(thiscpu_quantum_length)); */
	movl   %eax, APIC_TIMER_INITIAL(%rcx)
	popfq
	ret
INTERN_CONST(x86_apic_cpu_enable_preemptive_interrupts_size, . - x86_apic_cpu_enable_preemptive_interrupts)
END(x86_apic_cpu_enable_preemptive_interrupts)

INTERN_FUNCTION(x86_apic_cpu_enable_preemptive_interrupts_nopr)
	EXTERN(this_cpu)
	movq   %gs:this_cpu, %rax
	EXTERN(x86_lapicbase)
	movq   x86_lapicbase, %rcx
	EXTERN(thiscpu_quantum_length)
	movl   thiscpu_quantum_length(%rax), %eax
	/* lapic_write(APIC_TIMER_DIVIDE, APIC_TIMER_DIVIDE_F16); */
	movl   $(APIC_TIMER_DIVIDE_F16), APIC_TIMER_DIVIDE(%rcx)
	/* lapic_write(APIC_TIMER,
	 *             // Set the PIT interrupt to the APIC timer.
	 *             X86_INTNO_PIC1_PIT |
	 *             APIC_TIMER_MODE_FPERIODIC |
	 *             APIC_TIMER_SOURCE_FDIV); */
	movl   $(X86_INTNO_PIC1_PIT | APIC_TIMER_MODE_FPERIODIC | APIC_TIMER_SOURCE_FDIV), \
	       APIC_TIMER(%rcx)
	/* lapic_write(APIC_TIMER_INITIAL, PERCPU(thiscpu_quantum_length)); */
	movl   %eax, APIC_TIMER_INITIAL(%rcx)
	ret
INTERN_CONST(x86_apic_cpu_enable_preemptive_interrupts_size_nopr, . - x86_apic_cpu_enable_preemptive_interrupts_nopr)
END(x86_apic_cpu_enable_preemptive_interrupts_nopr)

INTERN_FUNCTION(x86_apic_cpu_quantum_reset)
	pushfq
	EXTERN(this_cpu)
	movq   %gs:this_cpu, %rax
	EXTERN(x86_lapicbase)
	movq   x86_lapicbase, %rcx
	cli
	EXTERN(thiscpu_quantum_length)
	movl   thiscpu_quantum_length(%rax), %eax
	/* lapic_write(APIC_TIMER_CURRENT, PERCPU(thiscpu_quantum_length)); */
	movl   %eax, APIC_TIMER_CURRENT(%rcx)
	popfq
	ret
INTERN_CONST(x86_apic_cpu_quantum_reset_size, . - x86_apic_cpu_quantum_reset)
END(x86_apic_cpu_quantum_reset)

INTERN_FUNCTION(x86_apic_cpu_quantum_reset_nopr)
	EXTERN(this_cpu)
	movq   %gs:this_cpu, %rax
	EXTERN(x86_lapicbase)
	movq   x86_lapicbase, %rcx
	EXTERN(thiscpu_quantum_length)
	movl   thiscpu_quantum_length(%rax), %eax
	/* lapic_write(APIC_TIMER_CURRENT, PERCPU(thiscpu_quantum_length)); */
	movl   %eax, APIC_TIMER_CURRENT(%rcx)
	ret
INTERN_CONST(x86_apic_cpu_quantum_reset_size_nopr, . - x86_apic_cpu_quantum_reset_nopr)
END(x86_apic_cpu_quantum_reset_nopr)

INTERN_FUNCTION(x86_apic_cpu_ipi_pending)
	/* u32 mask = lapic_read(APIC_ISR(APIC_ISR_INDEX(X86_INTERRUPT_APIC_IPI))); */
	/* return (mask & APIC_ISR_MASK(X86_INTERRUPT_APIC_IPI)) != 0; */
	xorq   %rax, %rax
	EXTERN(x86_lapicbase)
	movq   x86_lapicbase, %rcx
	movl   APIC_ISR(APIC_ISR_INDEX(X86_INTERRUPT_APIC_IPI))(%rcx), %ecx
	testl  $(APIC_ISR_MASK(X86_INTERRUPT_APIC_IPI)), %ecx
	setnz  %al
	ret
INTERN_CONST(x86_apic_cpu_ipi_pending_size, . - x86_apic_cpu_ipi_pending)
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
	movzwq %cx, %rax
	ret
.if x86_apic_cpu_quantum_remaining_size_nopr > (. - cpu_quantum_remaining_nopr)
.skip x86_apic_cpu_quantum_remaining_size_nopr - (. - cpu_quantum_remaining_nopr), 0x90
.endif
END(cpu_quantum_remaining_nopr)


PUBLIC_FUNCTION(cpu_quantum_remaining)
	pushfq
	cli
	/* Read the current PIT counter position. */
	movb   $(PIT_COMMAND_SELECT_F0 | \
	         PIT_COMMAND_ACCESS_FLATCH | \
	         PIT_COMMAND_FBINARY), %al
	outb   %al,  $(PIT_COMMAND)
	inb    $(PIT_DATA0),     %al
	movb   %al, %cl
	inb    $(PIT_DATA0),     %al
	popfq
	movb   %al, %ch
	movzwq %cx, %rax
	ret
.if x86_apic_cpu_quantum_remaining_size > (. - cpu_quantum_remaining)
.skip x86_apic_cpu_quantum_remaining_size - (. - cpu_quantum_remaining), 0x90
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
	movq   $PIT_HZ_DIV(HZ), %rax
	subw   %cx, %ax
	ret
.if x86_apic_cpu_quantum_elapsed_size_nopr > (. - cpu_quantum_elapsed_nopr)
.skip x86_apic_cpu_quantum_elapsed_size_nopr - (. - cpu_quantum_elapsed_nopr), 0x90
.endif
END(cpu_quantum_elapsed_nopr)

PUBLIC_FUNCTION(cpu_quantum_elapsed)
	pushfq
	movb   $(PIT_COMMAND_SELECT_F0 | \
	         PIT_COMMAND_ACCESS_FLATCH | \
	         PIT_COMMAND_FBINARY), %al
	cli
	/* Read the current PIT counter position. */
	outb   %al,  $(PIT_COMMAND)
	inb    $(PIT_DATA0),     %al
	movb   %al, %cl
	inb    $(PIT_DATA0),     %al
	popfq
	movb   %al, %ch
	movq   $PIT_HZ_DIV(HZ), %rax
	subw   %cx, %ax
	ret
.if x86_apic_cpu_quantum_elapsed_size > (. - cpu_quantum_elapsed)
.skip x86_apic_cpu_quantum_elapsed_size - (. - cpu_quantum_elapsed), 0x90
.endif
END(cpu_quantum_elapsed)


INTERN_FUNCTION(x86_cpu_disable_preemptive_interrupts)
	pushfq
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
	popfq
	ret
.if x86_apic_cpu_disable_preemptive_interrupts_size > (. - x86_cpu_disable_preemptive_interrupts)
.skip x86_apic_cpu_disable_preemptive_interrupts_size - (. - x86_cpu_disable_preemptive_interrupts), 0x90
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
.skip x86_apic_cpu_disable_preemptive_interrupts_size_nopr - (. - x86_cpu_disable_preemptive_interrupts_nopr), 0x90
.endif
END(x86_cpu_disable_preemptive_interrupts_nopr)

INTERN_FUNCTION(x86_cpu_enable_preemptive_interrupts)
	pushfq
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
	popfq
	ret
.if x86_apic_cpu_enable_preemptive_interrupts_size > (. - x86_cpu_enable_preemptive_interrupts)
.skip x86_apic_cpu_enable_preemptive_interrupts_size - (. - x86_cpu_enable_preemptive_interrupts), 0x90
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
.skip x86_apic_cpu_enable_preemptive_interrupts_size_nopr - (. - x86_cpu_enable_preemptive_interrupts_nopr), 0x90
.endif
END(x86_cpu_enable_preemptive_interrupts_nopr)


PUBLIC_FUNCTION(cpu_quantum_reset)
	pushfq
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
	popfq
	ret
.if x86_apic_cpu_quantum_reset_size > (. - cpu_quantum_reset)
.skip x86_apic_cpu_quantum_reset_size - (. - cpu_quantum_reset), 0x90
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
.skip x86_apic_cpu_quantum_reset_size_nopr - (. - cpu_quantum_reset_nopr), 0x90
.endif
END(cpu_quantum_reset_nopr)


PUBLIC_FUNCTION(cpu_hwipi_pending)
	/* outb(X86_PIC1_CMD, X86_PIC_READ_IRR) */
	pushfq
	movq   $(X86_PIC_READ_IRR), %rax /* NOTE: This also clears all of the upper bits! */
	cli
	outb   %al, $(X86_PIC1_CMD)
	/* AL = inb(X86_PIC1_CMD) */
	inb    $(X86_PIC2_CMD), %al
	popfq
	/* return PIT_BIT_IS_SET(AL); */
	testb  $(1 << (X86_INTNO_PIC1_PIT-X86_INTERRUPT_PIC1_BASE)), %al
	setnz  %al
	ret
.if x86_apic_cpu_ipi_pending_size > (. - cpu_hwipi_pending)
.skip x86_apic_cpu_ipi_pending_size - (. - cpu_hwipi_pending), 0x90
.endif
END(cpu_hwipi_pending)

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_SCHED_SCHED64_S */
