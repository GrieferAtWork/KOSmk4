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
#ifndef GUARD_KERNEL_INCLUDE_SCHED_TIMER_H
#define GUARD_KERNEL_INCLUDE_SCHED_TIMER_H 1

#include <kernel/compiler.h>

#include <kernel/types.h>

#include <hybrid/__assert.h>
#include <hybrid/sched/atomic-rwlock.h>

#include <asm/os/clock.h>
#include <bits/os/itimerspec.h>
#include <bits/os/timespec.h>

/* Stuff needed for:
 * - alarm(2)
 * - clock_settime(2)
 * - clock_gettime(2)
 * - clock_getres(2)
 * - clock_nanosleep(2)
 * - timer_create(2)
 * - timer_delete(2)
 * - timer_getoverrun(2)
 * - timer_gettime(2)
 * - timer_settime(2)
 * - timerfd_create(2)
 * - timerfd_gettime(2)
 * - timerfd_settime(2)
 */

#if !defined(CLOCK_REALTIME) && defined(__CLOCK_REALTIME)
#define CLOCK_REALTIME           __CLOCK_REALTIME           /* [rw] Realtime (wall) clock, in UTC (also used by `time(2)' and `gettimeofday(2)') */
#endif /* !CLOCK_REALTIME && __CLOCK_REALTIME */
#if !defined(CLOCK_MONOTONIC) && defined(__CLOCK_MONOTONIC)
#define CLOCK_MONOTONIC          __CLOCK_MONOTONIC          /* [ro] Time since system was booted (unaffected by system
                                                             * time  changes)  Paused while  the system  is suspended. */
#endif /* !CLOCK_MONOTONIC && __CLOCK_MONOTONIC */
#if !defined(CLOCK_PROCESS_CPUTIME_ID) && defined(__CLOCK_PROCESS_CPUTIME_ID)
#define CLOCK_PROCESS_CPUTIME_ID __CLOCK_PROCESS_CPUTIME_ID /* [ro] Sum of CPU time consumed by all threads in calling process */
#endif /* !CLOCK_PROCESS_CPUTIME_ID && __CLOCK_PROCESS_CPUTIME_ID */
#if !defined(CLOCK_THREAD_CPUTIME_ID) && defined(__CLOCK_THREAD_CPUTIME_ID)
#define CLOCK_THREAD_CPUTIME_ID  __CLOCK_THREAD_CPUTIME_ID  /* [ro] Sum of CPU time consumed by calling thread */
#endif /* !CLOCK_THREAD_CPUTIME_ID && __CLOCK_THREAD_CPUTIME_ID */
#if !defined(CLOCK_MONOTONIC_RAW) && defined(__CLOCK_MONOTONIC_RAW)
#define CLOCK_MONOTONIC_RAW      __CLOCK_MONOTONIC_RAW      /* [ro] Raw,  hardware time since  system was started (stopped
                                                             * while system is suspended), and unaffected by anything done
                                                             * by `adjtime(3)' */
#endif /* !CLOCK_MONOTONIC_RAW && __CLOCK_MONOTONIC_RAW */
#if !defined(CLOCK_REALTIME_COARSE) && defined(__CLOCK_REALTIME_COARSE)
#define CLOCK_REALTIME_COARSE    __CLOCK_REALTIME_COARSE    /* [ro] Same as `CLOCK_REALTIME', but may be less precise, yet faster to query. */
#endif /* !CLOCK_REALTIME_COARSE && __CLOCK_REALTIME_COARSE */
#if !defined(CLOCK_MONOTONIC_COARSE) && defined(__CLOCK_MONOTONIC_COARSE)
#define CLOCK_MONOTONIC_COARSE   __CLOCK_MONOTONIC_COARSE   /* [ro] Same as `CLOCK_MONOTONIC', but may be less precise, yet faster to query. */
#endif /* !CLOCK_MONOTONIC_COARSE && __CLOCK_MONOTONIC_COARSE */
#if !defined(CLOCK_BOOTTIME) && defined(__CLOCK_BOOTTIME)
#define CLOCK_BOOTTIME           __CLOCK_BOOTTIME           /* [ro] Same as `CLOCK_MONOTONIC', but includes time the system was suspended. */
#endif /* !CLOCK_BOOTTIME && __CLOCK_BOOTTIME */
#if !defined(CLOCK_REALTIME_ALARM) && defined(__CLOCK_REALTIME_ALARM)
#define CLOCK_REALTIME_ALARM     __CLOCK_REALTIME_ALARM     /* [ro] Like `CLOCK_REALTIME'. If used with `timer_create()', system will leave suspension when timer is triggered */
#endif /* !CLOCK_REALTIME_ALARM && __CLOCK_REALTIME_ALARM */
#if !defined(CLOCK_BOOTTIME_ALARM) && defined(__CLOCK_BOOTTIME_ALARM)
#define CLOCK_BOOTTIME_ALARM     __CLOCK_BOOTTIME_ALARM     /* [ro] Like `CLOCK_BOOTTIME'. If used with `timer_create()', system will leave suspension when timer is triggered */
#endif /* !CLOCK_BOOTTIME_ALARM && __CLOCK_BOOTTIME_ALARM */
#if !defined(CLOCK_TAI) && defined(__CLOCK_TAI)
#define CLOCK_TAI                __CLOCK_TAI                /* [ro] Time.Atomic.International -- Like `CLOCK_REALTIME', but isn't affected by leap seconds. */
#endif /* !CLOCK_TAI && __CLOCK_TAI */

