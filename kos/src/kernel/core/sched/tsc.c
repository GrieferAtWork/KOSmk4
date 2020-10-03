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
#ifndef GUARD_KERNEL_SRC_SCHED_TSC_C
#define GUARD_KERNEL_SRC_SCHED_TSC_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/printk.h>
#include <sched/atomic64.h>
#include <sched/cpu.h>
#include <sched/sched.h>
#include <sched/task.h>
#include <sched/tsc.h>

#include <hybrid/atomic.h>
#include <hybrid/overflow.h>

#include <int128.h>
#include <assert.h>
#include <inttypes.h>
#include <time.h> /* NSEC_PER_SEC */

DECL_BEGIN

/* [const] Initial timestamp of when this thread started. */
PUBLIC ATTR_PERTASK ktime_t this_starttime = 0;

/* [lock(PRIVATE(THIS_CPU))]
 * Timestamp of the last time this thread was last preempted.
 * Used to implement thread priorities, where a thread with the
 * lowest `this_stoptime' will be the one to get executed next.
 *
 * For the current thread, this is indicates the point in time
 * since when the caller has ran uninterrupted. */
PUBLIC ATTR_PERTASK ktime_t this_stoptime = 0;

/* [lock(PRIVATE(THIS_CPU))] Total time this thread spent being active. */
PUBLIC ATTR_PERTASK ktime_t this_activetime = 0;



/* The min/max bounds for what can be considered valid HZ values. */
PUBLIC ATTR_PERCPU tsc_hz_t thiscpu_tsc_hzmin = 0;
PUBLIC ATTR_PERCPU tsc_hz_t thiscpu_tsc_hzmax = (tsc_hz_t)-1;

struct timestamp {
	ktime_t ts_kt;  /* RTC realtime */
	tsc_t   ts_tsc; /* TSC counter mapping to some point in [ts_kt, ts_kt+tsc_realtime_err-1] */
};


/************************************************************************/
/* CPU uptime calculations.                                             */
/************************************************************************/
PRIVATE ATTR_PERCPU struct timestamp thiscpu_startup = { 0, 0 }; /* Startup timestamp (for the last time the CPU came online). */
//PRIVATE ATTR_PERCPU tsc_t thiscpu_uptime_tsc         = 0;        /* Uptime addend (updated when the CPU goes offline). */
/* TODO: `thiscpu_uptime_tsc' must be updated from within `cpu_enter_deepsleep()' as:
 *     >> thiscpu_uptime_tsc += tsc_get() - thiscpu_startup_tsc; */


/************************************************************************/
/* REALTIME calculations.                                               */
/************************************************************************/
PRIVATE ATTR_PERCPU struct timestamp thiscpu_basetime = { 0, 0 }; /* Baseline timestamp. */


PRIVATE NOBLOCK WUNUSED ATTR_CONST tsc_hz_t
NOTHROW(FCALL calculate_hz)(tsc_t tsc, ktime_t time, bool ceildiv) {
	tsc_hz_t result;
	if (OVERFLOW_UMUL(tsc, NSEC_PER_SEC, &result)) {
		uint128_t tsc_nsec;
do128:
		uint128_set(tsc_nsec, tsc);
		uint128_mul(tsc_nsec, NSEC_PER_SEC);
		if (ceildiv)
			uint128_add(tsc_nsec, time - 1);
		uint128_div(tsc_nsec, time);
		result = uint128_get64(tsc_nsec);
	} else {
		if (ceildiv) {
			if (OVERFLOW_UADD(result, time - 1, &result))
				goto do128;
		}
		result /= time;
	}
	return result;
}



/* Interrupt handler for implementing realtime() re-syncing.
 * This function should call `tsc_resync_realtime()' to retrieve the
 * current realtime, as read from some external clock-source that can
 * be relied upon, at which point it should calculate the delta and
 * relative error with the kernel's TSC-based idea of what realtime
 * should be.
 * @param: new_ktime: The new RTC time (as returned by `tsc_resync_realtime()') */
