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
#include "dma.c"
#define DEFINE_mman_startdma
//#define DEFINE_mman_startdmav
//#define   DEFINE_mman_enumdma
//#define  DEFINE_mman_enumdmav
#endif /* __INTELLISENSE__ */

#include <kernel/iovec.h>
#include <kernel/malloc.h>
#include <kernel/mman/fault.h>
#include <kernel/mman/mnode.h>
#include <kernel/mman/mpart.h>
#include <sched/task.h>

#include <hybrid/align.h>
#include <hybrid/atomic.h>
#include <hybrid/minmax.h>

#include <assert.h>
#include <stddef.h>

DECL_BEGIN

#undef LOCAL_IS_ENUM
#undef LOCAL_IS_VECTOR
#ifdef DEFINE_mman_startdma
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
 * @return: >  lockcnt: The number of _REQUIRED_ DMA locks (FAILURE) (All locks that may have already been acqured will have already been released) */
PUBLIC BLOCKING_IF(BLOCKING(prange)) NONNULL((1, 2, 4)) size_t KCALL
mman_startdma(struct mman *__restrict self, mdma_range_callback_t prange,
              void *cookie, struct mdmalock *__restrict lockvec, size_t lockcnt,
              UNCHECKED void *addr, size_t num_bytes, unsigned int flags)
		THROWS(E_BADALLOC, E_WOULDBLOCK, ...)
#elif defined(DEFINE_mman_startdmav)
PUBLIC BLOCKING_IF(BLOCKING(prange)) NONNULL((1, 2, 4, 6)) size_t KCALL
mman_startdmav(struct mman *__restrict self, mdma_range_callback_t prange,
               void *cookie, struct mdmalock *__restrict lockvec, size_t lockcnt,
               struct iov_buffer const *__restrict addr_v, unsigned int flags)
		THROWS(E_BADALLOC, E_WOULDBLOCK, ...)
#define LOCAL_IS_VECTOR
#elif defined(DEFINE_mman_enumdma)
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
 *              this may be less than that */
PUBLIC BLOCKING_IF(BLOCKING(prange)) NONNULL((1, 2)) size_t KCALL
mman_enumdma(struct mman *__restrict self,
             mdma_range_callback_t prange, void *cookie,
             UNCHECKED void *addr, size_t num_bytes,
             unsigned int flags)
		THROWS(E_BADALLOC, E_WOULDBLOCK, ...)
#define LOCAL_IS_ENUM
#elif defined(DEFINE_mman_enumdmav)
PUBLIC BLOCKING_IF(BLOCKING(prange)) NONNULL((1, 2, 4)) size_t KCALL
mman_enumdmav(struct mman *__restrict self,
              mdma_range_callback_t prange, void *cookie,
              struct iov_buffer const *__restrict addr_v,
              unsigned int flags)
		THROWS(E_BADALLOC, E_WOULDBLOCK, ...)
