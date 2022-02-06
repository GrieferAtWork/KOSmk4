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
#ifndef GUARD_KERNEL_SRC_SCHED_RPC_C
#define GUARD_KERNEL_SRC_SCHED_RPC_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/except.h>
#include <kernel/rt/except-handler.h>
#include <kernel/types.h>
#include <sched/group.h>
#include <sched/posix-signal.h>
#include <sched/rpc-internal.h>
#include <sched/rpc.h>
#include <sched/task.h>

#include <hybrid/atomic.h>

#include <kos/except.h>
#include <kos/kernel/cpu-state-helpers.h>
#include <kos/kernel/cpu-state.h>

#include <assert.h>
#include <inttypes.h>
#include <stdalign.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

#include <libcpustate/apply.h>

DECL_BEGIN

#if !defined(NDEBUG) && !defined(NDEBUG_FINI)
#define DBG_memset memset
#else /* !NDEBUG && !NDEBUG_FINI */
#define DBG_memset(...) (void)0
#endif /* NDEBUG || NDEBUG_FINI */

/* [0..n][lock(INSERT(ATOMIC), CLEAR(ATOMIC && THIS_TASK))]
 * Pending RPCs. (Set of `THIS_RPCS_TERMINATED' when RPCs may no longer
 * be executed, and all that were there prior to this becoming the case
 * are/were serviced with `RPC_REASONCTX_SHUTDOWN') */
PUBLIC ATTR_PERTASK struct pending_rpc_slist this_rpcs = SLIST_HEAD_INITIALIZER(this_rpcs);

/* A  signal that is broadcast whenever something is added to `this_rpcs'
 * This signal is _only_ used  to implement `signalfd(2)', as you're  not
 * normally supposed to "wait" for signals to arrive; you just always get
 * a sporadic interrupt once they do arrive. */
PUBLIC ATTR_PERTASK struct sig this_rpcs_sig = SIG_INIT;

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
PUBLIC NONNULL((1, 3)) bool KCALL
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
		/* TODO: Async RPCs are scheduled entirely different from regular ones:
		 *        - Send IPI to correct CPU
		 *        - Update scpustate of target thread via `task_asyncrpc_push()',
		 *          unless target is THIS_TASK,  where invocation is either  done
		 *          with  IPI-icpustate,  or via  `task_asyncrpc_execnow()' (when
		 *          no  IPI had to  be used because the  target CPU didn't differ
		 *          from that of the original sender) */
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
	sig_broadcast(&FORTASK(thread, this_rpcs_sig));

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
		STATIC_ASSERT(RPC_PRIORITY_F_HIGH == TASK_WAKE_FHIGHPRIO);
		return task_wake(thread, flags);
	} else {
		userexcept_sysret_inject_safe(thread, flags);
	}

	return true;
}


/* Helper wrapper for executing the given RPC `func' after
 * unwind the current system  call. This is identical  to:
 * >> task_rpc_exec(THIS_TASK, RPC_CONTEXT_KERN | RPC_SYNCMODE_F_USER, func, cookie);
 * >> THROW(E_INTERRUPT_USER_RPC); */
PUBLIC ABNORMAL_RETURN ATTR_NORETURN NONNULL((1)) void KCALL
task_rpc_userunwind(prpc_exec_callback_t func, void *cookie)
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_INTERRUPT_USER_RPC) {
#ifdef NDEBUG
	task_rpc_userunwind(func, cookie);
#else /* NDEBUG */
	bool ok = task_rpc_exec(THIS_TASK, RPC_CONTEXT_KERN | RPC_SYNCMODE_F_USER, func, cookie);
	assertf(ok, "This would mean you're calling from within `task_exit()'; don't do that!");
#endif /* !NDEBUG */
	THROW(E_INTERRUPT_USER_RPC);
}