PUBLIC NOPREEMPT NOBLOCK void
NOTHROW(FCALL tsc_resync_interrupt)(ktime_t curr_ktime) {
	struct cpu *me = THIS_CPU;
	struct timestamp now;
	tsc_t tsc_passed;
	ktime_t cpu_now;
	ktime_t ktime_passed_min;
	ktime_t ktime_passed_max;
	ktime_t ktime_passed_cpu;
	tsc_hz_t hz_min, hz_max;
	tsc_hz_t hz;
	now.ts_kt = curr_ktime;
	for (;;) {
		ktime_t temp;
		/* Get a TSC value, and ensure it corresponds to a consistent `curr_ktime'
		 * Ensure this by getting one that points to the same RTC time slice. */
		now.ts_tsc = tsc_get(me);
		temp       = tsc_resync_realtime();
		if (temp == now.ts_kt)
			break;
		now.ts_kt = temp;
	}
	COMPILER_BARRIER();
	/*
	 * Create a projection:
	 *
	 * TSC
	 *  ^
	 *  |                      [------]  (now)
	 *  |                      |     /
	 *  |                      |    /
	 *  |                     |    /
	 *  |                     |   /
	 *  |         hz_min --> |   / <-- hz_max
	 *  |                    |  /
	 *  |                   |  /
	 *  |                   | /
	 *  |                  | /
	 *  |                  |/
	 *  |                 |/
	 *  |                 /
	 *  |                /
	 *  |               /|
	 *  |              /|
	 *  |             / |
	 *  |            / |
	 *  |           /  |
	 *  |          /  |
	 *  |         /   |
	 *  |        /   |
	 *  |       /    |
	 *  |      /    |
	 *  |     /     |
	 *  |    [------]  (thiscpu_startup)
	 *  |
	 *  +--------------------------------------> KT
	 */
	tsc_passed       = now.ts_tsc - FORCPU(me, thiscpu_startup.ts_tsc);
	ktime_passed_min = FORCPU(me, thiscpu_startup.ts_kt) + tsc_realtime_err;
	if (OVERFLOW_USUB(now.ts_kt, ktime_passed_min, &ktime_passed_min))
		ktime_passed_min = 0;
	ktime_passed_max = (now.ts_kt + tsc_realtime_err) - FORCPU(me, thiscpu_startup.ts_kt);
	assert(ktime_passed_min <= ktime_passed_max);
	assert(ktime_passed_max != 0);
	hz_min = calculate_hz(tsc_passed, ktime_passed_max, false);
	hz_max = likely(ktime_passed_min != 0)
	         ? calculate_hz(tsc_passed, ktime_passed_min, true)
	         : (tsc_hz_t)-1;
	assert(hz_min <= hz_max);
	if (hz_min < FORCPU(me, thiscpu_tsc_hzmin)) {
		printk(KERN_WARNING "[cpu#%u] hz_min widened ("
		                    "%" PRIuN(__SIZEOF_TSC_HZ_T__) " -> "
		                    "%" PRIuN(__SIZEOF_TSC_HZ_T__) ")\n",
		       me->c_id, FORCPU(me, thiscpu_tsc_hzmin), hz_min);
	}
	if (hz_max > FORCPU(me, thiscpu_tsc_hzmax)) {
		printk(KERN_WARNING "[cpu#%u] hz_max widened ("
		                    "%" PRIuN(__SIZEOF_TSC_HZ_T__) " -> "
		                    "%" PRIuN(__SIZEOF_TSC_HZ_T__) ")\n",
		       me->c_id, FORCPU(me, thiscpu_tsc_hzmax), hz_max);
	}
	FORCPU(me, thiscpu_tsc_hzmin) = hz_min;
	FORCPU(me, thiscpu_tsc_hzmax) = hz_max;
	/* If the currently used HZ value falls into the hz_min/hz_max range, then everything is well. */
	hz = FORCPU(me, thiscpu_tsc_hz);
	if (hz >= hz_min && hz <= hz_max)
		return;
	/* Calculate what we though the current time would be. */
	ktime_passed_cpu = tsc_offset_to_ktime(me, tsc_passed);
	/* Check if our predicted CPU time falls within our margin of error.
	 * This may still be the case, even if the newly calculated HZ would
	 * fall outside the margin of error due to rounding errors. */
	if (ktime_passed_cpu >= ktime_passed_min &&
	    ktime_passed_cpu <= ktime_passed_max)
		return;
	/* Figure out the closest HZ value that would still be valid. */
	if (hz < hz_min)
		hz = hz_min;
	else {
		assert(hz > hz_max);
		hz = hz_max;
	}
	/* Our currently used HZ value wasn't correct.
	 * We must clamp it to the nearest valid HZ value, and re-calculate `thiscpu_basetime'
	 * to point to the nearest valid location on a line with an angle of the new HZ value,
	 * and drawn through some point within the `thiscpu_startup' range.
	 * This can easily be done by clamping `thiscpu_basetime' to some value within the
	 * range described by now...+=tsc_realtime_err
	 *
	 * TSC
	 *  ^
	 *  |          (cpu_now) [-]  [------] (now)
	 *  |                     |      /
	 *  |                     |     /
	 *  |                    |     /
	 *  |                    |    /
	 *  |                   |    /
	 *  |                   |   /
	 *  |                  |   /
	 *  |                  |  /
	 *  |                 |  /
	 *  |                 | /
	 *  |                | /
	 *  |                |/
	 *  |                /
	 *  |               [------]  (thiscpu_startup)
	 *  |
	 *  +--------------------------------------> KT
	 */
	cpu_now = tsc_now_to_ktime(me, now.ts_tsc);
	/* Clamp `cpu_now' to the closest valid TSC timestamp. */
	if (cpu_now < now.ts_kt) {
		/* Simple case: Have the clock jump ahead */
		cpu_now = now.ts_kt;
	} else {
		now.ts_kt += tsc_realtime_err;
		if (cpu_now > now.ts_kt) {
			/* Difficult case: we have to turn the clock backwards... */
			printk(KERN_WARNING "[cpu#%u] Turn back clock ("
			                    "%#" PRIxN(__SIZEOF_KTIME_T__) " -> "
			                    "%#" PRIxN(__SIZEOF_KTIME_T__) ")\n",
			       me->c_id, cpu_now, now.ts_kt);
			cpu_now = now.ts_kt;
		}
	}

	/* Set the baseline CPU timestamp to follow the linear vector from the
	 * CPU startup timestamp, all the way to the current point in time that
	 * still falls into the margin of error, and is closest to what we've
	 * assumed to be the case until this point. */
	FORCPU(me, thiscpu_basetime.ts_kt)  = cpu_now;
	FORCPU(me, thiscpu_basetime.ts_tsc) = now.ts_tsc;
	{
		bool increase;
		tsc_hz_t old_hz;
		old_hz = FORCPU(me, thiscpu_tsc_hz);
		FORCPU(me, thiscpu_tsc_hz) = hz;
		increase = hz > old_hz;
		printk(KERN_INFO "[cpu#%u][%c] Adjust tsc hz "
		                 "%" PRIuN(__SIZEOF_TSC_HZ_T__) " -> "
		                 "%" PRIuN(__SIZEOF_TSC_HZ_T__) " "
		                 "(cpu clock was running too %s)\n",
		       me->c_id,
		       increase ? '+' : '-',
		       old_hz,
		       hz,
		       increase ? "fast" : "slow");
		/* TODO: When TSC_HZ changes, we should probably re-calculate the
		 *       current TSC deadline by re-doing the deadline calculation
		 *       code as documented at the top of <sched/sched.h>, starting
		 *       at `TSC_DEAD = KTIME_TO_TSC(DEADLINE);'
		 * NOTE: For this case, we also need the ability to immediately
		 *       perform a thread switch, which is something that we can't
		 *       do right here, since our caller may need to do additional
		 *       hardware cleanup related to this function being called as
		 *       the result of a hardware interrupt! */
	}
	return;
}

