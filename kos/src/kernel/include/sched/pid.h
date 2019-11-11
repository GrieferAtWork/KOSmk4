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
#ifndef GUARD_KERNEL_INCLUDE_SCHED_PID_H
#define GUARD_KERNEL_INCLUDE_SCHED_PID_H 1

#include <kernel/compiler.h>

#include <kernel/types.h>
#include <misc/atomic-ref.h>
#include <sched/pertask.h>
#include <sched/signal.h>

#include <hybrid/sequence/list.h>
#include <hybrid/sync/atomic-rwlock.h>

#include <bits/waitstatus.h>

#ifndef __INTELLISENSE__
#include <sched/task.h>

#include <hybrid/__assert.h>
#include <hybrid/__atomic.h>
#endif

DECL_BEGIN

#ifdef __CC__
struct task;
struct pidns;

struct taskpid {
	/* The `struct taskpid' acts as a sort-of weak
	 * reference to a task, using a binding:
	 *
	 *  <struct TASK>                   <struct taskpid>
	 *   THIS_TASKPID[1..1]  <------>   tp_thread[0..1]
	 *   - Reference                    - Weak reference
	 *                                  - Cleared when the task gets destroyed.
	 *                                    WARNING: May point to a `wasdestroyed()' task! */
	WEAK refcnt_t                  tp_refcnt;     /* Reference counter. */
	XATOMIC_WEAKLYREF(struct task) tp_thread;     /* [0..1] The pointed-to task */
	union wait                     tp_status;     /* [const_if(!tp_thread || wasdestroyed(tp_thread) || tp_thread->t_flags & TASK_FTERMINATING)]
	                                               * Current thread status / thread exit status. */
	struct sig                     tp_changed;    /* Signal broadcast when the thread changes state (WSTOPPED, WCONTINUED, WEXITED) */
	LLIST_NODE(REF struct taskpid) tp_siblings;   /* [0..1][valid_if(tp_thread && !wasdestroyed(tp_thread))]
	                                               * Chain of sibling tasks:
	                                               *  - If `tp_thread' is a process-leader:
	                                               *    - Chain of sibling processes spawned by the parent process of `tp_thread'
	                                               *  - If `tp_thread' isn't a process-leader (but instead a secondary thread):
	                                               *    - Chain of sibling threads spawned within the same process
	                                               *  - In either case, the link may be unbound if `detach()' was called. */
	REF struct pidns              *tp_pidns;      /* [1..1][const] The associated PID namespace. */
	upid_t                         tp_pids[1024]; /* [const][tp_pidns->pn_indirection + 1] This task's PIDs within all
	                                               * of the different PID namespaces that were used to bring it forth.
	                                               * Usually, this is only 1 (the root PID namespace), which is also the
	                                               * one who's PID appears in system logs. */
};

FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(KCALL taskpid_destroy)(struct taskpid *__restrict self);
DEFINE_REFCOUNT_FUNCTIONS(struct taskpid, tp_refcnt, taskpid_destroy)

/* Return a reference to the task associated with the given PID.
 * If that task has already terminated and has already been destroyed, return `NULL' instead. */
#ifdef __INTELLISENSE__
FORCELOCAL WUNUSED REF struct task *
NOTHROW(KCALL taskpid_gettask)(struct taskpid *__restrict self);
#else
#define taskpid_gettask(self) (self)->tp_thread.get()
#endif

/* Return the PID of `self' within the given PID namespace. */
FORCELOCAL NOBLOCK WUNUSED upid_t NOTHROW(KCALL taskpid_getpid)(struct taskpid *__restrict self, struct pidns *__restrict ns);
FORCELOCAL NOBLOCK WUNUSED upid_t NOTHROW(KCALL taskpid_getpid_s)(struct taskpid *__restrict self, struct pidns *__restrict ns);

/* Return the PID of `self' within the root PID namespace. */
FORCELOCAL NOBLOCK WUNUSED upid_t
NOTHROW(KCALL taskpid_getrootpid)(struct taskpid *__restrict self);

/* [1..1][valid_if(!TASK_FKERNTHREAD)][const] The PID associated with the calling thread.
 * NOTE: `NULL' (though assume UNDEFINED if the choice comes up) for kernel threads. */
DATDEF ATTR_PERTASK struct taskpid *_this_taskpid;
#define THIS_TASKPID    PERTASK_GET(_this_taskpid)
#define THIS_PIDNS     (PERTASK_GET(_this_taskpid)->tp_pidns)


/* For `posix-signal' */
struct sigqueue_entry;
struct sigqueue {
	/* Descriptor for pending signals (always per-thread or per-process).
	 * NOTE: Locking of this also depends on the context, where per-process
	 *       locking uses an atomic r/w-lock, while per-thread locking uses
	 *       atomic append operations. */
	struct sig             sq_newsig; /* Signal used to broadcast addition of new signals. */
	struct sigqueue_entry *sq_queue;  /* [0..1][owned][lock(sq_lock)] List of queued signals.
	                                   * Set to `SIGQUEUE_SQ_QUEUE_TERMINATED' when the
	                                   * thread/process has terminated. */
#define SIGQUEUE_SQ_QUEUE_TERMINATED ((struct sigqueue_entry *)-1)
};

struct process_sigqueue {
	struct atomic_rwlock psq_lock;  /* Lock for `psq_queue'. */
	struct sigqueue      psq_queue; /* The underlying queue. */
};
__DEFINE_SYNC_PROXY(struct process_sigqueue, psq_lock)

FUNDEF NOBLOCK void NOTHROW(KCALL sigqueue_fini)(struct sigqueue *__restrict self);

/* [valid_if(!TASK_FKERNTHREAD)]
 * [lock(LINKED_LIST(APPEND(ATOMIC),CLEAR(THIS_TASK)))]
 * Pending signals for the calling thread. */
DATDEF ATTR_PERTASK struct sigqueue _this_sigqueue;
#define THIS_SIGQUEUE       PERTASK(_this_sigqueue)

/* [valid_if(!TASK_FKERNTHREAD)]
 * Pending signals for the calling process. */
#define THIS_PROCESS_SIGQUEUE FORTASK(task_getprocess(), _this_taskgroup.tg_proc_signals)

