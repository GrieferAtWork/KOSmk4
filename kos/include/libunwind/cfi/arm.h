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
#ifndef _LIBUNWIND_CFI_ARM_H
#define _LIBUNWIND_CFI_ARM_H 1

#include "../api.h"
/**/

#include <hybrid/host.h>
#include <hybrid/typecore.h>

/* Sources:
 * - IHI0040B_aadwarf.pdf
 */


/* arm-specific CFI constants. */
#define CFI_ARM_UNWIND_GPR_REGISTER_SIZE 4
#define CFI_ARM_REGISTER_MAXSIZE         4
#define CFI_ARM_REGISTER_SIZE(regno)     4
#define CFI_ARM_UNWIND_REGISTER_EXCEPTION CFI_ARM_UNWIND_REGISTER_R0 /* TODO: !!!UNCHECKED!!! */

/* GP Registers */
#define CFI_ARM_UNWIND_REGISTER_R0  0
#define CFI_ARM_UNWIND_REGISTER_R1  1
#define CFI_ARM_UNWIND_REGISTER_R2  2
#define CFI_ARM_UNWIND_REGISTER_R3  3
#define CFI_ARM_UNWIND_REGISTER_R4  4
#define CFI_ARM_UNWIND_REGISTER_R5  5
#define CFI_ARM_UNWIND_REGISTER_R6  6
#define CFI_ARM_UNWIND_REGISTER_R7  7
#define CFI_ARM_UNWIND_REGISTER_R8  8
#define CFI_ARM_UNWIND_REGISTER_R9  9
#define CFI_ARM_UNWIND_REGISTER_R10 10
#define CFI_ARM_UNWIND_REGISTER_R11 11
#define CFI_ARM_UNWIND_REGISTER_R12 12
#define CFI_ARM_UNWIND_REGISTER_SP  13 /* The register for the CFA. */
#define CFI_ARM_UNWIND_REGISTER_LR  14 /* Link register (return address) */
#define CFI_ARM_UNWIND_REGISTER_PC  15 /* The register containing the program counter. */
#define CFI_ARM_UNWIND_REGISTER_R13 CFI_ARM_UNWIND_REGISTER_SP
#define CFI_ARM_UNWIND_REGISTER_R14 CFI_ARM_UNWIND_REGISTER_LR
#define CFI_ARM_UNWIND_REGISTER_R15 CFI_ARM_UNWIND_REGISTER_PC
/* TODO: FPU Registers */

#define CFI_ARM_UNWIND_REGISTER_CPSR 128 /* CPSR */

