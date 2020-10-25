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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_SCHED_POSIX_SIGNAL_C
#define GUARD_KERNEL_CORE_ARCH_I386_SCHED_POSIX_SIGNAL_C 1
#define _GNU_SOURCE 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/fpu.h>
#include <kernel/panic.h>
#include <kernel/printk.h>
#include <kernel/syscall-properties.h>
#include <kernel/syscall.h>
#include <kernel/types.h>
#include <kernel/user.h>
#include <sched/cred.h>
#include <sched/except-handler.h>
#include <sched/posix-signal.h>
#include <sched/rpc.h>
#include <sched/task.h>

#include <hybrid/atomic.h>
#include <hybrid/minmax.h>

#include <asm/cpu-flags.h>
#include <asm/intrin.h>
#include <asm/registers.h>
#include <bits/os/kos/siginfo-convert.h> /* siginfo64_to_siginfo32 */
#include <bits/os/kos/siginfo32.h>       /* siginfo32_t */
#include <bits/os/kos/ucontext32.h>      /* __ucontextx32 */
#include <kos/except/reason/inval.h>
#include <kos/kernel/cpu-state-verify.h> /* cpustate_verify_user...() */
#include <kos/kernel/cpu-state.h>        /* icpustate */
#include <kos/kernel/cpu-state32.h>      /* ucpustate32 */
#include <kos/kernel/fpu-state32.h>      /* fpustate32 */
#include <sys/ucontext.h>

#include <assert.h>
#include <errno.h>
#include <signal.h>
#include <stddef.h>
#include <string.h>
#include <syscall.h>

#include <librpc/bits/syscall-info-convert.h> /* rpc_syscall_info_to_rpc_syscall_info32 */
#include <librpc/bits/syscall-info32.h>       /* rpc_syscall_info32 */
#include <librpc/rpc.h>

DECL_BEGIN

#define WORD64(a, b) (u64)((u64)(u32)(a) | (u64)(u32)(b) << 32)
PUBLIC atomic64_t x86_user_eflags_mask = ATOMIC64_INIT(WORD64(~(EFLAGS_DF), 0));
PUBLIC atomic64_t x86_exec_eflags_mask = ATOMIC64_INIT(WORD64(~(EFLAGS_DF | EFLAGS_IOPLMASK), 0));
#undef WORD64

/* TODO: Kernel commandline options:
 *  - user_eflags_mask=mask,flag
 *  - exec_eflags_mask=mask,flag
 */


#ifdef __x86_64__
#define SYSCALL_VECTOR_SIGRETURN64          __NR_rt_sigreturn
#define SYSCALL_VECTOR_SIGRETURN32          __NR32_sigreturn
#define SYSCALL_VECTOR_ISSIGRETURN64(vecno) ((vecno) == __NR_rt_sigreturn)
#define SYSCALL_VECTOR_ISSIGRETURN32(vecno) ((vecno) == __NR32_sigreturn || (vecno) == __NR32_rt_sigreturn)
#else /* __x86_64__ */
#define SYSCALL_VECTOR_SIGRETURN32          __NR_sigreturn
#define SYSCALL_VECTOR_ISSIGRETURN32(vecno) ((vecno) == __NR_sigreturn || (vecno) == __NR_rt_sigreturn)
#endif /* !__x86_64__ */

#ifdef __x86_64__
#ifndef __INTELLISENSE__
DECL_END
#define DEFINE_RAISE32 1
#include "posix-signal-raise.c.inl"
#define DEFINE_RAISE64 1
#include "posix-signal-raise.c.inl"
DECL_BEGIN
#else /* !__INTELLISENSE__ */
PRIVATE WUNUSED struct icpustate *KCALL
sighand_raise_signal32(struct icpustate *__restrict state,
                       struct kernel_sigaction const *__restrict action,
                       USER CHECKED siginfo_t const *siginfo,
                       struct rpc_syscall_info const *sc_info)
		THROWS(E_SEGFAULT, E_WOULDBLOCK);
PRIVATE WUNUSED struct icpustate *KCALL
sighand_raise_signal64(struct icpustate *__restrict state,
                       struct kernel_sigaction const *__restrict action,
                       USER CHECKED siginfo_t const *siginfo,
                       struct rpc_syscall_info const *sc_info)
		THROWS(E_SEGFAULT, E_WOULDBLOCK);