/* Trigger RPC completion for `self' with context `RPC_REASONCTX_SHUTDOWN' */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL task_asyncrpc_destroy_for_shutdown)(struct pending_rpc *__restrict self) {
	if (self->pr_flags & RPC_CONTEXT_KERN) {
		/* Invoke kernel RPC in RPC_REASONCTX_SHUTDOWN-context */
		alignas(alignof(struct rpc_context))
		byte_t _ctxbuf[offsetof(struct rpc_context, rc_scinfo)];
		struct rpc_context *ctx = (struct rpc_context *)_ctxbuf;
		uintptr_t rpc_flags = self->pr_flags;
		TRY {
			void *cookie = self;
			if (!(rpc_flags &_RPC_CONTEXT_DONTFREE))
				cookie = self->pr_kern.k_cookie;
			ctx->rc_context = RPC_REASONCTX_SHUTDOWN;
			task_asyncrpc_execnow(ctx, self->pr_kern.k_func, cookie);
		} EXCEPT {
			/* Dump the exception if it is non-signaling */
			except_printf("Unhandled exception in RPC function during thread termination");
		}
		if (!(rpc_flags & _RPC_CONTEXT_DONTFREE))
			pending_rpc_free(self);
	} else if (self->pr_flags & RPC_CONTEXT_SIGNAL) {
		pending_rpc_free(self);
	} else {
		/* Mark a user RPC program as canceled. */
		task_userrpc_cancelprogram(self);
		decref(&self->pr_user);
	}
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





PRIVATE ABNORMAL_RETURN ATTR_NORETURN NONNULL((1)) void
NOTHROW(FCALL unwind_current_exception_at_icpustate)(struct icpustate *__restrict state) {
	struct kcpustate kst;
	struct kcpustate *newstate;
	icpustate_to_kcpustate(state, &kst);
	newstate = except_unwind(&kst);
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
		THROWS(E_SEGFAULT, E_WOULDBLOCK) {
	struct pending_rpc *rpc;
	sigset_t known_masked, known_unmasked;
	sigemptyset(&known_masked);
	sigemptyset(&known_unmasked);
again_test_signo:
	/* NOTE: This `sigmask_ismasked()' is the only thing in here that might throw! */
	sigaddset(sigmask_ismasked(signo) ? &known_masked
	                                  : &known_unmasked,
	          signo);
	if unlikely(ATOMIC_READ(proc_rpcs->ppr_list.slh_first) == NULL)
		return false;
	process_pending_rpcs_read(proc_rpcs);
	SLIST_FOREACH (rpc, &proc_rpcs->ppr_list, pr_link) {
		int status;
		signo = _RPC_GETSIGNO(rpc->pr_flags);
		if (sigismember(&known_masked, signo))
			continue; /* Known-masked signal */
		if (sigismember(&known_unmasked, signo)) {
			/* TODO: If it's a POSIX signal RPC, check if our thread's sighand
			 *       disposition  indicates that the signal should be ignored.
			 *       If so, consume and discard the associated RPC! */
			process_pending_rpcs_endread(proc_rpcs);
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
			process_pending_rpcs_endread(proc_rpcs);
			goto again_test_signo;
		}
		/* TODO: If it's a POSIX signal RPC, check if our thread's sighand
		 *       disposition  indicates that the signal should be ignored.
		 *       If so, consume and discard the associated RPC! */
		process_pending_rpcs_endread(proc_rpcs);
		return true;
	}
	process_pending_rpcs_endread(proc_rpcs);
	return false;
}
#endif /* CONFIG_HAVE_USERPROCMASK */


/* Check if there are any unmasked process RPCs that are currently pending. */
PRIVATE WUNUSED bool FCALL
are_any_unmasked_process_rpcs_pending(void)
#ifdef CONFIG_HAVE_USERPROCMASK
		THROWS(E_WOULDBLOCK, E_SEGFAULT)
#else /* CONFIG_HAVE_USERPROCMASK */
		THROWS(E_WOULDBLOCK)
#endif /* !CONFIG_HAVE_USERPROCMASK */
{
	struct pending_rpc *rpc;
	struct process_pending_rpcs *proc_rpcs = &THIS_PROCESS_RPCS;
	if (ATOMIC_READ(proc_rpcs->ppr_list.slh_first) == NULL)
		return false;
	process_pending_rpcs_read(proc_rpcs);
	SLIST_FOREACH (rpc, &proc_rpcs->ppr_list, pr_link) {
		int status;
		status = sigmask_ismasked_nopf(_RPC_GETSIGNO(rpc->pr_flags));
		if (status == SIGMASK_ISMASKED_NOPF_YES)
			continue;
#ifdef CONFIG_HAVE_USERPROCMASK
		if (status == SIGMASK_ISMASKED_NOPF_FAULT) {
			signo_t signo = _RPC_GETSIGNO(rpc->pr_flags);
			process_pending_rpcs_endread(proc_rpcs);
			return are_any_unmasked_process_rpcs_pending_with_faulty(proc_rpcs, signo);
		}
		process_pending_rpcs_endread(proc_rpcs);
#else /* CONFIG_HAVE_USERPROCMASK */
		process_pending_rpcs_endread(proc_rpcs);
#endif /* !CONFIG_HAVE_USERPROCMASK */
		/* TODO: If it's a POSIX signal RPC, check if our thread's sighand
		 *       disposition  indicates that the signal should be ignored.
		 *       If so, consume and discard the associated RPC! */
		return true;
	}
	process_pending_rpcs_endread(proc_rpcs);
	return false;
}

/* Check if there are any unmasked process RPCs that are currently pending. */
PRIVATE WUNUSED NONNULL((1)) bool FCALL
are_any_unmasked_process_rpcs_pending_with_sigmask(sigset_t const *__restrict sigmask)
		THROWS(E_WOULDBLOCK) {
	struct pending_rpc *rpc;
	struct process_pending_rpcs *proc_rpcs = &THIS_PROCESS_RPCS;
	if (ATOMIC_READ(proc_rpcs->ppr_list.slh_first) == NULL)
		return false;
	process_pending_rpcs_read(proc_rpcs);
	SLIST_FOREACH (rpc, &proc_rpcs->ppr_list, pr_link) {
		if (sigismember(sigmask, _RPC_GETSIGNO(rpc->pr_flags)))
			continue;
		process_pending_rpcs_endread(proc_rpcs);
		/* TODO: If it's a POSIX signal RPC, check if our thread's sighand
		 *       disposition  indicates that the signal should be ignored.
		 *       If so, consume and discard the associated RPC! */
		return true;
	}
	process_pending_rpcs_endread(proc_rpcs);
	return false;
}

/* Same as `are_any_unmasked_process_rpcs_pending()', but use *_nopf memory
 * access, and if that fails, assume that pending RPCs are always unmasked. */
PRIVATE WUNUSED bool
NOTHROW(FCALL are_any_unmasked_process_rpcs_maybe_pending_nx)(void) {
	struct pending_rpc *rpc;
	struct process_pending_rpcs *proc_rpcs = &THIS_PROCESS_RPCS;
	if (ATOMIC_READ(proc_rpcs->ppr_list.slh_first) == NULL)
		return false;
	if (!process_pending_rpcs_tryread(proc_rpcs))
		return true; /* Must assume that at least one of them would be unmasked in our thread. */
	SLIST_FOREACH (rpc, &proc_rpcs->ppr_list, pr_link) {
		int status;
		status = sigmask_ismasked_nopf(_RPC_GETSIGNO(rpc->pr_flags));
		if (status == SIGMASK_ISMASKED_NOPF_YES)
			continue;
		/* Either the signal number isn't masked, or the status can't be determined.
		 * In any case, we're supposed to act like it isn't masked, since our caller
		 * asked weather there **may** be unmasked process RPCs. */
		process_pending_rpcs_endread(proc_rpcs);
		return true;
	}
	process_pending_rpcs_endread(proc_rpcs);
	return false;
}

/* Define high-level implementations for `task_serve()' */
#ifndef __INTELLISENSE__
DECL_END

#define DEFINE_task_serve_with_icpustate
#include "rpc-task_serve.c.inl"
#define DEFINE_task_serve_with_icpustate_nx
#include "rpc-task_serve.c.inl"
#define DEFINE_task_serve_with_icpustate_and_sigmask
#include "rpc-task_serve.c.inl"

DECL_BEGIN
#endif /* !__INTELLISENSE__ */


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
		if unlikely(head == THIS_RPCS_TERMINATED) {
			DBG_memset(&rpc->pr_link, 0xcc, sizeof(rpc->pr_link));
			return false; /* Already terminated */
		}
		rpc->pr_link.sle_next = head;
		COMPILER_BARRIER();
	} while (!ATOMIC_CMPXCH_WEAK(list->slh_first, head, rpc));
	sig_broadcast(&FORTASK(thread, this_rpcs_sig));

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
		 * the  same thing, but also works then  the thread is hosted by another
		 * CPU. */
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


#ifdef CONFIG_USE_NEW_GROUP
/* Same as `task_rpc_schedule()', but schedule the RPC for execution
 * by some arbitrary thread apart of the process `proc->tp_pctl'.
 * NOTE: Process-directed user-RPCs must not make use of `RPC_SYNCMODE_F_REQUIRE_SC'
 *       or `RPC_SYNCMODE_F_REQUIRE_CP'. Attempting to do so causes this function to
 *       trigger an internal assertion check.
 *       All other RPC functionality works as expected, though obviously  RPCs
 * NOTE: The caller must be holding a read-lock to `proc->tp_pctl->pc_chlds_lock'
 * @return: true:  Success. (Even if the process terminates before the RPC can be served
 *                 normally, it will  still be served  as `RPC_REASONCTX_SHUTDOWN'  when
 *                 true has been returned here)
 * @return: false: The target process was marked as having terminated. */
PUBLIC NOBLOCK WUNUSED NONNULL((1, 2)) bool
NOTHROW(FCALL proc_rpc_schedule)(struct taskpid *__restrict proc,
                                 /*inherit(on_success)*/ struct pending_rpc *__restrict rpc) {
	uintptr_t rpc_flags = rpc->pr_flags;
	struct procctl *ctl = proc->tp_pctl;
	struct pending_rpc *head;

	/* Insert into the process's pending RPC list. */
	do {
		head = ATOMIC_READ(ctl->pc_sig_list.slh_first);
		if unlikely(head == THIS_RPCS_TERMINATED) {
			DBG_memset(&rpc->pr_link, 0xcc, sizeof(rpc->pr_link));
			return false; /* Already terminated */
		}
		rpc->pr_link.sle_next = head;
		COMPILER_BARRIER();
	} while (!ATOMIC_CMPXCH_WEAK(ctl->pc_sig_list.slh_first, head, rpc));
	sig_broadcast(&ctl->pc_sig_more);

	/* Wake-up threads within the process. */
	if unlikely(rpc_flags & RPC_CONTEXT_KERN) {
		userexcept_sysret_injectproc_safe(proc, rpc_flags);
	} else {
		assertf(!(rpc_flags & RPC_SYNCMODE_F_REQUIRE_SC),
		        "Flag `RPC_SYNCMODE_F_REQUIRE_SC' cannot be used for user-space process RPCs");
		assertf(!(rpc_flags & RPC_SYNCMODE_F_REQUIRE_CP),
		        "Flag `RPC_SYNCMODE_F_REQUIRE_CP' cannot be used for user-space process RPCs");
		userexcept_sysret_injectproc_and_marksignal_safe(proc, rpc_flags);
	}
	return true;
}
#else /* CONFIG_USE_NEW_GROUP */
/* Same as `task_rpc_schedule()', but schedule the RPC for execution by
 * some arbitrary thread apart of the same process as `thread_in_proc'.
 * NOTE: Process-directed user-RPCs must not make use of `RPC_SYNCMODE_F_REQUIRE_SC'
 *       or `RPC_SYNCMODE_F_REQUIRE_CP'. Attempting to do so causes this function to
 *       trigger an internal assertion check.
 *       All other RPC functionality works as expected, though obviously  RPCs
 *       will be served by some arbitrary thread within the specified process.
 * @return: true:  Success. (Even if the process terminates before the RPC can be served
 *                 normally, it will  still be served  as `RPC_REASONCTX_SHUTDOWN'  when
 *                 true has been returned here)
 * @return: false: The target process was marked as having terminated. */
PUBLIC NOBLOCK WUNUSED NONNULL((1, 2)) bool
NOTHROW(FCALL proc_rpc_schedule)(struct task *__restrict thread_in_proc,
                                 /*inherit(on_success)*/ struct pending_rpc *__restrict rpc) {
	uintptr_t rpc_flags = rpc->pr_flags;
	struct pending_rpc_slist *list;
	struct pending_rpc *head;
	struct task *proc;
	proc = task_getprocess_of(thread_in_proc);

	/* Insert into the process's pending RPC list. */
	list = &FORTASK(proc, this_taskgroup.tg_proc_rpcs.ppr_list);
	do {
		head = ATOMIC_READ(list->slh_first);
		if unlikely(head == THIS_RPCS_TERMINATED) {
			DBG_memset(&rpc->pr_link, 0xcc, sizeof(rpc->pr_link));
			return false; /* Already terminated */
		}
		rpc->pr_link.sle_next = head;
		COMPILER_BARRIER();
	} while (!ATOMIC_CMPXCH_WEAK(list->slh_first, head, rpc));
	sig_broadcast(&FORTASK(proc, this_taskgroup.tg_proc_rpcs.ppr_more));

	if unlikely(rpc_flags & RPC_CONTEXT_KERN) {
		assertf(!(proc->t_flags & TASK_FKERNTHREAD) ||
		        !(rpc_flags & RPC_SYNCMODE_F_USER),
		        "Cannot schedule a RPC_SYNCMODE_F_USER RPC "
		        "for execution within a TASK_FKERNTHREAD thread");
		userexcept_sysret_injectproc_safe(proc, rpc_flags);
	} else {
		assertf(!(rpc_flags & RPC_SYNCMODE_F_REQUIRE_SC),
		        "Flag `RPC_SYNCMODE_F_REQUIRE_SC' cannot be used for user-space process RPCs");
		assertf(!(rpc_flags & RPC_SYNCMODE_F_REQUIRE_CP),
		        "Flag `RPC_SYNCMODE_F_REQUIRE_CP' cannot be used for user-space process RPCs");
		assertf(!(proc->t_flags & TASK_FKERNTHREAD),
		        "Cannot schedule a non-RPC_CONTEXT_KERN RPC "
		        "for execution within a TASK_FKERNTHREAD thread");
		userexcept_sysret_injectproc_and_marksignal_safe(proc, rpc_flags);
	}
	return true;
}
#endif /* !CONFIG_USE_NEW_GROUP */



PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL pending_signals_from_rpc_list)(/*in|out*/ sigset_t *__restrict result,
                                             struct pending_rpc *first) {
	for (; first; first = SLIST_NEXT(first, pr_link)) {
		if (!(first->pr_flags & RPC_CONTEXT_KERN))
			sigaddset(result, _RPC_GETSIGNO(first->pr_flags));
	}
}


