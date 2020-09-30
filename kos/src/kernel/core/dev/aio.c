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
#ifndef GUARD_KERNEL_SRC_DEV_AIO_C
#define GUARD_KERNEL_SRC_DEV_AIO_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/aio.h>
#include <kernel/driver.h>
#include <kernel/except.h>
#include <kernel/malloc.h>
#include <kernel/types.h>
#include <kernel/vm.h>
#include <kernel/vm/phys.h>
#include <sched/signal.h>

#include <hybrid/atomic.h>

#include <assert.h>
#include <stddef.h>
#include <string.h>

DECL_BEGIN


PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL aio_noop_noarg)(struct aio_handle *__restrict UNUSED(self)) {
}

/* No-op AIO handle type (intended for synchronous operations) */
PUBLIC struct aio_handle_type aio_noop_type = {
	/* .ht_fini   = */ &aio_noop_noarg,
	/* .ht_cancel = */ &aio_noop_noarg
};



/* Callback for `aio_handle_generic' */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL aio_handle_generic_func_)(struct aio_handle_generic *__restrict self,
                                        unsigned int status)
		ASMNAME("aio_handle_generic_func");
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL aio_handle_generic_func_)(struct aio_handle_generic *__restrict self,
                                        unsigned int status) {
	self->hg_status = status;
	if (status == AIO_COMPLETION_FAILURE) {
		memcpy(&self->hg_error, &THIS_EXCEPTION_DATA,
		       sizeof(struct exception_data));
	}
	COMPILER_WRITE_BARRIER();
	sig_broadcast(&self->hg_signal);
}

FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL aio_multihandle_generic_func_)(struct aio_multihandle_generic *__restrict self,
                                             unsigned int status)
		ASMNAME("aio_multihandle_generic_func");
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL aio_multihandle_generic_func_)(struct aio_multihandle_generic *__restrict self,
                                             unsigned int UNUSED(status)) {
	sig_broadcast(&self->mg_signal);
}





/* Callback for `aio_handle_multiple' */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL aio_handle_multiple_func_)(struct aio_handle_multiple *__restrict self,
                                         unsigned int status)
		ASMNAME("aio_handle_multiple_func");
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL aio_handle_multiple_func_)(struct aio_handle_multiple *__restrict self,
                                         unsigned int status) {
	struct aio_multihandle *hand;
	uintptr_t old_status;
	uintptr_t new_status;
	hand = self->hg_controller;
	self->hg_controller = AIO_HANDLE_MULTIPLE_CONTROLLER_COMPLETE;
	COMPILER_BARRIER();
	assert(hand != AIO_HANDLE_MULTIPLE_CONTROLLER_UNUSED &&
	       hand != AIO_HANDLE_MULTIPLE_CONTROLLER_COMPLETE);
	do {
		old_status = ATOMIC_READ(hand->am_status);
		new_status = (uintptr_t)status << AIO_MULTIHANDLE_STATUS_STATUSSHFT;
		assert((old_status & AIO_MULTIHANDLE_STATUS_RUNMASK) != 0);
		if (old_status & AIO_MULTIHANDLE_STATUS_FAILED)
			return; /* Controller failure (ignore handle completion). */
		if (new_status <= (old_status & AIO_MULTIHANDLE_STATUS_STATUSMASK))
			new_status = old_status & AIO_MULTIHANDLE_STATUS_STATUSMASK; /* Don't update the status */
		new_status |= (old_status & ~(AIO_MULTIHANDLE_STATUS_STATUSMASK | AIO_MULTIHANDLE_STATUS_RUNMASK));
		new_status |= (old_status & (AIO_MULTIHANDLE_STATUS_RUNMASK)) - 1;
	} while (!ATOMIC_CMPXCH_WEAK(hand->am_status, old_status, new_status));
	/* Must store the current context. */
	if (status == AIO_COMPLETION_FAILURE && (old_status & AIO_MULTIHANDLE_STATUS_STATUSMASK) <
	                                        ((uintptr_t)AIO_COMPLETION_FAILURE << AIO_MULTIHANDLE_STATUS_STATUSSHFT))
		memcpy(&hand->am_error, &THIS_EXCEPTION_DATA, sizeof(hand->am_error));
	if (!(old_status & AIO_MULTIHANDLE_STATUS_ALLRUNNING))
		return; /* Premature completion (don't invoke the callback, yet) */
	if ((old_status & AIO_MULTIHANDLE_STATUS_RUNMASK) == 1) {
		/* Last callback. */
		unsigned int final_status;
		final_status = (new_status & AIO_MULTIHANDLE_STATUS_STATUSMASK) >> AIO_MULTIHANDLE_STATUS_STATUSSHFT;
		if (final_status == AIO_COMPLETION_FAILURE)
			memcpy(&THIS_EXCEPTION_DATA, &hand->am_error, sizeof(hand->am_error));
		(*hand->am_func)(hand, final_status);
	}
}



PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(KCALL aio_multihandle_fini)(struct aio_multihandle *__restrict self) {
	unsigned int i;
	struct aio_multihandle_extension *iter, *next;
	for (i = 0; i < AIO_MULTIHANDLE_IVECLIMIT; ++i) {
		struct aio_handle_multiple *ent;
		ent = &self->am_ivec[i];
		assert(ent->hg_controller == AIO_HANDLE_MULTIPLE_CONTROLLER_UNUSED ||
		       ent->hg_controller == AIO_HANDLE_MULTIPLE_CONTROLLER_COMPLETE);
		if (ent->hg_controller == AIO_HANDLE_MULTIPLE_CONTROLLER_COMPLETE && ent->ah_type)
			aio_handle_fini(ent);
#ifndef NDEBUG
		memset(ent, 0xcc, sizeof(*ent));
#endif /* !NDEBUG */
	}
	iter = self->am_ext;
#ifndef NDEBUG
	memset(&self->am_ext, 0xcc, sizeof(self->am_ext));
#endif /* !NDEBUG */
	while (iter) {
		next = iter->ame_next;
		for (i = 0; i < AIO_MULTIHANDLE_XVECLIMIT; ++i) {
			struct aio_handle_multiple *ent;
			ent = &iter->ame_handles[i];
			assert(ent->hg_controller == AIO_HANDLE_MULTIPLE_CONTROLLER_UNUSED ||
			       ent->hg_controller == AIO_HANDLE_MULTIPLE_CONTROLLER_COMPLETE);
			if (ent->hg_controller == AIO_HANDLE_MULTIPLE_CONTROLLER_COMPLETE && ent->ah_type)
				aio_handle_fini(ent);
		}
		kfree(iter);
		iter = next;
	}
#ifndef NDEBUG
	memset(&self->am_func, 0xcc, sizeof(self->am_func));
	memset(&self->am_status, 0xcc, sizeof(self->am_status));
	memset(&self->am_error, 0xcc, sizeof(self->am_error));
#endif /* !NDEBUG */
}


/* Allocate handles for the purpose of AIO completion.
 * WARNING: Don't free a handle after you already started using it in the context of an AIO parameter.
 * NOTE: `aio_multihandle_allochandle()' calls `aio_multihandle_fail()' upon
 *       error, before returning propagating an error / returning `NULL'. */
