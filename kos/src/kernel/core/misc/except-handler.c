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
#ifndef GUARD_KERNEL_SRC_MISC_EXCEPT_HANDLER_C
#define GUARD_KERNEL_SRC_MISC_EXCEPT_HANDLER_C 1
#define _KOS_SOURCE 1

/* High-level exception handlers for translating exceptions thrown through
 * system calls or interrupts that  point to user-space return  locations.
 *
 * This also facilitates the handling of RPCs! */

#include <kernel/compiler.h>

#include <kernel/coredump.h>
#include <kernel/except.h>
#include <kernel/printk.h>
#include <kernel/rt/except-handler.h>
#include <kernel/rt/except-personality.h>
#include <kernel/syscall-properties.h>
#include <kernel/types.h>
#include <sched/arch/task.h>
#include <sched/cpu.h>
#include <sched/cred.h>
#include <sched/enum.h>
#include <sched/group.h>
#include <sched/rpc-internal.h>
#include <sched/rpc.h>
#include <sched/scheduler.h>
#include <sched/sigaction.h>
#include <sched/sigmask.h>
#include <sched/task.h>

#include <hybrid/sched/preemption.h>

#include <asm/intrin.h>
#include <kos/bits/except-register-state-helpers.h>
#include <kos/bits/except-register-state.h>
#include <kos/bits/except.h>
#include <kos/except.h>
#include <sys/wait.h>

#include <assert.h>
#include <atomic.h>
#include <inttypes.h>
#include <signal.h>
#include <stddef.h>
#include <string.h>

#include <libcpustate/apply.h>
#include <libunwind/cfi.h>
#include <libunwind/dwarf.h>
#include <libunwind/eh_frame.h>
#include <libunwind/errno.h>
#include <libunwind/register.h>
#include <libunwind/unwind.h>

DECL_BEGIN

#if !defined(NDEBUG) && !defined(NDEBUG_FINI)
#define DBG_memset(p, c, n) memset(p, c, n)
#else /* !NDEBUG && !NDEBUG_FINI */
#define DBG_memset(p, c, n) (void)0
#endif /* NDEBUG || NDEBUG_FINI */

INTERN NOBLOCK void
NOTHROW(FCALL restore_pending_rpcs)(struct pending_rpc *restore) {
	if (restore) {
		struct pending_rpc_slist *list;
		struct pending_rpc *last;
		list = &PERTASK(this_rpcs);
again:
		last = atomic_read(&list->slh_first);
		if (!last) {
			if (!atomic_cmpxch_weak(&list->slh_first, NULL, restore))
				goto again;
		} else {
			while (SLIST_NEXT(last, pr_link))
				last = SLIST_NEXT(last, pr_link);
			last->pr_link.sle_next = restore;
		}
	}
}




PRIVATE ABNORMAL_RETURN ATTR_NORETURN NONNULL((1)) void
NOTHROW(FCALL process_exit_for_exception_after_coredump)(struct exception_data const *__restrict error) {
	siginfo_t si;
	/* Try to translate the current exception  into a signal, so that  we
	 * can use that signal code as reason for why the process has exited. */
	if (!except_as_signal(error, &si))
		si.si_signo = SIGILL;
	process_exit(W_EXITCODE(1, si.si_signo) | WCOREFLAG);
}


PRIVATE WUNUSED NONNULL((1)) struct icpustate *FCALL
process_waitfor_SIG_CONT(struct icpustate *__restrict state, int status) {
	(void)state;
	(void)status;

	/* TODO: Allocate a SIG_CONT synchronization controller (a ref-counted
	 *       structure that will be shared  with all other threads  within
	 *       the current process)
	 * This structure primarily contains a `struct sig' and a condition flag
	 * that  will be set and broadcast resp. once execution should continue. */

	/* TODO: Send an RPC to the main thread of the current process, unless
	 *       the  caller already is  that thread. If an  RPC got send, the
	 *       current thread will already begin the act of sleeping.
	 * The main thread is always used so that no race conditions can happen
	 * relating to figuring out which thread is supposed to control a proc-
	 * wide stop state. (It's always the main thread) */

	/* TODO: Within the main thread, send additional RPCs to all other threads
	 *       apart of the process (except  for the original thread which  send
	 *       the stop-RPC to  the main  thread, unless  no such  RPC was  send
	 *       because the main thread _was_ that other thread) */

	/* TODO: All threads except for the main thread will perform a custom wait
	 *       operation that doesn't  serve non-kernel RPCs,  and discards  all
	 *       non-RTL exceptions thrown by kernel RPCs. All user-level RPCs are
	 *       added to a  pending-list, but are  scanned for posix-signal  RPCs
	 *       that  may translate to  SIG_CONT. If one is  found, that RPC will
	 *       be forwarded to the process's main thread.
	 * The following special actions are performed for certain signal action:
	 *   - SIG_TERM: Terminate the entire process
	 *   - SIG_EXIT: Terminate only the thread the signal was directed to.
	 *                      When send to the main thread, same as SIG_TERM
	 *   - SIG_CONT: Forwarded to the main thread to resume normal execution
	 *   - SIG_CORE: Normal behavior
	 *   - SIG_STOP: Ignore & discard (we're already stopped)
	 *   - SIG_IGN:  Ignore & discard
	 */

	/* TODO: The main thread keeps on polling the list of per-process RPCs, as
	 *       well  as its own  per-thread RPCs, both of  which are handled the
	 *       same as other threads handle their own per-thread RPCs, only that
	 *       user-RPCs are enqueued in 2  separate lists (one for those  meant
	 *       for random-thread execution, and one for those meant for the main
	 *       thread itself)
	 *
	 * Posix signal RPCs  send any of  the worker threads,  or the main  thread,
	 * or  the process as a whole are  scanned for signals with special actions.
	 * For this purpose, each thread uses its own private set of signal handlers
	 * for determining which special actions are associated with thread-directed
	 * signals.
	 * Signals directed to the process as a whole are handled by the main thread
	 * and compared against a pseudo-super-set of signal actions shared by _all_
	 * threads, where signal actions outweigh each other as follows:
	 *    - if _ANY_ thread assigns `SIG_CORE' as action, that action wins; else:
	 *    - if _ANY_ thread assigns `SIG_TERM' as action, that action wins; else:
	 *    - if _ANY_ thread assigns `SIG_CONT' as action, that action wins; else:
	 *    - if _ANY_ thread assigns `SIG_STOP' or `SIG_IGN' as action, `SIG_IGN' wins; else:
	 *    - if _ANY_ thread assigns `SIG_EXIT' as action, `SIG_TERM' wins
	 * Note that this handles _all_ of the special signal actions there are. */

	/* FIXME: The above model has a race condition where SIG_CONT that are send
	 *        while the main thread  has yet to stop  all of the other  threads
	 *        will be lost and ignored, even  when send after the initial  STOP
	 *        signal! */

	return state;
}


