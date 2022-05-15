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
#ifdef __INTELLISENSE__
#include "../emulate.c.inl"
#endif /* __INTELLISENSE__ */

EMU86_INTELLISENSE_BEGIN(mov_imm) {


#if EMU86_EMULATE_CONFIG_WANT_MOV_IMM || EMU86_EMULATE_CONFIG_WANT_XABORT
case EMU86_OPCODE_ENCODE(0xc6):
	MODRM_DECODE();
	switch (modrm.mi_reg) {

#if EMU86_EMULATE_CONFIG_WANT_MOV_IMM
	case 0: {
		/* C6 /0      MOV r/m8,imm8      Move imm8 to r/m8 */
		u8 value;
		value = *(u8 const *)pc;
		pc += 1;
		MODRM_SETRMB(value);
		goto done;
	}
#elif EMU86_EMULATE_CONFIG_CHECKERROR
	case 0:
		goto notsup_modrm_setb_rmreg_modrm_parsed;
#define NEED_notsup_modrm_setb_rmreg_modrm_parsed
#endif /* ... */


#if EMU86_EMULATE_CONFIG_WANT_XABORT
	case 7: {
		/* C6 F8 ib     XABORT imm8     Causes an RTM abort if in RTM execution */
		if (!EMU86_MODRM_ISREG(modrm.mi_type))
			goto return_expected_register_modrm;
#define NEED_return_expected_register_modrm
		if (modrm.mi_rm != 0)
			goto return_unknown_instruction_rmreg;
#define NEED_return_unknown_instruction_rmreg

		/* Check if we're inside of an RTM region */
#undef EMU86_EMULATE_XTEST_NO_FALLBACK_BRANCH
#ifndef EMU86_EMULATE_XTEST_IS_ZERO
#ifdef EMU86_EMULATE_RETURN_AFTER_XABORT
#ifdef EMU86_EMULATE_XTEST_IS_ONE
#define EMU86_EMULATE_XTEST_NO_FALLBACK_BRANCH
#else /* EMU86_EMULATE_XTEST_IS_ONE */
		if (EMU86_EMULATE_XTEST())
#endif /* !EMU86_EMULATE_XTEST_IS_ONE */
		{
			u8 code = *(u8 const *)pc;
			EMU86_EMULATE_RETURN_AFTER_XABORT(code);
			__builtin_unreachable();
		}
#endif /* EMU86_EMULATE_RETURN_AFTER_XABORT */
#endif /* !EMU86_EMULATE_XTEST_IS_ZERO */
#ifndef EMU86_EMULATE_XTEST_NO_FALLBACK_BRANCH
		pc += 1; /* imm8 */
		/* Since we emulate transactions by always choosing the fallback-branch,
		 * we must emulate this instruction as  a no-op, since that's what  it's
		 * supposed to behave as whenever not inside of a transaction. */
		goto done;
#else /* !EMU86_EMULATE_XTEST_HAVE_FALLBACK_BRANCH */
#undef EMU86_EMULATE_XTEST_NO_FALLBACK_BRANCH
#endif /* EMU86_EMULATE_XTEST_HAVE_FALLBACK_BRANCH */
	}
#elif EMU86_EMULATE_CONFIG_CHECKERROR
	case 7:
		if (!EMU86_MODRM_ISREG(modrm.mi_type))
			goto return_expected_register_modrm;
#define NEED_return_expected_register_modrm
		if (modrm.mi_rm != 0)
			goto return_unknown_instruction_rmreg;
#define NEED_return_unknown_instruction_rmreg
		goto return_unsupported_instruction_rmreg;
#define NEED_return_unsupported_instruction_rmreg
#endif /* ... */


	default:
#define NEED_return_unknown_instruction_rmreg
		goto return_unknown_instruction_rmreg;
	}
	break;
#elif EMU86_EMULATE_CONFIG_CHECKERROR
case EMU86_OPCODE_ENCODE(0xc6):
	MODRM_DECODE();
	switch (modrm.mi_reg) {
	case 0:
		goto notsup_modrm_setb_rmreg_modrm_parsed;
#define NEED_notsup_modrm_setb_rmreg_modrm_parsed

	case 7:
		if (!EMU86_MODRM_ISREG(modrm.mi_type))
			goto return_expected_register_modrm;
#define NEED_return_expected_register_modrm
		if (modrm.mi_rm != 0)
			goto return_unknown_instruction_rmreg;
#define NEED_return_unknown_instruction_rmreg
		goto return_unsupported_instruction_rmreg;
#define NEED_return_unsupported_instruction_rmreg

	default:
		goto return_unknown_instruction_rmreg;
#define NEED_return_unknown_instruction_rmreg
	}
#endif /* ... */



#if EMU86_EMULATE_CONFIG_WANT_MOV_IMM || EMU86_EMULATE_CONFIG_WANT_XBEGIN
case EMU86_OPCODE_ENCODE(0xc7):
	MODRM_DECODE();
	switch (modrm.mi_reg) {

#if EMU86_EMULATE_CONFIG_WANT_MOV_IMM
	case 0: {
		s32 value;
		/* C7 /0      MOV r/m16,imm16      Move imm16 to r/m16 */
		/* C7 /0      MOV r/m32,imm32      Move imm32 to r/m32 */
		if (!IS_16BIT()) {
			value = (s32)UNALIGNED_GETLE32((u32 const *)pc);
			pc += 4;
		} else {
			value = (s32)(u32)UNALIGNED_GETLE16((u16 const *)pc);
			pc += 2;
		}
		IF_64BIT(if (IS_64BIT()) {
			MODRM_SETRMQ((u64)(s64)value);
		} else) if (!IS_16BIT()) {
			MODRM_SETRML((u32)value);
		} else {
			MODRM_SETRMW((u16)value);
		}
		goto done;
	}
#elif EMU86_EMULATE_CONFIG_CHECKERROR
	case 0:
		goto notsup_modrm_setwlq_rmreg_modrm_parsed;
#define NEED_notsup_modrm_setwlq_rmreg_modrm_parsed
#endif /* ... */


#if EMU86_EMULATE_CONFIG_WANT_XBEGIN
	case 7: {
		/* C7 F8 XBEGIN rel16     Specifies the start of an RTM region. Provides a 16-bit relative offset to compute the address of the fallback instruction address at which execution resumes following an RTM abort.
		 * C7 F8 XBEGIN rel32     Specifies the start of an RTM region. Provides a 32-bit relative offset to compute the address of the fallback instruction address at which execution resumes following an RTM abort. */
		s32 offset;
		if (!EMU86_MODRM_ISREG(modrm.mi_type))
			goto return_expected_register_modrm;
#define NEED_return_expected_register_modrm
		if (modrm.mi_rm != 0)
			goto return_unknown_instruction_rmreg;
#define NEED_return_unknown_instruction_rmreg
		if (op_flags & EMU86_F_66) {
			offset = (s32)(s16)UNALIGNED_GETLE16((u16 const *)pc);
			pc += 2;
		} else {
			offset = (s32)UNALIGNED_GETLE32((u32 const *)pc);
			pc += 4;
		}
		(void)offset;
#ifdef EMU86_EMULATE_RETURN_AFTER_XBEGIN
		/* Set the instruction to the start of RTM execution. */
		EMU86_SETPCPTR(REAL_IP());
		EMU86_EMULATE_RETURN_AFTER_XBEGIN(REAL_IP() + offset);
		__builtin_unreachable();
#else /* EMU86_EMULATE_RETURN_AFTER_XBEGIN */
		/* We  don't  actually   implement  proper  transaction   support.
		 * Instead,  what  we do  is  behave like  an  implementation that
		 * doesn't have support for any kind of transactional instruction,
		 * such that we immediately branch to the fallback branch,  whilst
		 * also clearing %eax to `_XABORT_FAILED' */
		EMU86_SETIPREG(REAL_IP() + offset);
		EMU86_SETEAX(_XABORT_FAILED);
		goto done_dont_set_pc;
#define NEED_done_dont_set_pc
#endif /* !EMU86_EMULATE_RETURN_AFTER_XBEGIN */
	}
#elif EMU86_EMULATE_CONFIG_CHECKERROR
	case 7:
		if (!EMU86_MODRM_ISREG(modrm.mi_type))
			goto return_expected_register_modrm;
#define NEED_return_expected_register_modrm
		if (modrm.mi_rm != 0)
			goto return_unknown_instruction_rmreg;
#define NEED_return_unknown_instruction_rmreg
		goto return_unsupported_instruction_rmreg;
#define NEED_return_unsupported_instruction_rmreg
#endif /* ... */


	default:
#define NEED_return_unknown_instruction_rmreg
		goto return_unknown_instruction_rmreg;
	}
	break;
#elif EMU86_EMULATE_CONFIG_CHECKERROR
case EMU86_OPCODE_ENCODE(0xc7):
	MODRM_DECODE();
	switch (modrm.mi_reg) {
	case 0:
		goto notsup_modrm_setwlq_rmreg_modrm_parsed;
#define NEED_notsup_modrm_setwlq_rmreg_modrm_parsed

	case 7:
		if (!EMU86_MODRM_ISREG(modrm.mi_type))
			goto return_expected_register_modrm;
#define NEED_return_expected_register_modrm
		if (modrm.mi_rm != 0)
			goto return_unknown_instruction_rmreg;
#define NEED_return_unknown_instruction_rmreg
		goto return_unsupported_instruction_rmreg;
#define NEED_return_unsupported_instruction_rmreg

	default:
		goto return_unknown_instruction_rmreg;
#define NEED_return_unknown_instruction_rmreg
	}
#endif /* ... */



#if !EMU86_EMULATE_CONFIG_ONLY_MEMORY
#if EMU86_EMULATE_CONFIG_WANT_MOV_IMM
case EMU86_OPCODE_ENCODE(0xb0) ... EMU86_OPCODE_ENCODE(0xb7): {
	u8 value;
	u8 regno = tiny_opcode - EMU86_OPCODE_ENCODE(0xb0);
#if CONFIG_LIBEMU86_WANT_64BIT
	if (op_flags & EMU86_F_REX_B)
		regno |= 0x8;
#endif /* CONFIG_LIBEMU86_WANT_64BIT */
	/* B0+ rb ib    MOV r8, imm8      OI     Valid     Valid     Move imm8 to r8. */
	value = *pc;
	++pc;
	EMU86_SETREGB(regno, value, op_flags);
	goto done;
}
#elif EMU86_EMULATE_CONFIG_CHECKERROR && !EMU86_EMULATE_CONFIG_ONLY_CHECKERROR_NO_BASIC
case EMU86_OPCODE_ENCODE(0xb0) ... EMU86_OPCODE_ENCODE(0xb7):
	goto return_unsupported_instruction;
#define NEED_return_unsupported_instruction
#endif /* ... */


#if EMU86_EMULATE_CONFIG_WANT_MOV_IMM
case EMU86_OPCODE_ENCODE(0xb8) ... EMU86_OPCODE_ENCODE(0xbf): {
	/*         B8+ rw iw    MOV r16, imm16   OI   Valid    Valid    Move imm16 to r16.
	 *         B8+ rd id    MOV r32, imm32   OI   Valid    Valid    Move imm32 to r32.
	 * REX.W + B8+ rd io    MOV r64, imm64   OI   Valid    N.E.     Move imm64 to r64. */
	u8 regno = tiny_opcode - EMU86_OPCODE_ENCODE(0xb8);
#if CONFIG_LIBEMU86_WANT_64BIT
	if (op_flags & EMU86_F_REX_B)
		regno |= 0x8;
#endif /* CONFIG_LIBEMU86_WANT_64BIT */
	IF_64BIT(if (IS_64BIT()) {
		u64 value;
		value = UNALIGNED_GETLE64((u64 const *)pc);
		pc += 8;
		EMU86_SETREGQ(regno, value);
	} else) if (!IS_16BIT()) {
		u32 value;
		value = UNALIGNED_GETLE32((u32 const *)pc);
		pc += 4;
		EMU86_SETREGL(regno, value);
	} else {
		u16 value;
		value = UNALIGNED_GETLE16((u16 const *)pc);
		pc += 2;
		EMU86_SETREGW(regno, value);
	}
	goto done;
}
#elif EMU86_EMULATE_CONFIG_CHECKERROR && !EMU86_EMULATE_CONFIG_ONLY_CHECKERROR_NO_BASIC
case EMU86_OPCODE_ENCODE(0xb8) ... EMU86_OPCODE_ENCODE(0xbf):
	goto return_unsupported_instruction;
#define NEED_return_unsupported_instruction
#endif /* ... */
#endif /* !EMU86_EMULATE_CONFIG_ONLY_MEMORY */



}
EMU86_INTELLISENSE_END
