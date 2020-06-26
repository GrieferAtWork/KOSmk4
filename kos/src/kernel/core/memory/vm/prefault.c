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
#ifndef GUARD_KERNEL_SRC_MEMORY_VM_PREFAULT_C
#define GUARD_KERNEL_SRC_MEMORY_VM_PREFAULT_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/panic.h>
#include <kernel/vm.h>
#include <kernel/printk.h>
#include <kernel/malloc.h>
#include <kernel/except.h>

#include <hybrid/align.h>
#include <hybrid/atomic.h>
#include <sched/pid.h>

#include <assert.h>

DECL_BEGIN

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL free_partilly_initialized_datapart)(struct vm_datapart *__restrict self) {
	if (self->dp_ramdata.rd_blockv != NULL) {
		size_t i, count;
		count = self->dp_ramdata.rd_blockc;
		if (self->dp_ramdata.rd_blockv == &self->dp_ramdata.rd_block0)
			count = 1;
		for (i = 0; i < count; ++i) {
			page_free(self->dp_ramdata.rd_blockv[i].rb_start,
			          self->dp_ramdata.rd_blockv[i].rb_size);
		}
		if (self->dp_ramdata.rd_blockv != &self->dp_ramdata.rd_block0)
			kfree(self->dp_ramdata.rd_blockv);
	}
	kfree(self);
}


/* Lock and (possibly) unshare some given datapart for the purpose of performing
 * writes to its backing memory in the context of the given vm `self'.
 * This funciton is used by the #PF handler, `vm_write()', `vm_prefault()' and `vm_forcefault()'
 * whenever memory is accessed in a way that it is necessary to perform a write.
 * @param: self:              The VM inside of which `node' is mapped.
 * @param: ppart:             [in|out] A reference to the effective part being accessed (may be modified during unsharing)
 * @param: addr:              The access that is being accessed.
 * @param: node:              A pointer to the node that is being accessed. Note that since no lock is held to
 *                            `self' when this function is called, this pointer may already no longer be valid!
 * @param: node_prot:         The original value of `node->vn_prot'
 * @param: node_vpage_offset: Page-offset into `node' to the first page to which write-access is actually required.
 *                            This must be equal to `PAGEID_ENCODE(addr) - vm_node_getstartpageid(node)'
 * @param: node_vpage_count:  The max number of consecutive pages for which write-access is required. For most
 *                            kinds of memory accesses (including #PF-related ones), this argument is simply `1'
 * @param: pdid_unshare:      When non-NULL, set to `true' if the caller should try to merge `part' during decref(),
 *                            as the result of this function having actually performed an unshare.
 * @return: * : The number of consecutive pages loaded for write-access.
 *              In this case, a read-lock on `part' is passed to the caller.
 *              This is always at most `node_vpage_count'
 * @return: 0 : `node' is no longer valid (must re-attempt its lookup)
 *              In this case, no lock on `part' is passed to the caller. */
