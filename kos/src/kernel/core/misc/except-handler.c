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
#ifndef GUARD_KERNEL_SRC_MISC_EXCEPT_HANDLER_C
#define GUARD_KERNEL_SRC_MISC_EXCEPT_HANDLER_C 1
#define _KOS_SOURCE 1

/* High-level exception handlers for translating exceptions thrown through
 * system calls or interrupts that  point to user-space return  locations.
 *
 * This also facilitates the handling of RPCs! */

#include <kernel/compiler.h>

#ifdef CONFIG_USE_NEW_RPC
#include <kernel/coredump.h>
#include <kernel/except.h>
#include <kernel/mman.h>
#include <kernel/printk.h>
#include <kernel/rt/except-handler.h>
#include <kernel/syscall-properties.h>
#include <kernel/types.h>
#include <sched/arch/task.h>
#include <sched/cpu.h>
#include <sched/pid.h>
#include <sched/posix-signal.h>
#include <sched/rpc-internal.h>
#include <sched/rpc.h>
#include <sched/scheduler.h>
#include <sched/task.h>

#include <hybrid/atomic.h>

#include <asm/intrin.h>
#include <kos/bits/except.h>
#include <kos/except.h>
#include <kos/kernel/cpu-state-helpers.h>

#include <assert.h>
#include <inttypes.h>
#include <signal.h>
#include <stddef.h>
#include <string.h>

#include <libcpustate/apply.h>
#include <libunwind/cfi.h>
#include <libunwind/dwarf.h>
#include <libunwind/eh_frame.h>
#include <libunwind/unwind.h>

#define kcpustate_get_unwind_exception(state)        __ERROR_REGISTER_STATE_TYPE_RD_UNWIND_EXCEPTION(*(state))
#define kcpustate_set_unwind_exception(state, value) __ERROR_REGISTER_STATE_TYPE_WR_UNWIND_EXCEPTION(*(state), value)

DECL_BEGIN

#ifndef NDEBUG
#define DBG_memset(dst, byte, num_bytes) memset(dst, byte, num_bytes)
#else /* !NDEBUG */
#define DBG_memset(dst, byte, num_bytes) (void)0
#endif /* NDEBUG */

INTERN NOBLOCK void
NOTHROW(FCALL restore_pending_rpcs)(struct pending_rpc *restore) {
	if (restore) {
		struct pending_rpc_slist *list;
		struct pending_rpc *last;
		list = &PERTASK(this_rpcs);
again:
		last = ATOMIC_READ(list->slh_first);
		if (!last) {
			if (!ATOMIC_CMPXCH_WEAK(list->slh_first, NULL, restore))
				goto again;
		} else {
			while (SLIST_NEXT(last, pr_link))
				last = SLIST_NEXT(last, pr_link);
			last->pr_link.sle_next = restore;
		}
	}
}



PRIVATE ATTR_NORETURN void
NOTHROW(FCALL process_exit)(int reason) {
	if (!task_isprocessleader()) {
		/* We need to terminate the _process_; not just this thread!
		 * This can be done by re-using our exit RPC, and sending it
		 * to the process leader. */
		struct pending_rpc *rpc;
		rpc = ATOMIC_XCH(PERTASK(this_taskgroup.tg_thread_exit), NULL);
		/* When `rpc' was already `NULL', then our leader must already be
		 * in the process of exiting, and already took our exit RPC away,
		 * trying to terminate us.
		 * Handle this case by letting it do its thing, even though this
		 * will cause us to use a different exit reason than the leader. */
		if likely(rpc) {
			rpc->pr_kern.k_cookie = (void *)(uintptr_t)(unsigned int)reason;
			if (task_rpc_schedule(task_getprocess(), rpc))
				goto done;
			/* Failed to deliver the RPC because the process
			 * leader has/is already terminated/terminating,
			 * and is no longer able to service any RPCs. */
			pending_rpc_free(rpc);
		}
	}
done:
	task_exit(reason);
}

PRIVATE ATTR_NORETURN NONNULL((1)) void
NOTHROW(FCALL process_exit_for_exception_after_coredump)(struct exception_data const *__restrict error) {
	siginfo_t si;
	/* Try to translate the current exception  into a signal, so that  we
	 * can use that signal code as reason for why the process has exited. */
	if (!error_as_signal(error, &si))
		si.si_signo = SIGILL;
	process_exit(W_EXITCODE(1, si.si_signo) | WCOREFLAG);
}



/* Raise a posix signal in user-space for `siginfo'
 * @param: state:   The user-space CPU state (note that `icpustate_isuser(state)' is assumed!)
 * @param: sc_info: When  non-NULL,  information about  the system  call  that caused  the signal.
 *                  Otherwise,  if this argument  is `NULL', the signal  was caused by user-space,
 *                  such as a user-space program causing an `E_SEGFAULT', as opposed to the kernel
 *                  throwing an `E_FSERROR_FILE_NOT_FOUND'
 *            HINT: Additional information about how the system call was invoked can be extracted
 *                  from       `sc_info->rsi_flags'!       (s.a.        `<kos/asm/rpc-method.h>')
 * @param: siginfo: The signal that is being raised
 * @param: except_info: When non-NULL, `siginfo' was generated through `error_as_signal(&except_info->ei_data)',
 *                  and  if a coredump ends up being generated  as a result of the signal being
 *                  raised, that coredump will include information about `error_info()', rather
 *                  than the given `siginfo'
 * @return: * :     The updated interrupt CPU state, modified to invoke the
 *                  user-space signal  handler  once  user-space  execution
 *                  resumes. */
PRIVATE ATTR_RETNONNULL WUNUSED NONNULL((1, 3)) struct icpustate *FCALL
userexcept_raisesignal(struct icpustate *__restrict state,
                       struct rpc_syscall_info const *sc_info,
                       siginfo_t const *__restrict siginfo,
                       struct exception_info const *except_info)
		THROWS(E_SEGFAULT) {
	struct icpustate *result;
	struct sighand *hand;
	struct kernel_sigaction action;
	/* Raise a POSIX signal */
again_gethand:
	assert(siginfo->si_signo != 0);
	assert(siginfo->si_signo < NSIG);
	if (!THIS_SIGHAND_PTR) {
		action.sa_handler = KERNEL_SIG_DFL;
		action.sa_flags   = 0;
		action.sa_mask    = NULL;
	} else {
		hand   = sighand_ptr_lockread(THIS_SIGHAND_PTR);
		action = hand->sh_actions[siginfo->si_signo - 1];
		xincref(action.sa_mask);
		sync_endread(hand);
	}

	/* Check for special signal handlers. */
	if (action.sa_handler == KERNEL_SIG_DFL)
		action.sa_handler = sighand_default_action(siginfo->si_signo);
	switch ((uintptr_t)(void *)action.sa_handler) {

	case (uintptr_t)KERNEL_SIG_IGN:
		xdecref_unlikely(action.sa_mask);
		if (sc_info && except_info)
			state = userexcept_seterrno(state, sc_info, &except_info->ei_data);
		return state;

	case (uintptr_t)KERNEL_SIG_CORE:
		xdecref_unlikely(action.sa_mask);
		if (except_info) {
			/* If we've gotten here because of a system call, then we can assume that
			 * the exception does have a kernel-space side, and thus we must  include
			 * information about that exception's origin. */
			coredump_create_for_exception(state, except_info, sc_info != NULL);
		} else {
			coredump_create_for_signal(state, siginfo);
		}
		process_exit(W_EXITCODE(1, siginfo->si_signo) | WCOREFLAG);

	case (uintptr_t)KERNEL_SIG_TERM:
		xdecref_unlikely(action.sa_mask);
		process_exit(W_EXITCODE(1, siginfo->si_signo));

	case (uintptr_t)KERNEL_SIG_EXIT:
		xdecref_unlikely(action.sa_mask);
		task_exit(W_EXITCODE(1, siginfo->si_signo));

	case (uintptr_t)KERNEL_SIG_CONT:
		xdecref_unlikely(action.sa_mask);
		/* Continue execution. */
		task_sigcont(THIS_TASK);
		return state;

	case (uintptr_t)KERNEL_SIG_STOP:
		/* TODO: Mask additional signals by looking at `SIGACTION_SA_NODEFER' and `action.sa_mask' */
		xdecref_unlikely(action.sa_mask);
		/* Suspend execution. */
		task_sigstop(W_STOPCODE(siginfo->si_signo));
		return state;

	default: break;
	}

	/* Invoke a regular, old signal handler. */
	{
		FINALLY_XDECREF_UNLIKELY(action.sa_mask);
		result = sighand_raise_signal(state,
		                              &action,
		                              siginfo,
		                              sc_info);
	}
	if unlikely(!result)
		goto again_gethand;
	return result;
}



