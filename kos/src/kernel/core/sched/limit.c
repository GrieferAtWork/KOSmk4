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
#ifndef GUARD_KERNEL_SRC_SCHED_LIMIT_C
#define GUARD_KERNEL_SRC_SCHED_LIMIT_C 1
#define _GNU_SOURCE 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/handman.h>
#include <kernel/syscall.h>
#include <kernel/types.h>
#include <kernel/user.h>
#include <sched/cred.h>
#include <sched/pid.h>
#include <sched/task.h>

#include <bits/os/kos/rlimit.h>
#include <compat/config.h>
#include <kos/except.h>
#include <kos/except/reason/inval.h>
#include <sys/resource.h>

#include <atomic.h>
#include <limits.h>
#include <stddef.h>
#include <string.h>

#ifdef __ARCH_HAVE_COMPAT
#include <compat/bits/os/kos/rlimit.h>
#endif /* __ARCH_HAVE_COMPAT */

DECL_BEGIN

#if (defined(__ARCH_WANT_SYSCALL_GETRLIMIT) ||        \
     defined(__ARCH_WANT_SYSCALL_SETRLIMIT) ||        \
     defined(__ARCH_WANT_SYSCALL_PRLIMIT64) ||        \
     defined(__ARCH_WANT_COMPAT_SYSCALL_GETRLIMIT) || \
     defined(__ARCH_WANT_COMPAT_SYSCALL_SETRLIMIT) || \
     defined(__ARCH_WANT_COMPAT_SYSCALL_PRLIMIT64))
#define WANT_RLIMIT
#endif /* ... */

