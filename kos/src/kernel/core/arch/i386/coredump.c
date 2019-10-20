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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_COREDUMP_C
#define GUARD_KERNEL_CORE_ARCH_I386_COREDUMP_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/coredump.h>
#include <kernel/except.h>
#include <kernel/syscall.h>
#include <kernel/user.h>
#include <sched/cred.h>
#include <sched/rpc.h>

#include <hybrid/host.h>

#include <asm/registers.h>
#include <kos/bits/exception_data.h>
#include <kos/bits/exception_data32.h>
#include <kos/except-inval.h>
#include <kos/kernel/cpu-state.h>
#include <kos/kernel/cpu-state32.h>
#include <sys/wait.h>

#include <malloca.h>
#include <stddef.h>
#include <string.h>

#include <librpc/rpc.h>
#include <libunwind/api.h>
#ifdef __x86_64__
#include <bits/siginfo-convert.h>
#include <kos/bits/exception_data-convert.h>
#endif /* __x86_64__ */

DECL_BEGIN


LOCAL NOBLOCK void
NOTHROW(KCALL user_icpu_to_ucpu)(struct icpustate const *__restrict state,
                                 struct ucpustate *__restrict ust) {
#ifdef __x86_64__
#error TODO
#else /* __x86_64__ */
	ust->ucs_gpregs        = state->ics_gpregs;
	ust->ucs_sgregs.sg_ds  = state->ics_ds16;
	ust->ucs_sgregs.sg_es  = state->ics_es16;
	ust->ucs_sgregs.sg_fs  = state->ics_fs16;
	ust->ucs_sgregs.sg_gs  = __rdgs();
	ust->ucs_cs            = irregs_rdcs(&state->ics_irregs);
	ust->ucs_ss            = state->ics_irregs_u.ir_ss16;
	ust->ucs_eflags        = irregs_rdflags(&state->ics_irregs);
	ust->ucs_eip           = irregs_rdip(&state->ics_irregs);
	ust->ucs_gpregs.gp_esp = state->ics_irregs_u.ir_esp;
#endif /* !__x86_64__ */
}

LOCAL NOBLOCK void KCALL
user_ucpu32_to_ucpu(struct icpustate const *__restrict return_state,
                    struct ucpustate32 const *__restrict ust32,
                    struct ucpustate *__restrict ust) {
#ifdef __x86_64__
#error TODO
#else /* __x86_64__ */
	u32 eflags_mask;
	memcpy(ust, ust32, sizeof(struct ucpustate));
	eflags_mask = (u32)cred_allow_eflags_modify_mask();
	if unlikely((irregs_rdflags(&return_state->ics_irregs) & ~eflags_mask) !=
	            (ust->ucs_eflags & ~eflags_mask)) {
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_SIGRETURN_REGISTER,
		      X86_REGISTER_MISC_EFLAGS, ust->ucs_eflags);
	}
	ust->ucs_cs           = ust->ucs_cs16;
	ust->ucs_ss           = ust->ucs_ss16;
	ust->ucs_sgregs.sg_gs = ust->ucs_sgregs.sg_gs16;
	ust->ucs_sgregs.sg_fs = ust->ucs_sgregs.sg_fs16;
	ust->ucs_sgregs.sg_es = ust->ucs_sgregs.sg_es16;
	ust->ucs_sgregs.sg_ds = ust->ucs_sgregs.sg_ds16;
	if (!irregs_isvm86(&return_state->ics_irregs)) {
		/* Validate segment register indices before actually restoring them. */
		if unlikely(!SEGMENT_IS_VALID_USERCODE(ust->ucs_cs)) {
			THROW(E_INVALID_ARGUMENT_BAD_VALUE,
			      E_INVALID_ARGUMENT_CONTEXT_SIGRETURN_REGISTER,
			      X86_REGISTER_SEGMENT_CS, ust->ucs_cs);
		}
		if unlikely(!SEGMENT_IS_VALID_USERDATA(ust->ucs_sgregs.sg_gs)) {
			THROW(E_INVALID_ARGUMENT_BAD_VALUE,
			      E_INVALID_ARGUMENT_CONTEXT_SIGRETURN_REGISTER,
			      X86_REGISTER_SEGMENT_GS, ust->ucs_sgregs.sg_gs);
		}
		if unlikely(!SEGMENT_IS_VALID_USERDATA(ust->ucs_sgregs.sg_fs)) {
			THROW(E_INVALID_ARGUMENT_BAD_VALUE,
			      E_INVALID_ARGUMENT_CONTEXT_SIGRETURN_REGISTER,
			      X86_REGISTER_SEGMENT_FS, ust->ucs_sgregs.sg_fs);
		}
		if unlikely(!SEGMENT_IS_VALID_USERDATA(ust->ucs_sgregs.sg_es)) {
			THROW(E_INVALID_ARGUMENT_BAD_VALUE,
			      E_INVALID_ARGUMENT_CONTEXT_SIGRETURN_REGISTER,
			      X86_REGISTER_SEGMENT_ES, ust->ucs_sgregs.sg_es);
		}
		if unlikely(!SEGMENT_IS_VALID_USERDATA(ust->ucs_sgregs.sg_ds)) {
			THROW(E_INVALID_ARGUMENT_BAD_VALUE,
			      E_INVALID_ARGUMENT_CONTEXT_SIGRETURN_REGISTER,
			      X86_REGISTER_SEGMENT_DS, ust->ucs_sgregs.sg_ds);
		}
		if unlikely(!SEGMENT_IS_VALID_USERDATA(ust->ucs_ss)) {
			THROW(E_INVALID_ARGUMENT_BAD_VALUE,
			      E_INVALID_ARGUMENT_CONTEXT_SIGRETURN_REGISTER,
			      X86_REGISTER_SEGMENT_SS, ust->ucs_ss);
		}
	}