/* Helper function for `userexcept_raisesignal()' that may be used to
 * raise  the  appropriate  POSIX  signal  for  the  given   `error'.
 * @return: NULL: The given `error' cannot be translated into a posix signal.
 * @return: * :   The updated interrupt CPU state, modified to invoke the
 *                user-space signal  handler  once  user-space  execution
 *                resumes. */
PRIVATE WUNUSED NONNULL((1, 3)) struct icpustate *FCALL
userexcept_raisesignal_from_exception(struct icpustate *__restrict state,
                                      struct rpc_syscall_info const *sc_info,
                                      struct exception_info const *__restrict error)
		THROWS(E_SEGFAULT) {
	siginfo_t siginfo;
	/* Try to translate the given `error' into a signal. */
	if (!error_as_signal(&error->ei_data, &siginfo))
		return NULL;

	/* Include missing information within the signal info. */
	switch (siginfo.si_signo) {

	case SIGSYS:
		siginfo.si_call_addr = (void *)icpustate_getpc(state);
		break;

	default: break;
	}
	return userexcept_raisesignal(state, sc_info, &siginfo, error);
}


/* Unwind a given exception info user-space, either as  an
 * exception, by returning a negative errno, or by raising
 * a posix signal.
 * This function returns the updated CPU state which should
 * be loaded by the caller. */
PRIVATE ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) struct icpustate *
NOTHROW(FCALL userexcept_unwind)(struct icpustate *__restrict state,
                                 struct exception_info *__restrict error,
                                 struct rpc_syscall_info const *sc_info) {
	struct icpustate *result;
again:

	/* Handle/amend special exception codes */
	switch (error->ei_code) {

	case ERROR_CODEOF(E_EXIT_PROCESS):
		process_exit((int)error->ei_data.e_args.e_exit_process.ep_exit_code);

	case ERROR_CODEOF(E_EXIT_THREAD):
		task_exit((int)error->ei_data.e_args.e_exit_thread.et_exit_code);

#ifdef RPC_SYSCALL_INFO_METHOD_OTHER
	case ERROR_CODEOF(E_UNKNOWN_SYSTEMCALL): {
#ifdef RPC_SYSCALL_INFO_METHOD_F3264
		enum { MMASK = RPC_SYSCALL_INFO_FMETHOD & ~RPC_SYSCALL_INFO_METHOD_F3264 };
#else /* RPC_SYSCALL_INFO_METHOD_F3264 */
		enum { MMASK = RPC_SYSCALL_INFO_FMETHOD };
#endif /* !RPC_SYSCALL_INFO_METHOD_F3264 */
		uintptr_t flags;
		if (!sc_info)
			break;
		/* Amend missing information about how a system call was invoked. */
		flags = error->ei_data.e_args.e_unknown_systemcall.us_flags;
#ifdef RPC_SYSCALL_INFO_METHOD_F3264
		if ((flags & MMASK) == (RPC_SYSCALL_INFO_METHOD_OTHER & ~RPC_SYSCALL_INFO_METHOD_F3264))
#else /* RPC_SYSCALL_INFO_METHOD_F3264 */
		if ((flags & MMASK) == (RPC_SYSCALL_INFO_METHOD_OTHER))
#endif /* !RPC_SYSCALL_INFO_METHOD_F3264 */
		{
			flags = (flags & ~MMASK) | (sc_info->rsi_flags & MMASK);
			error->ei_data.e_args.e_unknown_systemcall.us_flags = flags;
		}
	}	break;
#endif /* RPC_SYSCALL_INFO_METHOD_OTHER */

	default: break;
	}

	/* Handle exception unwinding into user-space. */
	TRY {
		if (sc_info != NULL) {
			if (sc_info->rsi_flags & RPC_SYSCALL_INFO_FEXCEPT) {
				/* System call exceptions are enabled. */
				/* Propagate the exception to user-space if handlers are enabled. */
				if ((PERTASK_GET(this_user_except_handler.ueh_mode) &
				     EXCEPT_HANDLER_MODE_MASK) != EXCEPT_HANDLER_MODE_DISABLED) {
					result = userexcept_callhandler(state, sc_info, &error->ei_data);
					if likely(result)
						goto done;
				}
				/* If exceptions don't work, try to propagate a POSIX signal */
				result = userexcept_raisesignal_from_exception(state, sc_info, error);
				if likely(result)
					goto done;
				/* If the exception still cannot be handled, terminate the program. */
				goto terminate_app;
			}
			/* Translate the given `error' into an errno. */
			result = userexcept_seterrno(state, sc_info, &error->ei_data);
			goto done;
		}

		/* Check if signal exceptions should be propagated in non-syscall scenarios. */
		if ((PERTASK_GET(this_user_except_handler.ueh_mode) &
		     EXCEPT_HANDLER_MODE_MASK) == EXCEPT_HANDLER_MODE_SIGHAND) {
			result = userexcept_callhandler(state, sc_info, &error->ei_data);
			if likely(result)
				goto done;
		}
		/* Deliver a signal to the calling user-space thread. */
		result = userexcept_raisesignal_from_exception(state, sc_info, error);
		if likely(result)
			goto done;
	} EXCEPT {
		struct exception_info *tls = error_info();
		if (error_priority(tls->ei_code) > error_priority(error->ei_code)) {
			memcpy(error, tls, sizeof(*error));
			assert(PREEMPTION_ENABLED());
			goto again;
		} else {
			error_printf("raising exception/signal");
		}
	}

terminate_app:
	/* If we've gotten here because of a system call, then we can assume that
	 * the exception does have a kernel-space side, and thus we must  include
	 * information about that exception's origin. */
	coredump_create_for_exception(state, error, sc_info != NULL);
	process_exit_for_exception_after_coredump(&error->ei_data);
	__builtin_unreachable();
done:
	assert(PERTASK_GET(this_exception_info.ei_code) == ERROR_CODEOF(E_OK));
	assert(PERTASK_GET(this_exception_info.ei_flags) == EXCEPT_FNORMAL);
	assert(PERTASK_GET(this_exception_info.ei_nesting) == 0);
	assert(PREEMPTION_ENABLED());
	return result;
}






