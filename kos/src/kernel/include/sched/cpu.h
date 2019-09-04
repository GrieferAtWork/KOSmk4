/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_INCLUDE_SCHED_CPU_H
#define GUARD_KERNEL_INCLUDE_SCHED_CPU_H 1

#include <kernel/compiler.h>

#include <sched/pertask.h>

#include <hybrid/__bit.h>
#include <hybrid/typecore.h>

#include <stdbool.h>
#include <kos/jiffies.h>
#include <kos/kernel/types.h>

DECL_BEGIN

#ifdef CONFIG_NO_SMP
#   undef CONFIG_MAX_CPU_COUNT
#   define CONFIG_MAX_CPU_COUNT 1
#else /* CONFIG_NO_SMP */
/* Configuration option: The max number of CPUs supported by KOS. */
#   ifndef CONFIG_MAX_CPU_COUNT
#      define CONFIG_MAX_CPU_COUNT 16
#   elif (CONFIG_MAX_CPU_COUNT+0) <= 1
#      undef CONFIG_MAX_CPU_COUNT
#      define CONFIG_MAX_CPU_COUNT 1
#      define CONFIG_NO_SMP 1
#   endif
#endif /* !CONFIG_NO_SMP */



/* NOTE: When talking about a CPU having `work left to be done', what is meant one of these:
 *  - The CPU is hosting at least 1 thread (that isn't its IDLE thread)
 *    as part of the active chain of running tasks.
 *  - The CPU is hosting at least 1 thread with the KEEPCORE flag set, regardless
 *    of which state that thread may be in (may the thread be sleeping, or running) */

#define CPU_STATE_DREAMING       0x0000 /* The CPU is fast asleep
                                         *  - Only used by secondary cores
                                         *  - Preemptive interrupts are disabled
                                         *  - Outside interrupts are not responded to, except
                                         *    for when running on the boot CPU, where Preemption
                                         *    will remain enabled when `__hlt()' is called. */
#define CPU_STATE_FALLING_ASLEEP 0x0001 /* The CPU is currently falling asleep.
                                         *  - Preemption is disabled, but `cpu_deepwake()'
                                         *    should not stop the CPU before it has fully fallen
                                         *    asleep, or has woken up again after noticing that
                                         *    there is still work left to be done.
                                         *  - This is a transitional state used to describe an
                                         *    idling CPU that is currently checking if it is
                                         *    allowed to fall asleep.
                                         *  - During this state, preemptive interrupts are disabled,
                                         *    alongside other CPU-specific machinery being turned
                                         *    off in order to save power. */
#define CPU_STATE_RUNNING        0x0002 /* The CPU is fully up and running, hosting any number of threads. */
#define CPU_STATE_GETTING_UP     0x0003 /* An INIT IPI is being / has been send to the CPU, and the
                                         * core is currently in the process of startup up.
                                         * This state is transitioned to `CPU_STATE_RUNNING' at the end of
                                         * the internal CPU initialization phase (the i386 variant of which
                                         * is implemented in `/arch/i386/smp32.S') */


#ifndef CONFIG_NO_SMP
#define CPU_PENDING_ENDOFCHAIN (__CCAST(struct task *)(-1))
#endif

#ifdef __CC__

typedef __UINTPTR_TYPE__ cpuid_t;

struct task;
struct cpu {
	cpuid_t          c_id;       /* The ID of this CPU. */
	REF struct task *c_current;  /* [1..1][lock(PRIVATE(THIS_CPU && PREEMPTION))]
	                              * [CHAIN(->t_sched.s_running.sr_runnxt)]
	                              * The task currently being executed, as well as a linked
	                              * list of task scheduled for execution there-after. */
	REF struct task *c_sleeping; /* [0..1][lock(PRIVATE(THIS_CPU && PREEMPTION))]
	                              * [CHAIN(->t_sched.s_asleep.ss_tmonxt)]
	                              * Pointer to the next task scheduled to wake up due to a timeout.
	                              * NOTE: This chain never contains the IDLE thread, which
	                              *       must implement special handling when it comes to
	                              *       blocking waits, as implemented by `task_sleep()' */
#ifndef CONFIG_NO_SMP
	WEAK REF struct task
	                *c_pending;  /* [0..1|NULL(== CPU_PENDING_ENDOFCHAIN)]
	                              * [lock(WRITE(ATOMIC),READ(XCH(CPU_PENDING_ENDOFCHAIN)))]
	                              * [CHAIN(->t_sched.s_pending.ss_pennxt)]
	                              * Chain of tasks that are pending for being executed.
	                              * This chain is loaded by the CPU itself, which can be
	                              * provoked by another CPU calling `cpu_wake()' */
#endif /* !CONFIG_NO_SMP */
	size_t           c_heapsize; /* [const] Allocated heap size of this CPU */
	WEAK u16         c_state;    /* CPU State (one of `CPU_STATE_*') */
	u16              c_pad[(sizeof(void *)-2)/2]; /* ... */
	/* Per-CPU data goes here. */
};