PUBLIC size_t KCALL
vm_lock_and_unshare_datapart_for_writing(struct vm *__restrict self,
                                         REF struct vm_datapart **__restrict ppart,
                                         USER void *addr,
                                         WEAK struct vm_node *node,
                                         uintptr_half_t node_prot,
                                         size_t node_vpage_offset,
                                         size_t node_vpage_count,
                                         bool *pdid_unshare) {
	REF struct vm_datapart *part = *ppart;
	size_t part_num_vpages;
	if (node_prot & VM_PROT_SHARED) {
		/* Changes made by the caller should be shared.
		 * -> Simply unshare copy-on-write mappings, and
		 *    ensure that the part is loaded in-core, before
		 *    proceeding to initialize the associated page. */
		if (ATOMIC_READ(part->dp_crefs)) {
			/* If there are copy-on-write mappings, first
			 * minimize the data part to only contain a single
			 * page of physical memory. - That way, we only need
			 * to copy a single page, too, minimizing memory use. */
do_unshare_cow:
			if (node_vpage_offset != 0) {
				sync_endread(part);
				xdecref(vm_datapart_split(part, node_vpage_offset));
				return 0;
			}
			part_num_vpages = vm_datapart_numvpages(part);
			if (part_num_vpages > node_vpage_count) {
				sync_endread(part);
				xdecref(vm_datapart_split(part, node_vpage_count));
				return 0;
			}
			vm_datapart_lockread_setcore_unsharecow(part);
		} else {
			/* No copy-on-write references (lock the part, load it into the core, and check again) */
			vm_datapart_lockread_setcore(part);
			if unlikely(ATOMIC_READ(part->dp_crefs)) {
				sync_endread(part);
				goto do_unshare_cow;
			}
		}
	} else {
		/* Changes made by the caller should be private.
		 * -> Because of this, we must give them their own, private
		 *    copy of the given data part, if that part can somehow
		 *    be reached from the outside. */
		vm_datapart_lockread_setcore(part);
		if (/* The part is anonymous */
		    ATOMIC_READ(part->dp_block->db_parts) == VM_DATABLOCK_ANONPARTS &&
		    /* The part isn't mapped as shared by anyone */
		    part->dp_srefs == NULL &&
		    /* There aren't any other copy-on-write nodes. */
		    part->dp_crefs == node && node->vn_link.ln_next == NULL) {
			/* No need to copy the part. - we're already the only ones actually using it! */
		} else {
			struct vm_datapart *new_part;
			uintptr_half_t pagedir_prot;
			pageid_t addr_pageid;
			PAGEDIR_PAGEALIGNED void *pageaddr;
			size_t missing_part_num_vpages;

			/* We have to split the part such that we can
			 * manipulate the accessed page individually. */
			if (node_vpage_offset != 0) {
				sync_endread(part);
				xdecref(vm_datapart_split(part, node_vpage_offset));
				return 0;
			}
			part_num_vpages = vm_datapart_numvpages(part);
			if (part_num_vpages > node_vpage_count) {
				sync_endread(part);
				xdecref(vm_datapart_split(part, node_vpage_count));
				return 0;
			}
			assert(node_vpage_offset == 0);
			assert(part_num_vpages <= node_vpage_count);
			/*assert(vm_node_getstartpageid(node) == PAGEID_ENCODE(addr));*/
			/*assert(vm_node_getpagecount(node) >= 1 && vm_node_getpagecount(node) <= node_vpage_count);*/

			/* Make sure that PAGE#0 of `part' has been initialized!
			 * If it wasn't, we need to initialize it now, since
			 * otherwise we'd be copying uninitialized data below!
			 * Also: If this page isn't marked as initialized, the
			 *       duplicated part won't be set as such, either! */
			{
				unsigned int i, count, state;
				count = VM_DATABLOCK_PAGEALIGN(part->dp_block);
				for (i = 0; i < count; ++i) {
					state = vm_datapart_getstate(part, i);
					if (VM_DATAPART_PPP_ISINITIALIZED(state))
						continue;
					/* Must initialize the part's first page! */
					TRY {
						bool has_changed = false;
						vm_datapart_loadpage(part, 0, &has_changed);
					} EXCEPT {
						sync_endread(part);
						RETHROW();
					}
					sync_endread(part);
					return 0;
				}
			}
			addr_pageid = PAGEID_ENCODE(addr);
			pageaddr    = (PAGEDIR_PAGEALIGNED void *)((uintptr_t)addr & ~PAGEMASK);

			/* At this point, we need to allocate a new vm_datapart, which we
			 * then have to set up as a mirror copy of the affected part.
			 * HINT: By this point, we can already assume that `part' is INCORE/LOCKED,
			 *       since we used `vm_datapart_lockread_setcore()' to acquire a read
			 *       lock to it above.
			 * HINT: We don't need to allocate a new node, because we can simply re-use
			 *       the old node, as it doesn't even need to change its memory location! */
			new_part = (struct vm_datapart *)kmalloc_nx(sizeof(struct vm_datapart),
			                                            GFP_LOCKED | GFP_ATOMIC | GFP_VCBASE);
			if (!new_part) {
				sync_endread(part);
				new_part = (struct vm_datapart *)kmalloc(sizeof(struct vm_datapart),
				                                         GFP_LOCKED | GFP_VCBASE);
				goto upgrade_and_recheck_vm_for_node;
			} else if (!sync_tryupgrade(part)) {
				sync_endread(part);
upgrade_and_recheck_vm_for_node:
				sync_read(self);
				if unlikely(vm_getnodeofpageid(self, addr_pageid) != node ||
				            node->vn_part != part ||
				            node->vn_prot != node_prot) {
					sync_endread(self);
					kfree(new_part);
					printk(KERN_DEBUG "[vm] Race condition: Mapping target at %p (%p) has changed during unshare (#1)\n",
					       pageaddr, addr);
					return 0;
				}
				sync_endread(self);
				vm_datapart_lockwrite_setcore(part);
				part_num_vpages = vm_datapart_numvpages(part);
				assert(part_num_vpages <= node_vpage_count);
				assert(part_num_vpages != 0);
			}

			/* Initialize the new part. */
			new_part->dp_refcnt = 2; /* +1 (CREF: `node'), +1 (part; assignment below) */
			shared_rwlock_init_read(&new_part->dp_lock);
			new_part->dp_tree.a_vmin = part->dp_tree.a_vmin;
			new_part->dp_tree.a_vmax = part->dp_tree.a_vmax;
			new_part->dp_crefs = node;
			new_part->dp_srefs = NULL;
			new_part->dp_stale = NULL;
			new_part->dp_state = part->dp_state;
			new_part->dp_flags = part->dp_flags & (VM_DATAPART_FLAG_LOCKED | VM_DATAPART_FLAG_CHANGED);
			new_part->dp_pprop = (unlikely(part->dp_flags & VM_DATAPART_FLAG_HEAPPPP))
			                     ? part->dp_pprop_p[0]
			                     : part->dp_pprop;
			new_part->dp_futex = NULL;
			assertf(new_part->dp_state == VM_DATAPART_STATE_INCORE ||
			        new_part->dp_state == VM_DATAPART_STATE_LOCKED,
			        "Ensured by the `vm_datapart_lockread_setcore()' above!");

			/* Allocate the physical memory used for backing the vm-local copy. */
			new_part->dp_ramdata.rd_blockv = NULL;
			missing_part_num_vpages = part_num_vpages;
			for (;;) {
				pageptr_t alloc_start;
				pagecnt_t alloc_count;
				alloc_start = page_malloc_part(1, missing_part_num_vpages, &alloc_count);
				if unlikely(alloc_start == PAGEPTR_INVALID) {
					sync_endwrite(part);
					free_partilly_initialized_datapart(new_part);
					THROW(E_BADALLOC_INSUFFICIENT_PHYSICAL_MEMORY,
					      part_num_vpages * PAGESIZE);
				}
				assert(alloc_count != 0);
				assert(alloc_count <= missing_part_num_vpages);
				if (new_part->dp_ramdata.rd_blockv == NULL) {
					/* First pass */
					new_part->dp_ramdata.rd_blockv          = &new_part->dp_ramdata.rd_block0;
					new_part->dp_ramdata.rd_block0.rb_start = alloc_start;
					new_part->dp_ramdata.rd_block0.rb_size  = alloc_count;
				} else {
					struct vm_ramblock *newvec;
					struct vm_ramblock *oldvec;
					size_t avail_size, needed_size;
					oldvec = newvec = new_part->dp_ramdata.rd_blockv;
					if (oldvec == &new_part->dp_ramdata.rd_block0)
						oldvec = NULL; /* Second pass */
					needed_size = (new_part->dp_ramdata.rd_blockc + 1);
					avail_size  = kmalloc_usable_size(oldvec) / sizeof(struct vm_ramblock);
					if (needed_size > avail_size) {
						/* Must allocate more memory. */
						newvec = (struct vm_ramblock *)krealloc_nx(oldvec,
						                                           needed_size * sizeof(struct vm_ramblock),
						                                           GFP_LOCKED | GFP_ATOMIC | GFP_VCBASE);
						if unlikely(!newvec) {
							/* Must allocate more heap memory without holding a lock to `part' */
							size_t new_part_num_vpages;
							sync_endwrite(part);
							vm_datapart_lockwrite_setcore(part);
							new_part_num_vpages = vm_datapart_numvpages(part);
							assert(new_part_num_vpages <= part_num_vpages);
							if (new_part_num_vpages < part_num_vpages) {
								/* The part grew smaller. - We may already have what we need! */
								size_t done_part_num_vpages;
								done_part_num_vpages = part_num_vpages - missing_part_num_vpages;
								if (done_part_num_vpages >= new_part_num_vpages) {

								}
								part_num_vpages = new_part_num_vpages;
								missing_part_num_vpages = part_num_vpages - done_part_num_vpages;
							}
						}
					}
					new_part->dp_ramdata.rd_blockv = newvec;
					newvec += new_part->dp_ramdata.rd_blockc++;
					newvec->rb_start = alloc_start;
					newvec->rb_size  = alloc_count;
				}
				if (missing_part_num_vpages >= alloc_count)
					break;
				missing_part_num_vpages -= alloc_count;
			}
			assert(part_num_vpages != 0);
			if (!sync_trywrite(self)) {
				sync_endwrite(part);
				free_partilly_initialized_datapart(new_part);
				sync_write(self);
				sync_endwrite(self);
				return 0;
			}
			if unlikely(vm_getnodeofpageid(self, addr_pageid) != node ||
			            node->vn_part != part ||
			            node->vn_prot != node_prot) {
				sync_endwrite(self);
				sync_endwrite(part);
				free_partilly_initialized_datapart(new_part);
				printk(KERN_DEBUG "[vm] Race condition: Mapping target at %p (%p) has changed during unshare (#2)\n",
				       pageaddr, addr);
				return 0;
			}
			/* If the node isn't prepared, make sure that we can map memory. */
			if (!(node->vn_flags & VM_NODE_FLAG_PREPARED)) {
				if unlikely(!(self == THIS_VM || self == &vm_kernel
				              ? pagedir_prepare_map(pageaddr, part_num_vpages * PAGESIZE)
				              : pagedir_prepare_map_p(PAGEDIR_P_SELFOFVM(self), pageaddr, part_num_vpages * PAGESIZE))) {
					sync_endwrite(self);
					sync_endwrite(part);
					free_partilly_initialized_datapart(new_part);
					THROW(E_BADALLOC_INSUFFICIENT_PHYSICAL_MEMORY, PAGESIZE);
				}
			}

			/* Fill in the datablock of the new datapart as being derived
			 * from the appropriate anonymous-zero set of datablocks. */
			new_part->dp_block = incref(&vm_datablock_anonymous_zero_vec[VM_DATABLOCK_PAGESHIFT(part->dp_block)]);

			/* Copy the contents of the page being unshared. */
			assert(vm_datapart_numvpages(new_part) == part_num_vpages);
			vm_datapart_do_copyram(new_part, part);

			/* Must update the page directory mapping _before_ calling `sync_endwrite(self)'
			 * Otherwise, `part' may be destroyed while `self' still contains the mapping
			 * of the already destroyed (and potentially re-purposed) part. */
			pagedir_prot = node_prot & (PAGEDIR_MAP_FEXEC | PAGEDIR_MAP_FREAD | PAGEDIR_MAP_FWRITE);
			if (self != &vm_kernel)
				pagedir_prot |= PAGEDIR_MAP_FUSER;

			/* Since we're changing an existing mapping such that the
			 * previous mapping may get deleted, we must sync this change.
			 * Otherwise, some cached TLB entry may still reference the old
			 * datapart once that part has been destroyed. */
#ifndef CONFIG_NO_SMP
			if unlikely(!vm_sync_begin_nx(self)) {
				sync_endwrite(self);
				sync_endwrite(part);
				free_partilly_initialized_datapart(new_part);
				/* Block until the task lock becomes available, then try again. */
				vm_tasklock_read(self);
				vm_tasklock_endread(self);
				return 0;
			}
#endif /* !CONFIG_NO_SMP */

			/* Actually map the accessed page! */
			if (self == THIS_VM || self == &vm_kernel) {
				vm_datapart_map_ram(new_part, pageaddr, pagedir_prot);
			} else {
				vm_datapart_map_ram_p(new_part,
				                      PAGEDIR_P_SELFOFVM(self),
				                      pageaddr, pagedir_prot);
			}
			vm_paged_sync_end(self, addr_pageid, part_num_vpages);

			/* Unlink the given node from the old part's chain. */
			LLIST_REMOVE(node, vn_link);
			sync_endwrite(part);

			/* Re-link the node to be apart of our part copy. */
			assert(sync_reading(new_part));
			node->vn_link.ln_pself = &new_part->dp_crefs;
			node->vn_link.ln_next  = NULL;
			assert(node->vn_part == part);
			decref_nokill(part);      /* node->vn_part */
			node->vn_part = new_part; /* Inherit reference */
			assert(ATOMIC_READ(new_part->dp_block->db_parts) == VM_DATABLOCK_ANONPARTS);
			assert(new_part->dp_srefs == NULL);
			assert(new_part->dp_crefs == node);
			assert(node->vn_link.ln_pself == &new_part->dp_crefs);
			assert(node->vn_link.ln_next == NULL);
			sync_endwrite(self);

			/* Try to merge `part' during the decref() below! */
			if (pdid_unshare)
				*pdid_unshare = true;

			printk(KERN_TRACE "[vm] Unshared page at %p (%p) (RW) [tid=%u]\n",
			       pageaddr, addr, task_getroottid_s());
			*ppart = new_part;
			decref_unlikely(part);
			assert(sync_reading(new_part));
			goto done;
		}
	}

	/* Check if the part still includes the accessed page.
	 * This is required to ensure that `vm_datapart_loadpage()'
	 * can be called safely (the part may have been split between
	 * the time of us acquiring a read-lock to it, and the point
	 * when we released our write-lock to the effected VM) */
	part_num_vpages = vm_datapart_numvpages(part);
	assert(part_num_vpages != 0);
	if unlikely(node_vpage_offset >= part_num_vpages) {
		sync_endread(part);
		return 0;
	}
	/* Load the affected page into the core. */
	assert(part->dp_state != VM_DATAPART_STATE_ABSENT);
	assert(node_vpage_offset < part_num_vpages);
	assert(sync_reading(part));
done:
	return part_num_vpages;
}




