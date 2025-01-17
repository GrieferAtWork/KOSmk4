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
#ifndef GUARD_KERNEL_SRC_SCHED_ASYNC_WORKER_C
#define GUARD_KERNEL_SRC_SCHED_ASYNC_WORKER_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/handle.h>
#include <kernel/malloc.h>
#include <sched/async.h>
#include <sched/task.h>

#include <hybrid/sched/preemption.h>

#include <kos/aref.h>
#include <kos/except.h>

#include <assert.h>
#include <atomic.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

#ifndef CONFIG_NO_SMP
#define IF_SMP(...) __VA_ARGS__
#else /* !CONFIG_NO_SMP */
#define IF_SMP(...) /* nothing */
#endif /* CONFIG_NO_SMP */

DECL_BEGIN

/************************************************************************/
/* HIGH-LEVEL ASYNC WORKER API                                          */
/************************************************************************/

struct aworker: async {
	WEAK void      *aw_obj;   /* [0..1][lock(CLEAR_ONCE && SMP(aw_inuse))]
	                           * Object pointer. When set to NULL, this worker
	                           * may be removed */
	uintptr_half_t  aw_typ;   /* [const] Object type (one of `HANDLE_TYPE_*'). */
	uintptr_half_t _aw_pad;   /* ... */
#ifndef CONFIG_NO_SMP
	uintptr_t       aw_inuse; /* # of CPUs using `aw_obj' right now. */
#endif /* !CONFIG_NO_SMP */
};
#define aworker_getops(self) ((struct async_worker_ops *)(self)->a_ops)

#define aworker_decref_obj(self, obj) \
	(*handle_type_db.h_decref[(self)->aw_typ])(obj);

#define aworker_eq(self, ops, obj, typ)       \
	(aworker_getops(self) == (ops) &&         \
	 atomic_read(&(self)->aw_obj) == (obj) && \
	 (self)->aw_typ == (typ))

LOCAL NOBLOCK bool
NOTHROW(FCALL aworker_clearobj)(struct aworker *__restrict self) {
	void *old_value;
#ifdef CONFIG_NO_SMP
	preemption_flag_t was;
	preemption_pushoff(&was);
#endif /* CONFIG_NO_SMP */
	old_value = atomic_xch(&self->aw_obj, NULL);
#ifndef CONFIG_NO_SMP
	while (atomic_read(&self->aw_inuse))
		task_tryyield_or_pause();
#else /* !CONFIG_NO_SMP */
	preemption_pop(&was);
#endif /* CONFIG_NO_SMP */
	return old_value != NULL;
}

LOCAL WUNUSED NONNULL((1)) /*nullable*/ REF void *
NOTHROW(FCALL aworker_getref)(struct aworker *__restrict self) {
	REF void *result;
	PREEMPTION_DISABLE();
	IF_SMP(atomic_inc(&self->aw_inuse));
	COMPILER_READ_BARRIER();
	result = self->aw_obj;
	COMPILER_READ_BARRIER();
	/* Try to acquire a reference. */
	if (likely(result) && unlikely(!(*handle_type_db.h_tryincref[self->aw_typ])(result)))
		result = NULL;
	IF_SMP(atomic_dec(&self->aw_inuse));
	PREEMPTION_ENABLE();
	return result;
}


