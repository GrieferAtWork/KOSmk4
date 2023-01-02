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

EMU86_INTELLISENSE_BEGIN(bound) {

#if ((EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_BOUND) && \
     (LIBEMU86_CONFIG_WANT_32BIT || LIBEMU86_CONFIG_WANT_16BIT ||            \
      (EMU86_EMULATE_CONFIG_CHECKERROR && LIBEMU86_CONFIG_WANT_64BIT)))
case EMU86_OPCODE_ENCODE(0x62): {
	/* 62 /r     BOUND r16, m16&16     Check if r16 (array index) is within bounds specified by m16&16
	 * 62 /r     BOUND r32, m32&32     Check if r32 (array index) is within bounds specified by m32&32 */
	MODRM_DECODE_MEMONLY();
#define NEED_return_expected_memory_modrm
#if LIBEMU86_CONFIG_WANT_32BIT || LIBEMU86_CONFIG_WANT_16BIT
#if LIBEMU86_CONFIG_WANT_64BIT
#define NEED_return_unsupported_instruction
	if (EMU86_F_IS64(op_flags))
		goto return_unsupported_instruction;
#endif /* LIBEMU86_CONFIG_WANT_64BIT */
	{
		s32 bound_idx, bound_min, bound_max;
		byte_t *addr;
		addr = MODRM_MEMADDR();
		if (IS_16BIT()) {
			union {
				s16 words[2];
				u32 dword;
			} temp;
			EMU86_READ_USER_MEMORY(addr, 4);
			temp.dword = EMU86_MEMREADL(addr);
			bound_min  = temp.words[0];
			bound_max  = temp.words[1] + 2;
			bound_idx  = (s32)(s16)MODRM_GETREGW();
		} else {
			union {
				s32 dwords[2];
				u64 qword;
			} temp;
			EMU86_READ_USER_MEMORY(addr, 8);
#if LIBEMU86_CONFIG_WANT_64BIT
			temp.qword = EMU86_MEMREADQ(addr);
#else /* LIBEMU86_CONFIG_WANT_64BIT */
			temp.dwords[0] = EMU86_MEMREADL(addr);
			temp.dwords[1] = EMU86_MEMREADL(addr + 4);
#endif /* !LIBEMU86_CONFIG_WANT_64BIT */
			bound_min = temp.dwords[0];
			bound_max = temp.dwords[1] + 4;
			bound_idx = (s32)MODRM_GETREGL();
		}
		if (!(bound_idx >= bound_min && bound_idx <= bound_max))
			EMU86_EMULATE_THROW_BOUNDERR(bound_idx, bound_min, bound_max);
		goto done;
	}
#else /* LIBEMU86_CONFIG_WANT_32BIT || LIBEMU86_CONFIG_WANT_16BIT */
#define NEED_return_unsupported_instruction
	goto return_unsupported_instruction;
#endif /* !LIBEMU86_CONFIG_WANT_32BIT && !LIBEMU86_CONFIG_WANT_16BIT */
}
#endif /* LIBEMU86_CONFIG_WANT_32BIT || LIBEMU86_CONFIG_WANT_16BIT || (EMU86_EMULATE_CONFIG_CHECKERROR && LIBEMU86_CONFIG_WANT_64BIT) */

}
EMU86_INTELLISENSE_END
