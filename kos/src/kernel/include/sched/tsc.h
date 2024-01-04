/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_INCLUDE_SCHED_TSC_H
#define GUARD_KERNEL_INCLUDE_SCHED_TSC_H 1

#include <kernel/compiler.h>

#include <kernel/types.h>

#include <bits/os/timespec.h>
#include <bits/os/timeval.h>
#include <compat/config.h>
#ifdef __ARCH_HAVE_COMPAT
#include <compat/bits/os/timespec.h>
#include <compat/bits/os/timeval.h>
#include <compat/bits/types.h>
#endif /* __ARCH_HAVE_COMPAT */


#define __SIZEOF_TSC_T__    8
#define __SIZEOF_TSC_HZ_T__ 8
#define __SIZEOF_KTIME_T__  8


/************************************************************************/
/* Generate relative ktime values from known factors.                   */

/* seconds */
#define relktime_from_seconds(n) \
	(__CCAST(ktime_t)(n) * __UINT32_C(1000000000))

/* Add milliseconds (1/1_000 seconds) */
#define relktime_from_milliseconds(n) \
	(__CCAST(ktime_t)(n) * __UINT32_C(1000000))

/* microseconds (1/1_000_000 seconds) (aka. usec (s.a. `struct timeval')) */
#define relktime_from_microseconds(n) \
	(__CCAST(ktime_t)(n) * __UINT32_C(1000))

/* nanoseconds (1/1_000_000_000 seconds) (aka. nsec (s.a. `struct timespec')) */
#define relktime_from_nanoseconds(n) \
	(__CCAST(ktime_t)(n))
/************************************************************************/


#ifdef __CC__
DECL_BEGIN

/* Kernel timestamp counter.
 * This  is  a per-cpu  counter  that continuously  increments  at a
 * monotonous rate (but is reset when the CPU goes into deep sleep). */
typedef u64 tsc_t;
#define TSC_MAX __UINT64_MAX__

/* TODO: Intel manuals state a  minimum realtime before rdtsc  overflows.
 *       Using this, one can calculate the max HZ with which rdtsc ticks.
 *       If this HZ fits into 32-bit, proceed as follows:
 *       Research the max HZ with which the LAPIC timer is allowed to tick.
 *       If this value also fits into 32-bit, then change `tsc_hz_t' to  be
 *       a 32-bit value on x86! */
typedef u64 tsc_hz_t;

/* The best approximation currently known in regards to the  TSC
 * frequency of this CPU. This frequency should approximately be
 * the same on all CPUs, and  shouldn't change too much as  time
 * goes  on. However minor  adjustments may be  made in order to
 * deal with drifts  and inaccuracies. Also:  the actual HZ  may
 * be a floating point number, and  this value can only ever  be
 * as good of an approximation as we can manage to calculate.
 *
 * NOTE: The value of this variable may only change when preemption
 *       is  enabled, at which  point low-level, arch-specific code
 *       may set-up a periodic  interrupt handler who's purpose  is
 *       to occasionally re-sync the  realtime() clock, as well  as
 *       make minor adjustments to the TSC_HZ.
 *
 * HINT: HZ = ticks_per_second. */
DATDEF ATTR_PERCPU tsc_hz_t thiscpu_tsc_hz;
/* The min/max bounds for what can be considered valid HZ values. */
DATDEF ATTR_PERCPU tsc_hz_t thiscpu_tsc_hzmin;
DATDEF ATTR_PERCPU tsc_hz_t thiscpu_tsc_hzmax;

/* Read  and return the current timestamp counter of the calling CPU.
 * The base-line of  the returned  counter is the  calling CPU  being
 * booted,  or more precisely:  some point in  time during before the
 * CPU completed its low-level, arch-specific startup initialization.
 * This function may only be called with preemption disabled. */
FUNDEF NOBLOCK NOPREEMPT WUNUSED NONNULL((1)) tsc_t
NOTHROW(FCALL tsc_get)(struct cpu *__restrict me);

/* Set the TSC deadline, that is: the point in time when `tsc_interrupt()'
 * should be  called  by  low-level, arch-specific  code.  This  function,
 * together with `tsc_get()', form  the basis for timing-based  scheduling
 * on KOS.
 * NOTE: A previously set deadline is overwritten by later calls to this
 *       function.  If a previous deadline has expired in the mean time,
 *       then `tsc_interrupt()' may or may not be called once the caller
 *       re-enables preemption.
 * @return: * :          The timestamp at the time of the deadline being set.
 * @return: >= deadline: The given `deadline' has already expired.
 * @return: < deadline:  Successfully set the new deadline. */
FUNDEF NOBLOCK NOPREEMPT NONNULL((1)) tsc_t
NOTHROW(FCALL tsc_deadline)(struct cpu *__restrict me,
                            tsc_t deadline);

/* Return the currently set deadline. */
FUNDEF NOBLOCK NONNULL((1)) tsc_t
NOTHROW(FCALL tsc_getdeadline)(struct cpu *__restrict me);

/* Disable the TSC deadline, such that it will never trigger (or at the
 * very least: won't trigger until in  a couple of months or  something
 * like that...)
 * After this function is called, `tsc_getdeadline()' will return `TSC_MAX' */
FUNDEF NOBLOCK NOPREEMPT NONNULL((1)) void
NOTHROW(FCALL tsc_nodeadline)(struct cpu *__restrict me);

/* Interrupt handler callback for `tsc_deadline()'.
 * This  function is called  from arch-specific code as  the result of a
 * previously set deadline, and will be invoked no sooner than the point
 * in time when `tsc_get() >= deadline'
 * @return: * : The  new  thread to  which to  switch contexts.
 *              The caller is responsible to assign this thread
 *              to `FORCPU(me, thiscpu_sched_current)' * */
