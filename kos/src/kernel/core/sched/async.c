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
#ifndef GUARD_KERNEL_SRC_SCHED_ASYNC_C
#define GUARD_KERNEL_SRC_SCHED_ASYNC_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/aio.h>
#include <kernel/driver.h>
#include <kernel/except.h>
#include <kernel/handle.h>
#include <kernel/malloc.h>
#include <kernel/paging.h>
#include <kernel/printk.h>
#include <kernel/types.h>
#include <misc/atomic-ref.h>
#include <sched/async.h>
#include <sched/signal.h>
#include <sched/task.h>

#include <hybrid/atomic.h>
#include <hybrid/minmax.h>

#include <assert.h>
#include <inttypes.h>
#include <stdalign.h>
#include <stddef.h>
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
	 (self)->aw_typ == (typ))

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
	IF_SMP(ATOMIC_INC(self->aw_inuse));
	COMPILER_READ_BARRIER();
	result = self->aw_obj;
	COMPILER_READ_BARRIER();
	/* Try to acquire a reference. */
	if (likely(result) && unlikely(!(*handle_type_db.h_tryincref[self->aw_typ])(result)))
		result = NULL;
	IF_SMP(ATOMIC_DEC(self->aw_inuse));
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

/* [lock(PRIVATE(_asyncwork))][1..1]
 * [valid_if(asyncmain_timeout_worker != NULL)]
 * The timeout callback to-be invoked when the timeout expires. */
PRIVATE async_worker_timeout_t asyncmain_timeout_cb = NULL;


/* This function may be called by `awc_poll()'-callbacks to
 * specify the realtime() timestamp when `awc_time()' should
 * be invoked. The given `cookie' must be the same argument
 * prviously passed to `awc_poll()' */
PUBLIC NOBLOCK NONNULL((1, 2, 3)) void
NOTHROW(ASYNC_CALLBACK_CC async_worker_timeout)(struct timespec const *__restrict abs_timeout,
                                                void *__restrict cookie,
                                                async_worker_timeout_t on_timeout) {
	struct aworker *w;
	w = (struct aworker *)cookie;
	assertf(THIS_TASK == &_asyncwork, "This function may only be called by async-worker-poll-callbacks");
	assertf(abs_timeout && ADDR_ISKERN(abs_timeout), "Bad timeout argument");
	assertf(on_timeout && ADDR_ISKERN((void *)on_timeout), "Bad on_timeout callback");
	assertf(w && ADDR_ISKERN(w) && !wasdestroyed(w), "Bad cookie");
	if (!asyncmain_timeout_p) {
		asyncmain_timeout_p = &asyncmain_timeout;
	} else {
		assert(asyncmain_timeout_p == &asyncmain_timeout);
		if (*abs_timeout >= asyncmain_timeout)
			return; /* The previous timeout is already older! */
	}
	/* Set the used timeout. */
	asyncmain_timeout = *abs_timeout;
	asyncmain_timeout_cb = on_timeout;
	/* Set the associated worker as the one that will receive the timeout. */
	asyncmain_timeout_worker.set(w);
}


/* @return: true:  Previously connected signals have been disconnected.
 * @return: false: Move onto the step of waiting for something to happen. */
PRIVATE bool NOTHROW(FCALL _asyncjob_main)(void);

