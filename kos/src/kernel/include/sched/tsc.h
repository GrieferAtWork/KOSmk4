/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_INCLUDE_SCHED_TSC_H
#define GUARD_KERNEL_INCLUDE_SCHED_TSC_H 1

#include <kernel/compiler.h>

#include <kernel/types.h>

#include <bits/os/timespec.h>

#define __SIZEOF_TSC_T__    8
#define __SIZEOF_TSC_HZ_T__ 8
#define __SIZEOF_KTIME_T__  8

#ifdef __CC__
DECL_BEGIN

/* Kernel timestamp counter.
 * This is a per-cpu counter that continuously increments at a
 * monotonous rate (but is reset when the CPU goes into deep sleep).  */
typedef u64 tsc_t;
#define TSC_MAX __UINT64_MAX__

/* TODO: Intel manuals state a minimum realtime before rdtsc overflows.
 *       Using this, once can calculate the max HZ with which rdtsc ticks.
 *       If this HZ fits into 32-bit, proceed as follows:
 *       Research the max HZ with which the LAPIC timer is allowed to tick.
 *       If this value also fits into 32-bit, then change `tsc_hz_t' to be
 *       a 32-bit value on x86! */
typedef u64 tsc_hz_t;

/* Time (in Nano seconds == 1/1000000000 (1/1_000_000_000) seconds)
 * since the system was booted (s.a. `boottime')
 * NOTE: 64 bits is enough to keep this counter from overflowing for
 *       almost 600 years (so don't worry too much about overflows) */
typedef u64 ktime_t;

/* The best approximation currently known in regards to the TSC
 * frequency of this CPU. This frequency should approximately be
 * the same on all CPUs, and shouldn't change too much as time
 * goes on. However minor adjustments may be made in order to
 * deal with drifts and inaccuracies. Also: the actual HZ may
 * be a floating point number, and this value can only ever be
 * as good of an approximation as we can manage to calculate.
 *
 * NOTE: The value of this variable may only change when preemption
 *       is enabled, at which point low-level, arch-specific code
 *       may set-up a periodic interrupt handler who's purpose is
 *       to occasionally re-sync the realtime() clock, as well as
 *       make minor adjustments to the TSC_HZ.
 *
 * HINT: HZ = ticks_per_second. */
DATDEF ATTR_PERCPU tsc_hz_t thiscpu_tsc_hz;

/* Read and return the current timestamp counter of the calling CPU.
 * The base-line of the returned counter is the calling CPU being
 * booted, or more precisely: some point in time during before the
 * CPU completed its low-level, arch-specific startup initialization.
 * This function may only be called with preemption disabled. */
FUNDEF NOPREEMPT NOBLOCK WUNUSED NONNULL((1)) tsc_t
NOTHROW(FCALL tsc_get)(struct cpu *__restrict me);

/* Set the TSC deadline, that is: the point in time when `tsc_interrupt()'
 * should be called by low-level, arch-specific code. This function,
 * alongside `tsc_get()' form the basis for timing-based scheduling on KOS.
 * NOTE: A previously set deadline is overwritten by later calls to this
 *       function. If a previous deadline has expired in the mean time,
 *       then `tsc_interrupt()' may or may not be called once the caller
 *       re-enables preemption.
 * @return: * :          The timestamp at the time of the deadline being set.
 * @return: >= deadline: The given `deadline' has already expired.
 * @return: < deadline:  Successfully set the new deadline. */
FUNDEF NOPREEMPT NOBLOCK NONNULL((1)) tsc_t
NOTHROW(FCALL tsc_deadline)(struct cpu *__restrict me,
                            tsc_t deadline);

/* Return the currently set deadline. */
FUNDEF NOBLOCK NONNULL((1)) tsc_t
NOTHROW(FCALL tsc_getdeadline)(struct cpu *__restrict me);

/* Disable the TSC deadline, such that it will never trigger (or at the
 * very least: won't trigger until in a couple of months or something
 * like that...)
 * After this function is called, `tsc_getdeadline()' will return `TSC_MAX' */
FUNDEF NOPREEMPT NOBLOCK NONNULL((1)) void
NOTHROW(FCALL tsc_nodeadline)(struct cpu *__restrict me);

/* Interrupt handler callback for `tsc_deadline()'.
 * This function is called from arch-specific code as the result of a
 * previously set deadline, and will be invoked no sooner than the point
 * in time when `tsc_get() >= deadline'
 * @return: * : The new thread to which to switch contexts.
 *              The caller is responsible to assign this thread
 *              to `FORCPU(me, thiscpu_sched_current)' * */
