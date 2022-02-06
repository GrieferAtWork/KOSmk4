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
#ifndef GUARD_KERNEL_INCLUDE_SCHED_GROUP_H
#define GUARD_KERNEL_INCLUDE_SCHED_GROUP_H 1

#include <kernel/compiler.h>

#ifdef CONFIG_USE_NEW_GROUP
#include <sched/group-new.h>

/* Backwards-compatibility */
#define THIS_PROCESS_RPCS                 (*THIS_TASKPID->tp_pctl)
#define process_pending_rpcs              procctl
#define ppr_lock                          pc_sig_lock
#define ppr_list                          pc_sig_list
#define ppr_more                          pc_sig_more
#define process_pending_rpcs_mustreap     procctl_chlds_mustreap
#define process_pending_rpcs_reap         _procctl_chlds_reap
#define _process_pending_rpcs_reap        procctl_chlds_reap
#define process_pending_rpcs_write        procctl_chlds_write
#define process_pending_rpcs_write_nx     procctl_chlds_write_nx
#define process_pending_rpcs_trywrite     procctl_chlds_trywrite
#define process_pending_rpcs_endwrite     procctl_chlds_endwrite
#define _process_pending_rpcs_endwrite    _procctl_chlds_endwrite
#define process_pending_rpcs_read         procctl_chlds_read
#define process_pending_rpcs_read_nx      procctl_chlds_read_nx
#define process_pending_rpcs_tryread      procctl_chlds_tryread
#define _process_pending_rpcs_endread     _procctl_chlds_endread
#define process_pending_rpcs_endread      procctl_chlds_endread
#define _process_pending_rpcs_end         _procctl_chlds_end
#define process_pending_rpcs_end          procctl_chlds_end
#define process_pending_rpcs_upgrade      procctl_chlds_upgrade
#define process_pending_rpcs_upgrade_nx   procctl_chlds_upgrade_nx
#define process_pending_rpcs_tryupgrade   procctl_chlds_tryupgrade
#define process_pending_rpcs_downgrade    procctl_chlds_downgrade
#define process_pending_rpcs_reading      procctl_chlds_reading
#define process_pending_rpcs_writing      procctl_chlds_writing
#define process_pending_rpcs_canread      procctl_chlds_canread
#define process_pending_rpcs_canwrite     procctl_chlds_canwrite
#define process_pending_rpcs_waitread     procctl_chlds_waitread
#define process_pending_rpcs_waitwrite    procctl_chlds_waitwrite
#define process_pending_rpcs_waitread_nx  procctl_chlds_waitread_nx
#define process_pending_rpcs_waitwrite_nx procctl_chlds_waitwrite_nx

#else /* CONFIG_USE_NEW_GROUP */
#include <kernel/types.h>
#include <sched/pertask.h>
#ifndef GUARD_KERNEL_INCLUDE_SCHED_PID_H
#include <sched/pid.h>
#endif /* !GUARD_KERNEL_INCLUDE_SCHED_PID_H */
#include <sched/sig.h>

#include <hybrid/sequence/list.h>
#include <hybrid/sync/atomic-rwlock.h>

#include <kos/aref.h>
#include <sys/wait.h>

#ifndef __INTELLISENSE__
#include <sched/task.h>

#include <hybrid/__assert.h>
#include <hybrid/__atomic.h>
#endif /* !__INTELLISENSE__ */


DECL_BEGIN

#ifdef __CC__

/* For `posix-signal' */
struct pending_rpc; /* Define in `rpc-internal.h' */
#ifndef __pending_rpc_slist_defined
#define __pending_rpc_slist_defined
SLIST_HEAD(pending_rpc_slist, pending_rpc);
#endif /* !__pending_rpc_slist_defined */

struct process_pending_rpcs {
	struct atomic_rwlock     ppr_lock; /* Lock for `ppr_list'. */
	struct pending_rpc_slist ppr_list; /* [0..n][lock(APPEND(ATOMIC), REMOVE(ppr_lock))]
	                                    * List of pending RPCs directed at the process as a whole. When
	                                    * set  to `THIS_RPCS_TERMINATED', the  process is considered as
	                                    * terminated and no additional RPCs can be enqueued.
	                                    * NOTE: User-RPCs must not have the `RPC_SYNCMODE_F_REQUIRE_SC'
	                                    *       or `RPC_SYNCMODE_F_REQUIRE_CP'  flag set.  If they  do,
	                                    *       an internal assertion check will trigger. */
	struct sig               ppr_more; /* A signal that is broadcast  whenever something is added to  `ppr_list'
	                                    * This signal is _only_ used  to implement `signalfd(2)', as you're  not
	                                    * normally supposed to "wait" for signals to arrive; you just always get
	                                    * a sporadic interrupt once they do arrive. */
};

/* Helper macros for `struct driver::ppr_lock' */
#define process_pending_rpcs_mustreap(self)     0
#define process_pending_rpcs_reap(self)         (void)0
#define _process_pending_rpcs_reap(self)        (void)0
#define process_pending_rpcs_write(self)        atomic_rwlock_write(&(self)->ppr_lock)
#define process_pending_rpcs_write_nx(self)     atomic_rwlock_write_nx(&(self)->ppr_lock)
#define process_pending_rpcs_trywrite(self)     atomic_rwlock_trywrite(&(self)->ppr_lock)
#define process_pending_rpcs_endwrite(self)     (atomic_rwlock_endwrite(&(self)->ppr_lock), process_pending_rpcs_reap(self))
#define _process_pending_rpcs_endwrite(self)    atomic_rwlock_endwrite(&(self)->ppr_lock)
#define process_pending_rpcs_read(self)         atomic_rwlock_read(&(self)->ppr_lock)
#define process_pending_rpcs_read_nx(self)      atomic_rwlock_read_nx(&(self)->ppr_lock)
#define process_pending_rpcs_tryread(self)      atomic_rwlock_tryread(&(self)->ppr_lock)
#define _process_pending_rpcs_endread(self)     atomic_rwlock_endread(&(self)->ppr_lock)
#define process_pending_rpcs_endread(self)      (void)(atomic_rwlock_endread(&(self)->ppr_lock) && (process_pending_rpcs_reap(self), 0))
#define _process_pending_rpcs_end(self)         atomic_rwlock_end(&(self)->ppr_lock)
#define process_pending_rpcs_end(self)          (void)(atomic_rwlock_end(&(self)->ppr_lock) && (process_pending_rpcs_reap(self), 0))
#define process_pending_rpcs_upgrade(self)      atomic_rwlock_upgrade(&(self)->ppr_lock)
#define process_pending_rpcs_upgrade_nx(self)   atomic_rwlock_upgrade_nx(&(self)->ppr_lock)
#define process_pending_rpcs_tryupgrade(self)   atomic_rwlock_tryupgrade(&(self)->ppr_lock)
#define process_pending_rpcs_downgrade(self)    atomic_rwlock_downgrade(&(self)->ppr_lock)
#define process_pending_rpcs_reading(self)      atomic_rwlock_reading(&(self)->ppr_lock)
#define process_pending_rpcs_writing(self)      atomic_rwlock_writing(&(self)->ppr_lock)
#define process_pending_rpcs_canread(self)      atomic_rwlock_canread(&(self)->ppr_lock)
#define process_pending_rpcs_canwrite(self)     atomic_rwlock_canwrite(&(self)->ppr_lock)
#define process_pending_rpcs_waitread(self)     atomic_rwlock_waitread(&(self)->ppr_lock)
#define process_pending_rpcs_waitwrite(self)    atomic_rwlock_waitwrite(&(self)->ppr_lock)
#define process_pending_rpcs_waitread_nx(self)  atomic_rwlock_waitread_nx(&(self)->ppr_lock)
#define process_pending_rpcs_waitwrite_nx(self) atomic_rwlock_waitwrite_nx(&(self)->ppr_lock)


FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(KCALL process_pending_rpcs_fini)(struct process_pending_rpcs *__restrict self);

/* Pending RPCs for the calling process. */
#define THIS_PROCESS_RPCS \
	FORTASK(task_getprocess(), this_taskgroup.tg_proc_rpcs)

struct ttydev;
struct pending_rpc;

#ifndef __taskpid_list_defined
#define __taskpid_list_defined
LIST_HEAD(taskpid_list, REF taskpid);
#endif /* !__taskpid_list_defined */
#ifndef __task_list_defined
#define __task_list_defined
LIST_HEAD(task_list, WEAK task);
#endif /* !__task_list_defined */

#ifndef __ttydev_axref_defined
#define __ttydev_axref_defined
AXREF(ttydev_axref, ttydev);
#endif /* !__ttydev_axref_defined */


struct taskgroup {
	/* Controller structure for tracing task association within/between
	 * processes, process groups, as well as sessions. */
	REF struct task             *tg_process;             /* [1..1][ref_if(!= THIS_TASK)][const]
	                                                      * Process leader (the main-thread of the associated process).
	                                                      * When this thread terminates, all other threads within the process also die.
	                                                      * @assume(tg_process == FORTASK(tg_process,this_taskgroup).tg_process)
	                                                      * NOTE:
	                                                      *   - When  set to `THIS_TASK',  the calling thread  is a process leader,
	                                                      *     also meaning that the `tp_parsib' chain within its PID  structure
	                                                      *     is set up to form a chain of all other sibling processes within the
	                                                      *     same process group.
	                                                      *   - When  set  to something  different, the  calling  thread is  a worker
	                                                      *     thread, meaning that the `tp_parsib' chain within its PID structure
	                                                      *     is apart of a chain of other worker threads.
	                                                      *   - Any kernel thread is always its own process. */
	/* All of the following fields are only valid when `tg_process == THIS_TASK' (Otherwise, they are all `[0..1][const]') */
	union {
		struct pending_rpc      *tg_thread_exit;         /* [valid_if(tg_process != THIS_TASK)][lock(PRIVATE(tg_process), CLEAR_ONCE)][0..1][owned]
		                                                  * A pre-allocated RPC used by the process leader to propagate its exit status to this thread. */
		struct atomic_rwlock     tg_proc_threads_lock;   /* [valid_if(tg_process == THIS_TASK)] Lock for `tg_proc_threads' */
	};
	union {
#define TASKGROUP_TG_PROC_THREADS_TERMINATED ((REF struct taskpid *)-1)
		struct taskpid_list      tg_proc_threads;        /* [0..1][lock(tg_proc_threads_lock)][valid_if(tg_process == THIS_TASK)]
		                                                  * Chain  of  threads &  child processes  of this  process  (excluding the  calling (aka.  leader) thread)
		                                                  * Child processes are removed from this chain, either by being `detach(2)'ed, or by being `wait(2)'ed on.
		                                                  * NOTE: This chain is set to `TASKGROUP_TG_PROC_THREADS_TERMINATED' once the associated
		                                                  *       process  terminates,  in order  to prevent  any new  threads from  being added.
		                                                  * NOTE: When a thread is detached, the `tg_thread_detached' field is updated */
#define FOREACH_taskgroup__proc_threads(taskpid_elem, group)                                              \
	if (((taskpid_elem) = LIST_FIRST(&(group)->tg_proc_threads)) == TASKGROUP_TG_PROC_THREADS_TERMINATED) \
		;                                                                                                 \
	else                                                                                                  \
		for (; (taskpid_elem); (taskpid_elem) = LIST_NEXT(taskpid_elem, tp_parsib))
#define TASKGROUP_TG_THREAD_DETACHED_NO         0 /* The thread is not detached */
#define TASKGROUP_TG_THREAD_DETACHED_YES        1 /* The thread is detached */
#define TASKGROUP_TG_THREAD_DETACHED_TERMINATED 2 /* The thread has terminated */
		uintptr_t                tg_thread_detached;     /* [valid_if(tg_process != THIS_TASK)] Thread detach state (one of `TASKGROUP_TG_THREAD_DETACHED_*') */
	};
	struct sig                   tg_proc_threads_change; /* Broadcast when one of the  threads (or child processes)  of this process changes  state.
	                                                      * For this purpose, the changed child has previously set its `tp_status' field to describe
	                                                      * its new state.
	                                                      * Also: Broadcasts are performed through `sig_altbroadcast()', with the sender set to the
	                                                      *      `struct taskpid *' of the child which has changed state. */
	struct atomic_rwlock         tg_proc_parent_lock;    /* Lock for `tg_proc_parent' */
	WEAK struct task            *tg_proc_parent;         /* [0..1][const] The parent of this process.
	                                                      * @assume(tg_proc_parent == FORTASK(tg_proc_parent,this_taskgroup).tg_process)
	                                                      * In  the event  that this  process has  a parent, `THIS_TASKPID->tp_parsib'
	                                                      * is    a     link    within     `tg_proc_parent->tp_thread->tg_proc_threads'.
	                                                      * In the event that the parent process terminates before its child, this field
	                                                      * gets set to `NULL', at  which point `THIS_TASKPID->tp_parsib' is  unbound. */
	struct atomic_rwlock         tg_proc_group_lock;     /* Lock for `tg_proc_group' */
	REF struct taskpid          *tg_proc_group;          /* [1..1][lock(tg_proc_group_lock)]
	                                                      * @assume(tg_proc_procgroup == FORTASK(taskpid_gettask(tg_proc_procgroup), this_taskgroup).tg_proc_procgroup)
	                                                      * The leader of the associated process group.
	                                                      * When set to `THIS_TASKPID', then the calling thread is a process group leader. */
	LIST_ENTRY(WEAK task)        tg_proc_group_siblings; /* [0..1][lock(tg_proc_group->tg_pgrp_processes_lock)]
	                                                      * [valid_if(THIS_TASKPID != tg_proc_group &&
	                                                      *           taskpid_gettask(tg_proc_group) != NULL)]
	                                                      * Chain of sibling processes within the same process group.
	                                                      * The base of this chain is `taskpid_gettask(tg_proc_group)->tg_pgrp_processes' */
	struct process_pending_rpcs  tg_proc_rpcs;           /* Pending RPCs of this process as a whole. */
	/* All of the following fields are only valid when `tg_proc_group == THIS_TASKPID' (Otherwise, they are all `[0..1][const]') */
	struct atomic_rwlock         tg_pgrp_processes_lock; /* Lock for `tg_pgrp_processes' */
	struct task_list             tg_pgrp_processes;      /* [0..1] Chain of processes within this  process group (excluding the calling  process)
	                                                      * NOTE: This list of processes is chained using the `tg_proc_group_siblings' list node. */
#define KEY__this_taskgroup__tg_proc_group_siblings(thread) \
	FORTASK(thread, this_taskgroup).tg_proc_group_siblings
#define FOREACH_taskgroup__pgrp_processes(proc, group) \
	LIST_FOREACH_P(proc, &(group)->tg_pgrp_processes, KEY__this_taskgroup__tg_proc_group_siblings)
	struct atomic_rwlock         tg_pgrp_session_lock;   /* Lock for `tg_pgrp_session' */
	REF struct taskpid          *tg_pgrp_session;        /* [1..1][const_if(== THIS_TASKPID)][lock(tg_pgrp_session_lock)]
	                                                      * @assume(tg_pgrp_session == FORTASK(taskpid_gettask(tg_pgrp_session), this_taskgroup).tg_pgrp_session)
	                                                      * The session leader of the this process group.
	                                                      * When set to `THIS_TASKPID', then the calling thread is that leader. */
	/* All of the following fields are only valid when `tg_pgrp_session == THIS_TASKPID' (Otherwise, they are all `[0..1][const]') */
	struct ttydev_axref   tg_ctty;                /* [0..1] The controlling terminal  (/dev/tty) associated  with this  session
	                                                      * When non-NULL, `tg_ctty->t_cproc == THIS_TASKPID' (for the session leader) */
};