/* Try to prefault memory for the given address range within the current VM.
 * This function is intended to be used in conjunction with `memcpy_nopf()',
 * as well as functions using it in order to speed up the lock-copy-unlock-do_buffered_io-repeat
 * cycle by potentially allowing the caller to skip having to perform buffered I/O
 * in cases where the backing memory can be made to be backed by real, physical memory,
 * as opposed to not being mapped at all, or being mapped by VIO memory.
 * NOTE: This function should only be used as a hint for figuring out how buffered I/O should
 *       be performed in face of a memory range that cannot be accessed by `memcpy_nopf()'.
 *       In practice, this means that code using it should be aware that as far as the reliable
 *       semantics of this function go, one valid implementation could simply look like this:
 *       >> PUBLIC size_t FCALL
 *       >> vm_prefault(USER CHECKED void const *addr, size_t num_bytes, bool for_writing)
 *       >>         THROWS(E_WOULDBLOCK, E_BADALLOC) {
 *       >>     assert(num_bytes != 0);
 *       >>     (void)addr;
 *       >>     (void)num_bytes;
 *       >>     (void)for_writing;
 *       >>     // Always return 1, indicating a the necessity of performing just a bit of
 *       >>     // buffered I/O, which will automatically fault at least some memory on access,
 *       >>     // as well as handle the case of VIO memory being accessed.
 *       >>     return 1;
 *       >> }
 * NOTE: For a valid usage example of this function, you may look at the implementation of
 *       the `vm_datapart_(read|write)()' function pair, which uses it in order to determine
 *       the number of bytes that must be processed using `vm_datapart_(read|write)_buffered()'
 * @param: for_writing: When true, make sure that memory within the associated gets
 *                      faulted such that copy-on-write operations are carried out.
 *                      Otherwise, only make sure that memory from the given range
 *                      can be read from (though again: even this is only to be taken
 *                      as a hint. - This function is allowed to just do nothing if
 *                      it wants to)
 * @assume(num_bytes != 0);
 * @return: 0 :
 *     At least 1 page of memory (the one containing `addr') was faulted.
 *     In this case, the caller can immediately go back to performing direct I/O,
 *     though the possibility exists that either due to the backing physical memory
 *     for the given address range being swapped out, or this function choosing not
 *     to prefault the given range in its entirety, more transfer errors may still
 *     occur as memory from the given range is accessed using `memcpy_nopf()'.
 *     Another possible reason for more transfer errors could be a VIO, or unmapped
 *     segment of memory starting further into the given range.
 * @return: >= 1 && <= num_bytes:
 *     In this case, the return value indicates the number of bytes that could not
 *     be faulted (either because not being mapped, or due to being mapped to VIO) */
