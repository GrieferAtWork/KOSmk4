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
#ifndef GUARD_KERNEL_INCLUDE_SCHED_PID_H
#define GUARD_KERNEL_INCLUDE_SCHED_PID_H 1

#include <kernel/compiler.h>

#include <kernel/types.h>
#include <sched/pertask.h>
#include <sched/sig.h>

#include <hybrid/limitcore.h>
#include <hybrid/__assert.h>
#include <hybrid/sequence/list.h>
#include <hybrid/sequence/rbtree.h>
#include <hybrid/sched/atomic-rwlock.h>

#include <kos/aref.h>
#include <kos/lockop.h>


/* Valid range of PID numbers. Note that even though PIDs are signed,
 * structures like those found below may _only_ hold positive values.
 *
 * Negative PIDs in kernel control structures represent hard undefined
 * behavior and may lead to kernel panic, or similar. */
#define PID_MIN 1
#define PID_MAX __PRIVATE_MAX_S(__SIZEOF_PID_T__)

/* First PID that isn't reserved. (`0' is never assigned, and `1'
 * is only ever assigned to a PID namespace's root/init process). */
#define PIDNS_FIRST_NONRESERVED_PID 2


/* Default value for `pid_recycle_threshold' */
#ifndef PID_RECYCLE_THRESHOLD_DEFAULT
#define PID_RECYCLE_THRESHOLD_DEFAULT 32768 /* 2^16 */
#endif /* !PID_RECYCLE_THRESHOLD_DEFAULT */


#ifdef __CC__
DECL_BEGIN

/*
 * PID (or rather TID) data layout
 *
 * ```
 *           +------1..1---------+
 *           |                   v
 *       [taskpid] <--0..N--- [pidns] --+
 *        |    ^                 ^      |
 * weakref|    |                 |      | 0..1 (nested namespaces)
 *        |    | 1..1            +------+
 *        v    |
 *        [task]
 * ```
 *
 * NOTE: Process/Process-group/Session handling
 *       is  implemented  in `<sched/group.h>'!
 */


struct pidns;
struct taskpid;
struct task;
struct procgrp; /* Defined in <sched/group.h> */

#ifndef __task_awref_defined
#define __task_awref_defined
AWREF(task_awref, task);
#endif /* !__task_awref_defined */

struct taskpid_slot {
	LLRBTREE_NODE(taskpid) tps_link; /* [0..1][lock(:tp_ns->[pn_par...]->pn_lock)]
	                                  * Link entry within the associated PID namespace */
	upid_t                 tps_pid;  /* [const] PID relevant to this slot. */
};
#if __SIZEOF_PID_T__ == 4
#define _TASKPID_SLOT_PIDMASK __UINT32_C(0x7fffffff)
#define _TASKPID_SLOT_REDMASK __UINT32_C(0x80000000)
#elif __SIZEOF_PID_T__ == 8
#define _TASKPID_SLOT_PIDMASK __UINT64_C(0x7fffffffffffffff)
#define _TASKPID_SLOT_REDMASK __UINT64_C(0x8000000000000000)
#else /* __SIZEOF_PID_T__ == ... */
#error "Unsupported sizeof(pid_t)"
#endif /* __SIZEOF_PID_T__ != ... */
#define _taskpid_slot_getpidno(self) ((pid_t)((self).tps_pid & _TASKPID_SLOT_PIDMASK))



/************************************************************************/
/* TASK PID OBJECT                                                      */
/************************************************************************/
struct taskpid {
	WEAK refcnt_t           tp_refcnt;  /* Reference counter. */
#if (defined(__WANT_TASKPID__tp_nslop) || \
     defined(__WANT_TASKPID__tp_grplop))
	union {
		struct {
			struct task_awref tp_thread;  /* ... */
			struct sig        tp_changed; /* ... */
			uint16_t          tp_status;  /* ... */
			uint8_t           tp_SIGCLD;  /* ... */
			uint8_t          _tp_pad[sizeof(void *) - 3]; /* ... */
		};
#ifdef __WANT_TASKPID__tp_nslop
		Toblockop(pidns)     _tp_nslop;   /* Used internally during destruction */
		Tobpostlockop(pidns) _tp_nsplop;  /* Used internally during destruction */
#endif /* __WANT_TASKPID__tp_nslop */
#ifdef __WANT_TASKPID__tp_grplop
		Toblockop(procgrp)     _tp_grplop;   /* Used internally during destruction */
		Tobpostlockop(procgrp) _tp_grpplop;  /* Used internally during destruction */
#endif /* __WANT_TASKPID__tp_grplop */
	};
