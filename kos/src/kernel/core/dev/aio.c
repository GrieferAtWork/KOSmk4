/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_SRC_DEV_AIO_C
#define GUARD_KERNEL_SRC_DEV_AIO_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/aio.h>
#include <kernel/except.h>
#include <kernel/malloc.h>
#include <kernel/types.h>
#include <kernel/vm.h>
#include <sched/signal.h>

#include <hybrid/atomic.h>

#include <assert.h>
#include <string.h>

DECL_BEGIN

/* Callback for `aio_handle_generic' */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(KCALL aio_handle_generic_func_)(struct aio_handle_generic *__restrict self,
                                        unsigned int status)
		ASMNAME("aio_handle_generic_func");
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(KCALL aio_handle_generic_func_)(struct aio_handle_generic *__restrict self,
                                        unsigned int status) {
	self->hg_status = status;
	if (status == AIO_COMPLETION_FAILURE)
		memcpy(&self->hg_error, &THIS_EXCEPTION_INFO.ei_data,
		       sizeof(struct exception_data));
	COMPILER_WRITE_BARRIER();
	sig_broadcast(&self->hg_signal);
}

FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(KCALL aio_multihandle_generic_func_)(struct aio_multihandle_generic *__restrict self,
                                             unsigned int status)
		ASMNAME("aio_multihandle_generic_func");
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(KCALL aio_multihandle_generic_func_)(struct aio_multihandle_generic *__restrict self,
                                             unsigned int status) {
	sig_broadcast(&self->mg_signal);
}




/* Read/write/set data associated with AIO buffers. */
PUBLIC NONNULL((1)) void KCALL
aio_buffer_copyfromphys(struct aio_buffer const *__restrict self,
                        uintptr_t dst_offset, vm_phys_t src, size_t num_bytes)
		THROWS(E_SEGFAULT) {
	struct aio_buffer_entry ent;
	AIO_BUFFER_FOREACH_N(ent, self) {
		if (dst_offset >= ent.ab_size) {
			dst_offset -= ent.ab_size;
			continue;
		}
		if (ent.ab_size > num_bytes)
			ent.ab_size = num_bytes;
		vm_copyfromphys((byte_t *)ent.ab_base + dst_offset, src, ent.ab_size);
		if (ent.ab_size >= num_bytes)
			break;
		src += ent.ab_size;
		num_bytes -= ent.ab_size;
		dst_offset = 0;
	}
}

PUBLIC NONNULL((1)) void KCALL
aio_buffer_copytophys(struct aio_buffer const *__restrict self,
                      vm_phys_t dst, uintptr_t src_offset, size_t num_bytes)
		THROWS(E_SEGFAULT) {
	struct aio_buffer_entry ent;
	AIO_BUFFER_FOREACH_N(ent, self) {
		if (src_offset >= ent.ab_size) {
			src_offset -= ent.ab_size;
			continue;
		}
		if (ent.ab_size > num_bytes)
			ent.ab_size = num_bytes;
		vm_copytophys(dst, (byte_t *)ent.ab_base + src_offset, ent.ab_size);
		if (ent.ab_size >= num_bytes)
			break;
		dst += ent.ab_size;
		num_bytes -= ent.ab_size;
		src_offset = 0;
	}
}

PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(KCALL aio_pbuffer_memset)(struct aio_pbuffer const *__restrict self,
                                  uintptr_t dst_offset, int byte, size_t num_bytes) {
	struct aio_pbuffer_entry ent;
	AIO_PBUFFER_FOREACH_N(ent, self) {
		if (dst_offset >= ent.ab_size) {
			dst_offset -= ent.ab_size;
			continue;
		}
		if (ent.ab_size > num_bytes)
			ent.ab_size = num_bytes;
		vm_memsetphys(ent.ab_base + dst_offset, byte, ent.ab_size);
		if (ent.ab_size >= num_bytes)
			break;
		num_bytes -= ent.ab_size;
		dst_offset = 0;
	}
}

