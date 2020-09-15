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
#ifndef GUARD_KERNEL_SRC_MEMORY_VM_SYNC_C
#define GUARD_KERNEL_SRC_MEMORY_VM_SYNC_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/paging.h>
#include <kernel/vm.h>
#include <sched/cpu.h>

#include <hybrid/atomic.h>

#include <assert.h>
#include <inttypes.h>
#include <string.h>

DECL_BEGIN

#ifndef CONFIG_NO_SMP
/* Return the set of CPUs that are currently mapped to make use of `self'
 * Note that the returned set of CPUs is only a (possibly inconsistent)
 * snapshot, with the only guaranties being that:
 *   - If a CPU is apart of the returned cpuset, that CPU has at one point
 *     made use of the given vm `self'.
 *   - If a CPU is not apart of the returned cpuset, that CPU may have since
 *     switched its VM to the given one. Note however that during this switch,
 *     additional things may have also happened, such as the CPU invaliding
 *     its TLB cache (where is function is meant to be used to calculate the
 *     bounding set of CPUs that (may) need to have their page directories
 *     invalidated)
 * WARNING: This function does not include special handling for when `self'
 *          is the kernel VM. In this case, the caller must implement a
 *          dedicated code-path that behaves as though this function had
 *          returned a completely filled cpuset. */
#if CONFIG_MAX_CPU_COUNT > BITS_PER_POINTER
PUBLIC NOBLOCK NONNULL((2)) void
NOTHROW(FCALL pagedir_getcpus)(pagedir_phys_t self,
                               cpuset_ptr_t result)
#else /* CONFIG_MAX_CPU_COUNT > BITS_PER_POINTER */
FUNDEF NOBLOCK WUNUSED cpuset_t
NOTHROW(FCALL __pagedir_getcpus)(pagedir_phys_t self)
	ASMNAME("pagedir_getcpus");
PUBLIC NOBLOCK WUNUSED cpuset_t
NOTHROW(FCALL __pagedir_getcpus)(pagedir_phys_t self)
#endif /* CONFIG_MAX_CPU_COUNT <= BITS_PER_POINTER */
{
	cpuid_t i;
#if CONFIG_MAX_CPU_COUNT <= BITS_PER_POINTER
	cpuset_t result;
#endif /* CONFIG_MAX_CPU_COUNT <= BITS_PER_POINTER */
	/* Find all CPUs that make use of `self' */
	CPUSET_CLEAR(result);
	for (i = 0; i < cpu_count; ++i) {
		if (ATOMIC_READ(cpu_vector[i]->c_pdir) == self)
			CPUSET_INSERT(result, i);
	}
#if CONFIG_MAX_CPU_COUNT <= BITS_PER_POINTER
	return result;
#endif /* CONFIG_MAX_CPU_COUNT <= BITS_PER_POINTER */
}
#endif /* !CONFIG_NO_SMP */


#ifndef CONFIG_NO_SMP
PRIVATE NOBLOCK NONNULL((1, 2)) struct icpustate *
NOTHROW(FCALL ipi_invtlb_one)(struct icpustate *__restrict state,
                              void *args[CPU_IPI_ARGCOUNT]) {
	pagedir_syncone(args[0]);
	return state;
}

PRIVATE NOBLOCK NONNULL((1, 2)) struct icpustate *
NOTHROW(FCALL ipi_invtlb)(struct icpustate *__restrict state,
                          void *args[CPU_IPI_ARGCOUNT]) {
	pagedir_sync(args[0], (size_t)args[1]);
	return state;
}

PRIVATE NOBLOCK NONNULL((1, 2)) struct icpustate *
NOTHROW(FCALL ipi_invtlb_all)(struct icpustate *__restrict state,
                              void *args[CPU_IPI_ARGCOUNT]) {
	(void)args;
	pagedir_syncall();
	return state;
}

PRIVATE NOBLOCK NONNULL((1, 2)) struct icpustate *
NOTHROW(FCALL ipi_invtlb_user)(struct icpustate *__restrict state,
                               void *args[CPU_IPI_ARGCOUNT]) {
	(void)args;
	pagedir_syncall_user();
	return state;
}
#endif /* !CONFIG_NO_SMP */


/* vm syncing functions. These functions must be called when a memory mapping
 * becomes more restrictive, or has been deleted. These functions will
 * automatically send IPIs to all CPUs that are using a given VM, such that
 * the caller may assume that upon return of these functions:
 *  - All CPUs that may have been using `self' will have either synced
 *    their page directory cache to mirror the current mapping state,
 *    or are about to do so no later than the next time such a CPU is
 *    going to enable preemption.
 * Note though that all other vm_*-level APIs already perform syncing
 * automatically, unless otherwise documented by individual functions. */