#else /* ... */
	struct task_awref       tp_thread;  /* [0..1] The pointed-to task (or `NULL' if destroyed) */
	struct sig              tp_changed; /* Signal broadcast after changing `tp_status'. */
	uint16_t                tp_status;  /* [const_if(!tp_thread || wasdestroyed(tp_thread) ||
	                                     *           tp_thread->t_flags & TASK_FTERMINATING)]
	                                     * [lock(PRIVATE(tp_thread == THIS_TASK))]
	                                     * Current thread status (~ala `union wait'). */
	uint8_t                 tp_SIGCLD;  /* [const] Signal number send to parent process when `tp_status' changes. */
	uint8_t                _tp_pad[sizeof(void *) - 3]; /* ... */
#endif /* !... */
	REF struct taskpid     *tp_proc;    /* [1..1][ref_if(!= this)][const] PID descriptor for associated process. */
	struct procctl         *tp_pctl;    /* [1..1][owned_if(tp_proc == this)][== tp_proc->tp_pctl][const] Process controller. */
	LIST_ENTRY(REF taskpid) tp_parsib;  /* [0..1] Chain of sibling tasks:
	                                     * - If `tp_proc == this': Link in chain of other processes spawned by the parent process of `tp_thread'
	                                     * - If `tp_proc != this': Link in chain of sibling threads spawned within the same process
	                                     * Marked as unbound if this taskpid has been wait(2)-ed for. */
	REF struct pidns       *tp_ns;      /* [1..1][const][== tp_proc->tp_ns]
	                                     * Top-level PID namespace containing this descriptor. Note
	                                     * that threads are  _required_ to reside  in the same  PID
	                                     * namespace as a  process's main thread.  This is  assumed
	                                     * by stuff like `task_getpid()'. */
	COMPILER_FLEXIBLE_ARRAY(struct taskpid_slot,
	                        tp_pids);   /* [const][tp_ns->pn_ind+1] Task PID value from different namespaces. */
};

/* Allocate a taskpid descriptor for use with a given `ns' */
#define _taskpid_sizeof(ns)                         \
	((__builtin_offsetof(struct taskpid, tp_pids) + \
	  ((ns)->pn_ind + 1) * sizeof(struct taskpid_slot)))
#define _taskpid_alloc(ns)  ((struct taskpid *)kmalloc(_taskpid_sizeof(ns), GFP_NORMAL))
#define _taskpid_free(self) kfree(__COMPILER_REQTYPE(struct taskpid *, self))

/* Destroy the given taskpid. */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL taskpid_destroy)(struct taskpid *__restrict self);
DEFINE_REFCNT_FUNCTIONS(struct taskpid, tp_refcnt, taskpid_destroy)

/* [1..1][const] The PID associated with the calling thread. */
DATDEF ATTR_PERTASK REF struct taskpid *this_taskpid;
#ifdef __INTELLISENSE__
extern struct taskpid *THIS_TASKPID;
extern struct pidns *THIS_PIDNS;
#define THIS_TASKPID THIS_TASKPID
#define THIS_PIDNS   THIS_PIDNS
#else /* __INTELLISENSE__ */
#define THIS_TASKPID PERTASK_GET(this_taskpid)
#define THIS_PIDNS   PERTASK_GET(this_taskpid)->tp_ns
#endif /* !__INTELLISENSE__ */

/* Return a reference/pointer to the thread associated with `self'
 * Returns `NULL'  when said  thread has  already been  destroyed. */
#define taskpid_gettask(self)    ({ struct taskpid *__tpgt_self = (self); awref_get(&__tpgt_self->tp_thread); })
#define taskpid_gettaskptr(self) awref_ptr(&(self)->tp_thread)

/* Same as `taskpid_gettask()', but throw an exception if the thread has exited. */
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct task *FCALL
taskpid_gettask_srch(struct taskpid *__restrict self)
		THROWS(E_PROCESS_EXITED);

