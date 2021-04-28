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
#ifndef GUARD_KERNEL_SRC_MEMORY_MMAN_MPART_TRIM_C
#define GUARD_KERNEL_SRC_MEMORY_MMAN_MPART_TRIM_C 1

#include <kernel/compiler.h>

#include <kernel/mman/mnode.h>
#include <kernel/mman/mpart.h>

#include <hybrid/atomic.h>

DECL_BEGIN

/* Alongside mpart_merge(), there should also be a function `mpart_trim()'
 * that will look at what's actually being mapped about the part, and will
 * try to trim/split the part, such  that unmapped portions are no  longer
 * being represented.
 *
 * Without special handling, the following will actually keep backing memory allocated:
 *
 * >> mmap(0x01234000, PAGESIZE, PROT_READ | PROT_WRITE, MAP_FIXED | MAP_ANON, -1, 0);
 * >> mmap(0x01235000, PAGESIZE, PROT_READ | PROT_WRITE, MAP_FIXED | MAP_ANON, -1, 0); // Automatically merged
 * >> mmap(0x01236000, PAGESIZE, PROT_READ | PROT_WRITE, MAP_FIXED | MAP_ANON, -1, 0); // Automatically merged
 * >> munmap(0x01235000, PAGESIZE); // Automatically cases a split, but only within mem-nodes (mpart is unaffected)
 *
 * The idea here is that  the munmap() calls `mpart_trim()', which  will
 * (asynchronously, and only in case the part is anonymous) look at  the
 * part's set of mapped nodes and figure out which parts of the part (if
 * any)  are actually in use. Any part that's not in use from the part's
 * edges  is then simply  trimmed, and unused holes  from the middle are
 * handled by trying to split the part, such that each consecutive chunk
 * of used memory has its own mpart, and thus doesn't require the entire
 * region to be kept in-core all at once. */




/* If `self' is an anonymous mem-part, asynchronously acquire a
 * lock to `self' and compare the min/max-addr bounds of `self'
 * against the portions that are actually mapped by  mem-nodes.
 * If it is found that leading/trailing portions of `self'  are
 * not mapped by  any mem-node, trim  those parts from  `self'.
 * If there are holes within `self' of pages not mapped by  any
 * mem-nodes,  asynchronously split `self', and update nodes in
 * order to get rid of the relevant ranges.
 * This function should  be called  whenever mem-node  mappings
 * of `self' have been removed, in order to drop the references
 * that were originally held by those nodes.
 * NOTE: When `self' isn't anonymous, simply `decref(self)'!
 * NOTE: This function usually doesn't need to be called directly.
 *       Instead, it is  called from  `mnode_destroy()' to  decref
 *       the associated part after the node has been removed  from
 *       the list of node-mappings of `self' */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mpart_trim)(/*inherit(always)*/ REF struct mpart *__restrict self) {
	/* Check for special case: can we destroy the part immediately! */
	if (ATOMIC_CMPXCH(self->mp_refcnt, 1, 0))
		goto do_destroy;
	/* Check for special case: the part isn't anonymous. */
	if (!mpart_isanon(self)) {
do_normal_decref:
		decref_unlikely(self);
		return;
	}
	if (mpart_lock_tryacquire(self)) {
		if unlikely(!mpart_isanon(self)) {
			mpart_lock_release(self);
			goto do_normal_decref;
		}
		/* TODO: Do the actual trimming! */
		mpart_lock_release(self);
	} else {
		/* TODO: Async lockop! */
	}
	decref_unlikely(self);
	return;
do_destroy:
	mpart_destroy(self);
}


DECL_END

#endif /* !GUARD_KERNEL_SRC_MEMORY_MMAN_MPART_TRIM_C */
