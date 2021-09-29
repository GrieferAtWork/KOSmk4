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
#ifndef GUARD_KERNEL_SRC_SCHED_RPC_C
#define GUARD_KERNEL_SRC_SCHED_RPC_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#ifdef CONFIG_USE_NEW_RPC
#include <kernel/mman.h>
#include <kernel/rt/except-handler.h>
#include <kernel/types.h>
#include <sched/arch/rpc.h> /* _task_serve_with_icpustate_arch_set_return_bool, ... */
#include <sched/pid.h>
#include <sched/posix-signal.h>
#include <sched/rpc-internal.h>
#include <sched/rpc.h>
#include <sched/task.h>

#include <hybrid/atomic.h>

#include <kos/except.h>
#include <kos/kernel/cpu-state-helpers.h>

#include <assert.h>
#include <inttypes.h>
#include <stdalign.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

#include <libcpustate/apply.h>

DECL_BEGIN

/* [0..n][lock(INSERT(ATOMIC), CLEAR(ATOMIC && THIS_TASK))]
 * Pending RPCs. (Set of `THIS_RPCS_TERMINATED' when RPCs may no longer
 * be executed, and all that were there prior to this becoming the case
 * are/were serviced with `RPC_REASONCTX_SHUTDOWN') */
PUBLIC ATTR_PERTASK struct pending_rpc_slist this_rpcs = SLIST_HEAD_INITIALIZER(this_rpcs);


/* High-level RPC scheduling function.
 * This is the kernel-equivalent of the userspace `rpc_exec()' from <kos/rpc.h>
 *
 * @param: flags: Set of RPC flags (MUST contain `RPC_CONTEXT_KERN'):
 *   - RPC_CONTEXT_KERN:           Mandatory flag
 *   - RPC_CONTEXT_NOEXCEPT:       The given `func' never throws and may be served by `task_serve_nx()'
 *   - RPC_SYNCMODE_F_ALLOW_ASYNC: Schedule  as an asynchronous RPC (be _very_ careful about these, as
 *                                 the given `func' must act like an interrupt handler and be NOBLOCK)
 *   - RPC_SYNCMODE_F_USER:        Only  allowed  when  `!(thread->t_flags & TASK_FKERNTHREAD)':   Force
 *                                 unwind the current system call the next time `thread' makes a call to
 *                                 `task_serve()'  (if the thread is currently sleeping, it will be send
 *                                 a sporadic interrupt which should cause it to call that function once
 *                                 again). Once unwinding all to  way to userspace has finished,  invoke
 *                                 `func' in the context to which  the syscall returns. Note that  here,
 *                                 `func'  is allowed  to transition  the `ctx->rc_context'  it is given
 *                                 from `RPC_REASONCTX_SYSCALL' to `RPC_REASONCTX_SYSRET', in which case
 *                                 the system call/interrupt will not be restarted.
 *                                 When `thread == THIS_TASK', this function will not return normally,
 *                                 but will instead `THROW(E_INTERRUPT_USER_RPC)'.
 *   - RPC_SYNCMODE_F_SYSRET:      May only be used when  combined with `RPC_SYNCMODE_F_USER', in  which
 *                                 case the RPC will only be invoked the next time that `thread' returns
 *                                 to user-space (or immediately if `thread' is currently in user-space)
 *                                 Note though that an in-progress, blocking system call isn't  aborted.
 *   - RPC_PRIORITY_F_HIGH:        When  `thread' is hosted by the same CPU as the caller, gift the rest
 *                                 of the calling thread's current quantum to `thread' and have it start
 *                                 executing even before this function returns.
 * @return: true:  Success
 * @return: false: Failure because `thread' has already terminated. */