DATDEF ATTR_PERTASK struct taskgroup this_taskgroup;
#define THIS_TASKGROUP       PERTASK(this_taskgroup)

#ifdef __INTELLISENSE__
/* Returns a pointer to the process associated with the calling/given thread.
 * NOTE:   These   functions   return   `NULL'   for   kernel-space   thread! */
NOBLOCK WUNUSED /*ATTR_RETNONNULL*/ ATTR_CONST struct task *KCALL task_getprocess(void);
NOBLOCK WUNUSED /*ATTR_RETNONNULL*/ ATTR_CONST struct taskpid *KCALL task_getprocesspid(void);
NOBLOCK WUNUSED /*ATTR_RETNONNULL*/ ATTR_CONST NONNULL((1)) struct task *KCALL task_getprocess_of(struct task const *__restrict thread);
NOBLOCK WUNUSED /*ATTR_RETNONNULL*/ ATTR_CONST NONNULL((1)) struct taskpid *KCALL task_getprocesspid_of(struct task const *__restrict thread);
#else /* __INTELLISENSE__ */
#define task_getprocess()              ((struct task *)PERTASK_GET(this_taskgroup.tg_process))
#define task_getprocesspid()           FORTASK(task_getprocess(), this_taskpid)
#define task_getprocess_of(thread)     ((struct task *)FORTASK(thread, this_taskgroup).tg_process)
#define task_getprocesspid_of(thread)  FORTASK(task_getprocess_of(thread), this_taskpid)
#endif /* !__INTELLISENSE__ */

/* Returns  a  reference  to  the  parent  of  the  calling/given process.
 * If that parent has already terminated and has already been detach(2)ed,
 * or wait(2)ed, return `NULL' instead. */
LOCAL WUNUSED REF struct task *KCALL task_getprocessparent(void) THROWS(E_WOULDBLOCK);
LOCAL WUNUSED REF struct taskpid *KCALL task_getprocessparentpid(void) THROWS(E_WOULDBLOCK);
LOCAL WUNUSED NONNULL((1)) REF struct task *KCALL task_getprocessparent_of(struct task *__restrict thread) THROWS(E_WOULDBLOCK);
LOCAL WUNUSED NONNULL((1)) REF struct taskpid *KCALL task_getprocessparentpid_of(struct task *__restrict thread) THROWS(E_WOULDBLOCK);
LOCAL WUNUSED REF struct task *NOTHROW(KCALL task_getprocessparent_nx)(void);
LOCAL WUNUSED REF struct taskpid *NOTHROW(KCALL task_getprocessparentpid_nx)(void);
LOCAL WUNUSED NONNULL((1)) REF struct task *NOTHROW(KCALL task_getprocessparent_of_nx)(struct task *__restrict thread);
LOCAL WUNUSED NONNULL((1)) REF struct taskpid *NOTHROW(KCALL task_getprocessparentpid_of_nx)(struct task *__restrict thread);
LOCAL WUNUSED NONNULL((1)) struct task *NOTHROW(KCALL task_getprocessparentptr_of)(struct task *__restrict thread);

/* Check if the given task was orphaned (no longer has a parent process) */
LOCAL ATTR_PURE WUNUSED bool NOTHROW(KCALL task_isorphan)(void);
LOCAL ATTR_PURE WUNUSED NONNULL((1)) bool NOTHROW(KCALL task_isorphan_p)(struct task *__restrict thread);
LOCAL ATTR_PURE WUNUSED NONNULL((1)) bool NOTHROW(KCALL taskpid_isorphan_p)(struct taskpid *__restrict self);