/* Banked registers */
#define CFI_ARM_UNWIND_REGISTER_SPSR_FIQ 129 /* SPSR for FIQ-mode (old CPSR upon mode-entry) */
#define CFI_ARM_UNWIND_REGISTER_SPSR_IRQ 130 /* SPSR for IRQ-mode (old CPSR upon mode-entry) */
#define CFI_ARM_UNWIND_REGISTER_SPSR_ABT 131 /* SPSR for ABT-mode (old CPSR upon mode-entry) */
#define CFI_ARM_UNWIND_REGISTER_SPSR_UND 132 /* SPSR for UND-mode (old CPSR upon mode-entry) */
#define CFI_ARM_UNWIND_REGISTER_SPSR_SVC 133 /* SPSR for SVC-mode (old CPSR upon mode-entry) */
#define CFI_ARM_UNWIND_REGISTER_R8_USR   144 /* User-space r8 (same as `CFI_ARM_UNWIND_REGISTER_R8', except when in FIQ-mode) */
#define CFI_ARM_UNWIND_REGISTER_R9_USR   145 /* User-space r9 (same as `CFI_ARM_UNWIND_REGISTER_R9', except when in FIQ-mode) */
#define CFI_ARM_UNWIND_REGISTER_R10_USR  146 /* User-space r10 (same as `CFI_ARM_UNWIND_REGISTER_R10', except when in FIQ-mode) */
#define CFI_ARM_UNWIND_REGISTER_R11_USR  147 /* User-space r11 (same as `CFI_ARM_UNWIND_REGISTER_R11', except when in FIQ-mode) */
#define CFI_ARM_UNWIND_REGISTER_R12_USR  148 /* User-space r12 (same as `CFI_ARM_UNWIND_REGISTER_R12', except when in FIQ-mode) */
#define CFI_ARM_UNWIND_REGISTER_SP_USR   149 /* User-space sp (same as `CFI_ARM_UNWIND_REGISTER_SP', except when in FIQ-mode) */
#define CFI_ARM_UNWIND_REGISTER_LR_USR   150 /* User-space lr (same as `CFI_ARM_UNWIND_REGISTER_LR', except when in FIQ-mode) */
#define CFI_ARM_UNWIND_REGISTER_R13_USR  CFI_ARM_UNWIND_REGISTER_SP_USR
#define CFI_ARM_UNWIND_REGISTER_R14_USR  CFI_ARM_UNWIND_REGISTER_LR_USR
#define CFI_ARM_UNWIND_REGISTER_R8_FIQ   151 /* banked R8-register used instead of `fcs_usr.ucs_r8' in FIQ-mode */
#define CFI_ARM_UNWIND_REGISTER_R9_FIQ   152 /* banked R9-register used instead of `fcs_usr.ucs_r9' in FIQ-mode */
#define CFI_ARM_UNWIND_REGISTER_R10_FIQ  153 /* banked R10-register used instead of `fcs_usr.ucs_r10' in FIQ-mode */
#define CFI_ARM_UNWIND_REGISTER_R11_FIQ  154 /* banked R11-register used instead of `fcs_usr.ucs_r11' in FIQ-mode */
#define CFI_ARM_UNWIND_REGISTER_R12_FIQ  155 /* banked R12-register used instead of `fcs_usr.ucs_r12' in FIQ-mode */
#define CFI_ARM_UNWIND_REGISTER_SP_FIQ   156 /* banked SP-register used instead of `fcs_usr.ucs_sp' in FIQ-mode */
#define CFI_ARM_UNWIND_REGISTER_LR_FIQ   157 /* banked LR-register used instead of `fcs_usr.ucs_lr' in FIQ-mode */
#define CFI_ARM_UNWIND_REGISTER_R13_FIQ  CFI_ARM_UNWIND_REGISTER_SP_FIQ
#define CFI_ARM_UNWIND_REGISTER_R14_FIQ  CFI_ARM_UNWIND_REGISTER_LR_FIQ
#define CFI_ARM_UNWIND_REGISTER_SP_IRQ   158 /* banked SP-register used instead of `fcs_usr.ucs_sp' in IRQ-mode */
#define CFI_ARM_UNWIND_REGISTER_LR_IRQ   159 /* banked LR-register used instead of `fcs_usr.ucs_lr' in IRQ-mode */
#define CFI_ARM_UNWIND_REGISTER_R13_IRQ  CFI_ARM_UNWIND_REGISTER_SP_IRQ
#define CFI_ARM_UNWIND_REGISTER_R14_IRQ  CFI_ARM_UNWIND_REGISTER_LR_IRQ
#define CFI_ARM_UNWIND_REGISTER_SP_ABT   160 /* banked SP-register used instead of `fcs_usr.ucs_sp' in ABT-mode */
#define CFI_ARM_UNWIND_REGISTER_LR_ABT   161 /* banked LR-register used instead of `fcs_usr.ucs_lr' in ABT-mode */
#define CFI_ARM_UNWIND_REGISTER_R13_ABT  CFI_ARM_UNWIND_REGISTER_SP_ABT
#define CFI_ARM_UNWIND_REGISTER_R14_ABT  CFI_ARM_UNWIND_REGISTER_LR_ABT
#define CFI_ARM_UNWIND_REGISTER_SP_UND   162 /* banked SP-register used instead of `fcs_usr.ucs_sp' in UND-mode */
#define CFI_ARM_UNWIND_REGISTER_LR_UND   163 /* banked LR-register used instead of `fcs_usr.ucs_lr' in UND-mode */
#define CFI_ARM_UNWIND_REGISTER_R13_UND  CFI_ARM_UNWIND_REGISTER_SP_UND
#define CFI_ARM_UNWIND_REGISTER_R14_UND  CFI_ARM_UNWIND_REGISTER_LR_UND
#define CFI_ARM_UNWIND_REGISTER_SP_SVC   164 /* banked SP-register used instead of `fcs_usr.ucs_sp' in SVC-mode */
#define CFI_ARM_UNWIND_REGISTER_LR_SVC   165 /* banked LR-register used instead of `fcs_usr.ucs_lr' in SVC-mode */
#define CFI_ARM_UNWIND_REGISTER_R13_SVC  CFI_ARM_UNWIND_REGISTER_SP_SVC
#define CFI_ARM_UNWIND_REGISTER_R14_SVC  CFI_ARM_UNWIND_REGISTER_LR_SVC

#define CFI_ARM_UNWIND_REGISTER_COUNT 166 /* 1+ the greatest used register number */



/* Register <--> Common/Uncommon-register mapping
 * Basically: These are all of the callee-preserve registers, meaning
 *            that these are  the only registers  for which GCC  will
 *            generate unwind instructions within normal assembly. */

