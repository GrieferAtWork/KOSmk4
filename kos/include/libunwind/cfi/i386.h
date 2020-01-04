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
#ifndef _LIBUNWIND_CFI_I386_H
#define _LIBUNWIND_CFI_I386_H 1

#include "../api.h"
/**/

#include <hybrid/host.h>
#include <hybrid/typecore.h>

/* i386-specific CFI constants. */
#define CFI_386_UNWIND_REGISTER_SIZE      4
#define CFI_386_UNWIND_FPU_REGISTER_SIZE  16
#define CFI_386_UNWIND_IS_FPU_REGISTER(regno)  \
	((regno) >= CFI_386_UNWIND_REGISTER_ST0 && \
	 (regno) <= CFI_386_UNWIND_REGISTER_MM7)
#define CFI_386_REGISTER_SIZE(regno)       \
	(CFI_386_UNWIND_IS_FPU_REGISTER(regno) \
	 ? CFI_386_UNWIND_FPU_REGISTER_SIZE    \
	 : CFI_386_UNWIND_REGISTER_SIZE)
#define CFI_386_UNWIND_REGISTER_PC           CFI_386_UNWIND_REGISTER_EIP /* The register containing the program counter. */
#define CFI_386_UNWIND_REGISTER_SP           CFI_386_UNWIND_REGISTER_ESP /* The register for the CFA. */
#define CFI_386_UNWIND_REGISTER_EXCEPTION    CFI_386_UNWIND_REGISTER_EAX /* The register used to hold the current exception upon entry to an exception handler. */
#define CFI_386_UNWIND_REGISTER_EAX    0
#define CFI_386_UNWIND_REGISTER_ECX    1
#define CFI_386_UNWIND_REGISTER_EDX    2
#define CFI_386_UNWIND_REGISTER_EBX    3
#define CFI_386_UNWIND_REGISTER_ESP    4
#define CFI_386_UNWIND_REGISTER_EBP    5
#define CFI_386_UNWIND_REGISTER_ESI    6
#define CFI_386_UNWIND_REGISTER_EDI    7
#define CFI_386_UNWIND_REGISTER_EIP    8
#define CFI_386_UNWIND_REGISTER_EFLAGS 9
/*      CFI_386_UNWIND_REGISTER_       10 */
#define CFI_386_UNWIND_REGISTER_ST0    11
#define CFI_386_UNWIND_REGISTER_ST1    12
#define CFI_386_UNWIND_REGISTER_ST2    13
#define CFI_386_UNWIND_REGISTER_ST3    14
#define CFI_386_UNWIND_REGISTER_ST4    15
#define CFI_386_UNWIND_REGISTER_ST5    16
#define CFI_386_UNWIND_REGISTER_ST6    17
#define CFI_386_UNWIND_REGISTER_ST7    18
/*      CFI_386_UNWIND_REGISTER_       19 */
/*      CFI_386_UNWIND_REGISTER_       20 */
#define CFI_386_UNWIND_REGISTER_XMM0   21
#define CFI_386_UNWIND_REGISTER_XMM1   22
#define CFI_386_UNWIND_REGISTER_XMM2   23
#define CFI_386_UNWIND_REGISTER_XMM3   24
#define CFI_386_UNWIND_REGISTER_XMM4   25
#define CFI_386_UNWIND_REGISTER_XMM5   26
#define CFI_386_UNWIND_REGISTER_XMM6   27
#define CFI_386_UNWIND_REGISTER_XMM7   28
#define CFI_386_UNWIND_REGISTER_MM0    29
#define CFI_386_UNWIND_REGISTER_MM1    30
#define CFI_386_UNWIND_REGISTER_MM2    31
#define CFI_386_UNWIND_REGISTER_MM3    32
#define CFI_386_UNWIND_REGISTER_MM4    33
#define CFI_386_UNWIND_REGISTER_MM5    34
#define CFI_386_UNWIND_REGISTER_MM6    35
#define CFI_386_UNWIND_REGISTER_MM7    36
#define CFI_386_UNWIND_REGISTER_FCW    37
#define CFI_386_UNWIND_REGISTER_FSW    38
#define CFI_386_UNWIND_REGISTER_MXCSR  39
#define CFI_386_UNWIND_REGISTER_ES     40
#define CFI_386_UNWIND_REGISTER_CS     41
#define CFI_386_UNWIND_REGISTER_SS     42
#define CFI_386_UNWIND_REGISTER_DS     43
#define CFI_386_UNWIND_REGISTER_FS     44
#define CFI_386_UNWIND_REGISTER_GS     45
/*      CFI_386_UNWIND_REGISTER_       46 */
/*      CFI_386_UNWIND_REGISTER_       47 */
#define CFI_386_UNWIND_REGISTER_TR     48
#define CFI_386_UNWIND_REGISTER_LDTR   49
/*      CFI_386_UNWIND_REGISTER_       50 */
/*      CFI_386_UNWIND_REGISTER_       ... */
/*      CFI_386_UNWIND_REGISTER_       92 */
#define CFI_386_UNWIND_REGISTER_K0     93
#define CFI_386_UNWIND_REGISTER_K1     94
#define CFI_386_UNWIND_REGISTER_K2     95
#define CFI_386_UNWIND_REGISTER_K3     96
#define CFI_386_UNWIND_REGISTER_K4     97
#define CFI_386_UNWIND_REGISTER_K5     98
#define CFI_386_UNWIND_REGISTER_K6     99
#define CFI_386_UNWIND_REGISTER_K7     100
#define CFI_386_UNWIND_REGISTER_COUNT  101



