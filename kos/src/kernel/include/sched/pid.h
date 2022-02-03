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
#ifndef GUARD_KERNEL_INCLUDE_SCHED_PID_H
#define GUARD_KERNEL_INCLUDE_SCHED_PID_H 1

#include <kernel/compiler.h>

#include <kernel/types.h>
#include <sched/pertask.h>
#include <sched/signal.h>

#include <hybrid/limitcore.h>
#include <hybrid/__assert.h>
#include <hybrid/sequence/list.h>
#include <hybrid/sequence/rbtree.h>
#include <hybrid/sync/atomic-rwlock.h>

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
 *        |    | 0..1            +------+
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
#define __TASKPID_SLOT_PIDMASK __UINT32_C(0x7fffffff)
#define __TASKPID_SLOT_REDMASK __UINT32_C(0x80000000)
#elif __SIZEOF_PID_T__ == 8
#define __TASKPID_SLOT_PIDMASK __UINT64_C(0x7fffffffffffffff)
#define __TASKPID_SLOT_REDMASK __UINT64_C(0x8000000000000000)
#else /* __SIZEOF_PID_T__ == ... */
#error "Unsupported sizeof(pid_t)"
#endif /* __SIZEOF_PID_T__ != ... */
#define _taskpid_slot_getpidno(self) ((pid_t)((self).tps_pid & __TASKPID_SLOT_PIDMASK))



/************************************************************************/
/* TASK PID OBJECT                                                      */
/************************************************************************/
struct taskpid {
	WEAK refcnt_t           tp_refcnt;  /* Reference counter. */
#ifdef __WANT_TASKPID__tp_lop
	union {
		struct {
			struct task_awref tp_thread;  /* ... */
			struct sig        tp_changed; /* ... */
			uint16_t          tp_status;  /* ... */
			uint8_t           tp_SIGCLD;  /* ... */
			uint8_t          _tp_pad[sizeof(void *) - 3]; /* ... */
		};
		Toblockop(pidns)     _tp_lop;   /* Used internally during destruction */
		Tobpostlockop(pidns) _tp_plop;  /* Used internally during destruction */
	};
#else /* __WANT_TASKPID__tp_lop */
	struct task_awref       tp_thread;  /* [0..1] The pointed-to task (or `NULL' if destroyed) */
	struct sig              tp_changed; /* Signal broadcast after changing `tp_status'. */
	uint16_t                tp_status;  /* [const_if(!tp_thread || wasdestroyed(tp_thread) ||
	                                     *           tp_thread->t_flags & TASK_FTERMINATING)]
	                                     * [lock(PRIVATE(tp_thread == THIS_TASK))]
	                                     * Current thread status (~ala `union wait'). */
	uint8_t                 tp_SIGCLD;  /* [const] Signal number send to parent process when `tp_status' changes. */
	uint8_t                _tp_pad[sizeof(void *) - 3]; /* ... */
#endif /* !__WANT_TASKPID__tp_lop */
#ifdef CONFIG_USE_NEW_GROUP
	REF struct taskpid     *tp_proc;    /* [1..1][ref_if(!= this)][const] PID descriptor for associated process. */
	struct procctl         *tp_pctl;    /* [1..1][owned_if(tp_proc == this)][== tp_proc->tp_pctl][const] Process controller. */
	LIST_ENTRY(REF taskpid) tp_parsib;  /* [1..1] Chain of sibling tasks:
	                                     * - If `tp_proc == this': Link in chain of other processes spawned by the parent process of `tp_thread'
	                                     * - If `tp_proc != this': Link in chain of sibling threads spawned within the same process */
#else /* CONFIG_USE_NEW_GROUP */
	LIST_ENTRY(REF taskpid) tp_parsib;  /* [0..1] Chain of sibling tasks:
	                                     * - If `tp_proc == this':
	                                     *   Link in chain of other processes spawned by the parent process of `tp_thread'
	                                     * - If `tp_proc != this':
	                                     *   Link in chain of sibling threads spawned within the same process */
#endif /* !CONFIG_USE_NEW_GROUP */
	REF struct pidns       *tp_ns;      /* [1..1][const] Top-level PID namespace containing this descriptor. */
	COMPILER_FLEXIBLE_ARRAY(struct taskpid_slot,
	                        tp_pids);   /* [const][tp_ns->pn_ind+1] Task PID value from different namespaces. */
};

/* Allocate a taskpid descriptor for use with a given `ns' */
#define taskpid_alloc(ns)                                                        \
	((struct taskpid *)kmalloc(__builtin_offsetof(struct taskpid, tp_pids) +     \
	                           ((ns)->pn_ind + 1) * sizeof(struct taskpid_slot), \
	                           GFP_NORMAL))
#define taskpid_free(self) kfree(self)

/* Destroy the given taskpid. */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL taskpid_destroy)(struct taskpid *__restrict self);
DEFINE_REFCOUNT_FUNCTIONS(struct taskpid, tp_refcnt, taskpid_destroy)

/* [1..1][const] The PID associated with the calling thread. */
DATDEF ATTR_PERTASK struct taskpid *this_taskpid;
#define THIS_TASKPID PERTASK_GET(this_taskpid)
#define THIS_PIDNS   PERTASK_GET(this_taskpid)->tp_ns

/* Return a reference/pointer to the thread associated with `self'
 * Returns `NULL'  when said  thread has  already been  destroyed. */
#define taskpid_gettask(self)    awref_get(&(self)->tp_thread)
#define taskpid_gettaskptr(self) awref_ptr(&(self)->tp_thread)

/* Same as `taskpid_gettask()', but throw an exception if the thread has exited. */
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct task *FCALL
taskpid_gettask_srch(struct taskpid *__restrict self)
		THROWS(E_PROCESS_EXITED);

