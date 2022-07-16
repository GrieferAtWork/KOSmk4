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

EMU86_INTELLISENSE_BEGIN(rorx) {


#if EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_RORX
case EMU86_OPCODE_ENCODE(0x0f3af0): {
	/* VEX.LZ.F2.0F3A.W0 F0 /r ib     RORX r32, r/m32, imm8     Rotate 32-bit r/m32 right imm8 times without affecting arithmetic flags.
	 * VEX.LZ.F2.0F3A.W1 F0 /r ib     RORX r64, r/m64, imm8     Rotate 64-bit r/m64 right imm8 times without affecting arithmetic flags. */
	if ((op_flags & (EMU86_F_HASVEX | EMU86_F_VEX_LL_M |
	                 EMU86_F_66 | EMU86_F_f2 | EMU86_F_f3)) != EMU86_F_HASVEX)
		goto return_unexpected_prefix;
#define NEED_return_unexpected_prefix
#if EMU86_EMULATE_CONFIG_WANT_RORX
	MODRM_DECODE();
	{
		u8 num_bits;
		num_bits = *(u8 const *)pc;
		pc += 1;
#if LIBEMU86_CONFIG_WANT_64BIT
		if (op_flags & EMU86_F_VEX_W) {
			u64 value;
			value = MODRM_GETRMQ();
			num_bits %= 64;
			value = __hybrid_ror64(value, num_bits);
			MODRM_SETREGQ(value);
		} else
#endif /* LIBEMU86_CONFIG_WANT_64BIT */
		{
			u32 value;
			value = MODRM_GETRML();
			num_bits %= 32;
			value = __hybrid_ror32(value, num_bits);
			MODRM_SETREGL(value);
		}
	}
	goto done;
#else /* EMU86_EMULATE_CONFIG_WANT_RORX */
	goto notsup_modrm_getz_rex_w;
#define NEED_notsup_modrm_getz_rex_w
#endif /* !EMU86_EMULATE_CONFIG_WANT_RORX */
}
#endif /* EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_RORX */



}
EMU86_INTELLISENSE_END
