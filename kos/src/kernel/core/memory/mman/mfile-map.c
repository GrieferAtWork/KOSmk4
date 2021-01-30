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
#ifndef GUARD_KERNEL_SRC_MEMORY_MFILE_MAP_C
#define GUARD_KERNEL_SRC_MEMORY_MFILE_MAP_C 1
#define __WANT_MNODE__mn_alloc
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/malloc.h>
#include <kernel/mman.h>
#include <kernel/mman/mfile.h>
#include <kernel/mman/mm-map.h>
#include <kernel/mman/mnode.h>
#include <kernel/mman/mpart.h>
#include <sched/task.h>

#include <hybrid/align.h>

#include <kos/except.h>

#include <assert.h>
#include <string.h>

DECL_BEGIN

/* Check if 2 given ranges overlap (that is: share at least 1 common address) */
#define RANGE_OVERLAPS(a_min, a_max, b_min, b_max) \
	((a_max) >= (b_min) && (a_min) <= (b_max))

#ifndef NDEBUG
#define DBG_memset(dst, byte, num_bytes) memset(dst, byte, num_bytes)
#else /* !NDEBUG */
#define DBG_memset(dst, byte, num_bytes) (void)0
#endif /* NDEBUG */




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
PUBLIC NONNULL((1)) void
NOTHROW(FCALL mfile_map_fini)(struct mfile_map *__restrict self) {
	struct mnode *iter, *next;
	iter = SLIST_FIRST(&self->mfm_nodes);
	while (iter) {
		next = SLIST_NEXT(iter, _mn_alloc);
		decref(iter->mn_part);
		kfree(iter);
		iter = next;
	}
	/* Free all nodes still apart of the free-list. */
	iter = SLIST_FIRST(&self->mfm_flist);
	while (iter) {
		next = SLIST_NEXT(iter, _mn_alloc);
		kfree(iter);
		iter = next;
	}
}





/* Go over all parts and make use of `mpart_loadsome_or_unlock()' or
 * `mpart_unsharecow_or_unlock()' (and `mpart_split()' if necessary)
 * in order to populate+unshare (if PROT_WRITE was set) the file-range
 * that our caller is intending to map. */
