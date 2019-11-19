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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_SCHED_SCHED_C
#define GUARD_KERNEL_CORE_ARCH_I386_SCHED_SCHED_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <fs/vfs.h>
#include <kernel/apic.h>
#include <kernel/except.h>
#include <kernel/gdt.h>
#include <kernel/handle.h>
#include <kernel/paging.h>
#include <kernel/panic.h>
#include <kernel/pic.h>
#include <kernel/pit.h>
#include <kernel/printk.h>
#include <kernel/syscall.h>
#include <kernel/user.h>
#include <sched/cpu.h>
#include <sched/rpc.h>
#include <sched/task.h>

#include <hybrid/atomic.h>

#include <asm/cpu-flags.h>
#include <kos/compat/linux-ldt.h>
#include <kos/except-inval.h>
#include <kos/kernel/cpu-state-helpers.h>
#include <kos/kernel/cpu-state.h>
#include <sys/io.h>

#include <assert.h>
#include <stdarg.h>
#include <string.h>

#include <libunwind/unwind.h>

DECL_BEGIN


INTDEF byte_t __kernel_bootidle_stack[KERNEL_IDLE_STACKSIZE];

INTERN ATTR_FREETEXT void KCALL
kernel_initialize_scheduler_arch(void) {
	struct scpustate *init_state;
	/* Initialize the CPU state of the boot CPU's idle thread. */
#ifdef __x86_64__
	init_state = (struct scpustate *)((__kernel_bootidle_stack + KERNEL_IDLE_STACKSIZE) - SIZEOF_SCPUSTATE);
	memset(init_state, 0, SIZEOF_SCPUSTATE);
	init_state->scs_sgbase.sg_gsbase = (u64)&_bootidle;
	init_state->scs_sgregs.sg_gs     = SEGMENT_USER_DATA_RPL;
	init_state->scs_sgregs.sg_fs     = SEGMENT_USER_DATA_RPL;
	init_state->scs_sgregs.sg_es     = SEGMENT_USER_DATA_RPL;
	init_state->scs_sgregs.sg_ds     = SEGMENT_USER_DATA_RPL;
	init_state->scs_irregs.ir_cs     = SEGMENT_KERNEL_CODE;
	init_state->scs_irregs.ir_ss     = SEGMENT_KERNEL_DATA;
	init_state->scs_irregs.ir_rsp    = (u64)(__kernel_bootidle_stack + KERNEL_IDLE_STACKSIZE);
	init_state->scs_irregs.ir_rip    = (u64)(void *)&cpu_idlemain;
	_bootidle.t_sched.s_state        = init_state;
#else /* __x86_64__ */
	init_state = (struct scpustate *)((__kernel_bootidle_stack + KERNEL_IDLE_STACKSIZE) -
	                                  (OFFSET_SCPUSTATE_IRREGS + SIZEOF_IRREGS_KERNEL));
	memset(init_state, 0, OFFSET_SCPUSTATE_IRREGS + SIZEOF_IRREGS_KERNEL);
	init_state->scs_sgregs.sg_gs    = SEGMENT_USER_GSBASE_RPL;
	init_state->scs_sgregs.sg_fs    = SEGMENT_KERNEL_FSBASE;
	init_state->scs_sgregs.sg_es    = SEGMENT_USER_DATA_RPL;
	init_state->scs_sgregs.sg_ds    = SEGMENT_USER_DATA_RPL;
	init_state->scs_irregs_k.ir_cs  = SEGMENT_KERNEL_CODE;
	init_state->scs_irregs_k.ir_eip = (u32)(void *)&cpu_idlemain;
	_bootidle.t_sched.s_state       = init_state;
#endif /* !__x86_64__ */
}


