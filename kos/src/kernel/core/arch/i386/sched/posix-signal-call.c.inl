/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifdef __INTELLISENSE__
#define _KOS_SOURCE 1
#define _KOS_KERNEL_SOURCE 1
#include "posix-signal.c"
#define DEFINE_x86_userexcept_callsignal32
//#define DEFINE_x86_userexcept_callsignal64
#endif /* __INTELLISENSE__ */

#include <kernel/rt/except-syscall.h> /* CONFIG_HAVE_KERNEL_USERPROCMASK */
#include <sched/sigaction.h>
#include <sched/sigmask.h>
#include <sched/x86/eflags-mask.h>

#include <hybrid/align.h>

#include <bits/os/sigaction.h>

#include <assert.h>
#include <signal.h>

#if (defined(DEFINE_x86_userexcept_callsignal32) + \
     defined(DEFINE_x86_userexcept_callsignal64)) != 1
#error "Must #define exactly one of these"
#endif /* ... */

DECL_BEGIN

#ifndef __x86_64__
#ifdef DEFINE_x86_userexcept_callsignal64
#error "Can't define 64-bit signal-raise functions on i386"
#endif /* DEFINE_x86_userexcept_callsignal64 */
#define LOCAL_userexcept_callsignal userexcept_callsignal
#elif defined(DEFINE_x86_userexcept_callsignal64)
#define LOCAL_userexcept_callsignal x86_userexcept_callsignal64
#elif defined(DEFINE_x86_userexcept_callsignal32)
#define LOCAL_userexcept_callsignal x86_userexcept_callsignal32
#endif /* ... */

#ifdef DEFINE_x86_userexcept_callsignal64
#define LOCAL_struct_rpc_syscall_info struct rpc_syscall_info64
#define LOCAL_uintptr_t               u64
#define LOCAL_siginfo_t               struct __siginfox64_struct
#define LOCAL_ucontext_t              struct __ucontextx64
#define LOCAL_struct_fpustate         struct fpustate64
#define LOCAL_struct_xfpustate        struct xfpustate64
#define LOCAL_struct_sigset_with_size struct __sigset_with_sizex64
#define LOCAL_SIX_USER_MAX_SIZE       __SIX64_USER_MAX_SIZE
#define LOCAL_SIX_KERNEL_MAX_SIZE     __SIX64_KERNEL_MAX_SIZE
#define LOCAL_fpustate_saveinto       fpustate64_saveinto
#define LOCAL_siginfo_encode          siginfo_to_siginfox64
#define LOCAL_struct_ucpustate        struct ucpustate64
#define LOCAL_gp_Pdi                  gp_rdi
#define LOCAL_gp_Psi                  gp_rsi
#define LOCAL_gp_Pbp                  gp_rbp
#define LOCAL_gp_Psp                  gp_rsp
#define LOCAL_gp_Pbx                  gp_rbx
#define LOCAL_gp_Pdx                  gp_rdx
#define LOCAL_gp_Pcx                  gp_rcx
#define LOCAL_gp_Pax                  gp_rax
#define LOCAL_ucs_Pflags              ucs_rflags
#define LOCAL_ucs_Pip                 ucs_rip
#define LOCAL_kernel_syscall_regcnt   kernel_syscall64_regcnt
#define LOCAL_rpc_syscall_info_encode rpc_syscall_info_to_rpc_syscall_info64
#define LOCAL_NR_ksigreturn           __NR64_ksigreturn
#else /* DEFINE_x86_userexcept_callsignal64 */
#define LOCAL_struct_rpc_syscall_info struct rpc_syscall_info32
#define LOCAL_uintptr_t               u32
#define LOCAL_siginfo_t               struct __siginfox32_struct
#define LOCAL_ucontext_t              struct __ucontextx32
#define LOCAL_struct_fpustate         struct fpustate32
#define LOCAL_struct_xfpustate        struct xfpustate32
#define LOCAL_struct_sigset_with_size struct __sigset_with_sizex32
#define LOCAL_SIX_USER_MAX_SIZE       __SIX32_USER_MAX_SIZE
#define LOCAL_SIX_KERNEL_MAX_SIZE     __SIX32_KERNEL_MAX_SIZE
#define LOCAL_fpustate_saveinto       fpustate32_saveinto
#define LOCAL_siginfo_encode          siginfo_to_siginfox32
#define LOCAL_struct_ucpustate        struct ucpustate32
#define LOCAL_gp_Pdi                  gp_edi
#define LOCAL_gp_Psi                  gp_esi
#define LOCAL_gp_Pbp                  gp_ebp
#define LOCAL_gp_Psp                  gp_esp
#define LOCAL_gp_Pbx                  gp_ebx
#define LOCAL_gp_Pdx                  gp_edx
#define LOCAL_gp_Pcx                  gp_ecx
#define LOCAL_gp_Pax                  gp_eax
#define LOCAL_ucs_Pflags              ucs_eflags
#define LOCAL_ucs_Pip                 ucs_eip
#define LOCAL_kernel_syscall_regcnt   kernel_syscall32_regcnt
#define LOCAL_rpc_syscall_info_encode rpc_syscall_info_to_rpc_syscall_info32
#define LOCAL_NR_ksigreturn           __NR32_ksigreturn
#endif /* !DEFINE_x86_userexcept_callsignal64 */


