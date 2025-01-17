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

#include "push-pop-util.h"

EMU86_INTELLISENSE_BEGIN(ljmp) {

#if !EMU86_EMULATE_CONFIG_ONLY_MEMORY
#if (EMU86_EMULATE_CONFIG_CHECKERROR || \
     (EMU86_EMULATE_CONFIG_WANT_LJMP && \
      (LIBEMU86_CONFIG_WANT_32BIT || LIBEMU86_CONFIG_WANT_16BIT)))

case EMU86_OPCODE_ENCODE(0xea): {
	/* EA cd    JMP ptr16:16    Jump far, absolute, address given in operand
	 * EA cp    JMP ptr16:32    Jump far, absolute, address given in operand */
#if LIBEMU86_CONFIG_WANT_64BIT
#define NEED_return_unsupported_instruction
	if (EMU86_F_IS64(op_flags))
		goto return_unsupported_instruction;
#endif /* LIBEMU86_CONFIG_WANT_64BIT */
#if ((EMU86_EMULATE_CONFIG_WANT_LJMP || (EMU86_EMULATE_CONFIG_CHECKERROR && defined(EMU86_VALIDATE_IPCS))) && \
     (LIBEMU86_CONFIG_WANT_32BIT || LIBEMU86_CONFIG_WANT_16BIT))
	{
		u32 offset;
		u16 cs;
		if (!!EMU86_F_IS16(op_flags) ^ !!(op_flags & EMU86_F_AD16)) {
			offset = UNALIGNED_GETLE16(pc);
			pc += 2;
		} else {
			offset = UNALIGNED_GETLE32(pc);
			pc += 4;
		}
		cs = UNALIGNED_GETLE16(pc);
		pc += 2;
		/* Verify the segment index. */
#if EMU86_EMULATE_CONFIG_CHECKUSER
		if (!SEGMENT_IS_VALID_USERCODE(cs) && EMU86_ISUSER_NOVM86()) {
#ifdef EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER
			EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER(E_ILLEGAL_INSTRUCTION_REGISTER_WRPRV,
			                                                 X86_REGISTER_SEGMENT_CS,
			                                                 offset, cs, 0);
#else /* EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER */
#define NEED_return_privileged_instruction
			goto return_privileged_instruction;
#endif /* !EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER */
		}
#endif /* EMU86_EMULATE_CONFIG_CHECKUSER */
#if EMU86_EMULATE_CONFIG_WANT_LJMP
		EMU86_SETCS(cs);
		EMU86_SETIPREG(offset);
		goto done_dont_set_pc;
#define NEED_done_dont_set_pc
#else /* EMU86_EMULATE_CONFIG_WANT_LJMP */
		EMU86_VALIDATE_IPCS(offset, cs);
#define NEED_return_unsupported_instruction
		goto return_unsupported_instruction;
#endif /* !EMU86_EMULATE_CONFIG_WANT_LJMP */
	}
#else /* EMU86_EMULATE_CONFIG_WANT_LJMP && (LIBEMU86_CONFIG_WANT_32BIT || LIBEMU86_CONFIG_WANT_16BIT) */
#define NEED_return_unsupported_instruction
	goto return_unsupported_instruction;
#endif /* !EMU86_EMULATE_CONFIG_WANT_LJMP || (!LIBEMU86_CONFIG_WANT_32BIT && !LIBEMU86_CONFIG_WANT_16BIT) */
}

#endif /* ... */
#endif /* !EMU86_EMULATE_CONFIG_ONLY_MEMORY */

}
EMU86_INTELLISENSE_END
