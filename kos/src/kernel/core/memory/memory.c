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
#ifndef GUARD_KERNEL_SRC_MEMORY_MEMORY_C
#define GUARD_KERNEL_SRC_MEMORY_MEMORY_C 1
#define __NO_PAGE_MALLOC_CONSTANT_P_WRAPPERS 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <debugger/config.h>
#include <debugger/hook.h>
#include <debugger/io.h>
#include <kernel/memory.h>
#include <kernel/mman/cache.h>
#include <kernel/panic.h>
#include <kernel/printk.h>
#include <kernel/rand.h>
#include <sched/group.h>

#include <hybrid/atomic.h>
#include <hybrid/bit.h>
#include <hybrid/overflow.h>

#include <assert.h>
#include <format-printer.h>
#include <inttypes.h>
#include <stddef.h>
#include <string.h>

/* These are only here for do_trace_external() */
#include <kernel/arch/syslog.h> /* x86_syslog_write() */
#include <stdio.h>

DECL_BEGIN


#define PAGES_PER_WORD  (BITS_PER_POINTER / PMEMZONE_BITSPERPAGE)

#if !defined(NDEBUG) && 0
#define PRINT_ALLOCATION(...) (printk(KERN_DEBUG "[memory] " __VA_ARGS__))
#else /* !NDEBUG */
#define PRINT_ALLOCATION(...) (void)0
#endif /* NDEBUG */


#if !defined(NDEBUG) && 0
LOCAL NOBLOCK void
NOTHROW(KCALL do_trace_external)(char const *method,
                                 physpage_t min,
                                 physpage_t max) {
	size_t len;
	char buf[128];
	/* NOTE: 030 -> CAN -> CANCEL (abort any in-progress sequence) */
	len = sprintf(buf, "\030%%{trace:%s:pmem:%#p:%#p}", method, min, max);
	x86_syslog_write(buf, len);
}
#define TRACE_EXTERNAL(method, min, max) \
	do_trace_external(method, min, max)
#else /* !NDEBUG */
#define TRACE_EXTERNAL(method, min, max) (void)0
#endif /* NDEBUG */


#define TRACE_ALLOC(zone, min, max)                             \
	(TRACE_EXTERNAL("alloc", min, max),                         \
	 PRINT_ALLOCATION("Allocate physical ram "                  \
	                  "%" PRIpN(__SIZEOF_PHYSADDR_T__) "..."    \
	                  "%" PRIpN(__SIZEOF_PHYSADDR_T__) " ["     \
	                  "%" PRIuN(__SIZEOF_PHYSPAGE_T__) "-"      \
	                  "%" PRIuN(__SIZEOF_PHYSPAGE_T__) "="      \
	                  "%" PRIuN(__SIZEOF_PHYSPAGE_T__) "]\n",   \
	                  physpage2addr(min),                       \
	                  physpage2addr((max) + 1) - 1,             \
	                  (zone)->mz_cfree + (((max) - (min)) + 1), \
	                  ((max) - (min)) + 1, (zone)->mz_cfree))
#define TRACE_FREE(zone, min, max)                            \
	(TRACE_EXTERNAL("free", min, max),                        \
	 PRINT_ALLOCATION("Free physical ram "                    \
	                  "%" PRIpN(__SIZEOF_PHYSADDR_T__) "..."  \
	                  "%" PRIpN(__SIZEOF_PHYSADDR_T__) " ["   \
	                  "%" PRIuN(__SIZEOF_PHYSPAGE_T__) "-"    \
	                  "%" PRIuN(__SIZEOF_PHYSPAGE_T__) "="    \
	                  "%" PRIuN(__SIZEOF_PHYSPAGE_T__) "]\n", \
	                  physpage2addr(min),                     \
	                  physpage2addr((max) + 1) - 1,           \
	                  (zone)->mz_cfree,                       \
	                  ((max) - (min)) + 1,                    \
	                  (zone)->mz_cfree + (((max) - (min)) + 1)))


#undef IGNORE_FREE
#undef ALLOCATE_MIN_PARTS
#undef ALLOCATE_MIN_PARTS_RANDOMIZE

/* Ignore physical memory being freed. */
//#define IGNORE_FREE 1

/* Always allocate the minimum amount of memory in min-max allocations. */
//#define ALLOCATE_MIN_PARTS 1

#ifndef NDEBUG
/* In min-max allocations,  randomize the the  max-allocation to  occasionally
 * allocate less than the maximum request in order to harden the less-traveled
 * paths used when allocating scattered memory. */
//#define ALLOCATE_MIN_PARTS_RANDOMIZE 1
#define ALLOCATE_MIN_PARTS_RANDOMIZE_CHANCE()  (krand32() < 0x55555555)
#endif /* !NDEBUG */




/* Mask of bits that are tested to determine if a page is free. */
#if PMEMZONE_ISFREEBIT == 0
#if __SIZEOF_POINTER__ == 4
#define PMEMBITSET_FREEMASK   __UINT32_C(0x55555555)
#else /* __SIZEOF_POINTER__ == 4 */
#define PMEMBITSET_FREEMASK   __UINT64_C(0x5555555555555555)
#endif /* __SIZEOF_POINTER__ != 4 */
#else /* PMEMZONE_ISFREEBIT == 0 */
#if __SIZEOF_POINTER__ == 4
#define PMEMBITSET_FREEMASK   __UINT32_C(0xaaaaaaaa)
#else /* __SIZEOF_POINTER__ == 4 */
#define PMEMBITSET_FREEMASK   __UINT64_C(0xaaaaaaaaaaaaaaaa)
#endif /* __SIZEOF_POINTER__ != 4 */
#endif /* PMEMZONE_ISFREEBIT != 0 */
#define PMEMBITSET_UNDFMASK   (~PMEMBITSET_FREEMASK)
STATIC_ASSERT_MSG(PMEMZONE_BITSPERPAGE == 2,"Must re-do the logic above");
STATIC_ASSERT((BITSOF(uintptr_t) % PMEMZONE_BITSPERPAGE) == 0);



LOCAL NOBLOCK void
NOTHROW(KCALL pmemzone_set_fmax)(struct pmemzone *__restrict self,
                                 physpage_t new_free_max) {
	/* Keep  track  of  the  greatest  free  page within
	 * the zone, to-be used as a hint for the allocator. */
	physpage_t free_max;
	do {
		free_max = ATOMIC_READ(self->mz_fmax);
		if (free_max > new_free_max)
			break;
	} while (!ATOMIC_CMPXCH_WEAK(self->mz_fmax, free_max, new_free_max));
}

