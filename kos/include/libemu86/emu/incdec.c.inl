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

EMU86_INTELLISENSE_BEGIN(incdec) {

#if !EMU86_EMULATE_CONFIG_ONLY_MEMORY
#if EMU86_EMULATE_CONFIG_WANT_INC_REG && (LIBEMU86_CONFIG_WANT_16BIT || LIBEMU86_CONFIG_WANT_32BIT)
case EMU86_OPCODE_ENCODE(0x40) ... EMU86_OPCODE_ENCODE(0x47): {
	/* 40+ rw    INC r16      Increment word register by 1.
	 * 40+ rd    INC r32      Increment doubleword register by 1. */
	u8 regno;
	regno = tiny_opcode - EMU86_OPCODE_ENCODE(0x40);
#if LIBEMU86_CONFIG_WANT_64BIT
#define NEED_return_unsupported_instruction
	if (EMU86_F_IS64(op_flags))
		goto return_unsupported_instruction;
#if 0 /* Unsupported in 64-bit mode... */
	if (op_flags & EMU86_F_REX_B)
		regno |= 0x8;
#endif
#endif /* LIBEMU86_CONFIG_WANT_64BIT */
	if (!IS_16BIT()) {
		u32 oldval, newval;
		u32 eflags_addend = 0;
		oldval = EMU86_GETREGL(regno);
		if (OVERFLOW_SADD((s32)oldval, (s32)1, (s32 *)&newval))
			eflags_addend |= EFLAGS_OF;
		if (emu86_getflags_AF_add(oldval, 1))
			eflags_addend |= EFLAGS_AF;
		EMU86_SETREGL(regno, newval);
		EMU86_MSKFLAGS(~(EFLAGS_OF | EFLAGS_SF | EFLAGS_ZF | EFLAGS_PF | EFLAGS_AF),
		               eflags_addend | emu86_geteflags_testl(newval));
	} else {
		u16 oldval, newval;
		u32 eflags_addend = 0;
		oldval = EMU86_GETREGW(regno);
		if (OVERFLOW_SADD((s16)oldval, (s16)1, (s16 *)&newval))
			eflags_addend |= EFLAGS_OF;
		if (emu86_getflags_AF_add(oldval, 1))
			eflags_addend |= EFLAGS_AF;
		EMU86_SETREGW(regno, newval);
		EMU86_MSKFLAGS(~(EFLAGS_OF | EFLAGS_SF | EFLAGS_ZF | EFLAGS_PF | EFLAGS_AF),
		               eflags_addend | emu86_geteflags_testw(newval));
	}
	goto done;
}
#elif EMU86_EMULATE_CONFIG_CHECKERROR && !EMU86_EMULATE_CONFIG_ONLY_CHECKERROR_NO_BASIC
case EMU86_OPCODE_ENCODE(0x40) ... EMU86_OPCODE_ENCODE(0x47):
	goto return_unsupported_instruction;
#define NEED_return_unsupported_instruction
#endif


#if EMU86_EMULATE_CONFIG_WANT_DEC_REG && (LIBEMU86_CONFIG_WANT_16BIT || LIBEMU86_CONFIG_WANT_32BIT)
case EMU86_OPCODE_ENCODE(0x48) ... EMU86_OPCODE_ENCODE(0x4f): {
	/* 48+ rw    DEC r16      Decrement word register by 1.
	 * 48+ rd    DEC r32      Decrement doubleword register by 1. */
	u8 regno;
	regno = tiny_opcode - EMU86_OPCODE_ENCODE(0x48);
#if LIBEMU86_CONFIG_WANT_64BIT
#define NEED_return_unsupported_instruction
	if (EMU86_F_IS64(op_flags))
		goto return_unsupported_instruction;
#if 0 /* Unsupported in 64-bit mode... */
	if (op_flags & EMU86_F_REX_B)
		regno |= 0x8;
#endif
#endif /* LIBEMU86_CONFIG_WANT_64BIT */
	if (!IS_16BIT()) {
		u32 oldval, newval;
		u32 eflags_addend = 0;
		oldval = EMU86_GETREGL(regno);
		if (OVERFLOW_SSUB((s32)oldval, (s32)1, (s32 *)&newval))
			eflags_addend |= EFLAGS_OF;
		if (emu86_getflags_AF_sub(oldval, 1))
			eflags_addend |= EFLAGS_AF;
		EMU86_SETREGL(regno, newval);
		EMU86_MSKFLAGS(~(EFLAGS_OF | EFLAGS_SF | EFLAGS_ZF | EFLAGS_PF | EFLAGS_AF),
		               eflags_addend | emu86_geteflags_testl(newval));
	} else {
		u16 oldval, newval;
		u32 eflags_addend = 0;
		oldval = EMU86_GETREGW(regno);
		if (OVERFLOW_SSUB((s16)oldval, (s16)1, (s16 *)&newval))
			eflags_addend |= EFLAGS_OF;
		if (emu86_getflags_AF_sub(oldval, 1))
			eflags_addend |= EFLAGS_AF;
		EMU86_SETREGW(regno, newval);
		EMU86_MSKFLAGS(~(EFLAGS_OF | EFLAGS_SF | EFLAGS_ZF | EFLAGS_PF | EFLAGS_AF),
		               eflags_addend | emu86_geteflags_testw(newval));
	}
	goto done;
}
#elif EMU86_EMULATE_CONFIG_CHECKERROR && !EMU86_EMULATE_CONFIG_ONLY_CHECKERROR_NO_BASIC
case EMU86_OPCODE_ENCODE(0x48) ... EMU86_OPCODE_ENCODE(0x4f):
	goto return_unsupported_instruction;
#define NEED_return_unsupported_instruction
#endif

#endif /* !EMU86_EMULATE_CONFIG_ONLY_MEMORY */

}
EMU86_INTELLISENSE_END
