/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifdef __INTELLISENSE__
#include "heap.c"
#define HEAP_NX 1
#endif /* __INTELLISENSE__ */

#include <kernel/driver.h>
#include <kernel/rand.h>

#include "corebase.h"


#ifdef HEAP_NX
#define IFELSE_NX(if_nx,if_x)    if_nx
#define FUNC(x)                  x##_nx
#define NOTHROW_NX               NOTHROW
#else /* HEAP_NX */
#define IFELSE_NX(if_nx,if_x)    if_x
#define FUNC(x)                  x
#define NOTHROW_NX(x)            x
#endif /* HEAP_NX */


DECL_BEGIN

#define CORE_PAGE_MALLOC_ERROR  (VM_VPAGE_MAX + 1)
#define CORE_PAGE_MALLOC_AUTO   (VM_VPAGE_MAX + 1)
/* @param: mapping_target: The target page number where memory should be mapped.
 *                         When `CORE_PAGE_MALLOC_AUTO', automatically search
 *                         for a suitable location, otherwise _always_ return
 *                        `CORE_PAGE_MALLOC_AUTO' (regardless of `HEAP_NX'), if
 *                         another kernel VM mapping already exists at that location.
 *                   NOTE: When this is used to specify a fixed target, the caller
 *                         should do an additional check for pre-existing nodes within
 *                         VPAGE range `mapping_target ... mapping_target + num_pages - 1',
 *                         as this function will check for an existing mapping within
 *                         that range very late, and in a way that is not optimized
 *                         for this.
 * @param: num_pages:      The number of pages to allocate.
 * @param: alignment_in_pages: The minimum alignment (in pages) required from automatic
 *                             mapping_target detection. */
