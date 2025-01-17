/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifdef __INTELLISENSE__
#include "memory.c"
//#define ALLOC_SINGLE  1
//#define ALLOC_BETWEEN 1
#define ALLOC_MINMAX  1
#endif /* !__INTELLISENSE__ */

#include <atomic.h>

DECL_BEGIN

#ifdef ALLOC_BETWEEN
#ifdef ALLOC_SINGLE
PRIVATE NOBLOCK WUNUSED NONNULL((1)) physpage_t
NOTHROW(KCALL zone_mallocone_between)(struct pmemzone *__restrict self,
                                      physpage_t zone_relative_min,
                                      physpage_t zone_relative_max,
                                      bool out_of_bounds_is_ok)
#elif defined(ALLOC_MINMAX)
PRIVATE NOBLOCK WUNUSED NONNULL((1)) __page_malloc_part_return_t
NOTHROW(KCALL zone_malloc_part_between)(struct pmemzone *__restrict self,
                                        physpage_t zone_relative_min,
                                        physpage_t zone_relative_max,
                                        physpagecnt_t min_pages,
                                        physpagecnt_t max_pages,
                                        bool out_of_bounds_is_ok)
#else /* ... */
PRIVATE NOBLOCK WUNUSED NONNULL((1)) physpage_t
NOTHROW(KCALL zone_malloc_between)(struct pmemzone *__restrict self,
                                   physpage_t zone_relative_min,
                                   physpage_t zone_relative_max,
                                   physpagecnt_t num_pages,
                                   bool out_of_bounds_is_ok)
#endif /* !... */
#else /* ALLOC_BETWEEN */
#ifdef ALLOC_SINGLE
PRIVATE NOBLOCK WUNUSED NONNULL((1)) physpage_t
NOTHROW(KCALL zone_mallocone_before)(struct pmemzone *__restrict self,
                                     physpage_t zone_relative_max)
#elif defined(ALLOC_MINMAX)
PRIVATE NOBLOCK WUNUSED NONNULL((1)) __page_malloc_part_return_t
NOTHROW(KCALL zone_malloc_part_before)(struct pmemzone *__restrict self,
                                       physpage_t zone_relative_max,
                                       physpagecnt_t min_pages,
                                       physpagecnt_t max_pages)
#else /* ... */
PRIVATE NOBLOCK WUNUSED NONNULL((1)) physpage_t
NOTHROW(KCALL zone_malloc_before)(struct pmemzone *__restrict self,
                                  physpage_t zone_relative_max,
                                  physpagecnt_t num_pages)
