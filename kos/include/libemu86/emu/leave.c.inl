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

EMU86_INTELLISENSE_BEGIN(leave) {

case 0xc9:
	/* C9     LEAVE     ZO     Valid    Valid     Set SP to BP, then pop BP.
	 * C9     LEAVE     ZO     N.E.     Valid     Set ESP to EBP, then pop EBP. */
#ifndef EMU86_GETSEGBASE_IS_NOOP_SS
	byte_t *bp_addr;
#endif /* !EMU86_GETSEGBASE_IS_NOOP_SS */
	if (IS_16BIT()) {
		u16 bp, orig_bp;
		bp = EMU86_GETBP();
#ifndef EMU86_GETSEGBASE_IS_NOOP_SS
		bp_addr = (byte_t *)EMU86_SEGADDR(EMU86_GETSEGBASE(EMU86_R_SS), bp) - 2;
		EMU86_READ_USER_MEMORY(bp_addr, 2);
		orig_bp = EMU86_EMULATE_READW(bp_addr);
#else /* !EMU86_GETSEGBASE_IS_NOOP_SS */
		EMU86_READ_USER_MEMORY(bp - 2, 2);
		orig_bp = EMU86_EMULATE_READW(bp - 2);
#endif /* EMU86_GETSEGBASE_IS_NOOP_SS */
		EMU86_SETBP(orig_bp);
		EMU86_SETSP_RAW(bp);
	}
#if CONFIG_LIBEMU86_WANT_64BIT
	else
#if CONFIG_LIBEMU86_WANT_32BIT || CONFIG_LIBEMU86_WANT_16BIT
		if (EMU86_F_IS64(op_flags))
#endif /* CONFIG_LIBEMU86_WANT_32BIT || CONFIG_LIBEMU86_WANT_16BIT */
	{
		u64 bp, orig_bp;
		bp = EMU86_GETRBP();
#ifndef EMU86_GETSEGBASE_IS_NOOP_SS
		bp_addr = (byte_t *)EMU86_SEGADDR(EMU86_GETSEGBASE(EMU86_R_SS), bp) - 8;
		EMU86_READ_USER_MEMORY(bp_addr, 8);
		orig_bp = EMU86_EMULATE_READQ(bp_addr);
#else /* !EMU86_GETSEGBASE_IS_NOOP_SS */
		EMU86_READ_USER_MEMORY(bp - 8, 8);
		orig_bp = EMU86_EMULATE_READQ(bp - 8);
#endif /* EMU86_GETSEGBASE_IS_NOOP_SS */
		EMU86_SETRBP(orig_bp);
		EMU86_SETSP_RAW(bp);
	}
#endif /* CONFIG_LIBEMU86_WANT_64BIT */
#if CONFIG_LIBEMU86_WANT_32BIT || CONFIG_LIBEMU86_WANT_16BIT
	else {
		u32 bp, orig_bp;
		bp = EMU86_GETEBP();
#ifndef EMU86_GETSEGBASE_IS_NOOP_SS
		bp_addr = (byte_t *)EMU86_SEGADDR(EMU86_GETSEGBASE(EMU86_R_SS), bp) - 4;
		EMU86_READ_USER_MEMORY(bp_addr, 4);
		orig_bp = EMU86_EMULATE_READL(bp_addr);
#else /* !EMU86_GETSEGBASE_IS_NOOP_SS */
		EMU86_READ_USER_MEMORY(bp - 4, 4);
		orig_bp = EMU86_EMULATE_READL(bp - 4);
#endif /* EMU86_GETSEGBASE_IS_NOOP_SS */
		EMU86_SETEBP(orig_bp);
		EMU86_SETSP_RAW(bp);
	}
#endif /* CONFIG_LIBEMU86_WANT_32BIT || CONFIG_LIBEMU86_WANT_16BIT */
	goto done;
}
EMU86_INTELLISENSE_END
