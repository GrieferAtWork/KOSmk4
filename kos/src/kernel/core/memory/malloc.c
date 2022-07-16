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
#ifndef GUARD_KERNEL_SRC_MEMORY_MALLOC_C
#define GUARD_KERNEL_SRC_MEMORY_MALLOC_C 1
#define NO_INSTRUMENT_KMALLOC
#define __OMIT_KMALLOC_CONSTANT_P_WRAPPERS
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

/**/
#include "malloc.h"

DECL_BEGIN

#if HEAP_ALIGNMENT < (__SIZEOF_SIZE_T__ + 1)
struct ATTR_PACKED mptr {
	uintptr_t mp_data; /* Size and heap of the mptr. */
};
static_assert(sizeof(struct mptr) == HEAP_ALIGNMENT);
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
static_assert(sizeof(struct mptr) == HEAP_ALIGNMENT);

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


INTERN WUNUSED size_t
NOTHROW(KCALL untraced_kmalloc_usable_size)(VIRT void *ptr) {
	struct mptr *mblock;
	if (!ptr)
		return 0;
#ifdef CONFIG_HAVE_KERNEL_SLAB_ALLOCATORS
	if (KERNEL_SLAB_CHECKPTR(ptr))
		return SLAB_GET(ptr)->s_size;
#endif /* CONFIG_HAVE_KERNEL_SLAB_ALLOCATORS */
	assert(IS_ALIGNED((uintptr_t)ptr, HEAP_ALIGNMENT));
	mblock = mptr_get(ptr);
	mptr_assert(mblock);
	return mptr_size(mblock) - sizeof(struct mptr);
}

INTERN void
NOTHROW(KCALL untraced_kfree)(VIRT void *ptr) {
	struct mptr *mblock;
	if (!ptr)
		return; /* Ignore NULL-pointers. */
#ifdef CONFIG_HAVE_KERNEL_SLAB_ALLOCATORS
	if (KERNEL_SLAB_CHECKPTR(ptr)) {
		slab_free(ptr);
		return;
	}
#endif /* CONFIG_HAVE_KERNEL_SLAB_ALLOCATORS */
	assert(IS_ALIGNED((uintptr_t)ptr, HEAP_ALIGNMENT));
	mblock = mptr_get(ptr);
	mptr_assert(mblock);
	heap_free_untraced(mptr_heap(mblock), mblock,
	                   mptr_size(mblock), mptr_heap_gfp(mblock));
}

INTERN void
NOTHROW(KCALL untraced_kffree)(VIRT void *ptr, gfp_t flags) {
	struct mptr *mblock;
	if (!ptr)
		return; /* Ignore NULL-pointers. */
#ifdef CONFIG_HAVE_KERNEL_SLAB_ALLOCATORS
	if (KERNEL_SLAB_CHECKPTR(ptr)) {
		slab_ffree(ptr, flags);
		return;
	}
#endif /* CONFIG_HAVE_KERNEL_SLAB_ALLOCATORS */
	assert(IS_ALIGNED((uintptr_t)ptr, HEAP_ALIGNMENT));
	mblock = mptr_get(ptr);
	mptr_assert(mblock);
	heap_free_untraced(mptr_heap(mblock),
	                   mblock, mptr_size(mblock),
	                   mptr_heap_gfp(mblock) |
	                   (flags & ~__GFP_HEAPMASK));
}


INTERN NOBLOCK void
NOTHROW(KCALL untraced_kmalloc_validate)(void) {
}

INTERN ATTR_CONST size_t KCALL
untraced_kmalloc_leaks(void) THROWS(E_WOULDBLOCK) {
	return 0;
}

INTERN ATTR_CONST kmalloc_leaks_t KCALL
untraced_kmalloc_leaks_collect(void) THROWS(E_WOULDBLOCK) {
	return NULL;
}

