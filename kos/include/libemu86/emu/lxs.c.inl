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

#include "push-pop-util.h"

EMU86_INTELLISENSE_BEGIN(lxs) {

	/* The register ID of the segment to use */
	u8 segment_regno;


#if (EMU86_EMULATE_CONFIG_CHECKERROR || \
     (EMU86_EMULATE_CONFIG_WANT_LXS &&  \
      (LIBEMU86_CONFIG_WANT_16BIT || LIBEMU86_CONFIG_WANT_32BIT)))
case EMU86_OPCODE_ENCODE(0xc4): {
	/* C4 /r     LES r16,m16:16     Load ES:r16 with far pointer from memory.
	 * C4 /r     LES r32,m16:32     Load ES:r32 with far pointer from memory. */
#if LIBEMU86_CONFIG_WANT_64BIT
#define NEED_return_unsupported_instruction
	if (EMU86_F_IS64(op_flags))
		goto return_unsupported_instruction;
#endif /* LIBEMU86_CONFIG_WANT_64BIT */
	segment_regno = EMU86_R_ES;
	goto do_lxs;
}

case EMU86_OPCODE_ENCODE(0xc5): {
	/* C5 /r     LDS r16,m16:16     Load DS:r16 with far pointer from memory.
	 * C5 /r     LDS r32,m16:32     Load DS:r32 with far pointer from memory. */
#if LIBEMU86_CONFIG_WANT_64BIT
#define NEED_return_unsupported_instruction
	if (EMU86_F_IS64(op_flags))
		goto return_unsupported_instruction;
#endif /* LIBEMU86_CONFIG_WANT_64BIT */
	segment_regno = EMU86_R_DS;
	goto do_lxs;
}
#endif /* ... */


#if (EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_LXS)
case EMU86_OPCODE_ENCODE(0x0fb2): {
	/*       0F B2 /r     LSS r16,m16:16     Load SS:r16 with far pointer from memory.
	 *       0F B2 /r     LSS r32,m16:32     Load SS:r32 with far pointer from memory.
	 * REX + 0F B2 /r     LSS r64,m16:64     Load SS:r64 with far pointer from memory. */
	segment_regno = EMU86_R_SS;
	goto do_lxs;
}


case EMU86_OPCODE_ENCODE(0x0fb4): {
	/*       0F B4 /r     LFS r16,m16:16     Load FS:r16 with far pointer from memory.
	 *       0F B4 /r     LFS r32,m16:32     Load FS:r32 with far pointer from memory.
	 * REX + 0F B4 /r     LFS r64,m16:64     Load FS:r64 with far pointer from memory. */
	segment_regno = EMU86_R_FS;
	goto do_lxs;
}


case EMU86_OPCODE_ENCODE(0x0fb5): {
	/*       0F B5 /r     LGS r16,m16:16     Load GS:r16 with far pointer from memory.
	 *       0F B5 /r     LGS r32,m16:32     Load GS:r32 with far pointer from memory.
	 * REX + 0F B5 /r     LGS r64,m16:64     Load GS:r64 with far pointer from memory. */
#if EMU86_EMULATE_CONFIG_CHECKUSER || EMU86_EMULATE_CONFIG_WANT_LXS
	byte_t *addr;
	u16 segment;
	EMU86_UREG_TYPE offset;
#endif /* EMU86_EMULATE_CONFIG_CHECKUSER || EMU86_EMULATE_CONFIG_WANT_LXS */
	segment_regno = EMU86_R_GS;
do_lxs:
#define NEED_return_expected_memory_modrm
	MODRM_DECODE_MEMONLY();
#if EMU86_EMULATE_CONFIG_CHECKUSER || EMU86_EMULATE_CONFIG_WANT_LXS
	addr = MODRM_MEMADDR();
	IF_64BIT(if (IS_64BIT()) {
		EMU86_READ_USER_MEMORY(addr, 10);
		segment = EMU86_MEMREADW(addr);
		offset  = EMU86_MEMREADQ(addr + 2);
	} else) if (!IS_16BIT()) {
		EMU86_READ_USER_MEMORY(addr, 6);
		segment = EMU86_MEMREADW(addr);
		offset  = EMU86_MEMREADL(addr + 2);
	} else {
		EMU86_READ_USER_MEMORY(addr, 4);
		segment = EMU86_MEMREADW(addr);
		offset  = EMU86_MEMREADW(addr + 2);
	}
#if EMU86_EMULATE_CONFIG_CHECKUSER
	/* Validate the given segment index. */
	if (!SEGMENT_IS_VALID_USERDATA(segment) && EMU86_ISUSER_NOVM86()) {
#ifdef EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER
		EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER(E_ILLEGAL_INSTRUCTION_REGISTER_WRPRV,
		                                                 X86_REGISTER_SEGMENT_ES + segment_regno,
		                                                 offset, segment, 0);
#else /* EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER */
#define NEED_return_privileged_instruction
		goto return_privileged_instruction;
#endif /* !EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER */
	}
#endif /* EMU86_EMULATE_CONFIG_CHECKUSER */
#endif /* EMU86_EMULATE_CONFIG_CHECKUSER || EMU86_EMULATE_CONFIG_WANT_LXS */
#if EMU86_EMULATE_CONFIG_WANT_LXS
	EMU86_SETSEG(segment_regno, segment);
#if LIBEMU86_CONFIG_WANT_64BIT
	MODRM_SETREGQ(offset);
#else /* LIBEMU86_CONFIG_WANT_64BIT */
	MODRM_SETREGL(offset);
#endif /* LIBEMU86_CONFIG_WANT_64BIT */
	goto done;
#else /* EMU86_EMULATE_CONFIG_WANT_LXS */
	goto return_unsupported_instruction;
#define NEED_return_unsupported_instruction
#endif /* !EMU86_EMULATE_CONFIG_WANT_LXS */
}
#endif /* EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_LXS */


}
EMU86_INTELLISENSE_END
