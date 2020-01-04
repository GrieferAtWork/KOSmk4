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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_FAULT_DECODE_H
#define GUARD_KERNEL_CORE_ARCH_I386_FAULT_DECODE_H 1

#include <kernel/compiler.h>

#include <kernel/types.h>

DECL_BEGIN

#define R_EAX     0 /* Accumulator. */
#define R_ECX     1 /* Counter register. */
#define R_EDX     2 /* General purpose d-register. */
#define R_EBX     3 /* General purpose b-register. */
#define R_ESP     4 /* Stack pointer. */
#define R_EBP     5 /* Stack base pointer. */
#define R_ESI     6 /* Source pointer. */
#define R_EDI     7 /* Destination pointer. */
#ifdef __x86_64__
#define R_R8      8 /* R8 */
#define R_R9      9 /* R9 */
#define R_R10    10 /* R10 */
#define R_R11    11 /* R11 */
#define R_R12    12 /* R12 */
#define R_R13    13 /* R13 */
#define R_R14    14 /* R14 */
#define R_R15    15 /* R15 */
#define R_FREX 0x10 /* FLAG: A REX prefix is being used (only affects `x86_reg8_offsets'). */
#endif /* __x86_64__ */


/* Instruction flags. */
typedef u32 op_flag_t;
#define F_OP16       0x00000001 /* The 0x66 prefix is being used. */
#define F_AD16       0x00000002 /* The 0x67 prefix is being used. */
#define F_LOCK       0x00000004 /* The `lock' (0xf0) prefix is being used. */
#define F_REPNE      0x00000010 /* The `repne' (0xf2) prefix is being used. */
#define F_REP        0x00000020 /* The `rep' (0xf3) prefix is being used. */
#define F_HASVEX     0x00000040 /* A VEX prefix was given. */
#define F_SEGMASK    0x0000f000 /* Mask for segment overrides. */
#ifdef __x86_64__
#define F_VEX_VVVV_M 0x000f0000 /* Mask for VEX.VVVV */
#else
#define F_VEX_VVVV_M 0x00070000 /* Mask for VEX.VVVV */
#endif
#define F_VEX_VVVV_S         16 /* Shift for VEX.VVVV */
#define F_VEX_W      0x00100000 /* Value of VEX.W */
#define F_VEX_L      0x00200000 /* Value of VEX.L */
#ifdef __x86_64__
#define F_AD64       F_AD16     /* The 0x67 prefix is being used. */
#define F_IS_X32     0x00000008 /* The hosted process is running in compatibility mode (32-bit). */
#define F_HASREX     0x00000080 /* A REX prefix is being used. */
#define F_REXSHFT             8 /* Shift for the REX prefix byte. */
#define F_REXMASK    0x00000f00 /* Mask of the REX prefix byte. */
#define F_REX_W      0x00000800 /* The REX.W flag (Indicates 64-bit operands). */
#define F_REX_R      0x00000400 /* The REX.R flag (1-bit extension to MODRM.reg). */
#define F_REX_X      0x00000200 /* The REX.X flag (1-bit extension to SIB.index). */
#define F_REX_B      0x00000100 /* The REX.B flag (1-bit extension to MODRM.rm). */
#define F_SEGDS      0x00000000 /* DS override (compatibility mode ONLY). */
#define F_SEGES      0x00001000 /* ES override (compatibility mode ONLY). */
#define F_SEGCS      0x00002000 /* CS override (compatibility mode ONLY). */
#define F_SEGSS      0x00003000 /* SS override (compatibility mode ONLY). */
#else /* __x86_64__ */
#define F_SEGDS      0x00000000 /* DS override. */
#define F_SEGES      0x00001000 /* ES override. */
#define F_SEGCS      0x00002000 /* CS override. */
#define F_SEGSS      0x00003000 /* SS override. */
#endif /* !__x86_64__ */
#define F_SEGFS      0x00004000 /* FS override. */
#define F_SEGGS      0x00005000 /* GS override. */

/* Explicit prefix byte flags. */
#define F_66        F_OP16  /* The 0x66 prefix is being used. */
#define F_67        F_AD16  /* The 0x67 prefix is being used. */
#define F_f0        F_LOCK  /* The 0xf0 prefix is being used. */
#define F_f2        F_REPNE /* The 0xf2 prefix is being used. */
#define F_f3        F_REP   /* The 0xf3 prefix is being used. */



#define MODRM_MOD_MASK  0xc0 /* 0b11000000 */
#define MODRM_REG_MASK  0x38 /* 0b00111000 */
#define MODRM_RM_MASK   0x07 /* 0b00000111 */
#define MODRM_MOD_SHIFT 6
#define MODRM_REG_SHIFT 3
#define MODRM_RM_SHIFT  0
#define MODRM_GETMOD(x) (((x) & MODRM_MOD_MASK) >> MODRM_MOD_SHIFT)
#define MODRM_GETREG(x) (((x) & MODRM_REG_MASK) >> MODRM_REG_SHIFT)
#define MODRM_GETRM(x)  (((x) & MODRM_RM_MASK) >> MODRM_RM_SHIFT)

