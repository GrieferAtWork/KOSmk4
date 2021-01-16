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
#ifndef GUARD_KERNEL_SRC_MEMORY_MBUILDER_APPLY_C
#define GUARD_KERNEL_SRC_MEMORY_MBUILDER_APPLY_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/malloc.h>
#include <kernel/mman/mbuilder.h>
#include <kernel/mman/mfile.h>
#include <kernel/mman/mnode.h>
#include <kernel/mman/mpart.h>

#include <assert.h>
#include <string.h>

DECL_BEGIN

/* Apply all of the mappings from `self' onto `target', whilst simultaneously deleting
 * any memory mapping still present within `target' (except for the kernel-reserve node)
 * This function is guarantied to operate atomically in a way that allows the caller
 * to assume that no memory mappings (or anything else for that matter) changes if the
 * function fails and returns by throwing an error, and that everything happens exactly
 * as intended if it returns normally.
 * NOTE: Upon success, `self' will have been finalized.
 * @param: self:   The VM Builder object from which to take mappings to-be applied to `target'
 *                 Upon success, the contents of `self' are left undefined and must either be
 *                 re-initialized, or not be attempted to be finalized.
 * @param: target: The target VM to which to apply the new memory mappings.
 *                 Upon success, this VM will only contain the mappings from `self', with all
 *                 of its old mappings having been deleted.
 *                 NOTE: This argument must not be the kernel VM
 * @param: additional_actions: Additional actions to be atomically performed alongside
 *                 the application of the new memory mappings (set of `VMB_APPLY_AA_*') */
PUBLIC NONNULL((1, 2)) void KCALL
mbuilder_apply_and_fini(struct mbuilder *__restrict self,
                        struct mman *__restrict target,
                        unsigned int additional_actions,
                        struct mman_execinfo_struct *execinfo)
		THROWS(E_BADALLOC, E_WOULDBLOCK) {
	/* TODO */
}

DECL_END

#endif /* !GUARD_KERNEL_SRC_MEMORY_MBUILDER_APPLY_C */
