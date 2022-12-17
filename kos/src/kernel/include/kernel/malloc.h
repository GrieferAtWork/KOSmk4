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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_MALLOC_H
#define GUARD_KERNEL_INCLUDE_KERNEL_MALLOC_H 1

#include <kernel/compiler.h>

#include <kernel/types.h>

#include <asm/pagesize.h>
#include <bits/crt/format-printer.h>

#include "malloc-defs.h"

#ifdef __CC__
DECL_BEGIN

#if defined(__clang_tidy__) && !defined(NO_INSTRUMENT_KMALLOC)
#ifndef ____os_free_defined
#define ____os_free_defined
#define __os_free __builtin_free
#endif /* !____os_free_defined */
#define kcalloc(n_bytes, flags)                          kmalloc(n_bytes, (flags) | GFP_CALLOC)
#define krecalign(ptr, min_alignment, n_bytes, flags)    krealign(ptr, min_alignment, n_bytes, (flags) | GFP_CALLOC)
#define krecalloc(ptr, n_bytes, flags)                   krealloc(ptr, n_bytes, (flags) | GFP_CALLOC)
#define krecalloc_in_place(ptr, n_bytes, flags)          krealloc_in_place(ptr, n_bytes, (flags) | GFP_CALLOC)
#define kcalloc_nx(n_bytes, flags)                       kmalloc_nx(n_bytes, (flags) | GFP_CALLOC)
#define krecalign_nx(ptr, min_alignment, n_bytes, flags) krealign_nx(ptr, min_alignment, n_bytes, (flags) | GFP_CALLOC)
#define krecalloc_nx(ptr, n_bytes, flags)                krealloc_nx(ptr, n_bytes, (flags) | GFP_CALLOC)
#define krecalloc_in_place_nx(ptr, n_bytes, flags)       krealloc_in_place_nx(ptr, n_bytes, (flags) | GFP_CALLOC)
#define kfree_unlikely(ptr)                              kfree(ptr)
#ifdef CONFIG_HAVE_KERNEL_SLAB_ALLOCATORS
#define slab_free            kfree
#define slab_ffree           kffree
#define __os_slab_malloc     kmalloc
#define __os_slab_kmalloc_nx kmalloc_nx
#define slab_malloc          kmalloc
#define slab_kmalloc         kmalloc
#define slab_kmalloc_nx      kmalloc_nx
#endif /* CONFIG_HAVE_KERNEL_SLAB_ALLOCATORS */
#define __os_malloc              kmalloc
#define __os_malloc_noslab       kmalloc
#define __os_memalign            kmemalign
#define __os_memalign_offset     kmemalign_offset
#define __os_realloc             krealloc
#define __os_realign             krealign
#define __os_realign_offset      krealign_offset
#define __os_realloc_in_place    krealloc_in_place
#define __os_malloc_usable_size  kmalloc_usable_size
#define __os_ffree               kffree
#define __os_malloc_nx           kmalloc_nx
#define __os_malloc_noslab_nx    kmalloc_nx
#define __os_memalign_nx         kmemalign_nx
#define __os_memalign_offset_nx  kmemalign_offset_nx
#define __os_realloc_nx          krealloc_nx
#define __os_realign_nx          krealign_nx
#define __os_realign_offset_nx   krealign_offset_nx
#define __os_realloc_in_place_nx krealloc_in_place_nx
#define kmalloc(n_bytes, flags) \
	((flags) & GFP_CALLOC ? __builtin_calloc(n_bytes, 1) : __builtin_malloc(n_bytes))
#define krealloc(ptr, n_bytes, flags) \
	((void)(flags), __builtin_realloc(ptr, n_bytes))
#define krealloc_in_place(ptr, n_bytes, flags) \
	((void)(flags), __builtin_realloc_in_place(ptr, n_bytes))
#define kfree(ptr) \
	__builtin_free(ptr)
#define kmalloc_usable_size(ptr) \
	__builtin_malloc_usable_size(ptr)

#define kmemalign(min_alignment, n_bytes, flags) \
	((void)(min_alignment), kmalloc(n_bytes, flags))
