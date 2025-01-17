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

#include "string-util.h"

EMU86_INTELLISENSE_BEGIN(stos) {


#if EMU86_EMULATE_CONFIG_WANT_STOS
case EMU86_OPCODE_ENCODE(0xaa): {
	/* AA     STOSB     For  legacy mode, store AL at address ES:(E)DI;
	 *                  For 64-bit mode store AL at address RDI or EDI. */
	u8 value;
	value = EMU86_GETAL();
	EMU86_WRITE_STRING_EX_IMPL(EMU86_ADDRSIZE_SWITCH64,
	                           ES, DI, B, 8, 1, value,
	                           op_flags & EMU86_F_REP);
	if (op_flags & EMU86_F_REP)
		goto done_dont_set_pc;
#define NEED_done_dont_set_pc
	goto done;
}
#elif EMU86_EMULATE_CONFIG_CHECKERROR
case EMU86_OPCODE_ENCODE(0xaa):
	goto notsup_stosb;
#define NEED_notsup_stosb
#endif /* ... */


#if EMU86_EMULATE_CONFIG_WANT_STOS
case EMU86_OPCODE_ENCODE(0xab): {
	/*         AB     STOSW     For  legacy mode, store AX at address ES:(E)DI;
	 *                          For 64-bit mode store AX at address RDI or EDI.
	 *         AB     STOSD     For  legacy mode, store EAX at address ES:(E)DI;
	 *                          For 64-bit mode store EAX at address RDI or EDI.
	 * REX.W + AB     STOSQ     Store RAX at address RDI or EDI. */
	IF_64BIT(if (IS_64BIT()) {
		u64 value;
		value = EMU86_GETRAX();
		EMU86_WRITE_STRING_EX_IMPL(EMU86_ADDRSIZE_SWITCH64,
		                           ES, DI, Q, 64, 8, value,
		                           op_flags & EMU86_F_REP);
	} else) if (!IS_16BIT()) {
		u32 value;
		value = EMU86_GETEAX();
		EMU86_WRITE_STRING_EX_IMPL(EMU86_ADDRSIZE_SWITCH64,
		                           ES, DI, L, 32, 4, value,
		                           op_flags & EMU86_F_REP);
	} else {
		u16 value;
		value = EMU86_GETAX();
		EMU86_WRITE_STRING_EX_IMPL(EMU86_ADDRSIZE_SWITCH64,
		                           ES, DI, W, 16, 2, value,
		                           op_flags & EMU86_F_REP);
	}
	if (op_flags & EMU86_F_REP)
		goto done_dont_set_pc;
#define NEED_done_dont_set_pc
	goto done;
}
#elif EMU86_EMULATE_CONFIG_CHECKERROR
case EMU86_OPCODE_ENCODE(0xab):
	goto notsup_stoswlq;
#define NEED_notsup_stoswlq
#endif /* ... */


}
EMU86_INTELLISENSE_END