/* Register <--> Common/Uncommon-register mapping
 * Basically: These are all of the callee-preserve registers, meaning
 *            that these are the only registers for which GCC will
 *            generate unwind instructions within normal assembly. */
#define CFI_386_UNWIND_COMMON_REGISTER_EBX   0
#define CFI_386_UNWIND_COMMON_REGISTER_EBP   1
#define CFI_386_UNWIND_COMMON_REGISTER_ESI   2
#define CFI_386_UNWIND_COMMON_REGISTER_EDI   3
#define CFI_386_UNWIND_COMMON_REGISTER_EIP   4
#define CFI_386_UNWIND_COMMON_REGISTER_COUNT 5

#define CFI_386_UNWIND_UNCOMMON_REGISTER_SP  CFI_386_UNWIND_UNCOMMON_REGISTER_ESP
#define CFI_386_UNWIND_UNCOMMON_REGISTER_EAX    0
#define CFI_386_UNWIND_UNCOMMON_REGISTER_ECX    1
#define CFI_386_UNWIND_UNCOMMON_REGISTER_EDX    2
#define CFI_386_UNWIND_UNCOMMON_REGISTER_ESP    3
#define CFI_386_UNWIND_UNCOMMON_REGISTER_EFLAGS 4
#define CFI_386_UNWIND_UNCOMMON_REGISTER_ST0    5
#define CFI_386_UNWIND_UNCOMMON_REGISTER_ST1    6
#define CFI_386_UNWIND_UNCOMMON_REGISTER_ST2    7
#define CFI_386_UNWIND_UNCOMMON_REGISTER_ST3    8
#define CFI_386_UNWIND_UNCOMMON_REGISTER_ST4    9
#define CFI_386_UNWIND_UNCOMMON_REGISTER_ST5    10
#define CFI_386_UNWIND_UNCOMMON_REGISTER_ST6    11
#define CFI_386_UNWIND_UNCOMMON_REGISTER_ST7    12
#define CFI_386_UNWIND_UNCOMMON_REGISTER_XMM0   13
#define CFI_386_UNWIND_UNCOMMON_REGISTER_XMM1   14
#define CFI_386_UNWIND_UNCOMMON_REGISTER_XMM2   15
#define CFI_386_UNWIND_UNCOMMON_REGISTER_XMM3   16
#define CFI_386_UNWIND_UNCOMMON_REGISTER_XMM4   17
#define CFI_386_UNWIND_UNCOMMON_REGISTER_XMM5   18
#define CFI_386_UNWIND_UNCOMMON_REGISTER_XMM6   19
#define CFI_386_UNWIND_UNCOMMON_REGISTER_XMM7   20
#define CFI_386_UNWIND_UNCOMMON_REGISTER_MM0    21
#define CFI_386_UNWIND_UNCOMMON_REGISTER_MM1    22
#define CFI_386_UNWIND_UNCOMMON_REGISTER_MM2    23
#define CFI_386_UNWIND_UNCOMMON_REGISTER_MM3    24
#define CFI_386_UNWIND_UNCOMMON_REGISTER_MM4    25
#define CFI_386_UNWIND_UNCOMMON_REGISTER_MM5    26
#define CFI_386_UNWIND_UNCOMMON_REGISTER_MM6    27
#define CFI_386_UNWIND_UNCOMMON_REGISTER_MM7    28
#define CFI_386_UNWIND_UNCOMMON_REGISTER_FCW    29
#define CFI_386_UNWIND_UNCOMMON_REGISTER_FSW    30
#define CFI_386_UNWIND_UNCOMMON_REGISTER_MXCSR  31
#define CFI_386_UNWIND_UNCOMMON_REGISTER_ES     32
#define CFI_386_UNWIND_UNCOMMON_REGISTER_CS     33
#define CFI_386_UNWIND_UNCOMMON_REGISTER_SS     34
#define CFI_386_UNWIND_UNCOMMON_REGISTER_DS     35
#define CFI_386_UNWIND_UNCOMMON_REGISTER_FS     36
#define CFI_386_UNWIND_UNCOMMON_REGISTER_GS     37
#define CFI_386_UNWIND_UNCOMMON_REGISTER_TR     38
#define CFI_386_UNWIND_UNCOMMON_REGISTER_LDTR   39
#define CFI_386_UNWIND_UNCOMMON_REGISTER_K0     40
#define CFI_386_UNWIND_UNCOMMON_REGISTER_K1     41
#define CFI_386_UNWIND_UNCOMMON_REGISTER_K2     42
#define CFI_386_UNWIND_UNCOMMON_REGISTER_K3     43
#define CFI_386_UNWIND_UNCOMMON_REGISTER_K4     44
#define CFI_386_UNWIND_UNCOMMON_REGISTER_K5     45
#define CFI_386_UNWIND_UNCOMMON_REGISTER_K6     46
#define CFI_386_UNWIND_UNCOMMON_REGISTER_K7     47
#define CFI_386_UNWIND_UNCOMMON_REGISTER_COUNT  48

