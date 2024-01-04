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

EMU86_INTELLISENSE_BEGIN(popcnt) {

#if EMU86_EMULATE_CONFIG_WANT_POPCNT
case EMU86_OPCODE_ENCODE(0x0fb8): {
	/* F3       0F B8 /r     POPCNT r16, r/m16     POPCNT on r/m16
	 * F3       0F B8 /r     POPCNT r32, r/m32     POPCNT on r/m32
	 * F3 REX.W 0F B8 /r     POPCNT r64, r/m64     POPCNT on r/m64 */
	unsigned int result;
	if unlikely(!(op_flags & EMU86_F_f3))
		goto return_unexpected_prefix;
#define NEED_return_unexpected_prefix
	MODRM_DECODE();
#ifdef EMU86_EMULATE_CONFIG_DONT_USE_HYBRID_BIT
	{
		EMU86_UREG_TYPE word;
		IF_64BIT(if (IS_64BIT()) {
			word = MODRM_GETRMQ();
		} else) if (!IS_16BIT()) {
			word = MODRM_GETRML();
		} else {
			word = MODRM_GETRMW();
		}
		result = 0;
		for (; word; word >>= 1) {
			if (word & 1)
				++result;
		}
	}
#else /* EMU86_EMULATE_CONFIG_DONT_USE_HYBRID_BIT */
	IF_64BIT(if (IS_64BIT()) {
		u64 word;
		word   = MODRM_GETRMQ();
		result = __hybrid_popcount64(word);
	} else) if (!IS_16BIT()) {
		u32 word;
		word   = MODRM_GETRML();
		result = __hybrid_popcount32(word);
	} else {
		u16 word;
		word   = MODRM_GETRMW();
		result = __hybrid_popcount16(word);
	}
#endif /* !EMU86_EMULATE_CONFIG_DONT_USE_HYBRID_BIT */
#if LIBEMU86_CONFIG_WANT_64BIT
	MODRM_SETREGQ(result);
#else /* LIBEMU86_CONFIG_WANT_64BIT */
	MODRM_SETREGL(result);
#endif /* !LIBEMU86_CONFIG_WANT_64BIT */
	EMU86_MSKFLAGS(~(EFLAGS_OF | EFLAGS_SF | EFLAGS_ZF |
	                 EFLAGS_AF | EFLAGS_CF | EFLAGS_PF),
	               result == 0 ? EFLAGS_ZF : 0);
	goto done;
}
#elif EMU86_EMULATE_CONFIG_CHECKERROR
case EMU86_OPCODE_ENCODE(0x0fb8):
	if unlikely(!(op_flags & EMU86_F_f3))
		goto return_unexpected_prefix;
#define NEED_return_unexpected_prefix
	goto notsup_modrm_getwlq;
#define NEED_notsup_modrm_getwlq
#endif /* ... */

}
EMU86_INTELLISENSE_END
