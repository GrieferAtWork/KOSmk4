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
#include <asm/cpu-msr.h>
#include <asm/param.h>
#include <asm/instr/fsgsbase.h>
#include <asm/instr/interrupt.h>
#include <asm/instr/movzxq.h>


/* Push `IA32_KERNEL_GS_BASE' onto the stack
 * This macro clobbers %rax, %rcx and %rdx */
.macro pushq_cfi_kernel_gs_base
	subq   $8, %rsp
	.cfi_adjust_cfa_offset 8
	movl   $(IA32_KERNEL_GS_BASE), %ecx
	rdmsr
	movl   %eax, 0(%rsp)
	movl   %edx, 4(%rsp)
.endm


/* Pop `IA32_KERNEL_GS_BASE' onto the stack
 * This macro clobbers %rax, %rcx and %rdx */
.macro popq_cfi_kernel_gs_base
	movl   $(IA32_KERNEL_GS_BASE), %ecx
	movl   0(%rsp), %eax
	movl   4(%rsp), %edx
	wrmsr
	addq   $8, %rsp
	.cfi_adjust_cfa_offset -8
.endm


.section .text
INTERN_FUNCTION(x86_asmirq_ef)
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

	call   x86_apic_spur
	movq   x86_lapic_base_address, %rax
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

	intr_exit
	.cfi_endproc
END(x86_asmirq_ef)


INTERN(cpu_scheduler_interrupt)

/* The PIT interrupt handler -- Used for scheduling.
 * NOTE: If available, this interrupt will actually be fired by the LAPIC */
.section .text
INTERN_FUNCTION(x86_asmirq_f0)
	.cfi_startproc simple
	.cfi_iret_signal_frame
	.cfi_def_cfa %rsp, 0
	intr_enter INTR

	/* Construct a full `struct scpustate' structure */
	pushq_cfi_r %rax                 /* [C] Accumulator register */
	pushq_cfi_r %rcx                 /* [C] Count register */
	pushq_cfi_r %rdx                 /* [C] Data register */
	pushq_cfi_r %rbx                 /* [P] Base register */
	pushq_cfi_r %rbp                 /* [P] Frame base pointer */
	pushq_cfi_r %rsi                 /* [C] Source pointer */
	pushq_cfi_r %rdi                 /* [C] Destination pointer */
	pushq_cfi_r %r8                  /* [C] General purpose register #8 */
	pushq_cfi_r %r9                  /* [C] General purpose register #9 */
	pushq_cfi_r %r10                 /* [C] General purpose register #10 */
	pushq_cfi_r %r11                 /* [C] General purpose register #11 */
	pushq_cfi_r %r12                 /* [P] General purpose register #12 */
	pushq_cfi_r %r13                 /* [P] General purpose register #13 */
	pushq_cfi_r %r14                 /* [P] General purpose register #14 */
	pushq_cfi_r %r15                 /* [P] General purpose register #15 */
	pushq_seg_cfi_r %ds, %rax
	pushq_seg_cfi_r %es, %rax
	pushq_cfi_r %fs
	pushq_cfi_r %gs
	pushq_seg_cfi_r %fs.base, %rax
	pushq_cfi_kernel_gs_base

	/* Acknowledge the interrupt. */
INTERN_FUNCTION(x86_pic_acknowledge)
	.byte  0x90, 0x90, 0x90, 0x90, 0x90
	.byte  0x90, 0x90, 0x90, 0x90, 0x90
	.byte  0x90, 0x90, 0x90, 0x90, 0x90
	.byte  0x90, 0x90, 0x90
END(x86_pic_acknowledge)

	movq   %gs:0, %rdi           /* cpu_scheduler_interrupt::struct task *__restrict thread */
	movq   %rsp, _this_sched_state(%rdi)
	movq   _this_cpu(%rdi), %rbx /* THIS_CPU */
	movq   %rbx, %rcx            /* cpu_scheduler_interrupt::struct cpu *__restrict caller */

	/* Invoke the C-level interrupt implementation. */
	call   cpu_scheduler_interrupt

	/* Set the task returned by `cpu_scheduler_interrupt()'
	 * as the new current one. */
	movq   %rax, _this_cpu_current(%rbx)
