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
#ifndef GUARD_KERNEL_SRC_SCHED_SUPER_OVERRIDE_C
#define GUARD_KERNEL_SRC_SCHED_SUPER_OVERRIDE_C 1

#include <kernel/compiler.h>

#ifndef CONFIG_NO_SMP
#include <kernel/except.h>
#include <kernel/fpu.h>
#include <sched/cpu.h>
#include <sched/scheduler.h>
#include <sched/sig.h>
#include <sched/task.h>

#include <hybrid/sched/preemption.h>

#include <assert.h>
#include <atomic.h>
#include <stddef.h>

DECL_BEGIN

/* [lock(ATOMIC)] The CPU that is holding the super-override lock. (if any)
 * Setting this field to one's own CPU  is the first step of acquiring  the
 * super override lock. */
PRIVATE ATTR_COLDBSS struct cpu *super_override_cpu = NULL;

/* Signal  broadcast  when  the super  override  is released.
 * This signal will cause IPIs to be sent to every other CPU,
 * informing them that they may resume normal execution. */
PRIVATE ATTR_COLDBSS struct sig super_override_release = SIG_INIT;

/* [lock(SUPER_OVERRIDE)] Set to true while a super-override is active.
 * Only set to true once everyone has acknowledged the override itself. */
PRIVATE ATTR_COLDBSS bool super_override_active = false;

/* [lock(SUPER_OVERRIDE)] Set to true while waiting for a super-lock to be released. */
PRIVATE ATTR_COLDBSS bool super_override_unlocking = false;

/* [lock(ATOMIC)] # of CPUs currently suspended as the result of a super override. */
PRIVATE ATTR_COLDBSS WEAK unsigned int super_override_ack = 0;


/* Arch-specific wrapper for `super_override_ipi()' that does the equivalent of:
 * >> struct cpu *me;
 * >> me     = sched_override_start();
 * >> state  = UPGRADE_ICPUSTATE_TO_SCPUSTATE(state);
 * >> PERTASK_SET(this_sstate, state);
 * >> sched_super_override_ipi();
 * >> sched_override_end();
 * >> state = PERTASK_GET(this_sstate);
 * >> state = DOWNGRADE_SCPUSTATE_TO_ICPUSTATE(state);
 * >> if (FORCPU(me, thiscpu_sched_current) != THIS_TASK)
 * >>     return CPU_IPI_MODE_SWITCH_TASKS;
 * >> return state; */
INTDEF NOBLOCK NOPREEMPT ATTR_COLDTEXT NONNULL((1, 2)) struct icpustate *
NOTHROW(FCALL arch_sched_super_override_ipi)(struct icpustate *__restrict state,
                                             void *args[CPU_IPI_ARGCOUNT]);

/* Callback invoked by `arch_sched_super_override_ipi()' */
INTERN NOBLOCK NOPREEMPT ATTR_COLDTEXT void
NOTHROW(FCALL sched_super_override_ipi)(void) {
	struct task_connections cons;

	/* Report that we can now be considered to be suspended. */
	atomic_inc(&super_override_ack);

	/* Preserve active connections, so we don't interfere with
	 * signals that may have been connected by the thread that
	 * we're hi-jacking. */
	task_pushconnections(&cons);

	/* Ensure  that our  CPU's current  FPU state  is written to
	 * memory, thus allowing the super-override holder to modify
	 * the associated thread's FPU registers. */
#ifdef CONFIG_HAVE_FPU
	fpustate_savecpu();
#endif /* CONFIG_HAVE_FPU */

	/* Make sure that other IPIs also get handled!
	 * This is important because HW-IPIs may only be send when there  aren't
	 * any pending SW-IPIs, meaning that we wouldn't get the memo if we were
	 * to wait for other CPUs while there are still more pending SW-IPIs! */
	cpu_ipi_service_nopr();

	/* Re-enable  preemption  (our caller  will have
	 * already made us our CPU's scheduler override,
	 * so  we won't get  preempted by other threads) */
	PREEMPTION_ENABLE();

	while (atomic_read(&super_override_cpu) != NULL) {
		/* Wait for `super_override_release' */
		task_connect_for_poll(&super_override_release);
		if unlikely(atomic_read(&super_override_cpu) == NULL) {
			task_disconnectall();
			break;
		}

		/* Wait for the other thread, but don't service
		 * RPCs, or  allow  exceptions  to  be  thrown. */
		if (!task_waitfor_norpc_nx())
			task_disconnectall();
	}

	/* Disable preemption once again. */
	PREEMPTION_DISABLE();

	/* Restore old connections. */
	task_popconnections();

	/* Report that we've resumed execution. */
	atomic_dec(&super_override_ack);
}

