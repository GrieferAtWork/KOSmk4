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
#ifndef GUARD_KERNEL_SRC_MEMORY_SWAP_C
#define GUARD_KERNEL_SRC_MEMORY_SWAP_C 1

#include <kernel/compiler.h>

#include <kernel/except.h>
#include <kernel/panic.h>
#include <kernel/swap.h>
#include <kernel/types.h>

#include <assert.h>

DECL_BEGIN

#ifndef CONFIG_NO_SWAP

/* Allocate SWAP memory.
 * @return: * :              The base address for the allocated swap segment.
 * @return: SWAPPTR_INVALID: Failed to allocate swap memory. */
PUBLIC WUNUSED swappage_t
NOTHROW(KCALL swap_malloc)(physpagecnt_t num_pages) {
	physpagecnt_t res_pages;
	swappage_t result;
	result = swap_malloc_part(num_pages,
	                          num_pages,
	                          &res_pages);
	assert(result == SWAPPTR_INVALID ||
	       (res_pages == num_pages));
	return result;
}

PUBLIC WUNUSED NONNULL((3)) swappage_t
NOTHROW(KCALL swap_malloc_part)(physpagecnt_t min_pages, physpagecnt_t max_pages,
                                physpagecnt_t *__restrict res_pages) {
	(void)min_pages;
	(void)max_pages;
	(void)res_pages;
	COMPILER_IMPURE();
	*res_pages = 0;
	return SWAPPTR_INVALID;
}

/* Free SWAP memory. */
PUBLIC NOBLOCK void
NOTHROW(KCALL swap_free)(swappage_t start, physpagecnt_t num_pages) {
	(void)start;
	(void)num_pages;
	/* TODO */
	COMPILER_IMPURE();
	kernel_panic("TODO");
}

/* Issue asynchronous comments to read/write physical memory to/from SWAP.
 * NOTE: By default, swap reads/writes are performed using DMA,  which
 *       is why operations must be followed by a call to `swap_sync()'
 *       in order to ensure completion. */
PUBLIC void KCALL
swap_read(swapaddr_t start,
          physaddr_t buffer,
          size_t num_bytes) {
	(void)start;
	(void)buffer;
	(void)num_bytes;
	COMPILER_IMPURE();
	THROW(E_NOT_IMPLEMENTED_TODO);
}

PUBLIC void KCALL
swap_write(swapaddr_t start,
           physaddr_t buffer,
           size_t num_bytes) {
	(void)start;
	(void)buffer;
	(void)num_bytes;
	COMPILER_IMPURE();
	THROW(E_NOT_IMPLEMENTED_TODO);
}

/* Wait for all out-standing swap reads/writes to be completed.
 * @throw: E_IOERROR: The swap back-end has issued an I/O error. */
PUBLIC void KCALL swap_sync(void) THROWS(E_IOERROR) {
	COMPILER_IMPURE();
	THROW(E_NOT_IMPLEMENTED_TODO);
}

#endif /* !CONFIG_NO_SWAP */

DECL_END

#endif /* !GUARD_KERNEL_SRC_MEMORY_SWAP_C */
