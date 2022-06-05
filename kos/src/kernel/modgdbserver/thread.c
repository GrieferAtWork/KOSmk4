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
#ifndef GUARD_MODGDBSERVER_THREAD_C
#define GUARD_MODGDBSERVER_THREAD_C 1
#define _KOS_SOURCE 1

/* Implementation of `GDBThread_*' functions */

#include <kernel/compiler.h>

#include <kernel/except.h>
#include <kernel/fpu.h> /* CONFIG_FPU */
#include <kernel/printk.h>
#include <sched/cpu.h>
#include <sched/group.h>
#include <sched/rpc.h>
#include <sched/scheduler.h>
#include <sched/sig.h>
#include <sched/task.h>
#include <sched/tsc.h>

#include <hybrid/atomic.h>
#include <hybrid/sched/preemption.h>

#include <kos/debugtrap.h>

#include <assert.h>
#include <inttypes.h>
#include <stddef.h>

#include "gdb.h"
#include "server.h"      /* GDBServer_Features */
#include "thread-enum.h" /* GDBThread_Enumerate() */

DECL_BEGIN

/* Signal broadcast when a stop event is added to `GDBThread_Stopped' */
PRIVATE struct sig GDBThread_StoppedAdded = SIG_INIT;

struct gdb_thread_stop_event_with_reason {
	GDBThreadStopEvent      e;
	struct debugtrap_reason r;
};

#define GDBTHREAD_STOPRPCIMPL_F_SETREASON 1
#define GDBTHREAD_STOPRPCIMPL_F_STOPCPU   2


#ifndef NDEBUG
PRIVATE NOBLOCK ATTR_PURE WUNUSED NONNULL((2)) bool
NOTHROW(FCALL GDBServer_HasStopEvent)(GDBThreadStopEvent const *chain,
                                      GDBThreadStopEvent const *__restrict stop_event) {
	GDBThreadStopEvent const *iter;
	for (iter = chain; iter; iter = iter->tse_next) {
		if (iter == stop_event)
			return true;
	}
	return false;
}
#endif /* !NDEBUG */


PRIVATE void
NOTHROW(FCALL GDBThread_StopRPC_BecomeGDBHostImpl)(GDBThreadStopEvent *__restrict notif) {
	assert(PREEMPTION_ENABLED());

	/* Configure non-/all-stop mode */
	GDBThread_IsNonStopModeActive = true;
	if (!(GDBServer_Features & GDB_SERVER_FEATURE_NONSTOP))
		GDBThread_StopAllCpus();

again_gdb_main:
	/* Call the GDB main function. */
	GDB_MainWithAlternateStack();

	/* Check if we ourself are supposed to remain stopped. */
	if (ATOMIC_READ(notif->tse_mayresume) != GDB_THREAD_MAYRESUME_RESUME)
		goto again_gdb_main;

	/* Resume system execution if we were in all-stop mode. */
	if (GDBThread_IsAllStopModeActive)
		GDBThread_ResumeAllCpus();
	if (!(GDBServer_Features & GDB_SERVER_FEATURE_NONSTOP))
		GDBThread_ResumeEverything();

	/* Our own stop_event should have already been removed  by
	 * `GDBThread_Resume()', since our `tse_mayresume' was set
	 * to `GDB_THREAD_MAYRESUME_RESUME' */
#ifndef NDEBUG
	assertf(!GDBServer_HasStopEvent(GDBThread_Stopped, notif) &&
	        !GDBServer_HasStopEvent(GDBThread_AsyncNotifStopEvents, notif),
	        "Should have already been removed, because"
	        " `tse_mayresume == GDB_THREAD_MAYRESUME_RESUME'");
#endif /* !NDEBUG */

	/* Unlock the GDB server host lock */
	ATOMIC_WRITE(GDBServer_Host, NULL);
	sig_broadcast(&GDBServer_HostUnlocked);
}

