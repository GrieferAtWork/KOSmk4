/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifdef __INTELLISENSE__
#include "vm.c"
#define ALLOC_NX 1
#define PART_RAM  1
//#define PART_SWAP 1
#endif

#include <string.h>
#include <kernel/except.h>

DECL_BEGIN

#ifdef PART_RAM
#define PART_DP_DATA          dp_ramdata
#define PART_RD_BLOCKV        rd_blockv
#define PART_RD_BLOCK0        rd_block0
#define PART_RD_BLOCKC        rd_blockc
#define PART_RB_START         rb_start
#define PART_RB_SIZE          rb_size
#define PART_PAGEPTR_T        physpage_t
#define PART_PAGE_MALLOC_PART page_malloc_part
#define PART_PAGE_CCFREE      page_ccfree
#define PART_STRUCT_VM_BLOCK  struct vm_ramblock
#define IE(ram, swap)         ram
#else /* PART_RAM */
#define PART_DP_DATA          dp_swpdata
#define PART_RD_BLOCKV        sd_blockv
#define PART_RD_BLOCK0        sd_block0
#define PART_RD_BLOCKC        sd_blockc
#define PART_RB_START         sb_start
#define PART_RB_SIZE          sb_size
#define PART_PAGEPTR_T        swappage_t
#define PART_PAGE_MALLOC_PART swap_malloc_part
#define PART_PAGE_CCFREE      swap_free
#define PART_STRUCT_VM_BLOCK  struct vm_swpblock
#define IE(ram, swap)         swap
#endif /* !PART_RAM */



#ifdef PART_RAM
#ifdef ALLOC_NX
PUBLIC NONNULL((1)) struct vm_ramblock *
NOTHROW(KCALL vm_do_allocram_nx)(struct vm_ramblock *__restrict pblock0,
                                 physpagecnt_t num_pages, gfp_t flags)
#else /* ALLOC_NX */
PUBLIC ATTR_RETNONNULL NONNULL((1)) struct vm_ramblock *KCALL
vm_do_allocram(struct vm_ramblock *__restrict pblock0,
               physpagecnt_t num_pages, gfp_t flags)
		THROWS(E_WOULDBLOCK, E_BADALLOC)
