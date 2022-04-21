/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_CORE_ARCH_I386_SCHED_RPC_C
#define GUARD_KERNEL_CORE_ARCH_I386_SCHED_RPC_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/rt/except-handler.h>
#include <kernel/x86/syscall-tables.h>
#include <sched/cpu.h>
#include <sched/rpc-internal.h>
#include <sched/task.h>

#include <hybrid/sched/preemption.h>

#include <asm/cpu-flags.h>
#include <kos/kernel/cpu-state-compat.h>
#include <kos/kernel/cpu-state-helpers.h>
#include <kos/kernel/cpu-state.h>

#include <assert.h>
#include <stddef.h>
#include <string.h>

DECL_BEGIN

/* The following offsets are currently being hard-coded in `rpc.S' */
STATIC_ASSERT(offsetof(struct rpc_context, rc_context) == 0);
#ifdef __x86_64__
STATIC_ASSERT(offsetof(struct rpc_context, rc_state) == 8);
#else /* __x86_64__ */
STATIC_ASSERT(offsetof(struct rpc_context, rc_state) == 4);
#endif /* !__x86_64__ */

/* Restore function for functions pushed by `task_asyncrpc_push()'
 * This  function   is   entered   with  the   stack   set   like:
 *   0(%Psp): struct rpc_context */
extern void ASMCALL x86_task_asyncrpc_restore(void);

/* Arch-specific function:
 * Alter the given `state' to inject a call to `func'. The context
 * argument passed to  `func' will use  `RPC_REASONCTX_ASYNC_KERN'
 * or `RPC_REASONCTX_SYSRET' as reason. */
