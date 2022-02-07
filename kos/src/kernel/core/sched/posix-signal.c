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
#ifndef GUARD_KERNEL_SRC_SCHED_POSIX_SIGNAL_C
#define GUARD_KERNEL_SRC_SCHED_POSIX_SIGNAL_C 1
#define _GNU_SOURCE 1
#define _KOS_SOURCE 1
#define _TIME64_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/except.h>
#include <kernel/rt/except-handler.h>
#include <kernel/syscall.h>
#include <kernel/types.h>
#include <kernel/user.h>
#include <sched/cred.h>
#include <sched/group.h>
#include <sched/posix-signal.h>
#include <sched/rpc-internal.h>
#include <sched/rpc.h>
#include <sched/task.h>
#include <sched/tsc.h>

#include <hybrid/atomic.h>

#include <compat/config.h>
#include <kos/except.h>
#include <kos/except/reason/inval.h>

#include <assert.h>
#include <errno.h>
#include <signal.h>
#include <string.h>

#ifdef __ARCH_HAVE_COMPAT
#include <compat/bits/os/siginfo-convert.h>
#include <compat/bits/os/siginfo.h>
#include <compat/signal.h>
#endif /* __ARCH_HAVE_COMPAT */

#ifndef CONFIG_USE_NEW_GROUP
/* Need pointer sets for gathering targets of
 * process-group-wide   signal    broadcasts. */
#define POINTER_SET_BUFSIZE 16
#include <misc/pointer-set.h>
#endif /* !CONFIG_USE_NEW_GROUP */

DECL_BEGIN

STATIC_ASSERT_MSG(NSIG - 1 <= 0xff,
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
	if unlikely(info->si_signo <= 0 || info->si_signo >= NSIG) {
		signo_t signo = info->si_signo;
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_RAISE_SIGNO,
		      signo);
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





#ifdef CONFIG_USE_NEW_GROUP

/* Raise a posix signal within the given process `proc'
 * @return: true:  Successfully scheduled/enqueued the signal for delivery to `target'
 * @return: false: The given process `target' has already terminated execution.
 * @throw: E_INVALID_ARGUMENT_BAD_VALUE: The signal number in `info' is ZERO(0) or >= `_NSIG+1' */
PUBLIC NONNULL((1, 2)) __BOOL FCALL
task_raisesignalprocess(struct taskpid *__restrict proc,
                        siginfo_t const *__restrict info)
		THROWS(E_BADALLOC, E_WOULDBLOCK, E_INVALID_ARGUMENT_BAD_VALUE) {
	struct pending_rpc *rpc;
	if unlikely(info->si_signo <= 0 || info->si_signo >= NSIG) {
		signo_t signo = info->si_signo;
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_RAISE_SIGNO,
		      signo);
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
	if unlikely(info->si_signo <= 0 || info->si_signo >= NSIG) {
		signo_t signo = info->si_signo;
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_RAISE_SIGNO,
		      signo);
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
		procgrp_memb_endread(group);

		/* Allocate more RPCs. */
		assert(rpcs_count < proc_count);
		do {
			struct pending_rpc *rpc;
			rpc = pending_rpc_alloc_psig(GFP_NORMAL);
			memcpy(&rpc->pr_psig, info, sizeof(siginfo_t));
			rpc->pr_flags = RPC_SYNCMODE_F_ALLOW_ASYNC |
			                RPC_CONTEXT_SIGNAL |
			                RPC_SIGNO(rpc->pr_psig.si_signo);
			SLIST_INSERT(&rpcs, rpc, pr_link);
		} while (rpcs_count < proc_count);
	}

	/* Send 1 RPC to every process within the group. */
	FOREACH_procgrp_memb(member, group) {
		struct pending_rpc *rpc;
		assert(!SLIST_EMPTY(&rpcs));
		rpc = SLIST_FIRST(&rpcs);
		SLIST_REMOVE_HEAD(&rpcs, pr_link);
		rpc->pr_psig.si_pid = taskpid_getnstid_s(sender, member->tp_ns);
		if (!proc_rpc_schedule(member, rpc))
			SLIST_INSERT(&rpcs, rpc, pr_link);
	}

	procgrp_memb_endread(group);
done:
	return proc_count;
}


#else /* CONFIG_USE_NEW_GROUP */
/* Raise a posix signal within a given process that `target' is apart of
 * @return: true:  Successfully scheduled/enqueued the signal for delivery to `target'
 * @return: false: The given process `target' has already terminated execution.
 * @return: false: The given process `target' is a kernel thread.
 * @throw: E_INVALID_ARGUMENT_BAD_VALUE: The signal number in `info' is ZERO(0) or >= `NSIG' */
