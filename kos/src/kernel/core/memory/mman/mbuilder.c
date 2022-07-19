/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_SRC_MEMORY_MBUILDER_C
#define GUARD_KERNEL_SRC_MEMORY_MBUILDER_C 1
#define __WANT_MNODE__mn_alloc
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/fs/dirent.h>
#include <kernel/fs/path.h>
#include <kernel/malloc.h>
#include <kernel/mman/flags.h>
#include <kernel/mman/mbuilder.h>
#include <kernel/mman/mfile-map.h>
#include <kernel/mman/mfile.h>
#include <kernel/mman/mnode.h>
#include <kernel/mman/mpart.h>
#include <kernel/mman/phys.h>
#include <sched/rpc-internal.h>

#include <hybrid/align.h>
#include <hybrid/overflow.h>

#include <kos/except.h>
#include <kos/except/reason/inval.h>

#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

DECL_BEGIN

/* Assert that struct offsets between `struct mbnode' and `struct mnode'
 * are such that binary compatibility is possible. */
static_assert(sizeof(struct mnode) == sizeof(struct mbnode));
static_assert(alignof(struct mnode) <= alignof(struct mbnode));
static_assert(offsetof(struct mnode, mn_flags) == offsetof(struct mbnode, mbn_flags));
static_assert(offsetof(struct mnode, mn_minaddr) == offsetof(struct mbnode, mbn_minaddr));
static_assert(offsetof(struct mnode, mn_maxaddr) == offsetof(struct mbnode, mbn_maxaddr));
static_assert(offsetof(struct mnode, mn_mement) == offsetof(struct mbnode, mbn_mement));
static_assert(offsetof(struct mnode, mn_part) == offsetof(struct mbnode, mbn_part));
static_assert(offsetof(struct mnode, mn_fspath) == offsetof(struct mbnode, mbn_fspath));
static_assert(offsetof(struct mnode, mn_fsname) == offsetof(struct mbnode, mbn_fsname));
static_assert(offsetof(struct mnode, _mn_alloc) == offsetof(struct mbnode, _mbn_alloc));
static_assert(offsetof(struct mnode, _mn_alloc.sle_next) == offsetof(struct mbnode, mbn_filnxt));
static_assert(offsetof(struct mnode, mn_mman) == offsetof(struct mbnode, _mbn_mman));
static_assert(offsetof(struct mnode, mn_partoff) == offsetof(struct mbnode, _mbn_partoff));
static_assert(offsetof(struct mnode, mn_link) == offsetof(struct mbnode, _mbn_link));
static_assert(offsetof(struct mnode, mn_writable) == offsetof(struct mbnode, _mbn_writable));
static_assert(offsetof(struct mnode, mn_module) == offsetof(struct mbnode, _mbn_module));
static_assert(offsetof(struct mnode, mn_writable) == offsetof(struct mbnode, mbn_nxtuprt),
              "This is needed so that all non-unique-part nodes already have their writable "
              "link initialized as unbound, and all unique-part nodes can still be enumerated "
              "in `mbuilder_apply_impl' after the new node-tree has been assigned to the target "
              "mman, and all of the part<->node links have been set-up.");


#if !defined(NDEBUG) && !defined(NDEBUG_FINI)
#define DBG_memset memset
#else /* !NDEBUG && !NDEBUG_FINI */
#define DBG_memset(...) (void)0
#endif /* NDEBUG || NDEBUG_FINI */

#define file_mbnode_destroy(self) \
	(decref((self)->mbn_file), mbnode_destroy(self))

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mbnode_destroy)(struct mbnode *__restrict self) {
	decref(self->mbn_part);
	xdecref(self->mbn_fspath);
	xdecref(self->mbn_fsname);
	kfree(self);
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mbuilder_destroy_tree)(struct mbnode *__restrict self) {
	struct mbnode *lo, *hi;
again:
	lo = self->mbn_mement.rb_lhs;
	hi = self->mbn_mement.rb_rhs;
	mbnode_destroy(self);
	if (lo) {
		if (hi)
			mbuilder_destroy_tree(hi);
		self = lo;
		goto again;
	}
	if (hi) {
		self = hi;
		goto again;
	}
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mnode_tree_destroy)(struct mnode *__restrict self) {
	struct mnode *lo, *hi;
again:
	lo = self->mn_mement.rb_lhs;
	hi = self->mn_mement.rb_rhs;
	mnode_destroy(self);
	if (lo) {
		if (hi)
			mnode_tree_destroy(hi);
		self = lo;
		goto again;
	}
	if (hi) {
		self = hi;
		goto again;
	}
}


