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
#include <bits/siginfo-convert.h>  /* siginfo64_to_siginfo32 */
#include <bits/siginfo-struct32.h> /* siginfo32_t */
#include <kos/except-inval.h>
#include <kos/kernel/cpu-state-verify.h> /* cpustate_verify_user...() */
#include <kos/kernel/cpu-state.h>        /* icpustate */
#include <kos/kernel/cpu-state32.h>      /* ucpustate32 */
#include <kos/kernel/fpu-state32.h>      /* fpustate32 */
#include <kos/kernel/ucontext32.h>       /* ucontext32_t */

#include <signal.h>
#include <string.h>
#include <syscall.h>

#include <librpc/bits/syscall-info-convert.h> /* rpc_syscall_info_to_rpc_syscall_info32 */
#include <librpc/bits/syscall-info32.h>       /* rpc_syscall_info32 */
#include <librpc/rpc.h>

DECL_BEGIN

#define WORD64(a, b) (u64)((u64)(u32)(a) | (u64)(u32)(b) << 32)
PUBLIC struct atomic64 x86_user_eflags_mask = ATOMIC64_INIT(WORD64(~(EFLAGS_DF), 0));
PUBLIC struct atomic64 x86_exec_eflags_mask = ATOMIC64_INIT(WORD64(~(EFLAGS_DF | EFLAGS_IOPLMASK), 0));
#undef WORD64

#ifdef __x86_64__
#define SYSCALL_VECTOR_SIGRETURN64 __NR_rt_sigreturn
#define SYSCALL_VECTOR_SIGRETURN32 __NR32_sigreturn
#else /* __x86_64__ */
#define SYSCALL_VECTOR_SIGRETURN32 __NR_sigreturn
#endif /* !__x86_64__ */

/* Update the given `state' to raise the specified `siginfo'
 * as a user-space signal within the calling thread.
 * NOTE: The caller is responsible to handle special signal
 *       handlers (`KERNEL_SIG_*') before calling this function!
 *       This function should only be used to enqueue the execution
 *       of a signal handler with a user-space entry point.
 * @param: state:   The interrupt CPU state describing the return to user-space.
 * @param: action:  The signal action to perform.
 * @param: siginfo: The signal that is being raised.
 * @param: sc_info: When non-NULL, `sc_info' describes a system call that may be restarted.
 *                  Note however that ontop of this, [restart({auto,must,dont})]
 *                  logic will still be applied, which is done in cooperation
 *                  with the system call restart database.
 * @return: * :     The updated CPU state.
 * @return: NULL:   The `SIGACTION_SA_RESETHAND' flag was set, but `action'
 *                  differs from the set handler. */
#ifdef __x86_64__
PRIVATE WUNUSED struct icpustate *KCALL
sighand_raise_signal32(struct icpustate *__restrict state,
                       struct kernel_sigaction const *__restrict action,
                       USER CHECKED siginfo_t const *siginfo,
                       struct rpc_syscall_info const *sc_info)
		THROWS(E_SEGFAULT, E_WOULDBLOCK)
#else /* __x86_64__ */
PUBLIC WUNUSED struct icpustate *KCALL
sighand_raise_signal(struct icpustate *__restrict state,
                     struct kernel_sigaction const *__restrict action,
                     USER CHECKED siginfo_t const *siginfo,
                     struct rpc_syscall_info const *sc_info)
		THROWS(E_SEGFAULT, E_WOULDBLOCK)
