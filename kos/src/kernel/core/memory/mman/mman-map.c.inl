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
#ifdef __INTELLISENSE__
#include "mman-map.c"
#define DEFINE_mman_map
//#define DEFINE_mman_map_subrange
//#define      DEFINE_mman_map_res
#endif /* __INTELLISENSE__ */

#include <kernel/fs/dirent.h>
#include <kernel/fs/path.h>
#include <kernel/malloc.h>
#include <kernel/mman.h>
#include <kernel/mman/flags.h>
#include <kernel/mman/map.h>
#include <kernel/mman/mfile-map.h>
#include <kernel/mman/mfile.h>
#include <kernel/mman/mnode.h>
#include <kernel/mman/module.h>
#include <kernel/mman/mpart-blkst.h>
#include <kernel/mman/mpart.h>
#include <kernel/mman/sync.h>
#include <kernel/mman/unmapped.h>
#include <kernel/paging.h>
#include <misc/unlockinfo.h>
#include <sched/task.h>

#include <hybrid/align.h>
#include <hybrid/atomic.h>
#include <hybrid/overflow.h>

#include <kos/except.h>
#include <kos/except/reason/inval.h>

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include <libc/string.h>

DECL_BEGIN

#ifdef DEFINE_mman_map_subrange

/* Create an anonymous ram memory node. */
PRIVATE ATTR_RETNONNULL WUNUSED struct mnode *FCALL
mnode_create_anon_ram(PAGEDIR_PAGEALIGNED size_t num_bytes,
                      unsigned int prot, unsigned int flags) {
	struct mnode *node;
	struct mpart *part;
	assert(IS_ALIGNED(num_bytes, PAGESIZE));
	node = (struct mnode *)kmalloc(sizeof(struct mnode), GFP_LOCKED | GFP_PREFLT);
	TRY {
		part = (struct mpart *)kmalloc(sizeof(struct mpart), GFP_LOCKED | GFP_PREFLT);
		TRY {
			/* Initialize everything. */
			part->mp_refcnt = 1; /* +1: `node' */
			part->mp_xflags = MPART_XF_NORMAL;
#if MAP_LOCKED == MPART_F_MLOCK
			part->mp_flags = MPART_F_NORMAL | (flags & MAP_LOCKED);
#else /* MAP_LOCKED == MPART_F_MLOCK */
			part->mp_flags = MPART_F_NORMAL;
			if (flags & MAP_LOCKED)
				part->mp_flags |= MPART_F_MLOCK;
#endif /* MAP_LOCKED != MPART_F_MLOCK */

			if ((flags & MAP_POPULATE) && (prot & PROT_WRITE)) {
				/* Pre-initialize all blocks as CHNG, so-as to give the caller
				 * write-permissions from the get-go. */
				part->mp_blkst_ptr = NULL;
			} else if (num_bytes <= (MPART_BLKST_BLOCKS_PER_WORD * PAGESIZE)) {
				part->mp_flags |= MPART_F_BLKST_INL;
				part->mp_blkst_inl = MPART_BLOCK_REPEAT(MPART_BLOCK_ST_NDEF);
			} else {
				mpart_blkst_word_t *bitset;
				size_t num_words;
				num_words = CEILDIV(num_bytes >> PAGESHIFT, MPART_BLKST_BLOCKS_PER_WORD);
				assert(num_words >= 2);
				bitset = (mpart_blkst_word_t *)kmalloc(num_words * sizeof(mpart_blkst_word_t),
#if MPART_BLOCK_ST_NDEF == 0
				                                       GFP_CALLOC |
#endif /* MPART_BLOCK_ST_NDEF == 0 */
				                                       GFP_LOCKED | GFP_PREFLT);
				part->mp_blkst_ptr = bitset;
			}
			part->mp_state = MPART_ST_VOID;
			part->mp_file  = &mfile_zero; /* incref'd later! */
			LIST_INIT(&part->mp_copy);
			LIST_INIT(&part->mp_share);
			SLIST_INIT(&part->mp_lockops);
			LIST_ENTRY_UNBOUND_INIT(&part->mp_allparts);
			DBG_memset(&part->mp_changed, 0xcc, sizeof(part->mp_changed));
			part->mp_minaddr = (pos_t)0;
			part->mp_maxaddr = (pos_t)num_bytes - 1;
			_mpart_init_asanon(part);
			part->mp_meta = NULL;
			if (flags & MAP_POPULATE) {
				/* Pre-populate + pre-initialize RAM-data for this part. */
				TRY {
					mpart_ll_allocmem(part, num_bytes >> PAGESHIFT);
				} EXCEPT {
					if (!(part->mp_flags & MPART_F_BLKST_INL))
						kfree(part->mp_blkst_ptr);
					RETHROW();
				}
			}

			node->mn_flags = mnodeflags_from_prot(prot) |
			                 mnodeflags_from_mapflags(flags);
			node->mn_minaddr = (byte_t *)0;
			node->mn_maxaddr = (byte_t *)num_bytes - 1;
			node->mn_part    = part; /* Inherit reference */
			node->mn_fspath  = NULL;
			node->mn_fsname  = NULL;
			node->mn_module  = NULL;
			node->mn_partoff = 0;
			node->mn_link.le_next  = NULL;
			node->mn_link.le_prev  = &mpart_getnodlst_from_prot(part, prot)->lh_first;
			*node->mn_link.le_prev = node;
		} EXCEPT {
			kfree(part);
			RETHROW();
		}
	} EXCEPT {
		kfree(node);
		RETHROW();
	}
	incref(&mfile_zero); /* For `part->mp_file' */
	return node;
}

