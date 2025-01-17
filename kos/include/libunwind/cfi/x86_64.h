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
#ifndef _LIBUNWIND_CFI_X86_64_H
#define _LIBUNWIND_CFI_X86_64_H 1

#include "../api.h"
/**/

#include <hybrid/host.h>
#include <hybrid/typecore.h>

/* x86_64-specific CFI constants. */
#define CFI_X86_64_UNWIND_GPR_REGISTER_SIZE 8
#define CFI_X86_64_UNWIND_FPU_REGISTER_SIZE 16
#define CFI_X86_64_UNWIND_IS_FPU_REGISTER(regno)                                                  \
	(((regno) >= CFI_X86_64_UNWIND_REGISTER_XMM0 && (regno) <= CFI_X86_64_UNWIND_REGISTER_MM7) || \
	 ((regno) >= CFI_X86_64_UNWIND_REGISTER_XMM16 && (regno) <= CFI_X86_64_UNWIND_REGISTER_XMM31))
#define CFI_X86_64_REGISTER_MAXSIZE 16
#define CFI_X86_64_REGISTER_SIZE(regno)       \
	(CFI_X86_64_UNWIND_IS_FPU_REGISTER(regno) \
	 ? CFI_X86_64_UNWIND_FPU_REGISTER_SIZE    \
	 : CFI_X86_64_UNWIND_GPR_REGISTER_SIZE)

#define CFI_X86_64_UNWIND_REGISTER_PC        CFI_X86_64_UNWIND_REGISTER_RIP /* The register containing the program counter. */
#define CFI_X86_64_UNWIND_REGISTER_SP        CFI_X86_64_UNWIND_REGISTER_RSP /* The register for the CFA. */
#define CFI_X86_64_UNWIND_REGISTER_EXCEPTION CFI_X86_64_UNWIND_REGISTER_RAX /* The register used to hold the current exception upon entry to an exception handler. */
#define CFI_X86_64_UNWIND_REGISTER_RAX    0
#define CFI_X86_64_UNWIND_REGISTER_RDX    1
#define CFI_X86_64_UNWIND_REGISTER_RCX    2
#define CFI_X86_64_UNWIND_REGISTER_RBX    3
#define CFI_X86_64_UNWIND_REGISTER_RSI    4
#define CFI_X86_64_UNWIND_REGISTER_RDI    5
#define CFI_X86_64_UNWIND_REGISTER_RBP    6
#define CFI_X86_64_UNWIND_REGISTER_RSP    7
#define CFI_X86_64_UNWIND_REGISTER_R8     8
#define CFI_X86_64_UNWIND_REGISTER_R9     9
#define CFI_X86_64_UNWIND_REGISTER_R10    10
#define CFI_X86_64_UNWIND_REGISTER_R11    11
#define CFI_X86_64_UNWIND_REGISTER_R12    12
#define CFI_X86_64_UNWIND_REGISTER_R13    13
#define CFI_X86_64_UNWIND_REGISTER_R14    14
#define CFI_X86_64_UNWIND_REGISTER_R15    15
#define CFI_X86_64_UNWIND_REGISTER_RIP    16
#define CFI_X86_64_UNWIND_REGISTER_XMM0   17
#define CFI_X86_64_UNWIND_REGISTER_XMM1   18
#define CFI_X86_64_UNWIND_REGISTER_XMM2   19
#define CFI_X86_64_UNWIND_REGISTER_XMM3   20
#define CFI_X86_64_UNWIND_REGISTER_XMM4   21
#define CFI_X86_64_UNWIND_REGISTER_XMM5   22
#define CFI_X86_64_UNWIND_REGISTER_XMM6   23
#define CFI_X86_64_UNWIND_REGISTER_XMM7   24
#define CFI_X86_64_UNWIND_REGISTER_XMM8   25
#define CFI_X86_64_UNWIND_REGISTER_XMM9   26
#define CFI_X86_64_UNWIND_REGISTER_XMM10  27
#define CFI_X86_64_UNWIND_REGISTER_XMM11  28
#define CFI_X86_64_UNWIND_REGISTER_XMM12  29
#define CFI_X86_64_UNWIND_REGISTER_XMM13  30
#define CFI_X86_64_UNWIND_REGISTER_XMM14  31
#define CFI_X86_64_UNWIND_REGISTER_XMM15  32
#define CFI_X86_64_UNWIND_REGISTER_ST0    33
#define CFI_X86_64_UNWIND_REGISTER_ST1    34
#define CFI_X86_64_UNWIND_REGISTER_ST2    35
#define CFI_X86_64_UNWIND_REGISTER_ST3    36
#define CFI_X86_64_UNWIND_REGISTER_ST4    37
#define CFI_X86_64_UNWIND_REGISTER_ST5    38
#define CFI_X86_64_UNWIND_REGISTER_ST6    39
#define CFI_X86_64_UNWIND_REGISTER_ST7    40
#define CFI_X86_64_UNWIND_REGISTER_MM0    41
#define CFI_X86_64_UNWIND_REGISTER_MM1    42
#define CFI_X86_64_UNWIND_REGISTER_MM2    43
#define CFI_X86_64_UNWIND_REGISTER_MM3    44
#define CFI_X86_64_UNWIND_REGISTER_MM4    45
#define CFI_X86_64_UNWIND_REGISTER_MM5    46
#define CFI_X86_64_UNWIND_REGISTER_MM6    47
#define CFI_X86_64_UNWIND_REGISTER_MM7    48
#define CFI_X86_64_UNWIND_REGISTER_RFLAGS 49
#define CFI_X86_64_UNWIND_REGISTER_ES     50
#define CFI_X86_64_UNWIND_REGISTER_CS     51
#define CFI_X86_64_UNWIND_REGISTER_SS     52
#define CFI_X86_64_UNWIND_REGISTER_DS     53
#define CFI_X86_64_UNWIND_REGISTER_FS     54
#define CFI_X86_64_UNWIND_REGISTER_GS     55
/*      CFI_X86_64_UNWIND_REGISTER_       56 */
/*      CFI_X86_64_UNWIND_REGISTER_       57 */
#define CFI_X86_64_UNWIND_REGISTER_FSBASE 58 /* gas knows this as `%fs.base' */
#define CFI_X86_64_UNWIND_REGISTER_GSBASE 59 /* gas knows this as `%gs.base' */
/*      CFI_X86_64_UNWIND_REGISTER_       60 */
/*      CFI_X86_64_UNWIND_REGISTER_       61 */
#define CFI_X86_64_UNWIND_REGISTER_TR     62
#define CFI_X86_64_UNWIND_REGISTER_LDTR   63
#define CFI_X86_64_UNWIND_REGISTER_MXCSR  64
#define CFI_X86_64_UNWIND_REGISTER_FCW    65
#define CFI_X86_64_UNWIND_REGISTER_FSW    66
#define CFI_X86_64_UNWIND_REGISTER_XMM16  67
#define CFI_X86_64_UNWIND_REGISTER_XMM17  68
#define CFI_X86_64_UNWIND_REGISTER_XMM18  69
#define CFI_X86_64_UNWIND_REGISTER_XMM19  70
#define CFI_X86_64_UNWIND_REGISTER_XMM20  71
#define CFI_X86_64_UNWIND_REGISTER_XMM21  72
#define CFI_X86_64_UNWIND_REGISTER_XMM22  73
#define CFI_X86_64_UNWIND_REGISTER_XMM23  74
#define CFI_X86_64_UNWIND_REGISTER_XMM24  75
#define CFI_X86_64_UNWIND_REGISTER_XMM25  76
#define CFI_X86_64_UNWIND_REGISTER_XMM26  77
#define CFI_X86_64_UNWIND_REGISTER_XMM27  78
#define CFI_X86_64_UNWIND_REGISTER_XMM28  79
#define CFI_X86_64_UNWIND_REGISTER_XMM29  80
#define CFI_X86_64_UNWIND_REGISTER_XMM30  81
#define CFI_X86_64_UNWIND_REGISTER_XMM31  82
/*      CFI_X86_64_UNWIND_REGISTER_       83 */
/*      CFI_X86_64_UNWIND_REGISTER_       ... */
/*      CFI_X86_64_UNWIND_REGISTER_       117 */
#define CFI_X86_64_UNWIND_REGISTER_K0     118
#define CFI_X86_64_UNWIND_REGISTER_K1     119
#define CFI_X86_64_UNWIND_REGISTER_K2     120
#define CFI_X86_64_UNWIND_REGISTER_K3     121
#define CFI_X86_64_UNWIND_REGISTER_K4     122
#define CFI_X86_64_UNWIND_REGISTER_K5     123
#define CFI_X86_64_UNWIND_REGISTER_K6     124
#define CFI_X86_64_UNWIND_REGISTER_K7     125
#define CFI_X86_64_UNWIND_REGISTER_COUNT  126



/* Register <--> Normal common/uncommon-register mapping */
#define CFI_X86_64_UNWIND_COMMON_REGISTER_RBX   0
#define CFI_X86_64_UNWIND_COMMON_REGISTER_RBP   1
#define CFI_X86_64_UNWIND_COMMON_REGISTER_R12   2
#define CFI_X86_64_UNWIND_COMMON_REGISTER_R13   3
#define CFI_X86_64_UNWIND_COMMON_REGISTER_R14   4
#define CFI_X86_64_UNWIND_COMMON_REGISTER_R15   5
#define CFI_X86_64_UNWIND_COMMON_REGISTER_RIP   6
#define CFI_X86_64_UNWIND_COMMON_REGISTER_COUNT 7

