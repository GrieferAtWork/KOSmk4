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
#ifndef GUARD_KERNEL_SRC_SCHED_TIME_C
#define GUARD_KERNEL_SRC_SCHED_TIME_C 1
#define WANT_INT128_CXX_INTEGRATION 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <debugger/rt.h>
#include <kernel/driver.h>
#include <kernel/malloc.h>
#include <kernel/panic.h>
#include <kernel/printk.h>
#include <kernel/types.h>
#include <sched/cpu.h>
#include <sched/task.h>
#include <sched/time.h>

#include <hybrid/atomic.h>
#include <hybrid/overflow.h>
#include <hybrid/typecore.h>

#include <kos/jiffies.h>
#include <sys/param.h> /* HZ */

#include <assert.h>
#include <int128.h>
#include <inttypes.h>
#include <stdint.h>

/* How many ticks to wait before performing another realtime re-sync */
#ifndef CPU_RESYNC_DELAY_IN_TICKS
#define CPU_RESYNC_DELAY_IN_TICKS (HZ / 2) /* twice per second */
#endif /* !CPU_RESYNC_DELAY_IN_TICKS */


DECL_BEGIN

#ifndef ARCH_DEFAULT_REALTIME_CLOCK
#define ARCH_DEFAULT_REALTIME_CLOCK NULL
#endif /* !ARCH_DEFAULT_REALTIME_CLOCK */

/* [0..1] The used realtime system clock */
PUBLIC XATOMIC_REF(struct realtime_clock_struct)
realtime_clock = XATOMIC_REF_INIT(ARCH_DEFAULT_REALTIME_CLOCK);

/* Set to true/false by `arch_cpu_(enable|disable)_preemptive_interrupts_nopr()' */
PUBLIC ATTR_PERCPU bool arch_cpu_preemptive_interrupts_disabled = true;


/* Destroy the given realtime clock. */
PUBLIC NOBLOCK void
NOTHROW(KCALL realtime_clock_destroy)(struct realtime_clock_struct *__restrict self) {
	if (self->rc_fini)
		(*self->rc_fini)(self);
	decref(self->rc_driver);
	kfree(self);
}





struct cpu_timestamp {
	struct timespec               ct_real; /* Realtime */
	jtime_t                       ct_cpuj; /* CPU time jiffies */
	quantum_diff_t                ct_cpuq; /* CPU time quantum */
	struct realtime_clock_struct *ct_rtc;  /* [weak][0..1] The RPC used for the re-sync. */
};


/* Per-cpu time keeping variables */
PUBLIC ATTR_PERCPU jtime_t volatile thiscpu_jiffies = 0;
PUBLIC ATTR_PERCPU quantum_diff_t volatile thiscpu_quantum_offset = 0;
PUBLIC ATTR_PERCPU quantum_diff_t volatile thiscpu_quantum_length = (quantum_diff_t)-1;

/* prevent issues hardware timer roll-over happening
 * before we've able to read the timestamp counter. */
PRIVATE ATTR_PERCPU jtime_t        thiscpu_last_qtime_j = 0;
PRIVATE ATTR_PERCPU quantum_diff_t thiscpu_last_qtime_q = 0;
PRIVATE ATTR_PERCPU bool thiscpu_jiffi_pending = false;

/* Timestamp for the last realtime re-sync made by the CPU */
PRIVATE ATTR_PERCPU struct cpu_timestamp thiscpu_last_resync = {
	/* .ct_real = */ {
		/* .tv_sec  = */ 0,
		/* .tv_nsec = */ 0
	},
	/* .ct_cpuj = */ 0,
	/* .ct_cpuq = */ 0,
	/* .ct_rtc  = */ NULL
};

typedef __CRT_PRIVATE_SINT(__SIZEOF_JTIME_T__) signed_jtime_t;

/* Perform for task activity by logging a switch from
 * `oldthread' to `newthread' taking place at the specified time. */
PRIVATE NOBLOCK NONNULL((1, 2)) void
NOTHROW(KCALL cpu_account_activity)(struct task *__restrict oldthread,
                                    struct task *__restrict newthread,
                                    jtime_t switch_jtime,
                                    quantum_diff_t switch_qtime,
                                    quantum_diff_t switch_qsize);


/* Call `arch_cpu_update_quantum_length_nopr()' and add its return value to
 * the offset in `FORCPU(self, thiscpu_quantum_offset)' */
PRIVATE NOBLOCK NOPREEMPT void
NOTHROW(FCALL cpu_update_quantum_length_and_increment_offset)(struct cpu *__restrict me) {
	jtime_t /*  */ cpu_jtime;
	quantum_diff_t cpu_qelps;
	quantum_diff_t cpu_qsize;
	quantum_diff_t elapsed;
	elapsed   = arch_cpu_update_quantum_length_nopr(me);
	cpu_jtime = FORCPU(me, thiscpu_jiffies);
	cpu_qelps = FORCPU(me, thiscpu_quantum_offset);
	cpu_qsize = FORCPU(me, thiscpu_quantum_length);
	if unlikely(OVERFLOW_UADD(cpu_qelps, elapsed, &cpu_qelps)) {
		quantum_diff_t num_jiffies;
		num_jiffies = ((quantum_diff_t)-1) / cpu_qsize;
		cpu_jtime += num_jiffies;
		cpu_qelps -= num_jiffies * cpu_qsize;
	}
	if (cpu_qelps >= cpu_qsize) {
		cpu_jtime += cpu_qelps / cpu_qsize;
		cpu_qelps = (cpu_qelps % cpu_qsize);
	}
	/* Save the new jtime/quantum offset values. */
	FORCPU(me, thiscpu_jiffies)        = cpu_jtime;
	FORCPU(me, thiscpu_quantum_offset) = cpu_qelps;
	COMPILER_BARRIER();
}



/* Return the result of `(a * b + c) / d' such that overflow errors are handled by reducing the precision */
PRIVATE NOBLOCK NOPREEMPT quantum_diff_t
NOTHROW(FCALL rescale_qsize)(u64 a, quantum_diff_t b, u64 c, u64 d) {
	u64 temp;
	u64 oldd = d;
	assert(d != 0);
	/* Divide operands by 2 until the multiplication doesn't overflow.
	 * NOTE: Doing this _does_ cause a loss in precision, but that's OK. */
	while (OVERFLOW_UMUL(a, b, &temp)) {
reduce_precision:
		a >>= 1;
		d >>= 1;
	}
	if (OVERFLOW_UADD(temp, c, &temp))
		goto reduce_precision;
	if likely(d != 0)
		return (quantum_diff_t)(temp / d);
	while (oldd) {
		temp <<= 1;
		oldd >>= 1;
	}
	if (temp > (quantum_diff_t)-1)
		temp = (quantum_diff_t)-1; /* Shouldn't happen... */
	return (quantum_diff_t)temp;
}

/* Calculate the new quantum length, where
 *  - old_qsize: The old quantum length
 *  - pfc_qsize: The perfect quantum length with which no error would have
 *               occurred over the course of the previous quantum.
 * @param: realtime_elapsed:   The elapsed realtime (according to RTC)
 * @param: realtime_precision: The precision of the realtime clock.
 * @param: min_error:          The smallest error between CPU and RTC time. */
PRIVATE NOBLOCK NOPREEMPT quantum_diff_t
NOTHROW(FCALL calculate_new_qsize)(quantum_diff_t old_qsize,
                                   quantum_diff_t pfc_qsize,
                                   struct timespec const *__restrict realtime_elapsed,
                                   struct timespec const *__restrict realtime_precision,
                                   struct timespec const *__restrict min_error) {
	/* TODO: Take the # of realtime elapsed, vs. the realtime precision into
	 *       account, where:
	 *       A large (realtime_elapsed / realtime_precision) ratio should cause our
	 *       return value to lean more towards `old_qsize', while a small ratio should
	 *       cause our return value to lean more towards `pfc_qsize' (though with a
	 *       max ratio such that we end up with a 50-50 ratio at most):
	 * >> ratio = realtime_elapsed / realtime_precision
	 */
	(void)realtime_elapsed;
	(void)realtime_precision;
	(void)min_error;

	if (pfc_qsize <= old_qsize) {
		/* Must round down */
		return (quantum_diff_t)(((u64)pfc_qsize + old_qsize) / 2);
	} else {
		/* Must round up */
		return (quantum_diff_t)(((u64)pfc_qsize + old_qsize + 1) / 2);
	}
}


/* Perform a realtime re-sync.
 * WARNING: This function may reset the current quantum! */