PUBLIC NOBLOCK ATTR_RETNONNULL ATTR_SENTINEL NONNULL((1, 2)) struct task *
NOTHROW(VCALL task_setup_kernel)(struct task *__restrict thread,
                                 thread_main_t thread_main,
                                 size_t argc, ...) {
#ifdef __x86_64__
	struct scpustate *state;
	va_list args; byte_t *dest;
	va_start(args, argc);
	dest = (byte_t *)FORTASK(thread, this_x86_kernel_psp0);
	*(u64 *)(dest -= 8) = (u64)(void *)((void *)(void(FCALL *)(int))&task_exit);
	if (argc > 6)
		dest -= (argc - 6) * 8;
	state = (struct scpustate *)(dest - SIZEOF_SCPUSTATE);
	/* Initialize the thread's entry state. */
	memset(state, 0, sizeof(*state));
	state->scs_irregs.ir_cs     = SEGMENT_KERNEL_CODE;
	state->scs_irregs.ir_ss     = SEGMENT_KERNEL_DATA;
	state->scs_irregs.ir_rsp    = (u64)dest;
	state->scs_irregs.ir_rflags = EFLAGS_IF;
	state->scs_irregs.ir_rip    = (u64)(void *)thread_main;
	state->scs_sgregs.sg_gs     = SEGMENT_USER_DATA_RPL; /* Doesn't really matter, but stick to the likely case of this being USER_GSBASE */
	state->scs_sgregs.sg_fs     = SEGMENT_USER_DATA_RPL;
	state->scs_sgregs.sg_es     = SEGMENT_USER_DATA_RPL;
	state->scs_sgregs.sg_ds     = SEGMENT_USER_DATA_RPL;
	state->scs_sgbase.sg_gsbase = (u64)thread;
	/* Fill in arguments */
	if (argc >= 1)
		state->scs_gpregs.gp_rdi = va_arg(args, u64);
	if (argc >= 2)
		state->scs_gpregs.gp_rsi = va_arg(args, u64);
	if (argc >= 3)
		state->scs_gpregs.gp_rdx = va_arg(args, u64);
	if (argc >= 4)
		state->scs_gpregs.gp_rcx = va_arg(args, u64);
	if (argc >= 5)
		state->scs_gpregs.gp_r8 = va_arg(args, u64);
	if (argc >= 6)
		state->scs_gpregs.gp_r9 = va_arg(args, u64);
	if (argc > 6) {
		size_t i;
		for (i = 0; i < (argc - 6); ++i)
			((u64 *)dest)[i] = va_arg(args, u64);
	}
#else /* __x86_64__ */
	byte_t *dest = (byte_t *)FORTASK(thread, this_x86_kernel_psp0);
	struct scpustate *state;
#define PUSH(x) (dest -= sizeof(u32), *(u32 *)dest = (x))
	dest -= argc * sizeof(void *);
	memcpy(dest, &argc + 1, argc * sizeof(void *));
	PUSH((u32)(void *)(void(FCALL *)(int)) & task_exit); /* Return address */
	dest -= OFFSET_SCPUSTATE_IRREGS + SIZEOF_IRREGS_KERNEL;
	state = (struct scpustate *)dest;
	/* Initialize the thread's entry state. */
	state->scs_irregs_k.ir_cs     = SEGMENT_KERNEL_CODE;
	state->scs_irregs_k.ir_eflags = EFLAGS_IF;
	state->scs_irregs_k.ir_eip    = (u32)(void *)thread_main;
	state->scs_sgregs.sg_gs       = SEGMENT_USER_GSBASE_RPL; /* Doesn't really matter, but stick to the likely case of this being USER_GSBASE */
	state->scs_sgregs.sg_fs       = SEGMENT_KERNEL_FSBASE;
	state->scs_sgregs.sg_es       = SEGMENT_USER_DATA_RPL;
	state->scs_sgregs.sg_ds       = SEGMENT_USER_DATA_RPL;
	/* No special values required for general purpose registers. */
	memset(&state->scs_gpregs, 0, sizeof(state->scs_gpregs));
#undef PUSH
#endif /* !__x86_64__ */
	/* TODO: Must also execute thread startup callbacks! */
	ATOMIC_FETCHOR(thread->t_flags, TASK_FKERNTHREAD);
	thread->t_sched.s_state = state;
	if (!FORTASK(thread, this_fs))
		FORTASK(thread, this_fs) = incref(&fs_kernel);
	if (!FORTASK(thread, this_handle_manager))
		FORTASK(thread, this_handle_manager) = incref(&handle_manager_kernel);
	return thread;
}



INTDEF NOBLOCK void NOTHROW(KCALL x86_cpu_disable_preemptive_interrupts)(void);
INTDEF NOBLOCK void NOTHROW(KCALL x86_cpu_enable_preemptive_interrupts)(void);
INTDEF NOBLOCK void NOTHROW(KCALL x86_cpu_disable_preemptive_interrupts_nopr)(void);
INTDEF NOBLOCK void NOTHROW(KCALL x86_cpu_enable_preemptive_interrupts_nopr)(void);

PUBLIC NOBLOCK void
NOTHROW(KCALL cpu_disable_preemptive_interrupts)(void) {
	assert(!PREEMPTION_ENABLED() ||
	       (PERTASK_GET(this_task.t_flags) & (TASK_FKEEPCORE | TASK_FTERMINATING)));
	x86_cpu_disable_preemptive_interrupts();
	/* TODO: Track the time that passes between here and the
	 *       next call to `cpu_enable_preemptive_interrupts()' */
}

PUBLIC NOBLOCK void
NOTHROW(KCALL cpu_disable_preemptive_interrupts_nopr)(void) {
	assert(!PREEMPTION_ENABLED());
	x86_cpu_disable_preemptive_interrupts_nopr();
	/* TODO: Track the time that passes between here and the
	 *       next call to `cpu_enable_preemptive_interrupts()' */
}


PUBLIC NOBLOCK void
NOTHROW(KCALL cpu_enable_preemptive_interrupts)(void) {
	assert(!PREEMPTION_ENABLED() ||
	       (PERTASK_GET(this_task.t_flags) & (TASK_FKEEPCORE | TASK_FTERMINATING)));
	/* TODO: Track the time that passes between here and the
	 *       last call to `cpu_disable_preemptive_interrupts()' */
	x86_cpu_enable_preemptive_interrupts();
}

PUBLIC NOBLOCK void
NOTHROW(KCALL cpu_enable_preemptive_interrupts_nopr)(void) {
	assert(!PREEMPTION_ENABLED());
	/* TODO: Track the time that passes between here and the
	 *       last call to `cpu_disable_preemptive_interrupts()' */
	x86_cpu_enable_preemptive_interrupts_nopr();
}



#ifdef __x86_64__

/* Modify `state' to insert an asynchronous call to the given RPC function.
 * When that function then returns, the old state will restored, and (if provided)
 * the `completed' signal will be broadcast.
 * The reason passed to `func' is either `TASK_RPC_REASON_ASYNCUSER' if the
 * old state points into user-space, or `TASK_RPC_REASON_ASYNC' if not. */
