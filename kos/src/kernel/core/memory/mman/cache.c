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
#include <kernel/mman.h>
#include <kernel/mman/cache.h>
#include <kernel/mman/driver.h>
#include <kernel/mman/module-section-cache.h>
#include <sched/enum.h>
#include <sched/task.h>

#include <hybrid/atomic.h>
#include <hybrid/overflow.h>

#include <assert.h>
#include <limits.h>
#include <stddef.h>

/**/
#include "module-userelf.h" /* CONFIG_HAVE_USERELF_MODULES */

DECL_BEGIN



typedef NOBLOCK size_t /*NOTHROW*/ (KCALL *kernel_system_clearcache_t)(void);
INTDEF kernel_system_clearcache_t __kernel_syscache_clear_start[];
INTDEF kernel_system_clearcache_t __kernel_syscache_clear_end[];


#ifdef CONFIG_TRACE_MALLOC
INTDEF ATTR_WEAK struct heap trace_heap;
#endif /* CONFIG_TRACE_MALLOC */


/* Counter for the number of threads currently inside of `syscache_clear()' */
PRIVATE WEAK size_t syscache_clear_isinside = 0;

/* The id of the last invocation of `syscache_clear()' for which memory got actually released. */
PRIVATE WEAK uintptr_t syscache_clear_version = 0;

#define cc_account(p_result, expr)                          \
	do {                                                    \
		size_t _cc_temp;                                    \
		_cc_temp = (expr);                                  \
		if (OVERFLOW_UADD(*(p_result), _cc_temp, p_result)) \
			*(p_result) = (size_t)-1;                       \
	}	__WHILE0


/* Called as part of `syscache_clear()': Trim standard kernel heaps.
 * @return: * : The total number of trimmed bytes. */
PRIVATE NOBLOCK size_t NOTHROW(KCALL cc_trimheaps)(void) {
	size_t i, result = 0;
	for (i = 0; i < __GFP_HEAPCOUNT; ++i)
		cc_account(&result, heap_trim(&kernel_heaps[i], 0));
#ifdef CONFIG_TRACE_MALLOC
	if (&trace_heap)
		cc_account(&result, heap_trim(&trace_heap, 0));
#endif /* CONFIG_TRACE_MALLOC */
	return result;
}

/* Clear driver caches. */
PRIVATE NOBLOCK size_t NOTHROW(KCALL cc_drivers)(void) {
	size_t i, result = 0;
#ifdef CONFIG_USE_NEW_DRIVER
	REF struct driver_loadlist *ll;
	/* Invoke the `drv_clearcache()' function of every loaded driver. */
	ll = get_driver_loadlist();
	for (i = 0; i < ll->dll_count; ++i) {
		kernel_system_clearcache_t func;
		REF struct driver *drv;
		drv = ll->dll_drivers[i];
		if (!tryincref(drv))
			continue; /* Dead driver... */
		*(void **)&func = driver_dlsym_local(drv, "drv_clearcache");
		if (func)
			cc_account(&result, (*func)());
		decref_unlikely(drv);
	}
	assert(!wasdestroyed(ll));
	if (ATOMIC_DECFETCH(ll->dll_refcnt) == 0) {
		cc_account(&result,
		           offsetof(struct driver_loadlist, dll_drivers) +
		           (ll->dll_count * sizeof(REF struct driver *)));
		destroy(ll);
	}
#else /* CONFIG_USE_NEW_DRIVER */
	REF struct driver_state *state;
	/* Invoke the `drv_clearcache()' function of every loaded driver. */
	state = driver_get_state();
	for (i = 0; i < state->ds_count; ++i) {
		kernel_system_clearcache_t func;
		REF struct driver *drv;
		drv = state->ds_drivers[i];
		if (!tryincref(drv))
			continue; /* Dead driver... */
		if (driver_symbol_ex(drv, "drv_clearcache", (void **)&func))
			cc_account(&result, (*func)());
		decref_unlikely(drv);
	}
	assert(!wasdestroyed(state));
	if (ATOMIC_DECFETCH(state->ds_refcnt) == 0) {
		cc_account(&result,
		           offsetof(struct driver_state, ds_drivers) +
		           (state->ds_count * sizeof(REF struct driver *)));
		destroy(state);
	}
#endif /* !CONFIG_USE_NEW_DRIVER */
	return result;
}


/* Clear kernel core caches. */
PRIVATE NOBLOCK size_t NOTHROW(KCALL cc_kernel)(void) {
	size_t result = 0;
	kernel_system_clearcache_t *iter;
	/* Invoke kernel-internal clear-cache functions. */
	for (iter = __kernel_syscache_clear_start;
	     iter < __kernel_syscache_clear_end; ++iter)
		cc_account(&result, (**iter)());
	return result;
}


/* Cache-clear functions from around the kernel core... */
#ifdef CONFIG_HAVE_USERELF_MODULES
INTDEF NOBLOCK NONNULL((1)) size_t NOTHROW(FCALL mman_clear_module_cache)(struct mman *__restrict self);
#endif /* CONFIG_HAVE_USERELF_MODULES */
/*...*/


PRIVATE NOBLOCK size_t
NOTHROW(KCALL cc_permman)(struct mman *__restrict self) {
	size_t result = 0;
#ifdef CONFIG_HAVE_USERELF_MODULES
	cc_account(&result, mman_clear_module_cache(self));
#endif /* CONFIG_HAVE_USERELF_MODULES */
	return result;
}

