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
#ifdef __INTELLISENSE__
#include "malloc.c"
#define DEFINE_MALLOC_NX
#endif /* __INTELLISENSE__ */

#ifdef DEFINE_MALLOC_NX
#define LOCAL_IF_NX_ELSE(if_nx, if_x)    if_nx
#define LOCAL_NOTHROW                    NOTHROW
#define LOCAL_get_realloc_size           get_realloc_size_nx
#define LOCAL_untraced_kmalloc_noslab    untraced_kmalloc_noslab_nx
#define LOCAL_untraced_kmalloc           untraced_kmalloc_nx
#define LOCAL_untraced_kmemalign         untraced_kmemalign_nx
#define LOCAL_untraced_kmemalign_offset  untraced_kmemalign_offset_nx
#define LOCAL_untraced_krealloc_in_place untraced_krealloc_in_place_nx
#define LOCAL_untraced_krealloc          untraced_krealloc_nx
#define LOCAL_untraced_krealign          untraced_krealign_nx
#define LOCAL_heap_alloc_untraced        heap_alloc_untraced_nx
#define LOCAL_heap_align_untraced        heap_align_untraced_nx
#define LOCAL_heap_allat_untraced        heap_allat_untraced_nx
#define LOCAL_untraced_krealign_offset   untraced_krealign_offset_nx
#else /* DEFINE_MALLOC_NX */
#define LOCAL_IF_NX_ELSE(if_nx, if_x)    if_x
#define LOCAL_NOTHROW                    /* nothing */
#define LOCAL_get_realloc_size           get_realloc_size
#define LOCAL_untraced_kmalloc_noslab    untraced_kmalloc_noslab
#define LOCAL_untraced_kmalloc           untraced_kmalloc
#define LOCAL_untraced_kmemalign         untraced_kmemalign
#define LOCAL_untraced_kmemalign_offset  untraced_kmemalign_offset
#define LOCAL_untraced_krealloc_in_place untraced_krealloc_in_place
#define LOCAL_untraced_krealloc          untraced_krealloc
#define LOCAL_untraced_krealign          untraced_krealign
#define LOCAL_heap_alloc_untraced        heap_alloc_untraced
#define LOCAL_heap_align_untraced        heap_align_untraced
#define LOCAL_heap_allat_untraced        heap_allat_untraced
#define LOCAL_untraced_krealign_offset   untraced_krealign_offset
#endif /* !DEFINE_MALLOC_NX */

DECL_BEGIN

#ifdef CONFIG_HAVE_KERNEL_SLAB_ALLOCATORS
INTERN ATTR_MALLOC WUNUSED VIRT void *
LOCAL_NOTHROW(KCALL LOCAL_untraced_kmalloc_noslab)(size_t n_bytes, gfp_t flags) {
	heapptr_t hptr;
	struct mptr *result;
	size_t alloc_size;
	if unlikely(OVERFLOW_UADD(sizeof(struct mptr), n_bytes, &alloc_size))
		goto LOCAL_IF_NX_ELSE(err, err_overflow);
	hptr = LOCAL_heap_alloc_untraced(&kernel_heaps[flags & __GFP_HEAPMASK],
	                                 alloc_size, flags);
	LOCAL_IF_NX_ELSE(if unlikely(!heapptr_getsiz(hptr)) goto err;, )
	assert(heapptr_getsiz(hptr) >= alloc_size);
	result = (struct mptr *)heapptr_getptr(hptr);
	mptr_init(result, heapptr_getsiz(hptr), flags & __GFP_HEAPMASK);
	return mptr_user(result);
LOCAL_IF_NX_ELSE(err:, err_overflow:)
	LOCAL_IF_NX_ELSE(return NULL, THROW(E_BADALLOC_INSUFFICIENT_HEAP_MEMORY, n_bytes));
}
#elif defined(DEFINE_MALLOC_NX)
#define untraced_kmalloc_no_slab_nx untraced_kmalloc_nx
#else /* ... */
#define untraced_kmalloc_noslab     untraced_kmalloc
#endif /* !... */

