/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifdef __INTELLISENSE__
#include "heap.c"
#define DEFINE_HEAP_NX
#endif /* __INTELLISENSE__ */

#include <kernel/driver.h>
#include <kernel/rand.h>

#include <inttypes.h>

#ifdef DEFINE_HEAP_NX
#define LOCAL_IF_NX_ELSE(if_nx, if_x) if_nx
#define LOCAL_NOTHROW                 NOTHROW
#define LOCAL_core_page_alloc         core_page_alloc_nx
#define LOCAL_mman_map_kram           mman_map_kram_nx
#define LOCAL_heap_alloc_untraced     heap_alloc_untraced_nx
#define LOCAL_heap_acquirelock        heap_acquirelock_nx
#define LOCAL_heap_allat_partial      heap_allat_partial_nx
#define LOCAL_heap_allat_untraced     heap_allat_untraced_nx
#define LOCAL_heap_align_untraced     heap_align_untraced_nx
#define LOCAL_heap_realloc_untraced   heap_realloc_untraced_nx
#define LOCAL_heap_realign_untraced   heap_realign_untraced_nx
#else /* DEFINE_HEAP_NX */
#define LOCAL_IF_NX_ELSE(if_nx, if_x) if_x
#define LOCAL_NOTHROW(x)              x
#define LOCAL_core_page_alloc         core_page_alloc
#define LOCAL_mman_map_kram           mman_map_kram
#define LOCAL_heap_alloc_untraced     heap_alloc_untraced
#define LOCAL_heap_acquirelock        heap_acquirelock
#define LOCAL_heap_allat_partial      heap_allat_partial
#define LOCAL_heap_allat_untraced     heap_allat_untraced
#define LOCAL_heap_align_untraced     heap_align_untraced
#define LOCAL_heap_realloc_untraced   heap_realloc_untraced
#define LOCAL_heap_realign_untraced   heap_realign_untraced
#endif /* DEFINE_HEAP_NX */


DECL_BEGIN

#define LOCAL_CORE_PAGE_MALLOC_ERROR MAP_FAILED
#define LOCAL_CORE_PAGE_MALLOC_AUTO  MAP_FAILED

/* @param: mapping_target: The  target  page  number  where  memory  should  be  mapped. When
 *                         `LOCAL_CORE_PAGE_MALLOC_AUTO', automatically search for a suitable
 *                         location, otherwise _always_ return  `LOCAL_CORE_PAGE_MALLOC_AUTO'
 *                         (regardless  of  `DEFINE_HEAP_NX'), if  another kernel  VM mapping
 *                         already exists at that location.
 *                   NOTE: When this is  used to  specify a fixed  target, the  caller
 *                         should do an additional check for pre-existing nodes within
 *                         range  `mapping_target ... mapping_target + num_bytes - 1',
 *                         as this function will check for an existing mapping  within
 *                         that  range very late,  and in a way  that is not optimized
 *                         for this.
 * @param: num_bytes:      The number of bytes to allocate.
 * @param: min_alignment:  The minimum alignment required from automatic mapping_target
 *                         detection. */
PRIVATE ATTR_BLOCKLIKE_GFP(flags) NONNULL((1)) VIRT void *
LOCAL_NOTHROW(KCALL LOCAL_core_page_alloc)(struct heap *__restrict self,
                                           PAGEDIR_PAGEALIGNED void *mapping_target,
                                           PAGEDIR_PAGEALIGNED size_t num_bytes,
                                           PAGEDIR_PAGEALIGNED size_t min_alignment,
                                           gfp_t flags) {
	void *result;
	assert(!(flags & GFP_MAP_FLAGS));
	if (mapping_target == LOCAL_CORE_PAGE_MALLOC_AUTO) {
		void *mapping_hint;
		unsigned int mapping_mode;
		mapping_hint = atomic_read(&self->h_hintaddr);
		mapping_mode = atomic_read(&self->h_hintmode);
		result = LOCAL_mman_map_kram(mapping_hint,
		                             num_bytes,
		                             flags | gfp_from_mapflags(mapping_mode),
		                             min_alignment);
#ifdef DEFINE_HEAP_NX
		if (result != MAP_FAILED)
#endif /* DEFINE_HEAP_NX */
		{
			/* Update the hint for the next allocation to be adjacent to this one. */
			atomic_cmpxch(&self->h_hintaddr, mapping_hint,
			              mapping_mode & MAP_GROWSDOWN
			              ? (byte_t *)result
			              : (byte_t *)result + num_bytes);
		}
	} else {
		/* Try to map memory at the specified address. */
		result = LOCAL_mman_map_kram(mapping_target,
		                             num_bytes,
		                             flags | GFP_MAP_FIXED,
		                             min_alignment);
		if (result == MAP_INUSE) /* XXX: Do this better... */
			result = MAP_FAILED;
	}
	return result;
}