PUBLIC NONNULL((1, 2)) bool FCALL
task_raisesignalprocess(struct task *__restrict target,
                        siginfo_t const *__restrict info)
		THROWS(E_BADALLOC, E_WOULDBLOCK, E_INVALID_ARGUMENT_BAD_VALUE) {
	struct pending_rpc *rpc;
#ifndef __OPTIMIZE_SIZE__
	/* XXX: If any of `target's threads has a SIGHAND disposition for `info->si_signo'
	 *      that  is set to `SIG_IGN', then don't  send the signal and silently return
	 *      with `true'. */
#endif /* !__OPTIMIZE_SIZE__ */

	rpc = pending_rpc_alloc_psig(GFP_NORMAL);

	/* Fill in RPC signal information. */
	memcpy(&rpc->pr_psig, info, sizeof(siginfo_t));
	COMPILER_READ_BARRIER();
	if unlikely(rpc->pr_psig.si_signo <= 0 ||
	            rpc->pr_psig.si_signo >= NSIG) {
		signo_t signo = rpc->pr_psig.si_signo;
		pending_rpc_free(rpc);
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_RAISE_SIGNO,
		      signo);
	}

	/* Set RPC flags: posix signals are _always_ async */
	rpc->pr_flags = RPC_SYNCMODE_F_ALLOW_ASYNC |
	                RPC_CONTEXT_SIGNAL |
	                RPC_SIGNO(rpc->pr_psig.si_signo);

	/* Schedule the RPC */
	if (proc_rpc_schedule(target, rpc))
		return true;

	/* Target thread already died :( */
	pending_rpc_free(rpc);
	return false;
}



/* Decref every task-object from `self'. */
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL taskref_pointer_set_decref_all)(struct pointer_set *__restrict self) {
	REF struct task *thread;
	POINTER_SET_FOREACH(thread, self) {
		/* Arguably a  `decref_likely()', but  only if  the
		 * total # of threads in the set is extremely high,
		 * and only if the signal that was send caused most
		 * if not all of these threads to terminate. */
		decref(thread);
	}
}

/* Finalize a pointer set filled with `REF struct task *' elements. */
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL taskref_pointer_set_fini)(struct pointer_set *__restrict self) {
	taskref_pointer_set_decref_all(self);
	pointer_set_fini(self);
}

/* Send a signal to every process within the same process group that `target' is apart of.
 * @return: * : The number of processes to which the signal was delivered. */