PUBLIC NOBLOCK void
NOTHROW(FCALL vm_sync)(struct vm *__restrict self,
                       PAGEDIR_PAGEALIGNED UNCHECKED void *addr,
                       PAGEDIR_PAGEALIGNED size_t num_bytes) {
	assertf(((uintptr_t)addr & PAGEMASK) == 0, "addr = %p", addr);
	assertf((num_bytes & PAGEMASK) == 0, "num_bytes = %#" PRIxSIZ, num_bytes);
#ifdef CONFIG_NO_SMP
	if (self == THIS_VM || self == &vm_kernel)
		pagedir_sync(addr, num_bytes);
#else /* CONFIG_NO_SMP */
	{
		void *args[CPU_IPI_ARGCOUNT];
		cpuset_t targets;
		vm_getcpus(self, CPUSET_PTR(targets));
		/* Check for special case: The kernel VM is being synced. */
		if (self == &vm_kernel)
			CPUSET_SETFULL(targets);
		args[0] = (void *)(uintptr_t)addr;
		args[1] = (void *)(uintptr_t)num_bytes;
		cpu_sendipi_cpuset(targets, &ipi_invtlb, args,
		                   CPU_IPI_FWAITFOR |
		                   CPU_IPI_FNOINTR);
	}
#endif /* !CONFIG_NO_SMP */
}

PUBLIC NOBLOCK void
NOTHROW(FCALL vm_syncone)(struct vm *__restrict self,
                          PAGEDIR_PAGEALIGNED UNCHECKED void *addr) {
	assertf(((uintptr_t)addr & PAGEMASK) == 0, "addr = %p", addr);
#ifdef CONFIG_NO_SMP
	if (self == THIS_VM || self == &vm_kernel)
		pagedir_syncone(addr);
#else /* CONFIG_NO_SMP */
	{
		void *args[CPU_IPI_ARGCOUNT];
		cpuset_t targets;
		vm_getcpus(self, CPUSET_PTR(targets));
		/* Check for special case: The kernel VM is being synced. */
		if (self == &vm_kernel)
			CPUSET_SETFULL(targets);
		args[0] = (void *)(uintptr_t)addr;
		cpu_sendipi_cpuset(targets, &ipi_invtlb_one, args,
		                   CPU_IPI_FWAITFOR |
		                   CPU_IPI_FNOINTR);
	}
#endif /* !CONFIG_NO_SMP */
}

PUBLIC NOBLOCK void
NOTHROW(FCALL vm_syncall)(struct vm *__restrict self) {
	/* Check for special case: The kernel VM is being synced. */
	if (self == &vm_kernel) {
		vm_supersyncall();
	} else {
#ifdef CONFIG_NO_SMP
		if (self == THIS_VM)
			pagedir_syncall_user();
#else /* CONFIG_NO_SMP */
		void *args[CPU_IPI_ARGCOUNT];
		cpuset_t targets;
		vm_getcpus(self, CPUSET_PTR(targets));
		cpu_sendipi_cpuset(targets,
		                   &ipi_invtlb_user,
		                   args,
		                   CPU_IPI_FWAITFOR |
		                   CPU_IPI_FNOINTR);
#endif /* !CONFIG_NO_SMP */
	}
}


#ifndef CONFIG_NO_SMP

/* Sync memory within `THIS_VM' */
PUBLIC NOBLOCK void
NOTHROW(FCALL this_vm_sync)(PAGEDIR_PAGEALIGNED UNCHECKED void *addr,
                            PAGEDIR_PAGEALIGNED size_t num_bytes) {
	assertf(((uintptr_t)addr & PAGEMASK) == 0, "addr = %p", addr);
	assertf((num_bytes & PAGEMASK) == 0, "num_bytes = %#" PRIxSIZ, num_bytes);
	if (cpu_online_count > 1) {
		void *args[CPU_IPI_ARGCOUNT];
		cpuset_t targets;
		struct vm *myvm   = THIS_VM;
		struct cpu *mycpu = THIS_CPU;
		vm_getcpus(myvm, CPUSET_PTR(targets));
		/* Check for special case: The kernel VM is being synced. */
		if unlikely(myvm == &vm_kernel)
			CPUSET_SETFULL(targets);
		/* Don't use IPIs for the calling CPU */
		CPUSET_REMOVE(targets, mycpu->c_id);
		args[0] = (void *)(uintptr_t)addr;
		args[1] = (void *)(uintptr_t)num_bytes;
		cpu_sendipi_cpuset(targets,
		                   &ipi_invtlb,
		                   args,
		                   CPU_IPI_FWAITFOR |
		                   CPU_IPI_FNOINTR);
	}
	pagedir_sync(addr, num_bytes);
}

