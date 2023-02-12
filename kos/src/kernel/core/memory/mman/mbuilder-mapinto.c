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
#ifndef GUARD_KERNEL_SRC_MEMORY_MBUILDER_MAPINTO_C
#define GUARD_KERNEL_SRC_MEMORY_MBUILDER_MAPINTO_C 1
#define __WANT_MPART__mp_nodlsts /* mpart_getnodlst_from_mnodeflags() */
#define __WANT_MNODE__mn_dead
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/mman.h>
#include <kernel/mman/mbuilder.h>
#include <kernel/mman/mfile.h>
#include <kernel/mman/mnode.h>
#include <kernel/mman/module.h>
#include <kernel/mman/mpart.h>
#include <misc/unlockinfo.h>

#include <hybrid/align.h>
#include <hybrid/overflow.h>

#include <kos/except.h>
#include <kos/except/reason/inval.h>

#include <assert.h>
#include <atomic.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

DECL_BEGIN

#if !defined(NDEBUG) && !defined(NDEBUG_FINI)
#define DBG_memset memset
#else /* !NDEBUG && !NDEBUG_FINI */
#define DBG_memset(...) (void)0
#endif /* NDEBUG || NDEBUG_FINI */

/* Try to find a suitable loadaddr at which all of the mappings from `builder'
 * may be mapped, such that they don't collide with any existing mapping  that
 * is already mapped in `self'.
 * The caller must ensure that `builder' isn't empty.
 * @param: addr:      A load-address hint for where to search for free memory.
 * @param: flags:     Set of `MAP_GROWSDOWN | MAP_GROWSUP | MAP_32BIT | MAP_STACK | MAP_NOASLR'
 *                    Unknown flags are silently ignored.
 * @return: PAGEDIR_PAGEALIGNED * : The load address addend to-be added to mappings.
 *                                  Pass   this   value   to   `mman_map_mbuilder()'
 * @return: MAP_FAILED:             Error: No free space matching requirements was found. */
PUBLIC NOBLOCK WUNUSED NONNULL((1, 3)) uintptr_t
NOTHROW(FCALL mman_findunmapped_mbuilder)(struct mman const *__restrict self, uintptr_t addr,
                                          struct mbuilder_norpc const *__restrict builder,
                                          unsigned int flags) {
	uintptr_t result;
	struct mbnode const *minnode, *maxnode;
	assert(builder->mb_mappings != NULL);
	minnode = builder->mb_mappings;
	maxnode = builder->mb_mappings;
	while (minnode->mbn_mement.rb_lhs)
		minnode = minnode->mbn_mement.rb_lhs;
	while (maxnode->mbn_mement.rb_rhs)
		maxnode = maxnode->mbn_mement.rb_rhs;

	/* Use the min/max bounds of the lowest/greatest node to find a free area.
	 * TODO: This can be done better since we may not actually need the entire
	 *       area to be  free, but only  a select portion  of it (namely:  the
	 *       portion that's covered by nodes in `builder'). */
	result = (uintptr_t)mman_findunmapped(self, (void *)addr,
	                                      (size_t)((byte_t *)mbnode_getmaxaddr(maxnode) -
	                                               (byte_t *)mbnode_getminaddr(minnode)) +
	                                      1,
	                                      flags);
	if (result != (uintptr_t)MAP_FAILED) {
		/* Right now, `result' is the eventual base-address of `minnode'. However,
		 * we're supposed to return the  load-address of the mbuilder mapping.  As
		 * such,  we must  subtract the starting  offset of the  lowest node, thus
		 * calculating  the actual loadaddr  offset that'll end  up being used for
		 * relocating the mapping in virtual memory. */
		result -= (uintptr_t)mbnode_getminaddr(minnode);
	}
	return result;
}


