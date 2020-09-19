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
#ifndef GUARD_KERNEL_CORE_FS_DRIVER_C
#define GUARD_KERNEL_CORE_FS_DRIVER_C 1
#define _GNU_SOURCE 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <debugger/config.h>
#include <debugger/debugger.h>
#include <fs/node.h>
#include <fs/vfs.h>
#include <kernel/debugtrap.h>
#include <kernel/driver-param.h>
#include <kernel/driver.h>
#include <kernel/except.h>
#include <kernel/heap.h>
#include <kernel/malloc.h>
#include <kernel/module.h>
#include <kernel/panic.h>
#include <kernel/printk.h>
#include <kernel/types.h>
#include <kernel/vboxgdb.h>
#include <kernel/vm/usermod.h> /* CONFIG_HAVE_USERMOD */
#include <misc/atomic-ref.h>
#include <sched/task.h>

#include <hybrid/align.h>
#include <hybrid/atomic.h>
#include <hybrid/overflow.h>
#include <hybrid/sequence/atree.h>
#include <hybrid/sequence/list.h>
#include <hybrid/sync/atomic-rwlock.h>

#include <kos/debugtrap.h>
#include <kos/except/reason/noexec.h>
#include <kos/exec/elf-rel.h> /* ELF_ARCH_*_R_* */
#include <kos/exec/elf.h>     /* ELF_ARCH_USESRELA */

#include <assert.h>
#include <ctype.h>
#include <elf.h>
#include <format-printer.h>
#include <inttypes.h>
#include <malloca.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>

#include <libcmdline/decode.h>
#include <libcmdline/encode.h>
#include <libunwind/eh_frame.h>
#include <libzlib/error.h>
#include <libzlib/inflate.h>

DECL_BEGIN

/* FDE Cache API */
struct driver_fde_cache_node {
	struct {
		struct driver_fde_cache_node *a_min;  /* Min-node */
		struct driver_fde_cache_node *a_max;  /* Max-node */
	}                                 cn_node;
	size_t                            cn_heapsz; /* [const] Allocated heap size */
	unwind_fde_t                      cn_fde;    /* [const] Cached FDE */
};

DECL_END

#define ATREE(x)          driver_fde_cachetree_##x
#define ATREE_CALL        KCALL
#define ATREE_NOTHROW     NOTHROW
#define ATREE_NODE_MIN(x) ((uintptr_t)(x)->cn_fde.f_pcstart)
#define ATREE_NODE_MAX(x) ((uintptr_t)(x)->cn_fde.f_pcend - 1)
#define Tkey              uintptr_t
#define T                 struct driver_fde_cache_node
#define N_NODEPATH        cn_node
#include <hybrid/sequence/atree-abi.h>

DECL_BEGIN

LOCAL NOBLOCK size_t
NOTHROW(KCALL driver_fde_free_tree)(struct driver_fde_cache_node *__restrict self) {
	size_t result = 0;
	struct driver_fde_cache_node *mi, *ma;
again:
	mi = self->cn_node.a_min;
	ma = self->cn_node.a_max;
	result += self->cn_heapsz;
	heap_free_untraced(&kernel_locked_heap,
	                   self,
	                   self->cn_heapsz,
	                   GFP_LOCKED);
	if (mi) {
		if (ma)
			result += driver_fde_free_tree(ma);
		self = mi;
		goto again;
	}
	if (ma) {
		self = ma;
		goto again;
	}
	return result;
}


/* Lookup the FDE descriptor for a given `absolute_pc', whilst trying to
 * make use of the FDE cache of `self'.
 * @return: * : One of `UNWIND_*' from <libunwind/api.h> */
PUBLIC NOBLOCK NONNULL((1)) unsigned int
NOTHROW(KCALL driver_fde_find)(struct driver *__restrict self, void *absolute_pc,
                               unwind_fde_t *__restrict result) {
	unsigned int error;
	struct driver_fde_cache_node *node;
	struct heapptr nodeptr;
	/* NOTE: try-lock, the cache, since we need to remain NOBLOCK */
	if (sync_tryread(&self->d_eh_frame_cache_lock)) {
		/* Search the cache for an existing entry */
		node = driver_fde_cachetree_locate_at(self->d_eh_frame_cache,
		                                      (uintptr_t)absolute_pc,
		                                      self->d_eh_frame_cache_semi0,
		                                      self->d_eh_frame_cache_leve0);
		if (node) {
			/* Found an existing cache entry! */
			memcpy(result, &node->cn_fde, sizeof(unwind_fde_t));
			sync_endread(&self->d_eh_frame_cache_lock);
			return UNWIND_SUCCESS;
		}
		sync_endread(&self->d_eh_frame_cache_lock);
	}
	/* Scan the .eh_frame section of the driver. */
	error = unwind_fde_scan((byte_t *)self->d_eh_frame_start,
	                        (byte_t *)self->d_eh_frame_end,
	                        absolute_pc,
	                        result,
	                        sizeof(void *));
	if unlikely(error != UNWIND_SUCCESS)
		return error;
	/* Don't try to cache the results if we've been poisoned.
	 * If the problem is related to a heap violation, then we can no
	 * longer trust that heap memory hasn't been corrupted beyond
	 * repair! */
	if (kernel_poisoned())
		goto done;
	assert(absolute_pc >= result->f_pcstart);
	assert(absolute_pc < result->f_pcend);

	/* Try to cache the FDE descriptor.
	 * Emphasis on the _try_. - Only do an atomic+NX allocation here, so
	 * there is no chance of an exception, nor any chance of blocking.
	 * Also: PREFAULT is required since we may be getting called from within
	 *       the builtin debugger, in which case we have to make sure that
	 *       any memory allocated will not cause a #PF (since lazy initialization
	 *       would be disabled in this case) */
	nodeptr = heap_alloc_untraced_nx(&kernel_locked_heap,
	                                 sizeof(struct driver_fde_cache_node),
	                                 GFP_ATOMIC | GFP_LOCKED | GFP_PREFLT);
	if (nodeptr.hp_siz != 0) {
		node            = (struct driver_fde_cache_node *)nodeptr.hp_ptr;
		node->cn_heapsz = nodeptr.hp_siz;
		memcpy(&node->cn_fde, result, sizeof(unwind_fde_t));
		/* NOTE: try-lock, the cache, since we need to remain NOBLOCK */
		if (sync_trywrite(&self->d_eh_frame_cache_lock)) {
			/* Check for race condition: Has another thread created the  */
			if unlikely(driver_fde_cachetree_rlocate_at(self->d_eh_frame_cache,
			                                            (uintptr_t)node->cn_fde.f_pcstart,
			                                            (uintptr_t)node->cn_fde.f_pcend - 1,
			                                            self->d_eh_frame_cache_semi0,
			                                            self->d_eh_frame_cache_leve0) != NULL) {
				sync_endwrite(&self->d_eh_frame_cache_lock);
			} else {
				/* Cache the FDE descriptor. */
				driver_fde_cachetree_insert_at(&self->d_eh_frame_cache,
				                               node,
				                               self->d_eh_frame_cache_semi0,
				                               self->d_eh_frame_cache_leve0);
				sync_endwrite(&self->d_eh_frame_cache_lock);
				return UNWIND_SUCCESS;
			}
		}
		/* Failed to lock cache, or node already cached... */
		heap_free_untraced(&kernel_locked_heap,
		                   nodeptr.hp_ptr,
		                   nodeptr.hp_siz,
		                   GFP_LOCKED);
	}
done:
	return UNWIND_SUCCESS;
}

/* Try to clear the FDE cache of the given, or of all loaded drivers.
 * NOTE: Drivers who's caches cannot be locked are skipped.
 * @return: * : The total number of bytes of heap-memory released. */
PUBLIC NOBLOCK NONNULL((1)) size_t
NOTHROW(KCALL driver_clear_fde_cache)(struct driver *__restrict self) {
	size_t result = 0;
	struct driver_fde_cache_node *tree;
	if (!sync_trywrite(&self->d_eh_frame_cache_lock))
		goto done;
	tree = self->d_eh_frame_cache;
	self->d_eh_frame_cache = NULL;
	sync_endwrite(&self->d_eh_frame_cache_lock);
	if (tree)
		result = driver_fde_free_tree(tree);
done:
	return result;
}



/* NOTE: This function is normally part of libunwind, but in kernel-space
 *       is implemented here so-as to allow for per-driver caching of FDE
 *       descriptors. */

/* Lookup FDE information associated with a given program counter position.
 * Using integration with KOS's DL extension APIs, this function automatically
 * accesses the `.eh_frame' sections of the module associated with the given
 * address, as well as keep track of a lazily allocated address-tree of FDE
 * caches for quick (O(1)) repeated access to an FDE located within a known
 * function. */
INTERN NOBLOCK unsigned int
NOTHROW_NCX(KCALL libuw_unwind_fde_find)(void *absolute_pc,
                                         unwind_fde_t *__restrict result) {
	unsigned int error;
	REF struct driver *d;
	/* Figure out which driver is mapped at the given `absolute_pc' */
	d = driver_at_address(absolute_pc);
	if unlikely(!d)
		return UNWIND_NO_FRAME;
	/* Lookup the FDE descriptor within the driver */
	error = driver_fde_find(d,
	                        absolute_pc,
	                        result);
	decref_unlikely(d);
	return error;
}
DEFINE_PUBLIC_ALIAS(unwind_fde_find, libuw_unwind_fde_find);





/* Callbacks invoked when a new driver is loaded. */
PUBLIC CALLBACK_LIST(void KCALL(struct driver *))
driver_loaded_callbacks = CALLBACK_LIST_INIT;

/* Callbacks invoked when a driver is finalized. */
PUBLIC CALLBACK_LIST(void KCALL(struct driver *))
driver_finalized_callbacks = CALLBACK_LIST_INIT;

/* Callbacks invoked just before a driver is unloaded. */
PUBLIC CALLBACK_LIST(NOBLOCK void /*NOEXCEPT*/ KCALL(struct driver *))
driver_unloaded_callbacks = CALLBACK_LIST_INIT;


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
	state = self->get();
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
	success = self->cmpxch_inherit_new(state,
	                                   new_state);
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
	state = self->get();
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
		success = self->cmpxch_inherit_new(state,
		                                   new_state);
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
DEFINE_INTERN_ALIAS(empty_driver_state,callback_list_empty);
PUBLIC struct callback_list_struct callback_list_empty = {
	/* .cl_refcnt  = */ 2, /* +1: empty_driver_state, +1: current_driver_state */
	/* .cl_count   = */ 0
};



/* The current state of loaded drivers.
 * This needs to be implemented as an atomic_ref pointer, so-as to allow for NOBLOCK+NOEXCEPT
 * enumeration of loaded drivers for the purpose of both discovering, as well as locking of
 * the driver associated with some given static data pointer. */
INTDEF atomic_ref<struct driver_state> current_driver_state ASMNAME("current_driver_state");
INTERN atomic_ref<struct driver_state> current_driver_state = ATOMIC_REF_INIT(&empty_driver_state);
#ifdef CONFIG_VBOXGDB
DEFINE_PUBLIC_ALIAS(_vboxgdb_kos_driver_state, current_driver_state);
#endif /* CONFIG_VBOXGDB */

PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(KCALL driver_state_destroy)(struct driver_state *__restrict self) {
	size_t i;
	for (i = 0; i < self->ds_count; ++i)
		weakdecref_unlikely(self->ds_drivers[i]);
	kfree(self);
}

/* Return a snapshot for the current state of loaded drivers. */
PUBLIC NOBLOCK ATTR_RETNONNULL WUNUSED
REF struct driver_state *NOTHROW(KCALL driver_get_state)(void) {
	return current_driver_state.get();
}


/* Add a given driver `self' to the global driver state.
 * If another driver with the same name already exists, return
 * a reference to it. - Else, add `self' and return NULL. */
PRIVATE REF struct driver *KCALL
add_global_driver(struct driver *__restrict self) THROWS(E_BADALLOC) {
	size_t i, j;
	REF struct driver_state *old_state;
	REF struct driver_state *new_state;
again:
	old_state = current_driver_state.get();
	for (i = 0; i < old_state->ds_count; ++i) {
		struct driver *other_driver;
		other_driver = old_state->ds_drivers[i];
		assert(other_driver != self);
		if unlikely(!tryincref(other_driver))
			continue; /* Dead driver */
		if unlikely(strcmp(other_driver->d_name, self->d_name) != 0) {
			/* Driver's name differs from our's (-> Not the same driver) */
			decref_unlikely(other_driver);
			continue;
		}
		/* Oops... duplicate driver! */
		decref_unlikely(old_state);
		return other_driver;
	}
	FINALLY_DECREF(old_state);
	/* Create a copy of `old_state' that includes `self' */
	new_state = (REF struct driver_state *)kmalloc(offsetof(struct driver_state, ds_drivers) +
	                                               (old_state->ds_count + 1) *
	                                               sizeof(REF struct driver *),
	                                               GFP_LOCKED | GFP_PREFLT);
	new_state->ds_refcnt = 1; /* Inherited by `current_driver_state.cmpxch_inherit_new()' */
	new_state->ds_count  = old_state->ds_count + 1;
	/* Copy existing drivers. */
	for (i = j = 0; j < old_state->ds_count; ++j) {
		struct driver *other_driver;
		other_driver = old_state->ds_drivers[i];
		if (wasdestroyed(other_driver))
			continue; /* Skip dead drivers. */
		new_state->ds_drivers[i++] = weakincref(other_driver);
	}
	assert(i <= new_state->ds_count - 1);
	/* Add the new driver. */
	new_state->ds_drivers[i] = weakincref(self);
	new_state->ds_count      = i + 1;
	/* Try to set the new state via an atomic compare-exchange */
	if unlikely(!current_driver_state.cmpxch_inherit_new(old_state,
	                                                     new_state)) {
		destroy(new_state);
		goto again;
	}
	return NULL;
}

/* Try to remove a given driver `self' from the list of loaded drivers.
 * This function is called as part of `driver_destroy()', but is allowed
 * to fail, in which case anyone using the global driver list will simply
 * notice that one of the drivers has been destroyed, which is then handled
 * by simply skipping that driver. */
PRIVATE NOBLOCK bool
NOTHROW(KCALL try_remove_driver_from_global_set)(struct driver *__restrict self) {
	size_t i;
	REF struct driver_state *old_state;
	REF struct driver_state *new_state;
again:
	old_state = current_driver_state.get();
	for (i = 0; i < old_state->ds_count; ++i) {
		if (old_state->ds_drivers[i] == self) {
			/* Found it! */
			if (old_state->ds_count == 1) {
				new_state = incref(&empty_driver_state);
			} else {
				size_t j, dst;
				struct driver *other_driver;
				new_state = (REF struct driver_state *)kmalloc_nx(offsetof(struct driver_state, ds_drivers) +
				                                                  (old_state->ds_count - 1) *
				                                                  sizeof(REF struct driver *),
				                                                  GFP_LOCKED | GFP_PREFLT | GFP_ATOMIC);
				if unlikely(!new_state) {
					/* Cannot allocate the truncated driver state list...
					 * That means that the driver will remain as a ghost entry that
					 * users of the loaded-driver-list will simply have to skip over
					 * upon being encountered... */
					decref_unlikely(old_state);
					return false;
				}
				new_state->ds_refcnt = 1; /* Inherited by `current_driver_state.cmpxch_inherit_new()' */
				/* Copy existing drivers (but skip the driver at `i'). */
				dst = 0;
				for (j = 0; j < i; ++j) {
					other_driver = old_state->ds_drivers[j];
					if likely(!wasdestroyed(other_driver))
						new_state->ds_drivers[dst++] = weakincref(other_driver);
				}
				for (++j; j < old_state->ds_count; ++j) {
					other_driver = old_state->ds_drivers[j];
					if likely(!wasdestroyed(other_driver))
						new_state->ds_drivers[dst++] = weakincref(other_driver);
				}
				assert(dst <= old_state->ds_count - 1);
				new_state->ds_count = dst;
			}
			/* Try to set the new state via an atomic compare-exchange */
			if unlikely(!current_driver_state.cmpxch_inherit_new(old_state,
			                                                     new_state)) {
				decref_likely(new_state);
				goto again;
			}
			decref(old_state);
			return true;
		}
	}
	decref_unlikely(old_state);
	return false;
}



/* Try to clear the FDE cache of the given, or of all loaded drivers.
 * NOTE: Drivers who's caches cannot be locked are skipped.
 * @return: * : The total number of bytes of heap-memory released. */
DEFINE_SYSTEM_CACHE_CLEAR(driver_clear_fde_caches);

PUBLIC NOBLOCK size_t
NOTHROW(KCALL driver_clear_fde_caches)(void) {
	size_t i, result;
	REF struct driver_state *ds;
	result = driver_clear_fde_cache(&kernel_driver);
	ds = current_driver_state.get();
	for (i = 0; i < ds->ds_count; ++i) {
		REF struct driver *drv;
		drv = ds->ds_drivers[i];
		if (!tryincref(drv))
			continue;
		result += driver_clear_fde_cache(drv);
		decref_unlikely(drv);
	}
	decref_unlikely(ds);
	return result;
}


typedef NOBLOCK size_t /*NOTHROW*/ (KCALL *kernel_system_clearcache_t)(void);
INTDEF kernel_system_clearcache_t __kernel_system_clearcaches_start[];
INTDEF kernel_system_clearcache_t __kernel_system_clearcaches_end[];


#ifdef CONFIG_DEBUG_MALLOC
INTDEF ATTR_WEAK struct heap mall_heap;
#endif /* CONFIG_DEBUG_MALLOC */


/* Called as part of `system_clearcaches()': Trim standard kernel heaps.
 * @return: * : The total number of trimmed bytes. */
PUBLIC NOBLOCK size_t NOTHROW(KCALL system_trimheaps)(void) {
	size_t i, temp, result = 0;
	for (i = 0; i < __GFP_HEAPCOUNT; ++i) {
		temp = heap_trim(&kernel_heaps[i], 0);
		if (OVERFLOW_UADD(result, temp, &result))
			result = (size_t)-1;
	}
#ifdef CONFIG_DEBUG_MALLOC
	if (&mall_heap) {
		temp = heap_trim(&mall_heap, 0);
		if (OVERFLOW_UADD(result, temp, &result))
			result = (size_t)-1;
	}
#endif /* CONFIG_DEBUG_MALLOC */
	return result;
}


/* The id of the last invocation of `system_clearcaches()' for which memory got actually released. */
PRIVATE WEAK uintptr_t system_clearcaches_version = 0;
/* Counter for the number of threads currently inside of `system_clearcaches()' */
PRIVATE WEAK size_t system_clearcaches_isinside = 0;


PUBLIC NOBLOCK NONNULL((1)) size_t
NOTHROW(KCALL system_clearcaches_s)(uintptr_t *__restrict pversion) {
	enum { NUM_LASTCHANCE_ATTEMPTS = 32 };
	size_t inside_counter, result;
	uintptr_t old_version, new_version;
	/* Start out by trying to clear system caches ourself. */
	result = system_clearcaches();
	if (result)
		return result;
	/* Check if someone succeeded in clearing caches in the mean time. */
	new_version = ATOMIC_READ(system_clearcaches_version);
	old_version = *pversion;

	if (old_version != new_version &&
	    old_version < (uintptr_t)-NUM_LASTCHANCE_ATTEMPTS) {
		*pversion = new_version;
		return 1;
	}
	/* There is still the possibility that some other thread is still in
	 * the middle of a call to `system_clearcaches()'. - In this case,
	 * try to yield to them so they can finish, and keep on checking if
	 * the number of threads inside decreases. */
	inside_counter = ATOMIC_READ(system_clearcaches_isinside);
	if (inside_counter != 0) {
		unsigned int n;
		for (n = 0; n < 256; ++n) {
			unsigned int yield_error;
			yield_error = task_tryyield_or_pause();
			if (ATOMIC_READ(system_clearcaches_isinside) < inside_counter)
				break;
			if (yield_error != TASK_TRYYIELD_SUCCESS)
				break; /* Cannot yield... */
		}
	}
	/* Check for a version change one more time. */
	new_version = ATOMIC_READ(system_clearcaches_version);
	if (old_version != new_version &&
	    old_version < (uintptr_t)-NUM_LASTCHANCE_ATTEMPTS) {
		*pversion = new_version;
		return 1;
	}
	/* Even when nothing seems to change, try a couple more times in the vain
	 * hope that some other thread managed to get hold of a lock that was required
	 * to release the resource which our caller is after, and just didn't get around
	 * to incrementing the version counter, yet.
	 * However, only do this a limited number of times! */
	if (old_version != (uintptr_t)-1) {
		if (old_version < (uintptr_t)-NUM_LASTCHANCE_ATTEMPTS)
			*pversion = (uintptr_t)-NUM_LASTCHANCE_ATTEMPTS;
		else {
			*pversion = old_version + 1;
		}
		return 1;
	}
	if unlikely(new_version == (uintptr_t)-1) {
		/* We got here because the version number is too high.
		 * Fix this and indicate success since this only happens
		 * once every bagillion iterations, so this won't cause
		 * a soft-lock. */
		ATOMIC_CMPXCH(system_clearcaches_version, new_version, 0);
		*pversion = 0;
		return 1;
	}
	return 0;
}


/* Invoke cache clear callbacks for each and every globally reachable
 * component within the entire kernel.
 * This function is called when the kernel has run out of physical/virtual
 * memory, or some other kind of limited, and dynamically allocatable resource.
 * @return: * : At least some amount of some kind of resource was released.
 *              In this case the caller should re-attempt whatever lead them
 *              to try and clear caches to reclaim resource (usually memory)
 * @return: 0 : Nothing was released/freed.
 *              In this case, the caller should indicate failure due to
 *              lack of some necessary resource. */
PUBLIC NOBLOCK size_t
NOTHROW(KCALL system_clearcaches)(void) {
	size_t i, temp, result = 0;
	/* XXX: Execute this function on a separate stack to make invocations
	 *      in scenarios where little to no memory is available possible.
	 *      It is OK if this function cannot be executed in parallel with
	 *      itself, meaning that such a stack could easily be allocated
	 *      statically. */
	ATOMIC_INC(system_clearcaches_isinside);
	{
		REF struct driver_state *state;
		/* Invoke the `drv_clearcache()' function of every loaded driver. */
		state = current_driver_state.get();
		for (i = 0; i < state->ds_count; ++i) {
			kernel_system_clearcache_t func;
			REF struct driver *drv;
			drv = state->ds_drivers[i];
			if (!tryincref(drv))
				continue; /* Dead driver... */
			if (driver_symbol_ex(drv, "drv_clearcache", (void **)&func)) {
				temp = (*func)();
				if (OVERFLOW_UADD(result, temp, &result))
					result = (size_t)-1;
			}
			decref_unlikely(drv);
		}
		assert(!wasdestroyed(state));
		if (ATOMIC_DECFETCH(state->ds_refcnt) == 0) {
			temp = offsetof(struct driver_state, ds_drivers) +
			       (state->ds_count * sizeof(REF struct driver *));
			if (OVERFLOW_UADD(result, temp, &result))
				result = (size_t)-1;
			destroy(state);
		}
	}
	{
		kernel_system_clearcache_t *iter;
		/* Invoke kernel-internal clear-cache functions. */
		for (iter = __kernel_system_clearcaches_start;
		     iter < __kernel_system_clearcaches_end; ++iter) {
			temp = (**iter)();
			if (OVERFLOW_UADD(result, temp, &result))
				result = (size_t)-1;
		}
	}
	/* Lastly, trim kernel heaps within a threshold of 0 pages (thus forcing
	 * the heap sub-system to release as much memory as it possibly can) */
	temp = system_trimheaps();
	if (OVERFLOW_UADD(result, temp, &result))
		result = (size_t)-1;
	if (result != 0) /* Managed to do something: Increment the cache-version */
		ATOMIC_INC(system_clearcaches_version);
	ATOMIC_DEC(system_clearcaches_isinside);
	return result;
}