/* High-level exception handler that must be called by _all_ interrupts
 * and system call invocation wrappers.  This function is very  special
 * in that it _only_ returns when the associated interrupt/syscall must
 * be restarted immediately (for whatever reason).
 *
 * When  anything else needs to be done  in order to handle the currently
 * set exception, then this function won't return normally, but will load
 * the (at that point modified) `state' directly (via `cpu_apply(3)')
 *
 * The implementation of this function serves the function  documented
 * in <kos/rpc.md> under the name `generic_interrupt_or_system_call()'
 *
 * WARNING: When this function returns, it will have cleared the current
 *          exception, as it is also capable of handling (some)  errors,
 *          most notably `E_INTERRUPT_USER_RPC'! */
PUBLIC ATTR_RETNONNULL WUNUSED NONNULL((1)) struct icpustate *
NOTHROW(FCALL userexcept_handler)(struct icpustate *__restrict state,
                                  struct rpc_syscall_info *sc_info) {
	struct pending_rpc_slist pending;
	struct pending_rpc_slist restore;
	struct pending_rpc **restore_plast;
	struct pending_rpc_slist kernel_rpcs;
	struct rpc_context ctx;
	struct exception_info error;
	memcpy(&error, error_info(), sizeof(error));
	assertf(error.ei_code != ERROR_CODEOF(E_OK),
	        "In user exception handler, but no exception was thrown");
	assertf(PERTASK_GET(this_exception_info.ei_flags) == EXCEPT_FNORMAL,
	        "Unexpected exception flags");
	assertf(PERTASK_GET(this_exception_info.ei_nesting) == 0,
	        "There are still saved, nested exception somewhere on our stack");
	assertf(PREEMPTION_ENABLED(),
	        "Preemption must be enabled to propagate exceptions to user-space.");
	assertf(icpustate_isuser(state),
	        "In user exception handler, but return state points to kernel-space");
	/* Assert that there are no active task connections. */
#ifndef NDEBUG
	{
		struct task_connections *self = THIS_CONNECTIONS;
		struct task_connection *con   = self->tcs_con;
		assertf(con == NULL, "con = %p", con);
	}
#endif /* !NDEBUG */

	PERTASK_SET(this_exception_code, ERROR_CODEOF(E_OK));
	/* Handle the `E_INTERRUPT_USER_RPC' exception now. */
	if (error.ei_code == ERROR_CODEOF(E_INTERRUPT_USER_RPC)) {
		DBG_memset(&error, 0xcc, sizeof(error));
		error.ei_code = ERROR_CODEOF(E_OK);
	}

	ctx.rc_state = state;
	if (sc_info) {
		ctx.rc_context = RPC_REASONCTX_SYSCALL;
		ctx.rc_scinfo  = *sc_info;
	} else {
		ctx.rc_context = RPC_REASONCTX_INTERRUPT;
	}

	/* Load RPC functions */
	ATOMIC_AND(THIS_TASK->t_flags, ~TASK_FRPC);
	pending.slh_first = SLIST_ATOMIC_CLEAR(&PERTASK(this_rpcs));
	restore_plast = SLIST_PFIRST(&restore);
	SLIST_INIT(&kernel_rpcs);
handle_pending:
	for (;;) {
		struct pending_rpc *rpc;
		rpc = SLIST_FIRST(&pending);
		if (!rpc)
			break;
		SLIST_REMOVE_HEAD(&pending, pr_link);
		/* Here, kernel RPCs are executed _after_ user RPCs. */
		if (rpc->pr_flags & RPC_CONTEXT_KERN) {
			/* Check if this system call _must_ be handled during SYSRET. */
			if (rpc->pr_flags & RPC_SYNCMODE_F_SYSRET) {
				*restore_plast = rpc;
				restore_plast  = &rpc->pr_link.sle_next;
				rpc->pr_flags |= _RPC_CONTEXT_INACTIVE;
			} else {
				/* NOTE: This also inverts the order back to first-scheduled-first-run */
				SLIST_INSERT_HEAD(&kernel_rpcs, rpc, pr_link);
			}
		} else if (rpc->pr_flags & _RPC_CONTEXT_INACTIVE) {
			/* RPC was disabled in an earlier pass. */
			*restore_plast = rpc;
			restore_plast  = &rpc->pr_link.sle_next;
		} else {
			/* User-space RPC
			 * NOTE: These are executed in reverse  order, since each one  executed
			 *       will return to the context loaded by the one that was executed
			 *       before, meaning that the last one executed (iow: the first one
			 *       originally scheduled) will have the last word when it comes to
			 *       where execution should continue. */
			struct pending_user_rpc user_rpc_info;
			unsigned int user_rpc_reason;
			bool is_masked;
			TRY {
				is_masked = sigmask_ismasked(_RPC_GETSIGNO(rpc->pr_flags));
			} EXCEPT {
				/* Prioritize errors. */
				struct exception_info *tls = error_info();
				if (error_priority(error.ei_code) < error_priority(tls->ei_code))
					memcpy(&error, tls, sizeof(error));
				pending_user_rpc_fini(&rpc->pr_user);
				pending_rpc_free(rpc);
				continue;
			}
			if (is_masked) {
				/* User-space RPCs are currently masked. */
make_inactive:
				*restore_plast = rpc;
				restore_plast  = &rpc->pr_link.sle_next;
				rpc->pr_flags |= _RPC_CONTEXT_INACTIVE;
				continue;
			}
			/* Figure out the reason we want to tell user-space.
			 * NOTE: Yes: this checks for  the original `sc_info'  (and
			 *       not for `ctx.rc_context == RPC_REASONCTX_SYSCALL') */
			user_rpc_reason = _RPC_REASONCTX_SYNC;
			if (sc_info != NULL) {
				if ((rpc->pr_flags & RPC_SYNCMODE_F_REQUIRE_CP) &&
				    !kernel_syscall_iscp(sc_info->rsi_sysno))
					goto make_inactive;
				/* If the system call  */
				if (ctx.rc_context == RPC_REASONCTX_SYSCALL)
					user_rpc_reason = _RPC_REASONCTX_SYSCALL;
			} else {
				if ((rpc->pr_flags & RPC_SYNCMODE_F_REQUIRE_SC))
					goto make_inactive;
			}
			user_rpc_info = rpc->pr_user;
			pending_rpc_free(rpc);
			/* Execute the program associated with this RPC */
			TRY {
				ctx.rc_state = task_userrpc_runprogram(ctx.rc_state, &user_rpc_info,
				                                       user_rpc_reason, &ctx.rc_scinfo);
			} EXCEPT {
				/* Prioritize errors. */
				struct exception_info *tls = error_info();
				if (error_priority(error.ei_code) < error_priority(tls->ei_code))
					memcpy(&error, tls, sizeof(error));
			}
			/* User-space RPCs are _always_ required (or at least expected) to
			 * restart system calls, meaning that */
			ctx.rc_context = RPC_REASONCTX_SYSRET;
			pending_user_rpc_fini(&user_rpc_info);
		}
	}

	/* Service POSIX signals. */
	TRY {
		ctx.rc_state = sigmask_check_s(ctx.rc_state,
		                               ctx.rc_context == RPC_REASONCTX_SYSCALL
		                               ? &ctx.rc_scinfo
		                               : NULL);
	} EXCEPT {
		/* Prioritize errors. */
		struct exception_info *tls = error_info();
		if (tls->ei_code == ERROR_CODEOF(E_INTERRUPT_USER_RPC)) {
			/* Load additional RPCs, but discard this new exception */
			ATOMIC_AND(PERTASK(this_task.t_flags), ~TASK_FRPC);
			pending.slh_first = SLIST_ATOMIC_CLEAR(&PERTASK(this_rpcs));
			goto handle_pending;
		}
		if (error_priority(error.ei_code) < error_priority(tls->ei_code))
			memcpy(&error, tls, sizeof(error));
	}

	/* Kernel RPCs are handled before user-space RPCs. This is needed so that
	 * user-space RPCs have higher priority  when it executing code before  a
	 * system call can be  performed in a situation  where the system all  is
	 * implemented by a thread sending an RPC to itself (as is the  suggested
	 * method of gaining access of one's own register state) */
	while (!SLIST_EMPTY(&kernel_rpcs)) {
		struct pending_rpc *rpc;
		rpc = SLIST_FIRST(&kernel_rpcs);
		SLIST_REMOVE_HEAD(&kernel_rpcs, pr_link);
		assert(rpc->pr_flags & RPC_CONTEXT_KERN);
		assert(!(rpc->pr_flags & RPC_SYNCMODE_F_SYSRET));
		if (rpc->pr_flags & RPC_SYNCMODE_F_SYSRET) {
			*restore_plast = rpc;
			restore_plast  = &rpc->pr_link.sle_next;
			rpc->pr_flags |= _RPC_CONTEXT_INACTIVE;
		} else {
			prpc_exec_callback_t func;
			void *cookie;
			func   = rpc->pr_kern.k_func;
			cookie = rpc->pr_kern.k_cookie;
			pending_rpc_free(rpc);
			TRY {
				(*func)(&ctx, cookie);
			} EXCEPT {
				struct exception_info *tls = error_info();
				if (tls->ei_code == ERROR_CODEOF(E_INTERRUPT_USER_RPC)) {
					/* Load additional RPCs, but discard this new exception */
					ATOMIC_AND(PERTASK(this_task.t_flags), ~TASK_FRPC);
					pending.slh_first = SLIST_ATOMIC_CLEAR(&PERTASK(this_rpcs));
					goto handle_pending;
				}
				/* Prioritize errors. */
				if (error_priority(error.ei_code) < error_priority(tls->ei_code))
					memcpy(&error, tls, sizeof(error));
			}
			assert(ctx.rc_context == RPC_REASONCTX_SYSRET ||
			       ctx.rc_context == (sc_info ? RPC_REASONCTX_SYSCALL
			                                  : RPC_REASONCTX_INTERRUPT));
		}
	}

	/* Restore interrupts that could not be handled right now.
	 * In case we don't restart the interrupt/syscall, we must
	 * also handle SYSRET RPCs (as those must be invoked  just
	 * before  returning to user-space,  which is what's about
	 * to happen) */
	if (restore_plast != SLIST_PFIRST(&restore)) {
		*restore_plast = NULL; /* NULL-terminate list */
		if (error.ei_code != ERROR_CODEOF(E_OK) || ctx.rc_context == RPC_REASONCTX_SYSRET) {
			/* When  the system call won't be restarted, then we must still
			 * serve kernel RPCS with the `RPC_SYNCMODE_F_SYSRET' flag set. */
			struct pending_rpc **piter;
			assert(SLIST_EMPTY(&kernel_rpcs));
			piter = SLIST_PFIRST(&restore);
			for (;;) {
				struct pending_rpc *rpc;
				rpc = *piter;
				if (!rpc)
					break;
				/* Because we won't restart, we must also clear the
				 * INACTIVE flag for all  RPCs that we're about  to
				 * restore. */
				rpc->pr_flags &= ~_RPC_CONTEXT_INACTIVE;
				if (rpc->pr_flags & RPC_CONTEXT_KERN) {
					*piter = rpc->pr_link.sle_next; /* Remove from restore list. */
					/* Insert into the `kernel_rpcs' list */
					SLIST_INSERT(&kernel_rpcs, rpc, pr_link);
				} else {
					piter = &rpc->pr_link.sle_next;
				}
			}
			while (!SLIST_EMPTY(&kernel_rpcs)) {
				struct pending_rpc *rpc;
				prpc_exec_callback_t func;
				void *cookie;
				rpc = SLIST_FIRST(&kernel_rpcs);
				SLIST_REMOVE_HEAD(&kernel_rpcs, pr_link);
				assert(rpc->pr_flags & RPC_SYNCMODE_F_SYSRET);
				func   = rpc->pr_kern.k_func;
				cookie = rpc->pr_kern.k_cookie;
				pending_rpc_free(rpc);
				TRY {
					(*func)(&ctx, cookie);
				} EXCEPT {
					struct exception_info *tls = error_info();
					if (tls->ei_code == ERROR_CODEOF(E_INTERRUPT_USER_RPC)) {
						/* Load additional RPCs, but discard this new exception */
						ATOMIC_AND(PERTASK(this_task.t_flags), ~TASK_FRPC);
						pending.slh_first = SLIST_ATOMIC_CLEAR(&PERTASK(this_rpcs));
						goto handle_pending;
					}
					/* Prioritize errors. */
					if (error_priority(error.ei_code) < error_priority(tls->ei_code))
						memcpy(&error, tls, sizeof(error));
				}
				assert(ctx.rc_context == RPC_REASONCTX_SYSRET ||
				       ctx.rc_context == (sc_info ? RPC_REASONCTX_SYSCALL
				                                  : RPC_REASONCTX_INTERRUPT));
			}
		}
		if (!SLIST_EMPTY(&restore)) {
			restore_pending_rpcs(SLIST_FIRST(&restore));
			ATOMIC_OR(PERTASK(this_task.t_flags), TASK_FRPC);
		}
	}

	/* Check if we must throw a new exception. */
	if (error.ei_code != ERROR_CODEOF(E_OK)) {
		/* This will unwind into user-space! */
		ctx.rc_state = userexcept_unwind(ctx.rc_state, &error, sc_info);
		cpu_apply_icpustate(ctx.rc_state);
	}

	/* If the return context was  altered such that (logically  speaking),
	 * it points into async user-space  (iow: the interrupted system  call
	 * should not be restarted, or will be restored by user-space itself),
	 * then we mustn't try to restart  it ourselves, but rather load  back
	 * all RPCs that  are still pending  before resuming normal  execution
	 * in user-space. */
	if (ctx.rc_context == RPC_REASONCTX_SYSRET)
		cpu_apply_icpustate(ctx.rc_state);

	/* Must restart a previously aborted interrupt/syscall with all of
	 * the RPCs that can't be handled in the context of said interrupt
	 * or  syscall marked as  INACTIVE (thus preventing `task_serve()'
	 * from trying to unwind for them)
	 *
	 * Once the interrupt/syscall completes as normal, all of them will
	 * be re-enabled once again. */
	if (!SLIST_EMPTY(&restore)) {
		/* The following call causes `handle_sysret_rpc()' to be
		 * invoked before we'll eventually return to user-space. */
		assert(PREEMPTION_ENABLED());
		PREEMPTION_DISABLE();
		ctx.rc_state = userexcept_sysret_inject_with_state(ctx.rc_state);
		/* userexcept_sysret_inject(THIS_TASK); // Same as `userexcept_sysret_inject_with_state()' */
		PREEMPTION_ENABLE();
	}

	/* Restart the interrupt/syscall */
	return ctx.rc_state;
}




