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

EMU86_INTELLISENSE_BEGIN(clts) {

#if !EMU86_EMULATE_CONFIG_ONLY_MEMORY

#if EMU86_EMULATE_CONFIG_WANT_CLTS
case EMU86_OPCODE_ENCODE(0x0f06): {
	/* 0F 06     CLTS     Clears TS flag in CR0. */
#ifdef EMU86_EMULATE_CLTS
	EMU86_EMULATE_CLTS();
	goto done;
#else /* EMU86_EMULATE_CLTS */
	goto return_unsupported_instruction;
#define NEED_return_unsupported_instruction
#endif /* !EMU86_EMULATE_CLTS */
}
#elif EMU86_EMULATE_CONFIG_CHECKERROR && !EMU86_EMULATE_CONFIG_ONLY_CHECKERROR_NO_BASIC
case EMU86_OPCODE_ENCODE(0x0f06):
	goto return_unsupported_instruction;
#define NEED_return_unsupported_instruction
#endif /* ... */

#endif /* !EMU86_EMULATE_CONFIG_ONLY_MEMORY */

}
EMU86_INTELLISENSE_END
