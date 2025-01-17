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
#ifndef GUARD_KERNEL_SRC_MEMORY_MMAN_MMAN_MSYNC_C
#define GUARD_KERNEL_SRC_MEMORY_MMAN_MMAN_MSYNC_C 1

#include <kernel/compiler.h>

#include <kernel/mman.h>
#include <kernel/mman/mnode.h>
#include <kernel/mman/mpart.h>
#include <kernel/mman/msync.h>

#include <hybrid/overflow.h>

#include <kos/except.h>
#include <kos/except/reason/inval.h>

#include <atomic.h>
#include <stddef.h>

DECL_BEGIN

/* Sync  the backing mem-parts  of all MNODE_F_SHARED nodes
 * within the given address range. Note that this operation
 * is done distinct steps, meaning that some writes done by
 * a different process prior to this function returning may
 * get synced, whilst other  writes that might even  happen
 * after a prior write that  did end up being synced  don't
 * end up synced.
 *
 * Additionally,  if this function fails (by throwing an
 * exception), it is still possible that some writes may
 * have gotten synced while others weren't.
 *
 * However, anything written by the calling thread within
 * the given  range before  this  function is  called  is
 * guarantied to end up synced upon success.
 *
 * @param: flags: Set of `MS_*' (see above)
 * @throws: *:E_INVALID_ARGUMENT_CONTEXT_MSYNC_SIZE: [...]
 * @throws: E_SEGFAULT_UNMAPPED: When `MS_IFMAPPED' isn't given, this exception is
 *                               thrown for the first  address of the given  range
 *                               that isn't mapped. */
PUBLIC BLOCKING NONNULL((1)) void FCALL
mman_msync(struct mman *__restrict self, void *addr,
           size_t num_bytes, unsigned int flags)
		THROWS(E_INVALID_ARGUMENT_BAD_VALUE, E_SEGFAULT_UNMAPPED, ...) {
	byte_t *minaddr, *maxaddr;
	minaddr = (byte_t *)addr;
	if unlikely(OVERFLOW_UADD((uintptr_t)minaddr, num_bytes - 1,
	                          (uintptr_t *)&maxaddr)) {
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_MSYNC_SIZE,
		      num_bytes);
	}

	/* Go over the given address range in its entirety. */
	mman_lock_acquire(self);
	while (minaddr < maxaddr) {
		struct mpart *part;
		struct mnode_tree_minmax mima;
		mman_mappings_minmaxlocate(self, minaddr, maxaddr, &mima);
		if (!mima.mm_min) {
			mman_lock_release(self);
			if (!(flags & MS_IFMAPPED))
				THROW(E_SEGFAULT_UNMAPPED, minaddr, E_SEGFAULT_CONTEXT_FAULT);
			break;
		}
		if unlikely(!(flags & MS_IFMAPPED) &&
		            (minaddr < (byte_t *)mnode_getminaddr(mima.mm_min))) {
			/* The address space contains a gap before this mapping! */
			mman_lock_release(self);
			THROW(E_SEGFAULT_UNMAPPED, minaddr, E_SEGFAULT_CONTEXT_FAULT);
		}

		/* Once we're done with this node, continue syncing past it. */
		minaddr = (byte_t *)mnode_getendaddr(mima.mm_min);

		/* Sync all SHARED nodes bound to non-anonymous mem-parts. */
		if ((mima.mm_min->mn_flags & MNODE_F_SHARED) &&              /* Must be a SHARED mapping! */
		    (part = mima.mm_min->mn_part) != NULL &&                 /* Node needs to be bound to a part */
		    (atomic_read(&part->mp_flags) & MPART_F_CHANGED) != 0 && /* Part must have been changed */
		    !mpart_isanon(part)) {                                   /* Part mustn't be anonymous */
			/* Yes: _do_ sync this part! */
			incref(part);
			mman_lock_release(self);
			{
				FINALLY_DECREF_UNLIKELY(part);
				/*TODO:MS_ASYNC -> mpart_start_asyncjob(part, MPART_XF_WILLSYNC);*/
				mpart_sync(part);
			}
			mman_lock_acquire(self);
		}
	}
	mman_lock_release(self);
}


DECL_END

#endif /* !GUARD_KERNEL_SRC_MEMORY_MMAN_MMAN_MSYNC_C */
