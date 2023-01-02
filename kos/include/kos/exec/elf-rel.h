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
#ifndef _KOS_EXEC_ELF_REL_H
#define _KOS_EXEC_ELF_REL_H 1

#include <kos/exec/asm/elf-rel.h>

#if defined(ELF_ARCH_R_NONE) && !defined(ELF_ARCH_CASE_R_NONE)
#define ELF_ARCH_CASE_R_NONE case ELF_ARCH_R_NONE
#endif /* ELF_ARCH_R_NONE && !ELF_ARCH_CASE_R_NONE */

#if defined(ELF_ARCH_R_8) && !defined(ELF_ARCH_CASE_R_8)
#define ELF_ARCH_CASE_R_8 case ELF_ARCH_R_8
#endif /* ELF_ARCH_R_8 && !ELF_ARCH_CASE_R_8 */

#if defined(ELF_ARCH_R_8S) && !defined(ELF_ARCH_CASE_R_8S)
#define ELF_ARCH_CASE_R_8S case ELF_ARCH_R_8S
#endif /* ELF_ARCH_R_8S && !ELF_ARCH_CASE_R_8S */

#if defined(ELF_ARCH_R_PC8) && !defined(ELF_ARCH_CASE_R_PC8)
#define ELF_ARCH_CASE_R_PC8 case ELF_ARCH_R_PC8
#endif /* ELF_ARCH_R_PC8 && !ELF_ARCH_CASE_R_PC8 */

#if defined(ELF_ARCH_R_16) && !defined(ELF_ARCH_CASE_R_16)
#define ELF_ARCH_CASE_R_16 case ELF_ARCH_R_16
#endif /* ELF_ARCH_R_16 && !ELF_ARCH_CASE_R_16 */

#if defined(ELF_ARCH_R_PC16) && !defined(ELF_ARCH_CASE_R_PC16)
#define ELF_ARCH_CASE_R_PC16 case ELF_ARCH_R_PC16
#endif /* ELF_ARCH_R_PC16 && !ELF_ARCH_CASE_R_PC16 */

#if defined(ELF_ARCH_R_32) && !defined(ELF_ARCH_CASE_R_32)
#define ELF_ARCH_CASE_R_32 case ELF_ARCH_R_32
#endif /* ELF_ARCH_R_32 && !ELF_ARCH_CASE_R_32 */

#if defined(ELF_ARCH_R_PC32) && !defined(ELF_ARCH_CASE_R_PC32)
#define ELF_ARCH_CASE_R_PC32 case ELF_ARCH_R_PC32
#endif /* ELF_ARCH_R_PC32 && !ELF_ARCH_CASE_R_PC32 */

#if defined(ELF_ARCH_R_64) && !defined(ELF_ARCH_CASE_R_64)
#define ELF_ARCH_CASE_R_64 case ELF_ARCH_R_64
#endif /* ELF_ARCH_R_64 && !ELF_ARCH_CASE_R_64 */

#if defined(ELF_ARCH_R_PC64) && !defined(ELF_ARCH_CASE_R_PC64)
#define ELF_ARCH_CASE_R_PC64 case ELF_ARCH_R_PC64
#endif /* ELF_ARCH_R_PC64 && !ELF_ARCH_CASE_R_PC64 */

#if defined(ELF_ARCH_R_COPY) && !defined(ELF_ARCH_CASE_R_COPY)
#define ELF_ARCH_CASE_R_COPY case ELF_ARCH_R_COPY
#endif /* ELF_ARCH_R_COPY && !ELF_ARCH_CASE_R_COPY */

#if defined(ELF_ARCH_R_GLOB_DAT) && !defined(ELF_ARCH_CASE_R_GLOB_DAT)
#define ELF_ARCH_CASE_R_GLOB_DAT case ELF_ARCH_R_GLOB_DAT
#endif /* ELF_ARCH_R_GLOB_DAT && !ELF_ARCH_CASE_R_GLOB_DAT */

#if defined(ELF_ARCH_R_RELATIVE32) && !defined(ELF_ARCH_CASE_R_RELATIVE32)
#define ELF_ARCH_CASE_R_RELATIVE32 case ELF_ARCH_R_RELATIVE32
#endif /* ELF_ARCH_R_RELATIVE32 && !ELF_ARCH_CASE_R_RELATIVE32 */

#if defined(ELF_ARCH_R_RELATIVE64) && !defined(ELF_ARCH_CASE_R_RELATIVE64)
#define ELF_ARCH_CASE_R_RELATIVE64 case ELF_ARCH_R_RELATIVE64
#endif /* ELF_ARCH_R_RELATIVE64 && !ELF_ARCH_CASE_R_RELATIVE64 */

#if defined(ELF_ARCH_R_DTPMOD32) && !defined(ELF_ARCH_CASE_R_DTPMOD32)
#define ELF_ARCH_CASE_R_DTPMOD32 case ELF_ARCH_R_DTPMOD32
#endif /* ELF_ARCH_R_DTPMOD32 && !ELF_ARCH_CASE_R_DTPMOD32 */

#if defined(ELF_ARCH_R_DTPOFF32) && !defined(ELF_ARCH_CASE_R_DTPOFF32)
#define ELF_ARCH_CASE_R_DTPOFF32 case ELF_ARCH_R_DTPOFF32
#endif /* ELF_ARCH_R_DTPOFF32 && !ELF_ARCH_CASE_R_DTPOFF32 */

