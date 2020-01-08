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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_CORE_ARCH_I386_FAULT_HANDLE_PAGEFAULT_C
#define GUARD_KERNEL_CORE_ARCH_I386_FAULT_HANDLE_PAGEFAULT_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/debugtrap.h>
#include <kernel/except.h>
#include <kernel/fault.h>
#include <kernel/malloc.h>
#include <kernel/memory.h>
#include <kernel/paging.h>
#include <kernel/printk.h>
#include <kernel/vio.h>
#include <kernel/vm.h>
#include <kernel/vm/phys.h>
#include <sched/cpu.h>
#include <sched/except-handler.h>
#include <sched/iobm.h>
#include <sched/pid.h>
#include <sched/tss.h>

#include <hybrid/atomic.h>

#include <asm/cpu-flags.h>
#include <asm/intrin.h>
#include <kos/kernel/cpu-state-compat.h>
#include <kos/kernel/cpu-state-helpers.h>
#include <kos/kernel/cpu-state.h>

#include <assert.h>
#include <signal.h>
#include <string.h>

#include <libinstrlen/instrlen.h>

#include "vio.h"

DECL_BEGIN

#ifndef CONFIG_NO_SMP
#define IF_SMP(...) __VA_ARGS__
#else /* !CONFIG_NO_SMP */
#define IF_SMP(...) /* nothing */
#endif /* CONFIG_NO_SMP */

STATIC_ASSERT(PAGEDIR_MAP_FEXEC == VM_PROT_EXEC);
STATIC_ASSERT(PAGEDIR_MAP_FWRITE == VM_PROT_WRITE);
STATIC_ASSERT(PAGEDIR_MAP_FREAD == VM_PROT_READ);


/* @return: true:  Success
 * @return: false: Must try again (preemption had to be enabled) */
LOCAL bool FCALL
handle_iob_access(struct cpu *__restrict mycpu,
                  bool is_writing,
                  bool allow_preemption) {
#define GET_GFP_FLAGS()                           \
	(allow_preemption ? (GFP_LOCKED | GFP_PREFLT) \
	                  : (GFP_LOCKED | GFP_PREFLT | GFP_ATOMIC))
	struct ioperm_bitmap *iob;
	assert(!PREEMPTION_ENABLED());
	iob = THIS_X86_IOPERM_BITMAP;
	if (!iob) {
		assertf(ATOMIC_READ(FORCPU(mycpu, thiscpu_x86_ioperm_bitmap)) == NULL,
		        "FORCPU(mycpu, thiscpu_x86_ioperm_bitmap) = %p",
		        ATOMIC_READ(FORCPU(mycpu, thiscpu_x86_ioperm_bitmap)));
		if (is_writing) {
			iob = ioperm_bitmap_allocf_nx(GET_GFP_FLAGS());
			if unlikely(!iob) {
				if (!allow_preemption)
					THROW(E_WOULDBLOCK_PREEMPTED);
				/* Re-attempt the allocation with preemption enabled. */
				PREEMPTION_ENABLE();
				iob = ioperm_bitmap_allocf(GFP_LOCKED | GFP_PREFLT);
				assertf(ATOMIC_READ(FORCPU(mycpu, thiscpu_x86_ioperm_bitmap)) == NULL,
				        "FORCPU(mycpu, thiscpu_x86_ioperm_bitmap) = %p",
				        ATOMIC_READ(FORCPU(mycpu, thiscpu_x86_ioperm_bitmap)));
				PERTASK_SET(this_x86_ioperm_bitmap, iob);
				return false;
			}
		} else {
			iob = incref(&ioperm_bitmap_empty);
			ATOMIC_FETCHINC(iob->ib_share);
		}
		/* NOTE: The following line causes an inconsistency that is fixed by
		 *       assigning `FORCPU(mycpu, thiscpu_x86_ioperm_bitmap) = iob'
		 *       below. Because preemption is currently off, this inconsistency
		 *       never becomes visible outside of this function. */
		PERTASK_SET(this_x86_ioperm_bitmap, iob);
	} else if (is_writing && ATOMIC_READ(iob->ib_share) > 1) {
		/* Unshare the IOB vector prior to allowing write-access */
		REF struct ioperm_bitmap *cow;
		cow = ioperm_bitmap_copyf_nx(iob, GET_GFP_FLAGS());
		if unlikely(!cow) {
			if (!allow_preemption)
				THROW(E_WOULDBLOCK_PREEMPTED);

			/* Re-attempt the allocation with preemption enabled. */
			PREEMPTION_ENABLE();
			cow = ioperm_bitmap_copyf(iob, GFP_LOCKED | GFP_PREFLT);

			/* Unmap the current IOB map if it still points to our old IOB.
			 * This must be done to ensure that the assumption:
			 *     FORCPU(mycpu, thiscpu_x86_ioperm_bitmap) == NULL ||
			 *     FORCPU(mycpu, thiscpu_x86_ioperm_bitmap) == THIS_X86_IOPERM_BITMAP
			 * continues to be consistent.
			 */
			assertf(THIS_X86_IOPERM_BITMAP == iob,
			        "THIS_X86_IOPERM_BITMAP = %p\n"
			        "iob                    = %p",
			        THIS_X86_IOPERM_BITMAP, iob);
			if (ATOMIC_READ(FORCPU(mycpu, thiscpu_x86_ioperm_bitmap)) == iob) {
				PREEMPTION_DISABLE();
				COMPILER_READ_BARRIER();
				if (FORCPU(mycpu, thiscpu_x86_ioperm_bitmap) == iob) {
					pagedir_unmap(FORCPU(mycpu, thiscpu_x86_iob), 2 * PAGESIZE);
					pagedir_sync(FORCPU(mycpu, thiscpu_x86_iob), 2 * PAGESIZE);
					FORCPU(mycpu, thiscpu_x86_ioperm_bitmap) = NULL;
				}
				PREEMPTION_ENABLE();
			} else {
				assertf(ATOMIC_READ(FORCPU(mycpu, thiscpu_x86_ioperm_bitmap)) == NULL,
				        "FORCPU(mycpu, thiscpu_x86_ioperm_bitmap) = %p",
				        ATOMIC_READ(FORCPU(mycpu, thiscpu_x86_ioperm_bitmap)));
			}
			PERTASK_SET(this_x86_ioperm_bitmap, cow);
			ATOMIC_FETCHDEC(iob->ib_share);
			decref(iob);
			return false;
		}
		/* NOTE: The following line causes an inconsistency that is fixed by
		 *       assigning `FORCPU(mycpu, thiscpu_x86_ioperm_bitmap) = iob'
		 *       below. Because preemption is currently off, this inconsistency
		 *       never becomes visible outside of this function. */
		PERTASK_SET(this_x86_ioperm_bitmap, cow);
		ATOMIC_FETCHDEC(iob->ib_share);
		decref(iob);
		iob = cow;
	}
	pagedir_map(FORCPU(mycpu, thiscpu_x86_iob),
	            2 * PAGESIZE,
	            iob->ib_pages,
	            is_writing ? (PAGEDIR_MAP_FREAD | PAGEDIR_MAP_FWRITE)
	                       : (PAGEDIR_MAP_FREAD));
	FORCPU(mycpu, thiscpu_x86_ioperm_bitmap) = iob;
#undef GET_GFP_FLAGS
	return true;
}


