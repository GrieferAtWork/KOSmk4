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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_SCHED_APIC_C
#define GUARD_KERNEL_CORE_ARCH_I386_SCHED_APIC_C 1
#define DISABLE_BRANCH_PROFILING 1 /* Don't profile this file */
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <debugger/config.h>
#include <fs/vfs.h>
#include <kernel/driver-param.h>
#include <kernel/handle.h>
#include <kernel/malloc.h>
#include <kernel/memory.h>
#include <kernel/paging.h>
#include <kernel/panic.h>
#include <kernel/printk.h>
#include <kernel/vm.h>
#include <kernel/vm/phys.h>
#include <kernel/x86/apic.h>
#include <kernel/x86/cpuid.h>
#include <kernel/x86/gdt.h>
#include <kernel/x86/pic.h>
#include <kernel/x86/pit.h>
#include <sched/cpu.h>
#include <sched/scheduler.h>
#include <sched/task.h>
#include <sched/tsc.h>
#include <sched/x86/cpureg.h>
#include <sched/x86/smp.h>
#include <sched/x86/tss.h>

#include <hybrid/align.h>
#include <hybrid/atomic.h>

#include <asm/intrin.h>
#include <kos/kernel/cpu-state.h>
#include <kos/kernel/tss-compat.h>
#include <kos/kernel/tss.h>

#include <assert.h>
#include <inttypes.h>
#include <stddef.h>
#include <string.h>

DECL_BEGIN

#ifndef NDEBUG
#define DBG_memset(dst, byte, num_bytes) memset(dst, byte, num_bytes)
#else /* !NDEBUG */
#define DBG_memset(dst, byte, num_bytes) (void)0
#endif /* NDEBUG */

DATDEF ATTR_PERCPU u8 thiscpu_x86_lapicid_ ASMNAME("thiscpu_x86_lapicid");
DATDEF ATTR_PERCPU u8 thiscpu_x86_lapicversion_ ASMNAME("thiscpu_x86_lapicversion");
DATDEF unsigned int cpu_count_ ASMNAME("cpu_count");
DATDEF struct cpu *cpu_vector_[CONFIG_MAX_CPU_COUNT] ASMNAME("cpu_vector");


#ifndef CONFIG_NO_SMP

/* Saved GDT register.
 * usually: { (SEGMENT_COUNT * SIZEOF_SEGMENT_DESCRIPTOR) - 1, thiscpu_x86_gdt } */
PUBLIC ATTR_PERCPU struct desctab thiscpu_x86_saved_gdtr = {
	/* .dt_limit = */ sizeof(bootcpu_x86_gdt) - 1,
	/* .dt_base  = */ (uintptr_t)bootcpu_x86_gdt
};

/* Saved IDT register. (usually `x86_idt_ptr') */
PUBLIC ATTR_PERCPU struct desctab thiscpu_x86_saved_idtr = {
	/* .dt_limit = */ sizeof(x86_idt) - 1,
	/* .dt_base  = */ (uintptr_t)x86_idt
};

/* Saved LDT register. (usually `SEGMENT_CPU_LDT') */
PUBLIC ATTR_PERCPU u16 thiscpu_x86_saved_ldtr = SEGMENT_CPU_LDT;

/* Saved Task register. (usually `SEGMENT_CPU_TSS') */
PUBLIC ATTR_PERCPU u16 thiscpu_x86_saved_tr = SEGMENT_CPU_TSS;

/* Saved %cr0 and %cr4 registers. Loaded during late CPU
 * bootstrap, and saved when a CPU goes into deep sleep.
 *
 * First initialized alongside cpuid information. */
PUBLIC ATTR_PERCPU uintptr_t thiscpu_x86_saved_cr0 = 0;
PUBLIC ATTR_PERCPU uintptr_t thiscpu_x86_saved_cr4 = 0;



INTDEF NOBLOCK void NOTHROW(KCALL apic_send_init)(u8 procid);
INTDEF NOBLOCK void NOTHROW(KCALL apic_send_startup)(u8 procid, u8 pageno);

INTERN ATTR_FREEBSS volatile u8 cpu_offline_mask[CEILDIV(CONFIG_MAX_CPU_COUNT, 8)];
#if CEILDIV(CONFIG_MAX_CPU_COUNT, 8) == 1
#define CPU_ALL_ONLINE  (ATOMIC_READ(*(u8 *)cpu_offline_mask) == 0)
#elif CEILDIV(CONFIG_MAX_CPU_COUNT, 8) == 2
#define CPU_ALL_ONLINE  (ATOMIC_READ(*(u16 *)cpu_offline_mask) == 0)
#elif CEILDIV(CONFIG_MAX_CPU_COUNT, 8) == 4
#define CPU_ALL_ONLINE  (ATOMIC_READ(*(u32 *)cpu_offline_mask) == 0)
#else
LOCAL bool KCALL all_all_cpus_online(void) {
	unsigned int i;
	for (i = 0; i < COMPILER_LENOF(cpu_offline_mask); ++i)
		if (ATOMIC_READ(cpu_offline_mask[i]))
			return false;
	return true;
}
#define CPU_ALL_ONLINE   all_all_cpus_online()
#endif

INTDEF FREE void NOTHROW(KCALL x86_calibrate_boottsc)(void);
INTDEF FREE void NOTHROW(KCALL x86_altcore_entry)(void);

/* The physical page to which the realmode SMP entry code is mapped. */
INTERN u8 x86_smp_entry_page = 0;

INTDEF FREE byte_t x86_smp_gdt[];
INTDEF FREE byte_t x86_smp_entry[];
#undef x86_smp_entry_size
INTDEF FREE byte_t x86_smp_entry_size[];
#define x86_smp_entry_size (size_t)x86_smp_entry_size

INTDEF u16 x86_smp_entry_gdt_segment;
INTDEF u16 x86_smp_entry_gdt_offset;
INTDEF u32 x86_smp_gdt_pointer_base;

INTDEF byte_t __kernel_percpu_start[];
INTDEF byte_t __kernel_percpu_size[];
INTDEF byte_t __kernel_percpu_full_bytes[];
INTDEF byte_t __kernel_pertask_start[];
INTDEF byte_t __kernel_pertask_size[];
INTDEF FREE struct tss __kernel_percpu_tss;

typedef void (KCALL *pertask_init_t)(struct task *__restrict self);
INTDEF pertask_init_t __kernel_pertask_init_start[];
INTDEF pertask_init_t __kernel_pertask_init_end[];

typedef void (KCALL *pertask_fini_t)(struct task *__restrict self);
INTDEF pertask_fini_t __kernel_pertask_fini_start[];
INTDEF pertask_fini_t __kernel_pertask_fini_end[];