INTERN_FUNCTION(x86_load_thread_rax_cpu_rbx)
	movq   _this_sched_state(%rax), %rsp

	/* Load other scheduler-related register values. */
	movq   x86_this_kernel_sp0(%rax), %rcx
	movq   %rcx, x86_cputss + OFFSET_TSS_RSP0(%rbx)

	/* Update the kernel TLS pointer. */
	wrgsbaseq %rax

#ifndef CONFIG_NO_FPU
	/* Disable the FPU, preparing it to be loaded lazily. */
	movq   %cr0, %rcx
	andq   $~CR0_TS, %rcx
	movq   x86_fpu_current(%rbx), %rdx
	cmpq   %rdx, %rax
	je     1f
	/* Only disable if the target thread isn't holding the active FPU-context */
	orq    $(CR0_TS), %rcx
1:	movq   %rcx, %cr0
#endif /* !CONFIG_NO_FPU */

	/* Update the used page directory pointer. */
	movq   _this_vm(%rax), %rcx
	movq   _this_vm_pdir_phys_ptr(%rcx), %rax
	movq   %cr3, %rdx
	cmpq   %rdx, %rax
	je     1f
	movq   %rax, %cr3
	/* Reload debug registers */
	reload_x86_debug_registers %rcx, %rax, %rdx, 1
1:

.Lload_scpustate_rsp:
	/* Load the underlying CPU state */
	popq_cfi_kernel_gs_base
	popq_seg_cfi_r %fs.base, %rax
	popq_cfi_r %gs
	popq_cfi_r %fs
	popq_seg_cfi_r %es, %rax
	popq_seg_cfi_r %ds, %rax
	popq_cfi_r %r15                 /* [P] General purpose register #15 */
	popq_cfi_r %r14                 /* [P] General purpose register #14 */
	popq_cfi_r %r13                 /* [P] General purpose register #13 */
	popq_cfi_r %r12                 /* [P] General purpose register #12 */
	popq_cfi_r %r11                 /* [C] General purpose register #11 */
	popq_cfi_r %r10                 /* [C] General purpose register #10 */
	popq_cfi_r %r9                  /* [C] General purpose register #9 */
	popq_cfi_r %r8                  /* [C] General purpose register #8 */
	popq_cfi_r %rdi                 /* [C] Destination pointer */
	popq_cfi_r %rsi                 /* [C] Source pointer */
	popq_cfi_r %rbp                 /* [P] Frame base pointer */
	popq_cfi_r %rbx                 /* [P] Base register */
	popq_cfi_r %rdx                 /* [C] Data register */
	popq_cfi_r %rcx                 /* [C] Count register */
	popq_cfi_r %rax                 /* [C] Accumulator register */

	intr_exit
	.cfi_endproc
END(x86_load_thread_rax_cpu_rbx)
END(x86_asmirq_f0)


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
	pushq_cfi_r %rax                 /* [C] Accumulator register */
	pushq_cfi_r %rcx                 /* [C] Count register */
	pushq_cfi_r %rdx                 /* [C] Data register */
	pushq_cfi_r %rbx                 /* [P] Base register */
	pushq_cfi_r %rbp                 /* [P] Frame base pointer */
	pushq_cfi_r %rsi                 /* [C] Source pointer */
	pushq_cfi_r %rdi                 /* [C] Destination pointer */
	pushq_cfi_r %r8                  /* [C] General purpose register #8 */
	pushq_cfi_r %r9                  /* [C] General purpose register #9 */
	pushq_cfi_r %r10                 /* [C] General purpose register #10 */
	pushq_cfi_r %r11                 /* [C] General purpose register #11 */
	pushq_cfi_r %r12                 /* [P] General purpose register #12 */
	pushq_cfi_r %r13                 /* [P] General purpose register #13 */
	pushq_cfi_r %r14                 /* [P] General purpose register #14 */
	pushq_cfi_r %r15                 /* [P] General purpose register #15 */
	pushq_seg_cfi_r %ds, %rax
	pushq_seg_cfi_r %es, %rax
	pushq_cfi_r %fs
	pushq_cfi_r %gs
	pushq_seg_cfi_r %fs.base, %rax
	pushq_cfi_kernel_gs_base


	/* Remember the current scheduler state. */
	movq   %gs:0, %rbx
	cli
	movq   _this_sched_runnxt(%rbx), %rbp
	cmpq   %rbx, %rbp
	je     .Lyield_same_target