#ifndef CONFIG_NO_SMP
/* Check if the given `node' is the IOB vector of some CPU */
LOCAL NOBLOCK WUNUSED ATTR_CONST bool
NOTHROW(FCALL is_iob_node)(struct vm_node *node) {
	cpuid_t i;
	for (i = 0; i < cpu_count; ++i) {
		if (node == &FORCPU(cpu_vector[i], thiscpu_x86_iobnode))
			return true;
	}
	return false;
}

/* Check if `*pc' points to some I/O instruction that doesn't
 * perform a read or write access to `fault_addr'. */
LOCAL WUNUSED bool FCALL
is_io_instruction_and_not_memory_access(byte_t *pc,
                                        struct icpustate *state,
                                        uintptr_t fault_addr) {
	byte_t opcode;
	bool result = true;
	unsigned int pfx66;
	COMPILER_BARRIER();
#ifdef __x86_64__
	pfx66 = 0;
#else /* __x86_64__ */
	pfx66 = (icpustate_getpflags(state) & EFLAGS_VM) ? 1 : 0;
#endif /* !__x86_64__ */
	opcode = *pc++;
	/* Parse prefix bytes. */
	for (;;) {
		if (opcode == 0x66) {
#ifdef __x86_64__
			pfx66 = 1;
#else /* __x86_64__ */
			pfx66 ^= 1;
#endif /* !__x86_64__ */
			opcode = *pc++;
			continue;
		}
		if (opcode == 0xf3) { /* rep */
			opcode = *pc++;
			continue;
		}
		break;
	}

	switch (opcode) {

	case 0xee: /* out dx, al */
	case 0xef: /* out dx, ax | out dx, eax */
	case 0xe6: /* out imm8, al */
	case 0xe7: /* out imm8, ax | out imm8, eax */
	case 0xe4: /* in al, imm8 */
	case 0xe5: /* in ax, imm8 | in eax, imm8 */
	case 0xec: /* in al, dx */
	case 0xed: /* in ax, dx | in eax, dx */
		break;

	case 0x6c: /* insb */
		if (gpregs_getpdi(&state->ics_gpregs) == fault_addr)
			goto nope;
		break;

	case 0x6d: /* insw | insd */
		if (fault_addr >= gpregs_getpdi(&state->ics_gpregs) &&
		    fault_addr < gpregs_getpdi(&state->ics_gpregs) + (pfx66 ? 2 : 4))
			goto nope;
		break;

	case 0x6e: /* outsb */
		if (gpregs_getpsi(&state->ics_gpregs) == fault_addr)
			goto nope;
		break;

	case 0x6f: /* outsw | outsd */
		if (fault_addr >= gpregs_getpsi(&state->ics_gpregs) &&
		    fault_addr < gpregs_getpsi(&state->ics_gpregs) + (pfx66 ? 2 : 4))
			goto nope;
		break;

	default:
nope:
		result = false;
		break;
	}

	COMPILER_BARRIER();
	return result;
}

#else /* !CONFIG_NO_SMP */

#define is_iob_node(node) ((node) == &FORCPU(&_bootcpu, thiscpu_x86_iobnode))

