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
#ifndef GUARD_KERNEL_SRC_MEMORY_MALLOC_C
#define GUARD_KERNEL_SRC_MEMORY_MALLOC_C 1
#define __OMIT_KMALLOC_CONSTANT_P_WRAPPERS 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/except.h>
#include <kernel/heap.h>
#include <kernel/malloc.h>
#include <kernel/printk.h>
#include <kernel/slab.h>
#include <kernel/types.h>

#include <hybrid/align.h>
#include <hybrid/overflow.h>

#include <assert.h>
#include <stdint.h>
#include <string.h>

DECL_BEGIN

#if HEAP_ALIGNMENT < (__SIZEOF_SIZE_T__ + 1)
struct ATTR_PACKED mptr {
	uintptr_t mp_data; /* Size and heap of the mptr. */
};
STATIC_ASSERT(sizeof(struct mptr) == HEAP_ALIGNMENT);
#define MPTR_HEAP_SHIFT ((__SIZEOF_SIZE_T__ * 8) - 1)
#define MPTR_HEAP_MASK  ((uintptr_t)1 << MPTR_HEAP_SHIFT)
#define MPTR_SIZE_MASK  (((uintptr_t)1 << MPTR_HEAP_SHIFT) - 1)
#define MPTR_IS_SINGLE_WORD 1

#define mptr_init(x, size, heap) ((x)->mp_data = (size) | ((uintptr_t)(heap) << MPTR_HEAP_SHIFT))
#define mptr_size(x)             ((x)->mp_data & MPTR_SIZE_MASK)
#define mptr_setsize(x, size)    ((x)->mp_data = (size) | ((uintptr_t)(x)->mp_data & MPTR_HEAP_MASK))
#define mptr_heap_gfp(x)         (gfp_t)((x)->mp_data >> MPTR_HEAP_SHIFT)
#define mptr_assert(x)                                 \
	(/*assert(mptr_heap_gfp(x) < __GFP_HEAPCOUNT),*/   \
	 assert(IS_ALIGNED(mptr_size(x), HEAP_ALIGNMENT)), \
	 assert(mptr_size(x) >= HEAP_MINSIZE))
#else /* HEAP_ALIGNMENT < (__SIZEOF_SIZE_T__ + 1) */
struct ATTR_PACKED mptr {
	union ATTR_PACKED {
		struct ATTR_PACKED {
			size_t mp_size; /* Size of the block, including this header
			                 * (in bytes; aligned by  `HEAP_ALIGNMENT') */
			u8     mp_heap; /* [<= __GFP_HEAPCOUNT] The originating heap id */
		};
		byte_t     mp_align[HEAP_ALIGNMENT]; /* ... */
	};
};
STATIC_ASSERT(sizeof(struct mptr) == HEAP_ALIGNMENT);

#define mptr_init(x, size, heap) ((x)->mp_size = (size), (x)->mp_heap = (heap))
#define mptr_size(x)             (x)->mp_size
#define mptr_setsize(x, size)    ((x)->mp_size = (size))
#define mptr_heap_gfp(x)         (x)->mp_heap
#define mptr_assert(x)                                 \
	(assert(mptr_heap_gfp(x) < __GFP_HEAPCOUNT),       \
	 assert(IS_ALIGNED(mptr_size(x), HEAP_ALIGNMENT)), \
	 assert(mptr_size(x) >= HEAP_MINSIZE))
#endif /* HEAP_ALIGNMENT >= (__SIZEOF_SIZE_T__ + 1) */

#define mptr_get(x)  ((struct mptr *)(x) - 1)
#define mptr_user(x) ((struct mptr *)(x) + 1)
#define mptr_heap(x) (&kernel_heaps[mptr_heap_gfp(x)])

#if !defined(NDEBUG) && 0
#define mptr_assert_paranoid mptr_assert
#else /* !NDEBUG */
#define mptr_assert_paranoid(x) (void)0
#endif /* NDEBUG */


PUBLIC ATTR_WEAK WUNUSED size_t
NOTHROW(KCALL kmalloc_usable_size)(VIRT void *ptr) {
	struct mptr *mblock;
	if (!ptr)
		return 0;
#ifdef CONFIG_USE_SLAB_ALLOCATORS
	if (KERNEL_SLAB_CHECKPTR(ptr))
		return SLAB_GET(ptr)->s_size;
#endif /* CONFIG_USE_SLAB_ALLOCATORS */
	assert(IS_ALIGNED((uintptr_t)ptr, HEAP_ALIGNMENT));
	mblock = mptr_get(ptr);
	mptr_assert(mblock);
	return mptr_size(mblock) - sizeof(struct mptr);
}

PUBLIC ATTR_WEAK void
NOTHROW(KCALL kfree)(VIRT void *ptr) {
	struct mptr *mblock;
	if (!ptr)
		return; /* Ignore NULL-pointers. */
#ifdef CONFIG_USE_SLAB_ALLOCATORS
	if (KERNEL_SLAB_CHECKPTR(ptr)) {
		slab_free(ptr);
		return;
	}
#endif /* CONFIG_USE_SLAB_ALLOCATORS */
	assert(IS_ALIGNED((uintptr_t)ptr, HEAP_ALIGNMENT));
	mblock = mptr_get(ptr);
	mptr_assert(mblock);
	heap_free_untraced(mptr_heap(mblock), mblock,
	                   mptr_size(mblock), mptr_heap_gfp(mblock));
}

