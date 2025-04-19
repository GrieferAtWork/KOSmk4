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
#ifndef GUARD_KERNEL_SRC_SCHED_PID_C
#define GUARD_KERNEL_SRC_SCHED_PID_C 1
#define __WANT_TASKPID__tp_nslop
#define __WANT_TASKPID__tp_grplop
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/malloc.h>
#include <sched/async.h>
#include <sched/group.h>
#include <sched/pertask.h>
#include <sched/pid.h>
#include <sched/rpc-internal.h>
#include <sched/sig.h>
#include <sched/task.h>
#include <sched/timer.h>

#include <hybrid/overflow.h>
#include <hybrid/sched/atomic-rwlock.h>
#include <hybrid/sequence/list.h>
#include <hybrid/sequence/rbtree.h>

#include <kos/aref.h>
#include <kos/except.h>
#include <kos/except/reason/inval.h>
#include <kos/lockop.h>
#include <kos/types.h>

#include <assert.h>
#include <atomic.h>
#include <signal.h>
#include <stddef.h>


DECL_BEGIN

struct _pidtree_slot {
	LLRBTREE_NODE_P(void) pts_link; /* [0..1][lock(:tp_ns->[pn_par...]->pn_lock)]
	                                 * Link entry within the associated PID namespace */
	upid_t                pts_pid;  /* [const] PID relevant to this slot. */
};
#define _pidtree_slotat(self, offsetof_slot) \
	((struct _pidtree_slot *)((byte_t *)(self) + (offsetof_slot)))

DECL_END

/* Define the ABI for accessing `struct pidns::pn_tree' */
#define RBTREE_LEFT_LEANING /* Use left-leaning trees */
#define RBTREE_WANT_MINMAXLOCATE
#define RBTREE_OMIT_REMOVENODE
#define RBTREE_NOTHROW      NOTHROW
#define RBTREE(name)        _pidns_tree_##name
#define RBTREE_SLOT__PARAMS , ptrdiff_t _offsetof_slot
#define RBTREE_SLOT__ARGS   , _offsetof_slot
#define RBTREE_T            void
#define RBTREE_Tkey         pid_t
#define RBTREE_GETNODE(x)   _pidtree_slotat(x, _offsetof_slot)->pts_link
#define RBTREE_GETKEY(x)    (pid_t)(_pidtree_slotat(x, _offsetof_slot)->pts_pid & _TASKPID_SLOT_PIDMASK)
#define RBTREE_ISRED(x)     (_pidtree_slotat(x, _offsetof_slot)->pts_pid & _TASKPID_SLOT_REDMASK)
#define RBTREE_SETRED(x)    (_pidtree_slotat(x, _offsetof_slot)->pts_pid |= _TASKPID_SLOT_REDMASK)
#define RBTREE_SETBLACK(x)  (_pidtree_slotat(x, _offsetof_slot)->pts_pid &= ~_TASKPID_SLOT_REDMASK)
#define RBTREE_FLIPCOLOR(x) (_pidtree_slotat(x, _offsetof_slot)->pts_pid ^= _TASKPID_SLOT_REDMASK)
#define RBTREE_COPYCOLOR(dst, src)                                               \
	(_pidtree_slotat(dst, _offsetof_slot)->pts_pid =                             \
	 (_pidtree_slotat(dst, _offsetof_slot)->pts_pid & ~_TASKPID_SLOT_REDMASK) | \
	 (_pidtree_slotat(src, _offsetof_slot)->pts_pid & _TASKPID_SLOT_REDMASK))
#include <hybrid/sequence/rbtree-abi.h>

#define _taskpid_offsetof_slot(ind) \
	(offsetof(struct taskpid, tp_pids) + (ind) * sizeof(struct taskpid_slot))
#define _procgrp_offsetof_slot(ind) \
	(offsetof(struct procgrp, pgr_pids) + (ind) * sizeof(struct procgrp_slot))