PUBLIC NOBLOCK NOPREEMPT ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) struct scpustate *
NOTHROW(FCALL task_asyncrpc_push)(struct scpustate *__restrict state,
                                  prpc_exec_callback_t func,
                                  void *cookie) {
	byte_t *sp;
	rpc_cpustate_t *rc_state;
	struct scpustate *result_sstate;
	struct rpc_context *rc;
	bool isuser = scpustate_isuser(state);

#ifdef __x86_64__
	/* Convert `state' into a `struct icpustate'. On x86_64, that can
	 * easily  be done by  skipping over the  first couple of fields. */
	STATIC_ASSERT(SIZEOF_SCPUSTATE64 - OFFSET_SCPUSTATE64_GPREGSNSP == SIZEOF_ICPUSTATE64);
	STATIC_ASSERT(OFFSET_SCPUSTATE64_GPREGSNSP - OFFSET_SCPUSTATE64_GPREGSNSP == OFFSET_ICPUSTATE64_GPREGSNSP);
	STATIC_ASSERT(OFFSET_SCPUSTATE64_IRREGS - OFFSET_SCPUSTATE64_GPREGSNSP == OFFSET_ICPUSTATE64_IRREGS);
	sp       = (byte_t *)&state->scs_gpregs; /* Have `sp' point at the `icpustate' portion of `state' */
	rc_state = (struct icpustate *)sp;
	sp -= offsetof(struct rpc_context, rc_scinfo); /* Allocate space for the `struct rpc_context' */
	rc = (struct rpc_context *)sp;
	sp -= sizeof(void *); /* Allocate space for the return CPU state. */
	result_sstate = (struct scpustate *)(sp - (OFFSET_SCPUSTATE_IRREGS + SIZEOF_IRREGS_KERNEL));
	/* Copy everything except the IRET tail into the new CPU state. */
	memcpy(result_sstate, state, OFFSET_SCPUSTATE64_IRREGS);
#else /* __x86_64__ */
	STATIC_ASSERT(OFFSET_SCPUSTATE32_GPREGS == OFFSET_ICPUSTATE32_GPREGS);
	STATIC_ASSERT(OFFSET_SCPUSTATE32_SGREGS + OFFSET_SGREGS32_FS == OFFSET_ICPUSTATE32_FS + 4);
	STATIC_ASSERT(OFFSET_SCPUSTATE32_SGREGS + OFFSET_SGREGS32_ES == OFFSET_ICPUSTATE32_ES + 4);
	STATIC_ASSERT(OFFSET_SCPUSTATE32_SGREGS + OFFSET_SGREGS32_DS == OFFSET_ICPUSTATE32_DS + 4);
	u32 saved_gs = state->scs_sgregs.sg_gs;
	/* To inplace-convert a `struct scpustate' into `struct icpustate', we essentially
	 * just have to pluck out the `scs_sgregs.sg_gs' field by memmoveup-ing everything
	 * that comes before it by 4 bytes. */
	rc_state = (rpc_cpustate_t *)memmoveup((byte_t *)state + 4, state, OFFSET_ICPUSTATE32_FS);
	sp       = (byte_t *)rc_state;
	sp -= offsetof(struct rpc_context, rc_scinfo); /* Allocate space for the `struct rpc_context' */
	rc = (struct rpc_context *)sp;
	sp -= sizeof(void *); /* Allocate space for the return CPU state. */
	result_sstate = (struct scpustate *)(sp - (OFFSET_SCPUSTATE_IRREGS + SIZEOF_IRREGS_KERNEL));
	/* Fill in most of `result_sstate' */
	memcpy(&result_sstate->scs_gpregs, &rc_state->ics_gpregs, sizeof(struct gpregs32));
	memcpy((byte_t *)&result_sstate->scs_sgregs + OFFSET_SGREGS32_FS,
	       (byte_t *)&rc_state + OFFSET_ICPUSTATE32_FS, 3 * 4);
	result_sstate->scs_sgregs.sg_gs = saved_gs;
	result_sstate->scs_sgregs.sg_ds = SEGMENT_USER_DATA_RPL;
	result_sstate->scs_sgregs.sg_es = SEGMENT_USER_DATA_RPL;
	result_sstate->scs_sgregs.sg_fs = SEGMENT_KERNEL_FSBASE;
#endif /* !__x86_64__ */

	/* Setup everything such that execution resumes at `func' */
	*(uintptr_t *)sp = (uintptr_t)&x86_task_asyncrpc_restore;
#ifdef __x86_64__
	result_sstate->scs_irregs.ir_ss        = SEGMENT_KERNEL_DATA0;
	result_sstate->scs_irregs.ir_Psp       = (uintptr_t)sp;
#endif /* __x86_64__ */

	result_sstate->scs_irregs.ir_Pip       = (uintptr_t)func;
	result_sstate->scs_irregs.ir_cs        = SEGMENT_KERNEL_CODE;
	result_sstate->scs_irregs.ir_Pflags    = rc_state->ics_irregs.ir_Pflags & ~(EFLAGS_DF | EFLAGS_IF);
	result_sstate->scs_gpregs.gp_R_fcall0P = (uintptr_t)rc;
	result_sstate->scs_gpregs.gp_R_fcall1P = (uintptr_t)cookie;

	/* Fill in RPC context information. */
	rc->rc_state   = rc_state;
	rc->rc_context = isuser ? RPC_REASONCTX_SYSRET
	                        : RPC_REASONCTX_ASYNC_KERN;
	return result_sstate;
}



/* Saved IRET tail for `x86_userexcept_sysret' */
PUBLIC ATTR_SECTION(".data.pertask.early")
ATTR_ALIGN(struct irregs_kernel) this_x86_sysret_iret = { 0 };


/* Arch-specific function:
 * If not done already, modify  `state' such that rather than  returning
 * to  user-space (which the  caller is responsible to  ensure by use of
 * `assert(icpustate_isuser(state))'), it will make a round-trip through
 * arch-specific wrappers which  eventually call  `userexcept_sysret()'.
 * Once that function  returns, execution will  finally resume in  user-
 * space,  unless  this function  (or `userexcept_sysret_inject_nopr()')
 * was called yet again.
 * NOTE: The  given `state' must point to user-space, and be located at
 *       the very end of the kernel stack. This requirement is asserted
 *       internally by this function! */