/* Returns (void *)-1 if data hasn't been loaded, yet. */
LOCAL NOBLOCK_IF(gfp & GFP_ATOMIC) NONNULL((1)) void *
NOTHROW(KCALL driver_section_cdata_test)(struct driver_section *__restrict self) {
	/* Check for simple case: Decompressed data has already been loaded. */
	if (self->ds_cdata != (void *)-1)
		return self->ds_cdata;
	assertf(self->ds_data != (void *)-1, "Raw section data hasn't been loaded");
	/* Check if the section is really compressed. Because if it isn't, then
	 * we must set-up the `ds_cdata' field as an alias for `ds_data'! */
	if (!(self->ds_flags & SHF_COMPRESSED)) {
		self->ds_csize = self->ds_size;
		COMPILER_WRITE_BARRIER();
		self->ds_cdata = self->ds_data;
		COMPILER_WRITE_BARRIER();
		return self->ds_data;
	}
	/* Tell the caller to load decompressed data _now_. */
	return (void *)-1;
}

/* Decompress section data.
 * @return: * : One of `ZLIB_ERROR_*' */
PRIVATE ATTR_NOINLINE int
NOTHROW(KCALL decompress_section_data)(void *dst, size_t dst_size,
                                       void const *src, size_t src_size) {
	ssize_t error;
	struct zlib_reader reader;
	zlib_reader_init(&reader, src, src_size);
	error = zlib_reader_read(&reader, dst, dst_size);
#if 0 /* Can't be enabled at the moment */
	if (error >= 0 && !zlib_reader_eof(&reader))
		error = ZLIB_ERROR_BAD_LENGTH; /* More data exists after the stream... */
#endif
	zlib_reader_fini(&reader);
	if unlikely(error < 0)
		return (int)error; /* Inflate error. */
	/* clear all trailing data that could not be read. */
	if ((size_t)error < dst_size)
		memset((byte_t *)dst + (size_t)error, 0, dst_size - error);
	return ZLIB_ERROR_OK;
}

#ifdef CONFIG_HAVE_DEBUGGER
PRIVATE ATTR_NOINLINE int
NOTHROW(KCALL decompress_section_data_with_log)(struct driver_section *self,
                                                void *dst, size_t dst_size,
                                                void const *src, size_t src_size) {
	int result;
	/* Tell the user that we're decompressing section data if we're in
	 * debugger mode. Do this because the act of decompressing may take
	 * 1 to 2 seconds, and the user may otherwise be confused about what's
	 * taking so long the first time they try to run some command that
	 * makes use of debug information. */
	if (dbg_active && self && self->ds_sectflags != 0xffff && self->ds_module) {
		struct driver *d = self->ds_module;
		char const *driver_name  = NULL;
		char const *section_name = NULL;
		void *screen_buffer;
		driver_name = d->d_filename;
		if (!driver_name)
			driver_name = d->d_name;
		if (self->ds_index < d->d_shnum && d->d_shstrtab && d->d_shdr) {
			section_name = d->d_shstrtab + d->d_shdr[self->ds_index].sh_name;
			if unlikely(section_name < d->d_shstrtab || section_name >= d->d_shstrtab_end)
				section_name = NULL;
		}
		screen_buffer = alloca(dbg_screen_width * dbg_screen_cellsize);
		dbg_getscreendata(0, dbg_screen_height - 1, dbg_screen_width, 1, screen_buffer);
		dbg_beginupdate();
		dbg_savecolor();
		dbg_setcolor(ANSITTY_CL_BLACK, ANSITTY_CL_LIGHT_GRAY);
		dbg_hline(0, dbg_screen_height - 1, dbg_screen_width, ' ');
		dbg_pprintf(0, dbg_screen_height - 1, DBGSTR("Decompressing %s:%s..."), driver_name, section_name);
		dbg_loadcolor();
		dbg_endupdate();
		result = decompress_section_data(dst, dst_size, src, src_size);
		dbg_setscreendata(0, dbg_screen_height - 1, dbg_screen_width, 1, screen_buffer);
	} else {
		result = decompress_section_data(dst, dst_size, src, src_size);
	}
	return result;
}
#else /* CONFIG_HAVE_DEBUGGER */
#define decompress_section_data_with_log(self, dst, dst_size, src, src_size) \
	decompress_section_data(dst, dst_size, src, src_size)
#endif /* !CONFIG_HAVE_DEBUGGER */



#if (defined(CONFIG_HAVE_USERMOD) && !defined(CONFIG_USERMOD_SECTION_CDATA_IS_DRIVER_SECTION_CDATA))
#define ElfV_NEED_MODDTYPE
#if !(defined(USERMOD_TYPE_ELF32) && defined(USERMOD_TYPE_ELF64))
#error "Bad configuration"
#endif /* !(USERMOD_TYPE_ELF32 && USERMOD_TYPE_ELF64) */
typedef union {
	Elf32_Chdr e32;
	Elf64_Chdr e64;
} ElfV_Chdr;
#define ElfV_field(self, um_modtype, name) (USERMOD_TYPE_ISELF32(um_modtype) ? (self).e32.name : (self).e64.name)
#define ElfV_sizeof(self, um_modtype)      (USERMOD_TYPE_ISELF32(um_modtype) ? sizeof((self).e32) : sizeof((self).e64))
#else /* !CONFIG_HAVE_USERMOD && !CONFIG_USERMOD_SECTION_CDATA_IS_DRIVER_SECTION_CDATA */
typedef ElfW(Chdr) ElfV_Chdr;
#define ElfV_field(self, um_modtype, name) (self).name
#define ElfV_sizeof(self, um_modtype)      sizeof(self)
#endif /* CONFIG_HAVE_USERMOD || CONFIG_USERMOD_SECTION_CDATA_IS_DRIVER_SECTION_CDATA */

/* Return a pointer to the decompressed data blob for `self'.
 * If data could not be decompressed, an `E_INVALID_ARGUMENT' exception is thrown.
 * NOTE: The caller must ensure that raw section data of `self' has been loaded,
 *       as in `self->ds_data != (void *)-1'!
 * @return: * : A blob of `self->ds_csize' (after the caller) bytes of memory,
 *              representing the section's decompressed memory contents. */
#ifdef ElfV_NEED_MODDTYPE
INTERN ATTR_RETNONNULL NOBLOCK_IF(gfp & GFP_ATOMIC) NONNULL((1)) void *KCALL
driver_section_cdata_impl(struct driver_section *__restrict self,
                          gfp_t gfp, uintptr_t modtype)
		THROWS(E_BADALLOC, E_WOULDBLOCK, E_INVALID_ARGUMENT)
#else /* ElfV_NEED_MODDTYPE */
PUBLIC ATTR_RETNONNULL NOBLOCK_IF(gfp & GFP_ATOMIC) NONNULL((1)) void *KCALL
driver_section_cdata(struct driver_section *__restrict self, gfp_t gfp)
		THROWS(E_BADALLOC, E_WOULDBLOCK, E_INVALID_ARGUMENT)
#endif /* !ElfV_NEED_MODDTYPE */
{
	void *result, *new_result;
	size_t sizeof_chdr, ch_size, ch_pages;
	ElfV_Chdr *chdr;
	/* Test for already-loaded data. */
	result = driver_section_cdata_test(self);
	if (result != (void *)-1)
		return result;
	/* Must load data */
	chdr = (ElfV_Chdr *)self->ds_data;
	/* Verify the compressed-section header. */
	sizeof_chdr = ElfV_sizeof(*chdr, modtype);
	if unlikely(self->ds_size < sizeof_chdr)
		THROW(E_INVALID_ARGUMENT);
	if unlikely(ElfV_field(*chdr, modtype, ch_type) != ELFCOMPRESS_ZLIB)
		THROW(E_INVALID_ARGUMENT);
	ch_size  = ElfV_field(*chdr, modtype, ch_size);
	ch_pages = CEILDIV(ch_size, PAGESIZE);

	/* Allocate a blob for decompressed section data. */
	result = vpage_alloc(ch_pages, 1, gfp | GFP_PREFLT);
	if unlikely(decompress_section_data_with_log(self, result, ch_size,
	                                             (byte_t *)chdr + sizeof_chdr,
	                                             self->ds_size - sizeof_chdr) !=
	            ZLIB_ERROR_OK) {
		/* Inflate error. */
		vpage_free(result, ch_pages);
		THROW(E_INVALID_ARGUMENT);
	}
	/* Save the results. */
	ATOMIC_STORE(self->ds_csize, ch_size); /* This must be written first! */
	/* Account for other thread that may have been performing
	 * the inflate alongside us. */
	new_result = ATOMIC_CMPXCH_VAL(self->ds_cdata, (void *)-1, result);
	if likely(new_result == (void *)-1)
		return result;
	/* Race condition: Some other thread already did the thing! */
	vpage_free(result, ch_pages);
	return new_result;
}

/* @return: NULL: Failed to acquire compressed data. */
#ifdef ElfV_NEED_MODDTYPE
INTERN NOBLOCK_IF(gfp & GFP_ATOMIC) NONNULL((1)) void *
NOTHROW(KCALL driver_section_cdata_nx_impl)(struct driver_section *__restrict self,
                                            gfp_t gfp, uintptr_t modtype)
#else /* ElfV_NEED_MODDTYPE */
PUBLIC NOBLOCK_IF(gfp & GFP_ATOMIC) NONNULL((1)) void *
NOTHROW(KCALL driver_section_cdata_nx)(struct driver_section *__restrict self, gfp_t gfp)
#endif /* !ElfV_NEED_MODDTYPE */
{
	void *result, *new_result;
	size_t sizeof_chdr, ch_size, ch_pages;
	ElfV_Chdr *chdr;
	/* Test for already-loaded data. */
	result = driver_section_cdata_test(self);
	if (result != (void *)-1)
		return result;
	/* Must load data */
	chdr = (ElfV_Chdr *)self->ds_data;
	/* Verify the compressed-section header. */
	sizeof_chdr = ElfV_sizeof(*chdr, modtype);
	if unlikely(self->ds_size < sizeof_chdr)
		goto err;
	if unlikely(ElfV_field(*chdr, modtype, ch_type) != ELFCOMPRESS_ZLIB)
		goto err;
	ch_size  = ElfV_field(*chdr, modtype, ch_size);
	ch_pages = CEILDIV(ch_size, PAGESIZE);

	/* Allocate a blob for decompressed section data. */
	result = vpage_alloc_nx(ch_pages, 1, gfp | GFP_PREFLT);
	if unlikely(!result)
		goto err;
	if unlikely(decompress_section_data_with_log(self, result, ch_size,
	                                             (byte_t *)chdr + sizeof_chdr,
	                                             self->ds_size - sizeof_chdr) !=
	            ZLIB_ERROR_OK) {
		/* Inflate error. */
		vpage_free(result, ch_pages);
		goto err;
	}
	/* Save the results. */
	ATOMIC_STORE(self->ds_csize, ch_size); /* This must be written first! */
	/* Account for other thread that may have been performing
	 * the inflate alongside us. */
	new_result = ATOMIC_CMPXCH_VAL(self->ds_cdata, (void *)-1, result);
	if likely(new_result == (void *)-1)
		return result;
	/* Race condition: Some other thread already did the thing! */
	vpage_free(result, ch_pages);
	return new_result;
err:
	return NULL;
}

/* Define the native, driver-level wrappers. */
#ifdef ElfV_NEED_MODDTYPE
#if ELF_ARCH_CLASS == ELFCLASS32
#define ElfV_NATIVE_MODDTYPE USERMOD_TYPE_ELF32
#elif ELF_ARCH_CLASS == ELFCLASS64
#define ElfV_NATIVE_MODDTYPE USERMOD_TYPE_ELF64
#endif /* ELF_ARCH_CLASS == ... */

PUBLIC ATTR_RETNONNULL NOBLOCK_IF(gfp & GFP_ATOMIC) NONNULL((1)) void *KCALL
driver_section_cdata(struct driver_section *__restrict self, gfp_t gfp)
		THROWS(E_BADALLOC, E_WOULDBLOCK, E_INVALID_ARGUMENT) {
	return driver_section_cdata_impl(self, gfp, ElfV_NATIVE_MODDTYPE);
}

PUBLIC NOBLOCK_IF(gfp & GFP_ATOMIC) NONNULL((1)) void *
NOTHROW(KCALL driver_section_cdata_nx)(struct driver_section *__restrict self, gfp_t gfp) {
	return driver_section_cdata_nx_impl(self, gfp, ElfV_NATIVE_MODDTYPE);
}
#endif /* ElfV_NEED_MODDTYPE */






PRIVATE NOBLOCK NONNULL((1, 2)) void
NOTHROW(KCALL driver_section_do_destroy_with_sections_lock_held)(struct driver_section *__restrict self,
                                                                 struct driver *__restrict drv) {
	assert(wasdestroyed(self));
	assert(sync_writing(&drv->d_sections_lock) || wasdestroyed(drv));
	assert(self->ds_module == drv); /* The reference from `ds_module' was already deleted by the caller. */
	if (self->ds_sectflags & DRIVER_DLSECTION_FOWNED) {
		/* Must unmap sections data. */
		uintptr_t sect_base;
		size_t sect_size;
		sect_base = (uintptr_t)self->ds_data;
		if (sect_base != (uintptr_t)-1) {
			sect_size = self->ds_size;
			sect_size += sect_base & PAGEMASK;
			sect_base &= ~PAGEMASK;
			vpage_free((void *)sect_base,
			           (size_t)CEILDIV(sect_size, PAGESIZE));
		}
	}
	/* Free compressed section data. */
	if (self->ds_cdata != (void *)-1 && self->ds_cdata != self->ds_data)
		vpage_free(self->ds_cdata, (size_t)CEILDIV(self->ds_csize, PAGESIZE));
	kfree(self);
}

#define driver_must_service_dead_sections(self) \
	(ATOMIC_READ((self)->d_deadsect) != NULL)

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL driver_do_service_dead_sections)(struct driver *__restrict self) {
	REF struct driver_section *iter, *next;
	assert(wasdestroyed(self) || sync_writing(&self->d_sections_lock));
	iter = ATOMIC_XCH(self->d_deadsect, NULL);
	while (iter) {
		next = iter->ds_dangling;
		assert(wasdestroyed(iter));
		driver_section_do_destroy_with_sections_lock_held(iter, self);
		iter = next;
	}
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL driver_do_clear_dang_sections)(struct driver *__restrict self) {
	REF struct driver_section *iter, *next;
	assert(sync_writing(&self->d_sections_lock));
	iter = ATOMIC_XCH(self->d_dangsect, NULL);
	while (iter) {
		next = iter->ds_dangling;
		assert(!wasdestroyed(iter));
		if (ATOMIC_DECFETCH(iter->ds_refcnt) == 0) {
			/* Destroy this section. */
			assert(iter->ds_index < self->d_shnum);
			assert(iter->ds_module == self);
			assert(self->d_sections[iter->ds_index] == iter);
			self->d_sections[iter->ds_index] = NULL;
			driver_section_do_destroy_with_sections_lock_held(iter, self);
			decref_nokill(self); /* Reference from `iter->ds_module' */
		}
		iter = next;
	}
}


PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL driver_destroy)(struct driver *__restrict self) {
	ElfW(Half) i;
	assert(wasdestroyed(self));
	assertf(self->d_flags & DRIVER_FLAG_FINALIZED,
	        "Without this flag, our reference count should not have been able to reach 0!");
	assert(self != &kernel_driver);

	/* Invoke dynamic driver unloading callbacks. */
	driver_unloaded_callbacks(self);

	/* Try to remove the driver from the loaded-driver-list */
	try_remove_driver_from_global_set(self);

	printk(KERN_NOTICE "[mod][-] Delmod: %q\n", self->d_name);

	/* Wake up someone who might be waiting for the driver to get unloaded. */
	sig_broadcast(&self->d_destroyed);

	/* Service any remaining dead sections! */
	driver_do_service_dead_sections(self);
	assert(!self->d_dangsect);
	/* Go through all of the module's program headers and unload them from memory.
	 * Because drivers are mapped as anonymous memory, rather than file mappings,
	 * we can simply use the NOEXCEPT,NOBLOCK `vm_unmap_kernel_ram()' function! */
	for (i = 0; i < self->d_phnum; ++i) {
		uintptr_t progaddr;
		size_t progsize;
		if (self->d_phdr[i].p_type != PT_LOAD)
			continue;
		progaddr = (uintptr_t)(self->d_loadaddr + self->d_phdr[i].p_vaddr);
		progsize = self->d_phdr[i].p_memsz;
		progsize += progaddr & PAGEMASK;
		progaddr &= ~PAGEMASK;
		/* NOTE: During finalization, all write-only program headers were re-mapped
		 *       as read/write, so-as to allow us to free them as kernel-ram at this
		 *       point. */
		vm_unmap_kernel_ram((void *)progaddr,
		                     CEIL_ALIGN(progsize, PAGESIZE),
		                     false);
	}
	/* Free heap-allocated structures. */
	if (self->d_eh_frame_cache)
		driver_fde_free_tree(self->d_eh_frame_cache);
	kfree((void *)self->d_shdr);
	kfree((void *)self->d_depvec);
	kfree((void *)self->d_shstrtab);
	kfree((void *)self->d_sections);
	kfree((void *)self->d_cmdline);
	kfree((void *)self->d_argv);
	kfree((void *)self->d_filename);
	xdecref(self->d_file);
	weakdecref_likely(self);
}

PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL driver_free)(struct driver *__restrict self) {
	kfree(self);
}





INTDEF byte_t __kernel_start[];
INTDEF byte_t __kernel_end[];
INTDEF byte_t __kernel_size[];
INTDEF byte_t __kernel_size_nofree[];

/* TODO: Set `kernel_driver.d_loadend = __kernel_free_start' when unloading .free */
/* TODO: Set `kernel_driver.d_phnum   = 1' when unloading .free */
INTDEF byte_t __kernel_free_start[];
INTDEF byte_t __kernel_free_size[];
INTDEF byte_t __kernel_eh_frame_start[];
INTDEF byte_t __kernel_eh_frame_end[];

PRIVATE ATTR_COLDRODATA char const kernel_driver_name[]     = KERNEL_DRIVER_NAME;
PRIVATE ATTR_COLDRODATA char const kernel_driver_filename[] = KERNEL_DRIVER_FILENAME;


INTDEF char const kernel_shstrtab_data[];
INTDEF ElfW(Shdr) const kernel_shdr[];
INTDEF struct driver_section *const kernel_sections[];

#ifndef __INTELLISENSE__
#define SECTION_DESCRIPTOR_INDEX     PP_CAT2(KERNEL_SECTION_INDEX_, __LINE__)
#define SECTION_DESCRIPTOR_SHSTRNAME PP_CAT2(ks_name_, __LINE__)
#define SECTION_GLOBALS_DEFINED 1
enum{
#define INTERN_SECTION(symbol_name, name, type, flags, start, size, entsize, link, info) \
	SECTION_DESCRIPTOR_INDEX,
#include "kernel_sections.def"
	KERNEL_SECTIONS_COUNT
};
/* Define the kernel's .shstrtab section */
struct kernel_shstrtab {
#define INTERN_SECTION(symbol_name, name, type, flags, start, size, entsize, link, info) \
	char SECTION_DESCRIPTOR_SHSTRNAME[sizeof(name)];
#include "kernel_sections.def"
};
#undef SECTION_DESCRIPTOR_INDEX
#undef SECTION_DESCRIPTOR_SHSTRNAME
#endif /* !__INTELLISENSE__ */


PUBLIC struct driver kernel_driver = {
	/* .d_refcnt               = */ 2, /* +1: kernel_driver, +1: !DRIVER_FLAG_FINALIZED */
	/* .d_weakrefcnt           = */ 1, /* +1: kernel_driver */
	/* .d_name                 = */ kernel_driver_name,
	/* .d_filename             = */ kernel_driver_filename,
	/* .d_file                 = */ NULL,
	/* .d_cmdline              = */ NULL,
	/* .d_argc                 = */ 0,
	/* .d_argv                 = */ NULL,
	/* .d_flags                = */ (DRIVER_FLAG_DEPLOADING | DRIVER_FLAG_DEPLOADED |
	                                 DRIVER_FLAG_RELOCATING | DRIVER_FLAG_RELOCATED |
	                                 DRIVER_FLAG_INITIALIZED | DRIVER_FLAG_INITIALIZING),
	/* .d_initthread           = */ NULL,
	/* .d_loadaddr             = */ 0,
	/* .d_loadstart            = */ (uintptr_t)__kernel_start,
	/* .d_loadend              = */ (uintptr_t)__kernel_end,
	/* .d_eh_frame_start       = */ (byte_t *)__kernel_eh_frame_start,
	/* .d_eh_frame_end         = */ (byte_t *)__kernel_eh_frame_end,
	/* .d_eh_frame_cache       = */ NULL,
	/* .d_eh_frame_cache_lock  = */ ATOMIC_RWLOCK_INIT,
	/* .d_eh_frame_cache_semi0 = */ ATREE_SEMI0(uintptr_t),   /* TODO: Optimize specifically for the kernel core? */
	/* .d_eh_frame_cache_leve0 = */ ATREE_LEVEL0(uintptr_t),  /* TODO: Optimize specifically for the kernel core? */
#if __SIZEOF_POINTER__ > __SIZEOF_INT__
	/* .d_pad                  = */ { 0, },
#endif /* __SIZEOF_POINTER__ > __SIZEOF_INT__ */
	/* .d_depcnt               = */ 0,
	/* .d_depvec               = */ NULL,
	/* .d_dyncnt               = */ 0,
	/* .d_dynhdr               = */ NULL,
	/* .d_dynsym_tab           = */ NULL,
	/* .d_dynsym_cnt           = */ 0,
	/* .d_hashtab              = */ NULL,
	/* .d_dynstr               = */ NULL,
	/* .d_dynstr_end           = */ NULL,
	/* .d_shoff                = */ 0,
#ifdef __INTELLISENSE__
	/* .d_shstrndx             = */ 0,
	/* .d_shnum                = */ 0,
#else /* __INTELLISENSE__ */
	/* .d_shstrndx             = */ KERNEL_SECTIONS_COUNT - 1,
	/* .d_shnum                = */ KERNEL_SECTIONS_COUNT,
#endif /* !__INTELLISENSE__ */
#if __SIZEOF_POINTER__ > 4
	/* .d_pad2                 = */ { 0, },
#endif /* __SIZEOF_POINTER__ > 4 */
	/* .d_shdr                 = */ kernel_shdr,
	/* .d_sections_lock        = */ ATOMIC_RWLOCK_INIT,
	/* .d_sections             = */ (struct driver_section **)kernel_sections,
	/* .d_deadsect             = */ NULL,
	/* .d_dangsect             = */ NULL,
	/* .d_shstrtab             = */ kernel_shstrtab_data,
#ifdef __INTELLISENSE__
	/* .d_shstrtab_end         = */ kernel_shstrtab_data,
#else /* __INTELLISENSE__ */
	/* .d_shstrtab_end         = */ kernel_shstrtab_data + sizeof(struct kernel_shstrtab),
#endif /* !__INTELLISENSE__ */
	/* .d_destroyed              = */ SIG_INIT,
	/* .d_phnum                = */ 2,
	/* .d_pad3                 = */ { 0, },
	{
		/* [0] = */ ELFW(PHDR_INIT)(
			/* .p_type   = */ PT_LOAD,
			/* .p_offset = */ 0, /* Doesn't matter... */
			/* .p_vaddr  = */ (uintptr_t)__kernel_start,
			/* .p_paddr  = */ (uintptr_t)__kernel_start - KERNEL_CORE_BASE,
			/* .p_filesz = */ (uintptr_t)__kernel_size_nofree,
			/* .p_memsz  = */ (uintptr_t)__kernel_size_nofree,
			/* .p_flags  = */ PF_X | PF_W | PF_R,
			/* .p_align  = */ PAGESIZE
		),
		/* [1] = */ ELFW(PHDR_INIT)(
			/* .p_type   = */ PT_LOAD,
			/* .p_offset = */ 0, /* Doesn't matter... */
			/* .p_vaddr  = */ (uintptr_t)__kernel_free_start,
			/* .p_paddr  = */ (uintptr_t)__kernel_free_start - KERNEL_CORE_BASE,
			/* .p_filesz = */ (uintptr_t)__kernel_free_size,
			/* .p_memsz  = */ (uintptr_t)__kernel_free_size,
			/* .p_flags  = */ PF_X | PF_W | PF_R,
			/* .p_align  = */ PAGESIZE
		)
	}
};


