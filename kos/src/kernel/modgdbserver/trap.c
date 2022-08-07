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
#ifndef GUARD_MODGDBSERVER_TRAP_C
#define GUARD_MODGDBSERVER_TRAP_C 1
#define _KOS_SOURCE 1

/* Implementation of `GDBServer_Trap(I|S|U|K|L|F)CpuState' */

#include <kernel/compiler.h>

#include <debugger/config.h>
#include <debugger/entry.h>
#include <debugger/hook.h>
#include <debugger/io.h>
#include <kernel/debugtrap.h>
#include <kernel/except.h>
#include <kernel/fpu.h>
#include <kernel/panic.h>
#include <sched/cpu.h>
#include <sched/sig.h>
#include <sched/task.h>

#include <hybrid/atomic.h>

#include <assert.h>
#include <stddef.h>

#include "gdb.h"
#include "server.h" /* GDB_Main() */

DECL_BEGIN

/* `true'   if  `GDB_Main()'   was  called   in  non-stop   mode  (`false'  otherwise)
 * When  in non-stop mode, `GDBThread_IsStopped()' only returned true for threads that
 * have previously been suspended, and `GDBThread_Stop()' and `GDBThread_Resume()' are
 * no longer no-ops.
 * You may call `GDBThread_StopAllCpus()' to set `GDBThread_IsNonStopModeActive = false'
 * and  continue  in  all-stop  mode  until  the  next  vCont-  (or  similar)   command. */
INTERN bool GDBThread_IsNonStopModeActive = true;



/* [0..1][lock(PRIVATE(<GDB_HOST_THREAD>))]
 * Chain of stopped threads (always includes the GDB host thread)
 * May be `NULL' if called from the GDB fallback host thread,  in
 * response to the GDB remote sending a command. */
INTERN GDBThreadStopEvent *GDBThread_Stopped = NULL;

/* [0..1][lock(append(ATOMIC), remove(<GDB_HOST_THREAD>))]
 * Chain of pending async stop notifications */
INTERN GDBThreadStopEvent *GDBThread_AsyncNotifStopEvents = NULL;

/* Signal broadcast when `GDBThread_AsyncNotifStopEvents' becomes non-empty. */
INTERN struct sig GDBThread_AsyncNotifStopEventsAdded = SIG_INIT;

/* [1..1][lock(PRIVATE(<GDB_HOST_THREAD>))]
 * The thread that is hosting the GDB server (== THIS_TASK). */
INTERN struct task *GDBServer_Host = NULL;

/* Signal broadcast when `GDBServer_Host' becomes  unlocked
 * (aka. `NULL') as  the result  of `GDB_Main()'  returning
 * Used  by `GDBServer_FallbackHost' to wait for the active
 * host  to go away in order to not constantly be connected
 * to `GDBServer_FallbackHostOnByte', which would slow down
 * remote data processing when each byte would re-awake the
 * fallback host thread. */
INTERN struct sig GDBServer_HostUnlocked = SIG_INIT;



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


#ifdef CONFIG_HAVE_KERNEL_DEBUGGER
PRIVATE void KCALL GDBServer_RecursiveEntryDebuggerMain(void) {
	dbg_printf(DBGSTR(AC_COLOR(ANSITTY_CL_WHITE, ANSITTY_CL_MAROON)
	                  "Recursive GDB trap" AC_DEFATTR "\n"));
}
#endif /* CONFIG_HAVE_KERNEL_DEBUGGER */


