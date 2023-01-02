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

#include "push-pop-util.h"

EMU86_INTELLISENSE_BEGIN(pushf_popf) {


#if EMU86_EMULATE_CONFIG_WANT_PUSHF
case EMU86_OPCODE_ENCODE(0x9c): {
	/* 9C     PUSHF      Push lower 16 bits of EFLAGS.
	 * 9C     PUSHFD     Push EFLAGS.
	 * 9C     PUSHFQ     Push RFLAGS. */
	u32 value;
	value = EMU86_GETFLAGS() & ~(EFLAGS_VM | EFLAGS_RF);
#if EMU86_EMULATE_CONFIG_VM86
	if (EMU86_ISVM86()) {
		value |= EFLAGS_IOPL(3); /* (visible) IOPL is always 3 in vm86 mode. */
		value &= ~EFLAGS_IF;
		if (EMU86_EMULATE_VM86_GETIF())
			value |= EFLAGS_IF;
	}
#endif /* EMU86_EMULATE_CONFIG_VM86 */
	EMU86_PUSH163264((u16)value,
	                 (u32)value,
	                 (u64)value);
	goto done;
}
#elif EMU86_EMULATE_CONFIG_CHECKERROR
case EMU86_OPCODE_ENCODE(0x9c):
	goto notsup_pushwlq;
#define NEED_notsup_pushwlq
#endif /* ... */


#if EMU86_EMULATE_CONFIG_WANT_POPF
case EMU86_OPCODE_ENCODE(0x9d): {
	/* 9D     POPF      Pop top of stack into lower 16 bits of EFLAGS.
	 * 9D     POPFD     Pop top of stack into EFLAGS.
	 * 9D     POPFQ     Pop top of stack and zero-extend into RFLAGS. */
	u32 eflags_mask, new_eflags;
	byte_t *sp;
	sp = EMU86_GETSTACKPTR();
#define EFLAGS_MASK_COMMON                                 \
	(EFLAGS_RF | EFLAGS_NT | EFLAGS_IOPLMASK | EFLAGS_OF | \
	 EFLAGS_DF | EFLAGS_TF | EFLAGS_SF | EFLAGS_ZF |       \
	 EFLAGS_AF | EFLAGS_PF | EFLAGS_CF | EFLAGS_IF)
	EMU86_POP163264_IMPL(/* 16-bit  */
	                     eflags_mask = EFLAGS_MASK_COMMON;
	                     new_eflags  = (u32) /*value;*/,
	                     /* 32-bit  */
	                     eflags_mask = EFLAGS_MASK_COMMON | EFLAGS_ID | EFLAGS_AC;
	                     new_eflags  = ~(EFLAGS_RF) & (u32) /*value;*/,
	                     /* 64-bit  */
	                     eflags_mask = EFLAGS_MASK_COMMON | EFLAGS_ID | EFLAGS_AC;
	                     new_eflags  = ~(EFLAGS_RF) & (u32) /*value;*/);
#undef EFLAGS_MASK_COMMON
	EMU86_SETSTACKPTR(sp);
#if EMU86_EMULATE_CONFIG_VM86
	if (EMU86_ISVM86()) {
		EMU86_EMULATE_VM86_SETIF((new_eflags & EFLAGS_IF) != 0);
		eflags_mask &= ~(EFLAGS_IOPLMASK | EFLAGS_IF);
	} else
#endif /* EMU86_EMULATE_CONFIG_VM86 */
	{
		/* Allow modifications to  #IOPL and #IF  when IOPL=3 in  user-space.
		 * This matches the official documentation of `popf' which can modify
		 * #IF whenever #IOPL >= #CPL (where #CPL=3 for user-space) */
		if (EMU86_ISUSER() && (EMU86_GETFLAGS() & EFLAGS_IOPLMASK) != EFLAGS_IOPL(3))
			eflags_mask &= ~(EFLAGS_IOPLMASK | EFLAGS_IF);
	}
	EMU86_MSKFLAGS(~eflags_mask, new_eflags);
	goto done;
}
#elif EMU86_EMULATE_CONFIG_CHECKERROR
case EMU86_OPCODE_ENCODE(0x9d):
	goto notsup_popwlq;
#define NEED_notsup_popwlq
#endif /* ... */




}
EMU86_INTELLISENSE_END
