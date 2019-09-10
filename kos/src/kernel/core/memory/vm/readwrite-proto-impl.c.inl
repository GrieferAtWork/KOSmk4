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
#include "readwrite.c"
//#define COPY_USER2KERNEL 1
//#define COPY_KERNEL2USER 1
#define VM_MEMSET_IMPL 1
#endif

#include <kernel/vio.h>
#include <kernel/printk.h>
#include <hybrid/atomic.h>
#include <sched/pid.h>

#if (defined(COPY_USER2KERNEL) + defined(COPY_KERNEL2USER) + defined(VM_MEMSET_IMPL)) != 1
#error "Must #define COPY_USER2KERNEL or COPY_KERNEL2USER or VM_MEMSET_IMPL before #include-ing this file"
#endif


DECL_BEGIN


#ifdef COPY_USER2KERNEL
#define IS_READING 1
LOCAL void KCALL
copy_kernelspace_from_vm(KERNEL CHECKED void *dst,
                         struct vm *__restrict effective_vm,
                         UNCHECKED void const *src,
                         size_t num_bytes,
                         bool force_accessible)
#define USERSPACE_VM_ADDRESS     src
#else /* COPY_USER2KERNEL */
#define IS_WRITING 1
#ifdef VM_MEMSET_IMPL
LOCAL void KCALL
memset_into_vm(struct vm *__restrict effective_vm,
               UNCHECKED void *dst,
               int byte,
               size_t num_bytes,
               bool force_accessible)
#else /* VM_MEMSET_IMPL */
LOCAL void KCALL
copy_kernelspace_into_vm(struct vm *__restrict effective_vm,
                         UNCHECKED void *dst,
                         KERNEL CHECKED void const *src,
                         size_t num_bytes,
                         bool force_accessible)
