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

EMU86_INTELLISENSE_BEGIN(mov) {


#if EMU86_EMULATE_CONFIG_WANT_MOV_RM
case EMU86_OPCODE_ENCODE(0x88): {
	/* 88 /r      MOV r/m8,r8      Move r8 to r/m8 */
	u8 value;
	MODRM_DECODE();
	value = MODRM_GETREGB();
	MODRM_SETRMB(value);
	goto done;
}
#elif EMU86_EMULATE_CONFIG_CHECKERROR
case EMU86_OPCODE_ENCODE(0x88):
	goto notsup_modrm_setb;
#define NEED_notsup_modrm_setb
#endif /* ... */


#if EMU86_EMULATE_CONFIG_WANT_MOV_RM
case EMU86_OPCODE_ENCODE(0x89): {
	/* 89 /r      MOV r/m16,r16      Move r16 to r/m16 */
	/* 89 /r      MOV r/m32,r32      Move r32 to r/m32 */
	/* 89 /r      MOV r/m64,r64      Move r64 to r/m64 */
	MODRM_DECODE();
	IF_64BIT(if (IS_64BIT()) {
		u64 value;
		value = MODRM_GETREGQ();
		MODRM_SETRMQ(value);
	} else) if (!IS_16BIT()) {
		u32 value;
		value = MODRM_GETREGL();
		MODRM_SETRML(value);
	} else {
		u16 value;
		value = MODRM_GETREGW();
		MODRM_SETRMW(value);
	}
	goto done;
}
#elif EMU86_EMULATE_CONFIG_CHECKERROR
case EMU86_OPCODE_ENCODE(0x89):
	goto notsup_modrm_setwlq;
#define NEED_notsup_modrm_setwlq
#endif /* ... */


#if EMU86_EMULATE_CONFIG_WANT_MOV_RM
case EMU86_OPCODE_ENCODE(0x8a): {
	/* 8A /r      MOV r8,r/m8      Move r/m8 to r8 */
	u8 value;
	MODRM_DECODE();
	value = MODRM_GETRMB();
	MODRM_SETREGB(value);
	goto done;
}
#elif EMU86_EMULATE_CONFIG_CHECKERROR
case EMU86_OPCODE_ENCODE(0x8a):
	goto notsup_modrm_getb;
#define NEED_notsup_modrm_getb
#endif /* ... */


#if EMU86_EMULATE_CONFIG_WANT_MOV_RM
case EMU86_OPCODE_ENCODE(0x8b): {
	/* 8b /r      MOV r16,r/m16      Move r/m16 to r16 */
	/* 8b /r      MOV r32,r/m32      Move r/m32 to r32 */
	/* 8b /r      MOV r64,r/m64      Move r/m64 to r64 */
	MODRM_DECODE();
	IF_64BIT(if (IS_64BIT()) {
		u64 value;
		value = MODRM_GETRMQ();
		MODRM_SETREGQ(value);
	} else) if (!IS_16BIT()) {
		u32 value;
		value = MODRM_GETRML();
		MODRM_SETREGL(value);
	} else {
		u16 value;
		value = MODRM_GETRMW();
		MODRM_SETREGW(value);
	}
	goto done;
}
#elif EMU86_EMULATE_CONFIG_CHECKERROR
case EMU86_OPCODE_ENCODE(0x8b):
	goto notsup_modrm_getwlq;
#define NEED_notsup_modrm_getwlq
#endif /* ... */


}
EMU86_INTELLISENSE_END