PUBLIC NOBLOCK NOPREEMPT ATTR_RETNONNULL WUNUSED NONNULL((1)) struct icpustate *
NOTHROW(FCALL userexcept_sysret_inject_with_state_nopr)(struct icpustate *__restrict state) {
#ifdef __x86_64__
	struct task *me = THIS_TASK;
	struct irregs *thread_save;
	assert(!PREEMPTION_ENABLED());
	assert(!(me->t_flags & TASK_FTERMINATING));
	assert(!(me->t_flags & TASK_FKERNTHREAD));
	assert(&state->ics_irregs == x86_get_irregs(me));
	if (state->ics_irregs.ir_rip == (uintptr_t)&x86_userexcept_sysret)
		return state; /* Already redirected. */

	/* Save the original IRET tail. */
	thread_save = &FORTASK(me, this_x86_sysret_iret);
	thread_save->ir_rip    = state->ics_irregs.ir_rip;
	thread_save->ir_cs     = state->ics_irregs.ir_cs;
	thread_save->ir_rflags = state->ics_irregs.ir_rflags;
	thread_save->ir_ss     = state->ics_irregs.ir_ss;
	thread_save->ir_rsp    = state->ics_irregs.ir_rsp;
	COMPILER_READ_BARRIER();
	/* NOTE: The write-order of all  of these is highly  important,
	 *       so  just  put  a  write-barrier  around  every  write.
	 *       For more information, see `irregs_rdip()' and friends. */
	COMPILER_WRITE_BARRIER();
	state->ics_irregs.ir_rip = (uintptr_t)&x86_userexcept_sysret;
	COMPILER_WRITE_BARRIER();
	state->ics_irregs.ir_cs = SEGMENT_KERNEL_CODE;
	COMPILER_WRITE_BARRIER();
	state->ics_irregs.ir_rflags = 0;
	COMPILER_WRITE_BARRIER();
	state->ics_irregs.ir_ss  = SEGMENT_KERNEL_DATA0;
	COMPILER_WRITE_BARRIER();
	state->ics_irregs.ir_rsp = (u64)(&state->ics_irregs + 1);
	COMPILER_WRITE_BARRIER();
#else /* __x86_64__ */
	struct task *me = THIS_TASK;
	assert(!PREEMPTION_ENABLED());
	assert(!(me->t_flags & TASK_FTERMINATING));
	assert(!(me->t_flags & TASK_FKERNTHREAD));
	assert(&state->ics_irregs_u == x86_get_irregs(me));
	if (state->ics_irregs_u.ir_eip == (uintptr_t)&x86_userexcept_sysret)
		return state; /* Already redirected. */
	FORTASK(me, this_x86_sysret_iret).ir_eip    = state->ics_irregs_u.ir_eip;
	FORTASK(me, this_x86_sysret_iret).ir_cs     = state->ics_irregs_u.ir_cs;
	FORTASK(me, this_x86_sysret_iret).ir_eflags = state->ics_irregs_u.ir_eflags;
	COMPILER_READ_BARRIER();
	/* NOTE: The write-order of all  of these is highly  important,
	 *       so  just  put  a  write-barrier  around  every  write.
	 *       For more information, see `irregs_rdip()' and friends. */
	COMPILER_WRITE_BARRIER();
	state->ics_irregs_u.ir_eip = (uintptr_t)&x86_userexcept_sysret;
	COMPILER_WRITE_BARRIER();
	state->ics_irregs_u.ir_cs = SEGMENT_KERNEL_CODE;
	COMPILER_WRITE_BARRIER();
	state->ics_irregs_u.ir_eflags = 0;
	COMPILER_WRITE_BARRIER();
#endif /* !__x86_64__ */
	return state;
}


