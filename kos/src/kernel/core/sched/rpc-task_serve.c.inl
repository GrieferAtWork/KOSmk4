/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifdef __INTELLISENSE__
#include "rpc.c"
#define    DEFINE_task_serve_with_icpustate
//#define          DEFINE_task_serve_with_icpustate_nx
//#define DEFINE_task_serve_with_icpustate_and_sigmask
#endif /* __INTELLISENSE__ */

#include <sched/sigaction.h>

#include <signal.h>

#if (defined(DEFINE_task_serve_with_icpustate) +    \
     defined(DEFINE_task_serve_with_icpustate_nx) + \
     defined(DEFINE_task_serve_with_icpustate_and_sigmask)) != 1
#error "Must #define exactly one of these"
#endif /* ... */

DECL_BEGIN

#undef LOCAL_NOEXCEPT
#undef LOCAL_HAVE_SIGMASK

/* Automatically updates `state' to include the intended return value for `task_serve()'! */
#ifdef DEFINE_task_serve_with_icpustate
PUBLIC BLOCKING ATTR_RETNONNULL WUNUSED NONNULL((1)) struct icpustate *FCALL
task_serve_with_icpustate(struct icpustate *__restrict state)
		THROWS(E_INTERRUPT_USER_RPC, ...)
#elif defined(DEFINE_task_serve_with_icpustate_nx)
PUBLIC BLOCKING ATTR_RETNONNULL WUNUSED NONNULL((1)) struct icpustate *
NOTHROW(FCALL task_serve_with_icpustate_nx)(struct icpustate *__restrict state)
#define LOCAL_NOEXCEPT
#else /* DEFINE_task_serve_with_icpustate */
PUBLIC BLOCKING ATTR_RETNONNULL WUNUSED NONNULL((1)) struct icpustate *FCALL
task_serve_with_icpustate_and_sigmask(struct icpustate *__restrict state,
                                      NCX sigset_t const *sigmask)
		THROWS(E_SEGFAULT, E_INTERRUPT_USER_RPC, ...)