#ifndef NDEBUG
FUNDEF NOBLOCK void NOTHROW(FCALL cpu_assert_integrity)(bool need_caller DFL(true));
#else /* !NDEBUG */
#define cpu_assert_integrity(need_caller) (void)0
#endif /* NDEBUG */

/* The per-cpu / global jiffies counters. */
DATDEF ATTR_PERCPU jtime_t volatile cpu_jiffies;

/* [< cpu_quantum_length]
 * A sub-quantum offset that must be added to `cpu_jiffies' in
 * order to determine the true start of the current quantum (in ticks). */
DATDEF ATTR_PERCPU quantum_diff_t volatile cpu_quantum_offset;

/* The length of a single quantum (the number of ticks
 * that need to pass before `cpu_jiffies' is incremented)
 * HINT: On x86, this the LAPIC reload value! */
DATDEF ATTR_PERCPU quantum_diff_t volatile cpu_quantum_length;

/* Returns the number of ticks that have passed since the start
 * of the current quantum. - The true current CPU-local time
 * (in ticks) can then be calculated as:
 * >> (cpu_jiffies * PERCPU(cpu_quantum_length)) + PERCPU(cpu_quantum_offset) + cpu_quantum_elapsed();
 * NOTE: The `*_nopr' variants may only be called when preemption is disabled! */
FUNDEF NOBLOCK WUNUSED quantum_diff_t NOTHROW(KCALL cpu_quantum_elapsed)(void);
FUNDEF NOBLOCK WUNUSED quantum_diff_t NOTHROW(KCALL cpu_quantum_elapsed_nopr)(void);
FUNDEF NOBLOCK WUNUSED quantum_diff_t NOTHROW(KCALL cpu_quantum_remaining)(void);
FUNDEF NOBLOCK WUNUSED quantum_diff_t NOTHROW(KCALL cpu_quantum_remaining_nopr)(void);

/* Returns the cpu-local quantum time. */
FUNDEF NOBLOCK WUNUSED qtime_t NOTHROW(KCALL cpu_quantum_time)(void);

/* Returns the global quantum time, adjusted for the calling CPU. */
FUNDEF NOBLOCK WUNUSED qtime_t NOTHROW(KCALL quantum_time)(void);

/* Convert to/from quantum time and regular timespecs */
FUNDEF NOBLOCK WUNUSED struct timespec NOTHROW(FCALL qtime_to_timespec)(qtime_t const *__restrict qtime);
FUNDEF NOBLOCK WUNUSED qtime_t NOTHROW(FCALL timespec_to_qtime)(struct timespec const *__restrict tms);

/* Convert between global (the boot cpu's) and global (the current cpu's) quantum time.
 * WARNING: Unless the caller has disabled preemption or has set the
 *          KEEPCORE flag, these functions may not operate properly.
 * @param: tmp: [quantum_local_to_global] IN:  A timestamp in per-cpu local time
 *                                        OUT: A timestamp in global system time
 * @param: tmp: [quantum_global_to_local] IN:  A timestamp in global system time
 *                                        OUT: A timestamp in per-cpu local time
 * @return: * : [quantum_local_to_global] The current global system time
 * @return: * : [quantum_global_to_local] The current per-cpu local time */
FUNDEF NOBLOCK NONNULL((1)) qtime_t NOTHROW(FCALL quantum_local_to_global)(qtime_t *__restrict tmp);
FUNDEF NOBLOCK NONNULL((1)) qtime_t NOTHROW(FCALL quantum_global_to_local)(qtime_t *__restrict tmp);

/* Increment `cpu_quantum_offset' by `diff' incrementing the `cpu_jiffies' counter
 * when the resulting value turns out to be greater than `cpu_quantum_length',
 * in which case the value will also be truncated.
 * When `cpu_jiffies' is incremented, also check if this causes additional
 * tasks to time out, and if so, re-schedule them for execution.
 * WARNING: This function may only be called when preemption is disabled!
 * @return: * : Always returns `PERCPU(cpu_quantum_length)' */
FUNDEF NOBLOCK quantum_diff_t NOTHROW(FCALL cpu_add_quantum_offset)(quantum_diff_t diff);

/* == FORCPU(&_bootcpu,cpu_jiffies)
 * The global jiffies counter, aliasing the one from the boot CPU. */
DATDEF jtime_t volatile jiffies;


/* [!0][<= CONFIG_MAX_CPU_COUNT][const] The total number of known CPUs. */
DATDEF cpuid_t const cpu_count;

#ifndef CONFIG_NO_SMP
/* Number of CPUs with a state set to `CPU_STATE_RUNNING'
 * This value is incremented when a cpu changes state to `CPU_STATE_RUNNING'
 * as the result of a call to `cpu_wake()' when an INIT IPI is used, and is
 * decremented when a cpu changes state to `CPU_STATE_DREAMING'.
 * Because the BOOT CPU can never dream, this value is always `>= 1'! */