struct awork_vector {
	WEAK refcnt_t                                 av_refcnt; /* Reference counter. */
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

DEFINE_REFCNT_FUNCTIONS(struct awork_vector, av_refcnt, awork_vector_destroy)

PRIVATE struct awork_vector empty_awork = {
	.av_refcnt = 2, /* +1: empty_awork; +1: awork */
	.av_workc  = 0, /* No workers defined by default... */
};

ARREF(awork_vector_arref, awork_vector);

/* Registered async work. */
PRIVATE struct awork_vector_arref awork = ARREF_INIT(&empty_awork);


#define TRY_DELETE_ASYNC_WORKER_SUCCESS  0 /* Success */
#define TRY_DELETE_ASYNC_WORKER_BADALLOC 1 /* Failed to allocate a new set of workers */
#define TRY_DELETE_ASYNC_WORKER_CHANGED  2 /* `old_workers' differed from the active set of workers. */

/* Try to delete a worker from `old_workers' and assign atomically
 * update the global set of active async workers. */
PRIVATE ATTR_BLOCKLIKE_GFP(gfp_flags) NONNULL((1)) unsigned int
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
		new_workers->av_workc  = old_workers->av_workc - 1;
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
	if (arref_cmpxch_inherit_new(&awork, old_workers, new_workers))
		return TRY_DELETE_ASYNC_WORKER_SUCCESS; /* success! */
	/* The async workers vector was changed in the mean time. */
	decref_likely(new_workers);
	return TRY_DELETE_ASYNC_WORKER_CHANGED;
}




/* Operators for `struct async_worker_ops::awo_async' */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL _async_worker_v_destroy)(struct async *__restrict self) {
	struct aworker *me = (struct aworker *)self;
	kfree(me);
}

PUBLIC NONNULL((1)) ktime_t FCALL
_async_worker_v_connect(struct async *__restrict self) {
	ktime_t result;
	struct aworker *me = (struct aworker *)self;
	REF void *obj;
	obj = aworker_getref(me);
	if (!obj)
		return KTIME_NONBLOCK;
	RAII_FINALLY { aworker_decref_obj(me, obj); };
	result = (*aworker_getops(me)->awo_connect)(obj);
	return result;
}

PUBLIC WUNUSED NONNULL((1)) bool FCALL
_async_worker_v_test(struct async *__restrict self) {
	bool result;
	struct aworker *me = (struct aworker *)self;
	REF void *obj;
	obj = aworker_getref(me);
	if (!obj)
		return true;
	RAII_FINALLY { aworker_decref_obj(me, obj); };
	result = (*aworker_getops(me)->awo_test)(obj);
	return result;
}

PUBLIC WUNUSED NONNULL((1)) unsigned int FCALL
_async_worker_v_work(struct async *__restrict self) {
	unsigned int result;
	struct aworker *me = (struct aworker *)self;
	REF void *obj;
	obj = aworker_getref(me);
	if (!obj)
		return ASYNC_FINISHED;
	RAII_FINALLY { aworker_decref_obj(me, obj); };
	result = (*aworker_getops(me)->awo_work)(obj);
	return result;
}

PUBLIC WUNUSED NONNULL((1)) unsigned int FCALL
_async_worker_v_time(struct async *__restrict self) {
	unsigned int result;
	struct aworker *me = (struct aworker *)self;
	REF void *obj;
	if (!aworker_getops(me)->awo_time)
		return ASYNC_FINISHED;
	obj = aworker_getref(me);
	if (!obj)
		return ASYNC_FINISHED;
	RAII_FINALLY { aworker_decref_obj(me, obj); };
	result = (*aworker_getops(me)->awo_time)(obj);
	return result;
}

PUBLIC NONNULL((1)) void FCALL
_async_worker_v_cancel(struct async *__restrict self) {
	struct aworker *me = (struct aworker *)self;
	REF void *obj;
	if (!aworker_getops(me)->awo_cancel)
		return;
	obj = aworker_getref(me);
	if (!obj)
		return;
	RAII_FINALLY { aworker_decref_obj(me, obj); };
	(*aworker_getops(me)->awo_cancel)(obj);
}



