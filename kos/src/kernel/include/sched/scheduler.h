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
#ifndef GUARD_KERNEL_INCLUDE_SCHED_SCHEDULER_H
#define GUARD_KERNEL_INCLUDE_SCHED_SCHEDULER_H 1

#include <kernel/compiler.h>

#include <kernel/types.h>
#include <hybrid/sequence/list.h>
#include <sched/pertask.h>
#include <sched/tsc.h>

/* Scheduler control/context variables. */

/* Scheduler behavior:
 *
 *  =====================<<< tsc_deadline_passed() >>>=====================
 *    >> // NOTE: This is the preemptive interrupt handler!
 *    >> CALLER = THIS_TASK;
 *    >> if (thiscpu_sched_override) {
 *    >>     assert(thiscpu_sched_override == CALLER);
 *    >>     SWITCH_TO(CALLER);
 *    >> }
 *    >> NOW = ktime();
 *    >>again:
 *    >> NEXT = THIS_CPU.thiscpu_scheduler.s_running;
 *    >> NEXT_PRIORITY = NEXT.this_stoptime;
 *    >> FOREACH_thiscpu_waiting(thread, me) {
 *    >>     if (thread.this_sched_timeout > NOW)
 *    >>         break; // No more threads that have timed out.
 *    >>     if unlikely(thread.this_stoptime > NEXT_PRIORITY)
 *    >>         break; // Thread priority too low for a wake-up
 *    >>     sched_intern_unlink_from_waiting(me, thread);
 *    >>     thread.t_flags |= TASK_FRUNNING | TASK_FTIMEOUT;
 *    >>     sched_intern_add_to_runqueue(me, thread);
 *    >>     goto again;
 *    >> }
 *    >> DEADLINE = NOW + (NOW - NEXT_PRIORITY) / THIS_CPU.thiscpu_scheduler.s_runcount;
 *    >> if (CALLER != NEXT) {
 *    >>     DEADLINE = NOW + CLAMP(DEADLINE - NOW, sched_quantum_min, sched_quantum_max);
 *    >>     CALLER.this_activetime += NOW - CALLER.this_stoptime;
 *    >>     CALLER.this_stoptime    = NOW; // This will also update the position in `thiscpu_sched_threads'
 *    >>     NEXT.this_stoptime      = NOW; // This (should) position `NEXT' just after `CALLER'
 *    >> } else {
 *    >>     if (THIS_CPU.thiscpu_scheduler.s_runcount == 1)
 *    >>         DEADLINE = INFINITE;
 *    >> }
 *    >> // Check if we should cut the quantum short due to a sleeping thread.
 *    >> FOREACH_thiscpu_waiting(thread, me) {
 *    >>     if unlikely(thread.this_sched_timeout >= DEADLINE)
 *    >>         break; // No sleeping thread will time out before our quantum ends
 *    >>     // Check if the thread will have a greater priority than `NEXT' when it times out.
 *    >>     ktime_t distance = DEADLINE - thread.this_sched_timeout;
 *    >>     ktime_t my_priorty_then = MAX(NEXT_PRIORITY - distance, 0);
 *    >>     ktime_t ot_priorty_then = thread.this_stoptime + distance;
 *    >>     if (ot_priorty_then > my_priorty_then) {
 *    >>         DEADLINE = thread.this_sched_timeout;
 *    >>         break;
 *    >>     }
 *    >> }
 *    >> TSC_DEAD = ktime_future_to_tsc(DEADLINE);
 *    >> if (TSC_DEAD == TSC_MAX) {
 *    >>     tsc_nodeadline();
 *    >> } else {
 *    >>     TSC_NOW = tsc_deadline(TSC_DEAD);
 *    >>     if (TSC_NOW >= TSC_DEAD) { // Already expired...
 *    >>         CALLER = NEXT;
 *    >>         NOW    = tsc_now_to_ktime(TSC_NOW);
 *    >>         goto again;
 *    >>     }
 *    >> }
 *    >> SWITCH_TO(NEXT);
 *
 */

#ifdef __CC__
DECL_BEGIN

struct cpu;
struct task;

typedef LIST_ENTRY(task) _sched_link_t;

