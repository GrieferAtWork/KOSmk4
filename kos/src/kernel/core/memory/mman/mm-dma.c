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
#ifndef GUARD_KERNEL_SRC_MEMORY_MMAN_MM_DMA_C
#define GUARD_KERNEL_SRC_MEMORY_MMAN_MM_DMA_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/mman.h>
#include <kernel/mman/mpart.h>
#include <kernel/mman/mm-dma.h>

#include <kos/except.h>

#include <stdbool.h>

DECL_BEGIN

/* Start DMAing on memory within the specified address range.
 * @param: prange:      A callback that is invoked for each affected physical memory range
 *                      Should this callback return `false', all previously acquired DMA
 *                      locks are released, and `mman_startdma[v]()' returns `0'
 * @param: preset:      A callback this is invoked when it was impossible to acquire all
 *                      necessary DMA locks simultaneously without causing a dead-lock.
 *                      This is then resolved by releasing all pre-existing locks, before
 *                      forcibly acquiring+releasing the blocking lock (thus ensuring that
 *                      it has become available), before starting over.
 *                      This callback is then invoked just after all previously acquired
 *                      DMA locks have been released, but just before the blocking lock
 *                      is forcibly acquired. - It's purpose is then to reset whatever
 *                      information was already gathered from then released ranges.
 * @param: arg:         Argument passed to `prange' and `preset' upon execution.
 * @param: lockvec:     Vector of DMA lock slots provided by the caller.
 * @param: lockcnt:     Number of available DMA lock slots (allocated length (not size) of `lockvec')
 * @param: vaddr:       [mman_startdma] The base address where locking should start.
 * @param: num_bytes:   [mman_startdma] The number of continuous bytes that should be locked.
 * @param: buf:         [mman_startdmav] The scatter-gather list of virtual memory ranges to lock.
 * @param: for_writing: When true, unshare copy-on-write mappings of associated memory, allowing the
 *                      caller to then write to the acquired memory ranges without accidentally having
 *                      any changes made appear in PRIVATE mappings of the associated memory region.
 * @return: 0 :         `*prange' returned `false'
 * @return: 0 :         Some portion of the specified address range(s) doesn't actually map to a VM node.
 * @return: 0 :         Some portion of the specified address range(s) maps to a VM node reservation (no associated data part).
 * @return: 0 :         Some portion of the specified address range(s) maps to VIO memory, meaning there is no underlying physical memory.
 * @return: 0 :         [mman_startdma[v]] The equivalent `mman_startdma[v]' would have thrown an exception
 * @return: <= lockcnt: The number of used DMA locks (SUCCESS)
 * @return: >  lockcnt: The number of _REQUIRED_ DMA locks (FAILURE) (All locks that may have already been acqured will have already been released) */
PUBLIC NONNULL((1, 2, 3, 5)) size_t KCALL
mman_startdma(struct mman *__restrict self,
              mdma_range_callback_t prange, mdma_reset_callback_t preset,
              void *arg, struct mdmalock *__restrict lockvec, size_t lockcnt,
              UNCHECKED void *vaddr, size_t num_bytes, bool for_writing)
		THROWS(E_WOULDBLOCK, E_BADALLOC, ...) {
	/* TODO */
	THROW(E_NOT_IMPLEMENTED_TODO);
}

PUBLIC NONNULL((1, 2, 3, 5, 7)) size_t KCALL
mman_startdmav(struct mman *__restrict self,
               mdma_range_callback_t prange, mdma_reset_callback_t preset,
               void *arg, struct mdmalock *__restrict lockvec, size_t lockcnt,
               struct aio_buffer const *__restrict vaddr_buf, bool for_writing)
		THROWS(E_WOULDBLOCK, E_BADALLOC, ...) {
	/* TODO */
	THROW(E_NOT_IMPLEMENTED_TODO);
}

/* Similar to `mman_startdma[v]', however instead used to enumerate the DMA memory range individually.
 * @param: prange:      A callback that is invoked for each affected physical memory range
 *                      Should this callback return `false', enumeration will half and the
 *                      function will return the number of previously successfully enumerated
 *                      DMA bytes.
 * @param: arg:         Argument passed to `prange' upon execution.
 * @param: vaddr:       [mman_startdma] The base address where locking should start.
 * @param: num_bytes:   [mman_startdma] The number of continuous bytes that should be locked.
 * @param: buf:         [mman_startdmav] The scatter-gather list of virtual memory ranges to lock.
 * @param: for_writing: When true, unshare copy-on-write mappings of associated memory, allowing the
 *                      caller to then write to the acquired memory ranges without accidentally having
 *                      any changes made appear in PRIVATE mappings of the associated memory region.
 * @return: * : The number of DMA bytes successfully enumerated (sum of
 *             `num_bytes' in all calls to `*prange', where `true' was returned)
 *              Upon full success, this is identical to the given `num_bytes' / `aio_buffer_size(buf)',
 *              though for the same reasons that `mman_startdma[v]' can fail (s.a. `@return: 0' cases),
 *              this may be less than that */
PUBLIC NONNULL((1, 2)) size_t KCALL
mman_enumdma(struct mman *__restrict self,
             mdma_range_callback_t prange, void *arg,
             UNCHECKED void *vaddr, size_t num_bytes,
             bool for_writing)
		THROWS(E_WOULDBLOCK, E_BADALLOC, ...) {
	/* TODO */
	THROW(E_NOT_IMPLEMENTED_TODO);
}

PUBLIC NONNULL((1, 2, 4)) size_t KCALL
mman_enumdmav(struct mman *__restrict self,
              mdma_range_callback_t prange, void *arg,
              struct aio_buffer const *__restrict vaddr_buf,
              bool for_writing)
		THROWS(E_WOULDBLOCK, E_BADALLOC, ...) {
	/* TODO */
	THROW(E_NOT_IMPLEMENTED_TODO);
}


/* Stop DMAing by releasing all of the specified DMA locks.
 * NOTE: The caller must ensure that `lockcnt == return(mman_startdma*())', and
 *       that the specified `lockvec' is either the exact same `lockvec' originally
 *       passed to `mman_startdma[v]()', or an identical memory copy of it. */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mman_stopdma)(struct mdmalock *__restrict lockvec,
                            size_t lockcnt) {
	/* TODO */
}


DECL_END

#endif /* !GUARD_KERNEL_SRC_MEMORY_MMAN_MM_DMA_C */
