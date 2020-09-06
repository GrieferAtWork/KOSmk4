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
//#define SPLIT_NX 1
#endif

#include <hybrid/align.h>

#include <assert.h>
#include <string.h>

DECL_BEGIN

#ifndef SPLIT_FUTEX_HELPERS_DEFINED
#define SPLIT_FUTEX_HELPERS_DEFINED 1

PRIVATE NOBLOCK NONNULL((1)) struct vm_futex **
NOTHROW(KCALL vm_futextree_prlocate_at_at_not_destroyed)(struct vm_futex **__restrict proot,
                                                         uintptr_t key_min, uintptr_t key_max,
                                                         uintptr_t *__restrict paddr_semi,
                                                         unsigned int *__restrict paddr_level) {
	struct vm_futex *root;
	uintptr_t addr_semi = *paddr_semi;
	unsigned int addr_level = *paddr_level;
	/* addr_semi is the center point splitting the max
	 * ranges of the underlying sb_min/sb_max branches. */
	while ((root = *proot) != NULL) {
		/* Check if the given key lies within this branch. */
		if (key_min <= root->f_tree.a_vaddr &&
		    key_max >= root->f_tree.a_vaddr) {
			if (!wasdestroyed(root)) {
				*paddr_semi  = addr_semi;
				*paddr_level = addr_level;
				return proot;
			}
		}
		assertf(addr_level != (ATREE_LEVEL_T)-1,
		        "proot      = %p\n"
		        "*proot     = %p\n"
		        "key_min    = %p\n"
		        "key_max    = %p\n"
		        "addr_semi  = %p\n",
		        proot, *proot,
		        key_min,
		        key_max,
		        addr_semi);
		if (key_min < addr_semi) {
			if (key_max >= addr_semi) {
				struct vm_futex **result;
				/* Also search the max-branch */
				uintptr_t temp_semi = addr_semi;
				unsigned int temp_level = addr_level;
				ATREE_WALKMAX(uintptr_t, temp_semi, temp_level);
				result = vm_futextree_prlocate_at_at_not_destroyed(&root->f_tree.a_max,
				                                                   key_min, key_max,
				                                                   &temp_semi, &temp_level);
				if (result != NULL) {
					*paddr_semi  = temp_semi;
					*paddr_level = temp_level;
					return result;
				}
			}
			/* Continue with min-branch */
			ATREE_WALKMIN(uintptr_t, addr_semi, addr_level);
			proot = &root->f_tree.a_min;
		} else {
			/* Continue with max-branch */
			ATREE_WALKMAX(uintptr_t, addr_semi, addr_level);
			proot = &root->f_tree.a_max;
		}
	}
	return NULL;
}

PRIVATE NOBLOCK NONNULL((1)) struct vm_futex *
NOTHROW(KCALL vm_futextree_rremove_at_not_destroyed)(struct vm_futex **__restrict proot,
                                                     uintptr_t key_min, uintptr_t key_max,
                                                     uintptr_t addr_semi,
                                                     unsigned int addr_level) {
	struct vm_futex **remove_head;
	remove_head = vm_futextree_prlocate_at_at_not_destroyed(proot,
	                                                        key_min, key_max,
	                                                        &addr_semi, &addr_level);
	return remove_head != NULL
	       ? vm_futextree_pop_at(remove_head, addr_semi, addr_level)
	       : NULL;
}

/* Try to increment the reference counters of all futex objects and
 * keep track of those with the lowest and greatest addresses, updating
 * the given `p(min|max)addr' pointers as needed.
 * @return: true:  No destroyed futex objects exist.
 * @return: false: At least one futex object wasn't incref'd because it was already destroyed. */
PRIVATE NOBLOCK NONNULL((1, 2, 3)) bool
NOTHROW(KCALL vm_futextree_tryincref_all_and_collect_minmax)(struct vm_futex *__restrict tree,
                                                             uintptr_t *__restrict pminaddr,
                                                             uintptr_t *__restrict pmaxaddr
#ifndef NDEBUG
                                                             ,
                                                             struct vm_datapart *__restrict expected_part
#endif /* !NDEBUG */
                                                             ) {
	bool result = true;
again:
#ifndef NDEBUG
	assert(tree->f_part.m_pointer == expected_part);
#endif /* !NDEBUG */
	/* Try to acquire a reference (Only update min/max or alive futex objects) */
	if (tryincref(tree)) {
		/* Keep track of the lowest and greatest address
		 * that is bound to a futex that is still alive. */
		uintptr_t addr = tree->f_tree.a_vaddr;
		if (*pminaddr > addr)
			*pminaddr = addr;
		if (*pmaxaddr < addr)
			*pmaxaddr = addr;
	} else {
		result = false;
	}
	if (tree->f_tree.a_min) {
		if (tree->f_tree.a_max) {
			result &= vm_futextree_tryincref_all_and_collect_minmax(tree->f_tree.a_max,
			                                                        pminaddr,
			                                                        pmaxaddr
#ifndef NDEBUG
			                                                        ,
			                                                        expected_part
#endif /* !NDEBUG */
			                                                        );
		}
		tree = tree->f_tree.a_min;
		goto again;
	}
	if (tree->f_tree.a_max) {
		tree = tree->f_tree.a_max;
		goto again;
	}
	return result;
}


/* Subtract `bytes_to_subtract' from all futex objects,
 * then insert them into the given `*pnew_tree' */
PRIVATE NOBLOCK NONNULL((1, 2)) void
NOTHROW(KCALL vm_futextree_subtract_addr_and_reform_tree)(struct vm_futex *__restrict tree,
                                                          struct vm_futex **__restrict pnew_tree,
                                                          uintptr_t bytes_to_subtract,
                                                          uintptr_t new_tree_semi0,
                                                          unsigned int new_tree_level0) {
	struct vm_futex *lo, *hi;
again:
	lo = tree->f_tree.a_min;
	hi = tree->f_tree.a_max;
	assert(!wasdestroyed(tree));
	assert(tree->f_tree.a_vaddr >= bytes_to_subtract);
	/* Update the leaf's address. */
	tree->f_tree.a_vaddr -= bytes_to_subtract;
	/* Insert the leaf into the new tree. */
	vm_futextree_insert_at(pnew_tree, tree,
	                       new_tree_semi0,
	                       new_tree_level0);
	/* Recurse through all leaves. */
	if (hi) {
		if (lo) {
			vm_futextree_subtract_addr_and_reform_tree(lo, pnew_tree,
			                                           bytes_to_subtract,
			                                           new_tree_semi0,
			                                           new_tree_level0);
		}
		tree = hi;
		goto again;
	}
	if (lo) {
		tree = lo;
		goto again;
	}
}


