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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_FAULT_EMULOCK_C
#define GUARD_KERNEL_CORE_ARCH_I386_FAULT_EMULOCK_C 1
#define _KOS_SOURCE 1
#define DISABLE_BRANCH_PROFILING 1

#include <kernel/compiler.h>

#include <kernel/emulock.h>
#include <kernel/except.h>
#include <kernel/types.h>
#include <kernel/vio.h>
#include <kernel/vm.h>
#include <sched/cpu.h>
#include <sched/task.h>

#include <asm/cacheline.h>
#include <asm/intrin.h>
#include <kos/kernel/cpu-state-helpers.h>
#include <kos/kernel/cpu-state.h>

#include <stdbool.h>
#include <string.h>

#ifdef CONFIG_HAVE_EMULOCK

DECL_BEGIN

/* atomics _CAN_ be emulated:
 *  >> u32 emu_cmpxchl(u32 *p, u32 o, u32 n) {
 *  >>     pflag_t was;
 *  >>     struct cpu *me = THIS_CPU;
 *  >>     u32 result;
 *  >>     was = PREEMPTION_PUSHOFF();
 *  >>     ENSURE_PAGE_LOADED_INTO_MEMORY(p);
 *  >>     ACQUIRE_BUS_LOCK();
 *  >>     result = *p;
 *  >>     if (result == o)
 *  >>         *p = n;
 *  >>     RELEASE_BUS_LOCK();
 *  >>     PREEMPTION_POP(was);
 *  >>     return result;
 *  >> }
 * The BUS_LOCK can be implemented using this:
 * https://stackoverflow.com/questions/33270575/implementing-mutual-exclusion-algorithm-by-burns-and-lynch-in-java-could-there
 * http://groups.csail.mit.edu/tds/papers/Lynch/allertonconf.pdf
 */

#ifdef CONFIG_NO_SMP
#define bus_tryacquirelock()  true
#define bus_acquirelock()     COMPILER_BARRIER()
#define bus_releaselock()     COMPILER_BARRIER()
#else /* CONFIG_NO_SMP */
PRIVATE ATTR_ALIGNED(__ARCH_CACHELINESIZE) bool volatile bus_flags[CONFIG_MAX_CPU_COUNT];
PRIVATE ATTR_PERCPU bool thiscpu_busline7 = false;

PRIVATE NOBLOCK bool
NOTHROW(KCALL bus_tryacquirelock)(void) {
	struct cpu *me = THIS_CPU;
	cpuid_t i, myid = me->c_id;
	if (!FORCPU(me, thiscpu_busline7)) {
		COMPILER_BARRIER();
		bus_flags[myid] = false; /* down */
		COMPILER_BARRIER();
		for (i = 0; i < myid; ++i) {
			if (bus_flags[i])
				return false;
		}
		COMPILER_BARRIER();
		bus_flags[myid] = true; /* up */
		COMPILER_BARRIER();
		for (i = 0; i < myid; ++i) {
			if (bus_flags[i])
				return false;
		}
		COMPILER_BARRIER();
		FORCPU(me, thiscpu_busline7) = true;
		COMPILER_BARRIER();
	}
	COMPILER_BARRIER();
	for (i = myid + 1; i < cpu_count; ++i) {
		if (bus_flags[i])
			return false;
	}
	COMPILER_BARRIER();
	return true;
}
PRIVATE void NOTHROW(KCALL bus_acquirelock)(void) {
	while (!bus_tryacquirelock())
		__pause();
}

PRIVATE NOBLOCK void
NOTHROW(KCALL bus_releaselock)(void) {
	struct cpu *me = THIS_CPU;
	cpuid_t myid   = me->c_id;
	COMPILER_BARRIER();
	FORCPU(me, thiscpu_busline7) = false;
	COMPILER_BARRIER();
	bus_flags[myid] = false;
	COMPILER_BARRIER();
}
#endif /* CONFIG_NO_SMP */


#define EMULOCK_MAXBYTES 1
#ifdef CONFIG_EMULOCK_HAVE_CMPXCHG16
#undef EMULOCK_MAXBYTES
#define EMULOCK_MAXBYTES 2
#endif /* CONFIG_EMULOCK_HAVE_CMPXCHG16 */

#ifdef CONFIG_EMULOCK_HAVE_CMPXCHG32
#undef EMULOCK_MAXBYTES
#define EMULOCK_MAXBYTES 4
#endif /* CONFIG_EMULOCK_HAVE_CMPXCHG32 */

#ifdef CONFIG_EMULOCK_HAVE_CMPXCHG64
#undef EMULOCK_MAXBYTES
#define EMULOCK_MAXBYTES 8
#endif /* CONFIG_EMULOCK_HAVE_CMPXCHG64 */

