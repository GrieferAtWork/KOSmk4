/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifdef __INTELLISENSE__
#include "../emulate.c.inl"
#endif /* __INTELLISENSE__ */

EMU86_INTELLISENSE_BEGIN(bittest) {

#if EMU86_EMULATE_CONFIG_WANT_BITTEST || EMU86_EMULATE_CONFIG_CHECKERROR

#if EMU86_EMULATE_CONFIG_WANT_BITTEST
	bool nonzero;
	unsigned int bitno;
#endif /* EMU86_EMULATE_CONFIG_WANT_BITTEST */

case EMU86_OPCODE_ENCODE(0x0fa3):
#if EMU86_EMULATE_CONFIG_WANT_BITTEST
	/* 0F A3      BT r/m16, r16      Store selected bit in CF flag
	 * 0F A3      BT r/m32, r32      Store selected bit in CF flag
	 * 0F A3      BT r/m64, r64      Store selected bit in CF flag */
	MODRM_DECODE();
	bitno = MODRM_GETREGW();
do_bt_modrm:
	IF_64BIT(if (IS_64BIT()) {
		u64 temp = MODRM_GETRMQ();
		nonzero = (temp & (u64)1 << (bitno % 64)) != 0;
	} else) if (!IS_16BIT()) {
		u32 temp = MODRM_GETRML();
		nonzero = (temp & (u32)1 << (bitno % 32)) != 0;
	} else {
		u16 temp = MODRM_GETRMW();
		nonzero = (temp & (u16)1 << (bitno % 16)) != 0;
	}
set_cf_from_nonzero:
	EMU86_MSKFLAGS(~EFLAGS_CF, nonzero ? EFLAGS_CF : 0);
	goto done;
#else /* EMU86_EMULATE_CONFIG_WANT_BITTEST */
	goto notsup_modrm_getwlq;
#define NEED_notsup_modrm_getwlq
#endif /* !EMU86_EMULATE_CONFIG_WANT_BITTEST */


#if EMU86_EMULATE_CONFIG_WANT_BITTEST
#define DEFINE_BIT_TEST_AND_op(pred_oldval_mask)                                      \
	IF_64BIT(if (IS_64BIT()) {                                                        \
		u64 oldval, mask;                                                             \
		mask = (u64)1 << (bitno % 64);                                                \
		NIF_ONLY_MEMORY(                                                              \
		if (EMU86_MODRM_ISREG(modrm.mi_type)) {                                       \
			oldval = MODRM_GETRMREGQ();                                               \
			MODRM_SETRMREGQ(pred_oldval_mask(oldval, mask));                          \
		} else) {                                                                     \
			byte_t *addr = MODRM_MEMADDR();                                           \
			EMU86_WRITE_USER_MEMORY(addr, 8);                                         \
			for (;;) {                                                                \
				oldval = EMU86_MEMREADL(addr);                                        \
				if (EMU86_MEM_ATOMIC_CMPXCH_OR_WRITEQ(addr, oldval,                   \
				                                      pred_oldval_mask(oldval, mask), \
				                                      EMU86_HASLOCK()))               \
					break;                                                            \
				EMU86_EMULATE_LOOPHINT();                                             \
			}                                                                         \
		}                                                                             \
		nonzero = (oldval & mask) != 0;                                               \
	} else) if (!IS_16BIT()) {                                                        \
		u32 oldval, mask;                                                             \
		mask = (u32)1 << (bitno % 32);                                                \
		NIF_ONLY_MEMORY(                                                              \
		if (EMU86_MODRM_ISREG(modrm.mi_type)) {                                       \
			oldval = MODRM_GETRMREGL();                                               \
			MODRM_SETRMREGL(pred_oldval_mask(oldval, mask));                          \
		} else) {                                                                     \
			byte_t *addr = MODRM_MEMADDR();                                           \
			EMU86_WRITE_USER_MEMORY(addr, 4);                                         \
			for (;;) {                                                                \
				oldval = EMU86_MEMREADL(addr);                                        \
				if (EMU86_MEM_ATOMIC_CMPXCH_OR_WRITEL(addr, oldval,                   \
				                                      pred_oldval_mask(oldval, mask), \
				                                      EMU86_HASLOCK()))               \
					break;                                                            \
				EMU86_EMULATE_LOOPHINT();                                             \
			}                                                                         \
		}                                                                             \
		nonzero = (oldval & mask) != 0;                                               \
	} else {                                                                          \
		u16 oldval, mask;                                                             \
		mask = (u16)1 << (bitno % 16);                                                \
		NIF_ONLY_MEMORY(                                                              \
		if (EMU86_MODRM_ISREG(modrm.mi_type)) {                                       \
			oldval = MODRM_GETRMREGW();                                               \
			MODRM_SETRMREGW(pred_oldval_mask(oldval, mask));                          \
		} else) {                                                                     \
			byte_t *addr = MODRM_MEMADDR();                                           \
			EMU86_WRITE_USER_MEMORY(addr, 2);                                         \
			for (;;) {                                                                \
				oldval = EMU86_MEMREADW(addr);                                        \
				if (EMU86_MEM_ATOMIC_CMPXCH_OR_WRITEW(addr, oldval,                   \
				                                      pred_oldval_mask(oldval, mask), \
				                                      EMU86_HASLOCK()))               \
					break;                                                            \
				EMU86_EMULATE_LOOPHINT();                                             \
			}                                                                         \
		}                                                                             \
		nonzero = (oldval & mask) != 0;                                               \
	}
#endif /* EMU86_EMULATE_CONFIG_WANT_BITTEST */

case EMU86_OPCODE_ENCODE(0x0fbb):
	/*         0F BB /r     BTC r/m16, r16      Store selected bit in CF flag and complement.
	 *         0F BB /r     BTC r/m32, r32      Store selected bit in CF flag and complement.
	 * REX.W + 0F BB /r     BTC r/m64, r64      Store selected bit in CF flag and complement. */
#if EMU86_EMULATE_CONFIG_WANT_BITTEST
	MODRM_DECODE();
	bitno = MODRM_GETREGW();
do_btc_modrm:
#define PRED_COMPLEMENT(oldval, mask) ((oldval) ^ (mask))
	DEFINE_BIT_TEST_AND_op(PRED_COMPLEMENT);
#undef PRED_COMPLEMENT
	goto set_cf_from_nonzero;
#else /* EMU86_EMULATE_CONFIG_WANT_BITTEST */
	goto notsup_modrm_getsetwlq;
#define NEED_notsup_modrm_getsetwlq
#endif /* !EMU86_EMULATE_CONFIG_WANT_BITTEST */


case EMU86_OPCODE_ENCODE(0x0fb3):
	/*         0F B3 /r     BTR r/m16, r16      Store selected bit in CF flag and clear.
	 *         0F B3 /r     BTR r/m32, r32      Store selected bit in CF flag and clear.
	 * REX.W + 0F B3 /r     BTR r/m64, r64      Store selected bit in CF flag and clear. */
#if EMU86_EMULATE_CONFIG_WANT_BITTEST
	MODRM_DECODE();
	bitno = MODRM_GETREGW();
do_btr_modrm:
#define PRED_RESET(oldval, mask) ((oldval) & ~(mask))
	DEFINE_BIT_TEST_AND_op(PRED_RESET);
#undef PRED_RESET
	goto set_cf_from_nonzero;
#else /* EMU86_EMULATE_CONFIG_WANT_BITTEST */
	goto notsup_modrm_getsetwlq;
#define NEED_notsup_modrm_getsetwlq
#endif /* !EMU86_EMULATE_CONFIG_WANT_BITTEST */


case EMU86_OPCODE_ENCODE(0x0fab):
	/*         0F AB /r     BTS r/m16, r16      Store selected bit in CF flag and set.
	 *         0F AB /r     BTS r/m32, r32      Store selected bit in CF flag and set.
	 * REX.W + 0F AB /r     BTS r/m64, r64      Store selected bit in CF flag and set. */
#if EMU86_EMULATE_CONFIG_WANT_BITTEST
	MODRM_DECODE();
	bitno = MODRM_GETREGW();
do_bts_modrm:
#define PRED_SET(oldval, mask) ((oldval) | (mask))
	DEFINE_BIT_TEST_AND_op(PRED_SET);
#undef PRED_SET
	goto set_cf_from_nonzero;
#else /* EMU86_EMULATE_CONFIG_WANT_BITTEST */
	goto notsup_modrm_getsetwlq;
#define NEED_notsup_modrm_getsetwlq
#endif /* !EMU86_EMULATE_CONFIG_WANT_BITTEST */

#undef DEFINE_BIT_TEST_AND_op


case EMU86_OPCODE_ENCODE(0x0fba):
#if EMU86_EMULATE_CONFIG_WANT_BITTEST
	MODRM_DECODE();
	/* Take the bit number from *PC */
	bitno = *(u8 const *)pc;
	pc += 1;
	switch (modrm.mi_reg) {

	case 4:
		/*         0F BA /4 ib     BT r/m16, imm8      Store selected bit in CF flag.
		 *         0F BA /4 ib     BT r/m32, imm8      Store selected bit in CF flag.
		 * REX.W + 0F BA /4 ib     BT r/m64, imm8      Store selected bit in CF flag. */
		goto do_bt_modrm;

	case 5:
		/*         0F BA /5 ib     BTS r/m16, imm8      Store selected bit in CF flag and set.
		 *         0F BA /5 ib     BTS r/m32, imm8      Store selected bit in CF flag and set.
		 * REX.W + 0F BA /5 ib     BTS r/m64, imm8      Store selected bit in CF flag and set. */
		goto do_bts_modrm;

	case 6:
		/*         0F BA /6 ib     BTR r/m16, imm8      Store selected bit in CF flag and clear.
		 *         0F BA /6 ib     BTR r/m32, imm8      Store selected bit in CF flag and clear.
		 * REX.W + 0F BA /6 ib     BTR r/m64, imm8      Store selected bit in CF flag and clear. */
		goto do_btr_modrm;

	case 7:
		/*         0F BA /7 ib     BTC r/m16, imm8      Store selected bit in CF flag and complement.
		 *         0F BA /7 ib     BTC r/m32, imm8      Store selected bit in CF flag and complement.
		 * REX.W + 0F BA /7 ib     BTC r/m64, imm8      Store selected bit in CF flag and complement. */
		goto do_btc_modrm;

	default:
#define NEED_return_unknown_instruction_rmreg
		goto return_unknown_instruction_rmreg;
	}
	break;
#else /* EMU86_EMULATE_CONFIG_WANT_BITTEST */
	MODRM_DECODE();
#if LIBEMU86_CONFIG_WANT_64BIT
	if (modrm.mi_reg >= 8) {
		goto return_unknown_instruction_rmreg;
#define NEED_return_unknown_instruction_rmreg
	}
#endif /* LIBEMU86_CONFIG_WANT_64BIT */
	if (modrm.mi_reg >= 1 && modrm.mi_reg <= 3) {
		goto return_unknown_instruction_rmreg;
#define NEED_return_unknown_instruction_rmreg
	}
	if (modrm.mi_reg == 0) {
		MODRM_NOSUP_GETRMWLQ();
	} else {
		MODRM_NOSUP_GETSETRMWLQ();
	}
	goto return_unsupported_instruction_rmreg;
#define NEED_return_unsupported_instruction_rmreg
#endif /* !EMU86_EMULATE_CONFIG_WANT_BITTEST */

#endif /* EMU86_EMULATE_CONFIG_WANT_BITTEST || EMU86_EMULATE_CONFIG_CHECKERROR */

}
EMU86_INTELLISENSE_END
