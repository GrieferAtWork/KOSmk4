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
#ifndef GUARD_KERNEL_SRC_SCHED_TASK_EXIT_C
#define GUARD_KERNEL_SRC_SCHED_TASK_EXIT_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <dev/tty.h>
#include <kernel/debugtrap.h>
#include <kernel/except.h>
#include <kernel/fpu.h>
#include <kernel/mman/mfile.h>
#include <kernel/mman/mpartmeta.h>
#include <kernel/panic.h>
#include <kernel/printk.h>
#include <kernel/rt/except-syscall.h> /* CONFIG_HAVE_KERNEL_USERPROCMASK */
#include <sched/cpu.h>
#include <sched/group.h>
#include <sched/pertask.h>
#include <sched/pid.h>
#include <sched/rpc-internal.h>
#include <sched/scheduler.h>
#include <sched/sig.h>
#include <sched/task.h>

#include <hybrid/sequence/list.h>

#include <kos/aref.h>
#include <kos/bits/userprocmask.h>
#include <kos/debugtrap.h>
#include <kos/except.h>
#include <kos/kernel/cpu-state.h>
#include <kos/rpc.h>
#include <kos/types.h>
#include <sys/wait.h>

#include <assert.h>
#include <atomic.h>
#include <stdalign.h>
#include <stddef.h>

DECL_BEGIN

PRIVATE NOBLOCK NONNULL((1, 2)) void
NOTHROW(PRPC_EXEC_CALLBACK_CC task_decref_for_exit_rpc)(struct rpc_context *__restrict UNUSED(ctx),
                                                        void *cookie) {
	decref((struct task *)cookie);
}

PRIVATE NOBLOCK NONNULL((1, 2)) void
NOTHROW(PRPC_EXEC_CALLBACK_CC taskpid_destroy_rpc)(struct rpc_context *__restrict UNUSED(ctx),
                                                   void *cookie) {
	taskpid_destroy((struct taskpid *)cookie);
}

PRIVATE ATTR_KERNEL_PANIC_NORETURN ATTR_COLD ATTR_NOINLINE NONNULL((1)) void
NOTHROW(FCALL panic_critical_thread_exited)(struct task *__restrict caller) {
	kernel_panic("Critical thread at %p has exited", caller);
}


PRIVATE NONNULL((1)) void
NOTHROW(FCALL maybe_clear_tid_address)(struct task *__restrict caller) {
	NCX pid_t *addr;
	addr = FORTASK(caller, this_tid_address);
	if (addr == NULL)
		return;
	TRY {
		/* Special case for vfork when the kernel supports userprocmask. */
#ifdef CONFIG_HAVE_KERNEL_USERPROCMASK
		uintptr_t my_flags = PERTASK_GET(this_task.t_flags);
		if (my_flags & TASK_FVFORK) {
			if unlikely(my_flags & TASK_FUSERPROCMASK_AFTER_VFORK) {
				NCX struct userprocmask *um;
				um = (NCX struct userprocmask *)addr;
				/* Handle the special case of a vfork()'d thread having
				 * initialized their parent thread's userprocmask  data
				 * structure.
				 * This  is  needed  because  userprocmask  is  part  of   a
				 * thread's  user-space  TLS  state,  which  itself  is part
				 * of that process's VM, which  is the very thing that  gets
				 * shared  during a  call to  vfork(), meaning  that we must
				 * uninitialize it if it wasn't the parent who did the init! */
				atomic_write(&um->pm_sigmask, NULL);
			}
			return;
		}
#endif /* CONFIG_HAVE_KERNEL_USERPROCMASK */
		write_once(addr, 0);
		mman_broadcastfutex(addr);
	} EXCEPT {
		if (was_thrown(E_SEGFAULT) &&
		    PERTASK_EQ(this_exception_args.e_segfault.s_addr, (uintptr_t)addr)) {
			/* Explicitly handle E_SEGFAULT:addr as a no-op */
		} else {
			/* We  can't RETHROW() the  exception since our function
			 * has to be NOTHROW() (especially so since we're called
			 * as part of thread cleanup)
			 * Because of this, dump all other errors that happen here. */
			except_printf("Broadcasting tid_address=%p", addr);
		}
	}
}