LOCAL NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) bool
NOTHROW(KCALL debugtrap_reason_isenabled)(struct debugtrap_reason const *__restrict self) {
	switch (self->dtr_reason) {

	case DEBUGTRAP_REASON_FORK:
		return (GDBRemote_Features & GDB_REMOTE_FEATURE_FORKEVENTS) != 0;

	case DEBUGTRAP_REASON_VFORK:
	case DEBUGTRAP_REASON_VFORKDONE:
		return (GDBRemote_Features & GDB_REMOTE_FEATURE_VFORKEVENTS) != 0;

	case DEBUGTRAP_REASON_EXEC:
		return (GDBRemote_Features & GDB_REMOTE_FEATURE_EXECEVENTS) != 0;

	case DEBUGTRAP_REASON_CLONE:
		return (GDBRemote_Features & GDB_REMOTE_FEATURE_THREADEVENTS) != 0;

	default:
		break;
	}
	return true;
}


/* Debug trap entry points. */
INTERN NOBLOCK ATTR_NOINLINE ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) void *FCALL
GDBServer_TrapCpuState(void *__restrict state,
                       struct debugtrap_reason const *__restrict reason,
                       unsigned int state_kind) {
	struct task *oldhost;
	pflag_t was_preemption_enabled;
	GDBThreadStopEvent stop_event;
	/* Special handling for message traps. (think of it as KOS's version of `OutputDebugStringA()') */
	if (reason->dtr_reason == DEBUGTRAP_REASON_MESSAGE) {
		size_t num_printed;
again_message:
		if (ATOMIC_READ(GDBServer_Features) & GDB_SERVER_FEATURE_NONSTOP) {
do_print_message_in_nonstop_mode:
			num_printed = GDBServer_PrintMessageInNonStopMode(reason->dtr_strarg,
			                                                  reason->dtr_signo);
		} else {
			stop_event.tse_thread = THIS_TASK;
			oldhost = ATOMIC_CMPXCH_VAL(GDBServer_Host, NULL, stop_event.tse_thread);
			if (oldhost != NULL) {
				if (oldhost == stop_event.tse_thread) {
					/* Message from inside of GDB? ok... */
					num_printed = GDBServer_PrintMessageInAllStopMode(reason->dtr_strarg,
					                                                  reason->dtr_signo);
				} else {
					/* Getting here means we are about to, or already had been suspended:
					 *  - GDB is configured for all-stop mode
					 *  - We are unable to acquire the host-lock, meaning some other thread
					 *    is/was already running as GDB host, and had everything suspended.
					 *  - And this ~everything~ must have/will include our own thread, too.
					 * -> Going off of this, simply try to post the message once again. */
					goto again_message;
				}
			} else {
				/* Got the GDB context lock! */
				if unlikely(ATOMIC_READ(GDBServer_Features) & GDB_SERVER_FEATURE_NONSTOP)
					goto do_print_message_in_nonstop_mode;
				RAII_FINALLY {
					ATOMIC_WRITE(GDBServer_Host, NULL);
					sig_broadcast(&GDBServer_HostUnlocked);
				};
				num_printed = GDBServer_PrintMessageInAllStopMode(reason->dtr_strarg,
				                                                  reason->dtr_signo);
			}
		}
		/* Write back the number of actually written bytes. */
		((struct debugtrap_reason *)reason)->dtr_signo = (u32)num_printed;
		return state;
	}
	/* Quick check: Is the stop event for the given reason disabled? */
	if (!debugtrap_reason_isenabled(reason))
		return state;

	task_pushconnections(&stop_event.tse_oldcon);
	stop_event.tse_thread    = THIS_TASK;
	stop_event.tse_reason    = (struct debugtrap_reason *)reason;
	stop_event.tse_state     = state;
	stop_event.tse_statekind = state_kind;
	stop_event.tse_mayresume = GDB_THREAD_MAYRESUME_STOP;
	stop_event.tse_isacpu    = 0;
	sig_init(&stop_event.tse_sigresume);
	oldhost = ATOMIC_CMPXCH_VAL(GDBServer_Host, NULL, stop_event.tse_thread);
	if (oldhost != NULL) {
		GDBThreadStopEvent *next_notif;
		if (oldhost == stop_event.tse_thread) {
			kernel_debugtraps_uninstall(&GDBServer_DebugTraps);
#ifdef CONFIG_HAVE_KERNEL_DEBUGGER
			switch (state_kind) {
			case CPUSTATE_KIND_ICPUSTATE:
				dbg_enter(&GDBServer_RecursiveEntryDebuggerMain, (struct icpustate *)state);
			case CPUSTATE_KIND_SCPUSTATE:
				dbg_enter(&GDBServer_RecursiveEntryDebuggerMain, (struct scpustate *)state);
			case CPUSTATE_KIND_UCPUSTATE:
				dbg_enter(&GDBServer_RecursiveEntryDebuggerMain, (struct ucpustate *)state);
			case CPUSTATE_KIND_KCPUSTATE:
				dbg_enter(&GDBServer_RecursiveEntryDebuggerMain, (struct kcpustate *)state);
			case CPUSTATE_KIND_LCPUSTATE:
				dbg_enter(&GDBServer_RecursiveEntryDebuggerMain, (struct lcpustate *)state);
			case CPUSTATE_KIND_FCPUSTATE:
				dbg_enter(&GDBServer_RecursiveEntryDebuggerMain, (struct fcpustate *)state);
			default: break;
			}
#endif /* CONFIG_HAVE_KERNEL_DEBUGGER */
			switch (state_kind) {
			case CPUSTATE_KIND_ICPUSTATE:
				kernel_panic((struct icpustate *)state, "Recursive GDB trap\n");
			case CPUSTATE_KIND_SCPUSTATE:
				kernel_panic((struct scpustate *)state, "Recursive GDB trap\n");
			case CPUSTATE_KIND_UCPUSTATE:
				kernel_panic((struct ucpustate *)state, "Recursive GDB trap\n");
			case CPUSTATE_KIND_KCPUSTATE:
				kernel_panic((struct kcpustate *)state, "Recursive GDB trap\n");
			case CPUSTATE_KIND_LCPUSTATE:
				kernel_panic((struct lcpustate *)state, "Recursive GDB trap\n");
			case CPUSTATE_KIND_FCPUSTATE:
				kernel_panic((struct fcpustate *)state, "Recursive GDB trap\n");
			default:
				break;
			}
			kernel_panic("Recursive GDB trap\n");
		}
		do {
			next_notif = ATOMIC_READ(GDBThread_AsyncNotifStopEvents);
			stop_event.tse_next = next_notif;
		} while (!ATOMIC_CMPXCH_WEAK(GDBThread_AsyncNotifStopEvents, next_notif, &stop_event));
		if (!next_notif)
			sig_broadcast(&GDBThread_AsyncNotifStopEventsAdded);
again_waitfor_resume:
		/* Wait until we're supposed to resume execution. */
		task_connect_for_poll(&stop_event.tse_sigresume);
		/* Do an interlocked check if  we can become the  GDB
		 * main thread, or if we should resume our execution. */
		{
			uintptr_half_t resume_state;
			resume_state = ATOMIC_READ(stop_event.tse_mayresume);
			if (resume_state == GDB_THREAD_MAYRESUME_RESUME) {
				/* Should resume execution. */
				task_disconnectall();
				goto done;
			}
		}
		task_connect_for_poll(&GDBServer_HostUnlocked);
		if (ATOMIC_CMPXCH(GDBServer_Host, NULL, stop_event.tse_thread)) {
			uintptr_half_t resume_state;
			/* Now we're the GDB host thread. */
			task_disconnectall();
			resume_state = ATOMIC_READ(stop_event.tse_mayresume);
			if (resume_state == GDB_THREAD_MAYRESUME_RESUME)
				goto done_unlock; /* Should actually resume execution. */
			if (resume_state == GDB_THREAD_MAYRESUME_NASYNC)
				goto do_become_gdb_host; /* Our async stop was already send out, so don't re-queue */
			goto do_become_gdb_host_notif;
		}
		was_preemption_enabled = PREEMPTION_PUSHON();
		if (!task_waitfor_norpc_nx())
			task_disconnectall();
		PREEMPTION_POP(was_preemption_enabled);
		{
			uintptr_half_t resume_state;
			resume_state = ATOMIC_READ(stop_event.tse_mayresume);
			if (resume_state == GDB_THREAD_MAYRESUME_RESUME)
				goto done; /* Should resume execution. */
		}
		if (ATOMIC_CMPXCH(GDBServer_Host, NULL, stop_event.tse_thread)) {
			uintptr_half_t resume_state;
			/* Now we're the GDB host thread. */
			resume_state = ATOMIC_READ(stop_event.tse_mayresume);
			if (resume_state == GDB_THREAD_MAYRESUME_RESUME)
				goto done_unlock; /* Should actually resume execution. */
			if (resume_state == GDB_THREAD_MAYRESUME_NASYNC)
				goto do_become_gdb_host; /* Our async stop was already send out, so don't re-queue */
			goto do_become_gdb_host_notif;
		}
		goto again_waitfor_resume;
	}
	/* At this point we have become the designated GDB host thread! */

	/* Add our own stop event to the set of pending async stop notifications. */
do_become_gdb_host_notif:
	/* Check if the trap reason has been disabled... */
	if (!debugtrap_reason_isenabled(reason))
		goto done_unlock;
	do {
		stop_event.tse_next = ATOMIC_READ(GDBThread_AsyncNotifStopEvents);
	} while (!ATOMIC_CMPXCH_WEAK(GDBThread_AsyncNotifStopEvents,
	                             stop_event.tse_next, &stop_event));
do_become_gdb_host:

	/* Set the `TASK_FGDB_STOPPED' flag of the host thread. */
	ATOMIC_OR(stop_event.tse_thread->t_flags, TASK_FGDB_STOPPED);

	/* Make sure that preemption is enabled while inside of GDB_Main() */
	was_preemption_enabled = PREEMPTION_PUSHON();

	/* Configure non-/all-stop mode */
	GDBThread_IsNonStopModeActive = true;
	if (!(GDBServer_Features & GDB_SERVER_FEATURE_NONSTOP))
		GDBThread_StopAllCpus();

again_gdb_main:
	/* Call the GDB main function. */
	GDB_MainWithAlternateStack();

	/* Check if we ourself are supposed to remain stopped. */
	if (stop_event.tse_mayresume != GDB_THREAD_MAYRESUME_RESUME)
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
	assertf(!GDBServer_HasStopEvent(GDBThread_Stopped, &stop_event) &&
	        !GDBServer_HasStopEvent(GDBThread_AsyncNotifStopEvents, &stop_event),
	        "Should have already been removed, because"
	        " `tse_mayresume == GDB_THREAD_MAYRESUME_RESUME'");
#endif /* !NDEBUG */

	/* Restore the old preemption behavior */
	PREEMPTION_POP(was_preemption_enabled);

done_unlock:
	/* Unlock the GDB server host lock */
	ATOMIC_WRITE(GDBServer_Host, NULL);
	sig_broadcast(&GDBServer_HostUnlocked);

done:
	task_popconnections();
	return stop_event.tse_state;
}