/* Perform the initial TSC resync for the calling CPU.
 * This function will also calculate and set the initial TSC deadline. */
PUBLIC NOPREEMPT NOBLOCK NONNULL((1)) void
NOTHROW(FCALL tsc_resync_init)(struct cpu *__restrict me) {
	struct timestamp ts;
	COMPILER_BARRIER();
	ts.ts_kt = tsc_resync_realtime();
	for (;;) {
		ktime_t temp;
		ts.ts_tsc = tsc_get(me);
		temp      = tsc_resync_realtime();
		if (temp == ts.ts_kt)
			break;
		ts.ts_kt = temp;
	}
	COMPILER_BARRIER();
	FORCPU(me, thiscpu_startup) = ts;
	ts.ts_kt += tsc_realtime_err / 2; /* Assume an average error. */
	FORCPU(me, thiscpu_basetime)  = ts;
	FORCPU(me, thiscpu_tsc_hzmin) = 0;
	FORCPU(me, thiscpu_tsc_hzmax) = (tsc_hz_t)-1;

	/* TODO: Set the initial TSC deadline to the next scheduling EVENT:
	 * >> if (NUM_RUNNING_THREADS == 1 && !HAS_WAITING_THREADS)
	 * >>     tsc_nodeadline();
	 * >> else {
	 * >>     offset   = (new_tsc - PERTASK(this_stoptime)) / NUM_RUNNING_THREADS;
	 * >>     deadline = new_tsc + offset;
	 * >>     if (HAS_WAITING_THREADS) {
	 * >>         struct task *w = NEXT_WAITING_THERAD_TO_WAKE_UP;
	 * >>         if (TIMEOUT_DEADLINE_OF(w) < deadline) {
	 * >>             offset  = (new_tsc - PERTASK(this_stoptime)) / (NUM_RUNNING_THREADS + 1);
	 * >>             offset2 = new_tsc - FORTASK(w, this_stoptime);
	 * >>             // if the waiting thread has waited longer than the caller (i.e. has
	 * >>             // a higher effective scheduling priority), then set-up the deadline
	 * >>             // to trigger when it's timeout would expire, rather than whenever
	 * >>             // our quantum ends.
	 * >>             if (offset > offset2)
	 * >>                 offset = offset2;
	 * >>             deadline = new_tsc + offset;
	 * >>         }
	 * >>     }
	 * >>     tsc_deadline(deadline);
	 * >> } */
	tsc_nodeadline(me);
}