/* Min/max bounds for how long a quantum can be.
 *
 * These  values are required  since the length of  a quantum is calculated
 * dynamically,  and is based on how long  a thread has already waiting for
 * something  to happen, meaning that these limits are necessary to prevent
 * a  rouge thread from sleeping for a  couple of hours, then proceeding to
 * go  into an infinite  loop ala `for(;;) {}'. Since  the normal length of
 * a quantum directly reflects how long a thread has been waiting for, this
 * would mean that the system may remain unresponsive for quite some  time.
 *
 * Similarly, the quantum minimum is needed in a situation where there  are
 * hundreds upon thousands of threads running, to the point where the  time
 * the kernel needs to switch from one thread to another would already make
 * up most, if not all of the time a single thread is assigned.
 *
 * NOTE: These values are measured in nano-seconds.
 * Also note that `sched_quantum_max' only applies for non-infinite quanta,
 * and that `sched_quantum_min' doesn't apply to short delays as the result
 * of accounting to the timeouts of sleeping threads. */
DATDEF ktime_t sched_quantum_min;
DATDEF ktime_t sched_quantum_max;

/* Delay before a CPU (other than the boot CPU)
 * is  shut  down  in  order  to  save  energy. */
DATDEF ktime_t sched_shutdown_delay;


/* [lock(PRIVATE(THIS_CPU))]
 * Linked-list node for other threads. Used internally by scheduling. */
DATDEF ATTR_PERTASK REF _sched_link_t this_sched_link;
#define KEY__this_sched_link(thread) FORTASK(thread, this_sched_link)

/* [lock(PRIVATE(THIS_TASK))][valid_if(!TASK_FRUNNING)]
 * Timeout for when this thread should resume execution
 * by setting `TASK_FRUNNING | TASK_FTIMEOUT'. */
DATDEF ATTR_PERTASK ktime_t this_sched_timeout;

/* [1..1][lock(PRIVATE(THIS_CPU))] The currently running thread. */
DATDEF ATTR_PERCPU struct task *thiscpu_sched_current;

LIST_HEAD(task_runlist, REF task);
struct scheduler {
	/* Thread chains:
	 *
	 *   s_running  ──[NEXT...]─> s_running_last    (Sorted ascendingly by `this_stoptime')
	 *                               │
	 *       ┌─────────NEXT──────────┘
	 *       v
	 *   s_waiting  ──[NEXT...]─> s_waiting_last    (Sorted ascendingly by `this_sched_timeout')
	 *
	 * NOTE: Backwards links (via `this_sched_pself')
	 *       exist  everywhere  within  this   chain.
	 */
	struct task_runlist s_running;      /* [1..1] Chain of running threads (there is always at least 1 running thread!)
	                                     * This chain  is sorted  ascendingly by  `this_stoptime'. The  IDLE thread  is
	                                     * automatically added when no other threads are available.
	                                     * NOTE: Whenever  the IDLE thread  is loaded, it's `this_sched_link.le_prev'
	                                     *       will be non-NULL (also: when the IDLE thread's TASK_FRUNNING flag is
	                                     *       set, then you may also assume that the IDLE thread is loaded) */
	struct task        *s_running_last; /* [1..1] Last thread that is still running (equal to `s_running' when `s_runcount == 1')
	                                     * The NEXT-pointer of this thread is equal to s_waiting. */
	size_t              s_runcount;     /* [!0] # of running threads. (== COUNT(s_running->[NEXT...]->s_running_last)) */
#if 0 /* Only exits as `FORTASK(s_running_last, this_sched_link)' (use `scheduler_s_waiting' to access!) */
	struct task        *s_waiting;      /* [0..1][== FORTASK(s_running_last, this_sched_link)] Chain of waiting thread.
	                                     * This chain is sorted ascendingly by `this_sched_timeout'. */
#endif
	struct task        *s_waiting_last; /* [0..1] Last waiting thread. (i.e. the thread with the greatest  timeout,
	                                     * which usually ends up being the infinite timeout, i.e. `KTIME_INFINITE') */
};

#define scheduler_s_waiting(self) \
	FORTASK((self)->s_running_last, this_sched_link.le_next)


/* [lock(PRIVATE(THIS_CPU))] The scheduler for the associated CPU */
DATDEF ATTR_PERCPU struct scheduler thiscpu_scheduler;




/* The CPU's  IDLE  thread  (inlined into  the  CPU  structure)
 * This is the thread that's  running whenever the CPU  doesn't
 * have anything else to do, and as such can be used to measure
 * CPU  load by calculating the active time of this thread over
 * a period of time.
 * Also note that this thread has the lowest, possible  priority,
 * in  that  it will  only ever  be scheduled  (and only  ever be
 * reachable from the  CPU's chain of  active threads) when  this
 * is the _ONLY_ thread using the associated CPU that is actively
 * running. */
DATDEF ATTR_PERCPU struct task thiscpu_idle;

/* Alias for `FORCPU(&bootcpu, thiscpu_idle)' */
DATDEF struct task bootidle;


