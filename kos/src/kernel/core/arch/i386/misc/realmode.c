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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_MISC_REALMODE_C
#define GUARD_KERNEL_CORE_ARCH_I386_MISC_REALMODE_C 1
#define _KOS_SOURCE 1

#include <hybrid/compiler.h>

#include <hybrid/host.h>

#include <kernel/gdt.h>
#include <kernel/memory.h>
#include <kernel/realmode.h>
#include <kernel/printk.h>
#include <elf.h>

#include <hybrid/align.h>

#include <stddef.h>
#include <string.h>

#ifdef CONFIG_USE_LIBVM86_FOR_REALMODE
#include <libvm86/emulator.h>
#include <sys/io.h>
#endif /* CONFIG_USE_LIBVM86_FOR_REALMODE */


DECL_BEGIN

STATIC_ASSERT(offsetof(struct rmcpustate,rmcs_edi) == OFFSET_RMCPUSTATE_EDI);
STATIC_ASSERT(offsetof(struct rmcpustate,rmcs_esi) == OFFSET_RMCPUSTATE_ESI);
STATIC_ASSERT(offsetof(struct rmcpustate,rmcs_ebp) == OFFSET_RMCPUSTATE_EBP);
STATIC_ASSERT(offsetof(struct rmcpustate,rmcs_ebx) == OFFSET_RMCPUSTATE_EBX);
STATIC_ASSERT(offsetof(struct rmcpustate,rmcs_edx) == OFFSET_RMCPUSTATE_EDX);
STATIC_ASSERT(offsetof(struct rmcpustate,rmcs_ecx) == OFFSET_RMCPUSTATE_ECX);
STATIC_ASSERT(offsetof(struct rmcpustate,rmcs_eax) == OFFSET_RMCPUSTATE_EAX);
STATIC_ASSERT(offsetof(struct rmcpustate,rmcs_eflags) == OFFSET_RMCPUSTATE_EFLAGS);
STATIC_ASSERT(offsetof(struct rmcpustate,rmcs_gs) == OFFSET_RMCPUSTATE_GS);
STATIC_ASSERT(offsetof(struct rmcpustate,rmcs_fs) == OFFSET_RMCPUSTATE_FS);
STATIC_ASSERT(offsetof(struct rmcpustate,rmcs_es) == OFFSET_RMCPUSTATE_ES);
STATIC_ASSERT(offsetof(struct rmcpustate,rmcs_ds) == OFFSET_RMCPUSTATE_DS);
STATIC_ASSERT(offsetof(struct rmcpustate,rmcs_intno) == OFFSET_RMCPUSTATE_INTNO);
STATIC_ASSERT(sizeof(struct rmcpustate) == SIZEOF_RMCPUSTATE);

#ifdef CONFIG_USE_LIBVM86_FOR_REALMODE

//INTERN ATTR_FREEBSS vm_ppage_t x86_realmode_page;
INTERN ATTR_FREEBSS u16 x86_realmode_segment;
INTERN ATTR_FREEBSS byte_t *x86_realmode_buffer_addr;
INTERN uintptr_t x86_realmode_base = 0;

PRIVATE int LIBVM86_CC
vm86_handle_io(vm86_state_t *__restrict self,
               u16 port, unsigned int action,
               void *data) {
	int result = VM86_SUCCESS;
	(void)self;
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
		outb((port_t)port, *(uint8_t *)data);
		break;
	case VM86_HANDLE_IO_OUTW:
		outw((port_t)port, *(uint16_t *)data);
		break;
	case VM86_HANDLE_IO_OUTL:
		outl((port_t)port, *(uint32_t *)data);
		break;
	default:
		result = VM86_BADPORT;
		break;
	}
	return result;
}