#ifdef WANT_RLIMIT
PRIVATE errno_t KCALL
sys_prlimit64_impl(pid_t pid, syscall_ulong_t resource,
                   struct rlimit64 const *new_rlim,
                   struct rlimit64 *old_rlim) {
	REF struct task *thread;
	if (pid == 0) {
		/* Special case: calling thread. */
		thread = incref(THIS_TASK);
	} else {
		thread = pidns_lookuptask_srch(THIS_PIDNS, pid);
		if (task_getprocpid_of(thread) != task_getprocpid() && !capable(CAP_SYS_RESOURCE)) {
			struct cred *caller_cred;
			REF struct cred *target_cred;
			caller_cred = THIS_CRED;
			target_cred = task_getcred(thread);
			TRY {
				if (caller_cred != target_cred) {
					bool ids_match;
					/* If all 3 UIDs and GIDs match, then the call is also permitted. */
again_lock_cred:
					cred_read(caller_cred);
					if (!cred_tryread(target_cred)) {
						cred_endread(caller_cred);
						cred_waitread(target_cred);
						goto again_lock_cred;
					}
					ids_match = caller_cred->c_ruid == target_cred->c_ruid &&
					            caller_cred->c_ruid == target_cred->c_euid &&
					            caller_cred->c_ruid == target_cred->c_suid &&
					            caller_cred->c_rgid == target_cred->c_rgid &&
					            caller_cred->c_rgid == target_cred->c_egid &&
					            caller_cred->c_rgid == target_cred->c_sgid;
					cred_endread(target_cred);
					cred_endread(caller_cred);
					if (!ids_match) {
						/* FIXME: This translates to EACCES, but specs want EPERM... */
						THROW(E_INSUFFICIENT_RIGHTS, CAP_SYS_RESOURCE);
					}
				}
			} EXCEPT {
				decref_unlikely(target_cred);
				decref_unlikely(thread);
				RETHROW();
			}
			decref_unlikely(target_cred);
		}
	}
	FINALLY_DECREF_UNLIKELY(thread);
	if (new_rlim && (new_rlim->rlim_cur > new_rlim->rlim_max)) {
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_PRLIMIT_BADLIMIT,
		      (uintptr_t)new_rlim->rlim_cur,
		      (uintptr_t)new_rlim->rlim_max);
	}
	switch (resource) {

	case RLIMIT_NOFILE: {
		REF struct handman *hm;
		hm = task_gethandman(thread);
		FINALLY_DECREF_UNLIKELY(hm);
		if (new_rlim) {
			unsigned int new_maxval, old_maxval;
			new_maxval = (unsigned int)new_rlim->rlim_cur;
			if (new_maxval > (unsigned int)INT_MAX + 1)
				new_maxval = (unsigned int)INT_MAX + 1;
			old_maxval = atomic_xch(&hm->hm_maxhand, new_maxval);
			if (old_rlim) {
				old_rlim->rlim_cur = (rlim64_t)old_maxval;
				old_rlim->rlim_max = (rlim64_t)INT_MAX + 1; /* XXX: This would need to be saved in `struct procctl' */
			}
		} else if (old_rlim) {
			old_rlim->rlim_cur = (rlim64_t)atomic_read(&hm->hm_maxhand);
			old_rlim->rlim_max = (rlim64_t)INT_MAX + 1; /* XXX: This would need to be saved in `struct procctl' */
		}
	}	break;

	case RLIMIT_MAXFILE: {
		REF struct handman *hm;
		hm = task_gethandman(thread);
		FINALLY_DECREF_UNLIKELY(hm);
		if (new_rlim) {
			unsigned int new_maxval, old_maxval;
			new_maxval = (unsigned int)new_rlim->rlim_cur;
			if (new_maxval > (unsigned int)INT_MAX)
				new_maxval = (unsigned int)INT_MAX;
			old_maxval = atomic_xch(&hm->hm_maxfd, new_maxval);
			if (old_rlim) {
				old_rlim->rlim_cur = (rlim64_t)old_maxval;
				old_rlim->rlim_max = (rlim64_t)INT_MAX; /* XXX: This would need to be saved in `struct procctl' */
			}
		} else if (old_rlim) {
			old_rlim->rlim_cur = (rlim64_t)atomic_read(&hm->hm_maxfd);
			old_rlim->rlim_max = (rlim64_t)INT_MAX; /* XXX: This would need to be saved in `struct procctl' */
		}
	}	break;

	/* NOTE: For reference,  linux saves  _all_  limits in  a  location
	 *       whose   lifetime  matches  our  `struct procctl'.  In  our
	 *       implementation this will probably only apply to `rlim_max'
	 *       limits,  and `rlim_cur' are  stored alongside the relevant
	 *       component, like `hm_maxhand' in `struct handman'.
	 *
	 * For  the sake of performance (and the fact that resource limits
	 * aren't changed very often), our store should be a copy-on-write
	 * structure pointed-to by `struct procctl' via an `ARREF'.
	 *
	 * That way, processes with identical resource limits can easily
	 * share those limits, without us having to create copies  every
	 * time fork(2) is called. */

	/* TODO: case RLIMIT_CPU: */
	/* TODO: case RLIMIT_FSIZE: */
	/* TODO: case RLIMIT_DATA: */
	/* TODO: case RLIMIT_STACK: */
	/* TODO: case RLIMIT_CORE: */
	/* TODO: case RLIMIT_RSS: */
	/* TODO: case RLIMIT_NPROC: */
	/* TODO: case RLIMIT_MEMLOCK: */
	/* TODO: case RLIMIT_AS: */
	/* TODO: case RLIMIT_LOCKS: */
	/* TODO: case RLIMIT_SIGPENDING: */
	/* TODO: case RLIMIT_MSGQUEUE: */
	/* TODO: case RLIMIT_NICE: */
	/* TODO: case RLIMIT_RTPRIO: */
	/* TODO: case RLIMIT_RTTIME: */

	default:
		THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND,
		      E_INVALID_ARGUMENT_CONTEXT_PRLIMIT_RESOURCE,
		      resource);
		break;
	}
	return 0;
}
#endif /* WANT_RLIMIT */

#ifdef __ARCH_WANT_SYSCALL_PRLIMIT64
DEFINE_SYSCALL4(errno_t, prlimit64,
                pid_t, pid, syscall_ulong_t, resource,
                USER UNCHECKED struct rlimit64 const *, new_rlim,
                USER UNCHECKED struct rlimit64 *, old_rlim) {
	errno_t result;
	struct rlimit64 knewlim, koldlim;
	validate_writable_opt(old_rlim, sizeof(*old_rlim));
	if (new_rlim) {
		validate_readable(new_rlim, sizeof(*new_rlim));
		knewlim.rlim_cur = (rlim64_t)new_rlim->rlim_cur;
		knewlim.rlim_max = (rlim64_t)new_rlim->rlim_max;
		COMPILER_READ_BARRIER();
	}
	bzero(&koldlim, sizeof(koldlim));
	result = sys_prlimit64_impl(pid, resource,
	                            new_rlim ? &knewlim : NULL,
	                            old_rlim ? &koldlim : NULL);
	if (old_rlim) {
		old_rlim->rlim_cur = (typeof(old_rlim->rlim_cur))koldlim.rlim_cur;
		old_rlim->rlim_max = (typeof(old_rlim->rlim_max))koldlim.rlim_max;
		COMPILER_WRITE_BARRIER();
	}
	return result;
}
#endif /* __ARCH_WANT_SYSCALL_PRLIMIT64 */