/* Common registers */
#define CFI_ARM_UNWIND_COMMON_REGISTER_R4    0
#define CFI_ARM_UNWIND_COMMON_REGISTER_R5    1
#define CFI_ARM_UNWIND_COMMON_REGISTER_R6    2
#define CFI_ARM_UNWIND_COMMON_REGISTER_R7    3
#define CFI_ARM_UNWIND_COMMON_REGISTER_R8    4
#define CFI_ARM_UNWIND_COMMON_REGISTER_R9    5
#define CFI_ARM_UNWIND_COMMON_REGISTER_R10   6
#define CFI_ARM_UNWIND_COMMON_REGISTER_R11   7
#define CFI_ARM_UNWIND_COMMON_REGISTER_LR    8 /* Link register (return address) */
#define CFI_ARM_UNWIND_COMMON_REGISTER_PC    9 /* The register containing the program counter. */
#define CFI_ARM_UNWIND_COMMON_REGISTER_COUNT 10
#define CFI_ARM_UNWIND_COMMON_REGISTER_R14   CFI_ARM_UNWIND_COMMON_REGISTER_LR
#define CFI_ARM_UNWIND_COMMON_REGISTER_R15   CFI_ARM_UNWIND_COMMON_REGISTER_PC

/* Uncommon registers */
#define CFI_ARM_UNWIND_UNCOMMON_REGISTER_R13      CFI_ARM_UNWIND_UNCOMMON_REGISTER_SP /* The register for the CFA. */
#define CFI_ARM_UNWIND_UNCOMMON_REGISTER_R0       0
#define CFI_ARM_UNWIND_UNCOMMON_REGISTER_R1       1
#define CFI_ARM_UNWIND_UNCOMMON_REGISTER_R2       2
#define CFI_ARM_UNWIND_UNCOMMON_REGISTER_R3       3
#define CFI_ARM_UNWIND_UNCOMMON_REGISTER_R12      4
#define CFI_ARM_UNWIND_UNCOMMON_REGISTER_SP       5
#define CFI_ARM_UNWIND_UNCOMMON_REGISTER_CPSR     6  /* CPSR */
#define CFI_ARM_UNWIND_UNCOMMON_REGISTER_SPSR_FIQ 7  /* SPSR for FIQ-mode (old CPSR upon mode-entry) */
#define CFI_ARM_UNWIND_UNCOMMON_REGISTER_SPSR_IRQ 8  /* SPSR for IRQ-mode (old CPSR upon mode-entry) */
#define CFI_ARM_UNWIND_UNCOMMON_REGISTER_SPSR_ABT 9  /* SPSR for ABT-mode (old CPSR upon mode-entry) */
#define CFI_ARM_UNWIND_UNCOMMON_REGISTER_SPSR_UND 10 /* SPSR for UND-mode (old CPSR upon mode-entry) */
#define CFI_ARM_UNWIND_UNCOMMON_REGISTER_SPSR_SVC 11 /* SPSR for SVC-mode (old CPSR upon mode-entry) */
#define CFI_ARM_UNWIND_UNCOMMON_REGISTER_R8_USR   12 /* User-space r8 (same as `CFI_ARM_UNWIND_REGISTER_R8', except when in FIQ-mode) */
#define CFI_ARM_UNWIND_UNCOMMON_REGISTER_R9_USR   13 /* User-space r9 (same as `CFI_ARM_UNWIND_REGISTER_R9', except when in FIQ-mode) */
#define CFI_ARM_UNWIND_UNCOMMON_REGISTER_R10_USR  14 /* User-space r10 (same as `CFI_ARM_UNWIND_REGISTER_R10', except when in FIQ-mode) */
#define CFI_ARM_UNWIND_UNCOMMON_REGISTER_R11_USR  15 /* User-space r11 (same as `CFI_ARM_UNWIND_REGISTER_R11', except when in FIQ-mode) */
#define CFI_ARM_UNWIND_UNCOMMON_REGISTER_R12_USR  16 /* User-space r12 (same as `CFI_ARM_UNWIND_REGISTER_R12', except when in FIQ-mode) */
#define CFI_ARM_UNWIND_UNCOMMON_REGISTER_SP_USR   17 /* User-space sp (same as `CFI_ARM_UNWIND_REGISTER_SP', except when in FIQ-mode) */
#define CFI_ARM_UNWIND_UNCOMMON_REGISTER_LR_USR   18 /* User-space lr (same as `CFI_ARM_UNWIND_REGISTER_LR', except when in FIQ-mode) */
#define CFI_ARM_UNWIND_UNCOMMON_REGISTER_R8_FIQ   19 /* banked R8-register used instead of `fcs_usr.ucs_r8' in FIQ-mode */
#define CFI_ARM_UNWIND_UNCOMMON_REGISTER_R9_FIQ   20 /* banked R9-register used instead of `fcs_usr.ucs_r9' in FIQ-mode */
#define CFI_ARM_UNWIND_UNCOMMON_REGISTER_R10_FIQ  21 /* banked R10-register used instead of `fcs_usr.ucs_r10' in FIQ-mode */
#define CFI_ARM_UNWIND_UNCOMMON_REGISTER_R11_FIQ  22 /* banked R11-register used instead of `fcs_usr.ucs_r11' in FIQ-mode */
#define CFI_ARM_UNWIND_UNCOMMON_REGISTER_R12_FIQ  23 /* banked R12-register used instead of `fcs_usr.ucs_r12' in FIQ-mode */
#define CFI_ARM_UNWIND_UNCOMMON_REGISTER_SP_FIQ   24 /* banked SP-register used instead of `fcs_usr.ucs_sp' in FIQ-mode */
#define CFI_ARM_UNWIND_UNCOMMON_REGISTER_LR_FIQ   25 /* banked LR-register used instead of `fcs_usr.ucs_lr' in FIQ-mode */
#define CFI_ARM_UNWIND_UNCOMMON_REGISTER_SP_IRQ   26 /* banked SP-register used instead of `fcs_usr.ucs_sp' in IRQ-mode */
#define CFI_ARM_UNWIND_UNCOMMON_REGISTER_LR_IRQ   27 /* banked LR-register used instead of `fcs_usr.ucs_lr' in IRQ-mode */
#define CFI_ARM_UNWIND_UNCOMMON_REGISTER_SP_ABT   28 /* banked SP-register used instead of `fcs_usr.ucs_sp' in ABT-mode */
#define CFI_ARM_UNWIND_UNCOMMON_REGISTER_LR_ABT   29 /* banked LR-register used instead of `fcs_usr.ucs_lr' in ABT-mode */
#define CFI_ARM_UNWIND_UNCOMMON_REGISTER_SP_UND   30 /* banked SP-register used instead of `fcs_usr.ucs_sp' in UND-mode */
#define CFI_ARM_UNWIND_UNCOMMON_REGISTER_LR_UND   31 /* banked LR-register used instead of `fcs_usr.ucs_lr' in UND-mode */
#define CFI_ARM_UNWIND_UNCOMMON_REGISTER_SP_SVC   32 /* banked SP-register used instead of `fcs_usr.ucs_sp' in SVC-mode */
#define CFI_ARM_UNWIND_UNCOMMON_REGISTER_LR_SVC   33 /* banked LR-register used instead of `fcs_usr.ucs_lr' in SVC-mode */
#define CFI_ARM_UNWIND_UNCOMMON_REGISTER_COUNT    34