#endif /* __INTELLISENSE__ */

PUBLIC WUNUSED struct icpustate *KCALL
sighand_raise_signal(struct icpustate *__restrict state,
                     struct kernel_sigaction const *__restrict action,
                     USER CHECKED siginfo_t const *siginfo,
                     struct rpc_syscall_info const *sc_info)
		THROWS(E_SEGFAULT, E_WOULDBLOCK) {
	struct icpustate *result;
	if (irregs_is32bit(&state->ics_irregs)) {
		/* Compatibility mode. */
		result = sighand_raise_signal32(state, action, siginfo, sc_info);
	} else {
		result = sighand_raise_signal64(state, action, siginfo, sc_info);
	}
	return result;
}
#else /* __x86_64__ */
#ifndef __INTELLISENSE__
DECL_END
#define DEFINE_RAISE32 1
#include "posix-signal-raise.c.inl"
DECL_BEGIN
#endif /* !__INTELLISENSE__ */
#endif /* !__x86_64__ */



PRIVATE struct icpustate *FCALL
syscall_fill_icpustate_from_ucpustate32(struct icpustate *__restrict state,
                                        USER CHECKED struct ucpustate32 const *__restrict ust)
		THROWS(E_INVALID_ARGUMENT_BAD_VALUE, E_SEGFAULT, ...) {
	u16 gs, fs, es, ds, ss, cs;
	u32 eflags;
	gs     = ust->ucs_sgregs.sg_gs16;
	fs     = ust->ucs_sgregs.sg_fs16;
	es     = ust->ucs_sgregs.sg_es16;
	ds     = ust->ucs_sgregs.sg_ds16;
	ss     = ust->ucs_ss16;
	cs     = ust->ucs_cs16;
	eflags = ucpustate32_geteflags(ust);
	COMPILER_READ_BARRIER();
	cpustate_verify_userpflags(icpustate_getpflags(state),
	                           eflags,
	                           cred_allow_eflags_modify_mask());
#ifndef __x86_64__
	if (eflags & EFLAGS_VM) {
		state->ics_irregs_v.ir_es = es;
		state->ics_irregs_v.ir_ds = ds;
		state->ics_irregs_v.ir_fs = fs;
		state->ics_irregs_v.ir_gs = gs;
	} else
#endif /* !__x86_64__ */
	{
		/* Validate segment register indices before actually restoring them. */
		cpustate_verify_usercs(cs);
		cpustate_verify_userss(ss);
		cpustate_verify_usergs(gs);
		cpustate_verify_userfs(fs);
		cpustate_verify_useres(es);
		cpustate_verify_userds(ds);
		icpustate_setgs_novm86(state, gs);
		icpustate_setfs_novm86(state, fs);
		icpustate_setes_novm86(state, es);
		icpustate_setds_novm86(state, ds);
	}
	icpustate_setcs(state, cs);
	icpustate_setuserss(state, ss);
	gpregs32_to_gpregsnsp(&ust->ucs_gpregs, &state->ics_gpregs);
	icpustate_setpflags(state, eflags);
	icpustate_setpc(state, ucpustate32_geteip(ust));
	icpustate_setuserpsp(state, ucpustate32_getesp(ust));
	return state;
}


/* Argument indices of parameters passed to sigreturn() */
#define SIGRETURN_386_ARGID_RESTORE_CPU      5 /* SYSCALL_ARGUMENT_REGISTER_INDEX(%ebp) */
#define SIGRETURN_386_ARGID_RESTORE_FPU      0 /* SYSCALL_ARGUMENT_REGISTER_INDEX(%ebx) */
#define SIGRETURN_386_ARGID_RESTORE_SIGMASK  3 /* SYSCALL_ARGUMENT_REGISTER_INDEX(%esi) */
#define SIGRETURN_386_ARGID_SC_INFO          4 /* SYSCALL_ARGUMENT_REGISTER_INDEX(%edi) */