PRIVATE VIRT vm_vpage_t
NOTHROW_NX(KCALL FUNC(core_page_alloc))(struct heap *__restrict self,
                                        vm_vpage_t mapping_target, size_t num_pages,
                                        size_t alignment_in_pages, gfp_t flags) {
#define CORE_ALLOC_FLAGS                                                        \
	(GFP_LOCKED |                                                               \
	 GFP_PREFLT |                                                               \
	 GFP_VCBASE | /* Instruct the heap to only consider allocating from VCbase, \
	               * thus preventing an infinite loop. */                       \
	 GFP_NOOVER   /* Don't overallocate to prevent infinite recursion!          \
	               * -> This flag guaranties that upon recursion, at most 1     \
	               *    page will get allocated, in which case the              \
	               *   `block0_size >= num_pages' check above will be           \
	               *   `1 >= 1', meaning we'll never get here! */               \
	)
	TRACE("core_page_alloc(%p,%p,%Iu,%Iu,%#x)\n", self, mapping_target, num_pages, alignment_in_pages, flags);
	struct vm_corepair_ptr corepair;
	HEAP_ASSERT(num_pages != 0);
	/* Throw a would-block error if we're not allowed to map new memory. */
	if (flags & GFP_NOMMAP)
		IFELSE_NX(return CORE_PAGE_MALLOC_ERROR, THROW(E_WOULDBLOCK_PREEMPTED));
	heap_validate_all_pedantic();
	/* Only allocate using corebase when `GFP_SHARED|GFP_LOCKED'
	 * Otherwise, we can allocate the region and node using
	 * that same set of flags in a call to `kmalloc()'. */
	if (self == &kernel_locked_heap || (flags & GFP_VCBASE)) {
		/* Allocate a new corepair to describe this new mapping. */
#ifdef HEAP_NX
		corepair = vm_corepair_alloc(flags, true);
		if (!corepair.cp_node)
			goto err;
#else /* HEAP_NX */
		corepair = vm_corepair_alloc(flags, false);
#endif /* !HEAP_NX */
	} else {
#ifdef HEAP_NX
		corepair.cp_node = (VIRT struct vm_node *)kmalloc_nx(sizeof(struct vm_node),
		                                                     CORE_ALLOC_FLAGS | GFP_CALLOC |
		                                                     (flags & GFP_INHERIT));
		if unlikely(!corepair.cp_node)
			goto err;
		corepair.cp_part = (VIRT struct vm_datapart *)kmalloc_nx(sizeof(struct vm_datapart),
		                                                         CORE_ALLOC_FLAGS | GFP_CALLOC |
		                                                         (flags & GFP_INHERIT));
		if unlikely(!corepair.cp_part) {
			kffree(corepair.cp_node, GFP_CALLOC);
			goto err;
		}
#else /* HEAP_NX */
		corepair.cp_node = (VIRT struct vm_node *)kmalloc(sizeof(struct vm_node),
		                                                  CORE_ALLOC_FLAGS | GFP_CALLOC |
		                                                  (flags & GFP_INHERIT));
		TRY {
			corepair.cp_part = (VIRT struct vm_datapart *)kmalloc(sizeof(struct vm_datapart),
			                                                      CORE_ALLOC_FLAGS | GFP_CALLOC |
			                                                      (flags & GFP_INHERIT));
		} EXCEPT {
			kfree(corepair.cp_node);
			RETHROW();
		}
#endif /* !HEAP_NX */
	}
	/* Setup the corepair. */
	corepair.cp_part->dp_refcnt = 1; /* corepair.cp_node */
	corepair.cp_node->vn_prot   = VM_PROT_READ | VM_PROT_WRITE | VM_PROT_SHARED;
	corepair.cp_node->vn_vm     = &vm_kernel;
	corepair.cp_part->dp_block  = flags & GFP_CALLOC
	                             ? &vm_datablock_anonymous_zero
#ifdef CONFIG_DEBUG_HEAP
	                             : &vm_datablock_debugheap
#else /* CONFIG_DEBUG_HEAP */
	                             : &vm_datablock_anonymous
#endif /* !CONFIG_DEBUG_HEAP */
	                             ;
	incref(corepair.cp_part->dp_block);
	corepair.cp_node->vn_block = incref(corepair.cp_part->dp_block);
	corepair.cp_node->vn_flags |= VM_NODE_FLAG_PREPARED;
	corepair.cp_node->vn_part          = corepair.cp_part;
	corepair.cp_node->vn_link.ln_pself = &LLIST_HEAD(corepair.cp_part->dp_srefs);
	corepair.cp_part->dp_srefs         = corepair.cp_node;
	corepair.cp_part->dp_tree.a_vmax   = (vm_dpage_t)(num_pages - 1);
	{
		pageptr_t block0_addr;
		pagecnt_t block0_size;
		corepair.cp_part->dp_state = flags & GFP_LOCKED
		                             ? VM_DATAPART_STATE_LOCKED
		                             : VM_DATAPART_STATE_INCORE;
		/* Allocate / initialize the did-init bitset. */
		if (num_pages <= BITSOF(uintptr_t) / VM_DATAPART_PPP_BITS) {
			corepair.cp_part->dp_pprop = (flags & GFP_PREFLT) ? (uintptr_t)-1 : 0;
		} else if (flags & GFP_PREFLT) {
			/* When pre-faulting, we can simply assign a `NULL' */
			corepair.cp_part->dp_pprop_p = NULL;
			corepair.cp_part->dp_flags |= VM_DATAPART_FLAG_HEAPPPP;
		} else {
			/* Need the bitset to be dynamically allocated! */
			size_t bitset_size = (num_pages + ((BITSOF(uintptr_t) / VM_DATAPART_PPP_BITS) - 1)) & ~((BITSOF(uintptr_t) / VM_DATAPART_PPP_BITS) - 1);
#ifdef HEAP_NX
			corepair.cp_part->dp_pprop_p = (uintptr_t *)kmalloc_nx(bitset_size,
			                                                       CORE_ALLOC_FLAGS | GFP_CALLOC |
			                                                       (flags & GFP_INHERIT));
			if unlikely(!corepair.cp_part->dp_pprop_p)
				goto err_corepair_without_didinit;
#else /* HEAP_NX */
			TRY {
				corepair.cp_part->dp_pprop_p = (uintptr_t *)kmalloc(bitset_size,
				                                                    CORE_ALLOC_FLAGS | GFP_CALLOC |
				                                                    (flags & GFP_INHERIT));
			} EXCEPT {
				decref_nokill(corepair.cp_node->vn_block);
				decref_nokill(corepair.cp_part->dp_block);
				vm_node_free(corepair.cp_node);
				vm_datapart_free(corepair.cp_part);
				RETHROW();
			}
#endif /* !HEAP_NX */
			corepair.cp_part->dp_flags |= VM_DATAPART_FLAG_HEAPPPP;
		}
		block0_addr = page_malloc_part(1, num_pages, &block0_size);
		if unlikely(block0_addr == PAGEPTR_INVALID) {
			/* Allocation failed. */
#ifdef HEAP_NX
			goto err_corepair;
#else /* HEAP_NX */
			if (corepair.cp_part->dp_flags & VM_DATAPART_FLAG_HEAPPPP)
				kfree(corepair.cp_part->dp_pprop_p);
			decref_nokill(corepair.cp_node->vn_block);
			decref_nokill(corepair.cp_part->dp_block);
			vm_node_free(corepair.cp_node);
			vm_datapart_free(corepair.cp_part);
			THROW(E_BADALLOC_INSUFFICIENT_PHYSICAL_MEMORY, num_pages);
#endif /* !HEAP_NX */
		}
		HEAP_ASSERTF(block0_size >= 1, "num_pages = %Iu", num_pages);
		HEAP_ASSERT(block0_size <= num_pages);
		if likely(block0_size >= num_pages) {
			/* All requested memory could be served as part of a single block. */
			corepair.cp_part->dp_ramdata.rd_blockv          = &corepair.cp_part->dp_ramdata.rd_block0;
			corepair.cp_part->dp_ramdata.rd_block0.rb_size  = block0_size;
			corepair.cp_part->dp_ramdata.rd_block0.rb_start = block0_addr;
		} else {
			/* Must allocate a larger vector for all of the other pages. */
			struct vm_ramblock *blocks, *new_blocks;
			size_t blockc = 1;
#ifdef HEAP_NX
			blocks = (struct vm_ramblock *)kmalloc_nx(2 * sizeof(struct vm_ramblock),
			                                          CORE_ALLOC_FLAGS | (flags & GFP_INHERIT));
			if unlikely(!blocks) {
				page_ccfree(block0_addr, block0_size);
				goto err_corepair;
			}
			blocks[0].rb_start = block0_addr;
			blocks[0].rb_size  = block0_size;
			/* Allocate more blocks and populate the block-vector. */
			while (block0_size < num_pages) {
				pagecnt_t new_block_size;
				if (blockc >= (kmalloc_usable_size(blocks) / sizeof(struct vm_ramblock))) {
					new_blocks = (struct vm_ramblock *)krealloc_nx(blocks, (blockc * 2) * sizeof(struct vm_ramblock),
					                                               CORE_ALLOC_FLAGS | (flags & GFP_INHERIT));
					if unlikely(!new_blocks) {
						new_blocks = (struct vm_ramblock *)krealloc_nx(blocks, (blockc + 1) * sizeof(struct vm_ramblock),
						                                               CORE_ALLOC_FLAGS | (flags & GFP_INHERIT));
						if unlikely(!new_blocks) {
err_blocks:
							/* Free all blocks that had already been allocated. */
							while (blockc--) {
								page_ccfree(blocks[blockc].rb_start,
								            blocks[blockc].rb_size);
							}
							kfree(blocks);
							goto err_corepair;
						}
					}
					blocks = new_blocks;
				}
				/* Allocate the next part. */
				block0_addr = page_malloc_part(1,
				                               num_pages - block0_size,
				                               &new_block_size);
				if unlikely(block0_addr == PAGEPTR_INVALID)
					goto err_blocks;
#if 1
				/* Insert new blocks in the front, thus optimizing to better allocate
				 * memory in its proper order, following the assumption that page_malloc()
				 * will prefer allocating memory in top-down priority ordering. */
				memmove(&blocks[1], &blocks[0],
				        blockc * sizeof(struct vm_ramblock));
				blocks[0].rb_start = block0_addr;
				blocks[0].rb_size  = new_block_size;
#else
				blocks[blockc].rb_start = block0_addr;
				blocks[blockc].rb_size  = new_block_size;
#endif
				block0_size += new_block_size;
				HEAP_ASSERT(block0_size <= num_pages);
				++blockc;
			}
#else /* HEAP_NX */
			TRY {
				TRY {
					blocks = (struct vm_ramblock *)kmalloc(2 * sizeof(struct vm_ramblock),
					                                       CORE_ALLOC_FLAGS | (flags & GFP_INHERIT));
				} EXCEPT {
					page_ccfree(block0_addr, block0_size);
					RETHROW();
				}
				blocks[0].rb_start = block0_addr;
				blocks[0].rb_size = block0_size;
				/* Allocate more blocks and populate the block-vector. */
				while (block0_size < num_pages) {
					pagecnt_t new_block_size;
					if (blockc >= (kmalloc_usable_size(blocks) / sizeof(struct vm_ramblock))) {
						new_blocks = (struct vm_ramblock *)krealloc_nx(blocks, (blockc * 2) * sizeof(struct vm_ramblock),
						                                               CORE_ALLOC_FLAGS | (flags & GFP_INHERIT));
						if unlikely(!new_blocks) {
							TRY {
								new_blocks = (struct vm_ramblock *)krealloc(blocks, (blockc + 1) * sizeof(struct vm_ramblock),
								                                            CORE_ALLOC_FLAGS | (flags & GFP_INHERIT));
							} EXCEPT {
								/* Free all blocks that had already been allocated. */
								while (blockc--) {
									page_ccfree(blocks[blockc].rb_start,
									            blocks[blockc].rb_size);
								}
								kfree(blocks);
								RETHROW();
							}
						}
						blocks = new_blocks;
					}
					/* Allocate the next part. */
					block0_addr = page_malloc_part(1,
					                               num_pages - block0_size,
					                               &new_block_size);
					if unlikely(block0_addr == PAGEPTR_INVALID) {
						while (blockc--) {
							page_ccfree(blocks[blockc].rb_start,
							            blocks[blockc].rb_size);
						}
						kfree(blocks);
						THROW(E_BADALLOC_INSUFFICIENT_PHYSICAL_MEMORY, num_pages);
					}
					blocks[blockc].rb_start = block0_addr;
					blocks[blockc].rb_size = new_block_size;
					block0_size += new_block_size;
					HEAP_ASSERT(block0_size <= num_pages);
					++blockc;
				}
			} EXCEPT {
				if (corepair.cp_part->dp_flags & VM_DATAPART_FLAG_HEAPPPP)
					kfree(corepair.cp_part->dp_pprop_p);
				decref_nokill(corepair.cp_node->vn_block);
				decref_nokill(corepair.cp_part->dp_block);
				vm_node_free(corepair.cp_node);
				vm_datapart_free(corepair.cp_part);
				RETHROW();
			}
#endif /* !HEAP_NX */
			/* Release unused memory. */
			krealloc_in_place_nx(blocks, blockc * sizeof(struct vm_ramblock),
			                     CORE_ALLOC_FLAGS | (flags & GFP_INHERIT));
			/* All right! we've allocated all of the necessary blocks! */
			corepair.cp_part->dp_ramdata.rd_blockc = blockc;
			corepair.cp_part->dp_ramdata.rd_blockv = blocks;
		}
	}

#ifndef HEAP_NX
	TRY
#endif /* !HEAP_NX */
	{
		/* Acquire a lock to the kernel VM, so we can search for a
		 * location at which we can map the requested memory block at. */
again_lock_vm:
#ifdef HEAP_NX
		if unlikely(!vm_kernel_treelock_writef_nx(flags))
			goto err_corepair_content;
#else /* HEAP_NX */
		if unlikely(!vm_kernel_treelock_writef(flags))
			THROW(E_WOULDBLOCK_PREEMPTED);
#endif /* !HEAP_NX */
		if (mapping_target == CORE_PAGE_MALLOC_AUTO) {
			/* search for a suitable location. */
			vm_vpage_t mapping_hint;
			unsigned int mapping_mode;
			mapping_hint   = ATOMIC_READ(self->h_hintpage);
			mapping_mode   = ATOMIC_READ(self->h_hintmode);
			mapping_target = vm_getfree(&vm_kernel,
			                            mapping_hint,
			                            num_pages,
			                            alignment_in_pages,
			                            mapping_mode);
			if (mapping_target == VM_GETFREE_ERROR) {
				uintptr_t version;
				vm_kernel_treelock_endwrite();
#ifndef __OPTIMIZE_SIZE__
				if (system_clearcaches())
					goto again_lock_vm;
#endif /* !__OPTIMIZE_SIZE__ */
				version = 0;
again_tryhard_mapping_target:
				vm_kernel_treelock_read();
				mapping_target = vm_getfree(&vm_kernel,
				                            mapping_hint,
				                            num_pages,
				                            alignment_in_pages,
				                            mapping_mode);
				vm_kernel_treelock_endread();
				if (mapping_target != VM_GETFREE_ERROR)
					goto again_lock_vm;
				if (system_clearcaches_s(&version))
					goto again_tryhard_mapping_target;
				IFELSE_NX(goto err_corepair_content,
				          THROW(E_BADALLOC_INSUFFICIENT_VIRTUAL_MEMORY, (uintptr_t)num_pages));
			}
			/* Update the hint for the next allocation to be adjacent to this one. */
			ATOMIC_CMPXCH(self->h_hintpage, mapping_hint,
			              mapping_mode & VM_GETFREE_BELOW ? (mapping_target)
			                                              : (mapping_target + num_pages));
		} else {
			/* Check if there is already a mapping at the specified target address. */
			if (vm_isused(&vm_kernel, mapping_target, mapping_target + num_pages - 1)) {
				/* There is... (crap!) */
#ifdef HEAP_NX
				goto err_corepair_content;
#else /* HEAP_NX */
				if (corepair.cp_part->dp_state == VM_DATAPART_STATE_INCORE ||
				    corepair.cp_part->dp_state == VM_DATAPART_STATE_LOCKED) {
					struct vm_ramblock *blocks;
					size_t blockc, i;
					blocks = corepair.cp_part->dp_ramdata.rd_blockv;
					blockc = blocks == &corepair.cp_part->dp_ramdata.rd_block0
					         ? 1
					         : corepair.cp_part->dp_ramdata.rd_blockc;
					/* Free all pre-allocated pages. */
					for (i = 0; i < blockc; ++i)
						page_free(blocks[i].rb_start, blocks[i].rb_size);
					if (blocks != &corepair.cp_part->dp_ramdata.rd_block0)
						kfree(blocks);
				}
				if (corepair.cp_part->dp_flags & VM_DATAPART_FLAG_HEAPPPP)
					kfree(corepair.cp_part->dp_pprop_p);
				decref_nokill(corepair.cp_node->vn_block);
				decref_nokill(corepair.cp_part->dp_block);
				vm_node_free(corepair.cp_node);
				vm_datapart_free(corepair.cp_part);
				return CORE_PAGE_MALLOC_ERROR;
#endif /* !HEAP_NX */
			}
		}

		corepair.cp_node->vn_node.a_vmin = mapping_target;
		corepair.cp_node->vn_node.a_vmax = mapping_target + num_pages - 1;
		{
			/* Map the node to the kernel page directory & do initialization. */
			struct vm_ramblock *blocks;
			size_t blockc, i;
			vm_vpage_t mapping_offset = 0;
			blocks = corepair.cp_part->dp_ramdata.rd_blockv;
			blockc = blocks == &corepair.cp_part->dp_ramdata.rd_block0
			         ? 1
			         : corepair.cp_part->dp_ramdata.rd_blockc;
#ifdef CONFIG_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE
			/* Prepare to map all of the new blocks. */
			for (i = 0; i < blockc; ++i) {
				if unlikely(!pagedir_prepare_map(mapping_target + mapping_offset,
				                                 blocks[i].rb_size)) {
					/* Failed to map a part of the resulting data block. */
					while (i--) {
						mapping_offset -= blocks[i].rb_size;
						pagedir_unprepare_map(mapping_target + mapping_offset,
						                      blocks[i].rb_size);
					}
					IFELSE_NX(goto err_corepair_content,
					          THROW(E_BADALLOC_INSUFFICIENT_PHYSICAL_MEMORY, 1));
				}
			}
#endif /* CONFIG_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE */
			if (flags & GFP_PREFLT) {
				/* Map all pre-allocated pages. */
				for (i = 0; i < blockc; ++i) {
					pagedir_map(mapping_target + mapping_offset,
					            blocks[i].rb_size,
					            blocks[i].rb_start,
					            PAGEDIR_MAP_FWRITE | PAGEDIR_MAP_FREAD);
					if (flags & GFP_CALLOC) {
						/* Write zeros to all random-content pages. */
						pagecnt_t j;
						for (j = 0; j < blocks[i].rb_size; ++j) {
							vm_vpage_t vpage = mapping_target + mapping_offset + j;
							vm_ppage_t ppage = blocks[i].rb_start + j;
							if (!page_iszero(ppage)) {
								memset((void *)VM_PAGE2ADDR(vpage), 0, pagedir_pagesize());
#ifdef CONFIG_HAVE_PAGEDIR_CHANGED
								pagedir_unsetchanged(vpage);
#endif /* CONFIG_HAVE_PAGEDIR_CHANGED */
							}
						}
					}
#ifdef CONFIG_DEBUG_HEAP
					else {
						/* Fill memory using the fresh-memory pattern. */
						pagecnt_t j;
						for (j = 0; j < blocks[i].rb_size; ++j) {
							vm_vpage_t vpage = mapping_target + mapping_offset + j;
							mempatl((void *)VM_PAGE2ADDR(vpage),
							        DEBUGHEAP_FRESH_MEMORY,
							        pagedir_pagesize());
#ifdef CONFIG_HAVE_PAGEDIR_CHANGED
							pagedir_unsetchanged(vpage);
#endif /* CONFIG_HAVE_PAGEDIR_CHANGED */
						}
					}
#endif /* CONFIG_DEBUG_HEAP */
					mapping_offset += blocks[i].rb_size;
				}
				HEAP_ASSERT((size_t)mapping_offset == num_pages);
			} else if (flags & GFP_LOCKED) {
				/* Indicate that this node is being used with hinting. */
				corepair.cp_node->vn_flags |= VM_NODE_FLAG_HINTED;
				/* Set paging hints to allow for atomic initialization. */
				for (i = 0; i < blockc; ++i) {
					pagedir_maphint(mapping_target + mapping_offset,
					                blocks[i].rb_size,
					                corepair.cp_node);
				}
			}
		}
		/* Now insert the new node into the VM
		 * NOTE: No need to activate the node now:
		 *   - If we're supposed to pre-fault the pages, the above code
		 *     has already created the mapping in the page directory.
		 *   - If we're not supposed to pre-fault the pages, then the mapping
		 *     will automatically get created once the node gets accessed. */
		vm_node_insert(corepair.cp_node);
		vm_kernel_treelock_endwrite();
		heap_validate_all_pedantic();
		return mapping_target;
	}
#ifndef HEAP_NX
	EXCEPT
#endif /* !HEAP_NX */
	{
#ifdef HEAP_NX
err_corepair_content:
#endif /* HEAP_NX */
		if (VM_DATAPART_STATE_HASRAM(corepair.cp_part->dp_state)) {
			struct vm_ramblock *blocks;
			size_t blockc, i;
			blocks = corepair.cp_part->dp_ramdata.rd_blockv;
			blockc = blocks == &corepair.cp_part->dp_ramdata.rd_block0
			         ? 1
			         : corepair.cp_part->dp_ramdata.rd_blockc;
			/* Free all pre-allocated pages. */
			for (i = 0; i < blockc; ++i)
				page_free(blocks[i].rb_start, blocks[i].rb_size);
			if (blocks != &corepair.cp_part->dp_ramdata.rd_block0)
				kfree(blocks);
		}
#ifdef HEAP_NX
err_corepair:
#endif /* HEAP_NX */
		if (corepair.cp_part->dp_flags & VM_DATAPART_FLAG_HEAPPPP)
			kfree(corepair.cp_part->dp_pprop_p);
#ifdef HEAP_NX
err_corepair_without_didinit:
#endif /* HEAP_NX */
		decref_nokill(corepair.cp_node->vn_block);
		decref_nokill(corepair.cp_part->dp_block);
		vm_node_free(corepair.cp_node);
		vm_datapart_free(corepair.cp_part);
#ifdef HEAP_NX
err:
		return CORE_PAGE_MALLOC_ERROR;
#else /* HEAP_NX */
		RETHROW();
#endif /* !HEAP_NX */
	}
}


