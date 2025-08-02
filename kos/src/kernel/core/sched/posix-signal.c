/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_SRC_SCHED_POSIX_SIGNAL_C
#define GUARD_KERNEL_SRC_SCHED_POSIX_SIGNAL_C 1
#define _GNU_SOURCE 1
#define _KOS_SOURCE 1
#define _TIME64_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/except.h>
#include <kernel/malloc.h>
#include <kernel/rt/except-handler.h>
#include <kernel/syscall.h>
#include <kernel/types.h>
#include <kernel/user.h>
#include <sched/cred.h>
#include <sched/group.h>
#include <sched/pertask.h>
#include <sched/pid.h>
#include <sched/posix-signal.h>
#include <sched/rpc-internal.h>
#include <sched/rpc.h>
#include <sched/sig.h>
#include <sched/sigmask.h>
#include <sched/task.h>
#include <sched/tsc.h>

#include <hybrid/sequence/list.h>

#include <compat/config.h>
#include <kos/except.h>
#include <kos/except/reason/inval.h>

#include <assert.h>
#include <atomic.h>
#include <errno.h>
#include <signal.h>
#include <stddef.h>
#include <string.h>

#ifdef __ARCH_HAVE_COMPAT
#include <compat/bits/os/siginfo-convert.h>
#include <compat/bits/os/siginfo.h>
#include <compat/signal.h>
#endif /* __ARCH_HAVE_COMPAT */

DECL_BEGIN

static_assert(NSIG - 1 <= 0xff,
              "This is an ABI requirement imposed by:\n"
              " - clone(2)\n"
              " - RPC_SIGNO_MASK\n"
              " - RPC_OP_sigblock");


/* Raise a posix signal within a given thread `target'
 * @return: true:  Successfully scheduled/enqueued the signal for delivery to `target'
 * @return: false: The given thread `target' has already terminated execution.
 * @throw: E_INVALID_ARGUMENT_BAD_VALUE: The signal number in `info' is ZERO(0) or > `_NSIG' */
PUBLIC NONNULL((1, 2)) bool FCALL
task_raisesignalthread(struct task *__restrict target,
                       siginfo_t const *__restrict info)
		THROWS(E_BADALLOC, E_WOULDBLOCK, E_INVALID_ARGUMENT_BAD_VALUE) {
	struct pending_rpc *rpc;
	if unlikely(!sigvalid(info->si_signo)) {
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_BAD_SIGNO,
		      info->si_signo);
	}

#ifndef __OPTIMIZE_SIZE__
	/* XXX: If `target's SIGHAND disposition for `info->si_signo' is set
	 *      to `SIG_IGN', then don't send the signal and silently return
	 *      with `true'. */
#endif /* !__OPTIMIZE_SIZE__ */

	rpc = pending_rpc_alloc_psig(GFP_NORMAL);

	/* Fill in RPC signal information. */
	memcpy(&rpc->pr_psig, info, sizeof(siginfo_t));

	/* Set RPC flags: posix signals are _always_ async */
	rpc->pr_flags = RPC_SYNCMODE_F_ALLOW_ASYNC |
	                RPC_CONTEXT_SIGNAL |
	                RPC_SIGNO(rpc->pr_psig.si_signo);

	/* Schedule the RPC */
	if (task_rpc_schedule(target, rpc))
		return true;

	/* Target thread already died :( */
	pending_rpc_free(rpc);
	return false;
}



/* Raise a posix signal within the given process `proc'
 * @return: true:  Successfully scheduled/enqueued the signal for delivery to `target'
 * @return: false: The given process `target' has already terminated execution.
 * @throw: E_INVALID_ARGUMENT_BAD_VALUE: The signal number in `info' is ZERO(0) or >= `_NSIG+1' */
PUBLIC NONNULL((1, 2)) __BOOL FCALL
task_raisesignalprocess(struct taskpid *__restrict proc,
                        siginfo_t const *__restrict info)
		THROWS(E_BADALLOC, E_WOULDBLOCK, E_INVALID_ARGUMENT_BAD_VALUE) {
	struct pending_rpc *rpc;
	if unlikely(!sigvalid(info->si_signo)) {
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_BAD_SIGNO,
		      info->si_signo);
	}

