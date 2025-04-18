/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
/*!always_includes <kernel/malloc-defs.h>*/
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_HEAP_H
#define GUARD_KERNEL_INCLUDE_KERNEL_HEAP_H 1

#include <kernel/compiler.h>

#include <kernel/types.h>

#include <hybrid/__bit.h>
#include <hybrid/sequence/list.h>
#include <hybrid/sequence/rbtree.h>
#include <hybrid/sched/atomic-lock.h>
#include <hybrid/typecore.h>

#include "malloc-defs.h"


/* Heap debug initialization DWORDs */
#ifdef CONFIG_HAVE_KERNEL_DEBUG_HEAP
#ifndef DEBUGHEAP_NO_MANS_LAND
#define DEBUGHEAP_NO_MANS_LAND __UINT32_C(0xdeadbeef) /* Debug initialization of unallocated memory. */
#endif /* !DEBUGHEAP_NO_MANS_LAND */
#ifndef DEBUGHEAP_FRESH_MEMORY
#define DEBUGHEAP_FRESH_MEMORY __UINT32_C(0xaaaaaaaa) /* Debug initialization of freshly allocated memory. */
#endif /* !DEBUGHEAP_FRESH_MEMORY */
#endif /* CONFIG_HAVE_KERNEL_DEBUG_HEAP */


#define OFFSET_HEAP_LOCK       0
#define OFFSET_HEAP_ADDR       __SIZEOF_POINTER__
#define OFFSET_HEAP_SIZE       (__SIZEOF_POINTER__ * 2)
#define OFFSET_HEAP_OVERALLOC  (__SIZEOF_POINTER__ * (2 + HEAP_BUCKET_COUNT))
#define OFFSET_HEAP_FREETHRESH (__SIZEOF_POINTER__ * (3 + HEAP_BUCKET_COUNT))
#define OFFSET_HEAP_HINTADDR   (__SIZEOF_POINTER__ * (4 + HEAP_BUCKET_COUNT))
#define OFFSET_HEAP_HINTMODE   (__SIZEOF_POINTER__ * (5 + HEAP_BUCKET_COUNT))
#define OFFSET_HEAP_PFREE      (__SIZEOF_POINTER__ * (6 + HEAP_BUCKET_COUNT))
#ifdef CONFIG_HAVE_KERNEL_HEAP_TRACE_DANGLE
#define OFFSET_HEAP_DANGLE (__SIZEOF_POINTER__ * (7 + HEAP_BUCKET_COUNT))
#define SIZEOF_HEAP        (__SIZEOF_POINTER__ * (8 + HEAP_BUCKET_COUNT))
#else /* CONFIG_HAVE_KERNEL_HEAP_TRACE_DANGLE */
#define SIZEOF_HEAP (__SIZEOF_POINTER__ * (7 + HEAP_BUCKET_COUNT))
#endif /* !CONFIG_HAVE_KERNEL_HEAP_TRACE_DANGLE */
#define ALIGNOF_HEAP __ALIGNOF_POINTER__


#ifdef __CC__
DECL_BEGIN

struct mfree {
	LIST_ENTRY(mfree)    mf_lsize;   /* [lock(:h_lock)][sort(ASCENDING(mf_size))] List of free entries ordered by size. */
	LLRBTREE_NODE(mfree) mf_laddr;   /* [lock(:h_lock)][sort(ASCENDING(self))] List of free entries ordered by address. */
	size_t               mf_size;    /* Size of this block (in bytes; aligned by `HEAP_ALIGNMENT'; including this header) */
#define MFREE_FUNDEFINED 0x00        /* Memory initialization is undefined. In debug mode, this means that memory is
                                      * initialized  using `DEBUGHEAP_NO_MANS_LAND', with portions that haven't been
                                      * allocated  yet pending initialization for either `DEBUGHEAP_FRESH_MEMORY' or
                                      * ZERO(0), depending on how they were originally allocated. */
#define MFREE_FZERO      GFP_CALLOC  /* Memory is ZERO-initialized. */
#define MFREE_FMASK      MFREE_FZERO /* Mask of known flags. */
#define MFREE_FRED       0x80        /* This is a red node. */
	u8                   mf_flags;   /* Set of `MFREE_F*' */
#ifdef CONFIG_HAVE_KERNEL_DEBUG_HEAP
	u8                   mf_szchk;   /* Checksum for `mf_size' */
#endif /* CONFIG_HAVE_KERNEL_DEBUG_HEAP */
	COMPILER_FLEXIBLE_ARRAY(byte_t, mf_data); /* Block data. */
};
#define MFREE_MIN(self)   ((uintptr_t)(self))
#define MFREE_MAX(self)   ((uintptr_t)(self) + (self)->mf_size - 1)
#define MFREE_BEGIN(self) ((uintptr_t)(self))
#define MFREE_END(self)   ((uintptr_t)(self) + (self)->mf_size)
#define MFREE_SIZE(self)  (self)->mf_size


/* Heap configuration:
 * Index offset for the first bucket that should be searched for a given size. */
#if HEAP_ALIGNMENT == 1
#   define HEAP_BUCKET_OFFSET     0 /* FFS(HEAP_ALIGNMENT) */
#elif HEAP_ALIGNMENT == 2
#   define HEAP_BUCKET_OFFSET     1 /* FFS(HEAP_ALIGNMENT) */
#elif HEAP_ALIGNMENT == 4
#   define HEAP_BUCKET_OFFSET     2 /* FFS(HEAP_ALIGNMENT) */
#elif HEAP_ALIGNMENT == 8
#   define HEAP_BUCKET_OFFSET     4 /* FFS(HEAP_ALIGNMENT) */
#elif HEAP_ALIGNMENT == 16
#   define HEAP_BUCKET_OFFSET     5 /* FFS(HEAP_ALIGNMENT) */
#elif HEAP_ALIGNMENT == 32
#   define HEAP_BUCKET_OFFSET     6 /* FFS(HEAP_ALIGNMENT) */
#elif HEAP_ALIGNMENT == 64
#   define HEAP_BUCKET_OFFSET     7 /* FFS(HEAP_ALIGNMENT) */
#elif HEAP_ALIGNMENT == 128
#   define HEAP_BUCKET_OFFSET     8 /* FFS(HEAP_ALIGNMENT) */
#elif HEAP_ALIGNMENT == 256
#   define HEAP_BUCKET_OFFSET     9 /* FFS(HEAP_ALIGNMENT) */
#else /* HEAP_ALIGNMENT == ... */
#   define HEAP_BUCKET_OFFSET     __hybrid_ffs(HEAP_ALIGNMENT)
#endif /* HEAP_ALIGNMENT != ... */

