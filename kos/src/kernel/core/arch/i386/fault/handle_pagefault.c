/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_CORE_ARCH_I386_FAULT_HANDLE_PAGEFAULT_C
#define GUARD_KERNEL_CORE_ARCH_I386_FAULT_HANDLE_PAGEFAULT_C 1
#define _KOS_SOURCE 1

/* TODO: This entire file needs a clean re-write. (possibly even as part of portable code)
 * Also: VIO emulation needs to be able to run under ABNORMAL_RETURN in order to
 *       be  able to emulate  system calls under the  new syscall restart model! */

#include <kernel/compiler.h>

#include <debugger/rt.h>
#include <kernel/debugtrap.h>
#include <kernel/except.h>
#include <kernel/malloc.h>
#include <kernel/memory.h>
#include <kernel/mman.h>
#include <kernel/mman/fault.h>
#include <kernel/mman/mfile.h>
#include <kernel/mman/mnode.h>
#include <kernel/mman/mpart.h>
#include <kernel/mman/phys.h>
#include <kernel/mman/sync.h>
#include <kernel/paging.h>
#include <kernel/printk.h>
#include <kernel/rt/except-handler.h>
#include <kernel/x86/fault.h>
#include <kernel/x86/idt.h> /* IDT_CONFIG_ISTRAP() */
#include <kernel/x86/nopf.h>
#include <kernel/x86/phys2virt64.h>
#include <sched/cpu.h>
#include <sched/group.h>
#include <sched/task.h>
#include <sched/userkern.h> /* CONFIG_NO_KERNEL_USERKERN_SEGMENT */
#include <sched/x86/iobm.h>
#include <sched/x86/tss.h>

#include <hybrid/align.h>

#include <asm/cpu-flags.h>
#include <asm/intrin.h>
#include <kos/kernel/cpu-state-compat.h>
#include <kos/kernel/cpu-state-helpers.h>
#include <kos/kernel/cpu-state.h>
#include <kos/kernel/x86/segment.h>
#include <kos/nopf.h>

#include <assert.h>
#include <atomic.h>
#include <inttypes.h>
#include <signal.h>
#include <stdint.h>
#include <string.h>

#include <libinstrlen/instrlen.h>
#include <libvio/access.h>
#include <libviocore/viocore.h>
#ifndef __x86_64__
#include <cfi.h>
#endif /* !__x86_64__ */


#ifdef __x86_64__
#define IF_X32(...) /* nothing */
#define IF_X64(...) __VA_ARGS__
#else /* __x86_64__ */
#define IF_X32(...) __VA_ARGS__
#define IF_X64(...) /* nothing */
#endif /* !__x86_64__ */


/* NOTE: This #PF handler is also used while in debugger mode. And here's why:
 *
 * Use the normal #PF handler in debugger mode.
 *
 * This one's kind-of a departure from the original intend that the debugger
 * mode  should be as disconnected from the  rest of the system as possible.
 * However I've been running  into a couple of  problems related to how  the
 * kernel heap uses lazy mappings to speed up memory allocations outside  of
 * GFP_PREFLT and GFP_LOCKED, where any  piece of heap memory not  allocated
 * with one of these flags  may cause the kernel  to panic if accessed  from
 * within  debug mode,  since the  debugger's old  #PF handler intentionally
 * refused to handle this kind of mapping.
 * The design flaw in this is  that many places, such as  `driver_section_lock()'
 * will make use of  regular, old heap  memory that falls  under the category  of
 * the  above, meaning that whenever the debugger was accessing debug information
 * of dynamically loaded drivers, there was a chance that it was accessing memory
 * which it was unable to properly initialize.
 *
 * I've debated how to go about fixing this design flaw, and considered  adding
 * a global variable `bool dbg_restricted_memory' that could be used to  toggle
 * which kind of  #PF handler should  get used.  But then I'd  probably had  to
 * configure it to  not restrict  memory by default  since there  are just  soo
 * many places that you wouldn't even think about needing normal #PF  handling.
 * So with that in mind,  such a flag would have  only ever been enabled  while
 * doing some kind of dangerous  memory access while in debugger-mode.  However
 * with the current  API, such  memory access shouldn't  be performed  directly
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
 *   %ss  = *(u32 const *)(%eax + 0);
 *   %esp = *(u32 const *)(%eax + 4);
 *   %eip = *(u32 const *)(%eax + 8);
 *   %eax = *(u32 const *)(%eax + 12);
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


/* @return: true:  Success
 * @return: false: Must try again (preemption had to be enabled) */
