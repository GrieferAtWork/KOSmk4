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

EMU86_INTELLISENSE_BEGIN(shiftx) {


case 0x0f38f7: {
	/* VEX.LZ.66.0F38.W0 F7 /r     SHLX r32a, r/m32, r32b     Shift r/m32 logically left with count specified in r32b.
	 * VEX.LZ.F2.0F38.W0 F7 /r     SHRX r32a, r/m32, r32b     Shift r/m32 logically right with count specified in r32b.
	 * VEX.LZ.F3.0F38.W0 F7 /r     SARX r32a, r/m32, r32b     Shift r/m32 arithmetically right with count specified in r32b.
	 * VEX.LZ.66.0F38.W1 F7 /r     SHLX r64a, r/m64, r64b     Shift r/m64 logically left with count specified in r64b.
	 * VEX.LZ.F2.0F38.W1 F7 /r     SHRX r64a, r/m64, r64b     Shift r/m64 logically right with count specified in r64b.
	 * VEX.LZ.F3.0F38.W1 F7 /r     SARX r64a, r/m64, r64b     Shift r/m64 arithmetically right with count specified in r64b. */
	u8 num_bits;
	if ((op_flags & (EMU86_F_HASVEX | EMU86_F_VEX_LL_M | EMU86_F_LOCK)) != EMU86_F_HASVEX)
		goto return_unknown_instruction;
	if ((op_flags & (EMU86_F_66 | EMU86_F_f2 | EMU86_F_f3)) == 0)
		goto return_unknown_instruction;
	MODRM_DECODE();
	num_bits = VEX_GETREGB();
#if CONFIG_LIBEMU86_WANT_64BIT
	if (op_flags & EMU86_F_VEX_W) {
		u64 value;
		num_bits %= 64;
		value = MODRM_GETRMQ();
		if (op_flags & EMU86_F_66) {
			value = value << num_bits; /* shlx */
		} else if (op_flags & EMU86_F_f2) {
			value = value >> num_bits; /* shrx */
		} else {
			value = emu86_sarq(value, num_bits); /* sarx */
		}
		MODRM_SETREGQ(value);
	} else
#endif /* CONFIG_LIBEMU86_WANT_64BIT */
	{
		u32 value;
		num_bits %= 32;
		value = MODRM_GETRML();
		if (op_flags & EMU86_F_66) {
			value = value << num_bits; /* shlx */
		} else if (op_flags & EMU86_F_f2) {
			value = value >> num_bits; /* shrx */
		} else {
			value = emu86_sarl(value, num_bits); /* sarx */
		}
		MODRM_SETREGL(value);
	}
	goto done;
}


}
EMU86_INTELLISENSE_END