PUBLIC NOBLOCK_IF(rpc_gfp & GFP_ATOMIC) NONNULL((1, 3)) bool KCALL
task_rpc_exec(struct task *__restrict thread, syscall_ulong_t flags,
              prpc_exec_callback_t func, void *cookie)
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_INTERRUPT_USER_RPC) {
	struct pending_rpc_slist *list;
	struct pending_rpc *rpc, *head;
	assertf(!(flags & ~(RPC_CONTEXT_KERN | RPC_CONTEXT_NOEXCEPT |
	                    RPC_SYNCMODE_F_ALLOW_ASYNC | RPC_SYNCMODE_F_USER |
	                    RPC_SYNCMODE_F_SYSRET | RPC_PRIORITY_F_HIGH)),
	        "Invalid flags: %#" PRIxPTR " (unsupported flag used)", flags);
	assertf(flags & (RPC_CONTEXT_KERN),
	        "Invalid flags: %#" PRIxPTR " (`RPC_CONTEXT_KERN' is mandatory)", flags);
	assertf((flags & (RPC_SYNCMODE_F_SYSRET | RPC_SYNCMODE_F_USER)) != RPC_SYNCMODE_F_SYSRET,
	        "Invalid flags: %#" PRIxPTR " (`RPC_SYNCMODE_F_SYSRET' requires `RPC_SYNCMODE_F_USER')", flags);
	if (flags & RPC_SYNCMODE_F_ALLOW_ASYNC) {
		/* TODO: Async RPCs are scheduled entirely different from regular ones! */
		THROW(E_NOT_IMPLEMENTED_TODO);
	}

	rpc = pending_rpc_alloc_kern_nx(GFP_NORMAL);
	if unlikely(!rpc) {
		if (ATOMIC_READ(FORTASK(thread, this_rpcs.slh_first)) == THIS_RPCS_TERMINATED)
			return false; /* Thread has already terminated */
		rpc = pending_rpc_alloc_kern(GFP_NORMAL);
	}

	/* Initialize the new RPC. */
	rpc->pr_flags         = flags;
	rpc->pr_kern.k_func   = func;
	rpc->pr_kern.k_cookie = cookie;

	/* Insert into `thread's pending RPC list. */
	list = &FORTASK(thread, this_rpcs);
	do {
		head = ATOMIC_READ(list->slh_first);
		if unlikely(head == THIS_RPCS_TERMINATED) {
			/* Already terminated */
			pending_rpc_free(rpc);
			return false;
		}
		rpc->pr_link.sle_next = head;
		COMPILER_WRITE_BARRIER();
	} while (!ATOMIC_CMPXCH_WEAK(list->slh_first, head, rpc));

	/* Set the thread's `TASK_FRPC' flag to indicate that it's got work to do */
	ATOMIC_OR(thread->t_flags, TASK_FRPC);

	/* Deal  with the case where `thread' is currently running in user-space,
	 * which requires us to temporarily move its execution into kernel-space,
	 * such that it executes `handle_sysret_rpc()'  the next time it  returns
	 * back to user-space.
	 *
	 * This is normally done by `userexcept_sysret_inject_nopr()', however that
	 * function only  works  correctly  when  the thread  is  being  hosted  by
	 * the same  CPU as  the calling  thread. But  there's also  a wrapper  for
	 * that  low-level  function `userexcept_sysret_inject_safe()',  which does
	 * the same thing, but  also works then the  thread hosted by another  CPU. */
	if (thread->t_flags & TASK_FKERNTHREAD) {
		assertf(!(flags & RPC_SYNCMODE_F_USER), "Can't send user-return RPC to kernel-only thread");
		task_wake(thread);
	} else {
		userexcept_sysret_inject_safe(thread, flags);

		/* When sending a user-level RPC to oneself, it is necessary to force a
		 * syscall/interrupt  unwind by throwing an E_INTERRUPT_USER_RPC error.
		 * Is same behavior can also be seen in `task_serve()' */
		if ((flags & RPC_SYNCMODE_F_USER) && thread == THIS_TASK)
			THROW(E_INTERRUPT_USER_RPC);
	}

	return true;
}



