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
#include <kernel/mman/cc.h>
#include <kernel/mman/kram.h>
#include <kernel/mman/unmapped.h>
#include <kernel/panic.h>
#include <kernel/printk.h>
#include <kernel/slab.h>
#include <kernel/types.h>

#include <hybrid/align.h>
#include <hybrid/atomic.h>
#include <hybrid/overflow.h>
#include <hybrid/sched/atomic-lock.h>

#include <assert.h>
#include <inttypes.h>
#include <stdint.h>
#include <string.h>

DECL_BEGIN

#ifndef __slab_slist_defined
#define __slab_slist_defined
SLIST_HEAD(slab_slist, slab);
#endif /* !__slab_slist_defined */

struct slab_pool {
	/* Descriptor for the pool of free slab pages. */
	struct atomic_lock sp_lock;  /* Lock for free pages. */
	struct slab_slist  sp_free;  /* [0..1][lock(sp_lock)] Chain of fully free slab pages. */
	size_t             sp_count; /* [lock(sp_lock)] Current amount of free pool pages */
	size_t             sp_limit; /* [lock(sp_lock)] Max amount of free pool pages, before further pages must be freed. */
	struct slab_slist  sp_pend;  /* [lock(ATOMIC)] Chain of pages pending to-be freed. */
};

/* Helper macros for `struct slab_pool::sp_lock' */
#define slab_pool_reap(self)       (!slab_pool_mustreap(self) || (_slab_pool_reap(self), 0))
#define slab_pool_mustreap(self)   (__hybrid_atomic_load((self)->sp_pend.slh_first, __ATOMIC_ACQUIRE) != __NULLPTR)
#define slab_pool_tryacquire(self) atomic_lock_tryacquire(&(self)->sp_lock)
#define slab_pool_acquire(self)    atomic_lock_acquire(&(self)->sp_lock)
#define slab_pool_acquire_nx(self) atomic_lock_acquire_nx(&(self)->sp_lock)
#define _slab_pool_release(self)   atomic_lock_release(&(self)->sp_lock)
#define slab_pool_release(self)    (atomic_lock_release(&(self)->sp_lock), slab_pool_reap(self))
#define slab_pool_acquired(self)   atomic_lock_acquired(&(self)->sp_lock)
#define slab_pool_available(self)  atomic_lock_available(&(self)->sp_lock)
#define slab_pool_waitfor(self)    atomic_lock_waitfor(&(self)->sp_lock)
#define slab_pool_waitfor_nx(self) atomic_lock_waitfor_nx(&(self)->sp_lock)



#ifndef SLAB_POOL_DEFAULT_LIMIT
#define SLAB_POOL_DEFAULT_LIMIT 3
#endif /* !SLAB_POOL_DEFAULT_LIMIT */


PRIVATE struct slab_pool slab_freepool[2] = {
	{   /* SLAB_FNORMAL / GFP_NORMAL */
		.sp_lock  = ATOMIC_LOCK_INIT,
		.sp_free  = SLIST_HEAD_INITIALIZER(slab_freepool[0].sp_free),
		.sp_count = 0,
		.sp_limit = SLAB_POOL_DEFAULT_LIMIT,
		.sp_pend  = SLIST_HEAD_INITIALIZER(slab_freepool[0].sp_pend),
	}, { /* SLAB_FLOCKED / GFP_LOCKED */
		.sp_lock  = ATOMIC_LOCK_INIT,
		.sp_free  = SLIST_HEAD_INITIALIZER(slab_freepool[1].sp_free),
		.sp_count = 0,
		.sp_limit = SLAB_POOL_DEFAULT_LIMIT,
		.sp_pend  = SLIST_HEAD_INITIALIZER(slab_freepool[1].sp_pend),
	}
};


