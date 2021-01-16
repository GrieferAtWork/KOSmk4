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
#ifndef GUARD_KERNEL_SRC_MEMORY_MBUILDER_C
#define GUARD_KERNEL_SRC_MEMORY_MBUILDER_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/malloc.h>
#include <kernel/mman/mbuilder.h>
#include <kernel/mman/mfile.h>
#include <kernel/mman/mnode.h>
#include <kernel/mman/mpart.h>

#include <string.h>

DECL_BEGIN

/* Finalize the given mem-builder. */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mbuilder_fini)(struct mbuilder *__restrict self) {
	/* TODO */
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
	/* TODO */
}

/* Helper wrapper for `mbuilder_partlocks_acquire_or_unlock()' that
 * will keep on attempting the operation until it succeeds. */
PUBLIC NONNULL((1)) void FCALL
mbuilder_partlocks_acquire(struct mbuilder *__restrict self)
		THROWS(E_BADALLOC, E_WOULDBLOCK) {
	/* TODO */
}

/* Release locks to all of the mapped mem-parts, as should have previously
 * been acquired during a call to `mbuilder_partlocks_acquire()' */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mbuilder_partlocks_release)(struct mbuilder *__restrict self) {
	/* TODO */
}


/* Apply all of the mappings from `self' onto `target', whilst simultaneously deleting
 * any memory mapping still present within `target' (except for the kernel-reserve node)
 * This function is guarantied to operate atomically in a way that allows the caller
 * to assume that no memory mappings (or anything else for that matter) changes if the
 * function fails and returns by throwing an error, and that everything happens exactly
 * as intended if it returns normally.
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
mbuilder_apply(struct mbuilder *__restrict self,
               struct mman *__restrict target,
               unsigned int additional_actions,
               struct mman_execinfo_struct *execinfo)
		THROWS(E_BADALLOC, E_WOULDBLOCK) {
	/* TODO */
}





/************************************************************************/
/* Functions for populating MBUILDER                                    */
/************************************************************************/

#ifndef __INTELLISENSE__
#define DEFINE_mbuilder_getunmapped_nx
#include "mm-unmapped.c.inl"
#define DEFINE_mbuilder_getunmapped
#include "mm-unmapped.c.inl"
#endif /* !__INTELLISENSE__ */


/* Map a given file into the specified mbuilder.
 * Behaves exactly the same as `mman_map()' */
PUBLIC NONNULL((1, 6)) void *KCALL
mbuilder_map(struct mbuilder *__restrict self,
             UNCHECKED void *hint, size_t num_bytes,
             unsigned int prot, unsigned int flags,
             struct mfile *__restrict file,
             struct path *file_fspath,
             struct directory_entry *file_fsname,
             pos_t file_pos,
             size_t min_alignment)
		THROWS(E_WOULDBLOCK, E_BADALLOC,
		       E_BADALLOC_INSUFFICIENT_VIRTUAL_MEMORY,
		       E_BADALLOC_ADDRESS_ALREADY_EXISTS) {
	/* TODO */
}

/* Same as `mbuilder_map()', but only allow pages entirely contained within
 * the file-relative address range `file_map_minaddr...file_map_maxaddr'
 * to be mapped. Attempting to map file contents beyond this range will
 * instead result in `&mfile_zero' getting mapped instead.
 * Behaves exactly the same as `mman_map_subrange()' */
PUBLIC NONNULL((1, 6)) void *KCALL
mbuilder_map_subrange(struct mbuilder *__restrict self,
                      UNCHECKED void *hint, size_t num_bytes,
                      unsigned int prot, unsigned int flags,
                      struct mfile *__restrict file,
                      struct path *file_fspath,
                      struct directory_entry *file_fsname,
                      pos_t file_pos,
                      pos_t file_map_minaddr,
                      pos_t file_map_maxaddr,
                      size_t min_alignment)
		THROWS(E_WOULDBLOCK, E_BADALLOC,
		       E_BADALLOC_INSUFFICIENT_VIRTUAL_MEMORY,
		       E_BADALLOC_ADDRESS_ALREADY_EXISTS) {
	/* TODO */
}


/* Same as `mbuilder_map()', but instead of actually mapping something, leave the
 * address range as empty (but possibly prepared), making it a reserved address range.
 * Behaves exactly the same as `mman_map_res()' */
PUBLIC NONNULL((1)) void *KCALL
mbuilder_map_res(struct mbuilder *__restrict self,
                 UNCHECKED void *hint, size_t num_bytes,
                 unsigned int flags, size_t min_alignment)
		THROWS(E_WOULDBLOCK, E_BADALLOC,
		       E_BADALLOC_INSUFFICIENT_VIRTUAL_MEMORY,
		       E_BADALLOC_ADDRESS_ALREADY_EXISTS) {
	/* TODO */
}


DECL_END

#endif /* !GUARD_KERNEL_SRC_MEMORY_MBUILDER_C */
