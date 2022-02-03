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
#ifndef GUARD_KERNEL_SRC_SCHED_PID_C
#define GUARD_KERNEL_SRC_SCHED_PID_C 1
#define __WANT_TASKPID__tp_lop
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/malloc.h>
#include <sched/async.h>
#include <sched/pid.h>
#include <sched/task.h>

#include <kos/except.h>

#include <assert.h>
#include <signal.h>
#include <stddef.h>


/* Define the ABI for accessing `struct pidns::pn_tree' */
#define RBTREE_LEFT_LEANING /* Use left-leaning trees */
#define RBTREE_WANT_MINMAXLOCATE
#define RBTREE_NOTHROW      NOTHROW
#define RBTREE(name)        _pidns_tree_##name
#define RBTREE_SLOT__PARAMS , size_t _ns_ind
#define RBTREE_SLOT__ARGS   , _ns_ind
#define RBTREE_T            struct taskpid
#define RBTREE_Tkey         pid_t
#define RBTREE_NODEPATH     tp_pids[_ns_ind].tps_link
#define RBTREE_GETKEY(x)    _taskpid_slot_getpidno((x)->tp_pids[_ns_ind])
#define RBTREE_ISRED(x)     ((x)->tp_pids[_ns_ind].tps_pid & __TASKPID_SLOT_REDMASK)
#define RBTREE_SETRED(x)    ((x)->tp_pids[_ns_ind].tps_pid |= __TASKPID_SLOT_REDMASK)
#define RBTREE_SETBLACK(x)  ((x)->tp_pids[_ns_ind].tps_pid &= ~__TASKPID_SLOT_REDMASK)
#define RBTREE_FLIPCOLOR(x) ((x)->tp_pids[_ns_ind].tps_pid ^= __TASKPID_SLOT_REDMASK)
#define RBTREE_COPYCOLOR(dst, src)                                                                   \
	((dst)->tp_pids[_ns_ind].tps_pid = ((dst)->tp_pids[_ns_ind].tps_pid & ~__TASKPID_SLOT_REDMASK) | \
	                                   ((src)->tp_pids[_ns_ind].tps_pid & __TASKPID_SLOT_REDMASK))
#include <hybrid/sequence/rbtree-abi.h>

DECL_BEGIN


/************************************************************************/
/* TASK PID OBJECT                                                      */
/************************************************************************/

PRIVATE NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL taskpid_remove_from_ns)(struct taskpid *__restrict self,
                                      struct pidns *__restrict ns) {
	struct taskpid *removed;
	pid_t nspid;
	nspid   = _taskpid_slot_getpidno(self->tp_pids[ns->pn_ind]);
	removed = pidns_removepid(ns, nspid);
	assertf(removed == self,
	        "Wrong taskpid removed from %p:\n"
	        "removed = %p\n"
	        "self    = %p\n",
	        ns, removed, self);
	(void)removed;
}

/* Remove `self' from all associated namespaces (and decref the top-most
 * namespace), before using `taskpid_free()' to free the taskpid object. */
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL taskpid_remove_from_namespaces_and_free)(struct taskpid *__restrict self);


PRIVATE NOBLOCK NONNULL((1, 2)) void
NOTHROW(LOCKOP_CC pidns_removepid_postlop)(Tobpostlockop(pidns) *__restrict self,
                                           struct pidns *__restrict obj) {
	struct taskpid *me;
	me = container_of(self, struct taskpid, _tp_plop);
	assert(me->tp_ns == obj);
	decref_nokill(obj); /* *_nokill, because caller is still holding a reference */
	me->tp_ns = obj->pn_par;
	if (me->tp_ns) {
		/* Keep removing `self' from recursive namespaces. */
		incref(me->tp_ns); /* Inherited by `taskpid_remove_from_namespaces_and_free' */
		taskpid_remove_from_namespaces_and_free(me);
	} else {
		/* Free the taskpid descriptor. */
		taskpid_free(self);
	}
}

