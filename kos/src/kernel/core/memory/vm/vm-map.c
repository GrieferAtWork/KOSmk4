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
#ifndef GUARD_KERNEL_SRC_MEMORY_VM_VM_MAP_C
#define GUARD_KERNEL_SRC_MEMORY_VM_VM_MAP_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <fs/node.h>
#include <fs/vfs.h>
#include <kernel/driver.h>
#include <kernel/except.h>
#include <kernel/malloc.h>
#include <kernel/printk.h>
#include <kernel/vm.h>

#include <hybrid/atomic.h>
#include <hybrid/overflow.h>

#include <assert.h>
#include <inttypes.h>
#include <string.h>

#include "vm-nodeapi.h"

#if defined(NDEBUG) || 1
#define VM_MAP_TRACE(...) (void)0
#else
#define VM_MAP_TRACE(...) printk(__VA_ARGS__)
#endif

DECL_BEGIN

struct partnode_pair {
	REF struct vm_datapart *pn_part; /* [1..1] The associated part (NOTE: This pointer also holds a write-lock to this part). */
	struct vm_node         *pn_node; /* [1..1][owned] The associated node. */
};

struct partnode_pair_vector {
	size_t                pv_cnt;    /* Amount of used pairs. */
	size_t                pv_alc;    /* Amount of allocated pairs. */
	struct partnode_pair *pv_vec;    /* [0..pv_cnt|ALLOC(pv_alc)][owned_if(!= pv_buf)]
	                                  * Vector of part-node pairs. */
	struct partnode_pair  pv_buf[2]; /* A small, statically allocated buffer of pairs. */
};

/* Try to acquire write-locks to all of th parts contained within `self'
 * If this fails for one of these parts, unlock all parts previously locked,
 * and return a pointer to the blocking part. */
PRIVATE NOBLOCK struct vm_datapart *
NOTHROW(KCALL partnode_pair_vector_trywrite_parts)(struct partnode_pair_vector *__restrict self) {
	size_t i;
	for (i = 0; i < self->pv_cnt; ++i) {
		struct vm_datapart *part;
		part = self->pv_vec[i].pn_part;
		if (!sync_trywrite(part)) {
			while (i--)
				sync_endwrite(self->pv_vec[i].pn_part);
			return part;
		}
	}
	return NULL;
}

/* Release write-locks to all of the parts contained within `self' */
PRIVATE NOBLOCK void
NOTHROW(KCALL partnode_pair_vector_endwrite_parts)(struct partnode_pair_vector *__restrict self) {
	size_t i = self->pv_cnt;
	while (i--)
		sync_endwrite(self->pv_vec[i].pn_part);
}

/* Same as `partnode_pair_vector_reserve1_nx()', but allow for exceptions, as well as blocking */
PRIVATE void KCALL
partnode_pair_vector_reserve1(struct partnode_pair_vector *__restrict self)
		THROWS(E_WOULDBLOCK, E_BADALLOC) {
	assert(self->pv_cnt <= self->pv_alc);
	if (self->pv_cnt >= self->pv_alc) {
		/* Must allocate more pairs. */
		size_t new_alloc = self->pv_alc + 4;
		struct partnode_pair *new_vector;
		new_vector = self->pv_vec == self->pv_buf
		             ? (struct partnode_pair *)kmalloc_nx(new_alloc * sizeof(struct partnode_pair),
		                                                  GFP_LOCKED | GFP_PREFLT | GFP_VCBASE)
		             : (struct partnode_pair *)krealloc_nx(self->pv_vec,
		                                                   new_alloc * sizeof(struct partnode_pair),
		                                                   GFP_LOCKED | GFP_PREFLT | GFP_VCBASE);
		if (!new_vector) {
			new_alloc  = self->pv_cnt + 1;
			new_vector = self->pv_vec == self->pv_buf
			             ? (struct partnode_pair *)kmalloc(new_alloc * sizeof(struct partnode_pair),
			                                               GFP_LOCKED | GFP_PREFLT | GFP_VCBASE)
			             : (struct partnode_pair *)krealloc(self->pv_vec,
			                                                new_alloc * sizeof(struct partnode_pair),
			                                                GFP_LOCKED | GFP_PREFLT | GFP_VCBASE);
		}
		if (self->pv_vec == self->pv_buf)
			memcpy(new_vector, self->pv_buf, self->pv_cnt, sizeof(struct partnode_pair));
		self->pv_alc = new_alloc;
		self->pv_vec = new_vector;
	}
}

/* Add the given `part' to the part vector, as well as allocate an associated node. */
PRIVATE void KCALL
partnode_pair_vector_addpart(struct partnode_pair_vector *__restrict self,
                             /*inherit(on_success)*/ REF struct vm_datapart *__restrict part)
		THROWS(E_WOULDBLOCK, E_BADALLOC) {
	struct vm_node *new_node;
	partnode_pair_vector_reserve1(self);
	new_node = (struct vm_node *)kmalloc(sizeof(struct vm_node),
	                                     GFP_LOCKED | GFP_PREFLT | GFP_VCBASE);
	self->pv_vec[self->pv_cnt].pn_node = new_node; /* Inherit */
	self->pv_vec[self->pv_cnt].pn_part = part;     /* Inherit reference */
	++self->pv_cnt;
}

PRIVATE void KCALL
partnode_pair_vector_insertpart(struct partnode_pair_vector *__restrict self, size_t index,
                                /*inherit(on_success)*/ REF struct vm_datapart *__restrict part)
		THROWS(E_WOULDBLOCK, E_BADALLOC) {
	struct vm_node *new_node;
	assert(index <= self->pv_cnt);
	partnode_pair_vector_reserve1(self);
	new_node = (struct vm_node *)kmalloc(sizeof(struct vm_node),
	                                     GFP_LOCKED | GFP_PREFLT | GFP_VCBASE);
	memmoveup(&self->pv_vec[index + 1],
	          &self->pv_vec[index],
	          self->pv_cnt - index,
	          sizeof(struct partnode_pair));
	self->pv_vec[index].pn_node = new_node; /* Inherit */
	self->pv_vec[index].pn_part = part;     /* Inherit reference */
	++self->pv_cnt;
}

/* Finalize the given pair vector under the assumption
 * that the caller has inherited all nodes, data part
 * references, and data part locks. */
PRIVATE NOBLOCK void
NOTHROW(KCALL partnode_pair_vector_fini_caller_inherited_parts)(struct partnode_pair_vector *__restrict self) {
	/* Free a dynamically allocated part vector. */
	if (self->pv_vec != self->pv_buf)
		kfree(self->pv_vec);
}

/* Finalize the given pair vector, as well as release write-locks
 * from all data parts, drop all held references from each of them
 * before freeing all allocated vm nodes. */
