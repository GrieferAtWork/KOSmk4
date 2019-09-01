/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifdef __INTELLISENSE__
#include "vm.c"
#define VM_DEFINE_UNMAP 1
//#define VM_DEFINE_PROTECT 1
#endif

#if (defined(VM_DEFINE_UNMAP) + defined(VM_DEFINE_PROTECT)) != 1
#error "Invalid configuration"
#endif


DECL_BEGIN

#if defined(VM_DEFINE_UNMAP)
/* Unmap all memory mappings within the given address range.
 * @param: base:      The base page number at which to start unmapping memory.
 * @param: num_pages: The number of continuous pages of memory to unmap, starting at `base'
 * @param: how:       What memory may be unmapped, and how that memory should be unmapped (Set of `VM_UNMAP_*')
 * @return: * :       The actual number of unmapped pages of memory (when `VM_UNMAP_SEGFAULTIFUNUSED'
 *                    is given, this is always equal to `num_pages') */
PUBLIC size_t KCALL
vm_unmap(struct vm *__restrict effective_vm,
         vm_vpage_t base,
         size_t num_pages,
         unsigned int how)
#elif defined(VM_DEFINE_PROTECT)
/* Update access protection flags within the given address range.
 * @param: base:       The base page number at which to start unmapping memory.
 * @param: num_pages:  The number of continuous pages of memory to unmap, starting at `base'
 * @param: prot_mask:  Mask of protection bits that should be kept (Set of `VM_PROT_*').
 * @param: prot_flags: Set of protection bits that should be added (Set of `VM_PROT_*').
 * @param: how:        What memory may be updated, and how that memory should be updated (Set of `VM_UNMAP_*')
 * @return: * :        The actual number of updated pages of memory (when `VM_UNMAP_SEGFAULTIFUNUSED'
 *                     is given, this is always equal to `num_pages') */
PUBLIC size_t KCALL
vm_protect(struct vm *__restrict effective_vm,
           vm_vpage_t base,
           size_t num_pages,
           uintptr_t prot_mask,
           uintptr_t prot_flags,
           unsigned int how)
