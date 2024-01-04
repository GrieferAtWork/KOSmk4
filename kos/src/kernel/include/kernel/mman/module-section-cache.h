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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_MMAN_MODULE_SECTION_CACHE_H
#define GUARD_KERNEL_INCLUDE_KERNEL_MMAN_MODULE_SECTION_CACHE_H 1

#include <kernel/compiler.h>

#include <kernel/types.h>

#include <hybrid/sequence/list.h>
#include <hybrid/sched/atomic-lock.h>

#include <kos/lockop.h>

/* Module section cache. */

#ifdef __CC__
DECL_BEGIN

struct module_section;

#ifndef __module_section_list_defined
#define __module_section_list_defined
LIST_HEAD(module_section_list, module_section);
#endif /* !__module_section_list_defined */

/* [0..n][lock(module_section_cache_lock)][link(ms_cache)]
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
DATDEF struct REF module_section_list module_section_cache;
DATDEF struct atomic_lock /*       */ module_section_cache_lock;
DATDEF struct lockop_slist /*      */ module_section_cache_lops;
#define _module_section_cache_reap()      _lockop_reap_atomic_lock(&module_section_cache_lops, &module_section_cache_lock)
#define module_section_cache_reap()       lockop_reap_atomic_lock(&module_section_cache_lops, &module_section_cache_lock)
#define module_section_cache_tryacquire() atomic_lock_tryacquire(&module_section_cache_lock)
#define module_section_cache_acquire()    atomic_lock_acquire(&module_section_cache_lock)
#define module_section_cache_acquire_nx() atomic_lock_acquire_nx(&module_section_cache_lock)
#define module_section_cache_release()    (atomic_lock_release(&module_section_cache_lock), module_section_cache_reap())
#define _module_section_cache_release()  atomic_lock_release(&module_section_cache_lock)
#define module_section_cache_acquired()   atomic_lock_acquired(&module_section_cache_lock)
#define module_section_cache_available()  atomic_lock_available(&module_section_cache_lock)
#define module_section_cache_waitfor()    atomic_lock_waitfor(&module_section_cache_lock)
#define module_section_cache_waitfor_nx() atomic_lock_waitfor_nx(&module_section_cache_lock)

DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_MMAN_MODULE_SECTION_CACHE_H */
