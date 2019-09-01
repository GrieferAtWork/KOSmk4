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
#ifdef __INTELLISENSE__
#if 0
#define VM_GETFREE_VMB 1
#else
#define VM_GETFREE_VM 1
#endif

#ifdef VM_GETFREE_VMB
#include "builder.c"
#else
#include "vm.c"
#endif
#endif

#include <kernel/driver-param.h>

DECL_BEGIN

/* Return a pseudo-random number between `0..rand_size-1' (inclusively),
 * but prefer lower numbers over larger ones, generally aiming to
 * return values around `rand_avg'
 *
 *   Value...
 * C                 _
 * h               _- _
 * a            __-    _
 * n       ___--        -__
 * c __----                -----------___
 * e                                     - <0 chance
 *
 *                   ^                   ^
 *                   |                   |
 *                   rand_avg            rand_limit
 *
 */
#ifdef VM_GETFREE_VMB
INTDEF NOBLOCK uintptr_t
NOTHROW(KCALL krand_exponential)(uintptr_t rand_limit, uintptr_t rand_avg);
#else
INTERN NOBLOCK uintptr_t
NOTHROW(KCALL krand_exponential)(uintptr_t rand_limit, uintptr_t rand_avg) {
	uintptr_t result;
	assert(rand_limit != 0);
	result = krandptr() % rand_limit;
	result &= krandptr() % rand_limit;
	result += (krandptr() % rand_limit) >> 16;
	result += rand_avg;
	result &= ((krandptr() % rand_limit) |
	           (krandptr() % rand_limit) |
	           (krandptr() % rand_limit));
	result %= rand_limit; /* Prevent overflow. */
	return result;
}
#endif

#ifdef VM_GETFREE_VMB
#define VM_FUNCTION(x) vmb_##x
#else
#define VM_FUNCTION(x) vm_##x
#endif


#if !defined(NDEBUG) && 1
#define ASSERT_RESULT(result) \
	(assertf(!(result & (min_alignment_in_pages - 1)), \
	        #result "                = %p (%p)\n" \
	         "num_pages              = %Iu\n" \
	        #result " + num_pages    = %p (%p)\n" \
	         "mode                   = %#x\n" \
	         "min_alignment_in_pages = %Iu\n" \
	         , VM_PAGE2ADDR(result), result, num_pages \
	         , VM_PAGE2ADDR(result+num_pages), result+num_pages \
	         , mode, min_alignment_in_pages), \
	 assertf(!VM_FUNCTION(isused)(self, result, result + num_pages - 1), \
	        #result "                = %p (%p)\n" \
	         "num_pages              = %Iu\n" \
	        #result " + num_pages    = %p (%p)\n" \
	         "mode                   = %#x\n" \
	         "min_alignment_in_pages = %Iu\n" \
	         , VM_PAGE2ADDR(result), result, num_pages \
	         , VM_PAGE2ADDR(result+num_pages), result+num_pages \
	         , mode, min_alignment_in_pages))
#else
#define ASSERT_RESULT(result) (void)0
#endif

#ifndef VM_ASLR_DISABLED_DEFINED
#define VM_ASLR_DISABLED_DEFINED 1

/* Get/set ASLR-disabled (defaults to `false'; can also be
 * enabled by passing `noaslr' on the kernel commandline)
 * When enabled, the `VM_GETFREE_ASLR' is simply ignored
 * when passed to either `vm_getfree()' or `vmb_getfree()' */
#ifdef VM_GETFREE_VMB
INTDEF bool vm_aslr_disabled;
#else /* VM_GETFREE_VMB */
INTERN bool vm_aslr_disabled = false;
DEFINE_CMDLINE_FLAG(vm_aslr_disabled, "noaslr");
PUBLIC bool NOTHROW(KCALL vm_get_aslr_disabled)(void) {
	return ATOMIC_READ(vm_aslr_disabled);
}
PUBLIC bool NOTHROW(KCALL vm_set_aslr_disabled)(bool new_disabled) {
	return ATOMIC_XCH(vm_aslr_disabled, new_disabled);
}
#endif /* !VM_GETFREE_VMB */
#endif /* !VM_ASLR_DISABLED_DEFINED */