PRIVATE NOBLOCK void
NOTHROW(KCALL zone_free_keepz)(struct pmemzone *__restrict self,
                               physpage_t zone_relative_base,
                               physpagecnt_t num_pages) {
	size_t i, num_qpages;
	uintptr_t mask;
	uintptr_t oldval;
	assert(num_pages);
	assert(zone_relative_base + num_pages > zone_relative_base);
	assert(zone_relative_base + num_pages - 1 <= self->mz_rmax);
	ATOMIC_FETCHADD(self->mz_cfree, num_pages);
	pmemzone_set_fmax(self, zone_relative_base + num_pages - 1);
	i = (size_t)(zone_relative_base / PAGES_PER_WORD);
	num_qpages = 0;
	if (num_pages == 1) {
		mask   = (uintptr_t)PMEMZONE_ISFREEMASK
		       << (unsigned int)((zone_relative_base % PAGES_PER_WORD) * PMEMZONE_BITSPERPAGE);
		oldval = ATOMIC_FETCHOR(self->mz_free[i], mask);
		assertf(!(oldval & mask), "Double free at %" PRIpN(__SIZEOF_PHYSPAGE_T__),
		        (physpage_t)(self->mz_start + zone_relative_base));
		if (oldval & (mask << (PMEMZONE_ISUNDFBIT - PMEMZONE_ISFREEBIT)))
			++num_qpages;
	} else {
		/* free partial pages. */
		unsigned int misalignment, num_free;
		misalignment = (unsigned int)(zone_relative_base & (PAGES_PER_WORD - 1));
		if (misalignment) {
			num_free = (PAGES_PER_WORD - misalignment);
			mask     = PMEMBITSET_FREEMASK;
			if ((physpagecnt_t)num_free > num_pages) {
				num_free = (unsigned int)num_pages;
				mask &= (((uintptr_t)1 << (num_free * PMEMZONE_BITSPERPAGE)) - 1);
			}
			mask <<= misalignment * PMEMZONE_BITSPERPAGE;
			oldval = ATOMIC_FETCHOR(self->mz_free[i], mask);
			assertf(!(oldval & mask),
			        "Double free at near %" PRIpN(__SIZEOF_PHYSPAGE_T__) "\n",
			        "oldval        = %" PRIXPTR "\n"
			        "masked_oldval = %" PRIXPTR "\n"
			        "mask          = %" PRIXPTR,
			        (physpage_t)(self->mz_start + zone_relative_base),
			        oldval, oldval & PMEMBITSET_FREEMASK, mask);
			num_qpages += POPCOUNT(oldval & (mask << (PMEMZONE_ISUNDFBIT - PMEMZONE_ISFREEBIT)));
			num_pages -= num_free;
			assert(!num_pages ||
			       !((zone_relative_base + num_free) & (PAGES_PER_WORD - 1)));
			++i;
		}
		while (num_pages >= PAGES_PER_WORD) {
			/* Free full words. */
			oldval = ATOMIC_FETCHOR(self->mz_free[i], PMEMBITSET_FREEMASK);
			assertf(!(oldval & PMEMBITSET_FREEMASK),
			        "Double free at near %" PRIpN(__SIZEOF_PHYSPAGE_T__) "\n"
			        "oldval      = %" PRIXPTR "\n"
			        "mask_oldval = %" PRIXPTR,
			        (physpage_t)(self->mz_start + (i * PAGES_PER_WORD)),
			        oldval, oldval & PMEMBITSET_FREEMASK);
			num_qpages += POPCOUNT(oldval & PMEMBITSET_UNDFMASK);
			num_pages -= PAGES_PER_WORD;
			++i;
		}
		/* Mark trailing pages as free. */
		if (num_pages) {
			mask = PMEMBITSET_FREEMASK;
			mask &= ((uintptr_t)1 << ((unsigned int)num_pages * PMEMZONE_BITSPERPAGE)) - 1;
			oldval = ATOMIC_FETCHOR(self->mz_free[i], mask);
			assertf(!(oldval & mask),
			        "Double free at near %" PRIpN(__SIZEOF_PHYSPAGE_T__) "\n"
			        "oldval        = %" PRIXPTR "\n"
			        "masked_oldval = %" PRIXPTR "\n"
			        "mask          = %" PRIXPTR,
			        (physpage_t)(self->mz_start + (i * PAGES_PER_WORD)),
			        oldval, oldval & PMEMBITSET_FREEMASK, mask);
			num_qpages += POPCOUNT(oldval & (mask << (PMEMZONE_ISUNDFBIT - PMEMZONE_ISFREEBIT)));
		}
	}
	if (num_qpages)
		ATOMIC_FETCHADD(self->mz_qfree, num_qpages);
}


#ifdef NDEBUG
#define ASSIGN_OLDVAL                /* nothing */
#define ASSIGN_OLDVAL_ATOMIC_FETCHOR ATOMIC_OR
#else /* NDEBUG */
#define ASSIGN_OLDVAL                oldval =
#define ASSIGN_OLDVAL_ATOMIC_FETCHOR oldval = ATOMIC_FETCHOR
#endif /* !NDEBUG */

PRIVATE NOBLOCK void
NOTHROW(KCALL zone_free)(struct pmemzone *__restrict self,
                         physpage_t zone_relative_base,
                         physpagecnt_t num_pages) {
	size_t i;
	uintptr_t mask;
#ifndef NDEBUG
	uintptr_t oldval;
#endif /* !NDEBUG */
	assert(num_pages);
	assert(zone_relative_base + num_pages > zone_relative_base);
	assert(zone_relative_base + num_pages - 1 <= self->mz_rmax);
	ATOMIC_FETCHADD(self->mz_cfree, num_pages);
	ATOMIC_FETCHADD(self->mz_qfree, num_pages);
	pmemzone_set_fmax(self, zone_relative_base + num_pages - 1);
	i = (size_t)(zone_relative_base / PAGES_PER_WORD);
	if (num_pages == 1) {
		mask = (uintptr_t)(PMEMZONE_ISFREEMASK | PMEMZONE_ISUNDFBIT)
		       << (unsigned int)((zone_relative_base % PAGES_PER_WORD) *
		                         PMEMZONE_BITSPERPAGE);
		ASSIGN_OLDVAL_ATOMIC_FETCHOR(self->mz_free[i], mask);
		assertf(!(oldval & (mask & PMEMBITSET_FREEMASK)),
		        "Double free at %" PRIpN(__SIZEOF_PHYSPAGE_T__),
		        (physpage_t)(self->mz_start + zone_relative_base));
	} else {
		/* free partial pages. */
		unsigned int misalignment, num_free;
		misalignment = (unsigned int)(zone_relative_base % PAGES_PER_WORD);
		if (misalignment) {
			num_free = (PAGES_PER_WORD - misalignment);
			mask     = (PMEMBITSET_FREEMASK | PMEMBITSET_UNDFMASK);
			if ((physpagecnt_t)num_free > num_pages) {
				num_free = (unsigned int)num_pages;
				mask &= (((uintptr_t)1 << (num_free * PMEMZONE_BITSPERPAGE)) - 1);
			}
			mask <<= misalignment * PMEMZONE_BITSPERPAGE;
			ASSIGN_OLDVAL_ATOMIC_FETCHOR(self->mz_free[i], mask);
			assertf(!(oldval & (mask & PMEMBITSET_FREEMASK)),
			        "Double free at near %" PRIpN(__SIZEOF_PHYSPAGE_T__) "\n"
			        "oldval        = %" PRIXPTR "\n"
			        "masked_oldval = %" PRIXPTR "\n"
			        "mask          = %" PRIXPTR,
			        (physpage_t)(self->mz_start + zone_relative_base),
			        oldval, oldval & PMEMBITSET_FREEMASK,
			        mask & PMEMBITSET_FREEMASK);
			num_pages -= num_free;
			assert(!num_pages ||
			       !((zone_relative_base + num_free) & (PAGES_PER_WORD - 1)));
			++i;
		}
		while (num_pages >= PAGES_PER_WORD) {
			/* Free full words. */
			ASSIGN_OLDVAL_ATOMIC_FETCHOR(self->mz_free[i],
			                             (PMEMBITSET_FREEMASK |
			                              PMEMBITSET_UNDFMASK));
			assertf(!(oldval & PMEMBITSET_FREEMASK),
			        "Double free at near %" PRIpN(__SIZEOF_PHYSPAGE_T__) "\n"
			        "oldval      = %" PRIXPTR "\n"
			        "mask_oldval = %" PRIXPTR,
			        (physpage_t)(self->mz_start + (i * PAGES_PER_WORD)),
			        oldval, oldval & PMEMBITSET_FREEMASK);
			num_pages -= PAGES_PER_WORD;
			++i;
		}
#if 1
		/* Mark trailing pages as free. */
		if (num_pages) {
			mask = (PMEMBITSET_FREEMASK | PMEMBITSET_UNDFMASK);
			mask &= ((uintptr_t)1 << ((unsigned int)num_pages * PMEMZONE_BITSPERPAGE)) - 1;
			ASSIGN_OLDVAL_ATOMIC_FETCHOR(self->mz_free[i], mask);
			assertf(!(oldval & (mask & PMEMBITSET_FREEMASK)),
			        "Double free at near %" PRIpN(__SIZEOF_PHYSPAGE_T__) "\n"
			        "oldval        = %" PRIXPTR "\n"
			        "masked_oldval = %" PRIXPTR "\n"
			        "mask          = %" PRIXPTR,
			        (physpage_t)(self->mz_start + (i * PAGES_PER_WORD)),
			        oldval, oldval & PMEMBITSET_FREEMASK,
			        mask & PMEMBITSET_FREEMASK);
		}
#endif
	}
}
#undef ASSIGN_OLDVAL

