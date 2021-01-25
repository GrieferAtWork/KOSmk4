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
#ifndef GUARD_KERNEL_SRC_MEMORY_VM_BUILDER_C
#define GUARD_KERNEL_SRC_MEMORY_VM_BUILDER_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <fs/node.h>
#include <fs/vfs.h>
#include <kernel/except.h>
#include <kernel/printk.h>
#include <kernel/vm.h>
#include <kernel/vm/builder.h>
#include <kernel/vm/exec.h>
#include <sched/rpc-internal.h>
#include <sched/rpc.h>
#include <sched/userkern.h>

#include <hybrid/atomic.h>
#include <hybrid/overflow.h>

#include <compat/config.h>
#include <sys/wait.h>

#include <assert.h>
#include <inttypes.h>
#include <string.h>

#include "vm-nodeapi.h"

#define POINTER_SET_BUFSIZE 16
#include <misc/pointer-set.h>

DECL_BEGIN

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL vmb_delete_node)(struct vm_node *__restrict node) {
	xdecref(node->vn_fsname);
	xdecref(node->vn_fspath);
	decref(node->vn_block);
	/* Drop references held by the node. */
	vm_datapart_decref_and_merge(node->vn_part);
	/* Delete the VM Node */
	vm_node_free(node);
}


/* Finalize a given VM Builder.
 * NOTE: This function may not be called after a successful call to `vmb_apply()'!
 * >> struct vmb v;
 * >> vmb_init(&v);
 * >> TRY {
 * >>     // Create mappings
 * >>     vmb_paged_map(&v,...);
 * >>     ...
 * >>
 * >>     // Apply mappings
 * >>     vmb_apply(&v,...);
 * >> } EXCEPT {
 * >>     vmb_fini(&v);
 * >>     RETHROW();
 * >> }
 * >> // Don't finalize `v' after `vmb_apply()' has succeeded
 */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(KCALL vmb_fini)(struct vmb *__restrict self) {
	struct vm_node *iter, *next;
	iter = self->v_byaddr;
	while (iter) {
		next = iter->vn_byaddr.ln_next;
		/* Delete the node */
		vmb_delete_node(iter);
		iter = next;
	}
#ifndef NDEBUG
	memset(self, 0xcc, sizeof(*self));
#endif /* !NDEBUG */
}


PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL vmb_do_delete_whole_nodes)(struct vmb *__restrict self,
                                         pageid_t minpage,
                                         pageid_t maxpage) {
	struct vm_node *node;
	/* Remove all nodes within the given range. */
	for (;;) {
		node = vm_nodetree_rremove(&self->v_tree,
		                           minpage,
		                           maxpage);
		if (!node)
			break;
		/* Unlink the node */
		LLIST_REMOVE(node, vn_byaddr);
		/* Delete the node */
		vmb_delete_node(node);
	}
}

PRIVATE NONNULL((1, 4)) void KCALL
vmb_do_mapat(struct vmb *__restrict self,
             pageid_t page_index, size_t num_pages,
             struct vm_datablock *__restrict data,
             struct path *fspath,
             struct directory_entry *fsname,
             pageid64_t data_start_vpage,
             uintptr_half_t prot,
             uintptr_half_t flag,
             uintptr_t guard)
		THROWS(E_WOULDBLOCK, E_BADALLOC) {
	struct vm_node *node;
	size_t num_vpages;
	REF struct vm_datapart *part;
	pageid_t initial_page_index;
	assert(!(flag & (VM_NODE_FLAG_COREPRT | VM_NODE_FLAG_KERNPRT | VM_NODE_FLAG_HINTED)));
	assert(!(prot & ~(VM_PROT_EXEC | VM_PROT_WRITE | VM_PROT_READ | VM_PROT_LOOSE | VM_PROT_SHARED)));
	if unlikely(!num_pages)
		return;
	initial_page_index = page_index;
	assert(page_index + num_pages > page_index);
	assert(!PAGEIDRANGE_ISKERN_PARTIAL(page_index, page_index + num_pages - 1));
	assert(!vmb_paged_isused(self, page_index, page_index + num_pages - 1));
again:
	TRY {
		node = (struct vm_node *)kmalloc(sizeof(struct vm_node),
		                                 GFP_LOCKED | GFP_PREFLT);
		TRY {
			part = vm_paged_datablock_locatepart_exact(data,
			                                           data_start_vpage,
			                                           num_pages);
		} EXCEPT {
			kfree(node);
			RETHROW();
		}
	} EXCEPT {
		assert(page_index >= initial_page_index);
		/* Delete any mappings that had already been made. */
		if (page_index > initial_page_index) {
			vmb_do_delete_whole_nodes(self,
			                          initial_page_index,
			                          page_index - 1);
		}
		RETHROW();
	}
	/* Weakly read out how may pages we've managed to load with this part.
	 * Any reduction of this amount after this point will be handled once
	 * the VMB gets applied (s.a. `vmb_apply()') */
	num_vpages = vm_datapart_numvpages_atomic(part);
	assertf(num_vpages != 0,
	        "part                      = %p\n"
	        "part->dp_tree.a_vmin      = %" PRIp64 "\n"
	        "part->dp_tree.a_vmax      = %" PRIp64 "\n"
	        "vm_datapart_minbyte(part) = %" PRIp64 "\n"
	        "vm_datapart_maxbyte(part) = %" PRIp64 "\n"
	        "VM_DATABLOCK_PAGESHIFT(.) = %u\n"
	        "VM_DATABLOCK_ADDRSHIFT(.) = %u\n"
	        "VM_DATABLOCK_PAGEALIGN(.) = %" PRIuSIZ "\n"
	        "VM_DATABLOCK_PAGEMASK(.)  = %" PRIuSIZ "\n"
	        "VM_DATABLOCK_PAGESIZE(.)  = %" PRIuSIZ,
	        (uintptr_t)part,
	        (u64)part->dp_tree.a_vmin,
	        (u64)part->dp_tree.a_vmax,
	        (u64)vm_datapart_minbyte(part),
	        (u64)vm_datapart_maxbyte(part),
	        VM_DATABLOCK_PAGESHIFT(part->dp_block),
	        VM_DATABLOCK_ADDRSHIFT(part->dp_block),
	        VM_DATABLOCK_PAGEALIGN(part->dp_block),
	        VM_DATABLOCK_PAGEMASK(part->dp_block),
	        VM_DATABLOCK_PAGESIZE(part->dp_block));
	assert(num_vpages <= num_pages);

	/* Initialize the new VM Node */
	node->vn_part        = part;
	node->vn_block       = incref(data);
	node->vn_fspath      = xincref(fspath);
	node->vn_fsname      = xincref(fsname);
	node->vn_node.a_vmin = page_index;
	node->vn_node.a_vmax = page_index + num_vpages - 1;
	node->vn_prot        = prot;
	node->vn_flags       = VM_NODE_FLAG_NORMAL;
	node->vn_guard       = 0;

	/* Apply a guard. */
	if (guard) {
		if (num_vpages >= num_pages) {
			/* Last node. - Always apply the given guard! */
			node->vn_flags |= flag & VM_NODE_FLAG_GROWSUP;
			node->vn_guard = guard;
		} else if (!(flag & VM_NODE_FLAG_GROWSUP)) {
			/* Must apply the guard to the first node. */
			node->vn_guard = guard;
			guard          = 0;
		} else {
			/* Must apply the guard to the last node (done in a later pass) */
		}
	}
	/* Insert the node into the VMB */
	vmb_node_insert(self, node);
	/* Check if we need to map more nodes. */
	if (num_vpages < num_pages) {
		/* Need to map more! */
		data_start_vpage += num_vpages;
		page_index += num_vpages;
		num_pages -= num_vpages;
		goto again;
	}
}


