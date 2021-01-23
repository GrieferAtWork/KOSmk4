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
#ifndef GUARD_KERNEL_SRC_MEMORY_MMAN_MMAN_C
#define GUARD_KERNEL_SRC_MEMORY_MMAN_MMAN_C 1

#include <kernel/compiler.h>

#include <kernel/heap.h>
#include <kernel/iovec.h>
#include <kernel/malloc.h>
#include <kernel/mman.h>
#include <kernel/mman/mm-event.h>
#include <kernel/mman/mm-lockop.h>
#include <kernel/paging.h>

#include <kos/except.h>

#include <assert.h>

DECL_BEGIN

typedef NONNULL((1)) void (KCALL *pervm_init_t)(struct vm *__restrict self) /*THROWS(...)*/;
typedef NOBLOCK NONNULL((1)) void /*NOTHROW*/ (KCALL *pervm_fini_t)(struct vm *__restrict self);
INTDEF pervm_init_t __kernel_pervm_init_start[];
INTDEF pervm_init_t __kernel_pervm_init_end[];
INTDEF pervm_fini_t __kernel_pervm_fini_start[];
INTDEF pervm_fini_t __kernel_pervm_fini_end[];


/* List of callbacks that should be invoked after mman_exec()
 * These are called alongside stuff like `handle_manager_cloexec()'
 * NOTE: The passed mman is always `THIS_MMAN', and is never `&mman_kernel' */
PUBLIC CALLBACK_LIST(void KCALL(void)) mman_onexec_callbacks = CALLBACK_LIST_INIT;
/* Mman initialization/finalization callbacks. */
PUBLIC CALLBACK_LIST(void FCALL(struct mman *)) mman_oninit_callbacks = CALLBACK_LIST_INIT;
PUBLIC CALLBACK_LIST(void FCALL(struct mman *)) mman_onfini_callbacks = CALLBACK_LIST_INIT;
PUBLIC CALLBACK_LIST(void FCALL(struct mman * /*newmman*/, struct mman * /*oldmman*/)) mman_onclone_callbacks = CALLBACK_LIST_INIT;



/* Memory manager reference counting control. */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mman_free)(struct mman *__restrict self) {
	heap_free(&kernel_locked_heap,
	          self,
	          self->mm_heapsize,
	          GFP_NORMAL);
}

PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mman_destroy)(struct mman *__restrict self) {
	assert(self != THIS_MMAN);
	assert(self != &mman_kernel);
	pagedir_fini2(&self->mm_pagedir, self->mm_pagedir_p);
	assert(LIST_EMPTY(&self->mm_threads));

	/* Invoke per-VM finalizer callbacks. */
	mman_onfini_callbacks(self);
	{
		pervm_fini_t *iter = __kernel_pervm_fini_start;
		for (; iter < __kernel_pervm_fini_end; ++iter)
			(**iter)(self);
		assert(iter == __kernel_pervm_fini_end);
	}

	/* TODO */
	weakdecref(self);
}

/* Memory manager construction functions. */
PUBLIC ATTR_RETNONNULL WUNUSED REF struct mman *FCALL
mman_new(void) THROWS(E_BADALLOC, ...) {
	/* TODO */
}

PUBLIC ATTR_RETNONNULL WUNUSED REF struct mman *FCALL
mman_fork(void) THROWS(E_BADALLOC, ...) {
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


DECL_END

#endif /* !GUARD_KERNEL_SRC_MEMORY_MMAN_MMAN_C */