#endif /* !__x86_64__ */
}

#ifndef CONFIG_COREDUMP_TRACEBACK_LIMIT
#define CONFIG_COREDUMP_TRACEBACK_LIMIT 128
#endif /* !CONFIG_COREDUMP_TRACEBACK_LIMIT */


INTERN struct icpustate *FCALL
coredump32_impl(struct icpustate *__restrict return_state,
                USER UNCHECKED struct ucpustate32 const *curr_state,
                USER UNCHECKED struct ucpustate32 const *orig_state,
                USER UNCHECKED u32 const *const *traceback_vector, size_t traceback_length,
                USER UNCHECKED struct exception_data32 const *exception,
                syscall_ulong_t unwind_error) {
	struct ucpustate curr_ustate, orig_ustate;
	void **utb_vector;
	unsigned int signo = SIGILL;
	validate_readable_opt(exception,
	                      unwind_error == UNWIND_SUCCESS ? sizeof(exception_data32)
	                                                     : sizeof(siginfo32_t));
	if (!curr_state && !orig_state) {
		user_icpu_to_ucpu(return_state, &curr_ustate);
		memcpy(&orig_ustate, &curr_ustate, sizeof(struct ucpustate));
		traceback_vector = NULL;
		traceback_length = 0;
	} else if (!curr_state) {
		validate_readable(orig_state, sizeof(*orig_state));
		user_ucpu32_to_ucpu(return_state, orig_state, &orig_ustate);
		memcpy(&curr_ustate, &orig_ustate, sizeof(struct ucpustate));
		traceback_vector = NULL;
		traceback_length = 0;
	} else if (!orig_state) {
		validate_readable(curr_state, sizeof(*curr_state));
		user_ucpu32_to_ucpu(return_state, curr_state, &curr_ustate);
		memcpy(&orig_ustate, &curr_ustate, sizeof(struct ucpustate));
		traceback_vector = NULL;
		traceback_length = 0;
	} else {
		validate_readable(curr_state, sizeof(*curr_state));
		validate_readable(orig_state, sizeof(*orig_state));
		user_ucpu32_to_ucpu(return_state, curr_state, &curr_ustate);
		user_ucpu32_to_ucpu(return_state, orig_state, &orig_ustate);
		if (memcmp(&curr_ustate, &orig_ustate, sizeof(ucpustate)) == 0) {
			traceback_vector = NULL;
			traceback_length = 0;
		}
	}
	utb_vector = NULL;
	if (traceback_length > CONFIG_COREDUMP_TRACEBACK_LIMIT)
		traceback_length = CONFIG_COREDUMP_TRACEBACK_LIMIT;
	if (traceback_length != 0) {
		utb_vector = (void **)malloca(traceback_length * sizeof(void *));
		TRY {
			size_t i;
			for (i = 0; i < traceback_length; ++i)
				utb_vector[i] = (void *)(uintptr_t)traceback_vector[i];
		} EXCEPT {
			freea(utb_vector);
			RETHROW();
		}
	}
	TRY {
		if (!exception) {
			/* Coredump not caused by an exception or signal. */
			coredump_create(&curr_ustate,
			                utb_vector,
			                traceback_length,
			                &orig_ustate,
			                NULL,
			                0,
			                NULL,
			                NULL,
			                NULL,
			                UNWIND_SUCCESS);
		} else if (unwind_error == UNWIND_SUCCESS) {
			/* Coredump caused by a signal. */
			siginfo_t si;
#ifdef __x86_64__
			siginfo32_to_siginfo64(&si, (siginfo32_t *)exception);
#else /* __x86_64__ */
			memcpy(&si, (siginfo32_t *)exception, sizeof(siginfo_t));
#endif /* !__x86_64__ */
			COMPILER_READ_BARRIER();
			signo = si.si_signo;
			coredump_create(&curr_ustate,
			                utb_vector,
			                traceback_length,
			                &orig_ustate,
			                NULL,
			                0,
			                NULL,
			                NULL,
			                &si,
			                UNWIND_SUCCESS);
		} else {
			/* Coredump caused by an exception. */
			siginfo_t si;
			struct exception_data exc;
			bool has_signal;
#ifdef __x86_64__
			exception_data32_to_exception_data64(&exc, exception);
#else /* __x86_64__ */
			memcpy(&exc, exception, sizeof(struct exception_data));
#endif /* !__x86_64__ */
			COMPILER_READ_BARRIER();
			has_signal = error_as_signal(&exc, &si);
			if (has_signal)
				signo = si.si_signo;
			coredump_create(&curr_ustate,
			                utb_vector,
			                traceback_length,
			                &orig_ustate,
			                NULL,
			                0,
			                NULL,
			                &exc,
			                has_signal ? &si
			                           : NULL,
			                unwind_error);
		}
	} EXCEPT {
		if (utb_vector)
			freea(utb_vector);
		RETHROW();
	}
	if (utb_vector)
		freea(utb_vector);
	THROW(E_EXIT_PROCESS,
	      W_EXITCODE(1, signo & 0x7f) | WCOREFLAG);
	return return_state;
}