.Ldo_task_yield_rbx_to_rbp:

	/* Check for a scheduling override. */
	movq   _this_cpu(%rbx), %rax
	cmpq   $0, _this_cpu_override(%rax)
	jne    .Lyield_same_target_with_override

	/* CURR: %rbx */
	/* NEXT: %rbp*/
	movq   %rsp, _this_sched_state(%rbx)

	/* Prematurely end the current quantum */
	call   cpu_quantum_end

	/* Load the new CPU state */
	movq   _this_cpu(%rbx), %rbx
	movq   %rbp, _this_cpu_current(%rbx)
	movq   %rbp, %rax
	jmp    x86_load_thread_rax_cpu_rbx
.Lyield_same_target_with_override:
#ifndef NDEBUG
	cmpq   %rbx, _this_cpu_override(%rax)
	je     .Lyield_same_target
	int3   /* Assertion failed: CPU override does not match calling thread.
	        * >> struct task *caller = %rbx;
	        * >> struct cpu  *mycpu = %rax; */
#endif /* !NDEBUG */
.Lyield_same_target:
	sti
#ifndef CONFIG_NO_SMP
	pause
#endif /* !CONFIG_NO_SMP */
	jmp    .Lload_scpustate_rsp
	.cfi_restore_state
.Lillegal_task_yield:
	movq   $(ERROR_CODEOF(E_WOULDBLOCK_PREEMPTED)), %rdi
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
	pushq_cfi   $1                   /* [C] Accumulator register */
	.cfi_rel_offset %rax, 0 /* Eventually, we want to return true. */
	pushq_cfi_r %rcx                 /* [C] Count register */
	pushq_cfi_r %rdx                 /* [C] Data register */
	pushq_cfi_r %rbx                 /* [P] Base register */
	pushq_cfi_r %rbp                 /* [P] Frame base pointer */
	pushq_cfi_r %rsi                 /* [C] Source pointer */
	pushq_cfi_r %rdi                 /* [C] Destination pointer */
	pushq_cfi_r %r8                  /* [C] General purpose register #8 */
	pushq_cfi_r %r9                  /* [C] General purpose register #9 */
	pushq_cfi_r %r10                 /* [C] General purpose register #10 */
	pushq_cfi_r %r11                 /* [C] General purpose register #11 */
	pushq_cfi_r %r12                 /* [P] General purpose register #12 */
	pushq_cfi_r %r13                 /* [P] General purpose register #13 */
	pushq_cfi_r %r14                 /* [P] General purpose register #14 */
	pushq_cfi_r %r15                 /* [P] General purpose register #15 */
	pushq_seg_cfi_r %ds, %rax
	pushq_seg_cfi_r %es, %rax
	pushq_cfi_r %fs
	pushq_cfi_r %gs
	pushq_seg_cfi_r %fs.base, %rax
	pushq_cfi_kernel_gs_base

	/* Remember the current scheduler state. */
	movq   %gs:0, %rbx
	cli
	movq   _this_sched_runnxt(%rbx), %rbp
	cmpq   %rbx, %rbp
	je     .Lyield_same_target
	jmp    .Ldo_task_yield_rbx_to_rbp
	.cfi_restore_state
.Lillegal_task_yield_nx:
	addq   $24, %rsp
	.cfi_adjust_cfa_offset -24
	movq   %rax, %rcx
	.cfi_register %rip, %rcx
	movq   $0, %rax
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
	addq   $24, %rsp
	.cfi_adjust_cfa_offset -24
	.cfi_same_value %rflags
	movq   $(TASK_TRYYIELD_PREEMPTION_DISABLED), %rax
#ifndef CONFIG_NO_SMP
	pause