PRIVATE ATTR_NOINLINE ATTR_FREETEXT void
NOTHROW(KCALL malformed_argument)(char const *__restrict optname,
                                  char const *__restrict argstr) {
	kernel_panic(FREESTR("Malformed commandline argument for %q: %q"),
	             optname, argstr);
}

PRIVATE ATTR_NOINLINE ATTR_FREETEXT void
NOTHROW(KCALL initialize_cmdline)(struct kernel_commandline_option const *start,
                                  struct kernel_commandline_option const *end) {
	size_t i;
	char *arg;
	if (!kernel_driver.d_cmdline)
		return; /* No commandline provided. */
	while (start < end) {
		size_t namlen;
		namlen = strlen(start->co_name);
		assert(start->co_type <= KERNEL_COMMANDLINE_OPTION_TYPE_UINT64);
		if (start->co_type >= KERNEL_COMMANDLINE_OPTION_TYPE_PRESENT &&
		    start->co_type <= KERNEL_COMMANDLINE_OPTION_TYPE_BOOL) {
			/* Check if the option is present. */
			for (i = 0, arg = kernel_driver.d_cmdline;
			     i < kernel_driver.d_argc; ++i, arg = strend(arg) + 1) {
				if (memcmp(arg, start->co_name, namlen * sizeof(char)) != 0)
					continue;
				if (arg[namlen] != 0)
					continue;
				switch (start->co_type) {

				case KERNEL_COMMANDLINE_OPTION_TYPE_PRESENT:
					(*start->co_present)();
					break;

				case KERNEL_COMMANDLINE_OPTION_TYPE_BOOL:
					*(bool *)start->co_option_addr = true;
					break;

				default: __builtin_unreachable();
				}
				goto next_option;
			}
			if (start->co_type == KERNEL_COMMANDLINE_OPTION_TYPE_BOOL)
				*(bool *)start->co_option_addr = false;
		} else {
			/* Check for an option that has an argument. */
			for (i = 0, arg = kernel_driver.d_cmdline;
			     i < kernel_driver.d_argc; ++i, arg = strend(arg) + 1) {
				char *eq = strchr(arg, '=');
				size_t optlen;
				if (!eq)
					continue;
				optlen = (size_t)(eq - arg);
				if (optlen != namlen)
					continue;
				if (memcmp(arg, start->co_name, optlen * sizeof(char)) != 0)
					continue;
				arg += optlen + 1;
				switch (start->co_type) {

				case KERNEL_COMMANDLINE_OPTION_TYPE_FUNC:
					(*start->co_handler)(arg);
					break;

				case KERNEL_COMMANDLINE_OPTION_TYPE_STRING:
					*(char **)start->co_option_addr = arg;
					break;

#if __SIZEOF_POINTER__ < 8
				case KERNEL_COMMANDLINE_OPTION_TYPE_INT64: {
					char *endp;
					int64_t value;
					value = strto64(arg, &endp, 0);
					if (*endp)
						malformed_argument(start->co_name, arg);
					*(int64_t *)start->co_option_addr = value;
				}	break;
#endif /* __SIZEOF_POINTER__ >= 8 */

#if __SIZEOF_POINTER__ < 8
				case KERNEL_COMMANDLINE_OPTION_TYPE_UINT64: {
					char *endp;
					uint64_t value;
					value = strtou64(arg, &endp, 0);
					if (*endp)
						malformed_argument(start->co_name, arg);
					*(uint64_t *)start->co_option_addr = value;
				}	break;
#endif /* __SIZEOF_POINTER__ >= 8 */

				case KERNEL_COMMANDLINE_OPTION_TYPE_INT8:
				case KERNEL_COMMANDLINE_OPTION_TYPE_INT16:
				case KERNEL_COMMANDLINE_OPTION_TYPE_INT32: {
					char *endp;
#if __SIZEOF_POINTER__ < 8
					int32_t value;
					value = strto32(arg, &endp, 0);
#else /* __SIZEOF_POINTER__ < 8 */
					int64_t value;
				case KERNEL_COMMANDLINE_OPTION_TYPE_INT64:
					value = strto64(arg, &endp, 0);
#endif /* __SIZEOF_POINTER__ >= 8 */
					if (*endp)
						malformed_argument(start->co_name, arg);
					switch (start->co_type) {
					case KERNEL_COMMANDLINE_OPTION_TYPE_INT8:
						*(int8_t *)start->co_option_addr = (int8_t)value;
						break;
					case KERNEL_COMMANDLINE_OPTION_TYPE_INT16:
						*(int16_t *)start->co_option_addr = (int16_t)value;
						break;
					case KERNEL_COMMANDLINE_OPTION_TYPE_INT32:
						*(int32_t *)start->co_option_addr = (int32_t)value;
						break;
#if __SIZEOF_POINTER__ >= 8
					case KERNEL_COMMANDLINE_OPTION_TYPE_INT64:
						*(int64_t *)start->co_option_addr = (int64_t)value;
						break;
#endif /* __SIZEOF_POINTER__ >= 8 */
					default: __builtin_unreachable();
					}
				}	break;

				case KERNEL_COMMANDLINE_OPTION_TYPE_UINT8:
				case KERNEL_COMMANDLINE_OPTION_TYPE_UINT16:
				case KERNEL_COMMANDLINE_OPTION_TYPE_UINT32: {
					char *endp;
#if __SIZEOF_POINTER__ < 8
					uint32_t value;
					value = strtou32(arg, &endp, 0);
#else /* __SIZEOF_POINTER__ < 8 */
					uint64_t value;
				case KERNEL_COMMANDLINE_OPTION_TYPE_UINT64:
					value = strtou64(arg, &endp, 0);
#endif /* __SIZEOF_POINTER__ >= 8 */
					if (*endp)
						malformed_argument(start->co_name, arg);
					switch (start->co_type) {
					case KERNEL_COMMANDLINE_OPTION_TYPE_UINT8:
						*(uint8_t *)start->co_option_addr = (uint8_t)value;
						break;
					case KERNEL_COMMANDLINE_OPTION_TYPE_UINT16:
						*(uint16_t *)start->co_option_addr = (uint16_t)value;
						break;
					case KERNEL_COMMANDLINE_OPTION_TYPE_UINT32:
						*(uint32_t *)start->co_option_addr = (uint32_t)value;
						break;
#if __SIZEOF_POINTER__ >= 8
					case KERNEL_COMMANDLINE_OPTION_TYPE_UINT64:
						*(uint64_t *)start->co_option_addr = (uint64_t)value;
						break;
#endif /* __SIZEOF_POINTER__ >= 8 */
					default: __builtin_unreachable();
					}
				}	break;

				default: __builtin_unreachable();
				}
				goto next_option;
			}
		}
next_option:
		start = (struct kernel_commandline_option const *)((uintptr_t)start +
		                                                   ((offsetof(struct kernel_commandline_option, co_name) +
		                                                     (namlen + 1) * sizeof(char) + (sizeof(void *) - 1)) &
		                                                    ~(sizeof(void *) - 1)));
	}
}


INTDEF FREE struct kernel_commandline_option const __kernel_commandline_very_early_start[];
INTDEF FREE struct kernel_commandline_option const __kernel_commandline_very_early_end[];
INTERN ATTR_FREETEXT void
NOTHROW(KCALL kernel_initialize_commandline_options_very_early)(void) {
	initialize_cmdline(__kernel_commandline_very_early_start,
	                   __kernel_commandline_very_early_end);
}

INTDEF FREE struct kernel_commandline_option const __kernel_commandline_early_start[];
INTDEF FREE struct kernel_commandline_option const __kernel_commandline_early_end[];
INTERN ATTR_FREETEXT void
NOTHROW(KCALL kernel_initialize_commandline_options_early)(void) {
	initialize_cmdline(__kernel_commandline_early_start,
	                   __kernel_commandline_early_end);
}

INTDEF FREE struct kernel_commandline_option const __kernel_commandline_stable_start[];
INTDEF FREE struct kernel_commandline_option const __kernel_commandline_stable_end[];
INTERN ATTR_FREETEXT void
NOTHROW(KCALL kernel_initialize_commandline_options_stable)(void) {
	initialize_cmdline(__kernel_commandline_stable_start,
	                   __kernel_commandline_stable_end);
}

INTDEF FREE struct kernel_commandline_option const __kernel_commandline_late_start[];
INTDEF FREE struct kernel_commandline_option const __kernel_commandline_late_end[];
INTERN ATTR_FREETEXT void
NOTHROW(KCALL kernel_initialize_commandline_options_late)(void) {
	initialize_cmdline(__kernel_commandline_late_start,
	                   __kernel_commandline_late_end);
}



PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL driver_section_destroy)(struct driver_section *__restrict self) {
	REF struct driver *drv;
	drv = self->ds_module;
	/* Try to turn the section into a dangling one. */
	if (sync_trywrite(&drv->d_sections_lock)) {
		driver_do_service_dead_sections(drv);
		if (ATOMIC_READ(drv->d_flags) & DRIVER_FLAG_FINALIZING) {
			/* The module is being finalized. -> Delete the section, rather than set it as dangling! */
			driver_section_do_destroy_with_sections_lock_held(self, drv);
			goto done_service_endwrite_decref;
		}
		ATOMIC_WRITE(self->ds_refcnt, 1);
		self->ds_dangling = drv->d_dangsect;
		drv->d_dangsect   = self;
		sync_endwrite(&drv->d_sections_lock);
		return;
	}
	/* Must delete the driver.
	 * -> Since we were already unable to lock `drv->d_sections_lock',
	 *    we already know that we must make use of the `d_deadsect'
	 *    chain mechanism. */
	{
		struct driver_section *next;
		do
			self->ds_dangling = next = ATOMIC_READ(drv->d_deadsect);
		while (!ATOMIC_CMPXCH_WEAK(drv->d_deadsect, next, self));
	}
	if (sync_trywrite(&drv->d_sections_lock)) {
done_service_endwrite_decref:
		driver_do_service_dead_sections(drv);
		sync_endwrite(&drv->d_sections_lock);
	}
	decref(drv); /* The reference previously held by `self->ds_module' */
}



PRIVATE NONNULL((1)) void KCALL
driver_verify_ehdr(ElfW(Ehdr) const *__restrict ehdr)
		THROWS(E_NOT_EXECUTABLE) {
	unsigned int reason;
	if unlikely(ehdr->e_ident[EI_MAG0] != ELFMAG0 ||
	            ehdr->e_ident[EI_MAG1] != ELFMAG1 ||
	            ehdr->e_ident[EI_MAG2] != ELFMAG2 ||
	            ehdr->e_ident[EI_MAG3] != ELFMAG3)
		THROW(E_NOT_EXECUTABLE_NOT_A_BINARY);
	reason = E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BADCLASS;
	if unlikely(ehdr->e_ident[EI_CLASS] != KERNEL_DRIVER_REQUIRED_CLASS)
		goto err_elf_reason;
	reason = E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BADORDER;
	if unlikely(ehdr->e_ident[EI_DATA] != KERNEL_DRIVER_REQUIRED_DATA)
		goto err_elf_reason;
	reason = E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BADVERSION;
	if unlikely(ehdr->e_ident[EI_VERSION] != EV_CURRENT)
		goto err_elf_reason;
	reason = E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BADVERSION2;
	if unlikely(ehdr->e_version != EV_CURRENT)
		goto err_elf_reason;
	reason = E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BADTYPE;
	if unlikely(ehdr->e_type != ET_DYN)
		goto err_elf_reason;
	reason = E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BADMACH;
	if unlikely(ehdr->e_machine != KERNEL_DRIVER_REQUIRED_MACHINE)
		goto err_elf_reason;
	reason = E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BADHEADER;
	if unlikely(ehdr->e_ehsize < offsetafter(ElfW(Ehdr), e_phnum))
		goto err_elf_reason;
	reason = E_NOT_EXECUTABLE_FAULTY_REASON_ELF_NOSEGMENTS;
	if unlikely(ehdr->e_phnum == 0)
		goto err_elf_reason;
	reason = E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BADSEGMENTS;
	if unlikely(ehdr->e_phentsize != sizeof(ElfW(Phdr)))
		goto err_elf_reason;
	return;
err_elf_reason:
	THROW(E_NOT_EXECUTABLE_FAULTY,
	      E_NOT_EXECUTABLE_FAULTY_FORMAT_ELF,
	      reason);
}




/* Return the INode/filename of a given driver (which is
 * lazily loaded for drivers loaded via the kernel commandline) */
PUBLIC WUNUSED NONNULL((1)) struct regular_node *KCALL
driver_getfile(struct driver *__restrict self)
		THROWS(E_IOERROR, E_WOULDBLOCK, E_BADALLOC) {
	char const *filename;
	char const *lastseg_start;
	u16 lastseg_len;
	REF struct path *driver_path;
	REF struct directory_node *driver_directory;
	REF struct regular_node *driver_node;
	if (self->d_file)
		return self->d_file;
	filename = driver_getfilename(self);
	if unlikely(!filename) {
		return NULL;
	}
	COMPILER_READ_BARRIER();
	if (self->d_file)
		return self->d_file;
	/* Lookup the specified filename in real root filesystem. */
	TRY {
		driver_path = path_traverse(&fs_kernel,
		                            filename,
		                            &lastseg_start,
		                            &lastseg_len,
		                            FS_MODE_FNORMAL,
		                            NULL);
	} EXCEPT {
		error_code_t code = error_code();
		if (ERROR_CLASS(code) == E_FSERROR &&
		    E_FSERROR_IS_FILE_NOT_FOUND(code))
			return NULL; /* File not found */
		RETHROW();
	}
	{
		FINALLY_DECREF(driver_path);
		sync_read(driver_path);
		driver_directory = (REF struct directory_node *)incref(driver_path->p_inode);
		sync_endread(driver_path);
	}
	{
		FINALLY_DECREF(driver_directory);
		driver_node = (REF struct regular_node *)directory_getnode(driver_directory,
		                                                           lastseg_start,
		                                                           lastseg_len,
		                                                           directory_entry_hash(lastseg_start, lastseg_len),
		                                                           NULL);
	}
	if unlikely(!driver_node) {
		return NULL; /* File not found */
	}
	if unlikely(!INODE_ISREG((struct inode *)driver_node)) {
		decref(driver_node);
		return NULL; /* Not a file */
	}
	/* Remember that this is the driver's INode */
	if (!ATOMIC_CMPXCH(self->d_file, NULL, driver_node)) {
		decref_unlikely(driver_node); /* Resolve race condition... */
		driver_node = ATOMIC_READ(self->d_file);
	}
	return driver_node;
}

PUBLIC WUNUSED NONNULL((1)) char const *
(KCALL driver_getfilename)(struct driver *__restrict self)
		THROWS(E_IOERROR, E_WOULDBLOCK, E_BADALLOC) {
	if (self->d_filename)
		return self->d_filename;
	COMPILER_IMPURE();
	/* TODO: Search for a file `self->d_name' in the kernel driver library path list. */
	return NULL;
}


/* Lazily allocate if necessary, and return the vector of section headers for `self'
 * NOTE: On success, this function guaranties that the following fields have been initialized:
 *  - self->d_shdr
 * @return: * :   Returns `self->d_shdr'
 * @return: NULL: Failed to load the section headers vector (the driver
 *                file wasn't found, or doesn't contain any sections) */
PUBLIC WUNUSED NONNULL((1)) ElfW(Shdr) const *KCALL
driver_getshdrs(struct driver *__restrict self)
		THROWS(E_IOERROR, E_WOULDBLOCK, E_BADALLOC) {
	struct regular_node *node;
	ElfW(Shdr) *result;
	if (self->d_shdr)
		return self->d_shdr;
	node = driver_getfile(self);
	if unlikely(!node)
		return NULL;
	/* Allocate the section header vector. */
	result = (ElfW(Shdr) *)kmalloc(self->d_shnum * sizeof(ElfW(Shdr)), GFP_PREFLT);
	TRY {
		inode_readallk(node, result, self->d_shnum * sizeof(ElfW(Shdr)), (pos_t)self->d_shoff);
	} EXCEPT {
		kfree(result);
		RETHROW();
	}
	{
		ElfW(Shdr) *new_result;
		/* Save the newly loaded section header vector. */
		new_result = (ElfW(Shdr) *)ATOMIC_CMPXCH_VAL(self->d_shdr,
		                                             NULL,
		                                             result);
		if unlikely(new_result != NULL) {
			kfree(result);
			result = new_result;
		}
	}
	return result;
}

/* Lazily allocate if necessary, and return the section header string table for `self'
 * @return: * :   Returns `self->d_shstrtab'
 * @return: NULL: Failed to load the section headers string table (the driver
 *                file wasn't found, or doesn't contain any sections) */
PUBLIC WUNUSED NONNULL((1)) char const *KCALL
driver_getshstrtab(struct driver *__restrict self)
		THROWS(E_IOERROR,E_WOULDBLOCK, E_BADALLOC) {
	char *result;
	ElfW(Shdr) const *shdrs;
	result = (char *)self->d_shstrtab;
	if (result)
		return result;
	shdrs = driver_getshdrs(self);
	if unlikely(!shdrs)
		return NULL;
	shdrs += self->d_shstrndx;
	if unlikely(shdrs->sh_type == SHT_NOBITS)
		return NULL;
	/* Allocate the section header string table. */
	result = (char *)kmalloc(shdrs->sh_size + 1, GFP_PREFLT);
	result[shdrs->sh_size] = '\0'; /* Ensure NUL-termination */
	TRY {
		/* Read the string table into memory. */
		inode_readallk(self->d_file,
		               result,
		               shdrs->sh_size,
		               (pos_t)shdrs->sh_offset);
	} EXCEPT {
		kfree(result);
		RETHROW();
	}
	{
		char *new_result;
		/* Save the newly loaded section header string table. */
		ATOMIC_CMPXCH(self->d_shstrtab_end, NULL, result + shdrs->sh_size);
		new_result = (char *)ATOMIC_CMPXCH_VAL(self->d_shstrtab,
		                                       NULL,
		                                       result);
		if unlikely(new_result != NULL) {
			kfree(result);
			result = new_result;
		}
	}
	return result;
}

/* Return the section header associated with a given `name'
 * @return: * :   Returns a pointer to one of `&self->d_shdr[*]'
 * @return: NULL: No section exists that matches the given `name'
 * @return: NULL: Failed to load the section headers string table (the driver
 *                file wasn't found, or doesn't contain any sections) */
PUBLIC WUNUSED NONNULL((1)) ElfW(Shdr) const *KCALL
driver_getsection(struct driver *__restrict self,
                  USER CHECKED char const *name)
		THROWS(E_IOERROR, E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT) {
	ElfW(Shdr) const *result;
	uint16_t i;
	char const *strtab;
	strtab = driver_getshstrtab(self);
	if unlikely(!strtab) {
		goto err;
	}
	result = self->d_shdr;
	assert(result);
	for (i = 0; i < self->d_shnum; ++i, ++result) {
		if (strcmp(strtab + result->sh_name, name) == 0)
			return result; /* Got it! */
	}
err:
	return NULL;
}

/* Registers/thread-local variables that are saved/restored unconditionally
 * before/after invocation of driver initializers/finalizers.
 * This is done since driver init/fini functions may leave certain registers
 * clobbered, such as `PREEMPTION_ENABLED()', which we must make certain to
 * properly restore after invocation, as not doing so may cause later code
 * to throw `E_WOULDBLOCK' when `task_yield()' is called with preemption
 * disabled after a driver initializer failed to restore the preemption-
 * enabled state. */
struct driver_initstate {
	pflag_t di_preemption; /* The old preemption state. */
};

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL driver_init_savestate)(struct driver_initstate *__restrict self) {
	self->di_preemption = PREEMPTION_PUSH();
}
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL driver_init_loadstate)(struct driver_initstate const *__restrict self) {
	PREEMPTION_POP(self->di_preemption);
}


PRIVATE NONNULL((1)) void FCALL
call_destructor_at(struct driver *__restrict self, uintptr_t func) {
	if likely(func >= self->d_loadstart &&
	          func < self->d_loadend) {
		struct driver_initstate st;
		driver_init_savestate(&st);
		TRY {
			(*(void(*)(void))func)();
		} EXCEPT {
			driver_init_loadstate(&st);
			RETHROW();
		}
		driver_init_loadstate(&st);
	} else {
		printk(KERN_ERR "[mod] Driver %q destructor at %p is out-of-bounds of %p...%p\n",
		       self->d_name, func, self->d_loadstart, self->d_loadend);
	}
}

PRIVATE NONNULL((1)) void KCALL
driver_invoke_destructors(struct driver *__restrict self) {
	uintptr_t fini_func        = 0;
	uintptr_t *fini_array_base = NULL;
	size_t fini_array_size     = 0;
	size_t i;

	for (i = 0; i < self->d_dyncnt; ++i) {
		switch (self->d_dynhdr[i].d_tag) {

		case DT_NULL:
			goto done_dyntag;

		case DT_FINI:
			fini_func = (uintptr_t)self->d_dynhdr[i].d_un.d_ptr;
			break;

		case DT_FINI_ARRAY:
			fini_array_base = (uintptr_t *)(self->d_loadaddr +
			                                self->d_dynhdr[i].d_un.d_ptr);
			break;

		case DT_FINI_ARRAYSZ:
			fini_array_size = (size_t)self->d_dynhdr[i].d_un.d_val / sizeof(void(*)(void));
			break;

		default: break;
		}
	}
done_dyntag:
	/* Service fini-array functions in reverse order. */
	while (fini_array_size--)
		call_destructor_at(self, /*self->d_loadaddr + */ fini_array_base[fini_array_size]);
	/* Service a fini function, if one was specified. */
	if (fini_func)
		call_destructor_at(self, self->d_loadaddr + fini_func);
}


PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL driver_decref_dependencies)(struct driver *__restrict self) {
	size_t i;
	for (i = 0; i < self->d_depcnt; ++i)
		xdecref(self->d_depvec[i]);
}


PRIVATE NONNULL((1)) void KCALL
driver_enable_textrel(struct driver *__restrict self)
		THROWS(E_WOULDBLOCK) {
	ElfW(Half) i;
	bool did_lock_kernel = false;
	for (i = 0; i < self->d_phnum; ++i) {
		struct vm_node *node;
		if (self->d_phdr[i].p_type != PT_LOAD)
			continue; /* Not a load header */
		if (self->d_phdr[i].p_flags & PF_W)
			continue; /* Already writable */
		/* Must make this header writable! */
		if (!did_lock_kernel) {
			vm_kernel_treelock_write();
			did_lock_kernel = true;
		}
		node = vm_getnodeofaddress(&vm_kernel,
		                    (void *)(self->d_loadaddr + self->d_phdr[i].p_vaddr));
		assertf(node, "Missing node for driver %q's program segment #%" PRIu16 " mapped at %p",
		        self->d_name, (uint16_t)i, (void *)(self->d_loadaddr + self->d_phdr[i].p_vaddr));
		/* By simply adding write permissions here, a future #PF for nodes within this
		 * memory range will simply propagate this permission bit into the page directory. */
		ATOMIC_OR(node->vn_prot, VM_PROT_WRITE);
	}
	if (did_lock_kernel)
		vm_kernel_treelock_endwrite();
}

