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

EMU86_INTELLISENSE_BEGIN(movsx) {


#if EMU86_EMULATE_CONFIG_WANT_MOVSX
case EMU86_OPCODE_ENCODE(0x0fbe): {
	s8 value;
	/*         0F B6 /r     MOVSX r16, r/m8     Move byte to word with sign-extension.
	 *         0F B6 /r     MOVSX r32, r/m8     Move byte to doubleword, sign-extension.
	 * REX.W + 0F B6 /r     MOVSX r64, r/m8*    Move byte to quadword, sign-extension. */
	MODRM_DECODE();
	value = (s8)MODRM_GETRMB();
	IF_64BIT(if (IS_64BIT()) {
		MODRM_SETREGQ((u64)(s64)value);
	} else) if (!IS_16BIT()) {
		MODRM_SETREGL((u32)(s32)value);
	} else {
		MODRM_SETREGW((u16)(s16)value);
	}
	goto done;
}
#elif EMU86_EMULATE_CONFIG_CHECKERROR
case EMU86_OPCODE_ENCODE(0x0fbe):
	goto notsup_modrm_getb;
#define NEED_notsup_modrm_getb
#endif /* ... */


#if EMU86_EMULATE_CONFIG_WANT_MOVSX
case EMU86_OPCODE_ENCODE(0x0fbf): {
	s16 value;
	/*         0F B7 /r     MOVSX r32, r/m16    Move word to doubleword, sign-extension.
	 * REX.W + 0F B7 /r     MOVSX r64, r/m16    Move word to quadword, sign-extension. */
	MODRM_DECODE();
	value = (s16)MODRM_GETRMW();
	IF_64BIT(if (IS_64BIT()) {
		MODRM_SETREGQ((u64)(s64)value);
	} else) {
		MODRM_SETREGL((u32)(s32)value);
	}
	goto done;
}
#elif EMU86_EMULATE_CONFIG_CHECKERROR
case EMU86_OPCODE_ENCODE(0x0fbf):
	goto notsup_modrm_getw;
#define NEED_notsup_modrm_getw
#endif /* ... */


}
EMU86_INTELLISENSE_END
