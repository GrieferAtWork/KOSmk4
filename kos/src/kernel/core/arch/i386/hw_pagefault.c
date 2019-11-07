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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_HW_PAGEFAULT_C
#define GUARD_KERNEL_CORE_ARCH_I386_HW_PAGEFAULT_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/debugtrap.h>
#include <kernel/except.h>
#include <kernel/malloc.h>
#include <kernel/memory.h>
#include <kernel/paging.h>
#include <kernel/printk.h>
#include <kernel/vio.h>
#include <kernel/vm.h>
#include <kernel/vm/phys.h>
#include <sched/pid.h>

#include <hybrid/atomic.h>

#include <asm/cpu-flags.h>
#include <asm/intrin.h>
#include <kos/kernel/cpu-state-helpers.h>

#include <assert.h>
#include <signal.h>
#include <string.h>

#include <libinstrlen/instrlen.h>

#include "except.h"
#include "vio.h"

DECL_BEGIN

#define PAGEFAULT_F_PRESENT     0x0001 /* FLAG: The accessed page is present (Check for LOA) */
#define PAGEFAULT_F_WRITING     0x0002 /* FLAG: The fault happened as a result of a memory write (Check for COW) */
#define PAGEFAULT_F_USERSPACE   0x0004 /* FLAG: The fault occurred while in user-space */
#define PAGEFAULT_F_RESBIT      0x0008 /* FLAG: A reserved page bit is set */
#define PAGEFAULT_F_INSTRFETCH  0x0010 /* FLAG: The fault happened while fetching instructions.
                                        * NOTE: This flag isn't guarantied to be set, though an
                                        *       instruction-fetch fault can also easily be detected
                                        *       by comparing `%eip' with `%cr2' */


STATIC_ASSERT(PAGEDIR_MAP_FEXEC == VM_PROT_EXEC);
STATIC_ASSERT(PAGEDIR_MAP_FWRITE == VM_PROT_WRITE);
STATIC_ASSERT(PAGEDIR_MAP_FREAD == VM_PROT_READ);


DATDEF byte_t x86_memcpy_nopf_rep_pointer[];
DATDEF byte_t x86_memcpy_nopf_ret_pointer[];



#ifdef __x86_64__
#define ir_pip ir_rip
#else /* __x86_64__ */
#define ir_pip ir_eip
#endif /* !__x86_64__ */

