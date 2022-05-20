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
#ifndef _LIBEMU86_EMU86_H
#define _LIBEMU86_EMU86_H 1

#include "api.h"

#include <bits/types.h>

/* Helpers for decoding/disassembling/emulation of x86 instructions. */

__DECL_BEGIN

/* Register indices */
#define EMU86_R_AL      0 /* Accumulator. (lower byte) */
#define EMU86_R_CL      1 /* Counter register. (lower byte) */
#define EMU86_R_DL      2 /* General purpose d-register. (lower byte) */
#define EMU86_R_BL      3 /* General purpose b-register. (lower byte) */
#define EMU86_R_AH      4 /* Accumulator. (upper byte; used when _NO_ REX prefix is given) */
#define EMU86_R_CH      5 /* Counter register. (upper byte; used when _NO_ REX prefix is given) */
#define EMU86_R_DH      6 /* General purpose d-register. (upper byte; used when _NO_ REX prefix is given) */
#define EMU86_R_BH      7 /* General purpose b-register. (upper byte; used when _NO_ REX prefix is given) */
#if CONFIG_LIBEMU86_WANT_64BIT
#define EMU86_R_SPL     4 /* Stack pointer. (lower byte; used when _ANY_ REX prefix is given) */
#define EMU86_R_BPL     5 /* Stack base pointer. (lower byte; used when _ANY_ REX prefix is given) */
#define EMU86_R_SIL     6 /* Source pointer. (lower byte; used when _ANY_ REX prefix is given) */
#define EMU86_R_DIL     7 /* Destination pointer. (lower byte; used when _ANY_ REX prefix is given) */
#define EMU86_R_R8L     8 /* %r8l */
#define EMU86_R_R9L     9 /* %r9l */
#define EMU86_R_R10L   10 /* %r10l */
#define EMU86_R_R11L   11 /* %r11l */
#define EMU86_R_R12L   12 /* %r12l */
#define EMU86_R_R13L   13 /* %r13l */
#define EMU86_R_R14L   14 /* %r14l */
#define EMU86_R_R15L   15 /* %r15l */
#endif /* CONFIG_LIBEMU86_WANT_64BIT */

#define EMU86_R_AX      0 /* Accumulator. */
#define EMU86_R_CX      1 /* Counter register. */
#define EMU86_R_DX      2 /* General purpose d-register. */
#define EMU86_R_BX      3 /* General purpose b-register. */
#define EMU86_R_SP      4 /* Stack pointer. */
#define EMU86_R_BP      5 /* Stack base pointer. */
#define EMU86_R_SI      6 /* Source pointer. */
#define EMU86_R_DI      7 /* Destination pointer. */
#if CONFIG_LIBEMU86_WANT_64BIT
#define EMU86_R_R8W     8 /* %r8w */
#define EMU86_R_R9W     9 /* %r9w */
#define EMU86_R_R10W   10 /* %r10w */
#define EMU86_R_R11W   11 /* %r11w */
#define EMU86_R_R12W   12 /* %r12w */
#define EMU86_R_R13W   13 /* %r13w */
#define EMU86_R_R14W   14 /* %r14w */
#define EMU86_R_R15W   15 /* %r15w */
#endif /* CONFIG_LIBEMU86_WANT_64BIT */

#define EMU86_R_EAX     0 /* Accumulator. */
#define EMU86_R_ECX     1 /* Counter register. */
#define EMU86_R_EDX     2 /* General purpose d-register. */
#define EMU86_R_EBX     3 /* General purpose b-register. */
#define EMU86_R_ESP     4 /* Stack pointer. */
#define EMU86_R_EBP     5 /* Stack base pointer. */
#define EMU86_R_ESI     6 /* Source pointer. */
#define EMU86_R_EDI     7 /* Destination pointer. */
#if CONFIG_LIBEMU86_WANT_64BIT
#define EMU86_R_R8D     8 /* %r8d */
#define EMU86_R_R9D     9 /* %r9d */
#define EMU86_R_R10D   10 /* %r10d */
#define EMU86_R_R11D   11 /* %r11d */
#define EMU86_R_R12D   12 /* %r12d */
#define EMU86_R_R13D   13 /* %r13d */
#define EMU86_R_R14D   14 /* %r14d */
#define EMU86_R_R15D   15 /* %r15d */
#endif /* CONFIG_LIBEMU86_WANT_64BIT */

