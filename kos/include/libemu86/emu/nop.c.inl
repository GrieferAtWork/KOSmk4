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

EMU86_INTELLISENSE_BEGIN(nop) {


#if !EMU86_EMULATE_CONFIG_ONLY_MEMORY
#if EMU86_EMULATE_CONFIG_WANT_NOP_RM
case EMU86_OPCODE_ENCODE(0x0f1f):
	/* NP 0F 1F /0     NOP r/m16     Multi-byte no-operation instruction.
	 * NP 0F 1F /0     NOP r/m32     Multi-byte no-operation instruction. */
	MODRM_DECODE();
	if (modrm.mi_reg != 0) {
		goto return_unknown_instruction_rmreg;
#define NEED_return_unknown_instruction_rmreg
	}
	goto done;
#elif EMU86_EMULATE_CONFIG_CHECKERROR && !EMU86_EMULATE_CONFIG_ONLY_CHECKERROR_NO_BASIC
case EMU86_OPCODE_ENCODE(0x0f1f):
	MODRM_DECODE();
	if (modrm.mi_reg != 0) {
		goto return_unknown_instruction_rmreg;
#define NEED_return_unknown_instruction_rmreg
	}
	goto return_unsupported_instruction_rmreg;
#define NEED_return_unsupported_instruction_rmreg
#endif /* ... */
#endif /* !EMU86_EMULATE_CONFIG_ONLY_MEMORY */


}
EMU86_INTELLISENSE_END
