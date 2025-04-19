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
#ifndef GUARD_KERNEL_SRC_SCHED_GROUP_C
#define GUARD_KERNEL_SRC_SCHED_GROUP_C 1
#define __WANT_PROCGRP__pgr_lop
#define _KOS_SOURCE 1
#define _GNU_SOURCE 1
#define _TIME64_SOURCE 1

#include <kernel/compiler.h>

#include <dev/tty.h>
#include <kernel/except.h>
#include <kernel/malloc.h>
#include <kernel/mman/mfile.h>
#include <kernel/syscall.h>
#include <kernel/user.h>
#include <sched/group.h>
#include <sched/pid.h>
#include <sched/sig.h>
#include <sched/sigaction.h>
#include <sched/task.h>

#include <hybrid/sched/atomic-lock.h>
#include <hybrid/sched/atomic-rwlock.h>
#include <hybrid/sequence/list.h>

#include <bits/os/rusage-convert.h>
#include <bits/os/rusage.h>
#include <compat/config.h>
#include <kos/aref.h>
#include <kos/except.h>
#include <kos/except/reason/illop.h>
#include <kos/except/reason/inval.h>
#include <kos/lockop.h>
#include <kos/types.h>
#include <sys/wait.h>

#include <assert.h>
#include <atomic.h>
#include <errno.h>
#include <signal.h>
#include <stddef.h>
#include <string.h>

#ifdef __ARCH_HAVE_COMPAT
#include <compat/bits/os/rusage-convert.h>
#include <compat/bits/os/rusage.h>
#include <compat/bits/os/siginfo-convert.h>
#include <compat/bits/os/siginfo.h>
#include <compat/bits/types.h>
#include <compat/kos/types.h>
#include <compat/signal.h>
#endif /* __ARCH_HAVE_COMPAT */

DECL_BEGIN

/************************************************************************/
/* PROCESS GROUP                                                        */
/************************************************************************/
PRIVATE NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL procgrp_remove_from_ns)(struct procgrp *__restrict self,
                                      struct pidns *__restrict ns) {
	struct procgrp *removed;
	pid_t nspid;
	nspid   = _procgrp_slot_getpidno(self->pgr_pids[ns->pn_ind]);
	removed = pidns_grpremove(ns, nspid);
	assertf(removed == self,
	        "Wrong procgrp removed from %p:\n"
	        "removed = %p\n"
	        "self    = %p\n",
	        ns, removed, self);
	(void)removed;
}

/* Remove `self' from all associated namespaces (and decref the  top-most
 * namespace), before using `_procgrp_free()' to free the procgrp object. */
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL procgrp_remove_from_namespaces_and_free)(struct procgrp *__restrict self);


PRIVATE NOBLOCK NONNULL((1, 2)) void
NOTHROW(LOCKOP_CC pidns_removegrp_postlop)(Tobpostlockop(pidns) *__restrict self,
                                           struct pidns *__restrict obj) {
	struct procgrp *me;
	me = container_of(self, struct procgrp, _pgr_plop);
	assert(me->pgr_ns == obj);
	decref_nokill(obj); /* *_nokill, because caller is still holding a reference */
	me->pgr_ns = obj->pn_par;
	if (me->pgr_ns) {
		/* Keep removing `self' from recursive namespaces. */
		incref(me->pgr_ns); /* Inherited by `procgrp_remove_from_namespaces_and_free' */
		procgrp_remove_from_namespaces_and_free(me);
	} else {
		/* Free the procgrp descriptor. */
		_procgrp_free(me);
	}
}

PRIVATE NOBLOCK NONNULL((1, 2)) Tobpostlockop(pidns) *
NOTHROW(LOCKOP_CC pidns_removegrp_lop)(Toblockop(pidns) *__restrict self,
                                       struct pidns *__restrict obj) {
	struct procgrp *me;
	me = container_of(self, struct procgrp, _pgr_lop);
	assert(me->pgr_ns == obj);

	/* Remove from the just-locked namespace. */
	procgrp_remove_from_ns(me, obj);

	/* Do the rest of the accounting work in a post-lockop */
	me->_pgr_plop.oplo_func = &pidns_removegrp_postlop;
	return &me->_pgr_plop;
}


/* Remove `self' from all associated namespaces (and decref the  top-most
 * namespace), before using `_procgrp_free()' to free the procgrp object. */
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL procgrp_remove_from_namespaces_and_free)(struct procgrp *__restrict self) {
	struct pidns *par, *ns;
	/* Remove this procgrp from its pidns, if necessary via lockops */
	ns = self->pgr_ns;
	assert(ns);
again_lock_ns:
	if (pidns_trywrite(ns)) {
		procgrp_remove_from_ns(self, ns);
		pidns_endwrite(ns);
	} else {
		/* Must use a lock-op */
		self->_pgr_lop.olo_func = &pidns_removegrp_lop;
		incref(ns);
		oblockop_enqueue(&ns->pn_lops, &self->_pgr_lop);
		_pidns_reap(ns);
		decref_unlikely(ns);
		return;
	}
	par = ns->pn_par;
	xincref(par);
	decref_unlikely(ns);

	/* Recursively remove from parenting namespaces. */
	if unlikely(par) {
		self->pgr_ns = ns = par;
		goto again_lock_ns;
	}

	/* Free the procgrp descriptor. */
	_procgrp_free(self);
}

/* Destroy the given procgrp. */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL procgrp_destroy)(struct procgrp *__restrict self) {
	struct procsession *session;
	REF struct ttydev *ctty;
	_procgrp_memb_reap(self);
	assert(self->pgr_session == self->pgr_sleader->pgr_session);
	assertf(LIST_EMPTY(&self->pgr_memb_list),
	        "If this wasn't the case, `LIST_FIRST(pgr_memb_list)->tp_pctl->pc_grp' "
	        "should have kept us alive!");

	/* If we are the session tty's foreground process  group,
	 * then relinquish associated permissions by clearing the
	 * associated pointer. */
	session = self->pgr_session;
	ctty    = axref_get(&session->ps_ctty);
	if (ctty != NULL)
		awref_cmpxch(&ctty->t_fproc, self, NULL);

	if (self->pgr_sleader == self) {
		/* Destroy the associated session object. (and
		 * clear the tty's controlling process  group) */
		if (ctty) {
			assertf(awref_ptr(&ctty->t_cproc) == self,
			        "But this would mean that this isn't "
			        "actually our controlling terminal...");
			awref_clear(&ctty->t_cproc);
		}

		/* Destroy the session object (since it's owned by the
		 * session leader process group, which in turn: is us) */
		_procsession_destroy(session);
	} else {
		assertf(!ctty || awref_ptr(&ctty->t_cproc) != self,
		        "But this would mean we were the session leader...");

		/* Drop our reference from the session leader process group. */
		decref_unlikely(self->pgr_sleader);
	}
	xdecref_unlikely(ctty);

	/* Remove the process group from all associated PID namespaces,
	 * as well as free the process group descriptor once  finished. */
	procgrp_remove_from_namespaces_and_free(self);
}


/* Check if a given process group is considered "orphaned" (as per
 * posix's  definition  of what  an  "Orphaned Process Group" is):
 * """
 *    A process group in which the parent of every member is either itself
 *    a member of the  group or is  not a member  of the group's  session.
 * """
 * NOTE: The caller must be holding `procgrp_memb_read()' */
PUBLIC NOBLOCK WUNUSED NONNULL((1)) bool
NOTHROW(FCALL procgrp_orphaned)(struct procgrp const *__restrict self) {
	struct taskpid *member;
	FOREACH_procgrp_memb(member, self) {
		REF struct task *parent;
		REF struct procgrp *pargrp;
		struct procsession *parses;
		parent = taskpid_getparentprocess(member);
		pargrp = task_getprocgrp_of(parent);
		decref_unlikely(parent);
		if (pargrp == self) {
			/* Also a group member --> doesn't indicate non-orphaned */
			decref_nokill(pargrp);
			continue;
		}
		parses = pargrp->pgr_session;
		decref_unlikely(pargrp);
		if (parses != self->pgr_session) {
			/* Not member of our session --> doesn't indicate non-orphaned */
			continue;
		}
		return false;
	}
	return true;
}