DATDEF ATTR_PERCPU struct mnode thiscpu_x86_dfstacknode_ ASMNAME("thiscpu_x86_dfstacknode");
DATDEF ATTR_PERCPU struct mpart thiscpu_x86_dfstackpart_ ASMNAME("thiscpu_x86_dfstackpart");
DATDEF ATTR_PERTASK struct mnode this_kernel_stacknode_ ASMNAME("this_kernel_stacknode");
DATDEF ATTR_PERTASK struct mnode this_trampoline_node_ ASMNAME("this_trampoline_node");
#ifdef CONFIG_HAVE_KERNEL_STACK_GUARD
DATDEF ATTR_PERTASK struct mnode this_kernel_stackguard_ ASMNAME("this_kernel_stackguard");
#endif /* CONFIG_HAVE_KERNEL_STACK_GUARD */
DATDEF ATTR_PERTASK struct mpart this_kernel_stackpart_ ASMNAME("this_kernel_stackpart");
DATDEF ATTR_PERCPU u8 thiscpu_x86_iob_[] ASMNAME("thiscpu_x86_iob");

#define HINT_ADDR(x, y) x
#define HINT_MODE(x, y) y
#define HINT_GETADDR(x) HINT_ADDR x
#define HINT_GETMODE(x) HINT_MODE x

PRIVATE ATTR_FREETEXT REF struct mpart *KCALL
mpart_create_lockram(size_t num_pages) {
	REF struct mpart *result;
	result = (struct mpart *)kmalloc(sizeof(struct mpart),
	                                       GFP_LOCKED | GFP_PREFLT);
#ifdef CONFIG_USE_NEW_VM
	result->mp_refcnt = 1;
	result->mp_flags  = (MPART_F_NO_GLOBAL_REF | MPART_F_CHANGED |
	                     MPART_F_NOSPLIT | MPART_F_NOMERGE |
	                     MPART_F_MLOCK_FROZEN | MPART_F_MLOCK);
	result->mp_file   = incref(&mfile_ndef);
	LIST_INIT(&result->mp_copy);
	/*LIST_INIT(&result->mp_share);*/ /* Initialized by our caller. */
	SLIST_INIT(&result->mp_lockops);
	LIST_ENTRY_UNBOUND_INIT(&result->mp_allparts);
	DBG_memset(&result->mp_changed, 0xcc, sizeof(result->mp_changed));
	result->mp_minaddr = (pos_t)0;
	result->mp_maxaddr = (pos_t)((num_pages * PAGESIZE) - 1);
	_mpart_init_asanon(result);
	result->mp_blkst_ptr = NULL;
	result->mp_meta      = NULL;

	/* Allocate RAM for the new mem-part. */
	TRY {
		mpart_ll_allocmem(result, num_pages);
	} EXCEPT {
		kfree(result);
		RETHROW();
	}
#else /* CONFIG_USE_NEW_VM */
	result->dp_refcnt = 1;
	shared_rwlock_init(&result->dp_lock);
#ifndef NDEBUG
	memset(&result->dp_tree.a_min, 0xcc, sizeof(result->dp_tree.a_min));
	memset(&result->dp_tree.a_max, 0xcc, sizeof(result->dp_tree.a_max));
#endif /* !NDEBUG */
	result->dp_tree.a_vmin = 0;
	result->dp_tree.a_vmax = (datapage_t)(num_pages - 1);
	result->dp_crefs = NULL;
#ifndef NDEBUG
/*	memset(&result->dp_srefs, 0xcc, sizeof(result->dp_srefs)); */ /* Initialized by the caller */
#endif /* !NDEBUG */
	result->dp_stale = NULL;
	result->dp_block = incref(&vm_datablock_anonymous_zero);
	result->dp_flags = VM_DATAPART_FLAG_LOCKED | VM_DATAPART_FLAG_HEAPPPP | VM_DATAPART_FLAG_KERNPRT;
	result->dp_state = VM_DATAPART_STATE_LOCKED;
	result->dp_pprop_p = NULL;
	result->dp_futex   = NULL;
	/* Allocate RAM for the new datapart. */
	TRY {
		vm_datapart_do_allocram(result);
	} EXCEPT {
		kfree(result);
		RETHROW();
	}
#endif /* !CONFIG_USE_NEW_VM */
	return result;
}

PRIVATE ATTR_FREETEXT struct mnode *KCALL
mnode_create_lockram(size_t num_pages) {
	struct mnode *result;
	REF struct mpart *part;
	part = mpart_create_lockram(num_pages);
	TRY {
		result = (struct mnode *)kmalloc(sizeof(struct mnode),
		                                 GFP_LOCKED | GFP_PREFLT);
	} EXCEPT {
		destroy(part);
		RETHROW();
	}
#ifdef CONFIG_USE_NEW_VM
	result->mn_flags = MNODE_F_PWRITE | MNODE_F_PREAD |
	                   MNODE_F_SHARED | MNODE_F_NOSPLIT |
	                   MNODE_F_NOMERGE | MNODE_F_KERNPART |
	                   MNODE_F_MLOCK;
	result->mn_part         = part; /* Inherit reference */
	result->mn_fspath       = NULL;
	result->mn_fsname       = NULL;
	result->mn_mman         = &mman_kernel;
	result->mn_partoff      = 0;
	result->mn_link.le_next = NULL;
	result->mn_link.le_prev = &part->mp_share.lh_first;
	result->_mn_module      = NULL;
	part->mp_share.lh_first = result;
	LIST_ENTRY_UNBOUND_INIT(&result->mn_writable);
#else /* CONFIG_USE_NEW_VM */
	result->vn_prot          = VM_PROT_READ | VM_PROT_WRITE | VM_PROT_SHARED;
	part->dp_srefs           = result;
	result->vn_link.ln_pself = &part->dp_srefs;
	result->vn_link.ln_next  = NULL;
	result->vn_flags         = VM_NODE_FLAG_KERNPRT | VM_NODE_FLAG_NOMERGE;
	result->vn_vm            = &vm_kernel;
	result->vn_part          = part;
	result->vn_block         = incref(&vm_datablock_anonymous_zero);
	result->vn_fspath        = NULL;
	result->vn_fsname        = NULL;
	result->vn_guard         = 0;
#endif /* !CONFIG_USE_NEW_VM */
	return result;
}

PRIVATE NOBLOCK ATTR_FREETEXT void
NOTHROW(KCALL vm_node_destroy_locked_ram)(struct mnode *__restrict self) {
	assert(self->vn_block);
	assert(self->vn_part);
	assert(self->vn_fspath == NULL);
	assert(self->vn_fsname == NULL);
	assert(self->vn_link.ln_pself == &self->vn_part->dp_srefs);
	assert(self->vn_link.ln_next == NULL);
	assert(self->vn_part->dp_srefs == self);
	/* Clear out the SREFS field, as `vm_datapart_destroy()'
	 * will cause panic if that field is non-NULL */
	self->vn_part->dp_srefs = NULL;
	/* Drop references and free the node descriptor. */
	decref_unlikely(self->vn_block);
	decref_likely(self->vn_part);
	kfree(self);
}

INTDEF byte_t __x86_cpu_part1_bytes[];
INTDEF byte_t __x86_cpu_part1_pages[];

