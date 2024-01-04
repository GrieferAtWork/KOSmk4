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

#include "push-pop-util.h"

EMU86_INTELLISENSE_BEGIN(push_pop) {


#if EMU86_EMULATE_CONFIG_WANT_PUSH_REG
case EMU86_OPCODE_ENCODE(0x50) ... EMU86_OPCODE_ENCODE(0x57): {
	/* 50+rw     PUSH r16     Push r16.
	 * 50+rd     PUSH r32     Push r32.
	 * 50+rd     PUSH r64     Push r64. */
	u8 regno;
	regno = tiny_opcode - EMU86_OPCODE_ENCODE(0x50);
#if LIBEMU86_CONFIG_WANT_64BIT
	if (op_flags & EMU86_F_REX_B)
		regno |= 0x8;
#endif /* LIBEMU86_CONFIG_WANT_64BIT */
	EMU86_PUSH163264(EMU86_GETREGW(regno),
	                 EMU86_GETREGL(regno),
	                 EMU86_GETREGQ(regno));
	goto done;
}
#elif EMU86_EMULATE_CONFIG_CHECKERROR
case EMU86_OPCODE_ENCODE(0x50) ... EMU86_OPCODE_ENCODE(0x57):
	goto notsup_pushwlq;
#define NEED_notsup_pushwlq
#endif /* ... */



#if EMU86_EMULATE_CONFIG_WANT_POP_REG
case EMU86_OPCODE_ENCODE(0x58) ... EMU86_OPCODE_ENCODE(0x5f): {
	/* 50+rw     POP r16     Pop r16.
	 * 50+rd     POP r32     Pop r32.
	 * 50+rd     POP r64     Pop r64. */
	u8 regno;
	regno = tiny_opcode - EMU86_OPCODE_ENCODE(0x58);
#if LIBEMU86_CONFIG_WANT_64BIT
	if (op_flags & EMU86_F_REX_B)
		regno |= 0x8;
#endif /* LIBEMU86_CONFIG_WANT_64BIT */
#define SETREGW(v) EMU86_SETREGW(regno, v)
#define SETREGL(v) EMU86_SETREGL(regno, v)
#define SETREGQ(v) EMU86_SETREGQ(regno, v)
	EMU86_POP163264(SETREGW,
	                SETREGL,
	                SETREGQ);
#undef SETREGQ
#undef SETREGL
#undef SETREGW
	goto done;
}
#elif EMU86_EMULATE_CONFIG_CHECKERROR
case EMU86_OPCODE_ENCODE(0x58) ... EMU86_OPCODE_ENCODE(0x5f):
	goto notsup_popwlq;
#define NEED_notsup_popwlq
#endif /* ... */



#if (EMU86_EMULATE_CONFIG_CHECKERROR ||  \
     EMU86_EMULATE_CONFIG_WANT_POP_RM || \
     EMU86_EMULATE_CONFIG_WANT_XOP)