INTERN ATTR_NORETURN void
NOTHROW(FCALL _asyncmain)(void) {
	for (;;) {
		size_t i;
		REF struct awork_vector *workers;
again:
		assert(PREEMPTION_ENABLED());
		assert(!task_wasconnected());
		PREEMPTION_DISABLE();
		workers = awork.get_nopr();
		PREEMPTION_ENABLE();
		/* First pass: test() for work and service immediately if present. */
		for (i = 0; i < workers->av_testc; ++i) {
			struct aworker *w;
			REF void *obj;
			w = workers->av_workv[i];
			assert(w->aw_cb.awc_test);
			PREEMPTION_DISABLE();
			IF_SMP(ATOMIC_INC(w->aw_inuse));
			COMPILER_READ_BARRIER();
			obj = w->aw_obj;
			COMPILER_READ_BARRIER();
			if unlikely(!obj) {
				unsigned int error;
				IF_SMP(ATOMIC_DEC(w->aw_inuse));
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
				IF_SMP(ATOMIC_DEC(w->aw_inuse));
				PREEMPTION_ENABLE();
				continue; /* Skip dead objects. */
			}
			IF_SMP(ATOMIC_DEC(w->aw_inuse));
			PREEMPTION_ENABLE();
			assert(!task_wasconnected());
			if (aworker_calltest(w, obj)) {
				assert(!task_wasconnected());
				/* Service this worker. */
				aworker_callwork(w, obj);
				assert(!task_wasconnected());
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
			IF_SMP(ATOMIC_INC(w->aw_inuse));
			COMPILER_READ_BARRIER();
			obj = w->aw_obj;
			COMPILER_READ_BARRIER();
			if unlikely(!obj) {
				unsigned int error;
				IF_SMP(ATOMIC_DEC(w->aw_inuse));
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
				IF_SMP(ATOMIC_DEC(w->aw_inuse));
				PREEMPTION_ENABLE();
				continue; /* Skip dead objects. */
			}
			IF_SMP(ATOMIC_DEC(w->aw_inuse));
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
		decref_unlikely(workers);
		/* Service async jobs. */
		if (_asyncjob_main()) {
			task_disconnectall();
			goto again;
		}
		{
			struct sig *received_signal;
			/* Also wait for async workers to have changed. */
			TRY {
				task_connect_for_poll(&awork_changed);
				received_signal = task_waitfor_tms(asyncmain_timeout_p);
			} EXCEPT {
				task_disconnectall();
				error_printf("_asyncmain:task_waitfor()");
				goto again;
			}
			if (!received_signal) {
				REF struct aworker *receiver;
				/* A timeout expired. (invoke the associated worker's time-callback) */
				assert(asyncmain_timeout_p);
				asyncmain_timeout_p = NULL;
				receiver = asyncmain_timeout_worker.exchange(NULL);
				if likely(receiver) {
					REF void *obj;
					obj = aworker_getref(receiver);
					if likely(obj) {
						TRY {
							(*asyncmain_timeout_cb)(obj);
						} EXCEPT {
							error_printf("aworker:time@%p(%p:%#x)",
							             asyncmain_timeout_cb, obj,
							             (unsigned int)receiver->aw_typ);
						}
						aworker_decref_obj(receiver, obj);
					}
					decref_unlikely(receiver);
				}
			} else if (received_signal == &awork_changed) {
				/* If workers have changed, clear any defined timeout. */
				asyncmain_timeout_p = NULL;
				asyncmain_timeout_worker.clear();
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
	/* Acquire references to all of the old workers. */
	for (i = 0; i < old_workers->av_workc; ++i)
		incref(old_workers->av_workv[i]);

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

			/* If this worker is currently set as the timeout
			 * receiver, then remove it from that position. */
			asyncmain_timeout_worker.cmpxch_inherit_new(w, NULL);

			/* Always try to remove the worker. */
			try_delete_async_worker(workers, i, GFP_ATOMIC);
			decref_likely(workers);

			/* Indicate that workers have changed. */
			sig_broadcast(&awork_changed);
			return result;
		}
	}
	/* The worker wasn't found (or it was deleted during a prior pass) */
	decref_unlikely(workers);
	return false;
}















/************************************************************************/
/* ASYNC_JOB API                                                        */
/************************************************************************/

/* Special values for `async_job::aj_aio' */
#define ASYNC_JOB_AIO_NONPRESENT ((struct aio_handle *)0)  /* No AIO attached to this job, or AIO has already been triggered */
#define ASYNC_JOB_AIO_CANCELED   ((struct aio_handle *)-1) /* The async job has been canceled. */
#if 1
#define ASYNC_JOB_AIO_ISSPEC(x)    ((x) == ASYNC_JOB_AIO_CANCELED)
#else
#define ASYNC_JOB_AIO_ISSPEC(x)    ((uintptr_t)(x) >= (uintptr_t)-1)
#endif
#define ASYNC_JOB_AIO_ISPRESENT(x) (((uintptr_t)(x)-1) < (uintptr_t)-2)

struct async_job {
	REF struct async_job             *aj_next;   /* [0..1][lock(PRIVATE(ASYNC_WORKER))] Next async job. */
	struct async_job_callbacks const *aj_ops;    /* [1..1][const] Async job callbacks.
	                                              * NOTE: This field also holds a reference to `aj_ops->jc_driver' */
	WEAK struct aio_handle           *aj_aio;    /* [0..1][lock(CLEAR_ONCE)] Attached AIO and job cancellation indicator. */
	WEAK refcnt_t                     aj_refcnt; /* Reference counter.
	                                              * WARNING: This function _must_ always be located at the end of this structure!
	                                              *          This placement is part of the ABI (s.a. `async_job_refcnt()') */
};

/* [0..1][lock(INSERT(ATOMIC), REMOVE(PRIVATE(ASYNC_WORKER)))]
 * Chain of active async-jobs. */
PRIVATE ATTR_READMOSTLY REF struct async_job *WEAK async_jobs = NULL;

/* [?..1] The async job currently configured to receive timeouts. */
PRIVATE struct async_job *async_job_current_timeout = NULL;

PRIVATE NONNULL((1)) void ASYNC_CALLBACK_CC
asyncjob_timeout_worker_timeout(void *__restrict UNUSED(self)) {
	unsigned int status;
	assert(async_job_current_timeout);
	/* Check for `ASYNC_JOB_AIO_CANCELED' and call jc_cancel that's what happened. */
	if (ATOMIC_READ(async_job_current_timeout->aj_aio) == ASYNC_JOB_AIO_CANCELED) {
		if (async_job_current_timeout->aj_ops->jc_cancel) {
			TRY {
				(*async_job_current_timeout->aj_ops->jc_cancel)(async_job_current_timeout + 1);
			} EXCEPT {
				error_printf("ajob:cancel@%p(%p)",
				             async_job_current_timeout->aj_ops->jc_cancel,
				             async_job_current_timeout + 1);
			}
		}
		goto do_delete_job;
	}
	TRY {
		status = (*async_job_current_timeout->aj_ops->jc_time)(async_job_current_timeout + 1);
	} EXCEPT {
		struct aio_handle *aio;
		/* Signal AIO completion with error. */
		PREEMPTION_DISABLE();
		aio = ATOMIC_XCH(async_job_current_timeout->aj_aio,
		                 ASYNC_JOB_AIO_NONPRESENT);
		if (ASYNC_JOB_AIO_ISPRESENT(aio)) {
			aio_handle_complete_nopr(aio, AIO_COMPLETION_FAILURE);
			PREEMPTION_ENABLE();
		} else {
			PREEMPTION_ENABLE();
			/* Log an exception that's going to be discarded. */
			error_printf("ajob:time@%p(%p)",
			             async_job_current_timeout->aj_ops->jc_time,
			             async_job_current_timeout + 1);
		}
		goto do_delete_job;
	}
	if (status == ASYNC_JOB_WORK_COMPLETE) {
		struct async_job **pjob, *job;
do_delete_job:
		/* Delete this job. */
		pjob = &async_jobs;
		job  = ATOMIC_READ(async_jobs);
		for (;;) {
			assert(job);
			if (job == async_job_current_timeout)
				break;
			pjob = &job->aj_next;
			job  = *pjob;
		}
		if unlikely(!ATOMIC_CMPXCH(*pjob, job, job->aj_next)) {
			/* This can happen when `pjob == &async_jobs',
			 * and new jobs have been added in the mean time. */
			struct async_job *prev;
			assert(pjob == &async_jobs);
			prev = ATOMIC_READ(async_jobs);
			for (;;) {
				assert(prev);
				if (prev->aj_next == job)
					break;
				prev = prev->aj_next;
			}
			ATOMIC_WRITE(prev->aj_next, job->aj_next);
		}
		/* Drop our reference to the job, which will likely destroy it. */
		decref_likely(job + 1);
	}
}


PRIVATE NONNULL((1, 2)) bool ASYNC_CALLBACK_CC
asyncjob_timeout_worker_poll(void *__restrict UNUSED(self),
                             void *__restrict UNUSED(cookie)) {
	/* Should never be called */
	return false;
}

PRIVATE NONNULL((1)) void ASYNC_CALLBACK_CC
asyncjob_timeout_worker_work(void *__restrict UNUSED(self)) {
	/* Should never be called */
}

/* A stub async-worker that's used for async-job timeouts */
PRIVATE struct aworker asyncjob_timeout_worker = {
	/* .aw_refcnt = */ 1, /* +1: asyncjob_timeout_worker */
	/* .aw_cb     = */ {
		/* .awc_poll = */ &asyncjob_timeout_worker_poll,
		/* .awc_work = */ &asyncjob_timeout_worker_work,
		/* .awc_test = */ NULL
	},
	/* .aw_obj   = */ &drv_self,
	/* .aw_typ   = */ HANDLE_TYPE_DRIVER,
	/* ._aw_pad  = */ 0
#ifndef CONFIG_NO_SMP
	,
	/* .aw_inuse = */ 0
#endif /* !CONFIG_NO_SMP */
};


/* Passed to async-job poll() functions as timeout argument. */
PRIVATE struct timespec asyncjob_main_timeout = { 0, 0 };

/* @return: true:  Previously connected signals have been disconnected.
 * @return: false: Move onto the step of waiting for something to happen. */
PRIVATE bool NOTHROW(FCALL _asyncjob_main)(void) {
	struct async_job **pjob, *job;
	bool result = false;
	pjob = &async_jobs;
	job  = ATOMIC_READ(async_jobs);
handle_job:
	while (job) {
		struct aio_handle *state;
		state = ATOMIC_READ(job->aj_aio);
		if unlikely(ASYNC_JOB_AIO_ISSPEC(state)) {
			/* Special state handling. */
			if (state == ASYNC_JOB_AIO_CANCELED) {
				/* Invoke the cancellation callback. */
				if (job->aj_ops->jc_cancel) {
					result = true;
					task_disconnectall();
					TRY {
						(*job->aj_ops->jc_cancel)(job + 1);
					} EXCEPT {
						error_printf("ajob:cancel@%p(%p)",
						             job->aj_ops->jc_cancel,
						             job + 1);
					}
				}
				goto do_delete_job;
			}
		} else {
			/* Normal operations: poll()+work() if available. */
			unsigned int pollcode;
			TRY {
				pollcode = (*job->aj_ops->jc_poll)(job + 1, &asyncjob_main_timeout);
			} EXCEPT {
				struct aio_handle *aio;
				/* Signal AIO completion with error. */
				result = true;
				task_disconnectall();
				PREEMPTION_DISABLE();
				aio = ATOMIC_XCH(job->aj_aio, ASYNC_JOB_AIO_NONPRESENT);
				if (ASYNC_JOB_AIO_ISPRESENT(aio)) {
					aio_handle_complete_nopr(aio, AIO_COMPLETION_FAILURE);
					PREEMPTION_ENABLE();
				} else {
					PREEMPTION_ENABLE();
					/* Log an exception that's going to be discarded. */
					error_printf("ajob:poll@%p(%p)",
					             job->aj_ops->jc_poll,
					             job + 1);
				}
				goto do_delete_job;
			}
			switch (pollcode) {

			case ASYNC_JOB_POLL_AVAILABLE: {
				unsigned int status;
				result = true;
				task_disconnectall();
				TRY {
					status = (*job->aj_ops->jc_work)(job + 1);
				} EXCEPT {
					struct aio_handle *aio;
					/* Signal AIO completion with error. */
					PREEMPTION_DISABLE();
					aio = ATOMIC_XCH(job->aj_aio, ASYNC_JOB_AIO_NONPRESENT);
					if (ASYNC_JOB_AIO_ISPRESENT(aio)) {
						aio_handle_complete_nopr(aio, AIO_COMPLETION_FAILURE);
						PREEMPTION_ENABLE();
					} else {
						PREEMPTION_ENABLE();
						/* Log an exception that's going to be discarded. */
						error_printf("ajob:work@%p(%p)",
						             job->aj_ops->jc_work,
						             job + 1);
					}
					goto do_delete_job;
				}
				if (status == ASYNC_JOB_WORK_COMPLETE) {
					struct aio_handle *aio;
					struct async_job *next;
					/* Signal successful AIO completion. */
do_delete_job_success:
					PREEMPTION_DISABLE();
					aio = ATOMIC_XCH(job->aj_aio, ASYNC_JOB_AIO_NONPRESENT);
					if (ASYNC_JOB_AIO_ISPRESENT(aio))
						aio_handle_complete_nopr(aio, AIO_COMPLETION_SUCCESS);
					PREEMPTION_ENABLE();
do_delete_job:
					/* Remove this job. */
					next = job->aj_next;
					COMPILER_READ_BARRIER();
					if unlikely(!ATOMIC_CMPXCH(*pjob, job, next)) {
						/* This can happen when `pjob == &async_jobs',
						 * and new jobs have been added in the mean time. */
						struct async_job *prev;
						assert(pjob == &async_jobs);
						prev = ATOMIC_READ(async_jobs);
						for (;;) {
							assert(prev);
							if (prev->aj_next == job)
								break;
							prev = prev->aj_next;
						}
						ATOMIC_WRITE(prev->aj_next, next);
					}
					/* Drop our reference to the job, which will likely destroy it. */
					decref_likely(job + 1);
					job = next;
					goto handle_job;
				}
			}	break;

			case ASYNC_JOB_POLL_WAITFOR: {
				assertf(job->aj_ops->jc_time,
				        "poll returned `ASYNC_JOB_POLL_WAITFOR', but "
				        "the job does not define a timeout callback!");
				/* Use the async-worker timeout mechanism to set-up
				 * a custom callback for when the timeout expires. */
				if (!asyncmain_timeout_p) {
					asyncmain_timeout_p = &asyncmain_timeout;
				} else {
					assert(asyncmain_timeout_p == &asyncmain_timeout);
					if (asyncjob_main_timeout >= asyncmain_timeout)
						break; /* The previous timeout is already older! */
				}
				/* Set the used timeout and callback routing. */
				asyncmain_timeout = asyncjob_main_timeout;
				asyncmain_timeout_cb = &asyncjob_timeout_worker_timeout;
				/* NOTE: Because only the async worker (i.e. us) is allowed to
				 *       remove async jobs, we don't even have to store a reference
				 *       to the job within `async_job_current_timeout', since the
				 *       job will always be kept alive by its entry with the
				 *       `async_jobs' chain. */
				async_job_current_timeout = job;
				/* Set the associated worker as the one that will receive the timeout. */
				asyncmain_timeout_worker.set(&asyncjob_timeout_worker);
			}	break;

			case ASYNC_JOB_POLL_WAITFOR_NOTIMEOUT:
				break;

			case ASYNC_JOB_POLL_DELETE:
				goto do_delete_job_success;

			default:
				__builtin_unreachable();
			}

		}
		pjob = &job->aj_next;
		job = *pjob;
	}
	return result;
}


/* Destroy an async-job that has previously been started (i.e. `async_job_start(self)' was called). */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL async_job_destroy)(async_job_t self) {
	struct async_job *me;
	me = self - 1;
	if (me->aj_ops->jc_fini)
		(*me->aj_ops->jc_fini)(self);
	decref_unlikely(me->aj_ops->jc_driver);
	kfree(me);
}


/* Allocate and return a new async-job with the given callbacks.
 * Note that this job hasn't been started yet, which is something
 * that will only be done once the caller invokes `async_job_start()'
 * If the job should be free()'d before that point, `async_job_free()' should be used.
 * Afterwards, the job should be considered as reference-counted, with the caller
 * of `async_job_start()' being responsible to inherit a reference to the job.
 * NOTE: The returned pointer itself points at a user-defined structure of
 *       `cb->jc_jobsize' bytes aligned on some `cb->jc_jobalign'-byte border.
 * >> struct my_job_desc *desc;
 * >> async_job_t job;
 * >> job  = async_job_alloc(&my_job);
 * >> desc = (struct my_job_desc *)job;
 * >> // Initialize the job descriptor.
 * >> desc->...;
 * >> // Start the job and inherit a reference to `job'
 * >> async_job_start(job);
 * >> // Do something else...
 * >> ...
 * >> if (should_cancel) {
 * >>     async_job_cancel(job);
 * >>     decref(job);
 * >> } else {
 * >>     decref(job);
 * >> }
 * WARNING: Unlike with async workers, the backing memory for the given `cb' must
 *          have static storage duration backed by a reference to `cb->jc_driver' */
PUBLIC ATTR_RETNONNULL WUNUSED NONNULL((1)) /*inherit*/ async_job_t FCALL
async_job_alloc(struct async_job_callbacks const *__restrict cb) {
	struct async_job *result;
	assert(cb);
	assert(cb->jc_driver);
	assert(cb->jc_poll);
	assert(cb->jc_work);
	assertf((cb->jc_jobalign & (cb->jc_jobalign - 1)) == 0,
	        "Not a pointer-of-2: %#" PRIxSIZ,
	        cb->jc_jobalign);
	result = (struct async_job *)kmemalign_offset(MAX(alignof(struct async_job), cb->jc_jobalign),
	                                              sizeof(struct async_job),
	                                              sizeof(struct async_job) + cb->jc_jobsize,
	                                              GFP_NORMAL);
	result->aj_refcnt = 2;
	result->aj_ops    = cb;
	result->aj_aio    = ASYNC_JOB_AIO_NONPRESENT;
	incref(cb->jc_driver);
#ifndef NDEBUG
	result->aj_next = (REF struct async_job *)0x1234;
#endif /* !NDEBUG */
	return result + 1;
}

/* Free a previously allocated, but not-yet started job */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL async_job_free)(async_job_t self) {
	struct async_job *me;
	me = self - 1;
	assert(me->aj_refcnt == 2);
	assert(me->aj_aio == ASYNC_JOB_AIO_NONPRESENT);
	kfree(me);
}


struct async_job_aio_data {
	REF async_job_t ajad_job; /* [1..1] A reference to the associated job.
	                           * NOTE: This points to the user-data portion! */
};
STATIC_ASSERT(sizeof(struct async_job_aio_data) <=
              AIO_HANDLE_DRIVER_POINTER_COUNT * sizeof(void *));

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL async_job_aio_fini)(struct aio_handle *__restrict self) {
	struct async_job_aio_data *data;
	data = (struct async_job_aio_data *)self->ah_data;
	decref(data->ajad_job);
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL async_job_aio_cancel)(struct aio_handle *__restrict self) {
	struct async_job_aio_data *data;
	data = (struct async_job_aio_data *)self->ah_data;
	async_job_cancel(data->ajad_job);
}