PRIVATE WUNUSED NONNULL((1)) bool FCALL
mfile_map_populate_or_unlock(struct mfile_map *__restrict self)
		THROWS(E_WOULDBLOCK, E_BADALLOC) {

	/* TODO */
	(void)self;
	COMPILER_IMPURE();

	return true;
}



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
PUBLIC NONNULL((1)) void FCALL
_mfile_map_init_and_acquire(struct mfile_map *__restrict self)
		THROWS(E_WOULDBLOCK, E_BADALLOC) {
	struct mfile *file;
	struct mnode *node;
	REF struct mpart *part;
	pos_t block_aligned_addr;
	size_t block_aligned_size;
	file = self->mfm_file;
	assert(self->mfm_size != 0);
	assert(IS_ALIGNED(self->mfm_addr, PAGESIZE));
	assert(IS_ALIGNED(self->mfm_size, PAGESIZE));
	block_aligned_addr = self->mfm_addr & ~file->mf_part_amask;
	block_aligned_size = self->mfm_size + (size_t)(self->mfm_addr - block_aligned_addr);
	block_aligned_size = (block_aligned_size + file->mf_part_amask) & ~file->mf_part_amask;

	SLIST_INIT(&self->mfm_nodes);
	/* Allocate the initial node! */
	node = SLIST_FIRST(&self->mfm_flist);
	if (node != NULL) {
		SLIST_REMOVE_HEAD(&self->mfm_flist, _mn_alloc);
	} else {
		node = (struct mnode *)kmalloc(sizeof(struct mnode),
		                               GFP_LOCKED | GFP_PREFLT);
	}
	TRY {
again_getpart:
		part = mfile_getpart(file,
		                     block_aligned_addr,
		                     block_aligned_size);
		TRY {
			mpart_lock_acquire(part);
			/* re-check if `part' contains `block_aligned_addr'. */
			if (!(mpart_getminaddr(part) <= block_aligned_addr &&
			      mpart_getmaxaddr(part) >= block_aligned_addr)) {
				mpart_lock_release(part);
				decref(part);
				goto again_getpart;
			}
		} EXCEPT {
			decref(part);
			RETHROW();
		}
	} EXCEPT {
		kfree(node);
		DBG_memset(self, 0xcc, sizeof(*self));
		RETHROW();
	}
	/* Initialize the initial node. */
	SLIST_INSERT(&self->mfm_nodes, node, _mn_alloc);
	node->mn_minaddr = (byte_t *)0;
	node->mn_maxaddr = (byte_t *)self->mfm_size - 1;
	DBG_memset(&node->mn_flags, 0xcc, sizeof(node->mn_flags));
	DBG_memset(&node->mn_mement, 0xcc, sizeof(node->mn_mement));
	/*DBG_memset(&node->mn_mman, 0xcc, sizeof(node->mn_mman));*/ /* Used to chain nodes. */
	node->mn_part    = part; /* Inherit reference */
	node->mn_partoff = (mpart_reladdr_t)(self->mfm_addr - mpart_getminaddr(part));
	DBG_memset(&node->mn_link, 0xcc, sizeof(node->mn_link));
	DBG_memset(&node->mn_writable, 0xcc, sizeof(node->mn_writable));
	DBG_memset(&node->mn_fspath, 0xcc, sizeof(node->mn_fspath));
	DBG_memset(&node->mn_fsname, 0xcc, sizeof(node->mn_fsname));

	/* Check if `part' already contains the whole mapping needed by `node' */
	if (mpart_getmaxaddr(part) >= (self->mfm_addr + self->mfm_size - 1)) {
		/* Populate the mapping if the callers wants this. */
		if (self->mfm_flags & MAP_POPULATE) {
			TRY {
				if (!mfile_map_populate_or_unlock(self))
					goto again_acquire;
			} EXCEPT {
				mfile_map_fini(self);
				DBG_memset(self, 0xcc, sizeof(*self));
				RETHROW();
			}
		}
		/* done! */
		return;
	}

	/* Failed to acquire all required parts. - Unlock our's, and re-lock everything
	 * NOTE: This should never ~really~ happen when `file' is anonymous, though... */
	mpart_lock_release(part);
again_acquire:
	TRY {
		mfile_map_acquire(self);
		/* Populate the mapping if the callers wants this. */
		if (self->mfm_flags & MAP_POPULATE) {
			if (!mfile_map_populate_or_unlock(self))
				goto again_acquire;
		}
	} EXCEPT {
		mfile_map_fini(self);
		DBG_memset(self, 0xcc, sizeof(*self));
		RETHROW();
	}
}



/* Unlock or re-lock a mem-node allocator (that is: release/re-acquire locks
 * to all of the individual parts pointed to by the nodes allocated by `self')
 * For this purpose, re-locking a mem-node-allocator will (once again) make
 * sure that _all_ parts and nodes form a single, continuous range of mappings
 * as specified in the original call to `mfile_map_init()', leaving no
 * holes anywhere along the way, while the the act of holding locks to all of
 * the parts then guaranties that no new holes can possibly pop up out of the
 * blue. */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mfile_map_release)(struct mfile_map *__restrict self) {
	struct mnode *node;
	SLIST_FOREACH (node, &self->mfm_nodes, _mn_alloc) {
		mpart_lock_release(node->mn_part);
	}
}


/* Try to acquire locks to all already in-use parts.
 * If this fails for one of the parts, unlock everything
 * and return a pointer to that part. */
PRIVATE NOBLOCK WUNUSED NONNULL((1)) struct mpart *
NOTHROW(FCALL mfile_map_trylockall)(struct mfile_map *__restrict self) {
	struct mnode *node;
	SLIST_FOREACH(node, &self->mfm_nodes, _mn_alloc) {
		struct mpart *part = node->mn_part;
		if (!mpart_lock_tryacquire(part)) {
			/* Blocking-wait for this part to become available. */
			struct mnode *node2;
			for (node2 = SLIST_FIRST(&self->mfm_nodes);
			     node2 != node;
			     node2 = SLIST_NEXT(node2, _mn_alloc)) {
				assert(node2->mn_part != part);
				mpart_lock_release(node2->mn_part);
			}
			return part;
		}
	}
	return NULL;
}

