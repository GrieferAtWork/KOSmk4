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

#include "string-util.h"

EMU86_INTELLISENSE_BEGIN(lods) {


#if EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_LODS
case EMU86_OPCODE_ENCODE(0xac): {
	/* AC     LODSB     For legacy mode, Load byte at address DS:(E)SI into AL.
	 *                  For  64-bit mode  load byte  at address  (R)SI into AL. */
#if EMU86_EMULATE_CONFIG_WANT_LODS
	u8 value;
	EMU86_READ_STRING_EX_IMPL(EMU86_ADDRSIZE_SWITCH64,
	                          DS, SI, B, 8, 1, value,
	                          op_flags & EMU86_F_REP,
	                          /**/);
	EMU86_SETAL(value);
	if (op_flags & EMU86_F_REP)
		goto done_dont_set_pc;
#define NEED_done_dont_set_pc
	goto done;
#else /* EMU86_EMULATE_CONFIG_WANT_LODS */
	goto notsup_lodsb;
#define NEED_notsup_lodsb
#endif /* !EMU86_EMULATE_CONFIG_WANT_LODS */
}

case EMU86_OPCODE_ENCODE(0xad): {
	/*         AD     LODSW     For legacy mode, Load word at address DS:(E)SI into AX.
	 *                          For  64-bit mode  load word  at address  (R)SI into AX.
	 *         AD     LODSD     For legacy mode, Load dword at address DS:(E)SI into EAX.
	 *                          For  64-bit mode  load dword  at address  (R)SI into EAX.
	 * REX.W + AD     LODSQ     Load qword at address (R)SI into RAX. */
#if EMU86_EMULATE_CONFIG_WANT_LODS
	IF_64BIT(if (IS_64BIT()) {
		u64 value;
		EMU86_READ_STRING_EX_IMPL(EMU86_ADDRSIZE_SWITCH64,
		                          DS, SI, Q, 64, 8, value,
		                          op_flags & EMU86_F_REP,
		                          /**/);
		EMU86_SETRAX(value);
	} else) if (!IS_16BIT()) {
		u32 value;
		EMU86_READ_STRING_EX_IMPL(EMU86_ADDRSIZE_SWITCH64,
		                          DS, SI, L, 32, 4, value,
		                          op_flags & EMU86_F_REP,
		                          /**/);
		EMU86_SETEAX(value);
	} else {
		u16 value;
		EMU86_READ_STRING_EX_IMPL(EMU86_ADDRSIZE_SWITCH64,
		                          DS, SI, W, 16, 2, value,
		                          op_flags & EMU86_F_REP,
		                          /**/);
		EMU86_SETAX(value);
	}
	if (op_flags & EMU86_F_REP)
		goto done_dont_set_pc;
#define NEED_done_dont_set_pc
	goto done;
#else /* EMU86_EMULATE_CONFIG_WANT_LODS */
	goto notsup_lodswlq;
#define NEED_notsup_lodswlq
#endif /* !EMU86_EMULATE_CONFIG_WANT_LODS */
}
#endif /* EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_LODS */


}
EMU86_INTELLISENSE_END
