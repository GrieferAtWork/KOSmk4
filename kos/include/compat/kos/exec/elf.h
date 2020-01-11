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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _COMPAT_KOS_EXEC_ELF_H
#define _COMPAT_KOS_EXEC_ELF_H 1

#include <__stdinc.h>

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

#ifndef COMPAT_ELF_ARCH_CLASSNAME
#if COMPAT_ELF_ARCH_CLASS == ELFCLASS32
#define ELF_ARCH_CLASSNAME "CLASS32"
#elif COMPAT_ELF_ARCH_CLASS == ELFCLASS64
#define ELF_ARCH_CLASSNAME "CLASS64"
#else
#define ELF_ARCH_CLASSNAME PP_STR(COMPAT_ELF_ARCH_CLASS)
#endif
#endif /* !COMPAT_ELF_ARCH_CLASSNAME */

#ifndef COMPAT_ELF_ARCH_DATANAME
#if COMPAT_ELF_ARCH_DATA == ELFDATA2LSB
#define COMPAT_ELF_ARCH_DATANAME "DATA2LSB"
#elif COMPAT_ELF_ARCH_DATA == ELFDATA2MSB
#define COMPAT_ELF_ARCH_DATANAME "DATA2MSB"
#else
#define COMPAT_ELF_ARCH_DATANAME PP_STR(COMPAT_ELF_ARCH_DATA)
#endif
#endif /* !COMPAT_ELF_ARCH_DATANAME */