#ifdef CONFIG_EMULOCK_HAVE_CMPXCHG128
#undef EMULOCK_MAXBYTES
#define EMULOCK_MAXBYTES 16
#endif /* CONFIG_EMULOCK_HAVE_CMPXCHG128 */


PRIVATE void KCALL
x86_emulock_cmpxchg(struct icpustate **__restrict pstate,
                    USER CHECKED void *addr,
                    void *preal_oldval,
                    void *poldval,
                    void *pnewval,
                    size_t num_bytes) {
	pflag_t was;
	size_t error;
	byte_t real_oldval[EMULOCK_MAXBYTES];
again:
	was = PREEMPTION_PUSHOFF();
	bus_acquirelock();
	error = memcpy_nopf(real_oldval, addr, num_bytes);
	if unlikely(error != 0)
		goto handle_vio_or_not_faulted;
	if (memcmp(real_oldval, poldval, num_bytes) == 0) {
		error = memcpy_nopf(addr, pnewval, num_bytes);
		if unlikely(error != 0)
			goto handle_vio_or_not_faulted;
	}
	bus_releaselock();
	PREEMPTION_POP(was);
	memcpy(preal_oldval, real_oldval, num_bytes);
	return;
handle_vio_or_not_faulted:
	bus_releaselock();
	PREEMPTION_POP(was);
	{
		/* Check if this is a VIO segment (or maybe not mapped at all) */
		struct vm *effective_vm = THIS_VM;
		struct vm_node *node;
		pageid_t addr_page;
#ifdef CONFIG_VIO
		void *node_minaddr;
		REF struct vm_datapart *part;
		REF struct vm_datablock *block;
#endif /* CONFIG_VIO */
		if (ADDR_IS_KERNEL(addr))
			effective_vm = &vm_kernel;
		addr_page = PAGEID_ENCODE(addr);
		sync_read(effective_vm);
		node = vm_getnodeofpageid(effective_vm, addr_page);
		/* Check for an unmapped memory location. */
		if (!node || !node->vn_block) {
			uintptr_t context;
			sync_endread(effective_vm);
			context = 0;
#ifdef __x86_64__
			if (ADDR_IS_NONCANON((uintptr_t)addr))
				context |= E_SEGFAULT_CONTEXT_NONCANON;
#endif /* __x86_64__ */
			THROW(E_SEGFAULT_UNMAPPED,
			      addr,
			      context);
		}
		/* Check for read+write permissions. */
		if ((node->vn_prot & (VM_PROT_READ | VM_PROT_WRITE)) !=
		    /*            */ (VM_PROT_READ | VM_PROT_WRITE)) {
			uintptr_half_t prot = node->vn_prot;
			uintptr_t context;
			sync_endread(effective_vm);
			context = 0;
			if (icpustate_isuser(*pstate))
				context |= E_SEGFAULT_CONTEXT_USERCODE;
			if (prot & VM_PROT_READ) {
				THROW(E_SEGFAULT_READONLY,
				      addr,
				      E_SEGFAULT_CONTEXT_WRITING | context);
			} else {
				THROW(E_SEGFAULT_NOTREADABLE,
					  addr,
				      context);
			}
		}
#ifdef CONFIG_VIO
		node_minaddr = vm_node_getmin(node);
		block        = incref(node->vn_block);
		part         = xincref(node->vn_part);
#endif /* CONFIG_VIO */
		sync_endread(effective_vm);
#ifdef CONFIG_VIO
		{
			FINALLY_DECREF_UNLIKELY(part);
			FINALLY_DECREF_UNLIKELY(block);
			if (block->db_vio) {
				/* Handle VIO memory access. */
				struct vio_args args;
				pos_t vio_addr;
				args.va_type            = block->db_vio;
				args.va_block           = block;
				args.va_part            = part;
				args.va_access_partoff  = vm_datapart_minbyte(part);
				args.va_access_pageid   = addr_page;
				args.va_state           = *pstate;
				vio_addr = args.va_access_partoff + ((uintptr_t)addr -
				                                     (uintptr_t)node_minaddr);
				switch (num_bytes) {

#ifdef CONFIG_EMULOCK_HAVE_CMPXCHG8
				case 1:
					*(u8 *)preal_oldval = vio_cmpxchb(&args, vio_addr,
					                                  *(u8 *)poldval,
					                                  *(u8 *)pnewval,
					                                  true);
					break;
#endif /* CONFIG_EMULOCK_HAVE_CMPXCHG8 */

#ifdef CONFIG_EMULOCK_HAVE_CMPXCHG16
				case 2:
					*(u16 *)preal_oldval = vio_cmpxchw(&args, vio_addr,
					                                   *(u16 *)poldval,
					                                   *(u16 *)pnewval,
					                                   true);
					break;
#endif /* CONFIG_EMULOCK_HAVE_CMPXCHG16 */

#ifdef CONFIG_EMULOCK_HAVE_CMPXCHG32
				case 4:
					*(u32 *)preal_oldval = vio_cmpxchl(&args, vio_addr,
					                                   *(u32 *)poldval,
					                                   *(u32 *)pnewval,
					                                   true);
					break;
#endif /* CONFIG_EMULOCK_HAVE_CMPXCHG32 */

#ifdef CONFIG_EMULOCK_HAVE_CMPXCHG64
				case 8:
					*(u64 *)preal_oldval = vio_cmpxchq(&args, vio_addr,
					                                   *(u64 *)poldval,
					                                   *(u64 *)pnewval,
					                                   true);
					break;
#endif /* CONFIG_EMULOCK_HAVE_CMPXCHG64 */

#ifdef CONFIG_EMULOCK_HAVE_CMPXCHG128
				case 16:
					*(uint128_t *)preal_oldval = vio_cmpxch128(&args, vio_addr,
					                                           *(uint128_t *)poldval,
					                                           *(uint128_t *)pnewval,
					                                           true);
					break;
#endif /* CONFIG_EMULOCK_HAVE_CMPXCHG128 */

				default:
					__builtin_unreachable();
				}
				*pstate = args.va_state;
				return;
			}
		}
#endif /* CONFIG_VIO */
		/* We can get here if the given address hasn't been pre-faulted, yet. */
		vm_paged_forcefault(effective_vm,
		                    addr_page,
		                    PAGEID_ENCODE((byte_t *)addr + num_bytes - 1),
		                    true);
		goto again;
	}
}