/* Sigreturn system call implementation. */
INTERN struct icpustate *FCALL
sigreturn32_impl(struct icpustate *__restrict state,
                 USER UNCHECKED struct ucpustate32 const *restore_cpu,
                 USER UNCHECKED struct fpustate32 const *restore_fpu,
                 USER UNCHECKED sigset_t const *restore_sigmask,
                 USER UNCHECKED struct rpc_syscall_info32 const *sc_info) {
	bool enable_except;
	enable_except = (irregs_rdflags(&state->ics_irregs) & EFLAGS_DF) != 0;
	TRY {
again:
		validate_readable(restore_cpu, sizeof(*restore_cpu));
		validate_readable_opt(restore_fpu,
		                      MIN_C(sizeof(struct sfpustate),
		                            sizeof(struct xfpustate32)));
		validate_readable_opt(restore_sigmask, sizeof(*restore_sigmask));
		validate_readable_opt(sc_info, sizeof(*sc_info));
		/* Restore the given signal mask. */
		if (restore_sigmask) {
			USER CHECKED sigset_t *mymask;
			COMPILER_READ_BARRIER();
			mymask = sigmask_getwr();
			memcpy(mymask, restore_sigmask, sizeof(sigset_t));
			COMPILER_WRITE_BARRIER();
			/* Make sure that mandatory signals always remain unmasked.
			 * In case we just escaped an RPC attempt by another thread sending
			 * either one of these signals, not to worry, as code below will always
			 * check for `sigmask_check_s()' when `restore_sigmask' is non-NULL. */
			sigdelset(mymask, SIGKILL);
			sigdelset(mymask, SIGSTOP);
		}
		/* Restore the FPU context */
		if (restore_fpu)
			fpustate32_loadfrom(restore_fpu);
		/* Restore the CPU context */
		state = syscall_fill_icpustate_from_ucpustate32(state, restore_cpu);

		if (sc_info) {
			/* Restart a system call. */
			unsigned int i;
			struct rpc_syscall_info sc;
			rpc_syscall_info32_to_rpc_syscall_info(sc_info, &sc);
			COMPILER_READ_BARRIER();
			/* Check for restartable system calls.
			 * NOTE: When performing this check, use the system call given
			 *       by the caller as the one that would be restarted.
			 *       This, alongside the fact that sys_sigreturn() is marked
			 *       as being [restart(must)], will ensure that we always
			 *       eventually come back around to being able to restart
			 *       the system call. */
			if (restore_sigmask) {
				struct icpustate *new_state;
				new_state = sigmask_check_s(state, &sc);
				if (new_state != TASK_RPC_RESTART_SYSCALL)
					state = new_state;
			}
			/* Set invalid arguments to 0 */
			for (i = 0; i < 6; ++i) {
				if (!(sc.rsi_flags & RPC_SYSCALL_INFO_FREGVALID(i)))
					sc.rsi_regs[i] = 0;
			}
			if unlikely(SYSCALL_VECTOR_ISSIGRETURN32(sc.rsi_sysno)) {
				/* Special case: Return to sigreturn.
				 * -> To prevent recursion, restart this system call immediately
				 *    by looping back to the start of our function!
				 * NOTE: This special case mainly prevents user-space from being
				 *       able to cause a kernel stack overflow by chaining a bunch
				 *       of sigreturn invocations ontop of each other. */
				restore_cpu     = (USER UNCHECKED struct ucpustate32 const *)sc.rsi_regs[SIGRETURN_386_ARGID_RESTORE_CPU];
				restore_fpu     = (USER UNCHECKED struct fpustate32 const *)sc.rsi_regs[SIGRETURN_386_ARGID_RESTORE_FPU];
				restore_sigmask = (USER UNCHECKED sigset_t const *)sc.rsi_regs[SIGRETURN_386_ARGID_RESTORE_SIGMASK];
				sc_info         = (USER UNCHECKED struct rpc_syscall_info32 const *)sc.rsi_regs[SIGRETURN_386_ARGID_SC_INFO];
				/* Disable exception propagation when sigreturn() is invoked without exceptions enabled. */
				if ((sc.rsi_flags & RPC_SYSCALL_INFO_FEXCEPT) == 0)
					enable_except = false;
				goto again;
			}
			/* Emulate the system call.
			 * NOTE: Mirror the exceptions model specified in `sc_info',
			 *       in that we propagate system call exceptions the same
			 *       way they would have originally been propagated if the
			 *       system call hadn't had to be restarted. */
			sc.rsi_flags &= ~RPC_SYSCALL_INFO_FMETHOD;
			sc.rsi_flags |= RPC_SYSCALL_INFO_METHOD_SIGRETURN_32;
			state = syscall_emulate32(state, &sc);
		} else {
			if (restore_sigmask) {
				struct icpustate *new_state;
				new_state = sigmask_check_s(state, NULL);
				if (new_state != TASK_RPC_RESTART_SYSCALL)
					state = new_state;
			}
		}
	} EXCEPT {
		/* Implement our own custom exception handler to work around the fact
		 * that EFLAGS.DF is undefined when sigreturn() is called, meaning it
		 * would also be undefined how exceptions caused by restarted system
		 * calls are handled.
		 * The intended behavior here is that sigreturn() only accounts for
		 * its own EFLAGS.DF when validating and processing is restore arguments,
		 * but will mirror the exceptions model of a restarted system call. */

		/* NOTE: Technically, this behavior right here is incorrect, as it doesn't
		 *       preserve the correct user-space EFLAGS.DF value. However, we have
		 *       no other way of passing the knowledge about how the exception should
		 *       be propagated to `x86_userexcept_propagate()' and friends.
		 *       So with this in mind, this is the best we can do when it comes to this problem.
		 * However, since sigreturn() should only ever be used when returning from signal
		 * handlers, this shouldn't actually be a problem...
		 * XXX: Why not call `x86_userexcept_propagate()' directly here? */
		icpustate_setpflags(state,
		                    (icpustate_getpflags(state) & ~EFLAGS_DF) |
		                    (enable_except ? EFLAGS_DF : 0));
		RETHROW();
	}
	return state;
}