INTERN ATTR_MALLOC WUNUSED VIRT void *
LOCAL_NOTHROW(KCALL LOCAL_untraced_kmalloc)(size_t n_bytes, gfp_t flags) {
	heapptr_t hptr;
	struct mptr *result;
	size_t alloc_size;
	if unlikely(OVERFLOW_UADD(sizeof(struct mptr), n_bytes, &alloc_size))
		goto LOCAL_IF_NX_ELSE(err, err_overflow);
#ifdef CONFIG_HAVE_KERNEL_SLAB_ALLOCATORS
	if (n_bytes <= CONFIG_KERNEL_SLAB_MAXSIZE) {
		void *slab_ptr;
		slab_ptr = slab_malloc(n_bytes, flags);
		if (slab_ptr)
			return slab_ptr;
	}
#endif /* CONFIG_HAVE_KERNEL_SLAB_ALLOCATORS */
	hptr = LOCAL_heap_alloc_untraced(&kernel_heaps[flags & __GFP_HEAPMASK],
	                                 alloc_size, flags);
	LOCAL_IF_NX_ELSE(if unlikely(!heapptr_getsiz(hptr)) goto err;, )
	assert(heapptr_getsiz(hptr) >= alloc_size);
	result = (struct mptr *)heapptr_getptr(hptr);
	mptr_init(result, heapptr_getsiz(hptr), flags & __GFP_HEAPMASK);
	mptr_assert_paranoid(result);
	return mptr_user(result);
LOCAL_IF_NX_ELSE(err:, err_overflow:)
	LOCAL_IF_NX_ELSE(return NULL, THROW(E_BADALLOC_INSUFFICIENT_HEAP_MEMORY, n_bytes));
}

INTERN ATTR_MALLOC WUNUSED VIRT void *
LOCAL_NOTHROW(KCALL LOCAL_untraced_kmemalign)(size_t min_alignment,
                                              size_t n_bytes,
                                              gfp_t flags) {
	heapptr_t hptr;
	struct mptr *result;
	size_t alloc_size;
	if unlikely(OVERFLOW_UADD(sizeof(struct mptr), n_bytes, &alloc_size))
		goto LOCAL_IF_NX_ELSE(err, err_overflow);
	hptr = LOCAL_heap_align_untraced(&kernel_heaps[flags & __GFP_HEAPMASK],
	                                 min_alignment, sizeof(struct mptr),
	                                 alloc_size, flags);
	LOCAL_IF_NX_ELSE(if unlikely(!heapptr_getsiz(hptr)) goto err;, )
	result = (struct mptr *)heapptr_getptr(hptr);
	mptr_init(result, heapptr_getsiz(hptr), flags & __GFP_HEAPMASK);
	mptr_assert_paranoid(result);
	assert(IS_ALIGNED((uintptr_t)mptr_user(result), min_alignment));
	return mptr_user(result);
LOCAL_IF_NX_ELSE(err:, err_overflow:)
	LOCAL_IF_NX_ELSE(return NULL, THROW(E_BADALLOC_INSUFFICIENT_HEAP_MEMORY, n_bytes));
}

INTERN ATTR_MALLOC WUNUSED VIRT void *
LOCAL_NOTHROW(KCALL LOCAL_untraced_kmemalign_offset)(size_t min_alignment, ptrdiff_t offset,
                                                     size_t n_bytes, gfp_t flags) {
	heapptr_t hptr;
	struct mptr *result;
	size_t alloc_size;
	if unlikely(OVERFLOW_UADD(sizeof(struct mptr), n_bytes, &alloc_size))
		goto LOCAL_IF_NX_ELSE(err, err_overflow);
	hptr = LOCAL_heap_align_untraced(&kernel_heaps[flags & __GFP_HEAPMASK],
	                                 min_alignment, sizeof(struct mptr) + offset,
	                                 alloc_size, flags);
	LOCAL_IF_NX_ELSE(if unlikely(!heapptr_getsiz(hptr)) goto err;, )
	result = (struct mptr *)heapptr_getptr(hptr);
	mptr_init(result, heapptr_getsiz(hptr), flags & __GFP_HEAPMASK);
	mptr_assert_paranoid(result);
	assert(IS_ALIGNED((uintptr_t)mptr_user(result) + offset, min_alignment));
	return mptr_user(result);
LOCAL_IF_NX_ELSE(err:, err_overflow:)
	LOCAL_IF_NX_ELSE(return NULL, THROW(E_BADALLOC_INSUFFICIENT_HEAP_MEMORY, n_bytes));
}

