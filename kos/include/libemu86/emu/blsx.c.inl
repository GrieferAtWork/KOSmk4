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

EMU86_INTELLISENSE_BEGIN(blsx) {


#if (EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_BLSR || \
     EMU86_EMULATE_CONFIG_WANT_BLSMSK || EMU86_EMULATE_CONFIG_WANT_BLSI)
case EMU86_OPCODE_ENCODE(0x0f38f3): {
	MODRM_DECODE();
	if ((op_flags & (EMU86_F_HASVEX | EMU86_F_VEX_LL_M |
	                 EMU86_F_66 | EMU86_F_f2 | EMU86_F_f3)) != EMU86_F_HASVEX)
		goto return_unknown_instruction_rmreg;
#define NEED_return_unknown_instruction_rmreg
	switch (modrm.mi_reg) {

#if EMU86_EMULATE_CONFIG_WANT_BLSR
	case 1: {
		/* VEX.LZ.0F38.W0 F3 /1     BLSR r32, r/m32     Reset lowest set bit of r/m32, keep all other bits of r/m32 and write result to r32.
		 * VEX.LZ.0F38.W1 F3 /1     BLSR r64, r/m64     Reset lowest set bit of r/m64, keep all other bits of r/m64 and write result to r64. */
		u32 eflags_addend = 0;
#if LIBEMU86_CONFIG_WANT_64BIT
		if (op_flags & EMU86_F_VEX_W) {
			u64 src, result;
			src = MODRM_GETRMQ();
			result = src & (src - 1);
			if ((s64)result < 0)
				eflags_addend |= EFLAGS_SF;
			if (result == 0)
				eflags_addend |= EFLAGS_ZF;
			if (src == 0)
				eflags_addend |= EFLAGS_CF;
			VEX_SETREGQ(result);
		} else
#endif /* LIBEMU86_CONFIG_WANT_64BIT */
		{
			u32 src, result;
			src = MODRM_GETRML();
			result = src & (src - 1);
			if ((s32)result < 0)
				eflags_addend |= EFLAGS_SF;
			if (result == 0)
				eflags_addend |= EFLAGS_ZF;
			if (src == 0)
				eflags_addend |= EFLAGS_CF;
			VEX_SETREGL(result);
		}
		EMU86_MSKFLAGS(~(EFLAGS_SF | EFLAGS_ZF | EFLAGS_CF | EFLAGS_OF),
		               eflags_addend);
		goto done;
	}
#elif EMU86_EMULATE_CONFIG_CHECKERROR
	case 1:
		goto notsup_modrm_getz_rex_w_modrm_parsed_rmreg;
#define NEED_notsup_modrm_getz_rex_w_modrm_parsed_rmreg
#endif /* ... */


#if EMU86_EMULATE_CONFIG_WANT_BLSMSK
	case 2: {
		/* VEX.LZ.0F38.W0 F3 /2     BLSMSK r32, r/m32     Set all lower bits in r32 to "1" starting from bit 0 to lowest set bit in r/m32.
		 * VEX.LZ.0F38.W1 F3 /2     BLSMSK r64, r/m64     Set all lower bits in r64 to "1" starting from bit 0 to lowest set bit in r/m64. */
		u32 eflags_addend = 0;
#if LIBEMU86_CONFIG_WANT_64BIT
		if (op_flags & EMU86_F_VEX_W) {
			u64 src, result;
			src = MODRM_GETRMQ();
			result = src ^ (src - 1);
			if ((s64)result < 0)
				eflags_addend |= EFLAGS_SF;
			if (src == 0)
				eflags_addend |= EFLAGS_CF;
			VEX_SETREGQ(result);
		} else
#endif /* LIBEMU86_CONFIG_WANT_64BIT */
		{
			u32 src, result;
			src = MODRM_GETRML();
			result = src ^ (src - 1);
			if ((s32)result < 0)
				eflags_addend |= EFLAGS_SF;
			if (src == 0)
				eflags_addend |= EFLAGS_CF;
			VEX_SETREGL(result);
		}
		EMU86_MSKFLAGS(~(EFLAGS_SF | EFLAGS_ZF | EFLAGS_CF | EFLAGS_OF),
		               eflags_addend);
		goto done;
	}
#elif EMU86_EMULATE_CONFIG_CHECKERROR
	case 2:
		goto notsup_modrm_getz_rex_w_modrm_parsed_rmreg;
#define NEED_notsup_modrm_getz_rex_w_modrm_parsed_rmreg
#endif /* ... */


#if EMU86_EMULATE_CONFIG_WANT_BLSI
	case 3: {
		/* VEX.LZ.0F38.W0 F3 /3     BLSI r32, r/m32     Extract lowest set bit from r/m32 and set that bit in r32.
		 * VEX.LZ.0F38.W1 F3 /3     BLSI r64, r/m64     Extract lowest set bit from r/m64, and set that bit in r64. */
		u32 eflags_addend = 0;
#if LIBEMU86_CONFIG_WANT_64BIT
		if (op_flags & EMU86_F_VEX_W) {
			u64 src, result;
			src = MODRM_GETRMQ();
			result = src & ~(src - 1);
			if ((s64)result < 0)
				eflags_addend |= EFLAGS_SF;
			if (result == 0)
				eflags_addend |= EFLAGS_ZF;
			if (src != 0)
				eflags_addend |= EFLAGS_CF;
			VEX_SETREGQ(result);
		} else
#endif /* LIBEMU86_CONFIG_WANT_64BIT */
		{
			u32 src, result;
			src = MODRM_GETRML();
			result = src & ~(src - 1);
			if ((s32)result < 0)
				eflags_addend |= EFLAGS_SF;
			if (result == 0)
				eflags_addend |= EFLAGS_ZF;
			if (src != 0)
				eflags_addend |= EFLAGS_CF;
			VEX_SETREGL(result);
		}
		EMU86_MSKFLAGS(~(EFLAGS_SF | EFLAGS_ZF | EFLAGS_CF | EFLAGS_OF),
		               eflags_addend);
		goto done;
	}
#elif EMU86_EMULATE_CONFIG_CHECKERROR
	case 3:
		goto notsup_modrm_getz_rex_w_modrm_parsed_rmreg;
#define NEED_notsup_modrm_getz_rex_w_modrm_parsed_rmreg
#endif /* ... */


	default:
		goto return_unknown_instruction_rmreg;
#define NEED_return_unknown_instruction_rmreg
	}
	break;
}
#endif /* EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_BLSR || EMU86_EMULATE_CONFIG_WANT_BLSMSK || EMU86_EMULATE_CONFIG_WANT_BLSI */


}
EMU86_INTELLISENSE_END
