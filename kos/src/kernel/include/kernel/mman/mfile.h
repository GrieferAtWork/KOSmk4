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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_MMAN_MFILE_H
#define GUARD_KERNEL_INCLUDE_KERNEL_MMAN_MFILE_H 1

#include <kernel/compiler.h>

#include <kernel/memory.h>
#include <kernel/types.h>
#include <misc/unlockinfo.h>
#include <sched/signal.h>

#include <hybrid/__minmax.h>
#include <hybrid/sequence/list.h>
#include <hybrid/sequence/rbtree.h>
#include <hybrid/sync/atomic-rwlock.h>

#ifdef __CC__
DECL_BEGIN

struct mpart; /* Memory file part. */
struct mfile; /* Memory storage owner/descriptor. */
struct mfile_ops;
struct aio_buffer;
struct aio_pbuffer;

#ifndef __mpart_slist_defined
#define __mpart_slist_defined 1
SLIST_HEAD(mpart_slist, mpart);
#endif /* !__mpart_slist_defined */

/* Block-index within some given mem-file. */
#ifndef __mfile_block_t_defined
#define __mfile_block_t_defined 1
typedef pos_t mfile_block_t;
#endif /* !__mfile_block_t_defined */



/* Special value for `struct mfile::mf_parts': Anonymous file.
 * When this value is used, then attempting to access one of the file's
 * memory parts will yield unique parts for every access, such that
 * writes made to one part will not be mirrored by writes made to another
 * part that (supposedly) describes the same position. */
#define MFILE_PARTS_ANONYMOUS ((struct mpart *)-1)

struct mfile_ops {
	/* [0..1] Finalize + free the given mem-file. */
	NOBLOCK NONNULL((1)) void /*NOTHROW*/ (FCALL *mo_destroy)(struct mfile *__restrict self);
	/* [0..1] Initialize the given mem-part (called whenever a new part is created)
	 * NOTE: This function isn't required to do anything, and may assume that the
	 *       given part is already fully initialized as ABSENT, with the proper
	 *       address range already assigned.
	 * This function is mainly intended to assign physical memory ranges for mem-parts
	 * that directly map physical memory into virtual memory, allowing them to use this
	 * function to assign the proper memory ranges. */
	NOBLOCK NONNULL((1, 2)) void (FCALL *mo_initpart)(struct mfile *__restrict self,
	                                                  struct mpart *__restrict part);
	/* [0..1] Load/initialize the given physical memory buffer (this is the read-from-disk callback)
	 * NOTE: As long as the size of a single file-block is `<= PAGESIZE', this function
	 *       is allowed to assume that `buffer' is aligned by the size of a file-block.
	 *       With file-blocks larger than PAGESIZE, `buffer' may only be aligned by `PAGESIZE' */
	NONNULL((1)) void (KCALL *mo_loadblocks)(struct mfile *__restrict self,
	                                         mfile_block_t first_block,
	                                         physaddr_t buffer, size_t num_blocks);
	/* [0..1] Save/write-back the given physical memory buffer (this is the write-to-disk callback)
	 * NOTE: As long as the size of a single file-block is `<= PAGESIZE', this function
	 *       is allowed to assume that `buffer' is aligned by the size of a file-block.
	 *       With file-blocks larger than PAGESIZE, `buffer' may only be aligned by `PAGESIZE' */
	NONNULL((1)) void (KCALL *mo_saveblocks)(struct mfile *__restrict self,
	                                         mfile_block_t first_block,
	                                         physaddr_t buffer, size_t num_blocks);
	/* [0..1] VIO file operators. (when non-NULL, then this file is backed by VIO,
	 *        and the `mo_loadblocks' and `mo_saveblocks' operators are ignored) */
	struct vio_operators *mo_vio;
};

