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

EMU86_INTELLISENSE_BEGIN(xop_tbm) {

#if (EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_XOP_BLCFILL ||    \
     EMU86_EMULATE_CONFIG_WANT_XOP_BLSFILL || EMU86_EMULATE_CONFIG_WANT_XOP_BLCS || \
     EMU86_EMULATE_CONFIG_WANT_XOP_TZMSK || EMU86_EMULATE_CONFIG_WANT_XOP_BLCIC ||  \
     EMU86_EMULATE_CONFIG_WANT_XOP_BLSIC || EMU86_EMULATE_CONFIG_WANT_XOP_T1MSKC)
case EMU86_OPCODE_ENCODE_XOP(9, 0x01): {
	MODRM_DECODE();
	if unlikely((op_flags & EMU86_F_VEX_LL_M) != 0)
		goto return_unexpected_vex_ll_rmreg;
#define NEED_return_unexpected_vex_ll_rmreg
	switch (modrm.mi_reg) {

#if EMU86_EMULATE_CONFIG_WANT_XOP_BLCFILL
	case 1: {
		/* BLCFILL reg32, reg/mem32             8F RXB.09 0.dest.0.00 01 /1
		 * BLCFILL reg64, reg/mem64             8F RXB.09 1.dest.0.00 01 /1 */
		u32 eflags_addend = 0;
#if LIBEMU86_CONFIG_WANT_64BIT
		if (op_flags & EMU86_F_VEX_W) {
			/* 64-bit */
			u64 temp, src;
			src = MODRM_GETRMQ();
			if (OVERFLOW_SADD((s64)src, 1, (s64 *)&temp))
				eflags_addend |= EFLAGS_CF;
			temp &= src;
			VEX_SETREGQ(temp);
			eflags_addend |= emu86_geteflags_SFq(temp);
			eflags_addend |= emu86_geteflags_ZFq(temp);
		} else
#endif /* LIBEMU86_CONFIG_WANT_64BIT */
		{
			/* 32-bit */
			u32 temp, src;
			src = MODRM_GETRML();
			if (OVERFLOW_SADD((s32)src, 1, (s32 *)&temp))
				eflags_addend |= EFLAGS_CF;
			temp &= src;
			VEX_SETREGL(temp);
			eflags_addend |= emu86_geteflags_SFl(temp);
			eflags_addend |= emu86_geteflags_ZFl(temp);
		}
		EMU86_MSKFLAGS(~(EFLAGS_OF | EFLAGS_SF | EFLAGS_ZF | EFLAGS_CF),
		               eflags_addend);
		goto done;
	}
#elif EMU86_EMULATE_CONFIG_CHECKERROR
	case 1:
		goto notsup_modrm_getlq_vex_w_rmreg_modrm_parsed;
#define NEED_notsup_modrm_getlq_vex_w_rmreg_modrm_parsed
#endif /* ... */


#if EMU86_EMULATE_CONFIG_WANT_XOP_BLSFILL
	case 2: {
		/* BLSFILL reg32, reg/mem32             8F RXB.09 0.dest.0.00 01 /2
		 * BLSFILL reg64, reg/mem64             8F RXB.09 1.dest.0.00 01 /2 */
		u32 eflags_addend = 0;
#if LIBEMU86_CONFIG_WANT_64BIT
		if (op_flags & EMU86_F_VEX_W) {
			/* 64-bit */
			u64 temp, src;
			src = MODRM_GETRMQ();
			if (OVERFLOW_SSUB((s64)src, 1, (s64 *)&temp))
				eflags_addend |= EFLAGS_CF;
			temp |= src;
			VEX_SETREGQ(temp);
			eflags_addend |= emu86_geteflags_SFq(temp);
			eflags_addend |= emu86_geteflags_ZFq(temp);
		} else
#endif /* LIBEMU86_CONFIG_WANT_64BIT */
		{
			/* 32-bit */
			u32 temp, src;
			src = MODRM_GETRML();
			if (OVERFLOW_SSUB((s32)src, 1, (s32 *)&temp))
				eflags_addend |= EFLAGS_CF;
			temp |= src;
			VEX_SETREGL(temp);
			eflags_addend |= emu86_geteflags_SFl(temp);
			eflags_addend |= emu86_geteflags_ZFl(temp);
		}
		EMU86_MSKFLAGS(~(EFLAGS_OF | EFLAGS_SF | EFLAGS_ZF | EFLAGS_CF),
		               eflags_addend);
		goto done;
	}
#elif EMU86_EMULATE_CONFIG_CHECKERROR
	case 2:
		goto notsup_modrm_getlq_vex_w_rmreg_modrm_parsed;
#define NEED_notsup_modrm_getlq_vex_w_rmreg_modrm_parsed
#endif /* ... */


#if EMU86_EMULATE_CONFIG_WANT_XOP_BLCS
	case 3: {
		/* BLCS reg32, reg/mem32                8F RXB.09 0.dest.0.00 01 /3
		 * BLCS reg64, reg/mem64                8F RXB.09 1.dest.0.00 01 /3 */
		u32 eflags_addend = 0;
#if LIBEMU86_CONFIG_WANT_64BIT
		if (op_flags & EMU86_F_VEX_W) {
			/* 64-bit */
			u64 temp, src;
			src = MODRM_GETRMQ();
			if (OVERFLOW_SADD((s64)src, 1, (s64 *)&temp))
				eflags_addend |= EFLAGS_CF;
			temp |= src;
			VEX_SETREGQ(temp);
			eflags_addend |= emu86_geteflags_SFq(temp);
			eflags_addend |= emu86_geteflags_ZFq(temp);
		} else
#endif /* LIBEMU86_CONFIG_WANT_64BIT */
		{
			/* 32-bit */
			u32 temp, src;
			src = MODRM_GETRML();
			if (OVERFLOW_SADD((s32)src, 1, (s32 *)&temp))
				eflags_addend |= EFLAGS_CF;
			temp |= src;
			VEX_SETREGL(temp);
			eflags_addend |= emu86_geteflags_SFl(temp);
			eflags_addend |= emu86_geteflags_ZFl(temp);
		}
		EMU86_MSKFLAGS(~(EFLAGS_OF | EFLAGS_SF | EFLAGS_ZF | EFLAGS_CF),
		               eflags_addend);
		goto done;
	}
#elif EMU86_EMULATE_CONFIG_CHECKERROR
	case 3:
		goto notsup_modrm_getlq_vex_w_rmreg_modrm_parsed;
#define NEED_notsup_modrm_getlq_vex_w_rmreg_modrm_parsed
#endif /* ... */


#if EMU86_EMULATE_CONFIG_WANT_XOP_TZMSK
	case 4: {
		/* TZMSK reg32, reg/mem32               8F RXB.09 0.dest.0.00 01 /4
		 * TZMSK reg64, reg/mem64               8F RXB.09 1.dest.0.00 01 /4 */
		u32 eflags_addend = 0;
#if LIBEMU86_CONFIG_WANT_64BIT
		if (op_flags & EMU86_F_VEX_W) {
			/* 64-bit */
			u64 temp, src;
			src = MODRM_GETRMQ();
			if (OVERFLOW_SSUB((s64)src, 1, (s64 *)&temp))
				eflags_addend |= EFLAGS_CF;
			temp &= ~src;
			VEX_SETREGQ(temp);
			eflags_addend |= emu86_geteflags_SFq(temp);
			eflags_addend |= emu86_geteflags_ZFq(temp);
		} else
#endif /* LIBEMU86_CONFIG_WANT_64BIT */
		{
			/* 32-bit */
			u32 temp, src;
			src = MODRM_GETRML();
			if (OVERFLOW_SSUB((s32)src, 1, (s32 *)&temp))
				eflags_addend |= EFLAGS_CF;
			temp &= ~src;
			VEX_SETREGL(temp);
			eflags_addend |= emu86_geteflags_SFl(temp);
			eflags_addend |= emu86_geteflags_ZFl(temp);
		}
		EMU86_MSKFLAGS(~(EFLAGS_OF | EFLAGS_SF | EFLAGS_ZF | EFLAGS_CF),
		               eflags_addend);
		goto done;
	}
#elif EMU86_EMULATE_CONFIG_CHECKERROR
	case 4:
		goto notsup_modrm_getlq_vex_w_rmreg_modrm_parsed;
#define NEED_notsup_modrm_getlq_vex_w_rmreg_modrm_parsed
#endif /* ... */


#if EMU86_EMULATE_CONFIG_WANT_XOP_BLCIC
	case 5: {
		/* BLCIC reg32, reg/mem32               8F RXB.09 0.dest.0.00 01 /5
		 * BLCIC reg64, reg/mem64               8F RXB.09 1.dest.0.00 01 /5 */
		u32 eflags_addend = 0;
#if LIBEMU86_CONFIG_WANT_64BIT
		if (op_flags & EMU86_F_VEX_W) {
			/* 64-bit */
			u64 temp, src;
			src = MODRM_GETRMQ();
			if (OVERFLOW_SADD((s64)src, 1, (s64 *)&temp))
				eflags_addend |= EFLAGS_CF;
			temp &= ~src;
			VEX_SETREGQ(temp);
			eflags_addend |= emu86_geteflags_SFq(temp);
			eflags_addend |= emu86_geteflags_ZFq(temp);
		} else
#endif /* LIBEMU86_CONFIG_WANT_64BIT */
		{
			/* 32-bit */
			u32 temp, src;
			src = MODRM_GETRML();
			if (OVERFLOW_SADD((s32)src, 1, (s32 *)&temp))
				eflags_addend |= EFLAGS_CF;
			temp &= ~src;
			VEX_SETREGL(temp);
			eflags_addend |= emu86_geteflags_SFl(temp);
			eflags_addend |= emu86_geteflags_ZFl(temp);
		}
		EMU86_MSKFLAGS(~(EFLAGS_OF | EFLAGS_SF | EFLAGS_ZF | EFLAGS_CF),
		               eflags_addend);
		goto done;
	}
#elif EMU86_EMULATE_CONFIG_CHECKERROR
	case 5:
		goto notsup_modrm_getlq_vex_w_rmreg_modrm_parsed;
#define NEED_notsup_modrm_getlq_vex_w_rmreg_modrm_parsed
#endif /* ... */


#if EMU86_EMULATE_CONFIG_WANT_XOP_BLSIC
	case 6: {
		/* BLSIC reg32, reg/mem32               8F RXB.09 0.dest.0.00 01 /6
		 * BLSIC reg64, reg/mem64               8F RXB.09 1.dest.0.00 01 /6 */
		u32 eflags_addend = 0;
#if LIBEMU86_CONFIG_WANT_64BIT
		if (op_flags & EMU86_F_VEX_W) {
			/* 64-bit */
			u64 temp, src;
			src = MODRM_GETRMQ();
			if (OVERFLOW_SSUB((s64)src, 1, (s64 *)&temp))
				eflags_addend |= EFLAGS_CF;
			temp |= ~src;
			VEX_SETREGQ(temp);
			eflags_addend |= emu86_geteflags_SFq(temp);
			eflags_addend |= emu86_geteflags_ZFq(temp);
		} else
#endif /* LIBEMU86_CONFIG_WANT_64BIT */
		{
			/* 32-bit */
			u32 temp, src;
			src = MODRM_GETRML();
			if (OVERFLOW_SSUB((s32)src, 1, (s32 *)&temp))
				eflags_addend |= EFLAGS_CF;
			temp |= ~src;
			VEX_SETREGL(temp);
			eflags_addend |= emu86_geteflags_SFl(temp);
			eflags_addend |= emu86_geteflags_ZFl(temp);
		}
		EMU86_MSKFLAGS(~(EFLAGS_OF | EFLAGS_SF | EFLAGS_ZF | EFLAGS_CF),
		               eflags_addend);
		goto done;
	}
#elif EMU86_EMULATE_CONFIG_CHECKERROR
	case 6:
		goto notsup_modrm_getlq_vex_w_rmreg_modrm_parsed;
#define NEED_notsup_modrm_getlq_vex_w_rmreg_modrm_parsed
#endif /* ... */


#if EMU86_EMULATE_CONFIG_WANT_XOP_T1MSKC
	case 7: {
		/* T1MSKC reg32, reg/mem32              8F RXB.09 0.dest.0.00 01 /7
		 * T1MSKC reg64, reg/mem64              8F RXB.09 1.dest.0.00 01 /7 */
		u32 eflags_addend = 0;
#if LIBEMU86_CONFIG_WANT_64BIT
		if (op_flags & EMU86_F_VEX_W) {
			/* 64-bit */
			u64 temp, src;
			src = MODRM_GETRMQ();
			if (OVERFLOW_SADD((s64)src, 1, (s64 *)&temp))
				eflags_addend |= EFLAGS_CF;
			temp |= ~src;
			VEX_SETREGQ(temp);
			eflags_addend |= emu86_geteflags_SFq(temp);
			eflags_addend |= emu86_geteflags_ZFq(temp);
		} else
#endif /* LIBEMU86_CONFIG_WANT_64BIT */
		{
			/* 32-bit */
			u32 temp, src;
			src = MODRM_GETRML();
			if (OVERFLOW_SADD((s32)src, 1, (s32 *)&temp))
				eflags_addend |= EFLAGS_CF;
			temp |= ~src;
			VEX_SETREGL(temp);
			eflags_addend |= emu86_geteflags_SFl(temp);
			eflags_addend |= emu86_geteflags_ZFl(temp);
		}
		EMU86_MSKFLAGS(~(EFLAGS_OF | EFLAGS_SF | EFLAGS_ZF | EFLAGS_CF),
		               eflags_addend);
		goto done;
	}
#elif EMU86_EMULATE_CONFIG_CHECKERROR
	case 6:
		goto notsup_modrm_getlq_vex_w_rmreg_modrm_parsed;
#define NEED_notsup_modrm_getlq_vex_w_rmreg_modrm_parsed
#endif /* ... */


	default:
		goto return_unknown_instruction_rmreg;
#define NEED_return_unknown_instruction_rmreg
	}
	break;
}
#endif /* EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_XOP_... */