/* Update the given  `state' to raise  the specified `siginfo'  as
 * a user-space signal  within the calling  thread. The caller  is
 * responsible  to  handle   special  signal  handlers   (`SIG_*')
 * before calling this function! This function should only be used
 * to  enqueue the execution of a signal handler with a user-space
 * entry point.
 *
 * Functionality  like  `SA_RESETHAND', or  system call
 * restart selection must be implemented by the caller.
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
#if !defined(__x86_64__) && defined(DEFINE_x86_userexcept_callsignal32)
PUBLIC
#else /* !__x86_64__ && DEFINE_x86_userexcept_callsignal32 */
PRIVATE
#endif /* __x86_64__ || !DEFINE_x86_userexcept_callsignal32 */
ATTR_RETNONNULL WUNUSED NONNULL((1, 2, 3)) struct icpustate *FCALL
LOCAL_userexcept_callsignal(struct icpustate *__restrict state,
                            struct kernel_sigaction const *__restrict action,
                            siginfo_t const *__restrict siginfo,
                            struct rpc_syscall_info const *sc_info)
		THROWS(E_SEGFAULT) {
	NCX byte_t *usp, *orig_usp;
	bool must_restore_sigmask;
	sigset_t old_sigmask;
	NCX LOCAL_siginfo_t *user_siginfo;
	NCX LOCAL_ucontext_t *user_ucontext;
	NCX LOCAL_struct_sigset_with_size *user_sigset;
	NCX LOCAL_struct_fpustate *user_fpustate;
	NCX LOCAL_struct_rpc_syscall_info *user_sc_info;
	NCX LOCAL_uintptr_t user_rstor;
	assert(sigvalid(siginfo->si_signo));

	/* Figure out how, and if we need to mask signals. */
	must_restore_sigmask = false;
	if (!sigisemptyset(&action->sa_mask) || !(action->sa_flags & SA_NODEFER)) {
		sigset_t maskthese;
		memcpy(&maskthese, &action->sa_mask, sizeof(sigset_t));

		/* Unless `SA_NODEFER' is set, mask the signal that is being invoked. */
		if (!(action->sa_flags & SA_NODEFER))
			sigaddset(&maskthese, siginfo->si_signo);

		/* Never mask SIGKILL or SIGSTOP */
		sigdelset_nmi(&maskthese);

		/* If changes were made, then we must restore `old_sigmask' later on. */
		must_restore_sigmask = sigmask_getmask_and_blockmask(&old_sigmask, &maskthese);
	} else if (action->sa_flags & SA_SIGINFO) {
		/* Still need the old mask for `user_ucontext->uc_sigmask' */
		sigmask_getmask(&old_sigmask);
	}

	/* Figure out which stack we should write data to. */
	orig_usp = (NCX byte_t *)icpustate_getusersp(state);
	usp      = orig_usp;
	/* Check if sigaltstack should be used. */
	if (action->sa_flags & SA_ONSTACK) {
		/* TODO: SS_AUTODISARM */
		usp = (NCX byte_t *)PERTASK_GET(this_user_except_handler.ueh_stack);
	}
#ifdef DEFINE_x86_userexcept_callsignal64
	else {
		usp -= 128; /* Red zone (XXX: Make this configurable?) */
	}
#endif /* DEFINE_x86_userexcept_callsignal64 */

	/* Force proper alignment. */
#ifdef DEFINE_x86_userexcept_callsignal32
	usp = (NCX byte_t *)((uintptr_t)usp & ~3);
#else /* DEFINE_x86_userexcept_callsignal32 */
	usp = (NCX byte_t *)((uintptr_t)usp & ~7);
#endif /* !DEFINE_x86_userexcept_callsignal32 */

	/* At this point, the following options affect how we need to set up the stack:
	 *  - sc_info:                        When non-NULL, we must restart an interrupted system call
	 *  - must_restore_sigmask:           When true, we must restore `old_sigmask'
	 *  - action->sa_flags & SA_SIGINFO:  When true, we must invoke a 3-argument handler
	 *  - action->sa_flags & SA_RESTORER: When true, we must have the handler return to `sa_restore' */

	user_siginfo  = NULL;
	user_ucontext = NULL;
	user_sigset   = NULL;
	user_fpustate = NULL;
	if (action->sa_flags & SA_SIGINFO) {
		/* TODO: Use the sigsetsize passed to `sys_rt_sigaction()' when this handler was installed */
		size_t sigsetsize = sizeof(sigset_t);

		/* In 3-argument mode, we always have to push everything... */
		static_assert(LOCAL_SIX_USER_MAX_SIZE >= LOCAL_SIX_KERNEL_MAX_SIZE);
		static_assert(LOCAL_SIX_KERNEL_MAX_SIZE == sizeof(LOCAL_siginfo_t));

		/* Try to have the padding of `siginfo_t' overlap with `ucontextN_t' */
#define sizeof_LOCAL_ucontext_t (offsetof(LOCAL_ucontext_t, uc_sigmask) + sigsetsize)
#define EFFECTIVE_PADDING_SIGINFO_T (LOCAL_SIX_USER_MAX_SIZE - LOCAL_SIX_KERNEL_MAX_SIZE)
#define EFFECTIVE_SIZEOF_SIGINFO_T                               \
		(EFFECTIVE_PADDING_SIGINFO_T <= sizeof_LOCAL_ucontext_t \
		 ? LOCAL_SIX_KERNEL_MAX_SIZE                             \
		 : (LOCAL_SIX_USER_MAX_SIZE - sizeof_LOCAL_ucontext_t))

		/* Must push a full `ucontextN_t' */
		user_ucontext = (LOCAL_ucontext_t *)(usp - sizeof_LOCAL_ucontext_t);
		validate_writable((byte_t *)user_ucontext - EFFECTIVE_SIZEOF_SIGINFO_T,
		                  sizeof_LOCAL_ucontext_t + EFFECTIVE_SIZEOF_SIGINFO_T);

		COMPILER_WRITE_BARRIER();
		user_ucontext->uc_link              = (LOCAL_ucontext_t *)NULL; /* Unused... */
		user_ucontext->uc_stack.ss_sp       = usp;
		user_ucontext->uc_stack.ss_flags    = SS_ONSTACK;
		user_ucontext->uc_stack.ss_size     = 0;
		user_ucontext->uc_mcontext.mc_cr2   = 0;
		user_ucontext->uc_mcontext.mc_flags = 0;

		/* Fill in the `struct ucontext's signal mask (using the requested signal mask size) */
		{
			size_t limited_sigsetsize = sigsetsize;
			if (limited_sigsetsize > sizeof(sigset_t))
				limited_sigsetsize = sizeof(sigset_t);
			memset(mempcpy(&user_ucontext->uc_sigmask,
			               &old_sigmask, limited_sigsetsize),
			       0xff, sigsetsize - limited_sigsetsize);
		}
		if (siginfo->si_signo == SIGSEGV) {
			user_ucontext->uc_mcontext.mc_cr2 = (ulongptr_t)siginfo->si_addr;
			user_ucontext->uc_mcontext.mc_flags |= MCONTEXT_FLAG_HAVECR2;
		}
		if (PERTASK_TEST(this_fpustate)) {
			user_fpustate = &user_ucontext->uc_mcontext.mc_fpu;
			LOCAL_fpustate_saveinto(user_fpustate);
			user_ucontext->uc_mcontext.mc_flags |= MCONTEXT_FLAG_HAVEFPU;
		}
		usp -= EFFECTIVE_SIZEOF_SIGINFO_T + sizeof_LOCAL_ucontext_t;

		/* Copy signal information into user-space. */
		user_siginfo = (LOCAL_siginfo_t *)usp;
		LOCAL_siginfo_encode(siginfo, user_siginfo);

		if (must_restore_sigmask) {
			/* Allocate the `struct sigset_with_size' to-be loaded by `sys_ksigreturn(2)'. */
			user_sigset             = (LOCAL_struct_sigset_with_size *)usp;
			user_sigset->sws_sigset = (typeof(user_sigset->sws_sigset))(uintptr_t)&user_ucontext->uc_sigmask;
			user_sigset->sws_sigsiz = (typeof(user_sigset->sws_sigsiz))sigsetsize;
			usp -= sizeof(LOCAL_struct_sigset_with_size);
		}

#undef EFFECTIVE_PADDING_SIGINFO_T
#undef EFFECTIVE_SIZEOF_SIGINFO_T
#undef sizeof_LOCAL_ucontext_t
	} else {
		/* Only push the bare minimum */
		user_ucontext = container_of((LOCAL_struct_ucpustate *)(usp - sizeof(LOCAL_struct_ucpustate)),
		                             LOCAL_ucontext_t, uc_mcontext.mc_context);
		validate_writable(user_ucontext, sizeof(LOCAL_struct_ucpustate));
		COMPILER_WRITE_BARRIER();
		usp -= sizeof(LOCAL_struct_ucpustate);

		/* Only save the FPU state if it is in use. */
		if (PERTASK_TEST(this_fpustate)) {
			/* Only allocate what we need for the used FPU state */
			usp -= x86_fpustate_variant == FPU_STATE_SSTATE
			       ? sizeof(struct sfpustate)
			       : sizeof(LOCAL_struct_xfpustate);
			user_fpustate = (LOCAL_struct_fpustate *)usp;
			validate_writable(user_fpustate,
			                  MIN_C(sizeof(struct sfpustate),
			                        sizeof(LOCAL_struct_xfpustate)));
			COMPILER_WRITE_BARRIER();
			LOCAL_fpustate_saveinto(user_fpustate);
		}

		/* Only save the sigmask if it was changed.
		 *
		 * NOTE: In this case we can always use the kernel-space sigset-size,
		 *       as this structure (even though it resides on the user-stack)
		 *       isn't actually exposed to user-space. -- It's only there  so
		 *       that sys_ksigreturn(2) will be able to restore it upon being
		 *       called. */
		if (must_restore_sigmask) {
			NCX sigset_t *user_sigbuf;
			usp -= sizeof(sigset_t);
			user_sigbuf = (NCX sigset_t *)usp;
			usp -= sizeof(LOCAL_struct_sigset_with_size);
			user_sigset = (NCX LOCAL_struct_sigset_with_size *)usp;
			validate_writable(usp, sizeof(LOCAL_struct_sigset_with_size) + sizeof(sigset_t));
			COMPILER_WRITE_BARRIER();
			user_sigbuf = (NCX sigset_t *)memcpy(user_sigbuf, &old_sigmask, sizeof(sigset_t));
			user_sigset->sws_sigset = (typeof(user_sigset->sws_sigset))(uintptr_t)user_sigbuf;
			user_sigset->sws_sigsiz = (typeof(user_sigset->sws_sigsiz))sizeof(sigset_t);
		}
	}

	/* Fill in return context information */

	/* General purpose registers... */
	user_ucontext->uc_mcontext.mc_context.ucs_gpregs.LOCAL_gp_Pdi = (LOCAL_uintptr_t)gpregs_getpdi(&state->ics_gpregs);
	user_ucontext->uc_mcontext.mc_context.ucs_gpregs.LOCAL_gp_Psi = (LOCAL_uintptr_t)gpregs_getpsi(&state->ics_gpregs);
	user_ucontext->uc_mcontext.mc_context.ucs_gpregs.LOCAL_gp_Pbp = (LOCAL_uintptr_t)gpregs_getpbp(&state->ics_gpregs);
	user_ucontext->uc_mcontext.mc_context.ucs_gpregs.LOCAL_gp_Psp = (LOCAL_uintptr_t)(uintptr_t)orig_usp;
	user_ucontext->uc_mcontext.mc_context.ucs_gpregs.LOCAL_gp_Pbx = (LOCAL_uintptr_t)gpregs_getpbx(&state->ics_gpregs);
	user_ucontext->uc_mcontext.mc_context.ucs_gpregs.LOCAL_gp_Pdx = (LOCAL_uintptr_t)gpregs_getpdx(&state->ics_gpregs);
	user_ucontext->uc_mcontext.mc_context.ucs_gpregs.LOCAL_gp_Pcx = (LOCAL_uintptr_t)gpregs_getpcx(&state->ics_gpregs);
	user_ucontext->uc_mcontext.mc_context.ucs_gpregs.LOCAL_gp_Pax = (LOCAL_uintptr_t)gpregs_getpax(&state->ics_gpregs);
#ifdef DEFINE_x86_userexcept_callsignal64
	user_ucontext->uc_mcontext.mc_context.ucs_gpregs.gp_r15 = gpregs_getp15(&state->ics_gpregs);
	user_ucontext->uc_mcontext.mc_context.ucs_gpregs.gp_r14 = gpregs_getp14(&state->ics_gpregs);
	user_ucontext->uc_mcontext.mc_context.ucs_gpregs.gp_r13 = gpregs_getp13(&state->ics_gpregs);
	user_ucontext->uc_mcontext.mc_context.ucs_gpregs.gp_r12 = gpregs_getp12(&state->ics_gpregs);
	user_ucontext->uc_mcontext.mc_context.ucs_gpregs.gp_r11 = gpregs_getp11(&state->ics_gpregs);
	user_ucontext->uc_mcontext.mc_context.ucs_gpregs.gp_r10 = gpregs_getp10(&state->ics_gpregs);
	user_ucontext->uc_mcontext.mc_context.ucs_gpregs.gp_r9  = gpregs_getp9(&state->ics_gpregs);
	user_ucontext->uc_mcontext.mc_context.ucs_gpregs.gp_r8  = gpregs_getp8(&state->ics_gpregs);
#endif /* DEFINE_x86_userexcept_callsignal64 */

	/* Segment registers... */
	user_ucontext->uc_mcontext.mc_context.ucs_sgregs.sg_gs = icpustate_getgs(state);
	user_ucontext->uc_mcontext.mc_context.ucs_sgregs.sg_fs = icpustate_getfs(state);
	user_ucontext->uc_mcontext.mc_context.ucs_sgregs.sg_es = icpustate_getes(state);
	user_ucontext->uc_mcontext.mc_context.ucs_sgregs.sg_ds = icpustate_getds(state);
	user_ucontext->uc_mcontext.mc_context.ucs_cs           = icpustate_getcs(state);
	user_ucontext->uc_mcontext.mc_context.ucs_ss           = icpustate_getss(state);

	/* PC and FLAGS register... */
	user_ucontext->uc_mcontext.mc_context.LOCAL_ucs_Pflags = (LOCAL_uintptr_t)icpustate_getpflags(state);
	user_ucontext->uc_mcontext.mc_context.LOCAL_ucs_Pip    = (LOCAL_uintptr_t)icpustate_getpip(state);

	/* Segment base registers... */
#ifdef DEFINE_x86_userexcept_callsignal64
	user_ucontext->uc_mcontext.mc_context.ucs_sgbase.sg_fsbase = x86_get_user_fsbase();
	user_ucontext->uc_mcontext.mc_context.ucs_sgbase.sg_gsbase = x86_get_user_gsbase();
#endif /* DEFINE_x86_userexcept_callsignal64 */

	/* Encode system call restart information. */
	user_sc_info = NULL;
	if (sc_info != NULL) {
		unsigned int argc;
		size_t sizeof_sc_info;

		/* Only copy data up to the first unused argument. */
		for (argc = LOCAL_kernel_syscall_regcnt(sc_info->rsi_sysno); argc; --argc) {
			if (sc_info->rsi_flags & RPC_SYSCALL_INFO_FREGVALID(argc - 1))
				break;
		}
		sizeof_sc_info = (offsetof(LOCAL_struct_rpc_syscall_info, rsi_regs)) +
		                 (argc * sizeof(LOCAL_uintptr_t));
		usp -= sizeof_sc_info;
		user_sc_info = (NCX LOCAL_struct_rpc_syscall_info *)usp;
		validate_writable(user_sc_info, sizeof_sc_info);
		COMPILER_WRITE_BARRIER();
		LOCAL_rpc_syscall_info_encode(sc_info, user_sc_info, argc);
	}

	/* At this point, we must setup everything to restore:
	 * >> if (user_sigset)
	 * >>     RESTORE_SIGMASK(user_sigset);
	 * >> if (user_fpustate)
	 * >>     RESTORE_FPUSTATE(user_fpustate);
	 * >> RESTORE_UCPUSTATE(&user_ucontext->uc_mcontext.mc_context);
	 * >> if (user_sc_info)
	 * >>     RESTART_SYSTEM_CALL(user_sc_info);
	 */

	if (action->sa_flags & SA_RESTORER) {
		user_rstor = (LOCAL_uintptr_t)(uintptr_t)action->sa_restorer;
	} else {
		/* Must push assembly onto the user-stack:
		 * >>     movl  $SYS_ksigreturn, %eax
		 * >>     int   $(0x80) */
		/* NOTE: This assembly block's size must be pointer-aligned! */
		PRIVATE byte_t const sigreturn_invoke_assembly[8] = {
			/* movl  $SYS_ksigreturn, %eax */
			0xb8,
			(LOCAL_NR_ksigreturn >> 0) & 0xff,
			(LOCAL_NR_ksigreturn >> 8) & 0xff,
			(LOCAL_NR_ksigreturn >> 16) & 0xff,
			(LOCAL_NR_ksigreturn >> 24) & 0xff,
#ifdef DEFINE_x86_userexcept_callsignal64
			/* syscall */
			0x0f, 0x05,
#else /* DEFINE_x86_userexcept_callsignal64 */
			/* int   $(0x80) */
			0xcd, 0x80,
#endif /* !DEFINE_x86_userexcept_callsignal64 */
			/* Pad to 8 bytes */
			0xcc
		};
		usp -= sizeof(sigreturn_invoke_assembly);
		validate_writable(usp, sizeof(sigreturn_invoke_assembly));
		COMPILER_WRITE_BARRIER();
		memcpy(usp, sigreturn_invoke_assembly, sizeof(sigreturn_invoke_assembly));
		user_rstor = (LOCAL_uintptr_t)(uintptr_t)usp;
	}

	/* Push the arguments for the actual signal handler. */
#ifdef DEFINE_x86_userexcept_callsignal64
	/* SYSVABI specs require the stack pointer to be 16-byte aligned _BEFORE_ the call.
	 * This way, after +8 for the return  address and +8 for a potential  `pushq %rbp',
	 * the stack will be 16-byte aligned once again. */
	usp = (NCX byte_t *)FLOOR_ALIGN((uintptr_t)usp, 16);

	/* Push return address */
	usp -= 8;
	validate_writable(usp, 8);
	((u64 *)usp)[0] = (u64)user_rstor;

	gpregs_setpdi(&state->ics_gpregs, (uintptr_t)siginfo->si_signo); /* signo_t signo */
	if (action->sa_flags & SA_SIGINFO) {
		gpregs_setpsi(&state->ics_gpregs, (uintptr_t)user_siginfo);  /* siginfo64_t *info */
		gpregs_setpdx(&state->ics_gpregs, (uintptr_t)user_ucontext); /* struct ucontext64 *ctx */
	}
#else /* DEFINE_x86_userexcept_callsignal64 */
	if (action->sa_flags & SA_SIGINFO) {
		usp -= 4 * sizeof(u32);
		validate_writable(usp, 4 * sizeof(u32));
		((u32 *)usp)[0] = (u32)user_rstor;               /* Return address */
		((u32 *)usp)[1] = (u32)siginfo->si_signo;        /* signo_t signo */
		((u32 *)usp)[2] = (u32)(uintptr_t)user_siginfo;  /* siginfo32_t *info */
		((u32 *)usp)[3] = (u32)(uintptr_t)user_ucontext; /* struct ucontext32 *ctx */
	} else {
		usp -= 2 * sizeof(u32);
		validate_writable(usp, 2 * sizeof(u32));
		((u32 *)usp)[0] = (u32)user_rstor;        /* Return address */
		((u32 *)usp)[1] = (u32)siginfo->si_signo; /* signo_t signo */
	}
#endif /* !DEFINE_x86_userexcept_callsignal64 */


#ifdef DEFINE_x86_userexcept_callsignal64
	/* Setup the user-space to-be invoked with the following register state:
	 *   - %rbp == &user_ucontext->uc_mcontext.mc_context
	 *   - %rbx == user_fpustate ?: NULL
	 *   - %r12 == user_sigset ?: NULL
	 *   - %r13 == user_sc_info ?: NULL
	 * NOTE: This register state is what is expected by `sys_ksigreturn'
	 *       Note also that  we can only  use callee-preserve  registers
	 *       here, as all other registers may be clobbered by the signal
	 *       handler itself. */
	gpregs_setpbp(&state->ics_gpregs, (u64)(uintptr_t)&user_ucontext->uc_mcontext.mc_context);
	gpregs_setpbx(&state->ics_gpregs, (u64)(uintptr_t)user_fpustate);
	gpregs_setp12(&state->ics_gpregs, (u64)(uintptr_t)user_sigset);
	gpregs_setp13(&state->ics_gpregs, (u64)(uintptr_t)user_sc_info);
#else /* DEFINE_x86_userexcept_callsignal64 */
	/* Setup the user-space to-be invoked with the following register state:
	 *   - %ebp == &user_ucontext->uc_mcontext.mc_context
	 *   - %ebx == user_fpustate ?: NULL
	 *   - %esi == user_sigset ?: NULL
	 *   - %edi == user_sc_info ?: NULL
	 * NOTE: This register state is what is expected by `sys_ksigreturn'
	 *       Note also that  we can only  use callee-preserve  registers
	 *       here, as all other registers may be clobbered by the signal
	 *       handler itself. */
	gpregs_setpbp(&state->ics_gpregs, (u32)(uintptr_t)&user_ucontext->uc_mcontext.mc_context);
	gpregs_setpbx(&state->ics_gpregs, (u32)(uintptr_t)user_fpustate);
	gpregs_setpsi(&state->ics_gpregs, (u32)(uintptr_t)user_sigset);
	gpregs_setpdi(&state->ics_gpregs, (u32)(uintptr_t)user_sc_info);
#endif /* !DEFINE_x86_userexcept_callsignal64 */

	/* Fill in the actual handler PC and the stack-pointer under which it shall execute. */
	icpustate_setpip(state, (LOCAL_uintptr_t)(uintptr_t)action->sa_handler);
	icpustate_setuserpsp(state, (LOCAL_uintptr_t)(uintptr_t)usp);

	{
		/* Mask `%Pflags', as specified by `x86_user_eflags_mask' */
		union x86_user_eflags_mask_union word;
		word.uem_word = atomic64_read(&x86_user_eflags_mask);
		word.uem_mask &= ~EFLAGS_RF; /* Always clear `EFLAGS_RF' so hw-breakpoints work on signal handler entry */
		icpustate_mskpflags(state, word.uem_mask, word.uem_flag);
	}
	return state;
}


