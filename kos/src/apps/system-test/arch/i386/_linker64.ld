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
#ifndef GUARD_APPS_SYSTEM_TEST_ARCH_I386__LINKER64_LD
#define GUARD_APPS_SYSTEM_TEST_ARCH_I386__LINKER64_LD 1

#include <hybrid/typecore.h>

ENTRY(_start)
SECTIONS {
	PROVIDE(__executable_start = SEGMENT_START("text-segment", 0x400000));
	. = SEGMENT_START("text-segment", 0x400000) + SIZEOF_HEADERS;
	.interp : { *(.interp) }
	.note.gnu.build-id : { *(.note.gnu.build-id) }
	.hash : { *(.hash) }
	.gnu.hash : { *(.gnu.hash) }
	.dynsym : { *(.dynsym) }
	.dynstr : { *(.dynstr) }
	.gnu.version : { *(.gnu.version) }
	.gnu.version_d : { *(.gnu.version_d) }
	.gnu.version_r : { *(.gnu.version_r) }
	.rela.dyn : {
		*(.rela.init)
		*(.rela.text .rela.text.* .rela.gnu.linkonce.t.*)
		*(.rela.fini)
		*(.rela.rodata .rela.rodata.* .rela.gnu.linkonce.r.*)
		*(.rela.data .rela.data.* .rela.gnu.linkonce.d.*)
		*(.rela.tdata .rela.tdata.* .rela.gnu.linkonce.td.*)
		*(.rela.tbss .rela.tbss.* .rela.gnu.linkonce.tb.*)
		*(.rela.ctors)
		*(.rela.dtors)
		*(.rela.got)
		*(.rela.bss .rela.bss.* .rela.gnu.linkonce.b.*)
		*(.rela.ldata .rela.ldata.* .rela.gnu.linkonce.l.*)
		*(.rela.lbss .rela.lbss.* .rela.gnu.linkonce.lb.*)
		*(.rela.lrodata .rela.lrodata.* .rela.gnu.linkonce.lr.*)
		*(.rela.ifunc)
	}
	.rela.plt : {
		*(.rela.plt)
		PROVIDE_HIDDEN(__rela_iplt_start = .);
		*(.rela.iplt)
		PROVIDE_HIDDEN(__rela_iplt_end = .);
	}
	.init : {
		KEEP(*(SORT_NONE(.init)))
	}
	.plt : { *(.plt) *(.iplt) }
	lt.got : { *(.plt.got) }
	lt.sec : { *(.plt.sec) }
	.text : {
		*(.text.unlikely .text.*_unlikely .text.unlikely.*)
		*(.text.exit .text.exit.*)
		*(.text.startup .text.startup.*)
		*(.text.hot .text.hot.*)
		*(.text .stub .text.* .gnu.linkonce.t.*)
		*(.gnu.warning)
	}
	.fini : {
		KEEP(*(SORT_NONE(.fini)))
	}
	PROVIDE(__etext = .);
	PROVIDE(_etext = .);
	PROVIDE(etext = .);
	.xdata : {
		*(.xdata.unlikely .xdata.*_unlikely .xdata.unlikely.*)
		*(.xdata.exit .xdata.exit.*)
		*(.xdata.startup .xdata.startup.*)
		*(.xdata.hot .xdata.hot.*)
		*(.xdata  .xdata.*)
	}
	.rodata : { *(.rodata .rodata.* .gnu.linkonce.r.*) }
	.rodata1 : { *(.rodata1) }
	.eh_frame_hdr : { *(.eh_frame_hdr) *(.eh_frame_entry .eh_frame_entry.*) }
	.eh_frame : ONLY_IF_RO { KEEP(*(.eh_frame)) *(.eh_frame.*) }
	.gcc_except_table : ONLY_IF_RO { *(.gcc_except_table .gcc_except_table.*) }
	.gnu_extab : ONLY_IF_RO { *(.gnu_extab*) }
	.exception_ranges : ONLY_IF_RO { *(.exception_ranges*) }
	. = DATA_SEGMENT_ALIGN(CONSTANT(MAXPAGESIZE), CONSTANT(COMMONPAGESIZE));
	.eh_frame : ONLY_IF_RW { KEEP(*(.eh_frame)) *(.eh_frame.*) }
	.gnu_extab : ONLY_IF_RW { *(.gnu_extab) }
	.gcc_except_table : ONLY_IF_RW { *(.gcc_except_table .gcc_except_table.*) }
	.exception_ranges : ONLY_IF_RW { *(.exception_ranges*) }
	.tdata : {
		PROVIDE_HIDDEN(__tdata_start = .);
		*(.tdata .tdata.* .gnu.linkonce.td.*)
	}
	.tbss : { *(.tbss .tbss.* .gnu.linkonce.tb.*) *(.tcommon) }
	.preinit_array : {
		PROVIDE_HIDDEN(__preinit_array_start = .);
		KEEP(*(.preinit_array))
		PROVIDE_HIDDEN(__preinit_array_end = .);
	}
	.init_array : {
		PROVIDE_HIDDEN(__init_array_start = .);
		KEEP(*(SORT_BY_INIT_PRIORITY(.init_array.*) SORT_BY_INIT_PRIORITY(.ctors.*)))
		KEEP(*(.init_array EXCLUDE_FILE(*crtbegin.o *crtbegin?.o *crtend.o *crtend?.o ) .ctors))
		PROVIDE_HIDDEN(__init_array_end = .);
	}
	.fini_array : {
		PROVIDE_HIDDEN(__fini_array_start = .);
		KEEP(*(SORT_BY_INIT_PRIORITY(.fini_array.*) SORT_BY_INIT_PRIORITY(.dtors.*)))
		KEEP(*(.fini_array EXCLUDE_FILE(*crtbegin.o *crtbegin?.o *crtend.o *crtend?.o ) .dtors))
		PROVIDE_HIDDEN(__fini_array_end = .);
	}
	.ctors : {
		KEEP(*crtbegin.o(.ctors))
		KEEP(*crtbegin?.o(.ctors))
		KEEP(*(EXCLUDE_FILE(*crtend.o *crtend?.o ) .ctors))
		KEEP(*(SORT(.ctors.*)))
		KEEP(*(.ctors))
	}
	.dtors : {
		KEEP(*crtbegin.o(.dtors))
		KEEP(*crtbegin?.o(.dtors))
		KEEP(*(EXCLUDE_FILE(*crtend.o *crtend?.o ) .dtors))
		KEEP(*(SORT(.dtors.*)))
		KEEP(*(.dtors))
	}
	.jcr : { KEEP(*(.jcr)) }
	.data.rel.ro : { *(.data.rel.ro.local* .gnu.linkonce.d.rel.ro.local.*) *(.data.rel.ro .data.rel.ro.* .gnu.linkonce.d.rel.ro.*) }
	.dynamic : { *(.dynamic) }
	.got : { *(.got) *(.igot) }
	. = DATA_SEGMENT_RELRO_END(SIZEOF(.got.plt) >= 24 ? 24 : 0, .);
	.got.plt : { *(.got.plt) *(.igot.plt) }
	.data : {
		. = ALIGN(__SIZEOF_POINTER__);
		PROVIDE_HIDDEN(__system_tests_begin = .);
		KEEP(*(.data.system_tests))
		PROVIDE_HIDDEN(__system_tests_end = .);

		*(.data .data.* .gnu.linkonce.d.*)
		SORT(CONSTRUCTORS)
	}
	.data1 : { *(.data1) }
	_edata = .; PROVIDE(edata = .);
	. = .;
	__bss_start = .;
	.bss : {
		*(.dynbss)
		*(.bss .bss.* .gnu.linkonce.b.*)
		*(COMMON)
		. = ALIGN(. != 0 ? 64 / 8 : 1);
	}
	.lbss : {
		*(.dynlbss)
		*(.lbss .lbss.* .gnu.linkonce.lb.*)
		*(LARGE_COMMON)
	}
	. = ALIGN(64 / 8);
	. = SEGMENT_START("ldata-segment", .);
	.lrodata   ALIGN(CONSTANT(MAXPAGESIZE)) +(. &(CONSTANT(MAXPAGESIZE) - 1)) :
	{
	  *(.lrodata .lrodata.* .gnu.linkonce.lr.*)
	}
	.ldata   ALIGN(CONSTANT(MAXPAGESIZE)) +(. &(CONSTANT(MAXPAGESIZE) - 1)) :
	{
	  *(.ldata .ldata.* .gnu.linkonce.l.*)
	  . = ALIGN(. != 0 ? 64 / 8 : 1);
	}
	. = ALIGN(64 / 8);
	_end = .; PROVIDE(end = .);
	. = DATA_SEGMENT_END(.);
	/* Stabs debugging sections.  */
	.stab          0 : { *(.stab) }
	.stabstr       0 : { *(.stabstr) }
	.stab.excl     0 : { *(.stab.excl) }
	.stab.exclstr  0 : { *(.stab.exclstr) }
	.stab.index    0 : { *(.stab.index) }
	.stab.indexstr 0 : { *(.stab.indexstr) }
	.comment       0 : { *(.comment) }
	.gnu.build.attributes : { *(.gnu.build.attributes .gnu.build.attributes.*) }
	.debug          0 : { *(.debug) }
	.line           0 : { *(.line) }
	.debug_srcinfo  0 : { *(.debug_srcinfo) }
	.debug_sfnames  0 : { *(.debug_sfnames) }
	.debug_aranges  0 : { *(.debug_aranges) }
	.debug_pubnames 0 : { *(.debug_pubnames) }
	.debug_info     0 : { *(.debug_info .gnu.linkonce.wi.*) }
	.debug_abbrev   0 : { *(.debug_abbrev) }
	.debug_line     0 : { *(.debug_line .debug_line.* .debug_line_end) }
	.debug_frame    0 : { *(.debug_frame) }
	.debug_str      0 : { *(.debug_str) }
	.debug_line_str 0 : { *(.debug_line_str) }
	.debug_loclists 0 : { *(.debug_loclists) }
	.debug_macinfo  0 : { *(.debug_macinfo) }
	.debug_weaknames 0 : { *(.debug_weaknames) }
	.debug_funcnames 0 : { *(.debug_funcnames) }
	.debug_typenames 0 : { *(.debug_typenames) }
	.debug_varnames  0 : { *(.debug_varnames) }
	.debug_pubtypes 0 : { *(.debug_pubtypes) }
	.debug_rnglists 0 : { *(.debug_rnglists) }
	.debug_macro    0 : { *(.debug_macro) }
	.debug_addr     0 : { *(.debug_addr) }
	.gnu.attributes 0 : { KEEP(*(.gnu.attributes)) }
	/DISCARD/ : { *(.note.GNU-stack) *(.gnu_debuglink) *(.gnu.lto_*) }
}

#endif /* !GUARD_APPS_SYSTEM_TEST_ARCH_I386__LINKER64_LD */
