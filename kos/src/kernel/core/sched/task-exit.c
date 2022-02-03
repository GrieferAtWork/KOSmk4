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
#ifndef GUARD_KERNEL_SRC_SCHED_TASK_EXIT_C
#define GUARD_KERNEL_SRC_SCHED_TASK_EXIT_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/debugtrap.h>
#include <kernel/except.h>
#include <kernel/fpu.h>
#include <kernel/mman/mpartmeta.h>
#include <kernel/panic.h>
#include <kernel/printk.h>
#include <kernel/rt/except-syscall.h>
#include <sched/cpu.h>
#include <sched/group.h>
#include <sched/rpc-internal.h>
#include <sched/rpc.h>
#include <sched/scheduler.h>
#include <sched/task.h>

#include <hybrid/atomic.h>

#include <kos/except.h>
#include <sys/wait.h>

#include <assert.h>
#include <stddef.h>

DECL_BEGIN

PRIVATE NONNULL((1, 2)) void
NOTHROW(PRPC_EXEC_CALLBACK_CC task_decref_for_exit_rpc)(struct rpc_context *__restrict UNUSED(ctx),
                                                        void *cookie) {
	decref((struct task *)cookie);
}

PRIVATE ATTR_KERNEL_PANIC_NORETURN ATTR_COLD ATTR_NOINLINE NONNULL((1)) void
NOTHROW(FCALL panic_critical_thread_exited)(struct task *__restrict caller) {
	kernel_panic("Critical thread at %p has exited", caller);
}


