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
#ifdef __INTELLISENSE__
#include "mm-kram-map.c"
#define DEFINE_mmap_map_kram
//#define DEFINE_mmap_map_kram_nx
#endif /* __INTELLISENSE__ */

#include <kernel/heap.h>
#include <kernel/malloc.h>
#include <kernel/mman.h>
#include <kernel/mman/mcoreheap.h>
#include <kernel/mman/mm-flags.h>
#include <kernel/mman/mm-kram.h>
#include <kernel/mman/mm-unmapped.h>
#include <kernel/mman/mnode.h>
#include <kernel/mman/mpart-blkst.h>
#include <kernel/mman/mpart.h>
#include <kernel/paging.h>
#include <kernel/panic.h>

#include <hybrid/align.h>
#include <hybrid/atomic.h>

#include <kos/except.h>

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

DECL_BEGIN

#ifdef DEFINE_mmap_map_kram
/* @param: flags: Set of:
 *   - GFP_LOCKED:       Normal behavior
 *   - GFP_PREFLT:       Prefault everything
 *   - GFP_CALLOC:       Allocate from `mfile_zero' instead of `mfile_ndef'
 *   - GFP_ATOMIC:       Don't block when waiting to acquire any sort of lock.
 *   - GFP_NOMMAP:       Unconditionally throw `E_WOULDBLOCK_PREEMPTED'
 *   - GFP_VCBASE:       Allocate the mnode and mpart using `mcoreheap_alloc_locked_nx()'.
 *                       This also causes the `MNODE_F_COREPART' / `MPART_F_COREPART'
 *                       flags to be set for each resp. This flag is used internally
 *                       to resolve the dependency loop between this function needing
 *                       to call kmalloc() and kmalloc() needing to call this function.
 *   - GFP_MAP_32BIT:    Allocate 32-bit physical memory addresses. This flag
 *                       must be combined with `MAP_POPULATE', and should also
 *                       be combined with `GFP_LOCKED' to prevent the backing
 *                       physical memory from being altered.
 *   - GFP_MAP_PREPARED: Ensure that all mapped pages are prepared, and left as such
 *   - GFP_MAP_BELOW:    s.a. `MAP_GROWSDOWN'
 *   - GFP_MAP_ABOVE:    s.a. `MAP_GROWSUP'
 *   - GFP_MAP_NOASLR:   s.a. `MAP_NOASLR'
 *   - GFP_NOCLRC:       Don't call `system_clearcaches()' to try to free up memory
 *   - GFP_NOSWAP:       Don't move memory to swap to free up memory
 *   - Other flags are silently ignored, but will be forwarded onto
 *     other calls to kmalloc() that may need to be made internally.
 * Returned memory will be initialized as:
 *   - GFP_CALLOC: All zero-initialized
 *   - else:       #ifdef  CONFIG_DEBUG_HEAP: DEBUGHEAP_FRESH_MEMORY
 *                 #ifndef CONFIG_DEBUG_HEAP: Undefined */
PUBLIC NOBLOCK_IF(flags &GFP_ATOMIC) PAGEDIR_PAGEALIGNED void *FCALL
mmap_map_kram(PAGEDIR_PAGEALIGNED void *hint,
              PAGEDIR_PAGEALIGNED size_t num_bytes,
              gfp_t flags, size_t min_alignment)
THROWS(E_BADALLOC, E_WOULDBLOCK)
#elif defined(DEFINE_mmap_map_kram_nx)
/* Non-throwing version of `mmap_map_kram()'. Returns `MAP_FAILED' on error. */
PUBLIC NOBLOCK_IF(flags &GFP_ATOMIC) PAGEDIR_PAGEALIGNED void *NOTHROW(FCALL mmap_map_kram_nx)(PAGEDIR_PAGEALIGNED void *hint,
                                                                                               PAGEDIR_PAGEALIGNED size_t num_bytes,
                                                                                               gfp_t flags, size_t min_alignment)