/* Many binary formats contain the concept of a bss-overlap page.
 * This is a page of memory that contains a leading portion  that
 * is initialized from a file, as well as a trailing portion that
 * is initialized as all zeroes.
 *
 * Creating a node to represent this is normally rather hard,
 * but can  be simplified  by making  use of  this  function.
 *
 * This creates an already-initialized mbnode pointing to an  mpart
 * describing a single page,  who's leading `head_size' bytse  have
 * been loaded from `head_file', while tailing `PAGESIZE-head_size'
 * bytes have been zero-initialized.
 *
 * The caller must still initialize:
 *  - return->mbn_minaddr = ...
 *  - return->mbn_maxaddr = return->mbn_minaddr + PAGESIZE - 1
 *  - return->mbn_flags   = ...
 * Afterwards,   insert   into  an   mbuilder  using:
 * >> mbuilder_insert_fmnode(&builder, overlap_node);
 *
 * @param: head_file: The file from which to load head data.
 * @param: head_fpos: File position of head data.
 * @param: head_size: Head data sizes (in bytes; < PAGESIZE) */
PUBLIC ATTR_RETNONNULL WUNUSED NONNULL((1)) struct mbnode *KCALL
mbnode_create_partialbss(struct mfile *__restrict head_file,
                         pos_t head_fpos, size_t head_size) {
	struct mbnode *node;
	struct mpart *part;
	physpage_t overlap_page;
	assertf(head_size <= PAGESIZE, "Head size too large (must fit a single page)");
	assertf(head_size != PAGESIZE, "Then why wouldn't you use a normal file-map?");
	node = (struct mbnode *)kmalloc(sizeof(struct mbnode),
	                                GFP_LOCKED | GFP_PREFLT);
	TRY {
		part = (struct mpart *)kmalloc(sizeof(struct mpart),
		                               GFP_LOCKED | GFP_PREFLT);
		TRY {
			overlap_page = page_mallocone();
			if unlikely(overlap_page == PHYSPAGE_INVALID)
				THROW(E_BADALLOC_INSUFFICIENT_PHYSICAL_MEMORY, PAGESIZE);
			TRY {
				/* Load the overlapping file data into memory. */
				mfile_readall_p(head_file, physpage2addr(overlap_page),
				                head_size, head_fpos);

				/* Check if we must zero-initialize the BSS portion. */
				if (!page_iszero(overlap_page)) {
					/* Zero-initialize the BSS portion */
					memsetphys_onepage(physpage2addr(overlap_page) + head_size,
					                   0, PAGESIZE - head_size);
				}
			} EXCEPT {
				page_free(overlap_page, 1);
				RETHROW();
			}
		} EXCEPT {
			kfree(part);
			RETHROW();
		}
	} EXCEPT {
		kfree(node);
		RETHROW();
	}

	/* Initialize... */
	part->mp_refcnt = 1;
	part->mp_xflags = MPART_XF_NORMAL;
	part->mp_flags  = MPART_F_NORMAL;
	part->mp_state  = MPART_ST_MEM;
	part->mp_file   = incref(&mfile_zero);
	LIST_INIT(&part->mp_copy);
	LIST_INIT(&part->mp_share);
	SLIST_INIT(&part->mp_lockops);
	/*part->mp_allparts*/ /* Initialized by `mpart_all_list_insert' */
	DBG_memset(&part->mp_changed, 0xcc, sizeof(part->mp_changed));
	part->mp_minaddr      = (pos_t)(0);
	part->mp_maxaddr      = (pos_t)(PAGESIZE - 1);
	_mpart_init_asanon(part);
	part->mp_blkst_ptr    = NULL;
	part->mp_mem.mc_start = overlap_page;
	part->mp_mem.mc_size  = 1;
	part->mp_meta         = NULL;

	/* Add the part to the list of all parts. */
	mpart_all_list_insert(part);

	/*node->mbn_minaddr;*/ /* Initialized by the caller */
	/*node->mbn_maxaddr;*/ /* Initialized by the caller */
	/*node->mbn_flags;*/   /* Initialized by the caller */
	node->mbn_part   = part; /* Inherit reference */
	node->mbn_filnxt = NULL; /* Single-node mapping */
	node->mbn_fspath = NULL; /* Unused */
	node->mbn_fsname = NULL; /* Unused */
	node->mbn_file   = incref(&mfile_zero); /* Unused, but must be non-NULL */
	mnode_mbn_filpos_set(node, 0);

	return node;
}


