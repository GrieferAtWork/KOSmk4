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
#ifndef GUARD_KERNEL_SRC_SCHED_TIME_C
#define GUARD_KERNEL_SRC_SCHED_TIME_C 1
#define _GNU_SOURCE 1
#define _KOS_SOURCE 1
#define _TIME64_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/except.h>
#include <kernel/syscall.h>
#include <kernel/types.h>
#include <kernel/user.h>
#include <sched/group.h>
#include <sched/rpc.h>
#include <sched/task.h>
#include <sched/tsc.h>

#include <hybrid/atomic.h>
#include <hybrid/sched/preemption.h>

#include <bits/os/timespec.h>
#include <bits/os/timeval.h>
#include <compat/config.h>
#include <kos/except.h>
#include <kos/except/reason/inval.h>
#include <sys/time.h>
#include <sys/timeb.h>

#include <assert.h>
#include <errno.h>
#include <sched.h>
#include <stddef.h>
#include <string.h>
#include <time.h>

#ifdef __ARCH_HAVE_COMPAT
#include <compat/bits/os/timeb.h>
#include <compat/bits/os/timespec.h>
#include <compat/bits/os/timeval.h>
#include <compat/kos/types.h>
#endif /* __ARCH_HAVE_COMPAT */


DECL_BEGIN


PRIVATE void KCALL get_timezone(USER CHECKED struct timezone *result) {
	/* TODO */
	result->tz_dsttime     = 0;
	result->tz_minuteswest = 0;
}