#endif /* !__x86_64__ */
{
	USER CHECKED byte_t *usp;
	bool must_restore_sigmask;
	sigset_t old_sigmask;
	u32 signo = ATOMIC_READ(siginfo->si_signo);
	USER CHECKED siginfo32_t *user_siginfo;
	USER CHECKED ucontext32_t *user_ucontext;
	USER CHECKED sigset_t *user_sigset;
	USER CHECKED struct fpustate32 *user_fpustate;
	USER CHECKED struct rpc_syscall_info32 *user_sc_info;
	USER CHECKED u32 user_rstor;
	if unlikely(signo == 0 || signo >= NSIG)
		return NULL;
	/* Check if the handler should be reset before being invoked. */
	if (action->sa_flags & SIGACTION_SA_RESETHAND) {
		if unlikely(!sighand_reset_handler(signo, action))
			return NULL;
	}
	if (sc_info) {
		/* Figure out if we should really start a system call. */
		int rmode;
		rmode = kernel_syscall_restartmode(sc_info->rsi_sysno);
		if (rmode == SYSCALL_RESTART_MODE_MUST)
			; /* Always restart */
		else if (rmode == SYSCALL_RESTART_MODE_DONT)
			sc_info = NULL; /* Never restart */
		else if (rmode == SYSCALL_RESTART_MODE_AUTO) {
			/* Only restart when `SIGACTION_SA_RESTART' is set. */
			if (!(action->sa_flags & SIGACTION_SA_RESTART))
				sc_info = NULL;
		}
	}
	/* Figure out how, and if we need to mask signals. */
	must_restore_sigmask = false;
	if (action->sa_mask || !(action->sa_flags & SIGACTION_SA_NODEFER)) {
		struct kernel_sigmask *sigmask;
		sigmask = sigmask_getwr();
		memcpy(&old_sigmask,
		       &sigmask->sm_mask,
		       sizeof(old_sigmask));
		if (!(action->sa_flags & SIGACTION_SA_NODEFER))
			sigaddset(&sigmask->sm_mask, (int)signo);
		if (action->sa_mask) {
			sigorset(&sigmask->sm_mask,
			         &sigmask->sm_mask,
			         &action->sa_mask->sm_mask);
		}
		must_restore_sigmask = memcmp(&old_sigmask,
		                              &sigmask->sm_mask,
		                              sizeof(old_sigmask)) != 0;
	} else {
		struct kernel_sigmask *sigmask;
		sigmask = sigmask_getrd();
		memcpy(&old_sigmask,
		       &sigmask->sm_mask,
		       sizeof(old_sigmask));
	}

	/* Figure out which stack we should write data to. */
	usp = (USER CHECKED byte_t *)irregs_rdsp(&state->ics_irregs);
	/* Check if sigaltstack should be used. */
	if (action->sa_flags & SIGACTION_SA_ONSTACK)
		usp = (USER CHECKED byte_t *)PERTASK_GET(this_user_except_handler.ueh_stack);

	/* At this point, the following options affect how we need to set up the stack:
	 *  - sc_info:                                  When non-NULL, we must restart an interrupted system call
	 *  - must_restore_sigmask:                     When true, we must restore `old_sigmask'
	 *  - action->sa_flags & SIGACTION_SA_SIGINFO:  When true, we must invoke a 3-argument handler
	 *  - action->sa_flags & SIGACTION_SA_RESTORER: When true, we must have the handler return to `sa_restore' */

	user_siginfo  = NULL;
	user_ucontext = NULL;
	user_sigset   = NULL;
	user_fpustate = NULL;
	if (action->sa_flags & SIGACTION_SA_SIGINFO) {
		/* In 3-argument mode, we always have to push everything... */
		STATIC_ASSERT(SIZEOF_USER_SIGINFO_T >= SIZEOF_KERNEL_SIGINFO_T);
		STATIC_ASSERT(SIZEOF_KERNEL_SIGINFO_T == sizeof(siginfo_t));
		/* Try to have the padding of `siginfo_t' overlap with `ucontext32_t' */
#define EFFECTIVE_PADDING_SIGINFO_T (SIZEOF_USER_SIGINFO_T - SIZEOF_KERNEL_SIGINFO_T)
#define EFFECTIVE_SIZEOF_SIGINFO_T                           \
		(EFFECTIVE_PADDING_SIGINFO_T <= sizeof(ucontext32_t) \
		 ? SIZEOF_KERNEL_SIGINFO_T                           \
		 : (SIZEOF_USER_SIGINFO_T - sizeof(ucontext32_t)))
		/* Must push a full `ucontext32_t' */
		user_ucontext = (ucontext32_t *)(usp - sizeof(ucontext32_t));
		validate_writable((byte_t *)user_ucontext - EFFECTIVE_SIZEOF_SIGINFO_T,
		                  sizeof(ucontext32_t) + EFFECTIVE_SIZEOF_SIGINFO_T);
		COMPILER_WRITE_BARRIER();
		user_ucontext->uc_link              = (struct ucontext32 *)NULL; /* Unused... */
		user_ucontext->uc_stack.ss_sp       = usp;
		user_ucontext->uc_stack.ss_flags    = SS_ONSTACK;
		user_ucontext->uc_stack.ss_size     = 0;
		user_ucontext->uc_mcontext.mc_cr2   = 0;
		user_ucontext->uc_mcontext.mc_flags = 0;
		user_sigset = (USER CHECKED sigset_t *)memcpy(&user_ucontext->uc_sigmask,
		                                              &old_sigmask, sizeof(sigset_t));
		if (signo == SIGSEGV) {
			user_ucontext->uc_mcontext.mc_cr2 = (ulongptr_t)siginfo->si_addr;
			user_ucontext->uc_mcontext.mc_flags |= __MCONTEXT_FLAG_HAVECR2;
		}
		if (PERTASK_GET(this_x86_fpustate)) {
			user_fpustate = &user_ucontext->uc_mcontext.mc_fpu;
			fpustate32_saveinto(user_fpustate);
			user_ucontext->uc_mcontext.mc_flags |= x86_fpustate_variant == FPU_STATE_SSTATE
			                                       ? __MCONTEXT_FLAG_HAVESFPU
			                                       : __MCONTEXT_FLAG_HAVEXFPU;
		}
		user_ucontext->uc_mcontext.mc_context.ucs_gpregs.gp_esp = (uintptr_t)usp;
		usp -= sizeof(ucontext32_t) + EFFECTIVE_SIZEOF_SIGINFO_T;
		/* Copy signal information into user-space. */
		user_siginfo = (siginfo32_t *)usp;
		siginfo_to_siginfo32(siginfo, user_siginfo);
	} else {
		/* Only push the bare minimum */
		user_ucontext = COMPILER_CONTAINER_OF((struct ucpustate32 *)(usp - sizeof(struct ucpustate32)),
		                                      ucontext32_t, uc_mcontext.mc_context);
		validate_writable(user_ucontext, sizeof(struct ucpustate32));
		COMPILER_WRITE_BARRIER();
		user_ucontext->uc_mcontext.mc_context.ucs_gpregs.gp_esp = (u32)(uintptr_t)usp;
		usp -= sizeof(struct ucpustate32);
		/* Only save the FPU state if it is in use. */
		if (PERTASK_GET(this_x86_fpustate)) {
			/* Only allocate what we need for the used FPU state */
			usp -= x86_fpustate_variant == FPU_STATE_SSTATE
			       ? sizeof(struct sfpustate)
			       : sizeof(struct xfpustate32);
			user_fpustate = (struct fpustate32 *)usp;
			validate_writable(user_fpustate,
			                  MIN(sizeof(struct sfpustate),
			                      sizeof(struct xfpustate32)));
			COMPILER_WRITE_BARRIER();
			fpustate32_saveinto(user_fpustate);
		}
		/* Only save the sigmask if it was changed. */
		if (must_restore_sigmask) {
			usp -= sizeof(sigset_t);
			user_sigset = (USER CHECKED sigset_t *)usp;
			validate_writable(user_sigset, sizeof(sigset_t));
			COMPILER_WRITE_BARRIER();
			memcpy(user_sigset, &old_sigmask, sizeof(sigset_t));
		}
	}
	/* Fill in return context information */
	user_ucontext->uc_mcontext.mc_context.ucs_gpregs.gp_edi = (u32)gpregs_getpdi(&state->ics_gpregs);
	user_ucontext->uc_mcontext.mc_context.ucs_gpregs.gp_esi = (u32)gpregs_getpsi(&state->ics_gpregs);
	user_ucontext->uc_mcontext.mc_context.ucs_gpregs.gp_ebp = (u32)gpregs_getpbp(&state->ics_gpregs);
	user_ucontext->uc_mcontext.mc_context.ucs_gpregs.gp_ebx = (u32)gpregs_getpbx(&state->ics_gpregs);
	user_ucontext->uc_mcontext.mc_context.ucs_gpregs.gp_edx = (u32)gpregs_getpdx(&state->ics_gpregs);
	user_ucontext->uc_mcontext.mc_context.ucs_gpregs.gp_ecx = (u32)gpregs_getpcx(&state->ics_gpregs);
	user_ucontext->uc_mcontext.mc_context.ucs_gpregs.gp_eax = (u32)gpregs_getpax(&state->ics_gpregs);
	user_ucontext->uc_mcontext.mc_context.ucs_sgregs.sg_gs  = icpustate_getgs(state);
	user_ucontext->uc_mcontext.mc_context.ucs_sgregs.sg_fs  = icpustate_getfs(state);
	user_ucontext->uc_mcontext.mc_context.ucs_sgregs.sg_es  = icpustate_getes(state);
	user_ucontext->uc_mcontext.mc_context.ucs_sgregs.sg_ds  = icpustate_getds(state);
	user_ucontext->uc_mcontext.mc_context.ucs_cs            = icpustate_getcs(state);
	user_ucontext->uc_mcontext.mc_context.ucs_ss            = icpustate_getss(state);
	user_ucontext->uc_mcontext.mc_context.ucs_eflags        = (u32)icpustate_getpflags(state);
	user_ucontext->uc_mcontext.mc_context.ucs_eip           = (u32)icpustate_getpc(state);

	user_sc_info = NULL;
	if (sc_info) {
		unsigned int argc;
		size_t ob_size;
		/* Only copy data up to the first unused argument. */
		for (argc = kernel_syscall_regcnt(sc_info->rsi_sysno); argc; --argc) {
			if (sc_info->rsi_flags & RPC_SYSCALL_INFO_FREGVALID(argc - 1))
				break;
		}
		ob_size = (offsetof(struct rpc_syscall_info32, rsi_regs) + (argc * 4));
		usp -= ob_size;
		user_sc_info = (USER CHECKED struct rpc_syscall_info32 *)usp;
		validate_writable(user_sc_info, ob_size);
		COMPILER_WRITE_BARRIER();
		rpc_syscall_info_to_rpc_syscall_info32(sc_info, user_sc_info, argc);
	}

	/* At this point, we must setup everything to restore:
	 * >> if (must_restore_sigmask)
	 * >>     RESTORE_SIGMASK(user_sigset);
	 * >> if (user_fpustate)
	 * >>     RESTORE_FPUSTATE(user_fpustate,x86_fpustate_variant);
	 * >> RESTORE_UCPUSTATE(&user_ucontext->uc_mcontext.mc_context);
	 * >> if (user_sc_info)
	 * >>     RESTART_SYSTEM_CALL(user_sc_info);
	 */

	if (action->sa_flags & SIGACTION_SA_RESTORER) {
		user_rstor = (u32)(uintptr_t)action->sa_restore;
	} else {
		/* Must push assembly onto the user-stack:
		 * >>     movl  $SYS_sigreturn, %eax
		 * >>     int   $(0x80)
		 */
		/* NOTE: This assembly block's size must be pointer-aligned! */
		PRIVATE byte_t const sigreturn_invoke_assembly[] = {
			/* movl  $SYS_sigreturn, %eax */
			0xb8,
			(SYSCALL_VECTOR_SIGRETURN32 >> 0) & 0xff,
			(SYSCALL_VECTOR_SIGRETURN32 >> 8) & 0xff,
			(SYSCALL_VECTOR_SIGRETURN32 >> 16) & 0xff,
			(SYSCALL_VECTOR_SIGRETURN32 >> 24) & 0xff,
			/* int   $(0x80) */
			0xcd,
			0x80,
			/* Pad to 8 bytes */
			0x00
		};
		usp -= sizeof(sigreturn_invoke_assembly);
		validate_writable(usp, sizeof(sigreturn_invoke_assembly));
		COMPILER_WRITE_BARRIER();
		memcpy(usp, sigreturn_invoke_assembly, sizeof(sigreturn_invoke_assembly));
		user_rstor = (u32)(uintptr_t)(user_sigrestore_func_t)usp;
	}

	/* Push the arguments for the actual signal handler. */
	if (action->sa_flags & SIGACTION_SA_SIGINFO) {
		usp -= 4 * sizeof(u32);
		validate_writable(usp, 4 * sizeof(u32));
		((u32 *)usp)[0] = (u32)user_rstor;               /* Return address */
		((u32 *)usp)[1] = (u32)signo;                    /* int signo */
		((u32 *)usp)[2] = (u32)(uintptr_t)user_siginfo;  /* siginfo32_t *info */
		((u32 *)usp)[3] = (u32)(uintptr_t)user_ucontext; /* struct ucontext32 *ctx */
	} else {
		usp -= 2 * sizeof(u32);
		validate_writable(usp, 2 * sizeof(u32));
		((u32 *)usp)[0] = (u32)user_rstor; /* Return address */
		((u32 *)usp)[1] = (u32)signo;      /* int signo */
	}

	/* Setup the user-space to-be invoked with the following register state:
	 *   - %ebp == &user_ucontext->uc_mcontext.mc_context
	 *   - %ebx == user_fpustate ?: NULL
	 *   - %esi == must_restore_sigmask ? user_sigset : NULL
	 *   - %edi == user_sc_info ?: NULL
	 * NOTE: This register state is what is expected by `sys_sigreturn'
	 *       Note also that we can only use callee-preserve registers
	 *       here, as all other registers may be clobbered by the signal
	 *       handler itself. */
	gpregs_setpbp(&state->ics_gpregs, (u32)(uintptr_t)&user_ucontext->uc_mcontext.mc_context);
	gpregs_setpbx(&state->ics_gpregs, (u32)(uintptr_t)user_fpustate);
	gpregs_setpsi(&state->ics_gpregs, (u32)(uintptr_t)(must_restore_sigmask ? user_sigset : NULL));
	gpregs_setpdi(&state->ics_gpregs, (u32)(uintptr_t)user_sc_info);
	icpustate_setpc(state, (u32)(uintptr_t)action->sa_handler);
	icpustate_setuserpsp(state, (u32)(uintptr_t)usp);
	{
		union x86_user_eflags_mask word;
		word.uem_word = atomic64_read(&x86_user_eflags_mask);
		/* Mask %eflags, as specified by `x86_user_eflags_mask' */
		icpustate_mskpflags(state, word.uem_mask, word.uem_flag);
	}
	return state;
}


