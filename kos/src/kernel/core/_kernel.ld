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
#ifndef GUARD_KERNEL_CORE__KERNEL_LD
#define GUARD_KERNEL_CORE__KERNEL_LD 1
#define __LINKER__ 1
#define _KOS_SOURCE 1
#define _KOS_KERNEL_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/paging.h>
#include <kernel/selftest.h>
#include <sched/task.h> /* CONFIG_HAVE_KERNEL_STACK_GUARD */

#include <hybrid/align.h>
#include <hybrid/host.h>

#include <asm/cacheline.h>
#include <asm/pageid.h>

#if defined(__i386__) || defined(__x86_64__)
#include <kernel/x86/gdt.h>
#include <kernel/x86/idt.h>
#include <kernel/x86/multiboot.h>
#include <kernel/x86/syscall-tables.h>
#include <sched/x86/tss.h>
#include <kos/kernel/gdt.h>
#include <kos/kernel/segment.h>

#include "arch/i386/boot/start.h" /* CONFIG_NO_KERNEL_X86_BOOT0 */
#endif /* __i386__ || __x86_64__ */

#undef likely
#undef unlikely

#define addr2pageptr_p(ptr) (((ptr) - KERNEL_CORE_BASE) >> PAGESHIFT)

#define IP_ALIGN(x)  . = ALIGN(x)
#define SECTION(name) \
	name BLOCK(1) : AT(ADDR(name) - KERNEL_CORE_BASE)