PRIVATE NOBLOCK void
NOTHROW(KCALL partnode_pair_vector_fini_and_unlock_parts)(struct partnode_pair_vector *__restrict self) {
	size_t i;
	assert(self->pv_cnt <= self->pv_alc);
	/* Unlock data parts */
	i = self->pv_cnt;
	while (i--)
		sync_endwrite(self->pv_vec[i].pn_part);
	/* Drop references from data parts */
	i = self->pv_cnt;
	while (i--)
		decref_unlikely(self->pv_vec[i].pn_part);
	/* Free pre-allocated VM nodes */
	i = self->pv_cnt;
	while (i--)
		kfree(self->pv_vec[i].pn_node);
	/* Free a dynamically allocated part vector. */
	if (self->pv_vec != self->pv_buf)
		kfree(self->pv_vec);
}

/* Collect and lock all parts required to span the given range of memory
 * within the specified data block, before acquiring a write-lock to all
 * of those parts and re-check that they still span the entirety of the
 * given memory range within `data'. Afterwards, acquire a write-lock to
 * the given `effective_vm', before returning to the caller with locks held
 * to all of the indicated data parts, as well as the given VM, allowing
 * them to then use those parts in order to create a mapping of them within
 * the given VM.
 * NOTE: For every part that is acquired, this function also allocates 1
 *      `struct vm_node' object which must also be inherited by the caller,
 *       essentially off-loading all of the hard preparation work required
 *       to map some region of a datablock into memory, as well as thread-safe
 *       acquisition of all of the required locks. */
PRIVATE void KCALL
vm_collect_and_lock_parts_and_vm(struct partnode_pair_vector *__restrict info,
                                 struct vm *__restrict effective_vm,
                                 struct vm_datablock *__restrict data,
                                 pageid64_t data_start_vpage,
                                 size_t num_pages,
                                 uintptr_half_t prot)
		THROWS(E_WOULDBLOCK, E_BADALLOC) {
	if (ATOMIC_READ(data->db_parts) == MFILE_PARTS_ANONYMOUS) {
		/* Simple case: We can allocate the part in its entirety, all from the get-go! */
		info->pv_vec            = info->pv_buf;
		info->pv_cnt            = 1;
		info->pv_buf[0].pn_node = (struct vm_node *)kmalloc(sizeof(struct vm_node),
		                                                    GFP_LOCKED | GFP_PREFLT | GFP_VCBASE);
		TRY {
			/* Create the associated part.
			 * NOTE: Because we're the ones creating it, we don't have to look
			 *       out for splitting parts, or anything in that manner. */
			info->pv_buf[0].pn_part = vm_paged_datablock_createpart(data,
			                                                        data_start_vpage,
			                                                        num_pages);
			/* The caller wants us to give them some write-lock, so let's given them one! */
			shared_rwlock_init_write(&info->pv_buf[0].pn_part->dp_lock);
			TRY {
				sync_write(effective_vm);
			} EXCEPT {
				destroy(info->pv_buf[0].pn_part);
				RETHROW();
			}
		} EXCEPT {
			kfree(info->pv_buf[0].pn_node);
			RETHROW();
		}
		return;
	}
	info->pv_vec = info->pv_buf;
	info->pv_cnt = 0;
	info->pv_alc = COMPILER_LENOF(info->pv_buf);
	TRY {
		REF struct vm_datapart *part;
		size_t total_pages;
		/* Step #1: Collect all of the required parts. */
		part = vm_paged_datablock_locatepart_exact(data,
		                                           data_start_vpage,
		                                           num_pages);
		TRY {
			partnode_pair_vector_addpart(info, part);
		} EXCEPT {
			vm_datapart_decref_and_merge(part);
			RETHROW();
		}
		/* Load additional parts which may span the specified range. */
		total_pages = vm_datapart_numvpages_atomic(part);
		while (total_pages < num_pages) {
			part = vm_paged_datablock_locatepart_exact(data,
			                                           data_start_vpage + total_pages,
			                                           num_pages - total_pages);
			TRY {
				partnode_pair_vector_addpart(info, part);
			} EXCEPT {
				vm_datapart_decref_and_merge(part);
				RETHROW();
			}
			/* NOTE: The reference to `part' was inherited by `partnode_pair_vector_addpart()' */
			total_pages += vm_datapart_numvpages_atomic(part);
		}
		assert(total_pages == num_pages);
		/* We've now (presumably) gathered all of the necessary pages
		 * Now it's time to lock all of them and check to make sure that
		 * no gaps have formed prior to us acquiring locks to all of them. */
again_lock_all_parts:
		for (;;) {
			part = partnode_pair_vector_trywrite_parts(info);
			if likely(!part)
				break;
			sync_write(part);
			sync_endwrite(part);
		}
		/* With all of the necessary locks no held, check if they still form
		 * a continuous range of parts that span the entirety of requested
		 * address range. */
		{
			size_t i;
			COMPILER_READ_BARRIER();
			for (i = 0; i < info->pv_cnt; ++i) {
				pageid64_t part_end, req_part_end;
				req_part_end = i == info->pv_cnt - 1
				               ? data_start_vpage + num_pages
				               : vm_datapart_startvpage(info->pv_vec[i + 1].pn_part);
				part_end = vm_datapart_endvpage(info->pv_vec[i].pn_part);
				assert(part_end <= req_part_end);
				if (part_end >= req_part_end)
					continue; /* Continuous */
				/* There's a part missing between `part_end' and `req_part_end' */
				partnode_pair_vector_endwrite_parts(info);
				part = vm_paged_datablock_locatepart_exact(data, part_end,
				                                     (size_t)(req_part_end - part_end));
				TRY {
					partnode_pair_vector_insertpart(info, i + 1, part);
				} EXCEPT {
					vm_datapart_decref_and_merge(part);
					RETHROW();
				}
				/* Re-acquire locks to all of the necessary parts. */
				goto again_lock_all_parts;
			}
			if (!(prot & VM_PROT_SHARED)) {
				/* When the caller is mapping with write-permissions, must
				 * delete write permissions for other mappings:
				 * >> if (prot & VM_PROT_SHARED) {
				 * >>  LLIST_INSERT(part->dp_srefs,node,vn_link);
				 * >> } else {
				 * >>  // The addition of the first copy-on-write mapping requires
				 * >>  // that all existing SHARED memory mappings be updated to
				 * >>  // not include write permissions in their page directories.
				 * >>  // That way, a #PF will be triggered which will then unshare
				 * >>  // our own data part, preventing writes to the shared mapping
				 * >>  // from leaking into private mappings.
				 * >>  if (part->dp_crefs == NULL)
				 * >>      PAGEDIR_REMOVE_WRITE_FOR_ALL(part->dp_srefs);
				 * >>  else if (NEXT(part->dp_crefs) == NULL &&
				 * >>           ATOMIC_READ(part->dp_block->db_parts) == MFILE_PARTS_ANONYMOUS) {
				 * >>      // If this is the second copy-on-write mapping of an anonymous data part,
				 * >>      // then the first one may have had write permissions which must now be
				 * >>      // unshared (this is the case for general purpose RAM during fork())
				 * >>      PAGEDIR_REMOVE_WRITE_FOR_ONE(part->dp_crefs);
				 * >>  }
				 * >>  LLIST_INSERT(part->dp_crefs,node,vn_link);
				 * >> } */
				for (i = 0; i < info->pv_cnt; ++i) {
					struct vm_datapart *vecpart;
					unsigned int error;
					REF struct vm *blocking_vm;
					vecpart = info->pv_vec[i].pn_part;
					if (vecpart->dp_crefs == NULL) {
						struct vm_node *iter;
						/* The addition of the first copy-on-write mapping requires
						 * that all existing SHARED memory mappings be updated to
						 * not include write permissions in their page directories.
						 * That way, a #PF will be triggered which will then unshare
						 * our own data part, preventing writes to the shared mapping
						 * from leaking into private mappings. */
						for (iter = vecpart->dp_srefs; iter;
						     iter = iter->vn_link.ln_next) {
							error = vm_node_update_write_access(iter);
							if unlikely(error != VM_NODE_UPDATE_WRITE_ACCESS_SUCCESS) {
								blocking_vm = iter->vn_vm;
								goto handle_remove_write_error;
							}
						}
					} else if (vecpart->dp_crefs->vn_link.ln_next == NULL &&
					           /* If this is the second copy-on-write mapping of an anonymous data part,
					            * then the first one may have had write permissions which must now be
					            * unshared (this is the case for general purpose RAM during fork()) */
					           ATOMIC_READ(vecpart->dp_block->db_parts) == MFILE_PARTS_ANONYMOUS) {
						error = vm_node_update_write_access(vecpart->dp_crefs);
						if unlikely(error != VM_NODE_UPDATE_WRITE_ACCESS_SUCCESS) {
							blocking_vm = vecpart->dp_crefs->vn_vm;
handle_remove_write_error:
							if (error == VM_NODE_UPDATE_WRITE_ACCESS_BADALLOC) {
								partnode_pair_vector_endwrite_parts(info);
								THROW(E_BADALLOC_INSUFFICIENT_PHYSICAL_MEMORY, PAGESIZE);
							}
							if (!tryincref(blocking_vm))
								blocking_vm = NULL;
							partnode_pair_vector_endwrite_parts(info);
							assert(error == VM_NODE_UPDATE_WRITE_ACCESS_WOULDBLOCK);
							if (blocking_vm) {
								FINALLY_DECREF_UNLIKELY(blocking_vm);
								sync_write(blocking_vm);
								sync_endwrite(blocking_vm);
							}
							goto again_lock_all_parts;
						}
					}
				}
			}
		}
		/* And we're done! - We've got a lock to a continuous range of data parts,
		 * so now all that's still missing is getting a lock on the given `effective_vm'
		 * If this fails, we simply have to do some more lock juggling, before re-locking
		 * all of the associated data parts and re-checking for gaps. */
		if (!sync_trywrite(effective_vm)) {
			partnode_pair_vector_endwrite_parts(info);
			sync_write(effective_vm);
			sync_endwrite(effective_vm);
			goto again_lock_all_parts;
		}
	} EXCEPT {
		partnode_pair_vector_fini_and_unlock_parts(info);
		RETHROW();
	}
}