/* Trigger RPC completion for `self' with context `RPC_REASONCTX_SHUTDOWN' */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL task_asyncrpc_destroy_for_shutdown)(struct pending_rpc *__restrict self) {
	if (self->pr_flags & RPC_CONTEXT_KERN) {
		/* Invoke kernel RPC in RPC_REASONCTX_SHUTDOWN-context */
		alignas(alignof(struct rpc_context))
		byte_t _ctx[offsetof(struct rpc_context, rc_scinfo)];
		struct rpc_context *ctx = (struct rpc_context *)_ctx;
		ctx->rc_context         = RPC_REASONCTX_SHUTDOWN;
		task_asyncrpc_execnow(ctx, self->pr_kern.k_func,
		                      self->pr_kern.k_cookie);
	} else if (!(self->pr_flags & RPC_CONTEXT_SIGNAL)) {
		/* Finalize userspace RPC program meta-data. */
		pending_user_rpc_fini(&self->pr_user);
	}
	pending_rpc_free(self);
}

/* Same as `task_asyncrpc_destroy_for_shutdown()', but do an entire list. */
PUBLIC NOBLOCK void
NOTHROW(FCALL task_asyncrpc_destroy_list_for_shutdown)(struct pending_rpc *first) {
	while (first) {
		struct pending_rpc *next;
		next = SLIST_NEXT(first, pr_link);
		task_asyncrpc_destroy_for_shutdown(first);
		first = next;
	}
}





PRIVATE ATTR_NORETURN void
NOTHROW(FCALL unwind_current_exception_at_icpustate)(struct icpustate *__restrict state) {
	struct kcpustate kst;
	struct kcpustate *newstate;
	icpustate_to_kcpustate(state, &kst);
	newstate = error_unwind(&kst);
	cpu_apply_kcpustate(newstate);
}


INTDEF NOBLOCK void /* From "misc/except-handler.c" */
NOTHROW(FCALL restore_pending_rpcs)(struct pending_rpc *restore);

#ifdef CONFIG_HAVE_USERPROCMASK
/* Same  as `are_any_unmasked_process_rpcs_pending()', but keep a pair
 * of internal signal  sets to track  which signals are  known-masked,
 * and known-unmasked (this allows us to work around the locking issue
 * relating to the current thread using the userprocmask mechanism)
 * @param: signo: The first known "faulty" signo that must be blocking-
 *                checked for being masked/unmasked. */
PRIVATE ATTR_NOINLINE WUNUSED NONNULL((1)) bool FCALL
are_any_unmasked_process_rpcs_pending_with_faulty(struct process_pending_rpcs *__restrict proc_rpcs,
                                                  signo_t signo)
		THROWS(E_SEGFAULT) {
	struct pending_rpc *rpc;
	sigset_t known_masked, known_unmasked;
	sigemptyset(&known_masked);
	sigemptyset(&known_unmasked);
again_test_signo:
	sigaddset(sigmask_ismasked(signo) ? &known_masked
	                                  : &known_unmasked,
	          signo);
	if unlikely(ATOMIC_READ(proc_rpcs->ppr_list.slh_first) == NULL)
		return false;
	atomic_rwlock_read(&proc_rpcs->ppr_lock);
	SLIST_FOREACH (rpc, &proc_rpcs->ppr_list, pr_link) {
		int status;
		signo = _RPC_GETSIGNO(rpc->pr_flags);
		if (sigismember(&known_masked, signo))
			continue; /* Known-masked signal */
		if (sigismember(&known_unmasked, signo)) {
			atomic_rwlock_endread(&proc_rpcs->ppr_lock);
			return true; /* Known-unmasked signal */
		}

		/* Try to read the userprocmask without causing a #PF */
		status = sigmask_ismasked_nopf(signo);
		if (status == SIGMASK_ISMASKED_NOPF_YES) {
			sigaddset(&known_masked, signo);
			continue; /* Known-masked */
		}
		if (status == SIGMASK_ISMASKED_NOPF_FAULT) {
			/* Must do a "hard" masking-test */
			atomic_rwlock_endread(&proc_rpcs->ppr_lock);
			goto again_test_signo;
		}
		atomic_rwlock_endread(&proc_rpcs->ppr_lock);
		return true;
	}
	atomic_rwlock_endread(&proc_rpcs->ppr_lock);
	return false;
}
#endif /* CONFIG_HAVE_USERPROCMASK */