INTERN ATTR_CONST ssize_t KCALL
untraced_kmalloc_leaks_print(kmalloc_leaks_t UNUSED(leaks),
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
INTERN NOBLOCK ATTR_CONST WUNUSED size_t
NOTHROW(KCALL untraced_kmalloc_leaks_count)(kmalloc_leaks_t UNUSED(leaks)) {
	return 0;
}

INTERN NOBLOCK ATTR_CONST memleak_t
NOTHROW(FCALL untraced_memleak_next)(kmalloc_leaks_t UNUSED(leaks),
                                     memleak_t UNUSED(prev)) {
	return NULL;
}
DEFINE_INTERN_ALIAS(untraced_memleak_getattr, untraced_memleak_next);
#pragma GCC diagnostic pop


INTERN NOBLOCK void
NOTHROW(KCALL untraced_kmalloc_leaks_release)(kmalloc_leaks_t UNUSED(leaks),
                                              unsigned int UNUSED(now)) {
}

INTERN ATTR_CONST NOBLOCK_IF(gfp & GFP_ATOMIC) WUNUSED void *
NOTHROW(KCALL untraced_kmalloc_trace_nx)(void *base, size_t UNUSED(num_bytes),
                                         gfp_t UNUSED(gfp), unsigned int UNUSED(tb_skip)) {
	return base;
}

INTERN NOBLOCK ATTR_CONST void
NOTHROW(KCALL untraced_kmalloc_untrace)(void *UNUSED(ptr)) {
}

INTERN NOBLOCK ATTR_CONST void
NOTHROW(KCALL untraced_kmalloc_untrace_n)(void *UNUSED(ptr),
                                          size_t UNUSED(num_bytes)) {
}

INTERN NOBLOCK ATTR_CONST size_t
NOTHROW(KCALL untraced_kmalloc_traceback)(void *UNUSED(ptr),
                                          /*out*/ void **UNUSED(tb),
                                          size_t UNUSED(buflen),
                                          pid_t *UNUSED(p_alloc_roottid)) {
	return 0;
}


INTERN NOBLOCK ATTR_CONST ssize_t KCALL
untraced_kmalloc_printtrace(void *UNUSED(ptr),
                            __pformatprinter UNUSED(printer),
                            void *UNUSED(arg)) {
	return 0;
}


DEFINE_INTERN_ALIAS(untraced_kmalloc_trace, untraced_kmalloc_trace_nx);
#ifndef CONFIG_HAVE_KERNEL_SLAB_ALLOCATORS
DEFINE_INTERN_ALIAS(untraced_kmalloc_noslab, untraced_kmalloc);
DEFINE_INTERN_ALIAS(untraced_kmalloc_noslab_nx, untraced_kmalloc_nx);
#endif /* !CONFIG_HAVE_KERNEL_SLAB_ALLOCATORS */

DECL_END

#ifndef __INTELLISENSE__
#define DEFINE_MALLOC_NX
#include "malloc-impl.c.inl"
/**/
#include "malloc-impl.c.inl"
#endif /* !__INTELLISENSE__ */

#include <asm/redirect.h>
#ifdef CONFIG_HAVE_KERNEL_TRACE_MALLOC
#include <kernel/driver-param.h>
#endif /* CONFIG_HAVE_KERNEL_TRACE_MALLOC */

DECL_BEGIN

/* Export the untraced malloc API */
#define MALLOC_EXPORT_TABLE(cb)                               \
	cb(kmalloc_usable_size, untraced_kmalloc_usable_size)     \
	cb(kfree, untraced_kfree)                                 \
	cb(kffree, untraced_kffree)                               \
	cb(kmalloc_validate, untraced_kmalloc_validate)           \
	cb(kmalloc_leaks, untraced_kmalloc_leaks)                 \
	cb(kmalloc_leaks_collect, untraced_kmalloc_leaks_collect) \
	cb(kmalloc_leaks_print, untraced_kmalloc_leaks_print)     \
	cb(kmalloc_leaks_count, untraced_kmalloc_leaks_count)     \
	cb(memleak_next, untraced_memleak_next)                   \
	cb(memleak_getattr, untraced_memleak_getattr)             \
	cb(kmalloc_leaks_release, untraced_kmalloc_leaks_release) \
	cb(kmalloc_trace_nx, untraced_kmalloc_trace_nx)           \
	cb(kmalloc_trace, untraced_kmalloc_trace)                 \
	cb(kmalloc_untrace, untraced_kmalloc_untrace)             \
	cb(kmalloc_untrace_n, untraced_kmalloc_untrace_n)         \
	cb(kmalloc_traceback, untraced_kmalloc_traceback)         \
	cb(kmalloc_printtrace, untraced_kmalloc_printtrace)       \
	cb(kmalloc_noslab, untraced_kmalloc_noslab)               \
	cb(kmalloc_noslab_nx, untraced_kmalloc_noslab_nx)         \
	cb(kmalloc, untraced_kmalloc)                             \
	cb(kmalloc_nx, untraced_kmalloc_nx)                       \
	cb(kmemalign, untraced_kmemalign)                         \
	cb(kmemalign_nx, untraced_kmemalign_nx)                   \
	cb(kmemalign_offset, untraced_kmemalign_offset)           \
	cb(kmemalign_offset_nx, untraced_kmemalign_offset_nx)     \
	cb(krealloc_in_place, untraced_krealloc_in_place)         \
	cb(krealloc_in_place_nx, untraced_krealloc_in_place_nx)   \
	cb(krealloc, untraced_krealloc)                           \
	cb(krealloc_nx, untraced_krealloc_nx)                     \
	cb(krealign, untraced_krealign)                           \
	cb(krealign_nx, untraced_krealign_nx)                     \
	cb(krealign_offset, untraced_krealign_offset)             \
	cb(krealign_offset_nx, untraced_krealign_offset_nx)

/* Define public symbols for untraced malloc functions. */
#ifdef CONFIG_HAVE_KERNEL_TRACE_MALLOC
#define EXPORT(new, old) DEFINE_PUBLIC_WEAK_ALIAS(new, old); /* Allow override from "trace-malloc.c" */
#else /* CONFIG_HAVE_KERNEL_TRACE_MALLOC */
#define EXPORT(new, old) DEFINE_PUBLIC_ALIAS(new, old);
#endif /* !CONFIG_HAVE_KERNEL_TRACE_MALLOC */
MALLOC_EXPORT_TABLE(EXPORT)
#undef EXPORT


#ifdef CONFIG_HAVE_KERNEL_TRACE_MALLOC
#if __ARCH_REDIRECT_MAXBYTES != 0

/* No-op replacements for `heap_validate()' and `heap_validate_all()' */
PRIVATE NOBLOCK void
NOTHROW(KCALL noop_heap_validate_all)(void) {
}
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL noop_heap_validate)(struct heap *__restrict UNUSED(self)) {
}