/*[[[deemon
local clocks = {
	"CLOCK_REALTIME",
	"CLOCK_MONOTONIC",
	"CLOCK_PROCESS_CPUTIME_ID",
	"CLOCK_THREAD_CPUTIME_ID",
	"CLOCK_MONOTONIC_RAW",
	"CLOCK_REALTIME_COARSE",
	"CLOCK_MONOTONIC_COARSE",
	"CLOCK_BOOTTIME",
	"CLOCK_REALTIME_ALARM",
	"CLOCK_BOOTTIME_ALARM",
	"CLOCK_TAI",
};
print("#define CLOCK_COUNT 1");
for (local c: clocks) {
	print("#if ", c, " >= CLOCK_COUNT");
	print("#undef CLOCK_COUNT");
	print("#define CLOCK_COUNT (", c, " + 1)");
	print("#endif /" "* ", c, " >= CLOCK_COUNT *" "/");
}
]]]*/
#define CLOCK_COUNT 1
#if CLOCK_REALTIME >= CLOCK_COUNT
#undef CLOCK_COUNT
#define CLOCK_COUNT (CLOCK_REALTIME + 1)
#endif /* CLOCK_REALTIME >= CLOCK_COUNT */
#if CLOCK_MONOTONIC >= CLOCK_COUNT
#undef CLOCK_COUNT
#define CLOCK_COUNT (CLOCK_MONOTONIC + 1)
#endif /* CLOCK_MONOTONIC >= CLOCK_COUNT */
#if CLOCK_PROCESS_CPUTIME_ID >= CLOCK_COUNT
#undef CLOCK_COUNT
#define CLOCK_COUNT (CLOCK_PROCESS_CPUTIME_ID + 1)
#endif /* CLOCK_PROCESS_CPUTIME_ID >= CLOCK_COUNT */
#if CLOCK_THREAD_CPUTIME_ID >= CLOCK_COUNT
#undef CLOCK_COUNT
#define CLOCK_COUNT (CLOCK_THREAD_CPUTIME_ID + 1)
#endif /* CLOCK_THREAD_CPUTIME_ID >= CLOCK_COUNT */
#if CLOCK_MONOTONIC_RAW >= CLOCK_COUNT
#undef CLOCK_COUNT
#define CLOCK_COUNT (CLOCK_MONOTONIC_RAW + 1)
#endif /* CLOCK_MONOTONIC_RAW >= CLOCK_COUNT */
#if CLOCK_REALTIME_COARSE >= CLOCK_COUNT
#undef CLOCK_COUNT
#define CLOCK_COUNT (CLOCK_REALTIME_COARSE + 1)
#endif /* CLOCK_REALTIME_COARSE >= CLOCK_COUNT */
#if CLOCK_MONOTONIC_COARSE >= CLOCK_COUNT
#undef CLOCK_COUNT
#define CLOCK_COUNT (CLOCK_MONOTONIC_COARSE + 1)
#endif /* CLOCK_MONOTONIC_COARSE >= CLOCK_COUNT */
#if CLOCK_BOOTTIME >= CLOCK_COUNT
#undef CLOCK_COUNT
#define CLOCK_COUNT (CLOCK_BOOTTIME + 1)
#endif /* CLOCK_BOOTTIME >= CLOCK_COUNT */
#if CLOCK_REALTIME_ALARM >= CLOCK_COUNT
#undef CLOCK_COUNT
#define CLOCK_COUNT (CLOCK_REALTIME_ALARM + 1)
#endif /* CLOCK_REALTIME_ALARM >= CLOCK_COUNT */
#if CLOCK_BOOTTIME_ALARM >= CLOCK_COUNT
#undef CLOCK_COUNT
#define CLOCK_COUNT (CLOCK_BOOTTIME_ALARM + 1)
#endif /* CLOCK_BOOTTIME_ALARM >= CLOCK_COUNT */
#if CLOCK_TAI >= CLOCK_COUNT
#undef CLOCK_COUNT
#define CLOCK_COUNT (CLOCK_TAI + 1)
#endif /* CLOCK_TAI >= CLOCK_COUNT */
/*[[[end]]]*/