/************************************************************************/
/* ftime(), ftime64()                                                   */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_FTIME
DEFINE_SYSCALL1(errno_t, ftime,
                USER UNCHECKED struct timeb32 *, tp) {
	struct timespec ts;
	struct timezone tz;
	validate_writable(tp, sizeof(*tp));
	ts = realtime();
	get_timezone(&tz);
	COMPILER_WRITE_BARRIER();
	tp->dstflag  = (s16)tz.tz_dsttime;
	tp->timezone = (s16)tz.tz_minuteswest;
	tp->millitm  = (u16)(ts.tv_nsec / 1000000);
	tp->time     = (time32_t)ts.tv_sec;
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_FTIME */

#ifdef __ARCH_WANT_SYSCALL_FTIME64
DEFINE_SYSCALL1(errno_t, ftime64,
                USER UNCHECKED struct timeb64 *, tp) {
	struct timespec ts;
	struct timezone tz;
	validate_writable(tp, sizeof(*tp));
	ts = realtime();
	get_timezone(&tz);
	COMPILER_WRITE_BARRIER();
	tp->dstflag  = (s16)tz.tz_dsttime;
	tp->timezone = (s16)tz.tz_minuteswest;
	tp->millitm  = (u16)(ts.tv_nsec / 1000000);
	tp->time     = (time64_t)ts.tv_sec;
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_FTIME64 */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_FTIME
DEFINE_COMPAT_SYSCALL1(errno_t, ftime,
                       USER UNCHECKED struct compat_timeb32 *, tp) {
	struct timespec ts;
	struct timezone tz;
	compat_validate_writable(tp, sizeof(*tp));
	ts = realtime();
	get_timezone(&tz);
	COMPILER_WRITE_BARRIER();
	tp->dstflag  = (s16)tz.tz_dsttime;
	tp->timezone = (s16)tz.tz_minuteswest;
	tp->millitm  = (u16)(ts.tv_nsec / 1000000);
	tp->time     = (compat_time32_t)ts.tv_sec;
	return -EOK;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_FTIME */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_FTIME64
DEFINE_COMPAT_SYSCALL1(errno_t, ftime64,
                       USER UNCHECKED struct compat_timeb64 *, tp) {
	struct timespec ts;
	struct timezone tz;
	compat_validate_writable(tp, sizeof(*tp));
	ts = realtime();
	get_timezone(&tz);
	COMPILER_WRITE_BARRIER();
	tp->dstflag  = (s16)tz.tz_dsttime;
	tp->timezone = (s16)tz.tz_minuteswest;
	tp->millitm  = (u16)(ts.tv_nsec / 1000000);
	tp->time     = (compat_time64_t)ts.tv_sec;
	return -EOK;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_FTIME64 */





/************************************************************************/
/* gettimeofday(), gettimeofday64()                                     */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_GETTIMEOFDAY
DEFINE_SYSCALL2(errno_t, gettimeofday,
                USER UNCHECKED struct timeval32 *, tv,
                USER UNCHECKED struct timezone *, tz) {
	if (tv) {
		struct timespec ts;
		validate_writable(tv, sizeof(*tv));
		ts = realtime();
		COMPILER_WRITE_BARRIER();
		TIMESPEC_TO_TIMEVAL(tv, &ts);
		COMPILER_WRITE_BARRIER();
	}
	if (tz) {
		validate_writable(tz, sizeof(*tz));
		COMPILER_WRITE_BARRIER();
		get_timezone(tz);
		COMPILER_WRITE_BARRIER();
	}
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_GETTIMEOFDAY */

#ifdef __ARCH_WANT_SYSCALL_GETTIMEOFDAY64
DEFINE_SYSCALL2(errno_t, gettimeofday64,
                USER UNCHECKED struct timeval64 *, tv,
                USER UNCHECKED struct timezone *, tz) {
	if (tv) {
		struct timespec ts;
		validate_writable(tv, sizeof(*tv));
		ts = realtime();
		COMPILER_WRITE_BARRIER();
		TIMESPEC_TO_TIMEVAL(tv, &ts);
		COMPILER_WRITE_BARRIER();
	}
	if (tz) {
		validate_writable(tz, sizeof(*tz));
		COMPILER_WRITE_BARRIER();
		get_timezone(tz);
		COMPILER_WRITE_BARRIER();
	}
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_GETTIMEOFDAY64 */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_GETTIMEOFDAY
DEFINE_COMPAT_SYSCALL2(errno_t, gettimeofday,
                       USER UNCHECKED struct compat_timeval32 *, tv,
                       USER UNCHECKED struct timezone *, tz) {
	if (tv) {
		struct timespec ts;
		compat_validate_writable(tv, sizeof(*tv));
		ts = realtime();
		COMPILER_WRITE_BARRIER();
		TIMESPEC_TO_TIMEVAL(tv, &ts);
		COMPILER_WRITE_BARRIER();
	}
	if (tz) {
		compat_validate_writable(tz, sizeof(*tz));
		COMPILER_WRITE_BARRIER();
		get_timezone(tz);
		COMPILER_WRITE_BARRIER();
	}
	return -EOK;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_GETTIMEOFDAY */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_GETTIMEOFDAY64
DEFINE_COMPAT_SYSCALL2(errno_t, gettimeofday64,
                       USER UNCHECKED struct compat_timeval64 *, tv,
                       USER UNCHECKED struct timezone *, tz) {
	if (tv) {
		struct timespec ts;
		compat_validate_writable(tv, sizeof(*tv));
		ts = realtime();
		COMPILER_WRITE_BARRIER();
		TIMESPEC_TO_TIMEVAL(tv, &ts);
		COMPILER_WRITE_BARRIER();
	}
	if (tz) {
		compat_validate_writable(tz, sizeof(*tz));
		COMPILER_WRITE_BARRIER();
		get_timezone(tz);
		COMPILER_WRITE_BARRIER();
	}
	return -EOK;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_GETTIMEOFDAY64 */





/************************************************************************/
/* time(), time64()                                                     */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_TIME
DEFINE_SYSCALL1(time32_t, time, USER UNCHECKED time32_t *, tmp) {
	time32_t result;
	struct timespec nowts;
	nowts  = realtime();
	result = (time32_t)nowts.tv_sec;
	if (tmp) {
		validate_writable(tmp, sizeof(*tmp));
		COMPILER_WRITE_BARRIER();
		*tmp = result;
		COMPILER_WRITE_BARRIER();
	}
	return result;
}
#endif /* __ARCH_WANT_SYSCALL_TIME */

#ifdef __ARCH_WANT_SYSCALL_TIME64
DEFINE_SYSCALL1(time64_t, time64, USER UNCHECKED time64_t *, tmp) {
	time64_t result;
	struct timespec nowts;
	nowts  = realtime();
	result = (time64_t)nowts.tv_sec;
	if (tmp) {
		validate_writable(tmp, sizeof(*tmp));
		COMPILER_WRITE_BARRIER();
		*tmp = result;
		COMPILER_WRITE_BARRIER();
	}
	return result;
}
#endif /* __ARCH_WANT_SYSCALL_TIME64 */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_TIME
DEFINE_COMPAT_SYSCALL1(compat_time32_t, time,
                       USER UNCHECKED compat_time32_t *, tmp) {
	compat_time32_t result;
	struct timespec nowts;
	nowts  = realtime();
	result = (compat_time32_t)nowts.tv_sec;
	if (tmp) {
		compat_validate_writable(tmp, sizeof(*tmp));
		COMPILER_WRITE_BARRIER();
		*tmp = result;
		COMPILER_WRITE_BARRIER();
	}
	return result;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_TIME */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_TIME64
DEFINE_COMPAT_SYSCALL1(compat_time64_t, time64,
                       USER UNCHECKED compat_time64_t *, tmp) {
	compat_time64_t result;
	struct timespec nowts;
	nowts  = realtime();
	result = (compat_time64_t)nowts.tv_sec;
	if (tmp) {
		compat_validate_writable(tmp, sizeof(*tmp));
		COMPILER_WRITE_BARRIER();
		*tmp = result;
		COMPILER_WRITE_BARRIER();
	}
	return result;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_TIME64 */





/************************************************************************/
/* nanosleep(), nanosleep64()                                           */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_NANOSLEEP
DEFINE_SYSCALL2(errno_t, nanosleep,
                USER UNCHECKED struct timespec32 const *, req,
                USER UNCHECKED struct timespec32 *, rem) {
	ktime_t timeout;
	validate_readable(req, sizeof(*req));
	validate_writable_opt(rem, sizeof(*rem));
	COMPILER_READ_BARRIER();
	timeout = ktime() + relktime_from_user_rel(req);
	COMPILER_READ_BARRIER();
	TRY {
		for (;;) {
			PREEMPTION_DISABLE();
			/* Service RPC functions */
			if (task_serve())
				continue;
			if (!task_sleep(timeout))
				break; /* Timeout */
		}
	} EXCEPT {
		if (rem != NULL && was_thrown(E_INTERRUPT_USER_RPC)) {
			/* Write back the remaining time to user-space.
			 * NOTE: If `rem'  is  a  faulty pointer,  it  is  undefined  what
			 *       will  happen  to  that E_SEGFAULT  exception,  however it
			 *       is guarantied that an E_INTERRUPT caused by a  user-space
			 *       RPC or POSIX signal will invoke the RPC/signal's handler! */
			ktime_t now = ktime();
			struct timespec tsrem;
			if (now > timeout)
				now = timeout;
			tsrem = relktime_to_reltimespec(timeout - now);
			NESTED_EXCEPTION;
			COMPILER_WRITE_BARRIER();
			rem->tv_sec  = (typeof(rem->tv_sec))tsrem.tv_sec;
			rem->tv_nsec = (typeof(rem->tv_nsec))tsrem.tv_nsec;
			COMPILER_WRITE_BARRIER();
		}
		RETHROW();
	}
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_NANOSLEEP */

#ifdef __ARCH_WANT_SYSCALL_NANOSLEEP64
DEFINE_SYSCALL2(errno_t, nanosleep64,
                USER UNCHECKED struct timespec64 const *, req,
                USER UNCHECKED struct timespec64 *, rem) {
	ktime_t timeout;
	validate_readable(req, sizeof(*req));
	validate_writable_opt(rem, sizeof(*rem));
	COMPILER_READ_BARRIER();
	timeout = ktime() + relktime_from_user_rel(req);
	COMPILER_READ_BARRIER();
	TRY {
		for (;;) {
			PREEMPTION_DISABLE();
			/* Service RPC functions */
			if (task_serve())
				continue;
			if (!task_sleep(timeout))
				break; /* Timeout */
		}
	} EXCEPT {
		if (rem != NULL && was_thrown(E_INTERRUPT_USER_RPC)) {
			/* Write back the remaining time to user-space.
			 * NOTE: If `rem'  is  a  faulty pointer,  it  is  undefined  what
			 *       will  happen  to  that E_SEGFAULT  exception,  however it
			 *       is guarantied that an E_INTERRUPT caused by a  user-space
			 *       RPC or POSIX signal will invoke the RPC/signal's handler! */
			ktime_t now = ktime();
			struct timespec tsrem;
			if (now > timeout)
				now = timeout;
			tsrem = relktime_to_reltimespec(timeout - now);
			NESTED_EXCEPTION;
			COMPILER_WRITE_BARRIER();
			rem->tv_sec  = (typeof(rem->tv_sec))tsrem.tv_sec;
			rem->tv_nsec = (typeof(rem->tv_nsec))tsrem.tv_nsec;
			COMPILER_WRITE_BARRIER();
		}
		RETHROW();
	}
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_NANOSLEEP64 */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_NANOSLEEP
DEFINE_COMPAT_SYSCALL2(errno_t, nanosleep,
                       USER UNCHECKED struct compat_timespec32 const *, req,
                       USER UNCHECKED struct compat_timespec32 *, rem) {
	ktime_t timeout;
	compat_validate_readable(req, sizeof(*req));
	compat_validate_writable_opt(rem, sizeof(*rem));
	COMPILER_READ_BARRIER();
	timeout = ktime() + relktime_from_user_rel(req);
	COMPILER_READ_BARRIER();
	TRY {
		for (;;) {
			PREEMPTION_DISABLE();
			/* Service RPC functions */
			if (task_serve())
				continue;
			if (!task_sleep(timeout))
				break; /* Timeout */
		}
	} EXCEPT {
		if (rem != NULL && was_thrown(E_INTERRUPT_USER_RPC)) {
			/* Write back the remaining time to user-space.
			 * NOTE: If `rem'  is  a  faulty pointer,  it  is  undefined  what
			 *       will  happen  to  that E_SEGFAULT  exception,  however it
			 *       is guarantied that an E_INTERRUPT caused by a  user-space
			 *       RPC or POSIX signal will invoke the RPC/signal's handler! */
			ktime_t now = ktime();
			struct timespec tsrem;
			if (now > timeout)
				now = timeout;
			tsrem = relktime_to_reltimespec(timeout - now);
			NESTED_EXCEPTION;
			COMPILER_WRITE_BARRIER();
			rem->tv_sec  = (typeof(rem->tv_sec))tsrem.tv_sec;
			rem->tv_nsec = (typeof(rem->tv_nsec))tsrem.tv_nsec;
			COMPILER_WRITE_BARRIER();
		}
		RETHROW();
	}
	return -EOK;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_NANOSLEEP */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_NANOSLEEP64
DEFINE_COMPAT_SYSCALL2(errno_t, nanosleep64,
                       USER UNCHECKED struct compat_timespec64 const *, req,
                       USER UNCHECKED struct compat_timespec64 *, rem) {
	ktime_t timeout;
	compat_validate_readable(req, sizeof(*req));
	compat_validate_writable_opt(rem, sizeof(*rem));
	COMPILER_READ_BARRIER();
	timeout = ktime() + relktime_from_user_rel(req);
	COMPILER_READ_BARRIER();
	TRY {
		for (;;) {
			PREEMPTION_DISABLE();
			/* Service RPC functions */
			if (task_serve())
				continue;
			if (!task_sleep(timeout))
				break; /* Timeout */
		}
	} EXCEPT {
		if (rem != NULL && was_thrown(E_INTERRUPT_USER_RPC)) {
			/* Write back the remaining time to user-space.
			 * NOTE: If `rem'  is  a  faulty pointer,  it  is  undefined  what
			 *       will  happen  to  that E_SEGFAULT  exception,  however it
			 *       is guarantied that an E_INTERRUPT caused by a  user-space
			 *       RPC or POSIX signal will invoke the RPC/signal's handler! */
			ktime_t now = ktime();
			struct timespec tsrem;
			if (now > timeout)
				now = timeout;
			tsrem = relktime_to_reltimespec(timeout - now);
			NESTED_EXCEPTION;
			COMPILER_WRITE_BARRIER();
			rem->tv_sec  = (typeof(rem->tv_sec))tsrem.tv_sec;
			rem->tv_nsec = (typeof(rem->tv_nsec))tsrem.tv_nsec;
			COMPILER_WRITE_BARRIER();
		}
		RETHROW();
	}
	return -EOK;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_NANOSLEEP64 */




/************************************************************************/
/* clock_gettime(2), clock_getres(2)                                    */
/************************************************************************/
#if (defined(__ARCH_WANT_SYSCALL_CLOCK_GETTIME) ||        \
     defined(__ARCH_WANT_SYSCALL_CLOCK_GETTIME_TIME64) || \
     defined(__ARCH_WANT_COMPAT_SYSCALL_CLOCK_GETTIME) || \
     defined(__ARCH_WANT_COMPAT_SYSCALL_CLOCK_GETTIME_TIME64))
PRIVATE NONNULL((2)) errno_t KCALL
sys_clock_gettime_impl(clockid_t clockid,
                       struct timespec *__restrict result) {
	assert(PREEMPTION_ENABLED());
	/* Validate the `clockid' argument. */
	switch (clockid) {

	case CLOCK_REALTIME:
	case CLOCK_REALTIME_ALARM:
	case CLOCK_REALTIME_COARSE:
	case CLOCK_TAI:
		/* Wall-clock realtime */
		*result = realtime();
		break;

	case CLOCK_MONOTONIC:
	case CLOCK_MONOTONIC_RAW:
	case CLOCK_MONOTONIC_COARSE:
	case CLOCK_BOOTTIME:
	case CLOCK_BOOTTIME_ALARM: {
		/* Time since system boot */
		ktime_t now = ktime();
		result->tv_sec  = (time_t)(now / NSEC_PER_SEC);
		result->tv_nsec = (syscall_ulong_t)(now % NSEC_PER_SEC);
	}	break;

	case CLOCK_PROCESS_CPUTIME_ID: {
		/* Active-time of calling process */
		ktime_t active;
		struct task *me        = THIS_TASK;
		struct taskpid *mypid  = task_gettaskpid_of(me);
		struct taskpid *myproc = mypid->tp_proc;
		struct taskpid *sibling;
again:
		PREEMPTION_DISABLE();

		/* Calculate for calling thread. */
		active = ktime_nopr();
		active -= FORTASK(me, this_stoptime);
		active += FORTASK(me, this_activetime);

		/* Calculate for other threads in calling process
		 *
		 * Note that in this case, we can only use the last-snapshot
		 * active time values of other threads, and our result won't
		 * include the partially used-up quantum of threads from the
		 * calling process that are actively running on other CPUs. */
		if (myproc != mypid) {
			REF struct task *proc;
			proc = taskpid_gettask(myproc);
			if unlikely(!proc) {
				PREEMPTION_ENABLE();
serve_and_yield:
				task_serve();
				task_yield();
				goto again;
			}
			active += FORTASK(proc, this_activetime);
			if unlikely(ATOMIC_DECFETCH(proc->t_refcnt) == 0) {
				PREEMPTION_ENABLE();
				destroy(proc);
				goto serve_and_yield;
			}
		}

		FOREACH_procctl_thrds(sibling, mypid->tp_pctl) {
			REF struct task *sibtask;
			if (sibling == mypid)
				continue;
			sibtask = taskpid_gettask(sibling);
			if unlikely(!sibtask) {
				PREEMPTION_ENABLE();
				goto serve_and_yield;
			}
			active += FORTASK(sibtask, this_activetime);
			if unlikely(ATOMIC_DECFETCH(sibtask->t_refcnt) == 0) {
				PREEMPTION_ENABLE();
				destroy(sibtask);
				goto serve_and_yield;
			}
		}
		PREEMPTION_ENABLE();
		result->tv_sec  = (time_t)(active / NSEC_PER_SEC);
		result->tv_nsec = (syscall_ulong_t)(active % NSEC_PER_SEC);
	}	break;

	case CLOCK_THREAD_CPUTIME_ID: {
		/* Active-time of calling thread */
		ktime_t active;
		struct task *me = THIS_TASK;
		PREEMPTION_DISABLE();
		active = ktime_nopr();
		active -= FORTASK(me, this_stoptime);
		active += FORTASK(me, this_activetime);
		PREEMPTION_ENABLE();
		result->tv_sec  = (time_t)(active / NSEC_PER_SEC);
		result->tv_nsec = (syscall_ulong_t)(active % NSEC_PER_SEC);
	}	break;

	default:
		THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND,
		      E_INVALID_ARGUMENT_CONTEXT_CLOCK_GET_CLOCKID,
		      clockid);
		break;
	}
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_CLOCK_GETTIME... */

#if (defined(__ARCH_WANT_SYSCALL_CLOCK_GETRES) ||        \
     defined(__ARCH_WANT_SYSCALL_CLOCK_GETRES_TIME64) || \
     defined(__ARCH_WANT_COMPAT_SYSCALL_CLOCK_GETRES) || \
     defined(__ARCH_WANT_COMPAT_SYSCALL_CLOCK_GETRES_TIME64))
PRIVATE NONNULL((2)) errno_t KCALL
sys_clock_getres_impl(clockid_t clockid,
                      struct timespec *__restrict result) {
	/* Validate the `clockid' argument. */
	switch (clockid) {

	case CLOCK_REALTIME:
	case CLOCK_MONOTONIC:
	case CLOCK_PROCESS_CPUTIME_ID:
	case CLOCK_THREAD_CPUTIME_ID:
	case CLOCK_MONOTONIC_RAW:
	case CLOCK_REALTIME_COARSE:
	case CLOCK_MONOTONIC_COARSE:
	case CLOCK_BOOTTIME:
	case CLOCK_REALTIME_ALARM:
	case CLOCK_BOOTTIME_ALARM:
	case CLOCK_TAI:
		break;

	default:
		THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND,
		      E_INVALID_ARGUMENT_CONTEXT_CLOCK_GET_CLOCKID,
		      clockid);
		break;
	}

	/* All of our clocks have 1-nanosecond precision (although
	 * time values may get truncated when the system  reboots) */
	result->tv_sec  = 0;
	result->tv_nsec = 1;
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_CLOCK_GETRES... */

#ifdef __ARCH_WANT_SYSCALL_CLOCK_GETTIME
DEFINE_SYSCALL2(errno_t, clock_gettime,
                clockid_t, clockid,
                USER UNCHECKED struct timespec32 *, res) {
	errno_t result;
	struct timespec ts;
	validate_writable(res, sizeof(*res));
	result = sys_clock_gettime_impl(clockid, &ts);
	COMPILER_WRITE_BARRIER();
	res->tv_sec  = (typeof(res->tv_sec))ts.tv_sec;
	res->tv_nsec = (typeof(res->tv_nsec))ts.tv_nsec;
	return result;
}
#endif /* __ARCH_WANT_SYSCALL_CLOCK_GETTIME */

#ifdef __ARCH_WANT_SYSCALL_CLOCK_GETTIME_TIME64
DEFINE_SYSCALL2(errno_t, clock_gettime_time64,
                clockid_t, clockid,
                USER UNCHECKED struct timespec64 *, res) {
	errno_t result;
	struct timespec ts;
	validate_writable(res, sizeof(*res));
	result = sys_clock_gettime_impl(clockid, &ts);
	COMPILER_WRITE_BARRIER();
	res->tv_sec  = (typeof(res->tv_sec))ts.tv_sec;
	res->tv_nsec = (typeof(res->tv_nsec))ts.tv_nsec;
	return result;
}
#endif /* __ARCH_WANT_SYSCALL_CLOCK_GETTIME_TIME64 */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_CLOCK_GETTIME
DEFINE_COMPAT_SYSCALL2(errno_t, clock_gettime,
                       clockid_t, clockid,
                       USER UNCHECKED struct compat_timespec32 *, res) {
	errno_t result;
	struct timespec ts;
	validate_writable(res, sizeof(*res));
	result = sys_clock_gettime_impl(clockid, &ts);
	COMPILER_WRITE_BARRIER();
	res->tv_sec  = (typeof(res->tv_sec))ts.tv_sec;
	res->tv_nsec = (typeof(res->tv_nsec))ts.tv_nsec;
	return result;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_CLOCK_GETTIME */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_CLOCK_GETTIME_TIME64
DEFINE_COMPAT_SYSCALL2(errno_t, clock_gettime_time64,
                       clockid_t, clockid,
                       USER UNCHECKED struct compat_timespec64 *, res) {
	errno_t result;
	struct timespec ts;
	validate_writable(res, sizeof(*res));
	result = sys_clock_gettime_impl(clockid, &ts);
	COMPILER_WRITE_BARRIER();
	res->tv_sec  = (typeof(res->tv_sec))ts.tv_sec;
	res->tv_nsec = (typeof(res->tv_nsec))ts.tv_nsec;
	return result;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_CLOCK_GETTIME_TIME64 */

#ifdef __ARCH_WANT_SYSCALL_CLOCK_GETRES
DEFINE_SYSCALL2(errno_t, clock_getres,
                clockid_t, clockid,
                USER UNCHECKED struct timespec32 *, res) {
	errno_t result;
	struct timespec ts;
	validate_writable_opt(res, sizeof(*res));
	result = sys_clock_getres_impl(clockid, &ts);
	COMPILER_WRITE_BARRIER();
	if (res) {
		res->tv_sec  = (typeof(res->tv_sec))ts.tv_sec;
		res->tv_nsec = (typeof(res->tv_nsec))ts.tv_nsec;
	}
	return result;
}
#endif /* __ARCH_WANT_SYSCALL_CLOCK_GETRES */

#ifdef __ARCH_WANT_SYSCALL_CLOCK_GETRES_TIME64
DEFINE_SYSCALL2(errno_t, clock_getres_time64,
                clockid_t, clockid,
                USER UNCHECKED struct timespec64 *, res) {
	errno_t result;
	struct timespec ts;
	validate_writable_opt(res, sizeof(*res));
	result = sys_clock_getres_impl(clockid, &ts);
	COMPILER_WRITE_BARRIER();
	if (res) {
		res->tv_sec  = (typeof(res->tv_sec))ts.tv_sec;
		res->tv_nsec = (typeof(res->tv_nsec))ts.tv_nsec;
	}
	return result;
}
#endif /* __ARCH_WANT_SYSCALL_CLOCK_GETRES_TIME64 */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_CLOCK_GETRES
DEFINE_COMPAT_SYSCALL2(errno_t, clock_getres,
                       clockid_t, clockid,
                       USER UNCHECKED struct compat_timespec32 *, res) {
	errno_t result;
	struct timespec ts;
	validate_writable_opt(res, sizeof(*res));
	result = sys_clock_getres_impl(clockid, &ts);
	COMPILER_WRITE_BARRIER();
	if (res) {
		res->tv_sec  = (typeof(res->tv_sec))ts.tv_sec;
		res->tv_nsec = (typeof(res->tv_nsec))ts.tv_nsec;
	}
	return result;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_CLOCK_GETRES */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_CLOCK_GETRES_TIME64
DEFINE_COMPAT_SYSCALL2(errno_t, clock_getres_time64,
                       clockid_t, clockid,
                       USER UNCHECKED struct compat_timespec64 *, res) {
	errno_t result;
	struct timespec ts;
	validate_writable_opt(res, sizeof(*res));
	result = sys_clock_getres_impl(clockid, &ts);
	COMPILER_WRITE_BARRIER();
	if (res) {
		res->tv_sec  = (typeof(res->tv_sec))ts.tv_sec;
		res->tv_nsec = (typeof(res->tv_nsec))ts.tv_nsec;
	}
	return result;
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
                         struct timespec const *__restrict requested_time,
                         PCLOCK_NANOSLEEP_WRITE_REMAINING write_remaining,
                         void *write_remaining_arg) {
	ktime_t timeout;
	/* Calculate timeout. */
	VALIDATE_FLAGSET(flags, 0 | TIMER_ABSTIME,
	                 E_INVALID_ARGUMENT_CONTEXT_TIMER_FLAGS);
	switch (clockid) {

	case CLOCK_REALTIME:
	case CLOCK_TAI:
		if (flags & TIMER_ABSTIME) {
			/* The given timespec is measured in realtime, so we have
			 * to use `bootime' to convert it into a ktime timestamp. */
			timeout = timespec_to_ktime(*requested_time);
		} else {
			timeout = reltimespec_to_relktime(requested_time);
			timeout += ktime();
		}
		break;

	case CLOCK_MONOTONIC:
	case CLOCK_BOOTTIME:
		/* The given timespec is relative to boottime, as is out ktime_t.
		 * As such, we don't have  to do any special  addend-calculation! */
		timeout = reltimespec_to_relktime(requested_time);
		if (!(flags & TIMER_ABSTIME))
			timeout += ktime();
		break;

	//TODO: case CLOCK_PROCESS_CPUTIME_ID:

	default:
		THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND,
		      E_INVALID_ARGUMENT_CONTEXT_CLOCK_NANOSLEEP_CLOCKID,
		      clockid);
		break;
	}
	TRY {
		for (;;) {
			PREEMPTION_DISABLE();
			/* Service RPC functions */
			if (task_serve())
				continue;
			if (!task_sleep(timeout))
				break; /* Timeout */
		}
	} EXCEPT {
		if ((write_remaining_arg != NULL) &&
		    (flags & TIMER_ABSTIME) == 0 &&
		    (was_thrown(E_INTERRUPT_USER_RPC))) {
			/* Write back the remaining time to user-space.
			 * NOTE: If `rem'  is  a  faulty pointer,  it  is  undefined  what
			 *       will  happen  to  that E_SEGFAULT  exception,  however it
			 *       is guarantied that an E_INTERRUPT caused by a  user-space
			 *       RPC or POSIX signal will invoke the RPC/signal's handler! */
			ktime_t now = ktime();
			struct timespec tsrem;
			if (now > timeout)
				now = timeout;
			tsrem = relktime_to_reltimespec(timeout - now);
			NESTED_EXCEPTION;
			(*write_remaining)(write_remaining_arg, &tsrem);
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
	validate_readable(requested_time, sizeof(*requested_time));
	validate_writable_opt(remaining, sizeof(*remaining));
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
	validate_readable(requested_time, sizeof(*requested_time));
	validate_writable_opt(remaining, sizeof(*remaining));
	req.tv_sec  = (typeof(req.tv_sec))requested_time->tv_sec;
	req.tv_nsec = (typeof(req.tv_nsec))requested_time->tv_nsec;
	COMPILER_READ_BARRIER();
	return sys_clock_nanosleep_impl(clockid, flags, &req,
	                                &sys_clock_nanosleep_time64_compat_encode_remaining,
	                                remaining);
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_CLOCK_NANOSLEEP_TIME64 */

/* TODO: __ARCH_WANT_SYSCALL_CLOCK_NANOSLEEP */
/* TODO: __ARCH_WANT_SYSCALL_CLOCK_SETTIME */

DECL_END

#endif /* !GUARD_KERNEL_SRC_SCHED_TIME_C */