DATDEF cpuid_t cpu_online_count;
#else /* !CONFIG_NO_SMP */
#define cpu_online_count   1
#endif /* CONFIG_NO_SMP */


#ifndef CONFIG_NO_SMP
#define task_isonlythread() \
       (__hybrid_atomic_load(cpu_online_count,__ATOMIC_ACQUIRE) <= 1 && \
        __hybrid_atomic_load(THIS_TASK->t_sched.s_running.sr_runnxt,__ATOMIC_ACQUIRE) == THIS_TASK)
#else
#define task_isonlythread() \
       (__hybrid_atomic_load(THIS_TASK->t_sched.s_running.sr_runnxt,__ATOMIC_ACQUIRE) == THIS_TASK)
#endif


/* [1..1][cpu_count] Vector of CPU descriptors.
 * NOTE: The index in this vector is the `cpu_id' of the associated CPU.
 * NOTE: `_bootcpu' always has the CPUID ZERO(0) */
DATDEF struct cpu *const cpu_vector[CONFIG_MAX_CPU_COUNT];

#if CONFIG_MAX_CPU_COUNT > BITS_PER_POINTER
DECL_END
#include <libc/string.h>
DECL_BEGIN
typedef uintptr_t cpuset_t[(CONFIG_MAX_CPU_COUNT + (BITS_PER_POINTER-1)) / BITS_PER_POINTER];
#if __SIZEOF_POINTER__ == 8
#define CPUSET_COPY(dst,src)  (void)__libc_memcpyq(dst,src,(CONFIG_MAX_CPU_COUNT + (BITS_PER_POINTER-1)) / BITS_PER_POINTER)
#define CPUSET_CLEAR(x)       (void)__libc_memsetq(x,0,(CONFIG_MAX_CPU_COUNT + (BITS_PER_POINTER-1)) / BITS_PER_POINTER)
#define CPUSET_SETFULL(x)     (void)__libc_memsetq(x,(uintptr_t)-1,(CONFIG_MAX_CPU_COUNT + (BITS_PER_POINTER-1)) / BITS_PER_POINTER)
#elif __SIZEOF_POINTER__ == 4
#define CPUSET_COPY(dst,src)  (void)__libc_memcpyl(dst,src,(CONFIG_MAX_CPU_COUNT + (BITS_PER_POINTER-1)) / BITS_PER_POINTER)
#define CPUSET_CLEAR(x)       (void)__libc_memsetl(x,0,(CONFIG_MAX_CPU_COUNT + (BITS_PER_POINTER-1)) / BITS_PER_POINTER)
#define CPUSET_SETFULL(x)     (void)__libc_memsetl(x,(uintptr_t)-1,(CONFIG_MAX_CPU_COUNT + (BITS_PER_POINTER-1)) / BITS_PER_POINTER)
#else
#define CPUSET_COPY(dst,src)  (void)__libc_memcpy(dst,src,sizeof(cpuset_t))
#define CPUSET_CLEAR(x)       (void)__libc_memset(x,0,sizeof(cpuset_t))
#define CPUSET_SETFULL(x)     (void)__libc_memset(x,0xff,sizeof(cpuset_t))
#endif
#define CPUSET_CONTAINS(x,id) ((x)[(id) / BITS_PER_POINTER] & ((uintptr_t)1 << ((id) % BITS_PER_POINTER)))
#define CPUSET_INSERT(x,id)   (void)((x)[(id) / BITS_PER_POINTER] |= ((uintptr_t)1 << ((id) % BITS_PER_POINTER)))
#define CPUSET_REMOVE(x,id)   (void)((x)[(id) / BITS_PER_POINTER] &= ~((uintptr_t)1 << ((id) % BITS_PER_POINTER)))
FORCELOCAL size_t NOTHROW(KCALL cpuset_count_impl)(cpuset_t self) {
	size_t result = 0;
	cpuid_t i;
	for (i = 0; i < cpu_count; ++i) {
		if (CPUSET_CONTAINS(self, i))
			++result;
	}
	return result;
}
#define CPUSET_COUNT(x)       cpuset_count_impl(x)
#else
typedef uintptr_t cpuset_t;
#if CONFIG_MAX_CPU_COUNT <= 1
#define __cpuset_full_mask  1
#else
#define __HAVE_CPUSET_FULL_MASK 1
DATDEF cpuset_t const __cpuset_full_mask; /* [== (1 << cpu_count) - 1] */
#endif
#define CPUSET_COPY(dst,src)  (void)((dst)=(src))
#if CONFIG_MAX_CPU_COUNT > 32
#define CPUSET_COUNT(x)       __hybrid_popcount64((u64)((x) & __cpuset_full_mask))
#elif CONFIG_MAX_CPU_COUNT > 16
#define CPUSET_COUNT(x)       __hybrid_popcount32((u32)((x) & __cpuset_full_mask))
#elif CONFIG_MAX_CPU_COUNT > 8
#define CPUSET_COUNT(x)       __hybrid_popcount16((u16)((x) & __cpuset_full_mask))
#else
#define CPUSET_COUNT(x)       __hybrid_popcount8((u8)((x) & __cpuset_full_mask))
#endif
#define CPUSET_CLEAR(x)       (void)((x)=0)
#define CPUSET_SETFULL(x)     (void)((x)=(uintptr_t)-1)
#define CPUSET_SETONE(x,id)   (void)((x)=((uintptr_t)1 << (id)))
#define CPUSET_CONTAINS(x,id) ((x) & ((uintptr_t)1 << (id)))
#define CPUSET_INSERT(x,id)   (void)((x) |= ((uintptr_t)1 << (id)))
#define CPUSET_REMOVE(x,id)   (void)((x) &= ~((uintptr_t)1 << (id)))
#endif
#ifndef CPUSET_SETONE
#define CPUSET_SETONE(x,id)  (CPUSET_CLEAR(x),CPUSET_INSERT(x,id))
#endif





