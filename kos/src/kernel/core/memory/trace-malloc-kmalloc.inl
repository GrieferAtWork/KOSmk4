/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifdef __INTELLISENSE__
#include "trace-malloc-heap.c.inl"
//#define DEFINE_METHOD_kmalloc
//#define DEFINE_METHOD_kmalloc_in_place
//#define        DEFINE_METHOD_kmemalign
#define DEFINE_METHOD_kmemalign_offset
#endif /* __INTELLISENSE__ */

DECL_BEGIN

#if (defined(DEFINE_METHOD_kmalloc) +          \
     defined(DEFINE_METHOD_kmalloc_in_place) + \
     defined(DEFINE_METHOD_kmemalign) +        \
     defined(DEFINE_METHOD_kmemalign_offset)) != 1
#error "Must #define exactly one of `DEFINE_METHOD_*'"
#endif /* DEFINE_METHOD_... */

#if defined(DEFINE_METHOD_kmalloc)
#define LOCAL_METHOD_malloc  LOCAL_kmalloc
#define LOCAL_METHOD_realloc LOCAL_krealloc
#elif defined(DEFINE_METHOD_kmalloc_in_place)
/*efine LOCAL_METHOD_malloc  LOCAL_kmalloc_in_place*/
#define LOCAL_METHOD_realloc LOCAL_krealloc_in_place
#elif defined(DEFINE_METHOD_kmemalign)
#define LOCAL_HAVE_min_alignment
#define LOCAL_METHOD_malloc  LOCAL_kmemalign
#define LOCAL_METHOD_realloc LOCAL_krealign
#elif defined(DEFINE_METHOD_kmemalign_offset)
#define LOCAL_HAVE_min_alignment
#define LOCAL_HAVE_offset
#define LOCAL_METHOD_malloc  LOCAL_kmemalign_offset
#define LOCAL_METHOD_realloc LOCAL_krealign_offset
#endif /* ... */



#ifndef INITIALIZE_USER_POINTER
#if CONFIG_KERNEL_MALL_HEAD_SIZE != 0
#if (CONFIG_KERNEL_MALL_HEAD_SIZE & 3) == 0
#define INITIALIZE_USER_POINTER_HEAD(base, size) \
	memsetl((byte_t *)(base), CONFIG_KERNEL_MALL_HEAD_PATTERN, CONFIG_KERNEL_MALL_HEAD_SIZE / 4)
#else /* (CONFIG_KERNEL_MALL_HEAD_SIZE & 3) == 0 */
#define INITIALIZE_USER_POINTER_HEAD(base, size) \
	mempatl((byte_t *)(base), CONFIG_KERNEL_MALL_HEAD_PATTERN, CONFIG_KERNEL_MALL_HEAD_SIZE)
#endif /* (CONFIG_KERNEL_MALL_HEAD_SIZE & 3) != 0 */
#define BZERO_USER_POINTER_HEAD(base, size) \
	bzero((byte_t *)(base), CONFIG_KERNEL_MALL_HEAD_SIZE)
#else /* CONFIG_KERNEL_MALL_HEAD_SIZE != 0 */
#define INITIALIZE_USER_POINTER_HEAD(base, size) (void)0
#define BZERO_USER_POINTER_HEAD(base, size)      (void)0
#endif /* CONFIG_KERNEL_MALL_HEAD_SIZE == 0 */
#if CONFIG_KERNEL_MALL_TAIL_SIZE != 0
#if (CONFIG_KERNEL_MALL_TAIL_SIZE & 3) == 0
#define INITIALIZE_USER_POINTER_TAIL(base, size)             \
	memsetl((byte_t *)(base) + (size)-CONFIG_KERNEL_MALL_TAIL_SIZE, \
	        CONFIG_KERNEL_MALL_TAIL_PATTERN, CONFIG_KERNEL_MALL_TAIL_SIZE / 4)
#else /* (CONFIG_KERNEL_MALL_TAIL_SIZE & 3) == 0 */
#define INITIALIZE_USER_POINTER_TAIL(base, size)             \
	mempatl((byte_t *)(base) + (size)-CONFIG_KERNEL_MALL_TAIL_SIZE, \
	        CONFIG_KERNEL_MALL_TAIL_PATTERN, CONFIG_KERNEL_MALL_TAIL_SIZE)
#endif /* (CONFIG_KERNEL_MALL_TAIL_SIZE & 3) != 0 */
#define BZERO_USER_POINTER_TAIL(base, size) \
	bzero((byte_t *)(base) + (size)-CONFIG_KERNEL_MALL_TAIL_SIZE, CONFIG_KERNEL_MALL_TAIL_SIZE)