/* Detach the given `thread' from its parent
 * @return: true:  Successfully detached the given `thread'.
 * @return: false: The given `thread' had already been detached. */
FUNDEF bool KCALL task_detach(struct task *__restrict thread) THROWS(E_WOULDBLOCK);

/* Detach all child threads/processes of the given `process'
 * @assume(process == task_getprocess_of(process));
 * @return: * : The number of detached children. */
FUNDEF size_t KCALL task_detach_children(struct task *__restrict process) THROWS(E_WOULDBLOCK);


/* Return a reference to the leader of the process group of the calling/given thread. */
LOCAL WUNUSED REF struct task *KCALL task_getprocessgroupleader(void) THROWS(E_WOULDBLOCK);
LOCAL ATTR_RETNONNULL WUNUSED REF struct task *KCALL task_getprocessgroupleader_srch(void) THROWS(E_WOULDBLOCK, E_PROCESS_EXITED);
LOCAL ATTR_RETNONNULL WUNUSED REF struct taskpid *KCALL task_getprocessgroupleaderpid(void) THROWS(E_WOULDBLOCK);
LOCAL WUNUSED NONNULL((1)) REF struct task *KCALL task_getprocessgroupleader_of(struct task *__restrict thread) THROWS(E_WOULDBLOCK);
LOCAL ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct task *KCALL task_getprocessgroupleader_srch_of(struct task *__restrict thread) THROWS(E_WOULDBLOCK, E_PROCESS_EXITED);
LOCAL ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct taskpid *KCALL task_getprocessgroupleaderpid_of(struct task *__restrict thread) THROWS(E_WOULDBLOCK);
LOCAL WUNUSED REF struct task *NOTHROW(KCALL task_getprocessgroupleader_nx)(void);
LOCAL WUNUSED REF struct taskpid *NOTHROW(KCALL task_getprocessgroupleaderpid_nx)(void);
LOCAL WUNUSED NONNULL((1)) REF struct task *NOTHROW(KCALL task_getprocessgroupleader_of_nx)(struct task *__restrict thread);
LOCAL WUNUSED NONNULL((1)) REF struct taskpid *NOTHROW(KCALL task_getprocessgroupleaderpid_of_nx)(struct task *__restrict thread);

/* Return a reference to the session leader of the process group of the calling/given thread.
 * NOTE: After the process group leader has died, it's PID implicitly becomes the session leader PID.
 *       This way, code can be simplified since `task_getsessionleaderpid()' always returns non-NULL,
 *       and always returns a dead  taskpid once either the current  session, or the current  process
 *       group have exited. */
LOCAL WUNUSED REF struct task *KCALL task_getsessionleader(void) THROWS(E_WOULDBLOCK);
LOCAL ATTR_RETNONNULL WUNUSED REF struct task *KCALL task_getsessionleader_srch(void) THROWS(E_WOULDBLOCK, E_PROCESS_EXITED);
LOCAL ATTR_RETNONNULL WUNUSED REF struct taskpid *KCALL task_getsessionleaderpid(void) THROWS(E_WOULDBLOCK);
LOCAL WUNUSED NONNULL((1)) REF struct task *KCALL task_getsessionleader_of(struct task *__restrict thread) THROWS(E_WOULDBLOCK);
LOCAL ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct task *KCALL task_getsessionleader_srch_of(struct task *__restrict thread) THROWS(E_WOULDBLOCK, E_PROCESS_EXITED);
LOCAL ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct taskpid *KCALL task_getsessionleaderpid_of(struct task *__restrict thread) THROWS(E_WOULDBLOCK);
LOCAL WUNUSED REF struct task *NOTHROW(KCALL task_getsessionleader_nx)(void);
LOCAL WUNUSED REF struct taskpid *NOTHROW(KCALL task_getsessionleaderpid_nx)(void);
LOCAL WUNUSED NONNULL((1)) REF struct task *NOTHROW(KCALL task_getsessionleader_of_nx)(struct task *__restrict thread);
LOCAL WUNUSED NONNULL((1)) REF struct taskpid *NOTHROW(KCALL task_getsessionleaderpid_of_nx)(struct task *__restrict thread);

/* Returns true if the calling/given thread is a process leader (aka. process main thread) */
LOCAL ATTR_CONST WUNUSED bool NOTHROW(KCALL task_isprocessleader)(void);
LOCAL ATTR_CONST WUNUSED NONNULL((1)) bool NOTHROW(KCALL task_isprocessleader_p)(struct task const *__restrict thread);

/* Returns true if the calling/given thread is a process group leader */
LOCAL ATTR_PURE WUNUSED bool NOTHROW(KCALL task_isprocessgroupleader)(void);
LOCAL ATTR_PURE WUNUSED NONNULL((1)) bool NOTHROW(KCALL task_isprocessgroupleader_p)(struct task const *__restrict thread);

/* Returns true if the calling/given thread is a session group leader */
LOCAL ATTR_PURE WUNUSED bool NOTHROW(KCALL task_issessionleader)(void);
LOCAL ATTR_PURE WUNUSED NONNULL((1)) bool NOTHROW(KCALL task_issessionleader_p)(struct task const *__restrict thread);


/* Return the TID (thread id) /  PID (process id / thread  id
 * of the process leader) of the calling thread. The returned
 * IDS are either relative to  the task's own PID  namespace,
 * to the ROOT pid namespace, or the given namespace. */
#define task_gettid()       taskpid_getselftid(THIS_TASKPID)
#define task_getroottid()   taskpid_getroottid(THIS_TASKPID)
#define task_getnstid(ns)   taskpid_getnstid(THIS_TASKPID, ns)
#define task_getnstid_s(ns) taskpid_getnstid_s(THIS_TASKPID, ns)
#define task_getpid()       taskpid_gettid(task_getprocesspid())
#define task_getrootpid()   taskpid_getroottid(task_getprocesspid())
#define task_getnspid(ns)   taskpid_getnstid(task_getprocesspid(), ns)
#define task_getnspid_s(ns) taskpid_getnstid_s(task_getprocesspid(), ns)

