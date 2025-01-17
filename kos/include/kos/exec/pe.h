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
#ifndef _KOS_EXEC_PE_H
#define _KOS_EXEC_PE_H 1

#include <__stdinc.h>

#include <kos/exec/elf.h>
#include <nt/pe.h>

#include <libc/string.h>

#ifdef __CC__
__DECL_BEGIN

struct peexec_data {
	/* TODO: Don't include the entire `IMAGE_NT_HEADERS' -- Only include what's actually used! */
	__UINTPTR_TYPE__                                pd_loadmin; /* First (absolute) address mapped by the sections of this binary */
	__UINTPTR_TYPE__                                pd_loadmax; /* Last (absolute) address mapped by the sections of this binary */
	IMAGE_NT_HEADERS                                pd_nt;      /* NT header. (actual field size is `offsetof(IMAGE_NT_HEADERS, OptionalHeader) + pd_nt.FileHeader.SizeOfOptionalHeader'). */
/*	__COMPILER_FLEXIBLE_ARRAY(byte_t,              _pd_pad1);    * Pad to multiples of `sizeof(void *)' */
/*	__COMPILER_FLEXIBLE_ARRAY(IMAGE_SECTION_HEADER, pd_sect);    * Section headers (length is `pd_nt.FileHeader.NumberOfSections') */
/*	__COMPILER_FLEXIBLE_ARRAY(char,                 pd_name);    * NUL-termianted, absolute filename of primary executable in unix notation (e.g. `/bin/program.exe') */
/*	__COMPILER_FLEXIBLE_ARRAY(byte_t,              _pd_pad2);    * Pad to multiples of `sizeof(void *)' */
};

/* Helper macros for accessing hidden fields. */
#define _peexec_data__offsetof_pd_sect(self) \
	(((self)->pd_nt.FileHeader.SizeOfOptionalHeader + offsetof(struct peexec_data, pd_nt.OptionalHeader) + sizeof(void *) - 1) & ~(sizeof(void *) - 1))
#define _peexec_data__offsetof_pd_name(self) \
	(_peexec_data__offsetof_pd_sect(self) + (self)->pd_nt.FileHeader.NumberOfSections * sizeof(IMAGE_SECTION_HEADER))
#define peexec_data__pd_sect(self) ((IMAGE_SECTION_HEADER *)((__BYTE_TYPE__ *)(self) + _peexec_data__offsetof_pd_sect(self)))
#define peexec_data__pd_name(self) ((char *)((__BYTE_TYPE__ *)(self) + _peexec_data__offsetof_pd_name(self)))


struct peexec_info /*[PREFIX(ei_)]*/ {
	__UINTPTR_TYPE__                pi_rtldaddr;   /* Load address of the RTLD itself. */
	__UINT16_TYPE__                 pi_pnum;       /* [const] == (ElfW(Half))-1  (indicator for libdl to use an interpreter library) */
	__COMPILER_FLEXIBLE_ARRAY(char, pi_libdl_pe);  /* [const] Filename of PE interpreter library (usually "/lib/libdl-pe.so" or "/lib64/libdl-pe.so") */
/*	__BYTE_TYPE__                  _pi_pad[];       * Pad to multiples of `sizeof(void *)' */
/*	struct peexec_data              pi_pe;          * PE execution information  */
//	void                           *pi_entry;      /* The final entry point for the program. */
//	byte_t                          pi_entry_sp[]; /* Entry stack address (set the address of this field as
//	                                                * stack-pointer when handing control to the hosted application) */
};

#define peexec_info__pi_pe(self)                                             \
	((struct peexec_data *)(((uintptr_t)__libc_strend((self)->pi_libdl_pe) + \
	                         sizeof(void *) - 1) &                           \
	                        ~(sizeof(void *) - 1)))


__DECL_END
#endif /* __CC__ */

#endif /* !_KOS_EXEC_PE_H */
