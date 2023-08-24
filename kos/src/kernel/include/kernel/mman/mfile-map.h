/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_MMAN_MFILE_MAP_H
#define GUARD_KERNEL_INCLUDE_KERNEL_MMAN_MFILE_MAP_H 1

#include <kernel/compiler.h>

#include <kernel/memory.h>
#include <kernel/types.h>
#include <kernel/mman/mpart.h> /* `struct mpart_setcore_data', `struct mpart_unsharecow_data' */
#include <misc/unlockinfo.h>

#include <hybrid/sequence/list.h>

#ifdef __CC__
DECL_BEGIN

struct mnode;

#ifndef __mnode_slist_defined
#define __mnode_slist_defined
SLIST_HEAD(mnode_slist, mnode);
#endif /* !__mnode_slist_defined */

struct mfile_map {
	/* Helper  data  structure to  allocate+lock mem-nodes
	 * used for mapping files into a given memory-manager.
	 *
	 * Usage:
	 * >> void mman_mapat(struct mman *mm, void *addr, size_t num_bytes,
	 * >>                 struct mfile *file, pos_t offset) {
	 * >>     struct mfile_map map;
	 * >>     mfile_map_init_and_acquire(&map, file, offset, num_bytes);
	 * >>     TRY {
	 * >>         while (!mman_lock_tryacquire(mm)) {
	 * >>             mfile_map_release(&map);
	 * >>             while (!mman_lock_available(mm))
	 * >>                 task_yield();
	 * >>             mfile_map_acquire(&map);
	 * >>         }
	 * >>     } EXCEPT {
	 * >>         mfile_map_fini(&map);
	 * >>         RETHROW();
	 * >>     }
	 * >>     assert(!mnode_tree_rlocate(mm->mm_mappings, addr, (byte_t *)addr + num_bytes - 1));
	 * >>     while (!SLIST_EMPTY(&map.mfm_nodes)) {
	 * >>         struct mnode *node;
	 * >>         node = SLIST_FIRST(&map.mfm_nodes);
	 * >>         SLIST_REMOVE_HEAD(&map.mfm_nodes, _mn_alloc);
	 * >>         node->mn_flags = MNODE_F_PREAD | MNODE_F_PWRITE | MNODE_F_SHARED;
	 * >>         node->mn_mman  = mm;
	 * >>         LIST_INSERT_HEAD(&node->mn_part->mp_share, node, mn_link);
	 * >>         LIST_ENTRY_UNBOUND_INIT(&node->mn_writable);
	 * >>         node->mn_fspath = NULL;
	 * >>         node->mn_fsname = NULL;
	 * >>         node->mn_module = NULL;
	 * >>         node->mn_minaddr += (uintptr_t)addr;
	 * >>         node->mn_maxaddr += (uintptr_t)addr;
	 * >>         mman_mappings_insert(mm, node);
	 * >>         mpart_lock_release(node->mn_part);
	 * >>     }
	 * >>     mman_lock_release(mm);
	 * >>     mfile_map_fini(&map);
	 * >> } */
	struct mfile                *mfm_file;  /* [1..1][const] File from which to allocate nodes. */
	PAGEDIR_PAGEALIGNED pos_t    mfm_addr;  /* [const] Starting address within the source file. */
	PAGEDIR_PAGEALIGNED size_t   mfm_size;  /* [const] Total # of bytes that should be mapped. */
	unsigned int                 mfm_prot;  /* Set of `0 | PROT_WRITE | PROT_SHARED | PROT_FORCEWRITE' (other flags are silently ignored) */
	unsigned int                 mfm_flags; /* Set of `0 | MAP_POPULATE | MAP_NONBLOCK' (other flags are silently ignored)
	                                         * MAP_POPULATE -- Ensure  the following conditions  when locking data  parts:
	                                         *                  - mpart_setcore_or_unlock()
	                                         *                  - mpart_load_or_unlock()   (within the range being mapped)
	                                         *                  - mpart_unsharecow_or_unlock() (only if `mfm_prot & PROT_WRITE')
	                                         * MAP_NONBLOCK -- The  `MAP_POPULATE' flag  may be  ignored if  page init of
	                                         *                 previously not loaded  pages would  block. Currently,  all
	                                         *                 page initializers are assumed to block, with the exception
	                                         *                 of those that have a  NULL-init callback, and the  builtin
	                                         *                 file types known  to be  non-blocking (e.g.  `mfile_zero') */
	struct mnode_slist           mfm_nodes; /* [0..n][owned] List of nodes.
	                                         *  - Linked via `_mn_alloc'
	                                         *  - Sorted ascendingly by part-offset
	                                         *  - `mn_minaddr' and `mn_maxaddr' are fill in to describe  offsets
	                                         *    from the start of the mapping, such that nodes may directly be
	                                         *    inserted into an mman after adding the virtual base-address to
	                                         *    every node's `mn_minaddr' and `mn_maxaddr' field.
	                                         *  - The `mn_partoff' field is filled in correctly
	                                         *  - Each node is holding a lock to its `mn_part' field.
	                                         * The following fields are uninitialized:
	                                         *  - mn_flags, mn_mement, mn_mman, mn_link, mn_writable
	                                         *  - mn_fspath, mn_fsname, mn_module */
	struct mnode_slist           mfm_flist; /* [0..n][owned] Internal list of free nodes.
	                                         * Required/superfluous mem-nodes are added/removed from
	                                         * this list for the purpose of allocation/deallocation.
	                                         * NOTE: Nodes in this list are free'd using `kfree()'!
	                                         *       No mcorepart support here! */
	struct mpart_setcore_data    mfm_scdat; /* [owned] Internal data used for calling `mpart_setcore_or_unlock()' */
	struct mpart_unsharecow_data mfm_ucdat; /* [owned] Internal data used for calling `mpart_unsharecow_or_unlock()' */
};