/* Decrement the reference counter of each futex object
 * that hasn't been destroyed within the tree. */
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL vm_futextree_decref_all_if_not_destroyed)(struct vm_futex *__restrict tree
#ifndef NDEBUG
                                                        ,
                                                        struct vm_datapart *__restrict expected_part
#endif /* !NDEBUG */
                                                        ) {
	/* Note that even when a futex object gets destroyed due to this, we can
	 * assume that the tree pointers will not affected because the caller is
	 * still holding a lock to the associated `expected_part', meaning that
	 * `vm_futex_destroy()' isn't allowed to modify the tree. */
again:
#ifndef NDEBUG
	assert(tree->f_part.m_pointer == expected_part);
#endif /* !NDEBUG */
	if (!wasdestroyed(tree))
		decref_unlikely(tree);
	if (tree->f_tree.a_min) {
		if (tree->f_tree.a_max) {
			vm_futextree_decref_all_if_not_destroyed(tree->f_tree.a_max
#ifndef NDEBUG
			                                         ,
			                                         expected_part
#endif /* !NDEBUG */
			                                         );
		}
		tree = tree->f_tree.a_min;
		goto again;
	}
	if (tree->f_tree.a_max) {
		tree = tree->f_tree.a_max;
		goto again;
	}
}

PRIVATE NOBLOCK NONNULL((1, 2)) void
NOTHROW(KCALL vm_futextree_set_part_pointer_and_decref_all)(struct vm_futex *__restrict tree,
                                                            struct vm_datapart *__restrict new_part_pointer
#ifndef NDEBUG
                                                            ,
                                                            struct vm_datapart *__restrict expected_part
#endif /* !NDEBUG */
                                                            ) {
	/* Note that even when a futex object gets destroyed due to this, we can
	 * assume that the tree pointers will not affected because the caller is
	 * still holding a lock to the associated `expected_part', meaning that
	 * `vm_futex_destroy()' isn't allowed to modify the tree. */
again:
#ifndef NDEBUG
	assert(tree->f_part.m_pointer == expected_part);
#endif /* !NDEBUG */
	assert(!wasdestroyed(tree));
	/* Set the new part pointer (such that it now points to the upper-half datapart) */
	tree->f_part.set(new_part_pointer);
	decref_unlikely(tree);
	if (tree->f_tree.a_min) {
		if (tree->f_tree.a_max) {
			vm_futextree_set_part_pointer_and_decref_all(tree->f_tree.a_max,
			                                             new_part_pointer
#ifndef NDEBUG
			                                             ,
			                                             expected_part
#endif /* !NDEBUG */
			                                             );
		}
		tree = tree->f_tree.a_min;
		goto again;
	}
	if (tree->f_tree.a_max) {
		tree = tree->f_tree.a_max;
		goto again;
	}
}

#endif /* !SPLIT_FUTEX_HELPERS_DEFINED */


#ifdef SPLIT_NX
/* Same as `vm_datapart_split()', but don't block or throw an exception if something
 * goes wrong. - Instead, return `VM_DATAPART_SPLIT_NX_FAILED', though `NULL' is still
 * returned in the event that `vpage_offset' is too large. */
PUBLIC NONNULL((1)) REF struct vm_datapart *
NOTHROW(KCALL vm_datapart_split_nx)(struct vm_datapart *__restrict self, size_t vpage_offset)
#else /* SPLIT_NX */
/* Split the given datapart after `vpage_offset' pages of virtual memory.
 * Additionally, map new nodes within all VMs in with `self' is mapped as part of.
 * NOTE: The caller must not be holding locks to _any_ of those VMs or the given data part itself.
 * @return: * :   A reference to the new upper-half of `self', starting
 *                after `vpage_offset' pages at the end of `self'
 * @return: NULL: The given `vpage_offset >= vm_datapart_numvpages(self)' */
PUBLIC NONNULL((1)) REF struct vm_datapart *KCALL
vm_datapart_split(struct vm_datapart *__restrict self, size_t vpage_offset)
		THROWS(E_WOULDBLOCK, E_BADALLOC)