#endif /* !ALLOC_NX */
{
	physpage_t block0_addr;
	physpagecnt_t block0_size;
	struct vm_ramblock *blocks;
	struct vm_ramblock *new_blocks;
	size_t blockc;
	block0_addr = page_malloc_part(1, num_pages, &block0_size);
	if unlikely(block0_addr == PHYSPAGE_INVALID) {
#ifdef ALLOC_NX
		return NULL;
#else /* ALLOC_NX */
		THROW(E_BADALLOC_INSUFFICIENT_PHYSICAL_MEMORY, num_pages * PAGESIZE);
#endif /* !ALLOC_NX */
	}
	if (block0_size >= num_pages) {
		pblock0->rb_start = block0_addr;
		pblock0->rb_size  = block0_size;
		return pblock0;
	}
	blockc = 1;
#ifdef ALLOC_NX
	blocks = (struct vm_ramblock *)kmalloc_nx(2 * sizeof(struct vm_ramblock), flags);
	if unlikely(!blocks) {
		page_ccfree(block0_addr,
		            block0_size);
		return NULL;
	}
#else /* ALLOC_NX */
	TRY {
		blocks = (struct vm_ramblock *)kmalloc(2 * sizeof(struct vm_ramblock), flags);
	} EXCEPT {
		page_ccfree(block0_addr,
		            block0_size);
		RETHROW();
	}
	TRY
#endif /* !ALLOC_NX */
	{
		blocks[0].rb_start = block0_addr;
		blocks[0].rb_size  = block0_size;
		/* Allocate more blocks and populate the block-vector. */
		while (block0_size < num_pages) {
			physpagecnt_t new_block_size;
			if (blockc >= (kmalloc_usable_size(blocks) / sizeof(struct vm_ramblock))) {
				new_blocks = (struct vm_ramblock *)krealloc_nx(blocks,
				                                               (blockc * 2) * sizeof(struct vm_ramblock),
				                                               flags);
				if unlikely(!new_blocks) {
#ifdef ALLOC_NX
					new_blocks = (struct vm_ramblock *)krealloc_nx(blocks,
					                                               (blockc + 1) * sizeof(struct vm_ramblock),
					                                               flags);
					if unlikely(!new_blocks)
						goto err_blocks;
#else /* ALLOC_NX */
					new_blocks = (struct vm_ramblock *)krealloc(blocks,
					                                            (blockc + 1) * sizeof(struct vm_ramblock),
					                                            flags);
#endif /* !ALLOC_NX */
				}
				blocks = new_blocks;
			}
			/* Allocate the next part. */
			block0_addr = page_malloc_part(1,
			                               num_pages - block0_size,
			                               &new_block_size);
			if unlikely(block0_addr == PHYSPAGE_INVALID) {
#ifdef ALLOC_NX
				goto err_blocks;
#else /* ALLOC_NX */
				THROW(E_BADALLOC_INSUFFICIENT_PHYSICAL_MEMORY,
				      (num_pages - block0_size) * PAGESIZE);
#endif /* !ALLOC_NX */
			}
			/* Insert new blocks in the front, thus optimizing to better allocate
			 * memory in its proper order, following the assumption that page_malloc()
			 * will prefer allocating memory in top-down priority ordering. */
			memmoveup(&blocks[1], &blocks[0],
			          blockc, sizeof(struct vm_ramblock));
			blocks[0].PART_RB_START = block0_addr;
			blocks[0].PART_RB_SIZE  = new_block_size;
			block0_size += new_block_size;
			assert(block0_size <= num_pages);
			++blockc;
		}
	}
#ifndef ALLOC_NX
	EXCEPT {
		while (blockc--) {
			page_ccfree(blocks[blockc].rb_start,
			            blocks[blockc].rb_size);
		}
		kfree(blocks);
		RETHROW();
	}
#endif /* !ALLOC_NX */
	/* Release unused memory. */
	new_blocks = (struct vm_ramblock *)krealloc_nx(blocks,
	                                               blockc * sizeof(struct vm_ramblock),
	                                               flags);
	if likely(new_blocks)
		blocks = new_blocks;
	/* All right! we've allocated all of the necessary blocks! */
	*(size_t *)pblock0 = blockc;
	return blocks;
#ifdef ALLOC_NX
err_blocks:
	while (blockc--) {
		page_ccfree(blocks[blockc].rb_start,
		            blocks[blockc].rb_size);
	}
	kfree(blocks);
	return NULL;
#endif /* ALLOC_NX */
#undef INHERITED_FLAGS
}
#endif /* PART_RAM */




/* Allocate/free ram/swap data for the given data part.
 * NOTE: The caller must be holding a write-lock to `self', or
 *      `self' must not be shared (`isshared(self) == false')
 * @return: * : One of VM_DATAPART_ALLOC_*. */
PUBLIC NONNULL((1)) unsigned int
#ifdef ALLOC_NX
#ifdef PART_RAM
NOTHROW(KCALL vm_datapart_allocram_nx)(struct vm_datapart *__restrict self, gfp_t flags)
#else /* PART_RAM */
NOTHROW(KCALL vm_datapart_allocswap_nx)(struct vm_datapart *__restrict self, gfp_t flags)
#endif /* !PART_RAM */
#define INHERITED_FLAGS   (flags & GFP_INHERIT)
#else /* ALLOC_NX */
#ifdef PART_RAM
KCALL vm_datapart_allocram(struct vm_datapart *__restrict self)
#else /* PART_RAM */
KCALL vm_datapart_allocswap(struct vm_datapart *__restrict self)
#endif /* !PART_RAM */
#define INHERITED_FLAGS    0
		THROWS(E_WOULDBLOCK, E_BADALLOC)