PRIVATE VIRT vm_vpage_t
NOTHROW_NX(KCALL FUNC(core_page_alloc_check_hint))(struct heap *__restrict self,
                                                   vm_vpage_t mapping_target, size_t num_pages,
                                                   size_t alignment_in_pages, gfp_t flags) {
	bool is_used;
	HEAP_ASSERT(mapping_target != CORE_PAGE_MALLOC_AUTO);
	/* Checking beforehand is much faster if the memory is already in use.
	 * This check isn't really required, however without it, we'll have to do
	 * a lot more cleanup when it was already known that the operation was going
	 * to fail from the get-go. */
#ifdef HEAP_NX
	if unlikely(!vm_kernel_treelock_writef_nx(flags)) /* TODO: A read-lock is sufficient for us! */
		return CORE_PAGE_MALLOC_ERROR;
#else /* HEAP_NX */
	if unlikely(!vm_kernel_treelock_writef(flags)) /* TODO: A read-lock is sufficient for us! */
		THROW(E_WOULDBLOCK_PREEMPTED);
#endif /* !HEAP_NX */
	/* Check if the given address range is already in use! */
	is_used = vm_isused(&vm_kernel,
	                    mapping_target,
	                    mapping_target + num_pages - 1);
	vm_kernel_treelock_endwrite(); /* TODO: A read-lock is sufficient for us! */
	if (is_used)
		return CORE_PAGE_MALLOC_ERROR;
	return FUNC(core_page_alloc)(self,
	                             mapping_target,
	                             num_pages,
	                             alignment_in_pages,
	                             flags);
}



