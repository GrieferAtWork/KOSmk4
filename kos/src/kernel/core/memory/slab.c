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
#ifndef GUARD_KERNEL_SRC_MEMORY_SLAB_C
#define GUARD_KERNEL_SRC_MEMORY_SLAB_C 1
#define _KOS_SOURCE 1
#define __OMIT_SLAB_MALLOC_CONSTANT_P_WRAPPERS 1

#include <kernel/compiler.h>

#include <kernel/driver.h>
#include <kernel/except.h>
#include <kernel/heap.h>
#include <kernel/malloc.h>
#include <kernel/panic.h>
#include <kernel/printk.h>
#include <kernel/slab.h>
#include <kernel/types.h>

#include <hybrid/align.h>
#include <hybrid/atomic.h>
#include <hybrid/overflow.h>
#include <hybrid/sync/atomic-rwlock.h>

#include <assert.h>
#include <stdint.h>
#include <string.h>

#if defined(CONFIG_USE_SLAB_ALLOCATORS) || defined(__DEEMON__)

#include "corebase.h"

DECL_BEGIN

/* TODO: debug_malloc integration! */

struct slab_pool {
	/* Descriptor for the pool of free slab pages. */
	struct atomic_rwlock sp_lock;  /* Lock for free pages. */
	struct slab         *sp_free;  /* [0..1][lock(sp_lock)] Chain of fully free slab pages. */
	size_t               sp_count; /* [lock(sp_lock)] Current amount of free pool pages */
	size_t               sp_limit; /* [lock(sp_lock)] Max amount of free pool pages, before further pages must be freed. */
	WEAK struct slab    *sp_pend;  /* Chain of pages pending to-be freed. */
};


#define SLAB_POOL_DEFAULT_LIMIT 3

PRIVATE struct slab_pool slab_freepool[2] = {
	{   /* SLAB_FNORMAL / GFP_NORMAL */
		.sp_lock  = ATOMIC_RWLOCK_INIT,
		.sp_free  = NULL,
		.sp_count = 0,
		.sp_limit = SLAB_POOL_DEFAULT_LIMIT,
		.sp_pend  = NULL
	}, { /* SLAB_FLOCKED / GFP_LOCKED */
		.sp_lock  = ATOMIC_RWLOCK_INIT,
		.sp_free  = NULL,
		.sp_count = 0,
		.sp_limit = SLAB_POOL_DEFAULT_LIMIT,
		.sp_pend  = NULL
	}
};


LOCAL NOBLOCK void
NOTHROW(KCALL pool_do_free)(struct slab_pool *__restrict self,
                            struct slab *__restrict page) {
	if (self->sp_count < self->sp_limit) {
		page->s_next  = self->sp_free;
		self->sp_free = page;
		++self->sp_count;
		return;
	}
	/* Actually release the page as kernel-RAM. */
	vm_unmap_kernel_ram(VM_ADDR2PAGE((vm_virt_t)page), 1, false);
}

PRIVATE NOBLOCK void
NOTHROW(KCALL pool_clear_pending)(struct slab_pool *__restrict self) {
	struct slab *pend, *next;
	pend = ATOMIC_XCH(self->sp_pend, NULL);
	while (pend) {
		next = pend->s_next;
		pool_do_free(self, pend);
		pend = next;
	}
}

PRIVATE NOBLOCK bool
NOTHROW(KCALL pool_lock_trywrite)(struct slab_pool *__restrict self) {
	if (!sync_trywrite(&self->sp_lock))
		return false;
	pool_clear_pending(self);
	return true;
}

PRIVATE bool
NOTHROW(KCALL pool_lock_write)(struct slab_pool *__restrict self) {
	if (!sync_write_nx(&self->sp_lock))
		return false;
	pool_clear_pending(self);
	return true;
}