FUNDEF NOBLOCK NOPREEMPT ATTR_RETNONNULL NONNULL((1, 2)) struct task *
NOTHROW(FCALL tsc_deadline_passed)(struct cpu *__restrict me,
                                   struct task *__restrict caller,
                                   tsc_t now);

/* Interrupt  handler   for   implementing   realtime()   re-syncing.
 * This  function should call `tsc_resync_realtime()' to retrieve the
 * current realtime, as read from some external clock-source that can
 * be relied upon, at which point  it should calculate the delta  and
 * relative error with the kernel's  TSC-based idea of what  realtime
 * should be.
 * @param: new_ktime: The new RTC time (as returned by `tsc_resync_realtime()') */
FUNDEF NOBLOCK NOPREEMPT void
NOTHROW(FCALL tsc_resync_interrupt)(ktime_t new_ktime);

/* Perform the initial TSC resync for the calling CPU.
 * This function will also calculate and set the initial TSC deadline. */
FUNDEF NOBLOCK NOPREEMPT NONNULL((1)) void
NOTHROW(FCALL tsc_resync_init)(struct cpu *__restrict me);

/* Retrieve the current realtime, as read from an external clock source.
 * This function's implementation is  arch-specific, and should only  be
 * called from within `tsc_resync_interrupt()' in order to determine the
 * actual current realtime timestamp. */
FUNDEF NOBLOCK NOPREEMPT ktime_t NOTHROW(FCALL tsc_resync_realtime)(void);

/* The max error by which `tsc_resync_realtime()' may be off. */
DATDEF ktime_t const tsc_realtime_err;


/* Convert a given `tsc' value into the corresponding ktime offset. */
FUNDEF NOBLOCK NOPREEMPT ATTR_PURE WUNUSED NONNULL((1)) ktime_t
NOTHROW(FCALL tsc_to_ktime)(struct cpu const *__restrict me,
                            tsc_t tsc);

/* Same as `tsc_to_ktime()',  but the  caller guaranties  that `now'  is an  actual
 * timestamp  that elapsed in the near past. Unlike `tsc_to_ktime()', this function
 * is allowed to assume that `now >=' any previously passed value for `now',  since
 * the CPU was last initialized, also allowing it to move the internal TSC-to-KTIME
 * baseline forwards in order to account for offset overflows. */
FUNDEF NOBLOCK NOPREEMPT WUNUSED NONNULL((1)) ktime_t
NOTHROW(FCALL tsc_now_to_ktime)(struct cpu *__restrict me,
                                tsc_t now);

/* Convert a given `kt' timestamp into its TSC equivalent.
 * When `kt' lies so far into the future that TSC would overflow, return `TSC_MAX' instead.
 * NOTE:  It  is assumed  that  return >=  <any  `now' ever  passed  to `tsc_now_to_ktime'> */
FUNDEF NOBLOCK NOPREEMPT ATTR_PURE WUNUSED NONNULL((1)) tsc_t
NOTHROW(FCALL ktime_future_to_tsc)(struct cpu const *__restrict me,
                                   ktime_t kt);

/* Same as `ktime_future_to_tsc()', but make no assumptions on `kt' being in the future.
 * NOTE:  When `kt' lies in the past  of `tsc_to_ktime(me, 0)', `0' is returned instead. */
FUNDEF NOBLOCK NOPREEMPT ATTR_PURE WUNUSED NONNULL((1)) tsc_t
NOTHROW(FCALL ktime_to_tsc)(struct cpu const *__restrict me,
                            ktime_t kt);

/* Convert a ktime offset (read: not an absolute timestamp) to the equivalent # of TSC units. */
FUNDEF NOBLOCK NOPREEMPT ATTR_PURE WUNUSED NONNULL((1)) tsc_t
NOTHROW(FCALL ktime_offset_to_tsc)(struct cpu const *__restrict me,
                                   ktime_t num_nanoseconds);

/* Convert a tsc offset (read: not an absolute tick value) to the equivalent # of nanoseconds. */
FUNDEF NOBLOCK NOPREEMPT ATTR_PURE WUNUSED NONNULL((1)) ktime_t
NOTHROW(FCALL tsc_offset_to_ktime)(struct cpu const *__restrict me,
                                   tsc_t num_ticks);

/* Return the current kernel time (in nano seconds since `boottime')
 * WARNING: The results of  this function may  be inconsistent when  called
 *          from different CPUs (CPU#2 may return a lower value after CPU#1
 *          already returned a greater value)
 *          If this is a problem, you should instead use `ktime_stable()', but
 *          note  that for timeouts and the like, the scheduler uses `ktime()'
 * NOTE: This function is the same as doing `tsc_now_to_ktime(tsc_now())'
 *       while having preemption disabled. */
FUNDEF NOBLOCK WUNUSED ktime_t NOTHROW(KCALL ktime)(void);
FUNDEF NOBLOCK NOPREEMPT WUNUSED ktime_t NOTHROW(KCALL ktime_nopr)(void);

/* Same as `ktime()', but ensure that the `return >= <any-previous-return>' */
FUNDEF NOBLOCK WUNUSED ktime_t NOTHROW(KCALL ktime_stable)(void);

#define ktime_with_cpu(me) tsc_now_to_ktime(me, tsc_get(me))

/* [const] Initial timestamp of when this thread started. */
DATDEF ATTR_PERTASK ktime_t this_starttime;

/* [lock(PRIVATE(THIS_CPU))]
 * Timestamp of the last time  this thread was last  preempted.
 * Used to implement thread priorities, where a thread with the
 * lowest `this_stoptime' will be the one to get executed next.
 *
 * For the current thread, this indicates the point in
 * time  since when the  caller has ran uninterrupted. */
DATDEF ATTR_PERTASK ktime_t this_stoptime;

