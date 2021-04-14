/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_SRC_MEMORY_SLAB_C
#define GUARD_KERNEL_SRC_MEMORY_SLAB_C 1
#define _KOS_SOURCE 1
#define __OMIT_SLAB_MALLOC_CONSTANT_P_WRAPPERS 1

#include <kernel/compiler.h>

#include <kernel/malloc-defs.h>
#if defined(CONFIG_USE_SLAB_ALLOCATORS) || defined(__DEEMON__)

#include <kernel/except.h>
#include <kernel/heap.h>
#include <kernel/malloc.h>
#include <kernel/mman.h>
#include <kernel/mman/cache.h>
#include <kernel/mman/kram.h>
#include <kernel/mman/unmapped.h>
#include <kernel/panic.h>
#include <kernel/printk.h>
#include <kernel/slab.h>
#include <kernel/types.h>

#include <hybrid/align.h>
#include <hybrid/atomic.h>
#include <hybrid/overflow.h>
#include <hybrid/sync/atomic-lock.h>

#include <assert.h>
#include <inttypes.h>
#include <stdint.h>
#include <string.h>

DECL_BEGIN

struct slab_pool {
	/* Descriptor for the pool of free slab pages. */
	struct atomic_lock sp_lock;  /* Lock for free pages. */
	struct slab       *sp_free;  /* [0..1][lock(sp_lock)] Chain of fully free slab pages. */
	size_t             sp_count; /* [lock(sp_lock)] Current amount of free pool pages */
	size_t             sp_limit; /* [lock(sp_lock)] Max amount of free pool pages, before further pages must be freed. */
	WEAK struct slab  *sp_pend;  /* Chain of pages pending to-be freed. */
};


#ifndef SLAB_POOL_DEFAULT_LIMIT
#define SLAB_POOL_DEFAULT_LIMIT 3
#endif /* !SLAB_POOL_DEFAULT_LIMIT */


PRIVATE struct slab_pool slab_freepool[2] = {
	{   /* SLAB_FNORMAL / GFP_NORMAL */
		.sp_lock  = ATOMIC_LOCK_INIT,
		.sp_free  = NULL,
		.sp_count = 0,
		.sp_limit = SLAB_POOL_DEFAULT_LIMIT,
		.sp_pend  = NULL
	}, { /* SLAB_FLOCKED / GFP_LOCKED */
		.sp_lock  = ATOMIC_LOCK_INIT,
		.sp_free  = NULL,
		.sp_count = 0,
		.sp_limit = SLAB_POOL_DEFAULT_LIMIT,
		.sp_pend  = NULL
	}
};


LOCAL NOBLOCK NONNULL((1, 2)) void
NOTHROW(KCALL pool_do_free)(struct slab_pool *__restrict self,
                            struct slab *__restrict page) {
	if (self->sp_count < self->sp_limit) {
		page->s_next  = self->sp_free;
		self->sp_free = page;
		++self->sp_count;
		return;
	}
	/* Actually release the page as kernel-RAM. */
	mman_unmap_kram(page, PAGESIZE, GFP_NORMAL);
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL pool_clear_pending)(struct slab_pool *__restrict self) {
	struct slab *pend, *next;
	pend = ATOMIC_XCH(self->sp_pend, NULL);
	while (pend) {
		next = pend->s_next;
		pool_do_free(self, pend);
		pend = next;
	}
}

PRIVATE NOBLOCK NONNULL((1)) bool
NOTHROW(KCALL pool_lock_trywrite)(struct slab_pool *__restrict self) {
	if (!sync_trywrite(&self->sp_lock))
		return false;
	pool_clear_pending(self);
	return true;
}

PRIVATE NONNULL((1)) bool
NOTHROW(KCALL pool_lock_write)(struct slab_pool *__restrict self) {
	if (!sync_write_nx(&self->sp_lock))
		return false;
	pool_clear_pending(self);
	return true;
}

PRIVATE NOBLOCK NONNULL((1)) void
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


PRIVATE NOBLOCK NONNULL((1)) void
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
	 GFP_NOOVER   /* Don't overallocate to prevent infinite recursion! */       \
	)


/* [lock(mman_kernel.mm_lock)]
 * The pointer to either the lowest (CONFIG_SLAB_GROWS_DOWNWARDS), or
 * one past the greatest (CONFIG_SLAB_GROWS_UPWARDS) address that was
 * ever allocated for slab memory.
 * Since slab allocations don't carry any meta-data, they are actually
 * identified by their address, meaning that we need to keep track  of
 * the max range of pointers associated with the slab allocator.
 * NOTE: This value starts out as `KERNEL_SLAB_INITIAL', and is only
 *       ever extended in  one direction, based  on the slab  growth
 *       direction. */
