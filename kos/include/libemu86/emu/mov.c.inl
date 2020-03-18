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

EMU86_INTELLISENSE_BEGIN(mov) {

case 0x88: {
	/* 88 /r      MOV r/m8,r8      Move r8 to r/m8 */
	u8 value;
	MODRM_DECODE();
	MODRM_EMU86_ACCESS_MEMORY(1);
	value = MODRM_GETREGB();
	MODRM_SETRMB(value);
	goto done;
}


case 0x89: {
	/* 89 /r      MOV r/m16,r16      Move r16 to r/m16 */
	/* 89 /r      MOV r/m32,r32      Move r32 to r/m32 */
	/* 89 /r      MOV r/m64,r64      Move r64 to r/m64 */
	MODRM_DECODE();
	IF_64BIT(if (IS_64BIT()) {
		u64 value;
		MODRM_EMU86_ACCESS_MEMORY(8);
		value = MODRM_GETREGQ();
		MODRM_SETRMQ(value);
	} else) if (!IS_16BIT()) {
		u32 value;
		MODRM_EMU86_ACCESS_MEMORY(4);
		value = MODRM_GETREGL();
		MODRM_SETRML(value);
	} else {
		u16 value;
		MODRM_EMU86_ACCESS_MEMORY(2);
		value = MODRM_GETREGW();
		MODRM_SETRMW(value);
	}
	goto done;
}


case 0x8a: {
	/* 8A /r      MOV r8,r/m8      Move r/m8 to r8 */
	u8 value;
	MODRM_DECODE();
	MODRM_EMU86_ACCESS_MEMORY(1);
	value = MODRM_GETRMB();
	MODRM_SETREGB(value);
	goto done;
}


case 0x8b: {
	/* 8b /r      MOV r16,r/m16      Move r/m16 to r16 */
	/* 8b /r      MOV r32,r/m32      Move r/m32 to r32 */
	/* 8b /r      MOV r64,r/m64      Move r/m64 to r64 */
	MODRM_DECODE();
	IF_64BIT(if (IS_64BIT()) {
		u64 value;
		MODRM_EMU86_ACCESS_MEMORY(8);
		value = MODRM_GETRMQ();
		MODRM_SETREGQ(value);
	} else) if (!IS_16BIT()) {
		u32 value;
		MODRM_EMU86_ACCESS_MEMORY(4);
		value = MODRM_GETRML();
		MODRM_SETREGL(value);
	} else {
		u16 value;
		MODRM_EMU86_ACCESS_MEMORY(2);
		value = MODRM_GETRMW();
		MODRM_SETREGW(value);
	}
	goto done;
}


case 0x8c: {
	u16 segment;
	/*         8C /r     MOV r/m16,Sreg**           MR  Valid Valid Move segment register to r/m16.
	 * REX.W + 8C /r     MOV r16/r32/m16, Sreg**    MR  Valid Valid Move zero extended 16-bit segment register to r16/r32/r64/m16.
	 * REX.W + 8C /r     MOV r64/m16, Sreg**        MR  Valid Valid Move zero extended 16-bit segment register to r64/m16. */
	MODRM_DECODE();
	if (modrm.mi_reg >= 6)
		goto return_unknown_instruction;
	segment = EMU86_GETSEG(modrm.mi_reg);
	IF_64BIT(if (IS_64BIT()) {
		MODRM_EMU86_ACCESS_MEMORY(8);
		MODRM_SETREGQ(segment);
	} else) if (!IS_16BIT()) {
		MODRM_EMU86_ACCESS_MEMORY(4);
		MODRM_SETREGL(segment);
	} else {
		MODRM_EMU86_ACCESS_MEMORY(2);
		MODRM_SETREGW(segment);
	}
	goto done;
}


case 0x8e: {
	u16 segment;
	/*         8E /r      MOV Sreg,r/m16** RM Valid Valid Move r/m16 to segment register.
	 * REX.W + 8E /r      MOV Sreg,r/m64** RM Valid Valid Move lower 16 bits of r/m64 to segment register. */
	MODRM_DECODE();
	if unlikely(modrm.mi_reg >= 6)
		goto return_unknown_instruction;
	MODRM_EMU86_ACCESS_MEMORY(2);
	segment = MODRM_GETREGW();
#if EMU86_EMULATE_CHECKUSER && (CONFIG_LIBEMU86_WANT_32BIT || CONFIG_LIBEMU86_WANT_64BIT)
	if ((modrm.mi_reg == EMU86_R_CS ? !SEGMENT_IS_VALID_USERCODE(segment)
	                                : !SEGMENT_IS_VALID_USERDATA(segment)) &&
	    EMU86_ISUSER_NOVM86()) {
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_SIGRETURN_REGISTER,
		      X86_REGISTER_SEGMENT_ES + modrm.mi_reg,
		      segment);
	}
#endif /* EMU86_EMULATE_CHECKUSER && (CONFIG_LIBEMU86_WANT_32BIT || CONFIG_LIBEMU86_WANT_64BIT) */
	EMU86_SETSEG(modrm.mi_reg, segment);
	goto done;
}


