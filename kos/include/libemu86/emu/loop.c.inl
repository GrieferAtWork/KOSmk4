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

EMU86_INTELLISENSE_BEGIN(loop) {


#if !EMU86_EMULATE_CONFIG_ONLY_MEMORY

#if (EMU86_EMULATE_CONFIG_WANT_LOOPNE || \
     EMU86_EMULATE_CONFIG_WANT_LOOPE || \
     EMU86_EMULATE_CONFIG_WANT_LOOP)
case EMU86_OPCODE_ENCODE(0xe0):   /* E0 cb     LOOPNE rel8     Decrement count; jump short if count!=0 and ZF=0. */
case EMU86_OPCODE_ENCODE(0xe1):   /* E1 cb     LOOPE rel8      Decrement count; jump short if count!=0 and ZF=1. */
case EMU86_OPCODE_ENCODE(0xe2): { /* E2 cb     LOOP rel8       Decrement count; jump short if count!=0. */
	pc += 1; /* rel8 */
	EMU86_ADDRSIZE_SWITCH({
		u64 rcx = EMU86_GETRCX() - 1;
		EMU86_SETRCX(rcx);
		if (!rcx)
			goto done;
	}, {
		u32 ecx = EMU86_GETECX() - 1;
		EMU86_SETECX(ecx);
		if (!ecx)
			goto done;
	}, {
		u16 cx = EMU86_GETCX() - 1;
		EMU86_SETCX(cx);
		if (!cx)
			goto done;
	});
	/* Check additional conditions based on `tiny_opcode' */
	switch (tiny_opcode) {

	case EMU86_OPCODE_ENCODE(0xe0):
		/* E0 cb     LOOPNE rel8     Decrement count; jump short if count!=0 and ZF=0. */
		if (EMU86_GETFLAGS() & EFLAGS_ZF)
			goto done; /* ZF==1 -> Don't jump */
		break;

	case EMU86_OPCODE_ENCODE(0xe1):
		/* E1 cb     LOOPE rel8      Decrement count; jump short if count!=0 and ZF=1. */
		if (!(EMU86_GETFLAGS() & EFLAGS_ZF))
			goto done; /* ZF==0 -> Don't jump */
		break;

	case EMU86_OPCODE_ENCODE(0xe2):
		/* E2 cb     LOOP rel8       Decrement count; jump short if count!=0. */
		break;

	default: __builtin_unreachable();
	}
	/* Follow the loop branch */
	{
		EMU86_UREG_TYPE dest_ip;
		s8 offset = ((s8 *)pc)[-1];
		dest_ip   = REAL_IP() + offset;
		if (IS_16BIT())
			dest_ip &= 0xffff;
		EMU86_SETIPREG(dest_ip);
		goto done_dont_set_pc;
#define NEED_done_dont_set_pc
	}
}
#elif EMU86_EMULATE_CONFIG_CHECKERROR && !EMU86_EMULATE_CONFIG_ONLY_CHECKERROR_NO_BASIC
case EMU86_OPCODE_ENCODE(0xe0):
case EMU86_OPCODE_ENCODE(0xe1):
case EMU86_OPCODE_ENCODE(0xe2):
	goto return_unsupported_instruction;
#define NEED_return_unsupported_instruction
#endif /* ... */

#endif /* !EMU86_EMULATE_CONFIG_ONLY_MEMORY */

}
EMU86_INTELLISENSE_END