PRIVATE NOPREEMPT struct icpustate *
NOTHROW(FCALL GDBThread_StopRPCImpl)(uintptr_t flags,
                                     struct icpustate *__restrict state) {
	struct gdb_thread_stop_event_with_reason stop_event;
	uintptr_t old_flags;
	assert(!PREEMPTION_ENABLED());
	task_pushconnections(&stop_event.e.tse_oldcon);
#ifdef CONFIG_FPU
	fpustate_save();
#endif /* CONFIG_FPU */
	stop_event.e.tse_reason = NULL; /* Manual suspend -> No explicit reason */
	if (flags & GDBTHREAD_STOPRPCIMPL_F_SETREASON) {
		stop_event.r.dtr_signo  = 0;
		stop_event.r.dtr_reason = DEBUGTRAP_REASON_NONE;
		stop_event.e.tse_reason = &stop_event.r;
	}
	stop_event.e.tse_isacpu    = flags & GDBTHREAD_STOPRPCIMPL_F_STOPCPU ? 1 : 0;
	stop_event.e.tse_thread    = THIS_TASK;
	stop_event.e.tse_state     = state;
	stop_event.e.tse_statekind = CPUSTATE_KIND_ICPUSTATE;
	stop_event.e.tse_mayresume = stop_event.e.tse_reason
	                             ? GDB_THREAD_MAYRESUME_STOP    /* With asnotif */
	                             : GDB_THREAD_MAYRESUME_NASYNC; /* No asnotif */
	GDB_DEBUG("[gdb] Stop %s with %p ("
	          "%" PRIuN(__SIZEOF_PID_T__) "."
	          "%" PRIuN(__SIZEOF_PID_T__) ") "
	          "[flags=%#" PRIxPTR "]\n",
	          (flags & GDBTHREAD_STOPRPCIMPL_F_STOPCPU) ? "cpu" : "thread",
	          stop_event.e.tse_thread,
	          task_getrootpid_of(stop_event.e.tse_thread),
	          task_getroottid_of(stop_event.e.tse_thread),
	          flags);
	sig_init(&stop_event.e.tse_sigresume);
	COMPILER_BARRIER();
	if (stop_event.e.tse_mayresume == GDB_THREAD_MAYRESUME_STOP) {
		GDBThreadStopEvent *next;
		do {
			next = ATOMIC_READ(GDBThread_AsyncNotifStopEvents);
			stop_event.e.tse_next = next;
		} while (!ATOMIC_CMPXCH_WEAK(GDBThread_AsyncNotifStopEvents,
		                             stop_event.e.tse_next, &stop_event.e));
		if (!next)
			sig_broadcast(&GDBThread_AsyncNotifStopEventsAdded);
	} else {
		/* NOTE: Event though `GDBThread_Stopped' is normally private to the GDB host thread,
		 *       the host thread itself is currently waiting for us to become suspended,  and
		 *       is actually expecting us to access this field ourself. */
		do {
			stop_event.e.tse_next = ATOMIC_READ(GDBThread_Stopped);
		} while (!ATOMIC_CMPXCH_WEAK(GDBThread_Stopped, stop_event.e.tse_next,
		                             &stop_event.e));
	}
	COMPILER_BARRIER();

	/* Set our thread's STOPPED and KEEPCORE flags */
	old_flags = ATOMIC_FETCHOR(stop_event.e.tse_thread->t_flags,
	                           flags & GDBTHREAD_STOPRPCIMPL_F_STOPCPU
	                           ? (TASK_FKEEPCORE)
	                           : (TASK_FGDB_STOPPED | TASK_FKEEPCORE));

	/* Tell the GDB host thread that we're now suspended. */
	sig_broadcast(&GDBThread_StoppedAdded);

	COMPILER_READ_BARRIER();
	if (flags & GDBTHREAD_STOPRPCIMPL_F_STOPCPU) {
		struct task *old_override;
		struct cpu *me;
do_cpu_stop:
		COMPILER_BARRIER();
		me = stop_event.e.tse_thread->t_cpu;
		/* TODO: Don't directly access `thiscpu_sched_override'! */
		old_override = FORCPU(me, thiscpu_sched_override);
		FORCPU(me, thiscpu_sched_override) = stop_event.e.tse_thread;
		COMPILER_BARRIER();

		PREEMPTION_ENABLE();
		/* Wait until we're supposed to resume execution. */
		while ((ATOMIC_READ(stop_event.e.tse_mayresume) != GDB_THREAD_MAYRESUME_RESUME)) {
			if (!ATOMIC_READ(stop_event.e.tse_isacpu)) {
switch_to_normal_stop:
				COMPILER_BARRIER();
				FORCPU(me, thiscpu_sched_override) = old_override;
				COMPILER_BARRIER();
				goto do_normal_stop;
			}
			task_connect_for_poll(&stop_event.e.tse_sigresume);
			if (!ATOMIC_READ(stop_event.e.tse_isacpu)) {
				task_disconnectall();
				goto switch_to_normal_stop;
			}
			if (ATOMIC_READ(stop_event.e.tse_mayresume) == GDB_THREAD_MAYRESUME_RESUME) {
				task_disconnectall();
				break;
			}
			if (!task_waitfor_norpc_nx())
				task_disconnectall();
		}
		PREEMPTION_DISABLE();

		COMPILER_BARRIER();
		FORCPU(me, thiscpu_sched_override) = old_override;
		COMPILER_BARRIER();
	} else {
		/* Check if we have to switch over to the original scheduling override.
		 * s.a. `GDBThread_StopWithAsyncNotificationRPC()' */
		{
			struct cpu *me = stop_event.e.tse_thread->t_cpu;
			/* TODO: Don't directly access `thiscpu_sched_override'! */
			if (FORCPU(me, thiscpu_sched_override) &&
			    FORCPU(me, thiscpu_sched_override) != stop_event.e.tse_thread) {
				//TODO:sched_switchthread_force(me, stop_event.e.tse_thread, FORCPU(me, thiscpu_sched_override));
				/* Switch back to `c_override' */
				FORCPU(me, thiscpu_sched_current) = FORCPU(me, thiscpu_sched_override);
				cpu_run_current_and_remember_nopr(stop_event.e.tse_thread);
			}
		}
		PREEMPTION_ENABLE();
do_normal_stop:
		/* Wait until we're supposed to resume execution. */
		while (ATOMIC_READ(stop_event.e.tse_mayresume) != GDB_THREAD_MAYRESUME_RESUME) {
			if (ATOMIC_READ(stop_event.e.tse_isacpu))
				goto do_cpu_stop;
			/* Try to become the GDB host thread if we've been given a stop reason. */
			if (ATOMIC_READ(stop_event.e.tse_reason) != NULL) {
				if (ATOMIC_CMPXCH(GDBServer_Host, NULL, stop_event.e.tse_thread)) {
					assert(!ATOMIC_READ(stop_event.e.tse_isacpu));
					/* Check for race condition: We're actually supposed to resume execution */
					if unlikely(ATOMIC_READ(stop_event.e.tse_mayresume) == GDB_THREAD_MAYRESUME_RESUME) {
						ATOMIC_WRITE(GDBServer_Host, NULL);
						sig_broadcast(&GDBServer_HostUnlocked);
						break;
					}
					GDBThread_StopRPC_BecomeGDBHostImpl(&stop_event.e);
					continue;
				}
				task_connect_for_poll(&GDBServer_HostUnlocked);
			}
			task_connect_for_poll(&stop_event.e.tse_sigresume);
			if (ATOMIC_READ(stop_event.e.tse_isacpu)) {
				task_disconnectall();
				goto do_cpu_stop;
			}
			if (ATOMIC_READ(stop_event.e.tse_mayresume) == GDB_THREAD_MAYRESUME_RESUME) {
				task_disconnectall();
				break;
			}
			/* Try to become the GDB host thread if we've been given a stop reason. */
			if (ATOMIC_READ(stop_event.e.tse_reason) != NULL) {
				if (ATOMIC_CMPXCH(GDBServer_Host, NULL, stop_event.e.tse_thread)) {
					task_disconnectall();
					assert(!ATOMIC_READ(stop_event.e.tse_isacpu));
					/* Check for race condition: We're actually supposed to resume execution */
					if unlikely(ATOMIC_READ(stop_event.e.tse_mayresume) == GDB_THREAD_MAYRESUME_RESUME) {
						ATOMIC_WRITE(GDBServer_Host, NULL);
						sig_broadcast(&GDBServer_HostUnlocked);
						break;
					}
					GDBThread_StopRPC_BecomeGDBHostImpl(&stop_event.e);
					continue;
				}
			}
			if (!task_waitfor_norpc_nx())
				task_disconnectall();
		}
		PREEMPTION_DISABLE();
	}

	/* Clear our thread's KEEPCORE flags */
	if likely(!(old_flags & TASK_FKEEPCORE))
		ATOMIC_AND(stop_event.e.tse_thread->t_flags, ~TASK_FKEEPCORE);
	task_popconnections();
	return (struct icpustate *)stop_event.e.tse_state;
}

