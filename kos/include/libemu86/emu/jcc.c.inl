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

EMU86_INTELLISENSE_BEGIN(jcc) {

#if !EMU86_EMULATE_CONFIG_ONLY_MEMORY

#if EMU86_EMULATE_CONFIG_WANT_JCC_DISP8
#define NEED_done_dont_set_pc
#define DEFINE_Jcc8(id, cond)                              \
	case EMU86_OPCODE_ENCODE(0x70 + id): {                 \
		s8 offset;                                         \
		u32 eflags = EMU86_GETFLAGS();                     \
		offset     = *(s8 const *)pc;                      \
		pc += 1;                                           \
		if (!(cond))                                       \
			goto done;                                     \
		{                                                  \
			EMU86_UREG_TYPE dest_ip;                       \
			dest_ip = REAL_IP() + offset;                  \
			IF_16BIT_OR_32BIT(                             \
			if (IS_16BIT() && !EMU86_F_IS64(op_flags))     \
				dest_ip &= 0xffff;)                        \
			EMU86_SETIPREG(dest_ip);                       \
		}                                                  \
		goto done_dont_set_pc;                             \
	}
#elif EMU86_EMULATE_CONFIG_CHECKERROR && !EMU86_EMULATE_CONFIG_ONLY_CHECKERROR_NO_BASIC
#define NEED_return_unsupported_instruction
#define DEFINE_Jcc8(id, cond)            \
	case EMU86_OPCODE_ENCODE(0x70 + id): \
		goto return_unsupported_instruction;
#else /* ... */
#define DEFINE_Jcc8(id, cond) /* nothing */
#endif /* !... */

#if EMU86_EMULATE_CONFIG_WANT_JCC_DISP32
#define NEED_done_dont_set_pc
#define DEFINE_Jcc32(id, cond)                         \
	case EMU86_OPCODE_ENCODE(0x0f80 + id): {           \
		s32 offset;                                    \
		u32 eflags = EMU86_GETFLAGS();                 \
		IF_16BIT_OR_32BIT(if (IS_16BIT()) {            \
			offset = (s32)(s16)UNALIGNED_GETLE16(pc);  \
			pc += 2;                                   \
		} else) {                                      \
			offset = (s32)UNALIGNED_GETLE32(pc);       \
			pc += 4;                                   \
		}                                              \
		if (!(cond))                                   \
			goto done;                                 \
		{                                              \
			EMU86_UREG_TYPE dest_ip;                   \
			dest_ip = REAL_IP() + offset;              \
			IF_16BIT_OR_32BIT(                         \
			if (IS_16BIT() && !EMU86_F_IS64(op_flags)) \
				dest_ip &= 0xffff;)                    \
			EMU86_SETIPREG(dest_ip);                   \
		}                                              \
		goto done_dont_set_pc;                         \
	}
#elif EMU86_EMULATE_CONFIG_CHECKERROR && !EMU86_EMULATE_CONFIG_ONLY_CHECKERROR_NO_BASIC
#define NEED_return_unsupported_instruction
#define DEFINE_Jcc32(id, cond)               \
	case EMU86_OPCODE_ENCODE(0x0f80 + id): \
		goto return_unsupported_instruction;
#else /* ... */
#define DEFINE_Jcc32(id, cond) /* nothing */
#endif /* !... */

#define DEFINE_Jcc(id, cond) \
	DEFINE_Jcc8(id, cond)    \
	DEFINE_Jcc32(id, cond)


	/* 0F 80 cd     JO rel32       Jump near if overflow (OF=1).
	 * 0F 80 cw     JO rel16       Jump near if overflow (OF=1). Not supported in 64-bit mode.
	 *    70 cb     JO rel8        Jump short if overflow (OF=1). */
	DEFINE_Jcc(0x0, eflags & EFLAGS_OF)

	/* 0F 81 cd     JNO rel32      Jump near if not overflow (OF=0).
	 * 0F 81 cw     JNO rel16      Jump near if not overflow (OF=0). Not supported in 64-bit mode.
	 *    71 cb     JNO rel8       Jump short if not overflow (OF=0). */
	DEFINE_Jcc(0x1, !(eflags & EFLAGS_OF))

	/* 0F 82 cd     JB rel32       Jump near if below (CF=1).
	 * 0F 82 cd     JC rel32       Jump near if carry (CF=1).
	 * 0F 82 cd     JNAE rel32     Jump near if not above or equal (CF=1).
	 * 0F 82 cw     JB rel16       Jump near if below (CF=1). Not supported in 64-bit mode.
	 * 0F 82 cw     JC rel16       Jump near if carry (CF=1). Not supported in 64-bit mode.
	 * 0F 82 cw     JNAE rel16     Jump near if not above or equal (CF=1). Not supported in 64-bit mode.
	 *    72 cb     JB rel8        Jump short if below (CF=1).
	 *    72 cb     JC rel8        Jump short if carry (CF=1).
	 *    72 cb     JNAE rel8      Jump short if not above or equal (CF=1). */
	DEFINE_Jcc(0x2, eflags & EFLAGS_CF)

	/* 0F 83 cd     JAE rel32      Jump near if above or equal (CF=0).
	 * 0F 83 cd     JNB rel32      Jump near if not below (CF=0).
	 * 0F 83 cd     JNC rel32      Jump near if not carry (CF=0).
	 * 0F 83 cw     JAE rel16      Jump near if above or equal (CF=0). Not supported in 64-bit mode.
	 * 0F 83 cw     JNB rel16      Jump near if not below (CF=0). Not supported in 64-bit mode.
	 * 0F 83 cw     JNC rel16      Jump near if not carry (CF=0). Not supported in 64-bit mode.
	 *    73 cb     JAE rel8       Jump short if above or equal (CF=0).
	 *    73 cb     JNB rel8       Jump short if not below (CF=0).
	 *    73 cb     JNC rel8       Jump short if not carry (CF=0). */
	DEFINE_Jcc(0x3, !(eflags & EFLAGS_CF))

	/* 0F 84 cd     JE rel32       Jump near if equal (ZF=1).
	 * 0F 84 cd     JZ rel32       Jump near if 0 (ZF=1).
	 * 0F 84 cw     JE rel16       Jump near if equal (ZF=1). Not supported in 64-bit mode.
	 * 0F 84 cw     JZ rel16       Jump near if 0 (ZF=1). Not supported in 64-bit mode.
	 *    74 cb     JE rel8        Jump short if equal (ZF=1).
	 *    74 cb     JZ rel8        Jump short if zero (ZF = 1). */
	DEFINE_Jcc(0x4, eflags & EFLAGS_ZF)

	/* 0F 85 cd     JNE rel32      Jump near if not equal (ZF=0).
	 * 0F 85 cd     JNZ rel32      Jump near if not zero (ZF=0).
	 * 0F 85 cw     JNE rel16      Jump near if not equal (ZF=0). Not supported in 64-bit mode.
	 * 0F 85 cw     JNZ rel16      Jump near if not zero (ZF=0). Not supported in 64-bit mode.
	 *    75 cb     JNE rel8       Jump short if not equal (ZF=0).
	 *    75 cb     JNZ rel8       Jump short if not zero (ZF=0). */
	DEFINE_Jcc(0x5, !(eflags & EFLAGS_ZF))

	/* 0F 86 cd     JBE rel32      Jump near if below or equal (CF=1 or ZF=1).
	 * 0F 86 cd     JNA rel32      Jump near if not above (CF=1 or ZF=1).
	 * 0F 86 cw     JBE rel16      Jump near if below or equal (CF=1 or ZF=1). Not supported in 64-bit mode.
	 * 0F 86 cw     JNA rel16      Jump near if not above (CF=1 or ZF=1). Not supported in 64-bit mode.
	 *    76 cb     JBE rel8       Jump short if below or equal (CF=1 or ZF=1).
	 *    76 cb     JNA rel8       Jump short if not above (CF=1 or ZF=1). */
	DEFINE_Jcc(0x6, eflags & (EFLAGS_CF | EFLAGS_ZF))

	/* 0F 87 cd     JA rel32       Jump near if above (CF=0 and ZF=0).
	 * 0F 87 cd     JNBE rel32     Jump near if not below or equal (CF=0 and ZF=0).
	 * 0F 87 cw     JA rel16       Jump near if above (CF=0 and ZF=0). Not supported in 64-bit mode.
	 * 0F 87 cw     JNBE rel16     Jump near if not below or equal (CF=0 and ZF=0). Not supported in 64-bit mode.
	 *    77 cb     JA rel8        Jump short if above (CF=0 and ZF=0).
	 *    77 cb     JNBE rel8      Jump short if not below or equal (CF=0 and ZF=0). */
	DEFINE_Jcc(0x7, !(eflags & (EFLAGS_CF | EFLAGS_ZF)))

	/* 0F 88 cd     JS rel32       Jump near if sign (SF=1).
	 * 0F 88 cw     JS rel16       Jump near if sign (SF=1). Not supported in 64-bit mode.
	 *    78 cb     JS rel8        Jump short if sign (SF=1). */
	DEFINE_Jcc(0x8, eflags & EFLAGS_SF)

	/* 0F 89 cd     JNS rel32      Jump near if not sign (SF=0).
	 * 0F 89 cw     JNS rel16      Jump near if not sign (SF=0). Not supported in 64-bit mode.
	 *    79 cb     JNS rel8       Jump short if not sign (SF=0). */
	DEFINE_Jcc(0x9, !(eflags & EFLAGS_SF))

	/* 0F 8A cd     JP rel32       Jump near if parity (PF=1).
	 * 0F 8A cd     JPE rel32      Jump near if parity even (PF=1).
	 * 0F 8A cw     JP rel16       Jump near if parity (PF=1). Not supported in 64-bit mode.
	 * 0F 8A cw     JPE rel16      Jump near if parity even (PF=1). Not supported in 64-bit mode.
	 *    7A cb     JP rel8        Jump short if parity (PF=1).
	 *    7A cb     JPE rel8       Jump short if parity even (PF=1). */
	DEFINE_Jcc(0xa, eflags & EFLAGS_PF)

	/* 0F 8B cd     JNP rel32      Jump near if not parity (PF=0).
	 * 0F 8B cd     JPO rel32      Jump near if parity odd (PF=0).
	 * 0F 8B cw     JNP rel16      Jump near if not parity (PF=0). Not supported in 64-bit mode.
	 * 0F 8B cw     JPO rel16      Jump near if parity odd (PF=0). Not supported in 64-bit mode.
	 *    7B cb     JNP rel8       Jump short if not parity (PF=0).
	 *    7B cb     JPO rel8       Jump short if parity odd (PF=0). */
	DEFINE_Jcc(0xb, !(eflags & EFLAGS_PF))

	/* 0F 8C cd     JL rel32       Jump near if less (SF!=OF).
	 * 0F 8C cd     JNGE rel32     Jump near if not greater or equal (SF!=OF).
	 * 0F 8C cw     JL rel16       Jump near if less (SF!=OF). Not supported in 64-bit mode.
	 * 0F 8C cw     JNGE rel16     Jump near if not greater or equal (SF!=OF). Not supported in 64-bit mode.
	 *    7C cb     JL rel8        Jump short if less (SF!=OF).
	 *    7C cb     JNGE rel8      Jump short if not greater or equal (SF!=OF). */
	DEFINE_Jcc(0xc, !!(eflags & EFLAGS_SF) !=
	                !!(eflags & EFLAGS_OF))

	/* 0F 8D cd     JGE rel32      Jump near if greater or equal (SF=OF).
	 * 0F 8D cd     JNL rel32      Jump near if not less (SF=OF).
	 * 0F 8D cw     JGE rel16      Jump near if greater or equal (SF=OF). Not supported in 64-bit mode.
	 * 0F 8D cw     JNL rel16      Jump near if not less (SF=OF). Not supported in 64-bit mode.
	 *    7D cb     JGE rel8       Jump short if greater or equal (SF=OF).
	 *    7D cb     JNL rel8       Jump short if not less (SF=OF). */
	DEFINE_Jcc(0xd, !!(eflags & EFLAGS_SF) ==
	                !!(eflags & EFLAGS_OF))

	/* 0F 8E cd     JLE rel32      Jump near if less or equal (ZF=1 or SF!=OF).
	 * 0F 8E cd     JNG rel32      Jump near if not greater (ZF=1 or SF!=OF).
	 * 0F 8E cw     JLE rel16      Jump near if less or equal (ZF=1 or SF!=OF). Not supported in 64-bit mode.
	 * 0F 8E cw     JNG rel16      Jump near if not greater (ZF=1 or SF!=OF). Not supported in 64-bit mode.
	 *    7E cb     JLE rel8       Jump short if less or equal (ZF=1 or SF!=OF).
	 *    7E cb     JNG rel8       Jump short if not greater (ZF=1 or SF!=OF). */
	DEFINE_Jcc(0xe, (eflags & EFLAGS_ZF) ||
	                (!!(eflags & EFLAGS_SF) !=
	                 !!(eflags & EFLAGS_OF)))

	/* 0F 8F cd     JG rel32       Jump near if greater (ZF=0 and SF=OF).
	 * 0F 8F cd     JNLE rel32     Jump near if not less or equal (ZF=0 and SF=OF).
	 * 0F 8F cw     JG rel16       Jump near if greater (ZF=0 and SF=OF). Not supported in 64-bit mode.
	 * 0F 8F cw     JNLE rel16     Jump near if not less or equal (ZF=0 and SF=OF). Not supported in 64-bit mode.
	 *    7F cb     JG rel8        Jump short if greater (ZF=0 and SF=OF).
	 *    7F cb     JNLE rel8      Jump short if not less or equal (ZF=0 and SF=OF). */
	DEFINE_Jcc(0xf, !(eflags & EFLAGS_ZF) &&
	                (!!(eflags & EFLAGS_SF) ==
	                             !!(eflags & EFLAGS_OF)))

#undef DEFINE_Jcc8
#undef DEFINE_Jcc32
#undef DEFINE_Jcc


#if EMU86_EMULATE_CONFIG_WANT_JCXZ
case EMU86_OPCODE_ENCODE(0xe3): {
	/* E3 cb     JCXZ rel8      Jump short if CX register is 0. Not supported in 64-bit mode.
	 * E3 cb     JECXZ rel8     Jump short if ECX register is 0.
	 * E3 cb     JRCXZ rel8     Jump short if RCX register is 0. */
	s8 offset;
	offset = *(s8 const *)pc;
	pc += 1;
	EMU86_ADDRSIZE_SWITCH({
		/* 64-bit */
		if (EMU86_GETRCX() != 0)
			goto done;
	}, {
		/* 32-bit */
		if (EMU86_GETECX() != 0)
			goto done;
	}, {
		/* 16-bit */
		if (EMU86_GETCX() != 0)
			goto done;
	});
	{
		EMU86_UREG_TYPE dest_ip;
		dest_ip = REAL_IP() + offset;
		EMU86_SETIPREG(dest_ip);
	}
	goto done_dont_set_pc;
#define NEED_done_dont_set_pc
}
#elif EMU86_EMULATE_CONFIG_CHECKERROR && !EMU86_EMULATE_CONFIG_ONLY_CHECKERROR_NO_BASIC
case EMU86_OPCODE_ENCODE(0xe3):
	goto return_unsupported_instruction;
#define NEED_return_unsupported_instruction
#endif /* ... */

#endif /* !EMU86_EMULATE_CONFIG_ONLY_MEMORY */

}
EMU86_INTELLISENSE_END