/* Finalize the given mem-builder. */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mbuilder_norpc_fini)(struct mbuilder_norpc *__restrict self) {
	struct mbnode *iter;

	/* Drop file references. */
	SLIST_FOREACH (iter, &self->mb_files, mbn_nxtfile) {
		decref(iter->mbn_file);
	}

	/* Destroy the tree of mappings. */
	if unlikely(self->mb_mappings != NULL)
		mbuilder_destroy_tree(self->mb_mappings);

	/* Free all nodes that remained within the free-list. */
	iter = SLIST_FIRST(&self->_mb_fbnodes);
	while (iter) {
		struct mbnode *next;
		next = SLIST_NEXT(iter, _mbn_alloc);
		kfree(iter);
		iter = next;
	}

	DBG_memset(self, 0xcc, sizeof(*self));
}

/* Finalize the given mem-builder. */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mbuilder_fini)(struct mbuilder *__restrict self) {

	/* Destroy the old mappings tree (as inherited during in `mbuilder_apply()'). */
	if likely(self->mb_oldmap != NULL)
		mnode_tree_destroy(self->mb_oldmap);

	/* Free all RPC descriptors that may still be allocated */
	while unlikely(!SLIST_EMPTY(&self->mb_killrpc)) {
		struct pending_rpc *rpc;
		rpc = SLIST_FIRST(&self->mb_killrpc);
		SLIST_REMOVE_HEAD(&self->mb_killrpc, pr_link);
		assert(!(rpc->pr_flags & _RPC_CONTEXT_DONTFREE));
		pending_rpc_free(rpc);
	}
	mbuilder_norpc_fini(self);
}



/************************************************************************/
/* Functions for populating MBUILDER                                    */
/************************************************************************/

/* Check if `part' is already referenced by `self' */
PRIVATE NOBLOCK ATTR_PURE NONNULL((1, 2)) bool
NOTHROW(FCALL mbuilder_uparts_contains)(struct mbuilder_norpc const *__restrict self,
                                        struct mpart const *__restrict part) {
	struct mbnode const *node;
	struct mbnode_list list;
	list = *mbnode_partset_listof(&self->mb_uparts, part);
	LIST_FOREACH (node, &list, mbn_nxtuprt) {
		if (node->mbn_part == part)
			return true;
	}
	return false;
}

PRIVATE NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL mbuilder_uparts_insert)(struct mbuilder_norpc *__restrict self,
                                      struct mbnode *__restrict node) {
	struct mbnode_list *list;
	list = mbnode_partset_listof(&self->mb_uparts, node->mbn_part);
	LIST_INSERT_HEAD(list, node, mbn_nxtuprt);
}



PRIVATE NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL mbuilder_insert_anon_file_node)(struct mbuilder_norpc *__restrict self,
                                              /*inherit(always)*/ struct mbnode *__restrict node) {
	mbuilder_uparts_insert(self, node);
	SLIST_INSERT(&self->mb_files, node, mbn_nxtfile);
	mbnode_tree_insert(&self->mb_mappings, node); /* Inherit */
}



PRIVATE ATTR_RETNONNULL WUNUSED struct mnode *FCALL
mbuilder_create_res_file_node(PAGEDIR_PAGEALIGNED void *addr,
                              PAGEDIR_PAGEALIGNED size_t num_bytes)
		THROWS(E_BADALLOC) {
	struct mnode *result;
	result = (struct mnode *)kmalloc(sizeof(struct mnode), GFP_LOCKED);
	result->mn_minaddr = (byte_t *)addr;
	result->mn_maxaddr = (byte_t *)addr + num_bytes - 1;
	result->mn_part    = NULL; /* Reserved node */
	result->mn_fspath  = NULL;
	result->mn_fsname  = NULL;
	result->mn_mman    = NULL;
	result->mn_partoff = 0;
	DBG_memset(&result->mn_mman, 0xcc, sizeof(result->mn_mman));
	DBG_memset(&result->mn_module, 0xcc, sizeof(result->mn_module));
	DBG_memset(&result->mn_link, 0xcc, sizeof(result->mn_link));
	LIST_ENTRY_UNBOUND_INIT(&result->mn_writable);
	return result;
}