#ifndef __OPTIMIZE_SIZE__
	/* XXX: If any of `target's threads has a SIGHAND disposition for `info->si_signo'
	 *      that  is set to `SIG_IGN', then don't  send the signal and silently return
	 *      with `true'. */
#endif /* !__OPTIMIZE_SIZE__ */

	rpc = pending_rpc_alloc_psig(GFP_NORMAL);

	/* Fill in RPC signal information. */
	memcpy(&rpc->pr_psig, info, sizeof(siginfo_t));

	/* Set RPC flags: posix signals are _always_ async */
	rpc->pr_flags = RPC_SYNCMODE_F_ALLOW_ASYNC |
	                RPC_CONTEXT_SIGNAL |
	                RPC_SIGNO(rpc->pr_psig.si_signo);

	/* Schedule the RPC */
	if (proc_rpc_schedule(proc, rpc))
		return true;

	/* Target thread already died :( */
	pending_rpc_free(rpc);
	return false;
}

#ifndef __pending_rpc_slist_defined
#define __pending_rpc_slist_defined
SLIST_HEAD(pending_rpc_slist, pending_rpc);
#endif /* !__pending_rpc_slist_defined */

/* Send a signal to every process within the given `group'
 * @return: * : The number of processes to which the signal was delivered. */
PUBLIC NONNULL((1, 2)) size_t FCALL
task_raisesignalprocessgroup(struct procgrp *__restrict group,
                             siginfo_t const *__restrict info,
                             struct taskpid *__restrict sender)
		THROWS(E_BADALLOC, E_WOULDBLOCK, E_INVALID_ARGUMENT_BAD_VALUE) {
	struct taskpid *member;
	struct pending_rpc_slist rpcs;
	size_t rpcs_count = 0; /* # of elements in `rpcs' */
	size_t proc_count;
	size_t multiplier = 1;
	if unlikely(!sigvalid(info->si_signo)) {
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_BAD_SIGNO,
		      info->si_signo);
	}

	SLIST_INIT(&rpcs);
	RAII_FINALLY {
		/* Always free unused RPCs. */
		while (!SLIST_EMPTY(&rpcs)) {
			struct pending_rpc *rpc;
			rpc = SLIST_FIRST(&rpcs);
			SLIST_REMOVE_HEAD(&rpcs, pr_link);
			pending_rpc_free(rpc);
		}
	};

	/* Allocate enough RPCs so that we've got at  least
	 * one for every process that's apart of the group. */
	for (;;) {
		size_t req_rpcs;
		procgrp_memb_read(group);
		proc_count = procgrp_memb_count(group);
		if (rpcs_count >= proc_count) {
			if (!proc_count) {
				/* Special case: empty group */
				procgrp_memb_endread(group);
				goto done;
			}
			break;
		}
		if (multiplier > 2) {
			/* The third time we get here, try to allocate more RPCs without
			 * releasing  our lock to the group-member list. -- That way, if
			 * we are able to allocate _all_ of the required RPCs, we can do
			 * so whilst interlocked with  the member list, thus  preventing
			 * more members from being added in the mean time.
			 *
			 * This is useful to improve our odds when the group contains a
			 * run-away "fork bomb", since such a process will be unable to
			 * add  more processes to our group while we're still holding a
			 * lock to the group's member list! */
			do {
				struct pending_rpc *rpc;
				rpc = pending_rpc_alloc_psig_nx(GFP_ATOMIC);
				if (!rpc)
					break; /* We'll need to block in order to allocate more... :( */
				SLIST_INSERT(&rpcs, rpc, pr_link);
				++rpcs_count;
			} while (rpcs_count < proc_count);
			if (rpcs_count >= proc_count)
				break; /* All right -- we've got them all! */
		}
		procgrp_memb_endread(group);

		/* Allocate more RPCs. */
		req_rpcs = proc_count * multiplier;
		assert(rpcs_count < req_rpcs);
		do {
			struct pending_rpc *rpc;
			TRY {
				rpc = pending_rpc_alloc_psig(GFP_NORMAL);
			} CATCH (E_BADALLOC) {
				if (rpcs_count >= proc_count)
					break; /* Try our luck with the RPCs we _did_ manage to allocate. */
				RETHROW();
			}
			SLIST_INSERT(&rpcs, rpc, pr_link);
			++rpcs_count;
		} while (rpcs_count < req_rpcs);

		/* Overallocate more and more  in case the target  process
		 * group contains a run-away "fork bomb". -- In this case,
		 * more threads are constantly added to the group, and  we
		 * have to be fast enough with our overallocation strategy
		 * so-as to allocate at least  as many RPCs as there  will
		 * be processes the next time we get to acquire a lock  to
		 * `procgrp_memb_read()' */
		multiplier *= 2;
	}

	/* Send 1 RPC to every process within the group. */
	FOREACH_procgrp_memb(member, group) {
		struct pending_rpc *rpc;
		assert(!SLIST_EMPTY(&rpcs));
		rpc = SLIST_FIRST(&rpcs);
		SLIST_REMOVE_HEAD(&rpcs, pr_link);
		memcpy(&rpc->pr_psig, info, sizeof(siginfo_t));
		rpc->pr_flags = RPC_SYNCMODE_F_ALLOW_ASYNC |
		                RPC_CONTEXT_SIGNAL |
		                RPC_SIGNO(rpc->pr_psig.si_signo);
		rpc->pr_psig.si_pid = taskpid_getnstid_s(sender, member->tp_ns);
		if (!proc_rpc_schedule(member, rpc))
			SLIST_INSERT(&rpcs, rpc, pr_link);
	}

	procgrp_memb_endread(group);