PRIVATE NOBLOCK void
NOTHROW(KCALL pool_lock_endwrite)(struct slab_pool *__restrict self) {
again:
	sync_endwrite(&self->sp_lock);
	if (ATOMIC_READ(self->sp_pend)) {
		if (sync_trywrite(&self->sp_lock)) {
			pool_clear_pending(self);
			goto again;
		}
	}
}


PRIVATE NOBLOCK void
NOTHROW(KCALL slab_freepage)(struct slab *__restrict self) {
	struct slab_pool *pool;
#if SLAB_FLOCKED == 1
	pool = &slab_freepool[self->s_flags & SLAB_FLOCKED];
#else /* SLAB_FLOCKED == 1 */
	pool = &slab_freepool[(self->s_flags & SLAB_FLOCKED) ? 1 : 0];
#endif /* SLAB_FLOCKED != 1 */
	if (pool_lock_trywrite(pool)) {
		pool_do_free(pool, self);
		pool_lock_endwrite(pool);
	} else {
		struct slab *next;
		do {
			next = ATOMIC_READ(pool->sp_pend);
			self->s_next = next;
		} while (!ATOMIC_CMPXCH_WEAK(pool->sp_pend, next, self));
		if (pool_lock_trywrite(pool))
			pool_lock_endwrite(pool);
	}
}


#define CORE_ALLOC_FLAGS                                                        \
	(GFP_LOCKED |                                                               \
	 GFP_PREFLT |                                                               \
	 GFP_VCBASE | /* Instruct the heap to only consider allocating from VCbase, \
	               * thus preventing an infinite loop. */                       \
	 GFP_NOOVER   /* Don't overallocate to prevent infinite recursion!          \
	               * -> This flag guaranties that upon recursion, at most 1     \
	               *    page will get allocated, in which case the              \
	               *   `block0_size >= num_pages' check above will be           \
	               *   `1 >= 1', meaning we'll never get here! */               \
	)


/* [lock(vm_kernel)]
 * The pointer to either the lowest (CONFIG_SLAB_GROWS_DOWNWARDS), or
 * one past the greatest (CONFIG_SLAB_GROWS_UPWARDS) address that was
 * ever allocated for slab memory.
 * Since slab allocations don't carry any meta-data, they are actually
 * identified by their address, meaning that we need to keep track of
 * the max range of pointers associated with the slab allocator.
 * NOTE: This value starts out as `KERNEL_SLAB_INITIAL', and is only
 *       ever extended in one direction, based on the slab growth
 *       direction. */
PUBLIC uintptr_t kernel_slab_break = KERNEL_SLAB_INITIAL;

struct slab_pending_free {
	struct slab_pending_free *spf_next; /* [0..1] Next pending free. */
};

struct slab_descriptor {
	/* Data descriptor for some fixed-length-segment slab. */
	struct atomic_rwlock           sd_lock; /* Lock for this slab descriptor. */
	struct slab                   *sd_free; /* [0..1][lock(sd_lock)] Chain of partially free slab pages. */
	WEAK struct slab_pending_free *sd_pend; /* [0..1] Chain of pending free segments. */
};

