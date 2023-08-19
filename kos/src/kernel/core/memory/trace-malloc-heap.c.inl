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
#include "trace-malloc.c"
//#define DEFINE_X_except
#define DEFINE_X_noexcept
#endif /* __INTELLISENSE__ */

#if (defined(DEFINE_X_except) + defined(DEFINE_X_noexcept)) != 1
#error "Must #define exactly one of `DEFINE_X_except' or `DEFINE_X_noexcept'"
#endif /* DEFINE_X_[no]except... */

DECL_BEGIN

#ifdef DEFINE_X_except
#define LOCAL_NOTHROW /* nothing */
#elif defined(DEFINE_X_noexcept)
#define LOCAL_NOTHROW NOTHROW
#endif /* ... */

#ifdef DEFINE_X_except
#define LOCAL_heap_alloc            heap_alloc
#define LOCAL_heap_alloc_untraced   heap_alloc_untraced
#define LOCAL_heap_align            heap_align
#define LOCAL_heap_align_untraced   heap_align_untraced
#define LOCAL_heap_realloc          heap_realloc
#define LOCAL_heap_realloc_untraced heap_realloc_untraced
#define LOCAL_heap_allat            heap_allat
#define LOCAL_heap_allat_untraced   heap_allat_untraced
#define LOCAL_heap_realign          heap_realign
#define LOCAL_heap_realign_untraced heap_realign_untraced
#elif defined(DEFINE_X_noexcept)
#define LOCAL_heap_alloc            heap_alloc_nx
#define LOCAL_heap_alloc_untraced   heap_alloc_untraced_nx
#define LOCAL_heap_align            heap_align_nx
#define LOCAL_heap_align_untraced   heap_align_untraced_nx
#define LOCAL_heap_realloc          heap_realloc_nx
#define LOCAL_heap_realloc_untraced heap_realloc_untraced_nx
#define LOCAL_heap_allat            heap_allat_nx
#define LOCAL_heap_allat_untraced   heap_allat_untraced_nx
#define LOCAL_heap_realign          heap_realign_nx
#define LOCAL_heap_realign_untraced heap_realign_untraced_nx
#endif /* ... */

#ifdef DEFINE_X_except
#define LOCAL_kmalloc           kmalloc
#define LOCAL_kmemalign         kmemalign
#define LOCAL_kmemalign_offset  kmemalign_offset
#define LOCAL_krealloc_in_place krealloc_in_place
#define LOCAL_krealloc          krealloc
#define LOCAL_krealign          krealign
#define LOCAL_krealign_offset   krealign_offset
#elif defined(DEFINE_X_noexcept)
#define LOCAL_kmalloc           kmalloc_nx
#define LOCAL_kmemalign         kmemalign_nx
#define LOCAL_kmemalign_offset  kmemalign_offset_nx
#define LOCAL_krealloc_in_place krealloc_in_place_nx
#define LOCAL_krealloc          krealloc_nx
#define LOCAL_krealign          krealign_nx
#define LOCAL_krealign_offset   krealign_offset_nx
#endif /* ... */

#ifdef DEFINE_X_except
#define LOCAL_insert_trace_node_resolve insert_trace_node_resolve
#define LOCAL_insert_trace_node         insert_trace_node
#elif defined(DEFINE_X_noexcept)
#define LOCAL_insert_trace_node_resolve insert_trace_node_resolve_nx
#define LOCAL_insert_trace_node         insert_trace_node_nx
#endif /* ... */


#ifdef DEFINE_X_except
#define LOCAL_TRACE_OR_FAIL(result_ptr, gfp, nx_on_failure)                            \
	TRY {                                                                              \
		kmalloc_trace(heapptr_getptr(result_ptr), heapptr_getsiz(result_ptr), gfp, 1); \
	} EXCEPT {                                                                         \
		heap_free_untraced(self,                                                       \
		                   heapptr_getptr(result_ptr),                                 \
		                   heapptr_getsiz(result_ptr),                                 \
		                   gfp);                                                       \
		RETHROW();                                                                     \
	}
#elif defined(DEFINE_X_noexcept)
#define LOCAL_TRACE_OR_FAIL(result_ptr, gfp, nx_on_failure)                     \
	if unlikely(heapptr_getsiz(result_ptr) == 0) {                              \
		nx_on_failure                                                           \
	} else if unlikely(!kmalloc_trace_nx(heapptr_getptr(result_ptr),            \
	                                     heapptr_getsiz(result_ptr), gfp, 1)) { \
		heap_free_untraced(self,                                                \
		                   heapptr_getptr(result_ptr),                          \
		                   heapptr_getsiz(result_ptr),                          \
		                   gfp);                                                \
		nx_on_failure                                                           \
	}
#endif /* ... */