#else /* CONFIG_KERNEL_MALL_TAIL_SIZE != 0 */
#define INITIALIZE_USER_POINTER_TAIL(base, size) (void)0
#define BZERO_USER_POINTER_TAIL(base, size)      (void)0
#endif /* CONFIG_KERNEL_MALL_TAIL_SIZE == 0 */
#define INITIALIZE_USER_POINTER(base, size)    \
	(INITIALIZE_USER_POINTER_HEAD(base, size), \
	 INITIALIZE_USER_POINTER_TAIL(base, size))
#define BZERO_USER_POINTER_HEADTAIL(base, size) \
	(BZERO_USER_POINTER_HEAD(base, size),       \
	 BZERO_USER_POINTER_TAIL(base, size))
#endif /* !INITIALIZE_USER_POINTER */




#ifdef LOCAL_HAVE_min_alignment
#ifdef LOCAL_HAVE_offset
#define MY_heap_alloc_untraced(n_bytes, flags)                         \
	LOCAL_heap_align_untraced(&kernel_heaps[(flags) & __GFP_HEAPMASK], \
	                          min_alignment,                           \
	                          offset +                                 \
	                          CONFIG_KERNEL_MALL_HEAD_SIZE,                   \
	                          n_bytes,                                 \
	                          flags)
#else /* LOCAL_HAVE_offset */
#define MY_heap_alloc_untraced(n_bytes, flags)                         \
	LOCAL_heap_align_untraced(&kernel_heaps[(flags) & __GFP_HEAPMASK], \
	                          min_alignment,                           \
	                          CONFIG_KERNEL_MALL_HEAD_SIZE,                   \
	                          n_bytes,                                 \
	                          flags)
#endif /* !LOCAL_HAVE_offset */
#else /* LOCAL_HAVE_min_alignment */
#define MY_heap_alloc_untraced(n_bytes, flags)                         \
	LOCAL_heap_alloc_untraced(&kernel_heaps[(flags) & __GFP_HEAPMASK], \
	                          n_bytes,                                 \
	                          flags)
#endif /* !LOCAL_HAVE_min_alignment */

#ifdef DEFINE_X_except
#define MY_insert_trace_node_OR_trace_node_free(node, flags, n_skip) \
	TRY {                                                            \
		insert_trace_node(node, flags, 1);                           \
	} EXCEPT {                                                       \
		trace_node_free(node);                                       \
		RETHROW();                                                   \
	}
#elif defined(DEFINE_X_noexcept)
#define MY_insert_trace_node_OR_trace_node_free(node, flags, n_skip) \
	if unlikely(!insert_trace_node_nx(node, flags, 1))               \
		goto err_result_node;
#endif /* ... */





