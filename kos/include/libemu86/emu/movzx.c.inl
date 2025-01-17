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

EMU86_INTELLISENSE_BEGIN(movzx) {


#if EMU86_EMULATE_CONFIG_WANT_MOVZX
case EMU86_OPCODE_ENCODE(0x0fb6): {
	u8 value;
	/*         0F B6 /r     MOVZX r16, r/m8     Move byte to word with zero-extension.
	 *         0F B6 /r     MOVZX r32, r/m8     Move byte to doubleword, zero-extension.
	 * REX.W + 0F B6 /r     MOVZX r64, r/m8*    Move byte to quadword, zero-extension. */
	MODRM_DECODE();
	value = MODRM_GETRMB();
	IF_64BIT(if (IS_64BIT()) {
		MODRM_SETREGQ((u64)value);
	} else) if (!IS_16BIT()) {
		MODRM_SETREGL((u32)value);
	} else {
		MODRM_SETREGW((u16)value);
	}
	goto done;
}
#elif EMU86_EMULATE_CONFIG_CHECKERROR
case EMU86_OPCODE_ENCODE(0x0fb6):
	goto notsup_modrm_getb;
#define NEED_notsup_modrm_getb
#endif /* ... */


#if EMU86_EMULATE_CONFIG_WANT_MOVZX
case EMU86_OPCODE_ENCODE(0x0fb7): {
	u16 value;
	/*         0F B7 /r     MOVZX r32, r/m16    Move word to doubleword, zero-extension.
	 * REX.W + 0F B7 /r     MOVZX r64, r/m16    Move word to quadword, zero-extension. */
	MODRM_DECODE();
	value = MODRM_GETRMW();
	IF_64BIT(if (IS_64BIT()) {
		MODRM_SETREGQ((u64)value);
	} else) {
		MODRM_SETREGL((u32)value);
	}
	goto done;
}
#elif EMU86_EMULATE_CONFIG_CHECKERROR
case EMU86_OPCODE_ENCODE(0x0fb7):
	goto notsup_modrm_getw;
#define NEED_notsup_modrm_getw
#endif /* ... */


}
EMU86_INTELLISENSE_END