#ifdef __x86_64__
INTDEF FREE union p64_pdir_e1 *NOTHROW(FCALL x86_get_cpu_iob_pointer_p64)(struct cpu *__restrict self);
#define x86_get_cpu_iob_pointer  x86_get_cpu_iob_pointer_p64
#else /* __x86_64__ */
#ifndef CONFIG_NO_PAGING_P32
INTDEF FREE union p32_pdir_e1 *NOTHROW(FCALL x86_get_cpu_iob_pointer_p32)(struct cpu *__restrict self);
#endif /* !CONFIG_NO_PAGING_P32 */
#ifndef CONFIG_NO_PAGING_PAE
INTDEF FREE union pae_pdir_e1 *NOTHROW(FCALL x86_get_cpu_iob_pointer_pae)(struct cpu *__restrict self);
#endif /* !CONFIG_NO_PAGING_PAE */

#ifdef CONFIG_NO_PAGING_P32
#define x86_get_cpu_iob_pointer  x86_get_cpu_iob_pointer_p32
#elif defined(CONFIG_NO_PAGING_PAE)
#define x86_get_cpu_iob_pointer  x86_get_cpu_iob_pointer_pae
#else /* ... */
#define x86_get_cpu_iob_pointer(self)                                   \
	(X86_PAGEDIR_USES_P32() ? (void *)x86_get_cpu_iob_pointer_p32(self) \
	                        : (void *)x86_get_cpu_iob_pointer_pae(self))
#endif /* !... */
#endif /* !__x86_64__ */


PRIVATE ATTR_FREETEXT struct cpu *KCALL cpu_alloc(void) {
	/* A CPU structure is quite complicated, since it contains an in-line
	 * memory hole spanning two pages at an offset of `+(uintptr_t)thiscpu_x86_iob'
	 * bytes form the start of the CPU structure, that is then followed by
	 * 1 additional page that is really only needed for the single 0xff byte
	 * at its start, as mandated by the Intel developer manual for termination
	 * of the IOB vector.
	 * As such, the cpu structure itself consists of 3 consecutive VM nodes
	 * describing the memory mappings before, for, and after the 2-page hole. */
	struct mnode *cpu_node1;
	struct mnode *cpu_node2;
	struct mnode *cpu_node3;
	byte_t *cpu_baseaddr;
	struct cpu *result;
	cpu_node1 = mnode_create_lockram((size_t)__x86_cpu_part1_pages);
	TRY {
		cpu_node3 = mnode_create_lockram(1);
		TRY {
			sync_write(&vm_kernel);
			cpu_baseaddr = (byte_t *)vm_getfree(&vm_kernel,
			                                    HINT_GETADDR(KERNEL_VMHINT_ALTCORE),
			                                    (size_t)__kernel_percpu_full_bytes, PAGESIZE,
			                                    HINT_GETMODE(KERNEL_VMHINT_ALTCORE));
			if unlikely(cpu_baseaddr == VM_GETFREE_ERROR) {
				sync_endwrite(&vm_kernel);
				THROW(E_BADALLOC_INSUFFICIENT_VIRTUAL_MEMORY,
				      (size_t)__kernel_percpu_full_bytes);
			}
#ifdef ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE
			/* Make sure that the NODE2 portion of the CPU descriptor is always prepared. */
			if (!pagedir_prepare(cpu_baseaddr + (size_t)__x86_cpu_part1_bytes, 2 * PAGESIZE))
				THROW(E_BADALLOC_INSUFFICIENT_PHYSICAL_MEMORY, PAGESIZE);
#endif /* ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE */
		} EXCEPT {
			vm_node_destroy_locked_ram(cpu_node3);
			RETHROW();
		}
	} EXCEPT {
		vm_node_destroy_locked_ram(cpu_node1);
		RETHROW();
	}
	/* Fill in address ranges for CPU nodes. */
	vm_node_setminaddr(cpu_node1, cpu_baseaddr);
	vm_node_setmaxaddr(cpu_node1, cpu_baseaddr + (size_t)__x86_cpu_part1_bytes - 1);
	vm_node_setminaddr(cpu_node3, cpu_baseaddr + (size_t)__x86_cpu_part1_bytes + 2 * PAGESIZE);
	vm_node_setmaxaddr(cpu_node3, cpu_baseaddr + (size_t)__x86_cpu_part1_bytes + 2 * PAGESIZE + PAGESIZE - 1);

	/* Insert the CPU nodes into the kernel VM. */
	vm_node_insert(cpu_node1);
	vm_node_insert(cpu_node3);
	sync_endwrite(&vm_kernel);

	result = (struct cpu *)cpu_baseaddr;

	/* Copy the CPU template. */
	memcpy(result, __kernel_percpu_start, (size_t)__kernel_percpu_size);

	/* Copy the thread-template into the cpu's IDLE thread. */
	memcpy(&FORCPU(result, thiscpu_idle), __kernel_pertask_start, (size_t)__kernel_pertask_size);

	/* Copy the TSS template. */
	memcpy(&FORCPU(result, thiscpu_x86_tss), &__kernel_percpu_tss, SIZEOF_TSS);

#ifndef NDEBUG
	/* Also fill the area before thiscpu_idle with CCh bytes. */
	memset((byte_t *)result + (uintptr_t)__kernel_percpu_size, 0xcc,
	       (size_t)&thiscpu_idle - (size_t)__kernel_percpu_size);

	/* Also fill the area between thiscpu_idle and thiscpu_x86_tss with CCh bytes. */
	memset((byte_t *)result + ((uintptr_t)&thiscpu_idle + (size_t)__kernel_pertask_size), 0xcc,
	       (uintptr_t)&thiscpu_x86_tss - ((uintptr_t)&thiscpu_idle +
	                                 (size_t)__kernel_pertask_size));
#endif /* !NDEBUG */

	/* Fill in the IOB node mapping for this CPU. */
	result = (struct cpu *)cpu_baseaddr;
	cpu_node2 = (struct mnode *)&FORCPU(result, thiscpu_x86_iobnode);
	vm_node_setminaddr(cpu_node2, cpu_baseaddr + (size_t)__x86_cpu_part1_bytes);
	vm_node_setmaxaddr(cpu_node2, cpu_baseaddr + (size_t)__x86_cpu_part1_bytes + PAGESIZE - 1);
#ifdef CONFIG_USE_NEW_VM
	cpu_node2->mn_flags = MNODE_F_PWRITE | MNODE_F_PREAD |
	                      MNODE_F_SHARED | MNODE_F_NOSPLIT |
	                      MNODE_F_NOMERGE | MNODE_F_KERNPART |
	                      MNODE_F_MLOCK | MNODE_F_MPREPARED;
	cpu_node2->mn_mman    = &mman_kernel;
	cpu_node2->mn_part    = NULL; /* Reservation */
	cpu_node2->mn_fspath  = NULL;
	cpu_node2->mn_fsname  = NULL;
	cpu_node2->mn_partoff = 0;
	DBG_memset(&cpu_node2->mn_writable, 0xcc, sizeof(cpu_node2->mn_writable));
	cpu_node2->_mn_module = 0;
#else /* CONFIG_USE_NEW_VM */
	cpu_node2->vn_prot   = VM_PROT_READ | VM_PROT_WRITE | VM_PROT_PRIVATE;
	cpu_node2->vn_flags  = VM_NODE_FLAG_KERNPRT | VM_NODE_FLAG_NOMERGE | VM_NODE_FLAG_PREPARED;
	cpu_node2->vn_vm     = &vm_kernel;
	cpu_node2->vn_part   = NULL; /* Reservation */
	cpu_node2->vn_block  = NULL; /* Reservation */
	cpu_node2->vn_fspath = NULL;
	cpu_node2->vn_fsname = NULL;
	cpu_node2->vn_guard  = 0;
#endif /* !CONFIG_USE_NEW_VM */
	DBG_memset(&cpu_node2->mn_link, 0xcc, sizeof(cpu_node2->mn_link));

	/* Insert the IOB VM node into the kernel VM. */
	sync_write(&vm_kernel); /* Never throws due to early-boot guaranties. */
	vm_node_insert(cpu_node2);
	sync_endwrite(&vm_kernel);

	/* Make sure that the IOB is terminated by a byte containing all ones
	 * NOTE: The remainder of the last page (which is `cpu_node3') is left
	 *       uninitialized, as it is (currently) unused. */
	FORCPU(result, thiscpu_x86_iob_[65536/8]) = 0xff;

#ifndef NDEBUG
	/* Fill unused memory with CCh so that unintended access problems are reproducible. */
	memset(&FORCPU(result, thiscpu_x86_iob_[(65536/8) + 1]), 0xcc, PAGESIZE - 1);
#endif /* !NDEBUG */

	/* Initialize the CPU's pagedir_identity:iob pointer. */
	FORCPU(result, thiscpu_x86_iobnode_pagedir_identity) = x86_get_cpu_iob_pointer(result);

	return result;
}