INTERN struct icpustate *FCALL
x86_cirq_0e(struct icpustate *__restrict state, uintptr_t ecode) {
#if 1
#define IS_USER() (ecode & PAGEFAULT_F_USERSPACE)
#else
#define IS_USER() irregs_isuser(&state->ics_irregs_k)
#endif
	vm_virt_t addr;
	uintptr_t pc;
	vm_vpage_t page;
	struct vm *effective_vm;
	struct vm_node *node;
	uintptr_half_t prot;
	vm_ppage_t ppage;
	bool has_changed;
	/* Check for memcpy_nopf() */
	pc = state->ics_irregs.ir_pip;
	if unlikely_untraced(pc == (uintptr_t)x86_memcpy_nopf_rep_pointer) {
		state->ics_irregs.ir_pip = (uintptr_t)x86_memcpy_nopf_ret_pointer;
		return state;
	}
	addr = (vm_virt_t)__rdcr2();
	/* Re-enable interrupts if they were enabled before. */
#ifdef __x86_64__
	if (state->ics_irregs.ir_rflags & EFLAGS_IF)
		__sti();
#else /* __x86_64__ */
	if (state->ics_irregs_k.ir_eflags & EFLAGS_IF)
		__sti();
#endif /* !__x86_64__ */
	page = VM_ADDR2PAGE(addr);
#if 0
	printk(KERN_DEBUG "Page fault at %p (page %p) [pc=%p,sp=%p] [ecode=%#x] [pid=%u]\n",
	       (uintptr_t)addr, (uintptr_t)VM_PAGE2ADDR(page),
	       pc, icpustate_getsp(*state), ecode,
	       (unsigned int)task_getroottid_s());
#endif
	if ((ecode & (PAGEFAULT_F_PRESENT | PAGEFAULT_F_USERSPACE)) == 0 &&
	    page >= (vm_vpage_t)KERNEL_BASE_PAGE &&
	    /* Check if a hint was defined for this page. */
	    (node = (struct vm_node *)pagedir_gethint(page)) != NULL) {
		/* This is a hinted node (perform assertions on all
		 * of the requirements documented for such a node) */
		assert(node->vn_flags & VM_NODE_FLAG_HINTED);
		assert(node->vn_prot & VM_PROT_SHARED);
		assert(node->vn_flags & VM_NODE_FLAG_PREPARED);
		assert(!(node->vn_flags & VM_NODE_FLAG_PARTITIONED));
		assert(node->vn_vm == &vm_kernel);
		assert(node->vn_part != NULL);
		assert(node->vn_block != NULL);
		assert(node->vn_guard == 0);
		assert(node->vn_part->dp_srefs == node);
		assert(node->vn_link.ln_pself == &node->vn_part->dp_srefs);
		assert(node->vn_link.ln_next == NULL);
		assert(node->vn_part->dp_crefs == NULL);
		assert(!isshared(node->vn_part));
		assert(node->vn_part->dp_block == node->vn_block);
		assert(node->vn_block->db_parts == VM_DATABLOCK_ANONPARTS);
		assert(node->vn_part->dp_flags & VM_DATAPART_FLAG_LOCKED);
		assert(node->vn_part->dp_state == VM_DATAPART_STATE_LOCKED);
		has_changed = ecode & PAGEFAULT_F_WRITING;
		/* Load the affected page into the core. */
		ppage = vm_datapart_loadpage(node->vn_part,
		                             (size_t)(page - VM_NODE_MIN(node)),
		                             &has_changed);
		/* Map the affected page, overriding the mapping hint that originally got us here. */
		prot = node->vn_prot & (PAGEDIR_MAP_FEXEC | PAGEDIR_MAP_FREAD | PAGEDIR_MAP_FWRITE);
		/* Unset so we're able to track changes.
		 * NOTE: The actual tracking of changes isn't something that can be done atomically,
		 *       however atomic kernel pages do not impose any restrictions on use of change
		 *       tracking. */
		if ((node->vn_part->dp_flags & VM_DATAPART_FLAG_TRKCHNG) && !has_changed)
			prot &= ~PAGEDIR_MAP_FWRITE;
		pagedir_mapone(page, ppage, prot);
		goto done;
	}
	effective_vm = &vm_kernel;
	if (page < (vm_vpage_t)KERNEL_BASE_PAGE || IS_USER())
		effective_vm = THIS_VM;
	{
		struct task_connections con;
		size_t vpage_offset; /* Offset (in vpages) of the accessed page from the start of `node' */
		task_pushconnections(&con);
		TRY {
			struct vm_datapart *part;
again_lookup_node:
			sync_read(effective_vm);
again_lookup_node_already_locked:
			assert(sync_reading(effective_vm));
			assert(!sync_writing(effective_vm));
			/* Lookup the node associated with the given page. */
			node = vm_getnodeof(effective_vm,
			                    page);
			if unlikely(!node || !node->vn_part) {
				sync_endread(effective_vm);
				goto pop_connections_and_throw_segfault;
			}
			if (node->vn_guard) {
				/* TODO: Map a new guard above/below this node! */
			}
			assert(!wasdestroyed(node->vn_part));
			part         = incref(node->vn_part);
			vpage_offset = (size_t)(page - VM_NODE_MIN(node));
			assert(VM_NODE_SIZE(node) == vm_datapart_numvpages(part));
			has_changed = ecode & PAGEFAULT_F_WRITING;
			/* Acquire a lock to the affected data part. */
			TRY {
				/* Need at least a read-lock for part initialization */
#ifdef CONFIG_VIO
				if (part->dp_state == VM_DATAPART_STATE_VIOPRT) {
					vio_main_args_t args;
					uintptr_half_t nodeprot;
					nodeprot = node->vn_prot;
					COMPILER_READ_BARRIER();
					sync_endread(effective_vm);
					/* VIO Emulation */
					sync_read(part);
					args.ma_args.va_block = incref(part->dp_block);
					args.ma_args.va_access_partoff = ((vm_daddr_t)(vpage_offset +
					                                               vm_datapart_mindpage(part))
					                                  << VM_DATABLOCK_ADDRSHIFT(args.ma_args.va_block));
					sync_endread(part);
					args.ma_args.va_type = args.ma_args.va_block->db_vio;
					if unlikely(!args.ma_args.va_type) {
						decref_unlikely(args.ma_args.va_block);
						decref_unlikely(part);
						goto pop_connections_and_throw_segfault;
					}
					args.ma_args.va_part            = part; /* Inherit reference */
					args.ma_args.va_access_pageaddr = page;
					args.ma_args.va_state           = state;
					args.ma_oldcons                 = &con; /* Inherit */
					/* Check for special case: call into VIO memory */
					if (args.ma_args.va_type->dtv_call &&
					    (uintptr_t)addr == irregs_rdip(&state->ics_irregs)) {
						/* Make sure that memory mapping has execute permissions! */
						if unlikely(!(nodeprot & VM_PROT_EXEC)) {
							goto vio_failure_throw_segfault;
						}
						/* Special case: call into VIO memory */
						TRY {
							vm_daddr_t vio_addr;
							uintptr_t callsite_eip;
							uintptr_t sp;
							/* Must unwind the stack to restore the IP of the VIO call-site. */
							sp = irregs_rdsp(&state->ics_irregs);
							if (IS_USER() && sp >= KERNEL_BASE)
								goto do_normal_vio; /* Validate the stack-pointer for user-space. */
							TRY {
								callsite_eip = *(uintptr_t *)sp;
							} EXCEPT {
								if (!was_thrown(E_SEGFAULT))
									RETHROW();
								goto do_normal_vio;
							}
							/* Unwind the stack, and remember the call-site instruction pointer. */
#ifdef __x86_64__
							if (IS_USER() != (callsite_eip < KERNEL_BASE))
								goto do_normal_vio;
							irregs_wrip(&state->ics_irregs, callsite_eip);
							irregs_wrsp(&state->ics_irregs, sp + 8);
#else /* __x86_64__ */
							if (sp != (uintptr_t)(&state->ics_irregs_k + 1) ||
							    IS_USER()) {
								if (callsite_eip >= KERNEL_BASE)
									goto do_normal_vio;
								irregs_wrip(&state->ics_irregs_k, callsite_eip);
								state->ics_irregs_u.ir_esp += 4;
							} else {
								if (callsite_eip < KERNEL_BASE)
									goto do_normal_vio;
								state->ics_irregs_k.ir_eip = callsite_eip;
								state = (struct icpustate *)memmove((byte_t *)state + sizeof(void *), state,
								                                    OFFSET_ICPUSTATE_IRREGS +
								                                    SIZEOF_IRREGS_KERNEL);
							}
#endif /* !__x86_64__ */
							/* Figure out the exact VIO address that got called. */
							vio_addr = (vm_daddr_t)addr;
							vio_addr -= (vm_daddr_t)args.ma_args.va_access_pageaddr * PAGESIZE;
							vio_addr += (vm_daddr_t)args.ma_args.va_access_partoff;
							/* Invoke the VIO call operator. */
							state = (*args.ma_args.va_type->dtv_call)(&args.ma_args,
							                                          state,
							                                          vio_addr);
						} EXCEPT {
							assert(args.ma_oldcons == &con);
							assert(args.ma_args.va_part == part);
							decref_unlikely(args.ma_args.va_block);
							/*decref_unlikely(args.ma_args.va_part);*/
							/*task_popconnections(args.ma_oldcons);*/
							RETHROW(); /* Except blocks below will already cleanup `part' and `&con' */
						}
						assert(args.ma_oldcons == &con);
						assert(args.ma_args.va_part == part);
						decref_unlikely(args.ma_args.va_block);
						decref_unlikely(args.ma_args.va_part);
						task_popconnections(args.ma_oldcons);
						return state;
					}
do_normal_vio:
					/* Make sure that the segment was mapped with the proper protection */
					if unlikely((ecode & PAGEFAULT_F_WRITING)
						         ? !(nodeprot & VM_PROT_WRITE) /* Write to read-only VIO segment */
						         : !(nodeprot & VM_PROT_READ)  /* Read from non-readable VIO segment */
						         ) {
vio_failure_throw_segfault:
						assert(args.ma_oldcons == &con);
						assert(args.ma_args.va_part == part);
						decref_unlikely(args.ma_args.va_block);
						decref_unlikely(args.ma_args.va_part);
						goto pop_connections_and_throw_segfault;
					}
					return x86_vio_main(&args,
					                    (uintptr_t)addr,
					                    ecode);
				}
#endif /* CONFIG_VIO */
				sync_endread(effective_vm);

				if (has_changed) {
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
							vm_ppage_t old_ppage, new_ppage;
							/* Verify that the access being made is valid. */
							if unlikely(!(node->vn_prot & VM_PROT_WRITE))
								goto endread_and_decref_part_and_set_readonly;
							if (!(node->vn_prot & VM_PROT_EXEC)) {
								if unlikely((ecode & PAGEFAULT_F_INSTRFETCH) || (uintptr_t)addr == pc)
									goto endread_and_decref_part_and_set_noexec;
							}

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
										has_changed = false;
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
							shared_rwlock_init(&new_part->dp_lock);
							new_part->dp_tree.a_vmin = part->dp_tree.a_vmin;
							new_part->dp_tree.a_vmax = part->dp_tree.a_vmax;
							new_part->dp_crefs = node;
							new_part->dp_srefs = NULL;
							new_part->dp_stale = NULL;
							new_part->dp_state = part->dp_state;
							new_part->dp_flags = part->dp_flags & (VM_DATAPART_FLAG_LOCKED | VM_DATAPART_FLAG_CHANGED);
							new_part->dp_pprop = unlikely(part->dp_flags & VM_DATAPART_FLAG_HEAPPPP)
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
								if unlikely(!pagedir_prepare_mapone(page)) {
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
							pagedir_mapone(page, new_ppage, prot);
							vm_sync_endone(effective_vm, page);

							/* Unlink the given node from the old part's chain. */
							LLIST_REMOVE(node, vn_link);
							sync_endwrite(part);

							/* Re-link the node to be apart of our part copy. */
							assert(!sync_reading(new_part));
							assert(!sync_writing(new_part));
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
							vm_datapart_decref_and_merge(new_part);

#if 1
							printk(KERN_TRACE "Unshared page at %p [tid=%u]\n",
							       (uintptr_t)VM_PAGE2ADDR(page), task_getroottid_s());
#else
							printk(KERN_TRACE "Unshared page at %p [tid=%u,oldpage=" FORMAT_VM_PHYS_T ",newpage=" FORMAT_VM_PHYS_T "]\n",
							       (uintptr_t)VM_PAGE2ADDR(page), task_getroottid_s(),
							       VM_PPAGE2ADDR(old_ppage), VM_PPAGE2ADDR(new_ppage));
#endif
							goto done_before_pop_connections;
						}
					}
				} else {
					vm_datapart_lockread_setcore(part);
				}
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
				if unlikely(!(node->vn_prot & VM_PROT_WRITE) &&
				            (ecode & PAGEFAULT_F_WRITING)) {
					/* Read-only memory */
endread_and_decref_part_and_set_readonly:
					sync_endread(part);
					decref_unlikely(part);
					PERTASK_SET(_this_exception_info.ei_code,
					            ERROR_CODEOF(E_SEGFAULT_READONLY));
					goto pop_connections_and_set_exception_pointers;
				}
				if unlikely(!(node->vn_prot & VM_PROT_READ) &&
				            !(ecode & PAGEFAULT_F_WRITING)) {
					/* Write-only memory */
					PERTASK_SET(_this_exception_info.ei_code,
					            ERROR_CODEOF(E_SEGFAULT_NOTREADABLE));
					sync_endread(part);
					decref_unlikely(part);
					goto pop_connections_and_set_exception_pointers;
				}
				if (!(node->vn_prot & VM_PROT_EXEC)) {
					if unlikely((ecode & PAGEFAULT_F_INSTRFETCH) || (uintptr_t)addr == pc) {
						/* Non-executable memory */
endread_and_decref_part_and_set_noexec:
						sync_endread(part);
						decref_unlikely(part);
						PERTASK_SET(_this_exception_info.ei_code,
						            ERROR_CODEOF(E_SEGFAULT_NOTEXECUTABLE));
						goto pop_connections_and_set_exception_pointers;
					}
				}
				TRY {
					ppage = vm_datapart_loadpage(part,
					                             vpage_offset,
					                             &has_changed);
				} EXCEPT {
					sync_endread(part);
					RETHROW();
				}

				/* Re-acquire a lock to the VM, so we can map the affected page. */
				if (!sync_trywrite(effective_vm)) {
					sync_endread(part);
					sync_write(effective_vm);
					sync_downgrade(effective_vm);
					decref_unlikely(part);
					goto again_lookup_node_already_locked;
				}

				/* Check to ensure that the mapped target hasn't changed
				 * while we were loading the affected page into the core. */
				if unlikely(vm_getnodeof(effective_vm, page) != node ||
				            node->vn_part != part) {
					sync_endread(part);
					decref_unlikely(part);
					sync_downgrade(effective_vm);
					printk(KERN_DEBUG "Race condition: Mapping target at %p has changed\n",
					       VM_PAGE2ADDR(page));
					goto again_lookup_node_already_locked;
				}

				/* Check one more time if we must unshare the node when writing.
				 * This may still trigger after a fork() that happened in another
				 * thread within the same VM, which copied the VM before we got here,
				 * but did so after we checked this above (aka.: during the time
				 * when we had to release our VM lock to initialize the associated
				 * data part page) */
				if ((ecode & PAGEFAULT_F_WRITING) &&
				    !(node->vn_prot & VM_PROT_SHARED) &&
				    !(/* The part is anonymous */
				      ATOMIC_READ(part->dp_block->db_parts) == VM_DATABLOCK_ANONPARTS &&
				      /* The part isn't mapped as shared by anyone */
				      part->dp_srefs == NULL &&
				      /* There aren't any other copy-on-write nodes. */
				      part->dp_crefs == node && node->vn_link.ln_next == NULL)) {
					sync_endread(part);
					decref_unlikely(part);
					sync_downgrade(effective_vm);
					printk(KERN_DEBUG "Race condition: Must unshare node at %p because of write %u\n",
					       VM_PAGE2ADDR(page));
					goto again_lookup_node_already_locked;
				}

				/* Map the affected page, overriding the mapping hint that originally got us here. */
				prot = node->vn_prot & (PAGEDIR_MAP_FEXEC | PAGEDIR_MAP_FREAD | PAGEDIR_MAP_FWRITE);

				/* Unset so we're able to track changes.
				 * NOTE: The actual tracking of changes isn't something that can be done atomically,
				 *       however atomic kernel pages do not impose any restrictions on use of change
				 *       tracking. */
				if (node->vn_part->dp_flags & VM_DATAPART_FLAG_TRKCHNG && !has_changed)
					prot &= ~PAGEDIR_MAP_FWRITE;
				else if ((prot & PAGEDIR_MAP_FWRITE) && !(ecode & PAGEFAULT_F_WRITING)) {
					/* When `PAGEFAULT_F_WRITING' wasn't set, we didn't actually unshare the part, so if
					 * we're mapping it with write permissions, we must delete those in case of a PRIVATE
					 * memory mapping when the part isn't anonymous, or mapped by other SHARED or PRIVATE
					 * mappings. */
					if (!(node->vn_prot & VM_PROT_SHARED) &&
					    (ATOMIC_READ(part->dp_block->db_parts) != VM_DATABLOCK_ANONPARTS ||
					     part->dp_srefs != NULL || part->dp_crefs != node ||
					     node->vn_link.ln_next != NULL))
						prot &= ~PAGEDIR_MAP_FWRITE;
				}
				if (effective_vm != &vm_kernel)
					prot |= PAGEDIR_MAP_FUSER;
				/* If the node isn't prepared, make sure that we can map memory. */
				if (!(node->vn_flags & VM_NODE_FLAG_PREPARED)) {
					if unlikely(!pagedir_prepare_mapone(page)) {
						sync_endwrite(effective_vm);
						sync_endread(part);
						THROW(E_BADALLOC_INSUFFICIENT_PHYSICAL_MEMORY, 1);
					}
				}
				/* Actually map the accessed page! */
				pagedir_mapone(page, ppage, prot);

				assertf(ecode & PAGEFAULT_F_WRITING
				        ? (ecode & PAGEFAULT_F_USERSPACE ? pagedir_isuserwritable(page) : pagedir_iswritable(page))
				        : (ecode & PAGEFAULT_F_USERSPACE ? pagedir_isuseraccessible(page) : pagedir_ismapped(page)),
				        "ecode         = %p\n"
				        "prot          = %p\n"
				        "node->vn_prot = %p\n"
				        "addr          = %p (page %p)\n"
				        "phys          = %I64p (page %I64p)\n"
				        "effective_vm  = %p\n"
				        "has_changed   = %u\n",
				        (uintptr_t)ecode, (uintptr_t)prot, (uintptr_t)node->vn_prot, (uintptr_t)addr, (uintptr_t)page, (u64)VM_PPAGE2ADDR(ppage), (u64)ppage, (uintptr_t)effective_vm, (unsigned int)has_changed);

				sync_endwrite(effective_vm);
				sync_endread(part);
			} EXCEPT {
				decref_unlikely(part);
				RETHROW();
			}
			decref_unlikely(part);
done_before_pop_connections:
			;
		} EXCEPT {
			task_disconnectall();
			task_popconnections(&con);
			RETHROW();
		}
		task_popconnections(&con);
		__IF0 {
pop_connections_and_throw_segfault:
			task_popconnections(&con);
			goto throw_segfault;
pop_connections_and_set_exception_pointers:
			task_popconnections(&con);
			goto set_exception_pointers;
		}
	}