/*[[[deemon
import * from deemon;
import * from ....misc.libgen.strendN;
import * from ....misc.libgen.converter;
local macros: {string: int} = Dict(enumerateIntegerMacrosFromFile(__FILE__));
printArrayDefineMacro("DEFINE_cfi_arm_unwind_register_dw2common", generateArrayMapping(macros, "CFI_ARM_UNWIND_REGISTER_", "CFI_ARM_UNWIND_COMMON_REGISTER_"));
printArrayDefineMacro("DEFINE_cfi_arm_unwind_register_dw2uncommon", generateArrayMapping(macros, "CFI_ARM_UNWIND_REGISTER_", "CFI_ARM_UNWIND_UNCOMMON_REGISTER_"));
printArrayDefineMacro("DEFINE_cfi_arm_unwind_register_common2dw", generateArrayMapping(macros, "CFI_ARM_UNWIND_COMMON_REGISTER_", "CFI_ARM_UNWIND_REGISTER_"));
printArrayDefineMacro("DEFINE_cfi_arm_unwind_register_uncommon2dw", generateArrayMapping(macros, "CFI_ARM_UNWIND_UNCOMMON_REGISTER_", "CFI_ARM_UNWIND_REGISTER_"));
]]]*/
#define DEFINE_cfi_arm_unwind_register_dw2common(name)                                                                 \
	__UINT8_TYPE__ const name[167] = { 255, 255, 255, 255, 0,   1,   2,   3,   4,   5,   6,   7,   255, 255, 8,   9,   \
	                                   255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, \
	                                   255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, \
	                                   255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, \
	                                   255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, \
	                                   255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, \
	                                   255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, \
	                                   255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, \
	                                   255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, \
	                                   255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, \
	                                   255, 255, 255, 255, 255, 255, 10 }