/* Gather the set of posix signal numbers used by pending RPCs
 * of calling thread or process.  These functions are used  to
 * implement the `sigpending(2)' system call.
 *
 * NOTE: These functions don't `sigemptyset(result)' beforehand,
 *       but  will blindly `sigaddset()'  all pending signals to
 *       it. */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL task_rpc_pending_sigset)(/*in|out*/ sigset_t *__restrict result) {
	struct pending_rpc *list;
	list = PERTASK_GET(this_rpcs.slh_first);
	assert(list != THIS_RPCS_TERMINATED);
	pending_signals_from_rpc_list(result, list);
}

PUBLIC NONNULL((1)) void FCALL
proc_rpc_pending_sigset(/*in|out*/ sigset_t *__restrict result)
		THROWS(E_WOULDBLOCK) {
	struct process_pending_rpcs *proc_rpcs;
	struct pending_rpc *first;
	proc_rpcs = &THIS_PROCESS_RPCS;
	process_pending_rpcs_read(proc_rpcs);
	first = SLIST_FIRST(&proc_rpcs->ppr_list);
	if (first != THIS_RPCS_TERMINATED)
		pending_signals_from_rpc_list(result, first);
	process_pending_rpcs_endread(proc_rpcs);
}



/* Check if one of `these' is pending. */
PRIVATE NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) bool
NOTHROW(FCALL is_one_of_these_pending)(sigset_t const *__restrict these,
                                       struct pending_rpc const *first) {
	for (; first; first = SLIST_NEXT(first, pr_link)) {
		if (!(first->pr_flags & RPC_CONTEXT_KERN) &&
		    sigismember(these, _RPC_GETSIGNO(first->pr_flags)))
			return true;
	}
	return false;
}

