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
#ifndef GUARD_KERNEL_SRC_MEMORY_TRACE_MALLOC_C
#define GUARD_KERNEL_SRC_MEMORY_TRACE_MALLOC_C 1
#define NO_INSTRUMENT_KMALLOC
#define __OMIT_KMALLOC_CONSTANT_P_WRAPPERS
#define __OMIT_HEAP_TRACED_CONSTANT_P_WRAPPERS
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/malloc-defs.h>

/* Quick toggle to disable debug_malloc (and use the weak definitions from `malloc.c').
 * NOTE: You can also achieve identical effects by passing "nomall" on the kernel
 *       commandline, which  redirects all  traced malloc  functions to  untraced
 *       counterparts during early boot. */
#if 0
#undef CONFIG_HAVE_KERNEL_TRACE_MALLOC
#endif

#ifdef CONFIG_HAVE_KERNEL_TRACE_MALLOC
#include <debugger/config.h>
#include <debugger/hook.h>
#include <debugger/io.h>
#include <debugger/util.h>
#include <kernel/addr2line.h>
#include <kernel/except.h>
#include <kernel/fs/allnodes.h>
#include <kernel/fs/node.h>
#include <kernel/fs/super.h>
#include <kernel/heap.h>
#include <kernel/malloc.h>
#include <kernel/mman.h>
#include <kernel/mman/mcoreheap.h>
#include <kernel/mman/mnode.h>
#include <kernel/mman/mpart.h>
#include <kernel/mman/unmapped.h>
#include <kernel/panic.h>
#include <kernel/printk.h>
#include <kernel/slab.h>
#include <kernel/syslog.h>
#include <sched/cpu.h>
#include <sched/enum.h>
#include <sched/group.h>
#include <sched/scheduler.h>
#include <sched/task.h>

#include <hybrid/align.h>
#include <hybrid/overflow.h>
#include <hybrid/sched/atomic-lock.h>
#include <hybrid/sched/preemption.h>
#include <hybrid/sequence/rbtree.h>

#include <kos/aref.h>
#include <kos/kernel/cpu-state-helpers.h>
#include <kos/kernel/cpu-state.h>
#include <sys/param.h>

#include <alloca.h>
#include <assert.h>
#include <format-printer.h>
#include <inttypes.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include <libinstrlen/instrlen.h>
#include <libunwind/errno.h>
#include <libunwind/register.h>
#include <libunwind/unwind.h>

/**/
#include "trace-malloc.h"

DECL_BEGIN

#define TRACE_NODE_KIND_MALL   0x00 /* Normal kmalloc() memory */
#define TRACE_NODE_KIND_USER   0x01 /* Custom, mall_trace()'d memory */
#define TRACE_NODE_KIND_BITSET 0x02 /* Custom, mall_trace()'d  memory, but  instead  of having  a  vector
                                     * of traceback locations,  this node has  a bitset describing  which
                                     * of  its  pointed-to memory  is still  being  traced. This  kind of
                                     * node is needed to represent  the result of mall_trace(),  followed
                                     * by mall_untrace_n(), where the  range being untraced doesn't  span
                                     * or touch any node borders, in which  case a node would have to  be
                                     * split into 2 parts. If at that point the system fails to  allocate
                                     * a secondary node, the original node it transformed into this kind,
                                     * and given a  bitset of POINTER-aligned  memory locations that  are
                                     * still considered as traced. */
#ifdef CONFIG_HAVE_KERNEL_SLAB_ALLOCATORS
#define TRACE_NODE_KIND_SLAB   0x03 /* Does not actually appear in the nodes tree.
                                     * Only used  when  dumping/discarding  leaks. */
#endif /* CONFIG_HAVE_KERNEL_SLAB_ALLOCATORS */
#define TRACE_NODE_KIND_CORE   0x04 /* Like slab, referencing `mcoreheap_alloc()' */
#define TRACE_NODE_KIND_MNODE  0x05 /* Unreachable kernel mman mnode. */

#define TRACE_NODE_KIND_HAS_PADDING(kind)   ((kind) == TRACE_NODE_KIND_MALL)
#define TRACE_NODE_KIND_HAS_TRACEBACK(kind) ((kind) != TRACE_NODE_KIND_BITSET)

#define TRACE_NODE_FLAG_NOLEAK 0x10 /* FLAG: Don't consider this one a leak. */
#define TRACE_NODE_FLAG_NOWALK 0x20 /* FLAG: Don't search this one's contents for other reachable locations. */
#define TRACE_NODE_FLAG_ISRED  0x40 /* Reg flag. */


#if ((GFP_NOLEAK >> 12) == TRACE_NODE_FLAG_NOLEAK && \
     (GFP_NOWALK >> 12) == TRACE_NODE_FLAG_NOWALK)
#define TRACE_NODE_FLAG_FROM_GFP(gfp) \
	(((gfp) & __GFP_HEAPMASK) | ((gfp) & (GFP_NOLEAK | GFP_NOWALK)) >> 12)
#else /* ... */
#define TRACE_NODE_FLAG_FROM_GFP(gfp)                    \
	(((gfp) & __GFP_HEAPMASK) |                          \
	 ((gfp) & GFP_NOLEAK ? TRACE_NODE_FLAG_NOLEAK : 0) | \
	 ((gfp) & GFP_NOWALK ? TRACE_NODE_FLAG_NOWALK : 0))
#endif /* !... */

struct trace_node {
	RBTREE_NODE_WITH_KEY(trace_node, uintptr_t)
	            tn_link;  /* [const] Trace node link. */
#define trace_node_initlink(self, base, num_bytes) \
	((self)->tn_link.rb_min = (uintptr_t)(base),   \
	 (self)->tn_link.rb_max = (uintptr_t)(base) + (num_bytes)-1)
	size_t      tn_size;  /* [const] Allocated heap size of this TRACE-node. */
	u8          tn_reach; /* Last leak-check iteration when this node was reached. */
	u8          tn_visit; /* Last leak-check iteration when this node was visited. */
	u8          tn_flags; /* Node flags (or'd with `__GFP_HEAPMASK') */
	u8          tn_kind;  /* Node kind (one of `TRACE_NODE_KIND_*') */
	u32         tn_tid;   /* [const] ROOT-namespace TID of the allocating thread. */
	COMPILER_FLEXIBLE_ARRAY(void const *, tn_trace);
	                      /* [1..1][0..MALLNODE_TRACESZ(self)]
	                       * Traceback of where the pointer was originally allocated. */
};

/************************************************************************/
/* LEAK HELPERS                                                         */
/************************************************************************/
#define trace_node_leak_next(self)            ((self)->tn_link.rb_lhs)
#define trace_node_leak_getxrefs(self)        ((size_t)(self)->tn_link.rb_rhs)
#define trace_node_leak_setxrefs(self, value) ((self)->tn_link.rb_rhs = (struct trace_node *)(size_t)(value))
#if CONFIG_KERNEL_MALL_HEAD_SIZE != 0 || CONFIG_KERNEL_MALL_TAIL_SIZE != 0
#define trace_node_leak_getscan_uminmax(self, scan_umin, scan_umax)               \
	((self)->tn_kind == TRACE_NODE_KIND_MALL                                      \
	 ? (void)((scan_umin) = trace_node_umin(self) + CONFIG_KERNEL_MALL_HEAD_SIZE, \
	          (scan_umax) = trace_node_umax(self) - CONFIG_KERNEL_MALL_TAIL_SIZE) \
	 : (void)((scan_umin) = trace_node_umin(self),                                \
	          (scan_umax) = trace_node_umax(self)))
#else /* CONFIG_KERNEL_MALL_HEAD_SIZE != 0 || CONFIG_KERNEL_MALL_TAIL_SIZE != 0 */
#define trace_node_leak_getscan_uminmax(self, scan_umin, scan_umax) \
	(void)((scan_umin) = trace_node_umin(self),                     \
	       (scan_umax) = trace_node_umax(self))
#endif /* CONFIG_KERNEL_MALL_HEAD_SIZE == 0 && CONFIG_KERNEL_MALL_TAIL_SIZE == 0 */


/************************************************************************/
/* GENERIC HELPERS                                                      */
/************************************************************************/
#define trace_node_umin(self)  ((self)->tn_link.rb_min)
#define trace_node_umax(self)  ((self)->tn_link.rb_max)
#define trace_node_uaddr(self) ((byte_t *)(self)->tn_link.rb_min)       /* NOTE: This one's always pointer-aligned! */
#define trace_node_uend(self)  ((byte_t *)((self)->tn_link.rb_max + 1)) /* NOTE: This one's always pointer-aligned! */
#define trace_node_usize(self) (((self)->tn_link.rb_max - (self)->tn_link.rb_min) + 1)


/************************************************************************/
/* TRACEBACK HELPERS                                                    */
/************************************************************************/
/* Return the base address of a `void **'-vector of PC-locations. */
#define trace_node_traceback_vector(self) ((self)->tn_trace)
/* Return the upper limit of how many elements are in the traceback vector.
 * The vector may terminate prematurely  when a NULL-entry is  encountered. */
#define trace_node_traceback_count(self) (((self)->tn_size - offsetof(struct trace_node, tn_trace)) / sizeof(void *))


/************************************************************************/
/* HELPERS FOR `TRACE_NODE_KIND_BITSET'                                 */
/************************************************************************/
typedef uintptr_t trace_node_bitset_t;

/* Return the address of the is-traced bitset */
#define trace_node_bitset_words(self) ((trace_node_bitset_t *)(self)->tn_trace)

/* Return the # of bits within the is-traced bitset. (s.a. `trace_node_bitset_words()') */
#define trace_node_bitset_count(self) (trace_node_usize(self) / __SIZEOF_POINTER__)

#define trace_node_bitset_words_word(i) ((i) / BITSOF(trace_node_bitset_t))
#define trace_node_bitset_words_mask(i) ((trace_node_bitset_t)1 << ((i) % BITSOF(trace_node_bitset_t)))

#define trace_node_bitset_bitget(self, i) (trace_node_bitset_words(self)[trace_node_bitset_words_word(i)] & trace_node_bitset_words_mask(i))
#define trace_node_bitset_biton(self, i)  (trace_node_bitset_words(self)[trace_node_bitset_words_word(i)] |= trace_node_bitset_words_mask(i))
#define trace_node_bitset_bitoff(self, i) (trace_node_bitset_words(self)[trace_node_bitset_words_word(i)] &= ~trace_node_bitset_words_mask(i))


/* Example code for enumerating traced words of a `TRACE_NODE_KIND_BITSET'-node:
 * >> if (node->tn_kind == TRACE_NODE_KIND_BITSET) {
 * >>     trace_node_bitset_t *words;
 * >>     uintptr_t *uaddr;
 * >>     size_t i, count;
 * >>     uaddr = trace_node_bitset_uaddr(node);
 * >>     words = trace_node_bitset_words(node);
 * >>     count = trace_node_bitset_count(node);
 * >>     for (i = 0; i < count; ++i) {
 * >>          trace_node_bitset_t word, mask;
 * >>          word = words[trace_node_bitset_words_word(i)];
 * >>          mask = trace_node_bitset_words_mask(i);
 * >>          if (word & mask) {
 * >>              HANDLE_TRACED_POINTER(&uaddr[i]);
 * >>          }
 * >>     }
 * >> }
 */


PRIVATE ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW(KCALL sizeof_trace_node_for_tb)(struct trace_node *__restrict self) {
	size_t result, count;
	if (!TRACE_NODE_KIND_HAS_TRACEBACK(self->tn_kind))
		return offsetof(struct trace_node, tn_trace);
	count = trace_node_bitset_count(self);
	for (result = 0; result < count; ++result) {
		if (!trace_node_traceback_vector(self)[result])
			break;
	}
	result *= sizeof(void *);
	result += offsetof(struct trace_node, tn_trace);
	return result;
}

PRIVATE ATTR_RETNONNULL WUNUSED NONNULL((1)) struct trace_node *
NOTHROW(KCALL copy_trace_node_for_tb)(struct trace_node *__restrict copy,
                                      struct trace_node *__restrict self,
                                      size_t sizeof_copy) {
	memcpy(copy, self, sizeof_copy);
	copy->tn_size = sizeof_copy;
	return copy;
}

/* Duplicate the given trace-node for the purpose of logging. */
#define trace_node_dupa_tb(self)                                                       \
	({                                                                                 \
		size_t _dup_siz = sizeof_trace_node_for_tb(self);                              \
		copy_trace_node_for_tb((struct trace_node *)alloca(_dup_siz), self, _dup_siz); \
	})


DECL_END

/* Define the ABI for the address tree used by trace nodes. */
#if 0 /* Don't  use left-leaning RB-trees  (for now). Technically  we could do this,
       * and the only  thing stopping  this from  happening is  this `#if 0',  which
       * you are  free to  change to  `#if 1'. But  since normal  RB-trees are  just
       * that tiny bit faster than left-leaning ones when it comes to insert/remove,
       * we always just  use the normal  ones, just  so we can  slightly reduce  the
       * performance impact caused by the trace-malloc sub-system. */
#define RBTREE_LEFT_LEANING
#endif
#define RBTREE_WANT_RREMOVE
#define RBTREE_WANT_TRYINSERT
#define RBTREE(name)         trace_node_tree_##name
#define RBTREE_T             struct trace_node
#define RBTREE_Tkey          uintptr_t
#define RBTREE_GETNODE(self) (self)->tn_link
#define RBTREE_REDFIELD      tn_flags
#define RBTREE_REDBIT        TRACE_NODE_FLAG_ISRED
#define RBTREE_WANT_MINMAXLOCATE
#define RBTREE_WANT_PREV_NEXT_NODE
#ifdef RBTREE_LEFT_LEANING
#define tm_nodes_prevnode(node) trace_node_tree_prevnode(tm_nodes, node)
#define tm_nodes_nextnode(node) trace_node_tree_nextnode(tm_nodes, node)
#else /* RBTREE_LEFT_LEANING */
#define tm_nodes_prevnode(node) trace_node_tree_prevnode(node)
#define tm_nodes_nextnode(node) trace_node_tree_nextnode(node)
#endif /* !RBTREE_LEFT_LEANING */
#define tm_nodes_minmaxlocate(minkey, maxkey, result) trace_node_tree_minmaxlocate(tm_nodes, minkey, maxkey, result)
#include <hybrid/sequence/rbtree-abi.h>

DECL_BEGIN

/* SMP-lock for accessing internal TRACE-malloc structures. */
#ifndef CONFIG_NO_SMP
PRIVATE ATTR_MALL_UNTRACKED struct atomic_lock tm_smplock = ATOMIC_LOCK_INIT;
DEFINE_DBG_BZERO_OBJECT(tm_smplock);
#endif /* !CONFIG_NO_SMP */
#define tm_smplock_acquire_smp_r(p_flag) atomic_lock_acquire_smp_r(&tm_smplock, p_flag)
#define tm_smplock_release_smp_r(p_flag) atomic_lock_release_smp_r(&tm_smplock, p_flag)

#define LOCK_PARAMS preemption_flag_t _l_was
#define LOCK_ARGS   _l_was

#define lock_acquire()            \
	do {                          \
		preemption_flag_t _l_was; \
		tm_smplock_acquire_smp_r(&_l_was)
#define lock_break()  tm_smplock_release_smp_r(&_l_was)
#define lock_regain() tm_smplock_acquire_smp_r(&_l_was)
#define lock_release()                  \
		tm_smplock_release_smp_r(&_l_was); \
	}	__WHILE0


/* [0..1] Tree of traced nodes */
PRIVATE ATTR_MALL_UNTRACKED RBTREE_ROOT(trace_node) tm_nodes = NULL;
#define tm_nodes_locate(ptr)       trace_node_tree_locate(tm_nodes, (uintptr_t)(ptr))
#define tm_nodes_remove(ptr)       trace_node_tree_remove(&tm_nodes, (uintptr_t)(ptr))
#define tm_nodes_rlocate(min, max) trace_node_tree_rlocate(tm_nodes, min, max)
#define tm_nodes_rremove(min, max) trace_node_tree_rremove(&tm_nodes, min, max)
#define tm_nodes_removenode(node)  trace_node_tree_removenode(&tm_nodes, node)
#define tm_nodes_insert(node)      trace_node_tree_insert(&tm_nodes, node)
#define tm_nodes_tryinsert(node)   trace_node_tree_tryinsert(&tm_nodes, node)