PRIVATE NOBLOCK NOPREEMPT void
NOTHROW(FCALL cpu_resync_realtime)(struct cpu *__restrict me,
                                   struct timespec const *__restrict nts_realtime,
                                   struct realtime_clock_struct *__restrict nts_rtc,
                                   jtime_t nts_jtime, quantum_diff_t nts_qelapsed,
                                   bool log_messages) {
	struct cpu_timestamp nts; /* NewTimeStamp */
	struct cpu_timestamp ots; /* OldTimeStamp */
	struct timespec cpu_realtime;
	quantum_diff_t cpu_qoffs; /* CPU quantum offset */
	quantum_diff_t cpu_qsize; /* CPU time quantum size */
	jtime_t /*  */ cpu_resyncrel_jtime; /* Relative CPU jiffies since last re-sync */
	quantum_diff_t cpu_resyncrel_qtime; /* Relative CPU quantum since last re-sync */

	/* Fill in timestamp information. */
	nts.ct_rtc  = nts_rtc;
	nts.ct_real = *nts_realtime;
	nts.ct_cpuj = nts_jtime;
	nts.ct_cpuq = nts_qelapsed;

	/* Calculate the realtime for our current CPU, as it would be returned by
	 * `realtime()' for the values we received from `cpu_quantum_elapsed_nopr()'
	 * That timestamp is the compared against what the RTC has given us, so that
	 * was may determine the relative clock error. */
	COMPILER_BARRIER();
	ots       = FORCPU(me, thiscpu_last_resync);
	cpu_qoffs = FORCPU(me, thiscpu_quantum_offset);
	cpu_qsize = FORCPU(me, thiscpu_quantum_length);
	COMPILER_BARRIER();

	/* Calculate the whole quantum offset:
	 *   - cpu_qoffs:   Addend
	 *   - nts.ct_cpuq: Real, current quantum time */
	if unlikely(OVERFLOW_UADD(nts.ct_cpuq, cpu_qoffs, &nts.ct_cpuq)) {
		quantum_diff_t num_jiffies;
		num_jiffies = ((quantum_diff_t)-1) / cpu_qsize;
		nts.ct_cpuj += num_jiffies;
		nts.ct_cpuq -= num_jiffies * cpu_qsize;
	}
	if unlikely(nts.ct_cpuq >= cpu_qsize) {
		nts.ct_cpuj += nts.ct_cpuq / cpu_qsize;
		nts.ct_cpuq = (nts.ct_cpuq % cpu_qsize);
	}

	/* Right now, our cpu's quantum time is:
	 * >> nts.ct_cpuj * cpu_qsize + nts.ct_cpuq
	 * Which is expressed in `1 / (cpu_qsize * HZ)'-th seconds;
	 *
	 * With this in mind, subtract the timestamp of the last
	 * realtime resync from the current cpu-local quantum time. */
	cpu_resyncrel_jtime = nts.ct_cpuj - ots.ct_cpuj;
	if (OVERFLOW_USUB(nts.ct_cpuq, ots.ct_cpuq, &cpu_resyncrel_qtime)) {
		quantum_diff_t num_jiffies;
		num_jiffies = ((quantum_diff_t)-1) / cpu_qsize;
		cpu_resyncrel_jtime -= num_jiffies;
		cpu_resyncrel_qtime += num_jiffies * cpu_qsize;
	}
	if (cpu_resyncrel_qtime >= cpu_qsize) {
		cpu_resyncrel_jtime += cpu_resyncrel_qtime / cpu_qsize;
		cpu_resyncrel_qtime = (cpu_resyncrel_qtime % cpu_qsize);
	}

	/* The current realtime is now described by:
	 * >> cpu_realtime + QUANTUM_TO_SECONDS(cpu_resyncrel_jtime * cpu_qsize + cpu_resyncrel_qtime);
	 * To calculate that timestamp, start by dealing with `cpu_resyncrel_jtime', which is known
	 * to be in units of 1/HZ seconds!
	 * Though still note that `cpu_resyncrel_jtime' may be negative! */
	cpu_realtime = ots.ct_real;
	if unlikely((signed_jtime_t)cpu_resyncrel_jtime < 0) {
		intptr_t nsecs_addend;
		cpu_resyncrel_jtime = (jtime_t)-(signed_jtime_t)cpu_resyncrel_jtime;
		cpu_realtime.tv_sec -= cpu_resyncrel_jtime / HZ;
		nsecs_addend = (uintptr_t)(((u64)cpu_resyncrel_qtime * (__NSECS_PER_SEC / HZ)) / cpu_qsize);
		nsecs_addend -= ((intptr_t)cpu_resyncrel_jtime % HZ) * (__NSECS_PER_SEC / HZ);
		/* Also deal with the quantum offset. */
		if unlikely(nsecs_addend >= 0) {
			cpu_realtime.add_nanoseconds((uintptr_t)nsecs_addend);
		} else {
			cpu_realtime.sub_nanoseconds((uintptr_t)-nsecs_addend);
		}
	} else {
		u64 nsecs;
		cpu_realtime.tv_sec += cpu_resyncrel_jtime / HZ;
		nsecs = cpu_realtime.tv_nsec;
		/* Also deal with the quantum offsets. */
		nsecs += (cpu_resyncrel_jtime % HZ) * (__NSECS_PER_SEC / HZ);
		nsecs += ((u64)cpu_resyncrel_qtime * (__NSECS_PER_SEC / HZ)) / cpu_qsize;
		if (nsecs > __NSECS_PER_SEC) {
			cpu_realtime.tv_sec += (time_t)(nsecs / __NSECS_PER_SEC);
			nsecs %= __NSECS_PER_SEC;
		}
		cpu_realtime.tv_nsec = (syscall_ulong_t)nsecs;
	}

	if unlikely(nts.ct_rtc != ots.ct_rtc) {
		/* Real-time clock changed (or was installed)
		 * If it got freshly installed, then we may lazily start using it.
		 * If it got changed, then whoever changed it must manually update
		 * CPU clocks, and we must no longer re-sync periodically until
		 * they do! */
		if (ots.ct_rtc != NULL)
			goto done;
		/* Lazily start using the new RTC */
		if (nts.ct_real > cpu_realtime) {
			/* Make the clock jump into the future to catch up with realtime */
			FORCPU(me, thiscpu_last_resync) = nts;
			goto done;
		}
	}

	/* Figure out what kind of time error we're dealing with. */
	if (nts.ct_real > cpu_realtime) {
		/* The CPU's tick counter is running too slow */
		u64 quantum_cpu_elapsed; /* Quantum counter for elapsed CPU time (since last re-sync) */
		u64 quantum_rtc_elapsed; /* Quantum counter for elapsed RTC time (since last re-sync) */
		struct timespec rtc_elapsed;
		quantum_cpu_elapsed = (u64)cpu_resyncrel_jtime * cpu_qsize + cpu_resyncrel_qtime;
		rtc_elapsed         = nts.ct_real - ots.ct_real;
		quantum_rtc_elapsed = (u64)rtc_elapsed.tv_sec * HZ * cpu_qsize;
		quantum_rtc_elapsed += ((u64)rtc_elapsed.tv_nsec * cpu_qsize) / (__NSECS_PER_SEC / HZ);
		if likely(quantum_rtc_elapsed > quantum_cpu_elapsed) {
			quantum_diff_t perfect_cpu_qsize;
			quantum_diff_t new_cpu_qsize;
			struct timespec min_clock_error;
			/* Over the duration of the last `quantum_cpu_elapsed' quantum units, a total
			 * error of (at least, as true RTC may be even `nts.ct_rtc->rc_precision'
			 * seconds greater due to clock precision) `quantum_rtc_elapsed -
			 * quantum_cpu_elapsed' has occurred.
			 * Fix this problem by first calculating a new quantum length that, if it had
			 * been used over the duration since the last re-sync, `quantum_rtc_elapsed'
			 * would be equal to `quantum_cpu_elapsed'.
			 * Do this calculating the perfect quantum length as X in:
			 *   quantum_cpu_elapsed    quantum_rtc_elapsed
			 *   ------------------- == -------------------
			 *            X                  cpu_qsize
			 *
			 * Or solved for `X':
			 *   X = (quantum_cpu_elapsed * cpu_qsize) / quantum_rtc_elapsed
			 * NOTE: Do a floor-divide in this final division, so that our
			 *       quantum length ends up a tiny bit smaller (since we
			 *       can only set whole numbers as quantum length)
			 *       This way, if it ends up being too small, it won't be our
			 *       branch that has to do the next quantum re-adjustment, but
			 *       rather the "The CPU's tick counter is running too fast"
			 *       one, which'll round upwards
			 *
			 * Example:
			 *       RTC    0       1       2       3       4       5
			 *              |       |       |       |       |       |
			 *         -----+-------+-+-----+---+---+-----+-+------[+]------>
			 *              |         |         |         |         |
			 *  Slow CPU    0         1         2         3         4
			 *              |---------|
			 *               cpu_qsize
			 *
			 *  nts.ct_real  = { 5, 0 }
			 *  cpu_realtime = { 4, 0 } */
			perfect_cpu_qsize = rescale_qsize(quantum_cpu_elapsed,
			                                  cpu_qsize, 0,
			                                  quantum_rtc_elapsed);
			if unlikely(perfect_cpu_qsize > cpu_qsize)
				goto done; /* Shouldn't happen... (but could due to overflow...) */
			/* With the perfect quantum length calculated, don't go all in about
			 * using it, but rather use the average between the old quantum length,
			 * and the new one! (once again: round downwards) */
			min_clock_error = nts.ct_real - cpu_realtime;
			new_cpu_qsize = calculate_new_qsize(cpu_qsize,
			                                    perfect_cpu_qsize,
			                                    &rtc_elapsed,
			                                    &nts_rtc->rc_precision,
			                                    &min_clock_error);
			assert(new_cpu_qsize <= cpu_qsize);
			if (new_cpu_qsize < cpu_qsize) {
				if (log_messages) {
					printk(KERN_INFO "[cpu#%u][-] Adjust quantum length %I32u -> %I32u "
					                 "(cpu clock was running too slow)\n",
					       me->c_id, cpu_qsize, new_cpu_qsize);
				}
				/* Make the clock jump into the future to catch up with realtime */
				COMPILER_BARRIER();
				FORCPU(me, thiscpu_last_resync)    = nts;
				FORCPU(me, thiscpu_quantum_length) = new_cpu_qsize;
				COMPILER_BARRIER();
				cpu_update_quantum_length_and_increment_offset(me);
				COMPILER_BARRIER();
			}
		}
	} else {
		struct timespec upper_error;
		upper_error = nts.ct_real + nts.ct_rtc->rc_precision;
		if (upper_error < cpu_realtime) {
			/* The CPU's tick counter is running too fast */
			u64 quantum_cpu_elapsed; /* Quantum counter for elapsed CPU time (since last re-sync) */
			u64 quantum_rtc_elapsed; /* Quantum counter for elapsed RTC time (since last re-sync) */
			struct timespec rtc_elapsed;
			quantum_cpu_elapsed = (u64)cpu_resyncrel_jtime * cpu_qsize + cpu_resyncrel_qtime;
			rtc_elapsed         = nts.ct_real - ots.ct_real;
			quantum_rtc_elapsed = (u64)rtc_elapsed.tv_sec * HZ * cpu_qsize;
			quantum_rtc_elapsed += ((u64)rtc_elapsed.tv_nsec * cpu_qsize) / (__NSECS_PER_SEC / HZ);
			if likely(quantum_rtc_elapsed < quantum_cpu_elapsed && quantum_rtc_elapsed != 0) {
				quantum_diff_t perfect_cpu_qsize;
				quantum_diff_t new_cpu_qsize;
				struct timespec min_clock_error;
				/* Same as above, but round downwards (thus causing the final quantum length
				 * to be a tiny bit shorter than what would be the perfect length)
				 *
				 * Example:
				 *
				 *       RTC    0       1       2       3       4
				 *              |       |       |       |       |
				 *         -----+-----+-+---+---+-+----[+]------+------->
				 *              |     |     |     |     |
				 *  Fast CPU    0     1     2     3     4
				 *              |-----|
				 *             cpu_qsize
				 *
				 *  nts.ct_real  = { 3, 0 }
				 *  cpu_realtime = { 4, 0 } */
				perfect_cpu_qsize = rescale_qsize(quantum_cpu_elapsed, cpu_qsize,
				                                  quantum_rtc_elapsed - 1,
				                                  quantum_rtc_elapsed);
				if unlikely(perfect_cpu_qsize < cpu_qsize)
					goto done; /* Shouldn't happen... (but could due to overflow...) */
				new_cpu_qsize = (perfect_cpu_qsize + cpu_qsize) / 2;
				min_clock_error = cpu_realtime - upper_error;
				new_cpu_qsize = calculate_new_qsize(cpu_qsize,
				                                    perfect_cpu_qsize,
				                                    &rtc_elapsed,
				                                    &nts_rtc->rc_precision,
				                                    &min_clock_error);
				assert(new_cpu_qsize >= cpu_qsize);
				if (new_cpu_qsize > cpu_qsize) {
					struct timespec cputime_since_nts;
					u64 quantum_since_nts;
					if (log_messages) {
						printk(KERN_INFO "[cpu#%u][+] Adjust quantum length %I32u -> %I32u "
						                 "(cpu clock was running too fast)\n",
						       me->c_id, cpu_qsize, new_cpu_qsize);
					}
					/* Modify `nts.ct_cpuj' and `nts.ct_cpuq', such that a call to realtime()
					 * performed after we're done here produces `cpu_realtime' as result.
					 * This must be done in order to prevent the clock from jumping backwards,
					 * which it otherwise would due to the CPU quantum length being altered.
					 *
					 * How this has to be done can be calculated by taking the realtime() formula:
					 *    realtime() == PERCPU(LAST_RESYNC_REALTIME) +
					 *                  QUANTUM_TIME_SINCE_LAST_RESYNC()
					 *    or rather:
					 *    realtime() == PERCPU(thiscpu_last_resync).ct_real +
					 *                  (QUANTUM_TIME() - PERCPU(thiscpu_last_resync).ct_cpu(j|q))
					 * By inserting values here, we get:
					 *    cpu_realtime == nts.ct_real +
					 *                    (OLD(nts.ct_cpu(j|q)) - NEW(nts.ct_cpu(j|q)))
					 * Re-arranging this (so we end up with `NEW(nts.ct_cpu(j|q))' on one side):
					 *    NEW(nts.ct_cpu(j|q)) == (nts.ct_real - cpu_realtime) + OLD(nts.ct_cpu(j|q))
					 *    NEW(nts.ct_cpu(j|q)) == OLD(nts.ct_cpu(j|q)) - (cpu_realtime - nts.ct_real)
					 */
					cputime_since_nts = cpu_realtime - nts.ct_real;
					quantum_since_nts = (u64)cputime_since_nts.tv_sec * HZ * new_cpu_qsize;
					quantum_since_nts += ((u64)cputime_since_nts.tv_nsec * new_cpu_qsize +
					                      (__NSECS_PER_SEC / HZ) - 1) / /* ceil-div */
					                     (__NSECS_PER_SEC / HZ);
					/* Fill in the proper timestamp for when this resync took (takes) places,
					 * such that the realtime() clock won't jump backwards.
					 * Instead, if our clock had been running too fast before (and we were
					 * ahead of actually RTC-realtime), our (now) slower quantum timings will
					 * eventually cause us to drift in the opposite direction, at which point
					 * the "The CPU's tick counter is running too slow" branch will correct
					 * timings once again, and to the point where everything should once again
					 * line up properly! */
					nts.ct_cpuj -= quantum_since_nts / new_cpu_qsize;
					quantum_since_nts %= new_cpu_qsize;
					if (OVERFLOW_USUB(nts.ct_cpuq, quantum_since_nts, &nts.ct_cpuq)) {
						quantum_diff_t num_jiffies;
						num_jiffies = ((quantum_diff_t)-1) / new_cpu_qsize;
						nts.ct_cpuj -= num_jiffies;
						nts.ct_cpuq += num_jiffies * new_cpu_qsize;
					}
					if (nts.ct_cpuq > new_cpu_qsize) {
						nts.ct_cpuj += nts.ct_cpuq / new_cpu_qsize;
						nts.ct_cpuq = (nts.ct_cpuq % new_cpu_qsize);
					}
					COMPILER_BARRIER();
					FORCPU(me, thiscpu_last_resync)    = nts;
					FORCPU(me, thiscpu_quantum_length) = new_cpu_qsize;
					COMPILER_BARRIER();
					cpu_update_quantum_length_and_increment_offset(me);
					COMPILER_BARRIER();
					goto done;
				}
			}
		}
		/* Lazily start using the new RTC */
		if unlikely(nts.ct_rtc != ots.ct_rtc) {
			struct timespec cputime_since_nts;
			u64 quantum_since_nts;
			cputime_since_nts = cpu_realtime - nts.ct_real;
			quantum_since_nts = (u64)cputime_since_nts.tv_sec * HZ * cpu_qsize;
			quantum_since_nts += ((u64)cputime_since_nts.tv_nsec * cpu_qsize +
			                      (__NSECS_PER_SEC / HZ) - 1) / /* ceil-div */
			                     (__NSECS_PER_SEC / HZ);
			/* Fill in the proper timestamp for when this resync took (takes)
			 * places, such that the realtime() clock won't jump backwards. */
			nts.ct_cpuj -= quantum_since_nts / cpu_qsize;
			quantum_since_nts %= cpu_qsize;
			if (OVERFLOW_USUB(nts.ct_cpuq, quantum_since_nts, &nts.ct_cpuq)) {
				quantum_diff_t num_jiffies;
				num_jiffies = ((quantum_diff_t)-1) / cpu_qsize;
				nts.ct_cpuj -= num_jiffies;
				nts.ct_cpuq += num_jiffies * cpu_qsize;
			}
			if (nts.ct_cpuq >= cpu_qsize) {
				nts.ct_cpuj += nts.ct_cpuq / cpu_qsize;
				nts.ct_cpuq = (nts.ct_cpuq % cpu_qsize);
			}
			COMPILER_BARRIER();
			FORCPU(me, thiscpu_last_resync) = nts;
			COMPILER_BARRIER();
			goto done;
		}
	}
done:
	;
}