#ifdef __CC__
/* @return: CFI_386_UNWIND_COMMON_REGISTER_COUNT: Not a common register */
__LOCAL __ATTR_CONST __UINTPTR_HALF_TYPE__ LIBUNWIND_CC
cfi_386_unwind_register_dw2common(__UINTPTR_HALF_TYPE__ __dw_regno) {
	__UINTPTR_HALF_TYPE__ __result;
	switch (__dw_regno) {

	case CFI_386_UNWIND_REGISTER_EBX:
		__result = CFI_386_UNWIND_COMMON_REGISTER_EBX;
		break;

	case CFI_386_UNWIND_REGISTER_EBP:
		__result = CFI_386_UNWIND_COMMON_REGISTER_EBP;
		break;

	case CFI_386_UNWIND_REGISTER_ESI:
		__result = CFI_386_UNWIND_COMMON_REGISTER_ESI;
		break;

	case CFI_386_UNWIND_REGISTER_EDI:
		__result = CFI_386_UNWIND_COMMON_REGISTER_EDI;
		break;

	case CFI_386_UNWIND_REGISTER_EIP:
		__result = CFI_386_UNWIND_COMMON_REGISTER_EIP;
		break;

	default:
		__result = CFI_386_UNWIND_COMMON_REGISTER_COUNT;
		break;
	}
	return __result;
}

/* @return: CFI_386_UNWIND_REGISTER_COUNT: Invalid register id */
__LOCAL __ATTR_CONST __UINTPTR_HALF_TYPE__ LIBUNWIND_CC
cfi_386_unwind_register_common2dw(__UINTPTR_HALF_TYPE__ __com_regno) {
	__UINTPTR_HALF_TYPE__ __result;
	switch (__com_regno) {

	case CFI_386_UNWIND_COMMON_REGISTER_EBX:
		__result = CFI_386_UNWIND_REGISTER_EBX;
		break;

	case CFI_386_UNWIND_COMMON_REGISTER_EBP:
		__result = CFI_386_UNWIND_REGISTER_EBP;
		break;

	case CFI_386_UNWIND_COMMON_REGISTER_ESI:
		__result = CFI_386_UNWIND_REGISTER_ESI;
		break;

	case CFI_386_UNWIND_COMMON_REGISTER_EDI:
		__result = CFI_386_UNWIND_REGISTER_EDI;
		break;

	case CFI_386_UNWIND_COMMON_REGISTER_EIP:
		__result = CFI_386_UNWIND_REGISTER_EIP;
		break;

	default:
		__result = CFI_386_UNWIND_REGISTER_COUNT;
		break;
	}
	return __result;
}

/* @return: CFI_386_UNWIND_UNCOMMON_REGISTER_COUNT: Not an uncommon register */
__LOCAL __ATTR_CONST __UINTPTR_HALF_TYPE__ LIBUNWIND_CC
cfi_386_unwind_register_dw2uncommon(__UINTPTR_HALF_TYPE__ __dw_regno) {
	__UINTPTR_HALF_TYPE__ __result;
	switch (__dw_regno) {

	case CFI_386_UNWIND_REGISTER_EAX:
		__result = CFI_386_UNWIND_UNCOMMON_REGISTER_EAX;
		break;

	case CFI_386_UNWIND_REGISTER_ECX:
		__result = CFI_386_UNWIND_UNCOMMON_REGISTER_ECX;
		break;

	case CFI_386_UNWIND_REGISTER_EDX:
		__result = CFI_386_UNWIND_UNCOMMON_REGISTER_EDX;
		break;

	case CFI_386_UNWIND_REGISTER_ESP:
		__result = CFI_386_UNWIND_UNCOMMON_REGISTER_ESP;
		break;

	case CFI_386_UNWIND_REGISTER_EFLAGS:
		__result = CFI_386_UNWIND_UNCOMMON_REGISTER_EFLAGS;
		break;

	default:
		if (__dw_regno >= CFI_386_UNWIND_REGISTER_ST0 &&
		    __dw_regno <= CFI_386_UNWIND_REGISTER_ST7)
			__result = CFI_386_UNWIND_UNCOMMON_REGISTER_ST0 + (__dw_regno - CFI_386_UNWIND_REGISTER_ST0);
		else if (__dw_regno >= CFI_386_UNWIND_REGISTER_XMM0 &&
		         __dw_regno <= CFI_386_UNWIND_REGISTER_GS)
			__result = CFI_386_UNWIND_UNCOMMON_REGISTER_XMM0 + (__dw_regno - CFI_386_UNWIND_REGISTER_XMM0);
		else if (__dw_regno >= CFI_386_UNWIND_REGISTER_TR &&
		         __dw_regno <= CFI_386_UNWIND_REGISTER_LDTR)
			__result = CFI_386_UNWIND_UNCOMMON_REGISTER_TR + (__dw_regno - CFI_386_UNWIND_REGISTER_TR);
		else if (__dw_regno >= CFI_386_UNWIND_REGISTER_K0 &&
		         __dw_regno <= CFI_386_UNWIND_REGISTER_K7)
			__result = CFI_386_UNWIND_UNCOMMON_REGISTER_K0 + (__dw_regno - CFI_386_UNWIND_REGISTER_K0);
		else {
			__result = CFI_386_UNWIND_UNCOMMON_REGISTER_COUNT;
		}
		break;
	}
	return __result;
}