/* Go  over  all nodes  from `tree'  and check  if `self'  contains nodes
 * that  overlap with the eventual target locations of those from `tree'.
 * If any are found, either throw `E_BADALLOC_ADDRESS_ALREADY_EXISTS', or
 * split the node at the overlapping bounds (s.a.  `MAP_FIXED_NOREPLACE')
 * @return: true:  Success
 * @return: false: Lock was lost. */
PRIVATE NOBLOCK WUNUSED NONNULL((1, 3)) bool FCALL
maybe_split_overlapping_nodes_or_unlock(struct mman *__restrict self, uintptr_t addr,
                                        struct mbnode const *__restrict tree,
                                        unsigned int flags, struct unlockinfo *unlock)
		THROWS(E_BADALLOC_ADDRESS_ALREADY_EXISTS) {
	struct mnode *node;
	byte_t *minaddr, *maxaddr;

again:
	/* Figure out the final addresses of the given `tree'-node. */
	minaddr = (byte_t *)mbnode_getminaddr(tree) + addr;
	maxaddr = (byte_t *)mbnode_getmaxaddr(tree) + addr;
	if (flags & MAP_FIXED_NOREPLACE) {
		/* Check if there is ~any~ mapping whatsoever within this range. */
		node = mman_mappings_rlocate(self, minaddr, maxaddr);
		if unlikely(node != NULL) {
			/* Error: Another mapping already exists, which this one would collide with! */
			void *node_minaddr, *node_maxaddr;
			node_minaddr = mnode_getminaddr(node);
			node_maxaddr = mnode_getmaxaddr(node);
			mman_lock_release(self);
			unlockinfo_xunlock(unlock);
			THROW(E_BADALLOC_ADDRESS_ALREADY_EXISTS,
			      minaddr, maxaddr,
			      node_minaddr, node_maxaddr);
		}
	} else {
		/* Check if whole nodes  exist that overlap with  the
		 * bounds requirements specified by the given `tree'-
		 * node. If any such node exists, then we must  split
		 * it, both at the low end  of the range, as well  as
		 * the high end! */
		node = mman_mappings_locate(self, minaddr);
		if (node != NULL) {
			if (minaddr != (byte_t *)mnode_getminaddr(node) &&
			    !mnode_split_or_unlock(self, node, minaddr, unlock))
				goto nope;
			if (maxaddr > (byte_t *)mnode_getmaxaddr(node))
				goto check_maxaddr_node;
do_split_maxaddr_node:
			if (maxaddr != (byte_t *)mnode_getmaxaddr(node) &&
			    !mnode_split_or_unlock(self, node, maxaddr + 1, unlock))
				goto nope;
		} else {
check_maxaddr_node:
			node = mman_mappings_locate(self, maxaddr);
			if (node != NULL)
				goto do_split_maxaddr_node;
		}
	}

	/* Recursively iterate the entire tree. */
	if (tree->mbn_mement.rb_rhs) {
		if (tree->mbn_mement.rb_lhs) {
			if (!maybe_split_overlapping_nodes_or_unlock(self, addr,
			                                             tree->mbn_mement.rb_lhs,
			                                             flags, unlock))
				goto nope;
		}
		tree = tree->mbn_mement.rb_rhs;
		goto again;
	}
	if (tree->mbn_mement.rb_lhs) {
		tree = tree->mbn_mement.rb_lhs;
		goto again;
	}
	return true;
nope:
	return false;
}



/* Return the min-address of the lowest-address mem-node of `self' */
PRIVATE ATTR_PURE WUNUSED NONNULL((1)) byte_t *
NOTHROW(FCALL mbuilder_mappings_getminaddr)(struct mbuilder_norpc const *__restrict self) {
	struct mbnode const *node;
	assert(self->mb_mappings != NULL);
	node = self->mb_mappings;
	while (node->mbn_mement.rb_lhs)
		node = node->mbn_mement.rb_lhs;
	return node->mbn_minaddr;
}