#if CONFIG_LIBEMU86_WANT_64BIT
#define EMU86_R_RAX     0 /* Accumulator. */
#define EMU86_R_RCX     1 /* Counter register. */
#define EMU86_R_RDX     2 /* General purpose d-register. */
#define EMU86_R_RBX     3 /* General purpose b-register. */
#define EMU86_R_RSP     4 /* Stack pointer. */
#define EMU86_R_RBP     5 /* Stack base pointer. */
#define EMU86_R_RSI     6 /* Source pointer. */
#define EMU86_R_RDI     7 /* Destination pointer. */
#define EMU86_R_R8      8 /* %r8 */
#define EMU86_R_R9      9 /* %r9 */
#define EMU86_R_R10    10 /* %r10 */
#define EMU86_R_R11    11 /* %r11 */
#define EMU86_R_R12    12 /* %r12 */
#define EMU86_R_R13    13 /* %r13 */
#define EMU86_R_R14    14 /* %r14 */
#define EMU86_R_R15    15 /* %r15 */
#define EMU86_R_RIP    16 /* %rip (special value that may appear in `mi_rm') */
#endif /* CONFIG_LIBEMU86_WANT_64BIT */

#define EMU86_R_ES 0 /* %es */
#define EMU86_R_CS 1 /* %cs */
#define EMU86_R_SS 2 /* %ss */
#define EMU86_R_DS 3 /* %ds */
#define EMU86_R_FS 4 /* %fs */
#define EMU86_R_GS 5 /* %gs */



/* Layout of an EVEX prefix (64-bit only) */
#if CONFIG_LIBEMU86_WANT_64BIT
#define EMU86_EVEX_IDENT_M  0x0c0400 /* Mask of constant bits */
#define EMU86_EVEX_IDENT_V  0x000400 /* Value of constant bits */
#define EMU86_EVEX_aaa_M    0x000007 /* MASK:  EVEX.aaa */
#define EMU86_EVEX_aaa_S           0 /* SHIFT: EVEX.aaa */
#define EMU86_EVEX_Vi       0x000008 /* FLAG:  EVEX.V' */
#define EMU86_EVEX_b        0x000010 /* FLAG:  EVEX.b */
#define EMU86_EVEX_L        0x000020 /* FLAG:  VEX.L */
#define EMU86_EVEX_Li       0x000040 /* FLAG:  EVEX.L' */
#define EMU86_EVEX_z        0x000080 /* FLAG:  EVEX.z */
#define EMU86_EVEX_PP_M     0x000300 /* MASK:  VEX.PP */
#define EMU86_EVEX_PP_S            8 /* SHIFT: VEX.PP */
#define EMU86_EVEX_VVVV_M   0x007800 /* MASK:  VEX.VVVV */
#define EMU86_EVEX_VVVV_S         11 /* SHIFT: VEX.VVVV */
#define EMU86_EVEX_W        0x008000 /* FLAG:  VEX.W */
#define EMU86_EVEX_MM_M     0x030000 /* MASK:  EVEX.M_MM (same as VEX.M_MMMM) */
#define EMU86_EVEX_MM_S           16 /* SHIFT: EVEX.M_MM */
#define EMU86_EVEX_Ri       0x100000 /* FLAG:  EVEX.R' */
#define EMU86_EVEX_B        0x200000 /* FLAG:  VEX.B */
#define EMU86_EVEX_X        0x400000 /* FLAG:  VEX.X */
#define EMU86_EVEX_R        0x800000 /* FLAG:  VEX.R */
#endif /* CONFIG_LIBEMU86_WANT_64BIT */

