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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_FS_ALLNODES_H
#define GUARD_KERNEL_INCLUDE_KERNEL_FS_ALLNODES_H 1

#include <kernel/compiler.h>

#include <kernel/types.h>

#include <hybrid/__atomic.h>
#include <hybrid/sequence/list.h>
#include <hybrid/sched/atomic-lock.h>

#include <kos/lockop.h>

#ifndef REF_IF
#define REF_IF __REF_IF
#endif /* !REF_IF */

#ifdef __CC__
DECL_BEGIN

/* All file-nodes and/or super-blocks API */

struct fnode;
struct fsuper;

#ifndef __fnode_list_defined
#define __fnode_list_defined
LIST_HEAD(fnode_list, fnode);
#endif /* !__fnode_list_defined */
#ifndef __fsuper_list_defined
#define __fsuper_list_defined
LIST_HEAD(fsuper_list, fsuper);
#endif /* !__fsuper_list_defined */


/************************************************************************/
/* List of all file-nodes (excluding superblock root nodes)             */
/************************************************************************/

/* [0..n][lock(fallnodes_list)] List of all file nodes */
REF_IF([*]._fnode_file_ mf_flags & MFILE_FN_GLOBAL_REF)
DATDEF struct fnode_list fallnodes_list;

/* Lock for `fallnodes_list' */
DATDEF struct atomic_lock fallnodes_lock;

/* Lock operations for `fallnodes_list' */
DATDEF struct lockop_slist fallnodes_lockops;

/* Helper macros for working with `fallnodes_lock' */
#define _fallnodes_reap()      _lockop_reap_atomic_lock(&fallnodes_lockops, &fallnodes_lock)
#define fallnodes_reap()       lockop_reap_atomic_lock(&fallnodes_lockops, &fallnodes_lock)
#define fallnodes_mustreap()   lockop_mustreap(&fallnodes_lockops)
#define fallnodes_tryacquire() atomic_lock_tryacquire(&fallnodes_lock)
#define fallnodes_acquire()    atomic_lock_acquire(&fallnodes_lock)
#define fallnodes_acquire_nx() atomic_lock_acquire_nx(&fallnodes_lock)
#define _fallnodes_release()   atomic_lock_release(&fallnodes_lock)
#define fallnodes_release()    (atomic_lock_release(&fallnodes_lock), fallnodes_reap())
#define fallnodes_acquired()   atomic_lock_acquired(&fallnodes_lock)
#define fallnodes_available()  atomic_lock_available(&fallnodes_lock)
#define fallnodes_waitfor()    atomic_lock_waitfor(&fallnodes_lock)
#define fallnodes_waitfor_nx() atomic_lock_waitfor_nx(&fallnodes_lock)

/* Insert/remove nodes from/into `fallnodes_list' */
#define fallnodes_insert(node) (LIST_INSERT_HEAD(&fallnodes_list, node, fn_allnodes), __fallnodes_size_inc())
#define fallnodes_remove(node) (__fallnodes_size_dec(), LIST_REMOVE(node, fn_allnodes))
#define __fallnodes_size_inc() (void)0
#define __fallnodes_size_dec() (void)0
#define _fallnodes_getsize()   LIST_COUNT(&fallnodes_list, fn_allnodes)
#define fallnodes_getsize()                                   \
	({                                                        \
		size_t __fas_res;                                     \
		fallnodes_acquire();                                  \
		LIST_COUNT(&fallnodes_list, &__fas_res, fn_allnodes); \
		fallnodes_release();                                  \
		__fas_res;                                            \
	})



/************************************************************************/
/* List of all super blocks                                             */
/************************************************************************/

/* [0..n][lock(fallsuper_list)] List of all super blocks */
REF_IF([*].fs_root._fdirnode_node_ _fnode_file_ mf_flags & MFILE_FN_GLOBAL_REF)
DATDEF struct fsuper_list fallsuper_list;

/* Lock for `fallsuper_list' */
DATDEF struct atomic_lock fallsuper_lock;

/* Lock operations for `fallsuper_list' */
DATDEF struct lockop_slist fallsuper_lockops;