/* Check if an RPCs routed via one of `these' signals is pending. */
PUBLIC NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) bool
NOTHROW(FCALL task_rpc_pending_oneof)(sigset_t const *__restrict these) {
	struct pending_rpc const *list;
	list = PERTASK_GET(this_rpcs.slh_first);
	assert(list != THIS_RPCS_TERMINATED);
	return is_one_of_these_pending(these, list);
}

PUBLIC ATTR_PURE WUNUSED NONNULL((1)) bool FCALL
proc_rpc_pending_oneof(sigset_t const *__restrict these)
		THROWS(E_WOULDBLOCK) {
	bool result = false;
	struct process_pending_rpcs *proc_rpcs;
	struct pending_rpc *first;
	proc_rpcs = &THIS_PROCESS_RPCS;
	process_pending_rpcs_read(proc_rpcs);
	first = SLIST_FIRST(&proc_rpcs->ppr_list);
	if (first != THIS_RPCS_TERMINATED)
		result = is_one_of_these_pending(these, first);
	process_pending_rpcs_endread(proc_rpcs);
	return result;
}

/* @return: * : One of `PROC_RPC_TRYPENDING_ONEOF_*' */
PUBLIC NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) int
NOTHROW(FCALL proc_rpc_trypending_oneof)(sigset_t const *__restrict these) {
	int result = PROC_RPC_TRYPENDING_ONEOF_NO;
	struct process_pending_rpcs *proc_rpcs;
	struct pending_rpc *first;
	proc_rpcs = &THIS_PROCESS_RPCS;
	if (!process_pending_rpcs_tryread(proc_rpcs))
		return PROC_RPC_TRYPENDING_ONEOF_WOULDBLOCK;
	first = SLIST_FIRST(&proc_rpcs->ppr_list);
	if (first != THIS_RPCS_TERMINATED) {
		STATIC_ASSERT(PROC_RPC_TRYPENDING_ONEOF_NO == (int)false);
		STATIC_ASSERT(PROC_RPC_TRYPENDING_ONEOF_YES == (int)true);
		result = (int)is_one_of_these_pending(these, first);
	}
	process_pending_rpcs_endread(proc_rpcs);
	return result;
}




