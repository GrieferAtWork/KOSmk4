/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
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
#include <kernel/fs/fs.h>
#include <kernel/handman.h>
#include <kernel/malloc.h>
#include <kernel/memory.h>
#include <kernel/mman.h>
#include <kernel/syscall.h>
#include <kernel/types.h>
#include <kernel/user.h>
#include <sched/cpu.h>
#include <sched/cred.h>
#include <sched/group.h>
#include <sched/rpc.h>
#include <sched/sig.h>
#include <sched/sigaction.h>
#include <sched/task.h>
#include <sched/tsc.h>

#include <hybrid/atomic.h>

#include <bits/os/sysinfo.h>
#include <bits/os/timespec.h>
#include <bits/os/timeval.h>
#include <compat/config.h>
#include <kos/except/reason/inval.h>
#include <linux/sysinfo.h>
#include <sys/time.h>
#include <sys/timeb.h>

#include <assert.h>
#include <errno.h>
#include <sched.h>
#include <stddef.h>
#include <string.h>
#include <time.h>

#ifdef __ARCH_HAVE_COMPAT
#include <compat/bits/os/sysinfo.h>
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
	assert(!task_wasconnected());
	nowts  = realtime();
	result = (time32_t)nowts.tv_sec;
	if (tmp) {
		validate_writable(tmp, sizeof(*tmp));
		COMPILER_WRITE_BARRIER();
		*tmp = result;
		COMPILER_WRITE_BARRIER();
	}
	assert(!task_wasconnected());
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
/* sysinfo()                                                            */
/************************************************************************/
#if defined(__ARCH_WANT_SYSCALL_SYSINFO) || defined(__ARCH_WANT_COMPAT_SYSCALL_SYSINFO)
PRIVATE WUNUSED size_t
NOTHROW(KCALL get_total_ram_in_pages)(void) {
	static size_t known = 0;
	size_t i, result;
	result = known;
	if (result != 0)
		return result;
	for (i = 0; i < mzones.pm_zonec; ++i) {
		result += (size_t)mzones.pm_zones[i]->mz_rmax + 1;
	}
	ATOMIC_WRITE(known, result);
	return result;
}

PRIVATE WUNUSED size_t
NOTHROW(KCALL get_free_ram_in_pages)(void) {
	size_t i, result = 0;
	for (i = 0; i < mzones.pm_zonec; ++i)
		result += (size_t)ATOMIC_READ(mzones.pm_zones[i]->mz_cfree);
	return result;
}

PRIVATE void KCALL
do_sysinfo(USER CHECKED struct sysinfo *info) {
	size_t total, free, used;
	total = get_total_ram_in_pages();
	free  = get_free_ram_in_pages();

	info->uptime   = (typeof(info->uptime))(ktime() / NSEC_PER_SEC);
	info->loads[0] = (typeof(info->loads[0]))1234; /* XXX: Implement me */
	info->loads[1] = (typeof(info->loads[1]))1234; /* XXX: Implement me */
	info->loads[2] = (typeof(info->loads[2]))1234; /* XXX: Implement me */
	info->mem_unit = (typeof(info->mem_unit))PAGESIZE;
	info->totalram = (typeof(info->totalram))total;
	info->freeram  = (typeof(info->freeram))free;

	/* Write some sane values for stuff we don't actually keep track of. */
	used            = total - free;
	info->sharedram = (typeof(info->sharedram))(used / 2);
	info->bufferram = (typeof(info->bufferram))(used / 8);
	info->procs     = 42; /* TODO: # of threads running on the system */

	/* Linux has this weird concept of high memory, but I forget what it was about... */
	info->totalhigh = (typeof(info->totalhigh))total;
	info->freehigh  = (typeof(info->freehigh))free;

	/* We don't implement swap, yet. */
	info->totalswap = (typeof(info->totalswap))0;
	info->freeswap  = (typeof(info->freeswap))0;
}
#endif /* __ARCH_WANT_SYSCALL_SYSINFO || __ARCH_WANT_COMPAT_SYSCALL_SYSINFO */

