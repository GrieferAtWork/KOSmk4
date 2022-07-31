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
#ifndef GUARD_LIBDL__RTLD_LD
#define GUARD_LIBDL__RTLD_LD 1

#include <hybrid/compiler.h>

#include <hybrid/host.h>

#include <asm/pagesize.h>

/* clang-format off */

#if 0
#define PHDR(x)
#else
PHDRS {
	/* s.a. `.sources:OPT_ELF_FLATTEN_ALLOWED_HEADERS' for program headers that are kept. */
	text    PT_LOAD;    /* Kept during flattening */
	data    PT_LOAD;    /* Kept during flattening */
	rel     PT_LOAD;    /* Discarded during flattening */
	dynamic PT_DYNAMIC; /* Discarded during flattening */
}
#define PHDR(x) :x
#endif

#undef likely
#undef unlikely

#if defined(__i386__) || defined(__x86_64__)
#define OPT_TEXT_X86 .text.__x86.*
#endif /* __i386__ || __x86_64__ */


#ifndef OPT_TEXT_X86
#define OPT_TEXT_X86 /* nothing */
#endif /* !OPT_TEXT_X86 */


ENTRY(linker_entry)
SECTIONS {

	. = 0;

	.text BLOCK(1) : {
		PROVIDE_HIDDEN(__rtld_start = .);
		PROVIDE_HIDDEN(__rtld_text_start = .);
		*(.text.linker_entry)
		*(.text.hot .text.hot.* .text.likely .text.likely.*)
		*(OPT_TEXT_X86 .text .text.local.*)
		*(.text.cold .text.cold.* .text.unlikely .text.unlikely.*)
		*(.text.*)
		PROVIDE_HIDDEN(__rtld_text_end = .);
	} PHDR(text)

	.rodata BLOCK(1) : {
		PROVIDE_HIDDEN(__rtld_rodata_start = .);
		*(.rodata.hot .rodata.hot.* .rodata.likely .rodata.likely.*)
		*(.rodata .rodata.str* .rodata.cst* .rodata.*.str* .rodata.*.cst* .rodata.local.*)
		*(.rodata.cold .rodata.cold.* .rodata.unlikely .rodata.unlikely.*)
		*(.rodata.*)
		PROVIDE_HIDDEN(__rtld_rodata_end = .);
	} PHDR(text)

	.eh_frame : {
		PROVIDE_HIDDEN(__rtld_eh_frame_start = .);
		KEEP(*(.eh_frame))
		PROVIDE_HIDDEN(__rtld_eh_frame_end = .);
	} PHDR(text)

	.gcc_except_table BLOCK(1) : {
		PROVIDE_HIDDEN(__rtld_gcc_except_table_start = .);
		KEEP(*(.gcc_except_table .gcc_except_table.*))
		PROVIDE_HIDDEN(__rtld_gcc_except_table_end = .);
	} PHDR(text)

	. = ALIGN(__ARCH_PAGESIZE);

	.data BLOCK(1) : {
		PROVIDE_HIDDEN(__rtld_data_start = .);
		*(.data.hot .data.hot.* .data.likely .data.likely.*)
		*(.data .data.local.*)
		*(.data.cold .data.cold.* .data.unlikely .data.unlikely.*)
		*(.data.*)
		PROVIDE_HIDDEN(__rtld_data_end = .);
	} PHDR(data)

	.bss BLOCK(1) : {
		PROVIDE_HIDDEN(__rtld_bss_start = .);
		*(.bss.hot .bss.hot.* .bss.likely .bss.likely.*)
		*(.bss .bss.local.*)
		*(.bss.cold .bss.cold.* .bss.unlikely .bss.unlikely.*)
		*(.bss.*)
		PROVIDE_HIDDEN(__rtld_bss_end = .);
		PROVIDE_HIDDEN(__rtld_end = .);
	} PHDR(data)

	. = ALIGN(__ARCH_PAGESIZE);
	.dynamic BLOCK(1) : {
		*(.dynamic)
	} PHDR(rel) PHDR(dynamic)

	.got BLOCK(1) : {
		*(.got)
	} PHDR(rel)

	.got.plt BLOCK(1) : {
		*(.got.plt)
	} PHDR(rel)

	.rel.dyn BLOCK(1) : {
		*(.rel.init)
		*(.rel.text .rel.text.*)
		*(.rel.fini)
		*(.rel.rodata .rel.rodata.*)
		*(.rel.data.rel.ro .rel.data.rel.ro.*)
		*(.rel.data .rel.data.*)
		*(.rel.tdata .rel.tdata.*)
		*(.rel.tbss .rel.tbss.*)
		*(.rel.ctors)
		*(.rel.dtors)
		*(.rel.got)
		*(.rel.bss .rel.bss.*)
		*(.rel.ifunc)
	} PHDR(rel)

	.rel.plt BLOCK(1) : {
		*(.rel.plt)
		PROVIDE_HIDDEN(__rel_iplt_start = .);
		*(.rel.iplt)
		PROVIDE_HIDDEN(__rel_iplt_end = .);
	} PHDR(rel)

	.fakedata BLOCK(1) : {
		*(.fakedata)
	} PHDR(rel)

	/DISCARD/ : {
		*(.discard)
		*(.comment)
		*(.note.gnu.build-id)
		*(.data.DW.ref.*)
		*(.data.rel.local.DW.ref.__gxx_personality_v0)
	}
}

#endif /* !GUARD_LIBDL__RTLD_LD */