PRIVATE ATTR_PURE WUNUSED NONNULL((1)) byte_t *
NOTHROW(FCALL mbuilder_mappings_getmaxaddr)(struct mbuilder_norpc const *__restrict self) {
	struct mbnode const *node;
	assert(self->mb_mappings != NULL);
	node = self->mb_mappings;
	while (node->mbn_mement.rb_rhs)
		node = node->mbn_mement.rb_rhs;
	return node->mbn_maxaddr;
}



/* Return the size of the bounds of self (that is the # of bytes from the start
 * of the lowest node, to the end of the greatest node). The caller must ensure
 * that `self' isn't empty. */
PRIVATE NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW(FCALL mbuilder_get_bounds_size)(struct mbuilder_norpc const *__restrict self) {
	size_t result;
	byte_t const *minaddr, *maxaddr;
	minaddr = mbuilder_mappings_getminaddr(self);
	maxaddr = mbuilder_mappings_getmaxaddr(self);
	result  = (size_t)(maxaddr - minaddr) + 1;
	return result;
}


/* Similar  to `mman_findunmapped_mbuilder()', but  never return `MAP_FAILED', and
 * automatically split mem-nodes at the resulting min/max bounds when  `MAX_FIXED'
 * w/o `MAP_FIXED_NOREPLACE' is used, and  another mapping already existed at  the
 * specified location. If this cannot be done without blocking, release all locks,
 * do the split while not holding  any locks, and return `MAP_FAILED',  indicative
 * of   the  caller  needing   to  re-acquire  locks   and  re-attempt  the  call.
 * The caller must ensure that `builder' isn't empty.
 * @param: addr:      A load-address hint for where to search for free memory.
 * @param: flags:     Set of `MAP_GROWSDOWN | MAP_GROWSUP | MAP_32BIT | MAP_STACK | MAP_NOASLR'
 *                    Additionally,   `MAP_FIXED'   and  `MAP_FIXED_NOREPLACE'   are  accepted.
 *                    Unknown flags are silently ignored.
 * @return: PAGEDIR_PAGEALIGNED * : The load address to-be added to mappings.
 *                                  Pass this value to  `mman_map_mbuilder()'
 * @return: MAP_FAILED:             Locks had to be released, but another attempt might succeed.
 *                                  Reacquire  all  required  locks,  and  re-attempt  the call.
 * @throws: E_BADALLOC_INSUFFICIENT_VIRTUAL_MEMORY: Failed to locate a suitably large address
 *                                                  range  that  fits the  given constraints.
 * @throws: E_BADALLOC_ADDRESS_ALREADY_EXISTS:      Both  `MAP_FIXED'  and   `MAP_FIXED_NOREPLACE'
 *                                                  were given, and a pre-existing mapping already
 *                                                  exists within the given address range. */