#define _taskpid_tree_minmaxlocate(root, minkey, maxkey, result, ind) _pidns_tree_minmaxlocate(root, minkey, maxkey, result, _taskpid_offsetof_slot(ind))
#define _procgrp_tree_minmaxlocate(root, minkey, maxkey, result, ind) _pidns_tree_minmaxlocate(root, minkey, maxkey, result, _procgrp_offsetof_slot(ind))
#define _taskpid_tree_locate(root, key, ind)                          ((struct taskpid *)_pidns_tree_locate(root, key, _taskpid_offsetof_slot(ind)))
#define _procgrp_tree_locate(root, key, ind)                          ((struct procgrp *)_pidns_tree_locate(root, key, _procgrp_offsetof_slot(ind)))
#define _taskpid_tree_remove(proot, key, ind)                         ((struct taskpid *)_pidns_tree_remove((void **)(proot), key, _taskpid_offsetof_slot(ind)))
#define _procgrp_tree_remove(proot, key, ind)                         ((struct procgrp *)_pidns_tree_remove((void **)(proot), key, _procgrp_offsetof_slot(ind)))
#define _taskpid_tree_insert(proot, node, ind)                        _pidns_tree_insert((void **)(proot), node, _taskpid_offsetof_slot(ind))
#define _procgrp_tree_insert(proot, node, ind)                        _pidns_tree_insert((void **)(proot), node, _procgrp_offsetof_slot(ind))

DECL_BEGIN

/* Assert binary compatibility between `struct _pidtree_slot' and `struct taskpid_slot' */
static_assert((offsetof(struct taskpid, tp_pids[1]) - offsetof(struct taskpid, tp_pids[0])) == sizeof(struct taskpid_slot));
static_assert(offsetof(struct _pidtree_slot, pts_link) == offsetof(struct taskpid_slot, tps_link));
static_assert(sizeof(((struct _pidtree_slot *)0)->pts_link) == sizeof(((struct taskpid_slot *)0)->tps_link));
static_assert(offsetof(struct _pidtree_slot, pts_pid) == offsetof(struct taskpid_slot, tps_pid));
static_assert(sizeof(((struct _pidtree_slot *)0)->pts_pid) == sizeof(((struct taskpid_slot *)0)->tps_pid));

/* Assert binary compatibility between `struct _pidtree_slot' and `struct procgrp_slot' */
static_assert((offsetof(struct procgrp, pgr_pids[1]) - offsetof(struct procgrp, pgr_pids[0])) == sizeof(struct procgrp_slot));
static_assert(offsetof(struct _pidtree_slot, pts_link) == offsetof(struct procgrp_slot, pgs_link));
static_assert(sizeof(((struct _pidtree_slot *)0)->pts_link) == sizeof(((struct procgrp_slot *)0)->pgs_link));
static_assert(offsetof(struct _pidtree_slot, pts_pid) == offsetof(struct procgrp_slot, pgs_pid));
static_assert(sizeof(((struct _pidtree_slot *)0)->pts_pid) == sizeof(((struct procgrp_slot *)0)->pgs_pid));


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

/* Remove `self' from all associated namespaces (and decref the  top-most
 * namespace), before using `_taskpid_free()' to free the taskpid object. */
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL taskpid_remove_from_namespaces_and_free)(struct taskpid *__restrict self);


PRIVATE NOBLOCK NONNULL((1, 2)) void
NOTHROW(LOCKOP_CC pidns_removepid_postlop)(Tobpostlockop(pidns) *__restrict self,
                                           struct pidns *__restrict obj) {
	struct taskpid *me;
	me = container_of(self, struct taskpid, _tp_nsplop);
	assert(me->tp_ns == obj);
	decref_nokill(obj); /* *_nokill, because caller is still holding a reference */
	me->tp_ns = obj->pn_par;
	if (me->tp_ns) {
		/* Keep removing `self' from recursive namespaces. */
		incref(me->tp_ns); /* Inherited by `taskpid_remove_from_namespaces_and_free' */
		taskpid_remove_from_namespaces_and_free(me);
	} else {
		/* Free the taskpid descriptor. */
		_taskpid_free(me);
	}
}

