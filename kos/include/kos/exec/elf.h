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
#ifndef _KOS_EXEC_ELF_H
#define _KOS_EXEC_ELF_H 1

#include <__stdinc.h>

#include <kos/exec/asm/elf.h>
#include <kos/exec/bits/elf.h>

#include <elf.h>

/* The expected machine word-size class */
#ifndef ELF_ARCH_CLASS
#error "Arch must #define `ELF_ARCH_CLASS' (as one of `ELFCLASS*')"
#endif /* !ELF_ARCH_CLASS */

/* The expected machine endian */
#ifndef ELF_ARCH_DATA
#error "Arch must #define `ELF_ARCH_DATA' (as one of `ELFDATA*')"
#endif /* !ELF_ARCH_DATA */

/* The expected machine ID */
#ifndef ELF_ARCH_MACHINE
#error "Arch must #define `ELF_ARCH_MACHINE' (as one of `EM_*')"
#endif /* !ELF_ARCH_MACHINE */

/* Define as:
 *   1: ElfW(Rela) relocations may be used
 *   0: Only ElfW(Rel) relocations are used */
#ifndef ELF_ARCH_USESRELA
#error "Arch must #define `ELF_ARCH_USESRELA' (as either `0' or `1')"
#endif /* !ELF_ARCH_USESRELA */

/* Define as:
 *   1: Lazy relocations use indices, rather than offsets
 *   0: Lazy relocations use offsets, rather than indices */
#ifndef ELF_ARCH_LAZYINDX
#error "Arch must #define `ELF_ARCH_LAZYINDX' (as either `0' or `1')"
#endif /* !ELF_ARCH_LAZYINDX */

/* Must number of allowed program headers */
#ifndef ELF_ARCH_MAXPHCOUNT
#define ELF_ARCH_MAXPHCOUNT 64
#endif /* !ELF_ARCH_MAXPHCOUNT */

#ifndef ELFW
#if ELF_ARCH_CLASS == ELFCLASS32
#define ELFW(x)          ELF32_##x
#define ElfW(x)          Elf32_##x
#define elfW(x)          elf32_##x
#define __OFFSET_ELFW(x) __OFFSET_ELF32_##x
#define __SIZEOF_ELFW(x) __SIZEOF_ELF32_##x
#elif ELF_ARCH_CLASS == ELFCLASS64
#define ELFW(x)          ELF64_##x
#define ElfW(x)          Elf64_##x
#define elfW(x)          elf64_##x
#define __OFFSET_ELFW(x) __OFFSET_ELF64_##x
#define __SIZEOF_ELFW(x) __SIZEOF_ELF64_##x
#endif /* ... */
#endif /* !ELFW */


#ifdef __CC__
#ifndef __elfexec_info_defined
#define __elfexec_info_defined
__DECL_BEGIN

struct elfexec_info /*[PREFIX(ei_)]*/ {
	ElfW(Addr)  ei_rtldaddr;    /* Load address of the RTLD itself. */
	ElfW(Half)  ei_pnum;        /* Amount of ELF program headers. */
	__uint8_t   ei_abi;         /* [const] The value of `EI_OSABI' */
	__uint8_t   ei_abiver;      /* [const] The value of `EI_ABIVERSION' */
	ElfW(Phdr)  ei_phdr[1024];  /* [ei_pnum] Vector of ELF program headers.
	                             * All of these have already been loaded into memory. */
//	char        ei_filename[*]; /* NUL-terminated filename of the loaded binary. */
//	char        ei_align[*];    /* Align to next pointer-sized byte boundary. */
//	void       *ei_entry;       /* The final entry point for the program. */
//	byte_t      ei_entry_sp[];  /* Entry stack address (set the address of this field as
//	                             * stack-pointer when handing control to the hosted application) */
};

__DECL_END
#endif /* !__elfexec_info_defined */

/* Check if a custom interpreter library should be used. */
#ifndef elfexec_info_usesinterpreter
#define elfexec_info_usesinterpreter(x) ((x)->ei_pnum == (ElfW(Half))-1)
#endif /* !elfexec_info_usesinterpreter */

/* Return the filename for the interpreter library. */
#ifndef elfexec_info_getinterpreter
#define elfexec_info_getinterpreter(x) ((char *)&(x)->ei_abi)
#endif /* !elfexec_info_getinterpreter */

/* Return the filename of the primary application */
#ifndef elfexec_info_getfilename
#define elfexec_info_getfilename(x) ((char *)&(x)->ei_phdr[(x)->pr_pnum])
#endif /* !elfexec_info_getfilename */

/* Return the entry point address of the primary application (as an l-value) */
#ifndef elfexec_info_getentry
#include <libc/string.h>
#define elfexec_info_getentry(x)                                           \
	(*(void **)((__uintptr_t)(__libc_strend(elfexec_info_getfilename(x)) + \
	                          sizeof(__uintptr_t)) &                       \
	            ~(sizeof(__uintptr_t) - 1)))
#endif /* !elfexec_info_getentry */
#endif /* __CC__ */

#endif /* !_KOS_EXEC_ELF_H */