LOCAL NOBLOCK NONNULL((1, 2)) void
NOTHROW(KCALL pool_do_free)(struct slab_pool *__restrict self,
                            struct slab *__restrict page) {
	if (self->sp_count < self->sp_limit) {
		SLIST_INSERT(&self->sp_free, page, s_slink);
		++self->sp_count;
		return;
	}

	/* Actually release the page as kernel-RAM. */
	mman_unmap_kram(page, PAGESIZE, GFP_NORMAL);
}

/* Reap pending free slabs of `self' */
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL _slab_pool_reap)(struct slab_pool *__restrict self) {
	struct slab *pend, *next;
again:
	pend = SLIST_ATOMIC_CLEAR(&self->sp_pend);
	if unlikely(!pend)
		return;
	if unlikely(!slab_pool_tryacquire(self)) {
		if (!ATOMIC_CMPXCH(self->sp_pend.slh_first, NULL, pend)) {
			struct slab *more;
			next = pend;
			while (SLIST_NEXT(next, s_slink))
				next = SLIST_NEXT(next, s_slink);
			do {
				more = ATOMIC_READ(self->sp_pend.slh_first);
				next->s_slink.sle_next = more;
				COMPILER_WRITE_BARRIER();
			} while (!ATOMIC_CMPXCH_WEAK(self->sp_pend.slh_first, more, pend));
		}
		if unlikely(slab_pool_available(self))
			goto again;
		return;
	}
	do {
		next = SLIST_NEXT(pend, s_slink);
		pool_do_free(self, pend);
		pend = next;
	} while (pend);
	_slab_pool_release(self);
	if unlikely(slab_pool_mustreap(self))
		goto again;
}


/* Free a given slab `self', without ever blocking */
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL slab_freepage)(struct slab *__restrict self) {
	struct slab_pool *pool;
#if SLAB_FLOCKED == 1
	pool = &slab_freepool[self->s_flags & SLAB_FLOCKED];
#else /* SLAB_FLOCKED == 1 */
	pool = &slab_freepool[(self->s_flags & SLAB_FLOCKED) ? 1 : 0];
#endif /* SLAB_FLOCKED != 1 */
	if (slab_pool_tryacquire(pool)) {
		pool_do_free(pool, self);
		slab_pool_release(pool);
	} else {
		SLIST_ATOMIC_INSERT(&pool->sp_pend, self, s_slink);
		_slab_pool_reap(pool);
	}
}


/************************************************************************/
/* Cache clearing                                                       */
/************************************************************************/

PRIVATE NOBLOCK_IF(ccinfo_noblock(info)) NONNULL((1, 2)) void
NOTHROW(KCALL system_cc_perslabpool)(struct slab_pool *__restrict self,
                                     struct ccinfo *__restrict info) {
	struct slab_slist freelist;
	if (!slab_pool_tryacquire(self)) {
		if (ccinfo_noblock(info))
			return;
		if (!slab_pool_acquire_nx(self))
			return;
	}

	/* Steal all free slab pages. */
	freelist = self->sp_free;
	assert(!SLIST_EMPTY(&freelist) == (self->sp_count != 0));
	SLIST_INIT(&self->sp_free);
	self->sp_count = 0;
	slab_pool_release(self);

	/* Release all unused slab pages. */
	while (!SLIST_EMPTY(&freelist)) {
		struct slab *page;
		page = SLIST_FIRST(&freelist);
		SLIST_REMOVE_HEAD(&freelist, s_slink);
		mman_unmap_kram(page, PAGESIZE, GFP_NORMAL);
		ccinfo_account(info, PAGESIZE);
	}
}

/* Free pre-allocated pages of slab memory. */
INTERN NOBLOCK_IF(ccinfo_noblock(info)) NONNULL((1)) void
NOTHROW(KCALL system_cc_slab_prealloc)(struct ccinfo *__restrict info) {
	unsigned int i;
	for (i = 0; i < COMPILER_LENOF(slab_freepool); ++i) {
		system_cc_perslabpool(&slab_freepool[i], info);
		if (ccinfo_isdone(info))
			break;
	}
}