PUBLIC NONNULL((1, 2)) size_t FCALL
task_raisesignalprocessgroup(struct task *__restrict target,
                             siginfo_t const *__restrict info)
		THROWS(E_BADALLOC, E_WOULDBLOCK, E_INVALID_ARGUMENT_BAD_VALUE) {
	size_t result = 0;
	REF struct task *pgroup;
	struct taskgroup *pgroup_group;
	struct pointer_set ps; /* Set of processes already visited. */
	/* Deliver the first signal to the process group leader. */
	pgroup = task_getprocessgroupleader_srch_of(target);
	pgroup_group = &FORTASK(pgroup, this_taskgroup);
	TRY {
		if (task_raisesignalprocess(pgroup, info))
			++result;
	} EXCEPT {
		decref_unlikely(pgroup);
		RETHROW();
	}
	pointer_set_init(&ps);
	RAII_FINALLY {
		taskref_pointer_set_fini(&ps);
		decref_unlikely(pgroup);
	};
	{
		REF struct task *pending_delivery_procv[8];
		size_t pending_delivery_procc;
		bool there_are_more_procs;
		struct task *iter;
load_more_threads:
		pending_delivery_procc = 0;
		there_are_more_procs = false;
		sync_read(&pgroup_group->tg_pgrp_processes_lock);
		FOREACH_taskgroup__pgrp_processes(iter, pgroup_group) {
			assert(iter != pgroup);
			if (pointer_set_contains(&ps, iter))
				continue;
			if (!tryincref(iter))
				continue;
			/* Always re-start as  long as  we're able to  find any  other process that  is able  to
			 * receive  the signal. Otherwise, there would be  a race condition between us releasing
			 * the `tg_pgrp_processes_lock' lock,  and some process  calling `task_setprocess()'  to
			 * add itself to the process group. When this happens, that process wouldn't receive the
			 * signal that we're sending to every process within the group.
			 *
			 * This might sound like intended behavior on the surface, but this could also lead
			 * to a scenario  where you're  unable to kill  everyone from  some process  group:
			 *
			 *  #1: Thread[5]: setpgid(0, 0)                          - Become a process group leader
			 *  #2: Thread[5]: sys_fork()                             - Create new Process Thread[6]
			 *  #3: Thread[2]: kill(-5, SIGKILL);                     - Send SIGKILL to every process in PGROUP[5]
			 *  #4: Thread[2]: task_raisesignalprocessgroup()
			 *  #5: Thread[2]: sync_read(tg_pgrp_processes_lock)      - Acquire the lock to view every process apart of PGROUP[5]
			 *  #6: Thread[6]: sys_fork()                             - Try to create Thread[7]
			 *  #7: Thread[6]: task_setprocess(Thread[7])
			 *  #8: Thread[6]: sync_write(tg_pgrp_processes_lock)     - Acquire  the  lock  to add  Thread[7]  to PGROUP[5].
			 *                                                          This  blocks because we're  already holding the lock
			 *                                                          from step #5, so the call blocks until the lock will
			 *                                                          become available.
			 *  #9: Thread[2]: -- Gather all processes from PGROUP[5] (but keep `there_are_more_procs = false')
			 * #10: Thread[2]: sync_endread(tg_pgrp_processes_lock)             - The scheduler chooses not to wake-up `Thread[6]'
			 * #11: Thread[2]: -- Send SIGKILL to every process in PGROUP[5]
			 * #12: Thread[2]: sync_read(tg_pgrp_processes_lock)
			 * #13: Thread[2]: -- Scan for more processes that haven't gotten the signal, yet
			 * #14: Thread[2]: sync_endread(tg_pgrp_processes_lock)
			 * #15: Thread[2]: -- No further processes found
			 * #16: Thread[6]: sync_write(tg_pgrp_processes_lock)     - Finally stops blocking
			 * #17: Thread[6]: -- Add Thread[7] to process to PGROUP[5]
			 * #18: Thread[6]: sync_endwrite(tg_pgrp_processes_lock)
			 *
			 * #19: -- Every thread handles its signals in a random order and terminates.
			 *         However, Thread[7] was never given sent a signal and will continue
			 *         to run indefinitely.
			 *
			 * This is fixed  by always  keeping on searching  for more  processes to  receive
			 * the signal, which then interlocks with the call to `task_serve()' in `clone()',
			 * that is done by the parent process and can be used to prevent the child process
			 * from being started. */
			there_are_more_procs = true;
			pending_delivery_procv[pending_delivery_procc] = iter;
			++pending_delivery_procc;
			if (pending_delivery_procc >= COMPILER_LENOF(pending_delivery_procv))
				break;
		}
		sync_endread(&pgroup_group->tg_pgrp_processes_lock);
		TRY {
			while (pending_delivery_procc) {
				REF struct task *thread;
				thread = pending_delivery_procv[pending_delivery_procc - 1];
				/* Deliver to this process. */
				if (task_raisesignalprocess(thread, info))
					++result;
				/* NOTE: We must insert references to threads which already had
				 *       a signal get delivered. This is _required_ to  prevent
				 *       the scenario where:
				 *        - SEND_SIGNAL_TO_THREAD(t1);
				 *        - ps.insert(t1);
				 *        - In t1: task_exit();
				 *        - In t1: decref(THIS_TASK);
				 *        - In t1: destroy(THIS_TASK);
				 *        - In t1: free(THIS_TASK);
				 *        - In t2: clone();
				 *        - In t2: t3 = kmalloc(struct task);   // addrof(t3) == addrof(t2)
				 *        - In t2: init(t3);
				 *        - In t2: task_start(t3);
				 *       In this case, we'd never end up sending a signal to `t3',
				 *       since we'd think that that thread already had the  signal
				 *       delivered.
				 *
				 * It is kind-of sad  that we have to  keep references to all  of
				 * the threads that already got the signal, since we really don't
				 * need those references for anything else. But it's the simplest
				 * thing we can do here.
				 *
				 * NOTE: We don't keep references for the taskpid structures of
				 * threads that already got the signal, since certain types  of
				 * thread (kernel threads) don't have taskpid descriptors! */
				pointer_set_insert(&ps, thread, GFP_NORMAL); /* Inherit reference. */
				/*decref_unlikely(thread);*/ /* Inherited by `ps' */
				--pending_delivery_procc;
			}
		} EXCEPT {
			while (pending_delivery_procc--)
				decref_unlikely(pending_delivery_procv[pending_delivery_procc]);
			RETHROW();
		}
		if (there_are_more_procs)
			goto load_more_threads;
	}
	return result;
}
#endif /* !CONFIG_USE_NEW_GROUP */




LOCAL ATTR_PURE WUNUSED NONNULL((1)) size_t FCALL
get_pid_indirection(struct task const *__restrict thread) {
	/* TODO: Remove this function once `CONFIG_USE_NEW_GROUP' becomes mandatory */
	struct taskpid *pid = FORTASK(thread, this_taskpid);
	return likely(pid) ? pid->tp_ns->pn_ind : 0;
}

LOCAL ATTR_PURE WUNUSED NONNULL((1)) pid_t FCALL
taskpid_getpid_ind(struct taskpid *__restrict self, size_t ind) {
	/* TODO: Remove this function once `CONFIG_USE_NEW_GROUP' becomes mandatory */
	if likely(ind <= self->tp_ns->pn_ind)
		return _taskpid_slot_getpidno(self->tp_pids[ind]);
	return 0;
}





