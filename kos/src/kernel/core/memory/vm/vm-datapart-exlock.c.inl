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
#define EXLOCK_NX 1
#endif

DECL_BEGIN

/* Switch `self' to INCORE/LOCKED, using a write-lock provided by the caller.
 * NOTE: In the event of this function throwing an exception, the lock provided
 *       by the caller will have already been released!
 * @return: * : One of `VM_DATAPART_DO_SETCORE_*' */
PRIVATE NONNULL((1)) unsigned int
#ifdef EXLOCK_NX
NOTHROW(FCALL vm_datapart_do_setcore_nx)(struct vm_datapart *__restrict self)
#else /* EXLOCK_NX */
FCALL vm_datapart_do_setcore(struct vm_datapart *__restrict self)
		THROWS(E_WOULDBLOCK, E_BADALLOC)
#endif /* !EXLOCK_NX */
{
	unsigned int result;
	struct vm_ramblock block0;
	struct vm_ramblock *blocks;
	size_t num_pages;
	assert(self->dp_state != VM_DATAPART_STATE_INCORE &&
	       self->dp_state != VM_DATAPART_STATE_LOCKED);
	result    = VM_DATAPART_DO_SETCORE_SUCCESS;
	num_pages = vm_datapart_numvpages(self);
#ifndef CONFIG_NO_SWAP
	if (self->dp_state == VM_DATAPART_STATE_INSWAP) {
do_load_swap:
		blocks = vm_do_allocram_nx(&block0,
		                           vm_datapart_numvpages(self),
		                           GFP_ATOMIC | GFP_LOCKED |
		                           GFP_PREFLT | GFP_VCBASE);
		if (!blocks) {
			/* Must unlock and try to allocate again. */
			sync_endwrite(self);
			result = VM_DATAPART_DO_SETCORE_SUCCESS_RELOCKED;
#ifdef EXLOCK_NX
			blocks = vm_do_allocram_nx(&block0,
			                           num_pages,
			                           GFP_LOCKED | GFP_PREFLT | GFP_VCBASE);
			if unlikely(!blocks)
				return VM_DATAPART_DO_SETCORE_FAILED;
			if unlikely(!sync_write_nx(self)) {
				vm_do_ccfreeram(&block0, blocks);
				return VM_DATAPART_DO_SETCORE_FAILED;
			}
#else /* EXLOCK_NX */
			blocks = vm_do_allocram(&block0,
			                        num_pages,
			                        GFP_LOCKED | GFP_PREFLT | GFP_VCBASE);
			TRY {
				sync_write(self);
			} EXCEPT {
				vm_do_ccfreeram(&block0, blocks);
				RETHROW();
			}
#endif /* !EXLOCK_NX */
			COMPILER_READ_BARRIER();
			if unlikely(self->dp_state != VM_DATAPART_STATE_INSWAP) {
				if (self->dp_state == VM_DATAPART_STATE_ABSENT) {
					if (num_pages == vm_datapart_numvpages(self))
						goto do_load_absent_hasblocks;
					vm_do_ccfreeram(&block0, blocks);
					goto do_load_absent;
				}
				vm_do_ccfreeram(&block0, blocks);
				assert(self->dp_state == VM_DATAPART_STATE_INCORE ||
				       self->dp_state == VM_DATAPART_STATE_LOCKED);
				return VM_DATAPART_DO_SETCORE_SUCCESS_RELOCKED;
			}
		}
do_load_swap_hasblocks:
		assert(self->dp_state == VM_DATAPART_STATE_INSWAP);
		/* TODO: swap_read(); */
		self->dp_ramdata.rd_block0 = block0;
		self->dp_ramdata.rd_blockv = blocks; /* Inherit */
		self->dp_state = self->dp_flags & VM_DATAPART_FLAG_LOCKED
		                 ? VM_DATAPART_STATE_LOCKED
		                 : VM_DATAPART_STATE_INCORE;
	} else
#endif /* !CONFIG_NO_SWAP */
	{
		assert(self->dp_state == VM_DATAPART_STATE_ABSENT);
#ifndef CONFIG_NO_SWAP
do_load_absent:
#endif /* !CONFIG_NO_SWAP */
		blocks = vm_do_allocram_nx(&self->dp_ramdata.rd_block0,
		                           num_pages,
		                           GFP_ATOMIC | GFP_LOCKED |
		                           GFP_PREFLT | GFP_VCBASE);
#ifndef CONFIG_NO_SWAP
do_load_absent_hasblocks:
#endif /* !CONFIG_NO_SWAP */
		if (!blocks) {
			/* Must unlock and try to allocate again. */
			sync_endwrite(self);
			result = VM_DATAPART_DO_SETCORE_SUCCESS_RELOCKED;
#ifdef EXLOCK_NX
			blocks = vm_do_allocram_nx(&block0,
			                           num_pages,
			                           GFP_LOCKED | GFP_PREFLT | GFP_VCBASE);
			if unlikely(!blocks)
				return VM_DATAPART_DO_SETCORE_FAILED;
			if unlikely(!sync_write_nx(self)) {
				vm_do_ccfreeram(&block0, blocks);
				return VM_DATAPART_DO_SETCORE_FAILED;
			}
#else /* EXLOCK_NX */
			blocks = vm_do_allocram(&block0,
			                        num_pages,
			                        GFP_LOCKED | GFP_PREFLT | GFP_VCBASE);
			TRY {
				sync_write(self);
			} EXCEPT {
				vm_do_ccfreeram(&block0, blocks);
				RETHROW();
			}
#endif /* !EXLOCK_NX */
			COMPILER_READ_BARRIER();
			if unlikely(self->dp_state != VM_DATAPART_STATE_ABSENT) {
#ifndef CONFIG_NO_SWAP
				if (self->dp_state == VM_DATAPART_STATE_INSWAP) {
					if (num_pages == vm_datapart_numvpages(self))
						goto do_load_swap_hasblocks;
					vm_do_ccfreeram(&block0, blocks);
					goto do_load_swap;
				}
#endif /* !CONFIG_NO_SWAP */
				vm_do_ccfreeram(&block0, blocks);
				assert(self->dp_state == VM_DATAPART_STATE_INCORE ||
				       self->dp_state == VM_DATAPART_STATE_LOCKED);
				return VM_DATAPART_DO_SETCORE_SUCCESS_RELOCKED;
			}
			self->dp_ramdata.rd_block0 = block0;
		}
		self->dp_ramdata.rd_blockv = blocks; /* Inherit */
		self->dp_state             = self->dp_flags & VM_DATAPART_FLAG_LOCKED
		                 ? VM_DATAPART_STATE_LOCKED
		                 : VM_DATAPART_STATE_INCORE;
	}
	return result;
}





