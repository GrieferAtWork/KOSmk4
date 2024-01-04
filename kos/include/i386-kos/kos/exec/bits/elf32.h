/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _I386_KOS_KOS_EXEC_BITS_ELF32_H
#define _I386_KOS_KOS_EXEC_BITS_ELF32_H 1

#include <__stdinc.h>

#include <hybrid/host.h>

#include <bits/types.h>

#include <elf.h>

#include <libc/string.h>

#if !defined(__x86_64__) && defined(__i386__)
#define __OFFSET_PROCESS_RTLD_ELF_RTLDADDR __OFFSET_PROCESS_RTLD_ELF32_RTLDADDR
#define __OFFSET_PROCESS_RTLD_ELF_NUM      __OFFSET_PROCESS_RTLD_ELF32_NUM
#define __OFFSET_PROCESS_RTLD_ELF_ABI      __OFFSET_PROCESS_RTLD_ELF32_ABI
#define __OFFSET_PROCESS_RTLD_ELF_ABIVER   __OFFSET_PROCESS_RTLD_ELF32_ABIVER
#define __OFFSET_PROCESS_RTLD_ELF_PHDR     __OFFSET_PROCESS_RTLD_ELF32_PHDR
#define __elfexec_info_defined
#define elfexec_info32           elfexec_info
#define elfexec_info_getfilename elfexec_info32_getfilename
#define elfexec_info_getentry    elfexec_info32_getentry
#endif /* !__x86_64__ && __i386__ */


__DECL_BEGIN

#define __OFFSET_PROCESS_RTLD_ELF32_RTLDADDR 0
#define __OFFSET_PROCESS_RTLD_ELF32_PNUM     4
#define __OFFSET_PROCESS_RTLD_ELF32_ABI      6
#define __OFFSET_PROCESS_RTLD_ELF32_ABIVER   7
#define __OFFSET_PROCESS_RTLD_ELF32_PHDR     8

#ifdef __CC__
struct elfexec_info32 /*[PREFIX(ei_)]*/ {
	__uint32_t ei_rtldaddr;    /* Load address of the RTLD itself. */
	Elf32_Half ei_pnum;        /* Amount of ELF program headers. */
	__uint8_t  ei_abi;         /* [const] The value of `EI_OSABI' */
	__uint8_t  ei_abiver;      /* [const] The value of `EI_ABIVERSION' */
	Elf32_Phdr ei_phdr[1024];  /* [ei_pnum] Vector of ELF program headers.
	                            * All of these have already been loaded into memory. */
//	char       ei_filename[*]; /* NUL-terminated filename of the loaded binary. */
//	char       ei_align[*];    /* Align to next 4 byte boundary. */
//	__uint32_t ei_entry;       /* The final entry point for the program. */
//	byte_t     ei_entry_sp[];  /* Entry stack address (set the address of this field as
//	                            * stack-pointer when handing control to the hosted application) */
};
#define elfexec_info32_getfilename(x) \
	((char *)&(x)->ei_phdr[(x)->ei_pnum])
#define elfexec_info32_getentry(x) \
	(*(__uint32_t *)((__uint32_t)(__libc_strend(elfexec_info_getfilename(x)) + 1 + 3) & ~3))
#endif /* __CC__ */

__DECL_END

#endif /* !_I386_KOS_KOS_EXEC_BITS_ELF32_H */