INTERN struct icpustate *FCALL
sigreturn32_rpc(void *UNUSED(arg),
                struct icpustate *__restrict state,
                unsigned int reason,
                struct rpc_syscall_info const *sc_info) {
	if unlikely(reason != TASK_RPC_REASON_SYSCALL)
		return state;
	return sigreturn32_impl(state,
	                        (USER UNCHECKED struct ucpustate32 const *)sc_info->rsi_regs[SIGRETURN_386_ARGID_RESTORE_CPU],
	                        (USER UNCHECKED struct fpustate32 const *)sc_info->rsi_regs[SIGRETURN_386_ARGID_RESTORE_FPU],
	                        (USER UNCHECKED sigset_t const *)sc_info->rsi_regs[SIGRETURN_386_ARGID_RESTORE_SIGMASK],
	                        (USER UNCHECKED struct rpc_syscall_info32 const *)sc_info->rsi_regs[SIGRETURN_386_ARGID_SC_INFO]);
}


/* Define `rt_sigreturn()' as an alias for `sigreturn()' */
#ifdef __x86_64__
#ifdef __NR32_rt_sigreturn
DEFINE_PUBLIC_ALIAS(sys32_rt_sigreturn, sys32_sigreturn);
#endif /* __NR32_rt_sigreturn */
#else /* __x86_64__ */
#ifdef __NR_rt_sigreturn
DEFINE_PUBLIC_ALIAS(sys_rt_sigreturn, sys_sigreturn);
#endif /* __NR_rt_sigreturn */
#endif /* !__x86_64__ */

DEFINE_SYSCALL32_6(void, sigreturn,
                   USER UNCHECKED struct fpustate32 const *, restore_fpu,
                   syscall_ulong_t, unused1,
                   syscall_ulong_t, unused2,
                   USER UNCHECKED sigset_t const *, restore_sigmask,
                   USER UNCHECKED struct rpc_syscall_info32 const *, sc_info,
                   USER UNCHECKED struct ucpustate32 const *, restore_cpu) {
	(void)restore_fpu;
	(void)unused1;
	(void)unused2;
	(void)restore_sigmask;
	(void)sc_info;
	(void)restore_cpu;
	task_schedule_user_rpc(THIS_TASK,
	                       &sigreturn32_rpc,
	                       NULL,
	                       TASK_RPC_FHIGHPRIO |
	                       TASK_USER_RPC_FINTR,
	                       GFP_NORMAL);
	__builtin_unreachable();
}


