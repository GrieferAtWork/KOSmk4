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

EMU86_INTELLISENSE_BEGIN(hlt) {


#if !EMU86_EMULATE_CONFIG_ONLY_MEMORY

#if EMU86_EMULATE_CONFIG_WANT_HLT
case EMU86_OPCODE_ENCODE(0xf4): {
	/* F4     HLT     Halt */
#if EMU86_EMULATE_CONFIG_VM86
	if (EMU86_ISVM86()) {
		EMU86_SETPCPTR(REAL_IP());
		EMU86_EMULATE_RETURN_AFTER_HLT_VM86();
		__builtin_unreachable();
	}
#endif /* EMU86_EMULATE_CONFIG_VM86 */

#if EMU86_EMULATE_CONFIG_CHECKUSER
	if (EMU86_ISUSER())
		goto return_privileged_instruction;
#define NEED_return_privileged_instruction
#endif /* EMU86_EMULATE_CONFIG_CHECKUSER */

#if (defined(EMU86_EMULATE_RETURN_AFTER_HLT_IF0) || \
     defined(EMU86_EMULATE_RETURN_AFTER_HLT_IF1))
	if (EMU86_GETFLAGS() & EFLAGS_IF) {
#ifdef EMU86_EMULATE_RETURN_AFTER_HLT_IF1
		EMU86_SETPCPTR(REAL_IP());
		EMU86_EMULATE_RETURN_AFTER_HLT_IF1();
		__builtin_unreachable();
#endif /* EMU86_EMULATE_RETURN_AFTER_HLT_IF1 */
	} else {
#ifdef EMU86_EMULATE_RETURN_AFTER_HLT_IF0
		EMU86_SETPCPTR(REAL_IP());
		EMU86_EMULATE_RETURN_AFTER_HLT_IF0();
		__builtin_unreachable();
#endif /* EMU86_EMULATE_RETURN_AFTER_HLT_IF0 */
	}
#endif /* EMU86_EMULATE_RETURN_AFTER_HLT_IF(0|1) */
	goto done;
}
#elif EMU86_EMULATE_CONFIG_CHECKERROR && !EMU86_EMULATE_CONFIG_ONLY_CHECKERROR_NO_BASIC
case EMU86_OPCODE_ENCODE(0xf4):
	goto return_unsupported_instruction;
#define NEED_return_unsupported_instruction
#endif /* ... */

#endif /* !EMU86_EMULATE_CONFIG_ONLY_MEMORY */

}
EMU86_INTELLISENSE_END
