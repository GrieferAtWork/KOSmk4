/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_SRC_SCHED_EPOLL_C
#define GUARD_KERNEL_SRC_SCHED_EPOLL_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/except.h>
#include <kernel/handle-proto.h>
#include <kernel/handle.h>
#include <kernel/malloc.h>
#include <kernel/personality.h>
#include <kernel/syscall.h>
#include <kernel/types.h>
#include <kernel/user.h>
#include <sched/epoll.h>
#include <sched/signal-completion.h>
#include <sched/signal.h>
#include <sched/tsc.h>

#include <hybrid/atomic.h>

#include <kos/except/reason/inval.h>
#include <kos/io.h>
#include <sys/epoll.h>
#include <sys/poll.h>

#include <assert.h>
#include <errno.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

DECL_BEGIN

#ifndef NDEBUG
#define DBG_memset(dst, byte, num_bytes) memset(dst, byte, num_bytes)
#else /* !NDEBUG */
#define DBG_memset(dst, byte, num_bytes) (void)0
#endif /* NDEBUG */

/* Mask of events which can be polled using epoll */
#define EPOLL_WHATMASK                                           \
	(EPOLLIN | EPOLLPRI | EPOLLOUT | EPOLLRDNORM | EPOLLRDBAND | \
	 EPOLLWRNORM | EPOLLWRBAND | EPOLLRDHUP | EPOLLERR | EPOLLHUP)


/* Make sure that the EPOLL* constants are identical to the regular POLL* constants. */
STATIC_ASSERT(EPOLLIN == POLLIN);
STATIC_ASSERT(EPOLLPRI == POLLPRI);
STATIC_ASSERT(EPOLLOUT == POLLOUT);
STATIC_ASSERT(EPOLLRDNORM == POLLRDNORM);
STATIC_ASSERT(EPOLLRDBAND == POLLRDBAND);
STATIC_ASSERT(EPOLLWRNORM == POLLWRNORM);
STATIC_ASSERT(EPOLLWRBAND == POLLWRBAND);
STATIC_ASSERT(EPOLLRDHUP == POLLRDHUP);
STATIC_ASSERT(EPOLLERR == POLLERR);
STATIC_ASSERT(EPOLLHUP == POLLHUP);

/* Handle integration for `struct epoll_controller' */
DEFINE_HANDLE_REFCNT_FUNCTIONS_WITH_WEAKREF_SUPPORT(epoll, struct epoll_controller);


/************************************************************************/
/* Allow EPOLL controllers to be polled themself, in which case they will
 * indicate readable once there are pending events. */
INTERN NONNULL((1)) void KCALL
handle_epoll_pollconnect(struct epoll_controller *__restrict self,
                         poll_mode_t what) THROWS(...) {
	if (what & POLLINMASK)
		epoll_controller_pollconnect(self);
}

INTERN WUNUSED NONNULL((1)) poll_mode_t KCALL
handle_epoll_polltest(struct epoll_controller *__restrict self,
                      poll_mode_t what) THROWS(...) {
	if ((what & POLLINMASK) && epoll_controller_canwait(self))
		return POLLINMASK;
	return 0;
}
/************************************************************************/







/************************************************************************/
/* Low-level epoll signal completion function                           */

/* Add the given `monitor' to the chain of raised monitors of `self' */
PRIVATE NOBLOCK NOPREEMPT NONNULL((1, 2)) void
NOTHROW(FCALL epoll_controller_add_to_raised)(struct epoll_controller *__restrict self,
                                              struct epoll_handle_monitor *__restrict monitor) {
	struct epoll_handle_monitor *rnext;
	do {
		rnext = ATOMIC_READ(self->ec_raised);
		monitor->ehm_rnext = rnext;
		COMPILER_WRITE_BARRIER();
	} while (!ATOMIC_CMPXCH_WEAK(self->ec_raised,
	                             rnext, monitor));
}


/* Remove the given `monitor' from the raised-queue of `self'
 * The caller must be holding the lock of `self' */
PRIVATE NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL epoll_controller_remove_from_raised)(struct epoll_controller *__restrict self,
                                                   struct epoll_handle_monitor *__restrict monitor) {
	struct epoll_handle_monitor *rq;
	struct epoll_handle_monitor **prq;
again:
	rq = ATOMIC_READ(self->ec_raised);
	if (rq == monitor) {
		/* Special case: `monitor' is the most recently raised handle.
		 * In this case, we must use ATOMIC_CMPXCH because other monitors
		 * may have already changed `ec_raised' in the mean time. */
		if (!ATOMIC_CMPXCH_WEAK(self->ec_raised, rq, rq->ehm_rnext))
			goto again;
		return;
	}
	/* Not the first monitor (must scan the chain of raised monitors) */
	for (;;) {
		prq = &rq->ehm_rnext;
		rq  = *prq;
		assert(rq);
		if (rq == monitor)
			break; /* Found it! */
	}
	/* Unlink from the chain. */
	*prq = rq->ehm_rnext;
}

PRIVATE NOBLOCK NOPREEMPT NONNULL((1, 2)) void
NOTHROW(FCALL epoll_postcompletion)(struct sig_completion_context *__restrict UNUSED(context),
                                    void *buf) {
	REF struct epoll_controller *ctrl;
	ctrl = *(REF struct epoll_controller **)buf; /* Inherit reference */
	sig_send(&ctrl->ec_avail);
	decref_unlikely(ctrl);
}

PRIVATE NOBLOCK NOPREEMPT NONNULL((1, 2)) size_t
NOTHROW(FCALL epoll_completion)(struct sig_completion *__restrict self,
                                struct sig_completion_context *__restrict context,
                                void *buf, size_t bufsize) {
	struct epoll_handle_monitor *monitor;
	uintptr_half_t oldraise;
	/*sig_multicompletion_trydisconnect(self);*/ /* TODO: Optimization */

	/* Figure out our monitor. Note that we're safe to access the monitor, as
	 * well as its controller because the monitor owns `self', and right now
	 * our caller is preventing `self' from being destroyed by holding onto
	 * an internal SMP-lock that will block:
	 *  - `sig_completion_disconnect()', as called by
	 *  - `sig_multicompletion_disconnectall()', as called by
	 *  - `epoll_controller_destroy()' */
	monitor = container_of(sig_multicompletion_controller(self),
	                       struct epoll_handle_monitor, ehm_comp);
	/* Increment the raise-counter, but make sure not to overrun it. */
	do {
		oldraise = ATOMIC_READ(monitor->ehm_raised);
		if unlikely(oldraise == (uintptr_half_t)-1)
			break;
		if (oldraise == 0 && bufsize < sizeof(void *))
			return sizeof(void *);
	} while (!ATOMIC_CMPXCH_WEAK(monitor->ehm_raised,
	                             oldraise, oldraise + 1));
	/* If this is the first time that our monitor has been raised, then
	 * we must acquire a reference to the associated controller, as well
	 * as insert our own monitor into the controller's chain of raised
	 * monitors, before enqueuing a post-completion callback that will
	 * inherit that reference, and signal 1 waiting thread via `ec_avail' */
	if (oldraise == 0) {
		struct epoll_controller *ctrl;
		assert(bufsize >= sizeof(void *));
		ctrl = monitor->ehm_ctrl;
		/* NOTE: Must tryincref(), because the controller's reference counter
		 *       may have already dropped to `0'. - After all: epoll monitors
		 *       aren't holding actual references to their controllers, but
		 *       controllers will wait for monitors to disconnect during
		 *       destruction (though that happens _after_ the monitor's
		 *       reference counter has already dropped to 0...) */
		if likely(tryincref(ctrl)) {
			/* Enqueue our monitor as raised for the associated controller. */
			epoll_controller_add_to_raised(ctrl, monitor);
			/* Setup the post-completion function, and pass it
			 * our reference to the attached monitor. */
			*(void **)buf     = ctrl; /* Inherit reference */
			context->scc_post = &epoll_postcompletion;
			return sizeof(void *);
		}
	}
	return 0;
}
/************************************************************************/



