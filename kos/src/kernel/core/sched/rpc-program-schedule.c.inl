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
#ifdef __INTELLISENSE__
#define _KOS_SOURCE 1
#define DEFINE_sys_rpc_schedule
//#define DEFINE_compat_sys_rpc_schedule
#endif /* __INTELLISENSE__ */

#include <kernel/compiler.h>

#include <kernel/except.h>
#include <kernel/malloc.h>
#include <kernel/mman.h>
#include <kernel/rt/except-handler.h>
#include <kernel/rt/except-syscall.h> /* CONFIG_HAVE_USERPROCMASK */
#include <kernel/syscall.h>
#include <kernel/user.h>
#include <sched/group.h>
#include <sched/rpc-internal.h>
#include <sched/rpc.h>
#include <sched/sig.h>
#include <sched/sigmask.h>
#include <sched/task.h>

#include <hybrid/atomic.h>

#include <kos/except.h>
#include <kos/except/reason/inval.h>
#include <kos/kernel/cpu-state-helpers.h>
#include <kos/kernel/cpu-state.h>
#include <kos/rpc.h>

#include <assert.h>
#include <errno.h>
#include <signal.h>
#include <stddef.h>
#include <string.h>

#ifdef DEFINE_compat_sys_rpc_schedule
#include <compat/config.h>
#endif /* DEFINE_compat_sys_rpc_schedule */

DECL_BEGIN

#if (defined(DEFINE_sys_rpc_schedule) + \
     defined(DEFINE_compat_sys_rpc_schedule)) != 1
#error "Must #define exactly one of these"
#endif /* ... */

#ifdef DEFINE_compat_sys_rpc_schedule
#define LOCAL_validate_readable  compat_validate_readable
#define LOCAL_validate_readablem compat_validate_readablem
#define LOCAL_SIZEOF_POINTER     __ARCH_COMPAT_SIZEOF_POINTER
#else /* DEFINE_compat_sys_rpc_schedule */
#define LOCAL_validate_readable  validate_readable
#define LOCAL_validate_readablem validate_readablem
#define LOCAL_SIZEOF_POINTER     __SIZEOF_POINTER__
#endif /* !DEFINE_compat_sys_rpc_schedule */


#ifndef SIGMASK_ISMASKED_WITH_NESTING_DEFINED
#define SIGMASK_ISMASKED_WITH_NESTING_DEFINED
#ifdef CONFIG_HAVE_USERPROCMASK
PRIVATE ATTR_NOINLINE ATTR_PURE WUNUSED bool FCALL
sigmask_ismasked_with_nesting(signo_t signo) THROWS(E_SEGFAULT) {
	NESTED_EXCEPTION;
	return sigmask_ismasked(signo);
}
#else /* CONFIG_HAVE_USERPROCMASK */
#define sigmask_ismasked_with_nesting sigmask_ismasked
#endif /* !CONFIG_HAVE_USERPROCMASK */
#endif /* !SIGMASK_ISMASKED_WITH_NESTING_DEFINED */


#ifndef RPC_SCHEDULE_IN_THIS_TASK_DEFINED
#define RPC_SCHEDULE_IN_THIS_TASK_DEFINED
PRIVATE NONNULL((1)) void PRPC_EXEC_CALLBACK_CC
rpc_schedule_in_this_task_rpc(struct rpc_context *__restrict ctx, void *cookie) THROWS(...) {
	rpc_cpustate_t *newstate;
	REF struct pending_rpc *rpc = (REF struct pending_rpc *)cookie;
	FINALLY_DECREF_LIKELY(&rpc->pr_user); /* Always inherit the reference to the RPC */

	/* Check if we got here as the result of a system call. Anything else
	 * would mean that some other  RPC/posix-signal got delivered to  our
	 * thread, or that our thread  somehow got terminated (probably  also
	 * as a result of a posix-signal, or maybe some VIO memory access). */
	if (ctx->rc_context != RPC_REASONCTX_SYSCALL)
		return;

	/* Time to execute the RPC! */
	rpc->pr_user.pur_status = PENDING_USER_RPC_STATUS_PENDING;

	/* Have the original system call return with `-EOK'.
	 * This must be done _before_  executing the RPC program, so  that
	 * the program will see the correct register state during whatever
	 * it wants to do to transform our registers. */
	icpustate_setreturn(ctx->rc_state, -EOK);

	/* Errors thrown by this call are propagated as normal syscall errors. */
	newstate = task_userrpc_runprogram(ctx->rc_state, rpc,
	                                   _RPC_REASONCTX_SYSINT,
	                                   &ctx->rc_scinfo);
	assertf(newstate != NULL, "task_userrpc_runprogram() only returns NULL when the RPC "
	                          "got canceled. So the question is: who canceled it? Our RPC "
	                          "should only be visible to our own thread at this point!");
	ctx->rc_state = newstate;

	/* At  this point, the  system call has  completed. Indicate that fact
	 * so that the RPC won't try to restart the `rpc_schedule(2)' syscall. */
	ctx->rc_context = RPC_REASONCTX_SYSRET;
}