#define PEROBJECT_SECTION_EX(section_name, name, base_offset, sections) \
	PROVIDE_HIDDEN(name##_start = ABSOLUTE(.));                         \
	. = ABSOLUTE(base_offset);                                          \
	section_name base_offset : AT(name##_start - KERNEL_CORE_BASE)      \
		sections                                                        \
	PROVIDE_HIDDEN(name##_size = ABSOLUTE(. - base_offset));            \
	. = ABSOLUTE(name##_start + name##_size);                           \
	PROVIDE_HIDDEN(name##_end = ABSOLUTE(.));
#define PEROBJECT_SECTION(section_name, name, sections) \
	PEROBJECT_SECTION_EX(section_name, name, 0, sections)


#ifdef CONFIG_NO_SMP
#define BOOTCPU_SYMBOL(thiscpu_name) thiscpu_name
#else /* CONFIG_NO_SMP */
#define BOOTCPU_SYMBOL(thiscpu_name) bootcpu + thiscpu_name
#endif /* !CONFIG_NO_SMP */


ENTRY(_start)
SECTIONS {

#if defined(__i386__) || defined(__x86_64__)
	. = KERNEL_CORE_BASE + 0x100000;
#else /* __i386__ || __x86_64__ */
	. = KERNEL_CORE_BASE;
#endif /* !__i386__ && !__x86_64__ */

	PROVIDE_HIDDEN(__kernel_start = ABSOLUTE(.));

#if defined(__i386__) || defined(__x86_64__)
#ifndef CONFIG_NO_KERNEL_X86_BOOT0
	SECTION(.x86.boot0) {
		KEEP(*(.x86.boot0))
	}
	. = KERNEL_CORE_BASE + 0x100200;
#endif /* !CONFIG_NO_KERNEL_X86_BOOT0 */

	/* Boot header */
	SECTION(.x86.mb) {
		KEEP(*(.x86.mb))
		PROVIDE_HIDDEN(__386_kernel_mb2_start = ABSOLUTE(.));
		KEEP(*(.x86.mb2))
		PROVIDE_HIDDEN(__386_kernel_mb2_tag_start = ABSOLUTE(.));
		KEEP(*(.x86.mb2.tag))
		KEEP(*(.x86.mb2.tag.end))
		PROVIDE_HIDDEN(__386_kernel_mb2_end = ABSOLUTE(.));
		PROVIDE_HIDDEN(__386_kernel_mb2_size = ABSOLUTE(ABSOLUTE(__386_kernel_mb2_end) - ABSOLUTE(__386_kernel_mb2_start)));
#ifdef __x86_64__
		PROVIDE_HIDDEN(__x86_kernel_mb2_hdrlen_and_chksum = ABSOLUTE(__386_kernel_mb2_size) | (ABSOLUTE(0 - (MB2_HEADER_MAGIC + MB2_ARCHITECTURE_I386 + __386_kernel_mb2_size)) << 32));
#else /* __x86_64__ */
		PROVIDE_HIDDEN(__386_kernel_mb2_hdrlen = ABSOLUTE(__386_kernel_mb2_size));
		PROVIDE_HIDDEN(__386_kernel_mb2_chksum = ABSOLUTE(0 - (MB2_HEADER_MAGIC + MB2_ARCHITECTURE_I386 + __386_kernel_mb2_size)));
#endif /* !__x86_64__ */
	}
#endif /* __i386__ || __x86_64__ */

	IP_ALIGN(PAGESIZE);
	PROVIDE_HIDDEN(__kernel_sect_text_start = ABSOLUTE(.));
	PROVIDE_HIDDEN(__kernel_text_start = ABSOLUTE(.));
	PROVIDE_HIDDEN(__kernel_text_startpage_p = addr2pageptr_p(ABSOLUTE(.)));
	SECTION(.text) {
		*(.text.hot .text.likely .text.hot.*)
		*(.text .text._ZN*)
		*(.text.crt.*)
		*(.text.kernel.*)
		*(.text.unlikely*)     /* Should be necessary, but prevents problems... */
#if defined(__i386__) || defined(__x86_64__)
		*(.text.x86.syscall.*) /* C-level implementations of system calls. */
#ifdef __x86_64__
		*(.text.x86.syscall32.*) /* C-level implementations of system calls (for compatibility mode). */
#endif /* __x86_64__ */
		*(.text.x86.cisr.*)
		/* Must be KEEP, or else  these get deleted by --gc-sections,  since
		 * they're  only referenced by this linker script, and not by actual
		 * kernel code (we use the linker script to pre-calculate the values
		 * to-be written to the IDT vector) */
		KEEP(*(.text.x86.asmirq.*))
#ifdef __x86_64__
		*(.text.x86.asm64_syscall.*)
#endif /* __x86_64__ */
		*(.text.x86.asm32_syscall_int80.*)
		*(.text.x86.asm32_syscall_sysenter.*)
#ifdef __x86_64__
		*(.text.x86.asm32_syscall_sysrun32.*)
#endif /* __x86_64__ */
		*(.text.x86.*)
#endif /* __i386__ || __x86_64__ */
//		*(.text.local.*)
		*(.text.cold .text.unlikely .text.cold.*)
	}

	IP_ALIGN(PAGESIZE);
	PROVIDE_HIDDEN(__kernel_sect_text_size = ABSOLUTE(ABSOLUTE(.) - ABSOLUTE(__kernel_sect_text_start)));
	PROVIDE_HIDDEN(__kernel_text_end = ABSOLUTE(.));
	PROVIDE_HIDDEN(__kernel_text_size = ABSOLUTE(ABSOLUTE(__kernel_text_end) - ABSOLUTE(__kernel_text_start)));
	PROVIDE_HIDDEN(__kernel_text_numpages = ABSOLUTE(__kernel_text_size) / PAGESIZE);

	PROVIDE_HIDDEN(__kernel_sect_rodata_start = ABSOLUTE(.));
	PROVIDE_HIDDEN(__kernel_rodata_start = ABSOLUTE(.));
	PROVIDE_HIDDEN(__kernel_rodata_startpage_p = addr2pageptr_p(ABSOLUTE(.)));
	SECTION(.rodata) {
		*(.rodata.hot .rodata.likely .rodata.hot.*)
#if defined(__i386__) || defined(__x86_64__)
		*(.rodata.x86.*)
#endif /* __i386__ || __x86_64__ */
		KEEP(*(.rodata.execabi_system_rtld))
		PROVIDE_HIDDEN(execabi_system_rtld_startpage_p = addr2pageptr_p(ABSOLUTE(execabi_system_rtld)));
		PROVIDE_HIDDEN(execabi_system_rtld_numpages    = ABSOLUTE(execabi_system_rtld_size) / PAGESIZE);
#ifdef __x86_64__
		/* Compatibility-mode libdl.so binary (32-bit application) */
		KEEP(*(.rodata.compat_execabi_system_rtld))
		PROVIDE_HIDDEN(compat_execabi_system_rtld_startpage_p = addr2pageptr_p(ABSOLUTE(compat_execabi_system_rtld)));
		PROVIDE_HIDDEN(compat_execabi_system_rtld_numpages    = ABSOLUTE(compat_execabi_system_rtld_size) / PAGESIZE);
#endif /* __x86_64__ */
		*(.rodata .rodata.kernel_symtab .rodata.cst*)
		*(.rodata.str* .rodata.*.str* .rodata.kernel_strtab)

#ifndef CONFIG_NO_KERNEL_DEBUGGER
		IP_ALIGN(__SIZEOF_POINTER__);
		PROVIDE_HIDDEN(__kernel_sect_dbg_hooks_start = ABSOLUTE(.));
		KEEP(*(.dbg.hooks))
		PROVIDE_HIDDEN(__kernel_sect_dbg_hooks_size = ABSOLUTE(. - __kernel_sect_dbg_hooks_start));
#endif /* !CONFIG_NO_KERNEL_DEBUGGER */

#define DEFINE_VECTOR(name,section)                            \
		IP_ALIGN(__SIZEOF_POINTER__);                          \
		PROVIDE_HIDDEN(__kernel_##name##_start = ABSOLUTE(.)); \
		KEEP(*(section))                                       \
		PROVIDE_HIDDEN(__kernel_##name##_end = ABSOLUTE(.));

		DEFINE_VECTOR(idle_job, .rodata.callback.idle_job)
		DEFINE_VECTOR(pertask_relocations, .rodata.pertask.relocations)
		DEFINE_VECTOR(pertask_fini, .rodata.callback.pertask.fini)
		DEFINE_VECTOR(permman_init, .rodata.callback.permman.init)
		DEFINE_VECTOR(permman_fini, .rodata.callback.permman.fini)
		DEFINE_VECTOR(permman_clone, .rodata.callback.permman.clone)
		DEFINE_VECTOR(permman_onexec, .rodata.callback.permman.onexec)
		DEFINE_VECTOR(validatable_heaps, .rodata.heaps.validatable)
#undef DEFINE_VECTOR

		*(.rodata.local.* .rodata.cold .rodata.unlikely .rodata.cold.*)
	}

	PROVIDE_HIDDEN(__kernel_sect_rodata_size = ABSOLUTE(ABSOLUTE(.) - ABSOLUTE(__kernel_sect_rodata_start)));

	IP_ALIGN(__SIZEOF_POINTER__);
	PROVIDE_HIDDEN(__kernel_sect_gcc_except_table_start = ABSOLUTE(.));
	SECTION(.gcc_except_table) {
		KEEP(*(.gcc_except_table .gcc_except_table.*))
	}
	PROVIDE_HIDDEN(__kernel_sect_gcc_except_table_size = ABSOLUTE(ABSOLUTE(.) - ABSOLUTE(__kernel_sect_gcc_except_table_start)));

	IP_ALIGN(__SIZEOF_POINTER__);
	PROVIDE_HIDDEN(__kernel_sect_eh_frame_start = ABSOLUTE(.));
	SECTION(.eh_frame) {
		PROVIDE_HIDDEN(__kernel_eh_frame_start = ABSOLUTE(.));
		KEEP(*(.eh_frame))
		PROVIDE_HIDDEN(__kernel_eh_frame_end = ABSOLUTE(.));
		PROVIDE_HIDDEN(__kernel_eh_frame_size = ABSOLUTE(ABSOLUTE(__kernel_eh_frame_end) - ABSOLUTE(__kernel_eh_frame_start)));
	}
	PROVIDE_HIDDEN(__kernel_sect_eh_frame_size = ABSOLUTE(ABSOLUTE(.) - ABSOLUTE(__kernel_sect_eh_frame_start)));

	PEROBJECT_SECTION(.pertask, __kernel_pertask, {
		KEEP(*(.data.pertask.head))
		KEEP(*(.data.pertask.early))
		KEEP(*(.data.pertask.middle))
		KEEP(*(.data.pertask))
	})

	PEROBJECT_SECTION_EX(.permman, __kernel_permman, PAGEDIR_SIZE, {
		KEEP(*(.data.permman.head))
		KEEP(*(.data.permman))
	})

#ifndef CONFIG_NO_SMP
	PEROBJECT_SECTION(.percpu, __kernel_percpu, {
		KEEP(*(.data.percpu.head))
		KEEP(*(.data.percpu))
		PROVIDE(thiscpu_idle = ABSOLUTE(ALIGN(__ARCH_CACHELINESIZE)));
		PROVIDE_HIDDEN(__kernel_percpu_full_bytes = CEIL_ALIGN(ABSOLUTE(thiscpu_x86_iob) + 8192 + 1, PAGESIZE));
#if defined(__i386__) || defined(__x86_64__)
		PROVIDE(thiscpu_x86_tss = CEIL_ALIGN(ABSOLUTE(thiscpu_idle + __kernel_pertask_size), PAGESIZE));
		PROVIDE(thiscpu_x86_iob = ABSOLUTE(thiscpu_x86_tss) + PAGESIZE);
		PROVIDE_HIDDEN(__x86_cpu_part1_bytes = ABSOLUTE(thiscpu_x86_iob));
		PROVIDE_HIDDEN(__x86_cpu_part1_pages = ABSOLUTE(thiscpu_x86_iob) / PAGESIZE);
/*		PROVIDE_HIDDEN(__x86_cpu_part2_pages = ABSOLUTE(2)); */
/*		PROVIDE_HIDDEN(__x86_cpu_part3_pages = ABSOLUTE(1)); */
#endif /* __i386__ || __x86_64__ */
	})
#endif /* !CONFIG_NO_SMP */

	/* Kernel debug data.
	 * NOTE: This VM area is automatically managed by the `DILINK'  link-driver,
	 *       such that at runtime it will contain the compressed versions of all
	 *       of the .debug_* sections. */
	PROVIDE_HIDDEN(__kernel_debug_start = ABSOLUTE(.));
	PROVIDE_HIDDEN(__kernel_debug_size = ABSOLUTE(1));
	. = ABSOLUTE(0);
	.kdebug 0 : AT(__kernel_debug_start - KERNEL_CORE_BASE) {
		. = ABSOLUTE(__kernel_debug_size);
	}
	. = ABSOLUTE(__kernel_debug_start + __kernel_debug_size);

	/* Also define end-symbols for linked debug sections. */
	PROVIDE_HIDDEN(__kernel_debug_line_end = ABSOLUTE(__kernel_debug_line_start + __kernel_debug_line_size));
	PROVIDE_HIDDEN(__kernel_debug_info_end = ABSOLUTE(__kernel_debug_info_start + __kernel_debug_info_size));
	PROVIDE_HIDDEN(__kernel_debug_aranges_end = ABSOLUTE(__kernel_debug_aranges_start + __kernel_debug_aranges_size));
	PROVIDE_HIDDEN(__kernel_debug_abbrev_end = ABSOLUTE(__kernel_debug_abbrev_start + __kernel_debug_abbrev_size));
	PROVIDE_HIDDEN(__kernel_debug_str_end = ABSOLUTE(__kernel_debug_str_start + __kernel_debug_str_size));
	PROVIDE_HIDDEN(__kernel_debug_line_str_end = ABSOLUTE(__kernel_debug_line_str_start + __kernel_debug_line_str_size));
	PROVIDE_HIDDEN(__kernel_debug_rnglists_end = ABSOLUTE(__kernel_debug_rnglists_start + __kernel_debug_rnglists_size));
	PROVIDE_HIDDEN(__kernel_debug_loclists_end = ABSOLUTE(__kernel_debug_loclists_start + __kernel_debug_loclists_size));


	IP_ALIGN(PAGESIZE);
	PROVIDE_HIDDEN(__kernel_rodata_end = ABSOLUTE(.));
	PROVIDE_HIDDEN(__kernel_rodata_size = ABSOLUTE(ABSOLUTE(__kernel_rodata_end) - ABSOLUTE(__kernel_rodata_start)));
	PROVIDE_HIDDEN(__kernel_rodata_numpages = ABSOLUTE(__kernel_rodata_size) / PAGESIZE);

	PROVIDE_HIDDEN(__debug_malloc_tracked_start = ABSOLUTE(.));
	PROVIDE_HIDDEN(__kernel_sect_data_start = ABSOLUTE(.));
	PROVIDE_HIDDEN(__kernel_data_start = ABSOLUTE(.));
	PROVIDE_HIDDEN(__kernel_data_startpage_p = addr2pageptr_p(ABSOLUTE(.)));
	SECTION(.data) {

		IP_ALIGN(__ARCH_CACHELINESIZE);
		*(.data.hot.read_mostly)
		*(.data.hot.read_mostly.tail)

		IP_ALIGN(__ARCH_CACHELINESIZE);
		*(.data.hot.write_mostly)
		*(.data.hot.write_mostly.tail)

		*(.data.hot .data.likely .data.hot.*)
		*(.data)
		*(.data.local.*)

#ifdef CONFIG_NO_SMP
		IP_ALIGN(__ARCH_CACHELINESIZE);
		PROVIDE_HIDDEN(__kernel_percpu_start = ABSOLUTE(.));
		PROVIDE(bootcpu = ABSOLUTE(.));
		KEEP(*(.data.percpu.head))
		KEEP(*(.data.percpu))
		PROVIDE_HIDDEN(__kernel_percpu_end = ABSOLUTE(.));
		PROVIDE_HIDDEN(__kernel_percpu_size = ABSOLUTE(ABSOLUTE(__kernel_percpu_end) - ABSOLUTE(__kernel_percpu_start)));
		IP_ALIGN(__ARCH_CACHELINESIZE);
		PROVIDE(bootidle = ABSOLUTE(.));
		PROVIDE(thiscpu_idle = ABSOLUTE(.));
		. += __kernel_pertask_size;
		IP_ALIGN(PAGESIZE);
#if defined(__i386__) || defined(__x86_64__)
		PROVIDE(thiscpu_x86_tss = ABSOLUTE(.));
		KEEP(*(.data.percpu.tss))
		STATIC_ASSERT((ABSOLUTE(.) - ABSOLUTE(__kernel_percpu_tss)) == SIZEOF_TSS);
		IP_ALIGN(PAGESIZE);
		PROVIDE(thiscpu_x86_iob = ABSOLUTE(.));
		PROVIDE_HIDDEN(__x86_iob_empty_base = ABSOLUTE(.));
		PROVIDE_HIDDEN(__x86_iob_empty_page_p = addr2pageptr_p(ABSOLUTE(.)));
		PROVIDE_HIDDEN(__x86_kernel_data_before_iob_size = ABSOLUTE(__x86_iob_empty_base - __kernel_data_start));
		PROVIDE_HIDDEN(__x86_kernel_data_before_iob_pages = ABSOLUTE(__x86_kernel_data_before_iob_size) / PAGESIZE);
		. += 8192; /* Make space for the IOBM table. */
		. += 1;    /* Trailing FFh-byte */
#endif /* __i386__ || __x86_64__ */
#endif /* CONFIG_NO_SMP */

#ifndef CONFIG_NO_KERNEL_BRANCH_PROFILING
		PROVIDE_HIDDEN(kernel_profile_branch_start = ABSOLUTE(.));
		KEEP(*(.data.profile_branch))
		PROVIDE_HIDDEN(kernel_profile_branch_end = ABSOLUTE(.));
		PROVIDE_HIDDEN(kernel_profile_branch_annotated_start = ABSOLUTE(.));
		KEEP(*(.data.profile_branch_annotated))
		PROVIDE_HIDDEN(kernel_profile_branch_annotated_end = ABSOLUTE(.));
#else /* !CONFIG_NO_KERNEL_BRANCH_PROFILING */
		PROVIDE_HIDDEN(kernel_profile_branch_start = ABSOLUTE(.));
		PROVIDE_HIDDEN(kernel_profile_branch_end = ABSOLUTE(.));
		PROVIDE_HIDDEN(kernel_profile_branch_annotated_start = ABSOLUTE(.));
		PROVIDE_HIDDEN(kernel_profile_branch_annotated_end = ABSOLUTE(.));
#endif /* CONFIG_NO_KERNEL_BRANCH_PROFILING */
		*(.data.cold .data.unlikely .data.cold.*)

		IP_ALIGN(PAGESIZE);
		PROVIDE_HIDDEN(__kernel_data_end = ABSOLUTE(.));
		PROVIDE_HIDDEN(__kernel_data_size = ABSOLUTE(ABSOLUTE(__kernel_data_end) - ABSOLUTE(__kernel_data_start)));
		PROVIDE_HIDDEN(__kernel_data_numpages = ABSOLUTE(__kernel_data_size) / PAGESIZE);
#if defined(__i386__) || defined(__x86_64__)
#ifdef CONFIG_NO_SMP
		PROVIDE_HIDDEN(__x86_kernel_data_after_iob_size = ABSOLUTE(__kernel_bss_end - __x86_iob_empty_base));
		PROVIDE_HIDDEN(__x86_kernel_data_after_iob_pages = ABSOLUTE(__x86_kernel_data_after_iob_size) / PAGESIZE);
#endif /* CONFIG_NO_SMP */
#endif /* __i386__ || __x86_64__ */

		PROVIDE_HIDDEN(__kernel_xdata_start = ABSOLUTE(.));
		PROVIDE_HIDDEN(__kernel_xdata_startpage_p = addr2pageptr_p(ABSOLUTE(.)));

		/* PDATA: Memory that remains mapping at VADDR=PADDR within the kernel VM.
		 *        Note  however that this memory is linked by its virtual address! */
		PROVIDE_HIDDEN(__kernel_pdata_start = ABSOLUTE(.));
		PROVIDE_HIDDEN(__kernel_pdata_start_p = ABSOLUTE(.) - KERNEL_CORE_BASE);
		PROVIDE_HIDDEN(__kernel_pdata_startpage_p = addr2pageptr_p(ABSOLUTE(.)));
		KEEP(*(.text.pdata.hot .pdata.hot .text.pdata.likely .pdata.likely))
		KEEP(*(.text.pdata .pdata))
		KEEP(*(.text.pdata.cold .pdata.cold .text.pdata.unlikely .pdata.unlikely))
		PROVIDE_HIDDEN(__kernel_pdata_end = ALIGN(PAGESIZE));
		PROVIDE_HIDDEN(__kernel_pdata_end_p = ABSOLUTE(__kernel_pdata_end - KERNEL_CORE_BASE));
		PROVIDE_HIDDEN(__kernel_pdata_endpage_p = addr2pageptr_p(ABSOLUTE(__kernel_pdata_end)));
		PROVIDE_HIDDEN(__kernel_pdata_size = ABSOLUTE(ABSOLUTE(__kernel_pdata_end) - ABSOLUTE(__kernel_pdata_start)));
		PROVIDE_HIDDEN(__kernel_pdata_numpages = ABSOLUTE(__kernel_pdata_size) / PAGESIZE);

		*(.text.xdata.hot .xdata.hot .text.xdata.likely .xdata.likely)
		*(.text.xdata .xdata)
		*(.text.xdata.cold .xdata.cold .text.xdata.unlikely .xdata.unlikely)

#if defined(__i386__) || defined(__x86_64__)
		PROVIDE_HIDDEN(bootcpu_x86_df_stack = ABSOLUTE(.));
		PROVIDE_HIDDEN(bootcpu_x86_df_stackpage_p = addr2pageptr_p(ABSOLUTE(bootcpu_x86_df_stack)));
		KEEP(*(.text.xdata.x86.free_unloader))
		/* Allocate the remainder for the boot cpu's #DF stack. */
		. += (KERNEL_DF_STACKSIZE - (ABSOLUTE(.) - ABSOLUTE(bootcpu_x86_df_stack)));
#endif /* __i386__ || __x86_64__ */
	}
	PROVIDE_HIDDEN(__kernel_sect_data_size = ABSOLUTE(ABSOLUTE(.) - ABSOLUTE(__kernel_sect_data_start)));

	PROVIDE_HIDDEN(__kernel_sect_bss_start = ABSOLUTE(.));
	SECTION(.bss) {
		*(.xbss.hot .xbss.likely .xbss.hot.*)
		*(.xbss)
		*(.xbss.cold .xbss.unlikely .xbss.cold.*)
		IP_ALIGN(PAGESIZE);
		PROVIDE_HIDDEN(__kernel_xdata_end = ABSOLUTE(.));
		PROVIDE_HIDDEN(__kernel_xdata_size = ABSOLUTE(ABSOLUTE(__kernel_xdata_end) - ABSOLUTE(__kernel_xdata_start)));
		PROVIDE_HIDDEN(__kernel_xdata_numpages = ABSOLUTE(__kernel_xdata_size) / PAGESIZE);

		PROVIDE_HIDDEN(__kernel_bss_start = ABSOLUTE(.));
		PROVIDE_HIDDEN(__kernel_bss_startpage_p = addr2pageptr_p(ABSOLUTE(.)));
		*(.bss.hot .bss.likely .bss.hot.*)
		*(.bss)
		*(.bss.cold .bss.unlikely .bss.cold.*)

		/* Boot CPU/TASK/VM data. */
#ifndef CONFIG_NO_SMP
		IP_ALIGN(PAGESIZE);
		PROVIDE(bootcpu = ABSOLUTE(.));
		. += thiscpu_idle;
		PROVIDE(bootidle = ABSOLUTE(.));
		. += __kernel_pertask_size;
		STATIC_ASSERT((bootcpu & PAGEMASK) == 0);
#if defined(__i386__) || defined(__x86_64__)
		STATIC_ASSERT((thiscpu_x86_tss & PAGEMASK) == 0);
		STATIC_ASSERT((thiscpu_x86_iob & PAGEMASK) == 0);
		. = ABSOLUTE(bootcpu + thiscpu_x86_tss);
		PROVIDE_HIDDEN(bootcpu_x86_tss = ABSOLUTE(.));
		STATIC_ASSERT((ABSOLUTE(.) & PAGEMASK) == 0);
		. = ABSOLUTE(bootcpu + thiscpu_x86_iob);
		/* Re-use  the  physical memory  allocated for  bootcpu's IOB
		 * vector as the pages used to describe the empty IOB vector. */
		PROVIDE_HIDDEN(__x86_iob_empty_base = ABSOLUTE(.));
		PROVIDE_HIDDEN(__x86_iob_empty_page_p = addr2pageptr_p(ABSOLUTE(.)));
		PROVIDE_HIDDEN(__x86_kernel_bss_before_iob_size = ABSOLUTE(__x86_iob_empty_base - __kernel_bss_start));
		PROVIDE_HIDDEN(__x86_kernel_bss_before_iob_pages = ABSOLUTE(__x86_kernel_bss_before_iob_size) / PAGESIZE);
		STATIC_ASSERT((ABSOLUTE(.) & PAGEMASK) == 0);
		. += 8192; /* Make space for the IOBM table. */
		. += 1;    /* Trailing FFh-byte */
#endif /* __i386__ || __x86_64__ */
#endif /* !CONFIG_NO_SMP */

#if defined(__i386__) || defined(__x86_64__)
		/* The value stored in `thiscpu_x86_iob.t_iomap' */
		PROVIDE_HIDDEN(__x86_cputss_iob_offset = ABSOLUTE(thiscpu_x86_iob - thiscpu_x86_tss));
#endif /* __i386__ || __x86_64__ */

		IP_ALIGN(__ARCH_CACHELINESIZE);
		PROVIDE(boottask = ABSOLUTE(.));
		. += __kernel_pertask_size;

		IP_ALIGN(__ARCH_CACHELINESIZE);
		PROVIDE_HIDDEN(asyncwork = ABSOLUTE(.));
		. += __kernel_pertask_size;

		IP_ALIGN(PAGEDIR_ALIGN);
		PROVIDE(mman_kernel = ABSOLUTE(.));
		PROVIDE(mman_kernel_lockops = ABSOLUTE(mman_kernel + thismman_lockops));
		PROVIDE(pagedir_kernel = ABSOLUTE(.));
		PROVIDE(pagedir_kernel_phys = ABSOLUTE(pagedir_kernel) - KERNEL_CORE_BASE);
		. += PAGEDIR_SIZE;
		. += __kernel_permman_size;

		PROVIDE_HIDDEN(__debug_malloc_tracked_end = ABSOLUTE(.));
		PROVIDE_HIDDEN(__debug_malloc_tracked_size = ABSOLUTE(ABSOLUTE(__debug_malloc_tracked_end) - ABSOLUTE(__debug_malloc_tracked_start)));

		PROVIDE_HIDDEN(kernel_membanks_initial = ABSOLUTE(.));


		IP_ALIGN(PAGESIZE);
#ifdef CONFIG_HAVE_KERNEL_STACK_GUARD
		PROVIDE_HIDDEN(__kernel_boottask_stack_guard = ABSOLUTE(.));
		/* Insert a placeholder page to catch stack overflows */
		. += PAGESIZE;
#endif /* CONFIG_HAVE_KERNEL_STACK_GUARD */
		PROVIDE_HIDDEN(__kernel_boottask_stack = ABSOLUTE(.));
		PROVIDE_HIDDEN(__kernel_boottask_stack_page_p = addr2pageptr_p(ABSOLUTE(.)));
		. += KERNEL_STACKSIZE;


		IP_ALIGN(PAGESIZE);
#ifdef CONFIG_HAVE_KERNEL_STACK_GUARD
		PROVIDE_HIDDEN(__kernel_asyncwork_stack_guard = ABSOLUTE(.));
		/* Insert a placeholder page to catch stack overflows */
		. += PAGESIZE;
#endif /* CONFIG_HAVE_KERNEL_STACK_GUARD */
		PROVIDE_HIDDEN(__kernel_asyncwork_stack = ABSOLUTE(.));
		PROVIDE_HIDDEN(__kernel_asyncwork_stack_page_p = addr2pageptr_p(ABSOLUTE(.)));
		. += KERNEL_STACKSIZE;


		IP_ALIGN(PAGESIZE);
#ifdef CONFIG_HAVE_KERNEL_STACK_GUARD
		PROVIDE_HIDDEN(__kernel_bootidle_stack_guard = ABSOLUTE(.));
		/* Insert a placeholder page to catch stack overflows */
		. += PAGESIZE;
#endif /* CONFIG_HAVE_KERNEL_STACK_GUARD */
		PROVIDE_HIDDEN(__kernel_bootidle_stack = ABSOLUTE(.));
		PROVIDE_HIDDEN(__kernel_bootidle_stack_page_p = addr2pageptr_p(ABSOLUTE(.)));
		. += KERNEL_IDLE_STACKSIZE;

		IP_ALIGN(PAGESIZE);
		*(.bss.mall.untracked)

#if defined(__i386__) || defined(__x86_64__)
		IP_ALIGN(PAGESIZE);
		KEEP(*(.bss.x86.pagedir_kernel_share))
#endif /* __i386__ || __x86_64__ */
	}
	PROVIDE_HIDDEN(__kernel_sect_bss_size = ABSOLUTE(ABSOLUTE(.) - ABSOLUTE(__kernel_sect_bss_start)));

	IP_ALIGN(PAGESIZE);
	PROVIDE_HIDDEN(__kernel_bss_end = ABSOLUTE(.));
	PROVIDE_HIDDEN(__kernel_bss_size = ABSOLUTE(ABSOLUTE(__kernel_bss_end) - ABSOLUTE(__kernel_bss_start)));
	PROVIDE_HIDDEN(__kernel_bss_numpages = ABSOLUTE(__kernel_bss_size) / PAGESIZE);
#if defined(__i386__) || defined(__x86_64__)
#ifndef CONFIG_NO_SMP
	PROVIDE_HIDDEN(__x86_kernel_bss_after_iob_size = ABSOLUTE(__kernel_bss_end - __x86_iob_empty_base));
	PROVIDE_HIDDEN(__x86_kernel_bss_after_iob_pages = ABSOLUTE(__x86_kernel_bss_after_iob_size) / PAGESIZE);
#endif /* !CONFIG_NO_SMP */
#endif /* __i386__ || __x86_64__ */


	PROVIDE_HIDDEN(__kernel_free_start = ABSOLUTE(.));
	PROVIDE_HIDDEN(__kernel_free_startpage_p = addr2pageptr_p(ABSOLUTE(.)));
	PROVIDE_HIDDEN(__kernel_size_nofree = ABSOLUTE(ABSOLUTE(__kernel_free_start) - ABSOLUTE(__kernel_start)));
	SECTION(.free) {
		/* A special section where data can go that will be unmapped, but have
		 * its physical backing memory not  be freed once `.free' is  deleted.
		 * This section is needed by x86_64's pageing initialization, or  more
		 * specifically its `kernel_initialize_boot_trampolines()' function */
		KEEP(*(.free.unmap_but_keep_allocated))
		IP_ALIGN(PAGESIZE);
		/* Start of the page-free section. */
		PROVIDE_HIDDEN(__kernel_pfree_startpage_p = addr2pageptr_p(ABSOLUTE(.)));
		*(.text.free)
		*(.text.free.alternatives)

		IP_ALIGN(__SIZEOF_POINTER__);
		PROVIDE_HIDDEN(__kernel_commandline_very_early_start = ABSOLUTE(.));
		KEEP(*(.rodata.free.commandline_options.very_early))
		PROVIDE_HIDDEN(__kernel_commandline_very_early_end = ABSOLUTE(.));

		IP_ALIGN(__SIZEOF_POINTER__);
		PROVIDE_HIDDEN(__kernel_commandline_early_start = ABSOLUTE(.));
		KEEP(*(.rodata.free.commandline_options.early))
		PROVIDE_HIDDEN(__kernel_commandline_early_end = ABSOLUTE(.));

		IP_ALIGN(__SIZEOF_POINTER__);
		PROVIDE_HIDDEN(__kernel_commandline_stable_start = ABSOLUTE(.));
		KEEP(*(.rodata.free.commandline_options.stable))
		PROVIDE_HIDDEN(__kernel_commandline_stable_end = ABSOLUTE(.));

		IP_ALIGN(__SIZEOF_POINTER__);
		PROVIDE_HIDDEN(__kernel_commandline_late_start = ABSOLUTE(.));
		KEEP(*(.rodata.free.commandline_options.late))
		PROVIDE_HIDDEN(__kernel_commandline_late_end = ABSOLUTE(.));

#if defined(__i386__) || defined(__x86_64__)
#ifdef __x86_64__
		PROVIDE_HIDDEN(__x86_fixup_fsgsbase_start = ABSOLUTE(.));
		KEEP(*(.rodata.free.x86.fixup_fsgsbase))
		PROVIDE_HIDDEN(__x86_fixup_fsgsbase_end = ABSOLUTE(.));
#endif /* __x86_64__ */

#ifndef CONFIG_NO_SMP
		/* PROVIDE_HIDDEN(__kernel_percpu_tss = ABSOLUTE(.)); */
		KEEP(*(.data.percpu.tss))
		STATIC_ASSERT((ABSOLUTE(.) - ABSOLUTE(__kernel_percpu_tss)) == SIZEOF_TSS);
#endif /* !CONFIG_NO_SMP */

		PROVIDE_HIDDEN(__x86_alternatives_start = ABSOLUTE(.));
		KEEP(*(.alternatives))
		PROVIDE_HIDDEN(__x86_alternatives_end = ABSOLUTE(.));
#endif /* __i386__ || __x86_64__ */

#ifdef CONFIG_HAVE_KERNEL_SELFTEST
		PROVIDE_HIDDEN(__kernel_selftest_start = ABSOLUTE(.));
		KEEP(*(.rodata.free.callback.selftest))
		PROVIDE_HIDDEN(__kernel_selftest_end = ABSOLUTE(.));
#endif /* CONFIG_HAVE_KERNEL_SELFTEST */

		*(.rodata.free)
		*(.rodata.str.free)
		*(.data.free)
		*(.bss.free)
		IP_ALIGN(PAGESIZE);
		PROVIDE_HIDDEN(__kernel_end = ABSOLUTE(.));
		/* TODO: Check if the outer `ABSOLUTE()' here is actually necessary (remove if it is not). */
		PROVIDE_HIDDEN(__kernel_size = ABSOLUTE(ABSOLUTE(__kernel_end) - ABSOLUTE(__kernel_start)));

		PROVIDE_HIDDEN(__kernel_pfree_endpage_p = addr2pageptr_p(ABSOLUTE(.)));
		PROVIDE_HIDDEN(__kernel_pfree_numpages = ABSOLUTE(ABSOLUTE(__kernel_pfree_endpage_p) - ABSOLUTE(__kernel_pfree_startpage_p)));

		PROVIDE_HIDDEN(__kernel_free_end = ABSOLUTE(.));
		PROVIDE_HIDDEN(__kernel_free_size = ABSOLUTE(ABSOLUTE(__kernel_free_end) - ABSOLUTE(__kernel_free_start)));
		PROVIDE_HIDDEN(__kernel_free_numpages = ABSOLUTE(__kernel_free_size) / PAGESIZE);
	}


	PROVIDE(thiscpu_idle_sstate = ABSOLUTE(ABSOLUTE(thiscpu_idle) + ABSOLUTE(this_sstate)));
	PROVIDE_HIDDEN(bootcpu_idle_pid = ABSOLUTE(BOOTCPU_SYMBOL(thiscpu_idle_pid)));
	PROVIDE_HIDDEN(bootcpu_sched_current = ABSOLUTE(BOOTCPU_SYMBOL(thiscpu_sched_current)));

#if defined(__i386__) || defined(__x86_64__)
#ifndef CONFIG_NO_KERNEL_X86_BOOT0
	PROVIDE_HIDDEN(__kernel_sector_count = ABSOLUTE((__kernel_size + 511) / 512));
#endif /* !CONFIG_NO_KERNEL_X86_BOOT0 */

	PROVIDE_HIDDEN(__templatecpu_x86_gdt = ABSOLUTE(__kernel_percpu_start + thiscpu_x86_gdt));
	PROVIDE_HIDDEN(bootcpu_x86_dfstack_node = ABSOLUTE(BOOTCPU_SYMBOL(thiscpu_x86_dfstacknode)));
	PROVIDE_HIDDEN(bootcpu_x86_dfstack_part = ABSOLUTE(BOOTCPU_SYMBOL(thiscpu_x86_dfstackpart)));
	PROVIDE(bootcpu_x86_cpufeatures = ABSOLUTE(BOOTCPU_SYMBOL(thiscpu_x86_cpufeatures)));
	PROVIDE(bootcpu_x86_cpuid = ABSOLUTE(BOOTCPU_SYMBOL(thiscpu_x86_cpuid)));
	PROVIDE(bootcpu_x86_gdt = ABSOLUTE(BOOTCPU_SYMBOL(thiscpu_x86_gdt)));

#define TSS_BASE    BOOTCPU_SYMBOL(thiscpu_x86_tss)
#define TSS_DF_BASE BOOTCPU_SYMBOL(thiscpu_x86_tssdf)
#define LDT_BASE    BOOTCPU_SYMBOL(thiscpu_x86_ldt)

	/* The size of the `struct tss' plus the associated IOB vector addend. */
#define SIZEOF_TSS_PLUS_IOB_VECTOR \
	(CEIL_ALIGN(SIZEOF_TSS, PAGESIZE) + 2 * PAGESIZE + 1)

	/* Pre-calculate TSS and TLS segment initializers. */
#ifdef __x86_64__
#define GDT_L  1
#define GDT_DB 0
#define DEFINE_SEGMENT_SYMBOLS(name, TYPE, args)                 \
	PROVIDE_HIDDEN(name##_lo = SEGMENT_##TYPE##_INIT_U    args); \
	PROVIDE_HIDDEN(name##_hi = SEGMENT_##TYPE##_HI_INIT_U args);
#else /* __x86_64__ */
#define GDT_L  0
#define GDT_DB 1
#define DEFINE_SEGMENT_SYMBOLS(name, TYPE, args)               \
	PROVIDE_HIDDEN(name##_lo = SEGMENT_##TYPE##_INIT_UL args); \
	PROVIDE_HIDDEN(name##_hi = SEGMENT_##TYPE##_INIT_UH args);
#endif /* !__x86_64__ */
	DEFINE_SEGMENT_SYMBOLS(__x86_gdt_tss, TSS, (TSS_BASE, SIZEOF_TSS_PLUS_IOB_VECTOR - 1, SEGMENT_DESCRIPTOR_TYPE_TSS_AVL, 0, 1, 0, 0))
	DEFINE_SEGMENT_SYMBOLS(__x86_gdt_ldt, LDT, (LDT_BASE, (LDT_SEGMENT_COUNT * SIZEOF_SEGMENT_DESCRIPTOR) - 1, 3, 1, 0, 0))
#ifndef __x86_64__
	DEFINE_SEGMENT_SYMBOLS(__x86_gdt_tss_df, TSS, (TSS_DF_BASE, SIZEOF_TSS - 1, SEGMENT_DESCRIPTOR_TYPE_TSS_AVL, 0, 1, 0, 0))
	DEFINE_SEGMENT_SYMBOLS(__x86_gdt_kernel_tls, DESCRIPTOR, (boottask, 0xfffff, SEGMENT_DESCRIPTOR_TYPE_DATA_RDWR, 1, 0, 1, 0, GDT_L, GDT_DB, 1))
#endif /* !__x86_64__ */
#undef DEFINE_SEGMENT_SYMBOLS
#undef GDT_DB
#undef GDT_L

	PROVIDE(thiscpu_idle_x86_kernel_psp0 = ABSOLUTE(ABSOLUTE(thiscpu_idle) + ABSOLUTE(this_x86_kernel_psp0)));

	PROVIDE_HIDDEN(x86_dbg_cpu_temporary_b0 = (ABSOLUTE(dbg_cpu_temporary) & 0x000000ff) >> 0);
	PROVIDE_HIDDEN(x86_dbg_cpu_temporary_b1 = (ABSOLUTE(dbg_cpu_temporary) & 0x0000ff00) >> 8);
	PROVIDE_HIDDEN(x86_dbg_cpu_temporary_b2 = (ABSOLUTE(dbg_cpu_temporary) & 0x00ff0000) >> 16);
	PROVIDE_HIDDEN(x86_dbg_cpu_temporary_b3 = (ABSOLUTE(dbg_cpu_temporary) & 0xff000000) >> 24);
#ifdef __x86_64__
	PROVIDE_HIDDEN(x86_dbg_cpu_temporary_b4 = (ABSOLUTE(dbg_cpu_temporary) & 0x000000ff00000000) >> 32);
	PROVIDE_HIDDEN(x86_dbg_cpu_temporary_b5 = (ABSOLUTE(dbg_cpu_temporary) & 0x0000ff0000000000) >> 40);
	PROVIDE_HIDDEN(x86_dbg_cpu_temporary_b6 = (ABSOLUTE(dbg_cpu_temporary) & 0x00ff000000000000) >> 48);
	PROVIDE_HIDDEN(x86_dbg_cpu_temporary_b7 = (ABSOLUTE(dbg_cpu_temporary) & 0xff00000000000000) >> 56);
#endif /* __x86_64__ */

	PROVIDE_HIDDEN(x86_dbg_exitstate_b0 = (ABSOLUTE(x86_dbg_exitstate) & 0x000000ff) >> 0);
	PROVIDE_HIDDEN(x86_dbg_exitstate_b1 = (ABSOLUTE(x86_dbg_exitstate) & 0x0000ff00) >> 8);
	PROVIDE_HIDDEN(x86_dbg_exitstate_b2 = (ABSOLUTE(x86_dbg_exitstate) & 0x00ff0000) >> 16);
	PROVIDE_HIDDEN(x86_dbg_exitstate_b3 = (ABSOLUTE(x86_dbg_exitstate) & 0xff000000) >> 24);
#ifdef __x86_64__
	PROVIDE_HIDDEN(x86_dbg_exitstate_b4 = (ABSOLUTE(x86_dbg_exitstate) & 0x000000ff00000000) >> 32);
	PROVIDE_HIDDEN(x86_dbg_exitstate_b5 = (ABSOLUTE(x86_dbg_exitstate) & 0x0000ff0000000000) >> 40);
	PROVIDE_HIDDEN(x86_dbg_exitstate_b6 = (ABSOLUTE(x86_dbg_exitstate) & 0x00ff000000000000) >> 48);
	PROVIDE_HIDDEN(x86_dbg_exitstate_b7 = (ABSOLUTE(x86_dbg_exitstate) & 0xff00000000000000) >> 56);
#endif /* __x86_64__ */

#ifndef __x86_64__
	PROVIDE_HIDDEN(bootcpu_x86_tss = ABSOLUTE(BOOTCPU_SYMBOL(thiscpu_x86_tss)));
#endif /* !__x86_64__ */

#ifndef __x86_64__
#ifndef CONFIG_NO_KERNEL_X86_PAGING_P32
	PROVIDE_HIDDEN(__x86_p32_identity_mapped_text_4mib_index = (ABSOLUTE(__x86_paging_init_identity_mapped_text) - KERNEL_CORE_BASE) / 0x400000);
	PROVIDE_HIDDEN(__x86_p32_identity_mapped_text_4mib_e2_word = ABSOLUTE(pagedir_kernel + (__x86_p32_identity_mapped_text_4mib_index * 4)));
	PROVIDE_HIDDEN(__x86_p32_identity_mapped_text_4mib_ks_share = ABSOLUTE((__x86_pagedir_kernel_share - KERNEL_CORE_BASE) + (__x86_p32_identity_mapped_text_4mib_index * 0x1000)));
#endif /* !CONFIG_NO_KERNEL_X86_PAGING_P32 */
#endif /* !__x86_64__ */

	/* The main IDT used during normal operations */
#include "arch/i386/idt/idt.ld"

#ifndef CONFIG_NO_KERNEL_DEBUGGER

	/* The IDT active for `dbg_cpu' while the debugger is in use */
#define PREFIX x86_dbg
#include "arch/i386/idt/idt.ld"

#ifndef CONFIG_NO_SMP
	/* The IDT active for all CPUs other than `dbg_cpu' while the debugger is in use */
#define PREFIX x86_dbgaltcore
#include "arch/i386/idt/idt.ld"
#endif /* !CONFIG_NO_SMP */
#endif /* !CONFIG_NO_KERNEL_DEBUGGER */
#endif /* __i386__ || __x86_64__ */

	/* Allocate debug sections alongside each other. */
	.debug_line 0 : { *(.debug_line) }
	.debug_info 0 : { *(.debug_info) }
	.debug_aranges 0 : { *(.debug_aranges) }
	.debug_abbrev 0 : { *(.debug_abbrev) }
	.debug_str 0 : { *(.debug_str) }
	.debug_line_str 0 : { *(.debug_line_str) }
	.debug_rnglists 0 : { *(.debug_rnglists) }
	.debug_loclists 0 : { *(.debug_loclists) }

	/DISCARD/ : {
		*(.rel*)
		*(.discard)
		*(.dynamic)
		*(.symtab)
		*(.strtab)
		*(.comment)
		*(.eh_frame_hdr)
		*(.note.gnu.build-id)
	}
}

#endif /* !GUARD_KERNEL_CORE__KERNEL_LD */
