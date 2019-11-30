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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_SYSCALL_PERSONALITY_C
#define GUARD_KERNEL_CORE_ARCH_I386_SYSCALL_PERSONALITY_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/except.h>
#include <kernel/syscall-properties.h>
#include <kernel/types.h>
#include <kernel/user.h>
#include <sched/except-handler.h>

#include <kos/kernel/cpu-state-helpers.h>
#include <kos/kernel/cpu-state.h>

#include <string.h>

#include <librpc/rpc.h>
#include <libunwind/eh_frame.h>
#include <libunwind/unwind.h>

DECL_BEGIN

INTDEF byte_t __x86_syscall_emulate_r_protect_start[];
INTDEF byte_t __x86_syscall_emulate_r_protect_end[];


/* The personality function used to handle exceptions propagated through
 * system calls. - Specifically, the special handling that is required for
 * servicing an RPC as `rpc_serve_user_redirection_all' */
INTERN NONNULL((1, 2, 3)) unsigned int
NOTHROW(KCALL syscall_emulate_r_personality)(struct unwind_fde_struct *__restrict UNUSED(fde),
                                             struct kcpustate *__restrict state,
                                             byte_t *__restrict UNUSED(lsda)) {
	struct icpustate *return_cpustate;
	struct rpc_syscall_info *sc_info;
	COMPILER_IMPURE(); /* ??? */
	/* Check if the exception happened while actually
	 * in the process of servicing the system call. */
	if (kcpustate_getpc(state) <= (uintptr_t)__x86_syscall_emulate_r_protect_start ||
	    kcpustate_getpc(state) > (uintptr_t)__x86_syscall_emulate_r_protect_start)
		return DWARF_PERSO_CONTINUE_UNWIND;
	/* Load cpu state structures from the base of the kernel stack. */
	sc_info         = (struct rpc_syscall_info *)kcpustate_getsp(state);
	return_cpustate = (struct icpustate *)(sc_info + 1);
	x86_userexcept_unwind_i(return_cpustate, sc_info);
}



INTDEF void FCALL /* TODO: Get rid of this */
halt_unhandled_exception(unsigned int error,
                         struct kcpustate *__restrict unwind_state);


LOCAL void
NOTHROW(FCALL scinfo_get32_int80h)(struct rpc_syscall_info *__restrict self,
                                   struct ucpustate const *__restrict state) {
	self->rsi_flags = RPC_SYSCALL_INFO_METHOD_INT80H_32 |
	                  RPC_SYSCALL_INFO_FARGVALID(0) |
	                  RPC_SYSCALL_INFO_FARGVALID(1) |
	                  RPC_SYSCALL_INFO_FARGVALID(2) |
	                  RPC_SYSCALL_INFO_FARGVALID(3) |
	                  RPC_SYSCALL_INFO_FARGVALID(4) |
	                  RPC_SYSCALL_INFO_FARGVALID(5);
	if (ucpustate_getpflags(state) & EFLAGS_CF)
		self->rsi_flags |= RPC_SYSCALL_INFO_FEXCEPT;
	self->rsi_sysno   = gpregs_getpax(&state->ucs_gpregs);
	self->rsi_args[0] = gpregs_getpbx(&state->ucs_gpregs);
	self->rsi_args[1] = gpregs_getpcx(&state->ucs_gpregs);
	self->rsi_args[2] = gpregs_getpdx(&state->ucs_gpregs);
	self->rsi_args[3] = gpregs_getpsi(&state->ucs_gpregs);
	self->rsi_args[4] = gpregs_getpdi(&state->ucs_gpregs);
	self->rsi_args[5] = gpregs_getpbp(&state->ucs_gpregs);
}

LOCAL void
NOTHROW(FCALL scinfo_get32_sysenter)(struct rpc_syscall_info *__restrict self,
                                     struct ucpustate const *__restrict state) {
	unsigned int regcount;
	self->rsi_flags = RPC_SYSCALL_INFO_METHOD_SYSENTER_32 |
	                  RPC_SYSCALL_INFO_FARGVALID(0) |
	                  RPC_SYSCALL_INFO_FARGVALID(1) |
	                  RPC_SYSCALL_INFO_FARGVALID(2) |
	                  RPC_SYSCALL_INFO_FARGVALID(3);
	if (ucpustate_getpflags(state) & EFLAGS_CF)
		self->rsi_flags |= RPC_SYSCALL_INFO_FEXCEPT;
	self->rsi_sysno   = gpregs_getpax(&state->ucs_gpregs);
	self->rsi_args[0] = gpregs_getpbx(&state->ucs_gpregs);
	self->rsi_args[1] = gpregs_getpcx(&state->ucs_gpregs);
	self->rsi_args[2] = gpregs_getpdx(&state->ucs_gpregs);
	self->rsi_args[3] = gpregs_getpsi(&state->ucs_gpregs);
	regcount = kernel_syscall32_regcnt(self->rsi_sysno);
	if (regcount >= 5) {
		struct exception_info old_info;
		memcpy(&old_info, &THIS_EXCEPTION_INFO, sizeof(struct exception_info));
		TRY {
			u32 *ebp = (u32 *)(uintptr_t)(u32)gpregs_getpbp(&state->ucs_gpregs);
			validate_readable(ebp, 4);
			self->rsi_args[4] = __hybrid_atomic_load(ebp[0], __ATOMIC_ACQUIRE);
			self->rsi_flags |= RPC_SYSCALL_INFO_FARGVALID(4);
			if (regcount >= 6) {
				self->rsi_flags |= RPC_SYSCALL_INFO_FARGVALID(5);
				self->rsi_args[5] = __hybrid_atomic_load(ebp[1], __ATOMIC_ACQUIRE);
			}
		} EXCEPT {
			goto restore_exception;
		}
		__IF0 {
restore_exception:
			memcpy(&THIS_EXCEPTION_INFO, &old_info, sizeof(struct exception_info));
		}
	}
}