#ifdef __ARCH_WANT_SYSCALL_SYSINFO
DEFINE_SYSCALL1(errno_t, sysinfo,
                USER UNCHECKED struct sysinfo *, info) {
	validate_writable(info, sizeof(*info));
	do_sysinfo(info);
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_SYSINFO */
#ifdef __ARCH_WANT_COMPAT_SYSCALL_SYSINFO
DEFINE_COMPAT_SYSCALL1(errno_t, sysinfo,
                       USER UNCHECKED struct compat_sysinfo *, info) {
	struct sysinfo si;
	validate_writable(info, sizeof(*info));
	bzero(&si, sizeof(si));
	do_sysinfo(&si);

	/* Write-back info. */
	info->uptime    = (typeof(info->uptime))si.uptime;
	info->loads[0]  = (typeof(info->loads[0]))si.loads[0];
	info->loads[1]  = (typeof(info->loads[1]))si.loads[1];
	info->loads[2]  = (typeof(info->loads[2]))si.loads[2];
	info->totalram  = (typeof(info->totalram))si.totalram;
	info->freeram   = (typeof(info->freeram))si.freeram;
	info->sharedram = (typeof(info->sharedram))si.sharedram;
	info->bufferram = (typeof(info->bufferram))si.bufferram;
	info->totalswap = (typeof(info->totalswap))si.totalswap;
	info->freeswap  = (typeof(info->freeswap))si.freeswap;
	info->procs     = (typeof(info->procs))si.procs;
	info->totalhigh = (typeof(info->totalhigh))si.totalhigh;
	info->freehigh  = (typeof(info->freehigh))si.freehigh;
	info->mem_unit  = (typeof(info->mem_unit))si.mem_unit;
	return -EOK;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_SYSINFO */





/************************************************************************/
/* unshare()                                                            */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_UNSHARE
PRIVATE void KCALL unshare_vm(void) {
	struct mman *mymm = THIS_MMAN;
	if (isshared(mymm)) {
		mymm = mman_fork();         /* Inherit reference */
		task_setmman_inherit(mymm); /* Inherit reference */
	}
}

PRIVATE void KCALL unshare_fs(syscall_ulong_t what) {
	struct fs *myfs = THIS_FS;
	if (isshared(myfs)) {
		myfs = fs_clone(myfs, (what & CLONE_NEWNS) != 0); /* Inherit reference */
		myfs = task_setfs_inherit(myfs);                  /* Inherit reference */
		decref_unlikely(myfs);
	}
}

PRIVATE void KCALL unshare_files(void) {
	struct handman *myman = THIS_HANDMAN;
	if (isshared(myman)) {
		myman = handman_fork(myman);            /* Inherit reference */
		myman = task_sethandman_inherit(myman); /* Inherit reference */
		decref_unlikely(myman);
	}
}

PRIVATE void KCALL unshare_sighand(void) {
	struct sighand_ptr *myptr;
	myptr = PERTASK_GET(this_sighand_ptr);
	if (myptr && isshared(myptr)) {
		REF struct sighand_ptr *newptr;
		struct sighand *myhand;
		newptr = (REF struct sighand_ptr *)kmalloc(sizeof(struct sighand_ptr),
		                                           GFP_NORMAL);
again_lock_myptr:
		TRY {
			sighand_ptr_read(myptr);
			COMPILER_READ_BARRIER();
			myhand = myptr->sp_hand;
			COMPILER_READ_BARRIER();
			if (!myhand) {
				/* No handlers -> Nothing to point to! */
				sighand_ptr_endread(myptr);
				kfree(newptr);
				newptr = NULL;
			} else {
				if (!sighand_trywrite(myhand)) {
					sighand_ptr_endread(myptr);
					task_yield();
					goto again_lock_myptr;
				}
				sighand_ptr_endread(myptr);
				sighand_incshare(myhand);
				sighand_endwrite(myhand);
				/* Still share the handler table as copy-on-write. */
				atomic_rwlock_init(&newptr->sp_lock);
				newptr->sp_refcnt = 1;
				newptr->sp_hand   = myhand; /* Inherit: sighand_incshare() */
			}
		} EXCEPT {
			kfree(newptr);
			RETHROW();
		}
		FINALLY_DECREF_UNLIKELY(newptr);
		myptr = task_setsighand_ptr(newptr);
		xdecref_unlikely(myptr);
	}
}

PRIVATE void KCALL unshare_cred(void) {
	struct cred *mycred = THIS_CRED;
	if (isshared(mycred)) {
		mycred = cred_clone(mycred);           /* Inherit reference */
		mycred = task_setcred_inherit(mycred); /* Inherit reference */
		decref_unlikely(mycred);
	}
}

DEFINE_SYSCALL1(errno_t, unshare, syscall_ulong_t, what) {
	VALIDATE_FLAGSET(what,
	                 CLONE_VM | CLONE_FS | CLONE_FILES | CLONE_SIGHAND |
	                 CLONE_CRED | CLONE_NEWNS | CLONE_SYSVSEM | CLONE_NEWUTS |
	                 CLONE_NEWIPC | CLONE_NEWUSER | CLONE_NEWPID |
	                 CLONE_NEWNET | CLONE_IO,
	                 E_INVALID_ARGUMENT_CONTEXT_UNSHARE_WHAT);
	if (what & CLONE_VM)
		unshare_vm();
	if (what & CLONE_FS)
		unshare_fs(what);
	if (what & CLONE_FILES)
		unshare_files();
	if (what & CLONE_SIGHAND)
		unshare_sighand();
	if (what & CLONE_CRED)
		unshare_cred();
#if 0 /* XXX: Add support for these */
	if (what & CLONE_SYSVSEM) {
	}
	if (what & CLONE_NEWUTS) {
	}
	if (what & CLONE_NEWIPC) {
	}
	if (what & CLONE_NEWUSER) {
	}
	if (what & CLONE_NEWPID) {
		/* This one has some really weird semantics, since the
		 * calling  thread isn't moved into the new namespace. */
	}
	if (what & CLONE_NEWNET) {
	}
	if (what & CLONE_IO) {
	}
#endif
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_UNSHARE */


DECL_END

#endif /* !GUARD_KERNEL_SRC_SCHED_SYSCALLS_C */