#ifndef NDEBUG
#define set_cfree_word(pword, mask) \
	set_cfree_word(pword, mask, self)
#endif /* !NDEBUG */

#ifndef NDEBUG
PRIVATE NOBLOCK void
NOTHROW(KCALL set_cfree_word)(uintptr_t *__restrict pword,
                              uintptr_t mask,
                              struct pmemzone *__restrict self)
#else /* !NDEBUG */
PRIVATE NOBLOCK void
NOTHROW(KCALL set_cfree_word)(uintptr_t *__restrict pword,
                              uintptr_t mask)
#endif /* NDEBUG */
{
	uintptr_t oldval;
	do {
		oldval = ATOMIC_READ(*pword);
	} while (!ATOMIC_CMPXCH_WEAK(*pword, oldval,
	                             (oldval & ~mask) |
	                             (PMEMBITSET_FREEMASK & mask)));
	assertf(!(oldval & (mask & PMEMBITSET_FREEMASK)),
	        "Double free near %" PRIpN(__SIZEOF_PHYSPAGE_T__) "\n"
	        "oldval        = %" PRIXPTR "\n"
	        "masked_oldval = %" PRIXPTR "\n"
	        "mask          = %" PRIXPTR,
	        (physpage_t)(self->mz_start + (physpagecnt_t)(pword - self->mz_free) * PAGES_PER_WORD),
	        oldval, oldval & PMEMBITSET_FREEMASK,
	        mask & PMEMBITSET_FREEMASK);
}

PRIVATE NOBLOCK void
NOTHROW(KCALL zone_cfree)(struct pmemzone *__restrict self,
                          physpage_t zone_relative_base,
                          physpagecnt_t num_pages) {
	size_t i;
	uintptr_t mask;
	assert(num_pages);
	assert(zone_relative_base + num_pages > zone_relative_base);
	assert(zone_relative_base + num_pages - 1 <= self->mz_rmax);
	ATOMIC_FETCHADD(self->mz_cfree, num_pages);
	pmemzone_set_fmax(self, zone_relative_base + num_pages - 1);
	i = (size_t)(zone_relative_base / PAGES_PER_WORD);
	if (num_pages == 1) {
		mask = (uintptr_t)PMEMZONE_ISFREEMASK
		       << (unsigned int)((zone_relative_base % PAGES_PER_WORD) *
		                         PMEMZONE_BITSPERPAGE);
		set_cfree_word(&self->mz_free[i], mask);
	} else {
		/* free partial pages. */
		unsigned int misalignment, num_free;
		misalignment = (unsigned int)(zone_relative_base & (PAGES_PER_WORD - 1));
		if (misalignment) {
			num_free = (PAGES_PER_WORD - misalignment);
			mask     = PMEMBITSET_FREEMASK;
			if ((physpagecnt_t)num_free > num_pages) {
				num_free = (unsigned int)num_pages;
				mask &= (((uintptr_t)1 << (num_free * PMEMZONE_BITSPERPAGE)) - 1);
			}
			mask <<= misalignment * PMEMZONE_BITSPERPAGE;
			set_cfree_word(&self->mz_free[i], mask);
			num_pages -= num_free;
			assert(!num_pages ||
			       !((zone_relative_base + num_free) & (PAGES_PER_WORD - 1)));
			++i;
		}
		while (num_pages >= PAGES_PER_WORD) {
			/* Free full words. */
			set_cfree_word(&self->mz_free[i], PMEMBITSET_FREEMASK);
			num_pages -= PAGES_PER_WORD;
			++i;
		}
		/* Mark trailing pages as free. */
		if (num_pages) {
			mask = PMEMBITSET_FREEMASK;
			mask &= ((uintptr_t)1 << ((unsigned int)num_pages * PMEMZONE_BITSPERPAGE)) - 1;
			set_cfree_word(&self->mz_free[i], mask);
		}
	}
}




#if !defined(NDEBUG) && 0 /* This isn't thread-safe */
#define assert_free(base, num_pages)                                     \
	{                                                                    \
		physpagecnt_t i;                                                 \
		for (i = 0; i < (num_pages); ++i) {                              \
			assertf(page_isfree((base) + i),                             \
			        "Page at %" PRIpN(__SIZEOF_PHYSADDR_T__) " of "      \
			        "%" PRIpN(__SIZEOF_PHYSADDR_T__) "..."               \
			        "%" PRIpN(__SIZEOF_PHYSADDR_T__) " was not freed\n", \
			        physpage2addr((base) + i),                           \
			        physpage2addr(base),                                 \
			        physpage2addr((base) + (num_pages)) - 1);            \
		}                                                                \
	}
#else
#define assert_free(base, num_pages) (void)0
#endif


