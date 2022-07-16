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

EMU86_INTELLISENSE_BEGIN(xchg) {

#if EMU86_EMULATE_CONFIG_WANT_XCHG_RM
#if EMU86_EMULATE_CONFIG_IGNORE_LOCK
#define XCHG_IS_ATOMIC() 0
#elif EMU86_EMULATE_CONFIG_ATOMIC_XCHG_REQUIRES_LOCK
#define XCHG_IS_ATOMIC() EMU86_HASLOCK()
#else /* ... */
#define XCHG_IS_ATOMIC() 1
#endif /* !... */

#define DEFINE_XCHG_modrm(BWLQ, Nbits, Nbytes)                 \
	u##Nbits reg_operand, oldval;                              \
	reg_operand = MODRM_GETREG##BWLQ();                        \
	NIF_ONLY_MEMORY(                                           \
	if (EMU86_MODRM_ISREG(modrm.mi_type)) {                    \
		oldval = MODRM_GETRMREG##BWLQ();                       \
		MODRM_SETRMREG##BWLQ(reg_operand);                     \
	} else) {                                                  \
		byte_t *addr;                                          \
		addr = MODRM_MEMADDR();                                \
		EMU86_WRITE_USER_MEMORY(addr, Nbytes);                 \
		oldval = EMU86_MEM_ATOMIC_XCH##BWLQ(addr, reg_operand, \
		                                    XCHG_IS_ATOMIC()); \
	}                                                          \
	MODRM_SETREG##BWLQ(oldval);

case EMU86_OPCODE_ENCODE(0x86): {
	/* 86 /r      XCHG r/m8, r8      Exchange r8 (byte register) with byte from r/m8 */
	/* 86 /r      XCHG r8, r/m8      Exchange byte from r/m8 with r8 (byte register) */
	MODRM_DECODE();
	DEFINE_XCHG_modrm(B, 8, 1)
	goto done;
}

case EMU86_OPCODE_ENCODE(0x87): {
	/* 87 /r      XCHG r/m16, r16      Exchange r16 with word from r/m16
	 * 87 /r      XCHG r16, r/m16      Exchange word from r/m16 with r16
	 * 87 /r      XCHG r/m32, r32      Exchange r32 with doubleword from r/m32
	 * 87 /r      XCHG r32, r/m32      Exchange doubleword from r/m32 with r32
	 * 87 /r      XCHG r/m64, r64      Exchange r64 with quadword from r/m64
	 * 87 /r      XCHG r64, r/m64      Exchange quadword from r/m64 with r64 */
	MODRM_DECODE();
	IF_64BIT(if (IS_64BIT()) {
		DEFINE_XCHG_modrm(Q, 64, 8)
	} else) if (!IS_16BIT()) {
		DEFINE_XCHG_modrm(L, 32, 4)
	} else {
		DEFINE_XCHG_modrm(W, 16, 2)
	}
	goto done;
}
#elif EMU86_EMULATE_CONFIG_CHECKERROR
case EMU86_OPCODE_ENCODE(0x86):
	goto notsup_modrm_getsetb;
#define NEED_notsup_modrm_getsetb
case EMU86_OPCODE_ENCODE(0x87):
	goto notsup_modrm_getsetwlq;
#define NEED_notsup_modrm_getsetwlq
#endif /* ... */


/* Allow the user to override the behavior of `pause' */
#ifndef EMU86_EMULATE_PAUSE
#define EMU86_EMULATE_PAUSE() EMU86_EMULATE_LOOPHINT()
#endif /* !EMU86_EMULATE_PAUSE */


#if !EMU86_EMULATE_CONFIG_ONLY_MEMORY
#if EMU86_EMULATE_CONFIG_WANT_NOP || EMU86_EMULATE_CONFIG_WANT_PAUSE
#define HAVE_OPCODE_90
case EMU86_OPCODE_ENCODE(0x90):
	/* nop */
#if EMU86_EMULATE_CONFIG_WANT_PAUSE
	if (op_flags & EMU86_F_REP) {
		EMU86_EMULATE_PAUSE(); /* pause */
		goto done;
	}