/* kmalloc(...) */
#ifdef LOCAL_METHOD_malloc
PUBLIC ATTR_NOINLINE ATTR_MALLOC WUNUSED void *
LOCAL_NOTHROW(KCALL LOCAL_METHOD_malloc)(
#ifdef LOCAL_HAVE_min_alignment
                                         size_t min_alignment,
#endif /* LOCAL_HAVE_min_alignment */
#ifdef LOCAL_HAVE_offset
                                         ptrdiff_t offset,
#endif /* LOCAL_HAVE_offset */
                                         size_t n_bytes,
                                         gfp_t flags) {
	heapptr_t result;
	struct trace_node *node;
	result = MY_heap_alloc_untraced(CONFIG_KERNEL_MALL_HEAD_SIZE +
	                                n_bytes +
	                                CONFIG_KERNEL_MALL_TAIL_SIZE,
	                                flags);
#ifdef DEFINE_X_noexcept
	if unlikely(heapptr_getsiz(result) == 0)
		goto err;
#endif /* DEFINE_X_noexcept */
	INITIALIZE_USER_POINTER(heapptr_getptr(result),
	                        heapptr_getsiz(result));

#ifdef DEFINE_X_except
	TRY
#endif /* DEFINE_X_noexcept */
	{
		struct lcpustate cs;
		heapptr_t node_ptr;
		node_ptr = LOCAL_heap_alloc_untraced(&trace_heap,
		                                     offsetof(struct trace_node, tn_trace) +
		                                     CONFIG_KERNEL_TRACE_MALLOC_MIN_TRACEBACK * sizeof(void *),
		                                     TRACE_HEAP_FLAGS | (flags & GFP_INHERIT));
#ifdef DEFINE_X_noexcept
		if unlikely(!heapptr_getsiz(node_ptr))
			goto err_result;
#endif /* DEFINE_X_noexcept */
		node = (struct trace_node *)heapptr_getptr(node_ptr);
		node->tn_size = heapptr_getsiz(node_ptr);

		/* Fill in the newly allocated node. */
		trace_node_initlink(node, heapptr_getptr(result), heapptr_getsiz(result));
		node->tn_reach = gc_version;
		node->tn_visit = 0;
		node->tn_kind  = TRACE_NODE_KIND_MALL;
		node->tn_flags = TRACE_NODE_FLAG_FROM_GFP(flags);
		node->tn_tid   = task_getroottid();

		/* Generate a traceback. */
		lcpustate_current(&cs);
		trace_malloc_generate_traceback(trace_node_traceback_vector(node),
		                                trace_node_traceback_count(node),
		                                &cs, 1);

		/* Start tracing the node. */
		MY_insert_trace_node_OR_trace_node_free(node, flags, 1);
	}
#ifdef DEFINE_X_except
	EXCEPT {
		heap_free_untraced(&kernel_heaps[flags & __GFP_HEAPMASK],
		                   heapptr_getptr(result), heapptr_getsiz(result),
		                   flags & ~GFP_CALLOC);
		RETHROW();
	}
#endif /* DEFINE_X_noexcept */
	return (byte_t *)heapptr_getptr(result) + CONFIG_KERNEL_MALL_HEAD_SIZE;
#ifdef DEFINE_X_noexcept
err_result_node:
	trace_node_free(node);
err_result:
	heap_free_untraced(&kernel_heaps[flags & __GFP_HEAPMASK],
	                   heapptr_getptr(result), heapptr_getsiz(result),
	                   flags & ~GFP_CALLOC);
err:
	return NULL;
#endif /* DEFINE_X_noexcept */
}
#endif /* LOCAL_METHOD_malloc */



/* krealloc(...) */
#ifdef LOCAL_METHOD_realloc
#if defined(LOCAL_HAVE_min_alignment) && defined(LOCAL_HAVE_offset)
#define LOCAL_realloc_PRIFMT PP_STR(LOCAL_METHOD_realloc) "(%p, %" PRIuSIZ ", %" PRIdSIZ ", %" PRIuSIZ ", %#x)"
#define LOCAL_realloc_PRIARG ptr, min_alignment, offset, n_bytes, flags
#elif defined(LOCAL_HAVE_min_alignment)
#define LOCAL_realloc_PRIFMT PP_STR(LOCAL_METHOD_realloc) "(%p, %" PRIuSIZ ", %" PRIuSIZ ", %#x)"
#define LOCAL_realloc_PRIARG ptr, min_alignment, n_bytes, flags
#elif defined(LOCAL_HAVE_offset)
#define LOCAL_realloc_PRIFMT PP_STR(LOCAL_METHOD_realloc) "(%p, %" PRIdSIZ ", %" PRIuSIZ ", %#x)"
#define LOCAL_realloc_PRIARG ptr, offset, n_bytes, flags
#else /* ... */
#define LOCAL_realloc_PRIFMT PP_STR(LOCAL_METHOD_realloc) "(%p, %" PRIuSIZ ", %#x)"
#define LOCAL_realloc_PRIARG ptr, n_bytes, flags
#endif /* !... */