PRIVATE NONNULL((1)) void
NOTHROW(PRPC_EXEC_CALLBACK_CC GDBThread_StopRPC)(struct rpc_context *__restrict ctx,
                                                 void *cookie) {
	preemption_flag_t was;
	preemption_pushoff(&was);
	ctx->rc_state = GDBThread_StopRPCImpl((uintptr_t)cookie, ctx->rc_state);
	preemption_pop(&was);
}

PRIVATE NOBLOCK NOPREEMPT NONNULL((1, 2)) struct icpustate *
NOTHROW(FCALL GDBThread_StopAllCpusIPI)(struct icpustate *__restrict state,
                                        void *args[CPU_IPI_ARGCOUNT]) {
	(void)args;
	return GDBThread_StopRPCImpl(GDBTHREAD_STOPRPCIMPL_F_STOPCPU, state);
}

PRIVATE struct task *GDBThread_StopAll_Host_Old_override = NULL;
PRIVATE uintptr_t GDBThread_StopAll_Host_Old_flags = 0;

PRIVATE void NOTHROW(FCALL GDBThread_DisablePreemptionForHostCPU)(void) {
	preemption_flag_t was;
	/* TODO: Don't directly access `thiscpu_sched_override'! */
	preemption_pushoff(&was);
	/* Ensure that the GDB host thread doesn't move to a different core. */
	GDBThread_StopAll_Host_Old_flags = ATOMIC_FETCHOR(THIS_TASK->t_flags, TASK_FKEEPCORE);
	/* Set the GDB Host thread as the scheduling override */
	GDBThread_StopAll_Host_Old_override = FORCPU(GDBServer_Host->t_cpu, thiscpu_sched_override);
	FORCPU(GDBServer_Host->t_cpu, thiscpu_sched_override) = GDBServer_Host;
	preemption_pop(&was);
}

PRIVATE void NOTHROW(FCALL GDBThread_ReenablePreemptionForHostCPU)(void) {
	preemption_flag_t was;
	/* TODO: Don't directly access `thiscpu_sched_override'! */
	preemption_pushoff(&was);
	/* Restore the old scheduling override */
	FORCPU(GDBServer_Host->t_cpu, thiscpu_sched_override) = GDBThread_StopAll_Host_Old_override;
	/* Restore the old KEEPCORE flag. */
	if (!(GDBThread_StopAll_Host_Old_flags & TASK_FKEEPCORE))
		ATOMIC_AND(THIS_TASK->t_flags, ~TASK_FKEEPCORE);
	preemption_pop(&was);
}


INTERN void NOTHROW(FCALL GDBThread_StopAllCpus)(void) {
	unsigned int count;
	GDBThreadStopEvent *oldStopEvents;
	if (GDBThread_IsAllStopModeActive)
		return; /* Already in all-stop mode */
	oldStopEvents = GDBThread_Stopped;
	GDBThread_Stopped = NULL;
	/* Disable preemption for our own CPU */
	GDBThread_DisablePreemptionForHostCPU();
	{
		void *args[CPU_IPI_ARGCOUNT];
		/* Atomically send IPIs to all CPUs that aren't in deep sleep (excluding our own) */
		count = cpu_broadcastipi_notthis(&GDBThread_StopAllCpusIPI, args,
		                                 CPU_IPI_FWAITFOR);
	}
	if (count != 0) {
		/* Wait until a total of `count' new stop events have appeared. */
		GDBThreadStopEvent *lastNewEvent;
		unsigned int newCount;
		for (;;) {
			newCount     = 0;
			lastNewEvent = ATOMIC_READ(GDBThread_Stopped);
			if (lastNewEvent) {
				++newCount;
				assert(lastNewEvent->tse_isacpu);
				while (lastNewEvent->tse_next) {
					++newCount;
					lastNewEvent = lastNewEvent->tse_next;
					assert(lastNewEvent->tse_isacpu);
				}
			}
			assert(newCount <= count);
			if (newCount >= count)
				break;
			task_pause();
		}
		lastNewEvent->tse_next = oldStopEvents;
	} else {
		GDBThread_Stopped = oldStopEvents;
	}
	GDBThread_IsNonStopModeActive = false;
}