PRIVATE ATTR_FREETEXT void
NOTHROW(KCALL cpu_free)(struct cpu *__restrict self) {
	/* Release the CPU structure back to the heap. */
	struct mnode *cpu_node1;
	struct mnode *cpu_node2;
	struct mnode *cpu_node3;
	byte_t *cpu_baseaddr;
	assert(IS_ALIGNED((uintptr_t)self, PAGESIZE));
	cpu_baseaddr = (byte_t *)self;
	sync_write(&vm_kernel); /* Never throws due to early-boot guaranties. */
	/* NOTE: Must remove `cpu_node2' first, since that mnode object is actually
	 *       stored inside of `cpu_node1', meaning that once that node is removed,
	 *       the `cpu_node2' descriptor will automatically become invalid! */
	cpu_node2 = vm_node_remove(&vm_kernel, cpu_baseaddr + (size_t)__x86_cpu_part1_bytes);
	COMPILER_BARRIER();
	cpu_node3 = vm_node_remove(&vm_kernel, cpu_baseaddr + (size_t)__x86_cpu_part1_bytes + 2 * PAGESIZE);
	cpu_node1 = vm_node_remove(&vm_kernel, cpu_baseaddr);
#ifdef ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE
	if (!pagedir_prepare(self, ((size_t)__x86_cpu_part1_pages + 3) * PAGESIZE))
		kernel_panic(FREESTR("Failed to prepare pagedir for unmapping CPU descriptor"));
#endif /* ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE */
	pagedir_unmap(self, ((size_t)__x86_cpu_part1_pages + 3) * PAGESIZE);
#ifdef ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE
	pagedir_unprepare(self, ((size_t)__x86_cpu_part1_pages + 3) * PAGESIZE);
#endif /* ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE */
	sync_endwrite(&vm_kernel);
	assert(cpu_node1);
	assert(cpu_node2);
	assert(cpu_node3);
	assert(mnode_getminaddr(cpu_node1) == cpu_baseaddr);
	assert(mnode_getmaxaddr(cpu_node1) == cpu_baseaddr + (size_t)__x86_cpu_part1_bytes - 1);
	/* NOTE: Because we've already removed the nodes from `vm_kernel', we must no longer
	 *       access the `cpu_node2' structure, since the descriptor was contained inside
	 *       of `cpu_node1' */
	/*assert(cpu_node2->vn_node.a_vmin == cpu_node1->vn_node.a_vmax + 1);*/
	/*assert(cpu_node2->vn_node.a_vmax == cpu_node1->vn_node.a_vmax + 2);*/
	assert((byte_t *)mnode_getminaddr(cpu_node3) == (byte_t *)mnode_getendaddr(cpu_node1) + 2 * PAGESIZE);
	assert((byte_t *)mnode_getmaxaddr(cpu_node3) == (byte_t *)mnode_getminaddr(cpu_node3) + PAGESIZE - 1);
	assert(cpu_node2 == &FORCPU(self, thiscpu_x86_iobnode));
	vm_node_destroy_locked_ram(cpu_node1);
	vm_node_destroy_locked_ram(cpu_node3);
}


PRIVATE ATTR_FREETEXT void
NOTHROW(KCALL cpu_destroy)(struct cpu *__restrict self) {
	struct task *myidle;
	myidle = &FORCPU(self, thiscpu_idle);
#ifndef NDEBUG
	ATOMIC_WRITE(myidle->t_refcnt, 0); /* Satisfy assertions... */
#endif /* !NDEBUG */
	{
		/* Run finalizers for the IDLE task. */
		pertask_fini_t *iter;
		iter = __kernel_pertask_fini_start;
		for (; iter < __kernel_pertask_fini_end; ++iter)
			(**iter)(&FORCPU(self, thiscpu_idle));
	}
	/* Unmap, sync, & unprepare the mappings for the CPU's IDLE and #DF stacks.
	 * NOTE: Because these mappings are private the the CPU itself, we don't
	 *       need to be holding a lock to the kernel VM for this part! */
	pagedir_unmap(vm_node_getaddr(&FORCPU(self, thiscpu_x86_dfstacknode_)),
	              vm_node_getsize(&FORCPU(self, thiscpu_x86_dfstacknode_)));
	pagedir_sync(vm_node_getaddr(&FORCPU(self, thiscpu_x86_dfstacknode_)),
	             vm_node_getsize(&FORCPU(self, thiscpu_x86_dfstacknode_)));
#ifdef ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE
	pagedir_unprepare(vm_node_getaddr(&FORCPU(self, thiscpu_x86_dfstacknode_)),
	                  vm_node_getsize(&FORCPU(self, thiscpu_x86_dfstacknode_)));
#endif /* ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE */
	pagedir_unmap(vm_node_getaddr(&FORTASK(myidle, this_kernel_stacknode_)),
	              vm_node_getsize(&FORTASK(myidle, this_kernel_stacknode_)));
	pagedir_sync(vm_node_getaddr(&FORTASK(myidle, this_kernel_stacknode_)),
	             vm_node_getsize(&FORTASK(myidle, this_kernel_stacknode_)));
#ifdef ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE
	pagedir_unprepare(vm_node_getaddr(&FORTASK(myidle, this_kernel_stacknode_)),
	                  vm_node_getsize(&FORTASK(myidle, this_kernel_stacknode_)));
#endif /* ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE */
	pagedir_unmapone(vm_node_getaddr(&FORTASK(myidle, this_trampoline_node)));
	pagedir_syncone(vm_node_getaddr(&FORTASK(myidle, this_trampoline_node)));
#ifdef ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE
	pagedir_unprepareone(vm_node_getaddr(&FORTASK(myidle, this_trampoline_node)));
#endif /* ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE */

	/* Remove the #DF and IDLE stack nodes from the kernel VM */
	while (!mman_lock_tryacquire(&mman_kernel))
		task_pause();
	mman_mappings_removenode(&mman_kernel, &FORCPU(self, thiscpu_x86_dfstacknode_));
	mman_mappings_removenode(&mman_kernel, &FORTASK(myidle, this_kernel_stacknode_));
	mman_mappings_removenode(&mman_kernel, &FORTASK(myidle, this_trampoline_node_));
#ifdef CONFIG_HAVE_KERNEL_STACK_GUARD
	mman_mappings_removenode(&mman_kernel, &FORTASK(myidle, this_kernel_stackguard_));
#endif /* CONFIG_HAVE_KERNEL_STACK_GUARD */
	mman_lock_release(&mman_kernel);
	/* Finalize the associated data parts, freeing up backing physical memory. */
	mpart_ll_freemem(&FORCPU(self, thiscpu_x86_dfstackpart_));
	mpart_ll_freemem(&FORTASK(myidle, this_kernel_stackpart_));
	LIST_REMOVE(myidle, t_mman_tasks);
	cpu_free(self);
}


