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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_MMAN_DMA_H
#define GUARD_KERNEL_INCLUDE_KERNEL_MMAN_DMA_H 1

#include <kernel/compiler.h>

#include <kernel/paging.h>
#include <kernel/types.h>

#include <kernel/mman/mpart.h>
#include <kernel/mman/mpartmeta.h>

#ifdef __CC__
DECL_BEGIN

struct mman;
struct iov_buffer;

/* Callback for enumerating physical memory ranges for the purposes of DMA
 * @param: cookie:    The same `cookie' given to `mman_startdma[v]'
 * @param: paddr:     The physical memory base address of the range.
 * @param: num_bytes: The number of bytes found within the range.
 * @param: lock:      The lock used to lock the associated DMA range. */
typedef __BOOL (KCALL *mdma_range_callback_t)(void *cookie, physaddr_t paddr, size_t num_bytes,
                                              struct mdmalock *__restrict lock);

/* Descriptor for a lock held for the purposes of DMA */
struct mdmalock {
	REF struct mpart *mdl_part; /* [1..1] The data  part  to  which a  DMA-lock  is  being  held.
	                             * This lock will be released via a call to `mpart_dma_dellock()' */
};

/* Release the given DMA lock */
#ifdef __INTELLISENSE__
NOBLOCK NONNULL((1)) void
NOTHROW(mman_dmalock_release)(struct mdmalock *__restrict self);
#else /* __INTELLISENSE__ */
#define mman_dmalock_release(x) \
	decref_unlikely(mpart_dma_dellock((x)->mdl_part))
#endif /* !__INTELLISENSE__ */

/* Start DMAing on memory within the specified address range.
 * @param: prange:      A callback that is invoked for each affected physical memory range
 *                      Should this callback return  `false', all previously acquired  DMA
 *                      locks are released, and `mman_startdma[v]()' returns `0'
 * @param: cookie:      Cookie-argument passed to `prange' upon execution.
 * @param: lockvec:     Vector of DMA lock slots provided by the caller.
 * @param: lockcnt:     Number of available DMA lock slots (allocated length (not size) of `lockvec')
 * @param: addr:        [mman_startdma] The base address where locking should start.
 * @param: num_bytes:   [mman_startdma] The number of continuous bytes that should be locked.
 * @param: addr_v:      [mman_startdmav] The scatter-gather list of virtual memory ranges to lock.
 * @param: flags:       Set of `0 | MMAN_FAULT_F_WRITE'. When `MMAN_FAULT_F_WRITE' is given, unshare
 *                      copy-on-write  mappings of  associated memory,  allowing the  caller to then
 *                      write  to the acquired memory ranges without accidentally having any changes
 *                      made appear in PRIVATE mappings of the associated memory region.
 * @return: 0 :         `*prange' returned `false'
 * @return: 0 :         Some portion of the specified address range(s) doesn't actually map to a VM node.
 * @return: 0 :         Some portion of the specified address range(s) maps to a VM node reservation (no associated data part).
 * @return: 0 :         Some portion of the specified address range(s) maps to VIO memory, meaning there is no underlying physical memory.
 * @return: <= lockcnt: The number of used DMA locks (SUCCESS)
 * @return: >  lockcnt: The number of _REQUIRED_ DMA locks (FAILURE) (All locks that may have already been acqured will have already been released)
 * @throw: E_FSERROR_READONLY: Attempted to fault write-access for a SHARED mapping of a MFILE_F_READONLY file. */
