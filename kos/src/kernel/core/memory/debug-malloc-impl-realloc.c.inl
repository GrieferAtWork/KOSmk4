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
#include "debug-malloc-impl.c.inl"
//#define DO_KREALLOC_IN_PLACE 1
#define DO_KREALLOC 1
//#define DO_KREALIGN 1
//#define DO_KREALIGN_OFFSET 1
#endif

DECL_BEGIN

#undef IS_INPLACE
#undef HAVE_MIN_ALIGNMENT
#undef HAVE_OFFSET

#ifdef DO_KREALLOC_IN_PLACE
#define IS_INPLACE 1
PUBLIC VIRT void *
NOTHROW_NX(KCALL FUNC(krealloc_in_place))(VIRT void *ptr,
                                          size_t num_bytes, gfp_t flags)
#elif defined(DO_KREALLOC)
PUBLIC VIRT void *
NOTHROW_NX(KCALL FUNC(krealloc))(VIRT void *ptr,
                                 size_t num_bytes, gfp_t flags)
#elif defined(DO_KREALIGN)
#define HAVE_MIN_ALIGNMENT 1
PUBLIC VIRT void *
NOTHROW_NX(KCALL FUNC(krealign))(VIRT void *ptr, size_t min_alignment,
                                 size_t num_bytes, gfp_t flags)
#else
#define HAVE_MIN_ALIGNMENT 1
#define HAVE_OFFSET 1
PUBLIC VIRT void *
NOTHROW_NX(KCALL FUNC(krealign_offset))(VIRT void *ptr, size_t min_alignment,
                                        ptrdiff_t offset, size_t num_bytes,
                                        gfp_t flags)