PUBLIC ATTR_WEAK void
NOTHROW(KCALL kffree)(VIRT void *ptr, gfp_t flags) {
	struct mptr *mblock;
	if (!ptr)
		return; /* Ignore NULL-pointers. */
#ifdef CONFIG_USE_SLAB_ALLOCATORS
	if (KERNEL_SLAB_CHECKPTR(ptr)) {
		slab_ffree(ptr, flags);
		return;
	}
#endif /* CONFIG_USE_SLAB_ALLOCATORS */
	assert(IS_ALIGNED((uintptr_t)ptr, HEAP_ALIGNMENT));
	mblock = mptr_get(ptr);
	mptr_assert(mblock);
	heap_free_untraced(mptr_heap(mblock),
	                   mblock, mptr_size(mblock),
	                   mptr_heap_gfp(mblock) |
	                   (flags & ~__GFP_HEAPMASK));
}


PUBLIC NOBLOCK ATTR_WEAK void
NOTHROW(KCALL kmalloc_validate)(void) {
}

PUBLIC ATTR_WEAK ATTR_CONST size_t KCALL
kmalloc_leaks(void) THROWS(E_WOULDBLOCK) {
	return 0;
}

PUBLIC ATTR_WEAK ATTR_CONST kmalloc_leaks_t KCALL
kmalloc_leaks_collect(void) THROWS(E_WOULDBLOCK) {
	return NULL;
}

PUBLIC ATTR_WEAK ATTR_CONST ssize_t KCALL
kmalloc_leaks_print(kmalloc_leaks_t UNUSED(leaks),
                    __pformatprinter UNUSED(printer),
                    void *UNUSED(arg),
                    size_t *UNUSED(pnum_leaks)) {
	return 0;
}


/* Even though they've already been marked as ATTR_CONST,
 * gcc keeps complaining that I should mark the as  const
 * >> WHEN THEY'RE ALREADY MARKED AS SUCH!!! << */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsuggest-attribute=const"
PUBLIC NOBLOCK ATTR_CONST ATTR_WEAK WUNUSED size_t
NOTHROW(KCALL kmalloc_leaks_count)(kmalloc_leaks_t UNUSED(leaks)) {
	return 0;
}

PUBLIC NOBLOCK ATTR_CONST ATTR_WEAK memleak_t
NOTHROW(FCALL memleak_next)(kmalloc_leaks_t UNUSED(leaks),
                            memleak_t UNUSED(prev)) {
	return NULL;
}
DEFINE_PUBLIC_WEAK_ALIAS(memleak_getattr, memleak_next);
#pragma GCC diagnostic pop


PUBLIC NOBLOCK ATTR_WEAK void
NOTHROW(KCALL kmalloc_leaks_release)(kmalloc_leaks_t UNUSED(leaks),
                                     unsigned int UNUSED(now)) {
}

PUBLIC ATTR_WEAK ATTR_CONST NOBLOCK_IF(gfp & GFP_ATOMIC) WUNUSED void *
NOTHROW(KCALL kmalloc_trace_nx)(void *base, size_t UNUSED(num_bytes),
                                gfp_t UNUSED(gfp), unsigned int UNUSED(tb_skip)) {
	return base;
}

PUBLIC NOBLOCK ATTR_WEAK ATTR_CONST void
NOTHROW(KCALL kmalloc_untrace)(void *UNUSED(ptr)) {
}

PUBLIC NOBLOCK ATTR_WEAK ATTR_CONST void
NOTHROW(KCALL kmalloc_untrace_n)(void *UNUSED(ptr), size_t UNUSED(num_bytes)) {
}

PUBLIC NOBLOCK ATTR_WEAK ATTR_CONST size_t
NOTHROW(KCALL kmalloc_traceback)(void *UNUSED(ptr),
                                 /*out*/ void **UNUSED(tb),
                                 size_t UNUSED(buflen),
                                 pid_t *UNUSED(p_alloc_roottid)) {
	return 0;
}


PUBLIC NOBLOCK ATTR_WEAK ATTR_CONST ssize_t KCALL
kmalloc_printtrace(void *UNUSED(ptr),
                   __pformatprinter UNUSED(printer),
                   void *UNUSED(arg)) {
	return 0;
}


DEFINE_PUBLIC_WEAK_ALIAS(kmalloc_trace, kmalloc_trace_nx);

#ifndef CONFIG_USE_SLAB_ALLOCATORS
DEFINE_PUBLIC_WEAK_ALIAS(kmalloc_noslab, kmalloc);
DEFINE_PUBLIC_WEAK_ALIAS(kmalloc_noslab_nx, kmalloc_nx);
#endif /* !CONFIG_USE_SLAB_ALLOCATORS */

DECL_END

#ifndef __INTELLISENSE__
#define MALLOC_NX 1
#include "malloc-impl.c.inl"
/**/
#include "malloc-impl.c.inl"
#endif /* !__INTELLISENSE__ */

#endif /* !GUARD_KERNEL_SRC_MEMORY_MALLOC_C */