/* Debug-heap used for allocating `struct trace_node' objects. */
INTERN struct heap trace_heap =
HEAP_INIT(PAGESIZE * 4,
          PAGESIZE * 16,
          MHINT_GETADDR(KERNEL_MHINT_DHEAP),
          MHINT_GETMODE(KERNEL_MHINT_DHEAP));
DEFINE_VALIDATABLE_HEAP(trace_heap);
DEFINE_DBG_BZERO_OBJECT(trace_heap.h_lock);
#define TRACE_HEAP_FLAGS (GFP_NORMAL | GFP_LOCKED | GFP_PREFLT)



PRIVATE NOBLOCK void
NOTHROW(KCALL trace_node_free)(struct trace_node *__restrict self) {
	heap_free_untraced(&trace_heap,
	                   self,
	                   self->tn_size,
	                   TRACE_HEAP_FLAGS);
}


/* Generator-compatible ("%[gen:c]") function to print the traceback of a given node. */
PRIVATE ATTR_COLDTEXT ssize_t KCALL
trace_node_print_traceback(struct trace_node *__restrict self,
                           pformatprinter printer, void *arg) {
	ssize_t temp, result = 0;
	size_t i, max_count;
	if unlikely(!TRACE_NODE_KIND_HAS_TRACEBACK(self->tn_kind))
		goto done;
	max_count = trace_node_traceback_count(self);
	for (i = 0; i < max_count; ++i) {
		void const *prev_pc, *pc;
		pc = trace_node_traceback_vector(self)[i];
		if (!pc)
			break;
		prev_pc = instruction_trypred(pc, ISA_DEFAULT);
		if (i) {
			temp = addr2line_printf(printer, arg, prev_pc, pc,
			                        "Called here");
		} else {
			temp = addr2line_printf(printer, arg, prev_pc, pc,
			                        "Allocated from here [tid=%" PRIu32 "]",
			                        self->tn_tid);
		}
		if unlikely(temp < 0)
			goto err;
		result += temp;
	}
done:
	return result;
err:
	return temp;
}



/* Find the trace-block that `ptr' is apart of and remove it.
 * If  no  such   block  exists,  the   kernel  will   panic.
 * For this  purpose, `CEIL_ALIGN(ptr, sizeof(void *))'  must
 * point somewhere into an address range that has  previously
 * been registered by `kmalloc_trace()'.
 * NOTE: When `ptr' is `NULL', then this function does nothing. */
PUBLIC NOBLOCK ATTR_NOINLINE void
NOTHROW(KCALL kmalloc_untrace)(void *ptr) {
	struct trace_node *node;
	if unlikely(!ptr)
		return;
	ptr = (void *)CEIL_ALIGN((uintptr_t)ptr, sizeof(void *));
	lock_acquire();
	node = tm_nodes_remove(ptr);
	if unlikely(!node) {
		lock_break();
		kernel_panic_n(/* n_skip: */ 1,
		               "kmalloc_untrace(%p): No node at this location",
		               ptr);
		return;
	}
	switch (node->tn_kind) {

	case TRACE_NODE_KIND_MALL: {
		/* kmalloc_untrace() cannot be used to untrace internal kmalloc() tracings! */
		lock_break();
		kernel_panic_n(/* n_skip: */ 1,
		               "kmalloc_untrace(%p): Cannot untrace kmalloc()-pointer %p...%p\n"
		               "%[gen:c]",
		               ptr, trace_node_umin(node), trace_node_umax(node),
		               &trace_node_print_traceback, node);
		trace_node_free(node);
		return;
	}	break;

	case TRACE_NODE_KIND_BITSET: {
		size_t i, ptr_index, minbit, maxbit, limit;
		/* Special case: Partially untraced node. */
		ptr_index = (size_t)((byte_t *)ptr - trace_node_uaddr(node)) / sizeof(void *);
		limit     = trace_node_bitset_count(node);
		assert(limit);
		--limit;
		assert(ptr_index <= limit);
		if unlikely(!trace_node_bitset_bitget(node, ptr_index)) {
			lock_break();
			kernel_panic_n(/* n_skip: */ 1,
			               "kmalloc_untrace(%p): Node at %p...%p was already untraced",
			               ptr, trace_node_umin(node), trace_node_umax(node));
			return;
		}
		minbit = ptr_index;
		maxbit = ptr_index;
		while (minbit > 0 && trace_node_bitset_bitget(node, minbit - 1))
			--minbit;
		while (maxbit < limit && trace_node_bitset_bitget(node, maxbit + 1))
			++maxbit;
		if (minbit == 0 && maxbit == limit) {
			/* Completely remove this node. */
			lock_break();
			trace_node_free(node);
			return;
		}
		/* Mark all address locations in [minbit, maxbit] as untraced. */
		for (i = minbit; i <= maxbit; ++i)
			trace_node_bitset_bitoff(node, i);
		/* Re-insert the node into the tree */
		tm_nodes_insert(node);
		lock_break();
		return;
	}	break;

	default: break;
	}

	/* Since we're supposed to get rid of the whole node, we can simply
	 * release the trace-lock, and free  the node, since we've  already
	 * removed it from the tree. */
	lock_release();
	trace_node_free(node);
}



PRIVATE NOBLOCK ATTR_NOINLINE void
NOTHROW(KCALL kmalloc_untrace_n_impl)(void *base, size_t num_bytes,
                                      unsigned int n_skip) {
	uintptr_t endaddr;
	if unlikely(!IS_ALIGNED((uintptr_t)base, sizeof(void *))) {
		size_t offset = sizeof(void *) - ((uintptr_t)base & (sizeof(void *) - 1));
		if unlikely(offset >= num_bytes)
			return;
		base = (byte_t *)base + offset;
		num_bytes -= offset;
	}
	assert(((uintptr_t)base & (sizeof(void *) - 1)) == 0);
	num_bytes = FLOOR_ALIGN(num_bytes, sizeof(void *));
	endaddr   = (uintptr_t)base + num_bytes;
again_while_num_bytes:
	while (num_bytes) {
		struct trace_node *node;
		lock_acquire();
		node = tm_nodes_remove(base);
		if unlikely(!node) {
			lock_break();
			kernel_panic_n(/* n_skip: */ n_skip + 1,
			               "kmalloc_untrace_n(%p...%p): No node at %p",
			               base, endaddr - 1, base);
			return;
		}
		if unlikely(node->tn_kind == TRACE_NODE_KIND_MALL) {
			lock_break();
			kernel_panic_n(/* n_skip: */ n_skip + 1,
			               "kmalloc_untrace_n(%p...%p): Cannot untrace kmalloc()-pointer %p...%p\n"
			               "%[gen:c]",
			               base, endaddr - 1, trace_node_umin(node), trace_node_umax(node),
			               &trace_node_print_traceback, node);
			trace_node_free(node);
			return;
		}
		assert((uintptr_t)base >= trace_node_umin(node));
		if (node->tn_kind == TRACE_NODE_KIND_BITSET) {
			/* Assert that every byte of the given range is still marked as traced. */
			size_t i, minbit, maxbit;
			minbit = ((uintptr_t)base - trace_node_umin(node)) / sizeof(void *);
			maxbit = trace_node_bitset_count(node);
			if (endaddr <= trace_node_umax(node)) {
				size_t new_maxbit;
				new_maxbit = ((endaddr - sizeof(void *)) - trace_node_umin(node)) / sizeof(void *);
				assert(new_maxbit < maxbit);
				maxbit = new_maxbit;
			}
			assert(minbit <= maxbit);
			for (i = minbit; i <= maxbit; ++i) {
				size_t untrace_min, untrace_max;
				if (trace_node_bitset_bitget(node, i))
					continue;
				/* oops... Found a bit that's already been untraced... */
				untrace_min = i;
				while (i < maxbit && !trace_node_bitset_bitget(node, i + 1))
					++i;
				untrace_max = i;
				lock_break();
				kernel_panic_n(/* n_skip: */ n_skip + 1,
				               "kmalloc_untrace_n(%p...%p): Data at %p...%p (of node %p...%p) was already untraced",
				               base, endaddr - 1,
				               trace_node_umin(node) + untrace_min * sizeof(void *),
				               (trace_node_umin(node) + (untrace_max + 1) * sizeof(void *)) - 1,
				               trace_node_umin(node), trace_node_umax(node));
				trace_node_free(node);
				return;
			}
		}
		if (endaddr > trace_node_umax(node)) {
			byte_t *uend;
			/* Untrace range overlaps with the end of this node.
			 * -> Can either remove fully, or at least truncate the end. */
			if ((uintptr_t)base <= trace_node_umin(node)) {
				/* Fully remove this node! */
				lock_break();
				base      = trace_node_uend(node);
				num_bytes = endaddr - (uintptr_t)base;
				trace_node_free(node);
				goto again_while_num_bytes; /* Don't use `continue'! That one interferes with `lock_acquire()' */
			}
			/* Truncate the node near its upper end. */
			uend                 = trace_node_uend(node);
			node->tn_link.rb_max = (uintptr_t)base - 1;
			base                 = uend;
			tm_nodes_insert(node);
			lock_break();
			num_bytes = endaddr - (uintptr_t)base;
			goto again_while_num_bytes; /* Don't use `continue'! That one interferes with `lock_acquire()' */
		}
		/* Check if we can truncate the node at its base */
		if ((uintptr_t)base <= trace_node_umin(node)) {
			assert((uintptr_t)base == trace_node_umin(node));
			/* Truncate the node near its lower end. */
			assert(endaddr > node->tn_link.rb_min);
			if (node->tn_kind == TRACE_NODE_KIND_BITSET) {
				size_t bitset_offset, count, dst, src;
				/* Shift down the bits of the is-traced bitset down by `bitset_offset' */
				bitset_offset = (endaddr - node->tn_link.rb_min) / sizeof(void *);
				assert(bitset_offset != 0);
				count = trace_node_bitset_count(node) - bitset_offset;
				assert(count != 0);
				dst   = 0;
				src   = bitset_offset;
				for (;;) {
					if (trace_node_bitset_bitget(node, src)) {
						trace_node_bitset_biton(node, dst);
					} else {
						trace_node_bitset_bitoff(node, dst);
					}
					if (!count)
						break;
					--count;
					++dst;
					++src;
				}
			}
			node->tn_link.rb_min = endaddr;
			tm_nodes_insert(node);
			lock_break();
			break;
		}
		/* Must split the node (the caller wants us to cut a hole into the middle) */
		if (node->tn_kind == TRACE_NODE_KIND_BITSET) {
			/* Special case: This already is  a bitset node,  (and code above  already
			 *               asserted  that our range is still traced), so all we have
			 *               to do is clear some more bits corresponding to our range. */
			size_t i, minbit, maxbit;
			minbit = ((uintptr_t)base - trace_node_umin(node)) / sizeof(void *);
			maxbit = ((endaddr - sizeof(void *)) - trace_node_umin(node)) / sizeof(void *);
			assert(minbit <= maxbit);
			for (i = minbit; i <= maxbit; ++i) {
				assert(trace_node_bitset_bitget(node, i));
				trace_node_bitset_bitoff(node, i);
			}
			tm_nodes_insert(node);
			lock_break();
			break;
		}

#if 0
		/* TODO: Try to allocate a secondary node (but do this without holding the trace-lock) */
#endif

		/* Fallback: We've failed to allocate a secondary node, and so we have to convert the
		 *           node that we've already  got into a `TRACE_NODE_KIND_BITSET'-kind  node,
		 *           who's bitset is all ones,  except for the bits  from the range that  our
		 *           caller wants us to mark as untraced.
		 * The only down-side is that in doing this, we loose the node's traceback */
		node->tn_kind = TRACE_NODE_KIND_BITSET;
		memset(trace_node_bitset_words(node), 0xff,
		       CEILDIV(trace_node_bitset_count(node), NBBY));
		{
			size_t i, minbit, maxbit;
			minbit = ((uintptr_t)base - trace_node_umin(node)) / sizeof(void *);
			maxbit = ((endaddr - sizeof(void *)) - trace_node_umin(node)) / sizeof(void *);
			assert(minbit <= maxbit);
			for (i = minbit; i <= maxbit; ++i)
				trace_node_bitset_bitoff(node, i);
		}
		tm_nodes_insert(node);
		lock_release();
		break;
	}
}

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
PUBLIC NOBLOCK ATTR_NOINLINE void
NOTHROW(KCALL kmalloc_untrace_n)(void *base, size_t num_bytes) {
	kmalloc_untrace_n_impl(base, num_bytes, 1);
}

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
PUBLIC NOBLOCK ATTR_NOINLINE size_t
NOTHROW(KCALL kmalloc_traceback)(void *ptr, /*out*/ void **tb, size_t buflen,
                                 pid_t *p_alloc_roottid) {
	size_t result;
	struct trace_node *node;
	lock_acquire();
	node = tm_nodes_locate(ptr);
	if unlikely(!node) {
		lock_break();
		return 0;
	}

	/* Write-back the TID of the thread that originally allocated the node. */
	if (p_alloc_roottid)
		*p_alloc_roottid = node->tn_tid;

	/* Check if this node has a traceback */
	if (!TRACE_NODE_KIND_HAS_TRACEBACK(node->tn_kind)) {
		result = 0;
	} else {
		size_t max = trace_node_traceback_count(node);
		for (result = 0; result < max; ++result) {
			if (trace_node_traceback_vector(node)[result] == NULL)
				break;
		}

		/* Copy all traceback entries for which the caller has space. */
		memcpy(tb, trace_node_traceback_vector(node),
		       MIN(result, buflen), sizeof(void *));
	}
	lock_release();
	return result;
}

/* Print a traceback for `ptr' to the given `printer'.
 * WARNING: Don't kfree(ptr) while this function is running! */
PUBLIC NOBLOCK ssize_t KCALL
kmalloc_printtrace(void *ptr, pformatprinter printer, void *arg) {
	ssize_t result = 0;
	struct trace_node *node;
	lock_acquire();
	node = tm_nodes_locate(ptr);
	lock_release();
	if (node && TRACE_NODE_KIND_HAS_TRACEBACK(node->tn_kind))
		result = trace_node_print_traceback(node, printer, arg);
	return result;
}



#if CONFIG_KERNEL_MALL_HEAD_SIZE != 0 || CONFIG_KERNEL_MALL_TAIL_SIZE != 0
#define HAVE_kmalloc_validate_node
PRIVATE NOBLOCK ATTR_NOINLINE NONNULL((2)) bool
NOTHROW(KCALL kmalloc_validate_node)(unsigned int n_skip,
                                     struct trace_node const *__restrict node) {
	unsigned int i;
	u32 const *base;
	/* Check if the node has padding which we can validate. */
	if (!TRACE_NODE_KIND_HAS_PADDING(node->tn_kind))
		goto done;
	base = (u32 const *)trace_node_uaddr(node);
#if CONFIG_KERNEL_MALL_HEAD_SIZE != 0
	for (i = sizeof(size_t) / 4; i < CONFIG_KERNEL_MALL_HEAD_SIZE / 4; ++i) {
		if (base[i] != CONFIG_KERNEL_MALL_HEAD_PATTERN) {
			u32 word;
			word = CONFIG_KERNEL_MALL_HEAD_PATTERN;
			base += i;
			while (*(byte_t const *)base == ((byte_t const *)&word)[(uintptr_t)base & 3])
				base = (u32 const *)((byte_t const *)base + 1);
			kernel_panic_n(n_skip + 1,
			               "Corrupted MALL header at %p (offset %" PRIdSIZ " from %p...%p)\n"
			               "%$[hex]\n"
			               "%[gen:c]",
			               base, (uintptr_t)base - (trace_node_umin(node) + CONFIG_KERNEL_MALL_HEAD_SIZE),
			               trace_node_uaddr(node) + CONFIG_KERNEL_MALL_HEAD_SIZE,
			               trace_node_uend(node) - CONFIG_KERNEL_MALL_TAIL_SIZE,
			               /* %$[hex]  */ trace_node_usize(node), trace_node_uaddr(node),
			               /* %[gen:c] */ &trace_node_print_traceback, node);
			return false;
		}
	}
#endif /* CONFIG_KERNEL_MALL_HEAD_SIZE != 0 */
#if CONFIG_KERNEL_MALL_TAIL_SIZE != 0
	base = (u32 const *)(trace_node_umax(node) + 1 - CONFIG_KERNEL_MALL_TAIL_SIZE);
	for (i = 0; i < CONFIG_KERNEL_MALL_TAIL_SIZE / 4; ++i) {
		if (base[i] != CONFIG_KERNEL_MALL_TAIL_PATTERN) {
			u32 word;
			word = CONFIG_KERNEL_MALL_TAIL_PATTERN;
			base += i;
			while (*(byte_t const *)base == ((byte_t const *)&word)[(uintptr_t)base & 3])
				base = (u32 const *)((byte_t const *)base + 1);
			kernel_panic_n(n_skip + 1,
			               "Corrupted MALL tail at %p (offset %" PRIdSIZ " from %p...%p; "
			               "offset %" PRIuSIZ " from end of usable memory)\n"
			               "%$[hex]\n"
			               "%[gen:c]",
			               base, (uintptr_t)base - (trace_node_umin(node) + CONFIG_KERNEL_MALL_HEAD_SIZE),
			               trace_node_uaddr(node) + CONFIG_KERNEL_MALL_HEAD_SIZE,
			               trace_node_uend(node) - CONFIG_KERNEL_MALL_TAIL_SIZE,
			               (uintptr_t)base - (trace_node_umax(node) + 1 - CONFIG_KERNEL_MALL_TAIL_SIZE),
			               /* %$[hex]  */ trace_node_usize(node), trace_node_uaddr(node),
			               /* %[gen:c] */ &trace_node_print_traceback, node);
			return false;
		}
	}
#endif /* CONFIG_KERNEL_MALL_TAIL_SIZE != 0 */
done:
	return true;
}