/* [lock(PRIVATE(THIS_CPU))]
 * Total time  this thread  spent being  active, as  measured  since
 * the  thread's creation, up  until the start  of the thread's most
 * recent quantum  (iow:  for  your own  thread,  to  calculate  the
 * correct value, use `this_activetime + (ktime() - this_stoptime)',
 * but make  sure to  disable preemption  during this  calculation). */
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
 * This  is done  by adding  `boottime' to  the given value. */
FUNDEF NOBLOCK ATTR_CONST WUNUSED struct timespec
NOTHROW(FCALL ktime_to_timespec)(ktime_t t);

/* Convert a given  `struct timespec' into  a ktime  timestamp.
 * This is done by subtracting `boottime' from the given value.
 * NOTE: When the  given  timestamp  `abs_timestamp' points  at,  or  before
 *       `boottime', then this function will return `0', as it is impossible
 *       to represent  a ktime-timestamp  that  happened before  the  system
 *       goto booted.
 * NOTE: When the given `abs_timestamp' is located so far ahead of `boottime'
 *       that  the return value  would overflow, the value  is clamped to the
 *       maximum possible value of `KTIME_INFINITE' */
FUNDEF NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) ktime_t
NOTHROW(FCALL timespec_to_ktime)(struct timespec const *__restrict abs_timestamp);

/* Similar to the  functions above, but  return a relative  time.
 * e.g.    When    `rel_time->tv_sec = 1, rel_time->tv_nsec = 7',
 * then  this  function  simply  return   `1 * USEC_PER_SEC + 7'.
 * Note  however  that if  `rel_time->tv_sec < 0', or  the result
 * of the  multiplication+addition  above  would  overflow,  then
 * this function will clamp the return value to `KTIME_INFINITE'. */
FUNDEF NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) ktime_t
NOTHROW(FCALL reltimespec_to_relktime)(struct timespec const *__restrict rel_time);

/* Do the inverse of `reltimespec_to_relktime' */
FUNDEF NOBLOCK ATTR_CONST WUNUSED struct timespec
NOTHROW(FCALL relktime_to_reltimespec)(ktime_t t);


#ifdef __cplusplus
extern "C++" {
FUNDEF NOBLOCK ATTR_PURE WUNUSED ktime_t
NOTHROW(FCALL timespec_to_ktime)(struct timespec const &__restrict abs_timestamp)
	ASMNAME("timespec_to_ktime");
FUNDEF NOBLOCK ATTR_PURE WUNUSED ktime_t
NOTHROW(FCALL reltimespec_to_relktime)(struct timespec const &__restrict rel_time)
	ASMNAME("reltimespec_to_relktime");
} /* extern "C++" */
#endif /* __cplusplus */

#if (__SIZEOF_TIMESPEC32 == __SIZEOF_TIMESPEC64 &&         \
     __OFFSET_TIMESPEC32_SEC == __OFFSET_TIMESPEC64_SEC && \
     __OFFSET_TIMESPEC32_NSEC == __OFFSET_TIMESPEC64_NSEC)
#define __HAVE_TIMESPEC32_IS_TIMESPEC64
#endif /* ... */

#if (__SIZEOF_TIMEVAL32 == __SIZEOF_TIMEVAL64 &&         \
     __OFFSET_TIMEVAL32_SEC == __OFFSET_TIMEVAL64_SEC && \
     __OFFSET_TIMEVAL32_NSEC == __OFFSET_TIMEVAL64_NSEC)
#define __HAVE_TIMEVAL32_IS_TIMEVAL64
#endif /* ... */

#ifdef __ARCH_HAVE_COMPAT
#if (__SIZEOF_COMPAT_TIMESPEC32 == __SIZEOF_COMPAT_TIMESPEC64 &&         \
     __OFFSET_COMPAT_TIMESPEC32_SEC == __OFFSET_COMPAT_TIMESPEC64_SEC && \
     __OFFSET_COMPAT_TIMESPEC32_NSEC == __OFFSET_COMPAT_TIMESPEC64_NSEC)
#define __HAVE_COMPAT_TIMESPEC32_IS_COMPAT_TIMESPEC64
#endif /* ... */
#if (__SIZEOF_COMPAT_TIMEVAL32 == __SIZEOF_COMPAT_TIMEVAL64 &&         \
     __OFFSET_COMPAT_TIMEVAL32_SEC == __OFFSET_COMPAT_TIMEVAL64_SEC && \
     __OFFSET_COMPAT_TIMEVAL32_NSEC == __OFFSET_COMPAT_TIMEVAL64_NSEC)
#define __HAVE_COMPAT_TIMEVAL32_IS_COMPAT_TIMEVAL64
#endif /* ... */
#if __ARCH_COMPAT_SIZEOF_SYSCALL_LONG_T == __SIZEOF_SYSCALL_LONG_T__
#if (__SIZEOF_COMPAT_TIMESPEC32 == __SIZEOF_TIMESPEC32 &&         \
     __OFFSET_COMPAT_TIMESPEC32_SEC == __OFFSET_TIMESPEC32_SEC && \
     __OFFSET_COMPAT_TIMESPEC32_NSEC == __OFFSET_TIMESPEC32_NSEC)
#define __HAVE_COMPAT_TIMESPEC32_IS_TIMESPEC32
#endif /* ... */
#if (__SIZEOF_COMPAT_TIMESPEC32 == __SIZEOF_TIMESPEC64 &&         \
     __OFFSET_COMPAT_TIMESPEC32_SEC == __OFFSET_TIMESPEC64_SEC && \
     __OFFSET_COMPAT_TIMESPEC32_NSEC == __OFFSET_TIMESPEC64_NSEC)
