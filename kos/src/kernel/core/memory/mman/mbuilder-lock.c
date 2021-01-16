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
#ifndef GUARD_KERNEL_SRC_MEMORY_MBUILDER_LOCK_C
#define GUARD_KERNEL_SRC_MEMORY_MBUILDER_LOCK_C 1
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


DECL_END

#endif /* !GUARD_KERNEL_SRC_MEMORY_MBUILDER_LOCK_C */
