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
#ifdef __INTELLISENSE__
#include "oldposix-signal.c"
#define DEFINE_RAISE32 1
//#define DEFINE_RAISE64 1
#endif /* __INTELLISENSE__ */

#if (defined(DEFINE_RAISE32) + defined(DEFINE_RAISE64)) != 1
#error "Must #define exactly one of `DEFINE_RAISE32' or `DEFINE_RAISE64'"
#endif

DECL_BEGIN

#ifdef DEFINE_RAISE32
#define NAME(x)     x##32
#define NAME2(x, y) x##32##y
#else /* DEFINE_RAISE32 */
#define NAME(x)     x##64
#define NAME2(x, y) x##64##y
#endif /* !DEFINE_RAISE32 */


#ifdef CONFIG_USE_NEW_RPC
/* Update the given  `state' to raise  the specified `siginfo'  as
 * a user-space signal  within the calling  thread. The caller  is
 * responsible  to handle special signal handlers (`KERNEL_SIG_*')
 * before calling this function! This function should only be used
 * to  enqueue the execution of a signal handler with a user-space
 * entry point.
 *
 * Functionality like `SIGACTION_SA_RESETHAND', or system call
 * restart  selection  must  be  implemented  by  the  caller.
 *
 * @param: state:   The CPU state describing the return to user-space.
 * @param: action:  The signal action to perform.
 * @param: siginfo: The signal that is being raised.
 * @param: sc_info: When  non-NULL, `sc_info' describes a system call
 *                  that will be restarted once the user-space signal
 *                  handler returns. No additional  should-really-be-
 *                  re-started  logic is done  by this function (iow:
 *                  such logic must be implemented by the caller)
 * @return: * :     The updated CPU state. */
#ifdef __x86_64__
PRIVATE ATTR_RETNONNULL WUNUSED NONNULL((1, 2, 3)) struct icpustate *FCALL
NAME(userexcept_callsignal)(struct icpustate *__restrict state,
                            struct kernel_sigaction const *__restrict action,
                            siginfo_t const *__restrict siginfo,
                            struct rpc_syscall_info const *sc_info)
		THROWS(E_SEGFAULT)
#else /* __x86_64__ */
PUBLIC ATTR_RETNONNULL WUNUSED NONNULL((1, 2, 3)) struct icpustate *FCALL
userexcept_callsignal(struct icpustate *__restrict state,
                      struct kernel_sigaction const *__restrict action,
                      siginfo_t const *__restrict siginfo,
                      struct rpc_syscall_info const *sc_info)
		THROWS(E_SEGFAULT)
#endif /* !__x86_64__ */
#else /* CONFIG_USE_NEW_RPC */
/* Update the given  `state' to raise  the specified `siginfo'  as
 * a user-space signal  within the calling  thread. The caller  is
 * responsible  to handle special signal handlers (`KERNEL_SIG_*')
 * before calling this function! This function should only be used
 * to  enqueue the execution of a signal handler with a user-space
 * entry point.
 * @param: state:   The CPU state describing the return to user-space.
 * @param: action:  The signal action to perform.
 * @param: siginfo: The signal that is being raised.
 * @param: sc_info: When non-NULL, `sc_info'  describes a system  call
 *                  that may be restarted. Note however that ontop  of
 *                  this, [restart({auto,must,dont})] logic will still
 *                  be applied, which is done in cooperation with  the
 *                  system call restart database.
 * @return: * :     The updated CPU state.
 * @return: NULL:   The `SIGACTION_SA_RESETHAND' flag was set,
 *                  but `action' differs from the set handler. */
#ifdef __x86_64__
PRIVATE WUNUSED NONNULL((1, 2)) struct icpustate *KCALL
NAME(userexcept_callsignal)(struct icpustate *__restrict state,
                            struct kernel_sigaction const *__restrict action,
                            USER CHECKED siginfo_t const *siginfo,
                            struct rpc_syscall_info const *sc_info)
		THROWS(E_SEGFAULT, E_WOULDBLOCK)
#else /* __x86_64__ */
PUBLIC WUNUSED NONNULL((1, 2)) struct icpustate *KCALL
userexcept_callsignal(struct icpustate *__restrict state,
                      struct kernel_sigaction const *__restrict action,
                      USER CHECKED siginfo_t const *siginfo,
                      struct rpc_syscall_info const *sc_info)
		THROWS(E_SEGFAULT, E_WOULDBLOCK)
