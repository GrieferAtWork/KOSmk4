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
#ifndef GUARD_KERNEL_SRC_MEMORY_MMAN_MPART_MERGE_C
#define GUARD_KERNEL_SRC_MEMORY_MMAN_MPART_MERGE_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/mman.h>
#include <kernel/mman/mfile.h>
#include <kernel/mman/mpart.h>

DECL_BEGIN

/* Try to merge the given part with other, neighboring parts from
 * its associated file, or, in case that file is anonymous, try to
 * merge the part with parts from nodes of neighboring mappings
 * within the associated mman-s, so-long as those neighboring parts
 * make use of the same underlying (anonymous) file. */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mpart_merge)(struct mpart *__restrict self) {
	struct mfile *file;
	incref(self);
again:
	if (!mpart_lock_tryacquire(self))
		goto done;
	file = self->mp_file;
	if (mfile_isanon(file)) {
do_merge_anon:
		/* Try to merge anonymous parts by looking at the nodes mapping it. */
		if (LIST_EMPTY(&self->mp_copy) && LIST_EMPTY(&self->mp_share)) {
			/* Nothing is mapping our part, so we've go no frame of reference... */
			goto done_unlock;
		}

		/* TODO: Try to merge with the parts of neighboring
		 *       nodes from copy- and/or share-mappings. */
		goto done_unlock;
	}
	
	if (mfile_lock_trywrite(file)) {
		struct mpart *next;
		if unlikely(mfile_isanon(file)) {
			mfile_lock_endwrite(file);
			goto do_merge_anon;
		}
		/* Check for a neighboring, preceding part. */
		next = mpart_tree_prevnode(self);
		if (next && next->mp_maxaddr == self->mp_minaddr - 1) {
			/* Try to merge the prev node with `self' */
			if (tryincref(next)) {
				mfile_lock_endwrite(file);
				mpart_lock_release(self);
				decref_unlikely(self);
				self = next; /* Inherit reference */
				goto again;
			}
		}
		/* Check for a neighboring successor-part. */
		next = mpart_tree_nextnode(self);
		if (!next || self->mp_maxaddr + 1 != next->mp_minaddr || !tryincref(next)) {
done_unlock_endwrite_file:
			mfile_lock_endwrite(file);
			goto done_unlock;
		}
		if (!mpart_lock_tryacquire(next)) {
			decref_unlikely(next);
			goto done_unlock_endwrite_file;
		}

		/* TODO: Try to merge `self' with `next' */

		mpart_lock_release(next);
		decref_unlikely(next);
		mfile_lock_endwrite(file);
	}
done_unlock:
	mpart_lock_release(self);
done:
	decref_unlikely(self);
}

DECL_END

#endif /* !GUARD_KERNEL_SRC_MEMORY_MMAN_MPART_MERGE_C */