PUBLIC ATTR_BLOCKLIKE_GFP(flags) WUNUSED NONNULL((1)) heapptr_t
LOCAL_NOTHROW(KCALL LOCAL_heap_alloc_untraced)(struct heap *__restrict self,
                                               size_t num_bytes, gfp_t flags) {
	void *result_ptr;
	size_t result_siz;
	struct mfree_list *iter, *end;
	heap_validate_all_paranoid();
	TRACE(PP_STR(LOCAL_heap_alloc_untraced) "(self: %p, num_bytes: %" PRIuSIZ ", flags: %#x)\n",
	      self, num_bytes, flags);
	if unlikely(OVERFLOW_UADD(num_bytes, (size_t)(HEAP_ALIGNMENT - 1), &result_siz))
		LOCAL_IF_NX_ELSE(goto err, THROW(E_BADALLOC_INSUFFICIENT_HEAP_MEMORY, num_bytes));
	result_siz &= ~(HEAP_ALIGNMENT - 1);
	if unlikely(result_siz < HEAP_MINSIZE)
		result_siz = HEAP_MINSIZE;
	iter = &self->h_size[HEAP_BUCKET_OF(result_siz)];
	end  = COMPILER_ENDOF(self->h_size);
	HEAP_ASSERTF(iter >= self->h_size &&
	             iter < COMPILER_ENDOF(self->h_size),
	             "HEAP_BUCKET_OF(%" PRIuSIZ ") = %" PRIuSIZ "/%" PRIuSIZ,
	             result_siz, HEAP_BUCKET_OF(result_siz),
	             lengthof(self->h_size));
search_heap:
	if (!LOCAL_heap_acquirelock(self, flags))
		LOCAL_IF_NX_ELSE(goto err, THROW(E_WOULDBLOCK_PREEMPTED));
	for (; iter != end; ++iter) {
#ifdef CONFIG_HAVE_KERNEL_HEAP_TRACE_DANGLE
		size_t dangle_size;
#endif /* CONFIG_HAVE_KERNEL_HEAP_TRACE_DANGLE */
		size_t unused_size;
		struct mfree *chain;
		gfp_t chain_flags;
		/* Search this bucket. */
		chain = LIST_FIRST(iter);
		while (chain) {
			HEAP_ASSERTF(IS_ALIGNED(MFREE_SIZE(chain), HEAP_ALIGNMENT),
			             "MFREE_SIZE(chain) = %#" PRIxSIZ "\n",
			             MFREE_SIZE(chain));
			if (MFREE_SIZE(chain) >= result_siz)
				break;
			chain = LIST_NEXT(chain, mf_lsize);
		}
		if (!chain)
			continue;
		mfree_tree_removenode(&self->h_addr, chain);
		LIST_REMOVE(chain, mf_lsize);

		/* Track the potentially unused data size as dangling data. */
#ifdef CONFIG_HAVE_KERNEL_HEAP_TRACE_DANGLE
		dangle_size = MFREE_SIZE(chain) - result_siz;
		HEAP_ADD_DANGLE(self, dangle_size);
#endif /* CONFIG_HAVE_KERNEL_HEAP_TRACE_DANGLE */

		atomic_lock_release(&self->h_lock);
		HEAP_ASSERT(IS_ALIGNED(dangle_size, HEAP_ALIGNMENT));

		/* We've got the memory! */
		result_ptr  = (void *)chain;
		chain_flags = chain->mf_flags;
#ifdef CONFIG_HAVE_KERNEL_HEAP_TRACE_DANGLE
		unused_size = dangle_size;
#else /* CONFIG_HAVE_KERNEL_HEAP_TRACE_DANGLE */
		unused_size = MFREE_SIZE(chain) - result_siz;
#endif /* !CONFIG_HAVE_KERNEL_HEAP_TRACE_DANGLE */
		if (unused_size < HEAP_MINSIZE) {
			/* Remainder is too small. - Allocate it as well. */
			result_siz += unused_size;
		} else {
			void *unused_begin = (void *)((uintptr_t)chain + result_siz);
			/* Free the unused portion. */

#ifdef CONFIG_HAVE_KERNEL_HEAP_RANDOMIZE_OFFSETS
			/* Randomize allocated memory by shifting the
			 * resulting  pointer  somewhere  up  higher. */
			uintptr_t random_offset;
			random_offset = krand() % unused_size;
			random_offset &= ~(HEAP_ALIGNMENT - 1);
			if (random_offset >= HEAP_MINSIZE) {
				/* Set the new resulting pointer. */
				result_ptr = (void *)((uintptr_t)chain + random_offset);

				/* Rather than allocating `chain...+=num_bytes', instead
				 * allocate `chain+random_offset...+=num_bytes' and free
				 * `chain...+=random_offset' and
				 * `chain+random_offset+num_bytes...+=unused_size-random_offset' */
				if (chain_flags & MFREE_FZERO) {
					bzero(chain, SIZEOF_MFREE);
				}
#ifdef CONFIG_HAVE_KERNEL_DEBUG_HEAP
				else {
					mempatl(chain, DEBUGHEAP_NO_MANS_LAND, SIZEOF_MFREE);
				}
#endif /* CONFIG_HAVE_KERNEL_DEBUG_HEAP */
				/* Free unused low memory. */
				heap_free_underallocation(self, chain, random_offset,
				                          (flags & ~(GFP_CALLOC)) | chain_flags);
				unused_size -= random_offset;
				if (unused_size < HEAP_MINSIZE) {
					result_siz += unused_size;
				} else {
					unused_begin = (void *)((uintptr_t)result_ptr + result_siz);
					heap_free_overallocation(self, unused_begin, unused_size,
					                         (flags & ~(GFP_CALLOC)) | chain_flags);
				}
			} else
#endif /* CONFIG_HAVE_KERNEL_HEAP_RANDOMIZE_OFFSETS */
			{
				HEAP_ASSERT(unused_size < MFREE_SIZE(chain));
				/* Free the unused overallocation. */
				heap_free_overallocation(self, unused_begin, unused_size,
				                         (flags & ~(GFP_CALLOC)) | chain_flags);
			}
		}

		/* Now that it's been returned, the data is no longer dangling. */
#ifdef CONFIG_HAVE_KERNEL_HEAP_TRACE_DANGLE
		HEAP_SUB_DANGLE(self, dangle_size);
#endif /* CONFIG_HAVE_KERNEL_HEAP_TRACE_DANGLE */

		/* Initialize the result memory. */
		if (flags & GFP_CALLOC) {
			if (chain_flags & MFREE_FZERO) {
				bzero(result_ptr, SIZEOF_MFREE);
			} else {
				bzero(result_ptr, result_siz);
			}
		}
#ifdef CONFIG_HAVE_KERNEL_DEBUG_HEAP
		else {
			reset_heap_data((byte_t *)result_ptr,
			                DEBUGHEAP_FRESH_MEMORY,
			                result_siz);
		}
#endif /* CONFIG_HAVE_KERNEL_DEBUG_HEAP */
		HEAP_ASSERT(IS_ALIGNED((uintptr_t)result_ptr, HEAP_ALIGNMENT));
		HEAP_ASSERT(IS_ALIGNED((uintptr_t)result_siz, HEAP_ALIGNMENT));
		HEAP_ASSERT(result_siz >= HEAP_MINSIZE);
		heap_validate_all_paranoid();
		return heapptr_make(result_ptr, result_siz);
	}

	/* Check for dangling data and don't allocate new memory if enough exists. */
#ifdef CONFIG_HAVE_KERNEL_HEAP_TRACE_DANGLE
	if (atomic_read(&self->h_dangle) >= result_siz) {
		atomic_lock_release(&self->h_lock);
		/* Let some other thread about to release dangling
		 * data   do  so,  then  search  the  heap  again. */
		if (flags & GFP_ATOMIC)
			LOCAL_IF_NX_ELSE(goto err, THROW(E_WOULDBLOCK_PREEMPTED));
		task_yield();
		goto search_heap;
	}
#endif /* CONFIG_HAVE_KERNEL_HEAP_TRACE_DANGLE */

	/* NOTE: Don't track page overflow from below as dangling  data
	 *       here, so-as not to confuse allocators that are holding
	 *       a lock to `mman_kernel.mm_lock'.
	 *       Otherwise, we might end up with a soft-lock:
	 *        THREAD #1: (holding lock to `mman_kernel.mm_lock')
	 *                   kmalloc(1234);
	 *                   -> Sees dangling data from new allocation
	 *                      currently  being  made  by  THREAD  #2
	 *                   -> Doesn't allocate new pages, but tries
	 *                      to  yield to THREAD #2 and jumps back
	 *        THREAD #2: In `core_page_alloc()'; tracking dangling
	 *                   data  that  THREAD  #1  is  waiting  for.
	 *                  `core_page_alloc()' doesn't return because
	 *                   THREAD  #1   is   locking   `mman_kernel'
	 *                   THREAD #1 can't release that lock because
	 *                   it is waiting for THREAD #2.
	 *        -> Soft-lock!
	 * XXX: The above scenario can no longer happen since `mman_kernel.mm_lock'
	 *      has now been implemented as an atomic lock:
	 *       - A thread that is holding an atomic lock isn't allowed to
	 *         perform  a call to `task_yield()', meaning that THREAD#1
	 *         could  (and  does) only  allocate with  GFP_ATOMIC while
	 *         holding  a lock to  `mman_kernel.mm_lock', in which case
	 *         the yield never happens. */
	atomic_lock_release(&self->h_lock);

	/* No pre-allocated memory found. -> Allocate new memory. */
	{
		void *pageaddr;
		size_t page_bytes, unused_size;
		if unlikely(OVERFLOW_UADD(result_siz, (size_t)(PAGESIZE - 1), &page_bytes))
			LOCAL_IF_NX_ELSE(goto err, THROW(E_BADALLOC_INSUFFICIENT_HEAP_MEMORY, result_siz));
		if (!(flags & GFP_NOOVER)) {
			/* Add overhead for overallocation. */
			if unlikely(OVERFLOW_UADD(page_bytes, self->h_overalloc, &page_bytes))
				goto allocate_without_overalloc;
		}
		page_bytes &= ~PAGEMASK;
		pageaddr = core_page_alloc_nx(self,
		                              LOCAL_CORE_PAGE_MALLOC_AUTO,
		                              page_bytes,
		                              PAGESIZE,
		                              flags);
		if unlikely(pageaddr == LOCAL_CORE_PAGE_MALLOC_ERROR) {
allocate_without_overalloc:
			/* Try again without overallocation. */
			page_bytes = CEIL_ALIGN(result_siz, PAGESIZE);
			pageaddr = LOCAL_core_page_alloc(self,
			                                 LOCAL_CORE_PAGE_MALLOC_AUTO,
			                                 page_bytes,
			                                 PAGESIZE,
			                                 flags);
#ifdef DEFINE_HEAP_NX
			if unlikely(pageaddr == LOCAL_CORE_PAGE_MALLOC_ERROR)
				goto err;
#endif /* DEFINE_HEAP_NX */
		}
		PRINTK_SYSTEM_ALLOCATION("[heap] Acquire kernel heap: %p...%p\n",
		                         pageaddr,
		                         (byte_t *)pageaddr + page_bytes - 1);

		/* Got it! */
		result_ptr  = pageaddr;
		unused_size = page_bytes - result_siz;
		if unlikely(unused_size < HEAP_MINSIZE) {
			result_siz = page_bytes;
		} else {
			void *unused_begin = (void *)((uintptr_t)result_ptr + result_siz);
			/* Free unused size. */
			HEAP_ASSERT(IS_ALIGNED(unused_size, HEAP_ALIGNMENT));
			HEAP_ASSERT(IS_ALIGNED((uintptr_t)unused_begin, HEAP_ALIGNMENT));
#ifdef CONFIG_HAVE_KERNEL_DEBUG_HEAP
			if (!(flags & GFP_CALLOC)) {
				/* Be smart about  how much memory  we fill with  the debug initializer  pattern.
				 * As far as the heap validator is concerned, pages that haven't been initialized
				 * are always valid (aka. they don't have their contents checked).
				 * And knowing that `heap_free_raw()' will only modify up to the first `SIZEOF_MFREE'
				 * bytes, starting  at `unused_begin',  all we  really need  to pat  out markers  for
				 * no  man's land memory  within the last page  that still has  to be initialized for
				 * `heap_free_raw()' to function properly. */
				if (flags & GFP_PREFLT) {
					/* If memory got pre-faulted, we still have to pat _everything_,
					 * because   it's   already  been   allocated  at   this  point. */
					mempatl(unused_begin, DEBUGHEAP_NO_MANS_LAND, unused_size);
				} else {
					uintptr_t page_remainder;
					page_remainder = CEIL_ALIGN((uintptr_t)unused_begin, PAGESIZE) - (uintptr_t)unused_begin;
					if (page_remainder < SIZEOF_MFREE)
						page_remainder += PAGESIZE;
					if (page_remainder > unused_size)
						page_remainder = unused_size;
					mempatl(unused_begin, DEBUGHEAP_NO_MANS_LAND, page_remainder);
					/* Go over all remaining pages and check if they've already been
					 * initialized, because `mman_map_kram()' is allowed to prefault
					 * pages even if no request was made to prefault them. */
					if (page_remainder < unused_size) {
						byte_t *noinit_base;
						size_t noinit_size;
						noinit_base = (byte_t *)unused_begin + page_remainder;
						noinit_size = unused_size - page_remainder;
						HEAP_ASSERT(noinit_size);
						HEAP_ASSERT(IS_ALIGNED((uintptr_t)noinit_base, PAGESIZE));
						HEAP_ASSERT(IS_ALIGNED((uintptr_t)noinit_size, PAGESIZE));
						for (;;) {
							if (pagedir_iswritable(noinit_base))
								memsetl(noinit_base, DEBUGHEAP_NO_MANS_LAND, PAGESIZE / 4);
							if (noinit_size <= PAGESIZE)
								break;
							noinit_base += PAGESIZE;
							noinit_size -= PAGESIZE;
						}
					}
				}
			}
#endif /* CONFIG_HAVE_KERNEL_DEBUG_HEAP */
			/* Release the unused memory. */
			heap_free_raw(self, unused_begin, unused_size, flags);
		}
	}
	HEAP_ASSERT(IS_ALIGNED((uintptr_t)result_ptr, HEAP_ALIGNMENT));
	HEAP_ASSERT(IS_ALIGNED((uintptr_t)result_siz, HEAP_ALIGNMENT));
	HEAP_ASSERT(result_siz >= HEAP_MINSIZE);
	heap_validate_all_paranoid();
	return heapptr_make(result_ptr, result_siz);
#ifdef DEFINE_HEAP_NX
err:
	return heapptr_make(NULL, 0);
#endif /* DEFINE_HEAP_NX */
}



