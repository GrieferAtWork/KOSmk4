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
#ifndef GUARD_KERNEL_SRC_SCHED_TIMER_C
#define GUARD_KERNEL_SRC_SCHED_TIMER_C 1
#define _GNU_SOURCE 1
#define _KOS_SOURCE 1
#define _TIME64_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/driver.h>
#include <kernel/except.h>
#include <kernel/handle-proto.h>
#include <kernel/handman.h>
#include <kernel/malloc.h>
#include <kernel/syscall.h>
#include <kernel/user.h>
#include <sched/async.h>
#include <sched/group.h>
#include <sched/rpc.h>
#include <sched/sig.h>
#include <sched/task.h>
#include <sched/timer.h>
#include <sched/tsc.h>

#include <hybrid/atomic.h>
#include <hybrid/overflow.h>
#include <hybrid/unaligned.h>

#include <bits/os/itimerspec.h>
#include <compat/config.h>
#include <kos/aref.h>
#include <kos/except.h>
#include <kos/except/reason/inval.h>
#include <linux/timerfd.h>
#include <sys/stat.h>
#include <sys/timerfd.h>

#include <assert.h>
#include <errno.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <time.h>

#ifdef __ARCH_HAVE_COMPAT
#include <compat/bits/os/itimerspec.h>
#endif /* __ARCH_HAVE_COMPAT */

DECL_BEGIN

#define __uclockid_t __CRT_PRIVATE_UINT(__SIZEOF_CLOCKID_T__)
typedef __uclockid_t uclockid_t;


/* Known clock types */
PRIVATE WUNUSED struct timespec FCALL
clock_default_getres(clockid_t clockid) {
	struct timespec result;
	(void)clockid;
	result.tv_sec  = 0;
	result.tv_nsec = 1;
	return result;
}

PRIVATE void FCALL
clock_default_connect(clockid_t clockid) {
	(void)clockid;
	COMPILER_IMPURE();
	/* Nothing */
}


/************************************************************************/
/* REALTIME CLOCK (nanoseconds time 1970-01-01)                         */
/************************************************************************/
#define clock_realtime_getres  clock_default_getres
#define clock_realtime_connect clock_default_connect
PRIVATE WUNUSED struct timespec FCALL
clock_realtime_gettime(clockid_t clockid) {
	(void)clockid;
	return realtime();
}

PRIVATE WUNUSED ktime_t FCALL
clock_realtime_astimeout(clockid_t clockid,
                         USER CHECKED struct timespec const *__restrict p_ts) {
	(void)clockid;
	return ktime_from_user(p_ts);
}



/************************************************************************/
/* BOOTTIME CLOCK (nanoseconds since boot)                              */
/************************************************************************/
#define clock_boottime_getres  clock_default_getres
#define clock_boottime_connect clock_default_connect
PRIVATE struct timespec FCALL
clock_boottime_gettime(clockid_t clockid) {
	ktime_t now = ktime();
	struct timespec result;
	(void)clockid;
	result.tv_sec  = (time_t)(now / NSEC_PER_SEC);
	result.tv_nsec = (syscall_ulong_t)(now % NSEC_PER_SEC);
	return result;
}

PRIVATE WUNUSED ktime_t FCALL
clock_boottime_astimeout(clockid_t clockid,
                         USER CHECKED struct timespec const *__restrict p_ts) {
	(void)clockid;
	return relktime_from_user_rel(p_ts);
}




/************************************************************************/
/* UNSUPPORTED CLOCK                                                    */
/************************************************************************/
PRIVATE WUNUSED struct timespec FCALL
clock_notsup_gettime(clockid_t clockid) {
	THROW(E_NOT_IMPLEMENTED_UNSUPPORTED, clockid);
}

PRIVATE WUNUSED struct timespec FCALL
clock_notsup_getres(clockid_t clockid) {
	THROW(E_NOT_IMPLEMENTED_UNSUPPORTED, clockid);
}

PRIVATE WUNUSED ktime_t FCALL
clock_notsup_astimeout(clockid_t clockid, USER CHECKED struct timespec const *p_ts) {
	(void)p_ts;
	THROW(E_NOT_IMPLEMENTED_UNSUPPORTED, clockid);
}

PRIVATE void FCALL
clock_notsup_connect(clockid_t clockid) {
	THROW(E_NOT_IMPLEMENTED_UNSUPPORTED, clockid);
}




/************************************************************************/
/* THREAD CPU TIME CLOCK                                                */
/************************************************************************/
#define clock_thread_cputime_getres  clock_default_getres
#define clock_thread_cputime_connect clock_default_connect
PRIVATE WUNUSED struct timespec FCALL
clock_thread_cputime_gettime(clockid_t clockid) {
	struct task *me = THIS_TASK;
	ktime_t active;
	(void)clockid;
	active = FORTASK(me, this_activetime);
	active += (ktime() - FORTASK(me, this_stoptime));
	return relktime_to_reltimespec(active);
}

PRIVATE WUNUSED ktime_t FCALL
clock_thread_cputime_astimeout(clockid_t clockid, USER CHECKED struct timespec const *p_ts) {
	struct task *me = THIS_TASK;
	struct timespec ts;
	struct timespec now_ts;
	ktime_t active, now, remaining;
	ts = *p_ts;
	COMPILER_READ_BARRIER();
	(void)clockid;

	/* Figure out the  current kernel  time, and  how
	 * much CPU time the calling thread got thus far. */
	active = FORTASK(me, this_activetime);
	now    = ktime();
	active += (now - FORTASK(me, this_stoptime));
	now_ts = relktime_to_reltimespec(active);

	/* Check if the given timeout is already in the past. */
	if (now_ts >= ts)
		return KTIME_NONBLOCK;

	/* Figure out how long until the given timeout expires. */
	ts -= now_ts;
	remaining = reltimespec_to_relktime(&ts);

	/* Determine the absolute ktime of when the timeout expires. */
	if (OVERFLOW_UADD(now, remaining, &now))
		now = KTIME_INFINITE;
	return now;
}




/************************************************************************/
/* CLOCK TYPE DESCRIPTORS                                               */
/************************************************************************/
PUBLIC_CONST struct clocktype const clock_types[CLOCK_COUNT] = {
	[CLOCK_REALTIME] = {
		.ct_gettime   = &clock_realtime_gettime,
		.ct_getres    = &clock_realtime_getres,
		.ct_astimeout = &clock_realtime_astimeout,
		.ct_connect   = &clock_realtime_connect,
	},
	[CLOCK_MONOTONIC] = {
		.ct_gettime   = &clock_boottime_gettime,
		.ct_getres    = &clock_boottime_getres,
		.ct_astimeout = &clock_boottime_astimeout,
		.ct_connect   = &clock_boottime_connect,
	},
	[CLOCK_PROCESS_CPUTIME_ID] = {
		/* TODO */
		.ct_gettime   = &clock_notsup_gettime,
		.ct_getres    = &clock_notsup_getres,
		.ct_astimeout = &clock_notsup_astimeout,
		.ct_connect   = &clock_notsup_connect,
	},
	[CLOCK_THREAD_CPUTIME_ID] = {
		.ct_gettime   = &clock_thread_cputime_gettime,
		.ct_getres    = &clock_thread_cputime_getres,
		.ct_astimeout = &clock_thread_cputime_astimeout,
		.ct_connect   = &clock_thread_cputime_connect,
	},
	[CLOCK_MONOTONIC_RAW] = {
		/* TODO: Direct RTC access */
		.ct_gettime   = &clock_realtime_gettime,
		.ct_getres    = &clock_realtime_getres,
		.ct_astimeout = &clock_realtime_astimeout,
		.ct_connect   = &clock_realtime_connect,
	},
	[CLOCK_REALTIME_COARSE] = {
		.ct_gettime   = &clock_realtime_gettime,
		.ct_getres    = &clock_realtime_getres,
		.ct_astimeout = &clock_realtime_astimeout,
		.ct_connect   = &clock_realtime_connect,
	},
	[CLOCK_MONOTONIC_COARSE] = {
		.ct_gettime   = &clock_boottime_gettime,
		.ct_getres    = &clock_boottime_getres,
		.ct_astimeout = &clock_boottime_astimeout,
		.ct_connect   = &clock_boottime_connect,
	},
	[CLOCK_BOOTTIME] = {
		.ct_gettime   = &clock_boottime_gettime,
		.ct_getres    = &clock_boottime_getres,
		.ct_astimeout = &clock_boottime_astimeout,
		.ct_connect   = &clock_boottime_connect,
	},
	[CLOCK_REALTIME_ALARM] = {
		.ct_gettime   = &clock_realtime_gettime,
		.ct_getres    = &clock_realtime_getres,
		.ct_astimeout = &clock_realtime_astimeout,
		.ct_connect   = &clock_realtime_connect,
	},
	[CLOCK_BOOTTIME_ALARM] = {
		.ct_gettime   = &clock_boottime_gettime,
		.ct_getres    = &clock_boottime_getres,
		.ct_astimeout = &clock_boottime_astimeout,
		.ct_connect   = &clock_boottime_connect,
	},
	[10] = {
		.ct_gettime   = &clock_notsup_gettime,
		.ct_getres    = &clock_notsup_getres,
		.ct_astimeout = &clock_notsup_astimeout,
		.ct_connect   = &clock_notsup_connect,
	},
	[CLOCK_TAI] = {
		.ct_gettime   = &clock_realtime_gettime,
		.ct_getres    = &clock_realtime_getres,
		.ct_astimeout = &clock_realtime_astimeout,
		.ct_connect   = &clock_realtime_connect,
	},
};