PRIVATE ATTR_FREETEXT void KCALL
i386_allocate_secondary_cores(void) {
	unsigned int i;
	for (i = 1; i < cpu_count_; ++i) {
		struct cpu *altcore;
		struct task *altidle;
		/* Allocate an initialize the alternative core. */
		altcore = cpu_alloc();
		altidle = &FORCPU(altcore, thiscpu_idle);
		/* Decode information previously encoded in `smp.c' */
		FORCPU(altcore, thiscpu_x86_lapicid_)      = (uintptr_t)cpu_vector_[i] & 0xff;
		FORCPU(altcore, thiscpu_x86_lapicversion_) = ((uintptr_t)cpu_vector_[i] & 0xff00) >> 8;
		cpu_vector_[i] = altcore;

		altcore->c_id                          = i;
		FORCPU(altcore, thiscpu_sched_current) = altidle;
		altidle->t_cpu                         = altcore;
		altidle->t_self                        = altidle;
		altidle->t_flags                       = TASK_FSTARTED | TASK_FRUNNING | TASK_FKEEPCORE | TASK_FCRITICAL;
		FORCPU(altcore, thiscpu_scheduler).s_runcount         = 1;
		FORCPU(altcore, thiscpu_scheduler).s_running.lh_first = altidle;
		FORCPU(altcore, thiscpu_scheduler).s_running_last     = altidle;
		/*FORCPU(altcore, thiscpu_scheduler).s_waiting_last = NULL;*/
		FORTASK(altidle, this_sched_link).le_prev = &FORCPU(altcore, thiscpu_scheduler).s_running.lh_first;
		/*FORTASK(altidle, this_sched_link).ln_next = NULL;*/

		/* Insert the new task into the kernel VM's task user list. */
		LIST_INSERT_HEAD(&vm_kernel.v_tasks, altidle, t_mman_tasks);

		/* Allocate & map stacks for this cpu's IDLE task, as well as the #DF stack. */
		FORCPU(altcore, thiscpu_x86_dfstacknode_).vn_part          = &FORCPU(altcore, thiscpu_x86_dfstackpart_);
		FORCPU(altcore, thiscpu_x86_dfstacknode_).vn_link.ln_pself = &LLIST_HEAD(FORCPU(altcore, thiscpu_x86_dfstackpart_).dp_srefs);
		FORCPU(altcore, thiscpu_x86_dfstackpart_).dp_srefs         = &FORCPU(altcore, thiscpu_x86_dfstacknode_);
		vm_datapart_do_allocram(&FORCPU(altcore, thiscpu_x86_dfstackpart_));
		{
			byte_t *addr;
			addr = (byte_t *)vm_getfree(&vm_kernel,
			                            HINT_GETADDR(KERNEL_VMHINT_DFSTACK),
			                            CEIL_ALIGN(KERNEL_DF_STACKSIZE, PAGESIZE), PAGESIZE,
			                            HINT_GETMODE(KERNEL_VMHINT_DFSTACK));
			if unlikely(addr == VM_GETFREE_ERROR)
				kernel_panic(FREESTR("Failed to find suitable location for CPU #%u's #DF stack"), (unsigned int)i);
			vm_node_setminaddr(&FORCPU(altcore, thiscpu_x86_dfstacknode_), addr);
			vm_node_setmaxaddr(&FORCPU(altcore, thiscpu_x86_dfstacknode_), addr + KERNEL_DF_STACKSIZE - 1);
#ifdef ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE
			if (!pagedir_prepare(addr, CEIL_ALIGN(KERNEL_DF_STACKSIZE, PAGESIZE)))
				kernel_panic(FREESTR("Failed to map CPU #%u's #DF stack"), (unsigned int)i);
#endif /* ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE */
			vm_datapart_map_ram(&FORCPU(altcore, thiscpu_x86_dfstackpart_),
			                    addr,
			                    PAGEDIR_MAP_FREAD | PAGEDIR_MAP_FWRITE);
			vm_node_insert(&FORCPU(altcore, thiscpu_x86_dfstacknode_));
			addr = (byte_t *)addr + KERNEL_DF_STACKSIZE;
			/* Store the DF stack pointer in internal CPU structures. */
#ifdef __x86_64__
			FORCPU(altcore, thiscpu_x86_tss).t_ist1 = (u64)addr;
			FORCPU(altcore, thiscpu_x86_tss).t_ist2 = (u64)addr;
			FORCPU(altcore, thiscpu_x86_tss).t_ist3 = (u64)addr;
			FORCPU(altcore, thiscpu_x86_tss).t_ist4 = (u64)addr;
			FORCPU(altcore, thiscpu_x86_tss).t_ist5 = (u64)addr;
			FORCPU(altcore, thiscpu_x86_tss).t_ist6 = (u64)addr;
			FORCPU(altcore, thiscpu_x86_tss).t_ist7 = (u64)addr;
#else /* __x86_64__ */
			FORCPU(altcore, thiscpu_x86_tssdf).t_esp0 = (u32)addr;
			FORCPU(altcore, thiscpu_x86_tssdf).t_esp1 = (u32)addr;
			FORCPU(altcore, thiscpu_x86_tssdf).t_esp2 = (u32)addr;
			/* Fill in cpu-specific pointers needed by the implementation of the #DF handler! */
			FORCPU(altcore, thiscpu_x86_tssdf).t_ebx = (u32)altcore;
			FORCPU(altcore, thiscpu_x86_tssdf).t_esp = (u32)addr;
			FORCPU(altcore, thiscpu_x86_tssdf).t_ebp = (u32)&FORCPU(altcore, thiscpu_x86_tss);
#endif /* !__x86_64__ */
		}

#ifdef CONFIG_USE_NEW_VM
		FORTASK(altidle, this_kernel_stackpart_).mp_maxaddr = (pos_t)(KERNEL_IDLE_STACKSIZE - 1);
#else /* CONFIG_USE_NEW_VM */
		FORTASK(altidle, this_kernel_stackpart_).dp_tree.a_vmax = (datapage_t)(CEILDIV(KERNEL_IDLE_STACKSIZE, PAGESIZE) - 1);
#endif /* !CONFIG_USE_NEW_VM */
		/* The stack of IDLE threads is executable in order to allow for hacking around .free restrictions. */
		FORTASK(altidle, this_kernel_stacknode_).vn_prot = (VM_PROT_EXEC | VM_PROT_WRITE | VM_PROT_READ);

#define REL(x) ((x) = (__typeof__(x))(uintptr_t)((byte_t *)(x) + (uintptr_t)altidle))
		REL(FORTASK(altidle, this_kernel_stacknode_).vn_part);
		REL(FORTASK(altidle, this_kernel_stacknode_).vn_link.ln_pself);
		REL(FORTASK(altidle, this_kernel_stackpart_).dp_srefs);
#undef REL
		vm_datapart_do_allocram(&FORTASK(altidle, this_kernel_stackpart_));
		{
			byte_t *addr;
#ifdef CONFIG_HAVE_KERNEL_STACK_GUARD
			addr = (byte_t *)vm_getfree(&vm_kernel,
			                            HINT_GETADDR(KERNEL_VMHINT_IDLESTACK),
			                            CEIL_ALIGN(KERNEL_IDLE_STACKSIZE, PAGESIZE) + PAGESIZE,
			                            PAGESIZE, HINT_GETMODE(KERNEL_VMHINT_IDLESTACK));
#else /* CONFIG_HAVE_KERNEL_STACK_GUARD */
			addr = (byte_t *)vm_getfree(&vm_kernel,
			                            HINT_GETADDR(KERNEL_VMHINT_IDLESTACK),
			                            CEIL_ALIGN(KERNEL_IDLE_STACKSIZE, PAGESIZE), PAGESIZE,
			                            HINT_GETMODE(KERNEL_VMHINT_IDLESTACK));
#endif /* !CONFIG_HAVE_KERNEL_STACK_GUARD */
			if unlikely(addr == (byte_t *)VM_GETFREE_ERROR)
				kernel_panic(FREESTR("Failed to find suitable location for CPU #%u's IDLE stack"), (unsigned int)i);
#ifdef CONFIG_HAVE_KERNEL_STACK_GUARD
			vm_node_setminaddr(&FORTASK(altidle, this_kernel_stackguard_), addr);
			vm_node_setmaxaddr(&FORTASK(altidle, this_kernel_stackguard_), addr + PAGESIZE - 1);
			addr += PAGESIZE;
#endif /* CONFIG_HAVE_KERNEL_STACK_GUARD */
			vm_node_setminaddr(&FORTASK(altidle, this_kernel_stacknode_), addr);
			vm_node_setmaxaddr(&FORTASK(altidle, this_kernel_stacknode_), addr + KERNEL_IDLE_STACKSIZE - 1);

#ifdef ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE
			if (!pagedir_prepare(addr, CEIL_ALIGN(KERNEL_IDLE_STACKSIZE, PAGESIZE)))
				kernel_panic(FREESTR("Failed to map CPU #%u's IDLE stack"), (unsigned int)i);
#endif /* ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE */
			vm_datapart_map_ram(&FORTASK(altidle, this_kernel_stackpart_),
			                    addr,
			                    PAGEDIR_MAP_FREAD | PAGEDIR_MAP_FWRITE);
			vm_node_insert(&FORTASK(altidle, this_kernel_stacknode_));
#ifdef CONFIG_HAVE_KERNEL_STACK_GUARD
			vm_node_insert(&FORTASK(altidle, this_kernel_stackguard_));
#endif /* CONFIG_HAVE_KERNEL_STACK_GUARD */
		}

		{
			byte_t *addr;
			addr = (byte_t *)vm_getfree(&vm_kernel,
			                            HINT_GETADDR(KERNEL_VMHINT_TRAMPOLINE), PAGESIZE, PAGESIZE,
			                            HINT_GETMODE(KERNEL_VMHINT_TRAMPOLINE));
			if unlikely(addr == (byte_t *)VM_GETFREE_ERROR)
				kernel_panic(FREESTR("Failed to find suitable location for CPU #%u's IDLE trampoline"), (unsigned int)i);
			vm_node_setminaddr(&FORTASK(altidle, this_trampoline_node), addr);
			vm_node_setmaxaddr(&FORTASK(altidle, this_trampoline_node), addr + PAGESIZE - 1);
#ifdef ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE
			if unlikely(!pagedir_prepareone(addr))
				kernel_panic(FREESTR("Failed to prepare CPU #%u's IDLE trampoline"), (unsigned int)i);
#endif /* ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE */
			vm_node_insert(&FORTASK(altidle, this_trampoline_node));
		}

		FORTASK(altidle, this_fs)             = incref(&fs_kernel);
		FORTASK(altidle, this_handle_manager) = incref(&handle_manager_kernel);

		/* Set up the boot-strap CPU state for the new CPU.
		 * -> When a CPU is started by using an INIT IPI, it will perform internal setup
		 *    functions before executing `FORTASK(PERCPU(thiscpu_sched_current), this_sstate)'
		 *    Since this is the first time that we're starting this CPU, we direct
		 *    that state to perform some high-level CPU initialization functions,
		 *    such as determining CPU features (and comparing those against those
		 *    implement by the boot CPU in order to determine the features available
		 *    by the lowest common denominator), before shutting down again, until
		 *    some future point in time when the CPU will be used again. */
		{
			struct scpustate *init_state;
			init_state = (struct scpustate *)((byte_t *)vm_node_getendaddr(&FORTASK(altidle, this_kernel_stacknode_)) -
			                                  (offsetafter(struct scpustate, scs_irregs) + sizeof(void *)));
			memset(init_state, 0, offsetafter(struct scpustate, scs_irregs));
			/* Set the return address to execute the IDLE main loop. */
			*(void **)((byte_t *)init_state + offsetafter(struct scpustate, scs_irregs)) = (void *)&cpu_idlemain;
#ifdef __x86_64__
			init_state->scs_irregs.ir_cs     = SEGMENT_KERNEL_CODE;
			init_state->scs_irregs.ir_rip    = (u64)&x86_altcore_entry;
			init_state->scs_irregs.ir_ss     = SEGMENT_KERNEL_DATA0;
			init_state->scs_irregs.ir_rsp    = (u64)(init_state + 1);
			init_state->scs_sgregs.sg_ds     = SEGMENT_USER_DATA_RPL;
			init_state->scs_sgregs.sg_es     = SEGMENT_USER_DATA_RPL;
			init_state->scs_sgregs.sg_fs     = SEGMENT_USER_DATA_RPL;
			init_state->scs_sgregs.sg_gs     = SEGMENT_USER_DATA_RPL;
			init_state->scs_sgbase.sg_gsbase = (u64)altidle;
#else /* __x86_64__ */
			init_state->scs_irregs_k.ir_cs  = SEGMENT_KERNEL_CODE;
			init_state->scs_irregs_k.ir_eip = (u32)&x86_altcore_entry;
			init_state->scs_sgregs.sg_ds    = SEGMENT_USER_DATA_RPL;
			init_state->scs_sgregs.sg_es    = SEGMENT_USER_DATA_RPL;
			init_state->scs_sgregs.sg_fs    = SEGMENT_KERNEL_FSBASE;
			init_state->scs_sgregs.sg_gs    = SEGMENT_USER_GSBASE_RPL;
#endif /* !__x86_64__ */
			FORTASK(altidle, this_sstate) = init_state;
		}

		/* Run per-task initializers on the new cpu's IDLE thread. */
		{
			pertask_init_t *iter = __kernel_pertask_init_start;
			for (; iter < __kernel_pertask_init_end; ++iter)
				(**iter)(altidle);
		}

		/* Setup additional properties of the CPU */
		segment_wrbaseX(&FORCPU(altcore, thiscpu_x86_gdt[SEGMENT_INDEX(SEGMENT_CPU_TSS)]),
		                (uintptr_t)&FORCPU(altcore, thiscpu_x86_tss));
		segment_wrbaseX(&FORCPU(altcore, thiscpu_x86_gdt[SEGMENT_INDEX(SEGMENT_CPU_LDT)]),
		                (uintptr_t)&FORCPU(altcore, thiscpu_x86_ldt));
#ifndef __x86_64__
		segment_wrbaseX(&FORCPU(altcore, thiscpu_x86_gdt[SEGMENT_INDEX(SEGMENT_CPU_TSS_DF)]),
		                (uintptr_t)&FORCPU(altcore, thiscpu_x86_tssdf));
		segment_wrbaseX(&FORCPU(altcore, thiscpu_x86_gdt[SEGMENT_INDEX(SEGMENT_KERNEL_FSBASE)]),
		                (uintptr_t)altidle);
#endif /* !__x86_64__ */
		FORCPU(altcore, thiscpu_x86_tss.t_psp0) = FORTASK(altidle, this_x86_kernel_psp0);

		/* Have the CPU load the proper GDT during the initial startup.
		 * All of the other `thiscpu_x86_saved_*' registers already have
		 * their proper values as the result of static initialization! */
		FORCPU(altcore, thiscpu_x86_saved_gdtr.dt_base) = (uintptr_t)FORCPU(altcore, thiscpu_x86_gdt);
	}
}

