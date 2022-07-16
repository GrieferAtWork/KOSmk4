/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifdef __INTELLISENSE__
#include "../emulate.c.inl"
#endif /* __INTELLISENSE__ */

EMU86_INTELLISENSE_BEGIN(bswap) {

#if !EMU86_EMULATE_CONFIG_ONLY_MEMORY

#if EMU86_EMULATE_CONFIG_WANT_BSWAP
case EMU86_OPCODE_ENCODE(0x0fc8) ... EMU86_OPCODE_ENCODE(0x0fcf): {
	/*         0F C8+rd     BSWAP r32     Reverses the byte order of a 32-bit register.
	 * REX.W + 0F C8+rd     BSWAP r64     Reverses the byte order of a 64-bit register. */
	u8 regno;
	regno = tiny_opcode - EMU86_OPCODE_ENCODE(0x0fc8);
#if LIBEMU86_CONFIG_WANT_64BIT
	if (op_flags & EMU86_F_REX_B)
		regno |= 0x8;
	if (IS_64BIT()) {
#ifdef EMU86_EMULATE_CONFIG_DONT_USE_HYBRID_BYTESWAP
		union {
			u8  bytes[8];
			u64 qword;
		} oldval, newval;
		oldval.qword = EMU86_GETREGQ(regno);
		newval.bytes[0] = oldval.bytes[7];
		newval.bytes[1] = oldval.bytes[6];
		newval.bytes[2] = oldval.bytes[5];
		newval.bytes[3] = oldval.bytes[4];
		newval.bytes[4] = oldval.bytes[3];
		newval.bytes[5] = oldval.bytes[2];
		newval.bytes[6] = oldval.bytes[1];
		newval.bytes[7] = oldval.bytes[0];
		EMU86_SETREGQ(regno, newval.qword);
#else /* EMU86_EMULATE_CONFIG_DONT_USE_HYBRID_BYTESWAP */
		u64 temp;
		temp = EMU86_GETREGQ(regno);
		temp = BSWAP64(temp);
		EMU86_SETREGQ(regno, temp);
#endif /* !EMU86_EMULATE_CONFIG_DONT_USE_HYBRID_BYTESWAP */
	} else
#endif /* LIBEMU86_CONFIG_WANT_64BIT */
	{
#ifdef EMU86_EMULATE_CONFIG_DONT_USE_HYBRID_BYTESWAP
		union {
			u8  bytes[4];
			u32 dword;
		} oldval, newval;
		oldval.dword = EMU86_GETREGL(regno);
		newval.bytes[0] = oldval.bytes[3];
		newval.bytes[1] = oldval.bytes[2];
		newval.bytes[2] = oldval.bytes[1];
		newval.bytes[3] = oldval.bytes[0];
		EMU86_SETREGL(regno, newval.dword);
#else /* EMU86_EMULATE_CONFIG_DONT_USE_HYBRID_BYTESWAP */
		u32 temp;
		temp = EMU86_GETREGL(regno);
		temp = BSWAP32(temp);
		EMU86_SETREGL(regno, temp);
#endif /* !EMU86_EMULATE_CONFIG_DONT_USE_HYBRID_BYTESWAP */
	}
	goto done;
}
#elif EMU86_EMULATE_CONFIG_CHECKERROR && !EMU86_EMULATE_CONFIG_ONLY_CHECKERROR_NO_BASIC
case EMU86_OPCODE_ENCODE(0x0fc8) ... EMU86_OPCODE_ENCODE(0x0fcf):
	goto return_unsupported_instruction;
#define NEED_return_unsupported_instruction
#endif /* ... */

#endif /* !EMU86_EMULATE_CONFIG_ONLY_MEMORY */

}
EMU86_INTELLISENSE_END
