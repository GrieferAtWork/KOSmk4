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
#ifdef __INTELLISENSE__
#include "task-clone.c"
#define DEFINE_task_clone_thrdpid
//#define DEFINE_task_clone_procpid
#endif /* __INTELLISENSE__ */

#include <kos/nopf.h>

#if (defined(DEFINE_task_clone_thrdpid) + \
     defined(DEFINE_task_clone_procpid)) != 1
#error "Must #define exactly one of these"
#endif /* ... */

DECL_BEGIN

#ifdef DEFINE_task_clone_thrdpid
PRIVATE NONNULL((1, 2)) void FCALL
task_clone_thrdpid(struct task *__restrict result,
                   struct task *__restrict caller,
                   uint64_t clone_flags,
                   USER UNCHECKED pid_t *parent_tidptr)
#define LOCAL_IS_THRD
#else /* DEFINE_task_clone_thrdpid */
PRIVATE NONNULL((1, 2)) void FCALL
task_clone_procpid(struct task *__restrict result,
                   struct task *__restrict caller,
                   uint64_t clone_flags,
                   USER UNCHECKED pid_t *parent_tidptr)
#define LOCAL_IS_PROC
#endif /* !DEFINE_task_clone_thrdpid */
{
	/* Figure out which PID namespace(s) the new thread should appear in. */
	REF struct taskpid *result_pid;
	struct taskpid *caller_pid;
#ifdef LOCAL_IS_PROC
	struct procctl *parent_ctl;
	struct procctl *result_ctl;
#else /* LOCAL_IS_PROC */
	struct procctl *caller_ctl;
#endif /* !LOCAL_IS_PROC */
	REF struct task *parent_proc;
	struct taskpid *parent_pid;
#ifdef CONFIG_HAVE_USERPROCMASK
	sigset_t caller_sigmask;
	bool have_caller_sigmask = false;
#endif /* CONFIG_HAVE_USERPROCMASK */

	/* Figure out the caller's PID relationship */
	caller_pid = task_gettaskpid_of(caller);

	/* Allocate a PID descriptor for the new thread. */
#ifdef LOCAL_IS_THRD
	if unlikely(clone_flags & CLONE_NEWPID) {
		/* CLONE_THREAD must imply !CLONE_NEWPID */
		THROW(E_INVALID_ARGUMENT_BAD_FLAG_COMBINATION,
		      E_INVALID_ARGUMENT_CONTEXT_CLONE_THREAD_WITH_NEWPID,
		      (syscall_ulong_t)clone_flags,
		      CLONE_THREAD | CLONE_NEWPID,
		      CLONE_THREAD | CLONE_NEWPID);
	}
	result_pid        = _taskpid_alloc(caller_pid->tp_ns);
	result_pid->tp_ns = caller_pid->tp_ns; /* Incref'd later */
#endif /* LOCAL_IS_THRD */

#ifdef LOCAL_IS_PROC
	if unlikely(clone_flags & CLONE_NEWPID) {
		REF struct pidns *ns;
		ns = pidns_alloc(caller_pid->tp_ns);
		TRY {
			result_pid = _taskpid_alloc(ns);
		} EXCEPT {
			pidns_destroy(ns);
			RETHROW();
		}
		result_pid->tp_ns = ns; /* Inherit reference */
	} else {
		result_pid        = _taskpid_alloc(caller_pid->tp_ns);
		result_pid->tp_ns = incref(caller_pid->tp_ns);
	}
#endif /* !LOCAL_IS_PROC */

#ifdef LOCAL_IS_THRD
again_determine_parent:
	parent_pid = taskpid_getprocpid(caller_pid);
	caller_ctl = taskpid_getprocctl(caller_pid);
	assert(caller_ctl == taskpid_getprocctl(parent_pid));
	parent_proc = taskpid_gettask(parent_pid);
	if unlikely(!parent_proc || (ATOMIC_READ(parent_proc->t_flags) & (TASK_FTERMINATING |
	                                                                  TASK_FTERMINATED))) {
		/* Current process has exited. */
		xdecref(parent_proc);
		_taskpid_free(result_pid);
		_task_serve(); /* Serve main thread's exit RPC */
		/* Really shouldn't get here! */
		THROW(E_EXIT_THREAD, ATOMIC_READ(parent_pid->tp_status));
	}
	result_pid->tp_proc = parent_pid; /* Incref'd later */
	result_pid->tp_pctl = caller_ctl;
	if (clone_flags & CLONE_DETACHED)
		result->t_flags |= TASK_FDETACHED; /* Auto-reap on exit */
#endif /* LOCAL_IS_THRD */

#ifdef LOCAL_IS_PROC
	/* Allocate a new process controller. */
	TRY {
		result_ctl = _procctl_alloc();
	} EXCEPT {
		decref_unlikely(result_pid->tp_ns);
		_taskpid_free(result_pid);
		RETHROW();
	}

	/* Allocate process information. */
#ifndef CONFIG_NO_SMP
	atomic_lock_init(&result_ctl->pc_thrds_lock);
#endif /* !CONFIG_NO_SMP */
	LIST_INIT(&result_ctl->pc_thrds_list);
	atomic_rwlock_init(&result_ctl->pc_chlds_lock);
	LIST_INIT(&result_ctl->pc_chlds_list);
	sig_init(&result_ctl->pc_chld_changed);
	atomic_rwlock_init(&result_ctl->pc_sig_lock);
	SLIST_INIT(&result_ctl->pc_sig_list);
	result_ctl->pc_sig_pend = 0;
	sig_init(&result_ctl->pc_sig_more);

	/* Select who should be the process's parent. */
again_determine_parent:
	if (clone_flags & CLONE_DETACHED) {
		/* Launch in detached state, meaning /bin/init is parent. */
use_boottask_as_parent:
		parent_proc = incref(&boottask);
	} else if (clone_flags & CLONE_PARENT) {
		/* Re-use parent of calling process as parent of child process */
		parent_proc = taskpid_getparentprocess(caller_pid);
		if unlikely(ATOMIC_READ(parent_proc->t_flags) & (TASK_FTERMINATING |
		                                                 TASK_FTERMINATED)) {
			/* The calling process's parent has already terminated.
			 * -> Simply use `boottask' instead, emulating what would
			 *    have been done  by `parent_proc' in  `task_exit()'. */
			decref_unlikely(parent_proc);
			goto use_boottask_as_parent;
		}
	} else {
		/* Using calling process as parent. */
		parent_proc = taskpid_gettask(taskpid_getprocpid(caller_pid));
		if unlikely(!parent_proc || (ATOMIC_READ(parent_proc->t_flags) & (TASK_FTERMINATING |
		                                                                  TASK_FTERMINATED))) {
			/* Current process has exited. */
			xdecref(parent_proc);
			_procctl_free(result_ctl);
			decref_unlikely(result_pid->tp_ns);
			_taskpid_free(result_pid);
			_task_serve(); /* Serve main thread's exit RPC */
			/* Really shouldn't get here! */
			THROW(E_EXIT_THREAD, ATOMIC_READ(taskpid_getprocpid(caller_pid)->tp_status));
		}
	}
	parent_pid = task_gettaskpid_of(parent_proc);
	arref_init(&result_ctl->pc_parent, parent_proc); /* Inherit reference (upon success) */
	result_pid->tp_proc = result_pid;                /* New process */
	result_pid->tp_pctl = result_ctl;                /* Process controller */

	/* Owning process controller  (either current process  for
	 * `CLONE_THREAD', or parent process for `!CLONE_THREAD'). */
	parent_ctl = taskpid_getprocctl(parent_pid);

	/* NOTE: To jump to `again_determine_parent' from this point forth, do:
	 *  >> decref_unlikely(parent_proc);
	 *  >> goto again_determine_parent; */
#endif /* LOCAL_IS_PROC */

	/* Fill in simple fields. */
	result_pid->tp_refcnt = 2; /* +1: this_taskpid, +1: procctl_chlds_insert/procctl_thrds_insert */
	awref_init(&result_pid->tp_thread, result);
	sig_init(&result_pid->tp_changed);
	result_pid->tp_status = 0;
	result_pid->tp_SIGCLD = clone_flags & CSIGNAL;
	if (result_pid->tp_SIGCLD == 0)
		result_pid->tp_SIGCLD = SIGCLD;
	FORTASK(result, this_taskpid) = result_pid; /* Inherit reference */

	TRY {
#ifdef LOCAL_IS_THRD
		pflag_t preemption_was;
#endif /* LOCAL_IS_THRD */
#ifdef LOCAL_IS_PROC
		REF struct procgrp *result_grp;
#endif /* LOCAL_IS_PROC */

		/* Acquire a lock to all PID namespaces, so we can assign PIDs */
		struct pidns *ns;
again_lock_ns:
		while unlikely((ns = pidns_trywriteall(result_pid->tp_ns)) != NULL)
			pidns_waitwrite(ns);

		/* Allocate PIDs for `result_pid' within all namespaces it should appear in. */
#ifdef PIDNS_NEXTPID_CAN_RETURN_MINUS_ONE
		if (!pidns_allocpids(result_pid)) {
err_pidns_allocpids_failed:
			pidns_endwriteall(result_pid->tp_ns);
			THROW(E_BADALLOC); /* XXX: Custom error sub-class */
		}
#else /* PIDNS_NEXTPID_CAN_RETURN_MINUS_ONE */
		pidns_allocpids(result_pid);
#endif /* !PIDNS_NEXTPID_CAN_RETURN_MINUS_ONE */

		if (clone_flags & CLONE_PARENT_SETTID) {
			/* Write-back  the child TID to the parent  process. Because this is a memory
			 * access, we have to be very careful when it comes to writing to VIO memory.
			 * As  such, we have to interlock this write with all of locks above, as well
			 * as the allocation of (at least) the PID within the initial namespace. */
			pid_t ctid;
			if unlikely(ADDR_ISKERN(parent_tidptr)) {
				pidns_endwriteall(result_pid->tp_ns);
				THROW(E_SEGFAULT_UNMAPPED, parent_tidptr,
				      E_SEGFAULT_CONTEXT_USERCODE | E_SEGFAULT_CONTEXT_WRITING);
			}
			ctid = taskpid_getnstid(result_pid, caller_pid->tp_ns);
again_write_ctid_to_parent_tidptr:
			if (!write_nopf(parent_tidptr, ctid)) {
				pid_t new_ctid;
				/* Complicated case: writing to the user-given address faults. - This can
				 * happen for VIO memory,  if the pointer is  actually faulty, or if  the
				 * associated page simply hasn't been allocated, yet.
				 *
				 * Whatever the case be, we have to release locks, repeat the write, then
				 * re-acquire locks and allocate PIDs again. - Afterwards, we check if we
				 * were  able to allocate the `ctid', and if not, we try to write the new
				 * value back to user-space once again.
				 *
				 * This cycle continues until the ctid written in a previous cycle matches
				 * what would have to be written in the next, the calling thread  receives
				 * an interrupt, or the `write_nopf()' above succeeds. */
				pidns_endwriteall(result_pid->tp_ns);

				/* Do a proper write, which is allowed to fault or be VIO. */
				ATOMIC_WRITE(*parent_tidptr, ctid);
				task_serve();

				/* Re-acquire locks. */
				while unlikely((ns = pidns_trywriteall(result_pid->tp_ns)) != NULL)
					pidns_waitwrite(ns);

				/* Allocate PIDs for `result_pid' within all namespaces it should appear in. */
#ifdef PIDNS_NEXTPID_CAN_RETURN_MINUS_ONE
				if (!pidns_allocpids(result_pid))
					goto err_pidns_allocpids_failed;
#else /* PIDNS_NEXTPID_CAN_RETURN_MINUS_ONE */
				pidns_allocpids(result_pid);
#endif /* !PIDNS_NEXTPID_CAN_RETURN_MINUS_ONE */

				/* Check if we were able  to allocate the same  TID.
				 * If we were, then we also know that the same value
				 * has previously been written to user-space! */
				new_ctid = taskpid_getnstid(result_pid, caller_pid->tp_ns);
				if unlikely(ctid != new_ctid) {
					ctid = new_ctid;
					goto again_write_ctid_to_parent_tidptr;
				}
			}
		}

		/* Determine + lock the process group in which the new process should appear. */
#ifdef LOCAL_IS_PROC
again_determine_group:
		result_grp = taskpid_getprocgrp(caller_pid);
		if (!procgrp_memb_trywrite(result_grp)) {
			pidns_endwriteall(result_pid->tp_ns);
			procgrp_memb_waitwrite(result_grp);
			decref_unlikely(result_grp);
			goto again_lock_ns;
		}
		COMPILER_READ_BARRIER();
		/* Ensure that `result_grp' is still correct */
		if unlikely(result_grp != taskpid_getprocgrpptr(caller_pid)) {
			procgrp_memb_endwrite(result_grp);
			goto again_determine_group;
		}
		arref_init(&result_ctl->pc_grp, result_grp); /* Inherit reference (upon success) */
		/*result_ctl->pc_grpmember = ...;*/          /* Initialized below */
#endif /* LOCAL_IS_PROC */


#ifdef LOCAL_IS_PROC
		/* Lock the parent process's child list. */
		if (!procctl_chlds_trywrite(parent_ctl)) {
			_procgrp_memb_endwrite(result_grp);
			pidns_endwriteall(result_pid->tp_ns);
			procgrp_memb_reap(result_grp);
			decref_unlikely(result_grp);
			procctl_chlds_waitwrite(parent_ctl);
			goto again_lock_ns;
		}
#endif /* LOCAL_IS_PROC */

#ifdef LOCAL_IS_THRD
		/* Lock the current process's thread list. */
		preemption_was = PREEMPTION_PUSHOFF();
#ifndef CONFIG_NO_SMP
		if (!procctl_thrds_tryacquire_nopr(caller_ctl)) {
			task_pause();
			if (!procctl_thrds_tryacquire_nopr(caller_ctl)) {
				pidns_endwriteall(result_pid->tp_ns);
				while (!procctl_thrds_available(caller_ctl))
					task_pause();
				goto again_lock_ns;
			}
		}
#endif /* !CONFIG_NO_SMP */
#endif /* LOCAL_IS_THRD */

#ifdef LOCAL_IS_PROC
#define LOCAL_RELEASE_ALL_LOCKS()              \
		(_procctl_chlds_endwrite(parent_ctl),  \
		 _procgrp_memb_endwrite(result_grp),   \
		 pidns_endwriteall(result_pid->tp_ns), \
		 procctl_chlds_reap(parent_ctl),       \
		 procgrp_memb_reap(result_grp))
#else /* LOCAL_IS_PROC */
#define LOCAL_RELEASE_ALL_LOCKS()                \
		(procctl_thrds_release_nopr(caller_ctl), \
		 PREEMPTION_POP(preemption_was),         \
		 pidns_endwriteall(result_pid->tp_ns))
#endif /* !LOCAL_IS_PROC */



		/* Verify that we're still allowed to add threads / child processes to the parent
		 * process. If we're no longer allowed to  do so, then jump back to  re-determine
		 * the  parent process to-be used (if the then-determined process has terminated,
		 * and /bin/init cannot be used, clone(2) will fail) */
		if unlikely(ATOMIC_READ(parent_proc->t_flags) & (TASK_FTERMINATED |
		                                                 TASK_FTERMINATING)) {
			LOCAL_RELEASE_ALL_LOCKS();
#ifdef LOCAL_IS_PROC
			decref_unlikely(result_grp);
#endif /* LOCAL_IS_PROC */
			decref_unlikely(parent_proc);
			goto again_determine_parent;
		}


		/* Whilst interlocked with all of the locks needed to make a new thread
		 * globally visible, check if our own  thread might need to serve  some
		 * RPCs  right now. -- If it does,  then we mustn't actually go through
		 * with creation of a  new thread, since there  might be an RPC  that's
		 * meant for us to terminate,  and might originate from something  like
		 * a process-group-wide broadcast of a SIGINT.
		 *
		 * When something like that happens, we mustn't be allowed to add a new
		 * process to the process group, which would then no longer be apart of
		 * the original set of processes that received the SIGINT.
		 *
		 * Furthermore,  this is a special case in  that we can't solely rely on
		 * the presence of `TASK_FRPC' to indicate the presence of pending RPCs,
		 * which  in the case of process-wide RPCs might get set asynchronously,
		 * in which case there can be a process-directed RPC pending right  now,
		 * which is also meant to kill,  even though our `TASK_FRPC' flag  isn't
		 * set right now.
		 *
		 * Because of this, we need a custom way of checking for signal, which
		 * we facilitate by checking for TASK_FRPC, and even if that one's not
		 * set, we also go through signals send to our process in order to see
		 * if there are any that aren't marked by the calling thread.
		 *
		 * FIXME: What about a process-directed RPC with the intend of killing the
		 *        targeted process, but then one of the process's thread took that
		 *        RPC  and began handling it (so we're  no longer able to see it).
		 *        Now handling of the RPCs hasn't  finished yet, but once it  has,
		 *        the receiving thread will cause  our process to terminate,  only
		 *        at that point it's too late because we ended up creating the new
		 *        process...
		 * Solution: There needs to  be a  way to track  process-directed RPCs  until
		 *           after their kernel-side has  completed. This includes RPCs  that
		 *           throw E_EXIT_PROCESS or E_EXIT_THREAD, which may only be thought
		 *           of as completed _AFTER_ they set `TASK_FTERMINATING' within  the
		 *           receiving thread. */
		if (ATOMIC_READ(caller->t_flags) & TASK_FRPC) {
release_locks_and_do_task_serve:
			LOCAL_RELEASE_ALL_LOCKS();
#ifdef LOCAL_IS_PROC
			decref_unlikely(result_grp);
#endif /* LOCAL_IS_PROC */
			_task_serve();
			goto again_lock_ns;
		}

		/* Check for unmasked process-directed signals.
		 * Note that for this, we need yet another lock, which has to be held
		 * at the same time as all of the other locks in order to ensure that
		 * everything operates interlocked! */
		{
#ifndef LOCAL_IS_THRD
			struct procctl *caller_ctl = taskpid_getprocctl(caller_pid);
#endif /* !LOCAL_IS_THRD */
			struct pending_rpc *rpc;
			struct pending_rpc_slist pending;
			uint32_t pending_bitset;
			pending.slh_first = ATOMIC_READ(caller_ctl->pc_sig_list.slh_first);
			pending_bitset    = ATOMIC_READ(caller_ctl->pc_sig_pend);
			if (pending.slh_first != NULL || pending_bitset != 0) {
				if unlikely((pending.slh_first == THIS_RPCS_TERMINATED) ||
				            (pending_bitset & 1)) {
release_locks_and_force_do_task_serve:
					ATOMIC_OR(caller->t_flags, TASK_FRPC);
					goto release_locks_and_do_task_serve;
				}

				/* Lock pending signals and check if we need to handle any of them. */
				if (!procctl_sig_tryread(caller_ctl)) {
					LOCAL_RELEASE_ALL_LOCKS();
#ifdef LOCAL_IS_PROC
					decref_unlikely(result_grp);
#endif /* LOCAL_IS_PROC */
					procctl_sig_waitread(caller_ctl);
					_task_serve();
					goto again_lock_ns;
				}
				pending.slh_first = ATOMIC_READ(caller_ctl->pc_sig_list.slh_first);
				pending_bitset    = ATOMIC_READ(caller_ctl->pc_sig_pend);
				if unlikely((pending.slh_first == THIS_RPCS_TERMINATED) ||
				            (pending_bitset & 1)) {
sig_endread_and_release_locks_and_force_do_task_serve:
					procctl_sig_endread(caller_ctl);
					goto release_locks_and_force_do_task_serve;
				}
				SLIST_FOREACH (rpc, &pending, pr_link) {
					int status;
					status = sigmask_ismasked_nopf(_RPC_GETSIGNO(rpc->pr_flags));
					if (status == SIGMASK_ISMASKED_NOPF_NO)
						goto sig_endread_and_release_locks_and_force_do_task_serve; /* Unmasked, pending RPC! */
#ifdef CONFIG_HAVE_USERPROCMASK
					if (status != SIGMASK_ISMASKED_NOPF_FAULT)
						continue;
					if (!have_caller_sigmask) {
						/* Copy the calling thread's userprocmask so we can use that one! */
						USER CHECKED struct userprocmask *um;
						USER UNCHECKED sigset_t *umask;
						size_t umasksize;
unlock_everything_and_do_load_userprocmask:
						_procctl_sig_endread(caller_ctl);
						LOCAL_RELEASE_ALL_LOCKS();
#ifdef LOCAL_IS_PROC
						decref_unlikely(result_grp);
#endif /* LOCAL_IS_PROC */
						procctl_sig_reap(caller_ctl);
						um = PERTASK_GET(this_userprocmask_address);
						COMPILER_BARRIER();
						umask     = um->pm_sigmask;
						umasksize = um->pm_sigsize;
						COMPILER_READ_BARRIER();
						validate_readable(umask, umasksize);
						if (umasksize > sizeof(sigset_t))
							umasksize = sizeof(sigset_t);
						memset(mempcpy(&caller_sigmask, umask, umasksize),
						       0xff, sizeof(sigset_t) - umasksize);
						sigdelset(&caller_sigmask, SIGKILL);
						sigdelset(&caller_sigmask, SIGSTOP);
						have_caller_sigmask = true;
						goto again_lock_ns;
					}
					if (!sigismember(&caller_sigmask, _RPC_GETSIGNO(rpc->pr_flags)))
						goto sig_endread_and_release_locks_and_force_do_task_serve; /* Unmasked, pending RPC! */
#endif /* CONFIG_HAVE_USERPROCMASK */
				}
				if (pending_bitset != 0) {
					signo_t signo;
					for (signo = 1; signo <= 31; ++signo) {
						int status;
						if (!(pending_bitset & ((uint32_t)1 << signo)))
							continue;
						status = sigmask_ismasked_nopf(signo);
						if (status == SIGMASK_ISMASKED_NOPF_NO)
							goto sig_endread_and_release_locks_and_force_do_task_serve; /* Unmasked, pending RPC! */
#ifdef CONFIG_HAVE_USERPROCMASK
						if (status != SIGMASK_ISMASKED_NOPF_FAULT)
							continue;
						if (!have_caller_sigmask)
							goto unlock_everything_and_do_load_userprocmask;
						if (!sigismember(&caller_sigmask, signo))
							goto sig_endread_and_release_locks_and_force_do_task_serve; /* Unmasked, pending RPC! */
#endif /* CONFIG_HAVE_USERPROCMASK */
					}
				}
				procctl_sig_endread(caller_ctl);
			} /* if (pending.slh_first != NULL) */

		}     /* Scope */

		/* ========== Point of no return: From here on, we'll be making the thread visible! */

#ifdef LOCAL_IS_THRD
		/* Construct missing references */
		incref(result_pid->tp_ns);
		incref(result_pid->tp_proc);
#endif /* !LOCAL_IS_THRD */

		/* Insert `result_pid' into all of the PID namespaces it should appear in. */
		ns = result_pid->tp_ns;
		do {
			pidns_insertpid(ns, result_pid);
		} while ((ns = ns->pn_par) != NULL);

#ifdef LOCAL_IS_PROC
		/* Add process into its associated process group. */
		procgrp_memb_insert(result_grp, result_pid); /* Initializes `pc_grpmember' */

		/* Add process to its parent's list of child processes. */
		procctl_chlds_insert(parent_ctl, result_pid); /* Initializes `tp_parsib' */
#endif /* LOCAL_IS_PROC */

#ifdef LOCAL_IS_THRD
		/* Add thread to main process's thread list. */
		procctl_thrds_insert(caller_ctl, result_pid); /* Initializes `tp_parsib' */
#endif /* LOCAL_IS_THRD */

		/* Insert the new task into its mman's thread-list */
#ifdef LOCAL_IS_THRD
		mman_threadslock_acquire_nopr(result->t_mman); /* SMP-lock, so nesting is allowed! */
		LIST_INSERT_HEAD(&result->t_mman->mm_threads, result, t_mman_tasks);
		mman_threadslock_release_nopr(result->t_mman);
#else /* LOCAL_IS_THRD */
		mman_threadslock_acquire(result->t_mman); /* SMP-lock, so nesting is allowed! */
		LIST_INSERT_HEAD(&result->t_mman->mm_threads, result, t_mman_tasks);
		mman_threadslock_release(result->t_mman);
#endif /* !LOCAL_IS_THRD */

		/* Release all locks. */
#ifdef LOCAL_IS_PROC
		incref(parent_pid); /* Needed for `sig_broadcast(&parent_ctl->pc_chld_changed);' */
#endif /* LOCAL_IS_PROC */
		LOCAL_RELEASE_ALL_LOCKS();
#undef LOCAL_RELEASE_ALL_LOCKS
	} EXCEPT {
#ifdef LOCAL_IS_PROC
		_procctl_free(result_ctl);
		decref_unlikely(result_pid->tp_ns);
#endif /* LOCAL_IS_PROC */
		decref_unlikely(parent_proc);
		_taskpid_free(result_pid);
		DBG_memset(&FORTASK(result, this_taskpid), 0xcc,
		           sizeof(FORTASK(result, this_taskpid)));
		RETHROW();
	}

#ifdef LOCAL_IS_PROC
	/* Indicate to the parent process that its list of children has changed. */
	sig_broadcast(&parent_ctl->pc_chld_changed);
	decref_unlikely(parent_pid);
#endif /* LOCAL_IS_PROC */

#ifdef LOCAL_IS_THRD
	/* Indicate to the current process that its list of threads has changed. */
	sig_broadcast(&caller_ctl->pc_chld_changed);
	decref_unlikely(parent_proc);
#endif /* LOCAL_IS_THRD */
}

#undef LOCAL_IS_THRD
#undef LOCAL_IS_PROC

DECL_END

#undef DEFINE_task_clone_thrdpid
#undef DEFINE_task_clone_procpid