struct ttybase_device;
struct taskgroup {
	/* Controller structure for tracing task association within/between
	 * processes, process groups, as well as sessions. */
	REF struct task             *tg_process;             /* [1..1][ref_if(!= THIS_TASK)][const]
	                                                      * Process leader (the main-thread of the associated process).
	                                                      * When this thread terminates, all other threads within the process also die.
	                                                      * @assume(tg_process == FORTASK(tg_process,_this_taskgroup).tg_process)
	                                                      * NOTE:
	                                                      *   - When set to `THIS_TASK', the calling thread is a process leader,
	                                                      *     also meaning that the `tp_siblings' chain within its PID structure
	                                                      *     is set up to form a chain of all other sibling processes within the
	                                                      *     same process group.
	                                                      *   - When set to something different, the calling thread is a worker
	                                                      *     thread, meaning that the `tp_siblings' chain within its PID structure
	                                                      *     is apart of a chain of other worker threads.
	                                                      *   - Any kernel thread is always its own process. */
	/* All of the following fields are only valid when `tg_process == THIS_TASK' (Otherwise, they are all `[0..1][const]') */
	struct atomic_rwlock         tg_proc_threads_lock;   /* Lock for `tg_proc_threads' */
#define TASKGROUP_TG_PROC_THREADS_TERMINATED ((REF struct taskpid *)-1)
	LLIST(REF struct taskpid)    tg_proc_threads;        /* [0..1][lock(tg_proc_threads_lock)]
	                                                      * Chain of threads & child processes of this process (excluding the calling (aka. leader) thread)
	                                                      * Tasks are removed from this chain, either by being `detach(2)'ed, or by being `wait(2)'ed on.
	                                                      * NOTE: This chain is set to `TASKGROUP_TG_PROC_THREADS_TERMINATED' once the associated
	                                                      *       process terminates, in order to prevent any new threads from being added. */
	struct sig                   tg_proc_threads_change; /* Broadcast when one of the threads (or child processes) of this process changes state.
	                                                      * For this purpose, the changed child has previously set its `tp_status' field to describe
	                                                      * its new state.
	                                                      * Also: Broadcasts are performed through `sig_altbroadcast()', with the sender set to the
	                                                      *      `struct taskpid *' of the child which has changed state. */
	struct atomic_rwlock         tg_proc_parent_lock;    /* Lock for `tg_proc_parent' */
	WEAK struct task            *tg_proc_parent;         /* [0..1][const] The parent of this process.
	                                                      * @assume(tg_proc_parent == FORTASK(tg_proc_parent,_this_taskgroup).tg_process)
	                                                      * In the event that this process has a parent, `THIS_TASKPID->tp_siblings'
	                                                      * is a link within `tg_proc_parent->tp_thread->tg_proc_threads'.
	                                                      * In the event that the parent process terminates before its child, this field
	                                                      * gets set to `NULL', at which point `THIS_TASKPID->tp_siblings' is unbound. */
	struct atomic_rwlock         tg_proc_group_lock;     /* Lock for `tg_proc_group' */
	REF struct task             *tg_proc_group;          /* [1..1][ref_if(!= THIS_TASK)][lock(tg_proc_group_lock)]
	                                                      * @assume(tg_proc_procgroup == FORTASK(tg_proc_procgroup,_this_taskgroup).tg_proc_procgroup)
	                                                      * The leader of the associated process group.
	                                                      * When set to `THIS_TASK', then the calling thread is a process group leader. */
	LLIST_NODE(WEAK struct task) tg_proc_group_siblings; /* [0..1][lock(tg_proc_group->tg_pgrp_processes_lock)]
	                                                      * [valid_if(THIS_TASK != tg_proc_group)]
	                                                      * Chain of sibling processes within the same process group.
	                                                      * The base of this chain is `tg_proc_group->tg_pgrp_processes' */
	struct process_sigqueue      tg_proc_signals;        /* Pending signals that are being delivered to this process. */
	/* All of the following fields are only valid when `tg_proc_group == THIS_TASK' (Otherwise, they are all `[0..1][const]') */
	struct atomic_rwlock         tg_pgrp_processes_lock; /* Lock for `tg_pgrp_processes' */
	LLIST(WEAK struct task)      tg_pgrp_processes;      /* [0..1] Chain of processes within this process group (excluding the calling process)
	                                                      * NOTE: This list of processes is chained using the `tg_proc_group_siblings' list node.
	                                                      * NOTE: This chain is set to `TASKGROUP_TG_PGRP_PROCESSES_TERMINATED' to prevent any
	                                                      *       new processes from being added to the process group. */
	struct atomic_rwlock         tg_pgrp_session_lock;   /* Lock for `tg_pgrp_session' */
	REF struct task             *tg_pgrp_session;        /* [1..1][ref_if(!= THIS_TASK)][const_if(== THIS_TASK)][lock(tg_pgrp_session_lock)]
	                                                      * @assume(tg_pgrp_session == FORTASK(tg_pgrp_session,_this_taskgroup).tg_pgrp_session)
	                                                      * The session leader of the this process group.
	                                                      * When set to `THIS_TASK', then the calling thread is that leader. */
	/* All of the following fields are only valid when `tg_pgrp_session == THIS_TASK' (Otherwise, they are all `[0..1][const]') */
	XATOMIC_REF_STRUCT(struct ttybase_device) tg_ctty;   /* [0..1] The controlling terminal (/dev/tty) associated with this session
	                                                      * When non-NULL, `tg_ctty->t_cproc == THIS_TASKPID' (for the session leader) */
};


DATDEF ATTR_PERTASK struct taskgroup _this_taskgroup;
#define THIS_TASKGROUP       PERTASK(_this_taskgroup)

#ifdef __INTELLISENSE__
/* Returns a pointer to the process associated with the calling/given thread.
 * NOTE: These functions return `NULL' for kernel-space thread! */
FORCELOCAL WUNUSED /*ATTR_RETNONNULL*/ ATTR_CONST struct task *KCALL task_getprocess(void);
FORCELOCAL WUNUSED /*ATTR_RETNONNULL*/ ATTR_CONST struct taskpid *KCALL task_getprocesspid(void);
FORCELOCAL WUNUSED /*ATTR_RETNONNULL*/ ATTR_CONST NONNULL((1)) struct task *KCALL task_getprocess_of(struct task *__restrict thread);
FORCELOCAL WUNUSED /*ATTR_RETNONNULL*/ ATTR_CONST NONNULL((1)) struct taskpid *KCALL task_getprocesspid_of(struct task *__restrict thread);
#else
#define task_getprocess()              ((struct task *)PERTASK_GET(_this_taskgroup.tg_process))
#define task_getprocesspid()             FORTASK(task_getprocess(), _this_taskpid)
#define task_getprocess_of(thread)     ((struct task *)FORTASK(thread, _this_taskgroup).tg_process)
#define task_getprocesspid_of(thread)    FORTASK(task_getprocess_of(thread), _this_taskpid)
#endif

/* Returns a reference to the parent of the calling/given process.
 * If that parent has already terminated and has already been detach'ed,
 * or wait-ed, return `NULL' instead. */
FORCELOCAL WUNUSED REF struct task *KCALL task_getprocessparent(void) THROWS(E_WOULDBLOCK);
FORCELOCAL WUNUSED REF struct taskpid *KCALL task_getprocessparentpid(void) THROWS(E_WOULDBLOCK);
FORCELOCAL WUNUSED NONNULL((1)) REF struct task *KCALL task_getprocessparent_of(struct task *__restrict thread) THROWS(E_WOULDBLOCK);
FORCELOCAL WUNUSED NONNULL((1)) REF struct taskpid *KCALL task_getprocessparentpid_of(struct task *__restrict thread) THROWS(E_WOULDBLOCK);
FORCELOCAL WUNUSED REF struct task *NOTHROW(KCALL task_getprocessparent_nx)(void);
FORCELOCAL WUNUSED REF struct taskpid *NOTHROW(KCALL task_getprocessparentpid_nx)(void);
FORCELOCAL WUNUSED NONNULL((1)) REF struct task *NOTHROW(KCALL task_getprocessparent_of_nx)(struct task *__restrict thread);
FORCELOCAL WUNUSED NONNULL((1)) REF struct taskpid *NOTHROW(KCALL task_getprocessparentpid_of_nx)(struct task *__restrict thread);

/* Detach the given `thread' from its parent
 * @return: true:  Successfully detached the given `thread'.
 * @return: false: The given `thread' had already been detached. */
FUNDEF bool KCALL task_detach(struct task *__restrict thread) THROWS(E_WOULDBLOCK);

/* Detach all child threads/processes of the given `process'
 * @assume(process == task_getprocess_of(process));
 * @return: * : The number of detached children. */
FUNDEF size_t KCALL task_detach_children(struct task *__restrict process) THROWS(E_WOULDBLOCK);