#define kmemalign_offset(min_alignment, offset, n_bytes, flags) \
	((void)(min_alignment), (void)(offset), kmalloc(n_bytes, flags))
#define krealign(ptr, min_alignment, n_bytes, flags) \
	((void)(min_alignment), krealloc(ptr, n_bytes, flags))
#define krealign_offset(ptr, min_alignment, offset, n_bytes, flags) \
	((void)(min_alignment), (void)(offset), krealloc(ptr, n_bytes, flags))
#define kffree(ptr, flags) \
	((void)(flags), kfree(ptr))
#define kmalloc_nx(n_bytes, flags) \
	kmalloc(n_bytes, flags)
#define kmemalign_nx(min_alignment, n_bytes, flags) \
	kmemalign(min_alignment, n_bytes, flags)
#define kmemalign_offset_nx(min_alignment, offset, n_bytes, flags) \
	kmemalign_offset(min_alignment, offset, n_bytes, flags)
#define krealloc_nx(ptr, n_bytes, flags) \
	krealloc(ptr, n_bytes, flags)
#define krealign_nx(ptr, min_alignment, n_bytes, flags) \
	krealign(ptr, min_alignment, n_bytes, flags)
#define krealign_offset_nx(ptr, min_alignment, offset, n_bytes, flags) \
	krealign_offset(ptr, min_alignment, offset, n_bytes, flags)
#define krealloc_in_place_nx(ptr, n_bytes, flags) \
	krealloc_in_place(ptr, n_bytes, flags)

#else /* __clang_tidy__ && !NO_INSTRUMENT_KMALLOC */

#ifdef CONFIG_HAVE_KERNEL_SLAB_ALLOCATORS

/* Free (non-null) slab pointers. */
FUNDEF NOBLOCK NONNULL((1)) void NOTHROW(KCALL slab_free)(void *__restrict ptr);
FUNDEF NOBLOCK NONNULL((1)) void NOTHROW(KCALL slab_ffree)(void *__restrict ptr, gfp_t flags);

/* Allocate slab memory for fixed sizes.
 * If  the  allocation  is  impossible  (as  can  happen  when  no  free
 * slab  pages  are available,  and  mapping more  is  either impossible
 * due to a VM collision, or due to insufficient memory), return `NULL'.
 * In the later case, the caller should fall back to using kmalloc(), or
 * simply call the equivalent `slab_kmalloc*' function, with will do  so
 * automatically. */