#endif /* !SPLIT_NX */
{
	struct vm *v;
	struct pointer_set vms;
	size_t vms_count;
	REF struct vm_datapart *result = NULL;
	struct vm_node *vm_node_buffer[4];
	struct vm_node **vm_node_vector = vm_node_buffer;
	size_t vm_node_count            = 0;
	size_t vm_node_alloc            = COMPILER_LENOF(vm_node_buffer);
	size_t result_pprop_allocated   = 0;
	size_t result_pagevec_allocated = 0;
	assert(vpage_offset != 0);
	assert(!(self->dp_flags & VM_DATAPART_FLAG_KERNPRT));

	pointer_set_init(&vms);
#ifndef SPLIT_NX
	TRY
#endif /* !SPLIT_NX */
	{
again_lock_datapart:
		assert(vms.ps_size == 0);
#ifdef SPLIT_NX
		if unlikely(!sync_write_nx(self))
			goto err;
#else /* SPLIT_NX */
		sync_write(self);
#endif /* !SPLIT_NX */
		if (vpage_offset >= vm_datapart_numvpages(self)) {
			/* Special case: the part is too small to be split at the given offset. */
			sync_endwrite(self);
			if (result) {
				result->dp_crefs = NULL;
				result->dp_srefs = NULL;
				result->dp_stale = NULL;
				vm_datapart_destroy(result);
			}
			while (vm_node_count--)
				vm_node_destroy(vm_node_vector[vm_node_count]);
			if (vm_node_vector != vm_node_buffer)
				kfree(vm_node_vector);
			pointer_set_fini(&vms);
			return NULL;
		}
		/* Allocate a new part if we haven't done so already. */
		if (!result) {
			result = (REF struct vm_datapart *)kmalloc_nx(sizeof(struct vm_datapart),
			                                              GFP_CALLOC | GFP_ATOMIC | GFP_LOCKED |
			                                              GFP_PREFLT | GFP_VCBASE);
			if unlikely(!result) {
				/* Must allocate with blocking enabled! */
				sync_endwrite(self);
#ifdef SPLIT_NX
				result = (REF struct vm_datapart *)kmalloc_nx(sizeof(struct vm_datapart),
				                                              GFP_CALLOC | GFP_LOCKED |
				                                              GFP_PREFLT | GFP_VCBASE);
				if unlikely(!result)
					goto err;
#else /* SPLIT_NX */
				result = (REF struct vm_datapart *)kmalloc(sizeof(struct vm_datapart),
				                                           GFP_CALLOC | GFP_LOCKED |
				                                           GFP_PREFLT | GFP_VCBASE);
#endif /* !SPLIT_NX */
				goto again_lock_datapart;
			}
		}

		/* Collect all VMs referenced by this data part. */
		vms_count = vm_set_collect_from_datapart(&vms, self);
		if unlikely(vms_count > vms.ps_size) {
			sync_endwrite(self);
#ifdef SPLIT_NX
			if (!pointer_set_clear_and_rehash_nx(&vms, vms_count, GFP_LOCKED))
				goto err;
#else /* SPLIT_NX */
			pointer_set_clear_and_rehash(&vms, vms_count, GFP_LOCKED);
#endif /* !SPLIT_NX */
			goto again_lock_datapart;
		}
		/* Acquire a write-lock to all of the VMs that are mapping the given data part. */
		v = vm_set_locktrywrite_all(&vms);
		if unlikely(v) {
			/* One of the VMs is being a bit stubborn... */
			incref(v);
			sync_endwrite(self);
			vm_set_clear(&vms);
#ifdef SPLIT_NX
			if (!sync_write_nx(v)) {
				decref(v);
				goto err;
			}
#else /* SPLIT_NX */
			TRY {
				sync_write(v);
			} EXCEPT {
				decref(v);
				RETHROW();
			}
#endif /* !SPLIT_NX */
			sync_endwrite(v);
			decref(v);
			goto again_lock_datapart;
		}
		/* Figure out how many VM nodes it'll take to re-map all of the existing mappings. */
		{
			unsigned int i;
			size_t vm_node_reqcount = 0;
			struct vm_node *iter;
			for (i = 0; i < 2; ++i) {
				for (iter       = i ? self->dp_srefs : self->dp_crefs;
				     iter; iter = iter->vn_link.ln_next) {
					if (!wasdestroyed(iter->vn_vm)) {
						assert(i ? (iter->vn_prot & VM_PROT_SHARED)
						         : !(iter->vn_prot & VM_PROT_SHARED));
						++vm_node_reqcount;
					}
				}
			}
			if (vm_node_count > vm_node_reqcount) {
				/* Must free unused nodes. */
				do {
					--vm_node_count;
					vm_node_destroy(vm_node_vector[vm_node_count]);
				} while (vm_node_count > vm_node_reqcount);
			} else if (vm_node_count < vm_node_reqcount) {
				/* Must allocate more nodes. */
				if (vm_node_reqcount > vm_node_alloc) {
					struct vm_node **new_node_vector;
					vm_node_alloc   = vm_node_reqcount;
					new_node_vector = vm_node_vector == vm_node_buffer
					                  ? (struct vm_node **)kmalloc_nx(vm_node_reqcount * sizeof(struct vm_node *),
					                                                  GFP_ATOMIC | GFP_LOCKED | GFP_PREFLT | GFP_VCBASE)
					                  : (struct vm_node **)krealloc_nx(vm_node_vector,
					                                                   vm_node_reqcount * sizeof(struct vm_node *),
					                                                   GFP_ATOMIC | GFP_LOCKED | GFP_PREFLT | GFP_VCBASE);
					if (!new_node_vector) {
						vm_set_lockendwrite_all(&vms);
						sync_endwrite(self);
						vm_set_clear(&vms);
#ifdef SPLIT_NX
						new_node_vector = vm_node_vector == vm_node_buffer
						                  ? (struct vm_node **)kmalloc_nx(vm_node_reqcount * sizeof(struct vm_node *),
						                                                  GFP_LOCKED | GFP_PREFLT | GFP_VCBASE)
						                  : (struct vm_node **)krealloc_nx(vm_node_vector,
						                                                   vm_node_reqcount * sizeof(struct vm_node *),
						                                                   GFP_LOCKED | GFP_PREFLT | GFP_VCBASE);
						if unlikely(!new_node_vector)
							goto err;
#else /* SPLIT_NX */
						new_node_vector = vm_node_vector == vm_node_buffer
						                  ? (struct vm_node **)kmalloc(vm_node_reqcount * sizeof(struct vm_node *),
						                                               GFP_LOCKED | GFP_PREFLT | GFP_VCBASE)
						                  : (struct vm_node **)krealloc(vm_node_vector,
						                                                vm_node_reqcount * sizeof(struct vm_node *),
						                                                GFP_LOCKED | GFP_PREFLT | GFP_VCBASE);
#endif /* !SPLIT_NX */
						if (vm_node_vector == vm_node_buffer)
							memcpy(new_node_vector, vm_node_buffer, vm_node_count, sizeof(struct vm_node *));
						vm_node_vector = new_node_vector;
						goto again_lock_datapart;
					}
					if (vm_node_vector == vm_node_buffer)
						memcpy(new_node_vector, vm_node_buffer, vm_node_count, sizeof(struct vm_node *));
					vm_node_vector = new_node_vector;
				}
				do {
					struct vm_node *new_node;
					new_node = (struct vm_node *)kmalloc_nx(sizeof(struct vm_node),
					                                        GFP_LOCKED | GFP_CALLOC |
					                                        GFP_ATOMIC | GFP_PREFLT |
					                                        GFP_VCBASE);
					if (!new_node) {
						vm_set_lockendwrite_all(&vms);
						sync_endwrite(self);
						vm_set_clear(&vms);
						do {
#ifdef SPLIT_NX
							new_node = (struct vm_node *)kmalloc_nx(sizeof(struct vm_node),
							                                        GFP_LOCKED | GFP_CALLOC |
							                                        GFP_PREFLT | GFP_VCBASE);
							if unlikely(!new_node)
								goto err;
#else /* SPLIT_NX */
							new_node = (struct vm_node *)kmalloc(sizeof(struct vm_node),
							                                     GFP_LOCKED | GFP_CALLOC |
							                                     GFP_PREFLT | GFP_VCBASE);
#endif /* !SPLIT_NX */
							vm_node_vector[vm_node_count] = new_node;
						} while (++vm_node_count < vm_node_reqcount);
						goto again_lock_datapart;
					}
					vm_node_vector[vm_node_count] = new_node;
				} while (++vm_node_count < vm_node_reqcount);
			}
		}

		/* At this point, we've got locks to all VMs, as well as the data part itself,
		 * and have also allocated all of the node descriptors required for splitting
		 * the data part in every VM in which it appears.
		 * However, we still need to acquire a lock to the associated data block, in case
		 * that block isn't anonymous, we must also acquire a lock to it, so-as to be able
		 * to update its part tree with the upper half we intend on constructing. */
		if (self->dp_block->db_parts != VM_DATABLOCK_ANONPARTS) {
			/* Also need to acquire a lock to the datablock. */
			if (!sync_trywrite(self->dp_block)) {
				REF struct vm_datablock *block;
				vm_set_lockendwrite_all(&vms);
				block = incref(self->dp_block);
				sync_endwrite(self);
				vm_set_clear(&vms);
#ifdef SPLIT_NX
				if unlikely(!sync_write_nx(block)) {
					decref_unlikely(block);
					goto err;
				}
#else /* SPLIT_NX */
				TRY {
					sync_write(block);
				} EXCEPT {
					decref_unlikely(block);
					RETHROW();
				}
#endif /* !SPLIT_NX */
				sync_endwrite(block);
				decref_unlikely(block);
				goto again_lock_datapart;
			}
		}

		/* At this point, we've got all the locks we could possibly need.
		 * Now to move on to setup the higher half data part! */
		result->dp_refcnt = 1; /* The reference that's going to be returned */
		/* NOTE: Initialize with read-access, since we need that to update the data-part
		 *       pointers of transferred futex objects once everything else has been done. */
		shared_rwlock_init_read(&result->dp_lock);
		result->dp_tree.a_vmin = self->dp_tree.a_vmin + (vpage_offset << VM_DATABLOCK_PAGESHIFT(self->dp_block));
		result->dp_tree.a_vmax = self->dp_tree.a_vmax;
		assert(result->dp_tree.a_vmin <= result->dp_tree.a_vmax);
		result->dp_crefs = NULL;
		result->dp_srefs = NULL;
		result->dp_stale = NULL;

		result->dp_block = self->dp_block;
		result->dp_state = self->dp_state;
		result->dp_flags = self->dp_flags & ~(VM_DATAPART_FLAG_COREPRT |
		                                      VM_DATAPART_FLAG_HEAPPPP);
		/* Split the page property vector. */
		if (!(self->dp_flags & VM_DATAPART_FLAG_HEAPPPP)) {
			assert(vm_datapart_numdpages(self) <=
			       (BITSOF(uintptr_t) / VM_DATAPART_PPP_BITS));
			if unlikely(result_pprop_allocated) {
				kfree(result->dp_pprop_p);
				result_pprop_allocated = 0;
			}
			assert(!(result->dp_flags & VM_DATAPART_FLAG_HEAPPPP));
			result->dp_pprop = (self->dp_pprop >>
			                    (vpage_offset << VM_DATABLOCK_PAGESHIFT(self->dp_block)) *
			                    VM_DATAPART_PPP_BITS);
		} else if (!self->dp_pprop_p) {
			if unlikely(result_pprop_allocated) {
				kfree(result->dp_pprop_p);
				result_pprop_allocated = 0;
			}
			result->dp_pprop_p = NULL;
			result->dp_flags |= VM_DATAPART_FLAG_HEAPPPP;
		} else {
			/* Figure out how much memory we'll need for the upper-half page-property bitset. */
			size_t low_num_dpages;
			size_t high_num_dpages;
			size_t bitsize_size;
			high_num_dpages = vm_datapart_numdpages(self);
			low_num_dpages  = vpage_offset << VM_DATABLOCK_PAGESHIFT(self->dp_block);
			high_num_dpages -= low_num_dpages;
			if (high_num_dpages <= BITSOF(uintptr_t) / VM_DATAPART_PPP_BITS) {
				if unlikely(result_pprop_allocated) {
					kfree(result->dp_pprop_p);
					result_pprop_allocated = 0;
				}
				assert(!(result->dp_flags & VM_DATAPART_FLAG_HEAPPPP));
				pprop_memcpy(&result->dp_pprop,
				             self->dp_pprop_p,
				             0,
				             low_num_dpages,
				             high_num_dpages);
			} else {
				bitsize_size = CEILDIV(high_num_dpages,
				                       BITSOF(uintptr_t) / VM_DATAPART_PPP_BITS) *
				               sizeof(uintptr_t);
				assert(high_num_dpages != 0);
				assert(bitsize_size != 0);
				if (bitsize_size > result_pprop_allocated) {
					uintptr_t *new_bitset;
					if (!result_pprop_allocated)
						result->dp_pprop_p = NULL;
					result_pprop_allocated = bitsize_size;
					new_bitset = (uintptr_t *)krealloc_nx(result->dp_pprop_p,
					                                      bitsize_size,
					                                      GFP_ATOMIC | GFP_LOCKED |
					                                      GFP_PREFLT | GFP_VCBASE);
					if (!new_bitset) {
						/* Must allocate the bitset whilst blocking! */
						if (self->dp_block->db_parts != VM_DATABLOCK_ANONPARTS)
							sync_endwrite(self->dp_block);
						vm_set_lockendwrite_all(&vms);
						sync_endwrite(self);
						vm_set_clear(&vms);
#ifdef SPLIT_NX
						result->dp_pprop_p = (uintptr_t *)krealloc_nx(result->dp_pprop_p,
						                                              result_pprop_allocated,
						                                              GFP_LOCKED | GFP_PREFLT | GFP_VCBASE);
						if unlikely(!result->dp_pprop_p)
							goto err;
#else /* SPLIT_NX */
						result->dp_pprop_p = (uintptr_t *)krealloc(result->dp_pprop_p,
						                                           result_pprop_allocated,
						                                           GFP_LOCKED | GFP_PREFLT | GFP_VCBASE);
#endif /* !SPLIT_NX */
						goto again_lock_datapart;
					}
					result->dp_pprop_p = new_bitset;
				}
				result->dp_flags |= VM_DATAPART_FLAG_HEAPPPP;
				/* Copy page property bits into the target vector */
				pprop_memcpy(result->dp_pprop_p,
				             self->dp_pprop_p,
				             0,
				             low_num_dpages,
				             high_num_dpages);
			}
		}

		/* With all of the mandatory locks now acquired, check for stale nodes one more time,
		 * as some other thread may have unmapped one of the mappings apart of one of the VMs
		 * which we've just acquired a lock to.
		 * HINT: Stale nodes are serviced whenever a lock to `self' is acquired! */
		if unlikely(VM_DATAPART_MUST_SERVICE_STALE(self)) {
			vm_set_lockendwrite_all(&vms);
			sync_endwrite(self);
			vm_set_clear(&vms);
			goto again_lock_datapart;
		}

		/* Check if we must allocate a secondary futex controller for the upper-half datapart.
		 * For this purpose, we do a simplified check that is guarantied to catch all cases
		 * where a controller will be required, by simply checking if there is at least one
		 * futex allocated within the address range of the upper-half datapart. */
		if (self->dp_futex && !result->dp_futex &&
		    vm_futextree_rlocate_at(self->dp_futex->fc_tree,
		                            (uintptr_t)vpage_offset * PAGESIZE,
		                            (uintptr_t)-1,
		                            self->dp_futex->fc_semi0,
		                            self->dp_futex->fc_leve0) != NULL) {
			struct vm_futex_controller *hifc;
			hifc = vm_futex_controller_allocf_nx(GFP_ATOMIC | GFP_PREFLT | GFP_VCBASE);
			if (!hifc) {
				/* Must allocate while blocking. */
				vm_set_lockendwrite_all(&vms);
				sync_endwrite(self);
				vm_set_clear(&vms);
#ifdef SPLIT_NX
				hifc = vm_futex_controller_allocf_nx(GFP_PREFLT | GFP_VCBASE);
				if unlikely(!hifc)
					goto err;
#else /* SPLIT_NX */
				hifc = vm_futex_controller_allocf(GFP_PREFLT | GFP_VCBASE);
#endif /* !SPLIT_NX */
				result->dp_futex = hifc;
				goto again_lock_datapart;
			}
			result->dp_futex = hifc;
		}

		switch (result->dp_state) {
			STATIC_ASSERT(COMPILER_OFFSETOF(struct vm_datapart, dp_ramdata.rd_blockv) ==
			              COMPILER_OFFSETOF(struct vm_datapart, dp_swpdata.sd_blockv));

		case VM_DATAPART_STATE_INCORE: /* The part is currently loaded into main memory. */
		case VM_DATAPART_STATE_LOCKED: /* The part has been locked in main memory. */
#if !defined(CONFIG_NO_SWAP) && defined(VM_SWPBLOCK_EQUALS_RAMBLOCK)
		case VM_DATAPART_STATE_INSWAP:
#endif /* !CONFIG_NO_SWAP && VM_SWPBLOCK_EQUALS_RAMBLOCK */
			/* Split the ram / swap data vectors. */
			if (self->dp_ramdata.rd_blockv == &self->dp_ramdata.rd_block0) {
				/* Simple case: Split a single ram block */
				if unlikely(result_pagevec_allocated) {
					kfree(result->dp_ramdata.rd_blockv);
					result_pagevec_allocated = 0;
				}
				result->dp_ramdata.rd_blockv          = &result->dp_ramdata.rd_block0;
				result->dp_ramdata.rd_block0.rb_start = self->dp_ramdata.rd_block0.rb_start + vpage_offset;
				result->dp_ramdata.rd_block0.rb_size  = self->dp_ramdata.rd_block0.rb_size - vpage_offset;
				/* |----- Point of no return */
				self->dp_ramdata.rd_block0.rb_size = vpage_offset;
			} else {
				size_t req_blockc;
				size_t i;
				size_t total = 0;
				struct vm_ramblock *blocks;
				blocks = self->dp_ramdata.rd_blockv;
				/* Figure out where and how we need to split the ram-block-vector in
				 * order to be able to individually store in 2 different parts. */
				for (i = 0;; ++i) {
					assert(i < self->dp_ramdata.rd_blockc);
					assert(total <= vpage_offset);
					total += blocks[i].rb_size;
					if (total > vpage_offset) {
						total -= blocks[i].rb_size;
						assert(total <= vpage_offset);
						break;
					}
				}
				/* The split happens either somewhere within `blocks[i]',
				 * possibly at the very start.
				 * Specifically, it happens `vpage_offset - total' pages into `blocks[i]' */
				req_blockc = self->dp_ramdata.rd_blockc - i;
				assert(req_blockc != 0);
				if (req_blockc == 1) {
					assert(i == self->dp_ramdata.rd_blockc - 1);
					if unlikely(result_pagevec_allocated) {
						kfree(result->dp_ramdata.rd_blockv);
						result_pagevec_allocated = 0;
					}
					result->dp_ramdata.rd_blockv          = &result->dp_ramdata.rd_block0;
					result->dp_ramdata.rd_block0.rb_start = blocks[i].rb_start + (vpage_offset - total);
					result->dp_ramdata.rd_block0.rb_size  = blocks[i].rb_size - (vpage_offset - total);
				} else {
					struct vm_ramblock *result_blocks;
					result_blocks = result->dp_ramdata.rd_blockv;
					if (req_blockc > result_pagevec_allocated) {
						/* Need to allocate more blocks! */
						if (!result_pagevec_allocated)
							result_blocks = NULL;
						result_pagevec_allocated = req_blockc;
						result_blocks = (struct vm_ramblock *)krealloc_nx(result_blocks,
						                                                  req_blockc *
						                                                  sizeof(struct vm_ramblock),
						                                                  GFP_ATOMIC | GFP_LOCKED |
						                                                  GFP_PREFLT | GFP_VCBASE);
						if (!result_blocks) {
							/* Must allocate while blocking. */
							vm_set_lockendwrite_all(&vms);
							sync_endwrite(self);
							vm_set_clear(&vms);
							result_blocks = result->dp_ramdata.rd_blockv;
							if (!result_pagevec_allocated)
								result_blocks = NULL;
#ifdef SPLIT_NX
							result_blocks = (struct vm_ramblock *)krealloc_nx(result_blocks,
							                                                  req_blockc *
							                                                  sizeof(struct vm_ramblock),
							                                                  GFP_LOCKED | GFP_PREFLT | GFP_VCBASE);
							if unlikely(!result_blocks)
								goto err;
#else /* SPLIT_NX */
							result_blocks = (struct vm_ramblock *)krealloc(result_blocks,
							                                               req_blockc *
							                                               sizeof(struct vm_ramblock),
							                                               GFP_LOCKED | GFP_PREFLT | GFP_VCBASE);
#endif /* !SPLIT_NX */
							result->dp_ramdata.rd_blockv = result_blocks;
							goto again_lock_datapart;
						}
					}
					/* Copy all of the while data block that we want to duplicate. */
					assert(result_blocks != NULL);
					memcpy(result_blocks,
					       blocks + (self->dp_ramdata.rd_blockc - req_blockc),
					       req_blockc, sizeof(struct vm_ramblock));
					if (total != vpage_offset) {
						/* Adjust the initial duplicate part to properly feature the sub-part split. */
						assert(vpage_offset > total);
						result_blocks[0].rb_start += result_blocks[0].rb_size;
						result_blocks[0].rb_size -= vpage_offset - total;
						result_blocks[0].rb_start -= result_blocks[0].rb_size;
					}
					result->dp_ramdata.rd_blockv = result_blocks;
					result->dp_ramdata.rd_blockc = req_blockc;
				}
				/* |----- Point of no return */
				blocks[i].rb_size = vpage_offset - total; /* Adjust the length of the block that was split */

				assertf(blocks[i].rb_start + blocks[i].rb_size ==
				        result->dp_ramdata.rd_blockv[0].rb_start,
				        "The upper half of the split doesn't start where the lower half ends!\n"
				        "END_OF_FIRST_PART                        = %I64p\n"
				        "START_OF_SECOND_PART                     = %I64p\n"
				        "blocks[i].rb_start                       = %I64p\n"
				        "blocks[i].rb_size                        = %Iup\n"
				        "result->dp_ramdata.rd_blockv[0].rb_start = %I64p\n"
				        "result->dp_ramdata.rd_blockv[0].rb_size  = %Iup\n"
				        "vpage_offset                             = %Iu\n"
				        "total                                    = %Iu\n",
				        (u64)(blocks[i].rb_start + blocks[i].rb_size),
				        (u64)result->dp_ramdata.rd_blockv[0].rb_start,
				        (u64)blocks[i].rb_start,
				        (size_t)blocks[i].rb_size,
				        (u64)result->dp_ramdata.rd_blockv[0].rb_start,
				        (size_t)result->dp_ramdata.rd_blockv[0].rb_size,
				        vpage_offset, total);
				/* Figure out how many blocks the lower part should be left with.
				 *  -> If the split happened somewhere into the lower part's block,
				 *     the first half of that block must still be kept. - Otherwise,
				 *     that block must be removed alongside all that followed it. */
				if (blocks[i].rb_size != 0)
					++i;
				if (i == 1) {
					self->dp_ramdata.rd_block0.rb_start = blocks[0].rb_start;
					self->dp_ramdata.rd_block0.rb_size  = blocks[0].rb_size;
					assert(blocks[0].rb_size == vpage_offset);
					self->dp_ramdata.rd_blockv = &self->dp_ramdata.rd_block0;
					kfree(blocks);
				} else {
					blocks = (struct vm_ramblock *)krealloc_nx(blocks,
					                                           i * sizeof(struct vm_ramblock),
					                                           GFP_ATOMIC | GFP_LOCKED |
					                                           GFP_PREFLT | GFP_VCBASE);
					if likely(blocks)
						self->dp_ramdata.rd_blockv = blocks;
					self->dp_ramdata.rd_blockc = i;
				}
			}
			break;

#if !defined(CONFIG_NO_SWAP) && !defined(VM_SWPBLOCK_EQUALS_RAMBLOCK)
		case VM_DATAPART_STATE_INSWAP:
#error TODO
			break;
#endif /* !CONFIG_NO_SWAP && !VM_SWPBLOCK_EQUALS_RAMBLOCK */

		default:
			if unlikely(result_pagevec_allocated) {
				kfree(result->dp_ramdata.rd_blockv);
				result_pagevec_allocated = 0;
			}
			break;
		}
	}
#ifndef SPLIT_NX
	EXCEPT {
		while (vm_node_count--)
			vm_node_destroy(vm_node_vector[vm_node_count]);
		if (vm_node_vector != vm_node_buffer)
			kfree(vm_node_vector);
		vm_set_fini(&vms);
		if (result) {
			result->dp_crefs = NULL;
			result->dp_srefs = NULL;
			result->dp_stale = NULL;
			vm_datapart_destroy(result);
		}
		RETHROW();
	}
#endif /* !SPLIT_NX */

	/*----------------------------------------------------------*
	 | This is the point of no return, where nothing may go     |
	 | wrong anymore, and we start modifying the original       |
	 | datapart to only represent the lower half of the mapping |
	 *----------------------------------------------------------*/

	/* Split (and update) futex descriptors. */
	if (!self->dp_futex || self->dp_futex->fc_tree == NULL) {
set_result_no_futex:
		if unlikely(result->dp_futex != NULL) {
			vm_futex_controller_free(result->dp_futex);
			result->dp_futex = NULL;
		}
	} else {
		/* Splitting a futex controller has multiple steps:
		 *     #1: Enumerate all existing futex objects and use `tryincref()' to
		 *         acquire references to all of them. Once this is done, we can
		 *         assume that all futex objects that are `!wasdestroyed(FUTEX)'
		 *         are those that can qualify for being part of the transfer:
		 *           - Because we're holding a reference to each of them, it is
		 *             guarantied that none of them will end up getting destroyed
		 *             before we are done
		 *           - Because we are holding a lock to `self->dp_lock', we are
		 *             guarantied that no additional futex objects can appear.
		 *         The combination of these 2 (valid) assumptions then allows us
		 *         to assume that the set of qualifying futex objects will be
		 *         consistent until we're done.
		 *     #2: Figure out the lowest and greatest address to which a futex
		 *         that isn't destroyed has been bound.
		 *         If all these addresses...
		 *            ... lie within the lower-half data part (i.e. `self'), then nothing
		 *                else is left to be done, and the references acquired by step #1
		 *                will automatically be released by the call to `vm_futextree_decref_all()'
		 *                further down below.
		 *            ... lie within the upper-half data part (i.e. `result'), and no futex
		 *                object exists that had already been destroyed, then simply
		 *                assign the controller pointer to `result', and set the controller
		 *                pointer of `self' to `NULL'.
		 *                Afterwards, subtract the new size of the lower-half data part from
		 *                all futex objects and re-create the atree from scratch (also: update
		 *                the `fc_(semi|level)0' fields)
		 *                Then jump to the end of futex splitting code.
		 *         Otherwise, if futex objects exist for both the lower-half and upper-half data
		 *         parts, or futex objects exist that have already been destroyed, then a secondary
		 *         futex controller needs to be allocated for `result'. Note that this third option
		 *         is the only one that leads to step #4
		 *     #4: At this point, once again enumerate all futex objects of `self' and transfer
		 *         all those that belong into the upper-half data part into the newly allocated
		 *         futex controller after subtracting the size of the lower-half data part from
		 *         their address indices.
		 */
		struct vm_futex *transfer_futex;
		struct vm_futex_controller *lofc;
		struct vm_futex_controller *hifc;
		uintptr_t minaddr = (uintptr_t)-1;
		uintptr_t maxaddr = 0;
		uintptr_t lofc_maxaddr;
		bool all_futexes_alive;
		lofc = self->dp_futex;
again_incref_futexes:
		all_futexes_alive = vm_futextree_tryincref_all_and_collect_minmax(lofc->fc_tree,
		                                                                  &minaddr,
		                                                                  &maxaddr
#ifndef NDEBUG
		                                                                  ,
		                                                                  self
#endif /* !NDEBUG */
		                                                                  );
		/* Integrity check: When all futex objects are alive, then the dead-pointer
		 *                  has to be NULL. Note though that the opposite doesn't
		 *                  hold true, since a futex may be dead, but the thread that
		 *                  initiated the decref() may not yet have gotten around to
		 *                  actually appending the futex to the associated controller's
		 *                  chain of dead futex objects. */
		assert(all_futexes_alive ? lofc->fc_dead == NULL
		                         : true);
		if unlikely(minaddr > maxaddr)
			goto set_result_no_futex; /* Special case: All futex objects were already destroyed. */
		/* Figure out the greatest address that should be
		 * kept apart of the lower-half futex controller.
		 * We choose to use the greatest address for this, since this
		 * prevents the possibly of an overflow when the the split
		 * happens at an offset of `SIZE_MAX' */
		lofc_maxaddr = (uintptr_t)vpage_offset * PAGESIZE - 1;
		if (maxaddr <= lofc_maxaddr) {
			/* Simple case: The futex with the greatest address will still be apart of
			 *              the lower-half (i.e. old; i.e. `self') datapart, meaning
			 *              that we don't actually have to do anything! */
			/* TODO: Re-Calculate best-fit semi/level values for the tree (since it's
			 *       max-size is now lower than before).
			 *       If this calculation turns up different values than the old ones,
			 *       then we must also re-form the tree. */
			goto set_result_no_futex;
		}
		if (minaddr > lofc_maxaddr) {
			if (!all_futexes_alive) {
				/* Check if we can maybe service the futex controller so
				 * that all futexes that are dead now end up going away... */
				struct vm_futex *dead;
				dead = ATOMIC_XCH(lofc->fc_dead, NULL);
				if (dead != NULL) {
					struct vm_futex *next;
					do {
						next = dead->f_ndead;
#ifdef NDEBUG
						vm_futextree_remove(&lofc->fc_tree, dead->f_tree.a_vaddr,
						                    lofc->fc_semi0, lofc->fc_leve0);
#else /* NDEBUG */
						{
							struct vm_futex *removed;
							removed = vm_futextree_remove_at(&lofc->fc_tree,
							                                 dead->f_tree.a_vaddr,
							                                 lofc->fc_semi0,
							                                 lofc->fc_leve0);
							assertf(removed == dead, "%p != %p (addr: %p)",
							        removed, dead, dead->f_tree.a_vaddr);
						}
#endif /* !NDEBUG */
						vm_futex_free(dead);
					} while ((dead = next) != NULL);
					vm_futextree_decref_all_if_not_destroyed(lofc->fc_tree
#ifndef NDEBUG
					                                         ,
					                                         self
#endif /* !NDEBUG */
					                                         );
					/* Incref all futex objects once again.
					 * Maybe this time around, they'll all end up being alive... */
					goto again_incref_futexes;
				} else {
					/* Some futex objects are dead, but none of them appear in the
					 * chain of dead futex objects. This can happen when the thread
					 * that did the final decref() hasn't gotten around to adding
					 * the futex to the chain of dead ones of the associated controller.
					 * In this case, we also mustn't let the upper-half datapart inherit
					 * the futex controller, since we must uphold the assumption that
					 * any data parts futex controller is [1..1][const] so-long as it
					 * contains at least one futex with a reference counter of ZERO(0),
					 * and that futex has yet to be added to the controller's chain
					 * of dead futex objects. */
				}
			} else {
				/* Another (fairly) simple case: All futex objects ended up belonging onto
				 * the upper-half (i.e. `new'; i.e. `result') datapart, and there are no
				 * futex objects that dead. In this case, we can simply have the upper-half
				 * datapart inherit the futex controller of the lower-half one. */
				assert(result->dp_futex != lofc);
				if (result->dp_futex)
					vm_futex_controller_free(result->dp_futex);
				result->dp_futex = lofc;
				self->dp_futex   = NULL; /* Stolen by `result->dp_futex'. */
				assert(lofc->fc_tree != NULL);
				/* TODO: Calculate best-fit semi/level values. */
				lofc->fc_semi0 = ATREE_SEMI0(uintptr_t);
				lofc->fc_leve0 = ATREE_LEVEL0(uintptr_t);
				/* Reform the futex tree. */
				vm_futextree_subtract_addr_and_reform_tree(lofc->fc_tree,
				                                           &lofc->fc_tree,
				                                           lofc_maxaddr + 1,
				                                           lofc->fc_semi0,
				                                           lofc->fc_leve0);
				goto done_futex;
			}
		}
		/* Both the lower-half and upper-half data parts will end up containing
		 * futex objects. - In this case, we must allocate a secondary futex
		 * controller which we can then assign to `result', before filling it
		 * with only those futexes that are aren't destroyed, and have an
		 * address that is `> lofc_maxaddr'
		 * NOTE: Because we're already past the point of no return at this point,
		 *       we _have_ to make sure that earlier code has already allocated
		 *       the secondary futex controller by this point! */
		hifc = result->dp_futex;
		assertf(hifc != NULL,
		        "Earlier code must pre-allocate the futex controller for this case!");
		/* TODO: Calculate best-fit semi/level values. */
		hifc->fc_semi0 = ATREE_SEMI0(uintptr_t);
		hifc->fc_leve0 = ATREE_LEVEL0(uintptr_t);
		/* Remove all affected  */
		while ((transfer_futex = vm_futextree_rremove_at_not_destroyed(&lofc->fc_tree,
		                                                               lofc_maxaddr + 1, (uintptr_t)-1,
		                                                               lofc->fc_semi0,
		                                                               lofc->fc_leve0)) != NULL) {
			assert(transfer_futex->f_tree.a_vaddr > lofc_maxaddr);
			transfer_futex->f_tree.a_vaddr -= lofc_maxaddr + 1;
			vm_futextree_insert_at(&hifc->fc_tree, transfer_futex,
			                       hifc->fc_semi0, hifc->fc_leve0);
		}
		/* And we're done! (though some more cleanup will be happening further down below...) */
	}
done_futex:

	/* Try to truncate the page property vector of `self' */
	if (self->dp_flags & VM_DATAPART_FLAG_HEAPPPP) {
		size_t low_num_dpages;
		size_t bitsize_size;
		uintptr_t *new_vector;
		low_num_dpages = vpage_offset << VM_DATABLOCK_PAGESHIFT(self->dp_block);
		bitsize_size = CEILDIV(low_num_dpages,
		                       BITSOF(uintptr_t) / VM_DATAPART_PPP_BITS) *
		               sizeof(uintptr_t);
		new_vector = (uintptr_t *)krealloc_nx(self->dp_pprop_p,
		                                      bitsize_size,
		                                      GFP_ATOMIC | GFP_LOCKED |
		                                      GFP_PREFLT | GFP_VCBASE);
		if likely(new_vector)
			self->dp_pprop_p = new_vector;
	}

	/* With the new data part all set up, move on to initializing and fill in
	 * all of the new VM nodes which we have to map to their respective VMs */
	{
		unsigned int i;
		size_t node_index;
		struct vm_node *iter;
		node_index = 0;
		for (i = 0; i < 2; ++i) {
			for (iter       = i ? self->dp_srefs : self->dp_crefs;
			     iter; iter = iter->vn_link.ln_next) {
				struct vm_node *high;
				if (wasdestroyed(iter->vn_vm))
					continue; /* Stale node */
				assert(i ? (iter->vn_prot & VM_PROT_SHARED)
				         : !(iter->vn_prot & VM_PROT_SHARED));
				assert(node_index < vm_node_count);
				assert(vm_node_getpagecount(iter) == vm_datapart_numvpages(self));
				assert(!(iter->vn_flags & VM_NODE_FLAG_KERNPRT));
				high                 = vm_node_vector[node_index];
				high->vn_node.a_vmin = iter->vn_node.a_vmin + vpage_offset;
				high->vn_node.a_vmax = iter->vn_node.a_vmax;
				high->vn_prot        = iter->vn_prot;
				/* Unset the prepared flag for the node: because the node got split, it is no
				 * longer prepared in its entirety, meaning that when being modified, it must
				 * be prepared once again (see documentation of `pagedir_prepare_mapone()',
				 * specifically the part about having to re-prepare a sub-region before unmap()
				 * following a map() operation, when only a part of that original region must
				 * be unmapped, as opposed to it in its entirety) */
				high->vn_flags  = iter->vn_flags & ~(VM_NODE_FLAG_COREPRT);
				high->vn_vm     = iter->vn_vm;
				high->vn_part   = incref(result);
				high->vn_block  = incref(iter->vn_block);
				high->vn_fspath = xincref(iter->vn_fspath);
				high->vn_fsname = xincref(iter->vn_fsname);
				/* Set the partitioned flag for both node parts, so-as to prevent race conditions
				 * when one of them gets unmapped (and its region becomes unprepared) at a later
				 * point in time (required so each node can safely be unprepared, without interfering
				 * with a mapping made by the other node). */
				high->vn_flags |= VM_NODE_FLAG_PARTITIONED;
				iter->vn_flags |= VM_NODE_FLAG_PARTITIONED;
				/* Setup the nodes to be chained to the resulting part. */
				{
					struct vm_node **list = i ? &result->dp_srefs : &result->dp_crefs;
					assert(list == &result->dp_srefs
					       ? (high->vn_prot & VM_PROT_SHARED)
					       : !(high->vn_prot & VM_PROT_SHARED));
					LLIST_INSERT(*list, high, vn_link);
				}
				high->vn_guard = iter->vn_guard;
				if (high->vn_guard != 0) {
					if (high->vn_flags & VM_NODE_FLAG_GROWSUP) {
						/* Grows-up --> Delete the guard for the low page */
						iter->vn_guard = 0;
					} else {
						/* Grows-down --> Delete the guard for the high page */
						high->vn_guard = 0;
					}
				}
				vm_nodetree_remove(&iter->vn_vm->v_tree,
				                   iter->vn_node.a_vmin);
				LLIST_REMOVE(iter, vn_byaddr);
				iter->vn_node.a_vmax = high->vn_node.a_vmin - 1;
				/* Re-insert both of the nodes (no need to re-map anything, since
				 * nothing was actually changed about the underlying physical memory
				 * mapping) */
				assert(iter->vn_part == self);
				vm_node_insert_ignore_missmatch(iter); /* Ignore part-mismatches, which we are going to fix below! */
				vm_node_insert(high);

				++node_index;
			}
		}
		assertf(node_index == vm_node_count,
		        "node_index    = %Iu\n"
		        "vm_node_count = %Iu\n",
		        node_index, vm_node_count);
	}

	/* Update the datablock tree to include the split upper-half part. */
	incref(result->dp_block);
	if (self->dp_block->db_parts != VM_DATABLOCK_ANONPARTS) {
		vm_parttree_remove(&self->dp_block->db_parts,
		                   self->dp_tree.a_vmin);
		self->dp_tree.a_vmax = self->dp_tree.a_vmin;
		self->dp_tree.a_vmax += ((datapage_t)vpage_offset << VM_DATABLOCK_PAGESHIFT(self->dp_block)) - 1;
		vm_parttree_insert(&self->dp_block->db_parts, self);
		vm_parttree_insert(&self->dp_block->db_parts, incref(result));
		sync_endwrite(self->dp_block);
	} else {
#if 1
		self->dp_tree.a_vmax = self->dp_tree.a_vmin;
		self->dp_tree.a_vmax += ((datapage_t)vpage_offset << VM_DATABLOCK_PAGESHIFT(self->dp_block)) - 1;
#else
		assert(self->dp_tree.a_vmin == 0);
		self->dp_tree.a_vmax = ((datapage_t)vpage_offset << VM_DATABLOCK_PAGESHIFT(self->dp_block)) - 1;
		result->dp_tree.a_vmax -= result->dp_tree.a_vmin;
		result->dp_tree.a_vmin = 0;
#endif
	}
#ifndef NDEBUG
	/* Validate that our new part size matches the expectations of all of our nodes! */
	{
		unsigned int i;
		struct vm_node *iter;
		for (i = 0; i < 2; ++i) {
			for (iter       = i ? self->dp_srefs : self->dp_crefs;
			     iter; iter = iter->vn_link.ln_next) {
				if (wasdestroyed(iter->vn_vm))
					continue; /* Stale node */
				assert(i ? (iter->vn_prot & VM_PROT_SHARED)
				         : !(iter->vn_prot & VM_PROT_SHARED));
				assert(iter->vn_part == self);
				assertf(vm_node_getpagecount(iter) == vm_datapart_numvpages(self),
				        "Node size missmatch (%Iu != %Iu)",
				        vm_node_getpagecount(iter), vm_datapart_numvpages(self));
			}
		}
	}
#endif /* !NDEBUG */

	/* Release all of the locks we've acquired. */
	vm_set_lockendwrite_all(&vms);

	/* Deal with the aftermath of splitting a futex controller. */
	if (self->dp_futex && self->dp_futex->fc_tree) {
		/* Release the references previously acquired on futex objects. */
		vm_futextree_decref_all_if_not_destroyed(self->dp_futex->fc_tree
#ifndef NDEBUG
		                                         ,
		                                         self
#endif /* !NDEBUG */
		                                         );
	}

	sync_endwrite(self);
	if (vm_node_vector != vm_node_buffer)
		kfree(vm_node_vector);
	vm_set_fini(&vms);

	/* Deal with the aftermath of splitting a futex controller. */
	if (result->dp_futex && result->dp_futex->fc_tree) {
		/* Update the data-block pointers of all futex objects that were moved.
		 * Then, decrement the reference counters of all futex objects by one,
		 * thus undoing the incref() that was done prior to the transfer. */
		vm_futextree_set_part_pointer_and_decref_all(result->dp_futex->fc_tree,
		                                             result
#ifndef NDEBUG
		                                             ,
		                                             self
#endif /* !NDEBUG */
		                                             );
	}

	/* Release the read-lock with which the resulting data part was initialized. */
	sync_endread(result);

	return result;
#ifdef SPLIT_NX
err:
	while (vm_node_count--)
		vm_node_destroy(vm_node_vector[vm_node_count]);
	if (vm_node_vector != vm_node_buffer)
		kfree(vm_node_vector);
	vm_set_fini(&vms);
	if (result) {
		result->dp_crefs = NULL;
		result->dp_srefs = NULL;
		result->dp_stale = NULL;
		vm_datapart_destroy(result);
	}
	return VM_DATAPART_SPLIT_NX_FAILED;
#endif /* !SPLIT_NX */
}


DECL_END

#undef SPLIT_NX

