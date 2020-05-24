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
#ifndef GUARD_KERNEL_SRC_MEMORY_VM_CLONE_C
#define GUARD_KERNEL_SRC_MEMORY_VM_CLONE_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <fs/node.h>
#include <fs/vfs.h>
#include <kernel/except.h>
#include <kernel/printk.h>
#include <kernel/vm.h>
#include <kernel/vm/exec.h>

#include <hybrid/atomic.h>
#include <hybrid/overflow.h>

#include <assert.h>
#include <string.h>

#include "vm-nodeapi.h"


#define POINTER_SET_BUFSIZE 16
#include <misc/pointer-set.h>

DECL_BEGIN


#ifndef NDEBUG
PRIVATE NOBLOCK void KCALL
pointer_set_assert_writing_vm_dataparts(struct pointer_set *__restrict self) {
	struct vm_datapart *part;
	POINTER_SET_FOREACH(part, self) {
		assert(sync_writing(part));
	}
}
#else /* !NDEBUG */
#define pointer_set_assert_writing_vm_dataparts(self) (void)0
#endif /* NDEBUG */

PRIVATE NOBLOCK void KCALL
pointer_set_unlock_vm_dataparts(struct pointer_set *__restrict self) {
	struct vm_datapart *part;
	POINTER_SET_FOREACH(part, self) {
		sync_endwrite(part);
	}
}

PRIVATE NOBLOCK void KCALL
pointer_set_unlock_vm_dataparts_except(struct pointer_set *__restrict self,
                                       struct vm_datapart *__restrict not_this_one) {
	struct vm_datapart *part;
	POINTER_SET_FOREACH(part, self) {
		if (part != not_this_one)
			sync_endwrite(part);
	}
}

PRIVATE NOBLOCK void KCALL
pointer_set_unlock_vm_dataparts_and_clear(struct pointer_set *__restrict self) {
	pointer_set_unlock_vm_dataparts(self);
	pointer_set_clear(self);
}

PRIVATE NOBLOCK void KCALL
pointer_set_unlock_vm_dataparts_and_clear_except(struct pointer_set *__restrict self,
                                                 struct vm_datapart *__restrict not_this_one) {
	pointer_set_unlock_vm_dataparts_except(self, not_this_one);
	pointer_set_clear(self);
}

PRIVATE NOBLOCK void KCALL
free_nodes_chain(struct vm_node *chain) {
	while (chain) {
		struct vm_node *next;
		next = chain->vn_byaddr.ln_next;
		kfree(chain);
		chain = next;
	}
}


typedef void (KCALL *pervm_clone_t)(struct vm *__restrict newvm,
                                    struct vm *__restrict oldvm)
		/*THROWS(...)*/;
INTDEF pervm_clone_t __kernel_pervm_clone_start[];
INTDEF pervm_clone_t __kernel_pervm_clone_end[];
PUBLIC CALLBACK_LIST(void FCALL(struct vm * /*newvm*/, struct vm * /*oldvm*/)) vm_onclone_callbacks = CALLBACK_LIST_INIT;

/* Clone the given VM `self'
 * NOTE: The clone operation is performed atomically, meaning that
 *       this function guaranties that at one point both `self' and
 *       the returned VM contained perfectly identical mappings, even
 *       if during the course of this function operating the mappings
 *       contained within `self' are being changed.
 * @param: keep_loose_mappings: When false (default), don't clone mappings marked as `VM_PROT_LOOSE'
 * @return: * : A reference to the newly cloned VM (with a reference counter of `1'). */