#if defined(ELF_ARCH_R_NEG_TPOFF32) && !defined(ELF_ARCH_CASE_R_NEG_TPOFF32)
#define ELF_ARCH_CASE_R_NEG_TPOFF32 case ELF_ARCH_R_NEG_TPOFF32 /* `*addr = -(dm_tlsstoff + value)' */
#endif /* ELF_ARCH_R_NEG_TPOFF32 && !ELF_ARCH_CASE_R_NEG_TPOFF32 */

#if defined(ELF_ARCH_R_TPOFF32) && !defined(ELF_ARCH_CASE_R_TPOFF32)
#define ELF_ARCH_CASE_R_TPOFF32 case ELF_ARCH_R_TPOFF32 /* `*addr = dm_tlsstoff + value' */
#endif /* ELF_ARCH_R_TPOFF32 && !ELF_ARCH_CASE_R_TPOFF32 */

#if defined(ELF_ARCH_R_DTPMOD64) && !defined(ELF_ARCH_CASE_R_DTPMOD64)
#define ELF_ARCH_CASE_R_DTPMOD64 case ELF_ARCH_R_DTPMOD64
#endif /* ELF_ARCH_R_DTPMOD64 && !ELF_ARCH_CASE_R_DTPMOD64 */

#if defined(ELF_ARCH_R_DTPOFF64) && !defined(ELF_ARCH_CASE_R_DTPOFF64)
#define ELF_ARCH_CASE_R_DTPOFF64 case ELF_ARCH_R_DTPOFF64
#endif /* ELF_ARCH_R_DTPOFF64 && !ELF_ARCH_CASE_R_DTPOFF64 */

#if defined(ELF_ARCH_R_NEG_TPOFF64) && !defined(ELF_ARCH_CASE_R_NEG_TPOFF64)
#define ELF_ARCH_CASE_R_NEG_TPOFF64 case ELF_ARCH_R_NEG_TPOFF64 /* `*addr = -(dm_tlsstoff + value)' */
#endif /* ELF_ARCH_R_NEG_TPOFF64 && !ELF_ARCH_CASE_R_NEG_TPOFF64 */

#if defined(ELF_ARCH_R_TPOFF64) && !defined(ELF_ARCH_CASE_R_TPOFF64)
#define ELF_ARCH_CASE_R_TPOFF64 case ELF_ARCH_R_TPOFF64 /* `*addr = dm_tlsstoff + value' */
#endif /* ELF_ARCH_R_TPOFF64 && !ELF_ARCH_CASE_R_TPOFF64 */

#if defined(ELF_ARCH_R_SIZE32) && !defined(ELF_ARCH_CASE_R_SIZE32)
#define ELF_ARCH_CASE_R_SIZE32 case ELF_ARCH_R_SIZE32
#endif /* ELF_ARCH_R_SIZE32 && !ELF_ARCH_CASE_R_SIZE32 */

#if defined(ELF_ARCH_R_SIZE64) && !defined(ELF_ARCH_CASE_R_SIZE64)
#define ELF_ARCH_CASE_R_SIZE64 case ELF_ARCH_R_SIZE64
#endif /* ELF_ARCH_R_SIZE64 && !ELF_ARCH_CASE_R_SIZE64 */

#if defined(ELF_ARCH_R_TLSDESC) && !defined(ELF_ARCH_CASE_R_TLSDESC)
#define ELF_ARCH_CASE_R_TLSDESC case ELF_ARCH_R_TLSDESC
#endif /* ELF_ARCH_R_TLSDESC && !ELF_ARCH_CASE_R_TLSDESC */

#if defined(ELF_ARCH_R_IRELATIVE32) && !defined(ELF_ARCH_CASE_R_IRELATIVE32)
#define ELF_ARCH_CASE_R_IRELATIVE32 case ELF_ARCH_R_IRELATIVE32
#endif /* ELF_ARCH_R_IRELATIVE32 && !ELF_ARCH_CASE_R_IRELATIVE32 */

#if defined(ELF_ARCH_R_IRELATIVE64) && !defined(ELF_ARCH_CASE_R_IRELATIVE64)
#define ELF_ARCH_CASE_R_IRELATIVE64 case ELF_ARCH_R_IRELATIVE64
#endif /* ELF_ARCH_R_IRELATIVE64 && !ELF_ARCH_CASE_R_IRELATIVE64 */

#ifdef ELF_ARCH_R_JMP_SLOT
#ifndef ELF_ARCH_CASE_R_JMP_SLOT
#define ELF_ARCH_CASE_R_JMP_SLOT case ELF_ARCH_R_JMP_SLOT
#endif /* !ELF_ARCH_CASE_R_JMP_SLOT */
#ifndef ELF_ARCH_IS_R_JMP_SLOT
#define ELF_ARCH_IS_R_JMP_SLOT(x) ((x) == ELF_ARCH_R_JMP_SLOT)
#endif /* !ELF_ARCH_IS_R_JMP_SLOT */
#endif /* ELF_ARCH_R_JMP_SLOT */

#endif /* !_I386_KOS_KOS_EXEC_ASM_ELF_REL_H */
