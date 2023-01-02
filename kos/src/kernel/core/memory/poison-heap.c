/*[[[magic
local gcc_opt = options.setdefault("GCC.options", []);
if (gcc_opt.removeif([](x) -> x.startswith("-O")))
	gcc_opt.append("-Os");
]]]*/
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
#ifndef GUARD_KERNEL_SRC_MEMORY_POISON_HEAP_C
#define GUARD_KERNEL_SRC_MEMORY_POISON_HEAP_C 1

#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/poison-heap.h>

#ifdef CONFIG_HAVE_KERNEL_POISON_HEAP
#include <debugger/rt.h>
#include <kernel/except.h>
#include <kernel/heap.h>
#include <kernel/malloc.h>
#include <kernel/memory.h>
#include <kernel/mman.h>
#include <kernel/mman/mcoreheap.h>
#include <kernel/mman/mfile.h>
#include <kernel/mman/unmapped.h>
#include <kernel/paging.h>
#include <kernel/panic.h>
#include <kernel/slab.h>

#include <hybrid/align.h>
#include <hybrid/atomic.h>
#include <hybrid/minmax.h>
#include <hybrid/overflow.h>

#include <stddef.h>
#include <string.h>

/**/
#include "trace-malloc.h"


DECL_BEGIN

/* To make this stuff a bit more robust, no-op out NOTHROW annotations,
 * meaning  that everything in here is (theoretically) able to dea with
 * exceptions. */
#undef NOTHROW
#define NOTHROW /* nothing */


/* Size = *(size_t)((byte_t *)ptr - HEAP_USABLE_SIZE_OFFSET) & HEAP_USABLE_SIZE_MASK; */
#ifdef CONFIG_HAVE_KERNEL_TRACE_MALLOC
#define HEAP_USABLE_SIZE_OFFSET CONFIG_KERNEL_MALL_HEAD_SIZE
#elif HEAP_ALIGNMENT < (__SIZEOF_SIZE_T__ + 1)
#define HEAP_USABLE_SIZE_OFFSET __SIZEOF_POINTER__
#define HEAP_USABLE_SIZE_MASK   (((uintptr_t)1 << ((__SIZEOF_SIZE_T__ * 8) - 1)) - 1)
#else /* HEAP_ALIGNMENT < (__SIZEOF_SIZE_T__ + 1) */
#define HEAP_USABLE_SIZE_OFFSET HEAP_ALIGNMENT
#endif /* HEAP_ALIGNMENT >= (__SIZEOF_SIZE_T__ + 1) */