PRIVATE NOBLOCK NONNULL((1, 2)) Tobpostlockop(pidns) *
NOTHROW(LOCKOP_CC pidns_removepid_lop)(Toblockop(pidns) *__restrict self,
                                       struct pidns *__restrict obj) {
	struct taskpid *me;
	me = container_of(self, struct taskpid, _tp_lop);
	assert(me->tp_ns == obj);

	/* Remove from the just-locked namespace. */
	taskpid_remove_from_ns(me, obj);

	/* Do the rest of the accounting work in a post-lockop */
	me->_tp_plop.oplo_func = &pidns_removepid_postlop;
	return &me->_tp_plop;
}


/* Remove `self' from all associated namespaces (and decref the top-most
 * namespace), before using `taskpid_free()' to free the taskpid object. */
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL taskpid_remove_from_namespaces_and_free)(struct taskpid *__restrict self) {
	struct pidns *par, *ns;
	/* Remove this taskpid from its pidns, if necessary via lockops */
	ns = self->tp_ns;
	assert(ns);
again_lock_ns:
	if (pidns_trywrite(ns)) {
		taskpid_remove_from_ns(self, ns);
		pidns_endwrite(ns);
	} else {
		/* Must use a lock-op */
		self->_tp_lop.olo_func = &pidns_removepid_lop;
		incref(ns);
		oblockop_enqueue(&ns->pn_lops, &self->_tp_lop);
		_pidns_reap(ns);
		decref_unlikely(ns);
		return;
	}
	par = ns->pn_par;
	xincref(par);
	decref_unlikely(ns);

	/* Recursively remove from parenting namespaces. */
	if unlikely(par) {
		self->tp_ns = ns = par;
		goto again_lock_ns;
	}

	/* Free the taskpid descriptor. */
	taskpid_free(self);
}

/* Destroy the given taskpid. */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL taskpid_destroy)(struct taskpid *__restrict self) {
	assertf(awref_ptr(&self->tp_thread) == NULL,
	        "If this wasn't the case, `FORTASK(tp_thread, this_taskpid)' "
	        "should have kept us alive!");
	sig_broadcast_for_fini(&self->tp_changed);
	taskpid_remove_from_namespaces_and_free(self);
}




/* [1..1][const] The PID associated with the calling thread. */
PUBLIC ATTR_PERTASK struct taskpid *this_taskpid = NULL;

/* Same as `taskpid_gettask()', but throw an exception if the thread has exited. */
PUBLIC ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct task *FCALL
taskpid_gettask_srch(struct taskpid *__restrict self)
		THROWS(E_PROCESS_EXITED) {
	REF struct task *result;
	result = taskpid_gettask(self);
	/* Throw an exception if the thread already exited */
	if unlikely(!result)
		THROW(E_PROCESS_EXITED, taskpid_getpidno(self));
	return result;
}






/************************************************************************/
/* TASK PID NAMESPACE                                                   */
/************************************************************************/
INTDEF struct taskpid boottask_pid;
INTDEF struct taskpid bootidle_pid;
INTDEF struct taskpid asyncwork_pid;