done:
	return proc_count;
}


/* Same as `task_raisesignalprocessgroup()', but `signo' must be in range `1..31',
 * allowing this function to use "non-queuing" signals, thus preventing the chance
 * of running out of memory while trying to send a signal.
 * NOTE: This function is unable to encode a sender PID/UID, and instead uses
 *       defaults (s.a. `userexcept_exec_user_signo_rpc()') for this purpose. */
PUBLIC NONNULL((1)) size_t FCALL
_task_raisesignoprocessgroup(struct procgrp *__restrict group, signo_t signo)
		THROWS(E_WOULDBLOCK) {
	struct taskpid *member;
	size_t proc_count = 0;
	assert(signo >= 1 && signo <= 31);
	/* Send a signal to every process within the group. */
	procgrp_memb_read(group);
	FOREACH_procgrp_memb(member, group) {
		if (proc_sig_schedule(member, signo))
			++proc_count;
	}
	procgrp_memb_endread(group);
	return proc_count;
}

/* Same as `_task_raisesignoprocessgroup()', but the caller must be holding `procgrp_memb_read(group)' */
PUBLIC NOBLOCK NONNULL((1)) size_t
NOTHROW(FCALL _task_raisesignoprocessgroup_locked)(struct procgrp *__restrict group, signo_t signo) {
	struct taskpid *member;
	size_t proc_count = 0;
	assert(signo >= 1 && signo <= 31);
	/* Send a signal to every process within the group. */
	FOREACH_procgrp_memb(member, group) {
		if (proc_sig_schedule(member, signo))
			++proc_count;
	}
	return proc_count;
}