LOCAL NONNULL((1)) void
NOTHROW(FCALL GDBThread_ResumeSingleStopEvent)(GDBThreadStopEvent *__restrict self) {
	GDB_DEBUG("[gdb] Resume %s with %p ("
	          "%" PRIuN(__SIZEOF_PID_T__) "."
	          "%" PRIuN(__SIZEOF_PID_T__) ")\n",
	          self->tse_isacpu ? "cpu" : "thread",
	          self->tse_thread,
	          task_getrootpid_of(self->tse_thread),
	          task_getroottid_of(self->tse_thread));
	assert(self->tse_mayresume == GDB_THREAD_MAYRESUME_NASYNC);
	COMPILER_BARRIER();
	ATOMIC_AND(self->tse_thread->t_flags, ~TASK_FGDB_STOPPED);
	ATOMIC_WRITE(self->tse_mayresume, GDB_THREAD_MAYRESUME_RESUME);
	COMPILER_BARRIER();
	sig_broadcast(&self->tse_sigresume);
	COMPILER_BARRIER();
}


/* Find whole-cpu stop events in `GDBThread_AsyncNotifStopEvents', and
 * change them to only affect  the associated thread, rather than  the
 * entire CPU. */
PRIVATE void NOTHROW(FCALL GDBThread_DowngradeSuspendedAsyncCPUs)(void) {
	GDBThreadStopEvent *chain, *last, *iter;
	chain = ATOMIC_XCH(GDBThread_AsyncNotifStopEvents, NULL);
	if (!chain)
		return;
	iter = chain;
	do {
		if (iter->tse_isacpu) {
			/* Downgrade to a single-thread lock. */
			ATOMIC_WRITE(iter->tse_isacpu, 0);
			sig_broadcast(&iter->tse_sigresume);
		}
		last = iter;
	} while ((iter = iter->tse_next) != NULL);
	do {
		iter = ATOMIC_READ(GDBThread_AsyncNotifStopEvents);
		last->tse_next = chain;
	} while (!ATOMIC_CMPXCH_WEAK(GDBThread_AsyncNotifStopEvents,
	                             iter, chain));
}


/* Enter  non-stop  mode  (no-op  if  already  in  non-stop  mode)
 * This is done by resuming all stop events with `tse_isacpu != 0' */
INTERN void NOTHROW(FCALL GDBThread_ResumeAllCpus)(void) {
	GDBThreadStopEvent **piter, *iter;
	/* Wake up all suspended CPUs */
	if (!GDBThread_IsAllStopModeActive)
		return;
	GDB_DEBUG("[gdb] GDBThread_ResumeAllCpus()\n");
	piter = &GDBThread_Stopped;
again_piter:
	for (; (iter = *piter) != NULL; piter = &iter->tse_next) {
		if (!iter->tse_isacpu)
			continue; /* Not a CPU stop event */
		assert(iter->tse_mayresume == GDB_THREAD_MAYRESUME_NASYNC);
		*piter = iter->tse_next;
		GDBThread_ResumeSingleStopEvent(iter);
		goto again_piter;
	}
	GDBThread_DowngradeSuspendedAsyncCPUs();
	GDBThread_ReenablePreemptionForHostCPU();
	GDBThread_IsNonStopModeActive = true;
}



/* Resume all threads for which no pending async notifications exist. */
INTERN void NOTHROW(FCALL GDBThread_ResumeEverything)(void) {
	GDBThreadStopEvent *iter, *next;
	GDB_DEBUG("[gdb] GDBThread_ResumeEverything()\n");
	/* Resume execution of all suspended threads that
	 * don't  have   pending   async   notifications. */
	iter = GDBThread_Stopped;
	GDBThread_Stopped = NULL;
	while (iter) {
		next = iter->tse_next;
		GDBThread_ResumeSingleStopEvent(iter);
		iter = next;
	}
	if (GDBThread_IsAllStopModeActive) {
		/* Downgrade pending async stop notifications that used to affect
		 * the whole associated CPU, so only affect the single associated
		 * thread. */
		GDBThread_DowngradeSuspendedAsyncCPUs();
		/* Re-enable preemption for our hosting CPU */
		GDBThread_ReenablePreemptionForHostCPU();
		GDBThread_IsNonStopModeActive = true;
	}
}




/* Check if the given `thread' has been stopped by the GDB server */
INTERN NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) bool
NOTHROW(FCALL GDBThread_IsStopped)(struct task const *__restrict thread) {
	if (GDBThread_IsAllStopModeActive)
		return true; /* Everything is suspended in non-stop mode. */
	return (ATOMIC_READ(thread->t_flags) & TASK_FGDB_STOPPED) != 0;
}

/* Same as `GDBThread_IsStopped()', but the thread doesn't count as truly
 * stopped, unless it was stopped explicitly (rather than implicitly,  as
 * would be the case when `GDBThread_IsAllStopModeActive == true') */