#define HEAP_BUCKET_OF(size)   (((__SIZEOF_SIZE_T__ * 8) - __hybrid_clz(size)) - HEAP_BUCKET_OFFSET)
#define HEAP_BUCKET_MINSIZE(i) (1 << ((i) + HEAP_BUCKET_OFFSET - 1))
#define HEAP_BUCKET_COUNT      ((__SIZEOF_SIZE_T__ * 8) - (HEAP_BUCKET_OFFSET - 1))

#define HEAP_INIT(overalloc, freethresh, hintaddr, hintmode) \
	{ ATOMIC_LOCK_INIT, __NULLPTR, {}, overalloc, freethresh, hintaddr, hintmode }

struct heap_pending_free {
	struct heap_pending_free *hpf_next;  /* [0..1] Next pending free block. */
	size_t                    hpf_size;  /* Size of the free block. */
	u8                        hpf_flags; /* Set of `MFREE_F*' */
};

#ifndef __mfree_list_defined
#define __mfree_list_defined
LIST_HEAD(mfree_list, mfree);
#endif /* !__mfree_list_defined */

struct heap {
	struct atomic_lock        h_lock;       /* Lock for this heap. */
	LLRBTREE_ROOT(mfree)      h_addr;       /* [lock(h_lock)][0..1] Heap sorted by address. */
	struct mfree_list         h_size[HEAP_BUCKET_COUNT];
	                                        /* [lock(h_lock)][0..1][*] Heap sorted by free range size. */
	WEAK size_t               h_overalloc;  /* Amount (in bytes) by which to over-allocate memory in heaps.
	                                         * NOTE: Set to ZERO(0) to disable overallocation. */
	WEAK size_t               h_freethresh; /* Threshold  that must be  reached before any  continuous block of free
	                                         * data is unmapped from the kernel VM. (Should always be `>= PAGESIZE') */
	WEAK void                *h_hintaddr;   /* Address to use as next allocation hint. */
	WEAK uintptr_t            h_hintmode;   /* Mode used when searching for new pages. */
	WEAK struct heap_pending_free *h_pfree; /* [0..1] Atomic linked list of pending free operations.
	                                         * -> Used to ensure that `heap_free()' is always an atomic
	                                         *    operation, even when `h_lock' couldn't be acquired at
	                                         *    the time. */
#ifdef CONFIG_HAVE_KERNEL_HEAP_TRACE_DANGLE
	WEAK size_t               h_dangle;     /* [lock(INCREMENT(h_lock),DECREMENT(atomic),READ(atomic))]
	                                         * Amount  of dangling bytes  of memory (memory that  was allocated, but may
	                                         * be release again  shortly) When  new memory  would have  to be  requested
	                                         * from  the core, this  field is checked to  see if it  is likely that some
	                                         * large block of memory will be released soon, preventing a race  condition
	                                         * that would unnecessarily allocate more memory when `heap_free_untraced()'
	                                         * is merging a  data block with  another, larger data  block, for which  it
	                                         * must  temporarily  allocate  that  larger  data  block.  Another   thread
	                                         * allocating memory at  the same  time may then  think that  the cache  has
	                                         * grown  too small for the allocation and unnecessarily request more memory
	                                         * from the core. */
#endif /* CONFIG_HAVE_KERNEL_HEAP_TRACE_DANGLE */
};



#if __SIZEOF_POINTER__ == 8 && defined(__UINT128_TYPE__)
typedef __UINT128_TYPE__ heapptr_t;
#define heapptr_getptr(self)   ((void *)(uintptr_t)(self))
#define heapptr_getsiz(self)   ((size_t)((self) >> 64))
#define heapptr_make(ptr, siz) ((__UINT128_TYPE__)(uintptr_t)(ptr) | ((__UINT128_TYPE__)(size_t)(siz) << 64))
#elif __SIZEOF_POINTER__ == 4 && defined(__UINT64_TYPE__)
typedef __UINT64_TYPE__ heapptr_t;
#define heapptr_getptr(self)   ((void *)(uintptr_t)(self))
#define heapptr_getsiz(self)   ((size_t)((self) >> 32))
#define heapptr_make(ptr, siz) ((__UINT64_TYPE__)(uintptr_t)(ptr) | ((__UINT64_TYPE__)(size_t)(siz) << 32))
#else /* ... */
typedef struct {
	void  *_hp_ptr; /* [1.._hp_siz] Pointer base address. */
	size_t _hp_siz; /* [!0] Size of the pointer. */
} heapptr_t;
#define heapptr_getptr(self)   ((self)._hp_ptr)
#define heapptr_getsiz(self)   ((self)._hp_siz)
#define heapptr_make(ptr, siz) ((heapptr_t){ ptr, siz })
#endif /* !... */

DATDEF struct heap kernel_heaps[__GFP_HEAPCOUNT];
DATDEF struct heap kernel_default_heap; /* == &kernel_heaps[GFP_NORMAL] */
DATDEF struct heap kernel_locked_heap;  /* == &kernel_heaps[GFP_LOCKED] */

#ifdef CONFIG_HAVE_KERNEL_DEBUG_HEAP
DATDEF struct mfile mfile_dbgheap;
#endif /* CONFIG_HAVE_KERNEL_DEBUG_HEAP */