/* Return a reference to the leader of the process group of the calling/given thread. */
FORCELOCAL WUNUSED ATTR_RETNONNULL REF struct task *KCALL task_getprocessgroupleader(void) THROWS(E_WOULDBLOCK);
FORCELOCAL WUNUSED ATTR_RETNONNULL REF struct taskpid *KCALL task_getprocessgroupleaderpid(void) THROWS(E_WOULDBLOCK);
FORCELOCAL WUNUSED ATTR_RETNONNULL NONNULL((1)) REF struct task *KCALL task_getprocessgroupleader_of(struct task *__restrict thread) THROWS(E_WOULDBLOCK);
FORCELOCAL WUNUSED ATTR_RETNONNULL NONNULL((1)) REF struct taskpid *KCALL task_getprocessgroupleaderpid_of(struct task *__restrict thread) THROWS(E_WOULDBLOCK);
FORCELOCAL WUNUSED REF struct task *NOTHROW(KCALL task_getprocessgroupleader_nx)(void);
FORCELOCAL WUNUSED REF struct taskpid *NOTHROW(KCALL task_getprocessgroupleaderpid_nx)(void);
FORCELOCAL WUNUSED NONNULL((1)) REF struct task *NOTHROW(KCALL task_getprocessgroupleader_of_nx)(struct task *__restrict thread);
FORCELOCAL WUNUSED NONNULL((1)) REF struct taskpid *NOTHROW(KCALL task_getprocessgroupleaderpid_of_nx)(struct task *__restrict thread);

/* Return a reference to the session leader of the process group of the calling/given thread. */
FORCELOCAL WUNUSED ATTR_RETNONNULL REF struct task *KCALL task_getsessionleader(void) THROWS(E_WOULDBLOCK);
FORCELOCAL WUNUSED ATTR_RETNONNULL REF struct taskpid *KCALL task_getsessionleaderpid(void) THROWS(E_WOULDBLOCK);
FORCELOCAL WUNUSED ATTR_RETNONNULL NONNULL((1)) REF struct task *KCALL task_getsessionleader_of(struct task *__restrict thread) THROWS(E_WOULDBLOCK);
FORCELOCAL WUNUSED ATTR_RETNONNULL NONNULL((1)) REF struct taskpid *KCALL task_getsessionleaderpid_of(struct task *__restrict thread) THROWS(E_WOULDBLOCK);
FORCELOCAL WUNUSED REF struct task *NOTHROW(KCALL task_getsessionleader_nx)(void);
FORCELOCAL WUNUSED REF struct taskpid *NOTHROW(KCALL task_getsessionleaderpid_nx)(void);
FORCELOCAL WUNUSED NONNULL((1)) REF struct task *NOTHROW(KCALL task_getsessionleader_of_nx)(struct task *__restrict thread);
FORCELOCAL WUNUSED NONNULL((1)) REF struct taskpid *NOTHROW(KCALL task_getsessionleaderpid_of_nx)(struct task *__restrict thread);

/* Returns true if the calling/given thread is a process leader (aka. process main thread) */
FORCELOCAL WUNUSED ATTR_CONST bool NOTHROW(KCALL task_isprocessleader)(void);
FORCELOCAL WUNUSED ATTR_CONST NONNULL((1)) bool NOTHROW(KCALL task_isprocessleader_p)(struct task *__restrict thread);

/* Returns true if the calling/given thread is a process group leader */
FORCELOCAL WUNUSED bool NOTHROW(KCALL task_isprocessgroupleader)(void);
FORCELOCAL WUNUSED NONNULL((1)) bool NOTHROW(KCALL task_isprocessgroupleader_p)(struct task *__restrict thread);

/* Returns true if the calling/given thread is a session group leader */
FORCELOCAL WUNUSED bool NOTHROW(KCALL task_issessionleader)(void);
FORCELOCAL WUNUSED NONNULL((1)) bool NOTHROW(KCALL task_issessionleader_p)(struct task *__restrict thread);


/* Return the TID (thread id) / PID (process id /
 * thread id of the process leader) of the calling thread
 * The returned IDS are either relative to the task's own
 * PID namespace, or to the ROOT pid namespace.
 * NOTE: The `*_S' variants can also be used by kernel threads, where they evaluate to `0' */
FORCELOCAL NOBLOCK WUNUSED upid_t NOTHROW(KCALL task_gettid)(void);
FORCELOCAL NOBLOCK WUNUSED upid_t NOTHROW(KCALL task_gettid_s)(void);
FORCELOCAL NOBLOCK WUNUSED upid_t NOTHROW(KCALL task_getroottid)(void);
FORCELOCAL NOBLOCK WUNUSED upid_t NOTHROW(KCALL task_getroottid_s)(void);
FORCELOCAL NOBLOCK WUNUSED upid_t NOTHROW(KCALL task_getpid)(void);
FORCELOCAL NOBLOCK WUNUSED upid_t NOTHROW(KCALL task_getpid_s)(void);
FORCELOCAL NOBLOCK WUNUSED upid_t NOTHROW(KCALL task_getrootpid)(void);
FORCELOCAL NOBLOCK WUNUSED upid_t NOTHROW(KCALL task_getrootpid_s)(void);

/* Same as the functions above, but return the values for a given thread, rather than the calling.
 * NOTE: The non-root variants of these functions will still return the thread's proper IDs in
 *       the context of the calling thread's PID namespace
 * With that in mind, the non-*_s variants will cause kernel panic/undefined behavior for any
 * for the following situations:
 * task_gettid_of:
 *   - FORTASK(thread,_this_taskpid) == NULL                                  (`thread' is a kernel thread)
 *   - THIS_TASKPID == NULL                                                   (The caller is a kernel thread)
 * task_getroottid_of:
 *   - FORTASK(thread,_this_taskpid) == NULL                                  (`thread' is a kernel thread)
 * task_getpid_of:
 *   - FORTASK(thread,_this_group.tg_process) == NULL                         (`thread' is a kernel thread)
 *   - FORTASK(FORTASK(thread,_this_group.tg_process),_this_taskpid) == NULL  (The process leader of `thread' is a kernel thread)
 *   - THIS_TASKPID == NULL                                                   (The caller is a kernel thread)
 * task_getrootpid_of:
 *   - FORTASK(thread,_this_group.tg_process) == NULL                         (`thread' is a kernel thread)
 *   - FORTASK(FORTASK(thread,_this_group.tg_process),_this_taskpid) == NULL  (The process leader of `thread' is a kernel thread)
 */
FORCELOCAL NOBLOCK WUNUSED NONNULL((1)) upid_t NOTHROW(KCALL task_gettid_of)(struct task *__restrict thread);
FORCELOCAL NOBLOCK WUNUSED NONNULL((1)) upid_t NOTHROW(KCALL task_gettid_of_s)(struct task *__restrict thread);
FORCELOCAL NOBLOCK WUNUSED NONNULL((1)) upid_t NOTHROW(KCALL task_getroottid_of)(struct task *__restrict thread);
FORCELOCAL NOBLOCK WUNUSED NONNULL((1)) upid_t NOTHROW(KCALL task_getroottid_of_s)(struct task *__restrict thread);
FORCELOCAL NOBLOCK WUNUSED NONNULL((1)) upid_t NOTHROW(KCALL task_getpid_of)(struct task *__restrict thread);
FORCELOCAL NOBLOCK WUNUSED NONNULL((1)) upid_t NOTHROW(KCALL task_getpid_of_s)(struct task *__restrict thread);
FORCELOCAL NOBLOCK WUNUSED NONNULL((1)) upid_t NOTHROW(KCALL task_getrootpid_of)(struct task *__restrict thread);
FORCELOCAL NOBLOCK WUNUSED NONNULL((1)) upid_t NOTHROW(KCALL task_getrootpid_of_s)(struct task *__restrict thread);




