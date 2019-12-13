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
#ifndef GUARD_LIBC_LIBC_ARCH_I386__LIBC_LD
#define GUARD_LIBC_LIBC_ARCH_I386__LIBC_LD 1

#include <hybrid/compiler.h>
#include <asm/pagesize.h>

/* #include <crt-features/crt-kos-sections-order.h> */
/* Include as relative so we get a dependency on that header.
 * Since that header is automatically generated, it updating
 * will also force our file to be re-preprocessed, automating
 * the process a little bit better. */
#include "../../../../../include/crt-features/crt-kos-sections-order.h"

#if 0
#define PHDR(x) /* nothing */
#else
PHDRS {
	text PT_LOAD;
	xdata PT_LOAD;
	rodata PT_LOAD;
	data PT_LOAD;
	dynamic PT_DYNAMIC;
	tls PT_TLS;
}
#define PHDR(x) :x
#endif


#undef hot
#undef cold
#undef likely
#undef unlikely


#define ENUMERATE_CRT_SECTIONS(PREFIX) \
	__CRT_LINKORDER_SECTIONS(*,PREFIX.crt)
#define ENUMERATE_SECTIONS(PREFIX)                                 \
	*(PREFIX.hot PREFIX.likely PREFIX.hot.* PREFIX.likely.*)       \
	*(PREFIX)                                                      \
	ENUMERATE_CRT_SECTIONS(PREFIX)                                 \
	*(PREFIX.cold PREFIX.unlikely PREFIX.cold.* PREFIX.unlikely.*) \
	*(PREFIX.*)                                                    \
/**/


SECTIONS {

	.text : {
		*(.text.__x86.*)
		ENUMERATE_SECTIONS(.text)
	} PHDR(text)

	. = ALIGN(__ARCH_PAGESIZE);
	.xdata : {
		ENUMERATE_SECTIONS(.xdata)
	} PHDR(xdata)

	. = ALIGN(__ARCH_PAGESIZE);
	.rodata : {
		*(.rodata.hot .rodata.likely .rodata.hot.* .rodata.likely.*)
		*(.rodata .rodata.str* .rodata.*.str* .rodata.cst* .rodata.*.cst*)
		ENUMERATE_CRT_SECTIONS(.rodata)
		*(.rodata.cold .rodata.cold.* .rodata.unlikely .rodata.unlikely.*)
		*(.rodata.*)
	} PHDR(rodata)

	.gcc_except_table : {
		KEEP(*(.gcc_except_table))
	} PHDR(rodata)

	.eh_frame_hdr : {
		KEEP(*(.eh_frame_hdr))
	} PHDR(rodata)

	.eh_frame : {
		KEEP(*(.eh_frame))
	} PHDR(rodata)

	.rel.dyn : {
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
	} PHDR(rodata)

	.rel.plt : {
		*(.rel.plt)
		PROVIDE_HIDDEN(__rel_iplt_start = .);
		*(.rel.iplt)
		PROVIDE_HIDDEN(__rel_iplt_end = .);
	} PHDR(rodata)

	.tdata : {
		*(.tdata .tdata.* .gnu.linkonce.td.*)
	} PHDR(tls)

	.tbss : {
		*(.tbss .tbss.* .gnu.linkonce.tb.*)
		*(.tcommon)
	} PHDR(tls)

	. = ALIGN(__ARCH_PAGESIZE);
	.dynamic : {
		*(.dynamic)
	} PHDR(data) PHDR(dynamic)

	.got.plt : {
		*(.got.plt)
	} PHDR(data)

	.data : {
		*(.data.read_mostly .data.hot .data.likely .data.hot.* .data.likely.*)
		*(.data)
		ENUMERATE_CRT_SECTIONS(.data)
		*(.data.local.*) /* Load data objects, as defined by `__LOCAL_LIBC_DATA()' within automatic source files. */
		*(.data.cold .data.unlikely .data.cold.* .data.unlikely.*)
//		*(.data.*) /* We need to be able to discard *(.data.DW.ref.*)! */
	} PHDR(data)

	.preinit_array : {
		KEEP(*(.preinit_array*))
	} PHDR(data)

	.init_array : {
		KEEP(*(SORT_BY_INIT_PRIORITY(.init_array*) SORT_BY_INIT_PRIORITY(.ctors.*)))
	} PHDR(data)

	.fini_array : {
		KEEP(*(SORT_BY_INIT_PRIORITY(.fini_array*) SORT_BY_INIT_PRIORITY(.dtors.*)))
	} PHDR(data)

	. = ALIGN(__ARCH_PAGESIZE);
	.bss : {
		ENUMERATE_SECTIONS(.bss)
	} PHDR(data)

	/DISCARD/ : {
		*(.discard)
		*(.comment)
		*(.note.gnu.build-id)
		*(.data.DW.ref.*)
		*(.data.rel.local.DW.ref.__gxx_personality_v0)
	}

}

#endif /* !GUARD_LIBC_LIBC_ARCH_I386__LIBC_LD */