PRIVATE NOBLOCK NONNULL((1, 2)) unsigned int
NOTHROW(KCALL async_job_aio_progress)(struct aio_handle *__restrict self,
                                      struct aio_handle_stat *__restrict stat) {
	struct async_job_aio_data *data;
	struct aio_handle *aio_status;
	struct async_job *job;
	data = (struct async_job_aio_data *)self->ah_data;
	job  = data->ajad_job - 1;
	aio_status = ATOMIC_READ(job->aj_aio);
	/* Check if the operation has completed. */
	if (!ASYNC_JOB_AIO_ISPRESENT(aio_status)) {
		stat->hs_completed = 1;
		stat->hs_total     = 1;
		return AIO_PROGRESS_STATUS_COMPLETED;
	}
	if (!job->aj_ops->jc_progress) {
		stat->hs_completed = 0;
		stat->hs_total     = 1;
		return AIO_PROGRESS_STATUS_INPROGRESS;
	}
	return (*job->aj_ops->jc_progress)(job + 1, stat);
}

PRIVATE NOBLOCK WUNUSED NONNULL((1)) size_t
NOTHROW(KCALL async_job_aio_retsize)(struct aio_handle *__restrict self) {
	struct async_job_aio_data *data;
	struct aio_handle *aio_status;
	struct async_job *job;
	data = (struct async_job_aio_data *)self->ah_data;
	job  = data->ajad_job - 1;
	aio_status = ATOMIC_READ(job->aj_aio);
	assert(job->aj_ops->jc_retsize);
	/* Check if the operation has completed. */
	if (!ASYNC_JOB_AIO_ISPRESENT(aio_status))
		return 0;
	return (*job->aj_ops->jc_retsize)(job + 1);
}

