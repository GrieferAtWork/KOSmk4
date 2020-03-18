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

EMU86_INTELLISENSE_BEGIN(iret) {

case 0xcf: {
	/* CF     IRET     ZO     Valid     Valid     Interrupt return (16-bit operand size).
	 * CF     IRETD    ZO     Valid     Valid     Interrupt return (32-bit operand size).
	 * CF     IRETQ    ZO     Valid     Valid     Interrupt return (64-bit operand size). */
	byte_t *sp = (byte_t *)EMU86_GETSP();
#if CONFIG_LIBEMU86_WANT_64BIT
	if (IS_64BIT()) {
		u64 rip, rflags, rsp;
		u16 cs, ss;
		EMU86_EMULATE_POP(sp, 40);
		EMU86_READ_USER_MEMORY(sp, 40);
		rip    = EMU86_EMULATE_READQ(sp), sp += 8;
		cs     = EMU86_EMULATE_READQASW(sp), sp += 8;
		rflags = EMU86_EMULATE_READQ(sp), sp += 8;
		rsp    = EMU86_EMULATE_READQ(sp), sp += 8;
		ss     = EMU86_EMULATE_READQASW(sp), sp += 8;
#if EMU86_EMULATE_CHECKUSER
		if (!SEGMENT_IS_VALID_USERCODE(cs) && EMU86_ISUSER()) {
			THROW(E_INVALID_ARGUMENT_BAD_VALUE,
			      E_INVALID_ARGUMENT_CONTEXT_SIGRETURN_REGISTER,
			      X86_REGISTER_SEGMENT_CS, cs);
		}
		if (!SEGMENT_IS_VALID_USERDATA(ss) && EMU86_ISUSER()) {
			THROW(E_INVALID_ARGUMENT_BAD_VALUE,
			      E_INVALID_ARGUMENT_CONTEXT_SIGRETURN_REGISTER,
			      X86_REGISTER_SEGMENT_SS, ss);
		}
#ifndef EMU86_ALLOWED_EFLAGS_MODIFY_MASK_IS_FULL
		{
			u64 old_eflags, mask;
			old_eflags = EMU86_GETFLAGS();
			mask       = EMU86_ALLOWED_EFLAGS_MODIFY_MASK();
			if ((old_eflags & ~mask) != (rflags & ~mask) && EMU86_ISUSER()) {
				THROW(E_INVALID_ARGUMENT_BAD_VALUE,
				      E_INVALID_ARGUMENT_CONTEXT_SIGRETURN_REGISTER,
				      X86_REGISTER_MISC_EFLAGS,
				      (uintptr_t)rflags);
			}
		}
#endif /* !EMU86_ALLOWED_EFLAGS_MODIFY_MASK_IS_FULL */
#endif /* EMU86_EMULATE_CHECKUSER */
		sp = (byte_t *)rsp;
		EMU86_SETSS(ss);
		EMU86_SETFLAGS(rflags);
		EMU86_SETCS(cs);
		EMU86_EMULATE_SETPC(rip);
	} else
#endif /* CONFIG_LIBEMU86_WANT_64BIT */
	{
		u32 eip, eflags;
		u16 cs;
		unsigned int wordsize;
#if EMU86_EMULATE_VM86
		bool new_vm86_if = false;
#endif /* EMU86_EMULATE_VM86 */
		wordsize = IS_16BIT() ? 2 : 4;
		EMU86_EMULATE_POP(sp, 3 * wordsize);
		EMU86_READ_USER_MEMORY(sp, 3 * wordsize);
		if (wordsize == 2) {
			eip    = EMU86_EMULATE_READW(sp), sp += 2;
			cs     = EMU86_EMULATE_READW(sp), sp += 2;
			eflags = EMU86_EMULATE_READW(sp), sp += 2;
		} else {
			eip    = EMU86_EMULATE_READL(sp), sp += 4;
			cs     = EMU86_EMULATE_READLASW(sp), sp += 4;
			eflags = EMU86_EMULATE_READL(sp), sp += 4;
		}
#if EMU86_EMULATE_CHECKUSER && (CONFIG_LIBEMU86_WANT_32BIT || CONFIG_LIBEMU86_WANT_64BIT)
		if (!SEGMENT_IS_VALID_USERCODE(cs) && !EMU86_ISVM86() &&
#if EMU86_EMULATE_VM86
		    !(eflags & EFLAGS_VM) &&
#endif /* EMU86_EMULATE_VM86 */
		    EMU86_ISUSER_NOVM86()) {
			THROW(E_INVALID_ARGUMENT_BAD_VALUE,
			      E_INVALID_ARGUMENT_CONTEXT_SIGRETURN_REGISTER,
			      X86_REGISTER_SEGMENT_CS, cs);
		}
#endif /* EMU86_EMULATE_CHECKUSER && (CONFIG_LIBEMU86_WANT_32BIT || CONFIG_LIBEMU86_WANT_64BIT) */
#if EMU86_EMULATE_VM86
		if (EMU86_ISVM86()) {
			new_vm86_if = (eflags & EFLAGS_IF) != 0;
			if (eflags & EFLAGS_VM) {
				/* Cannot re-enter vm86 when already inside of vm86! */
				THROW(E_INVALID_ARGUMENT_BAD_VALUE,
				      E_INVALID_ARGUMENT_CONTEXT_SIGRETURN_REGISTER,
				      X86_REGISTER_MISC_EFLAGS, eflags);
			}
			eflags = (eflags & ~(EFLAGS_IF | EFLAGS_IOPLMASK)) |
			         (EMU86_GETFLAGS() & (EFLAGS_IF | EFLAGS_IOPLMASK)) |
			         EFLAGS_VM;
		}
#if EMU86_EMULATE_CHECKUSER && !defined(EMU86_ALLOWED_EFLAGS_MODIFY_MASK_IS_FULL)
		else
#endif /* EMU86_EMULATE_CHECKUSER && !EMU86_ALLOWED_EFLAGS_MODIFY_MASK_IS_FULL */
#endif /* EMU86_EMULATE_VM86 */
#if EMU86_EMULATE_CHECKUSER && !defined(EMU86_ALLOWED_EFLAGS_MODIFY_MASK_IS_FULL)
		{
			u32 old_eflags, mask;
			old_eflags = EMU86_GETFLAGS();
			mask       = EMU86_ALLOWED_EFLAGS_MODIFY_MASK();
			if ((old_eflags & ~mask) != (eflags & ~mask) && EMU86_ISUSER()) {
				THROW(E_INVALID_ARGUMENT_BAD_VALUE,
				      E_INVALID_ARGUMENT_CONTEXT_SIGRETURN_REGISTER,
				      X86_REGISTER_MISC_EFLAGS,
				      eflags);
			}
		}
#endif /* EMU86_EMULATE_CHECKUSER && !EMU86_ALLOWED_EFLAGS_MODIFY_MASK_IS_FULL */
#if CONFIG_LIBEMU86_WANT_32BIT || CONFIG_LIBEMU86_WANT_64BIT
		if (((cs & 3) != (EMU86_GETCS() & 3))
#if EMU86_EMULATE_VM86
		    || (eflags & EFLAGS_VM)
#endif /* EMU86_EMULATE_VM86 */
		    ) {
			u32 esp;
			u16 ss;
			EMU86_EMULATE_POP(sp - (3 * wordsize), 5 * wordsize);
			EMU86_READ_USER_MEMORY(sp, 2 * wordsize);
			if (wordsize == 2) {
				esp = EMU86_EMULATE_READW(sp), sp += 2;
				ss  = EMU86_EMULATE_READW(sp), sp += 2;
			} else {
				esp = EMU86_EMULATE_READL(sp), sp += 4;
				ss  = EMU86_EMULATE_READLASW(sp), sp += 4;
			}
#if EMU86_EMULATE_CHECKUSER
			if (!SEGMENT_IS_VALID_USERDATA(ss) && !(eflags & EFLAGS_VM)) {
				THROW(E_INVALID_ARGUMENT_BAD_VALUE,
				      E_INVALID_ARGUMENT_CONTEXT_SIGRETURN_REGISTER,
				      X86_REGISTER_SEGMENT_SS, ss);
			}
#endif /* EMU86_EMULATE_CHECKUSER */
#if EMU86_EMULATE_VM86
			if (eflags & EFLAGS_VM) {
				u16 es, ds, fs, gs;
				EMU86_EMULATE_POP(sp - (5 * wordsize), 9 * wordsize);
				EMU86_READ_USER_MEMORY(sp, 4 * wordsize);
				if (wordsize == 2) {
				} else {
				}
				es = EMU86_EMULATE_READLASW(sp), sp += 4;
				ds = EMU86_EMULATE_READLASW(sp), sp += 4;
				fs = EMU86_EMULATE_READLASW(sp), sp += 4;
				gs = EMU86_EMULATE_READLASW(sp), sp += 4;
				EMU86_SETES(es);
				EMU86_SETDS(ds);
				EMU86_SETFS(fs);
				EMU86_SETGS(gs);
			}
#endif /* EMU86_EMULATE_VM86 */
			sp = (byte_t *)esp;
			EMU86_SETSS(ss);
		}
#endif /* CONFIG_LIBEMU86_WANT_32BIT || CONFIG_LIBEMU86_WANT_64BIT */
		EMU86_SETFLAGS(eflags);
		EMU86_SETCS(cs);
		EMU86_EMULATE_SETPC(eip);
#if EMU86_EMULATE_VM86
		if (EMU86_ISVM86())
			EMU86_EMULATE_VM86_SETIF(new_vm86_if);
#endif /* EMU86_EMULATE_VM86 */
	}
	EMU86_SETSP_RAW((uintptr_t)sp);
	goto done_dont_set_pc;
}


}
EMU86_INTELLISENSE_END