#ifdef NDEBUG
#define cpu_resync_realtime_chk cpu_resync_realtime
#else /* NDEBUG */
PRIVATE NOBLOCK NOPREEMPT void
NOTHROW(FCALL cpu_resync_realtime_chk)(struct cpu *__restrict me,
                                       struct timespec const *__restrict nts_realtime,
                                       struct realtime_clock_struct *__restrict nts_rtc,
                                       jtime_t nts_jtime, quantum_diff_t nts_qelapsed,
                                       bool log_messages) {
	struct timespec before;
	struct timespec after;
	before = realtime();
	cpu_resync_realtime(me,
	                    nts_realtime,
	                    nts_rtc,
	                    nts_jtime,
	                    nts_qelapsed,
	                    log_messages);
	after = realtime();
	assertf(before <= after || kernel_poisoned(),
	        "Backwards realtime: { { %I64d, %Iu }, { %I64d, %Iu } } (diff: { %I64d, %Iu })\n",
	        (s64)before.tv_sec, (uintptr_t)before.tv_nsec,
	        (s64)after.tv_sec, (uintptr_t)after.tv_nsec,
	        (s64)(before - after).tv_sec,
	        (uintptr_t)(before - after).tv_nsec);
}
#endif /* !NDEBUG */

PRIVATE NOBLOCK NOPREEMPT void
NOTHROW(FCALL cpu_resync_realtime_at)(struct cpu *__restrict me,
                                      jtime_t nts_jtime,
                                      quantum_diff_t nts_qelapsed,
                                      bool log_messages) {
	REF struct realtime_clock_struct *rtc;
	rtc = realtime_clock.get_nopr();
	if likely(rtc) {
		struct timespec rtc_now;
		rtc_now = (*rtc->rc_gettime)(rtc);
		cpu_resync_realtime(me,
		                    &rtc_now,
		                    rtc,
		                    nts_jtime,
		                    nts_qelapsed,
		                    log_messages);
		decref_unlikely(rtc);
	}
}

#ifdef NDEBUG
#define cpu_resync_realtime_chk_at cpu_resync_realtime_at
#else /* NDEBUG */
PRIVATE NOBLOCK NOPREEMPT void
NOTHROW(FCALL cpu_resync_realtime_chk_at)(struct cpu *__restrict me,
                                          jtime_t nts_jtime,
                                          quantum_diff_t nts_qelapsed,
                                          bool log_messages) {
	REF struct realtime_clock_struct *rtc;
	rtc = realtime_clock.get_nopr();
	if likely(rtc) {
		struct timespec rtc_now;
		rtc_now = (*rtc->rc_gettime)(rtc);
		cpu_resync_realtime_chk(me,
		                        &rtc_now,
		                        rtc,
		                        nts_jtime,
		                        nts_qelapsed,
		                        log_messages);
		decref_unlikely(rtc);
	}
}
#endif /* !NDEBUG */


/* Returns the number of ticks that have passed since the start
 * of the current quantum. - The true current CPU-local time
 * (in ticks) can then be calculated as:
 * >> (thiscpu_jiffies * PERCPU(thiscpu_quantum_length)) + PERCPU(thiscpu_quantum_offset) + cpu_quantum_elapsed_nopr();
 * NOTE: The `*_nopr' variants may only be called when preemption is disabled! */