/************************************************************************/
/* kill(), tgkill(), tkill()                                            */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_KILL
DEFINE_SYSCALL2(errno_t, kill, pid_t, pid, signo_t, signo) {
#ifdef CONFIG_USE_NEW_GROUP
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
#else /* CONFIG_USE_NEW_GROUP */
	REF struct task *target;
	struct taskpid *mypid;
	siginfo_t info;
	bzero(&info, sizeof(siginfo_t));

	/* Make sure we've been given a valid signal number. */
	if unlikely(signo <= 0 || signo >= NSIG) {
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_RAISE_SIGNO,
		      signo);
	}
	info.si_signo = signo;
	info.si_errno = 0;
	info.si_code  = SI_USER;
	info.si_uid   = (__uid_t)cred_geteuid();
	mypid         = THIS_TASKPID;
	if (pid > 0) {
		/* Kill the thread matching `pid'. */
		target = pidns_lookuptask_srch(THIS_PIDNS, pid);
		FINALLY_DECREF_UNLIKELY(target);
		info.si_pid = taskpid_getpid_ind(mypid, get_pid_indirection(target));
		if (!task_raisesignalprocess(target, &info))
			THROW(E_PROCESS_EXITED, task_gettid_of_s(target));
	} else if (pid == 0) {
		/* Kill all processes in the calling thread's process group. */
		target = task_getprocessgroupleader_srch();
		goto do_inherit_target_and_raise_processgroup;
	} else if (pid == -1) {
		/* TODO: Kill all processes that we're allowed to (except for pid=1). */
		THROW(E_NOT_IMPLEMENTED_TODO);
	} else {
		/* Kill the entirety of a process group. */
		target = pidns_lookuptask_srch(THIS_PIDNS, -pid);
do_inherit_target_and_raise_processgroup:
		FINALLY_DECREF_UNLIKELY(target);
		info.si_pid = taskpid_getpid_ind(mypid, get_pid_indirection(target));
		if (!task_raisesignalprocessgroup(target, &info))
			THROW(E_PROCESS_EXITED, task_getpid_of_s(target));
	}
	return -EOK;
#endif /* !CONFIG_USE_NEW_GROUP */
}
#endif /* __ARCH_WANT_SYSCALL_KILL */

#ifdef __ARCH_WANT_SYSCALL_TGKILL
DEFINE_SYSCALL3(errno_t, tgkill,
                pid_t, pid, pid_t, tid,
                signo_t, signo) {
	REF struct task *target;
	if unlikely(signo < 0 || signo >= NSIG)
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_RAISE_SIGNO,
		      signo);
	/* TODO: Refactor `E_INVALID_ARGUMENT_CONTEXT_RAISE_PID' to `E_INVALID_ARGUMENT_CONTEXT_BADTID' */
	/* TODO: Get rid of `E_INVALID_ARGUMENT_CONTEXT_RAISE_TID' and use `E_INVALID_ARGUMENT_CONTEXT_BADTID' */
	/* TODO: Throw `E_INVALID_ARGUMENT_CONTEXT_BADTID' from within `pidns_lookup[task]_srch()' */
	if unlikely(pid <= 0)
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_RAISE_PID,
		      pid);
	if unlikely(tid <= 0)
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_RAISE_TID,
		      tid);
	target = pidns_lookuptask_srch(THIS_PIDNS, tid);
	FINALLY_DECREF_UNLIKELY(target);

	/* Check if the given TGID matches the group of this thread. */
	if (task_getpid_of_s(target) != pid) {
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
		info.si_pid   = (__pid_t)taskpid_getpid_ind(THIS_TASKPID, get_pid_indirection(target));
		if (!task_raisesignalthread(target, &info))
			THROW(E_PROCESS_EXITED, task_gettid_of_s(target));
	}
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_TGKILL */

#ifdef __ARCH_WANT_SYSCALL_TKILL
DEFINE_SYSCALL2(errno_t, tkill, pid_t, tid, signo_t, signo) {
	REF struct task *target;
	if unlikely(signo < 0 || signo >= NSIG)
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_RAISE_SIGNO, signo);
	if unlikely(tid <= 0)
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_RAISE_TID, tid);
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
		info.si_pid   = (__pid_t)taskpid_getpid_ind(THIS_TASKPID, get_pid_indirection(target));
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
                  USER UNCHECKED siginfo_t const *uinfo) {
	if unlikely(usigno < 0 || usigno >= NSIG) {
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_RAISE_SIGNO,
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
                         USER UNCHECKED compat_siginfo_t const *uinfo) {
	if unlikely(usigno < 0 || usigno >= NSIG) {
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_RAISE_SIGNO,
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
                USER UNCHECKED siginfo_t const *, uinfo) {
#ifdef CONFIG_USE_NEW_GROUP
	REF struct taskpid *target;
	siginfo_t info;
	if unlikely(pid <= 0) {
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_RAISE_PID, pid);
	}
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
#else /* CONFIG_USE_NEW_GROUP */
	REF struct task *target;
	siginfo_t info;
	if unlikely(pid <= 0) {
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_RAISE_PID, pid);
	}
	siginfo_from_user(&info, signo, uinfo);
	target = pidns_lookuptask_srch(THIS_PIDNS, pid);
	FINALLY_DECREF_UNLIKELY(target);

	/* Don't allow sending arbitrary signals to other processes. */
	if ((info.si_code >= 0 || info.si_code == SI_TKILL) &&
	    (task_getprocess_of(target) != task_getprocess()))
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_RAISE_SIGINFO_BADCODE,
		      info.si_code);
	if (signo != 0) {
		if (!task_raisesignalprocess(target, &info))
			THROW(E_PROCESS_EXITED, task_getpid_of_s(target));
	}
	return -EOK;