struct modrm {
	u32       mi_offset; /* Memory address. */
#define MODRM_REGISTER 0
#define MODRM_MEMORY   1
	/* EXAMPLES:
	 *  - mov $42, %mi_rm
	 *  - mov $42, mi_offset(%mi_rm)
	 *  - mov %mi_reg, mi_offset(%mi_rm,%mi_index,mi_shift)
	 */
	u8        mi_type;   /* mod R/M type (One of `MODRM_*') */
	u8        mi_reg;    /* Secondary register operand, or instruction sub-class. */
	u8        mi_rm;     /* Base register (or 0xff when not set). */
	u8        mi_index;  /* Index register (or 0xff when not set). */
	u8        mi_shift;  /* Index shift (or 0). */
};

struct icpustate;

#ifdef __x86_64__
INTDEF byte_t *(KCALL x86_decode_modrm)(byte_t *__restrict text, struct modrm *__restrict info, op_flag_t flags);
#else /* __x86_64__ */
INTDEF byte_t *(KCALL x86_decode_modrm)(byte_t *__restrict text, struct modrm *__restrict info);
#define x86_decode_modrm(text, info, flags) x86_decode_modrm(text, info)
#endif /* !__x86_64__ */


/* @param: regno: One of `R_*' */
#ifdef __x86_64__
INTDEF ATTR_PURE WUNUSED NONNULL((1)) u8 NOTHROW(FCALL x86_icpustate_get8)(struct icpustate *__restrict state, u8 regno, op_flag_t flags);
INTDEF NONNULL((1)) void NOTHROW(FCALL x86_icpustate_set8)(struct icpustate *__restrict state, u8 regno, op_flag_t flags, u8 value);
#else /* __x86_64__ */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) u8 NOTHROW(FCALL x86_icpustate_get8)(struct icpustate *__restrict state, u8 regno);
INTDEF NONNULL((1)) void NOTHROW(FCALL x86_icpustate_set8)(struct icpustate *__restrict state, u8 regno, u8 value);
#define x86_icpustate_get8(state, regno, flags)        x86_icpustate_get8(state, regno)
#define x86_icpustate_set8(state, regno, flags, value) x86_icpustate_set8(state, regno, value)
#endif /* !__x86_64__ */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) u16 NOTHROW(FCALL x86_icpustate_get16)(struct icpustate *__restrict state, u8 regno);
INTDEF ATTR_PURE WUNUSED NONNULL((1)) u32 NOTHROW(FCALL x86_icpustate_get32)(struct icpustate *__restrict state, u8 regno);
#ifdef __x86_64__
INTDEF NONNULL((1)) void NOTHROW(FCALL x86_icpustate_set16)(struct icpustate *__restrict state, u8 regno, u16 value);
INTDEF NONNULL((1)) void NOTHROW(FCALL x86_icpustate_set32)(struct icpustate *__restrict state, u8 regno, u32 value);
INTDEF ATTR_PURE WUNUSED NONNULL((1)) u64 NOTHROW(FCALL x86_icpustate_get64)(struct icpustate *__restrict state, u8 regno);
INTDEF NONNULL((1)) void NOTHROW(FCALL x86_icpustate_set64)(struct icpustate *__restrict state, u8 regno, u64 value);
#define x86_icpustate_get(state,regno)       x86_icpustate_get64(state,regno)
#define x86_icpustate_set(state,regno,value) x86_icpustate_set64(state,regno,value)
#else /* __x86_64__ */
INTDEF NONNULL((1)) void FCALL x86_icpustate_set16(struct icpustate *__restrict state, u8 regno, u16 value);
INTDEF NONNULL((1)) void FCALL x86_icpustate_set32(struct icpustate *__restrict state, u8 regno, u32 value);
#define x86_icpustate_get(state, regno)        x86_icpustate_get32(state, regno)
#define x86_icpustate_set(state, regno, value) x86_icpustate_set32(state, regno, value)
#endif /* !__x86_64__ */


INTDEF uintptr_t NOTHROW(KCALL x86_decode_segmentbase)(struct icpustate *__restrict state, op_flag_t flags);
INTDEF uintptr_t NOTHROW(KCALL x86_decode_modrmgetmem)(struct icpustate *__restrict state,
                                                       struct modrm *__restrict modrm, op_flag_t flags);