done:
	pagedir_syncone(page);
	return state;
throw_segfault:
	if (pc == (uintptr_t)addr) {
		/* This can happen when trying to call an invalid function pointer.
		 * -> Try to unwind this happening. */
		uintptr_t old_eip;
		uintptr_t sp = irregs_rdsp(&state->ics_irregs);
		if (sp != (uintptr_t)(&state->ics_irregs + 1) && sp >= KERNEL_BASE)
			goto not_a_badcall;
		TRY {
			old_eip = *(uintptr_t *)sp;
		} EXCEPT {
			if (!was_thrown(E_SEGFAULT))
				RETHROW();
			goto not_a_badcall;
		}
#ifdef __x86_64__
		if (IS_USER() != (old_eip >= KERNEL_BASE))
			goto not_a_badcall;
		irregs_wrip(&state->ics_irregs, old_eip);
		irregs_wrsp(&state->ics_irregs, sp + 8);
#else /* __x86_64__ */
		if (sp != (uintptr_t)(&state->ics_irregs_k + 1) || IS_USER()) {
			if (old_eip >= KERNEL_BASE)
				goto not_a_badcall;
			irregs_wrip(&state->ics_irregs_k, old_eip);
			state->ics_irregs_u.ir_esp += 4;
		} else {
			if (old_eip < KERNEL_BASE)
				goto not_a_badcall;
			state->ics_irregs_k.ir_eip = old_eip;
			state = (struct icpustate *)memmove((byte_t *)state + sizeof(void *), state,
			                                    OFFSET_ICPUSTATE_IRREGS +
			                                    SIZEOF_IRREGS_KERNEL);
		}
#endif /* !__x86_64__ */
		PERTASK_SET(_this_exception_info.ei_code, ERROR_CODEOF(E_SEGFAULT_NOTEXECUTABLE));
		PERTASK_SET(_this_exception_info.ei_data.e_pointers[0], (uintptr_t)addr);
#if PAGEFAULT_F_USERSPACE == E_SEGFAULT_CONTEXT_USERCODE && \
PAGEFAULT_F_WRITING == E_SEGFAULT_CONTEXT_WRITING
		PERTASK_SET(_this_exception_info.ei_data.e_pointers[1],
		            (uintptr_t)(E_SEGFAULT_CONTEXT_FAULT) |
		            (uintptr_t)(ecode & (PAGEFAULT_F_USERSPACE | PAGEFAULT_F_WRITING)));
#else
		PERTASK_SET(_this_exception_info.ei_data.e_pointers[1],
		            (uintptr_t)(E_SEGFAULT_CONTEXT_FAULT) |
		            (uintptr_t)(ecode & PAGEFAULT_F_USERSPACE ? E_SEGFAULT_CONTEXT_USERCODE : 0) |
		            (uintptr_t)(ecode & PAGEFAULT_F_WRITING ? E_SEGFAULT_CONTEXT_WRITING : 0));
#endif
		{
			unsigned int i;
			for (i = 2; i < EXCEPTION_DATA_POINTERS; ++i)
				PERTASK_SET(_this_exception_info.ei_data.e_pointers[i], (uintptr_t)0);
		}
		goto do_unwind_state;
	}
