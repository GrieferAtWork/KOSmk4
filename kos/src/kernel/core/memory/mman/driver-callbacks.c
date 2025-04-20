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
#ifndef GUARD_KERNEL_SRC_MEMORY_DRIVER_CALLBACKS_C
#define GUARD_KERNEL_SRC_MEMORY_DRIVER_CALLBACKS_C 1

#include <kernel/compiler.h>

#include <kernel/driver-callbacks.h>
#include <kernel/driver.h>
#include <kernel/malloc.h>

#include <kos/aref.h>
#include <kos/except.h>

#include <assert.h>
#include <stddef.h>

DECL_BEGIN

#undef callback_list_insert
#undef callback_list_remove
PUBLIC NOBLOCK void
NOTHROW(KCALL callback_list_detroy)(struct callback_list_struct *__restrict self) {
	size_t i;
	for (i = 0; i < self->cl_count; ++i)
		decref_unlikely(self->cl_list[i].cn_orig);
	kfree(self);
}

PUBLIC bool
(KCALL callback_list_insert)(__callback_list_t *__restrict self,
                             void (*func)(),
                             struct driver *__restrict orig)
		THROWS(E_BADALLOC, E_WOULDBLOCK) {
	size_t i;
	bool success;
	REF struct callback_list_struct *state;
	REF struct callback_list_struct *new_state;
again:
	state = arref_get(self);
	for (i = 0; i < state->cl_count; ++i) {
		if likely(state->cl_list[i].cn_func != func)
			continue;
		decref_unlikely(state);
		return false;
	}
	/* Create a new state */
	TRY {
		new_state = (REF struct callback_list_struct *)kmalloc(offsetof(struct callback_list_struct, cl_list) +
		                                                       (state->cl_count + 1) *
		                                                       sizeof(struct callback_node_struct),
		                                                       GFP_LOCKED | GFP_PREFLT);
	} EXCEPT {
		decref_unlikely(state);
		RETHROW();
	}
	new_state->cl_refcnt = 1;
	new_state->cl_count  = state->cl_count + 1;
	for (i = 0; i < state->cl_count; ++i) {
		new_state->cl_list[i] = state->cl_list[i];
		incref(new_state->cl_list[i].cn_orig);
	}
	/* Append the new function. */
	assert(i == new_state->cl_count - 1);
	new_state->cl_list[i].cn_func = func;
	new_state->cl_list[i].cn_orig = incref(orig);
	/* Try to set the new state. */
	success = arref_cmpxch_inherit_new(self, state, new_state);
	if likely(state != &__callback_list_empty)
		decref_likely(state);
	if likely(success)
		return true;
	destroy(new_state);
	goto again;
}

PUBLIC bool
(KCALL callback_list_remove)(__callback_list_t *__restrict self,
                             void (*func)())
		THROWS(E_BADALLOC, E_WOULDBLOCK) {
	size_t i;
	REF struct callback_list_struct *state;
	REF struct callback_list_struct *new_state;
again:
	state = arref_get(self);
	for (i = 0; i < state->cl_count; ++i) {
		bool success;
		if (state->cl_list[i].cn_func != func)
			continue;
		/* Found it. */
		if unlikely(state->cl_count == 1) {
			new_state = &__callback_list_empty;
		} else {
			size_t j;
			TRY {
				new_state = (REF struct callback_list_struct *)kmalloc(offsetof(struct callback_list_struct, cl_list) +
				                                                       (state->cl_count - 1) *
				                                                       sizeof(struct callback_node_struct),
				                                                       GFP_LOCKED | GFP_PREFLT);
			} EXCEPT {
				decref_unlikely(state);
				RETHROW();
			}
			new_state->cl_refcnt = 1;
			new_state->cl_count  = state->cl_count - 1;
			for (j = 0; j < i; ++j) {
				new_state->cl_list[j] = state->cl_list[j];
				incref(new_state->cl_list[j].cn_orig);
			}
			for (++j; j < state->cl_count; ++j) {
				new_state->cl_list[j - 1] = state->cl_list[j];
				incref(new_state->cl_list[j - 1].cn_orig);
			}
		}
		success = arref_cmpxch_inherit_new_nokill(self, state, new_state);
		if likely(state != &__callback_list_empty)
			decref_likely(state);
		if likely(success)
			return true;
		destroy(new_state);
		goto again;
	}
	decref_unlikely(state);
	return false;
}


INTDEF struct driver_state empty_driver_state;
DEFINE_INTERN_ALIAS(empty_driver_state, callback_list_empty);

PUBLIC struct callback_list_struct callback_list_empty = {
	.cl_refcnt = 2, /* +1: empty_driver_state, +1: current_driver_state */
	.cl_count  = 0,
};

DECL_END

#endif /* !GUARD_KERNEL_SRC_MEMORY_DRIVER_CALLBACKS_C */