#define CFI_X86_64_UNWIND_UNCOMMON_REGISTER_SP     CFI_X86_64_UNWIND_UNCOMMON_REGISTER_RSP
#define CFI_X86_64_UNWIND_UNCOMMON_REGISTER_RAX    0
#define CFI_X86_64_UNWIND_UNCOMMON_REGISTER_RDX    1
#define CFI_X86_64_UNWIND_UNCOMMON_REGISTER_RCX    2
#define CFI_X86_64_UNWIND_UNCOMMON_REGISTER_RSI    3
#define CFI_X86_64_UNWIND_UNCOMMON_REGISTER_RDI    4
#define CFI_X86_64_UNWIND_UNCOMMON_REGISTER_RSP    5
#define CFI_X86_64_UNWIND_UNCOMMON_REGISTER_R8     6
#define CFI_X86_64_UNWIND_UNCOMMON_REGISTER_R9     7
#define CFI_X86_64_UNWIND_UNCOMMON_REGISTER_R10    8
#define CFI_X86_64_UNWIND_UNCOMMON_REGISTER_R11    9
#define CFI_X86_64_UNWIND_UNCOMMON_REGISTER_XMM0   10
#define CFI_X86_64_UNWIND_UNCOMMON_REGISTER_XMM1   11
#define CFI_X86_64_UNWIND_UNCOMMON_REGISTER_XMM2   12
#define CFI_X86_64_UNWIND_UNCOMMON_REGISTER_XMM3   13
#define CFI_X86_64_UNWIND_UNCOMMON_REGISTER_XMM4   14
#define CFI_X86_64_UNWIND_UNCOMMON_REGISTER_XMM5   15
#define CFI_X86_64_UNWIND_UNCOMMON_REGISTER_XMM6   16
#define CFI_X86_64_UNWIND_UNCOMMON_REGISTER_XMM7   17
#define CFI_X86_64_UNWIND_UNCOMMON_REGISTER_XMM8   18
#define CFI_X86_64_UNWIND_UNCOMMON_REGISTER_XMM9   19
#define CFI_X86_64_UNWIND_UNCOMMON_REGISTER_XMM10  20
#define CFI_X86_64_UNWIND_UNCOMMON_REGISTER_XMM11  21
#define CFI_X86_64_UNWIND_UNCOMMON_REGISTER_XMM12  22
#define CFI_X86_64_UNWIND_UNCOMMON_REGISTER_XMM13  23
#define CFI_X86_64_UNWIND_UNCOMMON_REGISTER_XMM14  24
#define CFI_X86_64_UNWIND_UNCOMMON_REGISTER_XMM15  25
#define CFI_X86_64_UNWIND_UNCOMMON_REGISTER_ST0    26
#define CFI_X86_64_UNWIND_UNCOMMON_REGISTER_ST1    27
#define CFI_X86_64_UNWIND_UNCOMMON_REGISTER_ST2    28
#define CFI_X86_64_UNWIND_UNCOMMON_REGISTER_ST3    29
#define CFI_X86_64_UNWIND_UNCOMMON_REGISTER_ST4    30
#define CFI_X86_64_UNWIND_UNCOMMON_REGISTER_ST5    31
#define CFI_X86_64_UNWIND_UNCOMMON_REGISTER_ST6    32
#define CFI_X86_64_UNWIND_UNCOMMON_REGISTER_ST7    33
#define CFI_X86_64_UNWIND_UNCOMMON_REGISTER_MM0    34
#define CFI_X86_64_UNWIND_UNCOMMON_REGISTER_MM1    35
#define CFI_X86_64_UNWIND_UNCOMMON_REGISTER_MM2    36
#define CFI_X86_64_UNWIND_UNCOMMON_REGISTER_MM3    37
#define CFI_X86_64_UNWIND_UNCOMMON_REGISTER_MM4    38
#define CFI_X86_64_UNWIND_UNCOMMON_REGISTER_MM5    39
#define CFI_X86_64_UNWIND_UNCOMMON_REGISTER_MM6    40
#define CFI_X86_64_UNWIND_UNCOMMON_REGISTER_MM7    41
#define CFI_X86_64_UNWIND_UNCOMMON_REGISTER_RFLAGS 42
#define CFI_X86_64_UNWIND_UNCOMMON_REGISTER_ES     43
#define CFI_X86_64_UNWIND_UNCOMMON_REGISTER_CS     44
#define CFI_X86_64_UNWIND_UNCOMMON_REGISTER_SS     45
#define CFI_X86_64_UNWIND_UNCOMMON_REGISTER_DS     46
#define CFI_X86_64_UNWIND_UNCOMMON_REGISTER_FS     47
#define CFI_X86_64_UNWIND_UNCOMMON_REGISTER_GS     48
#define CFI_X86_64_UNWIND_UNCOMMON_REGISTER_FSBASE 49
#define CFI_X86_64_UNWIND_UNCOMMON_REGISTER_GSBASE 50
#define CFI_X86_64_UNWIND_UNCOMMON_REGISTER_TR     51
#define CFI_X86_64_UNWIND_UNCOMMON_REGISTER_LDTR   52
#define CFI_X86_64_UNWIND_UNCOMMON_REGISTER_MXCSR  53
#define CFI_X86_64_UNWIND_UNCOMMON_REGISTER_FCW    54
#define CFI_X86_64_UNWIND_UNCOMMON_REGISTER_FSW    55
#define CFI_X86_64_UNWIND_UNCOMMON_REGISTER_XMM16  56
#define CFI_X86_64_UNWIND_UNCOMMON_REGISTER_XMM17  57
#define CFI_X86_64_UNWIND_UNCOMMON_REGISTER_XMM18  58
#define CFI_X86_64_UNWIND_UNCOMMON_REGISTER_XMM19  59
#define CFI_X86_64_UNWIND_UNCOMMON_REGISTER_XMM20  60
#define CFI_X86_64_UNWIND_UNCOMMON_REGISTER_XMM21  61
#define CFI_X86_64_UNWIND_UNCOMMON_REGISTER_XMM22  62
#define CFI_X86_64_UNWIND_UNCOMMON_REGISTER_XMM23  63
#define CFI_X86_64_UNWIND_UNCOMMON_REGISTER_XMM24  64
#define CFI_X86_64_UNWIND_UNCOMMON_REGISTER_XMM25  65
#define CFI_X86_64_UNWIND_UNCOMMON_REGISTER_XMM26  66
#define CFI_X86_64_UNWIND_UNCOMMON_REGISTER_XMM27  67
#define CFI_X86_64_UNWIND_UNCOMMON_REGISTER_XMM28  68
#define CFI_X86_64_UNWIND_UNCOMMON_REGISTER_XMM29  69
#define CFI_X86_64_UNWIND_UNCOMMON_REGISTER_XMM30  70
#define CFI_X86_64_UNWIND_UNCOMMON_REGISTER_XMM31  71
#define CFI_X86_64_UNWIND_UNCOMMON_REGISTER_K0     72
#define CFI_X86_64_UNWIND_UNCOMMON_REGISTER_K1     73
#define CFI_X86_64_UNWIND_UNCOMMON_REGISTER_K2     74
#define CFI_X86_64_UNWIND_UNCOMMON_REGISTER_K3     75
#define CFI_X86_64_UNWIND_UNCOMMON_REGISTER_K4     76
#define CFI_X86_64_UNWIND_UNCOMMON_REGISTER_K5     77
#define CFI_X86_64_UNWIND_UNCOMMON_REGISTER_K6     78
#define CFI_X86_64_UNWIND_UNCOMMON_REGISTER_K7     79
#define CFI_X86_64_UNWIND_UNCOMMON_REGISTER_COUNT  80