#endif /* !ALLOC_NX */
{
	PART_PAGEPTR_T block0_addr;
	physpagecnt_t block0_size, num_pages;
	assert(sync_writing(self) || !isshared(self) ||
	       (!PREEMPTION_ENABLED() && cpu_online_count <= 1));
	assert(self->dp_state == VM_DATAPART_STATE_ABSENT);
	num_pages   = vm_datapart_numvpages(self);
	block0_addr = PART_PAGE_MALLOC_PART(1, num_pages, &block0_size);
	if unlikely(block0_addr == IE(PHYSPAGE_INVALID, SWAPPTR_INVALID)) {
		sync_endwrite(self);
		THROW(IE(E_BADALLOC_INSUFFICIENT_PHYSICAL_MEMORY,
		         E_BADALLOC_INSUFFICIENT_SWAP_SPACE),
		      num_pages * PAGESIZE);
	}
	if (block0_size >= num_pages) {
		self->PART_DP_DATA.PART_RD_BLOCKV               = &self->PART_DP_DATA.PART_RD_BLOCK0;
		self->PART_DP_DATA.PART_RD_BLOCK0.PART_RB_START = block0_addr;
		self->PART_DP_DATA.PART_RD_BLOCK0.PART_RB_SIZE  = block0_size;
	} else {
		/* Must allocate dynamically. */
		PART_STRUCT_VM_BLOCK *blocks, *new_blocks;
		size_t blockc = 1;
		blocks = (PART_STRUCT_VM_BLOCK *)kmalloc_nx(2 * sizeof(PART_STRUCT_VM_BLOCK),
		                                            GFP_ATOMIC | GFP_LOCKED |
		                                            GFP_PREFLT | GFP_VCBASE |
		                                            INHERITED_FLAGS);
		if (!blocks) {
			sync_endwrite(self);
#ifdef ALLOC_NX
			blocks = (PART_STRUCT_VM_BLOCK *)kmalloc_nx(2 * sizeof(PART_STRUCT_VM_BLOCK),
			                                            GFP_LOCKED | GFP_PREFLT | GFP_VCBASE |
			                                            INHERITED_FLAGS);
			if unlikely(!blocks) {
				PART_PAGE_CCFREE(block0_addr, block0_size);
				return VM_DATAPART_ALLOC_FAILURE;
			}
#else /* ALLOC_NX */
			TRY {
				blocks = (PART_STRUCT_VM_BLOCK *)kmalloc(2 * sizeof(PART_STRUCT_VM_BLOCK),
				                                         GFP_LOCKED | GFP_PREFLT | GFP_VCBASE |
				                                         INHERITED_FLAGS);
			} EXCEPT {
				PART_PAGE_CCFREE(block0_addr, block0_size);
				RETHROW();
			}
#endif /* !ALLOC_NX */
			blocks[0].PART_RB_START = block0_addr;
			blocks[0].PART_RB_SIZE  = block0_size;
realloc_without_locks:
#ifndef ALLOC_NX
			TRY
#endif /* !ALLOC_NX */
			{
				/* Allocate more blocks and populate the block-vector. */
				while (block0_size < num_pages) {
					physpagecnt_t new_block_size;
					if (blockc >= (kmalloc_usable_size(blocks) / sizeof(PART_STRUCT_VM_BLOCK))) {
						new_blocks = (PART_STRUCT_VM_BLOCK *)krealloc_nx(blocks, (blockc * 2) * sizeof(PART_STRUCT_VM_BLOCK),
						                                                 GFP_LOCKED | GFP_PREFLT | GFP_VCBASE |
						                                                 INHERITED_FLAGS);
						if unlikely(!new_blocks) {
#ifdef ALLOC_NX
							new_blocks = (PART_STRUCT_VM_BLOCK *)krealloc_nx(blocks, (blockc + 1) * sizeof(PART_STRUCT_VM_BLOCK),
							                                                 GFP_LOCKED | GFP_PREFLT | GFP_VCBASE |
							                                                 INHERITED_FLAGS);
							if unlikely(!new_blocks)
								goto err_blocks;
#else /* ALLOC_NX */
						new_blocks = (PART_STRUCT_VM_BLOCK *)krealloc(blocks, (blockc + 1) * sizeof(PART_STRUCT_VM_BLOCK),
						                                              GFP_LOCKED | GFP_PREFLT | GFP_VCBASE |
						                                              INHERITED_FLAGS);
#endif /* !ALLOC_NX */
						}
						blocks = new_blocks;
					}
					/* Allocate the next part. */
					block0_addr = PART_PAGE_MALLOC_PART(1,
					                                    num_pages - block0_size,
					                                    &new_block_size);
					if unlikely(block0_addr == PHYSPAGE_INVALID) {
#ifdef ALLOC_NX
						goto err_blocks;
#else /* ALLOC_NX */
					THROW(IE(E_BADALLOC_INSUFFICIENT_PHYSICAL_MEMORY,
					         E_BADALLOC_INSUFFICIENT_SWAP_SPACE),
					      num_pages - block0_size * PAGESIZE);
#endif /* !ALLOC_NX */
					}
					/* Insert new blocks in the front, thus optimizing to better allocate
					 * memory in its proper order, following the assumption that page_malloc()
					 * will prefer allocating memory in top-down priority ordering. */
					memmoveup(&blocks[1], &blocks[0],
					          blockc, sizeof(PART_STRUCT_VM_BLOCK));
					blocks[0].PART_RB_START = block0_addr;
					blocks[0].PART_RB_SIZE  = new_block_size;
					block0_size += new_block_size;
					assert(block0_size <= num_pages);
					++blockc;
				}
				/* Release unused memory. */
				krealloc_in_place_nx(blocks, blockc * sizeof(PART_STRUCT_VM_BLOCK),
				                     GFP_LOCKED | GFP_PREFLT | GFP_VCBASE |
				                     INHERITED_FLAGS);
				sync_write(self);
				if unlikely(self->dp_state != VM_DATAPART_STATE_ABSENT) {
					while (blockc--) {
						PART_PAGE_CCFREE(blocks[blockc].PART_RB_START,
						                 blocks[blockc].PART_RB_SIZE);
					}
					kfree(blocks);
					return VM_DATAPART_ALLOC_CHANGED_RELOCK;
				}
				assert(blockc);
				self->PART_DP_DATA.PART_RD_BLOCKC = blockc;
				self->PART_DP_DATA.PART_RD_BLOCKV = blocks;
#ifdef PART_RAM
				self->dp_state = self->dp_flags & VM_DATAPART_FLAG_LOCKED
				                 ? VM_DATAPART_STATE_LOCKED
				                 : VM_DATAPART_STATE_INCORE;
#else /* PART_RAM */
				self->dp_state = VM_DATAPART_STATE_INSWAP;
#endif /* !PART_RAM */
			}
#ifdef ALLOC_NX
			return VM_DATAPART_ALLOC_SUCCESS_RELOCK;
err_blocks:
			while (blockc--) {
				PART_PAGE_CCFREE(blocks[blockc].PART_RB_START,
				                 blocks[blockc].PART_RB_SIZE);
			}
			kfree(blocks);
			return VM_DATAPART_ALLOC_FAILURE;
#else /* ALLOC_NX */
			EXCEPT {
				while (blockc--) {
					PART_PAGE_CCFREE(blocks[blockc].PART_RB_START,
					                 blocks[blockc].PART_RB_SIZE);
				}
				kfree(blocks);
				RETHROW();
			}
			return VM_DATAPART_ALLOC_SUCCESS_RELOCK;
#endif /* !ALLOC_NX */
		} else {
			blocks[0].PART_RB_START = block0_addr;
			blocks[0].PART_RB_SIZE  = block0_size;
			/* Allocate more blocks and populate the block-vector. */
			while (block0_size < num_pages) {
				physpagecnt_t new_block_size;
				if (blockc >= (kmalloc_usable_size(blocks) / sizeof(PART_STRUCT_VM_BLOCK))) {
					new_blocks = (PART_STRUCT_VM_BLOCK *)krealloc_nx(blocks, (blockc * 2) * sizeof(PART_STRUCT_VM_BLOCK),
					                                                 GFP_ATOMIC | GFP_LOCKED | GFP_PREFLT | GFP_VCBASE |
					                                                 INHERITED_FLAGS);
					if unlikely(!new_blocks) {
						new_blocks = (PART_STRUCT_VM_BLOCK *)krealloc_nx(blocks, (blockc + 1) * sizeof(PART_STRUCT_VM_BLOCK),
						                                                 GFP_ATOMIC | GFP_LOCKED | GFP_PREFLT | GFP_VCBASE |
						                                                 INHERITED_FLAGS);
						if unlikely(!new_blocks) {
							sync_endwrite(self);
							goto realloc_without_locks;
						}
					}
					blocks = new_blocks;
				}
				/* Allocate the next part. */
				block0_addr = PART_PAGE_MALLOC_PART(1,
				                                    num_pages - block0_size,
				                                    &new_block_size);
				if unlikely(block0_addr == PHYSPAGE_INVALID) {
					sync_endwrite(self);
#ifdef ALLOC_NX
					goto err_blocks;
#else /* ALLOC_NX */
					while (blockc--) {
						PART_PAGE_CCFREE(blocks[blockc].PART_RB_START,
						                 blocks[blockc].PART_RB_SIZE);
					}
					kfree(blocks);
					THROW(IE(E_BADALLOC_INSUFFICIENT_PHYSICAL_MEMORY,
					         E_BADALLOC_INSUFFICIENT_SWAP_SPACE),
					      (num_pages - block0_size) * PAGESIZE);
#endif /* !ALLOC_NX */
				}
				/* Insert new blocks in the front, thus optimizing to better allocate
				 * memory in its proper order, following the assumption that page_malloc()
				 * will prefer allocating memory in top-down priority ordering. */
				memmoveup(&blocks[1], &blocks[0],
				          blockc, sizeof(PART_STRUCT_VM_BLOCK));
				blocks[0].PART_RB_START = block0_addr;
				blocks[0].PART_RB_SIZE  = new_block_size;
				block0_size += new_block_size;
				assert(block0_size <= num_pages);
				++blockc;
			}
		}
		/* Release unused memory. */
		new_blocks = (PART_STRUCT_VM_BLOCK *)krealloc_nx(blocks, blockc * sizeof(PART_STRUCT_VM_BLOCK),
		                                                 GFP_ATOMIC | GFP_LOCKED | GFP_PREFLT | GFP_VCBASE |
		                                                 INHERITED_FLAGS);
		if likely(new_blocks)
			blocks = new_blocks;
		/* All right! we've allocated all of the necessary blocks! */
		assert(self->dp_state == VM_DATAPART_STATE_ABSENT);
		assert(blockc);
		self->PART_DP_DATA.PART_RD_BLOCKC = blockc;
		self->PART_DP_DATA.PART_RD_BLOCKV = blocks;
	}
#ifdef PART_RAM
	self->dp_state = self->dp_flags & VM_DATAPART_FLAG_LOCKED
	                 ? VM_DATAPART_STATE_LOCKED
	                 : VM_DATAPART_STATE_INCORE;
#else /* PART_RAM */
	self->dp_state = VM_DATAPART_STATE_INSWAP;
#endif /* !PART_RAM */
	return VM_DATAPART_ALLOC_SUCCESS;
}

