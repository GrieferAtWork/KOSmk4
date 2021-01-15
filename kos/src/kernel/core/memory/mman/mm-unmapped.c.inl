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
#include "mm-unmapped.c"
//#define DEFINE_mman_getunmapped_nx
#define DEFINE_mman_getunmapped_or_unlock
#endif /* __INTELLISENSE__ */

#include <kernel/rand.h>

#include <hybrid/align.h>
#include <hybrid/overflow.h>

#include <kos/except.h>

#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

DECL_BEGIN

#ifndef MM_UNMAPPED_HELPERS_DEFINED
#define MM_UNMAPPED_HELPERS_DEFINED
/* Select a random integer >= minval && <= maxval, with
 * a bias towards numbers that are closer to `bias' */
PRIVATE PAGEDIR_PAGEALIGNED uintptr_t KCALL
select_random_integer_with_bias(uintptr_t minval,
                                uintptr_t maxval,
                                uintptr_t bias) {
	uintptr_t rand_count;
	assert(minval <= bias);
	assert(bias <= maxval);
	rand_count = (maxval - minval) + 1;
	if (rand_count > 1) {
		unsigned int steps = 1;
		unsigned int i;
		uintptr_t offset;
		for (offset = 1; offset <= rand_count; offset <<= 1)
			++steps;
		bias -= minval;
		offset = bias;

		/* Repeatedly shrink the random range surrounding the
		 * original bias, thus that the bias itself continues
		 * to remain apart of the minval...maxval range.
		 * This way, the range of valid values repeatedly shrinks,
		 * and could feasibly not shrink at all, though in the
		 * average case, it will continue to narrow down on the
		 * given bias. */
		for (i = 0; i < steps && rand_count > 0; ++i) {
			offset = krand() % rand_count;
			if (offset < bias) {
				minval += offset;
			} else {
				maxval = minval + offset;
			}
			rand_count = (maxval - minval) + 1;
		}
		return minval + offset;
	}
	return bias;
}

#endif /* !MM_UNMAPPED_HELPERS_DEFINED */


/* Try to find a suitable, unmapped address range:
 * @param: self:      The mman in which to create the mapping. For this purpose,
 *                    any mman other than `mman_kernel' will always cause an
 *                    error when trying to map to a kernel-space address.
 * @param: addr:      A hint for where to search for free memory.
 * @param: num_bytes: The min. number of bytes that should not already be in use,
 *                    starting at the returned address. For this purpose, you may
 *                    assume that this function actually guaranties that at least
 *                    `CEIL_ALIGN(num_bytes, PAGESIZE)' bytes are available, unless
 *                    `MMAN_GETUNMAPPED_F_FIXED' was used
 * @param: min_alignment: The minimum alignment of the return value. Note that no matter
 *                    what is passed for this value, the actual return value will always
 *                    be aligned by at least the size of a single page. If this argument
 *                    isn't a pointer-of-2, then the alignment guarantied for the return
 *                    value is undefined, except that it will still be at least PAGESIZE!
 * @param: flags:     Set of `MMAN_GETUNMAPPED_F_*' (unknown flags are silently ignored)
 *                    HINT: values of flags are chosen to such that they are compatible
 *                          with those from the `flags' argument of `mmap(2)'
 * @return: PAGEDIR_PAGEALIGNED * : The base address where the caller's mapping should go
 * @return: MMAN_GETUNMAPPED_ERROR: Error. */
#ifdef DEFINE_mman_getunmapped_nx
PUBLIC NOBLOCK WUNUSED NONNULL((1)) void *
NOTHROW(FCALL mman_getunmapped_nx)(struct mman *__restrict self,
                                   void *addr, size_t num_bytes, unsigned int flags,
                                   PAGEDIR_PAGEALIGNED size_t min_alignment)
#elif defined(DEFINE_mman_getunmapped_or_unlock)
/* Same as above, but never return `MMAN_GETUNMAPPED_ERROR'. Instead,
 * the given mman is unlocked on error, and an exception is thrown.
 * @throws: E_BADALLOC_INSUFFICIENT_VIRTUAL_MEMORY: Failed to locate a suitably large address
 *                                                  range that fits the given constraints.
 * @throws: E_BADALLOC_ADDRESS_ALREADY_EXISTS:      Both `MMAN_GETUNMAPPED_F_FIXED' and
 *                                                  `MMAN_GETUNMAPPED_F_FIXED_NOREPLACE' were
 *                                                  given, and a pre-existing mapping already
 *                                                  exists within the given address range. */
