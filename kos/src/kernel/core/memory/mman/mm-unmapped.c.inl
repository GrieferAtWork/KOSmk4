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

#include <hybrid/align.h>

#include <kos/except.h>

#include <assert.h>
#include <stddef.h>
#include <stdint.h>

DECL_BEGIN

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
		void *result_minaddr, *result_maxaddr;
		/* Figure out the bounds between which the mapping must be placed. */
		if (self == &mman_kernel && ADDR_ISKERN(addr)) {
			/* Kernel-space requesting a memory location in kernel-space. */
#ifdef KERNELSPACE_BASE
			result_minaddr = (void *)KERNELSPACE_BASE;
#else /* KERNELSPACE_BASE */
			result_minaddr = (void *)0;
#endif /* !KERNELSPACE_BASE */
#ifdef KERNELSPACE_END
			result_maxaddr = (byte_t *)KERNELSPACE_END - num_bytes;
#else /* KERNELSPACE_END */
			result_maxaddr = (byte_t *)0 - num_bytes;
#endif /* KERNELSPACE_END */
		} else {
			/* Allocate in user-space. */
			result_minaddr = mman_getunmapped_user_minaddr;
#ifdef KERNELSPACE_LOWMEM
			COMPILER_READ_BARRIER();
			if unlikely((byte_t *)result_minaddr < (byte_t *)KERNELSPACE_END)
				result_minaddr = (byte_t *)KERNELSPACE_END;
#endif /* KERNELSPACE_LOWMEM */
			if ((byte_t *)addr < (byte_t *)result_minaddr) {
				addr = flags & MMAN_GETUNMAPPED_F_STACK
				       ? mman_getunmapped_user_stkbase
				       : mman_getunmapped_user_defbase;
				if unlikely((byte_t *)addr < (byte_t *)result_minaddr)
					addr = result_minaddr;
			}
#ifdef USERSPACE_END
			result_maxaddr = (byte_t *)USERSPACE_END - num_bytes;
#elif defined(KERNELSPACE_HIGHMEM) && defined(KERNELSPACE_BASE)
			result_maxaddr = (byte_t *)KERNELSPACE_BASE - num_bytes;
#else /* USERSPACE_END */
			result_maxaddr = (byte_t *)0 - num_bytes;
#endif /* USERSPACE_END */
		}
#if __SIZEOF_POINTER__ > 4
		if (flags & MMAN_GETUNMAPPED_F_32BIT) {
			void *limit;
			limit = (void *)(uintptr_t)(((size_t)UINT32_MAX + 1) - num_bytes);
			if ((byte_t *)result_maxaddr > (byte_t *)limit)
				result_maxaddr = limit;
		}
#endif /* __SIZEOF_POINTER__ > 4 */

		/* Safety check: Is the range of allowed addresses non-empty? */
		if unlikely(!(result_minaddr <= result_maxaddr))
			goto err_already_exists_or_nomem;

		mnode_tree_minmaxlocate(self->mm_mappings,
		                        result_minaddr,
		                        result_maxaddr,
		                        &mima);
		assert((mima.mm_min != NULL) == (mima.mm_max != NULL));

		if (MMAN_GETUNMAPPED_ISBELOW(flags)) {
			/* TODO: Like `fallback', but try to find something below `addr' first */
		} else if (MMAN_GETUNMAPPED_ISABOVE(flags)) {
			/* TODO: Like `fallback', but try to find something above `addr' first */
		} else {
			/* TODO: Like `fallback', but try to find something close to `addr' first */
		}

		/* TODO: As fallback: Search the entirety of `result_minaddr...result_maxaddr'
		 *       and return the start (or random offset into) the first (or a random)
		 *       slot that is large enough
		 * NOTE: When `MMAN_GETUNMAPPED_F_STACK' is set, then try to keep a an at least
		 *       1-page-large gap above and the result mapping (but allow this gap to
		 *       be omitted if no location was found that was large enough to also
		 *       include the gap) */
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

