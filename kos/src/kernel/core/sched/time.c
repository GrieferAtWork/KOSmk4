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

#include <kos/jiffies.h>

#include <assert.h>

/*TODO:REMOVE_ME:BEGIN*/
#include <stdio.h>
#include <time.h>
/*TODO:REMOVE_ME:END*/

DECL_BEGIN

/*TODO:REMOVE_ME:BEGIN*/
INTDEF port_t x86_syslog_port;
/*TODO:REMOVE_ME:END*/

#ifndef ARCH_DEFAULT_REALTIME_CLOCK
#define ARCH_DEFAULT_REALTIME_CLOCK NULL
#endif /* !ARCH_DEFAULT_REALTIME_CLOCK */

/* [0..1] The used realtime system clock */
PUBLIC XATOMIC_REF(struct realtime_clock_struct)
realtime_clock = XATOMIC_REF_INIT(ARCH_DEFAULT_REALTIME_CLOCK);


/* Destroy the given realtime clock. */
PUBLIC NOBLOCK void
NOTHROW(KCALL realtime_clock_destroy)(struct realtime_clock_struct *__restrict self) {
	if (self->rc_fini)
		(*self->rc_fini)(self);
	decref(self->rc_driver);
	kfree(self);
}




#undef CONFIG_USE_NEW_REALTIME
#define CONFIG_USE_NEW_REALTIME 1


#ifdef CONFIG_USE_NEW_REALTIME

struct cpu_timestamp {
	struct timespec               ct_real; /* Realtime */
	jtime_t                       ct_cpuj; /* CPU time jiffies */
	quantum_diff_t                ct_cpuq; /* CPU time quantum */
	struct realtime_clock_struct *ct_rtc;  /* [weak][0..1] The RPC used for the re-sync. */
};

/* Timestamp for the last realtime re-sync made by the CPU */
PRIVATE ATTR_PERCPU struct cpu_timestamp thiscpu_last_resync = {
	/* .ct_real = */ {
		/* .tv_sec  = */ 0,
		/* .tv_nsec = */ 0
	},
	/* .ct_cpuj = */ 0,
	/* .ct_cpuq = */ 0
};

/* How many seconds to wait before performing another realtime re-sync */
#ifndef CPU_RESYNC_DELAY_IN_SECONDS
#define CPU_RESYNC_DELAY_IN_SECONDS 3
#endif /* !CPU_RESYNC_DELAY_IN_SECONDS */

typedef __CRT_PRIVATE_UINT(__SIZEOF_JTIME_T__) signed_jtime_t;



