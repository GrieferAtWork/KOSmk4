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
#ifndef GUARD_KERNEL_SRC_MEMORY_MMAN_DMA_C
#define GUARD_KERNEL_SRC_MEMORY_MMAN_DMA_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/iovec.h>
#include <kernel/malloc.h>
#include <kernel/mman.h>
#include <kernel/mman/dma.h>
#include <kernel/mman/fault.h>
#include <kernel/mman/mnode.h>
#include <kernel/mman/mpart.h>
#include <sched/task.h>

#include <hybrid/align.h>

#include <kos/except.h>

#include <assert.h>
#include <stdbool.h>
#include <string.h>

#include <libvio/api.h>

DECL_BEGIN

#if !defined(NDEBUG) && !defined(NDEBUG_FINI)
#define DBG_memset memset
#else /* !NDEBUG && !NDEBUG_FINI */
#define DBG_memset(...) (void)0
#endif /* NDEBUG || NDEBUG_FINI */

/* Start DMAing on  memory within the  specified address  range.
 * This function is used to lock physical memory for the purpose
 * of use with `mfile_direct_[read|write]()'.
 *
 * @param: prange:    A callback that is invoked for each affected physical memory range
 *                    When this callback returns a negative value, stop enumeration  and
 *                    propagate said return value.
 * @param: cookie:    Cookie-argument passed to `prange' upon execution.
 * @param: addr:      The base address where locking should start.
 * @param: num_bytes: The number of continuous bytes that should be locked.
 * @param: flags:     Set of `0 | MMAN_FAULT_F_WRITE'. When `MMAN_FAULT_F_WRITE' is given, unshare
 *                    copy-on-write  mappings of  associated memory,  allowing the  caller to then
 *                    write  to the acquired memory ranges without accidentally having any changes
 *                    made appear in PRIVATE mappings of the associated memory region.
 * @return: >= :      Sum of positive return values of `*prange'
 * @return: < 0:      Enumeration was stopped because `*prange' return this negative value.
 *
 * Exceptions thrown by this function:
 * WARNING: *prange may have already been invoked when this happens!
 * @throw: E_WOULDBLOCK:        ...
 * @throw: E_BADALLOC:          ...
 * @throw: E_SEGFAULT_UNMAPPED: An address was reached that isn't mapped or is reserved
 * @throw: E_SEGFAULT_UNMAPPED: Hit a VIO mapping (which can't be DMA'd) (context includes `E_SEGFAULT_CONTEXT_VIO')
 * @throw: E_SEGFAULT_READONLY: `MMAN_FAULT_F_WRITE' was given and an address is mapped without PROT_WRITE
 *                              WARNING: *prange may have already been invoked
 * @throw: E_FSERROR_READONLY:  Attempted to fault write-access for a SHARED mapping of a MFILE_F_READONLY file. */