PUBLIC NOBLOCK NOPREEMPT WUNUSED NONNULL((1, 2)) quantum_diff_t
NOTHROW(FCALL cpu_quantum_elapsed_nopr)(struct cpu *__restrict me,
                                        jtime_t *__restrict preal_jtime) {
	quantum_diff_t qtime;
	jtime_t jtime;
	qtime = arch_cpu_quantum_elapsed_nopr(me);
	jtime = FORCPU(me, thiscpu_jiffies);
	if (qtime < FORCPU(me, thiscpu_last_qtime_q) &&
		jtime == FORCPU(me, thiscpu_last_qtime_j)) {
		/* Roll-over prior to actual interrupt / roll-over with lost interrupt.
		 * In either case, increment the jiffies counter now, and set the flag
		 * to indicate that the next scheduler interrupt shouldn't increment
		 * the counter (since we already did so for it) */
		FORCPU(me, thiscpu_jiffi_pending) = true;
		++FORCPU(me, thiscpu_jiffies);
		++jtime;
		if ((jtime % CPU_RESYNC_DELAY_IN_TICKS) == 0) {
			/* Can't call `cpu_resync_realtime_chk_at()' here, because that
			 * would form a loop:
			 *    cpu_quantum_elapsed_nopr() calls:
			 *    cpu_resync_realtime_at()   calls:
			 *    realtime()                 calls:
			 *    cpu_quantum_elapsed_nopr() calls:
			 *    ...
			 */
			cpu_resync_realtime_at(me,
			                       jtime,
			                       qtime,
			                       false);
		}
	}
	FORCPU(me, thiscpu_last_qtime_q) = qtime;
	FORCPU(me, thiscpu_last_qtime_j) = jtime;
	*preal_jtime = jtime;
	return qtime;
}


PRIVATE NOPREEMPT NOBLOCK NONNULL((1)) struct timespec
NOTHROW(FCALL realtime_at)(struct cpu *__restrict me,
                           jtime_t cpu_jtime,
                           quantum_diff_t cpu_qtime) {
	struct timespec resync_real; /* CPU last resync realtime */
	jtime_t         resync_cpuj; /* CPU last resync jiffies */
	quantum_diff_t  resync_cpuq; /* CPU last resync quantum */
	quantum_diff_t  cpu_qoffs;   /* CPU quantum offset */
	quantum_diff_t  cpu_qsize;   /* CPU time quantum size */
	resync_real = FORCPU(me, thiscpu_last_resync.ct_real);
	resync_cpuj = FORCPU(me, thiscpu_last_resync.ct_cpuj);
	resync_cpuq = FORCPU(me, thiscpu_last_resync.ct_cpuq);
	cpu_qoffs   = FORCPU(me, thiscpu_quantum_offset);
	cpu_qsize   = FORCPU(me, thiscpu_quantum_length);
	/* Calculate the whole quantum offset:
	 *   - cpu_qoffs: Addend
	 *   - cpu_qtime: Real, current quantum time */
	if unlikely(OVERFLOW_UADD(cpu_qtime, cpu_qoffs, &cpu_qtime)) {
		quantum_diff_t num_jiffies;
		num_jiffies = ((quantum_diff_t)-1) / cpu_qsize;
		cpu_jtime  += num_jiffies;
		cpu_qtime  -= num_jiffies * cpu_qsize;
	}
	/* Right now, our cpu's quantum time is:
	 * >> cpu_jtime * cpu_qsize + cpu_qtime
	 * Which is expressed in `1 / (cpu_qsize * HZ)'-th seconds;
	 *
	 * With this in mind, subtract the timestamp of the last
	 * realtime resync from the current cpu-local quantum time.
	 * WARNING: Due to resync-offsets, this subtraction may produce a negative result! */
	cpu_jtime -= resync_cpuj;
	if (OVERFLOW_USUB(cpu_qtime, resync_cpuq, &cpu_qtime)) {
		quantum_diff_t num_jiffies;
		num_jiffies = ((quantum_diff_t)-1) / cpu_qsize;
		cpu_jtime  -= num_jiffies;
		cpu_qtime  += num_jiffies * cpu_qsize;
	}
	if unlikely(cpu_qtime >= cpu_qsize) {
		cpu_jtime += cpu_qtime / cpu_qsize;
		cpu_qtime = (cpu_qtime % cpu_qsize);
	}
	/* The current realtime is now described by:
	 * >> cpu_resync.ct_real + QUANTUM_TO_SECONDS(cpu_jtime * cpu_qsize + cpu_qtime);
	 * To calculate that timestamp, start by dealing with `cpu_jtime', which is known
	 * to be in units of 1/HZ seconds!
	 * Though still note that `cpu_jtime' may be negative! */
	if unlikely((signed_jtime_t)cpu_jtime < 0) {
		intptr_t nsecs_addend;
		cpu_jtime = (jtime_t)-(signed_jtime_t)cpu_jtime;
		resync_real.tv_sec -= cpu_jtime / HZ;
		nsecs_addend = (uintptr_t)(((u64)cpu_qtime * (__NSECS_PER_SEC / HZ)) / cpu_qsize);
		nsecs_addend -= ((intptr_t)cpu_jtime % HZ) * (__NSECS_PER_SEC / HZ);
		/* Also deal with the quantum offset. */
		if unlikely(nsecs_addend >= 0) {
			resync_real.add_nanoseconds((uintptr_t)nsecs_addend);
		} else {
			resync_real.sub_nanoseconds((uintptr_t)-nsecs_addend);
		}
	} else {
		u64 nsecs;
		resync_real.tv_sec += cpu_jtime / HZ;
		nsecs = resync_real.tv_nsec;
		/* Also deal with the quantum offsets. */
		nsecs += (cpu_jtime % HZ) * (__NSECS_PER_SEC / HZ);
		nsecs += ((u64)cpu_qtime * (__NSECS_PER_SEC / HZ)) / cpu_qsize;
		if (nsecs > __NSECS_PER_SEC) {
			resync_real.tv_sec += (time_t)(nsecs / __NSECS_PER_SEC);
			nsecs %= __NSECS_PER_SEC;
		}
		resync_real.tv_nsec = (syscall_ulong_t)nsecs;
	}
	return resync_real;
}

/* Wake-up all timeout-sleeping threads from `me' who's
 * timeout has expired, or will expire over the course
 * of the next CPU tick.
 * >> timeout <= (cpu_jtime + 1) * cpu_qsize +
 * >>            thiscpu_quantum_offset +
 * >>            cpu_qelapsed; */
PRIVATE NOPREEMPT NOBLOCK NONNULL((1)) void
NOTHROW(FCALL cpu_timeout_sleeping_threads)(struct cpu *__restrict me,
                                            jtime_t cpu_jtime,
                                            quantum_diff_t cpu_qelapsed) {
	/* Check for sleeping threads that should be woken. */
	if (me->c_sleeping != NULL) {
		struct timespec now;
		struct task *next;
		struct task *lsleeper; /* First sleeping thread to wake up */
		struct task *rsleeper; /* Last sleeping thread to wake up */

		lsleeper = me->c_sleeping;
#ifndef __OPTIMIZE_SIZE__
		/* Check for simple case: None of the waiting threads use any timeouts */
		if (lsleeper->t_sched.s_asleep.ss_timeout.tv_sec == INT64_MAX)
			return;
#endif /* !__OPTIMIZE_SIZE__ */

		/* Calculate the realtime for the given `cpu_jtime + cpu_qelapsed' */
		now = realtime_at(me, cpu_jtime, cpu_qelapsed);

		/* Wake up all threads with a `timeout <= now'
		 * NOTE: Sleeping threads are sorted such that the next thread to time-out appears first. */
		if (lsleeper->t_sched.s_asleep.ss_timeout > now)
			return; /* Special (and simple) case: All thread timeouts are still in the future. */
		for (rsleeper = lsleeper;;) {
			STATIC_ASSERT(offsetof(struct task, t_sched.s_running.sr_runprv) !=
			              offsetof(struct task, t_sched.s_asleep.ss_tmonxt));
			ATOMIC_FETCHOR(rsleeper->t_flags, TASK_FTIMEOUT | TASK_FRUNNING);
			next = rsleeper->t_sched.s_asleep.ss_tmonxt;
			if (!next)
				break; /* No more threads to wake up. */
			if (next->t_sched.s_asleep.ss_timeout > now)
				break; /* This thread shouldn't be woken up, yet. */
			rsleeper->t_sched.s_running.sr_runnxt = next;
			next->t_sched.s_running.sr_runprv     = rsleeper;
			rsleeper                              = next;
		}
		me->c_sleeping = next;
		if (next)
			next->t_sched.s_asleep.ss_pself = &me->c_sleeping;
		/* Re-schedule all of the sleepers. */
		next = me->c_current->t_sched.s_running.sr_runnxt;
		lsleeper->t_sched.s_running.sr_runprv      = me->c_current;
		rsleeper->t_sched.s_running.sr_runnxt      = next;
		next->t_sched.s_running.sr_runprv          = rsleeper;
		me->c_current->t_sched.s_running.sr_runnxt = lsleeper;
		cpu_assert_integrity();
	}
}


/* The C-level implementation of the scheduling interrupt
 * that is fired periodically for the purposes of preemption. */
