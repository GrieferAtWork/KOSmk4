/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _LIBUNWIND_CFI_ARM_H
#define _LIBUNWIND_CFI_ARM_H 1

#include "../api.h"
/**/

#include <hybrid/typecore.h>

/* Sources:
 * - IHI0040B_aadwarf.pdf
 */


/* arm-specific CFI constants. */
#define CFI_ARM_UNWIND_GPR_REGISTER_SIZE 4
#define CFI_ARM_REGISTER_MAXSIZE         4
#define CFI_ARM_REGISTER_SIZE(regno)     4
#define CFI_ARM_UNWIND_REGISTER_EXCEPTION CFI_ARM_UNWIND_REGISTER_R0 /* TODO: !!!UNCHECKED!!! */

/* Aliases */
#define CFI_ARM_UNWIND_REGISTER_SP CFI_ARM_UNWIND_REGISTER_R13 /* The register for the CFA. */
#define CFI_ARM_UNWIND_REGISTER_LR CFI_ARM_UNWIND_REGISTER_R14 /* Link register (return address) */
#define CFI_ARM_UNWIND_REGISTER_PC CFI_ARM_UNWIND_REGISTER_R15 /* The register containing the program counter. */

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
#define CFI_ARM_UNWIND_REGISTER_R13 13
#define CFI_ARM_UNWIND_REGISTER_R14 14
#define CFI_ARM_UNWIND_REGISTER_R15 15
/* TODO: FPU Registers */
#define CFI_ARM_UNWIND_REGISTER_COUNT 16



/* Register <--> Common/Uncommon-register mapping
 * Basically: These are all of the callee-preserve registers, meaning
 *            that these are  the only registers  for which GCC  will
 *            generate unwind instructions within normal assembly. */

/* Common registers */
#define CFI_ARM_UNWIND_COMMON_REGISTER_LR CFI_ARM_UNWIND_COMMON_REGISTER_R14 /* Link register (return address) */
#define CFI_ARM_UNWIND_COMMON_REGISTER_PC CFI_ARM_UNWIND_COMMON_REGISTER_R15 /* The register containing the program counter. */
#define CFI_ARM_UNWIND_COMMON_REGISTER_R4    0
#define CFI_ARM_UNWIND_COMMON_REGISTER_R5    1
#define CFI_ARM_UNWIND_COMMON_REGISTER_R6    2
#define CFI_ARM_UNWIND_COMMON_REGISTER_R7    3
#define CFI_ARM_UNWIND_COMMON_REGISTER_R8    4
#define CFI_ARM_UNWIND_COMMON_REGISTER_R9    5
#define CFI_ARM_UNWIND_COMMON_REGISTER_R10   6
#define CFI_ARM_UNWIND_COMMON_REGISTER_R11   7
#define CFI_ARM_UNWIND_COMMON_REGISTER_R14   8
#define CFI_ARM_UNWIND_COMMON_REGISTER_R15   9
#define CFI_ARM_UNWIND_COMMON_REGISTER_COUNT 10

/* Uncommon registers */
#define CFI_ARM_UNWIND_UNCOMMON_REGISTER_SP    CFI_ARM_UNWIND_UNCOMMON_REGISTER_R13 /* The register for the CFA. */
#define CFI_ARM_UNWIND_UNCOMMON_REGISTER_R0    0
#define CFI_ARM_UNWIND_UNCOMMON_REGISTER_R1    1
#define CFI_ARM_UNWIND_UNCOMMON_REGISTER_R2    2
#define CFI_ARM_UNWIND_UNCOMMON_REGISTER_R3    3
#define CFI_ARM_UNWIND_UNCOMMON_REGISTER_R12   4
#define CFI_ARM_UNWIND_UNCOMMON_REGISTER_R13   5
#define CFI_ARM_UNWIND_UNCOMMON_REGISTER_COUNT 6





/* The common/uncommon system  is optimized for  unwinding
 * regular C functions, since it only caches for registers
 * that have to be preserved when following the standard C
 * calling convention of the host.
 * However, at least within the kernel there is 1 additional
 * category  of registers that _very_ often appear alongside
 * each other, mainly when unwinding a system call:
 * arm:```
 *     Uncommon register used: 1 (1)
 *     Uncommon register used: 2 (2)
 *     Uncommon register used: 44 (36)
 *     Uncommon register used: 40 (32)
 *     Uncommon register used: 43 (35)
 *     Uncommon register used: 45 (37)
 *     Uncommon register used: 42 (34)
 *     Uncommon register used: 4 (3)
 *     Uncommon register used: 9 (4)
 *     Uncommon register used: 41 (33)
 * ```
 * To  optimize  for  stuff   like  this,  provide  an   optional,
 * secondary unwinding system specifically for sigframe functions.
 *  - When unwinding an FDE with the SIGNAL_FRAME flag set, use a different
 *    set of  COMMON registers  (mainly:  all GP-regs,  +  segments/eflags)
 *  - This  can then also  be implemented in user-space,  to only require a
 *    single evaluation-pass over the FDE body to gather all registers that
 *    are likely to ever be used.
 *  - This  entire sub-system is be implemented in parallel to the CFA_EXEC+
 *    CFA_APPLY functions and when building with __OPTIMIZE_SIZE__, we could
 *    simply implement these functions as aliases, since all they do is  add
 *    another layer of optimization.
 */

