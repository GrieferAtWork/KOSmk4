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

EMU86_INTELLISENSE_BEGIN(incdec) {

#if CONFIG_LIBEMU86_WANT_16BIT || CONFIG_LIBEMU86_WANT_32BIT
#ifndef EMU86_EMULATE_ONLY_MEMORY

case 0x40 ... 0x47: {
	/* 40+ rw    INC r16      Increment word register by 1.
	 * 40+ rd    INC r32      Increment doubleword register by 1. */
	IF_64BIT({
		if (EMU86_F_IS64(op_flags))
			goto return_unknown_instruction;
	});
	if (!IS_16BIT()) {
		u32 oldval, newval;
		u32 eflags_addend = 0;
		oldval = EMU86_GETREGL(opcode - 0x40);
		if (OVERFLOW_UADD(oldval, 1, &newval))
			eflags_addend |= EFLAGS_OF;
		if ((oldval & 0xf) == 0xf)
			eflags_addend |= EFLAGS_AF;
		EMU86_SETREGL(opcode - 0x40, newval);
		EMU86_MSKFLAGS(~(EFLAGS_OF | EFLAGS_SF | EFLAGS_ZF | EFLAGS_PF | EFLAGS_AF),
		               eflags_addend | emu86_geteflags_testl(newval));
	} else {
		u16 oldval, newval;
		u32 eflags_addend = 0;
		oldval = EMU86_GETREGW(opcode - 0x40);
		if (OVERFLOW_UADD(oldval, 1, &newval))
			eflags_addend |= EFLAGS_OF;
		if ((oldval & 0xf) == 0xf)
			eflags_addend |= EFLAGS_AF;
		EMU86_SETREGW(opcode - 0x40, newval);
		EMU86_MSKFLAGS(~(EFLAGS_OF | EFLAGS_SF | EFLAGS_ZF | EFLAGS_PF | EFLAGS_AF),
		               eflags_addend | emu86_geteflags_testw(newval));
	}
	goto done;
}


case 0x48 ... 0x4f: {
	/* 48+ rw    DEC r16      Decrement word register by 1.
	 * 48+ rd    DEC r32      Decrement doubleword register by 1. */
	IF_64BIT({
		if (EMU86_F_IS64(op_flags))
			goto return_unknown_instruction;
	});
	if (!IS_16BIT()) {
		u32 oldval, newval;
		u32 eflags_addend = EFLAGS_AF;
		oldval = EMU86_GETREGL(opcode - 0x48);
		if (OVERFLOW_USUB(oldval, 1, &newval))
			eflags_addend |= EFLAGS_OF;
		EMU86_SETREGL(opcode - 0x48, newval);
		EMU86_MSKFLAGS(~(EFLAGS_OF | EFLAGS_SF | EFLAGS_ZF | EFLAGS_PF | EFLAGS_AF),
		               eflags_addend | emu86_geteflags_testl(newval));
	} else {
		u16 oldval, newval;
		u32 eflags_addend = EFLAGS_AF;
		oldval = EMU86_GETREGW(opcode - 0x48);
		if (OVERFLOW_USUB(oldval, 1, &newval))
			eflags_addend |= EFLAGS_OF;
		EMU86_SETREGW(opcode - 0x48, newval);
		EMU86_MSKFLAGS(~(EFLAGS_OF | EFLAGS_SF | EFLAGS_ZF | EFLAGS_PF | EFLAGS_AF),
		               eflags_addend | emu86_geteflags_testw(newval));
	}
	goto done;
}



#endif /* !EMU86_EMULATE_ONLY_MEMORY */
#endif /* CONFIG_LIBEMU86_WANT_16BIT || CONFIG_LIBEMU86_WANT_32BIT */

}
EMU86_INTELLISENSE_END