PRIVATE ATTR_NOINLINE ATTR_NORETURN NONNULL((1)) void FCALL
abort_SIGINT_program_without_exception_handler(struct icpustate *__restrict state)
		THROWS(E_EXIT_PROCESS) {
	struct exception_info info;
	bzero(&info, sizeof(struct exception_info));
	info.ei_data.e_code      = EXCEPT_CODEOF(E_INTERRUPT);
	info.ei_data.e_faultaddr = icpustate_getpc(state);
	coredump_create_for_exception(state, &info, true);
	THROW(E_EXIT_PROCESS, W_EXITCODE(1, SIGINT) | WCOREFLAG);
}

/* Helper  wrapper  for `userexcept_callsignal()'  that  includes all  of  the logic
 * related to figuring out if a system call (if one is present) should be restarted,
 * or if the system call  should (seemingly) return with  -EINTR or by entering  the
 * user-space exception handler with an E_INTERRUPT exception.
 *
 * This function also implements handling of `SA_RESETHAND' */
PRIVATE WUNUSED ATTR_INOUT(1) ATTR_IN(2) ATTR_IN(3) ATTR_IN_OPT(4) struct icpustate *FCALL
userexcept_callsignal_and_maybe_restart_syscall(struct icpustate *__restrict state,
                                                struct kernel_sigaction const *__restrict action,
                                                siginfo_t const *__restrict siginfo,
                                                struct rpc_syscall_info const *sc_info)
		THROWS(E_SEGFAULT) {

	/* Figure out if the system call should be restarted. */
	if (sc_info != NULL) {
		bool should_restart;
		int syscall_restart_mode = kernel_syscall_restartmode(sc_info);
		switch (syscall_restart_mode) {
		case SYSCALL_RESTART_MODE_MUST:
			should_restart = true;
			break;
		case SYSCALL_RESTART_MODE_DONT:
			should_restart = false;
			break;
		case SYSCALL_RESTART_MODE_AUTO:
			should_restart = (action->sa_flags & SA_RESTART) != 0;
			break;
		default: __builtin_unreachable();
		}

		if (!should_restart) {
			struct exception_data error;
			/* Make modifications to `state' that will make it look like the
			 * interrupted  system call returned  with `-EINTR', or returned
			 * to  user-space by calling the user-defined exception handler. */
			bzero(&error, sizeof(error));
			error.e_code      = EXCEPT_CODEOF(E_INTERRUPT);
			error.e_faultaddr = icpustate_getpc(state);
			if (sc_info->rsi_flags & RPC_SYSCALL_INFO_FEXCEPT) {
				/* Make transformations to invoke the user-space exception handler.
				 * When no handler is installed, `userexcept_callhandler()' returns
				 * `NULL'. */
				struct icpustate *newstate;
				newstate = userexcept_callhandler(state, sc_info, &error);
				if unlikely(!newstate) {
					/* If the exception still cannot be handled, terminate the program.
					 * XXX: Logically speaking, the program should only terminate once
					 *      the signal handler that would be invoked below returned... */
					abort_SIGINT_program_without_exception_handler(state);
					/*newstate = state;*/
				}
				state = newstate;
			} else {
				/* Simple case: Just have the syscall return `-EINTR' */
				state = userexcept_seterrno(state, sc_info, &error);
			}

			/* Set `sc_info' to `NULL' in order to prevent `userexcept_callsignal()'
			 * from generating transformations needed  to have the returning  signal
			 * handler repeat the system call. */
			sc_info = NULL;
		} else {
			/* Simply pass along `sc_info' to `userexcept_callsignal()',
			 * which  will generate the necessary transformations needed
			 * to restart the interrupted system call. */
		}
	}

	/* Implement support for `SA_RESETHAND' */
	if (action->sa_flags & SA_RESETHAND) {
		if unlikely(!sighand_reset_handler(siginfo->si_signo, action))
			return NULL;
	}

	return userexcept_callsignal(state, action, siginfo, sc_info);
}



/* Raise a posix signal in user-space for `siginfo' whilst performing
 * all of the  extended "builtin"  signal actions, as  may have  been
 * requested by the user.
 * Returns `NULL' if `error' could not be translated into a signal. */
PRIVATE ABNORMAL_RETURN WUNUSED NONNULL((1, 3)) struct icpustate *FCALL
userexcept_raisesignal_from_exception(struct icpustate *__restrict state,
                                      struct rpc_syscall_info const *sc_info,
                                      struct exception_info const *__restrict error)
		THROWS(E_SEGFAULT) {
	struct icpustate *result;
	struct kernel_sigaction action;
	siginfo_t siginfo;

	/* Try to translate the given `error' into a signal. */
	if (!except_as_signal(&error->ei_data, &siginfo))
		return NULL;

	/* Include missing information within the signal info. */
	if (siginfo.si_signo == SIGSYS)
		siginfo.si_call_addr = (void *)icpustate_getpc(state);

	/* Raise a POSIX signal */
again_gethand:
	assert(sigvalid(siginfo.si_signo));
	sighand_getaction(siginfo.si_signo, &action);

	/* Check for special signal handlers. */
	if (action.sa_handler == SIG_DFL)
		action.sa_handler = sighand_default_action(siginfo.si_signo);
	switch ((uintptr_t)(void *)action.sa_handler) {

	case __SIG_IGN:
	case __SIG_CONT:
		if (sc_info)
			state = userexcept_seterrno(state, sc_info, &error->ei_data);
		return state;

	case __SIG_CORE:
		/* If we've gotten here because of a system call, then we can assume that
		 * the exception does have a kernel-space side, and thus we must  include
		 * information about that exception's origin. */
		coredump_create_for_exception(state, error, sc_info != NULL);
		process_exit(W_EXITCODE(1, siginfo.si_signo) | WCOREFLAG);

	case __SIG_TERM:
		process_exit(W_EXITCODE(1, siginfo.si_signo));

	case __SIG_EXIT:
		task_exit(W_EXITCODE(1, siginfo.si_signo));

	case __SIG_STOP:
		state = process_waitfor_SIG_CONT(state, W_STOPCODE(siginfo.si_signo));
		return state;

	default: break;
	}

	/* Invoke a regular, old signal handler. */
	result = userexcept_callsignal_and_maybe_restart_syscall(state, &action, &siginfo, sc_info);
	if unlikely(!result)
		goto again_gethand;
	return result;
}

PRIVATE ABNORMAL_RETURN ATTR_NOINLINE ATTR_NORETURN NONNULL((1, 2)) void
NOTHROW(FCALL trigger_coredump_from__E_CORE_PROCESS)(struct icpustate *__restrict state,
                                                     struct exception_info *__restrict error) {
	siginfo_t si;
	bzero(&si, sizeof(si));
	si.si_signo = WSTOPSIG(error->ei_data.e_args.e_pointers[0]);
	si.si_errno = error->ei_data.e_args.e_pointers[1];
	si.si_code  = error->ei_data.e_args.e_pointers[2];
	coredump_create_for_signal(state, &si);
	process_exit(error->ei_data.e_args.e_pointers[0]);
}

/* Unwind a given exception info user-space, either as  an
 * exception, by returning a negative errno, or by raising
 * a posix signal.
 * This function returns the updated CPU state which should
 * be loaded by the caller. */