#define DEFINE_SLAB_ALLOCATOR_FUNCTIONS(sz, _)                                                 \
	FUNDEF NOBLOCK ATTR_MALLOC WUNUSED VIRT void *NOTHROW(KCALL slab_malloc##sz)(gfp_t flags); \
	FUNDEF ATTR_MALLOC ATTR_RETNONNULL WUNUSED VIRT void *KCALL slab_kmalloc##sz(gfp_t flags); \
	FUNDEF ATTR_MALLOC WUNUSED VIRT void *NOTHROW(KCALL slab_kmalloc_nx##sz)(gfp_t flags);
SLAB_FOREACH_SIZE(DEFINE_SLAB_ALLOCATOR_FUNCTIONS, _)
#undef DEFINE_SLAB_ALLOCATOR_FUNCTIONS


/* Slab allocators for dynamic sizes.
 * NOTE: The caller is required to ensure that `num_bytes < CONFIG_KERNEL_SLAB_MAXSIZE' */
FUNDEF NOBLOCK ATTR_MALLOC WUNUSED VIRT void *NOTHROW(KCALL __os_slab_malloc)(size_t num_bytes, gfp_t flags) ASMNAME("slab_malloc");
FUNDEF ATTR_MALLOC ATTR_RETNONNULL WUNUSED VIRT void *KCALL __os_slab_kmalloc(size_t num_bytes, gfp_t flags) ASMNAME("slab_kmalloc");
FUNDEF ATTR_MALLOC WUNUSED VIRT void *NOTHROW(KCALL __os_slab_kmalloc_nx)(size_t num_bytes, gfp_t flags) ASMNAME("slab_kmalloc_nx");

#ifndef __OMIT_SLAB_MALLOC_CONSTANT_P_WRAPPERS
FUNDEF ATTR_ERROR("Invalid slab size") void __slab_invalid_size(void);

FORCELOCAL NOBLOCK ATTR_ARTIFICIAL ATTR_MALLOC WUNUSED VIRT void *
NOTHROW(KCALL slab_malloc)(size_t num_bytes, gfp_t flags) {
	if (__builtin_constant_p(num_bytes)) {
#define _SLAB_CHECK_SELECT(sz, _) \
		if (num_bytes <= sz)      \
			return slab_malloc##sz(flags);
		SLAB_FOREACH_SIZE(_SLAB_CHECK_SELECT, _)
#undef _SLAB_CHECK_SELECT
		__slab_invalid_size();
	}
	return __os_slab_malloc(num_bytes, flags);
}

FORCELOCAL ATTR_ARTIFICIAL ATTR_MALLOC ATTR_RETNONNULL WUNUSED VIRT void *KCALL
slab_kmalloc(size_t num_bytes, gfp_t flags) {
	if (__builtin_constant_p(num_bytes)) {
#define _SLAB_CHECK_SELECT(sz, _) \
		if (num_bytes <= sz)      \
			return slab_kmalloc##sz(flags);
		SLAB_FOREACH_SIZE(_SLAB_CHECK_SELECT, _)
#undef _SLAB_CHECK_SELECT
		__slab_invalid_size();
	}
	return __os_slab_kmalloc(num_bytes, flags);
}

FORCELOCAL ATTR_ARTIFICIAL ATTR_MALLOC WUNUSED VIRT void *
NOTHROW(KCALL slab_kmalloc_nx)(size_t num_bytes, gfp_t flags) {
	if (__builtin_constant_p(num_bytes)) {
#define _SLAB_CHECK_SELECT(sz, _) \
		if (num_bytes <= sz)      \
			return slab_kmalloc_nx##sz(flags);
		SLAB_FOREACH_SIZE(_SLAB_CHECK_SELECT, _)
#undef _SLAB_CHECK_SELECT
		__slab_invalid_size();
	}
	return __os_slab_kmalloc_nx(num_bytes, flags);
}
#endif /* !__OMIT_SLAB_MALLOC_CONSTANT_P_WRAPPERS */
#endif /* CONFIG_HAVE_KERNEL_SLAB_ALLOCATORS */



/* Allocate/Reallocate/Free virtual kernel memory.
 * @throw: E_BADALLOC:   Not enough available memory.
 * @throw: E_WOULDBLOCK: The operation would have blocked. (implied) */
FUNDEF ATTR_MALLOC ATTR_RETNONNULL WUNUSED VIRT void *KCALL __os_malloc(size_t n_bytes, gfp_t flags) THROWS(E_BADALLOC) ASMNAME("kmalloc");
#ifdef CONFIG_HAVE_KERNEL_SLAB_ALLOCATORS
FUNDEF ATTR_MALLOC ATTR_RETNONNULL WUNUSED VIRT void *KCALL __os_malloc_noslab(size_t n_bytes, gfp_t flags) THROWS(E_BADALLOC) ASMNAME("kmalloc_noslab");
#else /* CONFIG_HAVE_KERNEL_SLAB_ALLOCATORS */
FUNDEF ATTR_MALLOC ATTR_RETNONNULL WUNUSED VIRT void *KCALL __os_malloc_noslab(size_t n_bytes, gfp_t flags) THROWS(E_BADALLOC) ASMNAME("kmalloc");
#endif /* !CONFIG_HAVE_KERNEL_SLAB_ALLOCATORS */
FUNDEF ATTR_MALLOC ATTR_RETNONNULL WUNUSED VIRT void *KCALL __os_memalign(size_t min_alignment, size_t n_bytes, gfp_t flags) THROWS(E_BADALLOC) ASMNAME("kmemalign");
FUNDEF ATTR_MALLOC ATTR_RETNONNULL WUNUSED VIRT void *KCALL __os_memalign_offset(size_t min_alignment, ptrdiff_t offset, size_t n_bytes, gfp_t flags) THROWS(E_BADALLOC) ASMNAME("kmemalign_offset");
FUNDEF ATTR_RETNONNULL WUNUSED VIRT void *KCALL __os_realloc(VIRT void *ptr, size_t n_bytes, gfp_t flags) THROWS(E_BADALLOC) ASMNAME("krealloc");
FUNDEF ATTR_RETNONNULL WUNUSED VIRT void *KCALL __os_realign(VIRT void *ptr, size_t min_alignment, size_t n_bytes, gfp_t flags) THROWS(E_BADALLOC) ASMNAME("krealign");
FUNDEF ATTR_RETNONNULL WUNUSED VIRT void *KCALL __os_realign_offset(VIRT void *ptr, size_t min_alignment, ptrdiff_t offset, size_t n_bytes, gfp_t flags) THROWS(E_BADALLOC) ASMNAME("krealign_offset");
FUNDEF VIRT void *KCALL __os_realloc_in_place(VIRT void *ptr, size_t n_bytes, gfp_t flags) THROWS(E_BADALLOC) ASMNAME("krealloc_in_place");
FUNDEF NOBLOCK WUNUSED size_t NOTHROW(KCALL __os_malloc_usable_size)(VIRT void *ptr) ASMNAME("kmalloc_usable_size");
#ifndef ____os_free_defined
#define ____os_free_defined
FUNDEF NOBLOCK void NOTHROW(KCALL __os_free)(VIRT void *ptr) ASMNAME("kfree");
#endif /* !____os_free_defined */
FUNDEF NOBLOCK void NOTHROW(KCALL __os_ffree)(VIRT void *ptr, gfp_t flags) ASMNAME("kffree");
FUNDEF ATTR_MALLOC WUNUSED VIRT void *NOTHROW(KCALL __os_malloc_nx)(size_t n_bytes, gfp_t flags) ASMNAME("kmalloc_nx");
#ifdef CONFIG_HAVE_KERNEL_SLAB_ALLOCATORS
FUNDEF ATTR_MALLOC WUNUSED VIRT void *NOTHROW(KCALL __os_malloc_noslab_nx)(size_t n_bytes, gfp_t flags) ASMNAME("kmalloc_noslab_nx");
#else /* CONFIG_HAVE_KERNEL_SLAB_ALLOCATORS */
FUNDEF ATTR_MALLOC WUNUSED VIRT void *NOTHROW(KCALL __os_malloc_noslab_nx)(size_t n_bytes, gfp_t flags) ASMNAME("kmalloc_nx");
#endif /* !CONFIG_HAVE_KERNEL_SLAB_ALLOCATORS */
FUNDEF ATTR_MALLOC WUNUSED VIRT void *NOTHROW(KCALL __os_memalign_nx)(size_t min_alignment, size_t n_bytes, gfp_t flags) ASMNAME("kmemalign_nx");
FUNDEF ATTR_MALLOC WUNUSED VIRT void *NOTHROW(KCALL __os_memalign_offset_nx)(size_t min_alignment, ptrdiff_t offset, size_t n_bytes, gfp_t flags) ASMNAME("kmemalign_offset_nx");
FUNDEF WUNUSED VIRT void *NOTHROW(KCALL __os_realloc_nx)(VIRT void *ptr, size_t n_bytes, gfp_t flags) ASMNAME("krealloc_nx");
FUNDEF WUNUSED VIRT void *NOTHROW(KCALL __os_realign_nx)(VIRT void *ptr, size_t min_alignment, size_t n_bytes, gfp_t flags) ASMNAME("krealign_nx");
FUNDEF WUNUSED VIRT void *NOTHROW(KCALL __os_realign_offset_nx)(VIRT void *ptr, size_t min_alignment, ptrdiff_t offset, size_t n_bytes, gfp_t flags) ASMNAME("krealign_offset_nx");
FUNDEF VIRT void *NOTHROW(KCALL __os_realloc_in_place_nx)(VIRT void *ptr, size_t n_bytes, gfp_t flags) ASMNAME("krealloc_in_place_nx");

#ifndef __OMIT_KMALLOC_CONSTANT_P_WRAPPERS
#ifdef __INTELLISENSE__
ATTR_MALLOC ATTR_RETNONNULL WUNUSED VIRT void *KCALL kcalloc(size_t n_bytes, gfp_t flags) THROWS(E_BADALLOC);
ATTR_RETNONNULL WUNUSED VIRT void *KCALL krecalign(VIRT void *ptr, size_t min_alignment, size_t n_bytes, gfp_t flags) THROWS(E_BADALLOC);
ATTR_RETNONNULL WUNUSED VIRT void *KCALL krecalloc(VIRT void *ptr, size_t n_bytes, gfp_t flags) THROWS(E_BADALLOC);
VIRT void *KCALL krecalloc_in_place(VIRT void *ptr, size_t n_bytes, gfp_t flags) THROWS(E_BADALLOC);
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

FORCELOCAL ATTR_ARTIFICIAL ATTR_MALLOC ATTR_RETNONNULL WUNUSED VIRT void *KCALL
kmalloc(size_t n_bytes, gfp_t flags) THROWS(E_BADALLOC) {
	if (__builtin_constant_p(n_bytes)) {
#ifdef CONFIG_HAVE_KERNEL_SLAB_ALLOCATORS
		if (n_bytes < CONFIG_KERNEL_SLAB_MAXSIZE) {
#ifdef __OMIT_SLAB_MALLOC_CONSTANT_P_WRAPPERS
			return __os_slab_kmalloc(n_bytes, flags);
#else /* __OMIT_SLAB_MALLOC_CONSTANT_P_WRAPPERS */
			return slab_kmalloc(n_bytes, flags);
#endif /* !__OMIT_SLAB_MALLOC_CONSTANT_P_WRAPPERS */
		}
#endif /* CONFIG_HAVE_KERNEL_SLAB_ALLOCATORS */
		/* Pre-align `n_bytes' so that heap functions don't need to. */
		return __os_malloc((n_bytes + HEAP_ALIGNMENT - 1) & ~(HEAP_ALIGNMENT - 1), flags);
	}
	return __os_malloc(n_bytes, flags);
}

FORCELOCAL ATTR_ARTIFICIAL ATTR_MALLOC ATTR_RETNONNULL WUNUSED VIRT void *KCALL
kmemalign(size_t min_alignment, size_t n_bytes, gfp_t flags)
		THROWS(E_BADALLOC) {
	if (__builtin_constant_p(min_alignment) && min_alignment <= HEAP_ALIGNMENT)
		return kmalloc(n_bytes, flags);
	return __os_memalign(min_alignment, n_bytes, flags);
}

FORCELOCAL ATTR_ARTIFICIAL ATTR_MALLOC ATTR_RETNONNULL WUNUSED VIRT void *KCALL
kmemalign_offset(size_t min_alignment, ptrdiff_t offset,
                 size_t n_bytes, gfp_t flags)
		THROWS(E_BADALLOC) {
	if (__builtin_constant_p(offset) && offset == 0)
		return kmemalign(min_alignment, n_bytes, flags);
	return __os_memalign_offset(min_alignment, offset, n_bytes, flags);
}

FORCELOCAL ATTR_ARTIFICIAL ATTR_RETNONNULL WUNUSED VIRT void *KCALL
krealloc(VIRT void *ptr, size_t n_bytes, gfp_t flags)
		THROWS(E_BADALLOC) {
	if (__builtin_constant_p(ptr) && ptr == __NULLPTR)
		return kmalloc(n_bytes, flags);
	if (__builtin_constant_p(n_bytes))
		return __os_realloc(ptr, (n_bytes + HEAP_ALIGNMENT - 1) & ~(HEAP_ALIGNMENT - 1), flags);
	return __os_realloc(ptr, n_bytes, flags);
}

FORCELOCAL ATTR_ARTIFICIAL ATTR_RETNONNULL WUNUSED VIRT void *KCALL
krealign(VIRT void *ptr, size_t min_alignment, size_t n_bytes, gfp_t flags)
		THROWS(E_BADALLOC) {
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
		THROWS(E_BADALLOC) {
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
		THROWS(E_BADALLOC) {
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

/* Same as `kfree()', but use if it is unlikely that `ptr != NULL' */
#define kfree_unlikely(ptr) kfree(ptr)


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
#ifdef CONFIG_HAVE_KERNEL_SLAB_ALLOCATORS
		if (n_bytes < CONFIG_KERNEL_SLAB_MAXSIZE) {
#ifdef __OMIT_SLAB_MALLOC_CONSTANT_P_WRAPPERS
			return __os_slab_kmalloc_nx(n_bytes, flags);
#else /* __OMIT_SLAB_MALLOC_CONSTANT_P_WRAPPERS */
			return slab_kmalloc_nx(n_bytes, flags);
#endif /* !__OMIT_SLAB_MALLOC_CONSTANT_P_WRAPPERS */
		}
#endif /* CONFIG_HAVE_KERNEL_SLAB_ALLOCATORS */
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
#endif /* !__clang_tidy__ || NO_INSTRUMENT_KMALLOC */

DECL_END
#endif /* __CC__ */


#ifdef CONFIG_HAVE_KERNEL_TRACE_MALLOC
#ifdef __CC__
DECL_BEGIN

/* Trace a given address range `base...+=num_bytes' for the purposes
 * of  having that  range checked  during GC  memory leak detection.
 * @param: base:      Base-address of the range that should be traced. If not aligned
 *                    by at least `sizeof(void *)', the actual range that will end up
 *                    being  traced will be  truncated to start  at the next properly
 *                    aligned location.
 * @param: num_bytes: The # of bytes to trace. If not aligned by at least `sizeof(void *)',
 *                    the actual range being  traced will be truncated  to end at the  next
 *                    lower, and properly aligned location.
 * @param: gfp:       Set of:
 *                     - GFP_NOLEAK:  Don't consider this range as a leak if it can't be reached
 *                     - GFP_NOWALK:  Don't scan the body of this range during GC
 *                     - GFP_INHERIT: Passed along to underlying allocators.
 * @param: tb_skip:   How may traceback entries to skip when creating a traceback.
 * @return: * : Always re-returns `base' */
FUNDEF NOBLOCK_IF(gfp & GFP_ATOMIC) ATTR_RETNONNULL void *KCALL
kmalloc_trace(void *base, size_t num_bytes, gfp_t gfp, unsigned int tb_skip DFL(0))
		THROWS(E_BADALLOC, E_WOULDBLOCK);

/* Same as `kmalloc_trace()', but don't throw an exception. If the operation
 * fails, rather than re-returning `base', `NULL' will be returned  instead. */
FUNDEF NOBLOCK_IF(gfp & GFP_ATOMIC) WUNUSED void *
NOTHROW(KCALL kmalloc_trace_nx)(void *base, size_t num_bytes,
                                gfp_t gfp, unsigned int tb_skip DFL(0));

/* Find the trace-block that `ptr' is apart of and remove it.
 * If  no  such   block  exists,  the   kernel  will   panic.
 * For this  purpose, `CEIL_ALIGN(ptr, sizeof(void *))'  must
 * point somewhere into an address range that has  previously
 * been registered by `kmalloc_trace()'.
 * NOTE: When `ptr' is `NULL', then this function does nothing. */
FUNDEF NOBLOCK void
NOTHROW(KCALL kmalloc_untrace)(void *ptr);

/* Similar to `kmalloc_untrace()', but explicitly untrace only the given address range.
 * Just like `kmalloc_trace()',  this function  will truncate the  given address  range
 * to have it start/end at a pointer-aligned byte boundary.
 * This function will then try  to truncate the internal  descriptor(s) used for the  given
 * address range (which is allowed to span multiple prior invocations of `kmalloc_trace()',
 * so-long as no gaps exist between individually  traced ranges), and if this fails  (which
 * can happen when this function would  have to carve out a  chunk from the middle of  some
 * pre-existing  trace-node), that node will be changed such that the given range is marked
 * as  untraced, which will prevent the kernel from accessing its contents during GC scans.
 * In practice though, you shouldn't need to concern yourself with this behavior. */
FUNDEF NOBLOCK void
NOTHROW(KCALL kmalloc_untrace_n)(void *base, size_t num_bytes);

#ifdef __cplusplus
extern "C++" {
FUNDEF NOBLOCK void
NOTHROW(KCALL kmalloc_untrace)(void *base, size_t num_bytes) ASMNAME("kmalloc_untrace_n");
} /* extern "C++" */
#endif /* __cplusplus */

/* Return the  traceback stored  inside of  the debug  descriptor of  `ptr'.
 * When `ptr' is  `NULL', or  debug-malloc is disabled,  then this  function
 * will simply return with `0'. Otherwise, `CEIL_ALIGN(ptr, sizeof(void *))'
 * must  point into a  currently traced data-block, and  if it doesn't, then
 * this function will trigger a kernel panic. (unless the kernel has already
 * been poisoned, in which case it'll simply return `0')
 * When `ptr' is a SLAB-pointer, this function will also always return `0'
 * @param: tb:     Buffer to-be filled with traceback PC-locations pointer.
 * @param: buflen: Available buffer length in `tb' (# of allocated entries; not bytes)
 * @param: p_alloc_roottid: When  non-NULL, store the root-namespace TID of the
 *                          thread that originally allocated the block of `ptr'
 * @return: * :    The total number of traceback PC-locations available for `ptr'
 *                 When `> buflen', not all locations were written to `*tb',  and
 *                 the caller should re-attempt the call with more space. */
FUNDEF NOBLOCK size_t
NOTHROW(KCALL kmalloc_traceback)(void *ptr, /*out*/ void **tb, size_t buflen,
                                 pid_t *p_alloc_roottid);

/* Print a traceback for `ptr' to the given `printer'.
 * WARNING: Don't kfree(ptr) while this function is running! */
FUNDEF NOBLOCK ssize_t KCALL
kmalloc_printtrace(void *ptr, __pformatprinter printer, void *arg);

/* Validate that headers/footers of data blocks returned by kmalloc() haven't
 * been  modified (which can accidentally happen as the result of programming
 * errors, such as array over-/under-runs)
 * If inconsistencies are found, the kernel will panic.
 * s.a.  `heap_validate()'  and   `heap_validate_all()' */
FUNDEF NOBLOCK void NOTHROW(KCALL kmalloc_validate)(void);

/* Search for leaked heap memory, dump them to the system log, and return the
 * total number of leaked blocks.
 * Note that to do what it does, this function has to temporarily elevate the
 * calling  thread  to   super-override  status  (s.a.   <sched/scheduler.h>)
 * This function is the combination of:
 *     kmalloc_leaks_collect() +
 *     kmalloc_leaks_print(printer: &syslog_printer, arg: SYSLOG_LEVEL_RAW) +
 *     kmalloc_leaks_release() */
FUNDEF size_t KCALL kmalloc_leaks(void) THROWS(E_WOULDBLOCK);

typedef struct trace_node *memleak_t;
typedef void *kmalloc_leaks_t;

/* Collect, print and discard memory leaks. */
FUNDEF kmalloc_leaks_t KCALL
kmalloc_leaks_collect(void) THROWS(E_WOULDBLOCK);
FUNDEF ssize_t KCALL
kmalloc_leaks_print(kmalloc_leaks_t leaks,
                    __pformatprinter printer, void *arg,
                    size_t *pnum_leaks DFL(__NULLPTR));

/* Count the # of objects in `leaks' */
FUNDEF NOBLOCK ATTR_PURE WUNUSED size_t
NOTHROW(KCALL kmalloc_leaks_count)(kmalloc_leaks_t leaks);

/* Releaes leaks previously collected by `kmalloc_leaks_collect()'
 * @param: how: One of `KMALLOC_LEAKS_RELEASE_*' */
FUNDEF NOBLOCK void
NOTHROW(KCALL kmalloc_leaks_release)(kmalloc_leaks_t leaks,
                                     unsigned int how);

/* Helpers for working with abstract memory leak descriptors. */

/* Return the next memory after `prev' from the set of `leaks'
 * When `prev == NULL', return  the first  leak from  `leaks'.
 * Returns `NULL' when all leaks were enumerated. */
FUNDEF NOBLOCK ATTR_PURE memleak_t
NOTHROW(FCALL memleak_next)(kmalloc_leaks_t leaks, memleak_t prev);

/* Get a  named  attribute  of `self',  or  `NULL'  if  the
 * attribute isn't available or unknown, or `self == NULL'.
 * @param: attr: One of `MEMLEAK_ATTR_*' */
FUNDEF NOBLOCK ATTR_PURE void *FCALL
memleak_getattr(memleak_t self, uintptr_t attr);

DECL_END
#endif /* __CC__ */
#define ATTR_MALL_UNTRACKED ATTR_SECTION(".bss.mall.untracked")
#else /* CONFIG_HAVE_KERNEL_TRACE_MALLOC */
#ifdef __CC__
#define memleak_t                                         void *
#define kmalloc_leaks_t                                   void *
#define kmalloc_trace(base, num_bytes, flags, tb_skip)    (base)
#define kmalloc_trace_nx(base, num_bytes, flags, tb_skip) (base)
#define kmalloc_untrace(...)                              (void)0
#define kmalloc_untrace_n(ptr, num_bytes)                 (void)0
#define kmalloc_traceback(ptr, tb, buflen)                0
#define kmalloc_validate()                                (void)0
#define kmalloc_leaks()                                   0
#define kmalloc_leaks_collect()                           __NULLPTR
#define kmalloc_leaks_print(leaks, printer, arg, pnum_leaks) \
	((pnum_leaks) ? (void)(*(pnum_leaks) = 0) : (void)0, (ssize_t)0)
#define kmalloc_leaks_release(leaks, how) (void)0
#endif /* __CC__ */
#define ATTR_MALL_UNTRACKED ATTR_SECTION(".bss")
#endif /* !CONFIG_HAVE_KERNEL_TRACE_MALLOC */

/* Memory leak release modes. (For use with `kmalloc_leaks_release()') */
#define KMALLOC_LEAKS_RELEASE_RESTORE 0 /* Restore leaks; future calls to `kmalloc_leaks_collect()' will re-yield them. */
#define KMALLOC_LEAKS_RELEASE_DISCARD 1 /* Discard leaks but don't free leaked memory. */
#define KMALLOC_LEAKS_RELEASE_FREE    2 /* Discard leaks and free leaked memory. (Only possible for `kmalloc()'; not possible for `heap_alloc()') */

/* Memory leak attributes. (For use with `memleak_getattr()') */
#define MEMLEAK_ATTR_MINADDR   1             /* The lowest memory address apart of the leak */
#define MEMLEAK_ATTR_MAXADDR   2             /* The greatest memory address apart of the leak */
#define MEMLEAK_ATTR_LEAKSIZE  3             /* Total leak size (in bytes) */
#define MEMLEAK_ATTR_MINUSER   4             /* The lowest memory address apart of the leak's user-data area (following a possible `CONFIG_KERNEL_MALL_HEAD_SIZE') */
#define MEMLEAK_ATTR_MAXUSER   5             /* The greatest memory address apart of the leak's user-data area (ending before a possible `CONFIG_KERNEL_MALL_TAIL_SIZE') */
#define MEMLEAK_ATTR_USERSIZE  6             /* Total user-data area size (in bytes; w/o `CONFIG_KERNEL_MALL_HEAD_SIZE' or `CONFIG_KERNEL_MALL_TAIL_SIZE') */
#define MEMLEAK_ATTR_TID       7             /* Root-namespace TID of the original allocator thread. */
#define MEMLEAK_ATTR_TBSIZE    8             /* # of addresses within the traceback (enumerate through `MEMLEAK_ATTR_TBADDR()') */
#define MEMLEAK_ATTR_NOWALK    9             /* Returns non-NULL if `GFP_NOWALK' was set during the original allocation. */
#define MEMLEAK_ATTR_TBADDR(i) (0x100 + (i)) /* Traceback addresses. */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_MALLOC_H */