/************************************************************************/
/* EPOLL monitor helpers                                                */

/* Destroy the given monitor */
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL epoll_handle_monitor_destroy)(struct epoll_handle_monitor *__restrict self) {
	/* NOTE: The caller must ensure that `&self->ehm_comp'
	 *       has been disconnected before we get here! */
	sig_multicompletion_fini(&self->ehm_comp);
	/* Drop our weak reference from the associated handle. */
	(*handle_type_db.h_weakdecref[self->ehm_handtyp])(self->ehm_handptr);
	/* Free the monitor. */
	kfree(self);
}

#define epoll_handle_monitor_weaklckref(self) \
	((*handle_type_db.h_weaklckref[(self)->ehm_handtyp])((self)->ehm_handptr))

#define epoll_handle_monitor_handle_decref(self, handle_obptr) \
	((*handle_type_db.h_decref[(self)->ehm_handtyp])(handle_obptr))

/* Test which (if any) of the monitored conditions is currently asserted. */
#define epoll_handle_monitor_polltest(self, handle_obptr)                    \
	((*handle_type_db.h_polltest[(self)->ehm_handtyp])(handle_obptr,         \
	                                                   (self)->ehm_events) & \
	 (self)->ehm_events & EPOLL_WHATMASK)


/* Connect the given monitor `self' to the monitored signals of `handle_obptr' */
PRIVATE NONNULL((1, 2)) void KCALL
epoll_handle_monitor_pollconnect(struct epoll_handle_monitor *__restrict self,
                                 void *handle_obptr) {
again:
	assert(!task_wasconnected());
	assert(!sig_multicompletion_wasconnected(&self->ehm_comp));
	TRY {
		/* Connect to monitored signals. */
		(*handle_type_db.h_pollconnect[self->ehm_handtyp])(handle_obptr,
		                                                   self->ehm_events);
		sig_multicompletion_connect_from_task(/* completion: */ &self->ehm_comp,
		                                      /* cb:         */ &epoll_completion,
		                                      /* for_poll:   */ true);
	} EXCEPT {
		sig_multicompletion_disconnectall(&self->ehm_comp);
		task_disconnectall();
		RETHROW();
	}
	if unlikely(task_receiveall() != NULL) {
		/* Signals were delivered in the mean time, and we have not have been able
		 * to transfer all of them over to `self->ehm_comp'. -> Try again. */
		sig_multicompletion_disconnectall(&self->ehm_comp);
		task_disconnectall();
		goto again;
	}
}

PRIVATE NOBLOCK NOPREEMPT NONNULL((1, 2)) void
NOTHROW(FCALL epoll_controller_add_to_pending)(struct epoll_controller *__restrict self,
                                               struct epoll_handle_monitor *__restrict monitor) {
	struct epoll_handle_monitor **ppending, *pending;
	monitor->ehm_rnext = NULL;
	ppending = &self->ec_pending;
	while ((pending = *ppending) != NULL)
		ppending = &pending->ehm_rnext;
	*ppending = monitor;
	if (ppending == &self->ec_pending)
		sig_send(&self->ec_avail); /* First pending monitor became available. */
}

/* Prime the given epoll monitor by polling its handle and setting up
 * signal completion callbacks. The caller is required to be holding
 * a lock to the associated epoll controller.
 * @param: test_before_connect: When `true', do an initial is-raised
 *                              test prior to the first connect. */
PRIVATE void KCALL
epoll_handle_monitor_prime(struct epoll_handle_monitor *__restrict self,
                           void *handptr, bool test_before_connect) {
	poll_mode_t what;
	assert(mutex_acquired(&self->ehm_ctrl->ec_lock));
	assert(!sig_multicompletion_wasconnected(&self->ehm_comp));
	COMPILER_BARRIER();
	self->ehm_raised = 0;
#ifndef NDEBUG
	memset(&self->ehm_rnext, 0xcc, sizeof(self->ehm_rnext));
#endif /* !NDEBUG */
	COMPILER_BARRIER();
	if (test_before_connect) {
		what = epoll_handle_monitor_polltest(self, handptr);
		if (what) {
was_asserted:
			COMPILER_BARRIER();
			self->ehm_raised = 1;
			epoll_handle_monitor_setwtest(self, what);
			/* Enqueue the monitor within the pending-queue */
			epoll_controller_add_to_pending(self->ehm_ctrl, self);
			return;
		}
	}
	epoll_handle_monitor_pollconnect(self, handptr);
	TRY {
		what = epoll_handle_monitor_polltest(self, handptr);
		if unlikely(what) {
			/* Disconnect */
			sig_multicompletion_disconnectall(&self->ehm_comp);
			goto was_asserted;
		}
	} EXCEPT {
		sig_multicompletion_disconnectall(&self->ehm_comp);
		/* Deal with the case where the handle was already raised.
		 * In this case, we must remove it from the queue of raised
		 * monitors in order to ensure consistency. */
		if (self->ehm_raised != 0) {
			epoll_controller_remove_from_raised(self->ehm_ctrl, self);
			self->ehm_raised = 0;
		}
		RETHROW();
	}
}
/************************************************************************/




/* Special monitor used to represent deleted entries. */
PRIVATE struct epoll_handle_monitor deleted_monitor = {
	/* .ehm_ctrl    = */ NULL,
	/* .ehm_rnext   = */ NULL,
	/* .ehm_raised  = */ 0,
	/* .ehm_handtyp = */ HANDLE_TYPE_UNDEFINED,
	/* .ehm_handptr = */ NULL,
	/* .ehm_fdkey   = */ (unsigned int)-1,
	/* .ehm_events  = */ EPOLL_WHATMASK,
	/* .ehm_data    = */ { NULL },
	/* .ehm_comp    = */ { /* ... */ }
};


/* Destroy the given epoll controller. */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL epoll_controller_destroy)(struct epoll_controller *__restrict self) {
	size_t i;
	/* Destroy all attached monitors. */
	for (i = 0; i <= self->ec_mask; ++i) {
		struct epoll_handle_monitor *mon;
		mon = self->ec_list[i].ece_mon;
		if (!mon || mon == &deleted_monitor)
			continue;
		assert(mon->ehm_ctrl == self);
		/* Make sure that this monitor isn't still connected to anything! */
		sig_multicompletion_disconnectall(&mon->ehm_comp);
		epoll_handle_monitor_destroy(mon);
	}
	kfree(self->ec_list);

	/* Broadcast private signals for finalization */
	assert(!sig_iswaiting(&self->ec_lock.m_unlock));
	sig_broadcast_for_fini(&self->ec_avail);
	weakdecref_likely(self);
}