/* Access the register or memory location described by a MODRM instruction. */
INTDEF u8  KCALL modrm_getrmb(struct icpustate *__restrict state, struct modrm *__restrict modrm, op_flag_t flags) THROWS(E_SEGFAULT);
INTDEF u16 KCALL modrm_getrmw(struct icpustate *__restrict state, struct modrm *__restrict modrm, op_flag_t flags) THROWS(E_SEGFAULT);
INTDEF u32 KCALL modrm_getrml(struct icpustate *__restrict state, struct modrm *__restrict modrm, op_flag_t flags) THROWS(E_SEGFAULT);
INTDEF void KCALL modrm_setrmb(struct icpustate *__restrict state, struct modrm *__restrict modrm, op_flag_t flags, u8  value) THROWS(E_SEGFAULT);
INTDEF void KCALL modrm_setrmw(struct icpustate *__restrict state, struct modrm *__restrict modrm, op_flag_t flags, u16 value) THROWS(E_SEGFAULT);
INTDEF void KCALL modrm_setrml(struct icpustate *__restrict state, struct modrm *__restrict modrm, op_flag_t flags, u32 value) THROWS(E_SEGFAULT);
#ifdef __x86_64__
INTDEF u64 KCALL modrm_getrmq(struct icpustate *__restrict state, struct modrm *__restrict modrm, op_flag_t flags) THROWS(E_SEGFAULT);
INTDEF void KCALL modrm_setrmq(struct icpustate *__restrict state, struct modrm *__restrict modrm, op_flag_t flags, u64 value) THROWS(E_SEGFAULT);
#endif /* __x86_64__ */

#define modrm_getregb(state, modrm, flags)        x86_icpustate_get8(state, (modrm)->mi_reg, flags)
#define modrm_setregb(state, modrm, flags, value) x86_icpustate_set8(state, (modrm)->mi_reg, flags, value)
#define modrm_getregw(state, modrm, flags)        x86_icpustate_get16(state, (modrm)->mi_reg)
#define modrm_setregw(state, modrm, flags, value) x86_icpustate_set16(state, (modrm)->mi_reg, value)
#define modrm_getregl(state, modrm, flags)        x86_icpustate_get32(state, (modrm)->mi_reg)
#define modrm_setregl(state, modrm, flags, value) x86_icpustate_set32(state, (modrm)->mi_reg, value)
#ifdef __x86_64__
#define modrm_getregq(state, modrm, flags)        x86_icpustate_get64(state, (modrm)->mi_reg)
#define modrm_setregq(state, modrm, flags, value) x86_icpustate_set64(state, (modrm)->mi_reg, value)
#define modrm_getreg(state, modrm, flags)         x86_icpustate_get64(state, (modrm)->mi_reg)
#define modrm_setreg(state, modrm, flags, value)  x86_icpustate_set64(state, (modrm)->mi_reg, value)
#else /* __x86_64__ */
#define modrm_getreg(state, modrm, flags)         x86_icpustate_get32(state, (modrm)->mi_reg)
#define modrm_setreg(state, modrm, flags, value)  x86_icpustate_set32(state, (modrm)->mi_reg, value)
#endif /* !__x86_64__ */

#define modrm_getrmregb(state, modrm, flags)        x86_icpustate_get8(state, (modrm)->mi_rm, flags)
#define modrm_setrmregb(state, modrm, flags, value) x86_icpustate_set8(state, (modrm)->mi_rm, flags, value)
#define modrm_getrmregw(state, modrm, flags)        x86_icpustate_get16(state, (modrm)->mi_rm)
#define modrm_setrmregw(state, modrm, flags, value) x86_icpustate_set16(state, (modrm)->mi_rm, value)
#define modrm_getrmregl(state, modrm, flags)        x86_icpustate_get32(state, (modrm)->mi_rm)
#define modrm_setrmregl(state, modrm, flags, value) x86_icpustate_set32(state, (modrm)->mi_rm, value)
#ifdef __x86_64__
#define modrm_getrmregq(state, modrm, flags)        x86_icpustate_get64(state, (modrm)->mi_rm)
#define modrm_setrmregq(state, modrm, flags, value) x86_icpustate_set64(state, (modrm)->mi_rm, value)
#define modrm_getrmreg(state, modrm, flags)         x86_icpustate_get64(state, (modrm)->mi_rm)
#define modrm_setrmreg(state, modrm, flags, value)  x86_icpustate_set64(state, (modrm)->mi_rm, value)
#else /* __x86_64__ */
#define modrm_getrmreg(state, modrm, flags)         x86_icpustate_get32(state, (modrm)->mi_rm)
#define modrm_setrmreg(state, modrm, flags, value)  x86_icpustate_set32(state, (modrm)->mi_rm, value)
#endif /* !__x86_64__ */


/* Read (and return) an X86 opcode from `*ptext', updating that pointer
 * to refer to the the opcodes operands, or the next instruction, as well
 * as filling in `*pflags' to contain a set of `F_*' */
#ifdef __x86_64__
INTDEF u32 (KCALL x86_decode_instruction)(struct icpustate *__restrict state, byte_t **__restrict ptext, op_flag_t *__restrict pflags)
		THROWS(E_SEGFAULT, E_ILLEGAL_INSTRUCTION);
#else /* __x86_64__ */
INTDEF u32 (KCALL x86_decode_instruction)(byte_t **__restrict ptext, op_flag_t *__restrict pflags)
		THROWS(E_SEGFAULT);
#define x86_decode_instruction(state, ptext, pflags) x86_decode_instruction(ptext, pflags)
#endif /* !__x86_64__ */


DECL_END

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_FAULT_DECODE_H */