INTERN NOBLOCK NONNULL((1, 2)) struct task *
NOTHROW(FCALL cpu_scheduler_interrupt)(struct cpu *__restrict me,
                                       struct task *__restrict thread) {
	/* NOTE: Preemption is disabled while we're in here! */
	struct task *next;
	jtime_t /*  */ cpu_jtime; /* J-time */
	quantum_diff_t cpu_qelps; /* Quantum-elapsed */
#ifndef NDEBUG
	struct timespec before;
	struct timespec after;
	before = realtime();
#endif /* !NDEBUG */

	assertf(thread == me->c_current,
	        "thread        = %p\n"
	        "me            = %p\n"
	        "me->c_id      = %u\n"
	        "me->c_current = %p\n",
	        thread, me,
	        (unsigned int)me->c_id,
	        me->c_current);
	cpu_assert_running(thread);

	/* Check if this interrupt was already noticed as being pending */
	if (FORCPU(me, thiscpu_jiffi_pending)) {
		FORCPU(me, thiscpu_jiffi_pending) = false;
		/* Query the current quantum-elapsed value (which should be quite small) */
		cpu_qelps = cpu_quantum_elapsed_nopr(me, &cpu_jtime);
		if ((cpu_jtime % CPU_RESYNC_DELAY_IN_TICKS) == 0)
			goto do_resync_rtc;
	} else {
		cpu_jtime = ++FORCPU(me, thiscpu_jiffies);
		if ((cpu_jtime % CPU_RESYNC_DELAY_IN_TICKS) == 0) {
			/* Try to re-sync the CPU timer with the realtime clock. */
			REF struct realtime_clock_struct *rtc;
do_resync_rtc:
			rtc = realtime_clock.get_nopr();
			if likely(rtc != NULL) {
				struct timespec rtc_now;
				COMPILER_BARRIER();
				rtc_now   = (*rtc->rc_gettime)(rtc);
				cpu_qelps = arch_cpu_quantum_elapsed_nopr(me);
				COMPILER_BARRIER();
				/* Try to re-sync the CPU clock with the realtime clock. */
				cpu_resync_realtime_chk(me,
				                        &rtc_now,
				                        rtc,
				                        cpu_jtime,
				                        cpu_qelps,
				                        true);
				decref_unlikely(rtc);
			}
		}
		cpu_qelps = arch_cpu_quantum_elapsed_nopr(me);
	}
#ifndef NDEBUG
	after = realtime();
	assertf(before <= after || kernel_poisoned(),
	        "Backwards realtime: { { %I64d, %Iu }, { %I64d, %Iu } } (diff: { %I64d, %Iu })\n",
	        (s64)before.tv_sec, (uintptr_t)before.tv_nsec,
	        (s64)after.tv_sec, (uintptr_t)after.tv_nsec,
	        (s64)(before - after).tv_sec,
	        (uintptr_t)(before - after).tv_nsec);
#endif /* !NDEBUG */

	/* Check for a scheduling override */
	if unlikely((next = me->c_override) != NULL) {
		assert(thread == next);
		return next;
	}

	/* Check for sleeping threads that should be woken. */
	cpu_timeout_sleeping_threads(me, cpu_jtime, cpu_qelps);

	/* Round-robbin-style next-thread select */
	next = thread->t_sched.s_running.sr_runnxt;
	
	/* Account for time spent executing on behalf of `thread' */
	if (next != thread->t_sched.s_running.sr_runnxt) {
		quantum_diff_t cpu_qtime;
		quantum_diff_t cpu_qoffs;
		quantum_diff_t cpu_qsize;
		cpu_qoffs = FORCPU(me, thiscpu_quantum_offset);
		cpu_qsize = FORCPU(me, thiscpu_quantum_length);
		if unlikely(OVERFLOW_UADD(cpu_qelps, cpu_qoffs, &cpu_qtime)) {
			quantum_diff_t num_jiffies;
			num_jiffies = ((quantum_diff_t)-1) / cpu_qsize;
			cpu_jtime  += num_jiffies;
			cpu_qtime  -= num_jiffies * cpu_qsize;
		}
		if (cpu_qtime >= cpu_qsize) {
			cpu_jtime += cpu_qtime / cpu_qsize;
			cpu_qtime = (cpu_qtime % cpu_qsize);
		}
		cpu_account_activity(thread, next,
		                     cpu_jtime,
		                     cpu_qtime,
		                     cpu_qsize);
	}
#ifndef NDEBUG
	before = after;
	after = realtime();
	assertf(before <= after || kernel_poisoned(),
	        "Backwards realtime: { { %I64d, %Iu }, { %I64d, %Iu } } (diff: { %I64d, %Iu })\n",
	        (s64)before.tv_sec, (uintptr_t)before.tv_nsec,
	        (s64)after.tv_sec, (uintptr_t)after.tv_nsec,
	        (s64)(before - after).tv_sec,
	        (uintptr_t)(before - after).tv_nsec);
#endif /* !NDEBUG */
	return next;
}


#undef ASSERT_REALTIME_INCREMENTING
#if !defined(NDEBUG) && 1
#define ASSERT_REALTIME_INCREMENTING 1
#endif /* !NDEBUG */


#ifdef ASSERT_REALTIME_INCREMENTING
PRIVATE ATTR_PERCPU struct timespec last_realtime = { 0, 0 };
#endif /* ASSERT_REALTIME_INCREMENTING */

/* Returns the current real time derived from the current CPU time.
 * If no realtime hardware is available, this clock may stop when
 * the CPU is idle and will not indicate the actual current time.
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
PUBLIC NOBLOCK WUNUSED struct timespec NOTHROW(KCALL realtime)(void) {
	/* The basic function to calculate realtime() is:
	 *     realtime() == PERCPU(LAST_RESYNC_REALTIME) +
	 *                   QUANTUM_TIME_SINCE_LAST_RESYNC();
	 */
	struct timespec resync_real; /* CPU last resync realtime */
	jtime_t         resync_cpuj; /* CPU last resync jiffies */
	quantum_diff_t  resync_cpuq; /* CPU last resync quantum */
	jtime_t         cpu_jtime;   /* CPU jiffies */
	quantum_diff_t  cpu_qoffs;   /* CPU quantum offset */
	quantum_diff_t  cpu_qtime;   /* CPU quantum time */
	quantum_diff_t  cpu_qsize;   /* CPU time quantum size */
#ifdef ASSERT_REALTIME_INCREMENTING
	pflag_t was;
	struct cpu *me;
#endif /* ASSERT_REALTIME_INCREMENTING */
	/* Capture CPU time values. */
	{
#ifndef ASSERT_REALTIME_INCREMENTING
		struct cpu *me;
		pflag_t was;
#endif /* !ASSERT_REALTIME_INCREMENTING */
		me  = THIS_CPU;
		was = PREEMPTION_PUSHOFF();
		cpu_qtime = cpu_quantum_elapsed_nopr(me, &cpu_jtime);
		/* Check if the CPU clock was ever synced... */
#if 1
		if unlikely(FORCPU(me, thiscpu_last_resync.ct_rtc) == NULL) {
			/* Force an RTC re-sync. upon first access */
			REF struct realtime_clock_struct *rtc;
			rtc = realtime_clock.get_nopr();
			if likely(rtc != NULL) {
				/* Create snapshots of the RTC. */
				COMPILER_BARRIER();
				resync_real = (*rtc->rc_gettime)(rtc);
				COMPILER_BARRIER();
				decref_unlikely(rtc);
				cpu_resync_realtime(me,
				                    &resync_real,
				                    rtc,
				                    cpu_jtime,
				                    cpu_qtime,
				                    false);
				cpu_qtime = cpu_quantum_elapsed_nopr(me, &cpu_jtime);
			}
		}
#endif
		resync_real = FORCPU(me, thiscpu_last_resync.ct_real);
		resync_cpuj = FORCPU(me, thiscpu_last_resync.ct_cpuj);
		resync_cpuq = FORCPU(me, thiscpu_last_resync.ct_cpuq);
		cpu_qoffs   = FORCPU(me, thiscpu_quantum_offset);
		cpu_qsize   = FORCPU(me, thiscpu_quantum_length);
#ifndef ASSERT_REALTIME_INCREMENTING
		PREEMPTION_POP(was);
#endif /* !ASSERT_REALTIME_INCREMENTING */
	}

	/* Calculate the whole quantum offset:
	 *   - cpu_qoffs: Addend
	 *   - cpu_qtime: Real, current quantum time */
	if unlikely(OVERFLOW_UADD(cpu_qtime, cpu_qoffs, &cpu_qtime)) {
		quantum_diff_t num_jiffies;
		num_jiffies = ((quantum_diff_t)-1) / cpu_qsize;
		cpu_jtime  += num_jiffies;
		cpu_qtime  -= num_jiffies * cpu_qsize;
	}
	/* Right now, our cpu's quantum time is:
	 * >> cpu_jtime * cpu_qsize + cpu_qtime
	 * Which is expressed in `1 / (cpu_qsize * HZ)'-th seconds;
	 *
	 * With this in mind, subtract the timestamp of the last
	 * realtime resync from the current cpu-local quantum time.
	 * WARNING: Due to resync-offsets, this subtraction may produce a negative result! */
	cpu_jtime -= resync_cpuj;
	if (OVERFLOW_USUB(cpu_qtime, resync_cpuq, &cpu_qtime)) {
		quantum_diff_t num_jiffies;
		num_jiffies = ((quantum_diff_t)-1) / cpu_qsize;
		cpu_jtime  -= num_jiffies;
		cpu_qtime  += num_jiffies * cpu_qsize;
	}
	if unlikely(cpu_qtime >= cpu_qsize) {
		cpu_jtime += cpu_qtime / cpu_qsize;
		cpu_qtime = (cpu_qtime % cpu_qsize);
	}
	/* The current realtime is now described by:
	 * >> cpu_resync.ct_real + QUANTUM_TO_SECONDS(cpu_jtime * cpu_qsize + cpu_qtime);
	 * To calculate that timestamp, start by dealing with `cpu_jtime', which is known
	 * to be in units of 1/HZ seconds!
	 * Though still note that `cpu_jtime' may be negative! */
	if unlikely((signed_jtime_t)cpu_jtime < 0) {
		intptr_t nsecs_addend;
		cpu_jtime = (jtime_t)-(signed_jtime_t)cpu_jtime;
		resync_real.tv_sec -= cpu_jtime / HZ;
		nsecs_addend = (uintptr_t)(((u64)cpu_qtime * (__NSECS_PER_SEC / HZ)) / cpu_qsize);
		nsecs_addend -= ((intptr_t)cpu_jtime % HZ) * (__NSECS_PER_SEC / HZ);
		/* Also deal with the quantum offset. */
		if unlikely(nsecs_addend >= 0) {
			resync_real.add_nanoseconds((uintptr_t)nsecs_addend);
		} else {
			resync_real.sub_nanoseconds((uintptr_t)-nsecs_addend);
		}
	} else {
		u64 nsecs;
		resync_real.tv_sec += cpu_jtime / HZ;
		nsecs = resync_real.tv_nsec;
		/* Also deal with the quantum offsets. */
		nsecs += (cpu_jtime % HZ) * (__NSECS_PER_SEC / HZ);
		nsecs += ((u64)cpu_qtime * (__NSECS_PER_SEC / HZ)) / cpu_qsize;
		if (nsecs > __NSECS_PER_SEC) {
			resync_real.tv_sec += (time_t)(nsecs / __NSECS_PER_SEC);
			nsecs %= __NSECS_PER_SEC;
		}
		resync_real.tv_nsec = (syscall_ulong_t)nsecs;
	}