PRIVATE NOBLOCK ATTR_NOINLINE NONNULL((2)) void
NOTHROW(KCALL kmalloc_validate_walktree)(unsigned int n_skip,
                                         struct trace_node const *__restrict node) {
again:
	kmalloc_validate_node(n_skip + 1, node);
	if (node->tn_link.rb_lhs) {
		if (node->tn_link.rb_rhs)
			kmalloc_validate_walktree(n_skip + 1, node->tn_link.rb_rhs);
		node = node->tn_link.rb_lhs;
		goto again;
	}
	if (node->tn_link.rb_rhs) {
		node = node->tn_link.rb_rhs;
		goto again;
	}
}
#endif /* CONFIG_KERNEL_MALL_HEAD_SIZE != 0 || CONFIG_KERNEL_MALL_TAIL_SIZE != 0 */

/* Validate that headers/footers of data blocks returned by kmalloc() haven't
 * been  modified (which can accidentally happen as the result of programming
 * errors, such as array over-/under-runs)
 * If inconsistencies are found, the kernel will panic.
 * s.a.  `heap_validate()'  and   `heap_validate_all()' */
PUBLIC NOBLOCK ATTR_NOINLINE void
NOTHROW(KCALL kmalloc_validate)(void) {
#if CONFIG_KERNEL_MALL_HEAD_SIZE != 0 || CONFIG_KERNEL_MALL_TAIL_SIZE != 0
	lock_acquire();
	if (tm_nodes != NULL)
		kmalloc_validate_walktree(1, tm_nodes);
	lock_release();
#else /* CONFIG_KERNEL_MALL_HEAD_SIZE != 0 || CONFIG_KERNEL_MALL_TAIL_SIZE != 0 */
	/* nothing... */
#endif /* CONFIG_KERNEL_MALL_HEAD_SIZE == 0 && CONFIG_KERNEL_MALL_TAIL_SIZE == 0 */
}


/************************************************************************/
/* GC MEMORY LEAK DETECTOR                                              */
/************************************************************************/

/* The   current  version   number  used   when  searching   for  memory  leaks.
 * This value is used to identity pointers that haven't been reached/search yet. */
PRIVATE ATTR_MALL_UNTRACKED u8 gc_version = 0;


/* Mark a given `ptr' as reachable, returning the # of nodes reached from it. */
PRIVATE NOBLOCK ATTR_COLDTEXT size_t
NOTHROW(KCALL gc_reachable_pointer)(void *ptr);

/* Scan the given data-block for reachable pointers. */
PRIVATE NOBLOCK ATTR_COLDTEXT size_t
NOTHROW(KCALL gc_reachable_data)(void const *base, size_t num_bytes);


#ifdef CONFIG_HAVE_KERNEL_SLAB_ALLOCATORS
#define DECLARE_SLAB_DESCRIPTOR(size, _) \
	INTDEF struct slab_descriptor slab_desc##size;
SLAB_FOREACH_SIZE(DECLARE_SLAB_DESCRIPTOR, _)
#undef DECLARE_SLAB_DESCRIPTOR

/* Vector of pointers to all existing slab descriptors. */
PRIVATE ATTR_COLDRODATA struct slab_descriptor *const gc_slab_descs[] = {
#define DECLARE_SLAB_DESCRIPTOR(size, _) \
	&slab_desc##size,
	SLAB_FOREACH_SIZE(DECLARE_SLAB_DESCRIPTOR, _)
#undef DECLARE_SLAB_DESCRIPTOR
};

PRIVATE NOBLOCK ATTR_COLDTEXT NONNULL((1)) void
NOTHROW(KCALL gc_slab_reset_reach_slab)(struct slab *__restrict self) {
#if (SLAB_SEGMENT_STATUS_REACH & SLAB_SEGMENT_STATUS_ALLOC) != 0
	size_t i, count;
	uintptr_t *bits;
	bits = (uintptr_t *)(self + 1);
	bits  = (uintptr_t *)(self + 1);
	count = SLAB_LENGTHOF_BITSET(self->s_size);
	for (i = 0; i < count; ++i)
		bits[i] &= _SLAB_SEGMENT_STATUS_WORDMASK(SLAB_SEGMENT_STATUS_ALLOC);
#else /* (SLAB_SEGMENT_STATUS_REACH & SLAB_SEGMENT_STATUS_ALLOC) != 0 */
#error Not implemented
#endif /* (SLAB_SEGMENT_STATUS_REACH & SLAB_SEGMENT_STATUS_ALLOC) == 0 */
}

PRIVATE NOBLOCK ATTR_COLDTEXT NONNULL((1)) void
NOTHROW(KCALL gc_slab_reset_reach_slab_chain)(struct slab_list const *__restrict self) {
	struct slab *iter;
	LIST_FOREACH (iter, self, s_link) {
		gc_slab_reset_reach_slab(iter);
	}
}

PRIVATE NOBLOCK ATTR_COLDTEXT NONNULL((1)) void
NOTHROW(KCALL gc_slab_reset_reach_desc)(struct slab_descriptor const *__restrict self) {
	gc_slab_reset_reach_slab_chain(&self->sd_free);
	gc_slab_reset_reach_slab_chain(&self->sd_used);
}

PRIVATE NOBLOCK ATTR_COLDTEXT void
NOTHROW(KCALL gc_slab_reset_reach)(void) {
	unsigned int i;
	for (i = 0; i < lengthof(gc_slab_descs); ++i) {
		gc_slab_reset_reach_desc(gc_slab_descs[i]);
	}
}

PRIVATE NOBLOCK ATTR_COLDTEXT size_t
NOTHROW(KCALL gc_reachable_slab_pointer)(void *ptr) {
	struct slab *s;
	byte_t *slab_segments_start;
	uintptr_t index, word, value;
	uintptr_t *bits;
	size_t result;
	shift_t shift;
	if (!pagedir_iswritable(ptr)) {
		/* This can happen for stale pointers into slab pages that
		 * have later been deallocated, as may be done when  doing
		 * a `system_cc()'. (s.a. `system_cc_perslabpool()') */
		return 0;
	}

	s                   = SLAB_GET(ptr);
	slab_segments_start = (byte_t *)s + SLAB_SEGMENT_OFFSET(s->s_size);
	index               = (uintptr_t)((byte_t *)ptr - slab_segments_start) / s->s_size;
	if unlikely(index >= (size_t)SLAB_SEGMENT_COUNT(s->s_size))
		return 0; /* Not a valid slab user-segment pointer. */
	bits = (uintptr_t *)(s + 1);

	/* Check if `ptr' is actually allocated inside of `s', and wasn't already reached. */
	word  = _SLAB_SEGMENT_STATUS_WORD(index);
	shift = _SLAB_SEGMENT_STATUS_SHFT(index);
	value = bits[word];
	if (((value >> shift) & SLAB_SEGMENT_STATUS_MASK) != SLAB_SEGMENT_STATUS_ALLOC)
		return 0;

	/* Alright! So we've got a reachable slab-pointer!
	 * -> Mark it as such! */
#if (SLAB_SEGMENT_STATUS_REACH & SLAB_SEGMENT_STATUS_ALLOC) != 0
	bits[word] = value | ((uintptr_t)SLAB_SEGMENT_STATUS_REACH << shift);
#else /* (SLAB_SEGMENT_STATUS_REACH & SLAB_SEGMENT_STATUS_ALLOC) != 0 */
	bits[word] = (value & ~((uintptr_t)SLAB_SEGMENT_STATUS_ALLOC << shift)) |
	             /*     */ ((uintptr_t)SLAB_SEGMENT_STATUS_REACH << shift);
#endif /* (SLAB_SEGMENT_STATUS_REACH & SLAB_SEGMENT_STATUS_ALLOC) == 0 */
	/* Recursively scan the memory pointed-to by the segment. */
	result = gc_reachable_data(slab_segments_start +
	                           index * s->s_size,
	                           s->s_size);
	return result + 1;
}
#endif /* CONFIG_HAVE_KERNEL_SLAB_ALLOCATORS */



#ifndef SIZEOF_POINTER
#define SIZEOF_POINTER __SIZEOF_POINTER__
#endif /* !SIZEOF_POINTER */

#define INUSE_BITSET_INDEXOF(index)         ((index) / (SIZEOF_POINTER * NBBY))
#define INUSE_BITSET_SHIFTOF(index)         ((index) % (SIZEOF_POINTER * NBBY))
#define INUSE_BITSET_GET(bitset, index)     ((bitset[INUSE_BITSET_INDEXOF(index)] >> INUSE_BITSET_SHIFTOF(index)) & 1)
#define INUSE_BITSET_TURNOFF(bitset, index) (bitset[INUSE_BITSET_INDEXOF(index)] &= ~((uintptr_t)1 << INUSE_BITSET_SHIFTOF(index)))
#define INUSE_BITSET_TURNON(bitset, index)  (bitset[INUSE_BITSET_INDEXOF(index)] |= ((uintptr_t)1 << INUSE_BITSET_SHIFTOF(index)))


/* To prevent gc traversal of certain object pointers, we take advantage of the
 * fact  that all inter-object  pointers (iow: pointers to  object that in turn
 * also point to more object) are always pointer-aligned (since a struct T that
 * contains pointers must  have alignof(T)  >= alignof(void *)).  This is  also
 * assumed by `gc_reachable_pointer()', which simply ignores pointers that  are
 * not properly aligned.
 *
 * We  (ab-)use this fact  to prevent certain  inter-object pointers from being
 * used for traversal, as we don't want links between global object lists to be
 * considered as a viable method of reaching other global objects.
 *
 * As such, we assume that bit#0 is normally clear for inter-object pointers,
 * and simply set it to 1 to prevent the link from being traversed. Once leak
 * detection has finished, we change it back to clear.
 *
 * s.a. the discussion on why `Phase #3: Scan global objects' is disabled above */
#define gc_isskewed(p) ((uintptr_t)(p) & 1)
#define gc_skewed(p)   ((typeof(p))((uintptr_t)(p) | 1))
#define gc_unskewed(p) ((typeof(p))((uintptr_t)(p) & ~1))
#define gc_skew(p_p)   (void)(*(p_p) = gc_skewed(*(p_p)))
#define gc_unskew(p_p) (void)(*(p_p) = gc_unskewed(*(p_p)))







/* Reset coreheap reachability flags. */
PRIVATE NOBLOCK ATTR_COLDTEXT void
NOTHROW(KCALL gc_coreheap_reset_reach)(void) {
	unsigned int i;
	for (i = 0; i < lengthof(mcoreheap_lists); ++i) {
		struct mcorepage *iter;
		SLIST_FOREACH (iter, &mcoreheap_lists[i], mcp_link)
			bzero(iter->_mcp_reach, sizeof(iter->_mcp_reach));
	}
}



PRIVATE NOBLOCK ATTR_COLDTEXT NONNULL((1)) void
NOTHROW(KCALL gc_mnode_reset_reach)(struct mnode *__restrict self) {
again:
	self->mn_flags &= ~MNODE_F__REACH;
	if (self->mn_mement.rb_lhs) {
		if (self->mn_mement.rb_rhs)
			gc_mnode_reset_reach(self->mn_mement.rb_rhs);
		self = self->mn_mement.rb_lhs;
		goto again;
	}
	if (self->mn_mement.rb_rhs) {
		self = self->mn_mement.rb_rhs;
		goto again;
	}
}

/* Reset reachable bits for kernel mman nodes. */
PRIVATE NOBLOCK ATTR_COLDTEXT void
NOTHROW(KCALL gc_kernel_mman_nodes_reset_reach)(void) {
	if (mman_kernel.mm_mappings) /* Should never be NULL, but better be save... */
		gc_mnode_reset_reach(mman_kernel.mm_mappings);
}



PRIVATE NOBLOCK ATTR_COLDTEXT size_t
NOTHROW(KCALL gc_reachable_pointer)(void *ptr) {
	/* Do a number  of checks to  filter out often-found  pointers
	 * for which we know that they don't point to heap structures.
	 *
	 * By doing this here, we can cut down on a lot of boiler-plate
	 * code  that's  needed   to  verify   heap  pointers   proper. */
	struct trace_node *node;

	/* Check if NULL is part of kernel-space. */
#if (defined(KERNELSPACE_LOWMEM) || \
     (defined(KERNELSPACE_HIGHMEM) && 0 >= KERNELSPACE_BASE))
	if (ptr == NULL)
		return 0; /* Optimization: NULL pointer */
#endif /* ADDR_ISKERN(NULL) */

	/* If the pointer doesn't belong to kernel-space, we ignore it. */
	if (!ADDR_ISKERN(ptr))
		return 0;

	/* Unaligned pointer -> not a heap pointer */
	if (((uintptr_t)ptr & (sizeof(void *) - 1)) != 0)
		return 0;

#if __SIZEOF_POINTER__ == 4
#ifdef CONFIG_HAVE_KERNEL_DEBUG_HEAP
	if ((uintptr_t)ptr == DEBUGHEAP_NO_MANS_LAND)
		return 0; /* Optimization: No mans land */
	if ((uintptr_t)ptr == DEBUGHEAP_FRESH_MEMORY)
		return 0; /* Optimization: Fresh memory. */
#endif /* CONFIG_HAVE_KERNEL_DEBUG_HEAP */
	if ((uintptr_t)ptr == UINT32_C(0xcccccccc))
		return 0; /* Optimization: debug filler. */
#elif __SIZEOF_POINTER__ == 8
#ifdef CONFIG_HAVE_KERNEL_DEBUG_HEAP
	if ((uintptr_t)ptr == ((uint64_t)DEBUGHEAP_NO_MANS_LAND |
	                       (uint64_t)DEBUGHEAP_NO_MANS_LAND << 32))
		return 0; /* Optimization: No mans land */
	if ((uintptr_t)ptr == ((uint64_t)DEBUGHEAP_FRESH_MEMORY |
	                       (uint64_t)DEBUGHEAP_FRESH_MEMORY << 32))
		return 0; /* Optimization: Fresh memory. */
#endif /* CONFIG_HAVE_KERNEL_DEBUG_HEAP */
	if ((uintptr_t)ptr == UINT32_C(0xcccccccccccccccc))
		return 0; /* Optimization: debug filler. */
#endif /* __SIZEOF_POINTER__ == ... */

	/* Special handling for slab pointers. */
#ifdef CONFIG_HAVE_KERNEL_SLAB_ALLOCATORS
	if (KERNEL_SLAB_CHECKPTR(ptr))
		return gc_reachable_slab_pointer(ptr);
