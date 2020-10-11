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
#ifdef __INTELLISENSE__
#include "debug-malloc.c"
#define MALLOC_NX
#endif

#ifdef MALLOC_NX
#define IFELSE_NX(if_nx, if_x) if_nx
#define FUNC(x)                x##_nx
#define NOTHROW_NX             NOTHROW
#else /* MALLOC_NX */
#define IFELSE_NX(if_nx, if_x) if_x
#define FUNC(x)                x
#define NOTHROW_NX             /* nothing */
#endif /* !MALLOC_NX */

DECL_BEGIN


#ifdef MALLOC_NX
#define TRACE_IN_CALLER_CONTEXT_OR_FREE_AND_FAIL(result_ptr, flags, nx_on_failure)   \
	assert(!(flags & MALLNODE_FUSERNODE));                                           \
	if unlikely((result_ptr).hp_siz == 0) {                                          \
		nx_on_failure                                                                \
	} else if unlikely(!mall_trace_impl_nx((result_ptr).hp_ptr, (result_ptr).hp_siz, \
	                                       (flags & (GFP_NOLEAK | GFP_NOWALK |       \
	                                                 GFP_INHERIT)) |                 \
	                                       MALLNODE_FUSERNODE,                       \
	                                       context)) {                               \
		heap_free_untraced(self, (result_ptr).hp_ptr, (result_ptr).hp_siz, flags);   \
		nx_on_failure                                                                \
	}
#else /* MALLOC_NX */
#define TRACE_IN_CALLER_CONTEXT_OR_FREE_AND_FAIL(result_ptr, flags, nx_on_failure) \
	assert(!(flags & MALLNODE_FUSERNODE));                                         \
	TRY {                                                                          \
		mall_trace_impl((result_ptr).hp_ptr, (result_ptr).hp_siz,                  \
		                (flags & (GFP_NOLEAK | GFP_NOWALK | GFP_INHERIT)) |        \
		                MALLNODE_FUSERNODE,                                        \
		                context);                                                  \
	} EXCEPT {                                                                     \
		heap_free_untraced(self,                                                   \
		                   (result_ptr).hp_ptr,                                    \
		                   (result_ptr).hp_siz,                                    \
		                   flags);                                                 \
		RETHROW();                                                                 \
	}
#endif /* !MALLOC_NX */



PUBLIC struct heapptr
NOTHROW_NX(KCALL FUNC(heap_alloc))(struct heap *__restrict self,
                                   size_t num_bytes, gfp_t flags) {
	struct heapptr result;
	LOAD_CALLER_CONTEXT
	result = FUNC(heap_alloc_untraced)(self, num_bytes, flags);
	TRACE_IN_CALLER_CONTEXT_OR_FREE_AND_FAIL(result, flags, {
		result.hp_ptr = NULL;
		result.hp_siz = 0;
	})
	return result;
}


PUBLIC struct heapptr
NOTHROW_NX(KCALL FUNC(heap_align))(struct heap *__restrict self,
                                   size_t min_alignment, ptrdiff_t offset,
                                   size_t num_bytes, gfp_t flags) {
	struct heapptr result;
	LOAD_CALLER_CONTEXT
	result = FUNC(heap_align_untraced)(self, min_alignment,
	                                   offset, num_bytes,
	                                   flags);
	TRACE_IN_CALLER_CONTEXT_OR_FREE_AND_FAIL(result, flags, {
		result.hp_ptr = NULL;
		result.hp_siz = 0;
	})
	return result;
}