#ifdef __x86_64__
PRIVATE struct icpustate *FCALL
syscall_fill_icpustate_from_ucpustate64(struct icpustate *__restrict state,
                                        USER CHECKED struct ucpustate64 const *__restrict ust)
		THROWS(E_INVALID_ARGUMENT_BAD_VALUE, E_SEGFAULT, ...) {
	u16 gs, fs, es, ds, ss, cs;
	u64 rflags;
	gs     = ust->ucs_sgregs.sg_gs16;
	fs     = ust->ucs_sgregs.sg_fs16;
	es     = ust->ucs_sgregs.sg_es16;
	ds     = ust->ucs_sgregs.sg_ds16;
	ss     = ust->ucs_ss16;
	cs     = ust->ucs_cs16;
	rflags = ucpustate64_getrflags(ust);
	COMPILER_READ_BARRIER();
	cpustate_verify_userpflags(icpustate_getpflags(state),
	                           rflags,
	                           cred_allow_eflags_modify_mask());
	/* Validate segment register indices before actually restoring them. */
	cpustate_verify_usercs(cs);
	cpustate_verify_userss(ss);
	cpustate_verify_usergs(gs);
	cpustate_verify_userfs(fs);
	cpustate_verify_useres(es);
	cpustate_verify_userds(ds);
	icpustate_setgs_novm86(state, gs);
	icpustate_setfs_novm86(state, fs);
	icpustate_setes_novm86(state, es);
	icpustate_setds_novm86(state, ds);
	icpustate_setcs(state, cs);
	icpustate_setuserss(state, ss);
	gpregs64_to_gpregsnsp(&ust->ucs_gpregs, &state->ics_gpregs);
	icpustate_setpflags(state, rflags);
	icpustate_setpc(state, ucpustate64_getrip(ust));
	icpustate_setuserpsp(state, ucpustate64_getrsp(ust));
	set_user_gsbase(ust->ucs_sgbase.sg_gsbase);
	set_user_fsbase(ust->ucs_sgbase.sg_fsbase);
	return state;
}