PUBLIC NOBLOCK void
NOTHROW(FCALL this_vm_syncone)(PAGEDIR_PAGEALIGNED UNCHECKED void *addr) {
	assertf(((uintptr_t)addr & PAGEMASK) == 0, "addr = %p", addr);
	if (cpu_online_count > 1) {
		void *args[CPU_IPI_ARGCOUNT];
		cpuset_t targets;
		struct vm *myvm   = THIS_VM;
		struct cpu *mycpu = THIS_CPU;
		vm_getcpus(myvm, CPUSET_PTR(targets));
		/* Check for special case: The kernel VM is being synced. */
		if unlikely(myvm == &vm_kernel)
			CPUSET_SETFULL(targets);
		/* Don't use IPIs for the calling CPU */
		CPUSET_REMOVE(targets, mycpu->c_id);
		args[0] = (void *)(uintptr_t)addr;
		cpu_sendipi_cpuset(targets,
		                   &ipi_invtlb_one,
		                   args,
		                   CPU_IPI_FWAITFOR |
		                   CPU_IPI_FNOINTR);
	}
	pagedir_syncone(addr);
}
#endif /* !CONFIG_NO_SMP */


PUBLIC NOBLOCK void
NOTHROW(FCALL this_vm_syncall)(void) {
	struct vm *myvm = THIS_VM;
#ifndef CONFIG_NO_SMP
	if (cpu_online_count > 1) {
		void *args[CPU_IPI_ARGCOUNT];
		cpuset_t targets;
		struct cpu *mycpu = THIS_CPU;
		vm_getcpus(myvm, CPUSET_PTR(targets));
		/* Check for special case: The kernel VM is being synced. */
		if unlikely(myvm == &vm_kernel)
			CPUSET_SETFULL(targets);
		/* Don't use IPIs for the calling CPU */
		CPUSET_REMOVE(targets, mycpu->c_id);
		cpu_sendipi_cpuset(targets,
		                   myvm == &vm_kernel ? &ipi_invtlb_all
		                                      : &ipi_invtlb_user,
		                   args,
		                   CPU_IPI_FWAITFOR |
		                   CPU_IPI_FNOINTR);
	}
#endif /* !CONFIG_NO_SMP */
	if (myvm == &vm_kernel) {
		pagedir_syncall();
	} else {
		pagedir_syncall_user();
	}
}




#ifndef CONFIG_NO_SMP
/* Same as above, but these functions are specifically designed to optimally
 * sync changes made to the kernel VM. */
PUBLIC NOBLOCK void
NOTHROW(FCALL vm_supersync)(PAGEDIR_PAGEALIGNED UNCHECKED void *addr,
                              PAGEDIR_PAGEALIGNED size_t num_bytes) {
	assertf(((uintptr_t)addr & PAGEMASK) == 0, "addr = %p", addr);
	assertf((num_bytes & PAGEMASK) == 0, "num_bytes = %#" PRIxSIZ, num_bytes);
	if (cpu_online_count > 1) {
		void *args[CPU_IPI_ARGCOUNT];
		args[0] = (void *)(uintptr_t)addr;
		args[1] = (void *)(uintptr_t)num_bytes;
		cpu_broadcastipi_notthis(&ipi_invtlb, args,
		                         CPU_IPI_FWAITFOR |
		                         CPU_IPI_FNOINTR);
	}
	pagedir_sync(addr, num_bytes);
}

PUBLIC NOBLOCK void
NOTHROW(FCALL vm_supersyncone)(PAGEDIR_PAGEALIGNED UNCHECKED void *addr) {
	assertf(((uintptr_t)addr & PAGEMASK) == 0, "addr = %p", addr);
	if (cpu_online_count > 1) {
		void *args[CPU_IPI_ARGCOUNT];
		args[0] = (void *)(uintptr_t)addr;
		cpu_broadcastipi_notthis(&ipi_invtlb_one, args,
		                         CPU_IPI_FWAITFOR |
		                         CPU_IPI_FNOINTR);
	}
	pagedir_syncone(addr);
}

PUBLIC NOBLOCK void
NOTHROW(FCALL vm_supersyncall)(void) {
	if (cpu_online_count > 1) {
		void *args[CPU_IPI_ARGCOUNT];
		cpu_broadcastipi_notthis(&ipi_invtlb_all, args,
		                         CPU_IPI_FWAITFOR |
		                         CPU_IPI_FNOINTR);
	}
	pagedir_syncall();
}


/* Sync memory on every CPU with `CPU->c_vm->v_pdir_phys == pagedir' */
PUBLIC NOBLOCK void
NOTHROW(FCALL pagedir_sync_smp_p)(pagedir_phys_t pagedir,
                                  PAGEDIR_PAGEALIGNED UNCHECKED void *addr,
                                  PAGEDIR_PAGEALIGNED size_t num_bytes) {
	void *args[CPU_IPI_ARGCOUNT];
	cpuset_t targets;
	assertf(((uintptr_t)addr & PAGEMASK) == 0, "addr = %p", addr);
	assertf((num_bytes & PAGEMASK) == 0, "num_bytes = %#" PRIxSIZ, num_bytes);
	pagedir_getcpus(pagedir, CPUSET_PTR(targets));
	args[0] = (void *)(uintptr_t)addr;
	args[1] = (void *)(uintptr_t)num_bytes;
	cpu_sendipi_cpuset(targets, &ipi_invtlb, args,
	                   CPU_IPI_FWAITFOR |
	                   CPU_IPI_FNOINTR);
}