/* Map the memory region into the given VM.
 * The caller may invoke `vm_paged_sync()' after changes have been made.
 * @param: prot:   Set of `VM_PROT_*'.
 * @param: flag:   Set of `VM_NODE_FLAG_*'.
 * @param: data_start_vpage: The memory page index where mapping of `data' starts.
 * @param: fspath: Optional mapping path (only used for memory->disk mapping listings)
 * @param: fsname: Optional mapping name (only used for memory->disk mapping listings)
 * @param: guard:  If non-zero, repetition limit for a guard mapping.
 *                 Set to 0 if the mapping shouldn't include a guard.
 * @return: true:  Successfully created the mapping.
 * @return: false: Another mapping already exists. */
PUBLIC WUNUSED NONNULL((1, 4)) bool KCALL
vm_mapat(struct vm *__restrict self,
         PAGEDIR_PAGEALIGNED UNCHECKED void *addr,
         PAGEDIR_PAGEALIGNED size_t num_bytes,
         struct vm_datablock *__restrict data,
         struct path *fspath,
         struct directory_entry *fsname,
         PAGEDIR_PAGEALIGNED pos_t data_start_offset,
         uintptr_half_t prot, uintptr_half_t flag, uintptr_t guard) {
	size_t i, num_pages;
	struct partnode_pair_vector parts;
	pageid_t pageid;
	assert(((uintptr_t)addr & PAGEMASK) == 0);
	assert((num_bytes & PAGEMASK) == 0);
	assert((data_start_offset & PAGEMASK) == 0);
	assert(!(flag & (VM_NODE_FLAG_COREPRT | VM_NODE_FLAG_KERNPRT | VM_NODE_FLAG_HINTED | VM_NODE_FLAG_GROWSUP)));
	assert(!(prot & ~(VM_PROT_EXEC | VM_PROT_WRITE | VM_PROT_READ | VM_PROT_LOOSE | VM_PROT_SHARED)));
	if unlikely(!num_bytes)
		return true;
	/* Load parts & acquire locks. */
	num_pages = num_bytes / PAGESIZE;
	pageid    = PAGEID_ENCODE(addr);
	vm_collect_and_lock_parts_and_vm(&parts,
	                                 self,
	                                 data,
	                                 (pageid64_t)(data_start_offset / PAGESIZE),
	                                 num_pages,
	                                 prot);
	/* The rest of this function is already NOEXCEPT at this point.
	 * However, we still need to check that the indicated range isn't
	 * already being used by some other mapping! */
	if unlikely(vm_nodetree_rlocate(self->v_tree,
	                                pageid,
	                                pageid + num_pages - 1)) {
		/* It _is_ already being used... */
		sync_endwrite(self);
		partnode_pair_vector_fini_and_unlock_parts(&parts);
		return false;
	}
	VM_MAP_TRACE(KERN_DEBUG "[vm] Map %p...%p against %" PRIuSIZ " data parts\n",
	             (byte_t *)addr,
	             (byte_t *)addr + num_bytes - 1,
	             parts.pv_cnt);
	/* Must prepare the given address range beforehand! */
	if (flag & VM_NODE_FLAG_PREPARED) {
		if (!pagedir_prepare(addr, num_bytes)) {
			sync_endwrite(self);
			partnode_pair_vector_fini_and_unlock_parts(&parts);
			THROW(E_BADALLOC_INSUFFICIENT_PHYSICAL_MEMORY, PAGESIZE);
		}
	}

	/* Now to use what we were given, and initialize the memory mapping! */
	assert(parts.pv_cnt != 0);
	for (i = 0; i < parts.pv_cnt; ++i) {
		struct vm_datapart *part;
		struct vm_node *node;
		size_t part_pages;
		part = parts.pv_vec[i].pn_part;
		node = parts.pv_vec[i].pn_node;
		assert(sync_writing(part));
		assert(node);

		/* Initialize the given node. */
		part_pages           = vm_datapart_numvpages(part);
		node->vn_node.a_vmin = pageid;
		node->vn_node.a_vmax = pageid + part_pages - 1;
		node->vn_prot        = prot;
		node->vn_flags       = flag & (VM_NODE_FLAG_PREPARED | VM_NODE_FLAG_NOMERGE);
		node->vn_vm          = self;
		node->vn_part        = part; /* Inherit reference */
		node->vn_block       = incref(data);
		node->vn_fspath      = xincref(fspath);
		node->vn_fsname      = xincref(fsname);
		node->vn_guard       = 0;
		if (prot & VM_PROT_SHARED) {
			LLIST_INSERT(part->dp_srefs, node, vn_link);
		} else {
			LLIST_INSERT(part->dp_crefs, node, vn_link);
		}
		/* Map the given node into its associated VM */
		vm_node_insert(node);
		/* Release the write-lock from parts, as they are mapped. */
		sync_endwrite(part);
		pageid += part_pages;
	}

	/* Apply a guard to the appropriate page. */
	if (guard != 0) {
		if (flag & VM_NODE_FLAG_GROWSUP) {
			parts.pv_vec[parts.pv_cnt - 1].pn_node->vn_guard = guard;
			parts.pv_vec[parts.pv_cnt - 1].pn_node->vn_flags |= VM_NODE_FLAG_GROWSUP;
		} else {
			parts.pv_vec[0].pn_node->vn_guard = guard;
		}
	}
	sync_endwrite(self);
	partnode_pair_vector_fini_caller_inherited_parts(&parts);
	return true;
}