#endif /* CONFIG_HAVE_KERNEL_SLAB_ALLOCATORS */

	node = tm_nodes_locate(ptr);
	if (!node) {
		/* Special handling for mcoreheap */
		struct mnode *mn;
		struct mcorepage *cp, *iter;
		uintptr_t index, i;
		cp    = (struct mcorepage *)FLOOR_ALIGN((uintptr_t)ptr, PAGESIZE);
		index = (uintptr_t)((byte_t *)ptr - (byte_t *)cp->mcp_part);
		index /= sizeof(union mcorepart);
		if (index >= lengthof(cp->mcp_part))
			goto check_reachable_mnode; /* Invalid index. (including the underflow case) */
		if (!pagedir_iswritable((void *)cp))
			return 0; /* Page isn't writable. -> This can't be one of them! */
		if (!INUSE_BITSET_GET(cp->mcp_used, index))
			goto check_reachable_mnode; /* Not allocated. */
		if (INUSE_BITSET_GET(cp->_mcp_reach, index))
			goto check_reachable_mnode; /* Already reached. */

		/* Check that `cp' really is one of the coreheap pages. */
		for (i = 0; i < lengthof(mcoreheap_lists); ++i) {
			SLIST_FOREACH (iter, &mcoreheap_lists[i], mcp_link) {
				if (iter == cp) {
					/* Yes: this really is a reachable coreheap object! */
					size_t result;

					/* Prevent recursion by remembering reachability */
					INUSE_BITSET_TURNON(cp->_mcp_reach, index);

					/* Recursively visit pointed-to data. */
					result = gc_reachable_data(&cp->mcp_part[index], sizeof(cp->mcp_part[index]));
					return result + 1;
				}
			}
		}
check_reachable_mnode:
		/* Mark reachable mnode objects from the kernel mman */
		mn = mnode_tree_locate(mman_kernel.mm_mappings, gc_skewed(ptr));
		if (mn != NULL)
			mn->mn_flags |= MNODE_F__REACH;
		return 0;
	}

	/* Normal traced memory. */
	if (node->tn_reach == gc_version)
		return 0; /* Already reached. */
	if (node->tn_kind == TRACE_NODE_KIND_BITSET) {
		/* When node is `TRACE_NODE_KIND_BITSET', then only mark it
		 * as reachable when `ptr' points into its traced  portion. */
		size_t index;

		/* HINT: We already know that `ptr' is POINTER-aligned (see the other check above) */
		index = ((uintptr_t)ptr - trace_node_umin(node)) / sizeof(void *);
		if (!trace_node_bitset_bitget(node, index))
			return 0; /* This specific pointer isn't actually traced. */
	}
	node->tn_reach = gc_version;
	return 1;
}


PRIVATE NOBLOCK ATTR_COLDTEXT size_t
NOTHROW(KCALL gc_reachable_data)(void const *base, size_t num_bytes) {
	size_t result = 0;
	if unlikely((uintptr_t)base & (sizeof(void *) - 1)) {
		/* Align the base pointer. */
		size_t offset;
		offset = sizeof(void *) - ((uintptr_t)base & (sizeof(void *) - 1));
		if unlikely(offset >= num_bytes)
			goto done;
		num_bytes -= offset;
		base = (byte_t *)base + offset;
	}
	while (num_bytes >= sizeof(void *)) {
		void *ptr;
		size_t page_bytes = PAGESIZE - ((uintptr_t)base & PAGEMASK);

		/* Only scan writable pages. */
		if (!pagedir_iswritable((void *)base)) {
			/* FIXME: What if `base' isn't writable because it was written to SWAP?
			 *        In this case  we'd have  to abort GC  detection, release  our
			 *        scheduler super-lock, force  load `base' into  the core,  and
			 *        finally: try again (though we should probably gather all pages
			 *        to   which  this   applies,  and   load  them   all  at  once)
			 * NOTE:  We can only load them when not holding a super-lock, since
			 *        the  act of loading memory from SWAP might require the use
			 *        of async workers, which don't work while holding a  super-
			 *        lock. */
			if (page_bytes >= num_bytes)
				break;
			base = (byte_t *)base + page_bytes;
			num_bytes -= page_bytes;
			continue;
		}
		if (page_bytes > num_bytes)
			page_bytes = num_bytes;
		num_bytes -= page_bytes;
		while (page_bytes >= sizeof(void *)) {
			COMPILER_READ_BARRIER();
			ptr = *(void **)base;
			COMPILER_READ_BARRIER();

			/* Check if this is a heap pointer, and if so: mark it as reachable. */
			result += gc_reachable_pointer(ptr);
			base = (byte_t *)base + sizeof(void *);
			page_bytes -= sizeof(void *);
		}
	}
done:
	return result;
}


PRIVATE NOBLOCK ATTR_COLDTEXT size_t
NOTHROW(KCALL gc_reachable_thread_scpustate)(struct task *__restrict thread,
                                             struct scpustate *__restrict context) {
	size_t result = 0;

	/* Search the registers of this thread. */
	if (scpustate_isuser(context)) {
		/* Thread is currently in user-space (meaning its kernel stack is unused) */
	} else {
		void *sp, *stack_min, *stack_end;

		/* Search general-purpose registers. */
#define CONSUME_GP_REGISTER(val) result += gc_reachable_pointer((void *)(val))
		scpustate_foreach_gpregs(context, CONSUME_GP_REGISTER);
#undef CONSUME_GP_REGISTER
		stack_min = mnode_getminaddr(&FORTASK(thread, this_kernel_stacknode));
		stack_end = mnode_getendaddr(&FORTASK(thread, this_kernel_stacknode));
#ifdef scpustate_getkernelsp
		sp = scpustate_getkernelsp(context);
#else /* scpustate_getkernelsp */
		sp = scpustate_getsp(context);
#endif /* !scpustate_getkernelsp */
		if (sp > stack_min && sp <= stack_end) {
			/* Search the used portion of the kernel stack. */
			result += gc_reachable_data((byte_t *)sp,
			                            (size_t)((byte_t *)stack_end -
			                                     (byte_t *)sp));
		} else {
			/* Stack pointer  is  out-of-bounds  (no  idea  what  this  is
			 * about, but let's just assume the entire stack is allocated) */
			result += gc_reachable_data((byte_t *)stack_min,
			                            (size_t)((byte_t *)stack_end -
			                                     (byte_t *)stack_min));
		}
	}
	return result;
}


DATDEF ATTR_PERTASK struct mnode this_kernel_stacknode_ ASMNAME("this_kernel_stacknode");

PRIVATE NOBLOCK ATTR_COLDTEXT NONNULL((1)) void
NOTHROW(KCALL gc_reachable_thread)(struct task *__restrict thread) {
	/* Mark mem-nodes inlined to the task as reachable. */
	FORTASK(thread, this_kernel_stacknode_).mn_flags |= MNODE_F__REACH;
}

PRIVATE NOBLOCK ATTR_COLDTEXT size_t
NOTHROW(KCALL gc_reachable_this_thread)(void) {
	size_t result = 0;
	unsigned int i;
	void *sp, *stack_min, *stack_end;
	struct lcpustate context;
	struct mnode const *my_stack;
	gc_reachable_thread(THIS_TASK);

	/* Search the registers of this thread. */
	lcpustate_current(&context);

	/* Search general-purpose registers. */
	for (i = 0; i < (sizeof(struct lcpustate) / sizeof(void *)); ++i)
		result += gc_reachable_pointer(((void **)&context)[i]);
	my_stack = THIS_KERNEL_STACK;
	sp       = lcpustate_getsp(&context);
	get_stack_for(&stack_min, &stack_end, sp);
	if (sp > stack_min && sp <= stack_end) {
		/* Search the used portion of the kernel stack. */
		result += gc_reachable_data((byte_t *)sp,
		                            (size_t)((byte_t *)stack_end -
		                                     (byte_t *)sp));

		/* If we're running from a custom stack, also search the original kernel stack! */
		if (stack_end != (byte_t *)mnode_getendaddr(my_stack))
			goto do_search_kernel_stack;
	} else {
		/* Stack pointer is out-of-bounds (no idea what this
		 * is about, but let's just assume the entire  stack
		 * is allocated) */
do_search_kernel_stack:
		stack_min = mnode_getminaddr(my_stack);
		stack_end = mnode_getendaddr(my_stack);
		result += gc_reachable_data((byte_t *)stack_min,
		                            (size_t)((byte_t *)stack_end -
		                                     (byte_t *)stack_min));
	}
	return result;
}


PRIVATE NOBLOCK ATTR_COLDTEXT size_t
NOTHROW(KCALL gc_reachable_recursion)(struct trace_node *__restrict node) {
	size_t result = 0;
again:
	if (node->tn_reach == gc_version &&
	    node->tn_visit != gc_version &&
	    !(node->tn_flags & TRACE_NODE_FLAG_NOWALK)) {
		byte_t *minaddr, *maxaddr;
		/* Scan the user-data block of this node. */
		minaddr = (byte_t *)trace_node_umin(node);
		maxaddr = (byte_t *)trace_node_umax(node);
		switch (node->tn_kind) {

		case TRACE_NODE_KIND_BITSET: {
			/* Only scan data that is still marked as being traced. */
			size_t i, start, count;
			count = trace_node_bitset_count(node);
			for (i = 0; i < count; ++i) {
				if (!trace_node_bitset_bitget(node, i))
					continue;

				/* Found a traced range (find its end) */
				start = i;
				for (;;) {
					++i;
					if (i >= count)
						break;
					if (!trace_node_bitset_bitget(node, i))
						break;
				}

				/* Scan the contents of this particular (still-traced) range. */
				result += gc_reachable_data(minaddr + start * sizeof(void *),
				                            (i - start) * sizeof(void *));
			}
		}	break;

		case TRACE_NODE_KIND_MALL:
			/* Don't scan the header- or tail-area! */
			minaddr += CONFIG_KERNEL_MALL_HEAD_SIZE;
			maxaddr -= CONFIG_KERNEL_MALL_TAIL_SIZE;
			ATTR_FALLTHROUGH
		default:
			assert(minaddr <= maxaddr);
			/* Do the recursive scan. */
			result += gc_reachable_data(minaddr, (size_t)(maxaddr - minaddr) + 1);
			break;
		}
		node->tn_visit = gc_version;
	}
	if (node->tn_link.rb_lhs) {
		if (node->tn_link.rb_rhs)
			result += gc_reachable_recursion(node->tn_link.rb_rhs);
		node = node->tn_link.rb_lhs;
		goto again;
	}
	if (node->tn_link.rb_rhs) {
		node = node->tn_link.rb_rhs;
		goto again;
	}
	return result;
}


INTDEF byte_t __debug_malloc_tracked_start[];
INTDEF byte_t __debug_malloc_tracked_end[];
INTDEF byte_t __debug_malloc_tracked_size[];

#ifndef __driver_loadlist_arref_defined
#define __driver_loadlist_arref_defined
ARREF(driver_loadlist_arref, driver_loadlist);
#endif /* !__driver_loadlist_arref_defined */

PRIVATE NOBLOCK ATTR_COLDTEXT NONNULL((2)) ssize_t
NOTHROW(TASK_ENUM_CC gc_reachable_thread_cb)(void *UNUSED(arg),
                                             struct task *__restrict thread) {
	size_t result = 0;
	if (thread != THIS_TASK) {
		gc_reachable_thread(thread);
		result += gc_reachable_thread_scpustate(thread, FORTASK(thread, this_sstate));
	}
	return (ssize_t)result;
}

#if 0
#define PRINT_LEAKS_SEARCH_PHASE(...) printk(KERN_INFO __VA_ARGS__)
#else
#define PRINT_LEAKS_SEARCH_PHASE(...) (void)0
#endif



#if 0
PRIVATE NOBLOCK ATTR_COLDTEXT size_t
NOTHROW(KCALL gc_reachable_allmparts)(struct mpart *first) {
	size_t result = 0;
	for (gc_unskew(&first); first != NULL;
	     first = gc_unskewed(LIST_NEXT(first, mp_allparts))) {
		if (!wasdestroyed(first) && (first->mp_flags & MPART_F_GLOBAL_REF))
			result += gc_reachable_pointer(first);
	}
	return result;
}

PRIVATE NOBLOCK ATTR_COLDTEXT size_t
NOTHROW(KCALL gc_reachable_fallnodes)(struct fnode *first) {
	size_t result = 0;
	for (gc_unskew(&first); first != NULL;
	     first = gc_unskewed(LIST_NEXT(first, fn_allnodes))) {
		if (!wasdestroyed(first) && (first->mf_flags & MFILE_FN_GLOBAL_REF))
			result += gc_reachable_pointer(first);
	}
	return result;
}

PRIVATE NOBLOCK ATTR_COLDTEXT size_t
NOTHROW(KCALL gc_reachable_fallsuper)(struct fsuper *first) {
	size_t result = 0;
	for (gc_unskew(&first); first != NULL;
	     first = gc_unskewed(LIST_NEXT(first, fs_root.fn_allsuper))) {
		if (!wasdestroyed(first)/* && (first->fs_root.mf_flags & MFILE_FN_GLOBAL_REF)*/)
			result += gc_reachable_pointer(first);
	}
	return result;
}
#endif


PRIVATE NOBLOCK ATTR_COLDTEXT NONNULL((1, 2)) void
NOTHROW(KCALL gc_reachable_tm_node_memory)(struct trace_node *__restrict self,
                                           struct mnode *__restrict lastnode) {
again:
	if ((byte_t *)self < (byte_t *)mnode_getminaddr(lastnode) ||
	    (byte_t *)self > (byte_t *)mnode_getmaxaddr(lastnode)) {
		lastnode = mman_mappings_locate(&mman_kernel, (void *)gc_skewed(self));
		assertf(lastnode, "Bad node pointer: %p", self);
		lastnode->mn_flags |= MNODE_F__REACH;
	}
	if (self->tn_link.rb_lhs) {
		if (self->tn_link.rb_rhs)
			gc_reachable_tm_node_memory(self->tn_link.rb_rhs, lastnode);
		self = self->tn_link.rb_lhs;
		goto again;
	}
	if (self->tn_link.rb_rhs) {
		self = self->tn_link.rb_rhs;
		goto again;
	}
}

/* Mark all mem-nodes used for backing `tm_nodes' as reachable. */
PRIVATE NOBLOCK ATTR_COLDTEXT void
NOTHROW(KCALL gc_reachable_tm_memory)(void) {
	if (tm_nodes) {
		struct mnode *lastnode;
		lastnode = mman_mappings_locate(&mman_kernel, (void *)gc_skewed(tm_nodes));
		assertf(lastnode, "Bad node pointer: %p", tm_nodes);
		lastnode->mn_flags |= MNODE_F__REACH;
		gc_reachable_tm_node_memory(tm_nodes, lastnode);
	}
}