/* Set the group leader for the process of the given thread.
 * NOTE: If `leader' isn't a process leader, `task_getprocess_of(leader)' will be used instead.
 * @param: pold_group_leader: When non-NULL store a reference to the old process group leader of `task_getprocess_of(thread)'. (Only set on TASK_SETPROCESSGROUPLEADER_SUCCESS)
 * @param: pnew_group_leader: When non-NULL store a reference to the new process group leader of `task_getprocess_of(thread)'. (Only set on TASK_SETPROCESSGROUPLEADER_SUCCESS)
 * @return: * : One of `TASK_SETPROCESSGROUPLEADER_*' */
FUNDEF NONNULL((1, 2)) unsigned int KCALL
task_setprocessgroupleader(struct task *thread, struct task *leader,
                           /*OUT,OPT*/ REF struct task **pold_group_leader DFL(__NULLPTR),
                           /*OUT,OPT*/ REF struct task **pnew_group_leader DFL(__NULLPTR))
		THROWS(E_WOULDBLOCK);
#define TASK_SETPROCESSGROUPLEADER_SUCCESS 0 /* Successfully added `task_getprocess_of(thread)' to the process group
                                              * that `leader' is apart of (which is `task_getprocessgroupleader_of(leader)'),
                                              * or make `thread' become its own process group when
                                              * `task_getprocess_of(thread) == task_getprocess_of(leader)' */
#define TASK_SETPROCESSGROUPLEADER_LEADER  1 /*  The given `thread' is already the leader of its own process group.
                                              * -> Once promoted to a group leader, a process cannot back out and no longer be one! */
#define TASK_SETPROCESSGROUPLEADER_EXITED  2 /* The given `leader' has already terminated. */

/* Set the session leader for the process group of the given thread.
 * NOTE: If `task_getprocess_of(thread)' isn't already the leader of its own process group
 *      (`task_isprocessgroupleader_p(task_getprocess_of(thread))' is false), a call to
 *       this function also implies `task_setprocessgroupleader(thread,thread)', meaning
 *       that `task_getprocess_of(thread)' is turned into its own process group before that
 *       group is added to the session of `leader', or made to become a new session
 * @param: pold_group_leader:   When non-NULL store a reference to the old process group leader of `task_getprocess_of(thread)'.
 *                              NOTE: The new process group leader of `thread' is always `task_getprocess_of(thread)',
 *                                    since only the leader of a process group can dictate the associated session.
 * @param: pold_session_leader: When non-NULL store a reference to the old session leader of `task_getprocess_of(thread)'.
 * @param: pnew_session_leader: When non-NULL store a reference to the new session leader of `task_getprocess_of(thread)'.
 * @return: * : One of `TASK_SETSESSIONLEADER_*' */
FUNDEF NONNULL((1, 2)) unsigned int KCALL
task_setsessionleader(struct task *thread, struct task *leader,
                      /*OUT,OPT*/ REF struct task **pold_group_leader DFL(__NULLPTR),
                      /*OUT,OPT*/ REF struct task **pold_session_leader DFL(__NULLPTR),
                      /*OUT,OPT*/ REF struct task **pnew_session_leader DFL(__NULLPTR))
		THROWS(E_WOULDBLOCK);
#define TASK_SETSESSIONLEADER_SUCCESS 0 /* Successfully added `task_getprocess_of(thread)' (which at that
                                         * point is guarantied to be identical to `task_getprocessgroupleader(thread)')
                                         * to the session that `leader' is apart of (which is
                                         * `task_getsessionleader_of(leader)'), or make `thread' become a new session when
                                         * `task_getprocessgroupleader(thread) == task_getprocessgroupleader(leader)' */
#define TASK_SETSESSIONLEADER_LEADER  1 /* The given `thread' is already the leader of a different session than `leader'.
                                         * -> Once promoted to a session leader, a process group cannot back out and no longer be one!  */











struct pidns_entry {
	WEAK struct taskpid *pe_pid; /* [0..1] PID entry (Set to `PIDNS_ENTRY_DELETED' for deleted entries). */
#define PIDNS_ENTRY_DELETED ((WEAK struct taskpid *)-1)
};

struct pidns {
	WEAK refcnt_t        pn_refcnt;      /* Reference counter. */
	size_t               pn_indirection; /* [const] Namespace indirection of this PID NS.
	                                      * This also describes the number of PIDs that a
	                                      * thread that is added to this namespace will
	                                      * gain (+1), from this namespace and all namespaces
	                                      * that are reachable from `pn_parent'. */
	REF struct pidns    *pn_parent;      /* [0..1][const]
	                                      * [->pn_indirection == pn_indirection-1]
	                                      * [(!= NULL) == (pn_indirection != 0)]
	                                      * [(== NULL) == (self == &pidns_root)]
	                                      * The parenting PID namespace with one less indirection. */
	struct atomic_rwlock pn_lock;        /* Lock for accessing the hash-vector below. */
	size_t               pn_used;        /* [lock(pn_lock)] Amount of used (non-NULL and non-DUMMY) PIDs */
	size_t               pn_size;        /* [lock(pn_lock)] Amount of (non-NULL) PIDs entires. */
	size_t               pn_mask;        /* [lock(pn_lock)] Hash-mask for `pn_list' */
	struct pidns_entry  *pn_list;        /* [1..pn_mask+1][owned_if(!= INTERNAL(empty_pidns_list))]
	                                      * Hash-vector of PIDs. */
	WEAK struct taskpid *pn_dead;        /* [0..1] Chain of dead task PIDs that are pending removal.
	                                      * NOTE: Chained via `tp_siblings.ln_next' */
};

#define PIDNS_HASHNXT(i, perturb) \
	((i) = (((i) << 2) + (i) + (perturb) + 1), (perturb) >>= 5)


/* The root PID namespace. */
DATDEF struct pidns pidns_root;