INTERN FREE void
NOTHROW(FCALL x86_realmode_interrupt)(struct rmcpustate *__restrict state) {
	vm86_state_t st;
	memset(&st, 0, sizeof(st));
	st.vr_io = &vm86_handle_io;
	st.vr_regs.vr_eax    = state->rmcs_eax;
	st.vr_regs.vr_ecx    = state->rmcs_ecx;
	st.vr_regs.vr_edx    = state->rmcs_edx;
	st.vr_regs.vr_ebx    = state->rmcs_ebx;
	st.vr_regs.vr_esp    = x86_realmode_base + 256;
	st.vr_regs.vr_ebp    = state->rmcs_ebp;
	st.vr_regs.vr_esi    = state->rmcs_esi;
	st.vr_regs.vr_edi    = state->rmcs_edi;
	st.vr_regs.vr_eip    = 0xffff;
	st.vr_regs.vr_eflags = state->rmcs_eflags;
	st.vr_regs.vr_es     = state->rmcs_es;
	st.vr_regs.vr_cs     = 0xffff;
	st.vr_regs.vr_ss     = x86_realmode_segment;
	st.vr_regs.vr_ds     = state->rmcs_ds;
	st.vr_regs.vr_fs     = state->rmcs_fs;
	st.vr_regs.vr_gs     = state->rmcs_gs;
	/* Generate a software interrupt */
	vm86_sw_intr(&st, state->rmcs_intno);
	/* Execute VM86 code. */
	vm86_exec(&st); /* 0x0000f85c */
	state->rmcs_eax    = st.vr_regs.vr_eax;
	state->rmcs_ecx    = st.vr_regs.vr_ecx;
	state->rmcs_edx    = st.vr_regs.vr_edx;
	state->rmcs_ebx    = st.vr_regs.vr_ebx;
	state->rmcs_ebp    = st.vr_regs.vr_ebp;
	state->rmcs_esi    = st.vr_regs.vr_esi;
	state->rmcs_edi    = st.vr_regs.vr_edi;
	state->rmcs_eflags = st.vr_regs.vr_eflags;
	state->rmcs_es     = st.vr_regs.vr_es;
	state->rmcs_ds     = st.vr_regs.vr_ds;
	state->rmcs_fs     = st.vr_regs.vr_fs;
	state->rmcs_gs     = st.vr_regs.vr_gs;
}

INTERN ATTR_FREETEXT void
NOTHROW(KCALL x86_realmode_initialize)(void) {
#ifndef __x86_64__
#if 1
	if (X86_PAGEDIR_USES_P32()) {
		memcpyl(pagedir_kernel.pd_p32.p_e2,
		        pagedir_kernel.pd_p32.p_e2 + (1024 - 256),
		        256);
	} else {
		memcpyq(PAE_PDIR_E2_IDENTITY[0], PAE_PDIR_E2_IDENTITY[3], 512);
	}
#else
	memcpyl(pagedir_kernel.p_e2,
	        pagedir_kernel.p_e2 + (1024 - 256),
	        256);
#endif
#endif /* !__x86_64__ */
	pagedir_syncall();
#if 0
	{
		void  *bios_base = 0;
		size_t bios_size = 0x00100000;
		printk(KERN_RAW "%%{artifact:bios.bin:%Iu}", bios_size);
		outsb((port_t)0x3f8, bios_base, bios_size);
	}
#endif
	x86_realmode_base    = (uintptr_t)0x7c00;
	x86_realmode_segment = (x86_realmode_base & 0xf0000) >> 4;
	x86_realmode_buffer_addr = ((byte_t *)x86_realmode_base + 256); /* NOTE: 256 == STACKSIZE (s.a. `realmode32.S') */
}

INTERN ATTR_FREETEXT void
NOTHROW(KCALL x86_realmode_finalize)(void) {
#ifndef __x86_64__
#if 1
	if (X86_PAGEDIR_USES_P32()) {
		memsetl(pagedir_kernel.pd_p32.p_e2, 0, 256);
	} else {
		memsetq(PAE_PDIR_E2_IDENTITY[0], 0, 512);
	}
#else
	memsetl(pagedir_kernel.p_e2, 0, 256);
#endif
#endif /* !__x86_64__ */
	pagedir_syncall();
}