/* Scan the kernel for all reachable, traced pointers. */
PRIVATE NOBLOCK ATTR_COLDTEXT void
NOTHROW(KCALL gc_find_reachable_impl)(void) {
	/* Search for memory leaks.
	 * The idea here is not to be able to find all memory blocks that were
	 * leaked,  but rather  to find  anything that  ~might~ be referenced.
	 * To do this, we search all places we can think of:
	 *    - Kernel .data & .bss
	 *    - Driver .data & .bss
	 *    - Stacks and general purpose registers of all other threads
	 * For this purpose, any properly aligned data word is considered
	 * a possible pointer and if directed at a known heap-block, that
	 * block is saved as reachable.
	 * Following this  first pass,  we recursively  analyze the  user-data
	 * blocks of all heap pointers that were reached thus far, until we're
	 * no longer encountering any new ones.
	 * Anything that still hasn't been reached is then considered a leak. */
	PRINT_LEAKS_SEARCH_PHASE("Phase #1: Scan .data + .bss\n");
	gc_reachable_data((byte_t *)__debug_malloc_tracked_start,
	                  (size_t)__debug_malloc_tracked_size);

	/* Mark all mem-nodes used for backing `tm_nodes' as reachable. */
	gc_reachable_tm_memory();

	/* Search all threads on all CPUs. */
	PRINT_LEAKS_SEARCH_PHASE("Phase #2: Scan running threads\n");
	system_enum_threads_noipi_nb(&gc_reachable_thread_cb, NULL);

	PRINT_LEAKS_SEARCH_PHASE("Phase #2.1: Scan the calling thread\n");
	gc_reachable_this_thread();

#ifndef CONFIG_NO_SMP
	PRINT_LEAKS_SEARCH_PHASE("Phase #2.2: Scan secondary CPU control structures\n");
	/* The `struct cpu' of secondary CPUs is dynamically allocated, but not normally  traced.
	 * This is especially important because `struct cpu' contains some inlined `struct mnode'
	 * objects, which in turn must be considered reachable, as well as any other objects that
	 * are only reachable by traversing the kernel mman's mnode-tree from that on forth. */
	{
		unsigned int i;
		INTDEF byte_t __kernel_percpu_full_bytes[];
		for (i = 1; i < cpu_count; ++i) {
			struct cpu *c = cpu_vector[i];
			gc_reachable_data(c, (size_t)__kernel_percpu_full_bytes);
		}
	}
#endif /* !CONFIG_NO_SMP */

	/*
	 * NOTE: Technically speaking, we'd need to scan `mpart_all_list' at  this
	 *       point, and do the same for `fallnodes_list' and `fallsuper_list'.
	 * However, that's actually a bad idea:
	 *  - There  is only 1 reason why some  mem-part should really be apart of
	 *    the global list of mem-parts, that reason being: the associated file
	 *    hasn't been unloaded yet for the purpose of staying cached.
	 *  - As an extension, the same also goes for parts that have been marked
	 *    as changed, but have yet to be written to disk.
	 *
	 * We can detect parts marked as changed via MPART_F_CHANGED, but then the
	 * question becomes: how do we detect mem-parts that have a right to exist
	 * due to representing cached files?
	 *
	 * The answer is: We don't!
	 *
	 * Think about why these global lists exist:
	 *  - mpart_all_list: Keep parts alive for cached/changed files
	 *  - fallnodes_list: Keep file nodes alive so they don't have to be reloaded constantly
	 *  - fallsuper_list: `fsuper_opendev()' when already opened.
	 * NOTE: sync(2) is implemented via `fchangedsuper_list', so doesn't use `fallsuper_list'
	 *
	 * To tell me: what reason is there for anything reachable via these lists to
	 *             be considered globally visible  from a logical (not  semantic)
	 *             stance?
	 * Answer: there is no reason; any object found in those lists always has
	 *         to be reachable through some other mechanism so-as to actually
	 *         be reachable.
	 * >> e.g. SOME_THREAD->fs->vfs->pathmount->fsuper->fnode->mpart
	 * Our  normal gc-based detection logic is already able to traverse links
	 * such as that example, and we already scan all threads-local variables,
	 * meaning that something like the above mustn't be considered a leaf for
	 * that reason already.
	 *
	 * Furthermore,  in order to  do proper cleanup of  objects found in those
	 * global  lists, you'll have  to use stuff  like `fsuper_delete()' or the
	 * underlying `mfile_delete()'. And if there  isn't a thread that  somehow
	 * references a filesystem that is non-the-less still allocated, then yes:
	 * it should be considered a leak, even if it could (theoretically)  still
	 * be accessed via global lists.
	 *
	 * So in the end, by never scanning global file lists and relying on all
	 * files being reachable through other  means, we can detect  situations
	 * where  code forgot to  call `mfile_delete()' for  what they are; that
	 * being >>Memory Leaks<<
	 */
#if 0
	PRINT_LEAKS_SEARCH_PHASE("Phase #3: Scan global objects\n");
	gc_reachable_allmparts(LIST_FIRST(&mpart_all_list));
	gc_reachable_fallnodes(LIST_FIRST(&fallnodes_list));
	gc_reachable_fallsuper(LIST_FIRST(&fallsuper_list));
#endif


	PRINT_LEAKS_SEARCH_PHASE("Phase #3: Scan loaded drivers\n");
	{
		struct driver_loadlist *dll;
		size_t i;
		dll = arref_ptr(&drivers);
		for (i = 0; i < dll->dll_count; ++i) {
			uint16_t j;
			struct driver *drv = dll->dll_drivers[i];
			if unlikely(wasdestroyed(drv))
				continue;
			/* Since  we're in single-core  mode, we know  that when `drv' isn't
			 * destroyed at this point, it wont get destroyed before we're done! */
			for (j = 0; j < drv->d_phnum; ++j) {
				uintptr_t progaddr;
				size_t progsize;
				if (drv->d_phdr[j].p_type != PT_LOAD)
					continue;
				if (!(drv->d_phdr[j].p_flags & PF_W))
					continue;
				progaddr = (uintptr_t)(drv->md_loadaddr + drv->d_phdr[j].p_vaddr);
				progsize = drv->d_phdr[j].p_memsz;
				progsize += progaddr & PAGEMASK;
				progaddr &= ~PAGEMASK;
				gc_reachable_data((byte_t *)progaddr,
				                  CEIL_ALIGN(progsize, PAGESIZE));
			}
		}
	}

	PRINT_LEAKS_SEARCH_PHASE("Phase #4: Recursively scan reached pointers\n");
	if (tm_nodes) {
		size_t num_found;
		/* With all data collected, recursively scan the data blocks of all reachable nodes.
		 * The recursion takes place  because we keep scanning  until nothing new shows  up. */
		do {
			num_found = gc_reachable_recursion(tm_nodes);
			PRINT_LEAKS_SEARCH_PHASE("Phase #4: Reached %" PRIuSIZ " pointers\n", num_found);
		} while (num_found);
	}
}



#define trace_heap_alloc_heapptr(num_bytes) \
	heap_alloc_untraced(&trace_heap, num_bytes, TRACE_HEAP_FLAGS);
#define trace_heap_free_heapptr(hptr)        \
	heap_free_untraced(&trace_heap,          \
	                   heapptr_getptr(hptr), \
	                   heapptr_getsiz(hptr), \
	                   TRACE_HEAP_FLAGS);

struct abstract_object {
	LIST_ENTRY(abstract_object) ao_link;
};

PRIVATE NOBLOCK ATTR_COLDTEXT NONNULL((1)) void
NOTHROW(KCALL gc_list_skew)(void **p_list_head, ptrdiff_t offsetof_object_list_entry) {
	void *object;
	while ((object = *p_list_head) != NULL) {
		struct abstract_object *link;
		assert(!gc_isskewed(object));
		link = (struct abstract_object *)((byte_t *)object + offsetof_object_list_entry);
		assert((void **)link->ao_link.le_prev == p_list_head);
		assert(!gc_isskewed(link->ao_link.le_prev));
		gc_skew((void **)&link->ao_link.le_prev);
		gc_skew((void **)p_list_head);
		p_list_head = (void **)&link->ao_link.le_next;
	}
	gc_skew((void **)p_list_head);
}

PRIVATE NOBLOCK ATTR_COLDTEXT NONNULL((1)) void
NOTHROW(KCALL gc_list_unskew)(void **p_list_head, ptrdiff_t offsetof_object_list_entry) {
	void *object;
	for (;;) {
		struct abstract_object *link;
		assert(gc_isskewed(*p_list_head));
		gc_unskew((void **)p_list_head);
		object = *p_list_head;
		if (object == NULL)
			break;
		link = (struct abstract_object *)((byte_t *)object + offsetof_object_list_entry);
		assert(gc_isskewed(link->ao_link.le_prev));
		gc_unskew((void **)&link->ao_link.le_prev);
		assert((void **)link->ao_link.le_prev == p_list_head);
		p_list_head = (void **)&link->ao_link.le_next;
	}
}

PRIVATE NOBLOCK ATTR_COLDTEXT void
NOTHROW(KCALL gc_mnode_skew)(struct mnode *__restrict self) {
	/* We  skew the minaddr  attribute of all  mem-nodes because it might
	 * otherwise point into allocated kernel objects, which should  none-
	 * the-less be considered as memory leaks, simply because the minaddr
	 * pointer isn't meant to be  dereferenced, but only as an  indicator
	 * for where the mapping is located.
	 *
	 * We don't have to worry about `mn_maxaddr' because that one already
	 * is set-up like `(. & PAGEMASK) == PAGEMASK', meaning that it's not
	 * a pointed-aligned data-word! */
	gc_skew((void **)&self->mn_minaddr);

	/* We don't want the mpart->nodes lists to be traversed during leak
	 * detection, so we skew those pointers as well! */
	if (self->mn_part) {
		gc_skew((void **)&self->mn_link.le_prev);
		gc_skew((void **)&self->mn_link.le_next);
	}
}

PRIVATE NOBLOCK ATTR_COLDTEXT void
NOTHROW(KCALL gc_mnode_unskew)(struct mnode *__restrict self) {
	gc_unskew((void **)&self->mn_minaddr);
	if (self->mn_part) {
		gc_unskew((void **)&self->mn_link.le_prev);
		gc_unskew((void **)&self->mn_link.le_next);
	}
}


PRIVATE NOBLOCK ATTR_COLDTEXT void
NOTHROW(KCALL gc_mnode_tree_skew)(struct mnode *__restrict self) {
	struct mnode *lo, *hi;
again:
	lo = self->mn_mement.rb_lhs;
	hi = self->mn_mement.rb_rhs;
	gc_mnode_skew(self);
	if (lo) {
		if (hi)
			gc_mnode_tree_skew(hi);
		self = lo;
		goto again;
	}
	if (hi) {
		self = hi;
		goto again;
	}
}

PRIVATE NOBLOCK ATTR_COLDTEXT void
NOTHROW(KCALL gc_mnode_tree_unskew)(struct mnode *__restrict self) {
	struct mnode *lo, *hi;
again:
	lo = self->mn_mement.rb_lhs;
	hi = self->mn_mement.rb_rhs;
	gc_mnode_unskew(self);
	if (lo) {
		if (hi)
			gc_mnode_tree_unskew(hi);
		self = lo;
		goto again;
	}
	if (hi) {
		self = hi;
		goto again;
	}
}

PRIVATE NOBLOCK ATTR_COLDTEXT void
NOTHROW(KCALL gc_mman_skew)(struct mman *__restrict self) {
	if (!self->mm_mappings || gc_isskewed(self->mm_mappings->mn_minaddr))
		return; /* Already skewed */
	gc_mnode_tree_skew(self->mm_mappings);
}

PRIVATE NOBLOCK ATTR_COLDTEXT void
NOTHROW(KCALL gc_mman_unskew)(struct mman *__restrict self) {
	if (!self->mm_mappings || !gc_isskewed(self->mm_mappings->mn_minaddr))
		return; /* Already unskewed */
	gc_mnode_tree_unskew(self->mm_mappings);
}

PRIVATE NOBLOCK ATTR_COLDTEXT void
NOTHROW(KCALL gc_task_skew)(struct task *__restrict self) {
	gc_mman_skew(self->t_mman);
}

PRIVATE NOBLOCK ATTR_COLDTEXT void
NOTHROW(KCALL gc_task_unskew)(struct task *__restrict self) {
	gc_mman_unskew(self->t_mman);
}

PRIVATE NOBLOCK ATTR_COLDTEXT NONNULL((2)) ssize_t
NOTHROW(TASK_ENUM_CC _gc_task_skew_enum_cb)(void *UNUSED(arg), struct task *__restrict thread) {
	gc_task_skew(thread);
	return 0;
}

PRIVATE NOBLOCK ATTR_COLDTEXT NONNULL((2)) ssize_t
NOTHROW(TASK_ENUM_CC _gc_task_unskew_enum_cb)(void *UNUSED(arg), struct task *__restrict thread) {
	gc_task_unskew(thread);
	return 0;
}



PRIVATE NOBLOCK ATTR_COLDTEXT void
NOTHROW(KCALL gc_globals_skew)(void) {
	/* Prevent traversal of global object lists during GC leak detection.
	 * -> s.a. the rationale for why `Phase #3: Scan global objects' is disabled. */
	gc_list_skew((void **)&mpart_all_list.lh_first, offsetof(struct mpart, mp_allparts));
	gc_list_skew((void **)&fallnodes_list.lh_first, offsetof(struct fnode, fn_allnodes));
	gc_list_skew((void **)&fallsuper_list.lh_first, offsetof(struct fsuper, fs_root.fn_allsuper));

	/* Skew the kernel mman. */
	gc_mman_skew(&mman_kernel);

	/* Skew global pointers relating to threads. */
	system_enum_threads_noipi_nb(&_gc_task_skew_enum_cb, NULL);
}

PRIVATE NOBLOCK ATTR_COLDTEXT void
NOTHROW(KCALL gc_globals_unskew)(void) {
	/* Unskew global lists. */
	gc_list_unskew((void **)&mpart_all_list.lh_first, offsetof(struct mpart, mp_allparts));
	gc_list_unskew((void **)&fallnodes_list.lh_first, offsetof(struct fnode, fn_allnodes));
	gc_list_unskew((void **)&fallsuper_list.lh_first, offsetof(struct fsuper, fs_root.fn_allsuper));

	/* Unskew the kernel mman. */
	gc_mman_unskew(&mman_kernel);

	/* Unskew global pointers relating to threads. */
	system_enum_threads_noipi_nb(&_gc_task_unskew_enum_cb, NULL);
}


/* Scan the kernel for all reachable, traced pointers. */
PRIVATE NOBLOCK ATTR_COLDTEXT void
NOTHROW(KCALL gc_find_reachable)(void) {
	/* Skew global object lists. */
	gc_globals_skew();

	/* Scan for reachable objects. */
	gc_find_reachable_impl();

	/* Unskew global object lists. */
	gc_globals_unskew();
}


PRIVATE ATTR_COLDTEXT NONNULL((1)) void KCALL
gc_gather_explicit_leak(struct trace_node **__restrict pleaks,
                        u8 kind, void *base, size_t num_bytes,
                        void const **tb DFL(NULL),
                        size_t tb_len DFL(0), pid_t tid DFL(0)) {
	struct trace_node *node;
	heapptr_t node_ptr;
	size_t tb_cnt;
	node_ptr = heap_alloc_untraced(&trace_heap,
	                               offsetof(struct trace_node, tn_trace) +
	                               (tb_len * sizeof(void *)),
	                               TRACE_HEAP_FLAGS);
	node = (struct trace_node *)heapptr_getptr(node_ptr);
	trace_node_initlink(node, base, num_bytes);
	node->tn_size  = heapptr_getsiz(node_ptr);
	node->tn_reach = gc_version - 1;
	node->tn_visit = 0;
	node->tn_kind  = kind;
	node->tn_flags = 0;
	node->tn_tid   = tid;

	/* Copy traceback */
	tb_cnt = trace_node_traceback_count(node);
	if (tb_cnt) {
		void const **vec = trace_node_traceback_vector(node);
		assert(tb_cnt >= tb_len);
		memcpy(vec, tb, tb_len, sizeof(void *));
		if (tb_cnt > tb_len)
			vec[tb_len] = NULL;
	}

	/* Insert into list of leaks. */
	trace_node_leak_next(node) = *pleaks;
	*pleaks = node;
}

#ifdef CONFIG_HAVE_KERNEL_SLAB_ALLOCATORS
PRIVATE ATTR_COLDTEXT NONNULL((1, 2)) void KCALL
gc_gather_unreachable_slab(struct trace_node **__restrict pleaks,
                           struct slab *__restrict self) {
	/* Search for slabs with a status of `SLAB_SEGMENT_STATUS_ALLOC' */
	uintptr_t *bits;
	size_t i, count;
	bits  = (uintptr_t *)(self + 1);
	count = SLAB_SEGMENT_COUNT(self->s_size);
	for (i = 0; i < count; ++i) {
		unsigned int status;
		status = (bits[_SLAB_SEGMENT_STATUS_WORD(i)] >>
		          _SLAB_SEGMENT_STATUS_SHFT(i)) &
		         SLAB_SEGMENT_STATUS_MASK;
		if likely(status != SLAB_SEGMENT_STATUS_ALLOC)
			continue;
		/* Well... It's a leak :( */
		gc_gather_explicit_leak(pleaks, TRACE_NODE_KIND_SLAB,
		                        (byte_t *)self + SLAB_SEGMENT_OFFSET(self->s_size) +
		                        i * self->s_size,
		                        self->s_size);
	}
}

PRIVATE ATTR_COLDTEXT NONNULL((1, 2)) void KCALL
gc_gather_unreachable_slab_chain(struct trace_node **__restrict pleaks,
                                 struct slab_list const *__restrict self) {
	struct slab *iter;
	LIST_FOREACH (iter, self, s_link) {
		gc_gather_unreachable_slab(pleaks, iter);
	}
}

PRIVATE ATTR_COLDTEXT NONNULL((1, 2)) void KCALL
gc_gather_unreachable_slab_descriptor(struct trace_node **__restrict pleaks,
                                      struct slab_descriptor const *__restrict self) {
	gc_gather_unreachable_slab_chain(pleaks, &self->sd_free);
	gc_gather_unreachable_slab_chain(pleaks, &self->sd_used);
}

PRIVATE ATTR_COLDTEXT NONNULL((1)) void KCALL
gc_gather_unreachable_slabs(struct trace_node **__restrict pleaks) {
	unsigned int i;
	for (i = 0; i < lengthof(gc_slab_descs); ++i) {
		gc_gather_unreachable_slab_descriptor(pleaks, gc_slab_descs[i]);
	}
}
#endif /* !CONFIG_HAVE_KERNEL_SLAB_ALLOCATORS */


