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

EMU86_INTELLISENSE_BEGIN(movdir64b) {


#if EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_MOVDIR64B
case EMU86_OPCODE_ENCODE(0x0f38f8): {
	/* 66 0F 38 F8 /r     MOVDIR64B r16/r32/r64, m512     Move  64-bytes as direct-store with guaranteed 64-byte
	 *                                                    write atomicity from the source memory operand address
	 *                                                    to  destination memory address  specified as offset to
	 *                                                    ES segment in the register operand. */
	byte_t *dstaddr;
	byte_t *srcaddr;
	MODRM_DECODE_MEMONLY();
#define NEED_return_expected_memory_modrm
	dstaddr = EMU86_SEGADDR(EMU86_GETESBASE(),
	                        EMU86_GETREGP(modrm.mi_reg, op_flags));
	srcaddr = MODRM_MEMADDR();
	if (!IS_ALIGNED((uintptr_t)dstaddr, 16))
		EMU86_EMULATE_THROW_SEGFAULT_UNALIGNED(dstaddr, E_SEGFAULT_CONTEXT_WRITING, 16);
	EMU86_UNSUPPORTED_MEMACCESS(srcaddr, 64, true, false);
	EMU86_UNSUPPORTED_MEMACCESS(dstaddr, 64, false, true);

	/* We sadly don't have any way of emulating this instruction...
	 * The  problem is that it would require us to somehow provide a 512-bit atomic
	 * write (or better yet: 512-bit atomic  cmpxchg) method which we simply  don't
	 * have. So the best we can do is check for error conditions, before indicating
	 * that the instruction simply isn't supported... */
	(void)dstaddr;
	(void)srcaddr;

#define NEED_return_unsupported_instruction
	goto return_unsupported_instruction;
}
#endif /* EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_MOVDIR64B */


}
EMU86_INTELLISENSE_END
