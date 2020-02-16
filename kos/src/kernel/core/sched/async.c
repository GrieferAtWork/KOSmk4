/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_SRC_SCHED_ASYNC_C
#define GUARD_KERNEL_SRC_SCHED_ASYNC_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/except.h>
#include <kernel/handle.h>
#include <kernel/malloc.h>
#include <kernel/paging.h>
#include <kernel/types.h>
#include <misc/atomic-ref.h>
#include <sched/async.h>
#include <sched/signal.h>
#include <sched/task.h>

#include <hybrid/atomic.h>

#include <assert.h>
#include <string.h>

DECL_BEGIN

#ifndef CONFIG_NO_SMP
#define IF_SMP(...) __VA_ARGS__
#else /* !CONFIG_NO_SMP */
#define IF_SMP(...) /* nothing */
#endif /* CONFIG_NO_SMP */

struct aworker {
	WEAK refcnt_t                 aw_refcnt; /* Reference counter */
	struct async_worker_callbacks aw_cb;     /* [const] Worker callbacks */
	WEAK void                    *aw_obj;    /* [0..1][lock(CLEAR_ONCE && SMP(aw_inuse))] Object pointer.
	                                          * When set to NULL, this worker may be removed */
	uintptr_half_t                aw_typ;    /* [const] Object type (one of `HANDLE_TYPE_*'). */
	uintptr_half_t               _aw_pad;    /* ... */
#ifndef CONFIG_NO_SMP
	uintptr_t                     aw_inuse;  /* # of CPUs using `aw_obj' right now. */
#endif /* !CONFIG_NO_SMP */
};

#define aworker_decref_obj(self, obj) \
	(*handle_type_db.h_decref[(self)->aw_typ])(obj);

DEFINE_REFCOUNT_FUNCTIONS(struct aworker, aw_refcnt, kfree)

#define aworker_eq(self, cb, obj, typ)           \
	((self)->aw_cb.awc_work == (cb)->awc_work && \
	 ATOMIC_READ((self)->aw_obj) == (obj) &&     \
	 (self)->aw_cb.awc_poll == (cb)->awc_poll && \
	 (self)->aw_cb.awc_test == (cb)->awc_test && \
	 (self)->aw_typ == (typ) &&                  \
	 (self)->aw_cb.awc_time == (cb)->awc_time)

LOCAL NOBLOCK bool
NOTHROW(FCALL aworker_clearobj)(struct aworker *__restrict self) {
	void *old_value;
#ifdef CONFIG_NO_SMP
	pflag_t was = PREEMPTION_PUSHOFF();
#endif /* CONFIG_NO_SMP */
	old_value = ATOMIC_XCH(self->aw_obj, NULL);
#ifndef CONFIG_NO_SMP
	while (ATOMIC_READ(self->aw_inuse))
		task_tryyield_or_pause();
#else /* !CONFIG_NO_SMP */
	PREEMPTION_POP(was);
#endif /* CONFIG_NO_SMP */
	return old_value != NULL;
}

LOCAL WUNUSED NONNULL((1)) /*nullable*/ REF void *
NOTHROW(FCALL aworker_getref)(struct aworker *__restrict self) {
	REF void *result;
	PREEMPTION_DISABLE();
	IF_SMP(ATOMIC_FETCHINC(self->aw_inuse));
	COMPILER_READ_BARRIER();
	result = self->aw_obj;
	COMPILER_READ_BARRIER();
	/* Try to acquire a reference. */
	if (likely(result) && unlikely(!(*handle_type_db.h_tryincref[self->aw_typ])(result)))
		result = NULL;
	IF_SMP(ATOMIC_FETCHDEC(self->aw_inuse));
	PREEMPTION_ENABLE();
	return result;
}

LOCAL NONNULL((1, 2)) bool
NOTHROW(FCALL aworker_calltest)(struct aworker *__restrict self,
                                void *__restrict obj) {
	bool result;
	TRY {
		result = (*self->aw_cb.awc_test)(obj);
	} EXCEPT {
		error_printf("aworker:test@%p(%p:%#x)",
		             self->aw_cb.awc_test, obj,
		             (unsigned int)self->aw_typ);
		result = false;
	}
	return result;
}

LOCAL NONNULL((1, 2)) bool
NOTHROW(FCALL aworker_callpoll)(struct aworker *__restrict self,
                                void *__restrict obj) {
	bool result;
	TRY {
		result = (*self->aw_cb.awc_poll)(obj, (void *)self);
	} EXCEPT {
		error_printf("aworker:poll@%p(%p:%#x)",
		             self->aw_cb.awc_poll, obj,
		             (unsigned int)self->aw_typ);
		result = false;
	}
	return result;
}

