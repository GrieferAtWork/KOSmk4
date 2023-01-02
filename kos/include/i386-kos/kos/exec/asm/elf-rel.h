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
#ifndef _I386_KOS_KOS_EXEC_ASM_ELF_REL_H
#define _I386_KOS_KOS_EXEC_ASM_ELF_REL_H 1

#include <hybrid/host.h>

#include <elf.h>

#ifdef __x86_64__
#define ELF_ARCH_R_NONE             R_X86_64_NONE
#define ELF_ARCH_R_8                R_X86_64_8
#define ELF_ARCH_R_PC8              R_X86_64_PC8
#define ELF_ARCH_R_16               R_X86_64_16
#define ELF_ARCH_R_PC16             R_X86_64_PC16
#define ELF_ARCH_R_32               R_X86_64_32
#define ELF_ARCH_R_32S              R_X86_64_32S
#define ELF_ARCH_R_PC32             R_X86_64_PC32
#define ELF_ARCH_R_64               R_X86_64_64
#define ELF_ARCH_R_PC64             R_X86_64_PC64
#define ELF_ARCH_R_COPY             R_X86_64_COPY
#define ELF_ARCH_R_GLOB_DAT         R_X86_64_GLOB_DAT
#define ELF_ARCH_R_JMP_SLOT         R_X86_64_JMP_SLOT
#define ELF_ARCH_NAME_R_JMP_SLOT    "R_X86_64_JMP_SLOT"
#if __SIZEOF_POINTER__ == 4
#define ELF_ARCH_R_RELATIVE32       R_X86_64_RELATIVE
#define ELF_ARCH_R_RELATIVE64       R_X86_64_RELATIVE64
#else /* __SIZEOF_POINTER__ == 4 */
#define ELF_ARCH_CASE_R_RELATIVE64  case R_X86_64_RELATIVE: case R_X86_64_RELATIVE64
#define ELF_ARCH_IS_R_RELATIVE64(x) ((x) == R_X86_64_RELATIVE || (x) == R_X86_64_RELATIVE64)
#endif /* __SIZEOF_POINTER__ != 4 */
#define ELF_ARCH_R_IRELATIVE64      R_X86_64_IRELATIVE
#define ELF_ARCH_R_SIZE32           R_X86_64_SIZE32
#define ELF_ARCH_R_SIZE64           R_X86_64_SIZE64
#define ELF_ARCH_R_DTPMOD64         R_X86_64_DTPMOD64
#define ELF_ARCH_R_DTPOFF64         R_X86_64_DTPOFF64
#define ELF_ARCH_R_TPOFF64          R_X86_64_TPOFF64 /* `*addr = value - dm_tlsstoff' */
#define ELF_ARCH_NAME_R_TPOFF64     "R_X86_64_TPOFF64"
#define ELF_ARCH_R_DTPOFF32         R_X86_64_DTPOFF32
#define ELF_ARCH_R_TPOFF32          R_X86_64_TPOFF32 /* `*addr = value - dm_tlsstoff' */
#define ELF_ARCH_NAME_R_TPOFF32     "R_X86_64_TPOFF32"
#define ELF_ARCH_R_TLSDESC          R_X86_64_TLSDESC
#else /* __x86_64__ */
#define ELF_ARCH_R_NONE             R_386_NONE
#define ELF_ARCH_R_8                R_386_8
#define ELF_ARCH_R_PC8              R_386_PC8
#define ELF_ARCH_R_16               R_386_16
#define ELF_ARCH_R_PC16             R_386_PC16
#define ELF_ARCH_R_32               R_386_32
#define ELF_ARCH_R_PC32             R_386_PC32
#define ELF_ARCH_R_COPY             R_386_COPY
#define ELF_ARCH_R_GLOB_DAT         R_386_GLOB_DAT
#define ELF_ARCH_R_JMP_SLOT         R_386_JMP_SLOT
#define ELF_ARCH_NAME_R_JMP_SLOT    "R_386_JMP_SLOT"
#define ELF_ARCH_R_RELATIVE32       R_386_RELATIVE
#define ELF_ARCH_R_DTPMOD32         R_386_TLS_DTPMOD32
#define ELF_ARCH_R_DTPOFF32         R_386_TLS_DTPOFF32
#define ELF_ARCH_R_NEG_TPOFF32      R_386_TLS_TPOFF32 /* `*addr = -(dm_tlsstoff + value)' */
#define ELF_ARCH_NAME_R_NEG_TPOFF32 "R_386_TLS_TPOFF32"
#define ELF_ARCH_R_TPOFF32          R_386_TLS_TPOFF /* `*addr = dm_tlsstoff + value' */
#define ELF_ARCH_NAME_R_TPOFF32     "R_386_TLS_TPOFF"
#define ELF_ARCH_R_SIZE32           R_386_SIZE32
#define ELF_ARCH_R_TLSDESC          R_386_TLS_DESC
#define ELF_ARCH_R_IRELATIVE32      R_386_IRELATIVE
#endif /* !__x86_64__ */

#endif /* !_I386_KOS_KOS_EXEC_ASM_ELF_REL_H */