struct mfile {
	WEAK refcnt_t               mf_refcnt;     /* Reference counter. */
	struct mfile_ops           *mf_ops;        /* [1..1][const] File operators. */
	struct atomic_rwlock        mf_lock;       /* Lock for this file. */
	RBTREE_ROOT(struct mpart)   mf_parts;      /* [0..n][lock(mf_lock)] File parts. */
	struct sig                  mf_initdone;   /* Signal broadcast whenever one of the blocks of one of the
	                                            * contained parts changes state from INIT to LOAD. */
	struct REF mpart_slist      mf_deadparts;  /* [0..n][lock(ATOMIC)] Chain of dead parts (that still have
	                                            * to be removed from `mf_parts'). */
	struct REF mpart_slist      mf_changed;    /* [0..n][lock(ATOMIC)]
	                                            * Chain of references to parts that contain unsaved changes.
	                                            * NOTE: Set to `MFILE_PARTS_ANONYMOUS' if changed parts should
	                                            *       always be ignored unconditionally. This should also be
	                                            *       done when `mf_ops->mo_saveblocks' is `NULL'! */
	unsigned int                mf_blockshift; /* [const] == log2(FILE_BLOCK_SIZE) */
	size_t                      mf_part_amask; /* [const] == MAX(PAGESIZE, 1 << mf_blockshift) - 1
	                                            * This field describes the minimum alignment of file positions
	                                            * described by parts, minus one (meaning it can be used as a
	                                            * mask) */
};

#define MFILE_INIT_EX(refcnt, ops, parts, blockshift)                                  \
	{                                                                                  \
		/* .mf_refcnt     = */ refcnt,                                                 \
		/* .mf_ops        = */ ops,                                                    \
		/* .mf_lock       = */ ATOMIC_RWLOCK_INIT,                                     \
		/* .mf_parts      = */ parts,                                                  \
		/* .mf_initdone   = */ SIG_INIT,                                               \
		/* .mf_deadparts  = */ SLIST_HEAD_INITIALIZER(~),                              \
		/* .mf_changed    = */ SLIST_HEAD_INITIALIZER(~),                              \
		/* .mf_blockshift = */ blockshift,                                             \
		/* .mf_part_amask = */ __hybrid_max_c2(PAGESIZE, (size_t)1 << blockshift) - 1, \
	}
#define MFILE_INIT(ops, blockshift)      MFILE_INIT_EX(1, ops, __NULLPTR, blockshift)
#define MFILE_INIT_ANON(ops, blockshift) MFILE_INIT_EX(1, ops, MFILE_PARTS_ANONYMOUS, blockshift)


/* Allocate physical memory for use with mem-parts created for `self'
 * This function is a more restrictive version of `page_malloc_part(1, max_pages, res_pages)',
 * in that it will also ensure that returned pages are properly aligned, as well
 * as that the given `max_pages' is also properly aligned. Note however that so-long
 * as the size of a single file-block is <= PAGESIZE, this function behaves 100%
 * identical to the above call to `page_malloc_part()' */
FUNDEF NOBLOCK WUNUSED NONNULL((1, 3)) physpage_t
NOTHROW(FCALL mfile_alloc_physmem)(struct mfile *__restrict self,
                                   physpagecnt_t max_pages,
                                   physpagecnt_t *__restrict res_pages);


/* Destroy a given mem-file */
FUNDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL mfile_destroy)(struct mfile *__restrict self);
DEFINE_REFCOUNT_FUNCTIONS(struct mfile, mf_refcnt, mfile_destroy)



#define mfile_isanon(self) ((self)->mf_parts == MFILE_PARTS_ANONYMOUS)

/* Floor- or ceil-align a given `addr' such that it may describe the start/end of a mem-part. */
#define mfile_addr_flooralign(self, addr) (pos_t)((uint64_t)(addr) & ~(self)->mf_part_amask)
#define mfile_addr_ceilalign(self, addr)  (pos_t)(((uint64_t)(addr) + (self)->mf_part_amask) & ~(self)->mf_part_amask)
#define mfile_addr_aligned(self, addr)    (((uint64_t)(addr) & (self)->mf_part_amask) == 0)


