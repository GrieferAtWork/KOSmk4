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
 *    in a product, an acknowledgement (see the following) in the product     *
 *    documentation is required:                                              *
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifdef __INTELLISENSE__
#include "../emulate.c.inl"
#endif /* __INTELLISENSE__ */

EMU86_INTELLISENSE_BEGIN(arith) {
	u8 op8;
	u16 op16;
	u32 op32;
#if CONFIG_LIBEMU86_WANT_64BIT
	u64 op64;
#endif /* CONFIG_LIBEMU86_WANT_64BIT */


	/* NOTE: Always support register-based MODR/M to support reverse encoded operands */
#define DO_ARITHn(NAME, operator, BWLQ, Nbytes, oldval, rhs)                                         \
	if (EMU86_MODRM_ISMEM(modrm.mi_type)) {                                                          \
		byte_t *_addr = MODRM_MEMADDR();                                                             \
		EMU86_WRITE_USER_MEMORY(_addr, Nbytes);                                                      \
		oldval = EMU86_MEM_ATOMIC_FETCH##NAME##BWLQ(_addr, rhs, (op_flags & EMU86_F_LOCK) != 0); \
	} else {                                                                                         \
		oldval = MODRM_GETRMREG##BWLQ();                                                             \
		MODRM_SETRMREG##BWLQ(oldval operator rhs);                                                   \
	}

	/* Perform an arithmetic `modrm.mi_reg' with the given `rhs' as the right-hand-side
	 * operand, and `modrm.RM' as the left-hand-side. The operation size is described
	 * as the pairing of the other arguments, which must be one of:
	 *            bwlq   BWLQ   Nbytes   Nbits
	 *    8-bit   b      B      1        8
	 *    16-bit  w      W      2        16
	 *    32-bit  l      L      4        32
	 *    64-bit  q      Q      8        64
	 */
#define DO_ARITH_SWITCH_rmdst_mi_reg(bwlq, BWLQ, Nbytes, Nbits, rhs)                 \
	switch (modrm.mi_reg) {                                                          \
		u##Nbits oldval, newval;                                                     \
		u32 eflags_addend;                                                           \
	case 0:                                                                          \
do_add##Nbits:                                                                       \
		DO_ARITHn(ADD, +, BWLQ, Nbytes, oldval, rhs);                                \
		eflags_addend = 0;                                                           \
		if (OVERFLOW_UADD(oldval, rhs, &newval))                                     \
			eflags_addend |= EFLAGS_OF | EFLAGS_CF;                                  \
set_test##Nbits##_after_add:                                                         \
		if (((oldval & 0xf) + (rhs & 0xf)) >= 0x10)                                  \
			eflags_addend |= EFLAGS_AF;                                              \
		if ((s##Nbits)newval < 0)                                                    \
			eflags_addend |= EFLAGS_SF;                                              \
		EMU86_MSKFLAGS(~(EFLAGS_OF | EFLAGS_CF | EFLAGS_SF |                         \
		                 EFLAGS_ZF | EFLAGS_PF | EFLAGS_AF),                         \
		               eflags_addend | emu86_geteflags_test##bwlq(newval));          \
		break;                                                                       \
		                                                                             \
	case 1:                                                                          \
do_or##Nbits:                                                                        \
		DO_ARITHn(OR, |, BWLQ, Nbytes, oldval, rhs);                                 \
		oldval |= rhs;                                                               \
		goto set_test##Nbits;                                                        \
		                                                                             \
	case 2:                                                                          \
do_adc##Nbits:                                                                       \
		if (!(EMU86_GETFLAGS() & EFLAGS_CF))                                         \
			goto do_add##Nbits;                                                      \
		NIF_ONLY_MEMORY(                                                             \
		if (EMU86_MODRM_ISREG(modrm.mi_type)) {                                      \
			if unlikely(op_flags & EMU86_F_LOCK)                                     \
				goto return_unknown_instruction;                                     \
			oldval = MODRM_GETRMREG##BWLQ();                                         \
			eflags_addend = 0;                                                       \
			if (OVERFLOW_UADD(oldval, rhs, &newval))                                 \
				eflags_addend |= EFLAGS_OF | EFLAGS_CF;                              \
			if (OVERFLOW_UADD(newval, 1, &newval))                                   \
				eflags_addend |= EFLAGS_OF | EFLAGS_CF;                              \
			MODRM_SETRMREG##BWLQ(newval);                                            \
		} else) {                                                                    \
			byte_t *addr = MODRM_MEMADDR();                                          \
			EMU86_WRITE_USER_MEMORY(addr, Nbytes);                                   \
			for (;;) {                                                               \
				oldval = EMU86_MEMREAD##BWLQ(addr);                                  \
				eflags_addend = 0;                                                   \
				if (OVERFLOW_UADD(oldval, rhs, &newval))                             \
					eflags_addend |= EFLAGS_OF | EFLAGS_CF;                          \
				if (OVERFLOW_UADD(newval, 1, &newval))                               \
					eflags_addend |= EFLAGS_OF | EFLAGS_CF;                          \
				if (EMU86_MEM_ATOMIC_CMPXCH##BWLQ(addr, oldval, newval,              \
				                                  (op_flags & EMU86_F_LOCK) != 0))   \
					break;                                                           \
				EMU86_EMULATE_LOOPHINT();                                            \
			}                                                                        \
		}                                                                            \
		goto set_test##Nbits##_after_add;                                            \
		                                                                             \
	case 3:                                                                          \
do_sbb##Nbits:                                                                       \
		if (!(EMU86_GETFLAGS() & EFLAGS_CF))                                         \
			goto do_sub##Nbits;                                                      \
		NIF_ONLY_MEMORY(                                                             \
		if (EMU86_MODRM_ISREG(modrm.mi_type)) {                                      \
			if unlikely(op_flags & EMU86_F_LOCK)                                     \
				goto return_unknown_instruction;                                     \
			oldval = MODRM_GETRMREG##BWLQ();                                         \
			eflags_addend = 0;                                                       \
			if (OVERFLOW_USUB(oldval, rhs, &newval))                                 \
				eflags_addend |= EFLAGS_OF | EFLAGS_CF;                              \
			if (OVERFLOW_USUB(newval, 1, &newval))                                   \
				eflags_addend |= EFLAGS_OF | EFLAGS_CF;                              \
			MODRM_SETRMREG##BWLQ(newval);                                            \
		} else) {                                                                    \
			byte_t *addr = MODRM_MEMADDR();                                          \
			EMU86_WRITE_USER_MEMORY(addr, Nbytes);                                   \
			for (;;) {                                                               \
				oldval = EMU86_MEMREAD##BWLQ(addr);                                  \
				eflags_addend = 0;                                                   \
				if (OVERFLOW_USUB(oldval, rhs, &newval))                             \
					eflags_addend |= EFLAGS_OF | EFLAGS_CF;                          \
				if (OVERFLOW_USUB(newval, 1, &newval))                               \
					eflags_addend |= EFLAGS_OF | EFLAGS_CF;                          \
				if (EMU86_MEM_ATOMIC_CMPXCH##BWLQ(addr, oldval, newval,              \
				                                  (op_flags & EMU86_F_LOCK) != 0))   \
					break;                                                           \
				EMU86_EMULATE_LOOPHINT();                                            \
			}                                                                        \
		}                                                                            \
		goto set_test##Nbits##_after_sub;                                            \
		                                                                             \
	case 4:                                                                          \
do_and##Nbits:                                                                       \
		DO_ARITHn(AND, &, BWLQ, Nbytes, oldval, rhs);                                \
		oldval &= rhs;                                                               \
		goto set_test##Nbits;                                                        \
		                                                                             \
	case 5:                                                                          \
do_sub##Nbits:                                                                       \
		DO_ARITHn(SUB, -, BWLQ, Nbytes, oldval, rhs);                                \
set_test##Nbits##_before_sub:                                                        \
		eflags_addend = 0;                                                           \
		if (OVERFLOW_USUB(oldval, rhs, &newval))                                     \
			eflags_addend |= EFLAGS_OF | EFLAGS_CF;                                  \
set_test##Nbits##_after_sub:                                                         \
		if (((oldval & 0xf) + ((0 - (rhs)) & 0xf)) >= 0x10)                          \
			eflags_addend |= EFLAGS_AF;                                              \
		if ((s##Nbits)newval < 0)                                                    \
			eflags_addend |= EFLAGS_SF;                                              \
		EMU86_MSKFLAGS(~(EFLAGS_OF | EFLAGS_CF | EFLAGS_SF |                         \
		                 EFLAGS_ZF | EFLAGS_PF | EFLAGS_AF),                         \
		               eflags_addend | emu86_geteflags_test##bwlq(newval));          \
		break;                                                                       \
		                                                                             \
	case 6:                                                                          \
do_xor##Nbits:                                                                       \
		DO_ARITHn(XOR, ^, BWLQ, Nbytes, oldval, rhs);                                \
		oldval ^= rhs;                                                               \
set_test##Nbits:                                                                     \
		EMU86_MSKFLAGS(~(EFLAGS_OF | EFLAGS_CF | EFLAGS_SF | EFLAGS_ZF | EFLAGS_PF), \
		               emu86_geteflags_test##bwlq(oldval));                          \
		break;                                                                       \
		                                                                             \
	case 7:                                                                          \
do_cmp##Nbits:                                                                       \
		if unlikely(op_flags & EMU86_F_LOCK)                                         \
			goto return_unknown_instruction;                                         \
		/* Always support REGISTER-R/M here! (needed for register write-back) */     \
		IF_ONLY_MEMORY(                                                              \
		oldval = unlikely(EMU86_MODRM_ISREG(modrm.mi_type))                          \
		       ? MODRM_GETRMREG##BWLQ()                                              \
		       : MODRM_GETRM##BWLQ();)                                               \
		NIF_ONLY_MEMORY(oldval = MODRM_GETRM##BWLQ();)                               \
		goto set_test##Nbits##_before_sub;                                           \
		                                                                             \
	default: goto return_unknown_instruction;                                        \
	}


/* ======================================================================== */
/*    BINARY ARITHMATIC                                                     */
/* ======================================================================== */
case 0x80: {
	MODRM_DECODE();
	op8 = *(u8 *)pc;
	pc += 1;
/*do_op8:*/
	/* 80 /0 ib      ADD r/m8,imm8      Add imm8 to r/m8 */
	/* 80 /1 ib      OR r/m8,imm8       r/m8 OR imm8 */
	/* 80 /2 ib      ADC r/m8,imm8      Add with carry imm8 to r/m8 */
	/* 80 /3 ib      SBB r/m8,imm8      Subtract with borrow imm8 from r/m8 */
	/* 80 /4 ib      AND r/m8,imm8      r/m8 AND imm8 */
	/* 80 /5 ib      SUB r/m8,imm8      Subtract imm8 from r/m8 */
	/* 80 /6 ib      XOR r/m8,imm8      r/m8 XOR imm8 */
	/* 80 /7 ib      CMP r/m8,imm8      Compare imm8 with r/m8 */
	DO_ARITH_SWITCH_rmdst_mi_reg(b, B, 1, 8, op8)
	goto done;
}


case 0x81:
	MODRM_DECODE();
#if CONFIG_LIBEMU86_WANT_64BIT
	if (IS_64BIT()) {
		op64 = (u64)(s64)(s32)UNALIGNED_GET32((u32 *)pc);
		pc += 4;
do_op64:
		/* 81 /0 iq      ADD r/m64,Simm32      Add Simm32 to r/m64 */
		/* 81 /1 iq      OR r/m64,Simm32       r/m64 OR Simm32 */
		/* 81 /2 iq      ADC r/m64,Simm32      Add with carry Simm32 to r/m64 */
		/* 81 /3 iq      SBB r/m64,Simm32      Subtract with borrow Simm32 from r/m64 */
		/* 81 /4 iq      AND r/m64,Simm32      r/m64 AND Simm32 */
		/* 81 /5 iq      SUB r/m64,Simm32      Subtract Simm32 from r/m64 */
		/* 81 /6 iq      XOR r/m64,Simm32      r/m64 XOR Simm32 */
		/* 81 /7 iq      CMP r/m64,Simm32      Compare Simm32 with r/m64 */
		DO_ARITH_SWITCH_rmdst_mi_reg(q, Q, 8, 64, op64)
	} else
#endif /* CONFIG_LIBEMU86_WANT_64BIT */
	if (!IS_16BIT()) {
		op32 = UNALIGNED_GET32((u32 *)pc);
		pc += 4;
do_op32:
		/* 81 /0 id      ADD r/m32,imm32      Add imm32 to r/m32 */
		/* 81 /1 id      OR r/m32,imm32       r/m32 OR imm32 */
		/* 81 /2 id      ADC r/m32,imm32      Add with CF imm32 to r/m32 */
		/* 81 /3 id      SBB r/m32,imm32      Subtract with borrow imm32 from r/m32 */
		/* 81 /4 id      AND r/m32,imm32      r/m32 AND imm32 */
		/* 81 /5 id      SUB r/m32,imm32      Subtract imm32 from r/m32 */
		/* 81 /6 id      XOR r/m32,imm32      r/m32 XOR imm32 */
		/* 81 /7 id      CMP r/m32,imm32      Compare imm32 with r/m32 */
		DO_ARITH_SWITCH_rmdst_mi_reg(l, L, 4, 32, op32)
	} else {
		op16 = UNALIGNED_GET16((u16 *)pc);
		pc += 2;
do_op16:
		/* 81 /0 iw      ADD r/m16,imm16      Add imm16 to r/m16 */
		/* 81 /1 iw      OR r/m16,imm16       r/m16 OR imm16 */
		/* 81 /2 iw      ADC r/m16,imm16      Add with carry imm16 to r/m16 */
		/* 81 /3 iw      SBB r/m16,imm16      Subtract with borrow imm16 from r/m16 */
		/* 81 /4 iw      AND r/m16,imm16      r/m16 AND imm16 */
		/* 81 /5 iw      SUB r/m16,imm16      Subtract imm16 from r/m16 */
		/* 81 /6 iw      XOR r/m16,imm16      r/m16 XOR imm16 */
		/* 81 /7 iw      CMP r/m16,imm16      Compare imm16 with r/m16 */
		DO_ARITH_SWITCH_rmdst_mi_reg(w, W, 2, 16, op16)
	}
	goto done;

case 0x83:
	MODRM_DECODE();
#if CONFIG_LIBEMU86_WANT_64BIT
	if (IS_64BIT()) {
		/* 83 /0 ib      ADD r/m64,Simm8      Add sign-extended imm8 to r/m64 */
		/* 83 /1 ib      OR r/m64,Simm8       r/m64 OR imm8 (sign-extended) */
		/* 83 /2 ib      ADC r/m64,Simm8      Add with CF sign-extended imm8 into r/m64 */
		/* 83 /3 ib      SBB r/m64,Simm8      Subtract with borrow sign-extended imm8 from r/m64 */
		/* 83 /4 ib      AND r/m64,Simm8      r/m64 AND imm8 (sign-extended) */
		/* 83 /5 ib      SUB r/m64,Simm8      Subtract sign-extended imm8 from r/m64 */
		/* 83 /6 ib      XOR r/m64,Simm8      r/m64 XOR imm8 (sign-extended) */
		/* 83 /7 ib      CMP r/m64,Simm8      Compare imm8 with r/m64 */
		op64 = (u64)(s64)*(s8 *)pc;
		pc += 1;
		goto do_op64;
	} else
#endif /* CONFIG_LIBEMU86_WANT_64BIT */
	if (!IS_16BIT()) {
		/* 83 /0 ib      ADD r/m32,Simm8      Add sign-extended imm8 to r/m32 */
		/* 83 /1 ib      OR r/m32,Simm8       r/m32 OR imm8 (sign-extended) */
		/* 83 /2 ib      ADC r/m32,Simm8      Add with CF sign-extended imm8 into r/m32 */
		/* 83 /3 ib      SBB r/m32,Simm8      Subtract with borrow sign-extended imm8 from r/m32 */
		/* 83 /4 ib      AND r/m32,Simm8      r/m32 AND imm8 (sign-extended) */
		/* 83 /5 ib      SUB r/m32,Simm8      Subtract sign-extended imm8 from r/m32 */
		/* 83 /6 ib      XOR r/m32,Simm8      r/m32 XOR imm8 (sign-extended) */
		/* 83 /7 ib      CMP r/m32,Simm8      Compare imm8 with r/m32 */
		op32 = (u32)(s32)*(s8 *)pc;
		pc += 1;
		goto do_op32;
	} else {
		/* 83 /0 ib      ADD r/m16,Simm8      Add sign-extended imm8 to r/m16 */
		/* 83 /1 ib      OR r/m16,Simm8       r/m16 OR imm8 (sign-extended) */
		/* 83 /2 ib      ADC r/m16,Simm8      Add with CF sign-extended imm8 to r/m16 */
		/* 83 /3 ib      SBB r/m16,Simm8      Subtract with borrow sign-extended imm8 from r/m16 */
		/* 83 /4 ib      AND r/m16,Simm8      r/m16 AND imm8 (sign-extended) */
		/* 83 /5 ib      SUB r/m16,Simm8      Subtract sign-extended imm8 from r/m16 */
		/* 83 /6 ib      XOR r/m16,Simm8      r/m16 XOR imm8 (sign-extended) */
		/* 83 /7 ib      CMP r/m16,Simm8      Compare imm8 with r/m16 */
		op16 = (u16)(s16)*(s8 *)pc;
		pc += 1;
		goto do_op16;
	}
	goto done;


#define DEFINE_REGISTER_MEMORY_INSTRUCTIONS(_opcode, name, NAME)        \
	case _opcode + 0:                                                   \
		/* _opcode + 00 /r      FOO r/m8, r8        Foo r8 to r/m8 */   \
		MODRM_DECODE();                                                 \
		op8 = MODRM_GETREGB();                                          \
		goto do_##name##8;                                              \
		                                                                \
	case _opcode + 1:                                                   \
		/* _opcode + 01 /r      FOO r/m16, r16      Foo r16 to r/m16 */ \
		/* _opcode + 01 /r      FOO r/m32, r32      Foo r32 to r/m32 */ \
		/* _opcode + 01 /r      FOO r/m64, r64      Foo r64 to r/m64 */ \
		MODRM_DECODE();                                                 \
		IF_64BIT(if (IS_64BIT()) {                                      \
			op64 = MODRM_GETREGQ();                                     \
			goto do_##name##64;                                         \
		} else) if (!IS_16BIT()) {                                      \
			op32 = MODRM_GETREGL();                                     \
			goto do_##name##32;                                         \
		} else {                                                        \
			op16 = MODRM_GETREGW();                                     \
			goto do_##name##16;                                         \
		}                                                               \
		                                                                \
	case _opcode + 2:                                                   \
		/* _opcode + 02 /r      FOO r8, r/m8        Foo r/m8 to r8 */   \
		MODRM_DECODE();                                                 \
		op8 = MODRM_GETRMB();                                           \
		modrm.mi_type = EMU86_MODRM_REGISTER;                           \
		modrm.mi_rm   = modrm.mi_reg;                                   \
		goto do_##name##8;                                              \
		                                                                \
	case _opcode + 3:                                                   \
		/* _opcode + 03 /r      FOO r16, r/m16      Foo r/m16 to r16 */ \
		/* _opcode + 03 /r      FOO r32, r/m32      Foo r/m32 to r32 */ \
		/* _opcode + 03 /r      FOO r64, r/m64      Foo r/m64 to r64 */ \
		MODRM_DECODE();                                                 \
		IF_64BIT(if (IS_64BIT()) {                                      \
			op64 = MODRM_GETRMQ();                                      \
			modrm.mi_type = EMU86_MODRM_REGISTER;                       \
			modrm.mi_rm   = modrm.mi_reg;                               \
			goto do_##name##64;                                         \
		} else) if (!IS_16BIT()) {                                      \
			op32 = MODRM_GETRML();                                      \
			modrm.mi_type = EMU86_MODRM_REGISTER;                       \
			modrm.mi_rm   = modrm.mi_reg;                               \
			goto do_##name##32;                                         \
		} else {                                                        \
			op16 = MODRM_GETRMW();                                      \
			modrm.mi_type = EMU86_MODRM_REGISTER;                       \
			modrm.mi_rm   = modrm.mi_reg;                               \
			goto do_##name##16;                                         \
		}                                                               \


	/* 00 /r      ADD r/m8, r8        Add r8 to r/m8 */
	/* 01 /r      ADD r/m16, r16      Add r16 to r/m16 */
	/* 01 /r      ADD r/m32, r32      Add r32 to r/m32 */
	/* 02 /r      ADD r8, r/m8        Add r/m8 to r8 */
	/* 03 /r      ADD r16, r/m16      Add r/m16 to r16 */
	/* 03 /r      ADD r32, r/m32      Add r/m32 to r32 */
	DEFINE_REGISTER_MEMORY_INSTRUCTIONS(0x00, add, ADD)

	/* 08 /r      OR r/m8,r8        r/m8 OR r8 */
	/* 09 /r      OR r/m16,r16      r/m16 OR r16 */
	/* 09 /r      OR r/m32,r32      r/m32 OR r32 */
	/* 0A /r      OR r8,r/m8        r8 OR r/m8 */
	/* 0B /r      OR r16,r/m16      r16 OR r/m16 */
	/* 0B /r      OR r32,r/m32      r32 OR r/m32 */
	DEFINE_REGISTER_MEMORY_INSTRUCTIONS(0x08, or, OR)

	/* 10 /r      ADC r/m8, r8        Add with carry byte register to r/m8 */
	/* 11 /r      ADC r/m16, r16      Add with carry r16 to r/m16 */
	/* 11 /r      ADC r/m32, r32      Add with CF r32 to r/m32 */
	/* 12 /r      ADC r8, r/m8        Add with carry r/m8 to byte register */
	/* 13 /r      ADC r16, r/m16      Add with carry r/m16 to r16 */
	/* 13 /r      ADC r32, r/m32      Add with CF r/m32 to r32 */
	DEFINE_REGISTER_MEMORY_INSTRUCTIONS(0x10, adc, ADC)

	/* 18 /r      SBB r/m8,r8        Subtract with borrow r8 from r/m8 */
	/* 19 /r      SBB r/m16,r16      Subtract with borrow r16 from r/m16 */
	/* 19 /r      SBB r/m32,r32      Subtract with borrow r32 from r/m32 */
	/* 1A /r      SBB r8,r/m8        Subtract with borrow r/m8 from r8 */
	/* 1B /r      SBB r16,r/m16      Subtract with borrow r/m16 from r16 */
	/* 1B /r      SBB r32,r/m32      Subtract with borrow r/m32 from r32 */
	DEFINE_REGISTER_MEMORY_INSTRUCTIONS(0x18, sbb, SBB)

	/* 20 /r      AND r/m8, r8        r/m8 AND r8 */
	/* 21 /r      AND r/m16, r16      r/m16 AND r16 */
	/* 21 /r      AND r/m32, r32      r/m32 AND r32 */
	/* 22 /r      AND r8, r/m8        r8 AND r/m8 */
	/* 23 /r      AND r16, r/m16      r16 AND r/m16 */
	/* 23 /r      AND r32, r/m32      r32 AND r/m32 */
	DEFINE_REGISTER_MEMORY_INSTRUCTIONS(0x20, and, AND)

	/* 28 /r      SUB r/m8,r8        Subtract r8 from r/m8 */
	/* 29 /r      SUB r/m16,r16      Subtract r16 from r/m16 */
	/* 29 /r      SUB r/m32,r32      Subtract r32 from r/m32 */
	/* 2A /r      SUB r8,r/m8        Subtract r/m8 from r8 */
	/* 2B /r      SUB r16,r/m16      Subtract r/m16 from r16 */
	/* 2B /r      SUB r32,r/m32      Subtract r/m32 from r32 */
	DEFINE_REGISTER_MEMORY_INSTRUCTIONS(0x28, sub, SUB)

	/* 30 /r      XOR r/m8,r8        r/m8 XOR r8 */
	/* 31 /r      XOR r/m16,r16      r/m16 XOR r16 */
	/* 31 /r      XOR r/m32,r32      r/m32 XOR r32 */
	/* 32 /r      XOR r8,r/m8        r8 XOR r/m8 */
	/* 33 /r      XOR r16,r/m16      r16 XOR r/m16 */
	/* 33 /r      XOR r32,r/m32      r32 XOR r/m32 */
	DEFINE_REGISTER_MEMORY_INSTRUCTIONS(0x30, xor, XOR)

	/* 38 /r      CMP r/m8,r8        Compare r8 with r/m8 */
	/* 39 /r      CMP r/m16,r16      Compare r16 with r/m16 */
	/* 39 /r      CMP r/m32,r32      Compare r32 with r/m32 */
	/* 3A /r      CMP r8,r/m8        Compare r/m8 with r8 */
	/* 3B /r      CMP r16,r/m16      Compare r/m16 with r16 */
	/* 3B /r      CMP r32,r/m32      Compare r/m32 with r32 */
	DEFINE_REGISTER_MEMORY_INSTRUCTIONS(0x38, cmp, CMP)

#undef DEFINE_REGISTER_MEMORY_INSTRUCTIONS

}
EMU86_INTELLISENSE_END