#ifdef __CC__
DECL_BEGIN

struct clocktype {
	/* [1..1] Get the current time */
	WUNUSED_T struct timespec (FCALL *ct_gettime)(clockid_t clockid)
			THROWS(...);

	/* [1..1] Get the clock's resolution */
	WUNUSED_T struct timespec (FCALL *ct_getres)(clockid_t clockid)
			THROWS(...);

	/* [1..1]
	 * Convert a timestamp `p_ts' valued in the context of the clock's
	 * notion of time,  into the most  conservative representation  of
	 * time as understood by the scheduler.
	 *
	 * This function should  be used  to calculate a  timeout for  the
	 * earliest possible point in time when `(*ct_gettime)() >= *p_ts' */
	WUNUSED_T ktime_t (FCALL *ct_astimeout)(clockid_t clockid, USER CHECKED struct timespec const *p_ts)
			THROWS(...);

	/* [1..1]
	 * Connect the calling thread to signals that may be broadcast
	 * when the relation  between this clock  and the  ktime-clock
	 * changes  (i.e. the clock  time is changed,  or the speed at
	 * which this clock runs changes) */
	void (FCALL *ct_connect)(clockid_t clockid)
			THROWS(...);
};

/* Known clock types */
DATDEF struct clocktype const clock_types[CLOCK_COUNT];
DATDEF struct clocktype const clock_pid; /* Special per-process clock. */

/* Lookup the clock for a given clockid.
 * @throws: E_INVALID_ARGUMENT_BAD_VALUE:E_INVALID_ARGUMENT_CONTEXT_BAD_CLOCKID: ... */
FUNDEF ATTR_RETNONNULL WUNUSED struct clocktype const *FCALL
clock_lookup(clockid_t clockid) THROWS(E_INVALID_ARGUMENT_BAD_VALUE);