PUBLIC_CONST struct clocktype const clock_pid = {
	/* TODO: Like `CLOCK_THREAD_CPUTIME_ID' / `CLOCK_PROCESS_CPUTIME_ID', but for arbitrary threads/processes
	 * Problem: `this_activetime' cannot be safely accessed for threads hosted by other CPUs (no way to prevent
	 *          the value from changing while it is read, and since it's 64-bit, no way to portably read it  in
	 *          an atomic operation). */
	.ct_gettime   = &clock_notsup_gettime,
	.ct_getres    = &clock_notsup_getres,
	.ct_astimeout = &clock_notsup_astimeout,
	.ct_connect   = &clock_notsup_connect,
};


/* Lookup the clock for a given clockid. */
PUBLIC ATTR_RETNONNULL WUNUSED struct clocktype const *FCALL
clock_lookup(clockid_t clockid) THROWS(E_INVALID_ARGUMENT_BAD_VALUE) {
	if unlikely((uclockid_t)clockid >= CLOCK_COUNT) {
		if (clockid < 0 && (clockid & 7) != 7)
			return &clock_pid;
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_BAD_CLOCKID,
		      clockid);
	}
	return &clock_types[(uclockid_t)clockid];
}


/* Return the # of times the timer has currently overrun:
 * >> CEIL((now - t_expire) / t_interval);
 * When `t_interval' is 0:
 * >> (now >= t_expire) ? 1 : 0; */
PUBLIC NOBLOCK WUNUSED NONNULL((1, 2)) uint64_t
NOTHROW(FCALL timer_getoverrun_locked)(struct timer const *__restrict self,
                                       struct timespec const *__restrict now) {
	uint64_t result;
	struct timespec time_since_expired;
	assert(timer_reading(self));
	if (*now < self->t_expire)
		return 0; /* Not yet expired. */
	if (!timer_isarmed(self))
		return 0; /* Special case: not armed. */
	if (!timer_hasinterval(self))
		return 1;
	time_since_expired = *now - self->t_expire;
	time_since_expired += self->t_interval;
	time_since_expired.sub_nanoseconds(1);
	result = time_since_expired / self->t_interval;
	return result;
}


/* Check if the timer has elapsed (more efficient alternative
 * to `timer_getoverrun_locked(self) > 0') */
PUBLIC WUNUSED NONNULL((1)) bool FCALL
timer_haselapsed(struct timer *__restrict self)
		THROWS(E_WOULDBLOCK) {
	bool result;
	struct timespec now = timer_getclocknow(self);
	timer_read(self);
	result = timer_haselapsed_locked(self, &now);
	timer_endread(self);
	return result;
}


/* Same as `timer_getoverrun_locked()', but when the timer has
 * an  interval, increase `t_expire' by `N * t_interval', such
 * that it barely becomes greater than `now', then return `N'.
 *
 * When the timer has no interval, return `0' if the timer has
 * not  yet expired, or `1' (alongside disarming it) if it has
 * expired. */
PUBLIC NOBLOCK NONNULL((1, 2)) uint64_t
NOTHROW(FCALL timer_takeoverrun_locked)(struct timer *__restrict self,
                                        struct timespec const *__restrict now) {
	uint64_t result;
	struct timespec time_since_expired;
	struct timespec extra_time;
	assert(timer_writing(self));
	if (*now < self->t_expire)
		return 0; /* Not yet expired. */
	if (!timer_isarmed(self))
		return 0; /* Special case: not armed. */
	if (!timer_hasinterval(self)) {
		/* Non-interval timers are disarmed when they expire. */
		timer_disarm(self);
		return 1;
	}

	/* Figure out how often the timer has already expired. */
	time_since_expired = *now - self->t_expire;
	time_since_expired += self->t_interval;
	time_since_expired.sub_nanoseconds(1);
	result = time_since_expired / self->t_interval;

	/* Set the expire timestamp to point into the future. */
	extra_time = self->t_interval * result;
	self->t_expire += extra_time;
	return result;
}

PUBLIC WUNUSED NONNULL((1)) uint64_t FCALL
timer_takeoverrun(struct timer *__restrict self)
		THROWS(E_WOULDBLOCK) {
	uint64_t result;
	struct timespec now = timer_getclocknow(self);
	timer_write(self);
	result = timer_takeoverrun_locked(self, &now);
	timer_endwrite(self);
	return result;
}

/* Similar to `timer_takeoverrun_locked()', but doesn't  write-back
 * the next expire-timestamp to `self'. Instead, it calculates  the
 * next point in time when `self' will expire after `now', and then
 * returns that timestamp.
 * When `self' isn't an interval-timer, this function returns  the
 * currently configured expire-timestamp (if `> *now'), or an all-
 * zero timestamp if already expired. */
PUBLIC NOBLOCK WUNUSED NONNULL((1, 2)) struct timespec
NOTHROW(FCALL timer_getnextexpire_locked)(struct timer const *__restrict self,
                                          struct timespec const *__restrict now) {
	struct timespec result;
	struct timespec time_since_expired;
	struct timespec extra_time;
	uint64_t timer_overrun;
	assert(timer_reading(self));
	if (*now < self->t_expire)
		return self->t_expire; /* Not yet expired. */
	if (!timer_hasinterval(self)) {
		/* Non-interval timers are disarmed when they expire. */
		result.tv_sec  = 0;
		result.tv_nsec = 0;
		return result;
	}

	/* Figure out how often the timer has already expired. */
	time_since_expired = *now - self->t_expire;
	time_since_expired += self->t_interval;
	time_since_expired.sub_nanoseconds(1);
	timer_overrun = time_since_expired / self->t_interval;
	result = self->t_expire;

	/* Set the expire timestamp to point into the future. */
	extra_time = self->t_interval * timer_overrun;
	result += extra_time;
	return result;
}


/* Connect to the given timer `self' and calculate a  conservative
 * guess on when  the timer  will probably expire  (it may  expire
 * earlier than this guess, but in this case a signal is broadcast
 * which this function has connected to).
 *
 * This function is designed for use with `struct async_ops::ao_connect'
 * @return: KTIME_NONBLOCK: Timer has already expired (at least once) */
