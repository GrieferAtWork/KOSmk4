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
#include <sched/task.h>
#include <sched/x86/cpureg.h>
#include <sched/x86/smp.h>
#include <sched/x86/tss.h>

#include <hybrid/align.h>
#include <hybrid/atomic.h>

#include <asm/intrin.h>
#include <kos/kernel/cpu-state.h>
#include <kos/kernel/tss-compat.h>
#include <kos/kernel/tss.h>
#include <sys/param.h> /* HZ */

#include <assert.h>
#include <stddef.h>
#include <string.h>

DECL_BEGIN

#ifndef CONFIG_NO_SMP
/* Lock used to synchronize access to the PIT. */
PUBLIC struct atomic_rwlock x86_pit_lock = ATOMIC_RWLOCK_INIT;
#endif /* !CONFIG_NO_SMP */

INTDEF byte_t x86_pic_acknowledge[];
#ifdef CONFIG_HAVE_DEBUGGER
INTDEF byte_t x86_debug_pic_acknowledge[];
#endif /* CONFIG_HAVE_DEBUGGER */

INTDEF byte_t x86_ack_pic[];
INTDEF byte_t x86_ack_apic[];
INTDEF byte_t x86_ack_apic_size[];


DATDEF ATTR_PERCPU quantum_diff_t _thiscpu_quantum_length ASMNAME("thiscpu_quantum_length");
DATDEF ATTR_PERCPU u8 _thiscpu_x86_lapicid ASMNAME("thiscpu_x86_lapicid");
DATDEF ATTR_PERCPU u8 _thiscpu_x86_lapicversion ASMNAME("thiscpu_x86_lapicversion");
DATDEF size_t _cpu_count ASMNAME("cpu_count");
DATDEF struct cpu *_cpu_vector[CONFIG_MAX_CPU_COUNT] ASMNAME("cpu_vector");


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

PRIVATE NOBLOCK void NOTHROW(KCALL x86_calibrate_apic_with_pic)(void) {
	u8 temp;
	/* Make sure that the speaker is off and disconnected. */
	temp = inb(PIT_PCSPEAKER);
	outb(PIT_PCSPEAKER, temp & ~(PIT_PCSPEAKER_FSYNCPIT |
	                             PIT_PCSPEAKER_FINOUT));
	/* Wait until the speaker moves to the in-position */
	for (;;) {
		temp = inb(PIT_PCSPEAKER);
		if (!(temp & PIT_PCSPEAKER_OUT))
			break;
		__pause();
	}
	outb(PIT_COMMAND,
	     PIT_COMMAND_SELECT_F2 |
	     PIT_COMMAND_ACCESS_FLOHI |
	     PIT_COMMAND_MODE_FONESHOT |
	     PIT_COMMAND_FBINARY);
	/* Configure the PIT to trigger after 1/100th of a second (10ms). */
	outb_p(PIT_DATA2, (PIT_HZ_DIV(100) & 0xff));
	outb(PIT_DATA2, (PIT_HZ_DIV(100) >> 8) & 0xff);
	/*  Move the speaker to trigger the one-shot timer.
	 * (This is what I call a hack from the last century!) */
	outb(PIT_PCSPEAKER, temp | (PIT_PCSPEAKER_OUT |
	                            PIT_PCSPEAKER_FSYNCPIT));
	/* The PIC timer is now running. */
	/* Set LAPIC counter to its maximum possible value. */
	lapic_write(APIC_TIMER_INITIAL, (u32)-1);
	COMPILER_BARRIER();

	/* Wait for our one-shot time to expire. */
	while (inb(PIT_PCSPEAKER) & PIT_PCSPEAKER_FPIT2OUT)
		__pause();
	/* Turn off the APIC timer. */
	lapic_write(APIC_TIMER, APIC_TIMER_FDISABLED);
	/* Make sure to disable the speaker once again. */
	outb(PIT_PCSPEAKER, temp & ~(PIT_PCSPEAKER_FSYNCPIT |
	                             PIT_PCSPEAKER_FINOUT));
}


/* TODO: This function being apart of the .free section is unsafe!
 *       The boot core may move on to unmap the .free section while
 *       a secondary core still performing initialization in here! */