PUBLIC struct heapptr
NOTHROW_NX(KCALL FUNC(heap_realloc))(struct heap *__restrict self,
                                     VIRT void *old_ptr, size_t old_bytes,
                                     size_t new_bytes, gfp_t alloc_flags,
                                     gfp_t free_flags) {
	struct heapptr result;
	size_t missing_bytes;
	LOAD_CALLER_CONTEXT
	assert(IS_ALIGNED(old_bytes, HEAP_ALIGNMENT));
	assert(!old_bytes || IS_ALIGNED((uintptr_t)old_ptr, HEAP_ALIGNMENT));
	assert(!old_bytes || old_bytes >= HEAP_MINSIZE);
	assert(!(alloc_flags & MALLNODE_FUSERNODE));
	if (old_bytes == 0) {
		if unlikely(alloc_flags & GFP_NOMOVE)
			goto err;
		/* Special case: initial allocation */
		result = FUNC(heap_alloc_untraced)(self, new_bytes, alloc_flags);
		TRACE_IN_CALLER_CONTEXT_OR_FREE_AND_FAIL(result, alloc_flags, goto err;)
		return result;
	}
	if unlikely(OVERFLOW_UADD(new_bytes, (size_t)(HEAP_ALIGNMENT - 1), &new_bytes)) {
		IFELSE_NX(goto err, THROW(E_BADALLOC_INSUFFICIENT_HEAP_MEMORY,
		                          new_bytes - (HEAP_ALIGNMENT - 1)));
	}
	new_bytes &= ~(HEAP_ALIGNMENT - 1);
	if unlikely(new_bytes < HEAP_MINSIZE)
		new_bytes     = HEAP_MINSIZE;
	result.hp_ptr = old_ptr;
	result.hp_siz = old_bytes;
	if (new_bytes <= old_bytes) {
		size_t free_bytes;
		/* Free trailing memory. */
		free_bytes = old_bytes - new_bytes;
		if (free_bytes >= HEAP_MINSIZE) {
			heap_free(self,
			          (byte_t *)old_ptr + new_bytes,
			          free_bytes,
			          free_flags);
			result.hp_siz = new_bytes;
		}
		return result;
	}
	missing_bytes = new_bytes - old_bytes;
	missing_bytes = FUNC(heap_allat_untraced)(self,
	                                          (byte_t *)old_ptr + old_bytes,
	                                          missing_bytes,
	                                          alloc_flags);
	if (missing_bytes) {
		/* Managed to extend the data block. */
		result.hp_siz += missing_bytes;
#ifdef MALLOC_NX
		if unlikely(!mall_trace_impl_nx((byte_t *)old_ptr + old_bytes,
		                                missing_bytes,
		                                alloc_flags | MALLNODE_FUSERNODE,
		                                context)) {
			heap_free_untraced(self,
			                   (byte_t *)old_ptr + old_bytes,
			                   missing_bytes,
			                   alloc_flags);
			goto err;
		}
#else /* MALLOC_NX */
		TRY {
			mall_trace_impl((byte_t *)old_ptr + old_bytes,
			                missing_bytes,
			                alloc_flags | MALLNODE_FUSERNODE,
			                context);
		} EXCEPT {
			heap_free_untraced(self,
			                   (byte_t *)old_ptr + old_bytes,
			                   missing_bytes,
			                   alloc_flags);
			RETHROW();
		}
#endif /* !MALLOC_NX */
		return result;
	}
	if (alloc_flags & GFP_NOMOVE)
		goto err;
	/* Must allocate an entirely new data block and copy memory to it. */
	result = FUNC(heap_alloc_untraced)(self, new_bytes, alloc_flags);
	TRACE_IN_CALLER_CONTEXT_OR_FREE_AND_FAIL(result, alloc_flags, goto err;)
#if 1
	memcpy(result.hp_ptr, old_ptr, old_bytes);
#else
	TRY {
		/* The try block is here because of the possibility of a LOA failure.
		 * NO! This mustn't be something I should worry about -- Make it so
		 *     that heap memory mapped by the kernel is able to reserve its
		 *     physical memory! */
		memcpy(result.hp_ptr, old_ptr, old_bytes);
	} EXCEPT {
		heap_free_untraced(self, result.hp_ptr, result.hp_siz,
		                   alloc_flags & ~GFP_CALLOC);
		RETHROW();
	}
#endif
	/* Free the old data block. */
	heap_free(self, old_ptr, old_bytes,
	          free_flags & ~GFP_CALLOC);
	return result;
err:
	result.hp_ptr = NULL;
	result.hp_siz = 0;
	return result;
}