/* Return the # of TIDs defined by `self' */
#define taskpid_gettidcount(self) ((self)->tp_ns->pn_ind + 1)

/* Return `self's TID number associated with `ns' */
#ifdef NDEBUG
#define taskpid_getnstid(self, ns) \
	_taskpid_slot_getpidno((self)->tp_pids[(ns)->pn_ind])
#else /* NDEBUG */
#define taskpid_getnstid(self, ns)                                      \
	({                                                                  \
		struct taskpid const *_tpgp_self = (self);                      \
		struct pidns const *_tpgp_ns     = (ns);                        \
		__hybrid_assert(_tpgp_self->tp_ns->pn_ind >= _tpgp_ns->pn_ind); \
		_taskpid_slot_getpidno(_tpgp_self->tp_pids[_tpgp_ns->pn_ind]);  \
	})
#endif /* !NDEBUG */

/* Same as `taskpid_getnstid()', but return `0' if `self' doesn't appear in `ns' */
#define taskpid_getnstid_s(self, ns)                                       \
	({                                                                     \
		struct taskpid const *_tpgps_self = (self);                        \
		struct pidns const *_tpgps_ns     = (ns);                          \
		(likely(_tpgps_self->tp_ns->pn_ind >= _tpgps_ns->pn_ind)           \
		 ? _taskpid_slot_getpidno(_tpgps_self->tp_pids[_tpgps_ns->pn_ind]) \
		 : 0);                                                             \
	})

#define taskpid_gettid(self)   taskpid_getnstid(self, THIS_PIDNS)
#define taskpid_gettid_s(self) taskpid_getnstid_s(self, THIS_PIDNS)


/* Return `self's TID number within its own namespace */
#define taskpid_getselftid(self)                                                  \
	({                                                                            \
		struct taskpid const *_tpgsp_self = (self);                               \
		_taskpid_slot_getpidno(_tpgsp_self->tp_pids[_tpgsp_self->tp_ns->pn_ind]); \
	})

/* Return `self's TID number within the root namespace */
#define taskpid_getroottid(self) _taskpid_slot_getpidno((self)->tp_pids[0])

/* Query the process ID of a given taskpid */
#define taskpid_gettidcount(self) ((self)->tp_ns->pn_ind + 1)

/* Query sub-elements of `struct taskpid' */
#define taskpid_getprocpid(self)  (self)->tp_proc
#define taskpid_getprocctl(self)  (self)->tp_pctl
#define taskpid_isaprocess(self)  ((self) == taskpid_getprocpid(self))
#define _taskpid_isaprocess(self) ({ struct taskpid const *_tpiap_self = (self); taskpid_isaprocess(_tpiap_self); })

/* Return `self's PID number associated with `ns' */
#define taskpid_getnspid(self, ns)   taskpid_getnstid(taskpid_getprocpid(self), ns)
#define taskpid_getnspid_s(self, ns) taskpid_getnstid_s(taskpid_getprocpid(self), ns)
#define taskpid_getpid(self)         taskpid_gettid(taskpid_getprocpid(self))
#define taskpid_getpid_s(self)       taskpid_gettid_s(taskpid_getprocpid(self))
#define taskpid_getselfpid(self)     taskpid_getselftid(taskpid_getprocpid(self))
#define taskpid_getrootpid(self)     taskpid_getroottid(taskpid_getprocpid(self))

/* Check if `a' and `b' are part of the same process */
#define taskpid_sameproc(a, b) (taskpid_getprocpid(a) == taskpid_getprocpid(b))