PRIVATE VIRT struct slab *
NOTHROW(KCALL slab_alloc_page)(gfp_t flags) {
	struct slab_pool *pool;
	struct slab *result;
#if GFP_LOCKED == 1
	pool = &slab_freepool[flags & GFP_LOCKED];
#else /* GFP_LOCKED == 1 */
	pool = &slab_freepool[(flags & GFP_LOCKED) ? 1 : 0];
#endif /* GFP_LOCKED != 1 */
again:
	if unlikely(!pool_lock_trywrite(pool)) {
		if (flags & GFP_ATOMIC)
			goto err;
		if unlikely(!pool_lock_write(pool))
			goto err;
	}
	assert((pool->sp_free != NULL) ==
	       (pool->sp_count != 0));
	result = pool->sp_free;
	if (result) {
		/* Re-use an already allocated slab page. */
		pool->sp_free = result->s_next;
		--pool->sp_count;
		pool_lock_endwrite(pool);
		/* Pre-initialize the resulting slab page. */
#ifdef CONFIG_DEBUG_HEAP
#if GFP_CALLOC == SLAB_FCALLOC
		if ((flags & GFP_CALLOC) != (result->s_flags & SLAB_FCALLOC))
#else /* GFP_CALLOC == SLAB_FCALLOC */
		if (!!(flags & GFP_CALLOC) != !!(result->s_flags & SLAB_FCALLOC))
#endif /* GFP_CALLOC != SLAB_FCALLOC */
		{
			if (flags & GFP_CALLOC) {
				memset(result, 0, PAGESIZE);
			} else {
				mempatl(result, DEBUGHEAP_NO_MANS_LAND, PAGESIZE);
			}
		}
#else /* CONFIG_DEBUG_HEAP */
		if ((flags & GFP_CALLOC) && !(result->s_flags & SLAB_FCALLOC))
			memset(result, 0, PAGESIZE);
#endif /* !CONFIG_DEBUG_HEAP */
		return result;
	}
	pool_lock_endwrite(pool);
	COMPILER_READ_BARRIER();
	if unlikely(ATOMIC_READ(pool->sp_count) != 0)
		goto again;
	/* Must allocate a new slab page. */
	{
		struct vm_corepair_ptr corepair;
		if (flags & GFP_VCBASE) {
			corepair = vm_corepair_alloc(flags, true);
			if unlikely(!corepair.cp_node)
				goto err;
		} else {
			corepair.cp_node = (VIRT struct vm_node *)kmalloc_nx(sizeof(struct vm_node),
			                                                     CORE_ALLOC_FLAGS | GFP_CALLOC |
			                                                     (flags & GFP_INHERIT));
			if unlikely(!corepair.cp_node)
				goto err;
			corepair.cp_part = (VIRT struct vm_datapart *)kmalloc_nx(sizeof(struct vm_datapart),
			                                                         CORE_ALLOC_FLAGS | GFP_CALLOC |
			                                                         (flags & GFP_INHERIT));
			if unlikely(!corepair.cp_part) {
				kffree(corepair.cp_node, GFP_CALLOC);
				goto err;
			}
		}
		/* Setup the corepair. */
		corepair.cp_node->vn_vm    = &vm_kernel;
		corepair.cp_part->dp_block = flags & GFP_CALLOC
		                             ? &vm_datablock_anonymous_zero
#ifdef CONFIG_DEBUG_HEAP
		                             : &vm_datablock_debugheap
#else /* CONFIG_DEBUG_HEAP */
		                             : &vm_datablock_anonymous
#endif /* !CONFIG_DEBUG_HEAP */
		                             ;
		incref(corepair.cp_part->dp_block);
		corepair.cp_node->vn_block = incref(corepair.cp_part->dp_block);
		corepair.cp_node->vn_prot  = VM_PROT_READ | VM_PROT_WRITE | VM_PROT_SHARED;
		corepair.cp_node->vn_flags |= VM_NODE_FLAG_PREPARED;
		corepair.cp_node->vn_part          = corepair.cp_part;
		corepair.cp_node->vn_link.ln_pself = &LLIST_HEAD(corepair.cp_part->dp_srefs);
		corepair.cp_part->dp_srefs         = corepair.cp_node;
		corepair.cp_part->dp_state = flags & GFP_LOCKED
		                             ? VM_DATAPART_STATE_LOCKED
		                             : VM_DATAPART_STATE_INCORE;
		corepair.cp_part->dp_pprop                      = (uintptr_t)-1;
		corepair.cp_part->dp_ramdata.rd_blockv          = &corepair.cp_part->dp_ramdata.rd_block0;
		corepair.cp_part->dp_ramdata.rd_block0.rb_size  = 1;
		corepair.cp_part->dp_ramdata.rd_block0.rb_start = page_malloc(1);
		if unlikely(corepair.cp_part->dp_ramdata.rd_block0.rb_start == PAGEPTR_INVALID)
			goto err_corepair;
		{
			vm_vpage_t next_slab_page;
			vm_vpage_t slab_end_page;
again_lock_vm:
			if unlikely(!vm_kernel_treelock_writef_nx(flags))
				goto err_corepair_content;
#define HINT_ADDR(x, y) x
#define HINT_MODE(x, y) y
#define HINT_GETADDR(x) HINT_ADDR x
#define HINT_GETMODE(x) HINT_MODE x
			slab_end_page  = VM_ADDR2PAGE((vm_virt_t)kernel_slab_break);
			next_slab_page = vm_getfree(&vm_kernel,
			                            (vm_vpage_t)HINT_GETADDR(KERNEL_VMHINT_SLAB), 1, 1,
			                            HINT_GETMODE(KERNEL_VMHINT_SLAB));
#ifdef CONFIG_SLAB_GROWS_DOWNWARDS
			if (next_slab_page == VM_GETFREE_ERROR ||
			    next_slab_page < slab_end_page - 1)
#else /* CONFIG_SLAB_GROWS_DOWNWARDS */
			if (next_slab_page == VM_GETFREE_ERROR ||
			    next_slab_page > slab_end_page)
#endif /* !CONFIG_SLAB_GROWS_DOWNWARDS */
			{
				uintptr_t version;
				vm_kernel_treelock_endwrite();
#ifndef __OPTIMIZE_SIZE__
				if (system_clearcaches())
					goto again_lock_vm;
#endif /* !__OPTIMIZE_SIZE__ */
				version = 0;
again_next_slab_page_tryhard:
				if unlikely(!vm_kernel_treelock_writef_nx(flags))
					goto err_corepair_content;
				next_slab_page = vm_getfree(&vm_kernel,
				                            (vm_vpage_t)HINT_GETADDR(KERNEL_VMHINT_SLAB), 1, 1,
				                            HINT_GETMODE(KERNEL_VMHINT_SLAB));
				vm_kernel_treelock_endwrite();
#ifdef CONFIG_SLAB_GROWS_DOWNWARDS
				if (next_slab_page != VM_GETFREE_ERROR &&
				    next_slab_page >= slab_end_page - 1)
					goto again_lock_vm;
#else /* CONFIG_SLAB_GROWS_DOWNWARDS */
				if (next_slab_page != VM_GETFREE_ERROR &&
				    next_slab_page <= slab_end_page)
					goto again_lock_vm;
#endif /* !CONFIG_SLAB_GROWS_DOWNWARDS */
				if (system_clearcaches_s(&version))
					goto again_next_slab_page_tryhard;
				goto err_corepair_content;
			}
			/* Now to map the new page. */
#ifdef CONFIG_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE
			if unlikely(!pagedir_prepare_mapone(next_slab_page)) {
				vm_kernel_treelock_endwrite();
				goto err_corepair_content;
			}
#endif /* CONFIG_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE */
			/* Map all pre-allocated pages. */
			pagedir_mapone(next_slab_page,
			               corepair.cp_part->dp_ramdata.rd_block0.rb_start,
			               PAGEDIR_MAP_FWRITE | PAGEDIR_MAP_FREAD);
			if (flags & GFP_CALLOC) {
				/* Write zeros to all random-content pages. */
				if (!page_iszero(corepair.cp_part->dp_ramdata.rd_block0.rb_start)) {
					memset((void *)VM_PAGE2ADDR(next_slab_page), 0, PAGESIZE);
#ifdef CONFIG_HAVE_PAGEDIR_CHANGED
					pagedir_unsetchanged(next_slab_page);
#endif /* CONFIG_HAVE_PAGEDIR_CHANGED */
				}
			}
#ifdef CONFIG_DEBUG_HEAP
			else {
				/* Fill memory using the no-mans-land pattern. */
				mempatl((void *)VM_PAGE2ADDR(next_slab_page),
				        DEBUGHEAP_NO_MANS_LAND,
				        PAGESIZE);
#ifdef CONFIG_HAVE_PAGEDIR_CHANGED
				pagedir_unsetchanged(next_slab_page);
#endif /* CONFIG_HAVE_PAGEDIR_CHANGED */
			}
#endif /* CONFIG_DEBUG_HEAP */
			/* Set the returned slab */
			result = (struct slab *)VM_PAGE2ADDR(next_slab_page);
			/* Update the slab breaking point. */
#ifdef CONFIG_SLAB_GROWS_DOWNWARDS
			kernel_slab_break = (uintptr_t)result;
#else /* CONFIG_SLAB_GROWS_DOWNWARDS */
			kernel_slab_break = (uintptr_t)result + PAGESIZE;
#endif /* !CONFIG_SLAB_GROWS_DOWNWARDS */
			/* Insert the node into the kernel VM. */
			corepair.cp_node->vn_node.a_vmin = next_slab_page;
			corepair.cp_node->vn_node.a_vmax = next_slab_page;
			vm_node_insert(corepair.cp_node);
			vm_kernel_treelock_endwrite();
			return result;
		}
err_corepair_content:
		page_free(corepair.cp_part->dp_ramdata.rd_block0.rb_start, 1);
err_corepair:
		decref(corepair.cp_node->vn_block);
		decref(corepair.cp_part->dp_block);
		vm_node_free(corepair.cp_node);
		vm_datapart_free(corepair.cp_part);
	}
err:
	return NULL;
}

