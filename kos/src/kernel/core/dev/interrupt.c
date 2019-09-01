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
#ifndef GUARD_KERNEL_SRC_DEV_INTERRUPT_C
#define GUARD_KERNEL_SRC_DEV_INTERRUPT_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/driver.h>
#include <kernel/except.h>
#include <kernel/heap.h>
#include <kernel/interrupt.h>
#include <kernel/printk.h>
#include <kernel/types.h>
#include <misc/atomic-ref.h>

#include <hybrid/atomic.h>

#include <assert.h>
#include <stddef.h>
#include <string.h>

DECL_BEGIN

STATIC_ASSERT(!ISR_VECTOR_IS_VALID(ISR_VECTOR_INVALID));

#ifndef __INTELLISENSE__
#define ASSERT_INDICES(idx, vec)                        \
	STATIC_ASSERT(ISR_VECTOR_TO_INDEX(0x##vec) == idx); \
	STATIC_ASSERT(ISR_INDEX_TO_VECTOR(idx) == 0x##vec);
#define ASSERT_INDICES_SPECIFIC(idx, vec)                                          \
	STATIC_ASSERT(ISR_VECTOR_TO_INDEX(0x##vec) == idx + ISR_GENERIC_VECTOR_COUNT); \
	STATIC_ASSERT(ISR_INDEX_TO_VECTOR(idx + ISR_GENERIC_VECTOR_COUNT) == 0x##vec);
ISR_GENERIC_VECTOR_ENUM(ASSERT_INDICES);
ISR_SPECIFIC_VECTOR_ENUM(ASSERT_INDICES_SPECIFIC);
#undef ASSERT_INDICES_SPECIFIC
#undef ASSERT_INDICES
#endif /* !__INTELLISENSE__ */

#define ISR_COUNT  (ISR_GENERIC_VECTOR_COUNT + ISR_SPECIFIC_VECTOR_COUNT)


PUBLIC NOBLOCK void
NOTHROW(KCALL isr_vector_state_destroy)(struct isr_vector_state *__restrict self) {
	size_t i;
	for (i = 0; i < self->ivs_handc; ++i) {
		decref_unlikely(self->ivs_handv[i].ivh_drv);
	}
	xdecref_unlikely(self->ivs_greedy_drv);
	heap_free(&kernel_locked_heap, self, self->ivs_heapsize, GFP_LOCKED);
}


PRIVATE REF struct isr_vector_state *
(KCALL isr_vector_state_alloc)(size_t handc) THROWS(E_BADALLOC) {
	REF struct isr_vector_state *result;
	struct heapptr ptr = heap_alloc(&kernel_locked_heap,
	                                offsetof(struct isr_vector_state, ivs_handv) +
	                                handc * sizeof(struct isr_vector_handler),
	                                GFP_LOCKED | GFP_PREFLT);
	result = (REF struct isr_vector_state *)ptr.hp_ptr;
	result->ivs_heapsize = ptr.hp_siz;
	result->ivs_refcnt   = 1;
	result->ivs_handc    = handc;
	return result;
}


PRIVATE struct isr_vector_state empty_vector_state = {
	/* .ivs_refcnt     = */1 + ISR_COUNT,
	/* .ivs_heapsize   = */offsetof(struct isr_vector_state, ivs_handv),
	/* .ivs_greedy_fun = */NULL,
	/* .ivs_greedy_arg = */NULL,
	/* .ivs_greedy_drv = */NULL,
	/* .ivs_greedy_cnt = */0,
	/* .ivs_unhandled  = */0,
	/* .ivs_handc      = */0,
	/* .ivs_handv      = */{ }
};


/* The main ISR vector table. */
PRIVATE ATTR_SECTION(".data.hot.read_mostly.tail")
ATOMIC_REF(struct isr_vector_state) isr_vectors[ISR_COUNT] = {
#define ENUM_EMPTY_VECTOR_STATE(idx, vec) ATOMIC_REF_INIT(&empty_vector_state),
	ISR_GENERIC_VECTOR_ENUM(ENUM_EMPTY_VECTOR_STATE)
	ISR_SPECIFIC_VECTOR_ENUM(ENUM_EMPTY_VECTOR_STATE)
#undef ENUM_EMPTY_VECTOR_STATE
};

LOCAL bool KCALL
isr_try_register_at_impl(/*inherit(on_success)*/REF struct driver *__restrict func_driver,
                         struct isr_vector_state *__restrict old_state, size_t index,
                         void *func, void *arg, bool is_greedy)
		THROWS(E_BADALLOC) {
	size_t i;
	struct isr_vector_state *new_state;
	new_state = isr_vector_state_alloc(is_greedy ? old_state->ivs_handc
	                                             : old_state->ivs_handc + 1);
	if (is_greedy) {
		assert(!old_state->ivs_greedy_drv);
		new_state->ivs_greedy_fun = (isr_greedy_function_t)func;
		new_state->ivs_greedy_arg = arg;
		new_state->ivs_greedy_drv = incref(func_driver);
		new_state->ivs_greedy_cnt = 0;
		memcpy(new_state->ivs_handv,
		       old_state->ivs_handv,
		       old_state->ivs_handc * sizeof(struct isr_vector_handler));
		for (i = 0; i < old_state->ivs_handc; ++i) {
			incref(new_state->ivs_handv[i].ivh_drv);
		}
	} else {
		new_state->ivs_greedy_fun = old_state->ivs_greedy_fun;
		new_state->ivs_greedy_arg = old_state->ivs_greedy_arg;
		new_state->ivs_greedy_drv = xincref(old_state->ivs_greedy_drv);
		new_state->ivs_greedy_cnt = old_state->ivs_greedy_cnt;
		/* Load the new function as the primary handler, so
		 * we can more easily determine its hit/miss ratio. */
		new_state->ivs_handv[0].ivh_fun = (isr_function_t)func;
		new_state->ivs_handv[0].ivh_arg = arg;
		new_state->ivs_handv[0].ivh_drv = incref(func_driver);
		memcpy(new_state->ivs_handv + 1,
		       old_state->ivs_handv,
		       old_state->ivs_handc * sizeof(struct isr_vector_handler));
		for (i = 1; i < new_state->ivs_handc; ++i) {
			assert(new_state->ivs_handv[i].ivh_fun != (isr_function_t)func);
			incref(new_state->ivs_handv[i].ivh_drv);
		}
	}
	new_state->ivs_unhandled = ATOMIC_READ(old_state->ivs_unhandled);
	/* With the new state now fully initialized, try to install it (atomically). */
	if (isr_vectors[index].cmpxch_inherit_new(old_state, new_state)) {
		printk(KERN_INFO "[isr] Register handler for vector %#Ix (%[vinfo:%n(%p)] with %p in driver %q)\n",
		       (size_t)ISR_INDEX_TO_VECTOR(index), func, arg, func_driver->d_name);
		decref(func_driver); /* Inherit on success. */
		return true;
	}
	/* Failed to install the new state (so we must destroy it now) */
	decref(new_state);  /* Destroy the new state. */
	return false;
}

LOCAL isr_vector_t KCALL
isr_register_impl(void *func, void *arg, bool is_greedy)
		THROWS(E_BADALLOC, E_BADALLOC_INSUFFICIENT_INTERRUPT_VECTORS) {
	bool success;
	REF struct driver *func_driver;
	REF struct isr_vector_state *winner;
	size_t i, winner_index = 0;
	uintptr_t cache_version;
	cache_version = 0;
	func_driver = driver_at_address(func);
	/* Make sure that a driver exists at the given address. */
	if unlikely(!func_driver)
		THROW(E_SEGFAULT_NOTEXECUTABLE, func, E_SEGFAULT_CONTEXT_FAULT);
again_check_finalizing:
	/* Make sure that the driver is still alive. */
	if unlikely(driver_isfinalizing(func_driver)) {
		decref(func_driver);
		return ISR_VECTOR_INVALID;
	}
again_determine_winner:
	winner = isr_vectors[winner_index].get();
	if (winner->ivs_handc || winner->ivs_greedy_drv) {
		/* Search for the vector with the least amount of handlers,
		 * preferring those without greedy handlers over those with. */
		for (i = 1; i < ISR_COUNT; ++i) {
			REF struct isr_vector_state *temp;
			temp = isr_vectors[i].get();
			if ((!is_greedy || !temp->ivs_greedy_drv) &&
			    (temp->ivs_handc < winner->ivs_handc ||
			    (temp->ivs_handc == winner->ivs_handc &&
			     winner->ivs_greedy_drv && !temp->ivs_greedy_drv))) {
				decref_unlikely(winner);
				winner = temp;
				winner_index = i;
				if (!winner->ivs_handc && !winner->ivs_greedy_drv)
					goto got_perfect_winner;
			} else {
				decref_unlikely(temp);
			}
		}
	}
	if unlikely(is_greedy && winner->ivs_greedy_fun) {
		/* Try to reclaim cache resources, which may free up a suitable interrupt vector slot. */
		if (system_clearcaches_s(&cache_version))
			goto again_check_finalizing;
		decref_unlikely(func_driver);
		THROW(E_BADALLOC_INSUFFICIENT_INTERRUPT_VECTORS, (uintptr_t)-1);
	}
got_perfect_winner:
	/* Try to register the function as part of the winning ISR slot. */
	TRY {
		success = isr_try_register_at_impl(func_driver,
		                                   winner,
		                                   winner_index,
		                                   func,
		                                   arg,
		                                   is_greedy);
	} EXCEPT {
		decref_unlikely(func_driver);
		decref(winner);
		RETHROW();
	}
	decref(winner);
	if (success) /* Upon success, return the vector for the winning index. */
		return (isr_vector_t)ISR_INDEX_TO_VECTOR(winner_index);
	/* The winner must have changed in the mean time. - Try again */
	goto again_determine_winner;
}

PRIVATE isr_vector_t KCALL
isr_register_at_impl(isr_vector_t vector, void *func, void *arg, bool is_greedy)
		THROWS(E_BADALLOC, E_BADALLOC_INSUFFICIENT_INTERRUPT_VECTORS) {
	bool success;
	REF struct driver *func_driver;
	REF struct isr_vector_state *old_state;
	size_t index;
	uintptr_t cache_version;
	cache_version = 0;
	/* Make sure that the given vector is valid. - If it isn't,
	 * act like it's impossible to allocate further data for it. */
	if unlikely(!ISR_VECTOR_IS_VALID(vector))
		THROW(E_BADALLOC_INSUFFICIENT_INTERRUPT_VECTORS, vector);
	func_driver = driver_at_address(func);
	/* Make sure that a driver exists at the given address. */
	if unlikely(!func_driver)
		THROW(E_SEGFAULT_NOTEXECUTABLE, func, E_SEGFAULT_CONTEXT_FAULT);
	/* Make sure that the driver is still alive. */
again_check_finalizing:
	if unlikely(driver_isfinalizing(func_driver)) {
		decref_unlikely(func_driver);
		return ISR_VECTOR_INVALID;
	}
	index = ISR_VECTOR_TO_INDEX(vector);
again_get_old_state:
	old_state = isr_vectors[index].get();
	if (is_greedy && old_state->ivs_greedy_drv) {
		/* The old vector is already in use. */
		decref(old_state);
		/* Try to reclaim resources. */
		if (system_clearcaches_s(&cache_version))
			goto again_check_finalizing;
		decref_unlikely(func_driver);
		THROW(E_BADALLOC_INSUFFICIENT_INTERRUPT_VECTORS, vector);
	}
	TRY {
		success = isr_try_register_at_impl(func_driver,
		                                   old_state,
		                                   index,
		                                   func,
		                                   arg,
		                                   is_greedy);
	} EXCEPT {
		decref_unlikely(func_driver);
		decref(old_state);
		RETHROW();
	}
	decref(old_state);
	if (success)
		return vector;
	goto again_get_old_state;
}


FUNDEF bool KCALL
isr_unregister_(void *func, void *arg)
		ASMNAME("isr_unregister")
		THROWS(E_BADALLOC);

FUNDEF bool KCALL
isr_unregister_at_(isr_vector_t vector, void *func, void *arg)
		ASMNAME("isr_unregister_at")
		THROWS(E_BADALLOC);

FUNDEF bool KCALL
isr_unregister_any_(void *func)
		ASMNAME("isr_unregister_any")
		THROWS(E_BADALLOC);

FUNDEF bool KCALL
isr_unregister_any_at_(isr_vector_t vector, void *func)
		ASMNAME("isr_unregister_any_at")
		THROWS(E_BADALLOC);

PRIVATE NOBLOCK bool KCALL
isr_unregister_impl(size_t index, void *func, void *arg, bool ignore_arg)
		THROWS(E_BADALLOC) {
	bool success; size_t i;
	struct isr_vector_state *old_state;
	struct isr_vector_state *new_state;
	struct driver *declaring_driver;
	assert(index < ISR_COUNT);
again:
	old_state = isr_vectors[index].get();
	if ((old_state->ivs_greedy_fun == func) &&
		(old_state->ivs_greedy_arg == arg || ignore_arg)) {
		/* Delete the greedy handler of this ISR */
		if (old_state->ivs_handc == 0) {
			new_state = incref(&empty_vector_state);
		} else {
			new_state = isr_vector_state_alloc(old_state->ivs_handc);
			new_state->ivs_greedy_fun = NULL;
			new_state->ivs_greedy_arg = NULL;
			new_state->ivs_greedy_drv = NULL;
			new_state->ivs_greedy_cnt = 0;
			memcpy(new_state->ivs_handv, old_state->ivs_handv,
			       old_state->ivs_handc * sizeof(struct isr_vector_handler));
			for (i = 0; i < new_state->ivs_handc; ++i) {
				incref(new_state->ivs_handv[i].ivh_drv);
			}
		}
		arg              = old_state->ivs_greedy_arg;
		declaring_driver = old_state->ivs_greedy_drv;
assign_new_state:
		new_state->ivs_unhandled = ATOMIC_READ(old_state->ivs_unhandled);
		success = isr_vectors[index].cmpxch_inherit_new(old_state, new_state);
		if unlikely(!success) {
			decref(old_state);
			decref(new_state); /* Not inherited on failure */
			goto again;
		}
		printk(KERN_INFO "[isr] Delete handler for vector %#Ix (%[vinfo:%n(%p)] with %p in driver %q)\n",
		       (size_t)ISR_INDEX_TO_VECTOR(index), func, arg, declaring_driver->d_name);
		decref(old_state);
		return true;
	}

	/* Search the handler vector for the given func+arg. */
	for (i = 0; i < old_state->ivs_handc; ++i) {
		if (old_state->ivs_handv[i].ivh_fun != func)
			continue;
		if (old_state->ivs_handv[i].ivh_arg != arg && !ignore_arg)
			continue;
		/* Found it! */
		if (old_state->ivs_handc == 1 && !old_state->ivs_greedy_drv) {
			new_state = incref(&empty_vector_state);
		} else {
			new_state = isr_vector_state_alloc(old_state->ivs_handc - 1);
			new_state->ivs_greedy_fun = old_state->ivs_greedy_fun;
			new_state->ivs_greedy_arg = old_state->ivs_greedy_arg;
			new_state->ivs_greedy_drv = xincref(old_state->ivs_greedy_drv);
			new_state->ivs_greedy_cnt = old_state->ivs_greedy_cnt;
			/* Copy handlers, but leave out the one at index=`i' */
			memcpy(&new_state->ivs_handv[0],
			       &old_state->ivs_handv[0],
			       i * sizeof(struct isr_vector_handler));
			memcpy(&new_state->ivs_handv[i],
			       &old_state->ivs_handv[i + 1],
			       (new_state->ivs_handc - i) *
			       sizeof(struct isr_vector_handler));
			for (i = 0; i < new_state->ivs_handc; ++i) {
				incref(new_state->ivs_handv[i].ivh_drv);
			}
		}
		arg              = old_state->ivs_handv[i].ivh_arg;
		declaring_driver = old_state->ivs_handv[i].ivh_drv;
		goto assign_new_state;
	}

	/* Not found */
	decref_unlikely(old_state);
	return false;
}


PUBLIC NOBLOCK bool KCALL
isr_unregister_(void *func, void *arg) THROWS(E_BADALLOC) {
	size_t i;
	for (i = 0; i < ISR_COUNT; ++i) {
		if (isr_unregister_impl(i, func, arg, false))
			return true;
	}
	return false;
}

PUBLIC NOBLOCK bool KCALL
isr_unregister_at_(isr_vector_t vector, void *func, void *arg) THROWS(E_BADALLOC) {
	if unlikely(!ISR_VECTOR_IS_VALID(vector))
		return false;
	return isr_unregister_impl(ISR_VECTOR_TO_INDEX(vector),
	                           func, arg, false);
}

PUBLIC NOBLOCK bool KCALL
isr_unregister_any_(void *func) THROWS(E_BADALLOC) {
	size_t i;
	for (i = 0; i < ISR_COUNT; ++i) {
		if (isr_unregister_impl(i, func, NULL, true))
			return true;
	}
	return false;
}

PUBLIC NOBLOCK bool KCALL
isr_unregister_any_at_(isr_vector_t vector, void *func) THROWS(E_BADALLOC) {
	if unlikely(!ISR_VECTOR_IS_VALID(vector))
		return false;
	return isr_unregister_impl(ISR_VECTOR_TO_INDEX(vector),
	                           func, NULL, true);
}


/* Register ISR handlers, either by automatically selecting an
 * appropriate vector, or by specifying the required vector.
 * WARNING: The caller is responsible to ensure that any given func+arg
 *          combination will only be registered once.
 * @return: ISR_VECTOR_INVALID: The given `func' maps to a driver that is currently being finalized.
 * @throws: E_SEGFAULT:         The given `func' doesn't map to the static segment of any known driver.
 * @throws: E_BADALLOC_INSUFFICIENT_INTERRUPT_VECTORS: The given, or all vectors are already in use,
 *                                                     or the given vector cannot be allocated. */
PUBLIC isr_vector_t KCALL
isr_register(isr_function_t func,
             void *arg)
		THROWS(E_BADALLOC) {
	return isr_register_impl((void *)func, arg, false);
}
PUBLIC isr_vector_t KCALL
isr_register_at(isr_vector_t vector,
                isr_function_t func,
                void *arg)
		THROWS(E_BADALLOC) {
	return isr_register_at_impl(vector, (void *)func, arg, false);
}
PUBLIC isr_vector_t KCALL
isr_register_greedy(isr_greedy_function_t func,
                    void *arg)
		THROWS(E_BADALLOC, E_BADALLOC_INSUFFICIENT_INTERRUPT_VECTORS) {
	return isr_register_impl((void *)func, arg, true);
}
PUBLIC isr_vector_t KCALL
isr_register_greedy_at(isr_vector_t vector,
                       isr_greedy_function_t func,
                       void *arg)
		THROWS(E_BADALLOC, E_BADALLOC_INSUFFICIENT_INTERRUPT_VECTORS) {
	return isr_register_at_impl(vector, (void *)func, arg, true);
}




/* Return the usage descriptor for the given ISR vector. */
PUBLIC NOBLOCK ATTR_RETNONNULL REF struct isr_vector_state *
NOTHROW(KCALL isr_usage_of)(isr_vector_t vector) {
	if unlikely(!ISR_VECTOR_IS_VALID(vector))
		return incref(&empty_vector_state);
	return isr_vectors[ISR_VECTOR_TO_INDEX(vector)].get();
}

LOCAL ATTR_CONST NOBLOCK bool
NOTHROW(KCALL compare_hitmiss_gr)(size_t hit_a, size_t miss_a,
                                  size_t hit_b, size_t miss_b) {
	size_t total_a, total_b;
	size_t ratio_a, ratio_b;
	total_a = hit_a + miss_a;
	if (!total_a)
		return false;
	total_b = hit_b + miss_b;
	if (!total_b)
		return true;
	ratio_a = hit_a / total_a;
	ratio_b = hit_b / total_b;
	/* Compare the truncated ratios. */
	if (ratio_a > ratio_b)
		return true;
	if (ratio_a < ratio_b)
		return false;
	/* Compare the remainder. */
	ratio_a = hit_a % total_a;
	ratio_b = hit_b % total_b;
	return ratio_a > ratio_b;
}

LOCAL ATTR_PURE NOBLOCK bool
NOTHROW(KCALL compare_handler_hitmiss_gr)(struct isr_vector_handler const *__restrict a,
                                          struct isr_vector_handler const *__restrict b) {
	return compare_hitmiss_gr(a->ivh_hit, a->ivh_mis,
	                          b->ivh_hit, b->ivh_mis);
}


/* Try to re-order ISR handlers such that `src_handler_index' gets moved
 * closer to the start of the handler vector, placing it at `dst_handler_index' */
PRIVATE NOBLOCK ATTR_NOINLINE bool
NOTHROW(KCALL isr_try_reorder_handlers)(size_t vector_index,
                                        struct isr_vector_state *__restrict old_state,
                                        size_t src_handler_index,
                                        size_t dst_handler_index) {
	struct heapptr ptr; size_t i;
	struct isr_vector_state *new_state;
	assert(dst_handler_index < src_handler_index);
	/* Try to allocate a new state. (Using NX + ATOMIC to make this async-safe) */
	ptr = heap_alloc_nx(&kernel_locked_heap,
	                    offsetof(struct isr_vector_state, ivs_handv) +
	                    old_state->ivs_handc * sizeof(struct isr_vector_handler),
	                    GFP_LOCKED | GFP_PREFLT | GFP_ATOMIC);
	if (!ptr.hp_siz)
		return false; /* Allocation failed. */
	new_state = (struct isr_vector_state *)ptr.hp_ptr;
	new_state->ivs_heapsize   = ptr.hp_siz;
	new_state->ivs_refcnt     = 1;
	new_state->ivs_handc      = old_state->ivs_handc;
	new_state->ivs_greedy_fun = old_state->ivs_greedy_fun;
	new_state->ivs_greedy_arg = old_state->ivs_greedy_arg;
	new_state->ivs_greedy_drv = xincref(old_state->ivs_greedy_drv);
	new_state->ivs_greedy_cnt = old_state->ivs_greedy_cnt;
	/*   d  s   *
	 * ABCDEFG  *
	 * AB       */
	memcpy(&new_state->ivs_handv[0],
		   &old_state->ivs_handv[0],
	       dst_handler_index * sizeof(struct isr_vector_handler));
	/*   d  s   *
	 * ABCDEFG  *
	 * ABF      */
	memcpy(&new_state->ivs_handv[dst_handler_index],
	       &old_state->ivs_handv[src_handler_index],
	       sizeof(struct isr_vector_handler));
	/*   d  s   *
	 * ABCDEFG  *
	 * ABFCDE   */
	memcpy(&new_state->ivs_handv[dst_handler_index + 1],
	       &old_state->ivs_handv[dst_handler_index],
	       (src_handler_index - dst_handler_index) * sizeof(struct isr_vector_handler));
	/*   d  s   *
	 * ABCDEFG  *
	 * ABFCDEG  */
	memcpy(&new_state->ivs_handv[src_handler_index + 1],
	       &old_state->ivs_handv[src_handler_index + 1],
	       (new_state->ivs_handc - src_handler_index) * sizeof(struct isr_vector_handler));
	/* Update reference counts to backing drivers. */
	for (i = 0; i < new_state->ivs_handc; ++i) {
		incref(new_state->ivs_handv[i].ivh_drv);
	}
	new_state->ivs_unhandled = ATOMIC_READ(old_state->ivs_unhandled);
	if (isr_vectors[i].cmpxch_inherit_new(old_state, new_state)) {
		printk(KERN_INFO "[isr] Reorder handlers for vector %#Ix (%Iu -> %Iu)\n",
		       (size_t)ISR_INDEX_TO_VECTOR(vector_index),
		       src_handler_index, dst_handler_index);
		return true;
	}
	destroy(new_state); /* Not inherited on failure... */
	return false;
}


LOCAL NOBLOCK bool
NOTHROW(KCALL isr_vector_trigger_impl)(size_t index) {
	size_t i;
	struct isr_vector_state *self;
	self = isr_vectors[index].get();
	assert(self);
	for (i = 0; i < self->ivs_handc; ++i) {
		if (!(*self->ivs_handv[i].ivh_fun)(self->ivs_handv[i].ivh_arg)) {
			ATOMIC_FETCHINC(self->ivs_handv[i].ivh_mis);
			continue;
		}
		/* Handler successfully invoked. */
		ATOMIC_FETCHINC(self->ivs_handv[i].ivh_hit);
		if unlikely_untraced(i != 0) { /* Don't trace, since this should be kept as unlikely! */
			/* Check if our hit/miss ratio is now greater than that of i-1
			 * If so, try to allocate a new vector state with a more optimized handler order. */
			if (compare_handler_hitmiss_gr(&self->ivs_handv[i],
			                               &self->ivs_handv[i - 1])) {
				size_t dest = i - 1;
				/* Check if we should shift by more than 1 slot. */
				while (dest != 0 &&
				       compare_handler_hitmiss_gr(&self->ivs_handv[i],
				                                  &self->ivs_handv[dest - 1]))
					--dest;
				isr_try_reorder_handlers(index, self, i, dest);
				decref_likely(self);
				return true;
			}
		}
		decref_unlikely(self);
		return true;
	}
	/* Fallback: Invoke the greedy handler (if defined). */
	if (self->ivs_greedy_drv) {
		(*self->ivs_greedy_fun)(self->ivs_greedy_arg);
		ATOMIC_FETCHINC(self->ivs_greedy_cnt);
		decref_unlikely(self);
		return true;
	}
	ATOMIC_FETCHINC(self->ivs_unhandled);
	decref_unlikely(self);
	return false;
}

/* Trigger the given ISR vector, returning true if any handler returned
 * true, or if a greedy handler was defined. Otherwise, return `false'. */
PUBLIC NOBLOCK bool
NOTHROW(KCALL isr_vector_trigger)(isr_vector_t vector) {
	if unlikely(!ISR_VECTOR_IS_VALID(vector))
		return false;
	return isr_vector_trigger_impl(ISR_VECTOR_TO_INDEX(vector));
}

PRIVATE ATTR_NOINLINE ATTR_COLD void
NOTHROW(KCALL isr_unhandled)(size_t index) {
	printk(KERN_ERR "[isr] Unhandled interrupt %#Ix\n",
	       (size_t)ISR_INDEX_TO_VECTOR(index));
}

FORCELOCAL NOBLOCK void
NOTHROW(KCALL isr_handler)(size_t index) {
	if unlikely(!isr_vector_trigger_impl(index)) {
		isr_unhandled(index);
	}
}


#define DEFINE_ISR_HANDLER(index, vec)                         \
	INTERN NOBLOCK void NOTHROW(KCALL kernel_isr##vec)(void) { \
		isr_handler(ISR_VECTOR_TO_INDEX(0x##vec));             \
	}
ISR_GENERIC_VECTOR_ENUM(DEFINE_ISR_HANDLER)
ISR_SPECIFIC_VECTOR_ENUM(DEFINE_ISR_HANDLER)
#undef DEFINE_ISR_HANDLER



DECL_END

#endif /* !GUARD_KERNEL_SRC_DEV_INTERRUPT_C */
