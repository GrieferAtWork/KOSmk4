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

EMU86_INTELLISENSE_BEGIN(calljmp) {



#if CONFIG_LIBEMU86_WANT_16BIT || CONFIG_LIBEMU86_WANT_32BIT
case 0x9a: {
	/* 9A cd    CALL ptr16:16    Call far, absolute, address given in operand.
	 * 9A cp    CALL ptr16:32    Call far, absolute, address given in operand. */
	byte_t *sp;
	u32 offset;
	u16 segment;
	IF_64BIT({
		if (EMU86_F_IS64(op_flags))
			goto return_unknown_instruction;
	});
	if (!IS_16BIT()) {
		offset = UNALIGNED_GET32((u32 *)pc);
		pc += 4;
	} else {
		offset = UNALIGNED_GET16((u16 *)pc);
		pc += 2;
	}
	segment = UNALIGNED_GET16((u16 *)pc);
	pc += 2;
	/* Verify the segment index. */
#if EMU86_EMULATE_CHECKUSER
	if (!SEGMENT_IS_VALID_USERCODE(segment) && EMU86_ISUSER_NOVM86()) {
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_SIGRETURN_REGISTER,
		      X86_REGISTER_SEGMENT_CS, segment);
	}
#endif /* EMU86_EMULATE_CHECKUSER */
	sp = (byte_t *)EMU86_GETSP();
	if (!IS_16BIT()) {
		sp -= 8;
		EMU86_EMULATE_PUSH(sp, 8);
		EMU86_WRITE_USER_MEMORY(sp, 8);
		EMU86_EMULATE_WRITEL(sp + 4, (u32)EMU86_GETCS());
		EMU86_EMULATE_WRITEL(sp + 0, (u32)REAL_PC());
	} else {
		sp -= 4;
		EMU86_EMULATE_PUSH(sp, 4);
		EMU86_WRITE_USER_MEMORY(sp, 4);
		EMU86_EMULATE_WRITEW(sp + 2, (u16)EMU86_GETCS());
		EMU86_EMULATE_WRITEW(sp + 0, (u16)REAL_PC());
	}
	EMU86_SETSP(sp);
	EMU86_SETCS(segment);
	EMU86_EMULATE_SETIP(offset);
	goto done_dont_set_pc;
}
#endif /* CONFIG_LIBEMU86_WANT_16BIT || CONFIG_LIBEMU86_WANT_32BIT */



case 0xe8: {
	/* E8 cw    CALL rel16   Call near, relative, displacement relative to next instruction.
	 * E8 cd    CALL rel32   Call near, relative, displacement relative to next instruction.
	 *                       32-bit displacement sign extended to 64-bits in 64-bit mode. */
	s32 offset;
	byte_t const *dest_pc;
	byte_t *sp = (byte_t *)EMU86_GETSP();
	IF_16BIT_OR_32BIT(
	if (IS_16BIT() && !EMU86_F_IS64(op_flags)) {
		offset = (s32)(s16)UNALIGNED_GET16((u16 *)pc);
		pc += 2;
	} else) {
		offset = (s32)UNALIGNED_GET32((u32 *)pc);
		pc += 4;
	}
	dest_pc = pc + offset;
	/* Push the previous PC */
#if CONFIG_LIBEMU86_WANT_64BIT
	IF_16BIT_OR_32BIT(if (EMU86_F_IS64(op_flags))) {
		/* 64-bit mode */
		sp -= 8;
		EMU86_EMULATE_PUSH(sp, 8);
		EMU86_WRITE_USER_MEMORY(sp, 8);
		EMU86_EMULATE_WRITEQ(sp, (u64)REAL_PC());
	}
	IF_16BIT_OR_32BIT(else)
#endif /* CONFIG_LIBEMU86_WANT_64BIT */
#if CONFIG_LIBEMU86_WANT_16BIT || CONFIG_LIBEMU86_WANT_32BIT
	{
		/* 16/32-bit mode */
		if (!IS_16BIT()) {
			sp -= 4;
			EMU86_EMULATE_PUSH(sp, 4);
			EMU86_WRITE_USER_MEMORY(sp, 4);
			EMU86_EMULATE_WRITEL(sp, (u32)REAL_PC());
		} else {
			sp -= 2;
			EMU86_EMULATE_PUSH(sp, 2);
			EMU86_WRITE_USER_MEMORY(sp, 2);
			EMU86_EMULATE_WRITEW(sp, (u16)REAL_PC());
			/* Truncate to 16 bits. */
			dest_pc = (byte_t *)((uintptr_t)dest_pc & 0xffff);
		}
	}
#endif /* CONFIG_LIBEMU86_WANT_16BIT || CONFIG_LIBEMU86_WANT_32BIT */
	EMU86_EMULATE_SETPC(dest_pc);
	EMU86_SETSP(sp);
	goto done_dont_set_pc;
}



#ifndef EMU86_EMULATE_ONLY_MEMORY
case 0xe9: {
	/* E9 cw    JMP rel16   Jump near, relative, displacement relative to next instruction.
	 * E9 cd    JMP rel32   Jump near, relative, displacement relative to next instruction.
	 *                      32-bit displacement sign extended to 64-bits in 64-bit mode. */
	byte_t const *dest_pc;
	IF_16BIT_OR_32BIT(
	if (IS_16BIT() && !EMU86_F_IS64(op_flags)) {
		s16 offset;
		offset = (s16)UNALIGNED_GET16((u16 *)pc);
		pc += 2;
		dest_pc = (byte_t *)((uintptr_t)(pc + offset) & 0xffff);
	} else) {
		s32 offset;
		offset = (s32)UNALIGNED_GET32((u32 *)pc);
		pc += 4;
		dest_pc = pc + offset;
	}
	EMU86_EMULATE_SETPC(dest_pc);
	goto done_dont_set_pc;
}

case 0xeb: {
	/* EB cw    JMP rel8    Jump near, relative, displacement relative to next instruction. */
	s8 offset;
	byte_t const *dest_pc;
	offset = *(s8 *)pc;
	pc += 1;
	dest_pc = pc + offset;
	EMU86_EMULATE_SETPC(dest_pc);
	goto done_dont_set_pc;
}


#if CONFIG_LIBEMU86_WANT_32BIT || CONFIG_LIBEMU86_WANT_16BIT
case 0xea: {
	/* EA cd    JMP ptr16:16    Jump far, absolute, address given in operand
	 * EA cp    JMP ptr16:32    Jump far, absolute, address given in operand */
	u32 offset;
	u16 segment;
	if (op_flags & EMU86_F_AD16) {
		offset = UNALIGNED_GET16((u16 *)pc);
		pc += 2;
	} else {
		offset = UNALIGNED_GET32((u32 *)pc);
		pc += 4;
	}
	segment = UNALIGNED_GET16((u16 *)pc);
	/* Verify the segment index. */
#if EMU86_EMULATE_CHECKUSER
	if (!SEGMENT_IS_VALID_USERCODE(segment) && EMU86_ISUSER_NOVM86()) {
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_SIGRETURN_REGISTER,
		      X86_REGISTER_SEGMENT_CS, segment);
	}
#endif /* EMU86_EMULATE_CHECKUSER */
	EMU86_SETCS(segment);
	EMU86_EMULATE_SETIP(offset);
	goto done_dont_set_pc;
}
#endif /* CONFIG_LIBEMU86_WANT_32BIT || CONFIG_LIBEMU86_WANT_16BIT */

#endif /* !EMU86_EMULATE_ONLY_MEMORY */




}
EMU86_INTELLISENSE_END