/* Register <--> Sigframe Common/Uncommon-register mapping
 *
 * Signal  frames are  normally used  to unwind  to an interrupted
 * code location. - For this  purpose, they need to restore  _all_
 * GP registers, the FLAGS register, as well as all of the segment
 * registers. To speed  up this process,  define a special  unwind
 * register namespace specifically for signal frame functions. */
#define CFI_ARM_UNWIND_SIGFRAME_COMMON_REGISTER_SP  CFI_ARM_UNWIND_SIGFRAME_COMMON_REGISTER_ESP
#define CFI_ARM_UNWIND_SIGFRAME_COMMON_REGISTER_EAX    0
#define CFI_ARM_UNWIND_SIGFRAME_COMMON_REGISTER_ECX    1
#define CFI_ARM_UNWIND_SIGFRAME_COMMON_REGISTER_EDX    2
#define CFI_ARM_UNWIND_SIGFRAME_COMMON_REGISTER_EBX    3
#define CFI_ARM_UNWIND_SIGFRAME_COMMON_REGISTER_ESP    4
#define CFI_ARM_UNWIND_SIGFRAME_COMMON_REGISTER_EBP    5
#define CFI_ARM_UNWIND_SIGFRAME_COMMON_REGISTER_ESI    6
#define CFI_ARM_UNWIND_SIGFRAME_COMMON_REGISTER_EDI    7
#define CFI_ARM_UNWIND_SIGFRAME_COMMON_REGISTER_EIP    8
#define CFI_ARM_UNWIND_SIGFRAME_COMMON_REGISTER_EFLAGS 9
#define CFI_ARM_UNWIND_SIGFRAME_COMMON_REGISTER_ES     10
#define CFI_ARM_UNWIND_SIGFRAME_COMMON_REGISTER_CS     11
#define CFI_ARM_UNWIND_SIGFRAME_COMMON_REGISTER_SS     12
#define CFI_ARM_UNWIND_SIGFRAME_COMMON_REGISTER_DS     13
#define CFI_ARM_UNWIND_SIGFRAME_COMMON_REGISTER_FS     14
#define CFI_ARM_UNWIND_SIGFRAME_COMMON_REGISTER_GS     15
#define CFI_ARM_UNWIND_SIGFRAME_COMMON_REGISTER_COUNT  16

