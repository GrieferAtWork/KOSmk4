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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_FAULT_HANDLE_PAGEFAULT_C
#define GUARD_KERNEL_CORE_ARCH_I386_FAULT_HANDLE_PAGEFAULT_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/arch/vm.h>
#include <kernel/debugtrap.h>
#include <kernel/except.h>
#include <kernel/malloc.h>
#include <kernel/memory.h>
#include <kernel/paging.h>
#include <kernel/printk.h>
#include <kernel/vm.h>
#include <kernel/vm/phys.h>
#include <kernel/x86/fault.h>
#include <kernel/x86/idt.h> /* IDT_CONFIG_ISTRAP() */
#include <kernel/x86/phys2virt64.h>
#include <sched/cpu.h>
#include <sched/except-handler.h>
#include <sched/pid.h>
#include <sched/userkern.h>
#include <sched/x86/iobm.h>
#include <sched/x86/tss.h>

#include <hybrid/align.h>
#include <hybrid/atomic.h>

#include <asm/cpu-flags.h>
#include <asm/intrin.h>
#include <kos/kernel/cpu-state-compat.h>
#include <kos/kernel/cpu-state-helpers.h>
#include <kos/kernel/cpu-state.h>
#include <kos/kernel/segment.h>

#include <assert.h>
#include <inttypes.h>
#include <signal.h>
#include <stdint.h>
#include <string.h>

#include <libinstrlen/instrlen.h>
#include <libvio/access.h>
#include <libviocore/viocore.h>
#ifndef __x86_64__
#include <asm/cfi.h>
#endif /* !__x86_64__ */

/* NOTE: This #PF handler is also used while in debugger mode. And here's why:
 *
 * Use the normal #PF handler in debugger mode.
 *
 * This one's kind-of a departure from the original intend that the debugger
 * mode should be as disconnected from the rest of the system as possible.
 * However I've been running into a couple of problems related to how the
 * kernel heap uses lazy mappings to speed up memory allocations outside of
 * GFP_PREFLT and GFP_LOCKED, where any piece of heap memory not allocated
 * with one of these flags may cause the kernel to panic if accessed from
 * within debug mode, since the debugger's old #PF handler intentionally
 * refused to handle this kind of mapping.
 * The design flaw in this is that many places, such as `driver_section_lock()'
 * will make use of regular, old heap memory that falls under the category of
 * the above, meaning that whenever the debugger was accessing debug information
 * of dynamically loaded drivers, there was a chance that it was accessing memory
 * which it was unable to properly initialize.
 *
 * I've debated how to go about fixing this design flaw, and considered adding
 * a global variable `bool dbg_restricted_memory' that could be used to toggle
 * which kind of #PF handler should get used. But then I'd probably had to
 * configure it to not restrict memory by default since there are just soo
 * many places that you wouldn't even think about needing normal #PF handling.
 * So with that in mind, such a flag would have only ever been enabled while
 * doing some kind of dangerous memory access while in debugger-mode. However
 * with the current API, such memory access shouldn't be performed directly
 * anyhow. That's what the `dbg_readmemory()' and `dbg_writememory()' functions
 * are for.
 * So the conclusion was that the debugger shouldn't actually be using its own
 * #PF handling, as doing so has only ever caused problems, and would only end
 * up causing more problems in the future.
 */


DECL_BEGIN

#ifndef __x86_64__

/* Register bootstrap loader.
 * Restore:
 *   %ss  = *(u32 *)(%eax + 0);
 *   %esp = *(u32 *)(%eax + 4);
 *   %eip = *(u32 *)(%eax + 8);
 *   %eax = *(u32 *)(%eax + 12);
 */
INTDEF byte_t x86_vio_kernel_esp_bootstrap_loader[];
__asm__(".pushsection .text.cold\n\t"
        ".global x86_vio_kernel_esp_bootstrap_loader\n\t"
        ".hidden x86_vio_kernel_esp_bootstrap_loader\n\t"
        "x86_vio_kernel_esp_bootstrap_loader:\n\t"
        "	.cfi_startproc simple\n\t"
        "	.cfi_def_cfa %esp, 0\n\t"
        "	.cfi_reg_offset %ss, 0, %eax\n\t"
        "	.cfi_reg_offset %esp, 4, %eax\n\t"
        "	.cfi_reg_offset %eip, 8, %eax\n\t"
        "	.cfi_reg_offset %eax, 12, %eax\n\t"
        "	movw  0(%eax), %ss\n\t"
        "	.cfi_same_value %ss\n\t"
        "	movl  4(%eax), %esp\n\t"
        "	pushl 8(%eax)\n\t"
        "	movl  12(%eax), %eax\n\t"
        "	.cfi_same_value %eax\n\t"
        "	.cfi_reg_value  %esp, 4, %esp\n\t"
        "	.cfi_reg_offset %eip, 0, %esp\n\t"
        "	ret\n\t"
        "	.cfi_endproc\n\t"
        ".size x86_vio_kernel_esp_bootstrap_loader, . - x86_vio_kernel_esp_bootstrap_loader\n\t"
        ".popsection");
#endif /* !__x86_64__ */

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