FUNDEF ATTR_BLOCKLIKE_GFP(flags) WUNUSED NONNULL((1)) heapptr_t KCALL __os_heap_alloc_untraced(struct heap *__restrict self, size_t num_bytes, gfp_t flags) THROWS(E_BADALLOC) ASMNAME("heap_alloc_untraced");
FUNDEF ATTR_BLOCKLIKE_GFP(flags) WUNUSED NONNULL((1)) heapptr_t KCALL __os_heap_align_untraced(struct heap *__restrict self, size_t min_alignment, ptrdiff_t offset, size_t num_bytes, gfp_t flags) THROWS(E_BADALLOC) ASMNAME("heap_align_untraced");
FUNDEF ATTR_BLOCKLIKE_GFP(flags) WUNUSED NONNULL((1)) size_t KCALL __os_heap_allat_untraced(struct heap *__restrict self, VIRT void *__restrict ptr, size_t num_bytes, gfp_t flags) THROWS(E_BADALLOC) ASMNAME("heap_allat_untraced");
FUNDEF ATTR_BLOCKLIKE_GFP(alloc_flags) WUNUSED NONNULL((1)) heapptr_t KCALL __os_heap_realloc_untraced(struct heap *__restrict self, VIRT void *old_ptr, size_t old_bytes, size_t new_bytes, gfp_t alloc_flags, gfp_t free_flags) THROWS(E_BADALLOC) ASMNAME("heap_realloc_untraced");
FUNDEF ATTR_BLOCKLIKE_GFP(alloc_flags) WUNUSED NONNULL((1)) heapptr_t KCALL __os_heap_realign_untraced(struct heap *__restrict self, VIRT void *old_ptr, size_t old_bytes, size_t min_alignment, ptrdiff_t offset, size_t new_bytes, gfp_t alloc_flags, gfp_t free_flags) THROWS(E_BADALLOC) ASMNAME("heap_realign_untraced");
FUNDEF ATTR_BLOCKLIKE_GFP(flags) WUNUSED NONNULL((1)) heapptr_t KCALL __os_heap_alloc(struct heap *__restrict self, size_t num_bytes, gfp_t flags) THROWS(E_BADALLOC) ASMNAME("heap_alloc");
FUNDEF ATTR_BLOCKLIKE_GFP(flags) WUNUSED NONNULL((1)) heapptr_t KCALL __os_heap_align(struct heap *__restrict self, size_t min_alignment, ptrdiff_t offset, size_t num_bytes, gfp_t flags) THROWS(E_BADALLOC) ASMNAME("heap_align");
FUNDEF ATTR_BLOCKLIKE_GFP(flags) WUNUSED NONNULL((1)) size_t KCALL __os_heap_allat(struct heap *__restrict self, VIRT void *__restrict ptr, size_t num_bytes, gfp_t flags) THROWS(E_BADALLOC) ASMNAME("heap_allat");
FUNDEF ATTR_BLOCKLIKE_GFP(alloc_flags) WUNUSED NONNULL((1)) heapptr_t KCALL __os_heap_realloc(struct heap *__restrict self, VIRT void *old_ptr, size_t old_bytes, size_t new_bytes, gfp_t alloc_flags, gfp_t free_flags) THROWS(E_BADALLOC) ASMNAME("heap_realloc");
FUNDEF ATTR_BLOCKLIKE_GFP(alloc_flags) WUNUSED NONNULL((1)) heapptr_t KCALL __os_heap_realign(struct heap *__restrict self, VIRT void *old_ptr, size_t old_bytes, size_t min_alignment, ptrdiff_t offset, size_t new_bytes, gfp_t alloc_flags, gfp_t free_flags) THROWS(E_BADALLOC) ASMNAME("heap_realign");

/* No-throw variants of regular heap allocation functions.
 * These behave identical  to the  regular function,  however where  those would  have
 * thrown an error, these will instead return ZERO(0) or a heapptr with `hp_siz == 0'. */
FUNDEF ATTR_BLOCKLIKE_GFP(flags) WUNUSED NONNULL((1)) heapptr_t NOTHROW(KCALL __os_heap_alloc_untraced_nx)(struct heap *__restrict self, size_t num_bytes, gfp_t flags) ASMNAME("heap_alloc_untraced_nx");
FUNDEF ATTR_BLOCKLIKE_GFP(flags) WUNUSED NONNULL((1)) heapptr_t NOTHROW(KCALL __os_heap_align_untraced_nx)(struct heap *__restrict self, size_t min_alignment, ptrdiff_t offset, size_t num_bytes, gfp_t flags) ASMNAME("heap_align_untraced_nx");
FUNDEF ATTR_BLOCKLIKE_GFP(flags) WUNUSED NONNULL((1)) size_t NOTHROW(KCALL __os_heap_allat_untraced_nx)(struct heap *__restrict self, VIRT void *__restrict ptr, size_t num_bytes, gfp_t flags) ASMNAME("heap_allat_untraced_nx");
FUNDEF ATTR_BLOCKLIKE_GFP(alloc_flags) WUNUSED NONNULL((1)) heapptr_t NOTHROW(KCALL __os_heap_realloc_untraced_nx)(struct heap *__restrict self, VIRT void *old_ptr, size_t old_bytes, size_t new_bytes, gfp_t alloc_flags, gfp_t free_flags) ASMNAME("heap_realloc_untraced_nx");
FUNDEF ATTR_BLOCKLIKE_GFP(alloc_flags) WUNUSED NONNULL((1)) heapptr_t NOTHROW(KCALL __os_heap_realign_untraced_nx)(struct heap *__restrict self, VIRT void *old_ptr, size_t old_bytes, size_t min_alignment, ptrdiff_t offset, size_t new_bytes, gfp_t alloc_flags, gfp_t free_flags) ASMNAME("heap_realign_untraced_nx");
FUNDEF ATTR_BLOCKLIKE_GFP(flags) WUNUSED NONNULL((1)) heapptr_t NOTHROW(KCALL __os_heap_alloc_nx)(struct heap *__restrict self, size_t num_bytes, gfp_t flags) ASMNAME("heap_alloc_nx");
FUNDEF ATTR_BLOCKLIKE_GFP(flags) WUNUSED NONNULL((1)) heapptr_t NOTHROW(KCALL __os_heap_align_nx)(struct heap *__restrict self, size_t min_alignment, ptrdiff_t offset, size_t num_bytes, gfp_t flags) ASMNAME("heap_align_nx");
FUNDEF ATTR_BLOCKLIKE_GFP(flags) WUNUSED NONNULL((1)) size_t NOTHROW(KCALL __os_heap_allat_nx)(struct heap *__restrict self, VIRT void *__restrict ptr, size_t num_bytes, gfp_t flags) ASMNAME("heap_allat_nx");
FUNDEF ATTR_BLOCKLIKE_GFP(alloc_flags) WUNUSED NONNULL((1)) heapptr_t NOTHROW(KCALL __os_heap_realloc_nx)(struct heap *__restrict self, VIRT void *old_ptr, size_t old_bytes, size_t new_bytes, gfp_t alloc_flags, gfp_t free_flags) ASMNAME("heap_realloc_nx");
FUNDEF ATTR_BLOCKLIKE_GFP(alloc_flags) WUNUSED NONNULL((1)) heapptr_t NOTHROW(KCALL __os_heap_realign_nx)(struct heap *__restrict self, VIRT void *old_ptr, size_t old_bytes, size_t min_alignment, ptrdiff_t offset, size_t new_bytes, gfp_t alloc_flags, gfp_t free_flags) ASMNAME("heap_realign_nx");