#ifdef __ARCH_WANT_SYSCALL_GETRLIMIT
DEFINE_SYSCALL2(errno_t, getrlimit, syscall_ulong_t, resource,
                USER UNCHECKED struct __rlimit32 *, old_rlim) {
	errno_t result;
	struct rlimit64 koldlim;
	validate_writable(old_rlim, sizeof(*old_rlim));
	bzero(&koldlim, sizeof(koldlim));
	result = sys_prlimit64_impl(0, resource, NULL, &koldlim);
	old_rlim->rlim_cur = (typeof(old_rlim->rlim_cur))koldlim.rlim_cur;
	old_rlim->rlim_max = (typeof(old_rlim->rlim_max))koldlim.rlim_max;
	return result;
}
#endif /* __ARCH_WANT_SYSCALL_GETRLIMIT */

#ifdef __ARCH_WANT_SYSCALL_SETRLIMIT
DEFINE_SYSCALL2(errno_t, setrlimit, syscall_ulong_t, resource,
                USER UNCHECKED struct __rlimit32 const *, new_rlim) {
	errno_t result;
	struct rlimit64 knewlim;
	validate_readable(new_rlim, sizeof(*new_rlim));
	knewlim.rlim_cur = (rlim64_t)new_rlim->rlim_cur;
	knewlim.rlim_max = (rlim64_t)new_rlim->rlim_max;
	result = sys_prlimit64_impl(0, resource, &knewlim, NULL);
	return result;
}
#endif /* __ARCH_WANT_SYSCALL_SETRLIMIT */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_PRLIMIT64
DEFINE_COMPAT_SYSCALL4(errno_t, prlimit64,
                       pid_t, pid, syscall_ulong_t, resource,
                       USER UNCHECKED struct compat_rlimit64 const *, new_rlim,
                       USER UNCHECKED struct compat_rlimit64 *, old_rlim) {
	errno_t result;
	struct rlimit64 knewlim, koldlim;
	validate_writable_opt(old_rlim, sizeof(*old_rlim));
	if (new_rlim) {
		validate_readable(new_rlim, sizeof(*new_rlim));
		knewlim.rlim_cur = (rlim64_t)new_rlim->rlim_cur;
		knewlim.rlim_max = (rlim64_t)new_rlim->rlim_max;
		COMPILER_READ_BARRIER();
	}
	bzero(&koldlim, sizeof(koldlim));
	result = sys_prlimit64_impl(pid, resource,
	                            new_rlim ? &knewlim : NULL,
	                            old_rlim ? &koldlim : NULL);
	if (old_rlim) {
		old_rlim->rlim_cur = (typeof(old_rlim->rlim_cur))koldlim.rlim_cur;
		old_rlim->rlim_max = (typeof(old_rlim->rlim_max))koldlim.rlim_max;
		COMPILER_WRITE_BARRIER();
	}
	return result;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_PRLIMIT64 */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_GETRLIMIT
DEFINE_COMPAT_SYSCALL2(errno_t, getrlimit, syscall_ulong_t, resource,
                       USER UNCHECKED struct compat_rlimit32 *, old_rlim) {
	errno_t result;
	struct rlimit64 koldlim;
	validate_writable(old_rlim, sizeof(*old_rlim));
	bzero(&koldlim, sizeof(koldlim));
	result = sys_prlimit64_impl(0, resource, NULL, &koldlim);
	old_rlim->rlim_cur = (typeof(old_rlim->rlim_cur))koldlim.rlim_cur;
	old_rlim->rlim_max = (typeof(old_rlim->rlim_max))koldlim.rlim_max;
	return result;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_GETRLIMIT */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_SETRLIMIT
DEFINE_COMPAT_SYSCALL2(errno_t, setrlimit, syscall_ulong_t, resource,
                       USER UNCHECKED struct compat_rlimit32 const *, new_rlim) {
	errno_t result;
	struct rlimit64 knewlim;
	validate_readable(new_rlim, sizeof(*new_rlim));
	knewlim.rlim_cur = (rlim64_t)new_rlim->rlim_cur;
	knewlim.rlim_max = (rlim64_t)new_rlim->rlim_max;
	result = sys_prlimit64_impl(0, resource, &knewlim, NULL);
	return result;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_SETRLIMIT */

DECL_END

#endif /* !GUARD_KERNEL_SRC_SCHED_LIMIT_C */
