/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_CORE_ARCH_I386_FAULT_EMULOCK_C
#define GUARD_KERNEL_CORE_ARCH_I386_FAULT_EMULOCK_C 1
#define _KOS_SOURCE 1
#define DISABLE_BRANCH_PROFILING

#include <kernel/compiler.h>

#include <kernel/except.h>
#include <kernel/mman.h>
#include <kernel/mman/fault.h>
#include <kernel/mman/mfile.h>
#include <kernel/mman/mnode.h>
#include <kernel/mman/mpart.h>
#include <kernel/types.h>
#include <kernel/x86/emulock.h>
#include <sched/cpu.h>

#include <hybrid/align.h>
#include <hybrid/sched/preemption.h>

#include <asm/cacheline.h>
#include <asm/intrin.h>
#include <kos/kernel/cpu-state-helpers.h>
#include <kos/kernel/cpu-state.h>
#include <kos/nopf.h>

#include <stdbool.h>
#include <string.h>

#include <libvio/access.h>

#ifdef ARCH_X86_HAVE_EMULOCK

DECL_BEGIN

/* atomics _CAN_ be emulated:
 *  >> u32 emu_cmpxchl(u32 *p, u32 o, u32 n) {
 *  >>     preemption_flag_t was;
 *  >>     struct cpu *me = THIS_CPU;
 *  >>     u32 result;
 *  >>     preemption_pushoff(&was);
 *  >>     ENSURE_PAGE_LOADED_INTO_MEMORY(p);
 *  >>     ACQUIRE_BUS_LOCK();
 *  >>     result = *p;
 *  >>     if (result == o)
 *  >>         *p = n;
 *  >>     RELEASE_BUS_LOCK();
 *  >>     preemption_pop(&was);
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
#elif 1 /* `xchg' was already available, and was already atomic on the 8086, so we can simply use it! */

PRIVATE u8 buslock = 0;

LOCAL NOBLOCK u8
NOTHROW(KCALL buslock_xch)(u8 value) {
	u8 result;
	__asm__ __volatile__("xchgb %b0, %b1"
	                     : "=r" (result)
	                     : "m" (buslock)
	                     , "0" (value));
	return result;
}

LOCAL NOBLOCK bool
NOTHROW(KCALL bus_tryacquirelock)(void) {
	return buslock_xch(1) == 0;
}

LOCAL NOBLOCK void
NOTHROW(KCALL bus_acquirelock)(void) {
	while (!bus_tryacquirelock())
		__pause();
}

LOCAL NOBLOCK void
NOTHROW(KCALL bus_releaselock)(void) {
	buslock_xch(0);
}

#else /* CONFIG_NO_SMP */
PRIVATE ATTR_ALIGNED(__ARCH_CACHELINESIZE) bool volatile bus_flags[CONFIG_MAX_CPU_COUNT];
PRIVATE ATTR_PERCPU bool thiscpu_busline7 = false;

PRIVATE NOBLOCK bool
NOTHROW(KCALL bus_tryacquirelock)(void) {
	struct cpu *me = THIS_CPU;
	unsigned int i, myid = me->c_id;
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
	unsigned int myid   = me->c_id;
	COMPILER_BARRIER();
	FORCPU(me, thiscpu_busline7) = false;
	COMPILER_BARRIER();
	bus_flags[myid] = false;
	COMPILER_BARRIER();
}
#endif /* CONFIG_NO_SMP */


#define EMULOCK_MAXBYTES 1
#ifdef ARCH_X86_HAVE_EMULOCK_CMPXCHW
#undef EMULOCK_MAXBYTES
#define EMULOCK_MAXBYTES 2
#endif /* ARCH_X86_HAVE_EMULOCK_CMPXCHW */

#ifdef ARCH_X86_HAVE_EMULOCK_CMPXCHL
#undef EMULOCK_MAXBYTES
#define EMULOCK_MAXBYTES 4
#endif /* ARCH_X86_HAVE_EMULOCK_CMPXCHL */

#ifdef ARCH_X86_HAVE_EMULOCK_CMPXCHQ
#undef EMULOCK_MAXBYTES
#define EMULOCK_MAXBYTES 8
#endif /* ARCH_X86_HAVE_EMULOCK_CMPXCHQ */

#ifdef ARCH_X86_HAVE_EMULOCK_CMPXCHX
#undef EMULOCK_MAXBYTES
#define EMULOCK_MAXBYTES 16
#endif /* ARCH_X86_HAVE_EMULOCK_CMPXCHX */