case EMU86_OPCODE_ENCODE(0x8f): {
	MODRM_DECODE();
	if unlikely(modrm.mi_reg != 0) {
#if EMU86_EMULATE_CONFIG_WANT_XOP
#ifdef EMU86_F_BITMASK
		if (!(op_flags & ~(EMU86_F_SEGMASK | EMU86_F_BITMASK)))
#else /* EMU86_F_BITMASK */
		if (!(op_flags & ~(EMU86_F_SEGMASK)))
#endif /* !EMU86_F_BITMASK */
		{
			byte_t const *orig_modrm_pc = pc;
			u8 orig_modrm_reg = modrm.mi_reg;
			u16 vex;
			pc = start_pc + 1;
			vex = *pc++;
			vex <<= 8;
			vex |= *pc++;
			/*op_flags |= EMU86_F_HASVEX;*/ /* Not needed */
#if LIBEMU86_CONFIG_WANT_64BIT
			IF_16BIT_OR_32BIT(if (EMU86_F_IS64(op_flags))) {
				if (!(vex & EMU86_VEX3B_R))
					op_flags |= EMU86_F_REX_R;
				if (!(vex & EMU86_VEX3B_X))
					op_flags |= EMU86_F_REX_X;
				if (!(vex & EMU86_VEX3B_B))
					op_flags |= EMU86_F_REX_B;
			} IF_16BIT_OR_32BIT(else)
#endif /* LIBEMU86_CONFIG_WANT_64BIT */
#if LIBEMU86_CONFIG_WANT_32BIT || LIBEMU86_CONFIG_WANT_16BIT
			{
				if unlikely((vex & (EMU86_VEX3B_R | EMU86_VEX3B_X | EMU86_VEX3B_B)) !=
				            /*  */ (EMU86_VEX3B_R | EMU86_VEX3B_X | EMU86_VEX3B_B))
					goto xop_fallback;
			}
#endif /* LIBEMU86_CONFIG_WANT_32BIT || LIBEMU86_CONFIG_WANT_16BIT */
			if (vex & EMU86_VEX3B_L)
				op_flags |= 1 << EMU86_F_VEX_LL_S;
			if (vex & EMU86_VEX3B_W)
				op_flags |= EMU86_F_VEX_W;
			op_flags |= ((~vex & EMU86_VEX3B_VVVV_M) >> EMU86_VEX3B_VVVV_S) << EMU86_F_VEX_VVVVV_S;
			switch (vex & EMU86_VEX3B_PP_M) {
			case 0x01 << EMU86_VEX3B_PP_S: op_flags |= EMU86_F_OP16; break;  /* same as 0x66 prefix */
			case 0x02 << EMU86_VEX3B_PP_S: op_flags |= EMU86_F_REP; break;   /* same as 0xf3 prefix */
			case 0x03 << EMU86_VEX3B_PP_S: op_flags |= EMU86_F_REPNE; break; /* same as 0xf2 prefix */
			default: break;
			}
			/* The actual instruction opcode byte */
			tiny_opcode = *pc++;
			if likely((vex & EMU86_VEX3B_MMMMM_M) >= 0x8 << EMU86_VEX3B_MMMMM_S) {
				tiny_opcode |= EMU86_OPCODE_BASEXOP((vex & EMU86_VEX3B_MMMMM_M) >> EMU86_VEX3B_MMMMM_S);
				switch (tiny_opcode) {

#ifndef __INTELLISENSE__
#ifdef EMU86_EMULATE_IMPL_XOP_HEADER
#include EMU86_EMULATE_IMPL_XOP_HEADER
#else /* EMU86_EMULATE_IMPL_XOP_HEADER */
#include "xop-tbm.c.inl"
#endif /* !EMU86_EMULATE_IMPL_XOP_HEADER */
#endif /* !__INTELLISENSE__ */

				default:
					goto return_unknown_instruction;
				}
			}
IF_16BIT_OR_32BIT(xop_fallback:)
			pc           = orig_modrm_pc;
			modrm.mi_reg = orig_modrm_reg;
#ifdef EMU86_F_BITMASK
			op_flags &= (EMU86_F_SEGMASK | EMU86_F_BITMASK);
#else /* EMU86_F_BITMASK */
			op_flags &= (EMU86_F_SEGMASK);
#endif /* !EMU86_F_BITMASK */
			tiny_opcode = EMU86_OPCODE_ENCODE(0x8f);
		}
#endif /* EMU86_EMULATE_CONFIG_WANT_XOP */
#define NEED_return_unknown_instruction_rmreg
		goto return_unknown_instruction_rmreg;
	}
	/* 8F /0     POP r/m16     Pop top of stack into m16; increment stack pointer.
	 * 8F /0     POP r/m32     Pop top of stack into m32; increment stack pointer.
	 * 8F /0     POP r/m64     Pop top of stack into m64; increment stack pointer.
	 *                         Cannot encode 32-bit operand size. */
#if EMU86_EMULATE_CONFIG_WANT_POP_RM
	EMU86_POP163264(MODRM_SETRMW,
	                MODRM_SETRML,
	                MODRM_SETRMQ);
	goto done;
#else /* EMU86_EMULATE_CONFIG_WANT_POP_RM */
	goto notsup_modrm_setwlq_rmreg_modrm_parsed_popwlq;
#define NEED_notsup_modrm_setwlq_rmreg_modrm_parsed_popwlq
#endif /* !EMU86_EMULATE_CONFIG_WANT_POP_RM */
}
#endif /* EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_POP_RM || EMU86_EMULATE_CONFIG_WANT_XOP */


}
EMU86_INTELLISENSE_END