PRIVATE ABNORMAL_RETURN ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) struct icpustate *
NOTHROW(FCALL userexcept_unwind)(struct icpustate *__restrict state,
                                 struct exception_info *__restrict error,
                                 struct rpc_syscall_info const *sc_info) {
	struct icpustate *result;
again:

	/* Handle/amend special exception codes */
	switch (error->ei_code) {

	case EXCEPT_CODEOF(E_EXIT_PROCESS):
		process_exit((int)error->ei_data.e_args.e_exit_process.ep_exit_code);

	case EXCEPT_CODEOF(E_EXIT_THREAD):
		task_exit((int)error->ei_data.e_args.e_exit_thread.et_exit_code);

	case EXCEPT_CODEOF(_E_STOP_PROCESS):
		/* TODO: If/when we implement this properly, `userexcept_unwind()' must be
		 *       able  to return some  special value to  indicate that the current
		 *       system call/interrupt should be restarted. */
		return process_waitfor_SIG_CONT(state, error->ei_data.e_args.e_pointers[0]);

	case EXCEPT_CODEOF(_E_CORE_PROCESS):
		trigger_coredump_from__E_CORE_PROCESS(state, error);
		break;

#ifdef RPC_SYSCALL_INFO_METHOD_OTHER
	case EXCEPT_CODEOF(E_UNKNOWN_SYSTEMCALL): {
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
		struct exception_info *tls = except_info();
		if (except_priority(tls->ei_code) > except_priority(error->ei_code)) {
			memcpy(error, tls, sizeof(struct exception_info));
			assert(PREEMPTION_ENABLED());
			goto again;
		} else {
			except_printf("raising exception/signal");
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
	assert(PERTASK_EQ(this_exception_info.ei_code, EXCEPT_CODEOF(E_OK)));
	assert(PERTASK_EQ(this_exception_info.ei_flags, EXCEPT_FNORMAL));
	assert(PERTASK_EQ(this_exception_info.ei_nesting, 0));
	assert(PREEMPTION_ENABLED());
	return result;
}


/* Helper function for `userexcept_handler()' and `userexcept_sysret()'
 * @return: true:  RPC was handled.
 * @return: false: RPC cannot be handled right now; Load other RPCs and try again */
PRIVATE WUNUSED NONNULL((1, 2, 3)) bool
NOTHROW(FCALL userexcept_exec_user_rpc)(/*in|out*/ struct rpc_context *__restrict ctx,
                                        /*in|out*/ struct exception_info *__restrict error,
                                        /*inherit(always)*/ struct pending_rpc *__restrict rpc) {
	/* Execute the program associated with this RPC */
	if (rpc->pr_flags & RPC_CONTEXT_SIGNAL) {
		/* Because signals handled here must properly integrate with  other
		 * RPCs, as well as the current `error', we can't just make use  of
		 * `userexcept_raisesignal_from_exception()', but have to implement
		 * signal action handling ourselves.
		 *
		 * This is required for signal actions such as SIG_CORE, or
		 * SIG_STOP, which introduce  custom control routing  which
		 * could otherwise interfere with normal RPC handling. */
		struct kernel_sigaction action;
		assert(sigvalid(rpc->pr_psig.si_signo));
again_load_threadsig_action:
		sighand_getaction(rpc->pr_psig.si_signo, &action);

		/* Custom handlers. */
again_switch_action_handler:
		switch ((uintptr_t)action.sa_handler) {

		case __SIG_DFL:
			action.sa_handler = sighand_default_action(rpc->pr_psig.si_signo);
			goto again_switch_action_handler;

		case __SIG_IGN:
			/* Ignored */
			break;

		case __SIG_CONT:
			/* Undo the effects of `SIG_STOP' */
			if (error->ei_code == EXCEPT_CODEOF(_E_STOP_PROCESS))
				error->ei_code = EXCEPT_CODEOF(E_OK);
			break;

		case __SIG_TERM: {
			except_code_t code;
			code = EXCEPT_CODEOF(E_EXIT_PROCESS);
			__IF0 { case __SIG_EXIT: code = EXCEPT_CODEOF(E_EXIT_THREAD); }
			__IF0 { case __SIG_STOP: code = EXCEPT_CODEOF(_E_STOP_PROCESS); }
			__IF0 { case __SIG_CORE: code = EXCEPT_CODEOF(_E_CORE_PROCESS); }

			/* If applicable, override the active return-exception. */
			if (except_priority(error->ei_code) < except_priority(code)) {
				union wait reason;
				reason.w_status = W_EXITCODE(1, rpc->pr_psig.si_signo);
				bzero(error, sizeof(struct exception_info));
				error->ei_code = code;
				if (action.sa_handler == SIG_CORE) {
					error->ei_data.e_args.e_pointers[1] = rpc->pr_psig.si_errno;
					error->ei_data.e_args.e_pointers[2] = rpc->pr_psig.si_code;
					reason.w_status |= WCOREFLAG;
				} else if (action.sa_handler == SIG_STOP) {
					reason.w_status = W_STOPCODE(rpc->pr_psig.si_signo);
				}
				error->ei_data.e_args.e_pointers[0] = reason.w_status;
			}
		}	break;

		default:
			TRY {
				struct icpustate *newstate;

				/* "Normal" invoke-userspace-function signal action */
				newstate = userexcept_callsignal_and_maybe_restart_syscall(ctx->rc_state, &action, &rpc->pr_psig,
				                                                           ctx->rc_context == RPC_REASONCTX_SYSCALL
				                                                           ? &ctx->rc_scinfo
				                                                           : NULL);

				/* When  `userexcept_callsignal_and_maybe_restart_syscall()'  returns `NULL',
				 * a race condition is indicated where the user-defined signal action changed
				 * before the handler function could be invoked.
				 * This is important to ensure that `SA_RESETHAND' works atomically. */
				if (newstate == NULL)
					goto again_load_threadsig_action;
				ctx->rc_state = newstate;
			} EXCEPT {
				/* Prioritize errors. */
				struct exception_info *tls = except_info();
				if (tls->ei_code == EXCEPT_CODEOF(E_INTERRUPT_USER_RPC))
					return false; /* Load other RPCs and try again. */
				if (except_priority(error->ei_code) < except_priority(tls->ei_code)) {
					memcpy(error, tls, sizeof(struct exception_info));
					ctx->rc_context = RPC_REASONCTX_SYSRET; /* Will need to return to user-space to handle this exception */
				}
			}
			break;
		}
		assert(!(rpc->pr_flags & _RPC_CONTEXT_DONTFREE));
		pending_rpc_free(rpc);
	} else {
		struct icpustate *new_state;
		unsigned int user_rpc_reason;
		/* Figure out the reason we want to tell user-space. */
		assert(ctx->rc_context == RPC_REASONCTX_SYSRET ||
		       ctx->rc_context == RPC_REASONCTX_SYSCALL ||
		       ctx->rc_context == RPC_REASONCTX_INTERRUPT);
		switch (ctx->rc_context) {
		case RPC_REASONCTX_SYSRET:
			user_rpc_reason = _RPC_REASONCTX_ASYNC;
			break;
		case RPC_REASONCTX_INTERRUPT:
			user_rpc_reason = _RPC_REASONCTX_SYNC;
			break;
		case RPC_REASONCTX_SYSCALL: {
			int restart_mode;
			/* Figure out if we want the RPC program to restart the system call. */
			restart_mode    = kernel_syscall_restartmode(&ctx->rc_scinfo);
			user_rpc_reason = _RPC_REASONCTX_SYSCALL;
			switch (restart_mode) {
			case SYSCALL_RESTART_MODE_MUST:
				break;
			case SYSCALL_RESTART_MODE_DONT:
				user_rpc_reason = _RPC_REASONCTX_SYSINT;
				break;
			case SYSCALL_RESTART_MODE_AUTO:
				if (!(rpc->pr_flags & RPC_SYSRESTART_F_AUTO))
					user_rpc_reason = _RPC_REASONCTX_SYSINT;
				break;
			default: __builtin_unreachable();
			}
		}	break;
		default: __builtin_unreachable();
		}
		if (ctx->rc_context == RPC_REASONCTX_SYSCALL &&
		    user_rpc_reason != _RPC_REASONCTX_SYSCALL) {
			/* System call isn't being restarted; -> Must have it return with -EINTR,
			 * or by  calling the  user-defined exception  handler with  E_INTERRUPT. */
			struct exception_data error;
			bzero(&error, sizeof(error));
			error.e_code      = EXCEPT_CODEOF(E_INTERRUPT);
			error.e_faultaddr = icpustate_getpc(ctx->rc_state);
			if (ctx->rc_scinfo.rsi_flags & RPC_SYSCALL_INFO_FEXCEPT) {
				/* Make transformations to invoke the user-space exception handler.
				 * When no handler is installed, `userexcept_callhandler()' returns
				 * `NULL'. */
				struct icpustate *newstate;
				newstate = userexcept_callhandler(ctx->rc_state, &ctx->rc_scinfo, &error);
				if unlikely(!newstate) {
					/* If the exception still cannot be handled, terminate the program.
					 * XXX: Logically speaking, the program should only terminate
					 *      once  modifications made by the RPC program return... */
					abort_SIGINT_program_without_exception_handler(ctx->rc_state);
					/*newstate = ctx->rc_state;*/
				}
				ctx->rc_state = newstate;
			} else {
				/* Simple case: Just have the syscall return `-EINTR' */
				ctx->rc_state = userexcept_seterrno(ctx->rc_state, &ctx->rc_scinfo, &error);
			}
		}
		TRY {
			new_state = task_userrpc_runprogram(ctx->rc_state, rpc,
			                                    user_rpc_reason,
			                                    &ctx->rc_scinfo);
		} EXCEPT {
			/* Prioritize errors. */
			struct exception_info *tls = except_info();
			if (tls->ei_code == EXCEPT_CODEOF(E_INTERRUPT_USER_RPC))
				return false; /* Load other RPCs before trying to serve this one again. */
			if (except_priority(error->ei_code) < except_priority(tls->ei_code)) {
				memcpy(error, tls, sizeof(struct exception_info));
				ctx->rc_context = RPC_REASONCTX_SYSRET; /* Will need to return to user-space to handle this exception */
			}
			new_state = ctx->rc_state;
		}
		decref(&rpc->pr_user);

		/* When the RPC got canceled, then mustn't set SYSRET context
		 * as  no piece of  code got committed  which would have been
		 * able to restart the system call (meaning that as far as we
		 * are concerned, the system call  still has to be  restarted
		 * by means of the kernel's doing) */
		if (!new_state)
			return true;
		ctx->rc_state = new_state;
	}

	/* User-space RPCs are _always_ required (or at least expected)
	 * to restart system calls, meaning  that once the first  one's
	 * been executed, any that come after have to be told that they
	 * will return to an async user-space location (rather than  to
	 * another system call)
	 *
	 * NOTE: In actuality, `_RPC_REASONCTX_SYNC' is passed as reason
	 *       for any additional RPCs */
	ctx->rc_context = RPC_REASONCTX_SYSRET;
	return true;
}

/* Helper function for `userexcept_handler()' and `userexcept_sysret()'
 * @return: true:  RPC was handled.
 * @return: false: RPC cannot be handled right now; Load other RPCs and try again */
PRIVATE WUNUSED NONNULL((1, 2)) bool
NOTHROW(FCALL userexcept_exec_user_signo_rpc)(/*in|out*/ struct rpc_context *__restrict ctx,
                                              /*in|out*/ struct exception_info *__restrict error,
                                              signo_t signo) {
	/* Because signals handled here must properly integrate with  other
	 * RPCs, as well as the current `error', we can't just make use  of
	 * `userexcept_raisesignal_from_exception()', but have to implement
	 * signal action handling ourselves.
	 *
	 * This is required for signal actions such as SIG_CORE, or
	 * SIG_STOP, which introduce  custom control routing  which
	 * could otherwise interfere with normal RPC handling. */
	struct kernel_sigaction action;
	assert(sigvalid(signo));
again_load_threadsig_action:
	sighand_getaction(signo, &action);

	/* Custom handlers. */
again_switch_action_handler:
	switch ((uintptr_t)action.sa_handler) {

	case __SIG_DFL:
		action.sa_handler = sighand_default_action(signo);
		goto again_switch_action_handler;

	case __SIG_IGN:
		/* Ignored */
		break;

	case __SIG_CONT:
		/* Undo the effects of `SIG_STOP' */
		if (error->ei_code == EXCEPT_CODEOF(_E_STOP_PROCESS))
			error->ei_code = EXCEPT_CODEOF(E_OK);
		break;

	case __SIG_TERM: {
		except_code_t code;
		code = EXCEPT_CODEOF(E_EXIT_PROCESS);
		__IF0 { case __SIG_EXIT: code = EXCEPT_CODEOF(E_EXIT_THREAD); }
		__IF0 { case __SIG_STOP: code = EXCEPT_CODEOF(_E_STOP_PROCESS); }
		__IF0 { case __SIG_CORE: code = EXCEPT_CODEOF(_E_CORE_PROCESS); }

		/* If applicable, override the active return-exception. */
		if (except_priority(error->ei_code) < except_priority(code)) {
			union wait reason;
			reason.w_status = W_EXITCODE(1, signo);
			bzero(error, sizeof(struct exception_info));
			error->ei_code = code;
			if (action.sa_handler == SIG_CORE) {
				error->ei_data.e_args.e_pointers[1] = signo;
				error->ei_data.e_args.e_pointers[2] = SI_KERNEL; /* ??? */
				reason.w_status |= WCOREFLAG;
			} else if (action.sa_handler == SIG_STOP) {
				reason.w_status = W_STOPCODE(signo);
			}
			error->ei_data.e_args.e_pointers[0] = reason.w_status;
		}
	}	break;

	default: {
		siginfo_t info;
		bzero(&info, sizeof(info));
		info.si_signo = signo;
		info.si_code  = SI_KERNEL; /* ??? */
		info.si_pid   = 1;         /* (init?) */
//		info.si_uid   = 0;         /* (root?) */
		TRY {
			struct icpustate *newstate;

			/* "Normal" invoke-userspace-function signal action */
			newstate = userexcept_callsignal_and_maybe_restart_syscall(ctx->rc_state, &action, &info,
			                                                           ctx->rc_context == RPC_REASONCTX_SYSCALL
			                                                           ? &ctx->rc_scinfo
			                                                           : NULL);

			/* When  `userexcept_callsignal_and_maybe_restart_syscall()'  returns `NULL',
			 * a race condition is indicated where the user-defined signal action changed
			 * before the handler function could be invoked.
			 * This is important to ensure that `SA_RESETHAND' works atomically. */
			if (newstate == NULL)
				goto again_load_threadsig_action;
			ctx->rc_state = newstate;
		} EXCEPT {
			/* Prioritize errors. */
			struct exception_info *tls = except_info();
			if (tls->ei_code == EXCEPT_CODEOF(E_INTERRUPT_USER_RPC))
				return false; /* Load other RPCs and try again. */
			if (except_priority(error->ei_code) < except_priority(tls->ei_code)) {
				memcpy(error, tls, sizeof(struct exception_info));
				ctx->rc_context = RPC_REASONCTX_SYSRET; /* Will need to return to user-space to handle this exception */
			}
		}
	}	break;

	}

	/* User-space RPCs are _always_ required (or at least expected)
	 * to restart system calls, meaning  that once the first  one's
	 * been executed, any that come after have to be told that they
	 * will return to an async user-space location (rather than  to
	 * another system call)
	 *
	 * NOTE: In actuality, `_RPC_REASONCTX_SYNC' is passed as reason
	 *       for any additional RPCs */
	ctx->rc_context = RPC_REASONCTX_SYSRET;
	return true;
}


PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL set_unknown_syscall_exception)(struct rpc_syscall_info const *__restrict sc_info) {
	struct exception_info *info;
	/* Fill in exception information. */
	info = except_info();
	info->ei_code = EXCEPT_CODEOF(E_UNKNOWN_SYSTEMCALL);
	info->ei_data.e_args.e_unknown_systemcall.us_sysno = sc_info->rsi_sysno;
	info->ei_data.e_args.e_unknown_systemcall.us_flags = sc_info->rsi_flags;
	info->ei_data.e_args.e_unknown_systemcall.us_arg0  = sc_info->rsi_regs[0];
	info->ei_data.e_args.e_unknown_systemcall.us_arg1  = sc_info->rsi_regs[1];
	info->ei_data.e_args.e_unknown_systemcall.us_arg2  = sc_info->rsi_regs[2];
	info->ei_data.e_args.e_unknown_systemcall.us_arg3  = sc_info->rsi_regs[3];
	info->ei_data.e_args.e_unknown_systemcall.us_arg4  = sc_info->rsi_regs[4];
	info->ei_data.e_args.e_unknown_systemcall.us_arg5  = sc_info->rsi_regs[5];
#if EXCEPT_BACKTRACE_SIZE != 0
	bzero(info->ei_trace, sizeof(info->ei_trace));
#endif /* EXCEPT_BACKTRACE_SIZE != 0 */
	info->ei_flags = EXCEPT_FNORMAL;
}

/* Helper function to implement ENOSYS handling. */
PUBLIC ABNORMAL_RETURN ATTR_NORETURN NONNULL((1, 2)) void
NOTHROW(FCALL userexcept_handler_nosys)(struct icpustate *__restrict state,
                                        struct rpc_syscall_info const *__restrict sc_info) {
again:
	set_unknown_syscall_exception(sc_info);
	state = userexcept_handler(state, sc_info);
	goto again;
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
	if unlikely(atomic_read(&target->t_flags) & (TASK_FTERMINATING | TASK_FTERMINATED)) {
		decref(target);
		return state;
	}
	caller     = THIS_TASK;
	mycpu      = caller->t_cpu;
	target_cpu = atomic_read(&target->t_cpu);
	if unlikely(target_cpu != mycpu) {
		/* Re-deliver the IPI to yet another CPU (letting it bounce until we get it right) */
		while (!cpu_sendipi(target_cpu,
		                    &ipi_userexcept_sysret_inject_safe,
		                    args, /* inherit:reference:target */
		                    CPU_IPI_FWAKEUP))
			task_pause();
		return state;
	}
	userexcept_sysret_inject_nopr(target);
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


/* High-level wrapper  for `userexcept_sysret_inject_nopr()'  that makes  all
 * of the right decisions to only ever call `userexcept_sysret_inject_nopr()'
 * in  a valid context: using IPIs to make  the call from the same CPU as the
 * one  currently hosting `thread',  and ensuring that the  thread has yet to
 * terminate.
 * Additionally, this function will make a call to `task_wake()'  once
 * the injection has completed, meaning that `thread' will wake up and
 * either immediately start  executing `userexcept_sysret()', or  will
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
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL userexcept_sysret_inject_safe)(struct task *__restrict thread,
                                             syscall_ulong_t rpc_flags) {
	preemption_flag_t was;
#ifndef CONFIG_NO_SMP
	struct cpu *mycpu;
	struct cpu *target_cpu;
	preemption_pushoff(&was);
	mycpu      = THIS_CPU;
	target_cpu = atomic_read(&thread->t_cpu);
	if (mycpu != target_cpu) {
		void *args[CPU_IPI_ARGCOUNT];
		args[0] = (void *)incref(thread);
#ifdef IPI_USEREXCEPT_SYSRET_INJECT_SAFE_ALLOW_QUANTUM_HEIST
		args[1] = (void *)rpc_flags;
#endif /* IPI_USEREXCEPT_SYSRET_INJECT_SAFE_ALLOW_QUANTUM_HEIST */
		/* Must use `CPU_IPI_FWAITFOR' to  ensure that `thread' won't  be
		 * in user-space by the time we return. -- This is important  for
		 * the use-case of getting threads out of user-space during exec,
		 * where we need to unmap user-space (and can't have anyone still
		 * be in there when we do so)
		 *
		 * NOTE: this works correctly even in  the case where the  target
		 *       thread changes CPU, since a thread changing its CPU will
		 *       also  force  it to  do `userexcept_sysret_inject_self()'
		 *       following the transition having been made. */
		while (!cpu_sendipi(target_cpu, &ipi_userexcept_sysret_inject_safe,
		                    args, CPU_IPI_FWAKEUP | CPU_IPI_FWAITFOR))
			task_pause();
		preemption_pop(&was);
	} else
#endif /* !CONFIG_NO_SMP */
	{
		struct task *caller = THIS_TASK;
#ifdef CONFIG_NO_SMP
		preemption_pushoff(&was);
#endif /* CONFIG_NO_SMP */
		/* check if the thread has already terminated */
		if (thread->t_flags & (TASK_FTERMINATING | TASK_FTERMINATED)) {
			preemption_pop(&was);
			return;
		}
		userexcept_sysret_inject_nopr(thread);
		if (caller != thread) {
			thread = sched_intern_localwake(mycpu, caller, thread,
			                                (rpc_flags & RPC_PRIORITY_F_HIGH) != 0 &&
			                                preemption_wason(&was));
			if (thread != caller) {
				/* Immediately switch to the next thread. */
				FORCPU(mycpu, thiscpu_sched_current) = thread;
				cpu_run_current_and_remember_nopr(caller);
			}
		}
		preemption_pop(&was);
	}
}


/* Helper function to test (and try to set in the userprocmask) if
 * a given signal number is currently masked. Only if it unmasked,
 * or if the  masking-status cannot be  determined will sysret  be
 * injected via `userexcept_sysret_inject_nopr()' */
PRIVATE NOBLOCK NOPREEMPT NONNULL((1)) void
NOTHROW(FCALL userexcept_sysret_inject_and_marksignal_nopr)(struct task *__restrict thread,
                                                            signo_t signo) {
	int status;
	assert(thread->t_cpu == THIS_CPU);
	status = sigmask_ismasked_in(thread, signo);

	/* If the signal isn't masked, or masking cannot be determined, inject a sysret.
	 * Also  wake up the thread if it is explicitly requesting to be woken for every
	 * signal it is send, even if that signal is being masked. Such behavior is used
	 * to implement the `sigtimedwait(2)' and `sigsuspend(2)' system calls. */
	if (status != SIGMASK_ISMASKED_NOPF_YES || (thread->t_flags & TASK_FWAKEONMSKRPC)) {
		/* Set the thread's `TASK_FRPC' flag to indicate that it's got work to do */
		atomic_or(&thread->t_flags, TASK_FRPC);
		userexcept_sysret_inject_nopr(thread);
	}
}


#ifndef CONFIG_NO_SMP
PRIVATE NOBLOCK struct icpustate *
NOTHROW(FCALL ipi_userexcept_sysret_inject_and_marksignal_safe)(struct icpustate *__restrict state,
                                                                void *args[CPU_IPI_ARGCOUNT]) {
	REF struct task *target;
	struct cpu *mycpu, *target_cpu;
	struct task *caller;
	target = (REF struct task *)args[0];

	/* Re-check that the target thread has yet to start terminating. */
	if unlikely(atomic_read(&target->t_flags) & (TASK_FTERMINATING | TASK_FTERMINATED)) {
		decref(target);
		return state;
	}
	caller     = THIS_TASK;
	mycpu      = caller->t_cpu;
	target_cpu = atomic_read(&target->t_cpu);
	if unlikely(target_cpu != mycpu) {
		/* Re-deliver the IPI to yet another CPU (letting it bounce until we get it right) */
		while (!cpu_sendipi(target_cpu,
		                    &ipi_userexcept_sysret_inject_safe,
		                    args, /* inherit:reference:target */
		                    CPU_IPI_FWAKEUP))
			task_pause();
		return state;
	}
	userexcept_sysret_inject_and_marksignal_nopr(target, _RPC_GETSIGNO((uintptr_t)args[1]));
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


/* Check if `_RPC_GETSIGNO(rpc_flags)' is currently masked by `thread' (thereby
 * also marking the associated bit  as pending within its userprocmask,  should
 * `thread' be using one). Only if  that signal vector isn't currently  masked,
 * proceed to do the same as also done by `userexcept_sysret_inject_safe()'.
 *
 * The  userprocmask is accessed purely via *_nopf functions (hence the NOBLOCK),
 * and if doing this  fails, act as  though the signal  vector isn't masked,  and
 * proceed with calling `userexcept_sysret_inject_nopr()', resulting in the given
 * `thread' eventually calling `userexcept_sysret()'  which will repeat the  test
 * masked signals (at which point _it_ is  able to use the non-*_nopf variant  of
 * the masking test function `sigmask_ismasked()')
 *
 * Additionally, this function will also set the `TASK_FRPC' just before making
 * the call to `userexcept_sysret_inject_nopr()' (though obviously only if such
 * a call actually ends up being made) */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL userexcept_sysret_inject_and_marksignal_safe)(struct task *__restrict thread,
                                                            syscall_ulong_t rpc_flags) {
	preemption_flag_t was;
#ifndef CONFIG_NO_SMP
	struct cpu *mycpu;
	struct cpu *target_cpu;
	preemption_pushoff(&was);
	mycpu      = THIS_CPU;
	target_cpu = atomic_read(&thread->t_cpu);
	if (mycpu != target_cpu) {
		void *args[CPU_IPI_ARGCOUNT];
		args[0] = (void *)incref(thread);
		args[1] = (void *)(uintptr_t)rpc_flags;

		/* Must use `CPU_IPI_FWAITFOR' to  ensure that `thread' won't  be
		 * in user-space by the time we return. -- This is important  for
		 * the use-case of getting threads out of user-space during exec,
		 * where we need to unmap user-space (and can't have anyone still
		 * be in there when we do so)
		 *
		 * NOTE: this works correctly even in  the case where the  target
		 *       thread changes CPU, since a thread changing its CPU will
		 *       also  force  it to  do `userexcept_sysret_inject_self()'
		 *       following the transition having been made. */
		while (!cpu_sendipi(target_cpu, &ipi_userexcept_sysret_inject_and_marksignal_safe,
		                    args, CPU_IPI_FWAKEUP | CPU_IPI_FWAITFOR))
			task_pause();
		preemption_pop(&was);
	} else
#endif /* !CONFIG_NO_SMP */
	{
		struct task *caller = THIS_TASK;
#ifdef CONFIG_NO_SMP
		preemption_pushoff(&was);
#endif /* CONFIG_NO_SMP */

		/* check if the thread has already terminated */
		if (thread->t_flags & (TASK_FTERMINATING | TASK_FTERMINATED)) {
			preemption_pop(&was);
			return;
		}
		userexcept_sysret_inject_and_marksignal_nopr(thread, _RPC_GETSIGNO(rpc_flags));
		if (caller != thread) {
			thread = sched_intern_localwake(mycpu, caller, thread,
			                                (rpc_flags & RPC_PRIORITY_F_HIGH) != 0 &&
			                                preemption_wason(&was));
			if (thread != caller) {
				/* Immediately switch to the next thread. */
				FORCPU(mycpu, thiscpu_sched_current) = thread;
				cpu_run_current_and_remember_nopr(caller);
			}
		}
		preemption_pop(&was);
	}
}


PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL userexcept_sysret_injectpid_safe)(struct taskpid *__restrict pid,
                                                syscall_ulong_t rpc_flags) {
	REF struct task *thread = taskpid_gettask(pid);
	if (thread) {
		userexcept_sysret_inject_safe(thread, rpc_flags);
		decref_unlikely(thread);
	}
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL userexcept_sysret_injectpid_and_marksignal_safe)(struct taskpid *__restrict pid,
                                                               syscall_ulong_t rpc_flags) {
	REF struct task *thread = taskpid_gettask(pid);
	if (thread) {
		userexcept_sysret_inject_and_marksignal_safe(thread, rpc_flags);
		decref_unlikely(thread);
	}
}

