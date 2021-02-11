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
#ifndef GUARD_KERNEL_SRC_MEMORY_MMAN_MNODE_MERGE_C
#define GUARD_KERNEL_SRC_MEMORY_MMAN_MNODE_MERGE_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <fs/node.h>
#include <fs/vfs.h>
#include <kernel/mman.h>
#include <kernel/mman/mnode.h>
#include <kernel/mman/mpart.h>

#include <assert.h>

DECL_BEGIN

/* While holding  a lock  to `self->mn_mman'  and `self->mn_part',  try
 * to merge the given node with its successor/predecessor node, without
 * releasing any of the locks still held.
 * @return: * : The new, merged node (which may have a different min-addr
 *              that the original node `self'). Also note that this  node
 *              may or may not be equal to `self', and that it's min- and
 *              max-addr fields may be  different from those that  `self'
 *              had upon entry, irregardless of `self' being re-returned.
 *              As  a matter of fact `*self' becomes invalid after a call
 *              to this function! */
PUBLIC NOBLOCK ATTR_RETNONNULL NONNULL((1)) struct mnode *
NOTHROW(FCALL mnode_merge)(struct mnode *__restrict self) {
	assert(!self->mn_part || mpart_lock_acquired(self->mn_part));
	assert(self->mn_mman);
	assert(mman_lock_acquired(self->mn_mman));
	/* If we're not allowed to merge this node, then don't even try... */
	if unlikely(self->mn_flags & MNODE_F_NOMERGE)
		goto done;

	/* TODO */

done:
	return self;
}


DECL_END

#endif /* !GUARD_KERNEL_SRC_MEMORY_MMAN_MNODE_MERGE_C */
