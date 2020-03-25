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

EMU86_INTELLISENSE_BEGIN(pext) {


case EMU86_OPCODE_ENCODE(0x0f38f5): {
	MODRM_DECODE();
	if ((op_flags & (EMU86_F_HASVEX | EMU86_F_VEX_LL_M |
	                 EMU86_F_LOCK | EMU86_F_66)) != EMU86_F_HASVEX)
		goto return_unknown_instruction;
	if (op_flags & EMU86_F_f3) {
		/* VEX.LZ.F3.0F38.W0 F5 /r     PEXT r32a, r32b, r/m32     Parallel extract of bits from r32b using mask in r/m32, result is written to r32a.
		 * VEX.LZ.F3.0F38.W1 F5 /r     PEXT r64a, r64b, r/m64     Parallel extract of bits from r64b using mask in r/m64, result is written to r64a. */
#if CONFIG_LIBEMU86_WANT_64BIT
		if (op_flags & EMU86_F_VEX_W) {
			u64 src, msk, result, srcmsk, resmsk;
			src = MODRM_GETRMQ();
			msk = VEX_GETREGQ();
			result = 0;
			for (srcmsk = resmsk = 1; srcmsk <= msk; srcmsk <<= 1) {
				if (!(msk & srcmsk))
					continue;
				if (src & srcmsk)
					result |= resmsk;
				resmsk <<= 1;
			}
			MODRM_SETREGQ(result);
		} else
#endif /* CONFIG_LIBEMU86_WANT_64BIT */
		{
			u32 src, msk, result, srcmsk, resmsk;
			src = MODRM_GETRML();
			msk = VEX_GETREGL();
			result = 0;
			for (srcmsk = resmsk = 1; srcmsk <= msk; srcmsk <<= 1) {
				if (!(msk & srcmsk))
					continue;
				if (src & srcmsk)
					result |= resmsk;
				resmsk <<= 1;
			}
			MODRM_SETREGL(result);
		}
		goto done;
	} else if (op_flags & EMU86_F_f2) {
		/* VEX.LZ.F2.0F38.W0 F5 /r     PDEP r32a, r32b, r/m32     Parallel deposit of bits from r32b using mask in r/m32, result is written to r32a.
		 * VEX.LZ.F2.0F38.W1 F5 /r     PDEP r64a, r64b, r/m64     Parallel deposit of bits from r64b using mask in r/m64, result is written to r64a. */
#if CONFIG_LIBEMU86_WANT_64BIT
		if (op_flags & EMU86_F_VEX_W) {
			u64 src, msk, result, resmsk;
			src = MODRM_GETRMQ();
			msk = VEX_GETREGQ();
			result = 0;
			for (resmsk = 1; src && resmsk <= msk; resmsk <<= 1) {
				if (!(msk & resmsk))
					continue;
				if (src & 1)
					result |= resmsk;
				src >>= 1;
			}
			MODRM_SETREGQ(result);
		} else
#endif /* CONFIG_LIBEMU86_WANT_64BIT */
		{
			u32 src, msk, result, resmsk;
			src = MODRM_GETRML();
			msk = VEX_GETREGL();
			result = 0;
			for (resmsk = 1; src && resmsk <= msk; resmsk <<= 1) {
				if (!(msk & resmsk))
					continue;
				if (src & 1)
					result |= resmsk;
				src >>= 1;
			}
			MODRM_SETREGL(result);
		}
		goto done;
	} else {
		/* VEX.LZ.0F38.W0 F5 /r     BZHI r32a, r/m32, r32b     Zero bits in r/m32 starting with the position in r32b, write result to r32a.
		 * VEX.LZ.0F38.W1 F5 /r     BZHI r64a, r/m64, r64b     Zero bits in r/m64 starting with the position in r64b, write result to r64a. */
		u8 num_bits;
		u32 eflags_addend = 0;
		num_bits = VEX_GETREGB();
#if CONFIG_LIBEMU86_WANT_64BIT
		if (op_flags & EMU86_F_VEX_W) {
			u64 src, result;
			src    = MODRM_GETRMQ();
			result = src;
			if (num_bits < 64) {
				/* Clear the upper-most `num_bits' bits. */
				result &= ~((u64)UINT64_MAX >> num_bits);
			} else {
				eflags_addend |= EFLAGS_CF;
			}
			MODRM_SETREGQ(result);
			eflags_addend |= emu86_geteflags_SFq(result);
			eflags_addend |= emu86_geteflags_ZFq(result);
		} else
#endif /* CONFIG_LIBEMU86_WANT_64BIT */
		{
			u32 src, result;
			src    = MODRM_GETRML();
			result = src;
			if (num_bits < 32) {
				/* Clear the upper-most `num_bits' bits. */
				result &= ~((u32)UINT32_MAX >> num_bits);
			} else {
				eflags_addend |= EFLAGS_CF;
			}
			MODRM_SETREGL(result);
			eflags_addend |= emu86_geteflags_SFl(result);
			eflags_addend |= emu86_geteflags_ZFl(result);
		}
		EMU86_MSKFLAGS(~(EFLAGS_ZF | EFLAGS_CF | EFLAGS_SF | EFLAGS_OF),
		               eflags_addend);
		goto done;
	}
}


}
EMU86_INTELLISENSE_END
