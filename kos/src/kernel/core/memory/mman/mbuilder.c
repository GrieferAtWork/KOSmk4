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
#ifndef GUARD_KERNEL_SRC_MEMORY_MBUILDER_C
#define GUARD_KERNEL_SRC_MEMORY_MBUILDER_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <fs/node.h>
#include <fs/vfs.h>
#include <kernel/malloc.h>
#include <kernel/mman/mbuilder.h>
#include <kernel/mman/mfile.h>
#include <kernel/mman/mm-flags.h>
#include <kernel/mman/mnode.h>
#include <kernel/mman/mpart.h>

#include <hybrid/align.h>
#include <hybrid/overflow.h>

#include <assert.h>
#include <stddef.h>
#include <string.h>

DECL_BEGIN

/* Assert that struct offsets between `struct mbnode' and `struct mnode'
 * are such that binary compatibility is possible. */
STATIC_ASSERT(offsetof(struct mnode, mn_flags) == offsetof(struct mbnode, mbn_flags));
STATIC_ASSERT(offsetof(struct mnode, mn_minaddr) == offsetof(struct mbnode, mbn_minaddr));
STATIC_ASSERT(offsetof(struct mnode, mn_maxaddr) == offsetof(struct mbnode, mbn_maxaddr));
STATIC_ASSERT(offsetof(struct mnode, mn_mement) == offsetof(struct mbnode, mbn_mement));
STATIC_ASSERT(offsetof(struct mnode, mn_part) == offsetof(struct mbnode, mbn_part));
STATIC_ASSERT(offsetof(struct mnode, mn_fspath) == offsetof(struct mbnode, mbn_fspath));
STATIC_ASSERT(offsetof(struct mnode, mn_fsname) == offsetof(struct mbnode, mbn_fsname));
STATIC_ASSERT(offsetof(struct mnode, _mn_alloc) == offsetof(struct mbnode, _mbn_alloc));
STATIC_ASSERT(offsetof(struct mnode, _mn_alloc.sle_next) == offsetof(struct mbnode, mbn_filnxt));
STATIC_ASSERT(offsetof(struct mnode, mn_mman) == offsetof(struct mbnode, _mbn_mman));
STATIC_ASSERT(offsetof(struct mnode, mn_partoff) == offsetof(struct mbnode, _mbn_partoff));
STATIC_ASSERT(offsetof(struct mnode, mn_link) == offsetof(struct mbnode, _mbn_link));
STATIC_ASSERT(offsetof(struct mnode, mn_writable) == offsetof(struct mbnode, _mbn_writable));


#ifndef NDEBUG
#define DBG_memset(dst, byte, num_bytes) memset(dst, byte, num_bytes)
#else /* !NDEBUG */
#define DBG_memset(dst, byte, num_bytes) (void)0
#endif /* NDEBUG */

#define file_mbnode_destroy(self) \
	(decref((self)->mbn_file), mbnode_destroy(self))

PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mbnode_destroy)(struct mbnode *__restrict self) {
	decref(self->mbn_part);
	xdecref(self->mbn_fspath);
	xdecref(self->mbn_fsname);
	kfree(self);
}

PUBLIC NOBLOCK NONNULL((1)) void
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

/* Finalize the given mem-builder. */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mbuilder_fini)(struct mbuilder *__restrict self) {
	struct mbnode *iter;

	/* Drop file references. */
	SLIST_FOREACH(iter, &self->mb_files, mbn_nxtfile) {
		decref(iter->mbn_file);
	}

	/* Destroy the tree of mappings. */
	if (self->mb_mappings != NULL)
		mbuilder_destroy_tree(self->mb_mappings);

	/* Free all nodes that remained within the free-list. */
	iter = SLIST_FIRST(&self->mb_fparts);
	while (iter) {
		struct mbnode *next;
		next = SLIST_NEXT(iter, _mbn_alloc);
		kfree(iter);
		iter = next;
	}

	DBG_memset(self, 0xcc, sizeof(*self));
}



/************************************************************************/
/* Functions for populating MBUILDER                                    */
/************************************************************************/

#ifndef __INTELLISENSE__
#define DEFINE_mbuilder_getunmapped_nx
#include "mm-unmapped.c.inl"
#define DEFINE_mbuilder_getunmapped
#include "mm-unmapped.c.inl"
#endif /* !__INTELLISENSE__ */