PUBLIC WUNUSED NONNULL((1)) ktime_t FCALL
timer_connect(struct timer *__restrict self)
		THROWS(E_WOULDBLOCK, ...) {
	ktime_t result;
	struct timespec expires;

	/* Connect to  the changed-signal  (must  be done  _before_  we
	 * read the current expire-value, so that our thread  receiving
	 * notification of the timer being re-configured is interlocked
	 * with the expire-value we read below) */
	task_connect(&self->t_changed);

	/* Connect to the clock itself (its signals get  broadcast
	 * when something happens that changes its notion of time) */
	(*self->t_clock->ct_connect)(self->t_clockid);

	/* Take the current expire-timestamp... */
	timer_read(self);
	expires = self->t_expire;
	timer_endread(self);

	/* ... and convert it into a ktime-timeout */
	result = (*self->t_clock->ct_astimeout)(self->t_clockid, &expires);
	return result;
}

/* Blocking function to wait until  the timer has expired at  least
 * once, at which point `timer_takeoverrun_locked()' is called, and
 * its value is returned.
 *
 * The non-blocking equivalent to this is `timer_takeoverrun()' */
PUBLIC BLOCKING WUNUSED NONNULL((1)) uint64_t FCALL
timer_waitfor(struct timer *__restrict self)
		THROWS(E_WOULDBLOCK, ...) {
	uint64_t result;
	while ((result = timer_takeoverrun(self)) == 0) {
		ktime_t timeout;
		timeout = timer_connect(self);
		task_waitfor(timeout);
	}
	return result;
}

/* Get the current configuration of `self' */
PUBLIC WUNUSED NONNULL((1)) struct itimerspec FCALL
timer_gettime(struct timer *__restrict self)
		THROWS(E_WOULDBLOCK, E_SEGFAULT) {
	struct timespec now;
	struct itimerspec result;
	now = timer_getclocknow(self);
	timer_read(self);
	result.it_value    = timer_getnextexpire_locked(self, &now);
	result.it_interval = self->t_interval;
	timer_endread(self);
	return result;
}

PRIVATE void FCALL
validate_tv_nsec(ulongptr_t tv_nsec)
		THROWS(E_INVALID_ARGUMENT_BAD_VALUE) {
	if unlikely(tv_nsec >= NSEC_PER_SEC) {
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_BAD_TIMESPEC_NSEC,
		      tv_nsec);
	}
}

/* Set the configuration of `self' */
PUBLIC NONNULL((1)) void FCALL
timer_settime(struct timer *__restrict self,
              /*[0..1]*/ USER CHECKED struct itimerspec const *value,
              /*[0..1]*/ USER CHECKED struct itimerspec *old_value)
		THROWS(E_WOULDBLOCK, E_SEGFAULT, E_INVALID_ARGUMENT_BAD_VALUE) {
	if (value != NULL) {
		struct itimerspec config, old_config;
		memcpy(&config, value, sizeof(config));
		COMPILER_READ_BARRIER();

		/* Validate new configuration */
		validate_tv_nsec(config.it_value.tv_nsec);
		validate_tv_nsec(config.it_interval.tv_nsec);

		/* Save new configuration */
		timer_write(self);
		old_config.it_value    = self->t_expire;
		old_config.it_interval = self->t_interval;
		self->t_expire         = config.it_value;
		self->t_interval       = config.it_interval;
		timer_endwrite(self);

		/* Indicate that the configuration has changed. */
		sig_broadcast(&self->t_changed);

		/* Remember the old configuration if the caller wants it. */
		if (old_value) {
			COMPILER_WRITE_BARRIER();
			memcpy(old_value, &old_config, sizeof(old_config));
		}
	} else if (old_value != NULL) {
		/* Only query the current config. */
		struct itimerspec old_config;
		old_config = timer_gettime(self);
		COMPILER_WRITE_BARRIER();
		*old_value = old_config;
	}
}







/************************************************************************/
/* USER-SPACE TIMERFD OBJECT                                            */
/************************************************************************/

/* Check if the timer has elapsed (more efficient alternative
 * to `timer_getoverrun_locked(self) > 0') */
PRIVATE WUNUSED NONNULL((1)) bool FCALL
timerfd_haselapsed(struct timerfd *__restrict self)
		THROWS(E_WOULDBLOCK) {
	bool result;
	struct timespec now = timer_getclocknow(&self->tfd_timer);
	timer_read(&self->tfd_timer);
	result = self->tfd_xover != 0 ||
	         timer_haselapsed_locked(&self->tfd_timer, &now);
	timer_endread(&self->tfd_timer);
	return result;
}




AWREF(timerfd_awref, timerfd);
struct timerfd_async: async {
	struct timerfd_awref tfa_timerfd; /* [0..1] Linked timerfd (when NULL, lazily destroy async handler) */
};
#define async_gettimerfd(self) \
	awref_get(&((struct timerfd_async *)(self))->tfa_timerfd)


PRIVATE NONNULL((1)) ktime_t FCALL
timerfd_async_connect(struct async *__restrict self) {
	REF struct timerfd *me;
	me = async_gettimerfd(self);
	if unlikely(!me)
		return KTIME_NONBLOCK;
	FINALLY_DECREF_UNLIKELY(me);
	return timer_connect(&me->tfd_timer);
}

PRIVATE WUNUSED NONNULL((1)) bool FCALL
timerfd_async_test(struct async *__restrict self) {
	REF struct timerfd *me;
	me = async_gettimerfd(self);
	if unlikely(!me)
		return true;
	FINALLY_DECREF_UNLIKELY(me);
	return timerfd_haselapsed(me);
}

PRIVATE WUNUSED NONNULL((1)) unsigned int FCALL
timerfd_async_work(struct async *__restrict self) {
	REF struct timerfd *me;
	me = async_gettimerfd(self);
	if unlikely(!me)
		return ASYNC_CANCEL;

	/* NOTE: No need to synchronize with another thread calling `async_start()' here.
	 *       Even though we unconditionally  return `ASYNC_FINISHED' here, the  async
	 *       system automatically interlocks  calls to `ao_work'  with other  threads
	 *       making calls to `async_start()', but that `ao_work's return value simply
	 *       ends up being ignored in this case. */
	FINALLY_DECREF_UNLIKELY(me);
	sig_broadcast(&me->tfd_elapse);
	return ASYNC_FINISHED;
}

PRIVATE WUNUSED NONNULL((1)) unsigned int FCALL
timerfd_async_time(struct async *__restrict self) {
	/* Return `ASYNC_RESUME'  to have  the caller  use
	 * `timerfd_async_work()' to handle timeout events */
	(void)self;
	return ASYNC_RESUME;
}


PRIVATE struct async_ops const timerfd_async_ops = {
	.ao_driver  = &drv_self,
	.ao_destroy = NULL, /* Not needed */
	.ao_connect = &timerfd_async_connect,
	.ao_test    = &timerfd_async_test,
	.ao_work    = &timerfd_async_work,
	.ao_time    = &timerfd_async_time,
};




/* Destroy a given `struct timerfd' */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL timerfd_destroy)(struct timerfd *__restrict self) {
	sig_broadcast_for_fini(&self->tfd_elapse);
	timer_fini(&self->tfd_timer);
	/* If allocated, halt a linked async job. */
	if (self->tfd_async != NULL)
		decref(async_cancel(self->tfd_async));
	kfree(self);
}


/* Create a new timerfd object.
 *
 * The  returned object is unarmed by default, and
 * needs to be configured with `timerfd_settime()'
 * @throws: E_INVALID_ARGUMENT_BAD_VALUE:E_INVALID_ARGUMENT_CONTEXT_BAD_CLOCKID: ... */
PUBLIC WUNUSED REF struct timerfd *FCALL
timerfd_create(clockid_t clockid)
		THROWS(E_BADALLOC, E_INVALID_ARGUMENT_BAD_VALUE) {
	REF struct timerfd *result;
	result = (REF struct timerfd *)kmemalign(alignof(struct timerfd),
	                                         sizeof(struct timerfd),
	                                         GFP_CALLOC);
	TRY {
		timer_cinit(&result->tfd_timer, clockid);
	} EXCEPT {
		kfree(result);
		RETHROW();
	}
	assert(result->tfd_async == NULL);
	assert(result->tfd_xover == 0);
	result->tfd_refcnt = 1;
	sig_cinit(&result->tfd_elapse);
	return result;
}

