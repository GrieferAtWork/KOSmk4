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

EMU86_INTELLISENSE_BEGIN(jmp) {

#if !EMU86_EMULATE_CONFIG_ONLY_MEMORY

#if EMU86_EMULATE_CONFIG_WANT_JMP_DISP32
case EMU86_OPCODE_ENCODE(0xe9): {
	/* E9 cw    JMP rel16   Jump near, relative, displacement relative to next instruction.
	 * E9 cd    JMP rel32   Jump near, relative, displacement relative to next instruction.
	 *                      32-bit displacement sign  extended to 64-bits  in 64-bit  mode. */
	EMU86_UREG_TYPE dest_ip;
	IF_16BIT_OR_32BIT(
	if (IS_16BIT() && !EMU86_F_IS64(op_flags)) {
		s16 offset;
		offset = (s16)UNALIGNED_GETLE16(pc);
		pc += 2;
		dest_ip = REAL_IP() + offset;
	} else) {
		s32 offset;
		offset = (s32)UNALIGNED_GETLE32(pc);
		pc += 4;
		dest_ip = REAL_IP() + offset;
	}
	if (IS_16BIT())
		dest_ip &= 0xffff;
	EMU86_SETIPREG(dest_ip);
	goto done_dont_set_pc;
#define NEED_done_dont_set_pc
}
#elif EMU86_EMULATE_CONFIG_CHECKERROR && !EMU86_EMULATE_CONFIG_ONLY_CHECKERROR_NO_BASIC
case EMU86_OPCODE_ENCODE(0xe9):
	goto return_unsupported_instruction;
#define NEED_return_unsupported_instruction
#endif /* ... */


#if EMU86_EMULATE_CONFIG_WANT_JMP_DISP8
case EMU86_OPCODE_ENCODE(0xeb): {
	/* EB cw    JMP rel8    Jump near, relative, displacement relative to next instruction. */
	EMU86_UREG_TYPE dest_ip;
	s8 offset;
	offset = *(s8 const *)pc;
	pc += 1;
	dest_ip = REAL_IP() + offset;
	if (IS_16BIT())
		dest_ip &= 0xffff;
	EMU86_SETIPREG(dest_ip);
	goto done_dont_set_pc;
#define NEED_done_dont_set_pc
}
#elif EMU86_EMULATE_CONFIG_CHECKERROR && !EMU86_EMULATE_CONFIG_ONLY_CHECKERROR_NO_BASIC
case EMU86_OPCODE_ENCODE(0xeb):
	goto return_unsupported_instruction;
#define NEED_return_unsupported_instruction
#endif /* ... */

#endif /* !EMU86_EMULATE_CONFIG_ONLY_MEMORY */

}
EMU86_INTELLISENSE_END