PUBLIC NOBLOCK ATTR_RETNONNULL NONNULL((1, 2)) struct scpustate *
NOTHROW(FCALL task_push_asynchronous_rpc)(struct scpustate *__restrict state,
                                          task_rpc_t func, void *arg,
                                          struct sig *completed) {
	kernel_panic("TODO");
}


/* Same as `task_push_asynchronous_rpc()', but pass a copy
 * of the given buffer as value for `arg' to the given `func'. */
PUBLIC NOBLOCK ATTR_RETNONNULL NONNULL((1, 2)) struct scpustate *
NOTHROW(FCALL task_push_asynchronous_rpc_v)(struct scpustate *__restrict state,
                                            task_rpc_t func, void const *buf,
                                            size_t bufsize, struct sig *completed) {
	kernel_panic("TODO");
}



PUBLIC NOBLOCK ATTR_RETNONNULL NONNULL((1, 2)) struct scpustate *
NOTHROW(FCALL task_push_asynchronous_srpc)(struct scpustate *__restrict state,
                                           task_srpc_t func, void *arg,
                                           struct sig *completed) {
	kernel_panic("TODO");
}


/* An arch-specific function used to re-direct the given task's user-space
 * return target to instead point back towards a kernel-space function which is then
 * able to service RPC functions scheduled using `task_(schedule|exec)_user_[s]rpc()'
 * On x86, this is done by modifying the IRET tail at the top of the target thread's stack:
 *   >> FORTASK(self,this_x86_rpc_redirection_iret).ir_eip    = GET_USERCODE_IRET(self)->ir_eip;
 *   >> FORTASK(self,this_x86_rpc_redirection_iret).ir_cs     = GET_USERCODE_IRET(self)->ir_cs;
 *   >> FORTASK(self,this_x86_rpc_redirection_iret).ir_eflags = GET_USERCODE_IRET(self)->ir_eflags;
 *   >> GET_USERCODE_IRET(self)->ir_eip                  = &x86_rpc_user_redirection;
 *   >> GET_USERCODE_IRET(self)->ir_cs                   = SEGMENT_KERNEL_CODE;
 *   >> GET_USERCODE_IRET(self)->ir_eflags               = 0;
 * NOTE: The caller must ensure that preemption is disabled,
 *       and that `self' is hosted by the calling CPU.
 *       Additionally, the caller must ensure that `self' has
 *       neither terminated, nor is actually set up to be a
 *       kernel-space thread.
 * @return: true:  Successfully redirected the given thread.
 * @return: false: The given thread has already been redirected. */
PUBLIC NOBLOCK NONNULL((1)) bool
NOTHROW(FCALL task_enable_redirect_usercode_rpc)(struct task *__restrict self) {
	kernel_panic("TODO");
	return true;
}


#else /* __x86_64__ */

/* EAX:    <task_rpc_t func>
 * ECX:    <void *arg>
 * EDX:    <struct icpustate *>    (contains the return location; also used for CFI)
 * EBX:    <unsigned int reason>
 * EBP:    <struct icpustate *>    (Alias for `EDX')
 * ESP:    { EDI, ESI, EBP, IGNORED, EBX, EDX, ECX, EAX, FS, ES, DS, IRREGS }
 * EFLAGS: <0>                     (interrupts are disabled)
 * CS:     <SEGMENT_KERNEL_CODE>
 * SS:     <SEGMENT_KERNEL_DATA>
 * DS:     <SEGMENT_USER_DATA_RPL>
 * ES:     <SEGMENT_USER_DATA_RPL>
 * FS:     <SEGMENT_KERNEL_FSBASE>
 * GS:     Already restored
 * *:      Undefined */
INTDEF void ASMCALL x86_rpc_kernel_redirection(void);
INTDEF void ASMCALL x86_rpc_kernel_redirection_handler(void);

/* EAX:    <task_rpc_t func>
 * ECX:    <void *arg>
 * EDX:    <struct icpustate *>    (contains the return location; also used for CFI)
 * EBX:    <unsigned int reason>
 * EBP:    <struct icpustate *>    (Alias for `EDX')
 * ESP:    { <struct sig *completed>, EDI, ESI, EBP, IGNORED, EBX, EDX, ECX, EAX, FS, ES, DS, IRREGS }
 * EFLAGS: <0>                     (interrupts are disabled)
 * CS:     <SEGMENT_KERNEL_CODE>
 * SS:     <SEGMENT_KERNEL_DATA>
 * DS:     <SEGMENT_USER_DATA_RPL>
 * ES:     <SEGMENT_USER_DATA_RPL>
 * FS:     <SEGMENT_KERNEL_FSBASE>
 * GS:     Already restored
 * *:      Undefined */
INTDEF void ASMCALL x86_rpc_kernel_redirection_c(void);
INTDEF void ASMCALL x86_rpc_kernel_redirection_c_handler(void);


/* EAX:    <task_srpc_t func>
 * ECX:    <void *arg>
 * ESP:    { EDX, ECX, EAX, FS, ES, DS, IRREGS }
 * EFLAGS: <0>                     (interrupts are disabled)
 * CS:     <SEGMENT_KERNEL_CODE>
 * SS:     <SEGMENT_KERNEL_DATA>
 * DS:     <SEGMENT_USER_DATA_RPL>
 * ES:     <SEGMENT_USER_DATA_RPL>
 * FS:     <SEGMENT_KERNEL_FSBASE>
 * GS:     Already restored
 * *:      Undefined */