/* Functions for acquiring the `pn_lock' for reading/writing. */
FUNDEF NOBLOCK WUNUSED NONNULL((1)) bool NOTHROW(KCALL pidns_tryread)(struct pidns *__restrict self);
FUNDEF NOBLOCK WUNUSED NONNULL((1)) bool NOTHROW(KCALL pidns_trywrite)(struct pidns *__restrict self);
FUNDEF NOBLOCK WUNUSED NONNULL((1)) bool NOTHROW(KCALL pidns_tryupgrade)(struct pidns *__restrict self);
FUNDEF NOBLOCK NONNULL((1)) void NOTHROW(KCALL pidns_end)(struct pidns *__restrict self);
FUNDEF NOBLOCK NONNULL((1)) void NOTHROW(KCALL pidns_endread)(struct pidns *__restrict self);
FUNDEF NOBLOCK NONNULL((1)) void NOTHROW(KCALL pidns_endwrite)(struct pidns *__restrict self);
FUNDEF NOBLOCK NONNULL((1)) void NOTHROW(KCALL pidns_downgrade)(struct pidns *__restrict self);
FUNDEF NOBLOCK NONNULL((1)) void NOTHROW(KCALL pidns_tryservice)(struct pidns *__restrict self);
FUNDEF NONNULL((1)) void (KCALL pidns_read)(struct pidns *__restrict self) THROWS(E_WOULDBLOCK);
FUNDEF NONNULL((1)) void (KCALL pidns_write)(struct pidns *__restrict self) THROWS(E_WOULDBLOCK);
FUNDEF NONNULL((1)) bool (KCALL pidns_upgrade)(struct pidns *__restrict self) THROWS(E_WOULDBLOCK);
FUNDEF NONNULL((1)) WUNUSED bool NOTHROW(KCALL pidns_read_nx)(struct pidns *__restrict self);
FUNDEF NONNULL((1)) WUNUSED bool NOTHROW(KCALL pidns_write_nx)(struct pidns *__restrict self);
FUNDEF NONNULL((1)) WUNUSED unsigned int NOTHROW(KCALL pidns_upgrade_nx)(struct pidns *__restrict self);
#define pidns_reading(self)  sync_reading(&(self)->pn_lock)
#define pidns_writing(self)  sync_writing(&(self)->pn_lock)
#define pidns_canread(self)  sync_canread(&(self)->pn_lock)
#define pidns_canwrite(self) sync_canwrite(&(self)->pn_lock)
__DEFINE_SYNC_RWLOCK(struct pidns,
                     pidns_tryread,
                     pidns_read,
                     pidns_read_nx,
                     pidns_endread,
                     pidns_reading,
                     pidns_canread,
                     pidns_trywrite,
                     pidns_write,
                     pidns_write_nx,
                     pidns_endwrite,
                     pidns_writing,
                     pidns_canwrite,
                     pidns_end,
                     pidns_tryupgrade,
                     pidns_upgrade,
                     pidns_upgrade_nx,
                     pidns_downgrade)



/* Destroy a previously allocated pidns. */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(KCALL pidns_destroy)(struct pidns *__restrict self);
DEFINE_REFCOUNT_FUNCTIONS(struct pidns,pn_refcnt,pidns_destroy)

/* Allocate a new child PID namespace for `parent' */
FUNDEF ATTR_RETNONNULL NONNULL((1)) REF struct pidns *
(KCALL pidns_alloc)(struct pidns *__restrict parent) THROWS(E_BADALLOC);

/* Lookup a given `pid' within the specified PID namespace. */
FUNDEF WUNUSED ATTR_RETNONNULL NONNULL((1)) REF struct taskpid *
(KCALL pidns_lookup)(struct pidns *__restrict self, upid_t pid)
		THROWS(E_WOULDBLOCK, E_PROCESS_EXITED);
FUNDEF WUNUSED ATTR_RETNONNULL NONNULL((1)) REF struct task *
(KCALL pidns_lookup_task)(struct pidns *__restrict self, upid_t pid)
		THROWS(E_WOULDBLOCK, E_PROCESS_EXITED);
FUNDEF WUNUSED NONNULL((1)) REF struct taskpid *
(KCALL pidns_trylookup)(struct pidns *__restrict self, upid_t pid)
		THROWS(E_WOULDBLOCK);
FUNDEF WUNUSED NONNULL((1)) REF struct task *
(KCALL pidns_trylookup_task)(struct pidns *__restrict self, upid_t pid)
		THROWS(E_WOULDBLOCK);
FUNDEF WUNUSED NONNULL((1)) REF struct taskpid *
NOTHROW(KCALL pidns_trylookup_locked)(struct pidns *__restrict self, upid_t pid);
FUNDEF WUNUSED NONNULL((1)) REF struct task *
NOTHROW(KCALL pidns_trylookup_task_locked)(struct pidns *__restrict self, upid_t pid);


/* Allocate a `struct taskpid' for `self' (which must not have been
 * started yet, or have its taskpid already allocated), and register
 * that task within the given pidns `ns'
 * This function should be called after `task_alloc()', but before `task_start()'
 * WARNING: This function may only be called _ONCE_ for each task!
 * @param: ns_pid: The PID to try to assign to `self' within the namespace.
 *                 When ZERO(0), or already in use, randomly generate IDs
 *                 Also note that this PID is only set for `self' in `ns'.
 *                 All underlying namespaces _always_ have their PIDs randomly
 *                 generated.
 * @return: * : Always re-returns `self' */
FUNDEF ATTR_RETNONNULL NONNULL((1, 2)) struct task *
(KCALL task_setpid)(struct task *__restrict self,
                    struct pidns *__restrict ns,
                    upid_t ns_pid DFL(0))
		THROWS(E_WOULDBLOCK, E_BADALLOC);



/* Initialize the `self' to be a member of the same process which `leader' is apart of.
 * NOTE: This function or `task_setprocess()' may only be called once for any given thread.
 *       Also note that these functions must _NOT_ be called for kernel threads!
 * NOTE: This function must be called _AFTER_ `task_setpid(self)' has already been invoked!
 * @return: true:  Successfully initialized `self' as a thread within the same process as `leader'
 * @return: false: The process that `leader' is apart of has already terminated. */
FUNDEF NONNULL((1, 2)) bool
(KCALL task_setthread)(struct task *__restrict self,
                       struct task *__restrict leader)
		THROWS(E_WOULDBLOCK);

/* Initialize the `self' to be the leader of a new process, using `parent' as leader.
 * When `parent' is `NULL', initialize `self' as a detached process.
 * @param: parent:  The parent of the process
 * @param: group:   A thread apart of some process group that `self' should be apart of.
 *                  When `NULL' or equal to `self', initialize `self' as a its own process group.
 *                  In this case, the process group will be set to be apart of the session that
 *                  the given `session' is apart of, or `self' in case `session' is `NULL' or
 *                  equal to `self'.
 * @param: session: Some thread apart of the a session that a new process group should be made
 *                  apart of.
 * NOTE: This function or `task_setthread()' may only be called once for any given thread.
 *       Also note that these functions must _NOT_ be called for kernel threads!
 * NOTE: This function must be called _AFTER_ `task_setpid(self)' has already been invoked! */
FUNDEF ATTR_RETNONNULL NONNULL((1)) struct task *
(KCALL task_setprocess)(struct task *__restrict self,
                        struct task *parent DFL(__NULLPTR),
                        struct task *group DFL(__NULLPTR),
                        struct task *session DFL(__NULLPTR))
		THROWS(E_WOULDBLOCK);










#ifdef __cplusplus
extern "C++" {
FORCELOCAL NOBLOCK WUNUSED upid_t
NOTHROW(KCALL taskpid_getpid)(struct taskpid *__restrict self) {
	return taskpid_getpid(self, THIS_PIDNS);
}
FORCELOCAL NOBLOCK WUNUSED upid_t
NOTHROW(KCALL taskpid_getpid_s)(struct taskpid *__restrict self) {
	return taskpid_getpid_s(self, THIS_PIDNS);
}
}
#endif


#ifndef __INTELLISENSE__

/* Return the PID of `self' within the given PID namespace. */
FORCELOCAL NOBLOCK WUNUSED upid_t
NOTHROW(KCALL taskpid_getpid)(struct taskpid *__restrict self,
                              struct pidns *__restrict ns) {
	__hybrid_assert(self->tp_pidns->pn_indirection >= ns->pn_indirection);
	return self->tp_pids[ns->pn_indirection];
}

FORCELOCAL NOBLOCK WUNUSED upid_t
NOTHROW(KCALL taskpid_getpid_s)(struct taskpid *__restrict self,
                                struct pidns *__restrict ns) {
	if likely(self->tp_pidns->pn_indirection >= ns->pn_indirection)
		return self->tp_pids[ns->pn_indirection];
	return 0;
}