/* Arch-specific function:
 * Inject a call to `userexcept_sysret()' that is performed before `thread'
 * returns  back to user-space the next time. This function works correctly
 * even when `thread == THIS_TASK', or when the injection has already  been
 * performed (either by a  prior call to  this function, or  by use of  the
 * sibling function `userexcept_sysret_inject_with_state_nopr()'), in which
 * case the call is silent no-op.
 *
 * However, the caller still has to ensure `thread' won't make any  kernel-
 * user transitions for the duration of this call. The only way this can be
 * done, which this function also internally asserts to be the case, is  by
 * disabling preemption (hence the `NOPREEMPT'), and ensuring that `thread'
 * is hosted by  the current cpu  (iow: `thread->t_cpu == THIS_CPU').  When
 * either of these conditions aren't met, this function causes kernel panic
 *
 * Additionally, the caller must also ensure that `thread' is still running
 * and  has  yet   to  terminate  (iow:   `TASK_FTERMINATING'  isn't   set) */
PUBLIC NOBLOCK NOPREEMPT NONNULL((1)) void
NOTHROW(FCALL userexcept_sysret_inject_nopr)(struct task *__restrict thread) {
#ifdef __x86_64__
	struct irregs_user *thread_iret;
	struct irregs_user *thread_save;
	assert(!PREEMPTION_ENABLED());
	assert(thread->t_cpu == THIS_CPU);
	assert(!(thread->t_flags & TASK_FKERNTHREAD));
	thread_iret = x86_get_irregs(thread);
	if (thread_iret->ir_rip == (uintptr_t)&x86_userexcept_sysret)
		return; /* Already redirected. */
	/* Save the original IRET tail. */
	thread_save = &FORTASK(thread, this_x86_sysret_iret);
	thread_save->ir_rip    = thread_iret->ir_rip;
	thread_save->ir_cs     = thread_iret->ir_cs;
	thread_save->ir_rflags = thread_iret->ir_rflags;
	thread_save->ir_ss     = thread_iret->ir_ss;
	thread_save->ir_rsp    = thread_iret->ir_rsp;
	COMPILER_READ_BARRIER();
	/* NOTE: The write-order of all  of these is highly  important,
	 *       so  just  put  a  write-barrier  around  every  write.
	 *       For more information, see `irregs_rdip()' and friends. */
	COMPILER_WRITE_BARRIER();
	thread_iret->ir_rip = (uintptr_t)&x86_userexcept_sysret;
	COMPILER_WRITE_BARRIER();
	thread_iret->ir_cs = SEGMENT_KERNEL_CODE;
	COMPILER_WRITE_BARRIER();
	thread_iret->ir_rflags = 0;
	COMPILER_WRITE_BARRIER();
	thread_iret->ir_ss  = SEGMENT_KERNEL_DATA0;
	COMPILER_WRITE_BARRIER();
	thread_iret->ir_rsp = (u64)(thread_iret + 1);
	COMPILER_WRITE_BARRIER();
#else /* __x86_64__ */
	struct irregs_user *thread_iret;
	assert(!PREEMPTION_ENABLED());
	assert(thread->t_cpu == THIS_CPU);
	assert(!(thread->t_flags & TASK_FKERNTHREAD));
	thread_iret = x86_get_irregs(thread);
	if (thread_iret->ir_eip == (uintptr_t)&x86_userexcept_sysret)
		return; /* Already redirected. */
	FORTASK(thread, this_x86_sysret_iret).ir_eip    = thread_iret->ir_eip;
	FORTASK(thread, this_x86_sysret_iret).ir_cs     = thread_iret->ir_cs;
	FORTASK(thread, this_x86_sysret_iret).ir_eflags = thread_iret->ir_eflags;
	COMPILER_READ_BARRIER();
	/* NOTE: The write-order of all  of these is highly  important,
	 *       so  just  put  a  write-barrier  around  every  write.
	 *       For more information, see `irregs_rdip()' and friends. */
	COMPILER_WRITE_BARRIER();
	thread_iret->ir_eip = (uintptr_t)&x86_userexcept_sysret;
	COMPILER_WRITE_BARRIER();
	thread_iret->ir_cs = SEGMENT_KERNEL_CODE;
	COMPILER_WRITE_BARRIER();
	thread_iret->ir_eflags = 0;
	COMPILER_WRITE_BARRIER();
#endif /* !__x86_64__ */
}