PRIVATE ATTR_RETNONNULL WUNUSED struct mbnode *FCALL
mbuilder_create_zero_file_node(PAGEDIR_PAGEALIGNED void *addr,
                               PAGEDIR_PAGEALIGNED size_t num_bytes,
                               uintptr_t mnode_flags)
		THROWS(E_BADALLOC) {
	struct mbnode *result;
	assert(IS_ALIGNED((uintptr_t)addr, PAGESIZE));
	assert(IS_ALIGNED(num_bytes, PAGESIZE));
	result = (struct mbnode *)kmalloc(sizeof(struct mbnode), GFP_LOCKED);
	result->mbn_minaddr = (byte_t *)addr;
	result->mbn_maxaddr = (byte_t *)addr + num_bytes - 1;
	TRY {
		result->mbn_part = mfile_makepart(&mfile_zero, 0, num_bytes);
	} EXCEPT {
		kfree(result);
	}
	result->mbn_flags  = mnode_flags;
	result->mbn_fspath = NULL;
	result->mbn_fsname = NULL;
	result->mbn_filnxt = NULL;     /* No secondary nodes required to map the file */
	/*result->mbn_nxtfile = ...;*/ /* Fill in by the caller */
	result->mbn_file   = incref(&mfile_zero);
	mnode_mbn_filpos_set(result, 0);
	return result;
}



/* Map a given file into the specified mbuilder.
 * Behaves  exactly  the  same  as  `mman_map()' */
PUBLIC NONNULL((1, 6)) void *KCALL
mbuilder_map(struct mbuilder_norpc *__restrict self,
             UNCHECKED void *hint, size_t num_bytes,
             unsigned int prot, unsigned int flags,
             struct mfile *__restrict file,
             struct path *file_fspath,
             struct fdirent *file_fsname,
             pos_t file_pos,
             size_t min_alignment,
             ptrdiff_t min_alignment_offset)
		THROWS(E_WOULDBLOCK, E_BADALLOC,
		       E_BADALLOC_INSUFFICIENT_VIRTUAL_MEMORY,
		       E_BADALLOC_ADDRESS_ALREADY_EXISTS) {
	void *result, *baseaddr;
	struct mfile_map fm;
	struct mbnode *fmnode, *iter;
	uintptr_t addend;

	/* We don't allow zero-sized file mappings! */
	if unlikely(num_bytes == 0) {
err_bad_length:
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_MMAP_LENGTH,
		      num_bytes);
	}

	addend = 0;
	if unlikely(file_pos & PAGEMASK) {
		addend = (uintptr_t)file_pos & PAGEMASK;
		/* When mapping to a fixed location, the in-page offset of the target
		 * address, and the in-page offset  of the file position must  match! */
		if ((flags & MAP_FIXED) && unlikely(((uintptr_t)hint & PAGEMASK) != addend)) {
er_bad_addr_alignment:
			THROW(E_INVALID_ARGUMENT_BAD_ALIGNMENT,
			      E_INVALID_ARGUMENT_CONTEXT_MMAP_ADDR,
			      (uintptr_t)hint, PAGEMASK, addend);
		}
		if (OVERFLOW_UADD(num_bytes, addend, &num_bytes))
			goto err_bad_length;
		file_pos &= ~PAGEMASK;
	} else {
		if ((flags & MAP_FIXED) && unlikely(((uintptr_t)hint & PAGEMASK) != 0))
			goto er_bad_addr_alignment;
	}

	/* Align the required map size by whole pages. */
	num_bytes = CEIL_ALIGN(num_bytes, PAGESIZE);
	baseaddr  = mbuilder_getunmapped(self, hint, num_bytes, flags,
	                                 min_alignment, min_alignment_offset);
	result    = baseaddr;
	if unlikely(num_bytes == 0)
		goto done;

	/* Load required data parts, and acquire */
	fm.mfm_file  = file;
	fm.mfm_addr  = file_pos;
	fm.mfm_size  = num_bytes;
	fm.mfm_prot  = prot;
	fm.mfm_flags = flags;
	SLIST_MOVE(&fm.mfm_flist, &self->_mb_fnodes);
	{
		RAII_FINALLY { SLIST_MOVE(&self->_mb_fnodes, &fm.mfm_flist); };
		_mfile_map_init(&fm);
	}

	/* Convert the node list into a `struct mbnode' */
	fmnode = (struct mbnode *)SLIST_FIRST(&fm.mfm_nodes);

	/* Fill in fields shared by all nodes. */
	iter = fmnode;

	for (;;) {
		struct mbnode *next;
		/* If this part isn't already being used, insert it into
		 * the list of unique mem-parts used by our mem-builder. */
		LIST_ENTRY_UNBOUND_INIT(&iter->mbn_nxtuprt);
		if (!mbuilder_uparts_contains(self, iter->mbn_part))
			mbuilder_uparts_insert(self, iter);
		iter->mbn_flags = mbnodeflags_from_mapflags(flags) |
		                  mnodeflags_from_prot(prot);
		iter->mbn_minaddr += (uintptr_t)baseaddr;
		iter->mbn_maxaddr += (uintptr_t)baseaddr;
		iter->mbn_fspath = xincref(file_fspath);
		iter->mbn_fsname = xincref(file_fsname);

		/* Insert the node into our builder's mapping-tree */
		mbnode_tree_insert(&self->mb_mappings, iter);

		next = iter->mbn_filnxt;
		if (!next)
			break;
		DBG_memset(&next->mbn_nxtfile, 0xcc, sizeof(iter->mbn_nxtfile));
		DBG_memset(&next->mbn_file, 0xcc, sizeof(iter->mbn_file));
		DBG_memset(&next->mbn_filpos, 0xcc, sizeof(iter->mbn_filpos));
		iter = next;
	}

	/* Fill in basic mapping information. */
	fmnode->mbn_file = incref(file);
	mnode_mbn_filpos_set(fmnode, file_pos);

	/* TODO: Merge adjacent nodes if possible */

	/* Remember this mapping as a consistent file-mapping. */
	SLIST_INSERT(&self->mb_files, fmnode, mbn_nxtfile);