PRIVATE NONNULL((1)) void
NOTHROW(FCALL maybe_clear_tid_address)(struct task *__restrict caller) {
	USER CHECKED pid_t *addr;
	addr = FORTASK(caller, this_tid_address);
	if (addr == NULL)
		return;
	TRY {
		/* Special case for vfork when the kernel supports userprocmask. */
#ifdef CONFIG_HAVE_USERPROCMASK
		uintptr_t my_flags = PERTASK_GET(this_task.t_flags);
		if (my_flags & TASK_FVFORK) {
			if unlikely(my_flags & TASK_FUSERPROCMASK_AFTER_VFORK) {
				USER CHECKED struct userprocmask *um;
				um = (USER CHECKED struct userprocmask *)addr;
				/* Handle the special case of a vfork()'d thread having
				 * initialized their parent thread's userprocmask  data
				 * structure.
				 * This  is  needed  because  userprocmask  is  part  of   a
				 * thread's  user-space  TLS  state,  which  itself  is part
				 * of that process's VM, which  is the very thing that  gets
				 * shared  during a  call to  vfork(), meaning  that we must
				 * uninitialize it if it wasn't the parent who did the init! */
				ATOMIC_WRITE(um->pm_sigmask, NULL);
			}
			return;
		}
#endif /* CONFIG_HAVE_USERPROCMASK */
		ATOMIC_WRITE(*addr, 0);
		mman_broadcastfutex(addr);
	} EXCEPT {
		/* Explicitly handle E_SEGFAULT:addr as a no-op */
		if (!was_thrown(E_SEGFAULT) ||
		    PERTASK_NE(this_exception_args.e_segfault.s_addr, (uintptr_t)addr)) {
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
	remain = ATOMIC_XCH(FORTASK(caller, this_rpcs.slh_first),
	                    THIS_RPCS_TERMINATED);
	assertf(remain != THIS_RPCS_TERMINATED,
	        "We're the only ones that ever set this, "
	        "so what; did we get called twice?");
	sig_broadcast_for_fini(&FORTASK(caller, this_rpcs_sig));

	/* Destroy all remaining RPCs for the purpose of shutdown. */
	task_asyncrpc_destroy_list_for_shutdown(remain);
}


INTDEF NOBLOCK NONNULL((1)) void /* From "sched/pid.c" */
NOTHROW(KCALL maybe_propagate_exit_to_procss_children)(struct task *__restrict caller);


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
 *                   This argument is ignored for kernel-threads.
 * WARNING: Calling this function from an IDLE task, or any other
 *          task that is critical will cause the kernel to PANIC! */
PUBLIC ABNORMAL_RETURN ATTR_NORETURN void
NOTHROW(FCALL task_exit)(int w_status) {
	struct task *caller = THIS_TASK, *next;
	struct cpu *me;
	struct taskpid *pid = THIS_TASKPID;
	assert(!WIFSTOPPED(w_status));
	assert(!WIFCONTINUED(w_status));
	assertf(PREEMPTION_ENABLED(), "Without preemption, how do you want to switch tasks?");
	assertf(!task_wasconnected(), "Don't exit a thread while you've still got connections");
	assert(caller->t_flags & TASK_FRUNNING);

	if unlikely(caller->t_flags & TASK_FCRITICAL) {
		panic_critical_thread_exited(caller);
		ATOMIC_AND(caller->t_flags, ~TASK_FCRITICAL);
	}

	/* Fill in the exit status */
	ATOMIC_WRITE(pid->tp_status, w_status);

	/* Set the bit to indicate that we've started termination. */
	if (!(ATOMIC_FETCHOR(caller->t_flags, TASK_FTERMINATING) & TASK_FTERMINATING)) {
		printk(KERN_TRACE "[sched] Exiting thread %p\n", caller);

		/* Trigger the appropriate debug trap associated with thread/process  exits.
		 * This is required because otherwise GDB  will sooner or later hang  itself
		 * when waiting for the exited-notification of a terminated thread once it's
		 * no longer able to find the thread apart of thread listings.
		 *
		 * s.a. /kos/misc/gdbridge/gdbride.dee */
		if (kernel_debugtrap_enabled()) {
			struct debugtrap_reason reason;
			reason.dtr_reason = task_isprocessleader_p(caller)
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

		/* Propagate the  */
		maybe_propagate_exit_to_procss_children(caller);
	}

	PREEMPTION_DISABLE();
	me = caller->t_cpu;
	assertf(FORCPU(me, thiscpu_sched_current) == caller, "Inconsistent scheduler state");
	assertf(FORCPU(me, thiscpu_sched_override) != caller, "Cannot exit while being the scheduling override");
	assertf(caller != &FORCPU(me, thiscpu_idle), "The IDLE task cannot be terminated");

#ifdef CONFIG_FPU
	/* Unset the  calling thread  potentially holding  the FPU  state.
	 * Since the task will go away, we don't actually have to save it. */
	ATOMIC_CMPXCH(FORCPU(me, thiscpu_fputhread), THIS_TASK, NULL);
#endif /* CONFIG_FPU */

	/* Account for timings and scheduler internals, as well as figure out a successor thread. */
	next = sched_intern_yield_onexit(me, caller); /* NOTE: This causes us to inherit a reference to `caller' */

	/* Hi-jack the execution stack of the next thread to have it do the decref()
	 * of our own thread, thus preventing  the undefined behavior that would  be
	 * caused if we tried to decref (and possibly destroy) ourself.
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
			old_flags = ATOMIC_READ(caller->t_flags);
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
		} while (!ATOMIC_CMPXCH_WEAK(caller->t_flags,
		                             old_flags,
		                             new_flags));
	}

	/* Update the current-thread field to indicate who's about to start running. */
	FORCPU(me, thiscpu_sched_current) = next;

	/* Broadcast  the  status-changed   signal  _after_  setting   `TASK_FTERMINATED'
	 * That way,  other  thread  can use  `tp_changed'  alongside  `TASK_FTERMINATED'
	 * in order to wait for  the thread to fully terminate.  If we were to  broadcast
	 * `tp_changed'  before setting the  flag, then even  though we've got interrupts
	 * disabled, another CPU may receive the  `tp_changed' signal and read the  flags
	 * field not containing `TASK_FTERMINATED' yet before we've set the flag, causing
	 * it to end up  soft-locked (as in:  CTRL+C would still  work), waiting for  the
	 * thread to terminate when in fact it already has terminated.
	 * However,  we  must  fill  in  the  exit  status  _before_  setting  `TASK_FTERMINATED',
	 * such that another thread waiting for us to terminate knows that once `TASK_FTERMINATED'
	 * has been set,  the thread's  pid's `tp_status' field  contains its  final exit  status.
	 * Thus, the  terminate-flag  acts  as  an  interlocked check  for  the  exit  status  and
	 * waiting for the status to change during thread exit. */

	/* Important! Must broadcast the change while impersonating `next'!
	 *
	 * Our current thread context is already too broken to allow us to
	 * re-schedule  others threads that may be waiting for us to exit. */
	sig_broadcast_as_nopr(&pid->tp_changed, next);

	/* Good bye... */
	cpu_run_current_nopr();
}

DECL_END

#endif /* !GUARD_KERNEL_SRC_SCHED_TASK_EXIT_C */