/* Create a memory reservation mapping at the given address.
 * @param: flag: Set of `VM_NODE_FLAG_PREPARED | VM_NODE_FLAG_NOMERGE'
 * @return: true:  Successfully created the mapping.
 * @return: false: Another mapping already exists. */
PUBLIC WUNUSED NONNULL((1)) bool KCALL
vm_mapresat(struct vm *__restrict self,
            PAGEDIR_PAGEALIGNED UNCHECKED void *addr,
            PAGEDIR_PAGEALIGNED size_t num_bytes,
            uintptr_half_t flag)
		THROWS(E_WOULDBLOCK, E_BADALLOC) {
	struct vm_node *node;
	pageid_t pageid;
	size_t num_pages;
	assert(((uintptr_t)addr & PAGEMASK) == 0);
	assert((num_bytes & PAGEMASK) == 0);
	assert(!(flag & ~(VM_NODE_FLAG_PREPARED | VM_NODE_FLAG_NOMERGE)));
	if unlikely(!num_bytes)
		return true;
	pageid    = PAGEID_ENCODE(addr);
	num_pages = num_bytes / PAGESIZE;
	node = (struct vm_node *)kmalloc(sizeof(struct vm_node),
	                                 GFP_LOCKED | GFP_PREFLT | GFP_VCBASE);
	node->vn_node.a_vmin = pageid;
	node->vn_node.a_vmax = pageid + num_pages - 1;
	node->vn_prot        = VM_PROT_NONE;
	node->vn_flags       = flag;
	node->vn_vm          = self;
	node->vn_part        = NULL;
	node->vn_block       = NULL;
	node->vn_fspath      = NULL;
	node->vn_fsname      = NULL;
#ifndef NDEBUG
	memset(&node->vn_link, 0xcc, sizeof(node->vn_link));
#endif /* !NDEBUG */
	node->vn_guard = 0;
	TRY {
		sync_write(self);
	} EXCEPT {
		kfree(node);
		RETHROW();
	}
	/* Check if the specified range is already in use. */
	if unlikely(vm_nodetree_rlocate(self->v_tree,
	                                pageid,
	                                pageid + num_pages - 1)) {
		sync_endwrite(self);
		kfree(node);
		return false;
	}
	/* Must prepare the given address range beforehand! */
	if (flag & VM_NODE_FLAG_PREPARED) {
		if (!pagedir_prepare(addr, num_bytes)) {
			sync_endwrite(self);
			kfree(node);
			THROW(E_BADALLOC_INSUFFICIENT_PHYSICAL_MEMORY, PAGESIZE);
		}
	}
	/* Insert the new node into the given VM. */
	vm_node_insert(node);
	sync_endwrite(self);
	return true;
}



/* A combination of `vm_paged_getfree' + `vm_paged_mapat'
 * @throw: E_BADALLOC_INSUFFICIENT_VIRTUAL_MEMORY: Failed to find suitable target. */