done:
	return result;
}



/* Same as `mbuilder_map()', but only allow pages entirely contained within
 * the file-relative  address  range  `file_map_minaddr...file_map_maxaddr'
 * to  be mapped.  Attempting to map  file contents beyond  this range will
 * instead   result    in    `&mfile_zero'    getting    mapped    instead.
 * Behaves exactly the same as `mman_map_subrange()' */
PUBLIC NONNULL((1, 6)) void *KCALL
mbuilder_map_subrange(struct mbuilder_norpc *__restrict self,
                      UNCHECKED void *hint, size_t num_bytes,
                      unsigned int prot, unsigned int flags,
                      struct mfile *__restrict file,
                      struct path *file_fspath,
                      struct fdirent *file_fsname,
                      pos_t file_pos,
                      pos_t file_map_minaddr,
                      pos_t file_map_maxaddr,
                      size_t min_alignment,
                      ptrdiff_t min_alignment_offset)
		THROWS(E_WOULDBLOCK, E_BADALLOC,
		       E_BADALLOC_INSUFFICIENT_VIRTUAL_MEMORY,
		       E_BADALLOC_ADDRESS_ALREADY_EXISTS) {
	void *result, *baseaddr;
	struct mbnode *lonode, *hinode;
	uintptr_t addend;

	/* We don't allow zero-sized file mappings! */
	if unlikely(num_bytes == 0) {
err_bad_length:
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_MMAP_LENGTH,
		      num_bytes);
	}

	addend = 0;
	if unlikely(file_pos & PAGEMASK) {
		addend = (uintptr_t)file_pos & PAGEMASK;
		/* When mapping to a fixed location, the in-page offset of the target
		 * address, and the in-page offset  of the file position must  match! */
		if ((flags & MAP_FIXED) && unlikely(((uintptr_t)hint & PAGEMASK) != addend)) {
er_bad_addr_alignment:
			THROW(E_INVALID_ARGUMENT_BAD_ALIGNMENT,
			      E_INVALID_ARGUMENT_CONTEXT_MMAP_ADDR,
			      (uintptr_t)hint, PAGEMASK, addend);
		}
		if (OVERFLOW_UADD(num_bytes, addend, &num_bytes))
			goto err_bad_length;
		file_pos &= ~PAGEMASK;
	} else {
		if ((flags & MAP_FIXED) && unlikely(((uintptr_t)hint & PAGEMASK) != 0))
			goto er_bad_addr_alignment;
	}

	/* Align the required map size by whole pages. */
	num_bytes = CEIL_ALIGN(num_bytes, PAGESIZE);
	baseaddr  = mbuilder_getunmapped(self, hint, num_bytes, flags,
	                                 min_alignment, min_alignment_offset);
	result    = baseaddr;

	/* Make sure that the given file-bounds are properly aligned. */
	if unlikely(!IS_ALIGNED(file_map_minaddr, PAGESIZE))
		file_map_minaddr = CEIL_ALIGN(file_map_minaddr, PAGESIZE);
	if unlikely(!IS_ALIGNED(file_map_maxaddr + 1, PAGESIZE))
		file_map_maxaddr = FLOOR_ALIGN(file_map_maxaddr + 1, PAGESIZE) - 1;

	lonode = NULL;
	hinode = NULL;
	TRY {
		uintptr_t mnode_flags;
		mnode_flags = mbnodeflags_from_mapflags(flags) |
		              mnodeflags_from_prot(prot);

		/* Check if we need to create filler nodes before/after */
		if (file_pos < file_map_minaddr) {
			size_t gap;
			if (OVERFLOW_USUB(file_map_minaddr, file_pos, &gap))
				gap = (size_t)-1;
			if (gap > num_bytes)
				gap = num_bytes;
			lonode    = mbuilder_create_zero_file_node(baseaddr, gap, mnode_flags);
			baseaddr  = (byte_t *)baseaddr + gap;
			num_bytes = num_bytes - gap;
			file_pos  = file_map_minaddr;
		}

		/* Check the upper bound. */
		if (num_bytes > 0) {
			size_t max_file_size;
			if (file_pos >= file_map_maxaddr) {
				max_file_size = 0;
			} else {
				if (OVERFLOW_USUB(file_map_maxaddr, file_pos, &max_file_size) ||
				    OVERFLOW_UADD(max_file_size, 1, &max_file_size))
					max_file_size = SIZE_MAX;
			}
			/* Check if the requested size exceeds the allowed size. */
			if (num_bytes > max_file_size) {
				size_t gap;
				gap       = num_bytes - max_file_size;
				hinode    = mbuilder_create_zero_file_node(baseaddr, gap, mnode_flags);
				num_bytes = max_file_size;
			}
		}

		/* Map the actual file contents. */
		if (num_bytes > 0) {
			struct mfile_map fm;
			struct mbnode *fmnode, *iter;

			/* Load required data parts, and acquire  */
			fm.mfm_file  = file;
			fm.mfm_addr  = file_pos;
			fm.mfm_size  = num_bytes;
			fm.mfm_prot  = prot;
			fm.mfm_flags = flags;
			SLIST_MOVE(&fm.mfm_flist, &self->_mb_fnodes);
			{
				RAII_FINALLY { SLIST_MOVE(&self->_mb_fnodes, &fm.mfm_flist); };
				_mfile_map_init(&fm);
			}

			/* Convert the node list into a `struct mbnode' */
			fmnode = (struct mbnode *)SLIST_FIRST(&fm.mfm_nodes);

			/* Fill in fields shared by all nodes. */
			iter = fmnode;
			for (;;) {
				struct mbnode *next;
				iter->mbn_flags = mnode_flags;
				iter->mbn_minaddr += (uintptr_t)baseaddr;
				iter->mbn_maxaddr += (uintptr_t)baseaddr;
				iter->mbn_fspath = xincref(file_fspath);
				iter->mbn_fsname = xincref(file_fsname);

				/* If this part isn't already being used, insert it into
				 * the list of unique mem-parts used by our mem-builder. */
				LIST_ENTRY_UNBOUND_INIT(&iter->mbn_nxtuprt);
				if (!mbuilder_uparts_contains(self, iter->mbn_part))
					mbuilder_uparts_insert(self, iter);

				/* Insert the node into our builder's mapping-tree */
				mbnode_tree_insert(&self->mb_mappings, iter);

				next = iter->mbn_filnxt;
				if (!next)
					break;
				DBG_memset(&next->mbn_nxtfile, 0xcc, sizeof(iter->mbn_nxtfile));
				DBG_memset(&next->mbn_file, 0xcc, sizeof(iter->mbn_file));
				DBG_memset(&next->mbn_filpos, 0xcc, sizeof(iter->mbn_filpos));
				iter = next;
			}

			/* Fill in basic mapping information. */
			fmnode->mbn_file = incref(file);
			mnode_mbn_filpos_set(fmnode, file_pos);

			/* Remember this mapping as a consistent file-mapping. */
			SLIST_INSERT(&self->mb_files, fmnode, mbn_nxtfile);
		}
	} EXCEPT {
		if (lonode != NULL)
			file_mbnode_destroy(lonode);
		if (hinode != NULL)
			file_mbnode_destroy(hinode);
		RETHROW();
	}

	/* If they'd been created, insert and link-in nodes for
	 * the gap below and/or above the actual file  mapping. */
	if (lonode != NULL)
		mbuilder_insert_anon_file_node(self, lonode);
	if (hinode != NULL)
		mbuilder_insert_anon_file_node(self, hinode);

	/* TODO: Merge adjacent nodes if possible */
	return (byte_t *)result + addend;
}