/* Register <--> Sigframe common/uncommon-register mapping */
#define CFI_X86_64_UNWIND_SIGFRAME_COMMON_REGISTER_SP     CFI_X86_64_UNWIND_SIGFRAME_COMMON_REGISTER_RSP
#define CFI_X86_64_UNWIND_SIGFRAME_COMMON_REGISTER_RAX    0
#define CFI_X86_64_UNWIND_SIGFRAME_COMMON_REGISTER_RDX    1
#define CFI_X86_64_UNWIND_SIGFRAME_COMMON_REGISTER_RCX    2
#define CFI_X86_64_UNWIND_SIGFRAME_COMMON_REGISTER_RBX    3
#define CFI_X86_64_UNWIND_SIGFRAME_COMMON_REGISTER_RSI    4
#define CFI_X86_64_UNWIND_SIGFRAME_COMMON_REGISTER_RDI    5
#define CFI_X86_64_UNWIND_SIGFRAME_COMMON_REGISTER_RBP    6
#define CFI_X86_64_UNWIND_SIGFRAME_COMMON_REGISTER_RSP    7
#define CFI_X86_64_UNWIND_SIGFRAME_COMMON_REGISTER_R8     8
#define CFI_X86_64_UNWIND_SIGFRAME_COMMON_REGISTER_R9     9
#define CFI_X86_64_UNWIND_SIGFRAME_COMMON_REGISTER_R10    10
#define CFI_X86_64_UNWIND_SIGFRAME_COMMON_REGISTER_R11    11
#define CFI_X86_64_UNWIND_SIGFRAME_COMMON_REGISTER_R12    12
#define CFI_X86_64_UNWIND_SIGFRAME_COMMON_REGISTER_R13    13
#define CFI_X86_64_UNWIND_SIGFRAME_COMMON_REGISTER_R14    14
#define CFI_X86_64_UNWIND_SIGFRAME_COMMON_REGISTER_R15    15
#define CFI_X86_64_UNWIND_SIGFRAME_COMMON_REGISTER_RIP    16
#define CFI_X86_64_UNWIND_SIGFRAME_COMMON_REGISTER_RFLAGS 17
#define CFI_X86_64_UNWIND_SIGFRAME_COMMON_REGISTER_ES     18
#define CFI_X86_64_UNWIND_SIGFRAME_COMMON_REGISTER_CS     19
#define CFI_X86_64_UNWIND_SIGFRAME_COMMON_REGISTER_SS     20
#define CFI_X86_64_UNWIND_SIGFRAME_COMMON_REGISTER_DS     21
#define CFI_X86_64_UNWIND_SIGFRAME_COMMON_REGISTER_FS     22
#define CFI_X86_64_UNWIND_SIGFRAME_COMMON_REGISTER_GS     23
#define CFI_X86_64_UNWIND_SIGFRAME_COMMON_REGISTER_FSBASE 24 /* gas knows this as `%fs.base' */
#define CFI_X86_64_UNWIND_SIGFRAME_COMMON_REGISTER_GSBASE 25 /* gas knows this as `%fs.base' */
#define CFI_X86_64_UNWIND_SIGFRAME_COMMON_REGISTER_COUNT  26

#define CFI_X86_64_UNWIND_SIGFRAME_UNCOMMON_REGISTER_XMM0   0
#define CFI_X86_64_UNWIND_SIGFRAME_UNCOMMON_REGISTER_XMM1   1
#define CFI_X86_64_UNWIND_SIGFRAME_UNCOMMON_REGISTER_XMM2   2
#define CFI_X86_64_UNWIND_SIGFRAME_UNCOMMON_REGISTER_XMM3   3
#define CFI_X86_64_UNWIND_SIGFRAME_UNCOMMON_REGISTER_XMM4   4
#define CFI_X86_64_UNWIND_SIGFRAME_UNCOMMON_REGISTER_XMM5   5
#define CFI_X86_64_UNWIND_SIGFRAME_UNCOMMON_REGISTER_XMM6   6
#define CFI_X86_64_UNWIND_SIGFRAME_UNCOMMON_REGISTER_XMM7   7
#define CFI_X86_64_UNWIND_SIGFRAME_UNCOMMON_REGISTER_XMM8   8
#define CFI_X86_64_UNWIND_SIGFRAME_UNCOMMON_REGISTER_XMM9   9
#define CFI_X86_64_UNWIND_SIGFRAME_UNCOMMON_REGISTER_XMM10  10
#define CFI_X86_64_UNWIND_SIGFRAME_UNCOMMON_REGISTER_XMM11  11
#define CFI_X86_64_UNWIND_SIGFRAME_UNCOMMON_REGISTER_XMM12  12
#define CFI_X86_64_UNWIND_SIGFRAME_UNCOMMON_REGISTER_XMM13  13
#define CFI_X86_64_UNWIND_SIGFRAME_UNCOMMON_REGISTER_XMM14  14
#define CFI_X86_64_UNWIND_SIGFRAME_UNCOMMON_REGISTER_XMM15  15
#define CFI_X86_64_UNWIND_SIGFRAME_UNCOMMON_REGISTER_ST0    16
#define CFI_X86_64_UNWIND_SIGFRAME_UNCOMMON_REGISTER_ST1    17
#define CFI_X86_64_UNWIND_SIGFRAME_UNCOMMON_REGISTER_ST2    18
#define CFI_X86_64_UNWIND_SIGFRAME_UNCOMMON_REGISTER_ST3    19
#define CFI_X86_64_UNWIND_SIGFRAME_UNCOMMON_REGISTER_ST4    20
#define CFI_X86_64_UNWIND_SIGFRAME_UNCOMMON_REGISTER_ST5    21
#define CFI_X86_64_UNWIND_SIGFRAME_UNCOMMON_REGISTER_ST6    22
#define CFI_X86_64_UNWIND_SIGFRAME_UNCOMMON_REGISTER_ST7    23
#define CFI_X86_64_UNWIND_SIGFRAME_UNCOMMON_REGISTER_MM0    24
#define CFI_X86_64_UNWIND_SIGFRAME_UNCOMMON_REGISTER_MM1    25
#define CFI_X86_64_UNWIND_SIGFRAME_UNCOMMON_REGISTER_MM2    26
#define CFI_X86_64_UNWIND_SIGFRAME_UNCOMMON_REGISTER_MM3    27
#define CFI_X86_64_UNWIND_SIGFRAME_UNCOMMON_REGISTER_MM4    28
#define CFI_X86_64_UNWIND_SIGFRAME_UNCOMMON_REGISTER_MM5    29
#define CFI_X86_64_UNWIND_SIGFRAME_UNCOMMON_REGISTER_MM6    30
#define CFI_X86_64_UNWIND_SIGFRAME_UNCOMMON_REGISTER_MM7    31
#define CFI_X86_64_UNWIND_SIGFRAME_UNCOMMON_REGISTER_TR     32
#define CFI_X86_64_UNWIND_SIGFRAME_UNCOMMON_REGISTER_LDTR   33
#define CFI_X86_64_UNWIND_SIGFRAME_UNCOMMON_REGISTER_MXCSR  34
#define CFI_X86_64_UNWIND_SIGFRAME_UNCOMMON_REGISTER_FCW    35
#define CFI_X86_64_UNWIND_SIGFRAME_UNCOMMON_REGISTER_FSW    36
#define CFI_X86_64_UNWIND_SIGFRAME_UNCOMMON_REGISTER_XMM16  37
#define CFI_X86_64_UNWIND_SIGFRAME_UNCOMMON_REGISTER_XMM17  38
#define CFI_X86_64_UNWIND_SIGFRAME_UNCOMMON_REGISTER_XMM18  39
#define CFI_X86_64_UNWIND_SIGFRAME_UNCOMMON_REGISTER_XMM19  40
#define CFI_X86_64_UNWIND_SIGFRAME_UNCOMMON_REGISTER_XMM20  41
#define CFI_X86_64_UNWIND_SIGFRAME_UNCOMMON_REGISTER_XMM21  42
#define CFI_X86_64_UNWIND_SIGFRAME_UNCOMMON_REGISTER_XMM22  43
#define CFI_X86_64_UNWIND_SIGFRAME_UNCOMMON_REGISTER_XMM23  44
#define CFI_X86_64_UNWIND_SIGFRAME_UNCOMMON_REGISTER_XMM24  45
#define CFI_X86_64_UNWIND_SIGFRAME_UNCOMMON_REGISTER_XMM25  46
#define CFI_X86_64_UNWIND_SIGFRAME_UNCOMMON_REGISTER_XMM26  47
#define CFI_X86_64_UNWIND_SIGFRAME_UNCOMMON_REGISTER_XMM27  48
#define CFI_X86_64_UNWIND_SIGFRAME_UNCOMMON_REGISTER_XMM28  49
#define CFI_X86_64_UNWIND_SIGFRAME_UNCOMMON_REGISTER_XMM29  50
#define CFI_X86_64_UNWIND_SIGFRAME_UNCOMMON_REGISTER_XMM30  51
#define CFI_X86_64_UNWIND_SIGFRAME_UNCOMMON_REGISTER_XMM31  52
#define CFI_X86_64_UNWIND_SIGFRAME_UNCOMMON_REGISTER_K0     53
#define CFI_X86_64_UNWIND_SIGFRAME_UNCOMMON_REGISTER_K1     54
#define CFI_X86_64_UNWIND_SIGFRAME_UNCOMMON_REGISTER_K2     55
#define CFI_X86_64_UNWIND_SIGFRAME_UNCOMMON_REGISTER_K3     56
#define CFI_X86_64_UNWIND_SIGFRAME_UNCOMMON_REGISTER_K4     57
#define CFI_X86_64_UNWIND_SIGFRAME_UNCOMMON_REGISTER_K5     58
#define CFI_X86_64_UNWIND_SIGFRAME_UNCOMMON_REGISTER_K6     59
#define CFI_X86_64_UNWIND_SIGFRAME_UNCOMMON_REGISTER_K7     60
#define CFI_X86_64_UNWIND_SIGFRAME_UNCOMMON_REGISTER_COUNT  61




/* Register <--> Landing-pad Common/Uncommon-register mapping
 * Currently, landing-pad unwinding is  only needed for inline,  exception-enabled
 * system calls, and as such only the %eflags register is considered common, since
 * that one needs to be  modified in order to  set EFLAGS.DF=0 during landing  pad
 * adjustments. */
#define CFI_X86_64_UNWIND_LANDING_COMMON_REGISTER_RFLAGS 0
#define CFI_X86_64_UNWIND_LANDING_COMMON_REGISTER_COUNT  1