#ifdef __x86_64__
PUBLIC WUNUSED struct icpustate *KCALL
sighand_raise_signal(struct icpustate *__restrict state,
                     struct kernel_sigaction const *__restrict action,
                     USER CHECKED siginfo_t const *siginfo,
                     struct rpc_syscall_info const *sc_info)
		THROWS(E_SEGFAULT, E_WOULDBLOCK) {
	struct icpustate *result;
	if (irregs_is32bit(&state->ics_irregs)) {
		/* Compatibility mode. */
		result = sighand_raise_signal32(state, action,
		                                siginfo, sc_info);
	} else {
		kernel_panic("TODO");
	}
	return result;
}
#endif /* __x86_64__ */



INTERN struct icpustate *FCALL
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
                 USER UNCHECKED struct rpc_syscall_info32 *sc_info) {
	bool enable_except;
	enable_except = (irregs_rdflags(&state->ics_irregs) & EFLAGS_CF) != 0;
	TRY {
again:
		validate_readable(restore_cpu, sizeof(*restore_cpu));
		validate_readable_opt(restore_fpu, MIN(sizeof(struct sfpustate), sizeof(struct xfpustate)));
		validate_readable_opt(restore_sigmask, sizeof(*restore_sigmask));
		validate_readable_opt(sc_info, sizeof(*sc_info));
		/* Restore the given signal mask. */
		if (restore_sigmask) {
			struct kernel_sigmask *sigmask;
			COMPILER_READ_BARRIER();
			sigmask = sigmask_getwr();
			memcpy(&sigmask->sm_mask, restore_sigmask, sizeof(sigmask->sm_mask));
			COMPILER_WRITE_BARRIER();
			/* Make sure that mandatory signals always remain unmasked.
			 * In case we just escaped an RPC attempt by another thread sending
			 * either one of these signals, not to worry, as code below will always
			 * check for `sigmask_check_s()' when `restore_sigmask' is non-NULL. */
			sigdelset(&sigmask->sm_mask, SIGKILL);
			sigdelset(&sigmask->sm_mask, SIGSTOP);
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
			if unlikely(sc.rsi_sysno == SYSCALL_VECTOR_SIGRETURN32) {
				/* Special case: Return to sigreturn.
				 * -> To prevent recursion, restart this system call immediately
				 *    by looping back to the start of our function!
				 * NOTE: This special case mainly prevents user-space from being
				 *       able to cause a kernel stack overflow by chaining a bunch
				 *       of sigreturn invocations ontop of each other. */
				restore_cpu     = (USER UNCHECKED struct ucpustate32 const *)sc.rsi_regs[SIGRETURN_386_ARGID_RESTORE_CPU];
				restore_fpu     = (USER UNCHECKED struct fpustate32 const *)sc.rsi_regs[SIGRETURN_386_ARGID_RESTORE_FPU];
				restore_sigmask = (USER UNCHECKED sigset_t const *)sc.rsi_regs[SIGRETURN_386_ARGID_RESTORE_SIGMASK];
				sc_info         = (USER UNCHECKED struct rpc_syscall_info32 *)sc.rsi_regs[SIGRETURN_386_ARGID_SC_INFO];
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
			state = syscall_emulate(state, &sc);
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
		 * that EFLAGS.CF is undefined when sigreturn() is called, meaning it
		 * would also be undefined how exceptions caused by restarted system
		 * calls are handled.
		 * The intended behavior here is that sigreturn() only accounts for
		 * its own EFLAGS.CF when validating and processing is restore arguments,
		 * but will mirror the exceptions model of a restarted system call. */

		/* NOTE: Technically, this behavior right here is incorrect, as it doesn't
		 *       preserve the correct user-space EFLAGS.CF value. However, we have
		 *       no other way of passing the knowledge about how the exception should
		 *       be propagated to `x86_userexcept_propagate()' and friends.
		 *       So with this in mind, this is the best we can do when it comes to this problem.
		 * However, since sigreturn() should only ever be used when returning from signal
		 * handlers, this shouldn't actually be a problem...
		 * XXX: Why not call `x86_userexcept_propagate()' directly here? */
		icpustate_setpflags(state,
		                    (icpustate_getpflags(state) & ~EFLAGS_CF) |
		                    (enable_except ? EFLAGS_CF : 0));
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
	                        (USER UNCHECKED struct rpc_syscall_info32 *)sc_info->rsi_regs[SIGRETURN_386_ARGID_SC_INFO]);
}

DEFINE_SYSCALL32_6(void, sigreturn,
                    USER UNCHECKED struct fpustate32 const *, restore_fpu,
                    syscall_ulong_t, unused1,
                    syscall_ulong_t, unused2,
                    USER UNCHECKED sigset_t const *, restore_sigmask,
                    USER UNCHECKED struct rpc_syscall_info32 *, sc_info,
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



INTERN struct icpustate *FCALL
raiseat32_impl(struct icpustate *__restrict state,
               USER UNCHECKED struct ucpustate32 const *ust,
               USER UNCHECKED siginfo32_t const *usi) {
	siginfo_t si;
	validate_readable(usi, sizeof(*usi));
	siginfo32_to_siginfo(usi, &si);
	if (ust) {
		validate_readable(ust, sizeof(*ust));
		state = syscall_fill_icpustate_from_ucpustate32(state, ust);
	}
	/* Verify that the signal number is inside of its mandatory bounds. */
	if unlikely(!si.si_signo || si.si_signo >= NSIG) {
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_RAISE_SIGNO,
		      si.si_signo);
	}
	/* By passing sc_info as NULL, we can guaranty that raiseat() isn't restarted. */
	state = x86_userexcept_raisesignal(state, NULL,
	                                   &si, false);
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
	                      (USER UNCHECKED siginfo32_t const *)sc_info->rsi_regs[1]);
}

DEFINE_SYSCALL32_2(errno_t, raiseat,
                   USER UNCHECKED struct ucpustate32 const *, state,
                   USER UNCHECKED siginfo32_t const *, si) {
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
raiseat64_impl(struct icpustate *__restrict state,
               USER UNCHECKED struct ucpustate64 const *ust,
               USER UNCHECKED siginfo64_t const *usi) {
	siginfo_t si;
	validate_readable(usi, sizeof(*usi));
	siginfo64_to_siginfo(usi, &si);
	if (ust) {
		validate_readable(ust, sizeof(*ust));
		state = syscall_fill_icpustate_from_ucpustate64(state, ust);
	}
	/* Verify that the signal number is inside of its mandatory bounds. */
	if unlikely(!si.si_signo || si.si_signo >= NSIG) {
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_RAISE_SIGNO,
		      si.si_signo);
	}
	/* By passing sc_info as NULL, we can guaranty that raiseat() isn't restarted. */
	state = x86_userexcept_raisesignal(state, NULL,
	                                   &si, false);
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
	                      (USER UNCHECKED siginfo64_t const *)sc_info->rsi_regs[1]);
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