FUNDEF NOPREEMPT NOBLOCK ATTR_RETNONNULL NONNULL((1, 2)) struct task *
NOTHROW(FCALL tsc_deadline_passed)(struct cpu *__restrict me,
                                   struct task *__restrict caller,
                                   tsc_t now);

/* Interrupt handler for implementing realtime() re-syncing.
 * This function should call `tsc_resync_realtime()' to retrieve the
 * current realtime, as read from some external clock-source that can
 * be relied upon, at which point it should calculate the delta and
 * relative error with the kernel's TSC-based idea of what realtime
 * should be.
 * @param: new_ktime: The new RTC time (as returned by `tsc_resync_realtime()') */
FUNDEF NOPREEMPT NOBLOCK void
NOTHROW(FCALL tsc_resync_interrupt)(ktime_t new_ktime);

#ifndef CONFIG_NO_SMP
/* Perform the initial TSC resync for the calling CPU.
 * This function will also calculate and set the initial TSC deadline.*/
FUNDEF NOPREEMPT NOBLOCK NONNULL((1)) void
NOTHROW(FCALL tsc_resync_init)(struct cpu *__restrict me);
#endif /* !CONFIG_NO_SMP */

/* Retrieve the current realtime, as read from an external clock source.
 * This function's implementation is arch-specific, and should only be
 * called from within `tsc_resync_interrupt()' in order to determine the
 * actual current realtime timestamp. */
FUNDEF NOPREEMPT NOBLOCK ktime_t NOTHROW(FCALL tsc_resync_realtime)(void);

/* The max error by which `tsc_resync_realtime()' may be off. */
DATDEF ktime_t const tsc_realtime_err;


/* Convert a given `tsc' value into the corresponding ktime offset. */
FUNDEF NOBLOCK NOPREEMPT WUNUSED NONNULL((1)) ktime_t
NOTHROW(FCALL tsc_to_ktime)(struct cpu *__restrict me,
                            tsc_t tsc);

/* Same as `tsc_to_ktime()', but the caller guaranties that `now' is an actual
 * timestamp that elapsed in the near past. Unlike `tsc_to_ktime()', this function
 * is allowed to assume that `now >=' any previously passed value for `now', since
 * the CPU was last initialized, also allowing it to move the internal TSC-to-KTIME
 * baseline forwards in order to account for offset overflows. */
FUNDEF NOBLOCK NOPREEMPT WUNUSED NONNULL((1)) ktime_t
NOTHROW(FCALL tsc_now_to_ktime)(struct cpu *__restrict me,
                                tsc_t now);

/* Convert a given `kt' timestamp into its TSC equivalent.
 * When `kt' lies so far into the future that TSC would overflow, return `TSC_MAX' instead.
 * NOTE: It is assumed that return >= <any `now' ever passed to `tsc_now_to_ktime'> */
FUNDEF NOBLOCK NOPREEMPT WUNUSED NONNULL((1)) tsc_t
NOTHROW(FCALL ktime_future_to_tsc)(struct cpu *__restrict me,
                                   ktime_t kt);

/* Same as `ktime_future_to_tsc()', but make no assumptions on `kt' being in the future.
 * NOTE: When `kt' lies in the past of `tsc_to_ktime(me, 0)', `0' is returned instead. */
FUNDEF NOBLOCK NOPREEMPT WUNUSED NONNULL((1)) tsc_t
NOTHROW(FCALL ktime_to_tsc)(struct cpu *__restrict me,
                            ktime_t kt);

/* Convert a ktime offset (read: not an absolute timestamp) to the equivalent # of TSC units. */
FUNDEF NOBLOCK NOPREEMPT WUNUSED NONNULL((1)) tsc_t
NOTHROW(FCALL ktime_offset_to_tsc)(struct cpu *__restrict me,
                                   ktime_t num_nanoseconds);

/* Convert a tsc offset (read: not an absolute tick value) to the equivalent # of nanoseconds. */
FUNDEF NOBLOCK NOPREEMPT WUNUSED NONNULL((1)) ktime_t
NOTHROW(FCALL tsc_offset_to_ktime)(struct cpu *__restrict me,
                                   tsc_t num_ticks);

