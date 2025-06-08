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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_SCHED_SCHED_S
#define GUARD_KERNEL_CORE_ARCH_I386_SCHED_SCHED_S 1
#define __ASSEMBLER__ 1

#include <kernel/compiler.h>

#include <debugger/config.h>
#include <kernel/x86/syscall-tables.h>
#include <sched/cpu.h>
#include <sched/task.h>

#include <hybrid/host.h>

#include <cfi.h>
#include <asm/cpu-flags.h>
#include <asm/instr/compat.h>
#include <asm/instr/jccN.h>
#include <asm/instr/ttest.h>
#include <kos/except.h>
#include <kos/kernel/cpu-state-asm.h>
#include <kos/kernel/cpu-state.h>
#include <kos/kernel/x86/gdt.h>

#ifndef SIZEOF_POINTER
#define SIZEOF_POINTER __SIZEOF_POINTER__
#endif /* !SIZEOF_POINTER */

#ifdef __x86_64__
#define Ldo_yield_to_thread_Pax_cpu_Pbx Ldo_yield_to_thread_rax_cpu_rbx
#define x86_load_thread_Pax_cpu_Pbx     x86_load_thread_rax_cpu_rbx
#define libcpu_apply_scpustate_Psp      libcpu_apply_scpustate_rsp
#else /* __x86_64__ */
#define Ldo_yield_to_thread_Pax_cpu_Pbx Ldo_yield_to_thread_eax_cpu_ebx
#define x86_load_thread_Pax_cpu_Pbx     x86_load_thread_eax_cpu_ebx
#define libcpu_apply_scpustate_Psp      libcpu_apply_scpustate_esp
#endif /* !__x86_64__ */

#ifdef __x86_64__
#define pushP_cfi_r_kernel_cs pushq_cfi $(SEGMENT_KERNEL_CODE); .cfi_rel_offset %cs, 0
#else /* __x86_64__ */
#define pushP_cfi_r_kernel_cs pushl_cfi_r %cs
#endif /* !__x86_64__ */


.section .text
PUBLIC_FUNCTION(task_pause)
	.cfi_startproc
#ifndef CONFIG_NO_SMP
	pause
#endif /* !CONFIG_NO_SMP */
	ret
	.cfi_endproc
END(task_pause)


.section .text
PUBLIC_FUNCTION(task_yield)
	.cfi_startproc
	popP_cfi %Pax
	.cfi_register %Pip, %Pax
#ifdef __x86_64__
	movP   %Psp, %Pcx
	pushP_cfi $(SEGMENT_KERNEL_DATA0) /* ir_ss */
	.cfi_rel_offset %ss, 0
	pushP_cfi %Pcx                    /* ir_Psp */
	.cfi_rel_offset %Psp, 0
#endif /* __x86_64__ */
	pushfP_cfi_r                      /* ir_Pflags */
	ttest  mask=EFLAGS_IF, loc=0(%Psp)
	.cfi_remember_state
	jz     .Lillegal_task_yield
	pushP_cfi_r_kernel_cs             /* ir_cs */
	pushP  %Pax                       /* ir_Pip */
#ifdef __x86_64__
	.cfi_adjust_cfa_offset SIZEOF_POINTER
	.cfi_rel_offset %Pip, 0
#endif /* __x86_64__ */

#ifndef __x86_64__
	/* Switch over to a canonical IRET frame. */
	.cfi_def_cfa %Psp, 0
	.cfi_restore_iret_eip
	.cfi_restore_iret_cs
	.cfi_restore_iret_eflags
	.cfi_restore_iret_esp
	.cfi_restore_iret_ss
	.cfi_restore_iret_es
	.cfi_restore_iret_ds
	.cfi_restore_iret_fs
	.cfi_restore_iret_gs
#endif /* !__x86_64__ */

#ifdef __x86_64__
INTERN_FUNCTION(X86_ASMSYSCALL64(sched_yield))
#endif /* __x86_64__ */
	/* Construct a full `struct scpustate' structure */
	ASM_PUSH_SCPUSTATE_AFTER_HW_IRET_CFI_R

.Ltask_yield_with_saved_scpustate:

	/* Remember the current scheduler state. */
	EXTERN(this_sstate)
	movP   %Psp, %segtls:this_sstate

	EXTERN(this_task)
	movP   %segtls:this_task, %Pbp
	movP   %Pbp, %R_fcall1P
	cli
	EXTERN(this_cpu)
	movP   %segtls:this_cpu, %Pbx
	movP   %Pbx, %R_fcall0P
	EXTERN(sched_intern_yield)
	call   sched_intern_yield
	cmpP   %Pbp, %Pax
	je     .Lyield_same_target
