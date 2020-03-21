/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifdef __INTELLISENSE__
#include "../emulate.c.inl"
#endif /* __INTELLISENSE__ */

EMU86_INTELLISENSE_BEGIN(int) {

#ifndef EMU86_EMULATE_ONLY_MEMORY

#ifdef EMU86_EMULATE_RETURN_AFTER_INT1
case 0xf1: {
	/* F1     INT1     Generate debug trap. */
	EMU86_SETPCPTR(REAL_IP());
	EMU86_EMULATE_RETURN_AFTER_INT1();
	__builtin_unreachable();
}
#endif /* EMU86_EMULATE_RETURN_AFTER_INT1 */

#ifdef EMU86_EMULATE_RETURN_AFTER_INT3
case 0xcc: {
	/* CC     INT3     Generate breakpoint trap. */
	EMU86_SETPCPTR(REAL_IP());
	EMU86_EMULATE_RETURN_AFTER_INT3();
	__builtin_unreachable();
}
#endif /* EMU86_EMULATE_RETURN_AFTER_INT3 */

#ifdef EMU86_EMULATE_RETURN_AFTER_INT
case 0xcd: {
	/* CD ib     INT imm8     Generate software interrupt with vector specified by immediate byte. */
	u8 intno;
	intno = *(u8 *)pc;
	pc += 1;
	EMU86_SETPCPTR(REAL_IP());
	EMU86_EMULATE_RETURN_AFTER_INT(intno);
	__builtin_unreachable();
}
#endif /* EMU86_EMULATE_RETURN_AFTER_INT */

#ifdef EMU86_EMULATE_RETURN_AFTER_INTO
case 0xce: {
	/* CE     INTO     Generate overflow trap if overflow flag is 1. */
	if (EMU86_GETFLAGS() & EFLAGS_OF) {
		EMU86_SETPCPTR(REAL_IP());
		EMU86_EMULATE_RETURN_AFTER_INTO();
		__builtin_unreachable();
	}
	goto done;
}
#endif /* EMU86_EMULATE_RETURN_AFTER_INTO */

#endif /* !EMU86_EMULATE_ONLY_MEMORY */

}
EMU86_INTELLISENSE_END