FUNDEF WUNUSED NONNULL((1, 6)) PAGEDIR_PAGEALIGNED UNCHECKED void *KCALL
vm_map(struct vm *__restrict self,
       PAGEDIR_PAGEALIGNED UNCHECKED void *hint,
       PAGEDIR_PAGEALIGNED size_t num_bytes,
       PAGEDIR_PAGEALIGNED size_t min_alignment,
       unsigned int getfree_mode,
       struct vm_datablock *__restrict data,
       struct path *fspath,
       struct directory_entry *fsname,
       PAGEDIR_PAGEALIGNED pos_t data_start_offset,
       uintptr_half_t prot,
       uintptr_half_t flag,
       uintptr_t guard)
		THROWS(E_WOULDBLOCK, E_BADALLOC) {
	size_t i;
	void *result;
	pageid_t result_pageid, offset_pageid;
	uintptr_t version = 0;
	struct partnode_pair_vector parts;
	assert(((uintptr_t)hint & PAGEMASK) == 0);
	assert((num_bytes & PAGEMASK) == 0);
	assert((min_alignment & PAGEMASK) == 0);
	assert((data_start_offset & PAGEMASK) == 0);
	assert(!(flag & (VM_NODE_FLAG_COREPRT | VM_NODE_FLAG_KERNPRT | VM_NODE_FLAG_HINTED)));
	assert(!(prot & ~(VM_PROT_EXEC | VM_PROT_WRITE | VM_PROT_READ | VM_PROT_LOOSE | VM_PROT_SHARED)));
	if unlikely(!num_bytes)
		num_bytes = PAGESIZE;
again:
	/* Load parts & acquire locks. */
	vm_collect_and_lock_parts_and_vm(&parts,
	                                 self,
	                                 data,
	                                 (pageid64_t)(data_start_offset / PAGESIZE),
	                                 num_bytes / PAGESIZE,
	                                 prot);
#ifndef NDEBUG
	for (i = 0; i < parts.pv_cnt; ++i) {
		struct vm_datapart *part;
		part = parts.pv_vec[i].pn_part;
		assert(!part->dp_futex || ADDR_ISKERN(part->dp_futex));
	}
#endif /* !NDEBUG */
	/* The rest of this function is already NOEXCEPT at this point.
	 * However, we still need to check that the indicated range isn't
	 * already being used by some other mapping! */
	result = vm_getfree(self, hint, num_bytes, min_alignment, getfree_mode);
	if unlikely(result == VM_GETFREE_ERROR) {
		/* It _is_ already being used... */
		sync_endwrite(self);
		partnode_pair_vector_fini_and_unlock_parts(&parts);
		if (self == &vm_kernel) {
			if (system_clearcaches_s(&version))
				goto again;
		}
		THROW(E_BADALLOC_INSUFFICIENT_VIRTUAL_MEMORY,
		      num_bytes);
	}
	assertf(!vm_isused(self, result, num_bytes),
	        "result = %p...%p\n",
	        result, (byte_t *)result + num_bytes - 1);
	VM_MAP_TRACE(KERN_DEBUG "[vm] Map %p...%p against %" PRIuSIZ " data parts\n",
	             result, (byte_t *)result + num_bytes - 1,
	             parts.pv_cnt);
	/* Must prepare the given address range beforehand! */
	if (flag & VM_NODE_FLAG_PREPARED) {
		if (!pagedir_prepare(result, num_bytes)) {
			sync_endwrite(self);
			partnode_pair_vector_fini_and_unlock_parts(&parts);
			THROW(E_BADALLOC_INSUFFICIENT_PHYSICAL_MEMORY, PAGESIZE);
		}
	}

	/* Now to use what we were given, and initialize the memory mapping! */
	assert(parts.pv_cnt != 0);
	result_pageid = PAGEID_ENCODE(result);
	offset_pageid = result_pageid;
	for (i = 0; i < parts.pv_cnt; ++i) {
		struct vm_datapart *part;
		struct vm_node *node;
		size_t part_pages;
		part = parts.pv_vec[i].pn_part;
		node = parts.pv_vec[i].pn_node;
		assert(sync_writing(part));
		assert(node);
		assert(!part->dp_futex || ADDR_ISKERN(part->dp_futex));

		/* Initialize the given node. */
		part_pages = vm_datapart_numvpages(part);
		assertf(offset_pageid + part_pages <=
		        result_pageid + num_bytes / PAGESIZE,
		        "offset = %p...%p (%" PRIuSIZ " pages)\n"
		        "result = %p...%p (%" PRIuSIZ " pages)\n",
		        (byte_t *)PAGEID_DECODE(offset_pageid),
		        (byte_t *)PAGEID_DECODE(offset_pageid + part_pages) - 1, part_pages,
		        result, (byte_t *)result + num_bytes - 1, num_bytes / PAGESIZE);
		assertf(!vm_paged_isused(self, offset_pageid, offset_pageid + part_pages - 1),
		        "offset = %p...%p (%" PRIuSIZ " pages)\n"
		        "result = %p...%p (%" PRIuSIZ " pages)\n",
		        (byte_t *)PAGEID_DECODE(offset_pageid),
		        (byte_t *)PAGEID_DECODE(offset_pageid + part_pages) - 1, part_pages,
		        result, (byte_t *)result + num_bytes - 1, num_bytes / PAGESIZE);
		assert(!part->dp_futex || ADDR_ISKERN(part->dp_futex));
		node->vn_node.a_vmin = offset_pageid;
		node->vn_node.a_vmax = offset_pageid + part_pages - 1;
		node->vn_prot        = prot;
		node->vn_flags       = flag & (VM_NODE_FLAG_PREPARED | VM_NODE_FLAG_NOMERGE);
		node->vn_vm          = self;
		node->vn_part        = part; /* Inherit reference */
		node->vn_block       = incref(data);
		node->vn_fspath      = xincref(fspath);
		node->vn_fsname      = xincref(fsname);
		node->vn_guard       = 0;
		assert(!part->dp_futex || ADDR_ISKERN(part->dp_futex));
		if (prot & VM_PROT_SHARED) {
			LLIST_INSERT(part->dp_srefs, node, vn_link);
		} else {
			LLIST_INSERT(part->dp_crefs, node, vn_link);
		}
		assert(!part->dp_futex || ADDR_ISKERN(part->dp_futex));
		/* Map the given node into its associated VM */
		vm_node_insert(node);
		assert(!part->dp_futex || ADDR_ISKERN(part->dp_futex));
		/* Release the write-lock from parts, as they are mapped. */
		sync_endwrite(part);
		offset_pageid += part_pages;
	}
	assertf(offset_pageid == result_pageid + num_bytes / PAGESIZE,
	        "offset             = %p\n"
	        "result + num_bytes = %p\n"
	        "result             = %p\n"
	        "num_bytes          = %" PRIuSIZ "\n",
	        PAGEID_DECODE(offset_pageid),
	        (byte_t *)result + num_bytes,
	        (byte_t *)result, num_bytes);

	/* Apply a guard to the appropriate page. */
	if (guard != 0) {
		if (flag & VM_NODE_FLAG_GROWSUP) {
			parts.pv_vec[parts.pv_cnt - 1].pn_node->vn_guard = guard;
			parts.pv_vec[parts.pv_cnt - 1].pn_node->vn_flags |= VM_NODE_FLAG_GROWSUP;
		} else {
			parts.pv_vec[0].pn_node->vn_guard = guard;
		}
	}
	sync_endwrite(self);
	partnode_pair_vector_fini_caller_inherited_parts(&parts);
	return result;
}




/* A combination of `vm_paged_getfree' + `vm_mapresat'
 * @throw: E_BADALLOC_INSUFFICIENT_VIRTUAL_MEMORY: Failed to find suitable target. */
