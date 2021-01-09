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
#ifdef __INTELLISENSE__
#include "slab.c"
#define SEGMENT_SIZE 4
#endif /* __INTELLISENSE__ */

#define FUNC3(x, y) x##y
#define FUNC2(x, y) FUNC3(x, y)
#define FUNC(x)     FUNC2(x, SEGMENT_SIZE)

#define SEGMENT_OFFSET  SLAB_SEGMENT_OFFSET(SEGMENT_SIZE)
#define SEGMENT_COUNT   SLAB_SEGMENT_COUNT(SEGMENT_SIZE)
#define SIZEOF_BITSET   SLAB_SIZEOF_BITSET(SEGMENT_SIZE)
#define LENGTHOF_BITSET SLAB_LENGTHOF_BITSET(SEGMENT_SIZE)

DECL_BEGIN

#define DESC        FUNC(slab_desc)
#define BITSET(s)   ((uintptr_t *)((struct slab *)(s) + 1))
#define SEGMENTS(s) ((struct FUNC(segment) *)((byte_t *)(s) + SEGMENT_OFFSET))

INTERN struct slab_descriptor DESC = {
	/* .sd_lock = */ ATOMIC_LOCK_INIT,
	/* .sd_free = */ NULL,
#ifdef CONFIG_TRACE_MALLOC
	/* .sd_used = */ NULL,
#endif /* CONFIG_TRACE_MALLOC */
	/* .sd_pend = */ NULL
};

struct FUNC(segment) {
	byte_t s_data[SEGMENT_SIZE];
};

LOCAL NONNULL((1, 2)) void
NOTHROW(KCALL FUNC(slab_dofreeptr))(struct slab *__restrict self,
                                    void *__restrict ptr,
                                    gfp_t flags) {
	size_t index;
	assert(self == SLAB_GET(ptr));
	assert(self->s_size == SEGMENT_SIZE);
	if ((self->s_flags & SLAB_FCALLOC) && !(flags & GFP_CALLOC))
		memset(ptr, 0, SEGMENT_SIZE);
	index = (((uintptr_t)ptr & PAGEMASK) - SEGMENT_OFFSET) / SEGMENT_SIZE;
	assert(index < SEGMENT_COUNT);
	assert(index == (size_t)((struct FUNC(segment) *)ptr - SEGMENTS(self)));
	assertf(BITSET(self)[_SLAB_SEGMENT_STATUS_WORD(index)] & SLAB_SEGMENT_STATUS_ALLOC_N(index),
	        "Double free of %" PRIuSIZ "-byte segment at %p, in page at %p\n"
	        "index        = %" PRIuSIZ "\n"
	        "self->s_free = %" PRIuSIZ,
	        (size_t)SEGMENT_SIZE, ptr, self, index,
	        (size_t)self->s_free);
	assert(self->s_free < SEGMENT_COUNT);
	/* Clear the is-allocated bit. */
	(BITSET(self)[_SLAB_SEGMENT_STATUS_WORD(index)]) &= ~SLAB_SEGMENT_STATUS_ALLOC_N(index);
	++self->s_free;
	assert(self->s_free <= SEGMENT_COUNT);
	if (self->s_free == SEGMENT_COUNT) {
		/* Free this slab. */
		if ((*self->s_pself = self->s_next) != NULL)
			self->s_next->s_pself = self->s_pself;
		slab_freepage(self);
	} else if (self->s_free == 1) {
		/* Slab was fully allocated, but became partially allocated. */
#ifdef CONFIG_TRACE_MALLOC
		/* Unlink from `sd_used' */
		if ((*self->s_pself = self->s_next) != NULL)
			self->s_next->s_pself = self->s_pself;
#endif /* CONFIG_TRACE_MALLOC */
		/* Insert into `DESC.sd_free' */
		if ((self->s_next = DESC.sd_free) != NULL) {
			assert(DESC.sd_free->s_pself == &DESC.sd_free);
			DESC.sd_free->s_pself = &self->s_next;
		}
		self->s_pself = &DESC.sd_free;
		DESC.sd_free  = self;
	}
}