/* This is the function that is injected by `userexcept_sysret_inject()',
 * as well as related functions.
 *
 * The   implementation  of  this  function  serves  the  function
 * documented in <kos/rpc.md> under the name `handle_sysret_rpc()' */
PUBLIC ATTR_RETNONNULL WUNUSED NONNULL((1)) struct icpustate *
NOTHROW(FCALL userexcept_sysret)(struct icpustate *__restrict state) {
	struct pending_rpc_slist sysret_pending;
	struct pending_rpc_slist sysret_restore;
	struct pending_rpc **sysret_restore_plast;
	struct pending_rpc_slist sysret_kernel_rpcs;
	struct rpc_context sysret_ctx;
	struct exception_info sysret_error;
	/* Re-enable disabled RPCs and serve kernel RPCs with `RPC_REASONCTX_SYSRET' */
	sysret_ctx.rc_state      = state;
	sysret_ctx.rc_context    = RPC_REASONCTX_SYSRET;
	sysret_error.ei_code     = ERROR_CODEOF(E_OK);
	sysret_pending.slh_first = SLIST_ATOMIC_CLEAR(&PERTASK(this_rpcs));
	ATOMIC_AND(PERTASK(this_task.t_flags), ~TASK_FRPC);
	sysret_restore_plast = SLIST_PFIRST(&sysret_restore);
	SLIST_INIT(&sysret_kernel_rpcs);
sysret_handle_pending:
	for (;;) {
		struct pending_rpc *rpc;
		rpc = SLIST_FIRST(&sysret_pending);
		if (!rpc)
			break;
		SLIST_REMOVE_HEAD(&sysret_pending, pr_link);
		if (rpc->pr_flags & RPC_CONTEXT_KERN) {
			/* Here, kernel RPCs are executed _after_ user RPCs.
			 * NOTE: This also inverts the order back to first-scheduled-first-run */
			SLIST_INSERT_HEAD(&sysret_kernel_rpcs, rpc, pr_link);
		} else {
			rpc->pr_flags &= ~_RPC_CONTEXT_INACTIVE;
			if (!(rpc->pr_flags & RPC_SYNCMODE_F_ALLOW_ASYNC)) {
				*sysret_restore_plast = rpc;
				sysret_restore_plast  = &rpc->pr_link.sle_next;
			} else {
				/* User-space RPC */
				struct pending_user_rpc user_rpc_info;
				unsigned int user_rpc_reason;
				bool is_masked;
				TRY {
					is_masked = sigmask_ismasked(_RPC_GETSIGNO(rpc->pr_flags));
				} EXCEPT {
					/* Prioritize errors. */
					struct exception_info *tls = error_info();
					if (error_priority(sysret_error.ei_code) < error_priority(tls->ei_code))
						memcpy(&sysret_error, tls, sizeof(sysret_error));
					pending_user_rpc_fini(&rpc->pr_user);
					pending_rpc_free(rpc);
					continue;
				}
				if (is_masked) {
					/* User-space RPCs are currently masked. */
sysret_make_inactive:
					*sysret_restore_plast = rpc;
					sysret_restore_plast  = &rpc->pr_link.sle_next;
					continue;
				}
				/* Figure out the reason we want to tell user-space.
				 * NOTE: Yes: this checks for  the original `sc_info'  (and
				 *       not for `ctx.rc_context == RPC_REASONCTX_SYSCALL') */
				user_rpc_info = rpc->pr_user;
				pending_rpc_free(rpc);
				/* Execute the program associated with this RPC */
				TRY {
					sysret_ctx.rc_state = task_userrpc_runprogram(sysret_ctx.rc_state, &user_rpc_info,
					                                              _RPC_REASONCTX_ASYNC, NULL);
				} EXCEPT {
					/* Prioritize errors. */
					struct exception_info *tls = error_info();
					if (error_priority(sysret_error.ei_code) < error_priority(tls->ei_code))
						memcpy(&sysret_error, tls, sizeof(sysret_error));
				}
				pending_user_rpc_fini(&user_rpc_info);
			}
		}
	}

	/* Service POSIX signals. */
	TRY {
		sysret_ctx.rc_state = sigmask_check_s(sysret_ctx.rc_state, NULL);
	} EXCEPT {
		/* Prioritize errors. */
		struct exception_info *tls = error_info();
		if (tls->ei_code == ERROR_CODEOF(E_INTERRUPT_USER_RPC)) {
			/* Load additional RPCs, but discard this new exception */
			ATOMIC_AND(PERTASK(this_task.t_flags), ~TASK_FRPC);
			sysret_pending.slh_first = SLIST_ATOMIC_CLEAR(&PERTASK(this_rpcs));
			goto sysret_handle_pending;
		}
		if (error_priority(sysret_error.ei_code) < error_priority(tls->ei_code))
			memcpy(&sysret_error, tls, sizeof(sysret_error));
	}

	/* Invoke kernel RPC handlers */
	while (!SLIST_EMPTY(&sysret_kernel_rpcs)) {
		struct pending_rpc *rpc;
		rpc = SLIST_FIRST(&sysret_kernel_rpcs);
		SLIST_REMOVE_HEAD(&sysret_kernel_rpcs, pr_link);
		TRY {
			prpc_exec_callback_t func;
			void *cookie;
			func   = rpc->pr_kern.k_func;
			cookie = rpc->pr_kern.k_cookie;
			pending_rpc_free(rpc);
			(*func)(&sysret_ctx, cookie);
			assert(sysret_ctx.rc_context == RPC_REASONCTX_SYSRET);
		} EXCEPT {
			struct exception_info *tls = error_info();
			if (tls->ei_code == ERROR_CODEOF(E_INTERRUPT_USER_RPC)) {
				/* Load additional RPCs, but discard this new exception */
				ATOMIC_AND(PERTASK(this_task.t_flags), ~TASK_FRPC);
				sysret_pending.slh_first = SLIST_ATOMIC_CLEAR(&PERTASK(this_rpcs));
				goto sysret_handle_pending;
			}
			/* Prioritize errors. */
			if (error_priority(sysret_error.ei_code) < error_priority(tls->ei_code))
				memcpy(&sysret_error, tls, sizeof(sysret_error));
		}
	}

	/* If there are any RPCs that could not be handled, restore them now! */
	if (sysret_restore_plast != SLIST_PFIRST(&sysret_restore)) {
		*sysret_restore_plast = NULL;
		restore_pending_rpcs(SLIST_FIRST(&sysret_restore));
		ATOMIC_OR(PERTASK(this_task.t_flags), TASK_FRPC);
	}

	/* Check if we must throw a new exception. */
	if (sysret_error.ei_code != ERROR_CODEOF(E_OK)) {
		/* This will unwind into user-space! */
		sysret_ctx.rc_state = userexcept_unwind(sysret_ctx.rc_state, &sysret_error, NULL);
	}

	/* Resume normal execution. */
	return sysret_ctx.rc_state;
}