#ifndef COMPAT_ELF_ARCH_MACHINENAME
#if COMPAT_ELF_ARCH_MACHINE == EM_M32
#define COMPAT_ELF_ARCH_MACHINENAME "M32"
#elif COMPAT_ELF_ARCH_MACHINE == EM_SPARC
#define COMPAT_ELF_ARCH_MACHINENAME "SPARC"
#elif COMPAT_ELF_ARCH_MACHINE == EM_386
#define COMPAT_ELF_ARCH_MACHINENAME "386"
#elif COMPAT_ELF_ARCH_MACHINE == EM_68K
#define COMPAT_ELF_ARCH_MACHINENAME "68K"
#elif COMPAT_ELF_ARCH_MACHINE == EM_88K
#define COMPAT_ELF_ARCH_MACHINENAME "88K"
#elif COMPAT_ELF_ARCH_MACHINE == EM_860
#define COMPAT_ELF_ARCH_MACHINENAME "860"
#elif COMPAT_ELF_ARCH_MACHINE == EM_MIPS
#define COMPAT_ELF_ARCH_MACHINENAME "MIPS"
#elif COMPAT_ELF_ARCH_MACHINE == EM_S370
#define COMPAT_ELF_ARCH_MACHINENAME "S370"
#elif COMPAT_ELF_ARCH_MACHINE == EM_MIPS_RS3_LE
#define COMPAT_ELF_ARCH_MACHINENAME "MIPS_RS3_LE"
#elif COMPAT_ELF_ARCH_MACHINE == EM_PARISC
#define COMPAT_ELF_ARCH_MACHINENAME "PARISC"
#elif COMPAT_ELF_ARCH_MACHINE == EM_VPP500
#define COMPAT_ELF_ARCH_MACHINENAME "VPP500"
#elif COMPAT_ELF_ARCH_MACHINE == EM_SPARC32PLUS
#define COMPAT_ELF_ARCH_MACHINENAME "SPARC32PLUS"
#elif COMPAT_ELF_ARCH_MACHINE == EM_960
#define COMPAT_ELF_ARCH_MACHINENAME "960"
#elif COMPAT_ELF_ARCH_MACHINE == EM_PPC
#define COMPAT_ELF_ARCH_MACHINENAME "PPC"
#elif COMPAT_ELF_ARCH_MACHINE == EM_PPC64
#define COMPAT_ELF_ARCH_MACHINENAME "PPC64"
#elif COMPAT_ELF_ARCH_MACHINE == EM_S390
#define COMPAT_ELF_ARCH_MACHINENAME "S390"
#elif COMPAT_ELF_ARCH_MACHINE == EM_V800
#define COMPAT_ELF_ARCH_MACHINENAME "V800"
#elif COMPAT_ELF_ARCH_MACHINE == EM_FR20
#define COMPAT_ELF_ARCH_MACHINENAME "FR20"
#elif COMPAT_ELF_ARCH_MACHINE == EM_RH32
#define COMPAT_ELF_ARCH_MACHINENAME "RH32"
#elif COMPAT_ELF_ARCH_MACHINE == EM_RCE
#define COMPAT_ELF_ARCH_MACHINENAME "RCE"
#elif COMPAT_ELF_ARCH_MACHINE == EM_ARM
#define COMPAT_ELF_ARCH_MACHINENAME "ARM"
#elif COMPAT_ELF_ARCH_MACHINE == EM_FAKE_ALPHA
#define COMPAT_ELF_ARCH_MACHINENAME "FAKE_ALPHA"
#elif COMPAT_ELF_ARCH_MACHINE == EM_SH
#define COMPAT_ELF_ARCH_MACHINENAME "SH"
#elif COMPAT_ELF_ARCH_MACHINE == EM_SPARCV9
#define COMPAT_ELF_ARCH_MACHINENAME "SPARCV9"
#elif COMPAT_ELF_ARCH_MACHINE == EM_TRICORE
#define COMPAT_ELF_ARCH_MACHINENAME "TRICORE"
#elif COMPAT_ELF_ARCH_MACHINE == EM_ARC
#define COMPAT_ELF_ARCH_MACHINENAME "ARC"
#elif COMPAT_ELF_ARCH_MACHINE == EM_H8_300
#define COMPAT_ELF_ARCH_MACHINENAME "H8_300"
#elif COMPAT_ELF_ARCH_MACHINE == EM_H8_300H
#define COMPAT_ELF_ARCH_MACHINENAME "H8_300H"
#elif COMPAT_ELF_ARCH_MACHINE == EM_H8S
#define COMPAT_ELF_ARCH_MACHINENAME "H8S"
#elif COMPAT_ELF_ARCH_MACHINE == EM_H8_500
#define COMPAT_ELF_ARCH_MACHINENAME "H8_500"
#elif COMPAT_ELF_ARCH_MACHINE == EM_IA_64
#define COMPAT_ELF_ARCH_MACHINENAME "IA_64"
#elif COMPAT_ELF_ARCH_MACHINE == EM_MIPS_X
#define COMPAT_ELF_ARCH_MACHINENAME "MIPS_X"
#elif COMPAT_ELF_ARCH_MACHINE == EM_COLDFIRE
#define COMPAT_ELF_ARCH_MACHINENAME "COLDFIRE"
#elif COMPAT_ELF_ARCH_MACHINE == EM_68HC12
#define COMPAT_ELF_ARCH_MACHINENAME "68HC12"
#elif COMPAT_ELF_ARCH_MACHINE == EM_MMA
#define COMPAT_ELF_ARCH_MACHINENAME "MMA"
#elif COMPAT_ELF_ARCH_MACHINE == EM_PCP
#define COMPAT_ELF_ARCH_MACHINENAME "PCP"
#elif COMPAT_ELF_ARCH_MACHINE == EM_NCPU
#define COMPAT_ELF_ARCH_MACHINENAME "NCPU"
#elif COMPAT_ELF_ARCH_MACHINE == EM_NDR1
#define COMPAT_ELF_ARCH_MACHINENAME "NDR1"
#elif COMPAT_ELF_ARCH_MACHINE == EM_STARCORE
#define COMPAT_ELF_ARCH_MACHINENAME "STARCORE"
#elif COMPAT_ELF_ARCH_MACHINE == EM_ME16
#define COMPAT_ELF_ARCH_MACHINENAME "ME16"
#elif COMPAT_ELF_ARCH_MACHINE == EM_ST100
#define COMPAT_ELF_ARCH_MACHINENAME "ST100"
#elif COMPAT_ELF_ARCH_MACHINE == EM_TINYJ
#define COMPAT_ELF_ARCH_MACHINENAME "TINYJ"
#elif COMPAT_ELF_ARCH_MACHINE == EM_X86_64
#define COMPAT_ELF_ARCH_MACHINENAME "X86_64"
#elif COMPAT_ELF_ARCH_MACHINE == EM_PDSP
#define COMPAT_ELF_ARCH_MACHINENAME "PDSP"
#elif COMPAT_ELF_ARCH_MACHINE == EM_FX66
#define COMPAT_ELF_ARCH_MACHINENAME "FX66"
#elif COMPAT_ELF_ARCH_MACHINE == EM_ST9PLUS
#define COMPAT_ELF_ARCH_MACHINENAME "ST9PLUS"
#elif COMPAT_ELF_ARCH_MACHINE == EM_ST7
#define COMPAT_ELF_ARCH_MACHINENAME "ST7"
#elif COMPAT_ELF_ARCH_MACHINE == EM_68HC16
#define COMPAT_ELF_ARCH_MACHINENAME "68HC16"
#elif COMPAT_ELF_ARCH_MACHINE == EM_68HC11
#define COMPAT_ELF_ARCH_MACHINENAME "68HC11"
#elif COMPAT_ELF_ARCH_MACHINE == EM_68HC08
#define COMPAT_ELF_ARCH_MACHINENAME "68HC08"
#elif COMPAT_ELF_ARCH_MACHINE == EM_68HC05
#define COMPAT_ELF_ARCH_MACHINENAME "68HC05"
#elif COMPAT_ELF_ARCH_MACHINE == EM_SVX
#define COMPAT_ELF_ARCH_MACHINENAME "SVX"
#elif COMPAT_ELF_ARCH_MACHINE == EM_ST19
#define COMPAT_ELF_ARCH_MACHINENAME "ST19"
#elif COMPAT_ELF_ARCH_MACHINE == EM_VAX
#define COMPAT_ELF_ARCH_MACHINENAME "VAX"
#elif COMPAT_ELF_ARCH_MACHINE == EM_CRIS
#define COMPAT_ELF_ARCH_MACHINENAME "CRIS"
#elif COMPAT_ELF_ARCH_MACHINE == EM_JAVELIN
#define COMPAT_ELF_ARCH_MACHINENAME "JAVELIN"
#elif COMPAT_ELF_ARCH_MACHINE == EM_FIREPATH
#define COMPAT_ELF_ARCH_MACHINENAME "FIREPATH"
#elif COMPAT_ELF_ARCH_MACHINE == EM_ZSP
#define COMPAT_ELF_ARCH_MACHINENAME "ZSP"
#elif COMPAT_ELF_ARCH_MACHINE == EM_MMIX
#define COMPAT_ELF_ARCH_MACHINENAME "MMIX"
#elif COMPAT_ELF_ARCH_MACHINE == EM_HUANY
#define COMPAT_ELF_ARCH_MACHINENAME "HUANY"
#elif COMPAT_ELF_ARCH_MACHINE == EM_PRISM
#define COMPAT_ELF_ARCH_MACHINENAME "PRISM"
#elif COMPAT_ELF_ARCH_MACHINE == EM_AVR
#define COMPAT_ELF_ARCH_MACHINENAME "AVR"
#elif COMPAT_ELF_ARCH_MACHINE == EM_FR30
#define COMPAT_ELF_ARCH_MACHINENAME "FR30"
#elif COMPAT_ELF_ARCH_MACHINE == EM_D10V
#define COMPAT_ELF_ARCH_MACHINENAME "D10V"
#elif COMPAT_ELF_ARCH_MACHINE == EM_D30V
#define COMPAT_ELF_ARCH_MACHINENAME "D30V"
#elif COMPAT_ELF_ARCH_MACHINE == EM_V850
#define COMPAT_ELF_ARCH_MACHINENAME "V850"
#elif COMPAT_ELF_ARCH_MACHINE == EM_M32R
#define COMPAT_ELF_ARCH_MACHINENAME "M32R"
#elif COMPAT_ELF_ARCH_MACHINE == EM_MN10300
#define COMPAT_ELF_ARCH_MACHINENAME "MN10300"
#elif COMPAT_ELF_ARCH_MACHINE == EM_MN10200
#define COMPAT_ELF_ARCH_MACHINENAME "MN10200"
#elif COMPAT_ELF_ARCH_MACHINE == EM_PJ
#define COMPAT_ELF_ARCH_MACHINENAME "PJ"
#elif COMPAT_ELF_ARCH_MACHINE == EM_OPENRISC
#define COMPAT_ELF_ARCH_MACHINENAME "OPENRISC"
#elif COMPAT_ELF_ARCH_MACHINE == EM_ARC_A5
#define COMPAT_ELF_ARCH_MACHINENAME "ARC_A5"
#elif COMPAT_ELF_ARCH_MACHINE == EM_XTENSA
#define COMPAT_ELF_ARCH_MACHINENAME "XTENSA"
#else /* ... */
#define COMPAT_ELF_ARCH_MACHINENAME PP_STR(COMPAT_ELF_ARCH_MACHINE)
#endif /* !... */
#endif /* !COMPAT_ELF_ARCH_MACHINENAME */


/* Must number of allowed program headers */
#ifndef COMPAT_ELF_ARCH_MAXPHCOUNT
#define COMPAT_ELF_ARCH_MAXPHCOUNT ELF_ARCH_MAXPHCOUNT
#endif /* !COMPAT_ELF_ARCH_MAXPHCOUNT */

#ifndef COMPAT_ELFW
#if COMPAT_ELF_ARCH_CLASS == ELFCLASS32
#define COMPAT_ELFW(x) ELF32_##x
#define COMPAT_ElfW(x) Elf32_##x
#elif COMPAT_ELF_ARCH_CLASS == ELFCLASS64
#define COMPAT_ELFW(x) ELF64_##x
#define COMPAT_ElfW(x) Elf64_##x
#endif
#endif /* !COMPAT_ELFW */

#ifdef __CC__
__DECL_BEGIN

#ifndef __compat_elfexec_info_defined
#define __compat_elfexec_info_defined 1
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

#endif /* !_COMPAT_KOS_EXEC_ELF_H */