/* @return: CFI_386_UNWIND_REGISTER_COUNT: Not an uncommon register */
__LOCAL __ATTR_CONST __UINTPTR_HALF_TYPE__ LIBUNWIND_CC
cfi_386_unwind_register_uncommon2dw(__UINTPTR_HALF_TYPE__ __uncom_regno) {
	__UINTPTR_HALF_TYPE__ __result;
	switch (__uncom_regno) {

	case CFI_386_UNWIND_UNCOMMON_REGISTER_EAX:
		__result = CFI_386_UNWIND_REGISTER_EAX;
		break;

	case CFI_386_UNWIND_UNCOMMON_REGISTER_ECX:
		__result = CFI_386_UNWIND_REGISTER_ECX;
		break;

	case CFI_386_UNWIND_UNCOMMON_REGISTER_EDX:
		__result = CFI_386_UNWIND_REGISTER_EDX;
		break;

	case CFI_386_UNWIND_UNCOMMON_REGISTER_ESP:
		__result = CFI_386_UNWIND_REGISTER_ESP;
		break;

	case CFI_386_UNWIND_UNCOMMON_REGISTER_EFLAGS:
		__result = CFI_386_UNWIND_REGISTER_EFLAGS;
		break;

	default:
		if __unlikely(__uncom_regno > CFI_386_UNWIND_REGISTER_K7)
			__result = CFI_386_UNWIND_REGISTER_COUNT;
		else if (__uncom_regno >= CFI_386_UNWIND_UNCOMMON_REGISTER_K0)
			__result = CFI_386_UNWIND_REGISTER_K0 + (__uncom_regno - CFI_386_UNWIND_UNCOMMON_REGISTER_K0);
		else if (__uncom_regno >= CFI_386_UNWIND_UNCOMMON_REGISTER_K0)
			__result = CFI_386_UNWIND_REGISTER_K0 + (__uncom_regno - CFI_386_UNWIND_UNCOMMON_REGISTER_K0);
		else if (__uncom_regno >= CFI_386_UNWIND_UNCOMMON_REGISTER_TR)
			__result = CFI_386_UNWIND_REGISTER_TR + (__uncom_regno - CFI_386_UNWIND_UNCOMMON_REGISTER_TR);
		else if (__uncom_regno >= CFI_386_UNWIND_UNCOMMON_REGISTER_XMM0)
			__result = CFI_386_UNWIND_REGISTER_XMM0 + (__uncom_regno - CFI_386_UNWIND_UNCOMMON_REGISTER_XMM0);
		else {
			__result = CFI_386_UNWIND_REGISTER_ST0 + (__uncom_regno - CFI_386_UNWIND_UNCOMMON_REGISTER_ST0);
		}
		break;
	}
	return __result;
}

#endif /* __CC__ */



/* The common/uncommon system is optimized for unwinding
 * regular C functions, since it only caches for registers
 * that have to be preserved when following the standard C
 * calling convention of the host.
 * However, at least within the kernel there is 1 additional
 * category of registers that _very_ often appear alongside
 * each other, mainly when unwinding a system call:
 * i386:
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
 * To optimize for stuff like this, provide an optional,
 * secondary unwinding system specifically for sigframe functions.
 *  - When unwinding an FDE with the SIGNAL_FRAME flag set, use a different
 *    set of COMMON registers (mainly: all GP-regs, + segments/eflags)
 *  - This can then also be implemented in user-space, to only require a
 *    single evaluation-pass over the FDE body to gather all registers that
 *    are likely to ever be used.
 *  - This entire sub-system is be implemented in parallel to the CFA_EXEC+CFA_APPLY
 *    functions and when building with __OPTIMIZE_SIZE__, we could simply implement
 *    these functions as aliases, since all they do is add another layer of optimization.
 */

/* Register <--> Sigframe Common/Uncommon-register mapping
 * Signal frames are normally used to unwind to an interrupted code
 * location. - For this purpose, they need to restore _all_ GP registers,
 * the FLAGS register, as well as all of the segment registers.
 * To speed up this process, define a special unwind register
 * namespace specifically for signal frame functions. */