/************************************************************************/
/* TASK PID NAMESPACE                                                   */
/************************************************************************/
struct pidns {
	WEAK refcnt_t               pn_refcnt;  /* Reference counter. */
	size_t                      pn_ind;     /* [const][(== 0) == (. == &pidns_root)]
	                                         * Indirection of this PID namespace. (== number of PIDs that are
	                                         * associated  with every `struct taskpid' within this namespace)
	                                         * NOTE: `pidns_root' is the only namespace with `pn_ind == 0'! */
	REF struct pidns           *pn_par;     /* [1..1][const][->pn_ind == pn_ind-1]
	                                         * [valid_if(pn_ind != 0 <=> . != &pidns_root)]
	                                         * The parenting PID namespace with one less indirection.
	                                         * NOTE: For `pidns_root', this field is set to `NULL'. */
	size_t                      pn_size;    /* # of elements in `pn_tree'. -- For the root namespace == # of threads in system */
	struct atomic_rwlock        pn_lock;    /* Lock for accessing the LLRB-tree below. */
	Toblockop_slist(pidns)      pn_lops;    /* [0..n][lock(ATOMIC)] Lock operations for `pn_lock'. */
	LLRBTREE_ROOT(WEAK taskpid) pn_tree;    /* [LINK(->tp_pids[pn_ind].tps_link)][0..n][lock(pn_lock)]
	                                         * Tree of PIDs (pids remove themselves upon destruction). */
	LLRBTREE_ROOT(WEAK procgrp) pn_tree_pg; /* [LINK(->pgc_pids[pn_ind].pgs_link)][0..n][lock(pn_lock)]
	                                         * Tree of process groups (groups remove themselves upon destruction). */
	pid_t                       pn_npid;    /* [lock(pn_lock)] Next PID to hand out. (in [PIDNS_FIRST_NONRESERVED_PID,PID_MAX]) */
};

/* Helper macros for working with `struct pidns::pn_lock' */
#define pidns_mustreap(self)     oblockop_mustreap(&(self)->pn_lops)
#define _pidns_reap(self)        _oblockop_reap_atomic_rwlock(&(self)->pn_lops, &(self)->pn_lock, self)
#define pidns_reap(self)         oblockop_reap_atomic_rwlock(&(self)->pn_lops, &(self)->pn_lock, self)
#define pidns_write(self)        atomic_rwlock_write(&(self)->pn_lock)
#define pidns_write_nx(self)     atomic_rwlock_write_nx(&(self)->pn_lock)
#define pidns_trywrite(self)     atomic_rwlock_trywrite(&(self)->pn_lock)
#define pidns_endwrite(self)     (atomic_rwlock_endwrite(&(self)->pn_lock), pidns_reap(self))
#define _pidns_endwrite(self)    atomic_rwlock_endwrite(&(self)->pn_lock)
#define pidns_read(self)         atomic_rwlock_read(&(self)->pn_lock)
#define pidns_read_nx(self)      atomic_rwlock_read_nx(&(self)->pn_lock)
#define pidns_tryread(self)      atomic_rwlock_tryread(&(self)->pn_lock)
#define _pidns_endread(self)     atomic_rwlock_endread(&(self)->pn_lock)
#define pidns_endread(self)      (void)(atomic_rwlock_endread(&(self)->pn_lock) && (pidns_reap(self), 0))
#define _pidns_end(self)         atomic_rwlock_end(&(self)->pn_lock)
#define pidns_end(self)          (void)(atomic_rwlock_end(&(self)->pn_lock) && (pidns_reap(self), 0))
#define pidns_upgrade(self)      atomic_rwlock_upgrade(&(self)->pn_lock)
#define pidns_upgrade_nx(self)   atomic_rwlock_upgrade_nx(&(self)->pn_lock)
#define pidns_tryupgrade(self)   atomic_rwlock_tryupgrade(&(self)->pn_lock)
#define pidns_downgrade(self)    atomic_rwlock_downgrade(&(self)->pn_lock)
#define pidns_reading(self)      atomic_rwlock_reading(&(self)->pn_lock)
#define pidns_writing(self)      atomic_rwlock_writing(&(self)->pn_lock)
#define pidns_canread(self)      atomic_rwlock_canread(&(self)->pn_lock)
#define pidns_canwrite(self)     atomic_rwlock_canwrite(&(self)->pn_lock)
#define pidns_waitread(self)     atomic_rwlock_waitread(&(self)->pn_lock)
#define pidns_waitwrite(self)    atomic_rwlock_waitwrite(&(self)->pn_lock)
#define pidns_waitread_nx(self)  atomic_rwlock_waitread_nx(&(self)->pn_lock)
#define pidns_waitwrite_nx(self) atomic_rwlock_waitwrite_nx(&(self)->pn_lock)

/* `/proc/sys/kernel/pid_max': When `pn_nextpid' >= this
 * value, start recycling  PIDs. (in  [PID_MIN,PID_MAX]) */
