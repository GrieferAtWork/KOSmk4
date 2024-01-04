/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_SRC_MEMORY_MMAN_MMAN_RANGELOCK_C
#define GUARD_KERNEL_SRC_MEMORY_MMAN_MMAN_RANGELOCK_C 1
#define __WANT_MNODE__mn_ilink
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/mman.h>
#include <kernel/mman/mnode.h>
#include <kernel/mman/mpart.h>
#include <kernel/mman/rangelock.h>

#include <assert.h>
#include <stddef.h>
#include <string.h>

DECL_BEGIN

#if !defined(NDEBUG) && !defined(NDEBUG_FINI)
#define DBG_memset memset
#else /* !NDEBUG && !NDEBUG_FINI */
#define DBG_memset(...) (void)0
#endif /* NDEBUG || NDEBUG_FINI */

/* Check if `self' is holding a lock on `part' */
PRIVATE NOBLOCK ATTR_PURE NONNULL((1, 2)) bool
NOTHROW(FCALL mrangelock_is_locked_part)(struct mrangelock const *__restrict self,
                                         struct mpart const *__restrict part) {
	struct mnode_slist const *ulist;
	struct mnode const *iter;
	ulist = mrangelock_uparts_listof(self, part);
	SLIST_FOREACH (iter, ulist, _mn_ilink) {
		if (iter->mn_part == part)
			return true;
	}
	return false;
}

/* Try to initialize `self' for the purpose of acquiring locks to all of
 * the backing mem-parts within the given address range. The caller must
 * already be holding a lock to `mm'.
 * NOTE: If  non-NULL, only the parts of nodes for which `filter' returns
 *       `true' will be locked. - Nodes for which `false' is returned are
 *       silently ignored (and will not be locked).
 * @return: NULL: Success (all  (unique)  parts  have  been  locked)
 *                Only  in  this case  has `self'  been initialized!
 *                In this case,  `mnode_use_ilink_begin()' has  been
 *                called on all of the  mem-nodes apart of the  list
 *                of nodes referencing unique mem-parts (mrl_uparts)
 * @return: * :   Error. - Acquiring  a lock to  `return' may  require
 *                the  caller  to  block until  it  becomes available.
 *                The caller should resolve  this issue by incref  the
 *                returned  mpart,  release  their lock  to  `mm', and
 *                yield  until  `mpart_lock_available(return)' becomes
 *                true before start over with acquiring a lock to `mm' */
PUBLIC NOBLOCK WUNUSED NONNULL((1)) struct mpart *
NOTHROW(FCALL _mrangelock_tryacquire)(struct mrangelock *__restrict self,
                                      mrangelock_filter_cb_t filter,
                                      void *filter_arg) {
	bzero(self->mrl_uprts, sizeof(self->mrl_uprts));
	if (self->mrl_nodes.mm_min) {
		struct mnode *node;
		for (node = self->mrl_nodes.mm_min;;) {
			struct mpart *part;
			if ((part = node->mn_part) != NULL &&
			    (!filter || (*filter)(filter_arg, node))) {
				if (mpart_lock_tryacquire(part)) {
					struct mnode_slist *ulist;
					mnode_use_ilink_begin(node);
					/* Add this node to the list of nodes w/ unique parts! */
					ulist = mrangelock_uparts_listof(self, part);
					SLIST_INSERT(ulist, node, _mn_ilink);
				} else {
					/* Failed to acquire the lock.
					 * If this is because we've already locked `part',
					 * then we have to  silently ignore this node  and
					 * proceed  onwards.  But if  we  haven't already,
					 * then we  must release  all locks  and return  a
					 * pointer to the blocking part! */
					if (!mrangelock_is_locked_part(self, part)) {
						/* Oops... Blocking part!
						 * -> Release all locks already acquired. */
						mrangelock_release(self);

						/* Return a pointer to the blocking part. */
						return part;
					}
				}
			}
			if (node == self->mrl_nodes.mm_max)
				break;
			node = mnode_tree_nextnode(node);
			assert(node);
		}
	}
	return NULL;
}



/* Release all of the locks held to the various unique mem-
 * parts of `self', as well as call `mnode_use_ilink_end()'
 * on all of the mapping  mem-nodes in order to once  again
 * free up usage of the ilink field of those nodes for  its
 * native purpose.
 * This function _MUST_ _ALWAYS_ be called after any of  the
 * above acquire-functions had previously succeeded in doing
 * so.  Furthermore, this function _MUST_ be caller _BEFORE_
 * the caller releases their lock on the associated mman */
PUBLIC NONNULL((1)) void
NOTHROW(FCALL mrangelock_release)(struct mrangelock *__restrict self) {
	/* Release locks to all unique parts and free up  the
	 * ilink field of all of the associated nodes back to
	 * the given `mm' */
	unsigned int i;
	for (i = 0; i < MRANGELOCK_UPRTS_NUMBUCKETS; ++i) {
		struct mnode *iter, *next;
		iter = SLIST_FIRST(&self->mrl_uprts[i]);
		while (iter) {
			next = SLIST_NEXT(iter, _mn_ilink);
			assert(iter->mn_part);
			mpart_lock_release(iter->mn_part);
			mnode_use_ilink_end(iter);
			iter = next;
		}
	}
	DBG_memset(self, 0xcc, sizeof(*self));
}


DECL_END

#endif /* !GUARD_KERNEL_SRC_MEMORY_MMAN_MMAN_RANGELOCK_C */