/* Acquire locks to all parts */
PRIVATE NONNULL((1)) bool FCALL
mfile_map_lockall(struct mfile_map *__restrict self,
                  struct unlockinfo *unlock) {
	struct mpart *error;
	error = mfile_map_trylockall(self);
	if (error != NULL) {
		/* Must wait for the given part to become available. */
		unlockinfo_xunlock(unlock);
		while (!mpart_lock_available(error))
			task_yield();
		return false;
	}
	return true;
}


/* Unlock the part, and remove the node in all cases where the mapping-area
 * of the given node no longer overlaps with even a single byte of the area
 * described by the associated part. */
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mfile_map_unlock_and_remove_non_overlapping_parts)(struct mfile_map *__restrict self) {
	struct mnode **p_node, *node;
	p_node = SLIST_P_FIRST(&self->mfm_nodes);
	while ((node = *p_node) != NULL) {
		pos_t node_map_minaddr;
		pos_t node_map_maxaddr;
		struct mpart *part = node->mn_part;
		/* Calculate the address range that was ~supposed~ to be mapped by this node. */
		node_map_minaddr = self->mfm_addr + (uintptr_t)node->mn_minaddr;
		node_map_maxaddr = self->mfm_addr + (uintptr_t)node->mn_maxaddr;
		assert(node_map_minaddr <= node_map_maxaddr);
		if (!RANGE_OVERLAPS(node_map_minaddr,
		                    node_map_maxaddr,
		                    mpart_getminaddr(part),
		                    mpart_getmaxaddr(part))) {
			/* The mapped ranges no longer overlap. -> Remove this node. */
			SLIST_P_REMOVE(p_node, _mn_alloc);
			DBG_memset(node, 0xcc, sizeof(*node));
			SLIST_INSERT(&self->mfm_flist, node, _mn_alloc);
			mpart_lock_release(part);
			decref(part);
		} else {
			p_node = SLIST_P_NEXT(node, _mn_alloc);
		}
	}
}

/* Try to alter the addresses/offsets of nodes to enlarge/truncate
 * them such that they may take advantage of nodes parts that have
 * been split/merged in the mean time. */
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mnode_slist_adjusted_mapped_ranges)(struct mnode_slist *__restrict self,
                                                  pos_t min_mapped_address,
                                                  pos_t max_mapped_address) {
	struct mnode *prev, *node;
	bool changed;
again:
	changed = false;
	prev    = NULL;
	SLIST_FOREACH(node, self, _mn_alloc) {
		struct mnode *next = SLIST_NEXT(node, _mn_alloc);
		struct mpart *part = node->mn_part;
		pos_t want_map_minaddr, want_map_maxaddr;
		pos_t node_map_minaddr, node_map_maxaddr;
		pos_t part_map_minaddr, part_map_maxaddr;

		/* Calculate the address range currently mapped by this node. */
		node_map_minaddr = min_mapped_address + (uintptr_t)node->mn_minaddr;
		node_map_maxaddr = min_mapped_address + (uintptr_t)node->mn_maxaddr;
		part_map_minaddr = mpart_getminaddr(part);
		part_map_maxaddr = mpart_getmaxaddr(part);
		assert(node_map_minaddr <= node_map_maxaddr);
		assert(part_map_minaddr <= part_map_maxaddr);
		assert(RANGE_OVERLAPS(node_map_minaddr, node_map_maxaddr,
		                      part_map_minaddr, part_map_maxaddr));

		/* Calculate the address range that we want this node to represent.
		 * This represents the upper bounds to which this node (should) grow
		 * in order to fill in gaps to its left and right. */
		want_map_minaddr = min_mapped_address;
		want_map_maxaddr = max_mapped_address;
		if (prev != NULL)
			want_map_minaddr = (min_mapped_address + (uintptr_t)prev->mn_maxaddr) + 1;
		if (next != NULL)
			want_map_maxaddr = (min_mapped_address + (uintptr_t)next->mn_minaddr) - 1;

		/* Force node mappings back in-bounds of their associated parts,
		 * as well as (try to) widen nodes in order to fill holes. */
		if (node_map_minaddr < part_map_minaddr) {
			node->mn_minaddr = (byte_t *)(uintptr_t)(part_map_minaddr - min_mapped_address);
			node_map_minaddr = part_map_minaddr;
			changed          = true;
		} else if (node_map_minaddr > part_map_minaddr &&
		           node_map_minaddr > want_map_minaddr) {
			node_map_minaddr = part_map_minaddr;
			if (node_map_minaddr < want_map_minaddr)
				node_map_minaddr = want_map_minaddr;
			node->mn_minaddr = (byte_t *)(uintptr_t)(node_map_minaddr - min_mapped_address);
			changed          = true;
		}
		if (node_map_maxaddr > part_map_maxaddr) {
			node->mn_maxaddr = (byte_t *)(uintptr_t)(part_map_maxaddr - min_mapped_address);
			node_map_maxaddr = part_map_maxaddr;
			changed          = true;
		} else if (node_map_maxaddr < part_map_maxaddr &&
		           node_map_maxaddr < want_map_maxaddr) {
			node_map_maxaddr = part_map_maxaddr;
			if (node_map_maxaddr > want_map_maxaddr)
				node_map_maxaddr = want_map_maxaddr;
			node->mn_maxaddr = (byte_t *)(uintptr_t)(node_map_maxaddr - min_mapped_address);
			changed          = true;
		}

		/* Ensure that ranges have been properly calculated. */
		assert(node_map_minaddr == min_mapped_address + (uintptr_t)node->mn_minaddr);
		assert(node_map_maxaddr == min_mapped_address + (uintptr_t)node->mn_maxaddr);
		assert(node_map_minaddr >= part_map_minaddr);
		assert(node_map_maxaddr <= part_map_maxaddr);
		assert(node_map_minaddr >= want_map_minaddr);
		assert(node_map_maxaddr <= want_map_maxaddr);

		/* Re-calculate the effective offset into the associated part. */
		node->mn_partoff = (size_t)(node_map_minaddr - part_map_minaddr);

		/* Remember this node as the predecessor. */
		prev = node;
	}
	if (changed)
		goto again;
}