INTERN NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) bool
NOTHROW(FCALL GDBThread_IsStoppedExplicitly)(struct task const *__restrict thread) {
	return (ATOMIC_READ(thread->t_flags) & TASK_FGDB_STOPPED) != 0;
}


/* Check if the given `thread' has terminated */
INTERN NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) bool
NOTHROW(FCALL GDBThread_HasTerminated)(struct task const *__restrict thread) {
	return (ATOMIC_READ(thread->t_flags) & (TASK_FTERMINATED | TASK_FTERMINATING)) != 0;
}


/* cookie == (struct task *)old_scheduling_override */
PRIVATE NONNULL((1)) void
NOTHROW(PRPC_EXEC_CALLBACK_CC GDBThread_StopWithAsyncNotificationRPC)(struct rpc_context *__restrict ctx,
                                                                      void *cookie) {
	/* Restore the old CPU override. */
	struct cpu *me;
	preemption_flag_t was;
	preemption_pushoff(&was);
	me  = THIS_CPU;
	/* TODO: Don't directly access `thiscpu_sched_override'! */
	FORCPU(me, thiscpu_sched_override) = (REF struct task *)cookie;
	ctx->rc_state = GDBThread_StopRPCImpl(GDBTHREAD_STOPRPCIMPL_F_SETREASON, ctx->rc_state);
	preemption_pop(&was);
}


PRIVATE struct sig GDBThread_StopWithAsyncNotificationIPI_Done = SIG_INIT;

PRIVATE NOBLOCK NONNULL((1, 2)) struct icpustate *
NOTHROW(FCALL GDBThread_StopWithAsyncNotificationIPI)(struct icpustate *__restrict state,
                                                      void *args[CPU_IPI_ARGCOUNT]) {
	struct task *thread;
	struct task *caller = THIS_TASK;
	struct cpu *me   = caller->t_cpu;
	thread = (struct task *)args[0];
	assert(FORCPU(me, thiscpu_sched_override) == caller); /* TODO: This can fail if the CPU wasn't stop-suspended */
	assert(!PREEMPTION_ENABLED());
	/* Pass scheduling override control to `thread' */
	COMPILER_BARRIER();
	/* TODO: Don't directly access `thiscpu_sched_override'! */
	FORCPU(me, thiscpu_sched_override) = thread;
	COMPILER_BARRIER();
	GDB_DEBUG("[gdb] Send Stop RPC to with %p ("
	          "%" PRIuN(__SIZEOF_PID_T__) "."
	          "%" PRIuN(__SIZEOF_PID_T__) ") "
	          "[async-altcpu]\n",
	          thread,
	          task_getrootpid_of(thread),
	          task_getroottid_of(thread));
	/* Very important: Set  the  HIGH_PRIORITY flag,  thus ensuring
	 *                 that we immediately switch over to `thread',
	 *                 allowing it to run as the new override. */
	if (!task_rpc_exec(thread,
	                   RPC_CONTEXT_KERN |
	                   RPC_SYNCMODE_F_ALLOW_ASYNC |
	                   RPC_PRIORITY_F_HIGH,
	                   &GDBThread_StopWithAsyncNotificationRPC,
	                   caller)) {
		COMPILER_BARRIER();
		FORCPU(me, thiscpu_sched_override) = GDBServer_Host;
		COMPILER_BARRIER();
	}
	sig_broadcast(&GDBThread_StopWithAsyncNotificationIPI_Done);
	return state;
}