/* Resolve existing (possibly bitset-based) mappings between [umin, umax]
 * These  functions  must  be  called  while  already  holding  the lock.
 * NOTE: If these functions return an exception/false, the lock will have been released! */
#ifdef DEFINE_X_except
PRIVATE ATTR_BLOCKLIKE_GFP(gfp) ATTR_NOINLINE void FCALL
insert_trace_node_resolve(uintptr_t umin, uintptr_t umax,
                          gfp_t gfp, unsigned int n_skip,
                          LOCK_PARAMS)
		THROWS(E_BADALLOC, E_WOULDBLOCK)
#elif defined(DEFINE_X_noexcept)
PRIVATE ATTR_BLOCKLIKE_GFP(gfp) ATTR_NOINLINE bool
NOTHROW(FCALL insert_trace_node_resolve_nx)(uintptr_t umin, uintptr_t umax,
                                            gfp_t gfp, unsigned int n_skip,
                                            LOCK_PARAMS)
#endif /* ... */
{
	struct trace_node *oldnode;
	uintptr_t overlap_min, overlap_max;
	size_t i, minbit, maxbit;

	/* Don't panic yet: We might get here because of an existing  BITSET-node
	 *                  that already has all of the area in which it overlaps
	 *                  with our new node set to be fully untraced. */
	oldnode = tm_nodes_rremove(umin, umax);
	assertf(oldnode, "Then why did tm_nodes_tryinsert() fail for %p...%p?",
	        umin, umax);
	if unlikely(oldnode->tn_kind != TRACE_NODE_KIND_BITSET) {
		tm_lock_break();
		kernel_panic_n(n_skip + 1,
		               "Attempted to trace region %p...%p that "
		               "overlaps with existing node at %p...%p\n"
		               "%[gen:c]",
		               umin, umax,
		               trace_node_umin(oldnode), trace_node_umax(oldnode),
		               &trace_node_print_traceback, oldnode);
		trace_node_free(oldnode);
		tm_lock_regain();
		goto success;
	}

	/* Calculate the overlapping address range. */
	overlap_min = umin;
	overlap_max = umax;
	if (overlap_max > trace_node_umax(oldnode))
		overlap_max = trace_node_umax(oldnode);
	if (overlap_min < trace_node_umin(oldnode))
		overlap_min = trace_node_umin(oldnode);
	assert(overlap_min <= overlap_max);

	/* Verify that all overlapping range is marked as untraced in the old node. */
	minbit = (overlap_min - trace_node_umin(oldnode)) / sizeof(void *);
	maxbit = (overlap_max - trace_node_umin(oldnode)) / sizeof(void *);
	assert(minbit <= maxbit);
	for (i = minbit; i <= maxbit; ++i) {
		size_t startbit;
		if (!trace_node_bitset_bitget(oldnode, i))
			continue;

		/* Oops... That's a kernel panic... */
		startbit = i;
		while (i < maxbit && trace_node_bitset_bitget(oldnode, i + 1))
			++i;
		kernel_panic_n(n_skip + 1,
		               "Attempted to trace region %p...%p that overlaps with "
		               "existing node at %p...%p (sub-range of %p...%p)\n"
		               "%[gen:c]",
		               umin, umax,
		               (trace_node_umin(oldnode) + startbit * sizeof(void *)),
		               (trace_node_umin(oldnode) + (i + 1) * sizeof(void *)) - 1,
		               trace_node_umin(oldnode), trace_node_umax(oldnode),
		               &trace_node_print_traceback, oldnode);

		/* Manually untrace to resolve a continue-after-panic */
		for (;;) {
			trace_node_bitset_bitoff(oldnode, startbit);
			if (startbit >= i)
				break;
			++startbit;
		}
	}

	/* So we know that the indicated range really was marked as untraced.
	 * With this in mind, we must truncate/split the BITSET-node in order
	 * to make space for the new node that's supposed to take its place. */
	if (overlap_min == trace_node_umin(oldnode)) {
		size_t i, src, count;
		if unlikely(overlap_max == trace_node_umax(oldnode)) {
			/* Special case: The entirety of the old node is being replaced.
			 * With this in mind, simply don't re-insert the existing  node,
			 * but rather free it while temporarily dropping the lock. */
			tm_lock_break();
			trace_node_free(oldnode);
			tm_lock_regain();
			goto success;
		}

		/* Must shift-down the is-traced bits of `oldnode' */
		src   = ((overlap_max + 1) - oldnode->tn_link.rb_min) / sizeof(void *);
		count = ((trace_node_umax(oldnode) /*+1*/) - (overlap_max /*+1*/)) / sizeof(void *);
		for (i = 0; i < count; ++i) {
			if (trace_node_bitset_bitget(oldnode, src)) {
				trace_node_bitset_biton(oldnode, i);
			} else {
				trace_node_bitset_bitoff(oldnode, i);
			}
			++src;
		}

		/* Truncate `oldnode' in the front */
		oldnode->tn_link.rb_min = overlap_max + 1;
	} else if (overlap_max == trace_node_umax(oldnode)) {
		/* Truncate `oldnode' in the back */
		oldnode->tn_link.rb_max = overlap_min - 1;
	} else {
		struct trace_node *lo_node, *hi_node;
		uintptr_t lo_node_min, lo_node_max;
		uintptr_t hi_node_min, hi_node_max;
		size_t lo_node_usize, hi_node_usize;
		size_t new_node_size;
		struct trace_node **pnewnode, *newnode;
		heapptr_t node_ptr;

		/* Split `oldnode' into 2 nodes, such that we'll create
		 * a gap that  allows us to  insert `node' without  any
		 * problems. */
		lo_node_min = trace_node_umin(oldnode);
		lo_node_max = overlap_min - 1;
		hi_node_min = overlap_max + 1;
		hi_node_max = trace_node_umax(oldnode);
		lo_node_usize = (lo_node_max - lo_node_min) + 1;
		hi_node_usize = (hi_node_max - hi_node_min) + 1;
		if (hi_node_usize <= lo_node_usize) {
			/* Explicitly allocate the high node */
			new_node_size = hi_node_usize;
		} else {
			/* Explicitly allocate the low node */
			new_node_size = lo_node_usize;
		}
		new_node_size /= sizeof(void *);                                     /* new_node_size = REQ_BITS */
		new_node_size = CEILDIV(new_node_size, BITSOF(trace_node_bitset_t)); /* new_node_size = REQ_BITSET_WORDS */
		new_node_size *= sizeof(trace_node_bitset_t);                        /* new_node_size = sizeof(BITSET) */
		new_node_size += offsetof(struct trace_node, tn_trace);              /* Header addend. */

		/* Allocate the tracing node. */
		tm_nodes_insert(oldnode);
		tm_lock_break();
		node_ptr = LOCAL_heap_alloc_untraced(&trace_heap, new_node_size,
		                                     TRACE_HEAP_FLAGS |
		                                     (gfp & GFP_INHERIT));
#ifdef DEFINE_X_noexcept
		if unlikely(!heapptr_getsiz(node_ptr))
			return false;
#endif /* DEFINE_X_noexcept */
		tm_lock_regain();

		/* Verify that the old node didn't change. */
		oldnode = tm_nodes_rremove(umin, umax);
#define FREE_NODE_PTR()                              \
		heap_free_untraced(&trace_heap,              \
		                   heapptr_getptr(node_ptr), \
		                   heapptr_getsiz(node_ptr), \
		                   GFP_NORMAL)
		if unlikely(!oldnode)
			goto again_free_node_ptr;
		if unlikely(oldnode->tn_kind != TRACE_NODE_KIND_BITSET) {
again_free_node_ptr_insert_oldnode:
			tm_nodes_insert(oldnode);
again_free_node_ptr:
			FREE_NODE_PTR();
			goto success;
		}

		/* (re-)calculate the overlapping address range. */
		overlap_min = umin;
		overlap_max = umax;
		if (overlap_max > trace_node_umax(oldnode))
			overlap_max = trace_node_umax(oldnode);
		if (overlap_min < trace_node_umin(oldnode))
			overlap_min = trace_node_umin(oldnode);
		assert(overlap_min <= overlap_max);

		/* (re-)verify that all overlapping range is marked as untraced in the old node. */
		minbit = (overlap_min - trace_node_umin(oldnode)) / sizeof(void *);
		maxbit = (overlap_max - trace_node_umin(oldnode)) / sizeof(void *);
		assert(minbit <= maxbit);
		for (i = minbit; i <= maxbit; ++i) {
			if unlikely(trace_node_bitset_bitget(oldnode, i))
				goto again_free_node_ptr_insert_oldnode;
		}
		if unlikely(overlap_min == trace_node_umin(oldnode) ||
		            overlap_max == trace_node_umax(oldnode))
			goto again_free_node_ptr_insert_oldnode;

		/* (re-)calculate the memory requirements of the new node. */
		lo_node_min = trace_node_umin(oldnode);
		lo_node_max = overlap_min - 1;
		hi_node_min = overlap_max + 1;
		hi_node_max = trace_node_umax(oldnode);
		lo_node_usize = (lo_node_max - lo_node_min) + 1;
		hi_node_usize = (hi_node_max - hi_node_min) + 1;
		if (hi_node_usize <= lo_node_usize) {
			/* Explicitly allocate the high node */
			lo_node       = oldnode;
			pnewnode      = &hi_node;
			new_node_size = hi_node_usize;
		} else {
			/* Explicitly allocate the low node */
			pnewnode      = &lo_node;
			hi_node       = oldnode;
			new_node_size = lo_node_usize;
		}
		new_node_size /= sizeof(void *);                                     /* new_node_size = REQ_BITS */
		new_node_size = CEILDIV(new_node_size, BITSOF(trace_node_bitset_t)); /* new_node_size = REQ_BITSET_WORDS */
		new_node_size *= sizeof(trace_node_bitset_t);                        /* new_node_size = sizeof(BITSET) */
		new_node_size += offsetof(struct trace_node, tn_trace);              /* Header addend. */
		if unlikely(new_node_size > heapptr_getsiz(node_ptr))
			goto again_free_node_ptr_insert_oldnode;
#undef FREE_NODE_PTR
		newnode   = (struct trace_node *)heapptr_getptr(node_ptr);
		*pnewnode = newnode;

		/* Initialize the node. */
		newnode->tn_size  = heapptr_getsiz(node_ptr);
		newnode->tn_reach = oldnode->tn_reach;
		newnode->tn_visit = oldnode->tn_visit;
		newnode->tn_kind  = TRACE_NODE_KIND_BITSET;
		newnode->tn_flags = oldnode->tn_flags;
		newnode->tn_tid   = task_getroottid();

		/* Split the bitset of oldnode between it, and newnode */
		{
			size_t i, src, count;
			if (oldnode == lo_node) {
				assert(newnode == hi_node);
				/* Copy the high bits from `lo_node' into `hi_node' */
				src   = maxbit + 1;
				count = ((hi_node_max + 1) - hi_node_min) / sizeof(void *);
			} else {
				assert(newnode == lo_node);
				assert(oldnode == hi_node);
				/* Copy the low bits from `hi_node' into `lo_node' */
				src   = 0;
				count = minbit;
				assert(count == ((lo_node_max + 1) - lo_node_min) / sizeof(void *));
			}
			for (i = 0; i < count; ++i) {
				if (trace_node_bitset_bitget(oldnode, src)) {
					trace_node_bitset_biton(newnode, i);
				} else {
					trace_node_bitset_bitoff(newnode, i);
				}
				++src;
			}
			if (oldnode == hi_node) {
				/* Must shift-down the bits of `hi_node' */
				count = ((hi_node_max + 1) - hi_node_min) / sizeof(void *);
				for (i = 0; i < count; ++i) {
					if (trace_node_bitset_bitget(hi_node, src)) {
						trace_node_bitset_biton(hi_node, i);
					} else {
						trace_node_bitset_bitoff(hi_node, i);
					}
					++src;
				}
			}
		}

		/* Setup the min/max bounds of the lo/hi nodes. */
		lo_node->tn_link.rb_min = lo_node_min;
		lo_node->tn_link.rb_max = lo_node_max;
		hi_node->tn_link.rb_min = hi_node_min;
		hi_node->tn_link.rb_max = hi_node_max;

		/* And finally, re-insert both the lo- and hi-nodes */
		tm_nodes_insert(lo_node);
		tm_nodes_insert(hi_node);

		/* At this point, there should be a gap between the lo- and hi-nodes
		 * that we can now use to insert the caller's `node' into the  tree. */
		goto success;
	}

	/* Re-insert `oldnode' now that it's been truncated */
	tm_nodes_insert(oldnode);
success:;
#ifdef DEFINE_X_noexcept
	return true;
#endif /* DEFINE_X_noexcept */
}