PUBLIC NOBLOCK void
NOTHROW(KCALL page_freeone)(physpage_t page) {
#ifdef IGNORE_FREE
	(void)page;
#else /* IGNORE_FREE */
	struct pmemzone *zone;
	size_t i;
	unsigned int j;
	uintptr_t mask;
#ifndef NDEBUG
	uintptr_t oldval;
#endif /* !NDEBUG */
	for (zone = mzones.pm_last;; zone = zone->mz_prev) {
		assertf(zone, "Untracked page %" PRIpN(__SIZEOF_PHYSPAGE_T__), page);
		if (page < zone->mz_start)
			continue;
		if (page > zone->mz_max)
			continue;
		TRACE_FREE(zone, page, page);
		page -= zone->mz_start;
		i = (size_t)(page / PAGES_PER_WORD);
		j = (unsigned int)(page % PAGES_PER_WORD);
		ATOMIC_INC(zone->mz_cfree);
		ATOMIC_INC(zone->mz_qfree);
		mask = (uintptr_t)(PMEMZONE_ISFREEMASK | PMEMZONE_ISUNDFMASK)
		       << (j * PMEMZONE_BITSPERPAGE);
#ifndef NDEBUG
		oldval = ATOMIC_FETCHOR(zone->mz_free[i], mask);
		assertf(!(oldval & (mask & PMEMBITSET_FREEMASK)),
		        "Double free at %" PRIpN(__SIZEOF_PHYSPAGE_T__),
		        (physpage_t)page);
#else /* !NDEBUG */
		ATOMIC_OR(zone->mz_free[i], mask);
#endif /* NDEBUG */
		assert_free(page + zone->mz_start, 1);
		break;
	}
#endif /* !IGNORE_FREE */
}


/* Free a given physical address range.
 * The caller is responsible to ensure that the given range has previously been allocated. */
PUBLIC NOBLOCK void
NOTHROW(KCALL page_free)(physpage_t base, physpagecnt_t num_pages) {
#ifdef IGNORE_FREE
	(void)base;
	(void)num_pages;
#elif 0
	while (num_pages--) {
		page_freeone(base);
		++base;
	}
#else
	physpage_t max_page;
	struct pmemzone *zone;
	if unlikely(!num_pages)
		return;
	max_page = base + num_pages - 1;
	zone     = mzones.pm_last;
	for (;;) {
		if (base <= zone->mz_max) {
			assert(max_page <= zone->mz_max);
			if (base >= zone->mz_start) {
				/* The remainder of the section to-be freed is located within this zone */
				TRACE_FREE(zone, base, base + num_pages - 1);
				zone_free(zone,
				          base - zone->mz_start,
				          num_pages);
				break;
			}
#if 0
			zone_free(zone, 0,
			          (base + num_pages) -
			          zone->mz_start);
			num_pages = zone->mz_start - base;
			assert(num_pages != 0);
#endif
		}
		assert(zone->mz_prev);
		zone = zone->mz_prev;
	}
	assert_free(base, num_pages);
#endif /* !IGNORE_FREE */
}

PUBLIC NOBLOCK void
NOTHROW(KCALL page_cfree)(physpage_t base, physpagecnt_t num_pages) {
#ifdef IGNORE_FREE
	(void)base;
	(void)num_pages;
#else /* IGNORE_FREE */
	physpage_t max_page;
	struct pmemzone *zone;
	if (!num_pages)
		return;
	max_page = base + num_pages - 1;
	zone     = mzones.pm_last;
	for (;;) {
		if (base <= zone->mz_max) {
			assert(max_page <= zone->mz_max);
			if (base >= zone->mz_start) {
				/* The remainder of the section to-be freed is located within this zone */
				TRACE_FREE(zone, base, base + num_pages - 1);
				zone_cfree(zone,
				           base - zone->mz_start,
				           num_pages);
				break;
			}
#if 0
			zone_cfree(zone, 0,
			           (base + num_pages) -
			           zone->mz_start);
			num_pages = zone->mz_start - base;
			assert(num_pages != 0);
#endif
		}
		assert(zone->mz_prev);
		zone = zone->mz_prev;
	}
	assert_free(base, num_pages);
#endif /* !IGNORE_FREE */
}

PUBLIC NOBLOCK void
NOTHROW(KCALL page_ffree)(physpage_t base, physpagecnt_t num_pages,
                           bool is_zero) {
#ifdef IGNORE_FREE
	(void)base;
	(void)num_pages;
	(void)is_zero;
#else /* IGNORE_FREE */
	if (is_zero) {
		page_cfree(base, num_pages);
	} else {
		page_free(base, num_pages);
	}
#endif /* !IGNORE_FREE */
}

PUBLIC NOBLOCK void
NOTHROW(KCALL page_ccfree)(physpage_t base, physpagecnt_t num_pages) {
#ifdef IGNORE_FREE
	(void)base;
	(void)num_pages;
#else /* IGNORE_FREE */
	physpage_t max_page;
	struct pmemzone *zone;
	if (!num_pages)
		return;
	max_page = base + num_pages - 1;
	zone     = mzones.pm_last;
	for (;;) {
		if (base <= zone->mz_max) {
			assert(max_page <= zone->mz_max);
			if (base >= zone->mz_start) {
				/* The remainder of the section to-be freed is located within this zone */
				TRACE_FREE(zone, base, base + num_pages - 1);
				zone_free_keepz(zone,
				                base - zone->mz_start,
				                num_pages);
				break;
			}
#if 0
			zone_free_keepz(zone, 0,
			                (base + num_pages) -
			                zone->mz_start);
			num_pages = zone->mz_start - base;
			assert(num_pages != 0);
#endif
		}
		assert(zone->mz_prev);
		zone = zone->mz_prev;
	}
	assert_free(base, num_pages);
#endif /* !IGNORE_FREE */
}




PRIVATE NOBLOCK WUNUSED NONNULL((1)) physpage_t
NOTHROW(KCALL zone_mallocone_between)(struct pmemzone *__restrict self,
                                       physpage_t zone_relative_min,
                                       physpage_t zone_relative_max,
                                       bool out_of_bounds_is_ok);
PRIVATE NOBLOCK WUNUSED NONNULL((1, 6)) physpage_t
NOTHROW(KCALL zone_malloc_part_between)(struct pmemzone *__restrict self,
                                         physpage_t zone_relative_min,
                                         physpage_t zone_relative_max,
                                         physpagecnt_t min_pages,
                                         physpagecnt_t max_pages,
                                         physpagecnt_t *__restrict res_pages,
                                         bool out_of_bounds_is_ok);
PRIVATE NOBLOCK WUNUSED NONNULL((1)) physpage_t
NOTHROW(KCALL zone_malloc_between)(struct pmemzone *__restrict self,
                                    physpage_t zone_relative_min,
                                    physpage_t zone_relative_max,
                                    physpagecnt_t num_pages,
                                    bool out_of_bounds_is_ok);
PRIVATE NOBLOCK WUNUSED NONNULL((1)) physpage_t
NOTHROW(KCALL zone_mallocone_before)(struct pmemzone *__restrict self,
                                      physpage_t zone_relative_max);
PRIVATE NOBLOCK WUNUSED NONNULL((1, 5)) physpage_t
NOTHROW(KCALL zone_malloc_part_before)(struct pmemzone *__restrict self,
                                        physpage_t zone_relative_max,
                                        physpagecnt_t min_pages,
                                        physpagecnt_t max_pages,
                                        physpagecnt_t *__restrict res_pages);