PRIVATE ATTR_COLDTEXT NONNULL((1)) void KCALL
gc_gather_unreachable_coreheap(struct trace_node **__restrict pleaks) {
	/* Search for allocated, but not reachable parts. */
	unsigned int i;
	for (i = 0; i < lengthof(mcoreheap_lists); ++i) {
		struct mcorepage *iter;
		SLIST_FOREACH (iter, &mcoreheap_lists[i], mcp_link) {
			unsigned int partno;
			for (partno = 0; partno < lengthof(iter->mcp_part); ++partno) {
				if (!INUSE_BITSET_GET(iter->mcp_used, partno))
					continue; /* This one's not allocated */
				if (INUSE_BITSET_GET(iter->_mcp_reach, partno))
					continue; /* This one's reachable... */
				/* Ooops; found a leak :( */
				gc_gather_explicit_leak(pleaks, TRACE_NODE_KIND_CORE,
				                        &iter->mcp_part[partno],
				                        sizeof(iter->mcp_part[partno]));
			}
		}
	}
}


PRIVATE ATTR_COLDTEXT NONNULL((1, 2)) void KCALL
gc_gather_unreachable_kernel_mman_nodes(struct mnode *__restrict self,
                                        struct trace_node **__restrict pleaks) {
again:
	/* Check if we should consider this node as a leak. */
	if (self->mn_flags & (MNODE_F__REACH | MNODE_F_KERNPART))
		goto next; /* Node is reachable. */
	if (!ADDR_ISKERN(self->mn_minaddr))
		goto next; /* Can't trace outside of kernel-space. */
	if (self->mn_part == NULL)
		goto next; /* Don't consider reserved mappings as leaks. */

	/* There is a chance during  our leak scan, _all_ kernel  pointers
	 * which we _did_ find, actually pointed directly into fully valid
	 * trace-malloc nodes.
	 *
	 * If you look at `gc_reachable_pointer()', you will see that we
	 * only mark mnode-s as `MNODE_F__REACH' when we don't manage to
	 * find any trace-nodes at the reachable address.
	 *
	 * As such, we  have to make  up for not  marking mem-nodes if  we
	 * find trace-nodes now, by  simply not considering any  seemingly
	 * unreachable nodes as truly unreachable, if there are any trace-
	 * nodes  within the range  of the mem-node  that are _NOT_ leaks.
	 *
	 * Also  note that for this purpose, we also consider nodes marked
	 * to be non-leaking as indicators that any backing mem-nodes also
	 * isn't being leaked. */
	{
		trace_node_tree_minmax_t mima;
		tm_nodes_minmaxlocate((uintptr_t)mnode_getminaddr(self),
		                      (uintptr_t)mnode_getmaxaddr(self),
		                      &mima);
		if (mima.mm_min) {
			for (;;) {
				if (mima.mm_min->tn_reach == gc_version)
					goto next; /* (seemingly) unreachable mem-node contains reachable trace-node */
				if (mima.mm_min->tn_flags & TRACE_NODE_FLAG_NOLEAK)
					goto next; /* (seemingly) unreachable mem-node contains non-leaking trace-node */
				if (mima.mm_min == mima.mm_max)
					break;
				mima.mm_min = tm_nodes_nextnode(mima.mm_min);
			}
		}
	}

	/* NOTE: There may be  more situations where  a mem-node  should
	 *       be considered reachable, even when no pointers pointing
	 *       to it exist. */

	/* Yes, this does appear to be a leak! */
	{
		void const **tb = NULL;
		size_t tb_len   = 0;
		pid_t tid       = 0;
		struct trace_node *tn;

		/* When `self' was dynamically allocated, copy its traceback */
		tn = tm_nodes_locate(self);
		if (tn) {
			size_t max;
			tb  = trace_node_traceback_vector(tn);
			max = trace_node_traceback_count(tn);
			for (tb_len = 0; tb_len < max; ++tb_len) {
				if (tb[tb_len] == NULL)
					break;
			}
			tid = tn->tn_tid;
		}
		gc_gather_explicit_leak(pleaks, TRACE_NODE_KIND_MNODE,
		                        mnode_getaddr(self),
		                        mnode_getsize(self),
		                        tb, tb_len, tid);
	}

next:
	if (self->mn_mement.rb_lhs) {
		if (self->mn_mement.rb_rhs)
			gc_mnode_reset_reach(self->mn_mement.rb_rhs);
		self = self->mn_mement.rb_lhs;
		goto again;
	}
	if (self->mn_mement.rb_rhs) {
		self = self->mn_mement.rb_rhs;
		goto again;
	}
}

PRIVATE ATTR_COLDTEXT NONNULL((1)) void KCALL
gc_gather_unreachable_mnodes(struct trace_node **__restrict pleaks) {
	if (mman_kernel.mm_mappings)
		gc_gather_unreachable_kernel_mman_nodes(mman_kernel.mm_mappings, pleaks);
}


PRIVATE NOBLOCK ATTR_COLDTEXT bool
NOTHROW(KCALL gc_gather_unreachable_nodes)(struct trace_node *__restrict node,
                                           struct trace_node **__restrict pleaks) {
again:
	if (node->tn_reach != gc_version) {
		/* This node wasn't reached. (but ignore if the node has the NOLEAK flag set) */
		if (!(node->tn_flags & TRACE_NODE_FLAG_NOLEAK)) {
			tm_nodes_removenode(node);
			trace_node_leak_next(node) = *pleaks;
			*pleaks = node;
			return true;
		}
	}
	if (node->tn_link.rb_lhs) {
		if (node->tn_link.rb_rhs) {
			if (gc_gather_unreachable_nodes(node->tn_link.rb_rhs, pleaks))
				return true;
		}
		node = node->tn_link.rb_lhs;
		goto again;
	}
	if (node->tn_link.rb_rhs) {
		node = node->tn_link.rb_rhs;
		goto again;
	}
	return false;
}


/* Called after having become a super-override */
PRIVATE ATTR_COLDTEXT struct trace_node *KCALL
kmalloc_leaks_gather(void) {
	struct trace_node *result;

	/* Get a new GC version. */
	++gc_version;
	if unlikely(gc_version == 0)
		gc_version = 1; /* Don't recycle version #0 */

	/* Reset reachable bits for coreheap objects. */
	gc_coreheap_reset_reach();

	/* Reset reachable bits for kernel mman nodes. */
	gc_kernel_mman_nodes_reset_reach();

	/* Clear the  is-reachable bits  from all  of
	 * the different slabs that could be reached. */
#ifdef CONFIG_HAVE_KERNEL_SLAB_ALLOCATORS
	RAII_FINALLY { gc_slab_reset_reach(); };
#endif /* CONFIG_HAVE_KERNEL_SLAB_ALLOCATORS */

	/* Search for reachable data. */
	gc_find_reachable();

	/* Gather memory leaks. */
	result = NULL;
	TRY {
		/* Gather memory leaks from `mcoreheap_alloc()' */
		gc_gather_unreachable_coreheap(&result);

#ifdef CONFIG_HAVE_KERNEL_SLAB_ALLOCATORS
		/* Gather memory leaks from slabs.
		 * NOTE: This right here may cause new memory to be allocated. */
		gc_gather_unreachable_slabs(&result);
#endif /* CONFIG_HAVE_KERNEL_SLAB_ALLOCATORS */

		/* Gather nodes within the kernel mman who's pointed-to memory
		 * isn't reachable. */
		gc_gather_unreachable_mnodes(&result);
	} EXCEPT {
		/* Free dynamically allocated leak descriptors. */
		while (result) {
			struct trace_node *next;
			next = trace_node_leak_next(result);
			trace_node_free(result);
			result = next;
		}
		RETHROW();
	}

	/* Gather leaks from trace nodes. */
	/* Because of how removing nodes  from an RB-tree works, the  act
	 * of removing a node may cause the tree structure to be altered,
	 * such that  we'll be  unable to  hit all  (potentially  leaked)
	 * nodes during a single pass. As such, we must keep on  scanning
	 * the tree until  it's become  empty (unlikely) or  until we  no
	 * longer find any more leaks. */
	while (tm_nodes && gc_gather_unreachable_nodes(tm_nodes, &result))
		;

	return result;
}


#define FOREACH_XREF_BEGIN(ptr, pptr, scan_umin, scan_umax, target_min, target_max) \
	do {                                                                            \
		void *ptr, **pptr, **_scan_end;                                             \
		pptr      = (void **)(scan_umin);                                           \
		_scan_end = (void **)(scan_umax);                                           \
		for (; pptr <= _scan_end; ++pptr) {                                         \
			COMPILER_READ_BARRIER();                                                \
			ptr = *pptr;                                                            \
			COMPILER_READ_BARRIER();                                                \
			if ((uintptr_t)ptr >= (uintptr_t)(target_min) &&                        \
			    (uintptr_t)ptr <= (uintptr_t)(target_max)) {                        \
				do
#define FOREACH_XREF_END() \
				__WHILE0;  \
			}              \
		}                  \
	}	__WHILE0

/* Check if `lhs < rhs' as far as priority goes. */
PRIVATE ATTR_COLDTEXT ATTR_PURE WUNUSED NONNULL((1, 2)) bool KCALL
trace_node_isbelow(struct trace_node *__restrict lhs,
                   struct trace_node *__restrict rhs) {
	/* Leaks with more XREFS should come before ones with less. */
	if (trace_node_leak_getxrefs(lhs) < trace_node_leak_getxrefs(rhs))
		return true;
	if (trace_node_leak_getxrefs(lhs) > trace_node_leak_getxrefs(rhs))
		return false;

	/* Larger leaks should come before smaller leaks. */
	if (trace_node_usize(lhs) > trace_node_usize(rhs))
		return true;
	if (trace_node_usize(lhs) < trace_node_usize(rhs))
		return false;

	/* If everything else matches, just sort by address. */
	return trace_node_uaddr(lhs) < trace_node_uaddr(rhs);
}

PRIVATE ATTR_COLDTEXT ATTR_RETNONNULL WUNUSED NONNULL((1)) struct trace_node *KCALL
kmalloc_pop_smallest_node(struct trace_node **__restrict pleaks) {
	struct trace_node **pwinner, *winner;
	struct trace_node **piter, *iter;
	pwinner = pleaks;
	winner  = *pwinner;
	piter   = &trace_node_leak_next(winner);
	while ((iter = *piter) != NULL) {
		/* Check if `iter' should come before `winner' */
		if (trace_node_isbelow(iter, winner)) {
			winner  = iter;
			pwinner = piter;
		}
		piter = &trace_node_leak_next(iter);
	}
	/* Unlink+return the winner node. */
	*pwinner = trace_node_leak_next(winner);
	return winner;
}


PRIVATE ATTR_COLDTEXT ATTR_RETNONNULL WUNUSED NONNULL((1)) struct trace_node *KCALL
kmalloc_leaks_sort(struct trace_node *leaks) {
	struct trace_node *leak;
	struct trace_node *newchain, *newchain_last;
	/* Step #1: Calculate the xref total for every node. */
	for (leak = leaks; leak; leak = trace_node_leak_next(leak)) {
		/* XXX: Only use this slow O(N^2) approach when there are only a couple of leaks,
		 *      (say: less than 64), and try to re-construct an RBTREE for faster lookup
		 *      of addr->node which can then be used to only have to enumerate memory of
		 *      nodes once. */
		struct trace_node *leak2;
		uintptr_t leak_min, leak_max;
		size_t xref_count = 0;
		trace_node_leak_getscan_uminmax(leak, leak_min, leak_max);
		for (leak2 = leaks; leak2; leak2 = trace_node_leak_next(leak2)) {
			uintptr_t leak2_min, leak2_max;
			if (leak == leak2)
				continue;
			trace_node_leak_getscan_uminmax(leak2, leak2_min, leak2_max);
			/* TODO: If `leak' or `leak2' is `TRACE_NODE_KIND_BITSET', then
			 *       we must ensure to only  check traced areas for  xrefs! */
			FOREACH_XREF_BEGIN(ptr, pptr,
			                   leak2_min, leak2_max,
			                   leak_min, leak_max) {
				++xref_count;
			}
			FOREACH_XREF_END();
		}
		trace_node_leak_setxrefs(leak, xref_count);
	}
	/* Sort the chain of leaks. */
	newchain = kmalloc_pop_smallest_node(&leaks);
	newchain_last = newchain;
	while (leaks) {
		leak = kmalloc_pop_smallest_node(&leaks);
		trace_node_leak_next(newchain_last) = leak;
		newchain_last = leak;
	}
	/* Terminate the (now sorted) chain. */
	trace_node_leak_next(newchain_last) = NULL;
	return newchain;

}




/* Ensure that required locks are available, or release
 * the super-override and wait  for them to become  so. */
PRIVATE ATTR_COLDTEXT bool KCALL
waitfor_locks_or_unlock(void) THROWS(E_WOULDBLOCK) {
#define local_unlock() sched_super_override_end()
#define require_lock(available, waitfor) \
	if (!(available)) {                  \
		local_unlock();                  \
		waitfor;                         \
		goto fail;                       \
	}

	/* Basic locks to memory-related base components. */
	require_lock(mman_lock_available(&mman_kernel), mman_lock_waitwrite(&mman_kernel));
	require_lock(atomic_lock_available(&kernel_default_heap.h_lock), atomic_lock_waitfor(&kernel_default_heap.h_lock));
	require_lock(atomic_lock_available(&kernel_locked_heap.h_lock), atomic_lock_waitfor(&kernel_locked_heap.h_lock));
	require_lock(atomic_lock_available(&trace_heap.h_lock), atomic_lock_waitfor(&trace_heap.h_lock));

	/* Locks for global object lists. */
	require_lock(mpart_all_available(), mpart_all_waitfor());
	require_lock(fallnodes_available(), fallnodes_waitfor());
	require_lock(fallsuper_available(), fallsuper_waitfor());

	/* All required locks are available! */
	return true;
fail:
	return false;
#undef require_lock
#undef local_unlock
}


/* Collect, print and discard memory leaks. */
PUBLIC ATTR_COLDTEXT kmalloc_leaks_t KCALL
kmalloc_leaks_collect(void) THROWS(E_WOULDBLOCK) {
	struct trace_node *result;
	NESTED_EXCEPTION;

again:
	/* Acquire a scheduler super-override, thus ensuring that we're
	 * the only  thread  running  anywhere on  the  entire  system.
	 *
	 * NOTE: We do this first,  since a super-override should  only
	 *       be acquired when not already holding any atomic locks,
	 *       since when holding such locks, there is a small chance
	 *       that other CPUs are currently trying to acquire  them,
	 *       preventing us from reaching them.
	 * Technically, this shouldn't happen,  since you shouldn't do  a
	 * `while (!trylock()) task_pause();'  loop  (meaning that  a CPU
	 * that is blocking-waiting for an  atomic lock should also  have
	 * preemption enabled), and where you are allowed to do this kind
	 * of loop, you're actually dealing with an SMP-lock, which  also
	 * requires that preemption be  disabled, where becoming a  super
	 * override will implicitly cause  one to acquire all  SMP-locks,
	 * since a CPU that holds an SMP-lock must release it before  re-
	 * enabling preemption, meaning  that being able  to send an  IPI
	 * to every CPU, and having every CPU ACK that IPI, also  implies
	 * that all CPUs had preemption enabled, which then implies  that
	 * no CPU was holding an SMP-lock.
	 *
	 * But despite all of that, it's better to be safe than sorry. */
	sched_super_override_start();

	/* Ensure that required locks are available.
	 * Because we're running single-threaded, we don't actually have  to
	 * acquire those locks proper, but  to ensure consistency, we  still
	 * need to make sure they're available (because if they aren't, then
	 * relevant data structures may be in an inconsistent state)
	 *
	 * Also: collection of certain types of memory leaks requires us to
	 *       allocate additional memory (e.g. when we detect that  part
	 *       of the coreheap, or a mem-node has leaked). In those cases
	 *       the call to `gc_gather_explicit_leak()' makes a heap alloc
	 *       call that in turn must acquire a lock to the heap. And  if
	 *       that lock isn't available after we get the super override,
	 *       it  will never become so until we allow the holding thread
	 *       to run some more (which can only happen if we stop being a
	 *       super override). */
	if (!waitfor_locks_or_unlock())
		goto again;

	{
		RAII_FINALLY {
			/* Release the scheduler super-override, thereby
			 * allowing normal system  execution to  resume.
			 *
			 * This must _always_ happen, so we use FINALLY. */
			sched_super_override_end();

		};

		/* Actually search for memory leaks. */
		result = kmalloc_leaks_gather();
	}

	/* Sort memory leaks by number of x-refs
	 *
	 * This can happen after we  stop being a super-override,  since
	 * the fact that all of these are memory leaks also implies that
	 * no other piece of code on the entire system knows about them,
	 * meaning  that we're the only ones which are currently able to
	 * access any of them. */
	if (result)
		result = kmalloc_leaks_sort(result);

	return result;
}