INTDEF void ASMCALL x86_srpc_kernel_redirection(void);
INTDEF void ASMCALL x86_srpc_kernel_redirection_handler(void);

/* EAX:    <task_srpc_t func>
 * ECX:    <void *arg>
 * ESP:    { <struct sig *completed>, EDX, ECX, EAX, FS, ES, DS, IRREGS }
 * EFLAGS: <0>                     (interrupts are disabled)
 * CS:     <SEGMENT_KERNEL_CODE>
 * SS:     <SEGMENT_KERNEL_DATA>
 * DS:     <SEGMENT_USER_DATA_RPL>
 * ES:     <SEGMENT_USER_DATA_RPL>
 * FS:     <SEGMENT_KERNEL_FSBASE>
 * GS:     Already restored
 * *:      Undefined */
INTDEF void ASMCALL x86_srpc_kernel_redirection_c(void);
INTDEF void ASMCALL x86_srpc_kernel_redirection_c_handler(void);


/* Modify `state' to insert an asynchronous call to the given RPC function.
 * When that function then returns, the old state will restored, and (if provided)
 * the `completed' signal will be broadcast.
 * The reason passed to `func' is either `TASK_RPC_REASON_ASYNCUSER' if the
 * old state points into user-space, or `TASK_RPC_REASON_ASYNC' if not. */
PUBLIC NOBLOCK ATTR_RETNONNULL NONNULL((1, 2)) struct scpustate *
NOTHROW(FCALL task_push_asynchronous_rpc)(struct scpustate *__restrict state,
                                          task_rpc_t func, void *arg,
                                          struct sig *completed) {
	struct ATTR_PACKED buffer {
		struct gpregs b_gpregs; /* General purpose registers. */
		u32           b_gs;     /* G segment register (Usually `SEGMENT_USER_GSBASE_RPL') */
	};
	struct icpustate *istate;
	struct scpustate *result;
	struct buffer buf;
	byte_t *dest;
	memcpy(&buf, state, sizeof(buf));
	dest = (byte_t *)state + sizeof(buf);
#define SUBSP(x) (dest -= (x))
	/* DEST: fs, es, ds, eip, cs, eflags, [...] */
	SUBSP(sizeof(struct gpregs));
	memcpy(dest, &buf.b_gpregs, sizeof(struct gpregs));
	/* `dest' now points to a valid `struct icpustate' (which will be passed to `func') */
	istate = (struct icpustate *)dest;
	if (completed) {
		SUBSP(sizeof(struct sig *));
		*(uintptr_t *)dest = (uintptr_t)completed;
	}
	/* Allocate a kernel-space S-cpustate, which will be loaded to execute the user-function. */
	SUBSP(OFFSET_SCPUSTATE_IRREGS + SIZEOF_IRREGS_KERNEL);
	result = (struct scpustate *)dest;
	/* Fill in the new state to generate a redirection towards the RPC wrapper. */
	result->scs_gpregs.gp_ebp   = (uintptr_t)istate;
	result->scs_gpregs.gp_ebx   = irregs_isuser(&istate->ics_irregs)
	                              ? TASK_RPC_REASON_ASYNCUSER
	                              : TASK_RPC_REASON_ASYNC;
	result->scs_gpregs.gp_edx   = (uintptr_t)istate;
	result->scs_gpregs.gp_ecx   = (uintptr_t)arg;
	result->scs_gpregs.gp_eax   = (uintptr_t)(void *)func;
	result->scs_sgregs.sg_ds    = SEGMENT_USER_DATA_RPL;
	result->scs_sgregs.sg_es    = SEGMENT_USER_DATA_RPL;
	result->scs_sgregs.sg_fs    = SEGMENT_KERNEL_FSBASE;
	result->scs_sgregs.sg_gs    = buf.b_gs;
	result->scs_irregs_k.ir_eip = completed
	                              ? (uintptr_t)&x86_rpc_kernel_redirection_c
	                              : (uintptr_t)&x86_rpc_kernel_redirection;
	result->scs_irregs_k.ir_cs     = SEGMENT_KERNEL_CODE;
	result->scs_irregs_k.ir_eflags = 0;
#undef SUBSP
	return result;
}


/* Same as `task_push_asynchronous_rpc()', but pass a copy
 * of the given buffer as value for `arg' to the given `func'. */
