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
#ifndef GUARD_KERNEL_SRC_MEMORY_MBUILDER_APPLY_C
#define GUARD_KERNEL_SRC_MEMORY_MBUILDER_APPLY_C 1
#define __WANT_MPART__mp_nodlsts /* mpart_getnodlst_from_mnodeflags() */
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/compat.h>
#include <kernel/fs/dirent.h>
#include <kernel/fs/path.h>
#include <kernel/malloc.h>
#include <kernel/mman.h>
#include <kernel/mman/execinfo.h>
#include <kernel/mman/mbuilder.h>
#include <kernel/mman/mfile.h>
#include <kernel/mman/mnode.h>
#include <kernel/mman/module.h>
#include <kernel/mman/mpart.h>
#include <kernel/paging.h>
#include <misc/unlockinfo.h>
#include <sched/pertask.h>
#include <sched/rpc-internal.h>
#include <sched/rpc.h>
#include <sched/task.h>
#include <sched/userkern.h>

#include <hybrid/sequence/list.h>

#include <kos/except.h>
#include <kos/types.h>
#include <sys/wait.h>

#include <assert.h>
#include <atomic.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

DECL_BEGIN

#if !defined(NDEBUG) && !defined(NDEBUG_FINI)
#define DBG_memset(p, c, n) memset(p, c, n)
#else /* !NDEBUG && !NDEBUG_FINI */
#define DBG_memset(p, c, n) (void)0
#endif /* NDEBUG || NDEBUG_FINI */

/* Set the `MNODE_F_UNMAPPED' flag for all nodes starting at `root' */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mnode_tree_foreach_set_unmapped)(struct mnode *__restrict root) {
again:
	atomic_or(&root->mn_flags, MNODE_F_UNMAPPED);

	/* Keep track of how many nodes are mapping a particular module. */
	if (root->mn_module)
		module_dec_nodecount(root->mn_module);
	DBG_memset(&root->mn_module, 0xcc, sizeof(root->mn_module));
	if (root->mn_mement.rb_lhs) {
		if (root->mn_mement.rb_rhs)
			mnode_tree_foreach_set_unmapped(root->mn_mement.rb_rhs);
		root = root->mn_mement.rb_lhs;
		goto again;
	}
	if (root->mn_mement.rb_rhs) {
		root = root->mn_mement.rb_rhs;
		goto again;
	}
}

PUBLIC NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL mnode_tree_init_mman_and_module)(struct mnode *__restrict root,
                                               struct mman *__restrict mm) {
again:
	/* We must also delete a couple of flags that may still be left in the node,
	 * and  that might  otherwise interfere  with other  mman system components. */
	root->mn_flags &= ~(MBNODE_F_POPULATE | MBNODE_F_NONBLOCK);
	assertf(!(root->mn_flags & MNODE_F_UNMAPPED), "Why is this node marked as UNMAPPED?");
	assertf(!(root->mn_flags & MNODE_F_MPREPARED), "You can't set the PREPARED flag for user-space nodes!");
	assertf(!(root->mn_flags & MNODE_F_MHINT), "You can't set the MHINT flag for user-space nodes!");
	root->mn_mman   = mm;
	root->mn_module = NULL;
	if (root->mn_mement.rb_lhs) {
		if (root->mn_mement.rb_rhs)
			mnode_tree_init_mman_and_module(root->mn_mement.rb_rhs, mm);
		root = root->mn_mement.rb_lhs;
		goto again;
	}
	if (root->mn_mement.rb_rhs) {
		root = root->mn_mement.rb_rhs;
		goto again;
	}
}


/* Apply all of the mappings from  `self' onto `target', whilst simultaneously  deleting
 * any memory mapping still present within `target' (except for the kernel-reserve node)
 * NOTES:
 *  - When calling this function, the caller must ensure that:
 *     - mbuilder_partlocks_acquire(self)    (was called)
 *     - mman_lock_acquired(target)
 *  - Upon return, this function will have released all of the part-locks originally
 *    acquired  by `mbuilder_partlocks_acquire()', however the mman-lock to `target'
 *    will  _not_ have been released yet, and the caller must release that lock once
 *    they've finished doing other additional builder-apply operations.
 *  - This  function  doesn't  actually  modify  the  page  directory  of   `target'.
 *    The caller is responsible for doing this by calling `pagedir_unmap_userspace()'
 * @param: self:   The mman Builder object from which to take mappings to-be applied to `target'
 *                 Upon success, the contents  of `self' are left  undefined and must either  be
 *                 re-initialized, or not be attempted to be finalized.
 * @param: target: The target mman to which to apply the new memory mappings.
 *                 Upon success, this mman will only contain the mappings from `self', with all
 *                 of its old mappings having been deleted.
 *                 NOTE: This argument must not be the kernel mman */