/* Begin tracing the given `node' */
#ifdef DEFINE_X_except
PRIVATE ATTR_NOINLINE ATTR_BLOCKLIKE_GFP(gfp) NONNULL((1)) void FCALL
LOCAL_insert_trace_node(struct trace_node *__restrict node,
                        gfp_t gfp, unsigned int n_skip)
		THROWS(E_BADALLOC, E_WOULDBLOCK)
#elif defined(DEFINE_X_noexcept)
PRIVATE ATTR_NOINLINE ATTR_BLOCKLIKE_GFP(gfp) NONNULL((1)) bool
NOTHROW(FCALL LOCAL_insert_trace_node)(struct trace_node *__restrict node,
                                       gfp_t gfp, unsigned int n_skip)
#endif /* ... */
{
	tm_lock_acquire();
	while unlikely(!tm_nodes_tryinsert(node)) {
#ifdef DEFINE_X_except
		LOCAL_insert_trace_node_resolve(trace_node_umin(node),
		                                trace_node_umax(node),
		                                gfp, n_skip + 1,
		                                LOCK_ARGS);
#elif defined(DEFINE_X_noexcept)
		if unlikely(!LOCAL_insert_trace_node_resolve(trace_node_umin(node),
		                                             trace_node_umax(node),
		                                             gfp, n_skip + 1,
		                                             LOCK_ARGS))
			return false;
#endif /* ... */
	}
	tm_lock_release();
#ifdef DEFINE_X_noexcept
	return true;
#endif /* DEFINE_X_noexcept */
}



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
 *                     - GFP_NOLEAK: Don't consider this range as a leak if it can't be reached
 *                     - GFP_NOWALK: Don't scan the body of this range during GC
 *                     - GFP_INHERIT: Passed along to underlying allocators.
 * @param: tb_skip:   How may traceback entries to skip when creating a traceback.
 * @return: * : Always re-returns `base' */
#ifdef DEFINE_X_except
PUBLIC ATTR_NOINLINE ATTR_BLOCKLIKE_GFP(gfp) ATTR_RETNONNULL void *KCALL
kmalloc_trace(void *base, size_t num_bytes,
              gfp_t gfp, unsigned int tb_skip)
	THROWS(E_BADALLOC, E_WOULDBLOCK)
#elif defined(DEFINE_X_noexcept)
/* Same as `kmalloc_trace()', but don't throw an exception. If the operation fails,
 * rather  than   re-returning   `base',   `NULL'   will   be   returned   instead. */