PRIVATE NOBLOCK void
NOTHROW(FCALL mnode_destroy_anon_ram)(struct mnode *__restrict self) {
	decref_likely(self->mn_part);
	kfree(self);
}
#endif /* DEFINE_mman_map_subrange */


#ifdef DEFINE_mman_map
/* Map a given file into the specified mman.
 * @param: hint:          s.a. `mman_findunmapped'
 * @param: prot:          Set of `PROT_EXEC | PROT_WRITE | PROT_READ | PROT_SHARED | PROT_FORCEWRITE' (Other bits are silently ignored)
 * @param: flags:         Set  of  `MAP_LOCKED | MAP_POPULATE | MAP_NONBLOCK | MAP_PREPARED'   (Other  bits   are
 *                        silently ignored)  Additionally,  the following  flags  may  be set  to  customize  how
 *                        a  suitable   address  is   located  (s.a.   `mman_findunmapped()'  for   more   info):
 *                        `MAP_FIXED | MAP_32BIT | MAP_GROWSDOWN | MAP_GROWSUP | MAP_STACK | MAP_FIXED_NOREPLACE'
 * @param: file:          The file that is being mapped.
 * @param: file_fspath:   Optional mapping path (only used for memory->disk mapping listings)
 * @param: file_fsname:   Optional mapping name (only used for memory->disk mapping listings)
 * @param: file_pos:      Offset into the file being mapped, of where the mapping should start.
 *                        If this value isn't page-aligned,  then its sub-page offset is  added
 *                        to  the   return  value   eventually  returned   by  this   function.
 *                        But  that that when  `MAP_FIXED' flag is also  set, then the sub-page
 *                        offset of `hint' will be silently ignored, meaning that in this  case
 *                        the return value may differ from `hint'!
 * @param: min_alignment:        s.a. `mman_findunmapped'
 * @param: min_alignment_offset: s.a. `mman_findunmapped'
 * @return: * : The effective mapping  base at which `file->DATA.BYTES[file_pos]' can be found. */
PUBLIC BLOCKING_IF(flags & MAP_POPULATE) NONNULL((1, 6)) void *KCALL
mman_map(struct mman *__restrict self,
         UNCHECKED void *hint, size_t num_bytes,
         unsigned int prot, unsigned int flags,
         struct mfile *__restrict file,
         struct path *file_fspath,
         struct fdirent *file_fsname,
         pos_t file_pos, size_t min_alignment,
         ptrdiff_t min_alignment_offset)
		THROWS(E_WOULDBLOCK, E_BADALLOC,
		       E_BADALLOC_INSUFFICIENT_VIRTUAL_MEMORY,
		       E_BADALLOC_ADDRESS_ALREADY_EXISTS)
#define HAVE_FILE
#elif defined(DEFINE_mman_map_subrange)
/* Same as `mman_map()', but only allow pages entirely contained  within
 * the file-relative address range `file_map_minaddr...file_map_maxaddr'
 * to be mapped. Attempting to map file contents beyond this range  will
 * instead result in `&mfile_zero' getting mapped instead.
 * This function is mainly used to  restrict access to raw physical  memory
 * when user-space is allowed to directly mmap() device ram, but the driver
 * want's to prevent user-space from mapping more than the physical address
 * ranges actually associated with a device. */