/* Convert a given `tsc' value into the corresponding ktime offset. */
PUBLIC NOBLOCK NOPREEMPT ATTR_PURE WUNUSED NONNULL((1)) ktime_t
NOTHROW(FCALL tsc_to_ktime)(struct cpu const *__restrict me,
                            tsc_t tsc) {
	ktime_t result;
	/* Determine the TSC offset since the last re-sync */
	if unlikely(tsc < FORCPU(me, thiscpu_basetime.ts_tsc)) {
		tsc_t until, until_nano;
		until = FORCPU(me, thiscpu_basetime.ts_tsc) - tsc;
		/* Calculate the current boot-time offset. */
		result = FORCPU(me, thiscpu_basetime.ts_kt);
		if unlikely(OVERFLOW_UMUL(until, NSEC_PER_SEC, &until_nano)) {
			uint128_t since128;
			uint128_set(since128, until);
			uint128_mul(since128, (u32)NSEC_PER_SEC);
			uint128_div(since128, FORCPU(me, thiscpu_tsc_hz));
			result -= uint128_get64(since128);
		} else {
			result -= until_nano / FORCPU(me, thiscpu_tsc_hz);
		}
	} else {
		tsc_t since, since_nano;
		since = tsc - FORCPU(me, thiscpu_basetime.ts_tsc);
		/* Calculate the current boot-time offset. */
		result = FORCPU(me, thiscpu_basetime.ts_kt);
		if unlikely(OVERFLOW_UMUL(since, NSEC_PER_SEC, &since_nano)) {
			uint128_t since128;
			uint128_set(since128, since);
			uint128_mul(since128, NSEC_PER_SEC);
			uint128_div(since128, FORCPU(me, thiscpu_tsc_hz));
			result += uint128_get64(since128);
		} else {
			result += since_nano / FORCPU(me, thiscpu_tsc_hz);
		}
	}
	return result;
}

/* Fix a TSC HZ calculation overflow by advancing both
 * `thiscpu_basetime.ts_kt' and `thiscpu_basetime.ts_tsc' in
 * order to shrink offsets.
 *
 * When running under QEMU, this function needs to be
 * about every 16 seconds, as the result of the value of
 * `tsc_elapsed * 1000000000' (1000000000 == NSEC_PER_SEC)
 * overflowing a 64-bit value.
 *
 * Also note that on QEMU, it appears as though the 100%
 * perfect HZ counter is also `1000000000' (at least for
 * me), so by doing `1000000000**2', you get the result of
 * `0x0de0b6b3a7640000', which you can multiply by 16 to
 * get `0xde0b6b3a76400000'. But trying to add yet another
 * instance of `1000000000**2' will result in an overflow,
 * thus resulting in the 16-second interval mentioned above.
 *
 * WARNING: Don't add any printk() to this function. Doing so
 *          will result in an infinite loop caused by printk
 *          calling realtime()->ktime()->tsc_now_to_ktime()->tsc_fix_overflow()
 */
