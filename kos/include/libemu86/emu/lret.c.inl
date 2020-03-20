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


EMU86_INTELLISENSE_BEGIN(lret) {


case 0xcb: {
	/* CB     RET     Far return to calling procedure. */
	u16 cs;
	byte_t *sp;
	EMU86_UREG_TYPE ip;
	sp = EMU86_GETSTACKPTR();
	IF_64BIT(if (IS_64BIT()) {
		EMU86_EMULATE_POP(sp, 16);
		EMU86_READ_USER_MEMORY(sp, 16);
		ip = EMU86_MEMREADQ(sp + 0);
		cs = EMU86_MEMREADQASW(sp + 8);
		sp += 16;
	} else) if (!IS_16BIT()) {
		EMU86_EMULATE_POP(sp, 8);
		EMU86_READ_USER_MEMORY(sp, 8);
		ip = EMU86_MEMREADL(sp + 0);
		cs = EMU86_MEMREADLASW(sp + 4);
		sp += 8;
	} else {
		EMU86_EMULATE_POP(sp, 4);
		EMU86_READ_USER_MEMORY(sp, 4);
		cs = EMU86_MEMREADW(sp + 0);
		ip = EMU86_MEMREADW(sp + 2);
		sp += 4;
	}
#if EMU86_EMULATE_CHECKUSER
	/* Verify the given `cs' segment. */
	if (!SEGMENT_IS_VALID_USERCODE(cs) && EMU86_ISUSER_NOVM86()) {
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_SIGRETURN_REGISTER,
		      X86_REGISTER_SEGMENT_CS, cs);
	}
#endif /* EMU86_EMULATE_CHECKUSER */
	EMU86_SETSTACKPTR(sp);
	EMU86_SETCS(cs);
	EMU86_SETIPREG(ip);
	goto done_dont_set_pc;
}


case 0xca: {
	/* CA iw     RET imm16     Far return to calling procedure and pop imm16 bytes from stack. */
	u16 cs;
	byte_t *sp;
	u16 offset;
	EMU86_UREG_TYPE ip;
	offset = UNALIGNED_GET16((u16 *)pc);
	pc += 2;
	sp = EMU86_GETSTACKPTR();
	IF_64BIT(if (IS_64BIT()) {
		EMU86_EMULATE_POP(sp, 16);
		EMU86_READ_USER_MEMORY(sp, 16);
		ip = EMU86_MEMREADQ(sp + 0);
		cs = EMU86_MEMREADQASW(sp + 8);
		sp += 16;
	} else) if (!IS_16BIT()) {
		EMU86_EMULATE_POP(sp, 8);
		EMU86_READ_USER_MEMORY(sp, 8);
		ip = EMU86_MEMREADL(sp + 0);
		cs = EMU86_MEMREADLASW(sp + 4);
		sp += 8;
	} else {
		EMU86_EMULATE_POP(sp, 4);
		EMU86_READ_USER_MEMORY(sp, 4);
		cs = EMU86_MEMREADW(sp + 0);
		ip = EMU86_MEMREADW(sp + 2);
		sp += 4;
	}
#if EMU86_EMULATE_CHECKUSER
	/* Verify the given `cs' segment. */
	if (!SEGMENT_IS_VALID_USERCODE(cs) && EMU86_ISUSER_NOVM86()) {
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_SIGRETURN_REGISTER,
		      X86_REGISTER_SEGMENT_CS, cs);
	}
#endif /* EMU86_EMULATE_CHECKUSER */
	sp += offset;
	EMU86_SETSTACKPTR(sp);
	EMU86_SETCS(cs);
	EMU86_SETIPREG(ip);
	goto done_dont_set_pc;
}


}
EMU86_INTELLISENSE_END
