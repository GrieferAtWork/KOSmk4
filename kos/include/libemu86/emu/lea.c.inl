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

EMU86_INTELLISENSE_BEGIN(lea) {

#if !EMU86_EMULATE_CONFIG_ONLY_MEMORY
#if EMU86_EMULATE_CONFIG_WANT_LEA
case EMU86_OPCODE_ENCODE(0x8d): {
	/*         8D /r     LEA r16,m     RM     Valid     Valid     Store effective address for m in register r16.
	 *         8D /r     LEA r32,m     RM     Valid     Valid     Store effective address for m in register r32.
	 * REX.W + 8D /r     LEA r64,m     RM     Valid     N.E.      Store effective address for m in register r64. */
	uintptr_t addr;
#define NEED_return_expected_memory_modrm
	MODRM_DECODE_MEMONLY();
	addr = (uintptr_t)MODRM_MEMADDR_NOSEGBASE();
	IF_64BIT(if (IS_64BIT()) {
		MODRM_SETREGQ((u64)addr);
	} else) if (!IS_16BIT()) {
		MODRM_SETREGL((u32)addr);
	} else {
		MODRM_SETREGW((u16)addr);
	}
	goto done;
}
#else /* EMU86_EMULATE_CONFIG_WANT_LEA */
case EMU86_OPCODE_ENCODE(0x8d):
	goto return_unsupported_instruction;
#define NEED_return_unsupported_instruction
#endif /* !EMU86_EMULATE_CONFIG_WANT_LEA */
#endif /* !EMU86_EMULATE_CONFIG_ONLY_MEMORY */

}
EMU86_INTELLISENSE_END