PRIVATE struct aio_handle_type const async_job_aio = {
	/* .ht_fini     = */ &async_job_aio_fini,
	/* .ht_cancel   = */ &async_job_aio_cancel,
	/* .ht_progress = */ &async_job_aio_progress,
	/* .ht_retsize  = */ &async_job_aio_retsize
};

PRIVATE struct aio_handle_type const async_job_aio_noretsize = {
	/* .ht_fini     = */ &async_job_aio_fini,
	/* .ht_cancel   = */ &async_job_aio_cancel,
	/* .ht_progress = */ &async_job_aio_progress
};



/* Start the given async job, and optionally connect a given AIO handle
 * for process monitoring, job completion notification, and cancellation:
 *   - `aio_handle_cancel()' can be used to the same effect as `async_job_cancel()'
 *   - `aio->ah_func' will be invoked under the following conditions
 *     after `async_job_start()' had been called to start the async job,
 *     just after the job has been deleted:
 *     - AIO_COMPLETION_SUCCESS:
 *       - `jc_poll()' returning `ASYNC_JOB_POLL_DELETE'
 *       - `jc_work()' returning `ASYNC_JOB_WORK_COMPLETE'
 *       - `jc_time()' returning `ASYNC_JOB_WORK_COMPLETE'
 *     - AIO_COMPLETION_CANCEL:
 *       - `aio_handle_cancel()' has been called
 *       - `async_job_cancel()' has been called
 *     - AIO_COMPLETION_FAILURE:
 *       - `jc_poll()' returned with an exception
 *       - `jc_work()' returned with an exception
 *       - `jc_time()' returned with an exception
 * Note also that when `aio' is given, it will be initialize to inherit a reference
 * to `self', meaning that `decref(async_job_start(job, aio))' is a valid use case!
 * @return: * : Always re-returns `self' */
