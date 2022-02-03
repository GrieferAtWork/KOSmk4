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
#ifndef GUARD_KERNEL_INCLUDE_SCHED_GROUP_NEW_H
#define GUARD_KERNEL_INCLUDE_SCHED_GROUP_NEW_H 1

#include <kernel/compiler.h>

#ifdef CONFIG_USE_NEW_GROUP
#include <kernel/types.h>
#include <sched/pid.h>
#include <sched/signal.h>

#include <hybrid/sequence/list.h>
#include <hybrid/sync/atomic-rwlock.h>

#include <kos/aref.h>
#include <kos/lockop.h>


#ifdef __CC__
DECL_BEGIN

struct taskpid;

#ifndef __taskpid_list_defined
#define __taskpid_list_defined
LIST_HEAD(taskpid_list, taskpid);
#endif /* !__taskpid_list_defined */

#ifndef __task_arref_defined
#define __task_arref_defined
ARREF(task_arref, task);
#endif /* !__task_arref_defined */

#ifndef __taskpid_arref_defined
#define __taskpid_arref_defined
ARREF(taskpid_arref, taskpid);
#endif /* !__taskpid_arref_defined */

#ifndef __task_list_defined
#define __task_list_defined
LIST_HEAD(task_list, task);
#endif /* !__task_list_defined */

/* For `posix-signal' */
struct pending_rpc; /* Define in `rpc-internal.h' */
#ifndef __pending_rpc_slist_defined
#define __pending_rpc_slist_defined
SLIST_HEAD(pending_rpc_slist, pending_rpc);
#endif /* !__pending_rpc_slist_defined */


/* ============== Controller for processes / process groups / sessions ==============
 *
 * [1..1] Process of thread: >> struct taskpid *proc        = THIS_TASKPID->tp_proc;
 * [1..1] Process parent:    >> REF struct task *parent     = arref_get(&THIS_TASKPID->tp_pctl->pc_parent);
 * [1..1] Process group:     >> REF struct procgrp *grp     = arref_get(&THIS_TASKPID->tp_pctl->pc_grp);
 * [1..1] Process session:   >> REF struct procsession *ses = arref_get(&grp->pgc_session);
 *
 * Enumerate threads/children of process (WARNING: E_WOULDBLOCK):
 * >> struct taskpid *tpid;
 * >> struct procctl *ctl = _task_getproctl();
 * >> procctl_chlds_read(ctl);
 * >> // NOTE: This enumeration does not include task_getprocess()!
 * >> LIST_FOREACH (tpid, &ctl->pc_chlds, tp_parsib) {
 * >>     if (taskpid_isaprocess(tpid)) {
 * >>         assert(tpid->tp_pctl != ctl);
 * >>         assert(arref_ptr(&tpid->tp_pctl->pc_parent) == THIS_TASK);
 * >>         // Child process: `tpid'
 * >>     } else {
 * >>         // Thread: `tpid' (but doesn't include `THIS_TASKPID')
 * >>     }
 * >> }
 * >> procctl_chlds_endread(ctl);
 *
 * Enumerate process in a process group (WARNING: E_WOULDBLOCK):
 * >> struct procgrp *grp = ...;
 * >> struct taskpid *tpid;
 * >> procgrp_read(grp);
 * >> LIST_FOREACH (tpid, &grp->pc_chlds, tp_pctl->pc_grpmember) {
 * >>     assert(taskpid_isaprocess(tpid));
 * >>     assert(arref_ptr(&tpid->tp_pctl->pc_grp) == grp);
 * >>     // Member process: `tpid'
 * >> }
 * >> procgrp_endread(grp);
 */


struct ttydev;
#ifndef __ttydev_device_axref_defined
#define __ttydev_device_axref_defined
AXREF(ttydev_device_axref, ttydev);
#endif /* !__ttydev_device_axref_defined */

struct procsession {
	WEAK refcnt_t              ps_refcnt; /* Reference counter. */
	struct ttydev_device_axref ps_ctty;   /* [0..1] The controlling terminal; aka. "/dev/tty" (if any) */
};

/* Destroy the given process session. */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL procsession_destroy)(struct procsession *__restrict self);
DEFINE_REFCOUNT_FUNCTIONS(struct procsession, ps_refcnt, procsession_destroy)


struct procgrp;
struct procgrp_slot {
	LLRBTREE_NODE(procgrp) pgs_link; /* [0..1][lock(:pgc_ns->[pn_par...]->pn_lock)]
	                                  * Link entry within the associated PID namespace */
	upid_t                 pgs_pid;  /* [const] PID relevant to this slot. (s.a. `__TASKPID_SLOT_*') */
	/* TODO: When implementing LLRB operators for these slots, alter `_pidns_tree_*'
	 *       functions  to  take  `offsetof_slot',  at  which  point  we  can   pass
	 *       `offsetof(struct taskpid, tp_pids[ind])', or
	 *       `offsetof(struct procgrp, pgc_pids[ind])'. */
};