PRIVATE ATTR_BLOCKLIKE_GFP(flags) WUNUSED NONNULL((1)) size_t
LOCAL_NOTHROW(KCALL LOCAL_heap_allat_partial)(struct heap *__restrict self,
                                              VIRT void *__restrict ptr,
                                              gfp_t flags) {
	gfp_t slot_flags;
	size_t result;
	struct mfree *slot;
	HEAP_ASSERT(IS_ALIGNED((uintptr_t)ptr, HEAP_ALIGNMENT));
	TRACE(PP_STR(LOCAL_heap_allat_partial) "(self: %p, ptr: %p, flags: %#x)\n",
	      self, ptr, flags);
again:
	if (!LOCAL_heap_acquirelock(self, flags))
		LOCAL_IF_NX_ELSE(return 0, THROW(E_WOULDBLOCK_PREEMPTED));

	/* Check if the requested address is in cache. */
	slot = mfree_tree_locate(self->h_addr, (uintptr_t)ptr);
	if (!slot) {
		PAGEDIR_PAGEALIGNED void *pageaddr;
		atomic_lock_release(&self->h_lock);
		/* Not in cache. Try to allocate associated core memory. */
		pageaddr = (void *)((uintptr_t)ptr & ~PAGEMASK);
		pageaddr = LOCAL_core_page_alloc(self, pageaddr, PAGESIZE, PAGESIZE, flags);
		if (pageaddr == LOCAL_CORE_PAGE_MALLOC_ERROR)
			return 0;
#ifdef CONFIG_HAVE_KERNEL_DEBUG_HEAP
		/* Fill the page as no-mans-land if it's not supposed to be zero-initialized */
		if (!(flags & GFP_CALLOC))
			memsetl(pageaddr, DEBUGHEAP_NO_MANS_LAND, PAGESIZE / 4);
#endif /* CONFIG_HAVE_KERNEL_DEBUG_HEAP */
		/* Release the page to the heap and allocate again.
		 * NOTE: Set the `GFP_NOTRIM' to prevent the memory
		 *       from be unmapped immediately. */
		heap_free_raw(self, pageaddr, PAGESIZE, flags | GFP_NOTRIM);
		goto again;
	}
	HEAP_ASSERT(ptr >= (void *)MFREE_BEGIN(slot));
	if (ptr == (void *)MFREE_BEGIN(slot)) {
		/* Allocate this entire slot, then remove unused memory from the end. */
		mfree_tree_removenode(&self->h_addr, slot);
		LIST_REMOVE(slot, mf_lsize);
		atomic_lock_release(&self->h_lock);
		result     = slot->mf_size;
		slot_flags = (flags & (__GFP_HEAPMASK | GFP_INHERIT)) | slot->mf_flags;
#ifndef CONFIG_HAVE_KERNEL_DEBUG_HEAP
		if ((slot_flags & GFP_CALLOC) && (flags & GFP_CALLOC))
			bzero(slot, SIZEOF_MFREE);
#else /* !CONFIG_HAVE_KERNEL_DEBUG_HEAP */
		if (flags & GFP_CALLOC) {
			bzero(slot, SIZEOF_MFREE);
		} else {
			mempatl(slot, DEBUGHEAP_NO_MANS_LAND, SIZEOF_MFREE);
		}
#endif /* CONFIG_HAVE_KERNEL_DEBUG_HEAP */
	} else {
		size_t free_offset = (uintptr_t)ptr - MFREE_BEGIN(slot);
		HEAP_ASSERT(IS_ALIGNED(free_offset, HEAP_ALIGNMENT));
		if unlikely(free_offset < HEAP_MINSIZE) {
			/* The remaining part of the slot is too small.
			 *
			 * Ask the core if it can allocate the previous  page
			 * for us, so we can  merge this slot with that  page
			 * to get a chance of leaving a part large enough for
			 * us to return to the heap.
			 *
			 * NOTE: If the  slot doesn't  start at  a page  boundary,  we
			 *       already know that the requested part has already been
			 *       allocated (meaning  this  allocation  is  impossible) */
			PAGEDIR_PAGEALIGNED void *slot_pageaddr;
			atomic_lock_release(&self->h_lock);
			if (MFREE_BEGIN(slot) & PAGEMASK)
				return 0; /* Not page-aligned. */
			slot_pageaddr = (void *)MFREE_BEGIN(slot);
			if unlikely(slot_pageaddr == 0)
				return 0; /* Shouldn't happen: can't allocate previous page that doesn't exist. */
			slot_pageaddr = LOCAL_core_page_alloc(self, (byte_t *)slot_pageaddr - PAGESIZE, PAGESIZE, PAGESIZE, flags);
			if (slot_pageaddr == LOCAL_CORE_PAGE_MALLOC_ERROR)
				return 0; /* Failed to allocate the associated core-page. */

			/* Free the page, so-as to try and merge it with the slot from before.
			 * NOTE: Set the `GFP_NOTRIM' to prevent the memory
			 *       from be unmapped immediately. */
#ifdef CONFIG_HAVE_KERNEL_DEBUG_HEAP
			memsetl(slot_pageaddr, DEBUGHEAP_NO_MANS_LAND, PAGESIZE / 4);
#endif /* CONFIG_HAVE_KERNEL_DEBUG_HEAP */
			heap_free_raw(self,
			              slot_pageaddr,
			              PAGESIZE,
			              (flags & (__GFP_HEAPMASK | GFP_INHERIT)) | GFP_NOTRIM);
			goto again;
		}
		result = slot->mf_size - free_offset;
		if unlikely(result < HEAP_MINSIZE) {
			/* Too close to the back. - Try to allocate the next page. */
			void *slot_end = (void *)MFREE_END(slot);
			atomic_lock_release(&self->h_lock);
			if ((uintptr_t)slot_end & PAGEMASK)
				return 0; /* Not page-aligned. */
			if (LOCAL_core_page_alloc(self, slot_end, PAGESIZE, PAGESIZE, flags) == LOCAL_CORE_PAGE_MALLOC_ERROR)
				return 0; /* Failed to allocate the associated core-page. */
#ifdef CONFIG_HAVE_KERNEL_DEBUG_HEAP
			memsetl(slot_end, DEBUGHEAP_NO_MANS_LAND, PAGESIZE / 4);
#endif /* CONFIG_HAVE_KERNEL_DEBUG_HEAP */
			heap_free_raw(self, slot_end, PAGESIZE,
			              (flags & (__GFP_HEAPMASK | GFP_INHERIT)) |
			              GFP_NOTRIM);
			goto again;
		}
		mfree_tree_removenode(&self->h_addr, slot);
		LIST_REMOVE(slot, mf_lsize);

		/* Trace leading free data as dangling. */
#ifdef CONFIG_HAVE_KERNEL_HEAP_TRACE_DANGLE
		HEAP_ADD_DANGLE(self, free_offset);
#endif /* CONFIG_HAVE_KERNEL_HEAP_TRACE_DANGLE */

		atomic_lock_release(&self->h_lock);
		slot_flags = (flags & (__GFP_HEAPMASK | GFP_INHERIT)) | slot->mf_flags;
		if (slot_flags & GFP_CALLOC)
			bzero(slot, MIN(free_offset, SIZEOF_MFREE));
#ifdef CONFIG_HAVE_KERNEL_DEBUG_HEAP
		else {
			mempatl(slot, DEBUGHEAP_NO_MANS_LAND,
			        MIN(free_offset, SIZEOF_MFREE));
		}
#endif /* CONFIG_HAVE_KERNEL_DEBUG_HEAP */

		/* Release unused memory below the requested address. */
		heap_free_raw(self, (void *)MFREE_BEGIN(slot),
		              free_offset, slot_flags);
#ifdef CONFIG_HAVE_KERNEL_HEAP_TRACE_DANGLE
		HEAP_SUB_DANGLE(self, free_offset);
#endif /* CONFIG_HAVE_KERNEL_HEAP_TRACE_DANGLE */
	}

	/* Initialize newly allocated memory according to what the caller wants. */
#ifdef CONFIG_HAVE_KERNEL_DEBUG_HEAP
	if (!(flags & GFP_CALLOC))
		reset_heap_data((byte_t *)ptr, DEBUGHEAP_FRESH_MEMORY, result);
#endif /* CONFIG_HAVE_KERNEL_DEBUG_HEAP */
	if ((flags & GFP_CALLOC) && !(slot_flags & GFP_CALLOC))
		bzero(ptr, result);
	HEAP_ASSERT(result >= HEAP_MINSIZE);
	heap_validate_all_paranoid();
	return result;
}


