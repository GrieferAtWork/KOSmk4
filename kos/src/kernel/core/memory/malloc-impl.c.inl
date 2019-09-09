/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifdef __INTELLISENSE__
#include "malloc.c"
#define MALLOC_NX
#endif

#ifdef MALLOC_NX
#define IFELSE_NX(if_nx,if_x)    if_nx
#define FUNC(x)                  x##_nx
#define NOTHROW_NX               NOTHROW
#else
#define IFELSE_NX(if_nx,if_x)    if_x
#define FUNC(x)                  x
#define NOTHROW_NX               /* nothing */
#endif

DECL_BEGIN

#ifdef CONFIG_USE_SLAB_ALLOCATORS
PUBLIC WUNUSED ATTR_MALLOC ATTR_WEAK VIRT void *
NOTHROW_NX(KCALL FUNC(kmalloc_noslab))(size_t n_bytes, gfp_t flags) {
	struct heapptr hptr;
	struct mptr *result;
	size_t alloc_size;
	if unlikely(OVERFLOW_UADD(sizeof(struct mptr), n_bytes, &alloc_size))
		goto IFELSE_NX(err, err_overflow);
	hptr = FUNC(heap_alloc_untraced)(&kernel_heaps[flags & __GFP_HEAPMASK],
	                                 alloc_size, flags);
	IFELSE_NX(if unlikely(!hptr.hp_siz) goto err;, )
	assert(hptr.hp_siz >= alloc_size);
	result = (struct mptr *)hptr.hp_ptr;
	mptr_init(result, hptr.hp_siz, flags & __GFP_HEAPMASK);
	return mptr_user(result);
IFELSE_NX(err:, err_overflow:)
	IFELSE_NX(return NULL, THROW(E_BADALLOC_INSUFFICIENT_HEAP_MEMORY, n_bytes));
}
#elif defined(MALLOC_NX)
#define kmalloc_no_slab_nx  kmalloc_nx
#else
#define kmalloc_noslab     kmalloc
#endif

PUBLIC WUNUSED ATTR_MALLOC ATTR_WEAK VIRT void *
NOTHROW_NX(KCALL FUNC(kmalloc))(size_t n_bytes, gfp_t flags) {
	struct heapptr hptr;
	struct mptr *result;
	size_t alloc_size;
	if unlikely(OVERFLOW_UADD(sizeof(struct mptr), n_bytes, &alloc_size))
		goto IFELSE_NX(err, err_overflow);
#ifdef CONFIG_USE_SLAB_ALLOCATORS
	if (n_bytes <= SLAB_MAXSIZE) {
		void *slab_ptr;
		slab_ptr = slab_malloc(n_bytes, flags);
		if (slab_ptr)
			return slab_ptr;
	}
#endif /* CONFIG_USE_SLAB_ALLOCATORS */
	hptr = FUNC(heap_alloc_untraced)(&kernel_heaps[flags & __GFP_HEAPMASK],
	                                 alloc_size, flags);
	IFELSE_NX(if unlikely(!hptr.hp_siz) goto err;, )
	assert(hptr.hp_siz >= alloc_size);
	result = (struct mptr *)hptr.hp_ptr;
	mptr_init(result, hptr.hp_siz, flags & __GFP_HEAPMASK);
	return mptr_user(result);
IFELSE_NX(err:, err_overflow:)
	IFELSE_NX(return NULL, THROW(E_BADALLOC_INSUFFICIENT_HEAP_MEMORY, n_bytes));
}