/* Same as  `mbuilder_map()', but  instead of  actually mapping  something, leave  the
 * address range as empty (but possibly prepared), making it a reserved address range.
 * Behaves exactly the same as `mman_map_res()' */
PUBLIC NONNULL((1)) void *KCALL
mbuilder_map_res(struct mbuilder_norpc *__restrict self,
                 UNCHECKED void *hint, size_t num_bytes,
                 unsigned int flags, size_t min_alignment,
                 ptrdiff_t min_alignment_offset)
		THROWS(E_WOULDBLOCK, E_BADALLOC,
		       E_BADALLOC_INSUFFICIENT_VIRTUAL_MEMORY,
		       E_BADALLOC_ADDRESS_ALREADY_EXISTS) {
	struct mbnode *fmnode;
	void *result, *baseaddr;

	/* We don't allow zero-sized file mappings! */
	if unlikely(num_bytes == 0) {
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_MMAP_LENGTH,
		      num_bytes);
	}

	/* Align the required map size by whole pages. */
	num_bytes = CEIL_ALIGN(num_bytes, PAGESIZE);
	baseaddr  = mbuilder_getunmapped(self, hint, num_bytes, flags,
	                                 min_alignment, min_alignment_offset);
	result    = baseaddr;

	/* TODO: Extend adjacent nodes if possible */

	/* Construct the memory-reservation node. */
	fmnode = (struct mbnode *)mbuilder_create_res_file_node(baseaddr, num_bytes);

	/* Insert the node into the mem-builder.
	 * Note that we don't add the part to the files- or uparts lists,
	 * but  only to the mappings tree, since the node doesn't contain
	 * a mem-file or mem-part. */
	mbnode_tree_insert(&self->mb_mappings, fmnode); /* Inherit */
	return result;
}