PUBLIC BLOCKING NONNULL((1)) ssize_t KCALL
mman_dma(mdma_range_callback_t prange, void *cookie,
         UNCHECKED void *addr, size_t num_bytes, unsigned int flags)
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, E_FSERROR_READONLY, ...) {
	ssize_t result = 0;
	while (num_bytes) {
		struct mfault mf;
		size_t head_offset;
		size_t tail_offset;

		/* Initialize fault controller. */
again_init_mf:
		__mfault_init(&mf);
		mf.mfl_flags = flags;
		mf.mfl_mman  = THIS_MMAN;
		if (ADDR_ISKERN(addr))
			mf.mfl_mman = &mman_kernel;

		TRY {
			size_t max_io;
again_lock_mman:
			mman_lock_read(mf.mfl_mman);

			/* Lookup mem-node that should be faulted. */
			if unlikely((mf.mfl_node = mnode_tree_locate(mf.mfl_mman->mm_mappings, addr)) == NULL ||
			            (mf.mfl_part = mf.mfl_node->mn_part) == NULL) {
				mman_lock_endread(mf.mfl_mman);
				THROW(E_SEGFAULT_UNMAPPED, addr,
				      ((flags & MMAN_FAULT_F_WRITE) ? E_SEGFAULT_CONTEXT_WRITING : 0) |
				      ((mf.mfl_node != NULL) ? 0 : E_SEGFAULT_CONTEXT_FAULT));
			}

			/* DMA doesn't work for VIO */
#ifdef LIBVIO_CONFIG_ENABLED
			if unlikely(mf.mfl_part->mp_state == MPART_ST_VIO) {
				mman_lock_endread(mf.mfl_mman);
				THROW(E_SEGFAULT_UNMAPPED, addr,
				      ((flags & MMAN_FAULT_F_WRITE) ? E_SEGFAULT_CONTEXT_WRITING : 0) |
				      (E_SEGFAULT_CONTEXT_VIO));
			}
#endif /* LIBVIO_CONFIG_ENABLED */

			/* Fill in the fault range. */
			head_offset = (uintptr_t)addr & PAGEMASK;
			mf.mfl_addr = (PAGEDIR_PAGEALIGNED void *)((uintptr_t)addr - head_offset);
			mf.mfl_size = (byte_t *)mnode_getendaddr(mf.mfl_node) - (byte_t *)mf.mfl_addr;
			max_io      = head_offset + num_bytes;
			tail_offset = CEIL_ALIGN(max_io, PAGESIZE) - max_io;
			max_io += tail_offset;
			if (mf.mfl_size > max_io)
				mf.mfl_size = max_io;

			/* Lock the associated mem-part. */
			if (!mfault_lockpart_or_unlock(&mf))
				goto again_lock_mman;

			/* Fault memory for the access we need to do. */
			if (!mfault_or_unlock(&mf))
				goto again_lock_mman;
		} EXCEPT {
			mfault_fini(&mf);
			RETHROW();
		}

		/* No longer need the mman-lock! */
		incref(mf.mfl_part);
		mman_lock_endread(mf.mfl_mman);

		/* Ensure that the mem-part had its meta-data controller allocated. */
		TRY {
			if (!mpart_hasmeta_or_unlock(mf.mfl_part, NULL)) {
				decref_unlikely(mf.mfl_part);
				goto again_init_mf;
			}
		} EXCEPT {
			decref_unlikely(mf.mfl_part);
			RETHROW();
		}

		/* Adjust the faulted address range to not include the unaligned page-offset
		 * of the actually DMA location. (we had to subtract this originally,  since
		 * mfault_or_unlock() requires that it be given page-aligned addresses) */
		mf.mfl_offs += head_offset;
		mf.mfl_size -= head_offset;
		mf.mfl_size -= tail_offset;

		/* Create the initial DMA-lock. (and release our exclusive lock on the mem-part) */
		mpart_dma_addlock(mf.mfl_part);
		mpart_lock_release(mf.mfl_part);

		/* Update positions for the next iteration. */
		assert(num_bytes >= mf.mfl_size);
		addr = (UNCHECKED void *)((UNCHECKED byte_t *)addr + mf.mfl_size);
		num_bytes -= mf.mfl_size;

		/* Iterate through physical memory of the affected address range. */
		for (;;) {
			ssize_t temp;
			struct mpart_physloc pl;
			mpart_memaddr_direct(mf.mfl_part, mf.mfl_offs, &pl);
			if (pl.mppl_size >= mf.mfl_size) {
				/* Last range that needs to be enumerated. */
				pl.mppl_size = mf.mfl_size;

				/* NOTE: This call right here _always_ inherits a DMA lock, as well as a reference! */
				temp = (*prange)(cookie, pl.mppl_addr, pl.mppl_size, mf.mfl_part);
				if unlikely(temp < 0)
					return temp;
				result += temp;
				break;
			}

			/* Non-continuous memory
			 * -> We'll be needing additional DMA locks for later passes. */
			incref(mf.mfl_part);
			mpart_dma_addlock(mf.mfl_part);
			TRY {
				/* NOTE: This call right here _always_ inherits a DMA lock, as well as a reference! */
				temp = (*prange)(cookie, pl.mppl_addr, pl.mppl_size, mf.mfl_part);
			} EXCEPT {
				mf.mfl_part = mpart_dma_dellock(mf.mfl_part);
				decref(mf.mfl_part);
				RETHROW();
			}
			if unlikely(temp < 0) {
				mf.mfl_part = mpart_dma_dellock(mf.mfl_part);
				decref(mf.mfl_part);
				return temp;
			}
			result += temp;
		}
	}
	return result;
}


/* Simple wrapper for `mman_dma()' that just consecutively
 * invokes said function for all of the given iov  ranges. */
PUBLIC BLOCKING NONNULL((1, 3)) ssize_t KCALL
mman_dmav(mdma_range_callback_t prange, void *cookie,
          struct iov_buffer const *__restrict buffer, size_t buf_offset,
          size_t num_bytes, unsigned int flags)
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, E_FSERROR_READONLY, ...) {
	struct iov_entry ent;
	ssize_t temp, result = 0;
	IOV_BUFFER_FOREACH(ent, buffer) {
		if (buf_offset) {
			if (buf_offset >= ent.ive_size) {
				buf_offset -= ent.ive_size;
				continue;
			}
			ent.ive_base += buf_offset;
			ent.ive_size -= buf_offset;
			buf_offset = 0;
		}
		if (ent.ive_size > num_bytes)
			ent.ive_size = num_bytes;
		temp = mman_dma(prange, cookie, ent.ive_base, ent.ive_size, flags);
		if unlikely(temp < 0)
			return temp;
		result += temp;
		if (ent.ive_size >= num_bytes)
			break;
	}
	return result;
}


/* Callback for `struct refcountable_dmalock::rca_destroy' */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL refcountable_dmalock_destroy)(struct refcountable *__restrict self) {
	struct refcountable_dmalock *me;
	me = (struct refcountable_dmalock *)self;
	mdma_lock_release(me->rld_lock);
	xdecref(me->rld_misc); /* This right here allows for chaining of AIO cleanup operations! */
	kfree(me);
}

/* A function that may be called as-is from `mdma_range_callback_t' in order
 * to convert  a  DMA-lock  to `lock'  into  a  refcnt-controlled  DMA-lock. */
PUBLIC ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct refcountable_dmalock *FCALL
refcountable_dmalock_new(/*inherit(always)*/ mdma_lock_t lock, struct refcountable *misc)
		THROWS(E_BADALLOC) {
	REF struct refcountable_dmalock *result;
	TRY {
		result = (REF struct refcountable_dmalock *)kmalloc(sizeof(struct refcountable_dmalock),
		                                                    GFP_NORMAL);
	} EXCEPT {
		/* Must _always_ inherit the given lock (even on EXCEPT) */
		mdma_lock_release(lock);
		RETHROW();
	}

	/* Fill in the refcountable DMA-lock descriptor. */
	result->rca_refcnt  = 1;
	result->rca_destroy = &refcountable_dmalock_destroy;
	result->rld_lock    = lock;          /* Inherit */
	result->rld_misc    = xincref(misc); /* Chain support */
	return result;
}


DECL_END

#endif /* !GUARD_KERNEL_SRC_MEMORY_MMAN_DMA_C */