PUBLIC ATTR_BLOCKLIKE_GFP(gfp) WUNUSED void *
NOTHROW(KCALL kmalloc_trace_nx)(void *base, size_t num_bytes,
                                gfp_t gfp, unsigned int tb_skip)
#endif /* ... */
{
	struct trace_node *node;
	heapptr_t node_ptr;
	byte_t *umin, *uend;
	size_t node_size;
	umin = (byte_t *)base;
	uend = (byte_t *)base + num_bytes;
	umin = (byte_t *)CEIL_ALIGN((uintptr_t)umin, sizeof(void *));
	uend = (byte_t *)FLOOR_ALIGN((uintptr_t)uend, sizeof(void *));
	if unlikely(umin >= uend)
		goto done; /* Empty range */
	/* Calculate the minimum size that's going to be needed for an untrace-bitset. */
	node_size = (size_t)(uend - umin) / sizeof(void *);          /* node_size = REQ_BITS */
	node_size = CEILDIV(node_size, BITSOF(trace_node_bitset_t)); /* node_size = REQ_BITSET_WORDS */
	node_size *= sizeof(trace_node_bitset_t);                    /* node_size = sizeof(BITSET) */
	if (node_size < CONFIG_KERNEL_TRACE_MALLOC_MIN_TRACEBACK * sizeof(void *))
		node_size = CONFIG_KERNEL_TRACE_MALLOC_MIN_TRACEBACK * sizeof(void *);
	node_size += offsetof(struct trace_node, tn_trace);          /* Header addend. */
	/* Allocate the tracing node. */
	node_ptr = LOCAL_heap_alloc_untraced(&trace_heap, node_size,
	                                     TRACE_HEAP_FLAGS |
	                                     (gfp & GFP_INHERIT));
#ifdef DEFINE_X_noexcept
	if unlikely(!heapptr_getsiz(node_ptr))
		goto err;
#endif /* DEFINE_X_noexcept */
	node = (struct trace_node *)heapptr_getptr(node_ptr);
	/* Initialize the node. */
	node->tn_link.rb_min = (uintptr_t)umin;
	node->tn_link.rb_max = (uintptr_t)uend - 1;
	node->tn_size        = heapptr_getsiz(node_ptr);
	node->tn_reach       = gc_version;
	node->tn_visit       = 0;
	node->tn_kind        = TRACE_NODE_KIND_USER;
	node->tn_flags       = TRACE_NODE_FLAG_FROM_GFP(gfp);
	node->tn_tid         = task_getroottid();
	{
		struct lcpustate cs;
		lcpustate_current(&cs);
		/* Generate a traceback. */
		trace_malloc_generate_traceback(trace_node_traceback_vector(node),
		                                trace_node_traceback_count(node),
		                                &cs, tb_skip + 1);
	}
	/* Start tracing the node. */
#ifdef DEFINE_X_except
	TRY {
		insert_trace_node(node, gfp, 1);
	} EXCEPT
#elif defined(DEFINE_X_noexcept)
	if (!insert_trace_node_nx(node, gfp, 1))
#endif /* ... */
	{
		/* Free the previously constructed node. */
		trace_node_free(node);
#ifdef DEFINE_X_except
		RETHROW();
#elif defined(DEFINE_X_noexcept)
err:
		return NULL;
#endif /* ... */
	}

done:
	return base;
}