/************************************************************************/
/* PROCESS CONTROL                                                      */
/************************************************************************/
INTDEF struct taskpid asyncwork_pid;
INTDEF struct taskpid boottask_pid;

/* Session used by `procctl_boottask' (and consequently also by `/bin/init') */
PUBLIC struct procsession boottask_procsession = {
	.ps_ctty = AXREF_INIT(NULL), /* /bin/init doesn't have a controlling terminal at the start. */
};

/* Special process group with `pgid == 0'  used for kernel threads (and  /bin/init)
 * Because we use  `pgid == 0', `setpgid(2)'  cannot be  used to  join this  group,
 * since passing it `0' as the target process group ID is an alias for `getpid(2)'. */
PUBLIC struct procgrp boottask_procgrp = {
	.pgr_refcnt = 2, /* +1: boottask_procgrp, +1: boottask_procctl.pc_grp */
	{{
		.pgr_sleader = &boottask_procgrp,     /* The process group of /bin/init is also the initial session leader. */
		.pgr_session = &boottask_procsession, /* *ditto* */
	}},
	.pgr_memb_lops = SLIST_HEAD_INITIALIZER(boottask_procgrp.pgr_memb_lops),
	.pgr_memb_lock = ATOMIC_RWLOCK_INIT,
	.pgr_memb_list = { &boottask_pid }, /* /bin/init is the initial process, and thus a member of this process group */
	.pgr_ns        = &pidns_root,
	.pgr_pids      = {
		[0] = {
			.pgs_link = { NULL, NULL },
			.pgs_pid  = 1, /* == boottask_pid.tp_pids[0].tps_pid */
		}
	}
};


/* Process controller for `boottask' (aka. `/bin/init') */
PUBLIC struct procctl boottask_procctl = {
#ifndef CONFIG_NO_SMP
	.pc_thrds_lock = ATOMIC_LOCK_INIT,
#endif /* !CONFIG_NO_SMP */
	/* s.a. the static initializer of `asyncwork_pid', which is statically
	 *      set-up to behave  like the  first element of  this very  list! */
	.pc_thrds_list   = { &asyncwork_pid },
	.pc_chlds_lock   = ATOMIC_RWLOCK_INIT,
	.pc_chlds_list   = LIST_HEAD_INITIALIZER(boottask_procctl.pc_chlds_list),
	.pc_chld_changed = SIG_INIT,
	/* Even though it  doesn't ~really~  make sense, /bin/init  is set-up  to
	 * behave as its own parent process. Because the parent field must always
	 * be non-NULL, we have to fill in ~something~, and since /bin/init can't
	 * ever die (TASK_FCRITICAL), its parent never ~really~ becomes  relevant
	 * either. -- But note however that if /bin/init were to call  getppid(),
	 * it would get back its own PID! */
	.pc_parent    = ARREF_INIT(&boottask),
	.pc_sig_lock  = ATOMIC_RWLOCK_INIT,
	.pc_sig_list  = SLIST_HEAD_INITIALIZER(boottask_procctl.pc_sig_list),
	.pc_sig_more  = SIG_INIT,
	.pc_grp       = ARREF_INIT(&boottask_procgrp),
	.pc_grpmember = { .le_next = NULL, .le_prev = &boottask_procgrp.pgr_memb_list.lh_first },
	.pc_timers    = NULL,
};






/************************************************************************/
/* gettid(), getpid(), getppid(), getpgrp(), getpgid()                  */
/* setpgid(), getsid(), setsid()                                        */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_GETTID
DEFINE_SYSCALL0(pid_t, gettid) {
	COMPILER_IMPURE();
	return task_gettid();
}
#endif /* __ARCH_WANT_SYSCALL_GETTID */

#ifdef __ARCH_WANT_SYSCALL_GETPID
DEFINE_SYSCALL0(pid_t, getpid) {
	COMPILER_IMPURE();
	return task_getpid();
}
#endif /* __ARCH_WANT_SYSCALL_GETPID */

#ifdef __ARCH_WANT_SYSCALL_GETPPID
DEFINE_SYSCALL0(pid_t, getppid) {
	COMPILER_IMPURE();
	return task_getppid_s();
}
#endif /* __ARCH_WANT_SYSCALL_GETPPID */

#ifdef __ARCH_WANT_SYSCALL_GETPGRP
DEFINE_SYSCALL0(pid_t, getpgrp) {
	/* Same as `getpgid(0)' */
	COMPILER_IMPURE();
	return task_getpgid_s();
}
#endif /* __ARCH_WANT_SYSCALL_GETPGRP */

#ifdef __ARCH_WANT_SYSCALL_GETPGID
DEFINE_SYSCALL1(pid_t, getpgid, pid_t, pid) {
	REF struct procgrp *grp;
	struct taskpid *mypid = task_gettaskpid();
	pid_t result;
	if (pid == 0) {
		grp = taskpid_getprocgrp(mypid);
	} else {
		REF struct taskpid *req_pid;
		req_pid = pidns_lookup_srch(mypid->tp_ns, pid);
		grp     = taskpid_getprocgrp(req_pid);
		decref_unlikely(req_pid);
	}
	result = procgrp_getnspgid_s(grp, mypid->tp_ns);
	decref_unlikely(grp);
	return result;
}
#endif /* __ARCH_WANT_SYSCALL_GETPGID */