/* Map the memory region into the given VM Builder.
 * @param: prot:   Set of `VM_PROT_*'.
 * @param: flag:   Set of `VM_NODE_FLAG_*'.
 * @param: data_start_vpage: The memory page index where mapping of `data' starts.
 * @param: guard:  If non-zero, repetition limit for a guard mapping.
 *                 Set to 0 if the mapping should include a guard.
 * @return: true:  Successfully created the mapping.
 * @return: false: Another mapping already exists. */
PUBLIC WUNUSED NONNULL((1, 4)) bool KCALL
vmb_paged_mapat(struct vmb *__restrict self,
                pageid_t page_index, size_t num_pages,
                struct vm_datablock *__restrict data,
                struct path *fspath,
                struct directory_entry *fsname,
                pageid64_t data_start_vpage,
                uintptr_half_t prot,
                uintptr_half_t flag,
                uintptr_t guard)
		THROWS(E_WOULDBLOCK, E_BADALLOC) {
	pageid_t endpage;
	/* Use an overflow-addition, so we can indicate failure if the
	 * mapping range overflows (in which case we must indicate failure) */
	if unlikely(OVERFLOW_UADD(page_index, num_pages, &endpage))
		goto err;
	/* Check if some portion the given page-range is apart of kernel-space. */
	if unlikely(PAGEIDRANGE_ISKERN_PARTIAL(page_index, endpage - 1))
		return num_pages == 0;
	/* Check if some portion of the given page-range is already in use. */
	if unlikely(vmb_paged_isused(self, page_index, endpage - 1))
		goto err;
	/* With those validation out of the way, move on to actually create the mapping! */
	vmb_do_mapat(self,
	             page_index,
	             num_pages,
	             data,
	             fspath,
	             fsname,
	             data_start_vpage,
	             prot,
	             flag,
	             guard);
	return true;
err:
	return false;
}


/* Find the first node with `vm_node_getminpageid(return) >= min_page_index'
 * If no such node exists, return `NULL' instead. */
PUBLIC NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) struct vm_node *
NOTHROW(KCALL vmb_find_first_node_greater_equal)(struct vmb const *__restrict self,
                                                 pageid_t min_page_index) {
	struct vm_node *result;
	for (result = self->v_byaddr; result;
	     result = result->vn_byaddr.ln_next) {
		if (vm_node_getminpageid(result) >= min_page_index)
			break;
	}
	return result;
}

/* Find the last node with `vm_node_getmaxpageid(return) <= max_page_index'
 * If no such node exists, return `NULL' instead. */
PUBLIC NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) struct vm_node *
NOTHROW(KCALL vmb_find_last_node_lower_equal)(struct vmb const *__restrict self,
                                              pageid_t max_page_index) {
	struct vm_node *result = NULL;
	struct vm_node *iter;
	for (iter = self->v_byaddr; iter;
	     iter = iter->vn_byaddr.ln_next) {
		if (vm_node_getmaxpageid(iter) <= max_page_index)
			result = iter;
		else {
			break;
		}
	}
	return result;
}


#ifndef __INTELLISENSE__
DECL_END

#define VM_GETFREE_VMB 1
#include "vm-getfree-impl.c.inl"

DECL_BEGIN
#endif /* !__INTELLISENSE__ */