/* Determine a suitable, free memory location for `num_pages'
 * aligned by a multiple of `min_alignment_in_pages' pages.
 * Search happens as follows:
 *   #1: Search according to `VM_GETFREE_ABOVE/VM_GETFREE_BELOW'
 *       Additionally, check for surrounding nodes which are set
 *       up as GUARD nodes. - If such a node is found, it's size
 *       is considered to have reached its maximum potential for
 *       this purpose (limited by how often `vn_guard' can be
 *       decremented, as well as any other memory mapping it may
 *       run into before then)
 *       If a this process yields only a single candidate, that
 *       candidate is returned as result.
 *       If a this process yields more than 1 candidate, the one chosen
 *       depends on `VM_GETFREE_ABOVE / VM_GETFREE_BELOW / VM_GETFREE_ASLR'
 *        - VM_GETFREE_ABOVE: The candidate with the lowest memory address is used
 *        - VM_GETFREE_BELOW: The candidate with the greatest memory address is used
 *        - VM_GETFREE_ABOVE + VM_GETFREE_ASLR:
 *          Return the `x = rand() / RAND_MAX; x*x*NUM_CANDIDATES'th candidate
 *        - VM_GETFREE_BELOW + VM_GETFREE_ASLR:
 *          Return the `x = 1 - (rand() / RAND_MAX); x*x*NUM_CANDIDATES'th candidate
 *   #2: Repeat step #1, but ignore the potentials of GUARD nodes.
 *   #3: Return `VM_GETFREE_ERROR'
 * WARNING: The caller must be holding a read-lock to `self'.
 * @param: mode:                   Set of `VM_GETFREE_F*'
 * @param: hint:                   A hint used as base when searching for free memory ranges.
 * @param: min_alignment_in_pages: The minimum alignment required from the returned pointer (or `1')
 * @return: VM_GETFREE_ERROR:      No more virtual memory available. */
#ifdef VM_GETFREE_VMB
PUBLIC NOBLOCK WUNUSED vm_vpage_t
NOTHROW(KCALL vmb_getfree)(struct vmb *__restrict self,
                           vm_vpage_t hint, size_t num_pages,
                           size_t min_alignment_in_pages,
                           unsigned int mode)
#else
PUBLIC NOBLOCK WUNUSED vm_vpage_t
NOTHROW(KCALL vm_getfree)(struct vm *__restrict self,
                          vm_vpage_t hint, size_t num_pages,
                          size_t min_alignment_in_pages,
                          unsigned int mode)