#ifdef ASSERT_REALTIME_INCREMENTING
	if (!kernel_poisoned() /* && me == &_bootcpu*/) {
		struct timespec before;
		before = FORCPU(me, last_realtime);
		assertf(before <= resync_real,
		        "Backwards realtime: { { %I64d, %Iu }, { %I64d, %Iu } } (diff: { %I64d, %Iu })\n",
		        (s64)before.tv_sec, (uintptr_t)before.tv_nsec,
		        (s64)resync_real.tv_sec, (uintptr_t)resync_real.tv_nsec,
		        (s64)(before - resync_real).tv_sec,
		        (uintptr_t)(before - resync_real).tv_nsec);
		FORCPU(me, last_realtime) = resync_real;
	}
	PREEMPTION_POP(was);
#endif /* ASSERT_REALTIME_INCREMENTING */
	return resync_real;
}

/* Add the given `elapsed' to the quantum counter of the calling CPU
 * While doing this, wake up all timeout-sleeping threads that have
 * a timeout greater than a qtime_t that uses `elapsed' as the number
 * of quantum units elapsed since the start of the current quantum.
 * NOTE: This function does _not_ call `cpu_quantum_elapsed_nopr()'
 *       in order to determine the current time, but uses `elapsed'
 *       instead! */
PRIVATE NOBLOCK NOPREEMPT NONNULL((1)) void
NOTHROW(FCALL cpu_add_quantum_offset)(struct cpu *__restrict me,
                                      quantum_diff_t elapsed,
                                      bool wakeup_threads /* TODO: Remove this argument */) {
	jtime_t /*  */ old_jtime;
	jtime_t /*  */ cpu_jtime;
	quantum_diff_t cpu_qoffs;
	quantum_diff_t cpu_qsize;
	assert(!PREEMPTION_ENABLED());
	old_jtime = FORCPU(me, thiscpu_jiffies);
	cpu_qoffs = FORCPU(me, thiscpu_quantum_offset);
	cpu_qsize = FORCPU(me, thiscpu_quantum_length);
	cpu_jtime = old_jtime;
	if unlikely(OVERFLOW_UADD(cpu_qoffs, elapsed, &cpu_qoffs)) {
		quantum_diff_t num_jiffies;
		num_jiffies = ((quantum_diff_t)-1) / cpu_qsize;
		cpu_jtime += num_jiffies;
		cpu_qoffs -= num_jiffies * cpu_qsize;
	}
	if (cpu_qoffs >= cpu_qsize) {
		cpu_jtime += cpu_qoffs / cpu_qsize;
		cpu_qoffs = (cpu_qoffs % cpu_qsize);
	}

	/* Save the new jtime/quantum offset values. */
	FORCPU(me, thiscpu_jiffies)        = cpu_jtime;
	FORCPU(me, thiscpu_quantum_offset) = cpu_qoffs;
	COMPILER_BARRIER();

	/* If the jiffies counter got incremented, check if a realtime
	 * re-sync was meant to take place during the time that passed.
	 * If so, perform that re-sync now. */
	if unlikely(cpu_jtime > old_jtime) {
		if ((cpu_jtime / CPU_RESYNC_DELAY_IN_TICKS) !=
		    (old_jtime / CPU_RESYNC_DELAY_IN_TICKS)) {
			cpu_resync_realtime_chk_at(me,
			                           cpu_jtime,
			                           0,
			                           false);
		}
	}

	/* Wake up all sleeping threads
	 * NOTE: For this purpose, use a quantum-elapsed value of 0,
	 *       since the actual time that has already elapsed according
	 *       to our caller was already added to the general quantum
	 *       offset of the CPU. */
	if (wakeup_threads)
		cpu_timeout_sleeping_threads(me, cpu_jtime, 0);
	COMPILER_BARRIER();
}

/* Check for quantum roll-over, and increment jiffies if a roll-over occurred. */
PRIVATE NOBLOCK NOPREEMPT NONNULL((1)) void
NOTHROW(FCALL cpu_check_quantum_rollover)(struct cpu *__restrict me,
                                          quantum_diff_t elapsed) {
	/* Deal with quantum roll-over */
	if (elapsed < FORCPU(me, thiscpu_last_qtime_q) &&
		FORCPU(me, thiscpu_jiffies) == FORCPU(me, thiscpu_last_qtime_j)) {
		jtime_t cpu_jtime;
		FORCPU(me, thiscpu_jiffi_pending) = true;
		cpu_jtime = ++FORCPU(me, thiscpu_jiffies);
		if ((cpu_jtime % CPU_RESYNC_DELAY_IN_TICKS) == 0) {
			/* Can't call `cpu_resync_realtime_chk_at()', because
			 * the current realtime is inconsistent until we've
			 * cleared the last-quantum cache fields below.
			 * Additionally, there's no need to use the chk-variant,
			 * since we do our own realtime-consistency assertion! */
			cpu_resync_realtime_at(me,
			                       cpu_jtime,
			                       elapsed,
			                       false);
		}
	}

}


/* Prematurely end the current quantum, accounting its elapsed
 * time to `prev', and starting a new quantum such that the
 * next scheduler interrupt will happen after a full quantum. */
FUNDEF NOBLOCK NOPREEMPT NONNULL((1, 2)) void
NOTHROW(FCALL cpu_quantum_end_nopr)(struct task *__restrict prev,
                                    struct task *__restrict next) {
	quantum_diff_t elapsed;
	struct cpu *me;
#ifndef NDEBUG
	struct timespec after;
	struct timespec before;
	before = realtime();
#endif /* !NDEBUG */
	me = prev->t_cpu;
	assert(prev != next);
	assert(me == THIS_CPU);
	assert(me == next->t_cpu);

	/* Atomically (or near atomically) figure out how much
	 * time has already elapsed, and reset the quantum. */
	elapsed = arch_cpu_quantum_elapsed_and_reset_nopr(me);

	/* Deal with quantum roll-over */
	cpu_check_quantum_rollover(me, elapsed);

	/* Reset the last-quantum cache to prevent an incorrect overrun
	 * from being detected when the quantum-elapsed counter was in
	 * fact only lowered because the quantum got reset manually. */
	FORCPU(me, thiscpu_last_qtime_q) = 0;
	FORCPU(me, thiscpu_last_qtime_j) = 0;

	/* Account for the time spend in the previous quantum.
	 * Must be done to ensure proper time-keeping, as well
	 * as prevent the realtime() clock from running backwards! */
	/* TODO: Allow this call to wake up threads, and change `cpu_quantum_end_nopr()'
	 *       to be the function to select the next thread to-be executed in case of
	 *       a yield-style preemption:
	 * >> ATTR_RETNONNULL NONNULL((1)) WUNUSED struct task *
	 * >> NOTHROW(FCALL cpu_quantum_end_nopr)(struct task *__restrict caller); */
	cpu_add_quantum_offset(me, elapsed, false);

	/* Account for time spent executing in `prev',
	 * and remember when execution began in `next' */
	cpu_account_activity(prev, next,
	                     FORCPU(me, thiscpu_jiffies),
	                     FORCPU(me, thiscpu_quantum_offset),
	                     FORCPU(me, thiscpu_quantum_length));

#ifndef NDEBUG
	after = realtime();
	assertf(before <= after || kernel_poisoned(),
	        "Backwards realtime: { { %I64d, %Iu }, { %I64d, %Iu } } (diff: { %I64d, %Iu })\n",
	        (s64)before.tv_sec, (uintptr_t)before.tv_nsec,
	        (s64)after.tv_sec, (uintptr_t)after.tv_nsec,
	        (s64)(before - after).tv_sec,
	        (uintptr_t)(before - after).tv_nsec);
#endif /* !NDEBUG */
}


/* Disable / re-enable preemptive interrupts on the calling CPU.
 * When `cpu_enable_preemptive_interrupts_nopr()' is called, any time that has
 * passed between then and a prior call to `cpu_disable_preemptive_interrupts_nopr()'
 * will be added to the cpu's local jiffies counter, while also configuring
 * the current quantum to be aligned with the amount of time that has passed.
 * NOTE: In case preemptive interrupts cannot be disabled,
 *       all of these these functions are no-ops.
 * NOTE: The `*_nopr' variants may only be called when preemption is disabled! */
PUBLIC NOPREEMPT NOBLOCK void
NOTHROW(KCALL cpu_disable_preemptive_interrupts_nopr)(void) {
	quantum_diff_t elapsed;
	struct cpu *me;
#ifndef NDEBUG
	struct timespec before;
	struct timespec after;
	before = realtime();
#endif /* !NDEBUG */
	assert(!PREEMPTION_ENABLED() || kernel_poisoned());
	me = THIS_CPU;

	/* Figure out how much of the current quantum has already elapsed. */
	elapsed = arch_cpu_quantum_elapsed_nopr(me);

	/* Disable preemptive interrupts. */
	arch_cpu_disable_preemptive_interrupts_nopr(me);

	/* Deal with quantum roll-over */
	cpu_check_quantum_rollover(me, elapsed);

	/* When preemptive interrupts are disabled, `arch_cpu_quantum_elapsed_nopr()'
	 * will always return 0. - Reset the last-quantum cache to prevent an incorrect
	 * quantum overrun from being detected as the result of the elapsed counter
	 * being (permanently, at least for the time being) reset to 0. */
	FORCPU(me, thiscpu_last_qtime_q) = 0;
	FORCPU(me, thiscpu_last_qtime_j) = 0;

#ifndef NDEBUG
	if (!kernel_poisoned()) {
		quantum_diff_t new_elapsed;
		new_elapsed = arch_cpu_quantum_elapsed_nopr(me);
		assertf(new_elapsed == 0,
		        "So-long as preemptive interrupts are disabled, this must be 0!\n"
		        "elapsed                                 = %I32u\n"
		        "new_elapsed                             = %I32u\n"
		        "arch_cpu_preemptive_interrupts_disabled = %d\n",
		        elapsed, new_elapsed,
		        (int)FORCPU(me, arch_cpu_preemptive_interrupts_disabled));
	}
#endif /* !NDEBUG */

	/* Account for the elapsed time. */
	cpu_add_quantum_offset(me, elapsed, true);

#ifndef NDEBUG
	after = realtime();
	assertf(before <= after || kernel_poisoned(),
	        "Backwards realtime: { { %I64d, %Iu }, { %I64d, %Iu } } (diff: { %I64d, %Iu })\n",
	        (s64)before.tv_sec, (uintptr_t)before.tv_nsec,
	        (s64)after.tv_sec, (uintptr_t)after.tv_nsec,
	        (s64)(before - after).tv_sec,
	        (uintptr_t)(before - after).tv_nsec);
#endif /* !NDEBUG */
}