PRIVATE NOBLOCK WUNUSED NONNULL((1)) physpage_t
NOTHROW(KCALL zone_malloc_before)(struct pmemzone *__restrict self,
                                   physpage_t zone_relative_max,
                                   physpagecnt_t num_pages);

#if !defined(NDEBUG) && 1
#define assert_allocation(base, num_pages)                                                                             \
	{                                                                                                                  \
		physpagecnt_t i;                                                                                                   \
		for (i = 0; i < (num_pages); ++i) {                                                                            \
			assertf(!page_isfree((base) + i),                                                                          \
			        "Page at " PRIpN(__SIZEOF_PHYSADDR_T__) " of " PRIpN(__SIZEOF_PHYSADDR_T__) "..." PRIpN(__SIZEOF_PHYSADDR_T__) " was not allocated\n", \
			        (physaddr_t)((base) + i) * PAGESIZE,                                                                \
			        (physaddr_t)(base)*PAGESIZE,                                                                        \
			        (physaddr_t)((base) + (num_pages)) * PAGESIZE - 1);                                                 \
		}                                                                                                              \
	}
#else
#define assert_allocation(base, num_pages) (void)0
#endif


/* Allocate `num_pages' continuous pages of physical memory and return their page number.
 * WARNING: Physical   memory   cannot   be   dereferenced   prior   to   being   mapped.
 * @return: * :              The starting page number of the newly allocated memory range.
 * @return: PHYSPAGE_INVALID: The allocation failed. */
PUBLIC NOBLOCK WUNUSED physpage_t
NOTHROW(KCALL page_malloc)(physpagecnt_t num_pages) {
	physpage_t result, free_max;
	struct pmemzone *zone;
	syscache_version_t version = SYSCACHE_VERSION_INIT;
again:
	zone = mzones.pm_last;
	do {
		if (zone->mz_cfree < num_pages)
			continue; /* Zone is too small. */
		/* Search this zone. */
		free_max = ATOMIC_READ(zone->mz_fmax);
		if ((physpagecnt_t)free_max >= num_pages) {
			result = zone_malloc_before(zone, free_max, num_pages);
			if (result != PHYSPAGE_INVALID) {
				assert_allocation(result + zone->mz_start, num_pages);
				TRACE_ALLOC(zone,
				            result + zone->mz_start,
				            result + zone->mz_start + num_pages - 1);
				ATOMIC_CMPXCH(zone->mz_fmax, free_max,
				              result ? result - 1
				                     : zone->mz_rmax);
				return result + zone->mz_start;
			}
			result = zone_malloc_between(zone, free_max, zone->mz_rmax, num_pages, true);
		} else {
			result = zone_malloc_before(zone, zone->mz_rmax, num_pages);
		}
		if (result != PHYSPAGE_INVALID) {
			assert_allocation(result + zone->mz_start, num_pages);
			TRACE_ALLOC(zone,
			            result + zone->mz_start,
			            result + zone->mz_start + num_pages - 1);
			ATOMIC_CMPXCH(zone->mz_fmax, free_max,
			              result ? result - 1
			                     : zone->mz_rmax);
			return result + zone->mz_start;
		}
	} while ((zone = zone->mz_prev) != NULL);
	/* TODO: Don't do  this in  here unconditionally,  but expose  a  secondary
	 *       interface that does the allocation while possibly clearing caches!
	 * I totally forgot  that this happens  in here, and  there are many  places
	 * that aren't designed to efficiently deal with system caches being cleared
	 * in this manner! */
	if (syscache_clear_s(&version))
		goto again;
	return PHYSPAGE_INVALID;
}

/* Allocate `num_pages' continuous pages of physical memory and return their page number.
 * WARNING: Physical   memory   cannot   be   dereferenced   prior   to   being   mapped.
 * @return: * :               The starting page number of the newly allocated memory range.
 * @return: PHYSPAGE_INVALID: The allocation failed. */
PUBLIC NOBLOCK WUNUSED physpage_t
NOTHROW(KCALL page_mallocone)(void) {
	physpage_t result, free_max;
	struct pmemzone *zone;
	syscache_version_t version = SYSCACHE_VERSION_INIT;
again:
	zone = mzones.pm_last;
	do {
		if unlikely(!zone->mz_cfree)
			continue; /* Zone is too small. */
		/* Search this zone. */
		free_max = ATOMIC_READ(zone->mz_fmax);
		if likely((physpagecnt_t)free_max >= 1) {
			result = zone_mallocone_before(zone, free_max);
			if likely(result != PHYSPAGE_INVALID) {
				assert_allocation(result + zone->mz_start, 1);
				TRACE_ALLOC(zone,
				            result + zone->mz_start,
				            result + zone->mz_start);
				ATOMIC_CMPXCH(zone->mz_fmax, free_max,
				              result ? result - 1
				                     : zone->mz_rmax);
				return result + zone->mz_start;
			}
			result = zone_mallocone_between(zone, free_max, zone->mz_rmax, true);
		} else {
			result = zone_mallocone_before(zone, zone->mz_rmax);
		}
		if (result != PHYSPAGE_INVALID) {
			assert_allocation(result + zone->mz_start, 1);
			TRACE_ALLOC(zone,
			            result + zone->mz_start,
			            result + zone->mz_start);
			ATOMIC_CMPXCH(zone->mz_fmax, free_max,
			              result ? result - 1
			                     : zone->mz_rmax);
			return result + zone->mz_start;
		}
	} while ((zone = zone->mz_prev) != NULL);
	/* TODO: Don't do  this in  here unconditionally,  but expose  a  secondary
	 *       interface that does the allocation while possibly clearing caches!
	 * I totally forgot  that this happens  in here, and  there are many  places
	 * that aren't designed to efficiently deal with system caches being cleared
	 * in this manner! */
	if (syscache_clear_s(&version))
		goto again;
	return PHYSPAGE_INVALID;
}

/* Allocate  at  least  `min_pages', and  at  most `max_pages',
 * writing the actual number of pages allocated to `res_pages'.
 *  - This function  will try  to serve  the request  to allocate  `max_pages',
 *    but will prefer to return the first block of free consecutive pages  with
 *    a length of at least `min_pages', thus preventing memory fragmentation by
 *    using  up small memory blocks that might otherwise continue going unused.
 * @return: * :              The starting page number of the newly allocated memory range.
 * @return: PHYSPAGE_INVALID: The allocation failed. */