.Ldo_yield_to_thread_Pax_cpu_Pbx:
	/* Load the new CPU state */
	EXTERN(thiscpu_sched_current)
	movP   %Pax, thiscpu_sched_current(%Pbx)
	EXTERN(x86_load_thread_Pax_cpu_Pbx)
	jmp    x86_load_thread_Pax_cpu_Pbx
.Lyield_same_target:
#ifndef CONFIG_NO_SMP
	sti
	pause
	cli
#endif /* !CONFIG_NO_SMP */

#ifdef CONFIG_HAVE_KERNEL_DEBUGGER
	/* Special  case: calling `task_yield()' whilst in debugger-mode.
	 * Assuming that the caller wants to wait for something  specific
	 * to  happen, and knowing that the system is running in debugger
	 * mode, we know that there aren't any other threads running that
	 * may cause whatever our caller is waiting for end up happening.
	 *
	 * As such, in the interest  of preventing a deadlock  situation,
	 * rather than allowing the caller to yield indefinitely, we will
	 * throw an `E_WOULDBLOCK' exception. */
	EXTERN(dbg_active)
	cmpb   $0, dbg_active
	jne    .Ldbg_active_task_yield
#endif /* CONFIG_HAVE_KERNEL_DEBUGGER */

#ifdef __x86_64__
	EXTERN(x86_load_scpustate_rsp_gsbase_rax_nopr)
	jmp    x86_load_scpustate_rsp_gsbase_rax_nopr
#else /* __x86_64__ */
	EXTERN(x86_load_scpustate_esp_nopr)
	jmp    x86_load_scpustate_esp_nopr
#endif /* !__x86_64__ */

#ifdef CONFIG_HAVE_KERNEL_DEBUGGER
.Ldbg_active_task_yield:
	/* Throw an exception if the builtin debugger is active. */
	movP   $(EXCEPT_CODEOF(E_WOULDBLOCK)), %R_fcall0P
	EXTERN(except_throw)
	call   except_throw
	nop
#endif /* CONFIG_HAVE_KERNEL_DEBUGGER */

	.cfi_restore_state
.Lillegal_task_yield:
	movP   $(EXCEPT_CODEOF(E_WOULDBLOCK_PREEMPTED)), %R_fcall0P
	EXTERN(except_throw)
	call   except_throw
	nop
#ifdef __x86_64__
END(X86_ASMSYSCALL64(sched_yield))
#endif /* __x86_64__ */
	.cfi_endproc
END(task_yield)

DEFINE_PUBLIC_ALIAS(sys_sched_yield, task_yield)
#ifdef __x86_64__
/* sched_yield() is has an identical implementation in compatibility mode */
DEFINE_INTERN_ALIAS(X86_ASMSYSCALL32_SYSENTER(sched_yield), X86_ASMSYSCALL64(sched_yield))
DEFINE_INTERN_ALIAS(X86_ASMSYSCALL32_INT80(sched_yield), X86_ASMSYSCALL64(sched_yield))
#endif /* __x86_64__ */




#ifndef __x86_64__
.section .text
INTERN_FUNCTION(X86_ASMSYSCALL32_INT80(sched_yield))
	.cfi_startproc simple
	.cfi_restore_iret
	.cfi_def_cfa %esp, 0

	xorl   %eax, %eax /* sched_yield() should return 0 to user-space. */
	ASM_PUSH_SCPUSTATE_AFTER_HW_IRET_CFI_R

	movl   $(SEGMENT_USER_DATA_RPL), %eax
	movl   %eax, %ds
	movl   %eax, %es
	movl   $(SEGMENT_KERNEL_FSBASE), %eax
	movl   %eax, %fs

	jmp    .Ltask_yield_with_saved_scpustate
	.cfi_endproc
END(X86_ASMSYSCALL32_INT80(sched_yield))
DEFINE_INTERN_ALIAS(X86_ASMSYSCALL32_SYSENTER(sched_yield),
                    X86_ASMSYSCALL32_INT80(sched_yield))
#endif /* !__x86_64__ */





.section .text
PUBLIC_FUNCTION(task_yield_nx)
	.cfi_startproc
	popP_cfi %Pax
	.cfi_register %Pip, %Pax
#ifdef __x86_64__
	movq   %rsp, %rcx
	pushq_cfi $(SEGMENT_KERNEL_DATA0) /* ir_ss */
	.cfi_rel_offset %ss, 0
	pushq_cfi %rcx                    /* ir_rsp */
	.cfi_rel_offset %rsp, 0