/* Layout of a 3-byte VEX prefix */
#define EMU86_VEX3B_PP_M    0x0003 /* MASK:  3-byte VEX.PP */
#define EMU86_VEX3B_PP_S         0 /* SHIFT: 3-byte VEX.PP */
#define EMU86_VEX3B_L       0x0004 /* FLAG:  3-byte VEX.L */
#define EMU86_VEX3B_VVVV_M  0x0078 /* MASK:  3-byte VEX.VVVV */
#define EMU86_VEX3B_VVVV_S       3 /* SHIFT: 3-byte VEX.VVVV */
#define EMU86_VEX3B_W       0x0080 /* FLAG:  3-byte VEX.W */
#define EMU86_VEX3B_MMMMM_M 0x1f00 /* MASK:  3-byte VEX.MMMMM */
#define EMU86_VEX3B_MMMMM_S      8 /* SHIFT: 3-byte VEX.MMMMM */
#define EMU86_VEX3B_B       0x2000 /* FLAG:  3-byte VEX.B */
#define EMU86_VEX3B_X       0x4000 /* FLAG:  3-byte VEX.X */
#define EMU86_VEX3B_R       0x8000 /* FLAG:  3-byte VEX.R */

/* Layout of a 2-byte VEX prefix */
#define EMU86_VEX2B_PP_M   0x03 /* MASK:  2-byte VEX.PP */
#define EMU86_VEX2B_PP_S      0 /* SHIFT: 2-byte VEX.PP */
#define EMU86_VEX2B_L      0x04 /* FLAG:  2-byte VEX.L */
#define EMU86_VEX2B_VVVV_M 0x78 /* MASK:  2-byte VEX.VVVV */
#define EMU86_VEX2B_1      0x40 /* FLAG:  Must be one (if 0, not a prefix + generate opcode `0xc5') */
#define EMU86_VEX2B_VVVV_S    3 /* SHIFT: 2-byte VEX.VVVV */
#define EMU86_VEX2B_R      0x80 /* FLAG:  2-byte VEX.R */