/* Invoke  `userexcept_sysret_inject_safe()'  for every  thread  apart of
 * `proc', as well as set the `TASK_FRPC' flag for each of those threads. */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL userexcept_sysret_injectproc_safe)(struct taskpid *__restrict proc,
                                                 syscall_ulong_t rpc_flags) {
	struct taskpid *iter;
	struct procctl *ctl = proc->tp_pctl;
	userexcept_sysret_injectpid_safe(proc->tp_proc, rpc_flags);
	procctl_thrds_acquire(ctl);
	FOREACH_procctl_thrds(iter, ctl) {
		userexcept_sysret_injectpid_safe(iter, rpc_flags);
	}
	procctl_thrds_release(ctl);
}

/* Invoke `userexcept_sysret_inject_and_marksignal_safe()' for every thread apart of `proc' */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL userexcept_sysret_injectproc_and_marksignal_safe)(struct taskpid *__restrict proc,
                                                                syscall_ulong_t rpc_flags) {
	struct taskpid *iter;
	struct procctl *ctl = proc->tp_pctl;
	userexcept_sysret_injectpid_and_marksignal_safe(proc->tp_proc, rpc_flags);
	procctl_thrds_acquire(ctl);
	FOREACH_procctl_thrds(iter, ctl) {
		userexcept_sysret_injectpid_and_marksignal_safe(iter, rpc_flags);
	}
	procctl_thrds_release(ctl);
}



