/* Lookup/create all  parts  to  span the  given  address  range,  as
 * well  as allocate 1  mem-node for each  part, such that everything
 * put together forms 1 continuous range of fully mappable mem-parts.
 *
 * This function is designed for use in implementing `mman_map()',  such
 * that  this function is called before trying  to acquire a lock to all
 * of the bound mem-part (s.a. `mfile_map_acquire') and the target mman.
 * As such, this API is designed to make it simple to:
 *  - Acquire  locks to all of the parts, as well as making
 *    sure that all of the parts still form 1 uninterrupted
 *    mapping over the given address range in its entirety
 *  - Release locks to all of the parts
 * @param: prot:  Set of `0 | PROT_WRITE | PROT_SHARED | PROT_FORCEWRITE' (other flags are silently ignored)
 * @param: flags: Set of `0 | MAP_POPULATE | MAP_NONBLOCK' (other flags are silently ignored) */
#ifdef __INTELLISENSE__
BLOCKING_IF(flags & MAP_POPULATE) NONNULL((1, 2)) void
mfile_map_init_and_acquire(struct mfile_map *__restrict self,
                           struct mfile *__restrict file,
                           PAGEDIR_PAGEALIGNED pos_t addr,
                           PAGEDIR_PAGEALIGNED size_t num_bytes,
                           unsigned int prot, unsigned int flags)
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_FSERROR_READONLY, ...);

/* Same as `mfile_map_init_and_acquire()', but don't acquire an initial lock. */
BLOCKING_IF(flags & MAP_POPULATE) NONNULL((1, 2)) void
mfile_map_init(struct mfile_map *__restrict self,
               struct mfile *__restrict file,
               PAGEDIR_PAGEALIGNED pos_t addr,
               PAGEDIR_PAGEALIGNED size_t num_bytes,
               unsigned int prot, unsigned int flags)
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_FSERROR_READONLY, ...);
#else /* __INTELLISENSE__ */
#define mfile_map_init_and_acquire(self, file, addr, num_bytes, prot, flags) \
	((self)->mfm_file = (file), (self)->mfm_addr = (addr),                   \
	 (self)->mfm_size = (num_bytes), (self)->mfm_prot = (prot),              \
	 (self)->mfm_flags = (flags), SLIST_INIT(&(self)->mfm_flist),            \
	 _mfile_map_init_and_acquire(self))