PUBLIC NOBLOCK ATTR_RETNONNULL NONNULL((1, 2)) struct scpustate *
NOTHROW(FCALL task_push_asynchronous_rpc_v)(struct scpustate *__restrict state,
                                            task_rpc_t func, void const *buf,
                                            size_t bufsize, struct sig *completed) {
	struct ATTR_PACKED buffer {
		struct gpregs b_gpregs; /* General purpose registers. */
		u32 b_gs;               /* G segment register (Usually `SEGMENT_USER_GSBASE_RPL') */
	};
	struct icpustate *istate;
	struct scpustate *result;
	struct buffer regbuf;
	byte_t *dest;
	void *argbuffer;
	memcpy(&regbuf, state, sizeof(regbuf));
	dest = (byte_t *)state + sizeof(regbuf);
#define SUBSP(x) (dest -= (x))
	/* DEST: fs, es, ds, eip, cs, eflags, [...] */
	SUBSP(sizeof(struct gpregs));
	memcpy(dest, &regbuf.b_gpregs, sizeof(struct gpregs));
	/* `dest' now points to a valid `struct icpustate' (which will be passed to `func') */
	istate = (struct icpustate *)dest;
	/* Allocate memory for the given `buf' */
	SUBSP(bufsize);
	argbuffer = dest;
	memcpy(argbuffer, buf, bufsize);
	/* Allocate a kernel-space S-cpustate, which will be loaded to execute the user-function. */
	SUBSP(OFFSET_SCPUSTATE_IRREGS + SIZEOF_IRREGS_KERNEL);
	result = (struct scpustate *)dest;
	/* Fill in the new state to generate a redirection towards the RPC wrapper. */
	result->scs_gpregs.gp_ebp = (uintptr_t)istate;
	result->scs_gpregs.gp_ebx = irregs_isuser(&istate->ics_irregs)
	                            ? TASK_RPC_REASON_ASYNCUSER
	                            : TASK_RPC_REASON_ASYNC;
	result->scs_gpregs.gp_edx = (uintptr_t)istate;
	result->scs_gpregs.gp_ecx = (uintptr_t)argbuffer;
	result->scs_gpregs.gp_eax = (uintptr_t)(void *)func;
	result->scs_sgregs.sg_ds  = SEGMENT_USER_DATA_RPL;
	result->scs_sgregs.sg_es  = SEGMENT_USER_DATA_RPL;
	result->scs_sgregs.sg_fs  = SEGMENT_KERNEL_FSBASE;
	result->scs_sgregs.sg_gs  = regbuf.b_gs;
	result->scs_irregs_k.ir_eip = (uintptr_t)&x86_rpc_kernel_redirection;
	result->scs_irregs_k.ir_cs  = SEGMENT_KERNEL_CODE;
	result->scs_irregs_k.ir_eflags = 0;
#undef SUBSP
	return result;
}



PUBLIC NOBLOCK ATTR_RETNONNULL NONNULL((1, 2)) struct scpustate *
NOTHROW(FCALL task_push_asynchronous_srpc)(struct scpustate *__restrict state,
                                           task_srpc_t func, void *arg,
                                           struct sig *completed) {
	/* EAX:    <task_srpc_t func>
	 * ECX:    <void *arg>
	 * ESP:    { EDX, ECX, EAX, FS, ES, DS, IRREGS }
	 * EFLAGS: <0>                     (interrupts are disabled)
	 * CS:     <SEGMENT_KERNEL_CODE>
	 * SS:     <SEGMENT_KERNEL_DATA>
	 * DS:     <SEGMENT_USER_DATA_RPL>
	 * ES:     <SEGMENT_USER_DATA_RPL>
	 * FS:     <SEGMENT_KERNEL_FSBASE>
	 * GS:     Already restored
	 * *:      Undefined */
	struct ATTR_PACKED buffer {
		struct gpregs b_gpregs; /* General purpose registers. */
		struct sgregs b_sgregs; /* Segment registers. */
	};
	struct scpustate *result;
	struct buffer regbuf;
	byte_t *dest;
	/* NOTE: sizeof(regbuf) == OFFSET_SCPUSTATE_IRREGS */
	memcpy(&regbuf, state, sizeof(regbuf));
	dest = (byte_t *)state + OFFSET_SCPUSTATE_IRREGS;
#define SUBSP(x) (dest -= (x))
#define PUSH(x)  (dest -= sizeof(uintptr_t), *(uintptr_t *)dest = (x))
	/* Save clobbered registers. */
	PUSH(regbuf.b_sgregs.sg_ds16);
	PUSH(regbuf.b_sgregs.sg_es16);
	PUSH(regbuf.b_sgregs.sg_fs16);
	PUSH(regbuf.b_gpregs.gp_eax);
	PUSH(regbuf.b_gpregs.gp_ecx);
	PUSH(regbuf.b_gpregs.gp_edx);
	if (completed)
		PUSH((uintptr_t)completed);

	/* Allocate a kernel-space S-cpustate, which will be loaded to execute the user-function. */
	SUBSP(OFFSET_SCPUSTATE_IRREGS + SIZEOF_IRREGS_KERNEL);
	result = (struct scpustate *)dest;

	/* Fill in the new state to generate a redirection towards the RPC wrapper. */
	result->scs_gpregs.gp_edi   = regbuf.b_gpregs.gp_edi;
	result->scs_gpregs.gp_esi   = regbuf.b_gpregs.gp_esi;
	result->scs_gpregs.gp_ebp   = regbuf.b_gpregs.gp_ebp;
	result->scs_gpregs.gp_ebx   = regbuf.b_gpregs.gp_ebx;
	result->scs_gpregs.gp_edx   = regbuf.b_gpregs.gp_edx;
	result->scs_gpregs.gp_eax   = (uintptr_t)func;
	result->scs_gpregs.gp_ecx   = (uintptr_t)arg;
	result->scs_sgregs.sg_ds    = SEGMENT_USER_DATA_RPL;
	result->scs_sgregs.sg_es    = SEGMENT_USER_DATA_RPL;
	result->scs_sgregs.sg_fs    = SEGMENT_KERNEL_FSBASE;
	result->scs_sgregs.sg_gs    = regbuf.b_sgregs.sg_gs;
	result->scs_irregs_k.ir_eip = completed
	                              ? (uintptr_t)&x86_srpc_kernel_redirection_c
	                              : (uintptr_t)&x86_srpc_kernel_redirection;
	result->scs_irregs_k.ir_cs     = SEGMENT_KERNEL_CODE;
	result->scs_irregs_k.ir_eflags = 0;
#undef PUSH
#undef SUBSP
	return result;
}