#ifdef __ARCH_WANT_SYSCALL_SETPGID
DEFINE_SYSCALL2(errno_t, setpgid, pid_t, pid, pid_t, pgid) {
	struct taskpid *caller_pid = task_getprocpid();
	REF struct taskpid *self_pid; /* For `pid' */
	struct procctl *self_pctl;
	REF struct procgrp *oldgrp;
	REF struct procgrp *caller_grp;
	caller_grp = taskpid_getprocgrp(caller_pid);
	FINALLY_DECREF_UNLIKELY(caller_grp);
	if (pid == 0) {
		self_pid = incref(caller_pid);
		pid      = taskpid_gettid_s(caller_pid);
	} else {
		self_pid = pidns_lookup_srch(caller_pid->tp_ns, pid);
	}
	FINALLY_DECREF_UNLIKELY(self_pid);
	if (!taskpid_isaprocess(self_pid) || /* Must be a process */
	    !(self_pid == caller_pid ||      /* Must be the calling thread, or one of its children */
	      taskpid_getparentprocessptr(self_pid) == taskpid_gettaskptr(caller_pid)))
		THROW(E_PROCESS_EXITED, pid);
	self_pctl = taskpid_getprocctl(self_pid);

	if (pgid != 0 && pgid == taskpid_gettid_s(self_pid))
		pgid = 0; /* Also create a new group in this case. */

	/* Query the old process group of `self_pid' */
again_get_oldgrp:
	oldgrp = procctl_getprocgrp(self_pctl);
	FINALLY_DECREF_UNLIKELY(oldgrp);

	/* Posix only allows changing the group of a process apart of the caller's session.
	 * """
	 * EPERM  The value of the pid argument matches the process ID of  a
	 *        child process of the calling process and the child process
	 *        is not in the same session as the calling process.
	 * """
	 */
	if (procgrp_getsession(oldgrp) != procgrp_getsession(caller_grp)) {
		THROW(E_ILLEGAL_BECAUSE_GROUPING,
		      E_ILLEGAL_OPERATION_CONTEXT_SETPGID_DIFFERENT_SESSION, pid);
	}

	/* """
	 * EPERM The process indicated by the pid argument is a session leader.
	 * """ */
	if (procgrp_issessionleader(oldgrp) &&
		procgrp_getrootpgid(oldgrp) == taskpid_getrootpid(self_pid)) {
		THROW(E_ILLEGAL_BECAUSE_GROUPING,
		      E_ILLEGAL_OPERATION_CONTEXT_SETPGID_IS_SESSION_LEADER, pid);
	}

	/* Figure out which group we want to join. */
	if (pgid == 0) {
		struct pidns *ns_iter;
		REF struct procgrp *newgrp;

		/* Check for special case: `self_pid' already is the leader of `oldgrp'
		 * In this case we mustn't do anything. This is also important in order
		 * to  ensure that  no process  group matching  `self_pid's IDs already
		 * exists within any of the associated PID namespaces! */
		if (procgrp_getrootpgid(oldgrp) == taskpid_getrootpid(self_pid))
			return -EOK;

		/* Create a new process group. */
		newgrp = _procgrp_alloc(self_pid->tp_ns);

		/* Initialize the new group. */
		newgrp->pgr_refcnt  = 1; /* +1: self_pctl->pc_grp (arref_cmpxch_inherit_new) */
		newgrp->pgr_sleader = incref(oldgrp->pgr_sleader);
		newgrp->pgr_session = oldgrp->pgr_session;
		SLIST_INIT(&newgrp->pgr_memb_lops);
		atomic_rwlock_init_write(&newgrp->pgr_memb_lock); /* IMPORTANT: Init w/ a write-lock */
		LIST_INIT(&newgrp->pgr_memb_list);
		newgrp->pgr_ns = incref(self_pid->tp_ns);

		/* Fill in PIDs for the new process group. This has to happen
		 * first since the moment we set `self_pctl->pc_grp', the new
		 * process group will already  be globally visible. As  such,
		 * all of its non-locked (i.e. [const]) fields must be  fully
		 * initialized at that point! */
		ns_iter = newgrp->pgr_ns;
		do {
			size_t ind = ns_iter->pn_ind;
#if 0 /* No need. -- The `_TASKPID_SLOT_REDMASK' flag will get cleared anyways! */
			newgrp->pgr_pids[ind].pgs_pid = _taskpid_slot_getpidno(self_pid->tp_pids[ind]);
#else
			newgrp->pgr_pids[ind].pgs_pid = self_pid->tp_pids[ind].tps_pid;
#endif
		} while ((ns_iter = ns_iter->pn_par) != NULL);

		/* Acquire required locks.
		 *
		 * Because  we're creating a new process group,  we need locks to all of
		 * the PID namespaces it should appear in, as well as the member list of
		 * the group's first process's old process group. */
		TRY {
			struct pidns *blocking;
again_lock_oldgrp_for_new_group:
			procgrp_memb_write(oldgrp);
			blocking = pidns_trywriteall(newgrp->pgr_ns);
			if (blocking) {
				procgrp_memb_endwrite(oldgrp);
				pidns_waitwrite(blocking);
				goto again_lock_oldgrp_for_new_group;
			}
		} EXCEPT {
			decref_nokill(newgrp->pgr_ns);      /* *_nokill because of ref in `self_pid->tp_ns' */
			decref_nokill(newgrp->pgr_sleader); /* *_nokill because of ref in `oldgrp->pgr_sleader' */
			_procgrp_free(newgrp);
			RETHROW();
		}

		/* === Point of no return: make the new group globally visible */
		if (!arref_cmpxch_inherit_new(&self_pctl->pc_grp, oldgrp, newgrp)) {
			_procgrp_memb_endwrite(oldgrp);
			pidns_endwriteall(newgrp->pgr_ns);
			procgrp_memb_reap(oldgrp);
			decref_nokill(newgrp->pgr_ns);      /* *_nokill because of ref in `self_pid->tp_ns' */
			decref_nokill(newgrp->pgr_sleader); /* *_nokill because of ref in `oldgrp->pgr_sleader' */
			_procgrp_free(newgrp);
			goto again_get_oldgrp;
		}

		/* Update remaining links. */
		procgrp_memb_remove(oldgrp, self_pid);
		procgrp_memb_insert(newgrp, self_pid);
		_procgrp_memb_endwrite(newgrp); /* We initialized the lock in write-mode! */
		_procgrp_memb_endwrite(oldgrp);

		/* Insert the new process group into all of the namespaces.
		 *
		 * Note that the  "if (procgrp_getrootpgid(oldgrp) == taskpid_getrootpid(self_pid))"
		 * check above already asserted (when combined with POSIX's rules on PID reuse) that
		 * there  cannot be  pre-existing process groups  already using our  new group's IDs
		 * within any of those namespaces! */
		ns_iter = newgrp->pgr_ns;
		do {
			pidns_grpinsert(ns_iter, newgrp);
		} while ((ns_iter = ns_iter->pn_par) != NULL);

		/* Release locks. */
		pidns_endwriteall(newgrp->pgr_ns);
		procgrp_memb_reap(oldgrp);
		procgrp_memb_reap(newgrp);
	} else {
		REF struct procgrp *newgrp;
		/* Join an existing process group. */
		newgrp = pidns_grplookup_srch(caller_pid->tp_ns, pgid);
		if unlikely(!newgrp) {
			if unlikely(pgid < 0) {
				THROW(E_INVALID_ARGUMENT_BAD_VALUE,
				      E_INVALID_ARGUMENT_CONTEXT_BAD_PGID,
				      pgid);
			}
			/* """
			 * EPERM  The value of the pgid argument is valid but does not  match
			 *        the  process  ID  of  the  process  indicated  by  the  pid
			 *        argument and there is no process group with a process group
			 *        ID that matches the value of the pgid argument in the  same
			 *        session as the calling process.
			 * """
			 * [*] "valid" here only means that the value is positive */
throw_no_such_group:
			THROW(E_ILLEGAL_OPERATION,
			      E_ILLEGAL_OPERATION_CONTEXT_SETPGID_NO_SUCH_GROUP,
			      pgid);
		}

		/* Special case: we're a no-op if the group didn't change. */
		if (newgrp == oldgrp) {
			decref_nokill(newgrp); /* *_nokill because of 2nd reference held to `oldgrp' */
			return -EOK;
		}

		/* Existing group must be part of caller's session. */
		if (procgrp_getsession(newgrp) != procgrp_getsession(caller_grp)) {
			decref_unlikely(newgrp);
			goto throw_no_such_group;
		}

		/* All right: let's join this group! */
again_lock_oldgrp:
		procgrp_memb_write(oldgrp);
		if (!procgrp_memb_trywrite(newgrp)) {
			procgrp_memb_endwrite(oldgrp);
			procgrp_memb_write(newgrp);
			if (!procgrp_memb_trywrite(oldgrp)) {
				procgrp_memb_endwrite(newgrp);
				goto again_lock_oldgrp;
			}
		}

		/* Change group association */
		if (!arref_cmpxch_inherit_new(&self_pctl->pc_grp, oldgrp, newgrp)) {
			_procgrp_memb_endwrite(newgrp);
			_procgrp_memb_endwrite(oldgrp);
			procgrp_memb_reap(newgrp);
			procgrp_memb_reap(oldgrp);
			decref_unlikely(newgrp);
			goto again_get_oldgrp;
		}

		/* Update group membership list pointers. */
		procgrp_memb_remove(oldgrp, self_pid);
		procgrp_memb_insert(newgrp, self_pid);

		/* Release locks. */
		_procgrp_memb_endwrite(newgrp);
		_procgrp_memb_endwrite(oldgrp);
		procgrp_memb_reap(newgrp);
		procgrp_memb_reap(oldgrp);
	}
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_SETPGID */

#ifdef __ARCH_WANT_SYSCALL_GETSID
DEFINE_SYSCALL1(pid_t, getsid, pid_t, pid) {
	REF struct procgrp *grp;
	struct taskpid *mypid = task_gettaskpid();
	pid_t result;
	if (pid == 0) {
		grp = taskpid_getprocgrp(mypid);
	} else {
		REF struct taskpid *req_pid;
		req_pid = pidns_lookup_srch(mypid->tp_ns, pid);
		grp     = taskpid_getprocgrp(req_pid);
		decref_unlikely(req_pid);
	}
	result = procgrp_getnssid_s(grp, mypid->tp_ns);
	decref_unlikely(grp);
	return result;
}
#endif /* __ARCH_WANT_SYSCALL_GETSID */

#ifdef __ARCH_WANT_SYSCALL_SETSID
DEFINE_SYSCALL0(pid_t, setsid) {
	pid_t result;
	struct pidns *ns_iter;
	struct taskpid *pid = task_getprocpid();
	struct procctl *ctl = taskpid_getprocctl(pid);
	struct pidns *ns    = pid->tp_ns;
	REF struct procgrp *oldgrp, *newgrp;
again_get_oldgrp:
	oldgrp = procctl_getprocgrp(ctl);
	FINALLY_DECREF_UNLIKELY(oldgrp);

	/* """
	 * EPERM  The calling process is already a process group leader, or
	 *        the  process group ID of a process other than the calling
	 *        process matches the process ID of the calling process.
	 * """
	 * I  really don't know  how that second part  could happen, where a
	 * process group matching the  caller's PID already exists.  Because
	 * process groups can only be created using the PID of the  creating
	 * process, and processes only get assigned PIDs that aren't already
	 * in use by process groups (as per posix specs).
	 *
	 * Anyways: If the caller is already a process group leader, then
	 *          we're not  allowed to  make  them a  session  leader! */
	if (procgrp_getrootpgid(oldgrp) == taskpid_getroottid(pid)) {
		THROW(E_ILLEGAL_BECAUSE_GROUPING,
		      E_ILLEGAL_OPERATION_CONTEXT_SETSID_ALREADY_GROUP_LEADER);
	}

	/* All right: let's construct a new process group! */
	newgrp = _procgrp_alloc(ns);
	TRY {
		/* Allocate+initialize a new session. */
		newgrp->pgr_session = _procsession_new();
	} EXCEPT {
		_procgrp_free(newgrp);
		RETHROW();
	}

	/* Initialize the new group. */
	newgrp->pgr_refcnt  = 1;      /* +1: ctl->pc_grp (arref_cmpxch_inherit_new) */
	newgrp->pgr_sleader = newgrp; /* This one's a session leader! */
	SLIST_INIT(&newgrp->pgr_memb_lops);
	atomic_rwlock_init_write(&newgrp->pgr_memb_lock); /* IMPORTANT: Init w/ a write-lock */
	LIST_INIT(&newgrp->pgr_memb_list);
	newgrp->pgr_ns = incref(ns);

	/* Fill in PIDs for the new  process group. This has to  happen
	 * first since the moment we set `ctl->pc_grp', the new process
	 * group  will already be globally visible. As such, all of its
	 * non-locked  (i.e. [const]) fields  must be fully initialized
	 * at that point! */
	ns_iter = newgrp->pgr_ns;
	do {
		size_t ind = ns_iter->pn_ind;
#if 0 /* No need. -- The `_TASKPID_SLOT_REDMASK' flag will get cleared anyways! */
		newgrp->pgr_pids[ind].pgs_pid = _taskpid_slot_getpidno(pid->tp_pids[ind]);
#else
		newgrp->pgr_pids[ind].pgs_pid = pid->tp_pids[ind].tps_pid;
#endif
	} while ((ns_iter = ns_iter->pn_par) != NULL);

	/* Return the new session's process group ID */
	result = newgrp->pgr_pids[ns->pn_ind].pgs_pid;

	/* Acquire required locks.
	 *
	 * Because  we're creating a new process group,  we need locks to all of
	 * the PID namespaces it should appear in, as well as the member list of
	 * the group's first process's old process group. */
	TRY {
		struct pidns *blocking;
again_lock_oldgrp_for_new_group:
		procgrp_memb_write(oldgrp);
		blocking = pidns_trywriteall(newgrp->pgr_ns);
		if (blocking) {
			procgrp_memb_endwrite(oldgrp);
			pidns_waitwrite(blocking);
			goto again_lock_oldgrp_for_new_group;
		}
	} EXCEPT {
		decref_nokill(newgrp->pgr_ns); /* *_nokill because of ref in `pid->tp_ns' */
		_procsession_destroy(newgrp->pgr_session);
		_procgrp_free(newgrp);
		RETHROW();
	}

	/* === Point of no return: make the new group globally visible */
	if (!arref_cmpxch_inherit_new(&ctl->pc_grp, oldgrp, newgrp)) {
		_procgrp_memb_endwrite(oldgrp);
		pidns_endwriteall(newgrp->pgr_ns);
		procgrp_memb_reap(oldgrp);
		decref_nokill(newgrp->pgr_ns); /* *_nokill because of ref in `pid->tp_ns' */
		_procsession_destroy(newgrp->pgr_session);
		_procgrp_free(newgrp);
		goto again_get_oldgrp;
	}

	/* Update remaining links. */
	procgrp_memb_remove(oldgrp, pid);
	procgrp_memb_insert(newgrp, pid);
	_procgrp_memb_endwrite(newgrp); /* We initialized the lock in write-mode! */
	_procgrp_memb_endwrite(oldgrp);

	/* Insert the new process group into all of the namespaces.
	 *
	 * Note that the  "if (procgrp_getrootpgid(oldgrp) == taskpid_getroottid(pid))"
	 * check above already asserted (when combined with POSIX's rules on PID reuse)
	 * that  there  cannot be  pre-existing process  groups  already using  our new
	 * group's IDs within any of those namespaces! */
	ns_iter = newgrp->pgr_ns;
	do {
		pidns_grpinsert(ns_iter, newgrp);
	} while ((ns_iter = ns_iter->pn_par) != NULL);

	/* Release locks. */
	pidns_endwriteall(newgrp->pgr_ns);
	procgrp_memb_reap(oldgrp);
	procgrp_memb_reap(newgrp);

	return result;
}
#endif /* __ARCH_WANT_SYSCALL_SETSID */




/************************************************************************/
/* detach()                                                             */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_DETACH
DEFINE_SYSCALL1(errno_t, detach, pid_t, pid) {
	/* >> sys_detach(2)
	 * This is a KOS-specific system call that can be used to detach a
	 * child thread (by setting `TASK_FDETACHED'), or a child  process
	 * (by  changing it's parent to be `/bin/init'). The same may also
	 * be done to the calling thread/process!
	 *
	 * The following modes of operation are defined:
	 *
	 * >> detach(0)
	 *   - Same as `detach(gettid())', but note special handling when
	 *     the caller is the main thread.
	 *
	 * >> detach(TID_OF_THREAD_IN_CURRENT_PROCESS_OTHER_THAN_MAIN_THREAD)
	 *   - Set the `TASK_FDETACHED' flag for the thread. If the thread has
	 *     already  been destroyed, or already has the `TASK_FTERMINATING'
	 *     flag set, also unlink it from the process's list of children.
	 *   - When the `TASK_FDETACHED' flag is already set, throw `E_PROCESS_EXITED'
	 *
	 * >> detach(PID_OF_CURRENT_PROCESS_OR_CHILD_PROCESS)
	 *   - Change the parent of the indicated process to become /bin/init,
	 *     thus  also removing it from it's old parent's list of children,
	 *     and inserting it into that of /bin/init. Note that when this is
	 *     done by /bin/init itself, this becomes a no-op.
	 *
	 * >> detach(-1)
	 *   - Same as (atomic):
	 *     >> for (pid_t pid: opendir("/proc/self/task")) {
	 *     >>     if (pid == getpid())
	 *     >>         continue;
	 *     >>     detach(pid);
	 *     >> }
	 *     In other words: detach all children (both threads and processes)
	 *     of  the calling process. Note that if there weren't any children
	 *     to detach, `-ECHILD' is returned (yes: "return"; we don't use an
	 *     exception in this case).
	 *
	 * NOTE: Threads  created  with `clone(CLONE_DETACHED)'  already  have the
	 *       `TASK_FTERMINATING' flag set from the get-go. In child processes,
	 *       it causes /bin/init to be used as parent. */
	struct taskpid *caller_task = task_gettaskpid();
	struct taskpid *caller_proc = taskpid_getprocpid(caller_task);
	struct procctl *ctl         = taskpid_getprocctl(caller_proc);
	struct pidns *ns            = caller_task->tp_ns;
	if (pid == -1) {
		/* TODO: Detach all children */
	} else {
		REF struct taskpid *detach;
		if (pid == 0) /* Use the caller's TID instead. */
			pid = taskpid_getnstid(caller_task, ns);

		/* Lookup the task to detach. */
		detach = pidns_lookup_srch(ns, pid);
		FINALLY_DECREF_UNLIKELY(detach);

		/* Special case for child threads. */
		if (!taskpid_isaprocess(detach)) {
			REF struct task *thread;
			/* Ensure that this is one of our threads. */
			if (taskpid_getprocpid(detach) != caller_proc)
				THROW(E_PROCESS_EXITED, pid);

			thread = taskpid_gettask(detach);
			if (thread) {
				/* Thread is still running. -- Let's see if we can set the DETACHED
				 * flag before the thread itself  sets its TERMINATING flag. If  we
				 * manage to do that, then the  thread will remove itself from  our
				 * process's child list as soon as it terminates. */
				uintptr_t old_flags;
				old_flags = atomic_fetchor(&thread->t_flags, TASK_FDETACHED);
				decref_unlikely(thread);
				if unlikely(old_flags & TASK_FDETACHED)
					THROW(E_PROCESS_EXITED, pid); /* Thread had already been detached before */
				if (!(old_flags & TASK_FTERMINATING))
					return -EOK; /* Success: the thread will remove itself! */
				/* The thread is already terminating. -- In this case, we must (try) to
				 * remove the thread from our  process's child list (unless the  thread
				 * itself already managed to do so as well) */
			}

			/* (try to) unbind from our process's child list. */
			procctl_chlds_write(ctl);
			if (LIST_ISBOUND(detach, tp_parsib)) {
				procctl_chlds_unbind(ctl, detach); /* Inherit reference */
			} else {
				incref(detach);
			}
			procctl_chlds_endwrite(ctl);
			decref(detach);
		} else {
			REF struct task *oldparent;
again_get_oldparent:
			oldparent = taskpid_getparentprocess(detach);
			FINALLY_DECREF_UNLIKELY(oldparent);

			/* Ensure that this is actually one of our process's children (or the process itself). */
			if (detach != caller_proc && oldparent != taskpid_gettaskptr(caller_proc))
				THROW(E_PROCESS_EXITED, pid);

			/* Detach a child process (by changing its parent to become /bin/init)
			 * Note  that this is  a no-op if the  calling process _is_ /bin/init! */
			if likely(ctl != &boottask_procctl) {
again_write_ctl:
				procctl_chlds_write(ctl);
				if (!procctl_chlds_trywrite(&boottask_procctl)) {
					procctl_chlds_endwrite(ctl);
					procctl_chlds_write(&boottask_procctl);
					if (!procctl_chlds_trywrite(ctl)) {
						procctl_chlds_endwrite(&boottask_procctl);
						goto again_write_ctl;
					}
				}

				/* Atomically change the parent process to /bin/init */
				if (!arref_cmpxch(&detach->tp_pctl->pc_parent, oldparent, &boottask)) {
					_procctl_chlds_endwrite(&boottask_procctl);
					_procctl_chlds_endwrite(ctl);
					procctl_chlds_reap(&boottask_procctl);
					procctl_chlds_reap(ctl);
					goto again_get_oldparent;
				}

				/* Update list membership. */
				procctl_chlds_remove(ctl, detach); /* Inherit reference */
				assert(!(boottask.t_flags & TASK_FTERMINATING));
				procctl_chlds_insert(&boottask_procctl, detach); /* Inherit reference */

				/* Release locks. */
				_procctl_chlds_endwrite(&boottask_procctl);
				_procctl_chlds_endwrite(ctl);
				procctl_chlds_reap(&boottask_procctl);
				procctl_chlds_reap(ctl);

				/* Broadcast the process's change of parent */
				sig_broadcast(&boottask_procctl.pc_chld_changed);
				sig_broadcast(&ctl->pc_chld_changed);
				sig_broadcast(&detach->tp_changed);
			}
		}
	}
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_DETACH */




/************************************************************************/
/* waitid(), waitpid(), wait4()                                         */
/************************************************************************/
#if (defined(__ARCH_WANT_SYSCALL_WAITID) ||         \
     defined(__ARCH_WANT_SYSCALL_WAITPID) ||        \
     defined(__ARCH_WANT_SYSCALL_WAIT4) ||          \
     defined(__ARCH_WANT_COMPAT_SYSCALL_WAITID) ||  \
     defined(__ARCH_WANT_COMPAT_SYSCALL_WAITPID) || \
     defined(__ARCH_WANT_COMPAT_SYSCALL_WAIT4))
#define WANT_WAIT 1
#endif

#ifdef WANT_WAIT

/* Check if `SIGCLD' is being ignored by the calling thread */
PRIVATE WUNUSED bool FCALL
is_ignoring_SIGCLD(void) THROWS(E_WOULDBLOCK) {
	bool result;
	struct sighand_ptr *ptr;
	struct sighand *hand;
	ptr = THIS_SIGHAND_PTR;
	if (!ptr)
		return false;
	hand = sighand_ptr_lockread(ptr);
	if unlikely(!hand)
		return false;
	result = (hand->sh_actions[SIGCLD - 1].sa_flags & SA_NOCLDWAIT) || /* This also triggers `SIG_IGN' behavior! */
	         (hand->sh_actions[SIGCLD - 1].sa_handler == SIG_IGN);     /* SIGCLD is explicitly set to SIG_IGN */
	sighand_endread(hand);
	return result;
}

/* Check if the thread of a given `taskpid' has terminated (or is terminating). */
LOCAL NOBLOCK NONNULL((1)) bool
NOTHROW(KCALL taskpid_hasterminated)(struct taskpid *__restrict self) {
	uintptr_t flags;
	REF struct task *thread;
	thread = taskpid_gettask(self);
	if (!thread) {
		/* Destroyed thread --> thread must have terminated. */
		return true;
	}
	flags = atomic_read(&thread->t_flags);
	decref_unlikely(thread);

	/* Return indicative of the TERMINATING or TERMINATED flags being set. */
	return (flags & (TASK_FTERMINATING | TASK_FTERMINATED)) != 0;
}


/* @return: true:  There are no non-terminated child processes, and all
 *                 those  that have terminated  were reaped (unless the
 *                 WNOREAP flag was given)
 * @return: false: There are still some child processes that have yet to terminate. */
PRIVATE WUNUSED NONNULL((1)) bool FCALL
try_reap_all_children(struct procctl *__restrict ctl,
                      syscall_ulong_t options)
		THROWS(E_WOULDBLOCK) {
	bool result = true;
	struct taskpid *child;
again:
	/* Enumerate child processes */
	procctl_chlds_read(ctl);
	FOREACH_procctl_chlds(child, ctl) {
		if (!taskpid_hasterminated(child)) {
			/* Found a child process that has yet to terminate! */
			result = false;
			continue;
		}
		/* If instructed to, reap terminated child processes. */
		if (!(options & WNOREAP)) {
			if (!procctl_chlds_tryupgrade(ctl)) {
				procctl_chlds_endread(ctl);
				procctl_chlds_waitwrite(ctl);
				goto again;
			}
			/* Unlink `child' from the list. */
			procctl_chlds_unbind(ctl, child); /* Inherit reference */
			procctl_chlds_endwrite(ctl);
			decref_likely(child);
			goto again;
		}
	}
	procctl_chlds_endread(ctl);
	return result;
}

/* Block until all  child processes have  exited,
 * and reap all zombies created in the mean time.
 *
 * @param: options: WNOREAP: Don't actually reap children; just wait until all child processes have exited.
 *                  WNOHANG: Don't actually wait; just reap children as they are present right now.
 * NOTE: When `WNOHANG | WNOREAP' is passed, this function becomes a de-facto no-op. */
PRIVATE BLOCKING_IF(!(options & WNOHANG)) NONNULL((1)) void FCALL
waitfor_and_reap_all_children(struct procctl *__restrict ctl,
                              syscall_ulong_t options) {
again:
	if (try_reap_all_children(ctl, options))
		return;
	if (options & WNOHANG)
		return; /* Not supposed to block. */
	task_connect_for_poll(&ctl->pc_chld_changed);
	TRY {
		if (try_reap_all_children(ctl, options)) {
			task_disconnectall();
			return;
		}
	} EXCEPT {
		task_disconnectall();
		RETHROW();
	}

	/* Wait for one of our children to change status. */
	task_waitfor();
	goto again;
}


/* Fill in wait status information for user-space.
 * @return: * : The used child PID for `child' */
PRIVATE NONNULL((1, 2)) pid_t KCALL
fill_wait_info(struct taskpid *__restrict proc,
               struct taskpid *__restrict child,
               uint16_t status,
               NCX int32_t *wstatus,
               NCX siginfo_t *infop,
               NCX struct rusage *ru) {
	pid_t result;
	result = taskpid_getnstid_s(child, proc->tp_ns);

	/* Fill in information in user-pointers! */
	COMPILER_WRITE_BARRIER();
	if (wstatus != NULL)
		*wstatus = status;
	if (infop) {
		infop->si_signo  = SIGCLD;
		infop->si_errno  = 0;
		if (WIFCONTINUED(status)) {
			infop->si_code = CLD_CONTINUED;
		} else if (WIFSTOPPED(status)) {
			infop->si_code = CLD_STOPPED;
		} else if (WCOREDUMP(status)) {
			infop->si_code = CLD_DUMPED;
		} else if (WIFEXITED(status)) {
			infop->si_code = CLD_EXITED;
		} else if (WIFSIGNALED(status)) {
			infop->si_code = CLD_KILLED;
		} else {
			infop->si_code = CLD_TRAPPED;
		}
		infop->si_pid    = result;
		infop->si_uid    = 0; /* ??? */
		infop->si_status = status;
		infop->si_utime  = 0; /* ??? */
		infop->si_stime  = 0; /* ??? */
	}
	if (ru) {
		bzero(ru, sizeof(*ru));
		/* XXX: Fill in usage information? */
	}
	COMPILER_WRITE_BARRIER();
	return result;
}


PRIVATE pid_t KCALL
waitfor_children(idtype_t which, id_t which_pid,
                 syscall_ulong_t options,
                 NCX int32_t *wstatus,
                 NCX siginfo_t *infop,
                 NCX struct rusage *ru) {
	struct taskpid *proc = task_getprocpid();
	struct procctl *ctl  = taskpid_getprocctl(proc);

	/* Check for special behavior when SIGCLD is being ignored. */
	if (is_ignoring_SIGCLD()) {
		waitfor_and_reap_all_children(ctl, options);
		return -ECHILD;
	}

	/* Do the actual job of waiting for threads/processes. */
	if (which == P_PID) {
		uint16_t status;
		REF struct taskpid *child;

		/* Wait for a specific child thread/process */
		child = pidns_lookup(proc->tp_ns, (pid_t)which_pid);
		if unlikely(!child)
			return -ECHILD; /* No such process */
		FINALLY_DECREF_UNLIKELY(child);
again_read_status:
		if (taskpid_isaprocess(child)) {
			if (taskpid_getparentprocessptr(child) != taskpid_gettaskptr(proc))
				return -ECHILD; /* Not a child process */
		} else {
			if (taskpid_getprocpid(child) != proc)
				return -ECHILD; /* Not a child thread */
		}
		status = atomic_read(&child->tp_status);
		if (((options & WSTOPPED) && WIFSTOPPED(status)) ||
		    ((options & WCONTINUED) && WIFCONTINUED(status))) {
again_consume_status_stop_cont:
			if (!atomic_cmpxch_weak(&child->tp_status, status, 0))
				goto again_read_status;
			/* we're dealing with an stop/continue status */
		} else if ((options & WEXITED) && taskpid_hasterminated(child)) {
			/* we're dealing with an exit-code status */
again_child_has_exited:
			if (!(options & WNOREAP)) {
				/* Reap child */
				if (taskpid_isaprocess(child)) {
					procctl_chlds_write(ctl);
					if (taskpid_getparentprocessptr(child) != taskpid_gettaskptr(proc)) {
						procctl_chlds_endwrite(ctl);
						return -ECHILD; /* Not a child */
					}
					if likely(LIST_ISBOUND(child, tp_parsib)) {
						procctl_chlds_unbind(ctl, child); /* Inherit reference */
						decref_nokill(child);             /* Still got our reference from `pidns_lookup()'! */
					}
					procctl_chlds_endwrite(ctl);
				} else {
					procctl_thrds_acquire(ctl);
					if likely(LIST_ISBOUND(child, tp_parsib)) {
						procctl_thrds_unbind(ctl, child); /* Inherit reference */
						decref_nokill(child);             /* Still got our reference from `pidns_lookup()'! */
					}
					procctl_thrds_release(ctl);
				}
			}
		} else if (options & WNOHANG) {
			/* Don't block */
			goto err_EAGAIN;
		} else {
			/* Wait for child to change status. */
			task_connect_for_poll(&child->tp_changed);
			status = atomic_read(&child->tp_status);
			if (((options & WSTOPPED) && WIFSTOPPED(status)) ||
			    ((options & WCONTINUED) && WIFCONTINUED(status))) {
				task_disconnectall();
				goto again_consume_status_stop_cont;
			}
			if ((options & WEXITED) && taskpid_hasterminated(child)) {
				task_disconnectall();
				goto again_child_has_exited;
			}
			task_waitfor();
			goto again_read_status;
		}

		/* Write-back wait information for this child. */
		return fill_wait_info(proc, child, status, wstatus, infop, ru);
	} else {
		/* Wait for multiple children (as opposed to a specific child) */
		struct taskpid *child;
		bool has_candidates;
again_scan_children:
		has_candidates = false;
		if (!(options & WNOHANG))
			task_connect_for_poll(&ctl->pc_chld_changed);
		TRY {
			procctl_chlds_read(ctl);
		} EXCEPT {
			task_disconnectall();
			RETHROW();
		}

		/* Enumerate child processes. (in this case, we ignore threads) */
		FOREACH_procctl_chlds (child, ctl) {
			uint16_t status;
			assert(taskpid_isaprocess(child));
			if (which == P_PGID) {
				/* Ignore if `child' isn't apart of a specific process group. */
				if (taskpid_getpgid_s(child) != (pid_t)which_pid)
					continue;
			}
again_read_status_in_nonspecific:
			status = atomic_read(&child->tp_status);
			if (((options & WSTOPPED) && WIFSTOPPED(status)) ||
			    ((options & WCONTINUED) && WIFCONTINUED(status))) {
				if (!atomic_cmpxch_weak(&child->tp_status, status, 0))
					goto again_read_status_in_nonspecific;

				/* we're dealing with an stop/continue status */
				incref(child);
				procctl_chlds_endread(ctl);
			} else if ((options & WEXITED) && taskpid_hasterminated(child)) {
				/* we're dealing with an exit-code status */
				if (options & WNOREAP) {
					incref(child);
				} else {
					/* Reap child */
					if (!procctl_chlds_tryupgrade(ctl)) {
						procctl_chlds_endread(ctl);
						task_disconnectall();
						procctl_chlds_waitwrite(ctl);
						goto again_scan_children;
					}
					procctl_chlds_unbind(ctl, child); /* Inherit reference */
					procctl_chlds_endwrite(ctl);
				}
			} else {
				/* We've got a candidate, but it doesn't
				 * have a status that we're looking for. */
				has_candidates = true;
				continue;
			}
			FINALLY_DECREF(child);
			task_disconnectall();
			return fill_wait_info(proc, child, status, wstatus, infop, ru);
		}
		procctl_chlds_endread(ctl);
		if (!has_candidates) {
			task_disconnectall();
			return -ECHILD; /* No candidates */
		}
		if (options & WNOHANG) {
			assert(!task_wasconnected());
			goto err_EAGAIN; /* Operation would have blocked */
		}
		task_waitfor();
		goto again_scan_children;
	}
	__builtin_unreachable();
err_EAGAIN:
	if (infop) {
		/* From `man 2 waitpid':
		 * """
		 *    POSIX.1-2008 Technical Corrigendum 1 (2013) adds the requirement
		 *    that when  WNOHANG is  specified in  options and  there were  no
		 *    children  in a waitable state, then waitid() should zero out the
		 *    si_pid and si_signo fields of the structure. [...]
		 * """ */
		infop->si_pid   = 0;
		infop->si_signo = 0;
	}
	return -EAGAIN;
}
#endif /* WANT_WAIT */

#ifdef __ARCH_WANT_SYSCALL_WAITID
DEFINE_SYSCALL5(pid_t, waitid,
                syscall_ulong_t, which, id_t, upid,
                NCX UNCHECKED siginfo_t *, infop,
                syscall_ulong_t, options,
                NCX UNCHECKED struct __rusage32 *, ru) {
	pid_t result;
	VALIDATE_FLAGSET(options,
	                 WNOHANG | WNOREAP | WEXITED | WSTOPPED | WCONTINUED,
	                 E_INVALID_ARGUMENT_CONTEXT_WAITID_OPTIONS);
	if (!(options & (WEXITED | WSTOPPED | WCONTINUED)))
		THROW(E_INVALID_ARGUMENT_BAD_FLAG_COMBINATION,
		      E_INVALID_ARGUMENT_CONTEXT_WAITID_OPTIONS,
		      options,
		      WEXITED | WSTOPPED | WCONTINUED,
		      0);
	if (which > P_PGID)
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_WAITID_WHICH,
		      which);
	validate_writable_opt(infop, sizeof(*infop));
	validate_writable_opt(ru, sizeof(*ru));
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME_T__
	result = waitfor_children((idtype_t)which, upid, options, NULL, infop, ru);
#else /* __SIZEOF_TIME32_T__ == __SIZEOF_TIME_T__ */
	if (ru) {
		struct rusage kru;
		result = waitfor_children((idtype_t)which, upid, options, NULL, infop, &kru);
		if (E_ISOK(result))
			rusage_to_rusage32(&kru, ru);
	} else {
		result = waitfor_children((idtype_t)which, upid, options, NULL, infop, NULL);
	}
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME_T__ */
	return result;
}
#endif /* __ARCH_WANT_SYSCALL_WAITID */

