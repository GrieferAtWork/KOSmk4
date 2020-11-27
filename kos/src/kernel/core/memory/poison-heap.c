/*[[[magic
local gcc_opt = options.setdefault("GCC.options", []);
if (gcc_opt.removeif([](x) -> x.startswith("-O")))
	gcc_opt.append("-Os");
]]]*/
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
#ifndef GUARD_KERNEL_SRC_MEMORY_POISON_HEAP_C
#define GUARD_KERNEL_SRC_MEMORY_POISON_HEAP_C 1

#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/poison-heap.h>

#ifdef CONFIG_HAVE_POISON_HEAP
#include <kernel/except.h>
#include <kernel/heap.h>
#include <kernel/malloc.h>
#include <kernel/paging.h>
#include <kernel/panic.h>
#include <kernel/slab.h>

#include <hybrid/align.h>
#include <hybrid/atomic.h>
#include <hybrid/minmax.h>
#include <hybrid/overflow.h>

#include <string.h>

#include "corebase.h"

DECL_BEGIN

/* To make this stuff a bit more robust, no-op out NOTHROW annotations,
 * meaning that everything in here is (theoretically) able to dea with
 * exceptions. */
#undef NOTHROW
#define NOTHROW /* nothing */


/* Size = *(size_t)((byte_t *)ptr - HEAP_USABLE_SIZE_OFFSET) & HEAP_USABLE_SIZE_MASK; */
#ifdef CONFIG_TRACE_MALLOC
#ifndef CONFIG_MALL_PREFIX_SIZE
#define CONFIG_MALL_PREFIX_SIZE (__SIZEOF_SIZE_T__)
#endif /* !CONFIG_MALL_PREFIX_SIZE */
#ifndef CONFIG_MALL_HEAD_SIZE
#define CONFIG_MALL_HEAD_SIZE (HEAP_ALIGNMENT - __SIZEOF_SIZE_T__)
#endif /* !CONFIG_MALL_HEAD_SIZE */
#define HEAP_USABLE_SIZE_OFFSET (CONFIG_MALL_PREFIX_SIZE + CONFIG_MALL_HEAD_SIZE)
#elif HEAP_ALIGNMENT < (__SIZEOF_SIZE_T__ + 1)
#define HEAP_USABLE_SIZE_OFFSET __SIZEOF_POINTER__
#define HEAP_USABLE_SIZE_MASK   (((uintptr_t)1 << ((__SIZEOF_SIZE_T__ * 8) - 1)) - 1)
#else /* HEAP_ALIGNMENT < (__SIZEOF_SIZE_T__ + 1) */
#define HEAP_USABLE_SIZE_OFFSET HEAP_ALIGNMENT
#endif /* HEAP_ALIGNMENT >= (__SIZEOF_SIZE_T__ + 1) */

#define HINT_ADDR(x, y) x
#define HINT_MODE(x, y) y
#define HINT_GETADDR(x) HINT_ADDR x
#define HINT_GETMODE(x) HINT_MODE x