/************************************************************************/
/* BASIC TIMER CONTROL STRUCTURE                                        */
/************************************************************************/
struct timer {
	struct clocktype const *t_clock;    /* [1..1][const] Attached clock. */
	clockid_t               t_clockid;  /* [const] Clock-id attached to `t_clock' */
	struct atomic_rwlock    t_lock;     /* Timer lock */
	struct timespec         t_expire;   /* [lock(t_lock)] Absolute time (in `t_clock') when the timer expires next.
	                                     * When in the past, the timer  has already expired, and when  `t_interval'
	                                     * is non-zero, it has done so `(now - t_expire) / t_interval' times.  When
	                                     * this field is set to zero, the timer is disarmed. */
	struct timespec         t_interval; /* [lock(t_lock)] Timer expiration interval. */
	struct sig              t_changed;  /* Signal broadcast when `t_expire/t_interval'  are changed because of  the
	                                     * timer being re-configured (not broadcast as a result of `t_expire' being
	                                     * updated as a result of a periodic `t_interval') */
};

/* Helper macros for `struct timer::t_lock' */
#define timer_mustreap(self)     0
#define timer_reap(self)         (void)0
#define _timer_reap(self)        (void)0
#define timer_write(self)        atomic_rwlock_write(&(self)->t_lock)
#define timer_write_nx(self)     atomic_rwlock_write_nx(&(self)->t_lock)
#define timer_trywrite(self)     atomic_rwlock_trywrite(&(self)->t_lock)
#define timer_endwrite(self)     (atomic_rwlock_endwrite(&(self)->t_lock), timer_reap(self))
#define _timer_endwrite(self)    atomic_rwlock_endwrite(&(self)->t_lock)
#define timer_read(self)         atomic_rwlock_read(&(self)->t_lock)
#define timer_read_nx(self)      atomic_rwlock_read_nx(&(self)->t_lock)
#define timer_tryread(self)      atomic_rwlock_tryread(&(self)->t_lock)
#define _timer_endread(self)     atomic_rwlock_endread(&(self)->t_lock)
#define timer_endread(self)      (void)(atomic_rwlock_endread(&(self)->t_lock) && (timer_reap(self), 0))
#define _timer_end(self)         atomic_rwlock_end(&(self)->t_lock)
#define timer_end(self)          (void)(atomic_rwlock_end(&(self)->t_lock) && (timer_reap(self), 0))
#define timer_upgrade(self)      atomic_rwlock_upgrade(&(self)->t_lock)
#define timer_upgrade_nx(self)   atomic_rwlock_upgrade_nx(&(self)->t_lock)
#define timer_tryupgrade(self)   atomic_rwlock_tryupgrade(&(self)->t_lock)
#define timer_downgrade(self)    atomic_rwlock_downgrade(&(self)->t_lock)
#define timer_reading(self)      atomic_rwlock_reading(&(self)->t_lock)
#define timer_writing(self)      atomic_rwlock_writing(&(self)->t_lock)
#define timer_canread(self)      atomic_rwlock_canread(&(self)->t_lock)
#define timer_canwrite(self)     atomic_rwlock_canwrite(&(self)->t_lock)
#define timer_waitread(self)     atomic_rwlock_waitread(&(self)->t_lock)
#define timer_waitwrite(self)    atomic_rwlock_waitwrite(&(self)->t_lock)
#define timer_waitread_nx(self)  atomic_rwlock_waitread_nx(&(self)->t_lock)
#define timer_waitwrite_nx(self) atomic_rwlock_waitwrite_nx(&(self)->t_lock)

#define timer_init(self, clockid)                               \
	(void)((self)->t_clockid = (clockid),                       \
	       (self)->t_clock   = clock_lookup((self)->t_clockid), \
	       atomic_rwlock_init(&(self)->t_lock),                 \
	       (self)->t_expire.tv_sec    = 0,                      \
	       (self)->t_expire.tv_nsec   = 0,                      \
	       (self)->t_interval.tv_sec  = 0,                      \
	       (self)->t_interval.tv_nsec = 0,                      \
	       sig_init(&(self)->t_changed))
