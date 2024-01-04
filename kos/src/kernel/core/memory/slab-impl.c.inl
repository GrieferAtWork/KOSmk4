/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifdef __INTELLISENSE__
#include "slab.c"
#define SEGMENT_SIZE 4
#endif /* __INTELLISENSE__ */

DECL_BEGIN

#ifndef DBG_memset
#if !defined(NDEBUG) && !defined(NDEBUG_FINI)
#define DBG_memset memset
#else /* !NDEBUG && !NDEBUG_FINI */
#define DBG_memset(...) (void)0
#endif /* NDEBUG || NDEBUG_FINI */
#endif /* !DBG_memset */

#define SEGMENT_OFFSET  SLAB_SEGMENT_OFFSET(SEGMENT_SIZE)
#define SEGMENT_COUNT   SLAB_SEGMENT_COUNT(SEGMENT_SIZE)
#define SIZEOF_BITSET   SLAB_SIZEOF_BITSET(SEGMENT_SIZE)
#define LENGTHOF_BITSET SLAB_LENGTHOF_BITSET(SEGMENT_SIZE)

#define LOCAL_segment   PP_CAT2(segment, SEGMENT_SIZE)
#define LOCAL_desc      PP_CAT2(slab_desc, SEGMENT_SIZE)
#define INUSE_BITSET(s) ((uintptr_t *)((struct slab *)(s) + 1))
#define SEGMENTS(s)     ((struct LOCAL_segment *)((byte_t *)(s) + SEGMENT_OFFSET))

/* Local symbols. */
#define LOCAL_slab_dofreeptr                  PP_CAT2(slab_dofreeptr, SEGMENT_SIZE)
#define LOCAL_slab_freeptr                    PP_CAT2(slab_freeptr, SEGMENT_SIZE)
#define LOCAL_slab_descriptor_service_pending PP_CAT2(slab_service_pending, SEGMENT_SIZE)
#define LOCAL_slab_malloc                     PP_CAT2(slab_malloc, SEGMENT_SIZE)
#define LOCAL_slab_kmalloc                    PP_CAT2(slab_kmalloc, SEGMENT_SIZE)
#define LOCAL_slab_kmalloc_nx                 PP_CAT2(slab_kmalloc_nx, SEGMENT_SIZE)

INTERN struct slab_descriptor LOCAL_desc = {
	.sd_lock = ATOMIC_LOCK_INIT,
	.sd_free = LIST_HEAD_INITIALIZER(LOCAL_desc.sd_free),
#ifdef CONFIG_HAVE_KERNEL_TRACE_MALLOC
	.sd_used = LIST_HEAD_INITIALIZER(LOCAL_desc.sd_used),
#endif /* CONFIG_HAVE_KERNEL_TRACE_MALLOC */
	.sd_pend = SLIST_HEAD_INITIALIZER(LOCAL_desc.sd_pend),
};

struct LOCAL_segment {
	byte_t s_data[SEGMENT_SIZE];
};

LOCAL NOBLOCK NONNULL((1, 2)) void
NOTHROW(KCALL LOCAL_slab_dofreeptr)(struct slab *__restrict self,
                                    void *__restrict ptr,
                                    gfp_t flags) {
	size_t index;
	assert(self == SLAB_GET(ptr));
	assert(self->s_size == SEGMENT_SIZE);
	if ((self->s_flags & SLAB_FCALLOC) && !(flags & GFP_CALLOC))
		bzero(ptr, SEGMENT_SIZE);
	index = (((uintptr_t)ptr & PAGEMASK) - SEGMENT_OFFSET) / SEGMENT_SIZE;
	assert(index < SEGMENT_COUNT);
	assert(index == (size_t)((struct LOCAL_segment *)ptr - SEGMENTS(self)));
	assertf(INUSE_BITSET(self)[_SLAB_SEGMENT_STATUS_WORD(index)] & SLAB_SEGMENT_STATUS_ALLOC_N(index),
	        "Double free of %" PRIuSIZ "-byte segment at %p, in page at %p\n"
	        "index        = %" PRIuSIZ "\n"
	        "self->s_free = %" PRIuSIZ,
	        (size_t)SEGMENT_SIZE, ptr, self, index,
	        (size_t)self->s_free);
	assert(self->s_free < SEGMENT_COUNT);

	/* Clear the is-allocated bit. */
	(INUSE_BITSET(self)[_SLAB_SEGMENT_STATUS_WORD(index)]) &= ~SLAB_SEGMENT_STATUS_ALLOC_N(index);

	/* Keep track of how many elements are free. */
	++self->s_free;
	assert(self->s_free <= SEGMENT_COUNT);

	/* Handle special cases. */
	if (self->s_free == SEGMENT_COUNT) {
		/* Free this slab. */
		LIST_REMOVE(self, s_link);
		slab_freepage(self);
	} else if (self->s_free == 1) {
		/* Slab was fully allocated, but became partially allocated. */

#ifdef CONFIG_HAVE_KERNEL_TRACE_MALLOC
		/* Unlink from `sd_used' */
		LIST_REMOVE(self, s_link);
#endif /* CONFIG_HAVE_KERNEL_TRACE_MALLOC */

		/* Insert into `LOCAL_desc.sd_free' */
		LIST_INSERT_HEAD(&LOCAL_desc.sd_free, self, s_link);
	}
}