PUBLIC NONNULL((1)) void KCALL
aio_pbuffer_copyfrommem(struct aio_pbuffer const *__restrict self,
                        uintptr_t dst_offset,
                        USER CHECKED void const *src, size_t num_bytes)
		THROWS(E_SEGFAULT) {
	struct aio_pbuffer_entry ent;
	AIO_PBUFFER_FOREACH_N(ent, self) {
		if (dst_offset >= ent.ab_size) {
			dst_offset -= ent.ab_size;
			continue;
		}
		if (ent.ab_size > num_bytes)
			ent.ab_size = num_bytes;
		vm_copytophys(ent.ab_base + dst_offset, src, ent.ab_size);
		if (ent.ab_size >= num_bytes)
			break;
		src = (byte_t *)src + ent.ab_size;
		num_bytes -= ent.ab_size;
		dst_offset = 0;
	}
}

PUBLIC NONNULL((1)) void KCALL
aio_pbuffer_copytomem(struct aio_pbuffer const *__restrict self,
                      USER CHECKED void *dst,
                      uintptr_t src_offset, size_t num_bytes)
       THROWS(E_SEGFAULT) {
	struct aio_pbuffer_entry ent;
	AIO_PBUFFER_FOREACH_N(ent, self) {
		if (src_offset >= ent.ab_size) {
			src_offset -= ent.ab_size;
			continue;
		}
		if (ent.ab_size > num_bytes)
			ent.ab_size = num_bytes;
		vm_copyfromphys(dst, (vm_phys_t)(ent.ab_base + src_offset), ent.ab_size);
		if (ent.ab_size >= num_bytes)
			break;
		dst = (byte_t *)dst + ent.ab_size;
		num_bytes -= ent.ab_size;
		src_offset = 0;
	}
}

PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(KCALL aio_pbuffer_copyfromphys)(struct aio_pbuffer const *__restrict self,
                                        uintptr_t dst_offset,
                                        vm_phys_t src, size_t num_bytes) {
	struct aio_pbuffer_entry ent;
	AIO_PBUFFER_FOREACH_N(ent, self) {
		if (dst_offset >= ent.ab_size) {
			dst_offset -= ent.ab_size;
			continue;
		}
		if (ent.ab_size > num_bytes)
			ent.ab_size = num_bytes;
		vm_copyinphys(ent.ab_base + dst_offset, src, ent.ab_size);
		if (ent.ab_size >= num_bytes)
			break;
		src += ent.ab_size;
		num_bytes -= ent.ab_size;
		dst_offset = 0;
	}
}

PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(KCALL aio_pbuffer_copytophys)(struct aio_pbuffer const *__restrict self,
                                      vm_phys_t dst,
                                      uintptr_t src_offset, size_t num_bytes) {
	struct aio_pbuffer_entry ent;
	AIO_PBUFFER_FOREACH_N(ent, self) {
		if (src_offset >= ent.ab_size) {
			src_offset -= ent.ab_size;
			continue;
		}
		if (ent.ab_size > num_bytes)
			ent.ab_size = num_bytes;
		vm_copyinphys(dst, ent.ab_base + src_offset, ent.ab_size);
		if (ent.ab_size >= num_bytes)
			break;
		dst += ent.ab_size;
		num_bytes -= ent.ab_size;
		src_offset = 0;
	}
}




/* Callback for `aio_handle_multiple' */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(KCALL aio_handle_multiple_func_)(struct aio_handle_multiple *__restrict self,
                                         unsigned int status)
		ASMNAME("aio_handle_multiple_func");
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(KCALL aio_handle_multiple_func_)(struct aio_handle_multiple *__restrict self,
                                         unsigned int status) {
	struct aio_multihandle *hand;
	uintptr_t old_status;
	uintptr_t new_status;
	hand = self->hg_controller;
	self->hg_controller = NULL;
	COMPILER_BARRIER();
	assert(hand != NULL);
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
		memcpy(&hand->am_error, &THIS_EXCEPTION_INFO.ei_data, sizeof(hand->am_error));
	if (!(old_status & AIO_MULTIHANDLE_STATUS_ALLRUNNING))
		return; /* Premature completion (don't invoke the callback, yet) */
	if ((old_status & AIO_MULTIHANDLE_STATUS_RUNMASK) == 1) {
		/* Last callback. */
		unsigned int final_status;
		final_status = (new_status & AIO_MULTIHANDLE_STATUS_STATUSMASK) >> AIO_MULTIHANDLE_STATUS_STATUSSHFT;
		if (final_status == AIO_COMPLETION_FAILURE)
			memcpy(&THIS_EXCEPTION_INFO.ei_data, &hand->am_error, sizeof(hand->am_error));
		(*hand->am_func)(hand, final_status);
	}
}



PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(KCALL aio_multihandle_extension_destroy)(struct aio_multihandle_extension *__restrict self) {
	struct aio_multihandle_extension *next;
	for (;;) {
		next = self->ame_next;
		kfree(self);
		if (!next)
			break;
		self = next;
	}
}

/* Allocate handles for the purpose of AIO completion.
 * WARNING: Don't free a handle after you already started using it in the context of an AIO parameter.
 * NOTE: `aio_multihandle_allochandle()' calls `aio_multihandle_fail()' upon
 *       error, before returning propagating an error / returning `NULL'. */
PUBLIC WUNUSED ATTR_RETNONNULL NONNULL((1)) struct aio_handle *KCALL
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
			result = &self->am_ivec[i];
			if (!result->hg_controller)
				goto fill_in_result;
		}
		for (iter = self->am_ext; iter; iter = iter->ame_next) {
			for (i = 0; i < AIO_MULTIHANDLE_XVECLIMIT; ++i) {
				result = &iter->ame_handles[i];
				if (!result->hg_controller)
					goto fill_in_result;
			}
		}
		/* Must allocate a new extension table. */
		iter = (struct aio_multihandle_extension *)kmalloc(sizeof(struct aio_multihandle_extension),
		                                                   GFP_CALLOC | GFP_PREFLT | GFP_LOCKED);
		result         = &iter->ame_handles[0];
		iter->ame_next = self->am_ext;
		self->am_ext   = iter;
	}
fill_in_result:
	result->ah_func       = &aio_handle_multiple_func;
	result->hg_controller = self;
	ATOMIC_FETCHINC(self->am_status); /* Increment the run counter. */
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
			result = &self->am_ivec[i];
			if (!result->hg_controller)
				goto fill_in_result;
		}
		for (iter = self->am_ext; iter; iter = iter->ame_next) {
			for (i = 0; i < AIO_MULTIHANDLE_XVECLIMIT; ++i) {
				result = &iter->ame_handles[i];
				if (!result->hg_controller)
					goto fill_in_result;
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
	result->ah_func       = &aio_handle_multiple_func;
	result->hg_controller = self;
	ATOMIC_FETCHINC(self->am_status); /* Increment the run counter. */
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
		if (status == AIO_COMPLETION_FAILURE)
			memcpy(&THIS_EXCEPTION_INFO.ei_data, &self->am_error, sizeof(self->am_error));
		/* Invoke the completion callback. */
		(*self->am_func)(self, status);
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
		memcpy(&self->am_error, &THIS_EXCEPTION_INFO.ei_data, sizeof(self->am_error));
	/* Invoke the completion function. */
	memcpy(&THIS_EXCEPTION_INFO.ei_data, &self->am_error, sizeof(self->am_error));
	(*self->am_func)(self, AIO_COMPLETION_FAILURE);
}


PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(KCALL aio_multihandle_cancel)(struct aio_multihandle *__restrict self) {
	unsigned int i;
	struct aio_multihandle_extension *ext;
	for (i = 0; i < AIO_MULTIHANDLE_IVECLIMIT; ++i) {
		if (self->am_ivec[i].hg_controller &&
		    self->am_ivec[i].ah_type)
			aio_handle_cancel(&self->am_ivec[i]);
	}
	for (ext = self->am_ext; ext; ext = ext->ame_next) {
		for (i = 0; i < AIO_MULTIHANDLE_XVECLIMIT; ++i) {
			if (ext->ame_handles[i].hg_controller &&
			    ext->ame_handles[i].ah_type)
				aio_handle_cancel(&ext->ame_handles[i]);
		}
	}
	assertf((ATOMIC_READ(self->am_status) & AIO_MULTIHANDLE_STATUS_RUNMASK) == 0,
	        "self->am_status = %.8I64X\n", self->am_status);
}





DECL_END

#endif /* !GUARD_KERNEL_SRC_DEV_AIO_C */