#define CFI_386_UNWIND_SIGFRAME_COMMON_REGISTER_SP  CFI_386_UNWIND_SIGFRAME_COMMON_REGISTER_ESP
#define CFI_386_UNWIND_SIGFRAME_COMMON_REGISTER_EAX    0
#define CFI_386_UNWIND_SIGFRAME_COMMON_REGISTER_ECX    1
#define CFI_386_UNWIND_SIGFRAME_COMMON_REGISTER_EDX    2
#define CFI_386_UNWIND_SIGFRAME_COMMON_REGISTER_EBX    3
#define CFI_386_UNWIND_SIGFRAME_COMMON_REGISTER_ESP    4
#define CFI_386_UNWIND_SIGFRAME_COMMON_REGISTER_EBP    5
#define CFI_386_UNWIND_SIGFRAME_COMMON_REGISTER_ESI    6
#define CFI_386_UNWIND_SIGFRAME_COMMON_REGISTER_EDI    7
#define CFI_386_UNWIND_SIGFRAME_COMMON_REGISTER_EIP    8
#define CFI_386_UNWIND_SIGFRAME_COMMON_REGISTER_EFLAGS 9
#define CFI_386_UNWIND_SIGFRAME_COMMON_REGISTER_ES     10
#define CFI_386_UNWIND_SIGFRAME_COMMON_REGISTER_CS     11
#define CFI_386_UNWIND_SIGFRAME_COMMON_REGISTER_SS     12
#define CFI_386_UNWIND_SIGFRAME_COMMON_REGISTER_DS     13
#define CFI_386_UNWIND_SIGFRAME_COMMON_REGISTER_FS     14
#define CFI_386_UNWIND_SIGFRAME_COMMON_REGISTER_GS     15
#define CFI_386_UNWIND_SIGFRAME_COMMON_REGISTER_COUNT  16

#define CFI_386_UNWIND_SIGFRAME_UNCOMMON_REGISTER_ST0   0
#define CFI_386_UNWIND_SIGFRAME_UNCOMMON_REGISTER_ST1   1
#define CFI_386_UNWIND_SIGFRAME_UNCOMMON_REGISTER_ST2   2
#define CFI_386_UNWIND_SIGFRAME_UNCOMMON_REGISTER_ST3   3
#define CFI_386_UNWIND_SIGFRAME_UNCOMMON_REGISTER_ST4   4
#define CFI_386_UNWIND_SIGFRAME_UNCOMMON_REGISTER_ST5   5
#define CFI_386_UNWIND_SIGFRAME_UNCOMMON_REGISTER_ST6   6
#define CFI_386_UNWIND_SIGFRAME_UNCOMMON_REGISTER_ST7   7
#define CFI_386_UNWIND_SIGFRAME_UNCOMMON_REGISTER_XMM0  8
#define CFI_386_UNWIND_SIGFRAME_UNCOMMON_REGISTER_XMM1  9
#define CFI_386_UNWIND_SIGFRAME_UNCOMMON_REGISTER_XMM2  10
#define CFI_386_UNWIND_SIGFRAME_UNCOMMON_REGISTER_XMM3  11
#define CFI_386_UNWIND_SIGFRAME_UNCOMMON_REGISTER_XMM4  12
#define CFI_386_UNWIND_SIGFRAME_UNCOMMON_REGISTER_XMM5  13
#define CFI_386_UNWIND_SIGFRAME_UNCOMMON_REGISTER_XMM6  14
#define CFI_386_UNWIND_SIGFRAME_UNCOMMON_REGISTER_XMM7  15
#define CFI_386_UNWIND_SIGFRAME_UNCOMMON_REGISTER_MM0   16
#define CFI_386_UNWIND_SIGFRAME_UNCOMMON_REGISTER_MM1   17
#define CFI_386_UNWIND_SIGFRAME_UNCOMMON_REGISTER_MM2   18
#define CFI_386_UNWIND_SIGFRAME_UNCOMMON_REGISTER_MM3   19
#define CFI_386_UNWIND_SIGFRAME_UNCOMMON_REGISTER_MM4   20
#define CFI_386_UNWIND_SIGFRAME_UNCOMMON_REGISTER_MM5   21
#define CFI_386_UNWIND_SIGFRAME_UNCOMMON_REGISTER_MM6   22
#define CFI_386_UNWIND_SIGFRAME_UNCOMMON_REGISTER_MM7   23
#define CFI_386_UNWIND_SIGFRAME_UNCOMMON_REGISTER_FCW   24
#define CFI_386_UNWIND_SIGFRAME_UNCOMMON_REGISTER_FSW   25
#define CFI_386_UNWIND_SIGFRAME_UNCOMMON_REGISTER_MXCSR 26
#define CFI_386_UNWIND_SIGFRAME_UNCOMMON_REGISTER_TR    27
#define CFI_386_UNWIND_SIGFRAME_UNCOMMON_REGISTER_LDTR  28
#define CFI_386_UNWIND_SIGFRAME_UNCOMMON_REGISTER_K0    29
#define CFI_386_UNWIND_SIGFRAME_UNCOMMON_REGISTER_K1    30
#define CFI_386_UNWIND_SIGFRAME_UNCOMMON_REGISTER_K2    31
#define CFI_386_UNWIND_SIGFRAME_UNCOMMON_REGISTER_K3    32
#define CFI_386_UNWIND_SIGFRAME_UNCOMMON_REGISTER_K4    33
#define CFI_386_UNWIND_SIGFRAME_UNCOMMON_REGISTER_K5    34
#define CFI_386_UNWIND_SIGFRAME_UNCOMMON_REGISTER_K6    35
#define CFI_386_UNWIND_SIGFRAME_UNCOMMON_REGISTER_K7    36
#define CFI_386_UNWIND_SIGFRAME_UNCOMMON_REGISTER_COUNT 37