PUBLIC WUNUSED ATTR_MALLOC ATTR_WEAK VIRT void *
NOTHROW_NX(KCALL FUNC(kmemalign))(size_t min_alignment,
                                  size_t n_bytes, gfp_t flags) {
	struct heapptr hptr;
	struct mptr *result;
	size_t alloc_size;
	if unlikely(OVERFLOW_UADD(sizeof(struct mptr), n_bytes, &alloc_size))
		goto IFELSE_NX(err, err_overflow);
	hptr = FUNC(heap_align_untraced)(&kernel_heaps[flags & __GFP_HEAPMASK],
	                                 min_alignment, sizeof(struct mptr),
	                                 alloc_size, flags);
	IFELSE_NX(if unlikely(!hptr.hp_siz) goto err;, )
	result = (struct mptr *)hptr.hp_ptr;
	mptr_init(result, hptr.hp_siz, flags & __GFP_HEAPMASK);
	assert(IS_ALIGNED((uintptr_t)mptr_user(result), min_alignment));
	return mptr_user(result);
IFELSE_NX(err:, err_overflow:)
	IFELSE_NX(return NULL, THROW(E_BADALLOC_INSUFFICIENT_HEAP_MEMORY, n_bytes));
}

PUBLIC WUNUSED ATTR_MALLOC ATTR_WEAK VIRT void *
NOTHROW_NX(KCALL FUNC(kmemalign_offset))(size_t min_alignment, ptrdiff_t offset,
                                         size_t n_bytes, gfp_t flags) {
	struct heapptr hptr;
	struct mptr *result;
	size_t alloc_size;
	if unlikely(OVERFLOW_UADD(sizeof(struct mptr), n_bytes, &alloc_size))
		goto IFELSE_NX(err, err_overflow);
	hptr = FUNC(heap_align_untraced)(&kernel_heaps[flags & __GFP_HEAPMASK],
	                                 min_alignment, sizeof(struct mptr) + offset,
	                                 alloc_size, flags);
	IFELSE_NX(if unlikely(!hptr.hp_siz) goto err;, )
	result = (struct mptr *)hptr.hp_ptr;
	mptr_init(result, hptr.hp_siz, flags & __GFP_HEAPMASK);
	assert(IS_ALIGNED((uintptr_t)mptr_user(result) + offset, min_alignment));
	return mptr_user(result);
IFELSE_NX(err:, err_overflow:)
	IFELSE_NX(return NULL, THROW(E_BADALLOC_INSUFFICIENT_HEAP_MEMORY, n_bytes));
}

FORCELOCAL size_t
NOTHROW_NX(KCALL FUNC(get_realloc_size))(size_t n_bytes) {
	size_t result;
	if unlikely(OVERFLOW_UADD(n_bytes, (size_t)(HEAP_ALIGNMENT - 1), &result))
		goto err_overflow;
	result &= ~(HEAP_ALIGNMENT - 1);
	if unlikely(OVERFLOW_UADD(result, sizeof(struct mptr), &result))
		goto err_overflow;
	return result;
err_overflow:
	IFELSE_NX(return (size_t)-1,
	          THROW(E_BADALLOC_INSUFFICIENT_HEAP_MEMORY, n_bytes));
}

PUBLIC ATTR_WEAK VIRT void *
NOTHROW_NX(KCALL FUNC(krealloc_in_place))(VIRT void *ptr,
                                          size_t n_bytes,
                                          gfp_t flags) {
	struct heapptr hptr;
	struct mptr *result;
	struct heap *heap;
	size_t more_size;
	assert(!(flags & GFP_NOMOVE));
	if unlikely(!ptr)
		goto err;
	assert(IS_ALIGNED((uintptr_t)ptr, HEAP_ALIGNMENT));
#ifdef CONFIG_USE_SLAB_ALLOCATORS
	if (KERNEL_SLAB_CHECKPTR(ptr))
		return n_bytes <= SLAB_GET(ptr)->s_size ? ptr : NULL;
#endif /* CONFIG_USE_SLAB_ALLOCATORS */
	/* Align the given n_bytes and add the overhead caused by the mptr. */
	n_bytes = FUNC(get_realloc_size)(n_bytes);
	IFELSE_NX(if unlikely(n_bytes == (size_t)-1) goto err;, )
	result = mptr_get(ptr);
	mptr_assert(result);
	if (n_bytes <= mptr_size(result)) {
		/* Truncate the pointer. */
		hptr.hp_siz = mptr_size(result) - n_bytes;
		if (hptr.hp_siz >= HEAP_MINSIZE) {
			/* Only do the truncation if the memory
			 * that gets freed by this is large enough. */
			hptr.hp_ptr = (VIRT void *)((uintptr_t)result + n_bytes);
			heap_free_untraced(&kernel_heaps[mptr_heap(result)],
			                   hptr.hp_ptr,
			                   hptr.hp_siz,
			                   GFP_NORMAL);
			mptr_setsize(result, n_bytes);
		}
		return ptr;
	}
	/* Increase the pointer (try to do so in-place at first) */
	flags &= ~__GFP_HEAPMASK;
	flags |= mptr_heap(result);
	heap      = &kernel_heaps[mptr_heap(result)];
	more_size = FUNC(heap_allat_untraced)(heap,
	                                      (void *)((uintptr_t)result + mptr_size(result)),
	                                      (size_t)(n_bytes - mptr_size(result)), flags);
	if (more_size != 0) {
		/* Allocation was OK. Update the mptr. */
		mptr_setsize(result, mptr_size(result) + more_size);
		assert(mptr_size(result) >= n_bytes);
		return ptr;
	}
err:
	return NULL;
}

