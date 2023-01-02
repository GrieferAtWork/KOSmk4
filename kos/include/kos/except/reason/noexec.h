/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _KOS_EXCEPT_REASON_NOEXEC_H
#define _KOS_EXCEPT_REASON_NOEXEC_H 1

#include <__stdinc.h>

#include <libunwind/asm/features.h> /* LIBUNWIND_HAVE_ARM_EXIDX */

__DECL_BEGIN

/* Format codes for `E_NOT_EXECUTABLE_FAULTY' */

/*[[[enum]]]*/
#ifdef __CC__
enum {
	E_NOT_EXECUTABLE_FAULTY_FORMAT_ELF     = 0x0001, /* ELF Binary */
	E_NOT_EXECUTABLE_FAULTY_FORMAT_SHEBANG = 0x0002, /* #!-script file */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#define E_NOT_EXECUTABLE_FAULTY_FORMAT_ELF     E_NOT_EXECUTABLE_FAULTY_FORMAT_ELF     /* ELF Binary */
#define E_NOT_EXECUTABLE_FAULTY_FORMAT_SHEBANG E_NOT_EXECUTABLE_FAULTY_FORMAT_SHEBANG /* #!-script file */
#else /* __COMPILER_PREFERR_ENUMS */
#define E_NOT_EXECUTABLE_FAULTY_FORMAT_ELF     1 /* ELF Binary */
#define E_NOT_EXECUTABLE_FAULTY_FORMAT_SHEBANG 2 /* #!-script file */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/

/* Reason codes for `E_NOT_EXECUTABLE_FAULTY' */

/*[[[enum]]]*/
#ifdef __CC__
enum {
	E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BADCLASS = 1,            /* e_ident[EI_CLASS] != ELFCLASS32/64 (as required by the host) */
	E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BADORDER,                /* e_ident[EI_DATA] != ELFDATA2LSB/MSB (as required by the host) */
	E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BADVERSION,              /* e_ident[EI_VERSION] != EV_CURRENT */
	E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BADVERSION2,             /* e_version != EV_CURRENT */
	E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BADTYPE,                 /* e_type != ET_EXEC (or in the case of a driver: e_type != ET_DYN) */
	E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BADMACH,                 /* e_machine != EM_* (as required by the host) */
	E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BADHEADER,               /* e_ehsize < offsetafter(ElfW(Ehdr), e_phnum) */
	E_NOT_EXECUTABLE_FAULTY_REASON_ELF_NOSEGMENTS,              /* e_phnum == 0 */
	E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BADSEGMENTS,             /* e_phentsize != sizeof(ElfW(Phdr)) */
	E_NOT_EXECUTABLE_FAULTY_REASON_ELF_TOOMANYSEGMENTS,         /* e_phnum > ... (hard limit imposed by the host; i386/x86_64 uses 64 for this) */
	E_NOT_EXECUTABLE_FAULTY_REASON_ELF_UNALIGNEDSEGMENT,        /* (p_offset & (getpagesize() - 1)) != (p_vaddr & (getpagesize() - 1)) */
	E_NOT_EXECUTABLE_FAULTY_REASON_ELF_SEGMENTOVERLAP,          /* Loading of static binary failed due to overlapping segments */
	E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BADABI,                  /* [unsigned char abi] Unsupported `EI_OSABI' for the indicated architecture */
	E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BADABIVERSION,           /* [unsigned char abi, unsigned char abiver] Unsupported `EI_ABIVERSION' for the indicated `EI_OSABI' */
	E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_HEADERS,             /* Only when loading drivers: The program headers pointer is out-of-bounds */
	E_NOT_EXECUTABLE_FAULTY_REASON_ELF_NO_DYNAMIC,              /* Only when loading drivers: No `PT_DYNAMIC' program header found */
	E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_DYNAMIC,             /* Only when loading drivers: The `PT_DYNAMIC' program header is out-of-bounds */
	E_NOT_EXECUTABLE_FAULTY_REASON_ELF_NO_SONAME,               /* Only when loading drivers: No `DT_SONAME' or `DT_STRTAB' tag found */
	E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_SONAME,              /* Only when loading drivers: The `DT_STRTAB' tag isn't mapped, or the `DT_SONAME' tag is out-of-bounds */
	E_NOT_EXECUTABLE_FAULTY_REASON_ELF_TOOMANYSECTIONS,         /* Only when loading drivers: [ElfW(Half) e_shnum] e_shnum > ... (hard limit imposed by the host; by default, limit is 128) */
	E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_SHENT,               /* Only when loading drivers: [ElfW(Half) e_shentsize] The `e_shentsize' fields doesn't equal `sizeof(ElfW(Shdr))' */
	E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_SHSTRNDX,            /* Only when loading drivers: [ElfW(Half) e_shstrndx, ElfW(Half) e_shnum] The `e_shstrndx' field of the header is out-of-bounds */
	E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_SHOFF,               /* Only when loading drivers: [uintptr_t e_shoff, size_t e_shnum, size_t image_size] The `e_shoff' / `e_shnum' fields of the header are out-of-bounds */
	E_NOT_EXECUTABLE_FAULTY_REASON_ELF_NOBITS_SHSTRTAB,         /* Only when loading drivers: [ElfW(Half) e_shstrndx] The `.shstrtab' section header has a type `SHT_NOBITS' */
	E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_SHSTRTAB,            /* Only when loading drivers: [uintptr_t sh_offset, size_t sh_size, size_t image_size] The `.shstrtab' section header points out-of-bounds */
	E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_PHDR_VADDR,          /* Only when loading drivers: [uintptr_t p_vaddr, size_t p_memsz] The virtual address bounds of a program header overflow */
	E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_PHDR_ALIGN,          /* Only when loading drivers: [size_t min_alignment] The alignment requirement of a program header isn't a power-of-2 */
	E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_PHDR_OFFSET,         /* Only when loading drivers: [ElfW(Off) p_offset, size_t p_filesz] Bad program header file-offset/size. */
	E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_PHDR_FSIZE,          /* Only when loading drivers: [size_t p_filesz, size_t p_memsz] Bad file-/mem-size interaction. */
	E_NOT_EXECUTABLE_FAULTY_REASON_ELF_NALLOC_EH_FRAME,         /* Only when loading drivers: [ElfW(Half) shndx] The `.eh_frame' section doesn't have the `SHF_ALLOC' flag set. */
	E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_EH_FRAME,            /* Only when loading drivers: [uintptr_t sh_addr, size_t sh_size] The `.eh_frame' section address points out-of-bounds */
	E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_DYNSTR,              /* Only when loading drivers: [uintptr_t tagval] The `DT_STRTAB' tag is mapped out-of-bounds */
	E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_SYMHASH,             /* Only when loading drivers: [uintptr_t tagval] The `DT_HASH' tag is mapped out-of-bounds */
	E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_GNUSYMHASH,          /* Only when loading drivers: [uintptr_t tagval] The `DT_GNU_HASH' tag is mapped out-of-bounds */
	E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_DYNSYM,              /* Only when loading drivers: [uintptr_t tagval] The `DT_DYNSYM' tag is mapped out-of-bounds */
	E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_SYMENT,              /* Only when loading drivers: [uintptr_t tagval] The `DT_SYMENT' tag contains an invalid value */
	E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_RELAENT,             /* Only when loading drivers: [uintptr_t tagval] The `DT_RELAENT' tag contains an invalid value */
	E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_RELENT,              /* Only when loading drivers: [uintptr_t tagval] The `DT_RELENT' tag contains an invalid value */
	E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_INIT_FUNC,           /* Only when loading drivers: [intptr_t reladdr] A constructor callback is located out-of-bounds */
	E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_NEEDED,              /* Only when loading drivers: [size_t depid] Bad dependency (either an index miss-match, or a bad filename) */
	E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_SYMBOL,              /* Only when loading drivers: [uintptr_t symid] Bad symbol index (symbol index is out-of-bounds) */
	E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_SYMNAME,             /* Only when loading drivers: [uintptr_t st_name] Bad symbol name (symbol name is out-of-bounds) */
	E_NOT_EXECUTABLE_FAULTY_REASON_ELF_NO_SYMBOL,               /* Only when loading drivers: [uintptr_t st_name] Relocation against unknown symbol (s.a. system log) */
	E_NOT_EXECUTABLE_FAULTY_REASON_ELF_ARGCASH_X_BAD_NIBBLE,    /* Only when loading drivers: Incomplete hex-nibble in hex-based arg$ driver argument. */
	E_NOT_EXECUTABLE_FAULTY_REASON_ELF_ARGCASH_X_TOO_LONG,      /* Only when loading drivers: [size_t req_bytes, size_t given_bytes] Value of hex-based arg$ argument too long. */
	E_NOT_EXECUTABLE_FAULTY_REASON_ELF_ARGCASH_D_ECANCELED,     /* Only when loading drivers: strtoimax_r() returned `ECANCELED' when parsing an integer argument. */
	E_NOT_EXECUTABLE_FAULTY_REASON_ELF_ARGCASH_D_ERANGE,        /* Only when loading drivers: strtoimax_r() returned `ERANGE' when parsing an integer argument. */
	E_NOT_EXECUTABLE_FAULTY_REASON_ELF_ARGCASH_D_EINVAL,        /* Only when loading drivers: strtoimax_r() returned `EINVAL' when parsing an integer argument. */
	E_NOT_EXECUTABLE_FAULTY_REASON_SHEBANG_NO_INTERP = 1024,    /* No interpreter given (script file starts with #!, but no filename found) */
	E_NOT_EXECUTABLE_FAULTY_REASON_SHEBANG_TRUNC,               /* Total length of the #!-line is too long */
#ifdef LIBUNWIND_HAVE_ARM_EXIDX
	E_NOT_EXECUTABLE_FAULTY_REASON_ELF_NALLOC_ARM_EXIDX = 4096, /* Only when loading drivers: [ElfW(Half) shndx] The `.ARM.exidx' section doesn't have the `SHF_ALLOC' flag set. */
	E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_ARM_EXIDX,           /* Only when loading drivers: [uintptr_t p_vaddr/sh_addr, size_t p_memsz/sh_size] The `.ARM.exidx' section address points out-of-bounds */
#endif /* LIBUNWIND_HAVE_ARM_EXIDX */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BADCLASS             E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BADCLASS             /* e_ident[EI_CLASS] != ELFCLASS32/64 (as required by the host) */
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BADORDER             E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BADORDER             /* e_ident[EI_DATA] != ELFDATA2LSB/MSB (as required by the host) */
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BADVERSION           E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BADVERSION           /* e_ident[EI_VERSION] != EV_CURRENT */
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BADVERSION2          E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BADVERSION2          /* e_version != EV_CURRENT */
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BADTYPE              E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BADTYPE              /* e_type != ET_EXEC (or in the case of a driver: e_type != ET_DYN) */
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BADMACH              E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BADMACH              /* e_machine != EM_* (as required by the host) */
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BADHEADER            E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BADHEADER            /* e_ehsize < offsetafter(ElfW(Ehdr), e_phnum) */
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_NOSEGMENTS           E_NOT_EXECUTABLE_FAULTY_REASON_ELF_NOSEGMENTS           /* e_phnum == 0 */
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BADSEGMENTS          E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BADSEGMENTS          /* e_phentsize != sizeof(ElfW(Phdr)) */
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_TOOMANYSEGMENTS      E_NOT_EXECUTABLE_FAULTY_REASON_ELF_TOOMANYSEGMENTS      /* e_phnum > ... (hard limit imposed by the host; i386/x86_64 uses 64 for this) */
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_UNALIGNEDSEGMENT     E_NOT_EXECUTABLE_FAULTY_REASON_ELF_UNALIGNEDSEGMENT     /* (p_offset & (getpagesize() - 1)) != (p_vaddr & (getpagesize() - 1)) */
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_SEGMENTOVERLAP       E_NOT_EXECUTABLE_FAULTY_REASON_ELF_SEGMENTOVERLAP       /* Loading of static binary failed due to overlapping segments */
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BADABI               E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BADABI               /* [unsigned char abi] Unsupported `EI_OSABI' for the indicated architecture */
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BADABIVERSION        E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BADABIVERSION        /* [unsigned char abi, unsigned char abiver] Unsupported `EI_ABIVERSION' for the indicated `EI_OSABI' */
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_HEADERS          E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_HEADERS          /* Only when loading drivers: The program headers pointer is out-of-bounds */
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_NO_DYNAMIC           E_NOT_EXECUTABLE_FAULTY_REASON_ELF_NO_DYNAMIC           /* Only when loading drivers: No `PT_DYNAMIC' program header found */
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_DYNAMIC          E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_DYNAMIC          /* Only when loading drivers: The `PT_DYNAMIC' program header is out-of-bounds */
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_NO_SONAME            E_NOT_EXECUTABLE_FAULTY_REASON_ELF_NO_SONAME            /* Only when loading drivers: No `DT_SONAME' or `DT_STRTAB' tag found */
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_SONAME           E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_SONAME           /* Only when loading drivers: The `DT_STRTAB' tag isn't mapped, or the `DT_SONAME' tag is out-of-bounds */
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_TOOMANYSECTIONS      E_NOT_EXECUTABLE_FAULTY_REASON_ELF_TOOMANYSECTIONS      /* Only when loading drivers: [ElfW(Half) e_shnum] e_shnum > ... (hard limit imposed by the host; by default, limit is 128) */
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_SHENT            E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_SHENT            /* Only when loading drivers: [ElfW(Half) e_shentsize] The `e_shentsize' fields doesn't equal `sizeof(ElfW(Shdr))' */
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_SHSTRNDX         E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_SHSTRNDX         /* Only when loading drivers: [ElfW(Half) e_shstrndx, ElfW(Half) e_shnum] The `e_shstrndx' field of the header is out-of-bounds */
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_SHOFF            E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_SHOFF            /* Only when loading drivers: [uintptr_t e_shoff, size_t e_shnum, size_t image_size] The `e_shoff' / `e_shnum' fields of the header are out-of-bounds */
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_NOBITS_SHSTRTAB      E_NOT_EXECUTABLE_FAULTY_REASON_ELF_NOBITS_SHSTRTAB      /* Only when loading drivers: [ElfW(Half) e_shstrndx] The `.shstrtab' section header has a type `SHT_NOBITS' */
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_SHSTRTAB         E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_SHSTRTAB         /* Only when loading drivers: [uintptr_t sh_offset, size_t sh_size, size_t image_size] The `.shstrtab' section header points out-of-bounds */
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_PHDR_VADDR       E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_PHDR_VADDR       /* Only when loading drivers: [uintptr_t p_vaddr, size_t p_memsz] The virtual address bounds of a program header overflow */
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_PHDR_ALIGN       E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_PHDR_ALIGN       /* Only when loading drivers: [size_t min_alignment] The alignment requirement of a program header isn't a power-of-2 */
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_PHDR_OFFSET      E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_PHDR_OFFSET      /* Only when loading drivers: [ElfW(Off) p_offset, size_t p_filesz] Bad program header file-offset/size. */
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_PHDR_FSIZE       E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_PHDR_FSIZE       /* Only when loading drivers: [size_t p_filesz, size_t p_memsz] Bad file-/mem-size interaction. */
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_NALLOC_EH_FRAME      E_NOT_EXECUTABLE_FAULTY_REASON_ELF_NALLOC_EH_FRAME      /* Only when loading drivers: [ElfW(Half) shndx] The `.eh_frame' section doesn't have the `SHF_ALLOC' flag set. */
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_EH_FRAME         E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_EH_FRAME         /* Only when loading drivers: [uintptr_t sh_addr, size_t sh_size] The `.eh_frame' section address points out-of-bounds */
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_DYNSTR           E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_DYNSTR           /* Only when loading drivers: [uintptr_t tagval] The `DT_STRTAB' tag is mapped out-of-bounds */
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_SYMHASH          E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_SYMHASH          /* Only when loading drivers: [uintptr_t tagval] The `DT_HASH' tag is mapped out-of-bounds */
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_GNUSYMHASH       E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_GNUSYMHASH       /* Only when loading drivers: [uintptr_t tagval] The `DT_GNU_HASH' tag is mapped out-of-bounds */
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_DYNSYM           E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_DYNSYM           /* Only when loading drivers: [uintptr_t tagval] The `DT_DYNSYM' tag is mapped out-of-bounds */
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_SYMENT           E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_SYMENT           /* Only when loading drivers: [uintptr_t tagval] The `DT_SYMENT' tag contains an invalid value */
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_RELAENT          E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_RELAENT          /* Only when loading drivers: [uintptr_t tagval] The `DT_RELAENT' tag contains an invalid value */
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_RELENT           E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_RELENT           /* Only when loading drivers: [uintptr_t tagval] The `DT_RELENT' tag contains an invalid value */
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_INIT_FUNC        E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_INIT_FUNC        /* Only when loading drivers: [intptr_t reladdr] A constructor callback is located out-of-bounds */
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_NEEDED           E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_NEEDED           /* Only when loading drivers: [size_t depid] Bad dependency (either an index miss-match, or a bad filename) */
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_SYMBOL           E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_SYMBOL           /* Only when loading drivers: [uintptr_t symid] Bad symbol index (symbol index is out-of-bounds) */
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_SYMNAME          E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_SYMNAME          /* Only when loading drivers: [uintptr_t st_name] Bad symbol name (symbol name is out-of-bounds) */
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_NO_SYMBOL            E_NOT_EXECUTABLE_FAULTY_REASON_ELF_NO_SYMBOL            /* Only when loading drivers: [uintptr_t st_name] Relocation against unknown symbol (s.a. system log) */
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_ARGCASH_X_BAD_NIBBLE E_NOT_EXECUTABLE_FAULTY_REASON_ELF_ARGCASH_X_BAD_NIBBLE /* Only when loading drivers: Incomplete hex-nibble in hex-based arg$ driver argument. */
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_ARGCASH_X_TOO_LONG   E_NOT_EXECUTABLE_FAULTY_REASON_ELF_ARGCASH_X_TOO_LONG   /* Only when loading drivers: [size_t req_bytes, size_t given_bytes] Value of hex-based arg$ argument too long. */
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_ARGCASH_D_ECANCELED  E_NOT_EXECUTABLE_FAULTY_REASON_ELF_ARGCASH_D_ECANCELED  /* Only when loading drivers: strtoimax_r() returned `ECANCELED' when parsing an integer argument. */
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_ARGCASH_D_ERANGE     E_NOT_EXECUTABLE_FAULTY_REASON_ELF_ARGCASH_D_ERANGE     /* Only when loading drivers: strtoimax_r() returned `ERANGE' when parsing an integer argument. */
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_ARGCASH_D_EINVAL     E_NOT_EXECUTABLE_FAULTY_REASON_ELF_ARGCASH_D_EINVAL     /* Only when loading drivers: strtoimax_r() returned `EINVAL' when parsing an integer argument. */
#define E_NOT_EXECUTABLE_FAULTY_REASON_SHEBANG_NO_INTERP        E_NOT_EXECUTABLE_FAULTY_REASON_SHEBANG_NO_INTERP        /* No interpreter given (script file starts with #!, but no filename found) */
#define E_NOT_EXECUTABLE_FAULTY_REASON_SHEBANG_TRUNC            E_NOT_EXECUTABLE_FAULTY_REASON_SHEBANG_TRUNC            /* Total length of the #!-line is too long */
#ifdef LIBUNWIND_HAVE_ARM_EXIDX
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_NALLOC_ARM_EXIDX     E_NOT_EXECUTABLE_FAULTY_REASON_ELF_NALLOC_ARM_EXIDX     /* Only when loading drivers: [ElfW(Half) shndx] The `.ARM.exidx' section doesn't have the `SHF_ALLOC' flag set. */
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_ARM_EXIDX        E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_ARM_EXIDX        /* Only when loading drivers: [uintptr_t p_vaddr/sh_addr, size_t p_memsz/sh_size] The `.ARM.exidx' section address points out-of-bounds */
#endif /* LIBUNWIND_HAVE_ARM_EXIDX */
#else /* __COMPILER_PREFERR_ENUMS */
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BADCLASS             1    /* e_ident[EI_CLASS] != ELFCLASS32/64 (as required by the host) */
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BADORDER             2    /* e_ident[EI_DATA] != ELFDATA2LSB/MSB (as required by the host) */
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BADVERSION           3    /* e_ident[EI_VERSION] != EV_CURRENT */
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BADVERSION2          4    /* e_version != EV_CURRENT */
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BADTYPE              5    /* e_type != ET_EXEC (or in the case of a driver: e_type != ET_DYN) */
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BADMACH              6    /* e_machine != EM_* (as required by the host) */
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BADHEADER            7    /* e_ehsize < offsetafter(ElfW(Ehdr), e_phnum) */
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_NOSEGMENTS           8    /* e_phnum == 0 */
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BADSEGMENTS          9    /* e_phentsize != sizeof(ElfW(Phdr)) */
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_TOOMANYSEGMENTS      10   /* e_phnum > ... (hard limit imposed by the host; i386/x86_64 uses 64 for this) */
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_UNALIGNEDSEGMENT     11   /* (p_offset & (getpagesize() - 1)) != (p_vaddr & (getpagesize() - 1)) */
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_SEGMENTOVERLAP       12   /* Loading of static binary failed due to overlapping segments */
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BADABI               13   /* [unsigned char abi] Unsupported `EI_OSABI' for the indicated architecture */
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BADABIVERSION        14   /* [unsigned char abi, unsigned char abiver] Unsupported `EI_ABIVERSION' for the indicated `EI_OSABI' */
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_HEADERS          15   /* Only when loading drivers: The program headers pointer is out-of-bounds */
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_NO_DYNAMIC           16   /* Only when loading drivers: No `PT_DYNAMIC' program header found */
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_DYNAMIC          17   /* Only when loading drivers: The `PT_DYNAMIC' program header is out-of-bounds */
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_NO_SONAME            18   /* Only when loading drivers: No `DT_SONAME' or `DT_STRTAB' tag found */
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_SONAME           19   /* Only when loading drivers: The `DT_STRTAB' tag isn't mapped, or the `DT_SONAME' tag is out-of-bounds */
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_TOOMANYSECTIONS      20   /* Only when loading drivers: [ElfW(Half) e_shnum] e_shnum > ... (hard limit imposed by the host; by default, limit is 128) */
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_SHENT            21   /* Only when loading drivers: [ElfW(Half) e_shentsize] The `e_shentsize' fields doesn't equal `sizeof(ElfW(Shdr))' */
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_SHSTRNDX         22   /* Only when loading drivers: [ElfW(Half) e_shstrndx, ElfW(Half) e_shnum] The `e_shstrndx' field of the header is out-of-bounds */
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_SHOFF            23   /* Only when loading drivers: [uintptr_t e_shoff, size_t e_shnum, size_t image_size] The `e_shoff' / `e_shnum' fields of the header are out-of-bounds */
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_NOBITS_SHSTRTAB      24   /* Only when loading drivers: [ElfW(Half) e_shstrndx] The `.shstrtab' section header has a type `SHT_NOBITS' */
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_SHSTRTAB         25   /* Only when loading drivers: [uintptr_t sh_offset, size_t sh_size, size_t image_size] The `.shstrtab' section header points out-of-bounds */
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_PHDR_VADDR       26   /* Only when loading drivers: [uintptr_t p_vaddr, size_t p_memsz] The virtual address bounds of a program header overflow */
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_PHDR_ALIGN       27   /* Only when loading drivers: [size_t min_alignment] The alignment requirement of a program header isn't a power-of-2 */
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_PHDR_OFFSET      28   /* Only when loading drivers: [ElfW(Off) p_offset, size_t p_filesz] Bad program header file-offset/size. */
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_PHDR_FSIZE       29   /* Only when loading drivers: [size_t p_filesz, size_t p_memsz] Bad file-/mem-size interaction. */
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_NALLOC_EH_FRAME      30   /* Only when loading drivers: [ElfW(Half) shndx] The `.eh_frame' section doesn't have the `SHF_ALLOC' flag set. */
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_EH_FRAME         31   /* Only when loading drivers: [uintptr_t sh_addr, size_t sh_size] The `.eh_frame' section address points out-of-bounds */
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_DYNSTR           32   /* Only when loading drivers: [uintptr_t tagval] The `DT_STRTAB' tag is mapped out-of-bounds */
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_SYMHASH          33   /* Only when loading drivers: [uintptr_t tagval] The `DT_HASH' tag is mapped out-of-bounds */
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_GNUSYMHASH       34   /* Only when loading drivers: [uintptr_t tagval] The `DT_GNU_HASH' tag is mapped out-of-bounds */
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_DYNSYM           35   /* Only when loading drivers: [uintptr_t tagval] The `DT_DYNSYM' tag is mapped out-of-bounds */
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_SYMENT           36   /* Only when loading drivers: [uintptr_t tagval] The `DT_SYMENT' tag contains an invalid value */
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_RELAENT          37   /* Only when loading drivers: [uintptr_t tagval] The `DT_RELAENT' tag contains an invalid value */
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_RELENT           38   /* Only when loading drivers: [uintptr_t tagval] The `DT_RELENT' tag contains an invalid value */
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_INIT_FUNC        39   /* Only when loading drivers: [intptr_t reladdr] A constructor callback is located out-of-bounds */
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_NEEDED           40   /* Only when loading drivers: [size_t depid] Bad dependency (either an index miss-match, or a bad filename) */
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_SYMBOL           41   /* Only when loading drivers: [uintptr_t symid] Bad symbol index (symbol index is out-of-bounds) */
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_SYMNAME          42   /* Only when loading drivers: [uintptr_t st_name] Bad symbol name (symbol name is out-of-bounds) */
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_NO_SYMBOL            43   /* Only when loading drivers: [uintptr_t st_name] Relocation against unknown symbol (s.a. system log) */
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_ARGCASH_X_BAD_NIBBLE 44   /* Only when loading drivers: Incomplete hex-nibble in hex-based arg$ driver argument. */
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_ARGCASH_X_TOO_LONG   45   /* Only when loading drivers: [size_t req_bytes, size_t given_bytes] Value of hex-based arg$ argument too long. */
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_ARGCASH_D_ECANCELED  46   /* Only when loading drivers: strtoimax_r() returned `ECANCELED' when parsing an integer argument. */
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_ARGCASH_D_ERANGE     47   /* Only when loading drivers: strtoimax_r() returned `ERANGE' when parsing an integer argument. */
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_ARGCASH_D_EINVAL     48   /* Only when loading drivers: strtoimax_r() returned `EINVAL' when parsing an integer argument. */
#define E_NOT_EXECUTABLE_FAULTY_REASON_SHEBANG_NO_INTERP        1024 /* No interpreter given (script file starts with #!, but no filename found) */
#define E_NOT_EXECUTABLE_FAULTY_REASON_SHEBANG_TRUNC            1025 /* Total length of the #!-line is too long */
#ifdef LIBUNWIND_HAVE_ARM_EXIDX
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_NALLOC_ARM_EXIDX     4096 /* Only when loading drivers: [ElfW(Half) shndx] The `.ARM.exidx' section doesn't have the `SHF_ALLOC' flag set. */
#define E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BAD_ARM_EXIDX        4097 /* Only when loading drivers: [uintptr_t p_vaddr/sh_addr, size_t p_memsz/sh_size] The `.ARM.exidx' section address points out-of-bounds */
#endif /* LIBUNWIND_HAVE_ARM_EXIDX */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/



__DECL_END

#endif /* !_KOS_EXCEPT_REASON_NOEXEC_H */
