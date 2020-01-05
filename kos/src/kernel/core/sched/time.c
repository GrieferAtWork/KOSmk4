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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_SRC_SCHED_TIME_C
#define GUARD_KERNEL_SRC_SCHED_TIME_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/driver.h>
#include <kernel/malloc.h>
#include <kernel/printk.h>
#include <kernel/types.h>
#include <sched/cpu.h>
#include <sched/task.h>
#include <sched/time.h>

#include <hybrid/atomic.h>
#include <hybrid/overflow.h>

#include <kos/jiffies.h>

#include <assert.h>

DECL_BEGIN

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



struct cpu_timestamp {
	struct timespec ct_real; /* Realtime */
	struct timespec ct_prec; /* Realtime precision */
	jtime_t         ct_cpuj; /* CPU time jiffies */
	quantum_diff_t  ct_cpuq; /* CPU time quantum */
};

/* Timestamp for the last realtime re-sync made by the CPU */
PRIVATE ATTR_PERCPU struct cpu_timestamp thiscpu_last_resync = {};

INTERN NOBLOCK void
NOTHROW(FCALL cpu_resync_realtime)(struct cpu *__restrict self) {
	REF struct realtime_clock_struct *rt;
	struct cpu_timestamp *cts;
	struct cpu_timestamp nts;
	quantum_diff_t elapsed, cpus;
	assert(!PREEMPTION_ENABLED());
	rt = realtime_clock.get_nopr();
	if (!rt)
		return;
	cts = &FORCPU(self, thiscpu_last_resync);
	COMPILER_BARRIER();
	nts.ct_real = (*rt->rc_gettime)(rt);
	elapsed     = cpu_quantum_elapsed_nopr(self, &nts.ct_cpuj);
	COMPILER_BARRIER();
	nts.ct_prec = rt->rc_precision;
	decref_unlikely(rt);
	cpus = FORCPU(self, thiscpu_quantum_length);
	nts.ct_cpuq = FORCPU(self, thiscpu_quantum_offset);
	if (OVERFLOW_UADD(nts.ct_cpuq, elapsed, &nts.ct_cpuq)) {
		nts.ct_cpuj += ((quantum_diff_t)-1) / cpus;
		nts.ct_cpuq += elapsed;
		nts.ct_cpuq -= (quantum_diff_t)-1;
	}
	if (nts.ct_cpuq >= cpus) {
		nts.ct_cpuj += nts.ct_cpuq / cpus;
		nts.ct_cpuq = nts.ct_cpuq % cpus;
	}
	if (!cts->ct_prec.tv_nsec && !cts->ct_prec.tv_sec) {
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
		cputime_diff_j = nts.ct_cpuj - cts->ct_cpuj;
		if (nts.ct_cpuq < cts->ct_cpuq) {
			--cputime_diff_j;
			cputime_diff_q = (nts.ct_cpuq + cpus) - cts->ct_cpuq;
		} else {
			cputime_diff_q = nts.ct_cpuq - cts->ct_cpuq;
		}
		cpu_elapsed.tv_sec  = cputime_diff_j / HZ;
		cpu_elapsed.tv_nsec = ((cputime_diff_j % HZ) * (__NSECS_PER_SEC / HZ)) +
		                      (syscall_ulong_t)((u64)((u64)cputime_diff_q *
		                                              (__NSECS_PER_SEC / HZ)) /
		                                        cpus);
		rt_elapsed = nts.ct_real - cts->ct_real;
		if (cpu_elapsed > rt_elapsed) {
			elapsed_error      = cpu_elapsed - rt_elapsed;
			cpu_clock_too_fast = true;
		} else {
			elapsed_error      = rt_elapsed - cpu_elapsed;
			cpu_clock_too_fast = false;
		}
		if (elapsed_error > nts.ct_prec) {
			u64 elapsed_error_nano, cpu_elapsed_nano;
			quantum_diff_t adjust, new_quantum_length;
			elapsed_error -= nts.ct_prec;
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
			adjust = (quantum_diff_t)(((u64)elapsed_error_nano * (cpus / JIFFIES_FROM_SECONDS(3))) / cpu_elapsed_nano);
			if (adjust != 0) {
				new_quantum_length = cpu_clock_too_fast ? cpus + adjust : cpus - adjust;
				printk(KERN_INFO "[cpu#%u] Adjust quantum length %I32u -> %I32u\n",
				       self->c_id, cpus, new_quantum_length);
				FORCPU(self, thiscpu_quantum_length) = new_quantum_length;
				arch_cpu_update_quantum_length();
				*cts = nts;
			}
		}
	}
}