/* A combination of `vmb_paged_getfree' + `vmb_paged_mapat'
 * @throw: E_BADALLOC_INSUFFICIENT_VIRTUAL_MEMORY: Failed to find suitable target. */
PUBLIC WUNUSED NONNULL((1, 6)) pageid_t KCALL
vmb_paged_map(struct vmb *__restrict self,
              pageid_t hint,
              size_t num_pages,
              size_t min_alignment_in_pages,
              unsigned int getfree_mode,
              struct vm_datablock *__restrict data,
              struct path *fspath,
              struct directory_entry *fsname,
              pageid64_t data_start_vpage,
              uintptr_half_t prot,
              uintptr_half_t flag,
              uintptr_t guard)
		THROWS(E_WOULDBLOCK, E_BADALLOC) {
	pageid_t result;
	result = vmb_paged_getfree(self,
	                     hint,
	                     num_pages,
	                     min_alignment_in_pages,
	                     getfree_mode);
	if unlikely(result == VM_PAGED_GETFREE_ERROR)
		THROW(E_BADALLOC_INSUFFICIENT_VIRTUAL_MEMORY, num_pages * PAGESIZE);
	vmb_do_mapat(self,
	             result,
	             num_pages,
	             data,
	             fspath,
	             fsname,
	             data_start_vpage,
	             prot,
	             flag,
	             guard);
	return result;
}


/* Insert the given node into the specified VM Builder */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(KCALL vmb_node_insert)(struct vmb *__restrict self,
                               struct vm_node *__restrict node) {
	struct vm_node **pinsert, *insert_before;
	assertf(vm_node_getminpageid(node) <= vm_node_getmaxpageid(node),
	        "Unordered node: MIN(%p) >= MAX(%p)",
	        vm_node_getminaddr(node), vm_node_getmaxaddr(node));
	assertf(vm_node_getmaxpageid(node) <= __ARCH_PAGEID_MAX,
	        "Mapping of node covering pages %p...%p is out-of-bounds",
	        vm_node_getminpageid(node), vm_node_getmaxpageid(node));
	assert(node->vn_block != NULL);
	assert(node->vn_part != NULL);
	assert((self->v_tree != NULL) == (self->v_byaddr != NULL));
#ifndef NDEBUG
	/* Fill undefined fields with consistent invalid data in NDEBUG-mode */
	memset(&node->vn_vm, 0xcc, sizeof(node->vn_vm));
	memset(&node->vn_link, 0xcc, sizeof(node->vn_link));
#endif /* !NDEBUG */
	vm_nodetree_insert(&self->v_tree, node);
	/* Figure out where we need to insert the node. */
	pinsert = &self->v_byaddr;
	while ((insert_before = *pinsert) != NULL &&
	       (insert_before->vn_node.a_vmax < node->vn_node.a_vmin))
		pinsert = &insert_before->vn_byaddr.ln_next;
	assertf(!insert_before ||
	        node->vn_node.a_vmax < insert_before->vn_node.a_vmin,
	        "insert_before  = %p:%p...%p\n"
	        "node           = %p:%p...%p\n"
	        "node->vn_flags = %#x\n",
	        insert_before,
	        vm_node_getminaddr(insert_before),
	        vm_node_getmaxaddr(insert_before),
	        node,
	        vm_node_getminaddr(node),
	        vm_node_getmaxaddr(node),
	        (unsigned int)node->vn_flags);
	/* Insert the node before `insert' at `pinsert' */
	node->vn_byaddr.ln_pself = pinsert;
	node->vn_byaddr.ln_next  = insert_before;
	if (insert_before)
		insert_before->vn_byaddr.ln_pself = &node->vn_byaddr.ln_next;
	*pinsert = node;
}

/* Remove a given node from the specified VM Builder. */
PUBLIC NOBLOCK NONNULL((1)) struct vm_node *
NOTHROW(KCALL vmb_node_remove)(struct vmb *__restrict self,
                               pageid_t page) {
	struct vm_node *result;
	result = vm_nodetree_remove(&self->v_tree, page);
	if likely(result)
		LLIST_REMOVE(result, vn_byaddr);
	return result;
}

/* Get the node associated with the given `page' */
PUBLIC NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) struct vm_node *
NOTHROW(FCALL vmb_getnodeofpageid)(struct vmb const *__restrict self, pageid_t page) {
	return vm_nodetree_locate(self->v_tree,
	                          page);
}

/* Check if some part of the given address range is currently in use. */
PUBLIC NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) bool
NOTHROW(FCALL vmb_paged_isused)(struct vmb const *__restrict self,
                                pageid_t min_page,
                                pageid_t max_page) {
	return vm_nodetree_rlocate(self->v_tree,
	                           min_page,
	                           max_page) != NULL;
}


PRIVATE NOBLOCK NONNULL((1)) void KCALL
pointer_set_unlock_vm_dataparts(struct pointer_set *__restrict self) {
	struct vm_datapart *part;
	POINTER_SET_FOREACH(part, self) {
		sync_endwrite(part);
	}
}

PRIVATE NOBLOCK NONNULL((1, 2)) void KCALL
pointer_set_unlock_vm_dataparts_except(struct pointer_set *__restrict self,
                                       struct vm_datapart *__restrict not_this_one) {
	struct vm_datapart *part;
	POINTER_SET_FOREACH(part, self) {
		if (part != not_this_one)
			sync_endwrite(part);
	}
}

PRIVATE NOBLOCK NONNULL((1)) void KCALL
pointer_set_unlock_vm_dataparts_and_clear(struct pointer_set *__restrict self) {
	pointer_set_unlock_vm_dataparts(self);
	pointer_set_clear(self);
}