#ifdef __ARCH_WANT_SYSCALL_WAITID64
DEFINE_SYSCALL5(pid_t, waitid64,
                syscall_ulong_t, which, id_t, upid,
                NCX UNCHECKED siginfo_t *, infop,
                syscall_ulong_t, options,
                NCX UNCHECKED struct rusage64 *, ru) {
	pid_t result;
	VALIDATE_FLAGSET(options,
	                 WNOHANG | WNOREAP | WEXITED | WSTOPPED | WCONTINUED,
	                 E_INVALID_ARGUMENT_CONTEXT_WAITID_OPTIONS);
	if (!(options & (WEXITED | WSTOPPED | WCONTINUED)))
		THROW(E_INVALID_ARGUMENT_BAD_FLAG_COMBINATION,
		      E_INVALID_ARGUMENT_CONTEXT_WAITID_OPTIONS,
		      options,
		      WEXITED | WSTOPPED | WCONTINUED,
		      0);
	if (which > P_PGID)
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_WAITID_WHICH,
		      which);
	validate_writable_opt(infop, sizeof(*infop));
	validate_writable_opt(ru, sizeof(*ru));
#if __SIZEOF_TIME64_T__ == __SIZEOF_TIME_T__
	result = waitfor_children((idtype_t)which, options, upid, NULL, infop, ru);