LOCAL NONNULL((1, 2)) void
NOTHROW(FCALL aworker_callwork)(struct aworker *__restrict self,
                                void *__restrict obj) {
	TRY {
		(*self->aw_cb.awc_work)(obj);
	} EXCEPT {
		error_printf("aworker:poll@%p(%p:%#x)",
		             self->aw_cb.awc_work, obj,
		             (unsigned int)self->aw_typ);
	}
}

LOCAL NONNULL((1, 2)) void
NOTHROW(FCALL aworker_calltime)(struct aworker *__restrict self,
                                void *__restrict obj) {
	TRY {
		(*self->aw_cb.awc_time)(obj);
	} EXCEPT {
		error_printf("aworker:time@%p(%p:%#x)",
		             self->aw_cb.awc_time, obj,
		             (unsigned int)self->aw_typ);
	}
}



struct awork_vector {
	WEAK refcnt_t                                 av_refcnt; /* Reference counter. */
	size_t                                        av_testc;  /* # of worker threads with test-callbacks.
	                                                           * All such workers come before those without! */
	size_t                                        av_workc;  /* # of worker threads. */
	COMPILER_FLEXIBLE_ARRAY(REF struct aworker *, av_workv); /* [0..awc_workc] Vector of workers */
};

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL awork_vector_destroy)(struct awork_vector *__restrict self) {
	size_t i;
	for (i = 0; i < self->av_workc; ++i)
		decref_unlikely(self->av_workv[i]);
	kfree(self);
}

DEFINE_REFCOUNT_FUNCTIONS(struct awork_vector, av_refcnt, awork_vector_destroy)

PRIVATE struct awork_vector empty_awork = {
	/* .aws_refcnt = */ 2, /* +1: empty_awork; +1: awork */
	/* .awc_testc  = */ 0, /* No workers defined by default... */
	/* .awc_workc  = */ 0  /* No workers defined by default... */
};

/* Registered async work. */
PRIVATE ATOMIC_REF(struct awork_vector) awork = ATOMIC_REF_INIT(&empty_awork);

/* Signal broadcast when `awork' has changed. */
PRIVATE struct sig awork_changed = SIG_INIT;

#define TRY_DELETE_ASYNC_WORKER_SUCCESS  0 /* Success */
#define TRY_DELETE_ASYNC_WORKER_BADALLOC 1 /* Failed to allocate a new set of workers */
#define TRY_DELETE_ASYNC_WORKER_CHANGED  2 /* `old_workers' differed from the active set of workers. */

/* Try to delete a worker from `old_workers' and assign atomically
 * update the global set of active async workers. */
PRIVATE NOBLOCK_IF(gfp_flags & GFP_ATOMIC) NONNULL((1)) unsigned int
NOTHROW(KCALL try_delete_async_worker)(struct awork_vector *__restrict old_workers,
                                       size_t worker_index, gfp_t gfp_flags) {
	REF struct awork_vector *new_workers;
	assert(worker_index < old_workers->av_workc);
	if (old_workers->av_workc == 1) {
		/* Simple case: Just assign the empty workers list. */
		new_workers = incref(&empty_awork);
	} else {
		size_t i;
		assert(old_workers->av_workc >= 2);
		new_workers = (REF struct awork_vector *)kmalloc_nx(offsetof(struct awork_vector, av_workv) +
		                                                    ((old_workers->av_workc - 1) *
		                                                     sizeof(REF struct aworker *)),
		                                                    gfp_flags);
		if unlikely(!new_workers)
			return TRY_DELETE_ASYNC_WORKER_BADALLOC;
		new_workers->av_refcnt = 1;
		new_workers->av_testc  = old_workers->av_testc;
		new_workers->av_workc  = old_workers->av_workc - 1;
		if (worker_index < new_workers->av_testc)
			--new_workers->av_testc; /* The to-be-removed worker had a test-function */
		memcpy(new_workers->av_workv,
		       old_workers->av_workv,
		       worker_index,
		       sizeof(REF struct aworker *));
		memcpy(new_workers->av_workv + worker_index,
		       old_workers->av_workv + worker_index + 1,
		       old_workers->av_workc - worker_index,
		       sizeof(REF struct aworker *));
		for (i = 0; i < new_workers->av_workc; ++i)
			incref(new_workers->av_workv[i]);
	}
	/* Try to exchange the global async workers vector. */
	if (awork.cmpxch_inherit_new(old_workers, new_workers))
		return TRY_DELETE_ASYNC_WORKER_SUCCESS; /* success! */
	/* The async workers vector was changed in the mean time. */
	decref_likely(new_workers);
	return TRY_DELETE_ASYNC_WORKER_CHANGED;
}