DATDEF struct cpu _bootcpu;
DATDEF struct task _bootidle;
DATDEF ATTR_PERTASK struct cpu *_this_cpu;
DATDEF ATTR_PERCPU struct task _this_idle;

#ifdef CONFIG_NO_SMP
#undef THIS_CPU
#undef THIS_IDLE
#define THIS_CPU   (&_bootcpu)
#define THIS_IDLE  (&_bootidle)
#else
#ifndef THIS_CPU
#define THIS_CPU   PERTASK_GET(_this_cpu)
#endif
#ifndef THIS_IDLE
#define THIS_IDLE  (&PERCPU(_this_idle))
#endif
#endif


/* Enter deep-sleep mode on the given CPU.
 * In deep-sleep mode, no interrupts are fired and no code is executed.
 * Essentially, the CPU is offline, and can only be re-enabled by another
 * core calling `cpu_deepwake()' on the core.
 * NOTES:
 *    - This function may only ever be called a the CPU's IDLE thread
 *    - When called, it is checked if there are other running tasks.
 *      If there are, simply switch to the next one.
 *      If there are none that can continue execution, `__hlt()', but
 *      don't disable preemption, thus checking again periodically.
 *      If there are none at all, disable preemptive interrupts, as
 *      well as other hardware-specific machinery to reduce power
 *      consumption, before entering deep-sleep mode.
 *    - The BOOT cpu cannot be shut down in this manner, as it is
 *      responsible for handling interrupts.
 *      When called by the BOOT cpu's IDLE thread, the function will
 *      instead check if other threads should be run, before disabling
 *      preemptive interrupts and waiting for the next hardware interrupt,
 *      in the mean time tracking how much time has passed before then in
 *      order to update the global jiffies counter (which is identical to
 *      the counter of the boot CPU)
 *      After a hardware interrupt occurred, the process is repeated, in
 *      that the function will check for new tasks that may have shown up.
 *    - This function returns once DEEP-SLEEP ends, and the IDLE task should
 *      execute again for the first time since the last DEEP-SLEEP.
 *      For this purpose, the CPU can be woken by a call to `cpu_wake()'
 * Implementation-wise, this function will:
 *   #1 Disable preemption
 *   #2 Transition from `CPU_STATE_RUNNING' to `CPU_STATE_FALLING_ASLEEP'
 *#ifndef CONFIG_NO_SMP
 *   #3 Schedule all tasks found in `c_pending'
 *   #4 Serve all pending IPI callbacks (s.a. `cpu_sendipi()')
 *#endif
 *   #5 Check for other running tasks
 *      #5.1 If there are some, unschedule the IDLE thread and yield to the first
 *           In this case, this function will return the next time the IDLE thread
 *           will get re-scheduled.
 *   #6 Check for sleeping tasks with the KEEPCORE flag
 *      #6.1 If there are any, re-enable preemption and wait for the next
 *           preemptive interrupt before going back to step #1
 *   #7 Disable preemptive interrupts on secondary cores,
 *      or the boot core if no secondary cores are online.
 *   #8 Hand over all tasks still hosted by the CPU to another one (with the
 *      fallback hand-over target being the boot-cpu, as it can never fall asleep)
 *   #9 Disable other per-cpu hardware components to save power
 *  --- Secondary cores:
 *   #10 Change state to `CPU_STATE_DREAMING'
 *   #11 Halt execution, now only listening for INIT-IPIs send via `cpu_wake()'
 *  --- Boot CPU:
 *   #10 Halt execution until the next interrupt.
 *   #11 Disable preemption
 *   #12 Re-enable per-cpu hardware components disabled in step #9
 *   #13 If disabled in step #7, re-enable preemptive interrupts
 *   #14 Got back to step #2
 */