/* Return TIDs/PIDs of the given thread. */
#define task_gettid_of(thread)         taskpid_gettid(FORTASK(thread, this_taskpid))
#define task_gettid_of_s(thread)       taskpid_gettid_s(FORTASK(thread, this_taskpid))
#define task_getnstid_of(thread, ns)   taskpid_getnstid(FORTASK(thread, this_taskpid), ns)
#define task_getnstid_of_s(thread, ns) taskpid_getnstid_s(FORTASK(thread, this_taskpid), ns)
#define task_getselftid_of(thread)     taskpid_getselftid(FORTASK(thread, this_taskpid))
#define task_getroottid_of(thread)     taskpid_getroottid(FORTASK(thread, this_taskpid))
#define task_getpid_of(thread)         taskpid_gettid(task_getprocesspid_of(thread))
#define task_getpid_of_s(thread)       taskpid_gettid_s(task_getprocesspid_of(thread))
#define task_getnspid_of(thread, ns)   taskpid_getnstid(task_getprocesspid_of(thread), ns)
#define task_getnspid_of_s(thread, ns) taskpid_getnstid_s(task_getprocesspid_of(thread), ns)
#define task_getselfpid_of(thread)     taskpid_getselftid(task_getprocesspid_of(thread))
#define task_getrootpid_of(thread)     taskpid_getroottid(task_getprocesspid_of(thread))




/* Set the group leader for the process of the given thread.
 * NOTE: If `leader' isn't a process leader, `task_getprocess_of(leader)' will be used instead.
 * @param: pold_group_leader: When non-NULL store a reference to the old process group leader of `task_getprocess_of(thread)'. (Only set on TASK_SETPROCESSGROUPLEADER_SUCCESS)
 * @param: pnew_group_leader: When non-NULL store a reference to the new process group leader of `task_getprocess_of(thread)'. (Only set on TASK_SETPROCESSGROUPLEADER_SUCCESS)
 * @return: * : One of `TASK_SETPROCESSGROUPLEADER_*' */
FUNDEF NONNULL((1, 2)) unsigned int KCALL
task_setprocessgroupleader(struct task *thread, struct task *leader,
                           /*OUT,OPT*/ REF struct taskpid **pold_group_leader DFL(__NULLPTR),
                           /*OUT,OPT*/ REF struct taskpid **pnew_group_leader DFL(__NULLPTR))
		THROWS(E_WOULDBLOCK);
#define TASK_SETPROCESSGROUPLEADER_SUCCESS 0 /* Successfully  added   `task_getprocess_of(thread)'  to   the  process   group
                                              * that `leader' is apart of (which is `task_getprocessgroupleader_of(leader)'),
                                              * or make `thread' become its own process group when
                                              * `task_getprocess_of(thread) == task_getprocess_of(leader)' */
#define TASK_SETPROCESSGROUPLEADER_LEADER  1 /*  The given `thread' is already the leader of its own process group.
                                              * -> Once promoted to a group leader, a process cannot back out and no longer be one! */
#define TASK_SETPROCESSGROUPLEADER_EXITED  2 /* The given `leader' has already terminated. */

/* Set the session leader for the process group of the given thread.
 * NOTE: If `task_getprocess_of(thread)' isn't already the leader of its own process group
 *      (`task_isprocessgroupleader_p(task_getprocess_of(thread))' is false), a call to
 *       this  function  also implies  `task_setprocessgroupleader(thread,thread)', meaning
 *       that `task_getprocess_of(thread)' is turned into its own process group before that
 *       group is added to the session of `leader', or made to become a new session
 * @param: pold_group_leader:   When non-NULL store a reference to the old process group leader of `task_getprocess_of(thread)'.
 *                              NOTE:  The  new  process  group  leader  of  `thread'  is  always  `task_getprocess_of(thread)',
 *                                    since only the leader of a process group can dictate the associated session.
 * @param: pold_session_leader: When non-NULL store a reference to the old session leader of `task_getprocess_of(thread)'.
 * @param: pnew_session_leader: When non-NULL store a reference to the new session leader of `task_getprocess_of(thread)'.
 * @return: * : One of `TASK_SETSESSIONLEADER_*' */
FUNDEF NONNULL((1, 2)) unsigned int KCALL
task_setsessionleader(struct task *thread, struct task *leader,
                      /*OUT,OPT*/ REF struct taskpid **pold_group_leader DFL(__NULLPTR),
                      /*OUT,OPT*/ REF struct taskpid **pold_session_leader DFL(__NULLPTR),
                      /*OUT,OPT*/ REF struct taskpid **pnew_session_leader DFL(__NULLPTR))
		THROWS(E_WOULDBLOCK);
#define TASK_SETSESSIONLEADER_SUCCESS 0 /* Successfully   added    `task_getprocess_of(thread)'    (which    at    that
                                         * point is guarantied to be identical to `task_getprocessgroupleader(thread)')
                                         * to the session that `leader' is apart of (which is
                                         * `task_getsessionleader_of(leader)'), or make `thread' become a new session when
                                         * `task_getprocessgroupleader(thread) == task_getprocessgroupleader(leader)' */
#define TASK_SETSESSIONLEADER_LEADER  1 /* The given `thread' is already the leader of a different session than `leader'.
                                         * -> Once promoted to a session leader, a process group cannot back out and no longer be one! */







/* Allocate a `struct taskpid' for `self' (which must not have  been
 * started yet, or have its taskpid already allocated), and register
 * that task within the given pidns `ns'
 * WARNING: This function may only be called _ONCE_ for each task!
 * @param: ns_pid: The  PID  to  try to  assign  to `self'  within  the namespace.
 *                 When ZERO(0),  or already  in  use, sequentially  generate  IDs
 *                 Also note  that  this PID  is  only  set for  `self'  in  `ns'.
 *                 All underlying namespaces _always_ have their PIDs sequentially
 *                 generated.
 * @return: * : Always re-returns `self' */
FUNDEF ATTR_RETNONNULL NONNULL((1, 2)) struct task *KCALL
task_setpid(struct task *__restrict self,
            struct pidns *__restrict ns,
            pid_t ns_pid DFL(0))
		THROWS(E_WOULDBLOCK, E_BADALLOC);



/* Initialize the `self' to be a member of the same process which `leader' is apart of.
 * NOTE: This function or `task_setprocess()' may only be called once for any given thread.
 *       Also  note  that  these  functions  must  _NOT_  be  called  for  kernel  threads!
 * NOTE: This function must be called _AFTER_ `task_setpid(self)' has already been invoked!
 * @return: true:  Successfully initialized `self' as a thread within the same process as `leader'
 * @return: false: The process that `leader' is apart of has already terminated. */
FUNDEF NONNULL((1, 2)) bool KCALL
task_setthread(struct task *__restrict self,
               struct task *__restrict leader)
		THROWS(E_WOULDBLOCK);