#else /* __SIZEOF_TIME64_T__ == __SIZEOF_TIME_T__ */
	if (ru) {
		struct rusage kru;
		result = waitfor_children((idtype_t)which, upid, options, NULL, infop, &kru);
		if (E_ISOK(result))
			rusage_to_rusage64(&kru, ru);
	} else {
		result = waitfor_children((idtype_t)which, upid, options, NULL, infop, NULL);
	}
#endif /* __SIZEOF_TIME64_T__ != __SIZEOF_TIME_T__ */
	return result;
}
#endif /* __ARCH_WANT_SYSCALL_WAITID64 */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_WAITID
DEFINE_COMPAT_SYSCALL5(pid_t, waitid,
                       syscall_ulong_t, which, id_t, upid,
                       NCX UNCHECKED compat_siginfo_t *, infop,
                       syscall_ulong_t, options,
                       NCX UNCHECKED struct compat_rusage32 *, ru) {
	pid_t result;
	siginfo_t info;
	VALIDATE_FLAGSET(options,
	                 WNOHANG | WNOREAP | WEXITED | WSTOPPED | WCONTINUED,
	                 E_INVALID_ARGUMENT_CONTEXT_WAITID_OPTIONS);
	if (!(options & (WEXITED | WSTOPPED | WCONTINUED)))
		THROW(E_INVALID_ARGUMENT_BAD_FLAG_COMBINATION,
		      E_INVALID_ARGUMENT_CONTEXT_WAITID_OPTIONS,
		      options,
		      WEXITED | WSTOPPED | WCONTINUED,
		      0);
	if (which > P_PGID)
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_WAITID_WHICH,
		      which);
	validate_writable_opt(infop, sizeof(*infop));
	validate_writable_opt(ru, sizeof(*ru));
	if (ru) {
		struct rusage kru;
		result = waitfor_children((idtype_t)which, upid, options,
		                          NULL, infop ? &info : NULL, &kru);
		if (E_ISOK(result))
			rusage_to_compat_rusage32(&kru, ru);
	} else {
		result = waitfor_children((idtype_t)which, upid, options,
		                          NULL, infop ? &info : NULL, NULL);
	}
	if (E_ISOK(result) && infop)
		siginfo_to_compat_siginfo(&info, infop);
	return result;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_WAITID */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_WAITID64