PRIVATE void KCALL
x86_emulock_cmpxch(struct icpustate **__restrict pstate,
                   NCX void *addr,
                   void *preal_oldval,
                   void *poldval,
                   void *pnewval,
                   size_t num_bytes) {
	preemption_flag_t was;
	size_t error;
	byte_t real_oldval[EMULOCK_MAXBYTES];
again:
	preemption_pushoff(&was);
	/* TODO: In SMP, we must send a  (preferably NMI) IPI to all  other
	 *       CPUs, and tell them to temporarily halt what they're doing
	 *       until we're done here.
	 *       That's the only way to ensure that what we do in here will
	 *       really  happen  atomically  in regards  to  anything else! */
	bus_acquirelock();
	error = memcpy_nopf(real_oldval, addr, num_bytes);
	if unlikely(error != 0)
		goto handle_vio_or_not_faulted;
	if (bcmp(real_oldval, poldval, num_bytes) == 0) {
		error = memcpy_nopf(addr, pnewval, num_bytes);
		if unlikely(error != 0)
			goto handle_vio_or_not_faulted;
	}
	bus_releaselock();
	preemption_pop(&was);
	memcpy(preal_oldval, real_oldval, num_bytes);
	return;
handle_vio_or_not_faulted:
	bus_releaselock();
	preemption_pop(&was);
	{
		/* Check if this is a VIO segment (or maybe not mapped at all) */
		struct mman *effective_mman;
		struct mnode *node;
#ifdef LIBVIO_CONFIG_ENABLED
		void *node_minaddr;
		pos_t part_minaddr;
		REF struct mpart *part;
#endif /* LIBVIO_CONFIG_ENABLED */
		effective_mman = &mman_kernel;
		if (ADDR_ISUSER(addr))
			effective_mman = THIS_MMAN;
		mman_lock_read(effective_mman);
		node = mman_mappings_locate(effective_mman, addr);
		/* Check for an unmapped memory location. */
		if (!node || !node->mn_part) {
			uintptr_t context;
			mman_lock_endread(effective_mman);
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
		if ((node->mn_flags & (MNODE_F_PREAD | MNODE_F_PWRITE)) !=
		    /*             */ (MNODE_F_PREAD | MNODE_F_PWRITE)) {
			uintptr_half_t prot = node->mn_flags;
			uintptr_t context;
			mman_lock_endread(effective_mman);
			context = 0;
			if (icpustate_isuser(*pstate))
				context |= E_SEGFAULT_CONTEXT_USERCODE;
			if (prot & MNODE_F_PREAD) {
				THROW(E_SEGFAULT_READONLY,
				      addr,
				      E_SEGFAULT_CONTEXT_WRITING | context);
			} else {
				THROW(E_SEGFAULT_NOTREADABLE,
				      addr,
				      context);
			}
		}
#ifdef LIBVIO_CONFIG_ENABLED
		node_minaddr = mnode_getminaddr(node);
		part         = incref(node->mn_part);
		part_minaddr = mpart_getminaddr(part);
#endif /* LIBVIO_CONFIG_ENABLED */
		mman_lock_endread(effective_mman);
#ifdef LIBVIO_CONFIG_ENABLED
		{
			REF struct mfile *file;
			FINALLY_DECREF_UNLIKELY(part);
			mpart_lock_acquire(part);
			file = incref(part->mp_file);
			mpart_lock_release(part);
			FINALLY_DECREF_UNLIKELY(file);
			if (file->mf_ops->mo_vio) {
				/* Handle VIO memory access. */
				struct vioargs args;
				vio_addr_t vio_addr;
				args.va_ops          = file->mf_ops->mo_vio;
				args.va_file         = file;
				args.va_acmap_offset = part_minaddr;
				args.va_acmap_page   = node_minaddr;
				args.va_state        = *pstate;
				vio_addr = args.va_acmap_offset + ((uintptr_t)addr - (uintptr_t)node_minaddr);
				switch (num_bytes) {

#ifdef ARCH_X86_HAVE_EMULOCK_CMPXCHB
				case 1:
					*(u8 *)preal_oldval = vio_cmpxchb(&args, vio_addr,
					                                  *(u8 const *)poldval,
					                                  *(u8 const *)pnewval,
					                                  true);
					break;
#endif /* ARCH_X86_HAVE_EMULOCK_CMPXCHB */

#ifdef ARCH_X86_HAVE_EMULOCK_CMPXCHW
				case 2:
					*(u16 *)preal_oldval = vio_cmpxchw(&args, vio_addr,
					                                   *(u16 const *)poldval,
					                                   *(u16 const *)pnewval,
					                                   true);
					break;
#endif /* ARCH_X86_HAVE_EMULOCK_CMPXCHW */

#ifdef ARCH_X86_HAVE_EMULOCK_CMPXCHL
				case 4:
					*(u32 *)preal_oldval = vio_cmpxchl(&args, vio_addr,
					                                   *(u32 const *)poldval,
					                                   *(u32 const *)pnewval,
					                                   true);
					break;
#endif /* ARCH_X86_HAVE_EMULOCK_CMPXCHL */

#ifdef ARCH_X86_HAVE_EMULOCK_CMPXCHQ
				case 8:
					*(u64 *)preal_oldval = vio_cmpxchq(&args, vio_addr,
					                                   *(u64 const *)poldval,
					                                   *(u64 const *)pnewval,
					                                   true);
					break;
#endif /* ARCH_X86_HAVE_EMULOCK_CMPXCHQ */

#ifdef ARCH_X86_HAVE_EMULOCK_CMPXCHX
				case 16:
					*(uint128_t *)preal_oldval = vio_cmpxchx(&args, vio_addr,
					                                         *(uint128_t const *)poldval,
					                                         *(uint128_t const *)pnewval,
					                                         true);
					break;
#endif /* ARCH_X86_HAVE_EMULOCK_CMPXCHX */

				default:
					__builtin_unreachable();
				}
				*pstate = args.va_state;
				return;
			}
		}
#endif /* LIBVIO_CONFIG_ENABLED */
		/* We can get here if the given address hasn't been pre-faulted, yet. */
		mman_forcefault(effective_mman, addr, num_bytes,
		                MMAN_FAULT_F_WRITE);
		goto again;
	}
}


#ifdef ARCH_X86_HAVE_EMULOCK_CMPXCHB
PUBLIC u8 KCALL
x86_emulock_cmpxchb(struct icpustate **__restrict pstate,
                    NCX u8 *addr,
                    u8 oldval, u8 newval) {
	u8 real_oldval;
	x86_emulock_cmpxch(pstate, addr, &real_oldval, &oldval, &newval, 1);
	return real_oldval;
}
#endif /* ARCH_X86_HAVE_EMULOCK_CMPXCHB */

#ifdef ARCH_X86_HAVE_EMULOCK_CMPXCHW
PUBLIC u16 KCALL
x86_emulock_cmpxchw(struct icpustate **__restrict pstate,
                    NCX u16 *addr,
                    u16 oldval, u16 newval) {
	u16 real_oldval;
	x86_emulock_cmpxch(pstate, addr, &real_oldval, &oldval, &newval, 2);
	return real_oldval;
}
#endif /* ARCH_X86_HAVE_EMULOCK_CMPXCHW */

#ifdef ARCH_X86_HAVE_EMULOCK_CMPXCHL
PUBLIC u32 KCALL
x86_emulock_cmpxchl(struct icpustate **__restrict pstate,
                    NCX u32 *addr,
                    u32 oldval, u32 newval) {
	u32 real_oldval;
	x86_emulock_cmpxch(pstate, addr, &real_oldval, &oldval, &newval, 4);
	return real_oldval;
}
#endif /* ARCH_X86_HAVE_EMULOCK_CMPXCHL */

#ifdef ARCH_X86_HAVE_EMULOCK_CMPXCHQ
PUBLIC u64 KCALL
x86_emulock_cmpxchq(struct icpustate **__restrict pstate,
                    NCX u64 *addr,
                    u64 oldval, u64 newval) {
	u64 real_oldval;
	x86_emulock_cmpxch(pstate, addr, &real_oldval, &oldval, &newval, 8);
	return real_oldval;
}
#endif /* ARCH_X86_HAVE_EMULOCK_CMPXCHQ */

#ifdef ARCH_X86_HAVE_EMULOCK_CMPXCHX
PUBLIC uint128_t KCALL
x86_emulock_cmpxchx(struct icpustate **__restrict pstate,
                    NCX uint128_t *addr,
                    uint128_t oldval, uint128_t newval) {
	uint128_t real_oldval;
	x86_emulock_cmpxch(pstate, addr, &real_oldval, &oldval, &newval, 16);
	return real_oldval;
}
#endif /* ARCH_X86_HAVE_EMULOCK_CMPXCHX */


DECL_END
#endif /* ARCH_X86_HAVE_EMULOCK */

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_FAULT_EMULOCK_C */
