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

EMU86_INTELLISENSE_BEGIN(push_imm) {


#if EMU86_EMULATE_CONFIG_WANT_PUSH_IMM
{
	EMU86_UREG_TYPE imm;
case EMU86_OPCODE_ENCODE(0x6a):
	imm = (EMU86_UREG_TYPE)(EMU86_SREG_TYPE)(*(s8 const *)pc);
	pc += 1;
	goto do_push_imm;
case EMU86_OPCODE_ENCODE(0x68):
	/* 6A ib     PUSH imm8      Push imm8.
	 * 68 iw     PUSH imm16     Push imm16.
	 * 68 id     PUSH imm32     Push imm32. */
	if (IS_16BIT()) {
		imm = (EMU86_UREG_TYPE)(EMU86_SREG_TYPE)(s16)UNALIGNED_GETLE16(pc);
		pc += 2;
	} else {
		imm = (EMU86_UREG_TYPE)(EMU86_SREG_TYPE)(s32)UNALIGNED_GETLE32(pc);
		pc += 4;
	}
do_push_imm:
	EMU86_PUSH163264((u16)imm,
	                 (u32)imm,
	                 (u64)imm);
	goto done;
}
#elif EMU86_EMULATE_CONFIG_CHECKERROR
case EMU86_OPCODE_ENCODE(0x6a):
case EMU86_OPCODE_ENCODE(0x68):
	goto notsup_pushwlq;
#define NEED_notsup_pushwlq
#endif /* ... */


}
EMU86_INTELLISENSE_END
