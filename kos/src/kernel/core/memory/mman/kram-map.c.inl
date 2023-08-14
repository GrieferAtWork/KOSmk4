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
#ifdef __INTELLISENSE__
#include "kram-map.c"
//#define DEFINE_mman_map_kram
#define DEFINE_mman_map_kram_nx
#endif /* __INTELLISENSE__ */

#include <kernel/heap.h>
#include <kernel/malloc.h>
#include <kernel/mman.h>
#include <kernel/mman/flags.h>
#include <kernel/mman/kram.h>
#include <kernel/mman/mcoreheap.h>
#include <kernel/mman/mnode.h>
#include <kernel/mman/mpart-blkst.h>
#include <kernel/mman/mpart.h>
#include <kernel/mman/unmapped.h>
#include <kernel/paging.h>
#include <kernel/panic.h>

#include <hybrid/align.h>

#include <kos/except.h>
#include <kos/kernel/paging.h>

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

DECL_BEGIN

#ifdef DEFINE_mman_map_kram
/* @param: flags: Set of:
 *   - GFP_LOCKED:       Usual behavior
 *   - GFP_PREFLT:       Prefault everything
 *   - GFP_CALLOC:       Allocate from `mfile_zero' instead of `mfile_ndef'
 *   - GFP_ATOMIC:       Don't block when waiting to acquire any sort of lock.
 *   - GFP_NOMMAP:       Unconditionally throw `E_WOULDBLOCK_PREEMPTED'
 *   - GFP_MCHEAP:       Allocate the mnode and mpart using `mcoreheap_alloc_locked_nx()'.
 *                       This also  causes  the  `MNODE_F_COREPART'  /  `MPART_F_COREPART'
 *                       flags  to  be set  for each  resp. This  flag is  used internally
 *                       to resolve  the dependency  loop  between this  function  needing
 *                       to call kmalloc()  and kmalloc() needing  to call this  function.
 *   - GFP_MAP_FIXED:    Map memory at the given address `hint' exactly.
 *                       If memory has already been mapped at that address, then simply
 *                       return `MAP_INUSE' unconditionally.
 *   - GFP_MAP_32BIT:    Allocate   32-bit  physical  memory  addresses.  This  flag
 *                       should be combined with `GFP_LOCKED' to prevent the backing
 *                       physical memory  from being  altered (and  thus having  its
 *                       physical location changed).
 *   - GFP_MAP_PREPARED: Ensure that all mapped pages are prepared, and left as such
 *   - GFP_MAP_BELOW:    s.a. `MAP_GROWSDOWN'
 *   - GFP_MAP_ABOVE:    s.a. `MAP_GROWSUP'
 *   - GFP_MAP_NOASLR:   s.a. `MAP_NOASLR'
 *   - GFP_MAP_NOSPLIT:  Set the `MNODE_F_NOSPLIT' flag for new nodes
 *   - GFP_MAP_NOMERGE:  Set the `MNODE_F_NOMERGE' flag for new nodes, and don't try
 *                       to extend an existing node.
 *   - GFP_NOCLRC:       Don't call `system_cc()' to try to free up memory
 *   - GFP_NOSWAP:       Don't move memory to swap to free up memory
 *   - Other flags are silently ignored, but will be forwarded  onto
 *     other calls to kmalloc() that may need to be made internally.
 * Returned memory will be initialized as:
 *   - GFP_CALLOC: All zero-initialized
 *   - else:       - #ifdef CONFIG_HAVE_KERNEL_DEBUG_HEAP: DEBUGHEAP_FRESH_MEMORY
 *                 - #ifndef CONFIG_HAVE_KERNEL_DEBUG_HEAP: Undefined
 *
 * @param: hint:          Hint  for  where  the  mapping  should  go.  This  argument is
 *                        passed  onto  `mman_findunmapped()',  alongside  certain  bits
 *                        from `flags': `GFP_MAP_BELOW | GFP_MAP_ABOVE | GFP_MAP_NOASLR'
 *                        You may  pass  `NULL'  to use  either  `KERNEL_MHINT_HEAP'  or
 *                        `KERNEL_MHINT_LHEAP'   (based   on   `GFP_LOCKED')    instead.
 *                        When `GFP_MAP_FIXED' is set, this is the (possibly  unaligned)
 *                        address of where the mapping  should go. If not  page-aligned,
 *                        then the sub-page-misalignment will  be carried over into  the
 *                        return value. If another mapping  already exists at the  given
 *                        location, then unconditionally return `MAP_INUSE'
 * @param: num_bytes:     The  # of bytes to allocate. The actual amount is ceil-
 *                        aligned to multiples of  pages (after also including  a
 *                        possibly sub-page-misalignment from GFP_MAP_FIXED+hint)
 * @param: flags:         Allocation option flags (see above)
 * @param: min_alignment: The minimum alignment  for the returned  pointer. Ignored  when
 *                        the `GFP_MAP_FIXED' flag was given. Otherwise, a value  greater
 *                        than `PAGESIZE' can be used to ensure that the returned pointer
 *                        is aligned by multiple pages. s.a. `mman_findunmapped()'
 * @param: min_alignment_offset: Offset from `return' at which `min_alignment' shall be applied. */