/* MBuilder-version of `mman_getunmapped_or_unlock()' (without the unlock-part)
 * But  note  that unlike  `mman_getunmapped_or_unlock()', this  version always
 * acts  as though  `MAP_FIXED_NOREPLACE' was  given when  `MAP_FIXED' is used.
 * After  all: there  is no functionality  for removing nodes  from an mbuilder
 * once they've been added. Not because  this would be impossible, but  because
 * such functionality is never required.
 * Also: This function never returns `MAP_FAILED'! */
PUBLIC NOBLOCK WUNUSED NONNULL((1)) PAGEDIR_PAGEALIGNED void *FCALL
mbuilder_getunmapped(struct mbuilder_norpc *__restrict self, void *addr,
                     size_t num_bytes, unsigned int flags,
                     size_t min_alignment, ptrdiff_t min_alignment_offset)
		THROWS(E_BADALLOC_INSUFFICIENT_VIRTUAL_MEMORY,
		       E_BADALLOC_ADDRESS_ALREADY_EXISTS) {
	void *result;
	/* Deal with MAP_FIXED */
	if (flags & MAP_FIXED) {
		struct mbnode *node;
		byte_t *maxaddr;
		result  = (void *)FLOOR_ALIGN((uintptr_t)addr, PAGESIZE);
		maxaddr = (byte_t *)addr + num_bytes - 1;
		node    = mbnode_tree_rlocate(self->mb_mappings, addr, maxaddr);
		if unlikely(node != NULL) {
			/* Always behave as through `MAP_FIXED_NOREPLACE' had been given. */
			void *node_minaddr, *node_maxaddr;
			node_minaddr = mbnode_getminaddr(node);
			node_maxaddr = mbnode_getmaxaddr(node);
			THROW(E_BADALLOC_ADDRESS_ALREADY_EXISTS,
			      addr, maxaddr,
			      node_minaddr, node_maxaddr);
		}
	} else {
		/* Normal case: automatically select a free location. */
		result = mbuilder_findunmapped(self, addr, num_bytes,
		                               flags, min_alignment,
		                               min_alignment_offset);
		if unlikely(result == MAP_FAILED)
			THROW(E_BADALLOC_INSUFFICIENT_VIRTUAL_MEMORY, num_bytes);
	}
	return result;
}



