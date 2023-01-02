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
#ifndef _ARM_KOS_KOS_EXEC_ASM_ELF_REL_H
#define _ARM_KOS_KOS_EXEC_ASM_ELF_REL_H 1

#include <elf.h>

#define ELF_ARCH_R_NONE             R_ARM_NONE
#define ELF_ARCH_R_8                R_ARM_ABS8
#define ELF_ARCH_R_16               R_ARM_ABS16
#define ELF_ARCH_R_32               R_ARM_ABS32
#define ELF_ARCH_R_COPY             R_ARM_COPY
#define ELF_ARCH_R_GLOB_DAT         R_ARM_GLOB_DAT
#define ELF_ARCH_R_JMP_SLOT         R_ARM_JUMP_SLOT
#define ELF_ARCH_NAME_R_JMP_SLOT    "R_ARM_JUMP_SLOT"
#define ELF_ARCH_R_RELATIVE32       R_ARM_RELATIVE
#define ELF_ARCH_R_DTPMOD32         R_ARM_TLS_DTPMOD32
#define ELF_ARCH_R_DTPOFF32         R_ARM_TLS_DTPOFF32
#define ELF_ARCH_R_NEG_TPOFF32      R_ARM_TLS_TPOFF32 /* `*addr = -(dm_tlsstoff + value)' */
#define ELF_ARCH_NAME_R_NEG_TPOFF32 "R_ARM_TLS_TPOFF32"
#define ELF_ARCH_R_TLSDESC          R_ARM_TLS_DESC
#define ELF_ARCH_R_IRELATIVE32      R_ARM_IRELATIVE

#endif /* !_ARM_KOS_KOS_EXEC_ASM_ELF_REL_H */