/* Return the current kernel time (in nano seconds since `boottime')
 * WARNING: The results of this function may be inconsistent when called
 *          from different CPUs (CPU#2 may return a lower value after CPU#1
 *          already returned a greater value)
 *          If this is a problem, you should instead use `ktime_stable()',
 *          but not that for timeouts and the like, the scheduler uses `ktime()'
 * NOTE: This function is the same as doing `tsc_now_to_ktime(tsc_now())'
 *       while having preemption disabled. */
FUNDEF NOBLOCK WUNUSED ktime_t NOTHROW(KCALL ktime)(void);

/* Same as `ktime()', but ensure that the `return >= <any-previous-return>' */
FUNDEF NOBLOCK WUNUSED ktime_t NOTHROW(KCALL ktime_stable)(void);

#define ktime_with_cpu(me) tsc_now_to_ktime(me, tsc_get(me))

/* [const] Initial timestamp of when this thread started. */
DATDEF ATTR_PERTASK ktime_t this_starttime;

/* [lock(PRIVATE(THIS_CPU))]
 * Timestamp of the last time this thread was last preempted.
 * Used to implement thread priorities, where a thread with the
 * lowest `this_stoptime' will be the one to get executed next.
 *
 * For the current thread, this is indicates the point in time
 * since when the caller has ran uninterrupted. */
DATDEF ATTR_PERTASK ktime_t this_stoptime;

/* [lock(PRIVATE(THIS_CPU))] Total time this thread spent being active. */
DATDEF ATTR_PERTASK ktime_t this_activetime;

/* Timestamp of when the kernel was booted. */
DATDEF struct timespec const boottime;

#define task_getstarttime(thread) \
	ktime_to_timespec(FORTASK(thread, this_starttime))

/*
 * Special thread timers, and how to calculate them:
 *
 *  - Real time since thread was original started:
 *    ktime() - this_starttime
 *
 *  - Real time since the current quantum started:
 *    ktime() - this_stoptime   (only for THIS_TASK)
 *
 *  - Real time spent waiting to be executed:
 *    ktime() - this_stoptime   (only for NOT THIS_TASK)
 *
 *  - Real time spent being active:
 *    this_activetime + (ktime() - this_stoptime)   (for THIS_TASK)
 *    this_activetime                               (for NOT THIS_TASK)
 *    -> This value can also be summed between multiple threads
 *       to calculate active times of processes or other thread
 *       groups.
 *
 * NOTE: All of these timers use nanosecond precision!
 */

/* Convert a given ktime timestamp into a `struct timespec'.
 * This is done by adding `boottime' to the given value. */
FUNDEF NOBLOCK WUNUSED ATTR_PURE struct timespec
NOTHROW(FCALL ktime_to_timespec)(ktime_t t);

/* Convert a given `struct timespec' into a ktime timestamp.
 * This is done by subtracting `boottime' from the given value.
 * NOTE: When the given timestamp `t' points at, or before `boottime',
 *       then this function will return `0', as it is impossible to
 *       represent a ktime-timestamp that happened before the system
 *       goto booted.
 * NOTE: When the given `t' is located so far ahead of `boottime' that
 *       the return value would overflow, the value is clamed to the
 *       maximum possible value of `(ktime_t)-1' */
FUNDEF NOBLOCK WUNUSED ATTR_PURE NONNULL((1)) ktime_t
NOTHROW(FCALL timespec_to_ktime)(struct timespec const *__restrict t);

#ifdef __cplusplus
extern "C++" {
FUNDEF NOBLOCK WUNUSED ATTR_PURE ktime_t
NOTHROW(FCALL timespec_to_ktime)(struct timespec const &__restrict t)
	ASMNAME("timespec_to_ktime");
} /* extern "C++" */
#endif /* __cplusplus */


#ifndef __realtime_defined
#define __realtime_defined 1
/* Returns the current real time derived from the current CPU time.
 * WARNING: KOS only gives a best-effort guaranty for this function
 *          in terms of consistency when it comes to the calling
 *          thread being moved to a different CPU.
 *          There is a chance that minor inconsistencies in terms
 *          of exact nano-second values returned by this function
 *          when the calling thread is moved.
 * However, it is guarantied that (so long as `settimeofday()' isn't
 * called), calling this function repeatedly from the threads hosted
 * by the same CPU will _always_ return values such that later values
 * are >= earlier values. */
FUNDEF NOBLOCK WUNUSED struct timespec NOTHROW(KCALL realtime)(void);
#endif /* !__realtime_defined */


DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_SCHED_TSC_H */
