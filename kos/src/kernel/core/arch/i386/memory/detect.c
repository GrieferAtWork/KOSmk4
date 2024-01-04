/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_CORE_ARCH_I386_MEMORY_DETECT_C
#define GUARD_KERNEL_CORE_ARCH_I386_MEMORY_DETECT_C 1
#define _KOS_SOURCE 1
#define DISABLE_BRANCH_PROFILING /* Don't profile this file */

#include <kernel/compiler.h>

#include <kernel/boot.h>
#include <kernel/memory.h>
#include <kernel/paging.h>
#include <kernel/printk.h>

#include <asm/cpu-flags.h>
#include <sys/io.h>

#include <stddef.h>
#include <string.h>

#include <libvm86/emulator.h>

DECL_BEGIN

INTDEF byte_t __kernel_start[];
INTDEF byte_t __kernel_free_start[];
INTDEF byte_t __kernel_end[];

#define V2P(x) ((uintptr_t)(x) - KERNEL_CORE_BASE)
PRIVATE ATTR_FREERODATA struct pmembank const default_memory_banks[] = {
	PMEMBANK_INIT(0x00000000, PMEMBANK_TYPE_ALLOCATED),  /* Keep the first page as allocated */
	PMEMBANK_INIT(0x00001000, PMEMBANK_TYPE_RAM),        /* Available as RAM on any PC-derivative */
	PMEMBANK_INIT(0x00080000, PMEMBANK_TYPE_UNDEF),      /* EBDA (max-sized) */
	PMEMBANK_INIT(0x000a0000, PMEMBANK_TYPE_DEVICE),     /* VGA display buffer (Not defined by BIOS functions) */
	/*PMEMBANK_INIT(0x00100000, PMEMBANK_TYPE_UNDEF),*/
	PMEMBANK_INIT(V2P(__kernel_start), PMEMBANK_TYPE_KERNEL),
	PMEMBANK_INIT(V2P(__kernel_free_start), PMEMBANK_TYPE_KFREE),
	PMEMBANK_INIT(V2P(__kernel_end), PMEMBANK_TYPE_UNDEF),
	PMEMBANK_INIT(0x00000000, PMEMBANK_TYPE_UNDEF)
};
#undef V2P

INTDEF struct pmembank kernel_membanks_initial[];
PUBLIC ATTR_COLDDATA struct pmeminfo minfo = {
	 .mb_bankc = lengthof(default_memory_banks) - 1,
	 .mb_banks = kernel_membanks_initial
};

INTERN ATTR_FREETEXT void
NOTHROW(KCALL x86_initialize_default_memory_banks)(void) {
	memcpy(kernel_membanks_initial,
	       default_memory_banks,
	       sizeof(default_memory_banks));
}

/* Base address where the virtual memory mapping for vm86 begins. */
#define VM86_VIRT_OFFSET    KERNEL_CORE_BASE
#define VM86_BASE           0x7c00
#define VM86_BUFFER         (VM86_VIRT_OFFSET + VM86_BASE)
#define VM86_BUFFER_OFFSET  (VM86_BASE & 0xffff)
#define VM86_BUFFER_SEG     ((VM86_BASE & 0xf0000) >> 4)


PRIVATE ATTR_FREETEXT WUNUSED NONNULL((1)) void *LIBVM86_TRANSLATE_CC
vm86_translate(vm86_state_t *__restrict UNUSED(self), void *ptr) {
	return (void *)((uintptr_t)ptr + VM86_VIRT_OFFSET);
}

PRIVATE ATTR_FREETEXT NONNULL((1)) int LIBVM86_CC
vm86_io(vm86_state_t *__restrict UNUSED(self),
        u16 port, unsigned int action,
        void *data) {
	int result = VM86_SUCCESS;
	switch (action) {
	case VM86_HANDLE_IO_INB:
		*(uint8_t *)data = inb((port_t)port);
		break;
	case VM86_HANDLE_IO_INW:
		*(uint16_t *)data = inw((port_t)port);
		break;
	case VM86_HANDLE_IO_INL:
		*(uint32_t *)data = inl((port_t)port);
		break;
	case VM86_HANDLE_IO_OUTB:
		outb((port_t)port, *(uint8_t const *)data);
		break;
	case VM86_HANDLE_IO_OUTW:
		outw((port_t)port, *(uint16_t const *)data);
		break;
	case VM86_HANDLE_IO_OUTL:
		outl((port_t)port, *(uint32_t const *)data);
		break;
	default:
		result = VM86_BADPORT;
		break;
	}
	return result;
}

