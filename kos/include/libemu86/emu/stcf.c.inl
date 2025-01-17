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

EMU86_INTELLISENSE_BEGIN(stcf) {

#if !EMU86_EMULATE_CONFIG_ONLY_MEMORY

	/* Instructions that modify the EFLAGS.CF (carry) bit. */

#if EMU86_EMULATE_CONFIG_WANT_CMC
case EMU86_OPCODE_ENCODE(0xf5): {
	/* F5     CMC     Complement CF flag. */
	u32 flags;
	flags = EMU86_GETFLAGS();
	flags ^= EFLAGS_CF;
	EMU86_SETFLAGS(flags);
	goto done;
}
#elif EMU86_EMULATE_CONFIG_CHECKERROR && !EMU86_EMULATE_CONFIG_ONLY_CHECKERROR_NO_BASIC
case EMU86_OPCODE_ENCODE(0xf5):
	goto return_unsupported_instruction;
#define NEED_return_unsupported_instruction
#endif /* ... */


#if EMU86_EMULATE_CONFIG_WANT_CLC
case EMU86_OPCODE_ENCODE(0xf8): {
	/* F8     CLC     Clear CF flag. */
	EMU86_MSKFLAGS(~EFLAGS_CF, 0);
	goto done;
}
#elif EMU86_EMULATE_CONFIG_CHECKERROR && !EMU86_EMULATE_CONFIG_ONLY_CHECKERROR_NO_BASIC
case EMU86_OPCODE_ENCODE(0xf8):
	goto return_unsupported_instruction;
#define NEED_return_unsupported_instruction
#endif /* ... */


#if EMU86_EMULATE_CONFIG_WANT_STC
case EMU86_OPCODE_ENCODE(0xf9): {
	/* F9     STC     Set CF flag. */
	EMU86_MSKFLAGS(~EFLAGS_CF, EFLAGS_CF);
	goto done;
}
#elif EMU86_EMULATE_CONFIG_CHECKERROR && !EMU86_EMULATE_CONFIG_ONLY_CHECKERROR_NO_BASIC
case EMU86_OPCODE_ENCODE(0xf9):
	goto return_unsupported_instruction;
#define NEED_return_unsupported_instruction
#endif /* ... */

#endif /* !EMU86_EMULATE_CONFIG_ONLY_MEMORY */

}
EMU86_INTELLISENSE_END