#define timer_cinit(self, clockid)                              \
	(void)((self)->t_clockid = (clockid),                       \
	       (self)->t_clock   = clock_lookup((self)->t_clockid), \
	       atomic_rwlock_cinit(&(self)->t_lock),                \
	       __hybrid_assert((self)->t_expire.tv_sec == 0),       \
	       __hybrid_assert((self)->t_expire.tv_nsec == 0),      \
	       __hybrid_assert((self)->t_interval.tv_sec == 0),     \
	       __hybrid_assert((self)->t_interval.tv_nsec == 0),    \
	       sig_cinit(&(self)->t_changed))
#define timer_fini(self) \
	(void)sig_broadcast_for_fini(&(self)->t_changed)

#define timer_getclocknow(self) \
	((*(self)->t_clock->ct_gettime)((self)->t_clockid))

#define timer_isarmed(self)     ((self)->t_expire.tv_sec || (self)->t_expire.tv_nsec)
#define timer_hasinterval(self) ((self)->t_interval.tv_sec || (self)->t_interval.tv_nsec)
#define timer_disarm(self)               \
	(void)((self)->t_expire.tv_sec  = 0, \
	       (self)->t_expire.tv_nsec = 0)

/* Return the # of times the timer has currently overrun:
 * >> CEIL((now - t_expire) / t_interval);
 * When `t_interval' is 0:
 * >> (now >= t_expire) ? 1 : 0; */
FUNDEF NOBLOCK WUNUSED NONNULL((1, 2)) uint64_t
NOTHROW(FCALL timer_getoverrun_locked)(struct timer const *__restrict self,
                                       struct timespec const *__restrict now);

/* Check if the timer has elapsed (more efficient alternative
 * to `timer_getoverrun_locked(self) > 0') */
#define timer_haselapsed_locked(self, now) \
	(*(now) >= (self)->t_expire && timer_isarmed(self))
FUNDEF WUNUSED NONNULL((1)) __BOOL FCALL
timer_haselapsed(struct timer *__restrict self)
		THROWS(E_WOULDBLOCK);

/* Same as `timer_getoverrun_locked()', but when the timer has
 * an  interval, increase `t_expire' by `N * t_interval', such
 * that it is still less than `now', and return `N'
 *
 * When the timer has no interval, return `0' if the timer has
 * not  yet expired, or `1' (alongside disarming it) if it has
 * expired. */
FUNDEF NOBLOCK NONNULL((1, 2)) uint64_t
NOTHROW(FCALL timer_takeoverrun_locked)(struct timer *__restrict self,
                                        struct timespec const *__restrict now);
FUNDEF WUNUSED NONNULL((1)) uint64_t FCALL
timer_takeoverrun(struct timer *__restrict self)
		THROWS(E_WOULDBLOCK);

/* Similar to `timer_takeoverrun_locked()', but doesn't  write-back
 * the next expire-timestamp to `self'. Instead, it calculates  the
 * next point in time when `self' will expire after `now', and then
 * returns that timestamp.
 * When `self' isn't an interval-timer, this function returns  the
 * currently configured expire-timestamp (if `> *now'), or an all-
 * zero timestamp if already expired. */
FUNDEF NOBLOCK WUNUSED NONNULL((1, 2)) struct timespec
NOTHROW(FCALL timer_getnextexpire_locked)(struct timer const *__restrict self,
                                          struct timespec const *__restrict now);

/* Connect to the given timer `self' and calculate a  conservative
 * guess on when  the timer  will probably expire  (it may  expire
 * earlier than this guess, but in this case a signal is broadcast
 * which this function has connected to).
 *
 * This function is designed for use with `struct async_ops::ao_connect'
 * @return: KTIME_NONBLOCK: Timer has already expired (at least once) */
FUNDEF WUNUSED NONNULL((1)) ktime_t FCALL
timer_connect(struct timer *__restrict self)
		THROWS(E_WOULDBLOCK, ...);

/* Blocking function to wait until  the timer has expired at  least
 * once, at which point `timer_takeoverrun_locked()' is called, and
 * its value is returned.
 *
 * The non-blocking equivalent to this is `timer_takeoverrun()' */