PUBLIC ATTR_BLOCKLIKE_GFP(flags) WUNUSED NONNULL((1)) heapptr_t
LOCAL_NOTHROW(KCALL LOCAL_heap_alloc)(struct heap *__restrict self,
                                      size_t num_bytes, gfp_t flags) {
	heapptr_t result;
	result = LOCAL_heap_alloc_untraced(self, num_bytes, flags);
	LOCAL_TRACE_OR_FAIL(result, flags, {
		result = heapptr_make(NULL, 0);
	})
	return result;
}


PUBLIC ATTR_BLOCKLIKE_GFP(flags) WUNUSED NONNULL((1)) heapptr_t
LOCAL_NOTHROW(KCALL LOCAL_heap_align)(struct heap *__restrict self,
                                      size_t min_alignment, ptrdiff_t offset,
                                      size_t num_bytes, gfp_t flags) {
	heapptr_t result;
	result = LOCAL_heap_align_untraced(self, min_alignment,
	                                   offset, num_bytes,
	                                   flags);
	LOCAL_TRACE_OR_FAIL(result, flags, {
		result = heapptr_make(NULL, 0);
	})
	return result;
}


PUBLIC ATTR_BLOCKLIKE_GFP(alloc_flags) WUNUSED NONNULL((1)) heapptr_t
LOCAL_NOTHROW(KCALL LOCAL_heap_realloc)(struct heap *__restrict self,
                                        VIRT void *old_ptr, size_t old_bytes,
                                        size_t new_bytes, gfp_t alloc_flags,
                                        gfp_t free_flags) {
	size_t missing_bytes;
	assert(IS_ALIGNED(old_bytes, HEAP_ALIGNMENT));
	assert(!old_bytes || IS_ALIGNED((uintptr_t)old_ptr, HEAP_ALIGNMENT));
	assert(!old_bytes || old_bytes >= HEAP_MINSIZE);
	if (old_bytes == 0) {
		heapptr_t result;
		if unlikely(alloc_flags & GFP_NOMOVE)
			goto err;
		/* Special case: initial allocation */
		result = LOCAL_heap_alloc_untraced(self, new_bytes, alloc_flags);
		LOCAL_TRACE_OR_FAIL(result, alloc_flags, goto err;)
		return result;
	}
	if unlikely(OVERFLOW_UADD(new_bytes, (size_t)(HEAP_ALIGNMENT - 1), &new_bytes)) {
#ifdef DEFINE_X_except
		THROW(E_BADALLOC_INSUFFICIENT_HEAP_MEMORY,
		      new_bytes - (HEAP_ALIGNMENT - 1));
#elif defined(DEFINE_X_noexcept)
		goto err;
#endif /* ... */
	}
	new_bytes &= ~(HEAP_ALIGNMENT - 1);
	if unlikely(new_bytes < HEAP_MINSIZE)
		new_bytes     = HEAP_MINSIZE;
	if (new_bytes <= old_bytes) {
		size_t free_bytes;
		/* Free trailing memory. */
		free_bytes = old_bytes - new_bytes;
		if (free_bytes >= HEAP_MINSIZE) {
			heap_free(self,
			          (byte_t *)old_ptr + new_bytes,
			          free_bytes,
			          free_flags);
			old_bytes = new_bytes;
		}
		return heapptr_make(old_ptr, old_bytes);
	}
	missing_bytes = new_bytes - old_bytes;
	missing_bytes = LOCAL_heap_allat_untraced(self, (byte_t *)old_ptr + old_bytes,
	                                          missing_bytes, alloc_flags);
	if (missing_bytes) {
		/* Managed to extend the data block. */
		struct trace_node *node;

		/* Try to extend an existing trace-node at `old_ptr+old_bytes-1'
		 *
		 * This is required to ensure that any pointer into the returned
		 * data-block is considered  as a valid  method of marking  said
		 * block as reachable.
		 *
		 * If we were to create individual blocks for each realloc'd part
		 * of a larger chunk of memory, then pointers would have to exist
		 * that point into each individual chunk, or we'd consider  those
		 * chunks without pointers as leaks! */
		tm_lock_acquire();
		node = tm_nodes_remove((byte_t *)old_ptr + old_bytes - 1);
		if likely(node) {
			if unlikely(node->tn_link.rb_max != (uintptr_t)((byte_t *)old_ptr + old_bytes - 1)) {
				tm_nodes_insert(node);
				node = trace_node_dupa_tb(node);
				tm_lock_break();
				kernel_panic_n(/* n_skip: */ 1,
				               PP_STR(LOCAL_heap_realloc) "(%p,%" PRIuSIZ ",%" PRIuSIZ ",%#x,%#x): "
				               "New allocation %p-%p overlaps with node %p-%p\n"
				               "%[gen:c]",
				               old_ptr, old_bytes, new_bytes, alloc_flags, free_flags,
				               (byte_t *)old_ptr + old_bytes,
				               (byte_t *)old_ptr + old_bytes + missing_bytes - 1,
				               trace_node_umin(node), trace_node_umax(node),
				               &trace_node_print_traceback, node);
				tm_lock_regain();
			} else {
				/* Expand the existing node. */
				node->tn_link.rb_max += missing_bytes;
				tm_nodes_insert(node);
				tm_lock_break();
				goto inplace_success;
			}
		}
		tm_lock_release();

		/* Create  a new  node for  the block  as a whole.
		 * This is the case when the original block wasn't
		 * being  traced, but after realloc is becomes so. */
#ifdef DEFINE_X_except
		TRY {
			kmalloc_trace((byte_t *)old_ptr, old_bytes + missing_bytes, alloc_flags, 1);
		} EXCEPT
#elif defined(DEFINE_X_noexcept)
		if unlikely(!kmalloc_trace_nx((byte_t *)old_ptr, old_bytes + missing_bytes, alloc_flags, 1))
#endif /* ... */
		{
			heap_free_untraced(self, (byte_t *)old_ptr + old_bytes, missing_bytes, alloc_flags);
#ifdef DEFINE_X_except
			RETHROW();
#elif defined(DEFINE_X_noexcept)
			goto err;
#endif /* ... */
		}
inplace_success:
		return heapptr_make(old_ptr, old_bytes + missing_bytes);
	}
	if (alloc_flags & GFP_NOMOVE)
		goto err;
	{
		heapptr_t result;
		/* Must allocate an entirely new data block and copy memory to it. */
		result = LOCAL_heap_alloc_untraced(self, new_bytes, alloc_flags);
		LOCAL_TRACE_OR_FAIL(result, alloc_flags, goto err;)
		memcpy(heapptr_getptr(result), old_ptr, old_bytes);

		/* Free the old data block. */
		heap_free(self, old_ptr, old_bytes,
		          free_flags & ~GFP_CALLOC);
		return result;
	}
err:
	return heapptr_make(NULL, 0);
}