/* Opcode flags. */
/*      EMU86_F_BITMASK     0x00000003  * Mask for the architecture bit count. */
#define EMU86_F_OP16        0x00000004 /* The 0x66 prefix is being used. */
#define EMU86_F_AD16        0x00000008 /* The 0x67 prefix is being used. */
#define EMU86_F_LOCK        0x00000010 /* The `lock' (0xf0) prefix is being used. */
#define EMU86_F_REPNE       0x00000020 /* The `repne' (0xf2) prefix is being used. */
#define EMU86_F_REP         0x00000040 /* The `rep' (0xf3) prefix is being used. */
#if CONFIG_LIBEMU86_WANT_64BIT
#define EMU86_F_AD64        EMU86_F_AD16 /* The 0x67 prefix is being used. (alias for `EMU86_F_AD16') */
#define EMU86_F_HASREX      0x00000080 /* A REX prefix is being used. */
#define EMU86_F_REX_B       0x00000100 /* The REX.B flag (1-bit extension to MODRM.rm). */
#define EMU86_F_REX_X       0x00000200 /* The REX.X flag (1-bit extension to SIB.index). */
#define EMU86_F_REX_R       0x00000400 /* The REX.R flag (1-bit extension to MODRM.reg). */
#define EMU86_F_REX_W       0x00000800 /* The REX.W flag (Indicates 64-bit operands). */
#define EMU86_F_REXMASK     0x00000f00 /* Mask of the REX prefix byte. */
#define EMU86_F_REXSHFT              8 /* Shift for the REX prefix byte. */
#endif /* CONFIG_LIBEMU86_WANT_64BIT */
#define EMU86_F_SEGMASK     0x00007000 /* Mask for segment overrides. */
#define EMU86_F_SEGSHIFT            12 /* Shift for segment overrides. */
#define EMU86_F_SEGREG(x)   ((((x) & EMU86_F_SEGMASK) >> EMU86_F_SEGSHIFT) - 1)
#define EMU86_F_HASSEG(x)   (((x) & EMU86_F_SEGMASK) != 0)
#if CONFIG_LIBEMU86_WANT_16BIT || CONFIG_LIBEMU86_WANT_32BIT
#define EMU86_F_SEGES       0x00001000 /* ES override. */
#define EMU86_F_SEGCS       0x00002000 /* CS override. */
#define EMU86_F_SEGSS       0x00003000 /* SS override. */
#define EMU86_F_SEGDS       0x00004000 /* DS override. */
#endif /* CONFIG_LIBEMU86_WANT_16BIT || CONFIG_LIBEMU86_WANT_32BIT */
#define EMU86_F_SEGFS       0x00005000 /* FS override. */
#define EMU86_F_SEGGS       0x00006000 /* GS override. */
/*      EMU86_F_SEG6        0x00007000  * ... */
#define EMU86_F_HASVEX      0x00008000 /* A VEX prefix was given. */
#if CONFIG_LIBEMU86_WANT_64BIT
#define EMU86_F_VEX_VVVVV_M 0x001f0000 /* Mask for EVEX.~Vi + VEX.~VVVV */
#else /* CONFIG_LIBEMU86_WANT_64BIT */
#define EMU86_F_VEX_VVVVV_M 0x000f0000 /* Mask for VEX.~VVVV */
/*      EMU86_F_            0x00100000  * ... */
#endif /* !CONFIG_LIBEMU86_WANT_64BIT */
#define EMU86_F_VEX_VVVVV_S         16 /* Shift for EVEX.~Vi + VEX.~VVVV */
#define EMU86_F_VEX_VVVVV(x) (((x) & EMU86_F_VEX_VVVVV_M) >> EMU86_F_VEX_VVVVV_S)
#define EMU86_F_VEX_W       0x00200000 /* Value of VEX.W */
#if CONFIG_LIBEMU86_WANT_64BIT
#define EMU86_F_VEX_LL_M    0x00c00000 /* Value of EVEX.Li + VEX.L */
#else /* CONFIG_LIBEMU86_WANT_64BIT */
#define EMU86_F_VEX_LL_M    0x00400000 /* Value of VEX.L */
/*      EMU86_F_            0x00800000  * ... */
#endif /* !CONFIG_LIBEMU86_WANT_64BIT */
#define EMU86_F_VEX_LL_S            22 /* Shift for EVEX.Li + VEX.L */
#define EMU86_F_VEX_LL(x)   (((x) & EMU86_F_VEX_LL_M) >> EMU86_F_VEX_LL_S)
#if CONFIG_LIBEMU86_WANT_64BIT
#define EMU86_F_EVEX_z      0x01000000 /* Value of EVEX.z */
#define EMU86_F_EVEX_b      0x02000000 /* Value of EVEX.b */
#define EMU86_F_EVEX_R      0x04000000 /* The EVEX.R flag (a second 1-bit extension to MODRM.reg; use with `EMU86_F_REX_R'). */
#define EMU86_F_EVEX_aaa_M  0x38000000 /* Value of EVEX.aaa */
#define EMU86_F_EVEX_aaa_S          27 /* Shift for EVEX.aaa */
#define EMU86_F_EVEX_aaa(x) (((x) & EMU86_F_EVEX_aaa_M) >> EMU86_F_EVEX_aaa_S)
#define EMU86_F_HASEVEX     0x40000000 /* An EVEX prefix was given. */
#endif /* CONFIG_LIBEMU86_WANT_64BIT */
/*      EMU86_F_            0x80000000  * ... */

/* Explicit prefix byte flags. */
#define EMU86_F_66 EMU86_F_OP16  /* The 0x66 prefix is being used. */
#define EMU86_F_67 EMU86_F_AD16  /* The 0x67 prefix is being used. */
#define EMU86_F_f0 EMU86_F_LOCK  /* The 0xf0 prefix is being used. */
#define EMU86_F_f2 EMU86_F_REPNE /* The 0xf2 prefix is being used. */
#define EMU86_F_f3 EMU86_F_REP   /* The 0xf3 prefix is being used. */

