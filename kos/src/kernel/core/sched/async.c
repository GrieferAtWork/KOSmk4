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


struct asyncworker {
	async_callback_t aw_test;  /* [0..1][const] Test-callback */
	async_callback_t aw_poll;  /* [1..1][const] Poll-callback */
	async_callback_t aw_work;  /* [1..1][const] Work-callback */
	WEAK void       *aw_obj;   /* [0..1][lock(CLEAR_ONCE && SMP(aw_inuse))] Object pointer.
	                            * When set to NULL, this worker may be removed */
	uintptr_half_t   aw_typ;   /* [const] Object type (one of `HANDLE_TYPE_*'). */
	uintptr_half_t   aw_didrm; /* Set to non-zero in the old async-vector when the entry is removed.
	                            *  */
#ifndef CONFIG_NO_SMP
	uintptr_t        aw_inuse; /* # of CPUs using `aw_obj' right now. */
#endif /* !CONFIG_NO_SMP */
};

#define asyncworker_eq(self, test, poll, work, obj, typ) \
	((self)->aw_work == (work) &&                        \
	 ATOMIC_READ((self)->aw_obj) == (obj) &&             \
	 (self)->aw_poll == (poll) &&                        \
	 (self)->aw_test == (test) &&                        \
	 (self)->aw_typ == (typ))


