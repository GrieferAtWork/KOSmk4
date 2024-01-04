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
#ifndef _KOS_EXEC_ASM_ELF_REL_H
#define _KOS_EXEC_ASM_ELF_REL_H 1

#if 0 /* ... */
#include <elf.h>
#define ELF_ARCH_R_NONE             R_MYARCH_NONE
#define ELF_ARCH_R_8                R_MYARCH_8
#define ELF_ARCH_R_PC8              R_MYARCH_PC8
#define ELF_ARCH_R_16               R_MYARCH_16
#define ELF_ARCH_R_PC16             R_MYARCH_PC16
#define ELF_ARCH_R_32               R_MYARCH_32
#define ELF_ARCH_R_PC32             R_MYARCH_PC32
#define ELF_ARCH_R_COPY             R_MYARCH_COPY
#define ELF_ARCH_R_GLOB_DAT         R_MYARCH_GLOB_DAT
#define ELF_ARCH_R_JMP_SLOT         R_MYARCH_JMP_SLOT
#define ELF_ARCH_NAME_R_JMP_SLOT    "R_MYARCH_JMP_SLOT"
#define ELF_ARCH_R_RELATIVE32       R_MYARCH_RELATIVE
#define ELF_ARCH_R_DTPMOD32         R_MYARCH_TLS_DTPMOD32
#define ELF_ARCH_R_DTPOFF32         R_MYARCH_TLS_DTPOFF32
#define ELF_ARCH_R_NEG_TPOFF32      R_MYARCH_TLS_TPOFF32 /* `*addr = -(dm_tlsstoff + value)' */
#define ELF_ARCH_NAME_R_NEG_TPOFF32 "R_MYARCH_TLS_TPOFF32"
#define ELF_ARCH_R_TPOFF32          R_MYARCH_TLS_TPOFF /* `*addr = dm_tlsstoff + value' */
#define ELF_ARCH_NAME_R_TPOFF32     "R_MYARCH_TLS_TPOFF"
#define ELF_ARCH_R_SIZE32           R_MYARCH_SIZE32
#define ELF_ARCH_R_TLSDESC          R_MYARCH_TLS_DESC
#define ELF_ARCH_R_IRELATIVE32      R_MYARCH_IRELATIVE
#endif

#endif /* !_KOS_EXEC_ASM_ELF_REL_H */
