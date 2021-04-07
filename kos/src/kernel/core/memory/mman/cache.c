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
#ifndef GUARD_KERNEL_SRC_MEMORY_MMAN_CACHE_C
#define GUARD_KERNEL_SRC_MEMORY_MMAN_CACHE_C 1

#include <kernel/compiler.h>

#include <kernel/heap.h>
#include <kernel/malloc.h>
#include <kernel/mman/cache.h>
#include <kernel/mman/driver.h>
#include <sched/task.h>

#include <hybrid/atomic.h>
#include <hybrid/overflow.h>

#include <assert.h>
#include <stddef.h>

DECL_BEGIN



typedef NOBLOCK size_t /*NOTHROW*/ (KCALL *kernel_system_clearcache_t)(void);
INTDEF kernel_system_clearcache_t __kernel_system_clearcaches_start[];
INTDEF kernel_system_clearcache_t __kernel_system_clearcaches_end[];


#ifdef CONFIG_TRACE_MALLOC
INTDEF ATTR_WEAK struct heap trace_heap;
#endif /* CONFIG_TRACE_MALLOC */


/* Called as part of `system_clearcaches()': Trim standard kernel heaps.
 * @return: * : The total number of trimmed bytes. */
PRIVATE NOBLOCK size_t NOTHROW(KCALL system_trimheaps)(void) {
	size_t i, temp, result = 0;
	for (i = 0; i < __GFP_HEAPCOUNT; ++i) {
		temp = heap_trim(&kernel_heaps[i], 0);
		if (OVERFLOW_UADD(result, temp, &result))
			result = (size_t)-1;
	}
#ifdef CONFIG_TRACE_MALLOC
	if (&trace_heap) {
		temp = heap_trim(&trace_heap, 0);
		if (OVERFLOW_UADD(result, temp, &result))
			result = (size_t)-1;
	}
#endif /* CONFIG_TRACE_MALLOC */
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
	 * the middle of a call  to `system_clearcaches()'. - In this  case,
	 * try  to yield to them so they can finish, and keep on checking if
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
	/* Even  when  nothing seems  to change,  try a  couple more  times in  the vain
	 * hope  that some other thread managed to get  hold of a lock that was required
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
		/* We got here because the  version number is too  high.
		 * Fix this and indicate success since this only happens
		 * once  every bagillion iterations, so this won't cause
		 * a soft-lock. */
		ATOMIC_CMPXCH(system_clearcaches_version, new_version, 0);
		*pversion = 0;
		return 1;
	}
	return 0;
}


/* Invoke cache clear callbacks for each and every globally reachable
 * component within the entire kernel.
 * This function is  called when  the kernel  has run  out of  physical/virtual
 * memory, or some other kind of limited, and dynamically allocatable resource.
 * @return: * : At  least some amount of some kind of resource was released.
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
	 *      itself, meaning that such a  stack could easily be  allocated
	 *      statically. */
	ATOMIC_INC(system_clearcaches_isinside);
#ifdef CONFIG_USE_NEW_DRIVER
	{
		REF struct driver_loadlist *ll;
		/* Invoke the `drv_clearcache()' function of every loaded driver. */
		ll = get_driver_loadlist();
		for (i = 0; i < ll->dll_count; ++i) {
			kernel_system_clearcache_t func;
			REF struct driver *drv;
			drv = ll->dll_drivers[i];
			if (!tryincref(drv))
				continue; /* Dead driver... */
			*(void **)&func = driver_dlsym(drv, "drv_clearcache");
			if (func) {
				temp = (*func)();
				if (OVERFLOW_UADD(result, temp, &result))
					result = (size_t)-1;
			}
			decref_unlikely(drv);
		}
		assert(!wasdestroyed(ll));
		if (ATOMIC_DECFETCH(ll->dll_refcnt) == 0) {
			temp = offsetof(struct driver_loadlist, dll_drivers) +
			       (ll->dll_count * sizeof(REF struct driver *));
			if (OVERFLOW_UADD(result, temp, &result))
				result = (size_t)-1;
			destroy(ll);
		}
	}
#else /* CONFIG_USE_NEW_DRIVER */
	{
		REF struct driver_state *state;
		/* Invoke the `drv_clearcache()' function of every loaded driver. */
		state = driver_get_state();
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
#endif /* !CONFIG_USE_NEW_DRIVER */
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
	 * the  heap sub-system  to release as  much memory as  it possibly can) */
	temp = system_trimheaps();
	if (OVERFLOW_UADD(result, temp, &result))
		result = (size_t)-1;
	if (result != 0) /* Managed to do something: Increment the cache-version */
		ATOMIC_INC(system_clearcaches_version);
	ATOMIC_DEC(system_clearcaches_isinside);
	return result;
}

DECL_END

#endif /* !GUARD_KERNEL_SRC_MEMORY_MMAN_CACHE_C */