FUNDEF void NOTHROW(KCALL cpu_deepsleep)(void);

#ifndef CONFIG_NO_SMP
/* MUST ONLY BE CALLED FROM AN IDLE TAST!
 * This function does the following:
 * >> FORCPU(me,_this_idle).t_sched.s_state = PUSH_CPU_STATE_FOR_RETURNING_TO_CALLER();
 * >> ATOMIC_WRITE(caller->c_state,CPU_STATE_DREAMING);
 * >> PREEMPTION_DEEPHALT();
 * NOTE: Do not call this function directly. - Use `cpu_deepsleep()' instead,
 *       and even then: Only call that function from an IDLE task.
 * NOTE: When this function returns, preemption will have been re-enabled
 *       as the result of another CPU calling `cpu_wake()' on `caller'
 * NOTE: This function must not be called by the BOOT CPU!
 * With this, it is the arch-dependent portion of `cpu_deepsleep()' that performs
 * the actual deep-sleep on a multi-core system. */
FUNDEF void NOTHROW(FCALL cpu_enter_deepsleep)(struct cpu *__restrict caller);
#endif /* !CONFIG_NO_SMP */


/* Disable / re-enable preemptive interrupts on the calling CPU.
 * When `cpu_enable_preemptive_interrupts()' is called, any time that has
 * passed between then and a prior call to `cpu_disable_preemptive_interrupts()'
 * will be added to the cpu's local jiffies counter, while also configuring
 * the current quantum to be aligned with the amount of time that has passed.
 * NOTE: In case preemptive interrupts cannot be disabled,
 *       all of these these functions are no-ops.
 * NOTE: The `*_nopr' variants may only be called when preemption is disabled! */
FUNDEF NOBLOCK void NOTHROW(KCALL cpu_disable_preemptive_interrupts)(void);
FUNDEF NOBLOCK void NOTHROW(KCALL cpu_enable_preemptive_interrupts)(void);
FUNDEF NOBLOCK void NOTHROW(KCALL cpu_disable_preemptive_interrupts_nopr)(void);
FUNDEF NOBLOCK void NOTHROW(KCALL cpu_enable_preemptive_interrupts_nopr)(void);


#ifndef CONFIG_NO_SMP

/* Load all pending threads within the calling CPU.
 * NOTE: Preemption must be disabled before this function may be called!
 * @return: true:  At least 1 new task was added to the execution ring.
 * @return: false: No tasks were pending. */
FUNDEF NOBLOCK bool NOTHROW(KCALL cpu_loadpending)(void);


/* Wake up a CPU, regardless of which ever state it may be in, potentially
 * not even waking it at all, but simply sending an IPI, such that sooner
 * or later it will check its chain of pending task (`target->c_pending'),
 * causing it to load all threads found within that chain, so-as to allow
 * those tasks to continue running on it.
 * On X86, this function is implemented as:
 * >> for (;;) {
 * >>     u16 state = ATOMIC_READ(target->c_state);
 * >>     switch (state) {
 * >>     case CPU_STATE_DREAMING:
 * >>         // Take on the responsibility of waking up the CPU.
 * >>         if (!ATOMIC_CMPXCH_WEAK(target->c_state,state,CPU_STATE_GETTING_UP))
 * >>             continue;
 * >>         SEND_IPI(INIT,target);
 * >>         ATTR_FALLTHROUGH
 * >>     case CPU_STATE_GETTING_UP:
 * >>         // The CPU has been instructed to wake up / is currently waking up
 * >>         // In this state, we can be sure that (when not considering possible
 * >>         // hardware failure), it will load pending tasks after switching to
 * >>         // `CPU_STATE_RUNNING' mode.
 * >>         return;
 * >>     case CPU_STATE_FALLING_ASLEEP:
 * >>         // The CPU is currently falling asleep. - If it already went past the
 * >>         // point of checking for pending tasks, then it will switch states to
 * >>         // `CPU_STATE_DREAMING' in just a moment.
 * >>         // If it didn't and is currently loading those tasks, the state will
 * >>         // shortly change to `CPU_STATE_RUNNING'
 * >>         // In either case, wait for something to happen, but do so in a busy
 * >>         // loop, so-as to not block, fulfilling the `NOBLOCK' requirement.
 * >>         __pause();
 * >>         continue;
 * >>     case CPU_STATE_RUNNING:
 * >>         // The CPU should still be able to receive regular IPIs, so use those
 * >>         SEND_IPI(LOAD_PENDING_TASKS,target);
 * >>         // NOTE: If the CPU changed states to one where IPIs can no longer be
 * >>         //       received (aka. from `CPU_STATE_RUNNING' to `CPU_STATE_FALLING_ASLEEP'),
 * >>         //       it would have already loaded pending tasks during that transition,
 * >>         //       so regardless of the IPI actually being delivered, we know that
 * >>         //       the CPU _has_ loaded any pending tasks!
 * >>         return;
 * >>
 * >>     default:
 * >>         __builtin_unreachable();
 * >>     }
 * >>     break;
 * >> }
 */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(KCALL cpu_wake)(struct cpu *__restrict target);