/* Return the # of PIDs defined by `self' */
#define taskpid_getpidnocount(self) ((self)->tp_ns->pn_ind + 1)

/* Return `self's PID number associated with `ns' */
#ifdef NDEBUG
#define taskpid_getnspidno(self, ns) \
	_taskpid_slot_getpidno((self)->tp_pids[(ns)->pn_ind])
#else /* NDEBUG */
#define taskpid_getnspidno(self, ns)                                      \
	({                                                                    \
		struct taskpid const *__tpgp_self = (self);                       \
		struct pidns const *__tpgp_ns     = (ns);                         \
		__hybrid_assert(__tpgp_self->tp_ns->pn_ind >= __tpgp_ns->pn_ind); \
		_taskpid_slot_getpidno(__tpgp_self->tp_pids[__tpgp_ns->pn_ind]);  \
	})
#endif /* !NDEBUG */

/* Same as `taskpid_getnspidno()', but return `0' if `self' doesn't appear in `ns' */
#define taskpid_getnspidno_s(self, ns)                                       \
	({                                                                       \
		struct taskpid const *__tpgps_self = (self);                         \
		struct pidns const *__tpgps_ns     = (ns);                           \
		(likely(__tpgps_self->tp_ns->pn_ind >= __tpgps_ns->pn_ind)           \
		 ? _taskpid_slot_getpidno(__tpgps_self->tp_pids[__tpgps_ns->pn_ind]) \
		 : 0);                                                               \
	})

#define taskpid_getpidno(self)   taskpid_getnspidno(self, THIS_PIDNS)
#define taskpid_getpidno_s(self) taskpid_getnspidno_s(self, THIS_PIDNS)


/* Return `self's PID number within its own namespace */
#define taskpid_getselfpidno(self)                                                  \
	({                                                                              \
		struct taskpid const *__tpgsp_self = (self);                                \
		_taskpid_slot_getpidno(__tpgsp_self->tp_pids[__tpgsp_self->tp_ns->pn_ind]); \
	})

/* Return `self's PID number within the root namespace */
#define taskpid_getrootpidno(self) _taskpid_slot_getpidno((self)->tp_pids[0])




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
	struct atomic_rwlock        pn_lock;    /* Lock for accessing the LLRB-tree below. */
	Toblockop_slist(pidns)      pn_lops;    /* [0..n][lock(ATOMIC)] Lock operations for `pn_lock'. */
	LLRBTREE_ROOT(WEAK taskpid) pn_tree;    /* [LINK(->tp_pids[pn_ind].tps_link)][0..n][lock(pn_lock)]
	                                         * Tree of PIDs (pids remove themselves upon destruction). */
#ifdef CONFIG_USE_NEW_GROUP
	LLRBTREE_ROOT(WEAK procgrp) pn_tree_pg; /* [LINK(->pgc_pids[pn_ind].pgs_link)][0..n][lock(pn_lock)]
	                                         * Tree of process groups (groups remove themselves upon destruction). */
	/* TODO: When implementing CONFIG_USE_NEW_GROUP, remember that PIDs cannot be
	 *       re-used if there is EITHER a process with that ID, or a process group
	 *       with that ID (s.a. posix -- "4.13 Process ID Reuse") */
#endif /* CONFIG_USE_NEW_GROUP */
	pid_t                       pn_npid;    /* [lock(pn_lock)] Next PID to hand out. (in [PIDNS_FIRST_NONRESERVED_PID,PID_MAX]) */
};

/* Helper macros for working with `struct pidns::pn_lock' */
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
DEFINE_REFCOUNT_FUNCTIONS(struct pidns, pn_refcnt, pidns_destroy)

/* Allocate a new child PID namespace for `parent' */
FUNDEF ATTR_RETNONNULL NONNULL((1)) REF struct pidns *FCALL
pidns_alloc(struct pidns *__restrict parent) THROWS(E_BADALLOC);

/* Lookup a thread in a given PID namespace. */
FUNDEF WUNUSED NONNULL((1)) REF struct taskpid *FCALL pidns_lookup(struct pidns *__restrict self, pid_t pid) THROWS(E_WOULDBLOCK);
FUNDEF WUNUSED NONNULL((1)) REF struct task *FCALL pidns_lookuptask(struct pidns *__restrict self, pid_t pid) THROWS(E_WOULDBLOCK);
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct taskpid *FCALL pidns_lookup_srch(struct pidns *__restrict self, pid_t pid) THROWS(E_WOULDBLOCK, E_PROCESS_EXITED);
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct task *FCALL pidns_lookuptask_srch(struct pidns *__restrict self, pid_t pid) THROWS(E_WOULDBLOCK, E_PROCESS_EXITED);

/* Return the taskpid object associated with `pid' within `self' */
FUNDEF NOBLOCK WUNUSED NONNULL((1)) struct taskpid *
NOTHROW(FCALL pidns_lookup_locked)(struct pidns const *__restrict self, pid_t pid);
FUNDEF NOBLOCK WUNUSED NONNULL((1)) REF struct task *
NOTHROW(FCALL pidns_lookuptask_locked)(struct pidns const *__restrict self, pid_t pid);

/* Return the taskpid object with the lowest PID (in `self'), that is still `>= min_pid'
 * This  function is  used for task  enumeration for things  such as `opendir("/proc")'. */
FUNDEF NOBLOCK WUNUSED NONNULL((1)) struct taskpid *
NOTHROW(FCALL pidns_lookupnext_locked)(struct pidns const *__restrict self, pid_t min_pid);


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
FUNDEF WUNUSED NOBLOCK NONNULL((1)) pid_t
NOTHROW(FCALL pidns_findpid)(struct pidns const *__restrict self,
                             pid_t minpid, pid_t maxpid);


DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_SCHED_PID_H */