#endif /* !CONFIG_NO_SMP */


#ifdef __HAVE_CPUSET_FULL_MASK
DATDEF cpuset_t ___cpuset_full_mask ASMNAME("__cpuset_full_mask");
#endif /* __HAVE_CPUSET_FULL_MASK */


#ifndef CONFIG_HAVE_DEBUGGER
INTERN ATTR_FREETEXT void NOTHROW(KCALL x86_initialize_pic)(void)
#else /* !CONFIG_HAVE_DEBUGGER */
/* The debugger calls this function during init,
 * so we can't mark it as ATTR_FREETEXT */
INTERN void NOTHROW(KCALL x86_initialize_pic)(void)
#endif /* CONFIG_HAVE_DEBUGGER */
{
	/* >> (re-)initialize the master & slave PICs.
	 * Following this, each PIC will expect 3 additional "initialization words". */
	outb_p(X86_PIC1_CMD, X86_ICW1_INIT | X86_ICW1_ICW4);
	outb_p(X86_PIC2_CMD, X86_ICW1_INIT | X86_ICW1_ICW4);

	/* Word #2: Define the IRQ offsets. */
	outb_p(X86_PIC1_DATA, X86_INTERRUPT_PIC1_BASE);
	outb_p(X86_PIC2_DATA, X86_INTERRUPT_PIC2_BASE);

	/* Word #3: Tell the master and slave how they are wired to each other. */
	outb_p(X86_PIC1_DATA, 4);
	outb_p(X86_PIC2_DATA, 2);

	/* Word #4: Define the environment mode. */
	outb_p(X86_PIC1_DATA, X86_ICW4_8086);
	outb_p(X86_PIC2_DATA, X86_ICW4_8086);

#ifdef CONFIG_HAVE_DEBUGGER
	/* This function should only ever be called once (I've seen the
	 * PIC stop working properly if it's initialized more than once...)
	 * To ensure this, we re-write our own entry-point with a ret-instruction. */
	*(u8 *)(void *)&x86_initialize_pic = 0xc3; /* ret */
#endif /* CONFIG_HAVE_DEBUGGER */
}