PUBLIC ATTR_RETNONNULL WUNUSED NONNULL((1)) struct aio_handle *KCALL
aio_multihandle_allochandle(struct aio_multihandle *__restrict self)
		THROWS(E_BADALLOC) {
	struct aio_handle_multiple *result;
	uintptr_t run_count;
	run_count = ATOMIC_READ(self->am_status);
	assert(!(run_count & AIO_MULTIHANDLE_STATUS_FAILED));
	assert(!(run_count & AIO_MULTIHANDLE_STATUS_ALLRUNNING));
	run_count &= AIO_MULTIHANDLE_STATUS_RUNMASK;
	if (!run_count) {
		result = &self->am_ivec[0];
	} else {
		/* Search through already existing handles to find one that has
		 * already completed. */
		size_t i;
		struct aio_multihandle_extension *iter;
		for (i = 0; i < AIO_MULTIHANDLE_IVECLIMIT; ++i) {
			struct aio_multihandle *ctrl;
			result = &self->am_ivec[i];
			ctrl   = ATOMIC_READ(result->hg_controller);
			if (ctrl == AIO_HANDLE_MULTIPLE_CONTROLLER_UNUSED)
				goto fill_in_result;
			if (ctrl == AIO_HANDLE_MULTIPLE_CONTROLLER_COMPLETE) {
fini_and_fill_in_result:
				aio_handle_fini(result);
				goto fill_in_result;
			}
		}
		for (iter = self->am_ext; iter; iter = iter->ame_next) {
			for (i = 0; i < AIO_MULTIHANDLE_XVECLIMIT; ++i) {
				struct aio_multihandle *ctrl;
				result = &iter->ame_handles[i];
				ctrl   = ATOMIC_READ(result->hg_controller);
				if (ctrl == AIO_HANDLE_MULTIPLE_CONTROLLER_UNUSED)
					goto fill_in_result;
				if (ctrl == AIO_HANDLE_MULTIPLE_CONTROLLER_COMPLETE)
					goto fini_and_fill_in_result;
			}
		}
		/* Must allocate a new extension table. */
		iter = (struct aio_multihandle_extension *)kmalloc(sizeof(struct aio_multihandle_extension),
		                                                   GFP_CALLOC | GFP_PREFLT | GFP_LOCKED);
#ifndef AIO_HANDLE_MULTIPLE_CONTROLLER_UNUSED_IS_ZERO
		for (i = 0; i < AIO_MULTIHANDLE_XVECLIMIT; ++i)
			iter->ame_handles[i].hg_controller = AIO_HANDLE_MULTIPLE_CONTROLLER_UNUSED;
#endif /* !AIO_HANDLE_MULTIPLE_CONTROLLER_UNUSED_IS_ZERO */
		result         = &iter->ame_handles[0];
		iter->ame_next = self->am_ext;
		self->am_ext   = iter;
	}
fill_in_result:
#ifndef NDEBUG
	memset(result, 0xcc, sizeof(struct aio_handle));
#endif /* !NDEBUG */
	result->ah_func       = &aio_handle_multiple_func;
	result->hg_controller = self;
	/* Required by `aio_multihandle_cancel()'
	 * Used to ensure that the handle was actually initialized. */
	result->ah_type = NULL;
	ATOMIC_INC(self->am_status); /* Increment the run counter. */
	return result;
}

PUBLIC WUNUSED NONNULL((1)) struct aio_handle *
NOTHROW(KCALL aio_multihandle_allochandle_nx)(struct aio_multihandle *__restrict self) {
	struct aio_handle_multiple *result;
	uintptr_t run_count;
	run_count = ATOMIC_READ(self->am_status);
	assert(!(run_count & AIO_MULTIHANDLE_STATUS_FAILED));
	assert(!(run_count & AIO_MULTIHANDLE_STATUS_ALLRUNNING));
	run_count &= AIO_MULTIHANDLE_STATUS_RUNMASK;
	if (!run_count) {
		result = &self->am_ivec[0];
	} else {
		/* Search through already existing handles to find one that has
		 * already completed. */
		size_t i;
		struct aio_multihandle_extension *iter;
		for (i = 0; i < AIO_MULTIHANDLE_IVECLIMIT; ++i) {
			struct aio_multihandle *ctrl;
			result = &self->am_ivec[i];
			ctrl   = ATOMIC_READ(result->hg_controller);
			if (ctrl == AIO_HANDLE_MULTIPLE_CONTROLLER_UNUSED)
				goto fill_in_result;
			if (ctrl == AIO_HANDLE_MULTIPLE_CONTROLLER_COMPLETE) {
fini_and_fill_in_result:
				aio_handle_fini(result);
				goto fill_in_result;
			}
		}
		for (iter = self->am_ext; iter; iter = iter->ame_next) {
			for (i = 0; i < AIO_MULTIHANDLE_XVECLIMIT; ++i) {
				struct aio_multihandle *ctrl;
				result = &iter->ame_handles[i];
				ctrl   = ATOMIC_READ(result->hg_controller);
				if (ctrl == AIO_HANDLE_MULTIPLE_CONTROLLER_UNUSED)
					goto fill_in_result;
				if (ctrl == AIO_HANDLE_MULTIPLE_CONTROLLER_COMPLETE)
					goto fini_and_fill_in_result;
			}
		}
		/* Must allocate a new extension table. */
		iter = (struct aio_multihandle_extension *)kmalloc_nx(sizeof(struct aio_multihandle_extension),
		                                                      GFP_CALLOC | GFP_PREFLT | GFP_LOCKED);
		if unlikely(!iter)
			goto err;
		result         = &iter->ame_handles[0];
		iter->ame_next = self->am_ext;
		self->am_ext   = iter;
	}
fill_in_result:
#ifndef NDEBUG
	memset(result, 0xcc, sizeof(struct aio_handle));
#endif /* !NDEBUG */
	result->ah_func       = &aio_handle_multiple_func;
	result->hg_controller = self;
	/* Required by `aio_multihandle_cancel()'
	 * Used to ensure that the handle was actually initialized. */
	result->ah_type = NULL;
	ATOMIC_INC(self->am_status); /* Increment the run counter. */
	return result;
err:
	return NULL;
}