/* [lock(PRIVATE(_asyncwork))] Timeout storage for `asyncmain_timeout_p' */
PRIVATE struct timespec asyncmain_timeout = { 0, 0 };

/* [lock(PRIVATE(_asyncwork))][0..1] The timeout argument
 * for the async worker main `task_waitfor()' function */
PRIVATE struct timespec *asyncmain_timeout_p = NULL;

/* [0..1] The worker who's timeout callback should
 * be invoked when `asyncmain_timeout_p' expires. */
PRIVATE XATOMIC_REF(struct aworker) asyncmain_timeout_worker = XATOMIC_REF_INIT(NULL);


/* This function may be called by `awc_poll()'-callbacks to
 * specify the realtime() timestamp when `awc_time()' should
 * be invoked. The given `cookie' must be the same argument
 * prviously passed to `awc_poll()' */
PUBLIC NOBLOCK NONNULL((1, 2)) void
NOTHROW(ASYNC_CALLBACK_CC async_worker_timeout)(struct timespec const *__restrict abs_timeout,
                                                void *__restrict cookie) {
	struct aworker *w;
	w = (struct aworker *)cookie;
	assertf(THIS_TASK == &_asyncwork, "This function may only be called by async-worker-poll-callbacks");
	assertf(w && ADDR_ISKERN(w) && !wasdestroyed(w), "Bad cookie");
	assertf(w->aw_cb.awc_time, "No time-callback");
	if (!asyncmain_timeout_p) {
		asyncmain_timeout_p = &asyncmain_timeout;
	} else {
		assert(asyncmain_timeout_p == &asyncmain_timeout);
		if (*abs_timeout >= asyncmain_timeout)
			return; /* The previous timeout is already older! */
	}
	/* Set the used timeout. */
	asyncmain_timeout = *abs_timeout;
	/* Set the associated worker as the one that will receive the timeout. */
	asyncmain_timeout_worker.set(w);
}