PRIVATE NOBLOCK NONNULL((1, 2)) void KCALL
pointer_set_unlock_vm_dataparts_and_clear_except(struct pointer_set *__restrict self,
                                                 struct vm_datapart *__restrict not_this_one) {
	pointer_set_unlock_vm_dataparts_except(self, not_this_one);
	pointer_set_clear(self);
}

PRIVATE NOBLOCK NONNULL((1)) void KCALL
rpc_free_chain(struct rpc_entry *self) {
	struct rpc_entry *next;
	while (self) {
		next = self->re_next;
		task_free_rpc(self);
		self = next;
	}
}

PRIVATE NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) size_t KCALL
rpc_count_chain(struct rpc_entry const *self) {
	size_t result;
	for (result = 0; self; self = self->re_next)
		++result;
	return result;
}

PRIVATE WUNUSED NONNULL((2)) struct icpustate *FCALL
vmb_apply_terminate_thread(void *UNUSED(arg),
                           struct icpustate *__restrict state,
                           unsigned int reason,
                           struct rpc_syscall_info const *UNUSED(sc_info)) {
	if (reason != TASK_RPC_REASON_SHUTDOWN)
		THROW(E_EXIT_THREAD, W_EXITCODE(0, 0));
	return state;
}


/* Apply all of the mappings from `self' onto `target', whilst simultaneously deleting
 * any memory mapping still present within `target' (except for the kernel-reserve node)
 * This function is guarantied to operate atomically in a way that allows the caller
 * to assume that no memory mappings (or anything else for that matter) changes if the
 * function fails and returns by throwing an error, and that everything happens exactly
 * as intended if it returns normally.
 * @param: self:   The VM Builder object from which to take mappings to-be applied to `target'
 *                 Upon success, the contents of `self' are left undefined and must either be
 *                 re-initialized, or not be attempted to be finalized.
 * @param: target: The target VM to which to apply the new memory mappings.
 *                 Upon success, this VM will only contain the mappings from `self', with all
 *                 of its old mappings having been deleted.
 *                 NOTE: This argument must not be the kernel VM
 * @param: additional_actions: Additional actions to be atomically performed alongside
 *                 the application of the new memory mappings (set of `VMB_APPLY_AA_*') */