#endif /* CONFIG_NO_SMP */


DATDEF byte_t x86_memcpy_nopf_rep_pointer[];
DATDEF byte_t x86_memcpy_nopf_ret_pointer[];


INTERN struct icpustate *FCALL
x86_handle_pagefault(struct icpustate *__restrict state, uintptr_t ecode) {
#if 1
#define isuser() (ecode & X86_PAGEFAULT_ECODE_USERSPACE)
#else
#define isuser() icpustate_isuser(state)
#endif
	void *addr;
	uintptr_t pc;
	pageid_t pageid;
	void *pageaddr;
	struct vm *effective_vm;
	uintptr_half_t prot;
	bool has_changed;
	/* Check for memcpy_nopf() */
	pc = state->ics_irregs.ir_pip;
	if unlikely_untraced(pc == (uintptr_t)x86_memcpy_nopf_rep_pointer) {
		state->ics_irregs.ir_pip = (uintptr_t)x86_memcpy_nopf_ret_pointer;
		return state;
	}
	addr = __rdcr2();
	/* Re-enable interrupts if they were enabled before. */
	if (state->ics_irregs.ir_pflags & EFLAGS_IF)
		__sti();
	pageid   = PAGEID_ENCODE(addr);
	pageaddr = (void *)((uintptr_t)addr & ~PAGEMASK);
#if 0
	printk(KERN_DEBUG "Page fault at %p (page %p) [pc=%p,sp=%p] [ecode=%#x] [tid=%u]\n",
	       (uintptr_t)addr, pageaddr, pc, icpustate_getsp(state),
	       ecode, (unsigned int)task_getroottid_s());
#endif
	if ((ecode & (X86_PAGEFAULT_ECODE_PRESENT | X86_PAGEFAULT_ECODE_USERSPACE)) == 0 &&
	    pageid >= PAGEID_ENCODE(KERNELSPACE_BASE)) {
	    /* Check if a hint was defined for this page. */
		struct vm_node *hinted_node;
		if ((hinted_node = (struct vm_node *)pagedir_gethint(addr)) != NULL) {
			/* This is a hinted node (perform assertions on all
			 * of the requirements documented for such a node) */
			pageptr_t ppage;
			assert(hinted_node->vn_flags & VM_NODE_FLAG_HINTED);
			assert(hinted_node->vn_prot & VM_PROT_SHARED);
			assert(hinted_node->vn_flags & VM_NODE_FLAG_PREPARED);
			assert(!(hinted_node->vn_flags & VM_NODE_FLAG_PARTITIONED));
			assert(hinted_node->vn_vm == &vm_kernel);
			assert(hinted_node->vn_part != NULL);
			assert(hinted_node->vn_block != NULL);
			assert(hinted_node->vn_guard == 0);
			assert(hinted_node->vn_part->dp_srefs == hinted_node);
			assert(hinted_node->vn_link.ln_pself == &hinted_node->vn_part->dp_srefs);
			assert(hinted_node->vn_link.ln_next == NULL);
			assert(hinted_node->vn_part->dp_crefs == NULL);
			assert(!isshared(hinted_node->vn_part));
			assert(hinted_node->vn_part->dp_block == hinted_node->vn_block);
			assert(hinted_node->vn_block->db_parts == VM_DATABLOCK_ANONPARTS);
			assert(hinted_node->vn_part->dp_flags & VM_DATAPART_FLAG_LOCKED);
			assert(hinted_node->vn_part->dp_state == VM_DATAPART_STATE_LOCKED);
			has_changed = ecode & X86_PAGEFAULT_ECODE_WRITING;
			/* Load the affected page into the core. */
			ppage = vm_datapart_loadpage(hinted_node->vn_part,
			                             (size_t)(pageid - vm_node_getminpageid(hinted_node)),
			                             &has_changed);
			/* Map the affected page, overriding the mapping hint that originally got us here. */
			prot = hinted_node->vn_prot & (PAGEDIR_MAP_FEXEC | PAGEDIR_MAP_FREAD | PAGEDIR_MAP_FWRITE);
			/* Unset so we're able to track changes.
			 * NOTE: The actual tracking of changes isn't something that can be done atomically,
			 *       however atomic kernel pages do not impose any restrictions on use of change
			 *       tracking. */
			if ((hinted_node->vn_part->dp_flags & VM_DATAPART_FLAG_TRKCHNG) && !has_changed)
				prot &= ~PAGEDIR_MAP_FWRITE;
			pagedir_mapone(pageaddr, page2addr(ppage), prot);
			goto done;
		}
	}
	effective_vm = &vm_kernel;
	if (pageid < PAGEID_ENCODE(KERNELSPACE_BASE) || isuser())
		effective_vm = THIS_VM;
	{
		struct task_connections con;
		size_t vpage_offset; /* Offset (in vpages) of the accessed page from the start of `node' */
		task_pushconnections(&con);
		TRY {
			struct vm_node *node;
			struct vm_datapart *part;
again_lookup_node:
			sync_read(effective_vm);
again_lookup_node_already_locked:
			assert(sync_reading(effective_vm));
			assert(!sync_writing(effective_vm));
			/* Lookup the node associated with the given page. */
			node = vm_getnodeofpageid(effective_vm, pageid);
			if unlikely(!node) {
				sync_endread(effective_vm);
				if (pageid >= PAGEID_ENCODE(KERNELSPACE_BASE) &&
				    effective_vm != &vm_kernel && isuser()) {
					/* This can happen depending on what the CPU does when
					 * attempting to access the IOB vector associated with
					 * the calling thread.
					 * In this case, we must re-attempt the lookup within kernel-space. */
					sync_read(&vm_kernel);
					node = vm_getnodeofpageid(&vm_kernel, pageid);
					if (node && !node->vn_part) {
						sync_endread(&vm_kernel);
						/* Reservation node. */
						if (is_iob_node(node))
							goto do_handle_iob_node_access;
						goto pop_connections_and_throw_segfault;
					}
					sync_endread(&vm_kernel);
				}
				goto pop_connections_and_throw_segfault;
			}
			if unlikely(!node->vn_part) {
				struct cpu *mycpu;
				sync_endread(effective_vm);
				/* Check for special case: `node' may be the `thiscpu_x86_iobnode' of some CPU */
do_handle_iob_node_access:
				mycpu = THIS_CPU;
				if (node == &FORCPU(mycpu, thiscpu_x86_iobnode)) {
					PREEMPTION_DISABLE();
					IF_SMP(COMPILER_READ_BARRIER();)
					IF_SMP(mycpu = THIS_CPU;)
					IF_SMP(if (node == &FORCPU(mycpu, thiscpu_x86_iobnode))) {
						/* Most likely case: Accessing the IOB of the current CPU. */
						bool allow_preemption;
						assertf(FORCPU(mycpu, thiscpu_x86_ioperm_bitmap) == NULL ||
						        FORCPU(mycpu, thiscpu_x86_ioperm_bitmap) == THIS_X86_IOPERM_BITMAP,
						        "mycpu                                    = %p\n"
						        "FORCPU(mycpu, thiscpu_x86_ioperm_bitmap) = %p\n"
						        "THIS_X86_IOPERM_BITMAP                   = %p\n",
						        mycpu, FORCPU(mycpu, thiscpu_x86_ioperm_bitmap),
						        THIS_X86_IOPERM_BITMAP);
						/* Make sure to handle any access errors after the ioperm() bitmap
						 * was already mapped during the current quantum as full segfault. */
						if unlikely(FORCPU(mycpu, thiscpu_x86_ioperm_bitmap) != NULL) {
							/* Check for special case: even if the IOPERM bitmap is already
							 * mapped, allow a mapping upgrade if it was mapped read-only
							 * before, but is now needed as read-write. */
							if ((ecode & X86_PAGEFAULT_ECODE_WRITING) && !pagedir_iswritable(addr))
								; /* Upgrade the mapping */
							else {
								goto pop_connections_and_throw_segfault;
							}
						}
						allow_preemption = (icpustate_getpflags(state) & EFLAGS_IF) != 0;
						/* Make special checks if the access itself seems to
						 * originate from a direct user-space access. */
						if ((ecode & X86_PAGEFAULT_ECODE_USERSPACE) && isuser()) {
							/* User-space can never get write-access to the IOB vector. */
							if (ecode & X86_PAGEFAULT_ECODE_WRITING)
								goto pop_connections_and_throw_segfault;
							/* User-space isn't allowed to directly access the IOB vector.
							 * To not rely on undocumented processor behavior, manually check
							 * if the access originates from a user-space I/O instruction.
							 * If not (such as user-space directly trying to read kernel memory),
							 * then we always deny the access, no matter what! */
							if (!is_io_instruction_and_not_memory_access((byte_t *)pc, state, (uintptr_t)addr))
								goto pop_connections_and_throw_segfault;
						}
						if (!handle_iob_access(mycpu, (ecode & X86_PAGEFAULT_ECODE_WRITING) != 0, allow_preemption)) {
							assert(PREEMPTION_ENABLED());
							goto again_lookup_node;
						}
						if (allow_preemption)
							__sti();
						goto done_before_pop_connections;
					}
					IF_SMP(if (icpustate_getpflags(state) & EFLAGS_IF) __sti());
				}
				/* Either this is an access to the IOB vector of a different CPU,
				 * or the accessed node is just some random, reservation node.
				 * In the former case, we must take care to deal with a race condition
				 * which may happen in an SMP system where our current thread has been
				 * moved to a different CPU since we've re-enabled preemption at the
				 * start of this function, and before getting here. In that case, the
				 * access is still going to reference the IOB of the old CPU, and we
				 * have to alter our behavior depending on the access happening because
				 * of the some invalid access to a different CPU's IOB vector, or the
				 * access being caused by the CPU itself, and a CPU-transfer happening
				 * at just the wrong moment. */
#ifndef CONFIG_NO_SMP
				if (is_iob_node(node)) {
					/* If we didn't actually re-enable preemption, then no cpu-transfer could have happened! */
					if (!(icpustate_getpflags(state) & EFLAGS_IF))
						goto pop_connections_and_throw_segfault;
					if (!isuser())
						goto pop_connections_and_throw_segfault;
					/* If the calling thread couldn't have changed CPUs, then this is an access to  */
					if (PERTASK_GET(this_task.t_flags) & TASK_FKEEPCORE)
						goto pop_connections_and_throw_segfault;
					/* The calling thread is capable of being migrated between different CPUs,
					 * and the accessed node _is_ the IOB vector of a different CPU. However with
					 * all of these factors, there still exists the possibility that the access
					 * happened because the CPU itself accessed the vector, as may be triggered
					 * by use of the `(in|out)(b|w|l)' instructions.
					 * To make sure that we can handle those cases as well, as can check the
					 * memory to which `icpustate_getpc(state)' points for being one of these
					 * instructions.
					 * To prevent the possibility of repeating the access to the IOB vector during
					 * this check (in case a bad jump caused IP to end up within the IOB vector),
					 * also make sure that `pc' isn't apart of said vector! */
					if (pc >= (uintptr_t)vm_node_getmin(node) &&
					    pc <= (uintptr_t)vm_node_getmax(node))
						goto pop_connections_and_throw_segfault;
					/* If we got here cause of an I/O instruction, just return to the caller and
					 * have them attempt the access once again, hopefully without accessing  */
					if (is_io_instruction_and_not_memory_access((byte_t *)pc, state, (uintptr_t)addr))
						goto done_before_pop_connections;
				}
#endif /* !CONFIG_NO_SMP */
				goto pop_connections_and_throw_segfault;
			}
			if (node->vn_guard) {
				/* TODO: Map a new guard above/below this node! */
			}
			assert(!wasdestroyed(node->vn_part));
			part         = incref(node->vn_part);
			vpage_offset = (size_t)(pageid - vm_node_getminpageid(node));
			assert(vm_node_getpagecount(node) == vm_datapart_numvpages(part));
			has_changed = ecode & X86_PAGEFAULT_ECODE_WRITING;
			/* Acquire a lock to the affected data part. */
			TRY {
				pageptr_t ppage;
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
					args.ma_args.va_access_partoff = ((pos_t)(vpage_offset +
					                                          vm_datapart_mindpage(part))
					                                  << VM_DATABLOCK_ADDRSHIFT(args.ma_args.va_block));
					sync_endread(part);
					args.ma_args.va_type = args.ma_args.va_block->db_vio;
					if unlikely(!args.ma_args.va_type) {
						decref_unlikely(args.ma_args.va_block);
						decref_unlikely(part);
						goto pop_connections_and_throw_segfault;
					}
					args.ma_args.va_part          = part; /* Inherit reference */
					args.ma_args.va_access_pageid = pageid;
					args.ma_args.va_state         = state;
					args.ma_oldcons               = &con; /* Inherit */
					/* Check for special case: call into VIO memory */
					if (args.ma_args.va_type->dtv_call && (uintptr_t)addr == pc) {
						/* Make sure that memory mapping has execute permissions! */
						if unlikely(!(nodeprot & VM_PROT_EXEC)) {
							goto vio_failure_throw_segfault;
						}
						/* Special case: call into VIO memory */
						TRY {
							pos_t vio_addr;
							uintptr_t callsite_pc;
							uintptr_t sp;
							/* Must unwind the stack to restore the IP of the VIO call-site. */
							sp = icpustate_getsp(state);
							if (sp >= KERNELSPACE_BASE && isuser())
								goto do_normal_vio; /* Validate the stack-pointer for user-space. */
							TRY {
								callsite_pc = *(uintptr_t *)sp;
							} EXCEPT {
								if (!was_thrown(E_SEGFAULT))
									RETHROW();
								goto do_normal_vio;
							}
							/* Unwind the stack, and remember the call-site instruction pointer. */
#ifdef __x86_64__
							if (isuser() ? (callsite_pc >= USERSPACE_END)
							             : (callsite_pc < KERNELSPACE_BASE))
								goto do_normal_vio;
							icpustate_setpc(state, callsite_pc);
							icpustate_setsp(state, sp + 8);
#else /* __x86_64__ */
							if (sp != (uintptr_t)(&state->ics_irregs_k + 1) ||
							    isuser()) {
								if (callsite_pc >= KERNELSPACE_BASE)
									goto do_normal_vio;
								irregs_wrip(&state->ics_irregs_k, callsite_pc);
								state->ics_irregs_u.ir_esp += 4;
							} else {
								if (callsite_pc < KERNELSPACE_BASE)
									goto do_normal_vio;
								state->ics_irregs_k.ir_eip = callsite_pc;
								state = (struct icpustate *)memmoveup((byte_t *)state + sizeof(void *), state,
								                                      OFFSET_ICPUSTATE_IRREGS +
								                                      SIZEOF_IRREGS_KERNEL);
							}
#endif /* !__x86_64__ */
							/* Figure out the exact VIO address that got called. */
							vio_addr = (pos_t)addr;
							vio_addr -= (pos_t)PAGEID_DECODE(args.ma_args.va_access_pageid);
							vio_addr += (pos_t)args.ma_args.va_access_partoff;
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
					if unlikely((ecode & X86_PAGEFAULT_ECODE_WRITING)
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
					return x86_vio_main(&args, (uintptr_t)addr);
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
								xdecref(vm_datapart_split(part, vpage_offset));
								decref_unlikely(part);
								goto again_lookup_node;
							}
							if (vm_datapart_numvpages(part) != 1) {
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
							pageptr_t old_ppage, new_ppage;
							/* Verify that the access being made is valid. */
							if unlikely(!(node->vn_prot & VM_PROT_WRITE))
								goto endread_and_decref_part_and_set_readonly;
							if (!(node->vn_prot & VM_PROT_EXEC)) {
								if unlikely((ecode & X86_PAGEFAULT_ECODE_INSTRFETCH) || (uintptr_t)addr == pc)
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
							assert(vm_node_getstartpageid(node) == pageid);
							assert(vm_node_getpagecount(node) == 1);

							/* Make sure that PAGE#0 of `part' has been initialized!
							 * If it wasn't, we need to initialize it now, since
							 * otherwise we'd be copying uninitialized data below!
							 * Also: If this page isn't marked as initialized, the
							 *       duplicated part won't be set as such, either! */
							{
								unsigned int i, count;
								count = VM_DATABLOCK_PAGEALIGN(part->dp_block);
								for (i = 0; i < count; ++i) {
									unsigned int part_state;
									part_state = vm_datapart_getstate(part, i);
									if (VM_DATAPART_PPP_ISINITIALIZED(part_state))
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
								if unlikely(vm_getnodeofpageid(effective_vm, pageid) != node ||
								            node->vn_part != part ||
								            (node->vn_prot & VM_PROT_SHARED)) {
									decref_unlikely(part);
									kfree(new_part);
									printk(KERN_DEBUG "Race condition: Mapping target at %p (%p) has changed during unshare (#1)\n",
									       pageaddr, addr);
									goto again_lookup_node_already_locked;
								}
								sync_endread(effective_vm);
								vm_datapart_lockwrite_setcore(part);
							}

							/* Allocate the physical memory used for backing the vm-local copy. */
							new_ppage = page_mallocone();
							/* Check if the allocation failed. */
							if unlikely(new_ppage == PAGEPTR_INVALID) {
								sync_endwrite(part);
								kfree(new_part);
								THROW(E_BADALLOC_INSUFFICIENT_PHYSICAL_MEMORY, PAGESIZE);
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
							if unlikely(vm_getnodeofpageid(effective_vm, pageid) != node ||
							            node->vn_part != part ||
							            (node->vn_prot & VM_PROT_SHARED)) {
								sync_downgrade(effective_vm);
								sync_endwrite(part);
								page_free(new_ppage, 1);
								kfree(new_part);
								decref_unlikely(part);
								printk(KERN_DEBUG "Race condition: Mapping target at %p (%p) has changed during unshare (#2)\n",
								       pageaddr, addr);
								goto again_lookup_node_already_locked;
							}
							/* If the node isn't prepared, make sure that we can map memory. */
							if (!(node->vn_flags & VM_NODE_FLAG_PREPARED)) {
								if unlikely(!pagedir_prepare_mapone(pageaddr)) {
									sync_endwrite(effective_vm);
									sync_endwrite(part);
									page_free(new_ppage, 1);
									kfree(new_part);
									decref_unlikely(part);
									THROW(E_BADALLOC_INSUFFICIENT_PHYSICAL_MEMORY, PAGESIZE);
								}
							}

							/* Copy the contents of the page being unshared. */
							old_ppage = part->dp_ramdata.rd_blockv[0].rb_start;
							vm_copypageinphys(page2addr(new_ppage),
							                  page2addr(old_ppage));

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
							pagedir_mapone(pageaddr, page2addr(new_ppage), prot);
							vm_sync_endone(effective_vm, pageaddr);

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
							printk(KERN_TRACE "[vm] Unshared page at %p [tid=%u,pc=%p,sp=%p]\n",
							       pageaddr, task_getroottid_s(),
							       pc, icpustate_getsp(state));
#else
							printk(KERN_TRACE "[vm] Unshared page at %p [tid=%u,pc=%p,sp=%p,oldpage=" FORMAT_VM_PHYS_T ",newpage=" FORMAT_VM_PHYS_T "]\n",
							       pageaddr, task_getroottid_s(),
							       page2addr(old_ppage), page2addr(new_ppage),
							       pc, icpustate_getsp(state));
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
				            (ecode & X86_PAGEFAULT_ECODE_WRITING)) {
					/* Read-only memory */
endread_and_decref_part_and_set_readonly:
					sync_endread(part);
					decref_unlikely(part);
					PERTASK_SET(this_exception_code, ERROR_CODEOF(E_SEGFAULT_READONLY));
					goto pop_connections_and_set_exception_pointers;
				}
				if unlikely(!(node->vn_prot & VM_PROT_READ) &&
				            !(ecode & X86_PAGEFAULT_ECODE_WRITING)) {
					/* Write-only memory */
					PERTASK_SET(this_exception_code, ERROR_CODEOF(E_SEGFAULT_NOTREADABLE));
					sync_endread(part);
					decref_unlikely(part);
					goto pop_connections_and_set_exception_pointers;
				}
				if (!(node->vn_prot & VM_PROT_EXEC)) {
					if unlikely((ecode & X86_PAGEFAULT_ECODE_INSTRFETCH) || (uintptr_t)addr == pc) {
						/* Non-executable memory */
endread_and_decref_part_and_set_noexec:
						sync_endread(part);
						decref_unlikely(part);
						PERTASK_SET(this_exception_code, ERROR_CODEOF(E_SEGFAULT_NOTEXECUTABLE));
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
				if unlikely(vm_getnodeofpageid(effective_vm, pageid) != node ||
				            node->vn_part != part) {
					sync_endread(part);
					decref_unlikely(part);
					sync_downgrade(effective_vm);
					printk(KERN_DEBUG "Race condition: Mapping target at %p has changed\n",
					       pageaddr);
					goto again_lookup_node_already_locked;
				}

				/* Check one more time if we must unshare the node when writing.
				 * This may still trigger after a fork() that happened in another
				 * thread within the same VM, which copied the VM before we got here,
				 * but did so after we checked this above (aka.: during the time
				 * when we had to release our VM lock to initialize the associated
				 * data part page) */
				if ((ecode & X86_PAGEFAULT_ECODE_WRITING) &&
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
					       pageaddr);
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
				else if ((prot & PAGEDIR_MAP_FWRITE) && !(ecode & X86_PAGEFAULT_ECODE_WRITING)) {
					/* When `X86_PAGEFAULT_ECODE_WRITING' wasn't set, we didn't actually unshare the part, so if
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
					if unlikely(!pagedir_prepare_mapone(pageaddr)) {
						sync_endwrite(effective_vm);
						sync_endread(part);
						THROW(E_BADALLOC_INSUFFICIENT_PHYSICAL_MEMORY, PAGESIZE);
					}
				}
				/* Actually map the accessed page! */
				pagedir_mapone(pageaddr, page2addr(ppage), prot);

				/* Make sure that the performed access can now succeed */
				assertf(ecode & X86_PAGEFAULT_ECODE_WRITING
				        ? (ecode & X86_PAGEFAULT_ECODE_USERSPACE
				           ? pagedir_isuserwritable(addr)
				           : pagedir_iswritable(addr))
				        : (ecode & X86_PAGEFAULT_ECODE_USERSPACE
				           ? pagedir_isuseraccessible(addr)
				           : pagedir_ismapped(addr)),
				        "ecode         = %p\n"
				        "prot          = %p\n"
				        "node->vn_prot = %p\n"
				        "addr          = %p (page %p)\n"
				        "phys          = " FORMAT_VM_PHYS_T " (page " FORMAT_PAGEPTR_T ")\n"
				        "effective_vm  = %p\n"
				        "has_changed   = %u\n",
				        (uintptr_t)ecode,
				        (uintptr_t)prot,
				        (uintptr_t)node->vn_prot,
				        (uintptr_t)addr,
				        (uintptr_t)pageaddr,
				        (vm_phys_t)page2addr(ppage),
				        (pageptr_t)ppage,
				        (uintptr_t)effective_vm,
				        (unsigned int)has_changed);
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
			if (isuser())
				PERTASK_SET(this_exception_faultaddr, (void *)pc);
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
	pagedir_syncone(addr);
	pagedir_syncall();
	return state;
throw_segfault:
	if (pc == (uintptr_t)addr) {
		/* This can happen when trying to call an invalid function pointer.
		 * -> Try to unwind this happening. */
		uintptr_t callsite_pc;
		uintptr_t sp = icpustate_getsp(state);
		if (sp >= KERNELSPACE_BASE && (sp != (uintptr_t)(&state->ics_irregs + 1) || isuser()))
			goto not_a_badcall;
		TRY {
			callsite_pc = *(uintptr_t *)sp;
		} EXCEPT {
			if (!was_thrown(E_SEGFAULT)) {
				if (isuser())
					PERTASK_SET(this_exception_faultaddr, (void *)pc);
				RETHROW();
			}
			goto not_a_badcall;
		}
#ifdef __x86_64__
		if (isuser() ? (callsite_pc >= USERSPACE_END)
		             : (callsite_pc < KERNELSPACE_BASE))
			goto not_a_badcall;
		icpustate_setpc(state, callsite_pc);
		icpustate_setsp(state, sp + 8);
#else /* __x86_64__ */
		if (sp != (uintptr_t)(&state->ics_irregs_k + 1) || isuser()) {
			if (callsite_pc >= KERNELSPACE_BASE)
				goto not_a_badcall;
			icpustate_setpc(state, callsite_pc);
			state->ics_irregs_u.ir_esp += 4;
		} else {
			if (callsite_pc < KERNELSPACE_BASE)
				goto not_a_badcall;
			state->ics_irregs_k.ir_eip = callsite_pc;
			state = (struct icpustate *)memmoveup((byte_t *)state + sizeof(void *), state,
			                                      OFFSET_ICPUSTATE_IRREGS +
			                                      SIZEOF_IRREGS_KERNEL);
		}
#endif /* !__x86_64__ */
		TRY {
			void const *call_instr;
			call_instr = instruction_pred((void *)callsite_pc);
			if likely(call_instr)
				callsite_pc = (uintptr_t)call_instr;
		} EXCEPT {
			if (!was_thrown(E_SEGFAULT)) {
				if (isuser())
					PERTASK_SET(this_exception_faultaddr, (void *)pc);
				RETHROW();
			}
			/* Discard read-from-callsite_pc exception... */
		}
		PERTASK_SET(this_exception_faultaddr, (void *)callsite_pc);
		PERTASK_SET(this_exception_code, ERROR_CODEOF(E_SEGFAULT_NOTEXECUTABLE));
		PERTASK_SET(this_exception_pointers[0], (uintptr_t)addr);
#if X86_PAGEFAULT_ECODE_USERSPACE == E_SEGFAULT_CONTEXT_USERCODE && \
    X86_PAGEFAULT_ECODE_WRITING == E_SEGFAULT_CONTEXT_WRITING
		PERTASK_SET(this_exception_pointers[1],
		            (uintptr_t)(E_SEGFAULT_CONTEXT_FAULT) |
		            (uintptr_t)(ecode & (X86_PAGEFAULT_ECODE_USERSPACE | X86_PAGEFAULT_ECODE_WRITING)));
#else
		PERTASK_SET(this_exception_pointers[1],
		            (uintptr_t)(E_SEGFAULT_CONTEXT_FAULT) |
		            (uintptr_t)(ecode & X86_PAGEFAULT_ECODE_USERSPACE ? E_SEGFAULT_CONTEXT_USERCODE : 0) |
		            (uintptr_t)(ecode & X86_PAGEFAULT_ECODE_WRITING ? E_SEGFAULT_CONTEXT_WRITING : 0));
#endif
		{
			unsigned int i;
			for (i = 2; i < EXCEPTION_DATA_POINTERS; ++i)
				PERTASK_SET(this_exception_pointers[i], (uintptr_t)0);
		}
		printk(KERN_DEBUG "[segfault] PC-Fault at %p (page %p) [pc=%p,%p] [ecode=%#x] [tid=%u]\n",
		       addr, pageaddr, callsite_pc, icpustate_getpc(state),
		       ecode, (unsigned int)task_getroottid_s());
		goto do_unwind_state;
	}
not_a_badcall:
	if ((ecode & (X86_PAGEFAULT_ECODE_PRESENT | X86_PAGEFAULT_ECODE_WRITING)) == (X86_PAGEFAULT_ECODE_PRESENT | X86_PAGEFAULT_ECODE_WRITING)) {
		PERTASK_SET(this_exception_code, ERROR_CODEOF(E_SEGFAULT_READONLY));
	} else if ((ecode & X86_PAGEFAULT_ECODE_PRESENT) && ((ecode & X86_PAGEFAULT_ECODE_INSTRFETCH) ||
	                                             (pc == (uintptr_t)addr))) {
		PERTASK_SET(this_exception_code, ERROR_CODEOF(E_SEGFAULT_NOTEXECUTABLE));
	} else {
		PERTASK_SET(this_exception_code, ERROR_CODEOF(E_SEGFAULT_UNMAPPED));
	}
set_exception_pointers:
	PERTASK_SET(this_exception_pointers[0], (uintptr_t)addr);
#if (X86_PAGEFAULT_ECODE_USERSPACE == E_SEGFAULT_CONTEXT_USERCODE && \
     X86_PAGEFAULT_ECODE_WRITING == E_SEGFAULT_CONTEXT_WRITING)
	PERTASK_SET(this_exception_pointers[1],
	            (uintptr_t)(E_SEGFAULT_CONTEXT_FAULT) |
	            (uintptr_t)(ecode & (X86_PAGEFAULT_ECODE_USERSPACE | X86_PAGEFAULT_ECODE_WRITING)));
#else
	PERTASK_SET(this_exception_pointers[1],
	            (uintptr_t)(E_SEGFAULT_CONTEXT_FAULT) |
	            (uintptr_t)(ecode & X86_PAGEFAULT_ECODE_USERSPACE ? E_SEGFAULT_CONTEXT_USERCODE : 0) |
	            (uintptr_t)(ecode & X86_PAGEFAULT_ECODE_WRITING ? E_SEGFAULT_CONTEXT_WRITING : 0));
#endif
	{
		unsigned int i;
		for (i = 2; i < EXCEPTION_DATA_POINTERS; ++i)
			PERTASK_SET(this_exception_pointers[i], (uintptr_t)0);
#if EXCEPT_BACKTRACE_SIZE != 0
		for (i = 0; i < EXCEPT_BACKTRACE_SIZE; ++i)
			PERTASK_SET(this_exception_trace[i], (void *)0);
#endif /* EXCEPT_BACKTRACE_SIZE != 0 */
	}
	/* Always make the state point to the instruction _after_ the one causing the problem. */
	PERTASK_SET(this_exception_faultaddr, (void *)pc);
	pc = (uintptr_t)instruction_trysucc((void const *)pc);
	printk(KERN_DEBUG "[segfault] Fault at %p (page %p) [pc=%p,%p] [ecode=%#x] [tid=%u]\n",
	       addr, pageaddr, icpustate_getpc(state), pc,
	       ecode, (unsigned int)task_getroottid_s());
	icpustate_setpc(state, pc);
do_unwind_state:
	/* Try to trigger a debugger trap (if enabled) */
	if (kernel_debugtrap_enabled() && (kernel_debugtrap_on & KERNEL_DEBUGTRAP_ON_SEGFAULT))
		state = kernel_debugtrap_r(state, SIGSEGV);
	x86_userexcept_unwind_interrupt(state);
#undef isuser
}

DECL_END

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_FAULT_HANDLE_PAGEFAULT_C */