/* Initial mask for the monitor hash-vector. */
#ifndef CONFIG_EPOLL_CONTROLLER_INITIAL_MASK
#define CONFIG_EPOLL_CONTROLLER_INITIAL_MASK 7
#endif /* !CONFIG_EPOLL_CONTROLLER_INITIAL_MASK */

/* Create a new epoll controller and return a reference to it.
 * This function is used by the `epoll_create(2)' syscall family. */
PUBLIC ATTR_RETNONNULL WUNUSED REF struct epoll_controller *KCALL
epoll_controller_create(void) THROWS(E_BADALLOC) {
	REF struct epoll_controller *result;
	result = (REF struct epoll_controller *)kmalloc(sizeof(struct epoll_controller),
	                                                GFP_NORMAL);
	result->ec_refcnt     = 1;
	result->ec_weakrefcnt = 1;
	mutex_init(&result->ec_lock);
	result->ec_raised  = NULL;
	result->ec_pending = NULL;
	sig_init(&result->ec_avail);
	result->ec_used = 0;
	result->ec_size = 0;
	result->ec_mask = CONFIG_EPOLL_CONTROLLER_INITIAL_MASK;
	TRY {
		result->ec_list = (struct epoll_controller_ent *)kmalloc((CONFIG_EPOLL_CONTROLLER_INITIAL_MASK + 1) *
		                                                         sizeof(struct epoll_controller_ent),
		                                                         GFP_CALLOC);
	} EXCEPT {
		kfree(result);
		RETHROW();
	}
	return result;
}



#define EPOLL_LOOP ((REF struct epoll_controller *)-1) /* Loop detected (or recursion too deep) */

/* Check if `findme' is already being monitored by `self'.
 * @return: NULL:       Everything's OK. - No loop here.
 * @return: EPOLL_LOOP: Loop detected (or recursion too deep)
 * @return: * :         A reference to a controller who's lock
 *                      couldn't be acquired immediately. The
 *                      caller should release all of their locks
 *                      and wait until this specific lock becomes
 *                      available. */
PRIVATE NOBLOCK WUNUSED NONNULL((1, 2)) REF struct epoll_controller *FCALL
epoll_controller_checkloop(struct epoll_controller *self,
                           struct epoll_controller *findme,
                           unsigned int current_depth) {
	REF struct epoll_controller *result = NULL;
	size_t i;
	if (!mutex_tryacquire(&self->ec_lock))
		return incref(self);
	mutex_release(&self->ec_lock);
	/* Scan the map of monitored handles of `self' */
	for (i = 0; i <= self->ec_mask; ++i) {
		struct epoll_handle_monitor *mon;
		mon = self->ec_list[i].ece_mon;
		if (!mon)
			continue;
		if (mon->ehm_handtyp == HANDLE_TYPE_EPOLL) {
			struct epoll_controller *inner;
			inner = (struct epoll_controller *)mon->ehm_handptr;
			/* TODO: Currently, user-space can do the following to circumvent the
			 *       CONFIG_EPOLL_MAX_NESTING restriction:
			 * Instead of adding an already-deeply nested epoll-fd to a new epoll-fd,
			 * which is caught and handled by this code right here, do the following:
			 * >> epfd_outer = epoll_create();
			 * >> for (;;) {
			 * >>     epfd_inner = epoll_create();
			 * >>     epoll_ctl(epfd_outer, EPOLL_CTL_ADD, epfd_inner, { ... });
			 * >>     epfd_outer = epfd_inner;
			 * >> }
			 */
			if (inner == findme || current_depth >= CONFIG_EPOLL_MAX_NESTING) {
				result = EPOLL_LOOP;
				goto done;
			}
			/* Try to acquire acquire a reference to the inner controller. */
			if (!tryincref(inner)) {
				assert(inner != findme);
				continue; /* Inner controller is already dead. - Just skip it. */
			}
			/* Recursive check. */
			result = epoll_controller_checkloop(inner, findme,
			                                    current_depth + 1);
			if (result != NULL)
				goto done; /* Try again, or loop detected */
		}
	}
done:
	mutex_release(&self->ec_lock);
	return result;
}


/* Acquire a lock to `self' with the intend of adding `hand' as a monitor.
 * This function asserts that when `hand' is another EPOLL controller, then
 * it must differ from `self' and not already be monitoring `self', either.
 *
 * Upon return, the caller inherits a lock to `self->ec_lock' */
PRIVATE NONNULL((1, 2)) void FCALL
epoll_controller_acquire_for_monitor_add(struct epoll_controller *__restrict self,
                                         struct handle const *__restrict hand)
		THROWS(E_WOULDBLOCK, E_ILLEGAL_REFERENCE_LOOP) {
again:
	mutex_acquire(&self->ec_lock);
	if (hand->h_type == HANDLE_TYPE_EPOLL) {
		REF struct epoll_controller *error;
		struct epoll_controller *hand_epoll;
		hand_epoll = (struct epoll_controller *)hand->h_data;
		/* Special case: top-level loops aren't checked by `epoll_controller_checkloop()' */
		if unlikely(hand_epoll == self)
			goto epoll_loop;
		/* Search for loops. */
		error = epoll_controller_checkloop(hand_epoll, self, 0);
		if unlikely(error != NULL) {
			if (error == EPOLL_LOOP) {
epoll_loop:
				mutex_release(&self->ec_lock);
				/* TODO: Linux returns -EINVAL when `hand_epoll == self',
				 *       and -ELOOP in all other cases. This right here
				 *       causes -ELOOP for all cases! */
				THROW(E_ILLEGAL_REFERENCE_LOOP);
			}
			mutex_release(&self->ec_lock);
			/* Wait for `error' to become available. */
			TRY {
				while (!mutex_poll_unlikely(&error->ec_lock))
					task_waitfor();
			} EXCEPT {
				task_disconnectall();
				decref_unlikely(error);
				RETHROW();
			}
			task_disconnectall();
			decref_unlikely(error);
			goto again;
		}
		/* At this point we know that `self' isn't already being monitored by
		 * the given `hand', and we also know that it won't start being monitored
		 * until we release `self->ec_lock' once again, since a similar call
		 * to `epoll_controller_addmonitor()' trying to add `self' to the set
		 * of the monitors of `hand' would have to acquire the lock of `self',
		 * which we're already holding at this point, thus ensuring that no
		 * other thread can add `self' to any monitor listings before we're
		 * done! */
	}
}

/* Add `monitor' to the hash-vector of monitors of `self' */
PRIVATE NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL epoll_controller_intern_rehash_with)(struct epoll_controller *__restrict self,
                                                   struct epoll_controller_ent *__restrict new_list,
                                                   size_t new_mask) {
	/* Rehash existing entries. */
	uintptr_t i, j, perturb;
	assert(new_mask >= self->ec_used);
	for (i = 0; i <= self->ec_mask; ++i) {
		struct epoll_controller_ent *dst;
		struct epoll_handle_monitor *mon;
		uintptr_t hash;
		mon = self->ec_list[i].ece_mon;
		if (!mon || mon == &deleted_monitor)
			continue; /* Empty, or deleted. */
		hash = epoll_controller_hashof(mon);
		j = perturb = hash & new_mask;
		for (;; epoll_controller_hashnx(j, perturb)) {
			dst = &new_list[j & new_mask];
			if (!dst->ece_mon)
				break;
		}
		dst->ece_mon = mon; /* Rehash */
	}
	kfree(self->ec_list);
	self->ec_list = new_list;
	self->ec_mask = new_mask;
	self->ec_size = self->ec_used; /* All deleted entries were removed... */
}

