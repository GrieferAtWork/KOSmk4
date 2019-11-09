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
#define _KOS_SOURCE 1
#define _KOS_KERNEL_SOURCE 1

#include <kernel/compiler.h>
#include <hybrid/limits.h>
#include <kernel/multiboot.h>
#include <kernel/paging.h>
#include <kos/kernel/gdt.h>
#include <kos/kernel/segment.h>
#include <kernel/gdt.h>
#include <kernel/idt.h>
#include <kernel/tss.h>

#undef likely
#undef unlikely

#define IP_ALIGN(x)  . = ALIGN(x)
#define SECTION(name) \
	name BLOCK(1) : AT(ADDR(name) - KERNEL_BASE)

#define PEROBJECT_SECTION_EX(section_name, name, base_offset, sections) \
	PROVIDE_HIDDEN(name##_start = ABSOLUTE(.));                         \
	. = ABSOLUTE(base_offset);                                          \
	section_name base_offset : AT(name##_start - KERNEL_BASE)           \
		sections                                                        \
	PROVIDE_HIDDEN(name##_size = ABSOLUTE(. - base_offset));            \
	. = ABSOLUTE(name##_start + name##_size);                           \
	PROVIDE_HIDDEN(name##_end = ABSOLUTE(.));
#define PEROBJECT_SECTION(section_name,name,sections) \
	PEROBJECT_SECTION_EX(section_name,name,0,sections)


ENTRY(_start)
SECTIONS {

	. = KERNEL_BASE + 0x100000;

	PROVIDE_HIDDEN(__kernel_start = ABSOLUTE(.));

#ifndef CONFIG_NO_BOOT0
	SECTION(.x86.boot0) {
		KEEP(*(.x86.boot0))
	}
	. = KERNEL_BASE + 0x100200;
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
	PROVIDE_HIDDEN(__kernel_text_startpage = ABSOLUTE(.) / PAGESIZE);
	SECTION(.text) {
		*(.text.hot .text.likely)
		*(.text .text._ZN*)
		*(.text.crt.*)
		*(.text.kernel.*)
		*(.text.cold .text.unlikely)
		*(.text.unlikely*)     /* Should be necessary, but prevents problems... */
		*(.text.x86.syscall.*) /* C-level implementations of system calls. */
#ifdef __x86_64__
		*(.text.x86.syscall32.*) /* C-level implementations of system calls (for compatibility mode). */
#endif /* __x86_64__ */
		KEEP(*(.text.x86.cirq.*))
		KEEP(*(.text.x86.asmirq.*))
		KEEP(*(.text.x86.asmisr.*))
#ifdef __x86_64__
		*(.text.x86.asm64_syscall.*)
#endif /* __x86_64__ */
		*(.text.x86.asm32_syscall_int80.*)
		*(.text.x86.asm32_syscall_sysenter.*)
	}

#define DEFINE_CALLBACK_VECTOR(name,section) \
		IP_ALIGN(__SIZEOF_POINTER__); \
		PROVIDE_HIDDEN(__kernel_##name##_start = ABSOLUTE(.)); \
		KEEP(*(section)) \
		PROVIDE_HIDDEN(__kernel_##name##_end = ABSOLUTE(.));


	IP_ALIGN(PAGESIZE);
	PROVIDE_HIDDEN(__kernel_sect_text_size = ABSOLUTE(ABSOLUTE(.) - ABSOLUTE(__kernel_sect_text_start)));
	PROVIDE_HIDDEN(__kernel_text_endpage = ABSOLUTE(.) / PAGESIZE);
	PROVIDE_HIDDEN(__kernel_text_numpages = ABSOLUTE(ABSOLUTE(__kernel_text_endpage) - ABSOLUTE(__kernel_text_startpage)));

	PROVIDE_HIDDEN(__kernel_sect_rodata_start = ABSOLUTE(.));
	PROVIDE_HIDDEN(__kernel_rodata_startpage = ABSOLUTE(.) / PAGESIZE);
	SECTION(.rodata) {
		*(.rodata.hot .rodata.likely)
		*(.rodata.x86.*)
		KEEP(*(.rodata.kernel_ld_elf))
		*(.rodata .rodata.kernel_symtab .rodata.cst*)
		*(.rodata.str* .rodata.*.str* .rodata.kernel_strtab)
		*(.rodata.cold .rodata.unlikely)
#ifndef CONFIG_NO_DEBUGGER
		*(.rodata.cold.debug_function_str)
		IP_ALIGN(__SIZEOF_POINTER__);
		PROVIDE_HIDDEN(__kernel_debug_functions_start = ABSOLUTE(.));
		KEEP(*(.rodata.cold.debug_functions))
		PROVIDE_HIDDEN(__kernel_debug_functions_end = ABSOLUTE(.));
		PROVIDE_HIDDEN(__kernel_debug_functions_size = ABSOLUTE(ABSOLUTE(__kernel_debug_functions_end) - ABSOLUTE(__kernel_debug_functions_start)));
		DEFINE_CALLBACK_VECTOR(dbg_init,.rodata.cold.callback.dbg_init)
		DEFINE_CALLBACK_VECTOR(dbg_reset,.rodata.cold.callback.dbg_reset)
		DEFINE_CALLBACK_VECTOR(dbg_fini,.rodata.cold.callback.dbg_fini)
#endif /* !CONFIG_NO_DEBUGGER */
		DEFINE_CALLBACK_VECTOR(system_clearcaches,.rodata.cold.callback.system_clearcaches)

		DEFINE_CALLBACK_VECTOR(idle_job,.rodata.callback.idle_job)
		DEFINE_CALLBACK_VECTOR(pertask_init,.rodata.callback.pertask.init)
		DEFINE_CALLBACK_VECTOR(pertask_fini,.rodata.callback.pertask.fini)
		DEFINE_CALLBACK_VECTOR(pertask_clone,.rodata.callback.pertask.clone)
		DEFINE_CALLBACK_VECTOR(pertask_onexit,.rodata.callback.pertask.onexit)
		DEFINE_CALLBACK_VECTOR(pervm_init,.rodata.callback.pervm.init)
		DEFINE_CALLBACK_VECTOR(pervm_fini,.rodata.callback.pervm.fini)
		DEFINE_CALLBACK_VECTOR(pervm_clone,.rodata.callback.pervm.clone)
		DEFINE_CALLBACK_VECTOR(pervm_onexec,.rodata.callback.pervm.onexec)
		DEFINE_CALLBACK_VECTOR(validatable_heaps,.rodata.heaps.validatable)
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
	section_name 0 : AT(name##_start - KERNEL_BASE) {                                      \
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

#define DEFINE_DEBUG_SECTION_WRAPPER(name)                                    \
	PROVIDE_HIDDEN(__wrapper_##name##_start = ABSOLUTE(.));                   \
	. = ABSOLUTE(0);                                                          \
	.name.wrapper 0 : AT(__wrapper_##name##_start - KERNEL_BASE) { BYTE(0); } \
	. += ABSOLUTE(__wrapper_##name##_start);
	DEFINE_DEBUG_SECTION_WRAPPER(debug_line)
	DEFINE_DEBUG_SECTION_WRAPPER(debug_info)
	DEFINE_DEBUG_SECTION_WRAPPER(debug_aranges)
	DEFINE_DEBUG_SECTION_WRAPPER(debug_abbrev)
	DEFINE_DEBUG_SECTION_WRAPPER(debug_str)
	DEFINE_DEBUG_SECTION_WRAPPER(debug_ranges)
	DEFINE_DEBUG_SECTION_WRAPPER(debug_loc)
#undef DEFINE_DEBUG_SECTION_WRAPPER

	IP_ALIGN(__SIZEOF_CACHELINE__);
	PEROBJECT_SECTION(.pertask, __kernel_pertask, {
		KEEP(*(.data.pertask.head))
		KEEP(*(.data.pertask.early))
		KEEP(*(.data.pertask))
	})

	IP_ALIGN(__SIZEOF_CACHELINE__);
	PEROBJECT_SECTION_EX(.pervm, __kernel_pervm, PAGEDIR_SIZE, {
		KEEP(*(.data.pervm.head))
		KEEP(*(.data.pervm))
	})

#ifndef CONFIG_NO_SMP
	IP_ALIGN(__SIZEOF_CACHELINE__);
	PEROBJECT_SECTION(.percpu, __kernel_percpu, {
		KEEP(*(.data.percpu.head))
		KEEP(*(.data.percpu))
		IP_ALIGN(__SIZEOF_CACHELINE__);
		PROVIDE(_this_idle = ABSOLUTE(.));
		. += __kernel_pertask_size;
	})
#endif /* !CONFIG_NO_SMP */

	IP_ALIGN(PAGESIZE);
	PROVIDE_HIDDEN(__kernel_rodata_end = ABSOLUTE(.));
	PROVIDE_HIDDEN(__kernel_rodata_size = ABSOLUTE(ABSOLUTE(__kernel_rodata_end) - ABSOLUTE(__kernel_start)));
	PROVIDE_HIDDEN(__kernel_rodata_endpage = ABSOLUTE(.) / PAGESIZE);
	PROVIDE_HIDDEN(__kernel_rodata_numpages = ABSOLUTE(ABSOLUTE(__kernel_rodata_endpage) - ABSOLUTE(__kernel_rodata_startpage)));

	PROVIDE_HIDDEN(__debug_malloc_tracked_start = ABSOLUTE(.));
	PROVIDE_HIDDEN(__kernel_sect_data_start = ABSOLUTE(.));
	PROVIDE_HIDDEN(__kernel_data_startpage = ABSOLUTE(.) / PAGESIZE);
	SECTION(.data) {

		IP_ALIGN(__SIZEOF_CACHELINE__);
		*(.data.hot.read_mostly)
		*(.data.hot.read_mostly.tail)

		IP_ALIGN(__SIZEOF_CACHELINE__);
		*(.data.hot.write_mostly)
		*(.data.hot.write_mostly.tail)

		*(.data.hot .data.likely)
		*(.data)
		*(.data.cold)
		*(.data.unlikely)
		*(.data.local.*)

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

		IP_ALIGN(__SIZEOF_POINTER__);
		PROVIDE(x86_idt_start = ABSOLUTE(.));
		/* Use the linker to generate our IDT table.
		 * This way, we don't have to keep a table of pointers
		 * that we'd otherwise need to convert at runtime! */
#include "interrupt.ld"

#ifndef CONFIG_NO_SYSCALL_TRACING
		IP_ALIGN(__SIZEOF_POINTER__);
		PROVIDE(x86_idt_start_traced = ABSOLUTE(.));
#define WITH_SYSCALL_TRACING_ENABLED 1
#include "interrupt.ld"
#undef WITH_SYSCALL_TRACING_ENABLED
#endif /* !CONFIG_NO_SYSCALL_TRACING */

#ifndef CONFIG_NO_DEBUGGER
		IP_ALIGN(__SIZEOF_POINTER__);
		PROVIDE(x86_idt_start_debug = ABSOLUTE(.));
		/* Use the linker to generate our IDT table.
		 * This way, we don't have to keep a table of pointers
		 * that we'd otherwise need to convert at runtime! */
#include "debugger/interrupt.ld"
#endif /* !CONFIG_NO_DEBUGGER */

#ifdef CONFIG_NO_SMP
		IP_ALIGN(__SIZEOF_CACHELINE__);
		PROVIDE_HIDDEN(__kernel_percpu_start = ABSOLUTE(.));
		PROVIDE(_bootcpu = ABSOLUTE(.));
		KEEP(*(.data.percpu.head))
		KEEP(*(.data.percpu))
		IP_ALIGN(__SIZEOF_CACHELINE__);
		PROVIDE(_bootidle = ABSOLUTE(.));
		PROVIDE(_this_idle = ABSOLUTE(.));
		. += __kernel_pertask_size;
		PROVIDE_HIDDEN(__kernel_percpu_end = ABSOLUTE(.));
		PROVIDE_HIDDEN(__kernel_percpu_size = ABSOLUTE(ABSOLUTE(__kernel_percpu_end) - ABSOLUTE(__kernel_percpu_start)));
#endif /* !CONFIG_NO_SMP */

		IP_ALIGN(PAGESIZE);
		PROVIDE_HIDDEN(__kernel_data_endpage = ABSOLUTE(.) / PAGESIZE);
		PROVIDE_HIDDEN(__kernel_data_numpages = ABSOLUTE(ABSOLUTE(__kernel_data_endpage) - ABSOLUTE(__kernel_data_startpage)));

		PROVIDE_HIDDEN(__kernel_xdata_startpage = ABSOLUTE(.) / PAGESIZE);
		/* PDATA: Memory that remains mapping at VADDR=PADDR within the kernel VM.
		 *        Note however that this memory is linked by its virtual address! */
		PROVIDE_HIDDEN(__kernel_pdata_startpage = ABSOLUTE(.) / PAGESIZE);
		KEEP(*(.text.pdata.hot .pdata.hot .text.pdata.likely .pdata.likely))
		KEEP(*(.text.pdata .pdata))
		KEEP(*(.text.pdata.cold .pdata.cold .text.pdata.unlikely .pdata.unlikely))
		PROVIDE_HIDDEN(__kernel_pdata_endpage = ABSOLUTE(ALIGN(PAGESIZE)) / PAGESIZE);
		PROVIDE_HIDDEN(__kernel_pdata_numpages = ABSOLUTE(ABSOLUTE(__kernel_pdata_endpage) - ABSOLUTE(__kernel_pdata_startpage)));

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
		*(.xbss.hot .xbss.likely)
		*(.xbss)
		*(.xbss.cold .xbss.unlikely)
		IP_ALIGN(PAGESIZE);
		PROVIDE_HIDDEN(__kernel_xdata_endpage = ABSOLUTE(.) / PAGESIZE);
		PROVIDE_HIDDEN(__kernel_xdata_numpages = ABSOLUTE(ABSOLUTE(__kernel_xdata_endpage) - ABSOLUTE(__kernel_xdata_startpage)));

		PROVIDE_HIDDEN(__kernel_bss_startpage = ABSOLUTE(.) / PAGESIZE);
		*(.bss.hot .bss.likely)
		*(.bss)
		*(.bss.cold .bss.unlikely)

		/* Boot CPU/TASK/VM data. */
#ifndef CONFIG_NO_SMP
		PROVIDE(_bootcpu = ABSOLUTE(.));
		. += __kernel_percpu_size - __kernel_pertask_size;
		PROVIDE(_bootidle = ABSOLUTE(.));
		. += __kernel_pertask_size;
#endif /* !CONFIG_NO_SMP */

		PROVIDE(_boottask = ABSOLUTE(.));
		. += __kernel_pertask_size;

		IP_ALIGN(PAGEDIR_ALIGN);
		PROVIDE(vm_kernel = ABSOLUTE(.));
		PROVIDE(pagedir_kernel = ABSOLUTE(.));
		PROVIDE(pagedir_kernel_phys = ABSOLUTE(pagedir_kernel) - KERNEL_BASE);
		. += PAGEDIR_SIZE;
		. += __kernel_pervm_size;

		PROVIDE_HIDDEN(__debug_malloc_tracked_end = ABSOLUTE(.));
		PROVIDE_HIDDEN(__debug_malloc_tracked_size = ABSOLUTE(ABSOLUTE(__debug_malloc_tracked_end) - ABSOLUTE(__debug_malloc_tracked_start)));

		PROVIDE_HIDDEN(kernel_membanks_initial = ABSOLUTE(.));
		IP_ALIGN(PAGESIZE);
		PROVIDE_HIDDEN(__kernel_boottask_stack_guard = ABSOLUTE(ABSOLUTE(.) / PAGESIZE));
		/* Insert a placeholder page to catch stack overflows */
		. += PAGESIZE;
		PROVIDE_HIDDEN(__kernel_boottask_stack = ABSOLUTE(.));
		PROVIDE_HIDDEN(__kernel_boottask_stack_page = ABSOLUTE(ABSOLUTE(.) / PAGESIZE));
		. += KERNEL_STACKSIZE;

		IP_ALIGN(PAGESIZE);
		PROVIDE_HIDDEN(__kernel_bootidle_stack = ABSOLUTE(.));
		PROVIDE_HIDDEN(__kernel_bootidle_stack_page = ABSOLUTE(ABSOLUTE(.) / PAGESIZE));
		. += KERNEL_IDLE_STACKSIZE;


#ifndef CONFIG_NO_DEBUGGER
		IP_ALIGN(PAGESIZE);
		PROVIDE_HIDDEN(__kernel_debug_stack = ABSOLUTE(.));
		PROVIDE_HIDDEN(__kernel_debug_stack_page = ABSOLUTE(ABSOLUTE(.) / PAGESIZE));
		. += KERNEL_DEBUG_STACKSIZE;
#endif /* !CONFIG_NO_DEBUGGER */

		*(.bss.mall.untracked)

		IP_ALIGN(PAGESIZE);
		KEEP(*(.bss.x86.pagedir_kernel_share))
	}
	PROVIDE_HIDDEN(__kernel_sect_bss_size = ABSOLUTE(ABSOLUTE(.) - ABSOLUTE(__kernel_sect_bss_start)));

	IP_ALIGN(PAGESIZE);
	PROVIDE_HIDDEN(__kernel_bss_endpage = ABSOLUTE(.) / PAGESIZE);
	PROVIDE_HIDDEN(__kernel_bss_numpages = ABSOLUTE(ABSOLUTE(__kernel_bss_endpage) - ABSOLUTE(__kernel_bss_startpage)));
	PROVIDE_HIDDEN(__kernel_free_start = ABSOLUTE(.));
	PROVIDE_HIDDEN(__kernel_free_startpage = ABSOLUTE(.) / PAGESIZE);
	PROVIDE_HIDDEN(__kernel_size_nofree = ABSOLUTE(ABSOLUTE(__kernel_free_start) - ABSOLUTE(__kernel_start)));
	SECTION(.free) {
		/* A special section where data can go that will be unmapped, but have
		 * its physical backing memory not be freed once `.free' is deleted.
		 * This section is needed by x86_64's pageing initialization, or more
		 * specifically its `kernel_initialize_boot_trampolines()' function */
		KEEP(*(.free.unmap_but_keep_allocated))
		IP_ALIGN(PAGESIZE);
		PROVIDE_HIDDEN(__kernel_pfree_startpage = ABSOLUTE(.) / PAGESIZE);
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
		PROVIDE_HIDDEN(__x86_64_fixup_fsgsbase_start = ABSOLUTE(.));
		KEEP(*(.rodata.fixup.fsgsbase.free))
		PROVIDE_HIDDEN(__x86_64_fixup_fsgsbase_end = ABSOLUTE(.));
#endif /* __x86_64__ */

		*(.rodata.free)
		*(.rodata.str.free)
		*(.data.free)
		*(.bss.free)
		IP_ALIGN(PAGESIZE);
		PROVIDE_HIDDEN(__kernel_end = ABSOLUTE(.));
		/* TODO: Check if the outer `ABSOLUTE()' here is actually necessary (remove if it is not). */
		PROVIDE_HIDDEN(__kernel_size = ABSOLUTE(ABSOLUTE(__kernel_end) - ABSOLUTE(__kernel_start)));

		PROVIDE_HIDDEN(__kernel_pfree_endpage = ABSOLUTE(.) / PAGESIZE);
		PROVIDE_HIDDEN(__kernel_pfree_numpages = ABSOLUTE(ABSOLUTE(__kernel_pfree_endpage) - ABSOLUTE(__kernel_pfree_startpage)));

		PROVIDE_HIDDEN(__kernel_free_size = ABSOLUTE(ABSOLUTE(.) - ABSOLUTE(__kernel_free_start)));
		PROVIDE_HIDDEN(__kernel_free_endpage = ABSOLUTE(.) / PAGESIZE);
		PROVIDE_HIDDEN(__kernel_free_numpages = ABSOLUTE(ABSOLUTE(__kernel_free_endpage) - ABSOLUTE(__kernel_free_startpage)));
	}

	PROVIDE(jiffies = ABSOLUTE(_bootcpu + cpu_jiffies));

	PROVIDE_HIDDEN(__x86_template_gdt = ABSOLUTE(__kernel_percpu_start + x86_cpugdt));
	PROVIDE_HIDDEN(__x86_bootcpu_dfstack_node = ABSOLUTE(_bootcpu + x86_this_dfstack));
	PROVIDE_HIDDEN(__x86_bootcpu_dfstack_part = ABSOLUTE(_bootcpu + x86_this_dfstack_part));
	PROVIDE_HIDDEN(__x86_bootcpu_df_stackpage = ABSOLUTE(__x86_bootcpu_df_stack / PAGESIZE));
	PROVIDE(__x86_bootcpu_features = ABSOLUTE(_bootcpu + cpu_features));
	PROVIDE(__x86_bootcpu_idfeatures = ABSOLUTE(_bootcpu + cpuid_features));
	PROVIDE(__x86_bootcpu_gdt = ABSOLUTE(_bootcpu + x86_cpugdt));

#ifndef CONFIG_NO_BOOT0
	PROVIDE_HIDDEN(__kernel_sector_count = ABSOLUTE((__kernel_size + 511) / 512));
#endif /* !CONFIG_NO_BOOT0 */

#ifdef CONFIG_NO_SMP
#define TSS_BASE    x86_cputss
#define TSS_DF_BASE x86_cputss_df
#define LDT_BASE    x86_cpuldt
#else /* CONFIG_NO_SMP */
#define TSS_BASE    _bootcpu + x86_cputss
#define TSS_DF_BASE _bootcpu + x86_cputss_df
#define LDT_BASE    _bootcpu + x86_cpuldt
#endif /* !CONFIG_NO_SMP */

	/* Pre-calculate TSS and TLS segment initializers. */
#ifdef __x86_64__
#define GDT_L 1
#define DEFINE_SEGMENT_SYMBOLS(name, TYPE, args) \
	PROVIDE_HIDDEN(name##_lo = SEGMENT_##TYPE##_INIT_U    args); \
	PROVIDE_HIDDEN(name##_hi = SEGMENT_##TYPE##_HI_INIT_U args);
#else /* __x86_64__ */
#define GDT_L 0
#define DEFINE_SEGMENT_SYMBOLS(name, TYPE, args) \
	PROVIDE_HIDDEN(name##_lo = SEGMENT_##TYPE##_INIT_UL args); \
	PROVIDE_HIDDEN(name##_hi = SEGMENT_##TYPE##_INIT_UH args);
#endif /* !__x86_64__ */
	DEFINE_SEGMENT_SYMBOLS(__x86_gdt_tss, TSS, (TSS_BASE, SIZEOF_TSS - 1, SEGMENT_DESCRIPTOR_TYPE_TSS_AVL, 0, 1, 0, 0))
	DEFINE_SEGMENT_SYMBOLS(__x86_gdt_ldt, LDT, (LDT_BASE, (LDT_SEGMENT_COUNT * SIZEOF_SEGMENT_DESCRIPTOR) - 1, 3, 1, 0, 0))
#ifndef __x86_64__
	DEFINE_SEGMENT_SYMBOLS(__x86_ldt_lcall7_main, CALLGATE, (x86_lcall7_main, SEGMENT_KERNEL_CODE, SEGMENT_DESCRIPTOR_TYPE_CALLGATE, 0, 3, 1))
	DEFINE_SEGMENT_SYMBOLS(__x86_gdt_tss_df, TSS, (TSS_DF_BASE, SIZEOF_TSS - 1, SEGMENT_DESCRIPTOR_TYPE_TSS_AVL, 0, 1, 0, 0))
	DEFINE_SEGMENT_SYMBOLS(__x86_gdt_kernel_tls, DESCRIPTOR, (_boottask, 0xfffff, SEGMENT_DESCRIPTOR_TYPE_DATA_RDWR, 1, 0, 1, 0, GDT_L, 1, 1))
#else /* !__x86_64__ */
	DEFINE_SEGMENT_SYMBOLS(__x86_ldt_lcall7_main, CALLGATE, (x86_lcall7_main, SEGMENT_KERNEL_CODE, SEGMENT_DESCRIPTOR_TYPE_CALLGATE, 3, 1))
#endif /* __x86_64__ */
#undef DEFINE_SEGMENT_SYMBOLS
#undef GDT_L

	PROVIDE_HIDDEN(__x86_kernel_ld_elf_startpage = ABSOLUTE(kernel_ld_elf) / PAGESIZE);
	PROVIDE_HIDDEN(__x86_kernel_ld_elf_numpages  = ABSOLUTE(__x86_kernel_ld_elf_size) / PAGESIZE);
	PROVIDE_HIDDEN(_this_idle_sched_state = ABSOLUTE(ABSOLUTE(_this_idle) + ABSOLUTE(_this_sched_state)));
	PROVIDE_HIDDEN(_this_idle_x86_this_kernel_sp0 = ABSOLUTE(ABSOLUTE(_this_idle) + ABSOLUTE(x86_this_kernel_sp0)));

	PROVIDE_HIDDEN(__x86_dbg_cpu_temporary_b0 = (ABSOLUTE(dbg_cpu_temporary) & 0x000000ff) >> 0);
	PROVIDE_HIDDEN(__x86_dbg_cpu_temporary_b1 = (ABSOLUTE(dbg_cpu_temporary) & 0x0000ff00) >> 8);
	PROVIDE_HIDDEN(__x86_dbg_cpu_temporary_b2 = (ABSOLUTE(dbg_cpu_temporary) & 0x00ff0000) >> 16);
	PROVIDE_HIDDEN(__x86_dbg_cpu_temporary_b3 = (ABSOLUTE(dbg_cpu_temporary) & 0xff000000) >> 24);
	PROVIDE_HIDDEN(__x86_dbg_exitstate_temporary_b0 = (ABSOLUTE(dbg_exitstate) & 0x000000ff) >> 0);
	PROVIDE_HIDDEN(__x86_dbg_exitstate_temporary_b1 = (ABSOLUTE(dbg_exitstate) & 0x0000ff00) >> 8);
	PROVIDE_HIDDEN(__x86_dbg_exitstate_temporary_b2 = (ABSOLUTE(dbg_exitstate) & 0x00ff0000) >> 16);
	PROVIDE_HIDDEN(__x86_dbg_exitstate_temporary_b3 = (ABSOLUTE(dbg_exitstate) & 0xff000000) >> 24);

	PROVIDE_HIDDEN(__x86_cputss_b0 = (ABSOLUTE(x86_cputss) & 0x000000ff) >> 0);
	PROVIDE_HIDDEN(__x86_cputss_b1 = (ABSOLUTE(x86_cputss) & 0x0000ff00) >> 8);
	PROVIDE_HIDDEN(__x86_cputss_b2 = (ABSOLUTE(x86_cputss) & 0x00ff0000) >> 16);
	PROVIDE_HIDDEN(__x86_cputss_b3 = (ABSOLUTE(x86_cputss) & 0xff000000) >> 24);

#ifndef __x86_64__
#ifndef CONFIG_NO_PAGING_P32
	PROVIDE_HIDDEN(__x86_p32_identity_mapped_text_4mib_index = (ABSOLUTE(__x86_paging_init_identity_mapped_text) - KERNEL_BASE) / 0x400000);
	PROVIDE_HIDDEN(__x86_p32_identity_mapped_text_4mib_e2_word = ABSOLUTE(pagedir_kernel + (__x86_p32_identity_mapped_text_4mib_index * 4)));
	PROVIDE_HIDDEN(__x86_p32_identity_mapped_text_4mib_ks_share = ABSOLUTE((__x86_pagedir_kernel_share - KERNEL_BASE) + (__x86_p32_identity_mapped_text_4mib_index * 0x1000)));
#endif /* !CONFIG_NO_PAGING_P32 */
#endif /* !__x86_64__ */



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