PUBLIC NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL mbuilder_apply_impl)(struct mbuilder *__restrict self,
                                   struct mman *__restrict target) {
	struct mbnode *fmnode;
	size_t i;

	/* Step #1: Unlink the kernel-reserve node from `target' */
	mman_mappings_removenode(target, &FORMMAN(target, thismman_kernel_reservation));
	assert(!LIST_ISBOUND(&FORMMAN(target, thismman_kernel_reservation), mn_writable));

	/* Step #2: Clear the target mman's list of writable nodes. */
	LIST_CLEAR(&target->mm_writable);

	/* Step #3: Go over all nodes currently mapped in `target', and
	 *          set the `MNODE_F_UNMAPPED'  flag for  all of  them. */
	assert(!self->mb_oldmap);
	if ((self->mb_oldmap = target->mm_mappings) != NULL)
		mnode_tree_foreach_set_unmapped(self->mb_oldmap);

	/* Step #4: Go over all file mappings and fill in the fields:
	 *    - _mbn_partoff
	 *    - _mbn_link */
	for (fmnode = SLIST_FIRST(&self->mb_files); fmnode;) {
		pos_t fm_base;   /* File-map-base */
		byte_t *mm_base; /* Memory-map-base */
		struct mbnode *iter, *fmnext;
		fmnext  = SLIST_NEXT(fmnode, mbn_nxtfile);
		mm_base = fmnode->mbn_minaddr;
		fm_base = mnode_mbn_filpos_get(fmnode);
		iter    = fmnode;
		decref_unlikely(fmnode->mbn_file); /* No longer needed... */
		do {
			pos_t fm_iter;
			struct mnode_list *link_list;
			struct mpart *part;
			part    = iter->mbn_part;
			fm_iter = fm_base + (size_t)(iter->mbn_minaddr - mm_base);
			assertf(fm_iter >= part->mp_minaddr,
			        "This should have been asserted earlier, and we should "
			        "have been holding a lock to `part' ever since!");
			iter->_mbn_partoff = (mpart_reladdr_t)(fm_iter - part->mp_minaddr);

			/* Add the node to the part's relevant list of nodes. */
			link_list = mpart_getnodlst_from_mnodeflags(part, iter->mbn_flags);
			LIST_INSERT_HEAD(link_list, (struct mnode *)iter, mn_link);
		} while ((iter = iter->mbn_filnxt) != NULL);
		fmnode = fmnext;
	}
	SLIST_INIT(&self->mb_files);

	/* Step #5: Go over _all_ nodes and set the `_mbn_mman' and `_mbn_module' field. */
	mnode_tree_init_mman_and_module((struct mnode *)self->mb_mappings, target);

	/* Step #6: Actually assign the new mappings-tree to the target mman */
	target->mm_mappings = (struct mnode *)self->mb_mappings;
	self->mb_mappings   = NULL; /* Got inherited! */

	/* Step #7: Go over all  of the  nodes from `mb_uparts'  and release  our
	 *          locks to  the associated  mem-parts.  Note that  the  address
	 *          of the  `mbn_nxtuprt' field  (which is  used to  link all  of
	 *          the  nodes pointing  to parts  who's locks  we're holding) is
	 *          set-up such that it shares its address with the `mn_writable'
	 *          field. As such, all  nodes with non-unique mem-parts  already
	 *          have  `mn_writable'  initialized  correctly,  and  all  nodes
	 *          with unique ones can still  be enumerated since the  writable
	 *          link field wasn't  already overwritten by  any of the  above! */
	for (i = 0; i < MBNODE_PARTSET_NUMBUCKETS; ++i) {
		struct mbnode *iter;
		for (iter = LIST_FIRST(&self->mb_uparts.mbps_set[i]); iter;) {
			struct mbnode *next;
			next = LIST_NEXT(iter, mbn_nxtuprt);

			/* Release the part lock. */
			mpart_lock_release(iter->mbn_part);

			/* Initialize the writable-link as unbound. */
			LIST_ENTRY_UNBOUND_INIT(&iter->_mbn_writable);
			iter = next;
		}
	}

	/* In  compatibility-mode, there is  a chance that `thismman_kernel_reservation'
	 * was resized to span a larger region of memory in order to simulate an address
	 * space that may be found on the emulated architecture.
	 *
	 * This happens mainly as the result of attempting to access ukern at an address
	 * that  should have been apart of kernel-space, but wasn't because kernel-space
	 * was actually allocated elsewhere:
	 *
	 * >> PF_HANDLER:
	 * >>     if (ATTEMTED_TO_ACCESS_UNMAPPED_ADDRESS) {
	 * >> #if !defined(CONFIG_NO_KERNEL_USERKERN_SEGMENT) && defined(__ARCH_HAVE_COMPAT)
	 * >>         if (IN_COMPAT_MODE() &&
	 * >>             FAULT_ADDR < KERNELSPACE_BASE &&
	 * >>             FAULT_ADDR >= COMPAT_KERNELSPACE_BASE) {
	 * >>             struct mman *mm = THIS_MMAN;
	 * >>             mman_lock_acquire(mm);
	 * >>             if (!mnode_tree_rlocate(mm->mm_mappings, COMPAT_KERNELSPACE_BASE,
	 * >>                                     KERNELSPACE_BASE - COMPAT_KERNELSPACE_BASE)) {
	 * >>                 mman_mappings_removenode(mm, &FORMMAN(mm, thismman_kernel_reservation));
	 * >>                 // Extend the kern-reserve node to fill the
	 * >>                 // entire compat-mode kernel address space.
	 * >>                 FORMMAN(mm, thismman_kernel_reservation).mn_minaddr = COMPAT_KERNELSPACE_BASE;
	 * >>                 mman_mappings_insert(mm, &FORMMAN(mm, thismman_kernel_reservation));
	 * >>                 mman_lock_release(mm);
	 * >>                 goto try_lookup_node_at_accessed_address;
	 * >>             }
	 * >>             mman_lock_release(mm);
	 * >>         }
	 * >> #endif // ...
	 * >>     }
	 */
#if defined(__ARCH_HAVE_COMPAT) && !defined(CONFIG_NO_KERNEL_USERKERN_SEGMENT)
	if (FORMMAN(target, thismman_kernel_reservation).mn_part == &userkern_segment_part_compat) {
#ifdef KERNELSPACE_HIGHMEM
#if defined(COMPAT_KERNELSPACE_BASE) && COMPAT_KERNELSPACE_BASE != KERNELSPACE_BASE
		FORMMAN(target, thismman_kernel_reservation).mn_minaddr = (byte_t *)KERNELSPACE_BASE;
#endif /* COMPAT_KERNELSPACE_BASE && COMPAT_KERNELSPACE_BASE != KERNELSPACE_BASE */
#else /* KERNELSPACE_HIGHMEM */
#if defined(COMPAT_KERNELSPACE_END) && COMPAT_KERNELSPACE_END != KERNELSPACE_END
		FORMMAN(target, thismman_kernel_reservation).mn_maxaddr = (byte_t *)KERNELSPACE_END - 1;
#endif /* COMPAT_KERNELSPACE_END && COMPAT_KERNELSPACE_END != KERNELSPACE_END */
#endif /* !KERNELSPACE_HIGHMEM */
		FORMMAN(target, thismman_kernel_reservation).mn_part = &userkern_segment_part;
	}
#endif /* __ARCH_HAVE_COMPAT && !CONFIG_NO_KERNEL_USERKERN_SEGMENT */

	/* Step #8: Re-insert the kernel-reserve node into the new tree */
	mman_mappings_insert_and_verify(target, &FORMMAN(target, thismman_kernel_reservation));

	/* Step #9: Because the mem-builder wouldn't have received updates on
	 *          situations  where mem-parts could have been re-merged, we
	 *          must manually check for nodes that can be merged now that
	 *          all of them have been applied to the `target' mman! */
	mman_mergenodes_locked(target);

	/* And with  that, the  newly constructed  mem-node-tree has  been
	 * fully assigned  to the  given  target-mman. Assuming  that  our
	 * caller dutifully did their call to `pagedir_unmap_userspace()',
	 * any  future memory access  to a user-space  address made in the
	 * context  of  the `target'  mman will  walk  the new  node tree,
	 * where it  will  find  the correct  node/part,  thus  allow  for
	 * lazy initialization of the actually mapped locations. */
}