PUBLIC ATTR_WEAK VIRT void *
NOTHROW_NX(KCALL FUNC(krealloc))(VIRT void *ptr,
                                 size_t n_bytes, gfp_t flags) {
	struct heapptr hptr;
	struct mptr *result;
	struct heap *heap;
	size_t more_size;
	assert(!(flags & GFP_NOMOVE));
	if (!ptr)
		return FUNC(kmalloc_noslab)(n_bytes, flags);
#ifdef CONFIG_USE_SLAB_ALLOCATORS
	if (KERNEL_SLAB_CHECKPTR(ptr)) {
		void *resptr;
		u8 old_size = SLAB_GET(ptr)->s_size;
		if (n_bytes <= old_size)
			return ptr;
		resptr = FUNC(kmalloc_noslab)(n_bytes, flags);
#ifdef MALLOC_NX
		if unlikely(!resptr)
			return NULL;
#endif /* MALLOC_NX */
		memcpy(resptr, ptr, old_size);
		slab_free(ptr);
		return resptr;
	}
#endif /* CONFIG_USE_SLAB_ALLOCATORS */
	assert(IS_ALIGNED((uintptr_t)ptr, HEAP_ALIGNMENT));
	/* Align the given n_bytes and add the overhead caused by the mptr. */
	n_bytes = FUNC(get_realloc_size)(n_bytes);
	IFELSE_NX(if unlikely(n_bytes == (size_t)-1) goto err;, )
	result = mptr_get(ptr);
	mptr_assert(result);
	if (n_bytes <= mptr_size(result)) {
		/* Truncate the pointer. */
		hptr.hp_siz = mptr_size(result) - n_bytes;
		if (hptr.hp_siz >= HEAP_MINSIZE) {
			/* Only do the truncation if the memory
			 * that gets freed by this is large enough. */
			hptr.hp_ptr = (VIRT void *)((uintptr_t)result + n_bytes);
			heap_free_untraced(&kernel_heaps[mptr_heap(result)],
			                   hptr.hp_ptr, hptr.hp_siz, GFP_NORMAL);
			mptr_setsize(result, n_bytes);
		}
		return ptr;
	}
	/* Increase the pointer (try to do so in-place at first) */
	flags &= ~__GFP_HEAPMASK;
	flags |= mptr_heap(result);
	heap      = &kernel_heaps[mptr_heap(result)];
	more_size = FUNC(heap_allat_untraced)(heap,
	                                      (void *)((uintptr_t)result + mptr_size(result)),
	                                      (size_t)(n_bytes - mptr_size(result)), flags);
	if (more_size != 0) {
		/* Allocation was OK. Update the mptr. */
		mptr_setsize(result, mptr_size(result) + more_size);
		assert(mptr_size(result) >= n_bytes);
		return ptr;
	}
	/* Overlap with another pointer. - Allocate a new block. */
	hptr = FUNC(heap_alloc_untraced)(heap, sizeof(struct mptr) + n_bytes, flags);
	IFELSE_NX(if unlikely(!hptr.hp_siz) goto err;, )
	memcpy(hptr.hp_ptr, result, mptr_size(result));
	/* Free the old pointer. */
	heap_free_untraced(heap, result, mptr_size(result), GFP_NORMAL);
	/* Initialize the new pointer. */
	result = (struct mptr *)hptr.hp_ptr;
	mptr_init(result, hptr.hp_siz, flags & __GFP_HEAPMASK);
	return mptr_user(result);
#ifdef MALLOC_NX
err:
	return NULL;
#endif /* MALLOC_NX */
}