#ifndef NDEBUG
INTDEF NOBLOCK ATTR_RETNONNULL struct task *
NOTHROW(KCALL x86_repair_broken_tls_state)(void);
#endif /* !NDEBUG */





PRIVATE ATTR_NORETURN void FCALL
rethrow_exception_from_pf_handler(struct icpustate *__restrict state, uintptr_t pc) {
	pc = (uintptr_t)instruction_trysucc((void const *)pc,
	                                    instrlen_isa_from_icpustate(state));
	icpustate_setpc(state, pc);
	RETHROW();
}


INTERN struct icpustate *FCALL
x86_handle_pagefault(struct icpustate *__restrict state, uintptr_t ecode) {
	STATIC_ASSERT(!IDT_CONFIG_ISTRAP(0x0e)); /* #PF  Page Fault */
#if (X86_PAGEFAULT_ECODE_USERSPACE == E_SEGFAULT_CONTEXT_USERCODE && \
     X86_PAGEFAULT_ECODE_WRITING == E_SEGFAULT_CONTEXT_WRITING)
#define GET_PF_CONTEXT_UW_BITS() (uintptr_t)(ecode & (X86_PAGEFAULT_ECODE_USERSPACE | X86_PAGEFAULT_ECODE_WRITING))
#else
#define GET_PF_CONTEXT_UW_BITS()                                                            \
	((uintptr_t)(ecode & X86_PAGEFAULT_ECODE_USERSPACE ? E_SEGFAULT_CONTEXT_USERCODE : 0) | \
	 (uintptr_t)(ecode & X86_PAGEFAULT_ECODE_WRITING ? E_SEGFAULT_CONTEXT_WRITING : 0))
#endif

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
	bool has_changed;
	/* Check for memcpy_nopf() */
	pc = state->ics_irregs.ir_pip;
	if unlikely_untraced(x86_nopf_check(pc)) {
		state->ics_irregs.ir_pip = x86_nopf_retof(pc);
		return state;
	}
	addr = __rdcr2();
	/* Re-enable interrupts if they were enabled before. */
	if (state->ics_irregs.ir_pflags & EFLAGS_IF)
		__sti();
	pageid   = PAGEID_ENCODE(addr);
	pageaddr = (void *)((uintptr_t)addr & ~PAGEMASK);
#if 0
	printk(KERN_DEBUG "Page fault at %p (page %p) [pc=%p,sp=%p] [ecode=%#x]\n",
	       (uintptr_t)addr, pageaddr, pc, icpustate_getsp(state));
