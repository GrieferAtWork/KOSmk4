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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_SWAP_H
#define GUARD_KERNEL_INCLUDE_KERNEL_SWAP_H 1

#include <kernel/compiler.h>

#include <kernel/memory.h>
#include <kernel/types.h>
#include <kernel/vm.h>

DECL_BEGIN

#ifdef __CC__
#ifndef CONFIG_NO_SWAP

typedef vm_spage_t swapptr_t;
#define SWAPPTR_INVALID   ((swapptr_t)-1)

/* Allocate SWAP memory.
 * @return: * :              The base address for the allocated swap segment.
 * @return: SWAPPTR_INVALID: Failed to allocate swap memory. */
FUNDEF swapptr_t NOTHROW(KCALL swap_malloc)(pagecnt_t num_pages);
FUNDEF NONNULL((3)) swapptr_t
NOTHROW(KCALL swap_malloc_part)(pagecnt_t min_pages, pagecnt_t max_pages,
                                pagecnt_t *__restrict res_pages);

/* Free SWAP memory. */
FUNDEF NOBLOCK void NOTHROW(KCALL swap_free)(swapptr_t start, pagecnt_t num_pages);

/* Issue asynchronous comments to read/write physical memory to/from SWAP.
 * NOTE: By default, swap reads/writes are performed using DMA, which
 *       is why operations must be followed by a call to `swap_sync()'
 *       in order to ensure completion. */
FUNDEF void (KCALL swap_read)(swapptr_t start, vm_ppage_t buffer, pagecnt_t num_pages);
FUNDEF void (KCALL swap_write)(swapptr_t start, vm_ppage_t buffer, pagecnt_t num_pages);

/* Wait for all out-standing swap reads/writes to be completed.
 * @throw: E_IOERROR: The swap back-end has issued an I/O error. */
FUNDEF void (KCALL swap_sync)(void) THROWS(E_IOERROR);

#endif /* !CONFIG_NO_SWAP */
#endif /* __CC__ */

DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_SWAP_H */