#ifdef CONFIG_NO_SMP
#define mycpu (&bootcpu)
#else /* CONFIG_NO_SMP */
#undef IPI_USEREXCEPT_SYSRET_INJECT_SAFE_ALLOW_QUANTUM_HEIST
#if 0 /* Allow `userexcept_sysret_inject_safe()' to "heist" the quantum of unrelated threads */
#define IPI_USEREXCEPT_SYSRET_INJECT_SAFE_ALLOW_QUANTUM_HEIST 1
#endif

PRIVATE NOBLOCK struct icpustate *
NOTHROW(FCALL ipi_userexcept_sysret_inject_safe)(struct icpustate *__restrict state,
                                                 void *args[CPU_IPI_ARGCOUNT]) {
	REF struct task *target;
	struct cpu *mycpu, *target_cpu;
	struct task *caller;
	target = (REF struct task *)args[0];
	/* Re-check that the target thread has yet to start terminating. */
	if unlikely(ATOMIC_READ(target->t_flags) & (TASK_FTERMINATING | TASK_FTERMINATED)) {
		decref(target);
		return state;
	}
	caller     = THIS_TASK;
	mycpu      = caller->t_cpu;
	target_cpu = ATOMIC_READ(target->t_cpu);
	if unlikely(target_cpu != mycpu) {
		/* Re-deliver the IPI to yet another CPU (letting it bounce until we get it right) */
		while (!cpu_sendipi(target_cpu,
		                    &ipi_userexcept_sysret_inject_safe,
		                    args, /* inherit:reference:target */
		                    CPU_IPI_FWAKEUP))
			task_pause();
		return state;
	}
	userexcept_sysret_inject(target);
	if (caller != target) {
		struct task *next_thread;
#ifdef IPI_USEREXCEPT_SYSRET_INJECT_SAFE_ALLOW_QUANTUM_HEIST
		next_thread = sched_intern_localwake(mycpu, caller, target,
		                                     ((syscall_ulong_t)(uintptr_t)args[1] & RPC_PRIORITY_F_HIGH) != 0);
#else /* IPI_USEREXCEPT_SYSRET_INJECT_SAFE_ALLOW_QUANTUM_HEIST */
		next_thread = sched_intern_localwake(mycpu, caller, target, false);
#endif /* !IPI_USEREXCEPT_SYSRET_INJECT_SAFE_ALLOW_QUANTUM_HEIST */
		if (next_thread != caller) {
			FORCPU(mycpu, thiscpu_sched_current) = next_thread;
			decref_unlikely(target);
			return CPU_IPI_MODE_SWITCH_TASKS;
		}
	}
	decref_unlikely(target);
	return state;
}
#endif /* !CONFIG_NO_SMP */