not_a_badcall:
	if ((ecode & (PAGEFAULT_F_PRESENT | PAGEFAULT_F_WRITING)) == (PAGEFAULT_F_PRESENT | PAGEFAULT_F_WRITING)) {
		PERTASK_SET(_this_exception_info.ei_code, ERROR_CODEOF(E_SEGFAULT_READONLY));
	} else if ((ecode & PAGEFAULT_F_PRESENT) && ((ecode & PAGEFAULT_F_INSTRFETCH) ||
	                                             (pc == (uintptr_t)addr))) {
		PERTASK_SET(_this_exception_info.ei_code, ERROR_CODEOF(E_SEGFAULT_NOTEXECUTABLE));
	} else {
		PERTASK_SET(_this_exception_info.ei_code, ERROR_CODEOF(E_SEGFAULT_UNMAPPED));
	}
set_exception_pointers:
	PERTASK_SET(_this_exception_info.ei_data.e_pointers[0], (uintptr_t)addr);
#if PAGEFAULT_F_USERSPACE == E_SEGFAULT_CONTEXT_USERCODE && \
PAGEFAULT_F_WRITING == E_SEGFAULT_CONTEXT_WRITING
	PERTASK_SET(_this_exception_info.ei_data.e_pointers[1],
	            (uintptr_t)(E_SEGFAULT_CONTEXT_FAULT) |
	            (uintptr_t)(ecode & (PAGEFAULT_F_USERSPACE | PAGEFAULT_F_WRITING)));