#define __HAVE_COMPAT_TIMESPEC32_IS_TIMESPEC64
#endif /* ... */
#if (__SIZEOF_COMPAT_TIMESPEC64 == __SIZEOF_TIMESPEC32 &&         \
     __OFFSET_COMPAT_TIMESPEC64_SEC == __OFFSET_TIMESPEC32_SEC && \
     __OFFSET_COMPAT_TIMESPEC64_NSEC == __OFFSET_TIMESPEC32_NSEC)
#define __HAVE_COMPAT_TIMESPEC64_IS_TIMESPEC32
#endif /* ... */
#if (__SIZEOF_COMPAT_TIMESPEC64 == __SIZEOF_TIMESPEC64 &&         \
     __OFFSET_COMPAT_TIMESPEC64_SEC == __OFFSET_TIMESPEC64_SEC && \
     __OFFSET_COMPAT_TIMESPEC64_NSEC == __OFFSET_TIMESPEC64_NSEC)
#define __HAVE_COMPAT_TIMESPEC64_IS_TIMESPEC64
#endif /* ... */
#endif /* __ARCH_COMPAT_SIZEOF_SYSCALL_LONG_T == __SIZEOF_SYSCALL_LONG_T__ */
#if __ARCH_COMPAT_SIZEOF_SUSECONDS_T == __SIZEOF_SUSECONDS_T__
#if (__SIZEOF_COMPAT_TIMEVAL32 == __SIZEOF_TIMEVAL32 &&         \
     __OFFSET_COMPAT_TIMEVAL32_SEC == __OFFSET_TIMEVAL32_SEC && \
     __OFFSET_COMPAT_TIMEVAL32_NSEC == __OFFSET_TIMEVAL32_NSEC)
#define __HAVE_COMPAT_TIMEVAL32_IS_TIMEVAL32
#endif /* ... */
#if (__SIZEOF_COMPAT_TIMEVAL32 == __SIZEOF_TIMEVAL64 &&         \
     __OFFSET_COMPAT_TIMEVAL32_SEC == __OFFSET_TIMEVAL64_SEC && \
     __OFFSET_COMPAT_TIMEVAL32_NSEC == __OFFSET_TIMEVAL64_NSEC)
#define __HAVE_COMPAT_TIMEVAL32_IS_TIMEVAL64
#endif /* ... */
#if (__SIZEOF_COMPAT_TIMEVAL64 == __SIZEOF_TIMEVAL32 &&         \
     __OFFSET_COMPAT_TIMEVAL64_SEC == __OFFSET_TIMEVAL32_SEC && \
     __OFFSET_COMPAT_TIMEVAL64_NSEC == __OFFSET_TIMEVAL32_NSEC)
#define __HAVE_COMPAT_TIMEVAL64_IS_TIMEVAL32
#endif /* ... */
#if (__SIZEOF_COMPAT_TIMEVAL64 == __SIZEOF_TIMEVAL64 &&         \
     __OFFSET_COMPAT_TIMEVAL64_SEC == __OFFSET_TIMEVAL64_SEC && \
     __OFFSET_COMPAT_TIMEVAL64_NSEC == __OFFSET_TIMEVAL64_NSEC)
#define __HAVE_COMPAT_TIMEVAL64_IS_TIMEVAL64
#endif /* ... */
#endif /* __ARCH_COMPAT_SIZEOF_SUSECONDS_T == __SIZEOF_SUSECONDS_T__ */
#endif /* __ARCH_HAVE_COMPAT */

#ifdef __HAVE_TIMESPEC32_IS_TIMESPEC64
#define __ASMNAME_ktime_from_user_timespec32       "ktime_from_user_timespec"
#define __ASMNAME_ktime_from_user_timespec64       "ktime_from_user_timespec"
#define __ASMNAME_relktime_from_user_reltimespec32 "relktime_from_user_reltimespec"
#define __ASMNAME_relktime_from_user_reltimespec64 "relktime_from_user_reltimespec"
#else /* __HAVE_TIMESPEC32_IS_TIMESPEC64 */
#define __ASMNAME_ktime_from_user_timespec32       "ktime_from_user_timespec32"
#define __ASMNAME_ktime_from_user_timespec64       "ktime_from_user_timespec64"
#define __ASMNAME_relktime_from_user_reltimespec32 "relktime_from_user_reltimespec32"
#define __ASMNAME_relktime_from_user_reltimespec64 "relktime_from_user_reltimespec64"
#endif /* !__HAVE_TIMESPEC32_IS_TIMESPEC64 */

#ifdef __HAVE_TIMEVAL32_IS_TIMEVAL64
#define __ASMNAME_ktime_from_user_timeval32       "ktime_from_user_timeval"
#define __ASMNAME_ktime_from_user_timeval64       "ktime_from_user_timeval"
#define __ASMNAME_relktime_from_user_reltimeval32 "relktime_from_user_reltimeval"
#define __ASMNAME_relktime_from_user_reltimeval64 "relktime_from_user_reltimeval"
#else /* __HAVE_TIMEVAL32_IS_TIMEVAL64 */
#define __ASMNAME_ktime_from_user_timeval32       "ktime_from_user_timeval32"
#define __ASMNAME_ktime_from_user_timeval64       "ktime_from_user_timeval64"
#define __ASMNAME_relktime_from_user_reltimeval32 "relktime_from_user_reltimeval32"
#define __ASMNAME_relktime_from_user_reltimeval64 "relktime_from_user_reltimeval64"
#endif /* !__HAVE_TIMEVAL32_IS_TIMEVAL64 */