PUBLIC NOBLOCK WUNUSED NONNULL((1, 3)) uintptr_t FCALL
mman_getunmapped_mbuilder_or_unlock(struct mman *__restrict self, uintptr_t addr,
                                    struct mbuilder_norpc const *__restrict builder,
                                    unsigned int flags,
                                    struct unlockinfo *unlock)
		THROWS(E_BADALLOC_INSUFFICIENT_VIRTUAL_MEMORY,
		       E_BADALLOC_ADDRESS_ALREADY_EXISTS) {
	uintptr_t result;
	/* Deal with MAP_FIXED */
	if (flags & MAP_FIXED) {
		struct mnode const *node;
		struct mbnode const *minnode, *maxnode;
		size_t num_bytes;
		byte_t *minaddr, *maxaddr;
		assert(builder->mb_mappings != NULL);
		minnode = builder->mb_mappings;
		maxnode = builder->mb_mappings;
		while (minnode->mbn_mement.rb_lhs)
			minnode = minnode->mbn_mement.rb_lhs;
		while (maxnode->mbn_mement.rb_rhs)
			maxnode = maxnode->mbn_mement.rb_rhs;

		result    = FLOOR_ALIGN(addr, PAGESIZE);
		num_bytes = (size_t)((byte_t *)mbnode_getmaxaddr(maxnode) -
		                     (byte_t *)mbnode_getminaddr(minnode)) +
		            1;

		/* Calculate the mapped min/max address and check for overflow. */
		if unlikely(OVERFLOW_UADD((uintptr_t)mbnode_getminaddr(minnode), result, (uintptr_t *)&minaddr) ||
		            OVERFLOW_UADD((uintptr_t)mbnode_getmaxaddr(maxnode), result, (uintptr_t *)&maxaddr)) {
			mman_lock_release(self);
			unlockinfo_xunlock(unlock);
			THROW(E_INVALID_ARGUMENT_BAD_VALUE,
			      E_INVALID_ARGUMENT_CONTEXT_MMAP_LENGTH,
			      num_bytes);
		}
		if ((node = mnode_tree_rlocate(self->mm_mappings, minaddr, maxaddr)) != NULL) {
			/* Do a try-hard check for nodes that may overlap with our target range. */
			if (!maybe_split_overlapping_nodes_or_unlock(self, result,
			                                             builder->mb_mappings,
			                                             flags, unlock))
				goto must_retry;
		}
	} else {
		/* Normal case: automatically select a free location. */
		result = mman_findunmapped_mbuilder(self, addr, builder, flags);
		if unlikely(result == (uintptr_t)MAP_FAILED)
			goto err_insufficient_vmem;
	}
	return result;
must_retry:
	return (uintptr_t)MAP_FAILED;
err_insufficient_vmem:
	/* Throw an insufficient-virtual-memory exception. */
	mman_lock_release(self);
	unlockinfo_xunlock(unlock);
	THROW(E_BADALLOC_INSUFFICIENT_VIRTUAL_MEMORY,
	      mbuilder_get_bounds_size(builder));
}


/* Used internally to indicate that a node should be added
 * to  the  list of  writable  nodes of  the  target mman. */
#define MBNODE_F_WRITABLE MBNODE_F_NONBLOCK


/* Recursively load `tree' into the page directory of `self' */
PRIVATE NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL mman_map_mbuilder_tree_pdmap)(struct mman *__restrict self,
                                            struct mbnode *__restrict tree,
                                            uintptr_t loadaddr, unsigned int flags) {
	struct mnode *node;

again:
	/* We must also delete a couple of flags that may still be left in the node,
	 * and  that might  otherwise interfere  with other  mman system components. */
	tree->mbn_flags &= ~(MBNODE_F_POPULATE | MBNODE_F_NONBLOCK);
	node = (struct mnode *)tree;
	assertf(!(node->mn_flags & MNODE_F_UNMAPPED), "Why is this node marked as UNMAPPED?");
	assertf(!(node->mn_flags & MNODE_F_MPREPARED), "No support for PREPARED here!");
	assertf(!(node->mn_flags & MNODE_F_MHINT), "No support for MHINT here!");

	/* Update the node's min/max address pair, adjusting it for use with `loadaddr' */
	node->mn_minaddr += loadaddr;
	node->mn_maxaddr += loadaddr;

	/* If the node has a backing part, then we can try  to
	 * map that part in the associated page directory now. */
	if (node->mn_part != NULL) {
		unsigned int was_prepared = flags;
		if (!(flags & MMAN_MAP_MBUILDER_F_PREPARED) &&
		    mnode_pagedir_prepare_p(self->mm_pagedir_p, node))
			was_prepared |= MMAN_MAP_MBUILDER_F_PREPARED;
		if (was_prepared & MMAN_MAP_MBUILDER_F_PREPARED) {
			pagedir_prot_t map_prot;

			/* Try to map the associated part into the target mman's page directory. */
			map_prot = mpart_mmap_node_p(node->mn_part,
			                             self->mm_pagedir_p,
			                             mnode_getaddr(node),
			                             mnode_getsize(node),
			                             node->mn_partoff,
			                             node);

			/* Set `MBNODE_F_WRITABLE' if the node ends up as writable. */
			if (map_prot & PAGEDIR_PROT_WRITE)
				tree->mbn_flags |= MBNODE_F_WRITABLE;

			/* If we've only temporarily prepared the pagedir, then unprepare again. */
			if (was_prepared != flags)
				mnode_pagedir_unprepare_p(self->mm_pagedir_p, node);
		}
	}

	/* Recursively enumerate the entire tree. */
	if (tree->mbn_mement.rb_lhs) {
		if (tree->mbn_mement.rb_rhs)
			mman_map_mbuilder_tree_pdmap(self, tree->mbn_mement.rb_rhs, loadaddr, flags);
		tree = tree->mbn_mement.rb_lhs;
		goto again;
	}
	if (tree->mbn_mement.rb_rhs) {
		tree = tree->mbn_mement.rb_rhs;
		goto again;
	}
}