INTERN ATTR_NORETURN void
NOTHROW(FCALL _asyncmain)(void) {
	for (;;) {
		size_t i;
		REF struct awork_vector *workers;
again:
		assert(PREEMPTION_ENABLED());
		assert(!task_isconnected());
		PREEMPTION_DISABLE();
		workers = awork.get_nopr();
		PREEMPTION_ENABLE();
		/* First pass: test() for work and service immediatly if present. */
		for (i = 0; i < workers->av_testc; ++i) {
			struct aworker *w;
			REF void *obj;
			w = workers->av_workv[i];
			assert(w->aw_cb.awc_test);
			PREEMPTION_DISABLE();
			IF_SMP(ATOMIC_FETCHINC(w->aw_inuse));
			COMPILER_READ_BARRIER();
			obj = w->aw_obj;
			COMPILER_READ_BARRIER();
			if unlikely(!obj) {
				unsigned int error;
				IF_SMP(ATOMIC_FETCHDEC(w->aw_inuse));
				PREEMPTION_ENABLE();
				error = try_delete_async_worker(workers, i, GFP_NORMAL);
				if (error == TRY_DELETE_ASYNC_WORKER_SUCCESS ||
				    error == TRY_DELETE_ASYNC_WORKER_CHANGED) {
					decref_likely(workers);
					goto again;
				}
				continue;
			}
			/* Try to acquire a reference. */
			if unlikely(!(*handle_type_db.h_tryincref[w->aw_typ])(obj)) {
				IF_SMP(ATOMIC_FETCHDEC(w->aw_inuse));
				PREEMPTION_ENABLE();
				continue; /* Skip dead objects. */
			}
			IF_SMP(ATOMIC_FETCHDEC(w->aw_inuse));
			PREEMPTION_ENABLE();
			assert(!task_isconnected());
			if (aworker_calltest(w, obj)) {
				assert(!task_isconnected());
				/* Service this worker. */
				aworker_callwork(w, obj);
				assert(!task_isconnected());
				/* TODO: Do automatic re-ordering of async workers based on how often
				 *       they are being triggered. (workers that have work more often
				 *       should come before those that have less often) */
			}
			aworker_decref_obj(w, obj);
		}
		/* Second pass: poll() for work and service if available. */
		for (i = 0; i < workers->av_workc; ++i) {
			struct aworker *w;
			REF void *obj;
			w = workers->av_workv[i];
			PREEMPTION_DISABLE();
			IF_SMP(ATOMIC_FETCHINC(w->aw_inuse));
			COMPILER_READ_BARRIER();
			obj = w->aw_obj;
			COMPILER_READ_BARRIER();
			if unlikely(!obj) {
				unsigned int error;
				IF_SMP(ATOMIC_FETCHDEC(w->aw_inuse));
				PREEMPTION_ENABLE();
				error = try_delete_async_worker(workers, i, GFP_NORMAL);
				if (error == TRY_DELETE_ASYNC_WORKER_SUCCESS ||
				    error == TRY_DELETE_ASYNC_WORKER_CHANGED) {
					decref_likely(workers);
					goto again;
				}
				continue;
			}
			/* Try to acquire a reference. */
			if unlikely(!(*handle_type_db.h_tryincref[w->aw_typ])(obj)) {
				IF_SMP(ATOMIC_FETCHDEC(w->aw_inuse));
				PREEMPTION_ENABLE();
				continue; /* Skip dead objects. */
			}
			IF_SMP(ATOMIC_FETCHDEC(w->aw_inuse));
			PREEMPTION_ENABLE();
			if (aworker_callpoll(w, obj)) {
				/* Service this worker. */
				task_disconnectall();
				aworker_callwork(w, obj);
				aworker_decref_obj(w, obj);
				decref_unlikely(workers);
				goto again;
			}
			aworker_decref_obj(w, obj);
		}

		{
			struct task_connection awork_changed_con;
			struct sig *received_signal;
			/* Also wait for async workers to have changed. */
			task_connect_c(&awork_changed_con, &awork_changed);
			TRY {
				received_signal = task_waitfor(asyncmain_timeout_p);
			} EXCEPT {
				error_printf("_asyncmain:task_waitfor()");
			}
			decref_unlikely(workers);
			if (!received_signal) {
				REF struct aworker *receiver;
				/* A timeout expired. (invoke the associated worker's time-callback) */
				assert(asyncmain_timeout_p);
				asyncmain_timeout_p = NULL;
				receiver = asyncmain_timeout_worker.exchange(NULL);
				if likely(receiver) {
					REF void *obj;
					assert(receiver->aw_cb.awc_time);
					obj = aworker_getref(receiver);
					if likely(obj) {
						aworker_calltime(receiver, obj);
						aworker_decref_obj(receiver, obj);
					}
					decref_unlikely(receiver);
				}
			}
		}
	}
}


/* Register an async worker callback.
 * NOTE: All callbacks should be non-blocking in that they mustn't wait for
 *       work to become available themself (that's what `poll()' is for, such
 *       that a single thread can wait for async work to become available for
 *       _all_ async workers)
 * @param: cb:         Callbacks for the async worker being registered.
 *                     NOTE: The backing storage of the `cb' container itself
 *                           doesn't need to be persistent! It only needs to
 *                           remain valid until this function returns!
 * @param: ob_pointer: A pointer to a handle data object. The destructor of this
 *                     object is responsible for invoking `unregister_async_worker()'
 *                     Callbacks will no longer be invoked if this object's
 *                     reference counter has reached 0, however the object's
 *                     destructor must still unregister the callbacks before
 *                     the memory used to back its reference counter is free()d!
 * @param: ob_type:    The object type for `ob_pointer' (one of `HANDLE_TYPE_*')
 * @return: true:      Successfully registered a new async worker.
 * @return: false:     An async worker for the given object/callback combination
 *                     was already registered. */