LOCAL void
NOTHROW(KCALL FUNC(slab_service_pending))(void) {
	struct slab_pending_free *pend, *next;
	pend = ATOMIC_XCH(DESC.sd_pend, NULL);
	while (pend) {
		next = pend->spf_next;
		assert(KERNEL_SLAB_CHECKPTR(pend));
		mempatl(pend, DEBUGHEAP_NO_MANS_LAND, sizeof(void *));
		FUNC(slab_dofreeptr)(SLAB_GET(pend), pend, GFP_NORMAL);
		pend = next;
	}
}

LOCAL NOBLOCK NONNULL((1, 2)) void
NOTHROW(KCALL FUNC(slab_freeptr))(struct slab *__restrict self,
                                  void *__restrict ptr,
                                  gfp_t flags) {
	assert(self->s_size == SEGMENT_SIZE);
#ifdef CONFIG_DEBUG_HEAP
	if (!(flags & GFP_CALLOC))
		mempatl(ptr, DEBUGHEAP_NO_MANS_LAND, SEGMENT_SIZE);
#endif /* CONFIG_DEBUG_HEAP */
	if likely(sync_trywrite(&DESC.sd_lock)) {
		FUNC(slab_service_pending)();
		FUNC(slab_dofreeptr)(self, ptr, flags);
		sync_endwrite(&DESC.sd_lock);
		if unlikely(ATOMIC_READ(DESC.sd_pend) != NULL)
			goto again_try_service;
	} else {
		struct slab_pending_free *pend, *next;
#ifdef CONFIG_DEBUG_HEAP
#if SEGMENT_SIZE > __SIZEOF_POINTER__
		if (flags & GFP_CALLOC)
			mempatl((byte_t *)ptr + sizeof(void *), DEBUGHEAP_NO_MANS_LAND, SEGMENT_SIZE - sizeof(void *));
#endif /* SEGMENT_SIZE > __SIZEOF_POINTER__ */
#endif /* CONFIG_DEBUG_HEAP */
		pend = (struct slab_pending_free *)ptr;
		do {
			next = ATOMIC_READ(DESC.sd_pend);
			pend->spf_next = next;
		} while unlikely(!ATOMIC_CMPXCH_WEAK(DESC.sd_pend, next, pend));
again_try_service:
		if (sync_trywrite(&DESC.sd_lock)) {
			FUNC(slab_service_pending)();
			sync_endwrite(&DESC.sd_lock);
			if unlikely(ATOMIC_READ(DESC.sd_pend) != NULL)
				goto again_try_service;
		}
	}
}

LOCAL NOBLOCK void
NOTHROW(KCALL FUNC(slab_endwrite))(void) {
again:
	sync_endwrite(&DESC.sd_lock);
	if unlikely(ATOMIC_READ(DESC.sd_pend) != NULL) {
		if likely(sync_trywrite(&DESC.sd_lock)) {
			FUNC(slab_service_pending)();
			goto again;
		}
	}
}