PUBLIC NONNULL((1)) void FCALL
timerfd_settime(struct timerfd *__restrict self,
                /*[0..1]*/ USER CHECKED struct itimerspec const *value,
                /*[0..1]*/ USER CHECKED struct itimerspec *old_value)
		THROWS(E_WOULDBLOCK, E_SEGFAULT, E_INVALID_ARGUMENT_BAD_VALUE) {
	if (value != NULL) {
		struct itimerspec config, old_config;
		memcpy(&config, value, sizeof(config));
		COMPILER_READ_BARRIER();

		/* Validate new configuration */
		validate_tv_nsec(config.it_value.tv_nsec);
		validate_tv_nsec(config.it_interval.tv_nsec);

		/* Save new configuration */
		timer_write(&self->tfd_timer);
		old_config.it_value        = self->tfd_timer.t_expire;
		old_config.it_interval     = self->tfd_timer.t_interval;
		self->tfd_timer.t_expire   = config.it_value;
		self->tfd_timer.t_interval = config.it_interval;
		self->tfd_xover            = 0;
		timer_endwrite(&self->tfd_timer);

		/* Indicate that the configuration has changed. */
		sig_broadcast(&self->tfd_timer.t_changed);

		/* Remember the old configuration if the caller wants it. */
		if (old_value) {
			COMPILER_WRITE_BARRIER();
			memcpy(old_value, &old_config, sizeof(old_config));
		}
	} else if (old_value != NULL) {
		/* Only query the current config. */
		struct itimerspec old_config;
		old_config = timerfd_gettime(self);
		COMPILER_WRITE_BARRIER();
		*old_value = old_config;
	}
}

PUBLIC BLOCKING WUNUSED NONNULL((1)) uint64_t FCALL
timerfd_trywaitfor(struct timerfd *__restrict self)
		THROWS(E_WOULDBLOCK, ...) {
	uint64_t result, extra;
	struct timespec now = timer_getclocknow(&self->tfd_timer);
	timer_write(&self->tfd_timer);
	result = timer_takeoverrun_locked(&self->tfd_timer, &now);
	extra  = self->tfd_xover;
	self->tfd_xover = 0;
	timer_endwrite(&self->tfd_timer);
	if (OVERFLOW_UADD(result, extra, &result))
		result = UINT64_MAX;
	return result;
}

PUBLIC BLOCKING WUNUSED NONNULL((1)) uint64_t FCALL
timerfd_waitfor(struct timerfd *__restrict self)
		THROWS(E_WOULDBLOCK, ...) {
	uint64_t result;
	while ((result = timerfd_trywaitfor(self)) == 0) {
		ktime_t timeout;
		timeout = timer_connect(&self->tfd_timer);
		task_waitfor(timeout);
	}
	return result;
}

PRIVATE ATTR_RETNONNULL WUNUSED NONNULL((1)) struct timerfd_async *FCALL
timerfd_get_async_timeout_notifier(struct timerfd *__restrict self)
		THROWS(E_BADALLOC) {
	struct timerfd_async *result;
again:
	result = ATOMIC_READ(self->tfd_async);
	if (!result) {
		result = async_new(struct timerfd_async, &timerfd_async_ops);
		awref_init(&result->tfa_timerfd, self);
		if unlikely(!ATOMIC_CMPXCH(self->tfd_async, NULL, result)) {
			async_destroy(result);
			goto again;
		}
	}
	return result;
}

PRIVATE NONNULL((1)) void FCALL
timerfd_start_async_timeout_notifier(struct timerfd *__restrict self)
		THROWS(E_BADALLOC) {
	struct timerfd_async *job;
	job = timerfd_get_async_timeout_notifier(self);
	async_start(job);
}


/* Handle object type integration */
DEFINE_HANDLE_REFCNT_FUNCTIONS(timerfd, struct timerfd);

INTERN BLOCKING WUNUSED NONNULL((1)) size_t KCALL
handle_timerfd_read(struct timerfd *__restrict self, USER CHECKED void *dst,
                    size_t num_bytes, iomode_t mode) THROWS(...) {
	uint64_t num_overruns;
	if unlikely(num_bytes < 8) {
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_TIMERFD_READ_BUFSIZE,
		      num_bytes);
	}

	/* Wait for the timerfd to expire */
	num_overruns = timerfd_trywaitfor(self);
	if (num_overruns == 0 && !(mode & IO_NONBLOCK))
		num_overruns = timerfd_waitfor(self);

	/* Handle the case of non-blocking, but not overrun, yet. */
	if (num_overruns == 0 && !(mode & IO_NODATAZERO))
		THROW(E_WOULDBLOCK); /* return -EAGAIN; */

	/* Write-back the # of overruns */
	UNALIGNED_SET64((USER CHECKED uint64_t *)dst, num_overruns);
	return 8;
}

INTERN BLOCKING NONNULL((1)) syscall_slong_t KCALL
handle_timerfd_ioctl(struct timerfd *__restrict self, ioctl_t cmd,
                     USER UNCHECKED void *arg, iomode_t mode) THROWS(...) {
	(void)mode;
	switch (cmd) {

	case TFD_IOC_SET_TICKS: {
		struct timespec now;
		uint64_t extra_ticks;
		validate_readable(arg, sizeof(uint64_t));
		extra_ticks = *(uint64_t const *)arg;
		COMPILER_READ_BARRIER();

		/* Consume all already-pending overruns, and set the extra-overrun counter. */
		now = timer_getclocknow(&self->tfd_timer);
		timer_write(&self->tfd_timer);
		timer_takeoverrun_locked(&self->tfd_timer, &now);
		self->tfd_xover = extra_ticks;
		timer_endwrite(&self->tfd_timer);
	}	break;

	default:
		THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND,
		      E_INVALID_ARGUMENT_CONTEXT_IOCTL_COMMAND,
		      cmd);
		break;
	}
	return 0;
}

INTERN BLOCKING NONNULL((1)) void KCALL
handle_timerfd_stat(struct timerfd *__restrict self,
                    USER CHECKED struct stat *result) THROWS(...) {
	struct timespec now;
	struct timespec next_expire;
	now = timer_getclocknow(&self->tfd_timer);
	timer_read(&self->tfd_timer);
	next_expire = timer_getnextexpire_locked(&self->tfd_timer, &now);
	timer_endread(&self->tfd_timer);

	bzero(result, sizeof(*result));
	result->st_size         = 8;
	result->st_atim.tv_sec  = (typeof(result->st_atim.tv_sec))next_expire.tv_sec;
	result->st_atim.tv_nsec = (typeof(result->st_atim.tv_nsec))next_expire.tv_nsec;
	result->st_mtim.tv_sec  = (typeof(result->st_mtim.tv_sec))next_expire.tv_sec;
	result->st_mtim.tv_nsec = (typeof(result->st_mtim.tv_nsec))next_expire.tv_nsec;
	result->st_ctim.tv_sec  = (typeof(result->st_ctim.tv_sec))next_expire.tv_sec;
	result->st_ctim.tv_nsec = (typeof(result->st_ctim.tv_nsec))next_expire.tv_nsec;
	result->st_btim.tv_sec  = (typeof(result->st_btim.tv_sec))next_expire.tv_sec;
	result->st_btim.tv_nsec = (typeof(result->st_btim.tv_nsec))next_expire.tv_nsec;
}

INTERN BLOCKING NONNULL((1)) void KCALL
handle_timerfd_pollconnect(struct timerfd *__restrict self,
                           poll_mode_t what) THROWS(...) {
	if (what & POLLINMASK) {
		task_connect(&self->tfd_elapse);
		if (!timerfd_haselapsed(self))
			timerfd_start_async_timeout_notifier(self);
	}
}

