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
#ifndef GUARD_KERNEL_SRC_MEMORY_MODULE_SECTION_CACHE_C
#define GUARD_KERNEL_SRC_MEMORY_MODULE_SECTION_CACHE_C 1
#define __WANT_MODULE_SECTION__ms_dead
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/driver.h>
#include <kernel/mman/cache.h>
#include <kernel/mman/module-section-cache.h>
#include <kernel/mman/module.h>
#include <sched/lockop.h>

#include <hybrid/atomic.h>
#include <hybrid/sync/atomic-lock.h>

DECL_BEGIN

#ifndef __module_section_slist_defined
#define __module_section_slist_defined
SLIST_HEAD(module_section_slist, module_section);
#endif /* !__module_section_slist_defined */

/* [0..n][lock(module_section_cache_lock)][link(cms_cache)]
 * Global cache of Module section  objects. In order to  keep
 * module sections loaded for a while longer, even after  the
 * user has dropped a reference  to them (so-as to allow  for
 * faster lookup if accessed again), a global cache of module
 * sections is kept. This cache is maintained thus, that when
 * the  associated module is destroyed, it will automatically
 * remove  all of  its sections  from this  cache (via async.
 * lockop  operations), meaning that  this cache functions to
 * automatically clean up the sections belonging to destroyed
 * modules. */
PUBLIC struct module_section_list module_section_cache      = LIST_HEAD_INITIALIZER(module_section_cache);
PUBLIC struct atomic_lock /*   */ module_section_cache_lock = ATOMIC_LOCK_INIT;
PUBLIC struct lockop_slist /*  */ module_section_cache_lops = SLIST_HEAD_INITIALIZER(module_section_cache_lops);


/* Clear the global cache of module sections, and return a
 * number representative of an approximation of the amount
 * of memory became available as a result of this. */
DEFINE_SYSTEM_CACHE_CLEAR(module_section_clearcache);
PUBLIC NOBLOCK size_t NOTHROW(KCALL module_section_clearcache)(void) {
	size_t result = 0;
	struct module_section_slist dead;
	if (!module_section_cache_tryacquire())
		goto done;

	/* Remove all objects from the cache. */
	SLIST_INIT(&dead);
	while (!LIST_EMPTY(&module_section_cache)) {
		REF struct module_section *sect;
		sect = LIST_FIRST(&module_section_cache);
		LIST_UNBIND(sect, ms_cache);
		if (ATOMIC_DECFETCH(sect->ms_refcnt) == 0)
			SLIST_INSERT_HEAD(&dead, sect, _ms_dead);
	}
	module_section_cache_release_f();

	/* Destroy dead sections. */
	while (!SLIST_EMPTY(&dead)) {
		struct module_section *sect;
		sect = SLIST_FIRST(&dead);
		SLIST_REMOVE_HEAD(&dead, _ms_dead);
		destroy(sect);
		result += sizeof(struct module_section);
	}
	module_section_cache_reap();
done:
	return result;
}
/************************************************************************/








DECL_END

#endif /* !GUARD_KERNEL_SRC_MEMORY_MODULE_SECTION_CACHE_C */
