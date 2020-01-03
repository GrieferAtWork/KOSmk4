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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifdef __INTELLISENSE__
#include "coredump.c"
#define DEFINE_COREDUMP32 1
//#define DEFINE_COREDUMP64 1
#endif /* __INTELLISENSE__ */

#if (defined(DEFINE_COREDUMP32) + defined(DEFINE_COREDUMP64)) != 1
#error "Must #define exactly one of DEFINE_COREDUMP32 or DEFINE_COREDUMP64"
#endif


#ifdef DEFINE_COREDUMP32
#define NAME(x)     x##32
#define NAME2(x, y) x##32##y
#else /* DEFINE_COREDUMP32 */
#define NAME(x)     x##64
#define NAME2(x, y) x##64##y
#endif /* !DEFINE_COREDUMP32 */

DECL_BEGIN

LOCAL void KCALL
NAME(user_ucpu_from_ucpu)(struct icpustate const *__restrict return_state,
                          USER CHECKED struct NAME(ucpustate) const *ust,
                          struct ucpustate *__restrict result) {
#ifdef DEFINE_COREDUMP32
	ucpustate32_to_ucpustate(ust, result);
#else /* DEFINE_COREDUMP32 */
	ucpustate64_to_ucpustate(ust, result);
#endif /* !DEFINE_COREDUMP32 */
	cpustate_verify_userpflags(icpustate_getpflags(return_state),
	                           ucpustate_getpflags(result),
	                           cred_allow_eflags_modify_mask());
#ifdef DEFINE_COREDUMP32
	if (!icpustate_isvm86(return_state)) {
		cpustate_verify_usercs(result->ucs_cs16);
		cpustate_verify_userss(result->ucs_ss16);
		cpustate_verify_usergs(result->ucs_sgregs.sg_gs16);
		cpustate_verify_userfs(result->ucs_sgregs.sg_fs16);
		cpustate_verify_useres(result->ucs_sgregs.sg_es16);
		cpustate_verify_userds(result->ucs_sgregs.sg_ds16);
	}
#endif /* DEFINE_COREDUMP32 */
}

INTERN struct icpustate *FCALL
NAME(coredump_impl)(struct icpustate *__restrict return_state,
                    USER UNCHECKED struct NAME(ucpustate) const *curr_state,
                    USER UNCHECKED struct NAME(ucpustate) const *orig_state,
                    USER UNCHECKED NAME(u) const *const *traceback_vector, size_t traceback_length,
                    USER UNCHECKED struct NAME(exception_data) const *exception,
                    syscall_ulong_t unwind_error) {
	struct ucpustate curr_ustate, orig_ustate;
	void **utb_vector;
	unsigned int signo = SIGILL;
	validate_readable_opt(exception,
	                      unwind_error == UNWIND_SUCCESS ? sizeof(struct NAME(exception_data))
	                                                     : sizeof(NAME2(siginfo, _t)));
	if (!curr_state && !orig_state) {
		icpustate_user_to_ucpustate(return_state, &curr_ustate);
		memcpy(&orig_ustate, &curr_ustate, sizeof(struct ucpustate));
		traceback_vector = NULL;
		traceback_length = 0;
	} else if (!curr_state) {
		validate_readable(orig_state, sizeof(*orig_state));
		NAME(user_ucpu_from_ucpu)(return_state, orig_state, &orig_ustate);
		memcpy(&curr_ustate, &orig_ustate, sizeof(struct ucpustate));
		traceback_vector = NULL;
		traceback_length = 0;
	} else if (!orig_state) {
		validate_readable(curr_state, sizeof(*curr_state));
		NAME(user_ucpu_from_ucpu)(return_state, curr_state, &curr_ustate);
		memcpy(&orig_ustate, &curr_ustate, sizeof(struct ucpustate));
		traceback_vector = NULL;
		traceback_length = 0;
	} else {
		validate_readable(curr_state, sizeof(*curr_state));
		validate_readable(orig_state, sizeof(*orig_state));
		NAME(user_ucpu_from_ucpu)(return_state, curr_state, &curr_ustate);
		NAME(user_ucpu_from_ucpu)(return_state, orig_state, &orig_ustate);
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
			NAME2(siginfo, _to_siginfo)((NAME2(siginfo, _t) *)(uintptr_t)exception, &si);
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
			NAME2(exception_data, _to_exception_data)(exception, &exc);
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
NAME(coredump_rpc)(void *UNUSED(arg),
                   struct icpustate *__restrict state,
                   unsigned int reason,
                   struct rpc_syscall_info const *sc_info) {
	if unlikely(reason != TASK_RPC_REASON_SYSCALL)
		return state;
	return NAME(coredump_impl)(state,
	                           (USER UNCHECKED struct NAME(ucpustate) const *)sc_info->rsi_regs[0],
	                           (USER UNCHECKED struct NAME(ucpustate) const *)sc_info->rsi_regs[1],
	                           (USER UNCHECKED NAME(u) const *const *)sc_info->rsi_regs[2],
	                           (size_t)sc_info->rsi_regs[3],
	                           (USER UNCHECKED struct NAME(exception_data) const *)sc_info->rsi_regs[4],
	                           (syscall_ulong_t)sc_info->rsi_regs[5]);
}

/************************************************************************/
/* coredump()                                                           */
/************************************************************************/
NAME2(DEFINE_SYSCALL, _6)(errno_t, coredump,
                          USER UNCHECKED struct NAME(ucpustate) const *, curr_state,
                          USER UNCHECKED struct NAME(ucpustate) const *, orig_state,
                          USER UNCHECKED NAME(PTR)(void) const *, traceback_vector, size_t, traceback_length,
                          USER UNCHECKED struct NAME(exception_data) const *, exception,
                          syscall_ulong_t, unwind_error) {
	(void)curr_state;
	(void)orig_state;
	(void)traceback_vector;
	(void)traceback_length;
	(void)exception;
	(void)unwind_error;
	task_schedule_user_rpc(THIS_TASK,
	                       &NAME(coredump_rpc),
	                       NULL,
	                       TASK_RPC_FHIGHPRIO |
	                       TASK_USER_RPC_FINTR,
	                       GFP_NORMAL);
	__builtin_unreachable();
}


DECL_END

#undef NAME
#undef NAME2
#undef DEFINE_COREDUMP32
#undef DEFINE_COREDUMP64

