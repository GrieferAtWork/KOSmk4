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

EMU86_INTELLISENSE_BEGIN(movsxd) {


#if (EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_MOVSXD || EMU86_EMULATE_CONFIG_WANT_ARPL)
case EMU86_OPCODE_ENCODE(0x63): {
	MODRM_DECODE();
#if EMU86_EMULATE_CONFIG_WANT_MOVSXD && LIBEMU86_CONFIG_WANT_64BIT
#if EMU86_EMULATE_CONFIG_WANT_ARPL && (LIBEMU86_CONFIG_WANT_32BIT || LIBEMU86_CONFIG_WANT_16BIT)
	if (EMU86_F_IS64(op_flags))
#endif /* EMU86_EMULATE_CONFIG_WANT_ARPL && (LIBEMU86_CONFIG_WANT_32BIT || LIBEMU86_CONFIG_WANT_16BIT) */
	{
#if EMU86_EMULATE_CONFIG_WANT_MOVSXD
		/*         63 /r*       MOVSXD r16, r/m16   Move word to word with sign-extension.
		 *         63 /r*       MOVSXD r32, r/m32   Move doubleword to doubleword with sign-extension.
		 * REX.W + 63 /r        MOVSXD r64, r/m32   Move doubleword to quadword with sign-extension. */
		if (IS_64BIT()) {
			s32 value;
			value = (s32)MODRM_GETRML();
			MODRM_SETREGQ((u64)(s64)value);
		} else if (!IS_16BIT()) {
			MODRM_SETREGL(MODRM_GETRML());
		} else {
			MODRM_SETREGW(MODRM_GETRMW());
		}
		goto done;
#else /* EMU86_EMULATE_CONFIG_WANT_MOVSXD */
		MODRM_NOSUP_GETRMZ(IS_64BIT() || !IS_16BIT() ? 4 : 2);
		goto return_unsupported_instruction;
#define NEED_return_unsupported_instruction
#endif /* !EMU86_EMULATE_CONFIG_WANT_MOVSXD */
	}
#endif /* EMU86_EMULATE_CONFIG_WANT_MOVSXD && LIBEMU86_CONFIG_WANT_64BIT */
#if EMU86_EMULATE_CONFIG_WANT_ARPL && (LIBEMU86_CONFIG_WANT_32BIT || LIBEMU86_CONFIG_WANT_16BIT)
#if EMU86_EMULATE_CONFIG_WANT_MOVSXD && LIBEMU86_CONFIG_WANT_64BIT
	else
#endif /* EMU86_EMULATE_CONFIG_WANT_MOVSXD && LIBEMU86_CONFIG_WANT_64BIT */
	{
#if EMU86_EMULATE_CONFIG_WANT_ARPL
		/* 63 /r     ARPL r/m16, r16     Adjust RPL of r/m16 to not less than RPL of r16. */
		u16 dst, src;
		u32 eflags_addend;
		src = MODRM_GETREGW();
		eflags_addend = 0;
		NIF_ONLY_MEMORY(
		if (EMU86_MODRM_ISREG(modrm.mi_type)) {
			dst = MODRM_GETRMREGW();
			if ((dst & 3) < (src & 3)) {
				u16 newval;
				newval = (dst & ~3) | (src & 3);
				MODRM_SETRMREGW(newval);
				eflags_addend = EFLAGS_ZF;
			}
		} else) {
			byte_t *addr;
			addr = MODRM_MEMADDR();
			EMU86_WRITE_USER_MEMORY(addr, 2);
#if EMU86_EMULATE_CONFIG_LOCK_ARPL
			for (;;)
#endif /* EMU86_EMULATE_CONFIG_LOCK_ARPL */
			{
				u16 newval;
				dst = EMU86_MEMREADW(addr);
				if ((dst & 3) >= (src & 3)) {
#if EMU86_EMULATE_CONFIG_LOCK_ARPL
					break;
#endif /* EMU86_EMULATE_CONFIG_LOCK_ARPL */
				} else {
					newval = (dst & ~3) | (src & 3);
#if EMU86_EMULATE_CONFIG_LOCK_ARPL
					if (EMU86_MEM_ATOMIC_CMPXCH_OR_WRITEW(addr, dst, newval,
					                                      EMU86_HASLOCK())) {
						eflags_addend = EFLAGS_ZF;
						break;
					}
					EMU86_EMULATE_LOOPHINT();
#else /* EMU86_EMULATE_CONFIG_LOCK_ARPL */
					EMU86_MEMWRITEW(addr, newval);
					eflags_addend = EFLAGS_ZF;
#endif /* !EMU86_EMULATE_CONFIG_LOCK_ARPL */
				}
			}
		}
		EMU86_MSKFLAGS(~EFLAGS_ZF, eflags_addend);
		goto done;
#else /* EMU86_EMULATE_CONFIG_WANT_ARPL */
		goto notsup_modrm_getsetw;
#define NEED_notsup_modrm_getsetw
#endif /* !EMU86_EMULATE_CONFIG_WANT_ARPL */
	}
#endif /* EMU86_EMULATE_CONFIG_WANT_ARPL && (LIBEMU86_CONFIG_WANT_32BIT || LIBEMU86_CONFIG_WANT_16BIT) */
	break;
}
#endif /* EMU86_EMULATE_CONFIG_CHECKERROR || ... */


}
EMU86_INTELLISENSE_END