PRIVATE ATTR_COLDTEXT PAGEDIR_PAGEALIGNED void *
NOTHROW(KCALL phcore_page_alloc_nx)(PAGEDIR_PAGEALIGNED size_t num_bytes,
                                    gfp_t flags) {
#if 1
#ifdef CONFIG_HAVE_KERNEL_DEBUGGER
	static int dbg_called_phcore = 0;
	bool haslock;
#endif /* CONFIG_HAVE_KERNEL_DEBUGGER */
	void *result;
	struct mnode *node;
	struct mpart *part;
	union mcorepart *cp;
	num_bytes = CEIL_ALIGN(num_bytes, PAGESIZE);
#ifdef CONFIG_HAVE_KERNEL_DEBUGGER
	haslock = true;
#endif /* CONFIG_HAVE_KERNEL_DEBUGGER */
	if (!mman_lock_tryacquire(&mman_kernel)) {
		if (flags & GFP_ATOMIC)
			goto err;
#ifdef CONFIG_HAVE_KERNEL_DEBUGGER
		if (dbg_active) {
			/* If  the kernel mman can't be locked from within the debugger,
			 * then yielding until it can be won't do anything since there's
			 * no-one else we could possibly yield to.
			 * This is a really _bad_ situation, and one which we can only
			 * hope doesn't cause any recursive problems.
			 * However, just in case it does, we use `dbg_called_phcore' to
			 * track  recursive calls to `phcore_page_alloc_nx()' whilst in
			 * debugger-mode.
			 * Such calls should never happen in practice, but if something
			 * goes wrong and the debugger  resets itself whilst inside  of
			 * this function, then don't make  any further attempts to  get
			 * more  poison-heap  memory, since  doing  so in-and-of-itself
			 * seems to cause the kernel to panic! */
			if (dbg_called_phcore)
				return NULL;
			haslock = false;
		} else
#endif /* CONFIG_HAVE_KERNEL_DEBUGGER */
		{
			if (!mman_lock_acquire_nx(&mman_kernel))
				goto err;
		}
	}

#ifdef CONFIG_HAVE_KERNEL_DEBUGGER
	/* Keep track of recursive calls. */
	if (dbg_active)
		++dbg_called_phcore;
#endif /* CONFIG_HAVE_KERNEL_DEBUGGER */

	/* Find a suitable free location.
	 * NOTE: To aid in debugging, unconditionally disable ASLR
	 *       for  memory  allocated   from  the   poison-heap! */
	result = mman_findunmapped(&mman_kernel,
	                           MHINT_GETADDR(KERNEL_MHINT_LHEAP), num_bytes,
	                           MHINT_GETMODE(KERNEL_MHINT_LHEAP) | MAP_NOASLR);
	if unlikely(result == MAP_FAILED)
		goto err_unlock;
	cp = mcoreheap_alloc_locked_nx();
	if unlikely(!cp)
		goto err_unlock;
	node = &cp->mcp_node;
	cp = mcoreheap_alloc_locked_nx();
	if unlikely(!cp)
		goto err_unlock_node;
	part = &cp->mcp_part;
	part->mp_mem.mc_size  = num_bytes / PAGESIZE;
	part->mp_mem.mc_start = page_malloc(part->mp_mem.mc_size);
	if unlikely(part->mp_mem.mc_start == PHYSPAGE_INVALID)
		goto err_unlock_node_part;
#ifdef ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE
	if unlikely(!pagedir_prepare(result, num_bytes)) {
		page_ccfree(part->mp_mem.mc_start, part->mp_mem.mc_size);
		goto err_unlock_node_part;
	}
#endif /* ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE */
	pagedir_map(result, num_bytes, physpage2addr(part->mp_mem.mc_start),
	            PAGEDIR_PROT_READ | PAGEDIR_PROT_WRITE);
	pagedir_sync(result, num_bytes);
#ifdef ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE
	pagedir_unprepare(result, num_bytes);
#endif /* ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE */

	/* Now just put everything together for the node/part, and
	 * follow this up  by loading them  into the kernel  mman. */
	node->mn_minaddr = (byte_t *)result;
	node->mn_maxaddr = (byte_t *)result + num_bytes - 1;

	/* Poison-heap mappings should never go away, so set the `MNODE_F_KERNPART'
	 * to cause all of the normal methods of unmapping memory to instead fault. */
	node->mn_flags        = MNODE_F_PWRITE | MNODE_F_PREAD | MNODE_F_SHARED |
	                        MNODE_F_COREPART | MNODE_F_KERNPART |
	                        MNODE_F_NOSPLIT | MNODE_F_NOMERGE;
	node->mn_part         = part;
	node->mn_fspath       = NULL;
	node->mn_fsname       = NULL;
	node->mn_module       = NULL;
	node->mn_mman         = &mman_kernel;
	node->mn_partoff      = 0;
	node->mn_link.le_prev = &part->mp_share.lh_first;
	node->mn_link.le_next = NULL;
	LIST_ENTRY_UNBOUND_INIT(&node->mn_writable);

	part->mp_refcnt = 1;
	part->mp_flags  = MPART_F_NOFREE | MPART_F_COREPART |
	                  MPART_F_NOSPLIT | MPART_F_NOMERGE |
	                  MPART_F_MLOCK_FROZEN | MPART_F_MLOCK;
	part->mp_xflags = MPART_XF_NORMAL;
	part->mp_state  = MPART_ST_MEM;
	part->mp_file   = &mfile_ndef;
	ATOMIC_INC(mfile_ndef.mf_refcnt);
	part->mp_copy.lh_first     = NULL;
	part->mp_share.lh_first    = node;
	part->mp_lockops.slh_first = NULL;
	/* Technically, we should insert the part into the global list
	 * of all parts. However, in practice that would be a bad idea
	 * since parts aren't required to be apart of the global list,
	 * and not adding a part to said list reduces its connectivity
	 * to other kernel sub-systems  (thus reducing the chances  of
	 * fault recursion) */
	LIST_ENTRY_UNBOUND_INIT(&part->mp_allparts);
	part->mp_minaddr          = (pos_t)(0);
	part->mp_maxaddr          = (pos_t)(num_bytes - 1);
	part->mp_changed.sle_next = NULL; /* Technically shouldn't needed... */
	_mpart_init_asanon(part);
	part->mp_blkst_ptr = NULL;
	part->mp_meta      = NULL;

	/* Insert the new node into the kernel and release our lock to it. */
	mman_mappings_insert(&mman_kernel, node);

	/* Technically, we'd have to merge the  node at this point, but  since
	 * that part's kind-of optional, and since we only get here if there's
	 * something _really_ wrong with the kernel, try to keep a low profile
	 * and not make any non-mandatory calls... */
	/*mnode_merge(node);*/

#ifdef CONFIG_HAVE_KERNEL_DEBUGGER
	if (haslock)
#endif /* CONFIG_HAVE_KERNEL_DEBUGGER */
	{
		mman_lock_release(&mman_kernel);
	}

#ifdef CONFIG_HAVE_KERNEL_DEBUGGER
	/* Keep track of recursive calls. */
	if (dbg_active)
		--dbg_called_phcore;
#endif /* CONFIG_HAVE_KERNEL_DEBUGGER */

	/* Initialize resulting memory.
	 * Note that technically, we could use `page_iszero()' to skip pages
	 * that had already been zero-initialized, but that would  introduce
	 * additional dependencies, as well as the assumption that the page-
	 * is-zero  database doesn't contain incorrect information (which it
	 * might  if the kernel  panic'd as the  result of calloc-memory not
	 * actually being zero-initialized due to an error in said database) */
	if (flags & GFP_CALLOC)
		bzero(result, num_bytes);

	return result;
err_unlock_node_part:
	mcoreheap_free_locked(container_of(part, union mcorepart, mcp_part));
err_unlock_node:
	mcoreheap_free_locked(container_of(node, union mcorepart, mcp_node));
err_unlock:
#ifdef CONFIG_HAVE_KERNEL_DEBUGGER
	if (haslock)
#endif /* CONFIG_HAVE_KERNEL_DEBUGGER */
	{
		mman_lock_release(&mman_kernel);
	}
#ifdef CONFIG_HAVE_KERNEL_DEBUGGER
	/* Keep track of recursive calls. */
	if (dbg_active)
		--dbg_called_phcore;
#endif /* CONFIG_HAVE_KERNEL_DEBUGGER */
err:
	return NULL;
#else
	/* NOTE: Can't use `mman_map_kram_nx()' because that one may allocate
	 *       physical  memory via a chunk-vector (which recursively calls
	 *       kmalloc_nx(), which we're not able to deal with) */
	void *result;
	result = mman_map_kram_nx(NULL, num_bytes,
	                          GFP_LOCKED | GFP_PREFLT |
	                          GFP_MCHEAP | GFP_NOCLRC |
	                          GFP_NOSWAP | flags);
	if (result == MAP_FAILED)
		result = NULL;
	return result;
#endif
}