extern byte_t x86_arch_cpu_hwipi_pending_nopr[] ASMNAME("arch_cpu_hwipi_pending_nopr");

#ifndef CONFIG_NO_SMP
INTERN ATTR_FREETEXT void KCALL pit_delay_hz(u16 hz) {
	x86_pit_lock_acquire_nopr();
	outb(PIT_COMMAND,
	     PIT_COMMAND_SELECT_F1 |
	     PIT_COMMAND_ACCESS_FLOHI |
	     PIT_COMMAND_MODE_FONESHOT |
	     PIT_COMMAND_FBINARY);
	/* Configure the PIT to trigger after 1/100th of a second (10ms). */
	outb_p(PIT_DATA1, hz & 0xff);
	outb(PIT_DATA1, (hz >> 8) & 0xff);
	outb(PIT_COMMAND, PIT_COMMAND_SELECT_F1 | PIT_COMMAND_ACCESS_FHI |
	                  PIT_COMMAND_MODE_FONESHOT | PIT_COMMAND_FBINARY);
	while (inb(PIT_DATA1))
		task_pause();
	outb(PIT_COMMAND, PIT_COMMAND_SELECT_F1 | PIT_COMMAND_ACCESS_FLO |
	                  PIT_COMMAND_MODE_FONESHOT | PIT_COMMAND_FBINARY);
	while (inb(PIT_DATA1))
		task_pause();
	x86_pit_lock_release_nopr();
}
#endif /* !CONFIG_NO_SMP */


