/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_CORE_ARCH_I386_SCHED_RPC_C
#define GUARD_KERNEL_CORE_ARCH_I386_SCHED_RPC_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#ifdef CONFIG_USE_NEW_RPC
#include <kernel/rt/except-handler.h>
#include <kernel/x86/syscall-tables.h>
#include <sched/cpu.h>
#include <sched/rpc-internal.h>
#include <sched/task.h>

#include <kos/kernel/cpu-state-compat.h>
#include <kos/kernel/cpu-state-helpers.h>
#include <kos/kernel/cpu-state.h>

#include <assert.h>
#include <string.h>

DECL_BEGIN

/* Arch-specific function:
 * Alter the given `state' to inject a call to `func'. The context
 * argument passed to  `func' will use  `RPC_REASONCTX_ASYNC_KERN'
 * or `RPC_REASONCTX_SYSRET' as reason. */
PUBLIC NOBLOCK NOPREEMPT ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) struct scpustate *
NOTHROW(FCALL task_asyncrpc_push)(struct scpustate *__restrict state,
                                  prpc_exec_callback_t func,
                                  void *cookie) {
#ifdef __x86_64__
	struct rpc_context *rc;
	struct ATTR_PACKED buffer {
		struct gpregs b_gpregs; /* General purpose registers. */
		u32 b_gs;               /* G segment register (Usually `SEGMENT_USER_GSBASE_RPL') */
	};
	unsigned int reason;
	struct icpustate *istate;
	struct scpustate *result;
	struct buffer regbuf;
	byte_t *dest;
	void *argbuffer;
	reason = scpustate_isuser(state)
	         ? RPC_REASONCTX_SYSRET
	         : RPC_REASONCTX_ASYNC_KERN;
	memcpy(&regbuf, state, sizeof(regbuf));
	dest = (byte_t *)state + sizeof(regbuf);

	/* DEST: fs, es, ds, eip, cs, eflags, [...] */
	dest -= sizeof(struct gpregs);
	memcpy(dest, &regbuf.b_gpregs, sizeof(struct gpregs));

	/* `dest' now points to a valid `struct icpustate' (which will be passed to `func') */
	istate = (struct icpustate *)dest;

	/* Allocate memory for `struct rpc_context' passed to the function */
	dest -= sizeof(struct rpc_context);
	rc = (struct rpc_context *)dest;

	/* Push the return address for `func' */

	/* TODO */

	result->scs_sgregs.sg_gs     = regbuf.b_gs;
	result->scs_irregs.ir_rip    = (uintptr_t)func;
	result->scs_irregs.ir_ss     = SEGMENT_KERNEL_DATA0;
	result->scs_irregs.ir_rsp    = (u64)dest;
	result->scs_irregs.ir_cs     = SEGMENT_KERNEL_CODE;
	result->scs_irregs.ir_rflags = istate->ics_irregs.ir_Pflags;
	return result;
#else /* __x86_64__ */
	/* TODO */
#endif /* !__x86_64__ */
}



/* Arch-specific function:
 * If not done already, modify  `state' such that rather than  returning
 * to  user-space (which the  caller is responsible to  ensure by use of
 * `assert(icpustate_isuser(state))'), it will make a round-trip through
 * arch-specific wrappers which  eventually call  `userexcept_sysret()'.
 * Once that function  returns, execution will  finally resume in  user-
 * space,  unless  this function  (or  `userexcept_sysret_inject()') was
 * called yet again.
 * NOTE: The  given `state' must point to user-space, and be located at
 *       the very end of the kernel stack. This requirement is asserted
 *       internally by this function! */