PUBLIC NONNULL((1, 2)) void KCALL
vmb_apply(struct vmb *__restrict self,
          struct vm *__restrict target,
          unsigned int additional_actions,
          struct vm_execinfo_struct *execinfo)
		THROWS(E_BADALLOC, E_WOULDBLOCK) {
	struct vm_node *node;
	struct pointer_set locked_parts;
	struct vm_execinfo_struct old_execinfo;
	struct rpc_entry *task_terminate_rpcs = NULL;
	assert(target != &vm_kernel);
	memset(&old_execinfo, 0, sizeof(old_execinfo));

	/* Step #1: Acquire write-lock to all mapped data-parts.
	 * NOTE:    This part's kind-of complicated, since we need to make sure
	 *          that we don't try to lock any given part more than once, as
	 *          a single part may have been mapped multiple times.
	 *         (The lock of vm_datapart objects is non-recursive, we'd
	 *          deadlock if we we'd just mindlessly lock all off them).
	 *       -> To solve this problem, we keep a set of all parts that we've
	 *          already acquired locks for.
	 */
	pointer_set_init(&locked_parts);
again_lock_parts:
	for (node = self->v_byaddr; node;
	     node = node->vn_byaddr.ln_next) {
		int error;
		/* Insert the new part into our set (thus also determining
		 * if the part's already been locked before) */
		error = pointer_set_insert_nx(&locked_parts,
		                              node->vn_part,
		                              GFP_ATOMIC);
		if unlikely(error == POINTER_SET_INSERT_NX_FAILED) {
			size_t min_parts;
			/* Failed to re-hash the pointer set.
			 * -> Unlock all already locked parts and re-hash the set while blocking. */
			pointer_set_unlock_vm_dataparts(&locked_parts);
			min_parts = locked_parts.ps_size;
			for (; node; node = node->vn_byaddr.ln_next)
				++min_parts;
			/* NOTE: `pointer_set_clear_and_rehash()' automatically clears the part-set,
			 *        as well as frees the old hash-vector in case of an allocation
			 *        failure. */
			pointer_set_clear_and_rehash(&locked_parts,
			                             min_parts,
			                             GFP_NORMAL);
			goto again_lock_parts;
		}
		if (error != POINTER_SET_INSERT_NX_EXISTS) {
			/* This one's a new data part. -> Must lock it the first time around! */
			if (!sync_trywrite(node->vn_part)) {
				/* Failed to acquire a lock. -> Unlock all already locked parts, and
				 * acquire a blocking lock to this one. Then, try again. */
				pointer_set_unlock_vm_dataparts_and_clear_except(&locked_parts,
				                                                 node->vn_part);
				TRY {
					sync_write(node->vn_part);
				} EXCEPT {
					pointer_set_fini(&locked_parts);
					rpc_free_chain(task_terminate_rpcs);
					RETHROW();
				}
				sync_endwrite(node->vn_part);
				goto again_lock_parts;
			}
		}
		/* Successfully acquired a lock to this part.
		 * Now we must check if the part has been split since it was originally mapped
		 * into the VMB. - If it has, we must create more mappings to accommodate for
		 * the portions that had been lost in the mean time.
		 * NOTE: Then only way to prevent a data part from being split is to be the one
		 *       holding a read- or write-lock to it (which we are at this point) */
		{
			size_t part_vpages;
			part_vpages = vm_datapart_numvpages(node->vn_part);
			assertf(part_vpages <= vm_node_getpagecount(node),
			        "part_vpages                = %" PRIuSIZ "\n"
			        "vm_node_getpagecount(node) = %" PRIuSIZ "\n",
			        part_vpages, vm_node_getpagecount(node));
			if unlikely(part_vpages < vm_node_getpagecount(node)) {
				/* Must create an additional node in order to map the missing portion.
				 * Note however that since there isn't a non-blocking `vm_datablock_locatepart_nx()'
				 * function, we must always do this while not holding locks to any of the aforementioned
				 * parts. This, however, isn't a problem since a part can only ever be split down to a
				 * 1-page granularity, meaning that at one point we're guarantied to no longer have to
				 * keep on splitting parts, since they can no longer be split at all! */
				REF struct vm_datablock *part_block;
				size_t num_missing_vpages;
				pageid64_t off_missing_vpages;

				/* NOTE: Use the BLOCK-pointer of the part itself, rather than the BLOCK-pointer of our
				 *       associated node, just in case the part has since been unshared, in which case
				 *       we don't want to re-introduce the shared mappings after the data-block had been
				 *       explicitly unshared.
				 * HINT: If the block was unshared, `dp_block' will have been set to
				 *       one of the `vm_datablock_anonymous_zero_vec[*]' descriptors. */
				part_block         = incref(node->vn_part->dp_block);
				num_missing_vpages = vm_node_getpagecount(node) - part_vpages;
				off_missing_vpages = vm_datapart_startvpage(node->vn_part) + part_vpages;

				/* Release all previously held locks (including the one for `node->vn_part') */
				COMPILER_READ_BARRIER();
				pointer_set_unlock_vm_dataparts_and_clear(&locked_parts);
				FINALLY_DECREF_UNLIKELY(part_block);
#ifndef NDEBUG
				{
					struct vm_node *n;
					n = vm_nodetree_remove(&self->v_tree, node->vn_node.a_vmin);
					assertf(n == node,
					        "n    = %p\n"
					        "node = %p\n",
					        n, node);
				}
#else /* !NDEBUG */
				vm_nodetree_remove(&self->v_tree, node->vn_node.a_vmin);
#endif /* NDEBUG */
				/* Update the already mapped node. */
				node->vn_node.a_vmax -= num_missing_vpages;
				{
					uintptr_t node_guard      = 0;
					uintptr_half_t node_flags = VM_NODE_FLAG_NORMAL;
					if (node->vn_guard && (node->vn_flags & VM_NODE_FLAG_GROWSUP)) {
						/* Inherit guard characteristics of the original node. */
						node_guard     = node->vn_guard;
						node_flags     = VM_NODE_FLAG_GROWSUP;
						node->vn_guard = 0;
						node->vn_flags &= ~VM_NODE_FLAG_GROWSUP;
					}
					/* Re-insert the node (NOTE: No need to update the by-addr list, since
					 * the node's order in relation to other nodes didn't get changed at
					 * any point during this) */
					vm_nodetree_insert(&self->v_tree, node);
					/* Map the missing upper portion of the node. */
					TRY {
						vmb_do_mapat(self,
						             node->vn_node.a_vmax + 1,
						             num_missing_vpages,
						             part_block,
						             node->vn_fspath,
						             node->vn_fsname,
						             off_missing_vpages,
						             node->vn_prot,
						             node_guard,
						             node_flags);
					} EXCEPT {
						/* Restore the split nodes original memory range. */
#ifndef NDEBUG
						{
							struct vm_node *n;
							n = vm_nodetree_remove(&self->v_tree, node->vn_node.a_vmin);
							assertf(n == node,
							        "n    = %p\n"
							        "node = %p\n",
							        n, node);
						}
#else /* !NDEBUG */
						vm_nodetree_remove(&self->v_tree, node->vn_node.a_vmin);
#endif /* NDEBUG */
						node->vn_node.a_vmax += num_missing_vpages;
						node->vn_guard = node_guard;
						node->vn_flags |= node_flags;
						vm_nodetree_insert(&self->v_tree, node);
						RETHROW();
					}
				}
				goto again_lock_parts;
			}
		}
		/* Check if we need to update write permissions for existing mappings. */
		if (!(node->vn_prot & VM_PROT_SHARED)) {
			unsigned int update_write_error;
			struct vm_datapart *part = node->vn_part;
			REF struct vm *blocking_vm;
			assert(part);
			if (part->dp_crefs == NULL) {
				struct vm_node *iter;
				/* The addition of the first copy-on-write mapping requires
				 * that all existing SHARED memory mappings be updated to
				 * not include write permissions in their page directories.
				 * That way, a #PF will be triggered which will then unshare
				 * our own data part, preventing writes to the shared mapping
				 * from leaking into private mappings. */
				for (iter = part->dp_srefs; iter;
				     iter = iter->vn_link.ln_next) {
					update_write_error = vm_node_update_write_access(iter);
					if unlikely(update_write_error != VM_NODE_UPDATE_WRITE_ACCESS_SUCCESS) {
						blocking_vm = iter->vn_vm;
						goto handle_remove_write_error;
					}
				}
			} else if (part->dp_crefs->vn_link.ln_next == NULL &&
			           /* If this is the second copy-on-write mapping of an anonymous data part,
			           * then the first one may have had write permissions which must now be
			           * unshared (this is the case for general purpose RAM during fork()) */
			           ATOMIC_READ(part->dp_block->db_parts) == VM_DATABLOCK_ANONPARTS) {
				update_write_error = vm_node_update_write_access(part->dp_crefs);
				if unlikely(update_write_error != VM_NODE_UPDATE_WRITE_ACCESS_SUCCESS) {
					blocking_vm = part->dp_crefs->vn_vm;
handle_remove_write_error:
					if (update_write_error == VM_NODE_UPDATE_WRITE_ACCESS_BADALLOC) {
						pointer_set_unlock_vm_dataparts(&locked_parts);
						pointer_set_fini(&locked_parts);
						rpc_free_chain(task_terminate_rpcs);
						THROW(E_BADALLOC_INSUFFICIENT_PHYSICAL_MEMORY, PAGESIZE);
					}
					if (!tryincref(blocking_vm))
						blocking_vm = NULL;
					pointer_set_unlock_vm_dataparts_and_clear(&locked_parts);
					assert(update_write_error == VM_NODE_UPDATE_WRITE_ACCESS_WOULDBLOCK);
					if (blocking_vm) {
						FINALLY_DECREF_UNLIKELY(blocking_vm);
						TRY {
							sync_write(blocking_vm);
							sync_endwrite(blocking_vm);
						} EXCEPT {
							pointer_set_fini(&locked_parts);
							rpc_free_chain(task_terminate_rpcs);
							RETHROW();
						}
					}
					goto again_lock_parts;
				}
			}
		}
	} /* FOREACH(node: self) */

	/* At this point we have locks to all unique parts of the given `vmb'
	 * Now it's time to mode on to acquiring a lock to the given target VM,
	 * as well as see if we need to terminate all of the threads that are
	 * using it. (besides ourself) */

	/* Start out this part by locking the target VM normally
	 * (so we gain the rights to start modifying its contents) */
	if (!sync_trywrite(target)) {
		/* Block until we can acquire a write-lock to the target VM, then start over */
		pointer_set_unlock_vm_dataparts_and_clear(&locked_parts);
		TRY {
			sync_write(target);
		} EXCEPT {
			pointer_set_fini(&locked_parts);
			rpc_free_chain(task_terminate_rpcs);
			RETHROW();
		}
		sync_endwrite(target);
		goto again_lock_parts;
	}

	/* Always acquire a lock to the tasklist of the target VM, since we
	 * also need that lock for when we'll be syncing it further below. */
	if (!vm_tasklock_trywrite(target)) {
		sync_endwrite(target);
		pointer_set_unlock_vm_dataparts_and_clear(&locked_parts);
		TRY {
			vm_tasklock_write(target);
		} EXCEPT {
			pointer_set_fini(&locked_parts);
			rpc_free_chain(task_terminate_rpcs);
			RETHROW();
		}
		vm_tasklock_endwrite(target);
		goto again_lock_parts;
	}
	if (additional_actions & VMB_APPLY_AA_TERMTHREADS) {
		struct task *thread;
		/* At this point, we're holding each and every one of the required locks!
		 * Now it's time to get to meat (which in this case means that we need to
		 * start allocating a sufficient number of synchronous RPC descriptors,
		 * so we can terminate all of the threads) */
		{
			size_t alloc_count;
			size_t thread_count = 0;
			alloc_count = rpc_count_chain(task_terminate_rpcs);
			LIST_FOREACH (thread, &target->v_tasks, t_mman_tasks) {
				if (!(ATOMIC_READ(thread->t_flags) &
				      (TASK_FTERMINATING | TASK_FTERMINATED)) &&
				    thread != THIS_TASK)
					++thread_count;
			}
			/* Check if we need to allocate more RPC descriptors. */
			if (thread_count > alloc_count) {
				do {
					struct rpc_entry *rpc;
					rpc = task_alloc_user_rpc_nx(&vmb_apply_terminate_thread,
					                             NULL,
					                             TASK_RPC_FNORMAL,
					                             GFP_ATOMIC);
					if unlikely(!rpc) {
						/* Must allocate the remaining RPCs whilst blocking. */
						vm_tasklock_endwrite(target);
						sync_endwrite(target);
						pointer_set_unlock_vm_dataparts_and_clear(&locked_parts);
						do {
							TRY {
								rpc = task_alloc_user_rpc(&vmb_apply_terminate_thread,
								                          NULL,
								                          TASK_RPC_FNORMAL,
								                          GFP_NORMAL);
							} EXCEPT {
								rpc_free_chain(task_terminate_rpcs);
								pointer_set_fini(&locked_parts);
								RETHROW();
							}
							rpc->re_next        = task_terminate_rpcs;
							task_terminate_rpcs = rpc;
							++alloc_count;
						} while (thread_count > alloc_count);
						goto again_lock_parts;
					}
					rpc->re_next        = task_terminate_rpcs;
					task_terminate_rpcs = rpc;
					++alloc_count;
				} while (thread_count > alloc_count);
			}
		}

		/* At this point we've got everything we need, so now it's time to start
		 * delivering RPCs to all of the affected threads, thus terminating them.
		 * |----- Point of no return */
		LIST_FOREACH (thread, &target->v_tasks, t_mman_tasks) {
			struct rpc_entry *next;
			int error;
			if (ATOMIC_READ(thread->t_flags) & (TASK_FTERMINATING | TASK_FTERMINATED))
				continue;
			if (thread == THIS_TASK)
				continue;
			assert(task_terminate_rpcs);
			next = task_terminate_rpcs->re_next;
			COMPILER_READ_BARRIER();
			error = task_deliver_rpc(thread,
			                         task_terminate_rpcs,
			                         /* Wait for IPI: If the thread is hosted by a different CPU, we need to wait
			                          *               for that CPU to acknowledge the IPI before we can commence.
			                          *               Otherwise, we end up with a race condition where some other
			                          *               CPU is still hosting threads that are actively running within
			                          *               our VM, simply because their CPU hasn't gotten the memo about
			                          *               their termination request.
			                          * NOTE: This only has an affect in SMP when `thread' is running on a different
			                          *       core than the caller, where it is currently the thread with the active
			                          *       quantum, spending its time in user-space. */
			                         TASK_RPC_FWAITFOR);
			/* If the delivery was successfully (it might fail if `thread' had already been terminated before
			 * we managed to get here), deal with the fact that `task_deliver_rpc()' will have consumed the RPC
			 * descriptor.
			 * Also: If there are any kernel-threads that are using `target', `task_deliver_rpc()' will have
			 *       failed as well, though this isn't something that should normally happen... */
			if (TASK_DELIVER_RPC_WASOK(error))
				task_terminate_rpcs = next;
		}
		/* Free any unused RPCs (though in general, there probably won't be any left) */
		rpc_free_chain(task_terminate_rpcs);
		/* At this point all threads using `target' have been instructed to terminate, and are
		 * guarantied to no longer be executing user-space code on any potential secondary CPU
		 * core.
		 * With that in mind, we're succeeded and can now move on applying the new VM contents. */
	}
	/* Set the given execinfo if the caller wants us to do so. */
	if (additional_actions & VMB_APPLY_AA_SETEXECINFO) {
		memcpy(&old_execinfo, &FORVM(target, thisvm_execinfo), sizeof(struct vm_execinfo_struct));
		memcpy(&FORVM(target, thisvm_execinfo), execinfo, sizeof(struct vm_execinfo_struct));
		xincref(execinfo->ei_node);
		xincref(execinfo->ei_dent);
		xincref(execinfo->ei_path);
	}

	{
		struct vm_node *old_node_list;
		/* Unlink the kernel-reserve node. */
#ifndef NDEBUG
#ifdef KERNELSPACE_HIGHMEM
		node = vm_nodetree_remove(&target->v_tree, PAGEID_ENCODE(KERNELSPACE_BASE));
#else /* KERNELSPACE_HIGHMEM */
		node = vm_nodetree_remove(&target->v_tree, 0);
#endif /* !KERNELSPACE_HIGHMEM */
		assertf(node == &target->v_kernreserve,
		        "node                   = %p\n"
		        "&target->v_kernreserve = %p\n",
		        node, &target->v_kernreserve);
#else /* !NDEBUG */
#ifdef KERNELSPACE_HIGHMEM
		vm_nodetree_remove(&target->v_tree, PAGEID_ENCODE(KERNELSPACE_BASE));
#else /* KERNELSPACE_HIGHMEM */
		vm_nodetree_remove(&target->v_tree, 0);
#endif /* !KERNELSPACE_HIGHMEM */
#endif /* NDEBUG */
		LLIST_REMOVE(&target->v_kernreserve, vn_byaddr);

		/* Assign the new node tree */
		old_node_list = target->v_byaddr;
		assert(!old_node_list || old_node_list->vn_byaddr.ln_pself == &target->v_byaddr);
		target->v_tree   = self->v_tree;
		target->v_byaddr = node = self->v_byaddr;
		if (node) {
			node->vn_byaddr.ln_pself = &target->v_byaddr;
			do {
				assert(*node->vn_byaddr.ln_pself == node);
				/* Assign the proper VM to this node. */
				node->vn_vm = target;
				/* Create the part link for this node. */
				if (node->vn_prot & VM_PROT_SHARED) {
					LLIST_INSERT(node->vn_part->dp_srefs, node, vn_link);
				} else {
					LLIST_INSERT(node->vn_part->dp_crefs, node, vn_link);
				}
				printk(KERN_DEBUG "Map %p...%p against 1 data part\n",
				       vm_node_getminaddr(node),
				       vm_node_getmaxaddr(node));
			} while ((node = node->vn_byaddr.ln_next) != NULL);
		}

		/* Re-insert the kernel-reserve node. */
		assert(target->v_kernreserve.vn_vm == target);
		/* In compatibility-mode, there is a chance that `v_kernreserve' was
		 * resized to span a larger region of memory in order to simulate an
		 * address space that may be found on the emulated architecture.
		 * This happens mainly as the result of attempting to access ukern
		 * at an address that should have been apart of kernel-space, but
		 * wasn't because kernel-space was actually allocated elsewhere:
		 * >> PF_HANDLER:
		 * >>     if (ATTEMTED_TO_ACCESS_UNMAPPED_ADDRESS) {
		 * >> #if !defined(CONFIG_NO_USERKERN_SEGMENT) && defined(__ARCH_HAVE_COMPAT)
		 * >>         if (IN_COMPAT_MODE() &&
		 * >>             FAULT_ADDR < KERNELSPACE_BASE &&
		 * >>             FAULT_ADDR >= COMPAT_KERNELSPACE_BASE) {
		 * >>             sync_write(THIS_VM);
		 * >>             if (!vm_isused(THIS_VM, COMPAT_KERNELSPACE_BASE,
		 * >>                            KERNELSPACE_BASE - COMPAT_KERNELSPACE_BASE)) {
		 * >>                 struct vm_node *kr = vm_node_remove(THIS_VM, KERNELSPACE_BASE);
		 * >>                 assert(kr == &THIS_VM->v_kernreserve);
		 * >>                 // Extend the kern-reserve node to fill the
		 * >>                 // entire compat-mode kernel address space.
		 * >>                 kr->vn_node.a_vmin = PAGEID_ENCODE(COMPAT_KERNELSPACE_BASE);
		 * >>                 vm_node_insert(kr);
		 * >>                 sync_endwrite(THIS_VM);
		 * >>                 goto try_lookup_node_at_accessed_address;
		 * >>             }
		 * >>             sync_endwrite(THIS_VM);
		 * >>         }
		 * >> #endif // ...
		 * >>     }
		 */
#if defined(__ARCH_HAVE_COMPAT) && !defined(CONFIG_NO_USERKERN_SEGMENT)
		if (target->v_kernreserve.vn_part == &userkern_segment_part_compat) {
			assert(target->v_kernreserve.vn_block == &userkern_segment_file_compat);
#ifdef KERNELSPACE_HIGHMEM
#if defined(COMPAT_KERNELSPACE_BASE) && COMPAT_KERNELSPACE_BASE != KERNELSPACE_BASE
			target->v_kernreserve.vn_node.a_vmin = KERNELSPACE_MINPAGEID;
			assert(target->v_kernreserve.vn_node.a_vmax == KERNELSPACE_MAXPAGEID);
#endif /* COMPAT_KERNELSPACE_BASE && COMPAT_KERNELSPACE_BASE != KERNELSPACE_BASE */
#else /* KERNELSPACE_HIGHMEM */
#if defined(COMPAT_KERNELSPACE_END) && COMPAT_KERNELSPACE_END != KERNELSPACE_END
			assert(target->v_kernreserve.vn_node.a_vmin == KERNELSPACE_MINPAGEID);
			target->v_kernreserve.vn_node.a_vmax = KERNELSPACE_MAXPAGEID;
#endif /* COMPAT_KERNELSPACE_END && COMPAT_KERNELSPACE_END != KERNELSPACE_END */
#endif /* !KERNELSPACE_HIGHMEM */
			target->v_kernreserve.vn_part  = &userkern_segment_part;
			target->v_kernreserve.vn_block = &userkern_segment_file;
		}
#endif /* __ARCH_HAVE_COMPAT && !CONFIG_NO_USERKERN_SEGMENT */

		vm_node_insert(&target->v_kernreserve);

		/* Delete all user-space mappings within the specified target VM.
		 * All of the newly created mappings are simply going to be bound
		 * lazily, as they get accessed.
		 * NOTE: Outside of SMP, or when `VMB_APPLY_AA_TERMTHREADS' is given, we
		 *       can unmap user-space without having to keep on syncing the VM! */
#ifndef CONFIG_NO_SMP
		if (!(additional_actions & VMB_APPLY_AA_TERMTHREADS)) {
			if (target == THIS_VM)
				pagedir_unmap_userspace_nosync();
			else {
				pagedir_unmap_userspace_nosync_p(target->v_pdir_phys);
			}
		} else
#endif /* !CONFIG_NO_SMP */
		{
			if (target == THIS_VM)
				pagedir_unmap_userspace();
			else {
				pagedir_unmap_userspace_p(target->v_pdir_phys);
			}
		}

		/* Sync everything within the specified target VM */
#ifndef CONFIG_NO_SMP
		if (!(additional_actions & VMB_APPLY_AA_TERMTHREADS)) {
			vm_syncall(target);
		} else
#endif /* !CONFIG_NO_SMP */
		{
			/* Simple case: we know we're the only thread using this VM (meaning we're also
			 * the only CPU using it). - Because of this, we don't even need to go down the
			 * rabbit hole of proper VM syncing since everything is now contained to our own
			 * thread. */
			if (THIS_VM == target)
				pagedir_syncall();
		}

		/* Release held locks. */
		vm_tasklock_endwrite(target);
		pointer_set_unlock_vm_dataparts(&locked_parts);
		pointer_set_fini(&locked_parts);

		/* Destroy all of the old VM Nodes.
		 * NOTE: This _MUST_ be done before we `sync_endwrite(target)', as other code
		 * will check for stale node pointers after having acquired a lock to the VMs
		 * of all of the nodes associated with some data part. */
		while (old_node_list) {
			node = old_node_list->vn_byaddr.ln_next;
			assert(!node || node->vn_byaddr.ln_pself == &old_node_list->vn_byaddr.ln_next);
			vm_node_destroy(old_node_list);
			old_node_list = node;
		}
		sync_endwrite(target);
	}
	xdecref(old_execinfo.ei_dent);
	xdecref(old_execinfo.ei_node);
	xdecref(old_execinfo.ei_path);
#ifndef NDEBUG
	/* Undefined state... */
	memset(self, 0xcc, sizeof(*self));
#endif /* !NDEBUG */
}


/* Overlay mappings from `self' onto `target'
 * This operation is performed atomically, though will fail if `target'
 * already contains mappings at addressed described by `self'.
 * @return: true:  The overlay was successful.
 * @return: false: The given `target' already contains
 *                 mappings with conflicting address ranges. */
PUBLIC NONNULL((1, 2)) bool KCALL
vmb_overlay(struct vmb *__restrict self,
            struct vm *__restrict target)
		THROWS(E_BADALLOC, E_WOULDBLOCK) {
	(void)self;
	(void)target;
	/* TODO */
	THROW(E_NOT_IMPLEMENTED_TODO);
}



DECL_END

#endif /* !GUARD_KERNEL_SRC_MEMORY_VM_BUILDER_C */