/* Normal (initial) flags before calling `emu86_opcode_decode()' */
#define EMU86_F_NORMAL 0


#ifdef CONFIG_LIBEMU86_NEED_ARCHMODE
#undef EMU86_F_16BIT
#undef EMU86_F_32BIT
#undef EMU86_F_64BIT
#if (CONFIG_LIBEMU86_WANT_16BIT && CONFIG_LIBEMU86_WANT_32BIT && CONFIG_LIBEMU86_WANT_64BIT)
#ifdef __x86_64__
#define EMU86_F_64BIT   0x00000000 /* 64-bit mode */
#define EMU86_F_32BIT   0x00000001 /* 32-bit mode */
#else /* __x86_64__ */
#define EMU86_F_32BIT   0x00000000 /* 32-bit mode */
#define EMU86_F_64BIT   0x00000001 /* 64-bit mode */
#endif /* !__x86_64__ */
#define EMU86_F_16BIT   0x00000002 /* 16-bit mode */
#define EMU86_F_BITMASK 0x00000003 /* Mask for code bit count. */
#define EMU86_F_IS16(x) (((x) & 3) >= 2)
#define EMU86_F_IS32(x) (((x) & 3) == EMU86_F_32BIT)
#define EMU86_F_IS64(x) (((x) & 3) == EMU86_F_64BIT)
#elif (CONFIG_LIBEMU86_WANT_32BIT && CONFIG_LIBEMU86_WANT_64BIT)
#ifdef __x86_64__
#define EMU86_F_64BIT   0x00000000 /* 64-bit mode */
#define EMU86_F_32BIT   0x00000001 /* 32-bit mode */
#else /* __x86_64__ */
#define EMU86_F_32BIT   0x00000000 /* 32-bit mode */
#define EMU86_F_64BIT   0x00000001 /* 64-bit mode */
#endif /* !__x86_64__ */
#elif (CONFIG_LIBEMU86_WANT_16BIT && CONFIG_LIBEMU86_WANT_32BIT)
#define EMU86_F_32BIT   0x00000000 /* 32-bit mode */
#define EMU86_F_16BIT   0x00000001 /* 16-bit mode */
#elif (CONFIG_LIBEMU86_WANT_16BIT && CONFIG_LIBEMU86_WANT_64BIT)
#define EMU86_F_64BIT   0x00000000 /* 64-bit mode */
#define EMU86_F_16BIT   0x00000001 /* 16-bit mode */
#else
#error "Bad configuration"
#endif
#ifndef EMU86_F_BITMASK
#define EMU86_F_BITMASK 0x00000001 /* Mask for code bit count. */
#ifdef EMU86_F_16BIT
#define EMU86_F_IS16(x) (((x) & 1) == EMU86_F_16BIT)
#else /* EMU86_F_16BIT */
#define EMU86_F_IS16(x) 0
#endif /* !EMU86_F_16BIT */
#ifdef EMU86_F_32BIT
#define EMU86_F_IS32(x) (((x) & 1) == EMU86_F_32BIT)
#else /* EMU86_F_32BIT */
#define EMU86_F_IS32(x) 0
#endif /* !EMU86_F_32BIT */
#ifdef EMU86_F_64BIT
#define EMU86_F_IS64(x) (((x) & 1) == EMU86_F_64BIT)
#else /* EMU86_F_64BIT */
#define EMU86_F_IS64(x) 0
#endif /* !EMU86_F_64BIT */
#endif /* !EMU86_F_BITMASK */
#else /* CONFIG_LIBEMU86_NEED_ARCHMODE */
#define EMU86_F_IS16(x) CONFIG_LIBEMU86_WANT_16BIT
#define EMU86_F_IS32(x) CONFIG_LIBEMU86_WANT_32BIT
#define EMU86_F_IS64(x) CONFIG_LIBEMU86_WANT_64BIT
#endif /* !CONFIG_LIBEMU86_NEED_ARCHMODE */