#endif
	if ((ecode & (X86_PAGEFAULT_ECODE_PRESENT | X86_PAGEFAULT_ECODE_USERSPACE)) == 0 &&
	    pageid >= PAGEID_ENCODE(KERNELSPACE_BASE)) {
	    /* Check if a hint was defined for this page. */
		struct vm_node *hinted_node;
		if ((hinted_node = (struct vm_node *)pagedir_gethint(addr)) != NULL) {
			/* This is a hinted node (perform assertions on all
			 * of the requirements documented for such a node) */
			physpage_t ppage;
			uintptr_half_t pagedir_prot;
			assert(hinted_node->vn_flags & VM_NODE_FLAG_HINTED);
			assert(hinted_node->vn_prot & VM_PROT_SHARED);
			assert(hinted_node->vn_flags & VM_NODE_FLAG_PREPARED);
			assert(!(hinted_node->vn_flags & VM_NODE_FLAG_PARTITIONED));
			assert(hinted_node->vn_vm == &vm_kernel);
			assert(hinted_node->vn_part != NULL);
			assert(hinted_node->vn_block != NULL);
			assert(hinted_node->vn_fspath == NULL);
			assert(hinted_node->vn_fsname == NULL);
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
			pagedir_prot = hinted_node->vn_prot & (PAGEDIR_MAP_FEXEC | PAGEDIR_MAP_FREAD | PAGEDIR_MAP_FWRITE);
			/* Unset so we're able to track changes.
			 * NOTE: The actual tracking of changes isn't something that can be done atomically,
			 *       however atomic kernel pages do not impose any restrictions on use of change
			 *       tracking. */
			if ((hinted_node->vn_part->dp_flags & VM_DATAPART_FLAG_TRKCHNG) && !has_changed)
				pagedir_prot &= ~PAGEDIR_MAP_FWRITE;
			pagedir_mapone(pageaddr, physpage2addr(ppage), pagedir_prot);
			goto done;
		}
	}
	effective_vm = &vm_kernel;
	if (pageid < PAGEID_ENCODE(KERNELSPACE_BASE) || isuser()) {
#ifndef NDEBUG
		/* Special case: When the TLS segment contains an invalid pointer, us
		 *               trying to obtain THIS_VM at this point is just going
		 *               to result in a #DF:
		 *   #1: READ_FROM_BAD_POINTER(%tls:0)
		 *   #2: Trigger #PF at `%tls.base'
		 *   #3: When `%tls.base' points into user-space (e.g. is `NULL'), we get here again
		 *   #4: Repeat at step #1
		 * This then eventually results in a stack overflow that cannot be
		 * inspected properly, so when compiling for a debug-target, we use
		 * memcpy_nopf() to access the TLS segment. */
		struct task *mythread;
#ifdef __x86_64__
		mythread = (struct task *)__rdgsbaseq();
#else /* __x86_64__ */
		mythread = NULL;
		if likely(__rdfs() == SEGMENT_KERNEL_FSBASE) {
			struct desctab gdt;
			__sgdt(&gdt);
			if likely(gdt.dt_limit > SEGMENT_KERNEL_FSBASE) {
				struct segment *fsseg;
				fsseg    = (struct segment *)(gdt.dt_base + SEGMENT_KERNEL_FSBASE);
				mythread = (struct task *)segment_rdbaseX(fsseg);
			}
		}
#endif /* !__x86_64__ */
		if unlikely(memcpy_nopf(&effective_vm, &mythread->t_vm, sizeof(effective_vm)) != 0) {
			assertf(memcpy_nopf(&effective_vm, &mythread->t_vm, sizeof(effective_vm)) == 0,
			        "Corrupt TLS base pointer: mythread = %p", mythread);
			/* Allow the user to IGNORE the assertion check, in which case we'll
			 * try to repair the damage... */
			effective_vm = x86_repair_broken_tls_state()->t_vm;
		}
#else /* !NDEBUG */
		effective_vm = THIS_VM;
#endif /* NDEBUG */
	}
	{
		struct task_connections con;
		task_pushconnections(&con);
		TRY {
			struct vm_node *node;
			REF struct vm_datapart *part;
			uintptr_half_t node_prot;
			size_t node_vpage_offset; /* Offset (in vpages) of the accessed page from the start of `node' */
again_lookup_node:
#ifdef CONFIG_PHYS2VIRT_IDENTITY_MAXALLOC
			/* Access to the phys2virt section is allowed while preemption is disabled.
			 * However, when preemption is disabled, locking the kernel VM may fail,
			 * so we need a special-case check for access to the phys2virt section when
			 * we've previously failed to lock the kernel VM for reading. */
			if unlikely(!sync_tryread(effective_vm)) {
				if (effective_vm == &vm_kernel &&
				    (uintptr_t)addr >= KERNEL_PHYS2VIRT_MIN &&
				    (uintptr_t)addr <= KERNEL_PHYS2VIRT_MAX &&
				    !isuser()) {
					x86_phys2virt64_require(addr);
					goto done_before_pop_connections;
				}
				sync_read(effective_vm);
			}
#else /* CONFIG_PHYS2VIRT_IDENTITY_MAXALLOC */
			sync_read(effective_vm);
#endif /* !CONFIG_PHYS2VIRT_IDENTITY_MAXALLOC */
			assert(sync_reading(effective_vm));
			assert(!sync_writing(effective_vm));
			/* Lookup the node associated with the given page. */
			node = vm_getnodeofpageid(effective_vm, pageid);
			if unlikely(!node) {
				sync_endread(effective_vm);
				if (pageid >= PAGEID_ENCODE(KERNELSPACE_BASE)) {
					if (effective_vm != &vm_kernel && isuser()) {
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
				}
#if !defined(CONFIG_NO_USERKERN_SEGMENT) && defined(__x86_64__)
				else {
					/* We can get here if the calling program is running in compatibility
					 * mode, and has just attempted to perform a memory access/call to its
					 * ukern segment.
					 * NOTE: At this point we already know that `addr < KERNELSPACE_BASE',
					 *       and because any non-canonical CR2 would have instead caused
					 *       a GPF, we actually also know that `addr <= 0x0000ffffffffffff' */
					if (icpustate_getcs(state) == SEGMENT_USER_CODE32_RPL &&
					    addr >= (void *)(uintptr_t)COMPAT_KERNELSPACE_BASE &&
					    /* NOTE: The addr <= 32-bit is necessary since the hosted
					     *       application may have done something like `*(u32 *)0xffffffff = 0',
					     *       which would (among other addresses) have also accessed
					     *       memory beyond the 32-bit address space, and I'm not entirely
					     *       sure if a processor would wrap the pointer in this case...
					     * Also: There may be other ways for 32-bit programs to deref 64-bit
					     *       pointers that I can't think of right now. */
					    addr <= (void *)(uintptr_t)UINT32_C(0xffffffff)) {
						/* The access is of a 32-bit program trying to reach into
						 * what it ~thinks~ is the location of its kernel-space.
						 * -> Try to handle this case by re-sizing the `v_kernreserve'
						 *    to instead start at +3GiB, but only do so if there isn't
						 *    anything else mapped within that address range.
						 * Technically, it would be more correct if'd had already done
						 * this during the exec() that spawned the calling application,
						 * especially since prior to this being done, the application
						 * would have been able to map something else into the +3GiB...+4GiB
						 * address space range, however given that this is highly kos-specific
						 * behavior, I do think that doing this lazily should be ok (especially
						 * since a 32-bit program trying to map into +3GiB...+4GiB would already
						 * be doing something that it shouldn't, as attempting to map that area
						 * of memory is something that cannot be done when hosted by a 32-bit
						 * kernel) */
						sync_write(effective_vm);
						node = vm_getnodeofpageid(effective_vm, pageid);
						/* Re-check that there is no mapping at the accessed address. */
						if unlikely(node != NULL) {
							sync_downgrade(effective_vm);
							goto got_node_and_effective_vm_lock;
						}
						/* Make sure that `v_kernreserve' hasn't already been extended. */
						assert(effective_vm->v_kernreserve.vn_node.a_vmin == KERNELSPACE_MINPAGEID ||
						       effective_vm->v_kernreserve.vn_node.a_vmin == PAGEID_ENCODE(COMPAT_KERNELSPACE_BASE));
						if (effective_vm->v_kernreserve.vn_node.a_vmin == KERNELSPACE_MINPAGEID) {
							/* Make sure that the +3GiB...+4GiB region is currently unmapped. */
							if (!vm_isused(effective_vm,
							               (void *)(uintptr_t)COMPAT_KERNELSPACE_BASE,
							               ((uintptr_t)UINT64_C(0x100000000) -
							                (uintptr_t)COMPAT_KERNELSPACE_BASE))) {
								/* All right! Let's extend the `v_kernreserve' node! */
								printk(KERN_DEBUG "[x32] Extend v_kernreserve to include +3GiB...+4GiB\n");
								node = &effective_vm->v_kernreserve;
								assert(node->vn_vm == effective_vm);
#ifdef NDEBUG
								vm_node_remove(effective_vm, (void *)KERNELSPACE_BASE);
#else /* NDEBUG */
								{
									struct vm_node *removed_node;
									removed_node = vm_node_remove(effective_vm, (void *)KERNELSPACE_BASE);
									assert(removed_node == node);
								}
#endif /* !NDEBUG */
								node->vn_node.a_vmin = PAGEID_ENCODE(COMPAT_KERNELSPACE_BASE);
								node->vn_part  = &userkern_segment_part_compat;
								node->vn_block = &userkern_segment_block_compat;
								assert(node->vn_fspath == NULL);
								assert(node->vn_fsname == NULL);
								/* Re-insert the node and continue operating as if we'd found
								 * everything as it has been changed into from the get-go. */
								vm_node_insert(node);
								sync_downgrade(effective_vm);
								goto got_node_and_effective_vm_lock;
							}
						}
						sync_endwrite(effective_vm);
					}
				}
#endif /* !CONFIG_NO_USERKERN_SEGMENT && __x86_64__ */
				goto pop_connections_and_throw_segfault;
			}
#if !defined(CONFIG_NO_USERKERN_SEGMENT) && defined(__x86_64__)
got_node_and_effective_vm_lock:
#endif /* !CONFIG_NO_USERKERN_SEGMENT && __x86_64__ */
			if unlikely(!node->vn_part) {
				struct cpu *mycpu;
				sync_endread(effective_vm);
#ifdef CONFIG_PHYS2VIRT_IDENTITY_MAXALLOC
				/* Check for special case: `node' belongs to the physical identity area. */
				if (node == &x86_phys2virt64_node) {
					x86_phys2virt64_require(addr);
					goto done_before_pop_connections;
				}
#endif /* CONFIG_PHYS2VIRT_IDENTITY_MAXALLOC */

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
						allow_preemption = icpustate_getpreemption(state);
						/* Make special checks if the access itself seems to
						 * originate from a direct user-space access. */
						if (isuser()) {
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
						if (!handle_iob_access(mycpu,
						                       (ecode & X86_PAGEFAULT_ECODE_WRITING) != 0,
						                       allow_preemption)) {
							assert(PREEMPTION_ENABLED());
							goto again_lookup_node;
						}
						if (allow_preemption)
							__sti();
						goto done_before_pop_connections;
					}
					IF_SMP(if (icpustate_getpreemption(state)) __sti());
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
					if (!icpustate_getpreemption(state))
						goto pop_connections_and_throw_segfault;
					/* I/O access from kernel-space wouldn't result in an IOB check, so
					 * if the access comes from kernel-space, then this is the calling
					 * thread incorrectly accessing some other cpu's IOB. */
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
			part              = incref(node->vn_part);
			node_prot         = node->vn_prot;
			node_vpage_offset = (size_t)(pageid - vm_node_getminpageid(node));
			assert(vm_node_getpagecount(node) == vm_datapart_numvpages(part));
			has_changed = ecode & X86_PAGEFAULT_ECODE_WRITING;
			/* Acquire a lock to the affected data part. */
			TRY {
				physpage_t ppage;
				uintptr_half_t pagedir_prot;
				/* Need at least a read-lock for part initialization */
#ifdef LIBVIO_CONFIG_ENABLED
				if (part->dp_state == VM_DATAPART_STATE_VIOPRT) {
					struct vio_emulate_args args;
					COMPILER_READ_BARRIER();
					sync_endread(effective_vm);
					/* VIO Emulation */
					sync_read(part);
					args.vea_args.va_block        = incref(part->dp_block);
					args.vea_args.va_acmap_offset = ((pos_t)(node_vpage_offset + vm_datapart_mindpage(part))
					                                 << VM_DATABLOCK_ADDRSHIFT(args.vea_args.va_block));
					sync_endread(part);
					args.vea_args.va_ops = args.vea_args.va_block->db_vio;
					if unlikely(!args.vea_args.va_ops) {
						decref_unlikely(args.vea_args.va_block);
						decref_unlikely(part);
						goto pop_connections_and_throw_segfault;
					}
					args.vea_args.va_part       = part; /* Inherit reference */
					args.vea_args.va_acmap_page = (void *)FLOOR_ALIGN((uintptr_t)addr, PAGESIZE);
					/* Check for special case: call into VIO memory */
					if (args.vea_args.va_ops->vo_call && (uintptr_t)addr == pc) {
						/* Make sure that memory mapping has execute permissions! */
						if unlikely(!(node_prot & VM_PROT_EXEC)) {
							PERTASK_SET(this_exception_code, ERROR_CODEOF(E_SEGFAULT_NOTEXECUTABLE));
							PERTASK_SET(this_exception_pointers[1],
							            (uintptr_t)(E_SEGFAULT_CONTEXT_FAULT | E_SEGFAULT_CONTEXT_EXEC |
							                        E_SEGFAULT_CONTEXT_VIO | GET_PF_CONTEXT_UW_BITS()));
cleanup_vio_and_pop_connections_and_set_exception_pointers2:
							decref_unlikely(args.vea_args.va_block);
							assert(args.vea_args.va_part == part);
							decref_unlikely(args.vea_args.va_part);
							goto pop_connections_and_set_exception_pointers2;
						}
						/* Special case: call into VIO memory */
						TRY {
							vio_addr_t vio_addr;
							uintptr_t callsite_pc;
							uintptr_t sp;
#ifdef __x86_64__
							bool is_compat;
#endif /* __x86_64__ */
							/* Must unwind the stack to restore the IP of the VIO call-site. */
							sp = icpustate_getsp(state);
							if (sp >= KERNELSPACE_BASE && isuser())
								goto do_normal_vio; /* Validate the stack-pointer for user-space. */
#ifdef __x86_64__
							is_compat = icpustate_is32bit(state);
#endif /* __x86_64__ */
							TRY {
#ifdef __x86_64__
								if (is_compat) {
									callsite_pc = (uintptr_t)*(u32 *)sp;
								} else
#endif /* __x86_64__ */
								{
									callsite_pc = *(uintptr_t *)sp;
								}
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
							icpustate_setsp(state, is_compat ? sp + 4 : sp + 8);
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
							vio_addr = args.vea_args.va_acmap_offset +
							           ((uintptr_t)addr - (uintptr_t)args.vea_args.va_acmap_page);
							/* Invoke the VIO call operator. */
							args.vea_args.va_state = state;
							(*args.vea_args.va_ops->vo_call)(&args.vea_args, vio_addr);
							state = args.vea_args.va_state;
						} EXCEPT {
							/* Ensure that a the VIO flag is set if necessary */
							if (was_thrown(E_SEGFAULT)) {
								void *faultaddr = (void *)PERTASK_GET(this_exception_pointers[0]);
								if (faultaddr == addr) {
									uintptr_t flags;
									flags = PERTASK_GET(this_exception_pointers[1]);
									flags |= E_SEGFAULT_CONTEXT_VIO;
									PERTASK_SET(this_exception_pointers[1], flags);
								}
							}
							decref_unlikely(args.vea_args.va_block);
							assert(args.vea_args.va_part == part);
							/* Directly unwind the exception, since we've got a custom return-pc set-up.
							 * If we did a normal RETHROW() here, then the (currently correct) return PC
							 * would get overwritten with the VIO function address. */
							decref_unlikely(args.vea_args.va_part);
							task_popconnections(&con);
							if (isuser())
								PERTASK_SET(this_exception_faultaddr, (void *)icpustate_getpc(state));
							x86_userexcept_unwind_interrupt(state);
						}
						assert(args.vea_args.va_part == part);
						decref_unlikely(args.vea_args.va_block);
						decref_unlikely(args.vea_args.va_part);
						task_popconnections(&con);
						return state;
					}
do_normal_vio:
					/* Make sure that the segment was mapped with the proper protection */
					if unlikely((ecode & X86_PAGEFAULT_ECODE_WRITING)
					            ? !(node_prot & VM_PROT_WRITE)   /* Write to read-only VIO segment */
					            : !(node_prot & VM_PROT_READ)) { /* Read from non-readable VIO segment */
						PERTASK_SET(this_exception_code, (ecode & X86_PAGEFAULT_ECODE_WRITING)
						                                 ? ERROR_CODEOF(E_SEGFAULT_READONLY)
						                                 : ERROR_CODEOF(E_SEGFAULT_NOTREADABLE));
						PERTASK_SET(this_exception_pointers[1],
						            (uintptr_t)(E_SEGFAULT_CONTEXT_FAULT | E_SEGFAULT_CONTEXT_EXEC |
						                        E_SEGFAULT_CONTEXT_VIO | GET_PF_CONTEXT_UW_BITS()));
						goto cleanup_vio_and_pop_connections_and_set_exception_pointers2;
					}
					args.vea_args.va_state = state;
					/* Determine the address range for which memory access should be virtualized
					 * by looking at the lower/upper bound of the accessed VM node. - Any memory
					 * access within this range will be dispatched via VIO. */
					args.vea_ptrlo = (byte_t *)pageaddr - node_vpage_offset * PAGESIZE;
					args.vea_ptrhi = (byte_t *)args.vea_ptrlo + vm_datapart_numvpages(part) * PAGESIZE - 1;
					args.vea_addr  = vio_args_vioaddr(&args.vea_args, args.vea_ptrlo);
					TRY {
						/* Emulate the current instruction. */
						viocore_emulate(&args);
					} EXCEPT {
						decref_unlikely(args.vea_args.va_block);
						assert(args.vea_args.va_part == part);
						/*decref_unlikely(args.vea_args.va_part);*/ /* Handled by outer EXCEPT */
						/*task_popconnections(&con);*/ /* Handled by outer EXCEPT */
						RETHROW();
					}
					decref_unlikely(args.vea_args.va_block);
					assert(args.vea_args.va_part == part);
					decref_unlikely(args.vea_args.va_part);
					task_popconnections(&con);
#ifndef __x86_64__
					/* Check if the kernel %esp or %ss was modified */
					if unlikely(args.vea_kernel_override & (VIO_EMULATE_ARGS_386_KERNEL_ESP_VALID |
					                                        VIO_EMULATE_ARGS_386_KERNEL_SS_VALID)) {
						u32 real_esp = args.vea_kernel_esp_override;
						u16 real_ss  = args.vea_kernel_ss_override;
						u32 *regload_area;
						assert(!isuser());
						if (!(args.vea_kernel_override & VIO_EMULATE_ARGS_386_KERNEL_SS_VALID))
							real_ss = icpustate32_getkernelss(args.vea_args.va_state);
						if (!(args.vea_kernel_override & VIO_EMULATE_ARGS_386_KERNEL_ESP_VALID))
							real_esp = icpustate32_getkernelesp(args.vea_args.va_state);
						regload_area = (u32 *)vm_node_getstart(THIS_KERNEL_STACK);
						/* Fill in the register save area to match what's going to
						 * get loaded by `x86_vio_kernel_esp_bootstrap_loader()' */
						regload_area[0] = real_ss;
						regload_area[1] = real_esp;
						regload_area[2] = args.vea_args.va_state->ics_irregs_k.ir_eip;
						regload_area[3] = args.vea_args.va_state->ics_gpregs.gp_eax;
						/* Have `%eax' point to the register save area */
						args.vea_args.va_state->ics_gpregs.gp_eax = (u32)regload_area;
						/* Have the icpustate return to the bootstrap function */
						args.vea_args.va_state->ics_irregs_k.ir_eip = (u32)x86_vio_kernel_esp_bootstrap_loader;
					}
#endif /* !__x86_64__ */
					return args.vea_args.va_state;
				}
#endif /* LIBVIO_CONFIG_ENABLED */
				sync_endread(effective_vm);
				/* Make sure the desired user-space access is actually allowed! */
				if unlikely(!(node_prot & VM_PROT_EXEC) &&
				            ((ecode & X86_PAGEFAULT_ECODE_INSTRFETCH) || (uintptr_t)addr == pc)) {
					/* Non-executable memory */
					PERTASK_SET(this_exception_code, ERROR_CODEOF(E_SEGFAULT_NOTEXECUTABLE));
decref_part_and_pop_connections_and_set_exception_pointers:
					decref_unlikely(part);
					goto pop_connections_and_set_exception_pointers;
				}
				if (has_changed) {
					bool did_unshare;
					if unlikely(!(node_prot & VM_PROT_WRITE)) {
						/* Read-only memory */
						PERTASK_SET(this_exception_code, ERROR_CODEOF(E_SEGFAULT_READONLY));
						goto decref_part_and_pop_connections_and_set_exception_pointers;
					}
					did_unshare = false;
					/* Lock and unshare the datapart being written to. */
					if (!vm_lock_and_unshare_datapart_for_writing(effective_vm,
					                                              &part,
					                                              addr,
					                                              node,
					                                              node_prot,
					                                              node_vpage_offset,
					                                              1,
					                                              &did_unshare)) {
						/* Race condition... (try again) */
						decref_unlikely(part);
						goto again_lookup_node;
					}
					/* In case an unshare did actually happen, `vm_lock_and_unshare_datapart_for_writing()'
					 * will have already performed the necessary page directory re-mapping, so we're already
					 * done. */
					if (did_unshare) {
						sync_endread(part);
						vm_datapart_decref_and_merge(part);
						goto done_before_pop_connections;
					}
				} else {
					if unlikely(!(node_prot & VM_PROT_READ)) {
						/* Write-only memory */
						PERTASK_SET(this_exception_code, ERROR_CODEOF(E_SEGFAULT_NOTREADABLE));
						goto decref_part_and_pop_connections_and_set_exception_pointers;
					}
					vm_datapart_lockread_setcore(part);
					/* Check if the part still includes the accessed page.
					 * This is required to ensure that `vm_datapart_loadpage()'
					 * can be called safely (the part may have been split between
					 * the time of us acquiring a read-lock to it, and the point
					 * when we released our write-lock to the effected VM) */
					if unlikely(node_vpage_offset >= vm_datapart_numvpages(part)) {
						sync_endread(part);
						decref_unlikely(part);
						goto again_lookup_node;
					}
				}
				assert(sync_reading(part));
				assert(part->dp_state != VM_DATAPART_STATE_ABSENT);
				assert(node_vpage_offset < vm_datapart_numvpages(part));
				COMPILER_BARRIER();

				/* Load the affected page into the core. */
				TRY {
					ppage = vm_datapart_loadpage(part,
					                             node_vpage_offset,
					                             &has_changed);
				} EXCEPT {
					sync_endread(part);
					RETHROW();
				}

				/* Re-acquire a lock to the VM, so we can map the affected page. */
				if (!sync_trywrite(effective_vm)) {
					sync_endread(part);
					/* Wait until it becomes possible to write to `effective_vm' */
					while (!sync_canwrite(effective_vm))
						task_yield();
					decref_unlikely(part);
					goto again_lookup_node;
				}

				/* Check to ensure that the mapped target hasn't changed
				 * while we were loading the affected page into the core. */
				if unlikely(vm_getnodeofpageid(effective_vm, pageid) != node ||
				            node->vn_part != part || node->vn_prot != node_prot) {
					sync_endread(part);
					sync_endwrite(effective_vm);
					decref_unlikely(part);
					printk(KERN_DEBUG "Race condition: Mapping target at %p has changed\n",
					       pageaddr);
					goto again_lookup_node;
				}

				/* Map the affected page, overriding the mapping hint that originally got us here. */
				pagedir_prot = node_prot & (PAGEDIR_MAP_FEXEC | PAGEDIR_MAP_FREAD | PAGEDIR_MAP_FWRITE);

				/* Unset so we're able to track changes.
				 * NOTE: The actual tracking of changes isn't something that can be done atomically,
				 *       however atomic kernel pages do not impose any restrictions on use of change
				 *       tracking. */
				if (node->vn_part->dp_flags & VM_DATAPART_FLAG_TRKCHNG && !has_changed)
					pagedir_prot &= ~PAGEDIR_MAP_FWRITE;
				else if ((pagedir_prot & PAGEDIR_MAP_FWRITE) && !(ecode & X86_PAGEFAULT_ECODE_WRITING)) {
					/* When `X86_PAGEFAULT_ECODE_WRITING' wasn't set, we didn't actually unshare the part, so if
					 * we're mapping it with write permissions, we must delete those in case of a PRIVATE
					 * memory mapping when the part isn't anonymous, or mapped by other SHARED or PRIVATE
					 * mappings. */
					if (!(node_prot & VM_PROT_SHARED) &&
					    (ATOMIC_READ(part->dp_block->db_parts) != VM_DATABLOCK_ANONPARTS ||
					     part->dp_srefs != NULL || part->dp_crefs != node ||
					     node->vn_link.ln_next != NULL))
						pagedir_prot &= ~PAGEDIR_MAP_FWRITE;
				}
				if (effective_vm != &vm_kernel)
					pagedir_prot |= PAGEDIR_MAP_FUSER;
				/* If the node isn't prepared, make sure that we can map memory. */
				if (!(node->vn_flags & VM_NODE_FLAG_PREPARED)) {
					if unlikely(!pagedir_prepare_mapone(pageaddr)) {
						sync_endwrite(effective_vm);
						sync_endread(part);
						THROW(E_BADALLOC_INSUFFICIENT_PHYSICAL_MEMORY, PAGESIZE);
					}
				}
				/* Actually map the accessed page! */
				pagedir_mapone(pageaddr, physpage2addr(ppage), pagedir_prot);

				/* Make sure that the performed access can now succeed */
				assertf(ecode & X86_PAGEFAULT_ECODE_WRITING
				        ? (pagedir_prot & PAGEDIR_MAP_FUSER
				           ? pagedir_isuserwritable(addr)
				           : pagedir_iswritable(addr))
				        : (pagedir_prot & PAGEDIR_MAP_FUSER
				           ? pagedir_isuseraccessible(addr)
				           : pagedir_ismapped(addr)),
				        "ecode         = %p\n"
				        "prot          = %p\n"
				        "node->vn_prot = %p\n"
				        "addr          = %p (page %p)\n"
				        "phys          = %" PRIpN(__SIZEOF_PHYSADDR_T__) " (page %" PRIpN(__SIZEOF_PHYSPAGE_T__) ")\n"
				        "effective_vm  = %p\n"
				        "has_changed   = %u\n",
				        (uintptr_t)ecode,
				        (uintptr_t)pagedir_prot,
				        (uintptr_t)node->vn_prot,
				        (uintptr_t)addr,
				        (uintptr_t)pageaddr,
				        (physaddr_t)physpage2addr(ppage),
				        (physpage_t)ppage,
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
			rethrow_exception_from_pf_handler(state, pc);
		}
		task_popconnections(&con);
		__IF0 {
pop_connections_and_throw_segfault:
			task_popconnections(&con);
			goto throw_segfault;
pop_connections_and_set_exception_pointers:
			task_popconnections(&con);
			goto set_exception_pointers;
pop_connections_and_set_exception_pointers2:
			task_popconnections(&con);
			goto set_exception_pointers2;
		}
	}
done:
	pagedir_syncone(addr);
	/*pagedir_syncall();*/
	return state;
throw_segfault:
	if (pc == (uintptr_t)addr) {
		/* This can happen when trying to call an invalid function pointer.
		 * -> Try to unwind this happening. */
#ifdef __x86_64__
		bool is_compat;
#endif /* __x86_64__ */
		uintptr_t callsite_pc;
		uintptr_t sp = icpustate_getsp(state);
		if (sp >= KERNELSPACE_BASE && (sp != (uintptr_t)(&state->ics_irregs + 1) || isuser()))
			goto not_a_badcall;
#ifdef __x86_64__
		is_compat = icpustate_is32bit(state);
#endif /* __x86_64__ */
		TRY {
#ifdef __x86_64__
			if (is_compat) {
				callsite_pc = (uintptr_t)*(u32 *)sp;
			} else
#endif /* __x86_64__ */
			{
				callsite_pc = *(uintptr_t *)sp;
			}
		} EXCEPT {
			if (!was_thrown(E_SEGFAULT)) {
				if (isuser())
					PERTASK_SET(this_exception_faultaddr, (void *)pc);
				rethrow_exception_from_pf_handler(state, pc);
			}
			goto not_a_badcall;
		}
#ifdef __x86_64__
		if (isuser() ? (callsite_pc >= USERSPACE_END)
		             : (callsite_pc < KERNELSPACE_BASE))
			goto not_a_badcall;
		icpustate_setpc(state, callsite_pc);
		icpustate_setsp(state, is_compat ? sp + 4 : sp + 8);
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
			call_instr = instruction_pred_nx((void *)callsite_pc,
			                                 instrlen_isa_from_icpustate(state));
			if likely(call_instr)
				callsite_pc = (uintptr_t)call_instr;
		} EXCEPT {
			if (!was_thrown(E_SEGFAULT)) {
				if (isuser())
					PERTASK_SET(this_exception_faultaddr, (void *)pc);
				rethrow_exception_from_pf_handler(state, pc);
			}
			/* Discard read-from-callsite_pc exception... */
		}
		PERTASK_SET(this_exception_faultaddr, (void *)callsite_pc);
		PERTASK_SET(this_exception_code, (ecode & X86_PAGEFAULT_ECODE_PRESENT)
		                                 ? ERROR_CODEOF(E_SEGFAULT_NOTEXECUTABLE)
		                                 : ERROR_CODEOF(E_SEGFAULT_UNMAPPED));
		PERTASK_SET(this_exception_pointers[0], (uintptr_t)addr);
		PERTASK_SET(this_exception_pointers[1],
		            (uintptr_t)(E_SEGFAULT_CONTEXT_FAULT |
		                        E_SEGFAULT_CONTEXT_EXEC |
		                        GET_PF_CONTEXT_UW_BITS()));
		{
			unsigned int i;
			for (i = 2; i < EXCEPTION_DATA_POINTERS; ++i)
				PERTASK_SET(this_exception_pointers[i], (uintptr_t)0);
		}
		printk(KERN_DEBUG "[segfault] PC-Fault at %p (page %p) [pc=%p,%p] [ecode=%#x]\n",
		       addr, pageaddr, callsite_pc, icpustate_getpc(state), ecode);
		goto do_unwind_state;
	}
not_a_badcall:
	if ((ecode & (X86_PAGEFAULT_ECODE_PRESENT | X86_PAGEFAULT_ECODE_WRITING)) ==
	    /*    */ (X86_PAGEFAULT_ECODE_PRESENT | X86_PAGEFAULT_ECODE_WRITING)) {
		PERTASK_SET(this_exception_code, ERROR_CODEOF(E_SEGFAULT_READONLY));
	} else if ((ecode & X86_PAGEFAULT_ECODE_PRESENT) && ((ecode & X86_PAGEFAULT_ECODE_INSTRFETCH) ||
	                                                     (pc == (uintptr_t)addr))) {
		PERTASK_SET(this_exception_code, ERROR_CODEOF(E_SEGFAULT_NOTEXECUTABLE));
	} else {
		PERTASK_SET(this_exception_code, ERROR_CODEOF(E_SEGFAULT_UNMAPPED));
	}
set_exception_pointers:
	PERTASK_SET(this_exception_pointers[1],
	            (uintptr_t)(E_SEGFAULT_CONTEXT_FAULT |
	                        ((ecode & X86_PAGEFAULT_ECODE_INSTRFETCH) ||
	                         (pc == (uintptr_t)addr)
	                         ? E_SEGFAULT_CONTEXT_EXEC
	                         : 0) |
	                        GET_PF_CONTEXT_UW_BITS()));
set_exception_pointers2:
	PERTASK_SET(this_exception_pointers[0], (uintptr_t)addr);
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
	pc = (uintptr_t)instruction_trysucc((void const *)pc, instrlen_isa_from_icpustate(state));
	printk(KERN_DEBUG "[segfault] Fault at %p (page %p) [pc=%p,%p] [ecode=%#x]\n",
	       addr, pageaddr, icpustate_getpc(state), pc, ecode);
	icpustate_setpc(state, pc);
do_unwind_state:
	/* Try to trigger a debugger trap (if enabled) */
	if (kernel_debugtrap_enabled() && (kernel_debugtrap_on & KERNEL_DEBUGTRAP_ON_SEGFAULT))
		state = kernel_debugtrap_r(state, SIGSEGV);
	x86_userexcept_unwind_interrupt(state);
#undef isuser
#undef GET_PF_CONTEXT_UW_BITS
}

DECL_END

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_FAULT_HANDLE_PAGEFAULT_C */