PUBLIC ATTR_BLOCKLIKE_GFP(flags) WUNUSED NONNULL((1)) size_t
LOCAL_NOTHROW(KCALL LOCAL_heap_allat_untraced)(struct heap *__restrict self,
                                               VIRT void *__restrict ptr,
                                               size_t num_bytes, gfp_t flags) {
	size_t unused_size, alloc_size;
	size_t result = 0;
	TRACE(PP_STR(LOCAL_heap_allat_untraced) "(self: %p, ptr: %p, num_bytes: %" PRIuSIZ ", flags: %#x)\n",
	      self, ptr, num_bytes, flags);
	if unlikely(!IS_ALIGNED((uintptr_t)ptr, HEAP_ALIGNMENT))
		goto err; /* Badly aligned pointer (can't allocate anything here...) */
	if unlikely(OVERFLOW_UADD(num_bytes, (size_t)(HEAP_ALIGNMENT - 1), &alloc_size))
		LOCAL_IF_NX_ELSE(goto err, THROW(E_BADALLOC_INSUFFICIENT_HEAP_MEMORY, num_bytes));
	alloc_size &= ~(HEAP_ALIGNMENT - 1);
	if unlikely(alloc_size < HEAP_MINSIZE)
		alloc_size = HEAP_MINSIZE;

	/* Allocate memory from the given range. */
	while (result < alloc_size) {
		size_t part;
		/* Allocate the new missing part. */
		LOCAL_IF_NX_ELSE(, TRY) {
			part = LOCAL_heap_allat_partial(self,
			                                (byte_t *)ptr + result,
			                                flags);
		} LOCAL_IF_NX_ELSE(if (!part), EXCEPT) {
			if (result)
				heap_free_untraced(self, ptr, result, flags);
			LOCAL_IF_NX_ELSE(goto err, RETHROW());
		}
#ifndef DEFINE_HEAP_NX
		if unlikely(!part) {
			/* Failed to allocate the entirety of the requested range.
			 * Free what was already allocated. */
			if (result)
				heap_free_untraced(self, ptr, result, flags);
			goto err;
		}
#endif /* !DEFINE_HEAP_NX */
		result += part;
	}

	/* With everything now allocated, free what the caller didn't ask for. */
	HEAP_ASSERT(result >= alloc_size);
	unused_size = result - alloc_size;
	if (unused_size >= HEAP_MINSIZE) {
		heap_free_untraced(self,
		                   (byte_t *)ptr + alloc_size,
		                   unused_size, flags);
		result = alloc_size;
	}
	return result;
err:
	return 0;
}