/************************************************************************/
/* kill(), tgkill(), tkill()                                            */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_KILL
DEFINE_SYSCALL2(errno_t, kill, pid_t, pid, signo_t, signo) {
	struct taskpid *mypid = task_gettaskpid();
	siginfo_t info;
	bzero(&info, sizeof(siginfo_t));
	info.si_signo = signo;
	info.si_errno = 0;
	info.si_code  = SI_USER;
	info.si_uid   = (__uid_t)cred_geteuid();
	if (pid > 0) {
		REF struct taskpid *target;
		/* Kill the process matching `pid'. */
		target = pidns_lookup_srch(THIS_PIDNS, pid);
		FINALLY_DECREF_UNLIKELY(target);
		info.si_pid = taskpid_getnstid_s(mypid, target->tp_ns);
		if (!task_raisesignalprocess(target, &info))
			THROW(E_PROCESS_EXITED, taskpid_getnstid_s(target, mypid->tp_ns));
	} else if (pid == -1) {
		/* TODO: Kill all processes that we're allowed to (except for pid=1). */
		THROW(E_NOT_IMPLEMENTED_TODO);
	} else {
		REF struct procgrp *grp;
		if (pid == 0) {
			grp = task_getprocgrp();
		} else {
			grp = pidns_grplookup_srch(mypid->tp_ns, -pid);
		}
		FINALLY_DECREF_UNLIKELY(grp);
		if (!task_raisesignalprocessgroup(grp, &info, mypid))
			THROW(E_PROCESS_EXITED, -pid);
	}
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_KILL */

#ifdef __ARCH_WANT_SYSCALL_TGKILL
DEFINE_SYSCALL3(errno_t, tgkill,
                pid_t, pid, pid_t, tid,
                signo_t, signo) {
	REF struct task *target;
	if unlikely(!sigvalid(signo)) {
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_BAD_SIGNO,
		      signo);
	}
	target = pidns_lookuptask_srch(THIS_PIDNS, tid);
	FINALLY_DECREF_UNLIKELY(target);

	/* Check if the given TGID matches the group of this thread. */
	if (task_getpid_of_s(target) != pid) {
		if unlikely(pid <= 0) {
			THROW(E_INVALID_ARGUMENT_BAD_VALUE,
			      E_INVALID_ARGUMENT_CONTEXT_BAD_PID,
			      pid);
		}

		/* Maybe not necessarily exited, but no need to create a new exception type for this... */
		THROW(E_PROCESS_EXITED, pid);
	}

	/* Don't deliver signal `0'. - It's used to test access. */
	if (signo != 0) {
		siginfo_t info;
		bzero(&info, sizeof(siginfo_t));
		info.si_signo = signo;
		info.si_errno = 0;
		info.si_code  = SI_TKILL;
		info.si_uid   = (__uid_t)cred_geteuid();
		info.si_pid   = (__pid_t)task_getnstid_s(task_gettaskpid_of(target)->tp_ns);
		if (!task_raisesignalthread(target, &info))
			THROW(E_PROCESS_EXITED, task_gettid_of_s(target));
	}
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_TGKILL */

#ifdef __ARCH_WANT_SYSCALL_TKILL
DEFINE_SYSCALL2(errno_t, tkill, pid_t, tid, signo_t, signo) {
	REF struct task *target;
	if unlikely(!sigvalid(signo)) {
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_BAD_SIGNO,
		      signo);
	}
	target = pidns_lookuptask_srch(THIS_PIDNS, tid);
	FINALLY_DECREF_UNLIKELY(target);

	/* Don't deliver signal `0'. - It's used to test access. */
	if (signo != 0) {
		siginfo_t info;
		bzero(&info, sizeof(siginfo_t));
		info.si_signo = signo;
		info.si_errno = 0;
		info.si_code  = SI_TKILL;
		info.si_uid   = (__uid_t)cred_geteuid();
		info.si_pid   = (__pid_t)task_getnstid_s(task_gettaskpid_of(target)->tp_ns);
		if (!task_raisesignalthread(target, &info))
			THROW(E_PROCESS_EXITED, task_gettid_of_s(target));
	}
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_TKILL */





/************************************************************************/
/* rt_sigqueueinfo(), rt_tgsigqueueinfo()                               */
/************************************************************************/

/* Fill in `info' from `usigno' + `uinfo' */
INTERN NONNULL((1)) void KCALL
siginfo_from_user(siginfo_t *__restrict info, signo_t usigno,
                  NCX UNCHECKED siginfo_t const *uinfo) {
	if unlikely(!sigvalid(usigno)) {
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_BAD_SIGNO,
		      usigno);
	}
	if (uinfo) {
		validate_readable(uinfo, sizeof(siginfo_t));
		COMPILER_READ_BARRIER();
		memcpy(info, uinfo, sizeof(siginfo_t));
		COMPILER_READ_BARRIER();
		if unlikely(usigno != info->si_signo) {
			THROW(E_INVALID_ARGUMENT_UNEXPECTED_COMMAND,
			      E_INVALID_ARGUMENT_CONTEXT_SIGINFO_SIGNO,
			      usigno, info->si_signo);
		}
	} else {
		bzero(info, sizeof(*info));
		info->si_signo = usigno;
		info->si_errno = 0;
		info->si_code  = SI_USER;
		info->si_pid   = (__pid_t)task_getpid();
		info->si_uid   = (__uid_t)cred_geteuid();
	}
}