#define CFI_ARM_UNWIND_SIGFRAME_UNCOMMON_REGISTER_ST0   0
#define CFI_ARM_UNWIND_SIGFRAME_UNCOMMON_REGISTER_ST1   1
#define CFI_ARM_UNWIND_SIGFRAME_UNCOMMON_REGISTER_ST2   2
#define CFI_ARM_UNWIND_SIGFRAME_UNCOMMON_REGISTER_ST3   3
#define CFI_ARM_UNWIND_SIGFRAME_UNCOMMON_REGISTER_ST4   4
#define CFI_ARM_UNWIND_SIGFRAME_UNCOMMON_REGISTER_ST5   5
#define CFI_ARM_UNWIND_SIGFRAME_UNCOMMON_REGISTER_ST6   6
#define CFI_ARM_UNWIND_SIGFRAME_UNCOMMON_REGISTER_ST7   7
#define CFI_ARM_UNWIND_SIGFRAME_UNCOMMON_REGISTER_XMM0  8
#define CFI_ARM_UNWIND_SIGFRAME_UNCOMMON_REGISTER_XMM1  9
#define CFI_ARM_UNWIND_SIGFRAME_UNCOMMON_REGISTER_XMM2  10
#define CFI_ARM_UNWIND_SIGFRAME_UNCOMMON_REGISTER_XMM3  11
#define CFI_ARM_UNWIND_SIGFRAME_UNCOMMON_REGISTER_XMM4  12
#define CFI_ARM_UNWIND_SIGFRAME_UNCOMMON_REGISTER_XMM5  13
#define CFI_ARM_UNWIND_SIGFRAME_UNCOMMON_REGISTER_XMM6  14
#define CFI_ARM_UNWIND_SIGFRAME_UNCOMMON_REGISTER_XMM7  15
#define CFI_ARM_UNWIND_SIGFRAME_UNCOMMON_REGISTER_MM0   16
#define CFI_ARM_UNWIND_SIGFRAME_UNCOMMON_REGISTER_MM1   17
#define CFI_ARM_UNWIND_SIGFRAME_UNCOMMON_REGISTER_MM2   18
#define CFI_ARM_UNWIND_SIGFRAME_UNCOMMON_REGISTER_MM3   19
#define CFI_ARM_UNWIND_SIGFRAME_UNCOMMON_REGISTER_MM4   20
#define CFI_ARM_UNWIND_SIGFRAME_UNCOMMON_REGISTER_MM5   21
#define CFI_ARM_UNWIND_SIGFRAME_UNCOMMON_REGISTER_MM6   22
#define CFI_ARM_UNWIND_SIGFRAME_UNCOMMON_REGISTER_MM7   23
#define CFI_ARM_UNWIND_SIGFRAME_UNCOMMON_REGISTER_FCW   24
#define CFI_ARM_UNWIND_SIGFRAME_UNCOMMON_REGISTER_FSW   25
#define CFI_ARM_UNWIND_SIGFRAME_UNCOMMON_REGISTER_MXCSR 26
#define CFI_ARM_UNWIND_SIGFRAME_UNCOMMON_REGISTER_TR    27
#define CFI_ARM_UNWIND_SIGFRAME_UNCOMMON_REGISTER_LDTR  28
#define CFI_ARM_UNWIND_SIGFRAME_UNCOMMON_REGISTER_K0    29
#define CFI_ARM_UNWIND_SIGFRAME_UNCOMMON_REGISTER_K1    30
#define CFI_ARM_UNWIND_SIGFRAME_UNCOMMON_REGISTER_K2    31
#define CFI_ARM_UNWIND_SIGFRAME_UNCOMMON_REGISTER_K3    32
#define CFI_ARM_UNWIND_SIGFRAME_UNCOMMON_REGISTER_K4    33
#define CFI_ARM_UNWIND_SIGFRAME_UNCOMMON_REGISTER_K5    34
#define CFI_ARM_UNWIND_SIGFRAME_UNCOMMON_REGISTER_K6    35
#define CFI_ARM_UNWIND_SIGFRAME_UNCOMMON_REGISTER_K7    36
#define CFI_ARM_UNWIND_SIGFRAME_UNCOMMON_REGISTER_COUNT 37



/* Register <--> Landing-pad Common/Uncommon-register mapping */
#define CFI_ARM_UNWIND_LANDING_COMMON_REGISTER_EFLAGS 0
#define CFI_ARM_UNWIND_LANDING_COMMON_REGISTER_COUNT  1