#endif /* __x86_64__ */
	pushfP_cfi_r                      /* ir_rflags */
	ttest  mask=EFLAGS_IF, loc=0(%Psp)
	.cfi_remember_state
	jz     .Lillegal_task_yield_nx
#ifdef CONFIG_HAVE_KERNEL_DEBUGGER
	EXTERN(dbg_active)
	cmpb   $0, dbg_active
	jne    .Lillegal_task_yield_nx
#endif /* CONFIG_HAVE_KERNEL_DEBUGGER */

	pushP_cfi_r_kernel_cs             /* ir_cs */
	pushP_cfi %Pax                    /* ir_rip */
	.cfi_rel_offset %Pip, 0

	/* Construct a full `struct scpustate' structure */
#ifdef __x86_64__
	pushq_cfi $(1)                    /* [C] Accumulator register */
	.cfi_rel_offset %rax, 0
	ASM_PUSH_GPREGSNSP_NORAX_CFI_R
	ASM_PUSH_SGBASE_CFI_R
	ASM_PUSH_SGREGS_CFI_R(%rax)
#else /* __x86_64__ */
	movl   $(1), %eax /* Eventually, we want to return true. */
	ASM_PUSH_SCPUSTATE_AFTER_IRET_CFI_R
#endif /* !__x86_64__ */
	jmp    .Ltask_yield_with_saved_scpustate
.Lillegal_task_yield_nx:
#ifdef __x86_64__
	addq   $(24), %rsp
	.cfi_adjust_cfa_offset -24
#else /* __x86_64__ */
	addl   $(4), %esp
	.cfi_adjust_cfa_offset -4
#endif /* !__x86_64__ */
	movP   %Pax, %Pcx
	.cfi_register %Pip, %Pcx
	xorP   %Pax, %Pax
	jmpP   *%Pcx
	.cfi_endproc
END(task_yield_nx)




.section .text
PUBLIC_FUNCTION(task_tryyield_or_pause)
	.cfi_startproc
	popP_cfi %Pax
	.cfi_register %Pip, %Pax
#ifdef __x86_64__
	movq   %rsp, %rcx
	pushq_cfi $(SEGMENT_KERNEL_DATA0) /* ir_ss */
	.cfi_rel_offset %ss, 0
	pushq_cfi %rcx                    /* ir_rsp */
	.cfi_rel_offset %rsp, 0
#endif /* __x86_64__ */
	pushfP_cfi_r
	ttest  mask=EFLAGS_IF, loc=0(%Psp)
	jnz    1f
#ifdef __x86_64__
	addq   $(24), %rsp
	.cfi_adjust_cfa_offset -24
	.cfi_same_value %ss
	.cfi_same_value %rsp
#else /* __x86_64__ */
	addl   $(4), %esp
	.cfi_adjust_cfa_offset -4
#endif /* !__x86_64__ */
	.cfi_same_value %Pflags
	movP   %Pax, %Pcx
	movP   $(TASK_TRYYIELD_PREEMPTION_DISABLED), %Pax
#ifndef CONFIG_NO_SMP
	pause
#endif /* !CONFIG_NO_SMP */
	jmpP   *%Pcx
END(task_tryyield_or_pause)
	.cfi_adjust_cfa_offset __SIZEOF_POINTER__
	.cfi_restore %Pip
PUBLIC_FUNCTION(task_tryyield)
	popP_cfi %Pax
	.cfi_register %Pip, %Pax
#ifdef __x86_64__
	movq   %rsp, %rcx
	pushq_cfi $(SEGMENT_KERNEL_DATA0) /* ir_ss */
	.cfi_rel_offset %ss, 0
	pushq_cfi %rcx                    /* ir_rsp */
	.cfi_rel_offset %rsp, 0
#endif /* __x86_64__ */
	pushfP_cfi_r
	ttest  mask=EFLAGS_IF, loc=0(%Psp)
	jnz    1f
	.cfi_remember_state
#ifdef __x86_64__
	addq   $(24), %rsp
	.cfi_adjust_cfa_offset -24
	.cfi_same_value %ss
	.cfi_same_value %rsp
#else /* __x86_64__ */
	addl   $(4), %esp
	.cfi_adjust_cfa_offset -4
#endif /* !__x86_64__ */
	.cfi_same_value %Pflags
	movP   %Pax, %Pcx
	movP   $(TASK_TRYYIELD_PREEMPTION_DISABLED), %Pax
	jmpP   *%Pcx
