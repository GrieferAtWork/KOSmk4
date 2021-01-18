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
#include "mm-dma.c"
//#define DEFINE_mman_startdma
#define DEFINE_mman_startdmav
//#define DEFINE_mman_enumdma
//#define DEFINE_mman_enumdmav
#endif /* __INTELLISENSE__ */

#include <kernel/iovec.h>
#include <kernel/mman/mnode.h>
#include <kernel/mman/mpart.h>
#include <sched/task.h>

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
 *                      Should this callback return `false', all previously acquired DMA
 *                      locks are released, and `mman_startdma[v]()' returns `0'
 * @param: cookie:      Cookie-argument passed to `prange' upon execution.
 * @param: lockvec:     Vector of DMA lock slots provided by the caller.
 * @param: lockcnt:     Number of available DMA lock slots (allocated length (not size) of `lockvec')
 * @param: addr:        [mman_startdma] The base address where locking should start.
 * @param: num_bytes:   [mman_startdma] The number of continuous bytes that should be locked.
 * @param: addr_v:      [mman_startdmav] The scatter-gather list of virtual memory ranges to lock.
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
PUBLIC NONNULL((1, 2, 4)) size_t KCALL
mman_startdma(struct mman *__restrict self, mdma_range_callback_t prange,
              void *cookie, struct mdmalock *__restrict lockvec, size_t lockcnt,
              UNCHECKED void *addr, size_t num_bytes, __BOOL for_writing)
		THROWS(E_WOULDBLOCK, E_BADALLOC, ...)
#elif defined(DEFINE_mman_startdmav)
PUBLIC NONNULL((1, 2, 4, 6)) size_t KCALL
mman_startdmav(struct mman *__restrict self, mdma_range_callback_t prange,
               void *cookie, struct mdmalock *__restrict lockvec, size_t lockcnt,
               struct aio_buffer const *__restrict addr_v, __BOOL for_writing)
		THROWS(E_WOULDBLOCK, E_BADALLOC, ...)