#ifdef CONFIG_EMULOCK_HAVE_CMPXCHG8
PUBLIC u8 KCALL
x86_emulock_cmpxchg8(struct icpustate **__restrict pstate,
                     USER CHECKED u8 *addr,
                     u8 oldval, u8 newval) {
	u8 real_oldval;
	x86_emulock_cmpxchg(pstate, addr, &real_oldval, &oldval, &newval, 1);
	return real_oldval;
}
#endif /* CONFIG_EMULOCK_HAVE_CMPXCHG8 */

#ifdef CONFIG_EMULOCK_HAVE_CMPXCHG16
PUBLIC u16 KCALL
x86_emulock_cmpxchg16(struct icpustate **__restrict pstate,
                      USER CHECKED u16 *addr,
                      u16 oldval, u16 newval) {
	u16 real_oldval;
	x86_emulock_cmpxchg(pstate, addr, &real_oldval, &oldval, &newval, 2);
	return real_oldval;
}
#endif /* CONFIG_EMULOCK_HAVE_CMPXCHG16 */

#ifdef CONFIG_EMULOCK_HAVE_CMPXCHG32
PUBLIC u32 KCALL
x86_emulock_cmpxchg32(struct icpustate **__restrict pstate,
                      USER CHECKED u32 *addr,
                      u32 oldval, u32 newval) {
	u32 real_oldval;
	x86_emulock_cmpxchg(pstate, addr, &real_oldval, &oldval, &newval, 4);
	return real_oldval;
}
#endif /* CONFIG_EMULOCK_HAVE_CMPXCHG32 */

#ifdef CONFIG_EMULOCK_HAVE_CMPXCHG64
PUBLIC u64 KCALL
x86_emulock_cmpxchg64(struct icpustate **__restrict pstate,
                      USER CHECKED u64 *addr,
                      u64 oldval, u64 newval) {
	u64 real_oldval;
	x86_emulock_cmpxchg(pstate, addr, &real_oldval, &oldval, &newval, 8);
	return real_oldval;
}
#endif /* CONFIG_EMULOCK_HAVE_CMPXCHG64 */

#ifdef CONFIG_EMULOCK_HAVE_CMPXCHG128
PUBLIC uint128_t KCALL
x86_emulock_cmpxchg128(struct icpustate **__restrict pstate,
                       USER CHECKED uint128_t *addr,
                       uint128_t oldval, uint128_t newval) {
	uint128_t real_oldval;
	x86_emulock_cmpxchg(pstate, addr, &real_oldval, &oldval, &newval, 16);
	return real_oldval;
}
#endif /* CONFIG_EMULOCK_HAVE_CMPXCHG128 */


DECL_END
#endif /* CONFIG_HAVE_EMULOCK */

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_FAULT_EMULOCK_C */