#ifdef __ARCH_HAVE_COMPAT
#ifdef __HAVE_COMPAT_TIMESPEC32_IS_COMPAT_TIMESPEC64
#if defined(__HAVE_COMPAT_TIMESPEC32_IS_TIMESPEC32) || defined(__HAVE_COMPAT_TIMESPEC64_IS_TIMESPEC32)
#define __ASMNAME_ktime_from_user_compat_timespec32       __ASMNAME_ktime_from_user_timespec32
#define __ASMNAME_ktime_from_user_compat_timespec64       __ASMNAME_ktime_from_user_timespec32
#define __ASMNAME_relktime_from_user_compat_reltimespec32 __ASMNAME_relktime_from_user_reltimespec32
#define __ASMNAME_relktime_from_user_compat_reltimespec64 __ASMNAME_relktime_from_user_reltimespec32
#elif defined(__HAVE_COMPAT_TIMESPEC32_IS_TIMESPEC64) || defined(__HAVE_COMPAT_TIMESPEC64_IS_TIMESPEC64)
#define __ASMNAME_ktime_from_user_compat_timespec32       __ASMNAME_ktime_from_user_timespec64
#define __ASMNAME_ktime_from_user_compat_timespec64       __ASMNAME_ktime_from_user_timespec64
#define __ASMNAME_relktime_from_user_compat_reltimespec32 __ASMNAME_relktime_from_user_reltimespec64
#define __ASMNAME_relktime_from_user_compat_reltimespec64 __ASMNAME_relktime_from_user_reltimespec64
#else /* ... */
#define __ASMNAME_ktime_from_user_compat_timespec32       "ktime_from_user_compat_timespec"
#define __ASMNAME_ktime_from_user_compat_timespec64       "ktime_from_user_compat_timespec"
#define __ASMNAME_relktime_from_user_compat_reltimespec32 "relktime_from_user_compat_reltimespec"
#define __ASMNAME_relktime_from_user_compat_reltimespec64 "relktime_from_user_compat_reltimespec"
#endif /* !... */
#else /* __HAVE_COMPAT_TIMESPEC32_IS_COMPAT_TIMESPEC64 */
#if defined(__HAVE_COMPAT_TIMESPEC32_IS_TIMESPEC32)
#define __ASMNAME_ktime_from_user_compat_timespec32       __ASMNAME_ktime_from_user_timespec32
#define __ASMNAME_relktime_from_user_compat_reltimespec32 __ASMNAME_relktime_from_user_reltimespec32
#elif defined(__HAVE_COMPAT_TIMESPEC32_IS_TIMESPEC64)
#define __ASMNAME_ktime_from_user_compat_timespec32       __ASMNAME_ktime_from_user_timespec64
#define __ASMNAME_relktime_from_user_compat_reltimespec32 __ASMNAME_relktime_from_user_reltimespec64
#else /* ... */
#define __ASMNAME_ktime_from_user_compat_timespec32       "ktime_from_user_compat_timespec32"
#define __ASMNAME_relktime_from_user_compat_reltimespec32 "relktime_from_user_compat_reltimespec32"
#endif /* !... */
#if defined(__HAVE_COMPAT_TIMESPEC64_IS_TIMESPEC32)
#define __ASMNAME_ktime_from_user_compat_timespec64       __ASMNAME_ktime_from_user_timespec32
#define __ASMNAME_relktime_from_user_compat_reltimespec64 __ASMNAME_relktime_from_user_reltimespec32
#elif defined(__HAVE_COMPAT_TIMESPEC64_IS_TIMESPEC64)
#define __ASMNAME_ktime_from_user_compat_timespec64       __ASMNAME_ktime_from_user_timespec64
#define __ASMNAME_relktime_from_user_compat_reltimespec64 __ASMNAME_relktime_from_user_reltimespec64
#else /* ... */
#define __ASMNAME_ktime_from_user_compat_timespec64       "ktime_from_user_compat_timespec64"
#define __ASMNAME_relktime_from_user_compat_reltimespec64 "relktime_from_user_compat_reltimespec64"
#endif /* !... */
#endif /* !__HAVE_COMPAT_TIMESPEC32_IS_COMPAT_TIMESPEC64 */