#else
	PERTASK_SET(_this_exception_info.ei_data.e_pointers[1],
	            (uintptr_t)(E_SEGFAULT_CONTEXT_FAULT) |
	            (uintptr_t)(ecode & PAGEFAULT_F_USERSPACE ? E_SEGFAULT_CONTEXT_USERCODE : 0) |
	            (uintptr_t)(ecode & PAGEFAULT_F_WRITING ? E_SEGFAULT_CONTEXT_WRITING : 0));
#endif
	{
		unsigned int i;
		for (i = 2; i < EXCEPTION_DATA_POINTERS; ++i)
			PERTASK_SET(_this_exception_info.ei_data.e_pointers[i], (uintptr_t)0);
#if EXCEPT_BACKTRACE_SIZE != 0
		for (i = 0; i < EXCEPT_BACKTRACE_SIZE; ++i)
			PERTASK_SET(_this_exception_info.ei_trace[i], (void *)0);
#endif
	}
	/* Always make the state point to the instruction _after_ the one causing the problem. */
	pc = (uintptr_t)instruction_trysucc((void const *)pc);
#if 1
	printk(KERN_DEBUG "Segmentation fault at %p (page %p) [pc=%p,%p] [ecode=%#x] [pid=%u]\n",
	       (uintptr_t)addr, (uintptr_t)VM_PAGE2ADDR(page),
	       icpustate_getpc(state), pc, ecode,
	       (unsigned int)task_getroottid_s());
#endif
	irregs_wrip(&state->ics_irregs, pc);
do_unwind_state:
	/* Try to trigger a debugger trap (if enabled) */
	if (kernel_debugtrap_enabled() && (kernel_debugtrap_on & KERNEL_DEBUGTRAP_ON_SEGFAULT))
		state = kernel_debugtrap_r(state, SIGSEGV);
	x86_unwind_interrupt(state);
#undef IS_USER
}

DECL_END

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_HW_PAGEFAULT_C */