/* Unshare any existing copy-on-write mappings which may be mapped to `self'
 * @return: * : One of `VM_DATAPART_DO_UNSHARE_COW_*' */
PRIVATE NONNULL((1)) unsigned int
#ifdef EXLOCK_NX
NOTHROW(FCALL vm_datapart_do_unshare_cow_nx)(struct vm_datapart *__restrict self)
#else /* EXLOCK_NX */
FCALL vm_datapart_do_unshare_cow(struct vm_datapart *__restrict self)
		THROWS(E_WOULDBLOCK, E_BADALLOC)
#endif /* !EXLOCK_NX */
{
	struct vm_datapart *copy;
	unsigned int result;
	size_t num_pages, vms_count;
	size_t num_dpages;
	struct pointer_set vms;
	assert(self->dp_crefs != NULL);
	assert(self->dp_state == VM_DATAPART_STATE_INCORE ||
	       self->dp_state == VM_DATAPART_STATE_LOCKED);
	result = VM_DATAPART_DO_UNSHARE_COW_SUCCESS;
	pointer_set_init(&vms);
	copy = (struct vm_datapart *)kmalloc_nx(sizeof(struct vm_datapart),
	                                        GFP_ATOMIC | GFP_LOCKED |
	                                        GFP_PREFLT | GFP_VCBASE);
#ifndef EXLOCK_NX
	TRY
#endif /* !EXLOCK_NX */
	{
		num_dpages = vm_datapart_numdpages(self);
		num_pages  = num_dpages >> VM_DATABLOCK_PAGESHIFT(self->dp_block);
		if (!copy) {
			sync_endwrite(self);
#ifdef EXLOCK_NX
			copy = (struct vm_datapart *)kmalloc_nx(sizeof(struct vm_datapart),
			                                        GFP_LOCKED | GFP_PREFLT |
			                                        GFP_VCBASE);
			if unlikely(!copy)
				goto err_vms;
#else /* EXLOCK_NX */
			copy = (struct vm_datapart *)kmalloc(sizeof(struct vm_datapart),
			                                     GFP_LOCKED | GFP_PREFLT |
			                                     GFP_VCBASE);
#endif /* !EXLOCK_NX */
alloc_part_copy_ramdata:
#ifdef EXLOCK_NX
			copy->dp_ramdata.rd_blockv = vm_do_allocram_nx(&copy->dp_ramdata.rd_block0,
			                                               num_pages,
			                                               GFP_LOCKED | GFP_PREFLT |
			                                               GFP_VCBASE);
			if unlikely(!copy->dp_ramdata.rd_blockv)
				goto err_vms_copy;
#else /* EXLOCK_NX */
			TRY {
				copy->dp_ramdata.rd_blockv = vm_do_allocram(&copy->dp_ramdata.rd_block0,
				                                            num_pages,
				                                            GFP_LOCKED | GFP_PREFLT |
				                                            GFP_VCBASE);
			} EXCEPT {
				kfree(copy);
				RETHROW();
			}
#endif /* !EXLOCK_NX */
alloc_part_copy_ppp:
			copy->dp_flags = VM_DATAPART_FLAG_NORMAL;
			if (num_dpages <= BITSOF(uintptr_t) / VM_DATAPART_PPP_BITS) {
			} else {
				/* Need to allocate a page property bitset as part of the heap! */
				size_t ppp_size;
				copy->dp_flags = (VM_DATAPART_FLAG_NORMAL | VM_DATAPART_FLAG_HEAPPPP);
				ppp_size       = CEILDIV(num_dpages, BITSOF(uintptr_t) / VM_DATAPART_PPP_BITS) * sizeof(uintptr_t);
#ifdef EXLOCK_NX
				copy->dp_pprop_p = (uintptr_t *)kmalloc_nx(ppp_size,
				                                           GFP_CALLOC | GFP_LOCKED |
				                                           GFP_PREFLT | GFP_VCBASE);
				if unlikely(!copy->dp_pprop_p)
					goto err_vms_copy_ramdata;
#else /* EXLOCK_NX */
				TRY {
					copy->dp_pprop_p = (uintptr_t *)kmalloc(ppp_size,
					                                        GFP_CALLOC | GFP_LOCKED |
					                                        GFP_PREFLT | GFP_VCBASE);
				} EXCEPT {
					vm_do_ccfreeram(&copy->dp_ramdata.rd_block0,
					                copy->dp_ramdata.rd_blockv);
					kfree(copy);
					RETHROW();
				}
#endif /* !EXLOCK_NX */
			}
#ifdef EXLOCK_NX
			if unlikely(!sync_write_nx(self))
				goto err_vms_copy_ramdata_ppp;
#else /* EXLOCK_NX */
			TRY {
				sync_write(self);
			} EXCEPT {
				if (copy->dp_flags & VM_DATAPART_FLAG_HEAPPPP)
					kfree(copy->dp_pprop_p);
				vm_do_ccfreeram(&copy->dp_ramdata.rd_block0,
				                copy->dp_ramdata.rd_blockv);
				kfree(copy);
				RETHROW();
			}
#endif /* !EXLOCK_NX */
			COMPILER_READ_BARRIER();
			result = VM_DATAPART_DO_UNSHARE_COW_SUCCESS_RELOCKED;
			if unlikely(self->dp_state != VM_DATAPART_STATE_INCORE &&
			            self->dp_state != VM_DATAPART_STATE_LOCKED) {
				result = VM_DATAPART_DO_UNSHARE_COW_CHANGED;
return_direct_locked:
				if (copy->dp_flags & VM_DATAPART_FLAG_HEAPPPP)
					kfree(copy->dp_pprop_p);
				vm_do_ccfreeram(&copy->dp_ramdata.rd_block0,
				                copy->dp_ramdata.rd_blockv);
				kfree(copy);
				return result;
			}
			if unlikely(!self->dp_crefs)
				goto return_direct_locked;
			if unlikely(num_dpages != vm_datapart_numdpages(self)) {
				if (copy->dp_flags & VM_DATAPART_FLAG_HEAPPPP)
					kfree(copy->dp_pprop_p);
				vm_do_ccfreeram(&copy->dp_ramdata.rd_block0,
				                copy->dp_ramdata.rd_blockv);
				goto alloc_part_copy_ramdata;
			}
		} else {
			copy->dp_ramdata.rd_blockv = vm_do_allocram_nx(&copy->dp_ramdata.rd_block0,
			                                               num_pages,
			                                               GFP_ATOMIC | GFP_LOCKED |
			                                               GFP_PREFLT | GFP_VCBASE);
			if (!copy->dp_ramdata.rd_blockv) {
				sync_endwrite(self);
				goto alloc_part_copy_ramdata;
			}
			copy->dp_flags = VM_DATAPART_FLAG_NORMAL;
			if (num_dpages <= BITSOF(uintptr_t) / VM_DATAPART_PPP_BITS)
				;
			else {
				/* Need to allocate a page property bitset as part of the heap! */
				size_t ppp_size;
				copy->dp_flags   = (VM_DATAPART_FLAG_NORMAL | VM_DATAPART_FLAG_HEAPPPP);
				ppp_size         = CEILDIV(num_dpages, BITSOF(uintptr_t) / VM_DATAPART_PPP_BITS) * sizeof(uintptr_t);
				copy->dp_pprop_p = (uintptr_t *)kmalloc_nx(ppp_size,
				                                           GFP_ATOMIC | GFP_CALLOC | GFP_LOCKED |
				                                           GFP_PREFLT | GFP_VCBASE);
				if (!copy->dp_pprop_p) {
					sync_endwrite(self);
					goto alloc_part_copy_ppp;
				}
			}
		}
#ifndef EXLOCK_NX
		TRY
#endif /* !EXLOCK_NX */
		{
			struct vm *v;
			struct vm_node *node;
			u16 perm_mask;
again_scan_nodes:
			assert(self->dp_crefs != NULL);
			vms_count = vm_set_collect_from_datapart_crefs(&vms, self);
			if unlikely(vms_count > vms.ps_size) {
				sync_endwrite(self);
				pointer_set_reset_rehash(&vms, vms_count, GFP_LOCKED);
				goto again_lock_datapart;
			}
			/* Acquire write-locks to all of the VMs affected. */
			v = vm_set_locktrywrite_all(&vms);
			if unlikely(v) {
				incref(v);
				sync_endwrite(self);
#ifdef EXLOCK_NX
				if unlikely(!sync_write_nx(v)) {
					decref(v);
					goto err_vms_copy_ramdata_ppp;
				}
#else /* EXLOCK_NX */
				TRY {
					sync_write(v);
				} EXCEPT {
					decref(v);
					RETHROW();
				}
#endif /* !EXLOCK_NX */
				sync_endwrite(v);
				decref(v);
				goto again_lock_datapart;
			}
			/* Initialize the copied datapart. */
			copy->dp_refcnt = 0; /* Incremented for each node below... */
			shared_rwlock_init(&copy->dp_lock);
			copy->dp_tree.a_vmin = self->dp_tree.a_vmin;
			copy->dp_tree.a_vmax = self->dp_tree.a_vmax;
#ifndef NDEBUG
			memset(&copy->dp_tree.a_min, 0xcc, sizeof(copy->dp_tree.a_min));
			memset(&copy->dp_tree.a_max, 0xcc, sizeof(copy->dp_tree.a_max));
#endif /* !NDEBUG */
			copy->dp_crefs = node = self->dp_crefs;
			copy->dp_srefs = NULL;
			copy->dp_stale = NULL;
			copy->dp_block = incref(&vm_datablock_anonymous_zero_vec[self->dp_block->db_pageshift]);
			copy->dp_flags |= self->dp_flags & (VM_DATAPART_FLAG_LOCKED |
			                                    VM_DATAPART_FLAG_CHANGED |
			                                    VM_DATAPART_FLAG_KERNPRT);
			copy->dp_state = self->dp_state;
			assert(copy->dp_state == VM_DATAPART_STATE_INCORE ||
			       copy->dp_state == VM_DATAPART_STATE_LOCKED);
			copy->dp_futex = NULL; /* Unshare futex operations. */
			if (copy->dp_flags & VM_DATAPART_FLAG_HEAPPPP) {
				assert(self->dp_flags & VM_DATAPART_FLAG_HEAPPPP);
				memcpy(copy->dp_pprop_p, self->dp_pprop_p,
				       CEILDIV(num_dpages, BITSOF(uintptr_t) / VM_DATAPART_PPP_BITS),
				       sizeof(uintptr_t));
			} else {
				copy->dp_pprop = self->dp_flags & VM_DATAPART_FLAG_HEAPPPP
				                 ? self->dp_pprop_p[0]
				                 : self->dp_pprop;
			}
			/* Copy the physical memory used to back the data of `self' */
			vm_datapart_do_copyram(copy,
			                       self);

			/* Update the node bindings of all of the affected
			 * VMs to point to `copy', rather than `self' */
			assert(node);
			assert(node == self->dp_crefs);
			assert(node == copy->dp_crefs);
			assert(node->vn_link.ln_pself == &self->dp_crefs);
			/* Check for stale nodes, so-as to ensure that we're not accidentally updating an unmapped node. */
			if unlikely(VM_DATAPART_MUST_SERVICE_STALE(self)) {
				vm_set_lockendwrite_all(&vms);
				sync_endwrite(self);
				goto again_lock_datapart;
			}
			v = THIS_VM;
			do {
				if unlikely(wasdestroyed(node->vn_vm))
					continue;
				/* Must re-prepare the address range before we
				 * can safely load new physical memory targets. */
				if unlikely(!(node->vn_vm == v || node->vn_vm == &vm_kernel
				              ? pagedir_prepare_map(vm_node_getstart(node), vm_node_getsize(node))
				              : pagedir_prepare_map_p(PAGEDIR_P_SELFOFVM(node->vn_vm),
				                                      vm_node_getstart(node),
				                                      vm_node_getsize(node)))) {
					vm_set_lockendwrite_all(&vms);
#ifdef EXLOCK_NX
					goto err_vms_copy_ramdata_ppp;
#else /* EXLOCK_NX */
					THROW(E_BADALLOC_INSUFFICIENT_PHYSICAL_MEMORY, PAGESIZE);
#endif /* !EXLOCK_NX */
				}
			} while ((node = node->vn_link.ln_next) != NULL);
			node                   = self->dp_crefs;
			self->dp_crefs         = NULL;
			node->vn_link.ln_pself = &copy->dp_crefs;
			perm_mask              = VM_PROT_READ | VM_PROT_WRITE | VM_PROT_SHARED;
			if (node->vn_link.ln_next != NULL)
				perm_mask &= ~VM_PROT_WRITE; /* More than one mapping remains (COW must remain enabled) */
			do {
				u16 perm;
				if unlikely(wasdestroyed(node->vn_vm))
					continue;
				decref_nokill(self); /* node->vn_part */
				node->vn_part = incref(copy);
				/* Must update the page directory mapping targets to instead map to the copy
				 * that we've just created, rather than keep on referring to the shared instance. */
				perm = node->vn_prot & perm_mask;
				if (node->vn_vm != &vm_kernel)
					perm |= PAGEDIR_MAP_FUSER;
				if (node->vn_vm == v || node->vn_vm == &vm_kernel) {
					vm_datapart_map_ram_autoprop(copy, vm_node_getstart(node), perm);
					pagedir_sync(vm_node_getstart(node), vm_node_getsize(node));
				} else {
					vm_datapart_map_ram_autoprop_p(copy,
					                               PAGEDIR_P_SELFOFVM(node->vn_vm),
					                               vm_node_getstart(node),
					                               perm);
				}
			} while ((node = node->vn_link.ln_next) != NULL);

			/* Unlock all of the VMs that were mapping the node as copy-on-write */
			vm_set_lockendwrite_all(&vms);
			pointer_set_fini(&vms);
			return result;
again_lock_datapart:
			sync_write(self);
			COMPILER_READ_BARRIER();
			if unlikely(self->dp_state != VM_DATAPART_STATE_INCORE &&
			            self->dp_state != VM_DATAPART_STATE_LOCKED) {
				vm_do_ccfreeram(&copy->dp_ramdata.rd_block0,
				                copy->dp_ramdata.rd_blockv);
				kfree(copy);
				pointer_set_fini(&vms);
				return VM_DATAPART_DO_UNSHARE_COW_CHANGED;
			}
			if unlikely(!self->dp_crefs) {
				vm_do_ccfreeram(&copy->dp_ramdata.rd_block0,
				                copy->dp_ramdata.rd_blockv);
				kfree(copy);
				pointer_set_fini(&vms);
				return VM_DATAPART_DO_UNSHARE_COW_SUCCESS_RELOCKED;
			}
			goto again_scan_nodes;
		}
#ifdef EXLOCK_NX
err_vms_copy_ramdata_ppp:
		if (copy->dp_flags & VM_DATAPART_FLAG_HEAPPPP)
			kfree(copy->dp_pprop_p);
err_vms_copy_ramdata:
		vm_do_ccfreeram(&copy->dp_ramdata.rd_block0,
		                copy->dp_ramdata.rd_blockv);
err_vms_copy:
		kfree(copy);
#else /* EXLOCK_NX */
		EXCEPT {
			if (copy->dp_flags & VM_DATAPART_FLAG_HEAPPPP)
				kfree(copy->dp_pprop_p);
			vm_do_ccfreeram(&copy->dp_ramdata.rd_block0,
			                copy->dp_ramdata.rd_blockv);
			kfree(copy);
			RETHROW();
		}
#endif /* !EXLOCK_NX */
	}
#ifdef EXLOCK_NX
err_vms:
	pointer_set_fini(&vms);
	return VM_DATAPART_DO_UNSHARE_COW_FAILED;
#else /* EXLOCK_NX */
	EXCEPT {
		pointer_set_fini(&vms);
		RETHROW();
	}
#endif /* !EXLOCK_NX */
}


DECL_END

#undef EXLOCK_NX