PRIVATE NOBLOCK NOPREEMPT void
NOTHROW(FCALL cpu_resync_realtime)(struct cpu *__restrict self) {
	/* Try to perform a realtime re-sync. */
	struct cpu_timestamp nts; /* NewTimeStamp */
	struct cpu_timestamp ots; /* OldTimeStamp */
	struct timespec cpu_realtime;
	quantum_diff_t cpu_qoffs; /* CPU quantum offset */
	quantum_diff_t cpu_qsize; /* CPU time quantum size */
	jtime_t /*  */ cpu_resyncrel_jtime; /* Relative CPU jiffies since last re-sync */
	quantum_diff_t cpu_resyncrel_qtime; /* Relative CPU quantum since last re-sync */
#ifndef NDEBUG
	struct timespec before;
	struct timespec after;
	before = realtime();
#endif /* !NDEBUG */
	assert(!PREEMPTION_ENABLED());

	nts.ct_rtc = realtime_clock.get_nopr();
	if unlikely(nts.ct_rtc == NULL)
		return;

	/* Create snapshots of the RTC and CPU clock counters. */
	COMPILER_BARRIER();
	nts.ct_real = (*nts.ct_rtc->rc_gettime)(nts.ct_rtc);
	nts.ct_cpuq = cpu_quantum_elapsed_nopr(self, &nts.ct_cpuj);
	COMPILER_BARRIER();

	/* Calculate the realtime for our current CPU, as it would be returned by
	 * `realtime()' for the values we received from `cpu_quantum_elapsed_nopr()'
	 * That timestamp is the compared against what the RTC has given us, so that
	 * was may determine the relative clock error. */
	COMPILER_BARRIER();
	ots       = FORCPU(self, thiscpu_last_resync);
	cpu_qoffs = FORCPU(self, thiscpu_quantum_offset);
	cpu_qsize = FORCPU(self, thiscpu_quantum_length);
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
	if unlikely(nts.ct_rtc != ots.ct_rtc) {
		/* Real-time clock changed (or was installed)
		 * If it got freshly installed, then we may lazily start using it.
		 * If it got changed, then whoever changed it must manually update
		 * CPU clocks, and we must no longer re-sync periodically until
		 * they do! */
		if (ots.ct_rtc != NULL)
			goto done_decref_rtc;
		/* Lazily start using the new RTC by setting the new RTC */
		COMPILER_BARRIER();
		FORCPU(self, thiscpu_last_resync) = nts;
		COMPILER_BARRIER();
		goto done_decref_rtc;
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
			perfect_cpu_qsize = (quantum_diff_t)((quantum_cpu_elapsed *
			                                      cpu_qsize) /
			                                     quantum_rtc_elapsed);
			assertf(perfect_cpu_qsize <= cpu_qsize,
			        "The formula must be wrong. We were running too slow, so "
			        "our perfect quantum length should be lower than our current!");
			/* With the perfect quantum length calculated, don't go all in about
			 * using it, but rather use the average between the old quantum length,
			 * and the new one! (once again: round downwards) */
			new_cpu_qsize = (perfect_cpu_qsize + cpu_qsize) / 2;
			assert(new_cpu_qsize <= cpu_qsize);
			if (new_cpu_qsize < cpu_qsize) {
				printk(KERN_INFO "[cpu#%u][-] Adjust quantum length %I32u -> %I32u (CPU clock was running too slow)\n",
				       self->c_id, cpu_qsize, new_cpu_qsize);
				/* Make the clock jump into the future to catch up with realtime */
				nts.ct_cpuj = FORCPU(self, thiscpu_jiffies);
				nts.ct_cpuq = 0;
				COMPILER_BARRIER();
				FORCPU(self, thiscpu_last_resync)    = nts;
				FORCPU(self, thiscpu_quantum_length) = new_cpu_qsize;
				COMPILER_BARRIER();
				arch_cpu_update_quantum_length_nopr();
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
			if likely(quantum_rtc_elapsed < quantum_cpu_elapsed) {
				quantum_diff_t perfect_cpu_qsize;
				quantum_diff_t new_cpu_qsize;
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
				perfect_cpu_qsize = (quantum_diff_t)(((quantum_cpu_elapsed *
				                                       cpu_qsize) +
				                                      (quantum_rtc_elapsed - 1)) /
				                                     quantum_rtc_elapsed);
				assertf(perfect_cpu_qsize >= cpu_qsize,
				        "The formula must be wrong. We were running too fast, so "
				        "our perfect quantum length should be greater than our current!");
				new_cpu_qsize = (perfect_cpu_qsize + cpu_qsize) / 2;
				assert(new_cpu_qsize >= cpu_qsize);
				if (new_cpu_qsize > cpu_qsize) {
					struct timespec cputime_since_nts;
					u64 quantum_since_nts;
					printk(KERN_INFO "[cpu#%u][+] Adjust quantum length %I32u -> %I32u (CPU clock was running too fast)\n",
					       self->c_id, cpu_qsize, new_cpu_qsize);
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
					 *                    (PERCPU(thiscpu_jiffies) - nts.ct_cpu(j|q))
					 *                            ^
					 *                            No quantum offset, because `thiscpu_quantum_offset' is set to 0
					 * Re-arranging this (so we end up with `nts.ct_cpu(j|q)' on one side):
					 *    nts.ct_cpu(j|q) == (nts.ct_real - cpu_realtime) + PERCPU(thiscpu_jiffies)
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
					nts.ct_cpuj = FORCPU(self, thiscpu_jiffies);
					nts.ct_cpuj -= quantum_since_nts / new_cpu_qsize;
					nts.ct_cpuq = (quantum_since_nts % new_cpu_qsize);
					if (nts.ct_cpuq) {
						--nts.ct_cpuj;
						nts.ct_cpuq = new_cpu_qsize - nts.ct_cpuq;
					}
					COMPILER_BARRIER();
					FORCPU(self, thiscpu_last_resync)    = nts;
					FORCPU(self, thiscpu_quantum_length) = new_cpu_qsize;
					COMPILER_BARRIER();
					arch_cpu_update_quantum_length_nopr();
					COMPILER_BARRIER();
				}
			}
		}
	}
done_decref_rtc:
	decref_unlikely(nts.ct_rtc);
#ifndef NDEBUG
	if (!kernel_poisoned()) {
		after = realtime();
		assertf(before <= after,
		        "Backwards realtime: { { %I64d, %Iu }, { %I64d, %Iu } } (diff: { %I64d, %Iu })\n",
		        (s64)before.tv_sec, (uintptr_t)before.tv_nsec,
		        (s64)after.tv_sec, (uintptr_t)after.tv_nsec,
		        (s64)(before - after).tv_sec,
		        (uintptr_t)(before - after).tv_nsec);
	}
#endif /* !NDEBUG */
}


/* prevent issues hardware timer roll-over happening
 * before we've able to read the timestamp counter. */
PRIVATE ATTR_PERCPU jtime_t        thiscpu_last_qtime_j = 0;
PRIVATE ATTR_PERCPU quantum_diff_t thiscpu_last_qtime_q = 0;
PRIVATE ATTR_PERCPU bool thiscpu_jiffi_pending = false;