#define CFI_ARM_UNWIND_LANDING_UNCOMMON_REGISTER_SP    CFI_ARM_UNWIND_LANDING_UNCOMMON_REGISTER_ESP
#define CFI_ARM_UNWIND_LANDING_UNCOMMON_REGISTER_EAX   0
#define CFI_ARM_UNWIND_LANDING_UNCOMMON_REGISTER_ECX   1
#define CFI_ARM_UNWIND_LANDING_UNCOMMON_REGISTER_EDX   2
#define CFI_ARM_UNWIND_LANDING_UNCOMMON_REGISTER_EBX   3
#define CFI_ARM_UNWIND_LANDING_UNCOMMON_REGISTER_ESP   4
#define CFI_ARM_UNWIND_LANDING_UNCOMMON_REGISTER_EBP   5
#define CFI_ARM_UNWIND_LANDING_UNCOMMON_REGISTER_ESI   6
#define CFI_ARM_UNWIND_LANDING_UNCOMMON_REGISTER_EDI   7
#define CFI_ARM_UNWIND_LANDING_UNCOMMON_REGISTER_EIP   8
#define CFI_ARM_UNWIND_LANDING_UNCOMMON_REGISTER_ST0   9
#define CFI_ARM_UNWIND_LANDING_UNCOMMON_REGISTER_ST1   10
#define CFI_ARM_UNWIND_LANDING_UNCOMMON_REGISTER_ST2   11
#define CFI_ARM_UNWIND_LANDING_UNCOMMON_REGISTER_ST3   12
#define CFI_ARM_UNWIND_LANDING_UNCOMMON_REGISTER_ST4   13
#define CFI_ARM_UNWIND_LANDING_UNCOMMON_REGISTER_ST5   14
#define CFI_ARM_UNWIND_LANDING_UNCOMMON_REGISTER_ST6   15
#define CFI_ARM_UNWIND_LANDING_UNCOMMON_REGISTER_ST7   16
#define CFI_ARM_UNWIND_LANDING_UNCOMMON_REGISTER_XMM0  17
#define CFI_ARM_UNWIND_LANDING_UNCOMMON_REGISTER_XMM1  18
#define CFI_ARM_UNWIND_LANDING_UNCOMMON_REGISTER_XMM2  19
#define CFI_ARM_UNWIND_LANDING_UNCOMMON_REGISTER_XMM3  20
#define CFI_ARM_UNWIND_LANDING_UNCOMMON_REGISTER_XMM4  21
#define CFI_ARM_UNWIND_LANDING_UNCOMMON_REGISTER_XMM5  22
#define CFI_ARM_UNWIND_LANDING_UNCOMMON_REGISTER_XMM6  23
#define CFI_ARM_UNWIND_LANDING_UNCOMMON_REGISTER_XMM7  24
#define CFI_ARM_UNWIND_LANDING_UNCOMMON_REGISTER_MM0   25
#define CFI_ARM_UNWIND_LANDING_UNCOMMON_REGISTER_MM1   26
#define CFI_ARM_UNWIND_LANDING_UNCOMMON_REGISTER_MM2   27
#define CFI_ARM_UNWIND_LANDING_UNCOMMON_REGISTER_MM3   28
#define CFI_ARM_UNWIND_LANDING_UNCOMMON_REGISTER_MM4   29
#define CFI_ARM_UNWIND_LANDING_UNCOMMON_REGISTER_MM5   30
#define CFI_ARM_UNWIND_LANDING_UNCOMMON_REGISTER_MM6   31
#define CFI_ARM_UNWIND_LANDING_UNCOMMON_REGISTER_MM7   32
#define CFI_ARM_UNWIND_LANDING_UNCOMMON_REGISTER_FCW   33
#define CFI_ARM_UNWIND_LANDING_UNCOMMON_REGISTER_FSW   34
#define CFI_ARM_UNWIND_LANDING_UNCOMMON_REGISTER_MXCSR 35
#define CFI_ARM_UNWIND_LANDING_UNCOMMON_REGISTER_ES    36
#define CFI_ARM_UNWIND_LANDING_UNCOMMON_REGISTER_CS    37
#define CFI_ARM_UNWIND_LANDING_UNCOMMON_REGISTER_SS    38
#define CFI_ARM_UNWIND_LANDING_UNCOMMON_REGISTER_DS    39
#define CFI_ARM_UNWIND_LANDING_UNCOMMON_REGISTER_FS    40
#define CFI_ARM_UNWIND_LANDING_UNCOMMON_REGISTER_GS    41
#define CFI_ARM_UNWIND_LANDING_UNCOMMON_REGISTER_TR    42
#define CFI_ARM_UNWIND_LANDING_UNCOMMON_REGISTER_LDTR  43
#define CFI_ARM_UNWIND_LANDING_UNCOMMON_REGISTER_K0    44
#define CFI_ARM_UNWIND_LANDING_UNCOMMON_REGISTER_K1    45
#define CFI_ARM_UNWIND_LANDING_UNCOMMON_REGISTER_K2    46
#define CFI_ARM_UNWIND_LANDING_UNCOMMON_REGISTER_K3    47
#define CFI_ARM_UNWIND_LANDING_UNCOMMON_REGISTER_K4    48
#define CFI_ARM_UNWIND_LANDING_UNCOMMON_REGISTER_K5    49
#define CFI_ARM_UNWIND_LANDING_UNCOMMON_REGISTER_K6    50
#define CFI_ARM_UNWIND_LANDING_UNCOMMON_REGISTER_K7    51
#define CFI_ARM_UNWIND_LANDING_UNCOMMON_REGISTER_COUNT 52


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
#define DEFINE_cfi_arm_unwind_register_dw2common(name)                                                                \
	__UINT8_TYPE__ const name[17] = { 255, 255, 255, 255, 0,   1,   2,   3,   4,   5,   6,   7,   255, 255, 8,   9,   \
	                                  10 }
#define DEFINE_cfi_arm_unwind_register_dw2uncommon(name)                                                              \
	__UINT8_TYPE__ const name[17] = { 0,   1,   2,   3,   255, 255, 255, 255, 255, 255, 255, 255, 4,   5,   255, 255, \
	                                  6 }
#define DEFINE_cfi_arm_unwind_register_common2dw(name) \
	__UINT8_TYPE__ const name[11] = { 4, 5, 6, 7, 8, 9, 10, 11, 14, 15, 16 }
#define DEFINE_cfi_arm_unwind_register_uncommon2dw(name) \
	__UINT8_TYPE__ const name[7] = { 0, 1, 2, 3, 12, 13, 16 }
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