#define LOCAL_HAVE_SIGMASK
#endif /* !DEFINE_task_serve_with_icpustate */
{
#ifndef LOCAL_NOEXCEPT
	struct exception_info error;
#endif /* !LOCAL_NOEXCEPT */
	struct pending_rpc_slist pending; /* Pending RPCs */
	struct pending_rpc_slist runnow;  /* RPCs that should be executed now */
	struct pending_rpc_slist restore; /* RPCs that must be restored */
	struct pending_rpc **restore_plast;
	struct rpc_context ctx;
#ifdef LOCAL_NOEXCEPT
	unsigned int result;
#else /* LOCAL_NOEXCEPT */
	bool did_serve_rpcs;
	bool must_unwind;
#endif /* !LOCAL_NOEXCEPT */

	ctx.rc_context = RPC_REASONCTX_SYNC;
	ctx.rc_state   = state;
	restore_plast  = SLIST_PFIRST(&restore);

#ifdef LOCAL_NOEXCEPT
	result = TASK_SERVE_NX_NORMAL;
#else /* LOCAL_NOEXCEPT */
	assertf(!except_active(), "Then how would we be able to THROW below?");
	error.ei_code  = EXCEPT_CODEOF(E_OK);
	did_serve_rpcs = false;
	must_unwind    = false;
#endif /* !LOCAL_NOEXCEPT */
	atomic_and(&PERTASK(this_task.t_flags), ~TASK_FRPC);

	/* Load RPC functions. This must happen _AFTER_ we clear
	 * the  pending-RPC  flag to  prevent a  race condition. */
	pending.slh_first = SLIST_ATOMIC_CLEAR(&PERTASK(this_rpcs));
	SLIST_INIT(&runnow);

#ifndef LOCAL_NOEXCEPT
handle_pending:
#endif /* !LOCAL_NOEXCEPT */
	while (!SLIST_EMPTY(&pending)) {
		struct pending_rpc *rpc = SLIST_FIRST(&pending);
		SLIST_REMOVE_HEAD(&pending, pr_link);
		if ((rpc->pr_flags & (RPC_CONTEXT_KERN | RPC_SYNCMODE_F_USER | _RPC_CONTEXT_INACTIVE)) == RPC_CONTEXT_KERN) {
#ifdef LOCAL_NOEXCEPT
			if (!(rpc->pr_flags & RPC_CONTEXT_NOEXCEPT)) {
				/* Cannot execute exception-enabled RPCs */
				*restore_plast = rpc;
				restore_plast  = &rpc->pr_link.sle_next;
				result |= TASK_SERVE_NX_EXCEPT;
				atomic_or(&PERTASK(this_task.t_flags), TASK_FRPC);
			} else
#endif /* LOCAL_NOEXCEPT */
			{
				/* Enabling interrupts when RPCs get served is part of the ABI! */
				PREEMPTION_ENABLE();
				icpustate_setpreemption(ctx.rc_state, 1);

				/* Execute synchronous kernel RPC immediately. */
				SLIST_INSERT_HEAD(&runnow, rpc, pr_link);

#ifdef LOCAL_NOEXCEPT
				result |= TASK_SERVE_NX_DIDRUN;
#else /* LOCAL_NOEXCEPT */
				did_serve_rpcs = true;
#endif /* !LOCAL_NOEXCEPT */
			}
		} else {
			/* user-level-, or inactive RPC (restore) */
			*restore_plast = rpc;
			restore_plast  = &rpc->pr_link.sle_next;
			if (!(rpc->pr_flags & _RPC_CONTEXT_INACTIVE)) {
				if (!(rpc->pr_flags & RPC_CONTEXT_KERN)) {
					signo_t signo = _RPC_GETSIGNO(rpc->pr_flags);
#ifdef LOCAL_HAVE_SIGMASK
					if (sigismember(sigmask, signo))
						continue; /* Signal is known to be masked! (so skip) */
#else /* LOCAL_HAVE_SIGMASK */
					/* NOTE: `sigmask_ismasked_chk_nopf()' returns one of:
					 *  - SIGMASK_ISMASKED_NOPF_YES:   Signal is masked
					 *  - SIGMASK_ISMASKED_NOPF_NO:    Signal isn't masked
					 *  - SIGMASK_ISMASKED_NOPF_FAULT: Unable to access userprocmask */
					int status = sigmask_ismasked_nopf(signo);
					if (status == SIGMASK_ISMASKED_NOPF_YES)
						continue; /* Signal is known to be masked! (so skip) */
#endif /* !LOCAL_HAVE_SIGMASK */

					/* For posix-signals (iow: no user-RPCs), check if the current
					 * disposition for that signal is  SIG_IGN. If it is, then  we
					 * mustn't unwind the current system call, but rather silently
					 * discard the RPC and continue execution like normal!
					 *
					 * Such semantics are required for stuff like `handle_fifohandle_write',
					 * which  needs to return  with EPIPE when the  signal is being ignored.
					 *
					 * But if we were to unwind  normally for ignored signals, then  that
					 * would result in the RPC only being discarded once the system  call
					 * has been unwound, after which  point it'll be restarted  silently,
					 * which would be no-good since it might lead to an infinite loop  of
					 * the thread sending itself a signal, unwinding the system call, the
					 * signal  being discarded, the system call being started, and all of
					 * it starting again by the thread sending itself the signal again! */
					if (rpc->pr_flags & RPC_CONTEXT_SIGNAL) {
						sighandler_t func;
						struct sighand_ptr *handptr;
						func    = SIG_DFL;
						handptr = THIS_SIGHAND_PTR;
						if (handptr != NULL) {
							struct sighand *hand;
							if (!atomic_rwlock_read_nx(&handptr->sp_lock)) {
								assert(!PREEMPTION_ENABLED());
								PREEMPTION_ENABLE();
								icpustate_setpreemption(ctx.rc_state, 1);
#ifdef LOCAL_NOEXCEPT
								result |= TASK_SERVE_NX_DIDRUN;
#else /* LOCAL_NOEXCEPT */
								did_serve_rpcs = true;
#endif /* !LOCAL_NOEXCEPT */
								/* This can't throw  because it only  could when  preemption
								 * were disabled, which it isn't because we just enabled it! */
								atomic_rwlock_read(&handptr->sp_lock);
							}
							if ((hand = handptr->sp_hand) != NULL)
								func = hand->sh_actions[signo - 1].sa_handler;
							atomic_rwlock_endread(&handptr->sp_lock);
						}
						if (func == SIG_DFL)
							func = sighand_default_action(signo);
						if (func == SIG_IGN) {
							/* Yes: discard this signal. */
							restore_plast = SLIST_PFIRST(&restore);
							while (*restore_plast != rpc)
								restore_plast = SLIST_PNEXT(*restore_plast, pr_link);
							pending_rpc_free(rpc);
							continue;
						}
					}
				}

#ifdef LOCAL_NOEXCEPT
				/* In order to handle user-level RPCs, we need exceptions! */
				result |= TASK_SERVE_NX_EXCEPT;
#else /* LOCAL_NOEXCEPT */
				/* Enabling interrupts when RPCs get served is part of the ABI! */
				PREEMPTION_ENABLE();
				icpustate_setpreemption(ctx.rc_state, 1);
				must_unwind = true;
#endif /* !LOCAL_NOEXCEPT */
			}
		}
	}

	/* Restore RPCs that can't be served right now. */
	if (restore_plast != SLIST_PFIRST(&restore)) {
		*restore_plast = NULL;
		restore_pending_rpcs(SLIST_FIRST(&restore));
	}

	/* Execute kernel RPCs. */
	while (!SLIST_EMPTY(&runnow)) {
		struct pending_rpc *rpc = SLIST_FIRST(&runnow);
		void *cookie;
		uintptr_t rpc_flags;
		SLIST_REMOVE_HEAD(&runnow, pr_link);
		assert(rpc->pr_flags & RPC_CONTEXT_KERN);
		assert(!(rpc->pr_flags & RPC_SYNCMODE_F_USER));
		rpc_flags = rpc->pr_flags;
		cookie    = rpc;
		if (!(rpc_flags &_RPC_CONTEXT_DONTFREE))
			cookie = rpc->pr_kern.k_cookie;
#ifdef LOCAL_NOEXCEPT
		(*rpc->pr_kern.k_func)(&ctx, cookie);
#else /* LOCAL_NOEXCEPT */
		TRY {
			(*rpc->pr_kern.k_func)(&ctx, cookie);
		} EXCEPT {
			struct exception_info *tls = except_info();
			if (tls->ei_code == EXCEPT_CODEOF(E_INTERRUPT_USER_RPC)) {
				if (!(rpc_flags & _RPC_CONTEXT_DONTFREE))
					pending_rpc_free(rpc);
				/* Load additional RPCs, but discard this new exception */
				atomic_and(&PERTASK(this_task.t_flags), ~TASK_FRPC);
				pending.slh_first = SLIST_ATOMIC_CLEAR(&PERTASK(this_rpcs));
				goto handle_pending;
			}
			/* Prioritize errors. */
			if (except_priority(error.ei_code) < except_priority(tls->ei_code))
				memcpy(&error, tls, sizeof(error));
		}
#endif /* !LOCAL_NOEXCEPT */
		if (!(rpc_flags & _RPC_CONTEXT_DONTFREE))
			pending_rpc_free(rpc);
		assert(ctx.rc_context == RPC_REASONCTX_SYNC);
	}

#ifndef LOCAL_NOEXCEPT
	/* Check if we must throw a new exception. */
	if (error.ei_code != EXCEPT_CODEOF(E_OK)) {
		memcpy(except_info(), &error, sizeof(error));
		unwind_current_exception_at_icpustate(ctx.rc_state);
	}
#endif /* !LOCAL_NOEXCEPT */



	/* Unmasked process RPCs also require that we unwind the system call. */
#ifdef LOCAL_NOEXCEPT
	if (!(result & TASK_SERVE_NX_EXCEPT))
#else /* LOCAL_NOEXCEPT */
	if (!must_unwind)
#endif /* !LOCAL_NOEXCEPT */
	{
		/* Check for pending, active bitset-style RPCs */
		uint32_t pending_bitset;
		pending_bitset = PERTASK_GET(this_rpcs_sigpend);
		pending_bitset &= ~PERTASK_GET(this_rpcs_sigpend_inactive);
		if (pending_bitset != 0) {
			/* Check if any of the signals from `pending_bitset' are unmasked. */
#ifdef LOCAL_HAVE_SIGMASK
			if (((pending_bitset >> 1) & ~(uint32_t)sigmask->__val[0]) != 0)
				goto yes_have_pending_rpcs;
#else /* LOCAL_HAVE_SIGMASK */
			signo_t signo;
			for (signo = 1; signo <= 31; ++signo) {
				uint32_t signo_mask = (uint32_t)1 << signo;
				sighandler_t func;
				struct sighand_ptr *handptr;
				if (!(pending_bitset & signo_mask))
					continue;
				/* NOTE: `sigmask_ismasked_chk_nopf()' returns one of:
				 *  - SIGMASK_ISMASKED_NOPF_YES:   Signal is masked
				 *  - SIGMASK_ISMASKED_NOPF_NO:    Signal isn't masked
				 *  - SIGMASK_ISMASKED_NOPF_FAULT: Unable to access userprocmask */
				int status = sigmask_ismasked_nopf(signo);
				if (status == SIGMASK_ISMASKED_NOPF_YES)
					continue; /* Signal is known to be masked! (so skip) */
				func    = SIG_DFL;
				handptr = THIS_SIGHAND_PTR;
				if (handptr != NULL) {
					struct sighand *hand;
					if (!atomic_rwlock_read_nx(&handptr->sp_lock)) {
						assert(!PREEMPTION_ENABLED());
						PREEMPTION_ENABLE();
						icpustate_setpreemption(ctx.rc_state, 1);
#ifdef LOCAL_NOEXCEPT
						result |= TASK_SERVE_NX_DIDRUN;
#else /* LOCAL_NOEXCEPT */
						did_serve_rpcs = true;
#endif /* !LOCAL_NOEXCEPT */
						/* This can't throw  because it only  could when  preemption
						 * were disabled, which it isn't because we just enabled it! */
						atomic_rwlock_read(&handptr->sp_lock);
					}
					if ((hand = handptr->sp_hand) != NULL)
						func = hand->sh_actions[signo - 1].sa_handler;
					atomic_rwlock_endread(&handptr->sp_lock);
				}
				if (func == SIG_DFL)
					func = sighand_default_action(signo);
				if (func == SIG_IGN) {
					/* Yes: discard this signal. */
					restore_plast = SLIST_PFIRST(&restore);
					atomic_and(&PERTASK(this_rpcs_sigpend), ~signo_mask);
					continue;
				}
				goto yes_have_pending_rpcs;
			}
#endif /* !LOCAL_HAVE_SIGMASK */
		}

#ifdef LOCAL_NOEXCEPT
#ifdef LOCAL_HAVE_SIGMASK
		if (are_any_unmasked_process_rpcs_maybe_pending_with_sigmask_nx(sigmask))
#else /* LOCAL_HAVE_SIGMASK */
		if (are_any_unmasked_process_rpcs_maybe_pending_nx())
#endif /* !LOCAL_HAVE_SIGMASK */
#else /* LOCAL_NOEXCEPT */
#ifdef LOCAL_HAVE_SIGMASK
		if (are_any_unmasked_process_rpcs_pending_with_sigmask(sigmask))
#else /* LOCAL_HAVE_SIGMASK */
		if (are_any_unmasked_process_rpcs_pending())
#endif /* !LOCAL_HAVE_SIGMASK */
#endif /* !LOCAL_NOEXCEPT */
		{
yes_have_pending_rpcs:
#ifdef LOCAL_NOEXCEPT
			result |= TASK_SERVE_NX_EXCEPT;
#else /* LOCAL_NOEXCEPT */
			/* Enabling interrupts before throwing an exception is part of the ABI! */
			PREEMPTION_ENABLE();
			icpustate_setpreemption(ctx.rc_state, 1);
			must_unwind = true;
#endif /* !LOCAL_NOEXCEPT */
		}
	}

	/* Throw an exception if we have to unwind. */
#ifndef LOCAL_NOEXCEPT
	if (must_unwind)
		THROW(E_INTERRUPT_USER_RPC);
#endif /* !LOCAL_NOEXCEPT */

	/* Write-back the result. */
#ifdef LOCAL_NOEXCEPT
	icpustate_setreturn(ctx.rc_state, result);
#else /* LOCAL_NOEXCEPT */
	icpustate_setreturnbool(ctx.rc_state, did_serve_rpcs);
#endif /* !LOCAL_NOEXCEPT */
	return ctx.rc_state;
}

#undef LOCAL_HAVE_SIGMASK
#undef LOCAL_NOEXCEPT

DECL_END

#undef DEFINE_task_serve_with_icpustate_and_sigmask
#undef DEFINE_task_serve_with_icpustate_nx
#undef DEFINE_task_serve_with_icpustate