PRIVATE NONNULL((1)) void PRPC_EXEC_CALLBACK_CC
killthread_for_exec_rpc(struct rpc_context *__restrict ctx, void *UNUSED(cookie)) {
	/* TODO: Supposed to use `si_code == SI_DETHREAD' for this case! */
	if (ctx->rc_context != RPC_REASONCTX_SHUTDOWN)
		THROW(E_EXIT_THREAD, W_EXITCODE(0, 0));
}

/* Terminate all threads bound to `target', other than the calling
 * thread by sending an RPC that throws an E_EXIT_THREAD exception
 * to each of them.
 * For this  purpose, first  pre-allocate a  set of  RPC  descriptors
 * for  every  target  thread,  before  sending  them  all  at  once.
 * If  the allocation cannot  be done without  blocking, do the usual
 * unlock+return_false. Otherwise, when this function returns `true',
 * then you know that no thread  other than yourself is still  making
 * any use of the given `target' mman.
 *
 * NOTE: This function is used to implement `MBUILDER_APPLY_AA_TERMTHREADS'
 *
 * Locking logic:
 *   in:   mbuilder_partlocks_acquire(self) && mman_lock_acquired(target) && HELD(unlock)
 *   out:  return == true:
 *           - mbuilder_partlocks_release(self);
 *           - mman_lock_acquired(target) && HELD(unlock)
 *         return == false || EXCEPT:
 *           - mbuilder_partlocks_release(self);
 *           - mman_lock_release(target);
 *           - unlock(); */