PRIVATE /*ATTR_FREETEXT*/ void KCALL x86_altcore_entry(void) {
	u32 num_ticks;
	struct cpu *me = THIS_CPU;
	cpuid_t id     = me->c_id;

	/* Disable the APIC timer again, which had already
	 * been enabled during SMP bootstrapping */
	lapic_write(APIC_TIMER, APIC_TIMER_FDISABLED);

	/* C-level entry point for secondary SMP cores. */
	printk(/*FREESTR*/ (KERN_INFO "[smp] Begin CPU #%u initialization\n"), id);

	/* Tell the boot-cpu that we're now online. */
	ATOMIC_FETCHAND(cpu_offline_mask[id / 8], ~(1 << (id % 8)));

	/* Same as what the BOOT processor does to configure its LAPIC. */
	while (!sync_trywrite(&x86_pit_lock))
		__pause();
	lapic_write(APIC_TIMER_DIVIDE, APIC_TIMER_DIVIDE_F16);
	lapic_write(APIC_TIMER, 0xff | APIC_TIMER_MODE_FONESHOT);
	x86_calibrate_apic_with_pic();
	sync_endwrite(&x86_pit_lock);
	num_ticks = lapic_read(APIC_TIMER_CURRENT);
	num_ticks = (((u32)-1) - num_ticks) * 100;
	num_ticks /= HZ;
	if unlikely(!num_ticks)
		num_ticks = 1;
	printk(/*FREESTR*/ (KERN_INFO "[apic] CPU #%u has a quantum length of %I32u units\n"),
	       me->c_id, num_ticks);
	/* TODO: If `num_ticks' differs from `FORCPU(&_bootcpu,_thiscpu_quantum_length)'
	 *       by more than 1%, re-try the calibration up to 2 more times.
	 *    -> Mainly affects emulators when the bus-clock is based on real
	 *       time, but the emulator itself may have been preempted while
	 *       it was hosting our calibration code.
	 *    -> This is something I've seen happening a couple of times, leaving
	 *       secondary cores to arbitrarily have tick counters off by _a_ _lot_. */

	cpu_set_quantum_length(num_ticks);

	/* Enable the LAPIC for real this time. */
	lapic_write(APIC_TIMER_DIVIDE, APIC_TIMER_DIVIDE_F16);
	lapic_write(APIC_TIMER,
	            X86_INTNO_PIC1_PIT |
	            APIC_TIMER_MODE_FPERIODIC);
	lapic_write(APIC_TIMER_INITIAL, num_ticks);
	FORCPU(me, arch_cpu_preemptive_interrupts_disabled) = false;
}




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


DATDEF ATTR_PERCPU struct vm_node thiscpu_x86_dfstacknode_ ASMNAME("thiscpu_x86_dfstacknode");
DATDEF ATTR_PERCPU struct vm_datapart thiscpu_x86_dfstackpart_ ASMNAME("thiscpu_x86_dfstackpart");
DATDEF ATTR_PERTASK struct vm_node this_kernel_stacknode_ ASMNAME("this_kernel_stacknode");
DATDEF ATTR_PERTASK struct vm_datapart this_kernel_stackpart_ ASMNAME("this_kernel_stackpart");
DATDEF ATTR_PERCPU u8 thiscpu_x86_iob_[] ASMNAME("thiscpu_x86_iob");

#define HINT_ADDR(x, y) x
#define HINT_MODE(x, y) y
#define HINT_GETADDR(x) HINT_ADDR x
#define HINT_GETMODE(x) HINT_MODE x

PRIVATE ATTR_FREETEXT REF struct vm_datapart *KCALL
vm_datapart_alloc_locked_ram(size_t num_pages) {
	REF struct vm_datapart *result;
	result = (struct vm_datapart *)kmalloc(sizeof(struct vm_datapart),
	                                       GFP_LOCKED | GFP_PREFLT);
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
	return result;
}

PRIVATE ATTR_FREETEXT struct vm_node *KCALL
vm_node_alloc_locked_ram(size_t num_pages) {
	struct vm_node *result;
	REF struct vm_datapart *part;
	part = vm_datapart_alloc_locked_ram(num_pages);
	TRY {
		result = (struct vm_node *)kmalloc(sizeof(struct vm_node),
		                                   GFP_LOCKED | GFP_PREFLT);
	} EXCEPT {
		decref_likely(part);
		RETHROW();
	}
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
	return result;
}