DECL_END


#undef SEGMENT_OFFSET
#undef SEGMENT_COUNT
#undef SIZEOF_BITSET
#undef LENGTHOF_BITSET

#ifndef __INTELLISENSE__
/*[[[deemon
local is_first = true;
local limit = 16;
for (local align: [4,8,16]) {
	print is_first ? "#if" : "#elif","HEAP_ALIGNMENT ==",align;
	is_first = false;
	print "#if KERNEL_SLAB_COUNT >=",limit + 1;
	print "#error Extend me";
	print "#endif";
	for (local x: [1:limit,-1]) {
		print "#if KERNEL_SLAB_COUNT >=",x;
		print "#define SEGMENT_SIZE",x * align;
		print "#include \"slab-impl.c.inl\"";
		if (x > 1)
			print "#define NEXT_SEGMENT_SIZE",x * align;
		print "#endif";
	}
}
print "#endif";
]]]*/
#if HEAP_ALIGNMENT == 4
#if KERNEL_SLAB_COUNT >= 17
#error Extend me
#endif
#if KERNEL_SLAB_COUNT >= 15
#define SEGMENT_SIZE 60
#include "slab-impl.c.inl"
#define NEXT_SEGMENT_SIZE 60
#endif
#if KERNEL_SLAB_COUNT >= 14
#define SEGMENT_SIZE 56
#include "slab-impl.c.inl"
#define NEXT_SEGMENT_SIZE 56
#endif
#if KERNEL_SLAB_COUNT >= 13
#define SEGMENT_SIZE 52
#include "slab-impl.c.inl"
#define NEXT_SEGMENT_SIZE 52
#endif
#if KERNEL_SLAB_COUNT >= 12
#define SEGMENT_SIZE 48
#include "slab-impl.c.inl"
#define NEXT_SEGMENT_SIZE 48
#endif
#if KERNEL_SLAB_COUNT >= 11
#define SEGMENT_SIZE 44
#include "slab-impl.c.inl"
#define NEXT_SEGMENT_SIZE 44
#endif
#if KERNEL_SLAB_COUNT >= 10
#define SEGMENT_SIZE 40
#include "slab-impl.c.inl"
#define NEXT_SEGMENT_SIZE 40
#endif
#if KERNEL_SLAB_COUNT >= 9
#define SEGMENT_SIZE 36
#include "slab-impl.c.inl"
#define NEXT_SEGMENT_SIZE 36
#endif
#if KERNEL_SLAB_COUNT >= 8
#define SEGMENT_SIZE 32
#include "slab-impl.c.inl"
#define NEXT_SEGMENT_SIZE 32
#endif
#if KERNEL_SLAB_COUNT >= 7
#define SEGMENT_SIZE 28
#include "slab-impl.c.inl"
#define NEXT_SEGMENT_SIZE 28
#endif
#if KERNEL_SLAB_COUNT >= 6
#define SEGMENT_SIZE 24
#include "slab-impl.c.inl"
#define NEXT_SEGMENT_SIZE 24
#endif
#if KERNEL_SLAB_COUNT >= 5
#define SEGMENT_SIZE 20
#include "slab-impl.c.inl"
#define NEXT_SEGMENT_SIZE 20
#endif
#if KERNEL_SLAB_COUNT >= 4
#define SEGMENT_SIZE 16
#include "slab-impl.c.inl"
#define NEXT_SEGMENT_SIZE 16
#endif
#if KERNEL_SLAB_COUNT >= 3
#define SEGMENT_SIZE 12
#include "slab-impl.c.inl"
#define NEXT_SEGMENT_SIZE 12
#endif
#if KERNEL_SLAB_COUNT >= 2
#define SEGMENT_SIZE 8
#include "slab-impl.c.inl"
#define NEXT_SEGMENT_SIZE 8
#endif
#if KERNEL_SLAB_COUNT >= 1
#define SEGMENT_SIZE 4
#include "slab-impl.c.inl"
#endif
#elif HEAP_ALIGNMENT == 8
#if KERNEL_SLAB_COUNT >= 17
#error Extend me
#endif
#if KERNEL_SLAB_COUNT >= 15
#define SEGMENT_SIZE 120
#include "slab-impl.c.inl"
#define NEXT_SEGMENT_SIZE 120
#endif
#if KERNEL_SLAB_COUNT >= 14
#define SEGMENT_SIZE 112
#include "slab-impl.c.inl"
#define NEXT_SEGMENT_SIZE 112
#endif
#if KERNEL_SLAB_COUNT >= 13
#define SEGMENT_SIZE 104
#include "slab-impl.c.inl"
#define NEXT_SEGMENT_SIZE 104
#endif
#if KERNEL_SLAB_COUNT >= 12
#define SEGMENT_SIZE 96
#include "slab-impl.c.inl"
#define NEXT_SEGMENT_SIZE 96
#endif
#if KERNEL_SLAB_COUNT >= 11
#define SEGMENT_SIZE 88
#include "slab-impl.c.inl"
#define NEXT_SEGMENT_SIZE 88
#endif
#if KERNEL_SLAB_COUNT >= 10
#define SEGMENT_SIZE 80
#include "slab-impl.c.inl"
#define NEXT_SEGMENT_SIZE 80
#endif
#if KERNEL_SLAB_COUNT >= 9
#define SEGMENT_SIZE 72
#include "slab-impl.c.inl"
#define NEXT_SEGMENT_SIZE 72
#endif
#if KERNEL_SLAB_COUNT >= 8
#define SEGMENT_SIZE 64
#include "slab-impl.c.inl"
#define NEXT_SEGMENT_SIZE 64
#endif
#if KERNEL_SLAB_COUNT >= 7
#define SEGMENT_SIZE 56
#include "slab-impl.c.inl"
#define NEXT_SEGMENT_SIZE 56
#endif
#if KERNEL_SLAB_COUNT >= 6
#define SEGMENT_SIZE 48
#include "slab-impl.c.inl"
#define NEXT_SEGMENT_SIZE 48
#endif
#if KERNEL_SLAB_COUNT >= 5
#define SEGMENT_SIZE 40
#include "slab-impl.c.inl"
#define NEXT_SEGMENT_SIZE 40
#endif
#if KERNEL_SLAB_COUNT >= 4
#define SEGMENT_SIZE 32
#include "slab-impl.c.inl"
#define NEXT_SEGMENT_SIZE 32
#endif
#if KERNEL_SLAB_COUNT >= 3
#define SEGMENT_SIZE 24
#include "slab-impl.c.inl"
#define NEXT_SEGMENT_SIZE 24
#endif
#if KERNEL_SLAB_COUNT >= 2
#define SEGMENT_SIZE 16
#include "slab-impl.c.inl"
#define NEXT_SEGMENT_SIZE 16
#endif
#if KERNEL_SLAB_COUNT >= 1
#define SEGMENT_SIZE 8
#include "slab-impl.c.inl"
#endif
#elif HEAP_ALIGNMENT == 16
#if KERNEL_SLAB_COUNT >= 17
#error Extend me
#endif
#if KERNEL_SLAB_COUNT >= 15
#define SEGMENT_SIZE 240
#include "slab-impl.c.inl"
#define NEXT_SEGMENT_SIZE 240
#endif
#if KERNEL_SLAB_COUNT >= 14
#define SEGMENT_SIZE 224
#include "slab-impl.c.inl"
#define NEXT_SEGMENT_SIZE 224
#endif
#if KERNEL_SLAB_COUNT >= 13
#define SEGMENT_SIZE 208
#include "slab-impl.c.inl"
#define NEXT_SEGMENT_SIZE 208
#endif
#if KERNEL_SLAB_COUNT >= 12
#define SEGMENT_SIZE 192
#include "slab-impl.c.inl"
#define NEXT_SEGMENT_SIZE 192
#endif
#if KERNEL_SLAB_COUNT >= 11
#define SEGMENT_SIZE 176
#include "slab-impl.c.inl"
#define NEXT_SEGMENT_SIZE 176
#endif
#if KERNEL_SLAB_COUNT >= 10
#define SEGMENT_SIZE 160
#include "slab-impl.c.inl"
#define NEXT_SEGMENT_SIZE 160
#endif
#if KERNEL_SLAB_COUNT >= 9
#define SEGMENT_SIZE 144
#include "slab-impl.c.inl"
#define NEXT_SEGMENT_SIZE 144
#endif
#if KERNEL_SLAB_COUNT >= 8
#define SEGMENT_SIZE 128
#include "slab-impl.c.inl"
#define NEXT_SEGMENT_SIZE 128
#endif
#if KERNEL_SLAB_COUNT >= 7
#define SEGMENT_SIZE 112
#include "slab-impl.c.inl"
#define NEXT_SEGMENT_SIZE 112
#endif
#if KERNEL_SLAB_COUNT >= 6
#define SEGMENT_SIZE 96
#include "slab-impl.c.inl"
#define NEXT_SEGMENT_SIZE 96
#endif
#if KERNEL_SLAB_COUNT >= 5
#define SEGMENT_SIZE 80
#include "slab-impl.c.inl"
#define NEXT_SEGMENT_SIZE 80
#endif
#if KERNEL_SLAB_COUNT >= 4
#define SEGMENT_SIZE 64
#include "slab-impl.c.inl"
#define NEXT_SEGMENT_SIZE 64
#endif
#if KERNEL_SLAB_COUNT >= 3
#define SEGMENT_SIZE 48
#include "slab-impl.c.inl"
#define NEXT_SEGMENT_SIZE 48
#endif
#if KERNEL_SLAB_COUNT >= 2
#define SEGMENT_SIZE 32
#include "slab-impl.c.inl"
#define NEXT_SEGMENT_SIZE 32
#endif
#if KERNEL_SLAB_COUNT >= 1
#define SEGMENT_SIZE 16
#include "slab-impl.c.inl"
#endif
#endif
//[[[end]]]
#endif /* !__INTELLISENSE__ */