case 0xa0: {
	/* A0      MOV AL,moffs8*      Move byte at (seg:offset) to AL */
	byte_t *addr;
	u32 offset;
	u8 value;
	if (op_flags & EMU86_F_AD16) {
		offset = UNALIGNED_GET16((u16 *)pc);
		pc += 2;
	} else {
		offset = UNALIGNED_GET32((u32 *)pc);
		pc += 4;
	}
	addr = SEGMENT_ADDR(offset);
	EMU86_READ_USER_MEMORY(addr, 1);
	value = EMU86_EMULATE_READB(addr);
	EMU86_SETAL(value);
	goto done;
}

case 0xa1: {
	/* A1      MOV AX,moffs16*      Move word at (seg:offset) to AX */
	/* A1      MOV EAX,moffs32*     Move doubleword at (seg:offset) to EAX */
	/* A1      MOV RAX,moffs32*     Move quadword at (seg:offset) to RAX */
	byte_t *addr;
	u32 offset;
	if (op_flags & EMU86_F_AD16) {
		offset = UNALIGNED_GET16((u16 *)pc);
		pc += 2;
	} else {
		offset = UNALIGNED_GET32((u32 *)pc);
		pc += 4;
	}
	addr = SEGMENT_ADDR(offset);
	IF_64BIT(if (IS_64BIT()) {
		u64 value;
		EMU86_READ_USER_MEMORY(addr, 8);
		value = EMU86_EMULATE_READQ(addr);
		EMU86_SETRAX(value);
	} else) if (!IS_16BIT()) {
		u32 value;
		EMU86_READ_USER_MEMORY(addr, 4);
		value = EMU86_EMULATE_READL(addr);
		EMU86_SETEAX(value);
	} else {
		u16 value;
		EMU86_READ_USER_MEMORY(addr, 2);
		value = EMU86_EMULATE_READW(addr);
		EMU86_SETAX(value);
	}
	goto done;
}


case 0xa2: {
	/* A2      MOV moffs8*,AL      Move AL to (seg:offset) */
	byte_t *addr;
	u32 offset;
	u8 value;
	if (op_flags & EMU86_F_AD16) {
		offset = UNALIGNED_GET16((u16 *)pc);
		pc += 2;
	} else {
		offset = UNALIGNED_GET32((u32 *)pc);
		pc += 4;
	}
	addr = SEGMENT_ADDR(offset);
	EMU86_WRITE_USER_MEMORY(addr, 1);
	value = EMU86_GETAL();
	EMU86_EMULATE_WRITEB(addr, value);
	goto done;
}


