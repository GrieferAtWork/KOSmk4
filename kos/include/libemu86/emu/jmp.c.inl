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

EMU86_INTELLISENSE_BEGIN(jmp) {

#ifndef EMU86_EMULATE_ONLY_MEMORY

case 0xe9: {
	/* E9 cw    JMP rel16   Jump near, relative, displacement relative to next instruction.
	 * E9 cd    JMP rel32   Jump near, relative, displacement relative to next instruction.
	 *                      32-bit displacement sign extended to 64-bits in 64-bit mode. */
	EMU86_UREG_TYPE dest_ip;
	IF_16BIT_OR_32BIT(
	if (IS_16BIT() && !EMU86_F_IS64(op_flags)) {
		s16 offset;
		offset = (s16)UNALIGNED_GET16((u16 *)pc);
		pc += 2;
		dest_ip = REAL_IP() + offset;
	} else) {
		s32 offset;
		offset = (s32)UNALIGNED_GET32((u32 *)pc);
		pc += 4;
		dest_ip = REAL_IP() + offset;
	}
	EMU86_SETIPREG(dest_ip);
	goto done_dont_set_pc;
}

case 0xeb: {
	/* EB cw    JMP rel8    Jump near, relative, displacement relative to next instruction. */
	EMU86_UREG_TYPE dest_ip;
	s8 offset;
	offset = *(s8 *)pc;
	pc += 1;
	dest_ip = REAL_IP() + offset;
	EMU86_SETIPREG(dest_ip);
	goto done_dont_set_pc;
}

#endif /* !EMU86_EMULATE_ONLY_MEMORY */


}
EMU86_INTELLISENSE_END