#ifdef __HAVE_COMPAT_TIMEVAL32_IS_COMPAT_TIMEVAL64
#if defined(__HAVE_COMPAT_TIMEVAL32_IS_TIMEVAL32) || defined(__HAVE_COMPAT_TIMEVAL64_IS_TIMEVAL32)
#define __ASMNAME_ktime_from_user_compat_timeval32       __ASMNAME_ktime_from_user_timeval32
#define __ASMNAME_ktime_from_user_compat_timeval64       __ASMNAME_ktime_from_user_timeval32
#define __ASMNAME_relktime_from_user_compat_reltimeval32 __ASMNAME_relktime_from_user_reltimeval32
#define __ASMNAME_relktime_from_user_compat_reltimeval64 __ASMNAME_relktime_from_user_reltimeval32
#elif defined(__HAVE_COMPAT_TIMEVAL32_IS_TIMEVAL64) || defined(__HAVE_COMPAT_TIMEVAL64_IS_TIMEVAL64)
#define __ASMNAME_ktime_from_user_compat_timeval32       __ASMNAME_ktime_from_user_timeval64
#define __ASMNAME_ktime_from_user_compat_timeval64       __ASMNAME_ktime_from_user_timeval64
#define __ASMNAME_relktime_from_user_compat_reltimeval32 __ASMNAME_relktime_from_user_reltimeval64
#define __ASMNAME_relktime_from_user_compat_reltimeval64 __ASMNAME_relktime_from_user_reltimeval64
#else /* ... */
#define __ASMNAME_ktime_from_user_compat_timeval32       "ktime_from_user_compat_timeval"
#define __ASMNAME_ktime_from_user_compat_timeval64       "ktime_from_user_compat_timeval"
#define __ASMNAME_relktime_from_user_compat_reltimeval32 "relktime_from_user_compat_reltimeval"
#define __ASMNAME_relktime_from_user_compat_reltimeval64 "relktime_from_user_compat_reltimeval"
#endif /* !... */
#else /* __HAVE_COMPAT_TIMEVAL32_IS_COMPAT_TIMEVAL64 */
#if defined(__HAVE_COMPAT_TIMEVAL32_IS_TIMEVAL32)
#define __ASMNAME_ktime_from_user_compat_timeval32       __ASMNAME_ktime_from_user_timeval32
#define __ASMNAME_relktime_from_user_compat_reltimeval32 __ASMNAME_relktime_from_user_reltimeval32
#elif defined(__HAVE_COMPAT_TIMEVAL32_IS_TIMEVAL64)
#define __ASMNAME_ktime_from_user_compat_timeval32       __ASMNAME_ktime_from_user_timeval64
#define __ASMNAME_relktime_from_user_compat_reltimeval32 __ASMNAME_relktime_from_user_reltimeval64
#else /* ... */
#define __ASMNAME_ktime_from_user_compat_timeval32       "ktime_from_user_compat_timeval32"
#define __ASMNAME_relktime_from_user_compat_reltimeval32 "relktime_from_user_compat_reltimeval32"
#endif /* !... */
#if defined(__HAVE_COMPAT_TIMEVAL64_IS_TIMEVAL32)
#define __ASMNAME_ktime_from_user_compat_timeval64       __ASMNAME_ktime_from_user_timeval32
#define __ASMNAME_relktime_from_user_compat_reltimeval64 __ASMNAME_relktime_from_user_reltimeval32
#elif defined(__HAVE_COMPAT_TIMEVAL64_IS_TIMEVAL64)
#define __ASMNAME_ktime_from_user_compat_timeval64       __ASMNAME_ktime_from_user_timeval64
#define __ASMNAME_relktime_from_user_compat_reltimeval64 __ASMNAME_relktime_from_user_reltimeval64
#else /* ... */
#define __ASMNAME_ktime_from_user_compat_timeval64       "ktime_from_user_compat_timeval64"
#define __ASMNAME_relktime_from_user_compat_reltimeval64 "relktime_from_user_compat_reltimeval64"
#endif /* !... */
#endif /* !__HAVE_COMPAT_TIMEVAL32_IS_COMPAT_TIMEVAL64 */
#endif /* __ARCH_HAVE_COMPAT */


/* Load absolute ktime values from various user-space sources
 * >> ktime_from_user_time*:
 *      Given: A user-space time descriptor for absolute seconds since 01.01.1970 + addend
 *      Return:  an   absolute  ktime   timestamp   (i.e.  nanoseconds   since   boottime)
 * >> relktime_from_user_reltime*:
 *      Given:  A  user-space  time descriptor  for  relative seconds  from  right now
 *      Return: The total # of nanoseconds described by the user-space time descriptor
 * @throw: E_SEGFAULT:                                                                ...
 * @throw: E_INVALID_ARGUMENT_BAD_VALUE:E_INVALID_ARGUMENT_CONTEXT_BAD_TIMEVAL_USEC:  ...
 * @throw: E_INVALID_ARGUMENT_BAD_VALUE:E_INVALID_ARGUMENT_CONTEXT_BAD_TIMESPEC_NSEC: ... */