#else /* CONFIG_USE_LIBVM86_FOR_REALMODE */

//INTERN ATTR_FREEBSS vm_ppage_t x86_realmode_page;
INTERN ATTR_FREEBSS u16 x86_realmode_segment;
INTERN ATTR_FREEBSS byte_t *x86_realmode_buffer_addr;
INTDEF uintptr_t x86_realmode_base;

INTDEF byte_t x86_realmode_interrupt_16_entry[];
INTDEF byte_t x86_realmode_interrupt_16_size[];

INTERN ATTR_FREEDATA struct segment x86_realmode_gdt[SEGMENT_COUNT] = {
	[SEGMENT_INDEX(0x0000)] = SEGMENT_DESCRIPTOR_INIT(0, 0, 0, 0, 0, 0, 0, 0, 0, 0), /* NULL segment */
	[SEGMENT_INDEX(0x0008)] = SEGMENT_DESCRIPTOR_INIT(0, 0xfffff, SEGMENT_DESCRIPTOR_TYPE_CODE_EXRD, 1, 0, 1, 0, 0, 1, 1), /* Kernel code segment */
	[SEGMENT_INDEX(0x0010)] = SEGMENT_DESCRIPTOR_INIT(0, 0xfffff, SEGMENT_DESCRIPTOR_TYPE_DATA_RDWR, 1, 0, 1, 0, 0, 1, 1), /* Kernel data segment */
	[SEGMENT_INDEX(0x0018)] = SEGMENT_DESCRIPTOR_INIT(0, 0xfffff, SEGMENT_DESCRIPTOR_TYPE_CODE_EXRD, 1, 0, 1, 0, 0, 0, 1), /* Kernel code segment (realmode) */
	[SEGMENT_INDEX(0x0020)] = SEGMENT_DESCRIPTOR_INIT(0, 0xfffff, SEGMENT_DESCRIPTOR_TYPE_DATA_RDWR, 1, 0, 1, 0, 0, 0, 1), /* Kernel data segment (realmode) */
};


INTERN ATTR_FREETEXT void
NOTHROW(KCALL x86_realmode_initialize)(void) {
#ifndef __x86_64__
	if (X86_PAGEDIR_USES_P32()) {
		memcpyl(pagedir_kernel.pd_p32.p_e2,
		        pagedir_kernel.pd_p32.p_e2 + (1024 - 256),
		        256);
	} else {
		memcpyq(PAE_PDIR_E2_IDENTITY[0], PAE_PDIR_E2_IDENTITY[3], 512);
	}
#endif /* !__x86_64__ */
	pagedir_syncall();
	x86_realmode_base    = (uintptr_t)0x7c00;
	x86_realmode_segment = (x86_realmode_base & 0xf0000) >> 4;
	/* TODO: Set the bases of `x86_realmode_gdt' to `x86_realmode_segment' */
	memcpy((byte_t *)x86_realmode_base,
	       (byte_t *)x86_realmode_interrupt_16_entry,
	       (uintptr_t)x86_realmode_interrupt_16_size);
	x86_realmode_buffer_addr = ((byte_t *)x86_realmode_base +
	                            (uintptr_t)x86_realmode_interrupt_16_size +
	                            256); /* NOTE: 256 == STACKSIZE (s.a. `realmode32.S') */
}

INTERN ATTR_FREETEXT void
NOTHROW(KCALL x86_realmode_finalize)(void) {
#ifndef __x86_64__
	if (X86_PAGEDIR_USES_P32()) {
		memsetl(pagedir_kernel.pd_p32.p_e2, 0, 256);
	} else {
		memsetq(PAE_PDIR_E2_IDENTITY[0], 0, 512);
	}
#endif /* !__x86_64__ */
	pagedir_syncall();
#if 0
	page_free(x86_realmode_page, CEILDIV((size_t)x86_realmode_interrupt_16_size, PAGESIZE));
#endif
}

#endif /* !CONFIG_USE_LIBVM86_FOR_REALMODE */

DECL_END

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_MISC_REALMODE_C */