LOCAL NOBLOCK bool
NOTHROW(FCALL asyncworker_clearobj)(struct asyncworker *__restrict self) {
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

LOCAL bool
NOTHROW(FCALL asyncworker_calltest)(struct asyncworker const *__restrict self,
                                    void *obj) {
	bool result;
	TRY {
		result = (*self->aw_test)(obj);
	} EXCEPT {
		error_printf("_asyncmain:test@%p(%p:%#x)",
		             self->aw_test, obj,
		             (unsigned int)self->aw_typ);
		result = false;
	}
	return result;
}

LOCAL bool
NOTHROW(FCALL asyncworker_callpoll)(struct asyncworker const *__restrict self,
                                    void *obj) {
	bool result;
	TRY {
		result = (*self->aw_poll)(obj);
	} EXCEPT {
		error_printf("_asyncmain:poll@%p(%p:%#x)",
		             self->aw_poll, obj,
		             (unsigned int)self->aw_typ);
		result = false;
	}
	return result;
}

LOCAL bool
NOTHROW(FCALL asyncworker_callwork)(struct asyncworker const *__restrict self,
                                    void *obj) {
	bool result;
	TRY {
		result = (*self->aw_work)(obj);
	} EXCEPT {
		error_printf("_asyncmain:poll@%p(%p:%#x)",
		             self->aw_work, obj,
		             (unsigned int)self->aw_typ);
		result = false;
	}
	return result;
}



struct asyncworkers {
	WEAK refcnt_t                               aws_refcnt; /* Reference counter. */
	size_t                                      awc_testc;  /* # of worker threads with test-callbacks.
	                                                         * All such workers come before those without! */
	size_t                                      awc_workc;  /* # of worker threads. */
	COMPILER_FLEXIBLE_ARRAY(struct asyncworker, awc_workv); /* [0..awc_workc] Vector of workers */
};

DEFINE_REFCOUNT_FUNCTIONS(struct asyncworkers, aws_refcnt, kfree)

PRIVATE struct asyncworkers empty_asyncworkers = {
	/* .aws_refcnt = */ 2, /* +1: empty_asyncworkers; +1: awork */
	/* .awc_testc  = */ 0, /* No workers defined by default... */
	/* .awc_workc  = */ 0  /* No workers defined by default... */
};

/* Registered async work. */
PRIVATE ATOMIC_REF(struct asyncworkers) awork = ATOMIC_REF_INIT(&empty_asyncworkers);

/* Signal broadcast when `awork' has changed. */
PRIVATE struct sig awork_changed = SIG_INIT;

#define TRY_DELETE_ASYNC_WORKER_SUCCESS  0 /* Success */
#define TRY_DELETE_ASYNC_WORKER_BADALLOC 1 /* Failed to allocate a new set of workers */
#define TRY_DELETE_ASYNC_WORKER_CHANGED  2 /* `old_workers' differed from the active set of workers. */

/* Try to delete a worker from `old_workers' and assign atomically
 * update the global set of active async workers. */
PRIVATE NOBLOCK_IF(gfp_flags & GFP_ATOMIC) NONNULL((1)) unsigned int
NOTHROW(KCALL try_delete_async_worker)(struct asyncworkers *__restrict old_workers,
                                       size_t worker_index, gfp_t gfp_flags) {
	REF struct asyncworkers *new_workers;
	assert(worker_index < old_workers->awc_workc);
	if (old_workers->awc_workc == 1) {
		/* Simple case: Just assign the empty workers list. */
		new_workers = incref(&empty_asyncworkers);
	} else {
		size_t oi, ni;
		assert(old_workers->awc_workc >= 2);
		new_workers = (REF struct asyncworkers *)kmalloc_nx(offsetof(struct asyncworkers, awc_workv) +
		                                                    ((old_workers->awc_workc - 1) *
		                                                     sizeof(struct asyncworker)),
		                                                    gfp_flags);
		if unlikely(!new_workers)
			return TRY_DELETE_ASYNC_WORKER_BADALLOC;
		new_workers->aws_refcnt = 1;
		new_workers->awc_testc  = old_workers->awc_testc;
		new_workers->awc_workc  = old_workers->awc_workc - 1;
		if (worker_index < new_workers->awc_testc)
			--new_workers->awc_testc; /* The to-be-removed worker had a test-function */
		for (oi = ni = 0; ni < new_workers->awc_workc; ++oi) {
			struct asyncworker *nw, *ow;
			if (oi == worker_index)
				continue; /* Don't copy this worker! */
			nw = &new_workers->awc_workv[ni];
			ow = &old_workers->awc_workv[oi];
			nw->aw_test = ow->aw_test;
			nw->aw_poll = ow->aw_poll;
			nw->aw_work = ow->aw_work;
			nw->aw_obj  = ATOMIC_READ(ow->aw_obj); /* Must be read as an atomic work (we can't have byte-splits here!) */
			nw->aw_typ  = ow->aw_typ;
			IF_SMP(nw->aw_inuse = 0);
			++ni;
		}
		assert(ni == new_workers->awc_workc);
		assert(oi == old_workers->awc_workc);
	}
	/* Try to exchange the global async workers vector. */
	if (awork.cmpxch_inherit_new(old_workers, new_workers)) {
		ATOMIC_WRITE(old_workers->awc_workv[worker_index].aw_didrm, 1);
		return TRY_DELETE_ASYNC_WORKER_SUCCESS; /* success! */
	}
	/* The async workers vector was changed in the mean time. */
	decref_likely(new_workers);
	return TRY_DELETE_ASYNC_WORKER_CHANGED;
}


INTERN ATTR_NORETURN void
NOTHROW(FCALL _asyncmain)(void) {
	for (;;) {
		size_t i;
		REF struct asyncworkers *workers;
again:
		assert(PREEMPTION_ENABLED());
		assert(!task_isconnected());
		PREEMPTION_DISABLE();
		workers = awork.get_nopr();
		PREEMPTION_ENABLE();
		/* First pass: test() for work and service immediatly if present. */
		for (i = 0; i < workers->awc_testc; ++i) {
			struct asyncworker *w;
			REF void *obj;
			w = &workers->awc_workv[i];
			assert(w->aw_test);
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
			if (asyncworker_calltest(w, obj)) {
				assert(!task_isconnected());
				/* Service this worker. */
				asyncworker_callwork(w, obj);
				assert(!task_isconnected());
				/* TODO: Do automatic re-ordering of async workers based on how often
				 *       they are being triggered. (workers that have work more often
				 *       should come before those that have less often) */
			}
			(*handle_type_db.h_decref[w->aw_typ])(obj);
		}
		/* Second pass: poll() for work and service if available. */
		for (i = 0; i < workers->awc_workc; ++i) {
			struct asyncworker *w;
			REF void *obj;
			w = &workers->awc_workv[i];
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
			if (asyncworker_callpoll(w, obj)) {
				/* Service this worker. */
				task_disconnectall();
				asyncworker_callwork(w, obj);
				(*handle_type_db.h_decref[w->aw_typ])(obj);
				decref_unlikely(workers);
				goto again;
			}
			(*handle_type_db.h_decref[w->aw_typ])(obj);
		}

		{
			struct task_connection awork_changed_con;
			/* Also wait for async workers to have changed. */
			task_connect_c(&awork_changed_con, &awork_changed);
			TRY {
				task_waitfor();
			} EXCEPT {
				error_printf("_asyncmain:task_waitfor()");
			}
			decref_unlikely(workers);
		}
	}
}


/* Register an async worker callback.
 * NOTE: All callbacks should be non-blocking in that they mustn't wait for
 *       work to become available themself (that's what `poll()' is for, such
 *       that a single thread can wait for async work to become available for
 *       _all_ async workers)
 * @param: test: [0..1] Check if work is available right now, returning `true'
 *                      if this is the case and `work()' should be invoked.
 *                      `arg' is a temporary reference to `ob_pointer:ob_type'
 *                      This callback is optional.
 * @param: poll: [1..1] Do the equivalent of test()+connect()+test() for work
 *                      being available, returning `true' if this is the case.
 *                      `arg' is a temporary reference to `ob_pointer:ob_type'
 * @param: work: [1..1] Perform the actual work, but don't block if no work is
 *                      available. Returns `true' if work was performed, but
 *                      returns `false' if no work was available. This callback
 *                      should be written with the assumption that work being
 *                      available is highly likely.
 * @param: ob_pointer:  A pointer to a handle data object. The destructor of this
 *                      object is responsible for invoking `unregister_async_worker()'
 *                      Callbacks will no longer be invoked if this object's
 *                      reference counter has reached 0, however the object's
 *                      destructor must still unregister the callbacks before
 *                      the memory used to back its reference counter is free()d!
 * @param: ob_type:     The object type for `ob_pointer' (one of `HANDLE_TYPE_*')
 * @return: true:       Successfully registered a new async worker.
 * @return: false:      An async worker for the given object/callback combination
 *                      was already registered. */
PUBLIC NONNULL((2, 3, 4)) bool KCALL
register_async_worker(async_callback_t test,
                      async_callback_t poll,
                      async_callback_t work,
                      void *__restrict ob_pointer,
                      uintptr_half_t ob_type)
		THROWS(E_BADALLOC) {
	REF struct asyncworkers *old_workers;
	REF struct asyncworkers *new_workers;
	struct asyncworker *nw;
	size_t i;
	assert(poll);
	assert(work);
	assert(ob_pointer);
	assert(ob_type < HANDLE_TYPE_COUNT);
again:
	old_workers = awork.get();
	/* Check if this worker has already been defined. */
	{
		size_t c;
		i = 0;
		c = old_workers->awc_testc;
		if (!test) {
			i = c;
			c = old_workers->awc_workc;
		}
		for (; i < c; ++i) {
			if (asyncworker_eq(&old_workers->awc_workv[i],
			                   test, poll, work,
			                   ob_pointer, ob_type))
				return false; /* Already defined. */
		}
	}
	TRY {
		/* Allocate enough space for +1 additional worker. */
		new_workers = (REF struct asyncworkers *)kmalloc(offsetof(struct asyncworkers, awc_workv) +
		                                                 (old_workers->awc_workc + 1) *
		                                                 sizeof(struct asyncworker),
		                                                 GFP_NORMAL);
	} EXCEPT {
		decref_unlikely(old_workers);
		RETHROW();
	}
	/* Fill in the new workers vector. */
	new_workers->aws_refcnt = 1;
	new_workers->awc_testc  = old_workers->awc_testc;
	new_workers->awc_workc  = old_workers->awc_workc;
	assert(new_workers->awc_workc >= new_workers->awc_testc);
	for (i = 0; i < old_workers->awc_workc; ++i) {
		struct asyncworker *ow;
		nw = &new_workers->awc_workv[i];
		ow = &old_workers->awc_workv[i];
		nw->aw_test = ow->aw_test;
		nw->aw_poll = ow->aw_poll;
		nw->aw_work = ow->aw_work;
		nw->aw_obj  = ATOMIC_READ(ow->aw_obj); /* Must be read as an atomic work (we can't have byte-splits here!) */
		nw->aw_typ  = ow->aw_typ;
		IF_SMP(nw->aw_inuse = 0);
	}
	/* Insert the new worker. */
	if (test) {
		/* Insert at the very beginning */
		nw = &new_workers->awc_workv[0];
		memmoveup(nw + 1, nw,
		          new_workers->awc_workc,
		          sizeof(struct asyncworker));
		++new_workers->awc_testc;
	} else {
		/* Insert after all workers with test-functions */
		nw = &new_workers->awc_workv[new_workers->awc_testc];
		memmoveup(nw + 1, nw,
		          new_workers->awc_workc - new_workers->awc_testc,
		          sizeof(struct asyncworker));
	}
	++new_workers->awc_workc;
	nw->aw_test = test;
	nw->aw_poll = poll;
	nw->aw_work = work;
	nw->aw_obj  = ob_pointer;
	nw->aw_typ  = ob_type;
	IF_SMP(nw->aw_inuse = 0);
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
 * @return: true:  Successfully deleted an async worker for the
 *                 given object/callback combination.
 * @return: false: No async worker for the given object/callback
 *                 combination had been registered. */
PUBLIC NOBLOCK NONNULL((2, 3, 4)) bool
NOTHROW(KCALL unregister_async_worker)(async_callback_t test,
                                       async_callback_t poll,
                                       async_callback_t work,
                                       void *__restrict ob_pointer,
                                       uintptr_half_t ob_type) {
	REF struct asyncworkers *workers;
	size_t i, count;
	bool fail_result = false;
	assert(poll);
	assert(work);
	assert(ob_pointer);
	assert(ob_type < HANDLE_TYPE_COUNT);
again:
	workers = awork.get();
	i       = 0;
	count   = workers->awc_testc;
	if (!test) {
		i     = count;
		count = workers->awc_workc;
	}
	for (; i < count; ++i) {
		struct asyncworker *w;
		unsigned int error;
		w = &workers->awc_workv[i];
		if (!asyncworker_eq(w, test, poll, work,
		                    ob_pointer, ob_type))
			continue; /* Different worker. */
		/* Found it! */
		if unlikely(!asyncworker_clearobj(w)) {
			/* The entry was already deleted by another thread.
			 * -> Try to remove the entry (in case the other thread failed in doing this) */
			try_delete_async_worker(workers, i, GFP_ATOMIC);
			break;
		}
		/* Try to delete (but use GFP_ATOMIC since we're not allowed to block) */
		error = try_delete_async_worker(workers, i, GFP_ATOMIC);
		/* Indicate that workers have changed */
		sig_broadcast(&awork_changed);
		if (error == TRY_DELETE_ASYNC_WORKER_BADALLOC) {
			/* Must still check if the active set of workers has changed.
			 * If so, then we must try again since it may have already changed
			 * before we've called `asyncworker_clearobj()', meaning that the
			 * worker we're trying to delete is still apart of the active set
			 * of async workers! */
			if (ATOMIC_READ(awork.m_pointer) != workers) {
again_success:
				/* Account for the possibility that the new set of workers
				 * were created before we've deleted our async worker, such
				 * that even though we've deleted the worker from some older
				 * async-worker-vector, it _may_ still be contained within
				 * the current vector.
				 * Notice the _may_ here, as irregardless of the worker still
				 * being contained inside the current vector, we do already
				 * know that it was contained in some past vector prior to
				 * our function being called, meaning that even if it's already
				 * gone at this point, it was there once, and our call to
				 * `asyncworker_clearobj()' was what caused it to be removed.
				 * -> As such, return `true' in all branches that would normally
				 *    cause `false' to be returned!
				 */
				decref_likely(workers);
				fail_result = true;
				goto again;
			}
			decref_unlikely(workers);
			/* Workers didn't change, but we've failed to allocate a smaller
			 * workers vector. However, since we've already cleared out worker's
			 * object pointer (s.a. `asyncworker_clearobj()'), the worker will
			 * no longer be invoked, and `_asyncwork' will be try to truncate
			 * the vector for us until it succeeds in doing so. */
			return true;
		}
		if (error == TRY_DELETE_ASYNC_WORKER_CHANGED)
			goto again_success; /* Workers have changed. */
		/* Success: The workers vector was truncated. */
		decref_likely(workers);
		return true;
	}
	/* The worker wasn't found (or it was deleted during a prior pass) */
	decref_unlikely(workers);
	return fail_result;
}


DECL_END

#endif /* !GUARD_KERNEL_SRC_SCHED_ASYNC_C */