PUBLIC struct heapptr
NOTHROW_NX(KCALL FUNC(heap_realign))(struct heap *__restrict self,
                                     VIRT void *old_ptr, size_t old_bytes,
                                     size_t min_alignment, ptrdiff_t offset,
                                     size_t new_bytes, gfp_t alloc_flags,
                                     gfp_t free_flags) {
	struct heapptr result;
	size_t missing_bytes;
	LOAD_CALLER_CONTEXT
	assert(IS_ALIGNED(old_bytes, HEAP_ALIGNMENT));
	assert(!old_bytes || IS_ALIGNED((uintptr_t)old_ptr, HEAP_ALIGNMENT));
	assert(!old_bytes || old_bytes >= HEAP_MINSIZE);
	assert(!(alloc_flags & MALLNODE_FUSERNODE));
	if (old_bytes == 0) {
		if unlikely(alloc_flags & GFP_NOMOVE)
			goto err;
		/* Special case: initial allocation */
		result = FUNC(heap_align_untraced)(self, min_alignment, offset,
		                                   new_bytes, alloc_flags);
		TRACE_IN_CALLER_CONTEXT_OR_FREE_AND_FAIL(result, alloc_flags, goto err;)
		return result;
	}
	if unlikely(OVERFLOW_UADD(new_bytes, (size_t)(HEAP_ALIGNMENT - 1), &new_bytes)) {
		IFELSE_NX(goto err, THROW(E_BADALLOC_INSUFFICIENT_HEAP_MEMORY,
		                          new_bytes - (HEAP_ALIGNMENT - 1)));
	}
	new_bytes &= ~(HEAP_ALIGNMENT - 1);
	result.hp_ptr = old_ptr;
	result.hp_siz = old_bytes;
	if (new_bytes <= old_bytes) {
		size_t free_bytes;
		if unlikely(new_bytes < HEAP_MINSIZE)
			new_bytes = HEAP_MINSIZE;
		/* Free trailing memory. */
		free_bytes = old_bytes - new_bytes;
		if (free_bytes >= HEAP_MINSIZE) {
			heap_free(self, (byte_t *)old_ptr + new_bytes,
			          free_bytes, free_flags);
			result.hp_siz = new_bytes;
		}
		return result;
	}
	missing_bytes = new_bytes - old_bytes;
	missing_bytes = FUNC(heap_allat_untraced)(self,
	                                          (byte_t *)old_ptr + old_bytes,
	                                          missing_bytes,
	                                          alloc_flags);
	if (missing_bytes) {
		/* Managed to extend the data block. */
		result.hp_siz += missing_bytes;
#ifdef MALLOC_NX
		if unlikely(!mall_trace_impl_nx((byte_t *)old_ptr + old_bytes,
		                                missing_bytes,
		                                 alloc_flags | MALLNODE_FUSERNODE,
		                                context)) {
			heap_free_untraced(self,
			                   (byte_t *)old_ptr + old_bytes,
			                   missing_bytes,
			                   alloc_flags);
			goto err;
		}
#else /* MALLOC_NX */
		TRY {
			mall_trace_impl((byte_t *)old_ptr + old_bytes,
			                missing_bytes,
			                alloc_flags | MALLNODE_FUSERNODE,
			                context);
		} EXCEPT {
			heap_free_untraced(self,
			                   (byte_t *)old_ptr + old_bytes,
			                   missing_bytes,
			                   alloc_flags);
			RETHROW();
		}
#endif /* !MALLOC_NX */
		return result;
	}
	if (alloc_flags & GFP_NOMOVE)
		goto err;
	/* Must allocate an entirely new data block and copy memory to it. */
	result = FUNC(heap_align_untraced)(self,
	                                   min_alignment,
	                                   offset,
	                                   new_bytes,
	                                   alloc_flags);
	TRACE_IN_CALLER_CONTEXT_OR_FREE_AND_FAIL(result, alloc_flags, goto err;)
#if 1
	memcpy(result.hp_ptr, old_ptr, old_bytes);
#else
	TRY {
		/* The try block is here because of the possibility of a LOA failure.
		 * NO! This mustn't be something I should worry about -- Make it so
		 *     that heap memory mapped by the kernel is able to reserve its
		 *     physical memory! */
		memcpy(result.hp_ptr, old_ptr, old_bytes);
	} EXCEPT {
		heap_free_untraced(self, result.hp_ptr, result.hp_siz,
		                   alloc_flags & ~GFP_CALLOC);
		RETHROW();
	}
#endif
	/* Free the old data block. */
	heap_free(self, old_ptr, old_bytes,
	          free_flags & ~GFP_CALLOC);
	return result;
err:
	result.hp_ptr = NULL;
	result.hp_siz = 0;
	return result;
}


#if CONFIG_MALL_HEAD_SIZE != 0
#if (CONFIG_MALL_HEAD_SIZE & 3) == 0
#define INITIALIZE_USER_POINTER_HEAD(base, size)        \
	memsetl((byte_t *)(base) + CONFIG_MALL_PREFIX_SIZE, \
	        CONFIG_MALL_HEAD_PATTERN, CONFIG_MALL_HEAD_SIZE / 4)
#else /* (CONFIG_MALL_HEAD_SIZE & 3) == 0 */
#define INITIALIZE_USER_POINTER_HEAD(base, size)        \
	mempatl((byte_t *)(base) + CONFIG_MALL_PREFIX_SIZE, \
	        CONFIG_MALL_HEAD_PATTERN, CONFIG_MALL_HEAD_SIZE)