/* Transfer nodes into the given target mman. */
PRIVATE NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL mman_map_mbuilder_tree_transfer)(struct mman *__restrict self,
                                               struct mbnode *__restrict tree) {
	struct mbnode *lhs, *rhs;
again:
	lhs = tree->mbn_mement.rb_lhs;
	rhs = tree->mbn_mement.rb_rhs;

	/* Insert the node into the given target mman. */
	tree->_mbn_mman   = self;
	tree->_mbn_module = NULL;
	mman_mappings_insert(self, (struct mnode *)tree);

	/* If  this node is responsible for holding a unique lock to
	 * one of the mem-parts mapped by the caller's builder, then
	 * this is the point where we must unlock that part. */
	if (LIST_ISBOUND(tree, mbn_nxtuprt)) {
		LIST_UNBIND(tree, mbn_nxtuprt);
		mpart_lock_release(tree->mbn_part);
	}

	/* Special case: If the node ended up as writable, then we
	 * must add it to the list of writable nodes of the target
	 * mman.
	 * Note that this must  happen _after_ we've unbound  the
	 * node from the unique-part hashset, since these 2 lists
	 * use the same memory location for links! */
	if (tree->mbn_flags & MBNODE_F_WRITABLE) {
		tree->mbn_flags &= ~MBNODE_F_WRITABLE; /* mbnode-specific flag! */
		LIST_INSERT_HEAD(&self->mm_writable, (struct mnode *)tree, mn_writable);
	}

	/* Recursively enumerate the entire tree. */
	if (lhs) {
		if (rhs)
			mman_map_mbuilder_tree_transfer(self, rhs);
		tree = lhs;
		goto again;
	}
	if (rhs) {
		tree = rhs;
		goto again;
	}
}




/* Map all of the  nodes from `builder' into  self whilst applying a  load-offset
 * specified by `loadaddr'. The caller must ensure that no other mappings already
 * exist  at any of the locations that will overlap with the nodes from `builder'
 * after `loadaddr' is applied to each of their min/max addresses.
 *
 * Before calling this function, the caller must have acquired a lock to `self',
 * as well as `mbuilder_partlocks_acquire()'! Once this function returns, all of
 * the locks to mem-parts will have been  released, but the lock to `self'  will
 * still be held, and thereby has to be removed by the caller.
 *
 * @param: flags: Set of `MMAN_MAP_MBUILDER_F_*' */
