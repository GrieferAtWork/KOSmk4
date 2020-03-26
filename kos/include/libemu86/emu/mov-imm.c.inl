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

EMU86_INTELLISENSE_BEGIN(mov_imm) {


#if EMU86_EMULATE_CONFIG_WANT_MOV_IMM
case EMU86_OPCODE_ENCODE(0xc6):
	MODRM_DECODE();
	switch (modrm.mi_reg) {

	case 0: {
		/* C6 /0      MOV r/m8,imm8      Move imm8 to r/m8 */
		u8 value;
		value = *(u8 *)pc;
		pc += 1;
		MODRM_SETRMB(value);
		goto done;
	}

	default:
#define NEED_return_unknown_instruction_rmreg
		goto return_unknown_instruction_rmreg;
	}
	break;
#elif EMU86_EMULATE_CONFIG_CHECKERROR
case EMU86_OPCODE_ENCODE(0xc6):
	goto notsup_modrm_setb_rmreg;
#define NEED_notsup_modrm_setb_rmreg
#endif /* ... */



#if EMU86_EMULATE_CONFIG_WANT_MOV_IMM
case EMU86_OPCODE_ENCODE(0xc7):
	MODRM_DECODE();
	switch (modrm.mi_reg) {

	case 0: {
		s32 value;
		/* C7 /0      MOV r/m16,imm16      Move imm16 to r/m16 */
		/* C7 /0      MOV r/m32,imm32      Move imm32 to r/m32 */
		if (!IS_16BIT()) {
			value = (s32)UNALIGNED_GET32((u32 *)pc);
			pc += 4;
		} else {
			value = (s32)(u32)UNALIGNED_GET16((u16 *)pc);
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

	default:
#define NEED_return_unknown_instruction_rmreg
		goto return_unknown_instruction_rmreg;
	}
	break;
#elif EMU86_EMULATE_CONFIG_CHECKERROR
case EMU86_OPCODE_ENCODE(0xc7):
	goto notsup_modrm_setwlq_rmreg;
#define NEED_notsup_modrm_setwlq_rmreg
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
		value = UNALIGNED_GET64((u64 *)pc);
		pc += 8;
		EMU86_SETREGQ(regno, value);
	} else) if (!IS_16BIT()) {
		u32 value;
		value = UNALIGNED_GET32((u32 *)pc);
		pc += 4;
		EMU86_SETREGL(regno, value);
	} else {
		u16 value;
		value = UNALIGNED_GET16((u16 *)pc);
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