/* Indicate that no further handles will be allocated, meaning that `self->am_func'
 * is now allowed to be called once all initiated operations have finished (which
 * may be immediately).
 * WARNING: This function should not be called after `aio_multihandle_fail()',
 *          or be called more than once! */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(KCALL aio_multihandle_done)(struct aio_multihandle *__restrict self) {
	uintptr_t old_status;
	for (;;) {
		old_status = ATOMIC_READ(self->am_status);
		if (old_status & AIO_MULTIHANDLE_STATUS_FAILED)
			return; /* Controller already failed */
		assertf(!(old_status & AIO_MULTIHANDLE_STATUS_ALLRUNNING),
		        "Cannot call `aio_multihandle_done()' more than once");
		if (ATOMIC_CMPXCH_WEAK(self->am_status, old_status, old_status | AIO_MULTIHANDLE_STATUS_ALLRUNNING))
			break;
	}
	if ((old_status & AIO_MULTIHANDLE_STATUS_RUNMASK) == 0) {
		unsigned int status;
		/* All handles have already completed. */
		status = (old_status & AIO_MULTIHANDLE_STATUS_STATUSMASK) >> AIO_MULTIHANDLE_STATUS_STATUSSHFT;
		if (status == AIO_COMPLETION_FAILURE) {
			struct exception_data old_exc, *my_exc;
			my_exc = &THIS_EXCEPTION_DATA;
			memcpy(&old_exc, &my_exc, sizeof(my_exc));
			memcpy(my_exc, &self->am_error, sizeof(self->am_error));
			/* Invoke the completion callback. */
			(*self->am_func)(self, status);
			memcpy(&my_exc, &old_exc, sizeof(my_exc));
		} else {
			/* Invoke the completion callback. */
			(*self->am_func)(self, status);
		}
	}
}



/* Handle the current exception using the given AIO multi-handle.
 * NOTE: This function will also call `aio_multihandle_cancel()' */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(KCALL aio_multihandle_fail)(struct aio_multihandle *__restrict self) {
	uintptr_t old_status;
	do {
		old_status = ATOMIC_READ(self->am_status);
		if (old_status & AIO_MULTIHANDLE_STATUS_FAILED)
			return; /* Already failed. */
		assertf(!(old_status & AIO_MULTIHANDLE_STATUS_ALLRUNNING),
		        "Cannot call `aio_multihandle_fail()' after `aio_multihandle_done()'");
	} while (!ATOMIC_CMPXCH_WEAK(self->am_status, old_status,
	                             (old_status & ~AIO_MULTIHANDLE_STATUS_STATUSMASK) |
	                             (uintptr_t)AIO_MULTIHANDLE_STATUS_FAILED |
	                             (uintptr_t)AIO_MULTIHANDLE_STATUS_ALLRUNNING |
	                             ((uintptr_t)AIO_COMPLETION_FAILURE << AIO_MULTIHANDLE_STATUS_STATUSSHFT)));
	/* Cancel all remaining operations that may still be running. */
	aio_multihandle_cancel(self);
	/* Copy active exception information. */
	if ((old_status & (uintptr_t)AIO_MULTIHANDLE_STATUS_STATUSMASK) <
	    ((uintptr_t)AIO_COMPLETION_FAILURE << AIO_MULTIHANDLE_STATUS_STATUSSHFT))
		memcpy(&self->am_error, &THIS_EXCEPTION_DATA, sizeof(self->am_error));
	/* Invoke the completion function. */
	memcpy(&THIS_EXCEPTION_DATA, &self->am_error, sizeof(self->am_error));
	(*self->am_func)(self, AIO_COMPLETION_FAILURE);
}