/* High-level wrapper for `userexcept_sysret_inject()' that makes all of
 * the right decisions to only ever call `userexcept_sysret_inject()' in
 * a valid context: using IPIs to make the call from the same CPU as the
 * one  currently hosting `thread', and ensuring that the thread has yet
 * to terminate.
 * Additionally, this function will make a call to `task_wake()'  once
 * the injection has completed, meaning that `thread' will wake up and
 * either immediatly  start executing  `userexcept_sysret()', or  will
 * handle a sporadic interrupt via a call to `task_serve()'.
 *
 * Note that the  actual injection may  complete asynchronously when  an
 * IPI  is used. Because of this, there is no way to check if the inject
 * was actually successful, or might have failed due to `thread' exiting
 * before the inject could be made.
 *
 * This function is used by `task_rpc_schedule()' (s.a. <kos/rpc.md>)
 *
 * @param: rpc_flags: Set of `0 | RPC_PRIORITY_F_HIGH', or one of
 *                    `RPC_PRIORITY_NORMAL',  `RPC_PRIORITY_HIGH'
 *                    Other flags are silently ignored. */
PUBLIC WUNUSED NONNULL((1)) void
NOTHROW(FCALL userexcept_sysret_inject_safe)(struct task *__restrict thread,
                                             syscall_ulong_t rpc_flags) {
	pflag_t was;
#ifndef CONFIG_NO_SMP
	struct cpu *mycpu;
	struct cpu *target_cpu;
	was        = PREEMPTION_PUSHOFF();
	mycpu      = THIS_CPU;
	target_cpu = ATOMIC_READ(thread->t_cpu);
	if (mycpu != target_cpu) {
		void *args[CPU_IPI_ARGCOUNT];
		args[0] = (void *)incref(thread);
#ifdef IPI_USEREXCEPT_SYSRET_INJECT_SAFE_ALLOW_QUANTUM_HEIST
		args[1] = (void *)rpc_flags;
#endif /* IPI_USEREXCEPT_SYSRET_INJECT_SAFE_ALLOW_QUANTUM_HEIST */
		while (!cpu_sendipi(target_cpu, &ipi_userexcept_sysret_inject_safe,
		                    args, CPU_IPI_FWAKEUP))
			task_pause();
		PREEMPTION_POP(was);
	} else
#endif /* !CONFIG_NO_SMP */
	{
		struct task *caller = THIS_TASK;
#ifdef CONFIG_NO_SMP
		was = PREEMPTION_PUSHOFF();
#endif /* CONFIG_NO_SMP */
		/* check if the thread has already terminated */
		if (thread->t_flags & (TASK_FTERMINATING | TASK_FTERMINATED)) {
			PREEMPTION_POP(was);
			return;
		}
		userexcept_sysret_inject(thread);
		if (caller != thread) {
			thread = sched_intern_localwake(mycpu, caller, thread,
			                                (rpc_flags & RPC_PRIORITY_F_HIGH) != 0 &&
			                                PREEMPTION_WASENABLED(was));
			if (thread != caller) {
				/* Immediately switch to the next thread thread. */
				FORCPU(mycpu, thiscpu_sched_current) = thread;
				cpu_run_current_and_remember_nopr(caller);
			}
		}
		PREEMPTION_POP(was);
	}
}

















/************************************************************************/
/* Kernel/C++ exception integration                                     */
/************************************************************************/

PRIVATE NONNULL((1)) unsigned int
NOTHROW(FCALL unwind_landingpad)(unwind_fde_t *__restrict fde, /* Only non-const for lazy initialized fields! */
                                 struct kcpustate *__restrict state,
                                 void const *except_pc) {
	void const *landing_pad_pc;
	unwind_cfa_landing_state_t cfa;
	struct kcpustate new_state;
	unsigned int unwind_error;
	landing_pad_pc = kcpustate_getpc(state);
	unwind_error   = unwind_fde_landing_exec(fde, &cfa, except_pc, landing_pad_pc);
	if unlikely(unwind_error != UNWIND_SUCCESS)
		goto done;
	/* Apply landing-pad transformations. */
	memcpy(&new_state, state, sizeof(new_state));
	unwind_error = unwind_cfa_landing_apply(&cfa, fde, except_pc,
	                                        &unwind_getreg_kcpustate, state,
	                                        &unwind_setreg_kcpustate, &new_state);
	if unlikely(unwind_error != UNWIND_SUCCESS)
		goto done;
	/* Write-back the new register state. */
	memcpy(state, &new_state, sizeof(new_state));
	return UNWIND_SUCCESS;
done:
	if (unwind_error == UNWIND_NO_FRAME) {
		/* Directly jump to the landing pad. */
		kcpustate_setpc(state, landing_pad_pc);
		unwind_error = UNWIND_SUCCESS;
	}
	return unwind_error;
}