/* Enumerate all (running+sleeping) threads of the given CPU
 * WARNING: The CPU's IDLE thread may or may not be enumerated!
 *          The IDLE thread is only  enumerated if it has  been
 *          scheduled before, but has yet to unschedule itself. */
#define FOREACH_thiscpu_threads(iter, me)                                       \
	for ((iter) = LIST_FIRST(&FORCPU(me, thiscpu_scheduler.s_running)); (iter); \
	     (iter) = LIST_NEXT_P(iter, KEY__this_sched_link))

/* Enumerate all running threads of the given CPU */
#define FOREACH_thiscpu_running(iter, me)                               \
	for ((iter) = LIST_FIRST(&FORCPU(me, thiscpu_scheduler.s_running)); \
	     (iter) != scheduler_s_waiting(&FORCPU(me, thiscpu_scheduler)); \
	     (iter) = LIST_NEXT_P(iter, KEY__this_sched_link))

/* Enumerate all sleeping threads of the given CPU */
#define FOREACH_thiscpu_waiting(iter, me)                                      \
	for ((iter) = scheduler_s_waiting(&FORCPU(me, thiscpu_scheduler)); (iter); \
	     (iter) = LIST_NEXT_P(iter, KEY__this_sched_link))



#ifndef CONFIG_NO_SMP
/* [0..1][lock(APPEND(ATOMIC), CLEAR(ATOMIC && THIS_CPU))]
 * [CHAIN(KEY__thiscpu_pending_next)]
 * Chain of tasks that are pending for being  executed.
 * This chain is loaded by the CPU itself, which can be
 * provoked by another CPU calling `cpu_wake()' */
DATDEF ATTR_PERCPU WEAK REF struct task *thiscpu_sched_pending;

/* Key for iterating a chain of pending threads. */
#define KEY__thiscpu_pending_next(thread) FORTASK(thread, this_sched_link.le_next)

/* Enumerate all pending threads of the given CPU */
#define FOREACH_thiscpu_sched_pending(iter, me)              \
	for ((iter) = FORCPU(me, thiscpu_sched_pending); (iter); \
	     (iter) = KEY__thiscpu_pending_next(iter))

/* Add `thread' to the chain of threads that are pending to be loaded by `target_cpu'
 * The caller should follow this up with a call to `cpu_wake(target_cpu)' in order to
 * request that `target_cpu' load its chain of pending threads. */
FUNDEF NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL sched_intern_addpending)(struct cpu *__restrict target_cpu,
                                       /*inherit*/ REF struct task *__restrict thread);

/* Load a chain of pending threads
 * @return: * : The thread with which to continue execution. */
FUNDEF NOBLOCK NOPREEMPT ATTR_RETNONNULL WUNUSED NONNULL((1, 2, 3)) struct task *
NOTHROW(FCALL sched_intern_loadpending)(struct cpu *__restrict me,
                                        struct task *__restrict caller,
                                        /*inherit*/ REF struct task *__restrict chain);
#endif /* !CONFIG_NO_SMP */

/* Wake-up a thread associated with the current CPU
 * @return: * : The thread with which to continue execution. */
FUNDEF NOBLOCK NOPREEMPT ATTR_RETNONNULL WUNUSED NONNULL((1, 2, 3)) struct task *
NOTHROW(FCALL sched_intern_localwake)(struct cpu *__restrict me,
                                      struct task *__restrict caller,
                                      struct task *__restrict thread,
                                      __BOOL high_priority);

/* Add a new (running) thread to the current CPU.
 * @return: * :  The new thread with which to continue execution. */
FUNDEF NOBLOCK NOPREEMPT ATTR_RETNONNULL WUNUSED NONNULL((1, 2, 3)) struct task *
NOTHROW(FCALL sched_intern_localadd)(struct cpu *__restrict me,
                                     struct task *__restrict caller,
                                     /*inherit*/ REF struct task *__restrict thread,
                                     __BOOL high_priority);

/* Yield execution to some other thread, returning the thread to which to switch.
 * If  it  is  impossible  to   yield  to  anyone,  simply  re-return   `caller'. */
FUNDEF NOBLOCK NOPREEMPT ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) struct task *
NOTHROW(FCALL sched_intern_yield)(struct cpu *__restrict me,
                                  struct task *__restrict caller);

/* Same as `sched_intern_yield()', but ensure that `caller' doesn't get  re-returned.
 * Additionally, this function will unlink `caller' from the run-queue, and if  doing
 * so were to cause the run queue to become empty, then the IDLE thread will be added
 * to the run queue, as well as be returned.
 * Note that it is illegal to call this function as the IDLE thread! */