/* Try to steal a posix signal RPC from `list' who's signal bit is `1' in `these'
 * If no such pending  RPC exists, return `NULL';  else return the stolen  entry. */
PRIVATE NOBLOCK WUNUSED NONNULL((1, 2)) struct pending_rpc *
NOTHROW(FCALL steal_posix_signal)(struct pending_rpc_slist *__restrict list,
                                  sigset_t const *__restrict these) {
	struct pending_rpc **p_rpc, *rpc;
again:
	p_rpc = SLIST_PFIRST(list);
	while ((rpc = *p_rpc) != NULL) {
		if ((rpc->pr_flags & (RPC_CONTEXT_KERN | RPC_CONTEXT_SIGNAL)) == RPC_CONTEXT_SIGNAL &&
		    sigismember(these, _RPC_GETSIGNO(rpc->pr_flags))) {
			/* Found one! */
#ifndef __OPTIMIZE_SIZE__
			if (p_rpc != SLIST_PFIRST(list)) {
				assert(*p_rpc == rpc);
				*p_rpc = rpc->pr_link.sle_next;
			} else
#endif /* !__OPTIMIZE_SIZE__ */
			{
				/* Need atomics for the first list entry. */
				if (!ATOMIC_CMPXCH(*p_rpc, rpc, rpc->pr_link.sle_next))
					goto again;
			}
			return rpc;
		}
		p_rpc = &rpc->pr_link.sle_next;
	}
	return NULL;
}