PUBLIC ATTR_RETNONNULL REF struct vm *KCALL
vm_clone(struct vm *__restrict self,
         bool keep_loose_mappings)
		THROWS(E_BADALLOC, ...) {
	REF struct vm *result;
	size_t node_alloc_count;
	size_t node_req_count;
	struct vm_node *result_nodes;
	struct vm_node *node;
	struct pointer_set locked_parts;

	assertf(self != &vm_kernel, "Can't clone the kernel VM");
	/* Allocate a new VM which we're going to populate */
	result           = vm_alloc();
	node_alloc_count = 0;
	result_nodes     = NULL;
	pointer_set_init(&locked_parts);
	TRY {
		assert(!isshared(result));
again_lock_vm:
		sync_write(self);
		/* Figure out how many nodes it'll take to clone the contents of `self' */
		node_req_count = 0;
		pointer_set_assert_writing_vm_dataparts(&locked_parts);
		for (node = self->v_byaddr; node;
		     node = node->vn_byaddr.ln_next) {
			int error;
			struct vm_datapart *node_part;
			if (node == &self->v_kernreserve ||
			    ((node->vn_prot & VM_PROT_LOOSE) && !keep_loose_mappings))
				continue; /* Ignore this node! */
			assertf(!PAGEIDRANGE_ISKERN_PARTIAL(vm_node_getstartpageid(node),
			                                    vm_node_getendpageid(node)),
			        "%p...%p\n"
			        "%p...%p\n",
			        (uintptr_t)vm_node_getmin(node),
			        (uintptr_t)vm_node_getmax(node),
			        (uintptr_t)vm_node_getstartpageid(node),
			        (uintptr_t)vm_node_getendpageid(node));
			node_part = node->vn_part;
			if (node_part) {
				pointer_set_assert_writing_vm_dataparts(&locked_parts);
				/* Acquire a lock to the associated data part (if this is
				 * the first time that the associated part has come up). */
				error = pointer_set_insert_nx(&locked_parts,
				                              node_part,
				                              GFP_ATOMIC);
				if unlikely(error == POINTER_SET_INSERT_NX_FAILED) {
					size_t min_parts;
					/* Failed to re-hash the pointer set.
					 * -> Unlock all already locked parts and re-hash the set while blocking. */
					pointer_set_unlock_vm_dataparts(&locked_parts);
					min_parts = locked_parts.ps_size;
					for (; node; node = node->vn_byaddr.ln_next)
						++min_parts;
					sync_endwrite(self);
					/* NOTE: `pointer_set_reset_rehash()' automatically clears the part-set,
					 *        as well as frees the old hash-vector in case of an allocation
					 *        failure. */
					pointer_set_reset_rehash(&locked_parts,
					                         min_parts,
					                         GFP_NORMAL);
					pointer_set_assert_writing_vm_dataparts(&locked_parts);
					goto again_lock_vm;
				}
				if (error != POINTER_SET_INSERT_NX_EXISTS) {
					/* This one's a new data part. -> Must lock it the first time around! */
					if (!sync_trywrite(node_part)) {
						/* Failed to acquire a lock. -> Unlock all already locked parts, and
						 * acquire a blocking lock to this one. Then, try again. */
						incref(node_part);
						pointer_set_unlock_vm_dataparts_and_clear_except(&locked_parts,
						                                                 node_part);
						sync_endwrite(self);
						{
							FINALLY_DECREF_UNLIKELY(node_part);
							sync_write(node_part);
							sync_endwrite(node_part);
						}
						pointer_set_assert_writing_vm_dataparts(&locked_parts);
						goto again_lock_vm;
					}
					assert(sync_writing(node_part));
				}
				assert(sync_writing(node_part));
				pointer_set_assert_writing_vm_dataparts(&locked_parts);
				if (!(node->vn_prot & VM_PROT_SHARED)) {
					struct vm *blocking_vm;
					if (node_part->dp_crefs == NULL) {
						struct vm_node *iter;
						/* The addition of the first copy-on-write mapping requires
						 * that all existing SHARED memory mappings be updated to
						 * not include write permissions in their page directories.
						 * That way, a #PF will be triggered which will then unshare
						 * our own data part, preventing writes to the shared mapping
						 * from leaking into private mappings. */
						for (iter = node_part->dp_srefs; iter;
						     iter = iter->vn_link.ln_next) {
							error = vm_node_update_write_access_locked_vm(iter, self);
							if unlikely(error != VM_NODE_UPDATE_WRITE_ACCESS_SUCCESS) {
								blocking_vm = iter->vn_vm;
								goto handle_remove_write_error;
							}
						}
					} else if (node_part->dp_crefs->vn_link.ln_next == NULL &&
					           /* If this is the second copy-on-write mapping of an anonymous data part,
					            * then the first one may have had write permissions which must now be
					            * unshared (this is the case for general purpose RAM during fork()) */
					           ATOMIC_READ(node_part->dp_block->db_parts) == VM_DATABLOCK_ANONPARTS) {
						error = vm_node_update_write_access_locked_vm(node_part->dp_crefs, self);
						if unlikely(error != VM_NODE_UPDATE_WRITE_ACCESS_SUCCESS) {
							blocking_vm = node_part->dp_crefs->vn_vm;
handle_remove_write_error:
							if (error == VM_NODE_UPDATE_WRITE_ACCESS_BADALLOC) {
								pointer_set_unlock_vm_dataparts(&locked_parts);
								THROW(E_BADALLOC_INSUFFICIENT_PHYSICAL_MEMORY, PAGESIZE);
							}
							if (!tryincref(blocking_vm))
								blocking_vm = NULL;
							pointer_set_unlock_vm_dataparts_and_clear(&locked_parts);
							assert(error == VM_NODE_UPDATE_WRITE_ACCESS_WOULDBLOCK ||
							       error == VM_NODE_UPDATE_WRITE_ACCESS_WOULDBLOCK_TASKS);
							if (blocking_vm) {
								FINALLY_DECREF_UNLIKELY(blocking_vm);
								if (error == VM_NODE_UPDATE_WRITE_ACCESS_WOULDBLOCK_TASKS) {
									vm_tasklock_read(blocking_vm);
									vm_tasklock_endread(blocking_vm);
								} else {
									sync_write(blocking_vm);
									sync_endwrite(blocking_vm);
								}
							}
							pointer_set_assert_writing_vm_dataparts(&locked_parts);
							goto again_lock_vm;
						}
					}
				}
			}
			pointer_set_assert_writing_vm_dataparts(&locked_parts);
			assert(node_alloc_count >= node_req_count);
			if (node_alloc_count <= node_req_count) {
				struct vm_node *new_node;
				/* Must allocate more nodes for our VM clone. */
				new_node = (struct vm_node *)kmalloc_nx(sizeof(struct vm_node),
				                                        GFP_LOCKED | GFP_PREFLT |
				                                        GFP_VCBASE | GFP_ATOMIC);
				if unlikely(!new_node) {
					/* Must blocking-allocate the node. */
					pointer_set_unlock_vm_dataparts_and_clear(&locked_parts);
					sync_endwrite(self);
					new_node = (struct vm_node *)kmalloc(sizeof(struct vm_node),
					                                     GFP_LOCKED | GFP_PREFLT | GFP_VCBASE);
					++node_alloc_count;
					new_node->vn_byaddr.ln_next = result_nodes;
					result_nodes                = new_node;
					pointer_set_assert_writing_vm_dataparts(&locked_parts);
					goto again_lock_vm;
				}
				++node_alloc_count;
				new_node->vn_byaddr.ln_next = result_nodes;
				result_nodes                = new_node;
			}
			++node_req_count;
		} /* FOREACH(node: self) */

		assert(node_alloc_count >= node_req_count);
		/* At this point we've got locks to all of the mapped data parts,
		 * as well as having allocated a sufficient number of nodes.
		 * -> Now to duplicate everything all at once. */
		/* |------ Pointer of no return */

		for (node = self->v_byaddr; node;
		     node = node->vn_byaddr.ln_next) {
			struct vm_node *resnode;
			if (node == &self->v_kernreserve ||
			    ((node->vn_prot & VM_PROT_LOOSE) && !keep_loose_mappings))
				continue; /* Ignore this node! */
			resnode = result_nodes;
			assertf(resnode,
			        "node_alloc_count = %Iu\n"
			        "node_req_count   = %Iu\n",
			        node_alloc_count, node_req_count);
			result_nodes            = resnode->vn_byaddr.ln_next;
			resnode->vn_node.a_vmin = node->vn_node.a_vmin;
			resnode->vn_node.a_vmax = node->vn_node.a_vmax;
			resnode->vn_prot        = node->vn_prot;
			resnode->vn_flags       = node->vn_flags;
			resnode->vn_vm          = result;
			resnode->vn_part        = xincref(node->vn_part);
			resnode->vn_block       = xincref(node->vn_block);
			assert(!node->vn_part || getrefcnt(node->vn_part) >= 2);
			assert(!node->vn_block || getrefcnt(node->vn_block) >= 2);
			if (resnode->vn_part) {
				if (resnode->vn_prot & VM_PROT_SHARED) {
					LLIST_INSERT(resnode->vn_part->dp_srefs, resnode, vn_link);
				} else {
					LLIST_INSERT(resnode->vn_part->dp_crefs, resnode, vn_link);
				}
			}
			resnode->vn_guard = node->vn_guard;
			assertf(!PAGEIDRANGE_ISKERN_PARTIAL(vm_node_getstartpageid(resnode),
			                                    vm_node_getendpageid(resnode)),
			        "%p...%p\n"
			        "%p...%p\n",
			        (uintptr_t)vm_node_getmin(resnode),
			        (uintptr_t)vm_node_getmax(resnode),
			        (uintptr_t)vm_node_getstartpageid(resnode),
			        (uintptr_t)vm_node_getendpageid(resnode));
			if (resnode->vn_flags & VM_NODE_FLAG_PREPARED) {
				/* Try to keep already prepared nodes also prepared within the VM clone.
				 * However, if this fails, just ignore the error and unset the PREPARED bit. */
				if (!pagedir_prepare_map_p(PAGEDIR_P_SELFOFVM(result),
				                           vm_node_getstart(resnode),
				                           vm_node_getsize(resnode)))
					resnode->vn_flags &= ~VM_NODE_FLAG_PREPARED;
			}
			/* Insert the cloned node into the resulting VM. */
			vm_node_insert(resnode);
		}
	} EXCEPT {
		/* Free all already allocated nodes. */
		assert((result_nodes != NULL) == (node_alloc_count != 0));
		free_nodes_chain(result_nodes);
		assert(!isshared(result));
		assert(!wasdestroyed(result));
		pointer_set_fini(&locked_parts);
		destroy(result);
		RETHROW();
	}
	/* And with that, we're done! */
	assert((result_nodes == NULL) ==
	       (node_alloc_count == node_req_count));

	/* Copy execinfo */
	{
		struct vm_execinfo_struct *dst, *src;
		dst = &FORVM(result, thisvm_execinfo);
		src = &FORVM(self, thisvm_execinfo);
		dst->ei_node = (REF struct inode *)xincref(src->ei_node);
		dst->ei_dent = xincref(src->ei_dent);
		dst->ei_path = xincref(src->ei_path);
	}

	/* Unlock all of the locked parts. */
	pointer_set_unlock_vm_dataparts(&locked_parts);
	/* Unlock the source VM */
	sync_endwrite(self);
	/* Free any unused nodes. (Though there really shouldn't be any) */
	free_nodes_chain(result_nodes);
	pointer_set_fini(&locked_parts);
	TRY {
		pervm_clone_t *iter;
		for (iter = __kernel_pervm_clone_start;
		     iter < __kernel_pervm_clone_end; ++iter)
			(**iter)(result, self);
		assert(iter == __kernel_pervm_clone_end);
		vm_onclone_callbacks(result, self);
	} EXCEPT {
		destroy(result);
		RETHROW();
	}
	return result;
}

DECL_END

#endif /* !GUARD_KERNEL_SRC_MEMORY_VM_CLONE_C */