PUBLIC struct heapptr
NOTHROW_NX(KCALL FUNC(heap_alloc_untraced))(struct heap *__restrict self,
                                            size_t num_bytes, gfp_t flags) {
	struct heapptr result;
	struct mfree **iter, **end;
	TRACE("heap_alloc_untraced(%p,%Iu,%#x)\n", self, num_bytes, flags);
	if unlikely(OVERFLOW_UADD(num_bytes, (size_t)(HEAP_ALIGNMENT - 1), &result.hp_siz))
		IFELSE_NX(goto err, THROW(E_BADALLOC_INSUFFICIENT_HEAP_MEMORY, num_bytes));
	result.hp_siz &= ~(HEAP_ALIGNMENT - 1);
	if unlikely(result.hp_siz < HEAP_MINSIZE)
		result.hp_siz = HEAP_MINSIZE;
	iter = &self->h_size[HEAP_BUCKET_OF(result.hp_siz)];
	end  = COMPILER_ENDOF(self->h_size);
	HEAP_ASSERTF(iter >= self->h_size &&
	             iter < COMPILER_ENDOF(self->h_size),
	             "HEAP_BUCKET_OF(%Iu) = %Iu/%Iu",
	             result.hp_siz, HEAP_BUCKET_OF(result.hp_siz),
	             COMPILER_LENOF(self->h_size));
search_heap:
	if (!FUNC(heap_acquirelock)(self, flags))
		IFELSE_NX(goto err, THROW(E_WOULDBLOCK_PREEMPTED));
	for (; iter != end; ++iter) {
#ifdef CONFIG_HEAP_TRACE_DANGLE
		size_t dangle_size;
#endif /* CONFIG_HEAP_TRACE_DANGLE */
		size_t unused_size;
		struct mfree *chain;
		gfp_t chain_flags;
		/* Search this bucket. */
		chain = *iter;
		while (chain &&
		       (HEAP_ASSERTF(IS_ALIGNED(MFREE_SIZE(chain), HEAP_ALIGNMENT),
		                     "MFREE_SIZE(chain) = 0x%Ix\n",
		                     MFREE_SIZE(chain)),
		        MFREE_SIZE(chain) < result.hp_siz))
			chain = LLIST_NEXT(chain, mf_lsize);
		if (!chain)
			continue;
		HEAP_ASSERTE(mfree_tree_remove(&self->h_addr, (uintptr_t)MFREE_BEGIN(chain)) == chain);
		LLIST_REMOVE(chain, mf_lsize);
#ifdef CONFIG_HEAP_TRACE_DANGLE
		/* Track the potentially unused data size as dangling data. */
		dangle_size = MFREE_SIZE(chain) - result.hp_siz;
		HEAP_ADD_DANGLE(self, dangle_size);
#endif /* CONFIG_HEAP_TRACE_DANGLE */
		sync_endwrite(&self->h_lock);
		HEAP_ASSERT(IS_ALIGNED(dangle_size, HEAP_ALIGNMENT));
		/* We've got the memory! */
		result.hp_ptr = (void *)chain;
		chain_flags   = chain->mf_flags;
#ifdef CONFIG_HEAP_TRACE_DANGLE
		unused_size = dangle_size;
#else /* CONFIG_HEAP_TRACE_DANGLE */
		unused_size = MFREE_SIZE(chain) - result.hp_siz;
#endif /* !CONFIG_HEAP_TRACE_DANGLE */
		if (unused_size < HEAP_MINSIZE) {
			/* Remainder is too small. - Allocate it as well. */
			result.hp_siz += unused_size;
		} else {
			void *unused_begin = (void *)((uintptr_t)chain + result.hp_siz);
			/* Free the unused portion. */
#ifdef CONFIG_HEAP_RANDOMIZE_OFFSETS
			/* Randomize allocated memory by shifting the
			 * resulting pointer somewhere up higher. */
			uintptr_t random_offset;
			random_offset = krand() % unused_size;
			random_offset &= ~(HEAP_ALIGNMENT - 1);
			if (random_offset >= HEAP_MINSIZE) {
				/* Set the new resulting pointer. */
				result.hp_ptr = (void *)((uintptr_t)chain + random_offset);
				/* Rather than allocating `chain...+=num_bytes', instead
				 * allocate `chain+random_offset...+=num_bytes' and free
				 * `chain...+=random_offset' and
				 * `chain+random_offset+num_bytes...+=unused_size-random_offset' */
				if (chain_flags & MFREE_FZERO)
					memset(chain, 0, SIZEOF_MFREE);
#ifdef CONFIG_DEBUG_HEAP
				else {
					mempatl(chain, DEBUGHEAP_NO_MANS_LAND, SIZEOF_MFREE);
				}
#endif /* CONFIG_DEBUG_HEAP */
				/* Free unused low memory. */
				heap_free_underallocation(self,
				                          chain,
				                          random_offset,
				                          (flags & ~(GFP_CALLOC)) | chain_flags);
				unused_size -= random_offset;
				if (unused_size < HEAP_MINSIZE) {
					result.hp_siz += unused_size;
				} else {
					unused_begin = (void *)((uintptr_t)result.hp_ptr + result.hp_siz);
					heap_free_overallocation(self,
					                         unused_begin,
					                         unused_size,
					                         (flags & ~(GFP_CALLOC)) | chain_flags);
				}
			} else
#endif /* CONFIG_HEAP_RANDOMIZE_OFFSETS */
			{
				HEAP_ASSERT(unused_size < MFREE_SIZE(chain));
				/* Free the unused overallocation. */
				heap_free_overallocation(self,
				                         unused_begin,
				                         unused_size,
				                         (flags & ~(GFP_CALLOC)) | chain_flags);
			}
		}
#ifdef CONFIG_HEAP_TRACE_DANGLE
		/* Now that it's been returned, the data is no longer dangling. */
		HEAP_SUB_DANGLE(self, dangle_size);
#endif /* CONFIG_HEAP_TRACE_DANGLE */
		/* Initialize the result memory. */
		if (flags & GFP_CALLOC) {
			if (chain_flags & MFREE_FZERO)
				memset(result.hp_ptr, 0, SIZEOF_MFREE);
			else {
				memset(result.hp_ptr, 0, result.hp_siz);
			}
		}
#ifdef CONFIG_DEBUG_HEAP
		else {
			reset_heap_data((byte_t *)result.hp_ptr,
			                DEBUGHEAP_FRESH_MEMORY,
			                result.hp_siz);
		}
#endif /* CONFIG_DEBUG_HEAP */
		HEAP_ASSERT(IS_ALIGNED((uintptr_t)result.hp_ptr, HEAP_ALIGNMENT));
		HEAP_ASSERT(IS_ALIGNED((uintptr_t)result.hp_siz, HEAP_ALIGNMENT));
		HEAP_ASSERT(result.hp_siz >= HEAP_MINSIZE);
		heap_validate_all_pedantic();
		return result;
	}
#ifdef CONFIG_HEAP_TRACE_DANGLE
	/* Check for dangling data and don't allocate new memory if enough exists. */
	if (ATOMIC_READ(self->h_dangle) >= result.hp_siz) {
		sync_endwrite(&self->h_lock);
		/* Let some other thread about to release dangling
		 * data do so, then search the heap again. */
		if (flags & GFP_ATOMIC)
			IFELSE_NX(goto err, THROW(E_WOULDBLOCK_PREEMPTED));
		__hybrid_yield();
		goto search_heap;
	}
#endif /* CONFIG_HEAP_TRACE_DANGLE */
	/* NOTE: Don't track page overflow from below as dangling data
	 *       here, so-as not to confuse allocators that are holding
	 *       a lock to `vm_kernel.v_treelock'.
	 *       Otherwise, we might end up with a soft-lock:
	 *        THREAD #1: (holding lock to `vm_kernel.v_treelock')
	 *                   kmalloc(1234);
	 *                   -> Sees dangling data from new allocation
	 *                      currently being made by THREAD #2
	 *                   -> Doesn't allocate new pages, but tries
	 *                      to yield to THREAD #2 and jumps back
	 *        THREAD #2: In `core_page_alloc()'; tracking dangling
	 *                   data that THREAD #1 is waiting for.
	 *                  `core_page_alloc()' doesn't return because
	 *                   THREAD #1 is locking `vm_kernel'
	 *                   THREAD #1 can't release that lock because
	 *                   it is waiting for THREAD #2.
	 *        -> Soft-lock!
	 * XXX: The above scenario can no longer happen since `vm_kernel.v_treelock'
	 *      has now been implemented as an atomic lock:
	 *       - A thread that is holding an atomic lock isn't allowed to
	 *         perform a call to `task_yield()', meaning that THREAD#1
	 *         could (and does) only allocate with GFP_ATOMIC while
	 *         holding a lock to `vm_kernel.v_treelock', in which case
	 *         the yield never happens. */
	sync_endwrite(&self->h_lock);

	/* No pre-allocated memory found. -> Allocate new memory. */
	{
		vm_vpage_t pageaddr;
		size_t page_bytes, unused_size;
		if unlikely(OVERFLOW_UADD(result.hp_siz, pagedir_pagesize() - 1, &page_bytes))
			IFELSE_NX(goto err, THROW(E_BADALLOC_INSUFFICIENT_HEAP_MEMORY, result.hp_siz));
		if (!(flags & GFP_NOOVER)) {
			/* Add overhead for overallocation. */
			if unlikely(OVERFLOW_UADD(page_bytes, self->h_overalloc, &page_bytes))
				goto allocate_without_overalloc;
		}
		page_bytes &= ~(pagedir_pagesize() - 1);
		pageaddr = core_page_alloc_nx(self,
		                              CORE_PAGE_MALLOC_AUTO,
		                              page_bytes / pagedir_pagesize(),
		                              1,
		                              flags);
		if unlikely(pageaddr == CORE_PAGE_MALLOC_ERROR) {
allocate_without_overalloc:
			/* Try again without overallocation. */
			page_bytes = result.hp_siz + (pagedir_pagesize() - 1);
			page_bytes &= ~(pagedir_pagesize() - 1);
			pageaddr = FUNC(core_page_alloc)(self,
			                                 CORE_PAGE_MALLOC_AUTO,
			                                 page_bytes / pagedir_pagesize(),
			                                 1,
			                                 flags);
#ifdef HEAP_NX
			if unlikely(pageaddr == CORE_PAGE_MALLOC_ERROR)
				goto err;
#endif /* HEAP_NX */
		}
		PRINTK_SYSTEM_ALLOCATION("Acquire kernel heap: %p...%p\n",
		                         VM_PAGE2ADDR(pageaddr),
		                         VM_PAGE2ADDR(pageaddr) + page_bytes - 1);
		/* Got it! */
		result.hp_ptr = (VIRT void *)VM_PAGE2ADDR(pageaddr);
		unused_size   = page_bytes - result.hp_siz;
		if unlikely(unused_size < HEAP_MINSIZE)
			result.hp_siz = page_bytes;
		else {
			void *unused_begin = (void *)((uintptr_t)result.hp_ptr + result.hp_siz);
			/* Free unused size. */
			HEAP_ASSERT(IS_ALIGNED(unused_size, HEAP_ALIGNMENT));
			HEAP_ASSERT(IS_ALIGNED((uintptr_t)unused_begin, HEAP_ALIGNMENT));
#ifdef CONFIG_DEBUG_HEAP
			if (!(flags & GFP_CALLOC)) {
				/* Be smart about how much memory we fill with the debug initializer pattern.
				 * As far as the heap validator is concerned, pages that haven't been initialized
				 * are always valid (aka. they don't have their contents checked).
				 * And knowing that `heap_free_raw()' will only modify up to the first `SIZEOF_MFREE'
				 * bytes, starting at `unused_begin', all we really need to pat out markers for
				 * no man's land memory within the last page that still has to be allocated for
				 * `heap_free_raw()' to function properly. */
				if (flags & GFP_PREFLT) {
					/* If memory got pre-faulted, we still have to pat _everything_,
					 * because it's already been allocated at this point. */
					mempatl(unused_begin, DEBUGHEAP_NO_MANS_LAND, unused_size);
				} else {
					uintptr_t page_remainder;
					page_remainder = CEIL_ALIGN((uintptr_t)unused_begin, pagedir_pagesize()) - (uintptr_t)unused_begin;
					if (page_remainder < SIZEOF_MFREE)
						page_remainder += pagedir_pagesize();
					if (page_remainder > unused_size)
						page_remainder = unused_size;
					mempatl(unused_begin, DEBUGHEAP_NO_MANS_LAND, page_remainder);
				}
			}
#endif /* CONFIG_DEBUG_HEAP */
			/* Release the unused memory. */
			heap_free_raw(self, unused_begin, unused_size, flags);
		}
#if 0
		if (vm_kernel_treelock_trywrite()) {
			/* Try to optimize the VM by merging the new mapping with adjacent nodes. */
			vm_merge_before(&vm_kernel, pageaddr);
			vm_merge_before(&vm_kernel, pageaddr + page_bytes / pagedir_pagesize());
			vm_kernel_treelock_endwrite();
		}
#endif
	}
	HEAP_ASSERT(IS_ALIGNED((uintptr_t)result.hp_ptr, HEAP_ALIGNMENT));
	HEAP_ASSERT(IS_ALIGNED((uintptr_t)result.hp_siz, HEAP_ALIGNMENT));
	HEAP_ASSERT(result.hp_siz >= HEAP_MINSIZE);
	heap_validate_all_pedantic();
	return result;
#ifdef HEAP_NX
err:
	result.hp_ptr = NULL;
	result.hp_siz = 0;
	return result;
#endif /* HEAP_NX */
}