PRIVATE NONNULL((1)) void KCALL
driver_disable_textrel(struct driver *__restrict self)
		THROWS(E_WOULDBLOCK) {
	ElfW(Half) i;
	bool did_lock_kernel  = false;
	bool must_sync_kernel = false;
	for (i = 0; i < self->d_phnum; ++i) {
		struct vm_node *node;
		if (self->d_phdr[i].p_type != PT_LOAD)
			continue; /* Not a load header */
		if (self->d_phdr[i].p_flags & PF_W)
			continue; /* Already writable */
		/* Must make this header writable! */
		if (!did_lock_kernel) {
			vm_kernel_treelock_write();
			did_lock_kernel = true;
		}
		node = vm_getnodeofaddress(&vm_kernel,
		                           (void *)(self->d_loadaddr + self->d_phdr[i].p_vaddr));
		assertf(node, "Missing node for driver %q's program segment #%I16u mapped at %p",
		        self->d_name, (uint16_t)i,
		        (void *)(self->d_loadaddr + self->d_phdr[i].p_vaddr));
		if (ATOMIC_FETCHAND(node->vn_prot, ~VM_PROT_WRITE) & VM_PROT_WRITE) {
			u16 perm = 0;
			/* Must also update the kernel page directory. */
			if (self->d_phdr[i].p_flags & PF_R)
				perm |= PAGEDIR_MAP_FREAD;
			if (self->d_phdr[i].p_flags & PF_X)
				perm |= PAGEDIR_MAP_FEXEC;
			/* Re-map the node's datapart without write-permissions */
			vm_datapart_map_ram_autoprop(node->vn_part,
			                             vm_node_getstart(node),
			                             perm);
			must_sync_kernel = true;
		}
	}
	if (did_lock_kernel)
		vm_kernel_treelock_endwrite();
	if (must_sync_kernel)
		vm_supersyncall();
}


/* Destroy all places where the given driver may still be loaded
 * globally, including registered devices or object types, as well
 * as task callbacks and interrupt hooks, etc... */
INTDEF NONNULL((1)) void KCALL
driver_destroy_global_objects(struct driver *__restrict self);


/* Finalize the given driver.
 *  #1: Execute destructor callbacks.
 *  #2: Decref (and ATOMIC_XCH(NULL)) each module from the dependency vector.
 * NOTE: In case the driver is being finalized right now, wait for another
 *       thread doing the finalization to either complete, or abort.
 * @return: true:  Successfully finalized the driver.
 * @return: false: The driver had already been finalized (also a success-case). */
PUBLIC NONNULL((1)) bool KCALL
driver_finalize(struct driver *__restrict self)
		THROWS(E_WOULDBLOCK, E_BADALLOC, ...) {
	bool result = false;
	uintptr_t flags;
	assert(self != &kernel_driver);
again:
	flags = ATOMIC_READ(self->d_flags);
	if (!(flags & DRIVER_FLAG_FINALIZED)) {
		/* Must invoke finalizers/ wait for finalizers to finish. */
		if (flags & DRIVER_FLAG_FINALIZING) {
			/* Another thread is currently finalizing the driver. */
			if (self->d_initthread == THIS_TASK)
				return false; /* Ignore recursive call */
			task_yield();
			goto again;
		}
		if (((flags & (DRIVER_FLAG_DEPLOADING)) && !(flags & (DRIVER_FLAG_DEPLOADED))) ||
		    ((flags & (DRIVER_FLAG_RELOCATING)) && !(flags & (DRIVER_FLAG_RELOCATED))) ||
		    ((flags & (DRIVER_FLAG_INITIALIZING)) && !(flags & (DRIVER_FLAG_INITIALIZED)))) {
			/* Another thread is current initializing the driver. */
			if (self->d_initthread == THIS_TASK)
				goto do_start_finalization; /* Force-start finalization */
			task_yield();
			goto again;
		}
do_start_finalization:
		/* Start the finalization process. */
		if (!ATOMIC_CMPXCH_WEAK(self->d_flags, flags, flags | DRIVER_FLAG_FINALIZING))
			goto again;
		TRY {
			if likely(!(flags & DRIVER_FLAG_FINALIZED_C)) {
				/* Invoke destructor callbacks. */
				if (flags & DRIVER_FLAG_INITIALIZING)
					driver_invoke_destructors(self);
				/* Drop references from driver dependencies. */
				if (flags & DRIVER_FLAG_DEPLOADED)
					driver_decref_dependencies(self);
			}
			/* Acquire a sections lock so we can clear dangling sections. */
			TRY {
				/* Enable text-relocations for the driver, so the driver destructor
				 * will be able to unmap program sections as though it was Kernel-RAM. */
				driver_enable_textrel(self);

				/* Invoke dynamic driver-level callbacks for a driver being unloaded. */
				driver_destroy_global_objects(self);
				driver_finalized_callbacks(self);

				sync_write(&self->d_sections_lock);
			} EXCEPT {
				/* If this acquire failed, still indicate that callbacks were executed. */
				ATOMIC_OR(self->d_flags, DRIVER_FLAG_FINALIZED_C);
				RETHROW();
			}
			/* Clear locked sections. */
			driver_do_service_dead_sections(self);
			driver_do_clear_dang_sections(self);
			sync_endwrite(&self->d_sections_lock);
		} EXCEPT {
			/* Unset the is-finalizing flag to indicate that we've failed. */
			ATOMIC_AND(self->d_flags, ~DRIVER_FLAG_FINALIZING);
			RETHROW();
		}
		/* Indicate that finalization is complete! */
		assert(!(ATOMIC_READ(self->d_flags) & DRIVER_FLAG_FINALIZED));
		ATOMIC_OR(self->d_flags, DRIVER_FLAG_FINALIZED);
		decref_nokill(self); /* The reference held by the absence of the `DRIVER_FLAG_FINALIZED' flag */
		result = true;
	}
	return result;
}

/* Try to unload a driver module.
 * This function will:
 *   - invoke module finalizers (if they haven't been already)
 *   - if (!DRIVER_DELMOD_FLAG_NODEPEND):
 *         Search for other modules make use of `self' through
 *         dependencies and finalize all of them such that their
 *         dependency vectors can be cleared, including the
 *         contained references to `self'
 * @param: self:   The driver to try to unload.
 * @param: flags:  Set of `DRIVER_DELMOD_FLAG_*'
 * @return: true:  Successfully unloaded the driver and inherited the reference to `self'
 * @return: false: Failed to unload the driver (there are still unaccounted
 *                 references to it other than the reference given through `self') */
PUBLIC NONNULL((1)) bool KCALL
driver_try_decref_and_delmod(/*inherit(always)*/ REF struct driver *__restrict self,
                             unsigned int flags)
		THROWS(E_WOULDBLOCK, E_BADALLOC, ...) {
	TRY {
		if unlikely(self == &kernel_driver) {
			decref_nokill(self);
			return false; /* Not allowed! */
		}
		/* Always finalize the driver */
		driver_finalize(self);
		if (ATOMIC_CMPXCH(self->d_refcnt, 1, 0))
			goto success;
		if (!(flags & DRIVER_DELMOD_FLAG_NODEPEND)) {
			/* Search for, and delete modules that are using `self' */
			size_t j;
			REF struct driver_state *ds;
again_search_for_depending_drivers:
			ds = current_driver_state.get();
			for (j = 0; j < ds->ds_count; ++j) {
				struct driver *d;
				size_t i;
				d = ds->ds_drivers[j];
				if (d == self)
					continue;
				if (!tryincref(d))
					continue;
				/* Check if this driver has a dependency on us. */
				for (i = 0; i < d->d_depcnt; ++i) {
					if (d->d_depvec[i] != self)
						continue;
					TRY {
						/* Recursively delete this driver. */
						driver_try_decref_and_delmod(d, flags);
						/* Even if 1 depending driver could not be unloaded, keep on finalizing
						 * all other drivers to give the first one more time to come to terms
						 * with the fact that it is being unloaded.
						 * If everything works out, we'll still be able to destroy our driver
						 * in the final ATOMIC_CMPXCH() below. */
						goto find_next_dependent_driver;
					} EXCEPT {
						decref_unlikely(ds);
						RETHROW();
					}
				}
				decref_unlikely(d);
find_next_dependent_driver:
				;
			}
			/* If the set of loaded drivers has changed, then
			 * we have to check for more depending drivers. */
			if (ATOMIC_READ(current_driver_state.m_pointer) != ds) {
				decref_unlikely(ds);
				goto again_search_for_depending_drivers;
			}
			decref_unlikely(ds);
		}
	} EXCEPT {
		decref(self);
		RETHROW();
	}
	/* Check if we can get rid of the last reference */
	if (ATOMIC_CMPXCH(self->d_refcnt, 1, 0))
		goto success;
	if (flags & DRIVER_DELMOD_FLAG_FORCE) {
		refcnt_t remaining_references;
		remaining_references = ATOMIC_CMPXCH_VAL(self->d_refcnt, 1, 0);
		if unlikely(remaining_references == 1)
			goto success;
		/* Forcing the kernel to do this is really bad, and the only situation
		 * where us getting won't end up in the kernel crashing, is when the
		 * driver really did leak one of its references.
		 * Now granted, the driver may have intentionally leaked one of its
		 * references, but even still: this is bad... */
		printk(KERN_CRIT "[mod] Forcing unload driver %q with %" PRIuSIZ " unaccounted references\n",
		       self->d_filename ? self->d_filename : self->d_name,
		       remaining_references);
		ATOMIC_WRITE(self->d_refcnt, 0);
		goto success;
	}
	if (!(flags & DRIVER_DELMOD_FLAG_NONBLOCK)) {
		/* Wait for the driver to be destroyed. */
		task_connect(&self->d_destroyed); /* This is broadcast when the driver gets destroyed. */
		weakincref(self);                 /* Keep the driver control structure alive */
again_decref_and_waitfor_destroy:
		decref(self);                     /* We'll re-acquire this reference of something goes wrong. */
		TRY {
			task_waitfor();
		} EXCEPT {
			/* Drop the weak reference we took above. */
			weakdecref(self);
			RETHROW();
		}
		/* Check if we can still acquire references.
		 * This really shouldn't happen, since task_waitfor() shouldn't return
		 * sporadically (meaning that we should only get here if someone did a
		 * broadcast over `d_destroyed'), but just to be safe, do the check for
		 * ourselves. */
		if unlikely(tryincref(self)) {
			TRY {
				task_connect(&self->d_destroyed); /* This is broadcast when the driver gets destroyed. */
			} EXCEPT {
				decref_unlikely(self);
				RETHROW();
			}
			goto again_decref_and_waitfor_destroy;
		}
		/* Yes: the driver is dead!
		 * Now all that's left is the weak reference we still have from above. */
		weakdecref(self);
		return true;
	}
	return false;
success:
	/* Successfully caused the reference counter to drop to zero! */
	driver_destroy(self);
	return true;
}



/* Unload a driver from the kernel core.
 * @param: driver_name: The name of the driver, or its
 *                      filename (when the first character is `/')
 * @param: flags: Set of `DRIVER_DELMOD_FLAG_*'
 * @return: * :   One of `DRIVER_DELMOD_*' */
PUBLIC NONNULL((1)) unsigned int KCALL
driver_delmod(USER CHECKED char const *driver_name,
              unsigned int flags)
		THROWS(E_WOULDBLOCK, E_BADALLOC, ...) {
	REF struct driver_state *ds;
	size_t i;
	char first_char;
	first_char = ATOMIC_READ(driver_name[0]);
	COMPILER_BARRIER();
	ds = current_driver_state.get();
	for (i = 0; i < ds->ds_count; ++i) {
		int compare;
		struct driver *d;
		d = ds->ds_drivers[i];
		if unlikely(!tryincref(d))
			continue; /* Dead driver */
		TRY {
			if (first_char == '/') {
				if (!d->d_filename)
					continue;
				compare = strcmp(d->d_filename, driver_name);
			} else {
				compare = strcmp(d->d_name, driver_name);
			}
		} EXCEPT {
			decref_unlikely(d);
			decref_unlikely(ds);
			RETHROW();
		}
		if (compare == 0) {
			bool success;
			/* Found it! */
			decref_unlikely(ds);
			success = driver_try_decref_and_delmod(d, flags);
			if (success)
				return DRIVER_DELMOD_SUCCESS;
			return DRIVER_DELMOD_INUSE;
		}
		decref_unlikely(d);
	}
	decref_unlikely(ds);
	return DRIVER_DELMOD_UNKNOWN;
}

PUBLIC NONNULL((1)) unsigned int KCALL
driver_delmod_inode(struct inode *__restrict driver_node,
                    unsigned int flags)
		THROWS(E_WOULDBLOCK, E_BADALLOC, ...) {
	REF struct driver_state *ds;
	size_t i;
	ds = current_driver_state.get();
	for (i = 0; i < ds->ds_count; ++i) {
		bool success;
		struct driver *d;
		d = ds->ds_drivers[i];
		if unlikely(!tryincref(d))
			continue; /* Dead driver */
		if (d->d_file != driver_node) {
			decref_unlikely(d);
			continue;
		}
		/* Found it! */
		decref_unlikely(ds);
		success = driver_try_decref_and_delmod(d, flags);
		if (success)
			return DRIVER_DELMOD_SUCCESS;
		return DRIVER_DELMOD_INUSE;
	}
	decref_unlikely(ds);
	return DRIVER_DELMOD_UNKNOWN;
}



LOCAL ATTR_PURE WUNUSED u32 KCALL
elf_symhash(USER CHECKED char const *name) {
	u32 h = 0;
	while (*name) {
		u32 g;
		h = (h << 4) + *name++;
		g = h & 0xf0000000;
		if (g)
			h ^= g >> 24;
		h &= ~g;
	}
	return h;
}

PRIVATE char const empty_argument_string[1] = { 0 };

PRIVATE NONNULL((1)) bool KCALL
driver_special_symbol(struct driver *__restrict self,
                      /*in*/ USER CHECKED char const *name,
                      /*out*/ void **psymbol_addr,
                      /*out*/ size_t *psymbol_size)
		THROWS(E_SEGFAULT) {
	if (name[0] == 'd' && name[1] == 'r' &&
	    name[2] == 'v' && name[3] == '_') {
		name += 4;
		switch (name[0]) {

		case 's':
			if (strcmp(name + 1, "elf") == 0) {
				if (psymbol_addr)
					*psymbol_addr = self;
				if (psymbol_size)
					*psymbol_size = (offsetof(struct driver, d_phdr) +
					                 self->d_phnum * sizeof(ElfW(Phdr)));
				return true;
			}
			if (strcmp(name + 1, "tart") == 0) {
				if (psymbol_addr)
					*psymbol_addr = (void *)self->d_loadstart;
				if (psymbol_size)
					*psymbol_size = 0;
				return true;
			}
			break;

		case 'e':
			if (strcmp(name + 1, "nd") == 0) {
				if (psymbol_addr)
					*psymbol_addr = (void *)self->d_loadend;
				if (psymbol_size)
					*psymbol_size = 0;
				return true;
			}
			break;

		case 'l':
			if (strcmp(name + 1, "oadaddr") == 0) {
				if (psymbol_addr)
					*psymbol_addr = (void *)self->d_loadaddr;
				if (psymbol_size)
					*psymbol_size = 0;
				return true;
			}
			break;

		case 'n':
			if (strcmp(name + 1, "ame") == 0) {
				if (psymbol_addr)
					*psymbol_addr = (void *)self->d_name;
				if (psymbol_size)
					*psymbol_size = (strlen(self->d_name) + 1) * sizeof(char);
				return true;
			}
			break;

		case 'f':
			if (strcmp(name + 1, "ilename") == 0) {
				if (psymbol_addr)
					*psymbol_addr = (void *)&self->d_filename;
				if (psymbol_size)
					*psymbol_size = sizeof(char *);
				return true;
			}
			if (strcmp(name + 1, "ile") == 0) {
				if (psymbol_addr)
					*psymbol_addr = (void *)&self->d_file;
				if (psymbol_size)
					*psymbol_size = sizeof(REF struct regular_node *);
				return true;
			}
			break;

		case 'c':
			if (strcmp(name + 1, "ommandline") == 0) {
				if (psymbol_addr)
					*psymbol_addr = (void *)self->d_cmdline;
				if (psymbol_size)
					*psymbol_size = self->d_argc
					                ? (size_t)((strend(self->d_argv[self->d_argc - 1]) + 1) -
					                           (self->d_cmdline)) *
					                  sizeof(char)
					                : sizeof(char);
				return true;
			}
			break;

		case 'a':
			if (name[1] != 'r')
				break;
			if (name[2] != 'g')
				break;
			if (name[3] == 'c' && name[4] == '\0') {
				if (psymbol_addr)
					*psymbol_addr = (void *)&self->d_argc;
				if (psymbol_size)
					*psymbol_size = sizeof(self->d_argc);
				return true;
			}
			if (name[3] == 'v' && name[4] == '\0') {
				if (psymbol_addr)
					*psymbol_addr = (void *)self->d_argv;
				if (psymbol_size)
					*psymbol_size = (self->d_argc + 1) * sizeof(char *);
				return true;
			}
			if (name[3] == '_') {
				size_t i, namelen;
				name += 4;
				namelen = strlen(name);
				for (i = 0; i < self->d_argc; ++i) {
					if (memcmp(self->d_argv[i], name, namelen * sizeof(char)) == 0 &&
					    self->d_argv[i][namelen] == '=') {
						/* Found it! */
						char const *value = self->d_argv[i] + namelen + 1;
						if (psymbol_addr)
							*psymbol_addr = (void *)value;
						if (psymbol_size)
							*psymbol_size = (strlen(value) + 1) * sizeof(char);
						return true;
					}
				}
				/* Unknown option */
				if (psymbol_addr)
					*psymbol_addr = (void *)empty_argument_string;
				if (psymbol_size)
					*psymbol_size = sizeof(char);
				return true;
			}
			if (name[3] == 'p' && name[4] == '_') {
				size_t i;
				name += 5;
				for (i = 0; i < self->d_argc; ++i) {
					char const *opt = self->d_argv[i];
					if (strcmp(opt, name) == 0) {
						/* Found it! */
						if (psymbol_addr)
							*psymbol_addr = (void *)opt;
						if (psymbol_size)
							*psymbol_size = (strlen(opt) + 1) * sizeof(char);
						return true;
					}
				}
				/* Unknown option */
				if (psymbol_addr)
					*psymbol_addr = (void *)NULL;
				if (psymbol_size)
					*psymbol_size = 0;
				return true;
			}
			break;

		default: break;
		}
	}
	return false;
}

struct kernel_syment {
	char const *ks_name; /* [0..1] Symbol name (NULL for sentinel) */
	void       *ks_addr; /* Symbol address */
	u32         ds_size; /* Symbol size */
	u32         ds_hash; /* Symbol hash (s.a. `elf_symhash()') */
};
struct kernel_symtab {
	uintptr_t            ds_mask;       /* Hash mask. */
	struct kernel_syment ds_list[1024]; /* Symbol map. */
};

/* The kernel symbol table (containing everything marked as PUBLIC) */
INTDEF struct kernel_symtab kernel_symbol_table;



PRIVATE WUNUSED NONNULL((1, 4)) bool KCALL
kernel_symbol(/*in*/USER CHECKED char const *name,
              /*out*/ void **psymbol_addr,
              /*out*/ size_t *psymbol_size,
              /*in|out*/ uintptr_t *__restrict phash_elf)
		THROWS(E_SEGFAULT) {
	uintptr_t hash = *phash_elf;
	uintptr_t i, perturb;
	if (hash == DRIVER_SYMBOL_HASH_UNSET)
		hash = *phash_elf = elf_symhash(name);
	perturb = i = hash & kernel_symbol_table.ds_mask;
	/* NOTE: Changes to this algorithm must be mirrored in /src/kernel/core/.sources */
	for (;; i = ((i << 2) + i + perturb + 1), perturb >>= 5) {
		uintptr_t index;
		index = i & kernel_symbol_table.ds_mask;
		if (!kernel_symbol_table.ds_list[index].ks_name)
			break; /* Sentinel */
		if (kernel_symbol_table.ds_list[index].ds_hash != hash)
			continue; /* Different hash */
		if (strcmp(kernel_symbol_table.ds_list[index].ks_name, name) != 0)
			continue; /* Different name */
		/* Found it! */
		if (psymbol_addr)
			*psymbol_addr = kernel_symbol_table.ds_list[index].ks_addr;
		if (psymbol_size)
			*psymbol_size = kernel_symbol_table.ds_list[index].ds_size;
		return true;
	}
	return false;
}

PRIVATE WUNUSED char const *
NOTHROW(KCALL kernel_symbol_at)(uintptr_t addr,
                                uintptr_t *psymbol_addr,
                                size_t *psymbol_size) {
	uintptr_t i;
	for (i = 0; i <= kernel_symbol_table.ds_mask; ++i) {
		uintptr_t end;
		if (kernel_symbol_table.ds_list[i].ks_addr > (void *)addr)
			continue;
		end = (uintptr_t)kernel_symbol_table.ds_list[i].ks_addr +
		      kernel_symbol_table.ds_list[i].ds_size;
		if (addr >= end)
			continue;
		/* Found it! */
		if (psymbol_addr)
			*psymbol_addr = (uintptr_t)kernel_symbol_table.ds_list[i].ks_addr;
		if (psymbol_size)
			*psymbol_size = kernel_symbol_table.ds_list[i].ds_size;
		return kernel_symbol_table.ds_list[i].ks_name;
	}
	return NULL;
}


/* Simplified variant of `driver_symbol_ex()'
 * This function returns `NULL' on error, however thus also
 * creates ambiguity for symbols defined as SHN_ABS:0. */
PUBLIC WUNUSED NONNULL((1)) void *KCALL
driver_symbol(struct driver *__restrict self,
              /*in*/ USER CHECKED char const *name,
              /*out*/ size_t *psymbol_size)
		THROWS(E_SEGFAULT, ...) {
	void *result;
	uintptr_t hash_elf, hash_gnu;
	hash_elf = hash_gnu = DRIVER_SYMBOL_HASH_UNSET;
	if unlikely(!driver_symbol_ex(self,
	                              name,
	                              &result,
	                              psymbol_size,
	                              &hash_elf,
	                              &hash_gnu)) {
		result = NULL;
	}
	return result;
}

/* Lookup a symbol exported from a given driver `self'
 * HINT: This function will also resolve special driver symbols
 * @return: true:  The symbol was found.
 * @return: false: The symbol could not be found. */
PUBLIC WUNUSED NONNULL((1, 5, 6)) bool KCALL
driver_symbol_ex(struct driver *__restrict self,
                 /*in*/ USER CHECKED char const *name,
                 /*out*/ void **psymbol_addr,
                 /*out*/ size_t *psymbol_size,
                 /*in|out*/ uintptr_t *__restrict phash_elf,
                 /*in|out*/ uintptr_t *__restrict phash_gnu)
		THROWS(E_SEGFAULT, ...) {
	ElfW(Sym) const *elf_sym;
	/* Check for special symbols in relation to this driver. */
	if (driver_special_symbol(self,
	                          name,
	                          psymbol_addr,
	                          psymbol_size))
		return true;
	if (self == &kernel_driver) {
		/* Special case for the kernel core driver. */
		return kernel_symbol(name,
		                     psymbol_addr,
		                     psymbol_size,
		                     phash_elf);
	}

	/* Check for symbols exported by this driver. */
	elf_sym = driver_local_symbol(self,
	                              name,
	                              phash_elf,
	                              phash_gnu);
	if (elf_sym &&
	    elf_sym->st_shndx != SHN_UNDEF) {
		if (psymbol_addr) {
			uintptr_t addr = elf_sym->st_value;
			if (elf_sym->st_shndx != SHN_ABS)
				addr += self->d_loadaddr;
			if (ELFW(ST_TYPE)(elf_sym->st_info) == STT_GNU_IFUNC ||
			    ELFW(ST_TYPE)(elf_sym->st_info) == STT_KOS_IDATA)
				addr = (*(uintptr_t(*)(void))addr)();
			*psymbol_addr = (void *)addr;
		}
		if (psymbol_size)
			*psymbol_size = elf_sym->st_size;
		return true;
	}
	return false;
}


