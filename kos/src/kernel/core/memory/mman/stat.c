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
#ifndef GUARD_KERNEL_SRC_MEMORY_MMAN_STAT_C
#define GUARD_KERNEL_SRC_MEMORY_MMAN_STAT_C 1

#include <kernel/compiler.h>

#include <kernel/mman.h>
#include <kernel/mman/mnode.h>
#include <kernel/mman/mpart.h>
#include <kernel/mman/stat.h>
#include <sched/task.h>

#include <assert.h>
#include <atomic.h>
#include <stddef.h>
#include <string.h>

DECL_BEGIN

/* Recursively collect stat information for all nodes reachable from  `node',
 * but exclude info relating to `&FORMMAN(self, thismman_kernel_reservation)' */
PRIVATE NOBLOCK NONNULL((1, 2, 3)) void
NOTHROW(FCALL mnode_tree_stat)(struct mman *__restrict self,
                               struct mnode *__restrict node,
                               struct mman_statinfo *__restrict result) {
again:
	if likely(node != &FORMMAN(self, thismman_kernel_reservation)) {
		struct mpart *part;
		size_t nodesize;
		nodesize = mnode_getsize(node);
		result->msi_size += nodesize;
		if (node->mn_flags & MNODE_F_MLOCK)
			result->msi_lock += nodesize;
		if ((node->mn_flags & (MNODE_F_PEXEC | MNODE_F_PWRITE | MNODE_F_PREAD)) == (MNODE_F_PEXEC | MNODE_F_PREAD))
			result->msi_nexe += nodesize;
		if ((node->mn_flags & (MNODE_F_PEXEC | MNODE_F_PWRITE | MNODE_F_PREAD)) == (MNODE_F_PWRITE | MNODE_F_PREAD))
			result->msi_ndat += nodesize;
		part = node->mn_part;
		if likely(part != NULL) {
			uintptr_quarter_t state;
			if (mpart_isanon_atomic(part))
				result->msi_anon += nodesize;
			state = atomic_read(&part->mp_state);
			if (state == MPART_ST_SWP || state == MPART_ST_SWP_SC)
				result->msi_swap += nodesize;
		}
	}
	if (node->mn_mement.rb_lhs) {
		if (node->mn_mement.rb_rhs)
			mnode_tree_stat(self, node->mn_mement.rb_rhs, result);
		node = node->mn_mement.rb_lhs;
		goto again;
	}
	if (node->mn_mement.rb_rhs) {
		node = node->mn_mement.rb_rhs;
		goto again;
	}
}

/* Collect stats on the given mman `self', filling in `*result' */
PUBLIC NONNULL((1, 2)) void FCALL
mman_stat(struct mman *__restrict self,
          struct mman_statinfo *__restrict result)
		THROWS(E_WOULDBLOCK) {
	bzero(result, sizeof(*result));
	mman_lock_read(self);
	if likely(self->mm_mappings != NULL)
		mnode_tree_stat(self, self->mm_mappings, result);
	mman_lock_endread(self);
}

/* Returns the # of threads bound to this mman (s.a. `struct mman::mm_threads') */
PUBLIC NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW(FCALL mman_nrthreads)(struct mman *__restrict self) {
	struct task *thread;
	size_t result = 0;
	mman_threadslock_acquire(self);
	LIST_FOREACH (thread, &self->mm_threads, t_mman_tasks) {
		++result;
	}
	mman_threadslock_release(self);
	return result;
}

DECL_END

#endif /* !GUARD_KERNEL_SRC_MEMORY_MMAN_STAT_C */