/* Override traced heap functions with their untraced counterparts. */
#define HEAP_OVERRIDE_TABLE(cb)                   \
	cb(heap_alloc, heap_alloc_untraced)           \
	cb(heap_align, heap_align_untraced)           \
	cb(heap_allat, heap_allat_untraced)           \
	cb(heap_alloc_nx, heap_alloc_untraced_nx)     \
	cb(heap_align_nx, heap_align_untraced_nx)     \
	cb(heap_allat_nx, heap_allat_untraced_nx)     \
	cb(heap_realloc_nx, heap_realloc_untraced_nx) \
	cb(heap_realign_nx, heap_realign_untraced_nx) \
	cb(heap_free, heap_free_untraced)             \
	cb(heap_truncate, heap_truncate_untraced)     \
	cb(heap_realloc, heap_realloc_untraced)       \
	cb(heap_realign, heap_realign_untraced)


#define DEFINE_NORMAL_SYMBOL(name, untraced_name) \
	extern byte_t __##name[] ASMNAME(#name);
MALLOC_EXPORT_TABLE(DEFINE_NORMAL_SYMBOL)
#undef DEFINE_NORMAL_SYMBOL
#define DEFINE_NORMAL_SYMBOL(name, untraced_name) \
	extern byte_t __##name[] ASMNAME(#name);      \
	extern byte_t __##untraced_name[] ASMNAME(#untraced_name);
HEAP_OVERRIDE_TABLE(DEFINE_NORMAL_SYMBOL)
#undef DEFINE_NORMAL_SYMBOL

PRIVATE ATTR_FREERODATA void *const trace_malloc_overrides[][2] = {
#define OVERRIDE(name, untraced_name) { __##name, (void *)&untraced_name },
	MALLOC_EXPORT_TABLE(OVERRIDE)
#undef OVERRIDE
#define OVERRIDE(name, untraced_name) { __##name, __##untraced_name },
	HEAP_OVERRIDE_TABLE(OVERRIDE)
#undef OVERRIDE

	/* `heap_validate_all()' takes up quite a bit of execution time, since
	 * it  has  to scan  a  whole bunch  of  memory for  potential faults.
	 * By overriding it to become a no-op, we can speed up execution  time
	 * of kernel builds with this feature enabled by quite a lot. */
	{ (void *)&heap_validate_all, (void *)&noop_heap_validate_all },
	{ (void *)&heap_validate, (void *)&noop_heap_validate },
};

/* Kernel commandline option handler to disable trace-malloc */
PRIVATE ATTR_USED ATTR_FREETEXT void KCALL
kernel_disable_trace_malloc(void) {
	unsigned int i;

	/* Redirect malloc functions to their untraced counterparts. */
	for (i = 0; i < COMPILER_LENOF(trace_malloc_overrides); ++i) {
		void *from = trace_malloc_overrides[i][0];
		void *to   = trace_malloc_overrides[i][1];
		if (from != to)
			__arch_redirect(from, to);
	}
}

DEFINE_VERY_EARLY_KERNEL_COMMANDLINE_OPTION(kernel_disable_trace_malloc,
                                            KERNEL_COMMANDLINE_OPTION_TYPE_PRESENT,
                                            "nomall");
#endif /* __ARCH_REDIRECT_MAXBYTES != 0 */
#endif /* CONFIG_HAVE_KERNEL_TRACE_MALLOC */

DECL_END

#endif /* !GUARD_KERNEL_SRC_MEMORY_MALLOC_C */