/* Check if the nodes from the given list are complete (that is: don't
 * contain any holes), as well as map a total of `num_bytes', as well
 * as that the first node has its min-addr set to `0' */
PRIVATE NOBLOCK ATTR_PURE NONNULL((1)) bool
NOTHROW(FCALL mnode_slist_is_complete_range)(struct mnode_slist const *__restrict self,
                                             size_t num_bytes) {
	struct mnode const *node;
	byte_t *expected_minaddr;
	expected_minaddr = (byte_t *)0;
	SLIST_FOREACH(node, self, _mn_alloc) {
		if (node->mn_minaddr != expected_minaddr)
			return false;
		expected_minaddr = node->mn_maxaddr + 1;
	}
	return (size_t)expected_minaddr == num_bytes;
}

PRIVATE NONNULL((1)) bool FCALL
mfile_map_fill_holes(struct mfile_map *__restrict self,
                     struct unlockinfo *unlock)
		THROWS(E_WOULDBLOCK, E_BADALLOC) {
	bool result;
	struct mnode **p_node, *prev, *next;
	result = true;
	p_node = SLIST_P_FIRST(&self->mfm_nodes);
	prev   = NULL;
continue_with_pnode:
	for (;;) {
		uintptr_t gap_min_offset;
		uintptr_t gap_end_offset;
		next = *p_node;
		/* Figure out the bounds of a (potential) gap. */
		gap_min_offset = 0;
		gap_end_offset = self->mfm_size - 1;
		if (prev != NULL)
			gap_min_offset = (uintptr_t)prev->mn_maxaddr + 1;
		if (next != NULL)
			gap_end_offset = (uintptr_t)next->mn_minaddr;
		if (gap_min_offset < gap_end_offset) {
			struct mfile *file = self->mfm_file;
			struct mnode *new_node;
			REF struct mpart *part;
			pos_t gap_min_addr, gap_max_addr;
			pos_t block_aligned_gap_addr;
			size_t block_aligned_gap_size, gap_size;
			uintptr_t gap_max_offset;
			gap_max_offset = gap_end_offset - 1;

			/* Part lookup is a blocking operation, so we must unlock everything first. */
			if (result) {
				unlockinfo_xunlock(unlock);
				result = false;
			}

			/* There is a gap right here that spans between `gap_min_offset...gap_max_offset'
			 * Start out by calculating the block-aligned address bounds of the gap. */
			gap_min_addr = self->mfm_addr + gap_min_offset;
			gap_max_addr = self->mfm_addr + gap_max_offset;
			gap_size     = (size_t)(gap_max_addr - gap_min_addr) + 1;
			block_aligned_gap_addr = gap_min_addr & ~file->mf_part_amask;
			block_aligned_gap_size = gap_size + (size_t)(gap_min_addr - block_aligned_gap_addr);
			block_aligned_gap_size = (block_aligned_gap_size + file->mf_part_amask) & ~file->mf_part_amask;

			/* Lookup the part that would best fit the gap. */
			part = mfile_getpart(file,
			                     block_aligned_gap_addr,
			                     block_aligned_gap_size);

			/* Check if we can find this part somewhere else within the list.
			 * If we do, then we must remove all nodes between the in-between
			 * position described by `p_node', and the duplicate (including
			 * the duplicate itself)
			 *
			 * Then, we must create a single, new node to split the union of
			 * all of the removed nodes, as well as the gap we're trying to
			 * fill above with a single, new node. */
			{
				struct mnode **p_duplicate_node;
				struct mnode *duplicate_node;
				/* Set to true if `duplicate_node' is located after the gap. */
				bool duplicate_node_is_after_gap = false;
				p_duplicate_node = SLIST_P_FIRST(&self->mfm_nodes);
				while ((duplicate_node = *p_duplicate_node) != NULL) {
					struct mnode *removed_nodes_lo;
					struct mnode *removed_nodes_hi;
					if (p_duplicate_node == p_node)
						duplicate_node_is_after_gap = true;
					if (duplicate_node->mn_part != part) {
						p_duplicate_node = SLIST_P_NEXT(duplicate_node, _mn_alloc);
						continue;
					}
					decref_nokill(part); /* The reference returned by `mfile_getpart()' */

					/* Found a duplicate of the part!
					 * Note that we may assume that at most one duplicate can ever exist at
					 * a time, since we always make an effort to prevent duplicates from the
					 * get-go, meaning that inside of the already-allocated list of nodes,
					 * there should never be any node that re-using the part from another one. */
					if (duplicate_node_is_after_gap) {
						removed_nodes_lo = next;
						removed_nodes_hi = duplicate_node;
						SLIST_P_REMOVE_R(p_node, duplicate_node, _mn_alloc);
					} else {
						removed_nodes_lo = next;
						removed_nodes_hi = prev;
						SLIST_P_REMOVE_R(p_duplicate_node, prev, _mn_alloc);
						p_node = p_duplicate_node;
					}

					/* Re-initialize the duplicate node to cover the union
					 * of gap and all of the removed nodes in its entirety. */
					new_node = duplicate_node;
					assert(removed_nodes_lo);
					assert(removed_nodes_hi);
					assert(removed_nodes_lo->mn_minaddr <= removed_nodes_hi->mn_maxaddr);
					if (gap_min_offset > (uintptr_t)removed_nodes_lo->mn_minaddr)
						gap_min_offset = (uintptr_t)removed_nodes_lo->mn_minaddr;
					if (gap_max_offset < (uintptr_t)removed_nodes_hi->mn_maxaddr)
						gap_max_offset = (uintptr_t)removed_nodes_hi->mn_maxaddr;
					new_node->mn_minaddr = (byte_t *)gap_min_offset;
					new_node->mn_maxaddr = (byte_t *)gap_max_offset;

					/* Free nodes that we've removed between p_node and the duplicate.
					 * However, exclude the duplicate node itself, since we're re-using
					 * that one! */
					{
						struct mnode *del_node, *del_next;
						del_node = removed_nodes_lo;
						for (;;) {
							del_next = SLIST_NEXT(del_node, _mn_alloc);
							if (del_node != duplicate_node) {
								/* Free this node! */
								decref_unlikely(del_node->mn_part);
								DBG_memset(del_node, 0xcc, sizeof(*del_node));
								SLIST_INSERT(&self->mfm_flist, del_node, _mn_alloc);
							}
							if (del_node == removed_nodes_hi)
								break;
							del_node = del_next;
						}
					}

					/* Re-insert the (now widened) `new_node' (which used to be
					 * `duplicate_node') into the list to take up the gap described
					 * by the hole we've created by removing all of those nodes
					 * above! */
					SLIST_P_INSERT_BEFORE(p_node, new_node, _mn_alloc);
					prev   = new_node;
					p_node = SLIST_P_NEXT(new_node, _mn_alloc);;
					goto continue_with_pnode;
				}
			} /* Scope... */

			/* Allocate and initialize the new node used to cover the gap.
			 * For this purpose, try to take a node from the free-list */
			new_node = SLIST_FIRST(&self->mfm_flist);
			if (new_node != NULL) {
				SLIST_REMOVE_HEAD(&self->mfm_flist, _mn_alloc);
			} else {
				/* Must allocate a new node proper!
				 * NOTE: No need to release any locks here, because we're not holding any! */
				TRY {
					new_node = (struct mnode *)kmalloc(sizeof(struct mnode),
					                                   GFP_LOCKED | GFP_PREFLT);
				} EXCEPT {
					decref_unlikely(part);
					RETHROW();
				}
			}
			/* Initialize the new node. (at least as much as we're supposed to) */
			new_node->mn_part = part; /* Inherit reference */
			/* Have the node fill the gap in its entirety. If we're wrong with
			 * this assessment, then later calls to
			 *   - mfile_map_unlock_and_remove_non_overlapping_parts
			 *   - mnode_slist_adjusted_mapped_ranges
			 * will fix the error we're making here.
			 *
			 * Also: No need to fill in `mn_partoff' because that also something
			 *       that will be done by `mnode_slist_adjusted_mapped_ranges()' */
			new_node->mn_minaddr = (byte_t *)gap_min_offset;
			new_node->mn_maxaddr = (byte_t *)gap_max_offset;

			/* Insert the new node and continue scanning for holes afterwards. */
			SLIST_P_INSERT_BEFORE(p_node, new_node, _mn_alloc);
			prev   = new_node;
			p_node = SLIST_P_NEXT(new_node, _mn_alloc);;
			goto continue_with_pnode;
		} else {
			/* No gap here :) */
		}
		if (!next)
			break;
		prev   = next;
		p_node = SLIST_P_NEXT(next, _mn_alloc);
	}
	return result;
}