/* Check if IPIs are pending to be executed by the calling CPU,
 * returning `true' if this is the case, or `false' it not.
 * In order to serve any pending IPIs, preemption must be enabled. */
FUNDEF NOBLOCK WUNUSED bool NOTHROW(KCALL cpu_hwipi_pending)(void);
/* Check if there are any non-interrupting software-based IPIs pending. */
FUNDEF NOBLOCK WUNUSED bool NOTHROW(KCALL cpu_swipi_pending)(void);

/* Service pending IPIs (must be called after a manual switch to the RUNNING state)
 * The general sequence of setting `CPU_STATE_RUNNING' looks like this:
 * >>again:
 * >>    PREEMPTION_DISABLE();
 * >>    ATOMIC_WRITE(me->c_state, CPU_STATE_FALLING_ASLEEP);
 * >>    // Check for hardware IPIs which may have been delivered after `PREEMPTION_DISABLE()'
 * >>    // was called, but bfore `CPU_STATE_FALLING_ASLEEP' got set (letting other CPUs think
 * >>    // that our CPU would be able to service IPIs)
 * >>    if (cpu_hwipi_pending()) {
 * >>        ATOMIC_WRITE(me->c_state, CPU_STATE_RUNNING);
 * >>        cpu_ipi_service();
 * >>        PREEMPTION_ENABLE_P();
 * >>        goto again;
 * >>    }
 * >>
 * >>    // Some other code
 * >>    ...
 * >>
 * >>    ATOMIC_WRITE(THIS_CPU->c_state, CPU_STATE_RUNNING);
 * >>    if (cpu_swipi_pending()) {
 * >>        cpu_ipi_service();
 * >>        PREEMPTION_ENABLE();
 * >>        goto again;
 * >>    }
 * This sequence is required, since cpu_wake() which is used to deliver IPI requests
 * to cpus in a state other than `CPU_STATE_RUNNING' (in order to allow for deep-sleep
 * wake-ups), will not trigger an IPI interrupt if there are any sw-based IPIs pending
 */
FUNDEF NOBLOCK void NOTHROW(KCALL cpu_ipi_service)(void);

/* Reset the amount of remaining time for the current quantum.
 * NOTE: The `*_nopr' variants may only be called when preemption is disabled! */
FUNDEF NOBLOCK void NOTHROW(KCALL cpu_quantum_reset)(void);
FUNDEF NOBLOCK void NOTHROW(KCALL cpu_quantum_reset_nopr)(void);

/* Adjust quantum time to track the calling thread's quantum about to end prematurely. */
FUNDEF NOBLOCK void NOTHROW(KCALL cpu_quantum_end)(void);

struct icpustate;
#endif /* !CONFIG_NO_SMP */
#endif /* __CC__ */


/* The max number of pointers that can be passed to an IPI function. */
#define CPU_IPI_ARGCOUNT  4

#ifdef __CC__
#ifndef CONFIG_NO_SMP
/* Callback for an asynchronous IPI executed by some target CPU.
 * IPIs can be handled (and thus executed) any time execution
 * in a target CPU has preemption enabled.
 * Note however that IPIs are very restricted in what they can actually
 * do when it comes to write-access. The poster-child example for the use
 * of an IPI is the TLB shoot down used by paging to invalidate old mappings
 * on other cores before associated paging data can safely be freed.
 * NOTE: IPIs are always executed with preemption disabled. - And even though
 *       IPIs are allowed to re-enable preemption, please note that doing so
 *       may lead to one IPI callback being interrupted by another.
 *       Also note that preemption is always enabled where `state' points to,
 *       unless the `CPU_IPI_FNOINTR' flag was set then the request was made.
 * @param: args: The arguments alongside which the IPI was scheduled.
 * @return: * :  The cpu state to restore, or one of `CPU_IPI_MODE_*'
 */
typedef NOBLOCK NONNULL((1, 2)) /*ATTR_NOTHROW*/struct icpustate *
(FCALL *cpu_ipi_t)(struct icpustate *__restrict state,
                   void *args[CPU_IPI_ARGCOUNT]);
#endif /* !CONFIG_NO_SMP */
#endif /* __CC__ */

/* Special return values for `cpu_ipi_t' callbacks. */
#define CPU_IPI_MODE_SPECIAL_MIN      (__CCAST(uintptr_t)(-1))
#define CPU_IPI_MODE_ISSPECIAL(x)     (__CCAST(uintptr_t)(x) >= CPU_IPI_MODE_SPECIAL_MIN)