PUBLIC NONNULL((1, 2)) bool KCALL
mbuilder_termthreads_or_unlock(struct mbuilder *__restrict self,
                               struct mman *__restrict target,
                               struct unlockinfo *unlock)
		THROWS(E_BADALLOC, E_WOULDBLOCK) {
	struct task *thread, *caller;
	struct pending_rpc **p_rpc_desc;

	/* Make sure that there are enough RPC descriptors
	 * in order to kill  all threads using this  mman.
	 *
	 * If  some are missing, then allocate more _before_
	 * doing anything, since once we start kill threads,
	 * we've already reached the point of no return! */
	caller     = THIS_TASK;
	p_rpc_desc = SLIST_PFIRST(&self->mb_killrpc);

	mman_threadslock_acquire(target);

	/* Allocate missing descriptors */
	LIST_FOREACH (thread, &target->mm_threads, t_mman_tasks) {
		struct pending_rpc *rpc;
		if (thread == caller)
			continue; /* Skip this one! */

		rpc = *p_rpc_desc;
		if (rpc == NULL) {
			/* Try to allocate another RPC descriptor w/o blocking. */
			rpc = pending_rpc_alloc_kern_nx(GFP_ATOMIC);
			if unlikely(!rpc) {
				mman_threadslock_release_b(target);
				mbuilder_partlocks_release(self);
				mman_lock_release(target);
				unlockinfo_xunlock(unlock);

				/* Re-try the allocation while blocking, and with exceptions enabled. */
				rpc = pending_rpc_alloc_kern(GFP_NORMAL);
				rpc->pr_link.sle_next = NULL;
				rpc->pr_flags         = RPC_CONTEXT_KERN;
				rpc->pr_kern.k_func   = &killthread_for_exec_rpc;
				*p_rpc_desc = rpc;

				/* We lost the locks, so we can't continue to enumerate threads */
				return false;
			}

			/* Set the next-link to NULL. */
			rpc->pr_link.sle_next = NULL;
			rpc->pr_flags         = RPC_CONTEXT_KERN;
			rpc->pr_kern.k_func   = &killthread_for_exec_rpc;
			*p_rpc_desc = rpc;
		}
		p_rpc_desc = SLIST_PNEXT(rpc, pr_link);
	}

	/* === Pointer of no return:
	 * Actually send out all of the RPCs to all of the target threads. */
	LIST_FOREACH (thread, &target->mm_threads, t_mman_tasks) {
		struct pending_rpc *rpc, *next;
		if (thread == caller)
			continue; /* Skip this one! */
		rpc = SLIST_FIRST(&self->mb_killrpc);
		assert(rpc);
		next = SLIST_NEXT(rpc, pr_link);
		COMPILER_BARRIER();
		/* Send the RPC to `thread' */
		if likely(task_rpc_schedule(thread, rpc))
			self->mb_killrpc.slh_first = next;
	}

	/* And with that, all target threads have been killed. */
	mman_threadslock_release(target);
	return true;
}