#if (EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_XOP_BLCMSK || \
     EMU86_EMULATE_CONFIG_WANT_XOP_BLCI)
case EMU86_OPCODE_ENCODE_XOP(9, 0x02): {
	MODRM_DECODE();
	if unlikely((op_flags & EMU86_F_VEX_LL_M) != 0)
		goto return_unexpected_vex_ll_rmreg;
#define NEED_return_unexpected_vex_ll_rmreg
	switch (modrm.mi_reg) {

#if EMU86_EMULATE_CONFIG_WANT_XOP_BLCMSK
	case 1: {
		/* BLCMSK reg32, reg/mem32              8F RXB.09 0.dest.0.00 02 /1
		 * BLCMSK reg64, reg/mem64              8F RXB.09 1.dest.0.00 02 /1 */
		u32 eflags_addend = 0;
#if LIBEMU86_CONFIG_WANT_64BIT
		if (op_flags & EMU86_F_VEX_W) {
			/* 64-bit */
			u64 temp, src;
			src = MODRM_GETRMQ();
			if (OVERFLOW_SADD((s64)src, 1, (s64 *)&temp))
				eflags_addend |= EFLAGS_CF;
			temp ^= src;
			VEX_SETREGQ(temp);
			eflags_addend |= emu86_geteflags_SFq(temp);
			eflags_addend |= emu86_geteflags_ZFq(temp);
		} else
#endif /* LIBEMU86_CONFIG_WANT_64BIT */
		{
			/* 32-bit */
			u32 temp, src;
			src = MODRM_GETRML();
			if (OVERFLOW_SADD((s32)src, 1, (s32 *)&temp))
				eflags_addend |= EFLAGS_CF;
			temp ^= src;
			VEX_SETREGL(temp);
			eflags_addend |= emu86_geteflags_SFl(temp);
			eflags_addend |= emu86_geteflags_ZFl(temp);
		}
		EMU86_MSKFLAGS(~(EFLAGS_OF | EFLAGS_SF | EFLAGS_ZF | EFLAGS_CF),
		               eflags_addend);
		goto done;
	}
#elif EMU86_EMULATE_CONFIG_CHECKERROR
	case 1:
		goto notsup_modrm_getlq_vex_w_rmreg_modrm_parsed;
#define NEED_notsup_modrm_getlq_vex_w_rmreg_modrm_parsed
#endif /* ... */



#if EMU86_EMULATE_CONFIG_WANT_XOP_BLCI
	case 6: {
		/* BLCI reg32, reg/mem32                8F RXB.09 0.dest.0.00 02 /6
		 * BLCI reg64, reg/mem64                8F RXB.09 1.dest.0.00 02 /6 */
		u32 eflags_addend = 0;
#if LIBEMU86_CONFIG_WANT_64BIT
		if (op_flags & EMU86_F_VEX_W) {
			/* 64-bit */
			u64 temp, src;
			src = MODRM_GETRMQ();
			if (OVERFLOW_SADD((s64)src, 1, (s64 *)&temp))
				eflags_addend |= EFLAGS_CF;
			temp = src | ~temp;
			VEX_SETREGQ(temp);
			eflags_addend |= emu86_geteflags_SFq(temp);
			eflags_addend |= emu86_geteflags_ZFq(temp);
		} else
#endif /* LIBEMU86_CONFIG_WANT_64BIT */
		{
			/* 32-bit */
			u32 temp, src;
			src = MODRM_GETRML();
			if (OVERFLOW_SADD((s32)src, 1, (s32 *)&temp))
				eflags_addend |= EFLAGS_CF;
			temp = src | ~temp;
			VEX_SETREGL(temp);
			eflags_addend |= emu86_geteflags_SFl(temp);
			eflags_addend |= emu86_geteflags_ZFl(temp);
		}
		EMU86_MSKFLAGS(~(EFLAGS_OF | EFLAGS_SF | EFLAGS_ZF | EFLAGS_CF),
		               eflags_addend);
		goto done;
	}
#elif EMU86_EMULATE_CONFIG_CHECKERROR
	case 6:
		goto notsup_modrm_getlq_vex_w_rmreg_modrm_parsed;
#define NEED_notsup_modrm_getlq_vex_w_rmreg_modrm_parsed
#endif /* ... */



	default:
		goto return_unknown_instruction_rmreg;
#define NEED_return_unknown_instruction_rmreg
	}
	break;
}
#endif /* EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_XOP_... */