/* modr/m encoding. */
#define EMU86_MODRM_MOD_MASK  0xc0 /* 0b11000000 */
#define EMU86_MODRM_REG_MASK  0x38 /* 0b00111000 */
#define EMU86_MODRM_RM_MASK   0x07 /* 0b00000111 */
#define EMU86_MODRM_MOD_SHIFT 6
#define EMU86_MODRM_REG_SHIFT 3
#define EMU86_MODRM_RM_SHIFT  0
#define EMU86_MODRM_GETMOD(x) (((x) & EMU86_MODRM_MOD_MASK) >> EMU86_MODRM_MOD_SHIFT)
#define EMU86_MODRM_GETREG(x) (((x) & EMU86_MODRM_REG_MASK) >> EMU86_MODRM_REG_SHIFT)
#define EMU86_MODRM_GETRM(x)  (((x) & EMU86_MODRM_RM_MASK) >> EMU86_MODRM_RM_SHIFT)

/* Possible values for `struct emu86_modrm::mi_type' */
#define EMU86_MODRM_REGISTER 0
#define EMU86_MODRM_MEMORY   1
#define EMU86_MODRM_ISREG(x) ((x) == 0)
#define EMU86_MODRM_ISMEM(x) ((x) != 0)


#define EMU86_OPCODE_BASE0         0x0000
#define EMU86_OPCODE_BASE0f        0x0100
#define EMU86_OPCODE_BASE0f38      0x0200
#define EMU86_OPCODE_BASE0f3a      0x0300

/* May appear in exceptions (map is in range of [8,31])
 * NOTE: Tiny opcodes in this range are _NOT_ returned by  `emu86_opcode_decode()'!
 *       To handle XOP opcodes, you must handle the `0x8f' opcode instead, and have
 *       the case of modrm.mi_reg != 0 be used for processing XOP opcodes. */
#define EMU86_OPCODE_BASEXOP(map) (0xe000 | (((map)/* & 0x1f*/) << 8))
#define EMU86_OPCODE_ENCODE_XOP(map, opcode) (EMU86_OPCODE_BASEXOP(map) | (opcode))

/* Encode/Decode an x86 opcode `real_opcode' */
#define EMU86_OPCODE_ENCODE(real_opcode)                                             \
	((real_opcode) <= 0xff                                                           \
	 ? __CCAST(emu86_opcode_t)(EMU86_OPCODE_BASE0 + (real_opcode))                   \
	 : ((real_opcode) >= 0x0f00 && (real_opcode) <= 0x0fff)                          \
	   ? __CCAST(emu86_opcode_t)(EMU86_OPCODE_BASE0f + ((real_opcode)-0x0f00))       \
	   : ((real_opcode) >= 0x0f3800 && (real_opcode) <= 0x0f38ff)                    \
	     ? __CCAST(emu86_opcode_t)(EMU86_OPCODE_BASE0f38 + ((real_opcode)-0x0f3800)) \
	     : __CCAST(emu86_opcode_t)(EMU86_OPCODE_BASE0f3a + ((real_opcode)-0x0f3a00)))
#define EMU86_OPCODE_DECODE(tiny_opcode)                                       \
	((tiny_opcode) < EMU86_OPCODE_BASE0f                                       \
	 ? __CCAST(__uint32_t)(0x00 + (tiny_opcode)-EMU86_OPCODE_BASE0)            \
	 : (tiny_opcode) < EMU86_OPCODE_BASE0f38                                   \
	   ? __CCAST(__uint32_t)(0x0f00 + (tiny_opcode)-EMU86_OPCODE_BASE0f)       \
	   : (tiny_opcode) < EMU86_OPCODE_BASE0f3a                                 \
	     ? __CCAST(__uint32_t)(0x0f3800 + (tiny_opcode)-EMU86_OPCODE_BASE0f38) \
	     : __CCAST(__uint32_t)(0x0f3a00 + (tiny_opcode)-EMU86_OPCODE_BASE0f3a))