PUBLIC size_t FCALL
vm_prefault(USER CHECKED void const *addr,
            size_t num_bytes, bool for_writing)
		THROWS(E_WOULDBLOCK, E_BADALLOC) {
	assert(num_bytes != 0);
	/* This function shares some of its code with `vm_read()' / `vm_write()', except that
	 * the contents of memory don't actually get modified.
	 * In practice, try to prefault the entirety of the indicated address range, but stop
	 * at the first gap within the VM where either no mapping exists for some part of the
	 * indicated range, or the part that does exist is a VIO mapping.
	 * If the indicated range starts with...
	 *     ... an unmapped memory segment (i.e. no `vm_node' exists for `addr'), then
	 *         immediately return some non-zero value < num_bytes. (for simplicitly, we
	 *         we can just always return `1', thus forgoing the need of additional
	 *         calculations needing to be done)
	 *     ... a memory segment that is backed by VIO, then return the number of bytes
	 *         within a span starting at `addr', and ending at either the end of the
	 *         indicate ranged, or at the first byte that is either not mapped any more,
	 *         or is no longer part of a memory block backed by VIO, whichever comes first:
	 *      >> return (MIN(addr + num_bytes, END_ADDRESS_OF_LAST_CONSECUTIVE_VIO_MAPPING_STARTING_AT(addr)) - addr);
	 *         Additionally, when `END_ADDRESS_OF_LAST_CONSECUTIVE_VIO_MAPPING_STARTING_AT(addr) > addr + num_bytes',
	 *         recursively call ourself:
	 *         >> void *p = END_ADDRESS_OF_LAST_CONSECUTIVE_VIO_MAPPING_STARTING_AT(addr);
	 *         >> if (p > addr + num_bytes) {
	 *         >>     TRY {
	 *         >>         vm_prefault(p, p - (addr + num_bytes));
	 *         >>     } EXCEPT {
	 *         >>         if (!was_thrown(E_BADALLOC) &&
	 *         >>             !was_thrown(E_WOULDBLOCK))
	 *         >>             RETHROW();
	 *         >>     }
	 *         >> }
	 *         >> return (MIN(addr + num_bytes, p) - addr);;
	 *         Thus allowing the caller to write code that immediately accesses memory
	 *         past a block of data for which buffered I/O is necessary using direct I/O,
	 *         without having to consult `vm_prefault()' yet again.
	 * Otherwise, slowly work through all consecutively mapped `vm_node's, starting with
	 * the node used for backing `addr' itself, and look at each of their data parts.
	 *   - If `addr + num_bytes' is reached, then stop iteration
	 *   - If at any point a gap between two consecutive is found, also stop
	 *   - Otherwise, with respect to `for_writing', as well as `VM_PROT_SHARED',
	 *     and also `VM_PROT_WRITE' when `for_writing' is `true', make use of
	 *     `vm_datapart_lockread_setcore_unsharecow()' and `vm_datapart_lockread_setcore()'
	 *     in order to lock mapped data parts, before potentially updating memory mappings
	 *     within the VM associated with the current address, and finally updating the backing
	 *     page directory mapping. Note that this last part is _mandatory_, since the only
	 *     real requirement for `vm_prefault()' in terms of semantics is:
	 *         When `vm_prefault()' returns `0', it is guarantied that at some point in
	 *         the past, presence, or future, virtual memory located at `addr' has/is/or
	 *         will be backed by true, physical memory.
	 *   - If at least a single byte of memory was already successfully faulted using this
	 *     memory, any `E_BADALLOC' or `E_WOULDBLOCK' exceptions thrown whilst attempting
	 *     to fault additional memory are caught, and will also cause the iteration to stop.
	 *     In practice this simply means:
	 *     >> if (ITER_ADDR == addr)
	 *     >>     RETHROW();
	 *     >> else {
	 *     >>     break;
	 *     >> }
	 *     Where ITER_ADDR is initialized to `addr', and during `continue' is updated to
	 *     instead refer to `vm_node_getend(CURRENT_NODE)'.
	 * Regardless of why iteration stops, always return `0' at this point, indicating that
	 * at least some part of the given range can be accessed using direct I/O.
	 */

	/* TODO: Implement me! :) */
	(void)addr;
	(void)num_bytes;
	(void)for_writing;

	return 1;
}



