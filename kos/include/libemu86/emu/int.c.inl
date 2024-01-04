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

EMU86_INTELLISENSE_BEGIN(int) {

#if !EMU86_EMULATE_CONFIG_ONLY_MEMORY

#if (EMU86_EMULATE_CONFIG_CHECKERROR && !EMU86_EMULATE_CONFIG_ONLY_CHECKERROR_NO_BASIC) || EMU86_EMULATE_CONFIG_WANT_INT1
case EMU86_OPCODE_ENCODE(0xf1): {
	/* F1     INT1     Generate debug trap. */
#if EMU86_EMULATE_CONFIG_WANT_INT1 && defined(EMU86_EMULATE_RETURN_AFTER_INT1)
	EMU86_SETPCPTR(REAL_IP());
	EMU86_EMULATE_RETURN_AFTER_INT1();
	__builtin_unreachable();
#else /* EMU86_EMULATE_CONFIG_WANT_INT1 && EMU86_EMULATE_RETURN_AFTER_INT1 */
	goto return_unsupported_instruction;
#define NEED_return_unsupported_instruction
#endif /* !EMU86_EMULATE_CONFIG_WANT_INT1 || !EMU86_EMULATE_RETURN_AFTER_INT1 */
}
#endif /* (EMU86_EMULATE_CONFIG_CHECKERROR && !EMU86_EMULATE_CONFIG_ONLY_CHECKERROR_NO_BASIC) || EMU86_EMULATE_CONFIG_WANT_INT1 */


#if (EMU86_EMULATE_CONFIG_CHECKERROR && !EMU86_EMULATE_CONFIG_ONLY_CHECKERROR_NO_BASIC) || EMU86_EMULATE_CONFIG_WANT_INT3
case EMU86_OPCODE_ENCODE(0xcc): {
	/* CC     INT3     Generate breakpoint trap. */
#if EMU86_EMULATE_CONFIG_WANT_INT3 && defined(EMU86_EMULATE_RETURN_AFTER_INT3)
	EMU86_SETPCPTR(REAL_IP());
	EMU86_EMULATE_RETURN_AFTER_INT3();
	__builtin_unreachable();
#else /* EMU86_EMULATE_CONFIG_WANT_INT3 && EMU86_EMULATE_RETURN_AFTER_INT3 */
	goto return_unsupported_instruction;
#define NEED_return_unsupported_instruction
#endif /* !EMU86_EMULATE_CONFIG_WANT_INT3 || !EMU86_EMULATE_RETURN_AFTER_INT3 */
}
#endif /* (EMU86_EMULATE_CONFIG_CHECKERROR && !EMU86_EMULATE_CONFIG_ONLY_CHECKERROR_NO_BASIC) || EMU86_EMULATE_CONFIG_WANT_INT3 */


#if (EMU86_EMULATE_CONFIG_CHECKERROR && !EMU86_EMULATE_CONFIG_ONLY_CHECKERROR_NO_BASIC) || EMU86_EMULATE_CONFIG_WANT_INT
case EMU86_OPCODE_ENCODE(0xcd): {
	/* CD ib     INT imm8     Generate software interrupt with vector specified by immediate byte. */
#if EMU86_EMULATE_CONFIG_WANT_INT && defined(EMU86_EMULATE_RETURN_AFTER_INT)
	u8 intno;
	intno = *(u8 const *)pc;
	pc += 1;
	EMU86_SETPCPTR(REAL_IP());
	EMU86_EMULATE_RETURN_AFTER_INT(intno);
	__builtin_unreachable();
#else /* EMU86_EMULATE_CONFIG_WANT_INT && EMU86_EMULATE_RETURN_AFTER_INT */
	goto return_unsupported_instruction;
#define NEED_return_unsupported_instruction
#endif /* !EMU86_EMULATE_CONFIG_WANT_INT || !EMU86_EMULATE_RETURN_AFTER_INT */
}
#endif /* (EMU86_EMULATE_CONFIG_CHECKERROR && !EMU86_EMULATE_CONFIG_ONLY_CHECKERROR_NO_BASIC) || EMU86_EMULATE_CONFIG_WANT_INT */


#if (EMU86_EMULATE_CONFIG_CHECKERROR && !EMU86_EMULATE_CONFIG_ONLY_CHECKERROR_NO_BASIC) || EMU86_EMULATE_CONFIG_WANT_INTO
case EMU86_OPCODE_ENCODE(0xce): {
	/* CE     INTO     Generate overflow trap if overflow flag is 1. */
#if EMU86_EMULATE_CONFIG_WANT_INTO && defined(EMU86_EMULATE_RETURN_AFTER_INTO)
	if (EMU86_GETFLAGS() & EFLAGS_OF) {
		EMU86_SETPCPTR(REAL_IP());
		EMU86_EMULATE_RETURN_AFTER_INTO();
		__builtin_unreachable();
	}
	goto done;
#else /* EMU86_EMULATE_CONFIG_WANT_INTO && EMU86_EMULATE_RETURN_AFTER_INTO */
	goto return_unsupported_instruction;
#define NEED_return_unsupported_instruction
#endif /* !EMU86_EMULATE_CONFIG_WANT_INTO || !EMU86_EMULATE_RETURN_AFTER_INTO */
}
#endif /* (EMU86_EMULATE_CONFIG_CHECKERROR && !EMU86_EMULATE_CONFIG_ONLY_CHECKERROR_NO_BASIC) || EMU86_EMULATE_CONFIG_WANT_INTO */

#endif /* !EMU86_EMULATE_CONFIG_ONLY_MEMORY */

}
EMU86_INTELLISENSE_END