#ifdef __CC__
/* @return: CFI_386_UNWIND_SIGFRAME_COMMON_REGISTER_COUNT: Not a common register */
__LOCAL __ATTR_CONST __UINTPTR_HALF_TYPE__ LIBUNWIND_CC
cfi_386_unwind_sigframe_register_dw2common(__UINTPTR_HALF_TYPE__ __dw_regno) {
	__UINTPTR_HALF_TYPE__ __result;
#if CFI_386_UNWIND_REGISTER_EAX != 0
	if (__dw_regno >= CFI_386_UNWIND_REGISTER_EAX &&
	    __dw_regno <= CFI_386_UNWIND_REGISTER_EFLAGS)
#else /* CFI_386_UNWIND_REGISTER_EAX != 0 */
	if (__dw_regno <= CFI_386_UNWIND_REGISTER_EFLAGS)
#endif /* CFI_386_UNWIND_REGISTER_EAX == 0 */
	{
		__result = CFI_386_UNWIND_SIGFRAME_COMMON_REGISTER_EAX + (__dw_regno - CFI_386_UNWIND_REGISTER_EAX);
	} else if (__dw_regno >= CFI_386_UNWIND_REGISTER_ES &&
	           __dw_regno <= CFI_386_UNWIND_REGISTER_GS) {
		__result = CFI_386_UNWIND_SIGFRAME_COMMON_REGISTER_ES + (__dw_regno - CFI_386_UNWIND_REGISTER_ES);
	} else {
		__result = CFI_386_UNWIND_SIGFRAME_COMMON_REGISTER_COUNT;
	}
	return __result;
}

/* @return: CFI_386_UNWIND_REGISTER_COUNT: Invalid register id */
__LOCAL __ATTR_CONST __UINTPTR_HALF_TYPE__ LIBUNWIND_CC
cfi_386_unwind_sigframe_register_common2dw(__UINTPTR_HALF_TYPE__ __com_regno) {
	__UINTPTR_HALF_TYPE__ __result;
#if CFI_386_UNWIND_SIGFRAME_COMMON_REGISTER_EAX != 0
	if (__com_regno >= CFI_386_UNWIND_SIGFRAME_COMMON_REGISTER_EAX &&
	    __com_regno <= CFI_386_UNWIND_SIGFRAME_COMMON_REGISTER_EFLAGS)
#else /* CFI_386_UNWIND_SIGFRAME_COMMON_REGISTER_EAX != 0 */
	if (__com_regno <= CFI_386_UNWIND_SIGFRAME_COMMON_REGISTER_EFLAGS)
#endif /* CFI_386_UNWIND_SIGFRAME_COMMON_REGISTER_EAX == 0 */
	{
		__result = CFI_386_UNWIND_REGISTER_EAX + (__com_regno - CFI_386_UNWIND_SIGFRAME_COMMON_REGISTER_EAX);
	}
#if CFI_386_UNWIND_SIGFRAME_COMMON_REGISTER_ES != CFI_386_UNWIND_SIGFRAME_COMMON_REGISTER_EFLAGS + 1
	else if (__com_regno >= CFI_386_UNWIND_SIGFRAME_COMMON_REGISTER_ES &&
	         __com_regno <= CFI_386_UNWIND_SIGFRAME_COMMON_REGISTER_GS)
#else /* CFI_386_UNWIND_SIGFRAME_COMMON_REGISTER_ES != CFI_386_UNWIND_SIGFRAME_COMMON_REGISTER_EFLAGS + 1 */
	else if (__com_regno <= CFI_386_UNWIND_SIGFRAME_COMMON_REGISTER_GS)
#endif /* CFI_386_UNWIND_SIGFRAME_COMMON_REGISTER_ES == CFI_386_UNWIND_SIGFRAME_COMMON_REGISTER_EFLAGS + 1 */
	{
		__result = CFI_386_UNWIND_REGISTER_ES + (__com_regno - CFI_386_UNWIND_SIGFRAME_COMMON_REGISTER_ES);
	} else {
		__result = CFI_386_UNWIND_REGISTER_COUNT;
	}
	return __result;
}

