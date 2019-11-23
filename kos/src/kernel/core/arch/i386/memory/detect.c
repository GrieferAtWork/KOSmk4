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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_MEMORY_DETECT_C
#define GUARD_KERNEL_CORE_ARCH_I386_MEMORY_DETECT_C 1
#define DISABLE_BRANCH_PROFILING 1 /* Don't profile this file */

#include <kernel/compiler.h>

#include <kernel/boot.h>
#include <kernel/memory.h>
#include <kernel/paging.h>
#include <kernel/printk.h>
#include <kernel/realmode.h>

#include <asm/cpu-flags.h>

#include <string.h>

DECL_BEGIN

INTDEF byte_t __kernel_start[];
INTDEF byte_t __kernel_free_start[];
INTDEF byte_t __kernel_end[];

#define V2P(x) ((uintptr_t)(x) - KERNEL_BASE)
PRIVATE ATTR_FREERODATA struct pmembank const default_memory_banks[] = {
	PMEMBANK_INIT(0x00000000, PMEMBANK_TYPE_ALLOCATED),  /* Keep the first page as allocated */
	PMEMBANK_INIT(0x00001000, PMEMBANK_TYPE_UNDEF),
	PMEMBANK_INIT(0x000a0000, PMEMBANK_TYPE_DEVICE),     /* VGA display buffer (Not defined by BIOS functions) */
	PMEMBANK_INIT(0x00100000, PMEMBANK_TYPE_UNDEF),
	PMEMBANK_INIT(V2P(__kernel_start), PMEMBANK_TYPE_KERNEL),
	PMEMBANK_INIT(V2P(__kernel_free_start), PMEMBANK_TYPE_KFREE),
	PMEMBANK_INIT(V2P(__kernel_end), PMEMBANK_TYPE_UNDEF),
	PMEMBANK_INIT(0x00000000, PMEMBANK_TYPE_UNDEF)
};
#undef V2P

INTDEF struct pmembank kernel_membanks_initial[];
PUBLIC ATTR_COLDDATA struct pmeminfo minfo = {
	 .mb_total = {
		/* TODO: These totals are incorrect! (they have to match the banks defined by `default_memory_banks') */
		/* [PMEMBANK_TYPE_UNDEF]     = */ (vm_phys_t)(0),
		/* [PMEMBANK_TYPE_RAM]       = */ (vm_phys_t)(0),
		/* [PMEMBANK_TYPE_PRESERVE]  = */ (vm_phys_t)(0),
		/* [PMEMBANK_TYPE_ALLOCATED] = */ (vm_phys_t)(0),
		/* [PMEMBANK_TYPE_KFREE]     = */ (vm_phys_t)(0),
		/* [PMEMBANK_TYPE_KERNEL]    = */ (vm_phys_t)(0),
		/* [PMEMBANK_TYPE_NVS]       = */ (vm_phys_t)(0),
		/* [PMEMBANK_TYPE_DEVICE]    = */ (vm_phys_t)(0),
		/* [PMEMBANK_TYPE_BADRAM]    = */ (vm_phys_t)(0),
	},
	 .mb_bankc = COMPILER_LENOF(default_memory_banks) - 1,
	 .mb_banks = kernel_membanks_initial
};

INTERN ATTR_FREETEXT void
NOTHROW(KCALL x86_initialize_default_memory_banks)(void) {
	memcpy(kernel_membanks_initial,
	       default_memory_banks,
	       sizeof(default_memory_banks));
}



struct smap_entry {
	u32 sm_addr_lo;
	u32 sm_addr_hi;
	u32 sm_size_lo;
	u32 sm_size_hi;
	u32 sm_type;
	u32 sm_acpi;
};
#define SMAP_BUFFER   ((struct smap_entry *)x86_realmode_buffer_addr)

INTDEF FREE u8 const memtype_bios_matrix[6];