PUBLIC NOBLOCK NONNULL((1)) REF async_job_t
NOTHROW(FCALL async_job_start)(async_job_t self,
                               /*out,opt*/ struct aio_handle *aio) {
	struct async_job *me, *next;
	assert(!ASYNC_JOB_AIO_ISSPEC(aio));
	me = self - 1;
#ifndef NDEBUG
	assert(me->aj_next == (REF struct async_job *)0x1234);
#endif /* !NDEBUG */
	assert(me->aj_refcnt == 2);
	assert(me->aj_aio == ASYNC_JOB_AIO_NONPRESENT);
	/* Initialize the AIO handle (if given) */
	if (aio) {
		struct async_job_aio_data *data;
		data = (struct async_job_aio_data *)aio->ah_data;
		data->ajad_job = self;
		me->aj_refcnt  = 3; /* +1: `data->ajad_job' */
		COMPILER_WRITE_BARRIER();
		aio_handle_init(aio,
		                me->aj_ops->jc_retsize
		                ? &async_job_aio
		                : &async_job_aio_noretsize);
	}

	me->aj_aio = aio;
	/* Register the job.
	 * NOTE: The first implicit reference is inherited by `async_jobs' */
	do {
		next = ATOMIC_READ(async_jobs);
		me->aj_next = next;
		COMPILER_WRITE_BARRIER();
	} while (!ATOMIC_CMPXCH_WEAK(async_jobs, next, me));
	/* Signal that new async jobs have become available. */
	sig_broadcast(&awork_changed);
	return self; /* Return the second implicit reference */
}


/* Cancel a given job.
 * This function can be used to prevent future invocation of the given job's functions.
 * WARNING: Job cancellation also happens asynchronously (except for in regards to
 *          the `AIO_COMPLETION_CANCEL' completion status of a possibly connected AIO
 *          handle), meaning that even after this function returns, the job may continue
 *          to exist for a while longer before eventually being deleted! */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL async_job_cancel)(async_job_t self) {
	struct async_job *me;
	struct aio_handle *aio;
	me  = self - 1;
	PREEMPTION_DISABLE();
	aio = ATOMIC_XCH(me->aj_aio, ASYNC_JOB_AIO_CANCELED);
	if (ASYNC_JOB_AIO_ISPRESENT(aio)) {
		/* Signal AIO completion with `AIO_COMPLETION_CANCEL' */
		aio_handle_complete_nopr(aio, AIO_COMPLETION_CANCEL);
	}
	PREEMPTION_ENABLE();
	/* Wake up the async worker to have to get rid of this job. */
	if (aio != ASYNC_JOB_AIO_CANCELED)
		sig_broadcast(&awork_changed);
}






DECL_END

#endif /* !GUARD_KERNEL_SRC_SCHED_ASYNC_C */
