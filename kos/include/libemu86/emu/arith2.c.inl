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
#ifdef __INTELLISENSE__
#include "../emulate.c.inl"
#endif /* __INTELLISENSE__ */

EMU86_INTELLISENSE_BEGIN(arith2) {

#if EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_ARITH2

#if EMU86_EMULATE_CONFIG_WANT_ARITH2
#define DEFINE_NOT_MODRM_rm(BWLQ, Nbits, Nbytes, mask)                \
	NIF_ONLY_MEMORY(if (EMU86_MODRM_ISREG(modrm.mi_type)) {           \
		u##Nbits reg;                                                 \
		reg = MODRM_GETRMREG##BWLQ();                                 \
		MODRM_SETRMREG##BWLQ(~reg);                                   \
	} else) {                                                         \
		byte_t *addr;                                                 \
		/* Use XOR to implement NOT */                                \
		addr = MODRM_MEMADDR();                                       \
		EMU86_WRITE_USER_MEMORY(addr, Nbytes);                        \
		EMU86_MEM_ATOMIC_FETCHXOR##BWLQ(addr, mask, EMU86_HASLOCK()); \
	}

#define DEFINE_NEG_MODRM_rm(bwlq, BWLQ, Nbits, Nbytes, maxbit_set)  \
	u32 eflags_addend = 0;                                          \
	u##Nbits oldval, newval;                                        \
	NIF_ONLY_MEMORY(if (EMU86_MODRM_ISREG(modrm.mi_type)) {         \
		oldval = MODRM_GETRMREG##BWLQ();                            \
		newval = (u##Nbits)0 - oldval;                              \
		MODRM_SETRMREG##BWLQ(newval);                               \
	} else) {                                                       \
		byte_t *addr;                                               \
		/* Use XOR to implement NEG */                              \
		addr = MODRM_MEMADDR();                                     \
		EMU86_WRITE_USER_MEMORY(addr, Nbytes);                      \
		for (;;) {                                                  \
			oldval = EMU86_MEMREAD##BWLQ(addr);                     \
			newval = (u##Nbits)0 - oldval;                          \
			if (EMU86_MEM_ATOMIC_CMPXCH##BWLQ(addr, oldval, newval, \
			                                  EMU86_HASLOCK()))     \
				break;                                              \
			EMU86_EMULATE_LOOPHINT();                               \
		}                                                           \
	}                                                               \
	if (oldval != 0)                                                \
		eflags_addend |= EFLAGS_CF;                                 \
	if (oldval == maxbit_set) /* 0x80, 0x8000, etc... */            \
		eflags_addend |= EFLAGS_OF;                                 \
	if (emu86_getflags_AF_sub(0, oldval))                           \
		eflags_addend |= EFLAGS_AF;                                 \
	EMU86_MSKFLAGS(~(EFLAGS_CF | EFLAGS_OF | EFLAGS_SF |            \
	                 EFLAGS_ZF | EFLAGS_AF | EFLAGS_PF),            \
	               eflags_addend | emu86_geteflags_test##bwlq(newval));
#endif /* EMU86_EMULATE_CONFIG_WANT_ARITH2 */


case EMU86_OPCODE_ENCODE(0xf6):
#if EMU86_EMULATE_CONFIG_WANT_ARITH2
	MODRM_DECODE();
	switch (modrm.mi_reg) {

	case 0:
	case 1: { /* Undocumented alias */
		u8 oldval, mask;
		/* F6 /0 ib      TEST r/m8,imm8      AND imm8 with r/m8; set SF, ZF, PF according to result */
		mask = *(u8 const *)pc;
		pc += 1;
		oldval = MODRM_GETRMB();
		oldval &= mask;
		EMU86_MSKFLAGS(~(EFLAGS_SF | EFLAGS_ZF | EFLAGS_PF),
		               emu86_geteflags_testb(oldval));
		goto done;
	}


	case 2: {
		/* F6 /2      NOT r/m8      Reverse each bit of r/m8 */
		DEFINE_NOT_MODRM_rm(B, 8, 1, UINT8_MAX)
		goto done;
	}

	case 3: {
		/* F6 /3      NEG r/m8      Two's complement negate r/m8 */
		DEFINE_NEG_MODRM_rm(b, B, 8, 1, UINT8_C(0x80))
		goto done;
	}

	case 4: {
		/* F6 /4      MUL r/m8      Unsigned multiply (AX = AL * r/m8) */
		u8 rhs = MODRM_GETRMB();
		u8 lhs = EMU86_GETAL();
		u16 result;
		result = (u16)lhs * (u16)rhs;
		EMU86_SETAX(result);
		EMU86_MSKFLAGS(~(EFLAGS_OF | EFLAGS_CF),
		               (result & UINT16_C(0xff00)) != 0
		               ? (EFLAGS_OF | EFLAGS_CF)
		               : 0);
		goto done;
	}

	case 5: {
		/* F6 /5      IMUL r/m8      AX = AL * r/m byte */
		s8 rhs = (s8)MODRM_GETRMB();
		s8 lhs = (s8)EMU86_GETAL();
		s16 result;
		result = (s16)lhs * (s16)rhs;
		EMU86_SETAX((u16)result);
		EMU86_MSKFLAGS(~(EFLAGS_OF | EFLAGS_CF),
		               (((u16)result & UINT16_C(0xff80)) != UINT16_C(0xff80) &&
		                ((u16)result & UINT16_C(0xff80)) != 0)
		               ? (EFLAGS_OF | EFLAGS_CF)
		               : 0);
		goto done;
	}

#ifndef NIF_EMU86_EMULATE_THROW_DIVIDE_BY_ZERO_ALLOW_RETHROW
#if EMU86_EMULATE_THROW_DIVIDE_BY_ZERO_ALLOW_RETHROW
#define NIF_EMU86_EMULATE_THROW_DIVIDE_BY_ZERO_ALLOW_RETHROW(...) /* nothing */
#else /* EMU86_EMULATE_THROW_DIVIDE_BY_ZERO_ALLOW_RETHROW */
#define NIF_EMU86_EMULATE_THROW_DIVIDE_BY_ZERO_ALLOW_RETHROW(...) __VA_ARGS__
#endif /* !EMU86_EMULATE_THROW_DIVIDE_BY_ZERO_ALLOW_RETHROW */
#endif /* !NIF_EMU86_EMULATE_THROW_DIVIDE_BY_ZERO_ALLOW_RETHROW */

	case 6: {
		u16 lhs, divres;
		u8 rhs, modres;
		/* F6 /6      DIV r/m8      Unsigned divide AX by r/m8, with result stored in AL = Quotient, AH = Remainder */
		lhs = EMU86_GETAX();
		rhs = MODRM_GETRMB();
		NIF_EMU86_EMULATE_THROW_DIVIDE_BY_ZERO_ALLOW_RETHROW(TRY) {
			divres = (u16)(lhs / rhs);
			modres = (u8)(lhs % rhs);
		} NIF_EMU86_EMULATE_THROW_DIVIDE_BY_ZERO_ALLOW_RETHROW(EXCEPT {
			if (was_thrown(E_DIVIDE_BY_ZERO))
				EMU86_EMULATE_THROW_DIVIDE_BY_ZEROB(lhs);
			RETHROW();
		});
		if unlikely(divres > 0xff)
			EMU86_EMULATE_THROW_DIVIDE_OVERFLOWB(lhs, rhs, divres);
		EMU86_SETAL((u8)divres);
		EMU86_SETAH(modres);
		goto done;
	}

	case 7: {
		s16 lhs, divres;
		s8 rhs, modres;
		/* F6 /7      IDIV r/m8      Signed divide AX by r/m8, with result stored in AL = Quotient, AH = Remainder */
		lhs = (s16)EMU86_GETAX();
		rhs = (s8)MODRM_GETRMB();
		NIF_EMU86_EMULATE_THROW_DIVIDE_BY_ZERO_ALLOW_RETHROW(TRY) {
			divres = (s16)(lhs / rhs);
			modres = (s8)(lhs % rhs);
		} NIF_EMU86_EMULATE_THROW_DIVIDE_BY_ZERO_ALLOW_RETHROW(EXCEPT {
			if (was_thrown(E_DIVIDE_BY_ZERO))
				EMU86_EMULATE_THROW_SIGNED_DIVIDE_BY_ZEROB(lhs);
			RETHROW();
		});
		if unlikely(divres < INT8_MIN || divres > INT8_MAX)
			EMU86_EMULATE_THROW_SIGNED_DIVIDE_OVERFLOWB(lhs, rhs, divres);
		EMU86_SETAL((u8)(u16)divres);
		EMU86_SETAH((u8)modres);
		goto done;
	}

	default:
#if LIBEMU86_CONFIG_WANT_64BIT
#define NEED_return_unknown_instruction_rmreg
		goto return_unknown_instruction_rmreg;
#else /* LIBEMU86_CONFIG_WANT_64BIT */
		__builtin_unreachable();
#endif /* !LIBEMU86_CONFIG_WANT_64BIT */
	}
#else /* EMU86_EMULATE_CONFIG_WANT_ARITH2 */
	MODRM_DECODE();
#if LIBEMU86_CONFIG_WANT_64BIT
	if (modrm.mi_reg >= 8) {
#define NEED_return_unknown_instruction_rmreg
		goto return_unknown_instruction_rmreg;
	}
#endif /* LIBEMU86_CONFIG_WANT_64BIT */
	if (modrm.mi_reg == 0) {
		MODRM_NOSUP_GETRMB();
	} else {
		MODRM_NOSUP_GETSETRMB();
	}
	goto return_unsupported_instruction_rmreg;
#define NEED_return_unsupported_instruction_rmreg
#endif /* !EMU86_EMULATE_CONFIG_WANT_ARITH2 */
	break;


case EMU86_OPCODE_ENCODE(0xf7):
#if EMU86_EMULATE_CONFIG_WANT_ARITH2
	MODRM_DECODE();
	switch (modrm.mi_reg) {

	case 0:
	case 1: { /* Undocumented alias */
		/* F7 /0 iw      TEST r/m16,imm16      AND imm16 with r/m16; set SF, ZF, PF according to result
		 * F7 /0 id      TEST r/m32,imm32      AND imm32 with r/m32; set SF, ZF, PF according to result
		 * F7 /0 id      TEST r/m64,Simm32     AND Simm32 with r/m64; set SF, ZF, PF according to result */
		IF_64BIT(if (IS_64BIT()) {
			u64 oldval, mask;
			mask = (u64)(s64)(s32)UNALIGNED_GETLE32(pc);
			pc += 4;
			oldval = MODRM_GETRMQ();
			oldval &= mask;
			EMU86_MSKFLAGS(~(EFLAGS_SF | EFLAGS_ZF | EFLAGS_PF),
			               emu86_geteflags_testq(oldval));
		} else) if (!IS_16BIT()) {
			u32 oldval, mask;
			mask = UNALIGNED_GETLE32(pc);
			pc += 4;
			oldval = MODRM_GETRML();
			oldval &= mask;
			EMU86_MSKFLAGS(~(EFLAGS_SF | EFLAGS_ZF | EFLAGS_PF),
			               emu86_geteflags_testl(oldval));
		} else {
			u16 oldval, mask;
			mask = UNALIGNED_GETLE16(pc);
			pc += 2;
			oldval = MODRM_GETRMW();
			oldval &= mask;
			EMU86_MSKFLAGS(~(EFLAGS_SF | EFLAGS_ZF | EFLAGS_PF),
			               emu86_geteflags_testw(oldval));
		}
		goto done;
	}

	case 2:
		/* F7 /2      NOT r/m16      Reverse each bit of r/m16
		 * F7 /2      NOT r/m32      Reverse each bit of r/m32
		 * F7 /2      NOT r/m64      Reverse each bit of r/m64 */
		IF_64BIT(if (IS_64BIT()) {
			DEFINE_NOT_MODRM_rm(Q, 64, 8, UINT64_MAX)
		} else) if (!IS_16BIT()) {
			DEFINE_NOT_MODRM_rm(L, 32, 4, UINT32_MAX)
		} else {
			DEFINE_NOT_MODRM_rm(W, 16, 2, UINT16_MAX)
		}
		goto done;

	case 3:
		/* F7 /3      NEG r/m16      Two's complement negate r/m16
		 * F7 /3      NEG r/m32      Two's complement negate r/m32
		 * F7 /3      NEG r/m64      Two's complement negate r/m64 */
		IF_64BIT(if (IS_64BIT()) {
			DEFINE_NEG_MODRM_rm(q, Q, 64, 8, UINT64_C(0x8000000000000000))
		} else) if (!IS_16BIT()) {
			DEFINE_NEG_MODRM_rm(l, L, 32, 4, UINT32_C(0x80000000))
		} else {
			DEFINE_NEG_MODRM_rm(w, W, 16, 2, UINT16_C(0x8000))
		}
		goto done;

	case 4: {
		/* F7 /4      MUL r/m16      Unsigned multiply (DX:AX = AX * r/m16)
		 * F7 /4      MUL r/m32      Unsigned multiply (EDX:EAX = EAX * r/m32)
		 * F7 /4      MUL r/m64      Unsigned multiply (RDX:RAX = RAX * r/m64) */
		bool is_upper_half_needed;
#if LIBEMU86_CONFIG_WANT_64BIT
		if (IS_64BIT()) {
#ifdef __UINT128_TYPE__
			u64 rhs = MODRM_GETRMQ();
			u64 lhs = EMU86_GETRAX();
			union {
				__UINT128_TYPE__ word128;
				u64 qwords[2];
			} result;
			result.word128 = (__UINT128_TYPE__)lhs *
			                 (__UINT128_TYPE__)rhs;
			EMU86_SETRAX(result.qwords[0]);
			EMU86_SETRDX(result.qwords[1]);
			is_upper_half_needed = result.qwords[1] != 0;
#else /* __UINT128_TYPE__ */
			/* XXX: Emulate this? */
#define NEED_return_unsupported_instruction_rmreg
			goto return_unsupported_instruction_rmreg;
#endif /* !__UINT128_TYPE__ */
		} else
#endif /* LIBEMU86_CONFIG_WANT_64BIT */
		if (!IS_16BIT()) {
			u32 rhs = MODRM_GETRML();
			u32 lhs = EMU86_GETEAX();
			union {
				u64 qword;
				u32 dwords[2];
			} result;
			result.qword = (u64)lhs * (u64)rhs;
			EMU86_SETEAX(result.dwords[0]);
			EMU86_SETEDX(result.dwords[1]);
			is_upper_half_needed = result.dwords[1] != 0;
		} else {
			u16 rhs = MODRM_GETRMW();
			u16 lhs = EMU86_GETAX();
			union {
				u32 dword;
				u16 words[2];
			} result;
			result.dword = (u32)lhs * (u32)rhs;
			EMU86_SETAX(result.words[0]);
			EMU86_SETDX(result.words[1]);
			is_upper_half_needed = result.words[1] != 0;
		}
		EMU86_MSKFLAGS(~(EFLAGS_OF | EFLAGS_CF),
		               is_upper_half_needed
		               ? (EFLAGS_OF | EFLAGS_CF)
		               : 0);
		goto done;
	}

	case 5: {
		/* F7 /5      IMUL r/m16      DX:AX = AX * r/m word
		 * F7 /5      IMUL r/m32      EDX:EAX = EAX * r/m doubleword
		 * F7 /5      IMUL r/m64      RDX:RAX = RAX * r/m doubleword */
		bool is_upper_half_needed;
#if LIBEMU86_CONFIG_WANT_64BIT
		if (IS_64BIT()) {
#ifdef __UINT128_TYPE__
			s64 rhs = (s64)MODRM_GETRMQ();
			s64 lhs = (s64)EMU86_GETRAX();
			union {
				__INT128_TYPE__ word128;
				u64 qwords[2];
			} result;
			result.word128 = (__INT128_TYPE__)lhs *
			                 (__INT128_TYPE__)rhs;
			EMU86_SETRAX(result.qwords[0]);
			EMU86_SETRDX(result.qwords[1]);
			is_upper_half_needed = result.qwords[1] == 0
			                       ? (result.qwords[0] & UINT64_C(0x8000000000000000)) == 0
			                       : result.qwords[1] == UINT64_C(0xffffffffffffffff)
			                         ? (result.qwords[0] & UINT64_C(0x8000000000000000)) != 0
			                         : true;
#else /* __UINT128_TYPE__ */
#define NEED_return_unsupported_instruction_rmreg
			goto return_unsupported_instruction_rmreg;
#endif /* !__UINT128_TYPE__ */
		} else
#endif /* LIBEMU86_CONFIG_WANT_64BIT */
		if (!IS_16BIT()) {
			s32 rhs = (s32)MODRM_GETRML();
			s32 lhs = (s32)EMU86_GETEAX();
			union {
				s64 qword;
				u32 dwords[2];
			} result;
			result.qword = (s64)lhs * (s64)rhs;
			EMU86_SETEAX(result.dwords[0]);
			EMU86_SETEDX(result.dwords[1]);
			is_upper_half_needed = result.dwords[1] == 0
			                       ? (result.dwords[0] & UINT32_C(0x80000000)) == 0
			                       : result.dwords[1] == UINT32_C(0xffffffff)
			                         ? (result.dwords[0] & UINT32_C(0x80000000)) != 0
			                         : true;
		} else {
			s16 rhs = (s16)MODRM_GETRMW();
			s16 lhs = (s16)EMU86_GETAX();
			union {
				s32 dword;
				u16 words[2];
			} result;
			result.dword = (s32)lhs * (s32)rhs;
			EMU86_SETAX(result.words[0]);
			EMU86_SETDX(result.words[1]);
			is_upper_half_needed = (((u32)result.dword & UINT32_C(0xffff8000)) != UINT32_C(0xffff8000) &&
			                         ((u32)result.dword & UINT32_C(0xffff8000)) != 0);
		}
		EMU86_MSKFLAGS(~(EFLAGS_OF | EFLAGS_CF),
		               is_upper_half_needed
		               ? (EFLAGS_OF | EFLAGS_CF)
		               : 0);
		goto done;
	}

	case 6:
		/* F7 /6      DIV r/m16      Unsigned divide DX:AX by r/m16, with result stored in AX = Quotient, DX = Remainder
		 * F7 /6      DIV r/m32      Unsigned divide EDX:EAX by r/m32, with result stored in EAX = Quotient, EDX = Remainder
		 * F7 /6      DIV r/m64      Unsigned divide RDX:RAX by r/m64, with result stored in RAX = Quotient, RDX = Remainder */
#if LIBEMU86_CONFIG_WANT_64BIT
		if (IS_64BIT()) {
#ifdef __UINT128_TYPE__
			union {
				__UINT128_TYPE__ word128;
				u64 qwords[2];
			} lhs, divres;
			u64 rhs, modres;
			lhs.qwords[0] = EMU86_GETRAX();
			lhs.qwords[1] = EMU86_GETRDX();
			rhs           = MODRM_GETRMQ();
			NIF_EMU86_EMULATE_THROW_DIVIDE_BY_ZERO_ALLOW_RETHROW(TRY) {
				divres.word128 = (__UINT128_TYPE__)(lhs.word128 / rhs);
				modres         = (u64)(lhs.word128 % rhs);
			} NIF_EMU86_EMULATE_THROW_DIVIDE_BY_ZERO_ALLOW_RETHROW(EXCEPT {
				if (was_thrown(E_DIVIDE_BY_ZERO))
					EMU86_EMULATE_THROW_DIVIDE_BY_ZEROQ(lhs);
				RETHROW();
			});
			if unlikely(divres.qwords[1] != 0)
				EMU86_EMULATE_THROW_DIVIDE_OVERFLOWQ(lhs, rhs, divres.word128);
			EMU86_SETRAX(divres.qwords[0]);
			EMU86_SETRDX(modres);
#else /* __UINT128_TYPE__ */
#define NEED_return_unsupported_instruction_rmreg
			goto return_unsupported_instruction_rmreg;
#endif /* !__UINT128_TYPE__ */
		} else
#endif /* LIBEMU86_CONFIG_WANT_64BIT */
		if (!IS_16BIT()) {
			union {
				u64 qword;
				u32 dwords[2];
			} lhs, divres;
			u32 rhs, modres;
			lhs.dwords[0] = EMU86_GETEAX();
			lhs.dwords[1] = EMU86_GETEDX();
			rhs           = MODRM_GETRML();
			NIF_EMU86_EMULATE_THROW_DIVIDE_BY_ZERO_ALLOW_RETHROW(TRY) {
				divres.qword = (u64)(lhs.qword / rhs);
				modres       = (u32)(lhs.qword % rhs);
			} NIF_EMU86_EMULATE_THROW_DIVIDE_BY_ZERO_ALLOW_RETHROW(EXCEPT {
				if (was_thrown(E_DIVIDE_BY_ZERO))
					EMU86_EMULATE_THROW_DIVIDE_BY_ZEROL(lhs);
				RETHROW();
			});
			if unlikely(divres.dwords[1] != 0)
				EMU86_EMULATE_THROW_DIVIDE_OVERFLOWL(lhs, rhs, divres.qword);
			EMU86_SETEAX(divres.dwords[0]);
			EMU86_SETEDX(modres);
		} else {
			union {
				u32 dword;
				u16 words[2];
			} lhs, divres;
			u16 rhs, modres;
			lhs.words[0] = EMU86_GETAX();
			lhs.words[1] = EMU86_GETDX();
			rhs          = MODRM_GETRMW();
			NIF_EMU86_EMULATE_THROW_DIVIDE_BY_ZERO_ALLOW_RETHROW(TRY) {
				divres.dword = (u32)(lhs.dword / rhs);
				modres       = (u16)(lhs.dword % rhs);
			} NIF_EMU86_EMULATE_THROW_DIVIDE_BY_ZERO_ALLOW_RETHROW(EXCEPT {
				if (was_thrown(E_DIVIDE_BY_ZERO))
					EMU86_EMULATE_THROW_DIVIDE_BY_ZEROW(lhs);
				RETHROW();
			});
			if unlikely(divres.words[1] != 0)
				EMU86_EMULATE_THROW_DIVIDE_OVERFLOWW(lhs, rhs, divres.dword);
			EMU86_SETAX(divres.words[0]);
			EMU86_SETDX(modres);
		}
		goto done;

	case 7:
		/* F7 /7      IDIV r/m16      Signed divide DX:AX by r/m16, with result stored in AX = Quotient, DX = Remainder
		 * F7 /7      IDIV r/m32      Signed divide EDX:EAX by r/m32, with result stored in EAX = Quotient, EDX = Remainder
		 * F7 /7      IDIV r/m64      Signed divide RDX:RAX by r/m64, with result stored in RAX = Quotient, RDX = Remainder */
#if LIBEMU86_CONFIG_WANT_64BIT
		if (IS_64BIT()) {
#ifdef __UINT128_TYPE__
			union {
				__INT128_TYPE__ word128;
				u64 qwords[2];
			} lhs, divres;
			s64 rhs, modres;
			lhs.qwords[0] = EMU86_GETRAX();
			lhs.qwords[1] = EMU86_GETRDX();
			rhs           = (s64)MODRM_GETRMQ();
			NIF_EMU86_EMULATE_THROW_DIVIDE_BY_ZERO_ALLOW_RETHROW(TRY) {
				divres.word128 = (__INT128_TYPE__)(lhs.word128 / rhs);
				modres         = (s64)(lhs.word128 % rhs);
			} NIF_EMU86_EMULATE_THROW_DIVIDE_BY_ZERO_ALLOW_RETHROW(EXCEPT {
				if (was_thrown(E_DIVIDE_BY_ZERO))
					EMU86_EMULATE_THROW_SIGNED_DIVIDE_BY_ZEROQ(lhs);
				RETHROW();
			});
			if unlikely(divres.qwords[1] == 0
			            ? (divres.qwords[0] & UINT64_C(0x8000000000000000)) != 0
			            : divres.qwords[1] == UINT64_MAX
			              ? (divres.qwords[0] & UINT64_C(0x8000000000000000)) == 0
			              : true)
				EMU86_EMULATE_THROW_SIGNED_DIVIDE_OVERFLOWQ(lhs, rhs, divres.word128);
			EMU86_SETRAX(divres.qwords[0]);
			EMU86_SETRDX((u64)modres);
#else /* __UINT128_TYPE__ */
#define NEED_return_unsupported_instruction_rmreg
			goto return_unsupported_instruction_rmreg;
#endif /* !__UINT128_TYPE__ */
		} else
#endif /* LIBEMU86_CONFIG_WANT_64BIT */
		if (!IS_16BIT()) {
			union {
				s64 qword;
				u32 dwords[2];
			} lhs, divres;
			s32 rhs, modres;
			lhs.dwords[0] = EMU86_GETEAX();
			lhs.dwords[1] = EMU86_GETEDX();
			rhs           = (s32)MODRM_GETRML();
			NIF_EMU86_EMULATE_THROW_DIVIDE_BY_ZERO_ALLOW_RETHROW(TRY) {
				divres.qword = (s64)(lhs.qword / rhs);
				modres       = (s32)(lhs.qword % rhs);
			} NIF_EMU86_EMULATE_THROW_DIVIDE_BY_ZERO_ALLOW_RETHROW(EXCEPT {
				if (was_thrown(E_DIVIDE_BY_ZERO))
					EMU86_EMULATE_THROW_SIGNED_DIVIDE_BY_ZEROL(lhs);
				RETHROW();
			});
			if unlikely(divres.qword < INT32_MIN || divres.qword > INT32_MAX)
				EMU86_EMULATE_THROW_SIGNED_DIVIDE_OVERFLOWL(lhs, rhs, divres.qword);
			EMU86_SETEAX(divres.dwords[0]);
			EMU86_SETEDX((u32)modres);
		} else {
			union {
				s32 dword;
				u16 words[2];
			} lhs, divres;
			s16 rhs, modres;
			lhs.words[0] = EMU86_GETAX();
			lhs.words[1] = EMU86_GETDX();
			rhs          = (s16)MODRM_GETRMW();
			NIF_EMU86_EMULATE_THROW_DIVIDE_BY_ZERO_ALLOW_RETHROW(TRY) {
				divres.dword = (s32)(lhs.dword / rhs);
				modres       = (s16)(lhs.dword % rhs);
			} NIF_EMU86_EMULATE_THROW_DIVIDE_BY_ZERO_ALLOW_RETHROW(EXCEPT {
				if (was_thrown(E_DIVIDE_BY_ZERO))
					EMU86_EMULATE_THROW_SIGNED_DIVIDE_BY_ZEROW(lhs);
				RETHROW();
			});
			if unlikely(divres.dword < INT16_MIN || divres.dword > INT16_MAX)
				EMU86_EMULATE_THROW_SIGNED_DIVIDE_OVERFLOWW(lhs, rhs, divres.dword);
			EMU86_SETAX(divres.words[0]);
			EMU86_SETDX((u16)modres);
		}
		goto done;

	default:
#if LIBEMU86_CONFIG_WANT_64BIT
#define NEED_return_unknown_instruction_rmreg
		goto return_unknown_instruction_rmreg;
#else /* LIBEMU86_CONFIG_WANT_64BIT */
		__builtin_unreachable();
#endif /* !LIBEMU86_CONFIG_WANT_64BIT */
	}
#else /* EMU86_EMULATE_CONFIG_WANT_ARITH2 */
	MODRM_DECODE();
#if LIBEMU86_CONFIG_WANT_64BIT
	if (modrm.mi_reg >= 8) {
#define NEED_return_unknown_instruction_rmreg
		goto return_unknown_instruction_rmreg;
	}
#endif /* LIBEMU86_CONFIG_WANT_64BIT */
	if (modrm.mi_reg == 0) {
		MODRM_NOSUP_GETRMWLQ();
	} else {
		MODRM_NOSUP_GETSETRMWLQ();
	}
	goto return_unsupported_instruction_rmreg;
#define NEED_return_unsupported_instruction_rmreg
#endif /* !EMU86_EMULATE_CONFIG_WANT_ARITH2 */
	break;

#undef DEFINE_NEG_MODRM_rm
#undef DEFINE_NOT_MODRM_rm


case EMU86_OPCODE_ENCODE(0x84): {
	/* 84 /r      TEST r/m8,r8      AND r8 with r/m8; set SF, ZF, PF according to result */
#if EMU86_EMULATE_CONFIG_WANT_ARITH2
	u8 lhs, rhs;
	MODRM_DECODE();
	lhs = MODRM_GETRMB();
	rhs = MODRM_GETREGB();
	EMU86_MSKFLAGS(~(EFLAGS_SF | EFLAGS_ZF | EFLAGS_PF),
	               emu86_geteflags_testb(lhs & rhs));
	goto done;
#else /* EMU86_EMULATE_CONFIG_WANT_ARITH2 */
#define NEED_notsup_modrm_getb
	goto notsup_modrm_getb;
#endif /* !EMU86_EMULATE_CONFIG_WANT_ARITH2 */
}



case EMU86_OPCODE_ENCODE(0x85): {
#if EMU86_EMULATE_CONFIG_WANT_ARITH2
	/* 85 /r      TEST r/m16,r16      AND r16 with r/m16; set SF, ZF, PF according to result
	 * 85 /r      TEST r/m32,r32      AND r32 with r/m32; set SF, ZF, PF according to result
	 * 85 /r      TEST r/m64,r64      AND r64 with r/m64; set SF, ZF, PF according to result */
	MODRM_DECODE();
	IF_64BIT(if (IS_64BIT()) {
		u64 lhs, rhs;
		lhs = MODRM_GETRMQ();
		rhs = MODRM_GETREGQ();
		EMU86_MSKFLAGS(~(EFLAGS_SF | EFLAGS_ZF | EFLAGS_PF),
		               emu86_geteflags_testq(lhs & rhs));
	} else) if (!IS_16BIT()) {
		u32 lhs, rhs;
		lhs = MODRM_GETRML();
		rhs = MODRM_GETREGL();
		EMU86_MSKFLAGS(~(EFLAGS_SF | EFLAGS_ZF | EFLAGS_PF),
		               emu86_geteflags_testl(lhs & rhs));
	} else {
		u16 lhs, rhs;
		lhs = MODRM_GETRMW();
		rhs = MODRM_GETREGW();
		EMU86_MSKFLAGS(~(EFLAGS_SF | EFLAGS_ZF | EFLAGS_PF),
		               emu86_geteflags_testw(lhs & rhs));
	}
	goto done;
#else /* EMU86_EMULATE_CONFIG_WANT_ARITH2 */
#define NEED_notsup_modrm_getwlq
	goto notsup_modrm_getwlq;
#endif /* !EMU86_EMULATE_CONFIG_WANT_ARITH2 */
}


case EMU86_OPCODE_ENCODE(0x0faf): {
#if EMU86_EMULATE_CONFIG_WANT_ARITH2
	/*         0F AF /r     IMUL r16, r/m16     word register <- word register * r/m16.
	 *         0F AF /r     IMUL r32, r/m32     doubleword register <- doubleword register * r/m32.
	 * REX.W + 0F AF /r     IMUL r64, r/m64     Quadword register <- Quadword register * r/m64. */
	bool overflow;
	MODRM_DECODE();
	IF_64BIT(if (IS_64BIT()) {
		s64 lhs, rhs, result;
		lhs      = (s64)MODRM_GETREGQ();
		rhs      = (s64)MODRM_GETRMQ();
		overflow = OVERFLOW_SMUL(lhs, rhs, &result);
		MODRM_SETREGQ((u64)result);
	} else) if (!IS_16BIT()) {
		s32 lhs, rhs, result;
		lhs      = (s32)MODRM_GETREGL();
		rhs      = (s32)MODRM_GETRML();
		overflow = OVERFLOW_SMUL(lhs, rhs, &result);
		MODRM_SETREGL((u32)result);
	} else {
		s16 lhs, rhs, result;
		lhs      = (s16)MODRM_GETREGW();
		rhs      = (s16)MODRM_GETRMW();
		overflow = OVERFLOW_SMUL(lhs, rhs, &result);
		MODRM_SETREGW((u16)result);
	}
	EMU86_MSKFLAGS(~(EFLAGS_CF | EFLAGS_OF),
	               overflow
	               ? (EFLAGS_CF | EFLAGS_OF)
	               : 0);
	goto done;
#else /* EMU86_EMULATE_CONFIG_WANT_ARITH2 */
#define NEED_notsup_modrm_getwlq
	goto notsup_modrm_getwlq;
#endif /* !EMU86_EMULATE_CONFIG_WANT_ARITH2 */
}


case EMU86_OPCODE_ENCODE(0x6b): {
	/*         6B /r ib     IMUL r16, r/m16, imm8     word register <- r/m16 * sign-extended immediate byte.
	 *         6B /r ib     IMUL r32, r/m32, imm8     doubleword register <- r/m32 * sign-extended immediate byte.
	 * REX.W + 6B /r ib     IMUL r64, r/m64, imm8     Quadword register <- r/m64 * sign-extended immediate byte. */
#if EMU86_EMULATE_CONFIG_WANT_ARITH2
	s8 imm;
	bool overflow;
	MODRM_DECODE();
	imm = *(s8 const *)pc;
	pc += 1;
	IF_64BIT(if (IS_64BIT()) {
		s64 lhs, result;
		lhs      = (s64)MODRM_GETRMQ();
		overflow = OVERFLOW_SMUL(lhs, imm, &result);
		MODRM_SETREGQ((u64)result);
	} else) if (!IS_16BIT()) {
		s32 lhs, result;
		lhs      = (s32)MODRM_GETRML();
		overflow = OVERFLOW_SMUL(lhs, imm, &result);
		MODRM_SETREGL((u32)result);
	} else {
		s16 lhs, result;
		lhs      = (s16)MODRM_GETRMW();
		overflow = OVERFLOW_SMUL(lhs, imm, &result);
		MODRM_SETREGW((u16)result);
	}
	EMU86_MSKFLAGS(~(EFLAGS_CF | EFLAGS_OF),
	               overflow
	               ? (EFLAGS_CF | EFLAGS_OF)
	               : 0);
	goto done;
#else /* EMU86_EMULATE_CONFIG_WANT_ARITH2 */
#define NEED_notsup_modrm_getwlq
	goto notsup_modrm_getwlq;
#endif /* !EMU86_EMULATE_CONFIG_WANT_ARITH2 */
}


case EMU86_OPCODE_ENCODE(0x69): {
	/*         69 /r iw     IMUL r16, r/m16, imm16     word register <- r/m16 * immediate word.
	 *         69 /r id     IMUL r32, r/m32, imm32     doubleword register <- r/m32 * immediate doubleword.
	 * REX.W + 69 /r id     IMUL r64, r/m64, imm32     Quadword register <- r/m64 * immediate doubleword. */
#if EMU86_EMULATE_CONFIG_WANT_ARITH2
	bool overflow;
	MODRM_DECODE();
	IF_64BIT(if (IS_64BIT()) {
		s32 imm;
		s64 lhs, result;
		imm = (s32)UNALIGNED_GETLE32(pc);
		pc += 4;
		lhs      = (s64)MODRM_GETRMQ();
		overflow = OVERFLOW_SMUL(lhs, imm, &result);
		MODRM_SETREGQ((u64)result);
	} else) if (!IS_16BIT()) {
		s32 lhs, imm, result;
		imm = (s32)UNALIGNED_GETLE32(pc);
		pc += 4;
		lhs      = (s32)MODRM_GETRML();
		overflow = OVERFLOW_SMUL(lhs, imm, &result);
		MODRM_SETREGL((u32)result);
	} else {
		s16 lhs, imm, result;
		imm = (s16)UNALIGNED_GETLE16(pc);
		pc += 2;
		lhs      = (s16)MODRM_GETRMW();
		overflow = OVERFLOW_SMUL(lhs, imm, &result);
		MODRM_SETREGW((u16)result);
	}
	EMU86_MSKFLAGS(~(EFLAGS_CF | EFLAGS_OF),
	               overflow
	               ? (EFLAGS_CF | EFLAGS_OF)
	               : 0);
	goto done;
#else /* EMU86_EMULATE_CONFIG_WANT_ARITH2 */
#define NEED_notsup_modrm_getwlq
	goto notsup_modrm_getwlq;
#endif /* !EMU86_EMULATE_CONFIG_WANT_ARITH2 */
}


#if !EMU86_EMULATE_CONFIG_ONLY_MEMORY
#if EMU86_EMULATE_CONFIG_WANT_ARITH2
case EMU86_OPCODE_ENCODE(0xa8): {
	/*         A8 ib     TEST AL, imm8       AND imm8 with AL; set SF, ZF, PF according to result. */
	u8 lhs, imm;
	imm = *(u8 const *)pc;
	pc += 1;
	lhs = EMU86_GETAL();
	EMU86_MSKFLAGS(~(EFLAGS_SF | EFLAGS_ZF | EFLAGS_PF),
	               emu86_geteflags_testb(lhs & imm));
	goto done;
}
#elif !EMU86_EMULATE_CONFIG_ONLY_CHECKERROR_NO_BASIC
case EMU86_OPCODE_ENCODE(0xa8): {
	goto return_unsupported_instruction;
#define NEED_return_unsupported_instruction
}
#endif /* ... */

#if EMU86_EMULATE_CONFIG_WANT_ARITH2
case EMU86_OPCODE_ENCODE(0xa9): {
	/*         A9 iw     TEST AX, imm16      AND imm16 with AX; set SF, ZF, PF according to result.
	 *         A9 id     TEST EAX, imm32     AND imm32 with EAX; set SF, ZF, PF according to result.
	 * REX.W + A9 id     TEST RAX, imm32     AND imm32 sign-extended to 64-bits with RAX; set SF, ZF, PF according to result. */
	IF_64BIT(if (IS_64BIT()) {
		u64 lhs, imm;
		imm = (u64)(s64)(s32)UNALIGNED_GETLE32(pc);
		pc += 4;
		lhs = EMU86_GETRAX();
		EMU86_MSKFLAGS(~(EFLAGS_SF | EFLAGS_ZF | EFLAGS_PF),
		               emu86_geteflags_testq(lhs & imm));
	} else) if (!IS_16BIT()) {
		u32 lhs, imm;
		imm = UNALIGNED_GETLE32(pc);
		pc += 4;
		lhs = EMU86_GETEAX();
		EMU86_MSKFLAGS(~(EFLAGS_SF | EFLAGS_ZF | EFLAGS_PF),
		               emu86_geteflags_testl(lhs & imm));
	} else {
		u16 lhs, imm;
		imm = UNALIGNED_GETLE16(pc);
		pc += 2;
		lhs = EMU86_GETAX();
		EMU86_MSKFLAGS(~(EFLAGS_SF | EFLAGS_ZF | EFLAGS_PF),
		               emu86_geteflags_testw(lhs & imm));
	}
	goto done;
}
#elif !EMU86_EMULATE_CONFIG_ONLY_CHECKERROR_NO_BASIC
case EMU86_OPCODE_ENCODE(0xa9): {
	goto return_unsupported_instruction;
#define NEED_return_unsupported_instruction
}
#endif /* ... */
#endif /* !EMU86_EMULATE_CONFIG_ONLY_MEMORY */

#endif /* EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_ARITH2 */

}
EMU86_INTELLISENSE_END
