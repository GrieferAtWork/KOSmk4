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
#ifndef GUARD_KERNEL_SRC_MEMORY_MBUILDER_LOCK_C
#define GUARD_KERNEL_SRC_MEMORY_MBUILDER_LOCK_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/malloc.h>
#include <kernel/mman/mbuilder.h>
#include <kernel/mman/mfile.h>
#include <kernel/mman/mnode.h>
#include <kernel/mman/mpart.h>
#include <misc/unlockinfo.h>
#include <sched/task.h>

#include <assert.h>
#include <stdbool.h>
#include <string.h>

DECL_BEGIN

/* Acquire a lock to every unique mem-part mapped by `self'.
 * If this fails for at least one of the parts, unlock all
 * parts already locked at that point, invoke `unlock' if
 * given, wait until the blocking part becomes available,
 * and return `false'
 * Otherwise, return `true' */
PRIVATE NONNULL((1)) bool FCALL
mbuilder_lock_all_mparts(struct mbuilder *__restrict self,
                         struct unlockinfo *unlock) {
	struct mbnode *iter;
	SLIST_FOREACH (iter, &self->mb_uparts, mbn_nxtuprt) {
		struct mpart *part = iter->mbn_part;
		if (mpart_lock_tryacquire(part))
			continue;
		/* We've got a blocking part... */
		{
			struct mbnode *iter2;
			for (iter2 = SLIST_FIRST(&self->mb_uparts);
			     iter2 != iter; iter2 = SLIST_NEXT(iter2, mbn_nxtuprt))
				mpart_lock_release(iter2->mbn_part);
		}
		unlockinfo_xunlock(unlock);
		while (!mpart_lock_available(part))
			task_yield();
		return false;
	}
	return true;
}



/* Acquire locks to all of the parts being mapped by `self', and
 * ensure that all mappings within `self' are fully continuous.
 * If this cannot be done without blocking, invoke `unlock' (if
 * given), try to make it so that a repeated call will (eventually)
 * succeed, and return `false'.
 * Otherwise (if all locks have been acquired, and all mappings are
 * continuous), return `true'.
 * NOTE: If this function returns with an exception, `unlock' will
 *       also be invoked. */
PUBLIC NONNULL((1)) bool FCALL
mbuilder_partlocks_acquire_or_unlock(struct mbuilder *__restrict self,
                                     struct unlockinfo *unlock)
		THROWS(E_BADALLOC, E_WOULDBLOCK) {
	/* Step #1: Acquire locks to all mapped parts. */
	if (!mbuilder_lock_all_mparts(self, unlock))
		goto fail;

	/* TODO */

	return true;
fail:
	return false;
}

/* Release locks to all of the mapped mem-parts, as should have previously
 * been acquired during a call to `mbuilder_partlocks_acquire()' */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mbuilder_partlocks_release)(struct mbuilder *__restrict self) {
	struct mbnode *node;
	SLIST_FOREACH (node, &self->mb_uparts, mbn_nxtuprt) {
		mpart_lock_release(node->mbn_part);
	}
}


/* Helper wrapper for `mbuilder_partlocks_acquire_or_unlock()' that
 * will keep on attempting the operation until it succeeds. */
PUBLIC NONNULL((1)) void FCALL
mbuilder_partlocks_acquire(struct mbuilder *__restrict self)
		THROWS(E_BADALLOC, E_WOULDBLOCK) {
	while (!mbuilder_partlocks_acquire_or_unlock(self, NULL))
		;
}

DECL_END

#endif /* !GUARD_KERNEL_SRC_MEMORY_MBUILDER_LOCK_C */