PUBLIC ATTR_BLOCKLIKE_GFP(alloc_flags) WUNUSED NONNULL((1)) heapptr_t
LOCAL_NOTHROW(KCALL LOCAL_heap_realign)(struct heap *__restrict self,
                                        VIRT void *old_ptr, size_t old_bytes,
                                        size_t min_alignment, ptrdiff_t offset,
                                        size_t new_bytes, gfp_t alloc_flags,
                                        gfp_t free_flags) {
	size_t missing_bytes;
	assert(IS_ALIGNED(old_bytes, HEAP_ALIGNMENT));
	assert(!old_bytes || IS_ALIGNED((uintptr_t)old_ptr, HEAP_ALIGNMENT));
	assert(!old_bytes || old_bytes >= HEAP_MINSIZE);
	if (old_bytes == 0) {
		heapptr_t result;
		if unlikely(alloc_flags & GFP_NOMOVE)
			goto err;

		/* Special case: initial allocation */
		result = LOCAL_heap_align_untraced(self, min_alignment, offset,
		                                   new_bytes, alloc_flags);
		LOCAL_TRACE_OR_FAIL(result, alloc_flags, goto err;)
		return result;
	}

	if unlikely(OVERFLOW_UADD(new_bytes, (size_t)(HEAP_ALIGNMENT - 1), &new_bytes)) {
#ifdef DEFINE_X_except
		THROW(E_BADALLOC_INSUFFICIENT_HEAP_MEMORY,
		      new_bytes - (HEAP_ALIGNMENT - 1));
#elif defined(DEFINE_X_noexcept)
		goto err;
#endif /* ... */
	}
	new_bytes &= ~(HEAP_ALIGNMENT - 1);
	if (new_bytes <= old_bytes) {
		size_t free_bytes;
		if unlikely(new_bytes < HEAP_MINSIZE)
			new_bytes = HEAP_MINSIZE;
		/* Free trailing memory. */
		free_bytes = old_bytes - new_bytes;
		if (free_bytes >= HEAP_MINSIZE) {
			heap_free(self, (byte_t *)old_ptr + new_bytes,
			          free_bytes, free_flags);
			old_bytes = new_bytes;
		}
		return heapptr_make(old_ptr, old_bytes);
	}
	missing_bytes = new_bytes - old_bytes;
	missing_bytes = LOCAL_heap_allat_untraced(self, (byte_t *)old_ptr + old_bytes,
	                                          missing_bytes, alloc_flags);
	if (missing_bytes) {
		/* Managed to extend the data block. */
		struct trace_node *node;

		/* Try to extend an existing trace-node at `old_ptr+old_bytes-1'
		 *
		 * This is required to ensure that any pointer into the returned
		 * data-block is considered  as a valid  method of marking  said
		 * block as reachable.
		 *
		 * If we were to create individual blocks for each realloc'd part
		 * of a larger chunk of memory, then pointers would have to exist
		 * that point into each individual chunk, or we'd consider  those
		 * chunks without pointers as leaks! */
		tm_lock_acquire();
		node = tm_nodes_remove((byte_t *)old_ptr + old_bytes - 1);
		if likely(node) {
			if unlikely(node->tn_link.rb_max != (uintptr_t)((byte_t *)old_ptr + old_bytes - 1)) {
				tm_nodes_insert(node);
				node = trace_node_dupa_tb(node);
				tm_lock_break();
				kernel_panic_n(/* n_skip: */ 1,
				               PP_STR(LOCAL_heap_realign) "(%p,%" PRIuSIZ ",%" PRIuSIZ ",%" PRIuSIZ ",%" PRIdSIZ ",%#x,%#x): "
				               "New allocation %p-%p overlaps with node %p-%p\n"
				               "%[gen:c]",
				               old_ptr, old_bytes, min_alignment, offset, new_bytes, alloc_flags, free_flags,
				               (byte_t *)old_ptr + old_bytes,
				               (byte_t *)old_ptr + old_bytes + missing_bytes - 1,
				               trace_node_umin(node), trace_node_umax(node),
				               &trace_node_print_traceback, node);
				tm_lock_regain();
			} else {
				/* Expand the existing node. */
				node->tn_link.rb_max += missing_bytes;
				tm_nodes_insert(node);
				tm_lock_break();
				goto inplace_success;
			}
		}
		tm_lock_release();

		/* Create  a new  node for  the block  as a whole.
		 * This is the case when the original block wasn't
		 * being  traced, but after realloc is becomes so. */
#ifdef DEFINE_X_except
		TRY {
			kmalloc_trace((byte_t *)old_ptr, old_bytes + missing_bytes, alloc_flags, 1);
		} EXCEPT
#elif defined(DEFINE_X_noexcept)
		if unlikely(!kmalloc_trace_nx((byte_t *)old_ptr, old_bytes + missing_bytes, alloc_flags, 1))
#endif /* ... */
		{
			heap_free_untraced(self, (byte_t *)old_ptr + old_bytes, missing_bytes, alloc_flags);
#ifdef DEFINE_X_except
			RETHROW();
#elif defined(DEFINE_X_noexcept)
			goto err;
#endif /* ... */
		}

inplace_success:
		return heapptr_make(old_ptr, old_bytes + missing_bytes);
	}
	if (alloc_flags & GFP_NOMOVE)
		goto err;
	{
		heapptr_t result;
		/* Must allocate an entirely new data block and copy memory to it. */
		result = LOCAL_heap_align_untraced(self,
		                                   min_alignment,
		                                   offset,
		                                   new_bytes,
		                                   alloc_flags);
		LOCAL_TRACE_OR_FAIL(result, alloc_flags, goto err;)
		memcpy(heapptr_getptr(result), old_ptr, old_bytes);
		/* Free the old data block. */
		heap_free(self, old_ptr, old_bytes,
		          free_flags & ~GFP_CALLOC);
		return result;
	}
err:
	return heapptr_make(NULL, 0);
}