FUNDEF NOBLOCK NOPREEMPT ATTR_RETNONNULL NONNULL((1, 2)) struct task *
NOTHROW(FCALL sched_intern_yield_onexit)(struct cpu *__restrict me,
                                         /*out*/ REF struct task *__restrict caller);



/* [0..1][lock(PRIVATE(THIS_CPU))]
 * [if(!= NULL, [== FORCPU(., thiscpu_sched_current)])]
 * A scheduling override for this CPU. When non-NULL, the specified thread
 * must be the  calling thread,  in which case  the caller  will never  be
 * preempted until this field is once again set to NULL. Note however that
 * this variable should not be written directly, but rather through use of
 * `sched_override_start()' and `sched_override_end()', which will account
 * for the TSC deadline and the like automatically. */
DATDEF ATTR_PERCPU struct task *thiscpu_sched_override;

/* Acquire/release the scheduler override lock for the calling  CPU,
 * thereby effectively seizing control over  the calling CPU to  the
 * point where regular scheduling mechanism will not let the calling
 * thread hand over control to anyone else:
 *   - task_yield()
 *   - task_wake()
 *   - tsc_deadline_passed()
 *
 * Note that this is quite similar to disabling preemption,  however
 * many cases exist where disabling preemption is overkill, or maybe
 * even be counter-productive  (i.e. certain functionality  requires
 * that preemption remain enabled, such as disk-, user-, or network-
 * I/O)
 *
 * Another similar mechanism  is to set  the TASK_FKEEPCORE flag  for
 * one's own thread, which, while not getting set explicitly by these
 * functions,  is implicitly  set whenever  a thread  is a scheduling
 * override.
 *
 * Note that other CPUs will continue to run normally, meaning that
 * these functions would only seize complete control of the  system
 * when `cpu_count == 1'
 *
 * NOTE: These functions can be called both with and without preemption
 *       enabled, however `sched_override_yieldto()' may only be called
 *       when preemption is enabled, additionally leaving this check up
 *       to the caller by only repeating it as an internal assertion.
 *
 * HINT: When a scheduler override  is active, the scheduler's  preemptive
 *       interrupt handler will not modify the currently set TSC deadline,
 *       leaving that facility up for use by the caller!
 *
 * WARNING: These function do not operate recursively. Calling...
 *     ... `sched_override_start()' with  `thiscpu_sched_override != NULL'  isn't  allowed
 *     ... `sched_override_end()' with `thiscpu_sched_override == NULL' also isn't allowed
 * @return: * : The CPU that the calling thread managed to seize (same as `THIS_CPU') */
FUNDEF NOBLOCK ATTR_RETNONNULL struct cpu *NOTHROW(FCALL sched_override_start)(void);
FUNDEF NOBLOCK void NOTHROW(FCALL sched_override_end)(void);

/* While the caller is holding a scheduler override, pass over that
 * privilege to `thread', and continue execution in the context  of
 * that thread.
 * This  function will only  return when `thread'  switches back to the
 * caller's thread, or when `thread', or whoever it passes the override
 * to ends up calling `sched_override_end()'
 * NOTE: This function must be called with preemption enabled.
 *       Otherwise,  an  internal assertion  check  will fail.
 * NOTE: When `thread == THIS_TASK', this function behaves as a no-op
 *       In this case, the function doesn't assert that preemption is
 *       enabled when called.
 * NOTE: The caller must ensure that `thread' has the `TASK_FRUNNING'
 *       flag set (meaning that `thread' must be apart of the current
 *       CPU's run-queue). */
FUNDEF NONNULL((1)) void
NOTHROW(FCALL sched_override_yieldto)(struct task *__restrict thread);

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
FUNDEF BLOCKING void FCALL sched_super_override_start(void) THROWS(E_WOULDBLOCK, ...);
FUNDEF NOBLOCK void NOTHROW(FCALL sched_super_override_end)(__BOOL release_sched_override DFL(1));

/* Same as `sched_super_override_start()', but fail and return
 * `false' if  the  lock  can't be  acquired  at  the  moment. */
FUNDEF NOBLOCK WUNUSED __BOOL NOTHROW(FCALL sched_super_override_trystart)(void);

/* Check  if a super override is active. As far as data races go, this function will
 * only ever return `true' after `sched_super_override_start()' has returned, but is
 * not restricted to only returning `true' for the thread holding the super-override
 * system lock, meaning that it can also be used from within IPIs send to other CPUs
 * where a completely different thread is the one who engaged the super-override. */
FUNDEF NOBLOCK ATTR_PURE __BOOL NOTHROW(FCALL sched_super_override_active)(void);

DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_SCHED_SCHEDULER_H */