#endif
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
	addq   $24, %rsp
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
	pushq_cfi   $(TASK_TRYYIELD_SUCCESS) /* [C] Accumulator register */
	.cfi_rel_offset %rax, 0
	pushq_cfi_r %rcx                 /* [C] Count register */
	pushq_cfi_r %rdx                 /* [C] Data register */
	pushq_cfi_r %rbx                 /* [P] Base register */
	pushq_cfi_r %rbp                 /* [P] Frame base pointer */
	pushq_cfi_r %rsi                 /* [C] Source pointer */
	pushq_cfi_r %rdi                 /* [C] Destination pointer */
	pushq_cfi_r %r8                  /* [C] General purpose register #8 */
	pushq_cfi_r %r9                  /* [C] General purpose register #9 */
	pushq_cfi_r %r10                 /* [C] General purpose register #10 */
	pushq_cfi_r %r11                 /* [C] General purpose register #11 */
	pushq_cfi_r %r12                 /* [P] General purpose register #12 */
	pushq_cfi_r %r13                 /* [P] General purpose register #13 */
	pushq_cfi_r %r14                 /* [P] General purpose register #14 */
	pushq_cfi_r %r15                 /* [P] General purpose register #15 */
	pushq_seg_cfi_r %ds, %rax
	pushq_seg_cfi_r %es, %rax
	pushq_cfi_r %fs
	pushq_cfi_r %gs
	pushq_seg_cfi_r %fs.base, %rax
	pushq_cfi_kernel_gs_base

	/* Remember the current scheduler state. */
	movq   %gs:0, %rbx
	cli
	movq   _this_sched_runnxt(%rbx), %rbp
	cmpq   %rbx, %rbp
	jne    .Ldo_task_yield_rbx_to_rbp
	sti

	/* Same target... */
	movq   $(TASK_TRYYIELD_NO_SUCCESSOR), OFFSET_SCPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_RAX(%esp)
#ifndef CONFIG_NO_SMP
	pause
#endif /* !CONFIG_NO_SMP */
	jmp    .Lload_scpustate_rsp
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
	pushq_cfi_r %rax                 /* [C] Accumulator register */
	pushq_cfi_r %rcx                 /* [C] Count register */
	pushq_cfi_r %rdx                 /* [C] Data register */
	pushq_cfi_r %rbx                 /* [P] Base register */
	pushq_cfi_r %rbp                 /* [P] Frame base pointer */
	pushq_cfi_r %rsi                 /* [C] Source pointer */
	pushq_cfi_r %rdi                 /* [C] Destination pointer */
	pushq_cfi_r %r8                  /* [C] General purpose register #8 */
	pushq_cfi_r %r9                  /* [C] General purpose register #9 */
	pushq_cfi_r %r10                 /* [C] General purpose register #10 */
	pushq_cfi_r %r11                 /* [C] General purpose register #11 */
	pushq_cfi_r %r12                 /* [P] General purpose register #12 */
	pushq_cfi_r %r13                 /* [P] General purpose register #13 */
	pushq_cfi_r %r14                 /* [P] General purpose register #14 */
	pushq_cfi_r %r15                 /* [P] General purpose register #15 */
	pushq_seg_cfi_r %ds, %rax
	pushq_seg_cfi_r %es, %rax
	pushq_cfi_r %fs
	pushq_cfi_r %gs
	pushq_seg_cfi_r %fs.base, %rax
	pushq_cfi_kernel_gs_base

	/* Remember the current scheduler state. */
	movq   %rsp, _this_sched_state(%rdi)
	movq   _this_cpu(%rdi), %rbx

	/* Load the new CPU state */
	movq   _this_cpu_current(%rbx), %rax
	jmp    x86_load_thread_rax_cpu_rbx
	.cfi_endproc
END(cpu_run_current_and_remember)

.section .text
PUBLIC_FUNCTION(cpu_run_current)
	.cfi_startproc
	/* Load the CPU state of the task set as current. */
	movq   %gs:0, %rax
	movq   _this_cpu(%rax), %rbx
	movq   _this_cpu_current(%rbx), %rax
	jmp    x86_load_thread_rax_cpu_rbx
	.cfi_endproc
END(cpu_run_current)



.section .text.free
INTERN_FUNCTION(x86_apic_cpu_quantum_elapsed)
	pushfq
	movq   x86_lapic_base_address, %rcx
	movq   %fs:_this_cpu, %rax
	cli
	movzlq APIC_TIMER_CURRENT(%rcx), %rcx
	movzlq cpu_quantum_length(%rax), %rax
	popfq
	subq   %rcx, %rax
	ret
INTERN(x86_apic_cpu_quantum_elapsed_size)
	x86_apic_cpu_quantum_elapsed_size = . - x86_apic_cpu_quantum_elapsed
END(x86_apic_cpu_quantum_elapsed)