#ifndef __OMIT_HEAP_CONSTANT_P_WRAPPERS
/* Allocate  at  least   `num_bytes'  of  dynamic   memory,
 * aligned by at least `min_alignment' or `HEAP_ALIGNMENT'.
 * NOTES:
 *   - Passing `0',  or  anything  less  than  `HEAP_MINSIZE'
 *     for `num_bytes' is the same as passing `HEAP_MINSIZE'.
 *   - Passing anything less than `HEAP_ALIGNMENT' for `min_alignment'
 *     is  the  same as  passing `HEAP_ALIGNMENT'  for `min_alignment'
 *   - The `offset' parameter is a delta added to the returned pointer
 *     where the given `min_alignment' applies:
 *     >> assert(IS_ALIGNED((uintptr_t)heapptr_getptr(return) + offset, min_alignment));
 *     However, it doesn't guaranty that memory at `(uintptr_t)heapptr_getptr(return) + offset'
 *     is actually part of the allocation.
 *     HINT: `offset' is internally truncated by `min_alignment':
 *           `offset = offset & (min_alignment - 1)'
 *   - These functions are written to be able to deal with _ANY_ `num_bytes'
 *     value, including unaligned value, or absurdly large values that  were
 *     designed only to cause internal overflow errors.
 * The following flags affect behavior:
 *    heap_alloc_untraced / heap_align_untraced:
 *       - GFP_CALLOC            -- Allocate ZERO-initialized memory (in `heapptr_getptr(return) ...+= heapptr_getsiz(return)')
 *       - GFP_NOOVER            -- Do not overallocate (by `self->h_overalloc')
 *       - GFP_NOMMAP            -- Don't map new memory (throw `E_WOULDBLOCK' instead)
 *       - GFP_ATOMIC            -- Do not block when mapping new memory (throw `E_WOULDBLOCK' instead)
 *       - GFP_NOCLRC|GFP_NOSWAP -- Behavioral modifiers for swapping memory
 *    heap_free_untraced:
 *       - GFP_CALLOC            -- The given memory block is ZERO-initialized (allows for some internal optimizations)
 *       - GFP_NOTRIM            -- Do not `mman_unmap()' free memory blocks larger than
 *                                  `h_freethresh', but keep them in cache instead.
 * NOTE: `heap_free_untraced()' always completes without  blocking.
 *       If `mman_unmap()' needs to be called, the free() operation
 *       is either postponed until the next call to a heap function
 *       that is allowed to block, or  is simply kept in cache,  as
 *       though `GFP_NOMAP' has been passed.
 * NOTE: The  `*_traced'  family  of  functions   will  automatically  call  `kmalloc_trace'   /
 *       `kmalloc_untrace' in  order  to  register  /  unregister the  data  blocks  as  a  MALL
 *       GC search data block. When building without `CONFIG_HAVE_KERNEL_TRACE_MALLOC', they are
 *       aliasing the regular versions.
 * @param: flags: Set of `GFP_*' flags used for allocation.
 * @throw: E_BADALLOC:   Failed to allocate memory.
 * @throw: E_WOULDBLOCK: `GFP_NOMAP' was specified and new memory would have had to be mapped. (implied)
 * @throw: E_WOULDBLOCK: `GFP_ATOMIC' was specified and a lock could not be acquired immediately. (implied) */
#ifndef __OMIT_HEAP_TRACED_CONSTANT_P_WRAPPERS
FORCELOCAL ATTR_BLOCKLIKE_GFP(flags) ATTR_ARTIFICIAL WUNUSED NONNULL((1)) heapptr_t KCALL
heap_alloc(struct heap *__restrict self, size_t num_bytes, gfp_t flags)
		THROWS(E_BADALLOC) {
	if (__builtin_constant_p(num_bytes))
		return __os_heap_alloc(self,
		                       (num_bytes + (HEAP_ALIGNMENT - 1)) & ~(HEAP_ALIGNMENT - 1),
		                       flags);
	return __os_heap_alloc(self, num_bytes, flags);
}

FORCELOCAL ATTR_BLOCKLIKE_GFP(flags) ATTR_ARTIFICIAL WUNUSED NONNULL((1)) heapptr_t KCALL
heap_align(struct heap *__restrict self, size_t min_alignment,
           ptrdiff_t offset, size_t num_bytes, gfp_t flags)
		THROWS(E_BADALLOC) {
	if ((__builtin_constant_p(min_alignment) && min_alignment <= HEAP_ALIGNMENT) &&
	    (__builtin_constant_p(offset) && (offset & (min_alignment - 1)) == 0))
		return heap_alloc(self, num_bytes, flags);
	if (__builtin_constant_p(num_bytes))
		return __os_heap_align(self, min_alignment, offset,
		                       (num_bytes + (HEAP_ALIGNMENT - 1)) & ~(HEAP_ALIGNMENT - 1),
		                       flags);
	return __os_heap_align(self, min_alignment, offset, num_bytes, flags);
}

/* Upon failure, `heapptr_getsiz(return) == 0' */
FORCELOCAL ATTR_BLOCKLIKE_GFP(flags) ATTR_ARTIFICIAL WUNUSED NONNULL((1)) heapptr_t
NOTHROW(KCALL heap_alloc_nx)(struct heap *__restrict self, size_t num_bytes, gfp_t flags) {
	if (__builtin_constant_p(num_bytes))
		return __os_heap_alloc_nx(self,
		                          (num_bytes + (HEAP_ALIGNMENT - 1)) & ~(HEAP_ALIGNMENT - 1),
		                          flags);
	return __os_heap_alloc_nx(self, num_bytes, flags);
}