PRIVATE NOBLOCK NONNULL((1, 2)) Tobpostlockop(pidns) *
NOTHROW(LOCKOP_CC pidns_removepid_lop)(Toblockop(pidns) *__restrict self,
                                       struct pidns *__restrict obj) {
	struct taskpid *me;
	me = container_of(self, struct taskpid, _tp_nslop);
	assert(me->tp_ns == obj);

	/* Remove from the just-locked namespace. */
	taskpid_remove_from_ns(me, obj);

	/* Do the rest of the accounting work in a post-lockop */
	me->_tp_nsplop.oplo_func = &pidns_removepid_postlop;
	return &me->_tp_nsplop;
}


/* Remove `self' from all associated namespaces (and decref the  top-most
 * namespace), before using `_taskpid_free()' to free the taskpid object. */
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
		self->_tp_nslop.olo_func = &pidns_removepid_lop;
		incref(ns);
		oblockop_enqueue(&ns->pn_lops, &self->_tp_nslop);
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
	_taskpid_free(self);
}

PRIVATE NOBLOCK NONNULL((1, 2)) void
NOTHROW(LOCKOP_CC taskpid_remove_from_group_postlop)(Tobpostlockop(procgrp) *__restrict self,
                                                     struct procgrp *__restrict obj) {
	struct taskpid *me  = container_of(self, struct taskpid, _tp_grpplop);
	struct procctl *ctl = me->tp_pctl;
	assert(me->tp_proc == me);
	assert(arref_ptr(&ctl->pc_grp) == obj);
#if 0
	arref_fini(&ctl->pc_grp);
#else
	decref_nokill(obj); /* nokill, because caller still got a reference. */
#endif
	_procctl_finicommon(ctl);
	_procctl_free(ctl);
	taskpid_remove_from_namespaces_and_free(me);
}

PRIVATE NOBLOCK NONNULL((1, 2)) Tobpostlockop(procgrp) *
NOTHROW(LOCKOP_CC taskpid_remove_from_group_lop)(Toblockop(procgrp) *__restrict self,
                                                 struct procgrp *__restrict obj) {
	struct taskpid *me  = container_of(self, struct taskpid, _tp_grplop);
	struct procctl *ctl = me->tp_pctl;
	assert(obj == arref_ptr(&ctl->pc_grp));
	procgrp_memb_remove(obj, me);
	me->_tp_grpplop.oplo_func = &taskpid_remove_from_group_postlop;
	return &me->_tp_grpplop;
}


/* Destroy the given taskpid. */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL taskpid_destroy)(struct taskpid *__restrict self) {
	assertf(awref_ptr(&self->tp_thread) == NULL,
	        "If this wasn't the case, `FORTASK(tp_thread, this_taskpid)' "
	        "should have kept us alive!");
	sig_broadcast_for_fini(&self->tp_changed);
	assertf(!LIST_ISBOUND(self, tp_parsib),
	        "The parent-sibling link should have kept us alive");
	if (self->tp_proc == self) {
		struct procctl *ctl = self->tp_pctl;
		REF struct procgrp *grp;
		assertf(LIST_EMPTY(&ctl->pc_thrds_list), "Child threads should have kept us alive");
		assertf(LIST_EMPTY(&ctl->pc_chlds_list), "Child processes should have kept us alive");
		assertf(atomic_read(&ctl->pc_sig_list.slh_first) == THIS_RPCS_TERMINATED,
		        "This should have happened in `task_exit()'");
		assertf(atomic_read(&ctl->pc_sig_pend) & 1,
		        "This should have happened in `task_exit()'");
		sig_broadcast_for_fini(&ctl->pc_chld_changed);

		/* We know that we're no longer part of the parent's list of child
		 * processes, so there's  no need to  tinker around with  removing
		 * ourselves from said list. */
		arref_fini(&ctl->pc_parent);

		/* Clear `pc_sig_list' (handling remaining RPCs via SHUTDOWN) */
		sig_broadcast_for_fini(&ctl->pc_sig_more);

		/* Remove from `ctl->pc_grp->pgr_memb_list' (using lockops) */
		grp = arref_ptr(&ctl->pc_grp);
		if (procgrp_memb_trywrite(grp)) {
			assert(grp == arref_ptr(&ctl->pc_grp));
			procgrp_memb_remove(grp, self);
			procgrp_memb_endwrite(grp);
		} else {
			incref(grp);
			self->_tp_grplop.olo_func = &taskpid_remove_from_group_lop;
			oblockop_enqueue(&grp->pgr_memb_lops, &self->_tp_grplop);
			_procgrp_memb_reap(grp);
			decref_unlikely(grp);
			return;
		}
#if 0
		arref_fini(&ctl->pc_grp);
#else
		decref(grp);
#endif
		_procctl_finicommon(ctl);
		_procctl_free(ctl);
	} else {
		COMPILER_READ_BARRIER();
		decref_unlikely(self->tp_proc);
	}
	taskpid_remove_from_namespaces_and_free(self);
}