PUBLIC void *kernel_slab_break = KERNEL_SLAB_INITIAL;

PRIVATE WUNUSED VIRT struct slab *
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
again_lock_mman_kernel:
	if (flags & GFP_ATOMIC) {
		if unlikely(!mman_lock_tryacquire(&mman_kernel))
			goto err;
	} else {
		if unlikely(!mman_lock_acquire_nx(&mman_kernel))
			goto err;
	}
	{
		void *next_slab_addr;
		void *slab_end_addr;
		slab_end_addr  = kernel_slab_break;
		/* Make sure that sufficient memory is available within the slab-region. */
		next_slab_addr = mman_findunmapped(&mman_kernel,
		                                   MHINT_GETADDR(KERNEL_MHINT_SLAB), PAGESIZE,
		                                   MHINT_GETMODE(KERNEL_MHINT_SLAB));
		mman_lock_release(&mman_kernel);
#ifdef CONFIG_SLAB_GROWS_DOWNWARDS
		if (next_slab_addr == MAP_FAILED || next_slab_addr < (byte_t *)slab_end_addr - PAGESIZE)
#else /* CONFIG_SLAB_GROWS_DOWNWARDS */
		if (next_slab_addr == MAP_FAILED || next_slab_addr > (byte_t *)slab_end_addr)
#endif /* !CONFIG_SLAB_GROWS_DOWNWARDS */
		{
			syscache_version_t version = SYSCACHE_VERSION_INIT;
			mman_lock_release(&mman_kernel);
again_next_slab_page_tryhard:
			if (flags & GFP_ATOMIC) {
				if unlikely(!mman_lock_tryacquire(&mman_kernel))
					goto err;
			} else {
				if unlikely(!mman_lock_acquire_nx(&mman_kernel))
					goto err;
			}
			next_slab_addr = mman_findunmapped(&mman_kernel,
			                                   MHINT_GETADDR(KERNEL_MHINT_SLAB), PAGESIZE,
			                                   MHINT_GETMODE(KERNEL_MHINT_SLAB));
			mman_lock_release(&mman_kernel);
#ifdef CONFIG_SLAB_GROWS_DOWNWARDS
			if (next_slab_addr != MAP_FAILED &&
			    next_slab_addr >= (byte_t *)slab_end_addr - PAGESIZE)
				goto gotaddr;
#else /* CONFIG_SLAB_GROWS_DOWNWARDS */
			if (next_slab_addr != VM_PAGED_GETFREE_ERROR &&
			    next_slab_addr <= (byte_t *)slab_end_addr)
				goto gotaddr;
#endif /* !CONFIG_SLAB_GROWS_DOWNWARDS */
			if (syscache_clear_s(&version))
				goto again_next_slab_page_tryhard;
			goto err;
		}
gotaddr:
		/* Make use of the KRAM mapping system to map more slab memory. */
		assert(!(flags & GFP_MAP_FLAGS));
		result = (struct slab *)mman_map_kram_nx(next_slab_addr, PAGESIZE,
		                                         GFP_MAP_FIXED | flags);
		if unlikely(result == MAP_INUSE)
			goto again_lock_mman_kernel; /* Race condition: our picked address got used in the meantime... */
		if unlikely(result == MAP_FAILED)
			goto err; /* Allocation failed :( */

		/* Update the slab-break end-pointer if necessary. */
#ifdef CONFIG_SLAB_GROWS_DOWNWARDS
		if ((byte_t *)result < (byte_t *)slab_end_addr) {
			while (!ATOMIC_CMPXCH_WEAK(kernel_slab_break, slab_end_addr, result)) {
				slab_end_addr = ATOMIC_READ(kernel_slab_break);
				if ((byte_t *)result >= (byte_t *)slab_end_addr)
					break;
			}
		}
#else /* CONFIG_SLAB_GROWS_DOWNWARDS */
		if ((byte_t *)result >= (byte_t *)slab_end_addr) {
			while (!ATOMIC_CMPXCH_WEAK(kernel_slab_break, slab_end_addr,
			                           (byte_t *)result + PAGESIZE)) {
				slab_end_addr = ATOMIC_READ(kernel_slab_break);
				if ((byte_t *)result < (byte_t *)slab_end_addr)
					break;
			}
		}
#endif /* !CONFIG_SLAB_GROWS_DOWNWARDS */

		return result;
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
for (local align: [4, 8, 16]) {
	print is_first ? "#if" : "#elif", "HEAP_ALIGNMENT ==", align;
	is_first = false;
	print "#if KERNEL_SLAB_COUNT >=", limit + 1;
	print "#error Extend me";
	print "#endif /" "* KERNEL_SLAB_COUNT >=", limit + 1, " *" "/";
	for (local x: [limit-1:0,-1]) {
		print "#if KERNEL_SLAB_COUNT >=", x;
		print "#define SEGMENT_SIZE", x * align;
		print "#include \"slab-impl.c.inl\"";
		if (x > 1)
			print "#define NEXT_SEGMENT_SIZE", x * align;
		print "#endif /" "* KERNEL_SLAB_COUNT >=", x, " *" "/";
	}
}
print "#endif /" "* HEAP_ALIGNMENT == ... *" "/";
]]]*/
#if HEAP_ALIGNMENT == 4
#if KERNEL_SLAB_COUNT >= 17
#error Extend me
#endif /* KERNEL_SLAB_COUNT >= 17  */
#if KERNEL_SLAB_COUNT >= 15
#define SEGMENT_SIZE 60
#include "slab-impl.c.inl"
#define NEXT_SEGMENT_SIZE 60
#endif /* KERNEL_SLAB_COUNT >= 15  */
#if KERNEL_SLAB_COUNT >= 14
#define SEGMENT_SIZE 56
#include "slab-impl.c.inl"
#define NEXT_SEGMENT_SIZE 56
#endif /* KERNEL_SLAB_COUNT >= 14  */
#if KERNEL_SLAB_COUNT >= 13
#define SEGMENT_SIZE 52
#include "slab-impl.c.inl"
#define NEXT_SEGMENT_SIZE 52
#endif /* KERNEL_SLAB_COUNT >= 13  */
#if KERNEL_SLAB_COUNT >= 12
#define SEGMENT_SIZE 48
#include "slab-impl.c.inl"
#define NEXT_SEGMENT_SIZE 48
#endif /* KERNEL_SLAB_COUNT >= 12  */
#if KERNEL_SLAB_COUNT >= 11
#define SEGMENT_SIZE 44
#include "slab-impl.c.inl"
#define NEXT_SEGMENT_SIZE 44
#endif /* KERNEL_SLAB_COUNT >= 11  */
#if KERNEL_SLAB_COUNT >= 10
#define SEGMENT_SIZE 40
#include "slab-impl.c.inl"
#define NEXT_SEGMENT_SIZE 40
#endif /* KERNEL_SLAB_COUNT >= 10  */
#if KERNEL_SLAB_COUNT >= 9
#define SEGMENT_SIZE 36
#include "slab-impl.c.inl"
#define NEXT_SEGMENT_SIZE 36
#endif /* KERNEL_SLAB_COUNT >= 9  */
#if KERNEL_SLAB_COUNT >= 8
#define SEGMENT_SIZE 32
#include "slab-impl.c.inl"
#define NEXT_SEGMENT_SIZE 32
#endif /* KERNEL_SLAB_COUNT >= 8  */
#if KERNEL_SLAB_COUNT >= 7
#define SEGMENT_SIZE 28
#include "slab-impl.c.inl"
#define NEXT_SEGMENT_SIZE 28
#endif /* KERNEL_SLAB_COUNT >= 7  */
#if KERNEL_SLAB_COUNT >= 6
#define SEGMENT_SIZE 24
#include "slab-impl.c.inl"
#define NEXT_SEGMENT_SIZE 24
#endif /* KERNEL_SLAB_COUNT >= 6  */
#if KERNEL_SLAB_COUNT >= 5
#define SEGMENT_SIZE 20
#include "slab-impl.c.inl"
#define NEXT_SEGMENT_SIZE 20
#endif /* KERNEL_SLAB_COUNT >= 5  */
#if KERNEL_SLAB_COUNT >= 4
#define SEGMENT_SIZE 16
#include "slab-impl.c.inl"
#define NEXT_SEGMENT_SIZE 16
#endif /* KERNEL_SLAB_COUNT >= 4  */
#if KERNEL_SLAB_COUNT >= 3
#define SEGMENT_SIZE 12
#include "slab-impl.c.inl"
#define NEXT_SEGMENT_SIZE 12
#endif /* KERNEL_SLAB_COUNT >= 3  */
#if KERNEL_SLAB_COUNT >= 2
#define SEGMENT_SIZE 8
#include "slab-impl.c.inl"
#define NEXT_SEGMENT_SIZE 8
#endif /* KERNEL_SLAB_COUNT >= 2  */
#if KERNEL_SLAB_COUNT >= 1
#define SEGMENT_SIZE 4
#include "slab-impl.c.inl"
#endif /* KERNEL_SLAB_COUNT >= 1  */
#elif HEAP_ALIGNMENT == 8
#if KERNEL_SLAB_COUNT >= 17
#error Extend me
#endif /* KERNEL_SLAB_COUNT >= 17  */
#if KERNEL_SLAB_COUNT >= 15
#define SEGMENT_SIZE 120
#include "slab-impl.c.inl"
#define NEXT_SEGMENT_SIZE 120
#endif /* KERNEL_SLAB_COUNT >= 15  */
#if KERNEL_SLAB_COUNT >= 14
#define SEGMENT_SIZE 112
#include "slab-impl.c.inl"
#define NEXT_SEGMENT_SIZE 112
#endif /* KERNEL_SLAB_COUNT >= 14  */
#if KERNEL_SLAB_COUNT >= 13
#define SEGMENT_SIZE 104
#include "slab-impl.c.inl"
#define NEXT_SEGMENT_SIZE 104
#endif /* KERNEL_SLAB_COUNT >= 13  */
#if KERNEL_SLAB_COUNT >= 12
#define SEGMENT_SIZE 96
#include "slab-impl.c.inl"
#define NEXT_SEGMENT_SIZE 96
#endif /* KERNEL_SLAB_COUNT >= 12  */
#if KERNEL_SLAB_COUNT >= 11
#define SEGMENT_SIZE 88
#include "slab-impl.c.inl"
#define NEXT_SEGMENT_SIZE 88
#endif /* KERNEL_SLAB_COUNT >= 11  */
#if KERNEL_SLAB_COUNT >= 10
#define SEGMENT_SIZE 80
#include "slab-impl.c.inl"
#define NEXT_SEGMENT_SIZE 80
#endif /* KERNEL_SLAB_COUNT >= 10  */
#if KERNEL_SLAB_COUNT >= 9
#define SEGMENT_SIZE 72
#include "slab-impl.c.inl"
#define NEXT_SEGMENT_SIZE 72
#endif /* KERNEL_SLAB_COUNT >= 9  */
#if KERNEL_SLAB_COUNT >= 8
#define SEGMENT_SIZE 64
#include "slab-impl.c.inl"
#define NEXT_SEGMENT_SIZE 64
#endif /* KERNEL_SLAB_COUNT >= 8  */
#if KERNEL_SLAB_COUNT >= 7
#define SEGMENT_SIZE 56
#include "slab-impl.c.inl"
#define NEXT_SEGMENT_SIZE 56
#endif /* KERNEL_SLAB_COUNT >= 7  */
#if KERNEL_SLAB_COUNT >= 6
#define SEGMENT_SIZE 48
#include "slab-impl.c.inl"
#define NEXT_SEGMENT_SIZE 48
#endif /* KERNEL_SLAB_COUNT >= 6  */
#if KERNEL_SLAB_COUNT >= 5
#define SEGMENT_SIZE 40
#include "slab-impl.c.inl"
#define NEXT_SEGMENT_SIZE 40
#endif /* KERNEL_SLAB_COUNT >= 5  */
#if KERNEL_SLAB_COUNT >= 4
#define SEGMENT_SIZE 32
#include "slab-impl.c.inl"
#define NEXT_SEGMENT_SIZE 32
#endif /* KERNEL_SLAB_COUNT >= 4  */
#if KERNEL_SLAB_COUNT >= 3
#define SEGMENT_SIZE 24
#include "slab-impl.c.inl"
#define NEXT_SEGMENT_SIZE 24
#endif /* KERNEL_SLAB_COUNT >= 3  */
#if KERNEL_SLAB_COUNT >= 2
#define SEGMENT_SIZE 16
#include "slab-impl.c.inl"
#define NEXT_SEGMENT_SIZE 16
#endif /* KERNEL_SLAB_COUNT >= 2  */
#if KERNEL_SLAB_COUNT >= 1
#define SEGMENT_SIZE 8
#include "slab-impl.c.inl"
#endif /* KERNEL_SLAB_COUNT >= 1  */
#elif HEAP_ALIGNMENT == 16
#if KERNEL_SLAB_COUNT >= 17
#error Extend me
#endif /* KERNEL_SLAB_COUNT >= 17  */
#if KERNEL_SLAB_COUNT >= 15
#define SEGMENT_SIZE 240
#include "slab-impl.c.inl"
#define NEXT_SEGMENT_SIZE 240
#endif /* KERNEL_SLAB_COUNT >= 15  */
#if KERNEL_SLAB_COUNT >= 14
#define SEGMENT_SIZE 224
#include "slab-impl.c.inl"
#define NEXT_SEGMENT_SIZE 224
#endif /* KERNEL_SLAB_COUNT >= 14  */
#if KERNEL_SLAB_COUNT >= 13
#define SEGMENT_SIZE 208
#include "slab-impl.c.inl"
#define NEXT_SEGMENT_SIZE 208
#endif /* KERNEL_SLAB_COUNT >= 13  */
#if KERNEL_SLAB_COUNT >= 12
#define SEGMENT_SIZE 192
#include "slab-impl.c.inl"
#define NEXT_SEGMENT_SIZE 192
#endif /* KERNEL_SLAB_COUNT >= 12  */
#if KERNEL_SLAB_COUNT >= 11
#define SEGMENT_SIZE 176
#include "slab-impl.c.inl"
#define NEXT_SEGMENT_SIZE 176
#endif /* KERNEL_SLAB_COUNT >= 11  */
#if KERNEL_SLAB_COUNT >= 10
#define SEGMENT_SIZE 160
#include "slab-impl.c.inl"
#define NEXT_SEGMENT_SIZE 160
#endif /* KERNEL_SLAB_COUNT >= 10  */
#if KERNEL_SLAB_COUNT >= 9
#define SEGMENT_SIZE 144
#include "slab-impl.c.inl"
#define NEXT_SEGMENT_SIZE 144
#endif /* KERNEL_SLAB_COUNT >= 9  */
#if KERNEL_SLAB_COUNT >= 8
#define SEGMENT_SIZE 128
#include "slab-impl.c.inl"
#define NEXT_SEGMENT_SIZE 128
#endif /* KERNEL_SLAB_COUNT >= 8  */
#if KERNEL_SLAB_COUNT >= 7
#define SEGMENT_SIZE 112
#include "slab-impl.c.inl"
#define NEXT_SEGMENT_SIZE 112
#endif /* KERNEL_SLAB_COUNT >= 7  */
#if KERNEL_SLAB_COUNT >= 6
#define SEGMENT_SIZE 96
#include "slab-impl.c.inl"
#define NEXT_SEGMENT_SIZE 96
#endif /* KERNEL_SLAB_COUNT >= 6  */
#if KERNEL_SLAB_COUNT >= 5
#define SEGMENT_SIZE 80
#include "slab-impl.c.inl"
#define NEXT_SEGMENT_SIZE 80
#endif /* KERNEL_SLAB_COUNT >= 5  */
#if KERNEL_SLAB_COUNT >= 4
#define SEGMENT_SIZE 64
#include "slab-impl.c.inl"
#define NEXT_SEGMENT_SIZE 64
#endif /* KERNEL_SLAB_COUNT >= 4  */
#if KERNEL_SLAB_COUNT >= 3
#define SEGMENT_SIZE 48
#include "slab-impl.c.inl"
#define NEXT_SEGMENT_SIZE 48
#endif /* KERNEL_SLAB_COUNT >= 3  */
#if KERNEL_SLAB_COUNT >= 2
#define SEGMENT_SIZE 32
#include "slab-impl.c.inl"
#define NEXT_SEGMENT_SIZE 32
#endif /* KERNEL_SLAB_COUNT >= 2  */
#if KERNEL_SLAB_COUNT >= 1
#define SEGMENT_SIZE 16
#include "slab-impl.c.inl"
#endif /* KERNEL_SLAB_COUNT >= 1  */
#endif /* HEAP_ALIGNMENT == ... */
//[[[end]]]
#endif /* !__INTELLISENSE__ */