/* Reap dead parts of `self' */
FUNDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL _mfile_deadparts_reap)(struct mfile *__restrict self);
#define mfile_deadparts_mustreap(self) \
	(__hybrid_atomic_load((self)->mf_deadparts.slh_first, __ATOMIC_ACQUIRE) != __NULLPTR)
#ifdef __OPTIMIZE_SIZE__
#define mfile_deadparts_reap(self) _mfile_deadparts_reap(self)
#else /* __OPTIMIZE_SIZE__ */
#define mfile_deadparts_reap(self) (void)(!mfile_deadparts_mustreap(self) || (_mfile_deadparts_reap(self), 0))
#endif /* !__OPTIMIZE_SIZE__ */

/* Lock accessor helpers for `struct mfile' */
#define mfile_lock_write(self)      atomic_rwlock_write(&(self)->mf_lock)
#define mfile_lock_write_nx(self)   atomic_rwlock_write_nx(&(self)->mf_lock)
#define mfile_lock_trywrite(self)   atomic_rwlock_trywrite(&(self)->mf_lock)
#define mfile_lock_endwrite(self)   (atomic_rwlock_endwrite(&(self)->mf_lock), mfile_deadparts_reap(self))
#define mfile_lock_endwrite_f(self) atomic_rwlock_endwrite(&(self)->mf_lock)
#define mfile_lock_read(self)       atomic_rwlock_read(&(self)->mf_lock)
#define mfile_lock_read_nx(self)    atomic_rwlock_read_nx(&(self)->mf_lock)
#define mfile_lock_tryread(self)    atomic_rwlock_tryread(&(self)->mf_lock)
#define mfile_lock_endread(self)    (void)(atomic_rwlock_endread(&(self)->mf_lock) && (mfile_deadparts_reap(self), 0))
#define mfile_lock_endread_f(self)  atomic_rwlock_endread(&(self)->mf_lock)
#define mfile_lock_end(self)        (void)(atomic_rwlock_end(&(self)->mf_lock) && (mfile_deadparts_reap(self), 0))
#define mfile_lock_end_f(self)      atomic_rwlock_end(&(self)->mf_lock)
#define mfile_lock_upgrade(self)    atomic_rwlock_upgrade(&(self)->mf_lock)
#define mfile_lock_upgrade_nx(self) atomic_rwlock_upgrade_nx(&(self)->mf_lock)
#define mfile_lock_tryupgrade(self) atomic_rwlock_tryupgrade(&(self)->mf_lock)
#define mfile_lock_downgrade(self)  atomic_rwlock_downgrade(&(self)->mf_lock)
#define mfile_lock_reading(self)    atomic_rwlock_reading(&(self)->mf_lock)
#define mfile_lock_writing(self)    atomic_rwlock_writing(&(self)->mf_lock)
#define mfile_lock_canread(self)    atomic_rwlock_canread(&(self)->mf_lock)
#define mfile_lock_canwrite(self)   atomic_rwlock_canwrite(&(self)->mf_lock)


/* Make the given file anonymous. What this means is that:
 *  - Existing mappings of all mem-parts are altered to point
 *    at anonymous memory files. For this purpose, the nodes of
 *    all existing mappings are altered. (s.a. `mfile_anon')
 *  - The `MPART_F_NO_GLOBAL_REF' flag is set for all parts
 *  - The `mf_parts' and `mf_changed' are set to `MFILE_PARTS_ANONYMOUS'
 *  - The `mf_deadparts' chain is cleared (one last time)
 * The result of all of this is that it is no longer possible to
 * trace back mappings of parts of `self' to that file.
 *
 * This function is called when the given file `self' should be deleted,
 * or has become unavailable for some other reason (e.g. the backing
 * filesystem has been unmounted) */