PRIVATE LOCAL_IF_NX_ELSE(ATTR_CONST, ) WUNUSED size_t
LOCAL_NOTHROW(KCALL LOCAL_get_realloc_size)(size_t n_bytes) {
	size_t result;
	if unlikely(OVERFLOW_UADD(n_bytes, (size_t)(HEAP_ALIGNMENT - 1), &result))
		goto err_overflow;
	result &= ~(HEAP_ALIGNMENT - 1);
	if unlikely(OVERFLOW_UADD(result, sizeof(struct mptr), &result))
		goto err_overflow;
	if unlikely(result < HEAP_MINSIZE)
		result = HEAP_MINSIZE;
	return result;
err_overflow:
	LOCAL_IF_NX_ELSE(return (size_t)-1,
	          THROW(E_BADALLOC_INSUFFICIENT_HEAP_MEMORY, n_bytes));
}

INTERN VIRT void *
LOCAL_NOTHROW(KCALL LOCAL_untraced_krealloc_in_place)(VIRT void *ptr,
                                                      size_t n_bytes,
                                                      gfp_t flags) {
	struct mptr *result;
	size_t more_size;
	assert(!(flags & GFP_NOMOVE));
	if unlikely(!ptr)
		goto err;
	assert(IS_ALIGNED((uintptr_t)ptr, HEAP_ALIGNMENT));
#ifdef CONFIG_HAVE_KERNEL_SLAB_ALLOCATORS
	if (KERNEL_SLAB_CHECKPTR(ptr))
		return n_bytes <= SLAB_GET(ptr)->s_size ? ptr : NULL;
#endif /* CONFIG_HAVE_KERNEL_SLAB_ALLOCATORS */

	/* Align the given n_bytes and add the overhead caused by the mptr. */
	n_bytes = LOCAL_get_realloc_size(n_bytes);
	LOCAL_IF_NX_ELSE(if unlikely(n_bytes == (size_t)-1) goto err;, )
	result = mptr_get(ptr);
	mptr_assert(result);
	if (n_bytes <= mptr_size(result)) {
		size_t unused;
		/* Truncate the pointer. */
		unused = mptr_size(result) - n_bytes;
		if (unused >= HEAP_MINSIZE) {
			void *unused_ptr;
			/* Only  do  the truncation  if  the memory
			 * that gets freed by this is large enough. */
			unused_ptr = (VIRT void *)((uintptr_t)result + n_bytes);
			heap_free_untraced(mptr_heap(result), unused_ptr,
			                   unused, mptr_heap_gfp(result));
			mptr_setsize(result, n_bytes);
			mptr_assert_paranoid(result);
		}
		return ptr;
	}

	/* Increase the pointer (try to do so in-place at first) */
	flags &= ~__GFP_HEAPMASK;
	flags |= mptr_heap_gfp(result);
	more_size = LOCAL_heap_allat_untraced(mptr_heap(result),
	                                      (void *)((uintptr_t)result + mptr_size(result)),
	                                      (size_t)(n_bytes - mptr_size(result)), flags);
	if (more_size != 0) {
		/* Allocation was OK. Update the mptr. */
		mptr_setsize(result, mptr_size(result) + more_size);
		mptr_assert_paranoid(result);
		assert(mptr_size(result) >= n_bytes);
		return ptr;
	}
err:
	return NULL;
}

