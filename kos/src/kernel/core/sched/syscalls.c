/* Copyright (c) 2019 Griefer@Work                                            *
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
#ifndef GUARD_KERNEL_SRC_SCHED_SYSCALLS_C
#define GUARD_KERNEL_SRC_SCHED_SYSCALLS_C 1
#define _GNU_SOURCE 1
#define _KOS_SOURCE 1
#define _TIME64_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/except.h>
#include <kernel/syscall.h>
#include <kernel/types.h>
#include <kernel/user.h>
#include <sched/cpu.h>
#include <sched/rpc.h>
#include <sched/task.h>

#include <bits/timeval.h>
#include <bits/timespec.h>

#include <errno.h>
#include <sys/time.h>

DECL_BEGIN

//DEFINE {0x0000004e,0x00000060} = gettimeofday(struct __timeval32 *tv, struct timezone *tz): errno_t;
//DEFINE {0x8000004e,0x80000060} = gettimeofday64(struct __timeval64 *tv, struct timezone *tz): errno_t;

PRIVATE struct timespec KCALL realtime_now(void) {
	struct timespec result;
	qtime_t now;
	/* TODO: This isn't `CLOCK_REALTIME'. - This is `CLOCK_MONOTONIC' */
	now    = quantum_time();
	result = qtime_to_timespec(&now);
	return result;
}

PRIVATE void KCALL get_timezone(USER CHECKED struct timezone *result) {
	/* TODO */
	result->tz_dsttime     = 0;
	result->tz_minuteswest = 0;
}


DEFINE_SYSCALL2(errno_t, gettimeofday,
                USER UNCHECKED struct __timeval32 *, tv,
                USER UNCHECKED struct timezone *, tz) {
	if (tv) {
		struct timespec ts;
		validate_writable(tv, sizeof(*tv));
		ts = realtime_now();
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

#ifdef __NR_gettimeofday64
DEFINE_SYSCALL2(errno_t, gettimeofday64,
                USER UNCHECKED struct __timeval64 *, tv,
                USER UNCHECKED struct timezone *, tz) {
	if (tv) {
		struct timespec ts;
		validate_writable(tv, sizeof(*tv));
		ts = realtime_now();
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
#endif /* __NR_gettimeofday64 */

#ifdef __NR_time
DEFINE_SYSCALL1(time32_t, time,
                USER UNCHECKED time32_t *, tmp) {
	time32_t now;
	now = (time32_t)realtime_now().tv_sec;
	if (tmp) {
		validate_writable(tmp, sizeof(*tmp));
		COMPILER_WRITE_BARRIER();
		*tmp = now;
		COMPILER_WRITE_BARRIER();
	}
	return now;
}
#endif /* __NR_time */

#ifdef __NR_time64
DEFINE_SYSCALL1(time64_t, time64,
                USER UNCHECKED time64_t *, tmp) {
	time64_t now;
	now = (time64_t)realtime_now().tv_sec;
	if (tmp) {
		validate_writable(tmp, sizeof(*tmp));
		COMPILER_WRITE_BARRIER();
		*tmp = now;
		COMPILER_WRITE_BARRIER();
	}
	return now;
}
#endif /* __NR_time64 */

DEFINE_SYSCALL2(errno_t, nanosleep,
                USER UNCHECKED struct __timespec32 const *, req,
                USER UNCHECKED struct __timespec32 *, rem) {
	qtime_t tmo;
	struct timespec tms;
	validate_readable(req, sizeof(*req));
	validate_writable_opt(rem, sizeof(*rem));
	COMPILER_READ_BARRIER();
	tms.tv_sec  = (time_t)req->tv_sec;
	tms.tv_nsec = req->tv_nsec;
	COMPILER_READ_BARRIER();
	tmo = quantum_time() + timespec_to_qtime(&tms);
	TRY {
		for (;;) {
			PREEMPTION_DISABLE();
			/* Service RPC functions */
			if (task_serve())
				continue;
			if (!task_sleep(&tmo))
				break; /* Timeout */
		}
	} EXCEPT {
		if (rem != NULL && was_thrown(E_INTERRUPT)) {
			/* Write back the remaining time to user-space.
			 * NOTE: If `rem' is a faulty pointer, it is undefined what
			 *       will happen to that E_SEGFAULT exception, however it
			 *       is guarantied that an E_INTERRUPT caused by a user-space
			 *       RPC or POSIX signal will invoke the RPC/signal's handler! */
			struct timespec tsrem;
			qtime_t now = quantum_time();
			now -= tmo;
			tsrem = qtime_to_timespec(&now);
			COMPILER_WRITE_BARRIER();
			rem->tv_sec  = (time32_t)tsrem.tv_sec;
			rem->tv_nsec = tsrem.tv_nsec;
			COMPILER_WRITE_BARRIER();
		}
		RETHROW();
	}
	return -EOK;
}

#ifdef __NR_nanosleep64
DEFINE_SYSCALL2(errno_t, nanosleep64,
                USER UNCHECKED struct __timespec64 const *, req,
                USER UNCHECKED struct __timespec64 *, rem) {
	qtime_t tmo;
	struct timespec tms;
	validate_readable(req, sizeof(*req));
	validate_writable_opt(rem, sizeof(*rem));
	COMPILER_READ_BARRIER();
	tms.tv_sec  = (time_t)req->tv_sec;
	tms.tv_nsec = req->tv_nsec;
	COMPILER_READ_BARRIER();
	tmo = quantum_time() + timespec_to_qtime(&tms);
	TRY {
		for (;;) {
			PREEMPTION_DISABLE();
			/* Service RPC functions */
			if (task_serve())
				continue;
			if (!task_sleep(&tmo))
				break; /* Timeout */
		}
	} EXCEPT {
		if (rem != NULL && was_thrown(E_INTERRUPT)) {
			/* Write back the remaining time to user-space.
			 * NOTE: If `rem' is a faulty pointer, it is undefined what
			 *       will happen to that E_SEGFAULT exception, however it
			 *       is guarantied that an E_INTERRUPT caused by a user-space
			 *       RPC or POSIX signal will invoke the RPC/signal's handler! */
			struct timespec tsrem;
			qtime_t now = quantum_time();
			now -= tmo;
			tsrem = qtime_to_timespec(&now);
			COMPILER_WRITE_BARRIER();
			rem->tv_sec  = (time64_t)tsrem.tv_sec;
			rem->tv_nsec = tsrem.tv_nsec;
			COMPILER_WRITE_BARRIER();
		}
		RETHROW();
	}
	return -EOK;
}
#endif /* __NR_nanosleep64 */



DECL_END

#endif /* !GUARD_KERNEL_SRC_SCHED_SYSCALLS_C */
