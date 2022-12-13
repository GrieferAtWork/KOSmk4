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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_SCHED_POSIX_SIGNAL_C
#define GUARD_KERNEL_CORE_ARCH_I386_SCHED_POSIX_SIGNAL_C 1
#define _GNU_SOURCE 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/except.h>
#include <kernel/fpu.h>
#include <kernel/rt/except-handler.h>
#include <kernel/rt/except-syscall.h> /* CONFIG_HAVE_KERNEL_USERPROCMASK */
#include <kernel/syscall-properties.h>
#include <kernel/syscall.h>
#include <kernel/user.h>
#include <sched/cred.h>
#include <sched/rpc-internal.h>
#include <sched/rpc.h>
#include <sched/sigmask.h>
#include <sched/task.h>

#include <hybrid/atomic.h>
#include <hybrid/host.h>
#include <hybrid/minmax.h>

#include <asm/cpu-flags.h>
#include <asm/syscalls32_d.h>
#include <asm/syscalls64_d.h>
#include <bits/os/generic/sigset_with_size32.h>
#include <bits/os/kos/mcontext32.h>
#include <bits/os/kos/siginfo-convert.h>
#include <bits/os/kos/ucontext32.h>
#include <kos/bits/syscall-info-convert.h>
#include <kos/bits/syscall-info32.h>
#include <kos/except.h>
#include <kos/kernel/cpu-state-compat.h>
#include <kos/kernel/cpu-state-helpers.h>
#include <kos/kernel/cpu-state-verify.h>
#include <kos/kernel/bits/cpu-state32.h>
#include <kos/kernel/bits/fpu-state32.h>
#include <kos/rpc.h>

#include <assert.h>
#include <signal.h>
#include <stddef.h>
#include <string.h>

#ifdef __x86_64__
#include <bits/os/generic/sigset_with_size64.h>
#include <bits/os/kos/mcontext64.h>
#include <bits/os/kos/ucontext64.h>
#include <kos/bits/syscall-info64.h>
#include <kos/kernel/bits/cpu-state64.h>
#include <kos/kernel/bits/fpu-state64.h>
#endif /* __x86_64__ */

#ifndef __INTELLISENSE__
#define DEFINE_x86_userexcept_callsignal32
#include "posix-signal-call.c.inl"
#ifdef __x86_64__
#define DEFINE_x86_userexcept_callsignal64
#include "posix-signal-call.c.inl"
#endif /* ... */
#endif /* !__INTELLISENSE__ */

DECL_BEGIN

/************************************************************************/
/* Compatibility mode wrappers                                          */
/************************************************************************/
#ifdef __x86_64__
PRIVATE ATTR_RETNONNULL WUNUSED NONNULL((1, 2, 3)) struct icpustate *FCALL
x86_userexcept_callsignal32(struct icpustate *__restrict state,
                            struct kernel_sigaction const *__restrict action,
                            siginfo_t const *__restrict siginfo,
                            struct rpc_syscall_info const *sc_info)
		THROWS(E_SEGFAULT);
PRIVATE ATTR_RETNONNULL WUNUSED NONNULL((1, 2, 3)) struct icpustate *FCALL
x86_userexcept_callsignal64(struct icpustate *__restrict state,
                            struct kernel_sigaction const *__restrict action,
                            siginfo_t const *__restrict siginfo,
                            struct rpc_syscall_info const *sc_info)
		THROWS(E_SEGFAULT);
PUBLIC ATTR_RETNONNULL WUNUSED NONNULL((1, 2, 3)) struct icpustate *FCALL
userexcept_callsignal(struct icpustate *__restrict state,
                      struct kernel_sigaction const *__restrict action,
                      siginfo_t const *__restrict siginfo,
                      struct rpc_syscall_info const *sc_info)
		THROWS(E_SEGFAULT) {
	return icpustate_iscompat(state) ? x86_userexcept_callsignal32(state, action, siginfo, sc_info)
	                                 : x86_userexcept_callsignal64(state, action, siginfo, sc_info);
}
#endif /* __x86_64__ */






/************************************************************************/
/* 32-BIT KSIGRETURN(2)                                                 */
/************************************************************************/

/* Sigreturn system call implementation.
 * WARNING: This function may not necessarily return normally, or by throwing an exception! */