PUBLIC UNCHECKED void *KCALL
vm_mapres(struct vm *__restrict self,
          PAGEDIR_PAGEALIGNED UNCHECKED void *hint,
          PAGEDIR_PAGEALIGNED size_t num_bytes,
          PAGEDIR_PAGEALIGNED size_t min_alignment,
          unsigned int getfree_mode,
          uintptr_half_t flag)
		THROWS(E_WOULDBLOCK, E_BADALLOC) {
	struct vm_node *node;
	UNCHECKED void *result;
	uintptr_t version = 0;
	assert(((uintptr_t)hint & PAGEMASK) == 0);
	assert((num_bytes & PAGEMASK) == 0);
	assert((min_alignment & PAGEMASK) == 0);
	assert(!(flag & ~(VM_NODE_FLAG_PREPARED | VM_NODE_FLAG_NOMERGE)));
	if unlikely(!num_bytes)
		num_bytes = PAGESIZE;

	node = (struct vm_node *)kmalloc(sizeof(struct vm_node),
	                                 GFP_LOCKED | GFP_PREFLT | GFP_VCBASE);
	node->vn_prot   = VM_PROT_NONE;
	node->vn_flags  = flag;
	node->vn_vm     = self;
	node->vn_part   = NULL;
	node->vn_block  = NULL;
	node->vn_fspath = NULL;
	node->vn_fsname = NULL;
#ifndef NDEBUG
	memset(&node->vn_link, 0xcc, sizeof(node->vn_link));
#endif /* !NDEBUG */
	node->vn_guard = 0;
again_lock_vm:
	TRY {
		sync_write(self);
	} EXCEPT {
		kfree(node);
		RETHROW();
	}
	/* Figure out a suitable mapping location */
	result = vm_getfree(self,
	                    hint,
	                    num_bytes,
	                    min_alignment,
	                    getfree_mode);
	if unlikely(result == VM_GETFREE_ERROR) {
		/* It _is_ already being used... */
		sync_endwrite(self);
		if (self == &vm_kernel) {
			if (system_clearcaches_s(&version))
				goto again_lock_vm;
		}
		kfree(node);
		THROW(E_BADALLOC_INSUFFICIENT_VIRTUAL_MEMORY,
		      num_bytes);
	}

	node->vn_node.a_vmin = PAGEID_ENCODE(result);
	node->vn_node.a_vmax = node->vn_node.a_vmin + (num_bytes / PAGESIZE) - 1;
	/* Must prepare the given address range beforehand! */
	if (flag & VM_NODE_FLAG_PREPARED) {
		if (!pagedir_prepare(result, num_bytes)) {
			sync_endwrite(self);
			kfree(node);
			THROW(E_BADALLOC_INSUFFICIENT_PHYSICAL_MEMORY, PAGESIZE);
		}
	}
	/* Insert the new node into the given VM. */
	vm_node_insert(node);
	sync_endwrite(self);
	return result;
}

struct vm_map_subrange_descriptors {
	REF struct vm_datapart     *sd_zeropart;  /* [1..1] The data part bound to `sd_zeronode'
	                                           * NOTE: No lock is held on this datapart! */
	struct vm_node             *sd_zeronode;  /* [1..1][owned] The VM node used to map trailing ZERO-memory. */
	struct partnode_pair_vector sd_dataparts; /* Data parts and nodes for mapping the data-portion.
	                                           * NOTE: Write-locks are held on all data parts in this vector. */
};

/* Finalize and release all relevant data (to-be used in the failure case). */
PRIVATE NOBLOCK void
NOTHROW(KCALL vm_map_subrange_descriptors_fini_and_unlock_parts)(struct vm_map_subrange_descriptors *__restrict self) {
	/* Finalize and unlock data parts. */
	partnode_pair_vector_fini_and_unlock_parts(&self->sd_dataparts);
	/* Destroy the zero-mapping. */
	assert(self->sd_zeronode->vn_block == &vm_datablock_anonymous_zero);
	assert(self->sd_zeronode->vn_part == self->sd_zeropart);
	assert(self->sd_zeronode->vn_fspath == NULL);
	assert(self->sd_zeronode->vn_fsname == NULL);
	decref_nokill(&vm_datablock_anonymous_zero); /* self->sd_zeronode->vn_block */
	decref_likely(self->sd_zeropart);            /* self->sd_zeropart */
	kfree(self->sd_zeronode);
}

/* Finalize under the assumption that the caller has inherited all relevant data. */
PRIVATE NOBLOCK void
NOTHROW(KCALL vm_map_subrange_descriptors_fini_caller_inherited_parts)(struct vm_map_subrange_descriptors *__restrict self) {
	partnode_pair_vector_fini_caller_inherited_parts(&self->sd_dataparts);
}

/* Initialize all vm nodes/parts required for mapping a two-fold data+oob=zero memory
 * mapping, with the data-portion starting at `data_minmappage' in `data', and spanning
 * a total of `num_datavpages' pages, followed by a mapping of `vm_datablock_anonymous_zero'
 * that spans a total of `num_zerovpages' pages.
 * NOTE: This function also acquires a write-lock to `effective_vm'! */
PRIVATE void KCALL
vm_map_subrange_descriptors_init_and_lock_parts_and_vm(struct vm_map_subrange_descriptors *__restrict self,
                                                       struct vm *__restrict effective_vm,
                                                       struct vm_datablock *__restrict data,
                                                       pageid64_t data_minmappage,
                                                       size_t num_datavpages,
                                                       size_t num_zerovpages,
                                                       uintptr_half_t prot)
		THROWS(E_WOULDBLOCK, E_BADALLOC) {
	REF struct vm_datapart *zeropart;
	struct vm_node *zeronode;
	assert(num_datavpages != 0);
	assert(num_zerovpages != 0);
	assert(!(prot & ~(VM_PROT_EXEC | VM_PROT_WRITE | VM_PROT_READ | VM_PROT_LOOSE | VM_PROT_SHARED)));
	/* Create the zero-part */
	zeronode = (struct vm_node *)kmalloc(sizeof(struct vm_node),
	                                     GFP_LOCKED | GFP_PREFLT | GFP_VCBASE);
	TRY {
		zeropart = vm_paged_datablock_createpart(&vm_datablock_anonymous_zero,
		                                         0, num_zerovpages);
		assert(!isshared(zeropart));
		TRY {
			/* Load data parts & acquire locks. */
			vm_collect_and_lock_parts_and_vm(&self->sd_dataparts,
			                                 effective_vm,
			                                 data,
			                                 data_minmappage,
			                                 num_datavpages,
			                                 prot);
		} EXCEPT {
			assert(!isshared(zeropart));
			destroy(zeropart);
			RETHROW();
		}
	} EXCEPT {
		kfree(zeronode);
		RETHROW();
	}
	self->sd_zeropart = zeropart; /* Inherit */
	self->sd_zeronode = zeronode; /* Inherit */
}

/* Insert all data mappings, as well as the zero-mapping into the given `effective_vm'.
 * During this operation, write-locks held on each data-part, and have `effective_vm'
 * inherit all data parts, and nodes such that `self' must be finalized by a call to
 * `vm_map_subrange_descriptors_fini_caller_inherited_parts()' */