/* Steal pending RPC (that must be a posix signal) with uses a
 * signal number that is a member of `these'. When no such RPC
 * exists, return `NULL' */
PUBLIC NOBLOCK WUNUSED NONNULL((1)) /*inherit*/ struct pending_rpc *
NOTHROW(FCALL task_rpc_pending_steal_posix_signal)(sigset_t const *__restrict these) {
	struct pending_rpc_slist *mylist = &PERTASK(this_rpcs);
	return steal_posix_signal(mylist, these);
}

PUBLIC WUNUSED NONNULL((1)) /*inherit*/ struct pending_rpc *FCALL
proc_rpc_pending_steal_posix_signal(sigset_t const *__restrict these)
		THROWS(E_WOULDBLOCK) {
	struct pending_rpc *result;
	struct process_pending_rpcs *proc_rpcs;
	proc_rpcs = &THIS_PROCESS_RPCS;
	result = ATOMIC_READ(proc_rpcs->ppr_list.slh_first);
	if (result == NULL || result == THIS_RPCS_TERMINATED)
		return NULL;
	/* XXX: Implement via read-lock + update */
	process_pending_rpcs_write(proc_rpcs);
	result = steal_posix_signal(&proc_rpcs->ppr_list, these);
	process_pending_rpcs_endwrite(proc_rpcs);
	return result;
}