PRIVATE ATTR_COLDTEXT PAGEDIR_PAGEALIGNED void *
NOTHROW(KCALL phcore_page_alloc_nx)(PAGEDIR_PAGEALIGNED size_t num_bytes,
                                    gfp_t flags) {
	PAGEDIR_PAGEALIGNED void *mapping_target;
	struct vm_corepair_ptr corepair;
	physpage_t block0_addr;
	physpagecnt_t block0_size;
	corepair = vm_corepair_alloc(flags, true);
	if (!corepair.cp_node)
		return NULL;
	/* Setup the corepair. */
	corepair.cp_part->dp_refcnt = 1; /* corepair.cp_node */
	corepair.cp_node->vn_prot   = VM_PROT_READ | VM_PROT_WRITE | VM_PROT_SHARED;
	corepair.cp_node->vn_vm     = &vm_kernel;
	corepair.cp_part->dp_block  = flags & GFP_CALLOC
	                              ? &vm_datablock_anonymous_zero
	                              : &vm_datablock_anonymous;
	incref(corepair.cp_part->dp_block);
	corepair.cp_node->vn_block  = incref(corepair.cp_part->dp_block);
	corepair.cp_node->vn_fspath = NULL;
	corepair.cp_node->vn_fsname = NULL;
	corepair.cp_node->vn_flags |= VM_NODE_FLAG_PREPARED;
	corepair.cp_node->vn_part          = corepair.cp_part;
	corepair.cp_node->vn_link.ln_pself = &LLIST_HEAD(corepair.cp_part->dp_srefs);
	corepair.cp_part->dp_srefs         = corepair.cp_node;
	corepair.cp_part->dp_tree.a_vmax   = (datapage_t)((num_bytes / PAGESIZE) - 1);
	corepair.cp_part->dp_state  = VM_DATAPART_STATE_LOCKED;
	corepair.cp_part->dp_flags |= VM_DATAPART_FLAG_LOCKED;
	block0_size = num_bytes / PAGESIZE;
	block0_addr = page_malloc(block0_size);
	if unlikely(block0_addr == PHYSPAGE_INVALID)
		goto err_corepair;
	/* initialize the did-init bitset. */
	if (num_bytes <= (BITSOF(uintptr_t) / VM_DATAPART_PPP_BITS) * PAGESIZE) {
		corepair.cp_part->dp_pprop = (flags & GFP_PREFLT) ? (uintptr_t)-1 : 0;
	} else {
		corepair.cp_part->dp_pprop_p = NULL;
		corepair.cp_part->dp_flags |= VM_DATAPART_FLAG_HEAPPPP;
	}
	corepair.cp_part->dp_ramdata.rd_blockv = &corepair.cp_part->dp_ramdata.rd_block0;
	corepair.cp_part->dp_ramdata.rd_block0.rb_start = block0_addr;
	corepair.cp_part->dp_ramdata.rd_block0.rb_size  = block0_size;
	if unlikely(!vm_kernel_treelock_writef_nx(flags))
		goto err_corepair_content;
	mapping_target = vm_getfree(&vm_kernel,
	                            HINT_GETADDR(KERNEL_VMHINT_HEAP),
	                            num_bytes,
	                            PAGESIZE,
	                            HINT_GETMODE(KERNEL_VMHINT_HEAP));
	corepair.cp_node->vn_node.a_vmin = PAGEID_ENCODE((byte_t *)mapping_target);
	corepair.cp_node->vn_node.a_vmax = PAGEID_ENCODE((byte_t *)mapping_target + num_bytes - 1);
	/* Map the node to the kernel page directory & do initialization. */
#ifdef ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE
	/* Prepare to map all of the new blocks. */
	if unlikely(!pagedir_prepare_map(mapping_target, num_bytes))
		goto err_corepair_content;
#endif /* ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE */
	pagedir_map(mapping_target, num_bytes,
	            physpage2addr(block0_addr),
	            PAGEDIR_MAP_FWRITE | PAGEDIR_MAP_FREAD);
	if (flags & GFP_CALLOC)
		memset(mapping_target, 0, num_bytes);
	vm_node_insert(corepair.cp_node);
	vm_kernel_treelock_endwrite();
	return mapping_target;
err_corepair_content:
	page_free(block0_addr, block0_size);
err_corepair:
	decref_nokill(corepair.cp_node->vn_block);
	decref_nokill(corepair.cp_part->dp_block);
	vm_node_free(corepair.cp_node);
	vm_datapart_free(corepair.cp_part);
	return NULL;
}

struct ph_unused {
	struct ph_unused *pu_next; /* [0..1] Next unused heap block. */
	size_t            pu_size; /* # of unused bytes in this block. */
};

/* [lock(ATOMIC)] Linked list of unused blocks. */
PRIVATE ATTR_COLDBSS WEAK struct ph_unused *ph_unused_blocks = NULL;

PRIVATE ATTR_COLDTEXT void *
NOTHROW(KCALL phcore_unsued_alloc_nx)(size_t num_bytes, gfp_t flags,
                                      size_t *__restrict palloc_bytes) {
	void *result = NULL;
	struct ph_unused *chain, **piter, *iter;
	/* Temporarily steal the chain.
	 * NOTE: This must be thread-safe, but not necessarily thread-efficient,
	 *       so it's OK if one thread can cause this fail for other threads! */
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
		memset(result, 0, *palloc_bytes);
	return result;
}