/* Arch-specific function: Behaves identical to:
 * >> preemption_flag_t was;
 * >> preemption_pushoff(&was);
 * >> userexcept_sysret_inject_nopr(THIS_TASK);
 * >> preemption_pop(&was);
 * This function can be used to force checks for RPCs (including  posix
 * signals) to be performed _after_ a  system has completed (even in  a
 * scenario where the system call completes successfully). This kind of
 * functionality is required for some POSIX-signal-related system calls */
PUBLIC NOBLOCK void NOTHROW(FCALL userexcept_sysret_inject_self)(void) {
	preemption_flag_t was;
	struct task *thread = THIS_TASK;
#ifdef __x86_64__
	struct irregs_user *thread_iret;
	struct irregs_user *thread_save;
	assert(!(thread->t_flags & TASK_FKERNTHREAD));
	thread_iret = x86_get_irregs(thread);
	preemption_pushoff(&was);
	if (thread_iret->ir_rip != (uintptr_t)&x86_userexcept_sysret) {
		/* Save the original IRET tail. */
		thread_save = &FORTASK(thread, this_x86_sysret_iret);
		thread_save->ir_rip    = thread_iret->ir_rip;
		thread_save->ir_cs     = thread_iret->ir_cs;
		thread_save->ir_rflags = thread_iret->ir_rflags;
		thread_save->ir_ss     = thread_iret->ir_ss;
		thread_save->ir_rsp    = thread_iret->ir_rsp;
		COMPILER_READ_BARRIER();
		/* NOTE: The write-order of all  of these is highly  important,
		 *       so  just  put  a  write-barrier  around  every  write.
		 *       For more information, see `irregs_rdip()' and friends. */
		COMPILER_WRITE_BARRIER();
		thread_iret->ir_rip = (uintptr_t)&x86_userexcept_sysret;
		COMPILER_WRITE_BARRIER();
		thread_iret->ir_cs = SEGMENT_KERNEL_CODE;
		COMPILER_WRITE_BARRIER();
		thread_iret->ir_rflags = 0;
		COMPILER_WRITE_BARRIER();
		thread_iret->ir_ss  = SEGMENT_KERNEL_DATA0;
		COMPILER_WRITE_BARRIER();
		thread_iret->ir_rsp = (u64)(thread_iret + 1);
		COMPILER_WRITE_BARRIER();
	}
	preemption_pop(&was);
#else /* __x86_64__ */
	struct irregs_user *thread_iret;
	assert(thread->t_cpu == THIS_CPU);
	assert(!(thread->t_flags & TASK_FKERNTHREAD));
	thread_iret = x86_get_irregs(thread);
	preemption_pushoff(&was);
	if (thread_iret->ir_eip != (uintptr_t)&x86_userexcept_sysret) {
		FORTASK(thread, this_x86_sysret_iret).ir_eip    = thread_iret->ir_eip;
		FORTASK(thread, this_x86_sysret_iret).ir_cs     = thread_iret->ir_cs;
		FORTASK(thread, this_x86_sysret_iret).ir_eflags = thread_iret->ir_eflags;
		COMPILER_READ_BARRIER();
		/* NOTE: The write-order of all  of these is highly  important,
		 *       so  just  put  a  write-barrier  around  every  write.
		 *       For more information, see `irregs_rdip()' and friends. */
		COMPILER_WRITE_BARRIER();
		thread_iret->ir_eip = (uintptr_t)&x86_userexcept_sysret;
		COMPILER_WRITE_BARRIER();
		thread_iret->ir_cs = SEGMENT_KERNEL_CODE;
		COMPILER_WRITE_BARRIER();
		thread_iret->ir_eflags = 0;
		COMPILER_WRITE_BARRIER();
	}
	preemption_pop(&was);
#endif /* !__x86_64__ */
}

DECL_END

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_SCHED_RPC_C */
