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

#include "push-pop-util.h"

EMU86_INTELLISENSE_BEGIN(lcall) {

#if ((EMU86_EMULATE_CONFIG_CHECKERROR && !EMU86_EMULATE_CONFIG_ONLY_CHECKERROR_NO_BASIC) || \
     (EMU86_EMULATE_CONFIG_WANT_LCALL && (LIBEMU86_CONFIG_WANT_16BIT || LIBEMU86_CONFIG_WANT_32BIT)))
case EMU86_OPCODE_ENCODE(0x9a): {
	/* 9A cd    CALL ptr16:16    Call far, absolute, address given in operand.
	 * 9A cp    CALL ptr16:32    Call far, absolute, address given in operand. */
#if LIBEMU86_CONFIG_WANT_16BIT || LIBEMU86_CONFIG_WANT_32BIT
	byte_t *sp;
#if EMU86_EMULATE_CONFIG_WANT_LCALL || EMU86_EMULATE_CONFIG_CHECKUSER
	u32 offset;
	u16 segment;
#endif /* EMU86_EMULATE_CONFIG_WANT_LCALL || EMU86_EMULATE_CONFIG_CHECKUSER */
#if LIBEMU86_CONFIG_WANT_64BIT
#define NEED_return_unsupported_instruction
	if (EMU86_F_IS64(op_flags))
		goto return_unsupported_instruction;
#endif /* LIBEMU86_CONFIG_WANT_64BIT */
#if EMU86_EMULATE_CONFIG_WANT_LCALL || EMU86_EMULATE_CONFIG_CHECKUSER
	if (!IS_16BIT()) {
		offset = UNALIGNED_GETLE32((u32 const *)pc);
		pc += 4;
	} else {
		offset = UNALIGNED_GETLE16((u16 const *)pc);
		pc += 2;
	}
	segment = UNALIGNED_GETLE16((u16 const *)pc);
	pc += 2;
#endif /* EMU86_EMULATE_CONFIG_WANT_LCALL || EMU86_EMULATE_CONFIG_CHECKUSER */
	/* Verify the segment index. */
#if EMU86_EMULATE_CONFIG_CHECKUSER
	if (!SEGMENT_IS_VALID_USERCODE(segment) && EMU86_ISUSER_NOVM86()) {
#ifdef EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER
		EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER(E_ILLEGAL_INSTRUCTION_REGISTER_WRPRV,
		                                                 X86_REGISTER_SEGMENT_CS,
		                                                 offset, segment, 0);
#else /* EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER */
#define NEED_return_privileged_instruction
		goto return_privileged_instruction;
#endif /* !EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER */
	}
#endif /* EMU86_EMULATE_CONFIG_CHECKUSER */
	sp = EMU86_GETSTACKPTR();
	if (!IS_16BIT()) {
		sp -= 8;
		EMU86_EMULATE_PUSH(sp, 8);
#if EMU86_EMULATE_CONFIG_WANT_LCALL
		EMU86_WRITE_USER_MEMORY(sp, 8);
		EMU86_MEMWRITEL(sp + 4, (u32)EMU86_GETCS());
		EMU86_MEMWRITEL(sp + 0, (u32)REAL_IP());
#else /* EMU86_EMULATE_CONFIG_WANT_LCALL */
		EMU86_UNSUPPORTED_MEMACCESS(sp, 8, false, true);
#endif /* !EMU86_EMULATE_CONFIG_WANT_LCALL */
	} else {
		sp -= 4;
		EMU86_EMULATE_PUSH(sp, 4);
#if EMU86_EMULATE_CONFIG_WANT_LCALL
		EMU86_WRITE_USER_MEMORY(sp, 4);
		EMU86_MEMWRITEW(sp + 2, (u16)EMU86_GETCS());
		EMU86_MEMWRITEW(sp + 0, (u16)REAL_IP());
#else /* EMU86_EMULATE_CONFIG_WANT_LCALL */
		EMU86_UNSUPPORTED_MEMACCESS(sp, 4, false, true);
#endif /* !EMU86_EMULATE_CONFIG_WANT_LCALL */
	}
#if EMU86_EMULATE_CONFIG_WANT_LCALL
	EMU86_SETSTACKPTR(sp);
	EMU86_SETCS(segment);
	EMU86_SETIPREG(offset);
#else /* EMU86_EMULATE_CONFIG_WANT_LCALL */
#define NEED_return_unsupported_instruction
	goto return_unsupported_instruction;
#endif /* !EMU86_EMULATE_CONFIG_WANT_LCALL */
#else /* LIBEMU86_CONFIG_WANT_16BIT || LIBEMU86_CONFIG_WANT_32BIT */
#define NEED_return_unsupported_instruction
	goto return_unsupported_instruction;
#endif /* !LIBEMU86_CONFIG_WANT_16BIT && !LIBEMU86_CONFIG_WANT_32BIT */
	goto done_dont_set_pc;
#define NEED_done_dont_set_pc
}
#endif /* ... */

}
EMU86_INTELLISENSE_END