case 0xa3: {
	/* A3      MOV moffs16*,AX      Move AX to word at (seg:offset) */
	/* A3      MOV moffs32*,EAX     Move EAX to doubleword at (seg:offset) */
	/* A3      MOV moffs64*,RAX     Move RAX to quadword at (seg:offset) */
	byte_t *addr;
	u32 offset;
	if (op_flags & EMU86_F_AD16) {
		offset = UNALIGNED_GET16((u16 *)pc);
		pc += 2;
	} else {
		offset = UNALIGNED_GET32((u32 *)pc);
		pc += 4;
	}
	addr = SEGMENT_ADDR(offset);
	IF_64BIT(if (IS_64BIT()) {
		u64 value;
		EMU86_WRITE_USER_MEMORY(addr, 8);
		value = EMU86_GETRAX();
		EMU86_EMULATE_WRITEQ(addr, value);
	} else) if (!IS_16BIT()) {
		u32 value;
		EMU86_WRITE_USER_MEMORY(addr, 4);
		value = EMU86_GETEAX();
		EMU86_EMULATE_WRITEL(addr, value);
	} else {
		u16 value;
		EMU86_WRITE_USER_MEMORY(addr, 2);
		value = EMU86_GETAX();
		EMU86_EMULATE_WRITEW(addr, value);
	}
	goto done;
}



case 0xc6:
	MODRM_DECODE();
	switch (modrm.mi_reg) {

	case 0: {
		/* C6 /0      MOV r/m8,imm8      Move imm8 to r/m8 */
		u8 value;
		MODRM_EMU86_ACCESS_MEMORY(1);
		value = *(u8 *)pc;
		pc += 1;
		MODRM_SETRMB(value);
	}	break;

	default:
		goto return_unknown_instruction;
	}
	goto done;



case 0xc7:
	MODRM_DECODE();
	switch (modrm.mi_reg) {

	case 0: {
		s32 value;
		/* C7 /0      MOV r/m16,imm16      Move imm16 to r/m16 */
		/* C7 /0      MOV r/m32,imm32      Move imm32 to r/m32 */
		if (!IS_16BIT()) {
			value = (s32)(u32)UNALIGNED_GET16((u16 *)pc);
			pc += 2;
		} else {
			value = (s32)UNALIGNED_GET32((u32 *)pc);
			pc += 4;
		}
		IF_64BIT(if (IS_64BIT()) {
			MODRM_EMU86_ACCESS_MEMORY(8);
			MODRM_SETRMQ((u64)(s64)value);
		} else) if (!IS_16BIT()) {
			MODRM_EMU86_ACCESS_MEMORY(4);
			MODRM_SETRML((u32)value);
		} else {
			MODRM_EMU86_ACCESS_MEMORY(2);
			MODRM_SETRMW((u16)value);
		}
		goto done;
	}	break;

	default:
		goto return_unknown_instruction;
	}
	break;


case 0x0fb6: {
	u8 value;
	/*         0F B6 /r     MOVZX r16, r/m8     Move byte to word with zero-extension.
	 *         0F B6 /r     MOVZX r32, r/m8     Move byte to doubleword, zero-extension.
	 * REX.W + 0F B6 /r     MOVZX r64, r/m8*    Move byte to quadword, zero-extension. */
	MODRM_DECODE();
	MODRM_EMU86_ACCESS_MEMORY(1);
	value = MODRM_GETRMB();
	IF_64BIT(if (IS_64BIT()) {
		MODRM_SETREGQ((u64)value);
	} else) if (!IS_16BIT()) {
		MODRM_SETREGL((u32)value);
	} else {
		MODRM_SETREGW((u16)value);
	}
	goto done;
}


case 0x0fb7: {
	u16 value;
	/*         0F B7 /r     MOVZX r32, r/m16    Move word to doubleword, zero-extension.
	 * REX.W + 0F B7 /r     MOVZX r64, r/m16    Move word to quadword, zero-extension. */
	MODRM_DECODE();
	MODRM_EMU86_ACCESS_MEMORY(2);
	value = MODRM_GETRMW();
	IF_64BIT(if (IS_64BIT()) {
		MODRM_SETREGQ((u64)value);
	} else) {
		MODRM_SETREGL((u32)value);
	}
	goto done;
}