PRIVATE NOBLOCK NONNULL((1, 2)) bool
NOTHROW(FCALL epoll_controller_intern_doadd)(struct epoll_controller *__restrict self,
                                             /*inherit(always)*/ struct epoll_handle_monitor *__restrict monitor) {
	uintptr_t hash, i, perturb;
	struct epoll_controller_ent *ent;
	assert((self->ec_size + 1) <= self->ec_mask);
	hash = epoll_controller_hashof(monitor);
	i = perturb = hash & self->ec_mask;
	for (;; epoll_controller_hashnx(i, perturb)) {
		struct epoll_handle_monitor *emon;
		ent  = &self->ec_list[i & self->ec_mask];
		emon = ent->ece_mon;
		if (!emon) {
			/* Found a free slot */
			++self->ec_size;
			break;
		}
		if (emon == &deleted_monitor) {
			/* Re-use a previously deleted slot. */
			break;
		}
		/* Check if this is an identical monitor. */
		if (emon->ehm_handptr == monitor->ehm_handptr &&
		    emon->ehm_fdkey == monitor->ehm_fdkey)
			return false; /* Identical (cannot add) */
	}
	ent->ece_mon = monitor; /* Inherit */
	++self->ec_used;
	return true;
}

/* Add the given `monitor' to `self'
 * @return: true:  Success.
 * @return: false: An identical monitor had already been added in the past. */
PRIVATE NONNULL((1, 2)) bool FCALL
epoll_controller_intern_addmon(struct epoll_controller *__restrict self,
                               /*inherit(on_success)*/ struct epoll_handle_monitor *__restrict monitor)
		THROWS(E_BADALLOC) {
	if (((self->ec_size + 1) * 3) / 2 >= self->ec_mask) {
		/* Must rehash! */
		struct epoll_controller_ent *new_list;
		size_t new_mask = CONFIG_EPOLL_CONTROLLER_INITIAL_MASK;
		size_t thresh   = ((self->ec_used + 1) * 3) / 2;
		while (thresh >= new_mask)
			new_mask = (new_mask << 1) | 1;
		new_list = (struct epoll_controller_ent *)kmalloc_nx((new_mask + 1) *
		                                                     sizeof(struct epoll_controller_ent),
		                                                     GFP_CALLOC);
		if unlikely(!new_list) {
			if ((self->ec_size + 1) <= self->ec_mask)
				goto doadd;
			new_mask = CONFIG_EPOLL_CONTROLLER_INITIAL_MASK;
			while ((self->ec_used + 1) > self->ec_mask)
				new_mask = (new_mask << 1) | 1;
			new_list = (struct epoll_controller_ent *)kmalloc((new_mask + 1) *
			                                                  sizeof(struct epoll_controller_ent),
			                                                  GFP_CALLOC);
		}
		/* Rehash using the new list. */
		epoll_controller_intern_rehash_with(self, new_list, new_mask);
		assert(self->ec_used == self->ec_size);
	}
doadd:
	return epoll_controller_intern_doadd(self, monitor);
}

/* Try to rehash the given controller following the removing of an monitor. */
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL epoll_controller_intern_rehash_after_remove)(struct epoll_controller *__restrict self)
		THROWS(E_BADALLOC) {
	if ((self->ec_used < (self->ec_mask / 3)) &&
	    self->ec_mask > CONFIG_EPOLL_CONTROLLER_INITIAL_MASK) {
		/* Try to shrink the hash-vector's mask size. */
		size_t new_mask = CONFIG_EPOLL_CONTROLLER_INITIAL_MASK;
		size_t thresh   = ((self->ec_used + 1) * 3) / 2;
		while (thresh >= new_mask)
			new_mask = (new_mask << 1) | 1;
		if (new_mask < self->ec_mask) {
			/* Try to shrink */
			struct epoll_controller_ent *new_list;
			new_list = (struct epoll_controller_ent *)kmalloc_nx((new_mask + 1) *
			                                                     sizeof(struct epoll_controller_ent),
			                                                     GFP_ATOMIC | GFP_CALLOC);
			/* If the alloc worked, re-hash using `new_list' */
			if (new_list)
				epoll_controller_intern_rehash_with(self, new_list, new_mask);
		}
	}
}

/* Remove `monitor' from the set of monitors of `self' */
PRIVATE NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL epoll_controller_intern_delmon)(struct epoll_controller *__restrict self,
                                              /*caller_inherit(always)*/ struct epoll_handle_monitor *__restrict monitor)
		THROWS(E_BADALLOC) {
	uintptr_t hash, i, perturb;
	struct epoll_controller_ent *ent;
	assert(self->ec_used);
	assert((self->ec_size + 1) <= self->ec_mask);
	hash = epoll_controller_hashof(monitor);
	i = perturb = hash & self->ec_mask;
	for (;; epoll_controller_hashnx(i, perturb)) {
		ent = &self->ec_list[i & self->ec_mask];
		assert(ent->ece_mon);
		if (ent->ece_mon == monitor)
			break;
	}
	ent->ece_mon = &deleted_monitor;
	--self->ec_used;
	epoll_controller_intern_rehash_after_remove(self);
}

/* Try to pop and return the monitor matching the given handle/fd-key pair.
 * If no such monitor exists, return NULL instead. */
PRIVATE NOBLOCK NONNULL((1, 2)) /*inherit(on_success)*/ struct epoll_handle_monitor *
NOTHROW(FCALL epoll_controller_intern_pop)(struct epoll_controller *__restrict self,
                                           void *handptr, uint32_t fd_key)
		THROWS(E_BADALLOC) {
	uintptr_t hash, i, perturb;
	struct epoll_controller_ent *ent;
	struct epoll_handle_monitor *emon;
	hash = epoll_controller_hashof_ex(handptr, fd_key);
	i = perturb = hash & self->ec_mask;
	for (;; epoll_controller_hashnx(i, perturb)) {
		ent  = &self->ec_list[i & self->ec_mask];
		emon = ent->ece_mon;
		if (!emon)
			return NULL; /* No such monitor. */
		if (emon->ehm_handptr == handptr &&
		    emon->ehm_fdkey == fd_key)
			break; /* Found it! */
	}
	assert(self->ec_used);
	ent->ece_mon = &deleted_monitor;
	--self->ec_used;
	epoll_controller_intern_rehash_after_remove(self);
	return emon;
}

/* Lookup the monitor for a given handle/fd-key pair.
 * If no such monitor exists, return NULL instead. */