#ifdef CONFIG_HAVE_KERNEL_SLAB_ALLOCATORS
PRIVATE ATTR_COLDBSS bool gc_slab_leak_did_notify_noslab_boot_option = false;
#endif /* CONFIG_HAVE_KERNEL_SLAB_ALLOCATORS */

PUBLIC ATTR_COLDTEXT ssize_t KCALL
kmalloc_leaks_print(kmalloc_leaks_t leaks,
                    pformatprinter printer, void *arg,
                    size_t *pnum_leaks) {
#define DO(expr)                           \
	do {                                   \
		if unlikely(((temp) = (expr)) < 0) \
			goto err;                      \
		result += temp;                    \
	}	__WHILE0
#define PRINT(str)  DO((*printer)(arg, str, COMPILER_STRLEN(str)))
#define PRINTF(...) DO(format_printf(printer, arg, __VA_ARGS__))
	size_t num_leaks = 0;
	ssize_t temp, result = 0;
	struct trace_node *iter;
	for (iter = (struct trace_node *)leaks;
	     iter; iter = trace_node_leak_next(iter))
		++num_leaks;
	if (pnum_leaks)
		*pnum_leaks = num_leaks;
	if (!num_leaks)
		goto done;
	result = format_printf(printer, arg,
	                       "============= %" PRIuSIZ " Memory leak%s\n",
	                       num_leaks, num_leaks == 1 ? "" : "s");
	if unlikely(result < 0)
		goto done;
	for (iter = (struct trace_node *)leaks;
	     iter; iter = trace_node_leak_next(iter)) {
		struct trace_node *xref_leak;
		size_t tracesize, i;
		void const **traceback, *pc;
		char const *method;
		uintptr_t umin, umax;
		size_t xrefs;
		umin      = trace_node_umin(iter);
		umax      = trace_node_umax(iter);
		traceback = trace_node_traceback_vector(iter);
		tracesize = trace_node_traceback_count(iter);
		pc        = tracesize ? traceback[0] : NULL;
		xrefs     = trace_node_leak_getxrefs(iter);
		switch (iter->tn_kind) {

		case TRACE_NODE_KIND_MALL:
			umin += CONFIG_KERNEL_MALL_HEAD_SIZE;
			umax -= CONFIG_KERNEL_MALL_TAIL_SIZE;
			method = "kmalloc-memory";
			break;

		case TRACE_NODE_KIND_BITSET:
			/* TODO: Print one entry for every consecutive address range of still-traced words. */
			method    = "partially untraced heap memory";
			tracesize = 0; /* No traceback */
			break;

#ifdef CONFIG_HAVE_KERNEL_SLAB_ALLOCATORS
		case TRACE_NODE_KIND_SLAB:
			/* Slab allocations are way too light-weight to be able to support tracebacks.
			 * As such, while we _are_ able to detect slab memory leaks, we aren't able to
			 * tell  the user where/how  the leaking memory  was allocated. However, since
			 * slab allocators are always allowed to either...
			 *
			 *   - Allocate regular kmalloc()-style memory (as  a matter of fact, most  calls
			 *     to slab allocators actually stem from compile-time dispatching from inside
			 *     of a FORCELOCAL kmalloc() wrapper)
			 *     Booting with `noslab' will modify the  text of these functions to  directly
			 *     call forward to the regular heap functions, which are then able to generate
			 *     proper tracebacks.
			 *
			 *   - Simply return `NULL'. This might come as a surprise, but because all  kernel
			 *     slab  memory _must_ be  continuous, there is a  chance that some conflicting
			 *     memory mapping will simply prevent us from expanding slab space any further.
			 *     Due  to this case,  pure slab allocators (i.e.  slab allocator function that
			 *     will never return  conventional heap  memory) are always  allowed to  simply
			 *     return `NULL', which  is indicative  of their  inability to  find space  for
			 *     additional slab memory.
			 *
			 * ... we can tell the user to reboot with "noslab" to turn off the system, thus
			 *     causing  tracebacks to be  generated for all the  cases where slabs would
			 *     normally be used. */
			if (!gc_slab_leak_did_notify_noslab_boot_option) {
				gc_slab_leak_did_notify_noslab_boot_option = true;
				PRINT("slab: Slab memory leaks don't include tracebacks.\n"
				      "slab: Consider rebooting with `noslab'\n");
			}
			method = "slab-memory";
			break;
#endif /* CONFIG_HAVE_KERNEL_SLAB_ALLOCATORS */

		case TRACE_NODE_KIND_CORE:
			method = "coreheap-memory";
			break;

		case TRACE_NODE_KIND_MNODE:
			method = "mnode-memory";
			break;

		default:
			method = "heap-memory";
			break;
		}
		PRINTF("Leaked %" PRIuSIZ " bytes of %s at %p...%p "
		       "[tid=%" PRIu32 "] (Referenced %" PRIuSIZ " times)\n",
		       (umax - umin) + 1, method,
		       umin, umax, iter->tn_tid, xrefs);
		/* Print xrefs */
		for (xref_leak = (struct trace_node *)leaks;
		     xref_leak; xref_leak = trace_node_leak_next(xref_leak)) {
			uintptr_t xref_umin, xref_umax;
			if (xref_leak == iter)
				continue;
			trace_node_leak_getscan_uminmax(xref_leak, xref_umin, xref_umax);
			/* TODO: If `iter' or `xref_leak' is `TRACE_NODE_KIND_BITSET', then
			 *       we  must  ensure to  only  check traced  areas  for xrefs! */
			FOREACH_XREF_BEGIN(ptr, pptr, xref_umin, xref_umax, umin, umax) {
				PRINTF("\tReferenced at [%p]=%p", pptr, ptr);
				if ((uintptr_t)ptr > umin)
					PRINTF(" [.+%#" PRIxSIZ "]", (uintptr_t)ptr - umin);
				PRINTF(" by leak at %p...%p", xref_umin, xref_umax);
				if ((uintptr_t)pptr > xref_umin)
					PRINTF(" [.+%#" PRIxSIZ "]", (uintptr_t)pptr - xref_umin);
				PRINTF("\n");
			}
			FOREACH_XREF_END();
		}
		if (tracesize && pc) {
			DO(addr2line_printf(&syslog_printer, SYSLOG_LEVEL_RAW,
			                    instruction_trypred(pc, ISA_DEFAULT),
			                    pc, "Allocated here"));
			for (i = 1; i < tracesize; ++i) {
				void const *pc_ent;
				pc_ent = traceback[i];
				if (!pc_ent)
					break;
				DO(addr2line_printf(printer, arg,
				                    instruction_trypred(pc_ent, ISA_DEFAULT),
				                    pc_ent, "Called here"));
			}
		}
		/* If  the amount of leaked memory is small enough, also print a hexdump of
		 * its contents. This might reveal sensitive data, but can be highly useful
		 * to learn more about what got leaked.
		 * Also: opening  and interacting with /proc/kos/leaks requires CAP_SYS_ADMIN,
		 *       so it's OK if there ends being something sensitive that gets revealed
		 *       by this. */
		if (umin + 1024 > umax) {
			PRINTF("%$[hex]\n",
			       (size_t)(umax - umin) + 1,
			       (void *)umin);
		}
		PRINT("\n");
	}
done:
	return result;
err:
	return temp;
#undef PRINTF
#undef PRINT
#undef DO
}

PUBLIC NOBLOCK ATTR_COLDTEXT void
NOTHROW(KCALL kmalloc_leaks_release)(kmalloc_leaks_t leaks,
                                     unsigned int how) {
	struct trace_node *node, *next;
	assert(how == KMALLOC_LEAKS_RELEASE_RESTORE ||
	       how == KMALLOC_LEAKS_RELEASE_DISCARD ||
	       how == KMALLOC_LEAKS_RELEASE_FREE);
	node = (struct trace_node *)leaks;
	while (node) {
		next = trace_node_leak_next(node);
		if (how == KMALLOC_LEAKS_RELEASE_FREE) {
			/* TODO: When the leak  was caused by  an unreferenced global  object,
			 *       then we mustn't blindly free the associated object when we're
			 *       supposed to discard leaks.
			 * As a matter of fact: there is no way to (safely; iow: without blocking)
			 * free  such a memory leak, as it would first have to be removed from the
			 * relevant global list, which in  turn we also could  only do if it  were
			 * still unreachable at this point, which  we could only confirm by  doing
			 * another scan for memory leaks. */

			/* Try  to release the memory pointed to by the memory leaks.
			 * However, we can only do this for kmalloc() and slab-leaks.
			 * Custom traced regions cannot be blindly free'd! */
			switch (node->tn_kind) {

			case TRACE_NODE_KIND_MALL: {
				gfp_t flags;
				flags = node->tn_flags & __GFP_HEAPMASK;
				heap_free_untraced(&kernel_heaps[flags],
				                   trace_node_uaddr(node),
				                   trace_node_usize(node),
				                   flags);
			}	break;

#ifdef CONFIG_HAVE_KERNEL_SLAB_ALLOCATORS
			case TRACE_NODE_KIND_SLAB:
#endif /* CONFIG_HAVE_KERNEL_SLAB_ALLOCATORS */
				slab_free(trace_node_uaddr(node));
				break;

			case TRACE_NODE_KIND_CORE:
				mcoreheap_free((union mcorepart *)trace_node_uaddr(node));
				break;

			default:
				break;
			}
		}
		if (how == KMALLOC_LEAKS_RELEASE_RESTORE &&
#ifdef CONFIG_HAVE_KERNEL_SLAB_ALLOCATORS
		    node->tn_kind != TRACE_NODE_KIND_SLAB &&
#endif /* CONFIG_HAVE_KERNEL_SLAB_ALLOCATORS */
		    node->tn_kind != TRACE_NODE_KIND_CORE &&
		    node->tn_kind != TRACE_NODE_KIND_MNODE &&
		    1) {
			lock_acquire();
			tm_nodes_insert(node);
			lock_release();
		} else {
			trace_node_free(node);
		}
		node = next;
	}
}

/* Count the # of objects in `leaks' */
PUBLIC NOBLOCK ATTR_PURE WUNUSED size_t
NOTHROW(KCALL kmalloc_leaks_count)(kmalloc_leaks_t leaks) {
	size_t result = 0;
	struct trace_node *node;
	node = (struct trace_node *)leaks;
	while (node) {
		++result;
		node = trace_node_leak_next(node);
	}
	return result;
}


/* Helpers for working with abstract memory leak descriptors. */

/* Return the next memory after `prev' from the set of `leaks'
 * When `prev == NULL', return  the first  leak from  `leaks'.
 * Returns `NULL' when all leaks were enumerated. */
PUBLIC NOBLOCK ATTR_PURE memleak_t
NOTHROW(FCALL memleak_next)(kmalloc_leaks_t leaks, memleak_t prev) {
	if (!leaks)
		return NULL;
	if (!prev)
		return (struct trace_node *)leaks;
	return trace_node_leak_next(prev);
}

/* Get a  named  attribute  of `self',  or  `NULL'  if  the
 * attribute isn't available or unknown, or `self == NULL'.
 * @param: attr: One of `MEMLEAK_ATTR_*' */
PUBLIC ATTR_PURE void *FCALL
memleak_getattr(memleak_t self, uintptr_t attr) {
	if (!self)
		return NULL;

	/* Query memory leak attributes. */
	switch (attr) {

	case MEMLEAK_ATTR_MINADDR:
		return (void *)trace_node_umin(self);

	case MEMLEAK_ATTR_MAXADDR:
		return (void *)trace_node_umax(self);

	case MEMLEAK_ATTR_LEAKSIZE:
		return (void *)trace_node_usize(self);

	case MEMLEAK_ATTR_MINUSER: {
		uintptr_t result = trace_node_umin(self);
		if (self->tn_kind == TRACE_NODE_KIND_MALL)
			result += CONFIG_KERNEL_MALL_HEAD_SIZE;
		return (void *)result;
	}	break;

	case MEMLEAK_ATTR_MAXUSER: {
		uintptr_t result = trace_node_umax(self);
		if (self->tn_kind == TRACE_NODE_KIND_MALL)
			result -= CONFIG_KERNEL_MALL_TAIL_SIZE;
		return (void *)result;
	}	break;

	case MEMLEAK_ATTR_USERSIZE: {
		size_t result = trace_node_usize(self);
		if (self->tn_kind == TRACE_NODE_KIND_MALL)
			result -= (CONFIG_KERNEL_MALL_HEAD_SIZE + CONFIG_KERNEL_MALL_TAIL_SIZE);
		return (void *)result;
	}	break;

	case MEMLEAK_ATTR_TID:
		return (void *)(uintptr_t)self->tn_tid;

	case MEMLEAK_ATTR_TBSIZE: {
		size_t result;
		result = trace_node_traceback_count(self);
		/* Trim NULL entries from the back of the traceback. */
		while (result && trace_node_traceback_vector(self)[result - 1] == NULL)
			--result;
		return (void *)result;
	}	break;

	case MEMLEAK_ATTR_NOWALK:
		return (void *)(uintptr_t)(self->tn_flags & TRACE_NODE_FLAG_NOWALK);

	default:
		break;
	}

	/* Check for traceback vector index attributes. */
	if (attr >= MEMLEAK_ATTR_TBADDR(0) && attr < MEMLEAK_ATTR_TBADDR(trace_node_traceback_count(self)))
		return (void *)trace_node_traceback_vector(self)[attr - MEMLEAK_ATTR_TBADDR(0)];

	/* Unknown/undefined attribute */
	return NULL;
}




/* Search for leaked heap memory, dump them to the system log, and return the
 * total number of leaked blocks.
 * Note that to do what it does, this function has to temporarily elevate the
 * calling  thread  to   super-override  status  (s.a.   <sched/scheduler.h>)
 * This function is the combination of:
 *     kmalloc_leaks_collect() +
 *     kmalloc_leaks_print(printer: &syslog_printer, arg: SYSLOG_LEVEL_RAW) +
 *     kmalloc_leaks_release() */
PUBLIC ATTR_COLDTEXT ATTR_NOINLINE size_t KCALL
kmalloc_leaks(void) THROWS(E_WOULDBLOCK) {
	size_t result;
	kmalloc_leaks_t leaks;
	leaks = kmalloc_leaks_collect();
	RAII_FINALLY { kmalloc_leaks_release(leaks, KMALLOC_LEAKS_RELEASE_RESTORE); };
	kmalloc_leaks_print(leaks, &syslog_printer, SYSLOG_LEVEL_RAW, &result);
	return result;
}



/* Must be INTERN, because this function gets overwritten
 * when   `nomall'   is   passed   on   the   commandline */
INTERN ATTR_NOINLINE NONNULL((1, 3)) void
NOTHROW(KCALL trace_malloc_generate_traceback)(void const **__restrict buffer, size_t buflen,
                                               struct lcpustate *__restrict state,
                                               unsigned int n_skip) {
#if 1
	struct lcpustate oldstate;
	/* NOTE: Despite this being for debugging purposes, _DONT_ use `unwind_for_debug()' here!
	 *       That one has  to make  use of  the kernel heap  (and consequently  us) in  order
	 *       to be able  to construct user-space  program/section descriptors, etc,  where-as
	 *       the  normal unwind() function is specifically designed  to _not_ make use of any
	 *       heap  memory  (which is  also the  reason why  drivers pre-load  their .eh_frame
	 *       sections during initialization, rather than loading them lazily)
	 * But the reason this is done isn't only for this, but rather to ensure that throwing
	 * exceptions  and the like don't just randomly  fail because the kernel couldn't find
	 * enough memory... */
	for (;;) {
		unwind_errno_t unwind_error;
		if (n_skip == 0) {
			*buffer++ = lcpustate_getpc(state);
			if (!--buflen)
				return;
		} else {
			--n_skip;
		}
		memcpy(&oldstate, state, sizeof(struct lcpustate));
		unwind_error = unwind(lcpustate_getpc(&oldstate) - 1,
		                      &unwind_getreg_lcpustate, &oldstate,
		                      &unwind_setreg_lcpustate, state);
		if (unwind_error != UNWIND_SUCCESS) {
			if (unwind_error == UNWIND_INVALID_REGISTER) {
				struct kcpustate kc;
				/* Try to continue unwinding with a larger register pool */
				lcpustate_to_kcpustate(&oldstate, &kc);
				unwind_error = unwind(lcpustate_getpc(&oldstate) - 1,
				                      &unwind_getreg_lcpustate, &oldstate,
				                      &unwind_setreg_kcpustate, &kc);
				if (unwind_error == UNWIND_SUCCESS) {
					struct kcpustate nc;
					for (;;) {
						if (n_skip == 0) {
							*buffer++ = kcpustate_getpc(&kc);
							if (!--buflen)
								return;
						} else {
							--n_skip;
						}
						memcpy(&nc, &kc, sizeof(struct kcpustate));
						unwind_error = unwind(kcpustate_getpc(&nc) - 1,
						                      &unwind_getreg_kcpustate, &nc,
						                      &unwind_setreg_kcpustate, &kc);
						if (unwind_error != UNWIND_SUCCESS)
							break;
					}
				}
			}
			break;
		}
	}
#endif
	/* Make sure that when there are unused entries, the chain is NULL-terminated */
	if (buflen)
		*buffer = NULL;
}