#undef LOCAL_userexcept_callsignal
#undef LOCAL_struct_rpc_syscall_info
#undef LOCAL_uintptr_t
#undef LOCAL_siginfo_t
#undef LOCAL_ucontext_t
#undef LOCAL_struct_fpustate
#undef LOCAL_struct_sigset_with_size
#undef LOCAL_struct_xfpustate
#undef LOCAL_SIX_USER_MAX_SIZE
#undef LOCAL_SIX_KERNEL_MAX_SIZE
#undef LOCAL_fpustate_saveinto
#undef LOCAL_siginfo_encode
#undef LOCAL_struct_ucpustate
#undef LOCAL_gp_Pdi
#undef LOCAL_gp_Psi
#undef LOCAL_gp_Pbp
#undef LOCAL_gp_Psp
#undef LOCAL_gp_Pbx
#undef LOCAL_gp_Pdx
#undef LOCAL_gp_Pcx
#undef LOCAL_gp_Pax
#undef LOCAL_ucs_Pflags
#undef LOCAL_ucs_Pip
#undef LOCAL_kernel_syscall_regcnt
#undef LOCAL_rpc_syscall_info_encode
#undef LOCAL_NR_ksigreturn

DECL_END

#undef DEFINE_x86_userexcept_callsignal64
#undef DEFINE_x86_userexcept_callsignal32