struct ph_unused {
	struct ph_unused *pu_next; /* [0..1] Next unused heap block. */
	size_t            pu_size; /* # of unused bytes in this block. */
};

/* [lock(ATOMIC)] Linked list of unused blocks. */
PRIVATE ATTR_COLDBSS WEAK struct ph_unused *ph_unused_blocks = NULL;

PRIVATE ATTR_COLDTEXT void *
NOTHROW(KCALL phcore_unused_alloc_nx)(size_t num_bytes, gfp_t flags,
                                      size_t *__restrict palloc_bytes) {
	void *result = NULL;
	struct ph_unused *chain, **piter, *iter;
	/* Temporarily steal the chain.
	 * NOTE: This must be thread-safe, but not necessarily thread-efficient,  so
	 *       it's OK if one thread can cause this to fail for all other threads! */
	chain = ATOMIC_XCH(ph_unused_blocks, NULL);
	for (piter = &chain; (iter = *piter) != NULL; piter = &iter->pu_next) {
		if (iter->pu_size >= num_bytes) {
			size_t used_size;
			size_t unused_size;
			/* Use this entry! */
			result = iter;
			used_size   = iter->pu_size;
			unused_size = used_size - num_bytes;
			*piter = iter->pu_next; /* Unlink this chain entry. */
			if (unused_size >= sizeof(struct ph_unused)) {
				unused_size = FLOOR_ALIGN(unused_size, HEAP_ALIGNMENT);
				if (unused_size >= sizeof(struct ph_unused)) {
					used_size -= unused_size;
					result = (byte_t *)result + unused_size;
					/* Re-insert an unused part. */
					iter->pu_size = unused_size;
					/* Re-insert the truncated entry. */
					iter->pu_next = *piter;
					*piter = iter;
				}
			}
			*palloc_bytes = used_size;
			break;
		}
	}
	if (chain) {
		/* Restore the chain for further use.
		 * NOTE: `piter' points to the next-field of the last chain entry. */
		do {
			iter = ATOMIC_READ(ph_unused_blocks);
			ATOMIC_WRITE(*piter, iter);
		} while (!ATOMIC_CMPXCH(ph_unused_blocks,
		                        iter, chain));
	}
	/* Deal with calloc()-like allocations. */
	if (result && (flags & GFP_CALLOC))
		bzero(result, *palloc_bytes);
	return result;
}

PRIVATE ATTR_COLDTEXT void
NOTHROW(KCALL phcore_unused_append)(void *ptr, size_t num_bytes) {
	struct ph_unused *ent, *next;
	if unlikely(num_bytes < sizeof(struct ph_unused))
		return; /* Shouldn't happen. */
	ent = (struct ph_unused *)ptr;
	ent->pu_size = num_bytes;
	do {
		next = ATOMIC_READ(ph_unused_blocks);
		ATOMIC_WRITE(ent->pu_next, next);
	} while (!ATOMIC_CMPXCH(ph_unused_blocks,
	                        next, ent));
}


PRIVATE ATTR_COLDTEXT void *
NOTHROW(KCALL phcore_core_alloc_nx)(size_t num_bytes, gfp_t flags,
                                    size_t *__restrict palloc_bytes) {
	void *result;
	result = phcore_unused_alloc_nx(num_bytes, flags, palloc_bytes);
	if (!result) {
		PAGEDIR_PAGEALIGNED size_t page_bytes;
		page_bytes = CEIL_ALIGN(num_bytes, PAGESIZE);
		result = phcore_page_alloc_nx(page_bytes, flags);
		if (result) {
			size_t unused_head, real_alloc;
			real_alloc  = page_bytes;
			unused_head = real_alloc - num_bytes;
			if (unused_head >= sizeof(struct ph_unused)) {
				unused_head = FLOOR_ALIGN(unused_head, HEAP_ALIGNMENT);
				if (unused_head >= sizeof(struct ph_unused)) {
					real_alloc = page_bytes - unused_head;
					/* In order to somewhat better deal with small  allocations,
					 * allow the unused head to be re-used in later allocations. */
					phcore_unused_append(result, unused_head);
					result = (byte_t *)result + unused_head;
				}
			}
			*palloc_bytes = real_alloc;
		}
	}
	return result;
}

PRIVATE ATTR_COLDTEXT void *
NOTHROW(KCALL phcore_raw_memalign_nx)(size_t min_alignment, ptrdiff_t offset,
                                      size_t num_bytes, gfp_t flags,
                                      size_t *__restrict palloc_bytes) {
	size_t alloc_bytes;
	void *result;
	offset &= (min_alignment - 1);
	if unlikely(OVERFLOW_UADD(num_bytes, min_alignment, &alloc_bytes))
		return NULL;
	result = phcore_core_alloc_nx(alloc_bytes, flags, palloc_bytes);
	if likely(result) {
		result = (void *)(CEIL_ALIGN((uintptr_t)result + offset,
		                             min_alignment) -
		                  offset);
	}
	return result;
}

/* Allocate  at  least  `num_bytes'  such  that
 * `IS_ALIGNED(return + offset, min_alignment)' */
