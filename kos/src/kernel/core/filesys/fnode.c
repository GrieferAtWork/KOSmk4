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
#ifndef GUARD_KERNEL_CORE_FILESYS_FNODE_C
#define GUARD_KERNEL_CORE_FILESYS_FNODE_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/fs/fnode.h>
#include <kernel/fs/fsuper.h>

#include <hybrid/atomic.h>

#include <kos/except.h>

#include <assert.h>
#include <stddef.h>

DECL_BEGIN

/* Mandatory callback for all types derived from `struct fnode',
 * for use with `mf_ops->mo_changed'. MUST NOT BE OVERWRITTEN! */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL fnode_v_changed)(struct fnode *__restrict self,
                               uintptr_t old_flags,
                               uintptr_t UNUSED(new_flags)) {
	if (!(old_flags & (MFILE_F_CHANGED | MFILE_F_ATTRCHANGED))) {
		/* Add to the list of changed file-nodes the first time around. */
		struct fsuper *super = self->fn_super;
		struct fnode *next;
		incref(self);
		do {
			next = ATOMIC_READ(super->fs_changed.slh_first);
			if unlikely(next == FSUPER_NODES_DELETED) {
				decref_nokill(self);
				break;
			}
			self->fn_changed.sle_next = next;
			COMPILER_WRITE_BARRIER();
		} while (!ATOMIC_CMPXCH_WEAK(super->fs_changed.slh_first,
		                             next, self));
		if (next == NULL) {
			/* First changed node was added to the superblock.
			 * ->  */
		}
	}
}

/* File-node destroy callback. Must be set in `mo_destroy',
 * but may be overwritten by sub-classes, in which case this
 * function must be called as the last thing done within the
 * sub-class destroy-operator. */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL fnode_v_destroy)(struct fnode *__restrict self) {
}


DECL_END

#endif /* !GUARD_KERNEL_CORE_FILESYS_FNODE_C */