/* Apply memory mappings  mapped within `self'  into `target', overriding  all
 * already-existing mappings, while also perform a set of `additional_actions'
 * @param: additional_actions: Additional actions to be atomically performed
 *                             alongside  the  setting of  the  new mem-node
 *                             mappings (set of `MBUILDER_APPLY_AA_*') */
PUBLIC BLOCKING NONNULL((1, 2)) void KCALL
mbuilder_apply(/*inherit(on_success)*/ struct mbuilder *__restrict self,
               struct mman *__restrict target,
               unsigned int additional_actions,
               struct mexecinfo *execinfo)
		THROWS(E_BADALLOC, E_WOULDBLOCK, ...) {
again:
	mbuilder_partlocks_acquire(self);
	if (!mman_lock_tryacquire(target)) {
		mbuilder_partlocks_release(self);
		mman_lock_waitfor(target);
		goto again;
	}
	/* All required locks have been acquired! */

	if (additional_actions & MBUILDER_APPLY_AA_TERMTHREADS) {
		/* Terminate all other threads. */
		if (!mbuilder_termthreads_or_unlock(self, target, NULL))
			goto again;
	}
	/* === Point of no return */

	/* Delete all user-space mappings within the specified target mman.
	 * All of the newly created mappings  are simply going to be  bound
	 * lazily, as they get accessed.
	 * NOTE: Outside of SMP, or when `MBUILDER_APPLY_AA_TERMTHREADS' is given,
	 *       we can unmap user-space without having to do SMP TLB shoot-downs. */
#ifndef CONFIG_NO_SMP
	if (!(additional_actions & MBUILDER_APPLY_AA_TERMTHREADS)) {
		if (target == THIS_MMAN) {
			pagedir_unmap_userspace();
		} else {
			pagedir_unmap_userspace_p(target->mm_pagedir_p);
		}
	} else
#endif /* !CONFIG_NO_SMP */
	{
		if (target == THIS_MMAN) {
			pagedir_unmap_userspace_nosync();

			/* Because our thread is  supposed to continue running,  and
			 * because  user-space (presumably) contained stuff prior to
			 * the exec, we must still sync the user-space portion  (and
			 * also the page directory identity mapping, should that one
			 * exist on this arch).
			 *
			 * Otherwise, we'd be executing user-space with a messed-up
			 * TLB (since it may still contain entries relevant to  the
			 * old state of user-space)
			 *
			 * Since we're only talking user-space here, it's enough  to
			 * sync _it_ alone (as opposed to doing `pagedir_syncall()') */
			pagedir_syncall_user();
		} else {
			pagedir_unmap_userspace_nosync_p(target->mm_pagedir_p);
		}
	}

	/* Do the actual job of applying the new node-tree, as
	 * well as clearing the  mman's page directory of  all
	 * remaining user-space mappings. */
	mbuilder_apply_impl(self, target);

	/* If requested to, also fill in new exec information, overwriting the old. */
	if (additional_actions & MBUILDER_APPLY_AA_SETEXECINFO) {
		struct mexecinfo oldinfo;
		memcpy(&oldinfo, &FORMMAN(target, thismman_execinfo), sizeof(struct mexecinfo));
		if (execinfo) {
			memcpy(&FORMMAN(target, thismman_execinfo), execinfo, sizeof(struct mexecinfo));
			xincref(execinfo->mei_file);
			xincref(execinfo->mei_dent);
			xincref(execinfo->mei_path);
		} else {
			bzero(&FORMMAN(target, thismman_execinfo), sizeof(struct mexecinfo));
		}

		/* Done! (but must still release our lock to `target') */
		mman_lock_release(target);

		/* Drop  references _after_ releasing the mman lock,
		 * thus improving efficiency by keeping the lock for
		 * a smaller period of time. */
		xdecref(oldinfo.mei_file);
		xdecref(oldinfo.mei_dent);
		xdecref(oldinfo.mei_path);
	} else {
		mman_lock_release(target);
	}
}


DECL_END

#endif /* !GUARD_KERNEL_SRC_MEMORY_MBUILDER_APPLY_C */