#define CFI_X86_64_UNWIND_LANDING_UNCOMMON_REGISTER_SP     CFI_X86_64_UNWIND_LANDING_UNCOMMON_REGISTER_RSP
#define CFI_X86_64_UNWIND_LANDING_UNCOMMON_REGISTER_RAX    0
#define CFI_X86_64_UNWIND_LANDING_UNCOMMON_REGISTER_RDX    1
#define CFI_X86_64_UNWIND_LANDING_UNCOMMON_REGISTER_RCX    2
#define CFI_X86_64_UNWIND_LANDING_UNCOMMON_REGISTER_RBX    3
#define CFI_X86_64_UNWIND_LANDING_UNCOMMON_REGISTER_RSI    4
#define CFI_X86_64_UNWIND_LANDING_UNCOMMON_REGISTER_RDI    5
#define CFI_X86_64_UNWIND_LANDING_UNCOMMON_REGISTER_RBP    6
#define CFI_X86_64_UNWIND_LANDING_UNCOMMON_REGISTER_RSP    7
#define CFI_X86_64_UNWIND_LANDING_UNCOMMON_REGISTER_R8     8
#define CFI_X86_64_UNWIND_LANDING_UNCOMMON_REGISTER_R9     9
#define CFI_X86_64_UNWIND_LANDING_UNCOMMON_REGISTER_R10    10
#define CFI_X86_64_UNWIND_LANDING_UNCOMMON_REGISTER_R11    11
#define CFI_X86_64_UNWIND_LANDING_UNCOMMON_REGISTER_R12    12
#define CFI_X86_64_UNWIND_LANDING_UNCOMMON_REGISTER_R13    13
#define CFI_X86_64_UNWIND_LANDING_UNCOMMON_REGISTER_R14    14
#define CFI_X86_64_UNWIND_LANDING_UNCOMMON_REGISTER_R15    15
#define CFI_X86_64_UNWIND_LANDING_UNCOMMON_REGISTER_RIP    16
#define CFI_X86_64_UNWIND_LANDING_UNCOMMON_REGISTER_XMM0   17
#define CFI_X86_64_UNWIND_LANDING_UNCOMMON_REGISTER_XMM1   18
#define CFI_X86_64_UNWIND_LANDING_UNCOMMON_REGISTER_XMM2   19
#define CFI_X86_64_UNWIND_LANDING_UNCOMMON_REGISTER_XMM3   20
#define CFI_X86_64_UNWIND_LANDING_UNCOMMON_REGISTER_XMM4   21
#define CFI_X86_64_UNWIND_LANDING_UNCOMMON_REGISTER_XMM5   22
#define CFI_X86_64_UNWIND_LANDING_UNCOMMON_REGISTER_XMM6   23
#define CFI_X86_64_UNWIND_LANDING_UNCOMMON_REGISTER_XMM7   24
#define CFI_X86_64_UNWIND_LANDING_UNCOMMON_REGISTER_XMM8   25
#define CFI_X86_64_UNWIND_LANDING_UNCOMMON_REGISTER_XMM9   26
#define CFI_X86_64_UNWIND_LANDING_UNCOMMON_REGISTER_XMM10  27
#define CFI_X86_64_UNWIND_LANDING_UNCOMMON_REGISTER_XMM11  28
#define CFI_X86_64_UNWIND_LANDING_UNCOMMON_REGISTER_XMM12  29
#define CFI_X86_64_UNWIND_LANDING_UNCOMMON_REGISTER_XMM13  30
#define CFI_X86_64_UNWIND_LANDING_UNCOMMON_REGISTER_XMM14  31
#define CFI_X86_64_UNWIND_LANDING_UNCOMMON_REGISTER_XMM15  32
#define CFI_X86_64_UNWIND_LANDING_UNCOMMON_REGISTER_ST0    33
#define CFI_X86_64_UNWIND_LANDING_UNCOMMON_REGISTER_ST1    34
#define CFI_X86_64_UNWIND_LANDING_UNCOMMON_REGISTER_ST2    35
#define CFI_X86_64_UNWIND_LANDING_UNCOMMON_REGISTER_ST3    36
#define CFI_X86_64_UNWIND_LANDING_UNCOMMON_REGISTER_ST4    37
#define CFI_X86_64_UNWIND_LANDING_UNCOMMON_REGISTER_ST5    38
#define CFI_X86_64_UNWIND_LANDING_UNCOMMON_REGISTER_ST6    39
#define CFI_X86_64_UNWIND_LANDING_UNCOMMON_REGISTER_ST7    40
#define CFI_X86_64_UNWIND_LANDING_UNCOMMON_REGISTER_MM0    41
#define CFI_X86_64_UNWIND_LANDING_UNCOMMON_REGISTER_MM1    42
#define CFI_X86_64_UNWIND_LANDING_UNCOMMON_REGISTER_MM2    43
#define CFI_X86_64_UNWIND_LANDING_UNCOMMON_REGISTER_MM3    44
#define CFI_X86_64_UNWIND_LANDING_UNCOMMON_REGISTER_MM4    45
#define CFI_X86_64_UNWIND_LANDING_UNCOMMON_REGISTER_MM5    46
#define CFI_X86_64_UNWIND_LANDING_UNCOMMON_REGISTER_MM6    47
#define CFI_X86_64_UNWIND_LANDING_UNCOMMON_REGISTER_MM7    48
#define CFI_X86_64_UNWIND_LANDING_UNCOMMON_REGISTER_ES     49
#define CFI_X86_64_UNWIND_LANDING_UNCOMMON_REGISTER_CS     50
#define CFI_X86_64_UNWIND_LANDING_UNCOMMON_REGISTER_SS     51
#define CFI_X86_64_UNWIND_LANDING_UNCOMMON_REGISTER_DS     52
#define CFI_X86_64_UNWIND_LANDING_UNCOMMON_REGISTER_FS     53
#define CFI_X86_64_UNWIND_LANDING_UNCOMMON_REGISTER_GS     54
#define CFI_X86_64_UNWIND_LANDING_UNCOMMON_REGISTER_FSBASE 55
#define CFI_X86_64_UNWIND_LANDING_UNCOMMON_REGISTER_GSBASE 56
#define CFI_X86_64_UNWIND_LANDING_UNCOMMON_REGISTER_TR     57
#define CFI_X86_64_UNWIND_LANDING_UNCOMMON_REGISTER_LDTR   58
#define CFI_X86_64_UNWIND_LANDING_UNCOMMON_REGISTER_MXCSR  59
#define CFI_X86_64_UNWIND_LANDING_UNCOMMON_REGISTER_FCW    60
#define CFI_X86_64_UNWIND_LANDING_UNCOMMON_REGISTER_FSW    61
#define CFI_X86_64_UNWIND_LANDING_UNCOMMON_REGISTER_XMM16  62
#define CFI_X86_64_UNWIND_LANDING_UNCOMMON_REGISTER_XMM17  63
#define CFI_X86_64_UNWIND_LANDING_UNCOMMON_REGISTER_XMM18  64
#define CFI_X86_64_UNWIND_LANDING_UNCOMMON_REGISTER_XMM19  65
#define CFI_X86_64_UNWIND_LANDING_UNCOMMON_REGISTER_XMM20  66
#define CFI_X86_64_UNWIND_LANDING_UNCOMMON_REGISTER_XMM21  67
#define CFI_X86_64_UNWIND_LANDING_UNCOMMON_REGISTER_XMM22  68
#define CFI_X86_64_UNWIND_LANDING_UNCOMMON_REGISTER_XMM23  69
#define CFI_X86_64_UNWIND_LANDING_UNCOMMON_REGISTER_XMM24  70
#define CFI_X86_64_UNWIND_LANDING_UNCOMMON_REGISTER_XMM25  71
#define CFI_X86_64_UNWIND_LANDING_UNCOMMON_REGISTER_XMM26  72
#define CFI_X86_64_UNWIND_LANDING_UNCOMMON_REGISTER_XMM27  73
#define CFI_X86_64_UNWIND_LANDING_UNCOMMON_REGISTER_XMM28  74
#define CFI_X86_64_UNWIND_LANDING_UNCOMMON_REGISTER_XMM29  75
#define CFI_X86_64_UNWIND_LANDING_UNCOMMON_REGISTER_XMM30  76
#define CFI_X86_64_UNWIND_LANDING_UNCOMMON_REGISTER_XMM31  77
#define CFI_X86_64_UNWIND_LANDING_UNCOMMON_REGISTER_K0     78
#define CFI_X86_64_UNWIND_LANDING_UNCOMMON_REGISTER_K1     79
#define CFI_X86_64_UNWIND_LANDING_UNCOMMON_REGISTER_K2     80
#define CFI_X86_64_UNWIND_LANDING_UNCOMMON_REGISTER_K3     81
#define CFI_X86_64_UNWIND_LANDING_UNCOMMON_REGISTER_K4     82
#define CFI_X86_64_UNWIND_LANDING_UNCOMMON_REGISTER_K5     83
#define CFI_X86_64_UNWIND_LANDING_UNCOMMON_REGISTER_K6     84
#define CFI_X86_64_UNWIND_LANDING_UNCOMMON_REGISTER_K7     85
#define CFI_X86_64_UNWIND_LANDING_UNCOMMON_REGISTER_COUNT  86