/* Return the PID of `self' within the root PID namespace. */
FORCELOCAL NOBLOCK WUNUSED upid_t
NOTHROW(KCALL taskpid_getrootpid)(struct taskpid *__restrict self) {
	return self->tp_pids[0];
}

FORCELOCAL WUNUSED REF struct task *KCALL
task_getprocessparent(void) THROWS(E_WOULDBLOCK) {
	REF struct task *result;
	struct task *proc = task_getprocess();
	sync_read(&FORTASK(proc, _this_taskgroup).tg_proc_parent_lock);
	result = FORTASK(proc, _this_taskgroup).tg_proc_parent;
	if (result && !tryincref(result))
		result = NULL;
	sync_endread(&FORTASK(proc, _this_taskgroup).tg_proc_parent_lock);
	return result;
}

FORCELOCAL WUNUSED NONNULL((1)) REF struct task *KCALL
task_getprocessparent_of(struct task *__restrict thread) THROWS(E_WOULDBLOCK) {
	REF struct task *result;
	struct task *proc = task_getprocess_of(thread);
	sync_read(&FORTASK(proc, _this_taskgroup).tg_proc_parent_lock);
	result = FORTASK(proc, _this_taskgroup).tg_proc_parent;
	if (result && !tryincref(result))
		result = NULL;
	sync_endread(&FORTASK(proc, _this_taskgroup).tg_proc_parent_lock);
	return result;
}

FORCELOCAL WUNUSED REF struct task *
NOTHROW(KCALL task_getprocessparent_nx)(void) {
	REF struct task *result;
	struct task *proc = task_getprocess();
	if unlikely(!sync_read_nx(&FORTASK(proc, _this_taskgroup).tg_proc_parent_lock))
		return __NULLPTR;
	result = FORTASK(proc, _this_taskgroup).tg_proc_parent;
	if (result && !tryincref(result))
		result = NULL;
	sync_endread(&FORTASK(proc, _this_taskgroup).tg_proc_parent_lock);
	return result;
}

FORCELOCAL WUNUSED NONNULL((1)) REF struct task *
NOTHROW(KCALL task_getprocessparent_of_nx)(struct task *__restrict thread) {
	REF struct task *result;
	struct task *proc = task_getprocess_of(thread);
	if unlikely(!sync_read_nx(&FORTASK(proc, _this_taskgroup).tg_proc_parent_lock))
		return __NULLPTR;
	result = FORTASK(proc, _this_taskgroup).tg_proc_parent;
	if (result && !tryincref(result))
		result = NULL;
	sync_endread(&FORTASK(proc, _this_taskgroup).tg_proc_parent_lock);
	return result;
}

FORCELOCAL WUNUSED REF struct taskpid *KCALL
task_getprocessparentpid(void) THROWS(E_WOULDBLOCK) {
	REF struct taskpid *result;
	REF struct task *result_thread;
	result_thread = task_getprocessparent();
	if unlikely(!result_thread)
		return __NULLPTR;
	result = incref(FORTASK(result_thread, _this_taskpid));
	decref_unlikely(result_thread);
	return result;
}

FORCELOCAL WUNUSED NONNULL((1)) REF struct taskpid *KCALL
task_getprocessparentpid_of(struct task *__restrict thread) THROWS(E_WOULDBLOCK) {
	REF struct taskpid *result;
	REF struct task *result_thread;
	result_thread = task_getprocessparent_of(thread);
	if unlikely(!result_thread)
		return __NULLPTR;
	result = incref(FORTASK(result_thread, _this_taskpid));
	decref_unlikely(result_thread);
	return result;
}

FORCELOCAL WUNUSED REF struct taskpid *
NOTHROW(KCALL task_getprocessparentpid_nx)(void) {
	REF struct taskpid *result;
	REF struct task *result_thread;
	result_thread = task_getprocessparent_nx();
	if unlikely(!result_thread)
		return __NULLPTR;
	result = incref(FORTASK(result_thread, _this_taskpid));
	decref_unlikely(result_thread);
	return result;
}

FORCELOCAL WUNUSED NONNULL((1)) REF struct taskpid *
NOTHROW(KCALL task_getprocessparentpid_of_nx)(struct task *__restrict thread) {
	REF struct taskpid *result;
	REF struct task *result_thread;
	result_thread = task_getprocessparent_of_nx(thread);
	if unlikely(!result_thread)
		return __NULLPTR;
	result = incref(FORTASK(result_thread, _this_taskpid));
	decref_unlikely(result_thread);
	return result;
}


FORCELOCAL WUNUSED ATTR_RETNONNULL REF struct task *KCALL
task_getprocessgroupleader(void) THROWS(E_WOULDBLOCK) {
	REF struct task *result;
	struct task *proc = task_getprocess();
	sync_read(&FORTASK(proc, _this_taskgroup).tg_proc_group_lock);
	result = incref(FORTASK(proc, _this_taskgroup).tg_proc_group);
	sync_endread(&FORTASK(proc, _this_taskgroup).tg_proc_group_lock);
	return result;
}

FORCELOCAL WUNUSED ATTR_RETNONNULL NONNULL((1)) REF struct task *KCALL
task_getprocessgroupleader_of(struct task *__restrict thread) THROWS(E_WOULDBLOCK) {
	REF struct task *result;
	struct task *proc = task_getprocess_of(thread);
	sync_read(&FORTASK(proc, _this_taskgroup).tg_proc_group_lock);
	result = incref(FORTASK(proc, _this_taskgroup).tg_proc_group);
	sync_endread(&FORTASK(proc, _this_taskgroup).tg_proc_group_lock);
	return result;
}

FORCELOCAL WUNUSED REF struct task *
NOTHROW(KCALL task_getprocessgroupleader_nx)(void) {
	REF struct task *result;
	struct task *proc = task_getprocess();
	if unlikely(!sync_read_nx(&FORTASK(proc, _this_taskgroup).tg_proc_group_lock))
		return __NULLPTR;
	result = incref(FORTASK(proc, _this_taskgroup).tg_proc_group);
	sync_endread(&FORTASK(proc, _this_taskgroup).tg_proc_group_lock);
	return result;
}

FORCELOCAL WUNUSED NONNULL((1)) REF struct task *
NOTHROW(KCALL task_getprocessgroupleader_of_nx)(struct task *__restrict thread) {
	REF struct task *result;
	struct task *proc = task_getprocess_of(thread);
	if unlikely(!sync_read_nx(&FORTASK(proc, _this_taskgroup).tg_proc_group_lock))
		return __NULLPTR;
	result = incref(FORTASK(proc, _this_taskgroup).tg_proc_group);
	sync_endread(&FORTASK(proc, _this_taskgroup).tg_proc_group_lock);
	return result;
}

FORCELOCAL WUNUSED ATTR_RETNONNULL REF struct taskpid *KCALL
task_getprocessgroupleaderpid(void) THROWS(E_WOULDBLOCK) {
	REF struct taskpid *result;
	REF struct task *result_thread;
	result_thread = task_getprocessgroupleader();
	result = incref(FORTASK(result_thread, _this_taskpid));
	decref_unlikely(result_thread);
	return result;
}

FORCELOCAL WUNUSED ATTR_RETNONNULL NONNULL((1)) REF struct taskpid *KCALL
task_getprocessgroupleaderpid_of(struct task *__restrict thread) THROWS(E_WOULDBLOCK) {
	REF struct taskpid *result;
	REF struct task *result_thread;
	result_thread = task_getprocessgroupleader_of(thread);
	result = incref(FORTASK(result_thread, _this_taskpid));
	decref_unlikely(result_thread);
	return result;
}