#ifdef __ARCH_HAVE_COMPAT
INTERN NONNULL((1)) void KCALL
siginfo_from_compat_user(siginfo_t *__restrict info, signo_t usigno,
                         NCX UNCHECKED compat_siginfo_t const *uinfo) {
	if unlikely(!sigvalid(usigno)) {
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_BAD_SIGNO,
		      usigno);
	}
	if (uinfo) {
		compat_validate_readable(uinfo, sizeof(compat_siginfo_t));
		compat_siginfo_to_siginfo(uinfo, info);
		if (usigno != info->si_signo) {
			THROW(E_INVALID_ARGUMENT_UNEXPECTED_COMMAND,
			      E_INVALID_ARGUMENT_CONTEXT_SIGINFO_SIGNO,
			      usigno, info->si_signo);
		}
	} else {
		bzero(info, sizeof(*info));
		info->si_signo = usigno;
		info->si_errno = 0;
		info->si_code  = SI_USER;
		info->si_pid   = (__pid_t)task_getpid();
		info->si_uid   = (__uid_t)cred_geteuid();
	}
}
#endif /* __ARCH_HAVE_COMPAT */


#ifdef __ARCH_WANT_SYSCALL_RT_SIGQUEUEINFO
DEFINE_SYSCALL3(errno_t, rt_sigqueueinfo,
                pid_t, pid, signo_t, signo,
                NCX UNCHECKED siginfo_t const *, uinfo) {
	REF struct taskpid *target;
	siginfo_t info;
	siginfo_from_user(&info, signo, uinfo);
	target = pidns_lookup_srch(THIS_PIDNS, pid);
	FINALLY_DECREF_UNLIKELY(target);

	/* Don't allow sending arbitrary signals to other processes. */
	if ((info.si_code >= 0 || info.si_code == SI_TKILL) &&
	    (taskpid_getprocpid(target) != task_getprocpid()))
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_RAISE_SIGINFO_BADCODE,
		      info.si_code);
	if (signo != 0) {
		if (!task_raisesignalprocess(target, &info))
			THROW(E_PROCESS_EXITED, pid);
	}
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_RT_SIGQUEUEINFO */

#ifdef __ARCH_WANT_SYSCALL_RT_TGSIGQUEUEINFO
DEFINE_SYSCALL4(errno_t, rt_tgsigqueueinfo,
                pid_t, pid, pid_t, tid, signo_t, signo,
                NCX UNCHECKED siginfo_t const *, uinfo) {
	siginfo_t info;
	REF struct task *target;
	struct taskpid *leader;
	struct taskpid *mypid = task_gettaskpid();
	siginfo_from_user(&info, signo, uinfo);
	target = pidns_lookuptask_srch(mypid->tp_ns, tid);
	FINALLY_DECREF_UNLIKELY(target);
	leader = task_getprocpid_of(target);
	if ((info.si_code >= 0 || info.si_code == SI_TKILL) &&
	    (leader != taskpid_getprocpid(mypid)))
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_RAISE_SIGINFO_BADCODE,
		      info.si_code);

	/* Check if the thread-group ID matches that of the leader of the requested thread-group. */
	if (taskpid_getnstid_s(leader, mypid->tp_ns) != pid) {
		if unlikely(pid <= 0) {
			THROW(E_INVALID_ARGUMENT_BAD_VALUE,
			      E_INVALID_ARGUMENT_CONTEXT_BAD_PID, pid);
		}
		THROW(E_PROCESS_EXITED, pid);
	}

	if (signo != 0) {
		if (!task_raisesignalthread(target, &info))
			THROW(E_PROCESS_EXITED, task_gettid_of_s(target));
	}
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_RT_TGSIGQUEUEINFO */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_RT_SIGQUEUEINFO
DEFINE_COMPAT_SYSCALL3(errno_t, rt_sigqueueinfo,
                       pid_t, pid, signo_t, signo,
                       NCX UNCHECKED compat_siginfo_t const *, uinfo) {
	REF struct taskpid *target;
	struct taskpid *mypid = task_gettaskpid();
	siginfo_t info;
	siginfo_from_compat_user(&info, signo, uinfo);
	target = pidns_lookup_srch(mypid->tp_ns, pid);
	FINALLY_DECREF_UNLIKELY(target);
	/* Don't allow sending arbitrary signals to other processes. */
	if ((info.si_code >= 0 || info.si_code == SI_TKILL) &&
	    (taskpid_getprocpid(target) != taskpid_getprocpid(mypid)))
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_RAISE_SIGINFO_BADCODE,
		      info.si_code);
	if (signo != 0) {
		if (!task_raisesignalprocess(target, &info))
			THROW(E_PROCESS_EXITED, pid);
	}
	return -EOK;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_RT_SIGQUEUEINFO */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_RT_TGSIGQUEUEINFO