1:	.cfi_restore_state
	pushP_cfi_r_kernel_cs            /* ir_cs */
	pushP_cfi %Pax                   /* ir_rip */
	.cfi_rel_offset %Pip, 0

	/* Construct a full `struct scpustate' structure */
#ifdef __x86_64__
	pushq_cfi $(TASK_TRYYIELD_SUCCESS) /* [C] Accumulator register */
	.cfi_rel_offset %rax, 0
	ASM_PUSH_GPREGSNSP_NORAX_CFI_R
	ASM_PUSH_SGBASE_CFI_R
	ASM_PUSH_SGREGS_CFI_R(%rax)
#else /* __x86_64__ */
	movl   $(TASK_TRYYIELD_SUCCESS), %eax
	ASM_PUSH_SCPUSTATE_AFTER_IRET_CFI_R
#endif /* !__x86_64__ */

	EXTERN(this_task)
	movP   %segtls:this_task, %Pbp

	/* Remember the current scheduler state. */
	EXTERN(this_sstate)
	movP   %Psp, this_sstate(%Pbp)
	movP   %Pbp, %R_fcall1P
	cli
	EXTERN(this_cpu)
	movP   this_cpu(%Pbp), %Pbx
	movP   %Pbx, %R_fcall0P
	EXTERN(sched_intern_yield)
	call   sched_intern_yield
	cmpP   %Pbp, %Pax
	jne    .Ldo_yield_to_thread_Pax_cpu_Pbx
#ifndef CONFIG_NO_SMP
	sti
#endif /* !CONFIG_NO_SMP */

	/* Same target... */
#ifdef __x86_64__
	movq   $(TASK_TRYYIELD_NO_SUCCESSOR), (OFFSET_SCPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_RAX)(%rsp)
#else /* __x86_64__ */
	movl   $(TASK_TRYYIELD_NO_SUCCESSOR), (OFFSET_SCPUSTATE_GPREGS + OFFSET_GPREGS_EAX)(%esp)
#endif /* !__x86_64__ */

#ifndef CONFIG_NO_SMP
	pause /* Let other CPUs run for a bit */
	cli   /* Don't forget to re-disable interrupts before loading the new CPU state */
#endif /* !CONFIG_NO_SMP */

#ifdef __x86_64__
	EXTERN(x86_load_scpustate_rsp_gsbase_rax_nopr)
	jmp    x86_load_scpustate_rsp_gsbase_rax_nopr
#else /* __x86_64__ */
	EXTERN(x86_load_scpustate_esp_nopr)
	jmp    x86_load_scpustate_esp_nopr
#endif /* !__x86_64__ */
	.cfi_endproc
END(task_tryyield)






.section .text
/* Save the current CPU context and store it in `caller->t_state'.
 * Then, switch context to `PERCPU(thiscpu_sched_current)' and continue by executing it.
 * NOTE: Preemption must be disabled before this function may be called!
 * NOTE: Upon return, preemption will have been re-enabled! */
PUBLIC_FUNCTION(cpu_run_current_and_remember_nopr)
	/* %R_fcall0P: <struct task *__restrict caller> */
	.cfi_startproc
	popP_cfi %Pax
	.cfi_register %Pip, %Pax
#ifdef __x86_64__
	movq   %rsp, %rcx
	pushq_cfi $(SEGMENT_KERNEL_DATA0) /* ir_ss */
	.cfi_rel_offset %ss, 0
	pushq_cfi %rcx                    /* ir_rsp */
	.cfi_rel_offset %rsp, 0
#endif /* __x86_64__ */
	pushfP_cfi_r                      /* ir_Pflags */
	orP    $(EFLAGS_IF), (%Psp)
	pushP_cfi_r_kernel_cs             /* ir_cs */
	pushP_cfi %Pax                    /* ir_Pip */
	.cfi_rel_offset %Pip, 0

	/* Construct a full `struct scpustate' structure */
	ASM_PUSH_SCPUSTATE_AFTER_IRET_CFI_R

	/* Remember the current scheduler state. */
	EXTERN(this_sstate)
	movP   %Psp, this_sstate(%R_fcall0P)
	EXTERN(this_cpu)
	movP   this_cpu(%R_fcall0P), %Pbx
	EXTERN(thiscpu_sched_current)
	movP   thiscpu_sched_current(%Pbx), %Pax

	/* Load the new CPU state */
	EXTERN(x86_load_thread_Pax_cpu_Pbx)
	jmp    x86_load_thread_Pax_cpu_Pbx
	.cfi_endproc