DATDEF pid_t pid_recycle_threshold;

/* The root PID namespace. */
DATDEF struct pidns pidns_root;

/* Destroy a given PID namespace. */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL pidns_destroy)(struct pidns *__restrict self);
DEFINE_REFCNT_FUNCTIONS(struct pidns, pn_refcnt, pidns_destroy)

/* Allocate a new child PID namespace for `parent' */
FUNDEF ATTR_RETNONNULL NONNULL((1)) REF struct pidns *FCALL
pidns_alloc(struct pidns *__restrict parent) THROWS(E_BADALLOC);

/* Lookup a thread in a given PID namespace. */
FUNDEF WUNUSED NONNULL((1)) REF struct taskpid *FCALL pidns_lookup(struct pidns *__restrict self, pid_t pid) THROWS(E_WOULDBLOCK);
FUNDEF WUNUSED NONNULL((1)) REF struct task *FCALL pidns_lookuptask(struct pidns *__restrict self, pid_t pid) THROWS(E_WOULDBLOCK);
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct taskpid *FCALL pidns_lookup_srch(struct pidns *__restrict self, pid_t pid) THROWS(E_WOULDBLOCK, E_PROCESS_EXITED, E_INVALID_ARGUMENT_BAD_VALUE);
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct task *FCALL pidns_lookuptask_srch(struct pidns *__restrict self, pid_t pid) THROWS(E_WOULDBLOCK, E_PROCESS_EXITED, E_INVALID_ARGUMENT_BAD_VALUE);

/* Return the taskpid object associated with `pid' within `self' */
FUNDEF NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) struct taskpid *
NOTHROW(FCALL pidns_lookup_locked)(struct pidns const *__restrict self, pid_t pid);
FUNDEF NOBLOCK WUNUSED NONNULL((1)) REF struct task *
NOTHROW(FCALL pidns_lookuptask_locked)(struct pidns const *__restrict self, pid_t pid);

/* Return the taskpid object with the lowest PID (in `self'), that is still `>= min_pid'
 * This  function is  used for task  enumeration for things  such as `opendir("/proc")'. */
FUNDEF NOBLOCK WUNUSED NONNULL((1)) REF struct taskpid *
NOTHROW(FCALL pidns_lookupnext_locked)(struct pidns const *__restrict self, pid_t min_pid);

/* Same as `pidns_lookupnext_locked()', but only enumerate actual processes (skip threads) */
FUNDEF NOBLOCK WUNUSED NONNULL((1)) REF struct taskpid *
NOTHROW(FCALL pidns_lookupnextproc_locked)(struct pidns const *__restrict self, pid_t min_pid);

/* Try to acquire write-locks to all PID namespaces reachable from `self'
 * Upon success, return `NULL'; else: return the blocking PID  namespace.
 * @return: NULL: Success
 * @return: * :   The blocking PID namespace. */
FUNDEF NOBLOCK WUNUSED NONNULL((1)) struct pidns *
NOTHROW(FCALL pidns_trywriteall)(struct pidns *__restrict self);
/* Release write-locks from all PID namespaces reachable from `self' */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL pidns_endwriteall)(struct pidns *__restrict self);

/* Insert a given `tpid' into the tree of `self'.
 * The caller is responsible to:
 *  - Assign `tpid->tp_pids[self->pn_ind].tps_pid'
 *  - Ensure that `pidns_lookup_locked(self, tpid->tp_pids[self->pn_ind].tps_pid) == NULL'
 *  - Be holding a lock to `self->pn_lock'
 * This function is only responsible for doing the actual
 * inserting of `tpid' into the LLRB-tree of `self',  and
 * it's  the caller's responsibility to ensure that doing
 * so actually makes sense! */
FUNDEF NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL pidns_insertpid)(struct pidns *__restrict self,
                               struct taskpid *__restrict tpid);

/* Do the reverse of `pidns_insertpid()' and remove the PID
 * descriptor associated with a given `pid' (which is  then
 * returned).  In this sense, this function behaves similar
 * to `pidns_lookup_locked', except that the taskpid object
 * is also removed from the tree.
 * When no taskpid is associated with `pid', return `NULL'. */