PUBLIC ATTR_BLOCKLIKE_GFP(flags) WUNUSED NONNULL((1)) heapptr_t
LOCAL_NOTHROW(KCALL LOCAL_heap_align_untraced)(struct heap *__restrict self,
                                               size_t min_alignment, ptrdiff_t offset,
                                               size_t num_bytes, gfp_t flags) {
	heapptr_t result_base;
	void *result_ptr;
	size_t result_siz;
	size_t nouse_size, alloc_bytes;
	size_t heap_alloc_bytes;
	assert(min_alignment != 0);
	assertf(!(min_alignment & (min_alignment - 1)),
	        "Invalid min_alignment: %#" PRIxSIZ,
	        min_alignment);

	/* Truncate the offset, if it was a multiple of `min_alignment'
	 * HINT: This also ensures that `offset' is positive. */
	offset &= (min_alignment - 1);

	/* Forward to the regular allocator when the constraints allow it. */
	if (min_alignment <= HEAP_ALIGNMENT && !offset)
		return LOCAL_heap_alloc_untraced(self, num_bytes, flags);
	if unlikely(OVERFLOW_UADD(num_bytes, (size_t)(HEAP_ALIGNMENT - 1), &alloc_bytes))
		LOCAL_IF_NX_ELSE(goto err, THROW(E_BADALLOC_INSUFFICIENT_HEAP_MEMORY, num_bytes));
	alloc_bytes &= ~(HEAP_ALIGNMENT - 1);
	if unlikely(alloc_bytes < HEAP_MINSIZE)
		alloc_bytes = HEAP_MINSIZE;

#if 1
	{
		struct mfree_list *iter, *end;
		iter = &self->h_size[HEAP_BUCKET_OF(alloc_bytes)];
		end  = COMPILER_ENDOF(self->h_size);
		HEAP_ASSERTF(iter >= self->h_size &&
		             iter < COMPILER_ENDOF(self->h_size),
		             "HEAP_BUCKET_OF(%" PRIuSIZ ") = %" PRIuSIZ "/%" PRIuSIZ,
		             alloc_bytes, HEAP_BUCKET_OF(alloc_bytes),
		             lengthof(self->h_size));
		if (!LOCAL_heap_acquirelock(self, flags))
			LOCAL_IF_NX_ELSE(goto err, THROW(E_WOULDBLOCK_PREEMPTED));

		/* Search for  existing  free  data  that
		 * fit the required alignment and offset. */
		for (; iter != end; ++iter) {
			struct mfree *chain;
			void *hkeep, *tkeep;
			gfp_t chain_flags;
			byte_t *alignment_base;
			size_t hkeep_size, tkeep_size;
#ifdef CONFIG_HAVE_KERNEL_HEAP_TRACE_DANGLE
			size_t dangle_size;
#endif /* CONFIG_HAVE_KERNEL_HEAP_TRACE_DANGLE */

			/* Search this bucket. */
			chain = LIST_FIRST(iter);
			while (chain &&
			       (HEAP_ASSERTF(IS_ALIGNED(MFREE_SIZE(chain), HEAP_ALIGNMENT),
			                     "MFREE_SIZE(chain) = %#" PRIxSIZ,
			                     MFREE_SIZE(chain)),
			        MFREE_SIZE(chain) < alloc_bytes))
				chain = LIST_NEXT(chain, mf_lsize);
			if (!chain)
				continue;

			/* Check if this chain entry can sustain our required alignment. */
			alignment_base = (byte_t *)chain;
			alignment_base += offset;
			alignment_base += (min_alignment - 1);
			alignment_base = (byte_t *)((uintptr_t)alignment_base & ~(min_alignment - 1));
			alignment_base -= offset;
			if unlikely(alignment_base < (byte_t *)chain)
				alignment_base += min_alignment;

			/* `alignment_base' is now the effective base address which we want to use.
			 * However,  in case it doesn't match the  free-node, we must advance it to
			 * the  nearest  correctly  aligned  address  (by  adding `min_alignment').
			 * This is required to ensure that the unused portion at `chain'  continues
			 * to be large enough to  be re-freed (should we  choose to use this  node) */
			if (alignment_base != (byte_t *)chain) {
				while ((size_t)(alignment_base - (byte_t *)chain) < HEAP_MINSIZE)
					alignment_base += min_alignment;
			}

			/* Check if the node still contains enough memory for the requested allocation. */
			if ((alignment_base + alloc_bytes) > (byte_t *)MFREE_END(chain))
				continue; /* The chain entry is too small once alignment was taken into consideration. */
			mfree_tree_removenode(&self->h_addr, chain);
			LIST_REMOVE(chain, mf_lsize);

			/* Trace potentially unused data as dangling. */
#ifdef CONFIG_HAVE_KERNEL_HEAP_TRACE_DANGLE
			dangle_size = chain->mf_size - alloc_bytes;
			HEAP_ADD_DANGLE(self, dangle_size);
#endif /* CONFIG_HAVE_KERNEL_HEAP_TRACE_DANGLE */

			atomic_lock_release(&self->h_lock);
			HEAP_ASSERT(IS_ALIGNED((uintptr_t)(alignment_base + offset), min_alignment));

			/* All right! we can actually use this one! */
			result_ptr = (VIRT void *)alignment_base;
			result_siz = alloc_bytes;
			/* Figure out how much memory should be re-freed at the front and back. */
			chain_flags = chain->mf_flags;
			hkeep       = (void *)chain;
			hkeep_size  = (size_t)(alignment_base - (byte_t *)chain);
			tkeep       = (void *)((uintptr_t)result_ptr + alloc_bytes);
			tkeep_size  = (size_t)(MFREE_END(chain) - (uintptr_t)tkeep);
#ifdef CONFIG_HAVE_KERNEL_HEAP_RANDOMIZE_OFFSETS
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
					result_ptr = (byte_t *)result_ptr + random_offset;
				}
			}
#endif /* CONFIG_HAVE_KERNEL_HEAP_RANDOMIZE_OFFSETS */

			if (hkeep_size) {
				HEAP_ASSERT(hkeep_size >= HEAP_MINSIZE);

				/* Reset data of the head if we're to re-free them. */
				if (chain_flags & GFP_CALLOC)
					bzero(hkeep, SIZEOF_MFREE);
#ifdef CONFIG_HAVE_KERNEL_DEBUG_HEAP
				else {
					mempatl(hkeep, DEBUGHEAP_NO_MANS_LAND, SIZEOF_MFREE);
				}
#endif /* CONFIG_HAVE_KERNEL_DEBUG_HEAP */
				heap_free_underallocation(self,
				                          hkeep,
				                          hkeep_size,
				                          chain_flags);
			}
			if (tkeep_size < HEAP_MINSIZE) {
				/* The tail is too small (or non-existent).
				 * -> We must allocate it, too. */
				result_siz += tkeep_size;
			} else {
				/* Free the tail pointer. */
				HEAP_ASSERT((byte_t *)tkeep ==
				            (byte_t *)result_ptr + result_siz);
				heap_free_overallocation(self,
				                         tkeep,
				                         tkeep_size,
				                         (flags & ~(GFP_CALLOC)) |
				                         chain_flags);
			}

			/* Remove dangling data. */
#ifdef CONFIG_HAVE_KERNEL_HEAP_TRACE_DANGLE
			HEAP_SUB_DANGLE(self, dangle_size);
#endif /* CONFIG_HAVE_KERNEL_HEAP_TRACE_DANGLE */

			/* Initialize the resulting memory. */
			if (flags & GFP_CALLOC) {
				if (chain_flags & MFREE_FZERO) {
					bzero(result_ptr, SIZEOF_MFREE);
				} else {
					bzero(result_ptr, result_siz);
				}
			}
#ifdef CONFIG_HAVE_KERNEL_DEBUG_HEAP
			else {
				reset_heap_data((byte_t *)result_ptr,
				                DEBUGHEAP_FRESH_MEMORY,
				                result_siz);
			}
#endif /* CONFIG_HAVE_KERNEL_DEBUG_HEAP */
			HEAP_ASSERT(IS_ALIGNED((uintptr_t)result_ptr, HEAP_ALIGNMENT));
			HEAP_ASSERTF(IS_ALIGNED((uintptr_t)result_ptr + offset, min_alignment),
			             "result_ptr          = %p\n"
			             "result_ptr + offset = %p\n"
			             "offset                 = %p\n"
			             "min_alignment          = %p\n",
			             (uintptr_t)result_ptr,
			             (uintptr_t)result_ptr + offset,
			             (uintptr_t)offset,
			             (uintptr_t)min_alignment);
			HEAP_ASSERT(IS_ALIGNED((uintptr_t)result_siz, HEAP_ALIGNMENT));
			HEAP_ASSERT(result_siz >= HEAP_MINSIZE);
			heap_validate_all_paranoid();
			return heapptr_make(result_ptr, result_siz);
		}
		atomic_lock_release(&self->h_lock);
	}