/*[[[deemon
import * from deemon;
import llrbtree = .....misc.libgen.llrbtree;
local nodes = {
	llrbtree.RbNode(minkey: 1, maxkey: 1, val: "boottask"),
	llrbtree.RbNode(minkey: 2, maxkey: 2, val: "thiscpu_idle"),
	llrbtree.RbNode(minkey: 3, maxkey: 3, val: "asyncwork"),
};
local staticPidTree = Cell(none);
for (local x: nodes)
	llrbtree.insert(staticPidTree, x);
function pidof(x) -> x is none ? "NULL" : x.val == "thiscpu_idle" ? "&bootidle_pid" : "&{}_pid".format({ x.val });
for (local x: nodes) {
	print("INTERN ", (x.val == "thiscpu_idle" ? "ATTR_PERCPU " : ""), "struct taskpid ", x.val, "_pid = {");
	print("	.tp_refcnt = 2, /" "* +1: ", x.val, "_pid, +1: FORTASK(", x.val, ", this_taskpid) *" "/");
	print("	{{");
	print("		.tp_thread  = AWREF_INIT(&", x.val == "thiscpu_idle" ? "bootidle" : x.val, "),");
	print("		.tp_changed = SIG_INIT,");
	print("		.tp_status  = 0,");
	print("		.tp_SIGCLD  = SIGCLD,");
	print("		._tp_pad    = {}");
	print("	}},");
	print("	.tp_sib  = LIST_ENTRY_UNBOUND_INITIALIZER,");
	print("	.tp_ns   = &pidns_root,");
	print("	.tp_pids = {");
	print("		[0] = {");
	print("			.tps_link = { ", pidof(x.lhs), ", ", pidof(x.rhs), " },");
	print("			.tps_pid  = ", x.minkey),;
	if (x.isred)
		print(" | __TASKPID_SLOT_REDMASK"),;
	print(",");
	print("		}");
	print("	}");
	print("};");
}
print("#define STATIC_TASKPID_TREE_ROOT ", pidof(staticPidTree.value));
]]]*/
INTERN struct taskpid boottask_pid = {
	.tp_refcnt = 2, /* +1: boottask_pid, +1: FORTASK(boottask, this_taskpid) */
	{{
		.tp_thread  = AWREF_INIT(&boottask),
		.tp_changed = SIG_INIT,
		.tp_status  = 0,
		.tp_SIGCLD  = SIGCLD,
		._tp_pad    = {}
	}},
	.tp_sib  = LIST_ENTRY_UNBOUND_INITIALIZER,
	.tp_ns   = &pidns_root,
	.tp_pids = {
		[0] = {
			.tps_link = { NULL, NULL },
			.tps_pid  = 1,
		}
	}
};
INTERN ATTR_PERCPU struct taskpid thiscpu_idle_pid = {
	.tp_refcnt = 2, /* +1: thiscpu_idle_pid, +1: FORTASK(thiscpu_idle, this_taskpid) */
	{{
		.tp_thread  = AWREF_INIT(&bootidle),
		.tp_changed = SIG_INIT,
		.tp_status  = 0,
		.tp_SIGCLD  = SIGCLD,
		._tp_pad    = {}
	}},
	.tp_sib  = LIST_ENTRY_UNBOUND_INITIALIZER,
	.tp_ns   = &pidns_root,
	.tp_pids = {
		[0] = {
			.tps_link = { &boottask_pid, &asyncwork_pid },
			.tps_pid  = 2,
		}
	}
};
INTERN struct taskpid asyncwork_pid = {
	.tp_refcnt = 2, /* +1: asyncwork_pid, +1: FORTASK(asyncwork, this_taskpid) */
	{{
		.tp_thread  = AWREF_INIT(&asyncwork),
		.tp_changed = SIG_INIT,
		.tp_status  = 0,
		.tp_SIGCLD  = SIGCLD,
		._tp_pad    = {}
	}},
	.tp_sib  = LIST_ENTRY_UNBOUND_INITIALIZER,
	.tp_ns   = &pidns_root,
	.tp_pids = {
		[0] = {
			.tps_link = { NULL, NULL },
			.tps_pid  = 3,
		}
	}
};
#define STATIC_TASKPID_TREE_ROOT &bootidle_pid
/*[[[end]]]*/

/* `/proc/sys/kernel/pid_max': When `pn_nextpid' >= this
 * value, start recycling  PIDs. (in  [PID_MIN,PID_MAX]) */
PUBLIC pid_t pid_recycle_threshold = PID_RECYCLE_THRESHOLD_DEFAULT;

/* The root PID namespace. */
PUBLIC struct pidns pidns_root = {
	.pn_refcnt = 4,    /* +1: pidns_root, +1: boottask_pid, +1: bootidle_pid, +1: asyncwork_pid */
	.pn_ind    = 0,    /* Root namespace indirection */
	.pn_par    = NULL, /* Root namespace doesn't have a parent */
	.pn_lock   = ATOMIC_RWLOCK_INIT,
	.pn_lops   = SLIST_HEAD_INITIALIZER(pidns_root.pn_lops),
	.pn_tree   = STATIC_TASKPID_TREE_ROOT,
	.pn_npid   = 4, /* 1-3 are already in use */
};