FORCELOCAL WUNUSED REF struct taskpid *
NOTHROW(KCALL task_getprocessgroupleaderpid_nx)(void) {
	REF struct taskpid *result;
	REF struct task *result_thread;
	result_thread = task_getprocessgroupleader_nx();
	if unlikely(!result_thread)
		return __NULLPTR;
	result = incref(FORTASK(result_thread, _this_taskpid));
	decref_unlikely(result_thread);
	return result;
}

FORCELOCAL WUNUSED NONNULL((1)) REF struct taskpid *
NOTHROW(KCALL task_getprocessgroupleaderpid_of_nx)(struct task *__restrict thread) {
	REF struct taskpid *result;
	REF struct task *result_thread;
	result_thread = task_getprocessgroupleader_of_nx(thread);
	if unlikely(!result_thread)
		return __NULLPTR;
	result = incref(FORTASK(result_thread, _this_taskpid));
	decref_unlikely(result_thread);
	return result;
}

FORCELOCAL WUNUSED ATTR_RETNONNULL REF struct task *KCALL
task_getsessionleader(void) THROWS(E_WOULDBLOCK) {
	REF struct task *result, *grp;
	grp = task_getprocessgroupleader();
	{
		FINALLY_DECREF_UNLIKELY(grp);
		sync_read(&FORTASK(grp, _this_taskgroup).tg_pgrp_session_lock);
		result = incref(FORTASK(grp, _this_taskgroup).tg_pgrp_session);
		sync_endread(&FORTASK(grp, _this_taskgroup).tg_pgrp_session_lock);
	}
	return result;
}

FORCELOCAL WUNUSED ATTR_RETNONNULL NONNULL((1)) REF struct task *KCALL
task_getsessionleader_of(struct task *__restrict thread) THROWS(E_WOULDBLOCK) {
	REF struct task *result, *grp;
	grp = task_getprocessgroupleader_of(thread);
	{
		FINALLY_DECREF_UNLIKELY(grp);
		sync_read(&FORTASK(grp, _this_taskgroup).tg_pgrp_session_lock);
		result = incref(FORTASK(grp, _this_taskgroup).tg_pgrp_session);
		sync_endread(&FORTASK(grp, _this_taskgroup).tg_pgrp_session_lock);
	}
	return result;
}

FORCELOCAL WUNUSED REF struct task *
NOTHROW(KCALL task_getsessionleader_nx)(void) {
	REF struct task *result, *grp;
	grp = task_getprocessgroupleader_nx();
	if unlikely(!grp)
		return __NULLPTR;
	if unlikely(!sync_read_nx(&FORTASK(grp, _this_taskgroup).tg_pgrp_session_lock)) {
		decref_unlikely(grp);
		return __NULLPTR;
	}
	result = incref(FORTASK(grp, _this_taskgroup).tg_pgrp_session);
	sync_endread(&FORTASK(grp, _this_taskgroup).tg_pgrp_session_lock);
	decref_unlikely(grp);
	return result;
}

FORCELOCAL WUNUSED NONNULL((1)) REF struct task *
NOTHROW(KCALL task_getsessionleader_of_nx)(struct task *__restrict thread) {
	REF struct task *result, *grp;
	grp = task_getprocessgroupleader_of_nx(thread);
	if unlikely(!grp)
		return __NULLPTR;
	if unlikely(!sync_read_nx(&FORTASK(grp, _this_taskgroup).tg_pgrp_session_lock)) {
		decref_unlikely(grp);
		return __NULLPTR;
	}
	result = incref(FORTASK(grp, _this_taskgroup).tg_pgrp_session);
	sync_endread(&FORTASK(grp, _this_taskgroup).tg_pgrp_session_lock);
	decref_unlikely(grp);
	return result;
}

FORCELOCAL WUNUSED ATTR_RETNONNULL REF struct taskpid *KCALL
task_getsessionleaderpid(void) THROWS(E_WOULDBLOCK) {
	REF struct taskpid *result;
	REF struct task *result_thread;
	result_thread = task_getsessionleader();
	result = incref(FORTASK(result_thread, _this_taskpid));
	decref_unlikely(result_thread);
	return result;
}

FORCELOCAL WUNUSED ATTR_RETNONNULL NONNULL((1)) REF struct taskpid *KCALL
task_getsessionleaderpid_of(struct task *__restrict thread) THROWS(E_WOULDBLOCK) {
	REF struct taskpid *result;
	REF struct task *result_thread;
	result_thread = task_getsessionleader_of(thread);
	result = incref(FORTASK(result_thread, _this_taskpid));
	decref_unlikely(result_thread);
	return result;
}


FORCELOCAL WUNUSED REF struct taskpid *
NOTHROW(KCALL task_getsessionleaderpid_nx)(void) {
	REF struct taskpid *result;
	REF struct task *result_thread;
	result_thread = task_getsessionleader_nx();
	if unlikely(!result_thread)
		return __NULLPTR;
	result = incref(FORTASK(result_thread, _this_taskpid));
	decref_unlikely(result_thread);
	return result;
}

FORCELOCAL WUNUSED NONNULL((1)) REF struct taskpid *
NOTHROW(KCALL task_getsessionleaderpid_of_nx)(struct task *__restrict thread) {
	REF struct taskpid *result;
	REF struct task *result_thread;
	result_thread = task_getsessionleader_of_nx(thread);
	if unlikely(!result_thread)
		return __NULLPTR;
	result = incref(FORTASK(result_thread, _this_taskpid));
	decref_unlikely(result_thread);
	return result;
}




FORCELOCAL WUNUSED ATTR_CONST bool
NOTHROW(KCALL task_isprocessleader)(void) {
	return PERTASK(_this_taskgroup.tg_process) == THIS_TASK;
}

FORCELOCAL WUNUSED ATTR_CONST bool
NOTHROW(KCALL task_isprocessleader_p)(struct task *__restrict thread) {
	return FORTASK(thread, _this_taskgroup.tg_process) == thread;
}


FORCELOCAL WUNUSED bool
NOTHROW(KCALL task_isprocessgroupleader)(void) {
	return PERTASK(_this_taskgroup.tg_proc_group) == THIS_TASK;
}

FORCELOCAL WUNUSED bool
NOTHROW(KCALL task_isprocessgroupleader_p)(struct task *__restrict thread) {
	return __hybrid_atomic_load(FORTASK(thread, _this_taskgroup.tg_proc_group),
	                            __ATOMIC_ACQUIRE) == thread;
}

FORCELOCAL WUNUSED bool
NOTHROW(KCALL task_issessionleader)(void) {
	return PERTASK(_this_taskgroup.tg_pgrp_session) == THIS_TASK;
}

FORCELOCAL WUNUSED bool
NOTHROW(KCALL task_issessionleader_p)(struct task *__restrict thread) {
	return __hybrid_atomic_load(FORTASK(thread, _this_taskgroup.tg_pgrp_session),
	                            __ATOMIC_ACQUIRE) == thread;
}

FORCELOCAL NOBLOCK WUNUSED upid_t NOTHROW(KCALL task_gettid)(void) {
	struct taskpid *pid = THIS_TASKPID;
	__hybrid_assertf(pid, "task_gettid() called by a kernel thread");
	return pid->tp_pids[pid->tp_pidns->pn_indirection];
}

FORCELOCAL NOBLOCK WUNUSED upid_t NOTHROW(KCALL task_gettid_s)(void) {
	struct taskpid *pid = THIS_TASKPID;
	return likely(pid) ? pid->tp_pids[pid->tp_pidns->pn_indirection] : 0;
}