/* Begin tracing the given `node' */
PRIVATE ATTR_NOINLINE NOBLOCK_IF(gfp & GFP_ATOMIC) void FCALL
insert_trace_node(struct trace_node *__restrict node,
                  gfp_t gfp, unsigned int n_skip)
		THROWS(E_BADALLOC, E_WOULDBLOCK);
PRIVATE ATTR_NOINLINE NOBLOCK_IF(gfp & GFP_ATOMIC) bool
NOTHROW(FCALL insert_trace_node_nx)(struct trace_node *__restrict node,
                                    gfp_t gfp, unsigned int n_skip);

/* Resolve existing (possibly bitset-based) mappings between [umin, umax]
 * These  functions  must  be  called  while  already  holding  the lock.
 * NOTE: If these functions return an exception/false, the lock will have been released! */
PRIVATE ATTR_NOINLINE NOBLOCK_IF(gfp & GFP_ATOMIC) void FCALL
insert_trace_node_resolve(uintptr_t umin, uintptr_t umax,
                          gfp_t gfp, unsigned int n_skip,
                          LOCK_PARAMS)
		THROWS(E_BADALLOC, E_WOULDBLOCK);
PRIVATE ATTR_NOINLINE NOBLOCK_IF(gfp & GFP_ATOMIC) bool
NOTHROW(FCALL insert_trace_node_resolve_nx)(uintptr_t umin, uintptr_t umax,
                                            gfp_t gfp, unsigned int n_skip,
                                            LOCK_PARAMS);


/************************************************************************/
/* Auto-tracing heap functions                                          */
/************************************************************************/

PUBLIC NOBLOCK ATTR_NOINLINE void
NOTHROW(KCALL heap_free)(struct heap *__restrict self,
                         VIRT void *ptr, size_t num_bytes,
                         gfp_t flags) {
	kmalloc_untrace_n_impl(ptr, num_bytes, 1);
	heap_free_untraced(self, ptr, num_bytes, flags);
}

PUBLIC ATTR_NOINLINE WUNUSED NONNULL((1)) size_t
NOTHROW(KCALL heap_truncate)(struct heap *__restrict self, void *base,
                             size_t old_size, size_t new_size, gfp_t free_flags) {
	size_t free_bytes;
	assertf(!old_size || old_size >= HEAP_MINSIZE,
	        "Invalid heap_truncate(): Too few bytes (%" PRIuSIZ " < %" PRIuSIZ ")",
	        old_size, HEAP_MINSIZE);
	assertf(!old_size || IS_ALIGNED((uintptr_t)base, HEAP_ALIGNMENT),
	        "Invalid heap_truncate(): Unaligned base pointer %p",
	        base);
	assertf(IS_ALIGNED(old_size, HEAP_ALIGNMENT),
	        "Invalid heap_truncate(): Unaligned old_size size %" PRIuSIZ " (%#" PRIxSIZ ")",
	        old_size, old_size);
	if unlikely(OVERFLOW_UADD(new_size, (size_t)(HEAP_ALIGNMENT - 1), &new_size))
		goto return_old_size;
	new_size &= ~(HEAP_ALIGNMENT - 1);
	if unlikely(new_size < HEAP_MINSIZE)
		new_size = HEAP_MINSIZE;
	if unlikely(new_size >= old_size)
		goto return_old_size;
	/* Free trailing memory. */
	free_bytes = old_size - new_size;
	if (free_bytes >= HEAP_MINSIZE) {
		heap_free(self, (void *)((uintptr_t)base + new_size),
		          free_bytes, free_flags);
		return new_size;
	}
return_old_size:
	return old_size;
}

PUBLIC NOBLOCK ATTR_NOINLINE WUNUSED size_t
NOTHROW(KCALL kmalloc_usable_size)(VIRT void *ptr) {
	struct trace_node *node;
	size_t result;
	if (!ptr)
		return 0;
	assert(IS_ALIGNED((uintptr_t)ptr, HEAP_ALIGNMENT));
#ifdef CONFIG_HAVE_KERNEL_SLAB_ALLOCATORS
	if (KERNEL_SLAB_CHECKPTR(ptr))
		return SLAB_GET(ptr)->s_size;
#endif /* CONFIG_HAVE_KERNEL_SLAB_ALLOCATORS */
	lock_acquire();
	node = tm_nodes_locate(ptr);
	if unlikely(!node) {
		lock_break();
		kernel_panic_n(/* n_skip: */ 1,
		               "kmalloc_usable_size(%p): No node at this address",
		               ptr);
		return 0;
	}
	if unlikely(node->tn_kind != TRACE_NODE_KIND_MALL) {
		node = trace_node_dupa_tb(node);
		lock_break();
		kernel_panic_n(/* n_skip: */ 1,
		               "kmalloc_usable_size(%p): Node at %p...%p wasn't created by kmalloc()\n"
		               "%[gen:c]",
		               ptr, trace_node_umin(node), trace_node_umax(node),
		               &trace_node_print_traceback, node);
		return 0;
	}
	if unlikely(ptr != trace_node_uaddr(node) + CONFIG_KERNEL_MALL_HEAD_SIZE) {
		node = trace_node_dupa_tb(node);
		lock_break();
		kernel_panic_n(/* n_skip: */ 1,
		               "kmalloc_usable_size(%p): Passed pointer does not "
		               "match start of containing node %p...%p (%p...%p)\n"
		               "%[gen:c]",
		               ptr,
		               trace_node_umin(node) + CONFIG_KERNEL_MALL_HEAD_SIZE,
		               trace_node_umax(node) - CONFIG_KERNEL_MALL_TAIL_SIZE,
		               trace_node_umin(node), trace_node_umax(node),
		               &trace_node_print_traceback, node);
		return 0;
	}

	/* Verify head/tail integrity of `node' */
#ifdef HAVE_kmalloc_validate_node
	if (!kmalloc_validate_node(1, node)) {
		lock_break();
		return 0;
	}
#endif /* HAVE_kmalloc_validate_node */

	/* Calculate the user-payload-size from the trace-node. */
	result = trace_node_usize(node) - (CONFIG_KERNEL_MALL_HEAD_SIZE +
	                                   CONFIG_KERNEL_MALL_TAIL_SIZE);
	lock_release();
	return result;
}

PUBLIC NOBLOCK ATTR_NOINLINE void
NOTHROW(KCALL kffree)(VIRT void *ptr, gfp_t flags) {
	void *user_area_ptr;
	size_t user_area_siz;
	struct trace_node *node;
	if (!ptr)
		return; /* Ignore NULL-pointers. */
#ifdef CONFIG_HAVE_KERNEL_SLAB_ALLOCATORS
	if (KERNEL_SLAB_CHECKPTR(ptr)) {
		slab_ffree(ptr, flags);
		return;
	}
#endif /* CONFIG_HAVE_KERNEL_SLAB_ALLOCATORS */
	lock_acquire();
	node = tm_nodes_remove(ptr);
	if unlikely(!node) {
		lock_break();
		kernel_panic_n(/* n_skip: */ 1,
		               "kffree(%p, %#x): No node at this address",
		               ptr, flags);
		return;
	}
	if unlikely(node->tn_kind != TRACE_NODE_KIND_MALL) {
		tm_nodes_insert(node);
		node = trace_node_dupa_tb(node);
		lock_break();
		kernel_panic_n(/* n_skip: */ 1,
		               "kffree(%p, %#x): Node at %p...%p wasn't created by kmalloc()\n"
		               "%[gen:c]",
		               ptr, flags, trace_node_umin(node), trace_node_umax(node),
		               &trace_node_print_traceback, node);
		return;
	}
	if unlikely(ptr != trace_node_uaddr(node) + CONFIG_KERNEL_MALL_HEAD_SIZE) {
		tm_nodes_insert(node);
		node = trace_node_dupa_tb(node);
		lock_break();
		kernel_panic_n(/* n_skip: */ 1,
		               "kffree(%p, %#x): Passed pointer does not match "
		               "start of containing node %p...%p (%p...%p)\n"
		               "%[gen:c]",
		               ptr, flags,
		               trace_node_umin(node) + CONFIG_KERNEL_MALL_HEAD_SIZE,
		               trace_node_umax(node) - CONFIG_KERNEL_MALL_TAIL_SIZE,
		               trace_node_umin(node), trace_node_umax(node),
		               &trace_node_print_traceback, node);
		return;
	}

	/* Validate  the padding for  a node before  freeing it, thus ensuring
	 * that the user hasn't done anything to corrupt the heap block during
	 * the block's life-time. */
#ifdef HAVE_kmalloc_validate_node
	if (!kmalloc_validate_node(1, node)) {
		tm_nodes_insert(node);
		lock_break();
		return;
	}
#endif /* HAVE_kmalloc_validate_node */
	lock_release();

	/* All right! everything checks out, so we can actually move on to
	 * freeing the associated  node, as well  as the user-data  block. */
	user_area_ptr = trace_node_uaddr(node);
	user_area_siz = trace_node_usize(node);

	/* Load heap-flag properties from the node itself. */
	flags = (flags & ~__GFP_HEAPMASK) | (node->tn_flags & __GFP_HEAPMASK);
	assert(user_area_siz >=
	       MAX(HEAP_MINSIZE, CONFIG_KERNEL_MALL_HEAD_SIZE +
	                         CONFIG_KERNEL_MALL_TAIL_SIZE));

	/* When freeing zero-initialized  memory,
	 * clean up the head & tail blocks first! */
	if (flags & GFP_CALLOC) {
		bzero(user_area_ptr, CONFIG_KERNEL_MALL_HEAD_SIZE);
		bzero((byte_t *)user_area_ptr +
		      (user_area_siz - CONFIG_KERNEL_MALL_TAIL_SIZE),
		      CONFIG_KERNEL_MALL_TAIL_SIZE);
	}

	/* Finally, free the actual payload */
	heap_free_untraced(&kernel_heaps[flags & __GFP_HEAPMASK],
	                   user_area_ptr, user_area_siz, flags);
	trace_node_free(node);
}

PUBLIC NOBLOCK ATTR_NOINLINE void
NOTHROW(KCALL kfree)(VIRT void *ptr) {
	void *user_area_ptr;
	size_t user_area_siz;
	struct trace_node *node;
	gfp_t flags;
	if (!ptr)
		return; /* Ignore NULL-pointers. */
#ifdef CONFIG_HAVE_KERNEL_SLAB_ALLOCATORS
	if (KERNEL_SLAB_CHECKPTR(ptr)) {
		slab_free(ptr);
		return;
	}
#endif /* CONFIG_HAVE_KERNEL_SLAB_ALLOCATORS */
	lock_acquire();
	node = tm_nodes_remove(ptr);
	if unlikely(!node) {
		lock_break();
		kernel_panic_n(/* n_skip: */ 1,
		               "kfree(%p): No node at this address",
		               ptr);
		return;
	}
	if unlikely(node->tn_kind != TRACE_NODE_KIND_MALL) {
		tm_nodes_insert(node);
		node = trace_node_dupa_tb(node);
		lock_break();
		kernel_panic_n(/* n_skip: */ 1,
		               "kfree(%p): Node at %p...%p wasn't created by kmalloc()\n"
		               "%[gen:c]",
		               ptr, trace_node_umin(node), trace_node_umax(node),
		               &trace_node_print_traceback, node);
		return;
	}
	if unlikely(ptr != trace_node_uaddr(node) + CONFIG_KERNEL_MALL_HEAD_SIZE) {
		tm_nodes_insert(node);
		node = trace_node_dupa_tb(node);
		lock_break();
		kernel_panic_n(/* n_skip: */ 1,
		               "kfree(%p): Passed pointer does not match "
		               "start of containing node %p...%p (%p...%p)\n"
		               "%[gen:c]",
		               ptr,
		               trace_node_umin(node) + CONFIG_KERNEL_MALL_HEAD_SIZE,
		               trace_node_umax(node) - CONFIG_KERNEL_MALL_TAIL_SIZE,
		               trace_node_umin(node), trace_node_umax(node),
		               &trace_node_print_traceback, node);
		return;
	}

	/* Validate  the padding for  a node before  freeing it, thus ensuring
	 * that the user hasn't done anything to corrupt the heap block during
	 * the block's life-time. */
#ifdef HAVE_kmalloc_validate_node
	if unlikely(!kmalloc_validate_node(1, node)) {
		tm_nodes_insert(node);
		lock_break();
		return;
	}
#endif /* HAVE_kmalloc_validate_node */
	lock_release();

	/* All right! everything checks out, so we can actually move on to
	 * freeing the associated  node, as well  as the user-data  block. */
	user_area_ptr = trace_node_uaddr(node);
	user_area_siz = trace_node_usize(node);

	/* Load heap-flag properties from the node itself. */
	flags = node->tn_flags & __GFP_HEAPMASK;
	assert(user_area_siz >=
	       MAX(HEAP_MINSIZE, CONFIG_KERNEL_MALL_HEAD_SIZE +
	                         CONFIG_KERNEL_MALL_TAIL_SIZE));

	/* Finally, free the actual payload */
	heap_free_untraced(&kernel_heaps[flags & __GFP_HEAPMASK],
	                   user_area_ptr, user_area_siz, flags);
	trace_node_free(node);
}

#ifdef CONFIG_HAVE_KERNEL_DEBUGGER
DBG_COMMAND(kmtrace,
            "kmtrace ptr...\n"
            "\tPrint tracebacks for where ptr was allocated from\n",
            argc, argv) {
	for (; argc >= 2; --argc, ++argv) {
		uintptr_t addr, hi;
		if (sscanf(argv[1], DBGSTR("%" SCNUPTR "-%" SCNUPTR), &addr, &hi) == 2) {
			if (addr <= hi) {
				trace_node_tree_minmax_t mima;
				tm_nodes_minmaxlocate(addr, hi, &mima);
				if (mima.mm_min) {
					for (;;) {
						dbg_printf(DBGSTR("kmalloc %p:\n"), trace_node_umin(mima.mm_min));
						if (TRACE_NODE_KIND_HAS_TRACEBACK(mima.mm_min->tn_kind))
							trace_node_print_traceback(mima.mm_min, &dbg_printer, NULL);
						kmalloc_printtrace((void *)addr, &dbg_printer, NULL);
						if (mima.mm_min == mima.mm_max)
							break;
						mima.mm_min = tm_nodes_nextnode(mima.mm_min);
					}
				}
			}
		} else {
			if (!dbg_evaladdr(argv[1], &addr))
				return DBG_STATUS_INVALID_ARGUMENTS;
			dbg_printf(DBGSTR("kmalloc %p:\n"), addr);
			kmalloc_printtrace((void *)addr, &dbg_printer, NULL);
		}
	}
	return 0;
}
#endif /* CONFIG_HAVE_KERNEL_DEBUGGER */


DECL_END

#ifndef __INTELLISENSE__
#define DEFINE_X_except
#include "trace-malloc-heap.c.inl"
#define DEFINE_X_noexcept
#include "trace-malloc-heap.c.inl"
#endif /* !__INTELLISENSE__ */

DECL_BEGIN

#ifdef CONFIG_HAVE_KERNEL_SLAB_ALLOCATORS
/* Must also override the default `kmalloc_noslab()' with our trace-enabled variant. */
DEFINE_PUBLIC_ALIAS(kmalloc_noslab, kmalloc);
DEFINE_PUBLIC_ALIAS(kmalloc_noslab_nx, kmalloc_nx);
#endif /* CONFIG_HAVE_KERNEL_SLAB_ALLOCATORS */

DECL_END

#endif /* CONFIG_HAVE_KERNEL_TRACE_MALLOC */

#endif /* !GUARD_KERNEL_SRC_MEMORY_TRACE_MALLOC_C */