/* Check if there are any unmasked process RPCs that are currently pending. */
PRIVATE WUNUSED bool FCALL are_any_unmasked_process_rpcs_pending(void)
		THROWS(E_SEGFAULT) {
	struct pending_rpc *rpc;
	struct process_pending_rpcs *proc_rpcs = &THIS_PROCESS_RPCS;
	if (ATOMIC_READ(proc_rpcs->ppr_list.slh_first) == NULL)
		return false;
	atomic_rwlock_read(&proc_rpcs->ppr_lock);
	SLIST_FOREACH (rpc, &proc_rpcs->ppr_list, pr_link) {
		int status;
		status = sigmask_ismasked_nopf(_RPC_GETSIGNO(rpc->pr_flags));
		if (status == SIGMASK_ISMASKED_NOPF_YES)
			continue;
#ifdef CONFIG_HAVE_USERPROCMASK
		if (status == SIGMASK_ISMASKED_NOPF_FAULT) {
			signo_t signo = _RPC_GETSIGNO(rpc->pr_flags);
			atomic_rwlock_endread(&proc_rpcs->ppr_lock);
			return are_any_unmasked_process_rpcs_pending_with_faulty(proc_rpcs, signo);
		}
		atomic_rwlock_endread(&proc_rpcs->ppr_lock);
		return true;
#else /* CONFIG_HAVE_USERPROCMASK */
		atomic_rwlock_endread(&proc_rpcs->ppr_lock);
		return true;
#endif /* !CONFIG_HAVE_USERPROCMASK */
	}
	atomic_rwlock_endread(&proc_rpcs->ppr_lock);
	return false;
}

/* Same as `are_any_unmasked_process_rpcs_pending()', but use *_nopf memory
 * access, and if that fails, assume that pending RPCs are always unmasked. */
PRIVATE WUNUSED bool NOTHROW(FCALL are_any_unmasked_process_rpcs_maybe_pending_nx)(void) {
	struct pending_rpc *rpc;
	struct process_pending_rpcs *proc_rpcs = &THIS_PROCESS_RPCS;
	if (ATOMIC_READ(proc_rpcs->ppr_list.slh_first) == NULL)
		return false;
	if (!atomic_rwlock_tryread(&proc_rpcs->ppr_lock))
		return true; /* Must assume that at least one of them would be unmasked in our thread. */
	SLIST_FOREACH (rpc, &proc_rpcs->ppr_list, pr_link) {
		int status;
		status = sigmask_ismasked_nopf(_RPC_GETSIGNO(rpc->pr_flags));
		if (status == SIGMASK_ISMASKED_NOPF_YES)
			continue;
		/* Either the signal number isn't masked, or the status can't be determined.
		 * In any case, we're supposed to act like it isn't masked, since our caller
		 * asked weather there **may** be unmasked process RPCs. */
		atomic_rwlock_endread(&proc_rpcs->ppr_lock);
		return true;
	}
	atomic_rwlock_endread(&proc_rpcs->ppr_lock);
	return false;
}


