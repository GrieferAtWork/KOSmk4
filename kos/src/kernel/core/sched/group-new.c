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
#ifndef GUARD_KERNEL_SRC_SCHED_GROUP_NEW_C
#define GUARD_KERNEL_SRC_SCHED_GROUP_NEW_C 1
#define __WANT_PROCGRP__pgr_lop
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#ifdef CONFIG_USE_NEW_GROUP
#include <dev/tty.h>
#include <kernel/malloc.h>
#include <sched/group-new.h>
#include <sched/pid.h>
#include <sched/task.h>

#include <assert.h>
#include <stddef.h>

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
NOTHROW(LOCKOP_CC pidns_removepid_postlop)(Tobpostlockop(pidns) *__restrict self,
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
		_procgrp_free(self);
	}
}

PRIVATE NOBLOCK NONNULL((1, 2)) Tobpostlockop(pidns) *
NOTHROW(LOCKOP_CC pidns_removepid_lop)(Toblockop(pidns) *__restrict self,
                                       struct pidns *__restrict obj) {
	struct procgrp *me;
	me = container_of(self, struct procgrp, _pgr_lop);
	assert(me->pgr_ns == obj);

	/* Remove from the just-locked namespace. */
	procgrp_remove_from_ns(me, obj);

	/* Do the rest of the accounting work in a post-lockop */
	me->_pgr_plop.oplo_func = &pidns_removepid_postlop;
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
		self->_pgr_lop.olo_func = &pidns_removepid_lop;
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
	.pc_chlds_lock = ATOMIC_RWLOCK_INIT,
	/* s.a. the static initializer of `asyncwork_pid', which is statically
	 *      set-up to behave  like the  first element of  this very  list! */
	.pc_chlds_list   = { &asyncwork_pid },
	.pc_chld_changed = SIG_INIT,
	/* Even though it doesn't ~really~ make sense, /bin/init is set-up to
	 * behave as its own parent process. Because the parent field must always
	 * be non-NULL, we have to fill in ~something~, and since /bin/init can't
	 * ever die (TASK_FCRITICAL), its parent never ~really~ becomes relevant
	 * either. -- But note however that if /bin/init were to call getppid(),
	 * it would get back its own PID! */
	.pc_parent    = ARREF_INIT(&boottask),
	.pc_sig_lock  = ATOMIC_RWLOCK_INIT,
	.pc_sig_list  = SLIST_HEAD_INITIALIZER(boottask_procctl.pc_sig_list),
	.pc_sig_more  = SIG_INIT,
	.pc_grp       = ARREF_INIT(&boottask_procgrp),
	.pc_grpmember = { .le_next = NULL, .le_prev = &boottask_procgrp.pgr_memb_list.lh_first },

};



DECL_END
#endif /* CONFIG_USE_NEW_GROUP */

#endif /* !GUARD_KERNEL_SRC_SCHED_GROUP_NEW_C */