case 0x0fbe: {
	s8 value;
	/*         0F B6 /r     MOVSX r16, r/m8     Move byte to word with sign-extension.
	 *         0F B6 /r     MOVSX r32, r/m8     Move byte to doubleword, sign-extension.
	 * REX.W + 0F B6 /r     MOVSX r64, r/m8*    Move byte to quadword, sign-extension. */
	MODRM_DECODE();
	MODRM_EMU86_ACCESS_MEMORY(1);
	value = (s8)MODRM_GETRMB();
	IF_64BIT(if (IS_64BIT()) {
		MODRM_SETREGQ((u64)(s64)value);
	} else) if (!IS_16BIT()) {
		MODRM_SETREGL((u32)(s32)value);
	} else {
		MODRM_SETREGW((u16)(s16)value);
	}
	goto done;
}


case 0x0fbf: {
	s16 value;
	/*         0F B7 /r     MOVSX r32, r/m16    Move word to doubleword, sign-extension.
	 * REX.W + 0F B7 /r     MOVSX r64, r/m16    Move word to quadword, sign-extension. */
	MODRM_DECODE();
	MODRM_EMU86_ACCESS_MEMORY(2);
	value = (s16)MODRM_GETRMW();
	IF_64BIT(if (IS_64BIT()) {
		MODRM_SETREGQ((u64)(s64)value);
	} else) {
		MODRM_SETREGL((u32)(s32)value);
	}
	goto done;
}


case 0x63: {
	/*         63 /r*       MOVSXD r16, r/m16   Move word to word with sign-extension.
	 *         63 /r*       MOVSXD r32, r/m32   Move doubleword to doubleword with sign-extension.
	 * REX.W + 63 /r        MOVSXD r64, r/m32   Move doubleword to quadword with sign-extension. */
	MODRM_DECODE();
	IF_64BIT(if (IS_64BIT()) {
		s32 value;
		MODRM_EMU86_ACCESS_MEMORY(4);
		value = (s32)MODRM_GETRML();
		MODRM_SETREGQ((u64)(s64)value);
	} else) if (!IS_16BIT()) {
		MODRM_EMU86_ACCESS_MEMORY(4);
		MODRM_SETREGL(MODRM_GETRML());
	} else {
		MODRM_EMU86_ACCESS_MEMORY(2);
		MODRM_SETREGW(MODRM_GETRMW());
	}
	goto done;
}



#ifndef EMU86_EMULATE_ONLY_MEMORY
case 0xb0 ... 0xb7: {
	u8 value;
	/* B0+ rb ib    MOV r8, imm8      OI     Valid     Valid     Move imm8 to r8. */
	value = *pc;
	++pc;
	EMU86_SETREGB(opcode - 0xb0, value, op_flags);
	goto done;
}


case 0xb8 ... 0xbf: {
	/*         B8+ rw iw    MOV r16, imm16   OI   Valid    Valid    Move imm16 to r16.
	 *         B8+ rd id    MOV r32, imm32   OI   Valid    Valid    Move imm32 to r32.
	 * REX.W + B8+ rd io    MOV r64, imm64   OI   Valid    N.E.     Move imm64 to r64. */
	IF_64BIT(if (IS_64BIT()) {
		u64 value;
		value = UNALIGNED_GET64((u64 *)pc);
		pc += 8;
		EMU86_SETREGQ(opcode - 0xb8, value);
	} else) if (!IS_16BIT()) {
		u32 value;
		value = UNALIGNED_GET32((u32 *)pc);
		pc += 4;
		EMU86_SETREGL(opcode - 0xb8, value);
	} else {
		u16 value;
		value = UNALIGNED_GET16((u16 *)pc);
		pc += 2;
		EMU86_SETREGW(opcode - 0xb8, value);
	}
	goto done;
}
#endif /* !EMU86_EMULATE_ONLY_MEMORY */



}
EMU86_INTELLISENSE_END