/* Destroy a given PID namespace. */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL pidns_destroy)(struct pidns *__restrict self) {
	assert(self != &pidns_root);
	assert(self->pn_ind != 0);
	assert(self->pn_par != NULL);
	assertf(self->pn_tree == NULL, "Any taskpid should have kept us alive");
	assert(SLIST_EMPTY(&self->pn_lops));
	decref_unlikely(self->pn_par);
	kfree(self);
}

/* Allocate a new child PID namespace for `parent' */
PUBLIC ATTR_RETNONNULL NONNULL((1)) REF struct pidns *FCALL
pidns_alloc(struct pidns *__restrict parent) THROWS(E_BADALLOC) {
	REF struct pidns *result;
	result = (REF struct pidns *)kmalloc(sizeof(struct pidns), GFP_NORMAL);
	result->pn_refcnt = 1;
	result->pn_ind    = parent->pn_ind + 1;
	result->pn_par    = incref(parent);
	atomic_rwlock_init(&result->pn_lock);
	SLIST_INIT(&result->pn_lops);
	result->pn_tree = NULL;
	result->pn_npid = PIDNS_FIRST_NONRESERVED_PID;
	return result;
}

/* Lookup a thread in a given PID namespace. */
PUBLIC WUNUSED NONNULL((1)) REF struct taskpid *FCALL
pidns_lookup(struct pidns *__restrict self, pid_t pid)
		THROWS(E_WOULDBLOCK) {
	REF struct taskpid *result;
	pidns_read(self);
	result = pidns_lookup_locked(self, pid);
	if (result && !tryincref(result))
		result = NULL;
	pidns_endread(self);
	return result;
}

PUBLIC WUNUSED NONNULL((1)) REF struct task *FCALL
pidns_lookuptask(struct pidns *__restrict self, pid_t pid)
		THROWS(E_WOULDBLOCK) {
	REF struct task *result;
	REF struct taskpid *tpid;
	tpid = pidns_lookup(self, pid);
	if (!tpid)
		return NULL;
	result = taskpid_gettask(tpid);
	decref_unlikely(tpid);
	return result;
}

PUBLIC ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct taskpid *FCALL
pidns_lookup_srch(struct pidns *__restrict self, pid_t pid)
		THROWS(E_WOULDBLOCK, E_PROCESS_EXITED) {
	REF struct taskpid *result;
	pidns_read(self);
	result = pidns_lookup_locked(self, pid);
	if unlikely(!result || !tryincref(result)) {
		pidns_endread(self);
		THROW(E_PROCESS_EXITED, pid);
	}
	pidns_endread(self);
	return result;
}

PUBLIC ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct task *FCALL
pidns_lookuptask_srch(struct pidns *__restrict self, pid_t pid)
		THROWS(E_WOULDBLOCK, E_PROCESS_EXITED) {
	REF struct task *result;
	REF struct taskpid *tpid;
	pidns_read(self);
	tpid = pidns_lookup_locked(self, pid);
	if unlikely(!tpid || !tryincref(tpid)) {
		pidns_endread(self);
		goto throw_exited;
	}
	pidns_endread(self);
	result = taskpid_gettask(tpid);
	decref_unlikely(tpid);
	if unlikely(!result)
		goto throw_exited;
	return result;
throw_exited:
	THROW(E_PROCESS_EXITED, pid);
}


/* Return the taskpid object associated with `pid' within `self' */
PUBLIC NOBLOCK WUNUSED NONNULL((1)) struct taskpid *
NOTHROW(FCALL pidns_lookup_locked)(struct pidns const *__restrict self, pid_t pid) {
	return _pidns_tree_locate(self->pn_tree, pid, self->pn_ind);
}

PUBLIC NOBLOCK WUNUSED NONNULL((1)) REF struct task *
NOTHROW(FCALL pidns_lookuptask_locked)(struct pidns const *__restrict self, pid_t pid) {
	REF struct task *result;
	REF struct taskpid *tpid;
	tpid = _pidns_tree_locate(self->pn_tree, pid, self->pn_ind);
	if (!tpid || !tryincref(tpid))
		return NULL;
	result = taskpid_gettask(tpid);
	decref_unlikely(tpid);
	return result;
}