INTERN ATTR_FREETEXT void NOTHROW(KCALL x86_initialize_apic)(void) {

	/* Initialize the regular PIC */
	x86_initialize_pic();

	/* Check if we should make use of the LAPIC */
	if (X86_HAVE_LAPIC) {
#ifndef CONFIG_NO_SMP
		unsigned int i;
		if (cpu_count_ > 1) {
			physpage_t entry_page;
			/* Allocate low physical memory for the SMP initialization entry page. */
			entry_page = page_malloc_between((physpage_t)((physaddr_t)0x00000000 / PAGESIZE),
			                                 (physpage_t)((physaddr_t)0x000fffff / PAGESIZE),
			                                 CEILDIV(x86_smp_entry_size, PAGESIZE));
			if unlikely(entry_page == PHYSPAGE_INVALID) {
				printk(FREESTR(KERN_WARNING "[smp] Failed to allocate SMP trampoline (re-configure for single-core mode)\n"));
				cpu_count_ = 1;
#ifdef __HAVE_CPUSET_FULL_MASK
				CPUSET_SETONE(___cpuset_full_mask, 0); /* 0 == BOOTCPU_ID */
#endif /* __HAVE_CPUSET_FULL_MASK */
				goto done_early_altcore_init;
			}
			printk(FREESTR(KERN_INFO "[smp] Allocating SMP trampoline at %" PRIpN(__SIZEOF_PHYSADDR_T__) "\n"),
			       physpage2addr(entry_page));
			x86_smp_entry_page = (u8)entry_page;
			/* Apply some custom AP entry relocations. */
			{
				u32 gdt_addr;
				gdt_addr = (u32)(x86_smp_gdt - x86_smp_entry);
				gdt_addr += physpage2addr32(entry_page);
				x86_smp_entry_gdt_segment = (gdt_addr & 0xf0000) >> 4;
				x86_smp_entry_gdt_offset  = (gdt_addr & 0x0ffff);
				x86_smp_gdt_pointer_base += physpage2addr32(entry_page);
			}
			COMPILER_WRITE_BARRIER();
			/* Copy AP entry code. */
			vm_copytophys(physpage2addr(entry_page),
			              x86_smp_entry,
			              x86_smp_entry_size);
	
			/* Allocate control structures for secondary cores. */
			i386_allocate_secondary_cores();
		}
done_early_altcore_init:
#endif /* !CONFIG_NO_SMP */

		/* Read out the boot cpu's LAPIC id if it couldn't be determined before now. */
		if (FORCPU(&_bootcpu, thiscpu_x86_lapicid_) == 0xff) {
			u32 id = lapic_read(APIC_ID);
			FORCPU(&_bootcpu, thiscpu_x86_lapicid_) = (u8)(id >> APIC_ID_FSHIFT);
		}

		/* Disable the PIT interrupt if we're going to use the LAPIC timer. */
		outb_p(X86_PIC1_DATA, 1);
		outb_p(X86_PIC2_DATA, 0);

		lapic_write(APIC_SPURIOUS,
		            APIC_SPURIOUS_FENABLED |
		            X86_INTERRUPT_APIC_SPURIOUS);
#ifndef CONFIG_NO_SMP
		assert(CPU_ALL_ONLINE);
		/* Send INIT commands to all CPUs. */
		for (i = 1; i < cpu_count_; ++i) {
			cpu_offline_mask[i / 8] |= 1 << (i % 8); /* Mark the CPU as offline */
			apic_send_init(FORCPU(cpu_vector[i], thiscpu_x86_lapicid));
		}
		/* NOTE: The APIC specs require us to wait for 10ms
		 *       before we should send `APIC_ICR0_TYPE_FSIPI'
		 *       And wouldn't you know, that's also the time that
		 *       our LAPIC calibration code needs to determine the
		 *       frequency of the BSP's LAPIC timer.
		 *       So we just merge the two together to speed
		 *       up boot time by just that tiny bit more. */
#endif /* !CONFIG_NO_SMP */

		/* Calibrate the APIC */
		x86_calibrate_boottsc();
#ifndef CONFIG_NO_SMP
		/* Send start IPIs to all APs. */
		for (i = 1; i < cpu_count_; ++i) {
			apic_send_startup(FORCPU(cpu_vector[i], thiscpu_x86_lapicid),
			                  x86_smp_entry_page);
		}
#endif /* !CONFIG_NO_SMP */

#ifndef CONFIG_NO_SMP
		/* Wait for secondary CPUs to come online. */
		if (!CPU_ALL_ONLINE) {
			unsigned int timeout;
			/* Wait for 1 ms (or 1/1000'th of a second) */
			pit_delay_hz(PIT_HZ_DIV(1000));
			if likely(CPU_ALL_ONLINE)
				goto all_online;
			/* Re-send start IPIs to all APs still not online. */
			for (i = 1; i < cpu_count_; ++i) {
				if (!(ATOMIC_READ(cpu_offline_mask[i / 8]) & (1 << (i % 8))))
					continue;
				printk(FREESTR(KERN_WARNING "[smp] Re-attempting startup of processor #%u (LAPIC id %#.2" PRIx8 ")\n"),
				       i, FORCPU(cpu_vector[i], thiscpu_x86_lapicid));
				apic_send_startup(FORCPU(cpu_vector[i], thiscpu_x86_lapicid),
				                  x86_smp_entry_page);
			}
			/* Wait up to a full second for the (possibly slow?) CPUs to come online. */
			for (timeout = 0; timeout < 20; ++timeout) {
				if (CPU_ALL_ONLINE)
					goto all_online;
				pit_delay_hz(PIT_HZ_DIV(20));
			}
			/* Check one last time? */
			if (CPU_ALL_ONLINE)
				goto all_online;
			/* Guess these CPUs are just broken... */
			for (i = 1; i < cpu_count_;) {
				struct cpu *discard_cpu;
				discard_cpu       = cpu_vector_[i];
				discard_cpu->c_id = i; /* Re-assign CPU IDs to reflect removed entries. */
				if (!(ATOMIC_READ(cpu_offline_mask[i / 8]) & (1 << (i % 8)))) {
					++i;
					continue;
				}
				printk(FREESTR(KERN_ERR "[smp] CPU with LAPIC id %#.2" PRIx8 " doesn't want to "
				                        "come online (removing it from the configuration)\n"),
				       i, FORCPU(cpu_vector_[i], thiscpu_x86_lapicid));
				cpu_destroy(cpu_vector_[i]);
				/* Remove the CPU from the vector. */
				--cpu_count_;
				memmovedown(&cpu_vector_[i], &cpu_vector_[i + 1],
				            cpu_count_ - i, sizeof(struct cpu *));
			}
		}
all_online:
		;
#ifdef __HAVE_CPUSET_FULL_MASK
		___cpuset_full_mask = ((cpuset_t)1 << cpu_count_) - 1;
#endif /* __HAVE_CPUSET_FULL_MASK */
#endif /* !CONFIG_NO_SMP */
	} else {
		printk(FREESTR(KERN_INFO "[smp] LAPIC unavailable or disabled\n"));

		/* Ensure that we're configured for only a single CPU */
		cpu_count_ = 1;
#ifdef __HAVE_CPUSET_FULL_MASK
		CPUSET_SETONE(___cpuset_full_mask, 0); /* 0 == BOOTCPU_ID */
#endif /* __HAVE_CPUSET_FULL_MASK */

		/* Enable all interrupts. */
		outb_p(X86_PIC1_DATA, 0);
		outb_p(X86_PIC2_DATA, 0);

		/* Have `arch_cpu_hwipi_pending_nopr()' immediatly return `false' */
		x86_arch_cpu_hwipi_pending_nopr[0] = 0x31; /* xorl */
		x86_arch_cpu_hwipi_pending_nopr[1] = 0xc0; /* %eax, %eax */
		x86_arch_cpu_hwipi_pending_nopr[2] = 0xc3; /* ret */
	}
	PREEMPTION_ENABLE();
}


DECL_END

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_SCHED_APIC_C */
