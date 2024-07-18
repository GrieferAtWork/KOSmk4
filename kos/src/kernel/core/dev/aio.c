/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
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
#include <kernel/mman/cc.h>
#include <kernel/refcountable.h>
#include <kernel/types.h>
#include <sched/sig.h>
#include <sched/task.h>

#include <hybrid/sched/preemption.h>

#include <assert.h>
#include <atomic.h>
#include <stddef.h>
#include <string.h>

DECL_BEGIN

#if !defined(NDEBUG) && !defined(NDEBUG_FINI)
#define DBG_memset memset
#else /* !NDEBUG && !NDEBUG_FINI */
#define DBG_memset(...) (void)0
#endif /* NDEBUG || NDEBUG_FINI */



PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL aio_noop_noarg)(struct aio_handle *__restrict UNUSED(self)) {
}

/* No-op AIO handle type (intended for synchronous operations) */
PUBLIC struct aio_handle_type aio_noop_type = {
	.ht_fini   = &aio_noop_noarg,
	.ht_cancel = &aio_noop_noarg,
};

PRIVATE NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW(KCALL aio_noop_retval_retsize)(struct aio_handle *__restrict self) {
	return (size_t)(uintptr_t)self->ah_data[0];
}

/* No-op  AIO handle type  (intended for synchronous operations)
 * Just like `aio_noop_type', but this one implements the retval
 * operator, which unconditionally returns  `(size_t)ah_data[0]' */
PUBLIC struct aio_handle_type aio_noop_retval_type = {
	.ht_fini     = &aio_noop_noarg,
	.ht_cancel   = &aio_noop_noarg,
	.ht_retsize  = &aio_noop_retval_retsize
};



struct sig_cleanup_callback_for_aio_completion: sig_cleanup_callback {
	struct aio_handle_generic *self;
};

PRIVATE NOBLOCK NOPREEMPT void
NOTHROW(FCALL sig_cleanup_for_aio_completion)(struct sig_cleanup_callback *self) {
	struct sig_cleanup_callback_for_aio_completion *me;
	me = (struct sig_cleanup_callback_for_aio_completion *)self;
	aio_handle_release(me->self);
}


/* Callback for `aio_handle_generic' */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL aio_handle_generic_func_)(struct aio_handle_generic *__restrict self,
                                        unsigned int status)
		ASMNAME("aio_handle_generic_func");
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL aio_handle_generic_func_)(struct aio_handle_generic *__restrict self,
                                        unsigned int status) {
	struct sig_cleanup_callback_for_aio_completion cleanup;
	self->hg_status = status;
	if (status == AIO_COMPLETION_FAILURE) {
		memcpy(&self->hg_error, &THIS_EXCEPTION_DATA,
		       sizeof(struct exception_data));
	}
	COMPILER_WRITE_BARRIER();
	/* Use a cleanup-callback to unlock  the AIO handle before  other
	 * non-SMP-lock-compatible cleanup operations  are performed,  or
	 * post-completion callbacks get invoked. (which may not actually
	 * be SMP-lock-safe) */
	cleanup.scc_cb = &sig_cleanup_for_aio_completion;
	cleanup.self   = self;
	sig_broadcast_cleanup_nopr(&self->hg_signal, &cleanup);
}




PUBLIC NONNULL((1)) void KCALL
aio_handle_generic_checkerror(struct aio_handle_generic *__restrict self)
		THROWS(E_IOERROR, ...) {
	if unlikely(self->hg_status == AIO_COMPLETION_FAILURE) {
		memcpy(&THIS_EXCEPTION_DATA,
		       &self->hg_error, sizeof(self->hg_error));
		except_throw_current();
	}
}

PUBLIC NONNULL((1)) bool KCALL
aio_handle_generic_poll(struct aio_handle_generic *__restrict self)
		THROWS(E_BADALLOC) {
	if (aio_handle_generic_hascompleted(self))
		return true;
	aio_handle_generic_connect_for_poll(self);
	return aio_handle_generic_hascompleted(self);
}

PUBLIC NONNULL((1)) bool KCALL
aio_handle_generic_waitfor_or_cancel(struct aio_handle_generic *__restrict self,
                                     ktime_t abs_timeout /*DFL(KTIME_INFINITE)*/)
		THROWS(E_WOULDBLOCK, ...) {
	assert(!task_wasconnected());
	while (!aio_handle_generic_hascompleted(self)) {
		TRY {
			aio_handle_generic_connect_for_poll(self);
			if unlikely(aio_handle_generic_hascompleted(self)) {
				task_disconnectall();
				break;
			}
			if (!task_waitfor(abs_timeout)) {
				aio_handle_cancel(self);
				return false;
			}
		} EXCEPT {
			aio_handle_cancel(self);
			RETHROW();
		}
	}
	return true;
}