DEFINE_COMPAT_SYSCALL4(errno_t, rt_tgsigqueueinfo,
                       pid_t, pid, pid_t, tid, signo_t, signo,
                       NCX UNCHECKED compat_siginfo_t const *, uinfo) {
	siginfo_t info;
	REF struct task *target;
	struct taskpid *leader;
	struct taskpid *mypid = task_gettaskpid();
	siginfo_from_compat_user(&info, signo, uinfo);
	target = pidns_lookuptask_srch(mypid->tp_ns, tid);
	FINALLY_DECREF_UNLIKELY(target);
	/* Don't allow sending arbitrary signals to other processes. */
	leader = task_getprocpid_of(target);
	if ((info.si_code >= 0 || info.si_code == SI_TKILL) &&
	    (leader != taskpid_getprocpid(mypid)))
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_RAISE_SIGINFO_BADCODE,
		      info.si_code);
	/* Check if the thread-group ID matches that of the leader of the requested thread-group. */
	if (taskpid_getnstid_s(leader, mypid->tp_ns) != pid) {
		if unlikely(pid <= 0) {
			THROW(E_INVALID_ARGUMENT_BAD_VALUE,
			      E_INVALID_ARGUMENT_CONTEXT_BAD_PID, pid);
		}
		THROW(E_PROCESS_EXITED, pid);
	}

	if (signo != 0) {
		if (!task_raisesignalthread(target, &info))
			THROW(E_PROCESS_EXITED, tid);
	}
	return -EOK;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_RT_TGSIGQUEUEINFO */





/************************************************************************/
/* rt_sigtimedwait(), rt_sigtimedwait_time64()                          */
/************************************************************************/
#if (defined(__ARCH_WANT_SYSCALL_RT_SIGTIMEDWAIT) ||          \
     defined(__ARCH_WANT_SYSCALL_RT_SIGTIMEDWAIT64) ||        \
     defined(__ARCH_WANT_SYSCALL_RT_SIGTIMEDWAIT_TIME64) ||   \
     defined(__ARCH_WANT_COMPAT_SYSCALL_RT_SIGTIMEDWAIT) ||   \
     defined(__ARCH_WANT_COMPAT_SYSCALL_RT_SIGTIMEDWAIT64) || \
     defined(__ARCH_WANT_COMPAT_SYSCALL_RT_SIGTIMEDWAIT_TIME64))
#define WANT_SIGTIMEDWAIT 1
#endif /* ... */

#ifdef WANT_SIGTIMEDWAIT
/* @return: 0 : The timeout has expired
 * @return: * : The accepted signal number */
PRIVATE NONNULL((1)) signo_t KCALL
signal_waitfor(sigset_t const *__restrict these,
               NCX siginfo_t *uinfo,
               ktime_t abs_timeout) {
	assert(!task_isconnected());
	assert(PREEMPTION_ENABLED());

	/* Since we may (very likely)  be waiting for signals that  are
	 * currently masked,  we need  to make  certain that  we  still
	 * receive notification when such a signal arrives, even though
	 * we're unable to handle it by "normal" means. */
	atomic_or(&THIS_TASK->t_flags, TASK_FWAKEONMSKRPC);
	RAII_FINALLY { atomic_and(&THIS_TASK->t_flags, ~TASK_FWAKEONMSKRPC); };
	for (;;) {
		struct pending_rpc *rpc;

		/* Disable preemption for interlocking with  sporadic
		 * wakeups send as the result of new RPCs being added
		 * to our thread's or process's pending lists. */
		PREEMPTION_DISABLE();

		/* Try to steal RPCs. */
		rpc = task_rpc_pending_steal_posix_signal(these);
		if (rpc == NULL) {
			rpc = proc_rpc_pending_trysteal_posix_signal(these);
			if (rpc == PROC_RPC_PENDING_TRYSTEAL_POSIX_SIGNAL_WOULDBLOCK) {
				struct procctl *proc;
				PREEMPTION_ENABLE();
				/* Yield until the lock becomes available. */
				proc = task_getprocctl();
				procctl_sig_waitwrite(proc);
				continue;
			}
		}

		if (rpc != NULL) {
			/* Got one! */
			signo_t result;
			PREEMPTION_ENABLE();
			assert(!(rpc->pr_flags & RPC_CONTEXT_KERN));
			assert(rpc->pr_flags & RPC_CONTEXT_SIGNAL);
			result = rpc->pr_psig.si_signo;
			/* Copy signal information to userspace */
			RAII_FINALLY { pending_rpc_free(rpc); };
			memcpy(uinfo, &rpc->pr_psig, sizeof(siginfo_t));
			return result;
		}

		/* Like always, serve RPCs (and posix signals) before going to sleep. */
		if (task_serve())
			continue;

		/* Sleep until the next sporadic interrupt. */
		if (!task_sleep(abs_timeout))
			return 0;
	}
}
#endif /* WANT_SIGTIMEDWAIT */