/* Automatically updates `state' to include the intended return value for `task_serve()'! */
PUBLIC ATTR_RETNONNULL WUNUSED NONNULL((1)) struct icpustate *FCALL
task_serve_with_icpustate(struct icpustate *__restrict state)
		THROWS(E_INTERRUPT_USER_RPC, ...) {
	struct exception_info error;
	struct pending_rpc_slist pending; /* Pending RPCs */
	struct pending_rpc_slist runnow;  /* RPCs that should be executed now */
	struct pending_rpc_slist restore; /* RPCs that must be restored */
	struct pending_rpc **restore_plast;
	struct rpc_context ctx;
	bool did_serve_rpcs;
	bool must_unwind;
	ctx.rc_context    = RPC_REASONCTX_SYNC;
	ctx.rc_state      = state;
	error.ei_code     = ERROR_CODEOF(E_OK);
	pending.slh_first = SLIST_ATOMIC_CLEAR(&PERTASK(this_rpcs));
	restore_plast     = SLIST_PFIRST(&restore);
	did_serve_rpcs    = false;
	must_unwind       = false;
handle_pending:
	ATOMIC_AND(PERTASK(this_task.t_flags), ~TASK_FRPC);
	while (!SLIST_EMPTY(&pending)) {
		struct pending_rpc *rpc = SLIST_FIRST(&pending);
		SLIST_REMOVE_HEAD(&pending, pr_link);
		if ((rpc->pr_flags & (RPC_CONTEXT_KERN | RPC_SYNCMODE_F_USER | _RPC_CONTEXT_INACTIVE)) == RPC_CONTEXT_KERN) {
			/* Enabling interrupts when RPCs get served is part of the ABI! */
			PREEMPTION_ENABLE();

			/* Execute synchronous kernel RPC immediately. */
			SLIST_INSERT_HEAD(&runnow, rpc, pr_link);
			did_serve_rpcs = true;
		} else {
			/* user-level-, or inactive RPC (restore) */
			*restore_plast = rpc;
			restore_plast  = &rpc->pr_link.sle_next;
			if (!(rpc->pr_flags & _RPC_CONTEXT_INACTIVE)) {
				if (!(rpc->pr_flags & RPC_CONTEXT_KERN)) {
					/* NOTE: `sigmask_ismasked_chk_nopf()' returns one of:
					 *  - SIGMASK_ISMASKED_NOPF_YES:   Signal is masked
					 *  - SIGMASK_ISMASKED_NOPF_NO:    Signal isn't masked
					 *  - SIGMASK_ISMASKED_NOPF_FAULT: Unable to access userprocmask */
					int status = sigmask_ismasked_nopf(_RPC_GETSIGNO(rpc->pr_flags));
					if (status == SIGMASK_ISMASKED_NOPF_YES)
						continue; /* Signal is known to be masked! (so skip) */
				}

				/* Enabling interrupts when RPCs get served is part of the ABI! */
				PREEMPTION_ENABLE();
				must_unwind = true;
			}
		}
	}

	/* Execute kernel RPCs. */
	while (!SLIST_EMPTY(&runnow)) {
		struct pending_rpc *rpc = SLIST_FIRST(&runnow);
		SLIST_REMOVE_HEAD(&runnow, pr_link);
		assert(rpc->pr_flags & RPC_CONTEXT_KERN);
		assert(!(rpc->pr_flags & RPC_SYNCMODE_F_USER));
		TRY {
			(*rpc->pr_kern.k_func)(&ctx, rpc->pr_kern.k_cookie);
		} EXCEPT {
			struct exception_info *tls = error_info();
			if (tls->ei_code == ERROR_CODEOF(E_INTERRUPT_USER_RPC)) {
				pending_rpc_free(rpc);
				/* Load additional RPCs, but discard this new exception */
				ATOMIC_AND(PERTASK(this_task.t_flags), ~TASK_FRPC);
				pending.slh_first = SLIST_ATOMIC_CLEAR(&PERTASK(this_rpcs));
				goto handle_pending;
			}
			/* Prioritize errors. */
			if (error_priority(error.ei_code) < error_priority(tls->ei_code))
				memcpy(&error, tls, sizeof(error));
		}
		pending_rpc_free(rpc);
		assert(ctx.rc_context == RPC_REASONCTX_SYNC);
	}

	/* Restore RPCs that can't be served right now. */
	if (restore_plast != SLIST_PFIRST(&restore)) {
		*restore_plast = NULL;
		restore_pending_rpcs(SLIST_FIRST(&restore));
	}

	/* Check if we must throw a new exception. */
	if (error.ei_code != ERROR_CODEOF(E_OK)) {
		memcpy(error_info(), &error, sizeof(error));
		unwind_current_exception_at_icpustate(ctx.rc_state);
	}

	/* Unmasked process RPCs also require that we unwind the system call. */
	if (!must_unwind) {
		if (are_any_unmasked_process_rpcs_pending())
			must_unwind = true;
	}
	if (must_unwind)
		THROW(E_INTERRUPT_USER_RPC);
	_task_serve_with_icpustate_arch_set_return_bool(ctx.rc_state, did_serve_rpcs);
	return ctx.rc_state;
}