FUNDEF NOBLOCK WUNUSED ktime_t FCALL ktime_from_user_timespec32(NCX struct __timespec32 const *__restrict abs_time) THROWS(E_SEGFAULT, E_INVALID_ARGUMENT_BAD_VALUE) ASMNAME(__ASMNAME_ktime_from_user_timespec32);
FUNDEF NOBLOCK WUNUSED ktime_t FCALL ktime_from_user_timespec64(NCX struct __timespec64 const *__restrict abs_time) THROWS(E_SEGFAULT, E_INVALID_ARGUMENT_BAD_VALUE) ASMNAME(__ASMNAME_ktime_from_user_timespec64);
FUNDEF NOBLOCK WUNUSED ktime_t FCALL relktime_from_user_reltimespec32(NCX struct __timespec32 const *__restrict rel_time) THROWS(E_SEGFAULT, E_INVALID_ARGUMENT_BAD_VALUE) ASMNAME(__ASMNAME_relktime_from_user_reltimespec32);
FUNDEF NOBLOCK WUNUSED ktime_t FCALL relktime_from_user_reltimespec64(NCX struct __timespec64 const *__restrict rel_time) THROWS(E_SEGFAULT, E_INVALID_ARGUMENT_BAD_VALUE) ASMNAME(__ASMNAME_relktime_from_user_reltimespec64);
FUNDEF NOBLOCK WUNUSED ktime_t FCALL ktime_from_user_timeval32(NCX struct __timeval32 const *__restrict abs_time) THROWS(E_SEGFAULT, E_INVALID_ARGUMENT_BAD_VALUE) ASMNAME(__ASMNAME_ktime_from_user_timeval32);
FUNDEF NOBLOCK WUNUSED ktime_t FCALL ktime_from_user_timeval64(NCX struct __timeval64 const *__restrict abs_time) THROWS(E_SEGFAULT, E_INVALID_ARGUMENT_BAD_VALUE) ASMNAME(__ASMNAME_ktime_from_user_timeval64);
FUNDEF NOBLOCK WUNUSED ktime_t FCALL relktime_from_user_reltimeval32(NCX struct __timeval32 const *__restrict rel_time) THROWS(E_SEGFAULT, E_INVALID_ARGUMENT_BAD_VALUE) ASMNAME(__ASMNAME_relktime_from_user_reltimeval32);
FUNDEF NOBLOCK WUNUSED ktime_t FCALL relktime_from_user_reltimeval64(NCX struct __timeval64 const *__restrict rel_time) THROWS(E_SEGFAULT, E_INVALID_ARGUMENT_BAD_VALUE) ASMNAME(__ASMNAME_relktime_from_user_reltimeval64);
#ifdef __ARCH_HAVE_COMPAT
FUNDEF NOBLOCK WUNUSED ktime_t FCALL ktime_from_user_compat_timespec32(NCX struct compat_timespec32 const *__restrict abs_time) THROWS(E_SEGFAULT, E_INVALID_ARGUMENT_BAD_VALUE) ASMNAME(__ASMNAME_ktime_from_user_compat_timespec32);
FUNDEF NOBLOCK WUNUSED ktime_t FCALL ktime_from_user_compat_timespec64(NCX struct compat_timespec64 const *__restrict abs_time) THROWS(E_SEGFAULT, E_INVALID_ARGUMENT_BAD_VALUE) ASMNAME(__ASMNAME_ktime_from_user_compat_timespec64);
FUNDEF NOBLOCK WUNUSED ktime_t FCALL relktime_from_user_compat_reltimespec32(NCX struct compat_timespec32 const *__restrict rel_time) THROWS(E_SEGFAULT, E_INVALID_ARGUMENT_BAD_VALUE) ASMNAME(__ASMNAME_relktime_from_user_compat_reltimespec32);
FUNDEF NOBLOCK WUNUSED ktime_t FCALL relktime_from_user_compat_reltimespec64(NCX struct compat_timespec64 const *__restrict rel_time) THROWS(E_SEGFAULT, E_INVALID_ARGUMENT_BAD_VALUE) ASMNAME(__ASMNAME_relktime_from_user_compat_reltimespec64);
FUNDEF NOBLOCK WUNUSED ktime_t FCALL ktime_from_user_compat_timeval32(NCX struct compat_timeval32 const *__restrict abs_time) THROWS(E_SEGFAULT, E_INVALID_ARGUMENT_BAD_VALUE) ASMNAME(__ASMNAME_ktime_from_user_compat_timeval32);
FUNDEF NOBLOCK WUNUSED ktime_t FCALL ktime_from_user_compat_timeval64(NCX struct compat_timeval64 const *__restrict abs_time) THROWS(E_SEGFAULT, E_INVALID_ARGUMENT_BAD_VALUE) ASMNAME(__ASMNAME_ktime_from_user_compat_timeval64);
FUNDEF NOBLOCK WUNUSED ktime_t FCALL relktime_from_user_compat_reltimeval32(NCX struct compat_timeval32 const *__restrict rel_time) THROWS(E_SEGFAULT, E_INVALID_ARGUMENT_BAD_VALUE) ASMNAME(__ASMNAME_relktime_from_user_compat_reltimeval32);
FUNDEF NOBLOCK WUNUSED ktime_t FCALL relktime_from_user_compat_reltimeval64(NCX struct compat_timeval64 const *__restrict rel_time) THROWS(E_SEGFAULT, E_INVALID_ARGUMENT_BAD_VALUE) ASMNAME(__ASMNAME_relktime_from_user_compat_reltimeval64);
#endif /* __ARCH_HAVE_COMPAT */