PRIVATE NOBLOCK ATTR_FREETEXT void
NOTHROW(KCALL vm_node_destroy_locked_ram)(struct vm_node *__restrict self) {
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
#else
#define x86_get_cpu_iob_pointer(self)                                   \
	(X86_PAGEDIR_USES_P32() ? (void *)x86_get_cpu_iob_pointer_p32(self) \
	                        : (void *)x86_get_cpu_iob_pointer_pae(self))
#endif
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
	struct vm_node *cpu_node1;
	struct vm_node *cpu_node2;
	struct vm_node *cpu_node3;
	void *cpu_baseaddr;
	struct cpu *result;
	cpu_node1 = vm_node_alloc_locked_ram((size_t)__x86_cpu_part1_pages);
	TRY {
		cpu_node3 = vm_node_alloc_locked_ram(1);
		TRY {
			sync_write(&vm_kernel);
			cpu_baseaddr = vm_getfree(&vm_kernel,
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
			if (!pagedir_prepare_map((byte_t *)cpu_baseaddr + (size_t)__x86_cpu_part1_pages * PAGESIZE, 2 * PAGESIZE))
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
	cpu_node1->vn_node.a_vmin = PAGEID_ENCODE((byte_t *)cpu_baseaddr);
	cpu_node1->vn_node.a_vmax = PAGEID_ENCODE((byte_t *)cpu_baseaddr + ((size_t)__x86_cpu_part1_pages - 1) * PAGESIZE);
	cpu_node3->vn_node.a_vmin = cpu_node1->vn_node.a_vmax + 3;
	cpu_node3->vn_node.a_vmax = cpu_node3->vn_node.a_vmin;

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
	cpu_node2 = &FORCPU(result, thiscpu_x86_iobnode);
	cpu_node2->vn_node.a_vmin = PAGEID_ENCODE((byte_t *)cpu_baseaddr + (size_t)__x86_cpu_part1_pages * PAGESIZE);
	cpu_node2->vn_node.a_vmax = cpu_node2->vn_node.a_vmin + 1;
	cpu_node2->vn_prot   = VM_PROT_READ | VM_PROT_WRITE | VM_PROT_PRIVATE;
	cpu_node2->vn_flags  = VM_NODE_FLAG_KERNPRT | VM_NODE_FLAG_NOMERGE | VM_NODE_FLAG_PREPARED;
	cpu_node2->vn_vm     = &vm_kernel;
	cpu_node2->vn_part   = NULL; /* Reservation */
	cpu_node2->vn_block  = NULL; /* Reservation */
	cpu_node2->vn_fspath = NULL;
	cpu_node2->vn_fsname = NULL;
	cpu_node2->vn_guard  = 0;
#ifndef NDEBUG
	memset(&cpu_node2->vn_link, 0xcc, sizeof(cpu_node2->vn_link));
#endif /* !NDEBUG */

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
	struct vm_node *cpu_node1;
	struct vm_node *cpu_node2;
	struct vm_node *cpu_node3;
	pageid_t cpu_basepage;
	assert(IS_ALIGNED((uintptr_t)self, PAGESIZE));
	cpu_basepage = PAGEID_ENCODE(self);
	sync_write(&vm_kernel); /* Never throws due to early-boot guaranties. */
	/* NOTE: Must remove `cpu_node2' first, since that vm_node object is actually
	 *       stored inside of `cpu_node1', meaning that once that node is removed,
	 *       the `cpu_node2' descriptor will automatically become invalid! */
	cpu_node2 = vm_paged_node_remove(&vm_kernel, cpu_basepage + (size_t)__x86_cpu_part1_pages);
	COMPILER_BARRIER();
	cpu_node3 = vm_paged_node_remove(&vm_kernel, cpu_basepage + (size_t)__x86_cpu_part1_pages + 2);
	cpu_node1 = vm_paged_node_remove(&vm_kernel, cpu_basepage);
#ifdef ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE
	if (!pagedir_prepare_map(self, ((size_t)__x86_cpu_part1_pages + 3) * PAGESIZE))
		kernel_panic(FREESTR("Failed to prepare pagedir for unmapping CPU descriptor"));
#endif /* ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE */
	pagedir_unmap(self, ((size_t)__x86_cpu_part1_pages + 3) * PAGESIZE);
#ifdef ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE
	pagedir_unprepare_map(self, ((size_t)__x86_cpu_part1_pages + 3) * PAGESIZE);
#endif /* ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE */
	sync_endwrite(&vm_kernel);
	assert(cpu_node1);
	assert(cpu_node2);
	assert(cpu_node3);
	assert(cpu_node1->vn_node.a_vmin == cpu_basepage);
	assert(cpu_node1->vn_node.a_vmax == cpu_basepage + (size_t)__x86_cpu_part1_pages - 1);
	/* NOTE: Because we've already removed the nodes from `vm_kernel', we must no longer
	 *       access the `cpu_node2' structure, since the descriptor was contained inside
	 *       of `cpu_node1' */
	/*assert(cpu_node2->vn_node.a_vmin == cpu_node1->vn_node.a_vmax + 1);*/
	/*assert(cpu_node2->vn_node.a_vmax == cpu_node1->vn_node.a_vmax + 2);*/
	assert(cpu_node3->vn_node.a_vmin == cpu_node1->vn_node.a_vmax + 3);
	assert(cpu_node3->vn_node.a_vmax == cpu_node3->vn_node.a_vmin);
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
	pagedir_unmap(vm_node_getstart(&FORCPU(self, thiscpu_x86_dfstacknode_)),
	              vm_node_getsize(&FORCPU(self, thiscpu_x86_dfstacknode_)));
	pagedir_sync(vm_node_getstart(&FORCPU(self, thiscpu_x86_dfstacknode_)),
	             vm_node_getsize(&FORCPU(self, thiscpu_x86_dfstacknode_)));
#ifdef ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE
	pagedir_unprepare_map(vm_node_getstart(&FORCPU(self, thiscpu_x86_dfstacknode_)),
	                      vm_node_getsize(&FORCPU(self, thiscpu_x86_dfstacknode_)));
#endif /* ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE */
	pagedir_unmap(vm_node_getstart(&FORTASK(myidle, this_kernel_stacknode_)),
	              vm_node_getsize(&FORTASK(myidle, this_kernel_stacknode_)));
	pagedir_sync(vm_node_getstart(&FORTASK(myidle, this_kernel_stacknode_)),
	             vm_node_getsize(&FORTASK(myidle, this_kernel_stacknode_)));
#ifdef ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE
	pagedir_unprepare_map(vm_node_getstart(&FORTASK(myidle, this_kernel_stacknode_)),
	                      vm_node_getsize(&FORTASK(myidle, this_kernel_stacknode_)));
#endif /* ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE */
	pagedir_unmapone(vm_node_getstart(&FORTASK(myidle, this_trampoline_node)));
	pagedir_syncone(vm_node_getstart(&FORTASK(myidle, this_trampoline_node)));
#ifdef ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE
	pagedir_unprepare_mapone(vm_node_getstart(&FORTASK(myidle, this_trampoline_node)));
#endif /* ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE */

	/* Remove the #DF and IDLE stack nodes from the kernel VM */
	while (!sync_trywrite(&vm_kernel.v_treelock))
		__pause();
	vm_paged_node_remove(&vm_kernel, FORCPU(self, thiscpu_x86_dfstacknode_).vn_node.a_vmin);
	vm_paged_node_remove(&vm_kernel, FORTASK(myidle, this_kernel_stacknode_).vn_node.a_vmin);
	vm_paged_node_remove(&vm_kernel, FORTASK(myidle, this_trampoline_node).vn_node.a_vmin);
	sync_endwrite(&vm_kernel.v_treelock);
	/* Finalize the associated data parts, freeing up backing physical memory. */
	vm_datapart_freeram(&FORCPU(self, thiscpu_x86_dfstackpart_), false);
	vm_datapart_freeram(&FORTASK(myidle, this_kernel_stackpart_), false);
	LLIST_REMOVE(myidle, t_vm_tasks);
	cpu_free(self);
}


PRIVATE ATTR_FREETEXT void KCALL
i386_allocate_secondary_cores(void) {
	cpuid_t i;
	for (i = 1; i < _cpu_count; ++i) {
		struct cpu *altcore;
		struct task *altidle;
		/* Allocate an initialize the alternative core. */
		altcore = cpu_alloc();
		altidle = &FORCPU(altcore, thiscpu_idle);
		/* Decode information previously encoded in `smp.c' */
		FORCPU(altcore, _thiscpu_x86_lapicid)      = (uintptr_t)_cpu_vector[i] & 0xff;
		FORCPU(altcore, _thiscpu_x86_lapicversion) = ((uintptr_t)_cpu_vector[i] & 0xff00) >> 8;
		_cpu_vector[i] = altcore;

		altcore->c_id                        = i;
		altcore->c_current                   = altidle;
		altcore->c_override                  = NULL;
		altidle->t_cpu                       = altcore;
		altidle->t_self                      = altidle;
		altidle->t_flags                     = TASK_FSTARTED | TASK_FRUNNING | TASK_FKEEPCORE | TASK_FCRITICAL;
		altidle->t_sched.s_running.sr_runnxt = altidle;
		altidle->t_sched.s_running.sr_runprv = altidle;

		/* Insert the new task into the kernel VM's task user list. */
		LLIST_INSERT(vm_kernel.v_tasks, altidle, t_vm_tasks);

		/* Allocate & map stacks for this cpu's IDLE task, as well as the #DF stack. */
		FORCPU(altcore, thiscpu_x86_dfstackpart_).dp_tree.a_vmax   = (datapage_t)(CEILDIV(KERNEL_DF_STACKSIZE, PAGESIZE) - 1);
		FORCPU(altcore, thiscpu_x86_dfstacknode_).vn_part          = &FORCPU(altcore, thiscpu_x86_dfstackpart_);
		FORCPU(altcore, thiscpu_x86_dfstacknode_).vn_link.ln_pself = &LLIST_HEAD(FORCPU(altcore, thiscpu_x86_dfstackpart_).dp_srefs);
		FORCPU(altcore, thiscpu_x86_dfstackpart_).dp_srefs         = &FORCPU(altcore, thiscpu_x86_dfstacknode_);
		vm_datapart_do_allocram(&FORCPU(altcore, thiscpu_x86_dfstackpart_));
		{
			void *addr;
			addr = vm_getfree(&vm_kernel,
			                  HINT_GETADDR(KERNEL_VMHINT_DFSTACK),
			                  CEIL_ALIGN(KERNEL_DF_STACKSIZE, PAGESIZE), PAGESIZE,
			                  HINT_GETMODE(KERNEL_VMHINT_DFSTACK));
			if unlikely(addr == VM_GETFREE_ERROR)
				kernel_panic(FREESTR("Failed to find suitable location for CPU #%u's #DF stack"), (unsigned int)i);
			FORCPU(altcore, thiscpu_x86_dfstacknode_).vn_node.a_vmin = PAGEID_ENCODE((byte_t *)addr);
			FORCPU(altcore, thiscpu_x86_dfstacknode_).vn_node.a_vmax = PAGEID_ENCODE((byte_t *)addr + CEIL_ALIGN(KERNEL_DF_STACKSIZE, PAGESIZE) - 1);
#ifdef ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE
			if (!pagedir_prepare_map(addr, CEIL_ALIGN(KERNEL_DF_STACKSIZE, PAGESIZE)))
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

		FORTASK(altidle, this_kernel_stackpart_).dp_tree.a_vmax = (datapage_t)(CEILDIV(KERNEL_IDLE_STACKSIZE, PAGESIZE) - 1);
		/* The stack of IDLE threads is executable in order to allow for hacking around .free restrictions. */
		FORTASK(altidle, this_kernel_stacknode_).vn_prot = (VM_PROT_EXEC | VM_PROT_WRITE | VM_PROT_READ);

#define REL(x) ((x) = (__typeof__(x))(uintptr_t)((byte_t *)(x) + (uintptr_t)altidle))
		REL(FORTASK(altidle, this_kernel_stacknode_).vn_part);
		REL(FORTASK(altidle, this_kernel_stacknode_).vn_link.ln_pself);
		REL(FORTASK(altidle, this_kernel_stackpart_).dp_srefs);
#undef REL
		vm_datapart_do_allocram(&FORTASK(altidle, this_kernel_stackpart_));
		{
			void *addr;
			addr = vm_getfree(&vm_kernel,
			                  HINT_GETADDR(KERNEL_VMHINT_IDLESTACK),
			                  CEIL_ALIGN(KERNEL_IDLE_STACKSIZE, PAGESIZE), PAGESIZE,
			                  HINT_GETMODE(KERNEL_VMHINT_IDLESTACK));
			if unlikely(addr == VM_GETFREE_ERROR)
				kernel_panic(FREESTR("Failed to find suitable location for CPU #%u's IDLE stack"), (unsigned int)i);
			FORTASK(altidle, this_kernel_stacknode_).vn_node.a_vmin = PAGEID_ENCODE((byte_t *)addr);
			FORTASK(altidle, this_kernel_stacknode_).vn_node.a_vmax = PAGEID_ENCODE((byte_t *)addr + CEIL_ALIGN(KERNEL_IDLE_STACKSIZE, PAGESIZE) - 1);
#ifdef ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE
			if (!pagedir_prepare_map(addr, CEIL_ALIGN(KERNEL_IDLE_STACKSIZE, PAGESIZE)))
				kernel_panic(FREESTR("Failed to map CPU #%u's IDLE stack"), (unsigned int)i);
#endif /* ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE */
			vm_datapart_map_ram(&FORTASK(altidle, this_kernel_stackpart_),
			                    addr,
			                    PAGEDIR_MAP_FREAD | PAGEDIR_MAP_FWRITE);
			vm_node_insert(&FORTASK(altidle, this_kernel_stacknode_));
		}

		{
			void *addr;
			addr = vm_getfree(&vm_kernel,
			                  HINT_GETADDR(KERNEL_VMHINT_TRAMPOLINE), PAGESIZE, PAGESIZE,
			                  HINT_GETMODE(KERNEL_VMHINT_TRAMPOLINE));
			if unlikely(addr == VM_GETFREE_ERROR)
				kernel_panic(FREESTR("Failed to find suitable location for CPU #%u's IDLE trampoline"), (unsigned int)i);
			FORTASK(altidle, this_trampoline_node).vn_node.a_vmin = PAGEID_ENCODE(addr);
			FORTASK(altidle, this_trampoline_node).vn_node.a_vmax = PAGEID_ENCODE(addr);
#ifdef ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE
			if unlikely(!pagedir_prepare_mapone(addr))
				kernel_panic(FREESTR("Failed to prepare CPU #%u's IDLE trampoline"), (unsigned int)i);
#endif /* ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE */
			vm_node_insert(&FORTASK(altidle, this_trampoline_node));
		}

		FORTASK(altidle, this_fs)             = incref(&fs_kernel);
		FORTASK(altidle, this_handle_manager) = incref(&handle_manager_kernel);

		/* Set up the boot-strap CPU state for the new CPU.
		 * -> When a CPU is started by using an INIT IPI, it will perform internal
		 *    setup functions before executing `THIS_CPU->c_current->t_sched.s_state'
		 *    Since this is the first time that we're starting this CPU, we direct
		 *    that state to perform some high-level CPU initialization functions,
		 *    such as determining CPU features (and comparing those against those
		 *    implement by the boot CPU in order to determine the features available
		 *    by the lowest common denominator), before shutting down again, until
		 *    some future point in time when the CPU will be used again. */
		{
			struct scpustate *init_state;
			init_state = (struct scpustate *)((byte_t *)vm_node_getend(&FORTASK(altidle, this_kernel_stacknode_)) -
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
			altidle->t_sched.s_state        = init_state;
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


/* Alternate implementation for `arch_cpu_quantum_elapsed_nopr()' for when APIC is available. */
INTDEF FREE byte_t apic86_arch_cpu_quantum_elapsed_nopr[];
INTDEF byte_t apic86_arch_cpu_quantum_elapsed_nopr_size[];

INTDEF FREE byte_t apic86_arch_cpu_enable_preemptive_interrupts_nopr[];
INTDEF byte_t apic86_arch_cpu_enable_preemptive_interrupts_nopr_size[];

INTDEF FREE byte_t apic86_arch_cpu_disable_preemptive_interrupts_nopr[];
INTDEF byte_t apic86_arch_cpu_disable_preemptive_interrupts_nopr_size[];

INTDEF FREE byte_t apic86_arch_cpu_quantum_elapsed_and_reset_nopr[];
INTDEF byte_t apic86_arch_cpu_quantum_elapsed_and_reset_nopr_size[];

INTDEF FREE byte_t apic86_arch_cpu_update_quantum_length_nopr[];
INTDEF byte_t apic86_arch_cpu_update_quantum_length_nopr_size[];

INTDEF FREE byte_t apic86_arch_cpu_hwipi_pending_nopr[];
INTDEF byte_t apic86_arch_cpu_hwipi_pending_nopr_size[];

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

INTERN ATTR_FREEBSS bool x86_config_noapic = false;
DEFINE_VERY_EARLY_KERNEL_COMMANDLINE_OPTION(x86_config_noapic,
                                            KERNEL_COMMANDLINE_OPTION_TYPE_BOOL,
                                            "noapic");

DATDEF VIRT byte_t volatile *_x86_lapicbase ASMNAME("x86_lapicbase");

INTERN ATTR_FREETEXT void NOTHROW(KCALL x86_initialize_apic)(void) {

	/* Initialize the regular PIC */
	x86_initialize_pic();
#define MAKE_DWORD(a, b, c, d) ((u32)(a) | ((u32)(b) << 8) | ((u32)(c) << 16) | ((u32)(d) << 24))
	if (bootcpu_x86_cpuid.ci_80000002a == MAKE_DWORD('B', 'O', 'C', 'H'))
		x86_config_noapic = true; /* FIXME: Work-around for weird timing... */

	/* Check if we should make use of the LAPIC */
	if (X86_HAVE_LAPIC && !x86_config_noapic) {
		u32 num_ticks;
#ifndef CONFIG_NO_SMP
		cpuid_t i;
		if (_cpu_count > 1) {
			pageptr_t entry_page;
			/* Allocate low physical memory for the SMP initialization entry page. */
			entry_page = page_malloc_between((pageptr_t)((vm_phys_t)0x00000000 / PAGESIZE),
			                                 (pageptr_t)((vm_phys_t)0x000fffff / PAGESIZE),
			                                 CEILDIV(x86_smp_entry_size, PAGESIZE));
			if unlikely(entry_page == PAGEPTR_INVALID) {
				printk(FREESTR(KERN_WARNING "[apic] Failed to allocate SMP trampoline (re-configure for single-core mode)\n"));
				_cpu_count = 1;
#ifdef __HAVE_CPUSET_FULL_MASK
				CPUSET_SETONE(___cpuset_full_mask, 0); /* 0 == BOOTCPU_ID */
#endif /* __HAVE_CPUSET_FULL_MASK */
				goto done_early_altcore_init;
			}
			printk(FREESTR(KERN_INFO "[apic] Allocating SMP trampoline at " FORMAT_VM_PHYS_T "\n"),
			       page2addr(entry_page));
			x86_smp_entry_page = (u8)entry_page;
			/* Apply some custom AP entry relocations. */
			{
				u32 gdt_addr;
				gdt_addr = (u32)(x86_smp_gdt - x86_smp_entry);
				gdt_addr += page2addr32(entry_page);
				x86_smp_entry_gdt_segment = (gdt_addr & 0xf0000) >> 4;
				x86_smp_entry_gdt_offset  = (gdt_addr & 0x0ffff);
				x86_smp_gdt_pointer_base += page2addr32(entry_page);
			}
			COMPILER_WRITE_BARRIER();
			/* Copy AP entry code. */
			vm_copytophys(page2addr(entry_page),
			              x86_smp_entry,
			              x86_smp_entry_size);
	
			/* Allocate control structures for secondary cores. */
			i386_allocate_secondary_cores();
		}
done_early_altcore_init:
#endif /* !CONFIG_NO_SMP */

		printk(FREESTR(KERN_INFO "[apic] Using LAPIC for timings\n"));

		/* Re-write text for the quantum accessor functions to use the APIC reload counter. */
		memcpy((void *)&arch_cpu_quantum_elapsed_nopr,
		       (void *)apic86_arch_cpu_quantum_elapsed_nopr,
		       (size_t)apic86_arch_cpu_quantum_elapsed_nopr_size);
		memcpy((void *)&arch_cpu_enable_preemptive_interrupts_nopr,
		       (void *)apic86_arch_cpu_enable_preemptive_interrupts_nopr,
		       (size_t)apic86_arch_cpu_enable_preemptive_interrupts_nopr_size);
		memcpy((void *)&arch_cpu_disable_preemptive_interrupts_nopr,
		       (void *)apic86_arch_cpu_disable_preemptive_interrupts_nopr,
		       (size_t)apic86_arch_cpu_disable_preemptive_interrupts_nopr_size);
		memcpy((void *)&arch_cpu_quantum_elapsed_and_reset_nopr,
		       (void *)apic86_arch_cpu_quantum_elapsed_and_reset_nopr,
		       (size_t)apic86_arch_cpu_quantum_elapsed_and_reset_nopr_size);
		memcpy((void *)&arch_cpu_update_quantum_length_nopr,
		       (void *)apic86_arch_cpu_update_quantum_length_nopr,
		       (size_t)apic86_arch_cpu_update_quantum_length_nopr_size);
		memcpy((void *)&arch_cpu_hwipi_pending_nopr,
		       (void *)apic86_arch_cpu_hwipi_pending_nopr,
		       (size_t)apic86_arch_cpu_hwipi_pending_nopr_size);

		/* Re-write scheduler interrupt handlers to ACK APIC interrupts, rather than the PIC ones. */
		memcpy((void *)x86_pic_acknowledge,
		       (void *)x86_ack_apic,
		       (size_t)x86_ack_apic_size);
#ifndef CONFIG_NO_DEBUGGER
		memcpy((void *)x86_debug_pic_acknowledge,
		       (void *)x86_ack_apic,
		       (size_t)x86_ack_apic_size);
#endif /* !CONFIG_NO_DEBUGGER */

		/* Read out the boot cpu's LAPIC id if it couldn't be determined before now. */
		if (FORCPU(&_bootcpu, _thiscpu_x86_lapicid) == 0xff) {
			u32 id = lapic_read(APIC_ID);
			FORCPU(&_bootcpu, _thiscpu_x86_lapicid) = (u8)(id >> APIC_ID_FSHIFT);
		}

		/* Disable the PIT interrupt if we're going to use the LAPIC timer. */
		outb_p(X86_PIC1_DATA, 1);
		outb_p(X86_PIC2_DATA, 0);

		lapic_write(APIC_SPURIOUS,
		            APIC_SPURIOUS_FENABLED |
		            X86_INTERRUPT_APIC_SPURIOUS);

#ifndef CONFIG_NO_SMP
		sync_write(&x86_pit_lock);
		assert(CPU_ALL_ONLINE);
		/* Send INIT commands to all CPUs. */
		for (i = 1; i < _cpu_count; ++i) {
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

		/* Setup the first portion of an APIC timer. */
		lapic_write(APIC_TIMER_DIVIDE, APIC_TIMER_DIVIDE_F16);
		lapic_write(APIC_TIMER,
		            X86_INTERRUPT_APIC_SPURIOUS |
		            APIC_TIMER_MODE_FONESHOT);
		/* Calibrate the APIC */
		x86_calibrate_apic_with_pic();
#ifndef CONFIG_NO_SMP
		sync_endwrite(&x86_pit_lock);
#endif /* !CONFIG_NO_SMP */
		COMPILER_BARRIER();
		num_ticks = lapic_read(APIC_TIMER_CURRENT);

#ifndef CONFIG_NO_SMP
		/* Send start IPIs to all APs. */
		for (i = 1; i < _cpu_count; ++i) {
			apic_send_startup(FORCPU(cpu_vector[i], thiscpu_x86_lapicid),
			                  x86_smp_entry_page);
		}
#endif /* !CONFIG_NO_SMP */
		num_ticks = (((u32)-1) - num_ticks) * 100;
		num_ticks /= HZ;
		if unlikely(!num_ticks)
			num_ticks = 1;
		printk(FREESTR(KERN_INFO "[apic] Boot CPU has a quantum length of %I32u units\n"), num_ticks);

		lapic_write(APIC_TIMER_DIVIDE, APIC_TIMER_DIVIDE_F16);
		lapic_write(APIC_TIMER,
		            /* Set the PIT interrupt to the APIC timer. */
		            X86_INTNO_PIC1_PIT |
		            APIC_TIMER_MODE_FPERIODIC);
		lapic_write(APIC_TIMER_INITIAL, num_ticks);
		cpu_set_quantum_length(num_ticks);
		FORCPU(&_bootcpu, arch_cpu_preemptive_interrupts_disabled) = false;
		PREEMPTION_ENABLE();

#ifndef CONFIG_NO_SMP
		/* Wait for secondary CPUs to come online. */
		if (!CPU_ALL_ONLINE) {
			unsigned int timeout;
			PREEMPTION_DISABLE();
			arch_cpu_quantum_elapsed_and_reset_nopr(&_bootcpu);
			PREEMPTION_ENABLE();
#if HZ >= 100
			/* Wait for more than a single jiffi. */
			timeout = ((HZ + 1) / 100);
			while (timeout--) {
				__hlt();
				if likely(CPU_ALL_ONLINE)
					goto all_online;
			}
#else /* HZ >= 100 */
			__hlt(); /* XXX: Waiting for 1ms would be enough here... */
#endif /* HZ < 100 */

			if likely(CPU_ALL_ONLINE)
				goto all_online;
			/* Re-send start IPIs to all APs still not online. */
			for (i = 1; i < _cpu_count; ++i) {
				if (!(ATOMIC_READ(cpu_offline_mask[i / 8]) & (1 << (i % 8))))
					continue;
				printk(FREESTR(KERN_WARNING "[apic] Re-attempting startup of processor #%u (LAPIC id %#.2I8x)\n"),
				       i, FORCPU(cpu_vector[i], thiscpu_x86_lapicid));
				apic_send_startup(FORCPU(cpu_vector[i], thiscpu_x86_lapicid),
				                  x86_smp_entry_page);
			}
			/* Wait up to a full second for the (possibly slow?) CPUs to come online. */
			timeout = HZ;
			while (timeout--) {
				if (CPU_ALL_ONLINE)
					goto all_online;
				__hlt();
			}
			/* Check one last time? */
			if (CPU_ALL_ONLINE)
				goto all_online;
			/* Guess these CPUs are just broken... */
			for (i = 1; i < _cpu_count;) {
				struct cpu *discard_cpu;
				discard_cpu       = _cpu_vector[i];
				discard_cpu->c_id = i; /* Re-assign CPU IDs to reflect removed entries. */
				if (!(ATOMIC_READ(cpu_offline_mask[i / 8]) & (1 << (i % 8)))) {
					++i;
					continue;
				}
				printk(FREESTR(KERN_ERR "[apic] CPU with LAPIC id %#.2I8x doesn't want to "
				                        "come online (removing it from the configuration)\n"),
				       i, FORCPU(_cpu_vector[i], thiscpu_x86_lapicid));
				cpu_destroy(_cpu_vector[i]);
				/* Remove the CPU from the vector. */
				--_cpu_count;
				memmovedown(&_cpu_vector[i], &_cpu_vector[i + 1],
				            _cpu_count - i, sizeof(struct cpu *));
			}
		}
all_online:
		;
#ifdef __HAVE_CPUSET_FULL_MASK
		___cpuset_full_mask = ((cpuset_t)1 << _cpu_count) - 1;
#endif /* __HAVE_CPUSET_FULL_MASK */
#endif /* !CONFIG_NO_SMP */
	} else {
		printk(FREESTR(KERN_INFO "[apic] LAPIC unavailable or disabled. Using PIC for timings\n"));

		/* Clear out the lapic pointer when disabled. */
		_x86_lapicbase = NULL;

		/* Ensure that we're configured for only a single CPU */
		_cpu_count = 1;
#ifdef __HAVE_CPUSET_FULL_MASK
		CPUSET_SETONE(___cpuset_full_mask, 0); /* 0 == BOOTCPU_ID */
#endif /* __HAVE_CPUSET_FULL_MASK */

		/* Enable all interrupts. */
		outb_p(X86_PIC1_DATA, 0);
		outb_p(X86_PIC2_DATA, 0);

		/* Re-write the preemption code to acknowledge PIC interrupts. */
		memcpy(x86_pic_acknowledge, x86_ack_pic, (size_t)x86_ack_apic_size);
#ifndef CONFIG_NO_DEBUGGER
		memcpy(x86_debug_pic_acknowledge, x86_ack_pic, (size_t)x86_ack_apic_size);
#endif /* !CONFIG_NO_DEBUGGER */

		cpu_set_quantum_length(PIT_HZ_DIV(HZ));

		/* Set the PIC speed. */
		outb(PIT_COMMAND,
		     PIT_COMMAND_SELECT_F0 |
		     PIT_COMMAND_ACCESS_FLOHI |
		     PIT_COMMAND_MODE_FRATEGEN |
		     PIT_COMMAND_FBINARY);
		outb_p(PIT_DATA0, PIT_HZ_DIV(HZ) & 0xff);
		outb(PIT_DATA0, PIT_HZ_DIV(HZ) >> 8);

		FORCPU(&_bootcpu, arch_cpu_preemptive_interrupts_disabled) = false;
		PREEMPTION_ENABLE();
	}
}


DECL_END

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_SCHED_APIC_C */