PRIVATE NOBLOCK NONNULL((1, 2, 3)) void
NOTHROW(KCALL vm_map_subrange_descriptors_insert_into_vm)(struct vm_map_subrange_descriptors *__restrict self,
                                                          struct vm *__restrict effective_vm,
                                                          struct vm_datablock *__restrict data,
                                                          struct path *fspath,
                                                          struct directory_entry *fsname,
                                                          size_t num_datavpages,
                                                          size_t num_zerovpages,
                                                          pageid_t base_offset,
                                                          uintptr_half_t prot,
                                                          uintptr_half_t flag,
                                                          uintptr_t guard) {
	struct partnode_pair *partvec;
	size_t i, partcnt;
	pageid_t node_minpage;
	assert(num_datavpages);
	assert(num_zerovpages);
	assert((size_t)(num_datavpages + num_zerovpages) > num_datavpages);
	assert((size_t)(num_datavpages + num_zerovpages) > num_zerovpages);
	assert((pageid_t)(base_offset + num_datavpages + num_zerovpages - 1) >= base_offset);
	assert(sync_writing(effective_vm));
	assert(!vm_paged_isused(effective_vm, base_offset, base_offset + num_datavpages + num_zerovpages - 1));
	assert(!(flag & (VM_NODE_FLAG_COREPRT | VM_NODE_FLAG_KERNPRT | VM_NODE_FLAG_HINTED)));
	assert(!(prot & ~(VM_PROT_EXEC | VM_PROT_WRITE | VM_PROT_READ | VM_PROT_LOOSE | VM_PROT_SHARED)));
	partvec = self->sd_dataparts.pv_vec;
	partcnt = self->sd_dataparts.pv_cnt;
	assert(partcnt != 0);
	(void)num_datavpages;
	(void)num_zerovpages;

	/* Initialize data nodes and insert them into the given VM. */
	node_minpage = base_offset;
	for (i = 0; i < partcnt; ++i) {
		struct vm_datapart *part;
		struct vm_node *node;
		size_t part_vpages;
		part = partvec[i].pn_part;
		node = partvec[i].pn_node;
		part_vpages = vm_datapart_numvpages(part);
		assert(sync_writing(part));
		node->vn_node.a_vmin = node_minpage;
		node->vn_node.a_vmax = node_minpage + part_vpages - 1;
		node->vn_prot        = prot;
		node->vn_flags       = flag & (VM_NODE_FLAG_PREPARED | VM_NODE_FLAG_NOMERGE);
		node->vn_vm          = effective_vm;
		node->vn_part        = part; /* Inherit reference */
		node->vn_block       = incref(data);
		node->vn_fspath      = xincref(fspath);
		node->vn_fsname      = xincref(fsname);
		node->vn_guard       = 0;
		if (prot & VM_PROT_SHARED) {
			LLIST_INSERT(part->dp_srefs, node, vn_link);
		} else {
			LLIST_INSERT(part->dp_crefs, node, vn_link);
		}
		/* Map the given node into its associated VM */
		vm_node_insert(node);
		/* Release the write-lock from parts, as they are mapped. */
		sync_endwrite(part);
		/* Advance to the next node. */
		node_minpage += part_vpages;
	}
	assertf(node_minpage == base_offset + num_datavpages,
	        "Miss-matching data size (is:%" PRIuSIZ " != expected:%" PRIuSIZ ")",
	        (size_t)(node_minpage - base_offset),
	        (size_t)(num_datavpages));
	/* Map the zero-node. */
	{
		struct vm_datapart *part;
		struct vm_node *node;
		part = self->sd_zeropart;
		node = self->sd_zeronode;
		assert(!isshared(part));
		assert(part->dp_block == &vm_datablock_anonymous_zero);
		assert(vm_datapart_numvpages(part) == num_zerovpages);
		node->vn_node.a_vmin = node_minpage;
		node->vn_node.a_vmax = node_minpage + num_zerovpages - 1;
		node->vn_prot        = prot;
		node->vn_flags       = flag & (VM_NODE_FLAG_PREPARED | VM_NODE_FLAG_NOMERGE);
		node->vn_vm          = effective_vm;
		node->vn_part        = part; /* Inherit reference */
		node->vn_block       = incref(&vm_datablock_anonymous_zero);
		node->vn_fspath      = NULL;
		node->vn_fsname      = NULL;
		node->vn_guard       = 0;
		if (prot & VM_PROT_SHARED) {
			LLIST_INSERT(part->dp_srefs, node, vn_link);
		} else {
			LLIST_INSERT(part->dp_crefs, node, vn_link);
		}
		/* Map the given node into its associated VM */
		vm_node_insert(node);
	}

	/* Apply a guard to the appropriate page. */
	if (guard != 0) {
		if (flag & VM_NODE_FLAG_GROWSUP) {
			self->sd_zeronode->vn_guard = guard;
			self->sd_zeronode->vn_flags |= VM_NODE_FLAG_GROWSUP;
		} else {
			partvec[0].pn_node->vn_guard = guard;
		}
	}
}


/* Same as `vm_paged_map()', but only allowed pages between `data_subrange_minvpage ... data_subrange_maxvpage'
 * to be mapped from `data'. - Any attempted to map data from outside that range will instead cause
 * memory from `vm_datablock_anonymous_zero' to be mapped.
 * Additionally, `data_start_vpage' is an offset from `data_subrange_minvpage'
 * @param: fspath: Optional mapping path (only used for memory->disk mapping listings)
 * @param: fsname: Optional mapping name (only used for memory->disk mapping listings) */