#endif /* !CONFIG_USE_NEW_GROUP */
}
#endif /* __ARCH_WANT_SYSCALL_RT_SIGQUEUEINFO */

#ifdef __ARCH_WANT_SYSCALL_RT_TGSIGQUEUEINFO
DEFINE_SYSCALL4(errno_t, rt_tgsigqueueinfo,
                pid_t, pid, pid_t, tid, signo_t, signo,
                USER UNCHECKED siginfo_t const *, uinfo) {
#ifdef CONFIG_USE_NEW_GROUP
	siginfo_t info;
	REF struct task *target;
	struct taskpid *leader;
	struct taskpid *mypid = task_gettaskpid();
	if unlikely(pid <= 0)
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_RAISE_PID, pid);
	if unlikely(tid <= 0)
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_RAISE_TID, tid);
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
	if (taskpid_getnstid_s(leader, mypid->tp_ns) != pid)
		THROW(E_PROCESS_EXITED, pid);

	if (signo != 0) {
		if (!task_raisesignalthread(target, &info))
			THROW(E_PROCESS_EXITED, task_gettid_of_s(target));
	}
	return -EOK;
#else /* CONFIG_USE_NEW_GROUP */
	siginfo_t info;
	REF struct task *target;
	struct task *leader;
	if unlikely(pid <= 0)
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_RAISE_PID, pid);
	if unlikely(tid <= 0)
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_RAISE_TID, tid);
	siginfo_from_user(&info, signo, uinfo);
	target = pidns_lookuptask_srch(THIS_PIDNS, tid);
	FINALLY_DECREF_UNLIKELY(target);
	/* Don't allow sending arbitrary signals to other processes. */
	leader = task_getprocess_of(target);
	if ((info.si_code >= 0 || info.si_code == SI_TKILL) && leader != task_getprocess())
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_RAISE_SIGINFO_BADCODE,
		      info.si_code);
	/* Check if the thread-group ID matches that of the leader of the requested thread-group. */
	if (task_gettid_of_s(leader) != pid)
		THROW(E_PROCESS_EXITED, pid);
	if (signo != 0) {
		if (!task_raisesignalthread(target, &info))
			THROW(E_PROCESS_EXITED, task_gettid_of_s(target));
	}
	return -EOK;
#endif /* !CONFIG_USE_NEW_GROUP */
}
#endif /* __ARCH_WANT_SYSCALL_RT_TGSIGQUEUEINFO */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_RT_SIGQUEUEINFO
DEFINE_COMPAT_SYSCALL3(errno_t, rt_sigqueueinfo,
                       pid_t, pid, signo_t, signo,
                       USER UNCHECKED compat_siginfo_t const *, uinfo) {
#ifdef CONFIG_USE_NEW_GROUP
	REF struct taskpid *target;
	struct taskpid *mypid = task_gettaskpid();
	siginfo_t info;
	if unlikely(pid <= 0)
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_RAISE_PID, pid);
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
#else /* CONFIG_USE_NEW_GROUP */
	REF struct task *target;
	siginfo_t info;
	if unlikely(pid <= 0)
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_RAISE_PID, pid);
	siginfo_from_compat_user(&info, signo, uinfo);
	target = pidns_lookuptask_srch(THIS_PIDNS, pid);
	FINALLY_DECREF_UNLIKELY(target);
	/* Don't allow sending arbitrary signals to other processes. */
	if ((info.si_code >= 0 || info.si_code == SI_TKILL) &&
	    (task_getprocess_of(target) != task_getprocess()))
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_RAISE_SIGINFO_BADCODE,
		      info.si_code);
	if (signo != 0) {
		if (!task_raisesignalprocess(target, &info))
			THROW(E_PROCESS_EXITED, task_getpid_of_s(target));
	}
	return -EOK;
#endif /* !CONFIG_USE_NEW_GROUP */
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_RT_SIGQUEUEINFO */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_RT_TGSIGQUEUEINFO
DEFINE_COMPAT_SYSCALL4(errno_t, rt_tgsigqueueinfo,
                       pid_t, pid, pid_t, tid, signo_t, signo,
                       USER UNCHECKED compat_siginfo_t const *, uinfo) {
#ifdef CONFIG_USE_NEW_GROUP
	siginfo_t info;
	REF struct task *target;
	struct taskpid *leader;
	struct taskpid *mypid = task_gettaskpid();
	if unlikely(pid <= 0)
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_RAISE_PID, pid);
	if unlikely(tid <= 0)
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_RAISE_TID, tid);
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
	if (taskpid_getnstid_s(leader, mypid->tp_ns) != pid)
		THROW(E_PROCESS_EXITED, pid);

	if (signo != 0) {
		if (!task_raisesignalthread(target, &info))
			THROW(E_PROCESS_EXITED, tid);
	}
	return -EOK;