/* Cancel all currently running handles of `self'
 * NOTE: May be called multiple times without causing harm. */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(KCALL aio_multihandle_cancel)(struct aio_multihandle *__restrict self) {
	unsigned int i;
	struct aio_multihandle_extension *ext;
	for (i = 0; i < AIO_MULTIHANDLE_IVECLIMIT; ++i) {
		if (self->am_ivec[i].hg_controller &&
		    self->am_ivec[i].ah_type) {
			aio_handle_cancel(&self->am_ivec[i]);
		}
	}
	for (ext = self->am_ext; ext; ext = ext->ame_next) {
		for (i = 0; i < AIO_MULTIHANDLE_XVECLIMIT; ++i) {
			if (ext->ame_handles[i].hg_controller &&
			    ext->ame_handles[i].ah_type)
				aio_handle_cancel(&ext->ame_handles[i]);
		}
	}
}





/* Allocate and return a special AIO handle that can be used just like any other,
 * however will clean-up itself after the usual init+complete+fini cycle of any
 * given AIO handle. This allows the caller to use this handle to detach themself
 * from any async-operation such that the operation will either succeed or fail
 * at an arbitrary point in the future, potentially long after the caller started
 * the operation. To-be used as follows:
 * >> void nic_background_send(struct nic_device const *__restrict self,
 * >>                          struct nic_packet *__restrict packet) {
 * >>     struct aio_handle *aio;
 * >>     aio = aio_handle_async_alloc();
 * >>     TRY {
 * >>         // This call essentially behaves as `inherit(on_success)' for `aio'
 * >>         (*self->nd_ops.nd_send)(self, packet, aio);
 * >>     } EXCEPT {
 * >>         aio_handle_async_free(aio);
 * >>         RETHROW();
 * >>     }
 * >> }
 * NOTE: When the AIO operation completes with `AIO_COMPLETION_FAILURE',
 *       then an error message is written to the system log.
 */
struct async_aio_handle: aio_handle {
	struct async_aio_handle *aah_next; /* [lock(IN_CHAIN(async_aio_handles))][0..1]
	                                    * The next used/free async-aio handle. */
	aio_completion_t         aah_func; /* [0..1] The user-defined completion function. */
};

/* [0..1][lock(ATOMIC)] Chain of used/free async-aio handles. */
PRIVATE WEAK struct async_aio_handle *async_aio_handles = NULL;

LOCAL NOBLOCK NONNULL((1, 2)) void
NOTHROW(KCALL aio_handle_async_restore_chain)(struct async_aio_handle *first,
                                              struct async_aio_handle *last) {
	struct async_aio_handle *next;
	do {
		next = ATOMIC_READ(async_aio_handles);
		last->aah_next = next;
		COMPILER_WRITE_BARRIER();
	} while (!ATOMIC_CMPXCH_WEAK(async_aio_handles, next, first));
}

/* Return the first handle with `aio_handle_completed(handle) == true'
 * from `async_aio_handles' and remove that handle from the chain.
 * If no such handle exists, or the chain is already being used by
 * some other thread, return `NULL' instead. */
PRIVATE NOBLOCK WUNUSED struct async_aio_handle *
NOTHROW(KCALL aio_handle_async_alloc_exising)(void) {
	struct async_aio_handle *chain, **piter, *iter;
	chain = ATOMIC_XCH(async_aio_handles, NULL);
	for (piter = &chain; (iter = *piter) != NULL; piter = &iter->aah_next) {
		struct async_aio_handle *result;
		if (!aio_handle_completed(iter))
			continue;
		result = iter;
		*piter = iter->aah_next; /* Unlink the resulting handle. */
		if (iter->aah_next) {
			while (iter->aah_next)
				iter = iter->aah_next;
		} else if (piter == &chain) {
			assert(chain == NULL);
			goto nothing_to_restore;
		} else {
			iter = container_of(piter, struct async_aio_handle, aah_next);
		}
		/* Restore the remainder of the chain. */
		aio_handle_async_restore_chain(chain, iter);
nothing_to_restore:
		/* Finalize the old handle. */
		aio_handle_fini(result);
#ifndef NDEBUG
		memset(&result->aah_next, 0xcc, sizeof(result->aah_next));
#endif /* !NDEBUG */
		return result;
	}
	return NULL;
}