/* Main function for the GDB fallback host thread */
INTERN void NOTHROW(KCALL GDBFallbackHost_Main)(void) {
	for (;;) {
		if (!GDBRemote_HasPendingBytes()) {
			/* Prefer  waiting on the HOST lock, since that one doesn't get
			 * triggered as often as the DATA lock, meaning that we take up
			 * less CPU cycles if we wait for it, instead. */
			if (ATOMIC_READ(GDBServer_Host) != NULL) {
				task_connect_for_poll(&GDBServer_HostUnlocked);
				if likely(ATOMIC_READ(GDBServer_Host) != NULL) {
					task_waitfor();
					continue;
				}
				task_disconnectall();
			}
			/* Wait for the GDB remote to send data. */
			task_connect_for_poll(&GDBServer_RemoteDataAvailable);
			if (!GDBRemote_HasPendingBytes()) {
				task_waitfor();
				continue;
			}
			task_disconnectall();
		}
		/* Try to become the GDB host thread. */
		if (!ATOMIC_CMPXCH(GDBServer_Host, NULL, GDBServer_FallbackHost)) {
			task_connect(&GDBServer_HostUnlocked);
			if (!GDBRemote_HasPendingBytes()) {
				task_disconnectall();
				continue;
			}
			if (!ATOMIC_CMPXCH(GDBServer_Host, NULL, GDBServer_FallbackHost)) {
				task_waitfor();
				continue;
			}
			task_disconnectall();
		}
		if (!GDBRemote_HasPendingBytes()) {
			task_disconnectall();
			continue;
		}
		GDBThread_IsNonStopModeActive = true;
		if (!(GDBServer_Features & GDB_SERVER_FEATURE_NONSTOP))
			GDBThread_StopAllCpus();

		/* Invoke the GDB main() function. */
		GDB_MainWithAlternateStack();

		/* Resume system execution if we were in all-stop mode. */
		if (GDBThread_IsAllStopModeActive)
			GDBThread_ResumeAllCpus();
		if (!(GDBServer_Features & GDB_SERVER_FEATURE_NONSTOP))
			GDBThread_ResumeEverything();
		/* Unlock the GDB server host lock */
		ATOMIC_WRITE(GDBServer_Host, NULL);
		sig_broadcast(&GDBServer_HostUnlocked);
	}
}