INTERN ABNORMAL_RETURN ATTR_RETNONNULL WUNUSED NONNULL((1)) struct icpustate *FCALL
sys_ksigreturn32_impl(struct icpustate *__restrict state,
                      USER UNCHECKED struct ucpustate32 const *restore_cpu,
                      USER UNCHECKED struct fpustate32 const *restore_fpu,
                      USER UNCHECKED struct __sigset_with_sizex32 const *restore_sigmask,
                      USER UNCHECKED struct rpc_syscall_info32 const *restart_sc_info) {
	struct __sigset_with_sizex32 rmask;

	/* TODO: `i386_validate_readable()'  (validate_readable() on i386; compat_validate_readable() on x86_64) */

	/* Validate arguments. */
	validate_readable(restore_cpu, sizeof(*restore_cpu));
	validate_readable_opt(restore_fpu,
	                      MIN_C(sizeof(struct sfpustate),
	                            sizeof(struct xfpustate32)));
	validate_readable_opt(restart_sc_info, sizeof(*restart_sc_info));
	bzero(&rmask, sizeof(rmask));
	if (restore_sigmask) {
		memcpy(&rmask, validate_readable(restore_sigmask, sizeof(rmask)), sizeof(rmask));
		validate_readable(rmask.sws_sigset, rmask.sws_sigsiz);
	}

	/* Load CPU state information from user-space data structures. */
	{
		u16 gs, fs, es, ds, ss, cs;
		u32 eflags;
		gs     = restore_cpu->ucs_sgregs.sg_gs16;
		fs     = restore_cpu->ucs_sgregs.sg_fs16;
		es     = restore_cpu->ucs_sgregs.sg_es16;
		ds     = restore_cpu->ucs_sgregs.sg_ds16;
		ss     = restore_cpu->ucs_ss16;
		cs     = restore_cpu->ucs_cs16;
		eflags = ucpustate32_geteflags(restore_cpu);
		COMPILER_READ_BARRIER();
		cpustate_verify_usereflags((u32)icpustate_getpflags(state), eflags,
		                           /* Accept `EFLAGS_RF' (needed return-from-exception-handler) */
		                           EFLAGS_RF | cred_allow_eflags_modify_mask());
#ifndef __x86_64__
#ifndef __I386_NO_VM86
		if (eflags & EFLAGS_VM) {
			state->ics_irregs_v.ir_es = es;
			state->ics_irregs_v.ir_ds = ds;
			state->ics_irregs_v.ir_fs = fs;
			state->ics_irregs_v.ir_gs = gs;
		} else
#endif /* !__I386_NO_VM86 */
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
		gpregs32_to_gpregsnsp(&restore_cpu->ucs_gpregs, &state->ics_gpregs);
		icpustate_setpflags(state, eflags);
		icpustate_setpip(state, ucpustate32_geteip(restore_cpu));
		icpustate_setuserpsp(state, ucpustate32_getesp(restore_cpu));
	}

	/* Restore the given signal mask. */
	if (rmask.sws_sigset != NULL) {
		if (sigmask_setmask_from_user((USER CHECKED sigset_t const *)(void *)rmask.sws_sigset,
		                              rmask.sws_sigsiz)) {
			/* If the signal mask changed (technically only needed if it became
			 * less restrictive), then ensure that pending signals are  checked
			 * prior to the next return to user-space. */
			userexcept_sysret_inject_self();
		}
	}

	/* Restore the FPU context */
	if (restore_fpu)
		fpustate32_loadfrom(restore_fpu);

	if (restart_sc_info) {
		struct rpc_syscall_info restart_sysinfo;
		COMPILER_READ_BARRIER();
		restart_sysinfo.rsi_flags   = restart_sc_info->rsi_flags;
		restart_sysinfo.rsi_sysno   = restart_sc_info->rsi_sysno;
		restart_sysinfo.rsi_regs[0] = restart_sc_info->rsi_regs[0];
		restart_sysinfo.rsi_regs[1] = restart_sc_info->rsi_regs[1];
		restart_sysinfo.rsi_regs[2] = restart_sc_info->rsi_regs[2];
		restart_sysinfo.rsi_regs[3] = restart_sc_info->rsi_regs[3];
		restart_sysinfo.rsi_regs[4] = restart_sc_info->rsi_regs[4];
		restart_sysinfo.rsi_regs[5] = restart_sc_info->rsi_regs[5];
		COMPILER_READ_BARRIER();

		/* Only a couple of information bits are actually kept. */
		restart_sysinfo.rsi_flags &= RPC_SYSCALL_INFO_FEXCEPT;
		restart_sysinfo.rsi_flags |= RPC_SYSCALL_INFO_METHOD_SIGRETURN_32;

		/* Emulate the requested system call (NOTE: This call does
		 * not return, neither by exception, nor by normal  means) */
		syscall_emulate32_r(state, &restart_sysinfo);
	}
	return state;
}

/* Argument indices of parameters passed to sigreturn() */
#define SIGRETURN32_ARGID_RESTORE_CPU     5 /* SYSCALL_ARGUMENT_REGISTER_INDEX(%ebp) */
#define SIGRETURN32_ARGID_RESTORE_FPU     0 /* SYSCALL_ARGUMENT_REGISTER_INDEX(%ebx) */
#define SIGRETURN32_ARGID_RESTORE_SIGMASK 3 /* SYSCALL_ARGUMENT_REGISTER_INDEX(%esi) */
#define SIGRETURN32_ARGID_SC_INFO         4 /* SYSCALL_ARGUMENT_REGISTER_INDEX(%edi) */


