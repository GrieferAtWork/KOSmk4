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


PRIVATE void KCALL get_timezone(NCX struct timezone *result) {
	/* TODO */
	result->tz_dsttime     = 0;
	result->tz_minuteswest = 0;
}



/************************************************************************/
/* ftime(), ftime64()                                                   */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_FTIME
DEFINE_SYSCALL1(errno_t, ftime,
                NCX UNCHECKED struct timeb32 *, tp) {
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
                NCX UNCHECKED struct timeb64 *, tp) {
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
                       NCX UNCHECKED struct compat_timeb32 *, tp) {
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
                       NCX UNCHECKED struct compat_timeb64 *, tp) {
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
                NCX UNCHECKED struct timeval32 *, tv,
                NCX UNCHECKED struct timezone *, tz) {
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
                NCX UNCHECKED struct timeval64 *, tv,
                NCX UNCHECKED struct timezone *, tz) {
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
                       NCX UNCHECKED struct compat_timeval32 *, tv,
                       NCX UNCHECKED struct timezone *, tz) {
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
                       NCX UNCHECKED struct compat_timeval64 *, tv,
                       NCX UNCHECKED struct timezone *, tz) {
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
DEFINE_SYSCALL1(time32_t, time, NCX UNCHECKED time32_t *, tmp) {
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
DEFINE_SYSCALL1(time64_t, time64, NCX UNCHECKED time64_t *, tmp) {
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
                       NCX UNCHECKED compat_time32_t *, tmp) {
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
                       NCX UNCHECKED compat_time64_t *, tmp) {
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
                NCX UNCHECKED struct timespec32 const *, req,
                NCX UNCHECKED struct timespec32 *, rem) {
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
                NCX UNCHECKED struct timespec64 const *, req,
                NCX UNCHECKED struct timespec64 *, rem) {
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
                       NCX UNCHECKED struct compat_timespec32 const *, req,
                       NCX UNCHECKED struct compat_timespec32 *, rem) {
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
                       NCX UNCHECKED struct compat_timespec64 const *, req,
                       NCX UNCHECKED struct compat_timespec64 *, rem) {
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

DECL_END

#endif /* !GUARD_KERNEL_SRC_SCHED_TIME_C */
