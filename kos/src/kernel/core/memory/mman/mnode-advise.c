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
#ifndef GUARD_KERNEL_SRC_MEMORY_MMAN_MNODE_ADVISE_C
#define GUARD_KERNEL_SRC_MEMORY_MMAN_MNODE_ADVISE_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/mman.h>
#include <kernel/mman/mnode.h>
#include <kernel/mman/mpart.h>
#include <sched/rpc.h>

#include <kos/except.h>
#include <kos/except/reason/inval.h>
#include <sys/mman.h>

#include <assert.h>
#include <atomic.h>

DECL_BEGIN

/* Apply a given `advise' to `self' and return `true', or release a
 * lock to `self->mn_mman' and return `false' (in which case `data'
 * may have been modified)
 * @param: advice: The advice to apply (one of `MADV_*', except `MADV_POPULATE_*')
 * @return: true:  Success (locks are still held)
 * @return: false: Error (locks were released)
 * @THROW: Error (locks were released) */
PUBLIC BLOCKING WUNUSED NONNULL((1, 2)) bool FCALL
mnode_advise_or_unlock(struct mnode *__restrict self,
                       struct mpart_trim_data *__restrict data,
                       unsigned int advice)
		THROWS(E_BADALLOC) {
#define LOCAL_unlock_all() mpart_trim_data_unlock(data)

	assert(self->mn_mman);
	assert(!(self->mn_flags & MNODE_F_UNMAPPED));
	assert(!wasdestroyed(self->mn_mman));
	assert(mman_lock_acquired(self->mn_mman));
	assert(data->mtd_mmlocked == self->mn_mman);

	switch (advice) {

	case MADV_NORMAL:
	case MADV_RANDOM:
	case MADV_SEQUENTIAL:
	case MADV_WILLNEED:
		/* These advices we simply ignore (for now) */
		break;

	case MADV_DONTNEED:
		data->mtd_mode = MPART_TRIM_MODE_UNCHANGED;
do_mpart_trim:
		if (self->mn_part) {

			/* Only trim the sub-area that is actually mapped by the node. */
			data->mtd_rstart = mnode_getpartminaddr(self);
			data->mtd_rend   = mnode_getpartendaddr(self);

			/* Note that we tell `mpart_trim_or_unlock()' about the fact
			 * that  we holding a  lock to the mman,  and that it should
			 * release that lock on error! */
			if (!mpart_trim_or_unlock(self->mn_part, data))
				return false; /* Try again... */
		}
		break;

	case MADV_FREE:
		data->mtd_mode = MPART_TRIM_MODE_UNCHANGED |
		                 MPART_TRIM_FLAG_FREE;
		goto do_mpart_trim;

	case MADV_PAGEOUT:
		data->mtd_mode = MPART_TRIM_MODE_UNCHANGED |
		                 MPART_TRIM_FLAG_SYNC |
		                 MPART_TRIM_FLAG_SWAP;
		goto do_mpart_trim;

	/*case MADV_REMOVE:*/ /* Unsupported... */

	/*case MADV_DOFORK:*/     /* TODO: Support me! (keep node during fork) */
	/*case MADV_DONTFORK:*/   /* TODO: Support me! (remove node during fork) */
	/*case MADV_WIPEONFORK:*/ /* TODO: Support me! (replace with anon memory during fork) */
	/*case MADV_KEEPONFORK:*/ /* TODO: Support me! (retain original mapping during fork) */

	case MADV_MERGEABLE:
	case MADV_UNMERGEABLE:
		/* Implemented as no-ops (for now)
		 *
		 * The idea here would be to  replace nodes of anonymous memory  mappings
		 * where the contents of the underlying physical pages are identical such
		 * that they map to the same mpart, as though the 2 mappings were made as
		 * a result a fork() (meaning they get unshared again when writing to one
		 * or the other)
		 *
		 * When  an mnode is write-faulted while it  has this flag, it gets added
		 * to a list of nodes that should be scanned for merging with other nodes
		 * that also have this flag. The scan then removes write access from  all
		 * nodes in the list (whilst also acquiring locks to all of those  nodes'
		 * mmans  and the  underlying parts),  and searches  for duplicates. When
		 * finished,  those nodes are *not* added back  to the list of nodes that
		 * need to be scanned (though  they will be added back  to it as soon  as
		 * such  a node is write-faulted again (no matter if COW needs to be done
		 * during the fault or not)) */
		break;

	case MADV_HUGEPAGE:
	case MADV_NOHUGEPAGE:
		/* Implemented as no-ops (probably forever) */
		break;

	case MADV_DONTDUMP:
		atomic_or(&self->mn_flags, MNODE_F_NOCORE);
		break;

	case MADV_DODUMP:
		atomic_and(&self->mn_flags, ~MNODE_F_NOCORE);
		break;

	case MADV_COLD:
		/* TODO: Indicate that the associated mem-part should be one
		 *       of the first parts  to be trimmed by  `system_cc()' */
		break;

	case MADV_HWPOISON:
	case MADV_SOFT_OFFLINE:
		/* Implemented as no-ops (probably forever) */
		break;

	default:
		break;
	}

	return true;
#undef LOCAL_unlock_all
}


DECL_END

#endif /* !GUARD_KERNEL_SRC_MEMORY_MMAN_MNODE_ADVISE_C */