PRIVATE BLOCKING_IF(force) ATTR_COLDTEXT bool FCALL
sched_super_override_start_impl(bool force)
		THROWS(E_WOULDBLOCK, ...) {
	struct cpu *me;
	bool was_already_override;
	assert(!task_wasconnected());
	assert(!super_override_active);

	/* Start by acquiring the regular scheduler override. */
	{
		preemption_flag_t was;
		preemption_pushoff(&was);
		me  = THIS_CPU;
		was_already_override = FORCPU(me, thiscpu_sched_override) != NULL;
		preemption_pop(&was);
	}
	if (!was_already_override)
		me = sched_override_start();

again:
	/* Now try to acquire the super-override lock. */
	while (!atomic_cmpxch(&super_override_cpu, NULL, me)) {
		if (!force) {
			if (!was_already_override)
				sched_override_end();
			return false;
		}

		/* Some other CPU  already acquired the  lock.
		 * When this happens, then we must simply wait
		 * for the lock to be released. */
		task_connect(&super_override_release);
		if (atomic_cmpxch(&super_override_cpu, NULL, me)) {
			task_disconnectall();
			break;
		}
		TRY {
			task_waitfor();
		} EXCEPT {
			/* Make sure to release the normal scheduler override. */
			if (!was_already_override)
				sched_override_end();
			RETHROW();
		}
	}

	/* Wait for a previous SUPER-lock to be fully released. */
	if unlikely(atomic_read(&super_override_unlocking)) {
		atomic_write(&super_override_cpu, NULL);
		sig_broadcast(&super_override_release);
		/* Wait for another thread to finish releasing the SUPER-lock. */
		do {
			preemption_tryyield();
		} while (atomic_read(&super_override_unlocking));
		goto again;
	}

	/* So now that we've got the scheduler override lock, we need to
	 * broadcast an IPI to all other CPUs, telling them to stop what
	 * they're doing and  wait until our  caller releases the  super
	 * override lock. */
	assert(atomic_read(&super_override_ack) == 0);

	{
		void *args[CPU_IPI_ARGCOUNT];
		unsigned int count;
		/* Broadcast an IPI to all other CPU, and force them to wake up. */
		count = cpu_broadcastipi_notthis(&arch_sched_super_override_ipi, args,
		                                 CPU_IPI_FWAKEUP | CPU_IPI_FWAITFOR);
		/* Wait until all other CPUs have acknowledged the request. */
		while (atomic_read(&super_override_ack) < count)
			preemption_tryyield();
	}

	/* We've successfully acquired the super-lock! */
	atomic_write(&super_override_active, true);
	return true;
}