#ifdef __CC__

/* X86 opcode. (tiny form; use `EMU86_OPCODE_DECODE()' to decode) */
typedef __uint16_t emu86_opcode_t;

/* Instruction flags (set of `EMU86_F_*'). */
typedef __uint32_t emu86_opflags_t;

/* Decode an opcode from `pc', store it in `*popcode' and `*pflags',
 * before returning a pointer past the opcode's ID.
 * @return: * :   A pointer to the first byte past the opcode's ID
 * @param: popcode: Filled with the opcode's number
 * @param: pflags:  [in(EMU86_F_BITMASK)|out] Opcode flags.
 *                  NOTE: The caller  should  have  previously  initialized  flags
 *                        through use of `emu86_opflags_from_*()', or by explicity
 *                        setting `EMU86_F_BITMASK' */
typedef __ATTR_RETNONNULL_T __ATTR_NONNULL_T((1, 2, 3)) __byte_t *
__NOTHROW_NCX_T(LIBEMU86_CC *PEMU86_OPCODE_DECODE)(__byte_t const *__restrict pc,
                                                   emu86_opcode_t *__restrict popcode,
                                                   emu86_opflags_t *__restrict pflags);
#ifdef LIBEMU86_WANT_PROTOTYPES
LIBEMU86_DECL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2, 3)) __byte_t *
__NOTHROW_NCX(LIBEMU86_CC emu86_opcode_decode)(__byte_t const *__restrict pc,
                                               emu86_opcode_t *__restrict popcode,
                                               emu86_opflags_t *__restrict pflags);
#endif /* LIBEMU86_WANT_PROTOTYPES */




struct emu86_modrm {
	__int32_t mi_offset; /* Memory address. */
	/* EXAMPLES:
	 *  - mov $42, %mi_rm                                   # mi_type == EMU86_MODRM_REGISTER
	 *  - mov $42, mi_offset(%mi_rm)                        # mi_type == EMU86_MODRM_MEMORY
	 *  - mov %mi_reg, mi_offset(%mi_rm,%mi_index,mi_shift) # mi_type == EMU86_MODRM_MEMORY */
	__uint8_t mi_type;   /* mod R/M type (One of `EMU86_MODRM_*') */
	__uint8_t mi_reg;    /* Secondary register operand, or instruction sub-class. */
	__uint8_t mi_rm;     /* Base register (or 0xff when not set). */
	__uint8_t mi_index;  /* Index register (or 0xff when not set). */
	__uint8_t mi_shift;  /* Index shift (or 0). */
};


/* Decode a MODRM suffix from `pc' and return a pointer past the end of the suffix.
 * @param: result: Filled in with information regarding the MODRM value.
 * @param: flags:  Opcode flags. */
typedef __ATTR_RETNONNULL_T __ATTR_NONNULL_T((1, 2)) __byte_t *
__NOTHROW_NCX_T(LIBEMU86_CC *PEMU86_MODRM_DECODE)(__byte_t const *__restrict pc,
                                                  struct emu86_modrm *__restrict result,
                                                  emu86_opflags_t flags);
#ifdef LIBEMU86_WANT_PROTOTYPES
LIBEMU86_DECL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __byte_t *
__NOTHROW_NCX(LIBEMU86_CC emu86_modrm_decode)(__byte_t const *__restrict pc,
                                              struct emu86_modrm *__restrict result,
                                              emu86_opflags_t flags);
#endif /* LIBEMU86_WANT_PROTOTYPES */

#endif /* __CC__ */

__DECL_END

#include <hybrid/host.h>