PRIVATE size_t
NOTHROW_NX(KCALL FUNC(heap_allat_partial))(struct heap *__restrict self,
                                           VIRT void *__restrict ptr,
                                           gfp_t flags) {
	ATREE_SEMI_T(uintptr_t)
	addr_semi;
	ATREE_LEVEL_T addr_level;
	gfp_t slot_flags;
	size_t result;
	struct mfree **pslot, *slot;
	HEAP_ASSERT(IS_ALIGNED((uintptr_t)ptr, HEAP_ALIGNMENT));
	TRACE("heap_allat_partial(%p,%p,%#x)\n", self, ptr, flags);
again:
	addr_semi  = ATREE_SEMI0(uintptr_t);
	addr_level = ATREE_LEVEL0(uintptr_t);

	if (!FUNC(heap_acquirelock)(self, flags))
		IFELSE_NX(return 0, THROW(E_WOULDBLOCK_PREEMPTED));

	/* Check if the requested address is in cache. */
	pslot = mfree_tree_plocate_at(&self->h_addr, (uintptr_t)ptr,
	                              &addr_semi, &addr_level);
	if (!pslot) {
		vm_vpage_t ptr_page;
		sync_endwrite(&self->h_lock);
		/* Not in cache. Try to allocate associated core memory. */
		ptr_page = VM_ADDR2PAGE((vm_virt_t)ptr);
		ptr_page = FUNC(core_page_alloc_check_hint)(self,
		                                            ptr_page,
		                                            1,
		                                            1,
		                                            flags);
		if (ptr_page == CORE_PAGE_MALLOC_ERROR)
			return 0;
#ifdef CONFIG_DEBUG_HEAP
		memsetl((void *)VM_PAGE2ADDR(ptr_page),
		        DEBUGHEAP_NO_MANS_LAND, pagedir_pagesize() / 4);
#endif /* CONFIG_DEBUG_HEAP */
		/* Release the page to the heap and allocate again.
		 * NOTE: Set the `GFP_NOTRIM' to prevent the memory
		 *       from be unmapped immediately. */
		heap_free_raw(self, (void *)VM_PAGE2ADDR(ptr_page), pagedir_pagesize(),
		              flags | GFP_NOTRIM);
#if 0
		if (vm_kernel_treelock_trywrite()) {
			/* Try to optimize the VM by merging the new mapping with adjacent nodes. */
			vm_merge_before(&vm_kernel, ptr_page);
			vm_merge_before(&vm_kernel, ptr_page + 1);
			vm_kernel_treelock_endwrite();
		}
#endif
		goto again;
	}
	slot = *pslot;
	HEAP_ASSERT((vm_virt_t)ptr >= MFREE_BEGIN(slot));
	if ((vm_virt_t)ptr == MFREE_BEGIN(slot)) {
		/* Allocate this entire slot, then remove unused memory from the end. */
		HEAP_ASSERTE(mfree_tree_pop_at(pslot, addr_semi, addr_level) == slot);
		LLIST_REMOVE(slot, mf_lsize);
		sync_endwrite(&self->h_lock);
		result     = slot->mf_size;
		slot_flags = (flags & (__GFP_HEAPMASK | GFP_INHERIT)) | slot->mf_flags;
#ifndef CONFIG_DEBUG_HEAP
		if ((slot_flags & GFP_CALLOC) && (flags & GFP_CALLOC))
			memset(slot, 0, SIZEOF_MFREE);
#else /* !CONFIG_DEBUG_HEAP */
		if (flags & GFP_CALLOC)
			memset(slot, 0, SIZEOF_MFREE);
		else {
			mempatl(slot, DEBUGHEAP_NO_MANS_LAND, SIZEOF_MFREE);
		}
#endif /* CONFIG_DEBUG_HEAP */
	} else {
		size_t free_offset = (uintptr_t)ptr - MFREE_BEGIN(slot);
		HEAP_ASSERT(IS_ALIGNED(free_offset, HEAP_ALIGNMENT));
		if unlikely(free_offset < HEAP_MINSIZE) {
			/* The remaining part of the slot is too small.
			 * Ask the core if it can allocate the the previous
			 * page for us, so we can merge this slot with that
			 * page to get a chance of leaving a part large enough
			 * for us to return to the heap.
			 * NOTE: If the slot doesn't start at a page boundary,
			 *       we already know that the requested part has already
			 *       been allocated (meaning this allocation is impossible) */
			vm_vpage_t slot_page;
			sync_endwrite(&self->h_lock);
			if (MFREE_BEGIN(slot) & (pagedir_pagesize() - 1))
				return 0; /* Not page-aligned. */
			slot_page = VM_ADDR2PAGE(MFREE_BEGIN(slot));
			if unlikely(slot_page == 0)
				return 0; /* Shouldn't happen: can't allocate previous page that doesn't exist. */
			slot_page = FUNC(core_page_alloc_check_hint)(self,
			                                             slot_page - 1,
			                                             1,
			                                             1,
			                                             flags);
			if (slot_page == CORE_PAGE_MALLOC_ERROR)
				return 0; /* Failed to allocate the associated core-page. */
			/* Free the page, so-as to try and merge it with the slot from before.
			 * NOTE: Set the `GFP_NOTRIM' to prevent the memory
			 *       from be unmapped immediately. */
#ifdef CONFIG_DEBUG_HEAP
			memsetl((void *)VM_PAGE2ADDR(slot_page),
			        DEBUGHEAP_NO_MANS_LAND, pagedir_pagesize() / 4);
#endif /* CONFIG_DEBUG_HEAP */
			heap_free_raw(self, (void *)VM_PAGE2ADDR(slot_page),
			              pagedir_pagesize(),
			              (flags & (__GFP_HEAPMASK | GFP_INHERIT)) | GFP_NOTRIM);
#if 0
			if (vm_kernel_treelock_trywrite()) {
				/* Try to optimize the VM by merging the new mapping with adjacent nodes. */
				vm_merge_before(&vm_kernel, slot_page);
				vm_merge_before(&vm_kernel, slot_page + 1);
				vm_kernel_treelock_endwrite();
			}
#endif
			goto again;
		}
		result = slot->mf_size - free_offset;
		if unlikely(result < HEAP_MINSIZE) {
			/* Too close to the back. - Try to allocate the next page. */
			vm_virt_t slot_end = MFREE_END(slot);
			sync_endwrite(&self->h_lock);
			if (slot_end & (pagedir_pagesize() - 1))
				return 0; /* Not page-aligned. */
			if (FUNC(core_page_alloc_check_hint)(self,
			                                     VM_ADDR2PAGE(slot_end),
			                                     1,
			                                     1,
			                                     flags) ==
			    CORE_PAGE_MALLOC_ERROR)
				return 0; /* Failed to allocate the associated core-page. */
#ifdef CONFIG_DEBUG_HEAP
			memsetl((void *)slot_end, DEBUGHEAP_NO_MANS_LAND, pagedir_pagesize() / 4);
#endif /* CONFIG_DEBUG_HEAP */
			heap_free_raw(self, (void *)slot_end, pagedir_pagesize(),
			              (flags & (__GFP_HEAPMASK | GFP_INHERIT)) |
			              GFP_NOTRIM);
			goto again;
		}
		HEAP_ASSERTE(mfree_tree_pop_at(pslot, addr_semi, addr_level) == slot);
		LLIST_REMOVE(slot, mf_lsize);
#ifdef CONFIG_HEAP_TRACE_DANGLE
		/* Trace leading free data as dangling. */
		HEAP_ADD_DANGLE(self, free_offset);
#endif /* CONFIG_HEAP_TRACE_DANGLE */
		sync_endwrite(&self->h_lock);
		slot_flags = (flags & (__GFP_HEAPMASK | GFP_INHERIT)) | slot->mf_flags;
		if (slot_flags & GFP_CALLOC)
			memset(slot, 0, MIN(free_offset, SIZEOF_MFREE));
#ifdef CONFIG_DEBUG_HEAP
		else {
			mempatl(slot, DEBUGHEAP_NO_MANS_LAND,
			        MIN(free_offset, SIZEOF_MFREE));
		}
#endif /* CONFIG_DEBUG_HEAP */
		/* Release unused memory below the requested address. */
		heap_free_raw(self, (void *)MFREE_BEGIN(slot),
		              free_offset, slot_flags);
#ifdef CONFIG_HEAP_TRACE_DANGLE
		HEAP_SUB_DANGLE(self, free_offset);
#endif /* CONFIG_HEAP_TRACE_DANGLE */
	}
	/* Initialize newly allocated memory according to what the caller wants. */
#ifdef CONFIG_DEBUG_HEAP
	if (!(flags & GFP_CALLOC))
		reset_heap_data((byte_t *)ptr, DEBUGHEAP_FRESH_MEMORY, result);
#endif /* CONFIG_DEBUG_HEAP */
	if ((flags & GFP_CALLOC) && !(slot_flags & GFP_CALLOC))
		memset(ptr, 0, result);
	HEAP_ASSERT(result >= HEAP_MINSIZE);
	heap_validate_all_pedantic();
	return result;
}