PRIVATE NOPREEMPT NOBLOCK NONNULL((1)) void
NOTHROW(FCALL tsc_fix_overflow)(struct cpu *__restrict me,
                                tsc_t tsc_elapsed) {
	ktime_t seconds;
	tsc_t tsc_seconds;
	tsc_t tsc_remainder;
	seconds       = (ktime_t)(tsc_elapsed / FORCPU(me, thiscpu_tsc_hz));
	tsc_remainder = tsc_elapsed % FORCPU(me, thiscpu_tsc_hz);
	tsc_seconds   = tsc_elapsed - tsc_remainder;
	/* Account for whole seconds which have elapsed */
	FORCPU(me, thiscpu_basetime.ts_kt) += seconds * NSEC_PER_SEC;
	FORCPU(me, thiscpu_basetime.ts_tsc) += tsc_seconds;
	if unlikely(!seconds) {
		/* The value of `thiscpu_tsc_hz' is so great that we can't adjust
		 * whole seconds. - Instead, we must sacrifice precision and adjust
		 * by nanoseconds. */
		ktime_t nanoseconds;
		tsc_hz_t nano_hz;
		tsc_t tsc_nano_remainder;
		tsc_t tsc_nano_seconds;
		assert(tsc_remainder == tsc_elapsed);
		assert(tsc_seconds == 0);
		/* WARNING: This division right here results in a loss of precision! */
		nano_hz     = FORCPU(me, thiscpu_tsc_hz) / NSEC_PER_SEC;
		nanoseconds = (ktime_t)(tsc_elapsed / nano_hz);
		assert(nanoseconds);
		tsc_nano_remainder = tsc_elapsed % nano_hz;
		tsc_nano_seconds   = tsc_elapsed - tsc_nano_remainder;
		FORCPU(me, thiscpu_basetime.ts_kt) += nanoseconds;
		FORCPU(me, thiscpu_basetime.ts_tsc) += tsc_nano_seconds;
	}
}

/* Same as `tsc_to_ktime()', but the caller guaranties that `now' is an actual
 * timestamp that elapsed in the near past. Unlike `tsc_to_ktime()', this function
 * is allowed to assume that `now >=' any previously passed value for `now', since
 * the CPU was last initialized, also allowing it to move the internal TSC-to-KTIME
 * baseline forwards in order to account for offset overflows. */
PUBLIC NOBLOCK NOPREEMPT WUNUSED NONNULL((1)) ktime_t
NOTHROW(FCALL tsc_now_to_ktime)(struct cpu *__restrict me,
                                tsc_t now) {
	ktime_t result;
	tsc_t since, since_nano;
again:
	/* Determine the TSC offset since the last re-sync */
	assert(now <= tsc_get(me));
	assert(now >= FORCPU(me, thiscpu_basetime.ts_tsc));
	since = now - FORCPU(me, thiscpu_basetime.ts_tsc);
	/* Calculate the current boot-time offset. */
	if unlikely(OVERFLOW_UMUL(since, NSEC_PER_SEC, &since_nano))
		goto hz_overflow;
	result = FORCPU(me, thiscpu_basetime.ts_kt);
	result += since_nano / FORCPU(me, thiscpu_tsc_hz);
	return result;
hz_overflow:
	tsc_fix_overflow(me, since);
	goto again;
}

/* Convert a given `kt' timestamp into its TSC equivalent.
 * When `kt' lies so far into the future that TSC would overflow, return `TSC_MAX' instead.
 * NOTE: It is assumed that return >= <any `now' ever passed to `tsc_now_to_ktime'> */