PUBLIC NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL mman_map_mbuilder)(struct mman *__restrict self,
                                 struct mbuilder_norpc *__restrict builder,
                                 uintptr_t loadaddr, unsigned int flags) {
	/* Go over all file mappings and fill in the fields:
	 *    - _mbn_partoff
	 *    - _mbn_link */
	struct mbnode *fmnode;
	for (fmnode = SLIST_FIRST(&builder->mb_files); fmnode;) {
		pos_t fm_base;   /* File-map-base */
		byte_t *mm_base; /* Memory-map-base */
		struct mbnode *iter, *fmnext;
		fmnext  = SLIST_NEXT(fmnode, mbn_nxtfile);
		mm_base = fmnode->mbn_minaddr;
		fm_base = mnode_mbn_filpos_get(fmnode);
		iter    = fmnode;
		decref_unlikely(fmnode->mbn_file); /* No longer needed... */
		do {
			pos_t fm_iter;
			struct mnode_list *link_list;
			struct mpart *part;
			part    = iter->mbn_part;
			fm_iter = fm_base + (size_t)(iter->mbn_minaddr - mm_base);
			assertf(fm_iter >= part->mp_minaddr,
			        "This should have been asserted earlier, and we should "
			        "have been holding a lock to `part' ever since!");
			iter->_mbn_partoff = (mpart_reladdr_t)(fm_iter - part->mp_minaddr);

			/* Add the node to the part's relevant list of nodes. */
			link_list = mpart_getnodlst_from_mnodeflags(part, iter->mbn_flags);
			LIST_INSERT_HEAD(link_list, (struct mnode *)iter, mn_link);
		} while ((iter = iter->mbn_filnxt) != NULL);
		fmnode = fmnext;
	}
	SLIST_INIT(&builder->mb_files);

	/* Iterate the builder's mappings and set the `_mbn_mman' and  `_mbn_module'
	 * fields for nodes whilst inserting them into the given target mman `self'. */
	if likely(builder->mb_mappings != NULL) {
		byte_t const *minaddr, *maxaddr;
		mman_map_mbuilder_tree_pdmap(self, builder->mb_mappings, loadaddr, flags);
		minaddr = mbuilder_mappings_getminaddr(builder);
		maxaddr = mbuilder_mappings_getmaxaddr(builder);
		mman_map_mbuilder_tree_transfer(self, builder->mb_mappings);

		/* With everything loaded into the new mman, we now have to check if
		 * it's possible to merge any of the newly inserted nodes with their
		 * neighboring nodes.
		 * This  has to be done for all nodes at once, and not on a per-node
		 * basis, since we'd  otherwise try  to merge nodes  in a  situation
		 * where pert->node lists might still point to other nodes that have
		 * yet to be loaded into their new mman! (this would only happen  if
		 * some  specific mem-part was mapped more than once, and an attempt
		 * to  merge one of its nodes is made before all of other nodes have
		 * been inserted into the target mman's mappings-tree) */
		mman_mergenodes_inrange(self, minaddr, maxaddr);

		builder->mb_mappings = NULL; /* Inherited! */
	}

#ifndef NDEBUG
	/* The tree-enumeration above _really_ should have gotten rid  of
	 * _all_ of the upart locks, however just to be save, assert that
	 * all of the upart hash-sets are empty now! */
	{
		unsigned int i;
		for (i = 0; i < MBNODE_PARTSET_NUMBUCKETS; ++i)
			assert(LIST_EMPTY(&builder->mb_uparts.mbps_set[i]));
	}
#endif /* !NDEBUG */
}