/* Upon failure, `heapptr_getsiz(return) == 0' */
FORCELOCAL ATTR_BLOCKLIKE_GFP(flags) ATTR_ARTIFICIAL WUNUSED NONNULL((1)) heapptr_t
NOTHROW(KCALL heap_align_nx)(struct heap *__restrict self,
                              size_t min_alignment, ptrdiff_t offset,
                              size_t num_bytes, gfp_t flags) {
	if ((__builtin_constant_p(min_alignment) && min_alignment <= HEAP_ALIGNMENT) &&
	    (__builtin_constant_p(offset) && (offset & (min_alignment - 1)) == 0))
		return heap_alloc_nx(self, num_bytes, flags);
	if (__builtin_constant_p(num_bytes))
		return __os_heap_align_nx(self, min_alignment, offset,
		                          (num_bytes + (HEAP_ALIGNMENT - 1)) & ~(HEAP_ALIGNMENT - 1),
		                          flags);
	return __os_heap_align_nx(self, min_alignment, offset, num_bytes, flags);
}
#endif /* !__OMIT_HEAP_TRACED_CONSTANT_P_WRAPPERS */

FORCELOCAL ATTR_BLOCKLIKE_GFP(flags) ATTR_ARTIFICIAL WUNUSED NONNULL((1)) heapptr_t KCALL
heap_alloc_untraced(struct heap *__restrict self, size_t num_bytes, gfp_t flags)
		THROWS(E_BADALLOC) {
	if (__builtin_constant_p(num_bytes))
		return __os_heap_alloc_untraced(self,
		                                (num_bytes + (HEAP_ALIGNMENT - 1)) & ~(HEAP_ALIGNMENT - 1),
		                                flags);
	return __os_heap_alloc_untraced(self, num_bytes, flags);
}

FORCELOCAL ATTR_BLOCKLIKE_GFP(flags) ATTR_ARTIFICIAL WUNUSED NONNULL((1)) heapptr_t KCALL
heap_align_untraced(struct heap *__restrict self, size_t min_alignment,
                    ptrdiff_t offset, size_t num_bytes, gfp_t flags)
		THROWS(E_BADALLOC) {
	if ((__builtin_constant_p(min_alignment) && min_alignment <= HEAP_ALIGNMENT) &&
	    (__builtin_constant_p(offset) && (offset & (min_alignment - 1)) == 0))
		return heap_alloc_untraced(self, num_bytes, flags);
	if (__builtin_constant_p(num_bytes))
		return __os_heap_align_untraced(self, min_alignment, offset,
		                                (num_bytes + (HEAP_ALIGNMENT - 1)) & ~(HEAP_ALIGNMENT - 1),
		                                flags);
	return __os_heap_align_untraced(self, min_alignment, offset, num_bytes, flags);
}

/* Upon failure, `heapptr_getsiz(return) == 0' */
FORCELOCAL ATTR_BLOCKLIKE_GFP(flags) ATTR_ARTIFICIAL WUNUSED NONNULL((1)) heapptr_t
NOTHROW(KCALL heap_alloc_untraced_nx)(struct heap *__restrict self,
                                      size_t num_bytes, gfp_t flags) {
	if (__builtin_constant_p(num_bytes))
		return __os_heap_alloc_untraced_nx(self,
		                                   (num_bytes + (HEAP_ALIGNMENT - 1)) & ~(HEAP_ALIGNMENT - 1),
		                                   flags);
	return __os_heap_alloc_untraced_nx(self, num_bytes, flags);
}

/* Upon failure, `heapptr_getsiz(return) == 0' */
FORCELOCAL ATTR_BLOCKLIKE_GFP(flags) ATTR_ARTIFICIAL WUNUSED NONNULL((1)) heapptr_t
NOTHROW(KCALL heap_align_untraced_nx)(struct heap *__restrict self,
                                      size_t min_alignment, ptrdiff_t offset,
                                      size_t num_bytes, gfp_t flags) {
	if ((__builtin_constant_p(min_alignment) && min_alignment <= HEAP_ALIGNMENT) &&
	    (__builtin_constant_p(offset) && (offset & (min_alignment - 1)) == 0))
		return heap_alloc_untraced_nx(self, num_bytes, flags);
	if (__builtin_constant_p(num_bytes))
		return __os_heap_align_untraced_nx(self, min_alignment, offset,
		                                   (num_bytes + (HEAP_ALIGNMENT - 1)) & ~(HEAP_ALIGNMENT - 1),
		                                   flags);
	return __os_heap_align_untraced_nx(self, min_alignment, offset, num_bytes, flags);
}

/* Try  to  allocate  memory at  a  given address,  returning  the actual
 * number of  bytes that  the function  managed to  allocate, ZERO(0)  if
 * allocation is not possible due to an overlap, or throw an `E_BADALLOC'
 * if the additional `num_bytes' could not be allocated.
 * NOTE: When `num_bytes' is less than `HEAP_MINSIZE', this function
 *       may  actually   return  less   than  `HEAP_MINSIZE',   too!
 *       With  that in mind, always make sure that you've either already
 *       allocated neighboring data block, or that `num_bytes' is larger
 *       than, or equal to `HEAP_MINSIZE'.
 * @return: * : The amount of continuous bytes allocated (`>= num_bytes').
 * @return: 0 : Memory at the given address has already been allocated.
 * @assume(return == 0 || return >= num_bytes)
 * @param: flags: GFP flags used for allocation.
 * @throw: E_BADALLOC:   Failed to allocate sufficient memory for the operation.
 * @throw: E_WOULDBLOCK: `GFP_NOMAP' was specified and new memory would have had to be mapped. (implied)
 * @throw: E_WOULDBLOCK: `GFP_ATOMIC' was specified and a lock could not be acquired immediately. (implied) */
#ifndef __OMIT_HEAP_TRACED_CONSTANT_P_WRAPPERS
FORCELOCAL ATTR_BLOCKLIKE_GFP(flags) ATTR_ARTIFICIAL WUNUSED NONNULL((1)) size_t KCALL
heap_allat(struct heap *__restrict self,
           VIRT void *__restrict ptr,
           size_t num_bytes, gfp_t flags)
		THROWS(E_BADALLOC) {
	if (__builtin_constant_p(num_bytes))
		return __os_heap_allat(self, ptr,
		                       (num_bytes + (HEAP_ALIGNMENT - 1)) & ~(HEAP_ALIGNMENT - 1),
		                       flags);
	return __os_heap_allat(self, ptr, num_bytes, flags);
}