PRIVATE ABNORMAL_RETURN NONNULL((1)) void PRPC_EXEC_CALLBACK_CC
sys_ksigreturn32_rpc(struct rpc_context *__restrict ctx,
                     void *UNUSED(cookie)) {
	USER UNCHECKED struct ucpustate32 const *restore_cpu;
	USER UNCHECKED struct fpustate32 const *restore_fpu;
	USER UNCHECKED struct __sigset_with_sizex32 const *restore_sigmask;
	USER UNCHECKED struct rpc_syscall_info32 const *restart_sc_info;
	if unlikely(ctx->rc_context != RPC_REASONCTX_SYSCALL)
		return;
	restore_cpu     = (USER UNCHECKED struct ucpustate32 const *)ctx->rc_scinfo.rsi_regs[SIGRETURN32_ARGID_RESTORE_CPU];
	restore_fpu     = (USER UNCHECKED struct fpustate32 const *)ctx->rc_scinfo.rsi_regs[SIGRETURN32_ARGID_RESTORE_FPU];
	restore_sigmask = (USER UNCHECKED struct __sigset_with_sizex32 const *)ctx->rc_scinfo.rsi_regs[SIGRETURN32_ARGID_RESTORE_SIGMASK];
	restart_sc_info = (USER UNCHECKED struct rpc_syscall_info32 const *)ctx->rc_scinfo.rsi_regs[SIGRETURN32_ARGID_SC_INFO];

	ctx->rc_state = sys_ksigreturn32_impl(ctx->rc_state, restore_cpu,
	                                      restore_fpu, restore_sigmask,
	                                      restart_sc_info);

	/* Indicate that the system call has completed; further RPCs should never try to restart it! */
	ctx->rc_context = RPC_REASONCTX_SYSRET;
}

DEFINE_SYSCALL32_6(void, ksigreturn,
                   USER UNCHECKED struct fpustate32 const *, restore_fpu,
                   syscall_ulong_t, unused1,
                   syscall_ulong_t, unused2,
                   USER UNCHECKED struct __sigset_with_sizex32 const *, restore_sigmask,
                   USER UNCHECKED struct rpc_syscall_info32 const *, sc_info,
                   USER UNCHECKED struct ucpustate32 const *, restore_cpu) {
	(void)restore_fpu;
	(void)unused1;
	(void)unused2;
	(void)restore_sigmask;
	(void)sc_info;
	(void)restore_cpu;

	/* Send an RPC to ourselves, so we can gain access to the user-space register state. */
	task_rpc_userunwind(&sys_ksigreturn32_rpc, NULL);
	__builtin_unreachable();
}








#ifdef __x86_64__
/************************************************************************/
/* 64-BIT KSIGRETURN(2)                                                 */
/************************************************************************/

/* Sigreturn system call implementation.
 * WARNING: This function may not necessarily return normally, or by throwing an exception! */