#endif /* ... */
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT)
{
	struct vm *myvm;
	size_t result;
	vm_vpage_t maxpage;
	vm_nodetree_minmax_t minmax;
	struct vm_node *new_node = NULL;
	bool must_sync = false;
	bool update_all = (how & (VM_UNMAP_NORMAL | VM_UNMAP_GUARD | VM_UNMAP_RESERVE)) ==
	                  (VM_UNMAP_NORMAL | VM_UNMAP_GUARD | VM_UNMAP_RESERVE);
	bool update_all_nokern = (how & (VM_UNMAP_NORMAL | VM_UNMAP_GUARD | VM_UNMAP_RESERVE | VM_UNMAP_NOKERNPART)) ==
	                         (VM_UNMAP_NORMAL | VM_UNMAP_GUARD | VM_UNMAP_RESERVE | VM_UNMAP_NOKERNPART);
#define SHOULD_UPDATE(node) \
	(update_all || ((!((node)->vn_flags & VM_NODE_FLAG_KERNPRT) || !(how & VM_UNMAP_NOKERNPART)) &&                             \
	                (update_all_nokern || (node)->vn_part                                                                       \
	                 ? ((node)->vn_guard ? (how & VM_UNMAP_GUARD) : (how & VM_UNMAP_NORMAL))                                    \
	                 : ((node)->vn_guard ? ((how & (VM_UNMAP_GUARD | VM_UNMAP_RESERVE)) == (VM_UNMAP_GUARD | VM_UNMAP_RESERVE)) \
	                                     : ((how & (VM_UNMAP_NORMAL | VM_UNMAP_RESERVE)) == (VM_UNMAP_NORMAL | VM_UNMAP_RESERVE))))))
#ifdef VM_DEFINE_PROTECT
	assertf(!(prot_mask &
	          ~(VM_PROT_EXEC | VM_PROT_WRITE | VM_PROT_READ | VM_PROT_LOOSE | VM_PROT_SHARED)),
	        "prot_mask = %#Ix", (uintptr_t)prot_mask);
	assertf(!(prot_flags &
	          ~(VM_PROT_EXEC | VM_PROT_WRITE | VM_PROT_READ | VM_PROT_LOOSE | VM_PROT_SHARED)),
	        "prot_flags = %#Ix", (uintptr_t)prot_flags);
#endif /* VM_DEFINE_PROTECT */
	if unlikely(!num_pages)
		return 0; /* No-op */
	if (OVERFLOW_UADD(base, num_pages - 1, &maxpage) || maxpage > VM_VPAGE_MAX) {
		if (how & VM_UNMAP_SEGFAULTIFUNUSED)
			THROW(E_SEGFAULT_UNMAPPED, (void *)-1, E_SEGFAULT_CONTEXT_UNMAP);
		maxpage = VM_VPAGE_MAX;
	}
	myvm   = THIS_VM;
	result = 0;
	TRY {
again_lock_vm:
		sync_write(effective_vm);
		minmax.mm_min = minmax.mm_max = NULL;
		vm_nodetree_minmaxlocate(effective_vm->v_tree,
		                         base,
		                         maxpage,
		                         &minmax);
		assert((minmax.mm_min != NULL) == (minmax.mm_max != NULL));
		if unlikely(!minmax.mm_min) {
			if unlikely(how & VM_UNMAP_SEGFAULTIFUNUSED)
				goto do_throw_base_unmapped;
			goto done;
		}
		if (how & VM_UNMAP_SEGFAULTIFUNUSED) {
			struct vm_node *iter;
			/* Check that the entire given address range is in use. */
			if unlikely(base < minmax.mm_min_min) {
do_throw_base_unmapped:
				sync_endwrite(effective_vm);
				THROW(E_SEGFAULT_UNMAPPED,
				      VM_PAGE2ADDR(base),
				      E_SEGFAULT_CONTEXT_UNMAP);
			}
			iter = minmax.mm_min;
			while (iter != minmax.mm_max) {
				vm_vpage_t first_unmapped;
				struct vm_node *next;
				if unlikely(!SHOULD_UPDATE(iter)) {
					first_unmapped = VM_NODE_START(iter);
					goto do_throw_first_unmapped;
				}
				next = iter->vn_byaddr.ln_next;
				assert(VM_NODE_END(iter) <= VM_NODE_START(next));
				if unlikely(VM_NODE_END(iter) != VM_NODE_START(next)) {
					first_unmapped = VM_NODE_END(iter);
do_throw_first_unmapped:
					sync_endwrite(effective_vm);
					THROW(E_SEGFAULT_UNMAPPED,
					      VM_PAGE2ADDR(first_unmapped),
					      E_SEGFAULT_CONTEXT_UNMAP);
				}
				iter = next;
			}
			if unlikely(maxpage > minmax.mm_max_max) {
				sync_endwrite(effective_vm);
				THROW(E_SEGFAULT_UNMAPPED,
				      VM_PAGE2ADDR(minmax.mm_max_max + 1),
				      E_SEGFAULT_CONTEXT_UNMAP);
			}
		}
		/* Make sure that all memory mappings within the given range have been prepared! */
		{
			struct vm_node *node = minmax.mm_min;
			for (;;) {
				assert(node->vn_vm == effective_vm);
				if (SHOULD_UPDATE(node) &&
				    (node->vn_flags & (VM_NODE_FLAG_PREPARED | VM_NODE_FLAG_PARTITIONED)) !=
				    VM_NODE_FLAG_PREPARED) {
					if unlikely(!(effective_vm == myvm || PRANGE_IS_KERNEL(VM_NODE_START(node), VM_NODE_END(node))
					              ? pagedir_prepare_map(VM_NODE_START(node), VM_NODE_SIZE(node))
					              : pagedir_prepare_map_p(PAGEDIR_P_SELFOFVM(effective_vm),
					                                      VM_NODE_START(node),
					                                      VM_NODE_SIZE(node)))) {
						sync_endwrite(effective_vm);
						THROW(E_BADALLOC_INSUFFICIENT_PHYSICAL_MEMORY, 1);
					}
				}
				if (node == minmax.mm_max)
					break;
				node = VM_NODE_NEXT(node);
			}
		}
		if (base > minmax.mm_min_min) {
			/* Must split the first page. */
			if (!SHOULD_UPDATE(minmax.mm_min) || (how & VM_UNMAP_NOSPLIT)) {
				if (how & VM_UNMAP_SEGFAULTIFUNUSED)
					goto do_throw_base_unmapped;
				if (minmax.mm_min == minmax.mm_max)
					goto done;
				minmax.mm_min     = minmax.mm_min->vn_byaddr.ln_next;
				minmax.mm_min_min = VM_NODE_MIN(minmax.mm_min);
			} else if unlikely(minmax.mm_min->vn_flags & VM_NODE_FLAG_KERNPRT) {
#ifdef VM_DEFINE_PROTECT
				kernel_panic("Attempted to mprotect() a kernel part at %p...%p",
				             VM_NODE_MINADDR(minmax.mm_min),
				             VM_NODE_MAXADDR(minmax.mm_min));
#else
				kernel_panic("Attempted to munmap a kernel part at %p...%p",
				             VM_NODE_MINADDR(minmax.mm_min),
				             VM_NODE_MAXADDR(minmax.mm_min));
#endif
#ifdef VM_DEFINE_UNMAP
			} else if (!minmax.mm_min->vn_part) {
				/* No part. -> The node can just be modified directly. */
				struct vm_node *next = minmax.mm_min->vn_byaddr.ln_next;
				vm_nodetree_remove(&effective_vm->v_tree, minmax.mm_min_min);
				LLIST_REMOVE(minmax.mm_min, vn_byaddr);
				if (maxpage >= VM_NODE_MAX(minmax.mm_min)) {
					printk(KERN_DEBUG "Unmap node at %p...%p (high_part of %p...%p)\n",
					       VM_PAGE2ADDR(base),
					       VM_NODE_MAX(minmax.mm_min),
					       VM_NODE_MIN(minmax.mm_min),
					       VM_NODE_MAX(minmax.mm_min));
					result += (size_t)(VM_NODE_END(minmax.mm_min) - base);
					minmax.mm_min->vn_node.a_vmax = base - 1;
					vm_node_insert(minmax.mm_min);
					minmax.mm_min     = next;
					minmax.mm_min_min = VM_NODE_MIN(next);
					assert(minmax.mm_min_min >= base);
					if (minmax.mm_min == minmax.mm_max)
						goto done;
				} else {
					/* Unmap a sub-segment of a reserved memory node.
					 * For this, we need to allocate a new node to fill in the high part.
					 * LOW:  VM_NODE_MIN(minmax.mm_min) ... base - 1
					 * HIGH: maxpage + 1 ... VM_NODE_MIN(minmax.mm_min) */
					if (!new_node) {
						new_node = (struct vm_node *)kmalloc_nx(sizeof(struct vm_node),
						                                        GFP_ATOMIC | GFP_LOCKED |
						                                        GFP_PREFLT | GFP_VCBASE);
						if (!new_node) {
							sync_endwrite(effective_vm);
							new_node = (struct vm_node *)kmalloc(sizeof(struct vm_node),
							                                     GFP_LOCKED |
							                                     GFP_PREFLT | GFP_VCBASE);
							goto again_lock_vm;
						}
					}
					printk(KERN_DEBUG "Unmap node at %p...%p (sub_segment of %p...%p)\n",
					       VM_PAGE2ADDR(base),
					       VM_PAGE2ADDR(maxpage + 1) - 1,
					       VM_NODE_MIN(minmax.mm_min),
					       VM_NODE_MAX(minmax.mm_min));
					assert(!(minmax.mm_min->vn_flags & VM_NODE_FLAG_HINTED));
					result                   = (size_t)(maxpage - base) + 1;
					new_node->vn_node.a_vmin = maxpage + 1;
					new_node->vn_node.a_vmax = minmax.mm_min->vn_node.a_vmax;
					new_node->vn_prot        = minmax.mm_min->vn_prot;
					new_node->vn_flags = minmax.mm_min->vn_flags & (VM_NODE_FLAG_PREPARED |
					                                                VM_NODE_FLAG_GROWSUP |
					                                                VM_NODE_FLAG_PARTITIONED |
					                                                VM_NODE_FLAG_NOMERGE |
					                                                VM_NODE_FLAG_KERNPRT);
					minmax.mm_min->vn_flags |= VM_NODE_FLAG_PARTITIONED;
					new_node->vn_flags |= VM_NODE_FLAG_PARTITIONED;
					new_node->vn_vm               = effective_vm;
					new_node->vn_part             = NULL;
					new_node->vn_block            = xincref(minmax.mm_min->vn_block);
					new_node->vn_guard            = 0;
					minmax.mm_min->vn_node.a_vmax = base - 1;
					if (minmax.mm_min->vn_guard &&
					    minmax.mm_min->vn_flags & VM_NODE_FLAG_GROWSUP) {
						new_node->vn_guard = minmax.mm_min->vn_guard;
						minmax.mm_min->vn_flags &= ~VM_NODE_FLAG_GROWSUP;
						minmax.mm_min->vn_guard = 0;
					}
					vm_node_insert(minmax.mm_min);
					vm_node_insert(new_node);
					sync_endwrite(effective_vm);
					return result;
				}
#endif /* VM_DEFINE_UNMAP */
			} else {
				REF struct vm_datapart *part;
				size_t vpage_offset;
				vpage_offset = (size_t)(base - minmax.mm_min_min);
				assert(vpage_offset < VM_NODE_SIZE(minmax.mm_min));
				part = incref(minmax.mm_min->vn_part);
				sync_endwrite(effective_vm);
				/* Split the part, so that our memory mapping
				 * starts when the given range begins. */
				TRY {
					xdecref(vm_datapart_split(part, vpage_offset));
				} EXCEPT {
					vm_datapart_decref_and_merge(part);
					RETHROW();
				}
				decref(part); /* Don't merge on this one! */
				goto again_lock_vm;
			}
		}
		if (minmax.mm_max_max > maxpage) {
			/* Must split the last page. */
			if (!SHOULD_UPDATE(minmax.mm_max) || (how & VM_UNMAP_NOSPLIT)) {
				if (how & VM_UNMAP_SEGFAULTIFUNUSED)
					goto do_throw_base_unmapped;
				if (minmax.mm_min == minmax.mm_max)
					goto done;
				minmax.mm_max     = VM_NODE_PREV(minmax.mm_max);
				minmax.mm_max_max = VM_NODE_MAX(minmax.mm_max);
			} else if unlikely(minmax.mm_max->vn_flags & VM_NODE_FLAG_KERNPRT) {
#ifdef VM_DEFINE_PROTECT
				kernel_panic("Attempted to mprotect() a kernel part at %p...%p",
				             VM_NODE_MINADDR(minmax.mm_max),
				             VM_NODE_MAXADDR(minmax.mm_max));
#else
				kernel_panic("Attempted to munmap() a kernel part at %p...%p",
				             VM_NODE_MINADDR(minmax.mm_max),
				             VM_NODE_MAXADDR(minmax.mm_max));
#endif
#ifdef VM_DEFINE_UNMAP
			} else if (!minmax.mm_max->vn_part) {
				/* No part. -> The node can just be modified directly. */
				struct vm_node *prev = VM_NODE_PREV(minmax.mm_max);
				vm_nodetree_remove(&effective_vm->v_tree, minmax.mm_max_max);
				LLIST_REMOVE(minmax.mm_max, vn_byaddr);
				assert(base <= VM_NODE_MIN(minmax.mm_max));
				printk(KERN_DEBUG "Unmap node at %p...%p (low_part of %p...%p)\n",
				       VM_NODE_MIN(minmax.mm_max),
				       VM_PAGE2ADDR(maxpage + 1) - 1,
				       VM_NODE_MIN(minmax.mm_max),
				       VM_NODE_MAX(minmax.mm_max));
				result += (size_t)((maxpage + 1) - VM_NODE_MIN(minmax.mm_max));
				minmax.mm_max->vn_node.a_vmin = maxpage + 1;
				vm_node_insert(minmax.mm_max);
				minmax.mm_max     = prev;
				minmax.mm_max_max = VM_NODE_MAX(prev);
				assert(minmax.mm_max_max <= maxpage);
				if (minmax.mm_min == minmax.mm_max)
					goto done;
#endif /* VM_DEFINE_UNMAP */
			} else {
				REF struct vm_datapart *part;
				size_t vpage_offset;
				vpage_offset = (size_t)((maxpage + 1) - VM_NODE_START(minmax.mm_max));
				assert(vpage_offset < VM_NODE_SIZE(minmax.mm_max));
				part = incref(minmax.mm_max->vn_part);
				sync_endwrite(effective_vm);
				/* Split the part, so that our memory mapping
				 * starts when the given range begins. */
				TRY {
					xdecref(vm_datapart_split(part, vpage_offset));
				} EXCEPT {
					vm_datapart_decref_and_merge(part);
					RETHROW();
				}
				decref(part); /* Don't merge on this one */
				goto again_lock_vm;
			}
		}
		/* Update all nodes within the minmax range (we've already split partially mapped
		 * nodes such that they the VM has been partitioned in order to allow the nodes
		 * to be unmapped fully) */
		{
			struct vm_node *node = minmax.mm_min;
#ifdef VM_DEFINE_PROTECT
			result = 0;
#endif /* !VM_DEFINE_PROTECT */
			for (;;) {
				struct vm_node *next = VM_NODE_NEXT(node);
				assert(node->vn_vm == effective_vm);
				if (SHOULD_UPDATE(node)) {
#ifdef VM_DEFINE_PROTECT
					uintptr_half_t old_prot;
					uintptr_half_t new_prot;
#endif
					assert(VM_NODE_MIN(node) >= base);
					assert(VM_NODE_MAX(node) <= maxpage);
					/* Update this node! */
					if unlikely(node->vn_flags & VM_NODE_FLAG_KERNPRT) {
#ifdef VM_DEFINE_PROTECT
						kernel_panic("Attempted to mprotect() a kernel part at %p...%p",
						             VM_NODE_MINADDR(node), VM_NODE_MAXADDR(node));
#else
						kernel_panic("Attempted to munmap() a kernel part at %p...%p",
						             VM_NODE_MINADDR(node), VM_NODE_MAXADDR(node));
#endif
					}
#ifdef VM_DEFINE_UNMAP
					printk(KERN_DEBUG "Unmap node at %p...%p\n",
					       VM_NODE_MINADDR(node), VM_NODE_MAXADDR(node));
#endif /* VM_DEFINE_UNMAP */
					result += VM_NODE_SIZE(node);
#ifdef VM_DEFINE_PROTECT
					old_prot = node->vn_prot;
					new_prot = (old_prot & prot_mask) | prot_flags;
					if ((old_prot & VM_PROT_SHARED) != (new_prot & VM_PROT_SHARED)) {
						/* PRIVATE <---> SHARED mapping change. */
						if (node->vn_part != NULL) {
							struct vm_datapart *part = node->vn_part;
							if (!sync_trywrite(part)) {
								incref(part);
								sync_endwrite(effective_vm);
								{
									FINALLY_DECREF_UNLIKELY(part);
									sync_write(part);
									sync_endwrite(part);
								}
								goto again_lock_vm;
							}
							/* Switch the associated chain.
							 * NOTE: When switching from SHARED --> PRIVATE, and our node
							 *       becomes the first PRIVATE mapping, we must update the
							 *       write-access of all other SHARED nodes before proceeding. */
							LLIST_REMOVE(node, vn_link);
							if (new_prot & VM_PROT_SHARED) {
								LLIST_INSERT(part->dp_srefs, node, vn_link);
							} else {
								if (!part->dp_crefs) {
									/* Must update write permissions of all of the other SHARED
									 * mappings, since any future writes at this point will require
									 * our (now) copy-on-write node to be unshared. */
									struct vm_node *sibling_shared;
									for (sibling_shared = part->dp_srefs; sibling_shared;
									     sibling_shared = sibling_shared->vn_link.ln_next) {
										unsigned int error;
										if (sibling_shared == node)
											continue;
										error = vm_node_update_write_access_locked_vm(sibling_shared,
										                                              effective_vm);
										if unlikely(error != VM_NODE_UPDATE_WRITE_ACCESS_SUCCESS) {
											REF struct vm *blocking_vm;
											if (error == VM_NODE_UPDATE_WRITE_ACCESS_BADALLOC) {
												sync_endwrite(part);
												sync_endwrite(effective_vm);
												THROW(E_BADALLOC_INSUFFICIENT_PHYSICAL_MEMORY, 1);
											}
											blocking_vm = sibling_shared->vn_vm;
											if (!tryincref(blocking_vm))
												blocking_vm = NULL;
											sync_endwrite(part);
											sync_endwrite(effective_vm);
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
											goto again_lock_vm;
										}
									}
									/* ... First copy-on-write mapping */
								}
								LLIST_INSERT(part->dp_crefs, node, vn_link);
							}
							/* Actually update the node protection.
							 * NOTE: Do this before unlocking the part, so at no point will
							 *       there be a node with invalid protection flags visible
							 *       within the part itself. */
							node->vn_prot = new_prot;
							COMPILER_WRITE_BARRIER();
							sync_endwrite(part);
							/* Always update the page directory when switching to a PRIVATE
							 * mapping, when the old mapping had write-permissions enabled. */
							if (!(new_prot & VM_PROT_SHARED) && (old_prot & VM_PROT_WRITE))
								goto do_update_page_directory;
						}
					}
					node->vn_prot = new_prot;

					/* Check if we need to update the page directory mapping (and subsequently sync the VM) */
					old_prot &= (VM_PROT_READ | VM_PROT_WRITE | VM_PROT_EXEC);
					new_prot &= (VM_PROT_READ | VM_PROT_WRITE | VM_PROT_EXEC);
					if ((old_prot & ~new_prot) == 0)
						goto did_update_node; /* The mapping became less restrictive, or stayed unchanged
						                       * -> No need to update the page directory */
do_update_page_directory:
#endif /* VM_DEFINE_PROTECT */

					if (effective_vm == myvm || PRANGE_IS_KERNEL(VM_NODE_START(node), VM_NODE_END(node))) {
						pagedir_unmap(VM_NODE_START(node),
						              VM_NODE_SIZE(node));
					} else {
						pagedir_unmap_p(PAGEDIR_P_SELFOFVM(effective_vm),
						                VM_NODE_START(node),
						                VM_NODE_SIZE(node));
					}
					must_sync = true;
#ifdef VM_DEFINE_UNMAP
					/* Remove the node from the VM. */
					vm_nodetree_remove(&effective_vm->v_tree, VM_NODE_START(node));
					LLIST_REMOVE(node, vn_byaddr);
					/* Destroy the old node. NOTE: This _MUST_ be done before we `sync_endwrite(effective_vm)',
					 * as other code will check for stale node pointers after having acquired a lock to the VMs
					 * of all of the nodes associated with some data part. */
					vm_node_destroy(node);
#endif /* VM_DEFINE_UNMAP */
				}
#ifdef VM_DEFINE_PROTECT
did_update_node:
#endif /* VM_DEFINE_PROTECT */
				if (node == minmax.mm_max)
					break;
				node = next;
			}
		}
	} EXCEPT {
		if unlikely(new_node)
			kfree(new_node);
		RETHROW();
	}
	/* Synchronize the affected address range. */
	if (must_sync)
		vm_sync(effective_vm, base, (size_t)(maxpage - base) + 1);
done:
	sync_endwrite(effective_vm);
	if unlikely(new_node)
		kfree(new_node);
	return result;
#undef SHOULD_UPDATE
}


#undef VM_DEFINE_PROTECT
#undef VM_DEFINE_UNMAP

DECL_END