/* When already in all-stop mode, create a missing async stop notification for `thread' */
INTERN NONNULL((1)) bool
NOTHROW(FCALL GDBThread_CreateMissingAsyncStopNotification)(struct task *__restrict thread) {
	if (!GDBThread_IsAllStopModeActive)
		return false; /* Only in all-stop mode can there be missing stop notifications. */
	if (GDBThread_HasTerminated(thread))
		return false; /* The thread has already terminated. */
	if (GDBThread_IsStoppedExplicitly(thread)) {
		GDBThreadStopEvent *evt;
		/* This thread has already been suspended.
		 * Check   if  it  was   suspended  by  use   of  an  async  notification.
		 * if not, then simply change the existing notification into an ASYNC one. */
		evt = GDBThread_PopStopEvent(thread);
		if (!evt) {
			/* The stop event isn't in the set of Stopped threads, so it has to be
			 * somewhere within  the  set  of pending  async  stop  notifications. */
#ifndef NDEBUG
			evt = ATOMIC_READ(GDBThread_AsyncNotifStopEvents);
			for (;;) {
				assertf(evt != NULL,
				        "Missing stop notification for thread %p",
				        thread);
				if (evt->tse_thread == thread)
					break;
				evt = evt->tse_next;
			}
#endif /* !NDEBUG */
			return false;
		}
		/* Check if the stop event already has an associated reason.
		 * If so,  then we  can't assign  its initial  reason  here! */
		if (evt->tse_reason != NULL) {
			evt->tse_next = GDBThread_Stopped;
			GDBThread_Stopped = evt;
			return false;
		}
		/* Assign the initial reason to this thread. */
		{
			struct gdb_thread_stop_event_with_reason *event_with_reason;
			event_with_reason = container_of(evt, struct gdb_thread_stop_event_with_reason, e);
			event_with_reason->r.dtr_signo  = 0;
			event_with_reason->r.dtr_reason = DEBUGTRAP_REASON_NONE;
			evt->tse_reason = &event_with_reason->r;
		}
		/* Add the event to the chain of pending async stop events. */
		ATOMIC_WRITE(evt->tse_mayresume, GDB_THREAD_MAYRESUME_STOP);
		{
			GDBThreadStopEvent *next;
			do {
				next = ATOMIC_READ(GDBThread_AsyncNotifStopEvents);
				evt->tse_next = next;
			} while (!ATOMIC_CMPXCH_WEAK(GDBThread_AsyncNotifStopEvents, next, evt));
			if (!next)
				sig_broadcast(&GDBThread_AsyncNotifStopEventsAdded);
		}
		/* Also wake up the thread so it can start trying to become the GDB host thread. */
		sig_broadcast(&evt->tse_sigresume);
	} else {
		struct cpu *target_cpu;
		/* The complicated case:
		 * - The CPU  that is  hosting `thread'  has been  suspended while  running
		 *   some other thread and has now been locked to only ever allow execution
		 *   of that other thread.
		 * - In this case, we have to:
		 *   #1: Enqueue an async RPC onto `thread', that will call `GDBThread_StopRPCImpl()'
		 *   #2: Talk to the CPU that is hosting `thread', and have it have over its scheduling
		 *       override to `thread', thus allowing the RPC to run.
		 *        - This can easily be done by simply posting an IPI request
		 *   #3: Within said RPC, create the Stop notification descriptor (the same way that
		 *       `GDBThread_StopRPCImpl()' does this)
		 *   #4: hand scheduling control back to the thread that had the scheduling override
		 *       before.
		 *   #5: Resume execution here, and eventually return from
		 *      `GDBThread_CreateMissingAsyncStopNotification()'
		 */
		target_cpu = thread->t_cpu;
		/* Special case: If the target is our own host  CPU, then we ourself are the  ones
		 *               holding the scheduling override, also meaning that there wouldn't
		 *               be a whole-cpu stop event for our own CPU, and also meaning  that
		 *               we shouldn't send an IPI to ourself. */
		if (target_cpu == GDBServer_Host->t_cpu) {
			COMPILER_BARRIER();
			/* TODO: Don't directly access `thiscpu_sched_override'! */
			FORCPU(target_cpu, thiscpu_sched_override) = thread;
			COMPILER_BARRIER();
			GDB_DEBUG("[gdb] Send Stop RPC to with %p ("
			          "%" PRIuN(__SIZEOF_PID_T__) "."
			          "%" PRIuN(__SIZEOF_PID_T__) ") "
			          "[async]\n",
			          thread,
			          task_getrootpid_of(thread),
			          task_getroottid_of(thread));
			/* Very important: Set  the  HIGH_PRIORITY flag,  thus ensuring
			 *                 that we immediately switch over to `thread',
			 *                 allowing it to run as the new override. */
			if (!task_rpc_exec(thread,
			                   RPC_CONTEXT_KERN |
			                   RPC_SYNCMODE_F_ALLOW_ASYNC |
			                   RPC_PRIORITY_F_HIGH,
			                   &GDBThread_StopWithAsyncNotificationRPC,
			                   GDBServer_Host)) {
				COMPILER_BARRIER();
				FORCPU(target_cpu, thiscpu_sched_override) = GDBServer_Host;
				COMPILER_BARRIER();
				return false; /* The thread has already exited... */
			}
			COMPILER_BARRIER();
			assert(FORCPU(target_cpu, thiscpu_sched_override) == GDBServer_Host);
			goto done;
		}

		/* Send an IPI to the target CPU */
		{
			void *args[CPU_IPI_ARGCOUNT];
			args[0] = thread;
			while (!cpu_sendipi(target_cpu, &GDBThread_StopWithAsyncNotificationIPI, args,
			                    CPU_IPI_FWAKEUP | CPU_IPI_FWAITFOR))
				task_pause();
		}

		/* Wait until the target thread has been explicitly stopped. */
		while (!GDBThread_IsStoppedExplicitly(thread)) {
			task_connect_for_poll(&GDBThread_StopWithAsyncNotificationIPI_Done);
			if (GDBThread_IsStoppedExplicitly(thread)) {
				task_disconnectall();
				break;
			}
			if (!task_waitfor_norpc_nx())
				task_disconnectall();
		}
		/* Check if the operation may have failed because the thread has terminated. */
		if (GDBThread_HasTerminated(thread))
			return false;
	}
done:
	return true;
}


/* Stop/Resume execution of the given thread
 * Note that when `GDBThread_IsNonStopModeActive' is false, `GDBThread_Resume()' becomes
 * a no-op, and  the thread  will not  be resumed until  the current  GDB session  ends.
 * @return: true:  Successfully stopped the given thread, or the given thread was already stopped.
 * @return: false: The given thread has already terminated and can no longer be stopped. */