PRIVATE NOBLOCK size_t
NOTHROW(KCALL cc_pertask)(struct task *__restrict thread) {
	size_t result;
	REF struct mman *mm;
	mm     = task_getmman(thread);
	result = cc_permman(mm);
	if unlikely(ATOMIC_DECFETCH(mm->mm_refcnt) == 0) {
		cc_account(&result, sizeof(struct mman));
		mman_destroy(mm);
	}
	return (ssize_t)result;
}

PRIVATE NOBLOCK ssize_t
NOTHROW(KCALL cc_pertask_cb)(void *UNUSED(arg),
                             struct task *thread,
                             struct taskpid *UNUSED(pid)) {
	size_t result = 0;
	if (thread) {
		result = cc_pertask(thread);
		if (result > (size_t)SSIZE_MAX)
			result = (size_t)SSIZE_MAX;
	}
	return (ssize_t)result;
}

PRIVATE NOBLOCK size_t
NOTHROW(KCALL cc_threads)(void) {
	return (size_t)task_enum_all_nb(&cc_pertask_cb, NULL);
}


/* Clear all caches. */
PRIVATE NOBLOCK size_t NOTHROW(KCALL cc_all)(void) {
	size_t result = cc_drivers();
	cc_account(&result, cc_kernel());
	cc_account(&result, cc_threads());
	cc_account(&result, cc_trimheaps());
	return result;
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
NOTHROW(KCALL syscache_clear)(void) {
	size_t result;
	/* XXX: Execute this function on a separate stack to make invocations
	 *      in scenarios where little to no memory is available possible.
	 *      It is OK if this function cannot be executed in parallel with
	 *      itself, meaning that such a  stack could easily be  allocated
	 *      statically. */
	ATOMIC_INC(syscache_clear_isinside);

	/* Actually clear caches. */
	result = cc_all();

	if (result != 0) /* Managed to do something: Increment the cache-version */
		ATOMIC_INC(syscache_clear_version);
	ATOMIC_DEC(syscache_clear_isinside);
	return result;
}


/* multi-thread-corrected version of `syscache_clear()'.
 * This function should always be used in favor of `syscache_clear()', as it
 * solves the scenario of multiple threads calling `syscache_clear()' at the
 * same time, in which case resources may only get freed by one thread, with
 * the other thread never getting informed about that fact.
 * In this case,  `syscache_clear()' would normally  (and correctly I  might
 * add) return `0' for some threads, since that thread really didn't release
 * any  resources. However,  the intended use  of this function  is inform a
 * caller who just  failed to  allocate some optional  resource, that  their
 * resource may have become available, and that they should try again (which
 * is  something that isn't fulfilled by the regular `syscache_clear()' in a
 * multi-threaded environment)
 *
 * That is where this function comes in:
 * >> void *my_alloc_tryhard() {
 * >>     void *result;
 * >>     result = my_alloc();
 * >>     if unlikely(!result) {
 * >>         syscache_version_t ver = SYSCACHE_VERSION_INIT;
 * >>         for (;;) {
 * >>             result = my_alloc();
 * >>             if (result)
 * >>                 break;
 * >>             if (!syscache_clear_s(&ver))
 * >>                 break;
 * >>         }
 * >>     }
 * >>     return result;
 * >> }
 *
 * @return: * : At  least  some amount  of  some kind  of  resource (may  have) been
 *              released by some thread since the last time the function was called.
 *              In  this  case  the  caller  should  re-attempt  whatever  lead them
 *              to try and clear caches to reclaim resource (usually memory)
 * @return: 0 : Nothing was released/freed.
 *              In this case, the caller should indicate failure due to
 *              lack of some necessary resource. */
PUBLIC NOBLOCK NONNULL((1)) size_t
NOTHROW(KCALL syscache_clear_s)(syscache_version_t *__restrict pversion) {
	enum { NUM_LASTCHANCE_ATTEMPTS = 32 };
	size_t inside_counter, result;
	uintptr_t old_version, new_version;
	/* Start out by trying to clear system caches ourself. */
	result = syscache_clear();
	if (result)
		return result;
	/* Check if someone succeeded in clearing caches in the mean time. */
	new_version = ATOMIC_READ(syscache_clear_version);
	old_version = *pversion;

	if (old_version != new_version &&
	    old_version < (uintptr_t)-NUM_LASTCHANCE_ATTEMPTS) {
		*pversion = new_version;
		return 1;
	}
	/* There is still the possibility that some other thread is still in
	 * the middle of a call  to `syscache_clear()'. - In this  case,
	 * try  to yield to them so they can finish, and keep on checking if
	 * the number of threads inside decreases. */
	inside_counter = ATOMIC_READ(syscache_clear_isinside);
	if (inside_counter != 0) {
		unsigned int n;
		for (n = 0; n < 256; ++n) {
			unsigned int yield_error;
			yield_error = task_tryyield_or_pause();
			if (ATOMIC_READ(syscache_clear_isinside) < inside_counter)
				break;
			if (yield_error != TASK_TRYYIELD_SUCCESS)
				break; /* Cannot yield... */
		}
	}
	/* Check for a version change one more time. */
	new_version = ATOMIC_READ(syscache_clear_version);
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
		ATOMIC_CMPXCH(syscache_clear_version, new_version, 0);
		*pversion = 0;
		return 1;
	}
	return 0;
}


DECL_END

#endif /* !GUARD_KERNEL_SRC_MEMORY_MMAN_CACHE_C */
