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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_APIC_C
#define GUARD_KERNEL_CORE_ARCH_I386_APIC_C 1
#define DISABLE_BRANCH_PROFILING 1 /* Don't profile this file */
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <fs/vfs.h>
#include <kernel/apic.h>
#include <kernel/debugger.h>
#include <kernel/driver-param.h>
#include <kernel/gdt.h>
#include <kernel/handle.h>
#include <kernel/heap.h>
#include <kernel/memory.h>
#include <kernel/panic.h>
#include <kernel/pic.h>
#include <kernel/pit.h>
#include <kernel/printk.h>
#include <kernel/tss.h>
#include <kernel/vm.h>
#include <sched/cpu.h>
#include <sched/smp.h>
#include <sched/task.h>

#include <hybrid/align.h>
#include <hybrid/atomic.h>
#include <hybrid/limits.h>

#include <asm/intrin.h>
#include <asm/param.h>
#include <kos/kernel/cpu-state.h>

#include <assert.h>
#include <stddef.h>
#include <string.h>

DECL_BEGIN

#ifndef CONFIG_NO_SMP
/* Lock used to synchronize access to the PIT. */
PUBLIC DEFINE_ATOMIC_RWLOCK(x86_pit_lock);
#endif /* !CONFIG_NO_SMP */

INTDEF byte_t x86_pic_acknowledge[];
#ifndef CONFIG_NO_DEBUGGER
INTDEF byte_t x86_debug_pic_acknowledge[];
#endif /* !CONFIG_NO_DEBUGGER */

#ifdef __x86_64__
PRIVATE ATTR_FREERODATA u8 const x86_ack_apic = {
	//TODO: movq x86_lapic_base_address, %rax
	//TODO: movl $(APIC_EOI_FSIGNAL), APIC_EOI(%rax)
};
#else /* __x86_64__ */
struct __ATTR_PACKED x86_ack_apic_data {
	/* movl x86_lapic_base_address, %eax */
	u8  b_a1;
	u32 l_x86_lapic_base_address;
	/* movl $(APIC_EOI_FSIGNAL), APIC_EOI(%eax) */
	u8  b_c7;
	u8  b_80;
	u32 l_APIC_EOI;
	u32 l_APIC_EOI_FSIGNAL;
};
PRIVATE ATTR_FREERODATA struct x86_ack_apic_data const x86_ack_apic = {
	/* movl x86_lapic_base_address, %eax */
	0xa1,
	(u32)&x86_lapic_base_address,
	/* movl $(APIC_EOI_FSIGNAL), APIC_EOI(%eax) */
	0xc7,
	0x80,
	APIC_EOI,
	APIC_EOI_FSIGNAL,
};
#endif /* !__x86_64__ */

/* NOTE: This code must match the text size in `x86_pic_acknowledge' */
#ifdef __x86_64__
PRIVATE ATTR_FREERODATA u8 const x86_ack_pic[18] = {
	0xb0, X86_PIC_CMD_EOI,   /* movb $X86_PIC_CMD_EOI, %al */
	0xe6, (u8)X86_PIC1_CMD,  /* outb %al, $X86_PIC1_CMD */
	/* Fill the remaining space with NOPs. */
	0x90, 0x90, 0x90, 0x90, 0x90, 0x90,
	0x90, 0x90, 0x90, 0x90, 0x90, 0x90,
	0x90, 0x90
};
#else /* __x86_64__ */
PRIVATE ATTR_FREERODATA u8 const x86_ack_pic[15] = {
	0xb0, X86_PIC_CMD_EOI,  /* movb $X86_PIC_CMD_EOI, %al */
	0xe6, (u8)X86_PIC1_CMD, /* outb %al, $X86_PIC1_CMD */
	/* Fill the remaining space with NOPs. */
	0x90, 0x90, 0x90, 0x90, 0x90, 0x90,
	0x90, 0x90, 0x90, 0x90, 0x90
};
#endif /* !__x86_64__ */
STATIC_ASSERT(sizeof(x86_ack_apic) == sizeof(x86_ack_pic));


DATDEF ATTR_PERCPU quantum_diff_t _cpu_quantum_length ASMNAME("cpu_quantum_length");
DATDEF ATTR_PERCPU u8 _x86_lapic_id ASMNAME("x86_lapic_id");
DATDEF ATTR_PERCPU u8 _x86_lapic_version ASMNAME("x86_lapic_version");
DATDEF size_t _cpu_count ASMNAME("cpu_count");
DATDEF struct cpu *_cpu_vector[CONFIG_MAX_CPU_COUNT] ASMNAME("cpu_vector");


#ifndef CONFIG_NO_SMP
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



/* TODO: This function being apart of the .free section is unsafe!
 *       The boot core may move on to unmap the .free section while
 *       a secondary core still performing initialization in here! */