DEFINE_COMPAT_SYSCALL5(pid_t, waitid64,
                       syscall_ulong_t, which, id_t, upid,
                       NCX UNCHECKED compat_siginfo_t *, infop,
                       syscall_ulong_t, options,
                       NCX UNCHECKED struct compat_rusage64 *, ru) {
	pid_t result;
	siginfo_t info;
	VALIDATE_FLAGSET(options,
	                 WNOHANG | WNOREAP | WEXITED | WSTOPPED | WCONTINUED,
	                 E_INVALID_ARGUMENT_CONTEXT_WAITID_OPTIONS);
	if (!(options & (WEXITED | WSTOPPED | WCONTINUED)))
		THROW(E_INVALID_ARGUMENT_BAD_FLAG_COMBINATION,
		      E_INVALID_ARGUMENT_CONTEXT_WAITID_OPTIONS,
		      options,
		      WEXITED | WSTOPPED | WCONTINUED,
		      0);
	if (which > P_PGID)
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_WAITID_WHICH,
		      which);
	validate_writable_opt(infop, sizeof(*infop));
	validate_writable_opt(ru, sizeof(*ru));
	if (ru) {
		struct rusage kru;
		result = waitfor_children((idtype_t)which, upid, options,
		                          NULL, infop ? &info : NULL, &kru);
		if (E_ISOK(result))
			rusage_to_compat_rusage64(&kru, ru);
	} else {
		result = waitfor_children((idtype_t)which, upid, options,
		                          NULL, infop ? &info : NULL, NULL);
	}
	if (E_ISOK(result) && infop)
		siginfo_to_compat_siginfo(&info, infop);
	return result;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_WAITID64 */