PRIVATE ATTR_FREETEXT bool NOTHROW(KCALL detect_e820)(void) {
	struct smap_entry *entry;
	struct rmcpustate state;
	bool result = false;
	memset(&state, 0, sizeof(state));
	state.rmcs_ebx = 0; /* continue-id. */
	entry          = SMAP_BUFFER;
	do {
		state.rmcs_eax   = 0xe820;
		state.rmcs_ecx   = sizeof(struct smap_entry);
		state.rmcs_edx   = 0x534d4150;
		state.rmcs_edi   = x86_realmode_buffer_offset;
		state.rmcs_es    = x86_realmode_buffer_segment;
		state.rmcs_intno = 0x15;
		x86_realmode_interrupt(&state); /* Execute realmode interrupt. */
		if (state.rmcs_eflags & EFLAGS_CF)
			break; /* Unsupported. */
		if (state.rmcs_eax != 0x534d4150)
			break; /* Error. */
		if (state.rmcs_ecx > 20 && (entry->sm_acpi & 1) == 0)
			continue; /* Ignored. */
		if (entry->sm_type >= COMPILER_LENOF(memtype_bios_matrix))
			entry->sm_type = 0;
		if (memtype_bios_matrix[entry->sm_type] >= PMEMBANK_TYPE_COUNT)
			continue;
		minfo_addbank((vm_phys_t)entry->sm_addr_lo | (vm_phys_t)entry->sm_addr_hi << 32,
		              (vm_phys_t)entry->sm_size_lo | (vm_phys_t)entry->sm_size_hi << 32,
		              memtype_bios_matrix[entry->sm_type]);
		result = true;
	} while (state.rmcs_ebx);
	return result;
}

PRIVATE ATTR_FREETEXT bool NOTHROW(KCALL detect_e801)(void) {
	struct rmcpustate state;
	memset(&state, 0, sizeof(state));
	state.rmcs_eax   = 0xe801;
	state.rmcs_intno = 0x15;
	x86_realmode_interrupt(&state); /* Execute realmode interrupt. */
	if (state.rmcs_eflags & EFLAGS_CF)
		return false; /* Check for errors. */
	state.rmcs_eax &= 0xffff;
	state.rmcs_ecx &= 0xffff;
	state.rmcs_edx &= 0xffff;
	state.rmcs_ebx &= 0xffff;
	/* Fix broken BIOS return registers. */
	if (!state.rmcs_ecx)
		state.rmcs_ecx = state.rmcs_eax;
	if (!state.rmcs_edx)
		state.rmcs_edx = state.rmcs_ebx;
	if (state.rmcs_ecx > 0x3c00)
		return false; /* Don't trust a broken value... */
	minfo_addbank((vm_phys_t)0x00100000, (vm_phys_t)state.rmcs_ecx * 1024, PMEMBANK_TYPE_RAM);
	minfo_addbank((vm_phys_t)0x01000000, (vm_phys_t)state.rmcs_edx * 64 * 1024, PMEMBANK_TYPE_RAM);
	return true;
}

PRIVATE ATTR_FREETEXT bool NOTHROW(KCALL detect_da88)(void) {
	struct rmcpustate state;
	u32 count;
	memset(&state, 0, sizeof(state));
	state.rmcs_eax   = 0xda88;
	state.rmcs_intno = 0x15;
	x86_realmode_interrupt(&state); /* Execute realmode interrupt. */
	if (state.rmcs_eflags & EFLAGS_CF)
		return false;
	count = ((u32)(state.rmcs_ebx & 0xffff) << 8 | (u32)(state.rmcs_ecx & 0xff)) * 1024;
	minfo_addbank((vm_phys_t)0x00100000,
	              (vm_phys_t)count,
	              PMEMBANK_TYPE_RAM);
	return true;
}

PRIVATE ATTR_FREETEXT bool NOTHROW(KCALL detect_88)(void) {
	struct rmcpustate state;
	u32 count;
	memset(&state, 0, sizeof(state));
	state.rmcs_eax   = 0x88;
	state.rmcs_intno = 0x15;
	x86_realmode_interrupt(&state); /* Execute realmode interrupt. */
	if (state.rmcs_eflags & EFLAGS_CF)
		return false;
	count = (u32)(state.rmcs_eax & 0xffff) * 1024;
	minfo_addbank((vm_phys_t)0x00100000,
	              (vm_phys_t)count,
	              PMEMBANK_TYPE_RAM);
	return true;
}