/* Discard all pending async notification events. */
INTERN void
NOTHROW(FCALL GDBThread_DiscardAllAsyncNotifEvents)(void) {
	GDBThreadStopEvent *notif, *next;
	for (;;) {
		notif = ATOMIC_XCH(GDBThread_AsyncNotifStopEvents, NULL);
		if (!notif)
			break;
		while (notif) {
			next = notif->tse_next;
			assert(notif->tse_mayresume == GDB_THREAD_MAYRESUME_STOP);
			ATOMIC_WRITE(notif->tse_mayresume, GDB_THREAD_MAYRESUME_NASYNC);
			notif->tse_next   = GDBThread_Stopped;
			GDBThread_Stopped = notif;
			notif = next;
		}
	}
}

/* Restore async stop events for all currently stopped threads. */
INTERN void NOTHROW(FCALL GDBThread_RestoreAllAsyncNotifEvents)(void) {
	GDBThreadStopEvent *first, *last, **pnext, *iter, **piter;
	last = NULL;
	pnext = &first;
	piter = &GDBThread_Stopped;
continue_piter:
	for (; (iter = *piter) != NULL; piter = &iter->tse_next) {
		if (iter->tse_mayresume != GDB_THREAD_MAYRESUME_NASYNC)
			continue;
		if (iter->tse_reason == NULL) {
			/* This one was stopped manually, so no notification
			 * XXX: Is  this correct? Or should we also be sending stop notifications
			 *      for threads that were manually  stopped by GDB (I wouldn't  think
			 *      so, since that would cause problems with auto stop/resume for the
			 *      purpose of settings the registers of a running thread) */
			continue;
		}
		/* Re-enable the stop notification of this stop event. */
		ATOMIC_WRITE(iter->tse_mayresume, GDB_THREAD_MAYRESUME_STOP);
		/* Unlink from `GDBThread_Stopped' */
		*piter = iter->tse_next;
		/* Append to our chain to events to-be re-added to `GDBThread_AsyncNotifStopEvents' */
		*pnext = iter;
		pnext  = &iter->tse_next;
		/* Keep track of the last element of our new chain. */
		last   = iter;
		goto continue_piter;
	}
	if (!last)
		return;
	assert(pnext == &last->tse_next);
	/* Insert all of the re-enabled notification packets into the queue. */
	for (;;) {
		iter = ATOMIC_READ(GDBThread_AsyncNotifStopEvents);
		last->tse_next = iter;
		COMPILER_WRITE_BARRIER();
		if (!ATOMIC_CMPXCH_WEAK(GDBThread_AsyncNotifStopEvents, iter, first))
			continue;
		if (!iter)
			sig_broadcast(&GDBThread_AsyncNotifStopEventsAdded);
		break;
	}
}