PRIVATE /*ATTR_FREETEXT*/ void KCALL x86_altcore_entry(void) {
	u32 num_ticks;
	struct cpu *me = THIS_CPU;
	cpuid_t id     = me->c_id;
	/* Disable the APIC timer again, which had already
	 * been enabled by `x86_altcore_initapic()' */
	lapic_write(APIC_TIMER, APIC_TIMER_FDISABLED);

	/* C-level entry point for secondary SMP cores. */
	printk(/*FREESTR*/ (KERN_NOTICE "Begin CPU #%u initialization\n"), id);

	/* Tell the boot-cpu that we're now online. */
	ATOMIC_FETCHAND(cpu_offline_mask[id / 8], ~(1 << (id % 8)));

	/* Same as what the BOOT processor does to configure its LAPIC. */
	while (!sync_trywrite(&x86_pit_lock))
		__pause();
	lapic_write(APIC_TIMER_DIVIDE, APIC_TIMER_DIVIDE_F16);
	lapic_write(APIC_TIMER, 0xff | APIC_TIMER_MODE_FONESHOT | APIC_TIMER_SOURCE_FDIV);
	outb(PIT_PCSPEAKER,
	     (inb(PIT_PCSPEAKER) &
	      ~(PIT_PCSPEAKER_FSYNCPIT | PIT_PCSPEAKER_FINOUT)) |
	     PIT_PCSPEAKER_FSYNCPIT);
	outb(PIT_COMMAND,
	     PIT_COMMAND_SELECT_F2 |
	     PIT_COMMAND_ACCESS_FLOHI |
	     PIT_COMMAND_MODE_FONESHOT);
	outb_p(PIT_DATA2, (PIT_HZ_DIV(100) & 0xff));
	outb(PIT_DATA2, (PIT_HZ_DIV(100) >> 8) & 0xff);
	{
		u8 temp = inb(PIT_PCSPEAKER) & ~PIT_PCSPEAKER_FINOUT;
		outb(PIT_PCSPEAKER, temp);
		outb(PIT_PCSPEAKER, temp | PIT_PCSPEAKER_OUT);
	}
	lapic_write(APIC_TIMER_INITIAL, (u32)-1);
	while (inb(PIT_PCSPEAKER) & PIT_PCSPEAKER_FPIT2OUT)
		__pause();
	sync_endwrite(&x86_pit_lock);
	lapic_write(APIC_TIMER, APIC_TIMER_FDISABLED);
	num_ticks = lapic_read(APIC_TIMER_CURRENT);
	num_ticks = (((u32)-1) - num_ticks) * 100;
	printk(/*FREESTR*/ (KERN_INFO "CPU #%u uses a LAPIC timing of %u ticks per second\n"),
	       id, num_ticks);
	num_ticks /= HZ;
	if unlikely(!num_ticks)
		num_ticks = 1;
	/* TODO: If `num_ticks' differs from `FORCPU(&_bootcpu,_cpu_quantum_length)'
	 *       by more than 1%, re-try the calibration up to 2 more times.
	 *    -> Mainly affects emulators when the bus-clock is based on real
	 *       time, but the emulator itself may have been preempted while
	 *       it was hosting our calibration code.
	 *    -> This is something I've seen happening a couple of times, leaving
	 *       secondary cores to arbitrarily have tick counters off by _a_ _lot_. */

	FORCPU(me, _cpu_quantum_length) = num_ticks;

	/* Enable the LAPIC for real this time. */
	lapic_write(APIC_TIMER_DIVIDE, APIC_TIMER_DIVIDE_F16);
	lapic_write(APIC_TIMER,
	            X86_INTNO_PIC1_PIT |
	            APIC_TIMER_MODE_FPERIODIC |
	            APIC_TIMER_SOURCE_FDIV);
	lapic_write(APIC_TIMER_INITIAL, num_ticks);
}

INTERN NOBLOCK void
NOTHROW(FCALL x86_altcore_initapic)(struct cpu *__restrict me) {
	/* Enable the APIC of this CPU */
	lapic_write(APIC_SPURIOUS,
	            APIC_SPURIOUS_FENABLED |
	            X86_INTERRUPT_APIC_SPURIOUS);
	lapic_write(APIC_TIMER_DIVIDE, APIC_TIMER_DIVIDE_F16);
	lapic_write(APIC_TIMER,
	            /* Set the PIT interrupt to the APIC timer. */
	            X86_INTNO_PIC1_PIT |
	            APIC_TIMER_MODE_FPERIODIC |
	            APIC_TIMER_SOURCE_FDIV);
	lapic_write(APIC_TIMER_INITIAL, FORCPU(me, _cpu_quantum_length));
}





/* The physical page to which the realmode SMP entry code is mapped. */
INTERN u8 x86_smp_entry_page = 0;


INTDEF FREE byte_t x86_smp_gdt[];
INTDEF FREE byte_t x86_smp_entry[];
INTDEF FREE byte_t x86_smp_entry_size[];

INTDEF u16 x86_smp_entry_gdt_segment;
INTDEF u16 x86_smp_entry_gdt_offset;
INTDEF u32 x86_smp_gdt_pointer_base;