INTERN struct icpustate *FCALL
coredump32_rpc(void *UNUSED(arg),
              struct icpustate *__restrict state,
              unsigned int reason,
              struct rpc_syscall_info const *sc_info) {
	if unlikely(reason != TASK_RPC_REASON_SYSCALL)
		return state;
	return coredump32_impl(state,
	                       (USER UNCHECKED struct ucpustate32 const *)sc_info->rsi_args[0],
	                       (USER UNCHECKED struct ucpustate32 const *)sc_info->rsi_args[1],
	                       (USER UNCHECKED u32 const *const *)sc_info->rsi_args[2],
	                       (size_t)sc_info->rsi_args[3],
	                       (USER UNCHECKED struct exception_data32 const *)sc_info->rsi_args[4],
	                       (syscall_ulong_t)sc_info->rsi_args[5]);
}


DEFINE_SYSCALL32_6(errno_t, coredump,
                   USER UNCHECKED struct /*ucpustate32*/ucpustate const *, curr_state,
                   USER UNCHECKED struct /*ucpustate32*/ucpustate const *, orig_state,
                   USER UNCHECKED /*u32*/void const *const *, traceback_vector, size_t, traceback_length,
                   USER UNCHECKED struct /*exception_data32*/exception_data const *, exception,
                   syscall_ulong_t, unwind_error) {
	(void)curr_state;
	(void)orig_state;
	(void)traceback_vector;
	(void)traceback_length;
	(void)exception;
	(void)unwind_error;
	task_schedule_user_rpc(THIS_TASK,
	                       &coredump32_rpc,
	                       NULL,
	                       TASK_RPC_FHIGHPRIO |
	                       TASK_USER_RPC_FINTR,
	                       NULL,
	                       GFP_NORMAL);
	__builtin_unreachable();
}


DECL_END

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_COREDUMP_C */