/* Consume a pending async notification event, or return NULL if none are pending. */
INTERN WUNUSED GDBThreadStopEvent *
NOTHROW(FCALL GDBThread_ConsumeAsyncNotifEvent)(void) {
	GDBThreadStopEvent *notif;
again_notif:
	notif = ATOMIC_READ(GDBThread_AsyncNotifStopEvents);
	if (notif) {
		if (!ATOMIC_CMPXCH_WEAK(GDBThread_AsyncNotifStopEvents,
		                        notif, notif->tse_next))
			goto again_notif;
		assert(notif->tse_mayresume == GDB_THREAD_MAYRESUME_STOP);
		ATOMIC_WRITE(notif->tse_mayresume, GDB_THREAD_MAYRESUME_NASYNC);
		notif->tse_next   = GDBThread_Stopped;
		GDBThread_Stopped = notif;
	}
	return notif;
}






INTERN_CONST struct kernel_debugtraps const GDBServer_DebugTraps = {
	.dt_trap_ucpustate = &GDBServer_TrapUCpuState,
	.dt_trap_lcpustate = &GDBServer_TrapLCpuState,
	.dt_trap_kcpustate = &GDBServer_TrapKCpuState,
	.dt_trap_icpustate = &GDBServer_TrapICpuState,
	.dt_trap_scpustate = &GDBServer_TrapSCpuState,
	.dt_trap_fcpustate = &GDBServer_TrapFCpuState,
};

