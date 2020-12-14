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
}

PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mman_destroy)(struct mman *__restrict self) {
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


/* Try to pre-fault access to the given addres range, such that `memcpy_nopf()'
 * may succeed when re-attempted.
 * @return: * : The # of leading bytes that this function managed to fault. For
 *              this purpose, any non-zero value means that `*(byte_t *)addr'
 *              was made accessible for at least one moment before this function
 *              returns. Note though that memory may have already been unloaded
 *              by the time this function returns (unlikely), so the caller must
 *              still be ready to deal with the possibility that another attempt
 *              at doing nopf access at `*(byte_t *)addr' might immediatly fail
 *              again.
 *              Also note that for any memory that had already been faulted within
 *              the given address range, this function acts as though it had been
 *              the one to fault that range, meaning that the return value doesn't
 *              actually represent how much memory had just been faulted, but rather
 *              how much continuous memory (starting at `addr' and limited by at
 *              most `num_bytes') was faulted simultaneously at some point before
 *              this function returns.
 * @return: 0 : Nothing could be faulted. This might be because `addr' doesn't
 *              point into mapped memory, or the memory that is pointed-to by it
 *              is backed by VIO storage.
 *              The caller should handle this case by attempting direct memory
 *              access to the affected region (i.e. using `memcpy' rather than 
 *              `memcpy_nopf'), and dealing with any potential E_SEGFAULT error. */
PUBLIC size_t FCALL
mman_prefault(USER CHECKED void const *addr,
              size_t num_bytes, bool for_writing)
		THROWS(E_WOULDBLOCK, E_BADALLOC) {
	/* TODO */
}

/* Enumerate segments from `buffer', and prefault up to `num_bytes' of pointed-to
 * memory, after skipping the first `offset' bytes. The return value is the sum
 * of successfully faulted segments, however faulting also stops on the first
 * segment that cannot be fully faulted. */
PUBLIC size_t FCALL
mman_prefaultv(struct aio_buffer const *__restrict buffer,
               size_t offset, size_t num_bytes, bool for_writing)
		THROWS(E_WOULDBLOCK, E_BADALLOC) {
	struct aio_buffer_entry ent;
	size_t temp, result = 0;
	AIO_BUFFER_FOREACH(ent, buffer) {
		if (offset != 0) {
			if (offset >= ent.ab_size) {
				offset -= ent.ab_size;
				continue;
			}
			ent.ab_base += offset;
			ent.ab_size -= offset;
		}
		if (ent.ab_size > num_bytes)
			ent.ab_size = num_bytes;
		/* Prefault this part. */
		temp = mman_prefault(ent.ab_base, ent.ab_size, for_writing);
		result += temp;
		/* Stop upon the first partial error (iow: once reaching
		 * the first byte that could not be faulted) */
		if (temp < ent.ab_size)
			break;
		if (ent.ab_size >= num_bytes)
			break;
		num_bytes -= ent.ab_size;
	}
	return result;
}


DECL_END

#endif /* !GUARD_KERNEL_SRC_MEMORY_MMAN_MMAN_C */