INTERN struct icpustate *FCALL
sigreturn64_impl(struct icpustate *__restrict state,
                 USER UNCHECKED struct ucpustate64 const *restore_cpu,
                 USER UNCHECKED struct fpustate64 const *restore_fpu,
                 USER UNCHECKED sigset_t const *restore_sigmask,
                 USER UNCHECKED struct rpc_syscall_info64 const *sc_info) {
	bool enable_except;
	enable_except = (irregs_rdflags(&state->ics_irregs) & EFLAGS_DF) != 0;
	TRY {
again:
		validate_readable(restore_cpu, sizeof(*restore_cpu));
		validate_readable_opt(restore_fpu,
		                      MIN_C(sizeof(struct sfpustate),
		                            sizeof(struct xfpustate64)));
		validate_readable_opt(restore_sigmask, sizeof(*restore_sigmask));
		validate_readable_opt(sc_info, sizeof(*sc_info));
		/* Restore the given signal mask. */
		if (restore_sigmask) {
			USER CHECKED sigset_t *sigmask;
			COMPILER_READ_BARRIER();
			sigmask = sigmask_getwr();
			memcpy(sigmask, restore_sigmask, sizeof(sigset_t));
			COMPILER_WRITE_BARRIER();
			/* Make sure that mandatory signals always remain unmasked.
			 * In case we just escaped an RPC attempt by another thread sending
			 * either one of these signals, not to worry, as code below will always
			 * check for `sigmask_check_s()' when `restore_sigmask' is non-NULL. */
			sigdelset(sigmask, SIGKILL);
			sigdelset(sigmask, SIGSTOP);
		}
		/* Restore the FPU context */
		if (restore_fpu)
			fpustate64_loadfrom(restore_fpu);
		/* Restore the CPU context */
		state = syscall_fill_icpustate_from_ucpustate64(state, restore_cpu);

		if (sc_info) {
			/* Restart a system call. */
			unsigned int i;
			struct rpc_syscall_info sc;
			rpc_syscall_info64_to_rpc_syscall_info(sc_info, &sc);
			COMPILER_READ_BARRIER();
			/* Check for restartable system calls.
			 * NOTE: When performing this check, use the system call given
			 *       by the caller as the one that would be restarted.
			 *       This, alongside the fact that sys_sigreturn() is marked
			 *       as being [restart(must)], will ensure that we always
			 *       eventually come back around to being able to restart
			 *       the system call. */
			if (restore_sigmask) {
				struct icpustate *new_state;
				new_state = sigmask_check_s(state, &sc);
				if (new_state != TASK_RPC_RESTART_SYSCALL)
					state = new_state;
			}
			/* Set invalid arguments to 0 */
			for (i = 0; i < 6; ++i) {
				if (!(sc.rsi_flags & RPC_SYSCALL_INFO_FREGVALID(i)))
					sc.rsi_regs[i] = 0;
			}
			if unlikely(SYSCALL_VECTOR_ISSIGRETURN64(sc.rsi_sysno)) {
				/* Special case: Return to sigreturn.
				 * -> To prevent recursion, restart this system call immediately
				 *    by looping back to the start of our function!
				 * NOTE: This special case mainly prevents user-space from being
				 *       able to cause a kernel stack overflow by chaining a bunch
				 *       of sigreturn invocations ontop of each other. */
				restore_cpu     = (USER UNCHECKED struct ucpustate64 const *)gpregs_getpbp(&state->ics_gpregs);
				restore_fpu     = (USER UNCHECKED struct fpustate64 const *)gpregs_getpbx(&state->ics_gpregs);
				restore_sigmask = (USER UNCHECKED sigset_t const *)gpregs_getp12(&state->ics_gpregs);
				sc_info         = (USER UNCHECKED struct rpc_syscall_info64 const *)gpregs_getp13(&state->ics_gpregs);

				/* Disable exception propagation when sigreturn() is invoked without exceptions enabled. */
				if ((sc.rsi_flags & RPC_SYSCALL_INFO_FEXCEPT) == 0)
					enable_except = false;
				goto again;
			}
			/* Emulate the system call.
			 * NOTE: Mirror the exceptions model specified in `sc_info',
			 *       in that we propagate system call exceptions the same
			 *       way they would have originally been propagated if the
			 *       system call hadn't had to be restarted. */
			sc.rsi_flags &= ~RPC_SYSCALL_INFO_FMETHOD;
			sc.rsi_flags |= RPC_SYSCALL_INFO_METHOD_SIGRETURN_64;
			state = syscall_emulate64(state, &sc);
		} else {
			if (restore_sigmask) {
				struct icpustate *new_state;
				new_state = sigmask_check_s(state, NULL);
				if (new_state != TASK_RPC_RESTART_SYSCALL)
					state = new_state;
			}
		}
	} EXCEPT {
		/* Implement our own custom exception handler to work around the fact
		 * that EFLAGS.DF is undefined when sigreturn() is called, meaning it
		 * would also be undefined how exceptions caused by restarted system
		 * calls are handled.
		 * The intended behavior here is that sigreturn() only accounts for
		 * its own EFLAGS.DF when validating and processing is restore arguments,
		 * but will mirror the exceptions model of a restarted system call. */

		/* NOTE: Technically, this behavior right here is incorrect, as it doesn't
		 *       preserve the correct user-space EFLAGS.DF value. However, we have
		 *       no other way of passing the knowledge about how the exception should
		 *       be propagated to `x86_userexcept_propagate()' and friends.
		 *       So with this in mind, this is the best we can do when it comes to this problem.
		 * However, since sigreturn() should only ever be used when returning from signal
		 * handlers, this shouldn't actually be a problem...
		 * XXX: Why not call `x86_userexcept_propagate()' directly here? */
		icpustate_setpflags(state,
		                    (icpustate_getpflags(state) & ~EFLAGS_DF) |
		                    (enable_except ? EFLAGS_DF : 0));
		RETHROW();
	}
	return state;
}

INTERN struct icpustate *FCALL
sigreturn64_rpc(void *UNUSED(arg),
                struct icpustate *__restrict state,
                unsigned int reason,
                struct rpc_syscall_info const *UNUSED(sc_info)) {
	if unlikely(reason != TASK_RPC_REASON_SYSCALL)
		return state;
	return sigreturn64_impl(state,
	                        (USER UNCHECKED struct ucpustate64 const *)gpregs_getpbp(&state->ics_gpregs),
	                        (USER UNCHECKED struct fpustate64 const *)gpregs_getpbx(&state->ics_gpregs),
	                        (USER UNCHECKED sigset_t const *)gpregs_getp12(&state->ics_gpregs),
	                        (USER UNCHECKED struct rpc_syscall_info64 const *)gpregs_getp13(&state->ics_gpregs));
}

DEFINE_SYSCALL64_0(void, rt_sigreturn) {
	task_schedule_user_rpc(THIS_TASK,
	                       &sigreturn64_rpc,
	                       NULL,
	                       TASK_RPC_FHIGHPRIO |
	                       TASK_USER_RPC_FINTR,
	                       GFP_NORMAL);
	__builtin_unreachable();
}
#endif /* __x86_64__ */