PRIVATE NOPREEMPT NONNULL((1)) bool FCALL
handle_iob_access(struct cpu *__restrict me,
                  bool is_writing,
                  bool allow_preemption) {
#define GET_GFP_FLAGS()                           \
	(allow_preemption ? (GFP_LOCKED | GFP_PREFLT) \
	                  : (GFP_LOCKED | GFP_PREFLT | GFP_ATOMIC))
	struct ioperm_bitmap *iob;
	assert(!PREEMPTION_ENABLED());
	iob = THIS_X86_IOPERM_BITMAP;
	if (!iob) {
		assertf(atomic_read(&FORCPU(me, thiscpu_x86_ioperm_bitmap)) == NULL,
		        "FORCPU(me, thiscpu_x86_ioperm_bitmap) = %p",
		        atomic_read(&FORCPU(me, thiscpu_x86_ioperm_bitmap)));
		if (is_writing) {
			iob = ioperm_bitmap_allocf_nx(GET_GFP_FLAGS());
			if unlikely(!iob) {
				if (!allow_preemption)
					THROW(E_WOULDBLOCK_PREEMPTED);
				/* Re-attempt the allocation with preemption enabled. */
				PREEMPTION_ENABLE();
				iob = ioperm_bitmap_allocf(GFP_LOCKED | GFP_PREFLT);
				assertf(atomic_read(&FORCPU(me, thiscpu_x86_ioperm_bitmap)) == NULL,
				        "FORCPU(me, thiscpu_x86_ioperm_bitmap) = %p",
				        atomic_read(&FORCPU(me, thiscpu_x86_ioperm_bitmap)));
				PERTASK_SET(this_x86_ioperm_bitmap, iob);
				return false;
			}
		} else {
			iob = incref(&ioperm_bitmap_empty);
			atomic_inc(&iob->ib_share);
		}
		/* NOTE: The following line  causes an inconsistency  that is fixed  by
		 *       assigning `FORCPU(me, thiscpu_x86_ioperm_bitmap) = iob' below.
		 *       Because   preemption  is  currently  off,  this  inconsistency
		 *       never becomes visible outside of this function. */
		PERTASK_SET(this_x86_ioperm_bitmap, iob);
	} else if (is_writing && atomic_read(&iob->ib_share) > 1) {
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
			 * This  must   be  done   to  ensure   that  the   assumption:
			 *     FORCPU(me, thiscpu_x86_ioperm_bitmap) == NULL ||
			 *     FORCPU(me, thiscpu_x86_ioperm_bitmap) == THIS_X86_IOPERM_BITMAP
			 * continues to be consistent.
			 */
			assertf(THIS_X86_IOPERM_BITMAP == iob,
			        "THIS_X86_IOPERM_BITMAP = %p\n"
			        "iob                    = %p",
			        THIS_X86_IOPERM_BITMAP, iob);
			if (atomic_read(&FORCPU(me, thiscpu_x86_ioperm_bitmap)) == iob) {
				PREEMPTION_DISABLE();
				COMPILER_READ_BARRIER();
				if (FORCPU(me, thiscpu_x86_ioperm_bitmap) == iob) {
					pagedir_unmap(FORCPU(me, thiscpu_x86_iob), 2 * PAGESIZE);
					pagedir_sync(FORCPU(me, thiscpu_x86_iob), 2 * PAGESIZE);
					FORCPU(me, thiscpu_x86_ioperm_bitmap) = NULL;
				}
				PREEMPTION_ENABLE();
			} else {
				assertf(atomic_read(&FORCPU(me, thiscpu_x86_ioperm_bitmap)) == NULL,
				        "FORCPU(me, thiscpu_x86_ioperm_bitmap) = %p",
				        atomic_read(&FORCPU(me, thiscpu_x86_ioperm_bitmap)));
			}
			PERTASK_SET(this_x86_ioperm_bitmap, cow);
			atomic_dec(&iob->ib_share);
			decref(iob);
			return false;
		}
		/* NOTE: The following line  causes an inconsistency  that is fixed  by
		 *       assigning `FORCPU(me, thiscpu_x86_ioperm_bitmap) = iob' below.
		 *       Because   preemption  is  currently  off,  this  inconsistency
		 *       never becomes visible outside of this function. */
		PERTASK_SET(this_x86_ioperm_bitmap, cow);
		atomic_dec(&iob->ib_share);
		decref(iob);
		iob = cow;
	}
	pagedir_map(FORCPU(me, thiscpu_x86_iob),
	            2 * PAGESIZE,
	            iob->ib_pages,
	            is_writing ? (PAGEDIR_PROT_READ | PAGEDIR_PROT_WRITE)
	                       : (PAGEDIR_PROT_READ));
	FORCPU(me, thiscpu_x86_ioperm_bitmap) = iob;
#undef GET_GFP_FLAGS
	return true;
}


#ifndef CONFIG_NO_SMP
/* Check if the given `node' is the IOB vector of some CPU */
PRIVATE NOBLOCK ATTR_CONST WUNUSED bool
NOTHROW(FCALL is_iob_mnode)(struct mnode *node) {
	unsigned int i;
	for (i = 0; i < cpu_count; ++i) {
		if (node == &FORCPU(cpu_vector[i], thiscpu_x86_iobnode))
			return true;
	}
	return false;
}

/* Check if `*pc' points to some I/O instruction that doesn't
 * perform   a   read  or   write  access   to  `fault_addr'. */