#define DEFINE_cfi_arm_unwind_register_dw2uncommon(name)                                                               \
	__UINT8_TYPE__ const name[167] = { 0,   1,   2,   3,   255, 255, 255, 255, 255, 255, 255, 255, 4,   5,   255, 255, \
	                                   255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, \
	                                   255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, \
	                                   255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, \
	                                   255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, \
	                                   255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, \
	                                   255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, \
	                                   255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, \
	                                   6,   7,   8,   9,   10,  11,  255, 255, 255, 255, 255, 255, 255, 255, 255, 255, \
	                                   12,  13,  14,  15,  16,  17,  18,  19,  20,  21,  22,  23,  24,  25,  26,  27,  \
	                                   28,  29,  30,  31,  32,  33,  34 }
#define DEFINE_cfi_arm_unwind_register_common2dw(name) \
	__UINT8_TYPE__ const name[11] = { 4, 5, 6, 7, 8, 9, 10, 11, 14, 15, 166 }
#define DEFINE_cfi_arm_unwind_register_uncommon2dw(name)                                                              \
	__UINT8_TYPE__ const name[35] = { 0,   1,   2,   3,   12,  13,  128, 129, 130, 131, 132, 133, 144, 145, 146, 147, \
	                                  148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159, 160, 161, 162, 163, \
	                                  164, 165, 166 }
/*[[[end]]]*/


/* Host-specific CFI constants. */
#ifdef __arm__
#define CFI_REGISTER_MAXSIZE                        CFI_ARM_REGISTER_MAXSIZE
#define CFI_REGISTER_SIZE(addrsize, regno)          CFI_ARM_REGISTER_SIZE(regno)      /* Register size for getreg/setreg callbacks */
#define CFI_REGISTER_MEMSIZE(addrsize, regno)       CFI_ARM_REGISTER_SIZE(regno)      /* Register size for read/write to/from memory */
#define CFI_REGISTER_MEMSIZE_IS_SIZE                1                                 /* Hint: `CFI_REGISTER_MEMSIZE() == CFI_REGISTER_SIZE()' */
#define CFI_UNWIND_REGISTER_PC(addrsize)            CFI_ARM_UNWIND_REGISTER_PC        /* The register containing the program counter. */
#define CFI_UNWIND_REGISTER_SP(addrsize)            CFI_ARM_UNWIND_REGISTER_SP        /* The register for the CFA. */
#define CFI_UNWIND_REGISTER_EXCEPTION(addrsize)     CFI_ARM_UNWIND_REGISTER_EXCEPTION /* The register used to hold the current exception upon entry to an exception handler. */
#define CFI_UNWIND_REGISTER_MAXCOUNT                CFI_ARM_UNWIND_REGISTER_COUNT
#define CFI_UNWIND_REGISTER_COUNT(addrsize)         CFI_ARM_UNWIND_REGISTER_COUNT

/* Normal common/uncommon */
#define CFI_UNWIND_UNCOMMON_REGISTER_SP(addrsize)              CFI_ARM_UNWIND_UNCOMMON_REGISTER_SP
#define CFI_UNWIND_COMMON_REGISTER_MAXCOUNT                    CFI_ARM_UNWIND_COMMON_REGISTER_COUNT
#define CFI_UNWIND_COMMON_REGISTER_COUNT(addrsize)             CFI_ARM_UNWIND_COMMON_REGISTER_COUNT
#define CFI_UNWIND_UNCOMMON_REGISTER_MAXCOUNT                  CFI_ARM_UNWIND_UNCOMMON_REGISTER_COUNT
#define CFI_UNWIND_UNCOMMON_REGISTER_COUNT(addrsize)           CFI_ARM_UNWIND_UNCOMMON_REGISTER_COUNT
#define DEFINE_cfi_unwind_register_dw2common(addrsize, name)   DEFINE_cfi_arm_unwind_register_dw2common(name)
#define DEFINE_cfi_unwind_register_dw2uncommon(addrsize, name) DEFINE_cfi_arm_unwind_register_dw2uncommon(name)
#define DEFINE_cfi_unwind_register_common2dw(addrsize, name)   DEFINE_cfi_arm_unwind_register_common2dw(name)
#define DEFINE_cfi_unwind_register_uncommon2dw(addrsize, name) DEFINE_cfi_arm_unwind_register_uncommon2dw(name)
#endif /* __arm__ */


#endif /* !_LIBUNWIND_CFI_ARM_H */