PRIVATE NOBLOCK NONNULL((1, 2, 4)) bool
NOTHROW(FCALL mman_unmap_mbuilder_tree)(struct mman *__restrict self,
                                        struct mbnode const *__restrict tree,
                                        uintptr_t loadaddr,
                                        struct mnode_slist *__restrict deadnodes) {
	struct mnode *removeme;
	byte_t *minaddr, *maxaddr;
again:
	minaddr = (byte_t *)mbnode_getminaddr(tree) + loadaddr;
	maxaddr = (byte_t *)mbnode_getmaxaddr(tree) + loadaddr;

	/* Remove all nodes that exist within the given address range. */
	while ((removeme = mman_mappings_rremove(self, minaddr, maxaddr)) != NULL) {
		if (LIST_ISBOUND(removeme, mn_writable))
			LIST_REMOVE(removeme, mn_writable);

		/* Keep track of how many nodes are mapping some given module. */
		if (removeme->mn_module)
			module_dec_nodecount(removeme->mn_module);
		DBG_memset(&removeme->mn_writable, 0xcc, sizeof(removeme->mn_writable));
		DBG_memset(&removeme->mn_module, 0xcc, sizeof(removeme->mn_module));
		DBG_memset(&removeme->mn_mman, 0xcc, sizeof(removeme->mn_mman));
		SLIST_INSERT(deadnodes, removeme, _mn_dead);
	}

	/* Recursively enumerate the entire tree. */
	if (tree->mbn_mement.rb_lhs) {
		if (tree->mbn_mement.rb_rhs) {
			if unlikely(!mman_unmap_mbuilder_tree(self, tree->mbn_mement.rb_rhs,
			                                      loadaddr, deadnodes))
				goto fail;
		}
		tree = tree->mbn_mement.rb_lhs;
		goto again;
	}
	if (tree->mbn_mement.rb_rhs) {
		tree = tree->mbn_mement.rb_rhs;
		goto again;
	}
	return true;
fail:
	return false;
}

/* Unmap all mem-nodes from `self' that overlap with nodes from `builder'
 * after the given `loadaddr' offset has  been applied to them. For  this
 * purpose, the page directory of `self' may need to be prepared in order
 * to  successfully unmap  those nodes, and  if doing so  fails, then all
 * already-removed nodes are restored, and `false' is returned.
 *
 * Otherwise, removed nodes are marked as UNMAPPED, and are inserted into
 * the given `deadnodes' list (linked via `_mn_dead').
 *
 * This function is needed to facility `MAP_FIXED' functionality detailed
 * by  `mman_getunmapped_mbuilder_or_unlock()', and may be used to remove
 * colliding  nodes prior to  new nodes from  `builder' being loaded into
 * the given mman (as per `mman_map_mbuilder()')
 *
 * @return: true:  Success
 * @return: false: Insufficient  physical  memory to  prepare  the page
 *                 directory for the removal of a pre-existing mapping. */
PUBLIC NOBLOCK NONNULL((1, 2, 4)) bool
NOTHROW(FCALL mman_unmap_mbuilder)(struct mman *__restrict self,
                                   struct mbuilder_norpc const *__restrict builder,
                                   uintptr_t loadaddr,
                                   struct mnode_slist *__restrict deadnodes) {
	if likely(builder->mb_mappings != NULL) {
		struct mnode *orig_deadnode;
		orig_deadnode = SLIST_FIRST(deadnodes);
		if unlikely(!mman_unmap_mbuilder_tree(self, builder->mb_mappings,
		                                      loadaddr, deadnodes)) {
			/* Restore all previously removed from until `orig_deadnode' */
			while (SLIST_FIRST(deadnodes) != orig_deadnode) {
				struct mnode *restore;
				restore = SLIST_FIRST(deadnodes);
				SLIST_REMOVE_HEAD(deadnodes, _mn_dead);
				mman_mappings_insert(self, restore);
				mnode_merge(restore);
			}
		} else {
			struct mnode *iter;
			/* Set the UNMAPPED flag for all of the nodes we've removed.
			 * Because that flag can only be set once, we can only do so
			 * once we're sure that we've managed to remove _all_ of the
			 * nodes without any problems! */
			for (iter = SLIST_FIRST(deadnodes); iter != orig_deadnode;
			     iter = SLIST_NEXT(iter, _mn_dead))
				atomic_or(&iter->mn_flags, MNODE_F_UNMAPPED);
		}
	}
	return true;
}


DECL_END

#endif /* !GUARD_KERNEL_SRC_MEMORY_MBUILDER_MAPINTO_C */