INTERN NOBLOCK void
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
	if (!FORCPU(me, thiscpu_last_resync.ct_prec.tv_sec) &&
	    !FORCPU(me, thiscpu_last_resync.ct_prec.tv_nsec))
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
		cpu_jtime += ((quantum_diff_t)-1) / cpu_qsize;
		cpu_qtime += cpu_qoffs;
		cpu_qtime -= (quantum_diff_t)-1;
	}
	if (OVERFLOW_USUB(cpu_qtime, resync_cpuq, &cpu_qtime)) {
		cpu_jtime -= ((quantum_diff_t)-1) / cpu_qsize;
		cpu_qtime += (quantum_diff_t)-1;
		cpu_qtime -= resync_cpuq;
	}
	if (cpu_qtime > cpu_qsize) {
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
	return result;
}



/* prevent issues hardware timer roll-over happening
 * before we've able to read the timestamp counter. */
PRIVATE ATTR_PERCPU jtime_t thiscpu_last_qtime_j = 0;
PRIVATE ATTR_PERCPU quantum_diff_t thiscpu_last_qtime_q = 0;

/* Returns the number of ticks that have passed since the start
 * of the current quantum. - The true current CPU-local time
 * (in ticks) can then be calculated as:
 * >> (thiscpu_jiffies * PERCPU(thiscpu_quantum_length)) + PERCPU(thiscpu_quantum_offset) + cpu_quantum_elapsed();
 * NOTE: The `*_nopr' variants may only be called when preemption is disabled! */
PUBLIC NOBLOCK WUNUSED NONNULL((1, 2)) quantum_diff_t
NOTHROW(FCALL cpu_quantum_elapsed)(struct cpu *__restrict mycpu,
                                   jtime_t *__restrict preal_jtime) {
	quantum_diff_t result;
	pflag_t was;
	was = PREEMPTION_PUSHOFF();
	result = cpu_quantum_elapsed_nopr(mycpu, preal_jtime);
	PREEMPTION_POP(was);
	return result;
}

PUBLIC NOBLOCK WUNUSED NONNULL((1, 2)) quantum_diff_t
NOTHROW(FCALL cpu_quantum_elapsed_nopr)(struct cpu *__restrict mycpu,
                                        jtime_t *__restrict preal_jtime) {
	quantum_diff_t result;
	result = arch_cpu_quantum_elapsed_nopr();
	*preal_jtime = FORCPU(mycpu, thiscpu_jiffies);
	if (result < FORCPU(mycpu, thiscpu_last_qtime_q) &&
	    *preal_jtime == FORCPU(mycpu, thiscpu_last_qtime_j)) {
		FORCPU(mycpu, thiscpu_last_qtime_q) = (quantum_diff_t)-1;
		++*preal_jtime;
	} else {
		FORCPU(mycpu, thiscpu_last_qtime_j) = *preal_jtime;
		FORCPU(mycpu, thiscpu_last_qtime_q) = result;
	}
	return result;
}

PUBLIC NOBLOCK WUNUSED NONNULL((1, 2)) quantum_diff_t
NOTHROW(FCALL cpu_quantum_remaining)(struct cpu *__restrict mycpu,
                                     jtime_t *__restrict preal_jtime) {
	quantum_diff_t result;
	pflag_t was;
	was = PREEMPTION_PUSHOFF();
	result = cpu_quantum_remaining_nopr(mycpu, preal_jtime);
	PREEMPTION_POP(was);
	return result;
}

PUBLIC NOBLOCK WUNUSED NONNULL((1, 2)) quantum_diff_t
NOTHROW(FCALL cpu_quantum_remaining_nopr)(struct cpu *__restrict mycpu,
                                          jtime_t *__restrict preal_jtime) {
	quantum_diff_t result;
	result = cpu_quantum_elapsed_nopr(mycpu, preal_jtime);
	return FORCPU(mycpu, thiscpu_quantum_length) - result;
}