/* (try to) do the same as `mfile_map_acquire()', but if doing so cannot be
 * done without blocking on an internal lock, then release all already-acquired
 * locks, invoke the `unlock' callback (if given), wait for the necessary lock
 * to become available, and return `false'.
 * Otherwise, don't invoke `unlock' and return `true'.
 * NOTE: In the case of an exception, `unlock' is guarantied to be invoked
 *       prior to the exception being thrown. */
PUBLIC NONNULL((1)) bool FCALL
mfile_map_acquire_or_unlock(struct mfile_map *__restrict self,
                            struct unlockinfo *unlock)
		THROWS(E_WOULDBLOCK, E_BADALLOC) {
	struct mfile *file;
	pos_t block_aligned_addr;
	size_t block_aligned_size;
	file = self->mfm_file;
	assert(IS_ALIGNED(self->mfm_addr, PAGESIZE));
	assert(IS_ALIGNED(self->mfm_size, PAGESIZE));
	block_aligned_addr = self->mfm_addr & ~file->mf_part_amask;
	block_aligned_size = self->mfm_size + (size_t)(self->mfm_addr - block_aligned_addr);
	block_aligned_size = (block_aligned_size + file->mf_part_amask) & ~file->mf_part_amask;
	/* Acquire locks to all parts already loaded! (For this purpose,
	 * we may assume that no part appears more than once, so we don't
	 * have to take care to track which parts are already locked) */
again:
	if (!mfile_map_lockall(self, unlock))
		goto fail;

	/* Now go through the list of nodes and throw out nodes who's parts
	 * no longer overlap at all with the range that is being mapped by
	 * the associated node. */
	mfile_map_unlock_and_remove_non_overlapping_parts(self);

	/* We now know that _all_ remaining nodes _do_ actually map at least
	 * some part of the requested address range. As such, try to alter
	 * the addresses/offsets of nodes to enlarge/truncate them such that
	 * they may take advantage of mem-parts that have been split/merged
	 * in the mean time. */
	mnode_slist_adjusted_mapped_ranges(&self->mfm_nodes,
	                                   self->mfm_addr,
	                                   self->mfm_addr + self->mfm_size - 1);

	/* At this point, all in-use nodes map the widest area(s) possible of
	 * their respective parts, limited only by the overall file-range that
	 * is supposed to get mapped.
	 *
	 * With this in mind, check if the current list of nodes still
	 * represents continuous range of consecutive file-parts, or if
	 * there might actually be holes between some of the nodes. */
	if (!mnode_slist_is_complete_range(&self->mfm_nodes, self->mfm_size)) {

		/* There must still be (some) holes between nodes currently being mapped.
		 * As such, we must release all of the locks, and allocate new nodes, as
		 * well as parts in order to fill those holes!
		 *
		 * NOTE: When allocating new parts, we must be extra careful to check if
		 *       there may already be another node bound to the same part, even
		 *       if that other node is somewhere completely different within our
		 *       local list of parts.
		 *       If we do find a duplicate part, then we must delete all nodes
		 *       between where we're found the duplicate (including the node of
		 *       the duplicate itself), and where we were intending to insert
		 *       the turns-out-to-be-a-duplicate part. */

		/* XXX: Why not try to do this without blocking before releasing all
		 *      of those pretty, tasty locks? */
		mfile_map_release(self);
		if (!mfile_map_fill_holes(self, unlock))
			goto fail;

		/* With all of the whole filled, the range should once again be complete,
		 * but then again: we're not holding the required locks right now... */
		assert(mnode_slist_is_complete_range(&self->mfm_nodes, self->mfm_size));
		goto again;
	}

	/* Populate the mapping if the callers wants this. */
	if (self->mfm_flags & MAP_POPULATE) {
		if (!mfile_map_populate_or_unlock(self))
			goto fail;
	}
	return true;
fail:
	return false;
}