INTDEF byte_t __kernel_percpu_start[];
INTDEF byte_t __kernel_percpu_size[];
INTDEF byte_t __kernel_pertask_start[];
INTDEF byte_t __kernel_pertask_size[];

typedef void (KCALL *pertask_init_t)(struct task *__restrict self);
INTDEF pertask_init_t __kernel_pertask_init_start[];
INTDEF pertask_init_t __kernel_pertask_init_end[];

typedef void (KCALL *pertask_fini_t)(struct task *__restrict self);
INTDEF pertask_fini_t __kernel_pertask_fini_start[];
INTDEF pertask_fini_t __kernel_pertask_fini_end[];


DATDEF ATTR_PERCPU struct vm_node _x86_this_dfstack ASMNAME("x86_this_dfstack");
DATDEF ATTR_PERCPU struct vm_datapart _x86_this_dfstack_part ASMNAME("x86_this_dfstack_part");
DATDEF ATTR_PERTASK struct vm_node __this_kernel_stack ASMNAME("_this_kernel_stack");
DATDEF ATTR_PERTASK struct vm_datapart __this_kernel_stack_part ASMNAME("_this_kernel_stack_part");

#define HINT_ADDR(x, y) x
#define HINT_MODE(x, y) y
#define HINT_GETADDR(x) HINT_ADDR x
#define HINT_GETMODE(x) HINT_MODE x

PRIVATE NOBLOCK ATTR_FREETEXT void
NOTHROW(KCALL x86_destroy_cpu)(struct cpu *__restrict self) {
	struct task *myidle;
	myidle = &FORCPU(self, _this_idle);
	{
		/* Run finalizers for the IDLE task. */
		pertask_fini_t *iter;
		iter = __kernel_pertask_fini_start;
		for (; iter < __kernel_pertask_fini_end; ++iter)
			(**iter)(&FORCPU(self, _this_idle));
	}
	/* Unmap, sync, & unprepare the mappings for the CPU's IDLE and #DF stacks.
	 * NOTE: Because these mappings are private the the CPU itself, we don't
	 *       need to be holding a lock to the kernel VM for this part! */
	pagedir_unmap(VM_NODE_MIN(&FORCPU(self, _x86_this_dfstack)), VM_NODE_SIZE(&FORCPU(self, _x86_this_dfstack)));
	pagedir_sync(VM_NODE_MIN(&FORCPU(self, _x86_this_dfstack)), VM_NODE_SIZE(&FORCPU(self, _x86_this_dfstack)));
#ifdef CONFIG_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE
	pagedir_unprepare_map(VM_NODE_MIN(&FORCPU(self, _x86_this_dfstack)), VM_NODE_SIZE(&FORCPU(self, _x86_this_dfstack)));
#endif /* CONFIG_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE */
	pagedir_unmap(VM_NODE_MIN(&FORTASK(myidle, __this_kernel_stack)), VM_NODE_SIZE(&FORTASK(myidle, __this_kernel_stack)));
	pagedir_sync(VM_NODE_MIN(&FORTASK(myidle, __this_kernel_stack)), VM_NODE_SIZE(&FORTASK(myidle, __this_kernel_stack)));
#ifdef CONFIG_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE
	pagedir_unprepare_map(VM_NODE_MIN(&FORTASK(myidle, __this_kernel_stack)), VM_NODE_SIZE(&FORTASK(myidle, __this_kernel_stack)));
#endif /* CONFIG_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE */
	pagedir_unmapone(VM_NODE_MIN(&FORTASK(myidle, _this_trampoline_node)));
	pagedir_syncone(VM_NODE_MIN(&FORTASK(myidle, _this_trampoline_node)));
#ifdef CONFIG_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE
	pagedir_unprepare_mapone(VM_NODE_MIN(&FORTASK(myidle, _this_trampoline_node)));
#endif /* CONFIG_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE */

	/* Remove the #DF and IDLE stack nodes from the kernel VM */
	while (!sync_trywrite(&vm_kernel.v_treelock))
		__pause();
	vm_node_remove(&vm_kernel, FORCPU(self, _x86_this_dfstack).vn_node.a_vmin);
	vm_node_remove(&vm_kernel, FORTASK(myidle, __this_kernel_stack).vn_node.a_vmin);
	vm_node_remove(&vm_kernel, FORTASK(myidle, _this_trampoline_node).vn_node.a_vmin);
	sync_endwrite(&vm_kernel.v_treelock);
	/* Finalize the associated data parts, freeing up backing physical memory. */
	vm_datapart_freeram(&FORCPU(self, _x86_this_dfstack_part), false);
	vm_datapart_freeram(&FORTASK(myidle, __this_kernel_stack_part), false);

	LLIST_REMOVE(myidle, t_vm_tasks);

	/* Release the CPU structure back to the heap it came from. */
	heap_free(&kernel_locked_heap, self,
	          self->c_heapsize, GFP_LOCKED);
}