/* Create (but don't start) a new async worker for the given object. */
PUBLIC ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) REF struct async *KCALL
async_worker_new(struct async_worker_ops const *__restrict ops,
                 void *__restrict ob_pointer, uintptr_half_t ob_type)
		THROWS(E_BADALLOC) {
	REF struct aworker *result;
	assert(ops->awo_async.ao_destroy == &_async_worker_v_destroy);
	assert(ops->awo_async.ao_connect == &_async_worker_v_connect);
	assert(ops->awo_async.ao_test == &_async_worker_v_test);
	assert(ops->awo_async.ao_work == &_async_worker_v_work);
	assert(ops->awo_async.ao_time == &_async_worker_v_time);
	assert(ops->awo_async.ao_cancel == &_async_worker_v_cancel);
	result = (REF struct aworker *)kmalloc(sizeof(struct aworker), GFP_NORMAL);

	/* Initialize the new worker */
	async_init(result, &ops->awo_async);
	result->aw_obj = ob_pointer;
	result->aw_typ = ob_type;
	IF_SMP(result->aw_inuse = 0);
	return result;
}


/* Using  an internal database of known async workers, add or remove
 * workers for the given operator table, that are bound to the given
 * ob_pointer/ob_type pair. */
PUBLIC NONNULL((1, 2)) bool KCALL
register_async_worker(struct async_worker_ops const *__restrict ops,
                      void *__restrict ob_pointer, uintptr_half_t ob_type)
		THROWS(E_BADALLOC) {
	REF struct aworker *new_worker;
	REF struct awork_vector *old_workers;
	REF struct awork_vector *new_workers;
	size_t i;
again:
	old_workers = arref_get(&awork);
	/* Check if this worker has already been defined. */
	for (i = 0; i < old_workers->av_workc; ++i) {
		if (aworker_eq(old_workers->av_workv[i],
		               ops, ob_pointer, ob_type))
			return false; /* Already defined. */
	}

	TRY {
		/* Allocate enough space for +1 additional worker. */
		new_workers = (REF struct awork_vector *)kmalloc(offsetof(struct awork_vector, av_workv) +
		                                                 (old_workers->av_workc + 1) *
		                                                 sizeof(struct aworker),
		                                                 GFP_NORMAL);
		TRY {
			new_worker = (REF struct aworker *)async_worker_new(ops, ob_pointer, ob_type);
		} EXCEPT {
			kfree(new_workers);
			RETHROW();
		}
	} EXCEPT {
		decref_unlikely(old_workers);
		RETHROW();
	}

	/* Fill in the new workers vector. */
	new_workers->av_refcnt = 1;
	new_workers->av_workc  = old_workers->av_workc + 1;

	/* Insert `new_worker' at the front */
	memcpy(new_workers->av_workv + 1,
	       old_workers->av_workv,
	       old_workers->av_workc,
	       sizeof(REF struct aworker *));
	new_workers->av_workv[0] = (REF struct aworker *)incref(new_worker);

	/* Acquire references to all of the old workers. */
	for (i = 0; i < old_workers->av_workc; ++i)
		incref(old_workers->av_workv[i]);

	/* Try to install the new async workers vector. */
	if (arref_cmpxch_inherit_new(&awork, old_workers, new_workers)) {
		decref_likely(old_workers);

		/* Actually start the new async job. */
		decref_unlikely(async_start(new_worker));
		return true;
	}

	/* The old set of workers has changed -> try again! */
	decref_likely(new_workers);
	decref_likely(old_workers);
	decref_likely(new_worker);
	goto again;
}

PUBLIC NOBLOCK NONNULL((1, 2)) bool
NOTHROW(KCALL unregister_async_worker)(struct async_worker_ops const *__restrict cb,
                                       void *__restrict ob_pointer, uintptr_half_t ob_type) {
	REF struct awork_vector *workers;
	size_t i;
	workers = arref_get(&awork);
	/* Figure out which parts of the worker-vector we need to search. */
	for (i = 0; i < workers->av_workc; ++i) {
		struct aworker *w;
		w = workers->av_workv[i];
		/* Check if this is the worker we're looking for. */
		if (aworker_eq(w, cb, ob_pointer, ob_type)) {
			bool result;

			/* Try to clear the worker's pointed-to object. */
			result = aworker_clearobj(w);

			/* Make sure that the worker in question has been cancel'd! */
			async_cancel(w);

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

#endif /* !GUARD_KERNEL_SRC_SCHED_ASYNC_WORKER_C */