FORCELOCAL ATTR_BLOCKLIKE_GFP(flags) ATTR_ARTIFICIAL WUNUSED NONNULL((1)) size_t
NOTHROW(KCALL heap_allat_nx)(struct heap *__restrict self, VIRT void *__restrict ptr,
                             size_t num_bytes, gfp_t flags) {
	if (__builtin_constant_p(num_bytes))
		return __os_heap_allat_nx(self, ptr,
		                          (num_bytes + (HEAP_ALIGNMENT - 1)) & ~(HEAP_ALIGNMENT - 1),
		                          flags);
	return __os_heap_allat_nx(self, ptr, num_bytes, flags);
}
#endif /* !__OMIT_HEAP_TRACED_CONSTANT_P_WRAPPERS */

FORCELOCAL ATTR_BLOCKLIKE_GFP(flags) ATTR_ARTIFICIAL WUNUSED NONNULL((1)) size_t KCALL
heap_allat_untraced(struct heap *__restrict self,
                    VIRT void *__restrict ptr,
                    size_t num_bytes, gfp_t flags)
		THROWS(E_BADALLOC) {
	if (__builtin_constant_p(num_bytes))
		return __os_heap_allat_untraced(self, ptr,
		                                (num_bytes + (HEAP_ALIGNMENT - 1)) & ~(HEAP_ALIGNMENT - 1),
		                                flags);
	return __os_heap_allat_untraced(self, ptr, num_bytes, flags);
}

FORCELOCAL ATTR_BLOCKLIKE_GFP(flags) ATTR_ARTIFICIAL WUNUSED NONNULL((1)) size_t
NOTHROW(KCALL heap_allat_untraced_nx)(struct heap *__restrict self,
                                      VIRT void *__restrict ptr,
                                      size_t num_bytes, gfp_t flags) {
	if (__builtin_constant_p(num_bytes))
		return __os_heap_allat_untraced_nx(self, ptr,
		                                   (num_bytes + (HEAP_ALIGNMENT - 1)) & ~(HEAP_ALIGNMENT - 1),
		                                   flags);
	return __os_heap_allat_untraced_nx(self, ptr, num_bytes, flags);
}

/* A convenience wrapper for `heap_alloc_untraced()', `heap_allat_untraced()' and
 * `heap_free_untraced()', implementing the following realloc()-style  semantics:
 *   - realloc(ptr, 0)                           --> Realloc to minimal size
 *   - realloc(ptr, malloc_usable_size(ptr) - x) --> Free unused memory at the end (always succeeds)
 *   - realloc(ptr, malloc_usable_size(ptr) + x) --> Try to `heap_allat_untraced()' at the old end, or move to new memory
 *   - realloc(0, x)                             --> Same as `heap_alloc_untraced()'
 *
 * Additionally, `GFP_NOMOVE' may be specified, in which case the base address of the
 * returned pointer will  always be  `{old_ptr,x} | x >= new_bytes && x <= old_bytes'
 * or `NULL, 0' (when `new_bytes > old_bytes'):
 *   - realloc_in_place(ptr, malloc_usable_size(ptr) - x) --> Free unused memory at the end (always succeeds)
 *   - realloc_in_place(ptr, malloc_usable_size(ptr) + x) --> Try to `heap_allat_untraced()' at the old end, or return (NULL, 0) (ignoring NX-mode)
 *   - realloc_in_place(0, x)                             --> Always return (NULL, 0) (ignoring NX-mode)
 *
 * NOTE: These functions always return a fully allocated heap data block.
 * NOTE: Alignment arguments passed to `heap_realign_untraced()' are ignored
 *       unless  the  initial, or  a new  data block  have to  be allocated.
 * NOTE: Allocation and free flags have been split to allow the user
 *       to request zero-initialized memory to be allocated for  new
 *       allocations, while simultaneously  releasing unused  memory
 *       without indicating that it is zero-initialized.
 * NOTE: If realloc() needs to move the data block to a new location,
 *       the old location  is freed using  `free_flags & ~GFP_CALLOC'
 * NOTE: These functions do _NOT_ implement `GFP_NOMOVE' support, as it  would
 *       not only be ambiguous in which set of flags that flag should  appear,
 *       but it also wouldn't fit the image if this function returned anything
 *       other than a valid HEAP data block.
 *       If you want to extend a heap data block in-place, simply use `heap_allat_untraced()'
 * @assume(heapptr_getsiz(return) >= new_bytes);
 * @param: old_ptr:      [valid_if(old_bytes != 0)] Base address of the old data block.
 * @param: old_bytes:    The old size of the data block (can be ZERO(0); must be aligned to `HEAP_ALIGNMENT' by the caller)
 * @param: alloc_flags:  Set of `GFP_*' flags used for allocating data.
 * @param: free_flags:   Set of `GFP_*' flags used for freeing data.
 * @param: new_bytes:    The new size of the data block (will be aligned by `HEAP_ALIGNMENT').
 * @throw: E_BADALLOC:   Failed to allocate memory.
 * @throw: E_WOULDBLOCK: `GFP_NOMAP' was specified and new memory would have had to be mapped. (implied)
 * @throw: E_WOULDBLOCK: `GFP_ATOMIC' was specified and a lock could not be acquired immediately. (implied) */
#ifndef __OMIT_HEAP_TRACED_CONSTANT_P_WRAPPERS
FORCELOCAL ATTR_BLOCKLIKE_GFP(alloc_flags) ATTR_ARTIFICIAL WUNUSED NONNULL((1)) heapptr_t KCALL
heap_realloc(struct heap *__restrict self,
             VIRT void *old_ptr, size_t old_bytes,
             size_t new_bytes, gfp_t alloc_flags, gfp_t free_flags)
		THROWS(E_BADALLOC) {
	if (__builtin_constant_p(old_bytes)) {
		if (old_bytes == 0)
			return heap_alloc(self, new_bytes, alloc_flags);
	}
	if (__builtin_constant_p(new_bytes))
		return __os_heap_realloc(self, old_ptr, old_bytes,
		                         (new_bytes + (HEAP_ALIGNMENT - 1)) & ~(HEAP_ALIGNMENT - 1),
		                         alloc_flags, free_flags);
	return __os_heap_realloc(self, old_ptr, old_bytes, new_bytes,
	                         alloc_flags, free_flags);
}