/* Insert or remove a raw mem-node `fmnode' from self.
 * This function does:
 *  - assert(fmnode->mbn_part != NULL);
 *  - assert(fmnode->mbn_file != NULL);
 *  - fmnode->mbn_filnxt = NULL;       // Only  single-nde   initial   mappings   are   supported.
 *                                     // Additional  required nodes are added lazily if necessary
 *                                     // via the re-flow mechanism that is done as part of a call
 *                                     // to `mbuilder_partlocks_acquire_or_unlock()'
 *  - SLIST_INSERT(&self->mb_files, fmnode, mbn_nxtfile);
 *  - LIST_INSERT_HEAD(mbnode_partset_listof(&self->mb_uparts,
 *                                           fmnode->mbn_part),
 *                     fmnode, mbn_nxtuprt);
 *  - mbnode_tree_insert(&self->mb_mappings, fmnode);
 * As such, the caller must initialize:
 *  - fmnode->mbn_minaddr  (Mapping min address)
 *  - fmnode->mbn_maxaddr  (Mapping max address)
 *  - fmnode->mbn_flags    (Mapping flags)
 *  - fmnode->mbn_part     (as some part from `fmnode->mbn_file')
 *  - fmnode->mbn_fspath   (optional: filesystem path)
 *  - fmnode->mbn_fsname   (optional: filesystem name)
 *  - fmnode->mbn_filpos   (Wanted in-file mapping address)
 *  - fmnode->mbn_file     (The actual file being mapped) */
PUBLIC NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL mbuilder_insert_fmnode)(struct mbuilder_norpc *__restrict self,
                                      struct mbnode *__restrict fmnode) {
	assert(fmnode->mbn_part != NULL);
	assert(fmnode->mbn_file != NULL);
	fmnode->mbn_filnxt = NULL;
	SLIST_INSERT(&self->mb_files, fmnode, mbn_nxtfile);
	LIST_INSERT_HEAD(mbnode_partset_listof(&self->mb_uparts,
	                                       fmnode->mbn_part),
	                 fmnode, mbn_nxtuprt);
	mbnode_tree_insert(&self->mb_mappings, fmnode);
}

/* Remove `fmnode' from `self'. - Asserts that no secondary nodes have
 * been allocated for use with `fmnode' (as could happen if the caller
 * uses `mbuilder_partlocks_acquire_or_unlock()' between a prior  call
 * to `mbuilder_insert_fmnode()' and the call to this function) */
PUBLIC NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL mbuilder_remove_fmnode)(struct mbuilder_norpc *__restrict self,
                                      struct mbnode *__restrict fmnode) {
	assert(fmnode->mbn_part != NULL);
	assert(fmnode->mbn_file != NULL);
	assert(fmnode->mbn_filnxt == NULL);
	mbnode_tree_removenode(&self->mb_mappings, fmnode);
	LIST_REMOVE(fmnode, mbn_nxtuprt);
	SLIST_REMOVE(&self->mb_files, fmnode, mbn_nxtfile); /* WARNING: O(n) operation! */
	DBG_memset(&fmnode->mbn_mement, 0xcc, sizeof(fmnode->mbn_mement));
	DBG_memset(&fmnode->mbn_nxtuprt, 0xcc, sizeof(fmnode->mbn_nxtuprt));
	DBG_memset(&fmnode->mbn_nxtfile, 0xcc, sizeof(fmnode->mbn_nxtfile));
}


DECL_END

#endif /* !GUARD_KERNEL_SRC_MEMORY_MBUILDER_C */