/* Adjust quantum time to track the calling thread's quantum about to end prematurely. */
PUBLIC NOBLOCK void
NOTHROW(KCALL cpu_quantum_end)(void) {
	quantum_diff_t elapsed, length;
	struct cpu *mycpu = THIS_CPU;
	assert(!PREEMPTION_ENABLED());
	elapsed = arch_cpu_quantum_elapsed_nopr();
	if (elapsed < FORCPU(mycpu, thiscpu_last_qtime_q) &&
	    FORCPU(mycpu, thiscpu_jiffies) == FORCPU(mycpu, thiscpu_last_qtime_j)) {
		FORCPU(mycpu, thiscpu_last_qtime_q) = (quantum_diff_t)-1;
		elapsed += FORCPU(mycpu, thiscpu_quantum_length);
	} else {
		FORCPU(mycpu, thiscpu_last_qtime_j) = FORCPU(mycpu, thiscpu_jiffies);
		FORCPU(mycpu, thiscpu_last_qtime_q) = elapsed;
	}
	cpu_quantum_reset_nopr();
	length = cpu_add_quantum_offset(elapsed);
	THIS_TASK->t_atime.add_quantum(elapsed, length);
}




PUBLIC NOBLOCK void
NOTHROW(KCALL cpu_disable_preemptive_interrupts_nopr)(void) {
	quantum_diff_t elapsed, length;
	struct cpu *mycpu = THIS_CPU;
	assert(!PREEMPTION_ENABLED());
	elapsed = arch_cpu_quantum_elapsed_nopr();
	arch_cpu_disable_preemptive_interrupts_nopr();
	if (elapsed < FORCPU(mycpu, thiscpu_last_qtime_q) &&
	    FORCPU(mycpu, thiscpu_jiffies) == FORCPU(mycpu, thiscpu_last_qtime_j)) {
		FORCPU(mycpu, thiscpu_last_qtime_q) = (quantum_diff_t)-1;
		elapsed += FORCPU(mycpu, thiscpu_quantum_length);
	} else {
		FORCPU(mycpu, thiscpu_last_qtime_j) = FORCPU(mycpu, thiscpu_jiffies);
		FORCPU(mycpu, thiscpu_last_qtime_q) = elapsed;
	}
	length = cpu_add_quantum_offset(elapsed);
	THIS_TASK->t_atime.add_quantum(elapsed, length);
}


PUBLIC NOBLOCK void
NOTHROW(KCALL cpu_enable_preemptive_interrupts_nopr)(void) {
	REF struct realtime_clock_struct *rt;
	assert(!PREEMPTION_ENABLED());
	rt = realtime_clock.get_nopr();
	if (rt) {
		/* Load RT information to make it look like
		 * our CPU is perfectly in sync with the RTC */
		struct timespec now;
		struct cpu *me = THIS_CPU;
		now = (*rt->rc_gettime)(rt);
		FORCPU(me, thiscpu_last_resync.ct_prec) = rt->rc_precision;
		decref_unlikely(rt);
		FORCPU(me, thiscpu_last_resync.ct_real) = now;
		FORCPU(me, thiscpu_last_resync.ct_cpuj) = FORCPU(me, thiscpu_jiffies);
		FORCPU(me, thiscpu_last_resync.ct_cpuq) = 0;
	}
	arch_cpu_enable_preemptive_interrupts_nopr();
}

PUBLIC NOBLOCK void
NOTHROW(KCALL cpu_disable_preemptive_interrupts)(void) {
	pflag_t was = PREEMPTION_PUSHOFF();
	cpu_disable_preemptive_interrupts_nopr();
	PREEMPTION_POP(was);
}

PUBLIC NOBLOCK void
NOTHROW(KCALL cpu_enable_preemptive_interrupts)(void) {
	pflag_t was = PREEMPTION_PUSHOFF();
	cpu_enable_preemptive_interrupts_nopr();
	PREEMPTION_POP(was);
}



DECL_END

#endif /* !GUARD_KERNEL_SRC_SCHED_TIME_C */
