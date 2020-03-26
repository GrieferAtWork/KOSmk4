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

EMU86_INTELLISENSE_BEGIN(push_pop) {


#if EMU86_EMULATE_CONFIG_WANT_PUSH_REG
case EMU86_OPCODE_ENCODE(0x50) ... EMU86_OPCODE_ENCODE(0x57): {
	/* 50+rw     PUSH r16     Push r16.
	 * 50+rd     PUSH r32     Push r32.
	 * 50+rd     PUSH r64     Push r64. */
	u8 regno;
	regno = tiny_opcode - EMU86_OPCODE_ENCODE(0x50);
#if CONFIG_LIBEMU86_WANT_64BIT
	if (op_flags & EMU86_F_REX_B)
		regno |= 0x8;
#endif /* CONFIG_LIBEMU86_WANT_64BIT */
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
#if CONFIG_LIBEMU86_WANT_64BIT
	if (op_flags & EMU86_F_REX_B)
		regno |= 0x8;
#endif /* CONFIG_LIBEMU86_WANT_64BIT */
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



#if EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_POP_RM
case EMU86_OPCODE_ENCODE(0x8f): {
	MODRM_DECODE();
	if unlikely(modrm.mi_reg != 0) {
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
#endif /* EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_POP_RM */


}
EMU86_INTELLISENSE_END