FUNDEF BLOCKING WUNUSED NONNULL((1)) uint64_t FCALL
timer_waitfor(struct timer *__restrict self)
		THROWS(E_WOULDBLOCK, ...);
#define timer_trywaitfor timer_takeoverrun

/* Get the current configuration of `self' */
FUNDEF WUNUSED NONNULL((1)) struct itimerspec FCALL
timer_gettime(struct timer *__restrict self)
		THROWS(E_WOULDBLOCK);

/* Set the configuration of `self'
 * @throw: E_INVALID_ARGUMENT_BAD_VALUE:E_INVALID_ARGUMENT_CONTEXT_BAD_TIMESPEC_NSEC: ... */
FUNDEF NONNULL((1)) void FCALL
timer_settime(struct timer *__restrict self,
              /*[0..1]*/ USER CHECKED struct itimerspec const *value,
              /*[0..1]*/ USER CHECKED struct itimerspec *old_value)
		THROWS(E_WOULDBLOCK, E_SEGFAULT, E_INVALID_ARGUMENT_BAD_VALUE);




/************************************************************************/
/* USER-SPACE TIMERFD OBJECT                                            */
/************************************************************************/
struct timerfd_async;
struct timerfd {
	/* HANDLE_TYPE_TIMERFD */
	struct timer              tfd_timer;  /* Underlying timer. */
	uint64_t                  tfd_xover;  /* [lock(tfd_timer.t_lock)] Extra timer overrun (for `TFD_IOC_SET_TICKS') */
	WEAK refcnt_t             tfd_refcnt; /* Reference counter. */
	struct sig                tfd_elapse; /* Signal broadcast by `tfd_async' upon timer overrun. */
	REF struct timerfd_async *tfd_async;  /* [0..1][lock(WRITE_ONCE)]  Timeout handler async-job (start to broadcast
	                                       * `tfd_elapse' during the next timer overrun). We need an extra async job
	                                       * to do this  (and can't  just use some  general-purpose timeout  system,
	                                       * since there needs to be a way to use timerfd with `sys/epoll.h',  which
	                                       * cannot be implemented via timeouts, but only via actual signals) */
};

FUNDEF NOBLOCK void NONNULL((1))
NOTHROW(FCALL timerfd_destroy)(struct timerfd *__restrict self);
DEFINE_REFCNT_FUNCTIONS(struct timerfd, tfd_refcnt, timerfd_destroy)


/* Create a new timerfd object.
 *
 * The  returned object is unarmed by default, and
 * needs to be configured with `timerfd_settime()'
 * @throws: E_INVALID_ARGUMENT_BAD_VALUE:E_INVALID_ARGUMENT_CONTEXT_BAD_CLOCKID: ... */
FUNDEF WUNUSED REF struct timerfd *FCALL timerfd_create(clockid_t clockid)
		THROWS(E_BADALLOC, E_INVALID_ARGUMENT_BAD_VALUE);


/* Functions for operating with `struct timerfd' */
#define timerfd_gettime(self) timer_gettime(&(self)->tfd_timer)
FUNDEF NONNULL((1)) void FCALL
timerfd_settime(struct timerfd *__restrict self,
                /*[0..1]*/ USER CHECKED struct itimerspec const *value,
                /*[0..1]*/ USER CHECKED struct itimerspec *old_value)
		THROWS(E_WOULDBLOCK, E_SEGFAULT, E_INVALID_ARGUMENT_BAD_VALUE);
FUNDEF BLOCKING WUNUSED NONNULL((1)) uint64_t FCALL
timerfd_trywaitfor(struct timerfd *__restrict self)
		THROWS(E_WOULDBLOCK, ...);
FUNDEF BLOCKING WUNUSED NONNULL((1)) uint64_t FCALL
timerfd_waitfor(struct timerfd *__restrict self)
		THROWS(E_WOULDBLOCK, ...);




DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_SCHED_TIMER_H */
