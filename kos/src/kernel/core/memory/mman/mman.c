/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_SRC_MEMORY_MMAN_MMAN_C
#define GUARD_KERNEL_SRC_MEMORY_MMAN_MMAN_C 1

#include <kernel/compiler.h>

#include <kernel/heap.h>
#include <kernel/iovec.h>
#include <kernel/malloc.h>
#include <kernel/mman.h>
#include <kernel/paging.h>

#include <kos/except.h>

DECL_BEGIN

/* Memory manager reference counting control. */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mman_free)(struct mman *__restrict self) {
	/* TODO */
	heap_free(&kernel_locked_heap,
	          self,
	          self->mm_heapsize,
	          GFP_NORMAL);
}

PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mman_destroy)(struct mman *__restrict self) {
	pagedir_fini2(&self->mm_pagedir, self->mm_pdir_phys);
	/* TODO */
	weakdecref(self);
}

/* Memory manager construction functions. */
PUBLIC ATTR_RETNONNULL WUNUSED REF struct mman *FCALL
mman_new(void) THROWS(E_BADALLOC, ...) {
	/* TODO */
}

PUBLIC ATTR_RETNONNULL WUNUSED REF struct mman *FCALL
mman_fork(struct mman *__restrict self) THROWS(E_BADALLOC, ...) {
	/* TODO */
}

/* Set the mman active within the calling thread, as well as
 * change page directories to make use of the new mman before
 * returning. */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL task_setmman)(struct mman *__restrict newmman) {
	/* TODO */
}

/* Return the active mman of the given `thread' */
PUBLIC NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct mman *
NOTHROW(FCALL task_getmman)(struct task *__restrict thread) {
	/* TODO */
}

/* Reap dead ram regions of `self' */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL _mman_reap)(struct mman *__restrict self) {
	/* TODO */
}


DECL_END

#endif /* !GUARD_KERNEL_SRC_MEMORY_MMAN_MMAN_C */