INTDEF NOBLOCK void /* From "misc/except-handler.c" */
NOTHROW(FCALL restore_pending_rpcs)(struct pending_rpc *restore);

PRIVATE ATTR_NORETURN NONNULL((1)) void FCALL
rpc_schedule_in_this_task(struct pending_rpc *__restrict rpc,
                          syscall_ulong_t mode)
		THROWS(E_INTERRUPT_USER_RPC) {
	/* Try to remove the RPC from the thread/process pending  list
	 * which it was originally added to. Since our caller  already
	 * marked it as `PENDING_USER_RPC_STATUS_CANCELED', anyone who
	 * may  come across  it within  the per-process  RPC list will
	 * simply discard+decref it  (which is the  same we're  trying
	 * to do, so if we don't find it in the per-proc list,  that's
	 * also OK) */
	if (mode & RPC_DOMAIN_F_PROC) {
		bool did_remove = true;
		struct process_pending_rpcs *rpcs;
		rpcs = &THIS_PROCESS_RPCS;
		process_pending_rpcs_write(rpcs);
		SLIST_TRYREMOVE(&rpcs->pc_sig_list, rpc, pr_link, { did_remove = false; });
		process_pending_rpcs_endwrite(rpcs);
		if unlikely(!did_remove) {
			/* Failed to remove -> Some other thread already came across it, but because
			 * we managed to set the RPC state to `PENDING_USER_RPC_STATUS_CANCELED', we
			 * also know that said other thread didn't manage to complete it! */
			if (isshared(&rpc->pr_user)) {
				/* Another thread (may be) executing  the RPC _right_ _now_, meaning  that
				 * we can't re-use the same RPC descriptor, since this one must have  it's
				 * status kept as `PENDING_USER_RPC_STATUS_CANCELED'. If we were to change
				 * that, then the other thread currently executing it might end up missing
				 * the memo on its cancellation.
				 *
				 * As such, our only option is to create a duplicate of the descriptor
				 * and let the original be lazily cleaned up. */
				struct pending_rpc *copy;
				size_t struct_size = offsetof(struct pending_rpc, pr_user.pur_argv) +
				                     rpc->pr_user.pur_argc * sizeof(USER UNCHECKED void *);
				if (struct_size < offsetafter(struct pending_rpc, pr_user.pur_error))
					struct_size = offsetafter(struct pending_rpc, pr_user.pur_error);
				copy = (struct pending_rpc *)pending_rpc_alloc(struct_size, GFP_NORMAL);
				memcpy(copy, rpc, struct_size);
				incref(copy->pr_user.pur_mman);
				copy->pr_user.pur_refcnt = 1;

				/* Continue working with the secondary copy. */
				rpc = copy;
			} else {
				/* Nothing else (except our caller; s.a. `FINALLY_DECREF(&rpc->pr_user);'
				 * within  `sys_rpc_schedule(2)' below) is  using the RPC,  so no need to
				 * copy it. */
				incref(&rpc->pr_user);
			}
		} else {
			/* Reference was inherited from `&rpcs->pc_sig_list' */
		}
	} else {
		/* The per-task RPC list is thread-private, so no-one should
		 * have been able to remove `rpc' from our's. */
		struct pending_rpc_slist *list = &PERTASK(this_rpcs);
		struct pending_rpc_slist pending;
		pending.slh_first = SLIST_ATOMIC_CLEAR(list);
		assert(!SLIST_EMPTY(&pending) &&
		       SLIST_FIRST(&pending) != THIS_RPCS_TERMINATED);
		SLIST_REMOVE(&pending, rpc, pr_link); /* Remove the RPC (and inherit reference) */
		restore_pending_rpcs(SLIST_FIRST(&pending));
		/*incref(&rpc->pr_user);*/ /* Already inherited from `&pending' */
	}

	/* At this point, the RPC can no longer be found in any of the pending lists,
	 * as well as that by  removing the RPC from pending  lists, it is no  longer
	 * visible to any other thread  (which it was for a  short period of time  in
	 * the case of `RPC_DOMAIN_F_PROC')
	 *
	 * As such, we can proceed to unwind  back to user-space via a custom  kernel
	 * RPC which then implements the special handling for self-directed, wait-for
	 * RPCs getting executed immediately. */
	TRY {
		task_rpc_exec(THIS_TASK, RPC_CONTEXT_KERN | RPC_SYNCMODE_F_USER,
		              &rpc_schedule_in_this_task_rpc, rpc);
	} EXCEPT {
		decref(&rpc->pr_user);
		RETHROW();
	}
	THROW(E_INTERRUPT_USER_RPC);
}
#endif /* !RPC_SCHEDULE_IN_THIS_TASK_DEFINED */