/* Prematurely end the current quantum and switch to the next task,
 * the same way a call to `task_yield()' would have when done by the
 * code that got interrupted.
 * This is mainly used to quickly cause a thread woken by `task_wake()'
 * to resume execution when it was hosted by a different CPU before then. */
#define CPU_IPI_MODE_SWITCH_TASKS     (__CCAST(struct icpustate *)(-1))



#define CPU_IPI_FNORMAL   0x0000 /* Normal IPI delivery flags. */
#define CPU_IPI_FWAKEUP   0x0001 /* FLAG: Wake up the target CPU if it is currently in deep-sleep mode. */
#define CPU_IPI_FNOINTR   0x0002 /* FLAG: The IPI may be executed when preemption is disabled.
                                  *       When this flag is set, sending a non-blocking IPI to
                                  *       one self is allowed. */
#define CPU_IPI_FWAITFOR  0x1000 /* Wait for the target CPU to acknowledge having received the IPI,
                                  * rather than allowing the IPI to be delivered asynchronously. */


/* The size of the buffer used to contain pending IPIs. */
#ifndef CPU_IPI_BUFFER_SIZE
#define CPU_IPI_BUFFER_SIZE  256
#endif /* !CPU_IPI_BUFFER_SIZE */


/* WARNING: Sending IPIs with preemption disabled is possible, but when sending
 *          more than `CPU_IPI_BUFFER_SIZE / cpu_count' IPIs in a row, without
 *          re-enabling preemption between any of them may lead to a situation
 *          where no further IPIs can be sent to some target CPU.
 */


#ifdef __CC__
#ifndef CONFIG_NO_SMP
/* Send an IPI to a specific target CPU.
 * The sync-variant will wait for the IPI to be acknowledged and completed before continuing,
 * which is quite the expensive operation, as it requires a second follow-up IPI by the target
 * cpu, which is used for confirming the completion of an IPI.
 * @return: true:  IPI delivery successful.
 * @return: false: The IPI could not be scheduled because the target
 *                 CPU is offline, and `CPU_IPI_FWAKEUP' was not set.
 * @return: false: The target CPU's IPI buffer is full.
 *                 This can happen if the target cpu has disabled preemption,
 *                 following which at least `CPU_IPI_BUFFER_SIZE' other IPIs
 *                 had been sent to it.
 * @return: false: The target CPU's is the caller's and `CPU_IPI_FNOINTR' isn't set. */
FUNDEF NOBLOCK NONNULL((1, 2, 3)) bool
NOTHROW(KCALL cpu_sendipi)(struct cpu *__restrict target, cpu_ipi_t func,
                           void *args[CPU_IPI_ARGCOUNT], unsigned int flags);

/* Send an IPI to all CPUs apart of the given set of `targets'.
 * @return: * : The number of successfully delivered IPIs. */
FUNDEF NOBLOCK NONNULL((2, 3)) cpuid_t
NOTHROW(KCALL cpu_sendipi_cpuset)(cpuset_t targets, cpu_ipi_t func,
                                  void *args[CPU_IPI_ARGCOUNT], unsigned int flags);

/* Same as the regular IPI functions, however the IPI is broadcast to all CPUs.
 * @return: * : The number of successfully delivered IPIs. */
FUNDEF NOBLOCK NONNULL((1, 2)) cpuid_t
NOTHROW(KCALL cpu_broadcastipi)(cpu_ipi_t func, void *args[CPU_IPI_ARGCOUNT], unsigned int flags);

/* Same as `cpu_broadcastipi()', but don't send the IPI to the calling CPU. */
FUNDEF NOBLOCK NONNULL((1, 2)) cpuid_t
NOTHROW(KCALL cpu_broadcastipi_notthis)(cpu_ipi_t func, void *args[CPU_IPI_ARGCOUNT], unsigned int flags);

#endif /* !CONFIG_NO_SMP */

/* The main loop that is executed by IDLE threads. */
FUNDEF ATTR_NORETURN void NOTHROW(FCALL cpu_idlemain)(void);

/* >> void NOTHROW(KCALL func(void));
 * A function that is invoked in order to allow the kernel to self-optimize
 * whenever there is nothing else to do, before falling asleep (these functions
 * are invoked by the IDLE thread). */
#define DEFINE_IDLE_JOB(func) \
	DEFINE_CALLBACK(".rodata.callback.idle_job", func)


/* Save the current CPU context and store it in `caller->s_state'.
 * Then, switch context to `THIS_CPU->c_current' and continue by executing it.
 * NOTE: Preemption must be disabled before this function may be called!
 * NOTE: Upon return, preemption will have been re-enabled! */
FUNDEF NONNULL((1)) void NOTHROW(FCALL cpu_run_current_and_remember)(struct task *__restrict caller);

/* Similar to `cpu_run_current_and_remember()', but don't remember the caller's context.
 * This function is used to implement `task_exit()'
 * NOTE: Preemption must be disabled before this function may be called! */