PUBLIC NOBLOCK_IF(flags & GFP_ATOMIC) void *FCALL
mman_map_kram(void *hint, size_t num_bytes,
              gfp_t flags, size_t min_alignment,
              ptrdiff_t min_alignment_offset)
		THROWS(E_BADALLOC, E_WOULDBLOCK)
#elif defined(DEFINE_mman_map_kram_nx)
/* Non-throwing version of `mman_map_kram()'. Returns `MAP_FAILED' on error. */
PUBLIC NOBLOCK_IF(flags & GFP_ATOMIC) void *
NOTHROW(FCALL mman_map_kram_nx)(void *hint, size_t num_bytes,
                                gfp_t flags, size_t min_alignment,
                                ptrdiff_t min_alignment_offset)
#define LOCAL_NX
#endif /* ... */
{
#ifdef LOCAL_NX
#define LOCAL_krealloc                       krealloc_nx
#define LOCAL_kmalloc                        kmalloc_nx
#define LOCAL_IFNX(...)                      __VA_ARGS__
#define LOCAL_IFELSE_NX(without_nx, with_nx) with_nx
#define LOCAL_THROW(...)                     goto err
#else /* LOCAL_NX */
#define LOCAL_krealloc                       krealloc
#define LOCAL_kmalloc                        kmalloc
#define LOCAL_IFNX(...)                      /* nothing */
#define LOCAL_IFELSE_NX(without_nx, with_nx) without_nx
#define LOCAL_THROW                          THROW
#endif /* !LOCAL_NX */
	ccstate_t cache_version = CCSTATE_INIT;
	uintptr_t addend = 0;
	void *result;
	struct mnode *node = NULL;
	struct mpart *part = NULL;
	gfp_t inner_flags;
	size_t num_pages;

	/* Check if we're allowed to map more memory. */
	if unlikely(flags & GFP_NOMMAP)
		goto err_preempt;

	/* These are the flags that will be used for dynamic
	 * allocations   made    within    this    function:
	 *  - GFP_LOCKED: All   components  must  be  locked,  since  we're
	 *                allocating stuff such as mem-nodes and mem-parts!
	 *  - GFP_PREFLT: Slightly improve through-put for locked memory
	 *  - GFP_MCHEAP: If  we end up  calling ourself recursively, don't
	 *                allocate mem-nodes/parts using kmalloc(), but use
	 *                the  mcoreheap system instead, thus resolving the
	 *                dependency loop between  us calling kmalloc,  and
	 *                kmalloc calling us.
	 *  - GFP_NOOVER: Don't  over-allocate.  This is  required so  that a
	 *                recursive call with the `GFP_MCHEAP' flag set won't
	 *                try  to allocate more  memory than the ceil-aligned
	 *                size of the requested data-blob.
	 *                This is required to  ensure that a truly  recursive
	 *                call  with  the  `GFP_MCHEAP' should  never  try to
	 *                allocate  more than a single page, thus guarantying
	 *                that we'll never be needing to make use of  further
	 *                dynamic memory allocations during a recursive call.
	 *                Otherwise,  we may need to allocate additional heap
	 *                memory for use by a block-status-bitset, or a  mem-
	 *                chunk-vector.
	 *
	 * Clear the following flags:
	 *  - GFP_CALLOC: Not needed.
	 *  - GFP_MAP_*:  Don't interfere with recursive mapping locations.
	 */
	num_pages = (num_bytes + PAGESIZE - 1) >> PAGESHIFT; /* CEILDIV-style */
	num_bytes = num_pages << PAGESHIFT; /* This enforces page-alignment for `num_bytes'! */
	inner_flags = flags;
	inner_flags |= GFP_LOCKED | GFP_PREFLT | GFP_MCHEAP | GFP_NOOVER;
	inner_flags &= ~(GFP_CALLOC | GFP_MAP_FLAGS);

again_lock_mman:
#ifndef LOCAL_NX
	TRY
#endif /* !LOCAL_NX */
	{
		/* Acquire a lock to the kernel mman. */
		if (!mman_lock_tryacquire(&mman_kernel)) {
			if (flags & GFP_ATOMIC)
				goto err_preempt;
			LOCAL_IFELSE_NX(mman_lock_acquire(&mman_kernel), {
				if (!mman_lock_acquire_nx(&mman_kernel))
					goto err;
			});
		}

		/* Figure out where the mapping's supposed to go.
		 * For this purpose, we also accept a special flag `GFP_MAP_FIXED'! */
		if (flags & GFP_MAP_FIXED) {
			struct mnode *existing_node;
			if unlikely(!IS_ALIGNED((uintptr_t)hint, PAGESIZE)) {
				addend    = (uintptr_t)hint & PAGEMASK;
				hint      = (void *)FLOOR_ALIGN((uintptr_t)hint, PAGESIZE);
				num_bytes = CEIL_ALIGN(num_bytes + addend, PAGESIZE);
				num_pages = num_bytes >> PAGESHIFT;
			}
			result = hint;
			/* Check if the given address range is already in-use. */
			existing_node = mnode_tree_rlocate(mman_kernel.mm_mappings,
			                                   (byte_t *)result,
			                                   (byte_t *)result + num_bytes - 1);
			if (existing_node != NULL) {
				/* Address range is already in use. */
				mman_lock_release(&mman_kernel);

				/* Unconditionally return MAP_INUSE. */
				if unlikely(node != NULL)
					mnode_free(node);
				if unlikely(part != NULL)
					kram_part_destroy(part);
				return MAP_INUSE;
			}
		} else {
			if unlikely(hint == NULL) {
				if (flags & GFP_LOCKED) {
					hint = MHINT_GETADDR(KERNEL_MHINT_LHEAP);
					flags |= gfp_from_mapflags(MHINT_GETMODE(KERNEL_MHINT_LHEAP));
				} else {
					hint = MHINT_GETADDR(KERNEL_MHINT_HEAP);
					flags |= gfp_from_mapflags(MHINT_GETMODE(KERNEL_MHINT_HEAP));
				}
			}
			result = mman_findunmapped(&mman_kernel, hint, num_bytes,
			                           mapfindflags_from_gfp(flags),
			                           min_alignment, min_alignment_offset);
			if unlikely(result == MAP_FAILED)
				goto err_nospace_for_mapping;
		}
		if unlikely(num_bytes == 0) {
			assert(node == NULL);
			assert(part == NULL);
			goto unlock_and_done;
		}

		/* Ensure that the resulting address range has been prepared. */
#ifdef ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE
		if unlikely(!pagedir_prepare(result, num_bytes))
			goto err_nophys_for_backing;
#endif /* ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE */

		/* Check if we may be able to extend a pre-existing node. */
		if (!(flags & GFP_MAP_NOMERGE)) {
			struct mnode *neighbor;
			neighbor = mnode_tree_locate(mman_kernel.mm_mappings,
			                             (byte_t *)result - 1);
			if (neighbor != NULL) {
				/* TODO: Try to extend `neighbor' upwards */
			}
			neighbor = mnode_tree_locate(mman_kernel.mm_mappings,
			                             (byte_t *)result + num_bytes);
			if (neighbor != NULL) {
				/* TODO: Try to extend `neighbor' downwards */
			}
		}

#define LOCAL_INIT_PART(part, flags) \
		((part)->mp_state = MPART_ST_VOID, (part)->mp_flags = (flags), (part)->mp_xflags = MPART_XF_NORMAL)
		/* Allocate the required node/part pair. */
		if (flags & GFP_MCHEAP) {
			if likely(!node) {
				union mcorepart *cp;
				cp = mcoreheap_alloc_locked_nx();
				if unlikely(!cp)
					goto err_noheap_for_corepart_and_unprepare;
				node           = &cp->mcp_node;
				node->mn_flags = MNODE_F_COREPART;
			}
			if likely(!part) {
				union mcorepart *cp;
				cp = mcoreheap_alloc_locked_nx();
				if unlikely(!cp)
					goto err_noheap_for_corepart_and_unprepare;
				part = &cp->mcp_part;
				LOCAL_INIT_PART(part, MPART_F_COREPART);
			}
		} else {
			if likely(!node) {
				node = (struct mnode *)kmalloc_nx(sizeof(struct mnode),
				                                  inner_flags | GFP_ATOMIC);
				if unlikely(!node) {
#ifdef ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE
					pagedir_unprepare(result, num_bytes);
#endif /* ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE */
					mman_lock_release(&mman_kernel);
					/* Must allocate without holding a lock to the kernel mman */
					node = (struct mnode *)LOCAL_kmalloc(sizeof(struct mnode), inner_flags);
					LOCAL_IFNX(if unlikely(!node) goto err);
					node->mn_flags = MNODE_F_NORMAL;
					if likely(!part) {
						part = (struct mpart *)LOCAL_kmalloc(sizeof(struct mpart), inner_flags);
						LOCAL_IFNX(if unlikely(!part) goto err);
						LOCAL_INIT_PART(part, MPART_F_NORMAL);
					}
					goto again_lock_mman;
				}
				node->mn_flags = MNODE_F_NORMAL;
			}
			if likely(!part) {
				part = (struct mpart *)kmalloc_nx(sizeof(struct mpart),
				                                  inner_flags | GFP_ATOMIC);
				if unlikely(!part) {
#ifdef ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE
					pagedir_unprepare(result, num_bytes);
#endif /* ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE */
					mman_lock_release(&mman_kernel);
					/* Must allocate without holding a lock to the kernel mman */
					part = (struct mpart *)LOCAL_kmalloc(sizeof(struct mpart), inner_flags);
					LOCAL_IFNX(if unlikely(!part) goto err);
					LOCAL_INIT_PART(part, MPART_F_NORMAL);
					goto again_lock_mman;
				}
				LOCAL_INIT_PART(part, MPART_F_NORMAL);
			}
		}
#undef LOCAL_INIT_PART

		/* Allocate backing physical memory of `part' */
		if likely(part->mp_state == MPART_ST_VOID) {
			/* NOTE: `MY_PAGE_MALLOC()' uses the `*_nocc' versions since we already do our own cc below.
			 *       Additionally, we're supposed  to respect  our caller's `GFP_NOCLRC',  so we're  not
			 *       supposed to do cache-clearing if that flag is set! */
#if __SIZEOF_PHYSADDR_T__ > 4
#define MY_PAGE_MALLOC(max_pages, res_pages)                                        \
			((flags & GFP_MAP_32BIT)                                                \
			 ? page_malloc_part_between_nocc(physaddr2page(__UINT32_C(0x00000000)), \
			                                 physaddr2page(__UINT32_C(0xffffffff)), \
			                                 1, max_pages, res_pages)               \
			 : page_malloc_part_nocc(1, max_pages, res_pages))
#else /* __SIZEOF_PHYSADDR_T__ > 4 */
#define MY_PAGE_MALLOC(max_pages, res_pages) \
			page_malloc_part_nocc(1, max_pages, res_pages)
#endif /* __SIZEOF_PHYSADDR_T__ <= 4 */
			part->mp_mem.mc_start = MY_PAGE_MALLOC(num_pages, &part->mp_mem.mc_size);
			if unlikely(part->mp_mem.mc_start == PHYSPAGE_INVALID)
				goto err_nophys_for_backing_and_unprepare;
			assert(part->mp_mem.mc_size != 0);
			assert(part->mp_mem.mc_size <= num_pages);
			if likely(part->mp_mem.mc_size >= num_pages) {
				part->mp_state = MPART_ST_MEM;
			} else {
				bool did_unlock = false;
				size_t missing;
				struct mchunkvec vec;
				/* Must allocate a mem-chunk-vector */
				missing  = num_pages - part->mp_mem.mc_size;
				vec.ms_v = (struct mchunk *)kmalloc_nx(2 * sizeof(struct mchunk),
				                                       inner_flags | GFP_ATOMIC);
				if unlikely(!vec.ms_v) {
					did_unlock = true;
#ifdef ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE
					pagedir_unprepare(result, num_bytes);
#endif /* ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE */
					mman_lock_release(&mman_kernel);
#ifndef LOCAL_NX
					TRY
#endif /* !LOCAL_NX */
					{
						vec.ms_v = (struct mchunk *)LOCAL_kmalloc(2 * sizeof(struct mchunk),
						                                          inner_flags);
					}
#ifdef LOCAL_NX
					if unlikely(!vec.ms_v)
#else /* LOCAL_NX */
					EXCEPT
#endif /* !LOCAL_NX */
					{
						page_ccfree(part->mp_mem.mc_start,
						            part->mp_mem.mc_size);
#ifdef LOCAL_NX
						goto err;
#else /* LOCAL_NX */
						RETHROW();
#endif /* !LOCAL_NX */
					}
				}
				vec.ms_v[0] = part->mp_mem;
				vec.ms_c    = 1;
#ifndef LOCAL_NX
				TRY
#endif /* !LOCAL_NX */
				{
					for (;;) {
						physpage_t page;
						physpagecnt_t count;
						if (((vec.ms_c + 1) * sizeof(struct mchunk)) > kmalloc_usable_size(vec.ms_v)) {
							struct mchunk *newvec;
							newvec = (struct mchunk *)krealloc_nx(vec.ms_v,
							                                      (vec.ms_c * 2) *
							                                      sizeof(struct mchunk),
							                                      inner_flags | GFP_ATOMIC);
							if unlikely(!newvec) {
								newvec = (struct mchunk *)krealloc_nx(vec.ms_v,
								                                      (vec.ms_c + 1) *
								                                      sizeof(struct mchunk),
								                                      inner_flags | GFP_ATOMIC);
								if (!newvec) {
									if (!did_unlock) {
#ifdef ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE
										pagedir_unprepare(result, num_bytes);
#endif /* ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE */
										mman_lock_release(&mman_kernel);
										did_unlock = true;
									}
									newvec = (struct mchunk *)krealloc_nx(vec.ms_v,
									                                      (vec.ms_c * 2) * sizeof(struct mchunk),
									                                      inner_flags);
									if unlikely(!newvec) {
										newvec = (struct mchunk *)LOCAL_krealloc(vec.ms_v,
										                                         (vec.ms_c + 1) *
										                                         sizeof(struct mchunk),
										                                         inner_flags);
										LOCAL_IFNX(if unlikely(!newvec) goto err_physmem);
									}
								}
							}
							vec.ms_v = newvec;
						}

						page = MY_PAGE_MALLOC(missing, &count);
						if unlikely(page == PHYSPAGE_INVALID) {
							kram_freevec(vec.ms_v, vec.ms_c);
							if (did_unlock)
								goto err_nophys_for_backing_unlocked;
							goto err_nophys_for_backing_and_unprepare;
						}
						assert(count != 0);
						assert(count <= missing);
						vec.ms_v[vec.ms_c].mc_start = page;
						vec.ms_v[vec.ms_c].mc_size  = count;
						++vec.ms_c;
						if (count >= missing)
							break;
						missing -= count;
					}
				} LOCAL_IFELSE_NX(EXCEPT, __IF0) {
LOCAL_IFNX(err_physmem:)
					kram_freevec(vec.ms_v, vec.ms_c);
					LOCAL_IFELSE_NX(RETHROW(), goto err);
				}

				/* Try to release unused memory */
				{
					struct mchunk *smvec;
					smvec = (struct mchunk *)krealloc_nx(vec.ms_v,
					                                     vec.ms_c * sizeof(struct mchunk),
					                                     inner_flags | GFP_ATOMIC);
					if likely(smvec)
						vec.ms_v = smvec;
				}

				/* Write-back the backing physical memory */
				part->mp_state  = MPART_ST_MEM_SC;
				part->mp_mem_sc = vec;
				if unlikely(did_unlock)
					goto again_lock_mman;
			} /* if unlikely(part->mp_mem.mc_size < num_pages) */
#undef MY_PAGE_MALLOC
		} /* if likely(part->mp_state == MPART_ST_VOID) */


		/* When `GFP_PREFLT' was given, directly map the new part into memory.
		 * Otherwise, set-up the node with `MNODE_F_MHINT', and store hints to
		 * the new node for all of the pages being mapped. */
		if (flags & GFP_PREFLT) {
			/* Map the part into the page directory. */
do_prefault:
			mpart_mmap_force(part, result, num_bytes, 0,
			                 PAGEDIR_PROT_READ |
			                 PAGEDIR_PROT_WRITE);
#ifdef ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE
			if (!(flags & GFP_MAP_PREPARED))
				pagedir_unprepare(result, num_bytes);
#endif /* ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE */
			pagedir_sync(result, num_bytes);

			/* Pre-initialize backing physical memory */
			if (flags & GFP_CALLOC) {
				if (part->mp_state == MPART_ST_MEM) {
					bzero_pages(result,
					            part->mp_mem.mc_start,
					            part->mp_mem.mc_size);
				} else {
					size_t i;
					byte_t *vbase = (byte_t *)result;
					assert(part->mp_state == MPART_ST_MEM_SC);
					for (i = 0; i < part->mp_mem_sc.ms_c; ++i) {
						struct mchunk chunk;
						chunk = part->mp_mem_sc.ms_v[i];
						bzero_pages(vbase, chunk.mc_start, chunk.mc_size);
						vbase += chunk.mc_size * PAGESIZE;
					}
				}
				part->mp_file = &mfile_zero;
			} else {
#ifdef CONFIG_HAVE_KERNEL_DEBUG_HEAP
				memsetl(result, DEBUGHEAP_FRESH_MEMORY, num_bytes / 4);
				part->mp_file = &mfile_dbgheap;
#else /* CONFIG_HAVE_KERNEL_DEBUG_HEAP */
				part->mp_file = &mfile_ndef;
#endif /* !CONFIG_HAVE_KERNEL_DEBUG_HEAP */
			}

			/* After prefaulting, we can simply set the block-status
			 * bitset to  NULL, thus  marking  all blocks  as  CHNG. */
			part->mp_blkst_ptr = NULL;
		} else {
			/* Allocate the block-status bitset (if we have to)
			 * Note  that if this allocation fails, then we can just pre-fault
			 * the mem-part, thus not having to re-trying the allocation after
			 * dropping our mman-lock and having to do _so_ much once again. */
			if (num_pages <= MPART_BLKST_BLOCKS_PER_WORD) {
				part->mp_flags |= MPART_F_BLKST_INL;
				part->mp_blkst_inl = MPART_BLOCK_REPEAT(MPART_BLOCK_ST_NDEF);
			} else {
				mpart_blkst_word_t *bitset;
				size_t num_words = CEILDIV(num_pages, MPART_BLKST_BLOCKS_PER_WORD);
				assert(num_words >= 2);
				bitset = (mpart_blkst_word_t *)kmalloc_nx(num_words * sizeof(mpart_blkst_word_t),
				                                          inner_flags |
				                                          GFP_ATOMIC
#if MPART_BLOCK_ST_NDEF == 0
				                                          |
				                                          GFP_CALLOC
#endif /* MPART_BLOCK_ST_NDEF == 0 */
				                                          );
				if unlikely(!bitset)
					goto do_prefault;
#if MPART_BLOCK_ST_NDEF != 0
				memset(bitset, MPART_BLOCK_REPEAT(MPART_BLOCK_ST_NDEF),
				       num_words, sizeof(mpart_blkst_word_t));
#endif /* MPART_BLOCK_ST_NDEF != 0 */
				part->mp_blkst_ptr = bitset;
			}
			if (flags & GFP_CALLOC) {
				part->mp_file = &mfile_zero;
			} else {
#ifdef CONFIG_HAVE_KERNEL_DEBUG_HEAP
				part->mp_file = &mfile_dbgheap;
#else /* CONFIG_HAVE_KERNEL_DEBUG_HEAP */
				part->mp_file = &mfile_ndef;
#endif /* !CONFIG_HAVE_KERNEL_DEBUG_HEAP */
			}

			/* To ensure atomic initialization without prefaulting, we must
			 * set-up the  new node/part  pair as  a page  directory  hint. */
			node->mn_flags |= MNODE_F_MHINT;
			pagedir_maphint(result, num_bytes, node);
#ifdef ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE
#ifdef ARCH_PAGEDIR_NEED_UNPREPARE_AFTER_MAPHINT
			if (!(flags & GFP_MAP_PREPARED))
				pagedir_unprepare(result, num_bytes);
#endif /* ARCH_PAGEDIR_NEED_UNPREPARE_AFTER_MAPHINT */
#endif /* ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE */
		}

		/* Initialize all remaining fields of our new node/part pair. */
		node->mn_flags |= MNODE_F_PWRITE | MNODE_F_PREAD | MNODE_F_SHARED |
		                  mnodeflags_from_gfp(flags);
		node->mn_minaddr      = (byte_t *)result;
		node->mn_maxaddr      = (byte_t *)result + num_bytes - 1;
		node->mn_part         = part; /* Inherit reference */
		node->mn_fspath       = NULL;
		node->mn_fsname       = NULL;
		node->mn_module       = NULL;
		node->mn_mman         = &mman_kernel;
		node->mn_partoff      = 0;
		part->mp_share.lh_first = node;
		node->mn_link.le_prev   = &part->mp_share.lh_first;
		node->mn_link.le_next   = NULL;
		LIST_ENTRY_UNBOUND_INIT(&node->mn_writable);
		part->mp_refcnt = 1;
		part->mp_flags |= MPART_F_NORMAL |
#if MNODE_F_MLOCK == MPART_F_MLOCK
		                  ((node->mn_flags & MNODE_F_MLOCK))
#else /* MNODE_F_MLOCK == MPART_F_MLOCK */
		                  ((node->mn_flags & MNODE_F_MLOCK) ? MPART_F_MLOCK : 0)
#endif /* MNODE_F_MLOCK != MPART_F_MLOCK */
		                  ;
		/*part->mp_state = ...;*/ /* Already initialized */
		/*part->mp_file  = ...;*/ /* Already initialized */
		incref(part->mp_file);
		LIST_INIT(&part->mp_copy);
		SLIST_INIT(&part->mp_lockops);
		LIST_ENTRY_UNBOUND_INIT(&part->mp_allparts);
		DBG_memset(&part->mp_changed, 0xcc, sizeof(part->mp_changed));
		part->mp_minaddr = (pos_t)(0);
		part->mp_maxaddr = (pos_t)(num_bytes - 1);
		_mpart_init_asanon(part);
		/*part->mp_blkst_ptr = ...;*/ /* Already initialized */
		/*part->mp_mem       = ...;*/ /* Already initialized */
		part->mp_meta = NULL;

		/* Insert the new node into the kernel mman. */
		mman_mappings_insert(&mman_kernel, node);
		mnode_merge(node);

unlock_and_done:
		mman_lock_release(&mman_kernel);
		/* And we're done! */
		return (byte_t *)result + addend;

#ifndef LOCAL_NX
err_nophys_for_backing_and_unprepare:
#ifdef ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE
		pagedir_unprepare(result, num_bytes);
err_nophys_for_backing:
#endif /* ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE */
		mman_lock_release(&mman_kernel);
err_nophys_for_backing_unlocked:
		if (kram_reclaim_memory(&cache_version, flags))
			goto again_lock_mman;
		THROW(E_BADALLOC_INSUFFICIENT_PHYSICAL_MEMORY,
		      num_bytes);
err_nospace_for_mapping:
		mman_lock_release(&mman_kernel);
		if (kram_reclaim_memory(&cache_version, flags))
			goto again_lock_mman;
		THROW(E_BADALLOC_INSUFFICIENT_VIRTUAL_MEMORY,
		      num_bytes);
err_noheap_for_corepart_and_unprepare:
#ifdef ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE
		pagedir_unprepare(result, num_bytes);
#endif /* ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE */
		mman_lock_release(&mman_kernel);
		if (kram_reclaim_memory(&cache_version, flags))
			goto again_lock_mman;
		THROW(E_BADALLOC_INSUFFICIENT_HEAP_MEMORY,
		      sizeof(union mcorepart));
#endif /* !LOCAL_NX */
	}
#ifndef LOCAL_NX
	EXCEPT
#endif /* !LOCAL_NX */
	{
		/* Error handling... */
#ifdef LOCAL_NX
err_nophys_for_backing_and_unprepare:
err_noheap_for_corepart_and_unprepare:
#ifdef ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE
		pagedir_unprepare(result, num_bytes);
err_nophys_for_backing:
#endif /* ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE */
err_nospace_for_mapping:
		mman_lock_release(&mman_kernel);
err_nophys_for_backing_unlocked:
		if (kram_reclaim_memory(&cache_version, flags))
			goto again_lock_mman;
err_preempt:
err:
#endif /* LOCAL_NX */
		if (node != NULL)
			mnode_free(node);
		if (part != NULL)
			kram_part_destroy(part);
		LOCAL_IFELSE_NX(RETHROW(), {
			return MAP_FAILED;
		});
	}
#ifndef LOCAL_NX
err_preempt:
	THROW(E_WOULDBLOCK_PREEMPTED);
#endif /* !LOCAL_NX */
#undef LOCAL_krealloc
#undef LOCAL_kmalloc
#undef LOCAL_IFNX
#undef LOCAL_IFELSE_NX
#undef LOCAL_THROW
}
#undef LOCAL_NX




DECL_END

#undef DEFINE_mman_map_kram
#undef DEFINE_mman_map_kram_nx