END(cpu_run_current_and_remember_nopr)


.section .text
/* Similar to `cpu_run_current_and_remember_nopr()',
 * but  don't   remember   the   caller's   context.
 * This  function is used to implement `task_exit()'
 * NOTE: Preemption must be disabled before this function may be called! */
PUBLIC_FUNCTION(cpu_run_current_nopr)
	.cfi_startproc
	/* Load the CPU state of the task set as current. */
	EXTERN(this_cpu)
	movP   %segtls:this_cpu, %Pbx
	EXTERN(thiscpu_sched_current)
	movP   thiscpu_sched_current(%Pbx), %Pax
	/* Load the new CPU state */
	EXTERN(x86_load_thread_Pax_cpu_Pbx)
	jmp    x86_load_thread_Pax_cpu_Pbx
	.cfi_endproc
END(cpu_run_current_nopr)


.section .text
	.cfi_startproc
	/* TODO: CFI annotation to say that there is no return address */
	/* TODO: CFI annotation for custom catch-all-and-dump-to-syslog exception handler */
	nop
PUBLIC_FUNCTION(x86_kthread_exit)
	movP   %Pax, %R_fcall0P
	EXTERN(task_exit)
	call   task_exit
	nop
END(x86_kthread_exit)
	.cfi_endproc




#ifndef CONFIG_NO_SMP
.section .text.cold
/* >> INTDEF NOBLOCK NOPREEMPT ATTR_COLDTEXT NONNULL((1, 2)) struct icpustate *
 * >> NOTHROW(FCALL arch_sched_super_override_ipi)(struct icpustate *__restrict state,
 * >>                                              void *args[CPU_IPI_ARGCOUNT]);  */
INTERN_FUNCTION(arch_sched_super_override_ipi)
	.cfi_startproc
	.cfi_def_cfa %R_fcall0P, 0
	ASM_CFI_OFFSET_RESTORE_ICPUSTATE(0)
	movP   %R_fcall0P, %Psp /* Return register state. (as an `icpustate') */
	.cfi_def_cfa_register %Psp

	/* Convert the caller's `icpustate' register state into a `scpustate' */
#ifdef __x86_64__
	ASM_PUSH_SGBASE_CFI_R
	ASM_PUSH_SGREGS_CFI_R(%rax)
#else /* __x86_64__ */
	popal_cfi_r
	pushl_cfi_r %gs
	pushal_cfi_r
#endif /* !__x86_64__ */

	cli    /* Should already be the case, but better be careful! */

	EXTERN(this_cpu)
	movP   %segtls:this_cpu, %Pbx

	/* Check if we're already the scheduler override for our CPU. */
	EXTERN(thiscpu_sched_override)
	movP   thiscpu_sched_override(%Pbx), %Pbp
	testP  %Pbp, %Pbp
	jnz    1f
	EXTERN(sched_override_start)
	call   sched_override_start
	movP   %Pax, %Pbx
1:	/* %Pbx = struct cpu *THIS_CPU;
	 * %Psp = struct scpustate *state;
	 * %Pbp = struct task *old_sched_override; */

	/* Save the current register state. */
	EXTERN(this_sstate)
	movP   %Psp, %segtls:this_sstate

	/* Invoke the high-level super-override IPI function. */
	EXTERN(sched_super_override_ipi)
	call   sched_super_override_ipi

	/* Release our scheduler override, if we acquired it earlier. */
	testP  %Pbp, %Pbp
	jnz    1f    /* if (old_sched_override != NULL) goto 1f; */
	EXTERN(sched_override_end)
	call   sched_override_end
1:

	/* Resume execution by loading the next thread. But still
	 * check if that thread differs from our current  thread. */
	EXTERN(thiscpu_sched_current)
	movP   thiscpu_sched_current(%Pbx), %Pax
	EXTERN(this_task)
	cmpP   %Pax, %segtls:this_task
	EXTERN(x86_load_thread_Pax_cpu_Pbx)
	jne    x86_load_thread_Pax_cpu_Pbx /* Switch to a different thread. */

	/* Resume execution by re-loading `this_sstate' */
	EXTERN(this_sstate)
	movP   %segtls:this_sstate, %Psp

	EXTERN(libcpu_apply_scpustate_Psp)
	jmp    libcpu_apply_scpustate_Psp
	.cfi_endproc
END(arch_sched_super_override_ipi)
#endif /* !CONFIG_NO_SMP */

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_SCHED_SCHED_S */
