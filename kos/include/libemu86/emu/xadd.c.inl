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

EMU86_INTELLISENSE_BEGIN(xadd) {

#define DEFINE_XADD_MODRM_reg_rm(bwlq, BWLQ, Nbits, Nbytes)                           \
	u##Nbits rhs, oldval, newval;                                                     \
	u32 eflags_addend = 0;                                                            \
	rhs = MODRM_GETREG##BWLQ();                                                       \
	NIF_ONLY_MEMORY(                                                                  \
	if (EMU86_MODRM_ISREG(modrm.mi_type)) {                                           \
		if unlikely(op_flags & EMU86_F_LOCK)                                          \
			goto return_unknown_instruction;                                          \
		oldval = MODRM_GETRMREG##BWLQ();                                              \
		MODRM_SETRMREG##BWLQ(oldval + rhs);                                           \
	} else) {                                                                         \
		byte_t *addr;                                                                 \
		addr = MODRM_MEMADDR();                                                       \
		EMU86_WRITE_USER_MEMORY(addr, Nbytes);                                        \
		oldval = EMU86_EMULATE_ATOMIC_FETCHADD##BWLQ(addr, rhs,                       \
		                                             (op_flags & EMU86_F_LOCK) != 0); \
	}                                                                                 \
	if (OVERFLOW_UADD(oldval, rhs, &newval))                                          \
		eflags_addend |= EFLAGS_OF | EFLAGS_CF;                                       \
	if (((oldval & 0xf) + (rhs & 0xf)) >= 0x10)                                       \
		eflags_addend |= EFLAGS_AF;                                                   \
	if ((s8)newval < 0)                                                               \
		eflags_addend |= EFLAGS_SF;                                                   \
	EMU86_MSKFLAGS(~(EFLAGS_OF | EFLAGS_CF | EFLAGS_SF |                              \
	                 EFLAGS_ZF | EFLAGS_PF | EFLAGS_AF),                              \
	               eflags_addend | emu86_geteflags_test##bwlq(newval));


case 0x0fc0: {
	/* 0F C0 /r      XADD r/m8, r8      Exchange r8 and r/m8; load sum into r/m8 */
	MODRM_DECODE();
	DEFINE_XADD_MODRM_reg_rm(b, B, 8, 1)
	goto done;
}


case 0x0fc1: {
	/* 0F C1 /r      XADD r/m16, r16      Exchange r16 and r/m16; load sum into r/m16
	 * 0F C1 /r      XADD r/m32, r32      Exchange r32 and r/m32; load sum into r/m32
	 * 0F C1 /r      XADD r/m64, r64      Exchange r64 and r/m64; load sum into r/m64 */
	MODRM_DECODE();
	IF_64BIT(if (IS_64BIT()) {
		DEFINE_XADD_MODRM_reg_rm(q, Q, 64, 8)
	} else) if (!IS_16BIT()) {
		DEFINE_XADD_MODRM_reg_rm(l, L, 32, 4)
	} else {
		DEFINE_XADD_MODRM_reg_rm(w, W, 16, 2)
	}
	goto done;
}

#undef DEFINE_XADD_MODRM_reg_rm

}
EMU86_INTELLISENSE_END