#ifdef __ARCH_WANT_SYSCALL_RT_SIGTIMEDWAIT
DEFINE_SYSCALL4(syscall_slong_t, rt_sigtimedwait,
                NCX UNCHECKED sigset_t const *, uthese,
                NCX UNCHECKED siginfo_t *, uinfo,
                NCX UNCHECKED struct timespec32 const *, uts,
                size_t, sigsetsize) {
	sigset_t these;
	syscall_slong_t result;
	ktime_t abs_timeout = KTIME_INFINITE;
	validate_readable(uthese, sigsetsize);
	validate_writable(uinfo, sizeof(siginfo_t));
	if (sigsetsize > sizeof(sigset_t))
		sigsetsize = sizeof(sigset_t);
	bzero(mempcpy(&these, uthese, sigsetsize),
	      sizeof(sigset_t) - sigsetsize);

	/* Make sure that we don't steal these signals */
	sigdelset_nmi(&these);

	if (uts) {
		validate_readable(uts, sizeof(*uts));
		abs_timeout = relktime_from_user_rel(uts);
		if (abs_timeout != 0)
			abs_timeout += ktime();
	}
	result = (syscall_slong_t)signal_waitfor(&these, uinfo,
	                                         abs_timeout);
	if (!result)
		result = -EAGAIN; /* Posix says EAGAIN for this. */
	return result;
}
#endif /* __ARCH_WANT_SYSCALL_RT_SIGTIMEDWAIT */

#if (defined(__ARCH_WANT_SYSCALL_RT_SIGTIMEDWAIT64) || \
     defined(__ARCH_WANT_SYSCALL_RT_SIGTIMEDWAIT_TIME64))
#ifdef __ARCH_WANT_SYSCALL_RT_SIGTIMEDWAIT64
DEFINE_SYSCALL4(syscall_slong_t, rt_sigtimedwait64,
                NCX UNCHECKED sigset_t const *, uthese,
                NCX UNCHECKED siginfo_t *, uinfo,
                NCX UNCHECKED struct timespec64 const *, uts,
                size_t, sigsetsize)
#else /* __ARCH_WANT_SYSCALL_RT_SIGTIMEDWAIT64 */
DEFINE_SYSCALL4(syscall_slong_t, rt_sigtimedwait_time64,
                NCX UNCHECKED sigset_t const *, uthese,
                NCX UNCHECKED siginfo_t *, uinfo,
                NCX UNCHECKED struct timespec64 const *, uts,
                size_t, sigsetsize)