/************************************************************************/
/* Kernel/C++ exception integration                                     */
/************************************************************************/

PRIVATE NONNULL((1)) unwind_errno_t
NOTHROW(FCALL unwind_landingpad)(unwind_fde_t *__restrict fde, /* Only non-const for lazy initialized fields! */
                                 except_register_state_t *__restrict state,
                                 void const *except_pc) {
	void const *landing_pad_pc;
	unwind_cfa_landing_state_t cfa;
	except_register_state_t new_state;
	unwind_errno_t unwind_error;
	landing_pad_pc = except_register_state_getpc(state);
	unwind_error   = unwind_fde_landing_exec(fde, &cfa, except_pc, landing_pad_pc);
	if unlikely(unwind_error != UNWIND_SUCCESS)
		goto done;

	/* Apply landing-pad transformations. */
	memcpy(&new_state, state, sizeof(new_state));
	unwind_error = unwind_cfa_landing_apply(&cfa, fde, except_pc,
	                                        &unwind_getreg_except_register_state, state,
	                                        &unwind_setreg_except_register_state, &new_state);
	if unlikely(unwind_error != UNWIND_SUCCESS)
		goto done;

	/* Write-back the new register state. */
	memcpy(state, &new_state, sizeof(new_state));
	return UNWIND_SUCCESS;
done:
	if (unwind_error == UNWIND_NO_FRAME) {
		/* Directly jump to the landing pad. */
		except_register_state_setpc(state, landing_pad_pc);
		unwind_error = UNWIND_SUCCESS;
	}
	return unwind_error;
}