PRIVATE ATTR_NOINLINE ATTR_COLDTEXT void *
NOTHROW(KCALL phcore_memalign_nx)(size_t min_alignment, ptrdiff_t offset,
                                  size_t num_bytes, gfp_t flags) {
	void *result;
	size_t alloc_bytes;
	if (min_alignment < HEAP_ALIGNMENT)
		min_alignment = HEAP_ALIGNMENT;
	num_bytes += HEAP_USABLE_SIZE_OFFSET;
	offset    += HEAP_USABLE_SIZE_OFFSET;
	result = phcore_raw_memalign_nx(min_alignment, offset, num_bytes,
	                                flags, &alloc_bytes);
	if likely(result) {
		*(size_t *)result = alloc_bytes - HEAP_USABLE_SIZE_OFFSET;
		result = (byte_t *)result + HEAP_USABLE_SIZE_OFFSET;
	}
	return result;
}

/* NOTE: This function is also be able to return correct values for heap
 *       pointers  allocated  _before_  the  poison  heap  got injected! */
PRIVATE ATTR_NOINLINE ATTR_PURE ATTR_COLDTEXT size_t
NOTHROW(KCALL phcore_usable_size)(void *ptr) {
	if (!ptr)
		return 0;
	NESTED_TRY {
#ifdef CONFIG_HAVE_KERNEL_SLAB_ALLOCATORS
		if (KERNEL_SLAB_CHECKPTR(ptr))
			return SLAB_GET(ptr)->s_size;
#endif /* CONFIG_HAVE_KERNEL_SLAB_ALLOCATORS */
		/* FIXME: Contrary  to documentation, I don't think this
		 *        works with memory allocated by trace-malloc.c! */
#ifdef HEAP_USABLE_SIZE_MASK
		return *(size_t *)((byte_t *)ptr - HEAP_USABLE_SIZE_OFFSET) & HEAP_USABLE_SIZE_MASK;
#else /* HEAP_USABLE_SIZE_MASK */
		return *(size_t *)((byte_t *)ptr - HEAP_USABLE_SIZE_OFFSET);
#endif /* !HEAP_USABLE_SIZE_MASK */
	} EXCEPT {
	}
	return 0;
}


PRIVATE ATTR_COLDTEXT void *
NOTHROW(KCALL phcore_realign_nx)(void *ptr,
                                 size_t min_alignment, ptrdiff_t offset,
                                 size_t num_bytes, gfp_t flags) {
	void *result;
	size_t old_bytes;
	old_bytes = phcore_usable_size(ptr);
	if (num_bytes <= old_bytes && ptr)
		return ptr;
	result = phcore_memalign_nx(min_alignment, offset,
	                            num_bytes, flags);
	if likely(result)
		memcpy(result, ptr, MIN(old_bytes, num_bytes));
	return result;
}

PRIVATE ATTR_COLDTEXT ATTR_RETNONNULL void *KCALL
phcore_memalign(size_t min_alignment, ptrdiff_t offset,
                size_t num_bytes, gfp_t flags) {
	void *result;
	result = phcore_memalign_nx(min_alignment, offset, num_bytes, flags);
	if unlikely(!result)
		THROW(E_BADALLOC_INSUFFICIENT_HEAP_MEMORY, num_bytes);
	return result;
}

PRIVATE ATTR_COLDTEXT ATTR_RETNONNULL void *KCALL
phcore_realign(void *ptr,
               size_t min_alignment, ptrdiff_t offset,
               size_t num_bytes, gfp_t flags) {
	void *result;
	result = phcore_realign_nx(ptr, min_alignment, offset, num_bytes, flags);
	if unlikely(!result)
		THROW(E_BADALLOC_INSUFFICIENT_HEAP_MEMORY, num_bytes);
	return result;
}