#endif /* !... */
#endif /* !ALLOC_BETWEEN */
{
	uintptr_t word;
	size_t i;
#ifdef ALLOC_BETWEEN
	size_t min_i;
#endif /* ALLOC_BETWEEN */
	unsigned int misalignment;
	physpage_t result;
#ifdef ALLOC_BETWEEN
	assert(zone_relative_max >= zone_relative_min);
#endif /* ALLOC_BETWEEN */
	assert(zone_relative_max <= self->mz_rmax);
#ifdef ALLOC_BETWEEN
	min_i = (size_t)(zone_relative_min / PAGES_PER_WORD);
#endif /* ALLOC_BETWEEN */
	i            = (size_t)(zone_relative_max / PAGES_PER_WORD);
	misalignment = (unsigned int)(zone_relative_max % PAGES_PER_WORD);
#ifdef ALLOC_MINMAX
	if (max_pages <= 1)
#elif !defined(ALLOC_SINGLE)
	if (num_pages <= 1)
#endif /* ... */
	{
		/* Non-transient allocation. */
		for (;;) {
			uintptr_t page_mask;
again_word_i:
			word      = atomic_read(&self->mz_free[i]);
			page_mask = (uintptr_t)PMEMZONE_ISFREEMASK << (misalignment * PMEMZONE_BITSPERPAGE);
			for (;;) {
				if (word & page_mask) {
					/* Got it! (allocate the remainder!) */
					assert(page_mask);
					result = (physpage_t)i * PAGES_PER_WORD + (CTZ(page_mask) / PMEMZONE_BITSPERPAGE);
#ifdef ALLOC_BETWEEN
					if unlikely(result < zone_relative_min && !out_of_bounds_is_ok)
						goto nope;
#endif /* ALLOC_BETWEEN */
#ifdef ALLOC_MINMAX
					if likely(max_pages)
#elif !defined(ALLOC_SINGLE)
					if likely(num_pages)
#endif
					{
						if (!atomic_cmpxch_weak(&self->mz_free[i], word, word & ~page_mask))
							goto again_word_i;
						assert(POPCOUNT(page_mask) == 1);
						atomic_dec(&self->mz_cfree);
						if (word & (page_mask << (PMEMZONE_ISUNDFBIT - PMEMZONE_ISFREEBIT)))
							atomic_dec(&self->mz_qfree);
					}
#ifdef ALLOC_MINMAX
					return __page_malloc_part_return_pack(result, 1);
#else /* ALLOC_MINMAX */
					return result;
#endif /* !ALLOC_MINMAX */
				}
				if (page_mask <= PMEMZONE_ISFREEMASK)
					break;
				page_mask >>= PMEMZONE_BITSPERPAGE;
			}
#ifdef ALLOC_BETWEEN
			if unlikely(i <= min_i)
				goto nope;
#else /* ALLOC_BETWEEN */
			if unlikely(!i)
				goto nope;
#endif /* !ALLOC_BETWEEN */
			--i;
			misalignment = PAGES_PER_WORD - 1;
		}
	}
#ifndef ALLOC_SINGLE
	else {
		physpagecnt_t alloc_count;
		unsigned int qcount;
		/* Transient allocation. */
		alloc_count = 0;
		for (;;) {
			uintptr_t page_mask;
			uintptr_t alloc_mask;
			size_t new_alloc_count;
again_word_i_trans:
			alloc_mask      = 0;
			new_alloc_count = alloc_count;
			word            = atomic_read(&self->mz_free[i]);
			page_mask       = (uintptr_t)PMEMZONE_ISFREEMASK << (misalignment * PMEMZONE_BITSPERPAGE);
			for (;;) {
				if (word & page_mask) {
					alloc_mask |= page_mask;
					++new_alloc_count;
#ifdef ALLOC_MINMAX
					if (new_alloc_count >= max_pages)
#else /* ALLOC_MINMAX */
					if (new_alloc_count >= num_pages)
#endif /* !ALLOC_MINMAX */
					{
						/* Got it! (allocate the remainder!) */
						assert(alloc_mask);
						result = (physpage_t)i * PAGES_PER_WORD + (CTZ(alloc_mask) / PMEMZONE_BITSPERPAGE);
#ifdef ALLOC_BETWEEN
						if unlikely(result < zone_relative_min && !out_of_bounds_is_ok) {
							if (alloc_count)
								zone_free_keepz(self, (physpage_t)((i + 1) * PAGES_PER_WORD), alloc_count);
							goto nope;
						}
#endif /* ALLOC_BETWEEN */
#ifdef ALLOC_MINMAX
min_max_allocate_current_alloc_mask:
#endif /* ALLOC_MINMAX */
						if (!atomic_cmpxch_weak(&self->mz_free[i], word, word & ~alloc_mask))
							goto again_word_i_trans;
						atomic_fetchsub(&self->mz_cfree, new_alloc_count - alloc_count);
						qcount = POPCOUNT(word & (alloc_mask << (PMEMZONE_ISUNDFBIT - PMEMZONE_ISFREEBIT)));
						assert(qcount <= (new_alloc_count - alloc_count));
						if (qcount)
							atomic_fetchsub(&self->mz_qfree, qcount);
#ifdef ALLOC_MINMAX
						return __page_malloc_part_return_pack(result, new_alloc_count);
#else /* ALLOC_MINMAX */
						return result;
#endif /* !ALLOC_MINMAX */
					}
				} else {
#ifdef ALLOC_MINMAX
					if (new_alloc_count >= min_pages) {
						result = (physpage_t)i * PAGES_PER_WORD;
						result += alloc_mask ? (CTZ(alloc_mask) / PMEMZONE_BITSPERPAGE) : PAGES_PER_WORD;
#ifdef ALLOC_BETWEEN
						if unlikely(out_of_bounds_is_ok || result >= zone_relative_min)
#endif /* ALLOC_BETWEEN */
						{
#if 1
							goto min_max_allocate_current_alloc_mask;
#else
							if (!atomic_cmpxch_weak(&self->mz_free[i], word, word & ~alloc_mask))
								goto again_word_i_trans;
							atomic_fetchsub(&self->mz_cfree, new_alloc_count - alloc_count);
							qcount = POPCOUNT(word & (alloc_mask << (PMEMZONE_ISUNDFBIT - PMEMZONE_ISFREEBIT)));
							assert(qcount <= (new_alloc_count - alloc_count));
							if (qcount)
								atomic_fetchsub(&self->mz_qfree, qcount);
							return __page_malloc_part_return_pack(result, new_alloc_count);
#endif
						}
					}
#endif /* ALLOC_MINMAX */
					if (alloc_count) {
						zone_free_keepz(self,
						                (physpage_t)((i + 1) * PAGES_PER_WORD),
						                alloc_count);
						alloc_count = 0;
					}
					new_alloc_count = 0;
					alloc_mask      = 0;
				}
				if (page_mask <= PMEMZONE_ISFREEMASK)
					break;
				page_mask >>= PMEMZONE_BITSPERPAGE;
			}
			/* Allocate the current mask. */
			if (alloc_mask) {
				assert(alloc_mask & PMEMZONE_ISFREEMASK);
				assert(new_alloc_count > alloc_count);
				if (!atomic_cmpxch_weak(&self->mz_free[i], word, word & ~alloc_mask))
					goto again_word_i_trans;
				atomic_fetchsub(&self->mz_cfree, new_alloc_count - alloc_count);
				qcount = POPCOUNT(word & (alloc_mask << (PMEMZONE_ISUNDFBIT - PMEMZONE_ISFREEBIT)));
				assert(qcount <= (new_alloc_count - alloc_count));
				if (qcount)
					atomic_fetchsub(&self->mz_qfree, qcount);
			} else {
				assert(new_alloc_count == alloc_count);
			}
			alloc_count = new_alloc_count;
#ifdef ALLOC_BETWEEN
			if unlikely(i <= min_i)
#else /* ALLOC_BETWEEN */
			if unlikely(!i)
#endif /* !ALLOC_BETWEEN */
			{
#ifdef ALLOC_MINMAX
#ifdef ALLOC_BETWEEN
				if (alloc_count >= min_pages && out_of_bounds_is_ok)
#else /* ALLOC_BETWEEN */
				if (alloc_count >= min_pages)
#endif /* !ALLOC_BETWEEN */
				{
					return __page_malloc_part_return_pack((physpage_t)(i * PAGES_PER_WORD), alloc_count);
				}
#endif /* ALLOC_MINMAX */
				if (alloc_count)
					zone_free_keepz(self, (physpage_t)(i * PAGES_PER_WORD), alloc_count);
				goto nope;
			}
			--i;
			misalignment = PAGES_PER_WORD - 1;
		}
	}
#endif /* !ALLOC_SINGLE */
nope:
#ifdef ALLOC_MINMAX
	return __page_malloc_part_return_pack(PHYSPAGE_INVALID, 0);
#else /* ALLOC_MINMAX */
	return PHYSPAGE_INVALID;
#endif /* !ALLOC_MINMAX */
}

DECL_END

#undef ALLOC_MINMAX
#undef ALLOC_BETWEEN
#undef ALLOC_SINGLE