INTDEF ATTR_COLD NONNULL((2)) void FCALL /* TODO: Standardize this function! (currently arch-specific) */
halt_unhandled_exception(unwind_errno_t unwind_error,
                         except_register_state_t *__restrict unwind_state);

DEFINE_PUBLIC_ALIAS(except_unwind, libc_except_unwind);
INTERN ATTR_RETNONNULL WUNUSED NONNULL((1)) except_register_state_t *
NOTHROW(FCALL libc_except_unwind)(except_register_state_t *__restrict state) {
	unwind_errno_t error;
	unwind_fde_t fde;
	except_register_state_t old_state;
	void const *pc;
	assertf(PERTASK_NE(this_exception_info.ei_code, EXCEPT_CODEOF(E_OK)) ||
	        PERTASK_NE(this_exception_info.ei_nesting, 0),
	        "In except_unwind(), but no exception set");

search_fde:
	/* unwind `state' until the nearest exception handler, or until user-space is reached.
	 * If the  later  happens,  then  we  must propagate  the  exception  to  it  instead.
	 * NOTE: -1 because the state we're being given has its PC pointer
	 *       set  to  be  directed  after  the  faulting  instruction. */
	memcpy(&old_state, state, sizeof(old_state));
	pc    = except_register_state_getpc(&old_state) - 1;
	error = unwind_fde_find(pc, &fde);
	if unlikely(error != UNWIND_SUCCESS)
		goto err;
	/* Check if there is a personality function for us to execute. */
	if (fde.f_persofun != NULL) {
		unsigned int perso_code;
		assertf(ADDR_ISKERN(fde.f_persofun),
		        "Not a kernel-space address: %p",
		        fde.f_persofun);
		perso_code = (*(except_personality_t)fde.f_persofun)(&fde, state);
		switch (perso_code) {

		case EXCEPT_PERSONALITY_EXECUTE_HANDLER:
			/* When unwinding a landing pad, we must check if there is an active
			 * `DW_CFA_GNU_args_size' instruction.
			 * If there is, we must add its value to ESP before resuming execution!
			 * s.a.: https://reviews.llvm.org/D38680 */
			error = unwind_landingpad(&fde, state, pc);
			if unlikely(error != UNWIND_SUCCESS)
				goto err;
			ATTR_FALLTHROUGH
		case EXCEPT_PERSONALITY_EXECUTE_HANDLER_NOW:
			return state; /* Execute a new handler. */

		case EXCEPT_PERSONALITY_ABORT_SEARCH:
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
		error = unwind_cfa_sigframe_apply_sysret_safe(&cfa, &fde, pc,
		                                              &unwind_getreg_except_register_state, &old_state,
		                                              &unwind_setreg_except_register_state, state);
	} else
#endif /* !CFI_UNWIND_NO_SIGFRAME_COMMON_UNCOMMON_REGISTERS */
	{
		unwind_cfa_state_t cfa;
		error = unwind_fde_exec(&fde, &cfa, pc);
		if unlikely(error != UNWIND_SUCCESS)
			goto err;
		error = unwind_cfa_apply_sysret_safe(&cfa, &fde, pc,
		                                     &unwind_getreg_except_register_state, &old_state,
		                                     &unwind_setreg_except_register_state, state);
	}

	/* When unwinding to user-space, we'll get an error `UNWIND_INVALID_REGISTER' */
	if (error == UNWIND_INVALID_REGISTER) {
		struct ucpustate ustate;
		unwind_cfa_sigframe_state_t sigframe_cfa;
		except_register_state_to_ucpustate(&old_state, &ustate);

		/* Assume that we're unwinding a signal frame when returning to user-space. */
		error = unwind_fde_sigframe_exec(&fde, &sigframe_cfa, pc);
		if unlikely(error != UNWIND_SUCCESS)
			goto err_old_state;
		error = unwind_cfa_sigframe_apply_sysret_safe(&sigframe_cfa, &fde, pc,
		                                              &unwind_getreg_except_register_state, &old_state,
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
#define LOG_SEGMENT_INCONSISTENCY(name, isval, wantval)                                     \
				do {                                                                        \
					if (isval != wantval) {                                                 \
						printk(KERN_CRIT "[except] Inconsistent unwind %%%cs: "             \
						                 "%#" PRIx32 " & 0xffff != %#" PRIx16 " [pc:%p]\n", \
						       name, isval, wantval, pc);                                   \
					}                                                                       \
				}	__WHILE0
#define LOG_SEGMENT_INCONSISTENCY_CHK(name, isval, isok)                        \
				do {                                                            \
					if (!isok(isval)) {                                         \
						printk(KERN_CRIT "[except] Inconsistent unwind %%%cs: " \
						                 "%#" PRIx32 " & 0xffff [pc:%p]\n",     \
						       name, isval, pc);                                \
					}                                                           \
				}	__WHILE0
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
				 * -> In other words:  Bochs is  entirely correct in  its emulation,  and
				 *    I'm at fault here, in which case. Honestly: Thank you Bochs. That's
				 *    one less Problem  for me to  figure out the  hard way once  testing
				 *    on real Hardware is going to start...
				 */
				LOG_SEGMENT_INCONSISTENCY_CHK('c', ustate.ucs_cs, SEGMENT_IS_VALID_KERNCODE);
				LOG_SEGMENT_INCONSISTENCY_CHK('s', ustate.ucs_ss, SEGMENT_IS_VALID_KERNDATA);
				LOG_SEGMENT_INCONSISTENCY('g', ustate.ucs_sgregs.sg_gs, expected_gs);
				LOG_SEGMENT_INCONSISTENCY('f', ustate.ucs_sgregs.sg_fs, expected_fs);
				LOG_SEGMENT_INCONSISTENCY('e', ustate.ucs_sgregs.sg_es, expected_es);
				LOG_SEGMENT_INCONSISTENCY('d', ustate.ucs_sgregs.sg_ds, expected_ds);
#undef LOG_SEGMENT_INCONSISTENCY_CHK
#undef LOG_SEGMENT_INCONSISTENCY
				error = UNWIND_INVALID_REGISTER;
				goto err_old_state;
			}
		}
#endif /* __i386__ || __x86_64__ */
		except_register_state_from_ucpustate(state, &ustate);
	} else {
		if unlikely(error != UNWIND_SUCCESS)
			goto err_old_state;
	}

#if EXCEPT_BACKTRACE_SIZE != 0
	/* Remember the current state PC as a new entry in the exception's traceback. */
	if (PERTASK_EQ(this_exception_trace[EXCEPT_BACKTRACE_SIZE - 1], NULL)) {
#if EXCEPT_BACKTRACE_SIZE > 1
		unsigned int i;
		for (i = 0; i < EXCEPT_BACKTRACE_SIZE - 1; ++i) {
			if (!PERTASK_TEST(this_exception_trace[i]))
				break;
		}
		PERTASK_SET(this_exception_trace[i], except_register_state_getpc(state));
#else /* EXCEPT_BACKTRACE_SIZE > 1 */
		PERTASK_SET(this_exception_trace[0], except_register_state_getpc(state));
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


/* Throw the current exception (which must _NOT_ be E_INTERRUPT_USER_RPC)
 * at the the given `state' and  perform all of the necessary  unwinding.
 *
 * This  function should  be used  for throwing  exception from interrupt
 * handlers (read: CPU exception handler), such as page-faults & similar. */
PUBLIC ABNORMAL_RETURN ATTR_NORETURN NONNULL((1)) void
NOTHROW(FCALL except_throw_current_at_icpustate)(struct icpustate *__restrict state) {
	struct exception_info *info = except_info();
	assertf(info->ei_code != EXCEPT_CODEOF(E_OK),
	        "No exception thrown");
	assertf(info->ei_code != EXCEPT_CODEOF(E_INTERRUPT_USER_RPC),
	        "No, you can't throw this one like that!");

	/* Clear out the exception traceback */
#if EXCEPT_BACKTRACE_SIZE != 0
	bzero(info->ei_trace, sizeof(info->ei_trace));
#endif /* EXCEPT_BACKTRACE_SIZE != 0 */

	/* Fill in the exception register state. */
	except_register_state_from_icpustate(&info->ei_state, state);

	/* Figure out how we want to unwind this exception. */
	if (icpustate_isuser(state)) {

		/* Directly unwind into user-space. */
		state = userexcept_handler(state, NULL);

		/* We _really_ shouldn't get here, but just in case: simply load `state' */
		cpu_apply_icpustate(state);
	} else {
		except_register_state_t st, *pst;

		/* Do normal unwinding. */
		memcpy(&st, &info->ei_state, sizeof(except_register_state_t));
		pst = libc_except_unwind(&st);
		except_register_state_cpu_apply(pst);
	}
}






/* This  function  is hooked  by CFI  under `struct unwind_fde_struct::f_persofun'
 * It's exact prototype and behavior are therefor not mandated by how GCC uses it. */
DEFINE_PUBLIC_ALIAS(__gcc_personality_v0, libc_gxx_personality_v0);
DEFINE_PUBLIC_ALIAS(__gxx_personality_v0, libc_gxx_personality_v0);
INTERN WUNUSED NONNULL((1, 2)) unsigned int
NOTHROW(EXCEPT_PERSONALITY_CC libc_gxx_personality_v0)(struct unwind_fde_struct *__restrict fde,
                                                       except_register_state_t *__restrict state) {
	u8 temp, callsite_encoding;
	byte_t const *reader;
	byte_t const *landingpad;
	byte_t const *callsite_end;
	size_t callsite_size;

	reader     = (byte_t const *)fde->f_lsdaaddr;
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
		(void)dwarf_decode_uleb128((byte_t const **)&reader); /* gl_typetab_off */
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
		if (except_register_state_getpc(state) > startpc && except_register_state_getpc(state) <= endpc)
#else
		if (except_register_state_getpc(state) >= startpc && except_register_state_getpc(state) < endpc)
#endif
		{
			if (handler == 0)
				return EXCEPT_PERSONALITY_CONTINUE_UNWIND; /* No handler -> exception should be propagated. */
			/* Just to the associated handler */
			except_register_state_setpc(state, landingpad + handler);
			if (action != 0) {
				/* The ABI wants  us to fill  %eax with  a pointer to  the exception  (`_Unwind_Exception').
				 * However,  since  KOS exception  is kept  a bit  simpler  (so-as to  allow it  to function
				 * without  the need of dynamic memory allocation),  the current exception isn't an internal
				 * implementation detail of the runtime, but rather stored in an exposed, per-task variable.
				 * So while what we  write here really doesn't  matter at all, let's  just put in  something
				 * that at the very least makes a bit of sense. */
				except_register_state_set_unwind_exception(state, except_code());
			}
			return EXCEPT_PERSONALITY_EXECUTE_HANDLER;
		}
	}
	/* Default behavior: abort exception handling (this function was marked as NOTHROW) */
	return EXCEPT_PERSONALITY_ABORT_SEARCH;
}


DECL_END

#ifndef __INTELLISENSE__
#define DEFINE_userexcept_handler
#include "except-handler-userexcept.c.inl"
#define DEFINE_userexcept_handler_with_sigmask
#include "except-handler-userexcept.c.inl"
#define DEFINE_userexcept_sysret
#include "except-handler-userexcept.c.inl"
#endif /* !__INTELLISENSE__ */

#endif /* !GUARD_KERNEL_SRC_MISC_EXCEPT_HANDLER_C */