PUBLIC ATTR_RETNONNULL WUNUSED NONNULL((1)) struct icpustate *
NOTHROW(FCALL task_serve_with_icpustate_nx)(struct icpustate *__restrict state) {
	struct pending_rpc_slist pending; /* Pending RPCs */
	struct pending_rpc_slist runnow;  /* RPCs that should be executed now */
	struct pending_rpc_slist restore; /* RPCs that must be restored */
	struct pending_rpc **restore_plast;
	struct rpc_context ctx;
	unsigned int result;
	ctx.rc_context    = RPC_REASONCTX_SYNC;
	ctx.rc_state      = state;
	pending.slh_first = SLIST_ATOMIC_CLEAR(&PERTASK(this_rpcs));
	restore_plast     = SLIST_PFIRST(&restore);
	result            = TASK_SERVE_NX_NORMAL;
handle_pending:
	ATOMIC_AND(PERTASK(this_task.t_flags), ~TASK_FRPC);
	while (!SLIST_EMPTY(&pending)) {
		struct pending_rpc *rpc = SLIST_FIRST(&pending);
		SLIST_REMOVE_HEAD(&pending, pr_link);
		if ((rpc->pr_flags & (RPC_CONTEXT_KERN | RPC_SYNCMODE_F_USER | _RPC_CONTEXT_INACTIVE)) == RPC_CONTEXT_KERN) {
			if (!(rpc->pr_flags & RPC_CONTEXT_NOEXCEPT)) {
				/* Cannot execute exception-enabled RPCs */
				*restore_plast = rpc;
				restore_plast  = &rpc->pr_link.sle_next;
				result |= TASK_SERVE_NX_EXCEPT;
			} else {
				/* Enabling interrupts when RPCs get served is part of the ABI! */
				PREEMPTION_ENABLE();

				/* Execute synchronous kernel RPC immediately. */
				SLIST_INSERT_HEAD(&runnow, rpc, pr_link);
				result |= TASK_SERVE_NX_DIDRUN;
			}
		} else {
			/* user-level-, or inactive RPC (restore) */
			*restore_plast = rpc;
			restore_plast  = &rpc->pr_link.sle_next;
			if (!(rpc->pr_flags & _RPC_CONTEXT_INACTIVE)) {
				if (!(rpc->pr_flags & RPC_CONTEXT_KERN)) {
					/* NOTE: `sigmask_ismasked_chk_nopf()' returns one of:
					 *  - SIGMASK_ISMASKED_NOPF_YES:   Signal is masked
					 *  - SIGMASK_ISMASKED_NOPF_NO:    Signal isn't masked
					 *  - SIGMASK_ISMASKED_NOPF_FAULT: Unable to access userprocmask */
					int status = sigmask_ismasked_nopf(_RPC_GETSIGNO(rpc->pr_flags));
					if (status == SIGMASK_ISMASKED_NOPF_YES)
						continue; /* Signal is known to be masked! (so skip) */
				}
				/* In order to handle user-level RPCs, we need exceptions! */
				result |= TASK_SERVE_NX_EXCEPT;
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
		SLIST_REMOVE_HEAD(&runnow, pr_link);
		assert(rpc->pr_flags & RPC_CONTEXT_KERN);
		assert(!(rpc->pr_flags & RPC_SYNCMODE_F_USER));
		(*rpc->pr_kern.k_func)(&ctx, rpc->pr_kern.k_cookie);
		pending_rpc_free(rpc);
		assert(ctx.rc_context == RPC_REASONCTX_SYNC);
	}

	/* Unmasked process RPCs also require that we unwind the system call. */
	if (!(result & TASK_SERVE_NX_EXCEPT)) {
		if (are_any_unmasked_process_rpcs_maybe_pending_nx())
			result |= TASK_SERVE_NX_EXCEPT;
	}
	_task_serve_with_icpustate_nx_arch_set_return_uint(ctx.rc_state, result);
	return ctx.rc_state;
}



/* Schedule the given `rpc' for execution on `thread'.
 * NOTE: Be mindful of the scenario  where `thread == THIS_TASK', in which  case
 *       this function will return like normal, and the RPC will only be noticed
 *       the next time you make a call to `task_serve()'!
 * NOTE: The caller must initialize:
 *       - `rpc->pr_flags'
 *       - `rpc->pr_kern' or `rpc->pr_user'
 * @return: true:  Success. (Even if the thread terminates before the RPC can be served
 *                 normally, it will still  be served as `RPC_REASONCTX_SHUTDOWN'  when
 *                 true has been returned here)
 * @return: false: The target thread has already terminated. */
PUBLIC NOBLOCK WUNUSED NONNULL((1, 2)) bool
NOTHROW(FCALL task_rpc_schedule)(struct task *__restrict thread,
                                 /*inherit(on_success)*/ struct pending_rpc *__restrict rpc) {
	struct pending_rpc_slist *list;
	struct pending_rpc *head;
	uintptr_t rpc_flags = rpc->pr_flags;

	/* Insert into `thread's pending RPC list. */
	list = &FORTASK(thread, this_rpcs);
	do {
		head = ATOMIC_READ(list->slh_first);
		if unlikely(head == THIS_RPCS_TERMINATED)
			return false; /* Already terminated */
		rpc->pr_link.sle_next = head;
		COMPILER_BARRIER();
	} while (!ATOMIC_CMPXCH_WEAK(list->slh_first, head, rpc));

	if (rpc_flags & RPC_CONTEXT_KERN) {
		assertf(!(thread->t_flags & TASK_FKERNTHREAD) ||
		        !(rpc_flags & RPC_SYNCMODE_F_USER),
		        "Cannot schedule a RPC_SYNCMODE_F_USER RPC "
		        "for execution within a TASK_FKERNTHREAD thread");

		/* Set the thread's `TASK_FRPC' flag to indicate that it's got work to do */
		ATOMIC_OR(thread->t_flags, TASK_FRPC);

		/* Deal  with the case where `thread' is currently running in user-space,
		 * which requires us to temporarily move its execution into kernel-space,
		 * such that it executes `handle_sysret_rpc()'  the next time it  returns
		 * back to user-space.
		 *
		 * This is normally  done by `userexcept_sysret_inject_nopr()',  however
		 * that function only works correctly when the thread is being hosted by
		 * the same CPU as  the calling thread. But  there's also a wrapper  for
		 * that low-level function `userexcept_sysret_inject_safe()', which does
		 * the same thing, but also works then the thread hosted by another CPU. */
		userexcept_sysret_inject_safe(thread, rpc_flags);
	} else {
		assertf(!(thread->t_flags & TASK_FKERNTHREAD),
		        "Cannot schedule a non-RPC_CONTEXT_KERN RPC "
		        "for execution within a TASK_FKERNTHREAD thread");

		/* Because it's a user-level RPC, we only want to interrupt the thread if
		 * it isn't masking the  signal vector `_RPC_GETSIGNO(rpc_flags)'. If  it
		 * is currently masked, then  we also want to  mark it as pending  within
		 * the thread's userprocmask (if it's  using one). Finally, we only  want
		 * to wake the thread if the signal isn't masked, all of which is done by
		 * the following call.
		 *
		 * NOTE: The `TASK_FRPC' flag also gets set by this function (though only
		 *       if necessary) */
		userexcept_sysret_inject_and_marksignal_safe(thread, rpc_flags);
	}
	return true;
}



/* Execute a user-space RPC program
 * @param: reason:  One of `_RPC_REASONCTX_ASYNC', `_RPC_REASONCTX_SYNC' or `_RPC_REASONCTX_SYSCALL'
 * @param: sc_info: [valid_if(reason == _RPC_REASONCTX_SYSCALL)] System call information. */
PUBLIC ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) rpc_cpustate_t *FCALL
task_userrpc_runprogram(rpc_cpustate_t *__restrict state, struct pending_user_rpc const *__restrict rpc,
                        unsigned int reason, struct rpc_syscall_info const *sc_info) {
	/* TODO */
	return state;
}


DECL_END

#endif /* CONFIG_USE_NEW_RPC */

#endif /* !GUARD_KERNEL_SRC_SCHED_RPC_C */