/* Finalizer for thread RPCs (called during `task_exit()') */
PRIVATE NONNULL((1)) void
NOTHROW(FCALL terminate_pending_rpcs)(struct task *__restrict caller) {
	struct pending_rpc *remain;

	/* Mark the RPC list as terminated and load remaining RPCs. */
	remain = atomic_xch(&FORTASK(caller, this_rpcs.slh_first),
	                    THIS_RPCS_TERMINATED);
	atomic_or(&FORTASK(caller, this_rpcs_sigpend), 1);
	assertf(remain != THIS_RPCS_TERMINATED,
	        "We're the only ones that ever set this, "
	        "so what; did we get called twice?");
	sig_broadcast_for_fini(&FORTASK(caller, this_rpcs_sig));

	/* Destroy all remaining RPCs for the purpose of shutdown. */
	task_asyncrpc_destroy_list_for_shutdown(remain);
}


/* [valid_if(!taskpid_isaprocess(THIS_TASKPID))]
 * Buffer used for holding a mini-RPC that can be used to propagate
 * exit  commands from non-main threads to the main thread, as well
 * as the main thread to all non-main threads. */
PRIVATE ATTR_SECTION(".data.pertask.middle")
ATTR_ALIGN(struct pending_rpc_head) this_exitrpc = {
	.prh_link  = { NULL },
	.prh_flags = RPC_CONTEXT_KERN | _RPC_CONTEXT_DONTFREE,
	.prh_func  = NULL, /* Allocated if non-NULL; set to one of:
	                    * - `propagate_process_exit_status'
	                    * - `propagate_thread_exit_status' */
};

/* Called in context of worker threads: propagate exit status of process leader */
PRIVATE NONNULL((1)) void PRPC_EXEC_CALLBACK_CC
propagate_process_exit_status(struct rpc_context *__restrict ctx,
                              void *UNUSED(cookie)) {
	struct taskpid *procpid;
	uint16_t status;
	if (ctx->rc_context == RPC_REASONCTX_SHUTDOWN)
		return; /* Already being shut down for some other reason --> don't do anything */

	/* At this point we know that we are a thread in a larger process, and
	 * that our process leader (iow: the main thread) has exited. Now it's
	 * our job to propagate its exit status into our own `taskpid'. */
	procpid = task_getprocpid();
	status  = atomic_read(&procpid->tp_status);
	THROW(E_EXIT_THREAD, status);
}


/* Called in context of main thread: propagate exit status of worker threads */
PRIVATE NONNULL((1)) void PRPC_EXEC_CALLBACK_CC
propagate_thread_exit_status(struct rpc_context *__restrict ctx,
                             void *cookie) {
	REF struct task *origin;
	struct taskpid *origin_pid;
	uint16_t status;

	/* Figure out the origin of the exit request. Note that for this purpose,
	 * the  originating thread used  its own `this_exitrpc'  in order to send
	 * an  RPC to the process's main thread (that  RPC is us, and we are said
	 * main  thread). As such, because `_RPC_CONTEXT_DONTFREE' means `cookie'
	 * is  a  pointer to  the sending  thread's `this_exitrpc',  we can  do a
	 * container_of-style  operation to determine the origin's `struct task'! */
	origin = (REF struct task *)((byte_t *)cookie - (uintptr_t)&this_exitrpc);

	/* Using the sending thread, we can determine their `struct taskpid' */
	origin_pid = task_gettaskpid_of(origin);

	/* And with that, we can extract the intended status */
	status = atomic_read(&origin_pid->tp_status);

	/* In order to  prevent `this_exitrpc' from  being free'd, child  threads
	 * let this RPC inherit a reference to the sending thread. Now that we're
	 * done  accessing the originating thread's TLS memory, we must drop that
	 * reference! */
	decref(origin);

	if (ctx->rc_context == RPC_REASONCTX_SHUTDOWN)
		return; /* Already being shut down for some other reason --> don't do anything */

	/* Actually propagate the exit status. */
	THROW(E_EXIT_THREAD, status);
}


/* Same as `task_exit()', but propagate the same status
 * to  all  other threads  within the  current process.
 *
 * This is the same as calling `task_exit()' from the
 * main thread of the calling process. */