#endif /* #if 1 */

	/* Fallback: Use overallocation to assert alignment. */

	/* Must overallocate by at least `HEAP_MINSIZE',
	 * so  we can _always_ free unused lower memory. */
	if unlikely(OVERFLOW_UADD(alloc_bytes, min_alignment, &heap_alloc_bytes))
		LOCAL_IF_NX_ELSE(goto err, THROW(E_BADALLOC_INSUFFICIENT_HEAP_MEMORY, MAX(alloc_bytes, min_alignment)));
	if unlikely(OVERFLOW_UADD(heap_alloc_bytes, HEAP_MINSIZE, &heap_alloc_bytes))
		LOCAL_IF_NX_ELSE(goto err, THROW(E_BADALLOC_INSUFFICIENT_HEAP_MEMORY, heap_alloc_bytes));
	result_base = LOCAL_heap_alloc_untraced(self, heap_alloc_bytes, flags);
	HEAP_ASSERT(heapptr_getsiz(result_base) >= heap_alloc_bytes);
	result_ptr = (void *)(CEIL_ALIGN((uintptr_t)heapptr_getptr(result_base) +
	                                 HEAP_MINSIZE + offset,
	                                 min_alignment) -
	                      offset);
	HEAP_ASSERT((byte_t *)result_ptr + alloc_bytes <=
	            (byte_t *)heapptr_getptr(result_base) + heapptr_getsiz(result_base));
	nouse_size = (byte_t *)result_ptr - (byte_t *)heapptr_getptr(result_base);
	HEAP_ASSERT(nouse_size + alloc_bytes <= heapptr_getsiz(result_base));
	HEAP_ASSERTF(nouse_size >= HEAP_MINSIZE, "nouse_size = %" PRIuSIZ, nouse_size);
	HEAP_ASSERTF(IS_ALIGNED(nouse_size, HEAP_ALIGNMENT),
	             "Invalid offset (%" PRIdSIZ ") / alignment (%" PRIuSIZ ")\n"
	             "nouse_size = %" PRIuSIZ,
	             offset, min_alignment, nouse_size);

	/* Release lower memory (This _MUST_ work because we've overallocated by `HEAP_MINSIZE'). */
	heap_free_untraced(self, heapptr_getptr(result_base), nouse_size, flags);
	result_siz = heapptr_getsiz(result_base) - nouse_size;

	/* Try to release upper memory. */
	nouse_size = result_siz - alloc_bytes;
	if (nouse_size >= HEAP_MINSIZE) {
		heap_free_untraced(self,
		                   (void *)((uintptr_t)result_ptr + alloc_bytes),
		                   nouse_size, flags);
		result_siz -= nouse_size;
	}
	HEAP_ASSERT(result_siz >= alloc_bytes);
	HEAP_ASSERT(result_siz >= HEAP_MINSIZE);
	HEAP_ASSERT(IS_ALIGNED((uintptr_t)result_ptr + offset, min_alignment));
	HEAP_ASSERT(IS_ALIGNED((uintptr_t)result_siz, HEAP_ALIGNMENT));
	heap_validate_all_paranoid();
	return heapptr_make(result_ptr, result_siz);