PUBLIC NONNULL((1, 2)) bool KCALL
register_async_worker(struct async_worker_callbacks const *__restrict cb,
                      void *__restrict ob_pointer, uintptr_half_t ob_type)
		THROWS(E_BADALLOC) {
	REF struct aworker *new_worker;
	REF struct awork_vector *old_workers;
	REF struct awork_vector *new_workers;
	size_t i;
	assert(cb);
	assert(cb->awc_poll);
	assert(cb->awc_work);
	assert(ob_pointer);
	assert(ob_type < HANDLE_TYPE_COUNT);
again:
	old_workers = awork.get();
	/* Check if this worker has already been defined. */
	{
		size_t c;
		i = 0;
		c = old_workers->av_testc;
		if (!cb->awc_test) {
			i = c;
			c = old_workers->av_workc;
		}
		for (; i < c; ++i) {
			if (aworker_eq(old_workers->av_workv[i],
			               cb, ob_pointer, ob_type))
				return false; /* Already defined. */
		}
	}
	TRY {
		/* Allocate enough space for +1 additional worker. */
		new_workers = (REF struct awork_vector *)kmalloc(offsetof(struct awork_vector, av_workv) +
		                                                 (old_workers->av_workc + 1) *
		                                                 sizeof(struct aworker),
		                                                 GFP_NORMAL);
		TRY {
			new_worker = (REF struct aworker *)kmalloc(sizeof(struct aworker), GFP_NORMAL);
		} EXCEPT {
			kfree(new_workers);
			RETHROW();
		}
	} EXCEPT {
		decref_unlikely(old_workers);
		RETHROW();
	}

	/* Initialize the new worker */
	new_worker->aw_refcnt = 1;
	memcpy(&new_worker->aw_cb, cb, sizeof(*cb));
	new_worker->aw_obj = ob_pointer;
	new_worker->aw_typ = ob_type;
	IF_SMP(new_worker->aw_inuse = 0);

	/* Fill in the new workers vector. */
	new_workers->av_refcnt = 1;
	new_workers->av_testc  = old_workers->av_testc;
	new_workers->av_workc  = old_workers->av_workc + 1;
	if (cb->awc_test) {
		/* Insert `new_worker' at the front */
		++new_workers->av_testc;
		memcpy(new_workers->av_workv + 1,
		       old_workers->av_workv,
		       old_workers->av_workc,
		       sizeof(REF struct aworker *));
		new_workers->av_workv[0] = new_worker;
	} else {
		/* Insert `new_worker' after test-enabled workers */
		memcpy(new_workers->av_workv,
		       old_workers->av_workv,
		       old_workers->av_testc,
		       sizeof(REF struct aworker *));
		new_workers->av_workv[old_workers->av_testc] = new_worker; /* Inherit reference. */
		memcpy(new_workers->av_workv + old_workers->av_testc + 1,
		       old_workers->av_workv + old_workers->av_testc,
		       old_workers->av_workc - old_workers->av_testc,
		       sizeof(REF struct aworker *));
	}

	/* Try to install the new async workers vector. */
	if (awork.cmpxch_inherit_new(old_workers, new_workers)) {
		decref_likely(old_workers);
		/* Indicate that workers have changed. */
		sig_broadcast(&awork_changed);
		return true;
	}
	/* The old set of workers has changed -> try again! */
	decref_likely(new_workers);
	decref_likely(old_workers);
	goto again;
}

/* Delete a previously defined async worker, using the same arguments as those
 * previously passed to `register_async_worker()'. This function should be
 * called from the destructor of `ob_pointer'
 * @param: cb:     Callbacks for the async worker being unregistered.
 *                 NOTE: The backing storage of the `cb' container itself
 *                       doesn't need to be persistent! It only needs to
 *                       remain valid until this function returns!
 * @return: true:  Successfully deleted an async worker for the
 *                 given object/callback combination.
 * @return: false: No async worker for the given object/callback
 *                 combination had been registered. */
PUBLIC NOBLOCK NONNULL((1, 2)) bool
NOTHROW(KCALL unregister_async_worker)(struct async_worker_callbacks const *__restrict cb,
                                       void *__restrict ob_pointer, uintptr_half_t ob_type) {
	REF struct awork_vector *workers;
	size_t i, count;
	assert(cb);
	assert(cb->awc_poll);
	assert(cb->awc_work);
	assert(ob_pointer);
	assert(ob_type < HANDLE_TYPE_COUNT);
	workers = awork.get();
	/* Figure out which parts of the worker-vector we need to search. */
	i     = 0;
	count = workers->av_testc;
	if (!cb->awc_test) {
		i     = count;
		count = workers->av_workc;
	}
	for (; i < count; ++i) {
		struct aworker *w;
		w = workers->av_workv[i];
		/* Check if this is the worker we're looking for. */
		if (aworker_eq(w, cb, ob_pointer, ob_type)) {
			bool result;
			/* Try to clear the worker's pointed-to object. */
			result = aworker_clearobj(w);
			/* Always try to remove the worker. */
			try_delete_async_worker(workers, i, GFP_ATOMIC);
			decref_likely(workers);
			return result;
		}
	}
	/* The worker wasn't found (or it was deleted during a prior pass) */
	decref_unlikely(workers);
	return false;
}

DECL_END

#endif /* !GUARD_KERNEL_SRC_SCHED_ASYNC_C */