#ifdef __cplusplus
extern "C++" {
FUNDEF NOBLOCK WUNUSED ktime_t FCALL ktime_from_user(NCX struct __timespec32 const *__restrict rel_time) THROWS(E_SEGFAULT, E_INVALID_ARGUMENT_BAD_VALUE) ASMNAME(__ASMNAME_ktime_from_user_timespec32);
FUNDEF NOBLOCK WUNUSED ktime_t FCALL relktime_from_user_rel(NCX struct __timespec32 const *__restrict rel_time) THROWS(E_SEGFAULT, E_INVALID_ARGUMENT_BAD_VALUE) ASMNAME(__ASMNAME_relktime_from_user_reltimespec32);
FUNDEF NOBLOCK WUNUSED ktime_t FCALL ktime_from_user(NCX struct __timeval32 const *__restrict rel_time) THROWS(E_SEGFAULT, E_INVALID_ARGUMENT_BAD_VALUE) ASMNAME(__ASMNAME_ktime_from_user_timeval32);
FUNDEF NOBLOCK WUNUSED ktime_t FCALL relktime_from_user_rel(NCX struct __timeval32 const *__restrict rel_time) THROWS(E_SEGFAULT, E_INVALID_ARGUMENT_BAD_VALUE) ASMNAME(__ASMNAME_relktime_from_user_reltimeval32);
#ifndef __HAVE_TIMESPEC32_IS_TIMESPEC64
FUNDEF NOBLOCK WUNUSED ktime_t FCALL ktime_from_user(NCX struct __timespec64 const *__restrict rel_time) THROWS(E_SEGFAULT, E_INVALID_ARGUMENT_BAD_VALUE) ASMNAME(__ASMNAME_ktime_from_user_timespec64);
FUNDEF NOBLOCK WUNUSED ktime_t FCALL relktime_from_user_rel(NCX struct __timespec64 const *__restrict rel_time) THROWS(E_SEGFAULT, E_INVALID_ARGUMENT_BAD_VALUE) ASMNAME(__ASMNAME_relktime_from_user_reltimespec64);
#endif /* !__HAVE_TIMESPEC32_IS_TIMESPEC64 */
#ifndef __HAVE_TIMEVAL32_IS_TIMEVAL64
FUNDEF NOBLOCK WUNUSED ktime_t FCALL ktime_from_user(NCX struct __timeval64 const *__restrict rel_time) THROWS(E_SEGFAULT, E_INVALID_ARGUMENT_BAD_VALUE) ASMNAME(__ASMNAME_ktime_from_user_timeval64);
FUNDEF NOBLOCK WUNUSED ktime_t FCALL relktime_from_user_rel(NCX struct __timeval64 const *__restrict rel_time) THROWS(E_SEGFAULT, E_INVALID_ARGUMENT_BAD_VALUE) ASMNAME(__ASMNAME_relktime_from_user_reltimeval64);
#endif /* !__HAVE_TIMEVAL32_IS_TIMEVAL64 */
#ifdef __ARCH_HAVE_COMPAT
#if !defined(__HAVE_COMPAT_TIMESPEC32_IS_TIMESPEC32) && !defined(__HAVE_COMPAT_TIMESPEC32_IS_TIMESPEC64)
FUNDEF NOBLOCK WUNUSED ktime_t FCALL ktime_from_user(NCX struct compat_timespec32 const *__restrict rel_time) THROWS(E_SEGFAULT, E_INSPECID_ARGUMENT_BAD_SPECUE) ASMNAME(__ASMNAME_ktime_from_user_compat_timespec32);
FUNDEF NOBLOCK WUNUSED ktime_t FCALL relktime_from_user_rel(NCX struct compat_timespec32 const *__restrict rel_time) THROWS(E_SEGFAULT, E_INSPECID_ARGUMENT_BAD_SPECUE) ASMNAME(__ASMNAME_relktime_from_user_compat_reltimespec32);
#endif /* !__HAVE_COMPAT_TIMESPEC32_IS_TIMESPEC32 && !__HAVE_COMPAT_TIMESPEC32_IS_TIMESPEC64 */
#ifndef __HAVE_COMPAT_TIMESPEC32_IS_COMPAT_TIMESPEC64
#if !defined(__HAVE_COMPAT_TIMESPEC64_IS_TIMESPEC32) && !defined(__HAVE_COMPAT_TIMESPEC64_IS_TIMESPEC64)
FUNDEF NOBLOCK WUNUSED ktime_t FCALL ktime_from_user(NCX struct compat_timespec64 const *__restrict rel_time) THROWS(E_SEGFAULT, E_INSPECID_ARGUMENT_BAD_SPECUE) ASMNAME(__ASMNAME_ktime_from_user_compat_timespec64);
FUNDEF NOBLOCK WUNUSED ktime_t FCALL relktime_from_user_rel(NCX struct compat_timespec64 const *__restrict rel_time) THROWS(E_SEGFAULT, E_INSPECID_ARGUMENT_BAD_SPECUE) ASMNAME(__ASMNAME_relktime_from_user_compat_reltimespec64);
#endif /* !__HAVE_COMPAT_TIMESPEC64_IS_TIMESPEC32 && !__HAVE_COMPAT_TIMESPEC64_IS_TIMESPEC64 */
#endif /* !__HAVE_COMPAT_TIMESPEC32_IS_COMPAT_TIMESPEC64 */
#if !defined(__HAVE_COMPAT_TIMEVAL32_IS_TIMEVAL32) && !defined(__HAVE_COMPAT_TIMEVAL32_IS_TIMEVAL64)
FUNDEF NOBLOCK WUNUSED ktime_t FCALL ktime_from_user(NCX struct compat_timeval32 const *__restrict rel_time) THROWS(E_SEGFAULT, E_INVALID_ARGUMENT_BAD_VALUE) ASMNAME(__ASMNAME_ktime_from_user_compat_timeval32);
FUNDEF NOBLOCK WUNUSED ktime_t FCALL relktime_from_user_rel(NCX struct compat_timeval32 const *__restrict rel_time) THROWS(E_SEGFAULT, E_INVALID_ARGUMENT_BAD_VALUE) ASMNAME(__ASMNAME_relktime_from_user_compat_reltimeval32);
#endif /* !__HAVE_COMPAT_TIMEVAL32_IS_TIMEVAL32 && !__HAVE_COMPAT_TIMEVAL32_IS_TIMEVAL64 */
#ifndef __HAVE_COMPAT_TIMEVAL32_IS_COMPAT_TIMEVAL64
#if !defined(__HAVE_COMPAT_TIMEVAL64_IS_TIMEVAL32) && !defined(__HAVE_COMPAT_TIMEVAL64_IS_TIMEVAL64)
FUNDEF NOBLOCK WUNUSED ktime_t FCALL ktime_from_user(NCX struct compat_timeval64 const *__restrict rel_time) THROWS(E_SEGFAULT, E_INVALID_ARGUMENT_BAD_VALUE) ASMNAME(__ASMNAME_ktime_from_user_compat_timeval64);
FUNDEF NOBLOCK WUNUSED ktime_t FCALL relktime_from_user_rel(NCX struct compat_timeval64 const *__restrict rel_time) THROWS(E_SEGFAULT, E_INVALID_ARGUMENT_BAD_VALUE) ASMNAME(__ASMNAME_relktime_from_user_compat_reltimeval64);
#endif /* !__HAVE_COMPAT_TIMEVAL64_IS_TIMEVAL32 && !__HAVE_COMPAT_TIMEVAL64_IS_TIMEVAL64 */
#endif /* !__HAVE_COMPAT_TIMEVAL32_IS_COMPAT_TIMEVAL64 */
#endif /* __ARCH_HAVE_COMPAT */
} /* extern "C++" */
#endif /* __cplusplus */



#ifndef __realtime_defined
#define __realtime_defined
/* Returns the current real time derived from the current CPU time.
 * WARNING: KOS only gives a best-effort guaranty for this function
 *          in terms of  consistency when it  comes to the  calling
 *          thread being moved to a different CPU.
 *          There is a chance  of minor inconsistencies in  terms
 *          of exact nano-second values returned by this function
 *          when the calling thread is moved.
 * However, it is guarantied that (so long as `settimeofday()'  isn't
 * called), calling this function repeatedly from the threads  hosted
 * by the same CPU will _always_ return values such that later values
 * are >= earlier values. */
FUNDEF NOBLOCK WUNUSED struct timespec NOTHROW(KCALL realtime)(void);
#endif /* !__realtime_defined */


DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_SCHED_TSC_H */