PUBLIC NOBLOCK WUNUSED NONNULL((3)) physpage_t
NOTHROW(KCALL page_malloc_part)(physpagecnt_t min_pages, physpagecnt_t max_pages,
                                physpagecnt_t *__restrict res_pages) {
	physpage_t result, free_max;
	struct pmemzone *zone;
	syscache_version_t version = SYSCACHE_VERSION_INIT;
#ifdef ALLOCATE_MIN_PARTS
	max_pages = min_pages;
#elif defined(ALLOCATE_MIN_PARTS_RANDOMIZE)
	if (max_pages > min_pages &&
	    ALLOCATE_MIN_PARTS_RANDOMIZE_CHANCE()) {
		physpagecnt_t new_count;
		new_count = min_pages + (krand() % ((max_pages - min_pages) + 1));
		assert(new_count >= min_pages);
		assert(new_count <= max_pages);
		max_pages = new_count;
	}
#endif
again:
	zone = mzones.pm_last;
	do {
		if unlikely(zone->mz_cfree < min_pages)
			continue; /* Zone is too small. */
		/* Search this zone. */
		free_max = ATOMIC_READ(zone->mz_fmax);
		if likely((physpagecnt_t)free_max >= min_pages) {
#ifndef NDEBUG
			*res_pages = (physpagecnt_t)-1;
#endif /* !NDEBUG */
			result = zone_malloc_part_before(zone,
			                                 free_max,
			                                 min_pages,
			                                 max_pages,
			                                 res_pages);
			if likely(result != PHYSPAGE_INVALID) {
				assertf(*res_pages >= min_pages && *res_pages <= max_pages,
				        "Bad *res_pages value: %" PRIpN(__SIZEOF_PHYSPAGE_T__) "\n"
				        "result = %" PRIpN(__SIZEOF_PHYSPAGE_T__),
				        *res_pages, result);
				TRACE_ALLOC(zone,
				            result + zone->mz_start,
				            result + zone->mz_start + *res_pages - 1);
				assert_allocation(result + zone->mz_start, *res_pages);
				ATOMIC_CMPXCH(zone->mz_fmax, free_max,
				              result ? result - 1
				                     : zone->mz_rmax);
				return result + zone->mz_start;
			}
#ifndef NDEBUG
			*res_pages = (physpagecnt_t)-1;
#endif /* !NDEBUG */
			result = zone_malloc_part_between(zone,
			                                  free_max,
			                                  zone->mz_rmax,
			                                  min_pages,
			                                  max_pages,
			                                  res_pages,
			                                  true);
		} else {
#ifndef NDEBUG
			*res_pages = (physpagecnt_t)-1;
#endif /* !NDEBUG */
			result = zone_malloc_part_before(zone,
			                                 zone->mz_rmax,
			                                 min_pages,
			                                 max_pages,
			                                 res_pages);
		}
		if (result != PHYSPAGE_INVALID) {
			assertf(*res_pages >= min_pages && *res_pages <= max_pages,
			        "Bad *res_pages value: %" PRIpN(__SIZEOF_PHYSPAGE_T__) "\n"
			        "result = %" PRIpN(__SIZEOF_PHYSPAGE_T__),
			        *res_pages, result);
			TRACE_ALLOC(zone,
			            result + zone->mz_start,
			            result + zone->mz_start + *res_pages - 1);
			assert_allocation(result + zone->mz_start, *res_pages);
			ATOMIC_CMPXCH(zone->mz_fmax, free_max,
			              result ? result - 1
			                     : zone->mz_rmax);
			return result + zone->mz_start;
		}
	} while ((zone = zone->mz_prev) != NULL);
	/* TODO: Don't do  this in  here unconditionally,  but expose  a  secondary
	 *       interface that does the allocation while possibly clearing caches!
	 * I totally forgot  that this happens  in here, and  there are many  places
	 * that aren't designed to efficiently deal with system caches being cleared
	 * in this manner! */
	if (syscache_clear_s(&version))
		goto again;
	return PHYSPAGE_INVALID;
}


/* Try to allocate the given page.
 * @return: * : One of `PAGE_MALLOC_AT_*' */
PUBLIC NOBLOCK WUNUSED unsigned int
NOTHROW(KCALL page_malloc_at)(physpage_t ptr) {
	struct pmemzone *zone;
again:
	zone = mzones.pm_last;
	do {
		if (ptr >= zone->mz_start && ptr <= zone->mz_max) {
			size_t i;
			uintptr_t mask, oldval;
			unsigned int j;
			ptr -= zone->mz_start;
			i      = (size_t)(ptr / PAGES_PER_WORD);
			j      = (unsigned int)(ptr % PAGES_PER_WORD);
			mask   = (uintptr_t)PMEMZONE_ISFREEMASK << (j * PMEMZONE_BITSPERPAGE);
			oldval = ATOMIC_FETCHAND(zone->mz_free[i], ~mask);
			if (!(oldval & mask))
				return PAGE_MALLOC_AT_NOTFREE; /* Page was already allocated */
			TRACE_ALLOC(zone, ptr ,ptr);
			ATOMIC_DEC(zone->mz_cfree);
			if (oldval & (mask << (PMEMZONE_ISUNDFBIT - PMEMZONE_ISFREEBIT)))
				ATOMIC_DEC(zone->mz_qfree);
			return PAGE_MALLOC_AT_SUCCESS;
		}
	} while ((zone = zone->mz_prev) != NULL);
	if (syscache_clear())
		goto again;
	return PAGE_MALLOC_AT_NOTMAPPED;
}


/* Similar to  `page_malloc()'  /  `page_malloc_part()',  but  only
 * allocate memory from between the two given page addresses,  such
 * that all allocated pages are located within the specified range.
 * @assume(return == PHYSPAGE_INVALID ||
 *        (return >= min_page &&
 *         return + num_pages - 1 <= max_page)); */
PUBLIC NOBLOCK WUNUSED physpage_t
NOTHROW(KCALL page_malloc_between)(physpage_t min_page, physpage_t max_page,
                                   physpagecnt_t num_pages) {
	physpagecnt_t num;
	physpage_t result;
#ifndef NDEBUG
	num = (physpagecnt_t)-1;
#endif /* !NDEBUG */
	result = page_malloc_part_between(min_page,
	                                  max_page,
	                                  num_pages,
	                                  num_pages,
	                                  &num);
	assert(result == PHYSPAGE_INVALID || num == num_pages);
	return result;
}