PUBLIC NOBLOCK NOPREEMPT ATTR_PURE WUNUSED NONNULL((1)) tsc_t
NOTHROW(FCALL ktime_future_to_tsc)(struct cpu const *__restrict me,
                                   ktime_t kt) {
	ktime_t distance;
	tsc_t result;
	/* Calculate the distance from the baseline in nanoseconds. */
	assert(kt >= FORCPU(me, thiscpu_basetime.ts_kt));
	distance = kt - FORCPU(me, thiscpu_basetime.ts_kt);
	if (OVERFLOW_UMUL(distance, FORCPU(me, thiscpu_tsc_hz), &result)) {
		uint128_t distance128;
		/* Special handling to speed up handling of max timeouts. */
		if (kt == (ktime_t)-1)
			goto infinite;
		uint128_set(distance128, distance);
		uint128_mul(distance128, FORCPU(me, thiscpu_tsc_hz));
		uint128_div(distance128, NSEC_PER_SEC);
		result = uint128_get64(distance128);
	} else {
		result /= NSEC_PER_SEC;
	}
	if (OVERFLOW_UADD(result, FORCPU(me, thiscpu_basetime.ts_tsc), &result)) {
infinite:
		result = TSC_MAX; /* (effectively) an infinite timeout. */
	}
	return result;
}

/* Same as `ktime_future_to_tsc()', but make no assumptions on `kt' being in the future. */
PUBLIC NOBLOCK NOPREEMPT ATTR_PURE WUNUSED NONNULL((1)) tsc_t
NOTHROW(FCALL ktime_to_tsc)(struct cpu const *__restrict me,
                            ktime_t kt) {
	ktime_t distance;
	tsc_t result;
	bool is_future;
	is_future = true;
	/* Calculate the distance from the baseline in nanoseconds. */
	if unlikely(OVERFLOW_USUB(kt, FORCPU(me, thiscpu_basetime.ts_kt), &distance)) {
		distance  = FORCPU(me, thiscpu_basetime.ts_kt) - kt;
		is_future = false;
	}
	if (OVERFLOW_UMUL(distance, FORCPU(me, thiscpu_tsc_hz), &result)) {
		uint128_t distance128;
		if (kt == (ktime_t)-1)
			goto infinite;
		uint128_set(distance128, distance);
		uint128_mul(distance128, FORCPU(me, thiscpu_tsc_hz));
		uint128_div(distance128, NSEC_PER_SEC);
		result = uint128_get64(distance128);
	} else {
		result /= NSEC_PER_SEC;
	}
	if likely(is_future) {
		if (OVERFLOW_UADD(result, FORCPU(me, thiscpu_basetime.ts_tsc), &result)) {
infinite:
			result = TSC_MAX; /* (effectively) an infinite timeout. */
		}
	} else {
		if (OVERFLOW_USUB(result, FORCPU(me, thiscpu_basetime.ts_tsc), &result))
			result = 0; /* Can't go lower than this. */
	}
	return result;
}


/* Convert a ktime offset (read: not an absolute timestamp) to the equivalent # of TSC units. */
PUBLIC NOBLOCK NOPREEMPT ATTR_PURE WUNUSED NONNULL((1)) tsc_t
NOTHROW(FCALL ktime_offset_to_tsc)(struct cpu const *__restrict me,
                                   ktime_t num_nanoseconds) {
	tsc_t result;
	if (OVERFLOW_UMUL(num_nanoseconds, FORCPU(me, thiscpu_tsc_hz), &result)) {
		uint128_t num_nano_128;
		uint128_set(num_nano_128, num_nanoseconds);
		uint128_mul(num_nano_128, FORCPU(me, thiscpu_tsc_hz));
		uint128_div(num_nano_128, NSEC_PER_SEC);
		result = uint128_get64(num_nano_128);
	} else {
		result /= NSEC_PER_SEC;
	}
	return result;
}

/* Convert a tsc offset (read: not an absolute tick value) to the equivalent # of nanoseconds. */
PUBLIC NOBLOCK NOPREEMPT ATTR_PURE WUNUSED NONNULL((1)) ktime_t
NOTHROW(FCALL tsc_offset_to_ktime)(struct cpu const *__restrict me,
                                   tsc_t num_ticks) {
	ktime_t result;
	if (OVERFLOW_UMUL(num_ticks, NSEC_PER_SEC, &result)) {
		uint128_t num_ticks_128;
		uint128_set(num_ticks_128, num_ticks);
		uint128_mul(num_ticks_128, NSEC_PER_SEC);
		uint128_div(num_ticks_128, FORCPU(me, thiscpu_tsc_hz));
		result = uint128_get64(num_ticks_128);
	} else {
		result /= FORCPU(me, thiscpu_tsc_hz);
	}
	return result;
}