#endif /* !VM_MEMSET_IMPL */
#define USERSPACE_VM_ADDRESS     dst
#endif /* !COPY_USER2KERNEL */
		THROWS(E_SEGFAULT, E_WOULDBLOCK)
{
	size_t error;
again:
	/* Try to perform the copy without page faults. */
#if defined(COPY_USER2KERNEL)
	error = copy_kernelspace_from_vm_nopf(dst, effective_vm, src, num_bytes);
#elif defined(COPY_KERNEL2USER)
	error = copy_kernelspace_into_vm_nopf(effective_vm, dst, src, num_bytes);
#elif defined(VM_MEMSET_IMPL)
	error = memset_into_vm_nopf(effective_vm, dst, byte, num_bytes);
#endif
	if (!error)
		return;
	dst = (byte_t *)dst + num_bytes - error;
#ifndef VM_MEMSET_IMPL
	src = (byte_t *)src + num_bytes - error;
#endif /* !VM_MEMSET_IMPL */
	num_bytes = error;
	{
		struct vm_node *node;
		REF struct vm_datapart *part;
#ifdef IS_WRITING
		bool try_merge_part;
#endif /* IS_WRITING */
		vm_vpage_t page;
		size_t vpage_offset; /* Offset (in vpages) of the accessed page from the start of `node' */
		size_t transfer_bytes;
		page = VM_ADDR2PAGE((vm_virt_t)USERSPACE_VM_ADDRESS);
		/* Must manually copy data by explicitly locking the user-space VM and
		 * looking at what kind of VM node is mapped at the target location. */
again_lookup_node:
		sync_read(effective_vm);
#ifdef IS_WRITING
again_lookup_node_already_locked:
		try_merge_part = false;
#endif /* IS_WRITING */
		node = vm_getnodeof(effective_vm, page);
		if unlikely(!node || !node->vn_part) {
			sync_endread(effective_vm);
#ifdef CONFIG_VIO
throw_segfault:
#endif /* CONFIG_VIO */
#ifdef IS_WRITING
			THROW(E_SEGFAULT_UNMAPPED, USERSPACE_VM_ADDRESS,
			      E_SEGFAULT_CONTEXT_FAULT | E_SEGFAULT_CONTEXT_WRITING);
#else /* IS_WRITING */
			THROW(E_SEGFAULT_UNMAPPED, USERSPACE_VM_ADDRESS,
			      E_SEGFAULT_CONTEXT_FAULT);
#endif /* !IS_WRITING */
		}
		if (node->vn_guard) {
			/* TODO: Map a new guard above/below this node! */
		}
		assert(!wasdestroyed(node->vn_part));
		part         = incref(node->vn_part);
		vpage_offset = (size_t)(page - VM_NODE_MIN(node));

		/* Figure out how many bytes to transfer */
		transfer_bytes = VM_NODE_BYTESIZE(node) - vpage_offset;
		if (transfer_bytes > num_bytes)
			transfer_bytes = num_bytes;

		assert(VM_NODE_SIZE(node) == vm_datapart_numvpages(part));
#ifdef CONFIG_VIO
		/* Check for a VIO memory segment */
		if (part->dp_state == VM_DATAPART_STATE_VIOPRT) {
			uintptr_half_t nodeprot;
			struct vio_args args;
			vm_daddr_t vio_addr;

			nodeprot = node->vn_prot;
			COMPILER_READ_BARRIER();
			sync_endread(effective_vm);
			TRY {
				sync_read(part);
			} EXCEPT {
				decref(part);
				RETHROW();
			}
			args.va_block = incref(part->dp_block);
			args.va_access_partoff = ((vm_daddr_t)(vpage_offset +
			                                       vm_datapart_mindpage(part))
			                          << VM_DATABLOCK_ADDRSHIFT(args.va_block));
			/* Figure out the staring VIO address that is being accessed. */
			vio_addr = ((vm_daddr_t)vm_datapart_mindpage(part) << VM_DATABLOCK_ADDRSHIFT(args.va_block)) +
			            (vm_daddr_t)((vm_virt_t)USERSPACE_VM_ADDRESS - VM_NODE_MINADDR(node));

			sync_endread(part);
			args.va_type = args.va_block->db_vio;
			if unlikely(!args.va_type) {
vio_decref_and_throw_segfault:
				decref_unlikely(args.va_block);
				decref_unlikely(part);
				goto throw_segfault;
			}
			args.va_part            = part; /* Inherit reference */
			args.va_access_pageaddr = page;
			args.va_state           = NULL;
			/* Make sure that the segment was mapped with the proper protection */
#ifdef IS_READING
			if unlikely(!force_accessible && !(nodeprot & VM_PROT_READ))
#else /* IS_READING */
			if unlikely(!force_accessible && !(nodeprot & VM_PROT_WRITE))
#endif /* !IS_READING */
			{
				goto vio_decref_and_throw_segfault;
			}
			FINALLY_DECREF_UNLIKELY(args.va_block);
			FINALLY_DECREF_UNLIKELY(part);
#ifdef IS_READING
			vio_copyfromvio(&args, dst, vio_addr, transfer_bytes);
#elif !defined(VM_MEMSET_IMPL)
			vio_copytovio(&args, vio_addr, src, transfer_bytes);
#else /* IS_READING */
			vio_memset(&args, vio_addr, byte, transfer_bytes);
#endif /* !IS_READING */
			goto done_part_transfer;
		}
#endif /* CONFIG_VIO */
		sync_endread(effective_vm);
		TRY {
#ifdef IS_WRITING
			if (node->vn_prot & VM_PROT_SHARED) {
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
					if (vpage_offset != 0) {
						sync_endread(part);
						xdecref(vm_datapart_split(part, vpage_offset));
						decref_unlikely(part);
						goto again_lookup_node;
					}
					if (vm_datapart_numvpages(part) != 1) {
						sync_endread(part);
						xdecref(vm_datapart_split(part, 1));
						decref_unlikely(part);
						goto again_lookup_node;
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
					uintptr_half_t prot;
					vm_ppage_t old_ppage, new_ppage;

					/* Verify that the access being made is valid. */
					if unlikely(!force_accessible && !(node->vn_prot & VM_PROT_WRITE))
						goto endread_and_decref_part_and_set_readonly;

					/* We have to split the part such that we can
					 * manipulate the accessed page individually. */
					if (vpage_offset != 0) {
						sync_endread(part);
						xdecref(vm_datapart_split(part, vpage_offset));
						decref_unlikely(part);
						goto again_lookup_node;
					}
					if (vm_datapart_numvpages(part) != 1) {
						sync_endread(part);
						xdecref(vm_datapart_split(part, 1));
						decref_unlikely(part);
						goto again_lookup_node;
					}
					assert(vpage_offset == 0);
					assert(vm_datapart_numvpages(part) == 1);
					assert(VM_NODE_START(node) == page);
					assert(VM_NODE_SIZE(node) == 1);

					/* Make sure that PAGE#0 of `part' has been initialized!
					 * If it wasn't, we need to initialize it now, since
					 * otherwise we'd be copying uninitialized data below!
					 * Also: If this page isn't marked as initialized, the
					 *       duplicated part won't be set as such, either! */
					{
						unsigned int i, count, state;
						count = VM_DATABLOCK_PAGEALIGN(part->dp_block);
						for (i = 0; i < count; ++i) {
							state = VM_DATAPART_GETSTATE(part, i);
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
							decref_unlikely(part);
							goto again_lookup_node;
						}
					}

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
						sync_read(effective_vm);
						if unlikely(vm_getnodeof(effective_vm, page) != node ||
						            node->vn_part != part ||
						            (node->vn_prot & VM_PROT_SHARED)) {
							decref_unlikely(part);
							kfree(new_part);
							printk(KERN_DEBUG "Race condition: Mapping target at %p has changed during unshare (#1)\n",
							       VM_PAGE2ADDR(page));
							goto again_lookup_node_already_locked;
						}
						sync_endread(effective_vm);
						vm_datapart_lockwrite_setcore(part);
					}
					/* Allocate the physical memory used for backing the vm-local copy. */
					new_ppage = page_malloc(1);
					/* Check if the allocation failed. */
					if unlikely(new_ppage == PAGEPTR_INVALID) {
						sync_endwrite(part);
						kfree(new_part);
						THROW(E_BADALLOC_INSUFFICIENT_PHYSICAL_MEMORY, 1);
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
					new_part->dp_ramdata.rd_blockv          = &new_part->dp_ramdata.rd_block0;
					new_part->dp_ramdata.rd_block0.rb_start = new_ppage;
					new_part->dp_ramdata.rd_block0.rb_size  = 1;
					new_part->dp_futex                      = NULL;
					assert(new_part->dp_state == VM_DATAPART_STATE_INCORE ||
					       new_part->dp_state == VM_DATAPART_STATE_LOCKED);
					if (!sync_trywrite(effective_vm)) {
						sync_endwrite(part);
						page_free(new_ppage, 1);
						kfree(new_part);
						sync_write(effective_vm);
						sync_downgrade(effective_vm);
						decref_unlikely(part);
						goto again_lookup_node_already_locked;
					}
					if unlikely(vm_getnodeof(effective_vm, page) != node ||
					            node->vn_part != part ||
					            (node->vn_prot & VM_PROT_SHARED)) {
						sync_downgrade(effective_vm);
						sync_endwrite(part);
						page_free(new_ppage, 1);
						kfree(new_part);
						decref_unlikely(part);
						printk(KERN_DEBUG "Race condition: Mapping target at %p has changed during unshare (#2)\n",
						       VM_PAGE2ADDR(page));
						goto again_lookup_node_already_locked;
					}
					/* If the node isn't prepared, make sure that we can map memory. */
					if (!(node->vn_flags & VM_NODE_FLAG_PREPARED)) {
						if unlikely(!(effective_vm == THIS_VM || effective_vm == &vm_kernel
						              ? pagedir_prepare_mapone(page)
						              : pagedir_prepare_mapone_p(PAGEDIR_P_SELFOFVM(effective_vm), page))) {
							sync_endwrite(effective_vm);
							sync_endwrite(part);
							page_free(new_ppage, 1);
							kfree(new_part);
							decref_unlikely(part);
							THROW(E_BADALLOC_INSUFFICIENT_PHYSICAL_MEMORY, 1);
						}
					}

					/* Copy the contents of the page being unshared. */
					old_ppage = part->dp_ramdata.rd_blockv[0].rb_start;
					/* TODO: Special function for copying whole pages. */
					vm_copyinphys(VM_PPAGE2ADDR(new_ppage),
					              VM_PPAGE2ADDR(old_ppage),
					              PAGESIZE);

					new_part->dp_block = incref(&vm_datablock_anonymous_zero_vec[VM_DATABLOCK_PAGESHIFT(part->dp_block)]);

					/* Must update the page directory mapping _before_ calling `sync_endwrite(effective_vm)'
					 * Otherwise, `part' may be destroyed while `effective_vm' still contains the mapping
					 * of the already destroyed (and potentially re-purposed) part. */
					prot = node->vn_prot & (PAGEDIR_MAP_FEXEC | PAGEDIR_MAP_FREAD | PAGEDIR_MAP_FWRITE);
					if (effective_vm != &vm_kernel)
						prot |= PAGEDIR_MAP_FUSER;

					/* Since we're changing an existing mapping such that the
					 * previous mapping may get deleted, we must sync this change.
					 * Otherwise, some cached TLB entry may still reference the old
					 * datapart once that part has been destroyed. */
#ifndef CONFIG_NO_SMP
					if unlikely(!vm_sync_begin_nx(effective_vm)) {
						sync_endwrite(effective_vm);
						sync_endwrite(part);
						page_free(new_ppage, 1);
						kfree(new_part);
						/* Block until the task lock becomes available, then try again. */
						vm_tasklock_read(effective_vm);
						vm_tasklock_endread(effective_vm);
						/* decref() is below `vm_tasklock_read(effective_vm)' because we're still
						 * inside of the `TRY { ... } EXCEPT { decref_unlikely(part); }' block */
						decref_unlikely(part);
						goto again_lookup_node_already_locked;
					}
#endif /* !CONFIG_NO_SMP */

					/* Actually map the accessed page! */
					if (effective_vm == THIS_VM || effective_vm == &vm_kernel) {
						pagedir_mapone(page, new_ppage, prot);
					} else {
						pagedir_mapone_p(PAGEDIR_P_SELFOFVM(effective_vm), page,
						                 new_ppage, prot);
					}
					vm_sync_endone(effective_vm, page);

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
					sync_endwrite(effective_vm);

					decref_unlikely(part); /* The reference created by `part = incref(node->vn_part);' above */
					/* Try to merge `part' during the decref() below! */
					try_merge_part = true;

#if 1
					printk(KERN_TRACE "Unshared page at %p (RW) [tid=%u]\n",
					       (uintptr_t)VM_PAGE2ADDR(page), task_getroottid_s());
#else
					printk(KERN_TRACE "Unshared page at %p (RW) [tid=%u,oldpage=" FORMAT_VM_PHYS_T ",newpage=" FORMAT_VM_PHYS_T "]\n",
					       (uintptr_t)VM_PAGE2ADDR(page), task_getroottid_s(),
					       VM_PPAGE2ADDR(old_ppage), VM_PPAGE2ADDR(new_ppage));
#endif
					part = new_part;
					assert(sync_reading(part));
					goto do_transfer_ram;
				}
			}
#else /* IS_WRITING */
			vm_datapart_lockread_setcore(part);
#endif /* !IS_WRITING */
			COMPILER_READ_BARRIER();

			/* Check if the part still includes the accessed page.
			 * This is required to ensure that `vm_datapart_loadpage()'
			 * can be called safely (the part may have been split between
			 * the time of us acquiring a read-lock to it, and the point
			 * when we released our write-lock to the effected VM) */
			if unlikely(vpage_offset >= vm_datapart_numvpages(part)) {
				sync_endread(part);
				decref_unlikely(part);
				goto again_lookup_node;
			}
			/* Load the affected page into the core. */
			assert(part->dp_state != VM_DATAPART_STATE_ABSENT);
			assert(vpage_offset < vm_datapart_numvpages(part));

			/* Make sure the desired user-space access is actually allowed! */
#ifdef IS_WRITING
			if unlikely(!force_accessible && !(node->vn_prot & VM_PROT_WRITE)) {
				/* Read-only memory */
endread_and_decref_part_and_set_readonly:
				sync_endread(part);
				THROW(E_SEGFAULT_READONLY, USERSPACE_VM_ADDRESS, E_SEGFAULT_CONTEXT_WRITING);
			}
#else /* IS_WRITING */
			if unlikely(!force_accessible && !(node->vn_prot & VM_PROT_READ)) {
				/* Write-only memory */
				sync_endread(part);
				THROW(E_SEGFAULT_NOTREADABLE, USERSPACE_VM_ADDRESS, 0);
			}
#endif /* !IS_WRITING */
			{
				bool has_changed;
				vm_ppage_t ppage;
				size_t page_remainder;
				uintptr_t page_offset;
#ifdef IS_WRITING
do_transfer_ram:
#endif /* IS_WRITING */
				page_offset    = (uintptr_t)USERSPACE_VM_ADDRESS & (PAGESIZE - 1);
				page_remainder = PAGESIZE - page_offset;
				/* Make sure not to copy beyond the associated page. */
				if (transfer_bytes > page_remainder)
					transfer_bytes = page_remainder;
#ifdef IS_READING
				has_changed = false;
#else /* IS_READING */
				has_changed = true;
#endif /* !IS_READING */
				TRY {
					ppage = vm_datapart_loadpage(part,
					                             vpage_offset,
					                             &has_changed);
				} EXCEPT {
					sync_endread(part);
					RETHROW();
				}
				/* Actually transfer low-level RAM data. */
#ifdef IS_READING
				vm_copyfromphys(dst,
				                (vm_phys_t)(VM_PPAGE2ADDR(ppage) + page_offset),
				                transfer_bytes);
#elif !defined(VM_MEMSET_IMPL)
				vm_copytophys((vm_phys_t)(VM_PPAGE2ADDR(ppage) + page_offset),
				              src,
				              transfer_bytes);
#else /* IS_READING */
				vm_memsetphys((vm_phys_t)(VM_PPAGE2ADDR(ppage) + page_offset),
				              byte,
				              transfer_bytes);
#endif /* !IS_READING */
				/* Unlock the affected part. */
				sync_endread(part);
			}
		} EXCEPT {
			decref_unlikely(part);
			RETHROW();
		}
#ifdef IS_WRITING
		if (try_merge_part)
			vm_datapart_decref_and_merge(part);
		else
#endif /* IS_WRITING */
		{
			decref_unlikely(part);
		}
#ifdef CONFIG_VIO
done_part_transfer:
#endif /* CONFIG_VIO */
		assert(transfer_bytes <= num_bytes);
		if (transfer_bytes >= num_bytes)
			return;
		num_bytes -= transfer_bytes;
		dst = (byte_t *)dst + transfer_bytes;
#ifndef VM_MEMSET_IMPL
		src = (byte_t *)src + transfer_bytes;
#endif /* !VM_MEMSET_IMPL */
		goto again;
	}
}


#undef USERSPACE_VM_ADDRESS
#undef VM_MEMSET_IMPL
#undef COPY_USER2KERNEL
#undef COPY_KERNEL2USER
#undef IS_READING
#undef IS_WRITING


DECL_END
