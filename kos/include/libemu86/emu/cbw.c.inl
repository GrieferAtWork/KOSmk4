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

EMU86_INTELLISENSE_BEGIN(cbw) {

#if !EMU86_EMULATE_CONFIG_ONLY_MEMORY

#if EMU86_EMULATE_CONFIG_WANT_CBW
case EMU86_OPCODE_ENCODE(0x98): {
	/*         98     CBW      AX := sign-extend of AL.
	 *         98     CWDE     EAX := sign-extend of AX.
	 * REX.W + 98     CDQE     RAX := sign-extend of EAX. */
	IF_64BIT(if (IS_64BIT()) {
		EMU86_SETRAX((u64)(s64)(s32)EMU86_GETEAX());
	} else) if (!IS_16BIT()) {
		EMU86_SETEAX((u32)(s32)(s16)EMU86_GETAX());
	} else {
		EMU86_SETAX((u16)(s16)(s8)EMU86_GETAL());
	}
	goto done;
}
#elif EMU86_EMULATE_CONFIG_CHECKERROR && !EMU86_EMULATE_CONFIG_ONLY_CHECKERROR_NO_BASIC
case EMU86_OPCODE_ENCODE(0x98):
	goto return_unsupported_instruction;
#define NEED_return_unsupported_instruction
#endif /* ... */


#if EMU86_EMULATE_CONFIG_WANT_CWD
case EMU86_OPCODE_ENCODE(0x99): {
	/*         99     CWD     DX:AX := sign-extend of AX.
	 *         99     CDQ     EDX:EAX := sign-extend of EAX.
	 * REX.W + 99     CQO     RDX:RAX:= sign-extend of RAX. */
	IF_64BIT(if (IS_64BIT()) {
		s64 rax;
		rax = (s64)EMU86_GETRAX();
		EMU86_SETRDX(rax < 0 ? UINT64_MAX : 0);
	} else) if (!IS_16BIT()) {
		s32 eax;
		eax = (s32)EMU86_GETEAX();
		EMU86_SETEDX(eax < 0 ? UINT32_MAX : 0);
	} else {
		s16 ax;
		ax = (s16)EMU86_GETAX();
		EMU86_SETDX(ax < 0 ? UINT16_MAX : 0);
	}
	goto done;
}
#elif EMU86_EMULATE_CONFIG_CHECKERROR && !EMU86_EMULATE_CONFIG_ONLY_CHECKERROR_NO_BASIC
case EMU86_OPCODE_ENCODE(0x99):
	goto return_unsupported_instruction;
#define NEED_return_unsupported_instruction
#endif /* ... */

#endif /* !EMU86_EMULATE_CONFIG_ONLY_MEMORY */

}
EMU86_INTELLISENSE_END