/*[[[deemon
import * from deemon;
import * from ....misc.libgen.strendN;
import * from ....misc.libgen.converter;
local macros: {string: int} = Dict(enumerateIntegerMacrosFromFile(__FILE__));
printArrayDefineMacro("DEFINE_cfi_x86_64_unwind_register_dw2common", generateArrayMapping(macros, "CFI_X86_64_UNWIND_REGISTER_", "CFI_X86_64_UNWIND_COMMON_REGISTER_"));
printArrayDefineMacro("DEFINE_cfi_x86_64_unwind_register_dw2uncommon", generateArrayMapping(macros, "CFI_X86_64_UNWIND_REGISTER_", "CFI_X86_64_UNWIND_UNCOMMON_REGISTER_"));
printArrayDefineMacro("DEFINE_cfi_x86_64_unwind_register_common2dw", generateArrayMapping(macros, "CFI_X86_64_UNWIND_COMMON_REGISTER_", "CFI_X86_64_UNWIND_REGISTER_"));
printArrayDefineMacro("DEFINE_cfi_x86_64_unwind_register_uncommon2dw", generateArrayMapping(macros, "CFI_X86_64_UNWIND_UNCOMMON_REGISTER_", "CFI_X86_64_UNWIND_REGISTER_"));
printArrayDefineMacro("DEFINE_cfi_x86_64_unwind_sigframe_register_dw2common", generateArrayMapping(macros, "CFI_X86_64_UNWIND_REGISTER_", "CFI_X86_64_UNWIND_SIGFRAME_COMMON_REGISTER_"));
printArrayDefineMacro("DEFINE_cfi_x86_64_unwind_sigframe_register_dw2uncommon", generateArrayMapping(macros, "CFI_X86_64_UNWIND_REGISTER_", "CFI_X86_64_UNWIND_SIGFRAME_UNCOMMON_REGISTER_"));
printArrayDefineMacro("DEFINE_cfi_x86_64_unwind_sigframe_register_common2dw", generateArrayMapping(macros, "CFI_X86_64_UNWIND_SIGFRAME_COMMON_REGISTER_", "CFI_X86_64_UNWIND_REGISTER_"));
printArrayDefineMacro("DEFINE_cfi_x86_64_unwind_sigframe_register_uncommon2dw", generateArrayMapping(macros, "CFI_X86_64_UNWIND_SIGFRAME_UNCOMMON_REGISTER_", "CFI_X86_64_UNWIND_REGISTER_"));
printArrayDefineMacro("DEFINE_cfi_x86_64_unwind_landing_register_dw2common", generateArrayMapping(macros, "CFI_X86_64_UNWIND_REGISTER_", "CFI_X86_64_UNWIND_LANDING_COMMON_REGISTER_"));
printArrayDefineMacro("DEFINE_cfi_x86_64_unwind_landing_register_dw2uncommon", generateArrayMapping(macros, "CFI_X86_64_UNWIND_REGISTER_", "CFI_X86_64_UNWIND_LANDING_UNCOMMON_REGISTER_"));
printArrayDefineMacro("DEFINE_cfi_x86_64_unwind_landing_register_common2dw", generateArrayMapping(macros, "CFI_X86_64_UNWIND_LANDING_COMMON_REGISTER_", "CFI_X86_64_UNWIND_REGISTER_"));
printArrayDefineMacro("DEFINE_cfi_x86_64_unwind_landing_register_uncommon2dw", generateArrayMapping(macros, "CFI_X86_64_UNWIND_LANDING_UNCOMMON_REGISTER_", "CFI_X86_64_UNWIND_REGISTER_"));
]]]*/
#define DEFINE_cfi_x86_64_unwind_register_dw2common(name)                                                              \
	__UINT8_TYPE__ const name[127] = { 255, 255, 255, 0,   255, 255, 1,   255, 255, 255, 255, 255, 2,   3,   4,   5,   \
	                                   6,   255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, \
	                                   255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, \
	                                   255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, \
	                                   255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, \
	                                   255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, \
	                                   255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, \
	                                   255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 7 }
#define DEFINE_cfi_x86_64_unwind_register_dw2uncommon(name)                                                            \
	__UINT8_TYPE__ const name[127] = { 0,   1,   2,   255, 3,   4,   255, 5,   6,   7,   8,   9,   255, 255, 255, 255, \
	                                   255, 10,  11,  12,  13,  14,  15,  16,  17,  18,  19,  20,  21,  22,  23,  24,  \
	                                   25,  26,  27,  28,  29,  30,  31,  32,  33,  34,  35,  36,  37,  38,  39,  40,  \
	                                   41,  42,  43,  44,  45,  46,  47,  48,  255, 255, 49,  50,  255, 255, 51,  52,  \
	                                   53,  54,  55,  56,  57,  58,  59,  60,  61,  62,  63,  64,  65,  66,  67,  68,  \
	                                   69,  70,  71,  255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, \
	                                   255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, \
	                                   255, 255, 255, 255, 255, 255, 72,  73,  74,  75,  76,  77,  78,  79,  80 }
#define DEFINE_cfi_x86_64_unwind_register_common2dw(name) \
	__UINT8_TYPE__ const name[8] = { 3, 6, 12, 13, 14, 15, 16, 126 }
#define DEFINE_cfi_x86_64_unwind_register_uncommon2dw(name)                                                           \
	__UINT8_TYPE__ const name[81] = { 0,   1,   2,   4,   5,   7,   8,   9,   10,  11,  17,  18,  19,  20,  21,  22,  \
	                                  23,  24,  25,  26,  27,  28,  29,  30,  31,  32,  33,  34,  35,  36,  37,  38,  \
	                                  39,  40,  41,  42,  43,  44,  45,  46,  47,  48,  49,  50,  51,  52,  53,  54,  \
	                                  55,  58,  59,  62,  63,  64,  65,  66,  67,  68,  69,  70,  71,  72,  73,  74,  \
	                                  75,  76,  77,  78,  79,  80,  81,  82,  118, 119, 120, 121, 122, 123, 124, 125, \
	                                  126 }
#define DEFINE_cfi_x86_64_unwind_sigframe_register_dw2common(name)                                                     \
	__UINT8_TYPE__ const name[127] = { 0,   1,   2,   3,   4,   5,   6,   7,   8,   9,   10,  11,  12,  13,  14,  15,  \
	                                   16,  255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, \
	                                   255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, \
	                                   255, 17,  18,  19,  20,  21,  22,  23,  255, 255, 24,  25,  255, 255, 255, 255, \
	                                   255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, \
	                                   255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, \
	                                   255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, \
	                                   255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 26 }
#define DEFINE_cfi_x86_64_unwind_sigframe_register_dw2uncommon(name)                                                   \
	__UINT8_TYPE__ const name[127] = { 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, \
	                                   255, 0,   1,   2,   3,   4,   5,   6,   7,   8,   9,   10,  11,  12,  13,  14,  \
	                                   15,  16,  17,  18,  19,  20,  21,  22,  23,  24,  25,  26,  27,  28,  29,  30,  \
	                                   31,  255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 32,  33,  \
	                                   34,  35,  36,  37,  38,  39,  40,  41,  42,  43,  44,  45,  46,  47,  48,  49,  \
	                                   50,  51,  52,  255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, \
	                                   255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, \
	                                   255, 255, 255, 255, 255, 255, 53,  54,  55,  56,  57,  58,  59,  60,  61 }
#define DEFINE_cfi_x86_64_unwind_sigframe_register_common2dw(name)                                                    \
	__UINT8_TYPE__ const name[27] = { 0,   1,   2,   3,   4,   5,   6,   7,   8,   9,   10,  11,  12,  13,  14,  15,  \
	                                  16,  49,  50,  51,  52,  53,  54,  55,  58,  59,  126 }
#define DEFINE_cfi_x86_64_unwind_sigframe_register_uncommon2dw(name)                                                  \
	__UINT8_TYPE__ const name[62] = { 17,  18,  19,  20,  21,  22,  23,  24,  25,  26,  27,  28,  29,  30,  31,  32,  \
	                                  33,  34,  35,  36,  37,  38,  39,  40,  41,  42,  43,  44,  45,  46,  47,  48,  \
	                                  62,  63,  64,  65,  66,  67,  68,  69,  70,  71,  72,  73,  74,  75,  76,  77,  \
	                                  78,  79,  80,  81,  82,  118, 119, 120, 121, 122, 123, 124, 125, 126 }
#define DEFINE_cfi_x86_64_unwind_landing_register_dw2common(name)                                                      \
	__UINT8_TYPE__ const name[127] = { 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, \
	                                   255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, \
	                                   255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, \
	                                   255, 0,   255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, \
	                                   255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, \
	                                   255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, \
	                                   255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, \
	                                   255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 1 }
#define DEFINE_cfi_x86_64_unwind_landing_register_dw2uncommon(name)                                                    \
	__UINT8_TYPE__ const name[127] = { 0,   1,   2,   3,   4,   5,   6,   7,   8,   9,   10,  11,  12,  13,  14,  15,  \
	                                   16,  17,  18,  19,  20,  21,  22,  23,  24,  25,  26,  27,  28,  29,  30,  31,  \
	                                   32,  33,  34,  35,  36,  37,  38,  39,  40,  41,  42,  43,  44,  45,  46,  47,  \
	                                   48,  255, 49,  50,  51,  52,  53,  54,  255, 255, 55,  56,  255, 255, 57,  58,  \
	                                   59,  60,  61,  62,  63,  64,  65,  66,  67,  68,  69,  70,  71,  72,  73,  74,  \
	                                   75,  76,  77,  255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, \
	                                   255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, \
	                                   255, 255, 255, 255, 255, 255, 78,  79,  80,  81,  82,  83,  84,  85,  86 }