/* Service pending free operations. */
LOCAL NOBLOCK void
NOTHROW(KCALL LOCAL_slab_descriptor_service_pending)(void) {
	struct slab_pending_free *pend, *next;
again:
	pend = SLIST_ATOMIC_CLEAR(&LOCAL_desc.sd_pend);
	if unlikely(!pend)
		return;
	assert(KERNEL_SLAB_CHECKPTR(pend));
	if unlikely(!slab_descriptor_tryacquire(&LOCAL_desc)) {
		if (!atomic_cmpxch(&LOCAL_desc.sd_pend.slh_first, NULL, pend)) {
			next = pend;
			while (SLIST_NEXT(next, spf_link))
				next = SLIST_NEXT(next, spf_link);
			SLIST_ATOMIC_INSERT_R(&LOCAL_desc.sd_pend, pend, next, spf_link);
		}
		if unlikely(slab_descriptor_available(&LOCAL_desc))
			goto again;
		return;
	}
	do {
		next = SLIST_NEXT(pend, spf_link);
#ifdef CONFIG_HAVE_KERNEL_DEBUG_HEAP
		mempatl(&pend->spf_link, DEBUGHEAP_NO_MANS_LAND, sizeof(pend->spf_link));
#endif /* CONFIG_HAVE_KERNEL_DEBUG_HEAP */
		LOCAL_slab_dofreeptr(SLAB_GET(pend), pend, GFP_NORMAL);
		pend = next;
	} while (pend);
	_slab_descriptor_release(&LOCAL_desc);
	if unlikely(slab_descriptor_mustreap(&LOCAL_desc))
		goto again;
}

LOCAL NOBLOCK NONNULL((1, 2)) void
NOTHROW(KCALL LOCAL_slab_freeptr)(struct slab *__restrict self,
                                  void *__restrict ptr,
                                  gfp_t flags) {
	assert(self->s_size == SEGMENT_SIZE);
#ifdef CONFIG_HAVE_KERNEL_DEBUG_HEAP
	if (!(flags & GFP_CALLOC))
		mempatl(ptr, DEBUGHEAP_NO_MANS_LAND, SEGMENT_SIZE);
#endif /* CONFIG_HAVE_KERNEL_DEBUG_HEAP */
	if likely(slab_descriptor_tryacquire(&LOCAL_desc)) {
		LOCAL_slab_dofreeptr(self, ptr, flags);
		slab_descriptor_release(&LOCAL_desc);
	} else {
		/* Free asynchronously once the lock becomes available. */
		struct slab_pending_free *pend;
		pend = (struct slab_pending_free *)ptr;
#ifdef CONFIG_HAVE_KERNEL_DEBUG_HEAP
#if SEGMENT_SIZE > __SIZEOF_POINTER__
		if (flags & GFP_CALLOC) {
			mempatl(pend + 1, DEBUGHEAP_NO_MANS_LAND,
			        SEGMENT_SIZE - sizeof(*pend));
		}
#endif /* SEGMENT_SIZE > __SIZEOF_POINTER__ */
#endif /* CONFIG_HAVE_KERNEL_DEBUG_HEAP */
		SLIST_ATOMIC_INSERT(&LOCAL_desc.sd_pend, pend, spf_link);
		LOCAL_slab_descriptor_service_pending();
	}
}


