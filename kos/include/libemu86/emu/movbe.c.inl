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

EMU86_INTELLISENSE_BEGIN(movbe) {


#if EMU86_EMULATE_CONFIG_WANT_MOVBE
case EMU86_OPCODE_ENCODE(0x0f38f0): {
	/*         0F 38 F0 /r     MOVBE r16, m16     Reverse byte order in m16 and move to r16.
	 *         0F 38 F0 /r     MOVBE r32, m32     Reverse byte order in m32 and move to r32.
	 * REX.W + 0F 38 F0 /r     MOVBE r64, m64     Reverse byte order in m64 and move to r64. */
	byte_t *addr;
	MODRM_DECODE_MEMONLY();
#define NEED_return_expected_memory_modrm
	addr = MODRM_MEMADDR();
#ifdef EMU86_EMULATE_CONFIG_DONT_USE_HYBRID_BYTESWAP
	IF_64BIT(if (IS_64BIT()) {
		union {
			u8  bytes[8];
			u64 qword;
		} oldword, newword;
		EMU86_READ_USER_MEMORY(addr, 8);
		oldword.qword = EMU86_MEMREADQ(addr);
		newword.bytes[0] = oldword.bytes[7];
		newword.bytes[1] = oldword.bytes[6];
		newword.bytes[2] = oldword.bytes[5];
		newword.bytes[3] = oldword.bytes[4];
		newword.bytes[4] = oldword.bytes[3];
		newword.bytes[5] = oldword.bytes[2];
		newword.bytes[6] = oldword.bytes[1];
		newword.bytes[7] = oldword.bytes[0];
		MODRM_SETREGQ(newword.qword);
	} else) if (!IS_16BIT()) {
		union {
			u8  bytes[4];
			u32 dword;
		} oldword, newword;
		EMU86_READ_USER_MEMORY(addr, 4);
		oldword.dword = EMU86_MEMREADL(addr);
		newword.bytes[0] = oldword.bytes[3];
		newword.bytes[1] = oldword.bytes[2];
		newword.bytes[2] = oldword.bytes[1];
		newword.bytes[3] = oldword.bytes[0];
		MODRM_SETREGL(newword.dword);
	} else {
		union {
			u8  bytes[2];
			u16 word;
		} oldword, newword;
		EMU86_READ_USER_MEMORY(addr, 2);
		oldword.word = EMU86_MEMREADW(addr);
		newword.bytes[0] = oldword.bytes[1];
		newword.bytes[1] = oldword.bytes[0];
		MODRM_SETREGW(newword.word);
	}
#else /* EMU86_EMULATE_CONFIG_DONT_USE_HYBRID_BYTESWAP */
	IF_64BIT(if (IS_64BIT()) {
		u64 oldword, newword;
		EMU86_READ_USER_MEMORY(addr, 8);
		oldword = EMU86_MEMREADQ(addr);
		newword = BSWAP64(oldword);
		MODRM_SETREGQ(newword);
	} else) if (!IS_16BIT()) {
		u32 oldword, newword;
		EMU86_READ_USER_MEMORY(addr, 4);
		oldword = EMU86_MEMREADL(addr);
		newword = BSWAP32(oldword);
		MODRM_SETREGL(newword);
	} else {
		u16 oldword, newword;
		EMU86_READ_USER_MEMORY(addr, 2);
		oldword = EMU86_MEMREADW(addr);
		newword = BSWAP16(oldword);
		MODRM_SETREGW(newword);
	}
#endif /* !EMU86_EMULATE_CONFIG_DONT_USE_HYBRID_BYTESWAP */
	goto done;
}
#elif EMU86_EMULATE_CONFIG_CHECKERROR
case EMU86_OPCODE_ENCODE(0x0f38f0):
	goto notsup_modrm_getwlq;
#define NEED_notsup_modrm_getwlq
#endif /* ... */


#if EMU86_EMULATE_CONFIG_WANT_MOVBE
case EMU86_OPCODE_ENCODE(0x0f38f1): {
	/*         0F 38 F1 /r     MOVBE m16, r16     Reverse byte order in r16 and move to m16.
	 *         0F 38 F1 /r     MOVBE m32, r32     Reverse byte order in r32 and move to m32.
	 * REX.W + 0F 38 F1 /r     MOVBE m64, r64     Reverse byte order in r64 and move to m64. */
	byte_t *addr;
	MODRM_DECODE_MEMONLY();
#define NEED_return_expected_memory_modrm
	addr = MODRM_MEMADDR();
#ifdef EMU86_EMULATE_CONFIG_DONT_USE_HYBRID_BYTESWAP
	IF_64BIT(if (IS_64BIT()) {
		union {
			u8  bytes[8];
			u64 qword;
		} oldword, newword;
		EMU86_WRITE_USER_MEMORY(addr, 8);
		oldword.qword = MODRM_GETREGQ();
		newword.bytes[0] = oldword.bytes[7];
		newword.bytes[1] = oldword.bytes[6];
		newword.bytes[2] = oldword.bytes[5];
		newword.bytes[3] = oldword.bytes[4];
		newword.bytes[4] = oldword.bytes[3];
		newword.bytes[5] = oldword.bytes[2];
		newword.bytes[6] = oldword.bytes[1];
		newword.bytes[7] = oldword.bytes[0];
		EMU86_MEMWRITEQ(addr, newword.qword);
	} else) if (!IS_16BIT()) {
		union {
			u8  bytes[4];
			u32 dword;
		} oldword, newword;
		EMU86_WRITE_USER_MEMORY(addr, 4);
		oldword.dword = MODRM_GETREGL();
		newword.bytes[0] = oldword.bytes[3];
		newword.bytes[1] = oldword.bytes[2];
		newword.bytes[2] = oldword.bytes[1];
		newword.bytes[3] = oldword.bytes[0];
		EMU86_MEMWRITEL(addr, newword.dword);
	} else {
		union {
			u8  bytes[2];
			u16 word;
		} oldword, newword;
		EMU86_WRITE_USER_MEMORY(addr, 2);
		oldword.word = MODRM_GETREGW();
		newword.bytes[0] = oldword.bytes[1];
		newword.bytes[1] = oldword.bytes[0];
		EMU86_MEMWRITEW(addr, newword.word);
	}
#else /* EMU86_EMULATE_CONFIG_DONT_USE_HYBRID_BYTESWAP */
	IF_64BIT(if (IS_64BIT()) {
		u64 oldword, newword;
		EMU86_WRITE_USER_MEMORY(addr, 8);
		oldword = MODRM_GETREGQ();
		newword = BSWAP64(oldword);
		EMU86_MEMWRITEQ(addr, newword);
	} else) if (!IS_16BIT()) {
		u32 oldword, newword;
		EMU86_WRITE_USER_MEMORY(addr, 4);
		oldword = MODRM_GETREGL();
		newword = BSWAP32(oldword);
		EMU86_MEMWRITEL(addr, newword);
	} else {
		u16 oldword, newword;
		EMU86_WRITE_USER_MEMORY(addr, 2);
		oldword = MODRM_GETREGW();
		newword = BSWAP16(oldword);
		EMU86_MEMWRITEW(addr, newword);
	}
#endif /* !EMU86_EMULATE_CONFIG_DONT_USE_HYBRID_BYTESWAP */
	goto done;
}
#elif EMU86_EMULATE_CONFIG_CHECKERROR
case EMU86_OPCODE_ENCODE(0x0f38f1):
	goto notsup_modrm_setwlq;
#define NEED_notsup_modrm_setwlq
#endif /* ... */


}
EMU86_INTELLISENSE_END
