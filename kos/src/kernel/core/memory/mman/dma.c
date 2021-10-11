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
#ifndef GUARD_KERNEL_SRC_MEMORY_MMAN_DMA_C
#define GUARD_KERNEL_SRC_MEMORY_MMAN_DMA_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/mman.h>
#include <kernel/mman/dma.h>

#include <kos/except.h>

#include <stdbool.h>
#include <string.h>

DECL_BEGIN

#if !defined(NDEBUG) && !defined(NDEBUG_FINI)
#define DBG_memset memset
#else /* !NDEBUG && !NDEBUG_FINI */
#define DBG_memset(...) (void)0
#endif /* NDEBUG || NDEBUG_FINI */

/* Stop DMAing by releasing all of the specified DMA locks.
 * NOTE: The  caller  must ensure  that  `lockcnt == return(mman_startdma*())', and
 *       that the specified `lockvec' is either the exact same `lockvec' originally
 *       passed to `mman_startdma[v]()', or an identical memory copy of it. */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mman_stopdma)(struct mdmalock *__restrict lockvec,
                            size_t lockcnt) {
	size_t i;
	/* Release all DMA locks first, and then decref everything in a  second
	 * pass, thus improving cache-locality, as well as semantics, such that
	 * we're invocing decref() with less locks held that we'd do otherwise. */
	for (i = lockcnt; i--;)
		lockvec[i].mdl_part = mpart_dma_dellock(lockvec[i].mdl_part);
	for (i = lockcnt; i--;)
		decref_unlikely(lockvec[i].mdl_part);
	DBG_memset(lockvec, 0xcc, lockcnt, sizeof(struct mdmalock));
}

DECL_END

#ifndef __INTELLISENSE__
#define DEFINE_mman_startdma
#include "dma.c.inl"
#define DEFINE_mman_startdmav
#include "dma.c.inl"
#define DEFINE_mman_enumdma
#include "dma.c.inl"
#define DEFINE_mman_enumdmav
#include "dma.c.inl"
#endif /* !__INTELLISENSE__ */


#endif /* !GUARD_KERNEL_SRC_MEMORY_MMAN_DMA_C */
