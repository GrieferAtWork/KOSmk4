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

EMU86_INTELLISENSE_BEGIN(cmpxchg) {

#if EMU86_EMULATE_CONFIG_WANT_CMPXCHG

/* Perform a CMPXCHG operation on MODRM.RM */
#define DEFINE_CMPXCHG_modrm_rm(bwlq, BWLQ, Nbits, Nbytes, get_want_oldval)   \
	u##Nbits real_oldval, want_oldval, newval;                                \
	want_oldval = get_want_oldval;                                            \
	newval      = MODRM_GETREG##BWLQ();                                       \
	NIF_ONLY_MEMORY(                                                          \
	if (EMU86_MODRM_ISREG(modrm.mi_type)) {                                   \
		real_oldval = MODRM_GETRMREG##BWLQ();                                 \
		if (real_oldval == want_oldval)                                       \
			MODRM_SETRMREG##BWLQ(newval);                                     \
	} else) {                                                                 \
		byte_t *addr = MODRM_MEMADDR();                                       \
		EMU86_WRITE_USER_MEMORY(addr, Nbytes);                                \
		real_oldval = EMU86_MEM_ATOMIC_CMPXCH##BWLQ(addr, want_oldval,        \
		                                            newval, EMU86_HASLOCK()); \
	}                                                                         \
	EMU86_MSKFLAGS(~EMU86_GETEFLAGS_CMP_MASK,                                 \
	               emu86_geteflags_cmp##bwlq(want_oldval,                     \
	                                         real_oldval));


case EMU86_OPCODE_ENCODE(0x0fb0): {
	/* 0F B0 /r      CMPXCHG r/m8,r8      Compare  AL with r/m8.  If equal, ZF is  set and r8 is
	 *                                    loaded into r/m8. Else, clear ZF and load r/m8 into AL */
	MODRM_DECODE();
	DEFINE_CMPXCHG_modrm_rm(b, B, 8, 1, EMU86_GETAL())
	goto done;
}


case EMU86_OPCODE_ENCODE(0x0fb1): {
	/* 0F B1 /r      CMPXCHG r/m16,r16    Compare  AX with  r/m16. If equal,  ZF is set  and r16 is
	 *                                    loaded into r/m16. Else, clear ZF and load r/m16 into AX.
	 * 0F B1 /r      CMPXCHG r/m32,r32    Compare  EAX with  r/m32. If equal,  ZF is set  and r32 is
	 *                                    loaded into r/m32. Else, clear ZF and load r/m32 into EAX.
	 * 0F B1 /r      CMPXCHG r/m64,r64    Compare  RAX with  r/m64. If equal,  ZF is set  and r64 is
	 *                                    loaded into r/m64. Else, clear ZF and load r/m64 into RAX. */
	MODRM_DECODE();
	IF_64BIT(if (IS_64BIT()) {
		DEFINE_CMPXCHG_modrm_rm(q, Q, 64, 8, EMU86_GETRAX())
	} else) if (!IS_16BIT()) {
		DEFINE_CMPXCHG_modrm_rm(l, L, 32, 4, EMU86_GETEAX())
	} else {
		DEFINE_CMPXCHG_modrm_rm(w, W, 16, 2, EMU86_GETAX())
	}
	goto done;
}

#undef DEFINE_CMPXCHG_modrm_rm
#endif /* EMU86_EMULATE_CONFIG_WANT_CMPXCHG */

}
EMU86_INTELLISENSE_END