FORCELOCAL ATTR_BLOCKLIKE_GFP(alloc_flags) ATTR_ARTIFICIAL WUNUSED NONNULL((1)) heapptr_t KCALL
heap_realign(struct heap *__restrict self,
             VIRT void *old_ptr, size_t old_bytes,
             size_t min_alignment, ptrdiff_t offset,
             size_t new_bytes, gfp_t alloc_flags, gfp_t free_flags)
		THROWS(E_BADALLOC) {
	if (__builtin_constant_p(old_bytes)) {
		if (old_bytes == 0)
			return heap_align(self, min_alignment, offset, new_bytes, alloc_flags);
	}
	if ((__builtin_constant_p(min_alignment) && min_alignment <= HEAP_ALIGNMENT) &&
	    (__builtin_constant_p(offset) && (offset & (min_alignment - 1)) == 0))
		return heap_realloc(self, old_ptr, old_bytes, new_bytes, alloc_flags, free_flags);
	if (__builtin_constant_p(new_bytes))
		return __os_heap_realign(self, old_ptr, old_bytes, min_alignment,
		                         offset, (new_bytes + (HEAP_ALIGNMENT - 1)) & ~(HEAP_ALIGNMENT - 1),
		                         alloc_flags, free_flags);
	return __os_heap_realign(self, old_ptr, old_bytes, min_alignment,
	                         offset, new_bytes, alloc_flags, free_flags);
}

/* Upon failure, `heapptr_getsiz(return) == 0' */
FORCELOCAL ATTR_BLOCKLIKE_GFP(alloc_flags) ATTR_ARTIFICIAL WUNUSED NONNULL((1)) heapptr_t
NOTHROW(KCALL heap_realloc_nx)(struct heap *__restrict self,
                               VIRT void *old_ptr, size_t old_bytes,
                               size_t new_bytes, gfp_t alloc_flags,
                               gfp_t free_flags) {
	if (__builtin_constant_p(old_bytes)) {
		if (old_bytes == 0)
			return heap_alloc_nx(self, new_bytes, alloc_flags);
	}
	if (__builtin_constant_p(new_bytes))
		return __os_heap_realloc_nx(self, old_ptr, old_bytes,
		                            (new_bytes + (HEAP_ALIGNMENT - 1)) & ~(HEAP_ALIGNMENT - 1),
		                            alloc_flags, free_flags);
	return __os_heap_realloc_nx(self, old_ptr, old_bytes, new_bytes,
	                            alloc_flags, free_flags);
}

/* Upon failure, `heapptr_getsiz(return) == 0' */
FORCELOCAL ATTR_BLOCKLIKE_GFP(alloc_flags) ATTR_ARTIFICIAL WUNUSED NONNULL((1)) heapptr_t
NOTHROW(KCALL heap_realign_nx)(struct heap *__restrict self,
                               VIRT void *old_ptr, size_t old_bytes,
                               size_t min_alignment, ptrdiff_t offset,
                               size_t new_bytes, gfp_t alloc_flags,
                               gfp_t free_flags) {
	if (__builtin_constant_p(old_bytes)) {
		if (old_bytes == 0)
			return heap_align_nx(self, min_alignment, offset, new_bytes, alloc_flags);
	}
	if ((__builtin_constant_p(min_alignment) && min_alignment <= HEAP_ALIGNMENT) &&
	    (__builtin_constant_p(offset) && (offset & (min_alignment - 1)) == 0))
		return heap_realloc_nx(self, old_ptr, old_bytes, new_bytes, alloc_flags, free_flags);
	if (__builtin_constant_p(new_bytes))
		return __os_heap_realign_nx(self, old_ptr, old_bytes, min_alignment,
		                            offset, (new_bytes + (HEAP_ALIGNMENT - 1)) & ~(HEAP_ALIGNMENT - 1),
		                            alloc_flags, free_flags);
	return __os_heap_realign_nx(self, old_ptr, old_bytes, min_alignment,
	                            offset, new_bytes, alloc_flags, free_flags);
}
#endif /* !__OMIT_HEAP_TRACED_CONSTANT_P_WRAPPERS */

FORCELOCAL ATTR_BLOCKLIKE_GFP(alloc_flags) ATTR_ARTIFICIAL WUNUSED NONNULL((1)) heapptr_t KCALL
heap_realloc_untraced(struct heap *__restrict self,
                      VIRT void *old_ptr, size_t old_bytes,
                      size_t new_bytes, gfp_t alloc_flags, gfp_t free_flags)
		THROWS(E_BADALLOC) {
	if (__builtin_constant_p(old_bytes)) {
		if (old_bytes == 0)
			return heap_alloc_untraced(self, new_bytes, alloc_flags);
	}
	if (__builtin_constant_p(new_bytes))
		return __os_heap_realloc_untraced(self, old_ptr, old_bytes,
		                                  (new_bytes + (HEAP_ALIGNMENT - 1)) & ~(HEAP_ALIGNMENT - 1),
		                                  alloc_flags, free_flags);
	return __os_heap_realloc_untraced(self, old_ptr, old_bytes, new_bytes,
	                                  alloc_flags, free_flags);
}

FORCELOCAL ATTR_BLOCKLIKE_GFP(alloc_flags) ATTR_ARTIFICIAL WUNUSED NONNULL((1)) heapptr_t KCALL
heap_realign_untraced(struct heap *__restrict self,
                      VIRT void *old_ptr, size_t old_bytes,
                      size_t min_alignment, ptrdiff_t offset,
                      size_t new_bytes, gfp_t alloc_flags, gfp_t free_flags)
		THROWS(E_BADALLOC) {
	if (__builtin_constant_p(old_bytes)) {
		if (old_bytes == 0)
			return heap_align_untraced(self, min_alignment, offset, new_bytes, alloc_flags);
	}
	if ((__builtin_constant_p(min_alignment) && min_alignment <= HEAP_ALIGNMENT) &&
	    (__builtin_constant_p(offset) && (offset & (min_alignment - 1)) == 0))
		return heap_realloc_untraced(self, old_ptr, old_bytes, new_bytes, alloc_flags, free_flags);
	if (__builtin_constant_p(new_bytes))
		return __os_heap_realign_untraced(self, old_ptr, old_bytes, min_alignment,
		                                  offset, (new_bytes + (HEAP_ALIGNMENT - 1)) & ~(HEAP_ALIGNMENT - 1),
		                                  alloc_flags, free_flags);
	return __os_heap_realign_untraced(self, old_ptr, old_bytes, min_alignment,
	                                  offset, new_bytes, alloc_flags, free_flags);
}