#endif
{
#ifdef HAVE_OFFSET
#define MY_MALLOC_OFFSET offset
#else /* HAVE_OFFSET */
#define MY_MALLOC_OFFSET 0
#endif /* !HAVE_OFFSET */
	struct heapptr result;
	struct mallnode *node;
	size_t old_user_size;
	size_t new_user_size;
	if (!ptr) {
#ifdef IS_INPLACE
		goto err;
#else /* IS_INPLACE */
		LOAD_CALLER_CONTEXT
		/* realloc(NULL) --> malloc() */
		assert(!(flags & MALLNODE_FUSERNODE));
#ifdef HAVE_MIN_ALIGNMENT
		result = FUNC(heap_align_untraced)(&kernel_heaps[flags & __GFP_HEAPMASK], min_alignment,
		                                   CONFIG_MALL_PREFIX_SIZE + CONFIG_MALL_HEAD_SIZE + MY_MALLOC_OFFSET,
		                                   CONFIG_MALL_PREFIX_SIZE + CONFIG_MALL_HEAD_SIZE + num_bytes +
		                                   CONFIG_MALL_TAIL_SIZE,
		                                   flags);
#else /* HAVE_MIN_ALIGNMENT */
		result = FUNC(heap_alloc_untraced)(&kernel_heaps[flags & __GFP_HEAPMASK],
		                                   CONFIG_MALL_PREFIX_SIZE + CONFIG_MALL_HEAD_SIZE + num_bytes +
		                                   CONFIG_MALL_TAIL_SIZE,
		                                   flags);
#endif /* !HAVE_MIN_ALIGNMENT */
		IFELSE_NX(if (result.hp_ptr == NULL) goto err;, )
		INITIALIZE_USER_POINTER(result.hp_ptr, result.hp_siz);
#ifdef MALLOC_NX
		if (!FUNC(mall_trace_impl)(result.hp_ptr, result.hp_siz,
		                           flags & (__GFP_HEAPMASK | GFP_NOLEAK | GFP_NOWALK | GFP_INHERIT),
		                           context))
#else /* MALLOC_NX */
		TRY {
			FUNC(mall_trace_impl)
			(result.hp_ptr, result.hp_siz,
			 flags & (__GFP_HEAPMASK | GFP_NOLEAK | GFP_NOWALK | GFP_INHERIT),
			 context);
		} EXCEPT
#endif /* !MALLOC_NX */
		{
			heap_free_untraced(&kernel_heaps[flags & __GFP_HEAPMASK],
			                   result.hp_ptr, result.hp_siz, flags);
			IFELSE_NX(goto err, RETHROW());
		}
		return (byte_t *)result.hp_ptr + CONFIG_MALL_PREFIX_SIZE + CONFIG_MALL_HEAD_SIZE;
#endif /* !IS_INPLACE */
	}
	if unlikely(OVERFLOW_UADD(num_bytes, (size_t)(HEAP_ALIGNMENT - 1), &result.hp_siz))
		IFELSE_NX(goto err, THROW(E_BADALLOC_INSUFFICIENT_HEAP_MEMORY, num_bytes));
	result.hp_siz &= ~(HEAP_ALIGNMENT - 1);
#ifdef CONFIG_USE_SLAB_ALLOCATORS
	/* Special case: realloc() a slab pointer */
	if unlikely(KERNEL_SLAB_CHECKPTR(ptr)) {
		old_user_size = SLAB_GET(ptr)->s_size;
		assertf((old_user_size & (HEAP_ALIGNMENT - 1)) == 0,
		        "Invalid slab size: %Iu", old_user_size);
#ifdef IS_INPLACE
		if (old_user_size >= result.hp_siz)
			return ptr; /* The slab is still large enough */
		goto err;
#else /* IS_INPLACE */
		LOAD_CALLER_CONTEXT
		/* realloc(NULL) --> malloc() */
		assert(!(flags & MALLNODE_FUSERNODE));
#ifdef HAVE_MIN_ALIGNMENT
		result = FUNC(heap_align_untraced)(&kernel_heaps[flags & __GFP_HEAPMASK], min_alignment,
		                                   CONFIG_MALL_PREFIX_SIZE + CONFIG_MALL_HEAD_SIZE + MY_MALLOC_OFFSET,
		                                   CONFIG_MALL_PREFIX_SIZE + CONFIG_MALL_HEAD_SIZE + num_bytes +
		                                   CONFIG_MALL_TAIL_SIZE,
		                                   flags);
#else /* HAVE_MIN_ALIGNMENT */
		result = FUNC(heap_alloc_untraced)(&kernel_heaps[flags & __GFP_HEAPMASK],
		                                   CONFIG_MALL_PREFIX_SIZE + CONFIG_MALL_HEAD_SIZE + num_bytes +
		                                   CONFIG_MALL_TAIL_SIZE,
		                                   flags);
#endif /* !HAVE_MIN_ALIGNMENT */
		IFELSE_NX(if (result.hp_ptr == NULL) goto err;, )
		INITIALIZE_USER_POINTER(result.hp_ptr, result.hp_siz);
#ifdef MALLOC_NX
		if (!FUNC(mall_trace_impl)(result.hp_ptr, result.hp_siz,
		                           flags & (__GFP_HEAPMASK | GFP_NOLEAK | GFP_NOWALK | GFP_INHERIT),
		                           context))
#else /* MALLOC_NX */
		TRY {
			FUNC(mall_trace_impl)(result.hp_ptr, result.hp_siz,
			                      flags & (__GFP_HEAPMASK | GFP_NOLEAK | GFP_NOWALK | GFP_INHERIT),
			                      context);
		} EXCEPT
#endif /* !MALLOC_NX */
		{
			heap_free_untraced(&kernel_heaps[flags & __GFP_HEAPMASK],
			                   result.hp_ptr, result.hp_siz, flags);
			IFELSE_NX(goto err, RETHROW());
		}
		result.hp_ptr = (byte_t *)result.hp_ptr + CONFIG_MALL_PREFIX_SIZE + CONFIG_MALL_HEAD_SIZE;
		memcpy(result.hp_ptr, ptr, old_user_size);
		slab_free(ptr);
		return result.hp_ptr;
#endif /* !IS_INPLACE */
	}
#endif /* CONFIG_USE_SLAB_ALLOCATORS */
	if (!mall_acquire(flags))
		IFELSE_NX(goto err, THROW(E_WOULDBLOCK_PREEMPTED));
	node = mallnode_tree_remove(&mall_tree, (uintptr_t)ptr);
again_check_node:
	if unlikely(!node) {
		sync_endwrite(&mall_lock);
		PANIC_INVALID_MALL_POINTER_WITH_CALLER_TRACEBACK(ptr);
	}
	if unlikely(node->m_flags & MALLNODE_FUSERNODE) {
		sync_endwrite(&mall_lock);
		PANIC_REALLOC_USER_NODE_WITH_CALLER_TRACEBACK(node, ptr);
	}
	if unlikely((uintptr_t)ptr != node->m_tree.a_vmin +
	            (CONFIG_MALL_PREFIX_SIZE + CONFIG_MALL_HEAD_SIZE)) {
		sync_endwrite(&mall_lock);
		PANIC_REALLOC_NOT_NODE_BASE_ADDRESS_WITH_CALLER_TRACEBACK(node, ptr);
	}
	/* Verify the previous padding before resizing a user-data-block. */
	mallnode_verify_padding(node);
	old_user_size = (size_t)((node->m_tree.a_vmax - node->m_tree.a_vmin) + 1) -
	                (CONFIG_MALL_PREFIX_SIZE + CONFIG_MALL_HEAD_SIZE + CONFIG_MALL_TAIL_SIZE);
	if (result.hp_siz <= old_user_size) {
		size_t num_free = old_user_size - result.hp_siz;
		if (num_free >= HEAP_MINSIZE) {
			gfp_t heap_flags = node->m_flags;
			/* Reduce the effective size of the user-data-block. */
			node->m_tree.a_vmax -= num_free;
			result.hp_ptr = (void *)(node->m_tree.a_vmax + 1);
			new_user_size = old_user_size - num_free;
			/* Update the prefixed size value of the user-data-block. */
			*(size_t *)node->m_tree.a_vmin = new_user_size;
			/* Re-initialize the tail. */
#if CONFIG_MALL_TAIL_SIZE != 0
#if (CONFIG_MALL_TAIL_SIZE & 3) == 0
			memsetl((byte_t *)ptr + new_user_size, CONFIG_MALL_TAIL_PATTERN, CONFIG_MALL_TAIL_SIZE / 4);
#else /* (CONFIG_MALL_TAIL_SIZE & 3) == 0 */
			mempatl((byte_t *)ptr + new_user_size, CONFIG_MALL_TAIL_PATTERN, CONFIG_MALL_TAIL_SIZE);
#endif /* (CONFIG_MALL_TAIL_SIZE & 3) != 0 */
#endif /* CONFIG_MALL_TAIL_SIZE != 0 */

			/* Re-insert the node, so-as to continue tracking it. */
			mallnode_tree_insert(&mall_tree, node);
			sync_endwrite(&mall_lock);
			/* Now just free trailing memory. */
			flags = (flags & ~(__GFP_HEAPMASK | GFP_CALLOC)) | (heap_flags & __GFP_HEAPMASK);
			heap_free_untraced(&kernel_heaps[flags & __GFP_HEAPMASK],
			                   result.hp_ptr, num_free, flags);
		} else {
			/* Don't change the allocated node size. */
			mallnode_tree_insert(&mall_tree, node);
			sync_endwrite(&mall_lock);
		}
		return ptr;
	}
	/* Size increase (first: try to extend memory.) */
	{
		size_t num_extend, num_allocated;
		void *extension_base;
		gfp_t extension_flags;
		num_extend = result.hp_siz - old_user_size;
		if (num_extend < HEAP_MINSIZE)
			num_extend = HEAP_MINSIZE;
		extension_base = (void *)(node->m_tree.a_vmax + 1);
		/* Try to allocate the missing part.
		 * NOTE: We try to do this atomically + NX first, because
		 *       we're always still holding a lock to `&mall_lock' */
		extension_flags = (flags & ~(__GFP_HEAPMASK | GFP_CALLOC)) | (node->m_flags & __GFP_HEAPMASK);
		num_allocated = heap_allat_untraced_nx(&kernel_heaps[extension_flags & __GFP_HEAPMASK],
		                                       extension_base, num_extend, extension_flags | GFP_ATOMIC);
		if (!num_allocated) {
			/* The extension fail, but that may have just been because of the `GFP_ATOMIC'
			 * -> Restore the user's node, unlock `mall_lock', then try again without `GFP_ATOMIC'. */
			mallnode_tree_insert(&mall_tree, node);
			sync_endwrite(&mall_lock);
			num_allocated = FUNC(heap_allat_untraced)(&kernel_heaps[extension_flags & __GFP_HEAPMASK],
			                                          extension_base, num_extend, extension_flags);
			if (!num_allocated) {
#ifdef IS_INPLACE
				/* Only inplace-realloc is allowed, so don't try to allocate a new block! */
				goto err;
#else /* IS_INPLACE */
				/* Must allocate a new block */
#ifdef HAVE_MIN_ALIGNMENT
				result = FUNC(heap_align_untraced)(&kernel_heaps[flags & __GFP_HEAPMASK], min_alignment,
				                                   CONFIG_MALL_PREFIX_SIZE + CONFIG_MALL_HEAD_SIZE + MY_MALLOC_OFFSET,
				                                   CONFIG_MALL_PREFIX_SIZE + CONFIG_MALL_HEAD_SIZE + num_bytes +
				                                   CONFIG_MALL_TAIL_SIZE,
				                                   flags);
#else /* HAVE_MIN_ALIGNMENT */
				result = FUNC(heap_alloc_untraced)(&kernel_heaps[flags & __GFP_HEAPMASK],
				                                   CONFIG_MALL_PREFIX_SIZE + CONFIG_MALL_HEAD_SIZE + num_bytes +
				                                   CONFIG_MALL_TAIL_SIZE,
				                                   flags);
#endif /* !HAVE_MIN_ALIGNMENT */
				IFELSE_NX(if (result.hp_ptr == NULL) goto err;, )
				/* Re-lock the MALL sub-system, and pop the node associated with the original pointer. */
				if (!mall_acquire(flags))
					IFELSE_NX(goto err, THROW(E_WOULDBLOCK_PREEMPTED));
				node = mallnode_tree_remove(&mall_tree, (uintptr_t)ptr);
				/* Check to make sure that the associated node hasn't changed. */
				if unlikely(!node ||
				            (node->m_flags & MALLNODE_FUSERNODE) ||
				            (uintptr_t)ptr != node->m_tree.a_vmin +
				                              (CONFIG_MALL_PREFIX_SIZE + CONFIG_MALL_HEAD_SIZE) ||
				            (uintptr_t)extension_base != (node->m_tree.a_vmax + 1)) {
					heap_free_untraced(&kernel_heaps[flags & __GFP_HEAPMASK],
					                   result.hp_ptr, result.hp_siz, flags);
					goto again_check_node;
				}
				/* Initialize the controller of the new (re-located) block. */
				INITIALIZE_USER_POINTER(result.hp_ptr, result.hp_siz);
				/* Extract information from the old node. */
				extension_flags = (node->m_flags & __GFP_HEAPMASK) | (flags & ~(__GFP_HEAPMASK | GFP_CALLOC));
				extension_base  = (void *)node->m_tree.a_vmin;
				num_allocated   = (size_t)(node->m_tree.a_vmax - node->m_tree.a_vmin) + 1;
				/* Re-write the contents of the node to fit the new block. */
				node->m_flags &= ~__GFP_HEAPMASK;
				node->m_flags |= flags & __GFP_HEAPMASK; /* Remember the heap bits now used by the allocation. */
				node->m_tree.a_vmin = (uintptr_t)result.hp_ptr;
				node->m_tree.a_vmax = (uintptr_t)result.hp_ptr + result.hp_siz - 1;
				/* Insert the updated node into MALL-tree */
				mall_insert_tree(node);
				sync_endwrite(&mall_lock);

				result.hp_ptr = (void *)((byte_t *)result.hp_ptr +
				                         CONFIG_MALL_PREFIX_SIZE +
				                         CONFIG_MALL_HEAD_SIZE);

				/* Copy all of the old data into the block. */
				memcpy(result.hp_ptr, ptr, old_user_size);
				/* Free the old block. */
				heap_free_untraced(&kernel_heaps[extension_flags & __GFP_HEAPMASK],
				                   extension_base, num_allocated, extension_flags);
				/* Return the base address of the new block. */
				return result.hp_ptr;
#endif /* !IS_INPLACE */
			}

			/* Re-acquire a lock to the MALL subsystem, and access the node again. */
			if (!mall_acquire(flags)) {
				heap_free_untraced(&kernel_heaps[extension_flags & __GFP_HEAPMASK],
				                   extension_base, num_allocated, extension_flags);
				IFELSE_NX(goto err, THROW(E_WOULDBLOCK_PREEMPTED));
			}
			node = mallnode_tree_remove(&mall_tree, (uintptr_t)ptr);
			/* Check to make sure that the associated node hasn't changed. */
			if unlikely(!node ||
			            (node->m_flags & MALLNODE_FUSERNODE) ||
			            (uintptr_t)ptr != node->m_tree.a_vmin +
			                              (CONFIG_MALL_PREFIX_SIZE + CONFIG_MALL_HEAD_SIZE) ||
			            (uintptr_t)extension_base != (node->m_tree.a_vmax + 1)) {
				heap_free_untraced(&kernel_heaps[extension_flags & __GFP_HEAPMASK],
				                   extension_base, num_allocated, extension_flags);
				goto again_check_node;
			}
			assert(old_user_size == (size_t)((node->m_tree.a_vmax - node->m_tree.a_vmin) + 1) -
			                        (CONFIG_MALL_PREFIX_SIZE + CONFIG_MALL_HEAD_SIZE + CONFIG_MALL_TAIL_SIZE));
			assert(result.hp_siz > old_user_size);
		}
		/* The extension was successful (now just to update the node!) */
		new_user_size = old_user_size + num_allocated;
		node->m_tree.a_vmax += num_allocated;
		/* Update the prefixed size value of the user-data-block. */
		*(size_t *)node->m_tree.a_vmin = new_user_size;
		/* Re-initialize the tail. */
#if CONFIG_MALL_TAIL_SIZE != 0
#if (CONFIG_MALL_TAIL_SIZE & 3) == 0
		memsetl((byte_t *)ptr + new_user_size, CONFIG_MALL_TAIL_PATTERN, CONFIG_MALL_TAIL_SIZE / 4);
#else /* (CONFIG_MALL_TAIL_SIZE & 3) == 0 */
		mempatl((byte_t *)ptr + new_user_size, CONFIG_MALL_TAIL_PATTERN, CONFIG_MALL_TAIL_SIZE);
#endif /* (CONFIG_MALL_TAIL_SIZE & 3) != 0 */
#endif /* CONFIG_MALL_TAIL_SIZE != 0 */
		/* Re-insert the node, so-as to continue tracking it. */
		mall_insert_tree(node);
		sync_endwrite(&mall_lock);
		/* Re-write the old tail into becoming ZERO-bytes, when GFP_CALLOC was set. */
#if CONFIG_MALL_TAIL_SIZE != 0
		if (flags & GFP_CALLOC) {
			size_t num_clear = num_allocated;
			if (num_clear > CONFIG_MALL_TAIL_SIZE)
				num_clear = CONFIG_MALL_TAIL_SIZE;
			memset((byte_t *)ptr + old_user_size, 0, num_clear);
		}
#endif /* CONFIG_MALL_TAIL_SIZE != 0 */
		/* Re-return the old pointer, because we were able to extend it! */
		return ptr;
	}
#if defined(IS_INPLACE) || defined(MALLOC_NX)
err:
	return NULL;
#endif /* IS_INPLACE || MALLOC_NX */
}


#undef MY_MALLOC_OFFSET
#undef IS_INPLACE
#undef HAVE_MIN_ALIGNMENT
#undef HAVE_OFFSET

DECL_END


#undef DO_KREALLOC_IN_PLACE
#undef DO_KREALLOC
#undef DO_KREALIGN
#undef DO_KREALIGN_OFFSET