INTERN ATTR_RETNONNULL WUNUSED NONNULL((1)) struct icpustate *FCALL
sys_ksigreturn64_impl(struct icpustate *__restrict state,
                      USER UNCHECKED struct ucpustate64 const *restore_cpu,
                      USER UNCHECKED struct fpustate64 const *restore_fpu,
                      USER UNCHECKED struct __sigset_with_sizex64 const *restore_sigmask,
                      USER UNCHECKED struct rpc_syscall_info64 const *restart_sc_info) {
	struct __sigset_with_sizex64 rmask;
	/* Validate arguments. */
	validate_readable(restore_cpu, sizeof(*restore_cpu));
	validate_readable_opt(restore_fpu,
	                      MIN_C(sizeof(struct sfpustate),
	                            sizeof(struct xfpustate64)));
	validate_readable_opt(restart_sc_info, sizeof(*restart_sc_info));
	bzero(&rmask, sizeof(rmask));
	if (restore_sigmask) {
		memcpy(&rmask, validate_readable(restore_sigmask, sizeof(rmask)), sizeof(rmask));
		validate_readable(rmask.sws_sigset, rmask.sws_sigsiz);
	}

	/* Load CPU state information from user-space data structures. */
	{
		u16 gs, fs, es, ds, ss, cs;
		u64 rflags;
		gs     = restore_cpu->ucs_sgregs.sg_gs16;
		fs     = restore_cpu->ucs_sgregs.sg_fs16;
		es     = restore_cpu->ucs_sgregs.sg_es16;
		ds     = restore_cpu->ucs_sgregs.sg_ds16;
		ss     = restore_cpu->ucs_ss16;
		cs     = restore_cpu->ucs_cs16;
		rflags = ucpustate64_getrflags(restore_cpu);
		COMPILER_READ_BARRIER();
		cpustate_verify_userrflags(icpustate_getpflags(state), rflags,
		                           /* Accept `EFLAGS_RF' (needed return-from-exception-handler) */
		                           EFLAGS_RF | cred_allow_eflags_modify_mask());
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
		gpregs64_to_gpregsnsp(&restore_cpu->ucs_gpregs, &state->ics_gpregs);
		icpustate_setpflags(state, rflags);
		icpustate_setpip(state, ucpustate64_getrip(restore_cpu));
		icpustate_setuserpsp(state, ucpustate64_getrsp(restore_cpu));
		x86_set_user_gsbase(restore_cpu->ucs_sgbase.sg_gsbase);
		x86_set_user_fsbase(restore_cpu->ucs_sgbase.sg_fsbase);
	}

	/* Restore the given signal mask. */
	if (rmask.sws_sigset != NULL) {
		if (sigmask_setmask_from_user(rmask.sws_sigset, rmask.sws_sigsiz)) {
			/* If the signal mask changed (technically only needed if it became
			 * less restrictive), then ensure that pending signals are  checked
			 * prior to the next return to user-space. */
			userexcept_sysret_inject_self();
		}
	}

	/* Restore the FPU context */
	if (restore_fpu)
		fpustate64_loadfrom(restore_fpu);

	if (restart_sc_info) {
		struct rpc_syscall_info restart_sysinfo;
		COMPILER_READ_BARRIER();
		restart_sysinfo.rsi_flags   = restart_sc_info->rsi_flags;
		restart_sysinfo.rsi_sysno   = restart_sc_info->rsi_sysno;
		restart_sysinfo.rsi_regs[0] = restart_sc_info->rsi_regs[0];
		restart_sysinfo.rsi_regs[1] = restart_sc_info->rsi_regs[1];
		restart_sysinfo.rsi_regs[2] = restart_sc_info->rsi_regs[2];
		restart_sysinfo.rsi_regs[3] = restart_sc_info->rsi_regs[3];
		restart_sysinfo.rsi_regs[4] = restart_sc_info->rsi_regs[4];
		restart_sysinfo.rsi_regs[5] = restart_sc_info->rsi_regs[5];
		COMPILER_READ_BARRIER();

		/* Only a couple of information bits are actually kept. */
		restart_sysinfo.rsi_flags &= RPC_SYSCALL_INFO_FEXCEPT;
		restart_sysinfo.rsi_flags |= RPC_SYSCALL_INFO_METHOD_SIGRETURN_64;

		/* Emulate the requested system call (NOTE: This call does
		 * not return, neither by exception, nor by normal  means) */
		syscall_emulate32_r(state, &restart_sysinfo);
	}
	return state;
}

PRIVATE NONNULL((1)) void PRPC_EXEC_CALLBACK_CC
sys_ksigreturn64_rpc(struct rpc_context *__restrict ctx,
                     void *UNUSED(cookie)) {
	USER UNCHECKED struct ucpustate64 const *restore_cpu;
	USER UNCHECKED struct fpustate64 const *restore_fpu;
	USER UNCHECKED struct __sigset_with_sizex64 const *restore_sigmask;
	USER UNCHECKED struct rpc_syscall_info64 const *restart_sc_info;
	if unlikely(ctx->rc_context != RPC_REASONCTX_SYSCALL)
		return;
	restore_cpu     = (USER UNCHECKED struct ucpustate64 const *)gpregs_getpbp(&ctx->rc_state->ics_gpregs);
	restore_fpu     = (USER UNCHECKED struct fpustate64 const *)gpregs_getpbx(&ctx->rc_state->ics_gpregs);
	restore_sigmask = (USER UNCHECKED struct __sigset_with_sizex64 const *)gpregs_getp12(&ctx->rc_state->ics_gpregs);
	restart_sc_info = (USER UNCHECKED struct rpc_syscall_info64 const *)gpregs_getp13(&ctx->rc_state->ics_gpregs);

	ctx->rc_state = sys_ksigreturn64_impl(ctx->rc_state, restore_cpu,
	                                      restore_fpu, restore_sigmask,
	                                      restart_sc_info);

	/* Indicate that the system call has completed; further RPCs should never try to restart it! */
	ctx->rc_context = RPC_REASONCTX_SYSRET;
}

DEFINE_SYSCALL64_0(void, ksigreturn) {
	/* Send an RPC to ourselves, so we can gain access to the user-space register state. */
	task_rpc_userunwind(&sys_ksigreturn64_rpc, NULL);
	__builtin_unreachable();
}
#endif /* __x86_64__ */

DECL_END

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_SCHED_POSIX_SIGNAL_C */