/* @return: CFI_386_UNWIND_SIGFRAME_UNCOMMON_REGISTER_COUNT: Not an uncommon register */
__LOCAL __ATTR_CONST __UINTPTR_HALF_TYPE__ LIBUNWIND_CC
cfi_386_unwind_sigframe_register_dw2uncommon(__UINTPTR_HALF_TYPE__ __dw_regno) {
	__UINTPTR_HALF_TYPE__ __result;
	if (__dw_regno >= CFI_386_UNWIND_REGISTER_ST0 &&
	    __dw_regno <= CFI_386_UNWIND_REGISTER_ST7) {
		__result = CFI_386_UNWIND_SIGFRAME_UNCOMMON_REGISTER_ST0 + (__dw_regno - CFI_386_UNWIND_REGISTER_ST0);
	} else if (__dw_regno >= CFI_386_UNWIND_REGISTER_XMM0 &&
	           __dw_regno <= CFI_386_UNWIND_REGISTER_MXCSR) {
		__result = CFI_386_UNWIND_SIGFRAME_UNCOMMON_REGISTER_XMM0 + (__dw_regno - CFI_386_UNWIND_REGISTER_XMM0);
	} else if (__dw_regno >= CFI_386_UNWIND_REGISTER_TR &&
	           __dw_regno <= CFI_386_UNWIND_REGISTER_LDTR) {
		__result = CFI_386_UNWIND_SIGFRAME_UNCOMMON_REGISTER_TR + (__dw_regno - CFI_386_UNWIND_REGISTER_TR);
	} else if (__dw_regno >= CFI_386_UNWIND_REGISTER_K0 &&
	           __dw_regno <= CFI_386_UNWIND_REGISTER_K7) {
		__result = CFI_386_UNWIND_SIGFRAME_UNCOMMON_REGISTER_K0 + (__dw_regno - CFI_386_UNWIND_REGISTER_K0);
	} else {
		__result = CFI_386_UNWIND_SIGFRAME_UNCOMMON_REGISTER_COUNT;
	}
	return __result;
}

/* @return: CFI_386_UNWIND_REGISTER_COUNT: Not an uncommon register */
__LOCAL __ATTR_CONST __UINTPTR_HALF_TYPE__ LIBUNWIND_CC
cfi_386_unwind_sigframe_register_uncommon2dw(__UINTPTR_HALF_TYPE__ __uncom_regno) {
	__UINTPTR_HALF_TYPE__ __result;
#if CFI_386_UNWIND_SIGFRAME_UNCOMMON_REGISTER_ST0 != 0
	if (__uncom_regno >= CFI_386_UNWIND_SIGFRAME_UNCOMMON_REGISTER_ST0 &&
	    __uncom_regno <= CFI_386_UNWIND_SIGFRAME_UNCOMMON_REGISTER_ST7)
#else /* CFI_386_UNWIND_SIGFRAME_UNCOMMON_REGISTER_ST0 != 0 */
	if (__uncom_regno <= CFI_386_UNWIND_SIGFRAME_UNCOMMON_REGISTER_ST7)
#endif /* CFI_386_UNWIND_SIGFRAME_UNCOMMON_REGISTER_ST0 == 0 */
	{
		__result = CFI_386_UNWIND_REGISTER_ST0 + (__uncom_regno - CFI_386_UNWIND_SIGFRAME_UNCOMMON_REGISTER_ST0);
	}
#if CFI_386_UNWIND_SIGFRAME_UNCOMMON_REGISTER_XMM0 != CFI_386_UNWIND_SIGFRAME_UNCOMMON_REGISTER_ST7 + 1
	else if (__uncom_regno >= CFI_386_UNWIND_SIGFRAME_UNCOMMON_REGISTER_XMM0 &&
	         __uncom_regno <= CFI_386_UNWIND_SIGFRAME_UNCOMMON_REGISTER_MXCSR)
#else /* CFI_386_UNWIND_SIGFRAME_UNCOMMON_REGISTER_XMM0 != CFI_386_UNWIND_SIGFRAME_UNCOMMON_REGISTER_ST7 + 1 */
	else if (__uncom_regno <= CFI_386_UNWIND_SIGFRAME_UNCOMMON_REGISTER_MXCSR)
#endif /* CFI_386_UNWIND_SIGFRAME_UNCOMMON_REGISTER_XMM0 == CFI_386_UNWIND_SIGFRAME_UNCOMMON_REGISTER_ST7 + 1 */
	{
		__result = CFI_386_UNWIND_REGISTER_XMM0 + (__uncom_regno - CFI_386_UNWIND_SIGFRAME_UNCOMMON_REGISTER_XMM0);
	}
#if CFI_386_UNWIND_SIGFRAME_UNCOMMON_REGISTER_TR != CFI_386_UNWIND_SIGFRAME_UNCOMMON_REGISTER_MXCSR + 1
	else if (__uncom_regno >= CFI_386_UNWIND_SIGFRAME_UNCOMMON_REGISTER_TR &&
	         __uncom_regno <= CFI_386_UNWIND_SIGFRAME_UNCOMMON_REGISTER_LDTR)
#else /* CFI_386_UNWIND_SIGFRAME_UNCOMMON_REGISTER_TR != CFI_386_UNWIND_SIGFRAME_UNCOMMON_REGISTER_MXCSR + 1 */
	else if (__uncom_regno <= CFI_386_UNWIND_SIGFRAME_UNCOMMON_REGISTER_LDTR)
#endif /* CFI_386_UNWIND_SIGFRAME_UNCOMMON_REGISTER_TR == CFI_386_UNWIND_SIGFRAME_UNCOMMON_REGISTER_MXCSR + 1 */
	{
		__result = CFI_386_UNWIND_REGISTER_TR + (__uncom_regno - CFI_386_UNWIND_SIGFRAME_UNCOMMON_REGISTER_TR);
	}
#if CFI_386_UNWIND_SIGFRAME_UNCOMMON_REGISTER_K0 != CFI_386_UNWIND_SIGFRAME_UNCOMMON_REGISTER_LDTR + 1
	else if (__uncom_regno >= CFI_386_UNWIND_SIGFRAME_UNCOMMON_REGISTER_K0 &&
	         __uncom_regno <= CFI_386_UNWIND_SIGFRAME_UNCOMMON_REGISTER_K7)
#else /* CFI_386_UNWIND_SIGFRAME_UNCOMMON_REGISTER_K0 != CFI_386_UNWIND_SIGFRAME_UNCOMMON_REGISTER_LDTR + 1 */
	else if (__uncom_regno <= CFI_386_UNWIND_SIGFRAME_UNCOMMON_REGISTER_K7)
#endif /* CFI_386_UNWIND_SIGFRAME_UNCOMMON_REGISTER_K0 == CFI_386_UNWIND_SIGFRAME_UNCOMMON_REGISTER_LDTR + 1 */
	{
		__result = CFI_386_UNWIND_REGISTER_K0 + (__uncom_regno - CFI_386_UNWIND_SIGFRAME_UNCOMMON_REGISTER_K0);
	} else {
		__result = CFI_386_UNWIND_REGISTER_COUNT;
	}
	return __result;
}

