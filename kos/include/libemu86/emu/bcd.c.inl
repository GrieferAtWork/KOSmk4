/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifdef __INTELLISENSE__
#include "../emulate.c.inl"
#endif /* __INTELLISENSE__ */

EMU86_INTELLISENSE_BEGIN(bcd) {

#if !EMU86_EMULATE_CONFIG_ONLY_MEMORY
#if EMU86_EMULATE_CONFIG_CHECKERROR || LIBEMU86_CONFIG_WANT_16BIT || LIBEMU86_CONFIG_WANT_32BIT

#if EMU86_EMULATE_CONFIG_WANT_DAA
case EMU86_OPCODE_ENCODE(0x27): {
	/* 27     DAA     Decimal adjust AL after addition. */
	uintptr_t old_flags, new_flags;
	u8 old_al, new_al;
#if LIBEMU86_CONFIG_WANT_64BIT
#define NEED_return_unsupported_instruction
	if (EMU86_F_IS64(op_flags))
		goto return_unsupported_instruction;
#endif /* LIBEMU86_CONFIG_WANT_64BIT */
	old_al    = EMU86_GETAL();
	old_flags = EMU86_GETFLAGS();
	new_al    = old_al;
	new_flags = old_flags;
	if (((new_al & 0xf) > 9) || (new_flags & EFLAGS_AF)) {
		new_al += 6;
		new_flags |= EFLAGS_AF;
	} else {
		new_flags &= ~EFLAGS_AF;
	}
	if (old_al > 0x99 || (old_flags & EFLAGS_CF)) {
		new_al += 0x60;
		new_flags |= EFLAGS_CF;
	} else {
		new_flags &= ~(EFLAGS_CF);
	}
	new_flags &= ~(EFLAGS_SF | EFLAGS_ZF | EFLAGS_PF);
	new_flags |= emu86_geteflags_testb(new_al);
	EMU86_SETAL(new_al);
	EMU86_SETFLAGS(new_flags);
	goto done;
}
#elif !EMU86_EMULATE_CONFIG_ONLY_CHECKERROR_NO_BASIC
case EMU86_OPCODE_ENCODE(0x27):
#define NEED_return_unsupported_instruction
	goto return_unsupported_instruction;
#endif /* ... */


#if EMU86_EMULATE_CONFIG_WANT_DAS
case EMU86_OPCODE_ENCODE(0x2f): {
	/* 2F     DAS     Decimal adjust AL after subtraction. */
	uintptr_t old_flags, new_flags;
	u8 old_al, new_al;
#if LIBEMU86_CONFIG_WANT_64BIT
#define NEED_return_unsupported_instruction
	if (EMU86_F_IS64(op_flags))
		goto return_unsupported_instruction;
#endif /* LIBEMU86_CONFIG_WANT_64BIT */
	old_al    = EMU86_GETAL();
	old_flags = EMU86_GETFLAGS();
	new_al    = old_al;
	new_flags = old_flags;
	if ((new_al & 0xf) > 9 || (new_flags & EFLAGS_AF)) {
		if (OVERFLOW_USUB(new_al, 6, &new_al))
			new_flags |= EFLAGS_CF;
		new_flags |= EFLAGS_AF;
	} else {
		new_flags &= ~(EFLAGS_CF | EFLAGS_AF);
	}
	if ((old_al > 0x99) || (old_flags & EFLAGS_CF)) {
		new_al -= 0x60;
		new_flags |= EFLAGS_CF;
	}
	new_flags &= ~(EFLAGS_SF | EFLAGS_ZF | EFLAGS_PF);
	new_flags |= emu86_geteflags_testb(new_al);
	EMU86_SETAL(new_al);
	EMU86_SETFLAGS(new_flags);
	goto done;
}
#elif !EMU86_EMULATE_CONFIG_ONLY_CHECKERROR_NO_BASIC
case EMU86_OPCODE_ENCODE(0x2f):
#define NEED_return_unsupported_instruction
	goto return_unsupported_instruction;
#endif /* ... */


#if EMU86_EMULATE_CONFIG_WANT_AAA
case EMU86_OPCODE_ENCODE(0x37): {
	/* 37     AAA     ASCII adjust AL after addition. */
	uintptr_t flags;
	u16 ax;
#if LIBEMU86_CONFIG_WANT_64BIT
#define NEED_return_unsupported_instruction
	if (EMU86_F_IS64(op_flags))
		goto return_unsupported_instruction;
#endif /* LIBEMU86_CONFIG_WANT_64BIT */
	ax    = EMU86_GETAX();
	flags = EMU86_GETFLAGS();
	if ((ax & 0xf) > 9 || (flags & EFLAGS_AF)) {
		ax += 0x106;
		flags |= (EFLAGS_AF | EFLAGS_CF);
	} else {
		flags &= ~(EFLAGS_AF | EFLAGS_CF);
	}
	ax &= 0xff0f;
	EMU86_SETAX(ax);
	EMU86_SETFLAGS(flags);
	goto done;
}
#elif !EMU86_EMULATE_CONFIG_ONLY_CHECKERROR_NO_BASIC
case EMU86_OPCODE_ENCODE(0x37):
#define NEED_return_unsupported_instruction
	goto return_unsupported_instruction;
#endif /* ... */


#if EMU86_EMULATE_CONFIG_WANT_AAS
case EMU86_OPCODE_ENCODE(0x3f): {
	/* 3F     AAS     ASCII adjust AL after subtraction.
	 * s.a. https://www.youtube.com/watch?v=c2ia8T4E2Mc */
	uintptr_t flags;
	u16 ax;
#if LIBEMU86_CONFIG_WANT_64BIT
#define NEED_return_unsupported_instruction
	if (EMU86_F_IS64(op_flags))
		goto return_unsupported_instruction;
#endif /* LIBEMU86_CONFIG_WANT_64BIT */
	ax    = EMU86_GETAX();
	flags = EMU86_GETFLAGS();
	if ((ax & 0xf) > 9 || (flags & EFLAGS_AF)) {
		ax -= 0x106;
		flags |= (EFLAGS_CF | EFLAGS_AF);
	} else {
		flags &= ~(EFLAGS_CF | EFLAGS_AF);
	}
	ax &= 0xff0f;
	EMU86_SETAX(ax);
	EMU86_SETFLAGS(flags);
	goto done;
}
#elif !EMU86_EMULATE_CONFIG_ONLY_CHECKERROR_NO_BASIC
case EMU86_OPCODE_ENCODE(0x3f):
#define NEED_return_unsupported_instruction
	goto return_unsupported_instruction;
#endif /* ... */



#if EMU86_EMULATE_CONFIG_WANT_AAM
#ifndef NIF_EMU86_EMULATE_THROW_DIVIDE_BY_ZERO_ALLOW_RETHROW
#if EMU86_EMULATE_THROW_DIVIDE_BY_ZERO_ALLOW_RETHROW
#define NIF_EMU86_EMULATE_THROW_DIVIDE_BY_ZERO_ALLOW_RETHROW(...) /* nothing */
#else /* EMU86_EMULATE_THROW_DIVIDE_BY_ZERO_ALLOW_RETHROW */
#define NIF_EMU86_EMULATE_THROW_DIVIDE_BY_ZERO_ALLOW_RETHROW(...) __VA_ARGS__
#endif /* !EMU86_EMULATE_THROW_DIVIDE_BY_ZERO_ALLOW_RETHROW */
#endif /* !NIF_EMU86_EMULATE_THROW_DIVIDE_BY_ZERO_ALLOW_RETHROW */

case EMU86_OPCODE_ENCODE(0xd4): {
	/* D4 0A     AAM          ASCII adjust AX after multiply.
	 * D4 ib     AAM imm8     Adjust AX after multiply to number base imm8. */
	u8 base;
	u8 ah, al;
#if LIBEMU86_CONFIG_WANT_64BIT
#define NEED_return_unsupported_instruction
	if (EMU86_F_IS64(op_flags))
		goto return_unsupported_instruction;
#endif /* LIBEMU86_CONFIG_WANT_64BIT */
	base = *(u8 const *)pc;
	pc += 1;
	al = EMU86_GETAL();
	NIF_EMU86_EMULATE_THROW_DIVIDE_BY_ZERO_ALLOW_RETHROW(TRY) {
		ah = (u16)(al / base);
		al = (u8)(al % base);
	} NIF_EMU86_EMULATE_THROW_DIVIDE_BY_ZERO_ALLOW_RETHROW(EXCEPT {
		if (was_thrown(E_DIVIDE_BY_ZERO))
			EMU86_EMULATE_THROW_DIVIDE_BY_ZEROB(al);
		RETHROW();
	});
	EMU86_SETAL(al);
	EMU86_SETAH(ah);
	EMU86_MSKFLAGS(~(EFLAGS_SF | EFLAGS_ZF | EFLAGS_PF),
	               emu86_geteflags_testb(al));
	goto done;
}
#elif !EMU86_EMULATE_CONFIG_ONLY_CHECKERROR_NO_BASIC
case EMU86_OPCODE_ENCODE(0xd4):
#define NEED_return_unsupported_instruction
	goto return_unsupported_instruction;
#endif /* ... */


#if EMU86_EMULATE_CONFIG_WANT_AAD
case EMU86_OPCODE_ENCODE(0xd5): {
	/* D5 0A     AAD          ASCII adjust AX before division.
	 * D5 ib     AAD imm8     Adjust AX before division to number base imm8. */
	u8 base;
	u8 ah, al;
#if LIBEMU86_CONFIG_WANT_64BIT
#define NEED_return_unsupported_instruction
	if (EMU86_F_IS64(op_flags))
		goto return_unsupported_instruction;
#endif /* LIBEMU86_CONFIG_WANT_64BIT */
	base = *(u8 const *)pc;
	pc += 1;
	al = EMU86_GETAL();
	ah = EMU86_GETAH();
	al = (al + (ah * base)) & 0xff;
	EMU86_SETAL(al);
	EMU86_SETAH(0);
	EMU86_MSKFLAGS(~(EFLAGS_SF | EFLAGS_ZF | EFLAGS_PF),
	               emu86_geteflags_testb(al));
	goto done;
}
#elif !EMU86_EMULATE_CONFIG_ONLY_CHECKERROR_NO_BASIC
case EMU86_OPCODE_ENCODE(0xd5):
#define NEED_return_unsupported_instruction
	goto return_unsupported_instruction;
#endif /* ... */

#endif /* EMU86_EMULATE_CONFIG_CHECKERROR || LIBEMU86_CONFIG_WANT_16BIT || LIBEMU86_CONFIG_WANT_32BIT */
#endif /* !EMU86_EMULATE_CONFIG_ONLY_MEMORY */

}
EMU86_INTELLISENSE_END