#define DEFINE_cfi_x86_64_unwind_landing_register_common2dw(name) \
	__UINT8_TYPE__ const name[2] = { 49, 126 }
#define DEFINE_cfi_x86_64_unwind_landing_register_uncommon2dw(name)                                                   \
	__UINT8_TYPE__ const name[87] = { 0,   1,   2,   3,   4,   5,   6,   7,   8,   9,   10,  11,  12,  13,  14,  15,  \
	                                  16,  17,  18,  19,  20,  21,  22,  23,  24,  25,  26,  27,  28,  29,  30,  31,  \
	                                  32,  33,  34,  35,  36,  37,  38,  39,  40,  41,  42,  43,  44,  45,  46,  47,  \
	                                  48,  50,  51,  52,  53,  54,  55,  58,  59,  62,  63,  64,  65,  66,  67,  68,  \
	                                  69,  70,  71,  72,  73,  74,  75,  76,  77,  78,  79,  80,  81,  82,  118, 119, \
	                                  120, 121, 122, 123, 124, 125, 126 }
/*[[[end]]]*/





/* Host-specific CFI constants. */
#ifdef __x86_64__
#define CFI_REGISTER_MAXSIZE                        CFI_X86_64_REGISTER_MAXSIZE
#define CFI_REGISTER_SIZE(addrsize, regno)          CFI_X86_64_REGISTER_SIZE(regno)
#define CFI_REGISTER_MEMSIZE(addrsize, regno)       CFI_X86_64_REGISTER_SIZE(regno)      /* Register size for read/write to/from memory */
#define CFI_REGISTER_MEMSIZE_IS_SIZE                1                                    /* Hint: `CFI_REGISTER_MEMSIZE() == CFI_REGISTER_SIZE()' */
#define CFI_UNWIND_REGISTER_PC(addrsize)            CFI_X86_64_UNWIND_REGISTER_PC        /* The register containing the program counter. */
#define CFI_UNWIND_REGISTER_SP(addrsize)            CFI_X86_64_UNWIND_REGISTER_SP        /* The register for the CFA. */
#define CFI_UNWIND_REGISTER_EXCEPTION(addrsize)     CFI_X86_64_UNWIND_REGISTER_EXCEPTION /* The register used to hold the current exception upon entry to an exception handler. */
#define CFI_UNWIND_REGISTER_MAXCOUNT                CFI_X86_64_UNWIND_REGISTER_COUNT
#define CFI_UNWIND_REGISTER_COUNT(addrsize)         CFI_X86_64_UNWIND_REGISTER_COUNT
#define CFI_UNWIND_IS_FPU_REGISTER(addrsize, regno) CFI_X86_64_UNWIND_IS_FPU_REGISTER(regno)

/* Normal common/uncommon */
#define CFI_UNWIND_COMMON_REGISTER_MAXCOUNT                    CFI_X86_64_UNWIND_COMMON_REGISTER_COUNT
#define CFI_UNWIND_COMMON_REGISTER_COUNT(addrsize)             CFI_X86_64_UNWIND_COMMON_REGISTER_COUNT
#define CFI_UNWIND_UNCOMMON_REGISTER_SP(addrsize)              CFI_X86_64_UNWIND_UNCOMMON_REGISTER_SP
#define CFI_UNWIND_UNCOMMON_REGISTER_MAXCOUNT                  CFI_X86_64_UNWIND_UNCOMMON_REGISTER_COUNT
#define CFI_UNWIND_UNCOMMON_REGISTER_COUNT(addrsize)           CFI_X86_64_UNWIND_UNCOMMON_REGISTER_COUNT
#define DEFINE_cfi_unwind_register_dw2common(addrsize, name)   DEFINE_cfi_x86_64_unwind_register_dw2common(name)
#define DEFINE_cfi_unwind_register_dw2uncommon(addrsize, name) DEFINE_cfi_x86_64_unwind_register_dw2uncommon(name)
#define DEFINE_cfi_unwind_register_common2dw(addrsize, name)   DEFINE_cfi_x86_64_unwind_register_common2dw(name)
#define DEFINE_cfi_unwind_register_uncommon2dw(addrsize, name) DEFINE_cfi_x86_64_unwind_register_uncommon2dw(name)

/* Sigframe common/uncommon */
#define CFI_UNWIND_SIGFRAME_COMMON_REGISTER_SP(addrsize)                CFI_X86_64_UNWIND_SIGFRAME_COMMON_REGISTER_SP
#define CFI_UNWIND_SIGFRAME_COMMON_REGISTER_MAXCOUNT                    CFI_X86_64_UNWIND_SIGFRAME_COMMON_REGISTER_COUNT
#define CFI_UNWIND_SIGFRAME_COMMON_REGISTER_COUNT(addrsize)             CFI_X86_64_UNWIND_SIGFRAME_COMMON_REGISTER_COUNT
#define CFI_UNWIND_SIGFRAME_UNCOMMON_REGISTER_MAXCOUNT                  CFI_X86_64_UNWIND_SIGFRAME_UNCOMMON_REGISTER_COUNT
#define CFI_UNWIND_SIGFRAME_UNCOMMON_REGISTER_COUNT(addrsize)           CFI_X86_64_UNWIND_SIGFRAME_UNCOMMON_REGISTER_COUNT
#define DEFINE_cfi_unwind_sigframe_register_dw2common(addrsize, name)   DEFINE_cfi_x86_64_unwind_sigframe_register_dw2common(name)
#define DEFINE_cfi_unwind_sigframe_register_dw2uncommon(addrsize, name) DEFINE_cfi_x86_64_unwind_sigframe_register_dw2uncommon(name)
#define DEFINE_cfi_unwind_sigframe_register_common2dw(addrsize, name)   DEFINE_cfi_x86_64_unwind_sigframe_register_common2dw(name)
#define DEFINE_cfi_unwind_sigframe_register_uncommon2dw(addrsize, name) DEFINE_cfi_x86_64_unwind_sigframe_register_uncommon2dw(name)

/* Landing-pad common/uncommon */
#define CFI_UNWIND_LANDING_UNCOMMON_REGISTER_SP(addrsize)              CFI_X86_64_UNWIND_LANDING_UNCOMMON_REGISTER_SP
#define CFI_UNWIND_LANDING_COMMON_REGISTER_MAXCOUNT                    CFI_X86_64_UNWIND_LANDING_COMMON_REGISTER_COUNT
#define CFI_UNWIND_LANDING_COMMON_REGISTER_COUNT(addrsize)             CFI_X86_64_UNWIND_LANDING_COMMON_REGISTER_COUNT
#define CFI_UNWIND_LANDING_UNCOMMON_REGISTER_MAXCOUNT                  CFI_X86_64_UNWIND_LANDING_UNCOMMON_REGISTER_COUNT
#define CFI_UNWIND_LANDING_UNCOMMON_REGISTER_COUNT(addrsize)           CFI_X86_64_UNWIND_LANDING_UNCOMMON_REGISTER_COUNT
#define DEFINE_cfi_unwind_landing_register_dw2common(addrsize, name)   DEFINE_cfi_x86_64_unwind_landing_register_dw2common(name)
#define DEFINE_cfi_unwind_landing_register_dw2uncommon(addrsize, name) DEFINE_cfi_x86_64_unwind_landing_register_dw2uncommon(name)
#define DEFINE_cfi_unwind_landing_register_common2dw(addrsize, name)   DEFINE_cfi_x86_64_unwind_landing_register_common2dw(name)
#define DEFINE_cfi_unwind_landing_register_uncommon2dw(addrsize, name) DEFINE_cfi_x86_64_unwind_landing_register_uncommon2dw(name)

#include <libunwind/asm/features.h> /* LIBUNWIND_HAVE_GETSETREG_COMPAT */
#ifdef LIBUNWIND_HAVE_GETSETREG_COMPAT
#include "i386.h"
#define CFI_ADDRSIZE_ISCOMPAT(addrsize) __unlikely((addrsize) < 8)