PUBLIC ATTR_WEAK VIRT void *
NOTHROW_NX(KCALL FUNC(krealign))(VIRT void *ptr, size_t min_alignment,
                                 size_t n_bytes, gfp_t flags) {
	struct heapptr hptr;
	struct mptr *result;
	struct heap *heap;
	size_t more_size;
	assert(!(flags & GFP_NOMOVE));
	if (!ptr)
		return FUNC(kmemalign)(min_alignment, n_bytes, flags);
	assert(IS_ALIGNED((uintptr_t)ptr, HEAP_ALIGNMENT));
#ifdef CONFIG_USE_SLAB_ALLOCATORS
	if (KERNEL_SLAB_CHECKPTR(ptr)) {
		void *resptr;
		u8 old_size = SLAB_GET(ptr)->s_size;
		if (n_bytes <= old_size)
			return ptr;
		resptr = FUNC(kmemalign)(min_alignment, n_bytes, flags);
#ifdef MALLOC_NX
		if unlikely(!resptr)
			return NULL;
#endif /* MALLOC_NX */
		memcpy(resptr, ptr, old_size);
		slab_free(ptr);
		return resptr;
	}
#endif /* CONFIG_USE_SLAB_ALLOCATORS */
	/* Align the given n_bytes and add the overhead caused by the mptr. */
	n_bytes = FUNC(get_realloc_size)(n_bytes);
	IFELSE_NX(if unlikely(n_bytes == (size_t)-1) goto err;, )
	result = mptr_get(ptr);
	mptr_assert(result);
	if (n_bytes <= mptr_size(result)) {
		/* Truncate the pointer. */
		hptr.hp_siz = mptr_size(result) - n_bytes;
		if (hptr.hp_siz >= HEAP_MINSIZE) {
			/* Only do the truncation if the memory
			 * that gets freed by this is large enough. */
			hptr.hp_ptr = (VIRT void *)((uintptr_t)result + n_bytes);
			heap_free_untraced(&kernel_heaps[mptr_heap(result)],
			                   hptr.hp_ptr,
			                   hptr.hp_siz,
			                   GFP_NORMAL);
			mptr_setsize(result, n_bytes);
		}
		return ptr;
	}
	/* Increase the pointer (try to do so in-place at first) */
	flags &= ~__GFP_HEAPMASK;
	flags |= mptr_heap(result);
	heap      = &kernel_heaps[mptr_heap(result)];
	more_size = FUNC(heap_allat_untraced)(heap,
	                                      (void *)((uintptr_t)result + mptr_size(result)),
	                                      (size_t)(n_bytes - mptr_size(result)), flags);
	if (more_size != 0) {
		/* Allocation was OK. Update the mptr. */
		mptr_setsize(result, mptr_size(result) + more_size);
		assert(mptr_size(result) >= n_bytes);
		return ptr;
	}
	/* Overlap with another pointer. - Allocate a new block. */
	hptr = FUNC(heap_align_untraced)(heap, min_alignment,
	                                 sizeof(struct mptr),
	                                 sizeof(struct mptr) + n_bytes,
	                                 flags);
	IFELSE_NX(if unlikely(!hptr.hp_siz) goto err;, )
	memcpy(hptr.hp_ptr, result, mptr_size(result));
	/* Free the old pointer. */
	heap_free_untraced(heap, result, mptr_size(result), GFP_NORMAL);
	/* Initialize the new pointer. */
	result = (struct mptr *)hptr.hp_ptr;
	mptr_init(result, hptr.hp_siz, flags & __GFP_HEAPMASK);
	return mptr_user(result);
#ifdef MALLOC_NX
err:
	return NULL;
#endif /* MALLOC_NX */
}