PRIVATE ATTR_FREETEXT NONNULL((1)) bool
NOTHROW(KCALL interrupt)(vm86_state_t *__restrict self, u8 intno) {
	int error;
	self->vr_trans = &vm86_translate;
	self->vr_io    = &vm86_io;
	self->vr_intr  = NULL;
	self->vr_regs.vr_esp = (VM86_BASE + 256) & 0xffff;
	self->vr_regs.vr_ss  = ((VM86_BASE + 256) & 0xf0000) >> 4;
	self->vr_regs.vr_eip = 0xffff;
	self->vr_regs.vr_cs  = 0xffff;
	/* Generate a software interrupt */
	vm86_intr(self, intno);
	/* Execute VM86 code. */
	error = vm86_exec(self);
	return error >= 0;
}


struct smap_entry {
	u32 sm_addr_lo;
	u32 sm_addr_hi;
	u32 sm_size_lo;
	u32 sm_size_hi;
	u32 sm_type;
	u32 sm_acpi;
};

#define SMAP_BUFFER ((struct smap_entry *)VM86_BUFFER)
INTDEF FREE u8 const memtype_bios_matrix[6];

PRIVATE ATTR_FREETEXT bool NOTHROW(KCALL detect_e820)(void) {
	struct smap_entry *entry;
	vm86_state_t state;
	bool result = false;
	bzero(&state.vr_regs, sizeof(state.vr_regs));
/*	state.vr_regs.vr_ebx = 0; * continue-id. */
	entry                = SMAP_BUFFER;
	do {
		bzero(entry, sizeof(*entry));
		state.vr_regs.vr_eax = 0xe820;
		state.vr_regs.vr_ecx = sizeof(struct smap_entry);
		state.vr_regs.vr_edx = 0x534d4150;
		state.vr_regs.vr_edi = VM86_BUFFER_OFFSET;
		state.vr_regs.vr_es  = VM86_BUFFER_SEG;
		/* Execute realmode interrupt. */
		if (!interrupt(&state, 0x15))
			break;
		if (state.vr_regs.vr_eflags & EFLAGS_CF)
			break; /* Unsupported. */
		if (state.vr_regs.vr_eax != 0x534d4150)
			break; /* Error. */
		if (state.vr_regs.vr_ecx > 20 && (entry->sm_acpi & 1) == 0)
			continue; /* Ignored. */
		if (entry->sm_type >= lengthof(memtype_bios_matrix))
			entry->sm_type = 0;
		if (memtype_bios_matrix[entry->sm_type] >= PMEMBANK_TYPE_COUNT)
			continue;
		minfo_addbank((physaddr_t)entry->sm_addr_lo | (physaddr_t)entry->sm_addr_hi << 32,
		              (physaddr_t)entry->sm_size_lo | (physaddr_t)entry->sm_size_hi << 32,
		              memtype_bios_matrix[entry->sm_type]);
		result = true;
	} while (state.vr_regs.vr_ebx);
	return result;
}

PRIVATE ATTR_FREETEXT bool NOTHROW(KCALL detect_e801)(void) {
	vm86_state_t state;
	bzero(&state.vr_regs, sizeof(state.vr_regs));
	state.vr_regs.vr_eax = 0xe801;
	/* Execute realmode interrupt. */
	if (!interrupt(&state, 0x15))
		return false;
	if (state.vr_regs.vr_eflags & EFLAGS_CF)
		return false; /* Check for errors. */
	state.vr_regs.vr_eax &= 0xffff;
	state.vr_regs.vr_ecx &= 0xffff;
	state.vr_regs.vr_edx &= 0xffff;
	state.vr_regs.vr_ebx &= 0xffff;
	/* Fix broken BIOS return registers. */
	if (!state.vr_regs.vr_ecx)
		state.vr_regs.vr_ecx = state.vr_regs.vr_eax;
	if (!state.vr_regs.vr_edx)
		state.vr_regs.vr_edx = state.vr_regs.vr_ebx;
	if (state.vr_regs.vr_ecx > 0x3c00)
		return false; /* Don't trust a broken value... */
	minfo_addbank((physaddr_t)0x00100000, (physaddr_t)state.vr_regs.vr_ecx * 1024, PMEMBANK_TYPE_RAM);
	minfo_addbank((physaddr_t)0x01000000, (physaddr_t)state.vr_regs.vr_edx * 64 * 1024, PMEMBANK_TYPE_RAM);
	return true;
}

PRIVATE ATTR_FREETEXT bool NOTHROW(KCALL detect_da88)(void) {
	vm86_state_t state;
	u32 count;
	bzero(&state.vr_regs, sizeof(state.vr_regs));
	state.vr_regs.vr_eax = 0xda88;
	/* Execute realmode interrupt. */
	if (!interrupt(&state, 0x15))
		return false;
	if (state.vr_regs.vr_eflags & EFLAGS_CF)
		return false;
	count = ((u32)(state.vr_regs.vr_ebx & 0xffff) << 8 | (u32)(state.vr_regs.vr_ecx & 0xff)) * 1024;
	minfo_addbank((physaddr_t)0x00100000,
	              (physaddr_t)count,
	              PMEMBANK_TYPE_RAM);
	return true;
}