PRIVATE NOBLOCK WUNUSED NONNULL((1, 2)) struct epoll_handle_monitor *
NOTHROW(FCALL epoll_controller_intern_lookup)(struct epoll_controller *__restrict self,
                                              void *handptr, uint32_t fd_key) {
	uintptr_t hash, i, perturb;
	struct epoll_controller_ent *ent;
	assert((self->ec_size + 1) <= self->ec_mask);
	hash = epoll_controller_hashof_ex(handptr, fd_key);
	i = perturb = hash & self->ec_mask;
	for (;; epoll_controller_hashnx(i, perturb)) {
		struct epoll_handle_monitor *emon;
		ent  = &self->ec_list[i & self->ec_mask];
		emon = ent->ece_mon;
		if (!emon)
			break; /* No such monitor... */
		/* Check if this is the one. */
		if (emon->ehm_handptr == handptr &&
		    emon->ehm_fdkey == fd_key)
			return emon; /* Found it! */
	}
	return NULL;
}
/************************************************************************/





/* Add a monitor for `hand' to the given epoll controller.
 * @throw: E_ILLEGAL_REFERENCE_LOOP: `hand' is another epoll controller that is either the same
 *                                   as `self', or is already monitoring `self'. Also thrown if
 *                                   the max depth of nested epoll controllers would exceed the
 *                                   compile-time `CONFIG_EPOLL_MAX_NESTING' limit.
 * @return: true:  Success
 * @return: false: Another monitor for `hand' already exists. */
PUBLIC NONNULL((1, 2)) bool KCALL
epoll_controller_addmonitor(struct epoll_controller *__restrict self,
                            struct handle const *__restrict hand,
                            uint32_t fd_key,
                            USER CHECKED struct epoll_event const *info)
		THROWS(E_BADALLOC, E_WOULDBLOCK, E_SEGFAULT,
		       E_ILLEGAL_REFERENCE_LOOP) {
	struct epoll_handle_monitor *newmon;
	/* Allocate the controller for the new monitor. */
	newmon = (struct epoll_handle_monitor *)kmalloc(sizeof(struct epoll_handle_monitor),
	                                                GFP_NORMAL);
	/* Already initialize some of the monitor's fields. */
	newmon->ehm_ctrl    = self;
	newmon->ehm_rnext   = NULL;
	newmon->ehm_raised  = 0;
	newmon->ehm_handtyp = hand->h_type;
	newmon->ehm_fdkey   = fd_key;
/*	newmon->ehm_handptr = ...; // Filled later */
	sig_multicompletion_init(&newmon->ehm_comp);
	TRY {
		/* Fill in monitor event information. */
		COMPILER_READ_BARRIER();
		newmon->ehm_events   = info->events;
		newmon->ehm_data.u64 = info->data.u64;
		COMPILER_READ_BARRIER();

		/* Make sure that these 2 events are always polled for.
		 * By setting them here, this simplifies other code. */
		newmon->ehm_events |= EPOLLERR | EPOLLHUP;

		/* Acquire a lock to `self' and assert that adding `hand' won't
		 * cause any reference loops (or rather: signal loops, where one
		 * signal would try to broadcast itself from within a signal
		 * completion callback)
		 * Note however that KOS's signal completion callback system
		 * should be strong enough to correctly deal with a signal that
		 * is sending itself, so-long as the associated completion
		 * function didn't attempt to re-prime itself. */
		epoll_controller_acquire_for_monitor_add(self, hand);
		TRY {
			/* Acquire a weak reference to the given handle. */
			newmon->ehm_handptr = handle_weakgetref(*hand); /* Inherit reference */
			assert(newmon->ehm_handptr);

			TRY {
				/* Add `newmon' from the monitor list of `self' */
				if unlikely(!epoll_controller_intern_addmon(self, newmon)) {
					/* Cannot add: An identical monitor had already been added in the past... */
					mutex_release(&self->ec_lock);
					(*handle_type_db.h_weakdecref[newmon->ehm_handtyp])(newmon->ehm_handptr);
					sig_multicompletion_fini(&newmon->ehm_comp);
					kfree(newmon);
					return false;
				}
	
				/* Prime the monitor for the first time. */
				TRY {
					epoll_handle_monitor_prime(newmon, hand->h_data, true);
				} EXCEPT {
					/* Remove `newmon' from the monitor list of `self' */
					epoll_controller_intern_delmon(self, newmon);
					RETHROW();
				}
			} EXCEPT {
				(*handle_type_db.h_weakdecref[newmon->ehm_handtyp])(newmon->ehm_handptr);
				RETHROW();
			}
		} EXCEPT {
			mutex_release(&self->ec_lock);
			RETHROW();
		}
		mutex_release(&self->ec_lock);
	} EXCEPT {
		sig_multicompletion_fini(&newmon->ehm_comp);
		kfree(newmon);
		RETHROW();
	}
	return true;
}

PRIVATE NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL epoll_controller_remove_from_raised_or_pending)(struct epoll_controller *__restrict self,
                                                              struct epoll_handle_monitor *__restrict monitor) {
	struct epoll_handle_monitor **ppending, *pending;
	/* Search the pending-queue. */
	ppending = &self->ec_pending;
	while ((pending = *ppending) != NULL) {
		if (pending == monitor) {
			*ppending = pending->ehm_rnext;
			return;
		}
		ppending = &pending->ehm_rnext;
	}
	/* Failed to find the monitor in the pending-queue.
	 * -> That means that the monitor must be apart of the raised queue! */
	epoll_controller_remove_from_raised(self, monitor);
}



/* Modify the monitor for `hand' within the given epoll controller.
 * @return: true:  Success
 * @return: false: The given `hand' isn't being monitored by `self'. */
PUBLIC NONNULL((1, 2)) bool KCALL
epoll_controller_modmonitor(struct epoll_controller *__restrict self,
                            struct handle const *__restrict hand,
                            uint32_t fd_key,
                            USER CHECKED struct epoll_event const *info)
		THROWS(E_BADALLOC, E_WOULDBLOCK, E_SEGFAULT) {
	struct epoll_event new_events;
	memcpy(&new_events, info, sizeof(struct epoll_event));
	COMPILER_READ_BARRIER();
	/* Make sure that these 2 events are always polled for.
	 * By setting them here, this simplifies other code. */
	new_events.events |= EPOLLERR | EPOLLHUP;

	mutex_acquire(&self->ec_lock);
	TRY {
		struct epoll_handle_monitor *monitor;
		monitor = epoll_controller_intern_lookup(self,
		                                         hand->h_data,
		                                         fd_key);
		if unlikely(!monitor) {
			mutex_release(&self->ec_lock);
			return false;
		}
		if (((monitor->ehm_events & EPOLL_WHATMASK) != (new_events.events & EPOLL_WHATMASK)) ||
		    /* Special case: Re-arm a ONESHOT monitor after that monitor has been left
		     *               dangling and disconnected. This behavior is required for
		     *               linux compatibility (but s.a. `KP_EPOLL_DELETE_ONESHOT') */
			((monitor->ehm_events & EPOLLONESHOT) && !sig_multicompletion_wasconnected(&monitor->ehm_comp))) {
			/* Change monitored events. */
			sig_multicompletion_disconnectall(&monitor->ehm_comp);
			COMPILER_BARRIER();
			/* If the monitor has already been raised, then we
			 * must remove it from the raised-monitor queue. */
			if (monitor->ehm_raised != 0)
				epoll_controller_remove_from_raised_or_pending(self, monitor);
			COMPILER_BARRIER();

			/* Apply new monitor settings. */
			monitor->ehm_events   = new_events.events;
			monitor->ehm_data.u64 = new_events.data.u64;

			/* Prime the monitor with its new settings. */
			TRY {
				epoll_handle_monitor_prime(monitor, hand->h_data, true);
			} EXCEPT {
				/* If priming failed, then we must manually mark the monitor as raised,
				 * even though it isn't, just so we can once again achieve internal
				 * consistency, since only a monitor that's currently raised is allowed
				 * not to be connected to any signals.
				 *
				 * This way, epoll_controller_trywait() will handle the problem for us. */
				monitor->ehm_raised = 1;
				epoll_controller_add_to_raised(self, monitor);
				RETHROW();
			}
		} else {
			monitor->ehm_events   = new_events.events;
			monitor->ehm_data.u64 = new_events.data.u64;
		}
	} EXCEPT {
		mutex_release(&self->ec_lock);
		RETHROW();
	}
	mutex_release(&self->ec_lock);
	return true;
}