INTERN VIRT void *
LOCAL_NOTHROW(KCALL LOCAL_untraced_krealloc)(VIRT void *ptr,
                                             size_t n_bytes,
                                             gfp_t flags) {
	heapptr_t hptr;
	struct mptr *result;
	struct heap *used_heap;
	size_t more_size;
	assert(!(flags & GFP_NOMOVE));
	if (!ptr) {
#ifdef CONFIG_HAVE_KERNEL_SLAB_ALLOCATORS
		return LOCAL_untraced_kmalloc_noslab(n_bytes, flags);
#else /* CONFIG_HAVE_KERNEL_SLAB_ALLOCATORS */
		return LOCAL_untraced_kmalloc(n_bytes, flags);
#endif /* !CONFIG_HAVE_KERNEL_SLAB_ALLOCATORS */
	}
#ifdef CONFIG_HAVE_KERNEL_SLAB_ALLOCATORS
	if (KERNEL_SLAB_CHECKPTR(ptr)) {
		void *resptr;
		u8 old_size = SLAB_GET(ptr)->s_size;
		if (n_bytes <= old_size)
			return ptr;
		resptr = LOCAL_untraced_kmalloc_noslab(n_bytes, flags);
#ifdef DEFINE_MALLOC_NX
		if unlikely(!resptr)
			return NULL;
#endif /* DEFINE_MALLOC_NX */
		memcpy(resptr, ptr, old_size);
		slab_free(ptr);
		return resptr;
	}
#endif /* CONFIG_HAVE_KERNEL_SLAB_ALLOCATORS */
	assert(IS_ALIGNED((uintptr_t)ptr, HEAP_ALIGNMENT));

	/* Align the given n_bytes and add the overhead caused by the mptr. */
	n_bytes = LOCAL_get_realloc_size(n_bytes);
	LOCAL_IF_NX_ELSE(if unlikely(n_bytes == (size_t)-1) goto err;, )
	result = mptr_get(ptr);
	mptr_assert(result);
	if (n_bytes <= mptr_size(result)) {
		/* Truncate the pointer. */
		size_t unused = mptr_size(result) - n_bytes;
		if (unused >= HEAP_MINSIZE) {
			void *unused_ptr;
			/* Only  do  the truncation  if  the memory
			 * that gets freed by this is large enough. */
			unused_ptr = (VIRT void *)((uintptr_t)result + n_bytes);
			heap_free_untraced(mptr_heap(result),
			                   unused_ptr, unused, mptr_heap_gfp(result));
			mptr_setsize(result, n_bytes);
			mptr_assert_paranoid(result);
		}
		return ptr;
	}

	/* Increase the pointer (try to do so in-place at first) */
	flags &= ~__GFP_HEAPMASK;
	flags |= mptr_heap_gfp(result);
	used_heap = mptr_heap(result);
	more_size = LOCAL_heap_allat_untraced(used_heap,
	                                      (void *)((uintptr_t)result + mptr_size(result)),
	                                      (size_t)(n_bytes - mptr_size(result)), flags);
	if (more_size != 0) {
		/* Allocation was OK. Update the mptr. */
		mptr_setsize(result, mptr_size(result) + more_size);
		assert(mptr_size(result) >= n_bytes);
		return ptr;
	}

	/* Overlap with another pointer. - Allocate a new block. */
	hptr = LOCAL_heap_alloc_untraced(used_heap, sizeof(struct mptr) + n_bytes, flags);
	LOCAL_IF_NX_ELSE(if unlikely(!heapptr_getsiz(hptr)) goto err;, )
	memcpy(heapptr_getptr(hptr), result, mptr_size(result));

	/* Free the old pointer. */
	heap_free_untraced(used_heap, result,
	                   mptr_size(result),
	                   mptr_heap_gfp(result));

	/* Initialize the new pointer. */
	result = (struct mptr *)heapptr_getptr(hptr);
	mptr_init(result, heapptr_getsiz(hptr), flags & __GFP_HEAPMASK);
	mptr_assert_paranoid(result);
	return mptr_user(result);
#ifdef DEFINE_MALLOC_NX
err:
	return NULL;
#endif /* DEFINE_MALLOC_NX */
}