#ifdef DEFINE_HEAP_NX
err:
	return heapptr_make(NULL, 0);
#endif /* DEFINE_HEAP_NX */
}


PUBLIC ATTR_BLOCKLIKE_GFP(alloc_flags) WUNUSED NONNULL((1)) heapptr_t
LOCAL_NOTHROW(KCALL LOCAL_heap_realloc_untraced)(struct heap *__restrict self,
                                                 VIRT void *old_ptr, size_t old_bytes,
                                                 size_t new_bytes, gfp_t alloc_flags,
                                                 gfp_t free_flags) {
	size_t missing_bytes;
	assert(IS_ALIGNED(old_bytes, HEAP_ALIGNMENT));
	assert(!old_bytes || IS_ALIGNED((uintptr_t)old_ptr, HEAP_ALIGNMENT));
	assert(!old_bytes || old_bytes >= HEAP_MINSIZE);
	if (old_bytes == 0) {
		if (alloc_flags & GFP_NOMOVE)
			goto err;
		/* Special case: initial allocation */
		return LOCAL_heap_alloc_untraced(self, new_bytes, alloc_flags);
	}
	if unlikely(OVERFLOW_UADD(new_bytes, (size_t)(HEAP_ALIGNMENT - 1), &new_bytes))
		LOCAL_IF_NX_ELSE(goto err, THROW(E_BADALLOC_INSUFFICIENT_HEAP_MEMORY, new_bytes - (HEAP_ALIGNMENT - 1)));
	new_bytes &= ~(HEAP_ALIGNMENT - 1);
	if unlikely(new_bytes < HEAP_MINSIZE)
		new_bytes = HEAP_MINSIZE;
	if (new_bytes <= old_bytes) {
		size_t free_bytes;
		/* Free trailing memory. */
		free_bytes = old_bytes - new_bytes;
		if (free_bytes >= HEAP_MINSIZE) {
			heap_free_untraced(self, (void *)((uintptr_t)old_ptr + new_bytes),
			                   free_bytes, free_flags);
			old_bytes = new_bytes;
		}
		return heapptr_make(old_ptr, old_bytes);
	}
	missing_bytes = new_bytes - old_bytes;
	missing_bytes = LOCAL_heap_allat_untraced(self, (void *)((uintptr_t)old_ptr + old_bytes),
	                                          missing_bytes, alloc_flags);
	if (missing_bytes) {
		/* Managed to extend the data block. */
		return heapptr_make(old_ptr, old_bytes + missing_bytes);
	}
	if (alloc_flags & GFP_NOMOVE)
		goto err;
	{
		heapptr_t result;
		/* Must allocate an entirely new data block and copy memory to it. */
		result = LOCAL_heap_alloc_untraced(self, new_bytes, alloc_flags);
		LOCAL_IF_NX_ELSE(if (heapptr_getsiz(result) == 0) goto err;, )
		memcpy(heapptr_getptr(result), old_ptr, old_bytes);
		/* Free the old data block. */
		heap_free_untraced(self, old_ptr, old_bytes,
		                   free_flags & ~GFP_CALLOC);
		return result;
	}
err:
	return heapptr_make(NULL, 0);
}

