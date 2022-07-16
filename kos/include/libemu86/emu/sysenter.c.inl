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

EMU86_INTELLISENSE_BEGIN(sysenter) {

#if !EMU86_EMULATE_CONFIG_ONLY_MEMORY
#if (EMU86_EMULATE_CONFIG_CHECKERROR ||               \
     (defined(EMU86_EMULATE_RETURN_AFTER_SYSENTER) && \
      EMU86_EMULATE_CONFIG_WANT_SYSENTER))
case EMU86_OPCODE_ENCODE(0x0f34): {
	/* 0F 34     SYSENTER     Fast call to privilege level 0 system procedures. */
#if EMU86_EMULATE_CONFIG_WANT_SYSENTER && defined(EMU86_EMULATE_RETURN_AFTER_SYSENTER)
#if LIBEMU86_CONFIG_WANT_16BIT
	/* Intel  documents that sysenter  cannot be used from
	 * real-mode (i.e. 16-bit mode, or in this case: vm86) */
	if unlikely(EMU86_F_IS16(op_flags))
		goto return_unsupported_instruction;
#define NEED_return_unsupported_instruction
#endif /* LIBEMU86_CONFIG_WANT_16BIT */
	/* Canonically, sysenter override the return IP, so no need to write it back here! */
	/*EMU86_SETPCPTR(REAL_IP());*/
	EMU86_EMULATE_RETURN_AFTER_SYSENTER();
	__builtin_unreachable();
#else /* EMU86_EMULATE_CONFIG_WANT_SYSENTER && EMU86_EMULATE_RETURN_AFTER_SYSENTER */
	goto return_unsupported_instruction;
#define NEED_return_unsupported_instruction
#endif /* !EMU86_EMULATE_CONFIG_WANT_SYSENTER || !EMU86_EMULATE_RETURN_AFTER_SYSENTER */
}
#endif /* EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_RETURN_AFTER_SYSENTER */
#endif /* !EMU86_EMULATE_CONFIG_ONLY_MEMORY */

}
EMU86_INTELLISENSE_END