/* Convenience wrapper for:
 * >> result = aio_handle_generic_waitfor_or_cancel(self, abs_timeout);
 * >> if (result)
 * >>     aio_handle_generic_checkerror(self);
 * >> return result;
 *
 * This function will do everything necessary to:
 * - Ensure completion of `self'
 * - Cancel `self' in case the calling thread is interrupted, or `abs_timeout' expires
 * - When there was no timeout, check if `self' encountered an error, and propagate it
 * - Finalize the AIO controller `self' */
PUBLIC NONNULL((1)) void KCALL
aio_handle_generic_await(struct aio_handle_generic *__restrict self)
		THROWS(E_WOULDBLOCK, ...) {
	aio_handle_generic_waitfor_or_cancel(self);
	aio_handle_generic_checkerror(self);
}

PUBLIC NONNULL((1)) bool KCALL
aio_handle_generic_await_timed(struct aio_handle_generic *__restrict self,
                               ktime_t abs_timeout)
		THROWS(E_WOULDBLOCK, ...) {
	bool result = aio_handle_generic_waitfor_or_cancel(self, abs_timeout);
	if likely(result)
		aio_handle_generic_checkerror(self);
	return result;
}




FUNDEF NOBLOCK NOPREEMPT NONNULL((1)) void
NOTHROW(FCALL aio_multihandle_generic_func_)(struct aio_multihandle_generic *__restrict self,
                                             unsigned int status)
		ASMNAME("aio_multihandle_generic_func");
PUBLIC NOBLOCK NOPREEMPT NONNULL((1)) void
NOTHROW(FCALL aio_multihandle_generic_func_)(struct aio_multihandle_generic *__restrict self,
                                             unsigned int UNUSED(status)) {
	sig_broadcast_nopr(&self->mg_signal);
	/* Release the multihandle. */
	aio_multihandle_release(self);
}

/* Check if the AIO operation failed, and propagate the error if it did. */
PUBLIC NONNULL((1)) void KCALL
aio_multihandle_generic_checkerror(struct aio_multihandle_generic *__restrict self)
		THROWS(E_IOERROR, ...) {
	if unlikely((self->_aio_multihandle_generic_base_ am_status & AIO_MULTIHANDLE_STATUS_STATUSMASK) ==
	           ((uintptr_t)AIO_COMPLETION_FAILURE << AIO_MULTIHANDLE_STATUS_STATUSSHFT)) {
		memcpy(&THIS_EXCEPTION_DATA,
		       &self->_aio_multihandle_generic_base_ am_error,
		       sizeof(self->_aio_multihandle_generic_base_ am_error));
		except_throw_current();
	}
}

PUBLIC NONNULL((1)) bool KCALL
aio_multihandle_generic_poll(struct aio_multihandle_generic *__restrict self)
		THROWS(E_BADALLOC) {
	if (aio_multihandle_generic_hascompleted(self))
		return true;
	aio_multihandle_generic_connect_for_poll(self);
	return aio_multihandle_generic_hascompleted(self);
}

PUBLIC NONNULL((1)) bool KCALL
aio_multihandle_generic_waitfor_or_cancel(struct aio_multihandle_generic *__restrict self,
                                          ktime_t abs_timeout /*DFL(KTIME_INFINITE)*/)
		THROWS(E_WOULDBLOCK, ...) {
	assert(!task_wasconnected());
	while (!aio_multihandle_generic_hascompleted(self)) {
		TRY {
			aio_multihandle_generic_connect_for_poll(self);
			if unlikely(aio_multihandle_generic_hascompleted(self)) {
				task_disconnectall();
				break;
			}
			if (!task_waitfor(abs_timeout)) {
				aio_multihandle_cancel(self);
				return false;
			}
		} EXCEPT {
			aio_multihandle_cancel(self);
			RETHROW();
		}
	}
	return true;
}

PUBLIC NONNULL((1)) void KCALL
aio_multihandle_generic_await(struct aio_multihandle_generic *__restrict self)
		THROWS(E_WOULDBLOCK, ...) {
	aio_multihandle_generic_waitfor_or_cancel(self);
	aio_multihandle_generic_checkerror(self);
}