/* Initialize the `self' to be the leader of a new process, using `parent' as leader.
 * When   `parent'   is   `NULL',   initialize   `self'   as   a   detached  process.
 * @param: parent:  The parent of the process
 * @param: group:   A thread  apart  of  some process  group  that  `self' should  be  apart  of.
 *                  When `NULL' or equal to `self', initialize `self' as a its own process group.
 *                  In  this case, the process group will be  set to be apart of the session that
 *                  the given `session' is  apart of, or  `self' in case  `session' is `NULL'  or
 *                  equal to `self'.
 * @param: session: Some thread apart of the a session that a new process group should be made
 *                  apart of.
 * NOTE: This function or `task_setthread()' may only be called once for any given thread.
 *       Also note  that  these  functions  must  _NOT_  be  called  for  kernel  threads!
 * NOTE: This function must be called _AFTER_ `task_setpid(self)' has already been invoked! */
FUNDEF ATTR_RETNONNULL NONNULL((1)) struct task *KCALL
task_setprocess(struct task *__restrict self,
                struct task *parent DFL(__NULLPTR),
                struct task *group DFL(__NULLPTR),
                struct task *session DFL(__NULLPTR))
		THROWS(E_WOULDBLOCK);


#ifndef __INTELLISENSE__

/* Check if the given task was orphaned (no longer has a parent process) */
LOCAL ATTR_PURE WUNUSED bool
NOTHROW(KCALL task_isorphan)(void) {
	struct taskpid *proc = task_getprocesspid();
	return __hybrid_atomic_load(proc->tp_parsib.le_prev, __ATOMIC_ACQUIRE) == __NULLPTR;
}

LOCAL ATTR_PURE WUNUSED NONNULL((1)) bool
NOTHROW(KCALL task_isorphan_p)(struct task *__restrict thread) {
	struct taskpid *proc = task_getprocesspid_of(thread);
	return __hybrid_atomic_load(proc->tp_parsib.le_prev, __ATOMIC_ACQUIRE) == __NULLPTR;
}

LOCAL ATTR_PURE WUNUSED NONNULL((1)) bool
NOTHROW(KCALL taskpid_isorphan_p)(struct taskpid *__restrict self) {
	return __hybrid_atomic_load(self->tp_parsib.le_prev, __ATOMIC_ACQUIRE) == __NULLPTR;
}

LOCAL WUNUSED REF struct task *KCALL
task_getprocessparent(void) THROWS(E_WOULDBLOCK) {
	REF struct task *result;
	struct task *proc = task_getprocess();
	sync_read(&FORTASK(proc, this_taskgroup).tg_proc_parent_lock);
	result = FORTASK(proc, this_taskgroup).tg_proc_parent;
	if (result && !tryincref(result))
		result = __NULLPTR;
	sync_endread(&FORTASK(proc, this_taskgroup).tg_proc_parent_lock);
	return result;
}

LOCAL WUNUSED NONNULL((1)) REF struct task *KCALL
task_getprocessparent_of(struct task *__restrict thread) THROWS(E_WOULDBLOCK) {
	REF struct task *result;
	struct task *proc = task_getprocess_of(thread);
	sync_read(&FORTASK(proc, this_taskgroup).tg_proc_parent_lock);
	result = FORTASK(proc, this_taskgroup).tg_proc_parent;
	if (result && !tryincref(result))
		result = __NULLPTR;
	sync_endread(&FORTASK(proc, this_taskgroup).tg_proc_parent_lock);
	return result;
}

LOCAL WUNUSED REF struct task *
NOTHROW(KCALL task_getprocessparent_nx)(void) {
	REF struct task *result;
	struct task *proc = task_getprocess();
	if unlikely(!sync_read_nx(&FORTASK(proc, this_taskgroup).tg_proc_parent_lock))
		return __NULLPTR;
	result = FORTASK(proc, this_taskgroup).tg_proc_parent;
	if (result && !tryincref(result))
		result = __NULLPTR;
	sync_endread(&FORTASK(proc, this_taskgroup).tg_proc_parent_lock);
	return result;
}

LOCAL WUNUSED NONNULL((1)) REF struct task *
NOTHROW(KCALL task_getprocessparent_of_nx)(struct task *__restrict thread) {
	REF struct task *result;
	struct task *proc = task_getprocess_of(thread);
	if unlikely(!sync_read_nx(&FORTASK(proc, this_taskgroup).tg_proc_parent_lock))
		return __NULLPTR;
	result = FORTASK(proc, this_taskgroup).tg_proc_parent;
	if (result && !tryincref(result))
		result = __NULLPTR;
	sync_endread(&FORTASK(proc, this_taskgroup).tg_proc_parent_lock);
	return result;
}

LOCAL WUNUSED NONNULL((1)) struct task *
NOTHROW(KCALL task_getprocessparentptr_of)(struct task *__restrict thread) {
	struct task *proc = task_getprocess_of(thread);
	return __hybrid_atomic_load(FORTASK(proc, this_taskgroup).tg_proc_parent, __ATOMIC_ACQUIRE);
}

LOCAL WUNUSED REF struct taskpid *KCALL
task_getprocessparentpid(void) THROWS(E_WOULDBLOCK) {
	REF struct taskpid *result;
	REF struct task *result_thread;
	result_thread = task_getprocessparent();
	if unlikely(!result_thread)
		return __NULLPTR;
	result = incref(FORTASK(result_thread, this_taskpid));
	decref_unlikely(result_thread);
	return result;
}

LOCAL WUNUSED NONNULL((1)) REF struct taskpid *KCALL
task_getprocessparentpid_of(struct task *__restrict thread) THROWS(E_WOULDBLOCK) {
	REF struct taskpid *result;
	REF struct task *result_thread;
	result_thread = task_getprocessparent_of(thread);
	if unlikely(!result_thread)
		return __NULLPTR;
	result = incref(FORTASK(result_thread, this_taskpid));
	decref_unlikely(result_thread);
	return result;
}

LOCAL WUNUSED REF struct taskpid *
NOTHROW(KCALL task_getprocessparentpid_nx)(void) {
	REF struct taskpid *result;
	REF struct task *result_thread;
	result_thread = task_getprocessparent_nx();
	if unlikely(!result_thread)
		return __NULLPTR;
	result = incref(FORTASK(result_thread, this_taskpid));
	decref_unlikely(result_thread);
	return result;
}

LOCAL WUNUSED NONNULL((1)) REF struct taskpid *
NOTHROW(KCALL task_getprocessparentpid_of_nx)(struct task *__restrict thread) {
	REF struct taskpid *result;
	REF struct task *result_thread;
	result_thread = task_getprocessparent_of_nx(thread);
	if unlikely(!result_thread)
		return __NULLPTR;
	result = incref(FORTASK(result_thread, this_taskpid));
	decref_unlikely(result_thread);
	return result;
}