PUBLIC NOBLOCK ATTR_MALLOC WUNUSED VIRT void *
NOTHROW(KCALL FUNC(slab_malloc))(gfp_t flags) {
	void *result;
	struct slab *result_page;
again:
	if unlikely(!sync_trywrite(&DESC.sd_lock)) {
		if (flags & GFP_ATOMIC)
			goto err;
		if unlikely(!sync_write_nx(&DESC.sd_lock))
			goto err;
	}
	result_page = DESC.sd_free;
	if likely(result_page) {
		unsigned int i, j;
		assert(result_page->s_pself == &DESC.sd_free);
		assert(result_page->s_free != 0);
		assert(result_page->s_size == SEGMENT_SIZE);
		for (i = 0;; ++i) {
			uintptr_t word, mask;
			u8 page_flags;
			assertf(i < LENGTHOF_BITSET, "i = %u, LENGTHOF_BITSET = %u",
			        i, (unsigned int)LENGTHOF_BITSET);
			word = BITSET(result_page)[i];
#if _SLAB_SEGMENT_STATUS_WORDMASK(SLAB_SEGMENT_STATUS_ALLOC) == UINTPTR_MAX
			if (word == _SLAB_SEGMENT_STATUS_WORDMASK(SLAB_SEGMENT_STATUS_ALLOC))
				continue; /* Fully allocated */
#else /* _SLAB_SEGMENT_STATUS_WORDMASK(SLAB_SEGMENT_STATUS_ALLOC) == UINTPTR_MAX */
			if ((word & _SLAB_SEGMENT_STATUS_WORDMASK(SLAB_SEGMENT_STATUS_ALLOC)) ==
			    /*   */ _SLAB_SEGMENT_STATUS_WORDMASK(SLAB_SEGMENT_STATUS_ALLOC))
				continue; /* Fully allocated */
#endif /* _SLAB_SEGMENT_STATUS_WORDMASK(SLAB_SEGMENT_STATUS_ALLOC) != UINTPTR_MAX */
			/* Search for the first unallocated segment in this word. */
			for (j = 0, mask = SLAB_SEGMENT_STATUS_ALLOC;
			     (word & mask) != 0;
			     ++j, mask <<= SLAB_SEGMENT_STATUS_BITS)
				;
			assert(j < (BITS_PER_POINTER / SLAB_SEGMENT_STATUS_BITS));
			assert(mask == (uintptr_t)SLAB_SEGMENT_STATUS_ALLOC << (j * SLAB_SEGMENT_STATUS_BITS));
			/* Add our new allocation mask to mark our new segment as allocated. */
			(BITSET(result_page)[i]) = word | mask;
			page_flags = result_page->s_flags;
			COMPILER_READ_BARRIER();
			result = &SEGMENTS(result_page)[j + i * (BITS_PER_POINTER / SLAB_SEGMENT_STATUS_BITS)];
			if (--result_page->s_free == 0) {
				DESC.sd_free = result_page->s_next;
				if (DESC.sd_free)
					DESC.sd_free->s_pself = &DESC.sd_free;
#ifdef CONFIG_TRACE_MALLOC
				if ((result_page->s_next = DESC.sd_used) != NULL)
					DESC.sd_used->s_pself = &result_page->s_next;
				result_page->s_pself = &DESC.sd_used;
				DESC.sd_used         = result_page;
#else /* CONFIG_TRACE_MALLOC */
				result_page->s_pself = NULL;
#ifndef NDEBUG
				memset(&result_page->s_next, 0xcc, sizeof(result_page->s_next));
#endif /* !NDEBUG */
#endif /* !CONFIG_TRACE_MALLOC */
			}
			FUNC(slab_endwrite)();
#ifdef CONFIG_DEBUG_HEAP
			if (page_flags & SLAB_FCALLOC) {
				if (!(flags & GFP_CALLOC))
					mempatl(result, DEBUGHEAP_FRESH_MEMORY, SEGMENT_SIZE);
			} else if (flags & GFP_CALLOC) {
				memset(result, 0, SEGMENT_SIZE);
			} else {
				mempatl(result, DEBUGHEAP_FRESH_MEMORY, SEGMENT_SIZE);
			}
#else /* CONFIG_DEBUG_HEAP */
			if ((flags & GFP_CALLOC) && !(page_flags & SLAB_FCALLOC))
				memset(result, 0, SEGMENT_SIZE);
#endif /* !CONFIG_DEBUG_HEAP */
			return result;
		}
	}
	FUNC(slab_endwrite)();
	/* Must allocate a new SLAB page. */
	result_page = slab_alloc_page(flags);
	if unlikely(!result_page)
		goto err;
	/* Initialize the new page. */
#if GFP_LOCKED == SLAB_FLOCKED && GFP_CALLOC == SLAB_FCALLOC
	result_page->s_flags = flags & (GFP_LOCKED | GFP_CALLOC);
#else /* GFP_LOCKED == SLAB_FLOCKED && GFP_CALLOC == SLAB_FCALLOC */
	result_page->s_flags = 0;
	if (flags & GFP_LOCKED)
		result_page->s_flags |= SLAB_FLOCKED;
	if (flags & GFP_CALLOC)
		result_page->s_flags |= SLAB_FCALLOC;
#endif /* GFP_LOCKED != SLAB_FLOCKED || GFP_CALLOC != SLAB_FCALLOC */
	result_page->s_free  = SEGMENT_COUNT - 1; /* One of the segments gets returned to the caller */
	result_page->s_size  = SEGMENT_SIZE;
	result_page->s_pself = &DESC.sd_free;
	result_page->s_next  = NULL;
	if (!(flags & GFP_CALLOC))
		memset(&BITSET(result_page)[1], 0, SIZEOF_BITSET - sizeof(uintptr_t));
	(BITSET(result_page)[0]) = SLAB_SEGMENT_STATUS_ALLOC;
	result = &SEGMENTS(result_page)[0];

	if unlikely(!sync_trywrite(&DESC.sd_lock)) {
		if (flags & GFP_ATOMIC)
			goto err_result_page;
		if unlikely(!sync_write_nx(&DESC.sd_lock))
			goto err_result_page;
	}
	COMPILER_READ_BARRIER();
	/* Check if new free-pages have appeared in the mean time. */
	if unlikely(ATOMIC_READ(DESC.sd_free) != NULL) {
		FUNC(slab_endwrite)();
		slab_freepage(result_page);
		goto again;
	}
	/* Save the new free-page. */
	DESC.sd_free = result_page;
	FUNC(slab_endwrite)();
	return result;
err_result_page:
	slab_freepage(result_page);
err:
#ifdef NEXT_SEGMENT_SIZE
	/* Re-attempt the allocation with the next larger SLAB segment. */
#define NEXT_FUNC2(x, y) x##y
#define NEXT_FUNC(x, y) NEXT_FUNC2(x, y)
	return NEXT_FUNC(slab_malloc, NEXT_SEGMENT_SIZE)(flags);
#else /* NEXT_SEGMENT_SIZE */
	return NULL;
#endif /* !NEXT_SEGMENT_SIZE */
}