#ifdef __ARCH_WANT_SYSCALL_WAITPID
DEFINE_SYSCALL3(pid_t, waitpid,
                pid_t, pid, int32_t *, stat_loc,
                syscall_ulong_t, options) {
	return sys_wait4(pid, stat_loc, options, NULL);
}
#endif /* __ARCH_WANT_SYSCALL_WAITPID */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_WAITPID
DEFINE_COMPAT_SYSCALL3(pid_t, waitpid,
                       pid_t, pid, int32_t *, stat_loc,
                       syscall_ulong_t, options) {
	return sys_wait4(pid, stat_loc, options, NULL);
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_WAITPID */

#ifdef __ARCH_WANT_SYSCALL_WAIT4
DEFINE_SYSCALL4(pid_t, wait4, pid_t, upid,
                NCX UNCHECKED int32_t *, wstatus,
                syscall_ulong_t, options,
                NCX UNCHECKED struct __rusage32 *, ru) {
	idtype_t which;
	pid_t result;
	VALIDATE_FLAGSET(options,
	                 WNOHANG | WSTOPPED | WCONTINUED | WNOREAP,
	                 E_INVALID_ARGUMENT_CONTEXT_WAIT4_OPTIONS);
	options |= WEXITED;
	validate_writable_opt(wstatus, sizeof(*wstatus));
	validate_writable_opt(ru, sizeof(*ru));
	if (upid < -1) {
		upid  = -upid;
		which = (idtype_t)P_PGID;
	} else if (upid == -1) {
		upid  = 0;
		which = (idtype_t)P_ALL;
	} else if (upid == 0) {
		/* wait for any child process whose process group ID is equal to that of the calling process. */
		upid  = task_getpgid_s();
		which = (idtype_t)P_PGID;
	} else {
		/* wait for the child whose process ID is equal to the value of pid. */
		which = (idtype_t)P_PID;
	}
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME_T__
	result = waitfor_children(which, upid, options, wstatus, NULL, ru);
#else /* __SIZEOF_TIME32_T__ == __SIZEOF_TIME_T__ */
	if (ru) {
		struct rusage kru;
		result = waitfor_children(which, upid, options, wstatus, NULL, &kru);
		if (E_ISOK(result))
			rusage_to_rusage32(&kru, ru);
	} else {
		result = waitfor_children(which, upid, options, wstatus, NULL, NULL);
	}
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME_T__ */
	return result;
}
#endif /* __ARCH_WANT_SYSCALL_WAIT4 */

#ifdef __ARCH_WANT_SYSCALL_WAIT4_64
DEFINE_SYSCALL4(pid_t, wait4_64, pid_t, upid,
                NCX UNCHECKED int32_t *, wstatus,
                syscall_ulong_t, options,
                NCX UNCHECKED struct rusage64 *, ru) {
	idtype_t which;
	pid_t result;
	VALIDATE_FLAGSET(options,
	                 WNOHANG | WSTOPPED | WCONTINUED | WNOREAP,
	                 E_INVALID_ARGUMENT_CONTEXT_WAIT4_OPTIONS);
	options |= WEXITED;
	validate_writable_opt(wstatus, sizeof(*wstatus));
	validate_writable_opt(ru, sizeof(*ru));
	if (upid < -1) {
		upid  = -upid;
		which = (idtype_t)P_PGID;
	} else if (upid == -1) {
		upid  = 0;
		which = (idtype_t)P_ALL;
	} else if (upid == 0) {
		/* wait for any child process whose process group ID is equal to that of the calling process. */
		upid  = task_getpgid_s();
		which = (idtype_t)P_PGID;
	} else {
		/* wait for the child whose process ID is equal to the value of pid. */
		which = (idtype_t)P_PID;
	}
#if __SIZEOF_TIME64_T__ == __SIZEOF_TIME_T__
	result = waitfor_children(which, upid, options, wstatus, NULL, ru);
#else /* __SIZEOF_TIME64_T__ == __SIZEOF_TIME_T__ */
	if (ru) {
		struct rusage kru;
		result = waitfor_children(which, upid, options, wstatus, NULL, &kru);
		if (E_ISOK(result))
			rusage_to_rusage64(&kru, ru);
	} else {
		result = waitfor_children(which, upid, options, wstatus, NULL, NULL);
	}
#endif /* __SIZEOF_TIME64_T__ != __SIZEOF_TIME_T__ */
	return result;
}
#endif /* __ARCH_WANT_SYSCALL_WAIT4_64 */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_WAIT4
DEFINE_COMPAT_SYSCALL4(pid_t, wait4, pid_t, upid,
                       NCX UNCHECKED int32_t *, wstatus,
                       syscall_ulong_t, options,
                       NCX UNCHECKED struct compat_rusage32 *, ru) {
	idtype_t which;
	pid_t result;
	VALIDATE_FLAGSET(options,
	                 WNOHANG | WSTOPPED | WCONTINUED | WNOREAP,
	                 E_INVALID_ARGUMENT_CONTEXT_WAIT4_OPTIONS);
	options |= WEXITED;
	validate_writable_opt(wstatus, sizeof(*wstatus));
	validate_writable_opt(ru, sizeof(*ru));
	if (upid < -1) {
		upid  = -upid;
		which = (idtype_t)P_PGID;
	} else if (upid == -1) {
		upid  = 0;
		which = (idtype_t)P_ALL;
	} else if (upid == 0) {
		/* wait for any child process whose process group ID is equal to that of the calling process. */
		upid  = task_getpgid_s();
		which = (idtype_t)P_PGID;
	} else {
		/* wait for the child whose process ID is equal to the value of pid. */
		which = (idtype_t)P_PID;
	}
	if (ru) {
		struct rusage kru;
		result = waitfor_children(which, upid, options, wstatus, NULL, &kru);
		if (E_ISOK(result))
			rusage_to_compat_rusage32(&kru, ru);
	} else {
		result = waitfor_children(which, upid, options, wstatus, NULL, NULL);
	}
	return result;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_WAIT4 */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_WAIT4_64
DEFINE_COMPAT_SYSCALL4(pid_t, wait4_64, pid_t, upid,
                       NCX UNCHECKED int32_t *, wstatus,
                       syscall_ulong_t, options,
                       NCX UNCHECKED struct compat_rusage64 *, ru) {
	idtype_t which;
	pid_t result;
	VALIDATE_FLAGSET(options,
	                 WNOHANG | WSTOPPED | WCONTINUED | WNOREAP,
	                 E_INVALID_ARGUMENT_CONTEXT_WAIT4_OPTIONS);
	options |= WEXITED;
	validate_writable_opt(wstatus, sizeof(*wstatus));
	validate_writable_opt(ru, sizeof(*ru));
	if (upid < -1) {
		upid  = -upid;
		which = (idtype_t)P_PGID;
	} else if (upid == -1) {
		upid  = 0;
		which = (idtype_t)P_ALL;
	} else if (upid == 0) {
		/* wait for any child process whose process group ID is equal to that of the calling process. */
		upid  = task_getpgid_s();
		which = (idtype_t)P_PGID;
	} else {
		/* wait for the child whose process ID is equal to the value of pid. */
		which = (idtype_t)P_PID;
	}
	if (ru) {
		struct rusage kru;
		result = waitfor_children(which, upid, options, wstatus, NULL, &kru);
		if (E_ISOK(result))
			rusage_to_compat_rusage64(&kru, ru);
	} else {
		result = waitfor_children(which, upid, options, wstatus, NULL, NULL);
	}
	return result;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_WAIT4_64 */

DECL_END

#endif /* !GUARD_KERNEL_SRC_SCHED_GROUP_C */