#define CORE_ALLOC_FLAGS                                                        \
	(GFP_LOCKED |                                                               \
	 GFP_PREFLT |                                                               \
	 GFP_MCHEAP | /* Instruct the heap to only consider allocating from VCbase, \
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
	if unlikely(!slab_pool_tryacquire(pool)) {
		if (flags & GFP_ATOMIC)
			goto err;
		if unlikely(!slab_pool_acquire_nx(pool))
			goto err;
	}
	assert(!!SLIST_EMPTY(&pool->sp_free) == (pool->sp_count == 0));
	result = SLIST_FIRST(&pool->sp_free);
	if (result) {
		/* Re-use an already allocated slab page. */
		SLIST_REMOVE_HEAD(&pool->sp_free, s_slink);
		--pool->sp_count;
		slab_pool_release(pool);

		/* Pre-initialize the resulting slab page. */
#ifdef CONFIG_DEBUG_HEAP
#if GFP_CALLOC == SLAB_FCALLOC
		if ((flags & GFP_CALLOC) != (result->s_flags & SLAB_FCALLOC))
#else /* GFP_CALLOC == SLAB_FCALLOC */
		if (!!(flags & GFP_CALLOC) != !!(result->s_flags & SLAB_FCALLOC))
#endif /* GFP_CALLOC != SLAB_FCALLOC */
		{
			if (flags & GFP_CALLOC) {
				bzero(result, PAGESIZE);
			} else {
				mempatl(result, DEBUGHEAP_NO_MANS_LAND, PAGESIZE);
			}
		}
#else /* CONFIG_DEBUG_HEAP */
		if ((flags & GFP_CALLOC) && !(result->s_flags & SLAB_FCALLOC))
			bzero(result, PAGESIZE);
#endif /* !CONFIG_DEBUG_HEAP */
		return result;
	}
	slab_pool_release(pool);
	COMPILER_READ_BARRIER();
	if unlikely(ATOMIC_READ(pool->sp_count) != 0)
		goto again;

	/* Must allocate a new slab page. */
again_lock_mman_kernel:
	if (!mman_lock_tryacquire(&mman_kernel)) {
		if (flags & GFP_ATOMIC)
			goto err;
		if unlikely(!mman_lock_acquire_nx(&mman_kernel))
			goto err;
	}
	{
		void *next_slab_addr;
		void *slab_end_addr;
		slab_end_addr = kernel_slab_break;

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
			if (!mman_lock_tryacquire(&mman_kernel)) {
				if (flags & GFP_ATOMIC)
					goto err;
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

#ifndef NDEBUG
#define NDEBUG_UNREACHABLE(...) __VA_ARGS__
#else /* !NDEBUG */
#define NDEBUG_UNREACHABLE(...) __builtin_unreachable()
#endif /* NDEBUG */


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
		NDEBUG_UNREACHABLE(
		kernel_panic("Corrupted SLAB page at %p has an invalid "
		             "size of %" PRIuN(__SIZEOF_INTPTR_QUARTER_T__),
		             self, self->s_size));
		break;
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
		NDEBUG_UNREACHABLE(
		kernel_panic("Corrupted SLAB page at %p has an invalid "
		             "size of %" PRIuN(__SIZEOF_INTPTR_QUARTER_T__),
		             self, self->s_size));
		break;
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
	NDEBUG_UNREACHABLE(
	kernel_panic("Invalid slab size %" PRIuSIZ, num_bytes);
	return NULL);
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
	NDEBUG_UNREACHABLE(
	kernel_panic("Invalid slab size %" PRIuSIZ, num_bytes);
	return NULL);
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
	NDEBUG_UNREACHABLE(
	kernel_panic("Invalid slab size %" PRIuSIZ, num_bytes);
	return NULL);
}


DECL_END

#endif /* CONFIG_USE_SLAB_ALLOCATORS */

#endif /* !GUARD_KERNEL_SRC_MEMORY_SLAB_C */