PRIVATE ATTR_FREETEXT void KCALL
i386_allocate_secondary_cores(void) {
	cpuid_t i;

	if (_cpu_count <= 1)
		return; /* No secondary cores. */
	for (i = 1; i < _cpu_count; ++i) {
		struct cpu *altcore;
		struct task *altidle;
		struct heapptr ptr;
		/* Allocate an initialize the alternative core. */
		ptr = heap_align(&kernel_locked_heap,
		                 __SIZEOF_CACHELINE__,
		                 0,
		                 (size_t)__kernel_percpu_size,
		                 GFP_LOCKED | GFP_PREFLT);
		altcore = (struct cpu *)ptr.hp_ptr;
		altidle = &FORCPU(altcore, _this_idle);
		memcpy(altcore, __kernel_percpu_start, (size_t)__kernel_percpu_size);
		memcpy(altidle, __kernel_pertask_start, (size_t)__kernel_pertask_size);
		/* Decode information previously encoded in `smp.c' */
		altcore->c_heapsize = ptr.hp_siz;
		FORCPU(altcore, _x86_lapic_id)      = (uintptr_t)_cpu_vector[i] & 0xff;
		FORCPU(altcore, _x86_lapic_version) = ((uintptr_t)_cpu_vector[i] & 0xff00) >> 8;
		_cpu_vector[i] = altcore;

		altcore->c_id                        = i;
		altcore->c_current                   = altidle;
		altcore->c_override                  = NULL;
		altidle->t_cpu                       = altcore;
		altidle->t_self                      = altidle;
		altidle->t_flags                     = TASK_FSTARTED | TASK_FRUNNING | TASK_FKEEPCORE;
		altidle->t_sched.s_running.sr_runnxt = altidle;
		altidle->t_sched.s_running.sr_runprv = altidle;

		/* Insert the new task into the kernel VM's task user list. */
		LLIST_INSERT(vm_kernel.v_tasks, altidle, t_vm_tasks);

		/* Allocate & map stacks for this cpu's IDLE task, as well as the #DF stack. */
		FORCPU(altcore, _x86_this_dfstack_part).dp_tree.a_vmax  = (vm_dpage_t)(CEILDIV(KERNEL_DF_STACKSIZE, PAGESIZE) - 1);
		FORCPU(altcore, _x86_this_dfstack).vn_part              = &FORCPU(altcore, _x86_this_dfstack_part);
		FORCPU(altcore, _x86_this_dfstack).vn_link.ln_pself     = &LLIST_HEAD(FORCPU(altcore, _x86_this_dfstack_part).dp_srefs);
		FORCPU(altcore, _x86_this_dfstack_part).dp_srefs        = &FORCPU(altcore, _x86_this_dfstack);
		vm_datapart_do_allocram(&FORCPU(altcore, _x86_this_dfstack_part));
		{
			vm_vpage_t addr;
			addr = vm_getfree(&vm_kernel,
			                  (vm_vpage_t)HINT_GETADDR(KERNEL_VMHINT_DFSTACK),
			                  CEILDIV(KERNEL_DF_STACKSIZE, PAGESIZE), 1,
			                  HINT_GETMODE(KERNEL_VMHINT_DFSTACK));
			if unlikely(addr == VM_GETFREE_ERROR)
				kernel_panic(FREESTR("Failed to find suitable location for CPU #%u's #DF stack"), (unsigned int)i);
			FORCPU(altcore, _x86_this_dfstack).vn_node.a_vmin = addr;
			FORCPU(altcore, _x86_this_dfstack).vn_node.a_vmax = addr + CEILDIV(KERNEL_DF_STACKSIZE, PAGESIZE) - 1;
#ifdef CONFIG_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE
			if (!pagedir_prepare_map(addr, CEILDIV(KERNEL_DF_STACKSIZE, PAGESIZE)))
				kernel_panic(FREESTR("Failed to map CPU #%u's #DF stack"), (unsigned int)i);
#endif /* CONFIG_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE */
			vm_datapart_map_ram(&FORCPU(altcore, _x86_this_dfstack_part),
			                    addr,
			                    PAGEDIR_MAP_FREAD | PAGEDIR_MAP_FWRITE);
			vm_node_insert(&FORCPU(altcore, _x86_this_dfstack));
		}

		FORTASK(altidle, __this_kernel_stack_part).dp_tree.a_vmax = (vm_dpage_t)(CEILDIV(KERNEL_IDLE_STACKSIZE, PAGESIZE) - 1);
		/* The stack of IDLE threads is executable in order to allow for hacking around .free restrictions. */
		FORTASK(altidle, __this_kernel_stack).vn_prot = (VM_PROT_EXEC | VM_PROT_WRITE | VM_PROT_READ);
		*(uintptr_t *)&FORTASK(altidle, __this_kernel_stack).vn_part += (uintptr_t)altidle;
		*(uintptr_t *)&FORTASK(altidle, __this_kernel_stack).vn_link.ln_pself += (uintptr_t)altidle;
		*(uintptr_t *)&FORTASK(altidle, __this_kernel_stack_part).dp_srefs += (uintptr_t)altidle;
		vm_datapart_do_allocram(&FORTASK(altidle, __this_kernel_stack_part));
		{
			vm_vpage_t addr;
			addr = vm_getfree(&vm_kernel,
			                  (vm_vpage_t)HINT_GETADDR(KERNEL_VMHINT_IDLESTACK),
			                  CEILDIV(KERNEL_IDLE_STACKSIZE, PAGESIZE), 1,
			                  HINT_GETMODE(KERNEL_VMHINT_IDLESTACK));
			if unlikely(addr == VM_GETFREE_ERROR)
				kernel_panic(FREESTR("Failed to find suitable location for CPU #%u's IDLE stack"), (unsigned int)i);
			FORTASK(altidle, __this_kernel_stack).vn_node.a_vmin = addr;
			FORTASK(altidle, __this_kernel_stack).vn_node.a_vmax = addr + CEILDIV(KERNEL_IDLE_STACKSIZE, PAGESIZE) - 1;
#ifdef CONFIG_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE
			if (!pagedir_prepare_map(addr, CEILDIV(KERNEL_IDLE_STACKSIZE, PAGESIZE)))
				kernel_panic(FREESTR("Failed to map CPU #%u's IDLE stack"), (unsigned int)i);
#endif /* CONFIG_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE */
			vm_datapart_map_ram(&FORTASK(altidle, __this_kernel_stack_part),
			                    addr,
			                    PAGEDIR_MAP_FREAD | PAGEDIR_MAP_FWRITE);
			vm_node_insert(&FORTASK(altidle, __this_kernel_stack));
		}

		{
			vm_vpage_t addr;
			addr = vm_getfree(&vm_kernel,
			                  (vm_vpage_t)HINT_GETADDR(KERNEL_VMHINT_TRAMPOLINE), 1, 1,
			                  HINT_GETMODE(KERNEL_VMHINT_TRAMPOLINE));
			if unlikely(addr == VM_GETFREE_ERROR)
				kernel_panic(FREESTR("Failed to find suitable location for CPU #%u's IDLE trampoline"), (unsigned int)i);
			FORTASK(altidle, _this_trampoline_node).vn_node.a_vmin = addr;
			FORTASK(altidle, _this_trampoline_node).vn_node.a_vmax = addr;
#ifdef CONFIG_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE
			if unlikely(!pagedir_prepare_mapone(addr))
				kernel_panic(FREESTR("Failed to prepare CPU #%u's IDLE trampoline"), (unsigned int)i);
#endif /* CONFIG_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE */
			vm_node_insert(&FORTASK(altidle, _this_trampoline_node));
		}

		FORTASK(altidle, _this_fs)             = incref(&fs_kernel);
		FORTASK(altidle, _this_handle_manager) = incref(&handle_manager_kernel);

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
			init_state = (struct scpustate *)(VM_PAGE2ADDR(FORTASK(altidle, __this_kernel_stack).vn_node.a_vmax + 1) -
			                                  (offsetafter(struct scpustate, scs_irregs) + sizeof(void *)));
			memset(init_state, 0, offsetafter(struct scpustate, scs_irregs));
			/* Set the return address to execute the IDLE main loop. */
			*(void **)((byte_t *)init_state + offsetafter(struct scpustate, scs_irregs)) = (void *)&cpu_idlemain;
#ifdef __x86_64__
			init_state->scs_irregs.ir_cs     = SEGMENT_KERNEL_CODE;
			init_state->scs_irregs.ir_rip    = (u64)&x86_altcore_entry;
			init_state->scs_irregs.ir_ss     = SEGMENT_KERNEL_DATA;
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
		segment_wrbaseX(&FORCPU(altcore, x86_cpugdt[SEGMENT_INDEX(SEGMENT_CPU_TSS)]),
		                (uintptr_t)&FORCPU(altcore, x86_cputss));
		segment_wrbaseX(&FORCPU(altcore, x86_cpugdt[SEGMENT_INDEX(SEGMENT_CPU_LDT)]),
		                (uintptr_t)&FORCPU(altcore, x86_cpuldt));
#ifdef __x86_64__
		FORCPU(altcore, x86_cputss).t_rsp0 = FORTASK(altidle, x86_this_kernel_sp0);
#else /* __x86_64__ */
		segment_wrbaseX(&FORCPU(altcore, x86_cpugdt[SEGMENT_INDEX(SEGMENT_CPU_TSS_DF)]),
		                (uintptr_t)&FORCPU(altcore, x86_cputss_df));
		segment_wrbaseX(&FORCPU(altcore, x86_cpugdt[SEGMENT_INDEX(SEGMENT_KERNEL_FSBASE)]),
		                (uintptr_t)altidle);
		FORCPU(altcore, x86_cputss).t_esp0 = FORTASK(altidle, x86_this_kernel_sp0);
#endif /* !__x86_64__ */
	}
}