/* Force all bytes within the given address range to be faulted for either reading
 * or writing. If any page within the specified range isn't mapped, throw an E_SEGFAULT
 * exception. Otherwise, ensure that copy-on-write is invoked when `VM_FORCEFAULT_FLAG_WRITE'
 * is set, and that irregardless of `VM_FORCEFAULT_FLAG_WRITE', physical memory is allocated
 * for any mapping that can be made to be backed by RAM.
 * Any VIO mappings within the specified range are simply ignored (and will not count
 * towards the returned value), unless `VM_FORCEFAULT_FLAG_NOVIO' is set
 * @return: * : The total number of bytes that become faulted as the result of this
 *              function being called. Note that even if you may be expecting that some
 *              specified address within the range wasn't faulted before, you must still
 *              allow for this function to return `0', since there always exists a
 *              possibility of some other thread changing the backing mappings, or
 *              faulting the mappings themself.
 *              As such, the return value should only be used for probability optimizations,
 *              as well as profiling, but not for the purpose of actual logic decisions.
 * NOTE: This function will also update the page directory mappings for any dataparts
 *       that get faulted during its invocation, meaning that use of `memcpy_nopf()'
 *       within the indicated address range (whilst still checking it for errors for
 *       the even of the mapping changing, or the mapping being a VIO mapping) becomes
 *       possible immediately, without having to force any soft of additional memory
 *       access (note though that this only applies to the page directory of `self',
 *       though also note that if some datapart within the range was already faulted, its
 *       page directory mapping in `self' will still be updated). */
FUNDEF size_t FCALL
vm_paged_forcefault(struct vm *__restrict self,
                    pageid_t minpageid,
                    pageid_t maxpageid,
                    unsigned int flags)
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT) {
	assert(minpageid <= maxpageid);
	(void)self;
	(void)minpageid;
	(void)maxpageid;
	(void)flags;

	COMPILER_IMPURE();
	kernel_panic("TODO");

	return 0;
}



DECL_END

#endif /* !GUARD_KERNEL_SRC_MEMORY_VM_PREFAULT_C */