FUNDEF NOBLOCK NONNULL((1)) struct taskpid *
NOTHROW(FCALL pidns_removepid)(struct pidns *__restrict self, pid_t pid);

/* Find the first (lowest) unused  pid that is in  [minpid,maxpid]
 * If no such pid exists (or when `minpid > maxpid'), return `-1'. */
FUNDEF NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) pid_t
NOTHROW(FCALL pidns_findpid)(struct pidns const *__restrict self,
                             pid_t minpid, pid_t maxpid);

/* Return the next free PID  to-be assigned to a new  thread/process
 * In the (highly unlikely) even that all PIDs are in use, and  none
 * can be reclaimed (iow: `self' contains 2^31 threads), return `-1'
 * instead.
 *
 * Allocation  of a PID  is done by use  of `pidns_insertpid', but in
 * addition to this, the  caller must also increment  `self->pn_npid'
 * to `return + 1' once  they inserted the  PID into this  namespace!
 * This only happens when `#ifdef PIDNS_NEXTPID_CAN_RETURN_MINUS_ONE' */
FUNDEF NOBLOCK WUNUSED NONNULL((1)) pid_t
NOTHROW(FCALL pidns_nextpid)(struct pidns const *__restrict self);
#if __SIZEOF_POINTER__ > 4
#define PIDNS_NEXTPID_CAN_RETURN_MINUS_ONE
#endif /* __SIZEOF_POINTER__ > 4 */


/* Allocate+assign PIDs of `self' in all of its namespaces.
 * NOTE: This function _DOESNT_ insert `self' into the relevant namespaces.
 * NOTE: The caller must be holding `pidns_trywriteall(self->tp_ns)'
 * @return: true:  Success.
 * @return: false: Failed to allocate a PID in at least one namespace. */
#ifdef PIDNS_NEXTPID_CAN_RETURN_MINUS_ONE
FUNDEF NOBLOCK WUNUSED NONNULL((1)) bool
NOTHROW(FCALL pidns_allocpids)(struct taskpid *__restrict self);
#else /* PIDNS_NEXTPID_CAN_RETURN_MINUS_ONE */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL pidns_allocpids)(struct taskpid *__restrict self);
#endif /* !PIDNS_NEXTPID_CAN_RETURN_MINUS_ONE */


/* Return the process group associated with `pgid' within `self' */
FUNDEF WUNUSED NONNULL((1)) REF struct procgrp *FCALL
pidns_grplookup(struct pidns *__restrict self, pid_t pgid) THROWS(E_WOULDBLOCK);
FUNDEF WUNUSED NONNULL((1)) REF struct procgrp *FCALL
pidns_grplookup_srch(struct pidns *__restrict self, pid_t pgid)
		THROWS(E_WOULDBLOCK, E_PROCESS_GROUP_EXITED, E_INVALID_ARGUMENT_BAD_VALUE);
FUNDEF NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) struct procgrp *
NOTHROW(FCALL pidns_grplookup_locked)(struct pidns const *__restrict self, pid_t pgid);

/* Insert/Remove a process group to/from the given namespace. */
FUNDEF NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL pidns_grpinsert)(struct pidns *__restrict self,
                               struct procgrp *__restrict grp);
FUNDEF NOBLOCK NONNULL((1)) struct procgrp *
NOTHROW(FCALL pidns_grpremove)(struct pidns *__restrict self, pid_t pgid);


#define task_gettaskpid()          THIS_TASKPID                                   /* Return task-pid of calling thread */
#define task_getprocpid()          task_gettaskpid()->tp_proc                     /* Return proc-pid of calling thread */
#define task_gettaskpid_of(thread) FORTASK(thread, this_taskpid)                  /* Return task-pid of given thread */
#define task_getprocpid_of(thread) taskpid_getprocpid(task_gettaskpid_of(thread)) /* Return proc-pid of given thread */
#define task_getprocctl()          task_gettaskpid()->tp_pctl                     /* Return process controller of calling thread */
#define task_getprocctl_of(thread) taskpid_getprocctl(task_gettaskpid_of(thread)) /* Return process controller of given thread */