/* Check if the given driver `self' is exporting a symbol that
 * contains the given `driver_relative_address', or it exports a symbol
 * with an undefined size that begins before `driver_relative_address',
 * but isn't defined within the SHN_ABS section, nor is followed by another
 * symbol that does have a defined size value.
 * NOTE: This function cannot be used to reverse special driver symbols
 * WARNING: This operation in O(n) | n = number of symbols exported by `self'
 * @return: * :                      The NUL-terminated name of the symbol.
 *                                   This pointer is valid as long as `self' isn't unloaded.
 * @return: NULL:                    No public symbol is defined for `driver_relative_address'
 *                                   Note however that the associated symbol may not necessarily
 *                                   have been made public by the associated driver. In this case,
 *                                   it may be possible to determine the symbol name by looking at
 *                                   the driver's debug data (s.a. `<libdebuginfo/addr2line.h>')
 * @param: driver_relative_address:  A module-relative pointer who's associated symbol should be located.
 * @param: psymbol_relative_address: When non-NULL, store the module-relative base address of the found symbol here.
 * @param: psymbol_size:             When non-NULL, store the size of the symbol here, or 0 if undefined. */
PUBLIC WUNUSED NONNULL((1)) char const *
NOTHROW(KCALL driver_symbol_at)(struct driver *__restrict self,
                                uintptr_t driver_relative_address,
                                uintptr_t *psymbol_relative_address,
                                size_t *psymbol_size) {
	ElfW(Sym) const *symbol;
	if (self == &kernel_driver) {
		/* Special case for the kernel core driver. */
		return kernel_symbol_at(driver_relative_address,
		                        psymbol_relative_address,
		                        psymbol_size);
	}
	symbol = driver_local_symbol_at(self, driver_relative_address);
	if (!symbol)
		return NULL;
	assert(symbol->st_shndx != SHN_ABS);
	assert(symbol->st_shndx != SHN_UNDEF);
	if (psymbol_relative_address)
		*psymbol_relative_address = symbol->st_value;
	if (psymbol_size)
		*psymbol_size = symbol->st_size;
	assert(symbol->st_name < (size_t)(self->d_dynstr_end - self->d_dynstr));
	return self->d_dynstr + symbol->st_name;
}




/* Same as `driver_symbol_at()', but returns the ELF symbol
 * WARNING: This function cannot be used with `&kernel_driver', as
 *          the kernel core itself implements a custom protocol for
 *          specifying which variables are exported. */
PUBLIC WUNUSED NONNULL((1)) ElfW(Sym) const *
NOTHROW(KCALL driver_local_symbol_at)(struct driver *__restrict self,
                                      uintptr_t driver_relative_address) {
	size_t i, count;
	ElfW(Sym) const *result;
	uintptr_t prev_symbol_end;
	count = self->d_dynsym_cnt;
	/* First pass: Search for a symbol that contains the given address exactly. */
	for (i = 0; i < count; ++i) {
		result = &self->d_dynsym_tab[i];
		if (result->st_shndx == SHN_UNDEF ||
		    result->st_shndx == SHN_ABS)
			continue;
		if (result->st_value > driver_relative_address)
			continue;
		if (result->st_value == driver_relative_address)
			return result; /* Exact match */
		if (result->st_size != 0) {
			/* Symbol has a defined size value. */
			if (driver_relative_address < (result->st_value + result->st_size))
				return result; /* The given address is contained within this one. */
		}
	}
	/* Second pass: Search for the nearest open-ended symbol defined below `'driver_relative_address */
	prev_symbol_end = 0;
	result = NULL;
	for (i = 0; i < count; ++i) {
		ElfW(Sym) const *sym;
		sym = &self->d_dynsym_tab[i];
		if (sym->st_shndx == SHN_UNDEF ||
		    sym->st_shndx == SHN_ABS)
			continue;
		if (sym->st_value > driver_relative_address)
			continue;
		if (result->st_size != 0) {
			uintptr_t symend;
			symend = result->st_value + result->st_size;
			assertf(symend <= driver_relative_address,
			        "Otherwise, the symbol would be a perfect match, which "
			        "we would have already detected during the first pass");
			if (symend > prev_symbol_end) {
				/* Closer matching symbol. */
				prev_symbol_end = symend;
				result          = NULL; /* Closed end */
			}
		} else if (sym->st_value > prev_symbol_end) {
			/* Open-ended symbol above previous symbol.
			 * Use this one unless we find another one that's closer. */
			prev_symbol_end = sym->st_value;
			result          = sym;
		}
	}
	assert(!result || (result->st_shndx != SHN_UNDEF &&
	                   result->st_shndx != SHN_ABS));
	assert(!result || result->st_size == 0);
	assert(!result || result->st_value < driver_relative_address);
	return result;
}



/* Lookup a locally defined ELF symbol within `self'
 * WARNING: This function cannot be used with `&kernel_driver', as
 *          the kernel core itself implements a custom protocol for
 *          specifying which variables are exported. */
PUBLIC WUNUSED NONNULL((1, 3, 4)) ElfW(Sym) const *KCALL
driver_local_symbol(struct driver *__restrict self,
                    /*in*/ USER CHECKED char const *name,
                    /*in|out*/ uintptr_t *__restrict phash_elf,
                    /*in|out*/ uintptr_t *__restrict phash_gnu)
		THROWS(E_SEGFAULT) {
	ElfW(Sym) const *result;
	ElfW(HashTable) const *elf_ht;
	if ((elf_ht = self->d_hashtab) != NULL) {
		ElfW(Word) const *ht_chains;
		ElfW(Word) max_attempts, chain;
		uintptr_t hash = *phash_elf;
		if (hash == DRIVER_SYMBOL_HASH_UNSET)
			hash = *phash_elf = elf_symhash(name);
		if unlikely(!elf_ht->ht_nbuckts || !elf_ht->ht_nchains) {
			goto nosym_no_elf_ht;
		}
		max_attempts = elf_ht->ht_nchains;
		ht_chains    = elf_ht->ht_table + elf_ht->ht_nbuckts;
		chain        = elf_ht->ht_table[hash % elf_ht->ht_nbuckts];
		do {
			if unlikely(chain == STN_UNDEF)
				break; /* End of chain. */
			if unlikely(chain >= elf_ht->ht_nchains)
				goto nosym_no_elf_ht; /* Corrupted hash-table */
			result = self->d_dynsym_tab + chain;
			assert(result->st_name < (size_t)(self->d_dynstr_end - self->d_dynstr));
			if (strcmp(name, self->d_dynstr + result->st_name) == 0)
				return result; /* Found it! */
			/* Load the next chain entry. */
			chain = ht_chains[chain];
		} while likely(--max_attempts);
		goto nosym;
	}
	/* TODO: GNU hash table support */
	(void)phash_gnu;
nosym:
	return NULL;
nosym_no_elf_ht:
	self->d_hashtab = NULL;
	goto nosym;
}


/* Lock a named section of a given driver into
 * memory and return a descriptor for that section.
 * @return: * :   Reference to the section descriptor.
 *                This reference must be released with `decref(return)'
 * @return: NULL: The given driver `self' doesn't contain any section `name' */
PUBLIC WUNUSED NONNULL((1)) REF struct driver_section *KCALL
driver_section_lock(struct driver *__restrict self,
                    USER CHECKED char const *name,
                    unsigned int flags)
		THROWS(E_SEGFAULT, E_BADALLOC) {
	ElfW(Shdr) const *sect;
	size_t index;
	REF struct driver_section *result;
	assertf(!(flags & ~(DRIVER_SECTION_LOCK_FINDEX | DRIVER_SECTION_LOCK_FNODATA)),
	        "Invalid flags %#x passed to `driver_section_lock()'", flags);
	assertf(self != NULL, "Invalid module handle");
	if (flags & DRIVER_SECTION_LOCK_FINDEX) {
		sect = driver_getshdrs(self);
		if unlikely(!sect)
			goto err;
		if unlikely((uintptr_t)name >= self->d_shnum)
			goto err;
		sect += (uintptr_t)name;
	} else {
		sect = driver_getsection(self, name);
		if unlikely(!sect)
			goto err;
	}
	assert(sect >= self->d_shdr);
	assert(sect < self->d_shdr + self->d_shnum);
	index = (size_t)(sect - self->d_shdr);
again_lock_sections:
	if (driver_must_service_dead_sections(self)) {
		sync_write(&self->d_sections_lock);
		driver_do_service_dead_sections(self);
		sync_downgrade(&self->d_sections_lock);
	} else {
		sync_read(&self->d_sections_lock);
		if unlikely(driver_must_service_dead_sections(self)) {
			sync_endread(&self->d_sections_lock);
			goto again_lock_sections;
		}
	}
	if (!self->d_sections) {
		struct driver_section **sec_vec;
		/* Must allocate the initial sections vector. */
		sync_endread(&self->d_sections_lock);
		sec_vec = (struct driver_section **)kmalloc(self->d_shnum * sizeof(struct driver_section *),
		                                            GFP_CALLOC | GFP_PREFLT);
		TRY {
			sync_write(&self->d_sections_lock);
		} EXCEPT {
			kfree(sec_vec);
			RETHROW();
		}
		driver_do_service_dead_sections(self);
		COMPILER_READ_BARRIER();
		if likely(!self->d_sections) {
			self->d_sections = sec_vec;
		} else {
			sync_endwrite(&self->d_sections_lock);
			kffree(sec_vec, GFP_CALLOC);
			COMPILER_READ_BARRIER();
			goto again_lock_sections;
		}
		sync_downgrade(&self->d_sections_lock);
	}
again_read_section:
	result = self->d_sections[index];
	if (!result || !tryincref(result)) {
		/* Must allocate a descriptor for this section. */
		sync_endread(&self->d_sections_lock);
		if unlikely(driver_must_service_dead_sections(self)) {
			sync_write(&self->d_sections_lock);
			driver_do_service_dead_sections(self);
			sync_endwrite(&self->d_sections_lock);
		}
		result = (REF struct driver_section *)kmalloc(sizeof(struct driver_section),
		                                              GFP_PREFLT);
		result->ds_size    = sect->sh_size;
		result->ds_entsize = sect->sh_entsize;
		result->ds_link    = sect->sh_link;
		result->ds_info    = sect->sh_info;
		result->ds_flags   = sect->sh_flags;
		result->ds_refcnt  = 1;
		result->ds_module  = incref(self);
		result->ds_index   = index;
		result->ds_cdata   = (void *)-1;
		result->ds_csize   = 0;
#ifndef NDEBUG
#if __SIZEOF_POINTER__ > 4
		memset(result->__ds_pad, 0xcc, sizeof(result->__ds_pad));
#endif /* __SIZEOF_POINTER__ > 4 */
		memset(&result->ds_dangling, 0xcc, sizeof(result->ds_dangling));
#endif /* !NDEBUG */
		if (sect->sh_flags & SHF_ALLOC) {
			/* Section is already allocated in member. */
			result->ds_data      = (void *)(self->d_loadaddr + sect->sh_addr);
			result->ds_sectflags = DRIVER_DLSECTION_FNORMAL;
		} else {
			result->ds_data      = (void *)-1;
			result->ds_sectflags = DRIVER_DLSECTION_FOWNED;
		}
		TRY {
			sync_write(&self->d_sections_lock);
		} EXCEPT {
			decref_nokill(self); /* Reference from `result->ds_module' */
			kfree(result);
			RETHROW();
		}
		driver_do_service_dead_sections(self);
		if likely(!self->d_sections[index]) {
			self->d_sections[index] = result;
		} else {
			/* Race condition: The section was already allocated in a different thread. */
			sync_endwrite(&self->d_sections_lock);
			kfree(result);
again_lock_sections_after_free_result:
			if (driver_must_service_dead_sections(self)) {
				sync_write(&self->d_sections_lock);
				driver_do_service_dead_sections(self);
				sync_downgrade(&self->d_sections_lock);
			} else {
				sync_read(&self->d_sections_lock);
				if unlikely(driver_must_service_dead_sections(self)) {
					sync_endread(&self->d_sections_lock);
					goto again_lock_sections_after_free_result;
				}
			}
			goto again_read_section;
		}
		sync_downgrade(&self->d_sections_lock);
	}
	sync_endread(&self->d_sections_lock);
	if (driver_must_service_dead_sections(self)) {
		sync_write(&self->d_sections_lock);
		driver_do_service_dead_sections(self);
		sync_endwrite(&self->d_sections_lock);
	}
	if (result->ds_data == (void *)-1 &&
	    !(flags & DRIVER_SECTION_LOCK_FNODATA) &&
	    (result->ds_sectflags & DRIVER_DLSECTION_FOWNED)) {
		void *base;
		size_t num_pages;
		/* Load section into memory. */
		num_pages = CEILDIV(sect->sh_size, PAGESIZE);
		TRY {
			struct regular_node *file;
			file = driver_getfile(self);
			if unlikely(!file) {
				/* Failed to load the driver's file. */
				decref(result);
				return NULL;
			}
			base = vpage_alloc(num_pages,
			                   1,
			                   GFP_PREFLT);
			TRY {
				inode_readallk(file,
				               base,
				               sect->sh_size,
				               (pos_t)sect->sh_offset);
			} EXCEPT {
				vpage_free(base, num_pages);
				RETHROW();
			}
		} EXCEPT {
			decref(result);
			RETHROW();
		}
		if unlikely(!ATOMIC_CMPXCH(result->ds_data, (void *)-1, base))
			vpage_free(base, num_pages);
	}
	return result;
err:
	return NULL;
}

/* Same as `driver_section_lock()', but return NULL, rather than throwing an exception. */
PUBLIC WUNUSED NONNULL((1)) REF struct driver_section *
NOTHROW(KCALL driver_section_lock_nx)(struct driver *__restrict self,
                                      USER CHECKED char const *name,
                                      unsigned int flags) {
	struct exception_info exinfo;
	REF struct driver_section *result;
	memcpy(&exinfo, error_info(), sizeof(struct exception_info));
	TRY {
		result = driver_section_lock(self, name, flags);
	} EXCEPT {
		goto restore_except;
	}
	return result;
restore_except:
	memcpy(error_info(), &exinfo, sizeof(struct exception_info));
	return NULL;
}




/* Try to lookup a driver stored at a given address.
 * If no such driver exists, return NULL */
PUBLIC NOBLOCK WUNUSED REF struct driver *
NOTHROW(FCALL driver_at_address)(void const *static_pointer) {
	REF struct driver_state *ds;
	size_t i;
	REF struct driver *result;
	/* Check for special case: The kernel core driver. */
	if (static_pointer >= (void *)__kernel_start &&
	    static_pointer < (void *)kernel_driver.d_loadend)
		return incref(&kernel_driver);
	/* Check for special case: The pointer isn't located in kernel-space. */
	if (!ADDR_ISKERN((uintptr_t)static_pointer))
		return NULL;
	ds = current_driver_state.get();
	for (i = 0; i < ds->ds_count; ++i) {
		size_t j;
		result = ds->ds_drivers[i];
		if unlikely(!tryincref(result))
			continue; /* Dead driver. */
		if (static_pointer < (void *)result->d_loadstart) {
decref_result_and_continue:
			decref_unlikely(result);
			continue;
		}
		if (static_pointer >= (void *)result->d_loadend)
			goto decref_result_and_continue;
		/* Make sure that `static_pointer' maps to some program segment. */
		for (j = 0; j < result->d_phnum; ++j) {
			uintptr_t segment_base;
			if (result->d_phdr[j].p_type != PT_LOAD)
				goto decref_result_and_continue;
			segment_base = result->d_loadaddr + result->d_phdr[j].p_vaddr;
			if ((uintptr_t)static_pointer < segment_base)
				goto decref_result_and_continue;
			if ((uintptr_t)static_pointer >= segment_base + result->d_phdr[j].p_memsz)
				goto decref_result_and_continue;
			goto done;
		}
	}
	result = NULL;
done:
	decref_unlikely(ds);
	return result;
}

/* Try to lookup a driver with a given `driver_name'.
 * If no such driver exists, return NULL */
PUBLIC WUNUSED REF struct driver *
(FCALL driver_with_name)(USER CHECKED char const *driver_name) THROWS(E_SEGFAULT) {
	REF struct driver_state *ds;
	size_t i;
	REF struct driver *result;
	/* Check for special case: The kernel core driver. */
	if (strcmp(kernel_driver.d_name, driver_name) == 0)
		return incref(&kernel_driver);
	ds = current_driver_state.get();
	FINALLY_DECREF_UNLIKELY(ds);
	for (i = 0; i < ds->ds_count; ++i) {
		bool is_a_match;
		result = ds->ds_drivers[i];
		if unlikely(!tryincref(result))
			continue; /* Dead driver. */
		TRY {
			is_a_match = strcmp(result->d_name, driver_name) == 0;
		} EXCEPT {
			decref_unlikely(result);
			RETHROW();
		}
		if (is_a_match)
			goto done;
		decref_unlikely(result);
	}
	result = NULL;
done:
	return result;
}

PUBLIC WUNUSED REF struct driver *
(FCALL driver_with_namel)(USER CHECKED char const *driver_name,
                          size_t driver_name_len) THROWS(E_SEGFAULT) {
	REF struct driver_state *ds;
	size_t i;
	REF struct driver *result;
	/* Check for special case: The kernel core driver. */
	if (memcmp(kernel_driver.d_name, driver_name, driver_name_len * sizeof(char)) == 0 &&
	    kernel_driver.d_name[driver_name_len] == '\0')
		return incref(&kernel_driver);
	ds = current_driver_state.get();
	FINALLY_DECREF_UNLIKELY(ds);
	for (i = 0; i < ds->ds_count; ++i) {
		bool is_a_match;
		result = ds->ds_drivers[i];
		if unlikely(!tryincref(result))
			continue; /* Dead driver. */
		TRY {
			is_a_match = strlen(result->d_name) == driver_name_len &&
			             memcmp(result->d_name, driver_name, driver_name_len * sizeof(char)) == 0;
		} EXCEPT {
			decref_unlikely(result);
			RETHROW();
		}
		if (is_a_match)
			goto done;
		decref_unlikely(result);
	}
	result = NULL;
done:
	return result;
}

PUBLIC WUNUSED REF struct driver *
(FCALL driver_with_filename)(USER CHECKED char const *driver_filename) THROWS(E_SEGFAULT) {
	REF struct driver_state *ds;
	size_t i;
	REF struct driver *result;
	/* Check for special case: The kernel core driver. */
	if (strcmp(kernel_driver.d_filename, driver_filename) == 0)
		return incref(&kernel_driver);
	ds = current_driver_state.get();
	FINALLY_DECREF_UNLIKELY(ds);
	for (i = 0; i < ds->ds_count; ++i) {
		bool is_a_match;
		char const *filename;
		result   = ds->ds_drivers[i];
		if unlikely(!tryincref(result))
			continue; /* Dead driver */
		filename = ATOMIC_READ(result->d_filename);
		if (!filename) {
			/* Filename not loaded. */
			decref_unlikely(result);
			continue;
		}
		TRY {
			is_a_match = strcmp(filename, driver_filename) == 0;
		} EXCEPT {
			decref_unlikely(result);
			RETHROW();
		}
		if (is_a_match)
			goto done;
		decref_unlikely(result);
	}
	result = NULL;
done:
	return result;
}

PUBLIC NOBLOCK WUNUSED NONNULL((1)) REF struct driver *
NOTHROW(FCALL driver_with_file)(struct regular_node *__restrict driver_file) {
	REF struct driver_state *ds;
	size_t i;
	REF struct driver *result;
	/* Check for special case: The kernel core driver. */
	if (kernel_driver.d_file == driver_file)
		return incref(&kernel_driver);
	ds = current_driver_state.get();
	for (i = 0; i < ds->ds_count; ++i) {
		result = ds->ds_drivers[i];
		if unlikely(!tryincref(result))
			continue; /* Dead driver. */
		if (result->d_file == driver_file)
			goto done;
		decref_unlikely(result);
	}
	result = NULL;
done:
	decref_unlikely(ds);
	return result;
}








#define THROW_FAULTY_ELF_ERROR(...)           \
	THROW(E_NOT_EXECUTABLE_FAULTY,            \
	      E_NOT_EXECUTABLE_FAULTY_FORMAT_ELF, \
	      __VA_ARGS__)


#define HINT_ADDR(x, y) x
#define HINT_MODE(x, y) y
#define HINT_GETADDR(x) HINT_ADDR x
#define HINT_GETMODE(x) HINT_MODE x


/* kmalloc() a string containing the absolute filename of `pth' + `dent' */
PRIVATE ATTR_MALLOC WUNUSED NONNULL((1, 2)) char *KCALL
print_kernel_path_malloc(struct path *__restrict pth,
                         struct directory_entry *__restrict dent) {
	char *buf;
	size_t buflen, reqlen;
	buflen = 128;
	buf = (char *)kmalloc((buflen + 1) * sizeof(char),
	                      GFP_LOCKED | GFP_PREFLT);
	TRY {
again_print_ent:
		reqlen = path_sprintentex(buf,
		                          buflen,
		                          pth,
		                          dent->de_name,
		                          dent->de_namelen,
		                          FS_MODE_FNORMAL,
		                          &vfs_kernel);
		buf = (char *)krealloc(buf, (reqlen + 1) * sizeof(char),
		                       GFP_LOCKED | GFP_PREFLT);
		if (reqlen > buflen) {
			buflen = reqlen;
			goto again_print_ent;
		}
		buf[reqlen] = '\0';
	} EXCEPT {
		kfree(buf);
		RETHROW();
	}
	return buf;
}


PRIVATE NONNULL((1)) void KCALL
driver_parse_cmdline(struct driver *__restrict self,
                     USER CHECKED char const *cmdline)
		THROWS(E_BADALLOC, E_SEGFAULT, E_WOULDBLOCK) {
	size_t cmdline_length;
	char *cmdline_copy;
	cmdline_length = strlen(cmdline);
	cmdline_copy = (char *)kmalloc((cmdline_length + 2) * sizeof(char),
	                               GFP_LOCKED | GFP_PREFLT);
	TRY {
		memcpy(cmdline_copy, cmdline, cmdline_length, sizeof(char));
		/* Add a double-NUL terminator to allow the commandline
		 * to always be interpreted into a NUL-NUL string-list */
		cmdline_copy[cmdline_length + 0] = '\0';
		cmdline_copy[cmdline_length + 1] = '\0';
		/* Split the commandline through use of libcmdline */
		self->d_argv = cmdline_decode_argv(cmdline_copy, &self->d_argc,
		                                   GFP_LOCKED | GFP_PREFLT);
	} EXCEPT {
		kfree(cmdline_copy);
		RETHROW();
	}
	self->d_cmdline = cmdline_copy;
}