/* Start/End a scheduler override super-lock, which behaves similar to regular
 * scheduler overrides, but will simultaneously  cause all other CPUs to  also
 * suspend execution, such  that the caller  will end up  as the only  running
 * thread on the entire system.
 *
 * Note  that in order to do something  like this, preemption must be enabled,
 * since other CPUs can only receive super-override-suspend requests when they
 * have preemption enabled, meaning that if 2 CPUs were to call this  function
 * at the same time, one  of them would have to  wait for the other's  suspend
 * IPI, which in turn requires preemption to be enabled for both.
 *
 * So as a result, a function like this one can only be implemented safely
 * by forcing the  caller to  have preemption enabled  before calling  it.
 *
 * Also note that other exceptions may also be thrown by this function, since
 * it also services synchronous RPCs for the calling thread, meaning that  it
 * behaves as a cancellation point.
 *
 * NOTES:
 *   - This function also sets the calling  thread as a scheduler override  for
 *     their current CPU through use of `sched_override_start()', meaning  that
 *     the  caller can pass  control over the super  override to another thread
 *     by using  `sched_override_yieldto()', in  which case  that other  thread
 *     must either switch to yet another thread via `sched_override_yieldto()',
 *     or  has to call  `sched_super_override_end()' in order  to end the super
 *     override.
 *   - IPIs  and device interrupts  continue to function  normally when a super
 *     override is held, and will be executed in the context of whatever thread
 *     was suspended when the super-override request was made.
 *   - For simplicity sake, you don't have to worry about CPUs that weren't  online
 *     at the time  a call  to `sched_super_override_start()' was  made, since  all
 *     CPUs are forced to come online by this function (with the suspended  threads
 *     also setting their  TASK_FKEEPCORE flags, thus  preventing their  respective
 *     CPUs from being shut down until the super-override lock is dropped), meaning
 *     that no race exists where a CPU may be brought online while a super-override
 *     lock is in place.
 *   - The super-override lock is mainly meant for debugging purposes, and may  be
 *     used  to implement facilities such as `kmalloc_leaks()', or the GDB driver.
 *     Note that the builtin debugger uses its own, separate mechanism in order to
 *     deal with more corner-cases.
 *   - The scheduling of other CPUs can  be directly altered while a  super-override
 *     is active, such that the caller may  view and alter the `this_sstate' of  any
 *     thread of any  other CPU (including  `thiscpu_sched_current', which  normally
 *     wouldn't be allowed), as well as change `thiscpu_sched_current' itself, which
 *     will cause the other  CPU to resume  execution in the  context of that  other
 *     thread once the super-override CPU calls `sched_super_override_end()'
 *   - Only the CPU that originally called `sched_super_override_start()' may eventually
 *     call `sched_super_override_end()' to  release the super  override lock. In  other
 *     words: You can't send an IPI to have another CPU release the lock for you!
 *   - When acquiring a  super-lock, if  the caller wasn't  already the  scheduling
 *     override for this current CPU, they will automatically become that override.
 *
 * WARNING: These functions aren't recursive. Calling `sched_super_override_start'
 *          when a super override is already  active results in kernel panic,  and
 *          calling  `sched_super_override_end'  when no  override is  active also
 *          results in panic.
 *
 * @param: release_sched_override: When  non-zero,  also  call   `sched_override_end()'
 *                                 Note   that   `sched_override_start()'   is   called
 *                                 unconditionally  by  `sched_super_override_start()',
 *                                 unless `thiscpu_sched_override' was already non-NULL
 *                                 before  `sched_super_override_start()'  was  called. */
PUBLIC BLOCKING ATTR_COLDTEXT void FCALL
sched_super_override_start(void) THROWS(E_WOULDBLOCK, ...) {
	sched_super_override_start_impl(true);
}

/* Same as `sched_super_override_start()', but fail and return
 * `false' if  the  lock  can't be  acquired  at  the  moment. */
PUBLIC NOBLOCK ATTR_COLDTEXT WUNUSED bool
NOTHROW(FCALL sched_super_override_trystart)(void) {
	return sched_super_override_start_impl(false);
}

PUBLIC NOBLOCK ATTR_COLDTEXT void
NOTHROW(FCALL sched_super_override_end)(bool release_sched_override) {
	assert(super_override_active);
	assert(super_override_cpu == THIS_CPU);
	assert(PERCPU(thiscpu_sched_override) == THIS_TASK);

	/* Set the override-unlocking flag. */
	atomic_write(&super_override_unlocking, true);

	/* Clear the override-active flag. */
	atomic_write(&super_override_active, false);

	/* Clear the super-override CPU field, and indicate
	 * to suspended CPUs that execution may now resume. */
	atomic_write(&super_override_cpu, NULL);
	sig_broadcast(&super_override_release);

	/* Wait for all CPUs to acknowledge resuming execution. */
	while (atomic_read(&super_override_ack) != 0)
		preemption_tryyield();

	/* Clear the override-unlocking flag.
	 * This  flag  is needed  to prevent  `super_override_ack' from
	 * being incremented by some other CPU immediately re-acquiring
	 * another super-lock. */
	atomic_write(&super_override_unlocking, false);

	if (release_sched_override)
		sched_override_end();
}

/* Check  if a super override is active. As far as data races go, this function will
 * only ever return `true' after `sched_super_override_start()' has returned, but is
 * not restricted to only returning `true' for the thread holding the super-override
 * system lock, meaning that it can also be used from within IPIs send to other CPUs
 * where a completely different thread is the one who engaged the super-override. */
PUBLIC NOBLOCK ATTR_COLDTEXT ATTR_PURE bool
NOTHROW(FCALL sched_super_override_active)(void) {
	return super_override_active;
}


DECL_END
#endif /* !CONFIG_NO_SMP */

#endif /* !GUARD_KERNEL_SRC_SCHED_SUPER_OVERRIDE_C */