/* Check if `part' is already referenced by `self' */
PRIVATE NOBLOCK NONNULL((1, 2)) bool
NOTHROW(FCALL mbuilder_contains_mpart)(struct mbuilder *__restrict self,
                                       struct mpart *__restrict part) {
	struct mbnode *iter;
	SLIST_FOREACH(iter, &self->mb_uparts, mbn_nxtuprt) {
		if (iter->mbn_part == part)
			return true;
	}
	return false;
}


PRIVATE NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL mbuilder_insert_anon_file_node)(struct mbuilder *__restrict self,
                                              /*inherit(always)*/ struct mbnode *__restrict node) {
	SLIST_INSERT(&self->mb_uparts, node, mbn_nxtuprt);
	SLIST_INSERT(&self->mb_files, node, mbn_nxtfile);
	mbnode_tree_insert(&self->mb_mappings, node); /* Inherit */
}



PRIVATE WUNUSED ATTR_RETNONNULL struct mbnode *FCALL
mbuilder_create_res_file_node(PAGEDIR_PAGEALIGNED void *addr,
                              PAGEDIR_PAGEALIGNED size_t num_bytes) {
	struct mbnode *result;
	result = (struct mbnode *)kmalloc(sizeof(struct mbnode), GFP_LOCKED);
	result->mbn_minaddr = (byte_t *)addr;
	result->mbn_maxaddr = (byte_t *)addr + num_bytes - 1;
	result->mbn_part    = NULL; /* Reserved node */
	result->mbn_fspath  = NULL;
	result->mbn_fsname  = NULL;
	result->mbn_filnxt  = NULL;
	DBG_memset(&result->mbn_nxtfile, 0xcc, sizeof(result->mbn_nxtfile));
	DBG_memset(&result->mbn_file, 0xcc, sizeof(result->mbn_file));
	DBG_memset(&result->mbn_filpos, 0xcc, sizeof(result->mbn_filpos));
	return result;
}



PRIVATE WUNUSED ATTR_RETNONNULL struct mbnode *FCALL
mbuilder_create_zero_file_node(PAGEDIR_PAGEALIGNED void *addr,
                               PAGEDIR_PAGEALIGNED size_t num_bytes) {
	struct mbnode *result;
	result = (struct mbnode *)kmalloc(sizeof(struct mbnode), GFP_LOCKED);
	result->mbn_minaddr = (byte_t *)addr;
	result->mbn_maxaddr = (byte_t *)addr + num_bytes - 1;
	TRY {
		result->mbn_part = mfile_makepart(&mfile_zero, 0, num_bytes);
	} EXCEPT {
		kfree(result);
	}
	result->mbn_fspath = NULL;
	result->mbn_fsname = NULL;
	result->mbn_filnxt = NULL;     /* No secondary nodes required to map the file */
	/*result->mbn_nxtfile = ...;*/ /* Fill in by the caller */
	result->mbn_file   = incref(&mfile_zero);
	result->mbn_filpos = 0;
	return result;
}




/* Map a given file into the specified mbuilder.
 * Behaves exactly the same as `mman_map()' */
