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

#include "pushpop-util.h"

EMU86_INTELLISENSE_BEGIN(ljmp) {

#ifndef EMU86_EMULATE_ONLY_MEMORY
#if CONFIG_LIBEMU86_WANT_32BIT || CONFIG_LIBEMU86_WANT_16BIT

case 0xea: {
	/* EA cd    JMP ptr16:16    Jump far, absolute, address given in operand
	 * EA cp    JMP ptr16:32    Jump far, absolute, address given in operand */
	u32 offset;
	u16 segment;
	if (op_flags & EMU86_F_AD16) {
		offset = UNALIGNED_GET16((u16 *)pc);
		pc += 2;
	} else {
		offset = UNALIGNED_GET32((u32 *)pc);
		pc += 4;
	}
	segment = UNALIGNED_GET16((u16 *)pc);
	/* Verify the segment index. */
#if EMU86_EMULATE_CHECKUSER
	if (!SEGMENT_IS_VALID_USERCODE(segment) && EMU86_ISUSER_NOVM86()) {
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_SIGRETURN_REGISTER,
		      X86_REGISTER_SEGMENT_CS, segment);
	}
#endif /* EMU86_EMULATE_CHECKUSER */
	EMU86_SETCS(segment);
	EMU86_SETIPREG(offset);
	goto done_dont_set_pc;
}

#endif /* CONFIG_LIBEMU86_WANT_32BIT || CONFIG_LIBEMU86_WANT_16BIT */
#endif /* !EMU86_EMULATE_ONLY_MEMORY */

}
EMU86_INTELLISENSE_END
