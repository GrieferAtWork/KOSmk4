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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_SWAP_H
#define GUARD_KERNEL_INCLUDE_KERNEL_SWAP_H 1

#include <kernel/compiler.h>

#include <kernel/memory.h>
#include <kernel/types.h>

#ifdef __CC__
#ifndef CONFIG_NO_SWAP
DECL_BEGIN

typedef physpage_t swappage_t;
typedef physaddr_t swapaddr_t;
#define SWAPPTR_INVALID ((swappage_t)-1)

/* Allocate SWAP memory.
 * @return: * :              The base address for the allocated swap segment.
 * @return: SWAPPTR_INVALID: Failed to allocate swap memory. */
FUNDEF WUNUSED swappage_t
NOTHROW(KCALL swap_malloc)(physpagecnt_t num_pages);

FUNDEF WUNUSED NONNULL((3)) swappage_t
NOTHROW(KCALL swap_malloc_part)(physpagecnt_t min_pages, physpagecnt_t max_pages,
                                physpagecnt_t *__restrict res_pages);

/* Free SWAP memory. */
FUNDEF NOBLOCK void
NOTHROW(KCALL swap_free)(swappage_t start, physpagecnt_t num_pages);

/* Issue asynchronous comments to read/write physical memory to/from SWAP.
 * NOTE: By default, swap reads/writes are performed using DMA,  which
 *       is why operations must be followed by a call to `swap_sync()'
 *       in order to ensure completion. */
FUNDEF void (KCALL swap_read)(swapaddr_t start, physaddr_t buffer, size_t num_bytes);
FUNDEF void (KCALL swap_write)(swapaddr_t start, physaddr_t buffer, size_t num_bytes);

/* Wait for all out-standing swap reads/writes to be completed.
 * @throw: E_IOERROR: The swap back-end has issued an I/O error. */
FUNDEF void (KCALL swap_sync)(void) THROWS(E_IOERROR);

DECL_END
#endif /* !CONFIG_NO_SWAP */
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_SWAP_H */
