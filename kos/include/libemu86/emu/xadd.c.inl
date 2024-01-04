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

EMU86_INTELLISENSE_BEGIN(xadd) {

#if EMU86_EMULATE_CONFIG_WANT_XADD
#define DEFINE_XADD_MODRM_reg_rm(bwlq, BWLQ, Nbits, Nbytes)                  \
	u##Nbits rhs, oldval, newval;                                            \
	u32 eflags_addend = 0;                                                   \
	rhs = MODRM_GETREG##BWLQ();                                              \
	NIF_ONLY_MEMORY(                                                         \
	if (EMU86_MODRM_ISREG(modrm.mi_type)) {                                  \
		oldval = MODRM_GETRMREG##BWLQ();                                     \
		MODRM_SETRMREG##BWLQ(oldval + rhs);                                  \
	} else) {                                                                \
		byte_t *addr;                                                        \
		addr = MODRM_MEMADDR();                                              \
		EMU86_WRITE_USER_MEMORY(addr, Nbytes);                               \
		oldval = EMU86_MEM_ATOMIC_FETCHADD##BWLQ(addr, rhs,                  \
		                                         EMU86_HASLOCK());           \
	}                                                                        \
	if (OVERFLOW_SADD((s##Nbits)oldval, (s##Nbits)rhs, (s##Nbits *)&newval)) \
		eflags_addend |= EFLAGS_OF;                                          \
	if (OVERFLOW_UADD(oldval, rhs, &newval))                                 \
		eflags_addend |= EFLAGS_CF;                                          \
	if (emu86_getflags_AF_add(oldval, rhs))                                  \
		eflags_addend |= EFLAGS_AF;                                          \
	EMU86_MSKFLAGS(~(EFLAGS_OF | EFLAGS_CF | EFLAGS_SF |                     \
	                 EFLAGS_ZF | EFLAGS_PF | EFLAGS_AF),                     \
	               eflags_addend | emu86_geteflags_test##bwlq(newval));


case EMU86_OPCODE_ENCODE(0x0fc0): {
	/* 0F C0 /r      XADD r/m8, r8      Exchange r8 and r/m8; load sum into r/m8 */
	MODRM_DECODE();
	DEFINE_XADD_MODRM_reg_rm(b, B, 8, 1)
	goto done;
}


case EMU86_OPCODE_ENCODE(0x0fc1): {
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
#elif EMU86_EMULATE_CONFIG_CHECKERROR
case EMU86_OPCODE_ENCODE(0x0fc0):
	goto notsup_modrm_getsetb;
#define NEED_notsup_modrm_getsetb
case EMU86_OPCODE_ENCODE(0x0fc1):
	goto notsup_modrm_getsetwlq;
#define NEED_notsup_modrm_getsetwlq
#endif /* ... */


}
EMU86_INTELLISENSE_END
