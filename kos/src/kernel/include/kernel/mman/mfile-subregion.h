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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_MMAN_MFILE_SUBREGION_H
#define GUARD_KERNEL_INCLUDE_KERNEL_MMAN_MFILE_SUBREGION_H 1

#include <kernel/compiler.h>

#include <kernel/mman/mfile.h>
#include <kernel/paging.h> /* PAGEDIR_PAGEALIGNED */

#include <kos/types.h>

#ifdef __CC__
DECL_BEGIN

/* Operator table for sub-region mfile-s */
DATDEF struct mfile_ops const mfile_subregion_ops;

/* Create a new, distinct sub-region wrapper around "self".
 * Memory mappings created by this mapping will behave  the
 * same as mappings created by  "self", only that they  are
 * offset by "minaddr", and cannot exceed "maxaddr".
 *
 * Additionally, `mfile_subregion_delete()' can be used  to
 * replace all memory  mappings created  from the  returned
 * mfile (or some other  sub-region mfile created from  it)
 * with "/dev/void" without running the risk of this revoke
 * failing due to OOM.
 *
 * @throw: E_INVALID_ARGUMENT_BAD_VALUE:E_INVALID_ARGUMENT_CONTEXT_FILE_SUBREGION_BOUNDS: [...]
 * @throw: E_INVALID_ARGUMENT_BAD_ALIGNMENT:E_INVALID_ARGUMENT_CONTEXT_FILE_SUBREGION_UNALIGNED_MINADDR: [...]
 * @throw: E_INVALID_ARGUMENT_BAD_ALIGNMENT:E_INVALID_ARGUMENT_CONTEXT_FILE_SUBREGION_UNALIGNED_MAXADDR: [...]
 * @throw: E_ILLEGAL_OPERATION:E_ILLEGAL_OPERATION_CONTEXT_SUBREGION_NOT_POSSIBLE:
 *         Given file `self' does not support "raw" I/O, and also isn't another sub-region mfile.
 *         >> !mfile_has_rawio(self) && self->mf_ops != &mfile_subregion_ops
 * @throw: E_ILLEGAL_OPERATION:E_ILLEGAL_OPERATION_CONTEXT_MMAP_BEYOND_END_OF_FILE:
 *         Given file `maxaddr' is greater than the or equal to current size of `self' */
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct mfile *KCALL
mfile_subregion(struct mfile *__restrict self,
                PAGEDIR_PAGEALIGNED pos_t minaddr, pos_t maxaddr)
		THROWS(E_BADALLOC, E_INVALID_ARGUMENT, E_ILLEGAL_OPERATION);

/* Return the name used by file mappings made by a given sub-region mfile "self"
 * @assume(self->mf_ops == &mfile_subregion_ops); */
FUNDEF NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct fdirent *
NOTHROW(FCALL mfile_subregion_getname)(struct mfile *__restrict self);

/* Delete all memory mappings created from a given sub-region mfile "self",
 * as well as recursively do the same for any further sub-regions that  may
 * have been created using "self".
 *
 * @assume(self->mf_ops == &mfile_subregion_ops);
 * @throw: E_WOULDBLOCK_PREEMPTED: Preemption is disabled (never happens if called from user-space) */
FUNDEF NONNULL((1)) void KCALL
mfile_subregion_delete(struct mfile *__restrict self)
		THROWS(E_WOULDBLOCK_PREEMPTED);

DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_MMAN_MFILE_SUBREGION_H */