#endif /* !CONFIG_NO_SMP */


/* Alternate implementations for `cpu_quantum_elapsed()'
 * and `cpu_quantum_remaining()' for when APIC is available. */
INTDEF FREE byte_t x86_apic_cpu_quantum_elapsed[];
INTDEF byte_t x86_apic_cpu_quantum_elapsed_size[];
INTDEF FREE byte_t x86_apic_cpu_quantum_elapsed_nopr[];
INTDEF byte_t x86_apic_cpu_quantum_elapsed_size_nopr[];

INTDEF FREE byte_t x86_apic_cpu_quantum_remaining[];
INTDEF byte_t x86_apic_cpu_quantum_remaining_size[];
INTDEF FREE byte_t x86_apic_cpu_quantum_remaining_nopr[];
INTDEF byte_t x86_apic_cpu_quantum_remaining_size_nopr[];

INTDEF FREE byte_t x86_apic_cpu_disable_preemptive_interrupts[];
INTDEF byte_t x86_apic_cpu_disable_preemptive_interrupts_size[];
INTDEF FREE byte_t x86_apic_cpu_disable_preemptive_interrupts_nopr[];
INTDEF byte_t x86_apic_cpu_disable_preemptive_interrupts_size_nopr[];

INTDEF FREE byte_t x86_apic_cpu_enable_preemptive_interrupts[];
INTDEF byte_t x86_apic_cpu_enable_preemptive_interrupts_size[];
INTDEF FREE byte_t x86_apic_cpu_enable_preemptive_interrupts_nopr[];
INTDEF byte_t x86_apic_cpu_enable_preemptive_interrupts_size_nopr[];

