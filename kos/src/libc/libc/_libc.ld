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
#ifndef GUARD_LIBC_LIBC__LIBC_LD
#define GUARD_LIBC_LIBC__LIBC_LD 1

#include <hybrid/compiler.h>

#include <hybrid/host.h>

#include <kos/exec/elf.h> /* ELF_ARCH_USESRELA */
#include <asm/pagesize.h>

#include "../crt-order.h"

#if 0
#define PHDR(x) /* nothing */
#else
PHDRS {
	text    PT_LOAD;
#ifndef __x86_64__
	xdata   PT_LOAD;
#endif /* !__x86_64__ */
	rodata  PT_LOAD;
	data    PT_LOAD;
	dynamic PT_DYNAMIC;
	tls     PT_TLS;
}
#define PHDR(x) :x
#endif


#undef hot
#undef cold
#undef likely
#undef unlikely


#define ENUMERATE_CRT_SECTIONS(PREFIX) \
	CRT_SECTIONS_LINKORDER(*,PREFIX)
#define ENUMERATE_SECTIONS(PREFIX)                                 \
	*(PREFIX.hot PREFIX.likely PREFIX.hot.* PREFIX.likely.*)       \
	*(PREFIX)                                                      \
	ENUMERATE_CRT_SECTIONS(PREFIX)                                 \
	*(PREFIX.cold PREFIX.unlikely PREFIX.cold.* PREFIX.unlikely.*)


#undef NEED___libc_errno_access_core_start
#undef NEED_xdata
#if !defined(__x86_64__) && defined(__i386__)
#define NEED___libc_errno_access_core_start
#define NEED_xdata
#endif /* !__x86_64__ && __i386__ */


SECTIONS {

	. = SIZEOF_HEADERS;

	.plt : {
		*(.plt)
	} PHDR(text)

	.text : {
#if defined(__i386__) || defined(__x86_64__)
		*(.text.__x86.* .text.__x86)
#endif /* __i386__ || __x86_64__ */
#ifdef NEED___libc_errno_access_core_start
		/* Hacky premature declaration of sections so we can let  the
		 * linker calculate the bounding address range which needs to
		 * be made writable for `nontls_errno_redirect()' */
		*(.text.hot .text.likely .text.hot.* .text.likely.*)
		*(.text)
		*(.text.crt.application.init)
		PROVIDE_HIDDEN(__libc_errno_access_core_start = .);
		*(.text.crt.errno_access.core)
		PROVIDE_HIDDEN(__libc_errno_access_core_end = .);
		ENUMERATE_SECTIONS(.text)
#else /* NEED___libc_errno_access_core_start */
		ENUMERATE_SECTIONS(.text)
#endif /* !NEED___libc_errno_access_core_start */
		*(.text.local.*)
	} PHDR(text)
	__etext = .;
	_etext = .;

#ifdef NEED_xdata
	. = ALIGN(__ARCH_PAGESIZE);
	.xdata : {
		*(.xdata)
	} PHDR(xdata)
#endif /* NEED_xdata */

	. = ALIGN(__ARCH_PAGESIZE);
	.rodata : {
		*(.rodata.str* .rodata.*.str* .rodata.cst* .rodata.*.cst*)
		ENUMERATE_SECTIONS(.rodata)
		*(.rodata.local.*)
	} PHDR(rodata)

	.gcc_except_table : {
		KEEP(*(.gcc_except_table .gcc_except_table.*))
	} PHDR(rodata)

	.eh_frame_hdr : {
		KEEP(*(.eh_frame_hdr))
	} PHDR(rodata)

	.eh_frame : {
		KEEP(*(.eh_frame))
	} PHDR(rodata)

#if ELF_ARCH_USESRELA
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
	} PHDR(rodata)

	.rela.plt : {
		*(.rela.plt)
	} PHDR(rodata)
#else /* ELF_ARCH_USESRELA */
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
	} PHDR(rodata)
#endif /* !ELF_ARCH_USESRELA */

	. = ALIGN(__ARCH_PAGESIZE);
	.dynamic : {
		*(.dynamic)
	} PHDR(data) PHDR(dynamic)

	.got.plt : {
		*(.got.plt)
	} PHDR(data)

	.got : {
		*(.got)
	} PHDR(data)

	.data : {
		*(.data.read_mostly)
		ENUMERATE_SECTIONS(.data)
		*(.data.rel.local.DW.ref.__gxx_personality_v0)
		*(.data.local.*)
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

	.tdata : {
		*(.tdata .tdata.* .gnu.linkonce.td.*)
	} PHDR(tls) PHDR(data)
	_edata = .;

//	. = ALIGN(__ARCH_PAGESIZE);
	__bss_start = .;
	.tbss : {
		*(.tbss .tbss.* .gnu.linkonce.tb.*)
		*(.tcommon)
	} PHDR(tls) PHDR(data)

	.bss : {
		ENUMERATE_SECTIONS(.bss)
		*(.bss.local.*)
	} PHDR(data)
	_end = .;

	/DISCARD/ : {
		*(.discard)
		*(.comment)
		*(.note.gnu.build-id)
		*(.note.GNU-stack)
		*(.gnu_debuglink)
		*(.gnu.lto_*)
		*(.data.DW.ref.*)
	}

}

#endif /* !GUARD_LIBC_LIBC__LIBC_LD */