PUBLIC NOBLOCK void
NOTHROW(FCALL pagedir_syncone_smp_p)(pagedir_phys_t pagedir,
                                     PAGEDIR_PAGEALIGNED UNCHECKED void *addr) {
	void *args[CPU_IPI_ARGCOUNT];
	cpuset_t targets;
	assertf(((uintptr_t)addr & PAGEMASK) == 0, "addr = %p", addr);
	pagedir_getcpus(pagedir, CPUSET_PTR(targets));
	args[0] = (void *)(uintptr_t)addr;
	cpu_sendipi_cpuset(targets,
	                   &ipi_invtlb_one,
	                   args,
	                   CPU_IPI_FWAITFOR |
	                   CPU_IPI_FNOINTR);
}

PUBLIC NOBLOCK void
NOTHROW(FCALL pagedir_syncall_smp_p)(pagedir_phys_t pagedir) {
	void *args[CPU_IPI_ARGCOUNT];
	cpuset_t targets;
	pagedir_getcpus(pagedir, CPUSET_PTR(targets));
	cpu_sendipi_cpuset(targets,
	                   &ipi_invtlb_all,
	                   args,
	                   CPU_IPI_FWAITFOR |
	                   CPU_IPI_FNOINTR);
}

/* Sync memory on every CPU with `CPU->c_vm->v_pdir_phys == pagedir_get()' */
PUBLIC NOBLOCK void
NOTHROW(FCALL pagedir_sync_smp)(PAGEDIR_PAGEALIGNED UNCHECKED void *addr,
                                PAGEDIR_PAGEALIGNED size_t num_bytes) {
	assertf(((uintptr_t)addr & PAGEMASK) == 0, "addr = %p", addr);
	assertf((num_bytes & PAGEMASK) == 0, "num_bytes = %#" PRIxSIZ, num_bytes);
	if (cpu_online_count > 1) {
		void *args[CPU_IPI_ARGCOUNT];
		cpuset_t targets;
		pagedir_phys_t pagedir;
		pagedir = pagedir_get();
		pagedir_getcpus(pagedir, CPUSET_PTR(targets));
		CPUSET_REMOVE(targets, THIS_CPU->c_id);
		args[0] = (void *)(uintptr_t)addr;
		args[1] = (void *)(uintptr_t)num_bytes;
		cpu_sendipi_cpuset(targets,
		                   &ipi_invtlb,
		                   args,
		                   CPU_IPI_FWAITFOR |
		                   CPU_IPI_FNOINTR);
	}
	pagedir_sync(addr, num_bytes);
}

PUBLIC NOBLOCK void
NOTHROW(FCALL pagedir_syncone_smp)(PAGEDIR_PAGEALIGNED UNCHECKED void *addr) {
	assertf(((uintptr_t)addr & PAGEMASK) == 0, "addr = %p", addr);
	if (cpu_online_count > 1) {
		void *args[CPU_IPI_ARGCOUNT];
		cpuset_t targets;
		pagedir_phys_t pagedir;
		pagedir = pagedir_get();
		pagedir_getcpus(pagedir, CPUSET_PTR(targets));
		CPUSET_REMOVE(targets, THIS_CPU->c_id);
		args[0] = (void *)(uintptr_t)addr;
		cpu_sendipi_cpuset(targets,
		                   &ipi_invtlb_one,
		                   args,
		                   CPU_IPI_FWAITFOR |
		                   CPU_IPI_FNOINTR);
	}
	pagedir_syncone(addr);
}

PUBLIC NOBLOCK void
NOTHROW(FCALL pagedir_syncall_smp)(void) {
	if (cpu_online_count > 1) {
		void *args[CPU_IPI_ARGCOUNT];
		cpuset_t targets;
		pagedir_phys_t pagedir = pagedir_get();
		pagedir_getcpus(pagedir, CPUSET_PTR(targets));
		CPUSET_REMOVE(targets, THIS_CPU->c_id);
		cpu_sendipi_cpuset(targets,
		                   &ipi_invtlb_all,
		                   args,
		                   CPU_IPI_FWAITFOR |
		                   CPU_IPI_FNOINTR);
	}
	pagedir_syncall();
}
#endif /* !CONFIG_NO_SMP */




DECL_END

#endif /* !GUARD_KERNEL_SRC_MEMORY_VM_SYNC_C */