PUBLIC size_t
NOTHROW_NX(KCALL FUNC(heap_allat_untraced))(struct heap *__restrict self,
                                            VIRT void *__restrict ptr,
                                            size_t num_bytes, gfp_t flags) {
	size_t unused_size, alloc_size;
	size_t result = 0;
	TRACE("heap_allat_untraced(%p,%p,%Iu,%#x)\n", self, ptr, num_bytes, flags);
	if unlikely(!IS_ALIGNED((uintptr_t)ptr, HEAP_ALIGNMENT))
		goto err; /* Badly aligned pointer (can't allocate anything here...) */
	if unlikely(OVERFLOW_UADD(num_bytes, (size_t)(HEAP_ALIGNMENT - 1), &alloc_size))
		IFELSE_NX(goto err, THROW(E_BADALLOC_INSUFFICIENT_HEAP_MEMORY, num_bytes));
	alloc_size &= ~(HEAP_ALIGNMENT - 1);
	if unlikely(alloc_size < HEAP_MINSIZE)
		alloc_size = HEAP_MINSIZE;
	/* Allocate memory from the given range. */
	while (result < alloc_size) {
		size_t part;
		/* Allocate the new missing part. */
		IFELSE_NX(, TRY) {
			part = FUNC(heap_allat_partial)(self,
			                                (void *)((uintptr_t)ptr + result),
			                                flags);
		} IFELSE_NX(if (!part), EXCEPT) {
			if (result)
				heap_free_untraced(self, ptr, result, flags);
			IFELSE_NX(goto err, RETHROW());
		}
#ifndef HEAP_NX
		if unlikely(!part) {
			/* Failed to allocate the entirety of the requested range.
			 * Free what was already allocated. */
			if (result)
				heap_free_untraced(self, ptr, result, flags);
			goto err;
		}
#endif /* !HEAP_NX */
		result += part;
	}
	/* With everything now allocated, free what the caller didn't ask for. */
	HEAP_ASSERT(result >= alloc_size);
	unused_size = result - alloc_size;
	if (unused_size >= HEAP_MINSIZE) {
		heap_free_untraced(self,
		                   (void *)((uintptr_t)ptr + alloc_size),
		                   unused_size, flags);
		result = alloc_size;
	}
	return result;
err:
	return 0;
}