/************************************************************************/
/* EXPOSED API PROTOTYPES                                               */
/************************************************************************/
INTDEF heapptr_t KCALL ph_heap_alloc(struct heap *self, size_t num_bytes, gfp_t flags);
INTDEF heapptr_t KCALL ph_heap_align(struct heap *self, size_t min_alignment, ptrdiff_t offset, size_t num_bytes, gfp_t flags);
INTDEF heapptr_t KCALL ph_heap_realloc(struct heap *self, void *old_ptr, size_t old_bytes, size_t new_bytes, gfp_t alloc_flags, gfp_t free_flags);
INTDEF heapptr_t KCALL ph_heap_realign(struct heap *self, void *old_ptr, size_t old_bytes, size_t min_alignment, ptrdiff_t offset, size_t new_bytes, gfp_t alloc_flags, gfp_t free_flags);
INTDEF heapptr_t NOTHROW(KCALL ph_heap_alloc_nx)(struct heap *self, size_t num_bytes, gfp_t flags);
INTDEF heapptr_t NOTHROW(KCALL ph_heap_align_nx)(struct heap *self, size_t min_alignment, ptrdiff_t offset, size_t num_bytes, gfp_t flags);
INTDEF heapptr_t NOTHROW(KCALL ph_heap_realloc_nx)(struct heap *self, void *old_ptr, size_t old_bytes, size_t new_bytes, gfp_t alloc_flags, gfp_t free_flags);
INTDEF heapptr_t NOTHROW(KCALL ph_heap_realign_nx)(struct heap *self, void *old_ptr, size_t old_bytes, size_t min_alignment, ptrdiff_t offset, size_t new_bytes, gfp_t alloc_flags, gfp_t free_flags);
#ifdef POISON_HEAP_CONFIG_NEED_VOID_FUNCTIONS
INTDEF void NOTHROW(KCALL ph_heap_free)(struct heap *self, void *ptr, size_t num_bytes, gfp_t flags);
#endif /* POISON_HEAP_CONFIG_NEED_VOID_FUNCTIONS */
#ifdef POISON_HEAP_CONFIG_NEED_ZERO_FUNCTIONS
INTDEF ATTR_CONST size_t KCALL ph_heap_allat(struct heap *self, void *ptr, size_t num_bytes, gfp_t flags);
INTDEF ATTR_CONST size_t NOTHROW(KCALL ph_heap_allat_nx)(struct heap *self, void *ptr, size_t num_bytes, gfp_t flags);
INTDEF ATTR_CONST size_t NOTHROW(KCALL ph_heap_truncate)(struct heap *self, void *base, size_t old_size, size_t new_size, gfp_t free_flags);
INTDEF ATTR_CONST size_t NOTHROW(KCALL ph_heap_trim)(struct heap *self, size_t threshold);
#endif /* POISON_HEAP_CONFIG_NEED_ZERO_FUNCTIONS */
#ifdef CONFIG_HAVE_KERNEL_DEBUG_HEAP
#ifdef POISON_HEAP_CONFIG_NEED_VOID_FUNCTIONS
INTDEF void NOTHROW(KCALL ph_heap_validate)(struct heap *self);
INTDEF void NOTHROW(KCALL ph_heap_validate_all)(void);
#endif /* POISON_HEAP_CONFIG_NEED_VOID_FUNCTIONS */
#endif /* CONFIG_HAVE_KERNEL_DEBUG_HEAP */
#ifdef CONFIG_HAVE_KERNEL_SLAB_ALLOCATORS
#ifdef POISON_HEAP_CONFIG_NEED_ZERO_FUNCTIONS
#define DEFINE_SLAB_ALLOCATOR_FUNCTIONS(sz, _) \
	INTDEF ATTR_CONST void *NOTHROW(KCALL ph_slab_malloc##sz)(gfp_t flags);
SLAB_FOREACH_SIZE(DEFINE_SLAB_ALLOCATOR_FUNCTIONS, _)
#undef DEFINE_SLAB_ALLOCATOR_FUNCTIONS
#endif /* POISON_HEAP_CONFIG_NEED_ZERO_FUNCTIONS */
#define DEFINE_SLAB_ALLOCATOR_FUNCTIONS(sz, _)                           \
	INTDEF ATTR_RETNONNULL void *KCALL ph_slab_kmalloc##sz(gfp_t flags); \
	INTDEF void *NOTHROW(KCALL ph_slab_kmalloc_nx##sz)(gfp_t flags);
SLAB_FOREACH_SIZE(DEFINE_SLAB_ALLOCATOR_FUNCTIONS, _)
#undef DEFINE_SLAB_ALLOCATOR_FUNCTIONS
#endif /* CONFIG_HAVE_KERNEL_SLAB_ALLOCATORS */

INTDEF ATTR_RETNONNULL void *KCALL ph_kmalloc(size_t n_bytes, gfp_t flags);
INTDEF void *NOTHROW(KCALL ph_kmalloc_nx)(size_t n_bytes, gfp_t flags);
INTDEF ATTR_RETNONNULL void *KCALL ph_kmemalign(size_t min_alignment, size_t n_bytes, gfp_t flags);
INTDEF void *NOTHROW(KCALL ph_kmemalign_nx)(size_t min_alignment, size_t n_bytes, gfp_t flags);
INTDEF ATTR_RETNONNULL void *KCALL ph_kmemalign_offset(size_t min_alignment, ptrdiff_t offset, size_t n_bytes, gfp_t flags);
INTDEF void *NOTHROW(KCALL ph_kmemalign_offset_nx)(size_t min_alignment, ptrdiff_t offset, size_t n_bytes, gfp_t flags);
INTDEF ATTR_RETNONNULL void *KCALL ph_krealloc(void *ptr, size_t n_bytes, gfp_t flags);
INTDEF void *NOTHROW(KCALL ph_krealloc_nx)(void *ptr, size_t n_bytes, gfp_t flags);
INTDEF ATTR_RETNONNULL void *KCALL ph_krealign(void *ptr, size_t min_alignment, size_t n_bytes, gfp_t flags);
INTDEF void *NOTHROW(KCALL ph_krealign_nx)(void *ptr, size_t min_alignment, size_t n_bytes, gfp_t flags);
INTDEF ATTR_RETNONNULL void *KCALL ph_krealign_offset(void *ptr, size_t min_alignment, ptrdiff_t offset, size_t n_bytes, gfp_t flags);
INTDEF void *NOTHROW(KCALL ph_krealign_offset_nx)(void *ptr, size_t min_alignment, ptrdiff_t offset, size_t n_bytes, gfp_t flags);
INTDEF void *KCALL ph_krealloc_in_place(void *ptr, size_t n_bytes, gfp_t flags);
INTDEF size_t NOTHROW(KCALL ph_kmalloc_usable_size)(void *ptr);
#ifdef POISON_HEAP_CONFIG_NEED_VOID_FUNCTIONS
INTDEF void NOTHROW(KCALL ph_kfree)(void *ptr);
INTDEF void NOTHROW(KCALL ph_kffree)(void *ptr, gfp_t flags);
#endif /* POISON_HEAP_CONFIG_NEED_VOID_FUNCTIONS */
#ifdef CONFIG_HAVE_KERNEL_TRACE_MALLOC
INTDEF ATTR_CONST ATTR_RETNONNULL WUNUSED void *
NOTHROW(KCALL ph_kmalloc_trace_nx)(void *base, size_t num_bytes,
                                   gfp_t gfp, unsigned int tb_skip);
#ifdef POISON_HEAP_CONFIG_NEED_ZERO_FUNCTIONS
INTDEF ATTR_CONST size_t KCALL ph_kmalloc_leaks(void);
INTDEF ATTR_CONST kmalloc_leaks_t KCALL ph_kmalloc_leaks_collect(void);
INTDEF ATTR_CONST ssize_t KCALL ph_kmalloc_leaks_print(kmalloc_leaks_t leaks, __pformatprinter printer, void *arg, size_t *pnum_leaks);
INTDEF ATTR_CONST size_t KCALL ph_kmalloc_traceback(void *ptr, /*out*/ void **tb, size_t buflen, pid_t *p_alloc_roottid);
#endif /* POISON_HEAP_CONFIG_NEED_ZERO_FUNCTIONS */
#ifdef POISON_HEAP_CONFIG_NEED_VOID_FUNCTIONS
INTDEF void NOTHROW(KCALL ph_kmalloc_validate)(void);
INTDEF void NOTHROW(KCALL ph_kmalloc_leaks_release)(kmalloc_leaks_t leaks, unsigned int how);
INTDEF void NOTHROW(KCALL ph_kmalloc_untrace)(void *ptr);
INTDEF void NOTHROW(KCALL ph_kmalloc_untrace_n)(void *ptr, size_t num_bytes);
#endif /* POISON_HEAP_CONFIG_NEED_VOID_FUNCTIONS */
#endif /* !CONFIG_HAVE_KERNEL_TRACE_MALLOC */




/************************************************************************/
/* EXPOSED API IMPLEMENTATION                                           */
/************************************************************************/
INTERN ATTR_COLDTEXT heapptr_t KCALL
ph_heap_alloc(struct heap *self, size_t num_bytes, gfp_t flags) {
	return ph_heap_align(self, HEAP_ALIGNMENT, 0, num_bytes, flags);
}

INTERN ATTR_COLDTEXT heapptr_t KCALL
ph_heap_align(struct heap *UNUSED(self),
              size_t min_alignment, ptrdiff_t offset,
              size_t num_bytes, gfp_t flags) {
	void *result_ptr;
	size_t result_siz;
	result_ptr = phcore_memalign(min_alignment, offset, num_bytes, flags);
	result_siz = phcore_usable_size(result_ptr);
	return heapptr_make(result_ptr, result_siz);
}

INTERN ATTR_COLDTEXT heapptr_t KCALL
ph_heap_realloc(struct heap *self,
                void *old_ptr, size_t old_bytes,
                size_t new_bytes, gfp_t alloc_flags,
                gfp_t free_flags) {
	return ph_heap_realign(self, old_ptr, old_bytes,
	                       HEAP_ALIGNMENT, 0, new_bytes,
	                       alloc_flags, free_flags);
}

INTERN ATTR_COLDTEXT heapptr_t KCALL
ph_heap_realign(struct heap *UNUSED(self), void *old_ptr,
                size_t old_bytes, size_t min_alignment,
                ptrdiff_t offset, size_t new_bytes,
                gfp_t alloc_flags, gfp_t UNUSED(free_flags)) {
	void *result_ptr;
	size_t result_siz;
	result_ptr = phcore_realign(old_bytes ? old_ptr : NULL,
	                            min_alignment, offset,
	                            new_bytes, alloc_flags);
	result_siz = phcore_usable_size(result_ptr);
	return heapptr_make(result_ptr, result_siz);
}

INTERN ATTR_COLDTEXT heapptr_t
NOTHROW(KCALL ph_heap_alloc_nx)(struct heap *self, size_t num_bytes, gfp_t flags) {
	return ph_heap_align_nx(self, HEAP_ALIGNMENT, 0, num_bytes, flags);
}

INTERN ATTR_COLDTEXT heapptr_t
NOTHROW(KCALL ph_heap_align_nx)(struct heap *UNUSED(self), size_t min_alignment,
                                ptrdiff_t offset, size_t num_bytes, gfp_t flags) {
	void *result_ptr;
	size_t result_siz;
	result_ptr = phcore_memalign_nx(min_alignment, offset, num_bytes, flags);
	result_siz = phcore_usable_size(result_ptr);
	return heapptr_make(result_ptr, result_siz);
}

INTERN ATTR_COLDTEXT heapptr_t
NOTHROW(KCALL ph_heap_realloc_nx)(struct heap *self, void *old_ptr,
                                  size_t old_bytes, size_t new_bytes,
                                  gfp_t alloc_flags, gfp_t free_flags) {
	return ph_heap_realign_nx(self, old_ptr, old_bytes,
	                          HEAP_ALIGNMENT, 0, new_bytes,
	                          alloc_flags, free_flags);
}

INTERN ATTR_COLDTEXT heapptr_t
NOTHROW(KCALL ph_heap_realign_nx)(struct heap *UNUSED(self), void *old_ptr,
                                  size_t old_bytes, size_t min_alignment,
                                  ptrdiff_t offset, size_t new_bytes,
                                  gfp_t alloc_flags, gfp_t UNUSED(free_flags)) {
	void *result_ptr;
	size_t result_siz;
	result_ptr = phcore_realign_nx(old_bytes ? old_ptr : NULL,
	                               min_alignment, offset,
	                               new_bytes, alloc_flags);
	result_siz = phcore_usable_size(result_ptr);
	return heapptr_make(result_ptr, result_siz);
}

#ifdef POISON_HEAP_CONFIG_NEED_VOID_FUNCTIONS
INTERN ATTR_COLDTEXT void
NOTHROW(KCALL ph_heap_free)(struct heap *UNUSED(self), void *UNUSED(ptr),
                            size_t UNUSED(num_bytes), gfp_t UNUSED(flags)) {
	/* no-op */
}
#endif /* POISON_HEAP_CONFIG_NEED_VOID_FUNCTIONS */

#ifdef POISON_HEAP_CONFIG_NEED_ZERO_FUNCTIONS
INTERN ATTR_CONST ATTR_COLDTEXT size_t KCALL
ph_heap_allat(struct heap *UNUSED(self), void *UNUSED(ptr),
              size_t UNUSED(num_bytes), gfp_t UNUSED(flags)) {
	return 0;
}

INTERN ATTR_CONST ATTR_COLDTEXT size_t
NOTHROW(KCALL ph_heap_allat_nx)(struct heap *UNUSED(self), void *UNUSED(ptr),
                                size_t UNUSED(num_bytes), gfp_t UNUSED(flags)) {
	return 0;
}

INTERN ATTR_CONST ATTR_COLDTEXT size_t
NOTHROW(KCALL ph_heap_truncate)(struct heap *UNUSED(self), void *UNUSED(base),
                                size_t UNUSED(old_size), size_t UNUSED(new_size),
                                gfp_t UNUSED(free_flags)) {
	return 0;
}

INTERN ATTR_CONST ATTR_COLDTEXT size_t
NOTHROW(KCALL ph_heap_trim)(struct heap *UNUSED(self),
                            size_t UNUSED(threshold)) {
	return 0;
}
#endif /* POISON_HEAP_CONFIG_NEED_ZERO_FUNCTIONS */

#ifdef CONFIG_HAVE_KERNEL_DEBUG_HEAP
#ifdef POISON_HEAP_CONFIG_NEED_VOID_FUNCTIONS
INTERN ATTR_COLDTEXT void
NOTHROW(KCALL ph_heap_validate)(struct heap *UNUSED(self)) {
	/* no-op */
}

INTERN ATTR_COLDTEXT void
NOTHROW(KCALL ph_heap_validate_all)(void) {
	/* no-op */
}
#endif /* POISON_HEAP_CONFIG_NEED_VOID_FUNCTIONS */
#endif /* CONFIG_HAVE_KERNEL_DEBUG_HEAP */

#ifdef CONFIG_HAVE_KERNEL_SLAB_ALLOCATORS
#ifdef POISON_HEAP_CONFIG_NEED_ZERO_FUNCTIONS
#define DEFINE_SLAB_ALLOCATOR_FUNCTIONS(sz, _)               \
	INTERN ATTR_CONST ATTR_COLDTEXT void *                   \
	NOTHROW(KCALL ph_slab_malloc##sz)(gfp_t UNUSED(flags)) { \
		return NULL;                                         \
	}
SLAB_FOREACH_SIZE(DEFINE_SLAB_ALLOCATOR_FUNCTIONS, _)
#undef DEFINE_SLAB_ALLOCATOR_FUNCTIONS
#endif /* POISON_HEAP_CONFIG_NEED_ZERO_FUNCTIONS */
#define DEFINE_SLAB_ALLOCATOR_FUNCTIONS(sz, _)           \
	INTERN ATTR_COLDTEXT ATTR_RETNONNULL void *KCALL     \
	ph_slab_kmalloc##sz(gfp_t flags) {                   \
		return ph_kmalloc(sz, flags);                    \
	}                                                    \
	INTERN ATTR_COLDTEXT void *                          \
	NOTHROW(KCALL ph_slab_kmalloc_nx##sz)(gfp_t flags) { \
		return ph_kmalloc_nx(sz, flags);                 \
	}
SLAB_FOREACH_SIZE(DEFINE_SLAB_ALLOCATOR_FUNCTIONS, _)
#undef DEFINE_SLAB_ALLOCATOR_FUNCTIONS
#endif /* CONFIG_HAVE_KERNEL_SLAB_ALLOCATORS */

INTERN ATTR_COLDTEXT ATTR_RETNONNULL void *KCALL
ph_kmalloc(size_t n_bytes, gfp_t flags) {
	return phcore_memalign(HEAP_ALIGNMENT, 0, n_bytes, flags);
}

INTERN ATTR_COLDTEXT void *
NOTHROW(KCALL ph_kmalloc_nx)(size_t n_bytes, gfp_t flags) {
	return phcore_memalign_nx(HEAP_ALIGNMENT, 0, n_bytes, flags);
}

INTERN ATTR_COLDTEXT ATTR_RETNONNULL void *KCALL
ph_kmemalign(size_t min_alignment, size_t n_bytes, gfp_t flags) {
	return phcore_memalign(min_alignment, 0, n_bytes, flags);
}

INTERN ATTR_COLDTEXT void *
NOTHROW(KCALL ph_kmemalign_nx)(size_t min_alignment, size_t n_bytes, gfp_t flags) {
	return phcore_memalign_nx(min_alignment, 0, n_bytes, flags);
}

INTERN ATTR_COLDTEXT ATTR_RETNONNULL void *KCALL
ph_kmemalign_offset(size_t min_alignment, ptrdiff_t offset, size_t n_bytes, gfp_t flags) {
	return phcore_memalign(min_alignment, offset, n_bytes, flags);
}

INTERN ATTR_COLDTEXT void *
NOTHROW(KCALL ph_kmemalign_offset_nx)(size_t min_alignment, ptrdiff_t offset,
                                      size_t n_bytes, gfp_t flags) {
	return phcore_memalign_nx(min_alignment, offset, n_bytes, flags);
}

INTERN ATTR_COLDTEXT ATTR_RETNONNULL void *KCALL
ph_krealloc(void *ptr, size_t n_bytes, gfp_t flags) {
	return phcore_realign(ptr, HEAP_ALIGNMENT, 0, n_bytes, flags);
}

INTERN ATTR_COLDTEXT void *
NOTHROW(KCALL ph_krealloc_nx)(void *ptr, size_t n_bytes, gfp_t flags) {
	return phcore_realign_nx(ptr, HEAP_ALIGNMENT, 0, n_bytes, flags);
}

INTERN ATTR_COLDTEXT ATTR_RETNONNULL void *KCALL
ph_krealign(void *ptr, size_t min_alignment, size_t n_bytes, gfp_t flags) {
	return phcore_realign(ptr, min_alignment, 0, n_bytes, flags);
}

INTERN ATTR_COLDTEXT void *
NOTHROW(KCALL ph_krealign_nx)(void *ptr, size_t min_alignment,
                              size_t n_bytes, gfp_t flags) {
	return phcore_realign_nx(ptr, min_alignment, 0, n_bytes, flags);
}

INTERN ATTR_COLDTEXT ATTR_RETNONNULL void *KCALL
ph_krealign_offset(void *ptr, size_t min_alignment,
                   ptrdiff_t offset, size_t n_bytes, gfp_t flags) {
	return phcore_realign(ptr, min_alignment, offset, n_bytes, flags);
}

INTERN ATTR_COLDTEXT void *
NOTHROW(KCALL ph_krealign_offset_nx)(void *ptr, size_t min_alignment,
                                     ptrdiff_t offset, size_t n_bytes,
                                     gfp_t flags) {
	return phcore_realign_nx(ptr, min_alignment, offset, n_bytes, flags);
}

INTERN ATTR_PURE ATTR_COLDTEXT void *KCALL
ph_krealloc_in_place(void *ptr, size_t n_bytes, gfp_t UNUSED(flags)) {
	if (phcore_usable_size(ptr) >= n_bytes)
		return ptr;
	return NULL;
}

INTERN ATTR_PURE ATTR_COLDTEXT size_t
NOTHROW(KCALL ph_kmalloc_usable_size)(void *ptr) {
	return phcore_usable_size(ptr);
}

#ifdef POISON_HEAP_CONFIG_NEED_VOID_FUNCTIONS
INTERN ATTR_COLDTEXT void
NOTHROW(KCALL ph_kfree)(void *UNUSED(ptr)) {
	/* no-op */
}

INTERN ATTR_COLDTEXT void
NOTHROW(KCALL ph_kffree)(void *UNUSED(ptr), gfp_t UNUSED(flags)) {
	/* no-op */
}
#endif /* POISON_HEAP_CONFIG_NEED_VOID_FUNCTIONS */

#ifdef CONFIG_HAVE_KERNEL_TRACE_MALLOC
INTERN ATTR_CONST ATTR_RETNONNULL WUNUSED void *
NOTHROW(KCALL ph_kmalloc_trace_nx)(void *base, size_t UNUSED(num_bytes),
                                   gfp_t UNUSED(gfp), unsigned int UNUSED(tb_skip)) {
	return base;
}

#ifdef POISON_HEAP_CONFIG_NEED_ZERO_FUNCTIONS
INTERN ATTR_COLDTEXT ATTR_CONST size_t KCALL
ph_kmalloc_leaks(void) {
	return 0;
}

INTERN ATTR_COLDTEXT ATTR_CONST kmalloc_leaks_t KCALL
ph_kmalloc_leaks_collect(void) {
	return NULL;
}

INTERN ATTR_COLDTEXT ATTR_CONST ssize_t KCALL
ph_kmalloc_leaks_print(kmalloc_leaks_t UNUSED(leaks),
                       __pformatprinter UNUSED(printer),
                       void *UNUSED(arg),
                       size_t *UNUSED(pnum_leaks)) {
	return 0;
}

INTERN NOBLOCK ATTR_COLDTEXT ATTR_CONST size_t
NOTHROW(KCALL ph_kmalloc_leaks_count)(kmalloc_leaks_t UNUSED(leaks)) {
	return 0;
}

INTERN ATTR_COLDTEXT ATTR_CONST size_t KCALL
ph_kmalloc_traceback(void *UNUSED(ptr),
                     /*out*/ void **UNUSED(tb),
                     size_t UNUSED(buflen),
                     pid_t *UNUSED(p_alloc_roottid)) {
	return 0;
}

INTERN NOBLOCK ATTR_CONST memleak_t
NOTHROW(FCALL ph_memleak_next)(kmalloc_leaks_t UNUSED(leaks), memleak_t UNUSED(prev)) {
	return NULL;
}

DEFINE_INTERN_ALIAS(ph_memleak_getattr, ph_memleak_next);
#endif /* POISON_HEAP_CONFIG_NEED_ZERO_FUNCTIONS */

#ifdef POISON_HEAP_CONFIG_NEED_VOID_FUNCTIONS
INTERN ATTR_COLDTEXT void
NOTHROW(KCALL ph_kmalloc_validate)(void) {
	/* no-op */
}

INTERN ATTR_COLDTEXT void
NOTHROW(KCALL ph_kmalloc_leaks_release)(kmalloc_leaks_t UNUSED(leaks),
                                        unsigned int UNUSED(how)) {
	/* no-op */
}

INTERN ATTR_COLDTEXT void
NOTHROW(KCALL ph_kmalloc_untrace)(void *UNUSED(ptr)) {
	/* no-op */
}

INTERN ATTR_COLDTEXT void
NOTHROW(KCALL ph_kmalloc_untrace_n)(void *UNUSED(ptr), size_t UNUSED(num_bytes)) {
	/* no-op */
}
#endif /* POISON_HEAP_CONFIG_NEED_VOID_FUNCTIONS */
#endif /* !CONFIG_HAVE_KERNEL_TRACE_MALLOC */


DECL_END
#endif /* CONFIG_HAVE_KERNEL_POISON_HEAP */

#endif /* !GUARD_KERNEL_SRC_MEMORY_POISON_HEAP_C */
