/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_CORE_ARCH_I386_SCHED_SMP_C
#define GUARD_KERNEL_CORE_ARCH_I386_SCHED_SMP_C 1
#define DISABLE_BRANCH_PROFILING /* Don't profile this file */
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/driver-param.h>
#include <kernel/mman/mpart.h>
#include <kernel/paging.h>
#include <kernel/printk.h>
#include <kernel/x86/apic.h>
#include <kernel/x86/pic.h>
#include <sched/cpu.h>
#include <sched/task.h>
#include <sched/x86/smp.h>

#include <hybrid/align.h>
#include <hybrid/unaligned.h>

#include <inttypes.h>
#include <stddef.h>
#include <stdint.h>

DECL_BEGIN

/* MMan nodes / parts for the LAPIC identity mapping. */
INTDEF struct mpart x86_lapic_mpart;
INTDEF struct mnode x86_lapic_mnode;

PRIVATE ATTR_PURE ATTR_FREETEXT byte_t
NOTHROW(KCALL smp_memsum)(void const *__restrict p, size_t n_bytes) {
	byte_t result = 0;
	byte_t *iter, *end;
	end = (iter = (byte_t *)p) + n_bytes;
	for (; iter != end; ++iter)
		result += *iter;
	return result;
}

PRIVATE ATTR_FREETEXT MpFloatingPointerStructure *
NOTHROW(KCALL Mp_LocateFloatingPointerStructureInAddressRange)(VIRT uintptr_t base, size_t bytes) {
	uintptr_t iter, end;
	/* Make sure not to search unmapped memory! */
	if (base < KERNEL_CORE_BASE) {
		base += bytes;
		if (base <= KERNEL_CORE_BASE)
			return NULL;
		bytes = base - KERNEL_CORE_BASE;
		base  = KERNEL_CORE_BASE;
	}
	if ((base + bytes) < base)
		bytes = 0 - base;
	end = (iter = (uintptr_t)base) + bytes;
	printk(FREESTR(KERN_DEBUG "[smp] Searching for MpFloatingPointerStructure in %p...%p\n"),
	       iter - KERNEL_CORE_BASE, (end - 1) - KERNEL_CORE_BASE);
	/* Clamp the search area to a 16-byte alignment. */
	iter = CEIL_ALIGN(iter, MPFPS_ALIGN);
	end  = FLOOR_ALIGN(end, MPFPS_ALIGN);
	for (; iter < end; iter += MPFPS_ALIGN) {
		MpFloatingPointerStructure *result = (MpFloatingPointerStructure *)iter;
		if (*(u32 *)result->mp_sig != MP_FLOATING_POINTER_SIGNATURE)
			continue;
		/* When found, check the length and checksum. */
		if (result->mp_length >= sizeof(MpFloatingPointerStructure) / 16 &&
		    !smp_memsum(result, sizeof(MpFloatingPointerStructure)))
			return result;
	}
	return NULL;
}


PRIVATE ATTR_FREETEXT MpFloatingPointerStructure *
NOTHROW(KCALL Mp_LocateFloatingPointerStructure)(void) {
	MpFloatingPointerStructure *result;
	uintptr_t base;
	/* NOTE: No need to identity-map these,  as they're all part of  the
	 *       first 1Gb of physical memory, which is fully mapped at this
	 *       point, both in 32-bit and 64-bit mode. */
	base   = (uintptr_t)(*(u16 const volatile *)(KERNEL_CORE_BASE + 0x40E));
	result = Mp_LocateFloatingPointerStructureInAddressRange(KERNEL_CORE_BASE + base, 1024);
	if (result)
		goto done;
	base   = (uintptr_t)(*(u16 const volatile *)(KERNEL_CORE_BASE + 0x413));
	result = Mp_LocateFloatingPointerStructureInAddressRange(KERNEL_CORE_BASE + base * 1024, 1024);
	if (result)
		goto done;
	result = Mp_LocateFloatingPointerStructureInAddressRange(KERNEL_CORE_BASE + 0x0f0000, 64 * 1024);
done:
	return result;
}


PUBLIC ATTR_PERCPU u8 thiscpu_x86_lapicid_ ASMNAME("thiscpu_x86_lapicid") = 0;
PUBLIC ATTR_PERCPU u8 thiscpu_x86_lapicversion_ ASMNAME("thiscpu_x86_lapicversion") = 0;
DATDEF unsigned int cpu_count_ ASMNAME("cpu_count");
DATDEF struct cpu *cpu_vector_[CONFIG_MAX_CPU_COUNT] ASMNAME("cpu_vector");

PUBLIC VIRT byte_t volatile *x86_lapicbase_ ASMNAME("x86_lapicbase") = NULL;

#ifndef CONFIG_NO_SMP
/* Commandline option to set the max number of CPUs which may be configured.
 * e.g.: `maxcpu=1' (forces the kernel to boot in single-core mode) */
INTERN u32 x86_config_max_cpu_count = CONFIG_MAX_CPU_COUNT;
DEFINE_VERY_EARLY_KERNEL_COMMANDLINE_OPTION(x86_config_max_cpu_count,
                                            KERNEL_COMMANDLINE_OPTION_TYPE_UINT32,
                                            "maxcpu");
#endif /* !CONFIG_NO_SMP */