PUBLIC NOBLOCK WUNUSED NONNULL((5)) physpage_t
NOTHROW(KCALL page_malloc_part_between)(physpage_t min_page, physpage_t max_page,
                                        physpagecnt_t min_pages, physpagecnt_t max_pages,
                                        physpagecnt_t *__restrict res_pages) {
	physpage_t result, free_max;
	struct pmemzone *zone;
	syscache_version_t version = SYSCACHE_VERSION_INIT;
#ifdef ALLOCATE_MIN_PARTS
	max_pages = min_pages;
#elif defined(ALLOCATE_MIN_PARTS_RANDOMIZE)
	if (max_pages > min_pages &&
	    ALLOCATE_MIN_PARTS_RANDOMIZE_CHANCE()) {
		physpagecnt_t new_count;
		new_count = min_pages + (krand() % ((max_pages - min_pages) + 1));
		assert(new_count >= min_pages);
		assert(new_count <= max_pages);
		max_pages = new_count;
	}
#endif
again:
	zone = mzones.pm_last;
	do {
		physpage_t relative_min_page;
		physpage_t relative_max_page;

		if (zone->mz_cfree < min_pages)
			continue; /* Zone is too small. */
		if (zone->mz_start > max_page)
			continue; /* Zone doesn't contain any allowed pages. */
		if (zone->mz_rmax < min_page)
			break; /* All potential zones have been checked. */
		relative_min_page = min_page <= zone->mz_start ? 0 : min_page - zone->mz_start;
		relative_max_page = max_page >= zone->mz_max ? zone->mz_rmax : max_page - zone->mz_start;

		if (relative_min_page == 0) {
			/* Search this zone. */
			free_max = ATOMIC_READ(zone->mz_fmax);
			if (free_max > relative_max_page)
				free_max = relative_max_page;
			if ((physpagecnt_t)free_max >= min_pages) {
#ifndef NDEBUG
				*res_pages = (physpagecnt_t)-1;
#endif /* !NDEBUG */
				result = zone_malloc_part_before(zone, free_max, min_pages, max_pages, res_pages);
				if (result != PHYSPAGE_INVALID) {
					assertf(*res_pages >= min_pages && *res_pages <= max_pages,
					        "Bad *res_pages value: %" PRIpN(__SIZEOF_PHYSPAGE_T__) "\n"
					        "result = %" PRIpN(__SIZEOF_PHYSPAGE_T__),
					        *res_pages, result);
					TRACE_ALLOC(zone,
					            result + zone->mz_start,
					            result + zone->mz_start + *res_pages - 1);
					assert_allocation(result + zone->mz_start, *res_pages);
					ATOMIC_CMPXCH(zone->mz_fmax, free_max,
					              result ? result - 1
					                     : zone->mz_rmax);
					assert(result + *res_pages - 1 <= free_max);
					assert(result + zone->mz_start >= min_page);
					assert(result + zone->mz_start + *res_pages - 1 <= max_page);
					return result + zone->mz_start;
				}
				if (free_max < relative_max_page) {
#ifndef NDEBUG
					*res_pages = (physpagecnt_t)-1;
#endif /* !NDEBUG */
					result = zone_malloc_part_between(zone, free_max, relative_max_page, min_pages, max_pages, res_pages, false);
				}
			} else {
#ifndef NDEBUG
				*res_pages = (physpagecnt_t)-1;
#endif /* !NDEBUG */
				result = zone_malloc_part_before(zone, relative_max_page, min_pages, max_pages, res_pages);
			}
			if (result != PHYSPAGE_INVALID) {
				assertf(*res_pages >= min_pages && *res_pages <= max_pages,
				        "Bad *res_pages value: %" PRIpN(__SIZEOF_PHYSPAGE_T__) "\n"
				        "result = %" PRIpN(__SIZEOF_PHYSPAGE_T__),
				        *res_pages, result);
				TRACE_ALLOC(zone,
				            result + zone->mz_start,
				            result + zone->mz_start + *res_pages - 1);
				assert_allocation(result + zone->mz_start, *res_pages);
				ATOMIC_CMPXCH(zone->mz_fmax, free_max,
				              result ? result - 1
				                     : zone->mz_rmax);
				assert(result + zone->mz_start >= min_page);
				assert(result + zone->mz_start + *res_pages - 1 <= max_page);
				return result + zone->mz_start;
			}
		} else {
			/* Search this zone. */
			free_max = ATOMIC_READ(zone->mz_fmax);
			if (free_max > relative_max_page)
				free_max = relative_max_page;
			if ((physpagecnt_t)free_max >= min_pages) {
#ifndef NDEBUG
				*res_pages = (physpagecnt_t)-1;
#endif /* !NDEBUG */
				result = zone_malloc_part_between(zone, relative_min_page, free_max, min_pages, max_pages, res_pages, false);
				if (result != PHYSPAGE_INVALID) {
					assertf(*res_pages >= min_pages && *res_pages <= max_pages,
					        "Bad *res_pages value: %" PRIpN(__SIZEOF_PHYSPAGE_T__) "\n"
					        "result = %" PRIpN(__SIZEOF_PHYSPAGE_T__),
					        *res_pages, result);
					TRACE_ALLOC(zone,
					            result + zone->mz_start,
					            result + zone->mz_start + *res_pages - 1);
					assert_allocation(result + zone->mz_start, *res_pages);
					ATOMIC_CMPXCH(zone->mz_fmax, free_max,
					              result ? result - 1
					                     : zone->mz_rmax);
					assert(result + zone->mz_start >= min_page);
					assert(result + zone->mz_start + *res_pages - 1 <= max_page);
					return result + zone->mz_start;
				}
				if (free_max < relative_min_page)
					free_max = relative_min_page;
				if (free_max < relative_max_page) {
#ifndef NDEBUG
					*res_pages = (physpagecnt_t)-1;
#endif /* !NDEBUG */
					result = zone_malloc_part_between(zone, free_max, relative_max_page, min_pages, max_pages, res_pages, false);
				}
			} else {
#ifndef NDEBUG
				*res_pages = (physpagecnt_t)-1;
#endif /* !NDEBUG */
				result = zone_malloc_part_between(zone, relative_min_page, relative_max_page, min_pages, max_pages, res_pages, false);
			}
			if (result != PHYSPAGE_INVALID) {
				assertf(*res_pages >= min_pages && *res_pages <= max_pages,
				        "Bad *res_pages value: %" PRIpN(__SIZEOF_PHYSPAGE_T__) "\n"
				        "result = %" PRIpN(__SIZEOF_PHYSPAGE_T__),
				        *res_pages, result);
				TRACE_ALLOC(zone,
				            result + zone->mz_start,
				            result + zone->mz_start + *res_pages - 1);
				assert_allocation(result + zone->mz_start, *res_pages);
				assert(result + zone->mz_start >= min_page);
				assert(result + zone->mz_start + *res_pages - 1 <= max_page);
				ATOMIC_CMPXCH(zone->mz_fmax, free_max,
				              result ? result - 1
				                     : zone->mz_rmax);
				return result + zone->mz_start;
			}
		}

	} while ((zone = zone->mz_prev) != NULL);
	/* TODO: Don't do  this in  here unconditionally,  but expose  a  secondary
	 *       interface that does the allocation while possibly clearing caches!
	 * I totally forgot  that this happens  in here, and  there are many  places
	 * that aren't designed to efficiently deal with system caches being cleared
	 * in this manner! */
	if (syscache_clear_s(&version))
		goto again;
	return PHYSPAGE_INVALID;
}


/* Check if a given `page' is current free.
 * NOTE: Returns `false' when `page_ismapped(page, 1)' is false. */
PUBLIC NOBLOCK WUNUSED bool
NOTHROW(KCALL page_isfree)(physpage_t page) {
	struct pmemzone *zone;
	zone = mzones.pm_last;
	do {
		if (page >= zone->mz_start && page <= zone->mz_max) {
			size_t i;
			unsigned int j;
			uintptr_t mask;
			page -= zone->mz_start;
			i    = (size_t)(page / PAGES_PER_WORD);
			j    = (unsigned int)(page % PAGES_PER_WORD);
			mask = (uintptr_t)PMEMZONE_ISFREEMASK << (j * PMEMZONE_BITSPERPAGE);
			return (ATOMIC_READ(zone->mz_free[i]) & mask) != 0;
		}
	} while ((zone = zone->mz_prev) != NULL);
	return false;
}

