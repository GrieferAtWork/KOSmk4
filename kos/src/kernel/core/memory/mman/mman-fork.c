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
#ifndef GUARD_KERNEL_SRC_MEMORY_MMAN_MMAN_FORK_C
#define GUARD_KERNEL_SRC_MEMORY_MMAN_MMAN_FORK_C 1

#include <kernel/compiler.h>

#include <kernel/mman.h>
#include <kernel/mman/mnode.h>
#include <kernel/mman/mpart.h>
#include <kernel/paging.h>

#include <kos/except.h>

DECL_BEGIN

/*
 * === Bad ideas (and why they're bad) ===
 *
 * pagedir_fork:
 *    Use the `v_unused*_ign' bits of the entries of all of the
 *    dynamically allocated vectors within the page directory
 *    as a data-stream to encode a reference counter for the
 *    surrounding page-vector. (s.a. `p32_pagedir_refe2_incref')
 *
 * >> // Initialize `self' as a fork-copy of the current page directory:
 * >> //   - Initialize kernel-space of `self' completely normal.
 * >> //   - Clear the WRITABLE bit for all user-space pages
 * >> //   - (try to) increment the reference counter for all currently
 * >> //     allocated vectors in `P32_PDIR_E2_IDENTITY'. Where this is
 * >> //     impossible (due to a refcnt overflow), a hard copy of the
 * >> //     associated vector is made.
 * >> INTDEF NOBLOCK NONNULL((1)) void
 * >> NOTHROW(FCALL p32_pagedir_fork)(VIRT struct p32_pdir *__restrict self,
 * >>                                 PHYS struct p32_pdir *phys_self);
 * >> 
 * >> // Reference counter control for `P32_PDIR_E2_IDENTITY[vec2]'
 * >> // NOTE: Reference counting is implemented by combining the `d_unused1_ign'
 * >> //       fields of all of the E1-entires pointed to by the indexed E2-vector.
 * >> INTDEF NOBLOCK __BOOL NOTHROW(FCALL p32_pagedir_refe2_incref)(unsigned int vec2); // true: OK; false: Failed to incref
 * >> INTDEF NOBLOCK __BOOL NOTHROW(FCALL p32_pagedir_refe2_decref)(unsigned int vec2); // true: OK; false: Last ref has gone away (you must free the vector now)
 * >> INTDEF NOBLOCK __BOOL NOTHROW(FCALL p32_pagedir_refe2_isshrd)(unsigned int vec2); // true: At least 2 references; false: 1 reference
 *
 * BAD: Is this really something that would make sense? After all:
 *      all of the page directory initialization on `newmm' will
 *      already happen completely lazily, and the intended use of
 *      fork() is to-be followed by an exec(), meaning that it
 *      doesn't actually make that much sense to not just do what
 *      the old VM system did; even in regards to how to implement
 *      exec... (i.e. don't create a new mman on exec, but use the
 *      `struct mbuilder' system and `mbuilder_apply()')
 *
 */


/* Memory manager construction functions.
 * NOTE: mman_fork() will fork the current mman. */
PUBLIC ATTR_RETNONNULL WUNUSED REF struct mman *FCALL
mman_fork(void) THROWS(E_BADALLOC, ...) {
	REF struct mman *newmm;
	struct mman *oldmm;
	oldmm = THIS_MMAN;
	newmm = mman_new();
	TRY {
		/* TODO: All at once: Acquire a lock to `oldmm' and every unique `mpart'
		 *                    mapped by any of its mnode-s. Additionally, allocate
		 *                    exactly 1 mem-node for every mem-node apart of `oldmm'
		 * It may also be useful to expose this functionality via a public API
		 * `mman_preparefork_or_unlock()', that acquires all of the locks, and
		 * does all of the necessary allocation... */

		/* TODO: Initialize all of the new mem-nodes to do copy-on-write on
		 *       the relevant mem-parts. During this process, we don't even
		 *       have to construct a new R/B-tree, since we can just blindly
		 *       copy the old mman's R/B-tree layout (with special handling for
		 *       `thismman_kernel_reservation' of course) */

		/* TODO: Release all of the locks we're still holding to the unique parts
		 *       from `oldmm'. However, don't release our lock to `oldmm' itself,
		 *       yet! */

		/* TODO: Unless the arch supports `pagedir_fork()', temporarily set the
		 *       resulting mman as the current, go through all mapped nodes, and
		 *       make use of `mpart_mmap()' to create mappings for those nodes
		 *       within the new page directory. */

		/* NOTE: No further initialization of the underlying page directory of `newmm'
		 *       is needed, since everything will happen lazily on first access. This
		 *       way, we don't even have to  */
	} EXCEPT {
		decref_likely(newmm);
		RETHROW();
	}
	return newmm;
}


DECL_END

#endif /* !GUARD_KERNEL_SRC_MEMORY_MMAN_MMAN_FORK_C */
