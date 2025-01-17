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

EMU86_INTELLISENSE_BEGIN(shiftx) {


#if EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_BEXTR || EMU86_EMULATE_CONFIG_WANT_SHIFTX
case EMU86_OPCODE_ENCODE(0x0f38f7): {
	MODRM_DECODE();
	if ((op_flags & (EMU86_F_HASVEX | EMU86_F_VEX_LL_M)) != EMU86_F_HASVEX)
		goto return_unexpected_prefix;
#define NEED_return_unexpected_prefix
	if ((op_flags & (EMU86_F_66 | EMU86_F_f2 | EMU86_F_f3)) == 0) {
#if EMU86_EMULATE_CONFIG_WANT_BEXTR
		/* VEX.LZ.0F38.W0 F7 /r     BEXTR r32a, r/m32, r32b     Contiguous bitwise extract from r/m32 using r32b as control; store result in r32a.
		 * VEX.LZ.0F38.W1 F7 /r     BEXTR r64a, r/m64, r64b     Contiguous bitwise extract from r/m64 using r64b as control; store result in r64a. */
		u32 eflags_addend = 0;
		u8 start, len;
		{
			u16 source;
			source = VEX_GETREGW();
			start  = (u8)(source);
			len    = (u8)(source >> 8);
		}
#if LIBEMU86_CONFIG_WANT_64BIT
		if (op_flags & EMU86_F_VEX_W) {
			u64 value, result;
			if (start >= 64)
				goto bextr_write_dst_0;
			if (len > 63)
				len = 63;
			value = MODRM_GETRMQ();
			result = (value >> start) & (((u64)1 << len) - 1);
			if (result == 0)
				eflags_addend |= EFLAGS_ZF;
			MODRM_SETREGQ(result);
		} else
#endif /* LIBEMU86_CONFIG_WANT_64BIT */
		{
			if (start >= 32) {
#if LIBEMU86_CONFIG_WANT_64BIT
bextr_write_dst_0:
				MODRM_SETREGQ(0);
#else /* LIBEMU86_CONFIG_WANT_64BIT */
				MODRM_SETREGL(0);
#endif /* !LIBEMU86_CONFIG_WANT_64BIT */
				eflags_addend |= EFLAGS_ZF; /* Result is 0 */
			} else {
				u32 value, result;
				if (len > 31)
					len = 31;
				value  = MODRM_GETRML();
				result = (value >> start) & (((u32)1 << len) - 1);
				if (result == 0)
					eflags_addend |= EFLAGS_ZF;
				MODRM_SETREGL(result);
			}
		}
		EMU86_MSKFLAGS(~(EFLAGS_ZF | EFLAGS_CF | EFLAGS_OF),
		               eflags_addend);
		goto done;
#elif EMU86_EMULATE_CONFIG_CHECKERROR
		goto notsup_modrm_getz_rex_w_modrm_parsed;
#define NEED_notsup_modrm_getz_rex_w_modrm_parsed
#else /* ... */
		goto return_unsupported_instruction;
#define NEED_return_unsupported_instruction
#endif /* !... */
	} else {
#if EMU86_EMULATE_CONFIG_WANT_SHIFTX
		/* VEX.LZ.66.0F38.W0 F7 /r     SHLX r32a, r/m32, r32b     Shift r/m32 logically left with count specified in r32b.
		 * VEX.LZ.F2.0F38.W0 F7 /r     SHRX r32a, r/m32, r32b     Shift r/m32 logically right with count specified in r32b.
		 * VEX.LZ.F3.0F38.W0 F7 /r     SARX r32a, r/m32, r32b     Shift r/m32 arithmetically right with count specified in r32b.
		 * VEX.LZ.66.0F38.W1 F7 /r     SHLX r64a, r/m64, r64b     Shift r/m64 logically left with count specified in r64b.
		 * VEX.LZ.F2.0F38.W1 F7 /r     SHRX r64a, r/m64, r64b     Shift r/m64 logically right with count specified in r64b.
		 * VEX.LZ.F3.0F38.W1 F7 /r     SARX r64a, r/m64, r64b     Shift r/m64 arithmetically right with count specified in r64b. */
		u8 num_bits;
		num_bits = VEX_GETREGB();
#if LIBEMU86_CONFIG_WANT_64BIT
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
#endif /* LIBEMU86_CONFIG_WANT_64BIT */
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
#elif EMU86_EMULATE_CONFIG_CHECKERROR
		goto notsup_modrm_getz_rex_w_modrm_parsed;
#define NEED_notsup_modrm_getz_rex_w_modrm_parsed
#else /* ... */
		goto return_unsupported_instruction;
#define NEED_return_unsupported_instruction
#endif
	}
	break;
}
#endif /* EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_BEXTR || EMU86_EMULATE_CONFIG_WANT_SHIFTX */


}
EMU86_INTELLISENSE_END
