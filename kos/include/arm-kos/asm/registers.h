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
#ifndef _ARM_KOS_ASM_REGISTERS_H
#define _ARM_KOS_ASM_REGISTERS_H 1

#include <hybrid/typecore.h>

#define ARM_REGISTER_NONE __UINT16_C(0xffff) /* No/invalid register. */

/* TODO: Improve this  list of  registers (e.g.  there should  be  dedicated
 *       register numbers for cpsr when using under various different masks) */

/* Basic registers */
#define ARM_REGISTER_R0      0x0000 /* r0 */
#define ARM_REGISTER_R1      0x0001 /* r1 */
#define ARM_REGISTER_R2      0x0002 /* r2 */
#define ARM_REGISTER_R3      0x0003 /* r3 */
#define ARM_REGISTER_R4      0x0004 /* r4 */
#define ARM_REGISTER_R5      0x0005 /* r5 */
#define ARM_REGISTER_R6      0x0006 /* r6 */
#define ARM_REGISTER_R7      0x0007 /* r7 */
#define ARM_REGISTER_R8      0x0008 /* (current) r8 */
#define ARM_REGISTER_R9      0x0009 /* (current) r9 */
#define ARM_REGISTER_R10     0x000a /* (current) r10 */
#define ARM_REGISTER_R11     0x000b /* (current) r11 */
#define ARM_REGISTER_R12     0x000c /* (current) r12 */
#define ARM_REGISTER_SP      0x000d /* (current) r13 */
#define ARM_REGISTER_LR      0x000e /* (current) r14 */
#define ARM_REGISTER_PC      0x000f /* (current) r15 */

/* Banked/explicit registers */
#define ARM_REGISTER_R8_USR  0x0018 /* explicit user-mode r8 */
#define ARM_REGISTER_R9_USR  0x0019 /* explicit user-mode r9 */
#define ARM_REGISTER_R10_USR 0x001a /* explicit user-mode r10 */
#define ARM_REGISTER_R11_USR 0x001b /* explicit user-mode r11 */
#define ARM_REGISTER_R12_USR 0x001c /* explicit user-mode r12 */
#define ARM_REGISTER_SP_USR  0x001d /* explicit user-mode r13 */
#define ARM_REGISTER_LR_USR  0x001e /* explicit user-mode r14 */

#define ARM_REGISTER_R8_FIQ  0x0018 /* banked R8-register used instead of `ARM_REGISTER_R8_USR' in FIQ-mode */
#define ARM_REGISTER_R9_FIQ  0x0019 /* banked R9-register used instead of `ARM_REGISTER_R9_USR' in FIQ-mode */
#define ARM_REGISTER_R10_FIQ 0x001a /* banked R10-register used instead of `ARM_REGISTER_R10_USR' in FIQ-mode */
#define ARM_REGISTER_R11_FIQ 0x001b /* banked R11-register used instead of `ARM_REGISTER_R11_USR' in FIQ-mode */
#define ARM_REGISTER_R12_FIQ 0x001c /* banked R12-register used instead of `ARM_REGISTER_R12_USR' in FIQ-mode */
#define ARM_REGISTER_SP_FIQ  0x001d /* banked SP-register used instead of `ARM_REGISTER_SP_USR' in FIQ-mode */
#define ARM_REGISTER_LR_FIQ  0x001e /* banked LR-register used instead of `ARM_REGISTER_LR_USR' in FIQ-mode */

#define ARM_REGISTER_SP_IRQ  0x002d /* banked SP-register used instead of `ARM_REGISTER_SP_USR' in IRQ-mode */
#define ARM_REGISTER_LR_IRQ  0x002e /* banked LR-register used instead of `ARM_REGISTER_LR_USR' in IRQ-mode */

#define ARM_REGISTER_SP_SVC  0x003d /* banked SP-register used instead of `ARM_REGISTER_SP_USR' in SVC-mode */
#define ARM_REGISTER_LR_SVC  0x003e /* banked LR-register used instead of `ARM_REGISTER_LR_USR' in SVC-mode */

#define ARM_REGISTER_SP_ABT  0x004d /* banked SP-register used instead of `ARM_REGISTER_SP_USR' in ABT-mode */
#define ARM_REGISTER_LR_ABT  0x004e /* banked LR-register used instead of `ARM_REGISTER_LR_USR' in ABT-mode */

#define ARM_REGISTER_SP_UND  0x005d /* banked SP-register used instead of `ARM_REGISTER_SP_USR' in UND-mode */
#define ARM_REGISTER_LR_UND  0x005e /* banked LR-register used instead of `ARM_REGISTER_LR_USR' in UND-mode */

/* Misc registers */
#define ARM_REGISTER_CPSR     0xf001 /* CurrentProgramStatusRegister */
#define ARM_REGISTER_SPSR     0xf002 /* SavedProgramStatusRegister (not valid in USR-mode) */
#define ARM_REGISTER_SPSR_FIQ 0xf003 /* SPSR for FIQ-mode (old CPSR upon mode-entry) */
#define ARM_REGISTER_SPSR_IRQ 0xf004 /* SPSR for IRQ-mode (old CPSR upon mode-entry) */
#define ARM_REGISTER_SPSR_SVC 0xf005 /* SPSR for SVC-mode (old CPSR upon mode-entry) */
#define ARM_REGISTER_SPSR_ABT 0xf006 /* SPSR for ABT-mode (old CPSR upon mode-entry) */
#define ARM_REGISTER_SPSR_UND 0xf007 /* SPSR for UND-mode (old CPSR upon mode-entry) */

#define ARM_REGISTER_TLSBASE  0xfff0 /* Fake register: current user-space TLS base */

#endif /* !_ARM_KOS_ASM_REGISTERS_H */