INTERN NOBLOCK NOPREEMPT void
NOTHROW(FCALL cpu_inc_jiffies)(struct cpu *__restrict self) {
	jtime_t newtime;
	/* Check if this interrupt was already noticed as being pending */
	if (FORCPU(self, thiscpu_jiffi_pending)) {
		FORCPU(self, thiscpu_jiffi_pending) = false;
	} else {
		++FORCPU(self, thiscpu_jiffies);
	}
	newtime = FORCPU(self, thiscpu_jiffies);
	if ((newtime % JIFFIES_FROM_SECONDS(CPU_RESYNC_DELAY_IN_SECONDS)) == 0)
		cpu_resync_realtime(self);
}

/* Returns the number of ticks that have passed since the start
 * of the current quantum. - The true current CPU-local time
 * (in ticks) can then be calculated as:
 * >> (thiscpu_jiffies * PERCPU(thiscpu_quantum_length)) + PERCPU(thiscpu_quantum_offset) + cpu_quantum_elapsed_nopr();
 * NOTE: The `*_nopr' variants may only be called when preemption is disabled! */
PUBLIC NOBLOCK NOPREEMPT WUNUSED NONNULL((1, 2)) quantum_diff_t
NOTHROW(FCALL cpu_quantum_elapsed_nopr)(struct cpu *__restrict mycpu,
                                        jtime_t *__restrict preal_jtime) {
	quantum_diff_t qtime;
	jtime_t jtime;
	qtime = arch_cpu_quantum_elapsed_nopr();
	jtime = FORCPU(mycpu, thiscpu_jiffies);
	if (qtime < FORCPU(mycpu, thiscpu_last_qtime_q) &&
		jtime == FORCPU(mycpu, thiscpu_last_qtime_j)) {
		/* Roll-over prior to actual interrupt / roll-over with lost interrupt.
		 * In either case, increment the jiffies counter now, and set the flag
		 * to indicate that the next scheduler interrupt shouldn't increment
		 * the counter (since we already did so for it) */
		FORCPU(mycpu, thiscpu_jiffi_pending) = true;
		++FORCPU(mycpu, thiscpu_jiffies);
		++jtime;
	}
	FORCPU(mycpu, thiscpu_last_qtime_q) = qtime;
	FORCPU(mycpu, thiscpu_last_qtime_j) = jtime;
	*preal_jtime = jtime;
	return qtime;
}


#undef ASSERT_REALTIME_INCREMENTING
#if !defined(NDEBUG) && 1
#define ASSERT_REALTIME_INCREMENTING 1
#endif /* !NDEBUG */

#undef LOG_REALTIME_TIMESTAMPS
#if !defined(NDEBUG) && 0
#define LOG_REALTIME_TIMESTAMPS 1
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
#ifdef LOG_REALTIME_TIMESTAMPS
		jtime_t last_jtime;
		jtime_t last_qtime_j;
		quantum_diff_t last_qtime_q;
#endif /* LOG_REALTIME_TIMESTAMPS */
		me  = THIS_CPU;
		was = PREEMPTION_PUSHOFF();
#ifdef LOG_REALTIME_TIMESTAMPS
		last_jtime    = FORCPU(me, thiscpu_jiffies);
		last_qtime_j  = FORCPU(me, thiscpu_last_qtime_j);
		last_qtime_q  = FORCPU(me, thiscpu_last_qtime_q);
#endif /* LOG_REALTIME_TIMESTAMPS */
		resync_real = FORCPU(me, thiscpu_last_resync.ct_real);
		resync_cpuj = FORCPU(me, thiscpu_last_resync.ct_cpuj);
		resync_cpuq = FORCPU(me, thiscpu_last_resync.ct_cpuq);
		cpu_qoffs   = FORCPU(me, thiscpu_quantum_offset);
		cpu_qsize   = FORCPU(me, thiscpu_quantum_length);
		cpu_qtime   = cpu_quantum_elapsed_nopr(me, &cpu_jtime);
#ifdef LOG_REALTIME_TIMESTAMPS
		if (me == &_bootcpu) {
			char buf[128];
			size_t len;
			len = sprintf(buf, "[c:%I64u,t:{%I64u,%7I32u+%I32u},l:{%I64u,%7I32u},r:{%I64u,%I32u},s:%I32u]\n",
			              last_jtime, cpu_jtime, cpu_qtime, cpu_qoffs,
			              last_qtime_j, last_qtime_q,
			              resync_cpuj, resync_cpuq, cpu_qsize);
			__outsb((u16)x86_syslog_port, buf, len);
		}