PRIVATE NONNULL((1)) void KCALL
driver_do_load_dependencies(struct driver *__restrict self)
		THROWS(E_NOT_EXECUTABLE, E_FSERROR, E_BADALLOC, E_WOULDBLOCK) {
	size_t i, dep_i = 0;
	REF struct driver *dependency;
	REF struct driver **depvec;
	depvec = (REF struct driver **)malloca(self->d_depcnt * sizeof(REF struct driver *));
	TRY {
		for (i = 0; i < self->d_dyncnt; ++i) {
			ElfW(Dyn) tag;
			char const *filename;
			tag = self->d_dynhdr[i];
			if (tag.d_tag == DT_NULL)
				break;
			if (tag.d_tag != DT_NEEDED)
				continue;
			if unlikely(dep_i >= self->d_depcnt)
				THROW_FAULTY_ELF_ERROR(E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_NEEDED, dep_i);
			filename = self->d_dynstr + tag.d_un.d_ptr;
			if unlikely(filename < self->d_dynstr ||
			            filename >= self->d_dynstr_end)
				THROW_FAULTY_ELF_ERROR(E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_NEEDED, dep_i);
			if unlikely(!ATOMIC_READ(vfs_kernel.p_inode)) {
				char const *name;
				dependency = driver_with_name(filename);
				if likely(dependency)
					goto got_dependency;
				/* We get here if a driver loaded as a bootloader module required
				 * another driver as a dependency, with that other driver not having
				 * been provided in the same manner.
				 * In this case, tell the user that they've booted KOS in an impossible
				 * configuration, also informing them of the missing driver.
				 * Note that when built with the builtin debugger enabled, the user
				 * will even be prompted with a really nice error message! ;) */
				name = strchr(filename, '/');
				name = name ? name + 1 : filename;
				kernel_panic("Cannot load dependency %q of driver %q\n"
				             "Consider starting KOS with the dependency as a boot-module",
				             name, self->d_name);
			}
			dependency = driver_insmod(filename);
got_dependency:
			depvec[dep_i] = dependency; /* Inherit reference. */
			++dep_i;
		}
		if unlikely(dep_i < self->d_depcnt)
			THROW_FAULTY_ELF_ERROR(E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_NEEDED);
	} EXCEPT {
		while (dep_i--) {
			dependency    = depvec[dep_i];
			depvec[dep_i] = NULL;
			decref(dependency);
		}
		freea(depvec);
		RETHROW();
	}
	assert(dep_i == self->d_depcnt);
	/* Check for special case: A callback from of the dependencies contained
	 * a call that resulted in our driver being finalized. - Instead of saving
	 * references to all of the dependencies, we must drop all of the references,
	 * thus complying with the command of us being supposed to resolve our
	 * inter-driver dependencies. */
	if unlikely(ATOMIC_READ(self->d_flags) & DRIVER_FLAG_FINALIZING) {
		while (dep_i--)
			decref(depvec[dep_i]);
	} else {
		/* Copy the vector of dependencies all at once. */
		memcpy(self->d_depvec,
		       depvec,
		       self->d_depcnt,
		       sizeof(REF struct driver *));
	}
	/* Inherit dependencies. */
	freea(depvec);
}


#define DRIVER_RELOC_FLAG_NORMAL   0x0000
#define DRIVER_RELOC_FLAG_DEEPBIND 0x0001

/* @param: reloc_flags: Set of `DRIVER_RELOC_FLAG_*' */
PRIVATE NONNULL((1)) void *KCALL
driver_find_symbol_for_relocation(struct driver *__restrict self,
                                  uintptr_t symbol_id,
                                  size_t *psymbol_size,
                                  struct driver **porigin_driver,
                                  unsigned int reloc_flags)
		THROWS(E_NOT_EXECUTABLE) {
	void *symbol_addr;
	char const *symbol_name;
	size_t i;
	uintptr_t elf_hash, gnu_hash;
	ElfW(Sym) const *search_sym, *weak_symbol, *sym;
	struct driver *weak_symbol_driver, *dep;
	if unlikely(symbol_id >= self->d_dynsym_cnt)
		THROW_FAULTY_ELF_ERROR(E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_SYMBOL, symbol_id);
	search_sym         = self->d_dynsym_tab + symbol_id;
	weak_symbol        = NULL;
	weak_symbol_driver = NULL;
	if ((search_sym->st_shndx != SHN_UNDEF) &&
	    (reloc_flags & DRIVER_RELOC_FLAG_DEEPBIND)) {
		if (ELFW(ST_BIND)(search_sym->st_info) == STB_WEAK) {
			weak_symbol        = search_sym;
			weak_symbol_driver = self;
		} else {
			gnu_hash = DRIVER_SYMBOL_HASH_UNSET;
			elf_hash = DRIVER_SYMBOL_HASH_UNSET;
			sym      = search_sym;
			dep      = self;
			goto found_symbol;
		}
	}
	symbol_name = self->d_dynstr + search_sym->st_name;
	if unlikely(symbol_name < self->d_dynstr ||
	            symbol_name >= self->d_dynstr_end) {
		THROW_FAULTY_ELF_ERROR(E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_SYMNAME,
		                       search_sym->st_name);
	}
	/* Check for special symbol names. */
	if (driver_special_symbol(self,
	                          symbol_name,
	                          &symbol_addr,
	                          psymbol_size)) {
		if (porigin_driver)
			*porigin_driver = self;
		return symbol_addr;
	}
	/* Search for kernel core symbols. */
	elf_hash = DRIVER_SYMBOL_HASH_UNSET;
	if (kernel_symbol(symbol_name,
	                  &symbol_addr,
	                  psymbol_size,
	                  &elf_hash)) {
		if (porigin_driver)
			*porigin_driver = &kernel_driver;
		return symbol_addr;
	}
	/* Search dependencies of the driver. */
	gnu_hash = DRIVER_SYMBOL_HASH_UNSET;
	for (i = 0; i < self->d_depcnt; ++i) {
		dep = self->d_depvec[i];
		sym = driver_local_symbol(dep,
		                          symbol_name,
		                          &elf_hash,
		                          &gnu_hash);
		if (!sym)
			continue;
		if (sym->st_shndx == SHN_UNDEF)
			continue;
		/* Found a viable candidate.*/
		if (ELFW(ST_BIND)(sym->st_info) == STB_WEAK) {
			if (!weak_symbol) {
				weak_symbol        = sym;
				weak_symbol_driver = dep;
			}
			continue;
		}
		/* Found the correct symbol. */
found_symbol:
		symbol_addr = (void *)sym->st_value;
		if (sym->st_shndx != SHN_ABS)
			symbol_addr = (byte_t *)symbol_addr + dep->d_loadaddr;
		if (ELFW(ST_TYPE)(sym->st_info) == STT_GNU_IFUNC ||
		    ELFW(ST_TYPE)(sym->st_info) == STT_KOS_IDATA)
			symbol_addr = (*(void *(*)(void))symbol_addr)();
		if (psymbol_size)
			*psymbol_size = sym->st_size;
		if (porigin_driver)
			*porigin_driver = dep;
		return symbol_addr;
	}
	if (weak_symbol) {
		sym = weak_symbol;
		dep = weak_symbol_driver;
		goto found_symbol;
	}
	/* Lastly: Check if the module itself has a valid definition... */
	if (search_sym->st_shndx != SHN_UNDEF) {
		gnu_hash = DRIVER_SYMBOL_HASH_UNSET;
		elf_hash = DRIVER_SYMBOL_HASH_UNSET;
		sym      = search_sym;
		dep      = self;
		goto found_symbol;
	}
	printk(KERN_ERR "[mod] Relocation against unknown symbol %q in driver %q\n",
	       symbol_name, self->d_name);
	THROW_FAULTY_ELF_ERROR(E_NOT_EXECUTABLE_FAULTY_REASON_ELF_NO_SYMBOL,
	                       search_sym->st_name);
}


#ifndef __INTELLISENSE__
#undef APPLY_RELA
#include "driver-apply-reloc.c.inl"
#if ELF_ARCH_USESRELA
#define APPLY_RELA 1
#include "driver-apply-reloc.c.inl"
#endif /* ELF_ARCH_USESRELA */
#else /* !__INTELLISENSE__ */

/* @param: reloc_flags: Set of `DRIVER_RELOC_FLAG_*' */
INTDEF NONNULL((1, 2)) void KCALL
driver_do_apply_relocations_vector(struct driver *__restrict self,
                                   ElfW(Rel) *__restrict vector,
                                   size_t count, unsigned int reloc_flags);

/* @param: reloc_flags: Set of `DRIVER_RELOC_FLAG_*' */
INTDEF NONNULL((1, 2)) void KCALL
driver_do_apply_relocations_vector_addend(struct driver *__restrict self,
                                          ElfW(Rela) *__restrict vector,
                                          size_t count, unsigned int reloc_flags);

#endif /* __INTELLISENSE__ */


PRIVATE NONNULL((1)) void KCALL
driver_do_apply_relocations(struct driver *__restrict self)
		THROWS(E_NOT_EXECUTABLE, E_WOULDBLOCK) {
	unsigned int reloc_flags = 0;
	ElfW(Rel) *rel_base = NULL;
	size_t rel_count  = 0;
	ElfW(Rel) *jmp_base = NULL;
	size_t jmp_size  = 0;
#if ELF_ARCH_USESRELA
	ElfW(Rela) *rela_base = NULL;
	size_t rela_count  = 0;
	bool jmp_rels_have_addend = false;
#endif /* ELF_ARCH_USESRELA */
	size_t i;

	/* Service relocations of the module. */
	for (i = 0; i < self->d_dyncnt; ++i) {
		ElfW(Dyn) tag = self->d_dynhdr[i];
		switch (tag.d_tag) {

		case DT_NULL:
			goto done_dynamic;

		case DT_REL:
			rel_base = (ElfW(Rel) *)(self->d_loadaddr + tag.d_un.d_ptr);
			break;

		case DT_RELSZ:
			rel_count = tag.d_un.d_val / sizeof(ElfW(Rel));
			break;

		case DT_JMPREL:
			jmp_base = (ElfW(Rel) *)(self->d_loadaddr + tag.d_un.d_ptr);
			break;

		case DT_PLTRELSZ:
#if !ELF_ARCH_USESRELA
			jmp_size = tag.d_un.d_val / sizeof(ElfW(Rel));
#else /* !ELF_ARCH_USESRELA */
			jmp_size = tag.d_un.d_val;
#endif /* ELF_ARCH_USESRELA */
			break;

#if ELF_ARCH_USESRELA
		case DT_RELA:
			rela_base = (ElfW(Rela) *)(self->d_loadaddr + tag.d_un.d_ptr);
			break;

		case DT_RELASZ:
			rela_count = tag.d_un.d_val / sizeof(ElfW(Rela));
			break;

		case DT_PLTREL:
			if (tag.d_un.d_val == DT_RELA)
				jmp_rels_have_addend = true;
			break;
#endif /* ELF_ARCH_USESRELA */

		case DT_FLAGS:
			if (tag.d_un.d_val & DF_SYMBOLIC)
				reloc_flags |= DRIVER_RELOC_FLAG_DEEPBIND;
			break;

		case DT_SYMBOLIC:
			reloc_flags |= DRIVER_RELOC_FLAG_DEEPBIND;
			break;

		default: break;
		}
	}
done_dynamic:

	/* Apply relocations. */
	driver_do_apply_relocations_vector(self, rel_base, rel_count, reloc_flags);
#if !ELF_ARCH_USESRELA
	driver_do_apply_relocations_vector(self, jmp_base, jmp_size, reloc_flags);
#else /* !ELF_ARCH_USESRELA */
	driver_do_apply_relocations_vector_addend(self, rela_base, rela_count, reloc_flags);
	if (jmp_rels_have_addend) {
		driver_do_apply_relocations_vector_addend(self,
		                                          (ElfW(Rela) *)jmp_base,
		                                          jmp_size / sizeof(ElfW(Rela)),
		                                          reloc_flags);
	} else {
		driver_do_apply_relocations_vector(self, jmp_base,
		                                   jmp_size / sizeof(ElfW(Rel)),
		                                   reloc_flags);
	}
#endif /* ELF_ARCH_USESRELA */

	/* Disable text relocations for read-only program sections of the driver. */
	driver_disable_textrel(self);
}



PRIVATE NONNULL((1)) bool KCALL
driver_load_dependencies(struct driver *__restrict self)
		THROWS(E_NOT_EXECUTABLE, E_FSERROR, E_BADALLOC, E_WOULDBLOCK) {
	uintptr_t flags;
again:
	flags = ATOMIC_READ(self->d_flags);
	if (flags & DRIVER_FLAG_DEPLOADED)
		return false;
	if (flags & DRIVER_FLAG_DEPLOADING) {
		if (self->d_initthread == THIS_TASK)
			return false; /* Ignore recursive call */
		task_yield();
		goto again;
	}
	if (!ATOMIC_CMPXCH_WEAK(self->d_flags, flags, flags | DRIVER_FLAG_DEPLOADING))
		goto again;
	if (!(flags & DRIVER_FLAG_FINALIZING)) {
		/* Do load driver dependencies. */
		TRY {
			self->d_initthread = THIS_TASK;
			driver_do_load_dependencies(self);
		} EXCEPT {
			self->d_initthread = NULL;
			ATOMIC_AND(self->d_flags, ~DRIVER_FLAG_DEPLOADING);
			RETHROW();
		}
		self->d_initthread = NULL;
	}
	ATOMIC_OR(self->d_flags, DRIVER_FLAG_DEPLOADED);
	return true;
}