INTERN NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) struct icpustate *FCALL
GDBServer_TrapICpuState(struct icpustate *__restrict state,
                        struct debugtrap_reason const *__restrict reason) {
	return (struct icpustate *)GDBServer_TrapCpuState(state, reason, CPUSTATE_KIND_ICPUSTATE);
}

INTERN NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) struct scpustate *FCALL
GDBServer_TrapSCpuState(struct scpustate *__restrict state,
                        struct debugtrap_reason const *__restrict reason) {
	return (struct scpustate *)GDBServer_TrapCpuState(state, reason, CPUSTATE_KIND_SCPUSTATE);
}

INTERN NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) struct ucpustate *FCALL
GDBServer_TrapUCpuState(struct ucpustate *__restrict state,
                        struct debugtrap_reason const *__restrict reason) {
	return (struct ucpustate *)GDBServer_TrapCpuState(state, reason, CPUSTATE_KIND_UCPUSTATE);
}

INTERN NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) struct kcpustate *FCALL
GDBServer_TrapKCpuState(struct kcpustate *__restrict state,
                        struct debugtrap_reason const *__restrict reason) {
	return (struct kcpustate *)GDBServer_TrapCpuState(state, reason, CPUSTATE_KIND_KCPUSTATE);
}

INTERN NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) struct lcpustate *FCALL
GDBServer_TrapLCpuState(struct lcpustate *__restrict state,
                        struct debugtrap_reason const *__restrict reason) {
	return (struct lcpustate *)GDBServer_TrapCpuState(state, reason, CPUSTATE_KIND_LCPUSTATE);
}

INTERN NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) struct fcpustate *FCALL
GDBServer_TrapFCpuState(struct fcpustate *__restrict state,
                        struct debugtrap_reason const *__restrict reason) {
	return (struct fcpustate *)GDBServer_TrapCpuState(state, reason, CPUSTATE_KIND_FCPUSTATE);
}




DECL_END

#endif /* !GUARD_MODGDBSERVER_TRAP_C */
