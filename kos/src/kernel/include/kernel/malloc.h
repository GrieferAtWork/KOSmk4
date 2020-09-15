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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_MALLOC_H
#define GUARD_KERNEL_INCLUDE_KERNEL_MALLOC_H 1

#include <kernel/compiler.h>

#include <kernel/types.h>

#include <asm/pagesize.h>

#include "malloc-defs.h"

DECL_BEGIN

#ifdef __CC__

#ifdef CONFIG_USE_SLAB_ALLOCATORS

/* Free (non-null) slab pointers. */
FUNDEF NOBLOCK NONNULL((1)) void NOTHROW(KCALL slab_free)(void *__restrict ptr);
FUNDEF NOBLOCK NONNULL((1)) void NOTHROW(KCALL slab_ffree)(void *__restrict ptr, gfp_t flags);

/* Allocate slab memory for fixed sizes.
 * If the allocation is impossible (as can happen when no free
 * slab pages are available, and mapping more is either impossible
 * due to a VM collision, or due to insufficient memory), return `NULL'.
 * In the later case, the caller should fall back to using kmalloc(), or
 * simply call the equivalent `slab_kmalloc*' function, with will do so
 * automatically. */
#define DEFINE_SLAB_ALLOCATOR_FUNCTIONS(sz, _)                                                 \
	FUNDEF NOBLOCK ATTR_MALLOC WUNUSED VIRT void *NOTHROW(KCALL slab_malloc##sz)(gfp_t flags); \
	FUNDEF ATTR_MALLOC ATTR_RETNONNULL WUNUSED VIRT void *KCALL slab_kmalloc##sz(gfp_t flags); \
	FUNDEF ATTR_MALLOC WUNUSED VIRT void *NOTHROW(KCALL slab_kmalloc_nx##sz)(gfp_t flags);
SLAB_FOREACH_SIZE(DEFINE_SLAB_ALLOCATOR_FUNCTIONS, _)
#undef DEFINE_SLAB_ALLOCATOR_FUNCTIONS


/* Slab allocators for dynamic sizes.
 * NOTE: The caller is required to ensure that `num_bytes < SLAB_MAXSIZE' */
FUNDEF NOBLOCK ATTR_MALLOC WUNUSED VIRT void *NOTHROW(KCALL __os_slab_malloc)(size_t num_bytes, gfp_t flags) ASMNAME("slab_malloc");
FUNDEF ATTR_MALLOC ATTR_RETNONNULL WUNUSED VIRT void *KCALL __os_slab_kmalloc(size_t num_bytes, gfp_t flags) ASMNAME("slab_kmalloc");
FUNDEF ATTR_MALLOC WUNUSED VIRT void *NOTHROW(KCALL __os_slab_kmalloc_nx)(size_t num_bytes, gfp_t flags) ASMNAME("slab_kmalloc_nx");

#ifndef __OMIT_SLAB_MALLOC_CONSTANT_P_WRAPPERS
FUNDEF ATTR_ERROR("Invalid slab size") void __slab_invalid_size(void);

FORCELOCAL NOBLOCK ATTR_ARTIFICIAL ATTR_MALLOC WUNUSED VIRT void *
NOTHROW(KCALL slab_malloc)(size_t num_bytes, gfp_t flags) {
	if (__builtin_constant_p(num_bytes)) {
#define SLAB_CHECK_SELECT(sz, _)  \
		if (num_bytes <= sz)      \
			return slab_malloc##sz(flags);
		SLAB_FOREACH_SIZE(SLAB_CHECK_SELECT, _)
#undef SLAB_CHECK_SELECT
		__slab_invalid_size();
	}
	return __os_slab_malloc(num_bytes, flags);
}

FORCELOCAL ATTR_ARTIFICIAL ATTR_MALLOC ATTR_RETNONNULL WUNUSED VIRT void *KCALL
slab_kmalloc(size_t num_bytes, gfp_t flags) {
	if (__builtin_constant_p(num_bytes)) {
#define SLAB_CHECK_SELECT(sz, _)  \
		if (num_bytes <= sz)      \
			return slab_kmalloc##sz(flags);
		SLAB_FOREACH_SIZE(SLAB_CHECK_SELECT, _)
#undef SLAB_CHECK_SELECT
		__slab_invalid_size();
	}
	return __os_slab_kmalloc(num_bytes, flags);
}

FORCELOCAL ATTR_ARTIFICIAL ATTR_MALLOC WUNUSED VIRT void *
NOTHROW(KCALL slab_kmalloc_nx)(size_t num_bytes, gfp_t flags) {
	if (__builtin_constant_p(num_bytes)) {
#define SLAB_CHECK_SELECT(sz, _)  \
		if (num_bytes <= sz)      \
			return slab_kmalloc_nx##sz(flags);
		SLAB_FOREACH_SIZE(SLAB_CHECK_SELECT, _)
#undef SLAB_CHECK_SELECT
		__slab_invalid_size();
	}
	return __os_slab_kmalloc_nx(num_bytes, flags);
}

#endif /* !__OMIT_SLAB_MALLOC_CONSTANT_P_WRAPPERS */
#endif /* CONFIG_USE_SLAB_ALLOCATORS */



/* Allocate/Reallocate/Free virtual kernel memory (as whole pages).
 * @throw: E_BADALLOC:   Not enough available memory.
 * @throw: E_WOULDBLOCK: The operation would have blocked. */
FUNDEF ATTR_MALLOC WUNUSED ATTR_RETNONNULL ATTR_ASSUME_ALIGNED(__ARCH_PAGESIZE) VIRT /*page-aligned*/ void *KCALL vpage_alloc(size_t num_pages, size_t alignment_in_pages, gfp_t flags);
FUNDEF ATTR_MALLOC WUNUSED ATTR_RETNONNULL ATTR_ASSUME_ALIGNED(__ARCH_PAGESIZE) VIRT /*page-aligned*/ void *KCALL vpage_alloc_untraced(size_t num_pages, size_t alignment_in_pages, gfp_t flags);
FUNDEF ATTR_MALLOC WUNUSED ATTR_ASSUME_ALIGNED(__ARCH_PAGESIZE) VIRT /*page-aligned*/ void *NOTHROW(KCALL vpage_alloc_nx)(size_t num_pages, size_t alignment_in_pages, gfp_t flags);
FUNDEF ATTR_MALLOC WUNUSED ATTR_ASSUME_ALIGNED(__ARCH_PAGESIZE) VIRT /*page-aligned*/ void *NOTHROW(KCALL vpage_alloc_untraced_nx)(size_t num_pages, size_t alignment_in_pages, gfp_t flags);
FUNDEF ATTR_RETNONNULL WUNUSED ATTR_ASSUME_ALIGNED(__ARCH_PAGESIZE) VIRT /*page-aligned*/ void *KCALL vpage_realloc(VIRT /*page-aligned*/ void *old_base, size_t old_pages, size_t new_pages, size_t alignment_in_pages, gfp_t alloc_flags, gfp_t free_flags);
FUNDEF ATTR_RETNONNULL WUNUSED ATTR_ASSUME_ALIGNED(__ARCH_PAGESIZE) VIRT /*page-aligned*/ void *KCALL vpage_realloc_untraced(VIRT /*page-aligned*/ void *old_base, size_t old_pages, size_t new_pages, size_t alignment_in_pages, gfp_t alloc_flags, gfp_t free_flags);
FUNDEF WUNUSED ATTR_ASSUME_ALIGNED(__ARCH_PAGESIZE) VIRT /*page-aligned*/ void *NOTHROW(KCALL vpage_realloc_nx)(VIRT /*page-aligned*/ void *old_base, size_t old_pages, size_t new_pages, size_t alignment_in_pages, gfp_t alloc_flags, gfp_t free_flags);
FUNDEF WUNUSED ATTR_ASSUME_ALIGNED(__ARCH_PAGESIZE) VIRT /*page-aligned*/ void *NOTHROW(KCALL vpage_realloc_untraced_nx)(VIRT /*page-aligned*/ void *old_base, size_t old_pages, size_t new_pages, size_t alignment_in_pages, gfp_t alloc_flags, gfp_t free_flags);
FUNDEF NOBLOCK void NOTHROW(KCALL vpage_free)(VIRT /*page-aligned*/ void *base, size_t num_pages);
FUNDEF NOBLOCK void NOTHROW(KCALL vpage_ffree)(VIRT /*page-aligned*/ void *base, size_t num_pages, gfp_t flags);
FUNDEF NOBLOCK void NOTHROW(KCALL vpage_free_untraced)(VIRT /*page-aligned*/ void *base, size_t num_pages);
FUNDEF NOBLOCK void NOTHROW(KCALL vpage_ffree_untraced)(VIRT /*page-aligned*/ void *base, size_t num_pages, gfp_t flags);



/* Allocate/Reallocate/Free virtual kernel memory.
 * @throw: E_BADALLOC:   Not enough available memory.
 * @throw: E_WOULDBLOCK: The operation would have blocked. */
FUNDEF ATTR_MALLOC WUNUSED ATTR_RETNONNULL VIRT void *KCALL __os_malloc(size_t n_bytes, gfp_t flags) THROWS(E_BADALLOC, E_WOULDBLOCK) ASMNAME("kmalloc");
#ifdef CONFIG_USE_SLAB_ALLOCATORS
FUNDEF ATTR_MALLOC WUNUSED ATTR_RETNONNULL VIRT void *KCALL __os_malloc_noslab(size_t n_bytes, gfp_t flags) THROWS(E_BADALLOC, E_WOULDBLOCK) ASMNAME("kmalloc_noslab");
#else /* CONFIG_USE_SLAB_ALLOCATORS */
FUNDEF ATTR_MALLOC WUNUSED ATTR_RETNONNULL VIRT void *KCALL __os_malloc_noslab(size_t n_bytes, gfp_t flags) THROWS(E_BADALLOC, E_WOULDBLOCK) ASMNAME("kmalloc");
#endif /* !CONFIG_USE_SLAB_ALLOCATORS */
FUNDEF ATTR_MALLOC WUNUSED ATTR_RETNONNULL VIRT void *KCALL __os_memalign(size_t min_alignment, size_t n_bytes, gfp_t flags) THROWS(E_BADALLOC, E_WOULDBLOCK) ASMNAME("kmemalign");
FUNDEF ATTR_MALLOC WUNUSED ATTR_RETNONNULL VIRT void *KCALL __os_memalign_offset(size_t min_alignment, ptrdiff_t offset, size_t n_bytes, gfp_t flags) THROWS(E_BADALLOC, E_WOULDBLOCK) ASMNAME("kmemalign_offset");
FUNDEF ATTR_RETNONNULL WUNUSED VIRT void *KCALL __os_realloc(VIRT void *ptr, size_t n_bytes, gfp_t flags) THROWS(E_BADALLOC, E_WOULDBLOCK) ASMNAME("krealloc");
FUNDEF ATTR_RETNONNULL WUNUSED VIRT void *KCALL __os_realign(VIRT void *ptr, size_t min_alignment, size_t n_bytes, gfp_t flags) THROWS(E_BADALLOC, E_WOULDBLOCK) ASMNAME("krealign");
FUNDEF ATTR_RETNONNULL WUNUSED VIRT void *KCALL __os_realign_offset(VIRT void *ptr, size_t min_alignment, ptrdiff_t offset, size_t n_bytes, gfp_t flags) THROWS(E_BADALLOC, E_WOULDBLOCK) ASMNAME("krealign_offset");
FUNDEF VIRT void *KCALL __os_realloc_in_place(VIRT void *ptr, size_t n_bytes, gfp_t flags) THROWS(E_BADALLOC, E_WOULDBLOCK) ASMNAME("krealloc_in_place");
FUNDEF NOBLOCK WUNUSED size_t NOTHROW(KCALL __os_malloc_usable_size)(VIRT void *ptr) ASMNAME("kmalloc_usable_size");
FUNDEF NOBLOCK void NOTHROW(KCALL __os_free)(VIRT void *ptr) ASMNAME("kfree");
FUNDEF NOBLOCK void NOTHROW(KCALL __os_ffree)(VIRT void *ptr, gfp_t flags) ASMNAME("kffree");
FUNDEF ATTR_MALLOC WUNUSED VIRT void *NOTHROW(KCALL __os_malloc_nx)(size_t n_bytes, gfp_t flags) ASMNAME("kmalloc_nx");
#ifdef CONFIG_USE_SLAB_ALLOCATORS
FUNDEF ATTR_MALLOC WUNUSED VIRT void *NOTHROW(KCALL __os_malloc_noslab_nx)(size_t n_bytes, gfp_t flags) ASMNAME("kmalloc_noslab_nx");
#else /* CONFIG_USE_SLAB_ALLOCATORS */
FUNDEF ATTR_MALLOC WUNUSED VIRT void *NOTHROW(KCALL __os_malloc_noslab_nx)(size_t n_bytes, gfp_t flags) ASMNAME("kmalloc_nx");
#endif /* !CONFIG_USE_SLAB_ALLOCATORS */
FUNDEF ATTR_MALLOC WUNUSED VIRT void *NOTHROW(KCALL __os_memalign_nx)(size_t min_alignment, size_t n_bytes, gfp_t flags) ASMNAME("kmemalign_nx");
FUNDEF ATTR_MALLOC WUNUSED VIRT void *NOTHROW(KCALL __os_memalign_offset_nx)(size_t min_alignment, ptrdiff_t offset, size_t n_bytes, gfp_t flags) ASMNAME("kmemalign_offset_nx");
FUNDEF WUNUSED VIRT void *NOTHROW(KCALL __os_realloc_nx)(VIRT void *ptr, size_t n_bytes, gfp_t flags) ASMNAME("krealloc_nx");
FUNDEF WUNUSED VIRT void *NOTHROW(KCALL __os_realign_nx)(VIRT void *ptr, size_t min_alignment, size_t n_bytes, gfp_t flags) ASMNAME("krealign_nx");
FUNDEF WUNUSED VIRT void *NOTHROW(KCALL __os_realign_offset_nx)(VIRT void *ptr, size_t min_alignment, ptrdiff_t offset, size_t n_bytes, gfp_t flags) ASMNAME("krealign_offset_nx");
FUNDEF VIRT void *NOTHROW(KCALL __os_realloc_in_place_nx)(VIRT void *ptr, size_t n_bytes, gfp_t flags) ASMNAME("krealloc_in_place_nx");

#ifndef __OMIT_KMALLOC_CONSTANT_P_WRAPPERS
#ifdef __INTELLISENSE__
ATTR_MALLOC WUNUSED ATTR_RETNONNULL VIRT void *KCALL kcalloc(size_t n_bytes, gfp_t flags) THROWS(E_BADALLOC, E_WOULDBLOCK);
ATTR_RETNONNULL WUNUSED VIRT void *KCALL krecalign(VIRT void *ptr, size_t min_alignment, size_t n_bytes, gfp_t flags) THROWS(E_BADALLOC, E_WOULDBLOCK);
ATTR_RETNONNULL WUNUSED VIRT void *KCALL krecalloc(VIRT void *ptr, size_t n_bytes, gfp_t flags) THROWS(E_BADALLOC, E_WOULDBLOCK);
VIRT void *KCALL krecalloc_in_place(VIRT void *ptr, size_t n_bytes, gfp_t flags) THROWS(E_BADALLOC, E_WOULDBLOCK);
ATTR_MALLOC WUNUSED VIRT void *NOTHROW(KCALL kcalloc_nx)(size_t n_bytes, gfp_t flags);
WUNUSED VIRT void *NOTHROW(KCALL krecalign_nx)(VIRT void *ptr, size_t min_alignment, size_t n_bytes, gfp_t flags);
WUNUSED VIRT void *NOTHROW(KCALL krecalloc_nx)(VIRT void *ptr, size_t n_bytes, gfp_t flags);
VIRT void *NOTHROW(KCALL krecalloc_in_place_nx)(VIRT void *ptr, size_t n_bytes, gfp_t flags);
#else /* __INTELLISENSE__ */
#define kcalloc(n_bytes, flags)                          kmalloc(n_bytes, (flags) | GFP_CALLOC)
#define krecalign(ptr, min_alignment, n_bytes, flags)    krealign(ptr, min_alignment, n_bytes, (flags) | GFP_CALLOC)
#define krecalloc(ptr, n_bytes, flags)                   krealloc(ptr, n_bytes, (flags) | GFP_CALLOC)
#define krecalloc_in_place(ptr, n_bytes, flags)          krealloc_in_place(ptr, n_bytes, (flags) | GFP_CALLOC)
#define kcalloc_nx(n_bytes, flags)                       kmalloc_nx(n_bytes, (flags) | GFP_CALLOC)
#define krecalign_nx(ptr, min_alignment, n_bytes, flags) krealign_nx(ptr, min_alignment, n_bytes, (flags) | GFP_CALLOC)
#define krecalloc_nx(ptr, n_bytes, flags)                krealloc_nx(ptr, n_bytes, (flags) | GFP_CALLOC)
#define krecalloc_in_place_nx(ptr, n_bytes, flags)       krealloc_in_place_nx(ptr, n_bytes, (flags) | GFP_CALLOC)
#endif /* !__INTELLISENSE__ */

FORCELOCAL ATTR_ARTIFICIAL ATTR_MALLOC WUNUSED ATTR_RETNONNULL VIRT void *KCALL
kmalloc(size_t n_bytes, gfp_t flags) THROWS(E_BADALLOC, E_WOULDBLOCK) {
	if (__builtin_constant_p(n_bytes)) {
#ifdef CONFIG_USE_SLAB_ALLOCATORS
		if (n_bytes < SLAB_MAXSIZE) {
#ifdef __OMIT_SLAB_MALLOC_CONSTANT_P_WRAPPERS
			return __os_slab_kmalloc(n_bytes, flags);
#else /* __OMIT_SLAB_MALLOC_CONSTANT_P_WRAPPERS */
			return slab_kmalloc(n_bytes, flags);
#endif /* !__OMIT_SLAB_MALLOC_CONSTANT_P_WRAPPERS */
		}
#endif /* CONFIG_USE_SLAB_ALLOCATORS */
		/* Pre-align `n_bytes' so that heap functions don't need to. */
		return __os_malloc((n_bytes + HEAP_ALIGNMENT - 1) & ~(HEAP_ALIGNMENT - 1), flags);
	}
	return __os_malloc(n_bytes, flags);
}

FORCELOCAL ATTR_ARTIFICIAL ATTR_MALLOC WUNUSED ATTR_RETNONNULL VIRT void *KCALL
kmemalign(size_t min_alignment, size_t n_bytes, gfp_t flags)
		THROWS(E_BADALLOC, E_WOULDBLOCK) {
	if (__builtin_constant_p(min_alignment) && min_alignment <= HEAP_ALIGNMENT)
		return kmalloc(n_bytes, flags);
	return __os_memalign(min_alignment, n_bytes, flags);
}

FORCELOCAL ATTR_ARTIFICIAL ATTR_MALLOC WUNUSED ATTR_RETNONNULL VIRT void *KCALL
kmemalign_offset(size_t min_alignment, ptrdiff_t offset,
                 size_t n_bytes, gfp_t flags)
		THROWS(E_BADALLOC, E_WOULDBLOCK) {
	if (__builtin_constant_p(offset) && offset == 0)
		return kmemalign(min_alignment, n_bytes, flags);
	return __os_memalign_offset(min_alignment, offset, n_bytes, flags);
}

FORCELOCAL ATTR_ARTIFICIAL ATTR_RETNONNULL WUNUSED VIRT void *KCALL
krealloc(VIRT void *ptr, size_t n_bytes, gfp_t flags)
		THROWS(E_BADALLOC, E_WOULDBLOCK) {
	if (__builtin_constant_p(ptr) && ptr == __NULLPTR)
		return kmalloc(n_bytes, flags);
	if (__builtin_constant_p(n_bytes))
		return __os_realloc(ptr, (n_bytes + HEAP_ALIGNMENT - 1) & ~(HEAP_ALIGNMENT - 1), flags);
	return __os_realloc(ptr, n_bytes, flags);
}
FORCELOCAL ATTR_ARTIFICIAL ATTR_RETNONNULL WUNUSED VIRT void *KCALL
krealign(VIRT void *ptr, size_t min_alignment, size_t n_bytes, gfp_t flags)
		THROWS(E_BADALLOC, E_WOULDBLOCK) {
	if (__builtin_constant_p(min_alignment) && min_alignment <= HEAP_ALIGNMENT)
		return krealloc(ptr, n_bytes, flags);
	if (__builtin_constant_p(ptr) && ptr == __NULLPTR)
		return kmemalign(min_alignment, n_bytes, flags);
	if (__builtin_constant_p(n_bytes))
		return __os_realign(ptr, min_alignment, (n_bytes + HEAP_ALIGNMENT - 1) & ~(HEAP_ALIGNMENT - 1), flags);
	return __os_realign(ptr, min_alignment, n_bytes, flags);
}
FORCELOCAL ATTR_ARTIFICIAL ATTR_RETNONNULL WUNUSED VIRT void *KCALL
krealign_offset(VIRT void *ptr, size_t min_alignment,
                ptrdiff_t offset, size_t n_bytes, gfp_t flags)
		THROWS(E_BADALLOC, E_WOULDBLOCK) {
	if (__builtin_constant_p(offset) && offset == 0)
		return krealign(ptr, min_alignment, n_bytes, flags);
	if (__builtin_constant_p(ptr) && ptr == __NULLPTR)
		return kmemalign_offset(min_alignment, offset, n_bytes, flags);
	if (__builtin_constant_p(n_bytes))
		return __os_realign_offset(ptr, min_alignment, offset, (n_bytes + HEAP_ALIGNMENT - 1) & ~(HEAP_ALIGNMENT - 1), flags);
	return __os_realign_offset(ptr, min_alignment, offset, n_bytes, flags);
}

FORCELOCAL ATTR_ARTIFICIAL VIRT void *KCALL
krealloc_in_place(VIRT void *ptr, size_t n_bytes, gfp_t flags)
		THROWS(E_BADALLOC, E_WOULDBLOCK) {
	if (__builtin_constant_p(ptr) && ptr == __NULLPTR)
		return kmalloc(n_bytes, flags);
	if (__builtin_constant_p(n_bytes))
		return __os_realloc_in_place(ptr, (n_bytes + HEAP_ALIGNMENT - 1) & ~(HEAP_ALIGNMENT - 1), flags);
	return __os_realloc_in_place(ptr, n_bytes, flags);
}

FORCELOCAL NOBLOCK ATTR_ARTIFICIAL WUNUSED size_t
NOTHROW(KCALL kmalloc_usable_size)(VIRT void *ptr) {
	if (__builtin_constant_p(ptr) && ptr == __NULLPTR)
		return 0;
	return __os_malloc_usable_size(ptr);
}

FORCELOCAL NOBLOCK ATTR_ARTIFICIAL void
NOTHROW(KCALL kfree)(VIRT void *ptr) {
	if (!__builtin_constant_p(ptr) || ptr != __NULLPTR)
		__os_free(ptr);
}

FORCELOCAL NOBLOCK ATTR_ARTIFICIAL void
NOTHROW(KCALL kffree)(VIRT void *ptr, gfp_t flags) {
	if (__builtin_constant_p(flags) && !(flags & (GFP_CALLOC | GFP_NOTRIM))) {
		kfree(ptr);
	} else {
		__os_ffree(ptr, flags);
	}
}


FORCELOCAL ATTR_ARTIFICIAL ATTR_MALLOC WUNUSED VIRT void *
NOTHROW(KCALL kmalloc_nx)(size_t n_bytes, gfp_t flags) {
	if (__builtin_constant_p(n_bytes)) {
#ifdef CONFIG_USE_SLAB_ALLOCATORS
		if (n_bytes < SLAB_MAXSIZE) {
#ifdef __OMIT_SLAB_MALLOC_CONSTANT_P_WRAPPERS
			return __os_slab_kmalloc_nx(n_bytes, flags);
#else /* __OMIT_SLAB_MALLOC_CONSTANT_P_WRAPPERS */
			return slab_kmalloc_nx(n_bytes, flags);
#endif /* !__OMIT_SLAB_MALLOC_CONSTANT_P_WRAPPERS */
		}
#endif /* CONFIG_USE_SLAB_ALLOCATORS */
		/* Pre-align `n_bytes' so that heap functions don't need to. */
		return __os_malloc_nx((n_bytes + HEAP_ALIGNMENT - 1) & ~(HEAP_ALIGNMENT - 1), flags);
	}
	return __os_malloc_nx(n_bytes, flags);
}

FORCELOCAL ATTR_ARTIFICIAL ATTR_MALLOC WUNUSED VIRT void *
NOTHROW(KCALL kmemalign_nx)(size_t min_alignment,
                            size_t n_bytes, gfp_t flags) {
	if (__builtin_constant_p(min_alignment) && min_alignment <= HEAP_ALIGNMENT)
		return kmalloc_nx(n_bytes, flags);
	return __os_memalign_nx(min_alignment, n_bytes, flags);
}

FORCELOCAL ATTR_ARTIFICIAL ATTR_MALLOC WUNUSED VIRT void *
NOTHROW(KCALL kmemalign_offset_nx)(size_t min_alignment, ptrdiff_t offset,
                                   size_t n_bytes, gfp_t flags) {
	if (__builtin_constant_p(offset) && offset == 0)
		return kmemalign_nx(min_alignment, n_bytes, flags);
	return __os_memalign_offset_nx(min_alignment, offset, n_bytes, flags);
}

FORCELOCAL ATTR_ARTIFICIAL WUNUSED VIRT void *
NOTHROW(KCALL krealloc_nx)(VIRT void *ptr, size_t n_bytes, gfp_t flags) {
	if (__builtin_constant_p(ptr) && ptr == __NULLPTR)
		return kmalloc_nx(n_bytes, flags);
	if (__builtin_constant_p(n_bytes))
		return __os_realloc_nx(ptr, (n_bytes + HEAP_ALIGNMENT - 1) & ~(HEAP_ALIGNMENT - 1), flags);
	return __os_realloc_nx(ptr, n_bytes, flags);
}

FORCELOCAL ATTR_ARTIFICIAL WUNUSED VIRT void *
NOTHROW(KCALL krealign_nx)(VIRT void *ptr, size_t min_alignment,
                           size_t n_bytes, gfp_t flags) {
	if (__builtin_constant_p(min_alignment) && min_alignment <= HEAP_ALIGNMENT)
		return krealloc_nx(ptr, n_bytes, flags);
	if (__builtin_constant_p(ptr) && ptr == __NULLPTR)
		return kmemalign_nx(min_alignment, n_bytes, flags);
	if (__builtin_constant_p(n_bytes))
		return __os_realign_nx(ptr, min_alignment, (n_bytes + HEAP_ALIGNMENT - 1) & ~(HEAP_ALIGNMENT - 1), flags);
	return __os_realign_nx(ptr, min_alignment, n_bytes, flags);
}

FORCELOCAL ATTR_ARTIFICIAL WUNUSED VIRT void *
NOTHROW(KCALL krealign_offset_nx)(VIRT void *ptr, size_t min_alignment,
                                  ptrdiff_t offset, size_t n_bytes, gfp_t flags) {
	if (__builtin_constant_p(offset) && offset == 0)
		return krealign_nx(ptr, min_alignment, n_bytes, flags);
	if (__builtin_constant_p(ptr) && ptr == __NULLPTR)
		return kmemalign_offset_nx(min_alignment, offset, n_bytes, flags);
	if (__builtin_constant_p(n_bytes))
		return __os_realign_offset_nx(ptr, min_alignment, offset, (n_bytes + HEAP_ALIGNMENT - 1) & ~(HEAP_ALIGNMENT - 1), flags);
	return __os_realign_offset_nx(ptr, min_alignment, offset, n_bytes, flags);
}

FORCELOCAL ATTR_ARTIFICIAL VIRT void *
NOTHROW(KCALL krealloc_in_place_nx)(VIRT void *ptr, size_t n_bytes, gfp_t flags) {
	if (__builtin_constant_p(ptr) && ptr == __NULLPTR)
		return kmalloc_nx(n_bytes, flags);
	if (__builtin_constant_p(n_bytes))
		return __os_realloc_in_place_nx(ptr, (n_bytes + HEAP_ALIGNMENT - 1) & ~(HEAP_ALIGNMENT - 1), flags);
	return __os_realloc_in_place_nx(ptr, n_bytes, flags);
}

#endif /* !__OMIT_KMALLOC_CONSTANT_P_WRAPPERS */


#ifdef CONFIG_DEBUG_MALLOC
#ifdef __CC__
/* Search for and dump kernel memory leaks,
 * returning the number of encountered leaks.
 * @throws: E_WOULDBLOCK: `GFP_ATOMIC' was not given, preemption was
 *                        disabled, and the operation would have blocked.
 */
FUNDEF NOBLOCK_IF(flags & GFP_ATOMIC) size_t KCALL
mall_dump_leaks(gfp_t flags) THROWS(E_WOULDBLOCK);

/* Validate padding surrounding heap pointers to check if
 * memory has been written past allocated end addresses.  */
FUNDEF NOBLOCK void NOTHROW(KCALL mall_validate_padding)(void);

/* Add/Remove a given address range as a valid tracing junction:
 *   - Tracing junctions are blocks of memory which may contain
 *     points to other tracing junction, or regular mall-pointers.
 *   - When searching for leaked data blocks, KOS will dereference
 *     mall-pointers that are referenced in some way by any active
 *     component of the operating system:
 *       - Pointers found in general purpose registers of any
 *         running thread (if preempted while in the kernel)
 *       - Pointers found in the used part of the kernel stack
 *         of any running thread
 *       - Pointers found in writable global variables (.data & .bss)
 *     The definition of a pointer is as follows:
 *       - Points into the kernel-share segment (only required for `GFP_SHARED' heap pointers)
 *       - Dereferencable (memory is mapped where it points to)
 *       - Is aligned by at least `sizeof(void *)'
 *     The definition of a mall-pointer is as follows:
 *       - Points into the usable memory portion of any kmalloc()-allocated
 *         data block (including leading and trailing padding data used to
 *         verify write-past-the-end errors using `mall_validate_padding()')
 *   - This is all well and good, and the kernel can easily detect
 *     leaked memory by recursively traversing all allocated memory
 *     in search of pointers to other allocated memory blocks.
 *     The fact that memory is pre-initialized to a consistent
 *     debug state when `CONFIG_DEBUG_HEAP' is enabled makes this
 *     even easier.
 *     However the problem comes when code uses custom allocators
 *     that make use of the `heap_alloc()' API.
 *     Since the mall API is built ontop of that API, there is no
 *     connection that points back to the heap API and would allow
 *     the MALL GC checker to differentiate between some random data
 *     word, and a pointer that is directed into a data block of some
 *     specific length, which in itself is allowed to hold pointers to
 *     other data blocks, some of which are allowed to be other mall
 *     blocks.
 *     However despite the fact that it might seem obvious to the programmer
 *     that a data block allocated using `heap_alloc_u()' should be able to
 *     hold pointers to data blocks allocated using `kmalloc()', this is
 *     not the case (out of the box), because again: the MALL GC checker
 *     would not be able to know what (if any) memory pointed to by that
 *     data block can carry GC-able pointers.
 *   - The solution is to use this function pair to inform mall about
 *     some custom data block that can be used during traversable of
 *     reachable memory.
 *     If itself reachable (through the means described above), that data
 *     block will be analyzed just like any other data block allocated
 *     using `kmalloc()' would have been.
 *     Additionally, if not reachable during MALL GC search, the data
 *     block will be dumped as a leak alongside a traceback to the
 *     call to `mall_trace()' that registered that data block.
 *   - Be sure to use `mall_untrace()' to delete the data block once
 *     it should no longer act as a proxy (usually just before a call
 *     to `heap_free_untraced()'), by passing the address of any pointer that
 *     is considered to be part of that block `>= base && < base+num_bytes'.
 *     Usually, you'll just be passing `base', as `heap_free_untraced()' will
 *     be needing that same pointer from you.
 *    (Or just use `heap_free()' to have that be done automatically for you)
 * @return: base: Successfully started tracing the given pointer.
 * @return: NULL: Pointer tracing failed (not enough available memory) */
FUNDEF NOBLOCK_IF(flags & GFP_ATOMIC) ATTR_RETNONNULL void *KCALL mall_trace(void *base, size_t num_bytes, gfp_t flags) THROWS(E_BADALLOC, E_WOULDBLOCK);
FUNDEF NOBLOCK_IF(flags & GFP_ATOMIC) void *NOTHROW(KCALL mall_trace_nx)(void *base, size_t num_bytes, gfp_t flags);
FUNDEF NOBLOCK_IF(flags & GFP_ATOMIC) void NOTHROW(KCALL mall_print_traceback)(void *ptr, gfp_t flags);
FUNDEF NOBLOCK_IF(flags & GFP_ATOMIC) void NOTHROW(KCALL mall_untrace)(void *ptr, gfp_t flags);
FUNDEF NOBLOCK_IF(flags & GFP_ATOMIC) void NOTHROW(KCALL mall_untrace_n)(void *ptr, size_t num_bytes, gfp_t flags);

#endif /* __CC__ */
#define ATTR_MALL_UNTRACKED ATTR_SECTION(".bss.mall.untracked")
#else /* CONFIG_DEBUG_MALLOC */
#ifdef __CC__
#define mall_dump_leaks(flags)              0
#define mall_validate_padding()             (void)0
#define mall_trace(base, num_bytes, flags)  (base)
#define mall_print_traceback(ptr, flags)    (void)0
#define mall_untrace(ptr, flags)            (void)0
#define mall_untrace_n(ptr, n_bytes, flags) (void)0
#endif /* __CC__ */
#define ATTR_MALL_UNTRACKED ATTR_SECTION(".bss")
#endif /* !CONFIG_DEBUG_MALLOC */


#ifdef __cplusplus
extern "C++" {
__NAMESPACE_INT_BEGIN
class _finally_kfree {
private:
	void *&m_ptr;
public:
	NOBLOCK _finally_kfree(void *&p) __CXX_NOEXCEPT: m_ptr(p) {}
#ifndef __OMIT_KMALLOC_CONSTANT_P_WRAPPERS
	NOBLOCK ~_finally_kfree() __CXX_NOEXCEPT { kfree(m_ptr); }
#else
	NOBLOCK ~_finally_kfree() __CXX_NOEXCEPT { __os_free(m_ptr); }
#endif
};
__NAMESPACE_INT_END
}
#define FINALLY_KFREE(ptr) __NAMESPACE_INT_SYM _finally_kfree __COMPILER_UNIQUE(__fkfptr)(ptr)
#endif /* __cplusplus */

#endif /* __CC__ */


DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_MALLOC_H */