DECL_BEGIN

PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(KCALL slab_free)(void *__restrict ptr) {
	struct slab *self;
	assert(KERNEL_SLAB_CHECKPTR(ptr));
	self = SLAB_GET(ptr);
	switch (self->s_size) {
#ifndef __INTELLISENSE__
#define CASE_SLAB_FREE(sz, _)                    \
	case sz:                                     \
		slab_freeptr##sz(self, ptr, GFP_NORMAL); \
		break;
	SLAB_FOREACH_SIZE(CASE_SLAB_FREE, _)
#undef CASE_SLAB_FREE
#endif /* !__INTELLISENSE__ */
	default:
#ifndef NDEBUG
#if __SIZEOF_POINTER__ >= 8
		kernel_panic("Corrupted SLAB page at %p has an invalid size of %" PRIu16,
		             self, self->s_size);
#else /* __SIZEOF_POINTER__ >= 8 */
		kernel_panic("Corrupted SLAB page at %p has an invalid size of %" PRIu8,
		             self, self->s_size);
#endif /* __SIZEOF_POINTER__ < 8 */
#else /* !NDEBUG */
		__builtin_unreachable();
#endif /* NDEBUG */
	}
}


PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(KCALL slab_ffree)(void *__restrict ptr, gfp_t flags) {
	struct slab *self;
	assert(KERNEL_SLAB_CHECKPTR(ptr));
	self = SLAB_GET(ptr);
	switch (self->s_size) {
#ifndef __INTELLISENSE__
#define CASE_SLAB_FREE(sz, _)               \
	case sz:                                \
		slab_freeptr##sz(self, ptr, flags); \
		break;
	SLAB_FOREACH_SIZE(CASE_SLAB_FREE, _)
#undef CASE_SLAB_FREE
#endif /* !__INTELLISENSE__ */
	default:
#ifndef NDEBUG
#if __SIZEOF_POINTER__ >= 8
		kernel_panic("Corrupted SLAB page at %p has an invalid size of %" PRIu16,
		             self, self->s_size);
#else /* __SIZEOF_POINTER__ >= 8 */
		kernel_panic("Corrupted SLAB page at %p has an invalid size of %" PRIu8,
		             self, self->s_size);
#endif /* __SIZEOF_POINTER__ < 8 */
#else /* !NDEBUG */
		__builtin_unreachable();
#endif /* NDEBUG */
	}
}