FUNDEF ATTR_NORETURN void NOTHROW(FCALL cpu_run_current)(void);

#ifndef CONFIG_NO_SMP
/* Schedule `thread' as a task that is pending execution on `target'
 * NOTE: This function inherits a reference to `thread' from the caller!
 * NOTE: The caller must ensure that:
 *        - `TASK_FRUNNING' isn't set
 *        - `TASK_FPENDING' is set
 * @return: true:  Successfully schedule the task pending on `target'.
 * @return: false: The task has already been designated a role as either
 *                 pending, sleeping, or running. */
FUNDEF NOBLOCK NONNULL((1, 2)) bool
NOTHROW(FCALL cpu_addpendingtask)(struct cpu *__restrict target,
                                  /*in*/REF struct task *__restrict thread);
#endif /* !CONFIG_NO_SMP */

/* Add the given task as running / sleeping within the current CPU.
 * NOTE: These functions inherit a reference to `thread' from the caller!
 * NOTE: Preemption must be disabled before this function may be called! */
FUNDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL cpu_addrunningtask)(/*in*/REF struct task *__restrict thread);
FUNDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL cpu_addsleepingtask)(/*in*/REF struct task *__restrict thread);

/* Remove a running or sleeping task `thread' from the current CPU.
 * NOTE: These functions return with a reference to `thread' handed to the caller.
 * NOTE: Preemption must be disabled before this function may be called! */
FUNDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL cpu_delrunningtask)(/*out*/REF struct task *__restrict thread);
FUNDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL cpu_delsleepingtask)(/*out*/REF struct task *__restrict thread);


/* IDLE job prototype.
 * @param: arg:  The argument with which the job was scheduled.
 * @param: mode: One of `IDLE_JOB_MODE_*' */
typedef NOBLOCK void /*NOTHROW*/(FCALL *idle_job_t)(void *arg, unsigned int mode);
#define IDLE_JOB_MODE_SERVICE 0x0000 /* Service the IDLE job now. */
#define IDLE_JOB_MODE_CANCEL  0x0001 /* The IDLE job was canceled after when the CPU decided
                                      * that too much time has already passed since the job
                                      * being scheduled, and whatever it may have been intended
                                      * to accomplish probably won't make any sense to prolong
                                      * even further.
                                      * In this case, the function should simply perform cleanup
                                      * on the given `arg', which is likely a call to `decref()',
                                      * acompanying a prior use of `cpu_schedule_idle_job_and_incref()' */

/* Optional functions to schedule / delete jobs that should be executed
 * by the current CPU's IDLE thread the next time there is nothing to do.
 * NOTE: These functions should be used for the purposes of _HINTS_ _ONLY_!
 *       The kernel is not actually required to implement them, and when
 *       defined as no-ops that simply return `false', kernel operations
 *       must be the same as otherwise!
 * `cpu_schedule_idle_job_and_incref' is the same as `cpu_schedule_idle_job()',
 * but if the request succeeds (return == true), atomically increment a `refcnt_t'
 * field found at `arg + refcnt_offset', thus allowing the job-function to take
 * and inherit a reference to some object on which to operate.
 * @param: job:    The job to perform.
 * @param: arg:    The argument to pass to `job' when it should be executed.
 * @return: true:  Successfully scheduled the job for execution.
 *                 In this case, it is guarantied that the job will eventually
 *                 either be executed, or canceled.
 * @return: false: Failed to allocate memory for the job, or there are already too many jobs.
 * @return: false: Another IDLE job with the same `job' and `arg' had already been scheduled.
 * @return: false: The kernel has been configured to disable IDLE jobs. */
FUNDEF NOBLOCK NONNULL((1)) bool NOTHROW(FCALL cpu_schedule_idle_job)(idle_job_t job, void *arg);
FUNDEF NOBLOCK NONNULL((1)) bool NOTHROW(FCALL cpu_schedule_idle_job_and_incref)(idle_job_t job, void *arg, ptrdiff_t refcnt_offset);

/* Delete a previously schedule IDLE job before it can be serviced.
 * @return: true:  The job was unscheduled, and invoked with `IDLE_JOB_MODE_CANCEL'
 * @return: false: Either the job was never scheduled, or has already been serviced
 *                 when the CPU had some down-time between now and a prior call to
 *                `cpu_schedule_idle_job*()' */
FUNDEF NOBLOCK NONNULL((1)) bool NOTHROW(FCALL cpu_delete_idle_job)(idle_job_t job, void *arg);

/* Helper functions to schedule a simple IDLE job. */
FUNDEF NOBLOCK NONNULL((1)) bool
NOTHROW(FCALL cpu_schedule_idle_job_simple)(NOBLOCK void /*NOTHROW*/(KCALL *func)(void));


#endif /* __CC__ */

DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_SCHED_CPU_H */