PUBLIC NOPREEMPT NOBLOCK void
NOTHROW(KCALL cpu_enable_preemptive_interrupts_nopr)(void) {
	struct cpu *me;
#ifndef NDEBUG
	struct timespec before;
	struct timespec after;
	before = realtime();
#endif /* !NDEBUG */
	assert(!PREEMPTION_ENABLED() || kernel_poisoned());
	me = THIS_CPU;
	/* Mark the last RTC re-sync timestamp as invalid, since
	 * with preemptive interrupts being re-enabled, we have
	 * no idea how much realtime has passed since they've
	 * been disabled (and as such: we must force a re-sync
	 * the next time a call to `realtime()' is made) */
	FORCPU(me, thiscpu_last_resync.ct_rtc) = NULL;

	/* Actually re-enable preemptive interrupts. */
	arch_cpu_enable_preemptive_interrupts_nopr(me);
#ifndef NDEBUG
	after = realtime();
	assertf(before <= after || kernel_poisoned(),
	        "Backwards realtime: { { %I64d, %Iu }, { %I64d, %Iu } } (diff: { %I64d, %Iu })\n",
	        (s64)before.tv_sec, (uintptr_t)before.tv_nsec,
	        (s64)after.tv_sec, (uintptr_t)after.tv_nsec,
	        (s64)(before - after).tv_sec,
	        (uintptr_t)(before - after).tv_nsec);
#endif /* !NDEBUG */
}


/* Explicitly set the quantum length value for the calling CPU, and do an RTC
 * re-sync such that the given `cpu_qsize' appears to fit perfectly (at least
 * for the time being)
 * NOTE: This function does _NOT_ call `arch_cpu_update_quantum_length_nopr()'! */
PUBLIC NOBLOCK NOPREEMPT void
NOTHROW(KCALL cpu_set_quantum_length)(quantum_diff_t cpu_qsize) {
	struct cpu *me;
	REF struct realtime_clock_struct *rtc;
	assert(!PREEMPTION_ENABLED());
	me  = THIS_CPU;
	rtc = realtime_clock.get_nopr();
	if likely(rtc) {
		jtime_t /*  */ cpu_jtime;
		quantum_diff_t cpu_qtime;
		quantum_diff_t cpu_qoffs;
		struct timespec rtc_now;
		cpu_qoffs = FORCPU(me, thiscpu_quantum_offset);
		COMPILER_BARRIER();
		rtc_now   = (*rtc->rc_gettime)(rtc);
		cpu_qtime = cpu_quantum_elapsed_nopr(me, &cpu_jtime);
		COMPILER_BARRIER();
		decref_unlikely(rtc);
		if unlikely(OVERFLOW_UADD(cpu_qtime, cpu_qoffs, &cpu_qtime)) {
			quantum_diff_t num_jiffies;
			num_jiffies = ((quantum_diff_t)-1) / cpu_qsize;
			cpu_jtime  += num_jiffies;
			cpu_qtime  -= num_jiffies * cpu_qsize;
		}
		if (cpu_qtime >= cpu_qsize) {
			cpu_jtime += cpu_qtime / cpu_qsize;
			cpu_qtime = (cpu_qtime % cpu_qsize);
		}
		FORCPU(me, thiscpu_last_resync.ct_cpuj) = cpu_jtime;
		FORCPU(me, thiscpu_last_resync.ct_cpuq) = cpu_qtime;
		FORCPU(me, thiscpu_last_resync.ct_real) = rtc_now;
		FORCPU(me, thiscpu_last_resync.ct_rtc)  = rtc;
		COMPILER_BARRIER();
	}
	COMPILER_BARRIER();
	FORCPU(me, thiscpu_quantum_length) = cpu_qsize;
	FORCPU(me, thiscpu_last_qtime_j)   = 0;
	FORCPU(me, thiscpu_last_qtime_q)   = 0;
	FORCPU(me, thiscpu_jiffi_pending)  = false;
	COMPILER_BARRIER();
}




/* Returns the cpu-local quantum time. */
PUBLIC NOBLOCK WUNUSED qtime_t /* TODO: Remove this function */
NOTHROW(KCALL cpu_quantum_time)(void) {
	qtime_t result;
	struct cpu *me;
	pflag_t was;
	quantum_diff_t elapsed;
	was = PREEMPTION_PUSHOFF();
	me             = THIS_CPU;
	result.q_qtime = FORCPU(me, thiscpu_quantum_offset);
	result.q_qsize = FORCPU(me, thiscpu_quantum_length);
	elapsed        = cpu_quantum_elapsed_nopr(me, &result.q_jtime);
	PREEMPTION_POP(was);
	if (OVERFLOW_UADD(result.q_qtime, elapsed, &result.q_qtime)) {
		result.q_jtime += ((quantum_diff_t)-1) / result.q_qsize;
		result.q_qtime += elapsed;
		result.q_qtime -= (quantum_diff_t)-1;
	}
	if (result.q_qtime >= result.q_qsize) {
		result.q_jtime += result.q_qtime / result.q_qsize;
		result.q_qtime = result.q_qtime % result.q_qsize;
	}
	return result;
}




/* Enter a sleeping state and return once being woken (true),
 * or once the given `abs_timeout' (which must be global) expires (false)
 * WARNING: Even if the caller has disabled preemption prior to the call,
 *          it will be re-enabled once this function returns.
 * NOTE: This function is the bottom-most (and still task-level) API
 *       for conserving CPU cycles using preemption, in that this
 *       function is even used to implement `task_wait()'.
 *       The functions used to implement this one no longer work on tasks, but on CPUs!
 * NOTE: If the thread is transferred to a different CPU while sleeping, a
 *       sporadic wakeup will be triggered, causing `task_sleep()' to return
 *      `true'.
 * The proper way of using this function is as follows:
 * >> while (SHOULD_WAIT()) { // Test some condition for which to wait
 * >>     PREEMPTION_DISABLE();
 * >>     // Test again now that interrupts are disabled
 * >>     // This test is required to prevent a race condition
 * >>     // where the condition is signaled between it being
 * >>     // changed and interrupts being disabled.
 * >>     COMPILER_READ_BARRIER();
 * >>     if (!SHOULD_WAIT()) {
 * >>         PREEMPTION_ENABLE();
 * >>         break;
 * >>     }
 * >>     // Serve RPC functions (when TRUE is returned, preemption was re-enabled)
 * >>     if (task_serve()) continue;
 * >>     // Do the actual sleep.
 * >>     if (!task_sleep(TIMEOUT))
 * >>         return DID_TIME_OUT;
 * >> }
 * >> return WAS_SIGNALED;
 * The sleeping thread should then be woken as follows:
 * >> SET_SHOULD_WAIT(false);
 * >> task_wake(waiting_thread); */
PUBLIC bool NOTHROW(FCALL task_sleep)(struct timespec const *abs_timeout) {
	struct task *me = THIS_TASK;
	struct cpu *mycpu;
	if (abs_timeout) {
		/* Check if we should immediately time out. */
		if (!abs_timeout->tv_sec && !abs_timeout->tv_nsec)
			goto do_return_false;
		/* Check if the given timeout has already expired. */
		if (realtime() >= *abs_timeout) {
do_return_false:
			PREEMPTION_ENABLE();
			return false;
		}
		/* Save the timeout to-be used. */
		me->t_sched.s_asleep.ss_timeout = *abs_timeout;
	} else {
		me->t_sched.s_asleep.ss_timeout.tv_sec = INT64_MAX;
	}
	PREEMPTION_DISABLE();
	mycpu = me->t_cpu;
	cpu_assert_running(me);
	if unlikely(me == mycpu->c_override)
		goto wait_a_bit;

	/* The caller is the only thread hosted by this cpu. */
	if likely(me->t_sched.s_running.sr_runnxt == me) {
		struct task *idle;
		assert(me->t_sched.s_running.sr_runprv == me);

		/* Special case: blocking call made by the IDLE thread. */
		idle = &FORCPU(mycpu, thiscpu_idle);
		if unlikely(me == idle) {
wait_a_bit:
			/* Wait for the next interrupt. */
			PREEMPTION_ENABLE_WAIT();
			/* Indicate a sporadic wake-up. */
			return false;
		}
		/* End the current quantum prematurely. */
		cpu_quantum_end_nopr(me, idle);
		assert(me->t_sched.s_running.sr_runnxt == me);
		assert(me->t_sched.s_running.sr_runprv == me);
		/* Check if the IDLE thread had been sleeping. */
		if (idle->t_sched.s_asleep.ss_pself) {
			/* The IDLE thread had been sleeping (time it out) */
			ATOMIC_FETCHOR(idle->t_flags, TASK_FTIMEOUT);
			if ((*idle->t_sched.s_asleep.ss_pself = idle->t_sched.s_asleep.ss_tmonxt) != NULL)
				idle->t_sched.s_asleep.ss_tmonxt->t_sched.s_asleep.ss_pself = idle->t_sched.s_asleep.ss_pself;
		}
		/* Unschedule the caller, and instead schedule the IDLE thread. */
		idle->t_sched.s_running.sr_runprv = idle;
		idle->t_sched.s_running.sr_runnxt = idle;
		ATOMIC_FETCHOR(idle->t_flags, TASK_FRUNNING);
		mycpu->c_current = idle;
	} else {
		/* Schedule the next task. */
		struct task *prev = me->t_sched.s_running.sr_runprv;
		struct task *next = me->t_sched.s_running.sr_runnxt;
		assert(prev->t_sched.s_running.sr_runnxt == me);
		assert(next->t_sched.s_running.sr_runprv == me);
		assert(prev != me);
		assert(next != me);

		/* End the current quantum prematurely. */
		cpu_quantum_end_nopr(me, next);

		mycpu->c_current = next;
		next->t_sched.s_running.sr_runprv = prev;
		prev->t_sched.s_running.sr_runnxt = next;
	}
	assert(mycpu->c_current->t_sched.s_running.sr_runnxt->t_sched.s_running.sr_runprv == mycpu->c_current);
	assert(mycpu->c_current->t_sched.s_running.sr_runprv->t_sched.s_running.sr_runnxt == mycpu->c_current);
	me->t_sched.s_running.sr_runprv = NULL;
	me->t_sched.s_running.sr_runnxt = NULL;
	assert(me->t_flags & TASK_FRUNNING);
	ATOMIC_FETCHAND(me->t_flags, ~TASK_FRUNNING);

	/* Register the calling task as a sleeper within the CPU. */
	cpu_addsleepingtask_nopr(me);

	/* Continue execution in the next thread. */
	cpu_run_current_and_remember_nopr(me);

	/* HINT: If your debugger break here, it means that your
	 *       thread is probably waiting on some kind of signal. */
	cpu_assert_running(me);

	/* Check if we got timed out. */
	if (ATOMIC_FETCHAND(me->t_flags, ~TASK_FTIMEOUT) & TASK_FTIMEOUT)
		return false; /* Timeout... */

	return true;
}