#endif /* EMU86_EMULATE_CONFIG_WANT_PAUSE */
#if EMU86_EMULATE_CONFIG_WANT_NOP || EMU86_EMULATE_CONFIG_WANT_XCHG_REG
	goto done;
#else /* EMU86_EMULATE_CONFIG_WANT_NOP || EMU86_EMULATE_CONFIG_WANT_XCHG_REG */
	goto return_unsupported_instruction;
#define NEED_return_unsupported_instruction
#endif /* !EMU86_EMULATE_CONFIG_WANT_NOP || EMU86_EMULATE_CONFIG_WANT_XCHG_REG */
#elif (EMU86_EMULATE_CONFIG_CHECKERROR &&                \
       !EMU86_EMULATE_CONFIG_ONLY_CHECKERROR_NO_BASIC && \
       !EMU86_EMULATE_CONFIG_WANT_XCHG_REG)
#define HAVE_OPCODE_90
case EMU86_OPCODE_ENCODE(0x90):
	goto return_unsupported_instruction;
#define NEED_return_unsupported_instruction
#endif /* ... */


#if EMU86_EMULATE_CONFIG_WANT_XCHG_REG
#define DEFINE_XCHG_reg(BWLQ, Nbits, regno, AX) \
	u##Nbits reg_operand, oldval;               \
	reg_operand = EMU86_GETREG##BWLQ(regno);    \
	oldval      = EMU86_GET##AX();              \
	EMU86_SET##AX(reg_operand);                 \
	EMU86_SETREG##BWLQ(regno, oldval);

#ifdef HAVE_OPCODE_90
case EMU86_OPCODE_ENCODE(0x91) ... EMU86_OPCODE_ENCODE(0x97):
#else /* HAVE_OPCODE_90 */
case EMU86_OPCODE_ENCODE(0x90) ... EMU86_OPCODE_ENCODE(0x97):
#endif /* !HAVE_OPCODE_90 */
{
	/*         90+rw     XCHG AX, r16      Exchange r16 with AX.
	 *         90+rw     XCHG r16, AX      Exchange AX with r16.
	 *         90+rd     XCHG EAX, r32     Exchange r32 with EAX.
	 * REX.W + 90+rd     XCHG RAX, r64     Exchange r64 with RAX.
	 *         90+rd     XCHG r32, EAX     Exchange EAX with r32.
	 * REX.W + 90+rd     XCHG r64, RAX     Exchange RAX with r64. */
	u8 regno;
	regno = tiny_opcode - EMU86_OPCODE_ENCODE(0x90);
#if LIBEMU86_CONFIG_WANT_64BIT
	if (op_flags & EMU86_F_REX_B)
		regno |= 0x8;
	if (IS_64BIT()) {
		DEFINE_XCHG_reg(Q, 64, regno, RAX)
	} else
#endif /* LIBEMU86_CONFIG_WANT_64BIT */
	if (!IS_16BIT()) {
		DEFINE_XCHG_reg(L, 32, regno, EAX)
	} else {
		DEFINE_XCHG_reg(W, 16, regno, AX)
	}
	goto done;
}
#undef DEFINE_XCHG_reg
#elif (EMU86_EMULATE_CONFIG_CHECKERROR && !EMU86_EMULATE_CONFIG_ONLY_CHECKERROR_NO_BASIC)
#ifdef HAVE_OPCODE_90
case EMU86_OPCODE_ENCODE(0x91) ... EMU86_OPCODE_ENCODE(0x97):
#else /* HAVE_OPCODE_90 */
case EMU86_OPCODE_ENCODE(0x90) ... EMU86_OPCODE_ENCODE(0x97):
#endif /* !HAVE_OPCODE_90 */
	goto return_unsupported_instruction;
#define NEED_return_unsupported_instruction
#endif /* ... */

#endif /* !EMU86_EMULATE_CONFIG_ONLY_MEMORY */


#undef DEFINE_XCHG_modrm
#undef XCHG_IS_ATOMIC

}
EMU86_INTELLISENSE_END
