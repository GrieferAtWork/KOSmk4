/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_MMAN_MFILE_MISALIGNED_H
#define GUARD_KERNEL_INCLUDE_KERNEL_MMAN_MFILE_MISALIGNED_H 1

#include <kernel/compiler.h>

#include <kernel/mman/mfile.h>

#include <hybrid/sched/__preemption.h>

#ifdef __CC__
DECL_BEGIN

struct misaligned_mfile
#ifdef __cplusplus
    : mfile
#endif /* __cplusplus */
{
#ifndef __cplusplus
	struct mfile                 mam_file; /* The underlying file */
#endif /* !__cplusplus */
	REF struct mfile            *mam_base; /* [1..1][const] The file around which this one is a wrapper. */
	size_t                       mam_offs; /* [const] Offset addend added to every request. */
	LIST_ENTRY(misaligned_mfile) mam_link; /* [lock(mfile_tslock_acquired(mam_base))][0..1]
	                                        * Link in list of misaligned sub-files of `mam_base'.
	                                        * This list is sorted by `mam_offs'. */
};

#define mfile_asmisaligned(self) ((struct misaligned_mfile *)(self))
#define mfile_ismisaligned(self) ((self)->mf_ops == &misaligned_mfile_ops)

DATDEF struct mfile_ops const misaligned_mfile_ops;

/* Create a wrapper file whose I/O cache is lazily populated from inner,
 * at offsets based on `*p_inner_fpos'. Note that the returned file will
 * probably not be writable, and that any modifications made to portions
 * of  `inner' that have  already been loaded by  `return' will _NOT_ be
 * visible (meaning that  the returned file  only works for  MAP_PRIVATE
 * mappings).
 *
 * This function is primarily used as a hacky wrapper for loading PE files
 * into memory (as those  sometimes have sub-page alignment  constraints).
 *
 * NOTES:
 * - The caller must ensure that `mfile_hasrawio(inner)'!
 * - This function will adjust `p_inner_fpos' such that (upon return) there
 *   is an invariant  `mfile_partaddr_aligned(return, OUT(*p_inner_fpos))'.
 * - This function doesn't necessarily return a misaligned file (hence  why
 *   its return type is just  `mfile'). When the effective alignment  turns
 *   out to be `0', it will just re-return `inner', and if another matching
 *   misaligned file already exists, that one is simply re-used. */
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) REF struct mfile *FCALL
mfile_create_misaligned_wrapper(struct mfile *__restrict inner,
                                pos_t *__restrict p_inner_fpos)
		THROWS(E_BADALLOC);

/* Unlink misaligned wrappers of `self' and mark them as  deleted.
 * This function needs to be called in order to release the TSLOCK
 * of a file after `MFILE_F_DELETED' was set. */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL _mfile_tslock_release_and_delete_misaligned_wrappers)(struct mfile *__restrict self,
                                                                    __hybrid_preemption_flag_t __hpsmp_pflag);
#define mfile_tslock_release_and_delete_misaligned_wrappers_br(self) \
	_mfile_tslock_release_and_delete_misaligned_wrappers(self, __hpsmp_pflag)
#define mfile_tslock_release_and_delete_misaligned_wrappers(self) \
	mfile_tslock_release_and_delete_misaligned_wrappers_br(self); } __WHILE0

DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_MMAN_MFILE_MISALIGNED_H */