PUBLIC pageid_t KCALL
vm_paged_map_subrange(struct vm *__restrict effective_vm,
                      pageid_t hint,
                      size_t num_pages,
                      size_t min_alignment_in_pages,
                      unsigned int getfree_mode,
                      struct vm_datablock *__restrict data,
                      struct path *fspath,
                      struct directory_entry *fsname,
                      pageid64_t data_start_vpage,
                      pageid64_t data_subrange_minvpage,
                      pageid64_t data_subrange_maxvpage,
                      uintptr_half_t prot,
                      uintptr_half_t flag,
                      uintptr_t guard)
		THROWS(E_WOULDBLOCK, E_BADALLOC) {
	pageid_t result;
	pageid64_t data_minmappage, data_maxmappage;
	if unlikely(!num_pages)
		num_pages = 1;
	if (OVERFLOW_UADD(data_subrange_minvpage, data_start_vpage, &data_minmappage) ||
		data_minmappage > data_subrange_maxvpage) {
		/* The entire range is out-of-bounds.
		 * Map everything as ANON+ZERO */
		result = vm_paged_map(effective_vm,
		                      hint,
		                      num_pages,
		                      min_alignment_in_pages,
		                      getfree_mode,
		                      &vm_datablock_anonymous_zero,
		                      NULL,
		                      NULL,
		                      0,
		                      prot,
		                      flag,
		                      guard);
		goto done;
	}
	if (OVERFLOW_UADD(data_minmappage, num_pages - 1, &data_maxmappage) ||
	    data_maxmappage > data_subrange_maxvpage) {
		size_t num_datavpages, num_zerovpages;
		struct vm_map_subrange_descriptors sr;
		uintptr_t version = 0;
		num_datavpages = (size_t)(data_subrange_maxvpage - data_minmappage) + 1;
		num_zerovpages = num_pages - num_datavpages;
		assert(num_datavpages != 0);
		assert(num_zerovpages != 0);
		if (num_datavpages > num_pages)
			num_datavpages = num_pages; /* This can happen due to the presence of a guard. */
		/* Must map as 2 parts:
		 * A total of `num_datavpages' from data+data_minmappage, followed by
		 * a total of `num_zerovpages' from `&vm_datablock_anonymous_zero'.
		 * To prevent race conditions, we must map both of these at the same time! */
again_create_sr:
		vm_map_subrange_descriptors_init_and_lock_parts_and_vm(&sr,
		                                                       effective_vm,
		                                                       data,
		                                                       data_minmappage,
		                                                       num_datavpages,
		                                                       num_zerovpages,
		                                                       prot);
		/* Figure out where the mapping should go. */
		result = vm_paged_getfree(effective_vm,
		                          hint,
		                          num_pages,
		                          min_alignment_in_pages,
		                          getfree_mode);
		if unlikely(result == VM_PAGED_GETFREE_ERROR) {
			sync_endwrite(effective_vm);
			vm_map_subrange_descriptors_fini_and_unlock_parts(&sr);
			if (effective_vm == &vm_kernel) {
				if (system_clearcaches_s(&version))
					goto again_create_sr;
			}
			THROW(E_BADALLOC_INSUFFICIENT_VIRTUAL_MEMORY,
			      num_pages);
		}
		/* Insert created mappings into the VM. */
		vm_map_subrange_descriptors_insert_into_vm(&sr,
		                                           effective_vm,
		                                           data,
		                                           fspath,
		                                           fsname,
		                                           num_datavpages,
		                                           num_zerovpages,
		                                           result,
		                                           prot,
		                                           flag,
		                                           guard);
		sync_endwrite(effective_vm);
		vm_map_subrange_descriptors_fini_caller_inherited_parts(&sr);
		goto done;
	}

	/* The entire mapping fits into the allowed mapping-range of the given data-block.
	 * -> We can just map the memory normally. */
	result = vm_paged_map(effective_vm,
	                      hint,
	                      num_pages,
	                      min_alignment_in_pages,
	                      getfree_mode,
	                      data,
	                      fspath,
	                      fsname,
	                      data_minmappage,
	                      prot,
	                      flag,
	                      guard);
done:
	return result;
}




/* Same as `vm_mapat()', but only allowed pages between `data_subrange_minvpage ... data_subrange_maxvpage'
 * to be mapped from `data'. - Any attempted to map data from outside that range will instead cause
 * memory from `vm_datablock_anonymous_zero' to be mapped.
 * Additionally, `data_start_vpage' is an offset from `data_subrange_minvpage'
 * @param: fspath: Optional mapping path (only used for memory->disk mapping listings)
 * @param: fsname: Optional mapping name (only used for memory->disk mapping listings) */
PUBLIC WUNUSED NONNULL((1, 4)) bool KCALL
vm_paged_mapat_subrange(struct vm *__restrict self,
                        pageid_t page_index, size_t num_pages,
                        struct vm_datablock *__restrict data,
                        struct path *fspath,
                        struct directory_entry *fsname,
                        pageid64_t data_start_vpage,
                        pageid64_t data_subrange_minvpage,
                        pageid64_t data_subrange_maxvpage,
                        uintptr_half_t prot,
                        uintptr_half_t flag,
                        uintptr_t guard)
		THROWS(E_WOULDBLOCK, E_BADALLOC) {
	pageid64_t data_minmappage, data_maxmappage;
	pageid_t maxvpage;
	if unlikely(!num_pages)
		num_pages = 1;
	/* Make sure that the mapping doesn't end up out-of-bounds! */
	if (OVERFLOW_UADD(page_index, num_pages - 1, &maxvpage) ||
	    maxvpage > __ARCH_PAGEID_MAX)
		return false;
	if (OVERFLOW_UADD(data_subrange_minvpage, data_start_vpage, &data_minmappage) ||
		data_minmappage > data_subrange_maxvpage) {
		/* The entire range is out-of-bounds.
		 * Map everything as ANON+ZERO */
		return vm_paged_mapat(self,
		                      page_index,
		                      num_pages,
		                      &vm_datablock_anonymous_zero,
		                      NULL,
		                      NULL,
		                      0,
		                      prot,
		                      flag,
		                      guard);
	}
	if (OVERFLOW_UADD(data_minmappage, num_pages - 1, &data_maxmappage) ||
	    data_maxmappage > data_subrange_maxvpage) {
		size_t num_datavpages, num_zerovpages;
		struct vm_map_subrange_descriptors sr;
		num_datavpages = (size_t)(data_subrange_maxvpage - data_minmappage) + 1;
		num_zerovpages = num_pages - num_datavpages;
		assert(num_datavpages != 0);
		assert(num_zerovpages != 0);
		if (num_datavpages > num_pages)
			num_datavpages = num_pages; /* This can happen due to the presence of a guard. */
		/* Must map as 2 parts:
		 * A total of `num_datavpages' from data+data_minmappage, followed by
		 * a total of `num_zerovpages' from `&vm_datablock_anonymous_zero'.
		 * To prevent race conditions, we must map both of these at the same time! */
		vm_map_subrange_descriptors_init_and_lock_parts_and_vm(&sr,
		                                                       self,
		                                                       data,
		                                                       data_minmappage,
		                                                       num_datavpages,
		                                                       num_zerovpages,
		                                                       prot);
		/* Figure out where the mapping should go. */
		if unlikely(vm_paged_isused(self, page_index, maxvpage)) {
			sync_endwrite(self);
			vm_map_subrange_descriptors_fini_and_unlock_parts(&sr);
			return false;
		}
		/* Insert created mappings into the VM. */
		vm_map_subrange_descriptors_insert_into_vm(&sr,
		                                           self,
		                                           data,
		                                           fspath,
		                                           fsname,
		                                           num_datavpages,
		                                           num_zerovpages,
		                                           page_index,
		                                           prot,
		                                           flag,
		                                           guard);
		sync_endwrite(self);
		vm_map_subrange_descriptors_fini_caller_inherited_parts(&sr);
		return true;
	}

	/* The entire mapping fits into the allowed mapping-range of the given data-block.
	 * -> We can just map the memory normally. */
	return vm_paged_mapat(self,
	                      page_index,
	                      num_pages,
	                      data,
	                      fspath,
	                      fsname,
	                      data_minmappage,
	                      prot,
	                      flag,
	                      guard);
}

DECL_END

#endif /* !GUARD_KERNEL_SRC_MEMORY_VM_VM_MAP_C */
