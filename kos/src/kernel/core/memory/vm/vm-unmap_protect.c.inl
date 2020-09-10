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
 * @param: addr:      The base address at which to start unmapping memory.
 * @param: num_bytes: The number of continuous bytes of memory to unmap, starting at `addr'
 * @param: how:       What memory may be unmapped, and how that memory should be unmapped (Set of `VM_UNMAP_*')
 * @return: * :       The actual number of unmapped bytes of memory (when `VM_UNMAP_SEGFAULTIFUNUSED'
 *                    is given, this is always equal to `num_bytes') */
PUBLIC size_t KCALL
vm_unmap(struct vm *__restrict self,
         PAGEDIR_PAGEALIGNED UNCHECKED void *addr,
         PAGEDIR_PAGEALIGNED size_t num_bytes,
         unsigned int how)
#elif defined(VM_DEFINE_PROTECT)
/* Update access protection flags within the given address range.
 * @param: addr:       The base address at which to start changing protection.
 * @param: num_bytes:  The number of continuous bytes of memory to change, starting at `addr'
 * @param: prot_mask:  Mask of protection bits that should be kept (Set of `VM_PROT_*').
 * @param: prot_flags: Set of protection bits that should be added (Set of `VM_PROT_*').
 * @param: how:        What memory may be updated, and how that memory should be updated (Set of `VM_UNMAP_*')
 * @return: * :        The actual number of updated bytes of memory (when `VM_UNMAP_SEGFAULTIFUNUSED'
 *                     is given, this is always equal to `num_bytes') */
PUBLIC size_t KCALL
vm_protect(struct vm *__restrict self,
           PAGEDIR_PAGEALIGNED UNCHECKED void *addr,
           PAGEDIR_PAGEALIGNED size_t num_bytes,
           uintptr_t prot_mask,
           uintptr_t prot_flags,
           unsigned int how)
#endif /* ... */
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT)
{
	struct vm *myvm;
	size_t result;
	pageid_t minpageid;
	pageid_t maxpageid;
	vm_nodetree_minmax_t minmax;
	struct vm_node *new_node = NULL;
	bool must_sync = false;
	bool update_all = (how & (VM_UNMAP_NORMAL | VM_UNMAP_GUARD | VM_UNMAP_RESERVE)) ==
	                  (VM_UNMAP_NORMAL | VM_UNMAP_GUARD | VM_UNMAP_RESERVE);
	bool update_all_nokern = (how & (VM_UNMAP_NORMAL | VM_UNMAP_GUARD | VM_UNMAP_RESERVE | VM_UNMAP_NOKERNPART)) ==
	                         (VM_UNMAP_NORMAL | VM_UNMAP_GUARD | VM_UNMAP_RESERVE | VM_UNMAP_NOKERNPART);
#define SHOULD_UPDATE(node)                                                                                                     \
	(update_all || ((!((node)->vn_flags & VM_NODE_FLAG_KERNPRT) || !(how & VM_UNMAP_NOKERNPART)) &&                             \
	                (update_all_nokern || (node)->vn_part                                                                       \
	                 ? ((node)->vn_guard ? (how & VM_UNMAP_GUARD) : (how & VM_UNMAP_NORMAL))                                    \
	                 : ((node)->vn_guard ? ((how & (VM_UNMAP_GUARD | VM_UNMAP_RESERVE)) == (VM_UNMAP_GUARD | VM_UNMAP_RESERVE)) \
	                                     : ((how & (VM_UNMAP_NORMAL | VM_UNMAP_RESERVE)) == (VM_UNMAP_NORMAL | VM_UNMAP_RESERVE))))))
	assert(((uintptr_t)addr & PAGEMASK) == 0);
	assert((num_bytes & PAGEMASK) == 0);
#ifdef VM_DEFINE_PROTECT
	assertf(!(prot_mask & ~(VM_PROT_EXEC | VM_PROT_WRITE | VM_PROT_READ | VM_PROT_LOOSE | VM_PROT_SHARED)),
	        "prot_mask = %#Ix", (uintptr_t)prot_mask);
	assertf(!(prot_flags & ~(VM_PROT_EXEC | VM_PROT_WRITE | VM_PROT_READ | VM_PROT_LOOSE | VM_PROT_SHARED)),
	        "prot_flags = %#Ix", (uintptr_t)prot_flags);
#endif /* VM_DEFINE_PROTECT */
	if unlikely(!num_bytes)
		return 0; /* No-op */
	minpageid = PAGEID_ENCODE((byte_t *)addr);
	maxpageid = PAGEID_ENCODE((byte_t *)addr + num_bytes - 1);
	if (maxpageid < minpageid) {
		if (how & VM_UNMAP_SEGFAULTIFUNUSED)
			THROW(E_SEGFAULT_UNMAPPED, (void *)-1, E_SEGFAULT_CONTEXT_UNMAP);
		maxpageid = __ARCH_PAGEID_MAX;
	}
	myvm   = THIS_VM;
	result = 0;
	TRY {
again_lock_vm:
		sync_write(self);
		minmax.mm_min = minmax.mm_max = NULL;
		vm_nodetree_minmaxlocate(self->v_tree,
		                         minpageid,
		                         maxpageid,
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
			if unlikely(minpageid < minmax.mm_min_min) {
do_throw_base_unmapped:
				sync_endwrite(self);
				THROW(E_SEGFAULT_UNMAPPED, addr,
				      E_SEGFAULT_CONTEXT_UNMAP);
			}
			iter = minmax.mm_min;
			while (iter != minmax.mm_max) {
				void *first_unmapped;
				struct vm_node *next;
				if unlikely(!SHOULD_UPDATE(iter)) {
					first_unmapped = vm_node_getstart(iter);
					goto do_throw_first_unmapped;
				}
				next = iter->vn_byaddr.ln_next;
				assert(vm_node_getendpageid(iter) <= vm_node_getstartpageid(next));
				if unlikely(vm_node_getendpageid(iter) != vm_node_getstartpageid(next)) {
					first_unmapped = vm_node_getend(iter);
do_throw_first_unmapped:
					sync_endwrite(self);
					THROW(E_SEGFAULT_UNMAPPED,
					      first_unmapped,
					      E_SEGFAULT_CONTEXT_UNMAP);
				}
				iter = next;
			}
			if unlikely(maxpageid > minmax.mm_max_max) {
				sync_endwrite(self);
				THROW(E_SEGFAULT_UNMAPPED,
				      PAGEID_DECODE(minmax.mm_max_max + 1),
				      E_SEGFAULT_CONTEXT_UNMAP);
			}
		}
		/* Make sure that all memory mappings within the given range have been prepared! */
		{
			struct vm_node *node = minmax.mm_min;
			for (;;) {
				assert(node->vn_vm == self);
				if (SHOULD_UPDATE(node) &&
				    (node->vn_flags & (VM_NODE_FLAG_PREPARED | VM_NODE_FLAG_PARTITIONED)) !=
				    VM_NODE_FLAG_PREPARED) {
					if unlikely(!((self == myvm || vm_node_iskernelspace(node))
					              ? pagedir_prepare_map(vm_node_getstart(node), vm_node_getsize(node))
					              : pagedir_prepare_map_p(PAGEDIR_P_SELFOFVM(self),
					                                      vm_node_getstart(node),
					                                      vm_node_getsize(node)))) {
						sync_endwrite(self);
						THROW(E_BADALLOC_INSUFFICIENT_PHYSICAL_MEMORY, PAGESIZE);
					}
				}
				if (node == minmax.mm_max)
					break;
				node = VM_NODE_NEXT(node);
			}
		}
		if (minpageid > minmax.mm_min_min) {
			/* Must split the first page. */
			if (!SHOULD_UPDATE(minmax.mm_min) || (how & VM_UNMAP_NOSPLIT)) {
				if (how & VM_UNMAP_SEGFAULTIFUNUSED)
					goto do_throw_base_unmapped;
				if (minmax.mm_min == minmax.mm_max)
					goto done;
				minmax.mm_min     = minmax.mm_min->vn_byaddr.ln_next;
				minmax.mm_min_min = vm_node_getminpageid(minmax.mm_min);
			} else if unlikely(minmax.mm_min->vn_flags & VM_NODE_FLAG_KERNPRT) {
#ifdef VM_DEFINE_PROTECT
				kernel_panic("Attempted to mprotect() a kernel part at %p...%p",
				             vm_node_getmin(minmax.mm_min),
				             vm_node_getmax(minmax.mm_min));
#else /* VM_DEFINE_PROTECT */
				kernel_panic("Attempted to munmap a kernel part at %p...%p",
				             vm_node_getmin(minmax.mm_min),
				             vm_node_getmax(minmax.mm_min));
#endif /* !VM_DEFINE_PROTECT */
#ifdef VM_DEFINE_UNMAP
			} else if (!minmax.mm_min->vn_part) {
				/* No part. -> The node can just be modified directly. */
				struct vm_node *next = minmax.mm_min->vn_byaddr.ln_next;
				vm_nodetree_remove(&self->v_tree, minmax.mm_min_min);
				LLIST_REMOVE(minmax.mm_min, vn_byaddr);
				if (maxpageid >= vm_node_getmaxpageid(minmax.mm_min)) {
					printk(KERN_DEBUG "[vm] Unmap node at %p...%p (high_part of %p...%p)\n",
					       PAGEID_DECODE(minpageid),
					       vm_node_getmax(minmax.mm_min),
					       vm_node_getmin(minmax.mm_min),
					       vm_node_getmax(minmax.mm_min));
					result += (size_t)(vm_node_getendpageid(minmax.mm_min) - minpageid);
					minmax.mm_min->vn_node.a_vmax = minpageid - 1;
					vm_node_insert(minmax.mm_min);
					minmax.mm_min     = next;
					minmax.mm_min_min = vm_node_getminpageid(next);
					assert(minmax.mm_min_min >= minpageid);
					if (minmax.mm_min == minmax.mm_max)
						goto done;
				} else {
					/* Unmap a sub-segment of a reserved memory node.
					 * For this, we need to allocate a new node to fill in the high part.
					 * LOW:  vm_node_getminpageid(minmax.mm_min) ... minpageid - 1
					 * HIGH: maxpageid + 1 ... vm_node_getminpageid(minmax.mm_min) */
					if (!new_node) {
						new_node = (struct vm_node *)kmalloc_nx(sizeof(struct vm_node),
						                                        GFP_ATOMIC | GFP_LOCKED |
						                                        GFP_PREFLT | GFP_VCBASE);
						if (!new_node) {
							sync_endwrite(self);
							new_node = (struct vm_node *)kmalloc(sizeof(struct vm_node),
							                                     GFP_LOCKED |
							                                     GFP_PREFLT | GFP_VCBASE);
							goto again_lock_vm;
						}
					}
					printk(KERN_DEBUG "Unmap node at %p...%p (sub_segment of %p...%p)\n",
					       PAGEID_DECODE(minpageid),
					       (byte_t *)PAGEID_DECODE(maxpageid + 1) - 1,
					       vm_node_getmin(minmax.mm_min),
					       vm_node_getmax(minmax.mm_min));
					assert(!(minmax.mm_min->vn_flags & VM_NODE_FLAG_HINTED));
					result                   = (size_t)(maxpageid - minpageid) + 1;
					new_node->vn_node.a_vmin = maxpageid + 1;
					new_node->vn_node.a_vmax = minmax.mm_min->vn_node.a_vmax;
					new_node->vn_prot        = minmax.mm_min->vn_prot;
					new_node->vn_flags = minmax.mm_min->vn_flags & (VM_NODE_FLAG_PREPARED |
					                                                VM_NODE_FLAG_GROWSUP |
					                                                VM_NODE_FLAG_PARTITIONED |
					                                                VM_NODE_FLAG_NOMERGE |
					                                                VM_NODE_FLAG_KERNPRT);
					minmax.mm_min->vn_flags |= VM_NODE_FLAG_PARTITIONED;
					new_node->vn_flags |= VM_NODE_FLAG_PARTITIONED;
					new_node->vn_vm               = self;
					new_node->vn_part             = NULL;
					new_node->vn_block            = xincref(minmax.mm_min->vn_block);
					new_node->vn_fspath           = xincref(minmax.mm_min->vn_fspath);
					new_node->vn_fsname           = xincref(minmax.mm_min->vn_fsname);
					new_node->vn_guard            = 0;
					minmax.mm_min->vn_node.a_vmax = minpageid - 1;
					if (minmax.mm_min->vn_guard &&
					    minmax.mm_min->vn_flags & VM_NODE_FLAG_GROWSUP) {
						new_node->vn_guard = minmax.mm_min->vn_guard;
						minmax.mm_min->vn_flags &= ~VM_NODE_FLAG_GROWSUP;
						minmax.mm_min->vn_guard = 0;
					}
					vm_node_insert(minmax.mm_min);
					vm_node_insert(new_node);
					sync_endwrite(self);
					return result;
				}
#endif /* VM_DEFINE_UNMAP */
			} else {
				REF struct vm_datapart *part;
				size_t vpage_offset;
				vpage_offset = (size_t)(minpageid - minmax.mm_min_min);
				assert(vpage_offset < vm_node_getpagecount(minmax.mm_min));
				part = incref(minmax.mm_min->vn_part);
				sync_endwrite(self);
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
		if (maxpageid < minmax.mm_max_max) {
			/* Must split the last page. */
			if (!SHOULD_UPDATE(minmax.mm_max) || (how & VM_UNMAP_NOSPLIT)) {
				if (how & VM_UNMAP_SEGFAULTIFUNUSED)
					goto do_throw_base_unmapped;
				if (minmax.mm_min == minmax.mm_max)
					goto done;
				minmax.mm_max     = VM_NODE_PREV(minmax.mm_max);
				minmax.mm_max_max = vm_node_getmaxpageid(minmax.mm_max);
			} else if unlikely(minmax.mm_max->vn_flags & VM_NODE_FLAG_KERNPRT) {
#ifdef VM_DEFINE_PROTECT
				kernel_panic("Attempted to mprotect() a kernel part at %p...%p",
				             vm_node_getmin(minmax.mm_max),
				             vm_node_getmax(minmax.mm_max));
#else /* VM_DEFINE_PROTECT */
				kernel_panic("Attempted to munmap() a kernel part at %p...%p",
				             vm_node_getmin(minmax.mm_max),
				             vm_node_getmax(minmax.mm_max));
#endif /* !VM_DEFINE_PROTECT */
#ifdef VM_DEFINE_UNMAP
			} else if (!minmax.mm_max->vn_part) {
				/* No part. -> The node can just be modified directly. */
				struct vm_node *prev = VM_NODE_PREV(minmax.mm_max);
				vm_nodetree_remove(&self->v_tree, minmax.mm_max_max);
				LLIST_REMOVE(minmax.mm_max, vn_byaddr);
				assert(minpageid <= vm_node_getminpageid(minmax.mm_max));
				printk(KERN_DEBUG "Unmap node at %p...%p (low_part of %p...%p)\n",
				       vm_node_getminpageid(minmax.mm_max),
				       (byte_t *)PAGEID_DECODE(maxpageid + 1) - 1,
				       vm_node_getminpageid(minmax.mm_max),
				       vm_node_getmaxpageid(minmax.mm_max));
				result += (size_t)((maxpageid + 1) - vm_node_getminpageid(minmax.mm_max));
				minmax.mm_max->vn_node.a_vmin = maxpageid + 1;
				vm_node_insert(minmax.mm_max);
				minmax.mm_max     = prev;
				minmax.mm_max_max = vm_node_getmaxpageid(prev);
				assert(minmax.mm_max_max <= maxpageid);
				if (minmax.mm_min == minmax.mm_max)
					goto done;
#endif /* VM_DEFINE_UNMAP */
			} else {
				REF struct vm_datapart *part;
				size_t vpage_offset;
				vpage_offset = (size_t)((maxpageid + 1) - vm_node_getstartpageid(minmax.mm_max));
				assert(vpage_offset < vm_node_getpagecount(minmax.mm_max));
				part = incref(minmax.mm_max->vn_part);
				sync_endwrite(self);
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
				assert(node->vn_vm == self);
				if (SHOULD_UPDATE(node)) {
#ifdef VM_DEFINE_PROTECT
					uintptr_half_t old_prot;
					uintptr_half_t new_prot;
#endif /* VM_DEFINE_PROTECT */
					assert(vm_node_getminpageid(node) >= minpageid);
					assert(vm_node_getmaxpageid(node) <= maxpageid);
					/* Update this node! */
					if unlikely(node->vn_flags & VM_NODE_FLAG_KERNPRT) {
#ifdef VM_DEFINE_PROTECT
						kernel_panic("Attempted to mprotect() a kernel part at %p...%p",
						             vm_node_getmin(node), vm_node_getmax(node));
#else /* VM_DEFINE_PROTECT */
						kernel_panic("Attempted to munmap() a kernel part at %p...%p",
						             vm_node_getmin(node), vm_node_getmax(node));
#endif /* !VM_DEFINE_PROTECT */
					}
#ifdef VM_DEFINE_UNMAP
					printk(KERN_DEBUG "Unmap node at %p...%p\n",
					       vm_node_getmin(node), vm_node_getmax(node));
#endif /* VM_DEFINE_UNMAP */
					result += vm_node_getpagecount(node);
#ifdef VM_DEFINE_PROTECT
					old_prot = node->vn_prot;
					new_prot = (old_prot & prot_mask) | prot_flags;
					printk(KERN_DEBUG "Mprotect node at %p...%p [%c%c%c%c%c to %c%c%c%c%c]\n",
					       vm_node_getmin(node), vm_node_getmax(node),
					       old_prot & VM_PROT_SHARED ? 's' : '-', old_prot & VM_PROT_LOOSE ? 'l' : '-',
					       old_prot & VM_PROT_READ ? 'r' : '-', old_prot & VM_PROT_WRITE ? 'w' : '-',
					       old_prot & VM_PROT_EXEC ? 'x' : '-',
					       new_prot & VM_PROT_SHARED ? 's' : '-', new_prot & VM_PROT_LOOSE ? 'l' : '-',
					       new_prot & VM_PROT_READ ? 'r' : '-', new_prot & VM_PROT_WRITE ? 'w' : '-',
					       new_prot & VM_PROT_EXEC ? 'x' : '-');
					if ((old_prot & VM_PROT_SHARED) != (new_prot & VM_PROT_SHARED)) {
						/* PRIVATE <---> SHARED mapping change. */
						if (node->vn_part != NULL) {
							struct vm_datapart *part = node->vn_part;
							if (!sync_trywrite(part)) {
								incref(part);
								sync_endwrite(self);
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
										                                              self);
										if unlikely(error != VM_NODE_UPDATE_WRITE_ACCESS_SUCCESS) {
											REF struct vm *blocking_vm;
											if (error == VM_NODE_UPDATE_WRITE_ACCESS_BADALLOC) {
												sync_endwrite(part);
												sync_endwrite(self);
												THROW(E_BADALLOC_INSUFFICIENT_PHYSICAL_MEMORY, PAGESIZE);
											}
											blocking_vm = sibling_shared->vn_vm;
											if (!tryincref(blocking_vm))
												blocking_vm = NULL;
											sync_endwrite(part);
											sync_endwrite(self);
											assert(error == VM_NODE_UPDATE_WRITE_ACCESS_WOULDBLOCK);
											if (blocking_vm) {
												FINALLY_DECREF_UNLIKELY(blocking_vm);
												sync_write(blocking_vm);
												sync_endwrite(blocking_vm);
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

					if (self == myvm || vm_node_iskernelspace(node)) {
						pagedir_unmap(vm_node_getstart(node),
						              vm_node_getsize(node));
					} else {
						pagedir_unmap_p(PAGEDIR_P_SELFOFVM(self),
						                vm_node_getstart(node),
						                vm_node_getsize(node));
					}
					must_sync = true;
#ifdef VM_DEFINE_UNMAP
					/* Remove the node from the VM. */
					vm_nodetree_remove(&self->v_tree, vm_node_getstartpageid(node));
					LLIST_REMOVE(node, vn_byaddr);
					/* Destroy the old node. NOTE: This _MUST_ be done before we `sync_endwrite(self)',
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
	if (must_sync) {
		vm_sync(self,
		        PAGEID_DECODE(minpageid),
		        ((size_t)(maxpageid - minpageid) + 1) * PAGESIZE);
	}
done:
	sync_endwrite(self);
	if unlikely(new_node)
		kfree(new_node);
	return result;
#undef SHOULD_UPDATE
}


#undef VM_DEFINE_PROTECT
#undef VM_DEFINE_UNMAP

DECL_END