PUBLIC NONNULL((1)) bool KCALL
aio_multihandle_generic_await_timed(struct aio_multihandle_generic *__restrict self,
                                    ktime_t abs_timeout)
		THROWS(E_WOULDBLOCK, ...) {
	bool result = aio_multihandle_generic_waitfor_or_cancel(self, abs_timeout);
	if likely(result)
		aio_multihandle_generic_checkerror(self);
	return result;
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
	REF struct refcountable *obj;
	uintptr_t old_status;
	uintptr_t new_status;
	hand = self->hg_controller;
	obj  = self->hg_obj;
	self->hg_controller = AIO_HANDLE_MULTIPLE_CONTROLLER_COMPLETE;
	DBG_memset(&self->hg_obj, 0xcc, sizeof(self->hg_obj));
	COMPILER_BARRIER();
	aio_handle_release(self);
	COMPILER_BARRIER();
	/* Decref the associated object (if any)
	 * You could use this for stuff like async release of DMA locks! */
	xdecref(obj);
	assert(hand != AIO_HANDLE_MULTIPLE_CONTROLLER_UNUSED &&
	       hand != AIO_HANDLE_MULTIPLE_CONTROLLER_COMPLETE);
	do {
		old_status = atomic_read(&hand->am_status);
		new_status = (uintptr_t)status << AIO_MULTIHANDLE_STATUS_STATUSSHFT;
		assert((old_status & AIO_MULTIHANDLE_STATUS_RUNMASK) != 0);
		if (old_status & AIO_MULTIHANDLE_STATUS_FAILED)
			return; /* Controller failure (ignore handle completion). */
		if (new_status <= (old_status & AIO_MULTIHANDLE_STATUS_STATUSMASK))
			new_status = old_status & AIO_MULTIHANDLE_STATUS_STATUSMASK; /* Don't update the status */
		new_status |= (old_status & ~(AIO_MULTIHANDLE_STATUS_STATUSMASK | AIO_MULTIHANDLE_STATUS_RUNMASK));
		new_status |= (old_status & (AIO_MULTIHANDLE_STATUS_RUNMASK)) - 1;
	} while (!atomic_cmpxch_weak(&hand->am_status, old_status, new_status));
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
		DBG_memset(ent, 0xcc, sizeof(*ent));
	}
	iter = self->am_ext;
	DBG_memset(&self->am_ext, 0xcc, sizeof(self->am_ext));
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

#ifndef CONFIG_NO_SMP
	/* Make sure that no other thread is still inside of `am_func' */
	while (!(atomic_read(&self->am_status) & AIO_MULTIHANDLE_STATUS_RELEASED))
		preemption_tryyield();
#endif /* !CONFIG_NO_SMP */

	DBG_memset(&self->am_func, 0xcc, sizeof(self->am_func));
	DBG_memset(&self->am_status, 0xcc, sizeof(self->am_status));
	DBG_memset(&self->am_error, 0xcc, sizeof(self->am_error));
}


/* Allocate handles for the purpose of AIO completion.
 * WARNING: Don't free a handle after you already started using it in the context of an AIO parameter. */
PUBLIC ATTR_RETNONNULL WUNUSED NONNULL((1)) struct aio_handle *KCALL
aio_multihandle_allochandle(struct aio_multihandle *__restrict self)
		THROWS(E_BADALLOC) {
	struct aio_handle_multiple *result;
	uintptr_t run_count;
	run_count = atomic_read(&self->am_status);
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
			ctrl   = atomic_read(&result->hg_controller);
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
				ctrl   = atomic_read(&result->hg_controller);
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
	DBG_memset(result, 0xcc, sizeof(struct aio_handle));
	result->ah_func       = &aio_handle_multiple_func;
	result->hg_controller = self;
	result->hg_obj        = xincref(self->am_obj);
	/* Required by `aio_multihandle_cancel()'
	 * Used to ensure that the handle was actually initialized. */
	result->ah_type = NULL;
	atomic_inc(&self->am_status); /* Increment the run counter. */
	return result;
}