PRIVATE ATTR_FREETEXT bool NOTHROW(KCALL detect_8a)(void) {
	struct rmcpustate state;
	u32 count;
	memset(&state, 0, sizeof(state));
	state.rmcs_eax   = 0x8a;
	state.rmcs_intno = 0x15;
	x86_realmode_interrupt(&state); /* Execute realmode interrupt. */
	if (state.rmcs_eflags & EFLAGS_CF)
		return false;
	count = ((u32)(state.rmcs_edx & 0xffff) |
	         (u32)(state.rmcs_eax & 0xffff) << 16) *
	        1024;
	minfo_addbank((vm_phys_t)0x00100000,
	              (vm_phys_t)count,
	              PMEMBANK_TYPE_RAM);
	return true;
}

struct c7_record {
	u16 r_size; /* 00h: Number of significant bytes of returned data (excluding this uint16_t). */
	u32 r_1x;   /* 02h: Amount of local memory between 1-16MB, in 1KB blocks. */
	u32 r_16x;  /* 06h: Amount of local memory between 16MB and 4GB, in 1KB blocks. */
	/* There are more fields here, but they don't matter to us... */
};
#define C7_RECORD ((struct c7_record *)x86_realmode_buffer_addr)

PRIVATE ATTR_FREETEXT bool NOTHROW(KCALL detect_c7)(void) {
	struct rmcpustate state;
	memset(&state, 0, sizeof(state));
	memset(C7_RECORD, 0, sizeof(*C7_RECORD));
	state.rmcs_eax   = 0xc7;
	state.rmcs_esi   = x86_realmode_buffer_offset;
	state.rmcs_ds    = x86_realmode_buffer_segment;
	state.rmcs_intno = 0x15;
	x86_realmode_interrupt(&state); /* Execute realmode interrupt. */
	if (state.rmcs_eflags & EFLAGS_CF)
		return false;
	if (C7_RECORD->r_1x > 0x3c00)
		return false; /* Don't trust a broken value... */
	minfo_addbank((vm_phys_t)0x00100000, (vm_phys_t)C7_RECORD->r_1x, PMEMBANK_TYPE_RAM);
	minfo_addbank((vm_phys_t)0x01000000, (vm_phys_t)C7_RECORD->r_16x, PMEMBANK_TYPE_RAM);
	return true;
}


PRIVATE ATTR_FREETEXT void
NOTHROW(KCALL log_beginmethod)(char const *name) {
	printk(FREESTR(KERN_INFO "[bios] Attempting memory detection method: %s\n"), name);
}

PRIVATE ATTR_FREETEXT void
NOTHROW(KCALL log_okmethod)(char const *name) {
	printk(FREESTR(KERN_INFO "[bios] Attempting memory detection method: %s (Ok)\n"), name);
}

PRIVATE ATTR_FREETEXT void
NOTHROW(KCALL log_badmethod)(char const *name) {
	printk(FREESTR(KERN_INFO "[bios] Attempting memory detection method: %s (Failed)\n"), name);
}


INTERN ATTR_FREETEXT void
NOTHROW(KCALL x86_initialize_memory_via_bios)(void) {
	x86_realmode_initialize();
#define TRY_METHOD(name, func)                                              \
	do {                                                                    \
		char const *_name = FREESTR(name);                                  \
		log_beginmethod(_name);                                             \
		if (func) {                                                         \
			log_okmethod(_name);                                            \
			if (minfo_usable_ram_pages() >= X86_BOOT_MINIMUM_AVAILABLE_RAM) \
				goto done;                                                  \
		} else {                                                            \
			log_badmethod(_name);                                           \
		}                                                                   \
	} __WHILE0
	TRY_METHOD("e820", detect_e820());
	TRY_METHOD("e801", detect_e801());
	TRY_METHOD("da88", detect_da88());
	TRY_METHOD("88", detect_88());
	TRY_METHOD("8a", detect_8a());
	TRY_METHOD("c7", detect_c7());
#undef TRY_METHOD
	printk(FREESTR(KERN_WARNING "[bios] Insufficient memory detected. Try to guess available RAM\n"));
#define RANGE(a, b) \
	minfo_addbank((vm_phys_t)(a), (vm_phys_t)(b - a) + 1, PMEMBANK_TYPE_RAM)
	/* Most likely that at least this memory exists... */
	RANGE(0x00000500, 0x0008ffff);
	/* TODO: Probe linear memory after the kernel core through trial-and-error */
	/* ... */
#undef RANGE
done:
	x86_realmode_finalize();
}

DECL_END

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_MEMORY_DETECT_C */
