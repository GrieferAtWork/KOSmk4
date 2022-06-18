/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_SRC_DEV_INTERRUPT_C
#define GUARD_KERNEL_SRC_DEV_INTERRUPT_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/except.h>
#include <kernel/handle.h>
#include <kernel/heap.h>
#include <kernel/isr.h>
#include <kernel/mman/cache.h>
#include <kernel/mman/driver.h>
#include <kernel/printk.h>
#include <kernel/types.h>
#include <sched/task.h>

#include <hybrid/atomic.h>

#include <kos/aref.h>

#include <assert.h>
#include <inttypes.h>
#include <stddef.h>
#include <string.h>

DECL_BEGIN

static_assert(!ISR_VECTOR_IS_VALID(ISR_VECTOR_INVALID));

#ifndef __INTELLISENSE__
#define ASSERT_INDICES(idx) \
	static_assert(ISR_VECTOR_TO_INDEX(ISR_INDEX_TO_VECTOR(0x##idx)) == 0x##idx);
#define ASSERT_INDICES_SPECIFIC(idx)                                                              \
	static_assert(ISR_VECTOR_TO_INDEX(ISR_INDEX_TO_VECTOR(0x##idx + ISR_GENERIC_VECTOR_COUNT)) == \
	              0x##idx + ISR_GENERIC_VECTOR_COUNT);
ISR_GENERIC_VECTOR_ENUM(ASSERT_INDICES);
ISR_SPECIFIC_VECTOR_ENUM(ASSERT_INDICES_SPECIFIC);
#undef ASSERT_INDICES_SPECIFIC
#undef ASSERT_INDICES
#endif /* !__INTELLISENSE__ */

#define ISR_COUNT  (ISR_GENERIC_VECTOR_COUNT + ISR_SPECIFIC_VECTOR_COUNT)


struct hisr {
	union {
		isr_function_t        hi_func;        /* [1..1][const] Object-level ISR handler */
		isr_greedy_function_t hi_greedy_func; /* [1..1][const] Object-level ISR handler (greedy) */
	};
	WEAK void     *hi_obj;   /* [0..1][MAYBE(DESTROYED)][lock(CLEAR_ONCE)] Pointed-to object (weakly referenced) */
	uintptr_half_t hi_typ;   /* [const] Handle object type for `hi_obj' */
#ifndef CONFIG_NO_SMP
	uintptr_half_t hi_pad;   /* ... */
	WEAK uintptr_t hi_inuse; /* Cross-CPU is-in-use tracking for `hi_obj' */
#endif /* !CONFIG_NO_SMP */
};

/* Try to acquire a reference to the pointed-to object, or return
 * NULL if  the pointed-to  object  had already  been  destroyed. */
LOCAL NOBLOCK NOPREEMPT WUNUSED NONNULL((1)) REF void *KCALL
NOTHROW(KCALL hisr_getref_nopr)(struct hisr *__restrict self) {
	REF void *obj;
	assert(!PREEMPTION_ENABLED());
	/* Try to acquire a reference to the handle object. */
#ifndef CONFIG_NO_SMP
	ATOMIC_INC(self->hi_inuse);
#endif /* !CONFIG_NO_SMP */
	COMPILER_READ_BARRIER();
	obj = self->hi_obj;
	COMPILER_READ_BARRIER();
	/* Try to acquire a reference */
	if (likely(obj) && unlikely(!(*handle_type_db.h_tryincref[self->hi_typ])(obj)))
		obj = NULL;
#ifndef CONFIG_NO_SMP
	ATOMIC_DEC(self->hi_inuse);
#endif /* !CONFIG_NO_SMP */
	return obj;
}

LOCAL NOBLOCK WUNUSED NONNULL((1)) void KCALL
NOTHROW(KCALL hisr_clear)(struct hisr *__restrict self) {
	/* Clear the `hi_obj' pointer of `self' */
#ifdef CONFIG_NO_SMP
	preemption_flag_t was;
	preemption_pushoff(&was);
#endif /* CONFIG_NO_SMP */
	ATOMIC_STORE(self->hi_obj, NULL);
#ifndef CONFIG_NO_SMP
	while (ATOMIC_READ(self->hi_inuse))
		task_tryyield_or_pause();
#else /* !CONFIG_NO_SMP */
	preemption_pop(&was);
#endif /* CONFIG_NO_SMP */
}



INTERN NOBLOCK bool NOTHROW(FCALL hisr_wrapper)(void *arg);
#if 1
#define HISR_GREEDY_WRAPPER_IS_ALIAS 1
INTERN NOBLOCK void NOTHROW(FCALL hisr_greedy_wrapper)(void *arg) ASMNAME("hisr_wrapper");
#else
PRIVATE NOBLOCK void NOTHROW(FCALL hisr_greedy_wrapper)(void *arg);
#endif

#ifdef HISR_GREEDY_WRAPPER_IS_ALIAS
#define hisr_iswrapper(f) ((void *)(f) == (void *)&hisr_wrapper)
#else /* HISR_GREEDY_WRAPPER_IS_ALIAS */
#define hisr_iswrapper(f) ((void *)(f) == (void *)&hisr_wrapper || (void *)(f) == (void *)&hisr_greedy_wrapper)
#endif /* !HISR_GREEDY_WRAPPER_IS_ALIAS */

/* Check if a given nullable driver/func/arg triple can be overwritten */
#define hisr_callback_mayoverride(d, func, arg, is_greedy) \
	(hisr_iswrapper(func) && (ATOMIC_READ(((struct hisr *)(arg))->hi_obj) == NULL))

/* Construct a new HISR descriptor. */
PRIVATE ATTR_RETNONNULL struct hisr *KCALL
hisr_new(void *func, void *ob_pointer, uintptr_half_t ob_type)
		THROWS(E_BADALLOC) {
	struct hisr *hi;
	hi = (struct hisr *)kmalloc(sizeof(struct hisr), GFP_LOCKED | GFP_PREFLT);
	hi->hi_func = (isr_function_t)func;
	hi->hi_obj  = ob_pointer;
	hi->hi_typ  = ob_type;
#ifndef CONFIG_NO_SMP
	hi->hi_inuse = 0;
#endif /* !CONFIG_NO_SMP */
	return hi;
}

/* Destroy a given HISR descriptor. */
LOCAL NOBLOCK void
NOTHROW(KCALL hisr_destroy)(struct hisr *__restrict self) {
	/* ... */
	kfree(self);
}

PUBLIC NOBLOCK void
NOTHROW(KCALL isr_vector_state_destroy)(struct isr_vector_state *__restrict self) {
	size_t i;
	for (i = 0; i < self->ivs_handc; ++i) {
		decref_unlikely(self->ivs_handv[i].ivh_drv);
	}
	if (self->ivs_greedy_drv)
		decref_unlikely(self->ivs_greedy_drv);
	heap_free(&kernel_locked_heap, self, self->ivs_heapsize, GFP_LOCKED);
}


PRIVATE ATTR_RETNONNULL REF struct isr_vector_state *
(KCALL isr_vector_state_alloc)(size_t handc) THROWS(E_BADALLOC) {
	REF struct isr_vector_state *result;
	heapptr_t ptr;
	ptr = heap_alloc(&kernel_locked_heap,
	                 offsetof(struct isr_vector_state, ivs_handv) +
	                 handc * sizeof(struct isr_vector_handler),
	                 GFP_LOCKED | GFP_PREFLT);
	result = (REF struct isr_vector_state *)heapptr_getptr(ptr);
	result->ivs_heapsize = heapptr_getsiz(ptr);
	result->ivs_refcnt   = 1;
	result->ivs_handc    = handc;
	return result;
}

PRIVATE NOBLOCK REF struct isr_vector_state *
NOTHROW(KCALL isr_vector_state_alloc_atomic_nx)(size_t handc) {
	REF struct isr_vector_state *result;
	heapptr_t ptr;
	ptr = heap_alloc_nx(&kernel_locked_heap,
	                    offsetof(struct isr_vector_state, ivs_handv) +
	                    handc * sizeof(struct isr_vector_handler),
	                    GFP_LOCKED | GFP_PREFLT | GFP_ATOMIC);
	if unlikely(!heapptr_getsiz(ptr))
		return NULL;
	result = (REF struct isr_vector_state *)heapptr_getptr(ptr);
	result->ivs_heapsize = heapptr_getsiz(ptr);
	result->ivs_refcnt   = 1;
	result->ivs_handc    = handc;
	return result;
}


PRIVATE struct isr_vector_state empty_vector_state = {
	.ivs_refcnt     = 1 + ISR_COUNT,
	.ivs_heapsize   = offsetof(struct isr_vector_state, ivs_handv),
	.ivs_greedy_fun = NULL,
	.ivs_greedy_arg = NULL,
	.ivs_greedy_drv = NULL,
	.ivs_greedy_cnt = 0,
	.ivs_unhandled  = 0,
	.ivs_handc      = 0,
	.ivs_handv      = { }
};

ARREF(isr_vector_state_arref, isr_vector_state);

/* The main ISR vector table. */
PRIVATE ATTR_SECTION(".data.hot.read_mostly.tail")
struct isr_vector_state_arref isr_vectors[ISR_COUNT] = {
#define ENUM_EMPTY_VECTOR_STATE(idx) ARREF_INIT(&empty_vector_state),
	ISR_GENERIC_VECTOR_ENUM(ENUM_EMPTY_VECTOR_STATE)
	ISR_SPECIFIC_VECTOR_ENUM(ENUM_EMPTY_VECTOR_STATE)
#undef ENUM_EMPTY_VECTOR_STATE
};

/* Remove no-op HISR callbacks from `self' */
PRIVATE ATTR_RETNONNULL WUNUSED NONNULL((1)) struct isr_vector_state *
NOTHROW(KCALL isr_vector_state_remove_noop_hisr)(struct isr_vector_state *__restrict self,
                                                 void *ignored_arg) {
	size_t i;
	/* Check if the old greedy handler is dead. */
	if (hisr_callback_mayoverride(self->ivs_greedy_drv,
	                              self->ivs_greedy_fun,
	                              self->ivs_greedy_arg,
	                              true) &&
	    self->ivs_greedy_arg != ignored_arg) {
		assert(self->ivs_greedy_drv == &drv_self);
		decref_nokill(&drv_self);
		self->ivs_greedy_fun = NULL;
		self->ivs_greedy_arg = NULL;
		self->ivs_greedy_drv = NULL;
		self->ivs_greedy_cnt = 0;
	}
	for (i = 0; i < self->ivs_handc;) {
		if likely(!hisr_callback_mayoverride(self->ivs_handv[i].ivh_drv,
		                                     self->ivs_handv[i].ivh_fun,
		                                     self->ivs_handv[i].ivh_arg,
		                                     false) ||
		          self->ivs_handv[i].ivh_arg == ignored_arg) {
			++i;
			continue;
		}
		/* Found a dead HISR handler that should get removed!
		 * NOTE: As far as the actual  destruction of the associated  callback,
		 *       that job falls to our caller, as this can only be done _after_
		 *       the new ISR vector has been installed (in order to ensure that
		 *       an installed vector is always in a consistent state) */
remove_dead_hisr_at_i:
		assert(self->ivs_handv[i].ivh_drv == &drv_self);
		/* The  caller also has a reference to this, and ontop of that, this is our own
		 * driver, so anyone calling into us also has to have some kind of reference to
		 * keep this driver from being unloaded! */
		decref_nokill(self->ivs_handv[i].ivh_drv);
		assert(self->ivs_handc);
		--self->ivs_handc;
		memmovedown(&self->ivs_handv[i],
		            &self->ivs_handv[i + 1],
		            (self->ivs_handc - i),
		            sizeof(struct isr_vector_handler));
		while (i < self->ivs_handc) {
			if likely(!hisr_callback_mayoverride(self->ivs_handv[i].ivh_drv,
			                                     self->ivs_handv[i].ivh_fun,
			                                     self->ivs_handv[i].ivh_arg,
			                                     false)) {
				++i;
				continue;
			}
			goto remove_dead_hisr_at_i;
		}
		/* Since some  handlers got  removed, try  to truncate  the
		 * ISR vector heap block to release unused trailing memory. */
		{
			heapptr_t shrunked_vector;
			shrunked_vector = heap_realloc_nx(&kernel_locked_heap,
			                                  self, self->ivs_heapsize,
			                                  offsetof(struct isr_vector_state, ivs_handv) +
			                                  self->ivs_handc * sizeof(struct isr_vector_handler),
			                                  GFP_LOCKED | GFP_PREFLT | GFP_ATOMIC,
			                                  GFP_LOCKED | GFP_PREFLT | GFP_ATOMIC);
			if likely(heapptr_getsiz(shrunked_vector)) {
				self = (struct isr_vector_state *)heapptr_getptr(shrunked_vector);
				self->ivs_heapsize = heapptr_getsiz(shrunked_vector);
			}
		}
		break;
	}
	return self;
}

#ifdef NDEBUG
#define isr_vector_state_cleanup_noop_hisr(old_state, new_state, ignored_arg) \
	isr_vector_state_cleanup_noop_hisr(old_state, new_state)
#endif /* NDEBUG */
PRIVATE NONNULL((1, 2)) void
NOTHROW(KCALL isr_vector_state_cleanup_noop_hisr)(struct isr_vector_state *__restrict old_state,
                                                  struct isr_vector_state *__restrict new_state
#ifndef NDEBUG
                                                  ,
                                                  void *ignored_arg
#endif /* !NDEBUG */
                                                  ) {
	/* Try to finalize the old greedy callback (in case we've overwritten it after
	 * a  prior call to `hisr_unregister_impl()' failed to replace the ISR vector) */
	if (hisr_iswrapper(old_state->ivs_greedy_fun) &&
	    (new_state->ivs_greedy_fun != old_state->ivs_greedy_fun ||
	     new_state->ivs_greedy_arg != old_state->ivs_greedy_arg)) {
		/* The greedy function has changed. */
		assert(old_state->ivs_greedy_drv == &drv_self);
#ifndef NDEBUG
		assert(old_state->ivs_greedy_arg != ignored_arg);
#endif /* !NDEBUG */
		hisr_destroy((struct hisr *)old_state->ivs_greedy_arg);
	}
	/* Check for, and finalize no-op HISR handlers that were removed. */
	if (new_state->ivs_handc <= old_state->ivs_handc) {
		/* At least 1 handler got removed. */
		size_t oi = 0, ni = 0;
		for (;;) {
			if (oi >= old_state->ivs_handc) {
				assertf(ni == new_state->ivs_handc,
				        "Unaccounted callbacks in new_state");
				break;
			}
			if (ni >= new_state->ivs_handc) {
				/* All remaining handlers from `old_state' were removed. */
				do {
					if (hisr_callback_mayoverride(old_state->ivs_handv[oi].ivh_drv,
					                              old_state->ivs_handv[oi].ivh_fun,
					                              old_state->ivs_handv[oi].ivh_arg,
					                              false)) {
						assert(old_state->ivs_handv[oi].ivh_drv == &drv_self);
#ifndef NDEBUG
						assert(old_state->ivs_handv[oi].ivh_arg != ignored_arg);
#endif /* !NDEBUG */
						hisr_destroy((struct hisr *)old_state->ivs_handv[oi].ivh_arg);
					}
				} while (++oi < old_state->ivs_handc);
				break;
			}
			/* Check if a handler got removed in this position. */
			if (old_state->ivs_handv[oi].ivh_drv == new_state->ivs_handv[ni].ivh_drv &&
			    old_state->ivs_handv[oi].ivh_fun == new_state->ivs_handv[ni].ivh_fun &&
			    old_state->ivs_handv[oi].ivh_arg == new_state->ivs_handv[ni].ivh_arg) {
				++oi;
				++ni;
				continue;
			}
			/* The handler from `old_state->ivs_handv[oi]' was removed!
			 * The  only reason this might happen is if that handler is
			 * a dead HISR callback, in which case we must destroy it. */
			assert(old_state->ivs_handv[oi].ivh_drv == &drv_self);
			assert(hisr_callback_mayoverride(old_state->ivs_handv[oi].ivh_drv,
			                                 old_state->ivs_handv[oi].ivh_fun,
			                                 old_state->ivs_handv[oi].ivh_arg,
			                                 false));
#ifndef NDEBUG
			assert(old_state->ivs_handv[oi].ivh_arg != ignored_arg);
#endif /* !NDEBUG */
			hisr_destroy((struct hisr *)old_state->ivs_greedy_arg);
			++oi;
		}
	}
}

LOCAL bool KCALL
isr_try_register_at_impl(/*inherit(on_success)*/ REF struct driver *__restrict func_driver,
                         struct isr_vector_state *__restrict old_state, size_t index,
                         void *func, void *arg, bool is_greedy)
		THROWS(E_BADALLOC) {
	size_t i;
	struct isr_vector_state *new_state;
	void *ignored_hisr_arg = hisr_iswrapper(func) ? arg : NULL;
	new_state = isr_vector_state_alloc(is_greedy ? old_state->ivs_handc
	                                             : old_state->ivs_handc + 1);
	if (is_greedy) {
		assert(!old_state->ivs_greedy_drv ||
		       hisr_callback_mayoverride(old_state->ivs_greedy_drv,
		                                 old_state->ivs_greedy_fun,
		                                 old_state->ivs_greedy_arg,
		                                 true));
		new_state->ivs_greedy_fun = (isr_greedy_function_t)func;
		new_state->ivs_greedy_arg = arg;
		new_state->ivs_greedy_drv = (REF struct driver *)incref(func_driver);
		new_state->ivs_greedy_cnt = 0;
		memcpy(new_state->ivs_handv,
		       old_state->ivs_handv,
		       old_state->ivs_handc,
		       sizeof(struct isr_vector_handler));
		for (i = 0; i < old_state->ivs_handc; ++i) {
			incref(new_state->ivs_handv[i].ivh_drv);
		}
	} else {
		new_state->ivs_greedy_fun = old_state->ivs_greedy_fun;
		new_state->ivs_greedy_arg = old_state->ivs_greedy_arg;
		new_state->ivs_greedy_drv = (REF struct driver *)xincref(old_state->ivs_greedy_drv);
		new_state->ivs_greedy_cnt = old_state->ivs_greedy_cnt;
		/* Load the new function as the primary handler, so
		 * we can more easily determine its hit/miss ratio. */
		new_state->ivs_handv[0].ivh_fun = (isr_function_t)func;
		new_state->ivs_handv[0].ivh_arg = arg;
		new_state->ivs_handv[0].ivh_drv = (REF struct driver *)incref(func_driver);
		memcpy(new_state->ivs_handv + 1,
		       old_state->ivs_handv,
		       old_state->ivs_handc,
		       sizeof(struct isr_vector_handler));
		for (i = 1; i < new_state->ivs_handc; ++i)
			incref(new_state->ivs_handv[i].ivh_drv);
	}
	/* Remove all no-op HISR handlers. */
	new_state = isr_vector_state_remove_noop_hisr(new_state, ignored_hisr_arg);
	new_state->ivs_unhandled = ATOMIC_READ(old_state->ivs_unhandled);
	/* With the new state now fully initialized, try to install it (atomically). */
	if (arref_cmpxch(&isr_vectors[index], old_state, new_state)) {
		void *real_func = func, *real_arg = arg;
		if (hisr_iswrapper(func)) {
			struct hisr *hi;
			hi = (struct hisr *)arg;
			real_func = (void *)hi->hi_func;
			real_arg  = hi->hi_obj;
			assert(func_driver == &drv_self);
			decref_nokill(func_driver); /* Inherit on success. */
			func_driver = driver_fromaddr(real_func);
			if unlikely(!func_driver)
				func_driver = (REF struct driver *)incref(&drv_self); /* Shouldn't happen... */
		}
		printk(KERN_INFO "[isr] Register handler for vector %#" PRIxSIZ " (%p with %p in driver %q)\n",
		       (size_t)ISR_INDEX_TO_VECTOR(index),
		       real_func, real_arg, func_driver->d_name);
		decref_unlikely(func_driver); /* Inherit on success. */
		isr_vector_state_cleanup_noop_hisr(old_state, new_state, ignored_hisr_arg);
		decref_unlikely(new_state);
		return true;
	}
	/* Failed to install the new state (so we must destroy it now) */
	decref_likely(new_state);  /* Destroy the new state. */
	return false;
}

LOCAL isr_vector_t KCALL
isr_register_impl(void *func, void *arg, bool is_greedy)
		THROWS(E_BADALLOC, E_BADALLOC_INSUFFICIENT_INTERRUPT_VECTORS) {
	bool success;
	REF struct driver *func_driver;
	REF struct isr_vector_state *winner;
	size_t i, winner_index = 0;
	syscache_version_t cache_version = SYSCACHE_VERSION_INIT;
	func_driver = driver_fromaddr(func);
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
	winner = arref_get(&isr_vectors[winner_index]);
	if (winner->ivs_handc || winner->ivs_greedy_drv) {
		/* Search for the vector with the least amount of  handlers,
		 * preferring those without greedy handlers over those with. */
		for (i = 1; i < ISR_COUNT; ++i) {
			REF struct isr_vector_state *temp;
			temp = arref_get(&isr_vectors[i]);
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
	if unlikely(is_greedy && winner->ivs_greedy_drv &&
	            !hisr_callback_mayoverride(winner->ivs_greedy_drv,
	                                      winner->ivs_greedy_fun,
	                                      winner->ivs_greedy_arg,
	                                      true)) {
		/* Try to reclaim cache resources, which may free up a suitable interrupt vector slot. */
		if (syscache_clear_s(&cache_version))
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
	syscache_version_t cache_version = SYSCACHE_VERSION_INIT;
	/* Make sure that the given vector is valid. - If it  isn't,
	 * act like it's impossible to allocate further data for it. */
	if unlikely(!ISR_VECTOR_IS_VALID(vector))
		THROW(E_BADALLOC_INSUFFICIENT_INTERRUPT_VECTORS, vector);
	func_driver = driver_fromaddr(func);
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
	old_state = arref_get(&isr_vectors[index]);
	if (is_greedy && old_state->ivs_greedy_drv &&
	    !hisr_callback_mayoverride(old_state->ivs_greedy_drv,
	                               old_state->ivs_greedy_fun,
	                               old_state->ivs_greedy_arg,
	                               true)) {
		/* The old vector is already in use. */
		decref(old_state);
		/* Try to reclaim resources. */
		if (syscache_clear_s(&cache_version))
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
		THROWS(E_BADALLOC)
		ASMNAME("isr_unregister");

FUNDEF bool KCALL
isr_unregister_at_(isr_vector_t vector, void *func, void *arg)
		THROWS(E_BADALLOC)
		ASMNAME("isr_unregister_at");

FUNDEF bool KCALL
isr_unregister_any_(void *func)
		THROWS(E_BADALLOC)
		ASMNAME("isr_unregister_any");

FUNDEF bool KCALL
isr_unregister_any_at_(isr_vector_t vector, void *func)
		THROWS(E_BADALLOC)
		ASMNAME("isr_unregister_any_at");

PRIVATE NOBLOCK bool KCALL
isr_unregister_impl(size_t index, void *func, void *arg, bool ignore_arg)
		THROWS(E_BADALLOC) {
	bool success; size_t i;
	struct isr_vector_state *old_state;
	struct isr_vector_state *new_state;
	struct driver *declaring_driver;
	assert(index < ISR_COUNT);
again:
	old_state = arref_get(&isr_vectors[index]);
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
			       old_state->ivs_handc,
			       sizeof(struct isr_vector_handler));
			for (i = 0; i < new_state->ivs_handc; ++i) {
				incref(new_state->ivs_handv[i].ivh_drv);
			}
		}
		arg              = old_state->ivs_greedy_arg;
		declaring_driver = old_state->ivs_greedy_drv;
assign_new_state:
		new_state = isr_vector_state_remove_noop_hisr(new_state, NULL);
		new_state->ivs_unhandled = ATOMIC_READ(old_state->ivs_unhandled);
		success = arref_cmpxch(&isr_vectors[index], old_state, new_state);
		if unlikely(!success) {
			decref(old_state);
			decref(new_state); /* Not inherited on failure */
			goto again;
		}
		isr_vector_state_cleanup_noop_hisr(old_state, new_state, NULL);
		decref_unlikely(new_state);
		printk(KERN_INFO "[isr] Delete handler for vector %#" PRIxSIZ " (%p with %p in driver %q)\n",
		       (size_t)ISR_INDEX_TO_VECTOR(index),
		       func, arg, declaring_driver->d_name);
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
			new_state->ivs_greedy_drv = (REF struct driver *)xincref(old_state->ivs_greedy_drv);
			new_state->ivs_greedy_cnt = old_state->ivs_greedy_cnt;
			/* Copy handlers, but leave out the one at index=`i' */
			memcpy(&new_state->ivs_handv[0],
			       &old_state->ivs_handv[0],
			       i, sizeof(struct isr_vector_handler));
			memcpy(&new_state->ivs_handv[i],
			       &old_state->ivs_handv[i + 1],
			       new_state->ivs_handc - i,
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
 * appropriate  vector, or by  specifying the required vector.
 * WARNING: The caller is responsible to ensure that any given func+arg
 *          combination will only be registered once.
 * @return: ISR_VECTOR_INVALID: The given `func' maps to a driver that is currently being finalized.
 * @throws: E_SEGFAULT:         The given `func' doesn't map to the static segment of any known driver.
 * @throws: E_BADALLOC_INSUFFICIENT_INTERRUPT_VECTORS: The given, or all vectors are already in use,
 *                                                     or the  given  vector  cannot  be  allocated. */
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










INTERN NOBLOCK bool NOTHROW(FCALL hisr_wrapper)(void *arg) {
	bool result;
	struct hisr *me;
	REF void *obj;
	assert(!PREEMPTION_ENABLED());
	me = (struct hisr *)arg;
	/* Try to acquire a reference to the handle object. */
	obj = hisr_getref_nopr(me);
	if unlikely(!obj)
		return false;
	/* Invoke the actual handler. */
	result = (*me->hi_func)(obj);
	(*handle_type_db.h_decref[me->hi_typ])(obj);
	return result;
}

#ifndef HISR_GREEDY_WRAPPER_IS_ALIAS
INTERN NOBLOCK void NOTHROW(FCALL hisr_greedy_wrapper)(void *arg) {
	struct hisr *me;
	REF void *obj;
	assert(!PREEMPTION_ENABLED());
	me = (struct hisr *)arg;
	/* Try to acquire a reference to the handle object. */
	obj = hisr_getref_nopr(me);
	if unlikely(!obj)
		return;
	/* Invoke the actual handler. */
	(*me->hi_greedy_func)(obj);
	(*handle_type_db.h_decref[me->hi_typ])(obj);
}
#endif /* !HISR_GREEDY_WRAPPER_IS_ALIAS */


PUBLIC isr_vector_t KCALL
hisr_register(isr_function_t func,
              void *ob_pointer,
              uintptr_half_t ob_type)
		THROWS(E_BADALLOC) {
	isr_vector_t result;
	struct hisr *hi;
	hi = hisr_new((void *)func, ob_pointer, ob_type);
	TRY {
		result = isr_register(&hisr_wrapper, hi);
	} EXCEPT {
		hisr_destroy(hi);
		RETHROW();
	}
	assert(result != ISR_VECTOR_INVALID);
	return result;
}

PUBLIC isr_vector_t KCALL
hisr_register_at(isr_vector_t vector, isr_function_t func,
                 void *ob_pointer, uintptr_half_t ob_type)
		THROWS(E_BADALLOC) {
	isr_vector_t result;
	struct hisr *hi;
	hi = hisr_new((void *)func, ob_pointer, ob_type);
	TRY {
		result = isr_register_at(vector, &hisr_wrapper, hi);
	} EXCEPT {
		hisr_destroy(hi);
		RETHROW();
	}
	assert(result != ISR_VECTOR_INVALID);
	return result;
}

PUBLIC isr_vector_t KCALL
hisr_register_greedy(isr_greedy_function_t func,
                     void *ob_pointer,
                     uintptr_half_t ob_type)
		THROWS(E_BADALLOC, E_BADALLOC_INSUFFICIENT_INTERRUPT_VECTORS) {
	isr_vector_t result;
	struct hisr *hi;
	hi = hisr_new((void *)func, ob_pointer, ob_type);
	TRY {
		result = isr_register_greedy(&hisr_greedy_wrapper, hi);
	} EXCEPT {
		hisr_destroy(hi);
		RETHROW();
	}
	assert(result != ISR_VECTOR_INVALID);
	return result;
}

PUBLIC isr_vector_t KCALL
hisr_register_greedy_at(isr_vector_t vector, isr_greedy_function_t func,
                        void *ob_pointer, uintptr_half_t ob_type)
		THROWS(E_BADALLOC, E_BADALLOC_INSUFFICIENT_INTERRUPT_VECTORS) {
	isr_vector_t result;
	struct hisr *hi;
	hi = hisr_new((void *)func, ob_pointer, ob_type);
	TRY {
		result = isr_register_greedy_at(vector, &hisr_greedy_wrapper, hi);
	} EXCEPT {
		hisr_destroy(hi);
		RETHROW();
	}
	assert(result != ISR_VECTOR_INVALID);
	return result;
}

PRIVATE NOBLOCK bool
NOTHROW(KCALL hisr_unregister_impl)(size_t index, void *func,
                                    void *ob_pointer,
                                    uintptr_half_t ob_type) {
	struct isr_vector_state *old_state;
	struct isr_vector_state *new_state;
	size_t i;
	bool success;
	assert(index < ISR_COUNT);
again:
	old_state = arref_get(&isr_vectors[index]);
	if (old_state->ivs_greedy_fun == &hisr_greedy_wrapper) {
		struct hisr *hi;
		hi = (struct hisr *)old_state->ivs_greedy_arg;
		if (hi->hi_func == func && hi->hi_obj == ob_pointer && hi->hi_typ == ob_type) {
			/* Clear the HISR descriptor. */
			hisr_clear(hi);
			/* Delete the greedy handler of this ISR, thus marking
			 * the  greedy  handler  as  no  longer  being in-use. */
			if (old_state->ivs_handc == 0) {
				new_state = incref(&empty_vector_state);
			} else {
				/* _try_  to allocate a new ISR vector state (but don't block, or throw an
				 * exception if this cannot  be done). If we're  unable to delete the  ISR
				 * handler  that we had  registered for the given  function, then the fact
				 * that we've already called `hisr_clear()' above will already allow other
				 * pieces  of code to detect that the  associated callback is dead and can
				 * be overwritten/discarded as will.
				 * In other words: If we fail this allocation, there's going to be a temporary
				 *                 memory leak that'll get fixed  as soon as some other  piece
				 *                 of code ties to modify the ISR vector.
				 */
				new_state = isr_vector_state_alloc_atomic_nx(old_state->ivs_handc);
				if unlikely(!new_state)
					goto shortcut_success;
				new_state->ivs_greedy_fun = NULL;
				new_state->ivs_greedy_arg = NULL;
				new_state->ivs_greedy_drv = NULL;
				new_state->ivs_greedy_cnt = 0;
				memcpy(new_state->ivs_handv, old_state->ivs_handv,
				       old_state->ivs_handc,
				       sizeof(struct isr_vector_handler));
				for (i = 0; i < new_state->ivs_handc; ++i) {
					incref(new_state->ivs_handv[i].ivh_drv);
				}
			}
assign_new_state:
			new_state = isr_vector_state_remove_noop_hisr(new_state, NULL);
			new_state->ivs_unhandled = ATOMIC_READ(old_state->ivs_unhandled);
			success = arref_cmpxch(&isr_vectors[index], old_state, new_state);
			if unlikely(!success) {
				decref(old_state);
				decref(new_state); /* Not inherited on failure */
				goto again;
			}
			isr_vector_state_cleanup_noop_hisr(old_state, new_state, NULL);
			decref_unlikely(new_state);
shortcut_success:
			{
				REF struct driver *declaring_driver;
				declaring_driver = driver_fromaddr(func);
				if unlikely(!declaring_driver)
					declaring_driver = (REF struct driver *)incref(&drv_self);
				printk(KERN_INFO "[isr] Delete handler for vector %#" PRIxSIZ " (%p with %p in driver %q)\n",
				       (size_t)ISR_INDEX_TO_VECTOR(index),
				       func, ob_pointer, declaring_driver->d_name);
				decref_unlikely(declaring_driver);
			}
			decref(old_state);
			return true;
		}
	}

	/* Search the handler vector for the given func+arg. */
	for (i = 0; i < old_state->ivs_handc; ++i) {
		struct hisr *hi;
		if (old_state->ivs_handv[i].ivh_fun != &hisr_wrapper)
			continue;
		hi = (struct hisr *)old_state->ivs_handv[i].ivh_arg;
		if (hi->hi_func != func || hi->hi_obj != ob_pointer || hi->hi_typ != ob_type)
			continue;
		/* Found it! */
		hisr_clear(hi);
		if (old_state->ivs_handc == 1 && !old_state->ivs_greedy_drv) {
			new_state = incref(&empty_vector_state);
		} else {
			new_state = isr_vector_state_alloc_atomic_nx(old_state->ivs_handc - 1);
			if unlikely(!new_state)
				goto shortcut_success;
			new_state->ivs_greedy_fun = old_state->ivs_greedy_fun;
			new_state->ivs_greedy_arg = old_state->ivs_greedy_arg;
			new_state->ivs_greedy_drv = (REF struct driver *)xincref(old_state->ivs_greedy_drv);
			new_state->ivs_greedy_cnt = old_state->ivs_greedy_cnt;
			/* Copy handlers, but leave out the one at index=`i' */
			memcpy(&new_state->ivs_handv[0],
			       &old_state->ivs_handv[0],
			       i, sizeof(struct isr_vector_handler));
			memcpy(&new_state->ivs_handv[i],
			       &old_state->ivs_handv[i + 1],
			       new_state->ivs_handc - i,
			       sizeof(struct isr_vector_handler));
			for (i = 0; i < new_state->ivs_handc; ++i) {
				incref(new_state->ivs_handv[i].ivh_drv);
			}
		}
		goto assign_new_state;
	}

	/* Not found */
	decref_unlikely(old_state);
	return false;
}

FUNDEF NOBLOCK bool
NOTHROW(KCALL hisr_unregister_)(void *func, void *ob_pointer,
                                uintptr_half_t ob_type)
		ASMNAME("hisr_unregister");
PUBLIC NOBLOCK bool
NOTHROW(KCALL hisr_unregister_)(void *func, void *ob_pointer,
                                uintptr_half_t ob_type) {
	size_t i;
	for (i = 0; i < ISR_COUNT; ++i) {
		if (hisr_unregister_impl(i, func, ob_pointer, ob_type))
			return true;
	}
	return false;
}

FUNDEF NOBLOCK bool
NOTHROW(KCALL hisr_unregister_at_)(isr_vector_t vector, void *func,
                                   void *ob_pointer, uintptr_half_t ob_type)
		ASMNAME("hisr_unregister_at");
PUBLIC NOBLOCK bool
NOTHROW(KCALL hisr_unregister_at_)(isr_vector_t vector, void *func,
                                   void *ob_pointer, uintptr_half_t ob_type) {
	if unlikely(!ISR_VECTOR_IS_VALID(vector))
		return false;
	return hisr_unregister_impl(ISR_VECTOR_TO_INDEX(vector),
	                            func, ob_pointer, ob_type);
}




















/* Return the usage descriptor for the given ISR vector. */
PUBLIC NOBLOCK ATTR_RETNONNULL REF struct isr_vector_state *
NOTHROW(KCALL isr_usage_of)(isr_vector_t vector) {
	if unlikely(!ISR_VECTOR_IS_VALID(vector))
		return incref(&empty_vector_state);
	return arref_get(&isr_vectors[ISR_VECTOR_TO_INDEX(vector)]);
}

LOCAL NOBLOCK ATTR_CONST bool
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

LOCAL NOBLOCK ATTR_PURE bool
NOTHROW(KCALL compare_handler_hitmiss_gr)(struct isr_vector_handler const *__restrict a,
                                          struct isr_vector_handler const *__restrict b) {
	return compare_hitmiss_gr(a->ivh_hit, a->ivh_mis,
	                          b->ivh_hit, b->ivh_mis);
}


/* Try to  re-order  ISR  handlers such  that  `src_handler_index'  gets  moved
 * closer to the start of the handler vector, placing it at `dst_handler_index' */
PRIVATE NOBLOCK ATTR_NOINLINE bool
NOTHROW(KCALL isr_try_reorder_handlers)(size_t vector_index,
                                        struct isr_vector_state *__restrict old_state,
                                        size_t src_handler_index,
                                        size_t dst_handler_index) {
	heapptr_t ptr; size_t i;
	struct isr_vector_state *new_state;
	assert(dst_handler_index < src_handler_index);
	/* Try to allocate a new state. (Using NX + ATOMIC to make this async-safe) */
	ptr = heap_alloc_nx(&kernel_locked_heap,
	                    offsetof(struct isr_vector_state, ivs_handv) +
	                    old_state->ivs_handc * sizeof(struct isr_vector_handler),
	                    GFP_LOCKED | GFP_PREFLT | GFP_ATOMIC);
	if (!heapptr_getsiz(ptr))
		return false; /* Allocation failed. */
	new_state = (struct isr_vector_state *)heapptr_getptr(ptr);
	new_state->ivs_heapsize   = heapptr_getsiz(ptr);
	new_state->ivs_refcnt     = 1;
	new_state->ivs_handc      = old_state->ivs_handc;
	new_state->ivs_greedy_fun = old_state->ivs_greedy_fun;
	new_state->ivs_greedy_arg = old_state->ivs_greedy_arg;
	new_state->ivs_greedy_drv = (REF struct driver *)xincref(old_state->ivs_greedy_drv);
	new_state->ivs_greedy_cnt = old_state->ivs_greedy_cnt;
	/************
	 *   d  s   *
	 * ABCDEFG  *
	 * AB       *
	 ************/
	memcpy(&new_state->ivs_handv[0],
		   &old_state->ivs_handv[0],
	       dst_handler_index,
	       sizeof(struct isr_vector_handler));
	/************
	 *   d  s   *
	 * ABCDEFG  *
	 * ABF      *
	 ************/
	memcpy(&new_state->ivs_handv[dst_handler_index],
	       &old_state->ivs_handv[src_handler_index],
	       sizeof(struct isr_vector_handler));
	/************
	 *   d  s   *
	 * ABCDEFG  *
	 * ABFCDE   *
	 ************/
	memcpy(&new_state->ivs_handv[dst_handler_index + 1],
	       &old_state->ivs_handv[dst_handler_index],
	       src_handler_index - dst_handler_index,
	       sizeof(struct isr_vector_handler));
	/************
	 *   d  s   *
	 * ABCDEFG  *
	 * ABFCDEG  *
	 ************/
	memcpy(&new_state->ivs_handv[src_handler_index + 1],
	       &old_state->ivs_handv[src_handler_index + 1],
	       new_state->ivs_handc - src_handler_index,
	       sizeof(struct isr_vector_handler));
	/* Update reference counts to backing drivers. */
	for (i = 0; i < new_state->ivs_handc; ++i) {
		incref(new_state->ivs_handv[i].ivh_drv);
	}
	new_state = isr_vector_state_remove_noop_hisr(new_state, NULL);
	new_state->ivs_unhandled = ATOMIC_READ(old_state->ivs_unhandled);
	if (arref_cmpxch(&isr_vectors[i], old_state, new_state)) {
		isr_vector_state_cleanup_noop_hisr(old_state, new_state, NULL);
		destroy(new_state);
		printk(KERN_INFO "[isr] Reorder handlers for vector "
		                 "%#" PRIxSIZ " (%" PRIuSIZ " -> %" PRIuSIZ ")\n",
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
	REF struct isr_vector_state *self;
	self = arref_get(&isr_vectors[index]);
	assert(self);
	for (i = 0; i < self->ivs_handc; ++i) {
		if (!(*self->ivs_handv[i].ivh_fun)(self->ivs_handv[i].ivh_arg)) {
			ATOMIC_INC(self->ivs_handv[i].ivh_mis);
			continue;
		}
		/* Handler successfully invoked. */
		ATOMIC_INC(self->ivs_handv[i].ivh_hit);
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
		ATOMIC_INC(self->ivs_greedy_cnt);
		decref_unlikely(self);
		return true;
	}
	ATOMIC_INC(self->ivs_unhandled);
	decref_unlikely(self);
	return false;
}

/* Trigger the given ISR vector, returning true if any handler returned
 * true, or if a greedy handler was defined. Otherwise, return `false'. */
PUBLIC NOBLOCK ATTR_NOINLINE bool
NOTHROW(KCALL isr_vector_trigger)(isr_vector_t vector) {
	assert(!PREEMPTION_ENABLED());
	if unlikely_untraced(!ISR_VECTOR_IS_VALID(vector))
		return false;
	return isr_vector_trigger_impl(ISR_VECTOR_TO_INDEX(vector));
}

PRIVATE ATTR_NOINLINE ATTR_COLD void
NOTHROW(KCALL isr_unhandled)(size_t index) {
	printk(KERN_ERR "[isr] Unhandled interrupt %#" PRIxSIZ "\n",
	       (size_t)ISR_INDEX_TO_VECTOR(index));
}

FORCELOCAL NOBLOCK ATTR_ARTIFICIAL void
NOTHROW(KCALL isr_handler)(size_t index) {
	if unlikely_untraced(!isr_vector_trigger_impl(index)) {
		isr_unhandled(index);
	}
}


#define DEFINE_ISR_HANDLER(index)                                                        \
	INTERN NOBLOCK ATTR_WEAK ATTR_SECTION(".text.kernel.kernel_isr_generic_" #index "h") \
	void NOTHROW(KCALL kernel_isr_generic_##index##h)(void) {                            \
		isr_handler(0x##index);                                                          \
	}
ISR_GENERIC_VECTOR_ENUM(DEFINE_ISR_HANDLER)
#undef DEFINE_ISR_HANDLER
#define DEFINE_ISR_HANDLER(index)                                                         \
	INTERN NOBLOCK ATTR_WEAK ATTR_SECTION(".text.kernel.kernel_isr_specific_" #index "h") \
	void NOTHROW(KCALL kernel_isr_specific_##index##h)(void) {                            \
		isr_handler(ISR_GENERIC_VECTOR_COUNT + 0x##index);                                \
	}
ISR_SPECIFIC_VECTOR_ENUM(DEFINE_ISR_HANDLER)
#undef DEFINE_ISR_HANDLER



DECL_END

#endif /* !GUARD_KERNEL_SRC_DEV_INTERRUPT_C */