INTDEF FREE byte_t x86_apic_cpu_quantum_reset[];
INTDEF byte_t x86_apic_cpu_quantum_reset_size[];
INTDEF FREE byte_t x86_apic_cpu_quantum_reset_nopr[];
INTDEF byte_t x86_apic_cpu_quantum_reset_size_nopr[];

INTDEF FREE byte_t x86_apic_cpu_ipi_pending[];
INTDEF byte_t x86_apic_cpu_ipi_pending_size[];

#ifdef __HAVE_CPUSET_FULL_MASK
DATDEF cpuset_t ___cpuset_full_mask ASMNAME("__cpuset_full_mask");
#endif /* __HAVE_CPUSET_FULL_MASK */

INTDEF NOBLOCK void NOTHROW(KCALL x86_cpu_disable_preemptive_interrupts)(void);
INTDEF NOBLOCK void NOTHROW(KCALL x86_cpu_enable_preemptive_interrupts)(void);
INTDEF NOBLOCK void NOTHROW(KCALL x86_cpu_disable_preemptive_interrupts_nopr)(void);
INTDEF NOBLOCK void NOTHROW(KCALL x86_cpu_enable_preemptive_interrupts_nopr)(void);


#ifdef CONFIG_NO_DEBUGGER
INTERN ATTR_FREETEXT void NOTHROW(KCALL x86_initialize_pic)(void)
#else /* CONFIG_NO_DEBUGGER */
/* The debugger calls this function during init,
 * so we can't mark it as ATTR_FREETEXT */
INTERN void NOTHROW(KCALL x86_initialize_pic)(void)
#endif /* !CONFIG_NO_DEBUGGER */
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

#ifndef CONFIG_NO_DEBUGGER
	/* This function should only ever be called once (I've seen the
	 * PIC stop working properly if it's initialized more than once...)
	 * To ensure this, we re-write our own entry-point with a ret-instruction. */
	*(u8 *)(void *)&x86_initialize_pic = 0xc3; /* ret */
#endif /* !CONFIG_NO_DEBUGGER */
}

INTERN ATTR_FREEBSS bool x86_config_noapic = false;
DEFINE_VERY_EARLY_KERNEL_COMMANDLINE_OPTION(x86_config_noapic,
                                            KERNEL_COMMANDLINE_OPTION_TYPE_BOOL,
                                            "noapic");

DATDEF VIRT byte_t volatile *x86_lapic_base_address_ ASMNAME("x86_lapic_base_address");