/* Remove all AIO handles that are `aio_handle_completed()'
 * from `async_aio_handles', and kfree() them. */
DEFINE_SYSTEM_CACHE_CLEAR(async_aio_handles_clear);
INTERN NOBLOCK size_t
NOTHROW(KCALL async_aio_handles_clear)(void) {
	/* TODO: A function similar to this one should be called when the CPU goes into
	 *       IDLE mode in order to finalize and kfree() unused AIO handles, since
	 *       in-use AIO handles could potentially slow down the system since they
	 *       might contain arbitrary, device-specific references to other objects!
	 * TODO: This function should be called after driver finalization to delete AIO
	 *       handles which may still be holding references to the driver (Note that
	 *       such references would likely be indirect; e.g.: aio->device->driver). */
	size_t i, result = 0;
	struct async_aio_handle *h;
	while ((h = aio_handle_async_alloc_exising()) != NULL) {
free_h:
		result += sizeof(struct async_aio_handle);
		aio_handle_async_free(h);
	}
	/* Try to yield to some other thread, who may still be holding AIO handles. */
	for (i = 0; i < 8; ++i) {
		if (task_tryyield() != TASK_TRYYIELD_SUCCESS)
			break;
		h = aio_handle_async_alloc_exising();
		if (h)
			goto free_h;
	}
	return result;
}

PRIVATE NOBLOCK NOPREEMPT NONNULL((1)) void
NOTHROW(FCALL aio_handle_async_func)(struct aio_handle *__restrict self,
                                     unsigned int status) {
	struct async_aio_handle *me;
	me = (struct async_aio_handle *)self;
	aio_handle_async_restore_chain(me, me);
	/* Invoke the user-defined completion function (if defined) */
	if (me->aah_func) {
		(*me->aah_func)(me, status);
	} else {
		if (status == AIO_COMPLETION_FAILURE)
			error_printf("Performing background AIO operation");
	}
}


/* Allocate and return a special AIO handle that can be used just like any other,
 * however will clean-up itself after the usual init+complete+fini cycle of any
 * given AIO handle. This allows the caller to use this handle to detach themself
 * from any async-operation such that the operation will either succeed or fail
 * at an arbitrary point in the future, potentially long after the caller started
 * the operation. To-be used as follows:
 * >> void nic_background_send(struct nic_device const *__restrict self,
 * >>                          struct nic_packet *__restrict packet) {
 * >>     struct aio_handle *aio;
 * >>     aio = aio_handle_async_alloc();
 * >>     TRY {
 * >>         // This call essentially behaves as `inherit(on_success)' for `aio'
 * >>         (*self->nd_ops.nd_send)(self, packet, aio);
 * >>     } EXCEPT {
 * >>         aio_handle_async_free(aio);
 * >>         RETHROW();
 * >>     }
 * >> }
 * NOTE: When the AIO operation completes with `AIO_COMPLETION_FAILURE', and
 *       `func' was NULL, then an error message is written to the system log.
 * @param: func: [0..1] An optional function that is invoked upon completion. */
PUBLIC ATTR_RETNONNULL WUNUSED struct aio_handle *KCALL
aio_handle_async_alloc(aio_completion_t func) THROWS(E_BADALLOC) {
	struct async_aio_handle *result;
	result = aio_handle_async_alloc_exising();
	if (!result) {
		/* Must allocate a new AIO handle. */
		result = (struct async_aio_handle *)kmalloc(sizeof(struct async_aio_handle),
		                                            GFP_LOCKED | GFP_PREFLT);
		/* Set-up the handle such that it will add itself to the
		 * async-aio-handle chain once its completion-function is invoked.
		 * NOTE: We can't have the completion-function simply kfree() the
		 *       handle immediately, because the caller of the callback
		 *       must still be able to set the handle's next pointer to
		 *       indicate `AIO_HANDLE_NEXT_COMPLETED' */
		result->ah_func  = &aio_handle_async_func;
		result->aah_func = func;
	}
	return result;
}

PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(KCALL aio_handle_async_free)(struct aio_handle *__restrict self) {
	kfree(self);
}




DECL_END

#endif /* !GUARD_KERNEL_SRC_DEV_AIO_C */