PRIVATE ATTR_COLDTEXT void
NOTHROW(KCALL phcore_unsued_append)(void *ptr, size_t num_bytes) {
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
	result = phcore_unsued_alloc_nx(num_bytes, flags, palloc_bytes);
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
					/* In order to somewhat better deal with small allocations,
					 * allow the unused tail to be re-used in later allocations. */
					phcore_unsued_append(result, unused_head);
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

/* Allocate at least `num_bytes' such that
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
 *       pointers allocated _before_ the poison heap got injected! */
PRIVATE ATTR_NOINLINE ATTR_PURE ATTR_COLDTEXT size_t
NOTHROW(KCALL phcore_usable_size)(void *ptr) {
	if (!ptr)
		return 0;
	TRY {
#ifdef CONFIG_USE_SLAB_ALLOCATORS
		if (KERNEL_SLAB_CHECKPTR(ptr))
			return SLAB_GET(ptr)->s_size;
#endif /* CONFIG_USE_SLAB_ALLOCATORS */
#ifdef HEAP_USABLE_SIZE_MASK
		return *(size_t *)((byte_t *)ptr - HEAP_USABLE_SIZE_OFFSET) & HEAP_USABLE_SIZE_MASK;
#else  /* HEAP_USABLE_SIZE_MASK */
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
INTDEF struct heapptr KCALL ph_heap_alloc(struct heap *self, size_t num_bytes, gfp_t flags);
INTDEF struct heapptr KCALL ph_heap_align(struct heap *self, size_t min_alignment, ptrdiff_t offset, size_t num_bytes, gfp_t flags);
INTDEF struct heapptr KCALL ph_heap_realloc(struct heap *self, void *old_ptr, size_t old_bytes, size_t new_bytes, gfp_t alloc_flags, gfp_t free_flags);
INTDEF struct heapptr KCALL ph_heap_realign(struct heap *self, void *old_ptr, size_t old_bytes, size_t min_alignment, ptrdiff_t offset, size_t new_bytes, gfp_t alloc_flags, gfp_t free_flags);
INTDEF struct heapptr NOTHROW(KCALL ph_heap_alloc_nx)(struct heap *self, size_t num_bytes, gfp_t flags);
INTDEF struct heapptr NOTHROW(KCALL ph_heap_align_nx)(struct heap *self, size_t min_alignment, ptrdiff_t offset, size_t num_bytes, gfp_t flags);
INTDEF struct heapptr NOTHROW(KCALL ph_heap_realloc_nx)(struct heap *self, void *old_ptr, size_t old_bytes, size_t new_bytes, gfp_t alloc_flags, gfp_t free_flags);
INTDEF struct heapptr NOTHROW(KCALL ph_heap_realign_nx)(struct heap *self, void *old_ptr, size_t old_bytes, size_t min_alignment, ptrdiff_t offset, size_t new_bytes, gfp_t alloc_flags, gfp_t free_flags);
#ifdef CONFIG_POISON_HEAP_NEED_VOID_FUNCTIONS
INTDEF ATTR_CONST void NOTHROW(KCALL ph_heap_free)(struct heap *self, void *ptr, size_t num_bytes, gfp_t flags);
#endif /* CONFIG_POISON_HEAP_NEED_VOID_FUNCTIONS */
#ifdef CONFIG_POISON_HEAP_NEED_ZERO_FUNCTIONS
INTDEF ATTR_CONST size_t KCALL ph_heap_allat(struct heap *self, void *ptr, size_t num_bytes, gfp_t flags);
INTDEF ATTR_CONST size_t NOTHROW(KCALL ph_heap_allat_nx)(struct heap *self, void *ptr, size_t num_bytes, gfp_t flags);
INTDEF ATTR_CONST size_t NOTHROW(KCALL ph_heap_truncate)(struct heap *self, void *base, size_t old_size, size_t new_size, gfp_t free_flags);
INTDEF ATTR_CONST size_t NOTHROW(KCALL ph_heap_trim)(struct heap *self, size_t threshold);
#endif /* CONFIG_POISON_HEAP_NEED_ZERO_FUNCTIONS */
#ifdef CONFIG_DEBUG_HEAP
#ifdef CONFIG_POISON_HEAP_NEED_VOID_FUNCTIONS
INTDEF ATTR_CONST void NOTHROW(KCALL ph_heap_validate)(struct heap *self);
INTDEF ATTR_CONST void NOTHROW(KCALL ph_heap_validate_all)(void);
#endif /* CONFIG_POISON_HEAP_NEED_VOID_FUNCTIONS */
#endif /* CONFIG_DEBUG_HEAP */
#ifdef CONFIG_USE_SLAB_ALLOCATORS
#ifdef CONFIG_POISON_HEAP_NEED_ZERO_FUNCTIONS
#define DEFINE_SLAB_ALLOCATOR_FUNCTIONS(sz, _) \
	INTDEF ATTR_CONST void *NOTHROW(KCALL ph_slab_malloc##sz)(gfp_t flags);
SLAB_FOREACH_SIZE(DEFINE_SLAB_ALLOCATOR_FUNCTIONS, _)
#undef DEFINE_SLAB_ALLOCATOR_FUNCTIONS
#endif /* CONFIG_POISON_HEAP_NEED_ZERO_FUNCTIONS */
#define DEFINE_SLAB_ALLOCATOR_FUNCTIONS(sz, _)                           \
	INTDEF ATTR_RETNONNULL void *KCALL ph_slab_kmalloc##sz(gfp_t flags); \
	INTDEF void *NOTHROW(KCALL ph_slab_kmalloc_nx##sz)(gfp_t flags);
SLAB_FOREACH_SIZE(DEFINE_SLAB_ALLOCATOR_FUNCTIONS, _)
#undef DEFINE_SLAB_ALLOCATOR_FUNCTIONS
#endif /* CONFIG_USE_SLAB_ALLOCATORS */
INTDEF ATTR_RETNONNULL /*page-aligned*/ void *KCALL ph_vpage_alloc(size_t num_pages, size_t alignment_in_pages, gfp_t flags);
INTDEF ATTR_RETNONNULL /*page-aligned*/ void *NOTHROW(KCALL ph_vpage_alloc_nx)(size_t num_pages, size_t alignment_in_pages, gfp_t flags);
INTDEF ATTR_RETNONNULL /*page-aligned*/ void *KCALL ph_vpage_realloc(/*page-aligned*/ void *old_base, size_t old_pages, size_t new_pages, size_t alignment_in_pages, gfp_t alloc_flags, gfp_t free_flags);
INTDEF ATTR_RETNONNULL /*page-aligned*/ void *NOTHROW(KCALL ph_vpage_realloc_nx)(/*page-aligned*/ void *old_base, size_t old_pages, size_t new_pages, size_t alignment_in_pages, gfp_t alloc_flags, gfp_t free_flags);
#ifdef CONFIG_POISON_HEAP_NEED_VOID_FUNCTIONS
INTDEF ATTR_CONST void NOTHROW(KCALL ph_vpage_free)(/*page-aligned*/ void *base, size_t num_pages);
INTDEF ATTR_CONST void NOTHROW(KCALL ph_vpage_ffree)(/*page-aligned*/ void *base, size_t num_pages, gfp_t flags);
#endif /* CONFIG_POISON_HEAP_NEED_VOID_FUNCTIONS */

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
#ifdef CONFIG_POISON_HEAP_NEED_VOID_FUNCTIONS
INTDEF ATTR_CONST void NOTHROW(KCALL ph_kfree)(void *ptr);
INTDEF ATTR_CONST void NOTHROW(KCALL ph_kffree)(void *ptr, gfp_t flags);
#endif /* CONFIG_POISON_HEAP_NEED_VOID_FUNCTIONS */
#ifdef CONFIG_TRACE_MALLOC
INTDEF ATTR_CONST WUNUSED ATTR_RETNONNULL void *
NOTHROW(KCALL ph_kmalloc_trace_nx)(void *base, size_t num_bytes,
                                   gfp_t gfp, unsigned int tb_skip);
#ifdef CONFIG_POISON_HEAP_NEED_ZERO_FUNCTIONS
INTDEF ATTR_CONST size_t KCALL ph_kmalloc_leaks(void);
INTDEF ATTR_CONST kmalloc_leak_t KCALL ph_kmalloc_leaks_collect(void);
INTDEF ATTR_CONST ssize_t KCALL ph_kmalloc_leaks_print(kmalloc_leak_t leaks, __pformatprinter printer, void *arg, size_t *pnum_leaks);
INTDEF ATTR_CONST size_t KCALL ph_kmalloc_traceback(void *ptr, /*out*/ void **tb, size_t buflen, pid_t *p_alloc_roottid);
#endif /* CONFIG_POISON_HEAP_NEED_ZERO_FUNCTIONS */
#ifdef CONFIG_POISON_HEAP_NEED_VOID_FUNCTIONS
INTDEF void NOTHROW(KCALL ph_kmalloc_validate)(void);
INTDEF void NOTHROW(KCALL ph_kmalloc_leaks_discard)(kmalloc_leak_t leaks);
INTDEF void NOTHROW(KCALL ph_kmalloc_untrace)(void *ptr);
INTDEF void NOTHROW(KCALL ph_kmalloc_untrace_n)(void *ptr, size_t num_bytes);
#endif /* CONFIG_POISON_HEAP_NEED_VOID_FUNCTIONS */
#endif /* !CONFIG_TRACE_MALLOC */




/************************************************************************/
/* EXPOSED API IMPLEMENTATION                                           */
/************************************************************************/
INTERN ATTR_COLDTEXT struct heapptr KCALL
ph_heap_alloc(struct heap *self, size_t num_bytes, gfp_t flags) {
	return ph_heap_align(self, HEAP_ALIGNMENT, 0, num_bytes, flags);
}

INTERN ATTR_COLDTEXT struct heapptr KCALL
ph_heap_align(struct heap *UNUSED(self),
              size_t min_alignment, ptrdiff_t offset,
              size_t num_bytes, gfp_t flags) {
	struct heapptr result;
	result.hp_ptr = phcore_memalign(min_alignment, offset, num_bytes, flags);
	result.hp_siz = phcore_usable_size(result.hp_ptr);
	return result;
}

INTERN ATTR_COLDTEXT struct heapptr KCALL
ph_heap_realloc(struct heap *self,
                void *old_ptr, size_t old_bytes,
                size_t new_bytes, gfp_t alloc_flags,
                gfp_t free_flags) {
	return ph_heap_realign(self, old_ptr, old_bytes,
	                       HEAP_ALIGNMENT, 0, new_bytes,
	                       alloc_flags, free_flags);
}

INTERN ATTR_COLDTEXT struct heapptr KCALL
ph_heap_realign(struct heap *UNUSED(self), void *old_ptr,
                size_t old_bytes, size_t min_alignment,
                ptrdiff_t offset, size_t new_bytes,
                gfp_t alloc_flags, gfp_t UNUSED(free_flags)) {
	struct heapptr result;
	result.hp_ptr = phcore_realign(old_bytes ? old_ptr : NULL,
	                               min_alignment, offset,
	                               new_bytes, alloc_flags);
	result.hp_siz = phcore_usable_size(result.hp_ptr);
	return result;
}

INTERN ATTR_COLDTEXT struct heapptr
NOTHROW(KCALL ph_heap_alloc_nx)(struct heap *self, size_t num_bytes, gfp_t flags) {
	return ph_heap_align_nx(self, HEAP_ALIGNMENT, 0, num_bytes, flags);
}

INTERN ATTR_COLDTEXT struct heapptr
NOTHROW(KCALL ph_heap_align_nx)(struct heap *UNUSED(self), size_t min_alignment,
                                ptrdiff_t offset, size_t num_bytes, gfp_t flags) {
	struct heapptr result;
	result.hp_ptr = phcore_memalign_nx(min_alignment, offset, num_bytes, flags);
	result.hp_siz = phcore_usable_size(result.hp_ptr);
	return result;
}

INTERN ATTR_COLDTEXT struct heapptr
NOTHROW(KCALL ph_heap_realloc_nx)(struct heap *self, void *old_ptr,
                                  size_t old_bytes, size_t new_bytes,
                                  gfp_t alloc_flags, gfp_t free_flags) {
	return ph_heap_realign_nx(self, old_ptr, old_bytes,
	                          HEAP_ALIGNMENT, 0, new_bytes,
	                          alloc_flags, free_flags);
}

INTERN ATTR_COLDTEXT struct heapptr
NOTHROW(KCALL ph_heap_realign_nx)(struct heap *UNUSED(self), void *old_ptr,
                                  size_t old_bytes, size_t min_alignment,
                                  ptrdiff_t offset, size_t new_bytes,
                                  gfp_t alloc_flags, gfp_t UNUSED(free_flags)) {
	struct heapptr result;
	result.hp_ptr = phcore_realign_nx(old_bytes ? old_ptr : NULL,
	                                  min_alignment, offset,
	                                  new_bytes, alloc_flags);
	result.hp_siz = phcore_usable_size(result.hp_ptr);
	return result;
}

#ifdef CONFIG_POISON_HEAP_NEED_VOID_FUNCTIONS
INTERN ATTR_CONST ATTR_COLDTEXT void
NOTHROW(KCALL ph_heap_free)(struct heap *UNUSED(self), void *UNUSED(ptr),
                            size_t UNUSED(num_bytes), gfp_t UNUSED(flags)) {
	/* no-op */
}
#endif /* CONFIG_POISON_HEAP_NEED_VOID_FUNCTIONS */

#ifdef CONFIG_POISON_HEAP_NEED_ZERO_FUNCTIONS
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
#endif /* CONFIG_POISON_HEAP_NEED_ZERO_FUNCTIONS */

#ifdef CONFIG_DEBUG_HEAP
#ifdef CONFIG_POISON_HEAP_NEED_VOID_FUNCTIONS
INTERN ATTR_CONST ATTR_COLDTEXT void
NOTHROW(KCALL ph_heap_validate)(struct heap *UNUSED(self)) {
	/* no-op */
}

INTERN ATTR_CONST ATTR_COLDTEXT void
NOTHROW(KCALL ph_heap_validate_all)(void) {
	/* no-op */
}
#endif /* CONFIG_POISON_HEAP_NEED_VOID_FUNCTIONS */
#endif /* CONFIG_DEBUG_HEAP */

#ifdef CONFIG_USE_SLAB_ALLOCATORS
#ifdef CONFIG_POISON_HEAP_NEED_ZERO_FUNCTIONS
#define DEFINE_SLAB_ALLOCATOR_FUNCTIONS(sz, _)               \
	INTERN ATTR_CONST ATTR_COLDTEXT void *                   \
	NOTHROW(KCALL ph_slab_malloc##sz)(gfp_t UNUSED(flags)) { \
		return NULL;                                         \
	}
SLAB_FOREACH_SIZE(DEFINE_SLAB_ALLOCATOR_FUNCTIONS, _)
#undef DEFINE_SLAB_ALLOCATOR_FUNCTIONS
#endif /* CONFIG_POISON_HEAP_NEED_ZERO_FUNCTIONS */
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
#endif /* CONFIG_USE_SLAB_ALLOCATORS */

INTERN ATTR_COLDTEXT ATTR_RETNONNULL /*page-aligned*/ void *KCALL
ph_vpage_alloc(size_t num_pages, size_t alignment_in_pages, gfp_t flags) {
	size_t min_alignment, num_bytes;
	if (OVERFLOW_UMUL(alignment_in_pages, PAGESIZE, &min_alignment))
		THROW(E_BADALLOC_INSUFFICIENT_HEAP_MEMORY, (size_t)-1);
	if (OVERFLOW_UMUL(num_pages, PAGESIZE, &num_bytes))
		THROW(E_BADALLOC_INSUFFICIENT_HEAP_MEMORY, (size_t)-1);
	return phcore_memalign(min_alignment, 0, num_bytes, flags);
}

INTERN ATTR_COLDTEXT ATTR_RETNONNULL /*page-aligned*/ void *
NOTHROW(KCALL ph_vpage_alloc_nx)(size_t num_pages, size_t alignment_in_pages, gfp_t flags) {
	size_t min_alignment, num_bytes;
	if (OVERFLOW_UMUL(alignment_in_pages, PAGESIZE, &min_alignment))
		return NULL;
	if (OVERFLOW_UMUL(num_pages, PAGESIZE, &num_bytes))
		return NULL;
	return phcore_memalign_nx(min_alignment, 0, num_bytes, flags);
}

INTERN ATTR_COLDTEXT ATTR_RETNONNULL /*page-aligned*/ void *KCALL
ph_vpage_realloc(/*page-aligned*/ void *old_base, size_t UNUSED(old_pages), size_t new_pages,
                 size_t alignment_in_pages, gfp_t alloc_flags, gfp_t UNUSED(free_flags)) {
	size_t min_alignment, new_bytes;
	if (OVERFLOW_UMUL(alignment_in_pages, PAGESIZE, &min_alignment))
		THROW(E_BADALLOC_INSUFFICIENT_HEAP_MEMORY, (size_t)-1);
	if (OVERFLOW_UMUL(new_pages, PAGESIZE, &new_bytes))
		THROW(E_BADALLOC_INSUFFICIENT_HEAP_MEMORY, (size_t)-1);
	return phcore_realign(old_base, min_alignment, 0, new_bytes, alloc_flags);
}

INTERN ATTR_COLDTEXT ATTR_RETNONNULL /*page-aligned*/ void *
NOTHROW(KCALL ph_vpage_realloc_nx)(/*page-aligned*/ void *old_base, size_t UNUSED(old_pages),
                                   size_t new_pages, size_t alignment_in_pages,
                                   gfp_t alloc_flags, gfp_t UNUSED(free_flags)) {
	size_t min_alignment, new_bytes;
	if (OVERFLOW_UMUL(alignment_in_pages, PAGESIZE, &min_alignment))
		return NULL;
	if (OVERFLOW_UMUL(new_pages, PAGESIZE, &new_bytes))
		return NULL;
	return phcore_realign_nx(old_base, min_alignment, 0, new_bytes, alloc_flags);
}

#ifdef CONFIG_POISON_HEAP_NEED_VOID_FUNCTIONS
INTERN ATTR_CONST ATTR_COLDTEXT void
NOTHROW(KCALL ph_vpage_free)(/*page-aligned*/ void *UNUSED(base),
                             size_t UNUSED(num_pages)) {
	/* no-op */
}
INTERN ATTR_CONST ATTR_COLDTEXT void
NOTHROW(KCALL ph_vpage_ffree)(/*page-aligned*/ void *UNUSED(base),
                              size_t UNUSED(num_pages),
                              gfp_t UNUSED(flags)) {
	/* no-op */
}
#endif /* CONFIG_POISON_HEAP_NEED_VOID_FUNCTIONS */

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

#ifdef CONFIG_POISON_HEAP_NEED_VOID_FUNCTIONS
INTERN ATTR_CONST ATTR_COLDTEXT void
NOTHROW(KCALL ph_kfree)(void *UNUSED(ptr)) {
	/* no-op */
}

INTERN ATTR_CONST ATTR_COLDTEXT void
NOTHROW(KCALL ph_kffree)(void *UNUSED(ptr), gfp_t UNUSED(flags)) {
	/* no-op */
}
#endif /* CONFIG_POISON_HEAP_NEED_VOID_FUNCTIONS */

#ifdef CONFIG_TRACE_MALLOC
INTERN ATTR_CONST WUNUSED ATTR_RETNONNULL void *
NOTHROW(KCALL ph_kmalloc_trace_nx)(void *base, size_t UNUSED(num_bytes),
                                   gfp_t UNUSED(gfp), unsigned int UNUSED(tb_skip)) {
	return base;
}

#ifdef CONFIG_POISON_HEAP_NEED_ZERO_FUNCTIONS
INTERN ATTR_COLDTEXT ATTR_CONST size_t KCALL
ph_kmalloc_leaks(void) {
	return 0;
}

INTERN ATTR_COLDTEXT ATTR_CONST kmalloc_leak_t KCALL
ph_kmalloc_leaks_collect(void) {
	return NULL;
}

INTERN ATTR_COLDTEXT ATTR_CONST ssize_t KCALL
ph_kmalloc_leaks_print(kmalloc_leak_t UNUSED(leaks),
                       __pformatprinter UNUSED(printer),
                       void *UNUSED(arg),
                       size_t *UNUSED(pnum_leaks)) {
	return 0;
}

INTERN ATTR_COLDTEXT ATTR_CONST size_t KCALL
ph_kmalloc_traceback(void *UNUSED(ptr),
                     /*out*/ void **UNUSED(tb),
                     size_t UNUSED(buflen),
                     pid_t *UNUSED(p_alloc_roottid)) {
	return 0;
}
#endif /* CONFIG_POISON_HEAP_NEED_ZERO_FUNCTIONS */

#ifdef CONFIG_POISON_HEAP_NEED_VOID_FUNCTIONS
INTERN ATTR_COLDTEXT void
NOTHROW(KCALL ph_kmalloc_validate)(void) {
	/* no-op */
}

INTERN ATTR_COLDTEXT void
NOTHROW(KCALL ph_kmalloc_leaks_discard)(kmalloc_leak_t UNUSED(leaks)) {
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
#endif /* CONFIG_POISON_HEAP_NEED_VOID_FUNCTIONS */
#endif /* !CONFIG_TRACE_MALLOC */


DECL_END
#endif /* CONFIG_HAVE_POISON_HEAP */

#endif /* !GUARD_KERNEL_SRC_MEMORY_POISON_HEAP_C */