/* The personality function used to handle exceptions propagated through
 * system calls. - Specifically, the special handling that is required for
 * servicing an RPC as `rpc_serve_user_redirection_all' */
INTERN unsigned int
NOTHROW(KCALL x86_syscall_personality_asm32_int80)(struct unwind_fde_struct *__restrict fde,
                                                   struct kcpustate *__restrict state,
                                                   byte_t *__restrict lsda) {
	struct ucpustate ustate;
	unsigned int error;
	struct rpc_syscall_info info;
	kcpustate_to_ucpustate(state, &ustate);
	{
		unwind_cfa_sigframe_state_t cfa;
		void *pc = (void *)(ucpustate_getpc(&ustate) - 1);
		error = unwind_fde_sigframe_exec(fde, &cfa, pc);
		if unlikely(error != UNWIND_SUCCESS)
			goto err;
		error = unwind_cfa_sigframe_apply(&cfa, fde, pc,
		                                  &unwind_getreg_kcpustate, state,
		                                  &unwind_setreg_ucpustate, &ustate);
		if unlikely(error != UNWIND_SUCCESS)
			goto err;
	}
	/* Check if the return state actually points into user-space,
	 * or alternatively: indicates a user-space redirection. */
	if (ucpustate_iskernel(&ustate) &&
	    ucpustate_getpc(&ustate) != (uintptr_t)&x86_rpc_user_redirection)
		return DWARF_PERSO_ABORT_SEARCH;
	/* System calls encode their vector number as the LSDA pointer, so that
	 * when unwinding we can reverse-engineer that number in order to decide
	 * on special actions to perform based on the called function, as well as
	 * inform user-space of which function caused the exception, as well as
	 * implement system call restarting. */
	gpregs_setpax(&ustate.ucs_gpregs, (uintptr_t)lsda);
	scinfo_get32_int80h(&info, &ustate);
	x86_userexcept_unwind(&ustate, &info);
err:
	halt_unhandled_exception(error, state);
	return DWARF_PERSO_ABORT_SEARCH;
}

/* The personality function used to handle exceptions propagated through
 * system calls. - Specifically, the special handling that is required for
 * servicing an RPC as `rpc_serve_user_redirection_all' */
INTERN unsigned int
NOTHROW(KCALL x86_syscall_personality_asm32_sysenter)(struct unwind_fde_struct *__restrict fde,
                                                      struct kcpustate *__restrict state,
                                                      byte_t *__restrict lsda) {
	struct ucpustate ustate;
	unsigned int error;
	struct rpc_syscall_info info;
	kcpustate_to_ucpustate(state, &ustate);
	{
		unwind_cfa_sigframe_state_t cfa;
		void *pc = (void *)(ucpustate_getpc(&ustate) - 1);
		error = unwind_fde_sigframe_exec(fde, &cfa, pc);
		if unlikely(error != UNWIND_SUCCESS)
			goto err;
		error = unwind_cfa_sigframe_apply(&cfa, fde, pc,
		                                  &unwind_getreg_kcpustate, state,
		                                  &unwind_setreg_ucpustate, &ustate);
		if unlikely(error != UNWIND_SUCCESS)
			goto err;
	}
	/* Check if the return state actually points into user-space,
	 * or alternatively: indicates a user-space redirection. */
	if (ucpustate_iskernel(&ustate) &&
	    ucpustate_getpc(&ustate) != (uintptr_t)&x86_rpc_user_redirection)
		return DWARF_PERSO_ABORT_SEARCH;
	/* System calls encode their vector number as the LSDA pointer, so that
	 * when unwinding we can reverse-engineer that number in order to decide
	 * on special actions to perform based on the called function, as well as
	 * inform user-space of which function caused the exception, as well as
	 * implement system call restarting. */
	gpregs_setpax(&ustate.ucs_gpregs, (uintptr_t)lsda);
	scinfo_get32_sysenter(&info, &ustate);
	x86_userexcept_unwind(&ustate, &info);
err:
	halt_unhandled_exception(error, state);
	return DWARF_PERSO_ABORT_SEARCH;
}



DECL_END

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_SYSCALL_PERSONALITY_C */