#define LOCAL_NX
#endif /* ... */
{
#ifdef LOCAL_NX
#define LOCAL_krealloc                       krealloc_nx
#define LOCAL_kmalloc                        kmalloc_nx
#define LOCAL_IFX(...)                       /* nothing */
#define LOCAL_IFNX(...)                      __VA_ARGS__
#define LOCAL_IFELSE_NX(without_nx, with_nx) with_nx
#define LOCAL_THROW(...)                     goto err
#else /* LOCAL_NX */
#define LOCAL_krealloc                       krealloc
#define LOCAL_kmalloc                        kmalloc
#define LOCAL_IFX(...)                       __VA_ARGS__
#define LOCAL_IFNX(...)                      /* nothing */
#define LOCAL_IFELSE_NX(without_nx, with_nx) without_nx
#define LOCAL_THROW                          THROW
#endif /* !LOCAL_NX */
	uintptr_t cache_version = 0;
	void *result;
	struct mnode *node = NULL;
	struct mpart *part = NULL;
	gfp_t inner_flags;
	size_t num_pages;

	/* Check if we're allowed to map more memory. */
	if unlikely(flags & GFP_NOMMAP)
		goto err_preempt;

	/* These are the flags that will be used for dynamic
	 * allocations made within this function:
	 *  - GFP_LOCKED: All components must be locked, since we're
	 *                allocating stuff such as mem-nodes and mem-parts!
	 *  - GFP_PREFLT: Slightly improve through-put for locked memory
	 *  - GFP_VCBASE: If we end up calling ourself recursively, don't
	 *                allocate mem-nodes/parts using kmalloc(), but use
	 *                the mcoreheap system instead, thus resolving the
	 *                dependency loop between us calling kmalloc, and
	 *                kmalloc calling us.
	 *  - GFP_NOOVER: Don't over-allocate. This is required so that a
	 *                recursive call with the `GFP_VCBASE' flag set won't
	 *                try to allocate more memory than the ceil-aligned
	 *                size of the requested data-blob.
	 *                This is required to ensure that a truly recursive
	 *                call with the `GFP_VCBASE' should never try to
	 *                allocate more than a single page, thus guarantying
	 *                that we'll never be needing to make use of further
	 *                dynamic memory allocations during a recursive call.
	 *                Otherwise, we may need to allocate additional heap
	 *                memory for use by a block-status-bitset, or a mem-
	 *                chunk-vector.
	 *
	 * Clear the following flags:
	 *  - GFP_CALLOC: Not needed.
	 *  - GFP_MAP_*:  Don't interfere with recursive mapping locations.
	 */
	inner_flags = flags;
	inner_flags |= GFP_LOCKED | GFP_PREFLT | GFP_VCBASE | GFP_NOOVER;
	inner_flags &= ~(GFP_CALLOC | GFP_MAP_32BIT | GFP_MAP_PREPARED |
	                 GFP_MAP_BELOW | GFP_MAP_ABOVE | GFP_MAP_NOASLR);
	num_pages = num_bytes >> PAGESHIFT;

again_lock_mman:
	LOCAL_IFX(TRY) {
		/* Acquire a lock to the kernel mman. */
		if (!mman_lock_tryacquire(&mman_kernel)) {
			if (flags & GFP_ATOMIC)
				goto err_preempt;
			LOCAL_IFELSE_NX(mman_lock_acquire(&mman_kernel), {
				if (!mman_lock_acquire_nx(&mman_kernel))
					goto err;
			});
		}

		/* Figure out where the mapping's supposed to go. */
		result = mman_findunmapped(&mman_kernel, hint, num_bytes,
		                           mapflags_from_gfp(flags),
		                           min_alignment);
		if unlikely (result == MAP_FAILED)
			goto err_nospace_for_mapping;
		if unlikely (num_bytes == 0) {
			assert(node == NULL);
			assert(part == NULL);
			goto unlock_and_done;
		}

		{
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
		((part)->mp_state = MPART_ST_VOID, (part)->mp_flags = (flags))
		/* Allocate the required node/part pair. */
		if (flags & GFP_VCBASE) {
			if likely (!node) {
				union mcorepart *cp;
				cp = mcoreheap_alloc_locked_nx();
				if unlikely (!cp)
					goto err_noheap_for_corepart;
				node           = &cp->mcp_node;
				node->mn_flags = MNODE_F_COREPART;
			}
			if likely (!part) {
				union mcorepart *cp;
				cp = mcoreheap_alloc_locked_nx();
				if unlikely (!cp)
					goto err_noheap_for_corepart;
				part = &cp->mcp_part;
				LOCAL_INIT_PART(part, MPART_F_COREPART);
			}
		} else {
			if likely (!node) {
				node = (struct mnode *)kmalloc_nx(sizeof(struct mnode),
				                                  inner_flags | GFP_ATOMIC);
				if unlikely (!node) {
					mman_lock_release(&mman_kernel);
					/* Must allocate without holding a lock to the kernel mman */
					node = (struct mnode *)LOCAL_kmalloc(sizeof(struct mnode), inner_flags);
					LOCAL_IFNX(if unlikely (!node) goto err);
					node->mn_flags = MNODE_F_NORMAL;
					if likely (!part) {
						part = (struct mpart *)LOCAL_kmalloc(sizeof(struct mpart), inner_flags);
						LOCAL_IFNX(if unlikely (!part) goto err);
						LOCAL_INIT_PART(part, MPART_F_NORMAL);
					}
					goto again_lock_mman;
				}
				node->mn_flags = MNODE_F_NORMAL;
			}
			if likely (!part) {
				part = (struct mpart *)kmalloc_nx(sizeof(struct mpart),
				                                  inner_flags | GFP_ATOMIC);
				if unlikely (!part) {
					mman_lock_release(&mman_kernel);
					/* Must allocate without holding a lock to the kernel mman */
					part = (struct mpart *)LOCAL_kmalloc(sizeof(struct mpart), inner_flags);
					LOCAL_IFNX(if unlikely (!part) goto err);
					LOCAL_INIT_PART(part, MPART_F_NORMAL);
					goto again_lock_mman;
				}
				LOCAL_INIT_PART(part, MPART_F_NORMAL);
			}
		}
#undef LOCAL_INIT_PART

		/* Allocate backing physical memory of `part' */
		if likely(part->mp_state == MPART_ST_VOID) {
#if __SIZEOF_PHYSADDR_T__ > 4
#define MY_PAGE_MALLOC(max_pages, res_pages)                                   \
			((flags & GFP_MAP_32BIT)                                           \
			 ? page_malloc_part(1, max_pages, res_pages)                       \
			 : page_malloc_part_between(physaddr2page(__UINT32_C(0x00000000)), \
			                            physaddr2page(__UINT32_C(0xffffffff)), \
			                            1, max_pages, res_pages))
#else /* __SIZEOF_PHYSADDR_T__ > 4 */
#define MY_PAGE_MALLOC(max_pages, res_pages) \
			page_malloc_part(1, max_pages, res_pages)
#endif /* __SIZEOF_PHYSADDR_T__ <= 4 */
			part->mp_state        = MPART_ST_MEM;
			part->mp_mem.mc_start = MY_PAGE_MALLOC(num_pages, &part->mp_mem.mc_size);
			if unlikely(part->mp_mem.mc_start == PHYSPAGE_INVALID)
				goto err_nophys_for_backing;
			assert(part->mp_mem.mc_size != 0);
			assert(part->mp_mem.mc_size <= num_pages);
			if unlikely(part->mp_mem.mc_size < num_pages) {
				bool did_unlock = false;
				size_t missing;
				struct mchunkvec vec;
				/* Must allocate a mem-chunk-vector */
				missing  = num_pages - part->mp_mem.mc_size;
				vec.ms_v = (struct mchunk *)kmalloc_nx(2 * sizeof(struct mchunk),
				                                       inner_flags | GFP_ATOMIC);
				if unlikely(!vec.ms_v) {
					did_unlock = true;
					mman_lock_release(&mman_kernel);
					vec.ms_v = (struct mchunk *)LOCAL_kmalloc(2 * sizeof(struct mchunk),
					                                          inner_flags);
					LOCAL_IFNX(if unlikely(!vec.ms_v) goto err);
				}
				vec.ms_v[0] = part->mp_mem;
				vec.ms_c    = 1;
				LOCAL_IFX(TRY) {
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
							goto err_nophys_for_backing;
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
			                 PAGEDIR_MAP_FREAD |
			                 PAGEDIR_MAP_FWRITE);
#ifdef ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE
			if (!(flags & GFP_MAP_PREPARED))
				pagedir_unprepare_map(result, num_bytes);
#endif /* ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE */

			/* Pre-initialize backing physical memory */
			if (flags & GFP_CALLOC) {
				part->mp_file = &mfile_zero;
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
			} else {
#ifdef CONFIG_DEBUG_HEAP
				part->mp_file = &mfile_dbgheap;
				mempatl(result, DEBUGHEAP_FRESH_MEMORY, num_bytes);
#else  /* CONFIG_DEBUG_HEAP */
			part->mp_file = &mfile_ndef;
#endif /* !CONFIG_DEBUG_HEAP */
			}
		} else {
			/* Allocate the block-status bitset (if we have to)
			 * Note that if this allocation fails, then we can just pre-fault
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
#ifdef CONFIG_DEBUG_HEAP
				part->mp_file = &mfile_dbgheap;
#else  /* CONFIG_DEBUG_HEAP */
			part->mp_file = &mfile_ndef;
#endif /* !CONFIG_DEBUG_HEAP */
			}
			/* To ensure atomic initialization without prefaulting, we must
			 * set-up the new node/part pair as a page directory hint. */
			node->mn_flags |= MNODE_F_MHINT;
			pagedir_maphint(result, num_bytes, node);
#ifdef ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE
#ifdef ARCH_PAGEDIR_NEED_UNPREPARE_AFTER_MAPHINT
			if (!(flags & GFP_MAP_PREPARED))
				pagedir_unprepare_map(result, num_bytes);
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
		node->mn_mman         = &mman_kernel;
		node->mn_partoff      = 0;
		node->mn_link.le_prev = &part->mp_share.lh_first;
		node->mn_link.le_next = NULL;
		LIST_ENTRY_UNBOUND_INIT(node, mn_writable);
		part->mp_refcnt = 1;
		part->mp_flags |= MPART_F_NORMAL |
#if MNODE_F_MLOCK == MPART_F_MLOCK
		                  ((node->mn_flags & MNODE_F_MLOCK)) |
#else  /* MNODE_F_MLOCK == MPART_F_MLOCK */
	                  ((node->mn_flags & MNODE_F_MLOCK) ? MPART_F_MLOCK : 0) |
#endif /* MNODE_F_MLOCK != MPART_F_MLOCK */
		                  MPART_F_NO_GLOBAL_REF | MPART_F_CHANGED;
		/*part->mp_state = ...;*/ /* Already initialized */
		/*part->mp_file  = ...;*/ /* Already initialized */
		incref(part->mp_file);
		LIST_INIT(&part->mp_copy);
		part->mp_share.lh_first = node;
		SLIST_INIT(&part->mp_lockops);
		LIST_ENTRY_UNBOUND_INIT(part, mp_allparts);
		DBG_memset(&part->mp_changed, 0xcc, sizeof(part->mp_changed));
		part->mp_minaddr = (pos_t)(0);
		part->mp_maxaddr = (pos_t)(num_bytes - 1);
		DBG_memset(&part->mp_filent, 0xcc, sizeof(part->mp_filent));
		/*part->mp_blkst_ptr = ...;*/ /* Already initialized */
		/*part->mp_mem       = ...;*/ /* Already initialized */
		part->mp_meta = NULL;

		/* Insert the new node into the kernel mman. */
		mnode_tree_insert(&mman_kernel.mm_mappings, node);

unlock_and_done:
		mman_lock_release(&mman_kernel);
		/* And we're done! */
		return result;

#ifndef LOCAL_NX
err_nophys_for_backing:
		mman_lock_release(&mman_kernel);
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
err_noheap_for_corepart:
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
err_nophys_for_backing:
err_nospace_for_mapping:
err_noheap_for_corepart:
		mman_lock_release(&mman_kernel);
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
#undef LOCAL_IFX
#undef LOCAL_IFNX
#undef LOCAL_IFELSE_NX
#undef LOCAL_THROW
}
#undef LOCAL_NX




DECL_END

#undef DEFINE_mmap_map_kram
#undef DEFINE_mmap_map_kram_nx