INTERN NONNULL((1)) bool
NOTHROW(FCALL GDBThread_Stop)(struct task *__restrict thread,
                              bool generateAsyncStopEvents) {
	if (GDBThread_IsStopped(thread)) {
		/* Make sure that  the thread is  explicitly stopped, in  case
		 * it was implicitly stopped by a whole-cpu stop event before. */
		if (GDBThread_FindStopEvent(thread))
			ATOMIC_OR(thread->t_flags, TASK_FGDB_STOPPED);
		else {
			if (generateAsyncStopEvents)
				GDBThread_CreateMissingAsyncStopNotification(thread);
		}
		return true; /* Already stopped */
	}
	GDB_DEBUG("[gdb] Send Stop RPC to with %p ("
	          "%" PRIuN(__SIZEOF_PID_T__) "."
	          "%" PRIuN(__SIZEOF_PID_T__) ")\n",
	          thread,
	          task_getrootpid_of(thread),
	          task_getroottid_of(thread));
	if (!task_rpc_exec(thread,
	                   RPC_CONTEXT_KERN |
	                   RPC_SYNCMODE_F_ALLOW_ASYNC |
	                   RPC_PRIORITY_F_HIGH,
	                   &GDBThread_StopRPC,
	                   (void *)(uintptr_t)(generateAsyncStopEvents
	                                       ? GDBTHREAD_STOPRPCIMPL_F_SETREASON
	                                       : 0)))
		return false; /* The given `thread' has already terminated. */
	/* If the thread hasn't been started yet, do so now
	 * (so that it immediately jumps into our stop RPC) */
	if (!(ATOMIC_READ(thread->t_flags) & TASK_FSTARTED))
		task_start(thread);
	/* Until until `GDBThread_StoppedAdded' has fully stopped. */
	while (!GDBThread_IsStopped(thread)) {
		task_connect_for_poll(&GDBThread_StoppedAdded);
		if (GDBThread_IsStopped(thread)) {
			task_disconnectall();
			break;
		}
		if (!task_waitfor_norpc_nx())
			task_disconnectall();
	}
	return true;
}

/* Stop/Resume execution of the given thread
 * Note that when `GDBThread_IsNonStopModeActive' is false, `GDBThread_Resume()' becomes
 * a no-op, and  the thread  will not  be resumed until  the current  GDB session  ends. */
INTERN NONNULL((1)) void
NOTHROW(FCALL GDBThread_Resume)(struct task *__restrict thread) {
	GDBThreadStopEvent **piter, *iter;
	if (!GDBThread_IsStoppedExplicitly(thread))
		return; /* Already resumed */
	/* NOTE: We ignore resume() request for suspended threads
	 *       with pending async stop notifications, since the
	 *       remote GDB doesn't know about them, yet. */
	piter = &GDBThread_Stopped;
	for (; (iter = *piter) != NULL; piter = &iter->tse_next) {
		if (iter->tse_thread != thread)
			continue;
		if (iter->tse_isacpu) {
			ATOMIC_AND(iter->tse_thread->t_flags, ~TASK_FGDB_STOPPED);
			break; /* whole-cpu stop events are resumed later. */
		}
		assert(iter->tse_mayresume == GDB_THREAD_MAYRESUME_NASYNC);
		*piter = iter->tse_next;
		/* Resume this thread. */
		GDBThread_ResumeSingleStopEvent(iter);
		break;
	}
}

LOCAL WUNUSED NONNULL((1)) bool
NOTHROW(FCALL decref_if_not_destroy)(struct task *__restrict thread) {
	refcnt_t refcnt;
	do {
		refcnt = ATOMIC_READ(thread->t_refcnt);
		assert(refcnt != 0);
		if (refcnt == 1)
			return false;
	} while (!ATOMIC_CMPXCH_WEAK(thread->t_refcnt, refcnt, refcnt - 1));
	return true;
}


/* Same as above, but stop/resume every thread apart of the process that `thread' is apart of. */
INTERN NONNULL((1)) void
NOTHROW(FCALL GDBThread_StopProcess)(struct task *__restrict thread,
                                     bool generateAsyncStopEvents) {
	struct procctl *ctl;
	struct taskpid *iter;
	if (GDBThread_IsAllStopModeActive && !generateAsyncStopEvents)
		return;
	if (GDBThread_IsKernelThread(thread)) {
		GDB_DEBUG("[gdb] TODO: Stop all kernel threads\n");
		return;
	}
	ctl = task_getprocctl_of(thread);
	/* FIXME: Must use a  timeout here, and  switch to all-stop  mode
	 *        in case one of the already stopped threads is currently
	 *        holding this lock. */
again_threads:
	procctl_thrds_acquire(ctl);
	FOREACH_procctl_thrds(iter, ctl) {
		REF struct task *pt;
		pt = taskpid_gettask(iter);
		if (!pt)
			continue;
		if (GDBThread_IsStoppedExplicitly(pt)) {
			if (decref_if_not_destroy(pt))
				continue;
			procctl_thrds_break(ctl);
			decref_likely(pt);
			goto again_threads;
		}
		/* Must stop this thread! */
		procctl_thrds_break(ctl);
		GDBThread_Stop(pt, generateAsyncStopEvents);
		decref_unlikely(pt);
		goto again_threads;
	}
	procctl_thrds_release(ctl);
	{
		REF struct task *proc;
		proc = task_getproc_of(thread);
		if (proc) {
			FINALLY_DECREF_UNLIKELY(proc);
			GDBThread_Stop(proc, generateAsyncStopEvents);
		}
	}
}