INTERN_FUNCTION(x86_apic_cpu_quantum_elapsed_nopr)
	movq   x86_lapic_base_address, %rcx
	movq   %fs:_this_cpu, %rax
	movzlq APIC_TIMER_CURRENT(%rcx), %rcx
	movzlq cpu_quantum_length(%rax), %rax
	subq   %rcx, %rax
	ret
INTERN(x86_apic_cpu_quantum_elapsed_size_nopr)
	x86_apic_cpu_quantum_elapsed_size_nopr = . - x86_apic_cpu_quantum_elapsed_nopr
END(x86_apic_cpu_quantum_elapsed_nopr)

INTERN_FUNCTION(x86_apic_cpu_quantum_remaining)
	pushfq
	movq   x86_lapic_base_address, %rax
	cli
	movzlq APIC_TIMER_CURRENT(%rax), %rax
	popfq
	ret
INTERN(x86_apic_cpu_quantum_remaining_size)
	x86_apic_cpu_quantum_remaining_size = . - x86_apic_cpu_quantum_remaining
END(x86_apic_cpu_quantum_remaining)

INTERN_FUNCTION(x86_apic_cpu_quantum_remaining_nopr)
	movq   x86_lapic_base_address, %rax
	movzlq APIC_TIMER_CURRENT(%rax), %rax
	ret
INTERN(x86_apic_cpu_quantum_remaining_size_nopr)
	x86_apic_cpu_quantum_remaining_size_nopr = . - x86_apic_cpu_quantum_remaining_nopr
END(x86_apic_cpu_quantum_remaining_nopr)

INTERN_FUNCTION(x86_apic_cpu_disable_preemptive_interrupts)
	pushfq
	movq   x86_lapic_base_address, %rcx
	cli
	/* lapic_write(APIC_TIMER, APIC_TIMER_FDISABLED); */
	movl   $(APIC_TIMER_FDISABLED), APIC_TIMER(%rcx)
	popfq
	ret
INTERN(x86_apic_cpu_disable_preemptive_interrupts_size)
	x86_apic_cpu_disable_preemptive_interrupts_size = . - x86_apic_cpu_disable_preemptive_interrupts
END(x86_apic_cpu_disable_preemptive_interrupts)

INTERN_FUNCTION(x86_apic_cpu_disable_preemptive_interrupts_nopr)
	movq   x86_lapic_base_address, %rcx
	/* lapic_write(APIC_TIMER, APIC_TIMER_FDISABLED); */
	movl   $(APIC_TIMER_FDISABLED), APIC_TIMER(%rcx)
	ret
INTERN(x86_apic_cpu_disable_preemptive_interrupts_size_nopr)
	x86_apic_cpu_disable_preemptive_interrupts_size_nopr = . - x86_apic_cpu_disable_preemptive_interrupts_nopr
END(x86_apic_cpu_disable_preemptive_interrupts_nopr)

INTERN_FUNCTION(x86_apic_cpu_enable_preemptive_interrupts)
	pushfq
	movq   %fs:_this_cpu, %rax
	movq   x86_lapic_base_address, %rcx
	cli
	movl   cpu_quantum_length(%rax), %eax
	/* lapic_write(APIC_TIMER_DIVIDE, APIC_TIMER_DIVIDE_F16); */
	movl   $(APIC_TIMER_DIVIDE_F16), APIC_TIMER_DIVIDE(%rcx)
	/* lapic_write(APIC_TIMER,
	 *             // Set the PIT interrupt to the APIC timer.
	 *             X86_INTNO_PIC1_PIT |
	 *             APIC_TIMER_MODE_FPERIODIC |
	 *             APIC_TIMER_SOURCE_FDIV); */
	movl   $(X86_INTNO_PIC1_PIT | APIC_TIMER_MODE_FPERIODIC | APIC_TIMER_SOURCE_FDIV), \
	       APIC_TIMER(%rcx)
	/* lapic_write(APIC_TIMER_INITIAL,PERCPU(cpu_quantum_length)); */
	movl   %eax, APIC_TIMER_INITIAL(%rcx)
	popfq
	ret
INTERN(x86_apic_cpu_enable_preemptive_interrupts_size)
	x86_apic_cpu_enable_preemptive_interrupts_size = . - x86_apic_cpu_enable_preemptive_interrupts
END(x86_apic_cpu_enable_preemptive_interrupts)