/* Return the process-task associated with a given thread. */
#define task_getproc()             taskpid_gettask(task_getprocpid())             /* >> REF struct task * [0..1] */
#define task_getproc_of(thread)    taskpid_gettask(task_getprocpid_of(thread))    /* >> REF struct task * [0..1] */
#define task_getprocptr()          taskpid_gettaskptr(task_getprocpid())          /* >> struct task * [0..1] */
#define task_getprocptr_of(thread) taskpid_gettaskptr(task_getprocpid_of(thread)) /* >> struct task * [0..1] */

/* Check if the calling/given thread is a process leader. */
#define task_isprocess()        _taskpid_isaprocess(task_gettaskpid())
#define task_isaprocess(thread) _taskpid_isaprocess(task_gettaskpid_of(thread))

#define task_getprocesspid    task_getprocpid    /* Deprecated */
#define task_getprocesspid_of task_getprocpid_of /* Deprecated */

/* Return the TID (thread id) /  PID (process id / thread  id
 * of the process leader) of the calling thread. The returned
 * IDS are either relative to  the task's own PID  namespace,
 * to the ROOT pid namespace, or the given namespace. */
#define task_gettid()                  taskpid_getselftid(task_gettaskpid())              /* Return TID of calling thread (in its own namespace) */
#define task_gettid_of(thread)         taskpid_gettid(task_gettaskpid_of(thread))         /* Return TID of given thread (in caller's namespace; panic/undefined if not mapped) */
#define task_gettid_of_s(thread)       taskpid_gettid_s(task_gettaskpid_of(thread))       /* Return TID of given thread (in caller's namespace; `0' if not mapped) */
#define task_getselftid_of(thread)     taskpid_getselftid(task_gettaskpid_of(thread))     /* Return TID of given thread (in its own namespace) */
#define task_getroottid()              taskpid_getroottid(task_gettaskpid())              /* Return TID of calling thread (in root namespace) */
#define task_getroottid_of(thread)     taskpid_getroottid(task_gettaskpid_of(thread))     /* Return TID of given thread (in root namespace) */
#define task_getnstid(ns)              taskpid_getnstid(task_gettaskpid(), ns)            /* Return TID of calling thread (in given namespace; panic/undefined if not mapped) */
#define task_getnstid_s(ns)            taskpid_getnstid_s(task_gettaskpid(), ns)          /* Return TID of calling thread (in given namespace; `0' if not mapped) */
#define task_getnstid_of(thread, ns)   taskpid_getnstid(task_gettaskpid_of(thread), ns)   /* Return TID of given thread (in given namespace; panic/undefined if not mapped) */
#define task_getnstid_of_s(thread, ns) taskpid_getnstid_s(task_gettaskpid_of(thread), ns) /* Return TID of given thread (in given namespace; `0' if not mapped) */
#define task_getpid()                  taskpid_getselftid(task_getprocpid())              /* Return PID of calling thread (in its own namespace) */
#define task_getpid_of(thread)         taskpid_gettid(task_getprocpid_of(thread))         /* Return PID of given thread (in caller's namespace; panic/undefined if not mapped) */
#define task_getpid_of_s(thread)       taskpid_gettid_s(task_getprocpid_of(thread))       /* Return PID of given thread (in caller's namespace; `0' if not mapped) */
#define task_getselfpid_of(thread)     taskpid_getselftid(task_getprocpid_of(thread))     /* Return PID of given thread (in its own namespace) */
#define task_getrootpid()              taskpid_getroottid(task_getprocpid())              /* Return PID of calling thread (in root namespace) */
#define task_getrootpid_of(thread)     taskpid_getroottid(task_getprocpid_of(thread))     /* Return PID of given thread (in root namespace) */
#define task_getnspid(ns)              taskpid_getnstid(task_getprocpid(), ns)            /* Return PID of calling thread (in given namespace; panic/undefined if not mapped) */
#define task_getnspid_s(ns)            taskpid_getnstid_s(task_getprocpid(), ns)          /* Return PID of calling thread (in given namespace; `0' if not mapped) */
#define task_getnspid_of(thread, ns)   taskpid_getnstid(task_getprocpid_of(thread), ns)   /* Return PID of given thread (in given namespace; panic/undefined if not mapped) */
#define task_getnspid_of_s(thread, ns) taskpid_getnstid_s(task_getprocpid_of(thread), ns) /* Return PID of given thread (in given namespace; `0' if not mapped) */

DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_SCHED_PID_H */
