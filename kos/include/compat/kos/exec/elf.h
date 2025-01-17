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
#ifndef _COMPAT_KOS_EXEC_ELF_H
#define _COMPAT_KOS_EXEC_ELF_H 1

#include <__stdinc.h>

#include <compat/config.h>
#ifdef __ARCH_HAVE_COMPAT
#include <compat/kos/exec/asm/elf.h>
#include <compat/kos/exec/bits/elf.h>
#include <kos/exec/elf.h>

#include <elf.h>

#ifndef COMPAT_ELF_ARCH_CLASS
#define COMPAT_ELF_ARCH_CLASS ELF_ARCH_CLASS
#endif /* !COMPAT_ELF_ARCH_CLASS */

#ifndef COMPAT_ELF_ARCH_DATA
#define COMPAT_ELF_ARCH_DATA ELF_ARCH_DATA
#endif /* !COMPAT_ELF_ARCH_DATA */

#ifndef COMPAT_ELF_ARCH_MACHINE
#define COMPAT_ELF_ARCH_MACHINE ELF_ARCH_MACHINE
#endif /* !COMPAT_ELF_ARCH_MACHINE */

#ifndef COMPAT_ELF_ARCH_USESRELA
#define COMPAT_ELF_ARCH_USESRELA ELF_ARCH_USESRELA
#endif /* !COMPAT_ELF_ARCH_USESRELA */

#ifndef COMPAT_ELF_ARCH_LAZYINDX
#define COMPAT_ELF_ARCH_LAZYINDX ELF_ARCH_LAZYINDX
#endif /* !COMPAT_ELF_ARCH_LAZYINDX */

/* Must number of allowed program headers */
#ifndef COMPAT_ELF_ARCH_MAXPHCOUNT
#define COMPAT_ELF_ARCH_MAXPHCOUNT ELF_ARCH_MAXPHCOUNT
#endif /* !COMPAT_ELF_ARCH_MAXPHCOUNT */

#ifndef COMPAT_ELFW
#if COMPAT_ELF_ARCH_CLASS == ELFCLASS32
#define COMPAT_ELFW(x)          ELF32_##x
#define COMPAT_ElfW(x)          Elf32_##x
#define COMPAT_elfW(x)          elf32_##x
#define __OFFSET_COMPAT_ELFW(x) __OFFSET_ELF32_##x
#define __SIZEOF_COMPAT_ELFW(x) __SIZEOF_ELF32_##x
#elif COMPAT_ELF_ARCH_CLASS == ELFCLASS64
#define COMPAT_ELFW(x)          ELF64_##x
#define COMPAT_ElfW(x)          Elf64_##x
#define COMPAT_elfW(x)          elf64_##x
#define __OFFSET_COMPAT_ELFW(x) __OFFSET_ELF64_##x
#define __SIZEOF_COMPAT_ELFW(x) __SIZEOF_ELF64_##x
#endif
#endif /* !COMPAT_ELFW */

#ifdef __CC__
__DECL_BEGIN

#ifndef __compat_elfexec_info_defined
#define __compat_elfexec_info_defined
struct compat_elfexec_info /*[PREFIX(pr_)]*/ {
	COMPAT_ElfW(Addr)  ei_rtldaddr;    /* Load address of the RTLD itself. */
	COMPAT_ElfW(Half)  ei_pnum;        /* Amount of ELF program headers. */
	__uint8_t          ei_abi;         /* [const] The value of `EI_OSABI' */
	__uint8_t          ei_abiver;      /* [const] The value of `EI_ABIVERSION' */
	COMPAT_ElfW(Phdr)  ei_phdr[1024];  /* [ei_pnum] Vector of ELF program headers.
	                             * All of these have already been loaded into memory. */
//	char               ei_filename[*]; /* NUL-terminated filename of the loaded binary. */
//	char               ei_align[*];    /* Align to next pointer-sized byte boundary. */
//	compat_ptr(void)   ei_entry;       /* The final entry point for the program. */
//	byte_t             ei_entry_sp[];  /* Entry stack address (set the address of this field as
//	                                    * stack-pointer when handing control to the hosted application) */
};
#endif /* !__compat_elfexec_info_defined */

__DECL_END

/* Return the filename of the primary application */
#ifndef compat_elfexec_info_getfilename
#define compat_elfexec_info_getfilename(x) ((char *)&(x)->ei_phdr[(x)->pr_pnum])
#endif /* !compat_elfexec_info_getfilename */

/* Return the entry point address of the primary application (as an l-value) */
#ifndef compat_elfexec_info_getentry
#include <libc/string.h>
#define compat_elfexec_info_getentry(x)                                           \
	(*(void **)((__uintptr_t)(__libc_strend(compat_elfexec_info_getfilename(x)) + \
	                          sizeof(__uintptr_t)) &                              \
	            ~(sizeof(__uintptr_t) - 1)))
#endif /* !compat_elfexec_info_getentry */

#endif /* __CC__ */
#endif /* __ARCH_HAVE_COMPAT */

#endif /* !_COMPAT_KOS_EXEC_ELF_H */
