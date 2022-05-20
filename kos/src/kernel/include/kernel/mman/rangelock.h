/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_MMAN_RANGELOCK_H
#define GUARD_KERNEL_INCLUDE_KERNEL_MMAN_RANGELOCK_H 1

#include <kernel/compiler.h>

#include <kernel/mman/mnode.h>
#include <kernel/types.h>

#include <hybrid/sequence/list.h>

/* Helper functions for acquiring locks to the backing
 * mem-parts pointed-to by  the mem-nodes  of a  given
 * address range, whilst taking care of the fact  that
 * any mem-part must only be locked once (i.e.  having
 * accounting for *unique* mem-parts, and only locking
 * every part once). */

#ifdef __CC__
DECL_BEGIN

struct mnode;

#ifndef __mnode_slist_defined
#define __mnode_slist_defined
SLIST_HEAD(mnode_slist, mnode);
#endif /* !__mnode_slist_defined */

#define MRANGELOCK_UPRTS_NUMBUCKETS 4

struct mrangelock {
	struct mnode_tree_minmax mrl_nodes;                              /* Min/max in-bounds nodes. */
	struct mnode_slist       mrl_uprts[MRANGELOCK_UPRTS_NUMBUCKETS]; /* [0..n][*] Linked list of mem-nodes with unique parts. */
};

#define mrangelock_uparts_indexof(self, part) \
	(((uintptr_t)(part) >> 4) % MRANGELOCK_UPRTS_NUMBUCKETS)
#define mrangelock_uparts_listof(self, part) \
	(&(self)->mrl_uprts[mrangelock_uparts_indexof(self, part)])

struct mpart;
struct mman;
struct unlockinfo;

/* Rangelock filter function prototype.
 * @return: true:  The caller should acquire a lock to this node's part.
 * @return: false: This node's part is of no concern and need not be locked.
 *                 Additionally,  `mrangelock_acquire_or_unlock()'  need not
 *                 split this node if it lies on a boundary. */
typedef NOBLOCK NONNULL_T((2)) __BOOL
NOTHROW_T(FCALL *mrangelock_filter_cb_t)(void *arg, struct mnode *__restrict node);


/* Try to initialize `self' for the purpose of acquiring locks to all of
 * the backing mem-parts within the given address range. The caller must
 * already be holding a lock to `mm'.
 * NOTE: If  non-NULL, only the parts of nodes for which `filter' returns
 *       `true' will be locked. - Nodes for which `false' is returned are
 *       silently ignored (and will not be locked).
 * @return: NULL: Success  (all  (unique) parts  have  been locked)
 *                Only in this  case has  `self' been  initialized!
 *                In this case, `mnode_use_ilink_begin()' has  been
 *                called on all of the mem-nodes apart of the  list
 *                of nodes referencing unique mem-parts (mrl_uprts)
 * @return: * :   Error. - Acquiring  a lock to  `return' may  require
 *                the  caller  to  block until  it  becomes available.
 *                The caller should resolve  this issue by incref  the
 *                returned  mpart,  release  their lock  to  `mm', and
 *                yield  until  `mpart_lock_available(return)' becomes
 *                true before start over with acquiring a lock to `mm' */
#ifdef __INTELLISENSE__
NOBLOCK WUNUSED NONNULL((1, 2)) struct mpart *
NOTHROW(mrangelock_tryacquire)(struct mrangelock *__restrict self,
                               struct mman *__restrict mm,
                               void const *minaddr, void const *maxaddr,
                               mrangelock_filter_cb_t filter DFL(__NULLPTR),
                               void *filter_arg DFL(__NULLPTR));
#else /* __INTELLISENSE__ */
#define mrangelock_tryacquire(self, mm, minaddr, maxaddr, ...)             \
	(mman_mappings_minmaxlocate(mm, minaddr, maxaddr, &(self)->mrl_nodes), \
	 _mrangelock_tryacquire(self, ##__VA_ARGS__))
#endif /* !__INTELLISENSE__ */
FUNDEF NOBLOCK WUNUSED NONNULL((1)) struct mpart *
NOTHROW(FCALL _mrangelock_tryacquire)(struct mrangelock *__restrict self,
                                      mrangelock_filter_cb_t filter DFL(__NULLPTR),
                                      void *filter_arg DFL(__NULLPTR));


/* Release all of the locks held to the various unique mem-
 * parts of `self', as well as call `mnode_use_ilink_end()'
 * on all of the mapping  mem-nodes in order to once  again
 * free up usage of the ilink field of those nodes for  its
 * native purpose.
 * This function _MUST_ _ALWAYS_ be called after any of  the
 * above acquire-functions had previously succeeded in doing
 * so.  Furthermore, this function _MUST_ be caller _BEFORE_
 * the caller releases their lock on the associated mman */
FUNDEF NONNULL((1)) void
NOTHROW(FCALL mrangelock_release)(struct mrangelock *__restrict self);


DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_MMAN_RANGELOCK_H */
