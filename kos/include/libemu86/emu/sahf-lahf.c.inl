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

EMU86_INTELLISENSE_BEGIN(sahf_lahf) {

#if !EMU86_EMULATE_CONFIG_ONLY_MEMORY

#define AHF_MASK (EFLAGS_CF | EFLAGS_PF | EFLAGS_AF | EFLAGS_ZF | EFLAGS_SF)

#if EMU86_EMULATE_CONFIG_WANT_SAHF
case EMU86_OPCODE_ENCODE(0x9e): {
	/* 9E     SAHF     Loads SF, ZF, AF, PF, and CF from AH into EFLAGS register. */
	u8 ah = EMU86_GETAH();
	EMU86_MSKFLAGS(~AHF_MASK, ah & AHF_MASK);
	goto done;
}
#elif EMU86_EMULATE_CONFIG_CHECKERROR && !EMU86_EMULATE_CONFIG_ONLY_CHECKERROR_NO_BASIC
case EMU86_OPCODE_ENCODE(0x9e):
	goto return_unsupported_instruction;
#define NEED_return_unsupported_instruction
#endif /* ... */


#if EMU86_EMULATE_CONFIG_WANT_SAHF
case EMU86_OPCODE_ENCODE(0x9f): {
	/* 9F     LAHF     Load: AH := EFLAGS(SF:ZF:0:AF:0:PF:1:CF). */
	u8 ah;
	ah = (u8)(EMU86_GETFLAGS() & AHF_MASK) |
	     0x02; /* bit#1 is documented as always-set-to-1 */
	EMU86_SETAH(ah);
	goto done;
}
#elif EMU86_EMULATE_CONFIG_CHECKERROR && !EMU86_EMULATE_CONFIG_ONLY_CHECKERROR_NO_BASIC
case EMU86_OPCODE_ENCODE(0x9f):
	goto return_unsupported_instruction;
#define NEED_return_unsupported_instruction
#endif /* ... */

#undef AHF_MASK

#endif /* !EMU86_EMULATE_CONFIG_ONLY_MEMORY */

}
EMU86_INTELLISENSE_END