/* Same  as `proc_rpc_pending_steal_posix_signal()', but only _try_ to
 * acquire the  necessary lock  to `THIS_PROCESS_RPCS.ppr_lock'.  When
 * doing so fails, `PROC_RPC_PENDING_TRYSTEAL_POSIX_SIGNAL_WOULDBLOCK'
 * is returned. */
PUBLIC NOBLOCK WUNUSED NONNULL((1)) /*inherit*/ struct pending_rpc *
NOTHROW(FCALL proc_rpc_pending_trysteal_posix_signal)(sigset_t const *__restrict these) {
	struct pending_rpc *result;
	struct process_pending_rpcs *proc_rpcs;
	proc_rpcs = &THIS_PROCESS_RPCS;
	result = ATOMIC_READ(proc_rpcs->ppr_list.slh_first);
	if (result == NULL || result == THIS_RPCS_TERMINATED)
		return NULL;
	/* XXX: Implement via read-lock + update */
	if (!process_pending_rpcs_trywrite(proc_rpcs))
		return PROC_RPC_PENDING_TRYSTEAL_POSIX_SIGNAL_WOULDBLOCK;
	result = steal_posix_signal(&proc_rpcs->ppr_list, these);
	process_pending_rpcs_endwrite(proc_rpcs);
	return result;
}

DECL_END

#endif /* !GUARD_KERNEL_SRC_SCHED_RPC_C */