#endif /* !__ARCH_WANT_SYSCALL_RT_SIGTIMEDWAIT64 */
{
	sigset_t these;
	syscall_slong_t result;
	ktime_t abs_timeout = KTIME_INFINITE;
	validate_readable(uthese, sigsetsize);
	validate_writable(uinfo, sizeof(siginfo_t));
	if (sigsetsize > sizeof(sigset_t))
		sigsetsize = sizeof(sigset_t);
	bzero(mempcpy(&these, uthese, sigsetsize),
	      sizeof(sigset_t) - sigsetsize);

	/* Make sure that we don't steal these signals */
	sigdelset_nmi(&these);
	if (uts) {
		validate_readable(uts, sizeof(*uts));
		abs_timeout = relktime_from_user_rel(uts);
		if (abs_timeout != 0)
			abs_timeout += ktime();
	}
	result = (syscall_slong_t)signal_waitfor(&these, uinfo,
	                                         abs_timeout);
	if (!result)
		result = -EAGAIN; /* Posix says EAGAIN for this. */
	return result;
}
#endif /* __ARCH_WANT_SYSCALL_RT_SIGTIMEDWAIT64 || __ARCH_WANT_SYSCALL_RT_SIGTIMEDWAIT_TIME64 */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_RT_SIGTIMEDWAIT
DEFINE_COMPAT_SYSCALL4(syscall_slong_t, rt_sigtimedwait,
                       NCX UNCHECKED compat_sigset_t const *, uthese,
                       NCX UNCHECKED compat_siginfo_t *, uinfo,
                       NCX UNCHECKED struct compat_timespec32 const *, uts,
                       size_t, sigsetsize) {
	sigset_t these;
	siginfo_t info;
	syscall_slong_t result;
	ktime_t abs_timeout = KTIME_INFINITE;
	validate_readable(uthese, sigsetsize);
	validate_writable(uinfo, sizeof(siginfo_t));
	if (sigsetsize > sizeof(sigset_t))
		sigsetsize = sizeof(sigset_t);
	bzero(mempcpy(&these, uthese, sigsetsize),
	      sizeof(sigset_t) - sigsetsize);

	/* Make sure that we don't steal these signals */
	sigdelset_nmi(&these);
	if (uts) {
		validate_readable(uts, sizeof(*uts));
		abs_timeout = relktime_from_user_rel(uts);
		if (abs_timeout != 0)
			abs_timeout += ktime();
	}
	result = (syscall_slong_t)signal_waitfor(&these, &info,
	                                         abs_timeout);
	if (!result) {
		result = -EAGAIN; /* Posix says EAGAIN for this. */
	} else {
		siginfo_to_compat_siginfo(&info, uinfo);
	}
	return result;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_RT_SIGTIMEDWAIT */

#if (defined(__ARCH_WANT_COMPAT_SYSCALL_RT_SIGTIMEDWAIT64) || \
     defined(__ARCH_WANT_COMPAT_SYSCALL_RT_SIGTIMEDWAIT_TIME64))
#ifdef __ARCH_WANT_COMPAT_SYSCALL_RT_SIGTIMEDWAIT64
DEFINE_COMPAT_SYSCALL4(syscall_slong_t, rt_sigtimedwait64,
                       NCX UNCHECKED compat_sigset_t const *, uthese,
                       NCX UNCHECKED compat_siginfo_t *, uinfo,
                       NCX UNCHECKED struct compat_timespec64 const *, uts,
                       size_t, sigsetsize)
#else /* __ARCH_WANT_COMPAT_SYSCALL_RT_SIGTIMEDWAIT64 */
DEFINE_COMPAT_SYSCALL4(syscall_slong_t, rt_sigtimedwait_time64,
                       NCX UNCHECKED compat_sigset_t const *, uthese,
                       NCX UNCHECKED compat_siginfo_t *, uinfo,
                       NCX UNCHECKED struct compat_timespec64 const *, uts,
                       size_t, sigsetsize)
#endif /* !__ARCH_WANT_COMPAT_SYSCALL_RT_SIGTIMEDWAIT64 */
{
	sigset_t these;
	siginfo_t info;
	syscall_slong_t result;
	ktime_t abs_timeout = KTIME_INFINITE;
	validate_readable(uthese, sigsetsize);
	validate_writable(uinfo, sizeof(siginfo_t));
	if (sigsetsize > sizeof(sigset_t))
		sigsetsize = sizeof(sigset_t);
	bzero(mempcpy(&these, uthese, sigsetsize),
	      sizeof(sigset_t) - sigsetsize);

	/* Make sure that we don't steal these signals */
	sigdelset_nmi(&these);
	if (uts) {
		validate_readable(uts, sizeof(*uts));
		abs_timeout = relktime_from_user_rel(uts);
		if (abs_timeout != 0)
			abs_timeout += ktime();
	}
	result = (syscall_slong_t)signal_waitfor(uthese, &info,
	                                         abs_timeout);
	if (!result) {
		result = -EAGAIN; /* Posix says EAGAIN for this. */
	} else {
		siginfo_to_compat_siginfo(&info, uinfo);
	}
	return result;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_RT_SIGTIMEDWAIT64 || __ARCH_WANT_COMPAT_SYSCALL_RT_SIGTIMEDWAIT_TIME64 */

DECL_END

#endif /* !GUARD_KERNEL_SRC_SCHED_POSIX_SIGNAL_C */
