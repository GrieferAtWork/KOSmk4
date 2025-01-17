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

EMU86_INTELLISENSE_BEGIN(stif) {

#if !EMU86_EMULATE_CONFIG_ONLY_MEMORY

	/* Instructions that modify the EFLAGS.IF (interrupt) bit. */

#if EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_CLI
case EMU86_OPCODE_ENCODE(0xfa): {
	/* FA     CLI     Clear interrupt flag; interrupts disabled when interrupt flag cleared. */
#if EMU86_EMULATE_CONFIG_WANT_CLI && EMU86_EMULATE_CONFIG_VM86
	if (EMU86_ISVM86()) {
		EMU86_EMULATE_VM86_SETIF(0);
		goto done;
	}
#endif /* EMU86_EMULATE_CONFIG_WANT_CLI && EMU86_EMULATE_CONFIG_VM86 */

#if EMU86_EMULATE_CONFIG_CHECKUSER
	if unlikely(EMU86_ISUSER())
		goto return_privileged_instruction;
#define NEED_return_privileged_instruction
#endif /* EMU86_EMULATE_CONFIG_CHECKUSER */

#if EMU86_EMULATE_CONFIG_WANT_CLI
	EMU86_MSKFLAGS(~EFLAGS_IF, 0);
	goto done;
#else /* EMU86_EMULATE_CONFIG_WANT_CLI */
	goto return_unsupported_instruction;
#define NEED_return_unsupported_instruction
#endif /* !EMU86_EMULATE_CONFIG_WANT_CLI */
}
#endif /* EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_CLI */


#if EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_STI
case EMU86_OPCODE_ENCODE(0xfb): {
	/* FB     STI     Set interrupt flag; external, maskable interrupts
	 *                enabled  at  the  end  of  the  next instruction. */
#if EMU86_EMULATE_CONFIG_WANT_STI && EMU86_EMULATE_CONFIG_VM86
	if (EMU86_ISVM86()) {
		EMU86_EMULATE_VM86_SETIF(1);
#ifdef EMU86_EMULATE_RETURN_AFTER_STI_VM86
		/* Set the return program counter. */
		EMU86_SETPCPTR(REAL_IP());
		/* Execute the custom return statement. */
		EMU86_EMULATE_RETURN_AFTER_STI_VM86();
		__builtin_unreachable();
#else /* EMU86_EMULATE_RETURN_AFTER_STI_VM86 */
		goto done;
#endif /* !EMU86_EMULATE_RETURN_AFTER_STI_VM86 */
	}
#endif /* EMU86_EMULATE_CONFIG_WANT_STI && EMU86_EMULATE_CONFIG_VM86 */

#if EMU86_EMULATE_CONFIG_CHECKUSER
	if unlikely(EMU86_ISUSER())
		goto return_privileged_instruction;
#define NEED_return_privileged_instruction
#endif /* EMU86_EMULATE_CONFIG_CHECKUSER */

#if EMU86_EMULATE_CONFIG_WANT_STI
#ifdef EMU86_EMULATE_RETURN_AFTER_STI
	{
		uintptr_t old_flags;
		old_flags = EMU86_GETFLAGS();
		if (old_flags & EFLAGS_IF)
			goto done; /* #IF was already on (sti is a no-op) */
		/* Turn on #IF */
		EMU86_SETFLAGS(old_flags | EFLAGS_IF);
	}
	/* Set the return program counter. */
	EMU86_SETPCPTR(REAL_IP());
	/* Execute the custom return statement. */
	EMU86_EMULATE_RETURN_AFTER_STI();
	__builtin_unreachable();
#else /* EMU86_EMULATE_RETURN_AFTER_STI */
	EMU86_MSKFLAGS(~EFLAGS_IF, EFLAGS_IF);
	goto done;
#endif /* !EMU86_EMULATE_RETURN_AFTER_STI */
#else /* EMU86_EMULATE_CONFIG_WANT_STI */
	goto return_unsupported_instruction;
#define NEED_return_unsupported_instruction
#endif /* !EMU86_EMULATE_CONFIG_WANT_STI */
}
#endif /* EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_STI */


#endif /* !EMU86_EMULATE_CONFIG_ONLY_MEMORY */

}
EMU86_INTELLISENSE_END
