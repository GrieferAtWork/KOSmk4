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
#ifndef GUARD_KERNEL_SRC_MEMORY_MMAN_MMAN_FIND_UNMAPPED_C
#define GUARD_KERNEL_SRC_MEMORY_MMAN_MMAN_FIND_UNMAPPED_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/malloc.h>
#include <kernel/mman.h>
#include <kernel/mman/mnode.h>
#include <kernel/mman/unmapped.h>
#include <kernel/paging.h>
#include <kernel/rand.h>
#include <misc/unlockinfo.h>

#include <hybrid/align.h>
#include <hybrid/atomic.h>
#include <hybrid/bit.h>
#include <hybrid/overflow.h>

#include <kos/except.h>
#include <kos/except/reason/inval.h>
#include <kos/kernel/paging.h> /* Default mapping hints */

#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

DECL_BEGIN

#ifdef KERNELSPACE_HIGHMEM
#define US_MINADDR ((uintptr_t)0)
#define US_MAXADDR ((uintptr_t)(KERNELSPACE_BASE - 1))
#define KS_MINADDR ((uintptr_t)KERNELSPACE_BASE)
#define KS_MAXADDR ((uintptr_t)-1)
#elif defined(KERNELSPACE_LOWMEM)
#define US_MINADDR ((uintptr_t)KERNELSPACE_END)
#define US_MAXADDR ((uintptr_t)-1)
#define KS_MINADDR ((uintptr_t)0)
#define KS_MAXADDR ((uintptr_t)(KERNELSPACE_END - 1))
#else /* KERNELSPACE_...MEM */
#if 1
#define US_MINADDR ((uintptr_t)0)
#define US_MAXADDR ((uintptr_t)(KERNELSPACE_BASE - 1))
#else
#define US_MINADDR ((uintptr_t)KERNELSPACE_END)
#define US_MAXADDR ((uintptr_t)-1)
#endif
#define KS_MINADDR ((uintptr_t)KERNELSPACE_BASE)
#define KS_MAXADDR ((uintptr_t)(KERNELSPACE_END - 1))
#endif /* !KERNELSPACE_...MEM */


#ifndef KERNEL_MHINT_USER_MINADDR
#define KERNEL_MHINT_USER_MINADDR (0, 0)
#endif /* !KERNEL_MHINT_USER_MINADDR */

/* The lowest (user-space) address  that might ever be  automatically
 * selected for mapping by `mman_findunmapped()'. Note that the  user
 * may still employ `MAP_FIXED' to overrule this limit, allowing them
 * to mmap anywhere (in user-space).
 *
 * When `addr' is less than this value, it will be clamped to be equal
 * to this value.  Furthermore, attempting to  search for free  memory
 * mappings below this address always fails.
 *
 * The value of this variable is exposed in `/proc/sys/vm/mmap_min_addr' */
PUBLIC USER CHECKED void *mman_getunmapped_user_minaddr = MHINT_GETADDR(KERNEL_MHINT_USER_MINADDR);

/* Default base address for user-space  memory mappings. When trying to  find
 * an unmapped area within a user-space mman, the FIXED flag isn't given, and
 * the  given hint-address is  less than `mman_getunmapped_user_minaddr' then
 * MAX(mman_getunmapped_user_minaddr, mman_getunmapped_user_defbase) will  be
 * used as initial hint instead.
 * Afterwards, the actual address to-be returned will be calculated normally.
 *
 * By default, this variable is set to `KERNEL_MHINT_USER_HEAP' */
PUBLIC USER CHECKED void *mman_getunmapped_user_defbase = MHINT_GETADDR(KERNEL_MHINT_USER_HEAP);

/* Same as `mman_getunmapped_user_defbase', but used
 * instead  when  the  `MAP_STACK'  flag  is  given. */
PUBLIC USER CHECKED void *mman_getunmapped_user_stkbase = MHINT_GETADDR(KERNEL_MHINT_USER_STACK);