FORCELOCAL NOBLOCK WUNUSED upid_t NOTHROW(KCALL task_getroottid)(void) {
	struct taskpid *pid = THIS_TASKPID;
	__hybrid_assertf(pid, "task_getroottid() called by a kernel thread");
	return pid->tp_pids[0];
}

FORCELOCAL NOBLOCK WUNUSED upid_t NOTHROW(KCALL task_getroottid_s)(void) {
	struct taskpid *pid = THIS_TASKPID;
	return likely(pid) ? pid->tp_pids[0] : 0;
}

FORCELOCAL NOBLOCK WUNUSED upid_t NOTHROW(KCALL task_getpid)(void) {
	struct taskpid *pid;
	struct task *leader = task_getprocess();
	__hybrid_assertf(leader, "task_getpid() called by a kernel thread");
	pid = FORTASK(leader, _this_taskpid);
	__hybrid_assertf(pid, "task_getpid() called by a thread within a kernel process");
	return pid->tp_pids[pid->tp_pidns->pn_indirection];
}

FORCELOCAL NOBLOCK WUNUSED upid_t NOTHROW(KCALL task_getpid_s)(void) {
	struct taskpid *pid;
	struct task *leader = task_getprocess();
	if unlikely(!leader)
		return 0;
	pid = FORTASK(leader, _this_taskpid);
	return likely(pid) ? pid->tp_pids[pid->tp_pidns->pn_indirection] : 0;
}

FORCELOCAL NOBLOCK WUNUSED upid_t NOTHROW(KCALL task_getrootpid)(void) {
	struct taskpid *pid;
	struct task *leader = task_getprocess();
	__hybrid_assertf(leader, "task_getrootpid() called by a kernel thread");
	pid = FORTASK(leader, _this_taskpid);
	__hybrid_assertf(pid, "task_getrootpid() called by a thread within a kernel process");
	return pid->tp_pids[0];
}

FORCELOCAL NOBLOCK WUNUSED upid_t NOTHROW(KCALL task_getrootpid_s)(void) {
	struct taskpid *pid;
	struct task *leader = task_getprocess();
	if unlikely(!leader)
		return 0;
	pid = FORTASK(leader, _this_taskpid);
	return likely(pid) ? pid->tp_pids[0] : 0;
}

FORCELOCAL NOBLOCK WUNUSED NONNULL((1)) upid_t
NOTHROW(KCALL task_gettid_of)(struct task *__restrict thread) {
	struct taskpid *pid   = FORTASK(thread, _this_taskpid);
	struct taskpid *mypid = THIS_TASKPID;
	__hybrid_assertf(pid, "task_gettid_of(%p) is a kernel thread", thread);
	__hybrid_assertf(mypid, "task_gettid_of(%p) called from a kernel thread", thread);
	__hybrid_assertf(mypid->tp_pidns->pn_indirection <= pid->tp_pidns->pn_indirection,
	                 "task_gettid_of(%p) PID cannot be represented in the caller's namespace", thread);
	return pid->tp_pids[mypid->tp_pidns->pn_indirection];
}

FORCELOCAL NOBLOCK WUNUSED NONNULL((1)) upid_t
NOTHROW(KCALL task_gettid_of_s)(struct task *__restrict thread) {
	struct taskpid *pid   = FORTASK(thread, _this_taskpid);
	struct taskpid *mypid = THIS_TASKPID;
	return likely(pid && mypid && mypid->tp_pidns->pn_indirection <= pid->tp_pidns->pn_indirection)
	       ? pid->tp_pids[mypid->tp_pidns->pn_indirection]
	       : 0;
}

FORCELOCAL NOBLOCK WUNUSED NONNULL((1)) upid_t
NOTHROW(KCALL task_getroottid_of)(struct task *__restrict thread) {
	struct taskpid *pid = FORTASK(thread, _this_taskpid);
	__hybrid_assertf(pid, "task_getroottid_of(%p) is a kernel thread", thread);
	return pid->tp_pids[0];
}

FORCELOCAL NOBLOCK WUNUSED NONNULL((1)) upid_t
NOTHROW(KCALL task_getroottid_of_s)(struct task *__restrict thread) {
	struct taskpid *pid = FORTASK(thread, _this_taskpid);
	return likely(pid) ? pid->tp_pids[0] : 0;
}

FORCELOCAL NOBLOCK WUNUSED NONNULL((1)) upid_t
NOTHROW(KCALL task_getpid_of)(struct task *__restrict thread) {
	struct taskpid *pid;
	struct taskpid *mypid = THIS_TASKPID;
	struct task *leader   = task_getprocess_of(thread);
	__hybrid_assertf(leader, "task_getpid_of(%p) is a kernel thread", thread);
	__hybrid_assertf(mypid, "task_getpid_of(%p) called from a kernel thread", thread);
	pid = FORTASK(leader, _this_taskpid);
	__hybrid_assertf(pid, "task_getpid_of(%p) is a thread within a kernel process", thread);
	__hybrid_assertf(mypid->tp_pidns->pn_indirection <= pid->tp_pidns->pn_indirection,
	                 "task_getpid_of(%p) PID cannot be represented in the caller's namespace", thread);
	return pid->tp_pids[mypid->tp_pidns->pn_indirection];
}

FORCELOCAL NOBLOCK WUNUSED NONNULL((1)) upid_t
NOTHROW(KCALL task_getpid_of_s)(struct task *__restrict thread) {
	struct taskpid *pid;
	struct task *leader   = task_getprocess_of(thread);
	struct taskpid *mypid = THIS_TASKPID;
	if unlikely(!leader || !mypid)
		return 0;
	pid = FORTASK(leader, _this_taskpid);
	return likely(pid && mypid && mypid->tp_pidns->pn_indirection <= pid->tp_pidns->pn_indirection)
	       ? pid->tp_pids[mypid->tp_pidns->pn_indirection]
	       : 0;
}

FORCELOCAL NOBLOCK WUNUSED NONNULL((1)) upid_t
NOTHROW(KCALL task_getrootpid_of)(struct task *__restrict thread) {
	struct taskpid *pid;
	struct task *leader = task_getprocess_of(thread);
	__hybrid_assertf(leader, "task_getrootpid_of(%p) is a kernel thread", thread);
	pid = FORTASK(leader, _this_taskpid);
	__hybrid_assertf(pid, "task_getrootpid_of(%p) is a thread within a kernel process", thread);
	return pid->tp_pids[0];
}

FORCELOCAL NOBLOCK WUNUSED NONNULL((1)) upid_t
NOTHROW(KCALL task_getrootpid_of_s)(struct task *__restrict thread) {
	struct taskpid *pid;
	struct task *leader = task_getprocess_of(thread);
	if unlikely(!leader)
		return 0;
	pid = FORTASK(leader, _this_taskpid);
	return likely(pid) ? pid->tp_pids[0] : 0;
}

#endif /* !__INTELLISENSE__ */

#endif /* __CC__ */

DECL_END

#ifdef GUARD_KERNEL_INCLUDE_DEV_TTYBASE_H
#ifndef GUARD_KERNEL_INCLUDE_SCHED_PID_CTTY_H
#include <sched/pid-ctty.h>
#endif /* !GUARD_KERNEL_INCLUDE_SCHED_PID_CTTY_H */
#endif /* GUARD_KERNEL_INCLUDE_DEV_TTYBASE_H */


#endif /* !GUARD_KERNEL_INCLUDE_SCHED_PID_H */
