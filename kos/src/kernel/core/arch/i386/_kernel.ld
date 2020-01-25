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
#ifndef GUARD_KERNEL_CORE_ARCH_I386__KERNEL_LD
#define GUARD_KERNEL_CORE_ARCH_I386__KERNEL_LD 1
#define __LINKER__ 1
#define _KOS_SOURCE 1
#define _KOS_KERNEL_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/gdt.h>
#include <kernel/idt.h>
#include <kernel/multiboot.h>
#include <kernel/paging.h>
#include <kernel/syscall-tables.h>
#include <sched/tss.h>

#include <hybrid/align.h>

#include <asm/cacheline.h>
#include <asm/pageid.h>
#include <kos/kernel/gdt.h>
#include <kos/kernel/segment.h>

#undef likely
#undef unlikely

#define addr2pageid(ptr)  __ARCH_PAGEID_ENCODE(ptr)
#define addr2pageptr(ptr) (((ptr) - KERNEL_CORE_BASE) >> 12)

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


ENTRY(_start)
SECTIONS {

	. = KERNEL_CORE_BASE + 0x100000;

	PROVIDE_HIDDEN(__kernel_start = ABSOLUTE(.));

#ifndef CONFIG_NO_BOOT0
	SECTION(.x86.boot0) {
		KEEP(*(.x86.boot0))
	}
	. = KERNEL_CORE_BASE + 0x100200;
#endif /* !CONFIG_NO_BOOT0 */

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

	IP_ALIGN(PAGESIZE);
	PROVIDE_HIDDEN(__kernel_sect_text_start = ABSOLUTE(.));
	PROVIDE_HIDDEN(__kernel_text_startpageid = addr2pageid(ABSOLUTE(.)));
	PROVIDE_HIDDEN(__kernel_text_startpageptr = addr2pageptr(ABSOLUTE(.)));
	SECTION(.text) {
		*(.text.hot .text.likely .text.hot.*)
		*(.text .text._ZN*)
		*(.text.crt.*)
		*(.text.kernel.*)
		*(.text.unlikely*)     /* Should be necessary, but prevents problems... */
		*(.text.x86.syscall.*) /* C-level implementations of system calls. */
#ifdef __x86_64__
		*(.text.x86.syscall32.*) /* C-level implementations of system calls (for compatibility mode). */
#endif /* __x86_64__ */
		*(.text.x86.cisr.*)
		*(.text.x86.asmisr.*)
#ifdef __x86_64__
		*(.text.x86.asm64_syscall.*)
#endif /* __x86_64__ */
		*(.text.x86.asm32_syscall_int80.*)
		*(.text.x86.asm32_syscall_sysenter.*)
#ifdef __x86_64__
		*(.text.x86.asm32_syscall_sysrun32.*)
#endif /* __x86_64__ */
		*(.text.x86.*)
		*(.text.cold .text.unlikely .text.cold.*)
	}

#define DEFINE_CALLBACK_VECTOR(name,section) \
		IP_ALIGN(__SIZEOF_POINTER__); \
		PROVIDE_HIDDEN(__kernel_##name##_start = ABSOLUTE(.)); \
		KEEP(*(section)) \
		PROVIDE_HIDDEN(__kernel_##name##_end = ABSOLUTE(.));


	IP_ALIGN(PAGESIZE);
	PROVIDE_HIDDEN(__kernel_sect_text_size = ABSOLUTE(ABSOLUTE(.) - ABSOLUTE(__kernel_sect_text_start)));
	PROVIDE_HIDDEN(__kernel_text_endpageid = addr2pageid(ABSOLUTE(.)));
	PROVIDE_HIDDEN(__kernel_text_numpages = ABSOLUTE(ABSOLUTE(__kernel_text_endpageid) - ABSOLUTE(__kernel_text_startpageid)));

	PROVIDE_HIDDEN(__kernel_sect_rodata_start = ABSOLUTE(.));
	PROVIDE_HIDDEN(__kernel_rodata_startpageid = addr2pageid(ABSOLUTE(.)));
	PROVIDE_HIDDEN(__kernel_rodata_startpageptr = addr2pageptr(ABSOLUTE(.)));
	SECTION(.rodata) {
		*(.rodata.hot .rodata.likely .rodata.hot.*)
		*(.rodata.x86.*)
		KEEP(*(.rodata.elfexec_system_rtld))
		PROVIDE_HIDDEN(elfexec_system_rtld_startpageptr = addr2pageptr(ABSOLUTE(elfexec_system_rtld)));
		PROVIDE_HIDDEN(elfexec_system_rtld_numpages     = ABSOLUTE(elfexec_system_rtld_size) / PAGESIZE);
#ifdef __x86_64__
		/* Compatibility-mode libdl.so binary (32-bit application) */
		KEEP(*(.rodata.elfexec_system_rtld32))
		PROVIDE_HIDDEN(elfexec_system_rtld32_startpageptr = addr2pageptr(ABSOLUTE(elfexec_system_rtld32)));
		PROVIDE_HIDDEN(elfexec_system_rtld32_numpages     = ABSOLUTE(elfexec_system_rtld32_size) / PAGESIZE);
#endif /* __x86_64__ */
		*(.rodata .rodata.kernel_symtab .rodata.cst*)
		*(.rodata.str* .rodata.*.str* .rodata.kernel_strtab)
#ifndef CONFIG_NO_DEBUGGER
		*(.rodata.cold.debug_function_str)
		IP_ALIGN(__SIZEOF_POINTER__);
		PROVIDE_HIDDEN(__kernel_debug_functions_start = ABSOLUTE(.));
		KEEP(*(.rodata.cold.debug_functions))
		PROVIDE_HIDDEN(__kernel_debug_functions_end = ABSOLUTE(.));
		PROVIDE_HIDDEN(__kernel_debug_functions_size = ABSOLUTE(ABSOLUTE(__kernel_debug_functions_end) - ABSOLUTE(__kernel_debug_functions_start)));
		DEFINE_CALLBACK_VECTOR(dbg_init, .rodata.cold.callback.dbg_init)
		DEFINE_CALLBACK_VECTOR(dbg_reset, .rodata.cold.callback.dbg_reset)
		DEFINE_CALLBACK_VECTOR(dbg_fini, .rodata.cold.callback.dbg_fini)
#endif /* !CONFIG_NO_DEBUGGER */
		DEFINE_CALLBACK_VECTOR(system_clearcaches, .rodata.cold.callback.system_clearcaches)

		DEFINE_CALLBACK_VECTOR(idle_job, .rodata.callback.idle_job)
		DEFINE_CALLBACK_VECTOR(pertask_init, .rodata.callback.pertask.init)
		DEFINE_CALLBACK_VECTOR(pertask_fini, .rodata.callback.pertask.fini)
		DEFINE_CALLBACK_VECTOR(pertask_clone, .rodata.callback.pertask.clone)
		DEFINE_CALLBACK_VECTOR(pertask_onexit, .rodata.callback.pertask.onexit)
		DEFINE_CALLBACK_VECTOR(pervm_init, .rodata.callback.pervm.init)
		DEFINE_CALLBACK_VECTOR(pervm_fini, .rodata.callback.pervm.fini)
		DEFINE_CALLBACK_VECTOR(pervm_clone, .rodata.callback.pervm.clone)
		DEFINE_CALLBACK_VECTOR(pervm_onexec, .rodata.callback.pervm.onexec)
		DEFINE_CALLBACK_VECTOR(validatable_heaps, .rodata.heaps.validatable)

		*(.rodata.cold .rodata.unlikely .rodata.cold.*)
	}
#undef DEFINE_CALLBACK_VECTOR
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

#define DEFINE_DEBUG_SECTION(section_name, alignment, name, sections)                      \
	PROVIDE_HIDDEN(name##_start = ABSOLUTE(ALIGN(alignment)));                             \
	. = ABSOLUTE(0);                                                                       \
	section_name 0 : AT(name##_start - KERNEL_CORE_BASE) {                                 \
		KEEP(sections)                                                                     \
		PROVIDE_HIDDEN(name##_size = ABSOLUTE(.));                                         \
	}                                                                                      \
	PROVIDE_HIDDEN(name##_end = ABSOLUTE(ABSOLUTE(name##_start) + ABSOLUTE(name##_size))); \
	. += ABSOLUTE(name##_start);
	DEFINE_DEBUG_SECTION(.debug_line, 1, __kernel_debug_line, *(.debug_line))
	DEFINE_DEBUG_SECTION(.debug_info, 1, __kernel_debug_info, *(.debug_info))
	DEFINE_DEBUG_SECTION(.debug_aranges, 8, __kernel_debug_aranges, *(.debug_aranges))
	DEFINE_DEBUG_SECTION(.debug_abbrev, 1, __kernel_debug_abbrev, *(.debug_abbrev))
	DEFINE_DEBUG_SECTION(.debug_str, 1, __kernel_debug_str, *(.debug_str))
	DEFINE_DEBUG_SECTION(.debug_ranges, 8, __kernel_debug_ranges, *(.debug_ranges))
	DEFINE_DEBUG_SECTION(.debug_loc, 1, __kernel_debug_loc, *(.debug_loc))
#undef DEFINE_DEBUG_SECTION

#define DEFINE_DEBUG_SECTION_WRAPPER(name)                                         \
	PROVIDE_HIDDEN(__wrapper_##name##_start = ABSOLUTE(.));                        \
	. = ABSOLUTE(0);                                                               \
	.name.wrapper 0 : AT(__wrapper_##name##_start - KERNEL_CORE_BASE) { BYTE(0); } \
	. += ABSOLUTE(__wrapper_##name##_start);
	DEFINE_DEBUG_SECTION_WRAPPER(debug_line)
	DEFINE_DEBUG_SECTION_WRAPPER(debug_info)
	DEFINE_DEBUG_SECTION_WRAPPER(debug_aranges)
	DEFINE_DEBUG_SECTION_WRAPPER(debug_abbrev)
	DEFINE_DEBUG_SECTION_WRAPPER(debug_str)
	DEFINE_DEBUG_SECTION_WRAPPER(debug_ranges)
	DEFINE_DEBUG_SECTION_WRAPPER(debug_loc)
#undef DEFINE_DEBUG_SECTION_WRAPPER

	PEROBJECT_SECTION(.pertask, __kernel_pertask, {
		KEEP(*(.data.pertask.head))
		KEEP(*(.data.pertask.early))
		KEEP(*(.data.pertask))
	})

	PEROBJECT_SECTION_EX(.pervm, __kernel_pervm, PAGEDIR_SIZE, {
		KEEP(*(.data.pervm.head))
		KEEP(*(.data.pervm))
	})

#ifndef CONFIG_NO_SMP
	PEROBJECT_SECTION(.percpu, __kernel_percpu, {
		KEEP(*(.data.percpu.head))
		KEEP(*(.data.percpu))
		PROVIDE(thiscpu_idle = ABSOLUTE(ALIGN(__ARCH_CACHELINESIZE)));
		PROVIDE(thiscpu_x86_tss = CEIL_ALIGN(ABSOLUTE(thiscpu_idle + __kernel_pertask_size), PAGESIZE));
		PROVIDE(thiscpu_x86_iob = ABSOLUTE(thiscpu_x86_tss) + PAGESIZE);
		PROVIDE_HIDDEN(__kernel_percpu_full_bytes = CEIL_ALIGN(ABSOLUTE(thiscpu_x86_iob) + 8192 + 1, PAGESIZE));
		PROVIDE_HIDDEN(__x86_cpu_part1_pages = ABSOLUTE(thiscpu_x86_iob) / PAGESIZE);
/*		PROVIDE_HIDDEN(__x86_cpu_part2_pages = ABSOLUTE(2)); */
/*		PROVIDE_HIDDEN(__x86_cpu_part3_pages = ABSOLUTE(1)); */
	})
#endif /* !CONFIG_NO_SMP */

	IP_ALIGN(PAGESIZE);
	PROVIDE_HIDDEN(__kernel_rodata_end = ABSOLUTE(.));
	PROVIDE_HIDDEN(__kernel_rodata_size = ABSOLUTE(ABSOLUTE(__kernel_rodata_end) - ABSOLUTE(__kernel_start)));
	PROVIDE_HIDDEN(__kernel_rodata_endpageid = addr2pageid(ABSOLUTE(.)));
	PROVIDE_HIDDEN(__kernel_rodata_numpages = ABSOLUTE(ABSOLUTE(__kernel_rodata_endpageid) - ABSOLUTE(__kernel_rodata_startpageid)));

	PROVIDE_HIDDEN(__debug_malloc_tracked_start = ABSOLUTE(.));
	PROVIDE_HIDDEN(__kernel_sect_data_start = ABSOLUTE(.));
	PROVIDE_HIDDEN(__kernel_data_startpageid = addr2pageid(ABSOLUTE(.)));
	PROVIDE_HIDDEN(__kernel_data_startpageptr = addr2pageptr(ABSOLUTE(.)));
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
		PROVIDE(_bootcpu = ABSOLUTE(.));
		KEEP(*(.data.percpu.head))
		KEEP(*(.data.percpu))
		PROVIDE_HIDDEN(__kernel_percpu_end = ABSOLUTE(.));
		PROVIDE_HIDDEN(__kernel_percpu_size = ABSOLUTE(ABSOLUTE(__kernel_percpu_end) - ABSOLUTE(__kernel_percpu_start)));
		IP_ALIGN(__ARCH_CACHELINESIZE);
		PROVIDE(_bootidle = ABSOLUTE(.));
		PROVIDE(thiscpu_idle = ABSOLUTE(.));
		. += __kernel_pertask_size;
		IP_ALIGN(PAGESIZE);
		PROVIDE(thiscpu_x86_tss = ABSOLUTE(.));
		KEEP(*(.data.percpu.tss))
		STATIC_ASSERT((ABSOLUTE(.) - ABSOLUTE(__kernel_percpu_tss)) == SIZEOF_TSS);
		IP_ALIGN(PAGESIZE);
		PROVIDE(thiscpu_x86_iob = ABSOLUTE(.));
		PROVIDE_HIDDEN(__x86_iob_empty_base = ABSOLUTE(.));
		PROVIDE_HIDDEN(__x86_iob_empty_pageid = addr2pageid(ABSOLUTE(.)));
		PROVIDE_HIDDEN(__x86_iob_empty_pageptr = addr2pageptr(ABSOLUTE(.)));
		PROVIDE_HIDDEN(__x86_kernel_data_before_iob_pages = ABSOLUTE(__x86_iob_empty_pageid - __kernel_data_startpageid));
		. += 8192; /* Make space for the IOBM table. */
		. += 1;    /* Trailing FFh-byte */
#endif /* CONFIG_NO_SMP */

#ifndef CONFIG_NO_BRANCH_PROFILING
		PROVIDE_HIDDEN(kernel_profile_branch_start = ABSOLUTE(.));
		KEEP(*(.data.profile_branch))
		PROVIDE_HIDDEN(kernel_profile_branch_end = ABSOLUTE(.));
		PROVIDE_HIDDEN(kernel_profile_branch_annotated_start = ABSOLUTE(.));
		KEEP(*(.data.profile_branch_annotated))
		PROVIDE_HIDDEN(kernel_profile_branch_annotated_end = ABSOLUTE(.));
#else /* !CONFIG_NO_BRANCH_PROFILING */
		PROVIDE_HIDDEN(kernel_profile_branch_start = ABSOLUTE(.));
		PROVIDE_HIDDEN(kernel_profile_branch_end = ABSOLUTE(.));
		PROVIDE_HIDDEN(kernel_profile_branch_annotated_start = ABSOLUTE(.));
		PROVIDE_HIDDEN(kernel_profile_branch_annotated_end = ABSOLUTE(.));
#endif /* CONFIG_NO_BRANCH_PROFILING */
		*(.data.cold .data.unlikely .data.cold.*)

		IP_ALIGN(PAGESIZE);
		PROVIDE_HIDDEN(__kernel_data_endpageid = addr2pageid(ABSOLUTE(.)));
		PROVIDE_HIDDEN(__kernel_data_numpages = ABSOLUTE(ABSOLUTE(__kernel_data_endpageid) - ABSOLUTE(__kernel_data_startpageid)));
#ifdef CONFIG_NO_SMP
		PROVIDE_HIDDEN(__x86_kernel_bata_after_iob_pages = ABSOLUTE(__kernel_bss_endpageid - __x86_iob_empty_pageid));
#endif /* CONFIG_NO_SMP */

		PROVIDE_HIDDEN(__kernel_xdata_startpageid = addr2pageid(ABSOLUTE(.)));
		PROVIDE_HIDDEN(__kernel_xdata_startpageptr = addr2pageptr(ABSOLUTE(.)));
		/* PDATA: Memory that remains mapping at VADDR=PADDR within the kernel VM.
		 *        Note however that this memory is linked by its virtual address! */
		PROVIDE_HIDDEN(__kernel_pdata_start = ABSOLUTE(.));
		PROVIDE_HIDDEN(__kernel_pdata_startpageid = addr2pageid(ABSOLUTE(.)));
		PROVIDE_HIDDEN(__kernel_pdata_startpageptr = addr2pageptr(ABSOLUTE(.)));
		KEEP(*(.text.pdata.hot .pdata.hot .text.pdata.likely .pdata.likely))
		KEEP(*(.text.pdata .pdata))
		KEEP(*(.text.pdata.cold .pdata.cold .text.pdata.unlikely .pdata.unlikely))
		PROVIDE_HIDDEN(__kernel_pdata_end = ALIGN(PAGESIZE));
		PROVIDE_HIDDEN(__kernel_pdata_endpageid = addr2pageid(ABSOLUTE(ALIGN(PAGESIZE))));
		PROVIDE_HIDDEN(__kernel_pdata_endpageptr = addr2pageptr(ABSOLUTE(ALIGN(PAGESIZE))));
		PROVIDE_HIDDEN(__kernel_pdata_numpages = ABSOLUTE(ABSOLUTE(__kernel_pdata_endpageid) - ABSOLUTE(__kernel_pdata_startpageid)));
		PROVIDE_HIDDEN(__kernel_pdata_numbytes = ABSOLUTE(ABSOLUTE(__kernel_pdata_end) - ABSOLUTE(__kernel_pdata_start)));

		*(.text.xdata.hot .xdata.hot .text.xdata.likely .xdata.likely)
		*(.text.xdata .xdata)
		*(.text.xdata.cold .xdata.cold .text.xdata.unlikely .xdata.unlikely)

		PROVIDE_HIDDEN(__x86_bootcpu_df_stack = ABSOLUTE(.));
		KEEP(*(.text.xdata.x86.free_unloader))
		/* Allocate the remainder for the boot cpu's #DF stack. */
		. += (KERNEL_DF_STACKSIZE - (ABSOLUTE(.) - ABSOLUTE(__x86_bootcpu_df_stack)));
	}
	PROVIDE_HIDDEN(__kernel_sect_data_size = ABSOLUTE(ABSOLUTE(.) - ABSOLUTE(__kernel_sect_data_start)));

	PROVIDE_HIDDEN(__kernel_sect_bss_start = ABSOLUTE(.));
	SECTION(.bss) {
		*(.xbss.hot .xbss.likely .xbss.hot.*)
		*(.xbss)
		*(.xbss.cold .xbss.unlikely .xbss.cold.*)
		IP_ALIGN(PAGESIZE);
		PROVIDE_HIDDEN(__kernel_xdata_endpageid = addr2pageid(ABSOLUTE(.)));
		PROVIDE_HIDDEN(__kernel_xdata_numpages = ABSOLUTE(ABSOLUTE(__kernel_xdata_endpageid) - ABSOLUTE(__kernel_xdata_startpageid)));

		PROVIDE_HIDDEN(__kernel_bss_startpageid = addr2pageid(ABSOLUTE(.)));
		PROVIDE_HIDDEN(__kernel_bss_startpageptr = addr2pageptr(ABSOLUTE(.)));
		*(.bss.hot .bss.likely .bss.hot.*)
		*(.bss)
		*(.bss.cold .bss.unlikely .bss.cold.*)

		/* Boot CPU/TASK/VM data. */
#ifndef CONFIG_NO_SMP
		IP_ALIGN(PAGESIZE);
		PROVIDE(_bootcpu = ABSOLUTE(.));
		. += thiscpu_idle;
		PROVIDE(_bootidle = ABSOLUTE(.));
		. += __kernel_pertask_size;
		STATIC_ASSERT((_bootcpu & PAGEMASK) == 0);
		STATIC_ASSERT((thiscpu_x86_tss & PAGEMASK) == 0);
		STATIC_ASSERT((thiscpu_x86_iob & PAGEMASK) == 0);
		. = ABSOLUTE(_bootcpu + thiscpu_x86_tss);
		PROVIDE_HIDDEN(_bootcpu_x86_tss = ABSOLUTE(.));
		STATIC_ASSERT((ABSOLUTE(.) & PAGEMASK) == 0);
		. = ABSOLUTE(_bootcpu + thiscpu_x86_iob);
		/* Re-use the physical memory allocated for _bootcpu's IOB
		 * vector as the pages used to describe the empty IOB vector. */
		PROVIDE_HIDDEN(__x86_iob_empty_base = ABSOLUTE(.));
		PROVIDE_HIDDEN(__x86_iob_empty_pageid = addr2pageid(ABSOLUTE(.)));
		PROVIDE_HIDDEN(__x86_iob_empty_pageptr = addr2pageptr(ABSOLUTE(.)));
		PROVIDE_HIDDEN(__x86_kernel_bss_before_iob_pages = ABSOLUTE(__x86_iob_empty_pageid - __kernel_bss_startpageid));
		STATIC_ASSERT((ABSOLUTE(.) & PAGEMASK) == 0);
		. += 8192; /* Make space for the IOBM table. */
		. += 1;    /* Trailing FFh-byte */
#endif /* !CONFIG_NO_SMP */

		/* The value stored in `thiscpu_x86_iob.t_iomap' */
		PROVIDE_HIDDEN(__x86_cputss_iob_offset = ABSOLUTE(thiscpu_x86_iob - thiscpu_x86_tss));

		IP_ALIGN(__ARCH_CACHELINESIZE);
		PROVIDE(_boottask = ABSOLUTE(.));
		. += __kernel_pertask_size;

		IP_ALIGN(PAGEDIR_ALIGN);
		PROVIDE(vm_kernel = ABSOLUTE(.));
		PROVIDE(pagedir_kernel = ABSOLUTE(.));
		PROVIDE(pagedir_kernel_phys = ABSOLUTE(pagedir_kernel) - KERNEL_CORE_BASE);
		. += PAGEDIR_SIZE;
		. += __kernel_pervm_size;

		PROVIDE_HIDDEN(__debug_malloc_tracked_end = ABSOLUTE(.));
		PROVIDE_HIDDEN(__debug_malloc_tracked_size = ABSOLUTE(ABSOLUTE(__debug_malloc_tracked_end) - ABSOLUTE(__debug_malloc_tracked_start)));

		PROVIDE_HIDDEN(kernel_membanks_initial = ABSOLUTE(.));
		IP_ALIGN(PAGESIZE);
		PROVIDE_HIDDEN(__kernel_boottask_stack_guard = ABSOLUTE(.));
		/* Insert a placeholder page to catch stack overflows */
		. += PAGESIZE;
		PROVIDE_HIDDEN(__kernel_boottask_stack = ABSOLUTE(.));
		PROVIDE_HIDDEN(__kernel_boottask_stack_pageid = addr2pageid(ABSOLUTE(.)));
		PROVIDE_HIDDEN(__kernel_boottask_stack_pageptr = addr2pageptr(ABSOLUTE(.)));
		. += KERNEL_STACKSIZE;

		IP_ALIGN(PAGESIZE);
		PROVIDE_HIDDEN(__kernel_bootidle_stack = ABSOLUTE(.));
		PROVIDE_HIDDEN(__kernel_bootidle_stack_pageid = addr2pageid(ABSOLUTE(.)));
		PROVIDE_HIDDEN(__kernel_bootidle_stack_pageptr = addr2pageptr(ABSOLUTE(.)));
		. += KERNEL_IDLE_STACKSIZE;

		IP_ALIGN(PAGESIZE);
		*(.bss.mall.untracked)

		IP_ALIGN(PAGESIZE);
		KEEP(*(.bss.x86.pagedir_kernel_share))
	}
	PROVIDE_HIDDEN(__kernel_sect_bss_size = ABSOLUTE(ABSOLUTE(.) - ABSOLUTE(__kernel_sect_bss_start)));

	IP_ALIGN(PAGESIZE);
	PROVIDE_HIDDEN(__kernel_bss_endpageid = addr2pageid(ABSOLUTE(.)));
	PROVIDE_HIDDEN(__kernel_bss_numpages = ABSOLUTE(ABSOLUTE(__kernel_bss_endpageid) - ABSOLUTE(__kernel_bss_startpageid)));
#ifndef CONFIG_NO_SMP
	PROVIDE_HIDDEN(__x86_kernel_bss_after_iob_pages = ABSOLUTE(__kernel_bss_endpageid - __x86_iob_empty_pageid));
#endif /* !CONFIG_NO_SMP */


	PROVIDE_HIDDEN(__kernel_free_start = ABSOLUTE(.));
	PROVIDE_HIDDEN(__kernel_free_startpageid = addr2pageid(ABSOLUTE(.)));
	PROVIDE_HIDDEN(__kernel_free_startpageptr = addr2pageptr(ABSOLUTE(.)));
	PROVIDE_HIDDEN(__kernel_size_nofree = ABSOLUTE(ABSOLUTE(__kernel_free_start) - ABSOLUTE(__kernel_start)));
	SECTION(.free) {
		/* A special section where data can go that will be unmapped, but have
		 * its physical backing memory not be freed once `.free' is deleted.
		 * This section is needed by x86_64's pageing initialization, or more
		 * specifically its `kernel_initialize_boot_trampolines()' function */
		KEEP(*(.free.unmap_but_keep_allocated))
		IP_ALIGN(PAGESIZE);
		/* Start of the page-free section. */
		PROVIDE_HIDDEN(__kernel_pfree_startpageptr = addr2pageptr(ABSOLUTE(.)));
		*(.text.free)

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

		*(.rodata.free)
		*(.rodata.str.free)
		*(.data.free)
		*(.bss.free)
		IP_ALIGN(PAGESIZE);
		PROVIDE_HIDDEN(__kernel_end = ABSOLUTE(.));
		/* TODO: Check if the outer `ABSOLUTE()' here is actually necessary (remove if it is not). */
		PROVIDE_HIDDEN(__kernel_size = ABSOLUTE(ABSOLUTE(__kernel_end) - ABSOLUTE(__kernel_start)));

		PROVIDE_HIDDEN(__kernel_pfree_endpageptr = addr2pageptr(ABSOLUTE(.)));
		PROVIDE_HIDDEN(__kernel_pfree_numpages = ABSOLUTE(ABSOLUTE(__kernel_pfree_endpageptr) - ABSOLUTE(__kernel_pfree_startpageptr)));

		PROVIDE_HIDDEN(__kernel_free_size = ABSOLUTE(ABSOLUTE(.) - ABSOLUTE(__kernel_free_start)));
		PROVIDE_HIDDEN(__kernel_free_endpageid = addr2pageid(ABSOLUTE(.)));
		PROVIDE_HIDDEN(__kernel_free_numpages = ABSOLUTE(ABSOLUTE(__kernel_free_endpageid) - ABSOLUTE(__kernel_free_startpageid)));
	}

	PROVIDE_HIDDEN(__x86_template_gdt = ABSOLUTE(__kernel_percpu_start + thiscpu_x86_gdt));
	PROVIDE_HIDDEN(__x86_bootcpu_dfstack_node = ABSOLUTE(_bootcpu + thiscpu_x86_dfstacknode));
	PROVIDE_HIDDEN(__x86_bootcpu_dfstack_part = ABSOLUTE(_bootcpu + thiscpu_x86_dfstackpart));
	PROVIDE_HIDDEN(__x86_bootcpu_df_stackpageid = addr2pageid(ABSOLUTE(__x86_bootcpu_df_stack)));
	PROVIDE_HIDDEN(__x86_bootcpu_df_stackpageptr = addr2pageptr(ABSOLUTE(__x86_bootcpu_df_stack)));
	PROVIDE(x86_bootcpu_cpufeatures = ABSOLUTE(_bootcpu + thiscpu_x86_cpufeatures));
	PROVIDE(x86_bootcpu_cpuid = ABSOLUTE(_bootcpu + thiscpu_x86_cpuid));
	PROVIDE(x86_bootcpu_gdt = ABSOLUTE(_bootcpu + thiscpu_x86_gdt));

#ifndef CONFIG_NO_BOOT0
	PROVIDE_HIDDEN(__kernel_sector_count = ABSOLUTE((__kernel_size + 511) / 512));
#endif /* !CONFIG_NO_BOOT0 */

#ifdef CONFIG_NO_SMP
#define TSS_BASE    thiscpu_x86_tss
#define TSS_DF_BASE thiscpu_x86_tssdf
#define LDT_BASE    thiscpu_x86_ldt
#else /* CONFIG_NO_SMP */
#define TSS_BASE    _bootcpu + thiscpu_x86_tss
#define TSS_DF_BASE _bootcpu + thiscpu_x86_tssdf
#define LDT_BASE    _bootcpu + thiscpu_x86_ldt
#endif /* !CONFIG_NO_SMP */

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
#ifndef CONFIG_X86_EMULATE_LCALL7
	DEFINE_SEGMENT_SYMBOLS(__x86_ldt_lcall7_main, CALLGATE, (x86_syscall32_lcall7, SEGMENT_KERNEL_CODE, SEGMENT_DESCRIPTOR_TYPE_CALLGATE, 0, 3, 1))
#endif /* !CONFIG_X86_EMULATE_LCALL7 */
	DEFINE_SEGMENT_SYMBOLS(__x86_gdt_tss_df, TSS, (TSS_DF_BASE, SIZEOF_TSS - 1, SEGMENT_DESCRIPTOR_TYPE_TSS_AVL, 0, 1, 0, 0))
	DEFINE_SEGMENT_SYMBOLS(__x86_gdt_kernel_tls, DESCRIPTOR, (_boottask, 0xfffff, SEGMENT_DESCRIPTOR_TYPE_DATA_RDWR, 1, 0, 1, 0, GDT_L, GDT_DB, 1))
#endif /* !__x86_64__ */
#undef DEFINE_SEGMENT_SYMBOLS
#undef GDT_DB
#undef GDT_L

	PROVIDE(thiscpu_idle_sched_state = ABSOLUTE(ABSOLUTE(thiscpu_idle) + ABSOLUTE(this_sched_state)));
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
	PROVIDE_HIDDEN(__x86_cputss_b0 = (ABSOLUTE(thiscpu_x86_tss) & 0x000000ff) >> 0);
	PROVIDE_HIDDEN(__x86_cputss_b1 = (ABSOLUTE(thiscpu_x86_tss) & 0x0000ff00) >> 8);
	PROVIDE_HIDDEN(__x86_cputss_b2 = (ABSOLUTE(thiscpu_x86_tss) & 0x00ff0000) >> 16);
	PROVIDE_HIDDEN(__x86_cputss_b3 = (ABSOLUTE(thiscpu_x86_tss) & 0xff000000) >> 24);
#endif /* !__x86_64__ */

#ifndef __x86_64__
#ifndef CONFIG_NO_PAGING_P32
	PROVIDE_HIDDEN(__x86_p32_identity_mapped_text_4mib_index = (ABSOLUTE(__x86_paging_init_identity_mapped_text) - KERNEL_CORE_BASE) / 0x400000);
	PROVIDE_HIDDEN(__x86_p32_identity_mapped_text_4mib_e2_word = ABSOLUTE(pagedir_kernel + (__x86_p32_identity_mapped_text_4mib_index * 4)));
	PROVIDE_HIDDEN(__x86_p32_identity_mapped_text_4mib_ks_share = ABSOLUTE((__x86_pagedir_kernel_share - KERNEL_CORE_BASE) + (__x86_p32_identity_mapped_text_4mib_index * 0x1000)));
#endif /* !CONFIG_NO_PAGING_P32 */
#endif /* !__x86_64__ */

#include "idt/idt.ld"
#ifndef CONFIG_NO_DEBUGGER
#define PREFIX x86_dbg
#include "idt/idt.ld"
#endif /* !CONFIG_NO_DEBUGGER */

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

#endif /* !GUARD_KERNEL_CORE_ARCH_I386__KERNEL_LD */
