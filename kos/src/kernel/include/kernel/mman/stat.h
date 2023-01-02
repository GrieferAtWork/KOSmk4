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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_MMAN_STAT_H
#define GUARD_KERNEL_INCLUDE_KERNEL_MMAN_STAT_H 1

#include <kernel/compiler.h>

#include <kernel/types.h>

#ifdef __CC__
DECL_BEGIN

struct mman;

/* NOTE: mapping info doesn't include `thismman_kernel_reservation'! */
struct mman_statinfo {
	size_t msi_size;   /* # of bytes that have mappings associated. */
	size_t msi_lock;   /* # of bytes who's mnode-s have MNODE_F_MLOCK. */
	size_t msi_nexe;   /* # of bytes mapped as `(MNODE_F_PREAD | MNODE_F_PEXEC) & ~MNODE_F_PWRITE'. */
	size_t msi_ndat;   /* # of bytes mapped as `(MNODE_F_PREAD | MNODE_F_PWRITE) & ~MNODE_F_PEXEC'. */
	size_t msi_anon;   /* # of bytes backed by `mpart_isanon()'-parts. */
	size_t msi_swap;   /* # of bytes backed by mem-parts stored in swap. */
};


/* Collect stats on the given mman `self', filling in `*result' */
FUNDEF NONNULL((1, 2)) void FCALL
mman_stat(struct mman *__restrict self,
          struct mman_statinfo *__restrict result)
		THROWS(E_WOULDBLOCK);

/* Returns the # of threads bound to this mman (s.a. `struct mman::mm_threads') */
FUNDEF NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW(FCALL mman_nrthreads)(struct mman *__restrict self);


DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_MMAN_STAT_H */