PUBLIC ABNORMAL_RETURN ATTR_NORETURN void
NOTHROW(FCALL process_exit)(uint16_t w_status) {
	struct task *caller = THIS_TASK;
	struct taskpid *pid = task_gettaskpid_of(caller);

	if (!taskpid_isaprocess(pid)) {
		REF struct task *main_thread;
		main_thread = taskpid_gettask(taskpid_getprocpid(pid));
		if likely(main_thread) {
			/* Main thread hasn't been destroyed. */
			if (!(atomic_read(&main_thread->t_flags) & (TASK_FTERMINATING | TASK_FTERMINATED))) {
				/* Main thread hasn't terminated, yet. */

				/* Send an RPC to the main thread in order to terminate it. */
				if (atomic_cmpxch(&FORTASK(caller, this_exitrpc.prh_func),
				                  NULL, &propagate_thread_exit_status)) {

					/* This write is repeated in `task_exit()', but that's OK.
					 * It also has to  be done here, so  that the RPC will  be
					 * able  to talk to  our thread in  order to determine the
					 * exit status that should be propagated. */
					atomic_write(&pid->tp_status, w_status);

					/* Inherited by `propagate_thread_exit_status()' */
					incref(caller);

					/* Actually send the RPC (or at least try to, because if this
					 * fails,  it means  that the  main thread  is also currently
					 * terminating for some unrelated reason) */
					if unlikely(!task_rpc_schedule(main_thread, &FORTASK(caller, this_exitrpc))) {
						/* Race condition: main thread has already terminated,
						 * and we were unable to schedule the RPC to propagate
						 * our thread's process-exit request.
						 *
						 * But that's OK since the main thread is also currently
						 * exiting (only for a reason other than what our caller
						 * wanted it to be) */
						decref_nokill(caller);
					}
				}
			}
			decref_unlikely(main_thread);
		}
	}
	task_exit(w_status);
}


/* Terminate the calling thread immediately.
 * WARNING: Do not call this function to terminate a thread.
 *          It  would work, but exception handlers would not
 *          get  unwound  and  resources  would  be  leaked.
 *          If you wish  to exit your  current thread,  just
 *          throw an `E_EXIT_THREAD' error instead.
 * This  function  is  called  by  the  unhandled  exception  handler
 * when it  encounters an  `E_EXIT_THREAD' error,  or when  exception
 * data  cannot  be  propagated  to  userspace  in  the  event  of an
 * interrupt throwing some error, whilst originating from user-space.
 * @param: w_status: The task's exit status (mustn't be `WIFSTOPPED()' or `WIFCONTINUED()').
 * WARNING: Calling this function from an IDLE task, or any other
 *          task that is critical will cause the kernel to PANIC! */