/* [1..1][const] The PID associated with the calling thread. */
PUBLIC ATTR_PERTASK ATTR_ALIGN(REF struct taskpid *) this_taskpid = NULL;

DEFINE_PERTASK_FINI(this_taskpid_fini);
PRIVATE ATTR_USED NOBLOCK NONNULL((1)) void
NOTHROW(KCALL this_taskpid_fini)(struct task *__restrict self) {
	REF struct taskpid *tpid = FORTASK(self, this_taskpid);
	assert(tpid && awref_ptr(&tpid->tp_thread) == self);
	awref_clear(&tpid->tp_thread);
	decref(tpid);
}


/* Same as `taskpid_gettask()', but throw an exception if the thread has exited. */
PUBLIC ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct task *FCALL
taskpid_gettask_srch(struct taskpid *__restrict self)
		THROWS(E_PROCESS_EXITED) {
	REF struct task *result;
	result = taskpid_gettask(self);
	/* Throw an exception if the thread already exited */
	if unlikely(!result)
		THROW(E_PROCESS_EXITED, taskpid_gettid_s(self));
	return result;
}






/************************************************************************/
/* TASK PID NAMESPACE                                                   */
/************************************************************************/
INTDEF struct taskpid boottask_pid;
INTDEF struct taskpid bootcpu_idle_pid;
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
function pidof(x) -> x is none ? "NULL" : x.val == "thiscpu_idle" ? "&bootcpu_idle_pid" : f"&{x.val}_pid";
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
	local prev, next = {
		"asyncwork"    : ("&boottask_procctl.pc_thrds_list.lh_first", "&bootcpu_idle_pid"),
		"thiscpu_idle" : ("&asyncwork_pid.tp_parsib.le_next", "NULL"),
	}.get(x.val, ("NULL", "NULL"))...;
	print("	.tp_proc   = &boottask_pid,");
	print("	.tp_pctl   = &boottask_procctl,");
	print("	.tp_parsib = { .le_next = ", next, ", .le_prev = ", prev, " },");
	print("	.tp_ns     = &pidns_root,");
	print("	.tp_pids   = {");
	print("		[0] = {");
	print("			.tps_link = { ", pidof(x.lhs), ", ", pidof(x.rhs), " },");
	print("			.tps_pid  = ", x.minkey),;
	if (x.isred)
		print(" | _TASKPID_SLOT_REDMASK"),;
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
	.tp_proc   = &boottask_pid,
	.tp_pctl   = &boottask_procctl,
	.tp_parsib = { .le_next = NULL, .le_prev = NULL },
	.tp_ns     = &pidns_root,
	.tp_pids   = {
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
	.tp_proc   = &boottask_pid,
	.tp_pctl   = &boottask_procctl,
	.tp_parsib = { .le_next = NULL, .le_prev = &asyncwork_pid.tp_parsib.le_next },
	.tp_ns     = &pidns_root,
	.tp_pids   = {
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
	.tp_proc   = &boottask_pid,
	.tp_pctl   = &boottask_procctl,
	.tp_parsib = { .le_next = &bootcpu_idle_pid, .le_prev = &boottask_procctl.pc_thrds_list.lh_first },
	.tp_ns     = &pidns_root,
	.tp_pids   = {
		[0] = {
			.tps_link = { NULL, NULL },
			.tps_pid  = 3,
		}
	}
};
#define STATIC_TASKPID_TREE_ROOT &bootcpu_idle_pid
/*[[[end]]]*/

/* `/proc/sys/kernel/pid_max': When `pn_nextpid' >= this
 * value, start recycling  PIDs. (in  [PID_MIN,PID_MAX]) */
PUBLIC pid_t pid_recycle_threshold = PID_RECYCLE_THRESHOLD_DEFAULT;

/* The root PID namespace. */
PUBLIC struct pidns pidns_root = {
	.pn_refcnt  = 5,    /* +1: pidns_root, +1: boottask_pid, +1: bootcpu_idle_pid, +1: asyncwork_pid, +1: boottask_procgrp.pgr_ns */
	.pn_ind     = 0,    /* Root namespace indirection */
	.pn_par     = NULL, /* Root namespace doesn't have a parent */
	.pn_size    = 3,    /* +1: boottask, +1: bootidle, +1: asyncwork */
	.pn_lock    = ATOMIC_RWLOCK_INIT,
	.pn_lops    = SLIST_HEAD_INITIALIZER(pidns_root.pn_lops),
	.pn_tree    = STATIC_TASKPID_TREE_ROOT,
	.pn_tree_pg = &boottask_procgrp, /* First and initial process group */
	.pn_npid    = 4, /* 1-3 are already in use */
	.pn_addproc = SIG_INIT,
	.pn_delproc = SIG_INIT,
};


/* Destroy a given PID namespace. */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL pidns_destroy)(struct pidns *__restrict self) {
	assert(self != &pidns_root);
	assert(self->pn_ind != 0);
	assert(self->pn_par != NULL);
	pidns_reap(self);
	assert(SLIST_EMPTY(&self->pn_lops));
	assertf(self->pn_tree == NULL, "Any taskpid should have kept us alive");
	assertf(self->pn_tree_pg == NULL, "Any procgrp should have kept us alive");
	assertf(self->pn_size == 0, "Then how come `pn_tree == NULL'?");
	sig_altbroadcast_for_fini_unlikely(&self->pn_addproc, PIDNS_PROCSIG_ENCODE(&boottask_pid));
	sig_altbroadcast_for_fini_unlikely(&self->pn_delproc, PIDNS_PROCSIG_ENCODE(&boottask_pid));
	decref_unlikely(self->pn_par);
	kfree(self);
}