PUBLIC ATTR_WEAK VIRT void *
NOTHROW_NX(KCALL FUNC(krealign_offset))(VIRT void *ptr, size_t min_alignment,
                                        ptrdiff_t offset, size_t n_bytes,
                                        gfp_t flags) {
	struct heapptr hptr;
	struct mptr *result;
	struct heap *heap;
	size_t more_size;
	assert(!(flags & GFP_NOMOVE));
	if (!ptr)
		return FUNC(kmemalign_offset)(min_alignment, offset, n_bytes, flags);
	assert(IS_ALIGNED((uintptr_t)ptr, HEAP_ALIGNMENT));
#ifdef CONFIG_USE_SLAB_ALLOCATORS
	if (KERNEL_SLAB_CHECKPTR(ptr)) {
		void *resptr;
		u8 old_size = SLAB_GET(ptr)->s_size;
		if (n_bytes <= old_size)
			return ptr;
		resptr = FUNC(kmemalign_offset)(min_alignment, offset, n_bytes, flags);
#ifdef MALLOC_NX
		if unlikely(!resptr)
			return NULL;
#endif /* MALLOC_NX */
		memcpy(resptr, ptr, old_size);
		slab_free(ptr);
		return resptr;
	}
#endif /* CONFIG_USE_SLAB_ALLOCATORS */
	/* Align the given n_bytes and add the overhead caused by the mptr. */
	n_bytes = FUNC(get_realloc_size)(n_bytes);
	IFELSE_NX(if unlikely(n_bytes == (size_t)-1) goto err;, )
	result = mptr_get(ptr);
	mptr_assert(result);
	if (n_bytes <= mptr_size(result)) {
		/* Truncate the pointer. */
		hptr.hp_siz = mptr_size(result) - n_bytes;
		if (hptr.hp_siz >= HEAP_MINSIZE) {
			/* Only do the truncation if the memory
			 * that gets freed by this is large enough. */
			hptr.hp_ptr = (VIRT void *)((uintptr_t)result + n_bytes);
			heap_free_untraced(&kernel_heaps[mptr_heap(result)],
			                   hptr.hp_ptr,
			                   hptr.hp_siz,
			                   GFP_NORMAL);
			mptr_setsize(result, n_bytes);
		}
		return ptr;
	}
	/* Increase the pointer (try to do so in-place at first) */
	flags &= ~__GFP_HEAPMASK;
	flags |= mptr_heap(result);
	heap      = &kernel_heaps[mptr_heap(result)];
	more_size = FUNC(heap_allat_untraced)(heap,
	                                      (void *)((uintptr_t)result + mptr_size(result)),
	                                      (size_t)(n_bytes - mptr_size(result)), flags);
	if (more_size != 0) {
		/* Allocation was OK. Update the mptr. */
		mptr_setsize(result, mptr_size(result) + more_size);
		assert(mptr_size(result) >= n_bytes);
		return ptr;
	}
	/* Overlap with another pointer. - Allocate a new block. */
	hptr = FUNC(heap_align_untraced)(heap, min_alignment,
	                                 sizeof(struct mptr) + offset,
	                                 sizeof(struct mptr) + n_bytes, flags);
	IFELSE_NX(if unlikely(!hptr.hp_siz) goto err;, )
	memcpy(hptr.hp_ptr, result, mptr_size(result));
	/* Free the old pointer. */
	heap_free_untraced(heap,
	                   result,
	                   mptr_size(result),
	                   GFP_NORMAL);
	/* Initialize the new pointer. */
	result = (struct mptr *)hptr.hp_ptr;
	mptr_init(result, hptr.hp_siz, flags & __GFP_HEAPMASK);
	return mptr_user(result);
#ifdef MALLOC_NX
err:
	return NULL;
#endif /* MALLOC_NX */
}

DECL_END

#undef NOTHROW_NX
#undef FUNC
#undef IFELSE_NX
#undef MALLOC_NX