INTDEF ATTR_COLD NONNULL((2)) void FCALL /* TODO: Standardize this function! (currently arch-specific) */
halt_unhandled_exception(unsigned int unwind_error,
                         struct kcpustate *__restrict unwind_state);

DEFINE_PUBLIC_ALIAS(error_unwind, libc_error_unwind);
INTERN NONNULL((1)) struct kcpustate *
NOTHROW(FCALL libc_error_unwind)(struct kcpustate *__restrict state) {
	unsigned int error;
	unwind_fde_t fde;
	struct kcpustate old_state;
	void const *pc;
	assertf(PERTASK_GET(this_exception_info.ei_code) != ERROR_CODEOF(E_OK) ||
	        PERTASK_GET(this_exception_info.ei_nesting) != 0,
	        "In error_unwind(), but no exception set");

search_fde:
	/* unwind `state' until the nearest exception handler, or until user-space is reached.
	 * If the  later  happens,  then  we  must propagate  the  exception  to  it  instead.
	 * NOTE: -1 because the state we're being given has its PC pointer
	 *       set  to  be  directed  after  the  faulting  instruction. */
	memcpy(&old_state, state, sizeof(old_state));
	pc    = kcpustate_getpc(&old_state) - 1;
	error = unwind_fde_find(pc, &fde);
	if unlikely(error != UNWIND_SUCCESS)
		goto err;
	/* Check if there is a personality function for us to execute. */
	if (fde.f_persofun) {
		unsigned int perso_code;
		perso_code = (*(dwarf_perso_t)fde.f_persofun)(&fde, state, fde.f_lsdaaddr);
		switch (perso_code) {

		case DWARF_PERSO_EXECUTE_HANDLER:
			/* When unwinding a landing pad, we must check if there is an active
			 * `DW_CFA_GNU_args_size' instruction.
			 * If there is, we must add its value to ESP before resuming execution!
			 * s.a.: https://reviews.llvm.org/D38680 */
			error = unwind_landingpad(&fde, state, pc);
			if unlikely(error != UNWIND_SUCCESS)
				goto err;
			ATTR_FALLTHROUGH
		case DWARF_PERSO_EXECUTE_HANDLER_NOW:
			return state; /* Execute a new handler. */

		case DWARF_PERSO_ABORT_SEARCH:
			error = UNWIND_SUCCESS;
			goto err;

		default: break;
		}
	}
#ifndef CFI_UNWIND_NO_SIGFRAME_COMMON_UNCOMMON_REGISTERS
	if (fde.f_sigframe) {
		unwind_cfa_sigframe_state_t cfa;
		error = unwind_fde_sigframe_exec(&fde, &cfa, pc);
		if unlikely(error != UNWIND_SUCCESS)
			goto err;
		error = unwind_cfa_sigframe_apply(&cfa, &fde, pc,
		                                  &unwind_getreg_kcpustate, &old_state,
		                                  &unwind_setreg_kcpustate, state);
	} else
#endif /* !CFI_UNWIND_NO_SIGFRAME_COMMON_UNCOMMON_REGISTERS */
	{
		unwind_cfa_state_t cfa;
		error = unwind_fde_exec(&fde, &cfa, pc);
		if unlikely(error != UNWIND_SUCCESS)
			goto err;
		error = unwind_cfa_apply(&cfa, &fde, pc,
		                         &unwind_getreg_kcpustate, &old_state,
		                         &unwind_setreg_kcpustate, state);
	}

	/* When unwinding to user-space, well get an error `UNWIND_INVALID_REGISTER' */
	if (error == UNWIND_INVALID_REGISTER) {
		struct ucpustate ustate;
		unwind_cfa_sigframe_state_t sigframe_cfa;
		kcpustate_to_ucpustate(&old_state, &ustate);
		/* Assume that we're unwinding a signal frame when returning to user-space. */
		error = unwind_fde_sigframe_exec(&fde, &sigframe_cfa, pc);
		if unlikely(error != UNWIND_SUCCESS)
			goto err_old_state;
		error = unwind_cfa_sigframe_apply(&sigframe_cfa, &fde, pc,
		                                  &unwind_getreg_kcpustate, &old_state,
		                                  &unwind_setreg_ucpustate, &ustate);
		if unlikely(error != UNWIND_SUCCESS)
			goto err_old_state;
		if (ucpustate_isuser(&ustate)) {
			/* At this point, we've got an exception that should be unwound
			 * into user-space, with the  user-space context at the  unwind
			 * location within user-space.
			 *
			 * We do this by making  a call to `userexcept_handler()',  but
			 * will return back to user-space, even when that function says
			 * that we should restart the current interrupt. This has to be
			 * done this way because we have no way of doing such a restart
			 *
			 * However, in most situations (such as #PF), the interrupt  is
			 * just restarted automatically the next time the fault happens */
			userexcept_handler_ucpustate(&ustate, NULL);
			__builtin_unreachable();
		}

		/* Safety checks for x86. These don't add anything semantically, but will
		 * catch stack corruptions bugs and  report on them before they'll  cause
		 * the kernel to panic. */

#if defined(__i386__) || defined(__x86_64__)
		/* CFI  instrumentation within `x86_userexcept_sysret' should have picked
		 * up on the custom return unwind info from `this_x86_sysret_iret', which
		 * should _always_ point into user-space, in which case the above call to
		 * `ucpustate_isuser()' should have returned `true'.
		 *
		 * Iow: getting here in the context of sysret is a bug! */
		assert(ucpustate_getpc(&ustate) != (void const *)&x86_userexcept_sysret);
		{
			u16 expected_gs = __rdgs();
			u16 expected_fs = __rdfs();
			u16 expected_es = __rdes();
			u16 expected_ds = __rdds();
			if unlikely(!SEGMENT_IS_VALID_KERNCODE(ustate.ucs_cs) ||
			            !SEGMENT_IS_VALID_KERNDATA(ustate.ucs_ss) ||
			            ustate.ucs_sgregs.sg_gs != expected_gs ||
			            ustate.ucs_sgregs.sg_fs != expected_fs ||
			            ustate.ucs_sgregs.sg_es != expected_es ||
			            ustate.ucs_sgregs.sg_ds != expected_ds) {
#define LOG_SEGMENT_INCONSISTENCY(name, isval, wantval)                                                        \
				do {                                                                                           \
					if (isval != wantval) {                                                                    \
						printk(KERN_CRIT "[except] Inconsistent unwind %%%cs: %#" PRIx16 " != %#" PRIx16 "\n", \
						       name, isval, wantval);                                                          \
					}                                                                                          \
				} __WHILE0
#define LOG_SEGMENT_INCONSISTENCY_CHK(name, isval, isok)                                       \
				do {                                                                           \
					if (!isok(isval)) {                                                        \
						printk(KERN_CRIT "[except] Inconsistent unwind %%%cs: %#" PRIx16 "\n", \
						       name, isval);                                                   \
					}                                                                          \
				} __WHILE0
				/* NOTE: Some x86 processors behave kind-of weird:
				 * [warn  ] [except] Inconsistent unwind %cs: 0x80000008 != 0x8
				 * [warn  ] [except] Inconsistent unwind %fs: 0xeafe0040 != 0x40
				 * [warn  ] [except] Inconsistent unwind %es: 0x10000023 != 0x23
				 * -> Testing indicates that bochs implements (and is allowed to implement) `pushl %ds' as:
				 * >> ESP -= 4;
				 * >> *(u16 *)ESP = DS;
				 * In other words, it leaves the upper 2 bytes of the pushed DWORD
				 * undefined (or  rather: have  them keep  their previous  values)
				 * -> To fix this, libunwind  (and also some other  components
				 *    that use segment registers) have been adjusted, in order
				 *    to  both ignore the upper 2 bytes during reads, and fill
				 *    them as all zeroes during writes.
				 * Intel manuals:
				 * ... if the operand size is 32-bits, either a zero-extended value is
				 * pushed on the stack or the segment selector is written on the stack
				 * using a 16-bit move.  For the last case,  all recent Core and  Atom
				 * processors  perform a 16-bit move, leaving the upper portion of the
				 * stack location unmodified. ...
				 * -> In  other words: Bochs  is entirely correct  in its emulation, and
				 *    I'm a fault here, in which case. Honestly: Thank you Bochs. That's
				 *    one less Problem for  me to figure out  the hard way once  testing
				 *    on real Hardware is going to start...
				 */
				LOG_SEGMENT_INCONSISTENCY_CHK('c', ustate.ucs_cs, SEGMENT_IS_VALID_KERNCODE);
				LOG_SEGMENT_INCONSISTENCY_CHK('s', ustate.ucs_ss, SEGMENT_IS_VALID_KERNDATA);
				LOG_SEGMENT_INCONSISTENCY('g', ustate.ucs_sgregs.sg_gs, expected_gs);
				LOG_SEGMENT_INCONSISTENCY('f', ustate.ucs_sgregs.sg_fs, expected_fs);
				LOG_SEGMENT_INCONSISTENCY('e', ustate.ucs_sgregs.sg_es, expected_es);
				LOG_SEGMENT_INCONSISTENCY('d', ustate.ucs_sgregs.sg_ds, expected_ds);
#undef LOG_SEGMENT_INCONSISTENCY
				error = UNWIND_INVALID_REGISTER;
				goto err_old_state;
			}
		}
#endif /* __i386__ || __x86_64__ */

		ucpustate_to_kcpustate(&ustate, state);
	} else {
		if unlikely(error != UNWIND_SUCCESS)
			goto err_old_state;
	}

#if EXCEPT_BACKTRACE_SIZE != 0
	/* Remember the current state PC as a new entry in the exception's traceback. */
	if (PERTASK_GET(this_exception_trace[EXCEPT_BACKTRACE_SIZE - 1]) == NULL) {
#if EXCEPT_BACKTRACE_SIZE > 1
		unsigned int i;
		for (i = 0; i < EXCEPT_BACKTRACE_SIZE - 1; ++i) {
			if (!PERTASK_GET(this_exception_trace[i]))
				break;
		}
		PERTASK_SET(this_exception_trace[i], kcpustate_getpc(state));
#else /* EXCEPT_BACKTRACE_SIZE > 1 */
		PERTASK_SET(this_exception_trace[0], kcpustate_getpc(state));
#endif /* EXCEPT_BACKTRACE_SIZE <= 1 */
	}
#endif /* EXCEPT_BACKTRACE_SIZE != 0 */

	/* Continue searching for handlers. */
	goto search_fde;
err_old_state:
	memcpy(state, &old_state, sizeof(*state));
err:
	halt_unhandled_exception(error, state);
	return state;
}





