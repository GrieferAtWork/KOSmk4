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

#include "push-pop-util.h"


EMU86_INTELLISENSE_BEGIN(ret) {


#if EMU86_EMULATE_CONFIG_WANT_RET
case EMU86_OPCODE_ENCODE(0xc3): {
	/* C3     RET     Near return to calling procedure. */
	EMU86_POP163264(EMU86_SETIP,
	                EMU86_SETEIP,
	                EMU86_SETRIP);
	goto done_dont_set_pc;
#define NEED_done_dont_set_pc
}


case EMU86_OPCODE_ENCODE(0xc2): {
	u16 offset;
	byte_t *sp;
	/* C2 iw     RET imm16     Near return to calling procedure and pop imm16 bytes from stack. */
	offset = UNALIGNED_GETLE16((u16 const *)pc);
	pc += 2;
	sp = EMU86_GETSTACKPTR();
	EMU86_POP163264_IMPL(EMU86_SETIP,
	                     EMU86_SETEIP,
	                     EMU86_SETRIP);
	sp += offset;
	EMU86_SETSTACKPTR(sp);
	goto done_dont_set_pc;
#define NEED_done_dont_set_pc
}
#elif EMU86_EMULATE_CONFIG_CHECKERROR
case EMU86_OPCODE_ENCODE(0xc3):
case EMU86_OPCODE_ENCODE(0xc2):
	goto notsup_popwlq;
#define NEED_notsup_popwlq
#endif /* ... */


}
EMU86_INTELLISENSE_END