FUNDEF BLOCKING_IF(BLOCKING(prange)) NONNULL((1, 2, 4)) size_t KCALL
mman_startdma(struct mman *__restrict self, mdma_range_callback_t prange,
              void *cookie, struct mdmalock *__restrict lockvec, size_t lockcnt,
              UNCHECKED void *addr, size_t num_bytes, unsigned int flags)
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_FSERROR_READONLY, ...);
FUNDEF BLOCKING_IF(BLOCKING(prange)) NONNULL((1, 2, 4, 6)) size_t KCALL
mman_startdmav(struct mman *__restrict self, mdma_range_callback_t prange,
               void *cookie, struct mdmalock *__restrict lockvec, size_t lockcnt,
               struct iov_buffer const *__restrict addr_v, unsigned int flags)
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_FSERROR_READONLY, ...);
#ifdef __cplusplus
extern "C++" {
FUNDEF BLOCKING_IF(BLOCKING(prange)) NONNULL((1, 2, 4, 6)) size_t KCALL
mman_startdma(struct mman *__restrict self, mdma_range_callback_t prange,
              void *cookie, struct mdmalock *__restrict lockvec, size_t lockcnt,
              struct iov_buffer const *__restrict addr_v, unsigned int flags)
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_FSERROR_READONLY, ...)
		ASMNAME("mman_startdmav");
} /* extern "C++" */
#endif /* __cplusplus */

/* Similar to `mman_startdma[v]', however instead used to enumerate the DMA memory range individually.
 * @param: prange:    A  callback that is  invoked for each  affected physical memory range
 *                    Should this callback  return `false', enumeration  will halt and  the
 *                    function will return the number of previously successfully enumerated
 *                    DMA bytes.
 * @param: cookie:    Cookie-argument passed to `prange' upon execution.
 * @param: addr:      [mman_startdma] The base address where locking should start.
 * @param: num_bytes: [mman_startdma] The number of continuous bytes that should be locked.
 * @param: addr_v:    [mman_startdmav] The scatter-gather list of virtual memory ranges to lock.
 * @param: flags:     Set of `0 | MMAN_FAULT_F_WRITE'. When `MMAN_FAULT_F_WRITE' is given, unshare
 *                    copy-on-write  mappings of  associated memory,  allowing the  caller to then
 *                    write  to the acquired memory ranges without accidentally having any changes
 *                    made appear in PRIVATE mappings of the associated memory region.
 * @return: * : The number of DMA bytes successfully enumerated (sum of
 *             `num_bytes' in all calls to `*prange', where `true' was returned)
 *              Upon full success, this is identical to the given `num_bytes' / `iov_buffer_size(buf)',
 *              though for the same reasons that `mman_startdma[v]' can fail (s.a. `@return: 0' cases),
 *              this may be less than that.
 * @throw: E_FSERROR_READONLY: Attempted to fault write-access for a SHARED mapping of a MFILE_F_READONLY file. */
FUNDEF BLOCKING_IF(BLOCKING(prange)) NONNULL((1, 2)) size_t KCALL
mman_enumdma(struct mman *__restrict self,
             mdma_range_callback_t prange, void *cookie,
             void *addr, size_t num_bytes, unsigned int flags)
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_FSERROR_READONLY, ...);
FUNDEF BLOCKING_IF(BLOCKING(prange)) NONNULL((1, 2, 4)) size_t KCALL
mman_enumdmav(struct mman *__restrict self,
              mdma_range_callback_t prange, void *cookie,
              struct iov_buffer const *__restrict addr_v,
              unsigned int flags)
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_FSERROR_READONLY, ...);
#ifdef __cplusplus
extern "C++" {
FUNDEF BLOCKING_IF(BLOCKING(prange)) NONNULL((1, 2, 4)) size_t KCALL
mman_enumdma(struct mman *__restrict self,
             mdma_range_callback_t prange, void *cookie,
             struct iov_buffer const *__restrict addr_v,
             unsigned int flags)
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_FSERROR_READONLY, ...)
		ASMNAME("mman_enumdmav");
} /* extern "C++" */
#endif /* __cplusplus */


/* Stop DMAing by releasing all of the specified DMA locks.
 * NOTE: The  caller  must ensure  that  `lockcnt == return(mman_startdma*())', and
 *       that the specified `lockvec' is either the exact same `lockvec' originally
 *       passed to `mman_startdma[v]()', or an identical memory copy of it. */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mman_stopdma)(struct mdmalock *__restrict lockvec, size_t lockcnt);


DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_MMAN_DMA_H */