#define LOCAL_IS_ENUM
#define LOCAL_IS_VECTOR
#else /* ... */
#error "Invalid configuration"
#endif /* !... */
{
#ifdef LOCAL_IS_VECTOR
	struct iov_entry _addrv_ent;
#endif /* LOCAL_IS_VECTOR */
	size_t result = 0;

#ifndef LOCAL_IS_ENUM
	TRY
#endif /* !LOCAL_IS_ENUM */
	{
#ifdef LOCAL_IS_VECTOR
		IOV_BUFFER_FOREACH(_addrv_ent, addr_v)
#define addr      _addrv_ent.ive_base
#define num_bytes _addrv_ent.ive_size
#endif /* LOCAL_IS_VECTOR */
		while (num_bytes != 0) {
			struct mfault mf;
			size_t page_offset, tail_offset, maxsize;
#ifdef LOCAL_IS_ENUM
			struct mdmalock dma_lock;
#endif /* LOCAL_IS_ENUM */
again_lookup_part_reinit:
			__mfault_init(&mf);

			/* Lookup the node at the given address */
again_lookup_part:
			mman_lock_acquire(self);
#ifndef LOCAL_IS_ENUM
again_lookup_part_locked:
#endif /* !LOCAL_IS_ENUM */
			mf.mfl_mman = self;
			mf.mfl_node = mnode_tree_locate(self->mm_mappings, addr);
			if unlikely(!mf.mfl_node)
				goto err_release_and_unmapped; /* No mapping at all */
			mf.mfl_part = mf.mfl_node->mn_part;
			if unlikely(!mf.mfl_part)
				goto err_release_and_unmapped; /* Reserved mapping */
#ifdef LIBVIO_CONFIG_ENABLED
			if unlikely(mf.mfl_part->mp_state == MPART_ST_VIO)
				goto err_release_and_unmapped; /* Cannot use VIO for DMA buffers. */
#endif /* LIBVIO_CONFIG_ENABLED */

			page_offset = (size_t)addr & PAGEMASK;
			mf.mfl_addr = (void *)FLOOR_ALIGN((uintptr_t)addr, PAGESIZE);
			mf.mfl_size = (size_t)((byte_t *)mnode_getendaddr(mf.mfl_node) - (byte_t *)mf.mfl_addr);
			maxsize     = page_offset + num_bytes;
			tail_offset = (PAGESIZE - (maxsize & PAGEMASK)) & PAGEMASK;
			maxsize += tail_offset;
			if (mf.mfl_size > maxsize)
				mf.mfl_size = maxsize;
			mf.mfl_flags = flags;

#ifndef LOCAL_IS_ENUM
			if (result >= lockcnt) {
				if (result == lockcnt)
					mman_stopdma(lockvec, lockcnt); /* Release already acquired locks. */
				mf.mfl_size -= page_offset;
				mf.mfl_size -= tail_offset;
				addr = (byte_t *)addr + mf.mfl_size;
				num_bytes -= mf.mfl_size;
				++result;
				goto again_lookup_part_locked;
			}
#endif /* !LOCAL_IS_ENUM */

			TRY {
				/* Ensure that all blocks that overlap with the given address
				 * range have their  state set  to `MPART_BLOCK_ST_LOAD'  for
				 * reads, and `MPART_BLOCK_ST_CHNG' for writes.
				 *
				 * XXX: It would be cool to have optimization for writes,  such
				 *      that DMA  operations  which  target  whole,  previously
				 *      uninitialized blocks (MPART_BLOCK_ST_NDEF), didn't have
				 *      to load those blocks prior  to the DMA operation  being
				 *      performed.
				 *      For  one, this would require a differentiation between
				 *      a successful and a failed write-related DMA operation.
				 *
				 * For reference: `mpart_write()' uses `mpart_lock_acquire_and_setcore_unsharecow()',
				 *                which doesn't ensure that accessed blocks have been loaded,  whilst
				 *                our use of `mfault_or_unlock()' (rightfully) does do so. */

				/* Fault the accessed address under the relevant access-mode. */
				if (!mfault_or_unlock(&mf))
					goto again_lookup_part;
			} EXCEPT {
				mfault_fini(&mf);
				RETHROW();
			}

			/* No longer need the mman-lock! */
			incref(mf.mfl_part);
			mman_lock_release(mf.mfl_mman);

			/* We're now only holding a lock  to `mf.mfl_part', which has been  unshared
			 * in the context of the backing node from `mf.mfl_mman' (although that node
			 * may have been unmapped since, as we're no longer locking the mman) */

			TRY {
				/* Ensure that `mf.mfl_part->mp_meta' has been allocated */
				if (!mpart_hasmeta_or_unlock(mf.mfl_part, NULL))
					goto again_lookup_part_reinit;
			} EXCEPT {
				decref_unlikely(mf.mfl_part);
				RETHROW();
			}

			/* Adjust the faulted address range to not include the unaligned page-offset
			 * of the actually DMA location. (we had to subtract this originally,  since
			 * mfault_or_unlock() requires that it be given page-aligned addresses) */
			mf.mfl_offs += page_offset;
			mf.mfl_size -= page_offset;
			mf.mfl_size -= tail_offset;

			/* If we're doing a write-DMA, mark the accessed address range as changed. */
			if (flags & MMAN_FAULT_F_WRITE)
				mpart_changed(mf.mfl_part, mf.mfl_offs, mf.mfl_size);

			/* Create the actual DMA-lock. (and release our exclusive lock on the mem-part) */
			mpart_dma_addlock(mf.mfl_part);
			mpart_lock_release(mf.mfl_part);

#ifndef LOCAL_IS_ENUM
			/* Append `mf.mfl_part' to the given list of DMA locks. */
			lockvec[result].mdl_part = mf.mfl_part; /* Inherit reference */
			++result;
#define LOCAL_dma_lock (&lockvec[result - 1])
#else /* !LOCAL_IS_ENUM */
#define LOCAL_dma_lock (&dma_lock)
			dma_lock.mdl_part = mf.mfl_part;
			RAII_FINALLY { mman_dmalock_release(LOCAL_dma_lock); };
#endif /* !LOCAL_IS_ENUM */

			/* Account for everything that will be enumerated. */
			addr = (byte_t *)addr + mf.mfl_size;
			num_bytes -= mf.mfl_size;

			/* Invoke `prange' (through use of `mpart_memaddr_direct()') */
			for (;;) {
				struct mpart_physloc pl;
				bool ok;
				mpart_memaddr_direct(mf.mfl_part, mf.mfl_offs, &pl);
				if (pl.mppl_size > mf.mfl_size)
					pl.mppl_size = mf.mfl_size;
#ifdef LOCAL_IS_ENUM
				ok = (*prange)(cookie, pl.mppl_addr, pl.mppl_size, LOCAL_dma_lock);
#else /* LOCAL_IS_ENUM */
				ok = (*prange)(cookie, pl.mppl_addr, pl.mppl_size, LOCAL_dma_lock);
#endif /* !LOCAL_IS_ENUM */
				if (!ok) {
#ifdef LOCAL_IS_ENUM
					decref_unlikely(mf.mfl_part);
#endif /* LOCAL_IS_ENUM */
					goto err_unmapped;
				}
#ifdef LOCAL_IS_ENUM
				result += pl.mppl_size;
#endif /* LOCAL_IS_ENUM */
				if (pl.mppl_size >= mf.mfl_size)
					break;
				mf.mfl_offs += pl.mppl_size;
				mf.mfl_size -= pl.mppl_size;
			}
#undef LOCAL_dma_lock
		}
	}
#ifndef LOCAL_IS_ENUM
	EXCEPT {
		if (result <= lockcnt)
			mman_stopdma(lockvec, result);
		RETHROW();
	}
#endif /* !LOCAL_IS_ENUM */
#undef addr
#undef num_bytes
	return result;
err_release_and_unmapped:
	mman_lock_release(self);
err_unmapped:
#ifndef LOCAL_IS_ENUM
	if (result <= lockcnt)
		mman_stopdma(lockvec, result);
#endif /* !LOCAL_IS_ENUM */
	return 0;
}

#undef LOCAL_IS_VECTOR
#undef LOCAL_IS_ENUM

DECL_END

#undef DEFINE_mman_startdma
#undef DEFINE_mman_startdmav
#undef DEFINE_mman_enumdma
#undef DEFINE_mman_enumdmav