/* Return the current quantum tick for the calling CPU
 * This quantum tick is the most precise unit of measurement available
 * within the KOS kernel, being at least as precise than `realtime()'.
 * Quantum ticks increase all the time so-long as preemptive interrupts
 * as enabled (i.e. the quantum tick doesn't change after a call to
 * `cpu_disable_preemptive_interrupts_nopr()')
 * Note that the actual point in time to which a quantum tick is the
 * result of the division of `return.qt_tick / return.qt_freq', as done
 * with infinite-precision floating point arithmetic.
 * Note that this function returns a value that is per-cpu, and as such
 * prone to inconsistencies when the calling thread is moved between
 * different CPUs. A similar, thread-consistent counter can be accessed
 * through `task_quantum_tick()', which returns a thread-local quantum
 * tick representing the # of time spent executing code in the context
 * of that thread. */
PUBLIC NOBLOCK WUNUSED ATTR_PURE struct qtick
NOTHROW(KCALL cpu_quantum_tick)(void) {
	struct qtick result;
	pflag_t was;
	was    = PREEMPTION_PUSHOFF();
	result = cpu_quantum_tick_nopr();
	PREEMPTION_POP(was);
	return result;
}

PUBLIC NOBLOCK NOPREEMPT WUNUSED ATTR_PURE struct qtick
NOTHROW(KCALL cpu_quantum_tick_nopr)(void) {
	struct qtick result;
	struct cpu *me;
	jtime_t /*  */ cpu_jtime;
	quantum_diff_t cpu_qtime;
	assert(!PREEMPTION_ENABLED());
	me = THIS_CPU;
	COMPILER_BARRIER();
	result.qt_freq = FORCPU(me, thiscpu_quantum_length);
	result.qt_tick = FORCPU(me, thiscpu_quantum_offset);
	cpu_qtime      = cpu_quantum_elapsed_nopr(me, &cpu_jtime);
	COMPILER_BARRIER();
	result.qt_tick += cpu_qtime;
	result.qt_tick += cpu_jtime * result.qt_freq;
	return result;
}


/* Amount of time spent executing code in the context of the calling thread. */
PRIVATE ATTR_PERTASK struct qtick this_quantum_spent = { 0, 1 };

/* Quantum time at the start of the calling thread's current quantum. */
PRIVATE ATTR_PERTASK struct qtick this_quantum_start = { 0, 1 };


/* Account for task activity by logging a switch from
 * `oldthread' to `newthread' taking place at the specified time. */
PRIVATE NOBLOCK NONNULL((1, 2)) void
NOTHROW(KCALL cpu_account_activity)(struct task *__restrict oldthread,
                                    struct task *__restrict newthread,
                                    jtime_t switch_jtime,
                                    quantum_diff_t switch_qtime,
                                    quantum_diff_t switch_qsize) {
	struct qtick now;
	struct qtick start;
	struct qtick passed;
	now.qt_tick = (u64)switch_jtime * switch_qsize + switch_qtime;
	now.qt_freq = switch_qsize;
	FORTASK(newthread, this_quantum_start) = now;
	start = FORTASK(oldthread, this_quantum_start);
	/* Figure out how much time was spent in `oldthread'. */
	passed = now - start;
	FORTASK(oldthread, this_quantum_spent) += passed;
}

/* Return the amount of time that has been spent executing code in the
 * context of the calling thread. */
PUBLIC NOBLOCK WUNUSED ATTR_PURE struct qtick
NOTHROW(KCALL task_quantum_tick)(void) {
	pflag_t was;
	struct task *mythread;
	struct qtick start, spent, now;
	mythread = THIS_TASK;
	was = PREEMPTION_PUSHOFF();
	COMPILER_BARRIER();
	now   = cpu_quantum_tick_nopr();
	start = FORTASK(mythread, this_quantum_spent);
	spent = FORTASK(mythread, this_quantum_start);
	COMPILER_BARRIER();
	PREEMPTION_POP(was);
	/* Simply return: SPENT + (NOW - START) */
	now -= start;
	spent += now;
	return spent;
}

/* Return the amount of time that has been spent executing code in the
 * context of the given thread. */
PUBLIC NOBLOCK WUNUSED ATTR_PURE struct qtick
NOTHROW(KCALL task_quantum_tick_of)(struct task const *__restrict thread) {
	struct qtick result;
	if (thread == THIS_TASK) {
		/* Special case: Calling thread */
		result = task_quantum_tick();
	} else {
		/* XXX: This read isn't atomic, but even disabling preemption
		 *      doesn't guaranty a consistent value when `thread' is
		 *      hosted by a different CPU...
		 * -> There needs to be some sort of per-cpu counter that is
		 *    incremented every time that `this_quantum_start' field
		 *    of a hosted thread was modified.
		 *    With such a field, we could:
		 *      1: Disable preemption
		 *      2: Check if `thread' is hosted by a different cpu:
		 *         no.1: Simply read the `this_quantum_start' field
		 *         no.2: Re-enable preemption
		 *        yes.1: Atomically read the quantum-start-version field
		 *        yes.2: Read the thread's `this_quantum_start' field
		 *        yes.3: Memory barrier
		 *        yes.4: Atomically re-read the quantum-start-version field
		 *               If changed:   Go to step #yes.1
		 *               If unchanged: Go to step #no.2
		 */
		result = FORTASK(thread, this_quantum_start);
	}
	return result;
}




/* Return the greatest value `x', such that:
 * >> (a % x) == 0 && (b % x) == 0
 * If no other value exists with this property, return `1' */
PRIVATE NOBLOCK ATTR_CONST u32
NOTHROW(KCALL greatest_common_divisor)(u32 a, u32 b) {
	u32 temp;
	for (;;) {
		if (!a)
			return b;
		temp = b % a;
		b    = a;
		a    = temp;
	}
} 



#ifndef __UINT128_TYPE__
/* https://stackoverflow.com/questions/5284898/implement-division-with-bit-wise-operator */
PRIVATE NOBLOCK ATTR_CONST uint128_t
NOTHROW(KCALL div128)(uint128_t a,
                      uint128_t b) {
	unsigned int n_pwr = 0;
	unsigned int i;
	uint128_t res, mask;
	mask = 0;
	for (i = 0; i < 128; ++i) {
		if (b & mask)
			n_pwr = i;
		mask <<= 1;
	}
	res = 0;
	i = 128 - n_pwr;
	b <<= i;
	mask = 1;
	mask <<= i;
	for (;;) {
		if (b <= a) {
			res += mask;
			a -= b;
		}
		if (!i)
			break;
		--i;
		b >>= 1;
		mask >>= 1;
	}
	/* HINT: `a' is the remainder! */
	return res;
}
#endif /* !__UINT128_TYPE__ */


/* Return the result of `((a * b) + c - 1) / c' */
PUBLIC NOBLOCK ATTR_CONST u64
NOTHROW(KCALL __umuldiv64)(u64 a, u32 b, u32 c) {
	/* XXX: This function really shouldn't go here!
	 *      Instead, maybe it should even go into
	 *      some (possibly dedicated) <hybrid/...> header? */
	u64 result;
again:
	if (!OVERFLOW_UMUL(a, b, &result)) {
		if (!OVERFLOW_UADD(result, c - 1, &result))
			return result / c;
		/* Very close to the  */
		result = (u64)-1 / c;
		if ((c % b) != 0)
			++result;
		return result;

	}
	{
		u32 gcd;
		gcd = greatest_common_divisor(b, c);
		if (gcd > 1) {
			/* Simplify: (b * 4) / 2 == (c * 2) / 1 */
			b /= gcd;
			c /= gcd;
			goto again;
		}
	}
	/* Well $h1t!
	 * Use (expensive) 128-bit arithmetic as a fallback... */
	{
		uint128_t mulres, temp;
		uint128_t result;
#ifdef __UINT128_TYPE__
		mulres = (uint128_t)a * b;
#else /* __UINT128_TYPE__ */
		{
			unsigned int i;
			temp = a;
			mulres = 0;
			for (i = 0; i < 32; ++i, temp <<= 1) {
				if (!(b & ((u32)1 << i)))
					continue;
				mulres += temp;
			}
		}
#endif /* !__UINT128_TYPE__ */

		/* At this point, `mulres == a * b' */
		temp = mulres;
		temp += c - 1;
		if (temp < mulres)
			uint128_setmax(temp); /* Overflow during the add */
		/* At this point, `temp == a * b + c - 1'
		 * Now we must divide `temp' by `c' */
#ifdef __UINT128_TYPE__
		result = temp / c;
#else /* __UINT128_TYPE__ */
		result = div128(temp, (uint128_t)c);
#endif /* !__UINT128_TYPE__ */
		/* If the 128-bit result fits into 64 bits, return it unaltered.
		 * Otherwise, clamp to the max possible value. */
		if (uint128_is64bit(result))
			return uint128_get64(result);
		/* Clamp */
		return UINT64_MAX;
	}
}


DECL_END

#endif /* !GUARD_KERNEL_SRC_SCHED_TIME_C */