FUNDEF NONNULL((1)) void FCALL
mfile_makeanon(struct mfile *__restrict self)
		THROWS(E_WOULDBLOCK);

/* Split a potential part at `minaddr' and `maxaddr', and make
 * it so that all parts between that range are removed from the
 * part-tree of `self', by essentially anonymizing them.
 * This function can be used to implement `ftruncate(2)' */
FUNDEF NONNULL((1)) void FCALL
mfile_makeanon_subrange(struct mfile *__restrict self,
                        PAGEDIR_PAGEALIGNED pos_t minaddr,
                        pos_t maxaddr)
		THROWS(E_WOULDBLOCK);


/* Sync unwritten changes made to parts within the given address range.
 * @return: * : The total # of bytes that have been synced. */
FUNDEF NONNULL((1)) pos_t FCALL
mfile_sync(struct mfile *__restrict self)
		THROWS(E_WOULDBLOCK, ...);

/* Check if there are unwritten changes made to any of the parts of `self' */
#define mfile_haschanged(self) \
	(((uintptr_t)__hybrid_atomic_load((self)->mf_changed.slh_first, __ATOMIC_ACQUIRE) - 1) < (uintptr_t)-2)


/* Check `self' for a known mem-part that contains `addr', and (if found),
 * return that part. Otherwise, construct a new part start starts at `addr'
 * and spans at most `max_num_bytes' bytes (less may be returned if another part
 * already exists that describes the mapping above the requested location)
 * NOTE: The caller must ensure that:
 * >> mfile_addr_aligned(addr) && mfile_addr_aligned(max_num_bytes)
 * @return: * : A reference to a part that (at some point in the past) contained
 *              the given `addr'. It may no longer contain that address now as
 *              the result of being truncated since. */
FUNDEF ATTR_RETNONNULL NONNULL((1)) REF struct mpart *FCALL
mfile_getpart(struct mfile *__restrict self,
              PAGEDIR_PAGEALIGNED pos_t addr,
              PAGEDIR_PAGEALIGNED size_t max_num_bytes)
		THROWS(E_WOULDBLOCK, ...);

/* Same as `mfile_getpart()', but may _only_ be used when `self' is an
 * anonymous file! As such, this function is mainly used to allocate
 * parts for `mfile_ndef' and `mfile_zero' */
FUNDEF ATTR_RETNONNULL NONNULL((1)) REF struct mpart *FCALL
mfile_makepart(struct mfile *__restrict self,
               PAGEDIR_PAGEALIGNED pos_t addr,
               PAGEDIR_PAGEALIGNED size_t num_bytes)
		THROWS(E_WOULDBLOCK, ...);


struct mnode;

#ifndef __mnode_slist_defined
#define __mnode_slist_defined 1
SLIST_HEAD(mnode_slist, mnode);
#endif /* !__mnode_slist_defined */