#endif /* !__x86_64__ */
#endif /* !CONFIG_USE_NEW_RPC */
{
	USER CHECKED byte_t *usp, *orig_usp;
	bool must_restore_sigmask;
	sigset_t old_sigmask;
	USER CHECKED struct NAME2(__siginfox, _struct) *user_siginfo;
	USER CHECKED struct NAME(__ucontextx) *user_ucontext;
	USER CHECKED sigset_t *user_sigset;
	USER CHECKED struct NAME(fpustate) *user_fpustate;
	USER CHECKED struct NAME(rpc_syscall_info) *user_sc_info;
	USER CHECKED NAME(u) user_rstor;
#ifdef CONFIG_USE_NEW_RPC
	signo_t signo = siginfo->si_signo;
	assert(!(signo <= 0 || signo >= NSIG));
#else /* CONFIG_USE_NEW_RPC */
	signo_t signo = ATOMIC_READ(siginfo->si_signo);
	if unlikely(signo <= 0 || signo >= NSIG)
		return NULL;
	/* Check if the handler should be reset before being invoked. */
	if (action->sa_flags & SIGACTION_SA_RESETHAND) {
		if unlikely(!sighand_reset_handler(signo, action))
			return NULL;
	}
	if (sc_info != NULL) {
		/* Figure out if we should really start a system call. */
		int rmode;
		bool delete_sc_info = false;

		rmode = kernel_syscall_restartmode(sc_info);
		if (rmode == SYSCALL_RESTART_MODE_MUST)
			; /* Always restart */
		else if (rmode == SYSCALL_RESTART_MODE_DONT)
			delete_sc_info = true; /* Never restart */
		else if (rmode == SYSCALL_RESTART_MODE_AUTO) {
			/* Only restart when `SIGACTION_SA_RESTART' is set. */
			if (!(action->sa_flags & SIGACTION_SA_RESTART))
				delete_sc_info = true;
		}
		/* When not restarting the system call, then we must
		 * either have it return with -EINTR, or the  signal
		 * handler must return  to the user-space  exception
		 * handler. */
		if (delete_sc_info) {
			if (sc_info->rsi_flags & RPC_SYSCALL_INFO_FEXCEPT) {
				struct exception_info *tls_info;
				tls_info = error_info();
				memset(tls_info, 0, sizeof(*tls_info));
				tls_info->ei_code             = ERROR_CODEOF(E_INTERRUPT);
				tls_info->ei_data.e_faultaddr = icpustate_getpc(state);
				/* FIXME: This function has a chance to never return when
				 *        it causes the calling process to be terminated!
				 * However, we need it to always return, since `userexcept_callsignal()'
				 * must always return normally, or via an exception! */
				state = x86_userexcept_propagate(state, sc_info);
				assert(tls_info->ei_code == ERROR_CODEOF(E_OK));
			} else {
				gpregs_setpax(&state->ics_gpregs, -EINTR);
			}
			sc_info = NULL;
		}
	}
#endif /* !CONFIG_USE_NEW_RPC */

	/* Figure out how, and if we need to mask signals. */
	must_restore_sigmask = false;
	if (action->sa_mask || !(action->sa_flags & SIGACTION_SA_NODEFER)) {
		USER CHECKED sigset_t *sigmask;
		sigmask = sigmask_getwr();
		memcpy(&old_sigmask, sigmask, sizeof(sigset_t));
		/* FIXME: `sigmask' may not actually be  writable if it's a  userprocmask.
		 *        Because of this, we only try add signals to `sigmask' when their
		 *        bits are  set to  `0' (s.a.  `setsigmaskfullptr(3)', which  sets
		 *        the  userprocmask to an all-1s mask which is stored in read-only
		 *        memory) */
		if (!(action->sa_flags & SIGACTION_SA_NODEFER))
			sigaddset(sigmask, (int)signo);
		if (action->sa_mask)
			sigorset(sigmask, sigmask, &action->sa_mask->sm_mask);
		must_restore_sigmask = memcmp(&old_sigmask, sigmask,
		                              sizeof(sigset_t)) != 0;
	} else {
		USER CHECKED sigset_t const *sigmask;
		sigmask = sigmask_getrd();
		memcpy(&old_sigmask, sigmask, sizeof(sigset_t));
	}

	/* Figure out which stack we should write data to. */
	orig_usp = (USER CHECKED byte_t *)icpustate_getusersp(state);
	usp      = orig_usp;
	/* Check if sigaltstack should be used. */
	if (action->sa_flags & SIGACTION_SA_ONSTACK) {
		/* TODO: SS_AUTODISARM */
		/* TODO: If we raised an E_INTERRUPT above, then we mustn't
		 *       switch  to the alternate  signal stack again here! */
		usp = (USER CHECKED byte_t *)PERTASK_GET(this_user_except_handler.ueh_stack);
	}
#ifdef DEFINE_RAISE64
	else {
		usp -= 128; /* Red zone (TODO: Make this configurable!) */
	}
#endif /* DEFINE_RAISE64 */

	/* Force proper alignment. */
#ifdef DEFINE_RAISE32
	usp = (USER CHECKED byte_t *)((uintptr_t)usp & ~3);
#else /* DEFINE_RAISE32 */
	usp = (USER CHECKED byte_t *)((uintptr_t)usp & ~7);
#endif /* !DEFINE_RAISE32 */

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
		STATIC_ASSERT(NAME2(__SIX, _USER_MAX_SIZE) >= NAME2(__SIX, _KERNEL_MAX_SIZE));
		STATIC_ASSERT(NAME2(__SIX, _KERNEL_MAX_SIZE) == sizeof(struct NAME2(__siginfox, _struct)));
		/* Try to have the padding of `siginfo_t' overlap with `ucontextN_t' */
#define EFFECTIVE_PADDING_SIGINFO_T (NAME2(__SIX, _USER_MAX_SIZE) - NAME2(__SIX, _KERNEL_MAX_SIZE))
#define EFFECTIVE_SIZEOF_SIGINFO_T                                       \
		(EFFECTIVE_PADDING_SIGINFO_T <= sizeof(struct NAME(__ucontextx)) \
		 ? NAME2(__SIX, _KERNEL_MAX_SIZE)                                \
		 : (NAME2(__SIX, _USER_MAX_SIZE) - sizeof(struct NAME(__ucontextx))))
		/* Must push a full `ucontextN_t' */
		user_ucontext = (struct NAME(__ucontextx) *)(usp - sizeof(struct NAME(__ucontextx)));
		validate_writable((byte_t *)user_ucontext - EFFECTIVE_SIZEOF_SIGINFO_T,
		                  sizeof(struct NAME(__ucontextx)) + EFFECTIVE_SIZEOF_SIGINFO_T);
		COMPILER_WRITE_BARRIER();
		user_ucontext->uc_link              = (struct NAME(__ucontextx) *)NULL; /* Unused... */
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
		if (PERTASK_GET(this_fpustate)) {
			user_fpustate = &user_ucontext->uc_mcontext.mc_fpu;
			user_fpustate = (NAME2(fpustate, _saveinto)(user_fpustate));
			user_ucontext->uc_mcontext.mc_flags |= x86_fpustate_variant == FPU_STATE_SSTATE
			                                       ? __MCONTEXT_FLAG_HAVESFPU
			                                       : __MCONTEXT_FLAG_HAVEXFPU;
		}
		usp -= sizeof(struct NAME(__ucontextx)) + EFFECTIVE_SIZEOF_SIGINFO_T;
		/* Copy signal information into user-space. */
		user_siginfo = (struct NAME2(__siginfox, _struct) *)usp;
		NAME(siginfo_to_siginfox)(siginfo, user_siginfo);
#undef EFFECTIVE_PADDING_SIGINFO_T
#undef EFFECTIVE_SIZEOF_SIGINFO_T
	} else {
		/* Only push the bare minimum */
		user_ucontext = container_of((struct NAME(ucpustate) *)(usp - sizeof(struct NAME(ucpustate))),
		                             struct NAME(__ucontextx), uc_mcontext.mc_context);
		validate_writable(user_ucontext, sizeof(struct NAME(ucpustate)));
		COMPILER_WRITE_BARRIER();
		usp -= sizeof(struct NAME(ucpustate));
		/* Only save the FPU state if it is in use. */
		if (PERTASK_GET(this_fpustate)) {
			/* Only allocate what we need for the used FPU state */
			usp -= x86_fpustate_variant == FPU_STATE_SSTATE
			       ? sizeof(struct sfpustate)
			       : sizeof(struct NAME(xfpustate));
			user_fpustate = (struct NAME(fpustate) *)usp;
			validate_writable(user_fpustate,
			                  MIN_C(sizeof(struct sfpustate),
			                        sizeof(struct NAME(xfpustate))));
			COMPILER_WRITE_BARRIER();
			user_fpustate = NAME2(fpustate, _saveinto)(user_fpustate);
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
#ifdef DEFINE_RAISE32
	user_ucontext->uc_mcontext.mc_context.ucs_gpregs.gp_edi = (u32)gpregs_getpdi(&state->ics_gpregs);
	user_ucontext->uc_mcontext.mc_context.ucs_gpregs.gp_esi = (u32)gpregs_getpsi(&state->ics_gpregs);
	user_ucontext->uc_mcontext.mc_context.ucs_gpregs.gp_ebp = (u32)gpregs_getpbp(&state->ics_gpregs);
	user_ucontext->uc_mcontext.mc_context.ucs_gpregs.gp_esp = (u32)(uintptr_t)orig_usp;
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
	user_ucontext->uc_mcontext.mc_context.ucs_eip           = (u32)icpustate_getpip(state);
#else /* DEFINE_RAISE32 */
	user_ucontext->uc_mcontext.mc_context.ucs_gpregs.gp_rdi = (u64)gpregs_getpdi(&state->ics_gpregs);
	user_ucontext->uc_mcontext.mc_context.ucs_gpregs.gp_rsi = (u64)gpregs_getpsi(&state->ics_gpregs);
	user_ucontext->uc_mcontext.mc_context.ucs_gpregs.gp_rbp = (u64)gpregs_getpbp(&state->ics_gpregs);
	user_ucontext->uc_mcontext.mc_context.ucs_gpregs.gp_rsp = (u64)(uintptr_t)orig_usp;
	user_ucontext->uc_mcontext.mc_context.ucs_gpregs.gp_rbx = (u64)gpregs_getpbx(&state->ics_gpregs);
	user_ucontext->uc_mcontext.mc_context.ucs_gpregs.gp_rdx = (u64)gpregs_getpdx(&state->ics_gpregs);
	user_ucontext->uc_mcontext.mc_context.ucs_gpregs.gp_rcx = (u64)gpregs_getpcx(&state->ics_gpregs);
	user_ucontext->uc_mcontext.mc_context.ucs_gpregs.gp_rax = (u64)gpregs_getpax(&state->ics_gpregs);
#ifdef __x86_64__
	user_ucontext->uc_mcontext.mc_context.ucs_gpregs.gp_r15 = (u64)gpregs_getp15(&state->ics_gpregs);
	user_ucontext->uc_mcontext.mc_context.ucs_gpregs.gp_r14 = (u64)gpregs_getp14(&state->ics_gpregs);
	user_ucontext->uc_mcontext.mc_context.ucs_gpregs.gp_r13 = (u64)gpregs_getp13(&state->ics_gpregs);
	user_ucontext->uc_mcontext.mc_context.ucs_gpregs.gp_r12 = (u64)gpregs_getp12(&state->ics_gpregs);
	user_ucontext->uc_mcontext.mc_context.ucs_gpregs.gp_r11 = (u64)gpregs_getp11(&state->ics_gpregs);
	user_ucontext->uc_mcontext.mc_context.ucs_gpregs.gp_r10 = (u64)gpregs_getp10(&state->ics_gpregs);
	user_ucontext->uc_mcontext.mc_context.ucs_gpregs.gp_r9  = (u64)gpregs_getp9(&state->ics_gpregs);
	user_ucontext->uc_mcontext.mc_context.ucs_gpregs.gp_r8  = (u64)gpregs_getp8(&state->ics_gpregs);
#else /* __x86_64__ */
	user_ucontext->uc_mcontext.mc_context.ucs_gpregs.gp_r15 = 0;
	user_ucontext->uc_mcontext.mc_context.ucs_gpregs.gp_r14 = 0;
	user_ucontext->uc_mcontext.mc_context.ucs_gpregs.gp_r13 = 0;
	user_ucontext->uc_mcontext.mc_context.ucs_gpregs.gp_r12 = 0;
	user_ucontext->uc_mcontext.mc_context.ucs_gpregs.gp_r11 = 0;
	user_ucontext->uc_mcontext.mc_context.ucs_gpregs.gp_r10 = 0;
	user_ucontext->uc_mcontext.mc_context.ucs_gpregs.gp_r9  = 0;
	user_ucontext->uc_mcontext.mc_context.ucs_gpregs.gp_r8  = 0;
#endif /* !__x86_64__ */
	user_ucontext->uc_mcontext.mc_context.ucs_sgregs.sg_gs     = icpustate_getgs(state);
	user_ucontext->uc_mcontext.mc_context.ucs_sgregs.sg_fs     = icpustate_getfs(state);
	user_ucontext->uc_mcontext.mc_context.ucs_sgregs.sg_es     = icpustate_getes(state);
	user_ucontext->uc_mcontext.mc_context.ucs_sgregs.sg_ds     = icpustate_getds(state);
	user_ucontext->uc_mcontext.mc_context.ucs_sgbase.sg_fsbase = x86_get_user_fsbase();
	user_ucontext->uc_mcontext.mc_context.ucs_sgbase.sg_gsbase = x86_get_user_gsbase();
	user_ucontext->uc_mcontext.mc_context.ucs_cs               = icpustate_getcs(state);
	user_ucontext->uc_mcontext.mc_context.ucs_ss               = icpustate_getss(state);
	user_ucontext->uc_mcontext.mc_context.ucs_rflags           = (u64)icpustate_getpflags(state);
	user_ucontext->uc_mcontext.mc_context.ucs_rip              = (u64)icpustate_getpip(state);
#endif /* !DEFINE_RAISE32 */

	user_sc_info = NULL;
	if (sc_info) {
		unsigned int argc;
		size_t ob_size;
		/* Only copy data up to the first unused argument. */
		for (argc = NAME2(kernel_syscall, _regcnt)(sc_info->rsi_sysno); argc; --argc) {
			if (sc_info->rsi_flags & RPC_SYSCALL_INFO_FREGVALID(argc - 1))
				break;
		}
		ob_size = (offsetof(struct NAME(rpc_syscall_info), rsi_regs)) +
		          (argc * sizeof(NAME(u)));
		usp -= ob_size;
		user_sc_info = (USER CHECKED struct NAME(rpc_syscall_info) *)usp;
		validate_writable(user_sc_info, ob_size);
		COMPILER_WRITE_BARRIER();
		NAME(rpc_syscall_info_to_rpc_syscall_info)(sc_info, user_sc_info, argc);
	}

	/* At this point, we must setup everything to restore:
	 * >> if (must_restore_sigmask)
	 * >>     RESTORE_SIGMASK(user_sigset);
	 * >> if (user_fpustate)
	 * >>     RESTORE_FPUSTATE(user_fpustate);
	 * >> RESTORE_UCPUSTATE(&user_ucontext->uc_mcontext.mc_context);
	 * >> if (user_sc_info)
	 * >>     RESTART_SYSTEM_CALL(user_sc_info);
	 */

	if (action->sa_flags & SIGACTION_SA_RESTORER) {
		user_rstor = (NAME(u))(uintptr_t)action->sa_restore;
	} else {
		/* Must push assembly onto the user-stack:
		 * >>     movl  $SYS_rt_sigreturn, %eax
		 * >>     int   $(0x80)
		 */
		/* NOTE: This assembly block's size must be pointer-aligned! */
		PRIVATE byte_t const sigreturn_invoke_assembly[8] = {
			/* movl  $SYS_rt_sigreturn, %eax */
			0xb8,
			(NAME(SYSCALL_VECTOR_SIGRETURN) >> 0) & 0xff,
			(NAME(SYSCALL_VECTOR_SIGRETURN) >> 8) & 0xff,
			(NAME(SYSCALL_VECTOR_SIGRETURN) >> 16) & 0xff,
			(NAME(SYSCALL_VECTOR_SIGRETURN) >> 24) & 0xff,
#if defined(DEFINE_RAISE64) && defined(__x86_64__)
			/* syscall */
			0x0f, 0x05,
#else /* DEFINE_RAISE64 && __x86_64__ */
			/* int   $(0x80) */
			0xcd, 0x80,
#endif /* !DEFINE_RAISE64 || !__x86_64__ */
			/* Pad to 8 bytes */
			0xcc
		};
		usp -= sizeof(sigreturn_invoke_assembly);
		validate_writable(usp, sizeof(sigreturn_invoke_assembly));
		COMPILER_WRITE_BARRIER();
		memcpy(usp, sigreturn_invoke_assembly, sizeof(sigreturn_invoke_assembly));
		user_rstor = (NAME(u))(uintptr_t)(user_sigrestore_func_t)usp;
	}

	/* Push the arguments for the actual signal handler. */
#ifdef DEFINE_RAISE64
	usp -= 8;
	validate_writable(usp, 8);
	((u64 *)usp)[0] = (u64)user_rstor;                   /* Return address */
	gpregs_setpdi(&state->ics_gpregs, (uintptr_t)signo); /* signo_t signo */
	if (action->sa_flags & SIGACTION_SA_SIGINFO) {
		gpregs_setpsi(&state->ics_gpregs, (uintptr_t)user_siginfo);  /* siginfo64_t *info */
		gpregs_setpdx(&state->ics_gpregs, (uintptr_t)user_ucontext); /* struct ucontext64 *ctx */
	}
#else /* DEFINE_RAISE64 */
	if (action->sa_flags & SIGACTION_SA_SIGINFO) {
		usp -= 4 * sizeof(u32);
		validate_writable(usp, 4 * sizeof(u32));
		((u32 *)usp)[0] = (u32)user_rstor;               /* Return address */
		((u32 *)usp)[1] = (u32)signo;                    /* signo_t signo */
		((u32 *)usp)[2] = (u32)(uintptr_t)user_siginfo;  /* siginfo32_t *info */
		((u32 *)usp)[3] = (u32)(uintptr_t)user_ucontext; /* struct ucontext32 *ctx */
	} else {
		usp -= 2 * sizeof(u32);
		validate_writable(usp, 2 * sizeof(u32));
		((u32 *)usp)[0] = (u32)user_rstor; /* Return address */
		((u32 *)usp)[1] = (u32)signo;      /* signo_t signo */
	}
#endif /* !DEFINE_RAISE64 */


#ifdef DEFINE_RAISE64
	/* Setup the user-space to-be invoked with the following register state:
	 *   - %rbp == &user_ucontext->uc_mcontext.mc_context
	 *   - %rbx == user_fpustate ?: NULL
	 *   - %r12 == must_restore_sigmask ? user_sigset : NULL
	 *   - %r13 == user_sc_info ?: NULL
	 * NOTE: This register state is what is expected by  `sys_sigreturn'
	 *       Note also that  we can only  use callee-preserve  registers
	 *       here, as all other registers may be clobbered by the signal
	 *       handler itself. */
	gpregs_setpbp(&state->ics_gpregs, (u64)(uintptr_t)&user_ucontext->uc_mcontext.mc_context);
	gpregs_setpbx(&state->ics_gpregs, (u64)(uintptr_t)user_fpustate);
	gpregs_setp12(&state->ics_gpregs, (u64)(uintptr_t)(must_restore_sigmask ? user_sigset : NULL));
	gpregs_setp13(&state->ics_gpregs, (u64)(uintptr_t)user_sc_info);
#else /* DEFINE_RAISE64 */
	/* Setup the user-space to-be invoked with the following register state:
	 *   - %ebp == &user_ucontext->uc_mcontext.mc_context
	 *   - %ebx == user_fpustate ?: NULL
	 *   - %esi == must_restore_sigmask ? user_sigset : NULL
	 *   - %edi == user_sc_info ?: NULL
	 * NOTE: This register state is what is expected by  `sys_sigreturn'
	 *       Note also that  we can only  use callee-preserve  registers
	 *       here, as all other registers may be clobbered by the signal
	 *       handler itself. */
	gpregs_setpbp(&state->ics_gpregs, (u32)(uintptr_t)&user_ucontext->uc_mcontext.mc_context);
	gpregs_setpbx(&state->ics_gpregs, (u32)(uintptr_t)user_fpustate);
	gpregs_setpsi(&state->ics_gpregs, (u32)(uintptr_t)(must_restore_sigmask ? user_sigset : NULL));
	gpregs_setpdi(&state->ics_gpregs, (u32)(uintptr_t)user_sc_info);
#endif /* !DEFINE_RAISE64 */
	icpustate_setpip(state, (NAME(u))(uintptr_t)action->sa_handler);
	icpustate_setuserpsp(state, (NAME(u))(uintptr_t)usp);
	{
		union x86_user_eflags_mask word;
		word.uem_word = atomic64_read(&x86_user_eflags_mask);
		/* Mask %eflags, as specified by `x86_user_eflags_mask' */
		icpustate_mskpflags(state, word.uem_mask, word.uem_flag);
	}
	return state;
}


DECL_END

#undef NAME
#undef NAME2
#undef DEFINE_RAISE32
#undef DEFINE_RAISE64
