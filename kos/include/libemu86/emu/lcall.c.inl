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

#include "push-pop-util.h"

EMU86_INTELLISENSE_BEGIN(lcall) {

#if CONFIG_LIBEMU86_WANT_16BIT || CONFIG_LIBEMU86_WANT_32BIT
case 0x9a: {
	/* 9A cd    CALL ptr16:16    Call far, absolute, address given in operand.
	 * 9A cp    CALL ptr16:32    Call far, absolute, address given in operand. */
	byte_t *sp;
	u32 offset;
	u16 segment;
	IF_64BIT({
		if (EMU86_F_IS64(op_flags))
			goto return_unknown_instruction;
	});
	if (!IS_16BIT()) {
		offset = UNALIGNED_GET32((u32 *)pc);
		pc += 4;
	} else {
		offset = UNALIGNED_GET16((u16 *)pc);
		pc += 2;
	}
	segment = UNALIGNED_GET16((u16 *)pc);
	pc += 2;
	/* Verify the segment index. */
#if EMU86_EMULATE_CHECKUSER
	if (!SEGMENT_IS_VALID_USERCODE(segment) && EMU86_ISUSER_NOVM86()) {
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_SIGRETURN_REGISTER,
		      X86_REGISTER_SEGMENT_CS, segment);
	}
#endif /* EMU86_EMULATE_CHECKUSER */
	sp = EMU86_GETSTACKPTR();
	if (!IS_16BIT()) {
		sp -= 8;
		EMU86_EMULATE_PUSH(sp, 8);
		EMU86_WRITE_USER_MEMORY(sp, 8);
		EMU86_MEMWRITEL(sp + 4, (u32)EMU86_GETCS());
		EMU86_MEMWRITEL(sp + 0, (u32)REAL_IP());
	} else {
		sp -= 4;
		EMU86_EMULATE_PUSH(sp, 4);
		EMU86_WRITE_USER_MEMORY(sp, 4);
		EMU86_MEMWRITEW(sp + 2, (u16)EMU86_GETCS());
		EMU86_MEMWRITEW(sp + 0, (u16)REAL_IP());
	}
	EMU86_SETSTACKPTR(sp);
	EMU86_SETCS(segment);
	EMU86_SETIPREG(offset);
	goto done_dont_set_pc;
}
#endif /* CONFIG_LIBEMU86_WANT_16BIT || CONFIG_LIBEMU86_WANT_32BIT */

}
EMU86_INTELLISENSE_END