/* Return the current kernel time (in nano seconds since `boottime')
 * WARNING: The results of this function may be inconsistent when called
 *          from different CPUs (CPU#2 may return a lower value after CPU#1
 *          already returned a greater value)
 *          If this is a problem, you should instead use `ktime_stable()',
 *          but not that for timeouts and the like, the scheduler uses `ktime()'
 * NOTE: This function is the same as doing `tsc_now_to_ktime(tsc_now())' while
 *       having preemption disabled. */
PUBLIC NOBLOCK WUNUSED ktime_t
NOTHROW(KCALL ktime)(void) {
	ktime_t result;
	pflag_t was;
	struct cpu *me;
	tsc_t now;
	was = PREEMPTION_PUSHOFF();
	me     = THIS_CPU;
	now    = tsc_get(me);
	result = tsc_now_to_ktime(THIS_CPU, now);
	PREEMPTION_POP(was);
	return result;
}


PRIVATE atomic64_t last_stable_ktime = ATOMIC64_INIT(0);

/* Same as `ktime()', but ensure that the `return >= <any-previous-return>' */
PUBLIC NOBLOCK WUNUSED ktime_t
NOTHROW(KCALL ktime_stable)(void) {
	ktime_t result;
	result = ktime();
	/* Prevent the ktime()-clock from running backwards.
	 * This can happen for 3 reasons:
	 *   #1: The clock was changed externally
	 *   #2: The TSC counter was suspended via external means (e.g. an attached debugger)
	 *   #3: A minor discrepancy between the timestamps of different CPUs
	 *       XXX: Research how an OS can minimize these discrepancies!
	 */
	for (;;) {
		u64 oldval;
		oldval = atomic64_read(&last_stable_ktime);
		if unlikely(result <= oldval) {
			result = oldval;
			break;
		}
		if (atomic64_cmpxch_weak(&last_stable_ktime,
		                         oldval, result))
			break;
	}
	return result;
}



/* Timestamp of when the kernel was booted. */
DATDEF struct timespec boottime_ ASMNAME("boottime");
PUBLIC struct timespec boottime_ = { 0, 0 };

/* Convert a given ktime timestamp into a `struct timespec'.
 * This is done by adding `boottime' to the given value. */
PUBLIC NOBLOCK WUNUSED ATTR_PURE struct timespec
NOTHROW(FCALL ktime_to_timespec)(ktime_t t) {
	struct timespec result;
	result.tv_sec  = (time_t)(t / NSEC_PER_SEC);
	result.tv_nsec = (syscall_ulong_t)(t % NSEC_PER_SEC);
	result += boottime;
	return result;
}

/* Convert a given `struct timespec' into a ktime timestamp.
 * This is done by subtracting `boottime' from the given value.
 * NOTE: When the given timestamp `t' points at, or before `boottime',
 *       then this function will return `0', as it is impossible to
 *       represent a ktime-timestamp that happened before the system
 *       goto booted.
 * NOTE: When the given `t' is located so far ahead of `boottime' that
 *       the return value would overflow, the value is clamed to the
 *       maximum possible value of `(ktime_t)-1' */
PUBLIC NOBLOCK WUNUSED ATTR_PURE NONNULL((1)) ktime_t
NOTHROW(FCALL timespec_to_ktime)(struct timespec const *__restrict t) {
	ktime_t result;
	struct timespec diff;
	diff = *t - boottime;

	/* Check for special case: negative second value,
	 * meaning that the given `t' happened before the
	 * system was booted.
	 *
	 * In this case, clamp the ktime timestamp to point
	 * to the moment the system was booted.
	 *
	 * This is required for situations where an absolute
	 * timeout value is specified as a 0-timespec, which
	 * should then be handled as a request to time-out
	 * immediately. */
	if unlikely(diff.tv_sec < 0)
		return 0;

	/* If the ktime timestamp value overflows, clamp it to its max
	 * possible value, which other scheduling components will interpret
	 * as an infinite timeout. */
	if (OVERFLOW_UMUL((ktime_t)diff.tv_sec, NSEC_PER_SEC, &result))
		goto infinite;
	if (OVERFLOW_UADD(result, diff.tv_nsec, &result))
		goto infinite;

	return result;
infinite:
	return (ktime_t)-1;
}

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
PUBLIC NOBLOCK WUNUSED struct timespec
NOTHROW(KCALL realtime)(void) {
	return ktime_to_timespec(ktime());
}


DECL_END

#endif /* !GUARD_KERNEL_SRC_SCHED_TSC_C */