INTERN ATTR_FREETEXT void NOTHROW(KCALL x86_initialize_apic)(void) {
#ifndef CONFIG_NO_SMP
	DEFINE_INTERN_SYMBOL(_this_vm_pdir_phys_ptr,
	                     offsetof(struct vm, v_pdir_phys_ptr),
	                     sizeof(vm_phys_t));
	DEFINE_INTERN_SYMBOL(_this_cpu_state,
	                     offsetof(struct cpu, c_state),
	                     sizeof(u16));
#endif /* !CONFIG_NO_SMP */

	/* Initialize the regular PIC */
	x86_initialize_pic();

	/* Check if we should make use of the LAPIC */
	if (X86_HAVE_LAPIC  && !x86_config_noapic) {
		u32 num_ticks;
#ifndef CONFIG_NO_SMP
		cpuid_t i;
		vm_ppage_t entry_page;
		/* Allocate low physical memory for the SMP initialization entry page. */
		entry_page = page_malloc_between(VM_ADDR2PAGE((vm_phys_t)0x00000000),
		                                 VM_ADDR2PAGE((vm_phys_t)0x000fffff),
		                                 CEILDIV((size_t)x86_smp_entry_size, PAGESIZE));
		if unlikely(entry_page == PAGEPTR_INVALID)
			kernel_panic(FREESTR("Failed to allocate SMP trampoline\n"));
		printk(FREESTR(KERN_INFO "[apic] Allocating SMP trampoline at " FORMAT_VM_PHYS_T "\n"),
		       VM_PPAGE2ADDR(entry_page));
		x86_smp_entry_page = (u8)entry_page;
		/* Apply some custom AP entry relocations. */
		{
			u32 gdt_addr;
			gdt_addr = (u32)(x86_smp_gdt - x86_smp_entry);
			gdt_addr += (u32)entry_page * PAGESIZE;
			x86_smp_entry_gdt_segment = (gdt_addr & 0xf0000) >> 4;
			x86_smp_entry_gdt_offset  = (gdt_addr & 0x0ffff);
			x86_smp_gdt_pointer_base += (u32)entry_page * PAGESIZE;
		}
		/* Copy AP entry code. */
		vm_copytophys(VM_PPAGE2ADDR(entry_page),
		              x86_smp_entry,
		              (size_t)x86_smp_entry_size);

		/* Allocate control structures for secondary cores. */
		i386_allocate_secondary_cores();
#endif /* !CONFIG_NO_SMP */

		printk(FREESTR(KERN_INFO "[apic] Using LAPIC for timings\n"));

		/* Re-write text for the quantum accessor functions to use the APIC reload counter. */
		memcpy((void *)&cpu_quantum_elapsed, x86_apic_cpu_quantum_elapsed, (size_t)x86_apic_cpu_quantum_elapsed_size);
		memcpy((void *)&cpu_quantum_elapsed_nopr, x86_apic_cpu_quantum_elapsed_nopr, (size_t)x86_apic_cpu_quantum_elapsed_size_nopr);
		memcpy((void *)&cpu_quantum_remaining, x86_apic_cpu_quantum_remaining, (size_t)x86_apic_cpu_quantum_remaining_size);
		memcpy((void *)&cpu_quantum_remaining_nopr, x86_apic_cpu_quantum_remaining_nopr, (size_t)x86_apic_cpu_quantum_remaining_size_nopr);
		memcpy((void *)&x86_cpu_disable_preemptive_interrupts, x86_apic_cpu_disable_preemptive_interrupts, (size_t)x86_apic_cpu_disable_preemptive_interrupts_size);
		memcpy((void *)&x86_cpu_disable_preemptive_interrupts_nopr, x86_apic_cpu_disable_preemptive_interrupts_nopr, (size_t)x86_apic_cpu_disable_preemptive_interrupts_size_nopr);
		memcpy((void *)&x86_cpu_enable_preemptive_interrupts, x86_apic_cpu_enable_preemptive_interrupts, (size_t)x86_apic_cpu_enable_preemptive_interrupts_size);
		memcpy((void *)&x86_cpu_enable_preemptive_interrupts_nopr, x86_apic_cpu_enable_preemptive_interrupts_nopr, (size_t)x86_apic_cpu_enable_preemptive_interrupts_size_nopr);
		memcpy((void *)&cpu_quantum_reset, x86_apic_cpu_quantum_reset, (size_t)x86_apic_cpu_quantum_reset_size);
		memcpy((void *)&cpu_quantum_reset_nopr, x86_apic_cpu_quantum_reset_nopr, (size_t)x86_apic_cpu_quantum_reset_size_nopr);
		memcpy((void *)&cpu_hwipi_pending, x86_apic_cpu_ipi_pending, (size_t)x86_apic_cpu_ipi_pending_size);
		memcpy(x86_pic_acknowledge, &x86_ack_apic, sizeof(x86_ack_apic));
#ifndef CONFIG_NO_DEBUGGER
		memcpy(x86_debug_pic_acknowledge, &x86_ack_apic, sizeof(x86_ack_apic));
#endif /* !CONFIG_NO_DEBUGGER */

		/* Read out the boot cpu's LAPIC id if it couldn't be determined before now. */
		if (FORCPU(&_bootcpu, _x86_lapic_id) == 0xff) {
			u32 id = lapic_read(APIC_ID);
			FORCPU(&_bootcpu, _x86_lapic_id) = (u8)(id >> APIC_ID_FSHIFT);
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
			apic_send_init(FORCPU(cpu_vector[i], x86_lapic_id));
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
		            APIC_TIMER_MODE_FONESHOT |
		            APIC_TIMER_SOURCE_FDIV);


		outb(PIT_PCSPEAKER,
		     (inb(PIT_PCSPEAKER) & ~(PIT_PCSPEAKER_FSYNCPIT | PIT_PCSPEAKER_FINOUT)) |
		     PIT_PCSPEAKER_FSYNCPIT);
		outb(PIT_COMMAND,
		     PIT_COMMAND_SELECT_F2 |
		     PIT_COMMAND_ACCESS_FLOHI |
		     PIT_COMMAND_MODE_FONESHOT);
		/* Configure the PIT to trigger after 1/100th of a second (10ms). */
		outb_p(PIT_DATA2, (PIT_HZ_DIV(100) & 0xff));
		outb(PIT_DATA2, (PIT_HZ_DIV(100) >> 8) & 0xff);
		{
			/*  Move the speaker to trigger the one-shot timer.
			 * (This is what I call a hack from the last century!) */
			u8 temp = inb(PIT_PCSPEAKER) & ~PIT_PCSPEAKER_FINOUT;
			outb(PIT_PCSPEAKER, temp);
			outb(PIT_PCSPEAKER, temp | PIT_PCSPEAKER_OUT);
		}
		/* The PIC timer is now running. */
		/* Set LAPIC counter to its maximum possible value. */
		lapic_write(APIC_TIMER_INITIAL, (u32)-1);
		COMPILER_BARRIER();

		/* Wait for our one-shot time to expire. */
		while (inb(PIT_PCSPEAKER) & PIT_PCSPEAKER_FPIT2OUT)
			__pause();
#ifndef CONFIG_NO_SMP
		sync_endwrite(&x86_pit_lock);
#endif /* !CONFIG_NO_SMP */

		/* Stop LAPIC counter */
		COMPILER_BARRIER();
		lapic_write(APIC_TIMER, APIC_TIMER_FDISABLED);
		num_ticks = lapic_read(APIC_TIMER_CURRENT);

#ifndef CONFIG_NO_SMP
		/* Send start IPIs to all APs. */
		for (i = 1; i < _cpu_count; ++i) {
			apic_send_startup(FORCPU(cpu_vector[i], x86_lapic_id),
			                  (u8)entry_page);
		}
#endif /* !CONFIG_NO_SMP */

		num_ticks = (((u32)-1) - num_ticks) * 100;
		printk(FREESTR(KERN_INFO "[apic] Boot CPU uses a LAPIC timing of %u ticks per second\n"), num_ticks);
		num_ticks /= HZ;
		if unlikely(!num_ticks)
			num_ticks = 1;

		lapic_write(APIC_TIMER_DIVIDE, APIC_TIMER_DIVIDE_F16);
		lapic_write(APIC_TIMER,
		            /* Set the PIT interrupt to the APIC timer. */
		            X86_INTNO_PIC1_PIT |
		            APIC_TIMER_MODE_FPERIODIC |
		            APIC_TIMER_SOURCE_FDIV);
		lapic_write(APIC_TIMER_INITIAL, num_ticks);
		FORCPU(&_bootcpu, _cpu_quantum_length) = num_ticks;
		PREEMPTION_ENABLE();

#ifndef CONFIG_NO_SMP
		/* Wait for secondary CPUs to come online. */
		if (!CPU_ALL_ONLINE) {
			unsigned int timeout;
			cpu_quantum_reset();
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
				       i, FORCPU(cpu_vector[i], x86_lapic_id));
				apic_send_startup(FORCPU(cpu_vector[i], x86_lapic_id),
				                  (u8)entry_page);
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
				       i, FORCPU(_cpu_vector[i], x86_lapic_id));
				x86_destroy_cpu(_cpu_vector[i]);
				/* Remove the CPU from the vector. */
				--_cpu_count;
				memmove(&_cpu_vector[i], &_cpu_vector[i + 1],
				        (_cpu_count - i) * sizeof(struct cpu *));
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
		x86_lapic_base_address_ = NULL;

		/* Ensure that we're configured for only a single CPU */
		_cpu_count = 1;
#ifdef __HAVE_CPUSET_FULL_MASK
		CPUSET_SETONE(___cpuset_full_mask, 0); /* 0 == BOOTCPU_ID */
#endif /* __HAVE_CPUSET_FULL_MASK */

		/* Enable all interrupts. */
		outb_p(X86_PIC1_DATA, 0);
		outb_p(X86_PIC2_DATA, 0);

		/* Re-write the preemption code to acknowledge PIC interrupts. */
		memcpy(x86_pic_acknowledge, x86_ack_pic, sizeof(x86_ack_pic));
#ifndef CONFIG_NO_DEBUGGER
		memcpy(x86_debug_pic_acknowledge, x86_ack_pic, sizeof(x86_ack_pic));
#endif /* !CONFIG_NO_DEBUGGER */

		FORCPU(&_bootcpu, _cpu_quantum_length) = PIT_HZ_DIV(HZ);

		/* Set the PIC speed. */
		outb(PIT_COMMAND,
		     PIT_COMMAND_SELECT_F0 |
		     PIT_COMMAND_ACCESS_FLOHI |
		     PIT_COMMAND_MODE_FSQRWAVE |
		     PIT_COMMAND_FBINARY);
		outb_p(PIT_DATA0, PIT_HZ_DIV(HZ) & 0xff);
		outb(PIT_DATA0, PIT_HZ_DIV(HZ) >> 8);

		PREEMPTION_ENABLE();
	}
}



DECL_END

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_APIC_C */