/* Allocate a new child PID namespace for `parent' */
PUBLIC ATTR_RETNONNULL NONNULL((1)) REF struct pidns *FCALL
pidns_new(struct pidns *__restrict parent) THROWS(E_BADALLOC) {
	REF struct pidns *result;
	result = (REF struct pidns *)kmalloc(sizeof(struct pidns), GFP_NORMAL);
	result->pn_refcnt = 1;
	result->pn_ind    = parent->pn_ind + 1;
	result->pn_par    = incref(parent);
	atomic_rwlock_init(&result->pn_lock);
	SLIST_INIT(&result->pn_lops);
	result->pn_size = 0;
	result->pn_tree = NULL;
	result->pn_npid = PIDNS_FIRST_NONRESERVED_PID;
	sig_init(&result->pn_addproc);
	sig_init(&result->pn_delproc);
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
		THROWS(E_WOULDBLOCK, E_PROCESS_EXITED, E_INVALID_ARGUMENT_BAD_VALUE) {
	REF struct taskpid *result;
	pidns_read(self);
	result = pidns_lookup_locked(self, pid);
	if unlikely(!result || !tryincref(result)) {
		pidns_endread(self);
		if (pid < 0) {
			THROW(E_INVALID_ARGUMENT_BAD_VALUE,
			      E_INVALID_ARGUMENT_CONTEXT_BAD_PID,
			      pid);
		}
		THROW(E_PROCESS_EXITED, pid);
	} else {
		pidns_endread(self);
	}
	return result;
}

PUBLIC ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct task *FCALL
pidns_lookuptask_srch(struct pidns *__restrict self, pid_t pid)
		THROWS(E_WOULDBLOCK, E_PROCESS_EXITED, E_INVALID_ARGUMENT_BAD_VALUE) {
	REF struct task *result;
	REF struct taskpid *tpid;
	pidns_read(self);
	tpid = pidns_lookup_locked(self, pid);
	if unlikely(!tpid || !tryincref(tpid)) {
		pidns_endread(self);
		if (pid < 0) {
			THROW(E_INVALID_ARGUMENT_BAD_VALUE,
			      E_INVALID_ARGUMENT_CONTEXT_BAD_PID,
			      pid);
		}
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
PUBLIC NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) struct taskpid *
NOTHROW(FCALL pidns_lookup_locked)(struct pidns const *__restrict self, pid_t pid) {
	return _taskpid_tree_locate(self->pn_tree, pid, self->pn_ind);
}

PUBLIC NOBLOCK WUNUSED NONNULL((1)) REF struct task *
NOTHROW(FCALL pidns_lookuptask_locked)(struct pidns const *__restrict self, pid_t pid) {
	REF struct task *result;
	REF struct taskpid *tpid;
	tpid = _taskpid_tree_locate(self->pn_tree, pid, self->pn_ind);
	if (!tpid || !tryincref(tpid))
		return NULL;
	result = taskpid_gettask(tpid);
	decref_unlikely(tpid);
	return result;
}


/* Return the taskpid object with the lowest PID (in `self'), that is still `>= min_pid'
 * This  function is  used for task  enumeration for things  such as `opendir("/proc")'. */
PUBLIC NOBLOCK WUNUSED NONNULL((1)) REF struct taskpid *
NOTHROW(FCALL pidns_lookupnext_locked)(struct pidns const *__restrict self, pid_t min_pid) {
	REF struct taskpid *result;
	_pidns_tree_minmax_t mima;
again_locate:
	_taskpid_tree_minmaxlocate(self->pn_tree, min_pid, PID_MAX, &mima, self->pn_ind);
	result = (REF struct taskpid *)mima.mm_min;
	if (result && !tryincref(result)) {
		/* Dead PID -- Try find another find past this one. */
		if (!OVERFLOW_SADD(taskpid_getnstid(result, self), 1, &min_pid))
			goto again_locate;
		result = NULL;
	}
	return result;
}

/* Same as `pidns_lookupnext_locked()', but only enumerate actual processes (skip threads) */
PUBLIC NOBLOCK WUNUSED NONNULL((1)) REF struct taskpid *
NOTHROW(FCALL pidns_lookupnextproc_locked)(struct pidns const *__restrict self, pid_t min_pid) {
	REF struct taskpid *result;
	_pidns_tree_minmax_t mima;
again_locate:
	_taskpid_tree_minmaxlocate(self->pn_tree, min_pid, PID_MAX, &mima, self->pn_ind);
	result = (REF struct taskpid *)mima.mm_min;
	if (result && ((result->tp_proc != result) || !tryincref(result))) {
		/* Dead PID -- Try find another find past this one. */
		if (!OVERFLOW_SADD(taskpid_getnstid(result, self), 1, &min_pid))
			goto again_locate;
		result = NULL;
	}
	return result;
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
	_taskpid_tree_insert(&self->pn_tree, tpid, self->pn_ind);
	++self->pn_size;
	sig_altbroadcast(&self->pn_addproc, PIDNS_PROCSIG_ENCODE(tpid));
}

/* Do the reverse of `pidns_insertpid()' and remove the PID
 * descriptor associated with a given `pid' (which is  then
 * returned).  In this sense, this function behaves similar
 * to `pidns_lookup_locked', except that the taskpid object
 * is also removed from the tree.
 * When no taskpid is associated with `pid', return `NULL'. */
PUBLIC NOBLOCK NONNULL((1)) struct taskpid *
NOTHROW(FCALL pidns_removepid)(struct pidns *__restrict self, pid_t pid) {
	struct taskpid *result;
	result = _taskpid_tree_remove(&self->pn_tree, pid, self->pn_ind);
	if (result != NULL) {
		--self->pn_size;
		sig_altbroadcast(&self->pn_delproc, PIDNS_PROCSIG_ENCODE(result));
	}
	return result;
}


/* Find the first (lowest) unused  pid that is in  [minpid,maxpid]
 * If no such pid exists (or when `minpid > maxpid'), return `-1'. */
PUBLIC NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) pid_t
NOTHROW(FCALL pidns_findpid)(struct pidns const *__restrict self,
                             pid_t minpid, pid_t maxpid) {
	if (minpid <= maxpid) {
		for (;;) {
			/* PIDs cannot be re-used if there is EITHER a process
			 * with that  ID, or  a process  group with  that  ID!
			 * -> s.a. posix -- "4.13 Process ID Reuse" */
			if (_taskpid_tree_locate(self->pn_tree, minpid, self->pn_ind) == NULL &&
			    _procgrp_tree_locate(self->pn_tree_pg, minpid, self->pn_ind) == NULL)
				return minpid;
			if (minpid >= maxpid)
				break;
			++minpid;
		}
	}
	return -1;
}

/* Return the next free PID  to-be assigned to a new  thread/process
 * In the (highly unlikely) even that all PIDs are in use, and  none
 * can be reclaimed (iow: `self' contains 2^31 threads), return `-1'
 * instead.
 *
 * Allocation  of a PID  is done by use  of `pidns_insertpid', but in
 * addition to this, the  caller must also increment  `self->pn_npid'
 * to `return + 1' once  they inserted the  PID into this  namespace!
 * This only happens when `#ifdef PIDNS_NEXTPID_CAN_RETURN_MINUS_ONE' */
PUBLIC NOBLOCK WUNUSED NONNULL((1)) pid_t
NOTHROW(FCALL pidns_nextpid)(struct pidns const *__restrict self) {
	pid_t recycle = atomic_read(&pid_recycle_threshold);
	pid_t result;

	/* Find  the next free PID between the next to-be used, and
	 * the threshold going from which we're supposed to recycle
	 * old PIDs. */
	result = pidns_findpid(self, self->pn_npid, recycle);
	if likely(result != -1)
		goto done;

	/* Try to recycle PIDs by searching for a free slot in the
	 * range  preceding   that   which   we   just   searched. */
	result = pidns_findpid(self, PIDNS_FIRST_NONRESERVED_PID, self->pn_npid - 1);
	if likely(result != -1)
		goto done;

	/* If we get here, that means there are at least `recycle'
	 * threads living within our PID namespace. In this  case,
	 * we're allowed to hand out PIDs beyond the threshold  at
	 * which PIDs are recycled. */
	result = pidns_findpid(self, recycle + 1, PID_MAX);

	/* If `result' still `== -1' at this point (extremely unlikely),
	 * then there are 2^31 threads living without our namespace.  In
	 * this case, our caller will */
#ifndef PIDNS_NEXTPID_CAN_RETURN_MINUS_ONE
	assertf(result != -1, "Given pointer size restrictions, it should "
	                      "be physically impossible to allocate 2^31 of "
	                      "something as large as `struct taskpid'. So "
	                      "how can it be that _all_ PIDs are allocated?");
#endif /* !PIDNS_NEXTPID_CAN_RETURN_MINUS_ONE */

done:
	return result;
}

/* Allocate+assign PIDs of `self' in all of its namespaces.
 * @return: true:  Success.
 * @return: false: Failed to allocate a PID in at least one namespace. */
#ifdef PIDNS_NEXTPID_CAN_RETURN_MINUS_ONE
PUBLIC NOBLOCK WUNUSED NONNULL((1)) bool
NOTHROW(FCALL pidns_allocpids)(struct taskpid *__restrict self)
#else /* PIDNS_NEXTPID_CAN_RETURN_MINUS_ONE */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL pidns_allocpids)(struct taskpid *__restrict self)
#endif /* !PIDNS_NEXTPID_CAN_RETURN_MINUS_ONE */
{
	struct pidns *ns_iter = self->tp_ns;
	do {
		pid_t rpid = pidns_nextpid(ns_iter);
#ifdef PIDNS_NEXTPID_CAN_RETURN_MINUS_ONE
		if unlikely(rpid == -1)
			return false;
#endif /* PIDNS_NEXTPID_CAN_RETURN_MINUS_ONE */
		self->tp_pids[ns_iter->pn_ind].tps_pid = rpid;
		if (OVERFLOW_SADD(rpid, 1, &ns_iter->pn_npid))
			ns_iter->pn_npid = PIDNS_FIRST_NONRESERVED_PID;
	} while ((ns_iter = ns_iter->pn_par) != NULL);
#ifdef PIDNS_NEXTPID_CAN_RETURN_MINUS_ONE
	return true;
#endif /* PIDNS_NEXTPID_CAN_RETURN_MINUS_ONE */
}



/* Return the process group associated with `pgid' within `self' */
PUBLIC WUNUSED NONNULL((1)) REF struct procgrp *FCALL
pidns_grplookup(struct pidns *__restrict self, pid_t pgid)
		THROWS(E_WOULDBLOCK) {
	REF struct procgrp *result;
	pidns_read(self);
	result = _procgrp_tree_locate(self->pn_tree_pg, pgid, self->pn_ind);
	if (result && !tryincref(result))
		result = NULL;
	pidns_endread(self);
	return result;
}

PUBLIC WUNUSED NONNULL((1)) REF struct procgrp *FCALL
pidns_grplookup_srch(struct pidns *__restrict self, pid_t pgid)
		THROWS(E_WOULDBLOCK, E_PROCESS_GROUP_EXITED, E_INVALID_ARGUMENT_BAD_VALUE) {
	REF struct procgrp *result;
	pidns_read(self);
	result = _procgrp_tree_locate(self->pn_tree_pg, pgid, self->pn_ind);
	if (!result || !tryincref(result)) {
		pidns_endread(self);
		if (pgid < 0) {
			THROW(E_INVALID_ARGUMENT_BAD_VALUE,
			      E_INVALID_ARGUMENT_CONTEXT_BAD_PGID,
			      pgid);
		}
		THROW(E_PROCESS_GROUP_EXITED, pgid);
	} else {
		pidns_endread(self);
	}
	return result;
}


PUBLIC NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) struct procgrp *
NOTHROW(FCALL pidns_grplookup_locked)(struct pidns const *__restrict self, pid_t pgid) {
	return _procgrp_tree_locate(self->pn_tree_pg, pgid, self->pn_ind);
}

/* Insert/Remove a process group to/from the given namespace. */
PUBLIC NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL pidns_grpinsert)(struct pidns *__restrict self,
                               struct procgrp *__restrict grp) {
	_procgrp_tree_insert(&self->pn_tree_pg, grp, self->pn_ind);
}

PUBLIC NOBLOCK NONNULL((1)) struct procgrp *
NOTHROW(FCALL pidns_grpremove)(struct pidns *__restrict self, pid_t pgid) {
	return _procgrp_tree_remove(&self->pn_tree_pg, pgid, self->pn_ind);
}


DECL_END

#endif /* !GUARD_KERNEL_SRC_SCHED_PID_C */