PUBLIC NOBLOCK WUNUSED NONNULL((1)) PAGEDIR_PAGEALIGNED void *FCALL
mman_getunmapped_or_unlock(struct mman *__restrict self,
                           void *addr, size_t num_bytes, unsigned int flags,
                           PAGEDIR_PAGEALIGNED size_t min_alignment)
		THROWS(E_BADALLOC_INSUFFICIENT_VIRTUAL_MEMORY,
		       E_BADALLOC_ADDRESS_ALREADY_EXISTS)
#endif /* ... */
{
	void *result;
	struct mnode *node;
	assert(mman_lock_acquired(self));

	/* Load additional flags. */
	flags |= mman_getunmapped_extflags;

	/* Deal with the special case of FIXED */
	if (flags & MMAN_GETUNMAPPED_F_FIXED) {
		result = (void *)FLOOR_ALIGN((uintptr_t)addr, PAGESIZE);
		if (flags & MMAN_GETUNMAPPED_F_FIXED_NOREPLACE) {
			node = mnode_tree_rlocate(self->mm_mappings,
			                          (byte_t *)addr,
			                          (byte_t *)addr + num_bytes - 1);
			if (node != NULL)
				goto err_already_exists;
		} else if (ADDRRANGE_ISKERN_PARTIAL((byte_t *)addr,
		                                    (byte_t *)addr + num_bytes) &&
		           self != &mman_kernel) {
			/* Special case: Only allowed to mmap FIXED into kernel-space
			 *               when using the kernel page directory as base,
			 *               which user-space isn't (normally) allowed to
			 *               do. */
			goto err_already_exists_or_nomem;
		}
	} else {
		struct mnode_tree_minmax mima;
		PAGEDIR_PAGEALIGNED void *allow_minaddr, *allow_maxaddr;
		PAGEDIR_PAGEALIGNED void *avail_minaddr, *avail_maxaddr;
		/* Ensure that the hinted address range is properly aligned. */
		if unlikely(!IS_ALIGNED((uintptr_t)addr, PAGESIZE)) {
			if (OVERFLOW_UADD(num_bytes, (uintptr_t)addr & (PAGESIZE - 1), &num_bytes))
				goto err_already_exists_or_nomem;
			addr = (void *)((uintptr_t)addr & ~(PAGESIZE - 1));
		}
		if unlikely(!IS_ALIGNED(num_bytes, PAGESIZE)) {
			size_t new_num_bytes;
			new_num_bytes = CEIL_ALIGN(num_bytes, PAGESIZE);
			if unlikely(new_num_bytes < num_bytes)
				goto err_already_exists_or_nomem;
			num_bytes = new_num_bytes;
		}
		/* Include +2 additional pages for guard space with stacks. */
		if (flags & MMAN_GETUNMAPPED_F_STACK) {
			if (OVERFLOW_UADD(num_bytes, 2 * PAGESIZE, &num_bytes))
				goto err_no_space;
#ifdef __ARCH_STACK_GROWS_DOWNWARDS
			if (OVERFLOW_USUB((uintptr_t)addr, PAGESIZE, (uintptr_t *)&addr))
				addr = (void *)0;
#endif /* __ARCH_STACK_GROWS_DOWNWARDS */
		}

		/* We want `addr' to always point to the lower end of the hinted
		 * address range. - As such, try to subtract the total size of
		 * the needed range from the hinted address. */
		if (MMAN_GETUNMAPPED_ISBELOW(flags)) {
			if (OVERFLOW_USUB((uintptr_t)addr, num_bytes, (uintptr_t *)&addr))
				addr = (void *)0;
		}
again_find_good_range:

		/* Figure out the bounds between which the mapping must be placed. */
		if (self == &mman_kernel && ADDR_ISKERN(addr)) {
			/* Kernel-space requesting a memory location in kernel-space. */
#ifdef KERNELSPACE_BASE
			allow_minaddr = (void *)KERNELSPACE_BASE;
#else /* KERNELSPACE_BASE */
			allow_minaddr = (void *)0;
#endif /* !KERNELSPACE_BASE */
#ifdef KERNELSPACE_END
			allow_maxaddr = (byte_t *)KERNELSPACE_END - num_bytes;
#else /* KERNELSPACE_END */
			allow_maxaddr = (byte_t *)0 - num_bytes;
#endif /* KERNELSPACE_END */
		} else {
			/* Allocate in user-space. */
			allow_minaddr = mman_getunmapped_user_minaddr;
#ifdef KERNELSPACE_LOWMEM
			COMPILER_READ_BARRIER();
			if unlikely((byte_t *)allow_minaddr < (byte_t *)KERNELSPACE_END)
				allow_minaddr = (byte_t *)KERNELSPACE_END;
#endif /* KERNELSPACE_LOWMEM */
#ifdef USERSPACE_END
			allow_maxaddr = (byte_t *)USERSPACE_END - num_bytes;
#elif defined(KERNELSPACE_HIGHMEM) && defined(KERNELSPACE_BASE)
			allow_maxaddr = (byte_t *)KERNELSPACE_BASE - num_bytes;
#else /* USERSPACE_END */
			allow_maxaddr = (byte_t *)0 - num_bytes;
#endif /* USERSPACE_END */
		}
#if __SIZEOF_POINTER__ > 4
		if (flags & MMAN_GETUNMAPPED_F_32BIT) {
			void *limit;
			limit = (void *)(uintptr_t)(((size_t)UINT32_MAX + 1) - num_bytes);
			if ((byte_t *)allow_maxaddr > (byte_t *)limit)
				allow_maxaddr = limit;
		}
#endif /* __SIZEOF_POINTER__ > 4 */

		/* Apply extended alignment requirements to result bounds and the hint address. */
		if unlikely(min_alignment > PAGESIZE) {
			uintptr_t aligned_max_start_addr;
			allow_minaddr = (void *)CEIL_ALIGN((uintptr_t)allow_minaddr, min_alignment);
			addr           = (void *)CEIL_ALIGN((uintptr_t)addr, min_alignment);
			if (OVERFLOW_USUB((uintptr_t)allow_maxaddr, num_bytes - 1, &aligned_max_start_addr)) {
err_no_space:
				/* Try without the +1 additional page of 
				 * normally included in stack allocations. */
				if (flags & MMAN_GETUNMAPPED_F_STACK) {
					num_bytes -= 2 * PAGESIZE;
					flags &= ~(MMAN_GETUNMAPPED_F_STACK |
					           MMAN_GETUNMAPPED_F_BELOW |
					           MMAN_GETUNMAPPED_F_ABOVE);
#ifdef __ARCH_STACK_GROWS_DOWNWARDS
					addr = (byte_t *)addr + PAGESIZE;
					flags |= MMAN_GETUNMAPPED_F_BELOW;
#else /* __ARCH_STACK_GROWS_DOWNWARDS */
					flags |= MMAN_GETUNMAPPED_F_ABOVE;
#endif /* !__ARCH_STACK_GROWS_DOWNWARDS */
					goto again_find_good_range;
				}
				goto err_already_exists_or_nomem;
			}
			aligned_max_start_addr &= ~(min_alignment - 1);
			aligned_max_start_addr += num_bytes - 1;
			allow_maxaddr = (void *)aligned_max_start_addr;
		}

		/* Safety check: Is the range of allowed addresses non-empty? */
		if unlikely(allow_maxaddr < allow_minaddr)
			goto err_no_space;

		if ((byte_t *)addr < (byte_t *)allow_minaddr) {
			if (self != &mman_kernel) {
do_set_automatic_userspace_hint:
				if (flags & MMAN_GETUNMAPPED_F_STACK) {
					addr = mman_getunmapped_user_stkbase;
#ifdef __ARCH_STACK_GROWS_DOWNWARDS
					if (OVERFLOW_USUB((uintptr_t)addr, num_bytes, (uintptr_t *)&addr))
						addr = (void *)0;
#endif /* __ARCH_STACK_GROWS_DOWNWARDS */
				} else {
					addr = mman_getunmapped_user_defbase;
				}
				if unlikely((byte_t *)addr < (byte_t *)allow_minaddr)
					addr = allow_minaddr;
			} else {
				addr = allow_minaddr;
			}
		} else if (addr == NULL && self != &mman_kernel) {
			goto do_set_automatic_userspace_hint;
		}

		avail_minaddr = (byte_t *)addr;
		avail_maxaddr = (byte_t *)addr + num_bytes - 1;
		/* Make sure that the hinted address range lies within the max result bounds.
		 * This also makes sure that the requested address size is properly bound. */
		if (avail_maxaddr > allow_maxaddr) {
			if unlikely(OVERFLOW_USUB((uintptr_t)allow_maxaddr, num_bytes - 1, (uintptr_t *)&addr))
				goto err_no_space;
			if unlikely((byte_t *)addr < (byte_t *)allow_minaddr)
				goto err_no_space;
			avail_minaddr = (byte_t *)addr;
			avail_maxaddr = allow_maxaddr;
		}

		/* Check if the hinted address range is available. */
		mnode_tree_minmaxlocate(self->mm_mappings,
		                        avail_minaddr,
		                        avail_maxaddr,
		                        &mima);
		assert((mima.mm_min != NULL) == (mima.mm_max != NULL));
		if (mima.mm_min == NULL) {
			uintptr_t retindex;
			unsigned int alignshift;
select_from_avail_range:
			/* The hinted address range it available! */
			if (flags & MMAN_GETUNMAPPED_F_NO_ASLR) {
				result = avail_minaddr;
				goto done_dynamic;
			}
			alignshift = PAGESHIFT;
			if unlikely(min_alignment > PAGESIZE)
				alignshift = ffs(min_alignment) - 1;

			/* Figure out the outer bounds of the available range, and
			 * select a biased result value based on the original hint. */
			if (MMAN_GETUNMAPPED_ISBELOW(flags)) {
				if (avail_minaddr > allow_minaddr) {
					mnode_tree_minmaxlocate(self->mm_mappings, allow_minaddr,
					                        (byte_t *)avail_minaddr - 1, &mima);
					if (mima.mm_max != NULL)
						avail_minaddr = (byte_t *)mnode_getmaxaddr(mima.mm_max) + 1;
				}
				retindex = select_random_integer_with_bias((uintptr_t)avail_minaddr >> alignshift,
				                                           (uintptr_t)addr >> alignshift,
				                                           (uintptr_t)addr >> alignshift);
			} else if (MMAN_GETUNMAPPED_ISABOVE(flags)) {
				if (avail_maxaddr < allow_maxaddr) {
					mnode_tree_minmaxlocate(self->mm_mappings,
					                        (byte_t *)avail_maxaddr + 1,
					                        (byte_t *)allow_maxaddr, &mima);
					if (mima.mm_min != NULL)
						avail_minaddr = (byte_t *)mnode_getminaddr(mima.mm_min) - 1;
				}
				avail_maxaddr = (byte_t *)((uintptr_t)avail_maxaddr - (num_bytes - 1));
				retindex = select_random_integer_with_bias((uintptr_t)addr >> alignshift,
				                                           (uintptr_t)avail_maxaddr >> alignshift,
				                                           (uintptr_t)addr >> alignshift);
			} else {
				if (avail_minaddr > allow_minaddr) {
					mnode_tree_minmaxlocate(self->mm_mappings, allow_minaddr,
					                        (byte_t *)avail_minaddr - 1, &mima);
					if (mima.mm_max != NULL)
						avail_minaddr = (byte_t *)mnode_getmaxaddr(mima.mm_max) + 1;
				}
				if (avail_maxaddr < allow_maxaddr) {
					mnode_tree_minmaxlocate(self->mm_mappings,
					                        (byte_t *)avail_maxaddr + 1,
					                        (byte_t *)allow_maxaddr, &mima);
					if (mima.mm_min != NULL)
						avail_minaddr = (byte_t *)mnode_getminaddr(mima.mm_min) - 1;
				}
				avail_maxaddr = (byte_t *)((uintptr_t)avail_maxaddr - (num_bytes - 1));
				retindex = select_random_integer_with_bias((uintptr_t)avail_minaddr >> alignshift,
				                                           (uintptr_t)avail_maxaddr >> alignshift,
				                                           (uintptr_t)addr >> alignshift);
			}
			result = (void *)(retindex << alignshift);
		} else {
			struct mnode *prev, *next;
			bool want_below, want_above;
			PAGEDIR_PAGEALIGNED void *lo_best_minaddr, *lo_best_maxaddr;
			PAGEDIR_PAGEALIGNED void *hi_best_minaddr, *hi_best_maxaddr;
			/* The hinted address range is already in use.
			 * -> Find a larger range below and/or above the
			 *    first (resp.) conflict with the hinted range. */
			if (MMAN_GETUNMAPPED_ISBELOW(flags)) {
				want_below = true;
				want_above = false;
			} else if (MMAN_GETUNMAPPED_ISABOVE(flags)) {
				want_below = false;
				want_above = true;
			} else {
				want_below = true;
				want_above = true;
			}
again_find_below_above:
			lo_best_minaddr = (void *)-1;
			lo_best_maxaddr = (void *)0;
			hi_best_minaddr = (void *)-1;
			hi_best_maxaddr = (void *)0;

			/* Search below, if requested to */
			if (want_below) {
				next = mima.mm_min;
				for (;;) {
					void *gap_min, *gap_max;
					size_t gap_size;
					prev    = mnode_tree_prevnode(next);
					gap_min = allow_minaddr;
					if (prev != NULL)
						gap_min = (byte_t *)mnode_getmaxaddr(prev) + 1;
					gap_max = (byte_t *)mnode_getminaddr(next) - 1;
					if (gap_min >= gap_max)
						goto continue_find_below;
					gap_size = (size_t)((byte_t *)gap_max - (byte_t *)gap_min) + 1;
					if (gap_size < num_bytes)
						goto continue_find_below;
					/* Include extended alignment requirements. */
					if unlikely(min_alignment > PAGESIZE) {
						gap_min = (void *)CEIL_ALIGN((uintptr_t)gap_min, min_alignment);
						if (gap_min >= gap_max)
							goto continue_find_below;
						gap_size = (size_t)((byte_t *)gap_max - (byte_t *)gap_min) + 1;
						if (gap_size < num_bytes)
							goto continue_find_below;
					}
					/* Found the nearest address range that is still large enough! */
					lo_best_minaddr = gap_min;
					lo_best_maxaddr = gap_max;
					break;
continue_find_below:
					if (!prev)
						break;
					next = prev;
				}
			}

			/* Search above, if requested to */
			if (want_above) {
				prev = mima.mm_max;
				for (;;) {
					void *gap_min, *gap_max;
					size_t gap_size;
					next    = mnode_tree_nextnode(prev);
					gap_min = (byte_t *)mnode_getmaxaddr(prev) + 1;
					gap_max = allow_maxaddr;
					if (next != NULL)
						gap_max = (byte_t *)mnode_getminaddr(next) - 1;
					if (gap_min >= gap_max)
						goto continue_find_above;
					gap_size = (size_t)((byte_t *)gap_max - (byte_t *)gap_min) + 1;
					if (gap_size < num_bytes)
						goto continue_find_above;
					/* Include extended alignment requirements. */
					if unlikely(min_alignment > PAGESIZE) {
						gap_min = (void *)CEIL_ALIGN((uintptr_t)gap_min, min_alignment);
						if (gap_min >= gap_max)
							goto continue_find_above;
						gap_size = (size_t)((byte_t *)gap_max - (byte_t *)gap_min) + 1;
						if (gap_size < num_bytes)
							goto continue_find_above;
					}
					/* Found the nearest address range that is still large enough! */
					hi_best_minaddr = gap_min;
					hi_best_maxaddr = gap_max;
					break;
continue_find_above:
					if (!next)
						break;
					prev = next;
				}
			}

			/* Check for special case: we've managed to find something in both directions. */
			if (lo_best_minaddr <= lo_best_maxaddr &&
			    hi_best_minaddr <= hi_best_maxaddr) {
				/* Must decide if we want to choose from below- or from
				 * above the requested range. For this purpose, we choose
				 * the range that is closer to the given hint address, or
				 * select randomly with a bias on said close-ness. */
				ssize_t lo_dist, hi_dist;
				size_t threshold, total;
				lo_dist = (byte_t *)avail_minaddr - (byte_t *)lo_best_maxaddr;
				hi_dist = (byte_t *)hi_best_minaddr - (byte_t *)avail_maxaddr;
				if (lo_dist < 0) {
					hi_dist += -lo_dist;
					lo_dist = 0;
				}
				if (hi_dist < 0) {
					lo_dist += -hi_dist;
					hi_dist = 0;
				}
				if (flags & MMAN_GETUNMAPPED_F_NO_ASLR) {
					/* Don't randomize!
					 * Always select from whichever address range is closer. */
					if ((size_t)lo_dist < (size_t)hi_dist)
						goto select_from_lo_range;
					goto select_from_hi_range;
				}
				total = (size_t)lo_dist + (size_t)hi_dist;
				if unlikely(total == 0)
					goto select_from_lo_range; /* Shouldn't happen... */
				threshold = KRAND(size_t) % total;

				/* Consider that lo_dist < hi_dist. We've got a random
				 * number between 0..(lo_dist+hi_dist)-1. It's less likely
				 * that the number is less than lo_dist, meaning that the
				 * check `threshold < (size_t)lo_dist' succeeds in the less
				 * likely case. And because `lo_dist < hi_dist', and we want
				 * the less likely case to be choosing the range that is
				 * further away, that check must be assigned to the hi range
				 * in this situation.
				 * The case where lo_dist > hi_dist automagically allows for
				 * the same code to be used! */
				if (threshold < (size_t)lo_dist)
					goto select_from_hi_range;
				goto select_from_lo_range;
			} else if (lo_best_minaddr <= lo_best_maxaddr) {
				/* Select from below the hinted range. */
select_from_lo_range:
				avail_minaddr = lo_best_minaddr;
				avail_maxaddr = lo_best_maxaddr;
				goto select_from_avail_range;
			} else if (hi_best_minaddr <= hi_best_maxaddr) {
				/* Select from above the hinted range. */
select_from_hi_range:
				avail_minaddr = hi_best_minaddr;
				avail_maxaddr = hi_best_maxaddr;
				goto select_from_avail_range;
			}

			/* If we didn't manage to find anything in one direction,
			 * try to search in the other direction also. */
			if (!want_below || !want_above) {
				want_below = true;
				want_above = true;
				goto again_find_below_above;
			}
			goto err_no_space;
		}

done_dynamic:
#ifdef __ARCH_STACK_GROWS_DOWNWARDS
		/* Have the return value point past the leading guard-page.
		 * We've originally (tried) to allocate +1 page of additional
		 * space for this very purpose! (see above) */
		if (flags & MMAN_GETUNMAPPED_F_STACK)
			result = (void *)((uintptr_t)result + PAGESIZE);
#endif /* __ARCH_STACK_GROWS_DOWNWARDS */
	}
	return result;
err_already_exists_or_nomem:
#ifdef DEFINE_mman_getunmapped_or_unlock
	if ((flags & (MMAN_GETUNMAPPED_F_FIXED | MMAN_GETUNMAPPED_F_FIXED_NOREPLACE)) !=
	    /*    */ (MMAN_GETUNMAPPED_F_FIXED | MMAN_GETUNMAPPED_F_FIXED_NOREPLACE)) {
		mman_lock_release(self);
		THROW(E_BADALLOC_INSUFFICIENT_VIRTUAL_MEMORY, num_bytes);
	}
#endif /* DEFINE_mman_getunmapped_or_unlock */
err_already_exists:
#ifdef DEFINE_mman_getunmapped_nx
	return MMAN_GETUNMAPPED_ERROR;
#elif defined(DEFINE_mman_getunmapped_or_unlock)
	/**/ {
		void *node_minaddr;
		void *node_maxaddr;
		node_minaddr = mnode_getminaddr(node);
		node_maxaddr = mnode_getmaxaddr(node);
		mman_lock_release(self);
		THROW(E_BADALLOC_ADDRESS_ALREADY_EXISTS,
		      (byte_t *)addr,
		      (byte_t *)addr + num_bytes - 1,
		      node_minaddr, node_maxaddr);
	}
#endif /* ... */
}

DECL_END

#undef DEFINE_mman_getunmapped_or_unlock
#undef DEFINE_mman_getunmapped_nx