PUBLIC ATTR_MALLOC ATTR_RETNONNULL WUNUSED VIRT void *KCALL
FUNC(slab_kmalloc)(gfp_t flags) {
	/* Try to allocate from slab memory */
	void *result;
#ifdef CONFIG_TRACE_MALLOC
	/* XXX: When `GFP_NOLEAK / GFP_NOWALK' are given, never allocate slab memory? */
#endif /* !CONFIG_TRACE_MALLOC */
	result = FUNC(slab_malloc)(flags);
	if likely(result)
		return result;
	/* Fall back to allocating without the slab engine */
	return __os_malloc_noslab(CEIL_ALIGN(SEGMENT_SIZE,
	                                     HEAP_ALIGNMENT),
	                          flags);
}

PUBLIC ATTR_MALLOC WUNUSED VIRT void *
NOTHROW(KCALL FUNC(slab_kmalloc_nx))(gfp_t flags) {
	/* Try to allocate from slab memory */
	void *result;
#ifdef CONFIG_TRACE_MALLOC
	/* XXX: When `GFP_NOLEAK / GFP_NOWALK' are given, never allocate slab memory? */
#endif /* !CONFIG_TRACE_MALLOC */
	result = FUNC(slab_malloc)(flags);
	if likely(result)
		return result;
	/* Fall back to allocating without the slab engine */
	return __os_malloc_noslab_nx(CEIL_ALIGN(SEGMENT_SIZE,
	                                        HEAP_ALIGNMENT),
	                             flags);
}


#undef SEGMENTS
#undef BITSET
#undef DESC

DECL_END

#undef LENGTHOF_BITSET
#undef SIZEOF_BITSET
#undef SEGMENT_COUNT
#undef SEGMENT_OFFSET
#undef SEGMENT_SIZE

#undef NEXT_SEGMENT_SIZE
#undef FUNC3
#undef FUNC2
#undef FUNC