PRIVATE WUNUSED bool FCALL
is_io_instruction_and_not_memory_access(byte_t const *pc,
                                        struct icpustate *state,
                                        uintptr_t fault_addr) {
	byte_t opcode;
	bool result = true;
	unsigned int pfx66;
	COMPILER_BARRIER();
#ifdef __x86_64__
	pfx66 = 0;
#else /* __x86_64__ */
#ifdef __I386_NO_VM86
	pfx66 = 0;
#else /* __I386_NO_VM86 */
	pfx66 = (icpustate_getpflags(state) & EFLAGS_VM) ? 1 : 0;
#endif /* !__I386_NO_VM86 */
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
#define is_iob_mnode(node) ((node) == &FORCPU(&bootcpu, thiscpu_x86_iobnode))
#endif /* CONFIG_NO_SMP */


#ifndef NDEBUG
INTDEF NOBLOCK ATTR_RETNONNULL struct task *
NOTHROW(KCALL x86_repair_broken_tls_state)(void);
#endif /* !NDEBUG */





PRIVATE ATTR_NORETURN void FCALL
rethrow_exception_from_pf_handler(struct icpustate *__restrict state, void const *pc)
		THROWS(...) {
	/* Use the regular `instruction_trysucc()' since we're actually inside
	 * of a CATCH-block right now, meaning that it will already do all  of
	 * the necessary work of preserving the old exception for us! */
	pc = instruction_trysucc(pc, icpustate_getisa(state));
	icpustate_setpc(state, pc);
	RETHROW();
}


INTERN ABNORMAL_RETURN ATTR_RETNONNULL WUNUSED NONNULL((1)) struct icpustate *FCALL
x86_handle_pagefault(struct icpustate *__restrict state,
                     uintptr_t ecode, void *addr) {
	static_assert(!IDT_CONFIG_ISTRAP(0x0e)); /* #PF  Page Fault */
#if 1
#define FAULT_IS_USER ((ecode & X86_PAGEFAULT_ECODE_USERSPACE) != 0)
#else
#define FAULT_IS_USER icpustate_isuser(state)
#endif
#define FAULT_IS_WRITE ((ecode & X86_PAGEFAULT_ECODE_WRITING) != 0)
#if (X86_PAGEFAULT_ECODE_USERSPACE == E_SEGFAULT_CONTEXT_USERCODE && \
     X86_PAGEFAULT_ECODE_WRITING == E_SEGFAULT_CONTEXT_WRITING)
#define GET_PF_CONTEXT_UW_BITS() (uintptr_t)(ecode & (X86_PAGEFAULT_ECODE_USERSPACE | X86_PAGEFAULT_ECODE_WRITING))
#else
#define GET_PF_CONTEXT_UW_BITS()                                                            \
	((uintptr_t)(ecode & X86_PAGEFAULT_ECODE_USERSPACE ? E_SEGFAULT_CONTEXT_USERCODE : 0) | \
	 (uintptr_t)(ecode & X86_PAGEFAULT_ECODE_WRITING ? E_SEGFAULT_CONTEXT_WRITING : 0))
#endif
	void const *pc;
	struct mfault mf;
	struct task_connections con;

	/* Check for memcpy_nopf() */
	pc = (void const *)state->ics_irregs.ir_Pip;
	if unlikely_untraced(x86_nopf_check(pc)) {
		state->ics_irregs.ir_Pip = (uintptr_t)x86_nopf_retof(pc);
		return state;
	}

	/* Load the address of the faulting page. */
	mf.mfl_addr = (void *)((uintptr_t)addr & ~PAGEMASK);

#if 0
	printk(KERN_DEBUG "Page fault at %p (page %p) [pc=%p,sp=%p] [ecode=%#" PRIxPTR "]\n",
	       (uintptr_t)addr, mf.mfl_addr, pc, icpustate_getsp(state), ecode);
#endif

	/* Check if a hint was defined for this page. */
	if ((ecode & (X86_PAGEFAULT_ECODE_PRESENT |
	              X86_PAGEFAULT_ECODE_USERSPACE)) == 0 &&
	    ADDR_ISKERN(addr)) {
		struct mnode *hinted_node;
		hinted_node = (struct mnode *)pagedir_gethint(addr);
		if (hinted_node != NULL) {
			/* Count how # CPUs are doing hinted-node initialization, so
			 * that  `mman_unmap_kram_locked()'  can  sync  itself  with
			 * other CPUs which may still be accessing a mem-node  which
			 * is currently being split. */
			mman_kernel_hintinit_inuse_inc();
#ifndef CONFIG_NO_SMP
			hinted_node = (struct mnode *)pagedir_gethint(addr);
			if likely(hinted_node != NULL)
#endif /* !CONFIG_NO_SMP */
			{
				/* Deal with hinted nodes. */
				mnode_hinted_mmap(hinted_node, mf.mfl_addr);
				mman_kernel_hintinit_inuse_dec();
				return state;
			}
			mman_kernel_hintinit_inuse_dec();
		}
		/* Check  if some other thread initialized this page...
		 * If this happened, we mustn't fall-through to any  of
		 * the blocking code below in case the original mapping
		 * was marked as HINTED.
		 *
		 * Luckily, we're allowed to assume that the transition
		 * from HINTED->MAPPED on the page-dir level is atomic! */
		if ((ecode & X86_PAGEFAULT_ECODE_WRITING)
		    ? pagedir_iswritable(addr)
		    : pagedir_ismapped(addr))
			return state;
	}

	/* Re-enable interrupts if they were enabled before. */
	if (state->ics_irregs.ir_Pflags & EFLAGS_IF)
		__sti();

	/* Figure out memory manager in charge of the accessed address. */
	mf.mfl_mman = &mman_kernel;
	if (ADDR_ISUSER(addr) || FAULT_IS_USER) {
#ifndef NDEBUG
		/* Special case: When the TLS segment  contains an invalid pointer,  us
		 *               trying to obtain THIS_MMAN at this point is just going
		 *               to result in a #DF:
		 *   #1: READ_FROM_BAD_POINTER(%tls:0)
		 *   #2: Trigger #PF at `%tls.base'
		 *   #3: When `%tls.base' points into user-space (e.g. is `NULL'), we get here again
		 *   #4: Repeat at step #1
		 * This  then eventually results in a stack overflow that cannot be
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
		if unlikely(!read_nopf(&mythread->t_mman, &mf.mfl_mman)) {
			assertf(read_nopf(&mythread->t_mman, &mf.mfl_mman),
			        "Corrupt TLS base pointer: mythread = %p", mythread);
			/* Allow the user to IGNORE the assertion check, in which case we'll
			 * try to repair the damage... */
			mf.mfl_mman = x86_repair_broken_tls_state()->t_mman;
		}
#else /* !NDEBUG */
		mf.mfl_mman = THIS_MMAN;
#endif /* NDEBUG */
	}

	/* Preserve high-level task connections. */
	task_pushconnections(&con);

	/* Fill in missing members of the mem-fault controller. */
	__mfault_init(&mf);
	mf.mfl_size  = PAGESIZE;
	mf.mfl_flags = MMAN_FAULT_F_NORMAL;
	if (FAULT_IS_WRITE)
		mf.mfl_flags |= MMAN_FAULT_F_WRITE;
	TRY {

		/* Acquire a lock to the mman in charge. */
again_lock_mman:
#ifdef CONFIG_KERNEL_X86_PHYS2VIRT_IDENTITY_MAXALLOC
		if unlikely(!mman_lock_tryacquire(mf.mfl_mman)) {
			/* Access to the phys2virt section is allowed while preemption is disabled.
			 * However,  when preemption is  disabled, locking the  kernel VM may fail,
			 * so we need a special-case check for access to the phys2virt section when
			 * we've previously failed to lock the kernel VM for reading. */
			if (mf.mfl_mman == &mman_kernel && !FAULT_IS_USER &&
			    (uintptr_t)addr >= KERNEL_PHYS2VIRT_MIN &&
			    (uintptr_t)addr <= KERNEL_PHYS2VIRT_MAX) {
				mfault_fini(&mf);
				x86_phys2virt64_require(addr);
				goto pop_connections_and_return;
			}
			mman_lock_acquire(mf.mfl_mman);
		}
#else /* CONFIG_KERNEL_X86_PHYS2VIRT_IDENTITY_MAXALLOC */
		mman_lock_acquire(mf.mfl_mman);
#endif /* !CONFIG_KERNEL_X86_PHYS2VIRT_IDENTITY_MAXALLOC */

		/* Lookup the mapping for the accessed address. */
		mf.mfl_node = mnode_tree_locate(mf.mfl_mman->mm_mappings,
		                                mf.mfl_addr);
		if unlikely(!mf.mfl_node) {
			struct mman *mm = mf.mfl_mman;
			mman_lock_release(mm);
			mfault_fini(&mf);
			__mfault_init(&mf);
			mf.mfl_addr = (void *)((uintptr_t)addr & ~PAGEMASK);
			mf.mfl_mman = mm;
			mf.mfl_size  = PAGESIZE;
			mf.mfl_flags = MMAN_FAULT_F_NORMAL;
			if (FAULT_IS_WRITE)
				mf.mfl_flags |= MMAN_FAULT_F_WRITE;
			if (mm != &mman_kernel) {
				if (ADDR_ISKERN(addr)) {
					if (FAULT_IS_USER) {
						/* This can happen depending on what the CPU does when
						 * attempting to access the IOB vector associated with
						 * the calling thread.
						 * In this case, we must re-attempt the lookup within kernel-space. */
						mman_lock_acquire(&mman_kernel);
						mf.mfl_node = mnode_tree_locate(mman_kernel.mm_mappings,
						                                mf.mfl_addr);
						if (mf.mfl_node && !mf.mfl_node->mn_part) {
							mman_lock_release(&mman_kernel);
							/* Reserved node. */
							if (is_iob_mnode(mf.mfl_node))
								goto do_handle_iob_node_access;
						} else {
							mman_lock_release(&mman_kernel);
						}
					}
				}
#if !defined(CONFIG_NO_KERNEL_USERKERN_SEGMENT) && defined(__x86_64__)
				else {
					/* We can get here if the calling program is running in  compatibility
					 * mode, and has just attempted to perform a memory access/call to its
					 * ukern segment.
					 * NOTE: At  this point we already know that `addr < KERNELSPACE_BASE',
					 *       and because any  non-canonical CR2 would  have instead  caused
					 *       a GPF, we actually also know that `addr <= 0x0000ffffffffffff' */
					if (icpustate_getcs(state) == SEGMENT_USER_CODE32_RPL &&
					    addr >= (void *)(uintptr_t)COMPAT_KERNELSPACE_BASE &&
					    /* NOTE: The addr <= 32-bit is necessary since the hosted
					     *       application may have done something like `*(u32 *)0xffffffff = 0',
					     *       which   would   (among   other  addresses)   have   also  accessed
					     *       memory  beyond  the 32-bit  address  space, and  I'm  not entirely
					     *       sure if  a  processor  would  wrap the  pointer  in  this  case...
					     * Also: There may be other ways for 32-bit programs to deref 64-bit
					     *       pointers that I can't think of right now. */
					    addr <= (void *)(uintptr_t)UINT32_C(0xffffffff)) {
						struct mnode *krs;
						/* The access is of a 32-bit program trying to reach into
						 * what it ~thinks~ is the location of its  kernel-space.
						 * -> Try to handle this case by re-sizing `thismman_kernel_reservation'
						 *    to instead start at +3GiB, but only do so if there isn't  anything
						 *    else mapped within that address range.
						 * Technically, it would be more correct  if'd had already done this  during
						 * the exec() that spawned the  calling application, especially since  prior
						 * to this being done, the application would have been able to map something
						 * else  into the +3GiB...+4GiB address space range, however given that this
						 * is highly kos-specific behavior, I do think that doing this lazily should
						 * be ok (especially since a 32-bit program trying to map into +3GiB...+4GiB
						 * would already be doing something that it shouldn't, as attempting to  map
						 * that area of memory  is something that  cannot be done  when hosted by  a
						 * 32-bit kernel) */

						mman_lock_acquire(mm);
						mf.mfl_node = mnode_tree_locate(mm->mm_mappings,
						                                mf.mfl_addr);
						/* Re-check that there is no mapping at the accessed address. */
						if unlikely(mf.mfl_node != NULL) {
#define NEED_got_node_and_lock
							goto got_node_and_lock;
						}
						/* Make sure that `thismman_kernel_reservation' hasn't already been extended. */
						krs = &FORMMAN(mm, thismman_kernel_reservation);
						assert(mnode_getaddr(krs) == (void *)KERNELSPACE_BASE ||
						       mnode_getaddr(krs) == (void *)COMPAT_KERNELSPACE_BASE);
						assert(krs->mn_mman == mm);
						if (mnode_getaddr(krs) == (void *)KERNELSPACE_BASE) {
							/* Make sure that the +3GiB...+4GiB region is currently unmapped. */
							if (!mnode_tree_rlocate(mm->mm_mappings,
							                        (void const *)((uintptr_t)COMPAT_KERNELSPACE_BASE),
							                        (void const *)((uintptr_t)UINT64_C(0x100000000) -
							                                       (uintptr_t)COMPAT_KERNELSPACE_BASE))) {
								/* All right! Let's extend the `thismman_kernel_reservation' node! */
								printk(KERN_DEBUG "[x32] Extend thismman_kernel_reservation to include +3GiB...+4GiB\n");
								mf.mfl_node = krs;
								mman_mappings_removenode(mm, krs);
								krs->mn_minaddr = (byte_t *)COMPAT_KERNELSPACE_BASE;
								krs->mn_part    = &userkern_segment_part_compat;
								assert(krs->mn_fspath == NULL);
								assert(krs->mn_fsname == NULL);
								assert(krs->mn_module == NULL);
								/* Re-insert the node and continue operating as if we'd found
								 * everything as it  has been changed  into from the  get-go. */
								mman_mappings_insert_and_verify(mm, krs);
#define NEED_got_node_and_lock
								goto got_node_and_lock;
							}
						}
						mman_lock_release(mm);
					}
				}
#endif /* !CONFIG_NO_KERNEL_USERKERN_SEGMENT && __x86_64__ */
			}
			goto pop_connections_and_throw_segfault;
		}
#ifdef NEED_got_node_and_lock
#undef NEED_got_node_and_lock
got_node_and_lock:
#endif /* NEED_got_node_and_lock */

		/* At this point, the accessed mem-node has been
		 * determined, and  is  known  to  be  non-NULL! */
		mf.mfl_part = mf.mfl_node->mn_part;
		if unlikely(mf.mfl_part == NULL) {
			/* Deal with reserved memory nodes. */
			struct cpu *me;
			mman_lock_release(mf.mfl_mman);
			{
				struct mnode *node;
				node = mf.mfl_node;
				mfault_fini(&mf);
				__mfault_init(&mf);
				mf.mfl_node = node;
			}

#ifdef CONFIG_KERNEL_X86_PHYS2VIRT_IDENTITY_MAXALLOC
			/* Check for special case: `mf.mfl_node' belongs to the physical identity area. */
			if (mf.mfl_node == &x86_phys2virt64_node) {
				PREEMPTION_DISABLE();
				x86_phys2virt64_require(addr);
				if (state->ics_irregs.ir_Pflags & EFLAGS_IF)
					PREEMPTION_ENABLE();
				goto pop_connections_and_return;
			}
#endif /* CONFIG_KERNEL_X86_PHYS2VIRT_IDENTITY_MAXALLOC */

			/* Check for special case: `mf.mfl_node' may be the `thiscpu_x86_iobnode' of some CPU */
do_handle_iob_node_access:
			me = THIS_CPU;
			if (mf.mfl_node == &FORCPU(me, thiscpu_x86_iobnode)) {
				PREEMPTION_DISABLE();
				IF_SMP(COMPILER_READ_BARRIER();)
				IF_SMP(me = THIS_CPU;)
				IF_SMP(if (mf.mfl_node == &FORCPU(me, thiscpu_x86_iobnode))) {
					/* Most likely case: Accessing the IOB of the current CPU. */
					bool allow_preemption;
					assertf(FORCPU(me, thiscpu_x86_ioperm_bitmap) == NULL ||
					        FORCPU(me, thiscpu_x86_ioperm_bitmap) == THIS_X86_IOPERM_BITMAP,
					        "me                                    = %p\n"
					        "FORCPU(me, thiscpu_x86_ioperm_bitmap) = %p\n"
					        "THIS_X86_IOPERM_BITMAP                = %p\n",
					        me, FORCPU(me, thiscpu_x86_ioperm_bitmap),
					        THIS_X86_IOPERM_BITMAP);

					/* Make sure to handle any access errors after the ioperm() bitmap
					 * was already mapped during the current quantum as full segfault. */
					if unlikely(FORCPU(me, thiscpu_x86_ioperm_bitmap) != NULL) {
						/* Check for special case: even if the IOPERM bitmap is already
						 * mapped, allow a mapping upgrade  if it was mapped  read-only
						 * before, but is now needed as read-write. */
						if (FAULT_IS_WRITE && !pagedir_iswritable(addr)) {
							/* Upgrade the mapping */
						} else {
							goto pop_connections_and_throw_segfault;
						}
					}
					allow_preemption = icpustate_getpreemption(state);

					/* Make special checks if the access itself seems
					 * to  originate from a direct user-space access. */
					if (FAULT_IS_USER) {

						/* User-space can never get write-access to the IOB vector. */
						if (FAULT_IS_WRITE)
							goto pop_connections_and_throw_segfault;

						/* User-space isn't  allowed  to  directly  access  the  IOB  vector.
						 * To not  rely on  undocumented processor  behavior, manually  check
						 * if the  access  originates  from  a  user-space  I/O  instruction.
						 * If not (such as user-space directly trying to read kernel memory),
						 * then we always deny the access, no matter what! */
						if (!is_io_instruction_and_not_memory_access((byte_t const *)pc, state,
						                                             (uintptr_t)addr))
							goto pop_connections_and_throw_segfault;
					}
					if (!handle_iob_access(me, FAULT_IS_WRITE, allow_preemption)) {
						assert(PREEMPTION_ENABLED());
						goto again_lock_mman;
					}
					if (allow_preemption)
						__sti();
					goto pop_connections_and_return;
				}
				IF_SMP(if (icpustate_getpreemption(state)) __sti());
			}

			/* Either this  is an  access to  the IOB  vector of  a different  CPU,
			 * or  the  accessed  node  is  just  some  random,  reservation  node.
			 * In  the former case, we must take care to deal with a race condition
			 * which may happen in an SMP system where our current thread has  been
			 * moved  to a different  CPU since we've  re-enabled preemption at the
			 * start of this function, and before  getting here. In that case,  the
			 * access is still going to  reference the IOB of  the old CPU, and  we
			 * have to alter our behavior depending on the access happening because
			 * of  the some invalid access to a  different CPU's IOB vector, or the
			 * access  being caused by the CPU itself, and a CPU-transfer happening
			 * at just the wrong moment. */
#ifndef CONFIG_NO_SMP
			if (is_iob_mnode(mf.mfl_node)) {
				/* If we didn't actually re-enable preemption, then no cpu-transfer could have happened! */
				if (!icpustate_getpreemption(state))
					goto pop_connections_and_throw_segfault;

				/* I/O access from kernel-space wouldn't result in an IOB check, so
				 * if  the access comes from kernel-space, then this is the calling
				 * thread incorrectly accessing some other cpu's IOB. */
				if (!FAULT_IS_USER)
					goto pop_connections_and_throw_segfault;

				/* If the calling thread couldn't have changed CPUs, then this has
				 * to be an (incorrect) explicit access. */
				if (PERTASK_GET(this_task.t_flags) & TASK_FKEEPCORE)
					goto pop_connections_and_throw_segfault;

				/* The  calling thread is  capable of being  migrated between different CPUs,
				 * and the accessed node _is_ the IOB vector of a different CPU. However with
				 * all of these factors, there still  exists the possibility that the  access
				 * happened because the CPU itself accessed  the vector, as may be  triggered
				 * by use of the `(in|out)(b|w|l)' instructions.
				 * To  make sure that we can handle those cases as well, we can check the
				 * memory to which `icpustate_getpc(state)' points for being one of these
				 * instructions.
				 * To prevent the possibility of repeating the access to the IOB vector during
				 * this  check (in case a bad jump caused IP to end up within the IOB vector),
				 * also make sure that `pc' isn't apart of said vector! */
				if ((byte_t const *)pc >= mnode_getminaddr(mf.mfl_node) &&
				    (byte_t const *)pc <= mnode_getmaxaddr(mf.mfl_node))
					goto pop_connections_and_throw_segfault;

				/* If we got here cause of an I/O instruction, just return to the caller and
				 * have them attempt the access once again, hopefully without being moved to
				 * a different CPU yet again. */
				if (is_io_instruction_and_not_memory_access((byte_t const *)pc, state,
				                                            (uintptr_t)addr))
					goto pop_connections_and_return;
			}
#endif /* !CONFIG_NO_SMP */
			goto pop_connections_and_throw_segfault;
		}

		/* Deal with VIO memory access */
#ifdef LIBVIO_CONFIG_ENABLED
		if (mf.mfl_part->mp_state == MPART_ST_VIO) {
			struct vio_emulate_args args;
			uintptr_t node_flags;
			REF struct mpart *part;

#ifdef CONFIG_HAVE_KERNEL_DEBUGGER
			/* Don't dispatch VIO while in debugger-mode. */
			if unlikely(dbg_active) {
				mman_lock_release(mf.mfl_mman);
				mfault_fini(&mf);
				goto pop_connections_and_throw_segfault;
			}
#endif /* CONFIG_HAVE_KERNEL_DEBUGGER */

			/* Fill in VIO callback arguments. */
			node_flags                    = mf.mfl_node->mn_flags;
			args.vea_args.va_acmap_page   = mf.mfl_addr;
			args.vea_args.va_acmap_offset = (vio_addr_t)(mf.mfl_node->mn_partoff +
			                                             (size_t)((byte_t *)mf.mfl_addr -
			                                                      (byte_t *)mnode_getaddr(mf.mfl_node)));
			args.vea_ptrlo                = mnode_getminaddr(mf.mfl_node);
			args.vea_ptrhi                = mnode_getmaxaddr(mf.mfl_node);
			args.vea_addr                 = vioargs_vioaddr(&args.vea_args, args.vea_ptrlo);
			part                          = incref(mf.mfl_part);
			mman_lock_release(mf.mfl_mman);
			mfault_fini(&mf);
			__mfault_init(&mf);

			TRY {
				mpart_lock_acquire(part);
			} EXCEPT {
				decref(part);
				RETHROW();
			}
			args.vea_args.va_file = incref(part->mp_file);
			args.vea_args.va_ops  = args.vea_args.va_file->mf_ops->mo_vio;
			mpart_lock_release(part);

			/* Ensure that VIO operators are present. */
			if unlikely(!args.vea_args.va_ops) {
				decref_unlikely(args.vea_args.va_file);
				decref_unlikely(part);
				goto pop_connections_and_throw_segfault;
			}

			/* Check for special case: call into VIO memory */
			if (args.vea_args.va_ops->vo_call && addr == pc) {
				/* Make sure that memory mapping has execute permissions! */
				if unlikely(!(node_flags & MNODE_F_PEXEC)) {
					PERTASK_SET(this_exception_code, EXCEPT_CODEOF(E_SEGFAULT_NOTEXECUTABLE));
					PERTASK_SET(this_exception_args.e_segfault.s_context,
					            E_SEGFAULT_CONTEXT_FAULT | E_SEGFAULT_CONTEXT_EXEC |
					            E_SEGFAULT_CONTEXT_VIO | GET_PF_CONTEXT_UW_BITS());
cleanup_vio_and_pop_connections_and_set_exception_pointers2:
					decref_unlikely(args.vea_args.va_file);
					decref_unlikely(part);
					goto pop_connections_and_set_exception_pointers2;
#define NEED_pop_connections_and_set_exception_pointers2
				}
				/* Special case: call into VIO memory */
				TRY {
					vio_addr_t vio_addr;
					void const *callsite_pc;
					byte_t const *sp;
					IF_X64(bool is_compat;)
					/* Must unwind the stack to restore the IP of the VIO call-site. */
					sp = icpustate_getsp(state);
					if ((sp >= (byte_t const *)KERNELSPACE_BASE) && FAULT_IS_USER)
						goto do_normal_vio; /* Validate the stack-pointer for user-space. */
					IF_X64(is_compat = icpustate_is32bit(state);)
					TRY {
						IF_X64(if (is_compat) {
							callsite_pc = (void const *)(uintptr_t)(*(u32 const *)sp);
						} else) {
							callsite_pc = *(void const *const *)sp;
						}
					} EXCEPT {
						if (!was_thrown(E_SEGFAULT))
							RETHROW();
						goto do_normal_vio;
					}
					/* Unwind the stack, and remember the call-site instruction pointer. */
#ifdef __x86_64__
					if (FAULT_IS_USER ? ((byte_t const *)callsite_pc >= (byte_t const *)USERSPACE_END)
					                  : ((byte_t const *)callsite_pc < (byte_t const *)KERNELSPACE_BASE))
						goto do_normal_vio;
					icpustate_setpc(state, callsite_pc);
					icpustate_setsp(state, (byte_t *)(is_compat ? sp + 4 : sp + 8));
#else /* __x86_64__ */
					if ((void const *)sp != (void const *)(&state->ics_irregs_k + 1) ||
					    FAULT_IS_USER) {
						if ((byte_t const *)callsite_pc >= (byte_t const *)KERNELSPACE_BASE)
							goto do_normal_vio;
						icpustate_setpc(state, callsite_pc);
						state->ics_irregs_u.ir_esp += 4;
					} else {
						if ((byte_t const *)callsite_pc < (byte_t const *)KERNELSPACE_BASE)
							goto do_normal_vio;
						state->ics_irregs_k.ir_eip = (uintptr_t)callsite_pc;
						state = (struct icpustate *)memmoveup((byte_t *)state + sizeof(void *), state,
						                                      OFFSET_ICPUSTATE_IRREGS +
						                                      SIZEOF_IRREGS_KERNEL);
					}
#endif /* !__x86_64__ */
					/* Figure out the exact VIO address that got called. */
					vio_addr = args.vea_args.va_acmap_offset +
					           ((byte_t *)addr - (byte_t *)args.vea_args.va_acmap_page);
					/* Invoke the VIO call operator. */
					args.vea_args.va_state = state;
					(*args.vea_args.va_ops->vo_call)(&args.vea_args, vio_addr);
					state = args.vea_args.va_state;
				} EXCEPT {
					/* Ensure that a the VIO flag is set if necessary */
					if (was_thrown(E_SEGFAULT)) {
						void *faultaddr;
						faultaddr = (void *)PERTASK_GET(this_exception_args.e_segfault.s_addr);
						if (faultaddr == addr) {
							uintptr_t flags;
							flags = PERTASK_GET(this_exception_args.e_segfault.s_context);
							flags |= E_SEGFAULT_CONTEXT_VIO;
							PERTASK_SET(this_exception_args.e_segfault.s_context, flags);
						}
					}
					/* Directly unwind the exception, since we've got a custom return-pc set-up.
					 * If we did a normal RETHROW() here, then the (currently correct) return PC
					 * would get overwritten with the VIO function address. */
					decref_unlikely(args.vea_args.va_file);
					decref_unlikely(part);
					RETHROW();
				}
				decref_unlikely(args.vea_args.va_file);
				decref_unlikely(part);
				goto pop_connections_and_return;
			}
do_normal_vio:
			/* Make sure that the segment was mapped with the proper protection */
			if unlikely((ecode & X86_PAGEFAULT_ECODE_WRITING)
			            ? !(node_flags & MNODE_F_PWRITE)   /* Write to read-only VIO segment */
			            : !(node_flags & MNODE_F_PREAD)) { /* Read from non-readable VIO segment */
				PERTASK_SET(this_exception_code, (ecode & X86_PAGEFAULT_ECODE_WRITING)
				                                 ? EXCEPT_CODEOF(E_SEGFAULT_READONLY)
				                                 : EXCEPT_CODEOF(E_SEGFAULT_NOTREADABLE));
				PERTASK_SET(this_exception_args.e_segfault.s_context,
				            E_SEGFAULT_CONTEXT_FAULT | E_SEGFAULT_CONTEXT_EXEC |
				            E_SEGFAULT_CONTEXT_VIO | GET_PF_CONTEXT_UW_BITS());
				goto cleanup_vio_and_pop_connections_and_set_exception_pointers2;
			}
			args.vea_args.va_state = state;
			TRY {
				/* Emulate the current instruction. */
				viocore_emulate(&args);
			} EXCEPT {
				decref_unlikely(args.vea_args.va_file);
				decref_unlikely(part);
				/*task_popconnections();*/ /* Handled by outer EXCEPT */
				RETHROW();
			}
			decref_unlikely(args.vea_args.va_file);
			decref_unlikely(part);
			task_popconnections();
#ifndef __x86_64__
			/* Check if the kernel %esp or %ss was modified */
			if unlikely(args.vea_kernel_override & (VIO_EMULATE_ARGS_386_KERNEL_ESP_VALID |
			                                        VIO_EMULATE_ARGS_386_KERNEL_SS_VALID)) {
				u32 real_esp = args.vea_kernel_esp_override;
				u16 real_ss  = args.vea_kernel_ss_override;
				u32 *regload_area;
				assert(!FAULT_IS_USER);
				if (!(args.vea_kernel_override & VIO_EMULATE_ARGS_386_KERNEL_SS_VALID))
					real_ss = icpustate32_getkernelss(args.vea_args.va_state);
				if (!(args.vea_kernel_override & VIO_EMULATE_ARGS_386_KERNEL_ESP_VALID))
					real_esp = icpustate32_getkernelesp(args.vea_args.va_state);
				regload_area = (u32 *)mnode_getaddr(THIS_KERNEL_STACK);
				/* Fill in the register save area to match what's going to
				 * get  loaded  by `x86_vio_kernel_esp_bootstrap_loader()' */
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

		/* Verify that the caller is allowed to perform th access that they're attempting. */
		if unlikely(!(mf.mfl_node->mn_flags & MNODE_F_PEXEC) &&
		            ((ecode & X86_PAGEFAULT_ECODE_INSTRFETCH) || addr == pc)) {
			/* Non-executable memory */
			PERTASK_SET(this_exception_code, EXCEPT_CODEOF(E_SEGFAULT_NOTEXECUTABLE));
decref_part_and_pop_connections_and_set_exception_pointers:
			mman_lock_release(mf.mfl_mman);
			mfault_fini(&mf);
#define NEED_pop_connections_and_set_exception_pointers
			goto pop_connections_and_set_exception_pointers;
		}
		if (mf.mfl_flags & MMAN_FAULT_F_WRITE) {
			if unlikely(!(mf.mfl_node->mn_flags & MNODE_F_PWRITE)) {
				/* Read-only memory */
				PERTASK_SET(this_exception_code, EXCEPT_CODEOF(E_SEGFAULT_READONLY));
				goto decref_part_and_pop_connections_and_set_exception_pointers;
			}
		} else {
			if unlikely(!(mf.mfl_node->mn_flags & MNODE_F_PREAD)) {
				/* Write-only memory */
				PERTASK_SET(this_exception_code, EXCEPT_CODEOF(E_SEGFAULT_NOTREADABLE));
				goto decref_part_and_pop_connections_and_set_exception_pointers;
			}
		}

		/* Do a regular, old memory fault. */
		if (!mfault_lockpart_or_unlock(&mf))
			goto again_lock_mman;
		if (!mfault_or_unlock(&mf))
			goto again_lock_mman;
	} EXCEPT {
		mfault_fini(&mf);
		task_popconnections();
		if (ecode & X86_PAGEFAULT_ECODE_USERSPACE)
			PERTASK_SET(this_exception_faultaddr, pc);
		RETHROW();
	}

	/* Re-map the freshly faulted memory. */
	{
		pagedir_prot_t prot;
		if unlikely(mf.mfl_node->mn_flags & MNODE_F_MPREPARED) {
			prot = mpart_mmap_node(mf.mfl_part, mf.mfl_addr,
			                       mf.mfl_size, mf.mfl_offs,
			                       mf.mfl_node);
		} else {
			if unlikely(!pagedir_prepare(mf.mfl_addr, mf.mfl_size)) {
				mpart_lock_release(mf.mfl_part);
				mman_lock_release(mf.mfl_mman);
				task_popconnections();
				THROW(E_BADALLOC_INSUFFICIENT_PHYSICAL_MEMORY, PAGESIZE);
			}
			prot = mpart_mmap_node(mf.mfl_part, mf.mfl_addr,
			                       mf.mfl_size, mf.mfl_offs,
			                       mf.mfl_node);
			pagedir_unprepare(mf.mfl_addr, mf.mfl_size);
		}
		mpart_lock_release(mf.mfl_part);

		/* If write-access was granted, add the node to the list of writable nodes. */
		if ((prot & PAGEDIR_PROT_WRITE) && !LIST_ISBOUND(mf.mfl_node, mn_writable))
			LIST_INSERT_HEAD(&mf.mfl_mman->mm_writable, mf.mfl_node, mn_writable);

		/* Sync the newly mapped address range if the mapping was created  with
		 * write  permissions. Technically, we'd only need to sync if a mapping
		 * is  created where there  was already a  mapping before, however this
		 * is exactly the case when a read/write mapping is created where there
		 * was a read-only mapping before.
		 *
		 * The reason why we need to sync in this situation boils down to the
		 * fact that other CPUs (or even the caller's CPU) may still have TLB
		 * caches for `addr' (even if those caches are only for read-access),
		 * such that those (now stale) caches could still be used.
		 *
		 * So to prevent cross-cpu inconsistencies, whenever a mapping is made
		 * that ~may~ be  replacing another pre-existing  mapping, we force  a
		 * sync for the mapped range.
		 *
		 * FIXME: The original `mf.mfl_part' (from before mfault_lockpart_or_unlock)
		 *        must only be decref'd _AFTER_ we did this. - Otherwise, other CPUs
		 *        might have TLBs for memory that was already freed! */
		if (prot & PAGEDIR_PROT_WRITE)
			mman_sync(mf.mfl_addr, mf.mfl_size);

#if 0
		printk(KERN_DEBUG "Page fault at %p (page %p) [pc=%p,sp=%p] [ecode=%#" PRIxPTR "] resolve:[part=%p,prot=%#x]\n",
		       (uintptr_t)addr, mf.mfl_addr, pc, icpustate_getsp(state), ecode,
		       mf.mfl_part, prot);
#endif
	}
	mman_lock_release(mf.mfl_mman);

	/* And we're done! */

pop_connections_and_return:
	task_popconnections();
	return state;

	/************************************************************************/
	/* Error handling...                                                    */
	/************************************************************************/
#ifdef NEED_pop_connections_and_set_exception_pointers
#undef NEED_pop_connections_and_set_exception_pointers
pop_connections_and_set_exception_pointers:
	task_popconnections();
	goto set_exception_pointers;
#endif /* NEED_pop_connections_and_set_exception_pointers */
#ifdef NEED_pop_connections_and_set_exception_pointers2
#undef NEED_pop_connections_and_set_exception_pointers2
pop_connections_and_set_exception_pointers2:
	task_popconnections();
	goto set_exception_pointers2;
#endif /* NEED_pop_connections_and_set_exception_pointers2 */
pop_connections_and_throw_segfault:
	task_popconnections();
/*throw_segfault:*/
	if (pc == addr) {
		/* This can happen when trying to call an invalid function pointer.
		 * -> Try to unwind this happening. */
		IF_X64(bool is_compat;)
		void const *callsite_pc;
		byte_t const *sp;

#ifdef __x86_64__
		/* Special handling required for work-around to QEMU bug.
		 * See `handle_noncanon_as_gpf:'  below  for  more  info! */
		if unlikely(ADDR_IS_NONCANON(addr))
			goto handle_noncanon_as_gpf;
#endif /* __x86_64__ */

		sp = icpustate_getsp(state);
		if (sp >= (byte_t const *)KERNELSPACE_BASE &&
		    ((void const *)sp != (void const *)(&state->ics_irregs + 1) || FAULT_IS_USER))
			goto not_a_badcall;
		IF_X64(is_compat = icpustate_is32bit(state);)
		TRY {
			IF_X64(if (is_compat) {
				callsite_pc = (void const *)(uintptr_t)(*(u32 const *)sp);
			} else) {
				callsite_pc = *(void const *const *)sp;
			}
		} EXCEPT {
			if (!was_thrown(E_SEGFAULT)) {
				if (FAULT_IS_USER)
					PERTASK_SET(this_exception_faultaddr, pc);
				rethrow_exception_from_pf_handler(state, pc);
			}
			goto not_a_badcall;
		}
#ifdef __x86_64__
		if (FAULT_IS_USER ? ((byte_t const *)callsite_pc >= (byte_t const *)USERSPACE_END)
		                  : ((byte_t const *)callsite_pc < (byte_t const *)KERNELSPACE_BASE))
			goto not_a_badcall;
		icpustate_setpc(state, callsite_pc);
		icpustate_setsp(state, (byte_t *)(is_compat ? sp + 4 : sp + 8));
#else /* __x86_64__ */
		if ((void const *)sp != (void const *)(&state->ics_irregs_k + 1) || FAULT_IS_USER) {
			if ((byte_t const *)callsite_pc >= (byte_t const *)KERNELSPACE_BASE)
				goto not_a_badcall;
			icpustate_setpc(state, callsite_pc);
			state->ics_irregs_u.ir_esp += 4;
		} else {
			if ((byte_t const *)callsite_pc < (byte_t const *)KERNELSPACE_BASE)
				goto not_a_badcall;
			state->ics_irregs_k.ir_eip = (uintptr_t)callsite_pc;
			state = (struct icpustate *)memmoveup((byte_t *)state + sizeof(void *), state,
			                                      OFFSET_ICPUSTATE_IRREGS +
			                                      SIZEOF_IRREGS_KERNEL);
		}
#endif /* !__x86_64__ */
		TRY {
			void const *call_instr;
			call_instr = instruction_pred_nx(callsite_pc, icpustate_getisa(state));
			if likely(call_instr)
				callsite_pc = call_instr;
		} EXCEPT {
			if (!was_thrown(E_SEGFAULT)) {
				if (FAULT_IS_USER)
					PERTASK_SET(this_exception_faultaddr, pc);
				rethrow_exception_from_pf_handler(state, pc);
			}
			/* Discard read-from-callsite_pc exception... */
		}
		PERTASK_SET(this_exception_faultaddr, callsite_pc);
		PERTASK_SET(this_exception_code, (ecode & X86_PAGEFAULT_ECODE_PRESENT)
		                                 ? EXCEPT_CODEOF(E_SEGFAULT_NOTEXECUTABLE)
		                                 : EXCEPT_CODEOF(E_SEGFAULT_UNMAPPED));
		PERTASK_SET(this_exception_args.e_segfault.s_addr, (uintptr_t)addr);
		PERTASK_SET(this_exception_args.e_segfault.s_context,
		            E_SEGFAULT_CONTEXT_FAULT | E_SEGFAULT_CONTEXT_EXEC |
		            GET_PF_CONTEXT_UW_BITS());
		{
			unsigned int i;
			for (i = 2; i < EXCEPTION_DATA_POINTERS; ++i)
				PERTASK_SET(this_exception_args.e_pointers[i], 0);
		}
		printk(KERN_DEBUG "[segfault] PC-Fault at %p (page %p) [pc=%p,%p] [ecode=%#" PRIxPTR "]\n",
		       addr, (void *)FLOOR_ALIGN((uintptr_t)addr, PAGESIZE),
		       callsite_pc, icpustate_getpc(state), ecode);
		goto do_unwind_state;
	}
not_a_badcall:
	if ((ecode & (X86_PAGEFAULT_ECODE_PRESENT | X86_PAGEFAULT_ECODE_WRITING)) ==
	    /*    */ (X86_PAGEFAULT_ECODE_PRESENT | X86_PAGEFAULT_ECODE_WRITING)) {
		PERTASK_SET(this_exception_code, EXCEPT_CODEOF(E_SEGFAULT_READONLY));
	} else if ((ecode & X86_PAGEFAULT_ECODE_PRESENT) &&
	           ((ecode & X86_PAGEFAULT_ECODE_INSTRFETCH) || (pc == addr))) {
		PERTASK_SET(this_exception_code, EXCEPT_CODEOF(E_SEGFAULT_NOTEXECUTABLE));
	} else {
		PERTASK_SET(this_exception_code, EXCEPT_CODEOF(E_SEGFAULT_UNMAPPED));
	}
set_exception_pointers:
	PERTASK_SET(this_exception_args.e_segfault.s_context,
	            E_SEGFAULT_CONTEXT_FAULT |
	            ((ecode & X86_PAGEFAULT_ECODE_INSTRFETCH) || (pc == addr) ? E_SEGFAULT_CONTEXT_EXEC : 0) |
	            GET_PF_CONTEXT_UW_BITS());
set_exception_pointers2:
	PERTASK_SET(this_exception_args.e_segfault.s_addr, (uintptr_t)addr);
	{
		unsigned int i;
		for (i = 2; i < EXCEPTION_DATA_POINTERS; ++i)
			PERTASK_SET(this_exception_args.e_pointers[i], 0);
	}
#ifdef __x86_64__
	/* Even though the CPU is supposed to raise a #GPF when trying to
	 * access a non-canon address, I've  seen newer versions of  QEMU
	 * still throw a #PF in this case.
	 *
	 * This  actually breaks the  "test-fault.c" system-test, so to
	 * normalize the behavior for this sort of situation, just call
	 * into the GPF handler when we see a non-canon address! */
	if unlikely(ADDR_IS_NONCANON(addr)) {
handle_noncanon_as_gpf:
		PERTASK_SET(this_exception_code, EXCEPT_CODEOF(E_OK));
		return x86_handle_gpf(state, 0);
	}
#endif /* __x86_64__ */

	/* Always make the state point to the instruction _after_ the one causing the problem. */
	PERTASK_SET(this_exception_faultaddr, pc);
	pc = instruction_trysucc(pc, icpustate_getisa(state));
	printk(KERN_DEBUG "[segfault] Fault at %p (page %p) [pc=%p,%p] [ecode=%#" PRIxPTR "]\n",
	       addr, (void *)FLOOR_ALIGN((uintptr_t)addr, PAGESIZE),
	       icpustate_getpc(state), pc, ecode);
	icpustate_setpc(state, pc);
do_unwind_state:

	/* Try to trigger a debugger trap (if enabled) */
	if (kernel_debugtrap_shouldtrap(KERNEL_DEBUGTRAP_ON_SEGFAULT))
		state = kernel_debugtrap_r(state, SIGSEGV);
	assert(except_active());
	except_throw_current_at_icpustate(state);
#undef FAULT_IS_USER
#undef FAULT_IS_WRITE
#undef GET_PF_CONTEXT_UW_BITS
}

DECL_END

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_FAULT_HANDLE_PAGEFAULT_C */