INTERN BLOCKING WUNUSED NONNULL((1)) poll_mode_t KCALL
handle_timerfd_polltest(struct timerfd *__restrict self,
                        poll_mode_t what) THROWS(...) {
	if (what & POLLINMASK) {
		if (timerfd_haselapsed(self))
			return what & POLLINMASK;
	}
	return 0;
}




/************************************************************************/
/* PROCESS TIMER CONTROL                                                */
/************************************************************************/

PRIVATE ATTR_RETNONNULL WUNUSED struct proctimerctl *FCALL
proctimerctl_new(void) THROWS(E_BADALLOC) {
	struct proctimerctl *result;
	result = _proctimerctl_alloc();
	/* TODO: init */
	return result;
}

/* Get or (lazily) allocate the process timer controller of `self' */
PUBLIC ATTR_RETNONNULL WUNUSED NONNULL((1)) struct proctimerctl *FCALL
procctl_reqtimerctl(struct procctl *__restrict self) THROWS(E_BADALLOC) {
	struct proctimerctl *result;
	result = procctl_gettimerctl(self);
	if (result == NULL) {
		result = proctimerctl_new();
		if unlikely(!ATOMIC_CMPXCH(self->pc_timers, NULL, result)) {
			proctimerctl_destroy(result);
			result = procctl_gettimerctl(self);
			assert(result != NULL);
		}
	}
	return result;
}






/************************************************************************/
/* SYSTEM CALLS                                                         */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_TIMERFD_CREATE
DEFINE_SYSCALL2(fd_t, timerfd_create,
                clockid_t, clock_id, syscall_ulong_t, flags) {
	iomode_t mode;
	fd_t result;
	REF struct timerfd *tfd;
	struct handle_install_data install;
	VALIDATE_FLAGSET(flags, TFD_NONBLOCK | TFD_CLOEXEC | TFD_CLOFORK,
	                 E_INVALID_ARGUMENT_CONTEXT_TIMERFD_CREATE_FLAGS);
	result = handles_install_begin(&install);
	TRY {
		tfd = timerfd_create(clock_id);
	} EXCEPT {
		handles_install_rollback(&install);
		RETHROW();
	}

	mode = IO_RDONLY; /* Write-access would just throw `E_FSERROR_UNSUPPORTED_OPERATION' regardlessly... */
	if (flags & TFD_NONBLOCK)
		mode |= IO_NONBLOCK;
	if (flags & TFD_CLOEXEC)
		mode |= IO_CLOEXEC;
	if (flags & TFD_CLOFORK)
		mode |= IO_CLOFORK;
	handles_install_commit_inherit(&install, tfd, mode);
	return result;
}
#endif /* __ARCH_WANT_SYSCALL_TIMERFD_CREATE */