/* Delete the monitor for `hand' within the given epoll controller.
 * @return: true:  Success
 * @return: false: The given `hand' isn't being monitored by `self'. */
PUBLIC NONNULL((1, 2)) bool KCALL
epoll_controller_delmonitor(struct epoll_controller *__restrict self,
                            struct handle const *__restrict hand,
                            uint32_t fd_key)
		THROWS(E_WOULDBLOCK) {
	struct epoll_handle_monitor *monitor;
	mutex_acquire(&self->ec_lock);
	TRY {
		/* Pop the monitor matching the given handle/fd-key */
		monitor = epoll_controller_intern_pop(self,
		                                      hand->h_data,
		                                      fd_key);
		if unlikely(!monitor) {
			mutex_release(&self->ec_lock);
			return false;
		}
	} EXCEPT {
		mutex_release(&self->ec_lock);
		RETHROW();
	}
	/* Note that we've just inherited `monitor', so now we have to destroy it! */
	sig_multicompletion_disconnectall(&monitor->ehm_comp);
	/* With signal completion callbacks all diconnected (by `sig_multicompletion_disconnectall()'),
	 * we must also ensure that `monitor' isn't apart of the raised monitor chain.
	 * If it is, then we must remove it prior to releasing our lock from `ec_lock' */
	if (monitor->ehm_raised != 0)
		epoll_controller_remove_from_raised_or_pending(self, monitor);
	mutex_release(&self->ec_lock);
	/* Finish destroying `monitor' */
	epoll_handle_monitor_destroy(monitor);
	return true;
}

PRIVATE WUNUSED NONNULL((1)) void
NOTHROW(KCALL epoll_controller_requeue_events_at_back_of_chain)(struct epoll_controller *__restrict self,
                                                                struct epoll_handle_monitor *chain) {
	struct epoll_handle_monitor *oldchain;
again:
	oldchain = ATOMIC_READ(self->ec_raised);
	if (!oldchain) {
		if (!ATOMIC_CMPXCH_WEAK(self->ec_raised, NULL, chain))
			goto again;
		return;
	}
	/* Re-insert at the end of the raised queue. (walk the distance) */
	while (oldchain->ehm_rnext)
		oldchain = oldchain->ehm_rnext;
	/* Append at the end. */
	oldchain->ehm_rnext = chain;
}

/* Disconnect all monitors from the given `chain' and assert that they are raised. */
PRIVATE void
NOTHROW(FCALL epoll_handle_monitor_dc_chain)(struct epoll_handle_monitor *chain) {
	for (; chain; chain = chain->ehm_rnext) {
		assert(chain->ehm_raised != 0);
		sig_multicompletion_disconnectall(&chain->ehm_comp);
	}
}


#undef EC_PENDING_INUSE
#ifndef NDEBUG
#if __SIZEOF_POINTER__ == 4
#define EC_PENDING_INUSE ((WEAK struct epoll_handle_monitor *)UINT32_C(0xcccccccc))
#elif __SIZEOF_POINTER__ == 8
#define EC_PENDING_INUSE ((WEAK struct epoll_handle_monitor *)UINT64_C(0xcccccccccccccccc))
#endif /* __SIZEOF_POINTER__ == ... */
#endif /* !NDEBUG */

/* Try to consume pending events from `self'. Note that this
 * function can throw E_BADALLOC because in the event that a
 * monitor has to be re-primed, there is a chance that doing
 * so might require more signal connection descriptors to be
 * allocated, which in turn might cause that allocation to fail.
 * When this happens, all already-consumed events will be marked
 * as raised once again, and be back onto the queue of pending
 * events. The same thing also happens when writing to `events'
 * would result in a SEGFAULT.
 * @param: maxevents: The max number of events to consume (asserted to be >= 1)
 * @return: * : The actual number of consumed events.
 * @return: 0 : No monitors have been raised at this time. Once any
 *              monitor becomes raised, `self->ec_avail' will be send. */