/* This  function  is hooked  by CFI  under `struct unwind_fde_struct::f_persofun'
 * It's exact prototype and behavior are therefor not mandated by how GCC uses it. */
DEFINE_PUBLIC_ALIAS(__gcc_personality_v0, __gxx_personality_v0);
PUBLIC NONNULL((1, 2, 3)) unsigned int
NOTHROW(KCALL __gxx_personality_v0)(struct unwind_fde_struct *__restrict fde,
                                    struct kcpustate *__restrict state,
                                    byte_t const *__restrict reader) {
	u8 temp, callsite_encoding;
	byte_t const *landingpad;
	byte_t const *callsite_end;
	size_t callsite_size;

	landingpad = (byte_t const *)fde->f_pcstart;

	/* NOTE: `reader' points to a `struct gcc_lsda' */
	temp = *reader++; /* gl_landing_enc */
	if (temp != DW_EH_PE_omit) {
		/* gl_landing_pad */
		landingpad = dwarf_decode_pointer((byte_t const **)&reader, temp,
		                                  sizeof(void *), &fde->f_bases);
	}
	temp = *reader++; /* gl_typetab_enc */
	if (temp != DW_EH_PE_omit) {
		dwarf_decode_uleb128((byte_t const **)&reader); /* gl_typetab_off */
	}
	callsite_encoding = *reader++; /* gl_callsite_enc */
	callsite_size     = dwarf_decode_uleb128((byte_t const **)&reader);
	callsite_end      = reader + callsite_size;
	while (reader < callsite_end) {
		uintptr_t start, size, handler, action;
		byte_t const *startpc, *endpc;
		start   = (uintptr_t)dwarf_decode_pointer((byte_t const **)&reader, callsite_encoding, sizeof(void *), &fde->f_bases); /* gcs_start */
		size    = (uintptr_t)dwarf_decode_pointer((byte_t const **)&reader, callsite_encoding, sizeof(void *), &fde->f_bases); /* gcs_size */
		handler = (uintptr_t)dwarf_decode_pointer((byte_t const **)&reader, callsite_encoding, sizeof(void *), &fde->f_bases); /* gcs_handler */
		action  = (uintptr_t)dwarf_decode_pointer((byte_t const **)&reader, callsite_encoding, sizeof(void *), &fde->f_bases); /* gcs_action */
		startpc = landingpad + start;
		endpc   = startpc + size;

#if 1 /* Compare pointers like this, as `kcs_eip' is the _RETURN_ address \
       * (i.e. the address after the piece of code that caused the exception) */
		if (kcpustate_getpc(state) > startpc && kcpustate_getpc(state) <= endpc)
#else
		if (kcpustate_getpc(state) >= startpc && kcpustate_getpc(state) < endpc)
#endif
		{
			if (handler == 0)
				return DWARF_PERSO_CONTINUE_UNWIND; /* No handler -> exception should be propagated. */
			/* Just to the associated handler */
			kcpustate_setpc(state, landingpad + handler);
			if (action != 0) {
				/* The ABI wants  us to fill  %eax with  a pointer to  the exception  (`_Unwind_Exception').
				 * However,  since  KOS exception  is kept  a bit  simpler  (so-as to  allow it  to function
				 * without  the need of dynamic memory allocation),  the current exception isn't an internal
				 * implementation detail of the runtime, but rather stored in an exposed, per-task variable.
				 * So while what we  write here really doesn't  matter at all, let's  just put in  something
				 * that at the very least makes a bit of sense. */
				kcpustate_set_unwind_exception(state, error_code());
			}
			return DWARF_PERSO_EXECUTE_HANDLER;
		}
	}
	/* Default behavior: abort exception handling (this function was marked as NOTHROW) */
	return DWARF_PERSO_ABORT_SEARCH;
}



DECL_END
#endif /* CONFIG_USE_NEW_RPC */

#endif /* !GUARD_KERNEL_SRC_MISC_EXCEPT_HANDLER_C */