struct mfile_map {
	/* Helper data structure to allocate+lock mem-nodes used
	 * for mapping files into a given memory-manager.
	 *
	 * Usage:
	 * >> void mman_mapat(struct mman *mm, void *addr, size_t num_bytes,
	 * >>                 struct mfile *file, pos_t offset) {
	 * >>     struct mfile_map data;
	 * >>     mfile_map_init_and_acquire(&data, file, offset, num_bytes);
	 * >>     TRY {
	 * >>         while (!mman_lock_available(mm)) {
	 * >>             mfile_map_release(&data);
	 * >>             while (!mman_lock_available(mm))
	 * >>                 task_yield();
	 * >>             mfile_map_acquire(&data);
	 * >>         }
	 * >>     } EXCEPT {
	 * >>         mfile_map_fini(&data);
	 * >>         RETHROW();
	 * >>     }
	 * >>     assert(!mnode_tree_rlocate(mm->mm_mappings, addr, (byte_t *)addr + num_bytes - 1));
	 * >>     while (!SLIST_EMPTY(&data.mfm_nodes)) {
	 * >>         struct mnode *node;
	 * >>         node = SLIST_FIRST(&data.mfm_nodes);
	 * >>         SLIST_REMOVE_HEAD(&data.mfm_nodes, _mn_alloc);
	 * >>         node->mn_flags = MNODE_F_PREAD | MNODE_F_PWRITE | MNODE_F_SHARED;
	 * >>         node->mn_mman  = mm;
	 * >>         LIST_INSERT_HEAD(&node->mn_part->mp_share, node, mn_link);
	 * >>         LIST_ENTRY_UNBOUND_INIT(node, mn_writable);
	 * >>         node->mn_fspath = NULL;
	 * >>         node->mn_fsname = NULL;
	 * >>         node->mn_minaddr += (uintptr_t)addr;
	 * >>         node->mn_maxaddr += (uintptr_t)addr;
	 * >>         mnode_tree_insert(&mm->mm_mappings, node);
	 * >>     }
	 * >>     sync_endwrite(&mm->mm_lock);
	 * >> } */
	struct mfile              *mfm_file;  /* [1..1][const] File from which to allocate nodes. */
	PAGEDIR_PAGEALIGNED pos_t  mfm_addr;  /* [const] Starting address within the source file. */
	PAGEDIR_PAGEALIGNED size_t mfm_size;  /* [const] Total # of bytes that should be mapped. */
	struct mnode_slist         mfm_nodes; /* [0..n][owned] List of nodes.
	                                       *  - Linked via `_mn_alloc'
	                                       *  - Sorted ascendingly by part-offset
	                                       *  - `mn_minaddr' and `mn_maxaddr' are fill in to describe offsets
	                                       *    from the start of the mapping, such that nodes may directly be
	                                       *    inserted into an mman after adding the virtual base-address to
	                                       *    every node's `mn_minaddr' and `mn_maxaddr' field.
	                                       *  - The `mn_partoff' field is filled in correctly
	                                       *  - Each node is holding a lock to its `mn_part' field.
	                                       * The following fields are uninitialized:
	                                       *  - mn_flags, mn_mement, mn_mman, mn_link, mn_writable
	                                       *  - mn_fspath, mn_fsname */
};

/* Lookup/create all parts to span the given address range, as
 * well as allocate 1 mem-node for each part, such that everything
 * put together forms 1 continuous range of fully mappable mem-parts.
 *
 * This function is designed for use in implementing `mman_map()', such
 * that this function is called before trying to acquire a lock to all
 * of the bound mem-part (s.a. `mfile_map_acquire') and the target mman.
 * As such, this API is designed to make it simple to:
 *  - Acquire locks to all of the parts, as well as making
 *    sure that all of the parts still form 1 uninterrupted
 *    mapping over the given address range in its entirety
 *  - Release locks to all of the parts */
FUNDEF NONNULL((1, 2, 5)) void FCALL
mfile_map_init(struct mfile_map *__restrict self,
               struct mfile *__restrict file,
               PAGEDIR_PAGEALIGNED pos_t addr,
               PAGEDIR_PAGEALIGNED size_t num_bytes,
               /*in|out*/ struct mnode_slist *__restrict mnode_free_list)
		THROWS(E_WOULDBLOCK, E_BADALLOC);

/* More efficient combination of `mfile_map_init()' and `mfile_map_acquire()' */
FUNDEF NONNULL((1, 2, 5)) void FCALL
mfile_map_init_and_acquire(struct mfile_map *__restrict self,
                           struct mfile *__restrict file,
                           PAGEDIR_PAGEALIGNED pos_t addr,
                           PAGEDIR_PAGEALIGNED size_t num_bytes,
                           /*in|out*/ struct mnode_slist *__restrict mnode_free_list)
		THROWS(E_WOULDBLOCK, E_BADALLOC);


