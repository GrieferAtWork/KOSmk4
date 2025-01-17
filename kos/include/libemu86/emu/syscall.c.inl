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

EMU86_INTELLISENSE_BEGIN(syscall) {

#if !EMU86_EMULATE_CONFIG_ONLY_MEMORY
#if (EMU86_EMULATE_CONFIG_CHECKERROR ||    \
     (EMU86_EMULATE_CONFIG_WANT_SYSCALL && \
      LIBEMU86_CONFIG_WANT_64BIT &&        \
      defined(EMU86_EMULATE_RETURN_AFTER_SYSCALL)))
case EMU86_OPCODE_ENCODE(0x0f05): {
	/* 0F 05     SYSCALL     Fast call to privilege level 0 system procedures. */
#if EMU86_EMULATE_CONFIG_WANT_SYSCALL && defined(EMU86_EMULATE_RETURN_AFTER_SYSCALL)
#if LIBEMU86_CONFIG_WANT_16BIT || LIBEMU86_CONFIG_WANT_32BIT
	if unlikely(!EMU86_F_IS64(op_flags))
		goto return_unsupported_instruction;
#define NEED_return_unsupported_instruction
#endif /* LIBEMU86_CONFIG_WANT_16BIT || LIBEMU86_CONFIG_WANT_32BIT */
	EMU86_SETPCPTR(REAL_IP());
	EMU86_EMULATE_RETURN_AFTER_SYSCALL();
	__builtin_unreachable();
#else /* EMU86_EMULATE_CONFIG_WANT_SYSCALL && EMU86_EMULATE_RETURN_AFTER_SYSCALL */
	goto return_unsupported_instruction;
#define NEED_return_unsupported_instruction
#endif /* !EMU86_EMULATE_CONFIG_WANT_SYSCALL || !EMU86_EMULATE_RETURN_AFTER_SYSCALL */
}
#endif /* EMU86_EMULATE_CONFIG_WANT_SYSCALL || (EMU86_EMULATE_CONFIG_WANT_SYSCALL && LIBEMU86_CONFIG_WANT_64BIT && EMU86_EMULATE_RETURN_AFTER_SYSCALL) */
#endif /* !EMU86_EMULATE_CONFIG_ONLY_MEMORY */

}
EMU86_INTELLISENSE_END