PUBLIC ATTR_BLOCKLIKE_GFP(alloc_flags) WUNUSED NONNULL((1)) heapptr_t
LOCAL_NOTHROW(KCALL LOCAL_heap_realign_untraced)(struct heap *__restrict self,
                                                 VIRT void *old_ptr, size_t old_bytes,
                                                 size_t min_alignment, ptrdiff_t offset,
                                                 size_t new_bytes, gfp_t alloc_flags,
                                                 gfp_t free_flags) {
	size_t missing_bytes;
	assert(IS_ALIGNED(old_bytes, HEAP_ALIGNMENT));
	assert(!old_bytes || IS_ALIGNED((uintptr_t)old_ptr, HEAP_ALIGNMENT));
	assert(!old_bytes || old_bytes >= HEAP_MINSIZE);
	if (old_bytes == 0) {
		if (alloc_flags & GFP_NOMOVE)
			goto err;
		/* Special case: initial allocation */
		return LOCAL_heap_align_untraced(self, min_alignment, offset, new_bytes, alloc_flags);
	}
	if unlikely(OVERFLOW_UADD(new_bytes, (size_t)(HEAP_ALIGNMENT - 1), &new_bytes))
		LOCAL_IF_NX_ELSE(goto err, THROW(E_BADALLOC_INSUFFICIENT_HEAP_MEMORY, new_bytes - (HEAP_ALIGNMENT - 1)));
	new_bytes &= ~(HEAP_ALIGNMENT - 1);
	if (new_bytes <= old_bytes) {
		size_t free_bytes;
		if unlikely(new_bytes < HEAP_MINSIZE)
			new_bytes = HEAP_MINSIZE;
		/* Free trailing memory. */
		free_bytes = old_bytes - new_bytes;
		if (free_bytes >= HEAP_MINSIZE) {
			heap_free(self, (void *)((uintptr_t)old_ptr + new_bytes),
			          free_bytes, free_flags);
			old_bytes = new_bytes;
		}
		return heapptr_make(old_ptr, old_bytes);
	}
	missing_bytes = new_bytes - old_bytes;
	missing_bytes = LOCAL_heap_allat_untraced(self, (void *)((uintptr_t)old_ptr + old_bytes),
	                                          missing_bytes, alloc_flags);
	if (missing_bytes) {
		/* Managed to extend the data block. */
		return heapptr_make(old_ptr, old_bytes + missing_bytes);
	}
	if (alloc_flags & GFP_NOMOVE)
		goto err;
	{
		heapptr_t result;

		/* Must allocate an entirely new data block and copy memory to it. */
		result = LOCAL_heap_align_untraced(self, min_alignment, offset,
		                                   new_bytes, alloc_flags);
		LOCAL_IF_NX_ELSE(if (heapptr_getsiz(result) == 0) goto err;, )
		memcpy(heapptr_getptr(result), old_ptr, old_bytes);

		/* Free the old data block. */
		heap_free_untraced(self, old_ptr, old_bytes,
		                   free_flags & ~GFP_CALLOC);
		return result;
	}
err:
	return heapptr_make(NULL, 0);
}

#undef LOCAL_CORE_PAGE_MALLOC_ERROR
#undef LOCAL_CORE_PAGE_MALLOC_AUTO

DECL_END

#undef LOCAL_NOTHROW
#undef LOCAL_IF_NX_ELSE
#undef LOCAL_core_page_alloc
#undef LOCAL_mman_map_kram
#undef LOCAL_heap_alloc_untraced
#undef LOCAL_heap_acquirelock
#undef LOCAL_heap_allat_partial
#undef LOCAL_heap_allat_untraced
#undef LOCAL_heap_align_untraced
#undef LOCAL_heap_realloc_untraced
#undef LOCAL_heap_realign_untraced

#undef DEFINE_HEAP_NX