INTERN struct icpustate *FCALL
raiseat32_impl(struct icpustate *__restrict state,
               USER UNCHECKED struct ucpustate32 const *ust,
               USER UNCHECKED struct __siginfox32_struct const *usi) {
	siginfo_t si;
	validate_readable(usi, sizeof(*usi));
	siginfox32_to_siginfo(usi, &si);
	if (ust) {
		validate_readable(ust, sizeof(*ust));
		state = syscall_fill_icpustate_from_ucpustate32(state, ust);
	}
	/* Verify that the signal number is inside of its mandatory bounds. */
	if unlikely(si.si_signo <= 0 || si.si_signo >= NSIG) {
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_RAISE_SIGNO,
		      si.si_signo);
	}
	/* By passing sc_info as NULL, we can guaranty that raiseat() isn't restarted. */
	state = x86_userexcept_raisesignal(state,
	                                   NULL,
	                                   &si,
	                                   NULL);
	return state;
}

INTERN struct icpustate *FCALL
raiseat32_rpc(void *UNUSED(arg),
              struct icpustate *__restrict state,
              unsigned int reason,
              struct rpc_syscall_info const *sc_info) {
	if unlikely(reason != TASK_RPC_REASON_SYSCALL)
		return state;
	return raiseat32_impl(state,
	                      (USER UNCHECKED struct ucpustate32 const *)sc_info->rsi_regs[0],
	                      (USER UNCHECKED struct __siginfox32_struct const *)sc_info->rsi_regs[1]);
}

DEFINE_SYSCALL32_2(errno_t, raiseat,
                   USER UNCHECKED struct ucpustate32 const *, state,
                   USER UNCHECKED struct __siginfox32_struct const *, si) {
	(void)state;
	(void)si;
	task_schedule_user_rpc(THIS_TASK,
	                       &raiseat32_rpc,
	                       NULL,
	                       TASK_RPC_FHIGHPRIO |
	                       TASK_USER_RPC_FINTR,
	                       GFP_NORMAL);
	__builtin_unreachable();
}


#ifdef __x86_64__

INTERN struct icpustate *FCALL
raiseat64_impl(struct icpustate *__restrict state,
               USER UNCHECKED struct ucpustate64 const *ust,
               USER UNCHECKED struct __siginfox64_struct const *usi) {
	siginfo_t si;
	validate_readable(usi, sizeof(*usi));
	siginfox64_to_siginfo(usi, &si);
	if (ust) {
		validate_readable(ust, sizeof(*ust));
		state = syscall_fill_icpustate_from_ucpustate64(state, ust);
	}
	/* Verify that the signal number is inside of its mandatory bounds. */
	if unlikely(si.si_signo <= 0 || si.si_signo >= NSIG) {
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_RAISE_SIGNO,
		      si.si_signo);
	}
	/* By passing sc_info as NULL, we can guaranty that raiseat() isn't restarted. */
	state = x86_userexcept_raisesignal(state,
	                                   NULL,
	                                   &si,
	                                   NULL);
	return state;
}

INTERN struct icpustate *FCALL
raiseat64_rpc(void *UNUSED(arg),
              struct icpustate *__restrict state,
              unsigned int reason,
              struct rpc_syscall_info const *sc_info) {
	if unlikely(reason != TASK_RPC_REASON_SYSCALL)
		return state;
	return raiseat64_impl(state,
	                      (USER UNCHECKED struct ucpustate64 const *)sc_info->rsi_regs[0],
	                      (USER UNCHECKED struct __siginfox64_struct const *)sc_info->rsi_regs[1]);
}

DEFINE_SYSCALL64_2(errno_t, raiseat,
                   USER UNCHECKED /*ucpustate32*/ struct ucpustate const *, state,
                   USER UNCHECKED /*siginfo32_t*/ struct __siginfo_struct const *, si) {
	(void)state;
	(void)si;
	task_schedule_user_rpc(THIS_TASK,
	                       &raiseat64_rpc,
	                       NULL,
	                       TASK_RPC_FHIGHPRIO |
	                       TASK_USER_RPC_FINTR,
	                       GFP_NORMAL);
	__builtin_unreachable();
}
#endif /* __x86_64__ */


DECL_END

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_SCHED_POSIX_SIGNAL_C */