PRIVATE ATTR_FREETEXT bool NOTHROW(KCALL detect_88)(void) {
	vm86_state_t state;
	u32 count;
	bzero(&state.vr_regs, sizeof(state.vr_regs));
	state.vr_regs.vr_eax = 0x88;
	/* Execute realmode interrupt. */
	if (!interrupt(&state, 0x15))
		return false;
	if (state.vr_regs.vr_eflags & EFLAGS_CF)
		return false;
	count = (u32)(state.vr_regs.vr_eax & 0xffff) * 1024;
	minfo_addbank((physaddr_t)0x00100000,
	              (physaddr_t)count,
	              PMEMBANK_TYPE_RAM);
	return true;
}

PRIVATE ATTR_FREETEXT bool NOTHROW(KCALL detect_8a)(void) {
	vm86_state_t state;
	u32 count;
	bzero(&state.vr_regs, sizeof(state.vr_regs));
	state.vr_regs.vr_eax = 0x8a;
	/* Execute realmode interrupt. */
	if (!interrupt(&state, 0x15))
		return false;
	if (state.vr_regs.vr_eflags & EFLAGS_CF)
		return false;
	count = ((u32)(state.vr_regs.vr_edx & 0xffff) |
	         (u32)(state.vr_regs.vr_eax & 0xffff) << 16) *
	        1024;
	minfo_addbank((physaddr_t)0x00100000,
	              (physaddr_t)count,
	              PMEMBANK_TYPE_RAM);
	return true;
}

struct c7_record {
	u16 r_size; /* 00h: Number of significant bytes of returned data (excluding this uint16_t). */
	u32 r_1x;   /* 02h: Amount of local memory between 1-16MB, in 1KB blocks. */
	u32 r_16x;  /* 06h: Amount of local memory between 16MB and 4GB, in 1KB blocks. */
	/* There are more fields here, but they don't matter to us... */
};
#define C7_RECORD ((struct c7_record *)VM86_BUFFER)

PRIVATE ATTR_FREETEXT bool NOTHROW(KCALL detect_c7)(void) {
	vm86_state_t state;
	bzero(&state.vr_regs, sizeof(state.vr_regs));
	bzero(C7_RECORD, sizeof(*C7_RECORD));
	state.vr_regs.vr_eax = 0xc7;
	state.vr_regs.vr_esi = VM86_BUFFER_OFFSET;
	state.vr_regs.vr_ds  = VM86_BUFFER_SEG;
	/* Execute realmode interrupt. */
	if (!interrupt(&state, 0x15))
		return false;
	if (state.vr_regs.vr_eflags & EFLAGS_CF)
		return false;
	if (C7_RECORD->r_1x > 0x3c00)
		return false; /* Don't trust a broken value... */
	minfo_addbank((physaddr_t)0x00100000, (physaddr_t)C7_RECORD->r_1x, PMEMBANK_TYPE_RAM);
	minfo_addbank((physaddr_t)0x01000000, (physaddr_t)C7_RECORD->r_16x, PMEMBANK_TYPE_RAM);
	return true;
}


PRIVATE ATTR_FREETEXT NONNULL((1)) void
NOTHROW(KCALL log_beginmethod)(char const *name) {
	printk(FREESTR(KERN_INFO "[bios] Attempting memory detection method: %s\n"), name);
}

PRIVATE ATTR_FREETEXT NONNULL((1)) void
NOTHROW(KCALL log_okmethod)(char const *name) {
	printk(FREESTR(KERN_INFO "[bios] Attempting memory detection method: %s (ok)\n"), name);
}

PRIVATE ATTR_FREETEXT NONNULL((1)) void
NOTHROW(KCALL log_badmethod)(char const *name) {
	printk(FREESTR(KERN_INFO "[bios] Attempting memory detection method: %s (failed)\n"), name);
}


INTERN ATTR_FREETEXT void
NOTHROW(KCALL x86_initialize_memory_via_bios)(void) {
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
	}	__WHILE0
	TRY_METHOD("e820", detect_e820());
	TRY_METHOD("e801", detect_e801());
	TRY_METHOD("da88", detect_da88());
	TRY_METHOD("88", detect_88());
	TRY_METHOD("8a", detect_8a());
	TRY_METHOD("c7", detect_c7());
#undef TRY_METHOD
	printk(FREESTR(KERN_WARNING "[bios] Insufficient memory detected. Try to guess available RAM\n"));
#define RANGE(min, max) \
	minfo_addbank((physaddr_t)(min), (physaddr_t)((max) - (min)) + 1, PMEMBANK_TYPE_RAM)
	/* Most likely that at least this memory exists... */
	RANGE(0x00000500, 0x0008ffff);
	/* TODO: Probe linear memory after the kernel core through trial-and-error */
	/* ... */
#undef RANGE
done:
	;
}

DECL_END

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_MEMORY_DETECT_C */