INTERN VIRT void *
LOCAL_NOTHROW(KCALL LOCAL_untraced_krealign)(VIRT void *ptr, size_t min_alignment,
                                             size_t n_bytes, gfp_t flags) {
	heapptr_t hptr;
	struct mptr *result;
	struct heap *used_heap;
	size_t more_size;
	assert(!(flags & GFP_NOMOVE));
	if (!ptr)
		return LOCAL_untraced_kmemalign(min_alignment, n_bytes, flags);
	assert(IS_ALIGNED((uintptr_t)ptr, HEAP_ALIGNMENT));
#ifdef CONFIG_HAVE_KERNEL_SLAB_ALLOCATORS
	if (KERNEL_SLAB_CHECKPTR(ptr)) {
		void *resptr;
		u8 old_size = SLAB_GET(ptr)->s_size;
		if (n_bytes <= old_size)
			return ptr;
		resptr = LOCAL_untraced_kmemalign(min_alignment, n_bytes, flags);
#ifdef DEFINE_MALLOC_NX
		if unlikely(!resptr)
			return NULL;
#endif /* DEFINE_MALLOC_NX */
		memcpy(resptr, ptr, old_size);
		slab_free(ptr);
		return resptr;
	}
#endif /* CONFIG_HAVE_KERNEL_SLAB_ALLOCATORS */

	/* Align the given n_bytes and add the overhead caused by the mptr. */
	n_bytes = LOCAL_get_realloc_size(n_bytes);
	LOCAL_IF_NX_ELSE(if unlikely(n_bytes == (size_t)-1) goto err;, )
	result = mptr_get(ptr);
	mptr_assert(result);
	if (n_bytes <= mptr_size(result)) {
		size_t unused;
		/* Truncate the pointer. */
		unused = mptr_size(result) - n_bytes;
		if (unused >= HEAP_MINSIZE) {
			void *unused_ptr;
			/* Only  do  the truncation  if  the memory
			 * that gets freed by this is large enough. */
			unused_ptr = (VIRT void *)((uintptr_t)result + n_bytes);
			heap_free_untraced(mptr_heap(result),
			                   unused_ptr, unused, mptr_heap_gfp(result));
			mptr_setsize(result, n_bytes);
			mptr_assert_paranoid(result);
		}
		return ptr;
	}

	/* Increase the pointer (try to do so in-place at first) */
	flags &= ~__GFP_HEAPMASK;
	flags |= mptr_heap_gfp(result);
	used_heap = mptr_heap(result);
	more_size = LOCAL_heap_allat_untraced(used_heap,
	                                      (void *)((uintptr_t)result + mptr_size(result)),
	                                      (size_t)(n_bytes - mptr_size(result)), flags);
	if (more_size != 0) {
		/* Allocation was OK. Update the mptr. */
		mptr_setsize(result, mptr_size(result) + more_size);
		mptr_assert_paranoid(result);
		assert(mptr_size(result) >= n_bytes);
		return ptr;
	}
	/* Overlap with another pointer. - Allocate a new block. */
	hptr = LOCAL_heap_align_untraced(used_heap, min_alignment,
	                                 sizeof(struct mptr),
	                                 sizeof(struct mptr) + n_bytes,
	                                 flags);
	LOCAL_IF_NX_ELSE(if unlikely(!heapptr_getsiz(hptr)) goto err;, )
	memcpy(heapptr_getptr(hptr), result, mptr_size(result));

	/* Free the old pointer. */
	heap_free_untraced(used_heap, result,
	                   mptr_size(result),
	                   mptr_heap_gfp(result));

	/* Initialize the new pointer. */
	result = (struct mptr *)heapptr_getptr(hptr);
	mptr_init(result, heapptr_getsiz(hptr), flags & __GFP_HEAPMASK);
	mptr_assert_paranoid(result);
	return mptr_user(result);
#ifdef DEFINE_MALLOC_NX
err:
	return NULL;
#endif /* DEFINE_MALLOC_NX */
}

