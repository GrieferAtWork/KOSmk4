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

#include "string-util.h"

EMU86_INTELLISENSE_BEGIN(scas) {


#if EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_SCAS
case EMU86_OPCODE_ENCODE(0xae): {
	/* AE     SCASB     Compare AL with byte at ES:(E)DI or RDI then set status flags. */
#if EMU86_EMULATE_CONFIG_WANT_SCAS
	u8 lhs, rhs;
	u32 new_eflags;
	EMU86_READ_STRING_EX_IMPL(EMU86_ADDRSIZE_SWITCH,
	                          ES, DI, B, 8, 1, rhs,
	                          op_flags & (EMU86_F_REP | EMU86_F_REPNE),
	                          /**/);
	lhs        = EMU86_GETAL();
	new_eflags = emu86_geteflags_cmpb(lhs, rhs);
	/* Set new eflags */
	EMU86_MSKFLAGS(~(EFLAGS_OF | EFLAGS_SF | EFLAGS_ZF |
	                 EFLAGS_AF | EFLAGS_PF | EFLAGS_CF),
	               new_eflags);
	/* Check for repeat */
	if (op_flags & EMU86_F_REP) {
		/* repe scasb   (while equal)*/
		if (new_eflags & EFLAGS_ZF)
			goto done_dont_set_pc;
#define NEED_done_dont_set_pc
	} else if (op_flags & EMU86_F_REPNE) {
		/* repne scasb   (while not equal) */
		if (!(new_eflags & EFLAGS_ZF))
			goto done_dont_set_pc;
#define NEED_done_dont_set_pc
	}
	goto done;
#else /* EMU86_EMULATE_CONFIG_WANT_SCAS */
	goto notsup_lodsb;
#define NEED_notsup_lodsb
#endif /* !EMU86_EMULATE_CONFIG_WANT_SCAS */
}
#endif /* EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_SCAS */



#if EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_SCAS
case EMU86_OPCODE_ENCODE(0xaf): {
	/*         AF     SCASW     Compare AX with word at ES:(E)DI or RDI then set status flags.
	 *         AF     SCASD     Compare EAX with doubleword at ES:(E)DI or RDI then set status flags.
	 * REX.W + AF     SCASQ     Compare RAX with quadword at RDI or EDI then set status flags. */
#if EMU86_EMULATE_CONFIG_WANT_SCAS
	u32 new_eflags;
	IF_64BIT(if (IS_64BIT()) {
		u64 lhs, rhs;
		EMU86_READ_STRING_EX_IMPL(EMU86_ADDRSIZE_SWITCH,
		                          ES, DI, Q, 64, 8, rhs,
		                          op_flags & (EMU86_F_REP | EMU86_F_REPNE),
		                          /**/);
		lhs        = EMU86_GETRAX();
		new_eflags = emu86_geteflags_cmpq(lhs, rhs);
	} else) if (!IS_16BIT()) {
		u32 lhs, rhs;
		EMU86_READ_STRING_EX_IMPL(EMU86_ADDRSIZE_SWITCH,
		                          ES, DI, L, 32, 4, rhs,
		                          op_flags & (EMU86_F_REP | EMU86_F_REPNE),
		                          /**/);
		lhs        = EMU86_GETEAX();
		new_eflags = emu86_geteflags_cmpl(lhs, rhs);
	} else {
		u16 lhs, rhs;
		EMU86_READ_STRING_EX_IMPL(EMU86_ADDRSIZE_SWITCH,
		                          ES, DI, W, 16, 2, rhs,
		                          op_flags & (EMU86_F_REP | EMU86_F_REPNE),
		                          /**/);
		lhs        = EMU86_GETAX();
		new_eflags = emu86_geteflags_cmpw(lhs, rhs);
	}
	/* Set new eflags */
	EMU86_MSKFLAGS(~(EFLAGS_OF | EFLAGS_SF | EFLAGS_ZF |
	                 EFLAGS_AF | EFLAGS_PF | EFLAGS_CF),
	               new_eflags);
	/* Check for repeat */
	if (op_flags & EMU86_F_REP) {
		/* repe scas(w|l|q)   (while equal)*/
		if (new_eflags & EFLAGS_ZF)
			goto done_dont_set_pc;
#define NEED_done_dont_set_pc
	} else if (op_flags & EMU86_F_REPNE) {
		/* repne scas(w|l|q)   (while not equal) */
		if (!(new_eflags & EFLAGS_ZF))
			goto done_dont_set_pc;
#define NEED_done_dont_set_pc
	}
	goto done;
#else /* EMU86_EMULATE_CONFIG_WANT_SCAS */
	goto notsup_lodswlq;
#define NEED_notsup_lodswlq
#endif /* !EMU86_EMULATE_CONFIG_WANT_SCAS */
}
#endif /* EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_SCAS */



}
EMU86_INTELLISENSE_END