PUBLIC NONNULL((1, 6)) void *KCALL
mbuilder_map(struct mbuilder *__restrict self,
             UNCHECKED void *hint, size_t num_bytes,
             unsigned int prot, unsigned int flags,
             struct mfile *__restrict file,
             struct path *file_fspath,
             struct directory_entry *file_fsname,
             pos_t file_pos,
             size_t min_alignment)
		THROWS(E_WOULDBLOCK, E_BADALLOC,
		       E_BADALLOC_INSUFFICIENT_VIRTUAL_MEMORY,
		       E_BADALLOC_ADDRESS_ALREADY_EXISTS) {
	void *result, *baseaddr;
	struct mfile_map filemap;
	struct mbnode *fmnode, *iter;
	if unlikely(file_pos & PAGEMASK) {
		size_t addend;
		addend = ((size_t)file_pos & PAGEMASK);
		result = (byte_t *)baseaddr + addend;
		num_bytes += addend;
		file_pos &= ~PAGEMASK;
	}
	num_bytes = CEIL_ALIGN(num_bytes, PAGESIZE);
	baseaddr  = mbuilder_getunmapped(self, hint, num_bytes, flags, min_alignment);
	result    = baseaddr;
	if unlikely(num_bytes == 0)
		goto done;

	/* Load required data parts, and acquire  */
	mfile_map_init(&filemap, file, file_pos, num_bytes, &self->_mb_fnodes);

	/* Convert the node list into a `struct mbnode' */
	fmnode = (struct mbnode *)SLIST_FIRST(&filemap.mfm_nodes);

	/* Fill in fields shared by all nodes. */
	iter = fmnode;
	do {
		iter->mbn_flags = mnodeflags_from_mapflags_with_populate(flags) |
		                  mnodeflags_from_prot(prot);
		iter->mbn_minaddr += (uintptr_t)baseaddr;
		iter->mbn_maxaddr += (uintptr_t)baseaddr;
		iter->mbn_fspath = xincref(file_fspath);
		iter->mbn_fsname = xincref(file_fsname);
		DBG_memset(&iter->mbn_nxtfile, 0xcc, sizeof(iter->mbn_nxtfile));
		DBG_memset(&iter->mbn_file, 0xcc, sizeof(iter->mbn_file));
		DBG_memset(&iter->mbn_filpos, 0xcc, sizeof(iter->mbn_filpos));
		DBG_memset(&iter->mbn_nxtuprt, 0xcc, sizeof(iter->mbn_nxtuprt));

		/* If this part isn't already being used, insert it into
		 * the list of unique mem-parts used by our mem-builder. */
		if (!mbuilder_contains_mpart(self, iter->mbn_part))
			SLIST_INSERT(&self->mb_uparts, iter, mbn_nxtuprt);

		/* Insert the node into our builder's mapping-tree */
		mbnode_tree_insert(&self->mb_mappings, iter);
	} while ((iter = iter->mbn_filnxt) != NULL);

	/* Fill in basic mapping information. */
	fmnode->mbn_file   = incref(file);
	fmnode->mbn_filpos = file_pos;

	/* Remember this mapping as a consistent file-mapping. */
	SLIST_INSERT(&self->mb_files, fmnode, mbn_nxtfile);
done:
	return result;
}



/* Same as `mbuilder_map()', but only allow pages entirely contained within
 * the file-relative address range `file_map_minaddr...file_map_maxaddr'
 * to be mapped. Attempting to map file contents beyond this range will
 * instead result in `&mfile_zero' getting mapped instead.
 * Behaves exactly the same as `mman_map_subrange()' */