#ifdef DEFINE_compat_sys_rpc_schedule
DEFINE_COMPAT_SYSCALL5(errno_t, rpc_schedule,
                       pid_t, target_tid, syscall_ulong_t, mode,
                       USER UNCHECKED void const *, program,
                       __ARCH_COMPAT_PTR(USER UNCHECKED void const) USER UNCHECKED const *, params,
                       size_t, max_param_count)
#else /* DEFINE_compat_sys_rpc_schedule */
DEFINE_SYSCALL5(errno_t, rpc_schedule,
                pid_t, target_tid, syscall_ulong_t, mode,
                USER UNCHECKED void const *, program,
                USER UNCHECKED void const *USER UNCHECKED const *, params,
                size_t, max_param_count)
#endif /* !DEFINE_compat_sys_rpc_schedule */
{
	REF struct pending_rpc *rpc;
	bool is_caller_potential_target;
	VALIDATE_FLAGSET(mode,
	                 RPC_SIGNO_MASK | RPC_SYNCMODE_F_ALLOW_ASYNC |
	                 RPC_SYNCMODE_F_REQUIRE_SC | RPC_SYNCMODE_F_REQUIRE_CP |
	                 RPC_SYSRESTART_F_AUTO | RPC_PRIORITY_F_HIGH |
	                 RPC_DOMAIN_F_PROC | RPC_JOIN_F_ASYNC,
	                 E_INVALID_ARGUMENT_CONTEXT_RPC_SCHEDULE_MODE);
	if unlikely(max_param_count > RPC_PROG_PARAMS_MAX) {
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_RPC_SCHEDULE_TOO_MANY_PARAMS,
		      max_param_count);
	}

	/* Set the default signal number `SIGRPC' if none was specified. */
	if ((mode & RPC_SIGNO_MASK) == 0) {
		STATIC_ASSERT(SIGRPC != SIGKILL);
		STATIC_ASSERT(SIGRPC != SIGSTOP);
		mode |= RPC_SIGNO(SIGRPC);
	} else {
		signo_t signo = _RPC_GETSIGNO(mode);
		if unlikely(signo <= 0 || signo >= NSIG) {
			THROW(E_INVALID_ARGUMENT_BAD_VALUE,
			      E_INVALID_ARGUMENT_CONTEXT_BAD_SIGNO,
			      signo);
		} else if unlikely(signo == SIGKILL || signo == SIGSTOP) {
			/* We do not allow use of SIGKILL or SIGSTOP as underlying signal number for use
			 * with RPCs. Because these signals cannot be masked, associated RPCs also can't
			 * be masked. This in turn could lead to program crashes. e.g.:
			 *
			 * >> pid_t parent = gettid();
			 * >> pid_t child  = vfork();
			 * >> if (child == 0) {
			 * >>     rpc_exec(parent, RPC_SIGNO(SIGKILL) | RPC_SYNCMODE_ASYNC, &somefunc, NULL);
			 * >>     for (;;) {
			 * >>         dprintf(STDOUT_FILENO, "Idling...\n");
			 * >>         sched_yield();
			 * >>     }
			 * >> }
			 * This program would crash because the RPC forces the parent to stop waiting for
			 * the child to exec() or  exit(). -- Because of  this, the parent will  suddenly
			 * start using its stack again,  leading to 2 threads  now using the same  stack.
			 * The results are what you'd expect...
			 *
			 * You could argue that something like that might be intended, and that SIGKILL
			 * and SIGSTOP in the context of RPCs  can be thought of as NMIs  (non-maskable
			 * interrupts). And you'd be right, and they would in fact work just like that.
			 * But I really don't like the idea of this being how they work. Plus: NMIs are
			 * already a pain in  the a$$ when working  in kernel-space. -- And  user-space
			 * really shouldn't need to worry about something like that, too.
			 *
			 * So  to be safe, we simply disallow use  of these 2 signals in the context of
			 * RPCs. If you want some thread to handle your RPC immediately, you'll have to
			 * make sure that the  signal you're using isn't  masked by the target  thread.
			 * And if it is, your RPC will only be handled once it gets unmasked, and there
			 * isn't supposed to be any way around this restriction! */
			THROW(E_INVALID_ARGUMENT_BAD_VALUE,
			      E_INVALID_ARGUMENT_CONTEXT_RPC_SCHEDULE_ILLSIGNO,
			      signo);
		}
	}

	LOCAL_validate_readable(program, 1);
	LOCAL_validate_readablem(params, max_param_count, LOCAL_SIZEOF_POINTER);

	/* If  we intend to wait for the RPC program to complete, then we also
	 * check  for RPCs pending  within our own thread  before we'll end up
	 * doing the wait. This way, no RPC is ever scheduled on one side more
	 * than once in a  scenario where 2 threads  are sending RPCs to  each
	 * other. */
	if (!(mode & RPC_JOIN_F_ASYNC))
		task_serve();

	/* Allocate the new RPC controller. */
	{
		size_t struct_size = offsetof(struct pending_rpc, pr_user.pur_argv) +
		                     max_param_count * sizeof(USER UNCHECKED void *);
		if (struct_size < offsetafter(struct pending_rpc, pr_user.pur_error))
			struct_size = offsetafter(struct pending_rpc, pr_user.pur_error);
		rpc = (struct pending_rpc *)pending_rpc_alloc(struct_size, GFP_NORMAL);
	}

	/* Copy RPC arguments. */
	TRY {
#ifdef DEFINE_compat_sys_rpc_schedule
		size_t i;
		for (i = 0; i < max_param_count; ++i)
			rpc->pr_user.pur_argv[i] = params[i];
#else /* DEFINE_compat_sys_rpc_schedule */
		memcpy(rpc->pr_user.pur_argv, params,
		       max_param_count, sizeof(USER UNCHECKED void *));
#endif /* !DEFINE_compat_sys_rpc_schedule */
	} EXCEPT {
		pending_rpc_free(rpc);
		RETHROW();
	}

	/* Fill in RPC information. */
	rpc->pr_flags = mode & (RPC_SIGNO_MASK |
	                        RPC_SYNCMODE_F_ALLOW_ASYNC |
	                        RPC_SYNCMODE_F_REQUIRE_SC |
	                        RPC_SYNCMODE_F_REQUIRE_CP |
	                        RPC_SYSRESTART_F_AUTO |
	                        RPC_PRIORITY_F_HIGH);
	rpc->pr_user.pur_refcnt = 1;
	rpc->pr_user.pur_status = PENDING_USER_RPC_STATUS_PENDING;
	sig_init(&rpc->pr_user.pur_stchng);
	rpc->pr_user.pur_mman = incref(THIS_MMAN);
	rpc->pr_user.pur_prog = program;
	rpc->pr_user.pur_argc = max_param_count;
	FINALLY_DECREF(&rpc->pr_user);
	COMPILER_WRITE_BARRIER();

	{
		/* Lookup the target thread. */
		struct taskpid *mypid;
		REF struct taskpid *target;
		mypid  = task_gettaskpid();
		target = pidns_lookup_srch(mypid->tp_ns, target_tid);
		FINALLY_DECREF_UNLIKELY(target);

		/* Check if the calling thread is a potential target. */
		is_caller_potential_target = (target == mypid) ||
		                             ((mode & RPC_DOMAIN_F_PROC) &&
		                              taskpid_sameproc(target, mypid));

		/* Schedule the RPC */
		rpc->pr_user.pur_refcnt = 2; /* +1 for the target component's list. */
		COMPILER_WRITE_BARRIER();
		if (mode & RPC_DOMAIN_F_PROC) {
			if unlikely(!proc_rpc_schedule(target, rpc))
				goto err_target_exited;
		} else {
			REF struct task *target_thread;
			target_thread = taskpid_gettask(target);
			if unlikely(!target_thread) {
err_target_exited:
				rpc->pr_user.pur_refcnt = 1;
				COMPILER_WRITE_BARRIER();
				THROW(E_PROCESS_EXITED, target_tid);
			}
			FINALLY_DECREF_UNLIKELY(target_thread);
			if unlikely(!task_rpc_schedule(target_thread, rpc))
				goto err_target_exited;
		}
	}

	/* (possibly) wait for completion */
	if (!(mode & RPC_JOIN_F_ASYNC)) {
		uintptr_t status;
		for (;;) {
			status = ATOMIC_READ(rpc->pr_user.pur_status);
			if (status != PENDING_USER_RPC_STATUS_PENDING)
				break;
			task_connect(&rpc->pr_user.pur_stchng);
			status = ATOMIC_READ(rpc->pr_user.pur_status);
			if (status != PENDING_USER_RPC_STATUS_PENDING) {
				task_disconnectall();
				break;
			}
			TRY {
				task_waitfor();
			} EXCEPT {
				except_code_t code = except_code();

				/* Must  cancel the RPC  if we get  here, and, if that
				 * cancel can't be performed because the RPC finished,
				 * then we must discard the exception (unless it's  an
				 * RT-level error) */
				status = ATOMIC_XCH(rpc->pr_user.pur_status, PENDING_USER_RPC_STATUS_CANCELED);
				if (status != PENDING_USER_RPC_STATUS_COMPLETE) {
					if (status == PENDING_USER_RPC_STATUS_PENDING &&
					    code == EXCEPT_CODEOF(E_INTERRUPT_USER_RPC)) {
						/* Check for special case: The interrupt is the result of us trying
						 * to  send an RPC to ourselves (either  our own thread, or our own
						 * process; in the later case, we already know that no other thread
						 * within the process  will/is executing the  RPC, because we  were
						 * able to set its status to CANCELED) */
						if (is_caller_potential_target &&
						    !sigmask_ismasked_with_nesting(_RPC_GETSIGNO(mode))) {
							/* On most definitely! While the actual cause may have also been
							 * some other RPC, the one we just tried to schedule is just  as
							 * good of a reason, too!
							 *
							 * As such, the special handling for synchronous serving of RPCs
							 * kicks  in, which has us invoke the RPC program directly under
							 * a context of:
							 *   - rpc_syscall_info: Information about the rpc_schedule(2) syscall
							 *   - reason:           `_RPC_REASONCTX_SYSINT' (even though the
							 *                       syscall won't/doesn't fail with  -EINTR)
							 *   - return == 0:      rpc_schedule(2) returns with `0' */
							goto exec_rpc_in_THIS_TASK;
						}
					}
					RETHROW();
				}

				/* Ooops... The RPC completed before we could cancel it.
				 * Well: now we have to get rid of the current exception,
				 *       as  user-space mustn't be told about ?something?
				 *       having gone wrong.
				 * A special case here are  RT exception which are  too
				 * important to dismiss (as they include stuff like our
				 * own thread being supposed to terminate) */
				if (EXCEPTCLASS_ISRTLPRIORITY(EXCEPT_CLASS(code)))
					RETHROW(); /* Sorry. Can't discard this one... */

				/* If it was  just an `E_INTERRUPT_USER_RPC',  then we  can
				 * discard it by redirecting our sysret path (so that async
				 * RPCs/posix signals can  be handled  that way).  However,
				 * synchronous RPCs can't be handled anymore since we can't
				 * restart the system call at this point (as it  succeeded) */
				if (code == EXCEPT_CODEOF(E_INTERRUPT_USER_RPC)) {
					userexcept_sysret_inject_self();
				} else {
					/* Everything else is just dumped to the system log.
					 * But  note that there really shouldn't be anything
					 * that gets here... */
					except_printf("canceling user RPC");
				}
				break;
			}
		}

		/* Check if the program managed to complete successfully. */
		if (status != PENDING_USER_RPC_STATUS_COMPLETE) {
			struct exception_data *tls;
			assert(status == PENDING_USER_RPC_STATUS_CANCELED ||
			       status == PENDING_USER_RPC_STATUS_ERROR);

			/* The RPC was canceled, but it wasn't us. This can only mean that
			 * the  target thread/process exited and will no longer be able to
			 * service _any_ rpcs at all! */
			if (status == PENDING_USER_RPC_STATUS_CANCELED)
				THROW(E_PROCESS_EXITED, target_tid);

			/* Rethrow the exception that brought down the RPC VM */
			tls = except_data();
			tls->e_code      = rpc->pr_user.pur_error.e_code;
			tls->e_faultaddr = NULL; /* ??? */
			memcpy(&tls->e_args, &rpc->pr_user.pur_error.e_args,
			       sizeof(union exception_data_pointers));
			except_throw_current();
		}
	}

	return -EOK;
exec_rpc_in_THIS_TASK:
	rpc_schedule_in_this_task(rpc, mode);
}

#undef LOCAL_validate_readablem
#undef LOCAL_validate_readable
#undef LOCAL_SIZEOF_POINTER

DECL_END

#undef DEFINE_compat_sys_rpc_schedule
#undef DEFINE_sys_rpc_schedule