DECL_BEGIN

PUBLIC NONNULL((1)) NOBLOCK void
NOTHROW(KCALL slab_free)(void *__restrict ptr) {
	struct slab *self;
	assert(KERNEL_SLAB_CHECKPTR(ptr));
	self = SLAB_GET(ptr);
	switch (self->s_size) {
#ifndef __INTELLISENSE__
#define CASE_SLAB_FREE(sz) \
	case sz:                                     \
		slab_freeptr##sz(self, ptr, GFP_NORMAL); \
		break;
	SLAB_FOREACH_SIZE(CASE_SLAB_FREE)
#undef CASE_SLAB_FREE
#endif /* !__INTELLISENSE__ */
	default:
#ifndef NDEBUG
		kernel_panic("Corrupted SLAB page at %p has an invalid size of %I8u",
		             self, self->s_size);
#else /* !NDEBUG */
		__builtin_unreachable();
#endif /* NDEBUG */
	}
}


PUBLIC NONNULL((1)) NOBLOCK void
NOTHROW(KCALL slab_ffree)(void *__restrict ptr, gfp_t flags) {
	struct slab *self;
	assert(KERNEL_SLAB_CHECKPTR(ptr));
	self = SLAB_GET(ptr);
	switch (self->s_size) {
#ifndef __INTELLISENSE__
#define CASE_SLAB_FREE(sz) \
	case sz:                                \
		slab_freeptr##sz(self, ptr, flags); \
		break;
	SLAB_FOREACH_SIZE(CASE_SLAB_FREE)
#undef CASE_SLAB_FREE
#endif /* !__INTELLISENSE__ */
	default:
#ifndef NDEBUG
		kernel_panic("Corrupted SLAB page at %p has an invalid size of %I8u",
		             self, self->s_size);
#else /* !NDEBUG */
		__builtin_unreachable();
#endif /* NDEBUG */
	}
}