PUBLIC NOPREEMPT ATTR_RETNONNULL WUNUSED NONNULL((1)) struct icpustate *
NOTHROW(FCALL userexcept_sysret_inject_with_state)(struct icpustate *__restrict state) {
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
	thread_save = &FORTASK(me, this_x86_rpc_redirection_iret);
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
	FORTASK(me, this_x86_rpc_redirection_iret).ir_eip    = state->ics_irregs_u.ir_eip;
	FORTASK(me, this_x86_rpc_redirection_iret).ir_cs     = state->ics_irregs_u.ir_cs;
	FORTASK(me, this_x86_rpc_redirection_iret).ir_eflags = state->ics_irregs_u.ir_eflags;
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
 * sibling function `userexcept_sysret_inject_with_state()'), in which case
 * the call is silent no-op.
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
PUBLIC NOPREEMPT WUNUSED NONNULL((1)) void
NOTHROW(FCALL userexcept_sysret_inject)(struct task *__restrict thread) {
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
	thread_save = &FORTASK(thread, this_x86_rpc_redirection_iret);
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
#ifndef CONFIG_X86_EMULATE_LCALL7
	/* Check for special case: `thread' was interrupted in
	 * `x86_syscall32_lcall7' before it was able to complete its IRET tail.
	 * NOTE: It is sufficient to only  check for EIP ==  ENTRY_OF(x86_syscall32_lcall7),
	 *       since the first thing `x86_syscall32_lcall7' does is to disable preemption,
	 *       meaning  that  interrupts  could  only  ever  happen  for  the  very  first
	 *       instruction. */
	if unlikely(thread != THIS_TASK &&
	            FORTASK(thread, this_sstate)->scs_irregs.ir_eip == (uintptr_t)(void *)&x86_syscall32_lcall7) {
		byte_t *fixup;
		u32 eflags;
		fixup = (byte_t *)FORTASK(thread, this_sstate);
		assertf((fixup + OFFSET_SCPUSTATE_IRREGS + SIZEOF_IRREGS_KERNEL) ==
		        (byte_t *)(FORTASK(thread, this_x86_kernel_psp0) - 16),
		        "Fixup(%p) itn't placed 16 bytes below stack_end(%p) (16 == { IP,CS,SP,SS })",
		        (fixup + OFFSET_SCPUSTATE_IRREGS + SIZEOF_IRREGS_KERNEL),
		        (byte_t *)FORTASK(thread, this_x86_kernel_psp0));
		/* Allocate 4 additional bytes. */
		fixup = (byte_t *)memmovedown(fixup - 4, fixup,
		                              OFFSET_SCPUSTATE_IRREGS +
		                              SIZEOF_IRREGS_KERNEL);
		FORTASK(thread, this_sstate) = (struct scpustate *)fixup;
		/* Read the original user-space EFLAGS value. */
		eflags = ((struct scpustate *)fixup)->scs_irregs.ir_eflags;
		/* Skip the lcall IRET adjustment  we're doing ourself below  by
		 * advancing the instruction pointer from `x86_syscall32_lcall7'
		 * to `x86_syscall32_lcall7_iret' */
		((struct scpustate *)fixup)->scs_irregs.ir_eip = (uintptr_t)(void *)&x86_syscall32_lcall7_iret;
		fixup += OFFSET_SCPUSTATE_IRREGS + SIZEOF_IRREGS_KERNEL;
		/* `fixup' now points at at the u32[5] = { ???, IP, CS, SP, SS }
		 * We want to change this to:   u32[5] = { IP, CS, EFLAGS, SP, SS } */
		((u32 *)fixup)[0] = ((u32 *)fixup)[1];
		((u32 *)fixup)[1] = ((u32 *)fixup)[2];
		((u32 *)fixup)[2] = eflags;
	}
#endif /* !CONFIG_X86_EMULATE_LCALL7 */
	thread_iret = x86_get_irregs(thread);
	if (thread_iret->ir_eip == (uintptr_t)&x86_userexcept_sysret)
		return; /* Already redirected. */
	FORTASK(thread, this_x86_rpc_redirection_iret).ir_eip    = thread_iret->ir_eip;
	FORTASK(thread, this_x86_rpc_redirection_iret).ir_cs     = thread_iret->ir_cs;
	FORTASK(thread, this_x86_rpc_redirection_iret).ir_eflags = thread_iret->ir_eflags;
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


DECL_END
#endif /* !CONFIG_USE_NEW_RPC */

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_SCHED_RPC_C */