/* Essentially does the same as `mfile_map_acquire_or_unlock()', however the
 * caller must already be holding locks to every mem-part mapped by `self'
 * However, use of `mfile_map_acquire_or_unlock()' is still more efficient,
 * since that function can do some tricks which this one can't (see impl)! */
PUBLIC WUNUSED NONNULL((1)) bool FCALL
mfile_map_reflow_or_unlock(struct mfile_map *__restrict self,
                           struct unlockinfo *unlock)
		THROWS(E_WOULDBLOCK, E_BADALLOC) {
	struct mfile *file;
	pos_t block_aligned_addr;
	size_t block_aligned_size;
	file = self->mfm_file;
	assert(IS_ALIGNED(self->mfm_addr, PAGESIZE));
	assert(IS_ALIGNED(self->mfm_size, PAGESIZE));
	block_aligned_addr = self->mfm_addr & ~file->mf_part_amask;
	block_aligned_size = self->mfm_size + (size_t)(self->mfm_addr - block_aligned_addr);
	block_aligned_size = (block_aligned_size + file->mf_part_amask) & ~file->mf_part_amask;

	/* Essentially do the same stuff as `mfile_map_acquire_or_unlock()' */
	mfile_map_unlock_and_remove_non_overlapping_parts(self);
	mnode_slist_adjusted_mapped_ranges(&self->mfm_nodes,
	                                   self->mfm_addr,
	                                   self->mfm_addr + self->mfm_size - 1);

	if (!mnode_slist_is_complete_range(&self->mfm_nodes, self->mfm_size)) {
		/* This is where the control-flow differs from `mfile_map_acquire_or_unlock()'
		 * Because the caller is responsible for locking the parts from our node-list,
		 * we are unable to re-acquire those locks, also meaning we have unconditionally
		 * unlock everything here, rather than still having the chance to do stuff w/o
		 * having to unlock everything. */
		/* XXX: Why not try to do this without blocking before releasing all
		 *      of those pretty, tasty locks? */
		mfile_map_release(self);
		unlockinfo_xunlock(unlock);
		if (mfile_map_fill_holes(self, NULL))
			assert(mnode_slist_is_complete_range(&self->mfm_nodes, self->mfm_size));
		goto fail;
	}

	/* Populate the mapping if the callers wants this. */
	if (self->mfm_flags & MAP_POPULATE) {
		if (!mfile_map_populate_or_unlock(self))
			goto fail;
	}

	return true;
fail:
	return false;
}


/* Fallback to-be used with `mfile_map_with_unlockinfo::mmwu_info::ui_unlock'
 * When invoked, will call `mfile_map_release()' on the contained mfile-map. */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mfile_map_with_unlockinfo_unlock)(struct unlockinfo *__restrict self) {
	struct mfile_map_with_unlockinfo *me;
	me = (struct mfile_map_with_unlockinfo *)self;
	mfile_map_release(&me->mmwu_map);
}



DECL_END

#endif /* !GUARD_KERNEL_SRC_MEMORY_MFILE_MAP_C */