#if defined(__x86_64__) || defined(__i386__)
#ifndef CONFIG_LIBEMU86_NEED_ARCHMODE
#define emu86_opflags_from_icpustate(state) EMU86_F_NORMAL
#define emu86_opflags_from_scpustate(state) EMU86_F_NORMAL
#define emu86_opflags_from_ucpustate(state) EMU86_F_NORMAL
#define emu86_opflags_from_fcpustate(state) EMU86_F_NORMAL
#else /* !CONFIG_LIBEMU86_NEED_ARCHMODE */
#include <kos/kernel/cpu-state.h>
#include <kos/kernel/cpu-state-helpers.h>
#if (CONFIG_LIBEMU86_WANT_16BIT && CONFIG_LIBEMU86_WANT_32BIT && CONFIG_LIBEMU86_WANT_64BIT)
#define emu86_opflags_from_icpustate(state) (icpustate_isvm86(state) ? EMU86_F_16BIT : icpustate_is32bit(state) ? EMU86_F_32BIT : EMU86_F_64BIT)
#define emu86_opflags_from_scpustate(state) (scpustate_isvm86(state) ? EMU86_F_16BIT : scpustate_is32bit(state) ? EMU86_F_32BIT : EMU86_F_64BIT)
#define emu86_opflags_from_ucpustate(state) (ucpustate_isvm86(state) ? EMU86_F_16BIT : ucpustate_is32bit(state) ? EMU86_F_32BIT : EMU86_F_64BIT)
#define emu86_opflags_from_fcpustate(state) (fcpustate_isvm86(state) ? EMU86_F_16BIT : fcpustate_is32bit(state) ? EMU86_F_32BIT : EMU86_F_64BIT)
#elif (CONFIG_LIBEMU86_WANT_32BIT && CONFIG_LIBEMU86_WANT_64BIT)
#define emu86_opflags_from_icpustate(state) (icpustate_is32bit(state) ? EMU86_F_32BIT : EMU86_F_64BIT)
#define emu86_opflags_from_scpustate(state) (scpustate_is32bit(state) ? EMU86_F_32BIT : EMU86_F_64BIT)
#define emu86_opflags_from_ucpustate(state) (ucpustate_is32bit(state) ? EMU86_F_32BIT : EMU86_F_64BIT)
#define emu86_opflags_from_fcpustate(state) (fcpustate_is32bit(state) ? EMU86_F_32BIT : EMU86_F_64BIT)
#elif (CONFIG_LIBEMU86_WANT_16BIT && CONFIG_LIBEMU86_WANT_32BIT)
#define emu86_opflags_from_icpustate(state) (icpustate_isvm86(state) ? EMU86_F_16BIT : EMU86_F_32BIT)
#define emu86_opflags_from_scpustate(state) (scpustate_isvm86(state) ? EMU86_F_16BIT : EMU86_F_32BIT)
#define emu86_opflags_from_ucpustate(state) (ucpustate_isvm86(state) ? EMU86_F_16BIT : EMU86_F_32BIT)
#define emu86_opflags_from_fcpustate(state) (fcpustate_isvm86(state) ? EMU86_F_16BIT : EMU86_F_32BIT)
#elif (CONFIG_LIBEMU86_WANT_16BIT && CONFIG_LIBEMU86_WANT_64BIT)
#define emu86_opflags_from_icpustate(state) (icpustate_isvm86(state) ? EMU86_F_16BIT : EMU86_F_64BIT)
#define emu86_opflags_from_scpustate(state) (scpustate_isvm86(state) ? EMU86_F_16BIT : EMU86_F_64BIT)
#define emu86_opflags_from_ucpustate(state) (ucpustate_isvm86(state) ? EMU86_F_16BIT : EMU86_F_64BIT)
#define emu86_opflags_from_fcpustate(state) (fcpustate_isvm86(state) ? EMU86_F_16BIT : EMU86_F_64BIT)
#else /* ... */
#error "Invalid configuration"
#endif /* !... */
#endif /* CONFIG_LIBEMU86_NEED_ARCHMODE */
#endif /* __x86_64__ || __i386__ */




#ifdef __LIBEMU86_STATIC
#ifndef __INTELLISENSE__
#include "emu86.c"
#endif /* !__INTELLISENSE__ */
#endif /* __LIBEMU86_STATIC */

#endif /* !_LIBEMU86_EMU86_H */
