/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifdef __INTELLISENSE__
#include "../emulate.c.inl"
#endif /* __INTELLISENSE__ */

EMU86_INTELLISENSE_BEGIN(cmovcc) {

	/* Define CMOVcc and SETcc instructions */
#if EMU86_EMULATE_CONFIG_WANT_SETCC
#define DEFINE_SETcc(id, cond_expr)          \
	case EMU86_OPCODE_ENCODE(0x0f90 + id): { \
		u32 eflags;                          \
		MODRM_DECODE();                      \
		eflags = EMU86_GETFLAGS();           \
		MODRM_SETRMB((cond_expr) ? 1 : 0);   \
		goto done;                           \
	}
#elif EMU86_EMULATE_CONFIG_CHECKERROR
#define DEFINE_SETcc(id, cond_expr)        \
	case EMU86_OPCODE_ENCODE(0x0f90 + id): \
		goto notsup_modrm_getwlq;
#define NEED_notsup_modrm_getwlq
#else
#define DEFINE_SETcc(id, cond_expr) /* nothing */
#endif

#if EMU86_EMULATE_CONFIG_WANT_CMOVCC
#define DEFINE_CMOVcc(id, cond_expr)         \
	case EMU86_OPCODE_ENCODE(0x0f40 + id): { \
		u32 eflags;                          \
		MODRM_DECODE();                      \
		eflags = EMU86_GETFLAGS();           \
		if (cond_expr) {                     \
			IF_64BIT(if (IS_64BIT()) {       \
				u64 value = MODRM_GETRMQ();  \
				MODRM_SETREGQ(value);        \
			} else) if (!IS_16BIT()) {       \
				u32 value = MODRM_GETRML();  \
				MODRM_SETREGL(value);        \
			} else {                         \
				u16 value = MODRM_GETRMW();  \
				MODRM_SETREGW(value);        \
			}                                \
		}                                    \
		goto done;                           \
	}
#elif EMU86_EMULATE_CONFIG_CHECKERROR
#define DEFINE_CMOVcc(id, cond_expr)       \
	case EMU86_OPCODE_ENCODE(0x0f40 + id): \
		goto notsup_modrm_getwlq;
#define NEED_notsup_modrm_getwlq
#else
#define DEFINE_CMOVcc(id, cond_expr) /* nothing */
#endif

#define DEFINE_CMOVcc_SETcc(id, cond_expr) \
	DEFINE_CMOVcc(id, cond_expr)           \
	DEFINE_SETcc(id, cond_expr)

	/* 0F 40      CMOVO r16, r/m16        Move if overflow (OF=1) */
	/* 0F 40      CMOVO r32, r/m32        Move if overflow (OF=1) */
	DEFINE_CMOVcc_SETcc(0x0, eflags & EFLAGS_OF)

	/* 0F 41      CMOVNO r16, r/m16       Move if not overflow (OF=0) */
	/* 0F 41      CMOVNO r32, r/m32       Move if not overflow (OF=0) */
	DEFINE_CMOVcc_SETcc(0x1, !(eflags & EFLAGS_OF))

	/* 0F 42      CMOVB r16, r/m16        Move if below (CF=1) */
	/* 0F 42      CMOVB r32, r/m32        Move if below (CF=1) */
	/* 0F 42      CMOVC r16, r/m16        Move if carry (CF=1) */
	/* 0F 42      CMOVC r32, r/m32        Move if carry (CF=1) */
	/* 0F 42      CMOVNAE r16, r/m16      Move if not above or equal (CF=1) */
	/* 0F 42      CMOVNAE r32, r/m32      Move if not above or equal (CF=1) */
	DEFINE_CMOVcc_SETcc(0x2, eflags & EFLAGS_CF)

	/* 0F 43      CMOVAE r16, r/m16       Move if above or equal (CF=0) */
	/* 0F 43      CMOVAE r32, r/m32       Move if above or equal (CF=0) */
	/* 0F 43      CMOVNB r16, r/m16       Move if not below (CF=0) */
	/* 0F 43      CMOVNB r32, r/m32       Move if not below (CF=0) */
	/* 0F 43      CMOVNC r16, r/m16       Move if not carry (CF=0) */
	/* 0F 43      CMOVNC r32, r/m32       Move if not carry (CF=0) */
	DEFINE_CMOVcc_SETcc(0x3, !(eflags & EFLAGS_CF))

	/* 0F 44      CMOVE r16, r/m16        Move if equal (ZF=1) */
	/* 0F 44      CMOVE r32, r/m32        Move if equal (ZF=1) */
	/* 0F 44      CMOVZ r16, r/m16        Move if zero (ZF=1) */
	/* 0F 44      CMOVZ r32, r/m32        Move if zero (ZF=1) */
	DEFINE_CMOVcc_SETcc(0x4, eflags & EFLAGS_ZF)

	/* 0F 45      CMOVNE r16, r/m16       Move if not equal (ZF=0) */
	/* 0F 45      CMOVNE r32, r/m32       Move if not equal (ZF=0) */
	/* 0F 45      CMOVNZ r16, r/m16       Move if not zero (ZF=0) */
	/* 0F 45      CMOVNZ r32, r/m32       Move if not zero (ZF=0) */
	DEFINE_CMOVcc_SETcc(0x5, !(eflags & EFLAGS_ZF))

	/* 0F 46      CMOVBE r16, r/m16       Move if below or equal (CF=1 or ZF=1) */
	/* 0F 46      CMOVBE r32, r/m32       Move if below or equal (CF=1 or ZF=1) */
	/* 0F 46      CMOVNA r16, r/m16       Move if not above (CF=1 or ZF=1) */
	/* 0F 46      CMOVNA r32, r/m32       Move if not above (CF=1 or ZF=1) */
	DEFINE_CMOVcc_SETcc(0x6, eflags & (EFLAGS_CF | EFLAGS_ZF))

	/* 0F 47      CMOVA r16, r/m16        Move if above (CF=0 and ZF=0) */
	/* 0F 47      CMOVA r32, r/m32        Move if above (CF=0 and ZF=0) */
	/* 0F 47      CMOVNBE r16, r/m16      Move if not below or equal (CF=0 and ZF=0) */
	/* 0F 47      CMOVNBE r32, r/m32      Move if not below or equal (CF=0 and ZF=0) */
	DEFINE_CMOVcc_SETcc(0x7, !(eflags & (EFLAGS_CF | EFLAGS_ZF)))

	/* 0F 48      CMOVS r16, r/m16        Move if sign (SF=1) */
	/* 0F 48      CMOVS r32, r/m32        Move if sign (SF=1) */
	DEFINE_CMOVcc_SETcc(0x8, eflags & EFLAGS_SF)

	/* 0F 49      CMOVNS r16, r/m16       Move if not sign (SF=0) */
	/* 0F 49      CMOVNS r32, r/m32       Move if not sign (SF=0) */
	DEFINE_CMOVcc_SETcc(0x9, !(eflags & EFLAGS_SF))

	/* 0F 4A      CMOVP r16, r/m16        Move if parity (PF=1) */
	/* 0F 4A      CMOVP r32, r/m32        Move if parity (PF=1) */
	/* 0F 4A      CMOVPE r16, r/m16       Move if parity even (PF=1) */
	/* 0F 4A      CMOVPE r32, r/m32       Move if parity even (PF=1) */
	DEFINE_CMOVcc_SETcc(0xa, eflags & EFLAGS_PF)

	/* 0F 4B      CMOVNP r16, r/m16       Move if not parity (PF=0) */
	/* 0F 4B      CMOVNP r32, r/m32       Move if not parity (PF=0) */
	/* 0F 4B      CMOVPO r16, r/m16       Move if parity odd (PF=0) */
	/* 0F 4B      CMOVPO r32, r/m32       Move if parity odd (PF=0) */
	DEFINE_CMOVcc_SETcc(0xb, !(eflags & EFLAGS_PF))

	/* 0F 4C      CMOVL r16, r/m16        Move if less (SF!=OF) */
	/* 0F 4C      CMOVL r32, r/m32        Move if less (SF!=OF) */
	/* 0F 4C      CMOVNGE r16, r/m16      Move if not greater or equal (SF!=OF) */
	/* 0F 4C      CMOVNGE r32, r/m32      Move if not greater or equal (SF!=OF) */
	DEFINE_CMOVcc_SETcc(0xc, !!(eflags & EFLAGS_SF) !=
	                         !!(eflags & EFLAGS_OF))

	/* 0F 4D      CMOVGE r16, r/m16       Move if greater or equal (SF=OF) */
	/* 0F 4D      CMOVGE r32, r/m32       Move if greater or equal (SF=OF) */
	/* 0F 4D      CMOVNL r16, r/m16       Move if not less (SF=OF) */
	/* 0F 4D      CMOVNL r32, r/m32       Move if not less (SF=OF) */
	DEFINE_CMOVcc_SETcc(0xd, !!(eflags & EFLAGS_SF) ==
	                         !!(eflags & EFLAGS_OF))

	/* 0F 4E      CMOVLE r16, r/m16       Move if less or equal (ZF=1 or SF!=OF) */
	/* 0F 4E      CMOVLE r32, r/m32       Move if less or equal (ZF=1 or SF!=OF) */
	/* 0F 4E      CMOVNG r16, r/m16       Move if not greater (ZF=1 or SF!=OF) */
	/* 0F 4E      CMOVNG r32, r/m32       Move if not greater (ZF=1 or SF!=OF) */
	DEFINE_CMOVcc_SETcc(0xe, (eflags & EFLAGS_ZF) ||
	                         (!!(eflags & EFLAGS_SF) !=
	                          !!(eflags & EFLAGS_OF)))

	/* 0F 4F      CMOVG r16, r/m16        Move if greater (ZF=0 and SF=OF) */
	/* 0F 4F      CMOVG r32, r/m32        Move if greater (ZF=0 and SF=OF) */
	/* 0F 4F      CMOVNLE r16, r/m16      Move if not less or equal (ZF=0 and SF=OF) */
	/* 0F 4F      CMOVNLE r32, r/m32      Move if not less or equal (ZF=0 and SF=OF) */
	DEFINE_CMOVcc_SETcc(0xf, !(eflags & EFLAGS_ZF) &&
	                         (!!(eflags & EFLAGS_SF) ==
	                          !!(eflags & EFLAGS_OF)))

#undef DEFINE_SETcc
#undef DEFINE_CMOVcc
#undef DEFINE_CMOVcc_SETcc

}
EMU86_INTELLISENSE_END