PUBLIC ATTR_BLOCKLIKE_GFP(flags) ATTR_MALLOC WUNUSED VIRT void *
NOTHROW(KCALL LOCAL_slab_malloc)(gfp_t flags) {
	void *result;
	struct slab *result_page;
again:
	if unlikely(!slab_descriptor_tryacquire(&LOCAL_desc)) {
		if (flags & GFP_ATOMIC)
			goto err;
		if unlikely(!slab_descriptor_acquire_nx(&LOCAL_desc))
			goto err;
	}
	result_page = LIST_FIRST(&LOCAL_desc.sd_free);
	if likely(result_page) {
		unsigned int i, j;
		assert(result_page->s_link.le_prev == &LOCAL_desc.sd_free.lh_first);
		assert(result_page->s_free != 0);
		assert(result_page->s_size == SEGMENT_SIZE);
		for (i = 0;; ++i) {
			uintptr_t word, mask;
			u8 page_flags;
			assertf(i < LENGTHOF_BITSET, "i = %u, LENGTHOF_BITSET = %u",
			        i, (unsigned int)LENGTHOF_BITSET);
			word = INUSE_BITSET(result_page)[i];
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
			(INUSE_BITSET(result_page)[i]) = word | mask;
			page_flags = result_page->s_flags;
			COMPILER_READ_BARRIER();
			result = &SEGMENTS(result_page)[j + i * (BITS_PER_POINTER / SLAB_SEGMENT_STATUS_BITS)];
			if (--result_page->s_free == 0) {
				LIST_REMOVE(result_page, s_link);
#ifdef CONFIG_HAVE_KERNEL_TRACE_MALLOC
				LIST_INSERT_HEAD(&LOCAL_desc.sd_used, result_page, s_link);
#endif /* CONFIG_HAVE_KERNEL_TRACE_MALLOC */
			}
			slab_descriptor_release(&LOCAL_desc);
#ifdef CONFIG_HAVE_KERNEL_DEBUG_HEAP
			if (page_flags & SLAB_FCALLOC) {
				if (!(flags & GFP_CALLOC))
					mempatl(result, DEBUGHEAP_FRESH_MEMORY, SEGMENT_SIZE);
			} else if (flags & GFP_CALLOC) {
				bzero(result, SEGMENT_SIZE);
			} else {
				mempatl(result, DEBUGHEAP_FRESH_MEMORY, SEGMENT_SIZE);
			}
#else /* CONFIG_HAVE_KERNEL_DEBUG_HEAP */
			if ((flags & GFP_CALLOC) && !(page_flags & SLAB_FCALLOC))
				bzero(result, SEGMENT_SIZE);
#endif /* !CONFIG_HAVE_KERNEL_DEBUG_HEAP */
			return result;
		}
	}
	slab_descriptor_release(&LOCAL_desc);

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
	result_page->s_free = SEGMENT_COUNT - 1; /* One of the segments gets returned to the caller */
	result_page->s_size = SEGMENT_SIZE;
	result_page->s_link.le_prev = &LOCAL_desc.sd_free.lh_first;
	result_page->s_link.le_next = NULL;
	if (!(flags & GFP_CALLOC))
		bzero(&INUSE_BITSET(result_page)[1], SIZEOF_BITSET - sizeof(uintptr_t));
	(INUSE_BITSET(result_page)[0]) = SLAB_SEGMENT_STATUS_ALLOC;
	result = &SEGMENTS(result_page)[0];

	/* Re-acquire locks. */
	if unlikely(!slab_descriptor_tryacquire(&LOCAL_desc)) {
		if (flags & GFP_ATOMIC)
			goto err_result_page;
		if unlikely(!slab_descriptor_acquire_nx(&LOCAL_desc))
			goto err_result_page;
	}

	/* Check if new free-pages have appeared in the mean time. */
	COMPILER_READ_BARRIER();
	if unlikely(!LIST_EMPTY(&LOCAL_desc.sd_free)) {
		slab_descriptor_release(&LOCAL_desc);
		slab_freepage(result_page);
		goto again;
	}

	/* Save the new free-page. */
	LOCAL_desc.sd_free.lh_first = result_page;
	slab_descriptor_release(&LOCAL_desc);
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


PUBLIC ATTR_BLOCKLIKE_GFP(flags) ATTR_MALLOC ATTR_RETNONNULL WUNUSED VIRT void *KCALL
LOCAL_slab_kmalloc(gfp_t flags) {
	void *result;
#ifdef CONFIG_HAVE_KERNEL_TRACE_MALLOC
	/* XXX: When `GFP_NOLEAK / GFP_NOWALK' are given, never allocate slab memory? */
#endif /* !CONFIG_HAVE_KERNEL_TRACE_MALLOC */

	/* Try to allocate from slab memory */
	result = LOCAL_slab_malloc(flags);
	if likely(result != NULL)
		return result;

	/* Fall back to allocating without the slab engine */
	return __os_malloc_noslab(CEIL_ALIGN(SEGMENT_SIZE,
	                                     HEAP_ALIGNMENT),
	                          flags);
}

PUBLIC ATTR_BLOCKLIKE_GFP(flags) ATTR_MALLOC WUNUSED VIRT void *
NOTHROW(KCALL LOCAL_slab_kmalloc_nx)(gfp_t flags) {
	void *result;
#ifdef CONFIG_HAVE_KERNEL_TRACE_MALLOC
	/* XXX: When `GFP_NOLEAK / GFP_NOWALK' are given, never allocate slab memory? */
#endif /* !CONFIG_HAVE_KERNEL_TRACE_MALLOC */

	/* Try to allocate from slab memory */
	result = LOCAL_slab_malloc(flags);
	if likely(result != NULL)
		return result;

	/* Fall back to allocating without the slab engine */
	return __os_malloc_noslab_nx(CEIL_ALIGN(SEGMENT_SIZE,
	                                        HEAP_ALIGNMENT),
	                             flags);
}


#undef LOCAL_slab_dofreeptr
#undef LOCAL_slab_freeptr
#undef LOCAL_slab_descriptor_service_pending
#undef LOCAL_slab_malloc
#undef LOCAL_slab_kmalloc
#undef LOCAL_slab_kmalloc_nx

#undef SEGMENTS
#undef INUSE_BITSET
#undef LOCAL_segment
#undef LOCAL_desc

DECL_END

#undef LENGTHOF_BITSET
#undef SIZEOF_BITSET
#undef SEGMENT_COUNT
#undef SEGMENT_OFFSET
#undef SEGMENT_SIZE

#undef NEXT_SEGMENT_SIZE