#endif /* __CC__ */





/* Host-specific CFI constants. */
#if defined(__i386__) && !defined(__x86_64__)
#define CFI_UNWIND_REGISTER_MAXSIZE        CFI_386_UNWIND_FPU_REGISTER_SIZE
#define CFI_REGISTER_SIZE(regno)           CFI_386_REGISTER_SIZE(regno)
#define CFI_UNWIND_REGISTER_PC             CFI_386_UNWIND_REGISTER_PC        /* The register containing the program counter. */
#define CFI_UNWIND_REGISTER_SP             CFI_386_UNWIND_REGISTER_SP        /* The register for the CFA. */
#define CFI_UNWIND_REGISTER_EXCEPTION      CFI_386_UNWIND_REGISTER_EXCEPTION /* The register used to hold the current exception upon entry to an exception handler. */
#define CFI_UNWIND_REGISTER_COUNT          CFI_386_UNWIND_REGISTER_COUNT

/* Normal common/uncommon */
#define CFI_UNWIND_UNCOMMON_REGISTER_SP    CFI_386_UNWIND_UNCOMMON_REGISTER_SP
#define CFI_UNWIND_COMMON_REGISTER_COUNT   CFI_386_UNWIND_COMMON_REGISTER_COUNT
#define CFI_UNWIND_UNCOMMON_REGISTER_COUNT CFI_386_UNWIND_UNCOMMON_REGISTER_COUNT
#define cfi_unwind_register_dw2common      cfi_386_unwind_register_dw2common
#define cfi_unwind_register_dw2uncommon    cfi_386_unwind_register_dw2uncommon
#define cfi_unwind_register_common2dw      cfi_386_unwind_register_common2dw
#define cfi_unwind_register_uncommon2dw    cfi_386_unwind_register_uncommon2dw

/* Sigframe common/uncommon */
#define CFI_UNWIND_SIGFRAME_COMMON_REGISTER_SP      CFI_386_UNWIND_SIGFRAME_COMMON_REGISTER_SP
#define CFI_UNWIND_SIGFRAME_COMMON_REGISTER_COUNT   CFI_386_UNWIND_SIGFRAME_COMMON_REGISTER_COUNT
#define CFI_UNWIND_SIGFRAME_UNCOMMON_REGISTER_COUNT CFI_386_UNWIND_SIGFRAME_UNCOMMON_REGISTER_COUNT
#define cfi_unwind_sigframe_register_dw2common      cfi_386_unwind_sigframe_register_dw2common
#define cfi_unwind_sigframe_register_dw2uncommon    cfi_386_unwind_sigframe_register_dw2uncommon
#define cfi_unwind_sigframe_register_common2dw      cfi_386_unwind_sigframe_register_common2dw
#define cfi_unwind_sigframe_register_uncommon2dw    cfi_386_unwind_sigframe_register_uncommon2dw
#endif /* __i386__ && !__x86_64__ */


#endif /* !_LIBUNWIND_CFI_I386_H */