#if (EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_XOP_BEXTR_IMM)
case EMU86_OPCODE_ENCODE_XOP(0xa, 0x10): {
	union {
		u8 start;
		u8 len;
		u16 word;
	} imm;
	u32 eflags_addend;
	/* BEXTR reg32, reg/mem32, imm32        8F RXB.0A 0.1111.0.00 10 /r /id
	 * BEXTR reg64, reg/mem64, imm32        8F RXB.0A 1.1111.0.00 10 /r /id */
	if unlikely((op_flags & EMU86_F_VEX_VVVVV_M) != 0)
		goto return_unknown_instruction;
	MODRM_DECODE();
	if unlikely((op_flags & EMU86_F_VEX_LL_M) != 0)
		goto return_unexpected_vex_ll_rmreg;
#define NEED_return_unexpected_vex_ll_rmreg
	/* NOTE: Only the lower 2 bytes of the immediate operand are actually used.
	 *       As such, a 2-byte read is sufficient here, so-long as we increment
	 *       `pc' by the full 4 bytes.
	 * HINT: If x86 was a big-endian machine, this next line would say:
	 *       >> imm.word = UNALIGNED_GETBE16((u16 const *)(pc + 2)); */
	imm.word = UNALIGNED_GETLE16((u16 const *)pc);
	pc += 4;
	eflags_addend = 0;
#if LIBEMU86_CONFIG_WANT_64BIT
	if (op_flags & EMU86_F_VEX_W) {
		u64 value, result;
		if (imm.start >= 64)
			goto bextr_imm_write_dst_0;
		if (imm.len > 63)
			imm.len = 63;
		value  = MODRM_GETRMQ();
		result = (value >> imm.start) & (((u64)1 << imm.len) - 1);
		if (result == 0)
			eflags_addend |= EFLAGS_ZF;
		MODRM_SETREGQ(result);
	} else
#endif /* LIBEMU86_CONFIG_WANT_64BIT */
	{
		if (imm.start >= 32) {
#if LIBEMU86_CONFIG_WANT_64BIT
bextr_imm_write_dst_0:
			MODRM_SETREGQ(0);
#else /* LIBEMU86_CONFIG_WANT_64BIT */
			MODRM_SETREGL(0);
#endif /* !LIBEMU86_CONFIG_WANT_64BIT */
			eflags_addend |= EFLAGS_ZF; /* Result is 0 */
		} else {
			u32 value, result;
			if (imm.len > 31)
				imm.len = 31;
			value  = MODRM_GETRML();
			result = (value >> imm.start) & (((u32)1 << imm.len) - 1);
			if (result == 0)
				eflags_addend |= EFLAGS_ZF;
			MODRM_SETREGL(result);
		}
	}
	EMU86_MSKFLAGS(~(EFLAGS_ZF | EFLAGS_CF | EFLAGS_OF),
	               eflags_addend);
	goto done;
}
#endif /* EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_XOP_... */

}
EMU86_INTELLISENSE_END