/* Return the taskpid object with the lowest PID (in `self'), that is still `>= min_pid'
 * This  function is  used for task  enumeration for things  such as `opendir("/proc")'. */
PUBLIC NOBLOCK WUNUSED NONNULL((1)) struct taskpid *
NOTHROW(FCALL pidns_lookupnext_locked)(struct pidns const *__restrict self, pid_t min_pid) {
	_pidns_tree_minmax_t mima;
	_pidns_tree_minmaxlocate(self->pn_tree, min_pid, PID_MAX, &mima, self->pn_ind);
	return mima.mm_min;
}


/* Try to acquire write-locks to all PID namespaces reachable from `self'
 * Upon success, return `NULL'; else: return the blocking PID  namespace.
 * @return: NULL: Success
 * @return: * :   The blocking PID namespace. */
PUBLIC NOBLOCK WUNUSED NONNULL((1)) struct pidns *
NOTHROW(FCALL pidns_trywriteall)(struct pidns *__restrict self) {
	struct pidns *iter = self;
	do {
		if (!pidns_trywrite(iter)) {
			struct pidns *iter2;
			/* Release all previously acquired locks. */
			for (iter2 = self; iter2 != iter; iter2 = iter2->pn_par)
				_pidns_endwrite(iter2);
			for (iter2 = self; iter2 != iter; iter2 = iter2->pn_par)
				pidns_reap(iter2);
			return iter;
		}
	} while ((iter = iter->pn_par) != NULL);
	return NULL;
}

/* Release write-locks from all PID namespaces reachable from `self' */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL pidns_endwriteall)(struct pidns *__restrict self) {
	struct pidns *iter;
	iter = self;
	do {
		_pidns_endwrite(iter);
	} while ((iter = iter->pn_par) != NULL);
	iter = self;
	do {
		pidns_reap(iter);
	} while ((iter = iter->pn_par) != NULL);
}

/* Insert a given `tpid' into the tree of `self'.
 * The caller is responsible to:
 *  - Assign `tpid->tp_pids[self->pn_ind].tps_pid'
 *  - Ensure that `pidns_lookup_locked(self, tpid->tp_pids[self->pn_ind].tps_pid) == NULL'
 *  - Be holding a lock to `self->pn_lock'
 * This function is only responsible for doing the actual
 * inserting of `tpid' into the LLRB-tree of `self',  and
 * it's  the caller's responsibility to ensure that doing
 * so actually makes sense! */
PUBLIC NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL pidns_insertpid)(struct pidns *__restrict self,
                               struct taskpid *__restrict tpid) {
	_pidns_tree_insert(&self->pn_tree, tpid, self->pn_ind);
}

/* Do the reverse of `pidns_insertpid()' and remove the PID
 * descriptor associated with a given `pid' (which is  then
 * returned).  In this sense, this function behaves similar
 * to `pidns_lookup_locked', except that the taskpid object
 * is also removed from the tree.
 * When no taskpid is associated with `pid', return `NULL'. */
PUBLIC NOBLOCK NONNULL((1)) struct taskpid *
NOTHROW(FCALL pidns_removepid)(struct pidns *__restrict self, pid_t pid) {
	return _pidns_tree_remove(&self->pn_tree, pid, self->pn_ind);
}


/* Find the first (lowest) unused  pid that is in  [minpid,maxpid]
 * If no such pid exists (or when `minpid > maxpid'), return `-1'. */
PUBLIC WUNUSED NOBLOCK NONNULL((1)) pid_t
NOTHROW(FCALL pidns_findpid)(struct pidns const *__restrict self,
                             pid_t minpid, pid_t maxpid) {
	if (minpid <= maxpid) {
		for (;;) {
			if (_pidns_tree_locate(self->pn_tree, minpid, self->pn_ind) == NULL)
				return minpid;
			if (minpid >= maxpid)
				break;
			++minpid;
		}
	}
	return -1;
}

DECL_END

#endif /* !GUARD_KERNEL_SRC_SCHED_PID_C */