#undef INHERITED_FLAGS


#ifdef ALLOC_NX
PUBLIC NOBLOCK NONNULL((1)) void
#ifdef PART_RAM
NOTHROW(KCALL vm_datapart_freeram)(struct vm_datapart *__restrict self, bool is_zero)
#else /* PART_RAM */
NOTHROW(KCALL vm_datapart_freeswap)(struct vm_datapart *__restrict self)
#endif /* !PART_RAM */
{
#ifdef PART_RAM
#define FREE_PART(base, num_pages) page_ffree(base, num_pages, is_zero)
#else /* PART_RAM */
#define FREE_PART(base, num_pages) swap_free(base, num_pages)
#endif /* !PART_RAM */
	if (self->PART_DP_DATA.PART_RD_BLOCKV == &self->PART_DP_DATA.PART_RD_BLOCK0) {
		FREE_PART(self->PART_DP_DATA.PART_RD_BLOCK0.PART_RB_START,
		          self->PART_DP_DATA.PART_RD_BLOCK0.PART_RB_SIZE);
	} else {
		PART_STRUCT_VM_BLOCK *blocks;
		size_t blockc;
		blockc = self->PART_DP_DATA.PART_RD_BLOCKC;
		blocks = self->PART_DP_DATA.PART_RD_BLOCKV;
		while (blockc) {
			--blockc;
			FREE_PART(blocks[blockc].PART_RB_START,
			          blocks[blockc].PART_RB_SIZE);
		}
		kfree(blocks);
	}
#undef FREE_PART
}
#endif /* ALLOC_NX */


DECL_END

#undef PART_DP_DATA
#undef PART_RD_BLOCKV
#undef PART_RD_BLOCK0
#undef PART_RD_BLOCKC
#undef PART_RB_START
#undef PART_RB_SIZE
#undef PART_PAGEPTR_T
#undef PART_PAGE_MALLOC_PART
#undef PART_PAGE_CCFREE
#undef PART_STRUCT_VM_BLOCK
#undef IE

#undef ALLOC_NX
#undef PART_SWAP
#undef PART_RAM