/* Helper macros for working with `fallsuper_lock' */
#define _fallsuper_reap()      _lockop_reap_atomic_lock(&fallsuper_lockops, &fallsuper_lock)
#define fallsuper_reap()       lockop_reap_atomic_lock(&fallsuper_lockops, &fallsuper_lock)
#define fallsuper_mustreap()   lockop_mustreap(&fallsuper_lockops)
#define fallsuper_tryacquire() atomic_lock_tryacquire(&fallsuper_lock)
#define fallsuper_acquire()    atomic_lock_acquire(&fallsuper_lock)
#define fallsuper_acquire_nx() atomic_lock_acquire_nx(&fallsuper_lock)
#define _fallsuper_release()   atomic_lock_release(&fallsuper_lock)
#define fallsuper_release()    (atomic_lock_release(&fallsuper_lock), fallsuper_reap())
#define fallsuper_acquired()   atomic_lock_acquired(&fallsuper_lock)
#define fallsuper_available()  atomic_lock_available(&fallsuper_lock)
#define fallsuper_waitfor()    atomic_lock_waitfor(&fallsuper_lock)
#define fallsuper_waitfor_nx() atomic_lock_waitfor_nx(&fallsuper_lock)

/* Insert/remove superblocks from/into `fallsuper_list' */
#define fallsuper_insert(super) (LIST_INSERT_HEAD(&fallsuper_list, super, fs_root.fn_allsuper), __fallsuper_size_inc())
#define fallsuper_remove(super) (__fallsuper_size_dec(), LIST_REMOVE(super, fs_root.fn_allsuper))
#define __fallsuper_size_inc()  (void)0
#define __fallsuper_size_dec()  (void)0
#define _fallsuper_getsize()    LIST_COUNT(&fallsuper_list, fs_root.fn_allsuper)
#define fallsuper_getsize()                                           \
	({                                                                \
		size_t __fas_res;                                             \
		fallsuper_acquire();                                          \
		LIST_COUNT(&fallsuper_list, &__fas_res, fs_root.fn_allsuper); \
		fallsuper_release();                                          \
		__fas_res;                                                    \
	})



/************************************************************************/
/* List of all super blocks with modified nodes (for `sync(2)')         */
/************************************************************************/

/* [0..n][lock(fchangedsuper_list)] List of all changed super blocks */
DATDEF struct REF fsuper_list fchangedsuper_list;

/* Lock for `fchangedsuper_list' */
DATDEF struct atomic_lock fchangedsuper_lock;

/* Lock operations for `fchangedsuper_list' */
DATDEF struct lockop_slist fchangedsuper_lockops;

/* Helper macros for working with `fchangedsuper_lock' */
#define _fchangedsuper_reap()      _lockop_reap_atomic_lock(&fchangedsuper_lockops, &fchangedsuper_lock)
#define fchangedsuper_reap()       lockop_reap_atomic_lock(&fchangedsuper_lockops, &fchangedsuper_lock)
#define fchangedsuper_mustreap()   lockop_mustreap(&fchangedsuper_lockops)
#define fchangedsuper_tryacquire() atomic_lock_tryacquire(&fchangedsuper_lock)
#define fchangedsuper_acquire()    atomic_lock_acquire(&fchangedsuper_lock)
#define fchangedsuper_acquire_nx() atomic_lock_acquire_nx(&fchangedsuper_lock)
#define _fchangedsuper_release()   atomic_lock_release(&fchangedsuper_lock)
#define fchangedsuper_release()    (atomic_lock_release(&fchangedsuper_lock), fchangedsuper_reap())
#define fchangedsuper_acquired()   atomic_lock_acquired(&fchangedsuper_lock)
#define fchangedsuper_available()  atomic_lock_available(&fchangedsuper_lock)
#define fchangedsuper_waitfor()    atomic_lock_waitfor(&fchangedsuper_lock)
#define fchangedsuper_waitfor_nx() atomic_lock_waitfor_nx(&fchangedsuper_lock)

/* Insert/remove superblocks from/into `fchangedsuper_list' */
#define fchangedsuper_insert(super) (LIST_INSERT_HEAD(&fchangedsuper_list, super, fs_changedsuper), __fchangedsuper_size_inc())
#define fchangedsuper_remove(super) (__fchangedsuper_size_dec(), LIST_REMOVE(super, fs_changedsuper))
#define __fchangedsuper_size_inc()  (void)0
#define __fchangedsuper_size_dec()  (void)0
#define _fchangedsuper_getsize()    LIST_COUNT(&fchangedsuper_list, fs_changedsuper)
#define fchangedsuper_getsize()                                       \
	({                                                                \
		size_t __fcs_res;                                             \
		fchangedsuper_acquire();                                      \
		LIST_COUNT(&fchangedsuper_list, &__fcs_res, fs_changedsuper); \
		fchangedsuper_release();                                      \
		__fcs_res;                                                    \
	})




DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_FS_ALLNODES_H */