#endif /* (CONFIG_MALL_HEAD_SIZE & 3) != 0 */
#else /* CONFIG_MALL_HEAD_SIZE != 0 */
#define INITIALIZE_USER_POINTER_HEAD(base, size) (void)0
#endif /* CONFIG_MALL_HEAD_SIZE == 0 */
#if CONFIG_MALL_TAIL_SIZE != 0
#if (CONFIG_MALL_TAIL_SIZE & 3) == 0
#define INITIALIZE_USER_POINTER_TAIL(base, size)             \
	memsetl((byte_t *)(base) + (size)-CONFIG_MALL_TAIL_SIZE, \
	        CONFIG_MALL_TAIL_PATTERN, CONFIG_MALL_TAIL_SIZE / 4)
#else /* (CONFIG_MALL_TAIL_SIZE & 3) == 0 */
#define INITIALIZE_USER_POINTER_TAIL(base, size)             \
	mempatl((byte_t *)(base) + (size)-CONFIG_MALL_TAIL_SIZE, \
	        CONFIG_MALL_TAIL_PATTERN, CONFIG_MALL_TAIL_SIZE)
#endif /* (CONFIG_MALL_TAIL_SIZE & 3) != 0 */
#else /* CONFIG_MALL_TAIL_SIZE != 0 */
#define INITIALIZE_USER_POINTER_TAIL(base, size) (void)0
#endif /* CONFIG_MALL_TAIL_SIZE == 0 */
#define INITIALIZE_USER_POINTER_PREFIX(base, size)           \
	(*(size_t *)(base) = (size) - (CONFIG_MALL_PREFIX_SIZE + \
	                               CONFIG_MALL_HEAD_SIZE +   \
	                               CONFIG_MALL_TAIL_SIZE))
#define INITIALIZE_USER_POINTER(base, size)      \
	(INITIALIZE_USER_POINTER_PREFIX(base, size), \
	 INITIALIZE_USER_POINTER_HEAD(base, size),   \
	 INITIALIZE_USER_POINTER_TAIL(base, size))





PUBLIC ATTR_MALLOC WUNUSED VIRT void *
NOTHROW_NX(KCALL FUNC(kmalloc))(size_t n_bytes, gfp_t flags) {
	struct heapptr result;
	LOAD_CALLER_CONTEXT
	assert(!(flags & MALLNODE_FUSERNODE));
	result = FUNC(heap_alloc_untraced)(&kernel_heaps[flags & __GFP_HEAPMASK],
	                                   CONFIG_MALL_PREFIX_SIZE +
	                                   CONFIG_MALL_HEAD_SIZE + n_bytes +
	                                   CONFIG_MALL_TAIL_SIZE,
	                                   flags);
	IFELSE_NX(if unlikely(result.hp_ptr == NULL) goto err;, )
	INITIALIZE_USER_POINTER(result.hp_ptr, result.hp_siz);
#ifdef MALLOC_NX
	if unlikely(!FUNC(mall_trace_impl)(result.hp_ptr, result.hp_siz,
	                                   flags & (__GFP_HEAPMASK | GFP_NOLEAK |
	                                             GFP_NOWALK | GFP_INHERIT),
	                                   context))
#else /* MALLOC_NX */
	TRY {
		FUNC(mall_trace_impl)(result.hp_ptr, result.hp_siz,
		                      flags & (__GFP_HEAPMASK | GFP_NOLEAK |
		                               GFP_NOWALK | GFP_INHERIT),
		                      context);
	} EXCEPT
#endif /* !MALLOC_NX */
	{
		heap_free_untraced(&kernel_heaps[flags & __GFP_HEAPMASK],
		                   result.hp_ptr, result.hp_siz, flags);
		IFELSE_NX(goto err, RETHROW());
	}
	return (byte_t *)result.hp_ptr +
	       CONFIG_MALL_PREFIX_SIZE +
	       CONFIG_MALL_HEAD_SIZE;
IFELSE_NX(err: return NULL;, )
}

