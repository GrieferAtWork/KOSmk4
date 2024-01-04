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

EMU86_INTELLISENSE_BEGIN(mov_sreg) {

#if EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_MOV_SREG
case EMU86_OPCODE_ENCODE(0x8c): {
#if EMU86_EMULATE_CONFIG_WANT_MOV_SREG
	u16 segment;
#endif /* EMU86_EMULATE_CONFIG_WANT_MOV_SREG */
	/*         8C /r     MOV r/m16,Sreg**           MR  Valid Valid Move segment register to r/m16.
	 * REX.W + 8C /r     MOV r16/r32/m16, Sreg**    MR  Valid Valid Move zero extended 16-bit segment register to r16/r32/r64/m16.
	 * REX.W + 8C /r     MOV r64/m16, Sreg**        MR  Valid Valid Move zero extended 16-bit segment register to r64/m16. */
	MODRM_DECODE();
	if (modrm.mi_reg >= 6) {
#ifndef EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER
#define NEED_return_unsupported_instruction
		goto return_unsupported_instruction;
#else /* !EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER */
		EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER(E_ILLEGAL_INSTRUCTION_REGISTER_RDINV,
		                                                 X86_REGISTER_SEGMENT_ES + modrm.mi_reg,
		                                                 0, 0, 0);
#endif /* EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER */
	}
#if EMU86_EMULATE_CONFIG_WANT_MOV_SREG
	segment = EMU86_GETSEG(modrm.mi_reg);
	IF_64BIT(if (IS_64BIT()) {
		MODRM_SETRMQ(segment);
	} else) if (!IS_16BIT()) {
		MODRM_SETRML(segment);
	} else {
		MODRM_SETRMW(segment);
	}
	goto done;
#else /* EMU86_EMULATE_CONFIG_WANT_MOV_SREG */
	MODRM_NOSUP_SETRMW();
	goto return_unsupported_instruction;
#define NEED_return_unsupported_instruction
#endif /* !EMU86_EMULATE_CONFIG_WANT_MOV_SREG */
}
#endif /* EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_MOV_SREG */


#if EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_MOV_SREG
case EMU86_OPCODE_ENCODE(0x8e): {
#if (EMU86_EMULATE_CONFIG_CHECKUSER || EMU86_EMULATE_CONFIG_WANT_MOV_SREG || \
     (EMU86_EMULATE_CONFIG_CHECKERROR && defined(EMU86_VALIDATE_DATASEG)))
	u16 segment;
#endif /* ... */
	/*         8E /r      MOV Sreg,r/m16** RM Valid Valid Move r/m16 to segment register.
	 * REX.W + 8E /r      MOV Sreg,r/m64** RM Valid Valid Move lower 16 bits of r/m64 to segment register. */
	MODRM_DECODE();
#if (EMU86_EMULATE_CONFIG_CHECKUSER || EMU86_EMULATE_CONFIG_WANT_MOV_SREG || \
     (EMU86_EMULATE_CONFIG_CHECKERROR && defined(EMU86_VALIDATE_DATASEG)))
	segment = MODRM_GETRMW();
	if unlikely(modrm.mi_reg >= 6) {
#ifdef EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER
		EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER(E_ILLEGAL_INSTRUCTION_REGISTER_WRINV,
		                                                 X86_REGISTER_SEGMENT_ES + modrm.mi_reg,
		                                                 0, segment, 0);
#else /* EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER */
#define NEED_return_unsupported_instruction
		goto return_unsupported_instruction;
#endif /* !EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER */
	}
#if EMU86_EMULATE_CONFIG_CHECKUSER && (LIBEMU86_CONFIG_WANT_32BIT || LIBEMU86_CONFIG_WANT_64BIT)
	if ((modrm.mi_reg == EMU86_R_CS ? !SEGMENT_IS_VALID_USERCODE(segment)
	                                : !SEGMENT_IS_VALID_USERDATA(segment)) &&
	    EMU86_ISUSER_NOVM86()) {
#ifdef EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER
		EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER(E_ILLEGAL_INSTRUCTION_REGISTER_WRPRV,
		                                                 X86_REGISTER_SEGMENT_ES + modrm.mi_reg,
		                                                 0, segment, 0);
#else /* EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER */
#define NEED_return_privileged_instruction
		goto return_privileged_instruction;
#endif /* !EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER */
	}
#endif /* EMU86_EMULATE_CONFIG_CHECKUSER && (LIBEMU86_CONFIG_WANT_32BIT || LIBEMU86_CONFIG_WANT_64BIT) */
#if (!EMU86_EMULATE_CONFIG_WANT_MOV_SREG && \
     (EMU86_EMULATE_CONFIG_CHECKERROR && defined(EMU86_VALIDATE_DATASEG)))
	EMU86_VALIDATE_DATASEG(segment, X86_REGISTER_SEGMENT_ES + modrm.mi_reg);
#endif /* !EMU86_EMULATE_CONFIG_WANT_MOV_SREG && EMU86_EMULATE_CONFIG_CHECKERROR && EMU86_VALIDATE_DATASEG */
#elif EMU86_EMULATE_CONFIG_CHECKERROR
	MODRM_NOSUP_GETRMW();
#endif /* ... */
#if EMU86_EMULATE_CONFIG_WANT_MOV_SREG
	EMU86_SETSEG(modrm.mi_reg, segment);
	goto done;
#else /* EMU86_EMULATE_CONFIG_WANT_MOV_SREG */
	goto return_unsupported_instruction;
#define NEED_return_unsupported_instruction
#endif /* !EMU86_EMULATE_CONFIG_WANT_MOV_SREG */
}
#endif /* EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_MOV_SREG */



}
EMU86_INTELLISENSE_END