PUBLIC NONNULL((1, 6)) void *KCALL
mbuilder_map_subrange(struct mbuilder *__restrict self,
                      UNCHECKED void *hint, size_t num_bytes,
                      unsigned int prot, unsigned int flags,
                      struct mfile *__restrict file,
                      struct path *file_fspath,
                      struct directory_entry *file_fsname,
                      pos_t file_pos,
                      pos_t file_map_minaddr,
                      pos_t file_map_maxaddr,
                      size_t min_alignment)
		THROWS(E_WOULDBLOCK, E_BADALLOC,
		       E_BADALLOC_INSUFFICIENT_VIRTUAL_MEMORY,
		       E_BADALLOC_ADDRESS_ALREADY_EXISTS) {
	void *result, *baseaddr;
	struct mbnode *lonode, *hinode;
	if unlikely(file_pos & PAGEMASK) {
		size_t addend;
		addend = ((size_t)file_pos & PAGEMASK);
		result = (byte_t *)baseaddr + addend;
		num_bytes += addend;
		file_pos &= ~PAGEMASK;
	}
	num_bytes = CEIL_ALIGN(num_bytes, PAGESIZE);
	baseaddr  = mbuilder_getunmapped(self, hint, num_bytes, flags, min_alignment);
	result    = baseaddr;
	if unlikely(num_bytes == 0)
		goto done;

	/* Make sure that the given file-bounds are properly aligned. */
	if unlikely(!IS_ALIGNED(file_map_minaddr, PAGESIZE))
		file_map_minaddr = CEIL_ALIGN(file_map_minaddr, PAGESIZE);
	if unlikely(!IS_ALIGNED(file_map_maxaddr + 1, PAGESIZE))
		file_map_maxaddr = FLOOR_ALIGN(file_map_maxaddr + 1, PAGESIZE) - 1;

	lonode = NULL;
	hinode = NULL;

	TRY {

		/* Check if we need to create filler nodes before/after */
		if (file_pos < file_map_minaddr) {
			size_t gap;
			if (OVERFLOW_USUB(file_map_minaddr, file_pos, &gap))
				gap = (size_t)-1;
			if (gap > num_bytes)
				gap = num_bytes;
			lonode    = mbuilder_create_zero_file_node(baseaddr, gap);
			baseaddr  = (byte_t *)baseaddr + gap;
			num_bytes = num_bytes - gap;
			file_pos  = file_map_minaddr;
		}

		/* Check the upper bound. */
		if (num_bytes > 0) {
			size_t max_file_size;
			if (OVERFLOW_USUB((file_map_maxaddr + 1), file_pos, &max_file_size))
				max_file_size = 0;
			/* Check if the requested size exceeds the allowed size. */
			if (max_file_size < num_bytes) {
				size_t gap;
				gap       = num_bytes - max_file_size;
				hinode    = mbuilder_create_zero_file_node(baseaddr, gap);
				num_bytes = max_file_size;
			}
		}

		/* Map the actual file contents. */
		if (num_bytes > 0) {
			struct mfile_map filemap;
			struct mbnode *fmnode, *iter;

			/* Load required data parts, and acquire  */
			mfile_map_init(&filemap, file, file_pos, num_bytes, &self->_mb_fnodes);

			/* Convert the node list into a `struct mbnode' */
			fmnode = (struct mbnode *)SLIST_FIRST(&filemap.mfm_nodes);

			/* Fill in fields shared by all nodes. */
			iter = fmnode;
			do {
				iter->mbn_flags = mnodeflags_from_mapflags_with_populate(flags) |
				                  mnodeflags_from_prot(prot);
				iter->mbn_minaddr += (uintptr_t)baseaddr;
				iter->mbn_maxaddr += (uintptr_t)baseaddr;
				iter->mbn_fspath = xincref(file_fspath);
				iter->mbn_fsname = xincref(file_fsname);
				DBG_memset(&iter->mbn_nxtfile, 0xcc, sizeof(iter->mbn_nxtfile));
				DBG_memset(&iter->mbn_file, 0xcc, sizeof(iter->mbn_file));
				DBG_memset(&iter->mbn_filpos, 0xcc, sizeof(iter->mbn_filpos));
				DBG_memset(&iter->mbn_nxtuprt, 0xcc, sizeof(iter->mbn_nxtuprt));

				/* If this part isn't already being used, insert it into
				 * the list of unique mem-parts used by our mem-builder. */
				if (!mbuilder_contains_mpart(self, iter->mbn_part))
					SLIST_INSERT(&self->mb_uparts, iter, mbn_nxtuprt);

				/* Insert the node into our builder's mapping-tree */
				mbnode_tree_insert(&self->mb_mappings, iter);
			} while ((iter = iter->mbn_filnxt) != NULL);

			/* Fill in basic mapping information. */
			fmnode->mbn_file   = incref(file);
			fmnode->mbn_filpos = file_pos;

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
	 * the gap below and/or above the actual file mapping. */
	if (lonode != NULL)
		mbuilder_insert_anon_file_node(self, lonode);
	if (hinode != NULL)
		mbuilder_insert_anon_file_node(self, hinode);

done:
	return result;
}



/* Same as `mbuilder_map()', but instead of actually mapping something, leave the
 * address range as empty (but possibly prepared), making it a reserved address range.
 * Behaves exactly the same as `mman_map_res()' */
PUBLIC NONNULL((1)) void *KCALL
mbuilder_map_res(struct mbuilder *__restrict self,
                 UNCHECKED void *hint, size_t num_bytes,
                 unsigned int flags, size_t min_alignment)
		THROWS(E_WOULDBLOCK, E_BADALLOC,
		       E_BADALLOC_INSUFFICIENT_VIRTUAL_MEMORY,
		       E_BADALLOC_ADDRESS_ALREADY_EXISTS) {
	void *result, *baseaddr;
	num_bytes = CEIL_ALIGN(num_bytes, PAGESIZE);
	baseaddr  = mbuilder_getunmapped(self, hint, num_bytes, flags, min_alignment);
	result    = baseaddr;

	if likely(num_bytes > 0) {
		struct mbnode *fmnode;

		/* Construct the memory-reservation node. */
		fmnode = mbuilder_create_res_file_node(baseaddr, num_bytes);

		/* Insert the node into the mem-builder.
		 * Note that we don't add the part to the files- or uparts lists,
		 * but only to the mappings tree, since the node doesn't contain
		 * a mem-file or mem-part. */
		mbnode_tree_insert(&self->mb_mappings, fmnode); /* Inherit */
	}
	return result;
}


DECL_END

#endif /* !GUARD_KERNEL_SRC_MEMORY_MBUILDER_C */