LOCAL ATTR_RETNONNULL WUNUSED REF struct taskpid *KCALL
task_getprocessgroupleaderpid(void) THROWS(E_WOULDBLOCK) {
	REF struct taskpid *result;
	struct task *proc = task_getprocess();
	sync_read(&FORTASK(proc, this_taskgroup).tg_proc_group_lock);
	result = incref(FORTASK(proc, this_taskgroup).tg_proc_group);
	sync_endread(&FORTASK(proc, this_taskgroup).tg_proc_group_lock);
	return result;
}

LOCAL ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct taskpid *KCALL
task_getprocessgroupleaderpid_of(struct task *__restrict thread) THROWS(E_WOULDBLOCK) {
	REF struct taskpid *result;
	struct task *proc = task_getprocess_of(thread);
	sync_read(&FORTASK(proc, this_taskgroup).tg_proc_group_lock);
	result = incref(FORTASK(proc, this_taskgroup).tg_proc_group);
	sync_endread(&FORTASK(proc, this_taskgroup).tg_proc_group_lock);
	return result;
}

LOCAL WUNUSED REF struct taskpid *
NOTHROW(KCALL task_getprocessgroupleaderpid_nx)(void) {
	REF struct taskpid *result;
	struct task *proc = task_getprocess();
	if unlikely(!sync_read_nx(&FORTASK(proc, this_taskgroup).tg_proc_group_lock))
		return __NULLPTR;
	result = incref(FORTASK(proc, this_taskgroup).tg_proc_group);
	sync_endread(&FORTASK(proc, this_taskgroup).tg_proc_group_lock);
	return result;
}

LOCAL WUNUSED NONNULL((1)) REF struct taskpid *
NOTHROW(KCALL task_getprocessgroupleaderpid_of_nx)(struct task *__restrict thread) {
	REF struct taskpid *result;
	struct task *proc = task_getprocess_of(thread);
	if unlikely(!sync_read_nx(&FORTASK(proc, this_taskgroup).tg_proc_group_lock))
		return __NULLPTR;
	result = incref(FORTASK(proc, this_taskgroup).tg_proc_group);
	sync_endread(&FORTASK(proc, this_taskgroup).tg_proc_group_lock);
	return result;
}

LOCAL WUNUSED REF struct task *KCALL
task_getprocessgroupleader(void) THROWS(E_WOULDBLOCK) {
	REF struct task *result;
	REF struct taskpid *tpid;
	tpid   = task_getprocessgroupleaderpid();
	result = taskpid_gettask(tpid);
	decref_unlikely(tpid);
	return result;
}

LOCAL ATTR_RETNONNULL WUNUSED REF struct task *KCALL
task_getprocessgroupleader_srch(void) THROWS(E_WOULDBLOCK, E_PROCESS_EXITED) {
	REF struct task *result;
	REF struct taskpid *tpid;
	tpid = task_getprocessgroupleaderpid();
	FINALLY_DECREF_UNLIKELY(tpid);
	result = taskpid_gettask_srch(tpid);
	return result;
}

LOCAL WUNUSED NONNULL((1)) REF struct task *KCALL
task_getprocessgroupleader_of(struct task *__restrict thread) THROWS(E_WOULDBLOCK) {
	REF struct task *result;
	REF struct taskpid *tpid;
	tpid   = task_getprocessgroupleaderpid_of(thread);
	result = taskpid_gettask(tpid);
	decref_unlikely(tpid);
	return result;
}

LOCAL ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct task *KCALL
task_getprocessgroupleader_srch_of(struct task *__restrict thread) THROWS(E_WOULDBLOCK, E_PROCESS_EXITED) {
	REF struct task *result;
	REF struct taskpid *tpid;
	tpid = task_getprocessgroupleaderpid_of(thread);
	FINALLY_DECREF_UNLIKELY(tpid);
	result = taskpid_gettask_srch(tpid);
	return result;
}

LOCAL WUNUSED REF struct task *
NOTHROW(KCALL task_getprocessgroupleader_nx)(void) {
	REF struct task *result;
	REF struct taskpid *tpid;
	tpid = task_getprocessgroupleaderpid_nx();
	if unlikely(!tpid)
		return __NULLPTR;
	result = taskpid_gettask(tpid);
	decref_unlikely(tpid);
	return result;
}

LOCAL WUNUSED NONNULL((1)) REF struct task *
NOTHROW(KCALL task_getprocessgroupleader_of_nx)(struct task *__restrict thread) {
	REF struct task *result;
	REF struct taskpid *tpid;
	tpid = task_getprocessgroupleaderpid_of_nx(thread);
	if unlikely(!tpid)
		return __NULLPTR;
	result = taskpid_gettask(tpid);
	decref_unlikely(tpid);
	return result;
}




LOCAL ATTR_RETNONNULL WUNUSED REF struct taskpid *KCALL
task_getsessionleaderpid(void) THROWS(E_WOULDBLOCK) {
	REF struct taskpid *result;
	REF struct task *grp;
	result = task_getprocessgroupleaderpid();
	grp    = taskpid_gettask(result);
	if likely(grp) {
		FINALLY_DECREF_UNLIKELY(grp);
		decref_unlikely(result);
		sync_read(&FORTASK(grp, this_taskgroup).tg_pgrp_session_lock);
		result = incref(FORTASK(grp, this_taskgroup).tg_pgrp_session);
		sync_endread(&FORTASK(grp, this_taskgroup).tg_pgrp_session_lock);
	}
	return result;
}

LOCAL ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct taskpid *KCALL
task_getsessionleaderpid_of(struct task *__restrict thread) THROWS(E_WOULDBLOCK) {
	REF struct taskpid *result;
	REF struct task *grp;
	result = task_getprocessgroupleaderpid_of(thread);
	grp    = taskpid_gettask(result);
	if likely(grp) {
		FINALLY_DECREF_UNLIKELY(grp);
		decref_unlikely(result);
		sync_read(&FORTASK(grp, this_taskgroup).tg_pgrp_session_lock);
		result = incref(FORTASK(grp, this_taskgroup).tg_pgrp_session);
		sync_endread(&FORTASK(grp, this_taskgroup).tg_pgrp_session_lock);
	}
	return result;
}