PRIVATE NONNULL((1)) bool KCALL
driver_apply_relocations(struct driver *__restrict self)
		THROWS(E_NOT_EXECUTABLE, E_WOULDBLOCK) {
	uintptr_t flags;
again:
	flags = ATOMIC_READ(self->d_flags);
	assert(flags & DRIVER_FLAG_DEPLOADED);
	if (flags & DRIVER_FLAG_RELOCATED)
		return false;
	if (flags & DRIVER_FLAG_RELOCATING) {
		if (self->d_initthread == THIS_TASK)
			return false; /* Ignore recursive call */
		task_yield();
		goto again;
	}
	if (!ATOMIC_CMPXCH_WEAK(self->d_flags, flags, flags | DRIVER_FLAG_RELOCATING))
		goto again;
	/* Do apply driver relocations. */
	if (!(flags & DRIVER_FLAG_FINALIZING)) {
		TRY {
			self->d_initthread = THIS_TASK;
			driver_do_apply_relocations(self);
		} EXCEPT {
			self->d_initthread = NULL;
			ATOMIC_AND(self->d_flags, ~DRIVER_FLAG_RELOCATING);
			RETHROW();
		}
		self->d_initthread = NULL;
	}
	ATOMIC_OR(self->d_flags, DRIVER_FLAG_RELOCATED);
	return true;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.driver.driver_do_invoke_initializer")
NONNULL((1)) void FCALL driver_do_invoke_initializer(void (*func)(void)) {
	TRY {
		(*func)();
	} EXCEPT {
		if (kernel_debugtrap_enabled() &&
		    (kernel_debugtrap_on & KERNEL_DEBUGTRAP_ON_DRIVER_INIT_FAILURE))
			kernel_debugtrap(SIGTRAP);
		RETHROW();
	}
}

LOCAL void FCALL driver_invoke_initializer(void (*func)(void)) {
	struct driver_initstate st;
	driver_init_savestate(&st);
	TRY {
		driver_do_invoke_initializer(func);
	} EXCEPT {
		driver_init_loadstate(&st);
		RETHROW();
	}
	driver_init_loadstate(&st);
}

LOCAL void FCALL
driver_invoke_initializer_s(uintptr_t func, struct driver *__restrict self) {
	if unlikely(func < self->d_loadstart || func >= self->d_loadend) {
		printk(KERN_ERR "[mod] Bad init function in driver %q (%p is out-of-bounds of %p...%p, loadaddr:%p)\n",
		       self->d_name, func, self->d_loadstart, self->d_loadend - 1, self->d_loadaddr);
		THROW_FAULTY_ELF_ERROR(E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_INIT_FUNC,
		                       func - self->d_loadstart);
	}
	driver_invoke_initializer((void(*)(void))func);
}


PRIVATE NONNULL((1)) void KCALL
driver_do_run_initializers(struct driver *__restrict self) THROWS(...) {
	size_t i, dyni;
	uintptr_t init_func = 0;
	uintptr_t *preinit_array_base = NULL;
	size_t     preinit_array_size = 0;
	uintptr_t *init_array_base = NULL;
	size_t     init_array_size = 0;
	for (dyni = 0; dyni < self->d_dyncnt; ++dyni) {
		switch (self->d_dynhdr[dyni].d_tag) {

		case DT_NULL:
			goto done_dyntag;

		case DT_INIT:
			init_func = self->d_loadaddr + (uintptr_t)self->d_dynhdr[dyni].d_un.d_ptr;
			break;

		case DT_PREINIT_ARRAY:
			preinit_array_base = (uintptr_t *)(self->d_loadaddr + self->d_dynhdr[dyni].d_un.d_ptr);
			break;

		case DT_PREINIT_ARRAYSZ:
			preinit_array_size = (size_t)self->d_dynhdr[dyni].d_un.d_val / sizeof(void(*)(void));
			break;

		case DT_INIT_ARRAY:
			init_array_base = (uintptr_t *)(self->d_loadaddr + self->d_dynhdr[dyni].d_un.d_ptr);
			break;

		case DT_INIT_ARRAYSZ:
			init_array_size = (size_t)self->d_dynhdr[dyni].d_un.d_val / sizeof(void(*)(void));
			break;

		default: break;
		}
	}
done_dyntag:
	for (i = 0; i < preinit_array_size; ++i) {
		uintptr_t init_addr;
		init_addr = preinit_array_base[i] /* + self->d_loadaddr*/;
		driver_invoke_initializer_s(init_addr, self);
	}
	/* Service a init function, if one was specified. */
	if (init_func)
		driver_invoke_initializer_s(init_func, self);
	/* Service init-array functions in forward order. */
	for (i = 0; i < init_array_size; ++i) {
		uintptr_t init_addr;
		init_addr = init_array_base[i] /* + self->d_loadaddr*/;
		driver_invoke_initializer_s(init_addr, self);
	}
}

PRIVATE NONNULL((1)) bool KCALL
driver_run_initializers(struct driver *__restrict self)
		THROWS(E_WOULDBLOCK, ...) {
	uintptr_t flags;
again:
	flags = ATOMIC_READ(self->d_flags);
	assert(flags & DRIVER_FLAG_DEPLOADED);
	assert(flags & DRIVER_FLAG_RELOCATED);
	if (flags & DRIVER_FLAG_INITIALIZED)
		return false;
	if (flags & DRIVER_FLAG_INITIALIZING) {
		if (self->d_initthread == THIS_TASK)
			return false; /* Ignore recursive call */
		task_yield();
		goto again;
	}
	if (!ATOMIC_CMPXCH_WEAK(self->d_flags, flags, flags | DRIVER_FLAG_INITIALIZING))
		goto again;
	if (!(flags & DRIVER_FLAG_FINALIZING)) {
		/* Do run driver initializers. */
		TRY {
			self->d_initthread = THIS_TASK;
			driver_do_run_initializers(self);
		} EXCEPT {
			self->d_initthread = NULL;
			/* Don't unset the INITIALIZING flag, thus allowing
			 * driver finalizer callbacks to still be executed.
			 * After all: There may be more than one initializer, and it may
			 *            not be the first callback which threw the error, so
			 *            to make things simple: Always invoke _all_ finalizers
			 *            (which have to be written such that they work properly,
			 *            even when their accompanying initializer has never been
			 *            called), so-as to ensure that we don't skip one that
			 *            turned out to be important for freeing some resource
			 *            that had already been allocated successfully. */
#if 1
			ATOMIC_OR(self->d_flags, DRIVER_FLAG_INITIALIZED);
#else
			ATOMIC_AND(self->d_flags, ~DRIVER_FLAG_INITIALIZING);
#endif
			RETHROW();
		}
		self->d_initthread = NULL;
		ATOMIC_OR(self->d_flags, DRIVER_FLAG_INITIALIZED);
	} else {
		/* Also set the `DRIVER_FLAG_FINALIZED_C' flag,
		 * so-as to prevent finalizers from being run. */
		ATOMIC_OR(self->d_flags,
		          DRIVER_FLAG_INITIALIZED |
		          DRIVER_FLAG_FINALIZED_C);
	}
	return true;
}


/* Initialize the given driver.
 *  #1: Load driver dependencies.
 *  #2: Apply driver relocations.
 *  #3: Execute driver initializers. */
PUBLIC NONNULL((1)) bool
(KCALL driver_initialize)(struct driver *__restrict self)
		THROWS(E_WOULDBLOCK, E_FSERROR, E_NOT_EXECUTABLE) {
	bool result;
	if (ATOMIC_READ(self->d_flags) & DRIVER_FLAG_INITIALIZED)
		return false;
	driver_load_dependencies(self);
	driver_apply_relocations(self);
	result = driver_run_initializers(self);
	return result;
}



PRIVATE NONNULL((2)) void
NOTHROW(KCALL unmap_range)(uintptr_t loadaddr,
                           ElfW(Phdr) const *__restrict headers,
                           size_t count) {
	ElfW(Addr) addr;
	ElfW(Word) size;
	while (count--) {
		if (headers[count].p_type != PT_LOAD)
			continue;
		addr = headers[count].p_vaddr;
		size = headers[count].p_memsz;
		if unlikely(!size)
			continue;
		addr += loadaddr;
		size += addr & PAGEMASK;
		addr &= ~PAGEMASK;
		vm_unmap_kernel_ram((void *)addr,
		                     CEIL_ALIGN(size, PAGESIZE),
		                     false);
	}
}


PRIVATE ATTR_PURE WUNUSED NONNULL((1)) bool KCALL
contains_illegal_overlap(ElfW(Phdr) const *__restrict headers,
                         size_t count) {
	size_t i, j;
	for (i = 0; i < count; ++i) {
		uintptr_t min_page;
		uintptr_t max_page;
		ElfW(Addr) addr;
		ElfW(Word) size;
		if (headers[i].p_type != PT_LOAD)
			continue;
		addr = headers[i].p_vaddr;
		size = headers[i].p_memsz;
		if (OVERFLOW_UADD(size, addr & PAGEMASK, &size))
			goto yes;
		addr &= ~PAGEMASK;
		min_page = addr / PAGESIZE;
		if (OVERFLOW_UADD(addr, size, &addr))
			goto yes;
		if (OVERFLOW_UADD(addr, (ElfW(Addr))PAGEMASK, &addr))
			goto yes;
		max_page = (addr / PAGESIZE) - 1;
		for (j = i + 1; j < count; ++j) {
			uintptr_t other_min_page;
			uintptr_t other_max_page;
			if (headers[j].p_type != PT_LOAD)
				continue;
			addr = headers[j].p_vaddr;
			size = headers[j].p_memsz;
			if (OVERFLOW_UADD(size, addr & PAGEMASK, &size))
				goto yes;
			addr &= ~PAGEMASK;
			other_min_page = addr / PAGESIZE;
			if (OVERFLOW_UADD(addr, size, &addr))
				goto yes;
			if (OVERFLOW_UADD(addr, (ElfW(Addr))PAGEMASK, &addr))
				goto yes;
			other_max_page = (addr / PAGESIZE) - 1;
			if (other_min_page < max_page &&
			    other_max_page > min_page)
				goto yes;
		}
	}
	return false;
yes:
	return true;
}


/* Map a driver into memory (all created mappings will have TEXTREL enabled!) */
PRIVATE NONNULL((1)) void KCALL
driver_map_into_memory(struct driver *__restrict self,
                       USER CHECKED byte_t *base,
                       size_t num_bytes)
		THROWS(E_BADALLOC, E_SEGFAULT, E_WOULDBLOCK) {
	ElfW(Half) i;
	uintptr_t loadaddr, min_addr, max_addr;
	size_t min_alignment = PAGESIZE;
	size_t total_bytes;
	assert(self->d_phnum);
	min_addr = (uintptr_t)-1;
	max_addr = (uintptr_t)0;
	/* Figure out the min/max byte offsets for program segments. */
	for (i = 0; i < self->d_phnum; ++i) {
		ElfW(Addr) addr, endaddr;
		ElfW(Word) size, align;
		if (self->d_phdr[i].p_type != PT_LOAD)
			continue;
		addr  = self->d_phdr[i].p_vaddr;
		size  = self->d_phdr[i].p_memsz;
		align = self->d_phdr[i].p_align;
		if unlikely(!size)
			continue;
		align = CEIL_ALIGN(align, PAGESIZE);
		if (min_alignment < align)
			min_alignment = align;
		size += addr & PAGEMASK;
		addr &= ~PAGEMASK;
		size = CEIL_ALIGN(size, PAGESIZE);
		if (min_addr > addr)
			min_addr = addr;
		if (OVERFLOW_UADD(addr, size - 1, &endaddr))
			THROW_FAULTY_ELF_ERROR(E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_PHDR_VADDR,
			                       addr, size);
		if (max_addr < endaddr)
			max_addr = endaddr;
	}
	if unlikely(min_addr >= max_addr)
		THROW_FAULTY_ELF_ERROR(E_NOT_EXECUTABLE_FAULTY_REASON_ELF_NOSEGMENTS);
	self->d_loadstart = min_addr;
	self->d_loadend   = max_addr + 1;
	total_bytes = (CEILDIV(max_addr, PAGESIZE) -
                   FLOORDIV(min_addr, PAGESIZE)) *
	              PAGESIZE;
	assert(total_bytes != 0);
	if unlikely(min_alignment & (min_alignment - 1))
		THROW_FAULTY_ELF_ERROR(E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_PHDR_ALIGN, min_alignment);
	/* Find a suitable target location where we can map the library. */
find_new_candidate:
	vm_kernel_treelock_read();
	loadaddr = (uintptr_t)vm_getfree(&vm_kernel,
	                                  HINT_GETADDR(KERNEL_VMHINT_DRIVER),
	                                  total_bytes,
	                                  min_alignment,
	                                  HINT_GETMODE(KERNEL_VMHINT_DRIVER));
	vm_kernel_treelock_endread();
	if unlikely(loadaddr == (uintptr_t)VM_GETFREE_ERROR) {
		uintptr_t version;
#ifndef __OPTIMIZE_SIZE__
		if (system_clearcaches())
			goto find_new_candidate;
#endif /* !__OPTIMIZE_SIZE__ */
		version = 0;
find_new_candidate_tryhard:
		vm_kernel_treelock_read();
		loadaddr = (uintptr_t)vm_getfree(&vm_kernel,
		                                  HINT_GETADDR(KERNEL_VMHINT_DRIVER),
		                                  total_bytes,
		                                  min_alignment,
		                                  HINT_GETMODE(KERNEL_VMHINT_DRIVER));
		vm_kernel_treelock_endread();
		if (loadaddr == (uintptr_t)VM_PAGED_GETFREE_ERROR) {
			if (system_clearcaches_s(&version))
				goto find_new_candidate_tryhard;
			THROW(E_BADALLOC_INSUFFICIENT_VIRTUAL_MEMORY, total_bytes);
		}
	}
	loadaddr -= min_addr;
	/* Now that we've got a suitable memory location, move on to actually map the library. */
	i = 0;
	TRY {
		for (; i < self->d_phnum; ++i) {
			ElfW(Addr) addr;
			ElfW(Word) size;
			ElfW(Word) filesize;
			ElfW(Off) offset;
			uintptr_half_t prot;
			ElfW(Word) segment_flags;
			if (self->d_phdr[i].p_type != PT_LOAD)
				continue;
			addr          = self->d_phdr[i].p_vaddr;
			size          = self->d_phdr[i].p_memsz;
			filesize      = self->d_phdr[i].p_filesz;
			offset        = self->d_phdr[i].p_offset;
			segment_flags = self->d_phdr[i].p_flags;
			if unlikely(!size)
				continue;
#if PF_R == VM_PROT_READ && PF_X == VM_PROT_EXEC
			prot = (segment_flags & (VM_PROT_READ | VM_PROT_EXEC)) | (VM_PROT_WRITE | VM_PROT_SHARED);
#else
			prot = VM_PROT_WRITE | VM_PROT_SHARED;
			if (segment_flags & PF_R)
				prot |= VM_PROT_READ;
			if (segment_flags & PF_X)
				prot |= VM_PROT_EXEC;
#endif
			addr += loadaddr;
			if (filesize > size)
				filesize = size;
			/* Create the program segment. */
			/* TODO: Prefault this mapping! (although technically, this would only be a performance
			 *       improvement, since we're faulting all of the memory below anyways...) */
			if (!vm_mapat(&vm_kernel,
			              (void *)(addr & ~PAGEMASK),
			              CEIL_ALIGN(size + (addr & PAGEMASK), PAGESIZE),
			              &vm_datablock_anonymous,
			              NULL,
			              NULL,
			              0,
			              prot,
			              VM_NODE_FLAG_PREPARED,
			              0)) {
				/* Check for illegal overlap */
				if (contains_illegal_overlap(self->d_phdr, self->d_phnum))
					THROW_FAULTY_ELF_ERROR(E_NOT_EXECUTABLE_FAULTY_REASON_ELF_SEGMENTOVERLAP);
				unmap_range(loadaddr, self->d_phdr, i);
				goto find_new_candidate;
			}
			if (filesize) {
				/* Copy program data. */
				byte_t *src = base + offset;
				if unlikely((void *)(src) < (void *)(base) ||
				            (void *)(src + filesize) > (void *)(base + num_bytes))
					THROW_FAULTY_ELF_ERROR(E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_PHDR_ALIGN);
				memcpy((byte_t *)addr, src, filesize);
			}
			if (size > filesize) /* Initialize .bss to all zeroes */
				memset((byte_t *)addr + filesize, 0, size - filesize);
		}
	} EXCEPT {
		unmap_range(loadaddr, self->d_phdr, i);
		RETHROW();
	}
	/* Save the used load address. */
	self->d_loadaddr = loadaddr;
	self->d_loadstart += loadaddr;
	self->d_loadend += loadaddr;
}

#undef path
PRIVATE ATTR_RETNONNULL WUNUSED REF struct driver *KCALL
driver_do_insmod_blob(USER CHECKED byte_t *base, size_t num_bytes,
                      USER CHECKED char const *driver_cmdline,
                      bool *pnew_driver_loaded,
                      struct regular_node *driver_inode,
                      struct path *driver_path,
                      struct directory_entry *driver_dentry,
                      unsigned int flags)
		THROWS(E_SEGFAULT, E_NOT_EXECUTABLE, E_BADALLOC, E_IOERROR) {
	REF struct driver *result;
	ElfW(Half) phdr_pt_dynamic, phdrc, i;
	ElfW(Phdr) *phdrv;
	if unlikely(num_bytes < sizeof(ElfW(Ehdr)))
		THROW(E_NOT_EXECUTABLE_TOOSMALL);
	/* validate the presence of an ELF EHDR */
	driver_verify_ehdr((ElfW(Ehdr) *)base);
	phdrv = (ElfW(Phdr) *)(base + ((ElfW(Ehdr) *)base)->e_phoff);
	phdrc = ((ElfW(Ehdr) *)base)->e_phnum;
	/* Validate the program header pointers. */
	if unlikely(phdrc > KERNEL_DRIVER_MAXPROGRAMHEADERCOUNT)
		THROW_FAULTY_ELF_ERROR(E_NOT_EXECUTABLE_FAULTY_REASON_ELF_TOOMANYSEGMENTS);
	if unlikely(!phdrc)
		THROW_FAULTY_ELF_ERROR(E_NOT_EXECUTABLE_FAULTY_REASON_ELF_NOSEGMENTS);
	if unlikely((byte_t *)phdrv < base ||
	            (byte_t *)phdrv + phdrc > base + num_bytes)
		THROW_FAULTY_ELF_ERROR(E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_HEADERS);
	{
		ElfW(Dyn) *pt_dynamic, *pt_dynamic_end;
		/* Search for the .dynamic section.
		 * We need find this section first, because it contains the DT_SONAME
		 * tag which we need to determine the driver's name, which is used for
		 * matching the driver against other, already-loaded drivers in order
		 * to prevent unnecessary work when it comes to ensuring that any
		 * driver is only loaded once! */
		for (phdr_pt_dynamic = 0; phdr_pt_dynamic < phdrc; ++phdr_pt_dynamic) {
			if (phdrv[phdr_pt_dynamic].p_type == PT_DYNAMIC)
				goto found_dynamic;
		}
		THROW_FAULTY_ELF_ERROR(E_NOT_EXECUTABLE_FAULTY_REASON_ELF_NO_DYNAMIC);
found_dynamic:
		/* Load the in-file range of the .dynamic program header */
		pt_dynamic     = (ElfW(Dyn) *)(base + phdrv[phdr_pt_dynamic].p_offset);
		pt_dynamic_end = (ElfW(Dyn) *)((byte_t *)pt_dynamic + phdrv[phdr_pt_dynamic].p_filesz);
		/* Ensure that the .dynamic program header bounds are valid. */
		if unlikely((void *)pt_dynamic > (void *)pt_dynamic_end ||
		            (void *)pt_dynamic < (void *)base ||
		            (void *)pt_dynamic_end > (void *)(base + num_bytes))
			THROW_FAULTY_ELF_ERROR(E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_DYNAMIC);
		{
			uintptr_t dynstr_vla    = (uintptr_t)-1;
			uintptr_t soname_offset = (uintptr_t)-1;
			ElfW(Dyn) *pt_dynamic_iter;
			for (pt_dynamic_iter = pt_dynamic;
			     pt_dynamic_iter < pt_dynamic_end; ++pt_dynamic_iter) {
				uintptr_t tag;
				tag = pt_dynamic_iter->d_tag;
				switch (tag) {

				case DT_NULL:
					goto done_tags_for_soname;

				case DT_SONAME:
					soname_offset = pt_dynamic_iter->d_un.d_ptr;
					break;

				case DT_STRTAB:
					dynstr_vla = pt_dynamic_iter->d_un.d_ptr;
					break;

				default: break;
				}
			}
done_tags_for_soname:
			/* Make sure that we found both a .dynstr section, as well as a DT_SONAME tag. */
			if unlikely(dynstr_vla == (uintptr_t)-1 || soname_offset == (uintptr_t)-1)
				THROW_FAULTY_ELF_ERROR(E_NOT_EXECUTABLE_FAULTY_REASON_ELF_NO_SONAME);
			/* Figure out which PT_LOAD-phdr contains `dynstr_vla' */
			for (i = 0; i < phdrc; ++i) {
				char *dynstr_base;
				size_t dynstr_offset;
				size_t dynstr_size;
				char *so_name_start;
				char *so_name_end;
				if (phdrv[i].p_type != PT_LOAD)
					continue;
				if (phdrv[i].p_vaddr > dynstr_vla)
					continue;
				/* Technically p_memsz, but any pointer above would
				 * always be an empty string, which isn't allowed! */
				if (phdrv[i].p_vaddr + phdrv[i].p_filesz <= dynstr_vla)
					continue;
				/* Found the segment. */
				dynstr_offset = dynstr_vla - phdrv[i].p_vaddr; /* Offset of `.dynstr' in segment */
				dynstr_base   = (char *)(base + phdrv[i].p_offset + dynstr_offset);
				dynstr_size   = phdrv[i].p_filesz - dynstr_offset;
				/* Make sure that .dynstr is in-bounds of the driver image. */
				if unlikely((void *)dynstr_base < (void *)base || soname_offset > dynstr_size ||
				            (void *)(dynstr_base + dynstr_size) > (void *)(base + num_bytes))
					THROW_FAULTY_ELF_ERROR(E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_SONAME);
				so_name_start = dynstr_base + soname_offset;
				so_name_end = (char *)memend(so_name_start, '\0',
				                             dynstr_size - soname_offset);
				/* All right! we've got the DT_SONAME string!
				 * -> Search for an existing driver with this name. */
				result = driver_with_namel(so_name_start,
				                           (size_t)(so_name_end - so_name_start));
				if (result) {
					if (pnew_driver_loaded)
						*pnew_driver_loaded = false;
					return result; /* This driver has already been loaded. */
				}
			}
		}
	}
	/* Load + initialize a new driver. */
	result = (REF struct driver *)kmalloc(offsetof(struct driver, d_phdr) +
	                                      phdrc * sizeof(ElfW(Phdr)),
	                                      GFP_LOCKED | GFP_CALLOC | GFP_PREFLT);
	TRY {
		ElfW(Ehdr) *ehdr;
		/* Copy program headers. */
		memcpy(result->d_phdr, phdrv, phdrc, sizeof(ElfW(Phdr)));
		result->d_weakrefcnt = 1;
		result->d_refcnt     = 2; /* 2: +1:<return-value>, +1:Not setting the `DRIVER_FLAG_FINALIZED' flag */
		result->d_phnum      = phdrc;
		sig_cinit(&result->d_destroyed);
		atomic_rwlock_cinit(&result->d_eh_frame_cache_lock);
		atomic_rwlock_cinit(&result->d_sections_lock);
		/* Fill in driver information. */
		if (driver_path && driver_dentry) {
			result->d_filename = print_kernel_path_malloc(driver_path,
			                                              driver_dentry);
		}
		if (driver_inode)
			result->d_file = (REF struct regular_node *)incref(driver_inode);
		if (driver_cmdline)
			driver_parse_cmdline(result, driver_cmdline);
		else {
			/* Always allocate an argument vector, even if that vector is empty. */
			result->d_argv = (char **)kmalloc(1 * sizeof(char *),
			                                  GFP_CALLOC | GFP_LOCKED | GFP_PREFLT);
		}
		ehdr = (ElfW(Ehdr) *)base;
		result->d_shoff    = ehdr->e_shoff;
		result->d_shstrndx = ehdr->e_shstrndx;
		result->d_shnum    = ehdr->e_shnum;
		COMPILER_READ_BARRIER();
		if unlikely(ATOMIC_READ(ehdr->e_shentsize) != sizeof(ElfW(Shdr))) {
			THROW_FAULTY_ELF_ERROR(E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_SHENT,
			                       ehdr->e_shentsize);
		}
		/* Validate offsets for section headers */
		if unlikely(result->d_shstrndx >= result->d_shnum) {
			THROW_FAULTY_ELF_ERROR(E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_SHSTRNDX,
			                       result->d_shstrndx, result->d_shnum);
		}
		if unlikely(result->d_shoff >= num_bytes ||
		            result->d_shoff + (result->d_shnum * sizeof(ElfW(Shdr))) > num_bytes) {
			THROW_FAULTY_ELF_ERROR(E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_SHOFF,
			                       result->d_shoff, result->d_shnum, num_bytes);
		}
		/* Load the sections header into memory. */
		result->d_shdr = (ElfW(Shdr) *)kmalloc(result->d_shnum * sizeof(ElfW(Shdr)), GFP_PREFLT);
		memcpy((ElfW(Shdr) *)result->d_shdr,
		       base + result->d_shoff,
		       result->d_shnum, sizeof(ElfW(Shdr)));
		{
			ElfW(Shdr) const *shstrtab;
			size_t shstrtab_size;
			char const *shstrtab_base, *shstrtab_end;
			shstrtab = &result->d_shdr[result->d_shstrndx];
			if unlikely(shstrtab->sh_type == SHT_NOBITS) {
				THROW_FAULTY_ELF_ERROR(E_NOT_EXECUTABLE_FAULTY_REASON_ELF_NOBITS_SHSTRTAB,
				                       result->d_shstrndx);
			}
			shstrtab_base = (char *)(base + shstrtab->sh_offset);
			shstrtab_size = shstrtab->sh_size;
			shstrtab_end  = shstrtab_base + shstrtab_size;
			if unlikely((void *)shstrtab_end < (void *)shstrtab_base ||
			            (void *)shstrtab_base < (void *)base ||
			            (void *)shstrtab_end > (void *)(base + num_bytes)) {
				THROW_FAULTY_ELF_ERROR(E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_SHSTRTAB,
				                       shstrtab->sh_offset,
				                       shstrtab_size, num_bytes);
			}
			while (shstrtab_size && !shstrtab_base[shstrtab_size - 1])
				--shstrtab_size;
			/* Load the .shstrtab section into memory. */
			result->d_shstrtab = (char *)kmalloc((shstrtab_size + 1) * sizeof(char), GFP_PREFLT);
			memcpy((char *)result->d_shstrtab, shstrtab_base, shstrtab_size, sizeof(char));
			((char *)result->d_shstrtab)[shstrtab_size] = '\0';
			result->d_shstrtab_end = result->d_shstrtab + shstrtab_size;
		}
		/* Load the driver's program segments into memory */
		driver_map_into_memory(result, base, num_bytes);
		assert(ADDR_ISKERN(result->d_loadaddr));
		TRY {
			/* With the driver program now loaded into memory, we can scan it for
			 * the different program sections we'll be needing in the future, and
			 * which are cached within the driver descriptor itself. */

			/* Just so we get this out of the way: Search for a .eh_frame section */
			for (i = 0; i < result->d_shnum; ++i) {
				char const *name;
				name = result->d_shstrtab + result->d_shdr[i].sh_name;
				if unlikely(name < result->d_shstrtab ||
				            name >= result->d_shstrtab_end)
					continue;
				if (strcmp(name, ".eh_frame") == 0) {
					/* Found the .eh_frame section! */
					if unlikely(!(result->d_shdr[i].sh_flags & SHF_ALLOC))
						THROW_FAULTY_ELF_ERROR(E_NOT_EXECUTABLE_FAULTY_REASON_ELF_NALLOC_EH_FRAME, i);
					result->d_eh_frame_start = (byte_t *)result->d_loadaddr + result->d_shdr[i].sh_addr;
					result->d_eh_frame_end   = result->d_eh_frame_start + result->d_shdr[i].sh_size;
					if unlikely(result->d_eh_frame_start > result->d_eh_frame_end ||
					            result->d_eh_frame_start < (byte_t *)result->d_loadstart ||
					            result->d_eh_frame_end > (byte_t *)result->d_loadend) {
						THROW_FAULTY_ELF_ERROR(E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_EH_FRAME,
						                       result->d_shdr[i].sh_addr,
						                       result->d_shdr[i].sh_size);
					}
					/* TODO: Calculate best-fit semi/level values. */
					result->d_eh_frame_cache_semi0 = ATREE_SEMI0(uintptr_t);
					result->d_eh_frame_cache_leve0 = ATREE_LEVEL0(uintptr_t);
					break;
				}
			}
			/* Figure out where the .dynamic section is mapped. */
			for (i = 0;; ++i) {
				byte_t *dyn_base;
				if unlikely(i >= phdrc)
					THROW_FAULTY_ELF_ERROR(E_NOT_EXECUTABLE_FAULTY_REASON_ELF_NO_DYNAMIC);
				if (result->d_phdr[i].p_type != PT_DYNAMIC)
					continue;
				dyn_base = (byte_t *)result->d_loadaddr + result->d_phdr[i].p_vaddr;
				if unlikely((void *)(dyn_base) < (void *)result->d_loadstart ||
				            (void *)(dyn_base + result->d_phdr[i].p_memsz) > (void *)result->d_loadend)
					THROW_FAULTY_ELF_ERROR(E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_DYNAMIC);
				/* Found it! */
				result->d_dyncnt = result->d_phdr[i].p_memsz / sizeof(ElfW(Dyn));
				result->d_dynhdr = (ElfW(Dyn) *)dyn_base;
				break;
			}

			/* Scan .dynamic program tags to figure out driver dependencies,
			 * as well as how it performs its relocations, etc. */
			{
				uintptr_t soname_offset;
				size_t dyni, dynstr_size;
				soname_offset = (uintptr_t)-1;
				dynstr_size   = (size_t)-1;
				for (dyni = 0; dyni < result->d_dyncnt; ++dyni) {
					ElfW(Dyn) tag;
					tag = result->d_dynhdr[dyni];
					switch (tag.d_tag) {

					case DT_NULL:
						goto done_tags;

					case DT_NEEDED:
						++result->d_depcnt;
						break;

					case DT_SONAME:
						soname_offset = tag.d_un.d_ptr;
						break;

					case DT_STRTAB:
						result->d_dynstr = (char *)(result->d_loadaddr + tag.d_un.d_ptr);
						if unlikely((void *)result->d_dynstr < (void *)result->d_loadstart ||
						            (void *)result->d_dynstr > (void *)result->d_loadend)
							THROW_FAULTY_ELF_ERROR(E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_DYNSTR, tag.d_un.d_ptr);
						break;

					case DT_STRSZ:
						dynstr_size = tag.d_un.d_val;
						break;

					case DT_HASH:
						result->d_hashtab = (ElfW(HashTable) *)(result->d_loadaddr + tag.d_un.d_ptr);
						if unlikely((void *)result->d_hashtab < (void *)result->d_loadstart ||
						            (void *)result->d_hashtab > (void *)result->d_loadend)
							THROW_FAULTY_ELF_ERROR(E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_SYMHASH, tag.d_un.d_ptr);
						break;

					case DT_SYMTAB:
						result->d_dynsym_tab = (ElfW(Sym) *)(result->d_loadaddr + tag.d_un.d_ptr);
						if unlikely((void *)result->d_dynsym_tab < (void *)result->d_loadstart ||
						            (void *)result->d_dynsym_tab > (void *)result->d_loadend)
							THROW_FAULTY_ELF_ERROR(E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_DYNSYM, tag.d_un.d_ptr);
						break;

					case DT_SYMENT:
						if unlikely(tag.d_un.d_val != sizeof(ElfW(Sym)))
							THROW_FAULTY_ELF_ERROR(E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_SYMENT, tag.d_un.d_ptr);
						break;

					case DT_RELAENT:
						if unlikely(tag.d_un.d_val != sizeof(ElfW(Rela)))
							THROW_FAULTY_ELF_ERROR(E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_RELAENT, tag.d_un.d_ptr);
						break;

					case DT_RELENT:
						if unlikely(tag.d_un.d_val != sizeof(ElfW(Rel)))
							THROW_FAULTY_ELF_ERROR(E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_RELENT, tag.d_un.d_ptr);
						break;

					default: break;
					}
				}
done_tags:
				if unlikely(!result->d_dynstr || soname_offset == (uintptr_t)-1)
					THROW_FAULTY_ELF_ERROR(E_NOT_EXECUTABLE_FAULTY_REASON_ELF_NO_SONAME);
				if unlikely((void *)result->d_dynstr < (void *)result->d_loadstart ||
				            (void *)result->d_dynstr > (void *)result->d_loadend)
					THROW_FAULTY_ELF_ERROR(E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_DYNSTR);
				if (dynstr_size == (size_t)-1) {
					/* Determine the .dynstr segment size by searching for the associated section header. */
					for (i = 0; i < result->d_shnum; ++i) {
						byte_t *sect_start, *sect_end;
						if (!(result->d_shdr[i].sh_flags & SHF_ALLOC))
							continue; /* Unallocated section... */
						sect_start = (byte_t *)result->d_loadaddr + result->d_shdr[i].sh_addr;
						sect_end   = sect_start + result->d_shdr[i].sh_size;
						if unlikely(sect_start >= sect_end)
							continue;
						if unlikely((void *)sect_start < (void *)result->d_loadstart ||
						            (void *)sect_end > (void *)result->d_loadend)
							continue;
						if ((void *)result->d_dynstr >= (void *)sect_start &&
						    (void *)result->d_dynstr < (void *)sect_end) {
							/* Found the section */
							result->d_dynstr_end = (char *)sect_end;
							goto do_dynstr_size;
						}
					}
					/* Fallback: Max section size */
					result->d_dynstr_end = (char *)result->d_loadend;
				} else {
					result->d_dynstr_end = result->d_dynstr + dynstr_size;
				}
do_dynstr_size:
				if unlikely((void *)result->d_dynstr_end < (void *)result->d_dynstr ||
				            (void *)result->d_dynstr_end > (void *)result->d_loadend)
					THROW_FAULTY_ELF_ERROR(E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_DYNSTR);
				result->d_name = result->d_dynstr + soname_offset;
				if unlikely(result->d_name < result->d_dynstr ||
				            result->d_name >= result->d_dynstr_end)
					THROW_FAULTY_ELF_ERROR(E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_DYNSTR);
			}
			/* Figure out how many symbols there are... */
			if (result->d_dynsym_tab) {
				if (result->d_hashtab) {
					result->d_dynsym_cnt = (size_t)result->d_hashtab->ht_nchains;
				} else {
					/* Look at section headers to find the .dynsym section. */
					for (i = 0; i < result->d_shnum; ++i) {
						byte_t *sect_start, *sect_end;
						if (!(result->d_shdr[i].sh_flags & SHF_ALLOC))
							continue; /* Unallocated section... */
						sect_start = (byte_t *)result->d_loadaddr + result->d_shdr[i].sh_addr;
						sect_end   = sect_start + result->d_shdr[i].sh_size;
						if unlikely(sect_start >= sect_end)
							continue;
						if unlikely((void *)sect_start < (void *)result->d_loadstart ||
						            (void *)sect_end > (void *)result->d_loadend)
							continue;
						if ((void *)result->d_dynsym_tab >= (void *)sect_start &&
						    (void *)result->d_dynsym_tab < (void *)sect_end) {
							/* Found the section */
							result->d_dynsym_cnt = ((byte_t *)sect_end - (byte_t *)result->d_dynsym_tab) /
							                       sizeof(ElfW(Sym));
							goto done_dynsym;
						}
					}
					THROW_FAULTY_ELF_ERROR(E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_DYNSYM);
				}
			}
#if DRIVER_FLAG_NORMAL != 0
			result->d_flags = DRIVER_FLAG_NORMAL;
#endif /* DRIVER_FLAG_NORMAL != 0 */
done_dynsym:

			/* Allocate the driver dependency vector.
			 * HINT: The number of dependencies was already calculated
			 *       by the `DT_NEEDED' case in the for-loop above. */
			result->d_depvec = (REF struct driver **)kmalloc(result->d_depcnt *
			                                                 sizeof(REF struct driver *),
			                                                 GFP_CALLOC |
			                                                 GFP_LOCKED |
			                                                 GFP_PREFLT);

			/* At this point, the driver structure has been fully initialized,
			 * so now it's time to actually register it as a known driver, before
			 * moving on to load dependencies, applying relocation, and finally
			 * invoking driver initializers.
			 * However, firstly we must register the driver as globally loaded,
			 * as well as do one final check to ensure that no other driver with
			 * the same name has already been loaded. */
			TRY {
				REF struct driver *existing_driver;
				existing_driver = add_global_driver(result);
				if unlikely(existing_driver) {
					/* Delete our newly created driver. */
					kfree(result->d_depvec);
					unmap_range(result->d_loadaddr,
					            result->d_phdr,
					            result->d_phnum);
					kfree((void *)result->d_shstrtab);
					kfree((void *)result->d_shdr);
					kfree((void *)result->d_argv);
					kfree((void *)result->d_cmdline);
					kfree((void *)result->d_filename);
					xdecref(result->d_file);
					kfree(result);
					if (pnew_driver_loaded)
						*pnew_driver_loaded = false;
					/* Return the existing driver. */
					return existing_driver;
				}
			} EXCEPT {
				kfree(result->d_depvec);
				RETHROW();
			}
		} EXCEPT {
			/* Unmap the driver program */
			unmap_range(result->d_loadaddr,
			            result->d_phdr,
			            result->d_phnum);
			RETHROW();
		}
	} EXCEPT {
		kfree((void *)result->d_shstrtab);
		kfree((void *)result->d_shdr);
		kfree((void *)result->d_argv);
		kfree((void *)result->d_cmdline);
		kfree((void *)result->d_filename);
		xdecref(result->d_file);
		kfree(result);
		RETHROW();
	}
	printk(KERN_NOTICE "[mod][+] Insmod: %q\n", result->d_name);
	if (!(flags & DRIVER_INSMOD_FLAG_NOINIT)) {
		TRY {
			/* Load dependencies of the driver. */
			driver_load_dependencies(result);
			/* Apply relocations to the driver. */
			driver_apply_relocations(result);
			/* Inform any attached debugger of the new driver.
			 * NOTE: This is done after relocations, but before initializers, so that
			 *       a debugger is able to safely set breakpoints without overriding
			 *       memory locations possibly affected by relocations. */
			vboxgdb_trap(FREESTR(VBOXGDB_TRAP_LIBRARY));
			if (kernel_debugtrap_enabled()) {
				struct debugtrap_reason r;
				r.dtr_signo  = SIGTRAP;
				r.dtr_reason = DEBUGTRAP_REASON_LIBRARY;
				kernel_debugtrap(&r);
			}
			/* Run driver initializers. */
			driver_run_initializers(result);
			/* Invoke dynamic driver-level callbacks for a new driver being loaded. */
			driver_loaded_callbacks(result);
		} EXCEPT {
			/* Try to finalize the driver. */
			struct exception_data error;
			error = *error_data();
			TRY {
				driver_finalize(result);
			} EXCEPT {
				error_code_t code = error_code();
				if (ERRORCODE_ISRTLPRIORITY(code)) {
					decref(result);
					RETHROW();
				}
				error_printf("Finalizing driver %q", result->d_name);
			}
			/* Restore original error data. */
			*error_data() = error;
			/* Drop our reference from the driver.
			 * NOTE: If this is the last reference held to the driver,
			 *       this will automatically delete it from the global
			 *       drivers list. */
			decref(result);
			RETHROW();
		}
	}
	if (pnew_driver_loaded)
		*pnew_driver_loaded = true;
	return result;
}


/* Load a new driver into the kernel, either from the
 * specified filesystem location, or via a raw data blob.
 * @param: driver_inode:       The INode from which to load the driver.
 * @param: driver_path:        The parent directory path for `driver_inode'
 * @param: driver_dentry:      The directory entry of `driver_inode' within `driver_path'
 * @param: driver_cmdline:     The commandline to-be passed to the driver, or `NULL'
 * @param: pnew_driver_loaded: When non-NULL, write `true' to this pointer when the returned
 *                             driver was just newly loaded. - Otherwise, write `false'.
 * @return: * :                A reference to the freshly loaded driver. */
PUBLIC ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct driver *KCALL
driver_insmod_file(struct regular_node *__restrict driver_inode,
                   struct path *driver_path,
                   struct directory_entry *driver_dentry,
                   USER CHECKED char const *driver_cmdline,
                   bool *pnew_driver_loaded,
                   unsigned int flags)
		THROWS(E_SEGFAULT, E_NOT_EXECUTABLE, E_BADALLOC, E_IOERROR) {
	pos_t filesize;
	size_t num_bytes;
	void *temp_mapping;
	REF struct driver *result;
	/* Quick check: Is there a driver that is mapping the given INode? */
	result = driver_with_file(driver_inode);
	if (result) {
		/* Already found it! */
		if (pnew_driver_loaded)
			*pnew_driver_loaded = false;
		return result;
	}

	/* Map the file into memory, then load it as a blob */
	inode_loadattr(driver_inode);
	COMPILER_READ_BARRIER();
	filesize = driver_inode->i_filesize;
	COMPILER_READ_BARRIER();
	if (filesize >= (pos_t)0x10000000)
		THROW(E_NOT_EXECUTABLE_TOOLARGE);
	num_bytes = CEIL_ALIGN((size_t)filesize, PAGESIZE);
	temp_mapping = vm_map(&vm_kernel,
	                      HINT_GETADDR(KERNEL_VMHINT_TEMPORARY),
	                      num_bytes,
	                      PAGESIZE,
	                      HINT_GETMODE(KERNEL_VMHINT_TEMPORARY),
	                      driver_inode,
	                      driver_path,
	                      driver_dentry,
	                      0,
	                      VM_PROT_READ | VM_PROT_SHARED,
	                      VM_NODE_FLAG_NOMERGE,
	                      0);
	TRY {
		/* Load the driver from the file blob. */
		result = driver_do_insmod_blob((byte_t *)temp_mapping,
		                               (size_t)filesize,
		                               driver_cmdline,
		                               pnew_driver_loaded,
		                               driver_inode,
		                               driver_path,
		                               driver_dentry,
		                               flags);
	} EXCEPT {
		vm_unmap(&vm_kernel, temp_mapping, num_bytes,
		          VM_UNMAP_NORMAL | VM_UNMAP_NOSPLIT);
		RETHROW();
	}
	TRY {
		vm_unmap(&vm_kernel, temp_mapping, num_bytes,
		          VM_UNMAP_NORMAL | VM_UNMAP_NOSPLIT);
	} EXCEPT {
		decref(result);
		RETHROW();
	}
	return result;
}

PUBLIC ATTR_RETNONNULL WUNUSED REF struct driver *KCALL
driver_insmod_blob(USER CHECKED byte_t *base, size_t num_bytes,
                   USER CHECKED char const *driver_cmdline,
                   bool *pnew_driver_loaded,
                   unsigned int flags)
		THROWS(E_SEGFAULT, E_NOT_EXECUTABLE, E_BADALLOC, E_IOERROR) {
	REF struct driver *result;
	/* Load the driver from the file blob. */
	result = driver_do_insmod_blob(base,
	                               num_bytes,
	                               driver_cmdline,
	                               pnew_driver_loaded,
	                               NULL,
	                               NULL,
	                               NULL,
	                               flags);
	return result;
}

/* Convenience wrapper to load a driver, given its absolute filename. */
PRIVATE ATTR_RETNONNULL WUNUSED REF struct driver *KCALL
driver_insmod_filename(USER CHECKED char const *driver_filename,
                       USER CHECKED char const *driver_cmdline,
                       bool *pnew_driver_loaded, unsigned int flags)
		THROWS(E_SEGFAULT, E_NOT_EXECUTABLE, E_BADALLOC, E_IOERROR, E_FSERROR) {
	REF struct driver *result;
	REF struct path *driver_path;
	REF struct inode *driver_node;
	REF struct directory_node *driver_directory;
	REF struct directory_entry *driver_dentry;
	USER CHECKED char const *last_segment;
	u16 last_segment_len;
	/* Check for an existing filename. */
	result = driver_with_filename(driver_filename);
	if (result) {
		if (pnew_driver_loaded)
			*pnew_driver_loaded = false;
		return result;
	}
	driver_path = path_traverse_ex(&fs_kernel,
	                               &vfs_kernel,
	                               &vfs_kernel,
	                               driver_filename,
	                               &last_segment,
	                               &last_segment_len,
	                               FS_MODE_FNORMAL,
	                               NULL);
	FINALLY_DECREF(driver_path);
	sync_read(driver_path);
	driver_directory = (REF struct directory_node *)incref(driver_path->p_inode);
	sync_endread(driver_path);
	{
		FINALLY_DECREF(driver_directory);
		driver_node = directory_getnode(driver_directory,
		                                last_segment,
		                                last_segment_len,
		                                directory_entry_hash(last_segment, last_segment_len),
		                                &driver_dentry);
		if unlikely(!driver_node)
			THROW(E_FSERROR_FILE_NOT_FOUND);
	}
	FINALLY_DECREF(driver_dentry);
	FINALLY_DECREF(driver_node);
	if (!INODE_ISREG(driver_node))
		THROW(E_NOT_EXECUTABLE_NOT_REGULAR);
	result = driver_insmod_file((struct regular_node *)driver_node,
	                            driver_path,
	                            driver_dentry,
	                            driver_cmdline,
	                            pnew_driver_loaded,
	                            flags);
	return result;
}




/* The default library path.
 * By default, this string is simply set to "/os/drivers"
 * NOTE: This path can be restored with
 *      `sysctl_set_driver_library_path(SYSCTL_DRIVER_LIBRARY_PATH_DEFAULT)' */
INTERN struct driver_library_path_string default_library_path = {
	/* .dlp_refcnt = */ 2, /* +1:default_library_path, +1:current_library_path */
	/* .dlp_path   = */ KERNEL_DRIVER_DEFAULT_LIBRARY_PATH
};

/* TODO: Kernel commandline option `driver-libpath=...' */

/* [1..1] The current driver library path.
 * This path is a ':'-separated list of UNIX-style pathnames
 * that are used to resolve dependencies of kernel driver modules.
 * By default, this string is simply set to "/os/drivers" */
PUBLIC ATOMIC_REF(struct driver_library_path_string)
driver_library_path = ATOMIC_REF_INIT(&default_library_path);


PRIVATE WUNUSED NONNULL((1)) /*ATTR_RETNONNULL_IF(second_phase)*/ REF struct driver *KCALL
driver_insmod_loadlib_at(char const *__restrict path_start, size_t path_length,
                         USER CHECKED char const *driver_name, size_t driver_name_length,
                         USER CHECKED char const *driver_cmdline,
                         bool *pnew_driver_loaded, unsigned int flags,
                         bool second_phase) {
	REF struct driver *result;
	char *buf;
	while (path_length && path_start[path_length - 1] == '/')
		--path_length;
	while (driver_name_length && driver_name[0] == '/')
		++driver_name, --driver_name_length;
	buf = (char *)malloca((path_length + driver_name_length + 2) * sizeof(char));
	TRY {
		memcpy(buf, path_start, path_length, sizeof(char));
		buf[path_length] = '/';
		memcpy(buf + path_length + 1, driver_name, driver_name_length, sizeof(char));
		buf[path_length + 1 + driver_name_length] = '\0';
		if (second_phase) {
			/* Second-phase (actually load new drivers) */
			result = driver_insmod_filename(buf,
			                                driver_cmdline,
			                                pnew_driver_loaded,
			                                flags);
		} else {
			result = driver_with_filename(buf);
		}
	} EXCEPT {
		freea(buf);
		RETHROW();
	}
	freea(buf);
	return result;
}

PRIVATE WUNUSED NONNULL((1)) /*ATTR_RETNONNULL_IF(second_phase)*/ REF struct driver *KCALL
driver_insmod_loadlib(struct driver_library_path_string *__restrict libpath,
                      USER CHECKED char const *driver_name,
                      USER CHECKED char const *driver_cmdline,
                      bool *pnew_driver_loaded,
                      unsigned int flags,
                      bool second_phase) {
	REF struct driver *result;
	char const *sep;
	char const *path_start = libpath->dlp_path;
	size_t driver_name_len = strlen(driver_name);
	for (;;) {
		sep = strchrnul(path_start, ':');
		TRY {
			result = driver_insmod_loadlib_at(path_start, (size_t)(sep - path_start),
			                                  driver_name, driver_name_len,
			                                  driver_cmdline,
			                                  pnew_driver_loaded,
			                                  flags,
			                                  second_phase);
		} EXCEPT {
			error_code_t code = error_code();
			if (ERROR_CLASS(code) != E_FSERROR || !E_FSERROR_IS_FILE_NOT_FOUND(code))
				RETHROW(); /* Something other than file-not-found */
			if (second_phase && !*sep)
				RETHROW(); /* This is the last possible path to search in the second phase. */
			result = NULL;
		}
		if (result)
			break;
		if (!*sep)
			break;
		path_start = sep + 1;
	}
	return result;
}


/* Load a driver as a dependency of another. */
PUBLIC ATTR_RETNONNULL WUNUSED REF struct driver *KCALL
driver_insmod(USER CHECKED char const *driver_name,
              USER CHECKED char const *driver_cmdline,
              bool *pnew_driver_loaded,
              unsigned int flags)
		THROWS(E_SEGFAULT, E_NOT_EXECUTABLE, E_BADALLOC, E_IOERROR, E_FSERROR) {
	REF struct driver *result;
	if (driver_name[0] == '/') {
		/* Absolute filename. */
		/* Check for an existing driver. */
		result = driver_insmod_filename(driver_name,
		                                driver_cmdline,
		                                pnew_driver_loaded,
		                                flags);
	} else {
		REF struct driver_library_path_string *libpath;
		/* Search for a driver that is matching the given name. */
		result = driver_with_name(driver_name);
		if (result) {
			if (pnew_driver_loaded)
				*pnew_driver_loaded = false;
			goto done;
		}
		/* Load the driver library path and search for the driver. */
		libpath = driver_library_path.get();
		FINALLY_DECREF_UNLIKELY(libpath);
		result = driver_insmod_loadlib(libpath,
		                               driver_name,
		                               driver_cmdline,
		                               pnew_driver_loaded,
		                               flags,
		                               false);
		if (result)
			goto done;
		result = driver_insmod_loadlib(libpath,
		                               driver_name,
		                               driver_cmdline,
		                               pnew_driver_loaded,
		                               flags,
		                               true);
	}
done:
	return result;
}



#ifndef CONFIG_NO_BOOTLOADER_DRIVERS
PRIVATE ATTR_FREETEXT size_t
NOTHROW(KCALL initdrivers)(size_t buflen) {
	REF struct driver **buf;
	size_t i, dst, driver_count, loaded_drivers = 0;
	buf = (REF struct driver **)malloca(buflen * sizeof(REF struct driver *));
	/*TRY*/ {
		REF struct driver_state *state;
		state        = current_driver_state.get();
		driver_count = state->ds_count;
		if (!driver_count || unlikely(driver_count > buflen)) {
			decref_unlikely(state);
			loaded_drivers = driver_count;
			goto done;
		}
		for (dst = i = 0; i < driver_count; ++i) {
			struct driver *drv;
			drv = state->ds_drivers[i];
			if likely(tryincref(drv))
				buf[dst++] = drv;
		}
		decref_unlikely(state);
		driver_count = dst;
		/*TRY*/ {
			unsigned int sort_remaining;
			bool sort_must_restart;
			/* Step #1: Make sure that all enumerated drivers have dependencies linked. */
			for (i = 0; i < driver_count; ++i) {
				TRY {
					if (driver_load_dependencies(buf[i]))
						++loaded_drivers;
				} EXCEPT {
					error_printf(FREESTR("Loading dependencies for %q"),
					             buf[i]->d_name);
					TRY {
						driver_finalize(buf[i]);
					} EXCEPT {
						error_printf(FREESTR("Finalizing driver %q"), buf[i]->d_name);
					}
					decref(buf[i]);
					buf[i] = NULL;
				}
			}
			/* Step #2: Sort drivers based on inter-driver dependencies
			 *   -> Drivers that are dependencies of other drivers must be
			 *      initialized before drivers that depend on them. */
			sort_remaining = 64;
again_sort:
			sort_must_restart = false;
			assert(driver_count != 0);
			for (i = 0; i < driver_count - 1;) {
				struct driver *d = buf[i];
				size_t j;
				bool did_shift_vector;
				if (!d || !d->d_depcnt) {
					++i;
					continue;
				}
				/* This driver has some actual dependencies. */
				did_shift_vector = false;
				for (j = 0; j < d->d_depcnt; ++j) {
					struct driver *dep;
					size_t k;
					dep = ATOMIC_READ(d->d_depvec[j]);
					if unlikely(!dep)
						continue;
					/* Check if `dep' would normally be initialized after `i' */
					for (k = i + 1; k < driver_count; ++k) {
						if (buf[k] != dep)
							continue;
						/* Yes, it would be.
						 * -> Shift elements in `buf[i...k-1]' up by 1, then
						 *    override buf[i] with dep, thus causing `dep' to
						 *    be initialized before the driver `d', which depends
						 *    on it. */
						memmoveup(&buf[i + 1],
						          &buf[i],
						          k - i,
						          sizeof(REF struct driver *));
						buf[i]            = dep;
						sort_must_restart = true;
						did_shift_vector  = true;
						break;
					}
				}
				if (!did_shift_vector)
					++i;
			}
			/* Re-sort only a limited number of times to prevent the kernel from
			 * freezing up due to dependency loops (even though dependency loops
			 * aren't actually allowed, but I still don't want the kernel
			 * freezing up...) */
			if (sort_must_restart && sort_remaining) {
				--sort_remaining;
				goto again_sort;
			}
			/* With the driver vector now sorted, apply relocations */
			for (i = 0; i < driver_count; ++i) {
				struct driver *d;
				d = buf[i];
				if (!d)
					continue;
				TRY {
					if (driver_apply_relocations(buf[i]))
						++loaded_drivers;
				} EXCEPT {
					error_printf(FREESTR("Applying relocations to %q"),
					             buf[i]->d_name);
					TRY {
						driver_finalize(buf[i]);
					} EXCEPT {
						error_printf(FREESTR("Finalizing driver %q"), buf[i]->d_name);
					}
					decref(buf[i]);
					buf[i] = NULL;
				}
			}
			/* Finally, invoke constructors for all drivers */
			for (i = 0; i < driver_count; ++i) {
				struct driver *d;
				d = buf[i];
				if (!d)
					continue;
				TRY {
					if (driver_run_initializers(buf[i]))
						++loaded_drivers;
				} EXCEPT {
					error_printf(FREESTR("Calling constructors of %q"),
					             buf[i]->d_name);
					TRY {
						driver_finalize(buf[i]);
					} EXCEPT {
						error_printf(FREESTR("Finalizing driver %q"), buf[i]->d_name);
					}
					decref(buf[i]);
					buf[i] = NULL;
				}
			}
		} /*EXCEPT {
			while (driver_count--)
				xdecref(buf[driver_count]);
			RETHROW();
		}*/
		while (driver_count--)
			xdecref(buf[driver_count]);
	} /*EXCEPT {
		freea(buf);
		RETHROW();
	}*/
done:
	freea(buf);
	return loaded_drivers;
}

/* Initialize (link, relocation & initialize) all drivers
 * loaded via the kernel commandline as bootloader modules.
 * This is done as a separate step from the actual loading
 * of drivers so-as to allow for inter-driver dependencies
 * to be resolved correctly. */
INTERN ATTR_FREETEXT void
NOTHROW(KCALL kernel_initialize_loaded_drivers)(void) {
	size_t new_driver_count;
	size_t driver_count;
	REF struct driver_state *state;
	state        = current_driver_state.get();
	driver_count = state->ds_count;
	decref_unlikely(state);
again_init_drivers:
	new_driver_count = initdrivers(driver_count);
	if unlikely(new_driver_count > driver_count) {
		driver_count = new_driver_count;
		goto again_init_drivers;
	}
	/* Recursively re-check for any partially initialized drivers. */
	if (new_driver_count)
		goto again_init_drivers;
}
#endif /* !CONFIG_NO_BOOTLOADER_DRIVERS */


#ifdef CONFIG_HAVE_DEBUGGER
DBG_COMMAND(lsmod,
            "lsmod\n"
            "\tList all currently loaded drivers\n") {
	size_t i, longest_name, longest_cmdl;
	REF struct driver_state *ds;
	ds = driver_get_state();
	longest_name = 4;
	longest_cmdl = 7;
	for (i = 0; i < ds->ds_count; ++i) {
		struct driver *d;
		size_t temp;
		d = ds->ds_drivers[i];
		if (wasdestroyed(d))
			continue; /* Dead driver... */
		temp = strlen(d->d_name);
		if (longest_name < temp)
			longest_name = temp;
		temp = (size_t)cmdline_encode(&format_length, NULL, d->d_argc, d->d_argv);
		if (longest_cmdl < temp)
			longest_cmdl = temp;
	}
	if (longest_name > 24)
		longest_name = 24;
	if (longest_cmdl > 24)
		longest_cmdl = 24;
#if __SIZEOF_POINTER__ == 8
	dbg_printf(DBGSTR("%-*s %-*s loadaddr         minaddr          maxaddr\n"),
	           longest_name, DBGSTR("name"),
	           longest_cmdl, DBGSTR("cmdline"));
#else /* __SIZEOF_POINTER__ == 8 */
	dbg_printf(DBGSTR("%-*s %-*s loadaddr minaddr  maxaddr\n"),
	           longest_name, DBGSTR("name"),
	           longest_cmdl, DBGSTR("cmdline"));
#endif /* __SIZEOF_POINTER__ == 8 */
	for (i = 0; i < ds->ds_count; ++i) {
		struct driver *d;
		size_t temp;
		d = ds->ds_drivers[i];
		if (wasdestroyed(d))
			continue; /* Dead driver... */
		if (d->d_flags & DRIVER_FLAG_FINALIZED)
			/* Already finalized */
			dbg_print(DBGSTR(AC_FG(ANSITTY_CL_MAROON)));
		else if (d->d_flags & DRIVER_FLAG_FINALIZING)
			/* In the process of being finalized */
			dbg_print(DBGSTR(AC_FG(ANSITTY_CL_RED)));
		else if (!(d->d_flags & DRIVER_FLAG_INITIALIZED)) {
			/* In the process of being initialized */
			dbg_print(DBGSTR(AC_FG(ANSITTY_CL_YELLOW)));
		}
		dbg_printf(DBGSTR("%-*s "), longest_name, d->d_name);
		temp = (size_t)cmdline_encode(&dbg_printer, NULL, d->d_argc, d->d_argv);
		format_repeat(&dbg_printer, NULL, ' ', longest_cmdl - temp);
		dbg_printf(DBGSTR(" %p %p %p" AC_DEFATTR "\n"),
		           d->d_loadaddr,
		           d->d_loadstart,
		           d->d_loadend - 1);
	}
	decref_nokill(ds);
	return 0;
}
#endif /* CONFIG_HAVE_DEBUGGER */


DECL_END

#endif /* !GUARD_KERNEL_CORE_FS_DRIVER_C */