struct procgrp {
	WEAK refcnt_t                                pgc_refcnt;  /* Reference counter. */
	REF struct procsession                      *pgc_session; /* [1..1][const] Session associated with this process group. */
	Toblockop_slist(procgrp)                     pgc_lops;    /* Lock-ops for `pgc_lock' */
	struct atomic_rwlock                         pgc_lock;    /* Lock for `pgc_list' */
	struct WEAK taskpid_list                     pgc_list;    /* [0..n][LINK(tp_pctl->pc_grpmember)][lock(pgc_lock)]
	                                                           * List of processes apart of this group (including the group leader).
	                                                           * Members of  this list  automatically remove  themselves upon  being
	                                                           * destroyed (aka. inside of `taskpid_destroy()'). */
	REF struct pidns                            *pgc_ns;      /* [1..1][const] Top-level PID namespace containing this descriptor. */
	COMPILER_FLEXIBLE_ARRAY(struct procgrp_slot, pgc_pids);   /* [const][tp_ns->pn_ind+1] Task PID value from different namespaces. */
};

/* Destroy the given process group. */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL procgrp_destroy)(struct procgrp *__restrict self);
DEFINE_REFCOUNT_FUNCTIONS(struct procgrp, pgc_refcnt, procgrp_destroy)





#ifndef __procgrp_arref_defined
#define __procgrp_arref_defined
ARREF(procgrp_arref, procgrp);
#endif /* !__procgrp_arref_defined */

struct procctl {
	struct atomic_rwlock     pc_chlds_lock;   /* Lock for `pc_chlds' */
	struct REF taskpid_list  pc_chlds;        /* [0..n][lock(pc_chlds_lock)][link(tp_parsib)]
	                                           * Child tasks of  this process. This  includes
	                                           * both threads  (other than  the main  thread)
	                                           * within  the  process, as  well  as processes
	                                           * that were fork'd from this one. */
	struct sig               pc_chld_changed; /* Broadcast when one of `pc_chlds' changes status.
	                                           * (s.a. `struct taskpid::tp_changed') */
	struct task_arref        pc_parent;       /* [1..1][lock(READ(ATOMIC), WRITE(OLD->pc_chlds_lock &&
	                                           *                                 NEW->pc_chlds_lock))]
	                                           * Parent process. When the parent thread exits, it will
	                                           * re-parent  all of its remaining children to boottask. */
	struct atomic_rwlock     pc_sig_lock;     /* Lock for `pc_sig_list'. */
	struct pending_rpc_slist pc_sig_list;     /* [0..n][lock(APPEND(ATOMIC), REMOVE(pc_sig_lock))]
	                                           * List of pending RPCs directed at the process as a whole. When
	                                           * set  to `THIS_RPCS_TERMINATED', the  process is considered as
	                                           * terminated and no additional RPCs can be enqueued.
	                                           * NOTE: User-RPCs must not have the `RPC_SYNCMODE_F_REQUIRE_SC'
	                                           *       or `RPC_SYNCMODE_F_REQUIRE_CP'  flag set.  If they  do,
	                                           *       an internal assertion check will trigger. */
	struct sig               pc_sig_more;     /* A signal that is broadcast whenever something is added to `pc_sig_list'
	                                           * This  signal is _only_  used to implement  `signalfd(2)', as you're not
	                                           * normally supposed to "wait" for signals to arrive; you just always  get
	                                           * a sporadic interrupt once they do arrive. */
	struct procgrp_arref     pc_grp;          /* [1..1][lock(READ(ATOMIC), WRITE(OLD->pgc_lock &&
	                                           *                                 NEW->pgc_lock))]
	                                           * Process group controller. */
	LIST_ENTRY(taskpid)      pc_grpmember;    /* [0..1][lock(pc_grp->pgc_lock)] Process group member link. */
};

#define taskpid_isaprocess(self) ((self)->tp_proc == (self))
#define task_getprocesspid()     THIS_TASKPID->tp_proc                    /* struct taskpid * [1..1] */
#define _task_getproctl()        THIS_TASKPID->tp_pctl                    /* struct procctl * [1..1] */
#define task_getparentprocess()  awref_get(&_task_getproctl()->pc_parent) /* REF struct task * [0..1] */


/* Session used by `procgrp_kernel' (and consequently also by `/bin/init') */
DATDEF struct procsession procsession_kernel;

/* Special process group with `pgid == 0'  used for kernel threads (and  /bin/init)
 * Because we use  `pgid == 0', `setpgid(2)'  cannot be  used to  join this  group,
 * since passing it `0' as the target process group ID is an alias for `getpid(2)'. */
DATDEF struct procgrp procgrp_kernel;

/* Process controller for kernel threads. */
DATDEF struct procctl procctl_kernel;

/* Process controller for `boottask' (aka. `/bin/init') */
DATDEF struct procctl procctl_boottask;


DECL_END
#endif /* __CC__ */
#endif /* CONFIG_USE_NEW_GROUP */

#endif /* !GUARD_KERNEL_INCLUDE_SCHED_GROUP_NEW_H */