LOCAL WUNUSED REF struct taskpid *
NOTHROW(KCALL task_getsessionleaderpid_nx)(void) {
	REF struct taskpid *result;
	result = task_getprocessgroupleaderpid_nx();
	if likely(result) {
		REF struct task *grp;
		grp = taskpid_gettask(result);
		if likely(grp) {
			decref_unlikely(result);
			if unlikely(!sync_read_nx(&FORTASK(grp, this_taskgroup).tg_pgrp_session_lock)) {
				decref_unlikely(grp);
				return __NULLPTR;
			}
			result = incref(FORTASK(grp, this_taskgroup).tg_pgrp_session);
			sync_endread(&FORTASK(grp, this_taskgroup).tg_pgrp_session_lock);
			decref_unlikely(grp);
		}
	}
	return result;
}

LOCAL WUNUSED NONNULL((1)) REF struct taskpid *
NOTHROW(KCALL task_getsessionleaderpid_of_nx)(struct task *__restrict thread) {
	REF struct taskpid *result;
	result = task_getprocessgroupleaderpid_of_nx(thread);
	if likely(result) {
		REF struct task *grp;
		grp = taskpid_gettask(result);
		if likely(grp) {
			decref_unlikely(result);
			if unlikely(!sync_read_nx(&FORTASK(grp, this_taskgroup).tg_pgrp_session_lock)) {
				decref_unlikely(grp);
				return __NULLPTR;
			}
			result = incref(FORTASK(grp, this_taskgroup).tg_pgrp_session);
			sync_endread(&FORTASK(grp, this_taskgroup).tg_pgrp_session_lock);
			decref_unlikely(grp);
		}
	}
	return result;
}

LOCAL WUNUSED REF struct task *KCALL
task_getsessionleader(void) THROWS(E_WOULDBLOCK) {
	REF struct task *result;
	REF struct taskpid *tpid;
	tpid = task_getsessionleaderpid();
	result = taskpid_gettask(tpid);
	decref_unlikely(tpid);
	return result;
}

LOCAL WUNUSED REF struct task *KCALL
task_getsessionleader_srch(void) THROWS(E_WOULDBLOCK, E_PROCESS_EXITED) {
	REF struct task *result;
	REF struct taskpid *tpid;
	tpid = task_getsessionleaderpid();
	FINALLY_DECREF_UNLIKELY(tpid);
	result = taskpid_gettask_srch(tpid);
	return result;
}

LOCAL WUNUSED NONNULL((1)) REF struct task *KCALL
task_getsessionleader_of(struct task *__restrict thread) THROWS(E_WOULDBLOCK) {
	REF struct task *result;
	REF struct taskpid *tpid;
	tpid = task_getsessionleaderpid_of(thread);
	result = taskpid_gettask(tpid);
	decref_unlikely(tpid);
	return result;
}

LOCAL WUNUSED NONNULL((1)) REF struct task *KCALL
task_getsessionleader_srch_of(struct task *__restrict thread) THROWS(E_WOULDBLOCK, E_PROCESS_EXITED) {
	REF struct task *result;
	REF struct taskpid *tpid;
	tpid = task_getsessionleaderpid_of(thread);
	FINALLY_DECREF_UNLIKELY(tpid);
	result = taskpid_gettask_srch(tpid);
	return result;
}

LOCAL WUNUSED REF struct task *
NOTHROW(KCALL task_getsessionleader_nx)(void) {
	REF struct task *result;
	REF struct taskpid *tpid;
	tpid = task_getsessionleaderpid_nx();
	if unlikely(!tpid)
		return __NULLPTR;
	result = taskpid_gettask(tpid);
	decref_unlikely(tpid);
	return result;
}

LOCAL WUNUSED NONNULL((1)) REF struct task *
NOTHROW(KCALL task_getsessionleader_of_nx)(struct task *__restrict thread) {
	REF struct task *result;
	REF struct taskpid *tpid;
	tpid = task_getsessionleaderpid_of_nx(thread);
	if unlikely(!tpid)
		return __NULLPTR;
	result = taskpid_gettask(tpid);
	decref_unlikely(tpid);
	return result;
}





LOCAL ATTR_CONST WUNUSED bool
NOTHROW(KCALL task_isprocessleader)(void) {
	struct task *me = THIS_TASK;
	return FORTASK(me, this_taskgroup.tg_process) == me;
}

LOCAL ATTR_PURE WUNUSED NONNULL((1)) bool
NOTHROW(KCALL task_isprocessleader_p)(struct task const *__restrict thread) {
	return FORTASK(thread, this_taskgroup.tg_process) == thread;
}


LOCAL ATTR_PURE WUNUSED bool
NOTHROW(KCALL task_isprocessgroupleader)(void) {
	struct task *me = THIS_TASK;
	return FORTASK(me, this_taskgroup.tg_proc_group) == FORTASK(me, this_taskpid);
}

LOCAL ATTR_PURE WUNUSED NONNULL((1)) bool
NOTHROW(KCALL task_isprocessgroupleader_p)(struct task const *__restrict thread) {
	return __hybrid_atomic_load(FORTASK(thread, this_taskgroup.tg_proc_group), __ATOMIC_ACQUIRE) ==
	       FORTASK(thread, this_taskpid);
}

LOCAL ATTR_PURE WUNUSED bool
NOTHROW(KCALL task_issessionleader)(void) {
	struct task *me = THIS_TASK;
	struct taskpid *mypid = FORTASK(me, this_taskpid);
	return FORTASK(me, this_taskgroup.tg_proc_group) == mypid &&
	       FORTASK(me, this_taskgroup.tg_pgrp_session) == mypid;
}

LOCAL ATTR_PURE WUNUSED NONNULL((1)) bool
NOTHROW(KCALL task_issessionleader_p)(struct task const *__restrict thread) {
	return task_isprocessgroupleader_p(thread) &&
	       __hybrid_atomic_load(FORTASK(thread, this_taskgroup.tg_pgrp_session), __ATOMIC_ACQUIRE) ==
	       FORTASK(thread, this_taskpid);
}
#endif /* !__INTELLISENSE__ */

#endif /* __CC__ */

DECL_END
#endif /* !CONFIG_USE_NEW_GROUP */

#ifdef GUARD_KERNEL_INCLUDE_DEV_TTY_H
#ifndef GUARD_KERNEL_INCLUDE_SCHED_GROUP_CTTY_H
#include <sched/group-ctty.h>
#endif /* !GUARD_KERNEL_INCLUDE_SCHED_GROUP_CTTY_H */
#endif /* GUARD_KERNEL_INCLUDE_DEV_TTY_H */

#endif /* !GUARD_KERNEL_INCLUDE_SCHED_GROUP_H */