PUBLIC WUNUSED NONNULL((1)) struct aio_handle *
NOTHROW(KCALL aio_multihandle_allochandle_nx)(struct aio_multihandle *__restrict self) {
	struct aio_handle_multiple *result;
	uintptr_t run_count;
	run_count = atomic_read(&self->am_status);
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
			ctrl   = atomic_read(&result->hg_controller);
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
				ctrl   = atomic_read(&result->hg_controller);
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
	DBG_memset(result, 0xcc, sizeof(struct aio_handle));
	result->ah_func       = &aio_handle_multiple_func;
	result->hg_controller = self;
	result->hg_obj        = xincref(self->am_obj);
	/* Required by `aio_multihandle_cancel()'
	 * Used to ensure that the handle was actually initialized. */
	result->ah_type = NULL;
	atomic_inc(&self->am_status); /* Increment the run counter. */
	return result;
err:
	return NULL;
}



/* Indicate that no further handles will be allocated, meaning that `self->am_func'
 * is  now allowed to be called once  all initiated operations have finished (which
 * may be immediately).
 * WARNING: This function should not be called after `aio_multihandle_fail()',
 *          or be called more than once! */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(KCALL aio_multihandle_done)(struct aio_multihandle *__restrict self) {
	uintptr_t old_status;
	for (;;) {
		old_status = atomic_read(&self->am_status);
		if (old_status & AIO_MULTIHANDLE_STATUS_FAILED)
			return; /* Controller already failed */
		assertf(!(old_status & AIO_MULTIHANDLE_STATUS_ALLRUNNING),
		        "Cannot call `aio_multihandle_done()' more than once");
		if (atomic_cmpxch_weak(&self->am_status, old_status, old_status | AIO_MULTIHANDLE_STATUS_ALLRUNNING))
			break;
	}

	/* Check if all AIO handles have already completed. */
	if ((old_status & AIO_MULTIHANDLE_STATUS_RUNMASK) == 0) {
		unsigned int status;
		preemption_flag_t was;

		/* Completion functions must  be called  with preemption  disabled,
		 * so satisfy that requirement by disabling preemption temporarily. */
		preemption_pushoff(&was);

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
		preemption_pop(&was);
	}
}