/* Collect volatile statistics about the usage of physical memory */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(KCALL page_stat)(struct pmemstat *__restrict result) {
	struct pmemzone *zone;
	zone = mzones.pm_last;
	result->ps_free  = 0;
	result->ps_zfree = 0;
	result->ps_used  = 0;
	do {
		physpagecnt_t cfree = ATOMIC_READ(zone->mz_cfree);
		physpagecnt_t qfree = ATOMIC_READ(zone->mz_qfree);
		result->ps_free += cfree;
		result->ps_used += ((physpagecnt_t)zone->mz_rmax + 1) - cfree;
		result->ps_zfree += cfree - qfree;
	} while ((zone = zone->mz_prev) != NULL);
}


PUBLIC NOBLOCK NONNULL((3)) void
NOTHROW(KCALL page_stat_between)(physpage_t base, physpagecnt_t num_pages,
                                 struct pmemstat *__restrict result) {
	(void)base;
	(void)num_pages;
	(void)result;
	/* TODO */
}

/* Following a call to one of the `page_malloc()' functions,
 * check  if  the  given  `page'  contains  only zero-bytes.
 * NOTE: This function doesn't actually  look at the contents  of
 *       page itself, but rather at what it known about the page.
 * NOTE: Returns `false' when `page_ismapped(page, 1)' is false.
 * HINT: This  function  is  mainly  used  in  order  to  optimize the
 *       mapping of zero-initialized memory, such that the initializer
 *       will do something like:
 *       >> page = page_malloc(1);
 *       >> pagedir_mapone(dest, page, PAGEDIR_PROT_READ | PAGEDIR_PROT_WRITE);
 *       >> if (!page_iszero(page))
 *       >>      memsetphys(physpage2addr(dest), 0, PAGESIZE);
 *       In other words: The information is most useful in freshly
 *       allocated pages, in order to determine if the mapped memory
 *       already contains all zeros. */
PUBLIC NOBLOCK WUNUSED bool
NOTHROW(KCALL page_iszero)(physpage_t page) {
	struct pmemzone *zone;
	zone = mzones.pm_last;
	do {
		if (page >= zone->mz_start && page <= zone->mz_max) {
			size_t i;
			unsigned int j;
			uintptr_t mask;
			page -= zone->mz_start;
			i    = (size_t)(page / PAGES_PER_WORD);
			j    = (unsigned int)(page % PAGES_PER_WORD);
			mask = (uintptr_t)PMEMZONE_ISUNDFMASK << (j * PMEMZONE_BITSPERPAGE);
			return !(ATOMIC_READ(zone->mz_free[i]) & mask);
		}
	} while ((zone = zone->mz_prev) != NULL);
	return false;
}


/* Reset the is-zero attribute for all pages in the given range.
 * Pages  that aren't  part of  any zones  are silently ignored. */
PUBLIC NOBLOCK void
NOTHROW(KCALL page_resetzero)(physpage_t page, physpagecnt_t num_pages) {
	/* Keep it simple... */
	while (num_pages--)
		page_resetzeroone(page++);
}

PUBLIC NOBLOCK void
NOTHROW(KCALL page_resetzeroone)(physpage_t page) {
	struct pmemzone *zone;
	zone = mzones.pm_last;
	do {
		if (page >= zone->mz_start && page <= zone->mz_max) {
			size_t i;
			unsigned int j;
			uintptr_t mask;
			page -= zone->mz_start;
			i    = (size_t)(page / PAGES_PER_WORD);
			j    = (unsigned int)(page % PAGES_PER_WORD);
			mask = (uintptr_t)PMEMZONE_ISUNDFMASK << (j * PMEMZONE_BITSPERPAGE);
			ATOMIC_OR(zone->mz_free[i], mask);
			return;
		}
	} while ((zone = zone->mz_prev) != NULL);
}



/* Check if all pages of a given physical memory range are mapped as available RAM. */
PUBLIC NOBLOCK ATTR_PURE WUNUSED bool
NOTHROW(KCALL page_ismapped)(physpage_t page, physpagecnt_t num_pages) {
	struct pmemzone *zone;
	physpage_t page_max;
	page_max = page + num_pages - 1;
	zone     = mzones.pm_last;
	do {
		if (page >= zone->mz_start && page_max <= zone->mz_max)
			return true;
	} while ((zone = zone->mz_prev) != NULL);
	return false;
}





#ifndef CONFIG_NO_PAGE_USAGE
/* Memory usage information.
 * Keeps track of why certain  physical memory allocation were  made.
 * Any physical memory allocated that doesn't appear here is  assumed
 * to be allocated for general-purpose RAM, or some undefined reason. */
PUBLIC struct page_usage_struct page_usage = { 0, };
#endif /* !CONFIG_NO_PAGE_USAGE */





#ifdef CONFIG_HAVE_DEBUGGER
DBG_COMMAND(lsram,
            "lsram\n"
            "\tList page allocation zones, as well as the amount of available ram\n"
            "\tZones are listed as <id start-end 1.23456% used (used_pages/total_pages)>\n") {
	size_t i;
#if __SIZEOF_POINTER__ >= 8
	dbg_print(DBGSTR("# Start            End                   Usage (used/total)\n"));
#else /* __SIZEOF_POINTER__ >= 8 */
	dbg_print(DBGSTR("# Start    End           Usage (used/total)\n"));
#endif /* __SIZEOF_POINTER__ < 8 */
	for (i = 0; i < mzones.pm_zonec; ++i) {
		struct pmemzone *zone;
		size_t used_pages, total_pages;
		unsigned int usage_percent;
		zone = mzones.pm_zones[i];
		total_pages = (size_t)zone->mz_rmax + 1;
		used_pages  = total_pages - (size_t)zone->mz_cfree;
		usage_percent = (unsigned int)(((u64)used_pages * 100 * 100000) / total_pages);
		dbg_printf(DBGSTR("%" PRIuSIZ " " AC_WHITE("%" PRIpN(__SIZEOF_PHYSADDR_T__)) "-"
		                  /*           */ AC_WHITE("%" PRIpN(__SIZEOF_PHYSADDR_T__)) " "
		                  "%3u.%.5u%% (%" PRIuSIZ "/%" PRIuSIZ ")\n"),
		           i,
		           physpage2addr(zone->mz_start),
		           physpage2addr(zone->mz_max + 1) - 1,
		           usage_percent / 100000,
		           usage_percent % 100000,
		           used_pages, total_pages);
	}
	return 0;
}
#endif /* CONFIG_HAVE_DEBUGGER */


DECL_END

#ifndef __INTELLISENSE__
#define ALLOC_SINGLE  1
#define ALLOC_BETWEEN 1
#include "memory-zonealloc-impl.c.inl"
#define ALLOC_MINMAX  1
#define ALLOC_BETWEEN 1
#include "memory-zonealloc-impl.c.inl"
#define ALLOC_BETWEEN 1
#include "memory-zonealloc-impl.c.inl"

#define ALLOC_SINGLE  1
#include "memory-zonealloc-impl.c.inl"
#define ALLOC_MINMAX  1
#include "memory-zonealloc-impl.c.inl"
#include "memory-zonealloc-impl.c.inl"
#endif /* !__INTELLISENSE__ */


#endif /* !GUARD_KERNEL_SRC_MEMORY_MEMORY_C */