PUBLIC struct heapptr
NOTHROW_NX(KCALL FUNC(heap_align_untraced))(struct heap *__restrict self,
                                            size_t min_alignment, ptrdiff_t offset,
                                            size_t num_bytes, gfp_t flags) {
	struct heapptr result_base, result;
	size_t nouse_size, alloc_bytes;
	size_t heap_alloc_bytes;
	assert(min_alignment != 0);
	assertf(!(min_alignment & (min_alignment - 1)),
	        "Invalid min_alignment: %IX",
	        min_alignment);
	/* Truncate the offset, if it was a multiple of `min_alignment'
	 * HINT: This also ensures that `offset' is positive. */
	offset &= (min_alignment - 1);
	/* Forward to the regular allocator when the constraints allow it. */
	if (min_alignment <= HEAP_ALIGNMENT && !offset)
		return FUNC(heap_alloc_untraced)(self, num_bytes, flags);
	if unlikely(OVERFLOW_UADD(num_bytes, (size_t)(HEAP_ALIGNMENT - 1), &alloc_bytes))
		IFELSE_NX(goto err, THROW(E_BADALLOC_INSUFFICIENT_HEAP_MEMORY, num_bytes));
	alloc_bytes &= ~(HEAP_ALIGNMENT - 1);
	if unlikely(alloc_bytes < HEAP_MINSIZE)
		alloc_bytes = HEAP_MINSIZE;
#if 1
	{
		struct heapptr result;
		struct mfree **iter, **end;
		iter = &self->h_size[HEAP_BUCKET_OF(alloc_bytes)];
		end  = COMPILER_ENDOF(self->h_size);
		HEAP_ASSERTF(iter >= self->h_size &&
		             iter < COMPILER_ENDOF(self->h_size),
		             "HEAP_BUCKET_OF(%Iu) = %Iu/%Iu",
		             alloc_bytes, HEAP_BUCKET_OF(alloc_bytes),
		             COMPILER_LENOF(self->h_size));
		if (!FUNC(heap_acquirelock)(self, flags))
			IFELSE_NX(goto err, THROW(E_WOULDBLOCK_PREEMPTED));
		/* Search for existing free data that
		 * fit the required alignment and offset. */
		for (; iter != end; ++iter) {
			struct mfree *chain;
			void *hkeep, *tkeep;
			gfp_t chain_flags;
			vm_virt_t alignment_base;
			size_t hkeep_size, tkeep_size;
#ifdef CONFIG_HEAP_TRACE_DANGLE
			size_t dangle_size;
#endif /* CONFIG_HEAP_TRACE_DANGLE */
			/* Search this bucket. */
			chain = *iter;
			while (chain &&
			       (HEAP_ASSERTF(IS_ALIGNED(MFREE_SIZE(chain), HEAP_ALIGNMENT),
			                     "MFREE_SIZE(chain) = 0x%Ix",
			                     MFREE_SIZE(chain)),
			        MFREE_SIZE(chain) < alloc_bytes))
				chain = LLIST_NEXT(chain, mf_lsize);
			if (!chain)
				continue;
			/* Check if this chain entry can sustain our required alignment. */
			alignment_base = (vm_virt_t)chain;
			alignment_base += offset;
			alignment_base += (min_alignment - 1);
			alignment_base &= ~(min_alignment - 1);
			alignment_base -= offset;
			if unlikely(alignment_base < (vm_virt_t)chain)
				alignment_base += min_alignment;

			/* `alignment_base' is now the effective base address which we want to use.
			 * However, in case it doesn't match the free-node, we must advance it to
			 * the nearest correctly aligned address (by adding `min_alignment').
			 * This is required to ensure that the unused portion at `chain' continues
			 * to be large enough to be re-freed (should we choose to use this node) */
			if (alignment_base != (vm_virt_t)chain) {
				while ((size_t)(alignment_base - (vm_virt_t)chain) < HEAP_MINSIZE)
					alignment_base += min_alignment;
			}
			/* Check if the node still contains enough memory for the requested allocation. */
			if ((alignment_base + alloc_bytes) > MFREE_END(chain))
				continue; /* The chain entry is too small once alignment was taken into consideration. */
			HEAP_ASSERTE(mfree_tree_remove(&self->h_addr, (uintptr_t)MFREE_BEGIN(chain)) == chain);
			LLIST_REMOVE(chain, mf_lsize);
#ifdef CONFIG_HEAP_TRACE_DANGLE
			/* Trace potentially unused data as dangling. */
			dangle_size = chain->mf_size - alloc_bytes;
			HEAP_ADD_DANGLE(self, dangle_size);
#endif /* CONFIG_HEAP_TRACE_DANGLE */
			sync_endwrite(&self->h_lock);
			HEAP_ASSERT(IS_ALIGNED(alignment_base + offset, min_alignment));

			/* All right! we can actually use this one! */
			result.hp_ptr = (VIRT void *)alignment_base;
			result.hp_siz = alloc_bytes;
			/* Figure out how much memory should be re-freed at the front and back. */
			chain_flags = chain->mf_flags;
			hkeep       = (void *)chain;
			hkeep_size  = (size_t)(alignment_base - (vm_virt_t)chain);
			tkeep       = (void *)((uintptr_t)result.hp_ptr + alloc_bytes);
			tkeep_size  = (size_t)(MFREE_END(chain) - (vm_virt_t)tkeep);
#ifdef CONFIG_HEAP_RANDOMIZE_OFFSETS
			if (tkeep_size > min_alignment) {
				/* Add a random offset to the resulting pointer. */
				uintptr_t random_offset;
				random_offset = krand() % tkeep_size;
				random_offset += (min_alignment - 1);
				random_offset &= ~(min_alignment - 1);
				/* Make sure to only add the offset if hkeep's size will be large enough! */
				if ((hkeep_size + random_offset) >= HEAP_MINSIZE &&
				    ((tkeep_size == random_offset) ||
				     ((tkeep_size >= random_offset) && (tkeep_size - random_offset) >= HEAP_MINSIZE))) {
					hkeep_size += random_offset;
					tkeep_size -= random_offset;
					tkeep         = (byte_t *)tkeep + random_offset;
					result.hp_ptr = (byte_t *)result.hp_ptr + random_offset;
				}
			}
#endif /* CONFIG_HEAP_RANDOMIZE_OFFSETS */

			if (hkeep_size) {
				HEAP_ASSERT(hkeep_size >= HEAP_MINSIZE);
				/* Reset data of the head if we're to re-free them. */
				if (chain_flags & GFP_CALLOC)
					memset(hkeep, 0, SIZEOF_MFREE);
#ifdef CONFIG_DEBUG_HEAP
				else {
					mempatl(hkeep, DEBUGHEAP_NO_MANS_LAND, SIZEOF_MFREE);
				}
#endif /* CONFIG_DEBUG_HEAP */
				heap_free_underallocation(self,
				                          hkeep,
				                          hkeep_size,
				                          chain_flags);
			}
			if (tkeep_size < HEAP_MINSIZE) {
				/* The tail is too small (or non-existent).
				 * -> We must allocate it, too. */
				result.hp_siz += tkeep_size;
			} else {
				/* Free the tail pointer. */
				HEAP_ASSERT((byte_t *)tkeep ==
				            (byte_t *)result.hp_ptr + result.hp_siz);
				heap_free_overallocation(self,
				                         tkeep,
				                         tkeep_size,
				                         (flags & ~(GFP_CALLOC)) |
				                         chain_flags);
			}
#ifdef CONFIG_HEAP_TRACE_DANGLE
			/* Remove dangling data. */
			HEAP_SUB_DANGLE(self, dangle_size);
#endif /* CONFIG_HEAP_TRACE_DANGLE */
			/* Initialize the resulting memory. */
			if (flags & GFP_CALLOC) {
				if (chain_flags & MFREE_FZERO)
					memset(result.hp_ptr, 0, SIZEOF_MFREE);
				else {
					memset(result.hp_ptr, 0, result.hp_siz);
				}
			}
#ifdef CONFIG_DEBUG_HEAP
			else {
				reset_heap_data((byte_t *)result.hp_ptr,
				                DEBUGHEAP_FRESH_MEMORY,
				                result.hp_siz);
			}
#endif /* CONFIG_DEBUG_HEAP */
			HEAP_ASSERT(IS_ALIGNED((uintptr_t)result.hp_ptr, HEAP_ALIGNMENT));
			HEAP_ASSERTF(IS_ALIGNED((uintptr_t)result.hp_ptr + offset, min_alignment),
			             "result.hp_ptr          = %p\n"
			             "result.hp_ptr + offset = %p\n"
			             "offset                 = %p\n"
			             "min_alignment          = %p\n",
			             (uintptr_t)result.hp_ptr, (uintptr_t)result.hp_ptr + offset, (uintptr_t)offset, (uintptr_t)min_alignment);
			HEAP_ASSERT(IS_ALIGNED((uintptr_t)result.hp_siz, HEAP_ALIGNMENT));
			HEAP_ASSERT(result.hp_siz >= HEAP_MINSIZE);
			heap_validate_all_pedantic();
			return result;
		}
		sync_endwrite(&self->h_lock);
	}
#endif
	/* Fallback: Use overallocation to assert alignment. */

	/* Must overallocate by at least `HEAP_MINSIZE',
	 * so we can _always_ free unused lower memory. */
	if unlikely(OVERFLOW_UADD(alloc_bytes, min_alignment, &heap_alloc_bytes))
		IFELSE_NX(goto err, THROW(E_BADALLOC_INSUFFICIENT_HEAP_MEMORY, MAX(alloc_bytes, min_alignment)));
	if unlikely(OVERFLOW_UADD(heap_alloc_bytes, HEAP_MINSIZE, &heap_alloc_bytes))
		IFELSE_NX(goto err, THROW(E_BADALLOC_INSUFFICIENT_HEAP_MEMORY, heap_alloc_bytes));
	result_base = FUNC(heap_alloc_untraced)(self, heap_alloc_bytes, flags);
	HEAP_ASSERT(result_base.hp_siz >= heap_alloc_bytes);
	result.hp_ptr = (void *)(CEIL_ALIGN((uintptr_t)result_base.hp_ptr +
	                                    HEAP_MINSIZE + offset,
	                                    min_alignment) -
	                         offset);
	HEAP_ASSERT((uintptr_t)result.hp_ptr + alloc_bytes <=
	            (uintptr_t)result_base.hp_ptr + result_base.hp_siz);
	nouse_size = (uintptr_t)result.hp_ptr - (uintptr_t)result_base.hp_ptr;
	HEAP_ASSERT(nouse_size + alloc_bytes <= result_base.hp_siz);
	HEAP_ASSERTF(nouse_size >= HEAP_MINSIZE, "nouse_size = %Iu", nouse_size);
	HEAP_ASSERTF(IS_ALIGNED(nouse_size, HEAP_ALIGNMENT),
	             "Invalid offset (%Id) / alignment (%Iu)\n"
	             "nouse_size = %Iu",
	             offset, min_alignment, nouse_size);

	/* Release lower memory (This _MUST_ work because we've overallocated by `HEAP_MINSIZE'). */
	heap_free_untraced(self, result_base.hp_ptr, nouse_size, flags);
	result_base.hp_siz -= nouse_size;
	HEAP_ASSERT(result_base.hp_siz >= HEAP_MINSIZE);

	/* Try to release upper memory. */
	HEAP_ASSERT(result_base.hp_siz >= alloc_bytes);
	nouse_size = result_base.hp_siz - alloc_bytes;
	if (nouse_size >= HEAP_MINSIZE) {
		heap_free_untraced(self,
		                   (void *)((uintptr_t)result.hp_ptr + alloc_bytes),
		                   nouse_size, flags);
		result_base.hp_siz -= nouse_size;
	}
	HEAP_ASSERT(result_base.hp_siz >= alloc_bytes);
	HEAP_ASSERT(IS_ALIGNED((uintptr_t)result.hp_ptr + offset, min_alignment));
	result.hp_siz = result_base.hp_siz;
	HEAP_ASSERT(IS_ALIGNED((uintptr_t)result.hp_siz, HEAP_ALIGNMENT));
	HEAP_ASSERT(result.hp_siz >= HEAP_MINSIZE);
	heap_validate_all_pedantic();
	return result;
#ifdef HEAP_NX
err:
	result.hp_ptr = NULL;
	result.hp_siz = 0;
	return result;
#endif /* HEAP_NX */
}