#else /* CONFIG_USE_NEW_GROUP */
	siginfo_t info;
	REF struct task *target;
	struct task *leader;
	if unlikely(pid <= 0)
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_RAISE_PID, pid);
	if unlikely(tid <= 0)
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_RAISE_TID, tid);
	siginfo_from_compat_user(&info, signo, uinfo);
	target = pidns_lookuptask_srch(THIS_PIDNS, tid);
	FINALLY_DECREF_UNLIKELY(target);
	/* Don't allow sending arbitrary signals to other processes. */
	leader = task_getprocess_of(target);
	if ((info.si_code >= 0 || info.si_code == SI_TKILL) && leader != task_getprocess())
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_RAISE_SIGINFO_BADCODE,
		      info.si_code);
	/* Check if the thread-group ID matches that of the leader of the requested thread-group. */
	if (task_gettid_of_s(leader) != pid)
		THROW(E_PROCESS_EXITED, pid);
	if (signo != 0) {
		if (!task_raisesignalthread(target, &info))
			THROW(E_PROCESS_EXITED, task_gettid_of_s(target));
	}
	return -EOK;
#endif /* !CONFIG_USE_NEW_GROUP */
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
PRIVATE signo_t KCALL
signal_waitfor(CHECKED USER sigset_t const *uthese,
               CHECKED USER siginfo_t *uinfo,
               ktime_t abs_timeout) {
	sigset_t these;
	assert(!task_wasconnected());
	assert(PREEMPTION_ENABLED());
	memcpy(&these, uthese, sizeof(sigset_t));
	COMPILER_BARRIER();
	/* Make sure that we don't steal these signals */
	sigdelset(&these, SIGKILL);
	sigdelset(&these, SIGSTOP);
	COMPILER_WRITE_BARRIER();

	/* Since we may (very likely)  be waiting for signals that  are
	 * currently masked,  we need  to make  certain that  we  still
	 * receive notification when such a signal arrives, even though
	 * we're unable to handle it by "normal" means. */
	ATOMIC_OR(THIS_TASK->t_flags, TASK_FWAKEONMSKRPC);
	RAII_FINALLY { ATOMIC_AND(THIS_TASK->t_flags, ~TASK_FWAKEONMSKRPC); };
	for (;;) {
		struct pending_rpc *rpc;

		/* Disable preemption for interlocking with  sporadic
		 * wakeups send as the result of new RPCs being added
		 * to our thread's or process's pending lists. */
		PREEMPTION_DISABLE();

		/* Try to steal RPCs. */
		rpc = task_rpc_pending_steal_posix_signal(&these);
		if (rpc == NULL) {
			rpc = proc_rpc_pending_trysteal_posix_signal(&these);
			if (rpc == PROC_RPC_PENDING_TRYSTEAL_POSIX_SIGNAL_WOULDBLOCK) {
				struct process_pending_rpcs *proc_rpcs;
				PREEMPTION_ENABLE();
				/* Yield until the lock becomes available. */
				proc_rpcs = &THIS_PROCESS_RPCS;
				process_pending_rpcs_waitwrite(proc_rpcs);
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
                UNCHECKED USER sigset_t const *, uthese,
                UNCHECKED USER siginfo_t *, uinfo,
                UNCHECKED USER struct timespec32 const *, uts,
                size_t, sigsetsize) {
	syscall_slong_t result;
	ktime_t abs_timeout = KTIME_INFINITE;
	/* Validate user-structure pointers. */
	validate_readable(uthese, sigsetsize);
	validate_writable(uinfo, sizeof(siginfo_t));
	if (uts) {
		validate_readable(uts, sizeof(*uts));
		abs_timeout = relktime_from_user_rel(uts);
		if (abs_timeout != 0)
			abs_timeout += ktime();
	}
	result = (syscall_slong_t)signal_waitfor(uthese, uinfo,
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
                UNCHECKED USER sigset_t const *, uthese,
                UNCHECKED USER siginfo_t *, uinfo,
                UNCHECKED USER struct timespec64 const *, uts,
                size_t, sigsetsize)
#else /* __ARCH_WANT_SYSCALL_RT_SIGTIMEDWAIT64 */
DEFINE_SYSCALL4(syscall_slong_t, rt_sigtimedwait_time64,
                UNCHECKED USER sigset_t const *, uthese,
                UNCHECKED USER siginfo_t *, uinfo,
                UNCHECKED USER struct timespec64 const *, uts,
                size_t, sigsetsize)
#endif /* !__ARCH_WANT_SYSCALL_RT_SIGTIMEDWAIT64 */
{
	syscall_slong_t result;
	ktime_t abs_timeout = KTIME_INFINITE;
	/* Validate user-structure pointers. */
	validate_readable(uthese, sigsetsize);
	validate_writable(uinfo, sizeof(siginfo_t));
	if (uts) {
		validate_readable(uts, sizeof(*uts));
		abs_timeout = relktime_from_user_rel(uts);
		if (abs_timeout != 0)
			abs_timeout += ktime();
	}
	result = (syscall_slong_t)signal_waitfor(uthese, uinfo,
	                                         abs_timeout);
	if (!result)
		result = -EAGAIN; /* Posix says EAGAIN for this. */
	return result;
}
#endif /* __ARCH_WANT_SYSCALL_RT_SIGTIMEDWAIT64 || __ARCH_WANT_SYSCALL_RT_SIGTIMEDWAIT_TIME64 */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_RT_SIGTIMEDWAIT
DEFINE_COMPAT_SYSCALL4(syscall_slong_t, rt_sigtimedwait,
                       UNCHECKED USER compat_sigset_t const *, uthese,
                       UNCHECKED USER compat_siginfo_t *, uinfo,
                       UNCHECKED USER struct compat_timespec32 const *, uts,
                       size_t, sigsetsize) {
	syscall_slong_t result;
	siginfo_t info;
	ktime_t abs_timeout = KTIME_INFINITE;
	/* Validate user-structure pointers. */
	validate_readable(uthese, sigsetsize);
	validate_writable(uinfo, sizeof(siginfo_t));
	if (uts) {
		validate_readable(uts, sizeof(*uts));
		abs_timeout = relktime_from_user_rel(uts);
		if (abs_timeout != 0)
			abs_timeout += ktime();
	}
	result = (syscall_slong_t)signal_waitfor(uthese, &info,
	                                         abs_timeout);
	if (!result)
		result = -EAGAIN; /* Posix says EAGAIN for this. */
	else {
		siginfo_to_compat_siginfo(&info, uinfo);
	}
	return result;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_RT_SIGTIMEDWAIT */

#if (defined(__ARCH_WANT_COMPAT_SYSCALL_RT_SIGTIMEDWAIT64) || \
     defined(__ARCH_WANT_COMPAT_SYSCALL_RT_SIGTIMEDWAIT_TIME64))
#ifdef __ARCH_WANT_COMPAT_SYSCALL_RT_SIGTIMEDWAIT64
DEFINE_COMPAT_SYSCALL4(syscall_slong_t, rt_sigtimedwait64,
                       UNCHECKED USER compat_sigset_t const *, uthese,
                       UNCHECKED USER compat_siginfo_t *, uinfo,
                       UNCHECKED USER struct compat_timespec64 const *, uts,
                       size_t, sigsetsize)
#else /* __ARCH_WANT_COMPAT_SYSCALL_RT_SIGTIMEDWAIT64 */
DEFINE_COMPAT_SYSCALL4(syscall_slong_t, rt_sigtimedwait_time64,
                       UNCHECKED USER compat_sigset_t const *, uthese,
                       UNCHECKED USER compat_siginfo_t *, uinfo,
                       UNCHECKED USER struct compat_timespec64 const *, uts,
                       size_t, sigsetsize)
#endif /* !__ARCH_WANT_COMPAT_SYSCALL_RT_SIGTIMEDWAIT64 */
{
	syscall_slong_t result;
	siginfo_t info;
	ktime_t abs_timeout = KTIME_INFINITE;
	/* Validate user-structure pointers. */
	validate_readable(uthese, sigsetsize);
	validate_writable(uinfo, sizeof(siginfo_t));
	if (uts) {
		validate_readable(uts, sizeof(*uts));
		abs_timeout = relktime_from_user_rel(uts);
		if (abs_timeout != 0)
			abs_timeout += ktime();
	}
	result = (syscall_slong_t)signal_waitfor(uthese, &info,
	                                         abs_timeout);
	if (!result)
		result = -EAGAIN; /* Posix says EAGAIN for this. */
	else {
		siginfo_to_compat_siginfo(&info, uinfo);
	}
	return result;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_RT_SIGTIMEDWAIT64 || __ARCH_WANT_COMPAT_SYSCALL_RT_SIGTIMEDWAIT_TIME64 */





/************************************************************************/
/* rt_sigsuspend(), sigsuspend()                                        */
/************************************************************************/

#if (defined(__ARCH_WANT_SYSCALL_RT_SIGSUSPEND) || \
     defined(__ARCH_WANT_SYSCALL_SIGSUSPEND) ||    \
     defined(__ARCH_WANT_COMPAT_SYSCALL_SIGSUSPEND))
/* This function is also called from arch-specific, optimized syscall routers. */
INTERN ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) struct icpustate *FCALL
sys_sigsuspend_impl(struct icpustate *__restrict state,
                    struct rpc_syscall_info *__restrict sc_info,
                    size_t sigsetsize) {
	sigset_t not_these;
	USER UNCHECKED sigset_t const *unot_these;
	if unlikely(sigsetsize != sizeof(sigset_t)) {
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_SIGNAL_SIGSET_SIZE,
		      sigsetsize);
	}
	unot_these = (USER UNCHECKED sigset_t const *)sc_info->rsi_regs[0];
	validate_readable(unot_these, sizeof(sigset_t));
	memcpy(&not_these, unot_these, sizeof(sigset_t));

	/* These signals cannot be masked. (iow: _always_ wait for these signals) */
	sigdelset(&not_these, SIGSTOP);
	sigdelset(&not_these, SIGKILL);

	/* Indicate that we want to receive wake-ups for masked signals. */
	ATOMIC_OR(THIS_TASK->t_flags, TASK_FWAKEONMSKRPC);

	/* This will clear `TASK_FWAKEONMSKRPC', as well as
	 * perform a check for signals not in `these' which
	 * may have also appeared in the mean time prior to
	 * returning to user-space. */
	userexcept_sysret_inject_self();
again:
	TRY {
		/* The  normal implementation of the system call,
		 * except that `task_serve_with_sigmask' replaces
		 * calls to `task_serve()'
		 *
		 * In case of  `sigsuspend(2)`, the "normal"  implementation
		 * is `pause(2)`, which can simply be implemented like this: */
		for (;;) {
			PREEMPTION_DISABLE();
			if (task_serve_with_sigmask(&not_these))
				continue;
			task_sleep();
		}
	} EXCEPT {
		/* This function  only returns  normally
		 * when the syscall should be restarted. */
		state = userexcept_handler_with_sigmask(state, sc_info, &not_these);
		PERTASK_SET(this_exception_code, 1); /* Prevent internal fault */
		goto again;
	}
	__builtin_unreachable();
}
#endif /* ... */

#ifdef __ARCH_WANT_SYSCALL_RT_SIGSUSPEND
PRIVATE NONNULL((1)) void PRPC_EXEC_CALLBACK_CC
sys_rt_sigsuspend_rpc(struct rpc_context *__restrict ctx, void *UNUSED(cookie)) {
	if (ctx->rc_context != RPC_REASONCTX_SYSCALL)
		return;

	/* Do the actual system call. */
	ctx->rc_state = sys_sigsuspend_impl(ctx->rc_state, &ctx->rc_scinfo,
	                                    (size_t)ctx->rc_scinfo.rsi_regs[1]);

	/* Indicate that the system call has completed; further RPCs should never try to restart it! */
	ctx->rc_context = RPC_REASONCTX_SYSRET;
}

DEFINE_SYSCALL2(errno_t, rt_sigsuspend,
                USER UNCHECKED sigset_t const *, unot_these,
                size_t, sigsetsize) {
	(void)unot_these;
	(void)sigsetsize;

	/* Send an RPC to ourselves, so we can gain access to the user-space register state. */
	task_rpc_userunwind(&sys_rt_sigsuspend_rpc, NULL);
	__builtin_unreachable();
}
#endif /* __ARCH_WANT_SYSCALL_RT_SIGSUSPEND */

#ifdef __ARCH_WANT_SYSCALL_SIGSUSPEND
PRIVATE NONNULL((1)) void PRPC_EXEC_CALLBACK_CC
sys_sigsuspend_rpc(struct rpc_context *__restrict ctx, void *UNUSED(cookie)) {
	if (ctx->rc_context != RPC_REASONCTX_SYSCALL)
		return;

	/* Do the actual system call. */
	ctx->rc_state = sys_sigsuspend_impl(ctx->rc_state, &ctx->rc_scinfo, sizeof(sigset_t));

	/* Indicate that the system call has completed; further RPCs should never try to restart it! */
	ctx->rc_context = RPC_REASONCTX_SYSRET;
}

DEFINE_SYSCALL1(errno_t, sigsuspend,
                USER UNCHECKED sigset_t const *, unot_these) {
	(void)unot_these;

	/* Send an RPC to ourselves, so we can gain access to the user-space register state. */
	task_rpc_userunwind(&sys_sigsuspend_rpc, NULL);
	__builtin_unreachable();
}
#endif /* __ARCH_WANT_SYSCALL_SIGSUSPEND */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_SIGSUSPEND
PRIVATE NONNULL((1)) void PRPC_EXEC_CALLBACK_CC
sys_compat_sigsuspend_rpc(struct rpc_context *__restrict ctx, void *UNUSED(cookie)) {
	if (ctx->rc_context != RPC_REASONCTX_SYSCALL)
		return;

	/* Do the actual system call. */
	ctx->rc_state = sys_sigsuspend_impl(ctx->rc_state, &ctx->rc_scinfo, sizeof(compat_sigset_t));

	/* Indicate that the system call has completed; further RPCs should never try to restart it! */
	ctx->rc_context = RPC_REASONCTX_SYSRET;
}

DEFINE_COMPAT_SYSCALL1(errno_t, sigsuspend,
                       USER UNCHECKED compat_sigset_t const *, unot_these) {
	(void)unot_these;

	/* Send an RPC to ourselves, so we can gain access to the user-space register state. */
	task_rpc_userunwind(&sys_compat_sigsuspend_rpc, NULL);
	__builtin_unreachable();
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_SIGSUSPEND */

DECL_END

#endif /* !GUARD_KERNEL_SRC_SCHED_POSIX_SIGNAL_C */