#endif
{
	bool ignore_guard = false;
	bool was_strict   = mode & VM_GETFREE_STRICT;
	vm_nodetree_minmax_t minmax;
	vm_vpage_t minpage, maxpage;
	/* When ASLR disabled, clear the ASLR flag from `mode', effectively disabling it. */
	if (vm_aslr_disabled)
		mode &= ~VM_GETFREE_ASLR;
#ifdef VM_GETFREE_VM
	assert(sync_reading(self) || !isshared(self) ||
	       (!PREEMPTION_ENABLED() && cpu_online_count <= 1));
#endif /* VM_GETFREE_VM */
	assertf(min_alignment_in_pages != 0, "min_alignment_in_pages must be non-zero");
	assertf((min_alignment_in_pages & (min_alignment_in_pages - 1)) == 0,
	        "min_alignment_in_pages must be power-of-2, but is actually %Iu (%#Iu)",
	        min_alignment_in_pages, min_alignment_in_pages);
	if unlikely(!num_pages)
		num_pages = 1;
again:
	if (mode & VM_GETFREE_BELOW) {
		if (OVERFLOW_USUB(hint, num_pages, &minpage)) {
			if (mode & VM_GETFREE_STRICT)
				goto err;
			if unlikely(num_pages > (size_t)VM_VPAGE_MAX)
				goto err;
			hint = 0;
			mode &= ~VM_GETFREE_BELOW;
			mode |= VM_GETFREE_STRICT;
			goto again;
		}
		minpage &= ~(min_alignment_in_pages - 1);
		maxpage = hint - 1;
		for (;;) {
			minmax.mm_min = minmax.mm_max = NULL;
			vm_nodetree_minmaxlocate(self->v_tree,
			                         minpage,
			                         maxpage,
			                         &minmax);
			assert((minmax.mm_min != NULL) == (minmax.mm_max != NULL));
			if (!minmax.mm_min) {
				struct vm_node *next_below;
				struct vm_node *next_above;
				size_t rand_size;
				vm_vpage_t prev_end;
#ifdef VM_GETFREE_VMB
				if (PRANGE_IS_KERNEL_PARTIAL(minpage, maxpage + 1)) {
					/* Must not return locations in kernel memory.
					 * -> Regular VMs prevent this with the kernel-reserve-page, however
					 *    we don't have that luxury and must therefor manually check for
					 *    any potential overlaps with kernel-space! */
#ifdef HIGH_MEMORY_KERNEL
					maxpage = (vm_vpage_t)KERNEL_BASE_PAGE - 1;
					goto set_new_minpage_below;
#else
					break; /* Mapping can't go below here! */
#endif
				}
#endif /* VM_GETFREE_VMB */
				if (ignore_guard) {
					if (mode & VM_GETFREE_ASLR) {
						next_below = minpage ? VM_FUNCTION(find_last_node_lower_equal)(self, minpage - 1) : NULL;
						prev_end   = next_below ? VM_NODE_END(next_below) : (vm_vpage_t)0;
#ifdef VM_GETFREE_VMB
#ifdef LOW_MEMORY_KERNEL
						if (prev_end < (vm_vpage_t)KERNEL_CEILING_PAGE)
							prev_end = (vm_vpage_t)KERNEL_CEILING_PAGE;
#endif
#endif /* VM_GETFREE_VMB */
						rand_size = (size_t)(minpage - prev_end);
						if (rand_size > 1) {
							/* Add an offset >= 0 && < rand_size */
							minpage -= krand_exponential(rand_size, num_pages);
							/* Re-align the min-page. */
							minpage += (min_alignment_in_pages - 1);
							minpage &= ~(min_alignment_in_pages - 1);
						}
					}
					assertf(!VM_FUNCTION(isused)(self, minpage, minpage + num_pages - 1),
					        "minpage                = %p (%p)\n"
					        "num_pages              = %Iu\n"
					        "minpage + num_pages    = %p (%p)\n"
					        "mode                   = %#x\n"
					        "min_alignment_in_pages = %Iu\n",
					        VM_PAGE2ADDR(minpage), minpage, num_pages, VM_PAGE2ADDR(minpage + num_pages), minpage + num_pages, mode, min_alignment_in_pages);
					assertf(!(minpage & (min_alignment_in_pages - 1)),
					        "minpage                = %p (%p)\n"
					        "num_pages              = %Iu\n"
					        "minpage + num_pages    = %p (%p)\n"
					        "mode                   = %#x\n"
					        "min_alignment_in_pages = %Iu\n",
					        VM_PAGE2ADDR(minpage), minpage, num_pages, VM_PAGE2ADDR(minpage + num_pages), minpage + num_pages, mode, min_alignment_in_pages);

					return minpage;
				}
				next_below = VM_FUNCTION(find_last_node_lower_equal)(self, minpage - 1);
				if (next_below && next_below->vn_guard &&
				    (next_below->vn_flags & VM_NODE_FLAG_GROWSUP)) {
					vm_vpage_t guard_maxpage = VM_NODE_MAX(next_below);
					if (OVERFLOW_UADD(guard_maxpage, next_below->vn_guard, &guard_maxpage))
						guard_maxpage = (vm_vpage_t)-1;
					if (guard_maxpage >= minpage) {
						if (!VM_NODE_MIN(next_below))
							break;
						maxpage = VM_NODE_MIN(next_below) - 1;
						goto set_new_minpage_below;
					}
				}
				next_above = VM_FUNCTION(find_first_node_greater_equal)(self, maxpage + 1);
				if (next_above && next_above->vn_guard &&
				    !(next_above->vn_flags & VM_NODE_FLAG_GROWSUP)) {
					vm_vpage_t guard_minpage = VM_NODE_MIN(next_above);
					vm_vpage_t guard_limit   = next_below ? VM_NODE_END(next_below) : (vm_vpage_t)0;
#ifdef VM_GETFREE_VMB
#ifdef LOW_MEMORY_KERNEL
					if (guard_limit < (vm_vpage_t)KERNEL_CEILING_PAGE)
						guard_limit = (vm_vpage_t)KERNEL_CEILING_PAGE;
#endif
#endif /* VM_GETFREE_VMB */
					if (OVERFLOW_USUB(guard_minpage, next_above->vn_guard, &guard_minpage))
						guard_minpage = 0;
					if (guard_minpage < guard_limit)
						guard_minpage = guard_limit;
					if (guard_minpage >= maxpage) {
						maxpage = guard_minpage - 1;
						goto set_new_minpage_below;
					}
				}
				if (mode & VM_GETFREE_ASLR) {
					prev_end = next_below ? VM_NODE_END(next_below) : (vm_vpage_t)0;
#ifdef VM_GETFREE_VMB
#ifdef LOW_MEMORY_KERNEL
					if (prev_end < (vm_vpage_t)KERNEL_CEILING_PAGE)
						prev_end = (vm_vpage_t)KERNEL_CEILING_PAGE;
#endif
#endif /* VM_GETFREE_VMB */
					rand_size = (size_t)(minpage - prev_end);
					if (rand_size > 1) {
						/* Add an offset >= 0 && < rand_size */
						minpage -= krand_exponential(rand_size, num_pages);
						/* Re-align the min-page. */
						minpage += (min_alignment_in_pages - 1);
						minpage &= ~(min_alignment_in_pages - 1);
					}
				}
				ASSERT_RESULT(minpage);
				return minpage;
			}
			/* Continue searching above the limit. */
			maxpage = minmax.mm_min_min - 1;
set_new_minpage_below:
			if (OVERFLOW_USUB(maxpage, num_pages - 1, &minpage))
				break;
		}
		if (!(mode & VM_GETFREE_STRICT)) {
			mode &= ~VM_GETFREE_BELOW;
			mode |= VM_GETFREE_STRICT;
			goto again;
		}
	} else {
		minpage = hint & ~(min_alignment_in_pages - 1);
		if (OVERFLOW_UADD(minpage, num_pages - 1, &maxpage) ||
		    maxpage > VM_VPAGE_MAX) {
			if (mode & VM_GETFREE_STRICT)
				goto err;
			hint = VM_VPAGE_MAX - num_pages;
			mode |= (VM_GETFREE_BELOW | VM_GETFREE_STRICT);
			goto again;
		}
		for (;;) {
			minmax.mm_min = minmax.mm_max = NULL;
			vm_nodetree_minmaxlocate(self->v_tree,
			                         minpage,
			                         maxpage,
			                         &minmax);
			assert((minmax.mm_min != NULL) == (minmax.mm_max != NULL));
			if (!minmax.mm_min) {
				struct vm_node *next_below;
				struct vm_node *next_above;
				size_t rand_size;
				vm_vpage_t next_start;
#ifdef VM_GETFREE_VMB
				if (PRANGE_IS_KERNEL_PARTIAL(minpage, maxpage + 1)) {
					/* Must not return locations in kernel memory.
					 * -> Regular VMs prevent this with the kernel-reserve-page, however
					 *    we don't have that luxury and must therefor manually check for
					 *    any potential overlaps with kernel-space! */
#ifdef LOW_MEMORY_KERNEL
					minpage = ((vm_vpage_t)KERNEL_CEILING_PAGE - 1 + min_alignment_in_pages) & ~(min_alignment_in_pages - 1);
					goto set_new_maxpage_above;
#else
					break; /* Mapping can't go above here! */
#endif
				}
#endif /* VM_GETFREE_VMB */
				if (ignore_guard) {
					if (mode & VM_GETFREE_ASLR) {
						next_above = VM_FUNCTION(find_first_node_greater_equal)(self, maxpage + 1);
						next_start = next_above ? VM_NODE_MIN(next_above) : (vm_vpage_t)VM_VPAGE_MAX;
#ifdef VM_GETFREE_VMB
#ifdef HIGH_MEMORY_KERNEL
						if (next_start > (vm_vpage_t)KERNEL_BASE_PAGE)
							next_start = (vm_vpage_t)KERNEL_BASE_PAGE;
#endif
#endif /* VM_GETFREE_VMB */
						rand_size = (size_t)(next_start - maxpage);
						if (rand_size > 1) {
							/* Add an offset >= 0 && < rand_size */
							minpage += krand_exponential(rand_size, num_pages);
							/* Re-align the min-page. */
							minpage += (min_alignment_in_pages - 1);
							minpage &= ~(min_alignment_in_pages - 1);
						}
					}
					ASSERT_RESULT(minpage);
					return minpage;
				}
				next_above = VM_FUNCTION(find_first_node_greater_equal)(self, maxpage + 1);
				if (next_above && next_above->vn_guard &&
				    !(next_above->vn_flags & VM_NODE_FLAG_GROWSUP)) {
					vm_vpage_t guard_minpage = VM_NODE_MIN(next_above);
					if (OVERFLOW_USUB(guard_minpage, next_above->vn_guard, &guard_minpage))
						guard_minpage = 0;
					if (guard_minpage <= maxpage) {
						minpage = VM_NODE_MAX(next_above) + 1;
						goto set_new_maxpage_above;
					}
				}
				next_below = VM_FUNCTION(find_last_node_lower_equal)(self, minpage - 1);
				if (next_below && next_below->vn_guard &&
				    (next_below->vn_flags & VM_NODE_FLAG_GROWSUP)) {
					vm_vpage_t guard_maxpage = VM_NODE_MAX(next_below);
					vm_vpage_t guard_limit   = next_above ? VM_NODE_MIN(next_above) - 1 : (vm_vpage_t)VM_VPAGE_MAX;
#ifdef VM_GETFREE_VMB
#ifdef HIGH_MEMORY_KERNEL
					if (guard_limit > (vm_vpage_t)KERNEL_BASE_PAGE)
						guard_limit = (vm_vpage_t)KERNEL_BASE_PAGE;
#endif
#endif /* VM_GETFREE_VMB */
					if (OVERFLOW_UADD(guard_maxpage, next_below->vn_guard, &guard_maxpage))
						guard_maxpage = (vm_vpage_t)-1;
					if (guard_maxpage > guard_limit)
						guard_maxpage = guard_limit;
					if (guard_maxpage >= minpage) {
						minpage = guard_maxpage + 1;
						goto set_new_maxpage_above;
					}
				}
				if (mode & VM_GETFREE_ASLR) {
					next_start = next_above ? VM_NODE_MIN(next_above) : (vm_vpage_t)VM_VPAGE_MAX;
#ifdef VM_GETFREE_VMB
#ifdef HIGH_MEMORY_KERNEL
					if (next_start > (vm_vpage_t)KERNEL_BASE_PAGE)
						next_start = (vm_vpage_t)KERNEL_BASE_PAGE;
#endif
#endif /* VM_GETFREE_VMB */
					rand_size = (size_t)(next_start - maxpage);
					if (rand_size > 1) {
						/* Add an offset >= 0 && < rand_size */
						minpage += krand_exponential(rand_size, num_pages);
						/* Re-align the min-page. */
						minpage += (min_alignment_in_pages - 1);
						minpage &= ~(min_alignment_in_pages - 1);
					}
				}
				ASSERT_RESULT(minpage);
				return minpage;
			}
			/* Continue searching above the limit. */
			minpage = (minmax.mm_max_max + min_alignment_in_pages) & ~(min_alignment_in_pages - 1);
set_new_maxpage_above:
			if (OVERFLOW_UADD(minpage, num_pages - 1, &maxpage) ||
			    maxpage > VM_VPAGE_MAX)
				break;
		}
		if (!(mode & VM_GETFREE_STRICT)) {
			mode &= ~VM_GETFREE_BELOW;
			mode |= VM_GETFREE_STRICT;
			goto again;
		}
	}
	if (!ignore_guard) {
		if (!was_strict)
			mode &= ~VM_GETFREE_STRICT;
		ignore_guard = true;
		goto again;
	}
err:
	return VM_GETFREE_ERROR;
}

#undef ASSERT_RESULT

DECL_END

#undef VM_FUNCTION

#undef VM_GETFREE_VMB
#undef VM_GETFREE_VM