INTDEF byte_t x86_lcall7_main[];
INTDEF byte_t x86_lcall7_main_iret[];

PRIVATE ATTR_COLD NOBLOCK u32
NOTHROW(KCALL get_userspace_eflags)(struct task const *__restrict self) {
	struct ucpustate st, ost;
	void *unwind_pc;
	unsigned int unwind_error;
	assert(!PREEMPTION_ENABLED());
	assert(self->t_cpu == THIS_CPU);
	assert(!(self->t_flags & TASK_FKERNTHREAD));
	if (self == THIS_TASK) {
		ucpustate_current(&st);
	} else {
		scpustate_to_ucpustate(self->t_sched.s_state, &st);
	}
	unwind_pc = (void *)ucpustate_getpc(&st);
	for (;;) {
		memcpy(&ost, &st, sizeof(struct ucpustate));
		unwind_error = unwind(unwind_pc,
		                      &unwind_getreg_ucpustate, &ost,
		                      &unwind_setreg_ucpustate, &st);
		if unlikely(unwind_error != UNWIND_SUCCESS) {
			/* XXX: There may be cases where this is allowed.
			 *      Maybe custom task termination protocols? */
			kernel_panic("Unwind failed: %u", unwind_error);
		}
		if (!ucpustate_iskernel(&st))
			break;
		unwind_pc = (void *)(ucpustate_getpc(&st) - 1);
	}
	return st.ucs_eflags;
}

/* Return a pointer to the original user-space IRET tail of the calling thread.
 * This is the pointer to the IRET structure located at the base of the caller's kernel stack.
 * NOTE: The caller must ensure that preemption is disabled,
 *       and that `thread' is hosted by the calling CPU. */
PUBLIC ATTR_CONST ATTR_RETNONNULL NOBLOCK NONNULL((1)) struct irregs_user *
NOTHROW(FCALL x86_get_irregs)(struct task const *__restrict self) {
	struct irregs_user *result;
	assert(!PREEMPTION_ENABLED());
	assert(self->t_cpu == THIS_CPU);
	assert(!(self->t_flags & TASK_FKERNTHREAD));
#define stacktop() ((byte_t *)FORTASK(self, this_x86_kernel_psp0))
	result = (struct irregs_user *)(stacktop() - SIZEOF_IRREGS_USER);
	/* We need to account for the special case of the IRET tail pointing a VM86 thread!
	 * If this is the case, then fields of `result' are currently mapped as:
	 *  - ((u32 *)result)[-4] = real_result->ir_eip
	 *  - ((u32 *)result)[-3] = real_result->ir_cs
	 *  - ((u32 *)result)[-2] = real_result->ir_eflags
	 *  - ((u32 *)result)[-1] = real_result->ir_esp
	 *  - result->ir_eip      = real_result->ir_ss
	 *  - result->ir_cs       = real_result->ir_es
	 *  - result->ir_eflags   = real_result->ir_ds
	 *  - result->ir_esp      = real_result->ir_fs
	 *  - result->ir_ss       = real_result->ir_gs */
	if (!(result->ir_esp & 0xffff0000) &&
	    !(result->ir_eip & 0xffff0000) &&
	    !(result->ir_eflags & 0xffff0000) &&
	    (((u32 *)result)[-2] & (EFLAGS_VM | EFLAGS_IF)) == (EFLAGS_VM | EFLAGS_IF) &&
	    !(((u32 *)result)[-3] & 0xffff0000) &&
	    ADDR_IS_USER(((u32 *)result)[-4])) {
		/* There is a very good chance that this is a vm86 thread, however we _really_
		 * have to be sure about this, and the only way to be 100% sure, is to unwind
		 * the stack until we hit user-space, at which point we can unwind the %eflags
		 * register to see if it has the VM bit set. */
		u32 userspace_eflags;
		userspace_eflags = get_userspace_eflags(self);
		if (userspace_eflags & EFLAGS_VM) {
			/* It _really_ is a vm86 self! */
			result = (struct irregs_user *)((byte_t *)result -
			                                (SIZEOF_IRREGS_VM86 -
			                                 SIZEOF_IRREGS_USER));
			assertf(result->ir_eflags == userspace_eflags ||
			        (!(result->ir_eflags & EFLAGS_VM) &&
			         result->ir_eip == (uintptr_t)&x86_rpc_user_redirection &&
			         result->ir_cs == SEGMENT_KERNEL_CODE),
			        "Unexpected eflags at %p (found: %#Ix, expected: %#Ix)",
			        &result->ir_eflags, result->ir_eflags, userspace_eflags);
			printk(KERN_TRACE "[x86] Detected iret.vm86 tail at %p\n", result);
		}
	}
#undef stacktop
#ifndef NDEBUG
	if (result->ir_eflags & EFLAGS_VM) {
		assertf(result->ir_eflags & EFLAGS_IF,
		        "User-space IRET without EFLAGS.IF (%p)", result->ir_eflags);
	} else if (result->ir_eip != (uintptr_t)&x86_rpc_user_redirection ||
	           result->ir_cs != SEGMENT_KERNEL_CODE) {
		assertf(SEGMENT_IS_VALID_USERCODE(result->ir_cs),
		        "User-space IRET with invalid CS (%p)", result->ir_cs);
		assertf(result->ir_eflags & EFLAGS_IF,
		        "User-space IRET without EFLAGS.IF (%p)", result->ir_eflags);
	}
#endif /* !NDEBUG */
	return result;
}