INTERN ATTR_FREETEXT void
NOTHROW(KCALL x86_initialize_smp)(void) {
	MpFloatingPointerStructure *fps;
	MpConfigurationTable *table;
	/* TODO: Commandline option to override address of this structure */
	/* TODO: Commandline option to disable detection of this structure */
	fps = Mp_LocateFloatingPointerStructure();
	if unlikely(!fps) {
		printk(FREESTR(KERN_DEBUG "[smp] MpFloatingPointerStructure not found\n"));
		return;
	}
	printk(FREESTR(KERN_DEBUG "[smp] MpFloatingPointerStructure located at %p (v1.%" PRIu8 "; defcfg %" PRIu8 ")\n"),
	       ((uintptr_t)fps - KERNEL_CORE_BASE), fps->mp_specrev, fps->mp_defcfg);
	if (fps->mp_defcfg) {
		/* Default configuration. */
		x86_lapic_mpart.mp_mem.mc_start = physaddr2page(UINT32_C(0xfee00000));
		x86_lapic_mpart.mp_mem.mc_size  = 1;
		x86_lapic_mpart.mp_minaddr      = (pos_t)(0);
		x86_lapic_mpart.mp_maxaddr      = (pos_t)(PAGESIZE - 1);
		FORCPU(&bootcpu, thiscpu_x86_lapicid_)      = 0xff; /* Read later using the LAPIC */
		FORCPU(&bootcpu, thiscpu_x86_lapicversion_) = fps->mp_defcfg > 4 ? APICVER_INTEGRATED : APICVER_82489DX;
		return;
	}
	/* Check pointer location. */
	if (fps->mp_cfgtab >= 0x40000000)
		return;
	table = (MpConfigurationTable *)((uintptr_t)fps->mp_cfgtab + KERNEL_CORE_BASE);
	/* Check signature. */
	if (UNALIGNED_GET32((u32 const *)table->tab_sig) != ENCODE_INT32('P', 'C', 'M', 'P'))
		return;
	/* Check checksum. */
	if (smp_memsum(table, table->tab_length))
		return;
	/* Remember the LAPIC base address. */
	if (table->tab_lapicaddr & PAGEMASK) {
		x86_lapicbase_ = (byte_t *)(uintptr_t)(table->tab_lapicaddr & PAGEMASK);
		x86_lapic_mpart.mp_mem.mc_start = (physpage_t)physaddr2page(table->tab_lapicaddr);
		x86_lapic_mpart.mp_mem.mc_size  = 2;
		x86_lapic_mpart.mp_minaddr      = (pos_t)(0);
		x86_lapic_mpart.mp_maxaddr      = (pos_t)((2 * PAGESIZE) - 1);
	} else {
		x86_lapic_mpart.mp_mem.mc_start = (physpage_t)physaddr2page(table->tab_lapicaddr);
		x86_lapic_mpart.mp_mem.mc_size  = 1;
		x86_lapic_mpart.mp_minaddr      = (pos_t)(0);
		x86_lapic_mpart.mp_maxaddr      = (pos_t)(PAGESIZE - 1);
	}
	/* Process configuration entries. */
	{
		MpConfigurationEntry *entry, *end;
		u16 i, count;
		entry = (MpConfigurationEntry *)(table + 1);
		end   = (MpConfigurationEntry *)((uintptr_t)table + table->tab_length);
		count = table->tab_entryc;
		for (i = 0; i < count && entry < end; ++i) {
			size_t entsize = 8;
			switch (entry->mp_type) {

			case MPCFG_PROCESSOR:
				if (entry->mp_processor.p_cpuflag &
				    (MP_PROCESSOR_FENABLED | MP_PROCESSOR_FBOOTPROCESSOR)) {
					if (entry->mp_processor.p_cpuflag & MP_PROCESSOR_FBOOTPROCESSOR) {
						printk(FREESTR(KERN_INFO "[smp] Found boot processor with lapic id %#.2" PRIx8 "\n"),
						       entry->mp_processor.p_lapicid);
						FORCPU(&bootcpu, thiscpu_x86_lapicid_) = entry->mp_processor.p_lapicid;
					}
#ifndef CONFIG_NO_SMP
					else if unlikely(cpu_count_ >= x86_config_max_cpu_count) {
						printk(FREESTR(KERN_WARNING "[smp] Cannot configure additional "
						                            "processor with lapic id %#.2" PRIx8 "\n"),
						       entry->mp_processor.p_lapicid);
					} else {
						/* Remember this additional CPU's LAPIC id.
						 * NOTE: The CPU controller itself will then be allocated and initialized
						 *       later on. - For right now, we  only save its LAPIC id where  its
						 *       controller point will go later (s.a. `x86_initialize_apic()'). */
						printk(FREESTR(KERN_INFO "[smp] Found secondary processor #%u with lapic id %#.2" PRIx8 "\n"),
						       cpu_count_, entry->mp_processor.p_lapicid);
						/* This entry will later be replaced by a proper `struct cpu' structure! */
						cpu_vector_[cpu_count_] = (struct cpu *)(uintptr_t)(((u16)entry->mp_processor.p_lapicid) |
						                                                    ((u16)entry->mp_processor.p_lapicver << 8));
						++cpu_count_;
					}
#endif /* !CONFIG_NO_SMP */
				}
				entsize = 20;
				break;

			case MPCFG_IOAPIC:
				if (entry->mp_ioapic.io_flags & MP_IOAPIC_FENABLED) {
					printk(FREESTR(KERN_INFO "[smp] IoApic %#.2" PRIx8 ":%#.2" PRIx8 " found at %#.8" PRIx32 "\n"),
					       entry->mp_ioapic.io_apicid,
					       entry->mp_ioapic.io_apicver,
					       entry->mp_ioapic.io_apicaddr);
				}
				break;

			default:
				break;
			}
			entry = (MpConfigurationEntry *)((byte_t *)entry + entsize);
		}
	}
}


DECL_END

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_SCHED_SMP_C */