/* Upon failure, `heapptr_getsiz(return) == 0' */
FORCELOCAL ATTR_BLOCKLIKE_GFP(alloc_flags) ATTR_ARTIFICIAL WUNUSED NONNULL((1)) heapptr_t
NOTHROW(KCALL heap_realloc_untraced_nx)(struct heap *__restrict self,
                                        VIRT void *old_ptr, size_t old_bytes,
                                        size_t new_bytes, gfp_t alloc_flags,
                                        gfp_t free_flags) {
	if (__builtin_constant_p(old_bytes)) {
		if (old_bytes == 0)
			return heap_alloc_untraced_nx(self, new_bytes, alloc_flags);
	}
	if (__builtin_constant_p(new_bytes))
		return __os_heap_realloc_untraced_nx(self, old_ptr, old_bytes,
		                                     (new_bytes + (HEAP_ALIGNMENT - 1)) & ~(HEAP_ALIGNMENT - 1),
		                                     alloc_flags, free_flags);
	return __os_heap_realloc_untraced_nx(self, old_ptr, old_bytes, new_bytes,
	                                     alloc_flags, free_flags);
}

/* Upon failure, `heapptr_getsiz(return) == 0' */
FORCELOCAL ATTR_BLOCKLIKE_GFP(alloc_flags) ATTR_ARTIFICIAL WUNUSED NONNULL((1)) heapptr_t
NOTHROW(KCALL heap_realign_untraced_nx)(struct heap *__restrict self,
                                        VIRT void *old_ptr, size_t old_bytes,
                                        size_t min_alignment, ptrdiff_t offset,
                                        size_t new_bytes, gfp_t alloc_flags,
                                        gfp_t free_flags) {
	if (__builtin_constant_p(old_bytes)) {
		if (old_bytes == 0)
			return heap_align_untraced_nx(self, min_alignment, offset, new_bytes, alloc_flags);
	}
	if ((__builtin_constant_p(min_alignment) && min_alignment <= HEAP_ALIGNMENT) &&
	    (__builtin_constant_p(offset) && (offset & (min_alignment - 1)) == 0))
		return heap_realloc_untraced_nx(self, old_ptr, old_bytes, new_bytes, alloc_flags, free_flags);
	if (__builtin_constant_p(new_bytes))
		return __os_heap_realign_untraced_nx(self, old_ptr, old_bytes, min_alignment,
		                                     offset, (new_bytes + (HEAP_ALIGNMENT - 1)) & ~(HEAP_ALIGNMENT - 1),
		                                     alloc_flags, free_flags);
	return __os_heap_realign_untraced_nx(self, old_ptr, old_bytes, min_alignment,
	                                     offset, new_bytes, alloc_flags, free_flags);
}
#endif /* !__OMIT_HEAP_CONSTANT_P_WRAPPERS */

/* Free the given memory, returning it to the heap.
 * The   caller  must  ensure  that  `ptr'  and  `num_bytes'  are  aligned  by
 * `HEAP_ALIGNMENT', and that `num_bytes' be least `HEAP_MINSIZE' bytes large.
 * The following flags affect the behavior of this function:
 *       - GFP_NOTRIM          -- Do not release large blocks of free data back to the core.
 *       - GFP_CALLOC          -- The given data block is ZERO-initialized.
 * @param: flags:     The flags that should be used when freeing data. (see above)
 *                    NOTE: The heap flags  (`__GFP_HEAPMASK') must match  those
 *                          passed during original allocation of the data block.
 * @param: ptr:       The HEAP_ALIGNMENT-aligned base pointer of the block to-be freed.
 * @param: num_bytes: The amount of bytes that should be freed.
 *                    NOTE: This argument must be aligned by `HEAP_ALIGNMENT',
 *                          and must not be equal to ZERO(0). */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(KCALL heap_free)(struct heap *__restrict self,
                         VIRT void *ptr, size_t num_bytes, gfp_t flags);
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(KCALL heap_free_untraced)(struct heap *__restrict self,
                                  VIRT void *ptr, size_t num_bytes, gfp_t flags);

/* Truncate `base...old_size' to have a length of at least  `new_size'
 * bytes,  returning  the   actual  new  size   of  the  data   block.
 * When `new_size' is  larger than  `old_size', re-return  `old_size'.
 * This function is intended to be used to free unused trailing memory
 * of some data structure, without  running the risk of  re-allocating
 * that structure to another memory location. */
FUNDEF NOBLOCK WUNUSED NONNULL((1)) size_t
NOTHROW(KCALL heap_truncate)(struct heap *__restrict self, void *base,
                             size_t old_size, size_t new_size, gfp_t free_flags);
FUNDEF NOBLOCK WUNUSED NONNULL((1)) size_t
NOTHROW(KCALL heap_truncate_untraced)(struct heap *__restrict self, void *base,
                                      size_t old_size, size_t new_size, gfp_t free_flags);


/* Truncate the  given heap,  releasing  unmapping free  memory  chunks
 * that  are greater than, or equal to `CEIL_ALIGN(threshold,PAGESIZE)'
 * This function is automatically invoked  for kernel heaps as part  of
 * the clear-cache machinery,  though regular should  never feel  moved
 * to invoke this function manually, as all it really does is slow down
 * future calls to allocating heap functions.
 * NOTE: When `threshold' is lower than `PAGESIZE', `PAGESIZE' is used instead.
 * @return: * : The total number of bytes released back to the core (a multiple of PAGESIZE) */
FUNDEF NOBLOCK_IF(gfp & GFP_ATOMIC) NONNULL((1)) size_t
NOTHROW(KCALL heap_trim)(struct heap *__restrict self, size_t threshold, gfp_t flags);


#ifdef CONFIG_HAVE_KERNEL_DEBUG_HEAP
/* Validate   the  memory  of  the  given  heap  for
 * consistency, checking for invalid use-after-free. */
FUNDEF NOBLOCK NONNULL((1)) void NOTHROW(KCALL heap_validate)(struct heap *__restrict self);
FUNDEF NOBLOCK void NOTHROW(KCALL heap_validate_all)(void);
#define DEFINE_VALIDATABLE_HEAP(x) DEFINE_CALLBACK(".rodata.heaps.validatable", x)
#else /* CONFIG_HAVE_KERNEL_DEBUG_HEAP */
#define heap_validate(self)        (void)0
#define heap_validate_all()        (void)0
#define DEFINE_VALIDATABLE_HEAP(x) /* nothing */
#endif /* !CONFIG_HAVE_KERNEL_DEBUG_HEAP */

DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_HEAP_H */