/* An arch-specific function used to re-direct the given task's user-space
 * return target to instead point back towards a kernel-space function which is then
 * able to service RPC functions scheduled using `task_(schedule|exec)_user_[s]rpc()'
 * On x86, this is done by modifying the IRET tail at the top of the target thread's stack:
 *   >> FORTASK(self,this_x86_rpc_redirection_iret).ir_eip    = GET_USERCODE_IRET(self)->ir_eip;
 *   >> FORTASK(self,this_x86_rpc_redirection_iret).ir_cs     = GET_USERCODE_IRET(self)->ir_cs;
 *   >> FORTASK(self,this_x86_rpc_redirection_iret).ir_eflags = GET_USERCODE_IRET(self)->ir_eflags;
 *   >> GET_USERCODE_IRET(self)->ir_eip                  = &x86_rpc_user_redirection;
 *   >> GET_USERCODE_IRET(self)->ir_cs                   = SEGMENT_KERNEL_CODE;
 *   >> GET_USERCODE_IRET(self)->ir_eflags               = 0;
 * NOTE: The caller must ensure that preemption is disabled,
 *       and that `self' is hosted by the calling CPU.
 *       Additionally, the caller must ensure that `self' has
 *       neither terminated, nor is actually set up to be a
 *       kernel-space thread.
 * @return: true:  Successfully redirected the given thread.
 * @return: false: The given thread has already been redirected. */
PUBLIC NOBLOCK NONNULL((1)) bool
NOTHROW(FCALL task_enable_redirect_usercode_rpc)(struct task *__restrict self) {
	struct irregs_user *thread_iret;
	assert(!PREEMPTION_ENABLED());
	assert(self->t_cpu == THIS_CPU);
	assert(!(self->t_flags & TASK_FKERNTHREAD));
	/* Check for special case: `self' was interrupted in
	 * `x86_lcall7_main' before it was able to complete its IRET tail.
	 * NOTE: It is sufficient to only check for EIP == ENTRY_OF(x86_lcall7_main),
	 *       since the first thing `x86_lcall7_main' does is to disable preemption,
	 *       meaning that interrupts could only ever happen for the very first
	 *       instruction. */
	if unlikely(self != THIS_TASK &&
	            self->t_sched.s_state->scs_irregs_k.ir_eip == (uintptr_t)x86_lcall7_main) {
		byte_t *fixup;
		u32 eflags;
		fixup = (byte_t *)self->t_sched.s_state;
		assertf((fixup + OFFSET_SCPUSTATE_IRREGS + SIZEOF_IRREGS_KERNEL) ==
		        (byte_t *)(FORTASK(self, this_x86_kernel_psp0) - 16),
		        "Fixup(%p) itn't placed 16 bytes below stack_end(%p) (16 == { IP,CS,SP,SS })",
		        (fixup + OFFSET_SCPUSTATE_IRREGS + SIZEOF_IRREGS_KERNEL),
		        (byte_t *)FORTASK(self, this_x86_kernel_psp0));
		/* Allocate 4 additional bytes. */
		fixup = (byte_t *)memmove(fixup - 4, fixup,
		                          OFFSET_SCPUSTATE_IRREGS +
		                          SIZEOF_IRREGS_KERNEL);
		self->t_sched.s_state = (struct scpustate *)fixup;
		/* Read the original user-space EFLAGS value. */
		eflags = ((struct scpustate *)fixup)->scs_irregs_k.ir_eflags;
		/* Skip the lcall IRET adjustment we're doing outself below by
		 * advancing the instruction pointer from `x86_lcall7_main'
		 * to `x86_lcall7_main_iret' */
		((struct scpustate *)fixup)->scs_irregs_k.ir_eip = (uintptr_t)x86_lcall7_main_iret;
		fixup += OFFSET_SCPUSTATE_IRREGS + SIZEOF_IRREGS_KERNEL;
		/* `fixup' now points at at the u32[5] = { ???, IP, CS, SP, SS }
		 * We want to change this to:   u32[5] = { IP, CS, EFLAGS, SP, SS } */
		((u32 *)fixup)[0] = ((u32 *)fixup)[1];
		((u32 *)fixup)[1] = ((u32 *)fixup)[2];
		((u32 *)fixup)[2] = eflags;
	}
	thread_iret = x86_get_irregs(self);
	if (thread_iret->ir_eip == (uintptr_t)&x86_rpc_user_redirection)
		return false; /* Already redirected. */
	FORTASK(self, this_x86_rpc_redirection_iret).ir_eip    = thread_iret->ir_eip;
	FORTASK(self, this_x86_rpc_redirection_iret).ir_cs     = thread_iret->ir_cs;
	FORTASK(self, this_x86_rpc_redirection_iret).ir_eflags = thread_iret->ir_eflags;
	/* NOTE: The write-order of all of these is highly important,
	 *       so just put a write-barrier around every write.
	 *       For more information, see `irregs_rdip()' and friends. */
	COMPILER_WRITE_BARRIER();
	thread_iret->ir_eip = (uintptr_t)&x86_rpc_user_redirection;
	COMPILER_WRITE_BARRIER();
	thread_iret->ir_cs = SEGMENT_KERNEL_CODE;
	COMPILER_WRITE_BARRIER();
	thread_iret->ir_eflags = 0;
	COMPILER_WRITE_BARRIER();
	return true;
}