PUBLIC ATTR_MALLOC WUNUSED VIRT void *
NOTHROW_NX(KCALL FUNC(kmemalign))(size_t min_alignment,
                                  size_t n_bytes, gfp_t flags) {
	struct heapptr result;
	LOAD_CALLER_CONTEXT
	assert(!(flags & MALLNODE_FUSERNODE));
	result = FUNC(heap_align_untraced)(&kernel_heaps[flags & __GFP_HEAPMASK],
	                                   min_alignment,
	                                   CONFIG_MALL_PREFIX_SIZE + CONFIG_MALL_HEAD_SIZE,
	                                   CONFIG_MALL_PREFIX_SIZE + CONFIG_MALL_HEAD_SIZE + n_bytes +
	                                   CONFIG_MALL_TAIL_SIZE,
	                                   flags);
	IFELSE_NX(if unlikely(result.hp_ptr == NULL) goto err;, )
	INITIALIZE_USER_POINTER(result.hp_ptr, result.hp_siz);
#ifdef MALLOC_NX
	if unlikely(!FUNC(mall_trace_impl)(result.hp_ptr, result.hp_siz,
	                                   flags & (__GFP_HEAPMASK | GFP_NOLEAK |
	                                             GFP_NOWALK | GFP_INHERIT),
	                                   context))
#else /* MALLOC_NX */
	TRY {
		FUNC(mall_trace_impl)(result.hp_ptr,
		                      result.hp_siz,
		                      flags & (__GFP_HEAPMASK | GFP_NOLEAK |
		                               GFP_NOWALK | GFP_INHERIT),
		                      context);
	} EXCEPT
#endif /* !MALLOC_NX */
	{
		heap_free_untraced(&kernel_heaps[flags & __GFP_HEAPMASK],
		                   result.hp_ptr, result.hp_siz, flags);
		IFELSE_NX(goto err, RETHROW());
	}
	return (byte_t *)result.hp_ptr +
	       CONFIG_MALL_PREFIX_SIZE +
	       CONFIG_MALL_HEAD_SIZE;
IFELSE_NX(err: return NULL;, )
}

PUBLIC ATTR_MALLOC WUNUSED VIRT void *
NOTHROW_NX(KCALL FUNC(kmemalign_offset))(size_t min_alignment, ptrdiff_t offset,
                                         size_t n_bytes, gfp_t flags) {
	struct heapptr result;
	LOAD_CALLER_CONTEXT
	assert(!(flags & MALLNODE_FUSERNODE));
	result = FUNC(heap_align_untraced)(&kernel_heaps[flags & __GFP_HEAPMASK],
	                                   min_alignment,
	                                   offset +
	                                   CONFIG_MALL_PREFIX_SIZE + CONFIG_MALL_HEAD_SIZE,
	                                   CONFIG_MALL_PREFIX_SIZE + CONFIG_MALL_HEAD_SIZE + n_bytes +
	                                   CONFIG_MALL_TAIL_SIZE,
	                                   flags);
	IFELSE_NX(if unlikely(result.hp_ptr == NULL) goto err;, )
#ifdef MALLOC_NX
	if unlikely(!FUNC(mall_trace_impl)(result.hp_ptr, result.hp_siz,
	                                   flags & (__GFP_HEAPMASK | GFP_NOLEAK |
	                                             GFP_NOWALK | GFP_INHERIT),
	                                   context))
#else /* MALLOC_NX */
	TRY {
		FUNC(mall_trace_impl)(result.hp_ptr, result.hp_siz,
		                      flags & (__GFP_HEAPMASK | GFP_NOLEAK |
		                               GFP_NOWALK | GFP_INHERIT),
		                      context);
	} EXCEPT
#endif /* !MALLOC_NX */
	{
		heap_free_untraced(&kernel_heaps[flags & __GFP_HEAPMASK],
		                   result.hp_ptr, result.hp_siz, flags);
		IFELSE_NX(goto err, RETHROW());
	}
	INITIALIZE_USER_POINTER(result.hp_ptr, result.hp_siz);
	return (byte_t *)result.hp_ptr +
	       CONFIG_MALL_PREFIX_SIZE +
	       CONFIG_MALL_HEAD_SIZE;
IFELSE_NX(err: return NULL;, )
}

DECL_END

#ifndef __INTELLISENSE__
#define DO_KREALLOC_IN_PLACE 1
#include "debug-malloc-impl-realloc.c.inl"
#define DO_KREALLOC 1
#include "debug-malloc-impl-realloc.c.inl"
#define DO_KREALIGN 1
#include "debug-malloc-impl-realloc.c.inl"
#define DO_KREALIGN_OFFSET 1
#include "debug-malloc-impl-realloc.c.inl"


#undef TRACE_IN_CALLER_CONTEXT_OR_FREE_AND_FAIL
#undef INITIALIZE_USER_POINTER_PREFIX
#undef INITIALIZE_USER_POINTER_HEAD
#undef INITIALIZE_USER_POINTER_TAIL
#undef INITIALIZE_USER_POINTER

#undef NOTHROW_NX
#undef FUNC
#undef IFELSE_NX
#undef MALLOC_NX
#endif /* !__INTELLISENSE__ */