/* Unlock or re-lock a mem-node allocator (that is: release/re-acquire locks
 * to all of the individual parts pointed to by the nodes allocated by `self')
 * For this purpose, re-locking a mem-node-allocator will (once again) make
 * sure that _all_ parts and nodes form a single, continuous range of mappings
 * as specified in the original call to `mfile_map_init()', leaving no
 * holes anywhere along the way, while the the act of holding locks to all of
 * the parts then guaranties that no new holes can possibly pop up out of the
 * blue. */
FUNDEF NONNULL((1)) void FCALL
mfile_map_acquire(struct mfile_map *__restrict self)
		THROWS(E_WOULDBLOCK, E_BADALLOC);
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mfile_map_release)(struct mfile_map *__restrict self);


/* (try to) do the same as `mfile_map_acquire()', but if doing so cannot be
 * done without blocking on an internal lock, then release all already-acquired
 * locks, invoke the `unlock' callback (if given), wait for the necessary lock
 * to become available, and return `false'.
 * Otherwise, don't invoke `unlock' and return `true'.
 * NOTE: In the case of an exception, `unlock' is guarantied to be invoked
 *       prior to the exception being thrown.
 * @param: mnode_free_list: Required/superfluous mem-nodes are added/removed from
 *                          this list for the purpose of allocation/deallocation. */
FUNDEF WUNUSED NONNULL((1, 3)) __BOOL FCALL
mfile_map_acquire_or_unlock(struct mfile_map *__restrict self,
                            struct unlockinfo *unlock,
                            /*in|out*/ struct mnode_slist *__restrict mnode_free_list)
		THROWS(E_WOULDBLOCK, E_BADALLOC);

/* Finalize a given mem-node-allocator.
 * This function will free (and only free; the caller is responsible to release
 * all of the locks to the individual mem-parts themselves, though for this purpose,
 * `mfile_map_release()' may also be used) all of the (still-)allocated
 * mem-nodes, as can be found apart of the `self->mfm_nodes' list. In addition
 * to freeing all of the container-nodes, this function will also drop 1 reference
 * from the mem-parts pointed-to by each of the nodes.
 * NOTE: This function doesn't necessarily have to be called if the caller was
 *       able to inherit _all_ of the nodes originally allocated (which should
 *       normally be the case when mapping was successful) */
FUNDEF NONNULL((1)) void
NOTHROW(FCALL mfile_map_fini)(struct mfile_map *__restrict self);







/* Read/write raw data to/from a given mem-file. */
FUNDEF NONNULL((1)) void KCALL mfile_read(struct mfile *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t src_offset) THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...);
FUNDEF NONNULL((1)) void KCALL mfile_write(struct mfile *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t dst_offset) THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...);
FUNDEF NONNULL((1)) void KCALL mfile_read_p(struct mfile *__restrict self, physaddr_t dst, size_t num_bytes, pos_t src_offset) THROWS(E_WOULDBLOCK, E_BADALLOC, ...);
FUNDEF NONNULL((1)) void KCALL mfile_write_p(struct mfile *__restrict self, physaddr_t src, size_t num_bytes, pos_t dst_offset) THROWS(E_WOULDBLOCK, E_BADALLOC, ...);
FUNDEF NONNULL((1, 2)) void KCALL mfile_readv(struct mfile *__restrict self, struct aio_buffer const *__restrict buf, size_t buf_offset, size_t num_bytes, pos_t src_offset) THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...);
FUNDEF NONNULL((1, 2)) void KCALL mfile_writev(struct mfile *__restrict self, struct aio_buffer const *__restrict buf, size_t buf_offset, size_t num_bytes, pos_t dst_offset) THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...);
FUNDEF NONNULL((1, 2)) void KCALL mfile_readv_p(struct mfile *__restrict self, struct aio_pbuffer const *__restrict buf, size_t buf_offset, size_t num_bytes, pos_t src_offset) THROWS(E_WOULDBLOCK, E_BADALLOC, ...);
FUNDEF NONNULL((1, 2)) void KCALL mfile_writev_p(struct mfile *__restrict self, struct aio_pbuffer const *__restrict buf, size_t buf_offset, size_t num_bytes, pos_t dst_offset) THROWS(E_WOULDBLOCK, E_BADALLOC, ...);