INTERN VIRT void *
LOCAL_NOTHROW(KCALL LOCAL_untraced_krealign_offset)(VIRT void *ptr, size_t min_alignment,
                                                    ptrdiff_t offset, size_t n_bytes,
                                                    gfp_t flags) {
	heapptr_t hptr;
	struct mptr *result;
	struct heap *used_heap;
	size_t more_size;
	assert(!(flags & GFP_NOMOVE));
	if (!ptr)
		return LOCAL_untraced_kmemalign_offset(min_alignment, offset, n_bytes, flags);
	assert(IS_ALIGNED((uintptr_t)ptr, HEAP_ALIGNMENT));
#ifdef CONFIG_HAVE_KERNEL_SLAB_ALLOCATORS
	if (KERNEL_SLAB_CHECKPTR(ptr)) {
		void *resptr;
		u8 old_size = SLAB_GET(ptr)->s_size;
		if (n_bytes <= old_size)
			return ptr;
		resptr = LOCAL_untraced_kmemalign_offset(min_alignment, offset, n_bytes, flags);
#ifdef DEFINE_MALLOC_NX
		if unlikely(!resptr)
			return NULL;
#endif /* DEFINE_MALLOC_NX */
		memcpy(resptr, ptr, old_size);
		slab_free(ptr);
		return resptr;
	}
#endif /* CONFIG_HAVE_KERNEL_SLAB_ALLOCATORS */

	/* Align the given n_bytes and add the overhead caused by the mptr. */
	n_bytes = LOCAL_get_realloc_size(n_bytes);
	LOCAL_IF_NX_ELSE(if unlikely(n_bytes == (size_t)-1) goto err;, )
	result = mptr_get(ptr);
	mptr_assert(result);
	if (n_bytes <= mptr_size(result)) {
		size_t unused;
		/* Truncate the pointer. */
		unused = mptr_size(result) - n_bytes;
		if (unused >= HEAP_MINSIZE) {
			void *unused_ptr;
			/* Only  do  the truncation  if  the memory
			 * that gets freed by this is large enough. */
			unused_ptr = (VIRT void *)((uintptr_t)result + n_bytes);
			heap_free_untraced(mptr_heap(result),
			                   unused_ptr, unused, mptr_heap_gfp(result));
			mptr_setsize(result, n_bytes);
			mptr_assert_paranoid(result);
		}
		return ptr;
	}

	/* Increase the pointer (try to do so in-place at first) */
	flags &= ~__GFP_HEAPMASK;
	flags |= mptr_heap_gfp(result);
	used_heap = mptr_heap(result);
	more_size = LOCAL_heap_allat_untraced(used_heap,
	                                      (void *)((uintptr_t)result + mptr_size(result)),
	                                      (size_t)(n_bytes - mptr_size(result)), flags);
	if (more_size != 0) {
		/* Allocation was OK. Update the mptr. */
		mptr_setsize(result, mptr_size(result) + more_size);
		assert(mptr_size(result) >= n_bytes);
		mptr_assert_paranoid(result);
		return ptr;
	}

	/* Overlap with another pointer. - Allocate a new block. */
	hptr = LOCAL_heap_align_untraced(used_heap, min_alignment,
	                                 sizeof(struct mptr) + offset,
	                                 sizeof(struct mptr) + n_bytes,
	                                 flags);
	LOCAL_IF_NX_ELSE(if unlikely(!heapptr_getsiz(hptr)) goto err;, )
	memcpy(heapptr_getptr(hptr), result, mptr_size(result));

	/* Free the old pointer. */
	heap_free_untraced(used_heap, result,
	                   mptr_size(result),
	                   mptr_heap_gfp(result));

	/* Initialize the new pointer. */
	result = (struct mptr *)heapptr_getptr(hptr);
	mptr_init(result, heapptr_getsiz(hptr), flags & __GFP_HEAPMASK);
	mptr_assert_paranoid(result);
	return mptr_user(result);
#ifdef DEFINE_MALLOC_NX
err:
	return NULL;
#endif /* DEFINE_MALLOC_NX */
}

DECL_END

#undef LOCAL_NOTHROW
#undef LOCAL_IF_NX_ELSE
#undef LOCAL_get_realloc_size
#undef LOCAL_untraced_kmalloc_noslab
#undef LOCAL_untraced_kmalloc
#undef LOCAL_untraced_kmemalign
#undef LOCAL_untraced_kmemalign_offset
#undef LOCAL_untraced_krealloc_in_place
#undef LOCAL_untraced_krealloc
#undef LOCAL_untraced_krealign
#undef LOCAL_heap_alloc_untraced
#undef LOCAL_heap_align_untraced
#undef LOCAL_heap_allat_untraced
#undef LOCAL_untraced_krealign_offset

#undef DEFINE_MALLOC_NX
