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
#ifndef GUARD_KERNEL_SRC_SCHED_SYSCALLS_C
#define GUARD_KERNEL_SRC_SCHED_SYSCALLS_C 1
#define _GNU_SOURCE 1
#define _KOS_SOURCE 1
#define _TIME64_SOURCE 1

#include <kernel/compiler.h>

#include <fs/vfs.h>
#include <kernel/except.h>
#include <kernel/handle.h>
#include <kernel/syscall.h>
#include <kernel/types.h>
#include <kernel/user.h>
#include <kernel/vm.h>
#include <sched/cpu.h>
#include <sched/cred.h>
#include <sched/pid.h>
#include <sched/posix-signal.h>
#include <sched/rpc.h>
#include <sched/signal.h>
#include <sched/task.h>

#include <bits/timespec.h>
#include <bits/timeval.h>
#include <compat/config.h>
#include <kos/except/reason/inval.h>
#include <sys/time.h>
#include <sys/timeb.h>

#include <assert.h>
#include <errno.h>
#include <sched.h>

#ifdef __ARCH_HAVE_COMPAT
#include <compat/bits/timeb.h>
#include <compat/bits/timespec.h>
#include <compat/bits/timeval.h>
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
	assert(!task_isconnected());
	nowts  = realtime();
	result = (time32_t)nowts.tv_sec;
	if (tmp) {
		validate_writable(tmp, sizeof(*tmp));
		COMPILER_WRITE_BARRIER();
		*tmp = result;
		COMPILER_WRITE_BARRIER();
	}
	assert(!task_isconnected());
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
	struct timespec tmo;
	validate_readable(req, sizeof(*req));
	validate_writable_opt(rem, sizeof(*rem));
	COMPILER_READ_BARRIER();
	tmo.tv_sec  = (time_t)req->tv_sec;
	tmo.tv_nsec = req->tv_nsec;
	COMPILER_READ_BARRIER();
	if unlikely(!tmo.tv_sec && !tmo.tv_nsec)
		return -EOK;
	tmo += realtime();
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
			struct timespec tsrem = realtime() - tmo;
			COMPILER_WRITE_BARRIER();
			rem->tv_sec  = (time32_t)tsrem.tv_sec;
			rem->tv_nsec = tsrem.tv_nsec;
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
	struct timespec tmo;
	validate_readable(req, sizeof(*req));
	validate_writable_opt(rem, sizeof(*rem));
	COMPILER_READ_BARRIER();
	tmo.tv_sec  = (time_t)req->tv_sec;
	tmo.tv_nsec = req->tv_nsec;
	COMPILER_READ_BARRIER();
	if unlikely(!tmo.tv_sec && !tmo.tv_nsec)
		return -EOK;
	tmo += realtime();
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
			struct timespec tsrem = realtime() - tmo;
			COMPILER_WRITE_BARRIER();
			rem->tv_sec  = (time64_t)tsrem.tv_sec;
			rem->tv_nsec = tsrem.tv_nsec;
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
	struct timespec tmo;
	compat_validate_readable(req, sizeof(*req));
	compat_validate_writable_opt(rem, sizeof(*rem));
	COMPILER_READ_BARRIER();
	tmo.tv_sec  = (time_t)req->tv_sec;
	tmo.tv_nsec = req->tv_nsec;
	COMPILER_READ_BARRIER();
	if unlikely(!tmo.tv_sec && !tmo.tv_nsec)
		return -EOK;
	tmo += realtime();
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
			struct timespec tsrem = realtime() - tmo;
			COMPILER_WRITE_BARRIER();
			rem->tv_sec  = (compat_time32_t)tsrem.tv_sec;
			rem->tv_nsec = tsrem.tv_nsec;
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
	struct timespec tmo;
	compat_validate_readable(req, sizeof(*req));
	compat_validate_writable_opt(rem, sizeof(*rem));
	COMPILER_READ_BARRIER();
	tmo.tv_sec  = (time_t)req->tv_sec;
	tmo.tv_nsec = req->tv_nsec;
	COMPILER_READ_BARRIER();
	if unlikely(!tmo.tv_sec && !tmo.tv_nsec)
		return -EOK;
	tmo += realtime();
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
			struct timespec tsrem = realtime() - tmo;
			COMPILER_WRITE_BARRIER();
			rem->tv_sec  = (compat_time64_t)tsrem.tv_sec;
			rem->tv_nsec = tsrem.tv_nsec;
			COMPILER_WRITE_BARRIER();
		}
		RETHROW();
	}
	return -EOK;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_NANOSLEEP64 */





/************************************************************************/
/* unshare()                                                            */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_UNSHARE
PRIVATE void KCALL unshare_vm(void) {
	struct vm *myvm = THIS_VM;
	if (isshared(myvm)) {
		REF struct vm *newvm;
		newvm = vm_clone(myvm);
		FINALLY_DECREF_UNLIKELY(newvm);
		task_setvm(newvm);
	}
}

PRIVATE void KCALL unshare_fs(syscall_ulong_t what) {
	struct fs *myfs = THIS_FS;
	if (isshared(myfs)) {
		REF struct fs *newfs;
		newfs = fs_clone(myfs, (what & CLONE_NEWNS) != 0);
		FINALLY_DECREF_UNLIKELY(newfs);
		myfs = task_setfs(newfs);
		decref_unlikely(myfs);
	}
}

PRIVATE void KCALL unshare_files(void) {
	struct handle_manager *myman = THIS_HANDLE_MANAGER;
	if (isshared(myman)) {
		REF struct handle_manager *newman;
		newman = handle_manager_clone(myman);
		FINALLY_DECREF_UNLIKELY(newman);
		myman = task_sethandlemanager(newman);
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
			sync_read(myptr);
			COMPILER_READ_BARRIER();
			myhand = myptr->sp_hand;
			COMPILER_READ_BARRIER();
			if (!myhand) {
				/* No handlers -> Nothing to point to! */
				sync_endread(myptr);
				kfree(newptr);
				newptr = NULL;
			} else {
				if (!sync_trywrite(myhand)) {
					sync_endread(myptr);
					task_yield();
					goto again_lock_myptr;
				}
				sync_endread(myptr);
				sighand_incshare(myhand);
				sync_endwrite(myhand);
				/* Still share the handler table as copy-on-write. */
				atomic_rwlock_init(&newptr->sp_lock);
				newptr->sp_refcnt = 1;
				newptr->sp_hand   = myhand; /* Inherit: sighand_incshare() */
			}
		} EXCEPT {
			kfree(newptr);
			RETHROW();
		}
		PERTASK_SET(this_sighand_ptr, newptr); /* Inherit reference */
		decref_unlikely(myptr);
	}
}

PRIVATE void KCALL unshare_cred(void) {
	struct cred *mycred = THIS_CRED;
	if (isshared(mycred)) {
		REF struct cred *newcred;
		newcred = cred_clone(mycred);
		FINALLY_DECREF_UNLIKELY(newcred);
		mycred = task_setcred(newcred);
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
		 * calling thread isn't moved into the new namespace. */
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