/* Helpers for directly reading to/from VIO space. */
FUNDEF NONNULL((1)) void KCALL mfile_vio_read(struct mfile *__restrict self, struct mpart *part, USER CHECKED void *dst, size_t num_bytes, pos_t src_offset) THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...);
FUNDEF NONNULL((1)) void KCALL mfile_vio_write(struct mfile *__restrict self, struct mpart *part, USER CHECKED void const *src, size_t num_bytes, pos_t dst_offset) THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...);
FUNDEF NONNULL((1)) void KCALL mfile_vio_read_p(struct mfile *__restrict self, struct mpart *part, physaddr_t dst, size_t num_bytes, pos_t src_offset) THROWS(E_WOULDBLOCK, E_BADALLOC, ...);
FUNDEF NONNULL((1)) void KCALL mfile_vio_write_p(struct mfile *__restrict self, struct mpart *part, physaddr_t src, size_t num_bytes, pos_t dst_offset) THROWS(E_WOULDBLOCK, E_BADALLOC, ...);
FUNDEF NONNULL((1, 3)) void KCALL mfile_vio_readv(struct mfile *__restrict self, struct mpart *part, struct aio_buffer const *__restrict buf, size_t buf_offset, size_t num_bytes, pos_t src_offset) THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...);
FUNDEF NONNULL((1, 3)) void KCALL mfile_vio_writev(struct mfile *__restrict self, struct mpart *part, struct aio_buffer const *__restrict buf, size_t buf_offset, size_t num_bytes, pos_t dst_offset) THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...);
FUNDEF NONNULL((1, 3)) void KCALL mfile_vio_readv_p(struct mfile *__restrict self, struct mpart *part, struct aio_pbuffer const *__restrict buf, size_t buf_offset, size_t num_bytes, pos_t src_offset) THROWS(E_WOULDBLOCK, E_BADALLOC, ...);
FUNDEF NONNULL((1, 3)) void KCALL mfile_vio_writev_p(struct mfile *__restrict self, struct mpart *part, struct aio_pbuffer const *__restrict buf, size_t buf_offset, size_t num_bytes, pos_t dst_offset) THROWS(E_WOULDBLOCK, E_BADALLOC, ...);

/* Builtin mem files */
DATDEF struct mfile /*    */ mfile_phys;     /* Physical memory access (file position is physical memory address) */
DATDEF struct mfile_ops /**/ mfile_phys_ops; /* ... */
#ifndef __mfile_ndef_defined
#define __mfile_ndef_defined 1
DATDEF struct mfile /*    */ mfile_ndef;     /* Random, uninitialized, anonymous memory. */
#endif /* !__mfile_ndef_defined */
DATDEF struct mfile_ops /**/ mfile_ndef_ops; /* ... */
#ifndef __mfile_zero_defined
#define __mfile_zero_defined 1
DATDEF struct mfile /*    */ mfile_zero;     /* Zero-initialized, anonymous memory. */
#endif /* !__mfile_zero_defined */
DATDEF struct mfile_ops /**/ mfile_zero_ops; /* ... */

/* Fallback files for anonymous memory. These behave the same as `mfile_zero',
 * but one exists for every possible `mf_blockshift' (where the index into this
 * array is equal to that file's `mf_blockshift' value)
 * As such, these files are used by `mfile_makeanon()' as replacement mappings
 * of the original file. */
DATDEF struct mfile /*    */ mfile_anon[BITSOF(void *)];
DATDEF struct mfile_ops /**/ mfile_anon_ops[BITSOF(void *)];


DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_MMAN_MFILE_H */