PUBLIC NOCONNECT NONNULL((1)) size_t KCALL
epoll_controller_trywait(struct epoll_controller *__restrict self,
                         USER CHECKED struct epoll_event *events,
                         size_t maxevents)
		THROWS(E_BADALLOC, E_WOULDBLOCK, E_SEGFAULT) {
	/* Return value. */
	size_t result = 0;

	/* [0..1] Chain of monitors for which rising-edge events could be confirmed.
	 * Ordered by least-recently-raised to most-recently-raised, and chained via
	 * the `ehm_rnext' field. The actual raised events can be retrieved through
	 * use of `epoll_handle_monitor_getwtest()' */
	struct epoll_handle_monitor *result_events;

	assert(maxevents >= 1);
	/* Quick check: is there anything that was raised? */
	if (!epoll_controller_canwait(self))
		goto done;
	/* Acquire a lock to the controller, but make sure not to clobber
	 * the calling thread's current set of active connections. */
	mutex_acquire(&self->ec_lock);
	result_events = self->ec_pending;
#ifdef EC_PENDING_INUSE
	self->ec_pending = EC_PENDING_INUSE;
#endif /* EC_PENDING_INUSE */
	TRY {
		{
			struct epoll_handle_monitor *monitor;
			monitor = ATOMIC_XCH(self->ec_raised, NULL);
			TRY {
scan_monitors:
				while (monitor) {
					struct epoll_handle_monitor *next;
					poll_mode_t what;
					REF void *monitor_handptr;
					next = monitor->ehm_rnext;
					assert(monitor->ehm_raised != 0);
	
					/* First of all: Ensure that `monitor' isn't connected. */
					sig_multicompletion_disconnectall(&monitor->ehm_comp);
	
					/* Now acquire a reference to the monitor's handle.
					 * If this fails, silently destroy the monitor and move one. */
					monitor_handptr = epoll_handle_monitor_weaklckref(monitor);
	
					if unlikely(!monitor_handptr) {
						/* Object was destroyed (this is why we're using weak references)
						 * In this case, just get rid of the monitor and carry on like
						 * nothing ever happened. */
						epoll_controller_intern_delmon(self, monitor);
						epoll_handle_monitor_destroy(monitor);
						goto next_monitor;
					}
	
					TRY {
						/* Now figure out what (if anything) about `monitor' is pending. */
						what = epoll_handle_monitor_polltest(monitor, monitor_handptr);
						if (!what) {
							/* Monitor isn't actually raised (spurious
							 * signal, or edge has already fallen again).
							 * -> Handle this case by prime `monitor' once again. */
							DBG_memset(&monitor->ehm_rnext, 0xcc, sizeof(monitor->ehm_rnext));
							COMPILER_WRITE_BARRIER();
							ATOMIC_WRITE(monitor->ehm_raised, 0);
							epoll_handle_monitor_pollconnect(monitor, monitor_handptr);
							what = epoll_handle_monitor_polltest(monitor, monitor_handptr);
							if unlikely(what != 0) {
								sig_multicompletion_disconnectall(&monitor->ehm_comp);
								if (ATOMIC_READ(monitor->ehm_raised) != 0) {
									struct epoll_handle_monitor *more_raised;
									struct epoll_handle_monitor *more_raised_last;
									/* Must remove `monitor' from the raised-queue. */
									more_raised = ATOMIC_XCH(self->ec_raised, NULL);
									assert(more_raised != NULL);
									more_raised_last = more_raised;
									while (more_raised_last->ehm_rnext)
										more_raised_last = more_raised_last->ehm_rnext;
									/* Combine the two chains. */
									more_raised_last->ehm_rnext = next;
									if (more_raised_last != monitor)
										goto scan_monitors; /* Scan the chains in order. */
									/* We've got lucky, and `monitor' was the last to have
									 * been raised in the mean time. In this case, our current
									 * state is identical to what we need to handle `monitor'
									 * immediately, without having to re-calculate `what' */
								}
								goto got_monitor_what;
							}
							/* Now that the monitor has been re-connected,
							 * it's time to leave it running once again */
							epoll_handle_monitor_handle_decref(monitor, monitor_handptr);
							goto next_monitor;
						}
					} EXCEPT {
						epoll_handle_monitor_handle_decref(monitor, monitor_handptr);
						RETHROW();
					}
got_monitor_what:
					assert(what != 0);
					epoll_handle_monitor_handle_decref(monitor, monitor_handptr);
					/* Remember the set of raised channels for this monitor. */
					epoll_handle_monitor_setwtest(monitor, what);
					/* Found a monitor with raised events. (add it to the `result_events' queue) */
					monitor->ehm_rnext = result_events;
					result_events      = monitor;
next_monitor:
					monitor = next;
				}
			} EXCEPT {
				/* Restore the raised-event chain. */
				epoll_handle_monitor_dc_chain(monitor);
				epoll_controller_requeue_events_at_back_of_chain(self, monitor);
				RETHROW();
			}
		} /* Scope */
		/* With the set of raised monitors confirmed as `result_events', write
		 * back the results about their events to the user-supplied `events'. */
		if (result_events != NULL) {
			/* [0..1] The first monitor that is pending, but
			 *        hasn't been written to user-space, yet. */
			struct epoll_handle_monitor *next_monitor;
			next_monitor = result_events;
			for (;;) {
				/* Write-back information about the event to user-space. */
				COMPILER_WRITE_BARRIER();
				events[result].events   = epoll_handle_monitor_getwtest(next_monitor);
				events[result].data.u64 = next_monitor->ehm_data.u64;
				COMPILER_WRITE_BARRIER();
				++result;

				next_monitor = next_monitor->ehm_rnext;
				if (!next_monitor || result >= maxevents)
					break;
			} /* for (;;) */
			/* Now that all requested monitors have been written back to user-space,
			 * it's time to cleanup/reprime all of the monitors between `result_events'
			 * and `next_monitor' */
			assert(result_events != next_monitor);
			{
				/* A chain of monitors that must be re-appended at
				 * the end of the  chain of raised monitors. */
				struct epoll_handle_monitor *reraise_monitors = NULL;
				TRY {
					do {
						struct epoll_handle_monitor *next;
						next = result_events->ehm_rnext;
						/* Do one of the following:
						 * if (EPOLLONESHOT) {
						 *     - Do nothing. The monitor should still remain, but should
						 *       not actually be active. Linux docs state that the user
						 *       must use EPOLL_CTL_MOD to re-arm the monitor.
						 * } else if (EPOLLET) {
						 *   - Blindly re-connect `result_events' to its associated handle in
						 *     order to wait for the next rising-edge event, even though the
						 *     handle itself (should) still be raised right now.
						 * } else {
						 *   - Append `result_events' at the end of the `ec_raised' queue, such
						 *     that it gets re-checked for raised channels during the next call
						 *     to `epoll_controller_trywait()'
						 *   - The `ec_raised' should still be relatively small/entirely empty,
						 *     since we've just cleared it further above (of course: unrelated
						 *     monitors may have been raised in the mean time, but this re-insert
						 *     should still be a relatively fast operation, especially if we
						 *     combine the set of )
						 * } */
						assert(!sig_multicompletion_wasconnected(&result_events->ehm_comp));
						assert(result_events->ehm_raised != 0);
						if (result_events->ehm_events & EPOLLONESHOT) {
							if (has_personality(KP_EPOLL_DELETE_ONESHOT)) {
do_destroy_result_event:
								epoll_controller_intern_delmon(self, result_events);
								epoll_handle_monitor_destroy(result_events);
							} else {
								/* Mark the monitor as no longer raised. */
								ATOMIC_WRITE(result_events->ehm_raised, 0);
							}
						} else if (result_events->ehm_events & EPOLLET) {
							/* For this to work, we have to re-acquire a (strong) reference
							 * to the associated handle. Note however that this can still
							 * fail at this point, but we can easily handle that case by
							 * jumping to the `EPOLLONESHOT' handler. */
							REF void *monitor_handptr;
							monitor_handptr = epoll_handle_monitor_weaklckref(result_events);
							if unlikely(!monitor_handptr)
								goto do_destroy_result_event;
							ATOMIC_WRITE(result_events->ehm_raised, 0);
							TRY {
								epoll_handle_monitor_pollconnect(result_events, monitor_handptr);
							} EXCEPT {
								epoll_handle_monitor_handle_decref(result_events, monitor_handptr);
								RETHROW();
							}
							epoll_handle_monitor_handle_decref(result_events, monitor_handptr);
						} else {
							/* Re-raise this monitor, so it gets checked for pending channels
							 * once again the next time around (this is done for monitors that
							 * continuously produce events for as long as they remain raised),
							 * which is the default unless `EPOLLONESHOT' or `EPOLLET' is set. */
							/* NOTE: This insert once again reverses the monitor order from
							 *       least-recently-raised to most-recently-raised, which is
							 *       intended, as the raised-chain is sorted in that manner! */
							result_events->ehm_rnext = reraise_monitors;
							reraise_monitors         = result_events;
						}
						result_events = next;
					} while (result_events != next_monitor);
					assert(result_events == next_monitor);
				} EXCEPT {
					/* Re-insert raised monitors into the raised-queue */
					if (reraise_monitors)
						epoll_controller_requeue_events_at_back_of_chain(self, reraise_monitors);
					RETHROW();
				}
				/* Re-insert raised monitors into the raised-queue */
				if (reraise_monitors)
					epoll_controller_requeue_events_at_back_of_chain(self, reraise_monitors);
			} /* Scope */
		}     /* if (result_events != NULL) */
	} EXCEPT {
		/* Re-insert all result-events into the raised-list on error.
		 * That way, they can be received once again by the next one
		 * to call `epoll_controller_trywait()' */
#ifdef EC_PENDING_INUSE
		assert(self->ec_pending == EC_PENDING_INUSE);
#endif /* EC_PENDING_INUSE */
		self->ec_pending = result_events;
		if (result_events != NULL) {
			/* Indicate that more events may have become available */
			sig_send(&self->ec_avail);
		}
		mutex_release(&self->ec_lock);
		RETHROW();
	}
	/* Push-back all events that haven't been consumed, yet. */
#ifdef EC_PENDING_INUSE
	assert(self->ec_pending == EC_PENDING_INUSE);
#endif /* EC_PENDING_INUSE */
	self->ec_pending = result_events;
	if (result_events != NULL) {
		/* Indicate that more events may have become available */
		sig_send(&self->ec_avail);
	}
	mutex_release(&self->ec_lock);
done:
	return result;
}