INTERN_FUNCTION(x86_apic_cpu_enable_preemptive_interrupts_nopr)
	movq   %fs:_this_cpu, %rax
	movq   x86_lapic_base_address, %rcx
	movl   cpu_quantum_length(%rax), %eax
	/* lapic_write(APIC_TIMER_DIVIDE, APIC_TIMER_DIVIDE_F16); */
	movl   $(APIC_TIMER_DIVIDE_F16), APIC_TIMER_DIVIDE(%rcx)
	/* lapic_write(APIC_TIMER,
	 *             // Set the PIT interrupt to the APIC timer.
	 *             X86_INTNO_PIC1_PIT |
	 *             APIC_TIMER_MODE_FPERIODIC |
	 *             APIC_TIMER_SOURCE_FDIV); */
	movl   $(X86_INTNO_PIC1_PIT | APIC_TIMER_MODE_FPERIODIC | APIC_TIMER_SOURCE_FDIV), \
	       APIC_TIMER(%rcx)
	/* lapic_write(APIC_TIMER_INITIAL, PERCPU(cpu_quantum_length)); */
	movl   %eax, APIC_TIMER_INITIAL(%rcx)
	ret
INTERN(x86_apic_cpu_enable_preemptive_interrupts_size_nopr)
	x86_apic_cpu_enable_preemptive_interrupts_size_nopr = . - x86_apic_cpu_enable_preemptive_interrupts_nopr
END(x86_apic_cpu_enable_preemptive_interrupts_nopr)

INTERN_FUNCTION(x86_apic_cpu_quantum_reset)
	pushfq
	movq   %fs:_this_cpu, %rax
	movq   x86_lapic_base_address, %rcx
	cli
	movl   cpu_quantum_length(%rax), %eax
	/* lapic_write(APIC_TIMER_CURRENT, PERCPU(cpu_quantum_length)); */
	movl   %eax, APIC_TIMER_CURRENT(%rcx)
	popfq
	ret
INTERN(x86_apic_cpu_quantum_reset_size)
	x86_apic_cpu_quantum_reset_size = . - x86_apic_cpu_quantum_reset
END(x86_apic_cpu_quantum_reset)

INTERN_FUNCTION(x86_apic_cpu_quantum_reset_nopr)
	movq   %fs:_this_cpu, %rax
	movq   x86_lapic_base_address, %rcx
	movl   cpu_quantum_length(%rax), %eax
	/* lapic_write(APIC_TIMER_CURRENT, PERCPU(cpu_quantum_length)); */
	movl   %eax, APIC_TIMER_CURRENT(%rcx)
	ret
INTERN(x86_apic_cpu_quantum_reset_size_nopr)
	x86_apic_cpu_quantum_reset_size_nopr = . - x86_apic_cpu_quantum_reset_nopr
END(x86_apic_cpu_quantum_reset_nopr)

INTERN_FUNCTION(x86_apic_cpu_ipi_pending)
	/* u32 mask = lapic_read(APIC_ISR(APIC_ISR_INDEX(X86_INTERRUPT_APIC_IPI))); */
	/* return (mask & APIC_ISR_MASK(X86_INTERRUPT_APIC_IPI)) != 0; */
	xorq   %rax, %rax
	movq   x86_lapic_base_address, %rcx
	movl   APIC_ISR(APIC_ISR_INDEX(X86_INTERRUPT_APIC_IPI))(%rcx), %ecx
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
	movzwq %cx, %rax
	ret
.if x86_apic_cpu_quantum_remaining_size_nopr > (. - cpu_quantum_remaining_nopr)
.skip x86_apic_cpu_quantum_remaining_size_nopr - (. - cpu_quantum_remaining_nopr)
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
	movq   $PIT_HZ_DIV(HZ), %rax
	subw   %cx, %ax
	ret
.if x86_apic_cpu_quantum_elapsed_size_nopr > (. - cpu_quantum_elapsed_nopr)
.skip x86_apic_cpu_quantum_elapsed_size_nopr - (. - cpu_quantum_elapsed_nopr)
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
.skip x86_apic_cpu_quantum_elapsed_size - (. - cpu_quantum_elapsed)
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
.skip x86_apic_cpu_ipi_pending_size - (. - cpu_hwipi_pending)
.endif
END(cpu_hwipi_pending)