PUBLIC BLOCKING_IF(flags & MAP_POPULATE) NONNULL((1, 6)) void *KCALL
mman_map_subrange(struct mman *__restrict self,
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
		THROWS(E_BADALLOC, E_WOULDBLOCK,
		       E_BADALLOC_INSUFFICIENT_VIRTUAL_MEMORY,
		       E_BADALLOC_ADDRESS_ALREADY_EXISTS)
#define HAVE_FILE
#elif defined(DEFINE_mman_map_res)
/* Same  as  `mman_map()',  but  instead  of  actually  mapping  something,  leave the
 * address range as empty (but possibly prepared), making it a reserved address range.
 * @param: flags: Set of `MAP_PREPARED' (Other bits are silently ignored)
 *                Additionally,  the  usual  bits  relating  to  `mman_getunmapped_nx()'  are   accepted:
 *                `MAP_FIXED | MAP_32BIT | MAP_GROWSDOWN | MAP_GROWSUP | MAP_STACK | MAP_FIXED_NOREPLACE' */
PUBLIC NONNULL((1)) void *KCALL
mman_map_res(struct mman *__restrict self,
             UNCHECKED void *hint, size_t num_bytes,
             unsigned int flags, size_t min_alignment,
             ptrdiff_t min_alignment_offset)
		THROWS(E_WOULDBLOCK, E_BADALLOC,
		       E_BADALLOC_INSUFFICIENT_VIRTUAL_MEMORY,
		       E_BADALLOC_ADDRESS_ALREADY_EXISTS)
#else /* ... */
#error "Unsupported configuration"
#endif /* !... */
{
#ifdef DEFINE_mman_map_subrange
	struct mnode_slist ext_nodes;
	size_t file_size;        /* Total # of bytes to map from `file' */
	size_t file_base_offset; /* # of bytes offset from `result' where `file_pos' begins. */
#else /* DEFINE_mman_map_subrange */
#define file_size        num_bytes
#define file_base_offset 0
#endif /* !DEFINE_mman_map_subrange */
	void *result;
	struct mnode_slist old_mappings;
#ifdef DEFINE_mman_map_res
	struct mnode *res_node;
#endif /* DEFINE_mman_map_res */
#ifdef HAVE_FILE
	uintptr_t mnode_flags;
	struct mfile_map_with_unlockinfo map;
	uintptr_t addend;
#endif /* HAVE_FILE */

	/* We don't allow zero-sized file mappings! */
	if unlikely(num_bytes == 0) {
#ifdef HAVE_FILE
err_bad_length:
#endif /* HAVE_FILE */
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_MMAP_LENGTH,
		      num_bytes);
	}

#ifdef HAVE_FILE
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
#endif /* HAVE_FILE */

	/* Align the required map size by whole pages. */
	num_bytes = CEIL_ALIGN(num_bytes, PAGESIZE);

	/* Calculate the flags for the mem-nodes we're intending on creating. */
#ifdef HAVE_FILE
	mnode_flags = mnodeflags_from_prot(prot) |
	              mnodeflags_from_mapflags(flags);
#endif /* HAVE_FILE */


#ifdef DEFINE_mman_map_subrange
	/* Make sure that the given file-bounds are properly aligned. */
	if unlikely(!IS_ALIGNED(file_map_minaddr, PAGESIZE))
		file_map_minaddr = CEIL_ALIGN(file_map_minaddr, PAGESIZE);
	if unlikely(!IS_ALIGNED(file_map_maxaddr + 1, PAGESIZE))
		file_map_maxaddr = FLOOR_ALIGN(file_map_maxaddr + 1, PAGESIZE) - 1;
	SLIST_INIT(&ext_nodes);
	TRY
#endif /* DEFINE_mman_map_subrange */
	{
#ifdef DEFINE_mman_map_subrange
		/* Create anon-ram nodes as replacements for all file
		 * regions  which  the caller  isn't allowed  to map. */
		file_size        = num_bytes;
		file_base_offset = 0;
		if (file_pos < file_map_minaddr) {
			struct mnode *node;
			size_t gap;
			if (OVERFLOW_USUB(file_map_minaddr, file_pos, &gap))
				gap = (size_t)-1;
			if (gap > file_size)
				gap = file_size;
			node = mnode_create_anon_ram(gap, prot, flags);
			SLIST_INSERT(&ext_nodes, node, _mn_alloc);
			file_base_offset += gap;
			file_size -= gap;
			file_pos = file_map_minaddr;
		}

		/* Check the upper bound. */
		if (file_size > 0) {
			size_t max_file_size;
			if (file_pos >= file_map_maxaddr) {
				max_file_size = 0;
			} else {
				if (OVERFLOW_USUB(file_map_maxaddr, file_pos, &max_file_size) ||
				    OVERFLOW_UADD(max_file_size, 1, &max_file_size))
					max_file_size = SIZE_MAX;
			}

			/* Check if the requested size exceeds the allowed size. */
			if (file_size > max_file_size) {
				struct mnode *node;
				size_t gap, postfile_offset;
				gap       = file_size - max_file_size;
				file_size = max_file_size;
				node      = mnode_create_anon_ram(gap, prot, flags);

				/* Include the relative offset from the to-be returned base-address
				 * to after where the actual file mapping will end, so-as to  place
				 * the post-node properly. */
				postfile_offset = file_base_offset + file_size;
				node->mn_minaddr += postfile_offset;
				node->mn_maxaddr += postfile_offset;
				SLIST_INSERT(&ext_nodes, node, _mn_alloc);
			}
		}

		/* Check for special case: _nothing_ from the given file may be mapped. */
		if unlikely(file_size <= 0) {
			SLIST_INIT(&map.mmwu_map.mfm_nodes);
			SLIST_INIT(&map.mmwu_map.mfm_flist);
			mpart_setcore_data_init(&map.mmwu_map.mfm_scdat);
			mpart_unsharecow_data_init(&map.mmwu_map.mfm_ucdat);
			goto do_insert_without_file;
#define NEED_do_insert_mappings
		}
#endif /* DEFINE_mman_map_subrange */

		/* Lock & load required data parts. */
#ifdef HAVE_FILE
		mfile_map_init_and_acquire(&map.mmwu_map, file, file_pos,
		                           file_size, prot, flags);
#endif /* HAVE_FILE */

#ifdef NEED_do_insert_mappings
#undef NEED_do_insert_mappings
do_insert_without_file:
#endif /* NEED_do_insert_mappings */

#ifdef DEFINE_mman_map_res
		/* Create+initialize the reserved memory node that's supposed to get mapped. */
		res_node = (struct mnode *)kmalloc(sizeof(struct mnode), GFP_LOCKED | GFP_PREFLT);
		res_node->mn_flags  = mnodeflags_from_mapflags(flags);
		res_node->mn_part   = NULL; /* Reserved node */
		res_node->mn_fspath = NULL;
		res_node->mn_fsname = NULL;
		res_node->mn_module = NULL;
		res_node->mn_mman   = self;
		DBG_memset(&res_node->mn_partoff, 0xcc, sizeof(res_node->mn_partoff));   /* Unused */
		DBG_memset(&res_node->mn_link, 0xcc, sizeof(res_node->mn_link));         /* Unused */
		DBG_memset(&res_node->mn_writable, 0xcc, sizeof(res_node->mn_writable)); /* Unused */
#endif /* DEFINE_mman_map_res */

		/* Acquire a lock to the target mman. */
		TRY {
#ifdef HAVE_FILE
			for (;;) {
				if (mman_lock_tryacquire(self))
					break;
				mfile_map_release(&map.mmwu_map);
				mman_lock_waitfor(self);
again_lock_mfile_map:
				mfile_map_acquire(&map.mmwu_map);
			}
			map.ui_unlock = &mfile_map_with_unlockinfo_unlock;
#else /* HAVE_FILE */
again_lock_mfile_map:
			mman_lock_acquire(self);
#endif /* !HAVE_FILE */

			/* Figure out where the mapping should go.
			 * NOTE: This call also deals with  the case where a  pre-existing
			 *       mapping partially overlaps with the target address range.
			 *       If this happens, this call  makes sure that border  nodes
			 *       are split such that we're  able to overwrite whole  nodes
			 *       below. */
			result = mman_getunmapped_or_unlock(self, hint, num_bytes,
			                                    flags, min_alignment,
			                                    min_alignment_offset,
#ifdef HAVE_FILE
			                                    &map
#else /* HAVE_FILE */
			                                    NULL
#endif /* !HAVE_FILE */
			                                    );
			if (result == MAP_FAILED)
				goto again_lock_mfile_map; /* Locks were released -> Try again */

			/* Make sure that the target address range is prepared within the page directory. */
#ifdef DEFINE_mman_map_res
			if (flags & MAP_PREPARED)
#endif /* DEFINE_mman_map_res */
			{
				if (!pagedir_prepare_p(self->mm_pagedir_p, result, num_bytes)) {
					/* Failed to prepare the backing page directory... :( */
#ifdef HAVE_FILE
					mfile_map_release(&map.mmwu_map);
#endif /* HAVE_FILE */
					mman_lock_release(self);
					THROW(E_BADALLOC_INSUFFICIENT_PHYSICAL_MEMORY, PAGESIZE);
				}
			}
		} EXCEPT {
#ifdef HAVE_FILE
			mfile_map_fini(&map.mmwu_map);
#endif /* HAVE_FILE */
#ifdef DEFINE_mman_map_res
			kfree(res_node);
#endif /* DEFINE_mman_map_res */
			RETHROW();
		}
		/* === Point of no return === */

		/* Get rid of existing mappings. */
		SLIST_INIT(&old_mappings);
		for (;;) {
			struct mnode *removeme;
			removeme = mman_mappings_rremove(self,
			                                 (byte_t *)result,
			                                 (byte_t *)result + num_bytes - 1);
			if likely(removeme == NULL)
				break;
			assert(removeme->mn_mman == self);
			if (LIST_ISBOUND(removeme, mn_writable))
				LIST_REMOVE(removeme, mn_writable);
			/* Keep track of how many nodes are mapping some given module. */
			if (removeme->mn_module)
				module_dec_nodecount(removeme->mn_module);
			DBG_memset(&removeme->mn_writable, 0xcc, sizeof(removeme->mn_writable));
			DBG_memset(&removeme->mn_module, 0xcc, sizeof(removeme->mn_module));
			ATOMIC_OR(removeme->mn_flags, MNODE_F_UNMAPPED);
			SLIST_INSERT(&old_mappings, removeme, _mn_alloc);
		}

		/* Do the actual work of injecting the new mem-nodes into the mman. */
#ifdef HAVE_FILE
		while (!SLIST_EMPTY(&map.mmwu_map.mfm_nodes)) {
			struct mnode_list *list;
			struct mnode *node;
			struct mpart *part;
			pagedir_prot_t map_prot;
			node = SLIST_FIRST(&map.mmwu_map.mfm_nodes);
			SLIST_REMOVE_HEAD(&map.mmwu_map.mfm_nodes, _mn_alloc);
			part           = node->mn_part;
			node->mn_flags = mnode_flags;
			node->mn_mman  = self;
			/* Insert the node into the share- or copy-list of the associated part. */
			list = mpart_getnodlst_from_mnodeflags(part, mnode_flags);
			LIST_INSERT_HEAD(list, node, mn_link);
			node->mn_fspath = xincref(file_fspath);
			node->mn_fsname = xincref(file_fsname);
			node->mn_module = NULL;
			node->mn_minaddr += file_base_offset + (uintptr_t)result;
			node->mn_maxaddr += file_base_offset + (uintptr_t)result;

			/* Set the MLOCK  flag for  the backing  mem-part when  MAP_LOCKED is  given.
			 * Note that in this case, `node->mn_flags' already contains `MNODE_F_MLOCK'! */
			if ((mnode_flags & MAP_LOCKED) && !(part->mp_flags & MPART_F_MLOCK_FROZEN))
				ATOMIC_OR(part->mp_flags, MPART_F_MLOCK);

			/* Map the backing part (as far as that is  possible)
			 * Note that  unless `MAP_POPULATE'  was given,  this
			 * wouldn't  actually  need  to be  done  right here.
			 * However,  by unconditionally doing it here, we can
			 * speed up the initial memory access whenever memory
			 * had already been  loaded in some  other way,  too! */
			map_prot = mpart_mmap_node_p(part, self->mm_pagedir_p,
			                             mnode_getaddr(node),
			                             mnode_getsize(node),
			                             node->mn_partoff,
			                             node);

			/* If the node was mapped with write-permissions enabled,
			 * then add it to the  list of writable nodes within  our
			 * memory manager. */
			LIST_ENTRY_UNBOUND_INIT(&node->mn_writable);
			if (map_prot & PAGEDIR_PROT_WRITE)
				LIST_INSERT_HEAD(&self->mm_writable, node, mn_writable);

			mman_mappings_insert(self, node);
			node = mnode_merge_with_partlock(node);
			mpart_assert_integrity(node->mn_part);
			mpart_lock_release(node->mn_part);
		}
#endif /* HAVE_FILE */

#ifdef DEFINE_mman_map_res
		res_node->mn_minaddr = (byte_t *)result;
		res_node->mn_maxaddr = (byte_t *)result + num_bytes - 1;
		LIST_ENTRY_UNBOUND_INIT(&res_node->mn_writable);
		mman_mappings_insert(self, res_node);
		mnode_merge(res_node);
#endif /* DEFINE_mman_map_res */
	}
#ifdef DEFINE_mman_map_subrange
	EXCEPT {
		while (!SLIST_EMPTY(&ext_nodes)) {
			struct mnode *node;
			node = SLIST_FIRST(&ext_nodes);
			SLIST_REMOVE_HEAD(&ext_nodes, _mn_alloc);
			mnode_destroy_anon_ram(node);
		}
		RETHROW();
	}
	while (!SLIST_EMPTY(&ext_nodes)) {
		pagedir_prot_t map_prot;
		struct mnode *node;
		struct mpart *part;
		node = SLIST_FIRST(&ext_nodes);
		SLIST_REMOVE_HEAD(&ext_nodes, _mn_alloc);
		part = node->mn_part;
		node->mn_mman = self;
		node->mn_minaddr += (uintptr_t)result;
		node->mn_maxaddr += (uintptr_t)result;
		map_prot = mpart_mmap_p(part, self->mm_pagedir_p,
		                        mnode_getaddr(node),
		                        mnode_getsize(node),
		                        node->mn_partoff,
		                        mnode_getperm_force(node));
		LIST_ENTRY_UNBOUND_INIT(&node->mn_writable);
		if (map_prot & PAGEDIR_PROT_WRITE)
			LIST_INSERT_HEAD(&self->mm_writable, node, mn_writable);
		mman_mappings_insert(self, node);
		/* Add the part to the list of all parts. Note that this is
		 * when  the part becomes  externally visible, meaning that
		 * up until this point we don't need (or use) any locks  on
		 * the part, esp. since we were the ones to create it! */
		mpart_all_list_insert(part);
		mnode_merge(node);
	}
#endif /* DEFINE_mman_map_subrange */

#ifdef DEFINE_mman_map_res
	/* Since it essentially got replaced with nothing, unmap any pre-existing mappings. */
	if (!SLIST_EMPTY(&old_mappings))
		pagedir_unmap_p(self->mm_pagedir_p, result, num_bytes);
#endif /* DEFINE_mman_map_res */

#ifndef DEFINE_mman_map_res
	/* If we're not supposed to keep the mappings prepared, then
	 * unprepare them now. */
	if (!(flags & MAP_PREPARED))
		pagedir_unprepare_p(self->mm_pagedir_p, result, num_bytes);
#endif /* !DEFINE_mman_map_res */

	/* If some other mapping was there before, then we must invalidate
	 * the page directory  cache so-as to  prevent any stale  entries.
	 * This has to happen before we  unlock the mman, and destroy  the
	 * old mappings, though!
	 * NOTE: We don't do  this unconditionally though,  because this  isn't
	 *       one of the fastest operations since this one has to go through
	 *       all of the hoops of broadcasting an IPI to everyone else... */
	if (!SLIST_EMPTY(&old_mappings))
		mman_sync_p(self, result, num_bytes);

	mman_lock_release(self);
#ifdef HAVE_FILE
	mfile_map_fini(&map.mmwu_map);
#endif /* HAVE_FILE */
	while (!SLIST_EMPTY(&old_mappings)) {
		struct mnode *oldnode;
		oldnode = SLIST_FIRST(&old_mappings);
		SLIST_REMOVE_HEAD(&old_mappings, _mn_alloc);
		assert(oldnode->mn_flags & MNODE_F_UNMAPPED);
		mnode_destroy(oldnode);
	}
#ifdef HAVE_FILE
	return (byte_t *)result + addend;
#else /* HAVE_FILE */
	return (byte_t *)result;
#endif /* !HAVE_FILE */
#undef file_size
#undef file_base_offset
}

#undef HAVE_FILE

DECL_END

#undef DEFINE_mman_map
#undef DEFINE_mman_map_subrange
#undef DEFINE_mman_map_res