/* Same as `epoll_controller_trywait()', but blocking wait until
 * at least 1 event could be consumed. If `abs_timeout' is finite,
 * and expires while waiting for the first event to appear, then
 * this function will return `0' (note that if `abs_timeout' was already
 * expired from the get-go, this function will still try to consume
 * already-pending events, thus behaving identical to a call to
 * `epoll_controller_trywait()') */
PUBLIC NONNULL((1)) size_t KCALL
epoll_controller_wait(struct epoll_controller *__restrict self,
                      USER CHECKED struct epoll_event *events,
                      size_t maxevents, ktime_t abs_timeout)
		THROWS(E_BADALLOC, E_WOULDBLOCK, E_SEGFAULT, E_INTERRUPT) {
	size_t result;
	assert(!task_wasconnected());
again:
	result = epoll_controller_trywait(self, events, maxevents);
	if (result == 0) {
		task_connect(&self->ec_avail);
		TRY {
			result = epoll_controller_trywait(self, events, maxevents);
			if (result != 0) {
				task_disconnectall();
				return result;
			}
		} EXCEPT {
			task_disconnectall();
			RETHROW();
		}
		if (!task_waitfor(abs_timeout))
			return 0; /* Nothing became available in the mean time... */
		goto again;
	}
	return result;
}




/************************************************************************/
/* EPOLL syscall API                                                    */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_EPOLL_CREATE1
DEFINE_SYSCALL1(fd_t, epoll_create1, syscall_ulong_t, flags) {
	unsigned int result;
	struct handle hand;
	VALIDATE_FLAGSET(flags, EPOLL_CLOEXEC | EPOLL_CLOFORK,
	                 E_INVALID_ARGUMENT_CONTEXT_EPOLL_CREATE1_FLAGS);
	hand.h_type = HANDLE_TYPE_EPOLL;
	hand.h_mode = IO_RDWR;
#define EPOLL_CREATE_FLAGS_IO_SHIFT 17
#if ((EPOLL_CLOEXEC >> EPOLL_CREATE_FLAGS_IO_SHIFT) == IO_CLOEXEC && \
     (EPOLL_CLOFORK >> EPOLL_CREATE_FLAGS_IO_SHIFT) == IO_CLOFORK)
	hand.h_mode |= flags >> EPOLL_CREATE_FLAGS_IO_SHIFT;
#else /* ... */
	if (flags & EPOLL_CLOEXEC)
		hand.h_mode |= IO_CLOEXEC;
	if (flags & EPOLL_CLOFORK)
		hand.h_mode |= IO_CLOFORK;
#endif /* !... */
	/* Create the actual epoll object. */
	hand.h_data = epoll_controller_create();
	{
		FINALLY_DECREF_UNLIKELY((REF struct epoll_controller *)hand.h_data);
		/* Register the handle. */
		result = handle_install(THIS_HANDLE_MANAGER, hand);
	}
	return (fd_t)result;
}
#endif /* __ARCH_WANT_SYSCALL_EPOLL_CREATE1 */

#ifdef __ARCH_WANT_SYSCALL_EPOLL_CREATE
DEFINE_SYSCALL1(fd_t, epoll_create, syscall_ulong_t, size) {
	(void)size;
	return sys_epoll_create1(0);
}
#endif /* __ARCH_WANT_SYSCALL_EPOLL_CREATE */

#ifdef __ARCH_WANT_SYSCALL_EPOLL_CTL
DEFINE_SYSCALL4(errno_t, epoll_ctl,
                fd_t, epfd, syscall_ulong_t, op, fd_t, fd,
                USER UNCHECKED struct epoll_event *, info) {
	errno_t result = -EOK;
	REF struct epoll_controller *self;
	REF struct handle fd_handle;
	self = handle_get_epoll_controller(epfd);
	FINALLY_DECREF_UNLIKELY(self);
	fd_handle = handle_lookup(fd);
	TRY {
		switch (op) {
	
		case EPOLL_CTL_ADD:
			validate_readable(info, sizeof(*info));
			if (!epoll_controller_addmonitor(self, &fd_handle, (uint32_t)fd, info))
				result = -EEXIST;
			break;
	
		case EPOLL_CTL_MOD:
			validate_readable(info, sizeof(*info));
			if (!epoll_controller_modmonitor(self, &fd_handle, (uint32_t)fd, info))
				result = -ENOENT;
			break;
	
		case EPOLL_CTL_DEL:
			if (!epoll_controller_delmonitor(self, &fd_handle, (uint32_t)fd))
				result = -ENOENT;
			break;
	
		default:
			THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND,
			      E_INVALID_ARGUMENT_CONTEXT_EPOLL_CTL_OP,
			      op);
		}
	} EXCEPT {
		decref(fd_handle);
		RETHROW();
	}
	decref(fd_handle);
	return result;
}
#endif /* __ARCH_WANT_SYSCALL_EPOLL_CTL */

#ifdef __ARCH_WANT_SYSCALL_EPOLL_WAIT
DEFINE_SYSCALL4(ssize_t, epoll_wait,
                fd_t, epfd, USER UNCHECKED struct epoll_event *, events,
                size_t, maxevents, syscall_slong_t, timeout) {
	size_t result;
	REF struct epoll_controller *self;
	validate_writablem(events, maxevents, sizeof(struct epoll_event));
	self = handle_get_epoll_controller(epfd);
	FINALLY_DECREF_UNLIKELY(self);
	if unlikely(maxevents <= 0) {
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_EPOLL_WAIT_ZERO_MAXEVENTS,
		      maxevents);
	}
	if (timeout < 0) {
		result = epoll_controller_wait(self, events, maxevents);
	} else if (timeout == 0) {
		result = epoll_controller_trywait(self, events, maxevents);
	} else {
		ktime_t then = ktime();
		then += relktime_from_milliseconds((syscall_ulong_t)timeout);
		result = epoll_controller_wait(self, events, maxevents, then);
	}
	return (ssize_t)result;
}
#endif /* __ARCH_WANT_SYSCALL_EPOLL_WAIT */






DECL_END

#endif /* !GUARD_KERNEL_SRC_SCHED_EPOLL_C */
