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

EMU86_INTELLISENSE_BEGIN(misc) {


case 0xfe:
	MODRM_DECODE();
	switch (modrm.mi_reg) {

#define DO_INC_modrm(bwlq, BWLQ, Nbits, Nbytes)                                       \
	u##Nbits oldval, newval;                                                          \
	u32 eflags_addend = 0;                                                            \
	NIF_ONLY_MEMORY(                                                                  \
	if (EMU86_MODRM_ISREG(modrm.mi_type)) {                                           \
		if unlikely(op_flags &EMU86_F_LOCK)                                           \
			goto return_unknown_instruction;                                          \
		oldval = MODRM_GETRMREG##BWLQ();                                              \
		MODRM_SETRMREG##BWLQ((u##Nbits)(oldval + 1));                                 \
	} else) {                                                                         \
		byte_t *addr = MODRM_MEMADDR();                                               \
		EMU86_WRITE_USER_MEMORY(addr, Nbytes);                                        \
		oldval = EMU86_EMULATE_ATOMIC_FETCHADD##BWLQ(addr, 1,                         \
		                                             (op_flags & EMU86_F_LOCK) != 0); \
	}                                                                                 \
	if (OVERFLOW_UADD(oldval, 1, &newval))                                            \
		eflags_addend |= EFLAGS_OF;                                                   \
	if ((oldval & 0xf) == 0xf)                                                        \
		eflags_addend |= EFLAGS_AF;                                                   \
	EMU86_MSKFLAGS(~(EFLAGS_OF | EFLAGS_SF | EFLAGS_ZF | EFLAGS_PF | EFLAGS_AF),      \
	               eflags_addend | emu86_geteflags_test##bwlq(newval));

#define DO_DEC_modrm(bwlq, BWLQ, Nbits, Nbytes)                                       \
	u##Nbits oldval, newval;                                                          \
	u32 eflags_addend = EFLAGS_AF;                                                    \
	NIF_ONLY_MEMORY(                                                                  \
	if (EMU86_MODRM_ISREG(modrm.mi_type)) {                                           \
		if unlikely(op_flags &EMU86_F_LOCK)                                           \
			goto return_unknown_instruction;                                          \
		oldval = MODRM_GETRMREG##BWLQ();                                              \
		MODRM_SETRMREG##BWLQ(oldval - 1);                                             \
	} else) {                                                                         \
		byte_t *addr = MODRM_MEMADDR();                                               \
		EMU86_WRITE_USER_MEMORY(addr, Nbytes);                                        \
		oldval = EMU86_EMULATE_ATOMIC_FETCHSUB##BWLQ(addr, 1,                         \
		                                             (op_flags & EMU86_F_LOCK) != 0); \
	}                                                                                 \
	if (OVERFLOW_USUB(oldval, 1, &newval))                                            \
		eflags_addend |= EFLAGS_OF;                                                   \
	EMU86_MSKFLAGS(~(EFLAGS_OF | EFLAGS_SF | EFLAGS_ZF | EFLAGS_PF | EFLAGS_AF),      \
	               eflags_addend | emu86_geteflags_test##bwlq(newval));



	case 0: {
		/* FE /0      INC r/m8      Increment r/m byte by 1 */
		DO_INC_modrm(b, B, 8, 1)
		goto done;
	}

	case 1: {
		/* FE /1      DEC r/m8      Decrement r/m8 by 1 */
		DO_DEC_modrm(b, B, 8, 1)
		goto done;
	}

	default:
		break;
	}
	goto return_unknown_instruction;


case 0xff:
	MODRM_DECODE();
	switch (modrm.mi_reg) {

	case 0: {
		/* FF /0      INC r/m16      Increment r/m byte by 1
		 * FF /0      INC r/m32      Increment r/m byte by 1
		 * FF /0      INC r/m64      Increment r/m byte by 1 */
		IF_64BIT(if (IS_64BIT()) {
			DO_INC_modrm(q, Q, 64, 8)
		} else) if (!IS_16BIT()) {
			DO_INC_modrm(l, L, 32, 4)
		} else {
			DO_INC_modrm(w, W, 16, 2)
		}
		goto done;
	}

	case 1: {
		/* FF /1      DEC r/m16      Decrement r/m byte by 1
		 * FF /1      DEC r/m32      Decrement r/m byte by 1
		 * FF /1      DEC r/m64      Decrement r/m byte by 1 */
		IF_64BIT(if (IS_64BIT()) {
			DO_DEC_modrm(q, Q, 64, 8)
		} else) if (!IS_16BIT()) {
			DO_DEC_modrm(l, L, 32, 4)
		} else {
			DO_DEC_modrm(w, W, 16, 2)
		}
		goto done;
	}

	default:
		break;
	}
	goto return_unknown_instruction;

#undef DO_DEC_modrm
#undef DO_INC_modrm


}
EMU86_INTELLISENSE_END