#if CFI_386_REGISTER_MAXSIZE > CFI_REGISTER_MAXSIZE
#undef CFI_REGISTER_MAXSIZE
#define CFI_REGISTER_MAXSIZE CFI_386_REGISTER_MAXSIZE
#endif /* CFI_386_REGISTER_MAXSIZE > CFI_REGISTER_MAXSIZE */
#if CFI_386_UNWIND_REGISTER_COUNT > CFI_UNWIND_REGISTER_MAXCOUNT
#undef CFI_UNWIND_REGISTER_MAXCOUNT
#define CFI_UNWIND_REGISTER_MAXCOUNT CFI_386_UNWIND_REGISTER_COUNT
#endif /* CFI_386_UNWIND_REGISTER_COUNT > CFI_UNWIND_REGISTER_MAXCOUNT */
#if CFI_386_UNWIND_COMMON_REGISTER_COUNT > CFI_UNWIND_COMMON_REGISTER_MAXCOUNT
#undef CFI_UNWIND_COMMON_REGISTER_MAXCOUNT
#define CFI_UNWIND_COMMON_REGISTER_MAXCOUNT CFI_386_UNWIND_COMMON_REGISTER_COUNT
#endif /* CFI_386_UNWIND_COMMON_REGISTER_COUNT > CFI_UNWIND_COMMON_REGISTER_MAXCOUNT */
#if CFI_386_UNWIND_UNCOMMON_REGISTER_COUNT > CFI_UNWIND_UNCOMMON_REGISTER_MAXCOUNT
#undef CFI_UNWIND_UNCOMMON_REGISTER_MAXCOUNT
#define CFI_UNWIND_UNCOMMON_REGISTER_MAXCOUNT CFI_386_UNWIND_UNCOMMON_REGISTER_COUNT
#endif /* CFI_386_UNWIND_UNCOMMON_REGISTER_COUNT > CFI_UNWIND_UNCOMMON_REGISTER_MAXCOUNT */
#if CFI_386_UNWIND_SIGFRAME_COMMON_REGISTER_COUNT > CFI_UNWIND_SIGFRAME_COMMON_REGISTER_MAXCOUNT
#undef CFI_UNWIND_SIGFRAME_COMMON_REGISTER_MAXCOUNT
#define CFI_UNWIND_SIGFRAME_COMMON_REGISTER_MAXCOUNT CFI_386_UNWIND_SIGFRAME_COMMON_REGISTER_COUNT
#endif /* CFI_386_UNWIND_SIGFRAME_COMMON_REGISTER_COUNT > CFI_UNWIND_SIGFRAME_COMMON_REGISTER_MAXCOUNT */
#if CFI_386_UNWIND_SIGFRAME_UNCOMMON_REGISTER_COUNT > CFI_UNWIND_SIGFRAME_UNCOMMON_REGISTER_MAXCOUNT
#undef CFI_UNWIND_SIGFRAME_UNCOMMON_REGISTER_MAXCOUNT
#define CFI_UNWIND_SIGFRAME_UNCOMMON_REGISTER_MAXCOUNT CFI_386_UNWIND_SIGFRAME_UNCOMMON_REGISTER_COUNT
#endif /* CFI_386_UNWIND_SIGFRAME_UNCOMMON_REGISTER_COUNT > CFI_UNWIND_SIGFRAME_UNCOMMON_REGISTER_MAXCOUNT */

#undef CFI_REGISTER_SIZE
#undef CFI_REGISTER_MEMSIZE
#undef CFI_REGISTER_MEMSIZE_IS_SIZE
#undef CFI_UNWIND_REGISTER_PC
#undef CFI_UNWIND_REGISTER_SP
#undef CFI_UNWIND_REGISTER_EXCEPTION
#undef CFI_UNWIND_REGISTER_COUNT
#undef CFI_UNWIND_IS_FPU_REGISTER
#undef CFI_UNWIND_COMMON_REGISTER_COUNT
#undef CFI_UNWIND_UNCOMMON_REGISTER_SP
#undef CFI_UNWIND_UNCOMMON_REGISTER_COUNT
#undef CFI_UNWIND_SIGFRAME_COMMON_REGISTER_SP
#undef CFI_UNWIND_SIGFRAME_COMMON_REGISTER_COUNT
#undef CFI_UNWIND_SIGFRAME_UNCOMMON_REGISTER_COUNT
#define CFI_REGISTER_MEMSIZE(addrsize, regno)                 (__likely((addrsize) >= 8) ? CFI_X86_64_REGISTER_SIZE(regno) : CFI_386_REGISTER_SIZE(regno))
#define CFI_REGISTER_SIZE(addrsize, regno)                    (__likely((addrsize) >= 8) ? CFI_X86_64_REGISTER_SIZE(regno) : CFI_386_UNWIND_IS_FPU_REGISTER(regno) ? CFI_X86_64_UNWIND_FPU_REGISTER_SIZE : CFI_X86_64_UNWIND_GPR_REGISTER_SIZE)
#define CFI_UNWIND_REGISTER_PC(addrsize)                      (__likely((addrsize) >= 8) ? CFI_X86_64_UNWIND_REGISTER_PC : CFI_386_UNWIND_REGISTER_PC)
#define CFI_UNWIND_REGISTER_SP(addrsize)                      (__likely((addrsize) >= 8) ? CFI_X86_64_UNWIND_REGISTER_SP : CFI_386_UNWIND_REGISTER_SP)
#define CFI_UNWIND_REGISTER_EXCEPTION(addrsize)               (__likely((addrsize) >= 8) ? CFI_X86_64_UNWIND_REGISTER_EXCEPTION : CFI_386_UNWIND_REGISTER_EXCEPTION)
#define CFI_UNWIND_REGISTER_COUNT(addrsize)                   (__likely((addrsize) >= 8) ? CFI_X86_64_UNWIND_REGISTER_COUNT : CFI_386_UNWIND_REGISTER_COUNT)
#define CFI_UNWIND_IS_FPU_REGISTER(addrsize, regno)           (__likely((addrsize) >= 8) ? CFI_X86_64_UNWIND_IS_FPU_REGISTER(regno) : CFI_386_UNWIND_IS_FPU_REGISTER(regno))
#define CFI_UNWIND_COMMON_REGISTER_COUNT(addrsize)            (__likely((addrsize) >= 8) ? CFI_X86_64_UNWIND_COMMON_REGISTER_COUNT : CFI_386_UNWIND_COMMON_REGISTER_COUNT)
#define CFI_UNWIND_UNCOMMON_REGISTER_SP(addrsize)             (__likely((addrsize) >= 8) ? CFI_X86_64_UNWIND_UNCOMMON_REGISTER_SP : CFI_386_UNWIND_UNCOMMON_REGISTER_SP)
#define CFI_UNWIND_UNCOMMON_REGISTER_COUNT(addrsize)          (__likely((addrsize) >= 8) ? CFI_X86_64_UNWIND_UNCOMMON_REGISTER_COUNT : CFI_386_UNWIND_UNCOMMON_REGISTER_COUNT)
#define CFI_UNWIND_SIGFRAME_COMMON_REGISTER_SP(addrsize)      (__likely((addrsize) >= 8) ? CFI_X86_64_UNWIND_SIGFRAME_COMMON_REGISTER_SP : CFI_386_UNWIND_SIGFRAME_COMMON_REGISTER_SP)
#define CFI_UNWIND_SIGFRAME_COMMON_REGISTER_COUNT(addrsize)   (__likely((addrsize) >= 8) ? CFI_X86_64_UNWIND_SIGFRAME_COMMON_REGISTER_COUNT : CFI_386_UNWIND_SIGFRAME_COMMON_REGISTER_COUNT)
#define CFI_UNWIND_SIGFRAME_UNCOMMON_REGISTER_COUNT(addrsize) (__likely((addrsize) >= 8) ? CFI_X86_64_UNWIND_SIGFRAME_UNCOMMON_REGISTER_COUNT : CFI_386_UNWIND_SIGFRAME_UNCOMMON_REGISTER_COUNT)