/* Personality functions for RPC wrappers. */
INTERN unsigned int
NOTHROW(KCALL x86_rpc_user_redirection_personality)(struct unwind_fde_struct *__restrict fde,
                                                    struct kcpustate *__restrict state,
                                                    byte_t *__restrict UNUSED(reader)) {
	/* When unwinding directly into `x86_rpc_user_redirection', still execute that
	 * frame just as it is, with no modifications made to the register state. */
	if (kcpustate_getpc(state) == (uintptr_t)&x86_rpc_user_redirection)
		return DWARF_PERSO_EXECUTE_HANDLER_NOW;
	return DWARF_PERSO_CONTINUE_UNWIND;
}

INTERN unsigned int
NOTHROW(KCALL x86_rpc_kernel_redirection_personality)(struct unwind_fde_struct *__restrict fde,
                                                      struct kcpustate *__restrict state,
                                                      byte_t *__restrict UNUSED(reader)) {
	/* When unwinding directly into `x86_rpc_user_redirection', still execute that
	 * frame just as it is, with no modifications made to the register state. */
	if (kcpustate_getpc(state) == (uintptr_t)&x86_rpc_kernel_redirection) {
		kcpustate_setpc(state, (uintptr_t)&x86_rpc_kernel_redirection_handler);
		return DWARF_PERSO_EXECUTE_HANDLER_NOW;
	}
	return DWARF_PERSO_CONTINUE_UNWIND;
}

INTERN unsigned int
NOTHROW(KCALL x86_rpc_kernel_redirection_c_personality)(struct unwind_fde_struct *__restrict fde,
                                                        struct kcpustate *__restrict state,
                                                        byte_t *__restrict UNUSED(reader)) {
	/* When unwinding directly into `x86_rpc_user_redirection', still execute that
	 * frame just as it is, with no modifications made to the register state. */
	if (kcpustate_getpc(state) == (uintptr_t)&x86_rpc_kernel_redirection_c) {
		kcpustate_setpc(state, (uintptr_t)&x86_rpc_kernel_redirection_c_handler);
		return DWARF_PERSO_EXECUTE_HANDLER_NOW;
	}
	return DWARF_PERSO_CONTINUE_UNWIND;
}

INTERN unsigned int
NOTHROW(KCALL x86_srpc_kernel_redirection_personality)(struct unwind_fde_struct *__restrict fde,
                                                       struct kcpustate *__restrict state,
                                                       byte_t *__restrict UNUSED(reader)) {
	/* When unwinding directly into `x86_rpc_user_redirection', still execute that
	 * frame just as it is, with no modifications made to the register state. */
	if (kcpustate_getpc(state) == (uintptr_t)&x86_srpc_kernel_redirection) {
		kcpustate_setpc(state, (uintptr_t)&x86_srpc_kernel_redirection_handler);
		return DWARF_PERSO_EXECUTE_HANDLER_NOW;
	}
	return DWARF_PERSO_CONTINUE_UNWIND;
}

INTERN unsigned int
NOTHROW(KCALL x86_srpc_kernel_redirection_c_personality)(struct unwind_fde_struct *__restrict UNUSED(fde),
                                                         struct kcpustate *__restrict state,
                                                         byte_t *__restrict UNUSED(reader)) {
	/* When unwinding directly into `x86_rpc_user_redirection', still execute that
	 * frame just as it is, with no modifications made to the register state. */
	if (kcpustate_getpc(state) == (uintptr_t)&x86_srpc_kernel_redirection_c) {
		kcpustate_setpc(state, (uintptr_t)&x86_srpc_kernel_redirection_c_handler);
		return DWARF_PERSO_EXECUTE_HANDLER_NOW;
	}
	return DWARF_PERSO_CONTINUE_UNWIND;
}

#endif /* !__x86_64__ */







#ifndef __x86_64__
DEFINE_SYSCALL3(syscall_slong_t, modify_ldt,
                syscall_ulong_t, func,
                USER UNCHECKED void *, ptr,
                syscall_ulong_t, bytecount) {
	switch (func) {

	case 2:
		validate_writable(ptr, bytecount);
		memset(ptr, 0, bytecount);
		break;

	case 1:
	case 0x11: {
		struct linux_user_desc *desc;
		unsigned int entry;
		validate_readable(ptr, bytecount);
		if (bytecount < sizeof(struct linux_user_desc))
			THROW(E_BUFFER_TOO_SMALL, sizeof(struct linux_user_desc), bytecount);
		desc  = (struct linux_user_desc *)ptr;
		entry = ATOMIC_READ(desc->entry_number);
		/* We ignore everything except for `base_addr' */
		if ((entry & ~7) == SEGMENT_USER_FSBASE) {
			set_user_fsbase(ATOMIC_READ(desc->base_addr)); /* %fs */
		} else if ((entry & ~7) == SEGMENT_USER_GSBASE) {
			set_user_gsbase(ATOMIC_READ(desc->base_addr)); /* %gs */
		} else {
			THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND, entry);
		}
	}	break;

	default:
		THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND,
		      E_INVALID_ARGUMENT_CONTEXT_GENERIC,
		      func);
		break;
	}
	return 0;
}
#endif /* !__x86_64__ */


DECL_END

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_SCHED_SCHED_C */