PUBLIC NOBLOCK ATTR_MALLOC WUNUSED VIRT void *
NOTHROW(KCALL __os_slab_malloc)(size_t num_bytes, gfp_t flags) {
#ifndef __INTELLISENSE__
#define CASE_SLAB_MALLOC(sz) \
	if (num_bytes <= sz)     \
		return slab_malloc##sz(flags);
	SLAB_FOREACH_SIZE(CASE_SLAB_MALLOC)
#undef CASE_SLAB_MALLOC
#endif /* !__INTELLISENSE__ */
#ifndef NDEBUG
	kernel_panic("Invalid slab size %Iu", num_bytes);
#else /* !NDEBUG */
	__builtin_unreachable();
#endif /* NDEBUG */
}

PUBLIC ATTR_MALLOC WUNUSED ATTR_RETNONNULL VIRT void *KCALL
__os_slab_kmalloc(size_t num_bytes, gfp_t flags) {
#ifndef __INTELLISENSE__
#define CASE_SLAB_MALLOC(sz) \
	if (num_bytes <= sz)     \
		return slab_kmalloc##sz(flags);
	SLAB_FOREACH_SIZE(CASE_SLAB_MALLOC)
#undef CASE_SLAB_MALLOC
#endif /* !__INTELLISENSE__ */
#ifndef NDEBUG
	kernel_panic("Invalid slab size %Iu", num_bytes);
#else /* !NDEBUG */
	__builtin_unreachable();
#endif /* NDEBUG */
}

PUBLIC ATTR_MALLOC WUNUSED VIRT void *
NOTHROW(KCALL __os_slab_kmalloc_nx)(size_t num_bytes, gfp_t flags) {
#ifndef __INTELLISENSE__
#define CASE_SLAB_MALLOC(sz) \
	if (num_bytes <= sz)     \
		return slab_kmalloc_nx##sz(flags);
	SLAB_FOREACH_SIZE(CASE_SLAB_MALLOC)
#undef CASE_SLAB_MALLOC
#endif /* !__INTELLISENSE__ */
#ifndef NDEBUG
	kernel_panic("Invalid slab size %Iu", num_bytes);
#else /* !NDEBUG */
	__builtin_unreachable();
#endif /* NDEBUG */
}


DECL_END

#endif /* CONFIG_USE_SLAB_ALLOCATORS */

#endif /* !GUARD_KERNEL_SRC_MEMORY_SLAB_C */