#undef DEFINE_cfi_unwind_register_dw2common
#undef DEFINE_cfi_unwind_register_dw2uncommon
#undef DEFINE_cfi_unwind_register_common2dw
#undef DEFINE_cfi_unwind_register_uncommon2dw
#undef DEFINE_cfi_unwind_sigframe_register_dw2common
#undef DEFINE_cfi_unwind_sigframe_register_dw2uncommon
#undef DEFINE_cfi_unwind_sigframe_register_common2dw
#undef DEFINE_cfi_unwind_sigframe_register_uncommon2dw
#define __PRIVATE_DEFINE_cfi_unwind_register_dw2common_4                          DEFINE_cfi_386_unwind_register_dw2common
#define __PRIVATE_DEFINE_cfi_unwind_register_dw2common_8                          DEFINE_cfi_x86_64_unwind_register_dw2common
#define __PRIVATE_DEFINE_cfi_unwind_register_dw2uncommon_4                        DEFINE_cfi_386_unwind_register_dw2uncommon
#define __PRIVATE_DEFINE_cfi_unwind_register_dw2uncommon_8                        DEFINE_cfi_x86_64_unwind_register_dw2uncommon
#define __PRIVATE_DEFINE_cfi_unwind_register_common2dw_4                          DEFINE_cfi_386_unwind_register_common2dw
#define __PRIVATE_DEFINE_cfi_unwind_register_common2dw_8                          DEFINE_cfi_x86_64_unwind_register_common2dw
#define __PRIVATE_DEFINE_cfi_unwind_register_uncommon2dw_4                        DEFINE_cfi_386_unwind_register_uncommon2dw
#define __PRIVATE_DEFINE_cfi_unwind_register_uncommon2dw_8                        DEFINE_cfi_x86_64_unwind_register_uncommon2dw
#define __PRIVATE_DEFINE_cfi_unwind_sigframe_register_dw2common_4                 DEFINE_cfi_386_unwind_sigframe_register_dw2common
#define __PRIVATE_DEFINE_cfi_unwind_sigframe_register_dw2common_8                 DEFINE_cfi_x86_64_unwind_sigframe_register_dw2common
#define __PRIVATE_DEFINE_cfi_unwind_sigframe_register_dw2uncommon_4               DEFINE_cfi_386_unwind_sigframe_register_dw2uncommon
#define __PRIVATE_DEFINE_cfi_unwind_sigframe_register_dw2uncommon_8               DEFINE_cfi_x86_64_unwind_sigframe_register_dw2uncommon
#define __PRIVATE_DEFINE_cfi_unwind_sigframe_register_common2dw_4                 DEFINE_cfi_386_unwind_sigframe_register_common2dw
#define __PRIVATE_DEFINE_cfi_unwind_sigframe_register_common2dw_8                 DEFINE_cfi_x86_64_unwind_sigframe_register_common2dw
#define __PRIVATE_DEFINE_cfi_unwind_sigframe_register_uncommon2dw_4               DEFINE_cfi_386_unwind_sigframe_register_uncommon2dw
#define __PRIVATE_DEFINE_cfi_unwind_sigframe_register_uncommon2dw_8               DEFINE_cfi_x86_64_unwind_sigframe_register_uncommon2dw
#define __PRIVATE_DEFINE_cfi_unwind_register_dw2common(addrsize, name)            __PRIVATE_DEFINE_cfi_unwind_register_dw2common_##addrsize(name)
#define __PRIVATE_DEFINE_cfi_unwind_register_dw2uncommon(addrsize, name)          __PRIVATE_DEFINE_cfi_unwind_register_dw2uncommon_##addrsize(name)
#define __PRIVATE_DEFINE_cfi_unwind_register_common2dw(addrsize, name)            __PRIVATE_DEFINE_cfi_unwind_register_common2dw_##addrsize(name)
#define __PRIVATE_DEFINE_cfi_unwind_register_uncommon2dw(addrsize, name)          __PRIVATE_DEFINE_cfi_unwind_register_uncommon2dw_##addrsize(name)
#define __PRIVATE_DEFINE_cfi_unwind_sigframe_register_dw2common(addrsize, name)   __PRIVATE_DEFINE_cfi_unwind_sigframe_register_dw2common_##addrsize(name)
#define __PRIVATE_DEFINE_cfi_unwind_sigframe_register_dw2uncommon(addrsize, name) __PRIVATE_DEFINE_cfi_unwind_sigframe_register_dw2uncommon_##addrsize(name)
#define __PRIVATE_DEFINE_cfi_unwind_sigframe_register_common2dw(addrsize, name)   __PRIVATE_DEFINE_cfi_unwind_sigframe_register_common2dw_##addrsize(name)
#define __PRIVATE_DEFINE_cfi_unwind_sigframe_register_uncommon2dw(addrsize, name) __PRIVATE_DEFINE_cfi_unwind_sigframe_register_uncommon2dw_##addrsize(name)
#define DEFINE_cfi_unwind_register_dw2common(addrsize, name)                      __PRIVATE_DEFINE_cfi_unwind_register_dw2common(addrsize, name)
#define DEFINE_cfi_unwind_register_dw2uncommon(addrsize, name)                    __PRIVATE_DEFINE_cfi_unwind_register_dw2uncommon(addrsize, name)
#define DEFINE_cfi_unwind_register_common2dw(addrsize, name)                      __PRIVATE_DEFINE_cfi_unwind_register_common2dw(addrsize, name)
#define DEFINE_cfi_unwind_register_uncommon2dw(addrsize, name)                    __PRIVATE_DEFINE_cfi_unwind_register_uncommon2dw(addrsize, name)
#define DEFINE_cfi_unwind_sigframe_register_dw2common(addrsize, name)             __PRIVATE_DEFINE_cfi_unwind_sigframe_register_dw2common(addrsize, name)
#define DEFINE_cfi_unwind_sigframe_register_dw2uncommon(addrsize, name)           __PRIVATE_DEFINE_cfi_unwind_sigframe_register_dw2uncommon(addrsize, name)
#define DEFINE_cfi_unwind_sigframe_register_common2dw(addrsize, name)             __PRIVATE_DEFINE_cfi_unwind_sigframe_register_common2dw(addrsize, name)
#define DEFINE_cfi_unwind_sigframe_register_uncommon2dw(addrsize, name)           __PRIVATE_DEFINE_cfi_unwind_sigframe_register_uncommon2dw(addrsize, name)

#if 0 /* Not needed */
#if CFI_386_UNWIND_LANDING_COMMON_REGISTER_COUNT > CFI_UNWIND_LANDING_COMMON_REGISTER_MAXCOUNT
#undef CFI_UNWIND_LANDING_COMMON_REGISTER_MAXCOUNT
#define CFI_UNWIND_LANDING_COMMON_REGISTER_MAXCOUNT CFI_386_UNWIND_LANDING_COMMON_REGISTER_COUNT
#endif /* CFI_386_UNWIND_LANDING_COMMON_REGISTER_COUNT > CFI_UNWIND_LANDING_COMMON_REGISTER_MAXCOUNT */
#if CFI_386_UNWIND_LANDING_UNCOMMON_REGISTER_COUNT > CFI_UNWIND_LANDING_UNCOMMON_REGISTER_MAXCOUNT
#undef CFI_UNWIND_LANDING_UNCOMMON_REGISTER_MAXCOUNT
#define CFI_UNWIND_LANDING_UNCOMMON_REGISTER_MAXCOUNT CFI_386_UNWIND_LANDING_UNCOMMON_REGISTER_COUNT
#endif /* CFI_386_UNWIND_LANDING_UNCOMMON_REGISTER_COUNT > CFI_UNWIND_LANDING_UNCOMMON_REGISTER_MAXCOUNT */
#define CFI_UNWIND_LANDING_UNCOMMON_REGISTER_SP(addrsize)    (__likely((addrsize) >= 8) ? CFI_X86_64_UNWIND_LANDING_UNCOMMON_REGISTER_SP : CFI_386_UNWIND_LANDING_UNCOMMON_REGISTER_SP)
#define CFI_UNWIND_LANDING_COMMON_REGISTER_COUNT(addrsize)   (__likely((addrsize) >= 8) ? CFI_X86_64_UNWIND_LANDING_COMMON_REGISTER_COUNT : CFI_386_UNWIND_LANDING_COMMON_REGISTER_COUNT)
#define CFI_UNWIND_LANDING_UNCOMMON_REGISTER_COUNT(addrsize) (__likely((addrsize) >= 8) ? CFI_X86_64_UNWIND_LANDING_UNCOMMON_REGISTER_COUNT : CFI_386_UNWIND_LANDING_UNCOMMON_REGISTER_COUNT)

#undef DEFINE_cfi_unwind_landing_register_dw2common
#undef DEFINE_cfi_unwind_landing_register_dw2uncommon
#undef DEFINE_cfi_unwind_landing_register_common2dw
#undef DEFINE_cfi_unwind_landing_register_uncommon2dw
#define __PRIVATE_DEFINE_cfi_unwind_landing_register_dw2common_4                 DEFINE_cfi_386_unwind_landing_register_dw2common
#define __PRIVATE_DEFINE_cfi_unwind_landing_register_dw2common_8                 DEFINE_cfi_x86_64_unwind_landing_register_dw2common
#define __PRIVATE_DEFINE_cfi_unwind_landing_register_dw2uncommon_4               DEFINE_cfi_386_unwind_landing_register_dw2uncommon
#define __PRIVATE_DEFINE_cfi_unwind_landing_register_dw2uncommon_8               DEFINE_cfi_x86_64_unwind_landing_register_dw2uncommon
#define __PRIVATE_DEFINE_cfi_unwind_landing_register_common2dw_4                 DEFINE_cfi_386_unwind_landing_register_common2dw
#define __PRIVATE_DEFINE_cfi_unwind_landing_register_common2dw_8                 DEFINE_cfi_x86_64_unwind_landing_register_common2dw
#define __PRIVATE_DEFINE_cfi_unwind_landing_register_uncommon2dw_4               DEFINE_cfi_386_unwind_landing_register_uncommon2dw
#define __PRIVATE_DEFINE_cfi_unwind_landing_register_uncommon2dw_8               DEFINE_cfi_x86_64_unwind_landing_register_uncommon2dw
#define __PRIVATE_DEFINE_cfi_unwind_landing_register_dw2common(addrsize, name)   __PRIVATE_DEFINE_cfi_unwind_landing_register_dw2common_##addrsize(name)
#define __PRIVATE_DEFINE_cfi_unwind_landing_register_dw2uncommon(addrsize, name) __PRIVATE_DEFINE_cfi_unwind_landing_register_dw2uncommon_##addrsize(name)
#define __PRIVATE_DEFINE_cfi_unwind_landing_register_common2dw(addrsize, name)   __PRIVATE_DEFINE_cfi_unwind_landing_register_common2dw_##addrsize(name)
#define __PRIVATE_DEFINE_cfi_unwind_landing_register_uncommon2dw(addrsize, name) __PRIVATE_DEFINE_cfi_unwind_landing_register_uncommon2dw_##addrsize(name)
#define DEFINE_cfi_unwind_landing_register_dw2common(addrsize, name)             __PRIVATE_DEFINE_cfi_unwind_landing_register_dw2common(addrsize, name)
#define DEFINE_cfi_unwind_landing_register_dw2uncommon(addrsize, name)           __PRIVATE_DEFINE_cfi_unwind_landing_register_dw2uncommon(addrsize, name)
#define DEFINE_cfi_unwind_landing_register_common2dw(addrsize, name)             __PRIVATE_DEFINE_cfi_unwind_landing_register_common2dw(addrsize, name)
#define DEFINE_cfi_unwind_landing_register_uncommon2dw(addrsize, name)           __PRIVATE_DEFINE_cfi_unwind_landing_register_uncommon2dw(addrsize, name)
#endif /* ... */

#endif /* LIBUNWIND_HAVE_GETSETREG_COMPAT */
#endif /* __x86_64__ */


#endif /* !_LIBUNWIND_CFI_X86_64_H */