/* Handle the current exception using the given AIO multi-handle.
 * NOTE: This function will also call `aio_multihandle_cancel()' */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(KCALL aio_multihandle_fail)(struct aio_multihandle *__restrict self) {
	uintptr_t old_status;
	preemption_flag_t was;
	do {
		old_status = atomic_read(&self->am_status);
		if (old_status & AIO_MULTIHANDLE_STATUS_FAILED)
			return; /* Already failed. */
		assertf(!(old_status & AIO_MULTIHANDLE_STATUS_ALLRUNNING),
		        "Cannot call `aio_multihandle_fail()' after `aio_multihandle_done()'");
	} while (!atomic_cmpxch_weak(&self->am_status, old_status,
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
	preemption_pushoff(&was);
	(*self->am_func)(self, AIO_COMPLETION_FAILURE);
	preemption_pop(&was);
}


/* Cancel all currently running handles of `self'
 * NOTE: May be called multiple times without causing harm. */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(KCALL aio_multihandle_cancel)(struct aio_multihandle *__restrict self) {
	unsigned int i;
	struct aio_multihandle_extension *ext;
	for (i = 0; i < AIO_MULTIHANDLE_IVECLIMIT; ++i) {
		if (self->am_ivec[i].hg_controller && self->am_ivec[i].ah_type)
			aio_handle_cancel(&self->am_ivec[i]);
	}
	for (ext = self->am_ext; ext; ext = ext->ame_next) {
		for (i = 0; i < AIO_MULTIHANDLE_XVECLIMIT; ++i) {
			if (ext->ame_handles[i].hg_controller && ext->ame_handles[i].ah_type)
				aio_handle_cancel(&ext->ame_handles[i]);
		}
	}
}





/* Allocate and return a special AIO handle that can be used just like any other,
 * however will clean-up itself after  the usual init+complete+fini cycle of  any
 * given AIO handle. This allows the caller to use this handle to detach themself
 * from any async-operation such that the  operation will either succeed or  fail
 * at an arbitrary point in the future, potentially long after the caller started
 * the operation. To-be used as follows:
 * >> void nic_background_send(struct nicdev const *__restrict self,
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
 *       then  an  error   message  is  written   to  the  system   log.
 */
struct async_aio_handle: aio_handle {
	struct async_aio_handle *aah_next; /* [lock(IN_CHAIN(async_aio_handles))][0..1]
	                                    * The  next  used/free  async-aio   handle. */
	aio_completion_t         aah_func; /* [0..1] The user-defined completion function. */
};

/* [0..1][lock(ATOMIC)] Chain of used/free async-aio handles. */
PRIVATE WEAK struct async_aio_handle *async_aio_handles = NULL;

LOCAL NOBLOCK NONNULL((1, 2)) void
NOTHROW(KCALL aio_handle_async_restore_chain)(struct async_aio_handle *first,
                                              struct async_aio_handle *last) {
	struct async_aio_handle *next;
	do {
		next = atomic_read(&async_aio_handles);
		last->aah_next = next;
		COMPILER_WRITE_BARRIER();
	} while (!atomic_cmpxch_weak(&async_aio_handles, next, first));
}

/* Return the first handle with `aio_handle_completed(handle) == true'
 * from `async_aio_handles'  and remove  that handle  from the  chain.
 * If no such  handle exists, or  the chain is  already being used  by
 * some other thread, return `NULL' instead. */
PRIVATE NOBLOCK WUNUSED struct async_aio_handle *
NOTHROW(KCALL aio_handle_async_alloc_exising)(void) {
	struct async_aio_handle *chain, **piter, *iter;
	chain = atomic_xch(&async_aio_handles, NULL);
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
		DBG_memset(&result->aah_next, 0xcc, sizeof(result->aah_next));
		return result;
	}
	return NULL;
}


/* Remove all AIO handles that are `aio_handle_completed()'
 * from    `async_aio_handles',    and    kfree()     them. */
INTERN ATTR_BLOCKLIKE_CC(info) NONNULL((1)) void
NOTHROW(KCALL system_cc_async_aio_handles)(struct ccinfo *__restrict info) {
	/* TODO: A function similar to this one should be called when the CPU goes into
	 *       IDLE mode in order to finalize  and kfree() unused AIO handles,  since
	 *       in-use AIO handles could potentially  slow down the system since  they
	 *       might  contain arbitrary, device-specific references to other objects!
	 * TODO: This function should be called after driver finalization to delete AIO
	 *       handles which may still be holding references to the driver (Note that
	 *       such references would likely be indirect; e.g.: aio->device->driver). */
	/* TODO: Instead of periodically cleaning up handles, just pass them along to
	 *       some fixed thread (like boottask, asyncwork) in the form of an  RPC,
	 *       and then have *them* do the finalization. */
	size_t i;
	struct async_aio_handle *h;
	while ((h = aio_handle_async_alloc_exising()) != NULL) {
free_h:
		aio_handle_async_free(h);
		ccinfo_account(info, sizeof(struct async_aio_handle));
		if (ccinfo_isdone(info))
			return;
	}

	/* Try to yield to some other thread, who may still be holding AIO handles. */
	for (i = 0; i < 8; ++i) {
		if (task_tryyield() != TASK_TRYYIELD_SUCCESS)
			break;
		h = aio_handle_async_alloc_exising();
		if (h)
			goto free_h;
	}
}

PRIVATE NOBLOCK NOPREEMPT NONNULL((1)) void
NOTHROW(FCALL aio_handle_async_func)(struct aio_handle *__restrict self,
                                     unsigned int status) {
	struct async_aio_handle *me;
	me = (struct async_aio_handle *)self;
	/* Invoke the user-defined completion function (if defined) */
	if (me->aah_func) {
		(*me->aah_func)(me, status);
	} else {
		aio_handle_release(me);
		if (status == AIO_COMPLETION_FAILURE)
			except_printf("Performing background AIO operation");
	}
	aio_handle_async_restore_chain(me, me);
}


/* Allocate and return a special AIO handle that can be used just like any other,
 * however will clean-up itself after  the usual init+complete+fini cycle of  any
 * given AIO handle. This allows the caller to use this handle to detach themself
 * from any async-operation such that the  operation will either succeed or  fail
 * at an arbitrary point in the future, potentially long after the caller started
 * the operation. To-be used as follows:
 * >> void nic_background_send(struct nicdev const *__restrict self,
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
 * NOTE: When  the AIO operation completes with `AIO_COMPLETION_FAILURE', and
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
		/* Set-up  the  handle  such  that  it  will  add  itself  to  the
		 * async-aio-handle chain once its completion-function is invoked.
		 * NOTE: We can't have the completion-function simply kfree() the
		 *       handle  immediately, because the  caller of the callback
		 *       must still be able to  set the handle's next pointer  to
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