#define mfile_map_init(self, file, addr, num_bytes, prot, flags)           \
	(mfile_map_init_and_acquire(self, file, addr, num_bytes, prot, flags), \
	 mfile_map_release(self))
#endif /* !__INTELLISENSE__ */
FUNDEF BLOCKING_IF(self->mfm_flags & MAP_POPULATE) NONNULL((1)) void FCALL
_mfile_map_init_and_acquire(struct mfile_map *__restrict self)
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_FSERROR_READONLY, ...);
#define _mfile_map_init(self) \
	(_mfile_map_init_and_acquire(self), mfile_map_release(self))




/* Unlock or re-lock a mem-node  allocator (that is: release/re-acquire  locks
 * to all of the individual parts pointed to by the nodes allocated by `self')
 * For this purpose,  re-locking a mem-node-allocator  will (once again)  make
 * sure that _all_ parts and nodes form a single, continuous range of mappings
 * as  specified  in  the  original  call  to  `mfile_map_init()',  leaving no
 * holes  anywhere along the way, while the the act of holding locks to all of
 * the  parts then guaranties that no new holes can possibly pop up out of the
 * blue. */
#define mfile_map_acquire(self) \
	do {                        \
	} while (!mfile_map_acquire_or_unlock(self, __NULLPTR))
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mfile_map_release)(struct mfile_map *__restrict self);


/* (try to) do  the same as  `mfile_map_acquire()', but if  doing so cannot  be
 * done without blocking on an internal lock, then release all already-acquired
 * locks, invoke the `unlock' callback (if given), wait for the necessary  lock
 * to become available, and return `false'.
 * Otherwise, don't invoke `unlock' and return `true'.
 * NOTE: In the case of an exception, `unlock' is guarantied to be invoked
 *       prior to the exception being thrown. */
FUNDEF BLOCKING_IF(self->mfm_flags & MAP_POPULATE) WUNUSED NONNULL((1)) __BOOL FCALL
mfile_map_acquire_or_unlock(struct mfile_map *__restrict self,
                            struct unlockinfo *unlock)
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_FSERROR_READONLY, ...);

/* Essentially does the same as `mfile_map_acquire_or_unlock()', however the
 * caller must already be holding locks  to every mem-part mapped by  `self'
 * However,  use of `mfile_map_acquire_or_unlock()' is still more efficient,
 * since that function can do some tricks which this one can't (see impl)! */
FUNDEF BLOCKING_IF(self->mfm_flags & MAP_POPULATE) WUNUSED NONNULL((1)) __BOOL FCALL
mfile_map_reflow_or_unlock(struct mfile_map *__restrict self,
                           struct unlockinfo *unlock)
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_FSERROR_READONLY, ...);

/* Finalize a given mem-node-allocator.
 * This function will free (and  only free; the caller is  responsible
 * to release all of the locks to the individual mem-parts themselves,
 * though for this  purpose, `mfile_map_release()' may  also be  used)
 * all  of the (still-)allocated  mem-nodes, as can  be found apart of
 * the  `self->mfm_nodes'  list. In  addition  to freeing  all  of the
 * container-nodes, this function will also drop 1 reference from  the
 * mem-parts pointed-to by each of the nodes.
 * NOTE: This function doesn't necessarily have to be called if the caller was
 *       able to inherit _all_ of the nodes originally allocated (which should
 *       normally be the case when mapping was successful) */
FUNDEF NONNULL((1)) void
NOTHROW(FCALL mfile_map_fini)(struct mfile_map *__restrict self);





/* Same as all of the  functions above, but includes  support
 * for creating reserved nodes when `self->mfm_file == NULL'. */