PUBLIC NOBLOCK ATTR_MALLOC WUNUSED VIRT void *
NOTHROW(KCALL __os_slab_malloc)(size_t num_bytes, gfp_t flags) {
#ifndef __INTELLISENSE__
#define CASE_SLAB_MALLOC(sz, _) \
	if (num_bytes <= sz)        \
		return slab_malloc##sz(flags);
	SLAB_FOREACH_SIZE(CASE_SLAB_MALLOC, _)
#undef CASE_SLAB_MALLOC
#endif /* !__INTELLISENSE__ */
#ifndef NDEBUG
	kernel_panic("Invalid slab size %" PRIuSIZ, num_bytes);
	return NULL;
#else /* !NDEBUG */
	__builtin_unreachable();
#endif /* NDEBUG */
}

PUBLIC ATTR_MALLOC ATTR_RETNONNULL WUNUSED VIRT void *KCALL
__os_slab_kmalloc(size_t num_bytes, gfp_t flags) {
#ifndef __INTELLISENSE__
#define CASE_SLAB_MALLOC(sz, _) \
	if (num_bytes <= sz)        \
		return slab_kmalloc##sz(flags);
	SLAB_FOREACH_SIZE(CASE_SLAB_MALLOC, _)
#undef CASE_SLAB_MALLOC
#endif /* !__INTELLISENSE__ */
#ifndef NDEBUG
	kernel_panic("Invalid slab size %" PRIuSIZ, num_bytes);
	return NULL;
#else /* !NDEBUG */
	__builtin_unreachable();
#endif /* NDEBUG */
}

PUBLIC ATTR_MALLOC WUNUSED VIRT void *
NOTHROW(KCALL __os_slab_kmalloc_nx)(size_t num_bytes, gfp_t flags) {
#ifndef __INTELLISENSE__
#define CASE_SLAB_MALLOC(sz, _) \
	if (num_bytes <= sz)        \
		return slab_kmalloc_nx##sz(flags);
	SLAB_FOREACH_SIZE(CASE_SLAB_MALLOC, _)
#undef CASE_SLAB_MALLOC
#endif /* !__INTELLISENSE__ */
#ifndef NDEBUG
	kernel_panic("Invalid slab size %" PRIuSIZ, num_bytes);
	return NULL;
#else /* !NDEBUG */
	__builtin_unreachable();
#endif /* NDEBUG */
}


DECL_END

#endif /* CONFIG_USE_SLAB_ALLOCATORS */

#endif /* !GUARD_KERNEL_SRC_MEMORY_SLAB_C */