INTERN NONNULL((1)) void
NOTHROW(FCALL GDBThread_ResumeProcess)(struct task *__restrict thread) {
	GDBThreadStopEvent **piter, *iter;
	GDB_DEBUG("[gdb] GDBThread_ResumeProcess(%p(%u))\n",
	          thread, task_getrootpid_of(thread));
	piter = &GDBThread_Stopped;
	if (GDBThread_IsKernelThread(thread)) {
again_piter_kern:
		for (; (iter = *piter) != NULL; piter = &iter->tse_next) {
			if (!GDBThread_IsKernelThread(iter->tse_thread))
				continue; /* Different process. */
			if (iter->tse_isacpu) {
				ATOMIC_AND(iter->tse_thread->t_flags, ~TASK_FGDB_STOPPED);
				continue; /* whole-cpu stop events are resumed later. */
			}
			/* Unlink the stop event */
			assert(iter->tse_mayresume == GDB_THREAD_MAYRESUME_NASYNC);
			*piter = iter->tse_next;
			/* Resume this thread. */
			GDBThread_ResumeSingleStopEvent(iter);
			goto again_piter_kern;
		}
	} else {
		struct taskpid *procpid;
again_piter:
		procpid = task_getprocpid_of(thread);
		for (; (iter = *piter) != NULL; piter = &iter->tse_next) {
			if (task_getprocpid_of(iter->tse_thread) != procpid)
				continue; /* Different process. */
			if (iter->tse_isacpu) {
				ATOMIC_AND(iter->tse_thread->t_flags, ~TASK_FGDB_STOPPED);
				continue; /* whole-cpu stop events are resumed later. */
			}
			/* Unlink the stop event */
			assert(iter->tse_mayresume == GDB_THREAD_MAYRESUME_NASYNC);
			*piter = iter->tse_next;
			/* Resume this thread. */
			GDBThread_ResumeSingleStopEvent(iter);
			goto again_piter;
		}
	}
}


/* Find   and  return  the  stop  event  for  `thread'
 * If the thread hasn't been stopped, or has a pending
 * async  stop  notification,  return  NULL   instead. */
INTERN NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) GDBThreadStopEvent *
NOTHROW(FCALL GDBThread_FindStopEvent)(struct task const *__restrict thread) {
	GDBThreadStopEvent *result;
	for (result = GDBThread_Stopped; result;
	     result = result->tse_next) {
		if (result->tse_thread == thread)
			break;
	}
	return result;
}


/* Same  as  `GDBThread_FindStopEvent()', but  unlink  the event
 * from the chain of stopped threads. (The caller is responsible
 * for re-adding the thread back to said chain at a later  point
 * in time)
 * This can be used to exclude specific threads from calls to
 * `GDBThread_ResumeEverything()', which is something that is
 * required for implementing full `vCont' support. */
INTERN WUNUSED NONNULL((1)) GDBThreadStopEvent *
NOTHROW(FCALL GDBThread_PopStopEvent)(struct task *__restrict thread) {
	GDBThreadStopEvent **presult, *result;
	for (presult = &GDBThread_Stopped; (result = *presult) != NULL;
	     presult = &result->tse_next) {
		if (result->tse_thread == thread) {
			*presult = result->tse_next;
			break;
		}
	}
	return result;
}



/* Same   as  `GDBThread_PopStopEvent()',  but   return  a  chain  of
 * stop  events (with the last one being stored in `*plastevent') for
 * all stopped threads that are apart of the same process as `thread' */
INTERN WUNUSED NONNULL((1, 2)) GDBThreadStopEvent *
NOTHROW(FCALL GDBThread_PopStopEventProcess)(struct task *__restrict thread,
                                             GDBThreadStopEvent **__restrict plastevent) {
	GDBThreadStopEvent *result, **pnext, *last;
	GDBThreadStopEvent *iter, **piter;
	if (GDBThread_IsAllStopModeActive) {
		*plastevent = NULL;
		return NULL;
	}
	result = NULL;
	last   = NULL;
	pnext  = &result;
	if (GDBThread_IsKernelThread(thread)) {
		piter  = &GDBThread_Stopped;
		while ((iter = *piter) != NULL) {
			if (!GDBThread_IsKernelThread(iter->tse_thread)) {
				piter = &iter->tse_next;
				continue; /* Different process. */
			}
			*piter = iter->tse_next;
			*pnext = iter;
			pnext = &iter->tse_next;
		}
	} else {
		struct taskpid *procpid;
		procpid = task_getprocpid_of(thread);
		piter  = &GDBThread_Stopped;
		while ((iter = *piter) != NULL) {
			if (task_getprocpid_of(iter->tse_thread) != procpid) {
				piter = &iter->tse_next;
				continue; /* Different process. */
			}
			*piter = iter->tse_next;
			*pnext = iter;
			pnext = &iter->tse_next;
		}
	}
	*pnext      = NULL;
	*plastevent = last;
	return result;
}


PRIVATE ssize_t
NOTHROW(FCALL GDBThread_CreateMissingEventForThreadCallback)(void *UNUSED(arg),
                                                             struct task *__restrict thread) {
	bool didCreate;
	didCreate = GDBThread_CreateMissingAsyncStopNotification(thread);
	return didCreate ? 1 : 0;
}


/* Stop  execution in all threads by sending async RPCs to every
 * running thread on the system, and having them report back via
 * the `GDBThread_AsyncNotifStopEvents' chain.
 * Essentially, this function does:
 * >> GDBThread_StopAllCpus();
 * >> FOREACH(thread IN System.AllThreads) {
 * >>     GDBThread_CreateMissingAsyncStopNotification(thread);
 * >> }
 * @return: * : The total number of newly created async thread events. */
INTERN size_t
NOTHROW(FCALL GDBThread_StopAllAndGenerateAsyncStopEvents)(void) {
	size_t result;
	GDBThread_StopAllCpus();
	result = (size_t)GDBThread_Enumerate(&GDBThread_CreateMissingEventForThreadCallback,
	                                     NULL);
	return result;
}



/* Check if the given `thread' is considered to be a kernel thread */
INTERN NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) bool
NOTHROW(FCALL GDBThread_IsKernelThread)(struct task const *__restrict thread) {
	if (task_getroottid_of(thread) == 0)
		return true;
	if (task_getrootpid_of(thread) == 0)
		return true;
	return false;
}



DECL_END

#endif /* !GUARD_MODGDBSERVER_THREAD_C */