DECL_END

#ifndef __INTELLISENSE__
#define DEFINE_METHOD_kmalloc
#include "trace-malloc-kmalloc.inl"
#define DEFINE_METHOD_kmalloc_in_place
#include "trace-malloc-kmalloc.inl"
#define DEFINE_METHOD_kmemalign
#include "trace-malloc-kmalloc.inl"
#define DEFINE_METHOD_kmemalign_offset
#include "trace-malloc-kmalloc.inl"


#undef LOCAL_NOTHROW

#undef LOCAL_heap_alloc
#undef LOCAL_heap_alloc_untraced
#undef LOCAL_heap_align
#undef LOCAL_heap_align_untraced
#undef LOCAL_heap_realloc
#undef LOCAL_heap_realloc_untraced
#undef LOCAL_heap_allat
#undef LOCAL_heap_allat_untraced
#undef LOCAL_heap_realign
#undef LOCAL_heap_realign_untraced

#undef LOCAL_kmalloc
#undef LOCAL_kmemalign
#undef LOCAL_kmemalign_offset
#undef LOCAL_krealloc_in_place
#undef LOCAL_krealloc
#undef LOCAL_krealign
#undef LOCAL_krealign_offset

#undef LOCAL_insert_trace_node_resolve
#undef LOCAL_insert_trace_node

#undef LOCAL_TRACE_OR_FAIL

#undef DEFINE_X_except
#undef DEFINE_X_noexcept
#endif /* !__INTELLISENSE__ */