#define LOCAL_IS_VECTOR
#elif defined(DEFINE_mman_enumdma)
/* Similar to `mman_startdma[v]', however instead used to enumerate the DMA memory range individually.
 * @param: prange:      A callback that is invoked for each affected physical memory range
 *                      Should this callback return `false', enumeration will halt and the
 *                      function will return the number of previously successfully enumerated
 *                      DMA bytes.
 * @param: cookie:      Cookie-argument passed to `prange' upon execution.
 * @param: addr:        [mman_startdma] The base address where locking should start.
 * @param: num_bytes:   [mman_startdma] The number of continuous bytes that should be locked.
 * @param: addr_v:      [mman_startdmav] The scatter-gather list of virtual memory ranges to lock.
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
             mdma_range_callback_t prange, void *cookie,
             UNCHECKED void *addr, size_t num_bytes,
             bool for_writing)
		THROWS(E_WOULDBLOCK, E_BADALLOC, ...)
#define LOCAL_IS_ENUM
#elif defined(DEFINE_mman_enumdmav)
PUBLIC NONNULL((1, 2, 4)) size_t KCALL
mman_enumdmav(struct mman *__restrict self,
              mdma_range_callback_t prange, void *cookie,
              struct aio_buffer const *__restrict addr_v,
              bool for_writing)
		THROWS(E_WOULDBLOCK, E_BADALLOC, ...)
#define LOCAL_IS_ENUM
#define LOCAL_IS_VECTOR
#else /* ... */
#error "Invalid configuration"
#endif /* !... */
{
#ifdef LOCAL_IS_VECTOR
	struct aio_buffer_entry _addrv_ent;
#endif /* LOCAL_IS_VECTOR */
	size_t result = 0;

#ifdef LOCAL_IS_VECTOR
	AIO_BUFFER_FOREACH(_addrv_ent, addr_v)
#define addr      _addrv_ent.ab_base
#define num_bytes _addrv_ent.ab_size
#endif /* LOCAL_IS_VECTOR */
	while (num_bytes != 0) {
		struct mnode *node;
		struct mpart *part;
		mpart_reladdr_t partrel_addr;
		size_t partrel_size;

		/* Lookup the node at the given address */
again_lookup_part:
		mman_lock_acquire(self);
#ifndef LOCAL_IS_ENUM
again_lookup_part_locked:
#endif /* !LOCAL_IS_ENUM */
		node = mnode_tree_locate(self->mm_mappings, addr);
		if unlikely(!node)
			goto err_release_and_unmapped; /* No mapping at all */
		part = node->mn_part;
		if unlikely(!part)
			goto err_release_and_unmapped; /* Reserved mapping */

		/* Figure out the part-relative address range that is being enumerated. */
		partrel_addr = node->mn_partoff + (size_t)((byte_t const *)addr - (byte_t const *)mnode_getaddr(node));
		partrel_size = (size_t)((byte_t const *)mnode_getendaddr(node) - (byte_t const *)addr);
		if (partrel_size > num_bytes)
			partrel_size = num_bytes;

#ifndef LOCAL_IS_ENUM
		if (result >= lockcnt) {
			if (result == lockcnt)
				mman_stopdma(lockvec, lockcnt); /* Release already acquired locks. */
			addr = (byte_t *)addr + partrel_size;
			num_bytes -= partrel_size;
			++result;
			goto again_lookup_part_locked;
		}
#endif /* !LOCAL_IS_ENUM */

		/* Keep a reference to the part so we can unlock the mman. */
		incref(part);
		mman_lock_release(self);
		TRY {
			size_t enum_size;
#ifdef LOCAL_IS_ENUM
			struct mdmalock dma_lock;
#endif /* LOCAL_IS_ENUM */

			/* Ensure that all blocks that overlap with the given address
			 * range have their state set to `MPART_BLOCK_ST_LOAD' for
			 * reads, and `MPART_BLOCK_ST_CHNG' for writes.
			 *
			 * XXX: If would be cool to have optimization for writes, such that
			 *      DMA operations which target whole, previously uninitialized
			 *      blocks (MPART_BLOCK_ST_NDEF), didn't have to load those
			 *      blocks prior to the DMA operation being performed.
			 *      For one, this would require a differentiation between a
			 *      successful and a failed write-related DMA operation.
			 *      The problem with this is that this would also require
			 *      the extension of `struct mdmalock', but that would then
			 *      require a re-write of `AtaAIOHandleData' or an increase
			 *      of `AIO_HANDLE_DRIVER_POINTER_COUNT'... */
again_lock_part:
			if (for_writing ? !mpart_lock_acquire_and_setcore_unsharecow_loadsome(part, partrel_addr, partrel_size)
			                : !mpart_lock_acquire_and_setcore_loadsome(part, partrel_addr, partrel_size)) {
				/* Deal with the case where the part was truncated. */
				decref_unlikely(part);
				goto again_lookup_part;
			}

			/* Ensure that `part->mp_meta' has been allocated */
			if (!mpart_hasmeta_or_unlock(part, NULL))
				goto again_lock_part;

			/* If we're doing a write-DMA, mark the accessed address range as changed. */
			if (for_writing)
				mpart_changed(part, partrel_addr, partrel_size);

			/* Create the actual DMA-lock. */
			mpart_dma_addlock(part);
			mpart_lock_release(part);

#ifndef LOCAL_IS_ENUM
			/* Append `part' to the given list of DMA locks. */
			lockvec[result].mdl_part = part; /* Inherit reference */
			++result;
#define LOCAL_dma_lock (&lockvec[result - 1])
#else /* !LOCAL_IS_ENUM */
			dma_lock.mdl_part = part;
#define LOCAL_dma_lock (&dma_lock)
#endif /* !LOCAL_IS_ENUM */

			/* Invoke `prange' (through use of `mpart_memaddr_direct()') */
			enum_size = partrel_size;
			for (;;) {
				struct mpart_physloc pl;
				bool ok;
				mpart_memaddr_direct(part, partrel_addr, &pl);
				if (pl.mppl_size > enum_size)
					pl.mppl_size = enum_size;
				ok = (*prange)(cookie, pl.mppl_addr, pl.mppl_size, LOCAL_dma_lock);
				if (!ok) {
#ifdef LOCAL_IS_ENUM
					decref_unlikely(part);
#endif /* LOCAL_IS_ENUM */
					goto err_unmapped;
				}
#ifdef LOCAL_IS_ENUM
				result += pl.mppl_size;
#endif /* LOCAL_IS_ENUM */
				if (pl.mppl_size >= enum_size)
					break;
				partrel_addr += pl.mppl_size;
				enum_size -= pl.mppl_size;
			}

#undef LOCAL_dma_lock
		} EXCEPT {
			decref_unlikely(part);
			RETHROW();
		}
#ifdef LOCAL_IS_ENUM
		decref_unlikely(part);
#endif /* LOCAL_IS_ENUM */

		/* Account for everything that was enumerated. */
		addr = (byte_t *)addr + partrel_size;
		num_bytes -= partrel_size;
		mman_lock_acquire(self);
	}
#undef addr
#undef num_bytes
	mman_lock_release(self);
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