PUBLIC ATTR_NOINLINE WUNUSED void *
LOCAL_NOTHROW(KCALL LOCAL_METHOD_realloc)(void *ptr,
#ifdef LOCAL_HAVE_min_alignment
                                          size_t min_alignment,
#endif /* LOCAL_HAVE_min_alignment */
#ifdef LOCAL_HAVE_offset
                                          ptrdiff_t offset,
#endif /* LOCAL_HAVE_offset */
                                          size_t n_bytes,
                                          gfp_t flags) {
#ifndef DEFINE_METHOD_kmalloc_in_place
	heapptr_t result;
#endif /* !DEFINE_METHOD_kmalloc_in_place */
	struct trace_node *node;
	size_t old_user_size;
	size_t new_user_size;
	size_t num_allocated;
	/* Check for special case: krealloc(NULL) is the same as kmalloc(), except in
	 *                         in-place mode, where that'll simply re-return NULL */
	if (!ptr) {
do_normal_malloc:
#ifdef DEFINE_METHOD_kmalloc_in_place
		goto err;
#else /* DEFINE_METHOD_kmalloc_in_place */
		result = MY_heap_alloc_untraced(CONFIG_KERNEL_MALL_HEAD_SIZE +
		                                n_bytes +
		                                CONFIG_KERNEL_MALL_TAIL_SIZE,
		                                flags);
#ifdef DEFINE_X_noexcept
		if unlikely(heapptr_getsiz(result) == 0)
			goto err;
#endif /* DEFINE_X_noexcept */
		INITIALIZE_USER_POINTER(heapptr_getptr(result),
		                        heapptr_getsiz(result));

#ifdef DEFINE_X_except
		TRY
#endif /* DEFINE_X_noexcept */
		{
			struct lcpustate cs;
			heapptr_t node_ptr;
			node_ptr = LOCAL_heap_alloc_untraced(&trace_heap,
			                                     offsetof(struct trace_node, tn_trace) +
			                                     CONFIG_KERNEL_TRACE_MALLOC_MIN_TRACEBACK * sizeof(void *),
			                                     TRACE_HEAP_FLAGS | (flags & GFP_INHERIT));
#ifdef DEFINE_X_noexcept
			if unlikely(!heapptr_getsiz(node_ptr))
				goto err_result;
#endif /* DEFINE_X_noexcept */
			node = (struct trace_node *)heapptr_getptr(node_ptr);
			node->tn_size = heapptr_getsiz(node_ptr);

			/* Fill in the newly allocated node. */
			trace_node_initlink(node, heapptr_getptr(result), heapptr_getsiz(result));
			node->tn_reach = gc_version;
			node->tn_visit = 0;
			node->tn_kind  = TRACE_NODE_KIND_MALL;
			node->tn_flags = TRACE_NODE_FLAG_FROM_GFP(flags);
			node->tn_tid   = task_getroottid();

			/* Generate a traceback. */
			lcpustate_current(&cs);
			trace_malloc_generate_traceback(trace_node_traceback_vector(node),
			                                trace_node_traceback_count(node),
			                                &cs, 1);

			/* Start tracing the node. */
			MY_insert_trace_node_OR_trace_node_free(node, flags, 1);
		}
#ifdef DEFINE_X_except
		EXCEPT {
			heap_free_untraced(&kernel_heaps[flags & __GFP_HEAPMASK],
			                   heapptr_getptr(result), heapptr_getsiz(result),
			                   flags & ~GFP_CALLOC);
			RETHROW();
		}
#endif /* DEFINE_X_noexcept */
		return (byte_t *)heapptr_getptr(result) + CONFIG_KERNEL_MALL_HEAD_SIZE;
#endif /* !DEFINE_METHOD_kmalloc_in_place */
	}
again_nonnull_ptr:

#ifdef CONFIG_HAVE_KERNEL_SLAB_ALLOCATORS
	/* Special case: krealloc() a slab pointer */
	if unlikely(KERNEL_SLAB_CHECKPTR(ptr)) {
		old_user_size = SLAB_GET(ptr)->s_size;
		if (old_user_size >= n_bytes) {
#ifndef __OPTIMIZE_SIZE__
			/* TODO: Try to move the heap-blob into smaller slab! */
#endif /* !__OPTIMIZE_SIZE__ */
			return ptr; /* The slab is still large enough */
		}
#ifdef DEFINE_METHOD_kmalloc_in_place
		goto err; /* Cannot realloc-in-place */
#else /* DEFINE_METHOD_kmalloc_in_place */
		/* Allocate a new, non-slab chunk, and copy existing data into it. */
		result = MY_heap_alloc_untraced(CONFIG_KERNEL_MALL_HEAD_SIZE +
		                                n_bytes +
		                                CONFIG_KERNEL_MALL_TAIL_SIZE,
		                                flags);
#ifdef DEFINE_X_noexcept
		if unlikely(heapptr_getsiz(result) == 0)
			goto err;
#endif /* DEFINE_X_noexcept */
		INITIALIZE_USER_POINTER(heapptr_getptr(result),
		                        heapptr_getsiz(result));
#ifdef DEFINE_X_except
		TRY
#endif /* DEFINE_X_noexcept */
		{
			struct lcpustate cs;
			heapptr_t node_ptr;
			node_ptr = LOCAL_heap_alloc_untraced(&trace_heap,
			                                     offsetof(struct trace_node, tn_trace) +
			                                     CONFIG_KERNEL_TRACE_MALLOC_MIN_TRACEBACK * sizeof(void *),
			                                     TRACE_HEAP_FLAGS | (flags & GFP_INHERIT));
#ifdef DEFINE_X_noexcept
			if unlikely(!heapptr_getsiz(node_ptr))
				goto err_result;
#endif /* DEFINE_X_noexcept */
			node = (struct trace_node *)heapptr_getptr(node_ptr);
			node->tn_size = heapptr_getsiz(node_ptr);

			/* Fill in the newly allocated node. */
			trace_node_initlink(node, heapptr_getptr(result), heapptr_getsiz(result));
			node->tn_reach = gc_version;
			node->tn_visit = 0;
			node->tn_kind  = TRACE_NODE_KIND_MALL;
			node->tn_flags = TRACE_NODE_FLAG_FROM_GFP(flags);
			node->tn_tid   = task_getroottid();

			/* Generate a traceback. */
			lcpustate_current(&cs);
			trace_malloc_generate_traceback(trace_node_traceback_vector(node),
			                                trace_node_traceback_count(node),
			                                &cs, 1);

			/* Start tracing the node. */
			MY_insert_trace_node_OR_trace_node_free(node, flags, 1);
		}
#ifdef DEFINE_X_except
		EXCEPT {
			heap_free_untraced(&kernel_heaps[flags & __GFP_HEAPMASK],
			                   heapptr_getptr(result), heapptr_getsiz(result),
			                   flags & ~GFP_CALLOC);
			RETHROW();
		}
#endif /* DEFINE_X_noexcept */
		{
			byte_t *result_ptr;
			result_ptr = (byte_t *)heapptr_getptr(result) + CONFIG_KERNEL_MALL_HEAD_SIZE;
			result_ptr = (byte_t *)memcpy(result_ptr, ptr, old_user_size);
			slab_free(ptr);
			return result_ptr;
		}
#endif /* !DEFINE_METHOD_kmalloc_in_place */
	}
#endif /* CONFIG_HAVE_KERNEL_SLAB_ALLOCATORS */

	/* The actual meat of the krealloc() function: Resizing an existing pointer */
	lock_acquire();
	/* Remove the existing node from the nodes-tree */
	node = tm_nodes_locate(ptr);
	if unlikely(!node) {
		lock_break();
		kernel_panic_n(/* n_skip: */ 1,
		               LOCAL_realloc_PRIFMT ": No node at this address",
		               LOCAL_realloc_PRIARG);
		goto do_normal_malloc;
	}

	if unlikely(node->tn_kind != TRACE_NODE_KIND_MALL) {
		node = trace_node_dupa_tb(node);
		lock_break();
		kernel_panic_n(/* n_skip: */ 1,
		               LOCAL_realloc_PRIFMT ": Node at %p...%p wasn't created by kmalloc()\n"
		               "%[gen:c]",
		               LOCAL_realloc_PRIARG,
		               trace_node_umin(node), trace_node_umax(node),
		               &trace_node_print_traceback, node);
		goto do_normal_malloc;
	}

	if unlikely(ptr != trace_node_uaddr(node) + CONFIG_KERNEL_MALL_HEAD_SIZE) {
		node = trace_node_dupa_tb(node);
		lock_break();
		kernel_panic_n(/* n_skip: */ 1,
		               LOCAL_realloc_PRIFMT ": Passed pointer does not match "
		               "start of containing node %p...%p (%p...%p)\n"
		               "%[gen:c]",
		               LOCAL_realloc_PRIARG,
		               trace_node_umin(node) + CONFIG_KERNEL_MALL_HEAD_SIZE,
		               trace_node_umax(node) - CONFIG_KERNEL_MALL_TAIL_SIZE,
		               trace_node_umin(node), trace_node_umax(node),
		               &trace_node_print_traceback, node);
		goto do_normal_malloc;
	}

	/* Verify head/tail integrity of `node' */
#ifdef HAVE_kmalloc_validate_node
	if unlikely(!kmalloc_validate_node(1, node)) {
		node = tm_nodes_remove(ptr);
		lock_break();
		trace_node_free(node);
		goto do_normal_malloc;
	}
#endif /* HAVE_kmalloc_validate_node */

	/* Calculate the old user-size */
	old_user_size = trace_node_usize(node) - (CONFIG_KERNEL_MALL_HEAD_SIZE +
	                                          CONFIG_KERNEL_MALL_TAIL_SIZE);
	if (n_bytes <= old_user_size) {
		/* Size should be decreased (just try to truncate the node) */
		size_t num_free;
		if unlikely(n_bytes < HEAP_MINSIZE) {
			/* Make sure that the truncated block remains large enough! */
			n_bytes = HEAP_MINSIZE;
			if (n_bytes >= old_user_size)
				goto realloc_unchanged;
		} else {
			/* Make sure that `n_bytes' is properly aligned */
			n_bytes = CEIL_ALIGN(n_bytes, HEAP_ALIGNMENT);
		}
		num_free = old_user_size - n_bytes;
		if (num_free >= HEAP_MINSIZE) {
			void *free_base;
			u8 node_flags = node->tn_flags;
			tm_nodes_removenode(node);

			/* Reduce the effective size of the user-data-block. */
			node->tn_link.rb_max -= num_free;
			free_base = trace_node_uend(node);
			new_user_size = old_user_size - num_free;
			/* Re-initialize the tail. */
#if CONFIG_KERNEL_MALL_TAIL_SIZE != 0
#if (CONFIG_KERNEL_MALL_TAIL_SIZE & 3) == 0
			memsetl((byte_t *)ptr + new_user_size,
			        CONFIG_KERNEL_MALL_TAIL_PATTERN,
			        CONFIG_KERNEL_MALL_TAIL_SIZE / 4);
#else /* (CONFIG_KERNEL_MALL_TAIL_SIZE & 3) == 0 */
			mempatl((byte_t *)ptr + new_user_size,
			        CONFIG_KERNEL_MALL_TAIL_PATTERN,
			        CONFIG_KERNEL_MALL_TAIL_SIZE);
#endif /* (CONFIG_KERNEL_MALL_TAIL_SIZE & 3) != 0 */
#endif /* CONFIG_KERNEL_MALL_TAIL_SIZE != 0 */

			/* Re-insert the node, so-as to continue tracking it. */
			tm_nodes_insert(node);
			lock_break();

			/* Now just free trailing memory. */
			flags = (flags & ~(__GFP_HEAPMASK | GFP_CALLOC)) |
			        (node_flags & __GFP_HEAPMASK);
			heap_free_untraced(&kernel_heaps[flags & __GFP_HEAPMASK],
			                   free_base, num_free, flags);
		} else {
realloc_unchanged:
			/* Don't change the allocated node size. */
			lock_break();
		}
		return ptr;
	}
	/* Size increase (first: try to extend memory.) */
	{
		size_t num_extend;
		void *extension_base;
		gfp_t extension_flags;
		num_extend = n_bytes - old_user_size;
		if (num_extend < HEAP_MINSIZE)
			num_extend = HEAP_MINSIZE;
		extension_base  = trace_node_uend(node);
		extension_flags = (flags & ~__GFP_HEAPMASK) | (node->tn_flags & __GFP_HEAPMASK);
		lock_break();
		/* Try to allocate the missing part. */
		num_allocated = LOCAL_heap_allat_untraced(&kernel_heaps[extension_flags & __GFP_HEAPMASK],
		                                          extension_base, num_extend,
		                                          extension_flags);
		if (!num_allocated) {
			/* Failed to allocate extended memory. - Either move the entire heap-block,
			 * or  (if in in-place  mode), simply return  `NULL', indicating that we've
			 * failed to re-size memory. */
#ifdef DEFINE_METHOD_kmalloc_in_place
			goto err;
#else /* DEFINE_METHOD_kmalloc_in_place */
			byte_t *result_ptr;
			void *oldblock_base;
			size_t oldblock_size;
			/* Must allocate a new block */
			result = MY_heap_alloc_untraced(CONFIG_KERNEL_MALL_HEAD_SIZE +
			                                n_bytes +
			                                CONFIG_KERNEL_MALL_TAIL_SIZE,
			                                flags);
#ifdef DEFINE_X_noexcept
			if unlikely(heapptr_getsiz(result) == 0)
				goto err;
#endif /* DEFINE_X_noexcept */
			INITIALIZE_USER_POINTER(heapptr_getptr(result),
			                        heapptr_getsiz(result));
			lock_regain();
again_remove_node_for_newchunk:
			node = tm_nodes_remove(ptr);
			/* Check to make sure that the associated node hasn't changed. */
			if unlikely(!node ||
			            (node->tn_kind != TRACE_NODE_KIND_MALL) ||
			            (ptr != trace_node_uaddr(node) + CONFIG_KERNEL_MALL_HEAD_SIZE) ||
			            (extension_base != trace_node_uend(node)) ||
			            ((extension_flags & __GFP_HEAPMASK) != (node->tn_flags & __GFP_HEAPMASK))) {
				if (node)
					tm_nodes_insert(node);
				lock_break();
				if (flags & GFP_CALLOC) {
					BZERO_USER_POINTER_HEADTAIL(heapptr_getptr(result),
					                            heapptr_getsiz(result));
				}
				heap_free_untraced(&kernel_heaps[flags & __GFP_HEAPMASK],
				                   heapptr_getptr(result),
				                   heapptr_getsiz(result), flags);
				goto again_nonnull_ptr;
			}

			/* Extract information from the old node. */
			extension_flags = (extension_flags & __GFP_HEAPMASK) |
			                  (flags & ~(__GFP_HEAPMASK | GFP_CALLOC));
			oldblock_base = trace_node_uaddr(node);
			oldblock_size = trace_node_usize(node);
			assert(oldblock_base == (byte_t *)ptr - CONFIG_KERNEL_MALL_HEAD_SIZE);

			/* Re-write the contents of the node to fit the new block. */
			node->tn_flags = flags & __GFP_HEAPMASK; /* Remember the heap bits now used by the allocation. */
			trace_node_initlink(node, heapptr_getptr(result), heapptr_getsiz(result));

			/* This can fail due to other bitset nodes, and we must handle it when that happens! */
			if unlikely(!tm_nodes_tryinsert(node)) {
				/* Roll-back: We must restore the old node, then resolve the  existing
				 *            (possibly-bitset) node with which our new node overlaps. */
				node->tn_flags = extension_flags & __GFP_HEAPMASK;
				trace_node_initlink(node, oldblock_base, oldblock_size);
				tm_nodes_insert(node);
#ifdef DEFINE_X_except
				TRY {
					LOCAL_insert_trace_node_resolve((uintptr_t)heapptr_getptr(result),
					                                (uintptr_t)heapptr_getptr(result) + heapptr_getsiz(result) - 1,
					                                flags, 1, LOCK_ARGS);
				} EXCEPT
#elif defined(DEFINE_X_noexcept)
				if unlikely(!LOCAL_insert_trace_node_resolve((uintptr_t)heapptr_getptr(result),
				                                             (uintptr_t)heapptr_getptr(result) + heapptr_getsiz(result) - 1,
				                                             flags, 1, LOCK_ARGS))
#endif /* DEFINE_X_noexcept */
				{
#ifdef DEFINE_X_except
					heap_free_untraced(&kernel_heaps[flags & __GFP_HEAPMASK],
					                   heapptr_getptr(result), heapptr_getsiz(result),
					                   flags & ~GFP_CALLOC);
					RETHROW();
#elif defined(DEFINE_X_noexcept)
					goto err_result;
#endif /* DEFINE_X_noexcept */
				}
				goto again_remove_node_for_newchunk;
			}
			lock_break();

			/* Copy all of the old data into the block. */
			result_ptr = (byte_t *)heapptr_getptr(result) + CONFIG_KERNEL_MALL_HEAD_SIZE;
			result_ptr = (byte_t *)memcpy(result_ptr, ptr, old_user_size);
			/* Free the old block. */
			assert(!(extension_flags & GFP_CALLOC));
			heap_free_untraced(&kernel_heaps[extension_flags & __GFP_HEAPMASK],
			                   oldblock_base, oldblock_size, extension_flags);
			return result_ptr;
#endif /* !DEFINE_METHOD_kmalloc_in_place */
		}
		lock_regain();
again_remove_node_for_oldchunk:
		node = tm_nodes_remove(ptr);
		/* Check to make sure that the associated node hasn't changed. */
		if unlikely(!node ||
		            (node->tn_kind != TRACE_NODE_KIND_MALL) ||
		            (ptr != trace_node_uaddr(node) + CONFIG_KERNEL_MALL_HEAD_SIZE) ||
		            (extension_base != trace_node_uend(node)) ||
		            ((extension_flags & __GFP_HEAPMASK) != (node->tn_flags & __GFP_HEAPMASK))) {
			if (node)
				tm_nodes_insert(node);
			lock_break();
			assert(!(extension_flags & GFP_CALLOC));
			heap_free_untraced(&kernel_heaps[extension_flags & __GFP_HEAPMASK],
			                   extension_base, num_allocated, extension_flags);
			goto again_nonnull_ptr;
		}
		/* The extension was successful (now just to update the node!) */
		new_user_size = old_user_size + num_allocated;
		node->tn_link.rb_max += num_allocated;
		/* Re-initialize the tail. */
#if CONFIG_KERNEL_MALL_TAIL_SIZE != 0
#if (CONFIG_KERNEL_MALL_TAIL_SIZE & 3) == 0
		memsetl((byte_t *)ptr + new_user_size,
		        CONFIG_KERNEL_MALL_TAIL_PATTERN,
		        CONFIG_KERNEL_MALL_TAIL_SIZE / 4);
#else /* (CONFIG_KERNEL_MALL_TAIL_SIZE & 3) == 0 */
		mempatl((byte_t *)ptr + new_user_size,
		        CONFIG_KERNEL_MALL_TAIL_PATTERN,
		        CONFIG_KERNEL_MALL_TAIL_SIZE);
#endif /* (CONFIG_KERNEL_MALL_TAIL_SIZE & 3) != 0 */
#endif /* CONFIG_KERNEL_MALL_TAIL_SIZE != 0 */
		/* Re-insert the node, so-as to continue tracking it. */

		/* This can fail due to other bitset nodes, and we must handle it when that happens! */
		if unlikely(!tm_nodes_tryinsert(node)) {
			/* Roll-back: We must restore the old node, then resolve the  existing
			 *            (possibly-bitset) node with which our new node overlaps. */
			node->tn_link.rb_max -= num_allocated;
			tm_nodes_insert(node);
#ifdef DEFINE_X_except
			TRY {
				LOCAL_insert_trace_node_resolve((uintptr_t)extension_base,
				                                (uintptr_t)extension_base + num_allocated - 1,
				                                flags, 1, LOCK_ARGS);
			} EXCEPT
#elif defined(DEFINE_X_noexcept)
			if unlikely(!LOCAL_insert_trace_node_resolve((uintptr_t)extension_base,
			                                             (uintptr_t)extension_base + num_allocated - 1,
			                                             flags, 1, LOCK_ARGS))
#endif /* DEFINE_X_noexcept */
			{
				assert(!(extension_flags & GFP_CALLOC));
				heap_free_untraced(&kernel_heaps[extension_flags & __GFP_HEAPMASK],
				                   extension_base, num_allocated, extension_flags);
#ifdef DEFINE_X_except
				RETHROW();
#elif defined(DEFINE_X_noexcept)
				goto err;
#endif /* DEFINE_X_noexcept */
			}
			goto again_remove_node_for_oldchunk;
		}
	}
	lock_release();
	/* Re-write the old tail into becoming ZERO-bytes, when GFP_CALLOC was set. */
#if CONFIG_KERNEL_MALL_TAIL_SIZE != 0
	if (flags & GFP_CALLOC) {
		size_t num_clear = num_allocated;
		if (num_clear > CONFIG_KERNEL_MALL_TAIL_SIZE)
			num_clear = CONFIG_KERNEL_MALL_TAIL_SIZE;
		bzero((byte_t *)ptr + old_user_size, num_clear);
	}
#endif /* CONFIG_KERNEL_MALL_TAIL_SIZE != 0 */
	/* Re-return the old pointer, because we were able to extend it! */
	return ptr;

#ifdef DEFINE_X_noexcept
#ifndef DEFINE_METHOD_kmalloc_in_place
err_result_node:
	trace_node_free(node);
err_result:
	heap_free_untraced(&kernel_heaps[flags & __GFP_HEAPMASK],
	                   heapptr_getptr(result), heapptr_getsiz(result),
	                   flags & ~GFP_CALLOC);
#endif /* !DEFINE_METHOD_kmalloc_in_place */
#endif /* DEFINE_X_noexcept */
#if defined(DEFINE_METHOD_kmalloc_in_place) || defined(DEFINE_X_noexcept)
err:
	return NULL;
#endif /* DEFINE_METHOD_kmalloc_in_place || DEFINE_X_noexcept */
}
#undef LOCAL_realloc_PRIFMT
#undef LOCAL_realloc_PRIARG
#endif /* LOCAL_METHOD_realloc */


#undef MY_heap_alloc_untraced
#undef MY_insert_trace_node_OR_trace_node_free

#undef LOCAL_HAVE_offset
#undef LOCAL_HAVE_min_alignment
#undef LOCAL_METHOD_malloc
#undef LOCAL_METHOD_realloc

DECL_END

#undef DEFINE_METHOD_kmalloc
#undef DEFINE_METHOD_kmalloc_in_place
#undef DEFINE_METHOD_kmemalign
#undef DEFINE_METHOD_kmemalign_offset