#ifdef __ARCH_WANT_SYSCALL_TIMERFD_SETTIME
DEFINE_SYSCALL4(errno_t, timerfd_settime,
                fd_t, fd, syscall_ulong_t, flags,
                USER UNCHECKED struct itimerspec32 const *, p_new_config,
                USER UNCHECKED struct itimerspec32 *, p_old_config) {
	struct itimerspec new_config, old_config;
	REF struct timerfd *self = handles_lookuptimerfd(fd);
	FINALLY_DECREF_UNLIKELY(self);
	VALIDATE_FLAGSET(flags, TFD_TIMER_ABSTIME | TFD_TIMER_CANCEL_ON_SET,
	                 E_INVALID_ARGUMENT_CONTEXT_TIMERFD_SETTIME_FLAGS);
	validate_readable_opt(p_new_config, sizeof(*p_new_config));
	validate_writable_opt(p_old_config, sizeof(*p_old_config));
	if (p_new_config) {
		new_config.it_value.tv_sec     = (typeof(new_config.it_value.tv_sec))p_new_config->it_value.tv_sec;
		new_config.it_value.tv_nsec    = (typeof(new_config.it_value.tv_nsec))p_new_config->it_value.tv_nsec;
		new_config.it_interval.tv_sec  = (typeof(new_config.it_interval.tv_sec))p_new_config->it_interval.tv_sec;
		new_config.it_interval.tv_nsec = (typeof(new_config.it_interval.tv_nsec))p_new_config->it_interval.tv_nsec;
		if (!(flags & TFD_TIMER_ABSTIME)) {
			COMPILER_READ_BARRIER();
			if (new_config.it_value.tv_sec != 0 || new_config.it_value.tv_nsec != 0)
				new_config.it_value += timer_getclocknow(&self->tfd_timer);
		}
	}

	timerfd_settime(self,
	                p_new_config ? &new_config : NULL,
	                p_old_config ? &old_config : NULL);

	if (p_old_config) {
		p_old_config->it_value.tv_sec     = (typeof(p_old_config->it_value.tv_sec))old_config.it_value.tv_sec;
		p_old_config->it_value.tv_nsec    = (typeof(p_old_config->it_value.tv_nsec))old_config.it_value.tv_nsec;
		p_old_config->it_interval.tv_sec  = (typeof(p_old_config->it_interval.tv_sec))old_config.it_interval.tv_sec;
		p_old_config->it_interval.tv_nsec = (typeof(p_old_config->it_interval.tv_nsec))old_config.it_interval.tv_nsec;
	}
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_TIMERFD_SETTIME */

#ifdef __ARCH_WANT_SYSCALL_TIMERFD_SETTIME64
DEFINE_SYSCALL4(errno_t, timerfd_settime64,
                fd_t, fd, syscall_ulong_t, flags,
                USER UNCHECKED struct itimerspec64 const *, p_new_config,
                USER UNCHECKED struct itimerspec64 *, p_old_config) {
	struct itimerspec new_config, old_config;
	REF struct timerfd *self = handles_lookuptimerfd(fd);
	FINALLY_DECREF_UNLIKELY(self);
	VALIDATE_FLAGSET(flags, TFD_TIMER_ABSTIME | TFD_TIMER_CANCEL_ON_SET,
	                 E_INVALID_ARGUMENT_CONTEXT_TIMERFD_SETTIME_FLAGS);
	validate_readable_opt(p_new_config, sizeof(*p_new_config));
	validate_writable_opt(p_old_config, sizeof(*p_old_config));
	if (p_new_config) {
		new_config.it_value.tv_sec     = (typeof(new_config.it_value.tv_sec))p_new_config->it_value.tv_sec;
		new_config.it_value.tv_nsec    = (typeof(new_config.it_value.tv_nsec))p_new_config->it_value.tv_nsec;
		new_config.it_interval.tv_sec  = (typeof(new_config.it_interval.tv_sec))p_new_config->it_interval.tv_sec;
		new_config.it_interval.tv_nsec = (typeof(new_config.it_interval.tv_nsec))p_new_config->it_interval.tv_nsec;
		if (!(flags & TFD_TIMER_ABSTIME)) {
			COMPILER_READ_BARRIER();
			if (new_config.it_value.tv_sec != 0 || new_config.it_value.tv_nsec != 0)
				new_config.it_value += timer_getclocknow(&self->tfd_timer);
		}
	}

	timerfd_settime(self,
	                p_new_config ? &new_config : NULL,
	                p_old_config ? &old_config : NULL);

	if (p_old_config) {
		p_old_config->it_value.tv_sec     = (typeof(p_old_config->it_value.tv_sec))old_config.it_value.tv_sec;
		p_old_config->it_value.tv_nsec    = (typeof(p_old_config->it_value.tv_nsec))old_config.it_value.tv_nsec;
		p_old_config->it_interval.tv_sec  = (typeof(p_old_config->it_interval.tv_sec))old_config.it_interval.tv_sec;
		p_old_config->it_interval.tv_nsec = (typeof(p_old_config->it_interval.tv_nsec))old_config.it_interval.tv_nsec;
	}
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_TIMERFD_SETTIME64 */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_TIMERFD_SETTIME
DEFINE_COMPAT_SYSCALL4(errno_t, timerfd_settime,
                       fd_t, fd, syscall_ulong_t, flags,
                       USER UNCHECKED struct compat_itimerspec32 const *, p_new_config,
                       USER UNCHECKED struct compat_itimerspec32 *, p_old_config) {
	struct itimerspec new_config, old_config;
	REF struct timerfd *self = handles_lookuptimerfd(fd);
	FINALLY_DECREF_UNLIKELY(self);
	VALIDATE_FLAGSET(flags, TFD_TIMER_ABSTIME | TFD_TIMER_CANCEL_ON_SET,
	                 E_INVALID_ARGUMENT_CONTEXT_TIMERFD_SETTIME_FLAGS);
	compat_validate_readable_opt(p_new_config, sizeof(*p_new_config));
	compat_validate_writable_opt(p_old_config, sizeof(*p_old_config));
	if (p_new_config) {
		new_config.it_value.tv_sec     = (typeof(new_config.it_value.tv_sec))p_new_config->it_value.tv_sec;
		new_config.it_value.tv_nsec    = (typeof(new_config.it_value.tv_nsec))p_new_config->it_value.tv_nsec;
		new_config.it_interval.tv_sec  = (typeof(new_config.it_interval.tv_sec))p_new_config->it_interval.tv_sec;
		new_config.it_interval.tv_nsec = (typeof(new_config.it_interval.tv_nsec))p_new_config->it_interval.tv_nsec;
		if (!(flags & TFD_TIMER_ABSTIME)) {
			COMPILER_READ_BARRIER();
			if (new_config.it_value.tv_sec != 0 || new_config.it_value.tv_nsec != 0)
				new_config.it_value += timer_getclocknow(&self->tfd_timer);
		}
	}

	timerfd_settime(self,
	                p_new_config ? &new_config : NULL,
	                p_old_config ? &old_config : NULL);

	if (p_old_config) {
		p_old_config->it_value.tv_sec     = (typeof(p_old_config->it_value.tv_sec))old_config.it_value.tv_sec;
		p_old_config->it_value.tv_nsec    = (typeof(p_old_config->it_value.tv_nsec))old_config.it_value.tv_nsec;
		p_old_config->it_interval.tv_sec  = (typeof(p_old_config->it_interval.tv_sec))old_config.it_interval.tv_sec;
		p_old_config->it_interval.tv_nsec = (typeof(p_old_config->it_interval.tv_nsec))old_config.it_interval.tv_nsec;
	}
	return -EOK;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_TIMERFD_SETTIME */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_TIMERFD_SETTIME64
DEFINE_COMPAT_SYSCALL4(errno_t, timerfd_settime64,
                       fd_t, fd, syscall_ulong_t, flags,
                       USER UNCHECKED struct compat_itimerspec64 const *, p_new_config,
                       USER UNCHECKED struct compat_itimerspec64 *, p_old_config) {
	struct itimerspec new_config, old_config;
	REF struct timerfd *self = handles_lookuptimerfd(fd);
	FINALLY_DECREF_UNLIKELY(self);
	VALIDATE_FLAGSET(flags, TFD_TIMER_ABSTIME | TFD_TIMER_CANCEL_ON_SET,
	                 E_INVALID_ARGUMENT_CONTEXT_TIMERFD_SETTIME_FLAGS);
	compat_validate_readable_opt(p_new_config, sizeof(*p_new_config));
	compat_validate_writable_opt(p_old_config, sizeof(*p_old_config));
	if (p_new_config) {
		new_config.it_value.tv_sec     = (typeof(new_config.it_value.tv_sec))p_new_config->it_value.tv_sec;
		new_config.it_value.tv_nsec    = (typeof(new_config.it_value.tv_nsec))p_new_config->it_value.tv_nsec;
		new_config.it_interval.tv_sec  = (typeof(new_config.it_interval.tv_sec))p_new_config->it_interval.tv_sec;
		new_config.it_interval.tv_nsec = (typeof(new_config.it_interval.tv_nsec))p_new_config->it_interval.tv_nsec;
		if (!(flags & TFD_TIMER_ABSTIME)) {
			COMPILER_READ_BARRIER();
			if (new_config.it_value.tv_sec != 0 || new_config.it_value.tv_nsec != 0)
				new_config.it_value += timer_getclocknow(&self->tfd_timer);
		}
	}

	timerfd_settime(self,
	                p_new_config ? &new_config : NULL,
	                p_old_config ? &old_config : NULL);

	if (p_old_config) {
		p_old_config->it_value.tv_sec     = (typeof(p_old_config->it_value.tv_sec))old_config.it_value.tv_sec;
		p_old_config->it_value.tv_nsec    = (typeof(p_old_config->it_value.tv_nsec))old_config.it_value.tv_nsec;
		p_old_config->it_interval.tv_sec  = (typeof(p_old_config->it_interval.tv_sec))old_config.it_interval.tv_sec;
		p_old_config->it_interval.tv_nsec = (typeof(p_old_config->it_interval.tv_nsec))old_config.it_interval.tv_nsec;
	}
	return -EOK;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_TIMERFD_SETTIME64 */

#ifdef __ARCH_WANT_SYSCALL_TIMERFD_GETTIME
DEFINE_SYSCALL2(errno_t, timerfd_gettime,
                fd_t, fd, USER UNCHECKED struct itimerspec32 *, p_config) {
	struct itimerspec config;
	REF struct timerfd *self = handles_lookuptimerfd(fd);
	FINALLY_DECREF_UNLIKELY(self);
	validate_writable_opt(p_config, sizeof(*p_config));
	config = timerfd_gettime(self);

	p_config->it_value.tv_sec     = (typeof(p_config->it_value.tv_sec))config.it_value.tv_sec;
	p_config->it_value.tv_nsec    = (typeof(p_config->it_value.tv_nsec))config.it_value.tv_nsec;
	p_config->it_interval.tv_sec  = (typeof(p_config->it_interval.tv_sec))config.it_interval.tv_sec;
	p_config->it_interval.tv_nsec = (typeof(p_config->it_interval.tv_nsec))config.it_interval.tv_nsec;
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_TIMERFD_GETTIME */

#ifdef __ARCH_WANT_SYSCALL_TIMERFD_GETTIME64
DEFINE_SYSCALL2(errno_t, timerfd_gettime64,
                fd_t, fd, USER UNCHECKED struct itimerspec64 *, p_config) {
	struct itimerspec config;
	REF struct timerfd *self = handles_lookuptimerfd(fd);
	FINALLY_DECREF_UNLIKELY(self);
	validate_writable_opt(p_config, sizeof(*p_config));
	config = timerfd_gettime(self);

	p_config->it_value.tv_sec     = (typeof(p_config->it_value.tv_sec))config.it_value.tv_sec;
	p_config->it_value.tv_nsec    = (typeof(p_config->it_value.tv_nsec))config.it_value.tv_nsec;
	p_config->it_interval.tv_sec  = (typeof(p_config->it_interval.tv_sec))config.it_interval.tv_sec;
	p_config->it_interval.tv_nsec = (typeof(p_config->it_interval.tv_nsec))config.it_interval.tv_nsec;
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_TIMERFD_GETTIME64 */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_TIMERFD_GETTIME
DEFINE_COMPAT_SYSCALL2(errno_t, timerfd_gettime,
                       fd_t, fd, USER UNCHECKED struct compat_itimerspec32 *, p_config) {
	struct itimerspec config;
	REF struct timerfd *self = handles_lookuptimerfd(fd);
	FINALLY_DECREF_UNLIKELY(self);
	compat_validate_writable_opt(p_config, sizeof(*p_config));
	config = timerfd_gettime(self);

	p_config->it_value.tv_sec     = (typeof(p_config->it_value.tv_sec))config.it_value.tv_sec;
	p_config->it_value.tv_nsec    = (typeof(p_config->it_value.tv_nsec))config.it_value.tv_nsec;
	p_config->it_interval.tv_sec  = (typeof(p_config->it_interval.tv_sec))config.it_interval.tv_sec;
	p_config->it_interval.tv_nsec = (typeof(p_config->it_interval.tv_nsec))config.it_interval.tv_nsec;
	return -EOK;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_TIMERFD_GETTIME */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_TIMERFD_GETTIME64
DEFINE_COMPAT_SYSCALL2(errno_t, timerfd_gettime64,
                       fd_t, fd, USER UNCHECKED struct compat_itimerspec64 *, p_config) {
	struct itimerspec config;
	REF struct timerfd *self = handles_lookuptimerfd(fd);
	FINALLY_DECREF_UNLIKELY(self);
	compat_validate_writable_opt(p_config, sizeof(*p_config));
	config = timerfd_gettime(self);

	p_config->it_value.tv_sec     = (typeof(p_config->it_value.tv_sec))config.it_value.tv_sec;
	p_config->it_value.tv_nsec    = (typeof(p_config->it_value.tv_nsec))config.it_value.tv_nsec;
	p_config->it_interval.tv_sec  = (typeof(p_config->it_interval.tv_sec))config.it_interval.tv_sec;
	p_config->it_interval.tv_nsec = (typeof(p_config->it_interval.tv_nsec))config.it_interval.tv_nsec;
	return -EOK;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_TIMERFD_GETTIME64 */





/************************************************************************/
/* clock_gettime(2), clock_getres(2)                                    */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_CLOCK_GETTIME
DEFINE_SYSCALL2(errno_t, clock_gettime,
                clockid_t, clockid,
                USER UNCHECKED struct timespec32 *, res) {
	struct timespec ts;
	struct clocktype const *ct;
	validate_writable(res, sizeof(*res));
	ct = clock_lookup(clockid);
	ts = (*ct->ct_gettime)(clockid);
	COMPILER_WRITE_BARRIER();
	res->tv_sec  = (typeof(res->tv_sec))ts.tv_sec;
	res->tv_nsec = (typeof(res->tv_nsec))ts.tv_nsec;
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_CLOCK_GETTIME */

#ifdef __ARCH_WANT_SYSCALL_CLOCK_GETTIME_TIME64
DEFINE_SYSCALL2(errno_t, clock_gettime_time64,
                clockid_t, clockid,
                USER UNCHECKED struct timespec64 *, res) {
	struct timespec ts;
	struct clocktype const *ct;
	validate_writable(res, sizeof(*res));
	ct = clock_lookup(clockid);
	ts = (*ct->ct_gettime)(clockid);
	COMPILER_WRITE_BARRIER();
	res->tv_sec  = (typeof(res->tv_sec))ts.tv_sec;
	res->tv_nsec = (typeof(res->tv_nsec))ts.tv_nsec;
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_CLOCK_GETTIME_TIME64 */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_CLOCK_GETTIME
DEFINE_COMPAT_SYSCALL2(errno_t, clock_gettime,
                       clockid_t, clockid,
                       USER UNCHECKED struct compat_timespec32 *, res) {
	struct timespec ts;
	struct clocktype const *ct;
	compat_validate_writable(res, sizeof(*res));
	ct = clock_lookup(clockid);
	ts = (*ct->ct_gettime)(clockid);
	COMPILER_WRITE_BARRIER();
	res->tv_sec  = (typeof(res->tv_sec))ts.tv_sec;
	res->tv_nsec = (typeof(res->tv_nsec))ts.tv_nsec;
	return -EOK;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_CLOCK_GETTIME */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_CLOCK_GETTIME_TIME64
DEFINE_COMPAT_SYSCALL2(errno_t, clock_gettime_time64,
                       clockid_t, clockid,
                       USER UNCHECKED struct compat_timespec64 *, res) {
	struct timespec ts;
	struct clocktype const *ct;
	compat_validate_writable(res, sizeof(*res));
	ct = clock_lookup(clockid);
	ts = (*ct->ct_gettime)(clockid);
	COMPILER_WRITE_BARRIER();
	res->tv_sec  = (typeof(res->tv_sec))ts.tv_sec;
	res->tv_nsec = (typeof(res->tv_nsec))ts.tv_nsec;
	return -EOK;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_CLOCK_GETTIME_TIME64 */

#ifdef __ARCH_WANT_SYSCALL_CLOCK_GETRES
DEFINE_SYSCALL2(errno_t, clock_getres,
                clockid_t, clockid,
                USER UNCHECKED struct timespec32 *, res) {
	struct timespec ts;
	struct clocktype const *ct;
	validate_writable(res, sizeof(*res));
	ct = clock_lookup(clockid);
	ts = (*ct->ct_getres)(clockid);
	COMPILER_WRITE_BARRIER();
	res->tv_sec  = (typeof(res->tv_sec))ts.tv_sec;
	res->tv_nsec = (typeof(res->tv_nsec))ts.tv_nsec;
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_CLOCK_GETRES */

#ifdef __ARCH_WANT_SYSCALL_CLOCK_GETRES_TIME64
DEFINE_SYSCALL2(errno_t, clock_getres_time64,
                clockid_t, clockid,
                USER UNCHECKED struct timespec64 *, res) {
	struct timespec ts;
	struct clocktype const *ct;
	validate_writable(res, sizeof(*res));
	ct = clock_lookup(clockid);
	ts = (*ct->ct_getres)(clockid);
	COMPILER_WRITE_BARRIER();
	res->tv_sec  = (typeof(res->tv_sec))ts.tv_sec;
	res->tv_nsec = (typeof(res->tv_nsec))ts.tv_nsec;
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_CLOCK_GETRES_TIME64 */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_CLOCK_GETRES
DEFINE_COMPAT_SYSCALL2(errno_t, clock_getres,
                       clockid_t, clockid,
                       USER UNCHECKED struct compat_timespec32 *, res) {
	struct timespec ts;
	struct clocktype const *ct;
	compat_validate_writable(res, sizeof(*res));
	ct = clock_lookup(clockid);
	ts = (*ct->ct_getres)(clockid);
	COMPILER_WRITE_BARRIER();
	res->tv_sec  = (typeof(res->tv_sec))ts.tv_sec;
	res->tv_nsec = (typeof(res->tv_nsec))ts.tv_nsec;
	return -EOK;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_CLOCK_GETRES */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_CLOCK_GETRES_TIME64
DEFINE_COMPAT_SYSCALL2(errno_t, clock_getres_time64,
                       clockid_t, clockid,
                       USER UNCHECKED struct compat_timespec64 *, res) {
	struct timespec ts;
	struct clocktype const *ct;
	compat_validate_writable(res, sizeof(*res));
	ct = clock_lookup(clockid);
	ts = (*ct->ct_getres)(clockid);
	COMPILER_WRITE_BARRIER();
	res->tv_sec  = (typeof(res->tv_sec))ts.tv_sec;
	res->tv_nsec = (typeof(res->tv_nsec))ts.tv_nsec;
	return -EOK;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_CLOCK_GETRES_TIME64 */




/************************************************************************/
/* clock_nanosleep(2)                                                   */
/************************************************************************/
#if (defined(__ARCH_WANT_SYSCALL_CLOCK_NANOSLEEP) ||        \
     defined(__ARCH_WANT_SYSCALL_CLOCK_NANOSLEEP_TIME64) || \
     defined(__ARCH_WANT_COMPAT_SYSCALL_CLOCK_NANOSLEEP) || \
     defined(__ARCH_WANT_COMPAT_SYSCALL_CLOCK_NANOSLEEP_TIME64))
typedef NONNULL((1, 2)) void
(FCALL *PCLOCK_NANOSLEEP_WRITE_REMAINING)(void *arg, struct timespec const *__restrict remaining)
		THROWS(...);

PRIVATE NONNULL((3, 4)) errno_t KCALL
sys_clock_nanosleep_impl(clockid_t clockid, syscall_ulong_t flags,
                         struct timespec *__restrict requested_time,
                         PCLOCK_NANOSLEEP_WRITE_REMAINING write_remaining,
                         void *write_remaining_arg) {
	struct timespec now;
	ktime_t timeout;
	struct clocktype const *ct;
	/* Calculate timeout. */
	VALIDATE_FLAGSET(flags, 0 | TIMER_ABSTIME,
	                 E_INVALID_ARGUMENT_CONTEXT_TIMER_FLAGS);
	ct = clock_lookup(clockid);
	if (!(flags & TIMER_ABSTIME))
		*requested_time += (*ct->ct_gettime)(clockid);
	TRY {
again_maketimeout:
		timeout = (*ct->ct_astimeout)(clockid, requested_time);
again_waitfor:
		PREEMPTION_DISABLE();
		/* Service RPC functions */
		if (task_serve())
			goto again_waitfor;
		if (task_sleep(timeout))
			goto again_waitfor;

		/* Timeout -> check if actually timed out */
		now = (*ct->ct_gettime)(clockid);
		if (now < *requested_time)
			goto again_maketimeout;
	} EXCEPT {
		if ((write_remaining_arg != NULL) &&
		    (flags & TIMER_ABSTIME) == 0 &&
		    (was_thrown(E_INTERRUPT_USER_RPC))) {
			struct timespec remaining;
			/* Write back the remaining time to user-space.
			 * NOTE: If `rem'  is  a  faulty pointer,  it  is  undefined  what
			 *       will  happen  to  that E_SEGFAULT  exception,  however it
			 *       is guarantied that an E_INTERRUPT caused by a  user-space
			 *       RPC or POSIX signal will invoke the RPC/signal's handler! */
			NESTED_EXCEPTION;
			now = (*ct->ct_gettime)(clockid);
			remaining = *requested_time;
			if (now >= *requested_time) {
				/* Prevent overflow:
				 * > indicate that no  sleep-time remains,  but
				 *   there still was an interrupt non-the-less. */
				remaining.tv_sec  = 0;
				remaining.tv_nsec = 0;
			} else {
				remaining = *requested_time - now;
			}
			(*write_remaining)(write_remaining_arg, &remaining);
		}
		RETHROW();
	}
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_CLOCK_NANOSLEEP... */

#ifdef __ARCH_WANT_SYSCALL_CLOCK_NANOSLEEP
PRIVATE NONNULL((1, 2)) void FCALL
sys_clock_nanosleep_encode_remaining(void *arg, struct timespec const *__restrict remaining) {
	USER CHECKED struct timespec32 *res;
	res = (USER CHECKED struct timespec32 *)arg;
	res->tv_sec  = (typeof(res->tv_sec))remaining->tv_sec;
	res->tv_nsec = (typeof(res->tv_nsec))remaining->tv_nsec;
}

DEFINE_SYSCALL4(errno_t, clock_nanosleep,
                clockid_t, clockid, syscall_ulong_t, flags,
                USER UNCHECKED struct timespec32 const *, requested_time,
                USER UNCHECKED struct timespec32 *, remaining) {
	struct timespec req;
	validate_readable(requested_time, sizeof(*requested_time));
	validate_writable_opt(remaining, sizeof(*remaining));
	req.tv_sec  = (typeof(req.tv_sec))requested_time->tv_sec;
	req.tv_nsec = (typeof(req.tv_nsec))requested_time->tv_nsec;
	COMPILER_READ_BARRIER();
	return sys_clock_nanosleep_impl(clockid, flags, &req,
	                                &sys_clock_nanosleep_encode_remaining,
	                                remaining);
}
#endif /* __ARCH_WANT_SYSCALL_CLOCK_NANOSLEEP */

#ifdef __ARCH_WANT_SYSCALL_CLOCK_NANOSLEEP_TIME64
PRIVATE NONNULL((1, 2)) void FCALL
sys_clock_nanosleep_time64_encode_remaining(void *arg, struct timespec const *__restrict remaining) {
	USER CHECKED struct timespec64 *res;
	res = (USER CHECKED struct timespec64 *)arg;
	res->tv_sec  = (typeof(res->tv_sec))remaining->tv_sec;
	res->tv_nsec = (typeof(res->tv_nsec))remaining->tv_nsec;
}

DEFINE_SYSCALL4(errno_t, clock_nanosleep_time64,
                clockid_t, clockid, syscall_ulong_t, flags,
                USER UNCHECKED struct timespec64 const *, requested_time,
                USER UNCHECKED struct timespec64 *, remaining) {
	struct timespec req;
	validate_readable(requested_time, sizeof(*requested_time));
	validate_writable_opt(remaining, sizeof(*remaining));
	req.tv_sec  = (typeof(req.tv_sec))requested_time->tv_sec;
	req.tv_nsec = (typeof(req.tv_nsec))requested_time->tv_nsec;
	COMPILER_READ_BARRIER();
	return sys_clock_nanosleep_impl(clockid, flags, &req,
	                                &sys_clock_nanosleep_time64_encode_remaining,
	                                remaining);
}
#endif /* __ARCH_WANT_SYSCALL_CLOCK_NANOSLEEP_TIME64 */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_CLOCK_NANOSLEEP
PRIVATE NONNULL((1, 2)) void FCALL
sys_clock_nanosleep_compat_encode_remaining(void *arg, struct timespec const *__restrict remaining) {
	USER CHECKED struct compat_timespec32 *res;
	res = (USER CHECKED struct compat_timespec32 *)arg;
	res->tv_sec  = (typeof(res->tv_sec))remaining->tv_sec;
	res->tv_nsec = (typeof(res->tv_nsec))remaining->tv_nsec;
}

DEFINE_COMPAT_SYSCALL4(errno_t, clock_nanosleep,
                       clockid_t, clockid, syscall_ulong_t, flags,
                       USER UNCHECKED struct compat_timespec32 const *, requested_time,
                       USER UNCHECKED struct compat_timespec32 *, remaining) {
	struct timespec req;
	compat_validate_readable(requested_time, sizeof(*requested_time));
	compat_validate_writable_opt(remaining, sizeof(*remaining));
	req.tv_sec  = (typeof(req.tv_sec))requested_time->tv_sec;
	req.tv_nsec = (typeof(req.tv_nsec))requested_time->tv_nsec;
	COMPILER_READ_BARRIER();
	return sys_clock_nanosleep_impl(clockid, flags, &req,
	                                &sys_clock_nanosleep_compat_encode_remaining,
	                                remaining);
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_CLOCK_NANOSLEEP */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_CLOCK_NANOSLEEP_TIME64
PRIVATE NONNULL((1, 2)) void FCALL
sys_clock_nanosleep_time64_compat_encode_remaining(void *arg, struct timespec const *__restrict remaining) {
	USER CHECKED struct compat_timespec64 *res;
	res = (USER CHECKED struct compat_timespec64 *)arg;
	res->tv_sec  = (typeof(res->tv_sec))remaining->tv_sec;
	res->tv_nsec = (typeof(res->tv_nsec))remaining->tv_nsec;
}

DEFINE_COMPAT_SYSCALL4(errno_t, clock_nanosleep_time64,
                       clockid_t, clockid, syscall_ulong_t, flags,
                       USER UNCHECKED struct compat_timespec64 const *, requested_time,
                       USER UNCHECKED struct compat_timespec64 *, remaining) {
	struct timespec req;
	compat_validate_readable(requested_time, sizeof(*requested_time));
	compat_validate_writable_opt(remaining, sizeof(*remaining));
	req.tv_sec  = (typeof(req.tv_sec))requested_time->tv_sec;
	req.tv_nsec = (typeof(req.tv_nsec))requested_time->tv_nsec;
	COMPILER_READ_BARRIER();
	return sys_clock_nanosleep_impl(clockid, flags, &req,
	                                &sys_clock_nanosleep_time64_compat_encode_remaining,
	                                remaining);
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_CLOCK_NANOSLEEP_TIME64 */

DECL_END

#endif /* !GUARD_KERNEL_SRC_SCHED_TIMER_C */