#define mfile_map_isreserved(self) ((self)->mfm_file == __NULLPTR)
#ifdef __INTELLISENSE__
BLOCKING_IF(file && (flags & MAP_POPULATE)) NONNULL((1)) void
mfile_map_init_and_acquire_or_reserved(struct mfile_map *__restrict self,
                                       struct mfile *file,
                                       PAGEDIR_PAGEALIGNED pos_t addr,
                                       PAGEDIR_PAGEALIGNED size_t num_bytes,
                                       unsigned int prot, unsigned int flags)
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_FSERROR_READONLY);
BLOCKING_IF(file && (flags & MAP_POPULATE)) NONNULL((1)) void FCALL
mfile_map_init_or_reserved(struct mfile_map *__restrict self,
                           struct mfile *file,
                           PAGEDIR_PAGEALIGNED pos_t addr,
                           PAGEDIR_PAGEALIGNED size_t num_bytes,
                           unsigned int prot, unsigned int flags)
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_FSERROR_READONLY);
#else /* __INTELLISENSE__ */
#define mfile_map_init_and_acquire_or_reserved(self, file, addr, num_bytes, prot, flags) \
	((self)->mfm_file = (file), (self)->mfm_addr = (addr),                               \
	 (self)->mfm_size = (num_bytes), (self)->mfm_prot = (prot),                          \
	 (self)->mfm_flags = (flags), SLIST_INIT(&(self)->mfm_flist),                        \
	 _mfile_map_init_and_acquire_or_reserved(self))
#define mfile_map_init_or_reserved(self, file, addr, num_bytes, prot, flags)           \
	(mfile_map_init_and_acquire_or_reserved(self, file, addr, num_bytes, prot, flags), \
	 mfile_map_release_or_reserved(self))
#endif /* !__INTELLISENSE__ */
FUNDEF BLOCKING_IF(self->mfm_file != NULL && self->mfm_flags & MAP_POPULATE) NONNULL((1)) void FCALL
_mfile_map_init_and_acquire_or_reserved(struct mfile_map *__restrict self)
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_FSERROR_READONLY, ...);
#define _mfile_map_init_or_reserved(self) \
	(_mfile_map_init_and_acquire_or_reserved(self), mfile_map_release_or_reserved(self))
#define mfile_map_acquire_or_reserved(self) \
	do {                        \
	} while (!mfile_map_acquire_or_unlock_or_reserved(self, __NULLPTR))
#define mfile_map_release_or_reserved(self) \
	(void)(mfile_map_isreserved(self) || (mfile_map_release(self), 1))
#define mfile_map_acquire_or_unlock_or_reserved(self, unlock) \
	(mfile_map_isreserved(self) || mfile_map_acquire_or_unlock(self, unlock))
#define mfile_map_reflow_or_unlock_or_reserved(self, unlock) \
	(mfile_map_isreserved(self) || mfile_map_reflow_or_unlock(self, unlock))
FUNDEF NONNULL((1)) void
NOTHROW(FCALL mfile_map_fini_or_reserved)(struct mfile_map *__restrict self);




/* Helpers for constructing unlockinfo objects that invoke `mfile_map_release()'  when
 * triggering an unlock. - Mainly intended for use with `mman_getunmapped_or_unlock()'
 * once both mem-parts and the target mman have been locked in `mman_map()' */
struct mfile_map_with_unlockinfo
#ifdef __cplusplus
    : unlockinfo /* Underlying unlock info */
#endif /* __cplusplus */
{
#ifndef __cplusplus
	struct unlockinfo mmwu_info; /* Underlying unlock info */
#endif /* __cplusplus */
	struct mfile_map  mmwu_map;  /* MFile mapping. */
};

/* Fallback to-be used with `mfile_map_with_unlockinfo::mmwu_info::ui_unlock'
 * When invoked, will call `mfile_map_release()' on the contained  mfile-map. */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mfile_map_with_unlockinfo_unlock)(struct unlockinfo *__restrict self);
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mfile_map_with_unlockinfo_unlock_or_reserved)(struct unlockinfo *__restrict self);


DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_MMAN_MFILE_MAP_H */