PUBLIC ABNORMAL_RETURN ATTR_NORETURN void
NOTHROW(FCALL task_exit)(uint16_t w_status) {
	struct task *caller = THIS_TASK, *next;
	struct cpu *mycpu;
	uintptr_t flags;
	struct taskpid *pid = task_gettaskpid_of(caller);
	REF struct taskpid *parpid;

	assert(!WIFSTOPPED(w_status));
	assert(!WIFCONTINUED(w_status));
	assertf(PREEMPTION_ENABLED(), "Without preemption, how do you want to switch tasks?");
	assertf(!task_isconnected(), "Don't exit a thread while you've still got connections");
	assert(caller->t_flags & TASK_FRUNNING);

	if unlikely(caller->t_flags & TASK_FCRITICAL) {
		panic_critical_thread_exited(caller);
		atomic_and(&caller->t_flags, ~TASK_FCRITICAL);
	}

	/* Fill in the exit status.
	 * Note that this has to happen first, even before we set `TASK_FTERMINATING'! */
	atomic_write(&pid->tp_status, w_status);

	/* Set the bit to indicate that we've started termination. */
	flags = atomic_fetchor(&caller->t_flags, TASK_FTERMINATING);
	assertf(!(flags & TASK_FTERMINATING), "This shouldn't happen!");
	(void)flags;

	printk(KERN_TRACE "[sched] Exiting thread %p\n", caller);

	/* Determine the PID of the thread of which we are a child. */
	if (taskpid_isaprocess(pid)) {
		parpid = taskpid_getparentprocesspid(pid);
	} else {
		/* In this case, `parpid' is the PID of the associated process */
		parpid = incref(taskpid_getprocpid(pid));
	}

	/* Trigger the appropriate debug trap associated with thread/process  exits.
	 * This is required because otherwise GDB  will sooner or later hang  itself
	 * when waiting for the exited-notification of a terminated thread once it's
	 * no longer able to find the thread apart of thread listings.
	 *
	 * s.a. /kos/misc/gdbridge/gdbride.dee */
	if (kernel_debugtrap_enabled()) {
		struct debugtrap_reason reason;
		reason.dtr_reason = taskpid_isaprocess(pid)
		                    ? DEBUGTRAP_REASON_PEXITED
		                    : DEBUGTRAP_REASON_TEXITED;
		reason.dtr_signo  = w_status;
		reason.dtr_ptrarg = caller;
		kernel_debugtrap(&reason);
	}

	/* Clear the TID address of a user-space thread. */
	maybe_clear_tid_address(caller);

	/* Reap all remaining RPCs and invoke them in a SHUTDOWN context. */
	terminate_pending_rpcs(caller);

	if (taskpid_isaprocess(pid)) {
		/* Propagate  exit status to child threads, and
		 * reparent all child processes onto /bin/init. */
		struct procctl *ctl = pid->tp_pctl;
		REF struct procgrp *grp;

		/* Clear all still-pending process-directed RPCs. */
		{
			struct pending_rpc *rpcs;
			assert(PREEMPTION_ENABLED());
			procctl_sig_write(ctl); /* Never throws because preemption is enabled */
			rpcs = atomic_xch(&ctl->pc_sig_list.slh_first, THIS_RPCS_TERMINATED);
			atomic_or(&ctl->pc_sig_pend, 1); /* Indicate that further pending signals won't be served. */
			procctl_sig_endwrite(ctl);
			task_asyncrpc_destroy_list_for_shutdown(rpcs);
		}

		/* NOTE: As per the requirements, we're allowed to assume  that
		 *       no-one is allowed to still be adding additional  items
		 *       to `ctl->pc_chlds_list' (because we, as the associated
		 *       process, have the TASK_FTERMINATING flag set). */
again_process_children:
		assert(PREEMPTION_ENABLED());
		procctl_chlds_write(ctl); /* Never throws because preemption is enabled */
		while (!LIST_EMPTY(&ctl->pc_chlds_list)) {
			struct taskpid *child;
			child = LIST_FIRST(&ctl->pc_chlds_list);

			/* Re-parent onto /bin/init */
			if (!procctl_chlds_trywrite(&boottask_procctl)) {
				procctl_chlds_endwrite(ctl);
				procctl_chlds_waitwrite(&boottask_procctl); /* Never throws because preemption is enabled */
				goto again_process_children;
			}

			/* NOTE: Because  we're holding a lock to `ctl->pc_chlds_lock',
			 *       we know that the parent reference of any child process
			 *       can't be changed,  since doing so  requires one to  be
			 *       holding said lock. */
			assertf(arref_ptr(&child->tp_pctl->pc_parent) == caller,
			        "Child process indicates wrong parent:\n"
			        "arref_ptr(&child->tp_pctl->pc_parent) = %p\n"
			        "caller                                = %p",
			        arref_ptr(&child->tp_pctl->pc_parent), caller);

			/* Change the parent pointer to &boottask */
			arref_set(&child->tp_pctl->pc_parent, &boottask);
			procctl_chlds_remove(ctl, child);               /* Inherit reference */
			procctl_chlds_insert(&boottask_procctl, child); /* Inherit reference */
			procctl_chlds_endwrite(&boottask_procctl);
			sig_broadcast(&boottask_procctl.pc_chld_changed);
		}
		procctl_chlds_endwrite(ctl);

		/* Terminate all other threads within the process. */
		PREEMPTION_DISABLE();
		procctl_thrds_acquire_nopr(ctl);
		while (!LIST_EMPTY(&ctl->pc_thrds_list)) {
			REF struct task *child_thread;
			struct taskpid *child;
			child = LIST_FIRST(&ctl->pc_thrds_list);
			procctl_thrds_unbind(ctl, child); /* Inherit reference */
			procctl_thrds_release_nopr(ctl);
			PREEMPTION_ENABLE();
			child_thread = taskpid_gettask(child);
			decref_unlikely(child); /* Inherited from `procctl_thrds_unbind()' */
			if (child_thread != NULL) {
				/* Use the child thread's exit RPC to terminate
				 * it, as well  as propagate  our exit  status. */
				if (atomic_cmpxch(&FORTASK(child_thread, this_exitrpc.prh_func),
				                  NULL, &propagate_process_exit_status)) {
					bool ok;
					ok = task_rpc_schedule(child_thread, &FORTASK(child_thread, this_exitrpc));
					(void)ok; /* Unused */
				}
				decref_unlikely(child_thread);
			}
			PREEMPTION_DISABLE();
			procctl_thrds_acquire_nopr(ctl);
		}
		procctl_thrds_release_nopr(ctl);
		PREEMPTION_ENABLE();

		/* Posix:
		 * """
		 * When a controlling process terminates, the controlling terminal is
		 * dissociated from the current session,  allowing it to be  acquired
		 * by a new session leader.
		 * """
		 *
		 * IOW: If the caller is a session leader, disconnect their CTTY. */
		grp = procctl_getprocgrp(ctl);
		if (procgrp_issessionleader(grp) &&
		    procgrp_getrootpgid(grp) == taskpid_getroottid(pid)) {
			struct procsession *session = grp->pgr_session;
			REF struct ttydev *ctty;
again_get_ctty:
			ctty = axref_get(&session->ps_ctty);
			if (ctty) {
				bool ok;

				/* Clear the controlling process group field */
				awref_cmpxch(&ctty->t_cproc, grp, NULL);

				/* If the foreground process group is part of
				 * our  session,  clear that  field  as well. */
				for (;;) {
					REF struct procgrp *fproc;
					fproc = awref_get(&ctty->t_fproc);
					if (!fproc)
						break;
					ok = true;
					if (procgrp_getsessionleader(fproc) == grp)
						ok = awref_cmpxch(&ctty->t_fproc, fproc, NULL);
					decref_unlikely(fproc);
					if (ok)
						break;
				}

				/* Clear the session's CTTY reference. */
				ok = axref_cmpxch(&session->ps_ctty, ctty, NULL);
				decref_unlikely(ctty);
				if (!ok)
					goto again_get_ctty;
			}
		}
		decref_unlikely(grp);

		/* XXX: send `pid->tp_SIGCLD' to our parent process */
		/* XXX: Posix also say a bunch of stuff about SIGHUP relating to process
		 *      groups becoming orphaned as the  result of a process  exiting... */
	} else if (flags & TASK_FDETACHED) {
		/* Automatically unbind our PID from our process's list of threads. */
		struct procctl *parctl = parpid->tp_pctl;
		assert(PREEMPTION_ENABLED());
		PREEMPTION_DISABLE();
		procctl_thrds_acquire_nopr(parctl);
		if likely(LIST_ISBOUND(pid, tp_parsib)) {
			procctl_thrds_unbind(parctl, pid); /* Inherit reference */
			decref_nokill(pid);                /* nokill because of reference in `THIS_TASKPID' */
		}
		procctl_thrds_release_nopr(parctl);
		PREEMPTION_ENABLE();
	}

	PREEMPTION_DISABLE();
	mycpu = caller->t_cpu;
	assertf(FORCPU(mycpu, thiscpu_sched_current) == caller, "Inconsistent scheduler state");
	assertf(FORCPU(mycpu, thiscpu_sched_override) != caller, "Cannot exit while being the scheduling override");
	assertf(caller != &FORCPU(mycpu, thiscpu_idle), "The IDLE task cannot be terminated");

	/* Unset the  calling thread  potentially holding  the FPU  state.
	 * Since the task will go away, we don't actually have to save it. */
#ifdef CONFIG_HAVE_FPU
	if (FORCPU(mycpu, thiscpu_fputhread) == caller)
		FORCPU(mycpu, thiscpu_fputhread) = NULL;
#endif /* CONFIG_HAVE_FPU */

	/* Account for timings and scheduler internals, as well as figure out a successor thread. */
	next = sched_intern_yield_onexit(mycpu, caller); /* NOTE: This causes us to inherit a reference to `caller' */

	/* Hi-jack the execution stack of the next thread to have it do the decref()
	 * of our own thread, thus preventing  the undefined behavior that would  be
	 * caused if we tried to decref (and possibly destroy) ourselves.
	 *
	 * NOTE: The reference destroyed here was gifted to us by `sched_intern_yield_onexit()' */
	{
		struct scpustate *state;
		state = FORTASK(next, this_sstate);
		state = task_asyncrpc_push(state, &task_decref_for_exit_rpc, caller);
		FORTASK(next, this_sstate) = state;
	}

	/* Update our thread's status flags. */
	{
		uintptr_t old_flags;
		uintptr_t new_flags;
		do {
			/* Set the flag to indicate that we've been fully terminated.
			 * NOTE: Also ensure that a couple of other flags are set/cleared correctly,
			 *       though  most of these  flags should already  have the proper status */
			enum {
				set = (/* Set the terminated flags */
				       TASK_FTERMINATING | TASK_FTERMINATED |
				       /* Ensure that the thread's status indicates that it was (once) started */
				       TASK_FSTARTED | TASK_FSTARTING |
				       /* Once dead, there'd be no point in being moved to a different core */
				       TASK_FKEEPCORE |
				       0),
				del = (/* We're no longer running */
				       TASK_FRUNNING |
				       /* If we were  running in  vfork()-mode, clear  the
				        * VFORK flag to wake up our waiting parent thread. */
				       TASK_FVFORK |
				       /* This flag really shouldn't be set, so clearing simply ensures
				        * some consistency */
				       TASK_FTIMEOUT |
				       /* Once dead, we can no longer be resumed (so we're also no longer suspended) */
				       TASK_FSUSPENDED | TASK_FGDB_STOPPED |
				       0)
			};
			old_flags = atomic_read(&caller->t_flags);
			new_flags = old_flags;

			/* While this was already checked for above, some other thread may have set this
			 * flag in the mean time (though doing  something like that would be really  bad
			 * practice). In any case: properly handle the CRITICAL-flag until the very end,
			 * so  that other code can guaranty that setting  the flag at any point when the
			 * TERMINATED flag hasn't also been set will cause an intentional kernel  panic. */
			if unlikely(new_flags & TASK_FCRITICAL)
				panic_critical_thread_exited(caller);
			new_flags |= set;
			new_flags &= ~del;
		} while (!atomic_cmpxch_weak(&caller->t_flags,
		                             old_flags,
		                             new_flags));
	}

	/* Update the current-thread field to indicate who's about to start running. */
	FORCPU(mycpu, thiscpu_sched_current) = next;

	/* For the sake of easier  interlocking, we only broadcast our  thread's
	 * status change _after_ setting the TASK_FTERMINATED flag. -- That way,
	 * it  becomes possible to  wait for a thread  to _fully_ terminate, and
	 * there is no chance of a terminated thread still being scheduled after
	 * it broadcasted its terminated status.
	 *
	 * Important! Must broadcast the change while impersonating `next'!
	 *
	 * Our current thread context is already too broken to allow us to
	 * re-schedule  others threads that may be waiting for us to exit. */
	sig_broadcastas_nopr(&pid->tp_changed, next);

	/* Also notify our parent process that one of its children has changed state. */
	sig_broadcastas_nopr(&parpid->tp_pctl->pc_chld_changed, next);
	if unlikely(atomic_decfetch(&parpid->tp_refcnt) == 0) {
		struct scpustate *state;
		state = FORTASK(next, this_sstate);
		state = task_asyncrpc_push(state, &taskpid_destroy_rpc, parpid);
		FORTASK(next, this_sstate) = state;
	}

	/* Good bye... */
	cpu_run_current_nopr();
}

DECL_END

#endif /* !GUARD_KERNEL_SRC_SCHED_TASK_EXIT_C */
