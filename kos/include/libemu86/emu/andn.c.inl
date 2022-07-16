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

EMU86_INTELLISENSE_BEGIN(andn) {


#if EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_ANDN
case EMU86_OPCODE_ENCODE(0x0f38f2): {
	/* VEX.LZ.0F38.W0 F2 /r     ANDN r32a, r32b, r/m32     Bitwise AND of inverted r32b with r/m32, store result in r32a.
	 * VEX.LZ.0F38.W1 F2 /r     ANDN r64a, r64b, r/m64     Bitwise AND of inverted r64b with r/m64, store result in r64a. */
#if EMU86_EMULATE_CONFIG_WANT_ANDN
	EMU86_UREG_TYPE result;
	u32 eflags_addend = 0;
#endif /* EMU86_EMULATE_CONFIG_WANT_ANDN */
	if ((op_flags & (EMU86_F_HASVEX | EMU86_F_VEX_LL_M |
	                 EMU86_F_66 | EMU86_F_f2 | EMU86_F_f3)) != EMU86_F_HASVEX)
		goto return_unexpected_prefix;
#define NEED_return_unexpected_prefix
	MODRM_DECODE();
#if EMU86_EMULATE_CONFIG_WANT_ANDN
#if LIBEMU86_CONFIG_WANT_64BIT
	if (op_flags & EMU86_F_VEX_W) {
		u64 lhs, rhs;
		lhs = VEX_GETREGQ();
		rhs = MODRM_GETRMQ();
		result = ~lhs & rhs;
		if ((s64)(u64)result < 0)
			eflags_addend |= EFLAGS_SF;
		MODRM_SETREGQ(result);
	} else
#endif /* LIBEMU86_CONFIG_WANT_64BIT */
	{
		u32 lhs, rhs;
		lhs = VEX_GETREGL();
		rhs = MODRM_GETRML();
		result = ~lhs & rhs;
		if ((s32)(u32)result < 0)
			eflags_addend |= EFLAGS_SF;
		MODRM_SETREGL(result);
	}
	if (result == 0)
		eflags_addend |= EFLAGS_ZF;
	EMU86_MSKFLAGS(~(EFLAGS_SF | EFLAGS_ZF),
	               eflags_addend);
	goto done;
#else /* EMU86_EMULATE_CONFIG_WANT_ANDN */
	goto notsup_modrm_getz_rex_w_modrm_parsed;
#define NEED_notsup_modrm_getz_rex_w_modrm_parsed
#endif /* !EMU86_EMULATE_CONFIG_WANT_ANDN */
}
#endif /* EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_ANDN */



}
EMU86_INTELLISENSE_END