/* [lock(ATOMIC)]
 * Additional flags that are always or'd to those given to `mman_findunmapped()'
 * NOTE: _ONLY_ use this always force the  `MAP_NOASLR' flag to be set,  thus
 *       allowing you to force-disable ASLR system-wide. Using this for other
 *       flags  does  what you'd  think, but  the  results would  probably be
 *       catastrophic.
 *       Also note that modifications to this variable must be done atomically! */
PUBLIC unsigned int mman_findunmapped_extflags = 0;


/* Select a random integer >= minval && <= maxval, with
 * a bias  towards numbers  that are  closer to  `bias' */
PRIVATE PAGEDIR_PAGEALIGNED uintptr_t KCALL
select_random_integer_with_bias(uintptr_t minval,
                                uintptr_t maxval,
                                uintptr_t bias) {
#if 1
	assert(minval <= bias);
	assert(bias <= maxval);
	/* TODO: The below code doesn't work (returns numbers outside the min/max-range)... */
	return bias;
#else
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

		/* Repeatedly shrink  the  random  range  surrounding  the
		 * original  bias,  thus  that the  bias  itself continues
		 * to   remain   apart  of   the   minval...maxval  range.
		 * This way, the range of valid values repeatedly shrinks,
		 * and  could feasibly  not shrink  at all,  though in the
		 * average case, it  will continue to  narrow down on  the
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
#endif
}


/* Try to find a suitable, unmapped address range. Note that this function  never
 * throws an exception, but also doesn't allow for use of `MAP_FIXED'. Attempting
 * to  pass that flag is simply ignored, and the function acts as though that bit
 * hadn't actually been set.
 * @param: self:      The mman in which to create the mapping. For this purpose,
 *                    any mman  other than  `mman_kernel' will  always cause  an
 *                    error when trying to map to a kernel-space address.
 *                    NOTE: The caller  must be  holding a  lock to  this  mman!
 * @param: addr:      A hint for where to search for free memory.
 * @param: num_bytes: The min. number of bytes that  should not already be in  use,
 *                    starting at the returned address.  For this purpose, you  may
 *                    assume that this function  actually guaranties that at  least
 *                    `CEIL_ALIGN(num_bytes, PAGESIZE)' bytes are available, unless
 *                    `MAP_FIXED' was used
 * @param: min_alignment: The minimum alignment of the return value. Note that no matter
 *                    what is passed for this value, the actual return value will  always
 *                    be  aligned by at least the size of a single page. If this argument
 *                    isn't a pointer-of-2, then the alignment guarantied for the  return
 *                    value is undefined, except that it will still be at least PAGESIZE!
 * @param: min_alignment_offset: [valid_if(IS_POWER_OF_TWO(min_alignment) && min_alignment >= PAGESIZE)]
 *                    Offset from `return' at which `min_alignment' shall be applied.
 *                    If  valid, this  argument _must_  be a  multiple of `PAGESIZE'.
 * @param: flags:     Set of `MAP_GROWSDOWN | MAP_GROWSUP | MAP_32BIT | MAP_STACK | MAP_NOASLR'
 *                    Unknown flags are silently ignored.
 * @return: PAGEDIR_PAGEALIGNED * : The base address where the caller's mapping should go
 * @return: MAP_FAILED:             Error: No free space matching requirements was found. */
PUBLIC NOBLOCK WUNUSED NONNULL((1)) void *
NOTHROW(FCALL mman_findunmapped)(struct mman const *__restrict self,
                                 void *addr, size_t num_bytes, unsigned int flags,
                                 size_t min_alignment, ptrdiff_t min_alignment_offset) {
#define HAS_EXTENDED_MIN_ALIGNMENT \
	(min_alignment > PAGESIZE && IS_POWER_OF_TWO(min_alignment))
#define REQUIRED_ALIGNMENT \
	(HAS_EXTENDED_MIN_ALIGNMENT ? min_alignment : PAGESIZE)
#define ALIGN_EXTENDED_POINTER(value) \
	((void *)(CEIL_ALIGN((uintptr_t)(value) + min_alignment_offset, min_alignment) - min_alignment_offset))
	void *result;
	struct mnode_tree_minmax mima;
	PAGEDIR_PAGEALIGNED void *allow_minaddr, *allow_maxaddr;
	PAGEDIR_PAGEALIGNED void *avail_minaddr, *avail_maxaddr;
	/*assert(mman_lock_acquired(self));*/ /* Cannot be asserted because of `mman_findunmapped_in_usertree()' */

	/* Load additional flags. */
	flags |= ATOMIC_READ(mman_findunmapped_extflags);

	/* Ensure that the hinted address range is properly aligned. */
	if unlikely(!IS_ALIGNED((uintptr_t)addr, PAGESIZE)) {
		if (OVERFLOW_UADD(num_bytes, (uintptr_t)addr & (PAGESIZE - 1), &num_bytes))
			goto err;
		addr = (void *)((uintptr_t)addr & ~(PAGESIZE - 1));
	}
	if unlikely(!IS_ALIGNED(num_bytes, PAGESIZE)) {
		size_t new_num_bytes;
		new_num_bytes = CEIL_ALIGN(num_bytes, PAGESIZE);
		if unlikely(new_num_bytes <= num_bytes)
			goto err;
		num_bytes = new_num_bytes;
	}
	/* Include +2 additional pages for guard space with stacks. */
	if (flags & MAP_STACK) {
		if (OVERFLOW_UADD(num_bytes, 2 * PAGESIZE, &num_bytes))
			goto err_no_space;
#ifdef __ARCH_STACK_GROWS_DOWNWARDS
		if (OVERFLOW_USUB((uintptr_t)addr, PAGESIZE, (uintptr_t *)&addr))
			addr = (void *)0;
#endif /* __ARCH_STACK_GROWS_DOWNWARDS */
	}

	/* We want `addr' to always point to the lower end of the hinted
	 * address range. - As such, try  to subtract the total size  of
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
		allow_maxaddr = (byte_t *)KERNELSPACE_END - 1;
#else /* KERNELSPACE_END */
		allow_maxaddr = (byte_t *)-1;
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
		allow_maxaddr = (byte_t *)USERSPACE_END - 1;
#elif defined(KERNELSPACE_HIGHMEM) && defined(KERNELSPACE_BASE)
		allow_maxaddr = (byte_t *)KERNELSPACE_BASE - 1;
#else /* USERSPACE_END */
		allow_maxaddr = (byte_t *)-1;
#endif /* USERSPACE_END */
	}
#if __SIZEOF_POINTER__ > 4
	if (flags & MAP_32BIT) {
		if (allow_maxaddr > (byte_t *)UINT32_MAX)
			allow_maxaddr = (byte_t *)UINT32_MAX;
	}
#endif /* __SIZEOF_POINTER__ > 4 */

	/* Apply extended alignment requirements to result bounds and the hint address. */
	if unlikely(HAS_EXTENDED_MIN_ALIGNMENT) {
		assert(IS_ALIGNED(min_alignment_offset, PAGESIZE));
		allow_minaddr = ALIGN_EXTENDED_POINTER(allow_minaddr);
		addr          = ALIGN_EXTENDED_POINTER(addr);
	}

	/* Safety check: Is the range of allowed addresses non-empty? */
	if unlikely(allow_maxaddr < allow_minaddr) {
err_no_space:
		/* Try without the  +1 additional page  of
		 * normally included in stack allocations. */
		if (flags & MAP_STACK) {
			num_bytes -= 2 * PAGESIZE;
			flags &= ~(MAP_STACK | MAP_GROWSDOWN | MAP_GROWSUP);
#ifdef __ARCH_STACK_GROWS_DOWNWARDS
			addr = (byte_t *)addr + PAGESIZE;
			flags |= MAP_GROWSDOWN;
#else /* __ARCH_STACK_GROWS_DOWNWARDS */
			flags |= MAP_GROWSUP;
#endif /* !__ARCH_STACK_GROWS_DOWNWARDS */
			goto again_find_good_range;
		}
		goto err;
	}

	if ((byte_t *)addr < (byte_t *)allow_minaddr) {
		if (self == &mman_kernel) {
			addr = allow_minaddr;
		} else {
do_set_automatic_userspace_hint:
			if (flags & MAP_STACK) {
				addr = mman_getunmapped_user_stkbase;
#ifdef __ARCH_STACK_GROWS_DOWNWARDS
				if (OVERFLOW_USUB((uintptr_t)addr, num_bytes, (uintptr_t *)&addr))
					addr = (void *)0;
#endif /* __ARCH_STACK_GROWS_DOWNWARDS */
			} else {
				addr = mman_getunmapped_user_defbase;
			}
			if unlikely((byte_t *)addr < (byte_t *)allow_minaddr) {
				addr = allow_minaddr;
			} else {
				if (HAS_EXTENDED_MIN_ALIGNMENT)
					addr = ALIGN_EXTENDED_POINTER(addr);
			}
		}
	} else if (addr == NULL && self != &mman_kernel) {
		goto do_set_automatic_userspace_hint;
	}

	assert((byte_t *)addr >= (byte_t *)allow_minaddr);
	assert(IS_ALIGNED((uintptr_t)addr, REQUIRED_ALIGNMENT));
	avail_minaddr = (byte_t *)addr;
	avail_maxaddr = (byte_t *)addr + num_bytes - 1;

	/* Make sure that the hinted address range lies within the max result bounds.
	 * This  also makes sure  that the requested address  size is properly bound. */
	if (avail_maxaddr > allow_maxaddr) {
		if unlikely(OVERFLOW_USUB((uintptr_t)allow_maxaddr, num_bytes - 1, (uintptr_t *)&addr))
			goto err_no_space;
		if (HAS_EXTENDED_MIN_ALIGNMENT)
			addr = (void *)FLOOR_ALIGN((uintptr_t)addr, min_alignment);
		if unlikely((byte_t *)addr < (byte_t *)allow_minaddr)
			goto err_no_space;
		avail_minaddr = (byte_t *)addr;
		avail_maxaddr = (byte_t *)addr + num_bytes - 1;
	}
	assert((byte_t *)avail_minaddr >= (byte_t *)allow_minaddr);
	assert((byte_t *)avail_maxaddr <= (byte_t *)allow_maxaddr);

	/* Check if the hinted address range is available. */
	mnode_tree_minmaxlocate(self->mm_mappings,
	                        avail_minaddr,
	                        avail_maxaddr,
	                        &mima);
	assert((mima.mm_min != NULL) == (mima.mm_max != NULL));
	if (mima.mm_min == NULL) {
		void *alloc_maxaddr;
		shift_t alignshift;
select_from_avail_range:
		assert(IS_ALIGNED((uintptr_t)allow_minaddr, REQUIRED_ALIGNMENT));
		assert(IS_ALIGNED((uintptr_t)avail_minaddr, REQUIRED_ALIGNMENT));
		alignshift = PAGESHIFT;
		if unlikely(HAS_EXTENDED_MIN_ALIGNMENT)
			alignshift = CTZ(min_alignment);

		/* Figure out the outer bounds of the available range,  and
		 * select a biased result value based on the original hint. */
		assert(avail_maxaddr >= ((byte_t *)avail_minaddr + num_bytes - 1));
		assert(!mnode_tree_rlocate(self->mm_mappings, avail_minaddr, avail_maxaddr));
		if (avail_minaddr > allow_minaddr) {
			mnode_tree_minmaxlocate(self->mm_mappings,
			                        (byte_t *)allow_minaddr,
			                        (byte_t *)avail_minaddr - 1, &mima);
			if (mima.mm_max != NULL) {
				avail_minaddr = (byte_t *)mnode_getmaxaddr(mima.mm_max) + 1;
				if (avail_minaddr < allow_minaddr)
					avail_minaddr = allow_minaddr;
			} else {
				avail_minaddr = allow_minaddr;
			}
			if unlikely(HAS_EXTENDED_MIN_ALIGNMENT)
				avail_minaddr = ALIGN_EXTENDED_POINTER(avail_minaddr);
		}
		if (avail_maxaddr < allow_maxaddr) {
			mnode_tree_minmaxlocate(self->mm_mappings,
			                        (byte_t *)avail_maxaddr + 1,
			                        (byte_t *)allow_maxaddr, &mima);
			if (mima.mm_min != NULL) {
				avail_maxaddr = (byte_t *)mnode_getminaddr(mima.mm_min) - 1;
				if (avail_maxaddr > allow_maxaddr)
					avail_maxaddr = allow_maxaddr;
			} else {
				avail_maxaddr = allow_maxaddr;
			}
		}
		assert(!mnode_tree_rlocate(self->mm_mappings, avail_minaddr, avail_maxaddr));

		/* Figure out the max address which we're allowed to return. */
		alloc_maxaddr = ((byte_t *)avail_maxaddr + 1) - num_bytes;
		assertf(avail_minaddr <= alloc_maxaddr,
		        "avail_minaddr: %p\n"
		        "alloc_maxaddr: %p\n",
		        avail_minaddr, alloc_maxaddr);
		if (addr < avail_minaddr)
			addr = avail_minaddr;
		if (addr > alloc_maxaddr)
			addr = alloc_maxaddr;
		if (MMAN_GETUNMAPPED_ISBELOW(flags)) {
			alloc_maxaddr = addr;
		} else if (MMAN_GETUNMAPPED_ISABOVE(flags)) {
			avail_minaddr = addr;
		}
		assertf(addr >= avail_minaddr, "%p >= %p", addr, avail_minaddr);
		assertf(addr <= alloc_maxaddr, "%p <= %p", addr, alloc_maxaddr);
		if (flags & MAP_NOASLR) {
			/* Always use the given bias if ASLR is disabled. */
			result = addr;
		} else {
			uintptr_t retindex;
			retindex = select_random_integer_with_bias((uintptr_t)avail_minaddr >> alignshift,
			                                           (uintptr_t)alloc_maxaddr >> alignshift,
			                                           (uintptr_t)addr >> alignshift);
			result   = (void *)(retindex << alignshift);
		}
		assertf(result >= avail_minaddr, "%p >= %p", result, avail_minaddr);
		assertf(result <= alloc_maxaddr, "%p <= %p", result, alloc_maxaddr);
	} else {
		struct mnode const *prev, *next;
		bool want_below, want_above;
		PAGEDIR_PAGEALIGNED void *lo_best_minaddr, *lo_best_maxaddr;
		PAGEDIR_PAGEALIGNED void *hi_best_minaddr, *hi_best_maxaddr;

		/* The hinted address range is already in use.
		 * -> Find a larger  range below  and/or above  the
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
				if (prev != NULL) {
					gap_min = (byte_t *)mnode_getmaxaddr(prev) + 1;
					if (gap_min < allow_minaddr)
						gap_min = allow_minaddr;
				}
				gap_max = (byte_t *)mnode_getminaddr(next);
				if (OVERFLOW_USUB((uintptr_t)gap_max, 1, (uintptr_t *)&gap_max))
					break; /* Prevent overflow, else we'd get `gap_max == (void *)-1' */
				if (gap_min >= gap_max)
					goto continue_find_below;
				assert(gap_max <= allow_maxaddr);
				gap_size = (size_t)((byte_t *)gap_max - (byte_t *)gap_min) + 1;
				if (gap_size < num_bytes)
					goto continue_find_below;

				/* Include extended alignment requirements. */
				if unlikely(HAS_EXTENDED_MIN_ALIGNMENT) {
					gap_min = ALIGN_EXTENDED_POINTER(gap_min);
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
				gap_min = (byte_t *)mnode_getmaxaddr(prev);
				if (OVERFLOW_UADD((uintptr_t)gap_min, 1, (uintptr_t *)&gap_min))
					break; /* Prevent overflow, else we'd get `gap_min == (void *)0' */
				gap_max = allow_maxaddr;
				if (next != NULL) {
					gap_max = (byte_t *)mnode_getminaddr(next) - 1;
					assert(gap_max != (void *)-1);
					if (gap_max > allow_maxaddr)
						gap_max = allow_maxaddr;
				}
				if (gap_min >= gap_max)
					goto continue_find_above;
				assert(gap_min >= allow_minaddr);
				gap_size = (size_t)((byte_t *)gap_max - (byte_t *)gap_min) + 1;
				if (gap_size < num_bytes)
					goto continue_find_above;

				/* Include extended alignment requirements. */
				if unlikely(HAS_EXTENDED_MIN_ALIGNMENT) {
					gap_min = ALIGN_EXTENDED_POINTER(gap_min);
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

		/* Assert that best-fit ranges are within allowed bounds. */
		assert(!(lo_best_minaddr <= lo_best_maxaddr) || lo_best_minaddr >= allow_minaddr);
		assert(!(lo_best_minaddr <= lo_best_maxaddr) || lo_best_maxaddr <= allow_maxaddr);
		assert(!(lo_best_minaddr <= lo_best_maxaddr) || !mnode_tree_rlocate(self->mm_mappings, lo_best_minaddr, lo_best_maxaddr));
		assert(!(hi_best_minaddr <= hi_best_maxaddr) || hi_best_minaddr >= allow_minaddr);
		assert(!(hi_best_minaddr <= hi_best_maxaddr) || hi_best_maxaddr <= allow_maxaddr);
		assert(!(hi_best_minaddr <= hi_best_maxaddr) || !mnode_tree_rlocate(self->mm_mappings, hi_best_minaddr, hi_best_maxaddr));

		/* Check for special case: we've managed to find something in both directions. */
		if (lo_best_minaddr <= lo_best_maxaddr &&
		    hi_best_minaddr <= hi_best_maxaddr) {
			/* Must decide if we want  to choose from below- or  from
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
			if (flags & MAP_NOASLR) {
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

			/* Consider that  lo_dist  <  hi_dist. We've  got  a  random
			 * number between 0..(lo_dist+hi_dist)-1.  It's less  likely
			 * that the number  is less than  lo_dist, meaning that  the
			 * check `threshold < (size_t)lo_dist' succeeds in the  less
			 * likely case. And because `lo_dist < hi_dist', and we want
			 * the less likely  case to  be choosing the  range that  is
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
			assert(!mnode_tree_rlocate(self->mm_mappings, avail_minaddr, avail_maxaddr));
			goto select_from_avail_range;
		} else if (hi_best_minaddr <= hi_best_maxaddr) {
			/* Select from above the hinted range. */
select_from_hi_range:
			avail_minaddr = hi_best_minaddr;
			avail_maxaddr = hi_best_maxaddr;
			assert(!mnode_tree_rlocate(self->mm_mappings, avail_minaddr, avail_maxaddr));
			goto select_from_avail_range;
		}

		/* If we didn't manage to find anything in one direction,
		 * try   to   search   in  the   other   direction  also. */
		if (!want_below || !want_above) {
			want_below = true;
			want_above = true;
			goto again_find_below_above;
		}
		goto err_no_space;
	}

#ifdef __ARCH_STACK_GROWS_DOWNWARDS
	/* Have the return value  point past the leading  guard-page.
	 * We've originally (tried) to allocate +1 page of additional
	 * space for this very purpose! (see above) */
	if (flags & MAP_STACK) {
		result = (void *)((uintptr_t)result + PAGESIZE);
#ifndef NDEBUG
		num_bytes -= PAGESIZE * 2;
#endif /* !NDEBUG */
	}
#endif /* __ARCH_STACK_GROWS_DOWNWARDS */

	/* Sanity check: assert that the found region really is unused. */
	assertf(!mnode_tree_rlocate(self->mm_mappings,
	                            (byte_t *)result,
	                            (byte_t *)result + num_bytes - 1),
	        "Address range %p-%p already in use?",
	        (byte_t *)result, (byte_t *)result + num_bytes - 1);
	return result;
err:
	return MAP_FAILED;
#undef REQUIRED_ALIGNMENT
#undef HAS_EXTENDED_MIN_ALIGNMENT
}




/* Similar to `mman_findunmapped()', but never return `MAP_FAILED', and automatically split
 * mem-nodes  at the resulting min/max bounds when `MAX_FIXED' w/o `MAP_FIXED_NOREPLACE' is
 * used, and another mapping already existed at  the specified location. If this cannot  be
 * done  without blocking, release all locks, do the split while not holding any locks, and
 * return `MAP_FAILED', indicative of the caller needing to re-acquire locks and re-attempt
 * the call.
 * @param: self:      The mman in which to create the mapping. For this purpose,
 *                    any mman  other than  `mman_kernel' will  always cause  an
 *                    error when trying to map to a kernel-space address.
 *                    NOTE: The caller must be holding a lock to this mman!
 * @param: addr:      A hint for where to search for free memory.
 * @param: num_bytes: The min. number of bytes that  should not already be in  use,
 *                    starting at the returned address.  For this purpose, you  may
 *                    assume that this function  actually guaranties that at  least
 *                    `CEIL_ALIGN(num_bytes, PAGESIZE)' bytes are available, unless
 *                    `MAP_FIXED' was used
 * @param: min_alignment: The minimum alignment of the return value. Note that no matter
 *                    what is passed for this value, the actual return value will  always
 *                    be  aligned by at least the size of a single page. If this argument
 *                    isn't a pointer-of-2, then the alignment guarantied for the  return
 *                    value is undefined, except that it will still be at least PAGESIZE!
 * @param: flags:     Set of `MAP_GROWSDOWN | MAP_GROWSUP | MAP_32BIT | MAP_STACK | MAP_NOASLR'
 *                    Additionally,   `MAP_FIXED'   and  `MAP_FIXED_NOREPLACE'   are  accepted.
 *                    Unknown flags are silently ignored.
 * @return: PAGEDIR_PAGEALIGNED * : The base address where the caller's mapping should go
 * @return: MAP_FAILED:             Locks had to be released, but another attempt might succeed.
 *                                  Reacquire  all  required  locks,  and  re-attempt  the call.
 * @throws: E_BADALLOC_INSUFFICIENT_VIRTUAL_MEMORY: Failed to locate a suitably large address
 *                                                  range  that  fits the  given constraints.
 * @throws: E_BADALLOC_ADDRESS_ALREADY_EXISTS:      Both  `MAP_FIXED'  and   `MAP_FIXED_NOREPLACE'
 *                                                  were given, and a pre-existing mapping already
 *                                                  exists within the given address range. */
PUBLIC NOBLOCK WUNUSED NONNULL((1)) void *FCALL
mman_getunmapped_or_unlock(struct mman *__restrict self, void *addr,
                           size_t num_bytes, unsigned int flags,
                           size_t min_alignment,
                           ptrdiff_t min_alignment_offset,
                           struct unlockinfo *unlock)
		THROWS(E_BADALLOC_INSUFFICIENT_VIRTUAL_MEMORY,
		       E_BADALLOC_ADDRESS_ALREADY_EXISTS) {
	void *result;
	/* Deal with MAP_FIXED */
	if (flags & MAP_FIXED) {
		struct mnode const *node;
		byte_t *maxaddr;
		result = (void *)FLOOR_ALIGN((uintptr_t)addr, PAGESIZE);
		/* Check for overflowing `num_bytes' */
		if unlikely(OVERFLOW_UADD((uintptr_t)addr, num_bytes - 1, (uintptr_t *)&maxaddr)) {
			mman_lock_release(self);
			unlockinfo_xunlock(unlock);
			THROW(E_INVALID_ARGUMENT_BAD_VALUE,
			      E_INVALID_ARGUMENT_CONTEXT_MMAP_LENGTH,
			      num_bytes);
		}
		node = mnode_tree_rlocate(self->mm_mappings, addr, maxaddr);
		if (node != NULL) {
			byte_t *max_mapaddr;
			struct mnode_tree_minmax mima;
			if (flags & MAP_FIXED_NOREPLACE) {
				void *node_minaddr, *node_maxaddr;
				node_minaddr = mnode_getminaddr(node);
				node_maxaddr = mnode_getmaxaddr(node);
				mman_lock_release(self);
				unlockinfo_xunlock(unlock);
				THROW(E_BADALLOC_ADDRESS_ALREADY_EXISTS,
				      addr, maxaddr,
				      node_minaddr, node_maxaddr);
			}
			/* Special case: Only  allowed  to mmap  FIXED  into kernel-space
			 *               when using the  kernel page  directory as  base,
			 *               which user-space isn't (normally) allowed to do. */
			if (ADDRRANGE_ISKERN_PARTIAL((byte_t *)addr, maxaddr + 1) &&
			    self != &mman_kernel) {
disallow_mmap:
				mman_lock_release(self);
				unlockinfo_xunlock(unlock);
				THROW(E_BADALLOC_ADDRESS_ALREADY_EXISTS,
				      addr, maxaddr, KS_MINADDR, KS_MAXADDR);
			}
			/* Check if we must split mem-nodes in order to fulfill the request. */
			mnode_tree_minmaxlocate(self->mm_mappings, addr, maxaddr, &mima);
			assert(mima.mm_min && mima.mm_max);
			/* TODO: If we were to work together without our caller (mman_map()),
			 *       then we  could make  this easier  by simply  truncating  the
			 *       pre-existing node,  and only  splitting it  when the  result
			 *       range is fully contained within a single, pre-existing node! */
			if (mnode_getminaddr(mima.mm_min) != result) {
				/* Must split this node! */
				if (mima.mm_min->mn_flags & MNODE_F_NOSPLIT)
					goto disallow_mmap; /* Not allowed! */
				if (!mnode_split_or_unlock(self, mima.mm_min, result, unlock))
					goto must_retry;
				mnode_tree_minmaxlocate(self->mm_mappings, addr, maxaddr, &mima);
				assert(mima.mm_min && mima.mm_max);
			}
			num_bytes += (uintptr_t)addr & PAGEMASK;
			num_bytes   = CEIL_ALIGN(num_bytes, PAGESIZE);
			max_mapaddr = (byte_t *)result + num_bytes - 1;
			if (mnode_getmaxaddr(mima.mm_max) != max_mapaddr) {
				/* Must split this node! */
				if (mima.mm_min->mn_flags & MNODE_F_NOSPLIT)
					goto disallow_mmap; /* Not allowed! */
				TRY {
					if (!mnode_split_or_unlock(self, mima.mm_max, max_mapaddr + 1, unlock))
						goto must_retry;
				} EXCEPT {
					mman_mergenodes(self);
					RETHROW();
				}
			}
#ifndef NDEBUG
			mnode_tree_minmaxlocate(self->mm_mappings, addr, maxaddr, &mima);
			assert(mima.mm_min && mima.mm_max);
			assert(mnode_getminaddr(mima.mm_min) == result);
			assert(mnode_getmaxaddr(mima.mm_max) == max_mapaddr);
#endif /* !NDEBUG */
		}
	} else {
		/* Normal case: automatically select a free location. */
		result = mman_findunmapped(self, addr, num_bytes, flags,
		                           min_alignment, min_alignment_offset);
		if unlikely(result == MAP_FAILED)
			goto err_insufficient_vmem;
	}
	return result;
must_retry:
	return MAP_FAILED;
err_insufficient_vmem:
	/* Throw an insufficient-virtual-memory exception. */
	mman_lock_release(self);
	unlockinfo_xunlock(unlock);
	THROW(E_BADALLOC_INSUFFICIENT_VIRTUAL_MEMORY, num_bytes);
}


DECL_END

#endif /* !GUARD_KERNEL_SRC_MEMORY_MMAN_MMAN_FIND_UNMAPPED_C */