#endif /* LOG_REALTIME_TIMESTAMPS */
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
	if (!kernel_poisoned()/* && me == &_bootcpu*/) {
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

#else /* CONFIG_USE_NEW_REALTIME */

struct cpu_timestamp {
	struct timespec ct_real; /* Realtime */
	jtime_t         ct_cpuj; /* CPU time jiffies */
	quantum_diff_t  ct_cpuq; /* CPU time quantum */
};

/* Timestamp for the last realtime re-sync made by the CPU */
PRIVATE ATTR_PERCPU struct cpu_timestamp thiscpu_last_resync = {
	/* .ct_real = */ {
		/* .tv_sec  = */ 0,
		/* .tv_nsec = */ (syscall_ulong_t)-1
	}
};


PRIVATE NOBLOCK NOPREEMPT void
NOTHROW(FCALL cpu_resync_realtime)(struct cpu *__restrict self) {
#if 0
	(void)self;
#else
	REF struct realtime_clock_struct *rt;
	struct cpu_timestamp *cts;
	struct cpu_timestamp nts;
	struct timespec precision;
	quantum_diff_t elapsed, cpu_qsize;
#ifndef NDEBUG
	struct timespec before;
#endif /* !NDEBUG */
	assert(!PREEMPTION_ENABLED());
	rt = realtime_clock.get_nopr();
	if (!rt)
		return;
#ifndef NDEBUG
	/* For the assertion below, `before' must be a timestamp that
	 * happens prior to our call to `cpu_quantum_elapsed_nopr()'! */
	if (FORCPU(self, thiscpu_last_resync.ct_real.tv_nsec) != (syscall_ulong_t)-1) {
		before = realtime();
	} else {
		before.tv_sec  = 0;
		before.tv_nsec = 0;
	}
	COMPILER_BARRIER();
#endif /* !NDEBUG */
	cts = &FORCPU(self, thiscpu_last_resync);
	COMPILER_BARRIER();
	nts.ct_real = (*rt->rc_gettime)(rt);
	elapsed     = cpu_quantum_elapsed_nopr(self, &nts.ct_cpuj);
	COMPILER_BARRIER();
	precision = rt->rc_precision;
	decref_unlikely(rt);
	cpu_qsize   = FORCPU(self, thiscpu_quantum_length);
	nts.ct_cpuq = FORCPU(self, thiscpu_quantum_offset);
	if (OVERFLOW_UADD(nts.ct_cpuq, elapsed, &nts.ct_cpuq)) {
		quantum_diff_t num_jiffies;
		num_jiffies = ((quantum_diff_t)-1) / cpu_qsize;
		nts.ct_cpuj += num_jiffies;
		nts.ct_cpuq -= num_jiffies * cpu_qsize;
	}
	if unlikely(nts.ct_cpuq >= cpu_qsize) {
		nts.ct_cpuj += nts.ct_cpuq / cpu_qsize;
		nts.ct_cpuq = nts.ct_cpuq % cpu_qsize;
	}
	if (cts->ct_real.tv_nsec == (syscall_ulong_t)-1) {
		/* First time. */
		*cts = nts;
	} else {
		/* Check for drift.
		 * If the drift is larger than the realtime clock's precision,
		 * then we need to adjust `thiscpu_quantum_length' */
		jtime_t cputime_diff_j;
		quantum_diff_t cputime_diff_q;
		struct timespec cpu_elapsed, elapsed_error;
		struct timespec rt_elapsed;
		bool cpu_clock_too_fast;
		if unlikely(cts->ct_real > nts.ct_real)
			return; /* Shouldn't happen (the hardware clock moved backwards?) */
		cputime_diff_j = nts.ct_cpuj - cts->ct_cpuj;
		if (nts.ct_cpuq < cts->ct_cpuq) {
			assert(cputime_diff_j);
			--cputime_diff_j;
			cputime_diff_q = nts.ct_cpuq + (cpu_qsize - cts->ct_cpuq);
		} else {
			cputime_diff_q = nts.ct_cpuq - cts->ct_cpuq;
		}
		cpu_elapsed.tv_sec  = cputime_diff_j / HZ;
		cpu_elapsed.tv_nsec = ((cputime_diff_j % HZ) * (__NSECS_PER_SEC / HZ)) +
		                      (syscall_ulong_t)((u64)((u64)cputime_diff_q *
		                                              (__NSECS_PER_SEC / HZ)) /
		                                        cpu_qsize);
		rt_elapsed = nts.ct_real - cts->ct_real;
		if (cpu_elapsed > rt_elapsed) {
			elapsed_error      = cpu_elapsed - rt_elapsed;
			cpu_clock_too_fast = true;
		} else {
			elapsed_error      = rt_elapsed - cpu_elapsed;
			cpu_clock_too_fast = false;
		}
		if (elapsed_error > precision) {
			u64 elapsed_error_nano, cpu_elapsed_nano;
			quantum_diff_t adjust, new_quantum_length;
			elapsed_error -= precision;
			/* Adjust the quantum length to fix a precision error:
			 *    Over the last `cpu_elapsed' seconds, our CPU has accumulated
			 *    an error of approximately `elapsed_error' seconds.
			 * This we will fix by adjusting the quantum length:
			 *    thiscpu_quantum_length = cpu_clock_too_fast
			 *        ? thiscpu_quantum_length + (TONANO(elapsed_error) / TONANO(cpu_elapsed))
			 *        : thiscpu_quantum_length - (TONANO(elapsed_error) / TONANO(cpu_elapsed));
			 */
			elapsed_error_nano = ((u64)elapsed_error.tv_sec * __NSECS_PER_SEC) + elapsed_error.tv_nsec;
			cpu_elapsed_nano   = ((u64)cpu_elapsed.tv_sec * __NSECS_PER_SEC) + cpu_elapsed.tv_nsec;
			if unlikely(!cpu_elapsed_nano)
				return;
			adjust = (quantum_diff_t)(((u64)elapsed_error_nano *
			                           (cpu_qsize / JIFFIES_FROM_SECONDS(3))) /
			                          cpu_elapsed_nano);
			if (adjust != 0) {
				u64 cpu_elapsed_quantum;
				u64 rtc_elapsed_quantum;
				if (cpu_clock_too_fast) {
					new_quantum_length = cpu_qsize + adjust;
					/* When reducing the quantum length, we must decrease the
					 * timestamp of the last re-sync in order to prevent the realtime()
					 * clock for ever decreasing (i.e. because our previous value for realtime()
					 * was too high, we must decrease `QUANTUM_TIME_SINCE_LAST_RESYNC()' in
					 * order to fake a slower running realtime clock that can slowly catch
					 * up without ever stopping to run forward at any point):
					 * >> realtime() ==
					 * >>    LAST_RESYNC_REALTIME +
					 * >>    QUANTUM_TIME_SINCE_LAST_RESYNC()
					 * The about of time we have to subtract is equal to:
					 *      >> (PREV_LAST_RESYNC_REALTIME - RTC_CURRENT) +
					 *      >>  QUANTUM_TIME_FROM_PREV_LAST_RESYNC_TO_CURRENT_RESYNC;
					 *
					 * <==> >> QUANTUM_TIME_FROM_PREV_LAST_RESYNC_TO_CURRENT_RESYNC -
					 *      >>  (RTC_CURRENT - PREV_LAST_RESYNC_REALTIME);
					 *
					 * <==> >> cpu_elapsed - rt_elapsed;
					 */
					cpu_elapsed_quantum = (u64)cputime_diff_j * cpu_qsize + cputime_diff_q;
					rtc_elapsed_quantum = (((u64)rt_elapsed.tv_sec * HZ) * cpu_qsize) +
					                      (((u64)rt_elapsed.tv_nsec * cpu_qsize) / (1000000000 / HZ));
					assertf(cpu_elapsed_quantum >= rtc_elapsed_quantum,
					        "If this wasn't the case, then `cpu_clock_too_fast' "
					        "should have been false!");
					cpu_elapsed_quantum -= rtc_elapsed_quantum;
					/* Convert the offset. (NOTE: Use ceil-divide here to prevent a small rounding
					 *                            error from resulting in the clock moving backwards) */
					cpu_elapsed_quantum = ((cpu_elapsed_quantum * cpu_qsize) + (new_quantum_length - 1)) /
					                      new_quantum_length;
					/* Subtract the offset. */
#if 1
					{
						u64 diff_jif = ((u64)cpu_elapsed_quantum * 100000000) / new_quantum_length;
						printk(KERN_DEBUG "Subtract ticks: %I64u.%.8I64u\n",
						       (u64)(diff_jif / 100000000),
						       (u64)(diff_jif % 100000000));
					}
#endif
					nts.ct_cpuj -= cpu_elapsed_quantum / new_quantum_length;
					if (OVERFLOW_USUB(nts.ct_cpuq, cpu_elapsed_quantum % new_quantum_length, &nts.ct_cpuq)) {
						--nts.ct_cpuj;
						nts.ct_cpuq += new_quantum_length;
					}
				} else {
					new_quantum_length = cpu_qsize - adjust;
					/* When reducing the quantum length, the worst that can happen is the
					 * system clock jumping forward, which it's allowed to do irregardless! */
				}
				printk(KERN_INFO "[cpu#%u] Adjust quantum length %I32u%c%I32u -> %I32u\n",
				       self->c_id, cpu_qsize, cpu_clock_too_fast ? '+' : '-',
				       adjust, new_quantum_length);
				/* Apply the new quantum configuration */
				COMPILER_BARRIER();
				FORCPU(self, thiscpu_quantum_offset) = 0;
				FORCPU(self, thiscpu_quantum_length) = new_quantum_length;
				arch_cpu_update_quantum_length_nopr();
				*cts = nts;
				COMPILER_BARRIER();
#ifndef NDEBUG
				{
					struct timespec after;
					after = realtime();
					if (after < before) {
						printk(KERN_ERR "Backwards realtime: { { %I64d, %Iu }, { %I64d, %Iu } } (diff: { %I64d, %Iu })\n",
						       (s64)before.tv_sec, (uintptr_t)before.tv_nsec,
						       (s64)after.tv_sec, (uintptr_t)after.tv_nsec,
						       (s64)(before - after).tv_sec,
						       (uintptr_t)(before - after).tv_nsec);
					}
				}
#endif /* !NDEBUG */
			}
		}
	}
#endif
}

INTERN NOBLOCK NOPREEMPT void
NOTHROW(FCALL cpu_inc_jiffies)(struct cpu *__restrict self) {
	jtime_t newtime;
	newtime = ++FORCPU(self, thiscpu_jiffies);
	/* Try to re-sync CPU time with RTC time around every 3 seconds. */
	if ((newtime % JIFFIES_FROM_SECONDS(3)) == 0)
		cpu_resync_realtime(self);
}


/* Returns the current real time derived from the current CPU time.
 * If no realtime hardware is available, this clock may stop when
 * the CPU is idle and will not indicate the actual current time. */
PUBLIC NOBLOCK WUNUSED struct timespec NOTHROW(KCALL realtime)(void) {
	/* realtime() ==
	 *    PERCPU(LAST_RESYNC_REALTIME) +
	 *    QUANTUM_TIME_SINCE_LAST_RESYNC()
	 */

	struct timespec result;
	jtime_t         resync_cpuj; /* Resync CPU time jiffies */
	quantum_diff_t  resync_cpuq; /* Resync CPU time quantum */
	jtime_t         cpu_jtime;   /* CPU jiffies */
	quantum_diff_t  cpu_qoffs;   /* CPU quantum offset */
	quantum_diff_t  cpu_qtime;   /* CPU quantum time */
	quantum_diff_t  cpu_qsize;   /* CPU time quantum size */
	struct cpu *me;
	pflag_t was;
	u64 total_nsec;
	was = PREEMPTION_PUSHOFF();
	me  = THIS_CPU;
	/* Make sure that a timestamp was loaded at some point. */
	if (FORCPU(me, thiscpu_last_resync.ct_real.tv_nsec) == (syscall_ulong_t)-1)
		cpu_resync_realtime(me);
	result      = FORCPU(me, thiscpu_last_resync.ct_real);
	resync_cpuj = FORCPU(me, thiscpu_last_resync.ct_cpuj);
	resync_cpuq = FORCPU(me, thiscpu_last_resync.ct_cpuq);
	cpu_qoffs   = FORCPU(me, thiscpu_quantum_offset);
	cpu_qsize   = FORCPU(me, thiscpu_quantum_length);
	cpu_qtime   = cpu_quantum_elapsed_nopr(me, &cpu_jtime);
	PREEMPTION_POP(was);
	/* Calculate the elapsed CPU time since the last RTC resync */
	cpu_jtime -= resync_cpuj;
	if (OVERFLOW_UADD(cpu_qtime, cpu_qoffs, &cpu_qtime)) {
		quantum_diff_t num_jiffies;
		num_jiffies = ((quantum_diff_t)-1) / cpu_qsize;
		cpu_jtime += num_jiffies;
		cpu_qtime -= num_jiffies * cpu_qsize;
	}
	if (OVERFLOW_USUB(cpu_qtime, resync_cpuq, &cpu_qtime)) {
		quantum_diff_t num_jiffies;
		num_jiffies = ((quantum_diff_t)-1) / cpu_qsize;
		cpu_jtime -= num_jiffies;
		cpu_qtime += num_jiffies * cpu_qsize;
	}
	if (cpu_qtime >= cpu_qsize) {
		cpu_jtime += cpu_qtime / cpu_qsize;
		cpu_qtime = cpu_qtime % cpu_qsize;
	}
	/* We're now `(cpu_jtime + (cpu_qtime / cpu_qsize)) * HZ' seconds after `result'
	 * Adjust `result' accordingly to be a timestamp that's as precise as possible. */
	result.tv_sec += cpu_jtime / HZ;
	total_nsec = result.tv_nsec;
	total_nsec += (cpu_jtime % HZ) * (__NSECS_PER_SEC / HZ);
	total_nsec += (u64)((u64)cpu_qtime * (__NSECS_PER_SEC / HZ)) / cpu_qsize;
	result.tv_nsec = (syscall_ulong_t)total_nsec;
	if (total_nsec > __NSECS_PER_SEC) {
		result.tv_sec += (time_t)(total_nsec / __NSECS_PER_SEC);
		result.tv_nsec = (syscall_ulong_t)(total_nsec % __NSECS_PER_SEC);
	}
	if (result.tv_sec >= INT64_C(0x0ccccccc00000000))
		BREAKPOINT();
	return result;
}

/* prevent issues hardware timer roll-over happening
 * before we've able to read the timestamp counter. */
PRIVATE ATTR_PERCPU jtime_t thiscpu_last_qtime_j = 0;
PRIVATE ATTR_PERCPU quantum_diff_t thiscpu_last_qtime_q = 0;

/* Returns the number of ticks that have passed since the start
 * of the current quantum. - The true current CPU-local time
 * (in ticks) can then be calculated as:
 * >> (thiscpu_jiffies * PERCPU(thiscpu_quantum_length)) + PERCPU(thiscpu_quantum_offset) + cpu_quantum_elapsed_nopr();
 * NOTE: The `*_nopr' variants may only be called when preemption is disabled! */
PUBLIC NOBLOCK NOPREEMPT WUNUSED NONNULL((1, 2)) quantum_diff_t
NOTHROW(FCALL cpu_quantum_elapsed_nopr)(struct cpu *__restrict mycpu,
                                        jtime_t *__restrict preal_jtime) {
	quantum_diff_t result;
	result = arch_cpu_quantum_elapsed_nopr();
	*preal_jtime = FORCPU(mycpu, thiscpu_jiffies);
	if (result < FORCPU(mycpu, thiscpu_last_qtime_q) &&
	    *preal_jtime <= FORCPU(mycpu, thiscpu_last_qtime_j)) {
		FORCPU(mycpu, thiscpu_last_qtime_q) = (quantum_diff_t)-1;
		++*preal_jtime;
	} else {
		FORCPU(mycpu, thiscpu_last_qtime_j) = *preal_jtime;
		FORCPU(mycpu, thiscpu_last_qtime_q) = result;
	}
	return result;
}

#endif /* !CONFIG_USE_NEW_REALTIME */


/* Adjust quantum time to track the calling thread's quantum about to end prematurely. */
PUBLIC NOBLOCK NOPREEMPT void
NOTHROW(KCALL cpu_quantum_end_nopr)(void) {
#ifdef CONFIG_USE_NEW_REALTIME
#else /* CONFIG_USE_NEW_REALTIME */
	quantum_diff_t elapsed, length;
	struct cpu *mycpu = THIS_CPU;
	assert(!PREEMPTION_ENABLED());
	elapsed = arch_cpu_quantum_elapsed_nopr();
	if (elapsed < FORCPU(mycpu, thiscpu_last_qtime_q) &&
	    FORCPU(mycpu, thiscpu_jiffies) <= FORCPU(mycpu, thiscpu_last_qtime_j)) {
		FORCPU(mycpu, thiscpu_last_qtime_q) = (quantum_diff_t)-1;
		elapsed += FORCPU(mycpu, thiscpu_quantum_length);
	} else {
		FORCPU(mycpu, thiscpu_last_qtime_j) = FORCPU(mycpu, thiscpu_jiffies);
		FORCPU(mycpu, thiscpu_last_qtime_q) = elapsed;
	}
	arch_cpu_quantum_reset_nopr();
	length = cpu_add_quantum_offset_nopr(elapsed);
	THIS_TASK->t_atime.add_quantum(elapsed, length);
#endif /* !CONFIG_USE_NEW_REALTIME */
}




/* Disable / re-enable preemptive interrupts on the calling CPU.
 * When `cpu_enable_preemptive_interrupts_nopr()' is called, any time that has
 * passed between then and a prior call to `cpu_disable_preemptive_interrupts_nopr()'
 * will be added to the cpu's local jiffies counter, while also configuring
 * the current quantum to be aligned with the amount of time that has passed.
 * NOTE: In case preemptive interrupts cannot be disabled,
 *       all of these these functions are no-ops.
 * NOTE: The `*_nopr' variants may only be called when preemption is disabled! */
PUBLIC NOBLOCK void
NOTHROW(KCALL cpu_disable_preemptive_interrupts_nopr)(void) {
#ifdef CONFIG_USE_NEW_REALTIME
	assert(!PREEMPTION_ENABLED());
	/* XXX: Accounting? */
	arch_cpu_disable_preemptive_interrupts_nopr();
#else /* CONFIG_USE_NEW_REALTIME */
	quantum_diff_t elapsed, length;
	struct cpu *mycpu = THIS_CPU;
	assert(!PREEMPTION_ENABLED());
	elapsed = arch_cpu_quantum_elapsed_nopr();
	arch_cpu_disable_preemptive_interrupts_nopr();
	if (elapsed < FORCPU(mycpu, thiscpu_last_qtime_q) &&
	    FORCPU(mycpu, thiscpu_jiffies) <= FORCPU(mycpu, thiscpu_last_qtime_j)) {
		FORCPU(mycpu, thiscpu_last_qtime_q) = (quantum_diff_t)-1;
		elapsed += FORCPU(mycpu, thiscpu_quantum_length);
	} else {
		FORCPU(mycpu, thiscpu_last_qtime_j) = FORCPU(mycpu, thiscpu_jiffies);
		FORCPU(mycpu, thiscpu_last_qtime_q) = elapsed;
	}
	length = cpu_add_quantum_offset_nopr(elapsed);
	THIS_TASK->t_atime.add_quantum(elapsed, length);
#endif /* !CONFIG_USE_NEW_REALTIME */
}


PUBLIC NOBLOCK void
NOTHROW(KCALL cpu_enable_preemptive_interrupts_nopr)(void) {
#ifdef CONFIG_USE_NEW_REALTIME
	/* TODO (Without this, realtime() won't update whenever preemptive interrupts
	 *       are disabled, which they are whenever all threads are sleeping, and
	 *       none of them have specified any timeouts (as is the case when KOS
	 *       is hosting busybox's commandline prompt))
	 * A good solution here would be to simply mark the realtime clock as not being
	 * synced at all, and re-add the ability to automatically re-sync an entirely
	 * un-synced cpu clock from within `realtime()'! */
#else /* CONFIG_USE_NEW_REALTIME */
	REF struct realtime_clock_struct *rtc;
	assert(!PREEMPTION_ENABLED());
	rtc = realtime_clock.get_nopr();
	if (rtc) {
		/* Load RT information to make it look like
		 * our CPU is perfectly in sync with the RTC */
		struct timespec now;
		struct cpu *me = THIS_CPU;
		now = (*rtc->rc_gettime)(rtc);
		decref_unlikely(rtc);
		if (now > FORCPU(me, thiscpu_last_resync.ct_real)) {
			FORCPU(me, thiscpu_last_resync.ct_real) = now;
			FORCPU(me, thiscpu_last_resync.ct_cpuj) = FORCPU(me, thiscpu_jiffies);
			FORCPU(me, thiscpu_last_resync.ct_cpuq) = 0;
			FORCPU(me, thiscpu_last_resync.ct_rtc)  = rtc;
		}
	}
#endif /* !CONFIG_USE_NEW_REALTIME */
	arch_cpu_enable_preemptive_interrupts_nopr();
}

/* Increment `thiscpu_quantum_offset' by `diff' incrementing the `thiscpu_jiffies' counter
 * when the resulting value turns out to be greater than `thiscpu_quantum_length',
 * in which case the value will also be truncated.
 * When `thiscpu_jiffies' is incremented, also check if this causes additional
 * tasks to time out, and if so, re-schedule them for execution. */
PUBLIC NOBLOCK NOPREEMPT quantum_diff_t
NOTHROW(FCALL cpu_add_quantum_offset_nopr)(quantum_diff_t diff) {
#if 1
	(void)diff;
	return PERCPU(thiscpu_quantum_length);
#else
	struct cpu *me = THIS_CPU;
	quantum_diff_t new_diff, more_jiffies = 0;
	quantum_diff_t length = FORCPU(me, thiscpu_quantum_length);
	assert(!PREEMPTION_ENABLED());
	if (OVERFLOW_UADD(FORCPU(me, thiscpu_quantum_offset), diff, &new_diff)) {
		more_jiffies = ((quantum_diff_t)-1 / length);
		new_diff     = (FORCPU(me, thiscpu_quantum_offset) + diff) - ((quantum_diff_t)-1);
	}
	if (new_diff >= length) {
		more_jiffies += new_diff / length;
		new_diff = new_diff % length;
	}
	FORCPU(me, thiscpu_quantum_offset) = new_diff;
	if (more_jiffies) {
		struct task *sleeper, *last_sleeper, *next;
		jtime_t new_jiffies;
		new_jiffies = FORCPU(me, thiscpu_jiffies) + more_jiffies;
		FORCPU(me, thiscpu_jiffies) = new_jiffies;
		if ((sleeper = me->c_sleeping) != NULL) {
			if (sleeper->t_sched.s_asleep.ss_timeout.q_jtime > new_jiffies)
				goto done_wakeup;
			if (((u64)sleeper->t_sched.s_asleep.ss_timeout.q_qtime *
			     sleeper->t_sched.s_asleep.ss_timeout.q_qsize) >
			    ((u64)new_diff * length))
				goto done_wakeup;
			last_sleeper = sleeper;
			ATOMIC_FETCHOR(sleeper->t_flags, TASK_FTIMEOUT | TASK_FRUNNING);
			while ((next = last_sleeper->t_sched.s_asleep.ss_tmonxt) != NULL) {
				STATIC_ASSERT(offsetof(struct task, t_sched.s_running.sr_runprv) !=
				              offsetof(struct task, t_sched.s_asleep.ss_tmonxt));
				if (next->t_sched.s_asleep.ss_timeout.q_jtime > new_jiffies)
					break;
				if (((u64)next->t_sched.s_asleep.ss_timeout.q_qtime *
				     next->t_sched.s_asleep.ss_timeout.q_qsize) >
				    ((u64)new_diff * length))
					break;
				ATOMIC_FETCHOR(next->t_flags, TASK_FTIMEOUT | TASK_FRUNNING);
				last_sleeper->t_sched.s_running.sr_runnxt = next;
				next->t_sched.s_running.sr_runprv         = last_sleeper;
				last_sleeper                              = next;
			}
			me->c_sleeping = next;
			if (next)
				next->t_sched.s_asleep.ss_pself = &me->c_sleeping;
			/* Re-schedule all of the sleepers. */
			next = me->c_current->t_sched.s_running.sr_runnxt;
			sleeper->t_sched.s_running.sr_runprv       = me->c_current;
			last_sleeper->t_sched.s_running.sr_runnxt  = next;
			next->t_sched.s_running.sr_runprv          = last_sleeper;
			me->c_current->t_sched.s_running.sr_runnxt = sleeper;
		}
	}
done_wakeup:
	return length;
#endif
}



DECL_END

#endif /* !GUARD_KERNEL_SRC_SCHED_TIME_C */