PUBLIC struct heapptr
NOTHROW_NX(KCALL FUNC(heap_realloc_untraced))(struct heap *__restrict self,
                                              VIRT void *old_ptr, size_t old_bytes,
                                              size_t new_bytes, gfp_t alloc_flags,
                                              gfp_t free_flags) {
	struct heapptr result;
	size_t missing_bytes;
	assert(IS_ALIGNED(old_bytes, HEAP_ALIGNMENT));
	assert(!old_bytes || IS_ALIGNED((uintptr_t)old_ptr, HEAP_ALIGNMENT));
	assert(!old_bytes || old_bytes >= HEAP_MINSIZE);
	if (old_bytes == 0) {
		if (alloc_flags & GFP_NOMOVE)
			goto err;
		/* Special case: initial allocation */
		return FUNC(heap_alloc_untraced)(self, new_bytes, alloc_flags);
	}
	if unlikely(OVERFLOW_UADD(new_bytes, (size_t)(HEAP_ALIGNMENT - 1), &new_bytes))
		IFELSE_NX(goto err, THROW(E_BADALLOC_INSUFFICIENT_HEAP_MEMORY, new_bytes - (HEAP_ALIGNMENT - 1)));
	new_bytes &= ~(HEAP_ALIGNMENT - 1);
	if unlikely(new_bytes < HEAP_MINSIZE)
		new_bytes     = HEAP_MINSIZE;
	result.hp_ptr = old_ptr;
	result.hp_siz = old_bytes;
	if (new_bytes <= old_bytes) {
		size_t free_bytes;
		/* Free trailing memory. */
		free_bytes = old_bytes - new_bytes;
		if (free_bytes >= HEAP_MINSIZE) {
			heap_free_untraced(self, (void *)((uintptr_t)old_ptr + new_bytes),
			                   free_bytes, free_flags);
			result.hp_siz = new_bytes;
		}
		return result;
	}
	missing_bytes = new_bytes - old_bytes;
	missing_bytes = FUNC(heap_allat_untraced)(self, (void *)((uintptr_t)old_ptr + old_bytes),
	                                          missing_bytes, alloc_flags);
	if (missing_bytes) {
		/* Managed to extend the data block. */
		result.hp_siz += missing_bytes;
		return result;
	}
	if (alloc_flags & GFP_NOMOVE)
		goto err;
	/* Must allocate an entirely new data block and copy memory to it. */
	result = FUNC(heap_alloc_untraced)(self, new_bytes, alloc_flags);
	IFELSE_NX(if (result.hp_siz == 0) goto err;, )
#if 1
	memcpy(result.hp_ptr, old_ptr, old_bytes);
#else
	TRY {
		/* The try block is here because of the possibility of a LOA failure.
		 * NO! This mustn't be something I should worry about -- Make it so
		 *     that heap memory mapped by the kernel is able to reserve its
		 *     physical memory! */
		memcpy(result.hp_ptr, old_ptr, old_bytes);
	} EXCEPT {
		heap_free_untraced(self, result.hp_ptr, result.hp_siz,
		                   alloc_flags & ~GFP_CALLOC);
		RETHROW();
	}
#endif
	/* Free the old data block. */
	heap_free_untraced(self, old_ptr, old_bytes,
	                   free_flags & ~GFP_CALLOC);
	return result;
err:
	result.hp_ptr = NULL;
	result.hp_siz = 0;
	return result;
}

PUBLIC struct heapptr
NOTHROW_NX(KCALL FUNC(heap_realign_untraced))(struct heap *__restrict self,
                                              VIRT void *old_ptr, size_t old_bytes,
                                              size_t min_alignment, ptrdiff_t offset,
                                              size_t new_bytes, gfp_t alloc_flags,
                                              gfp_t free_flags) {
	struct heapptr result;
	size_t missing_bytes;
	assert(IS_ALIGNED(old_bytes, HEAP_ALIGNMENT));
	assert(!old_bytes || IS_ALIGNED((uintptr_t)old_ptr, HEAP_ALIGNMENT));
	assert(!old_bytes || old_bytes >= HEAP_MINSIZE);
	if (old_bytes == 0) {
		if (alloc_flags & GFP_NOMOVE)
			goto err;
		/* Special case: initial allocation */
		return FUNC(heap_align_untraced)(self, min_alignment, offset, new_bytes, alloc_flags);
	}
	if unlikely(OVERFLOW_UADD(new_bytes, (size_t)(HEAP_ALIGNMENT - 1), &new_bytes))
		IFELSE_NX(goto err, THROW(E_BADALLOC_INSUFFICIENT_HEAP_MEMORY, new_bytes - (HEAP_ALIGNMENT - 1)));
	new_bytes &= ~(HEAP_ALIGNMENT - 1);
	result.hp_ptr = old_ptr;
	result.hp_siz = old_bytes;
	if (new_bytes <= old_bytes) {
		size_t free_bytes;
		if unlikely(new_bytes < HEAP_MINSIZE)
			new_bytes = HEAP_MINSIZE;
		/* Free trailing memory. */
		free_bytes = old_bytes - new_bytes;
		if (free_bytes >= HEAP_MINSIZE) {
			heap_free(self, (void *)((uintptr_t)old_ptr + new_bytes),
			          free_bytes, free_flags);
			result.hp_siz = new_bytes;
		}
		return result;
	}
	missing_bytes = new_bytes - old_bytes;
	missing_bytes = FUNC(heap_allat_untraced)(self, (void *)((uintptr_t)old_ptr + old_bytes),
	                                          missing_bytes, alloc_flags);
	if (missing_bytes) {
		/* Managed to extend the data block. */
		result.hp_siz += missing_bytes;
		return result;
	}
	if (alloc_flags & GFP_NOMOVE)
		goto err;
	/* Must allocate an entirely new data block and copy memory to it. */
	result = FUNC(heap_align_untraced)(self,
	                                   min_alignment,
	                                   offset,
	                                   new_bytes,
	                                   alloc_flags);
	IFELSE_NX(if (result.hp_siz == 0) goto err;, )
#if 1
	memcpy(result.hp_ptr, old_ptr, old_bytes);
#else
	TRY {
		/* The try block is here because of the possibility of a LOA failure.
		 * NO! This mustn't be something I should worry about -- Make it so
		 *     that heap memory mapped by the kernel is able to reserve its
		 *     physical memory! */
		memcpy(result.hp_ptr, old_ptr, old_bytes);
	} EXCEPT {
		heap_free_untraced(self, result.hp_ptr, result.hp_siz,
		                   alloc_flags & ~GFP_CALLOC);
		RETHROW();
	}
#endif
	/* Free the old data block. */
	heap_free_untraced(self, old_ptr, old_bytes,
	                   free_flags & ~GFP_CALLOC);
	return result;
err:
	result.hp_ptr = NULL;
	result.hp_siz = 0;
	return result;
}


PUBLIC WUNUSED ATTR_MALLOC ATTR_RETNONNULL
ATTR_ASSUME_ALIGNED(PAGEDIR_MIN_PAGESIZE) VIRT /*page-aligned*/void *
NOTHROW_NX(KCALL FUNC(vpage_alloc_untraced))(size_t num_pages,
                                             size_t alignment_in_pages,
                                             gfp_t flags) {
	vm_vpage_t result;
	result = FUNC(core_page_alloc)(&kernel_heaps[flags & GFP_LOCKED],
	                               CORE_PAGE_MALLOC_AUTO,
	                               num_pages,
	                               alignment_in_pages,
	                               flags);
#ifdef HEAP_NX
	if unlikely(result == CORE_PAGE_MALLOC_ERROR)
		return NULL;
#endif /* HEAP_NX */
	return (void *)VM_PAGE2ADDR(result);
}

PUBLIC WUNUSED ATTR_RETNONNULL
ATTR_ASSUME_ALIGNED(PAGEDIR_MIN_PAGESIZE) VIRT /*page-aligned*/void *
NOTHROW_NX(KCALL FUNC(vpage_realloc_untraced))(VIRT /*page-aligned*/void *old_base,
                                               size_t old_pages, size_t new_pages,
                                               size_t alignment_in_pages,
                                               gfp_t alloc_flags, gfp_t free_flags) {
	vm_vpage_t result;
	assertf(!old_pages || IS_ALIGNED((uintptr_t)old_base, pagedir_pagesize()),
	        "old_base = %p\n"
	        "old_pages = %Iu (%#Ix)",
	        old_base, old_pages, old_pages);
	if (new_pages <= old_pages) {
		/* Special case: Free trailing memory. */
		vpage_ffree_untraced((byte_t *)old_base + new_pages * pagedir_pagesize(),
		                     old_pages - new_pages,
		                     free_flags);
		return old_base;
	}
	if (!old_pages) {
		/* Special case: Allocate from ZERO. */
		result = FUNC(core_page_alloc)(&kernel_heaps[alloc_flags & GFP_LOCKED],
		                               CORE_PAGE_MALLOC_AUTO,
		                               new_pages,
		                               alignment_in_pages,
		                               alloc_flags);
#ifdef HEAP_NX
		if unlikely(result == CORE_PAGE_MALLOC_ERROR)
			return NULL;
#endif /* HEAP_NX */
	} else {
		/* Generic case: Try to extent a given memory mapping. */
		result = FUNC(core_page_alloc_check_hint)(&kernel_heaps[alloc_flags & GFP_LOCKED],
		                                          VM_ADDR2PAGE((vm_virt_t)old_base) + old_pages,
		                                          new_pages - old_pages,
		                                          1,
		                                          alloc_flags);
		if (result != CORE_PAGE_MALLOC_ERROR)
			return old_base; /* Extension was successful */
		/* Must allocate a new block, then copy data from the old one into it. */
		result = FUNC(core_page_alloc)(&kernel_heaps[alloc_flags & GFP_LOCKED],
		                               CORE_PAGE_MALLOC_AUTO,
		                               new_pages,
		                               alignment_in_pages,
		                               alloc_flags);
#ifdef HEAP_NX
		if unlikely(result == CORE_PAGE_MALLOC_ERROR)
			return NULL;
#endif /* HEAP_NX */
		TRY {
			memcpyl((void *)VM_PAGE2ADDR(result),
			        old_base,
			        old_pages * pagedir_pagesize() / 4);
		} EXCEPT {
			vm_unmap_kernel_ram(result, new_pages, false);
#ifdef HEAP_NX
			return NULL;
#else /* HEAP_NX */
			RETHROW();
#endif /* !HEAP_NX */
		}
		vm_unmap_kernel_ram(VM_ADDR2PAGE((vm_virt_t)old_base),
		                    old_pages,
		                    !!(free_flags & GFP_CALLOC));
	}
	return (void *)VM_PAGE2ADDR(result);
}



DECL_END

#undef NOTHROW_NX
#undef FUNC
#undef IFELSE_NX
#undef CORE_PAGE_MALLOC_ERROR
#undef HEAP_NX

